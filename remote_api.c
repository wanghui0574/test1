#include <string.h>
#include <comm.h>
#include <datatree.h>
#include <display.h>
#include "console.h"

#include "event.h"
#include "main.h"
#include "public.h"
#include "remote_api.h"
#if defined(M_LOCAL)
#include "local_api.h"
#include "money.h"
#endif
#include "iso7816_4.h"
#include "lpm.h"
NAME_THIS_FILE(Remote_api)

static struct KeyOperateInfo raKeyOperateInfo;                   // 密钥操作信息
static uint8_t masterStationRandom[4];                // 主站下发的前4字节随机数
static uint8_t diffusionFactor[8];                                   // 分散因子
static uint8_t ESAMSeriesNo[8];                                    // ESAM序列号
static uint8_t FirstResetEsamFlag;                   // 上电第一次复位ESAM的标志

uint8_t ra07000101[2] = {0x05, 0x00};                        // 身份认证有效时长
uint8_t operatorID_LRC[4] = {0xFF, 0XFF, 0XFF, 0XFF};// 运程控制拉合闸操作者代码
uint8_t  LongRangeCommand;
uint8_t  ra_timeCheckoutMAC;                      // 一天内MAC校验失败总累计次数
bool     ra_longRangeForbid;                                         // 远程挂起
bool Ir_Authorize_ask;                                   // 红外认证请求成功标志

static const struct DataMirror dataMirrors[] = {
    {&ra_timeCheckoutMAC, ADDR_OF(EE_sect7, eeTimeCheckoutMAC),  sizeof(ra_timeCheckoutMAC)   },
    {&ra_longRangeForbid, ADDR_OF(EE_sect7, eeLongRangeForbid),  sizeof(ra_longRangeForbid)   },
    {&ra04000508,         ADDR_OF(EE_sect7, ee04000508),         sizeof(ra04000508)           },
    {&ra07000101,         ADDR_OF(EE_sect2, ee07000101),         sizeof(ra07000101)           },
    {&operatorID_LRC,     ADDR_OF(EE_sect7, eeoperatorID_LRC),   sizeof(operatorID_LRC)       },
    {&LongRangeCommand,   ADDR_OF(EE_sect7, eeLongRangeCommand), sizeof(LongRangeCommand)     },
    {&raKeyOperateInfo,   ADDR_OF(EE_sect8, eeKeyOperateInfo),   sizeof(struct KeyOperateInfo)},
    {ESAMSeriesNo,        ADDR_OF(EE_sect7, eeESAM_SiresNo),     sizeof(ESAMSeriesNo)         },
};

enum Comm_Retval {
    COMM_RETVAL_ERROR = -1,
    COMM_RETVAL_OK,
    COMM_RETVAL_NO_SEQ,
    COMM_RETVAL_HAS_SEQ,
};

struct CommKeyFile {
    uint8_t sum;                                                       // 总条数
    uint8_t reserve;                                                     // 保留
    uint8_t id;                                                          // 编号
    uint8_t type;                                                        // 类型
    uint8_t text[32];                                                    // 密文
};

#define ESAM_RESET          0x01
#define ESAM_RESET_SUCCESS  0x02


uint8_t allKeysState_get(void)
{
    uint8_t i = 0;
    uint32_t msk = 1;
    uint8_t PrivateKeyCnt = 0;
    
    for (; i < ra04000208; i++) {
        if (ra04000508 & msk) {
            PrivateKeyCnt++;
        }
        msk <<= 1;
    }
    if (PrivateKeyCnt == 0) {
        return ALL_KEYS_PUBLIC;                                        // 全公钥
    }
    else if(PrivateKeyCnt == ra04000208) {
        return ALL_KEYS_PRIVATE;                                       // 全私钥
    }
    else {
        return ALL_KEYS_NOT_SAME;                           // 部分公钥,部分私钥
    }
}


/* ===========================================================================*/
/**
 * brief : 密钥状态显示
 * 
 * date  : 2012-09-24
 */
/* ---------------------------------------------------------------------------*/
void flushKeyStateDisplay(void)
{
    uint8_t keyDisplayState = allKeysState_get();
    
    if (keyDisplayState == ALL_KEYS_PRIVATE) {
        LCD_Seg_clr(LCD_SEG__HOUSE);
    }
    else if (keyDisplayState == ALL_KEYS_PUBLIC) {
        LCD_Seg_set(LCD_SEG__HOUSE, 0);
    }
    else {
        LCD_Seg_set(LCD_SEG__HOUSE, 1);
    }
}

void longRangeForbid_Process(void)
{
    if (ra_longRangeForbid) {
        LCD_Seg_set(LCD_SEG__LOCK, 0);
        lcd_seg_lock_Client |= LOCK_CT_LRF;
        if (RTC_Get_TimeChangeFlag() & (DATE|MONTH|YEAR)) {
            ra_longRangeForbid = false;
            ra_timeCheckoutMAC = 0;
            allmemput(ADDR_OF(EE_sect7, eeLongRangeForbid), &ra_longRangeForbid, 1);
            allmemput(ADDR_OF(EE_sect7, eeTimeCheckoutMAC), &ra_timeCheckoutMAC, 1);
        }
    }
    else {
        lcd_seg_lock_Client &= ~LOCK_CT_LRF;
        if (!lcd_seg_lock_Client) {
            LCD_Seg_clr(LCD_SEG__LOCK);
        }
        if (ra_timeCheckoutMAC >= 200) {
            ra_longRangeForbid = true;
            allmemput(ADDR_OF(EE_sect7, eeLongRangeForbid), &ra_longRangeForbid, 1);
        }
    }
}
/* ===========================================================================*/
/**
 * brief : 软件比对的程序获取
 * 
 * date  : 2012-10-17
 *
 * param : dest
 * param : start
 * param : n
 */
/* ---------------------------------------------------------------------------*/
static
bool Program_get(uint8_t *dest, uint32_t start, uint16_t n)
{
    uint32_t end;
    uint32_t addr_max = get_rom_end_addr(start);
    if (addr_max == 0xffffffff) {
        return false;
    }
    D_ASSERT(start < addr_max);
    
    end = start + n;
    if (end > addr_max) {
        uint16_t len = (uint16_t)(addr_max - start);
        memcpy(dest, (uint8_t *)start, len);
        dest[len] = 0x80;
        memset(dest+len+1, 0x00, n-len-1);
    }
    else {
        memcpy(dest, (uint8_t *)start, n);
    }
    return true;
}
/* ===========================================================================*/
/**
 * brief : 密钥监视
 * 
 * date  : 2012-10-31
 */
/* ---------------------------------------------------------------------------*/
static
void Key_Monitor(void) 
{
    switch(raKeyOperateInfo.state) {
        case ST_KEY_OPERATE_IDLE:
        {
            if (   raKeyOperateInfo.receive_flg != (uint32_t)0
                || raKeyOperateInfo.cnt != 0x00)
            {
                raKeyOperateInfo.receive_flg = (uint32_t)0;
                raKeyOperateInfo.cnt = 0x00;
                allmemput(ADDR_OF(EE_sect8, eeKeyOperateInfo), &raKeyOperateInfo, 
                          sizeof(struct KeyOperateInfo));
            }
        }
        break;
        case ST_KEY_OPERATE_RECEIVE_ING:
        {
            if (raKeyOperateInfo.cnt == raKeyOperateInfo.sum) {
                raKeyOperateInfo.state = ST_KEY_OPERATE_UPDATE_ING;
                raKeyOperateInfo.update_flg = (uint32_t)0;
                raKeyOperateInfo.cnt = 0x00;
                raKeyOperateInfo.last04000508 = ra04000508;
                allmemput(ADDR_OF(EE_sect8, eeKeyOperateInfo), &raKeyOperateInfo, 
                      sizeof(struct KeyOperateInfo));
            }
            else if (raKeyOperateInfo.cnt > raKeyOperateInfo.sum) {
                raKeyOperateInfo.state = ST_KEY_OPERATE_IDLE;
                allmemput(ADDR_OF(EE_sect8, eeKeyOperateInfo), &raKeyOperateInfo, 
                         sizeof(struct KeyOperateInfo));
            }
            if (!LicenseState_get(LS_REMOTE_AUTHORIZE)) {
                raKeyOperateInfo.state = ST_KEY_OPERATE_IDLE;
                allmemput(ADDR_OF(EE_sect8, eeKeyOperateInfo), &raKeyOperateInfo, 
                         sizeof(struct KeyOperateInfo));
            }
        }
        break;
        case ST_KEY_OPERATE_UPDATE_ING:
        {
            uint8_t i;
            uint32_t msk = (uint32_t)1;
            uint8_t a_ra04000508[4];

            for (i = 0; i < KN; i++, msk <<= 1) {
                if (POWER_DOWN() && POWER_DOWN() && POWER_DOWN()) {
                    break;
                }
                if (raKeyOperateInfo.cnt == raKeyOperateInfo.sum) {
                    raKeyOperateInfo.state = ST_KEY_OPERATE_UPDATE_END;
                    break;
                }
                D_ASSERT(raKeyOperateInfo.receive_flg != raKeyOperateInfo.update_flg);
                if (raKeyOperateInfo.receive_flg & msk) {
                    if (!(raKeyOperateInfo.update_flg & msk)) {
                        uint8_t j = 0;
                        struct KeyFile a_KeyFile;
                        uint8_t P2 = 0xFF;
                        
                        raKeyOperateInfo.cnt++;
                        /* 取密钥 */
                        for (j = 0; j < 3; j++) {
                            uint16_t a_crc;
                            allmemget(&a_KeyFile, ADDR_OF(EE_sect8, 
                                         eeKeyFile[i]), sizeof(struct KeyFile));
                            a_crc = crc16_ccitt(0xFFFF, &a_KeyFile, 
                                                 offsetof(struct KeyFile, crc));
                            if (a_KeyFile.crc == a_crc) {
                                break;                             // 退出取密钥
                            }
                        }
                        if (j >= 3) {
                            continue;
                        }
                        if (a_KeyFile.id != i) {
                            continue;  
                        }
                        if (a_KeyFile.type != raKeyOperateInfo.type) {
                            continue;
                        }
                
                        /* 更新到ESAM */
                        if (a_KeyFile.id == 0x00) {
                            P2 = 0x00;
                        }
                        if (TimeCOS_WriteKey(P2, 32, a_KeyFile.text) != 0x9000) {
                            continue;
                        }
                        
                        /* 一条密钥更新成功后处理 */
                        if (raKeyOperateInfo.type) {
                            ra04000508 |= ((uint32_t)1 << i);
                        }
                        else {
                            ra04000508 &= ~((uint32_t)1 << i);
                        }
                        raKeyOperateInfo.update_flg |= ((uint32_t)1 << i);
                    }
                }
            }
            allmemput(ADDR_OF(EE_sect8, eeKeyOperateInfo), &raKeyOperateInfo, 
                      sizeof(struct KeyOperateInfo));
            // 保存密钥状态字
            allmemput(ADDR_OF(EE_sect7, ee04000508), &ra04000508, 
                      sizeof(ra04000508));
            ReverseMem_Copy(a_ra04000508, (uint8_t *)&ra04000508, 4);
            TimeCOS_UpdateBin(IS_ESAM_IO, 0x00, 0x80|(0x1f&ESEF5), 
                      offsetof(struct S_ESEF5, es04000508), 4, a_ra04000508, 0);
        }
        break;
        case ST_KEY_OPERATE_UPDATE_END:
        {
            uint32_t a_flag = raKeyOperateInfo.update_flg 
                            ^ raKeyOperateInfo.receive_flg;
            /* 有密钥更新不成功 */
            if (a_flag) {
                if (a_flag & (~(uint32_t)1)) {           // 非主控密钥更新不成功
                    raKeyOperateInfo.state = ST_KEY_OPERATE_IDLE;
                }
                else {                                     // 主控密钥更新不成功
                    if (raKeyOperateInfo.type) {     // 主控密钥更新成私钥不成功
                        raKeyOperateInfo.state = ST_KEY_OPERATE_IDLE;
                    }
                    else {                           // 主控密钥更新成公钥不成功
                        ra04000508 &= ~(uint32_t)1;
                        allmemput(ADDR_OF(EE_sect7, ee04000508), &ra04000508, 1);
                        TimeCOS_UpdateBin(IS_ESAM_IO, 0x00, 0x80|(0x1f&ESEF5), 
                                  offsetof(struct S_ESEF5, es04000508), 4, 
                                  (uint8_t *)&ra04000508, 0);
                        a_flag &= ~(uint32_t)1;
                    }
                }
            }
            if (!a_flag) {
                /* 记录密钥更新记录 */
                uint8_t buf[5];
                buf[0] = raKeyOperateInfo.sum;
                memcpy(buf+1, &raKeyOperateInfo.last04000508, 4);
                EventRecord_fn03301201(raKeyOperateInfo.operateID, buf);
                raKeyOperateInfo.state = ST_KEY_OPERATE_IDLE;
            }
        }
        break;
        default:
        {
            raKeyOperateInfo.state = ST_KEY_OPERATE_IDLE;
        }
        break;
    }
}
/* ===========================================================================*/
/**
 * brief : ESAM第一次复位
 * 
 * date  : 2012-10-17
 *
 * return: 
 */
/* ---------------------------------------------------------------------------*/
static
bool Esam_FirstReset(void)
{
    // 复位ESAM
    if (!Reset_ESAM()) {
        return false;
    }
    // 更换过ESAM则不进行密钥更新
    if (arrcmp(ESAMSeriesNo, Buff_ICC+5, 8) != 0) {
        memcpy(ESAMSeriesNo, Buff_ICC+5, 8);         // 复位成功取ESAM序列号
        allmemput(ADDR_OF(EE_sect7, eeESAM_SiresNo), ESAMSeriesNo, 8);
        raKeyOperateInfo.state = ST_KEY_OPERATE_IDLE;
        allmemput(ADDR_OF(EE_sect8, eeKeyOperateInfo), &raKeyOperateInfo, 
                                                 sizeof(struct KeyOperateInfo));
    }
    // 从ESAM中获取表号
    if (TimeCOS_ReadBin(IS_ESAM_IO, 0x00, 0x80|(0x1f&ESEF2), 
                 offsetof(struct S_ESEF2, es04000402), 0x00, NULL, 6) != 0x9000)
    {
        return false;
    }
    else {
        uint8_t buf[6 + 1];
        uint8_t a_id[] = {REV4(0x04, 0x00, 0x04, 0x02)};
        ReverseMem_Copy(buf, Buff_ICC+1, 6);
        if (arrcmp(buf, ra04000402, 6) != 0) {
            DT_put(a_id, buf);
        }
    }
    // 从ESAM中获取密钥状态
    if (TimeCOS_ReadBin(IS_ESAM_IO, 0x00, 0x80|(0x1f&ESEF5), 
                 offsetof(struct S_ESEF5, es04000508), 0x00, NULL, 4) != 0x9000)
    {
        return false;
    }
    else {
        uint32_t a_ra04000508;
        ReverseMem_Copy((uint8_t *)&a_ra04000508, Buff_ICC+1, 4);
        if (ra04000508 != a_ra04000508) {
            ra04000508 = a_ra04000508;
            allmemput(ADDR_OF(EE_sect7, ee04000508), &a_ra04000508, sizeof(ra04000508));
        }
    }
#if defined(M_LOCAL)
    // 上电结账
    Money_SettleAccount_Timing(0, 1);
#endif        

    return true;
}
/* ===========================================================================*/
/**
 * brief : 远程读ESAM钱包文件, 读之前先扣款
 *         数据回抄, 状态查询, 身份认证命令失效时调用
 * 
 * date  : 2012-10-17
 *
 * return: 成功读取
 */
/* ---------------------------------------------------------------------------*/
static
bool LR_ReadEsamWalletFile_MAC(uint8_t *buf)
{
    uint8_t tempBuf[17] = {0x00, 0x00, 0x00, 0x00, 
                           0x04, 0xd6, 0x86, 0x00, 0x10, 
                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
#if defined(M_LOCAL)
    /* 结账 */
    Money_SettleAccount_Timing(15*60, 0);
#endif
    memcpy(tempBuf, masterStationRandom, 4);
    ReverseMem_Copy(tempBuf+11, ra04000402, 6);
    /* 读取钱包金额 */
    if (TimeCOS_ReadRcd(IS_ESAM_IO, 0x04, 0x01, (ESEF1<<3)|0x04, 
        4+5+8, tempBuf, 8) != 0x9000)
    {
        return false;
    }
    ReverseMem_Copy(buf,   Buff_ICC + 1, 4);                     // ESAM钱包金额
    ReverseMem_Copy(buf+4, Buff_ICC + 5, 4);                              // mac

    /* 读取购电次数 */
    if (TimeCOS_ReadRcd(IS_ESAM_IO, 0x04, 0x03, (ESEF1<<3)|0x04, 
        4+5+8, tempBuf, 8) != 0x9000) 
    {
        return false;
    }
    ReverseMem_Copy(buf+8,  Buff_ICC + 1, 4);                        // 购电次数
    ReverseMem_Copy(buf+12, Buff_ICC + 5, 4);                             // mac
    
    return true;
}




/* ===========================================================================*/
/**
 * brief : 远程控制98级解密
 * 
 * date  : 2012-10-17
 *
 * param : buf 输入密文, 输出明文
 * param : len 长度
 *
 * return: -1:解密失败; 0: 解密成功
 */
/* ---------------------------------------------------------------------------*/
int8_t decryption_LRC(uint8_t *buf, uint8_t len, enum ESF file, uint8_t plainTextLen)
{
    if (ra_longRangeForbid) {                                       //: 电表挂起
        return -1;
    }
    ReverseMem_Copy(Buff_ICC+5, buf, len);
    if (TimeCOS_UpdateBin(IS_ESAM_IO, 0x04, 0x80|(0x1f&file), 0x00, 
        len, Buff_ICC+5, 0) != 0x9000)
    {
        ++ra_timeCheckoutMAC;
        return -1;
    }

    if(TimeCOS_ReadBin(IS_ESAM_IO, 0x00, 0x80|(0x1f&file), 0x00, 
       0x00, NULL, plainTextLen) != 0x9000) 
    {
        return -1;
    }
    memcpy(buf, Buff_ICC + 1, plainTextLen);
    return 0;
}




/* ===========================================================================*/
/**
 * brief : 远程身份认证
 * 
 * date  : 2012-10-17
 *
 * param : id[4]
 * param : rx_buf 8密文1+ 8随机数1+ 8分散因子
 * param : rx_len
 * param : tx_buf
 * param : tx_len
 *
 * return: 
 */
/* ---------------------------------------------------------------------------*/
static
int8_t func070000FF(const uint8_t id[4], uint8_t *rx_buf, const uint8_t rx_len,
                    uint8_t *tx_buf, uint8_t *tx_len)
{                                                               //: 身份认证指令
    (void)rx_len;
    (void)id;

    if (arrcmp(rx_buf+16, ra04000402, 6) != 0) {
        Comm_serr = COMM_ERR_OTHERS;
        return -1;
    }
    ReverseMem_Copy(diffusionFactor, rx_buf+16, 8);                  // 分散因子
    ReverseMem_Copy(masterStationRandom, rx_buf+12, 4);  // 主站的随机数高四字节
    
    // a) 获取ESAM序列号
    if (!Reset_ESAM()) {
        Comm_serr = COMM_SERR_USER_FAILED;
        return -1;
    }
    memcpy(ESAMSeriesNo, Buff_ICC + 5, 8);

    // b) 用分散因子(表号)对ESAM密钥分散, 生成临时密钥
    Buff_ICC[5] = 0x00;
    Buff_ICC[6] = 0x00;
    ReverseMem_Copy(Buff_ICC+7, ra04000402, 6);
    if (TimeCOS_GenConLoad(0x00, 0x03, 8, Buff_ICC+5) != 0x9000) {
        Comm_serr = COMM_SERR_USER_FAILED;
        return -1;
    }

    // c) ESAM用临时密钥加密随机数, 得到加密结果K1
    arrswap(rx_buf+8, 8);
    if (TimeCOS_GenConLoad(0x00, 0x00, 8, rx_buf+8) != 0x9000) {
        Comm_serr = COMM_SERR_USER_FAILED;
        return -1;
    }
    
    // d) 比较上位机下发的密文K2与ESAM加密结果K1
    arrswap(rx_buf, 8);
    if (!A_Same_B(rx_buf, Buff_ICC + 1, 8)) {
        Comm_serr = COMM_SERR_USER_FAILED;
        return -1;
    }

    // e) 获取随机数2
    if (TimeCOS_GetChallenge(IS_ESAM_IO, 4) != 0x9000) {
        Comm_serr = COMM_SERR_USER_FAILED;
        return -1;
    }
    // e) 返回随机数2, ESAM序列号
    ReverseMem_Copy(tx_buf, Buff_ICC + 1, 4);
    ReverseMem_Copy(tx_buf + 4, ESAMSeriesNo, 8);
    *tx_len = 12;

    LicenseState_set(LS_REMOTE_AUTHORIZE, true);
    return 0;
}
/* ===========================================================================*/
/**
 * brief : 身份认证时效设置
 * 
 * date  : 2012-10-17
 *
 * param : id[4]
 * param : rx_buf
 * param : rx_len
 * param : tx_buf
 * param : tx_len
 *
 * return: -1: 设置失败; 0: 设置成功
 */
/* ---------------------------------------------------------------------------*/
static
int8_t func070001FF(const uint8_t id[4], uint8_t *rx_buf, const uint8_t rx_len,
                    uint8_t *tx_buf, uint8_t *tx_len)
{                                                          
    struct RX070001FF {
        uint8_t m07000101[2];
        uint8_t MAC[4];
    };
    struct RX070001FF *rx070001FF = (struct RX070001FF *)rx_buf;
    (void)id;
    (void)rx_len;
    (void)tx_len;
    (void)tx_buf;

    /* 身份认证时效合法性检查 */
    if (!is_valid_bcd(rx070001FF->m07000101, 2)) {                      
        Comm_serr = COMM_SERR_OTHERS;
        return -1;
    }
    if ((rx070001FF->m07000101[0] | rx070001FF->m07000101[1]) == 0x00) {
        Comm_serr = COMM_SERR_OTHERS;
        return -1;
    }
    
    /* 更新ESAM参数信息文件中的 身份认证时效 */
    arrswap(rx070001FF->m07000101, 2);
    arrswap(rx070001FF->MAC, 4);
    if (TimeCOS_UpdateBin(IS_ESAM_IO, 0x04, 0x80|(0x1f&ESEF2), 
        offsetof(struct S_ESEF2, es07000101), 2+4, rx070001FF->m07000101, 0)
        != 0x9000)
    {
        ++ra_timeCheckoutMAC;
        Comm_serr = COMM_SERR_ESAM_FAILED;
        return -1;
    }
    
    /* 更新RAM, EEPROM中的 身份认证时效 */
    arrswap(rx070001FF->m07000101, 2);
    memcpy(ra07000101, rx070001FF->m07000101, 2);
    allmemput(ADDR_OF(EE_sect2, ee07000101), &ra07000101, sizeof(ra07000101));
    memcpy(ra02800022, ra07000101, 2);
    return 0;
}
/* ===========================================================================*/
/**
 * brief : 身份认证失效
 * 
 * date  : 2012-10-17
 *
 * param : id[4]
 * param : rx_buf
 * param : rx_len
 * param : tx_buf
 * param : tx_len
 *
 * return: -1: 设置失败; 0: 设置成功
 */
/* ---------------------------------------------------------------------------*/
static
int8_t func070002FF(const uint8_t id[4], uint8_t *rx_buf, const uint8_t rx_len,
                    uint8_t *tx_buf, uint8_t *tx_len)
{
    struct TX070002FF {
        uint8_t m0400040E[6];                                    // 客户编号
        uint8_t purchaseMoney[4];                                // ESAM剩余金额
        uint8_t purchaseTimes[4];                                // ESAM购电次数
        uint8_t m04000508[4];                                    // 密钥状态
    };
    struct TX070002FF *tx070002FF = (struct TX070002FF*)tx_buf;
    (void)id;
    (void)rx_buf;
    (void)rx_len;
    
    // ESAM钱包金额+购电次数
#if defined(M_LOCAL)
    if(!LR_ReadEsamWalletFile_MAC(tx_buf+18)) {
        Comm_serr = COMM_SERR_OTHERS;
        return -1;
    }
    memcpy(tx070002FF->purchaseMoney, tx_buf+18, 4);
    memcpy(tx070002FF->purchaseTimes, tx_buf+18+8, 4);
#elif defined(M_REMOTE) || defined(M_SMART)
    memset(tx070002FF->purchaseMoney, 0x00, 4);
    memset(tx070002FF->purchaseTimes, 0x00, 4);
#endif
    if(TimeCOS_ReadBin(IS_ESAM_IO, 0x00, 0x80|(0x1f&ESEF2), 
                 offsetof(struct S_ESEF2, es0400040E), 0x00, NULL, 6) != 0x9000) 
    {
        Comm_serr = COMM_SERR_OTHERS;
        return -1;
    }
    ReverseMem_Copy(tx070002FF->m0400040E, Buff_ICC+1, 6);           // 客户编号

    if (TimeCOS_ReadBin(IS_ESAM_IO, 0x00, 0x80|(0x1f&ESEF5), 
                 offsetof(struct S_ESEF5, es04000508), 0x00, NULL, 4) != 0x9000)
    {
        Comm_serr = COMM_SERR_OTHERS;
        return -1;
    }
    ReverseMem_Copy(tx070002FF->m04000508, Buff_ICC+1, 4);           // 密钥状态

    *tx_len = sizeof(struct TX070002FF);
    LicenseState_set(LS_REMOTE_AUTHORIZE, false);
    return 0;
}


/* ===========================================================================*/
/**
 * brief : 红外认证指令
 * 
 * date  : 2012-10-17
 *
 * param : id[4]
 * param : rx_buf 8随机数2密文
 * param : rx_len
 * param : tx_buf
 * param : tx_len
 *
 * return: 
 */
/* ---------------------------------------------------------------------------*/
static
int8_t func070003FF(const uint8_t id[4], uint8_t *rx_buf, const uint8_t rx_len,
                    uint8_t *tx_buf, uint8_t *tx_len)
{                                                                   //: 红外认证
    (void)id;
    (void)rx_len;
    (void)tx_buf;
    (void)tx_len;

    /* 红外认证有效期内，如再次红外认证失败，结束上次红外认证通过状态，如再次红
       外认证通过，重新开始计时；红外认证有效期内掉电，重新上电应处于失效状态。
       停电唤醒状态下，进行红外认证，应返回错误信息SERR中的“其它错误”。*/
    LicenseState_set(LS_IR_AUTHORIZE, false);
    if (!Ir_Authorize_ask) {
        Comm_serr = COMM_SERR_OTHERS;
        return -1;
    }
    arrswap(rx_buf, 8);
    if (TimeCOS_ExternalLoad(IS_ESAM_IO, 0x08, 8, rx_buf) != 0x9000) {
        Comm_serr = COMM_SERR_ESAM_FAILED;
        return -1;
    }
    LicenseState_set(LS_IR_AUTHORIZE, true);
    return 0;
}
/* ===========================================================================*/
/**
 * brief : 明文写信息文件
 * 
 * date  : 2012-10-17
 *
 * param : id[4]
 * param : rx_buf
 * param : rx_len
 * param : tx_buf
 * param : tx_len
 *
 * return: 
 */
/* ---------------------------------------------------------------------------*/
static
int8_t func070004FF(const uint8_t id[4], uint8_t *rx_buf, const uint8_t rx_len,
                    uint8_t *tx_buf, uint8_t *tx_len)
{                                                             //: 明文写信息文件
    uint16_t sw_sum;
    uint16_t id_File;
    uint8_t P1, P2;
    uint8_t len_File;
    (void)id;
    (void)tx_buf;
    (void)tx_len;

    id_File = (uint16_t)rx_buf[0];                                   // 文件编号
    // 明文写信息文件仅18、1A、1B、1C
    if (   id_File != 0x0018 && id_File != 0x001A && id_File != 0x001B 
        && id_File != 0x001C) 
    {
        Comm_serr = COMM_SERR_OTHERS;
        return -1;
    }
    arrswap(&id_File, 2);
    sw_sum = TimeCOS_SelectFile(IS_ESAM_IO, 2, (uint8_t *)&id_File); 
    if (sw_sum != 0x9000) {
        Comm_serr = COMM_SERR_ESAM_FAILED;
        return -1;
    }
    len_File = rx_len - 4/*DI0~3*/ - 4/*C0~3*/ - 1/*id_file*/ - 2/*ofs_file*/ - 4/*mac*/;
    P1 = rx_buf[2];                                                  // 偏移地址
    P2 = rx_buf[1];      
    D_ASSERT(!g_buf_locked);
    g_buf_locked = true;
    ReverseMem_Copy(g_buf, rx_buf+1+2, len_File);                        // 明文
    ReverseMem_Copy(g_buf+len_File, rx_buf+1+2+len_File, 4);              // MAC 
    sw_sum = TimeCOS_UpdateBin(IS_ESAM_IO, 0x04, P1, P2, 
                               len_File+4, g_buf, 0x00);
    g_buf_locked = false;
    if (sw_sum != 0x9000) {
        ++ra_timeCheckoutMAC;
        Comm_serr = COMM_SERR_ESAM_FAILED;
        return -1;
    }
    return 0;
}
/* ===========================================================================*/
/**
 * brief : 密文写信息文件
 * 
 * date  : 2012-10-17
 *
 * param : id[4]
 * param : rx_buf 1文件编号 + 2偏移地址 + L密文 + 4MAC
 * param : rx_len (645帧的数据域长度(4id + 4操作者 + L数据))
 * param : tx_buf
 * param : tx_len
 *
 * return: 
 */
/* ---------------------------------------------------------------------------*/
static
int8_t func070005FF(const uint8_t id[4], uint8_t *rx_buf, const uint8_t rx_len,
                    uint8_t *tx_buf, uint8_t *tx_len)
{                                                             //: 密文写信息文件
    uint16_t sw_sum;
    uint16_t id_File;
    uint8_t P1, P2;
    uint8_t len_File;
    (void)id;
    (void)tx_buf;
    (void)tx_len;

    id_File = (uint16_t)rx_buf[0];                                   // 文件编号
    // 密文写信息文件仅15、0B
    if (   id_File != 0x0015 && id_File != 0x000B) 
    {
        Comm_serr = COMM_SERR_OTHERS;
        return -1;
    }
    arrswap(&id_File, 2);
    sw_sum = TimeCOS_SelectFile(IS_ESAM_IO, 2, (uint8_t *)&id_File); 
    if (sw_sum != 0x9000) {
        Comm_serr = COMM_SERR_ESAM_FAILED;
        return -1;
    }
    len_File = rx_len - 4/*DI0~3*/ - 4/*C0~3*/ - 1/*id_file*/ - 2/*ofs_file*/ - 4/*mac*/;
    P1 = rx_buf[2];                                                  // 偏移地址
    P2 = rx_buf[1];      
    D_ASSERT(!g_buf_locked);
    g_buf_locked = true;
    ReverseMem_Copy(g_buf, rx_buf+1+2, len_File);                      // 密文
    ReverseMem_Copy(g_buf+len_File, rx_buf+1+2+len_File, 4);            // MAC 
    sw_sum = TimeCOS_UpdateBin(IS_ESAM_IO, 0x04, P1, P2, 
                               len_File+4, g_buf, 0x00);
    g_buf_locked = false;
    if (sw_sum != 0x9000) {
        ++ra_timeCheckoutMAC;
        Comm_serr = COMM_SERR_ESAM_FAILED;
        return -1;
    }
    return 0;
}

#if defined(M_LOCAL)
/* ===========================================================================*/
/**
 * brief : 远程开户
 * 
 * date  : 2012-10-17
 *
 * param : id[4]
 * param : rx_buf 4购电金额 + 4购电次数 + 4MAC1 + 6客户编号 + 4MAC2
 * param : rx_len
 * param : tx_buf
 * param : tx_len
 *
 * return: 
 */
/* ---------------------------------------------------------------------------*/
static
int8_t func070101FF(const uint8_t id[4], uint8_t *rx_buf, const uint8_t rx_len,
                    uint8_t *tx_buf, uint8_t *tx_len)
{                                                                       //: 开户
    struct RX070101FF {
        uint8_t purchaseMoney[4];
        uint8_t purchaseTimes[4];
        uint8_t MAC1[4];
        uint8_t m0400040E[6];
        uint8_t MAC2[4];
    };
    struct RX070101FF *rx070101FF = (struct RX070101FF *)rx_buf;
    uint32_t LData;
    uint32_t c_PurchaseTimes;                            // 通讯上下发的购电次数
    uint32_t m_PurchaseTimes;                                    // 表的购电次数
    uint8_t a_id[4] = {REV4(0x04, 0x00, 0x04, 0x0E)};
    (void)id;
    (void)rx_len;
    (void)tx_buf;
    (void)tx_len;
    
    /** 提取数据 **/
    LData = Array2Long(rx070101FF->purchaseMoney, 4);
    DEC2BCD(LData, RL1NgttrMoney_Dtr, 4);
    c_PurchaseTimes = Array2Long(rx070101FF->purchaseTimes, 4);
    m_PurchaseTimes = bcd2uint(RBuyCnt_Dtr, 4);
    
    /** 条件判断 **/
    // b) 判断是否已开户
    if (OpenAccountFlag != 0x55) {
        // c) 判断客户编号是否一致
        if(!A_Same_B(ra0400040E, rx070101FF->m0400040E, 6)) {
            Comm_serr = COMM_SERR_CUSTOM_NUM;
            return -1;
        }
    }

    // 验证客户编号合法性
    if (!is_valid_bcd(rx070101FF->m0400040E, 6)) {
        Comm_serr = COMM_SERR_CUSTOM_NUM;
        return -1;
    }
    // 验证MAC2正确性
    arrswap(rx070101FF->m0400040E, 6);
    arrswap(rx070101FF->MAC2, 4);
    if (TimeCOS_UpdateBin(IS_ESAM_IO, 0x04, 0x80|(0x1f&ESEF2), 0x24, 10, 
        rx070101FF->m0400040E, 0) != 0x9000)
    {
        ++ra_timeCheckoutMAC;
        Comm_serr = COMM_SERR_ESAM_FAILED;
        return -1;
    }

    // d) 判断购电次数是否为1,或0
    if (c_PurchaseTimes != (uint32_t)1 && c_PurchaseTimes != (uint32_t)0) {
        Comm_serr = COMM_SERR_BUY_TIMES;
        return -1;
    }

    /* 动作执行 */
    // e) 比较命令的购电次数与表内购电次数
    if (c_PurchaseTimes == m_PurchaseTimes) {}
    else if (c_PurchaseTimes == m_PurchaseTimes + 1) {
        uint8_t temp;
        // f) g) 充值
        if (ra_longRangeForbid) {
            Comm_serr = COMM_SERR_METER_SUSPEND;
            return -1;
        }
        arrswap(rx070101FF->purchaseMoney, 4);
        arrswap(rx070101FF->purchaseTimes, 4);
        arrswap(rx070101FF->MAC1, 4);
        temp = Money_Recharge(rx070101FF->purchaseMoney);
        switch(temp){
            case MSG_OK:
                break;
            case MSG_MAC_ERR:
                ++ra_timeCheckoutMAC;
                Comm_serr = COMM_SERR_ESAM_FAILED;
                return -1;
            case MSG_MENOY_OVER_LIMIT_FAIL:
                Comm_serr = COMM_SERR_REMAIN_LIMTD;
                return -1;
            default :
                Comm_serr = COMM_SERR_OTHERS;
                return -1;
        }
    }
    else {
        Comm_serr = COMM_SERR_BUY_TIMES;
        return -1;
    }
      
    // h) 保存客户编号 置远程开户标志
    arrswap(rx070101FF->m0400040E, 6);
    DT_put(a_id, rx070101FF->m0400040E);
    OpenAccountFlag &= 0x0F;
    allmemput(ADDR_OF(EE_sect6, eeOpenAccountFlag), &OpenAccountFlag, 1);
    ra04000501[2] &= ~ST3_REMOTE_OPEN_ACCOUNT;
    
    return 0;
}

/* ===========================================================================*/
/**
 * brief : 远程充值
 * 
 * date  : 2012-10-17
 *
 * param : id[4]
 * param : rx_buf
 * param : rx_len
 * param : tx_buf
 * param : tx_len
 *
 * return: 
 */
/* ---------------------------------------------------------------------------*/
static
int8_t func070102FF(const uint8_t id[4], uint8_t *rx_buf, const uint8_t rx_len,
                    uint8_t *tx_buf, uint8_t *tx_len)
{                                                                     
    struct RX070102FF {
        uint8_t purchaseMoney[4];
        uint8_t purchaseTimes[4];
        uint8_t MAC1[4];
        uint8_t m0400040E[6];
        uint8_t MAC2[4];
    };
    struct RX070102FF *rx070102FF = (struct RX070102FF *)rx_buf;
    uint32_t LData;
    uint32_t c_PurchaseTimes;                            // 通讯上下发的购电次数
    uint32_t m_PurchaseTimes;                                    // 表的购电次数
    (void)id;
    (void)rx_len;
    (void)tx_buf;
    (void)tx_len;

    /** 提取数据 **/
    LData = Array2Long(rx070102FF->purchaseMoney, 4);
    DEC2BCD(LData, RL1NgttrMoney_Dtr, 4);
    c_PurchaseTimes = Array2Long(rx070102FF->purchaseTimes, 4);
    m_PurchaseTimes = bcd2uint(RBuyCnt_Dtr, 4);

    /* 条件判断 */
    // b) 判断是否已开户
    if (OpenAccountFlag == 0x55) {                           // 远程本地都未开户
        Comm_serr = COMM_SERR_BUY_TIMES;
        return -1;
    }

    // c) 判断客户编号是否 一致
    if(!A_Same_B(ra0400040E, rx070102FF->m0400040E, 6)) {
        Comm_serr = COMM_SERR_CUSTOM_NUM;
        return -1;
    }

    // 验证MAC2正确性
    arrswap(rx070102FF->m0400040E, 6);
    arrswap(rx070102FF->MAC2, 4);
    if (TimeCOS_UpdateBin(IS_ESAM_IO, 0x04, 0x80|(0x1f&ESEF2), 0x24, 10, 
        rx070102FF->m0400040E, 0) != 0x9000)
    {
        ++ra_timeCheckoutMAC;
        Comm_serr = COMM_SERR_ESAM_FAILED;
        return -1;
    }

    /* 动作执行 */
    // d) 比较命令的购电次数与表内购电次数
    if (c_PurchaseTimes == m_PurchaseTimes) {
        Comm_serr = COMM_SERR_RECHARGE;
        return -1;
    }
    else if (c_PurchaseTimes == m_PurchaseTimes + 1) {
        uint8_t temp;
        // f) g) 充值
        if (ra_longRangeForbid) {
            Comm_serr = COMM_SERR_METER_SUSPEND;
            return -1;
        }
        arrswap(rx070102FF->purchaseMoney, 4);
        arrswap(rx070102FF->purchaseTimes, 4);
        arrswap(rx070102FF->MAC1, 4);
        temp = Money_Recharge(rx070102FF->purchaseMoney);
        switch(temp){
            case MSG_OK:
                break;
            case MSG_MAC_ERR:
                ++ra_timeCheckoutMAC;
                Comm_serr = COMM_SERR_ESAM_FAILED;
                return -1;
            case MSG_MENOY_OVER_LIMIT_FAIL:
                Comm_serr = COMM_SERR_REMAIN_LIMTD;
                return -1;
            default :
                Comm_serr = COMM_SERR_OTHERS;
                return -1;
        }
    }
    else {
        Comm_serr = COMM_SERR_BUY_TIMES;
        return -1;
    }
    return 0;
}

/* ===========================================================================*/
/**
 * brief : 钱包初始化命令
 *         1: 提取数据: 预置金额
 *         2: 检查数据合法性: 购电次数必须为0;
 *         3: ESAM操作: 预置ESAM购电金额; 清ESAM购电次数.
 *         4: 刷新电表数据
 *         5: 保存购电记录
 * 
 * date  : 2012-10-17
 *
 * param : id[4]
 * param : rx_buf
 * param : rx_len
 * param : tx_buf
 * param : tx_len
 *
 * return: 
 */
/* ---------------------------------------------------------------------------*/
static
int8_t func070103FF(const uint8_t id[4], uint8_t *rx_buf, const uint8_t rx_len,
                    uint8_t *tx_buf, uint8_t *tx_len)         //: 钱包初始化命令
{
    struct RX070103FF {
        uint8_t purchaseMoney[4];
        uint8_t MAC1[4];        
        uint8_t purchaseTimes[4];
        uint8_t MAC2[4];
    };
    struct RX070103FF *rx070103FF = (struct RX070103FF *)rx_buf;
    uint8_t temp;
    (void)id;
    (void)rx_buf;
    (void)rx_len;
    (void)tx_buf;
    (void)tx_len;

    if (ra_longRangeForbid) {
        Comm_serr = COMM_SERR_METER_SUSPEND;
        return -1;
    }
    arrswap(rx070103FF->purchaseMoney, 4); 
    arrswap(rx070103FF->MAC1, 4);
    arrswap(rx070103FF->purchaseTimes, 4);
    arrswap(rx070103FF->MAC2, 4);
    temp = Money_InitAccount(rx070103FF->purchaseMoney);
    switch (temp) {
        case MSG_OK:
            break;
        case MSG_MENOY_OVER_LIMIT_FAIL:
            Comm_serr = COMM_SERR_REMAIN_LIMTD;
            return -1;
        case MSG_BUY_TIMES_FAIL:
            Comm_serr = COMM_SERR_BUY_TIMES;
            return -1;
        case MSG_MAC_ERR:
            ++ra_timeCheckoutMAC;
            Comm_serr = COMM_SERR_ESAM_FAILED;
            return -1;
        default:
            Comm_serr = COMM_SERR_OTHERS;
            return -1;
    }
    // 刷新ESAM运行信息文件
    Update_EsamRuningFile();
    // 清零记录与清零标志在Comm.c里完成
    return 0;
}


#endif


/* ===========================================================================*/
/**
 * brief : 密钥更新命令
 * 
 * date  : 2012-10-17
 *
 * param : id[4]
 * param : rx_buf
 * param : rx_len
 * param : tx_buf
 * param : tx_len
 *
 * return: 
 */
/* ---------------------------------------------------------------------------*/
static
int8_t  func070301FF(const uint8_t id[4], uint8_t *rx_buf, const uint8_t rx_len,
                    uint8_t *tx_buf, uint8_t *tx_len)
{
    struct KeyFile a_KeyFile;
    uint8_t n;
    uint8_t *buf;
    uint8_t i;
    (void)id;
    (void)tx_buf;
    (void)tx_len;
    
    // 不处于接收密钥状态,不予接收新的密钥
    if (   (raKeyOperateInfo.state != ST_KEY_OPERATE_IDLE)
        && (raKeyOperateInfo.state != ST_KEY_OPERATE_RECEIVE_ING))
    {
        Comm_serr =  COMM_SERR_OTHERS;
        return -1;
    }
    /* 分析数据包有多少条密钥, 数据长度是否正确 */
    n = (rx_len-4/*id0~id3*/-4/*c0~c3*/-4/*mac*/) / 36;
    if ((n > 4) || (n*36 != rx_len-4/*id0~id3*/-4/*c0~c3*/-4/*mac*/)) {
        Comm_serr = COMM_SERR_OTHERS;
        return -1;
    }
    
    buf = Buff_ICC+5;
    /*异或处理 */
    memcpy(buf+8, rx_buf, 36);
    for (i = 1; i < n; i++) {
        uint8_t j;
        for (j = 0; j < 36; j++) {
            buf[8+j] ^=rx_buf[i*36 + j];
        }
    }
    /* 送ESAM验证 */
    buf[0] = 0x00;
    buf[1] = 0x00;
    ReverseMem_Copy(buf+2, ra04000402, 6);                               // 表号
    arrswap(buf+2+6, 36);                                            // 异或数据
    ReverseMem_Copy(buf+2+6+36, rx_buf+n*36, 4);                          // MAC
    if (TimeCOS_UpdateBin(IS_ESAM_IO, 0x04, 0x80|(0x1f&ESEF16), 0x00,
        0x30, buf, 0x00) != 0x9000) 
    {
        ++ra_timeCheckoutMAC;
        Comm_serr = COMM_SERR_ESAM_FAILED;
        return -1;
    }
    
    /* 内容分析*/
    for (i = 0; i < n; i++) {
        struct CommKeyFile * pCommKeyFile = (struct CommKeyFile *)(rx_buf+i*36);
        /* 645数据颠倒 */
        arrswap((uint8_t *)pCommKeyFile, 36);
        if (raKeyOperateInfo.state == ST_KEY_OPERATE_IDLE) {
            if (   (pCommKeyFile->sum != ra04000208) 
                || (pCommKeyFile->id  >= ra04000208)) 
            {
                Comm_serr = COMM_SERR_OTHERS;
                break;
            }
            raKeyOperateInfo.state = ST_KEY_OPERATE_RECEIVE_ING;
            /* 确定本次操作密钥的密钥总条数, 密钥状态标志 */
            raKeyOperateInfo.sum = pCommKeyFile->sum;                
            raKeyOperateInfo.type = pCommKeyFile->type;
        }
        else if (raKeyOperateInfo.state == ST_KEY_OPERATE_RECEIVE_ING) {
            /* 核对接收的密钥总条数, 密钥状态标志是否一致 */
            if (   (raKeyOperateInfo.sum != pCommKeyFile->sum)              
                || (raKeyOperateInfo.type != pCommKeyFile->type))
            {
                Comm_serr = COMM_SERR_OTHERS;
                break;
            }
        }
        /* 缓存密钥 */
        a_KeyFile.id = pCommKeyFile->id;
        a_KeyFile.type = pCommKeyFile->type;
        memcpy(a_KeyFile.text, pCommKeyFile->text, sizeof(a_KeyFile.text));
        a_KeyFile.crc = crc16_ccitt(0xFFFF, &a_KeyFile, 
                                    offsetof(struct KeyFile, crc));
        allmemput(ADDR_OF(EE_sect8, eeKeyFile[a_KeyFile.id]), &a_KeyFile, 
                  sizeof(struct KeyFile));

        /* 当前编号已接收标志置起 */
        if (!(raKeyOperateInfo.receive_flg & (uint32_t)1 << a_KeyFile.id)) {
              raKeyOperateInfo.receive_flg |= ((uint32_t)1 << a_KeyFile.id);
              raKeyOperateInfo.cnt++;
        }
    }
    if (Comm_serr != (uint16_t)0) {
        raKeyOperateInfo.state = ST_KEY_OPERATE_IDLE;
    }
    allmemput(ADDR_OF(EE_sect8, eeKeyOperateInfo), &raKeyOperateInfo, 
              sizeof(struct KeyOperateInfo));
    if (Comm_serr != (uint16_t)0) {
        return -1;
    }
    return 0;
}




/* ===========================================================================*/
/**
 * brief : 远程数据回抄
 * 
 * date  : 2012-10-17
 *
 * param : id[4]
 * param : rx_buf 8数据回抄标识
 * param : rx_len
 * param : tx_buf 8数据回抄标识 + Ld回抄的数据 + 4MAC
 * param : tx_len
 *
 * return: 
 * NOTE 8数据回抄标识
 * 第7-6字节 目录标识
 * 第5-4字节 文件标识
 * 第3-2字节 读取数据的相对起始地址
 * 第1-0字节 要读取的数据长度
 */
/* ---------------------------------------------------------------------------*/
static
int8_t func078001FF(const uint8_t id[4], uint8_t *rx_buf, const uint8_t rx_len,
                    uint8_t *tx_buf, uint8_t *tx_len)
{
    uint8_t Ld = rx_buf[0];                                          // 数据长度
    uint8_t P2 = rx_buf[2];                                        // 文件偏移量
    uint8_t P1 = rx_buf[4];                                          // 文件标识
    uint16_t sw_sum;

    (void)id;
    (void)rx_len;
    
    if (Ld > (uint16_t)COMM_TX_PAYLOAD) {
        Comm_serr = COMM_SERR_OTHERS;
        return -1;
    }
    memcpy(tx_buf, rx_buf, 8);
    /* 读ESAM钱包文件 */
    if (ESEF1 == P1) {
        if(!LR_ReadEsamWalletFile_MAC(tx_buf+8)) {
            Comm_serr = COMM_SERR_OTHERS;
            return -1;
        }
        tx_len[0] = 8/*数据回抄标识*/ 
                  + 4/*剩余金额*/ + 4/*MAC*/ + 4/*购电次数*/ + 4/*MAC*/;
        return 0;
    }
    /* 读ESAM其他文件 */
    memcpy(Buff_ICC+5, masterStationRandom, 4);
    Buff_ICC[9]  = 0x04;
    Buff_ICC[10] = 0xd6;
    Buff_ICC[11] = 0x86;
    Buff_ICC[12] = P2;
    Buff_ICC[13] = Ld+12;
    Buff_ICC[14] = 0x00;
    Buff_ICC[15] = 0x00;
    ReverseMem_Copy(Buff_ICC+16, ra04000402, 6);         // 使用表号作为分散因子
    sw_sum = TimeCOS_ReadBin(IS_ESAM_IO, 0x04, P1|0x80, P2, 
                                   4/*rand*/+5+8/*分散因子*/, Buff_ICC+5, Ld+4);
    if(sw_sum == 0x9000 || ((uint8_t)(sw_sum>>8) == 0x61)) {
        ReverseMem_Copy(tx_buf+8,    Buff_ICC+1,    Ld);
        ReverseMem_Copy(tx_buf+8+Ld, Buff_ICC+1+Ld, 4);
        tx_len[0] = 8/*数据回抄标识*/ + Ld/*回抄数据长度*/ + 4/*MAC*/;
        return 0;
    }
    else {
        Comm_serr = COMM_SERR_OTHERS;
        return -1;
    }
}

/* ===========================================================================*/
/**
 * brief : 软件比对
 * 
 * date  : 2012-10-17
 *
 * param : id[4]
 * param : rx_buf
 * param : rx_len
 * param : tx_buf
 * param : tx_len
 *
 * return: 
 */
/* ---------------------------------------------------------------------------*/
static
int8_t func078002FF(const uint8_t id[4], uint8_t *rx_buf, const uint8_t rx_len,
                    uint8_t *tx_buf, uint8_t *tx_len)
{  
    uint8_t CPU_num = *rx_buf;                                        // CPU编号
    uint8_t KeyIndex = *(rx_buf + 1);                                // 密钥索引
    uint32_t FactorAddr;                                     // 比对因子起始地址
    uint32_t DataAddr;                                       // 比对数据起始地址
    uint8_t i;
    uint8_t Factor[8];

    (void)id;
    (void)rx_len;
    FactorAddr = ( ((uint32_t)rx_buf[5] << 24) 
                 + ((uint32_t)rx_buf[4] << 16) 
                 + ((uint32_t)rx_buf[3] <<  8)
                 + ((uint32_t)rx_buf[2] <<  0));
    DataAddr   = ( ((uint32_t)rx_buf[9] << 24) 
                 + ((uint32_t)rx_buf[8] << 16) 
                 + ((uint32_t)rx_buf[7] <<  8)
                 + ((uint32_t)rx_buf[6] <<  0));
    
    /* 
     * 合法性判断
     */
    if (CPU_num >= 8) {
        Comm_serr = COMM_SERR_OTHERS;
        return -1;
    }

    D_ASSERT(!g_buf_locked);
    g_buf_locked = true;
    /* 1)提取比对因子 */
    if (!Program_get(g_buf, FactorAddr, 16)) {
        g_buf_locked = false;
        Comm_serr = COMM_SERR_ADDR_ABNORMAL;
        return -1;
    }
    for (i = 0; i < 8; i++) {
        Factor[i] = g_buf[i] ^ g_buf[i+8];
    }
    /* 2)使用比对因子计算比对因子密钥*/
    if (TimeCOS_GenConLoad(0x00, KeyIndex, 8, Factor) != 0x9000) {
        g_buf_locked = false;
        Comm_serr = COMM_SERR_OTHERS;
        return -1;
    }
    /* 3)提取待加密数据 */
    if (!Program_get(g_buf, DataAddr, 256)) {
        g_buf_locked = false;
        Comm_serr = COMM_SERR_ADDR_ABNORMAL;
        return -1;
    }
    for (i = 0; i < 64; i++) {
        g_buf[i] = g_buf[i+0*64] ^ g_buf[i+1*64] ^ g_buf[i+2*64] ^ g_buf[i+3*64];
    }
    /* 4)用比对因子密钥对待加密数据进行加密 */      
    if (TimeCOS_GenConLoad(0x01, 0x00, 64, g_buf) != 0x9000) {
        g_buf_locked = false;
        Comm_serr = COMM_SERR_OTHERS;
        return -1;
    }
    ReverseMem_Copy(tx_buf, Buff_ICC+1, 64);
    
    *tx_len = 64;
    g_buf_locked = false;
    return 0;
}

/* ===========================================================================*/
/**
 * brief : 红外认证请求
 * 
 * date  : 2012-10-17
 *
 * param : id[4]
 * param : rx_buf 8随机数1
 * param : rx_len
 * param : tx_buf 6表号+8ESAM序列号+8随机数1密文+8随机数2
 * param : tx_len 30
 *
 * return: 
 */
/* ---------------------------------------------------------------------------*/
static
int8_t func078003FF(const uint8_t id[4], uint8_t *rx_buf, const uint8_t rx_len,
                    uint8_t *tx_buf, uint8_t *tx_len)
{
    struct TX078003FF {
        uint8_t m04000402[6];
        uint8_t EasmSeriesNo[8];
        uint8_t rand1[8];
        uint8_t rand2[8];
    };
    struct TX078003FF *tx078003FF = (struct TX078003FF *)tx_buf;
    (void)id;
    (void)rx_len;

    
    /* 复位ESAM */
    if (!Reset_ESAM()) {
        Comm_serr = COMM_SERR_OTHERS;
        return -1;
    }
    
    memcpy(ESAMSeriesNo, Buff_ICC + 5, 8);
    // 用0000+表号作为分散因子. 
    Buff_ICC[5] = 0x00;
    Buff_ICC[6] = 0x00;
    ReverseMem_Copy(Buff_ICC+7, ra04000402, 6);
    /* ESAM密钥分散命令, 生成临时密钥 */
    if (TimeCOS_GenConLoad(0x00, 0x03, 8, Buff_ICC+5) != 0x9000) {
        Comm_serr = COMM_SERR_OTHERS;
        return -1;
    }
    /* ESAM用临时密钥加密随机数, 得到加密结果K1 */
    arrswap(rx_buf, 8);
    if (TimeCOS_GenConLoad(0x00, 0x00, 8, rx_buf) != 0x9000) {
        Comm_serr = COMM_SERR_OTHERS;
        return -1;
    }
    ReverseMem_Copy(tx078003FF->rand1, Buff_ICC+1, 8);            // 随机数1密文
    
    /* 获取随机数2 */
    if (TimeCOS_GetChallenge(IS_ESAM_IO, 8) != 0x9000) {
        Comm_serr = COMM_SERR_OTHERS;
        return -1;
    }
                                                      
    memcpy(tx078003FF->m04000402, ra04000402, 6);                        // 表号
    ReverseMem_Copy(tx078003FF->EasmSeriesNo, ESAMSeriesNo, 8);    // esam序列号
    ReverseMem_Copy(tx078003FF->rand2, Buff_ICC+1, 8);                // 随机数2
    *tx_len = sizeof(struct TX078003FF);

    LicenseState_set(LS_REMOTE_AUTHORIZE, false);
    Ir_Authorize_ask = true;
    return 0;
}

/* ===========================================================================*/
/**
 * brief : 查询状态
 * 
 * date  : 2012-10-17
 *
 * param : id[4]
 * param : rx_buf
 * param : rx_len
 * param : tx_buf
 * param : tx_len
 *
 * return: 
 */
/* ---------------------------------------------------------------------------*/
static
int8_t func078102FF(const uint8_t id[4], uint8_t *rx_buf, const uint8_t rx_len,
                    uint8_t *tx_buf, uint8_t *tx_len)
{
    (void)id;
    (void)rx_buf;
    (void)rx_len;
    

    if(!LR_ReadEsamWalletFile_MAC(tx_buf)) {
        Comm_serr = COMM_SERR_OTHERS;
        return -1;
    }   
    if(TimeCOS_ReadBin(IS_ESAM_IO, 0x00, 0x80|(0x1f&ESEF2), 
                 offsetof(struct S_ESEF2, es0400040E), 0x00, NULL, 6) != 0x9000) 
    {
        Comm_serr = COMM_SERR_OTHERS;
        return -1;
    }
    ReverseMem_Copy(tx_buf+16, Buff_ICC+1, 6);                       // 客户编号

    if (TimeCOS_ReadBin(IS_ESAM_IO, 0x00, 0x80|(0x1f&ESEF5), 
                 offsetof(struct S_ESEF5, es04000508), 0x00, NULL, 4) != 0x9000)
    {
        Comm_serr = COMM_SERR_OTHERS;
        return -1;
    }
    ReverseMem_Copy(tx_buf+22, Buff_ICC+1, 4);                       // 密钥状态

    tx_len[0] = 4+4+4+4+6+4;
    return 0;
}



/* ===========================================================================*/
/**
 * brief : 安全认证
 * 
 * date  : 2012-10-17
 *
 * param : tx_len 645协议返回帧 数据长度
 *
 * return: 返回Comm_Retval枚举类型值.
 */
/* ---------------------------------------------------------------------------*/
int8_t LR_certificationProc(uint8_t *tx_len)
{
    const uint8_t *id = Comm_rxBuf + COMM_FRAME_OFS_DATA;
    const uint8_t rx_len = Comm_rxBuf[COMM_FRAME_OFS_L];
    uint8_t *rx_buf = Comm_rxBuf + COMM_FRAME_OFS_DATA + 4/*DI0~3*/ + 4/*C0~3*/;
    uint8_t *tx_buf = Comm_txBuf[Comm_chnl] + COMM_FRAME_OFS_DATA + 4/*DI0~3*/;
    uint8_t operatorID[4];
    uint32_t a_id;
    int8_t retvalue = COMM_RETVAL_OK;

    if (Comm_chnl == 0 && !IR_Special_Id_Check()) {
        Comm_serr = COMM_ERR_OTHERS;
        return COMM_RETVAL_ERROR;
    }
    KICK_DOG();
    memcpy(operatorID, Comm_rxBuf + COMM_FRAME_OFS_DATA + 4/*DI0~3*/, 4);
    a_id =   ((uint32_t)id[3] << 24) + ((uint32_t)id[2] << 16)
           + ((uint32_t)id[1] <<  8) + id[0];

    /* 
     * 判断是否处于认证通过状态
     * 身份认证指令与红外认证不需要判断
     */
    if (!LicenseState_get(LS_REMOTE_AUTHORIZE)) {
        if(   a_id == 0x070001FF || a_id == 0x070002FF || a_id == 0x070004FF
           || a_id == 0x070005FF 
#if defined(M_LOCAL)
           || a_id == 0x070101FF || a_id == 0x070102FF || a_id == 0x070103FF
#endif
           || a_id == 0x070301FF || a_id == 0x078001FF || a_id == 0x078002FF
           || a_id == 0x078102FF)
        {
            Comm_serr = COMM_SERR_USER_FAILED;
            return COMM_RETVAL_ERROR;
        }
    }

    switch (a_id) {
        case 0x070000FF: {                                       // 身份认证指令
            if (func070000FF(id, rx_buf, rx_len, tx_buf, tx_len)) {
                D_ASSERT(Comm_serr != 0x00);
                retvalue = COMM_RETVAL_ERROR;
            }
        }
        break;
        case 0x070001FF: {                                   // 身份认证时效设置
            if (func070001FF(id, rx_buf, rx_len, tx_buf, tx_len)) {
                D_ASSERT(Comm_serr != 0x00);
                retvalue = COMM_RETVAL_ERROR;
            }
            else {
                EventRecord_fn033000ZZ(operatorID, id);
            }
        }
        break;
        case 0x070002FF: {                                       // 身份认证失效
            if (func070002FF(id, rx_buf, rx_len, tx_buf, tx_len)) {
                D_ASSERT(Comm_serr != 0x00);
                retvalue = COMM_RETVAL_ERROR;
            }
        }
        break;
        case 0x070003FF: {                                           // 红外认证
            if (Comm_chnl != 0) {
                Comm_serr = COMM_SERR_OTHERS;
                retvalue = COMM_RETVAL_ERROR;
            }
            if (g_opMode == OP_MODE_WAKEUP) {
                Comm_serr = COMM_SERR_OTHERS;
                retvalue = COMM_RETVAL_ERROR;
            }
            if (func070003FF(id, rx_buf, rx_len, tx_buf, tx_len)) {
                D_ASSERT(Comm_serr != 0x00);
                retvalue = COMM_RETVAL_ERROR;
            }
        }
        break;
        case 0x070004FF: {                                     // 明文写信息文件
            if (func070004FF(id, rx_buf, rx_len, tx_buf, tx_len)) {
                D_ASSERT(Comm_serr != 0x00);
                retvalue = COMM_RETVAL_ERROR;
            }
        }
        break;
        case 0x070005FF: {                                     // 密文写信息文件
            if (func070005FF(id, rx_buf, rx_len, tx_buf, tx_len)) {
                D_ASSERT(Comm_serr != 0x00);
                retvalue = COMM_RETVAL_ERROR;
            }
        }
        break;
#if defined(M_LOCAL)
        case 0x070101FF: {                                               // 开户
            if (func070101FF(id, rx_buf, rx_len, tx_buf, tx_len)) {
                D_ASSERT(Comm_serr != 0x00);
                retvalue = COMM_RETVAL_ERROR;
            }
        }
        break;
        case 0x070102FF: {                                               // 充值
            if (func070102FF(id, rx_buf, rx_len, tx_buf, tx_len)) {
                D_ASSERT(Comm_serr != 0x00);
                retvalue = COMM_RETVAL_ERROR;
            }
        }
        break;
        case 0x070103FF: {                                     // 钱包初始化命令
            if (allKeysState_get() != ALL_KEYS_PUBLIC) {   // 只在公钥状态下执行     
                Comm_serr = COMM_SERR_OTHERS;
                retvalue = COMM_RETVAL_ERROR;
                break;
            }
            if (func070103FF(id, rx_buf, rx_len, tx_buf, tx_len)) {
                D_ASSERT(Comm_serr != 0x00);
                retvalue = COMM_RETVAL_ERROR;
            }
        }        
        break;
#endif
        case 0x070301FF: {                                       // 密钥更新命令
            if (raKeyOperateInfo.state == ST_KEY_OPERATE_IDLE) {
                memcpy(raKeyOperateInfo.operateID, operatorID, 4);
            }
            if (func070301FF(id, rx_buf, rx_len, tx_buf, tx_len)) {
                D_ASSERT(Comm_serr != 0x00);
                retvalue = COMM_RETVAL_ERROR;
            }
            else {
                EventRecord_fn033000ZZ(operatorID, id);              // 编程记录
            }        
            
        }
        break;
        case 0x078001FF: {                                           // 数据回抄
            if (func078001FF(id, rx_buf, rx_len, tx_buf, tx_len)) {
                D_ASSERT(Comm_serr != 0x00);
                retvalue = COMM_RETVAL_ERROR;
            }
        }
        break;
        case 0x078002FF: {                                           // 软件比对
            if (func078002FF(id, rx_buf, rx_len, tx_buf, tx_len)) {
                D_ASSERT(Comm_serr != 0x00);
                retvalue = COMM_RETVAL_ERROR;
            }
        }
        break;
        case 0x078003FF: {                                       // 红外认证请求
            if (Comm_chnl != 0) {
                Comm_serr = COMM_SERR_OTHERS;
                retvalue = COMM_RETVAL_ERROR;
            }
            if (g_opMode == OP_MODE_WAKEUP) {
                Comm_serr = COMM_SERR_OTHERS;
                retvalue = COMM_RETVAL_ERROR;
            }
            if (func078003FF(id, rx_buf, rx_len, tx_buf, tx_len)) {
                D_ASSERT(Comm_serr != 0x00);
                retvalue = COMM_RETVAL_ERROR;
            }
        }
        break;
        case 0x078102FF: {                                           // 状态查询
            if (func078102FF(id, rx_buf, rx_len, tx_buf, tx_len)) {
                D_ASSERT(Comm_serr != 0x00);
                retvalue = COMM_RETVAL_ERROR;
            }
        }
        break;
        //...
        default: {
            Comm_serr |= COMM_SERR_OTHERS;
            retvalue = COMM_RETVAL_ERROR;
        }
        break;
    }
    
    return retvalue;
}
/* ===========================================================================*/
/**
 * brief : 
 * 
 * date  : 2012-10-17
 */
/* ---------------------------------------------------------------------------*/
void Remote_Init(void)
{
    // 数据恢复
    DataMirrorRestore(dataMirrors, dimof(dataMirrors));
    
    if((ra07000101[0] | ra07000101[1]) == 0 || (!is_valid_bcd(ra07000101, 2))) {
        ra07000101[0] = 5;
        ra07000101[1] = 0;
    }
    if (!LicenseState_get(LS_KEY_AUTHORIZE)){
        fr.newProgramRecord = true;
    }
}
void Remote_Default(void)
{
    DataMirrorDefault(dataMirrors, dimof(dataMirrors));
}

/* ===========================================================================*/
/**
 * brief : 
 * 
 * date  : 2012-10-17
 */
/* ---------------------------------------------------------------------------*/
//#pragma location="CODE_PROTECTED_AREAS" 
void Remote_Modu(void)
{
    if (g_flag & FLAG_GOING_TO_LPM) {
        allmemput(ADDR_OF(EE_sect7, eeTimeCheckoutMAC), &ra_timeCheckoutMAC, 1);
        return;
    }

    /* 清零处理 */
    if (Produce_askedToClr == SECURE_TRUE) {
        ra_timeCheckoutMAC = 0;
        ra_longRangeForbid = false;                          // 解除远程挂起状态
        ra04000508 = (uint32_t)0;
        allmemput(ADDR_OF(EE_sect7,eeTimeCheckoutMAC), &ra_timeCheckoutMAC, 1);
        allmemput(ADDR_OF(EE_sect7,eeLongRangeForbid), &ra_longRangeForbid, 1);
        allmemput(ADDR_OF(EE_sect7,eeESAM_SiresNo), &ESAMSeriesNo, sizeof(ESAMSeriesNo));
        allmemset(ADDR_OF(EE_sect7,ee04000508), 0x00, sizeof(ra04000508));
    }

    if ( (!(FirstResetEsamFlag & ESAM_RESET))                        // 没复位过
        || ((!(FirstResetEsamFlag & ESAM_RESET_SUCCESS))   // 复位没成功且过分钟
        && (RTC_Get_TimeChangeFlag() & (YEAR|MONTH|DATE|HOUR|MINUTE))))
    {
        FirstResetEsamFlag |= ESAM_RESET;
        if (Esam_FirstReset()) {
            FirstResetEsamFlag |= ESAM_RESET_SUCCESS;
        }
    }
        
    Key_Monitor();                                               // 密钥更新处理
    flushKeyStateDisplay();                                      // 密钥状态显示 
    longRangeForbid_Process();                                   // 挂起处理
}



