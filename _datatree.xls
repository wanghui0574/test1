#include <datatree.h>
#include <display.h>
#include "project.h"
#include "rtc.h"
#include "load_profile.h"
#include <energy.h>

NAME_THIS_FILE(_datatree)

// ---------------------------------------------------------------------- 版本号
#define SX_VER "V1.0"
// ------------------------------------------------------------------------ 市场
#define MARKET "SGCC"
// ------------------------------------------------------------------------- MCU
#if defined (__MSP430F5438__)
    #define MCU_NAME "5438"
#elif defined(__IO78F1168_A0_H__)
    #define MCU_NAME "1168"
#else
    #define MCU_NAME "?"
#endif
// -------------------------------------------------------------------- 计量芯片
#if defined (MEASURECHIP_ATT7022E)
    #define MPU_NAME "7022E"
#elif defined(MEASURECHIP_RN8302)
    #define MPU_NAME "8302"
#elif defined(MEASURECHIP_ADE7858)
    #define MPU_NAME "7858"
#else
    #define MPU_NAME "?"
#endif
// -------------------------------------------------------------------- 电表类型

#if defined(M_LOCAL)
    #define CMC    "DTZY"
    #define METER_TYPE "Local"
#elif defined(M_REMOTE)
    #define CMC    "DTZY"
    #define METER_TYPE "Remote"
#elif defined(M_SMART)
    #define CMC    "DTZ"
    #define METER_TYPE "Smart"
#else
    #define CMC    "?"
    #define METER_TYPE "?"
#endif   

// ------------------------------------------------------------------ 继电器方式
#if defined(RELAY_BUILT_IN)
    #define RELAY_TYPE
#else
    #if defined(M_LOCAL)||defined(M_REMOTE)
    #define RELAY_TYPE "_X"
    #else
    #define RELAY_TYPE
    #endif
#endif   

#define STR88888888() (SX_VER" "MARKET"_"CMC"_"METER_TYPE"_"MCU_NAME"_"MPU_NAME\
                       ""RELAY_TYPE)




// ROM区 =======================================================================
const uint8_t ro04000105[2]  = {REV2(0x00,0x80)};
const char    ro0400040D[16] = "DL/T 645 - 2007";

//#pragma location="DATA20_C_PROTECTED_AREAS"
const char ro88888888[64] = STR88888888();
 
// RAM区 =======================================================================
uint8_t  ra04000101[4];                                            // 日期及周次
uint8_t  ra04000102[3];                                                  // 时间

struct Xx02ZZZZZZ ra02ZZZZZZ;
/* 此区域的瞬时量在进入低功耗过程会在measure模块中被整块清零,增减变量时需同步调整清零长度 */
uint8_t  ra02010100[PN][2];                                        // A/B/C相电压
uint8_t  ra02020100[PN][3];                                        // A/B/C相电流
uint8_t  ra02030000[3];                                        // 瞬时有功总功率
uint8_t  ra02030100[PN][3];                                // A/B/C相瞬时有功功率
/*uint8_t  ra02040000[3];                                        // 瞬时无功总功率
uint8_t  ra02040100[3][3];                                // A/B/C相瞬时无功功率
uint8_t  ra02050000[3];                                        // 瞬时总视在功率
uint8_t  ra02050100[3][3];                                // A/B/C相瞬时视在功率*/
uint8_t  ra02060000[2] = {0x00,0x10};                              // 总功率因数
uint8_t  ra02060100[PN][2] = {{0x00,0x10}};                   // A/B/C相功率因数
uint8_t  ra02070100[PN][2];                                        // A/B/C相相角
/******************************************************************************/

//#if defined(M_SMART) 
//uint8_t  ra02080100[3][2];                              // A/B/C相电压波形失真度
//uint8_t  ra02090100[3][2];                              // A/B/C相电流波形失真度
//uint8_t  ra020A0101[3][1+HN][2];                 // A、B、C相电压0～HN次谐波含量
//uint8_t  ra020B0101[3][1+HN][2];                 // A、B、C相电流0～HN次谐波含量
//#endif
//uint8_t  ra02800001[3];                                            // 零线电流

/* 此区域的瞬时量在进入低功耗过程会在measure模块中被整块清零,增减变量时需同步调整清零长度 */
uint8_t  ra02800002[2];                                              // 电网频率
uint8_t  ra02800003[3];                                  // 一分钟有功总平均功率
uint8_t  ra02800004[3];                                          // 当前有功需量
uint8_t  ra02800005[3];                                          // 当前无功需量
uint8_t  ra02800006[3];                                        // 当前视在需量
/******************************************************************************/

uint8_t  ra02800007[2];                                              // 表内温度
uint8_t  ra02800008[2];                                    // 时钟电池电压(内部)
uint8_t  ra02800009[2];                                // 停电抄表电池电压(外部)
uint8_t  ra0280000A[4];                                      // 时钟电池工作时间
uint8_t  ra028000FC;                                           // 内部表计状态字
//uint8_t  ra02800100[3][2];                                // Uab/Uac/Ubc电压夹角

uint8_t   ra_APCF[3]={0x00,0x00,0x72};                        //高频脉冲输出设置

uint16_t ra04000501[7];                                    // 电表运行状态字1～7
uint8_t ra04001501[10];                                        // 主动上报状态字

uint8_t  ra02020100_ns[PN][3];                           // A/B/C相电流无符号数据
uint8_t  ra02030000_ns[3];                                     // 瞬时有功总功率
uint8_t  ra02030100_ns[PN][3];                             // A/B/C相瞬时有功功率
/*uint8_t  ra02040000_ns[3];                                     // 瞬时无功总功率
uint8_t  ra02040100_ns[3][3];                             // A/B/C相瞬时无功功率
uint8_t  ra02050000_ns[3];                                     // 瞬时总视在功率
uint8_t  ra02050100_ns[3][3];                             // A/B/C相瞬时视在功率*/
uint8_t  ra02060000_ns[2];                                         // 总功率因数
uint8_t  ra02060100_ns[PN][2];                                 // A/B/C相功率因数

/*========================= “可写”数据的RAM区对应 ==========================*/
uint8_t  ra04000103 = 5;
uint8_t  ra04000104 = 1;
uint8_t  ra04000106[5];                                    // 两套时区表切换时间
uint8_t  ra04000107[5];

uint16_t ra040001FC = 1;
uint8_t  ra040001FE = 3;
uint8_t  ra04000201 = ZN;
uint8_t  ra04000202 = BN;
uint8_t  ra04000203 = GN;
uint8_t  ra04000204 = TN;
uint16_t ra04000205 = 10;
uint8_t  ra04000206 = HN;
uint8_t  ra04000207 = LN -1;                                            //阶梯数

uint8_t  ra04000301 = 19;
uint8_t  ra04000302 = 5;
uint8_t  ra04000303 = 2;
uint8_t  ra04000304 = 4;
uint8_t  ra04000305 = 68;
uint8_t  ra04000308;
uint16_t ra040003EA[3] = {REV3(0x0002, 0x0000, 0x0000)};
uint16_t ra040003FA[3];
uint16_t ra040003FB[3];
uint16_t ra040003FC[3];
uint8_t  ra040003FE;

uint8_t  ra04000401[6];
uint8_t  ra04000402[6];
//uint8_t  ra04000403[32];
uint16_t ra04000404;
uint16_t ra04000405;
uint16_t ra04000406;
uint8_t  ra04000407;
uint8_t  ra04000408;
uint32_t ra04000409 = 3200;
uint32_t ra0400040A = 3200;
//uint8_t  ra0400040C[10];

uint8_t  ra04000601 = 0x09;
uint8_t  ra04000602[2] = {0x05, 0x50};

uint16_t ra04000701 = 1200;
uint16_t ra04000702 = 2400;
uint16_t ra04000703[3] = {2400, 2400, 2400};

uint8_t  ra04000801 = 0x3E;
uint8_t  ra04000802 = 1;

uint8_t  ra04000901 = 0xFF;                          // 负荷记录模式字
uint8_t  ra04000902 = 0xFF;                          // 定时冻结数据模式字
uint8_t  ra04000903 = 0xFF;                          // 瞬时冻结数据模式字
uint8_t  ra04000904 = 0xFF;                          // 约定冻结数据模式字
uint8_t  ra04000905 = 0x03;                          // 周期(整点)冻结数据模式字
uint8_t  ra04000906 = 0xFF;                          // 日冻结数据模式字

uint8_t  ra04000A01[4];
uint16_t ra04000A02[6] = {5, 5, 5, 5, 5, 5};

uint8_t  ra04000B01[3][2] = {
    {REV2(0x01,0x00)},
    {REV2(0x99,0x99)},
    {REV2(0x99,0x99)},
};

uint8_t  ra04000C01[10][4] = {
    {0, 0x00, 0x00, 0x00},
    {1, 0x00, 0x00, 0x00},
    {2, 0x00, 0x00, 0x00},
    {3, 0x00, 0x00, 0x00},
    {4, 0x00, 0x00, 0x00},
    {5, 0x00, 0x00, 0x00},
    {6, 0x00, 0x00, 0x00},
    {7, 0x00, 0x00, 0x00},
    {8, 0x00, 0x00, 0x00},
    {9, 0x00, 0x00, 0x00},
};
bool ra04000CFE;                                               // 允许进入软编程

uint8_t ra04001104[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};   //主动上报模式字

struct Xx04000D01_04 ra04000D01_04[3];
uint32_t ra04000E01 = (uint32_t)(3 * (UN * 1.5) * IMAX * 1e4 + 0.5);
uint32_t ra04000E02 = (uint32_t)(3 * (UN * 1.5) * IMAX * 1e4 + 0.5);
uint16_t ra04000E03 = (uint16_t)(UN * 1.5 * 1e1 + 0.5);
uint16_t ra04000E04 = (uint16_t)(UN * 0.6 * 1e1 + 0.5);
#if defined(M_LOCAL)
uint8_t  ra04001001[4] = {REV4(0x00, 0x00, 0x10, 0x00)};             //报警金额1
uint8_t  ra04001002[4] = {REV4(0x00, 0x00, 0x05, 0x00)};             //报警金额2
uint8_t  ra04001003[4] = {REV4(0x00, 0x00, 0x00, 0x00)};          //透支金额限值
uint8_t  ra04001004[4] = {REV4(0x99, 0x99, 0x99, 0x99)};          //囤积金额限值
uint8_t  ra04001005[4] = {REV4(0x00, 0x00, 0x00, 0x00)};      //合闸允许金额限值
#endif
uint8_t ra04001101;                                           // 电表运行特征字1
uint8_t ra04001201[5] = {0x00, 0x00, 0x01, 0x01, 0x10};      // 整点冻结起始时间
uint8_t ra04001202 = 60;                                     // 整点冻结时间间隔
uint8_t ra04001203[2] = {0x00, 0x01};                              // 日冻结时间
uint8_t ra04001301[1] = {0x00};                     //无线通信在线及强弱信号指示

uint16_t ra04001502;                                               // 插卡状态字
struct DispItem ra04040101[AN];
struct DispItem ra04040201[MN];
/*
uint16_t  ra04090101;                           // 失压事件电压触发上限
uint16_t  ra04090102;                           // 失压事件电压恢复下限
uint32_t  ra04090103;                           // 失压事件电流触发下限
uint8_t   ra04090104 = 1;                       // 失压事件触发延时时间
uint16_t  ra04090201;                           // 欠压事件电压触发上限
uint8_t   ra04090202 = 1;                       // 欠压事件触发延时时间
uint16_t  ra04090301;                           // 过压事件电压触发上限
uint8_t   ra04090302 = 1;                       // 过压事件触发延时时间
uint16_t  ra04090401;                           // 断相事件电压触发上限
uint32_t  ra04090402;                           // 断相事件电流触发上限
uint8_t   ra04090403 = 1;                       // 断相事件触发延时时间
uint16_t  ra04090501;                           // 电压不平衡率限值
uint8_t   ra04090502 = 1;                       // 电压不平衡率触发延时时间
uint16_t  ra04090601;                           // 电流不平衡率限值
uint8_t   ra04090602 = 1;                       // 电流不平衡率触发延时时间
uint16_t  ra04090701;                           // 失流事件电压触发下限
uint32_t  ra04090702;                           // 失流事件电流触发上限
uint32_t  ra04090703;                           // 失流事件电流触发下限
uint8_t   ra04090704 = 1;                       // 失流事件触发延时时间
uint16_t  ra04090801;                           // 过流事件电流触发下限
uint8_t   ra04090802 = 1;                       // 过流事件触发延时时间
uint16_t  ra04090901;                           // 断流事件电压触发下限
uint32_t  ra04090902;                           // 断流事件电流触发上限
uint8_t   ra04090903 = 1;                       // 断流事件触发延时时间
uint32_t  ra04090A01;                   // 潮流反向事件有功功率触发下限
uint8_t   ra04090A02 = 1;                   // 潮流反向事件触发延时时间
uint32_t  ra04091001;               // 有功功率反向事件有功功率触发下限
uint8_t   ra04091002 = 1;               // 有功功率反向事件判定延时时间
uint32_t  ra04090B01;                       // 过载事件有功功率触发下限
uint8_t   ra04090B02 = 1;                       // 过载事件触发延时时间
uint16_t  ra04090C01;                                   // 电压考核上限
uint16_t  ra04090C02;                                   // 电压考核下限
uint32_t  ra04090D01;                   // 有功需量超限事件需量触发下限
uint32_t  ra04090D02;                   // 无功需量超限事件需量触发下限
uint8_t   ra04090D03 = 1;                   // 需量超限事件触发延时时间
uint16_t  ra04090E01;                             // 总功率因数超限阀值
uint8_t   ra04090E02 = 1;               // 总功率因数超下限判定延时时间
uint16_t  ra04090F01;                             // 电流严重不平衡阀值
uint8_t   ra04090F02 = 1;                 // 电流严重不平衡触发延时时间
uint8_t   ra04090F11 = 60;                         //逆相序判断延时时间
*/
uint8_t ra00900200[4];                         // 当前剩余金额（用于显示、通信）
uint8_t ra0F000101[4];                                         // 购电前剩余金额
uint8_t ra00900201[4];                         // 当前透支金额（用于显示、通信）

uint8_t ra0280000B[4];                                           // 当前阶梯电价
uint8_t ra02800020[4];                                               // 当前电价
uint8_t ra02800021[4];                                           // 当前费率电价
uint8_t ra02800022[2];                                   // 身份认证时效剩余时间
uint8_t ra02800023[1];                                   // 红外认证时效剩余时间
uint8_t ra02800024[3];                                     // 本月总电压合格时间

uint8_t ra04000108[5];                                    //两套费率电价切换时间
uint8_t ra04000109[5];                                        //两套梯度切换时间
uint8_t ra04000306[3] = {REV3(0,0,1)};                         // 电流互感器变比
uint8_t ra04000307[3] = {REV3(0,0,1)};                         // 电压互感器变比
uint8_t ra0400040E[6];                                               // 客户编号

uint16_t ra04001401 = 5;                                          //跳闸延时时间


uint8_t ra04000208 = KN;                                           // 密钥总条数
uint32_t ra04000508;                                               // 密钥状态字

struct Xx0405ZZFF_TN ra040501FF;                               // 当前套费率数据
struct Xx0406ZZFF ra040604FF;                                  // 当前套阶梯数据

extern uint8_t ra_timeCheckoutMAC;

void DT_globalInit_CALLBACK(void)
{  
    /* 参变量中可写的数据可以通过writable_data_RAM_counterpart_restore()恢复, 
    ** 不可写的数据如040501FF, 040604FF需要在此恢复
    */
    D_ASSERT(!g_buf_locked);
    g_buf_locked = true;
#if defined(M_LOCAL)
    do {
        uint8_t a_id[4] = {REV4(0x04, 0x05,0x02, 0xFD)};
        /* 读取数据 */
        if (DT_get(a_id, g_buf)) {
            break;
        }
        /* 数据合法性检查 */
        if (fn0405ZZFF(DTE_FUNC_CONTEXT_WRITE_DATA_CHECK,
                                     a_id, 0xFF, g_buf, NULL,NULL))
        {
            break;
        }
        /* 转化到RAM区对应 */
        if (fn0405ZZFF(DTE_FUNC_CONTEXT_WRITE_DATA_TRANS,
                                     a_id, 0xFF, g_buf, NULL,NULL))
        {
            break;
        }
    }while(0);
    do {
        uint8_t a_id[4] = {REV4(0x04, 0x06,0x04, 0xFE)};
        /* 读取数据 */
        if (DT_get(a_id, g_buf)) {
            break;
        }
        /* 数据合法性检查 */
        if (fn0406ZZFF(DTE_FUNC_CONTEXT_WRITE_DATA_CHECK,
                                     a_id, 0xFF, g_buf, NULL,NULL))
        {
            break;
        }
        /* 转化到RAM区对应 */
        if (fn0406ZZFF(DTE_FUNC_CONTEXT_WRITE_DATA_TRANS,
                                     a_id, 0xFF, g_buf, NULL,NULL))
        {
            break;
        }
    }while(0);
#endif


    g_buf_locked = false;
}

// （非标准）处理函数 ----------------------------------------------------------
DTE_FUNC_PROTOTYPE(fn0E0F0000);
DTE_FUNC_PROTOTYPE(fn0E0F0100);
DTE_FUNC_PROTOTYPE(fn0F000100);
DTE_FUNC_PROTOTYPE(fn0F000101);
DTE_FUNC_PROTOTYPE(fn03060000);

#if defined (MEASURECHIP_ADE7858)
DTE_FUNC_PROTOTYPE(fn0E000000);
DTE_FUNC_PROTOTYPE(fn0E000029);
DTE_FUNC_PROTOTYPE(fn0E00002c);
DTE_FUNC_PROTOTYPE(fn0E000032);
DTE_FUNC_PROTOTYPE(fn0E010002);
DTE_FUNC_PROTOTYPE(fn0E010003);
DTE_FUNC_PROTOTYPE(fn0E0E0100);
DTE_FUNC_PROTOTYPE(fn0E0E0200);
DTE_FUNC_PROTOTYPE(fn0E0E0300);
DTE_FUNC_PROTOTYPE(fn0E0E0400);
#elif defined (MEASURECHIP_ATT7022E)
DTE_FUNC_PROTOTYPE(fn0D000000);
DTE_FUNC_PROTOTYPE(fn0D000016);
DTE_FUNC_PROTOTYPE(fn0D00001C);
DTE_FUNC_PROTOTYPE(fn0D010002);
DTE_FUNC_PROTOTYPE(fn0D010003);
DTE_FUNC_PROTOTYPE(fn0D010004);
DTE_FUNC_PROTOTYPE(fn0D010005);
DTE_FUNC_PROTOTYPE(fn0D0D0100);
DTE_FUNC_PROTOTYPE(fn0D0D0200);
DTE_FUNC_PROTOTYPE(fn0D0D0300);
DTE_FUNC_PROTOTYPE(fn0D0D0400);
#endif

/*============================= 数据树辅助结构 ===============================*/
const struct BiasedArraySpec DT_BASs[] = {
/*BI00000001*/ {0x01, 0x0C, DIM_SIZE_OF(EE_sect3, ee00ZZZZ01)},      // 电量
/*BI00D00001*/ {0x01, 0x04, DIM_SIZE_OF(EE_sect3, ee000DZZ01)},      // 年累计电量
/*BI00FE0001*/ {0x01, 0x0C, DIM_SIZE_OF(EE_sect3, ee00FEZZ01)},      // 电量结算时间
///*BI01010001*/ {0x01, 0x0C, DIM_SIZE_OF(EE_sect3, ee01ZZZZ01)},      // 需量
///*BI03050001*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03050001)},      // 全失压记录
#if defined(M_SMART)
///*BI03060001*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03060001)},      // 辅助电源失电
#endif
///*BI03100001*/ {0x01, 0x0C, DIM_SIZE_OF(EE_sect4, ee03100001)},      // 电压合格率统计数据
///*BI03100101*/ {0x01, 0x0C, DIM_SIZE_OF(EE_sect4, ee03100101[0])},   // A、B、C相电压合格率统计数据
///*BI03100201*/ {0x01, 0x0C, DIM_SIZE_OF(EE_sect4, ee03100101[1])},   // A、B、C相电压合格率统计数据
///*BI03100301*/ {0x01, 0x0C, DIM_SIZE_OF(EE_sect4, ee03100101[2])},   // A、B、C相电压合格率统计数据
/*BI03110001*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03110001)},      // 掉电
///*BI03120101*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03120101)},      // 正向有功需量超限记录
///*BI03120201*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03120201)},      // 反向有功需量超限记录
///*BI03120301*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03120301[0])},   // 第一、二、三四象限无功需量超限记录
///*BI03120401*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03120301[1])},   // 第一、二、三四象限无功需量超限记录
///*BI03120501*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03120301[2])},   // 第一、二、三四象限无功需量超限记录
///*BI03120601*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03120301[3])},   // 第一、二、三四象限无功需量超限记录
/*BI03300001*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300001)},      // 编程记录
/*BI03300101*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300101)},    // 电表清零记录
///*BI03300201*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, df03300201)},    // 需量清零记录
/*BI03300301*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300301)},      // 事件清零记录
/*BI03300401*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300401)},      // 校时记录
/*BI03300501*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300501)},    // 时段表编程记录
/*BI03300601*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300601)},    // 时区表编程记录
/*BI03300701*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300701)},      // 周休日编程记录
/*BI03300801*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300801)},    // 节假日编程记录
/*BI03300901*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300901)},      // 有功组合方式编程记录
///*BI03300A01*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300A01)},      // 无功组合方式1编程记录
///*BI03300B01*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300B01)},      // 无功组合方式2编程记录
/*BI03300C01*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300C01)},      // 结算日编程记录
/*BI03300D01*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300D01)},      // 开表盖记录
/*BI03300E01*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300E01)},      // 开端钮盒记录
/*BI03300F01*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300F01)},    // 费率表编程记录
/*BI03301001*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03301001)},    // 阶梯表编程记录
/*BI03301201*/ {0x01, 0x02, DIM_SIZE_OF(EE_sect4, ee03301201)},      // 密钥更新记录
/*BI03301301*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03301301)},      // 异常插卡记录
#if defined(M_LOCAL)
/*BI03330101*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03330101)},      // 购电记录
#endif
/*BI03340001*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03340001)},      // 退费记录
/*BI03350001*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03350001)},      // 恒定磁场干扰记录
/*BI03360001*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03360001)},      // 负荷开关误动记录
/*BI03370001*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03370001)},      // 电源异常事件记录
/*BI05000001*/ {0x01, 0x3C, DIM_SIZE_OF(EE_sect5, ee0500ZZ01)},    // 定时冻结
/*BI05010001*/ {0x01, 0x03, DIM_SIZE_OF(EE_sect5, ee0501ZZ01)},    // 瞬时冻结
/*BI05020001*/ {0x01, 0x02, DIM_SIZE_OF(EE_sect5, ee0502ZZ01)},    // 两套时区表切换（约定冻结）
/*BI05030001*/ {0x01, 0x02, DIM_SIZE_OF(EE_sect5, ee0503ZZ01)},    // 两套日时段表切换（约定冻结）
/*BI05040001*/ {0x01, 0xFE, DIM_SIZE_OF(EE_sect5, ee0504ZZ01)},      // 周期（整点）冻结
#if defined(M_LOCAL)
/*BI05050001*/ {0x01, 0x02, DIM_SIZE_OF(EE_sect5, ee0505ZZ01)},    // 费率表切换冻结
#endif
/*BI05060001*/ {0x01, 0x3E, DIM_SIZE_OF(EE_sect5, ee0506ZZ01)},      // 日冻结EE区
/*BI05070001*/ {0x01, 0x02, DIM_SIZE_OF(EE_sect5, ee0507ZZ01)},    // 两套阶梯切换数据记录
///*BI10010102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect4, df1001ZZ02[0]._)}, // A、B、C相失压记录
///*BI10020102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect4, df1001ZZ02[1]._)},
///*BI10030102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect4, df1001ZZ02[2]._)},
///*BI11010102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect4, df1101ZZ02[0]._)}, // A、B、C相欠压记录
///*BI11020102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect4, df1101ZZ02[1]._)},
///*BI11030102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect4, df1101ZZ02[2]._)},
///*BI12010102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect5, df1201ZZ02[0]._)}, // A、B、C相过压记录
///*BI12020102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect5, df1201ZZ02[1]._)},
///*BI12030102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect5, df1201ZZ02[2]._)},
///*BI13010102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect5, df1301ZZ02[0]._)}, // A、B、C相断相记录
///*BI13020102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect5, df1301ZZ02[1]._)},
///*BI13030102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect5, df1301ZZ02[2]._)},
///*BI14000101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect5, df1400ZZ01._)},    // 电压逆相序记录
///*BI15000101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect6, df1500ZZ01._)},    // 电流逆相序记录
///*BI16000102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect6, df1600ZZ02._)},    // 电压不平衡记录
///*BI17000102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect6, df1700ZZ02._)},    // 电流不平衡记录
///*BI18010101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect6, df1801ZZ01[0]._)}, // A、B、C相失流记录
///*BI18020101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect6, df1801ZZ01[1]._)},
///*BI18030101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect6, df1801ZZ01[2]._)},
///*BI19010101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect7, df1901ZZ01[0]._)}, // A、B、C相过流记录
///*BI19020101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect7, df1901ZZ01[1]._)},
///*BI19030101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect7, df1901ZZ01[2]._)},
///*BI1A010101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect7, df1A01ZZ01[0]._)}, // A、B、C相断流记录
///*BI1A020101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect7, df1A01ZZ01[1]._)},
///*BI1A030101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect7, df1A01ZZ01[2]._)},
///*BI1B010101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect8, df1B01ZZ01[0]._)}, // A、B、C相有功功率反向记录
///*BI1B020101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect8, df1B01ZZ01[1]._)},
///*BI1B030101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect8, df1B01ZZ01[2]._)},
///*BI1C010101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect8, df1C01ZZ01[0]._)}, // A、B、C相过载记录
///*BI1C020101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect8, df1C01ZZ01[1]._)},
///*BI1C030101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect8, df1C01ZZ01[2]._)},
/*BI1D000101*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee1D00ZZ01)},    // 跳闸记录
/*BI1E000101*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee1E00ZZ01)},    // 合闸记录
///*BI1F000101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect9, df1F00ZZ01._)},    // 总功率因素超下限记录
///*BI1F010101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect9, df1F01ZZ01[0]._)}, // A、B、C相功率因素超下限记录
///*BI1F020101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect9, df1F01ZZ01[1]._)},
///*BI1F030101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect9, df1F01ZZ01[2]._)},
///*BI20000102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect6, df2000ZZ02._)},    // 电流严重不平衡记录
///*BI21000001*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect8, df210000ZZ._)},    // 潮流反向记录
///*BI03800101*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03800101)},      // 非法校时记录(三星)
};
C_ASSERT(BI_END == dimof(DT_BASs));

const struct ConstantArraySpec DT_CASs[] = {
///*CI00030000*/ {0x03, 0x04-0x03+1, SIZE_OF(FR_sect4, fr00ZZZZ00.m_0003ZZZZ[0])},                  // 组合无功1,2
///*CI00050000*/ {0x05, 0x08-0x05+1, SIZE_OF(FR_sect4, fr00ZZZZ00.m_0005ZZZZ[0])},                  // 第一,二,三,四象限
///*CI00170000*/ {0x17, 0x18-0x17+1, SIZE_OF(FR_sect4, fr00ZZZZ00.m_0015_1E00ZZ[0].m_001700ZZ[0])}, // A相组合无功1,2
///*CI00190000*/ {0x19, 0x1C-0x19+1, SIZE_OF(FR_sect4, fr00ZZZZ00.m_0015_1E00ZZ[0].m_001900ZZ[0])}, // A相第一,二,三,四象限
///*CI002B0000*/ {0x2B, 0x2C-0x2B+1, SIZE_OF(FR_sect4, fr00ZZZZ00.m_0015_1E00ZZ[1].m_001700ZZ[0])}, // B相组合无功1,2
///*CI002D0000*/ {0x2D, 0x30-0x2D+1, SIZE_OF(FR_sect4, fr00ZZZZ00.m_0015_1E00ZZ[1].m_001900ZZ[0])}, // B相第一,二,三,四象限
///*CI003F0000*/ {0x3F, 0x40-0x3F+1, SIZE_OF(FR_sect4, fr00ZZZZ00.m_0015_1E00ZZ[2].m_001700ZZ[0])}, // C相组合无功1,2 
///*CI00410000*/ {0x41, 0x44-0x41+1, SIZE_OF(FR_sect4, fr00ZZZZ00.m_0015_1E00ZZ[2].m_001900ZZ[0])}, // C相第一,二,三,四象限
///*CI01030000*/ {0x03, 0x04-0x03+1, SIZE_OF(FR_sect4, fr01ZZZZ00.m_0103ZZZZ[0])},                  // 组合无功1,2需量
///*CI01050000*/ {0x05, 0x08-0x05+1, SIZE_OF(FR_sect4, fr01ZZZZ00.m_0105ZZZZ[0])},                  // 第一,二,三,四象限需量
//! /*CI01170000*/ {0x17, 0x18-0x17+1, SIZE_OF(FR_sect4, fr01ZZZZ00.m_0115_1E00ZZ[0].m_011700ZZ[0])},
//! /*CI01190000*/ {0x19, 0x1C-0x19+1, SIZE_OF(FR_sect4, fr01ZZZZ00.m_0115_1E00ZZ[0].m_011900ZZ[0])},
//! /*CI012B0000*/ {0x2B, 0x2C-0x2B+1, SIZE_OF(FR_sect4, fr01ZZZZ00.m_0115_1E00ZZ[1].m_011700ZZ[0])},
//! /*CI012D0000*/ {0x2D, 0x30-0x2D+1, SIZE_OF(FR_sect4, fr01ZZZZ00.m_0115_1E00ZZ[1].m_011900ZZ[0])},
//! /*CI013F0000*/ {0x3F, 0x40-0x3F+1, SIZE_OF(FR_sect4, fr01ZZZZ00.m_0115_1E00ZZ[2].m_011700ZZ[0])},
//! /*CI01410000*/ {0x41, 0x44-0x41+1, SIZE_OF(FR_sect4, fr01ZZZZ00.m_0115_1E00ZZ[2].m_011900ZZ[0])},
/*CI02010100*/ {0x01, 0x03-0x01+1, sizeof(ra02010100[0])},
/*CI02020100*/ {0x01, 0x03-0x01+1, sizeof(ra02020100[0])},
/*CI02030100*/ {0x01, 0x03-0x01+1, sizeof(ra02030100[0])},
///*CI02040100*/ {0x01, 0x03-0x01+1, sizeof(ra02040100[0])},    // 无功功率
///*CI02050100*/ {0x01, 0x03-0x01+1, sizeof(ra02050100[0])},    // 视在功率
/*CI02060100*/ {0x01, 0x03-0x01+1, sizeof(ra02060100[0])},
/*CI02070100*/ {0x01, 0x03-0x01+1, sizeof(ra02070100[0])},
#if defined(M_SMART)
///*CI02080100*/ {0x01, 0x03-0x01+1, sizeof(ra02080100[0])},      //电压波形失真度
///*CI02090100*/ {0x01, 0x03-0x01+1, sizeof(ra02090100[0])},      //电流波形失真度
#endif
/*CI04000501*/ {0x01, 0x07-0x01+1, sizeof(ra04000501[0])},
///*CI04000602*/ {0x02, 0x03-0x02+1, SIZE_OF(EE_sect2, ee04000602[0])},
/*CI04000703*/ {0x03, 0x05-0x03+1, SIZE_OF(EE_sect2, ee04000703[0])},
/*CI04000A02*/ {0x02, 0x07-0x02+1, SIZE_OF(EE_sect2, ee04000A02[0])},
/*CI04000B01*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect2, ee04000B01[0])},
/*CI04010000*/ {0x01, 0x02-0x01+1, SIZE_OF(EE_sect2, ee040100ZZ[0])},
/*CI04010001*/ {0x01,          BN, SIZE_OF(EE_sect2, ee040100ZZ[0].ee04ZZ0001[0])},
/*CI04030001*/ {0x01,          DN, SIZE_OF(EE_sect2, ee04030001[0])},
/*CI04040101*/ {0x01,          AN, SIZE_OF(EE_sect2, ee04040101[0])},
/*CI04040201*/ {0x01,          MN, SIZE_OF(EE_sect2, ee04040201[0])},
#if defined(M_LOCAL)
/*CI04050100*/ {0x01, 0x02-0x01+1, SIZE_OF(EE_sect2, ee0405ZZFF[0])},
/*CI04050101*/ {0x01,          TN, SIZE_OF(EE_sect2, ee0405ZZFF[0].m_0405ZZMO[0])}, // 费率数据
/*CI0406ZZEN*/ {0x01, LN-1-0x01+1, SIZE_OF(Xx0406ZZFF, m_0406ZZEN[0])},             // 阶梯值
/*CI0406ZZMO*/ {  LN,   LN-0x01+1, SIZE_OF(Xx0406ZZFF, m_0406ZZMO[0])},             // 阶梯电价
/*CI0406ZZYS*/ {2*LN,         YSN, SIZE_OF(Xx0406ZZFF, m_0406ZZYS[0])},             // 年结算日
#endif
///*CI05000301*/ {0x03, 0x04-0x03+1, SIZE_OF(EE_sect5, df0500ZZ01[0].m_05ZZ03ZZ[0])},
///*CI05000501*/ {0x05, 0x08-0x05+1, SIZE_OF(EE_sect5, df0500ZZ01[0].m_05ZZ05ZZ[0])},
/*CI06010000*/ {0x01, 0x06-0x01+1, 0},
#if defined(M_SMART)
/*CI020A0101*/ {0x01, 0x03-0x01+1, sizeof(ra020A0101[0])},            //谐波含量
#endif
#if defined(M_LOCAL)
/*CI0E0F0201*/ {0x01,          TN, 4},
/*CI0E0F0301*/ {0x01,        LN-1, 4},
/*CI0E0F0401*/ {0x01,          LN, 4},
#endif
///*CI10010001*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee10010001)+SIZE_OF(EE_sect5, ee10010002)},
///*CI10010101*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee1001ZZ01[0])},
///*CI10010102*/ {0x01, 0x03-0x01+1, SIZE_OF(DF_sect4, df1001ZZ02[0])},
///*CI11010001*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee11010001)+SIZE_OF(EE_sect5, ee11010002)},
///*CI11010101*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee1101ZZ01[0])},
///*CI11010102*/ {0x01, 0x03-0x01+1, SIZE_OF(DF_sect4, df1101ZZ02[0]._)},
///*CI12010001*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee12010001)+SIZE_OF(EE_sect5, ee12010002)},
///*CI12010101*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee1201ZZ01[0])},
///*CI12010102*/ {0x01, 0x03-0x01+1, SIZE_OF(DF_sect5, df1201ZZ02[0]._)},
///*CI13010001*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee13010001)+SIZE_OF(EE_sect5, ee13010002)},
///*CI13010101*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee1301ZZ01[0])},
///*CI13010102*/ {0x01, 0x03-0x01+1, SIZE_OF(DF_sect5, df1301ZZ02[0]._)},
///*CI18010001*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee18010001)+SIZE_OF(EE_sect5, ee18010002)},
///*CI18010101*/ {0x01, 0x03-0x01+1, SIZE_OF(DF_sect6, df1801ZZ01[0])},
///*CI19010001*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee19010001)+SIZE_OF(EE_sect5, ee19010002)},
///*CI19010101*/ {0x01, 0x03-0x01+1, SIZE_OF(DF_sect7, df1901ZZ01[0])},
///*CI1A010001*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee1A010001)+SIZE_OF(EE_sect5, ee1A010002)},
///*CI1A010101*/ {0x01, 0x03-0x01+1, SIZE_OF(DF_sect7, df1A01ZZ01[0])},
///*CI1B010001*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee1B010001)+SIZE_OF(EE_sect5, ee1B010002)},
///*CI1B010101*/ {0x01, 0x03-0x01+1, SIZE_OF(DF_sect8, df1B01ZZ01[0])},
///*CI1C010001*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee1C010001)+SIZE_OF(EE_sect5, ee1C010002)},
///*CI1C010101*/ {0x01, 0x03-0x01+1, SIZE_OF(DF_sect8, df1C01ZZ01[0])},
///*CI1D000501*/ {0x05, 0x08-0x05+1, SIZE_OF(DF_sect9, df1D00ZZ01[0].m_1D0005ZZ)},
///*CI1E000501*/ {0x05, 0x08-0x05+1, SIZE_OF(DF_sect9, df1E00ZZ01[0].m_1D0005ZZ)},
///*CI1F010001*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee1F010001)+SIZE_OF(EE_sect5, ee1F010002)},
///*CI1F010101*/ {0x01, 0x03-0x01+1, SIZE_OF(DF_sect9, df1F01ZZ01[0])},
///*CI02800100*/ {0x01, 0x03-0x01+1, sizeof(ra02800100[0])},
};
C_ASSERT(CI_END - CI_OFS == dimof(DT_CASs));

const struct DynamicArraySpec DT_DASs[] = {
/*DI00000100*/ {0x01, &ra04000204, SIZE_OF(FR_sect4, fr00ZZZZ00.m_000001ZZ[0])},
///*DI01010100*/ {0x01, &ra04000204, SIZE_OF(FR_sect4, fr01ZZZZ00.m_010101ZZ[0])},
#if defined(M_SMART)
/*DI020A0101*/ {0x01, &ra04000206, sizeof(ra020A0101[0][0])},     //谐波分析次数
#endif
};
C_ASSERT(DI_END - DI_OFS == dimof(DT_DASs));


/*================================= 数据树 ===================================*/
const struct DataTreeEntry DT_table[] = {
    {{REV4(0x00,   0x00,         0x00,         0x00)}, 0x0000, 0x04, (uint32_t)&RPwrTtl_Dtr[0] ,                    fn00000000, &ds00000000},
    {{REV4(0x00,   0x00,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_000000ZZ   ), fn00000000, &ds00000001},
    {{REV4(0x00,   0x00,     DI00000100,       0x00)}, 0x2000, 0x04, (uint32_t)&RPwrTtl_Dtr[4] ,                    fn00000000, &ds00000100},
    {{REV4(0x00,   0x00,     DI00000100, BI00000001)}, 0x3000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_000001ZZ[0]), fn00000000, &ds00000101},
    {{REV4(0x00,   0x01,         0x00,         0x00)}, 0x0000, 0x04, (uint32_t)&RPPwrTtl_Dtr[0],                    fn00000000, &ds00010000},
    {{REV4(0x00,   0x01,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_000100ZZ   ), fn00000000, &ds00010001},
    {{REV4(0x00,   0x01,     DI00000100,       0x00)}, 0x2000, 0x04, (uint32_t)&RPPwrTtl_Dtr[4],                    fn00000000, &ds00010100},
    {{REV4(0x00,   0x01,     DI00000100, BI00000001)}, 0x3000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_000101ZZ[0]), fn00000000, &ds00010101},
    {{REV4(0x00,   0x02,         0x00,         0x00)}, 0x0000, 0x04, (uint32_t)&RNPwrTtl_Dtr[0],                    fn00000000, &ds00020000},
    {{REV4(0x00,   0x02,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_000200ZZ   ), fn00000000, &ds00020001},
    {{REV4(0x00,   0x02,     DI00000100,       0x00)}, 0x2000, 0x04, (uint32_t)&RNPwrTtl_Dtr[4],                    fn00000000, &ds00020100},
    {{REV4(0x00,   0x02,     DI00000100, BI00000001)}, 0x3000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_000201ZZ[0]), fn00000000, &ds00020101},
/*
    {{REV4(0x00, CI00030000,     0x00,         0x00)}, 0x4000, 0x05, (uint32_t)&RPImpwrTtl_Dtr[0] ,                 fn00000000, &ds00030000},
    {{REV4(0x00, CI00030000,     0x00,   BI00000001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0003ZZZZ[0].m_00ZZ00ZZ   ), fn00000000, &ds00030001},
    {{REV4(0x00, CI00030000, DI00000100,       0x00)}, 0x6000, 0x05, (uint32_t)&RPImpwrTtl_Dtr[5] ,                 fn00000000, &ds00030100},
    {{REV4(0x00, CI00030000, DI00000100, BI00000001)}, 0x7000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0003ZZZZ[0].m_00ZZ01ZZ[0]), fn00000000, &ds00030101},
    {{REV4(0x00, CI00050000,     0x00,         0x00)}, 0x4000, 0x05, (uint32_t)&RQ1_ImpwrTtl_Dtr[0],                fn00000000, &ds00050000},
    {{REV4(0x00, CI00050000,     0x00,   BI00000001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0005ZZZZ[0].m_00ZZ00ZZ   ), fn00000000, &ds00050001},
    {{REV4(0x00, CI00050000, DI00000100,       0x00)}, 0x6000, 0x05, (uint32_t)&RQ1_ImpwrTtl_Dtr[5],                fn00000000, &ds00050100},
    {{REV4(0x00, CI00050000, DI00000100, BI00000001)}, 0x7000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0005ZZZZ[0].m_00ZZ01ZZ[0]), fn00000000, &ds00050101},
    {{REV4(0x00,   0x09,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_000900ZZ   ), fn00000000, NULL},
    {{REV4(0x00,   0x09,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_000900ZZ   ), fn00000000, NULL},
    {{REV4(0x00,   0x09,     DI00000100,       0x00)}, 0x2000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_000901ZZ[0]), fn00000000, NULL},
    {{REV4(0x00,   0x09,     DI00000100, BI00000001)}, 0x3000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_000901ZZ[0]), fn00000000, NULL},
    {{REV4(0x00,   0x0A,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_000A00ZZ   ), fn00000000, NULL},
    {{REV4(0x00,   0x0A,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_000A00ZZ   ), fn00000000, NULL},
    {{REV4(0x00,   0x0A,     DI00000100,       0x00)}, 0x2000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_000A01ZZ[0]), fn00000000, NULL},
    {{REV4(0x00,   0x0A,     DI00000100, BI00000001)}, 0x3000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_000A01ZZ[0]), fn00000000, NULL},
*/
    {{REV4(0x00,   0x0B,         0x00,         0x00)}, 0x0000, 0x05, (uint32_t)&ra000B0000[0],     fn00000000, &ds000B0000},
    {{REV4(0x00,   0x0B,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect3, ee000B0001), fn00000000, &ds000B0001},
    
    {{REV4(0x00,   0x0C,         0x00,         0x00)}, 0x0000, 0x05, (uint32_t)&ra000C0000[0],     fn00000000, &ds000B0000},
    {{REV4(0x00,   0x0C,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect3, ee000C0001), fn00000000, &ds000B0001},
    {{REV4(0x00,   0x0D,         0x00,         0x00)}, 0x0000, 0x08, (uint32_t)0,                  fn000D0000, &ds000D0000},
    {{REV4(0x00,   0x0D,         0x00,   BI000D0001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee000DZZ01[0].m_000D0001), fn000D0000, &ds000D0001},
    {{REV4(0x00,   0x0D,         0xFE,   BI000D0001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee000DZZ01[0].m_000DFE01), NULL, NULL},        
/*
    {{REV4(0x00,   0x15,         0x00,         0x00)}, 0x0000, 0x05, (uint32_t)&RPAPPwr_Dtr[0],    fn00000000, &ds00150000},
    {{REV4(0x00,   0x15,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[0].m_001500ZZ), fn00000000, &ds00150001},
    {{REV4(0x00,   0x16,         0x00,         0x00)}, 0x0000, 0x05, (uint32_t)&RPAPPwr_Dtr[5],    fn00000000, &ds00160000},
    {{REV4(0x00,   0x16,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[0].m_001600ZZ), fn00000000, &ds00160001},
    {{REV4(0x00, CI00170000,     0x00,         0x00)}, 0x4000, 0x05, (uint32_t)&RPAPPwr_Dtr[10] ,                               fn00000000, &ds00170000},
    {{REV4(0x00, CI00170000,     0x00,   BI00000001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[0].m_001700ZZ[0]), fn00000000, &ds00170001},
    {{REV4(0x00, CI00190000,     0x00,         0x00)}, 0x4000, 0x05, (uint32_t)&RPAPPwr_Dtr[20] , fn00000000, &ds00190000},
    {{REV4(0x00, CI00190000,     0x00,   BI00000001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[0].m_001900ZZ[0]), fn00000000, &ds00190001},
    {{REV4(0x00,   0x1D,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0015_1E00ZZ[0].m_001D00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x1D,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[0].m_001D00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x1E,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0015_1E00ZZ[0].m_001E00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x1E,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[0].m_001E00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x29,         0x00,         0x00)}, 0x0000, 0x05, (uint32_t)&RPBPPwr_Dtr[0],                                   fn00000000, &ds00290000},
    {{REV4(0x00,   0x29,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[1].m_001500ZZ), fn00000000, &ds00290001},
    {{REV4(0x00,   0x2A,         0x00,         0x00)}, 0x0000, 0x05, (uint32_t)&RPBPPwr_Dtr[5],                                   fn00000000, &ds002A0000},
    {{REV4(0x00,   0x2A,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[1].m_001600ZZ), fn00000000, &ds002A0001},
    {{REV4(0x00, CI002B0000,     0x00,         0x00)}, 0x4000, 0x05, (uint32_t)&RPBPPwr_Dtr[10] ,                                  fn00000000, &ds002B0000},
    {{REV4(0x00, CI002B0000,     0x00,   BI00000001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[1].m_001700ZZ[0]), fn00000000, &ds002B0001},
    {{REV4(0x00, CI002D0000,     0x00,         0x00)}, 0x4000, 0x05, (uint32_t)&RPBPPwr_Dtr[20] , fn00000000, &ds002D0000},
    {{REV4(0x00, CI002D0000,     0x00,   BI00000001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[1].m_001900ZZ[0]), fn00000000, &ds002D0001},
    {{REV4(0x00,   0x31,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0015_1E00ZZ[1].m_001D00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x31,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[1].m_001D00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x32,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0015_1E00ZZ[1].m_001E00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x32,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[1].m_001E00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x3D,         0x00,         0x00)}, 0x0000, 0x05, (uint32_t)&RPCPPwr_Dtr[0], fn00000000, &ds003D0000},
    {{REV4(0x00,   0x3D,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[2].m_001500ZZ), fn00000000, &ds003D0001},
    {{REV4(0x00,   0x3E,         0x00,         0x00)}, 0x0000, 0x05, (uint32_t)&RPCPPwr_Dtr[5], fn00000000, &ds003E0000},
    {{REV4(0x00,   0x3E,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[2].m_001600ZZ), fn00000000, &ds003E0001},
    {{REV4(0x00, CI003F0000,     0x00,         0x00)}, 0x4000, 0x05, (uint32_t)&RPCPPwr_Dtr[10] ,                                  fn00000000, &ds003F0000},
    {{REV4(0x00, CI003F0000,     0x00,   BI00000001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[2].m_001700ZZ[0]), fn00000000, &ds003F0001},
    {{REV4(0x00, CI00410000,     0x00,         0x00)}, 0x4000, 0x05, (uint32_t)&RPCPPwr_Dtr[20] , fn00000000, &ds00410000},
    {{REV4(0x00, CI00410000,     0x00,   BI00000001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[2].m_001900ZZ[0]), fn00000000, &ds00410001},
    {{REV4(0x00,   0x45,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0015_1E00ZZ[2].m_001D00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x45,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[2].m_001D00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x46,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0015_1E00ZZ[2].m_001E00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x46,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[2].m_001E00ZZ), fn00000000, NULL},
    不支持数据【关联电能】
    {{REV4(0x00,   0x80,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_008000ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x80,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_008000ZZ), fn00000000, NULL},
    
#if defined(M_SMART)
    【正向有功基波电能 反向有功基波电能 正向有功谐波电能 反向有功谐波电能】
    {{REV4(0x00,   0x81,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_008100ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x81,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_008100ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x82,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_008200ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x82,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_008200ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x83,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_008300ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x83,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_008300ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x84,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_008400ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x84,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_008400ZZ), fn00000000, NULL},
#endif
    {{REV4(0x00,   0x85,         0x00,         0x00)}, 0x0000, 0x05, (uint32_t)&RPLCU_pwr_Dtr[0] ,  fn00000000, NULL},
    {{REV4(0x00,   0x85,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_008500ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x86,         0x00,         0x00)}, 0x0000, 0x05, (uint32_t)&RPLFE_pwr_Dtr[0] ,  fn00000000, NULL},
    {{REV4(0x00,   0x86,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_008600ZZ), fn00000000, NULL},
#if defined(M_LOCAL)
    //{{REV4(0x00,   0x90,         0x01,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect5, fr00900100), NULL, &ds00900100},
    //{{REV4(0x00,   0x90,         0x01,         0x01)}, 0x0000, SIZE_ADDR_OF(FR_sect5, fr00900101), NULL, &ds00900101},
    {{REV4(0x00,   0x90,         0x02,         0x00)}, 0x0000, 4, (uint32_t)&ra00900200[0], fn00900200, &ds00900200},
    {{REV4(0x00,   0x90,         0x02,         0x01)}, 0x0000, 4, (uint32_t)&ra00900201[0], fn00900201, &ds00900201},
#endif
    不支持数据【A相关联电能】
    {{REV4(0x00,   0x94,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[0].m_009400ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x94,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect2, ee00ZZZZ01[0].m_0094_9A00ZZ[0].m_009400ZZ), fn00000000, NULL},
    
#if defined(M_SMART)
    【A相 正向有功基波电能 反向有功基波电能 正向有功谐波电能 反向有功谐波电能】
    {{REV4(0x00,   0x95,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[0].m_009500ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x95,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[0].m_009500ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x96,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[0].m_009600ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x96,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[0].m_009600ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x97,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[0].m_009700ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x97,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[0].m_009700ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x98,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[0].m_009800ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x98,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[0].m_009800ZZ), fn00000000, NULL},
#endif
    {{REV4(0x00,   0x99,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[0].m_009900ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x99,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[0].m_009900ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x9A,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[0].m_009A00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x9A,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[0].m_009A00ZZ), fn00000000, NULL},
    不支持数据【B相关联电能】
    {{REV4(0x00,   0xA8,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee00ZZZZ00   .m_0094_9A00ZZ[1].m_009400ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xA8,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[1].m_009400ZZ), fn00000000, NULL},
    
#if defined(M_SMART)
    【B相 正向有功基波电能 反向有功基波电能 正向有功谐波电能 反向有功谐波电能】
    {{REV4(0x00,   0xA9,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[1].m_009500ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xA9,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[1].m_009500ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xAA,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[1].m_009600ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xAA,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[1].m_009600ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xAB,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[1].m_009700ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xAB,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[1].m_009700ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xAC,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[1].m_009800ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xAC,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[1].m_009800ZZ), fn00000000, NULL},
#endif
    {{REV4(0x00,   0xAD,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[1].m_009900ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xAD,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[1].m_009900ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xAE,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[1].m_009A00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xAE,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[1].m_009A00ZZ), fn00000000, NULL},
    不支持数据【C相关联电能】
    {{REV4(0x00,   0xBC,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee00ZZZZ00   .m_0094_9A00ZZ[2].m_009400ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xBC,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[2].m_009400ZZ), fn00000000, NULL},
    
#if defined(M_SMART)
    【C相 正向有功基波电能 反向有功基波电能 正向有功谐波电能 反向有功谐波电能】*
    {{REV4(0x00,   0xBD,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[2].m_009500ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xBD,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[2].m_009500ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xBE,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[2].m_009600ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xBE,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[2].m_009600ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xBF,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[2].m_009700ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xBF,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[2].m_009700ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xC0,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[2].m_009800ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xC0,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[2].m_009800ZZ), fn00000000, NULL},
#endif
    {{REV4(0x00,   0xC1,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[2].m_009900ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xC1,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[2].m_009900ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xC2,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[2].m_009A00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xC2,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[2].m_009A00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xFE,         0x00,   BI00FE0001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00FEZZ01[0].m_00FE0001), NULL       , &ds00FE0001},
    {{REV4(0x00,   0xFE,         0xFE,   BI00FE0001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00FEZZ01[0].m_00FEFE01), NULL       , NULL},
*/
/*
    {{REV4(0x01,   0x01,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr01ZZZZ00   .m_010100ZZ   ), fn01010000, &ds01010000},
    {{REV4(0x01,   0x01,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_010100ZZ   ), fn01010000, &ds01010001},
    {{REV4(0x01,   0x01,     DI01010100,       0x00)}, 0x2000, SIZE_ADDR_OF(FR_sect4, fr01ZZZZ00   .m_010101ZZ[0]), fn01010000, &ds01010100},
    {{REV4(0x01,   0x01,     DI01010100, BI01010001)}, 0x3000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_010101ZZ[0]), fn01010000, &ds01010101},
    {{REV4(0x01,   0x02,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr01ZZZZ00   .m_010200ZZ   ), fn01010000, &ds01020000},
    {{REV4(0x01,   0x02,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_010200ZZ   ), fn01010000, &ds01020001},
    {{REV4(0x01,   0x02,     DI01010100,       0x00)}, 0x2000, SIZE_ADDR_OF(FR_sect4, fr01ZZZZ00   .m_010201ZZ[0]), fn01010000, &ds01020100},
    {{REV4(0x01,   0x02,     DI01010100, BI01010001)}, 0x3000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_010201ZZ[0]), fn01010000, &ds01020101},
    {{REV4(0x01, CI01030000,     0x00,         0x00)}, 0x4000, SIZE_ADDR_OF(FR_sect4, fr01ZZZZ00   .m_0103ZZZZ[0].m_01ZZ00ZZ   ), fn01010000, &ds01030000},
    {{REV4(0x01, CI01030000,     0x00,   BI01010001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0103ZZZZ[0].m_01ZZ00ZZ   ), fn01010000, &ds01030001},
    {{REV4(0x01, CI01030000, DI01010100,       0x00)}, 0x6000, SIZE_ADDR_OF(FR_sect4, fr01ZZZZ00   .m_0103ZZZZ[0].m_01ZZ01ZZ[0]), fn01010000, &ds01030100},
    {{REV4(0x01, CI01030000, DI01010100, BI01010001)}, 0x7000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0103ZZZZ[0].m_01ZZ01ZZ[0]), fn01010000, &ds01030101},
    {{REV4(0x01, CI01050000,     0x00,         0x00)}, 0x4000, SIZE_ADDR_OF(FR_sect4, fr01ZZZZ00   .m_0105ZZZZ[0].m_01ZZ00ZZ   ), fn01010000, &ds01050000},
    {{REV4(0x01, CI01050000,     0x00,   BI01010001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0105ZZZZ[0].m_01ZZ00ZZ   ), fn01010000, &ds01050001},
    {{REV4(0x01, CI01050000, DI01010100,       0x00)}, 0x6000, SIZE_ADDR_OF(FR_sect4, fr01ZZZZ00   .m_0105ZZZZ[0].m_01ZZ01ZZ[0]), fn01010000, &ds01050100},
    {{REV4(0x01, CI01050000, DI01010100, BI01010001)}, 0x7000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0105ZZZZ[0].m_01ZZ01ZZ[0]), fn01010000, &ds01050101},
    不支持数据
    {{REV4(0x01,   0x09,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_010900ZZ   ), fn01010000, NULL},
    {{REV4(0x01,   0x09,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_010900ZZ   ), fn01010000, NULL},
    {{REV4(0x01,   0x09,     DI01010100,       0x00)}, 0x2000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_010901ZZ[0]), fn01010000, NULL},
    {{REV4(0x01,   0x09,     DI01010100, BI01010001)}, 0x3000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_010901ZZ[0]), fn01010000, NULL},
    {{REV4(0x01,   0x0A,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_010A00ZZ   ), fn01010000, NULL},
    {{REV4(0x01,   0x0A,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_010A00ZZ   ), fn01010000, NULL},
    {{REV4(0x01,   0x0A,     DI01010100,       0x00)}, 0x2000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_010A01ZZ[0]), fn01010000, NULL},
    {{REV4(0x01,   0x0A,     DI01010100, BI01010001)}, 0x3000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_010A01ZZ[0]), fn01010000, NULL},
    {{REV4(0x01,   0x15,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[0].m_011500ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x15,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[0].m_011500ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x16,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[0].m_011600ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x16,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[0].m_011600ZZ), fn01010000, NULL},
    {{REV4(0x01, CI01170000,     0x00,         0x00)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[0].m_011700ZZ[0]), fn01010000, NULL},
    {{REV4(0x01, CI01170000,     0x00,   BI01010001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[0].m_011700ZZ[0]), fn01010000, NULL},
    {{REV4(0x01, CI01190000,     0x00,         0x00)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[0].m_011900ZZ[0]), fn01010000, NULL},
    {{REV4(0x01, CI01190000,     0x00,   BI01010001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[0].m_011900ZZ[0]), fn01010000, NULL},
    {{REV4(0x01,   0x1D,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[0].m_011D00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x1D,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[0].m_011D00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x1E,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[0].m_011E00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x1E,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[0].m_011E00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x29,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[1].m_011500ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x29,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[1].m_011500ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x2A,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[1].m_011600ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x2A,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[1].m_011600ZZ), fn01010000, NULL},
    {{REV4(0x01, CI012B0000,     0x00,         0x00)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[1].m_011700ZZ[0]), fn01010000, NULL},
    {{REV4(0x01, CI012B0000,     0x00,   BI01010001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[1].m_011700ZZ[0]), fn01010000, NULL},
    {{REV4(0x01, CI012D0000,     0x00,         0x00)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[1].m_011900ZZ[0]), fn01010000, NULL},
    {{REV4(0x01, CI012D0000,     0x00,   BI01010001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[1].m_011900ZZ[0]), fn01010000, NULL},
    {{REV4(0x01,   0x31,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[1].m_011D00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x31,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[1].m_011D00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x32,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[1].m_011E00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x32,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[1].m_011E00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x3D,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[2].m_011500ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x3D,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[2].m_011500ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x3E,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[2].m_011600ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x3E,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[2].m_011600ZZ), fn01010000, NULL},
    {{REV4(0x01, CI013F0000,     0x00,         0x00)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[2].m_011700ZZ[0]), fn01010000, NULL},
    {{REV4(0x01, CI013F0000,     0x00,   BI01010001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[2].m_011700ZZ[0]), fn01010000, NULL},
    {{REV4(0x01, CI01410000,     0x00,         0x00)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[2].m_011900ZZ[0]), fn01010000, NULL},
    {{REV4(0x01, CI01410000,     0x00,   BI01010001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[2].m_011900ZZ[0]), fn01010000, NULL},
    {{REV4(0x01,   0x45,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[2].m_011D00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x45,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[2].m_011D00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x46,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[2].m_011E00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x46,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[2].m_011E00ZZ), fn01010000, NULL},
*/
    {{REV4(0x02,   0x01,     CI02010100,       0x00)}, 0x2000, sizeof(ra02010100[0]), (uint32_t)ra02010100[0] , fn02010100, &ds02010100},
    {{REV4(0x02,   0x02,     CI02020100,       0x00)}, 0x2000, sizeof(ra02020100[0]), (uint32_t)ra02020100[0] , fn02020100_rev, &ds02020100},
    {{REV4(0x02,   0x03,         0x00,         0x00)}, 0x0000, sizeof(ra02030000)   , (uint32_t)&ra02030000[0], fn02030000, &ds02030000},
    {{REV4(0x02,   0x03,     CI02030100,       0x00)}, 0x2000, sizeof(ra02030100[0]), (uint32_t)ra02030100[0] , fn02030000, &ds02030100},
    //{{REV4(0x02,   0x04,         0x00,         0x00)}, 0x0000, sizeof(ra02040000)   , (uint32_t)&ra02040000[0], fn02030000, &ds02040000},
    //{{REV4(0x02,   0x04,     CI02040100,       0x00)}, 0x2000, sizeof(ra02040100[0]), (uint32_t)ra02040100[0] , fn02030000, &ds02040100},
    //{{REV4(0x02,   0x05,         0x00,         0x00)}, 0x0000, sizeof(ra02050000)   , (uint32_t)&ra02050000[0], fn02030000, &ds02050000},
    //{{REV4(0x02,   0x05,     CI02050100,       0x00)}, 0x2000, sizeof(ra02050100[0]), (uint32_t)ra02050100[0] , fn02030000, &ds02050100},
    {{REV4(0x02,   0x06,         0x00,         0x00)}, 0x0000, sizeof(ra02060000)   , (uint32_t)&ra02060000[0], fn02060000, &ds02060000},
    {{REV4(0x02,   0x06,     CI02060100,       0x00)}, 0x2000, sizeof(ra02060100[0]), (uint32_t)ra02060100[0] , fn02060000, &ds02060100},
    {{REV4(0x02,   0x07,     CI02070100,       0x00)}, 0x2000, sizeof(ra02070100[0]), (uint32_t)ra02070100[0] , fn02070100, &ds02070100},
#if defined(M_SMART)
    /*【电压电流失真度、谐波含量】*/
    {{REV4(0x02,   0x08,     CI02080100,       0x00)}, 0x2000, sizeof(ra02080100[0]), (uint32_t)ra02080100[0] , NULL, NULL},
    {{REV4(0x02,   0x09,     CI02090100,       0x00)}, 0x2000, sizeof(ra02090100[0]), (uint32_t)ra02090100[0] , NULL, NULL},
    {{REV4(0x02,   0x0A,     CI020A0101, DI020A0101)}, 0x3000, sizeof(ra020A0101[0][0]), (uint32_t)&ra020A0101[0][1][0], NULL, NULL},
    {{REV4(0x02,   0x0B,     CI020A0101, DI020A0101)}, 0x3000, sizeof(ra020B0101[0][0]), (uint32_t)&ra020B0101[0][1][0], NULL, NULL},
#endif
    //{{REV4(0x02,   0x80,         0x00,         0x01)}, 0x0000, sizeof(ra02800001), (uint32_t)&ra02800001[0], fn02800001, &ds02800001},
    {{REV4(0x02,   0x80,         0x00,         0x02)}, 0x0000, sizeof(ra02800002), (uint32_t)&ra02800002[0], fn02800002, &ds02800002},
    {{REV4(0x02,   0x80,         0x00,         0x03)}, 0x0000, sizeof(ra02800003), (uint32_t)&ra02800003[0], fn01010000, &ds02800003},
//    {{REV4(0x02,   0x80,         0x00,         0x04)}, 0x0000, sizeof(ra02800004), (uint32_t)&ra02800004[0], fn01010000, &ds02800004},
//    {{REV4(0x02,   0x80,         0x00,         0x05)}, 0x0000, sizeof(ra02800005), (uint32_t)&ra02800005[0], fn01010000, &ds02800005},
    //{{REV4(0x02,   0x80,         0x00,         0x06)}, 0x0000, sizeof(ra02800006), (uint32_t)&ra02800006[0], fn01010000, &ds02800006},
    {{REV4(0x02,   0x80,         0x00,         0x07)}, 0x0000, sizeof(ra02800007), (uint32_t)&ra02800007[0], fn02800007, &ds02800007},
    {{REV4(0x02,   0x80,         0x00,         0x08)}, 0x0000, sizeof(ra02800008), (uint32_t)&ra02800008[0], fn02800008, &ds02800008},
//    {{REV4(0x02,   0x80,         0x00,         0x09)}, 0x0000, sizeof(ra02800009), (uint32_t)&ra02800009[0], fn02800009, &ds02800009},
    {{REV4(0x02,   0x80,         0x00,         0x0A)}, 0x0000, SIZE_ADDR_OF(FR_sect3, fr0280000A      ), fn0280000A, &ds0280000A},
#if defined(M_LOCAL)
    /* 【当前阶梯电价】 */
    {{REV4(0x02,   0x80,         0x00,         0x0B)}, 0x0000, sizeof(ra0280000B), (uint32_t)&ra0280000B[0], fn0280000B, &ds0280000B},
    /* 【当前电价】 */
    {{REV4(0x02,   0x80,         0x00,         0x20)}, 0x0000, sizeof(ra02800020), (uint32_t)&ra02800020[0], fn0280000B, &ds02800020},
    /* 【当前费率电价】 */
    {{REV4(0x02,   0x80,         0x00,         0x21)}, 0x0000, sizeof(ra02800021), (uint32_t)&ra02800021[0], fn0280000B, NULL}, 
#endif
    {{REV4(0x02,   0x80,         0x00,         0x22)}, 0x0000, sizeof(ra02800022), (uint32_t)&ra02800022[0], NULL, NULL},
    {{REV4(0x02,   0x80,         0x00,         0x23)}, 0x0000, sizeof(ra02800023), (uint32_t)&ra02800023[0], NULL, NULL},
//    {{REV4(0x02,   0x80,         0x00,         0x24)}, 0x0000, SIZE_ADDR_OF(FR_sect3, fr02800024      ),     NULL, NULL},

    {{REV4(0x02,   0x80,         0x00,         0xFC)}, 0x0000, sizeof(ra028000FC), (uint32_t)&ra028000FC, NULL, NULL},
//    {{REV4(0x02,   0x80,     CI02800100,       0x00)}, 0x2000, sizeof(ra02800100[0]), (uint32_t)ra02800100[0] , NULL, NULL},
/*
    {{REV4(0x03,   0x05,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee03050000      ), fn03050000, &ds03050000},
    {{REV4(0x03,   0x05,         0x00,   BI03050001)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03050001[0]   ), fn03050001, &ds03050001},
#if defined(M_SMART)
    【辅助电源事件记录】
    {{REV4(0x03,   0x06,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee03060000      ), NULL, NULL},
    {{REV4(0x03,   0x06,         0x00,   BI03060001)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03060001[0]   ), NULL, NULL},
#endif
    {{REV4(0x03,   0x10,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee03100000      ), fn03100000, NULL},
    {{REV4(0x03,   0x10,         0x00,   BI03100001)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03100001[0]   ), fn03100000, NULL},
    {{REV4(0x03,   0x10,         0x01,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee03100100[0]   ), fn03100000, NULL},
    {{REV4(0x03,   0x10,         0x01,   BI03100101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03100101[0][0]), fn03100000, NULL},
    {{REV4(0x03,   0x10,         0x02,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee03100100[1]   ), fn03100000, NULL},
    {{REV4(0x03,   0x10,         0x02,   BI03100201)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03100101[1][0]), fn03100000, NULL},
    {{REV4(0x03,   0x10,         0x03,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee03100100[2]   ), fn03100000, NULL},
    {{REV4(0x03,   0x10,         0x03,   BI03100301)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03100101[2][0]), fn03100000, NULL},
*/
    {{REV4(0x03,   0x11,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03110000      ), fn03110000, &ds03110000},
    {{REV4(0x03,   0x11,         0x00,   BI03110001)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03110001[0]   ), NULL, &ds03110001},
/*
    {{REV4(0x03,   0x12,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03120000      ), NULL, NULL},
    {{REV4(0x03,   0x12,         0x01,   BI03120101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03120101[0]   ), NULL, NULL},
    {{REV4(0x03,   0x12,         0x02,   BI03120201)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03120201[0]   ), NULL, NULL},
    {{REV4(0x03,   0x12,         0x03,   BI03120301)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03120301[0][0]), NULL, NULL},
    {{REV4(0x03,   0x12,         0x04,   BI03120401)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03120301[1][0]), NULL, NULL},
    {{REV4(0x03,   0x12,         0x05,   BI03120501)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03120301[2][0]), NULL, NULL},
    {{REV4(0x03,   0x12,         0x06,   BI03120601)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03120301[3][0]), NULL, NULL},
*/
    {{REV4(0x03,   0x30,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300000      ), fn03110000, &ds03300000},
    {{REV4(0x03,   0x30,         0x00,   BI03300001)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300001[0]   ), NULL, &ds03300001},
    {{REV4(0x03,   0x30,         0x01,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300100      ), fn03110000, &ds03300100},
    {{REV4(0x03,   0x30,         0x01,   BI03300101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300101[0]   ), fn03300101, &ds03300101},
//    {{REV4(0x03,   0x30,         0x02,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300200      ), fn03110000, &ds03300200},
//    {{REV4(0x03,   0x30,         0x02,   BI03300201)}, 0x1000, SIZE_ADDR_OF(EE_sect4, df03300201[0] ), NULL, &ds03300201},
    {{REV4(0x03,   0x30,         0x03,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300300      ), fn03110000, &ds03300300},
    {{REV4(0x03,   0x30,         0x03,   BI03300301)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300301[0]   ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x04,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300400      ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x04,   BI03300401)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300401[0]   ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x05,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300500      ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x05,   BI03300501)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300501[0] ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x06,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300600      ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x06,   BI03300601)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300601[0] ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x07,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300700      ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x07,   BI03300701)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300701[0]   ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x08,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300800      ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x08,   BI03300801)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300801[0] ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x09,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300900      ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x09,   BI03300901)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300901[0]   ), NULL, NULL},
//    {{REV4(0x03,   0x30,         0x0A,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300A00      ), NULL, NULL},
//    {{REV4(0x03,   0x30,         0x0A,   BI03300A01)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300A01[0]   ), NULL, NULL},
//    {{REV4(0x03,   0x30,         0x0B,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300B00      ), NULL, NULL},
//    {{REV4(0x03,   0x30,         0x0B,   BI03300B01)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300B01[0]   ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x0C,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300C00      ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x0C,   BI03300C01)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300C01[0]   ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x0D,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300D00      ), fn03110000, &ds03300D00},
    {{REV4(0x03,   0x30,         0x0D,   BI03300D01)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300D01[0]   ), fn03300D01, NULL},
    {{REV4(0x03,   0x30,         0x0E,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300E00      ), fn03110000, &ds03300E00},
    {{REV4(0x03,   0x30,         0x0E,   BI03300E01)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300E01[0]   ), fn03300D01, NULL},
#if defined(M_LOCAL)
    {{REV4(0x03,   0x30,         0x0F,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300F00      ), fn03110000, NULL},
    {{REV4(0x03,   0x30,         0x0F,   BI03300F01)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300F01[0] ), fn03300F01, NULL},
    {{REV4(0x03,   0x30,         0x10,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03301000      ), fn03110000, NULL},
    {{REV4(0x03,   0x30,         0x10,   BI03301001)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03301001[0] ), NULL, NULL},
#endif
    {{REV4(0x03,   0x30,         0x12,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03301200      ), fn03110000, NULL},
    {{REV4(0x03,   0x30,         0x12,   BI03301201)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03301201[0]   ), NULL, NULL},
#if defined(M_LOCAL)
    /* 【异常插卡记录】 */
    {{REV4(0x03,   0x30,         0x13,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03301300      ), fn03110000, NULL},
    {{REV4(0x03,   0x30,         0x13,   BI03301301)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03301301[0]   ), NULL, NULL},
    /* 【非法插卡总次数】 */
    {{REV4(0x03,   0x30,         0x14,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect6, ee03301400      ), fn03110000, NULL},        
    /* 【电费型购电记录】 */
    {{REV4(0x03,   0x33,         0x01,   BI03330101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03330101[0].m_03330101), NULL, &ds03330101},
    {{REV4(0x03,   0x33,         0x02,   BI03330101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03330101[0].m_03330201), fn03330201, &ds03330201},
    {{REV4(0x03,   0x33,         0x03,   BI03330101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03330101[0].m_03330301), fn03330301, &ds03330301},
    {{REV4(0x03,   0x33,         0x04,   BI03330101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03330101[0].m_03330401), fn03330301, &ds03330401},
    {{REV4(0x03,   0x33,         0x05,   BI03330101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03330101[0].m_03330501), fn03330301, &ds03330501},
    {{REV4(0x03,   0x33,         0x06,   BI03330101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03330101[0].m_03330601), fn03330301, &ds03330601},
    /* 【退费记录】 */
    {{REV4(0x03,   0x34,         0x00,   BI03340001)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03340001[0]), NULL, NULL},
#endif
    /* 【恒定磁场干扰记录】 */
    {{REV4(0x03,   0x35,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03350000), NULL, NULL},
    {{REV4(0x03,   0x35,         0x00,   BI03350001)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03350001[0]), NULL, NULL},
#if ((defined(M_LOCAL) || defined(M_REMOTE)) && defined(RELAY_BUILT_IN))
    /* 【负荷开关误动记录】 */
    {{REV4(0x03,   0x36,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03360000), NULL, NULL},
    {{REV4(0x03,   0x36,         0x00,   BI03360101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03360001[0]), NULL, NULL},
#endif        
    /* 【电源异常记录】 */
    {{REV4(0x03,   0x37,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03370000), NULL, NULL},
    {{REV4(0x03,   0x37,         0x00,   BI03370101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03370001[0]), NULL, NULL},

//    {{REV4(0x03,   0x80,         0x01,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03800100), NULL, NULL},
//    {{REV4(0x03,   0x80,         0x01,   BI03800101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03800101[0]), NULL, NULL},

    
    {{REV4(0x04,   0x00,         0x01,         0x01)}, 0x0014, sizeof(ra04000101), (uint32_t)0,    fn04000101, &ds04000101_3},
    {{REV4(0x04,   0x00,         0x01,         0x02)}, 0x0014, sizeof(ra04000102), (uint32_t)0,    fn04000102, &ds04000102_1},
//    {{REV4(0x04,   0x00,         0x01,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000103), fn04000103, &ds04000103},
//    {{REV4(0x04,   0x00,         0x01,         0x04)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000104), fn04000104, &ds04000104},
    {{REV4(0x04,   0x00,         0x01,         0x05)}, 0x0000, sizeof(ro04000105), (uint32_t)&ro04000105[0], fn04000105, NULL},
    {{REV4(0x04,   0x00,         0x01,         0x06)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000106), fn04000106, &ds04000106},
    {{REV4(0x04,   0x00,         0x01,         0x07)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000107), fn04000106, &ds04000107},
#if defined(M_LOCAL)
    /* 【两套费率切换时间】【两套阶梯切换时间】  */
    {{REV4(0x04,   0x00,         0x01,         0x08)}, 0x0057, SIZE_ADDR_OF(EE_sect2, ee04000108), fn04000108, &ds04000108},
    {{REV4(0x04,   0x00,         0x01,         0x09)}, 0x0057, SIZE_ADDR_OF(EE_sect2, ee04000109), fn04000109, &ds04000109},
#endif
    {{REV4(0x04,   0x00,         0x01,         0x0C)}, 0x0014, 0x07                 , (uint32_t)0, fn0400010C, NULL},        
#if defined(M_LOCAL)|| defined(M_REMOTE)
    {{REV4(0x04,   0x00,         0x01,         0xFC)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee040001FC), fn040001FC, NULL},
    {{REV4(0x04,   0x00,         0x01,         0xFE)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee040001FE), fn040001FE, &ds040001FE},
#endif
    {{REV4(0x04,   0x00,         0x02,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000201), fn04000201, &ds04000201},
    {{REV4(0x04,   0x00,         0x02,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000202), fn04000202, &ds04000202},
    {{REV4(0x04,   0x00,         0x02,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000203), fn04000203, &ds04000203},
    {{REV4(0x04,   0x00,         0x02,         0x04)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000204), fn04000204, &ds04000204},
    {{REV4(0x04,   0x00,         0x02,         0x05)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000205), fn04000205, &ds04000205},
#if defined(M_SMART)
    /* 【谐波分析次数】 */
    {{REV4(0x04,   0x00,         0x02,         0x06)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000206), fn04000206, &ds04000206},
#endif
#if defined(M_LOCAL)
    {{REV4(0x04,   0x00,         0x02,         0x07)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000207), fn04000207, &ds04000207},
#endif        
    {{REV4(0x04,   0x00,         0x02,         0x08)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04000208), fn04000208, NULL},        
    {{REV4(0x04,   0x00,         0x02,         0xFE)}, 0x0424, sizeof(ra_timeCheckoutMAC), (uint32_t)&ra_timeCheckoutMAC, NULL, NULL},
    {{REV4(0x04,   0x00,         0x03,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000301), fn04000301, &ds04000301},
    {{REV4(0x04,   0x00,         0x03,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000302), fn04000302, &ds04000302},
    {{REV4(0x04,   0x00,         0x03,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000303), fn04000303, &ds04000303},
    {{REV4(0x04,   0x00,         0x03,         0x04)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000304), fn04000304, &ds04000304},
    {{REV4(0x04,   0x00,         0x03,         0x05)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000305), fn04000305, &ds04000305},
    {{REV4(0x04,   0x00,         0x03,         0x06)}, 0x0057, SIZE_ADDR_OF(EE_sect2, ee04000306), fn04000306, &ds04000306},
    {{REV4(0x04,   0x00,         0x03,         0x07)}, 0x0057, SIZE_ADDR_OF(EE_sect2, ee04000307), fn04000306, &ds04000307},
    {{REV4(0x04,   0x00,         0x03,         0x08)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000308), fn04000308, NULL},
    {{REV4(0x04,   0x00,         0x03,         0xEA)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee040003EA), fn040003EA, NULL},
    {{REV4(0x04,   0x00,         0x03,         0xFA)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee040003FA), fn040003FA, NULL},
    {{REV4(0x04,   0x00,         0x03,         0xFB)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee040003FB), fn040003FB, NULL},
    {{REV4(0x04,   0x00,         0x03,         0xFC)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee040003FC), fn040003FC, NULL},
    {{REV4(0x04,   0x00,         0x03,         0xFE)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee040003FE), fn040003FE, NULL},

    {{REV4(0x04,   0x00,         0x04,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000401), fn04000401, &ds04000401},
    {{REV4(0x04,   0x00,         0x04,         0x02)}, 0x0057, SIZE_ADDR_OF(EE_sect2, ee04000402), fn04000402, &ds04000402},
    {{REV4(0x04,   0x00,         0x04,         0x03)}, 0x0854, SIZE_ADDR_OF(EE_sect2, ee04000403), fn04000403, NULL},
    {{REV4(0x04,   0x00,         0x04,         0x04)}, 0x0860, SIZE_ADDR_OF(EE_sect2, ee04000404), fn04000404, NULL},
    {{REV4(0x04,   0x00,         0x04,         0x05)}, 0x0860, SIZE_ADDR_OF(EE_sect2, ee04000405), fn04000405, NULL},
    {{REV4(0x04,   0x00,         0x04,         0x06)}, 0x0860, SIZE_ADDR_OF(EE_sect2, ee04000406), fn04000406, NULL},
    {{REV4(0x04,   0x00,         0x04,         0x07)}, 0x0860, SIZE_ADDR_OF(EE_sect2, ee04000407), fn04000407, NULL},
//    {{REV4(0x04,   0x00,         0x04,         0x08)}, 0x0860, SIZE_ADDR_OF(EE_sect2, ee04000408), fn04000408, NULL},
    {{REV4(0x04,   0x00,         0x04,         0x09)}, 0x0060, SIZE_ADDR_OF(EE_sect2, ee04000409), fn04000409, &ds04000409},
//    {{REV4(0x04,   0x00,         0x04,         0x0A)}, 0x0060, SIZE_ADDR_OF(EE_sect2, ee0400040A), fn0400040A, &ds0400040A},
    {{REV4(0x04,   0x00,         0x04,         0x0B)}, 0x0860, SIZE_ADDR_OF(EE_sect2, ee0400040B), fn0400040B, NULL},
    {{REV4(0x04,   0x00,         0x04,         0x0C)}, 0x0860, SIZE_ADDR_OF(EE_sect2, ee0400040C), fn0400040C, NULL},
    {{REV4(0x04,   0x00,         0x04,         0x0D)}, 0x0800, sizeof(ro0400040D), (uint32_t)&ro0400040D[0], NULL, NULL},
    {{REV4(0x04,   0x00,         0x04,         0x0E)}, 0x0057, SIZE_ADDR_OF(EE_sect2, ee0400040E), fn0400040E, &ds0400040E},
    {{REV4(0x04,   0x00,         0x04,         0x0F)}, 0x041C, SIZE_ADDR_OF(EE_sect2, ee0400040F), fn0400040F, NULL},
    {{REV4(0x04,   0x00,         0x05,   CI04000501)}, 0x1400, sizeof(ra04000501[0]), (uint32_t)&ra04000501[0], fn04000501, &ds04000501},
    {{REV4(0x04,   0x00,         0x05,         0x08)}, 0x0400, SIZE_ADDR_OF(EE_sect7, ee04000508), NULL,       NULL},        
    {{REV4(0x04,   0x00,         0x06,         0x01)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04000601   ), fn04000601, &ds04000601},
//    {{REV4(0x04,   0x00,         0x06,   CI04000602)}, 0x1454, SIZE_ADDR_OF(EE_sect2, ee04000602[0]), fn04000602, &ds04000602},
    {{REV4(0x04,   0x00,         0x07,         0x01)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04000701), fn04000701, &ds04000701},
/*不支持数据
    {{REV4(0x04,   0x00,         0x07,         0x02)}, 0x0414, sizeof(ra04000702), (uint32_t)&ra04000702, fn04000702, &ds04000702},
*/
    {{REV4(0x04,   0x00,         0x07,   CI04000703)}, 0x1454, SIZE_ADDR_OF(EE_sect2, ee04000703[0]), fn04000703, &ds04000703},
    {{REV4(0x04,   0x00,         0x08,         0x01)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04000801   ), fn04000801, NULL},
    {{REV4(0x04,   0x00,         0x08,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000802   ), fn04000802, NULL},
    {{REV4(0x04,   0x00,         0x09,         0x01)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04000901   ), fn04000901, &ds04000901},
    {{REV4(0x04,   0x00,         0x09,         0x02)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04000902   ), fn04000902, &ds04000902},
    {{REV4(0x04,   0x00,         0x09,         0x03)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04000903   ), fn04000903, &ds04000903},
    {{REV4(0x04,   0x00,         0x09,         0x04)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04000904   ), fn04000904, &ds04000904},
    {{REV4(0x04,   0x00,         0x09,         0x05)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04000905   ), fn04000905, &ds04000905},
    {{REV4(0x04,   0x00,         0x09,         0x06)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04000906   ), fn04000906, &ds04000906},
    {{REV4(0x04,   0x00,         0x0A,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000A01   ), fn04000A01, NULL},
    {{REV4(0x04,   0x00,         0x0A,   CI04000A02)}, 0x1054, SIZE_ADDR_OF(EE_sect2, ee04000A02[0]), fn04000A02, NULL},
    {{REV4(0x04,   0x00,         0x0B,   CI04000B01)}, 0x1054, SIZE_ADDR_OF(EE_sect2, ee04000B01[0]), fn04000B01, &ds04000B01},
    {{REV4(0x04,   0x00,         0x0C,         0x01)}, 0x00F0, SIZE_ADDR_OF(EE_sect2, ee04000C01[0]), fn04000C01, NULL},
    {{REV4(0x04,   0x00,         0x0C,         0x02)}, 0x00F1, SIZE_ADDR_OF(EE_sect2, ee04000C01[1]), fn04000C01, NULL},
    {{REV4(0x04,   0x00,         0x0C,         0x03)}, 0x00F2, SIZE_ADDR_OF(EE_sect2, ee04000C01[2]), fn04000C01, NULL},
    {{REV4(0x04,   0x00,         0x0C,         0x04)}, 0x00F3, SIZE_ADDR_OF(EE_sect2, ee04000C01[3]), fn04000C01, NULL},
    {{REV4(0x04,   0x00,         0x0C,         0x05)}, 0x00F4, SIZE_ADDR_OF(EE_sect2, ee04000C01[4]), fn04000C01, NULL},
    {{REV4(0x04,   0x00,         0x0C,         0x06)}, 0x00F5, SIZE_ADDR_OF(EE_sect2, ee04000C01[5]), fn04000C01, NULL},
//    {{REV4(0x04,   0x00,         0x0C,         0x07)}, 0x00F6, SIZE_ADDR_OF(EE_sect2, ee04000C01[6]), fn04000C01, NULL},
//    {{REV4(0x04,   0x00,         0x0C,         0x08)}, 0x00F7, SIZE_ADDR_OF(EE_sect2, ee04000C01[7]), fn04000C01, NULL},
//    {{REV4(0x04,   0x00,         0x0C,         0x09)}, 0x00F8, SIZE_ADDR_OF(EE_sect2, ee04000C01[8]), fn04000C01, NULL},
//    {{REV4(0x04,   0x00,         0x0C,         0x0A)}, 0x00F9, SIZE_ADDR_OF(EE_sect2, ee04000C01[9]), fn04000C01, NULL},
    {{REV4(0x04,   0x00,         0x0C,         0xFE)}, 0x0012, sizeof(ra04000CFE), (uint32_t)&ra04000CFE, NULL, NULL},
//    {{REV4(0x04,   0x00,         0x0D,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[0].ee04000D01), fn04000D01, NULL},
    //{{REV4(0x04,   0x00,         0x0D,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[0].ee04000D02), fn04000D02, NULL},
//    {{REV4(0x04,   0x00,         0x0D,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[0].ee04000D03), fn04000D03, NULL},
    //{{REV4(0x04,   0x00,         0x0D,         0x04)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[0].ee04000D04), fn04000D04, NULL},
//    {{REV4(0x04,   0x00,         0x0D,         0x05)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[1].ee04000D01), fn04000D01, NULL},
    //{{REV4(0x04,   0x00,         0x0D,         0x06)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[1].ee04000D02), fn04000D02, NULL},
//    {{REV4(0x04,   0x00,         0x0D,         0x07)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[1].ee04000D03), fn04000D03, NULL},
    //{{REV4(0x04,   0x00,         0x0D,         0x08)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[1].ee04000D04), fn04000D04, NULL},
//    {{REV4(0x04,   0x00,         0x0D,         0x09)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[2].ee04000D01), fn04000D01, NULL},
    //{{REV4(0x04,   0x00,         0x0D,         0x0A)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[2].ee04000D02), fn04000D02, NULL},
//    {{REV4(0x04,   0x00,         0x0D,         0x0B)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[2].ee04000D03), fn04000D03, NULL},
    //{{REV4(0x04,   0x00,         0x0D,         0x0C)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[2].ee04000D04), fn04000D04, NULL},
//    {{REV4(0x04,   0x00,         0x0E,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000E01), fn04000E01, NULL},
//    {{REV4(0x04,   0x00,         0x0E,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000E02), fn04000E02, NULL},
//    {{REV4(0x04,   0x00,         0x0E,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000E03), fn04000E03, NULL},
//    {{REV4(0x04,   0x00,         0x0E,         0x04)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000E04), fn04000E04, NULL},
        
#if defined(M_LOCAL)
    /* 【报警金额1，2限值、透支金额限值、囤积金额限值、合闸允许金额限值】 */
    {{REV4(0x04,   0x00,         0x10,         0x01)}, 0x0057, SIZE_ADDR_OF(EE_sect2, ee04001001), fn04001001, &ds04001001},
    {{REV4(0x04,   0x00,         0x10,         0x02)}, 0x0057, SIZE_ADDR_OF(EE_sect2, ee04001002), fn04001001, &ds04001002},
    {{REV4(0x04,   0x00,         0x10,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04001003), fn04001001, &ds04001003},
    {{REV4(0x04,   0x00,         0x10,         0x04)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04001004), fn04001001, &ds04001004},
    {{REV4(0x04,   0x00,         0x10,         0x05)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04001005), fn04001001, &ds04001005},
    {{REV4(0x04,   0x00,         0x10,         0x06)}, 0x0094, 4,                  (uint32_t)0,    fn04001006, NULL},        
#endif

    {{REV4(0x04,   0x00,         0x11,         0x01)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04001101), fn04001101, &ds04001101},
    {{REV4(0x04,   0x00,         0x11,         0x04)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04001104), fn04001104, NULL},
    {{REV4(0x04,   0x00,         0x12,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04001201), fn04001201, NULL},
    {{REV4(0x04,   0x00,         0x12,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04001202), fn04001202, NULL},
    {{REV4(0x04,   0x00,         0x12,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04001203), fn04001203, NULL},
    {{REV4(0x04,   0x00,         0x12,         0x04)}, 0x0000, 0x04     , (uint32_t)&fr.fr04001204, NULL     , &ds04001204}, 
    {{REV4(0x04,   0x00,         0x13,         0x01)}, 0x0014, sizeof(ra04001301), (uint32_t)&ra04001301[0], fn04001301, &ds04001301}, 
#if defined(M_REMOTE) || defined(M_LOCAL)
    {{REV4(0x04,   0x00,         0x14,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04001401), fn04001401, &ds04001401},
#endif
    {{REV4(0x04,   0x00,         0x15,         0x01)}, 0x0400, sizeof(ra04001501), (uint32_t)&ra04001501[0], NULL, NULL},
#if defined(M_LOCAL)
    {{REV4(0x04,   0x00,         0x15,         0x02)}, 0x0400, sizeof(ra04001502), (uint32_t)&ra04001502, NULL, NULL},
#endif
    {{REV4(0x04, CI04010000,     0x00,         0x00)}, 0x405C, SIZE_ADDR_OF(EE_sect2, ee040100ZZ[0].ee04ZZ0000   ), fn04010000, &ds04010000},
    {{REV4(0x04, CI04010000,     0x00,   CI04010001)}, 0x505C, SIZE_ADDR_OF(EE_sect2, ee040100ZZ[0].ee04ZZ0001[0]), fn04010001, &ds04010001},
    {{REV4(0x04,   0x03,         0x00,   CI04030001)}, 0x1054, SIZE_ADDR_OF(EE_sect2, ee04030001[0]), fn04030001, NULL},
    {{REV4(0x04,   0x04,         0x01,   CI04040101)}, 0x141C, SIZE_ADDR_OF(EE_sect2, ee04040101[0]), fn04040101, NULL},
    {{REV4(0x04,   0x04,         0x02,   CI04040201)}, 0x141C, SIZE_ADDR_OF(EE_sect2, ee04040201[0]), fn04040201, NULL},
    {{REV4(0x04,   0x04,         0x03,         0x00)}, 0x0000, SIZE_OF(EE_sect2, ee04040101[0]), (uint32_t)0, fn04040300, NULL},

#if defined(M_LOCAL)
    // 当前/备用套 费率数据单条 读
    {{REV4(0x04,   0x05,     CI04050100, CI04050101)}, 0x3000, SIZE_ADDR_OF(EE_sect2,  ee0405ZZFF[0].m_0405ZZMO[0]), fn04050101, &ds04050101}, 
    // 当前套      费率数据块   读
    {{REV4(0x04,   0x05,         0x02,         0xFD)}, 0x000F, 4*TMN, 0, fn0405ZZFF, NULL}, 
    // 备用套      费率数据块   读写
    {{REV4(0x04,   0x05,         0x02,         0xFE)}, 0x001F, 4*TMN, 0, fn0405ZZFF, NULL},
    
    {{REV4(0x04,   0x06,         0x04,   CI0406ZZEN)}, 0x1000, 4, (uint32_t)&ra040604FF.m_0406ZZEN[0], NULL, &ds040604EN},
    {{REV4(0x04,   0x06,         0x04,   CI0406ZZMO)}, 0x1000, 4, (uint32_t)&ra040604FF.m_0406ZZMO[0], NULL, &ds040604MO},
    {{REV4(0x04,   0x06,         0x04,   CI0406ZZYS)}, 0x1000, 3, (uint32_t)&ra040604FF.m_0406ZZYS[0], NULL, &ds040604YS}, 
    // 当前套      阶梯数据块   读
    {{REV4(0x04,   0x06,         0x04,         0xFE)}, 0x000F, SIZE_ADDR_OF(EE_sect2, ee0406ZZFF[0]), fn0406ZZFF, NULL}, 
    // 备用套      阶梯数据块   读写
    {{REV4(0x04,   0x06,         0x05,         0xFE)}, 0x001F, SIZE_ADDR_OF(EE_sect2, ee0406ZZFF[1]), fn0406ZZFF, NULL},        
#endif    
/*
    {{REV4(0x04,   0x09,         0x01,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090101), fn04090101, &ds04090101},
    {{REV4(0x04,   0x09,         0x01,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090102), fn04090102, &ds04090102},
    {{REV4(0x04,   0x09,         0x01,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090103), fn04090103, &ds04090103},
    {{REV4(0x04,   0x09,         0x01,         0x04)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090104), fn04090104, &ds04090104},
    {{REV4(0x04,   0x09,         0x02,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090201), fn04090201, &ds04090201},
    {{REV4(0x04,   0x09,         0x02,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090202), fn04090202, &ds04090202},
    {{REV4(0x04,   0x09,         0x03,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090301), fn04090301, &ds04090301},
    {{REV4(0x04,   0x09,         0x03,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090302), fn04090302, &ds04090302},
    {{REV4(0x04,   0x09,         0x04,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090401), fn04090401, &ds04090401},
    {{REV4(0x04,   0x09,         0x04,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090402), fn04090402, &ds04090402},
    {{REV4(0x04,   0x09,         0x04,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090403), fn04090403, &ds04090403},
    {{REV4(0x04,   0x09,         0x05,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090501), fn04090501, &ds04090501},
    {{REV4(0x04,   0x09,         0x05,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090502), fn04090502, &ds04090502},
    {{REV4(0x04,   0x09,         0x06,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090601), fn04090601, &ds04090601},
    {{REV4(0x04,   0x09,         0x06,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090602), fn04090602, &ds04090602},
    {{REV4(0x04,   0x09,         0x07,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090701), fn04090701, &ds04090701},
    {{REV4(0x04,   0x09,         0x07,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090702), fn04090702, &ds04090702},
    {{REV4(0x04,   0x09,         0x07,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090703), fn04090703, &ds04090703},
    {{REV4(0x04,   0x09,         0x07,         0x04)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090704), fn04090704, &ds04090704},
    {{REV4(0x04,   0x09,         0x08,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090801), fn04090801, &ds04090801},
    {{REV4(0x04,   0x09,         0x08,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090802), fn04090802, &ds04090802},
    {{REV4(0x04,   0x09,         0x09,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090901), fn04090901, &ds04090901},
    {{REV4(0x04,   0x09,         0x09,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090902), fn04090902, &ds04090902},
    {{REV4(0x04,   0x09,         0x09,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090903), fn04090903, &ds04090903},
    {{REV4(0x04,   0x09,         0x0A,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090A01), fn04090A01, &ds04090A01},
    {{REV4(0x04,   0x09,         0x0A,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090A02), fn04090A02, &ds04090A02},
    {{REV4(0x04,   0x09,         0x0B,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090B01), fn04090B01, &ds04090B01},
    {{REV4(0x04,   0x09,         0x0B,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090B02), fn04090B02, &ds04090B02},
    {{REV4(0x04,   0x09,         0x0C,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090C01), fn04090C01, &ds04090C01},
    {{REV4(0x04,   0x09,         0x0C,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090C02), fn04090C02, &ds04090C02},
    {{REV4(0x04,   0x09,         0x0D,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090D01), fn04090D01, &ds04090D01},
    {{REV4(0x04,   0x09,         0x0D,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090D02), fn04090D02, &ds04090D02},
    {{REV4(0x04,   0x09,         0x0D,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090D03), fn04090D03, &ds04090D03},
    {{REV4(0x04,   0x09,         0x0E,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090E01), fn04090E01, &ds04090E01},
    {{REV4(0x04,   0x09,         0x0E,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090E02), fn04090E02, &ds04090E02},
    {{REV4(0x04,   0x09,         0x0F,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090F01), fn04090F01, &ds04090F01},
    {{REV4(0x04,   0x09,         0x0F,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090F02), fn04090F02, &ds04090F02},    
    {{REV4(0x04,   0x09,         0x10,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04091001), fn04091001, NULL},
    {{REV4(0x04,   0x09,         0x10,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04091002), fn04091002, NULL},
*/
    {{REV4(0x04,   0x80,         0x00,         0x01)}, 0x0860, SIZE_ADDR_OF(EE_sect2, ee04800001), fn04800001, &ds04800001},
    {{REV4(0x04,   0x80,         0x00,         0x02)}, 0x0860, SIZE_ADDR_OF(EE_sect2, ee04800002), fn04800002, NULL/*&ds04800002*/},
    {{REV4(0x04,   0x80,         0x00,         0x03)}, 0x0860, SIZE_ADDR_OF(EE_sect2, ee04800003), fn04800003, NULL/*&ds04800003*/},
    {{REV4(0x04,   0x80,         0x00,         0x04)}, 0x0460, SIZE_ADDR_OF(EE_sect2, ee04800004), fn04800004, NULL/*&ds04800004*/},

    {{REV4(0x05,   0x00,         0x00,   BI05000001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0500ZZ01[0].m_05ZZ00ZZ   ), NULL      , &ds05000001},
    {{REV4(0x05,   0x00,         0x01,   BI05000001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0500ZZ01[0].m_05ZZ01ZZ   ), fn05000101, &ds05000101},
    {{REV4(0x05,   0x00,         0x02,   BI05000001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0500ZZ01[0].m_05ZZ02ZZ   ), fn05000101, &ds05000201},
//    {{REV4(0x05,   0x00,     CI05000301, BI05000001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0500ZZ01[0].m_05ZZ03ZZ[0]), fn05000101, &ds05000301},
//    {{REV4(0x05,   0x00,     CI05000501, BI05000001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0500ZZ01[0].m_05ZZ05ZZ[0]), fn05000101, &ds05000501},
//    {{REV4(0x05,   0x00,         0x09,   BI05000001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0500ZZ01[0].m_05ZZ09ZZ   ), fn05000901, &ds05000901},
//    {{REV4(0x05,   0x00,         0x0A,   BI05000001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0500ZZ01[0].m_05ZZ0AZZ   ), fn05000901, &ds05000A01},
    {{REV4(0x05,   0x00,         0x10,   BI05000001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0500ZZ01[0].m_05ZZ10ZZ   ), fn05001001, &ds05001001},
    {{REV4(0x05,   0x01,         0x00,   BI05010001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0501ZZ01[0].m_05ZZ00ZZ   ), NULL      , &ds05010001},
    {{REV4(0x05,   0x01,         0x01,   BI05010001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0501ZZ01[0].m_05ZZ01ZZ   ), fn05000101, &ds05010101},
    {{REV4(0x05,   0x01,         0x02,   BI05010001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0501ZZ01[0].m_05ZZ02ZZ   ), fn05000101, &ds05010201},
//    {{REV4(0x05,   0x01,     CI05000301, BI05010001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0501ZZ01[0].m_05ZZ03ZZ[0]), fn05000101, &ds05010301},
//    {{REV4(0x05,   0x01,     CI05000501, BI05010001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0501ZZ01[0].m_05ZZ05ZZ[0]), fn05000101, &ds05010501},
//    {{REV4(0x05,   0x01,         0x09,   BI05010001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0501ZZ01[0].m_05ZZ09ZZ   ), fn05000901, &ds05010901},
//    {{REV4(0x05,   0x01,         0x0A,   BI05010001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0501ZZ01[0].m_05ZZ0AZZ   ), fn05000901, &ds05010A01},
    {{REV4(0x05,   0x01,         0x10,   BI05010001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0501ZZ01[0].m_05ZZ10ZZ   ), fn05001001, &ds05011001},
    {{REV4(0x05,   0x02,         0x00,   BI05020001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0502ZZ01[0].m_05ZZ00ZZ   ), NULL      , &ds05020001},
    {{REV4(0x05,   0x02,         0x01,   BI05020001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0502ZZ01[0].m_05ZZ01ZZ   ), fn05000101, &ds05020101},
    {{REV4(0x05,   0x02,         0x02,   BI05020001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0502ZZ01[0].m_05ZZ02ZZ   ), fn05000101, &ds05020201},
//    {{REV4(0x05,   0x02,     CI05000301, BI05020001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0502ZZ01[0].m_05ZZ03ZZ[0]), fn05000101, &ds05020301},
//    {{REV4(0x05,   0x02,     CI05000501, BI05020001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0502ZZ01[0].m_05ZZ05ZZ[0]), fn05000101, &ds05020501},
//    {{REV4(0x05,   0x02,         0x09,   BI05020001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0502ZZ01[0].m_05ZZ09ZZ   ), fn05000901, &ds05020901},
//    {{REV4(0x05,   0x02,         0x0A,   BI05020001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0502ZZ01[0].m_05ZZ0AZZ   ), fn05000901, &ds05020A01},
    {{REV4(0x05,   0x02,         0x10,   BI05020001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0502ZZ01[0].m_05ZZ10ZZ   ), fn05001001, &ds05021001},
    {{REV4(0x05,   0x03,         0x00,   BI05030001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0503ZZ01[0].m_05ZZ00ZZ   ), NULL      , &ds05030001},
    {{REV4(0x05,   0x03,         0x01,   BI05030001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0503ZZ01[0].m_05ZZ01ZZ   ), fn05000101, &ds05030101},
    {{REV4(0x05,   0x03,         0x02,   BI05030001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0503ZZ01[0].m_05ZZ02ZZ   ), fn05000101, &ds05030201},
//    {{REV4(0x05,   0x03,     CI05000301, BI05030001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0503ZZ01[0].m_05ZZ03ZZ[0]), fn05000101, &ds05030301},
//    {{REV4(0x05,   0x03,     CI05000501, BI05030001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0503ZZ01[0].m_05ZZ05ZZ[0]), fn05000101, &ds05030501},
//    {{REV4(0x05,   0x03,         0x09,   BI05030001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0503ZZ01[0].m_05ZZ09ZZ   ), fn05000901, &ds05030901},
//    {{REV4(0x05,   0x03,         0x0A,   BI05030001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0503ZZ01[0].m_05ZZ0AZZ   ), fn05000901, &ds05030A01},
    {{REV4(0x05,   0x03,         0x10,   BI05030001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0503ZZ01[0].m_05ZZ10ZZ   ), fn05001001, &ds05031001},
    {{REV4(0x05,   0x04,         0x00,   BI05040001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0504ZZ01[0].m_050400ZZ   ), NULL      , &ds05040001},
    {{REV4(0x05,   0x04,         0x01,   BI05040001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0504ZZ01[0].m_050401ZZ   ), fn05040101, &ds05040101},
    {{REV4(0x05,   0x04,         0x02,   BI05040001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0504ZZ01[0].m_050402ZZ   ), fn05040101, &ds05040201},
#if defined(M_LOCAL)
    /* 【两套费率表切换冻结】 */
    {{REV4(0x05,   0x05,         0x00,   BI05050001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0505ZZ01[0].m_05ZZ00ZZ   ), NULL      , &ds05050001},
    {{REV4(0x05,   0x05,         0x01,   BI05050001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0505ZZ01[0].m_05ZZ01ZZ   ), fn05000101, &ds05050101},
    {{REV4(0x05,   0x05,         0x02,   BI05050001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0505ZZ01[0].m_05ZZ02ZZ   ), fn05000101, &ds05050201},
//    {{REV4(0x05,   0x05,     CI05000301, BI05050001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0505ZZ01[0].m_05ZZ03ZZ[0]), fn05000101, &ds05050301},
//    {{REV4(0x05,   0x05,     CI05000501, BI05050001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0505ZZ01[0].m_05ZZ05ZZ[0]), fn05000101, &ds05050501},
//    {{REV4(0x05,   0x05,         0x09,   BI05050001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0505ZZ01[0].m_05ZZ09ZZ   ), fn05000901, &ds05050901},
//    {{REV4(0x05,   0x05,         0x0A,   BI05050001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0505ZZ01[0].m_05ZZ0AZZ   ), fn05000901, &ds05050A01},
    {{REV4(0x05,   0x05,         0x10,   BI05050001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0505ZZ01[0].m_05ZZ10ZZ   ), fn05001001, &ds05051001},
#endif
    {{REV4(0x05,   0x06,         0x00,   BI05060001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0506ZZ01[0].m_050600ZZ     ), NULL      , &ds05060001},
    {{REV4(0x05,   0x06,         0x01,   BI05060001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0506ZZ01[0].m_050601ZZ     ), fn05000101, &ds05060101},
    {{REV4(0x05,   0x06,         0x02,   BI05060001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0506ZZ01[0].m_050602ZZ     ), fn05000101, &ds05060201},
//    {{REV4(0x05,   0x06,     CI05000301, BI05060001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0506ZZ01[0].m_050603ZZ[0]  ), fn05000101, &ds05060301},
//    {{REV4(0x05,   0x06,     CI05000501, BI05060001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0506ZZ01[0].m_050605ZZ[0]  ), fn05000101, &ds05060501},
//    {{REV4(0x05,   0x06,         0x09,   BI05060001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0506ZZ01[0].m_050609ZZ     ), fn05000901, &ds05060901},
//    {{REV4(0x05,   0x06,         0x0A,   BI05060001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0506ZZ01[0].m_05060AZZ     ), fn05000901, &ds05060A01},
    {{REV4(0x05,   0x06,         0x10,   BI05060001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0506ZZ01[0].m_050610ZZ     ), fn05001001, &ds05061001},

    {{REV4(0x05,   0x07,         0x00,   BI05070001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0507ZZ01[0].m_05ZZ00ZZ   ), NULL      , &ds05070001},
    {{REV4(0x05,   0x07,         0x01,   BI05070001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0507ZZ01[0].m_05ZZ01ZZ   ), fn05000101, &ds05070101},
    {{REV4(0x05,   0x07,         0x02,   BI05070001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0507ZZ01[0].m_05ZZ02ZZ   ), fn05000101, &ds05070201},
//    {{REV4(0x05,   0x07,     CI05000301, BI05070001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0507ZZ01[0].m_05ZZ03ZZ[0]), fn05000101, &ds05070301},
//    {{REV4(0x05,   0x07,     CI05000501, BI05070001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0507ZZ01[0].m_05ZZ05ZZ[0]), fn05000101, &ds05070501},
//    {{REV4(0x05,   0x07,         0x09,   BI05070001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0507ZZ01[0].m_05ZZ09ZZ   ), fn05000901, &ds05070901},
//    {{REV4(0x05,   0x07,         0x0A,   BI05070001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0507ZZ01[0].m_05ZZ0AZZ   ), fn05000901, &ds05070A01},
    {{REV4(0x05,   0x07,         0x10,   BI05070001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0507ZZ01[0].m_05ZZ10ZZ   ), fn05001001, &ds05071001},
#if defined(M_LOCAL)
    {{REV4(0x05,   0x08,         0x02,   BI05060001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0506ZZ01[0].m_050802ZZ     ), NULL, &ds05080201},
#endif
    {{REV4(0x06,   0x00,         0x00,         0x00)}, 0x0000, 0, 0x00000000, fn06000000, NULL},
    {{REV4(0x06,   0x00,         0x00,         0x01)}, 0x0000, 0, 0x00000000, fn06000000, NULL},
    {{REV4(0x06,   0x00,         0x00,         0x02)}, 0x0000, 0, 0x00000000, fn06000002, NULL},
    {{REV4(0x06, CI06010000,     0x00,         0x00)}, 0x4000, 0, 0x00000000, fn06010000, NULL},
    {{REV4(0x06, CI06010000,     0x00,         0x01)}, 0x4000, 0, 0x00000000, fn06010000, NULL},
    {{REV4(0x06, CI06010000,     0x00,         0x02)}, 0x4000, 0, 0x00000000, fn06010002, NULL},

#if defined (MEASURECHIP_ATT7022E)
    {{REV4(0x0D,   0x00,         0x00,         0x00)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000000 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x01)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000001 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x02)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000002 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x03)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000003 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x04)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000004 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x05)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000005 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x06)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000006 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x07)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000007 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x08)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000008 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x09)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000009 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x0A)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00000A ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x0B)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00000B ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x0C)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00000C ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x0D)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00000D ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x0E)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00000E ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x0F)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00000F ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x10)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000010 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x11)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000011 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x12)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000012 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x13)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000013 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x14)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000014 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x15)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000015 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x16)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000016 ), fn0D000016, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x17)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000017 ), fn0D000016, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x18)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000018 ), fn0D000016, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x19)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000019 ), fn0D000016, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x1A)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00001A ), fn0D000016, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x1B)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00001B ), fn0D000016, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x1C)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00001C ), fn0D00001C, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x1D)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00001D ), fn0D00001C, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x1E)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00001E ), fn0D00001C, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x1F)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00001F ), fn0D00001C, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x20)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000020 ), fn0D00001C, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x21)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000021 ), fn0D00001C, NULL},
    
    {{REV4(0x0D,   0x01,         0x00,         0x01)}, 0x0020, sizeof(ra_APCF), (uint32_t)&ra_APCF[0] , NULL   , NULL},
    {{REV4(0x0D,   0x01,         0x00,         0x02)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D010002 ), fn0D010002, NULL},
    {{REV4(0x0D,   0x01,         0x00,         0x03)}, 0x0060, SIZE_ADDR_OF(FR_sect0, fr0D010003 ), fn0D010003, NULL},
    {{REV4(0x0D,   0x01,         0x00,         0x04)}, 0x0060, SIZE_ADDR_OF(FR_sect0, fr0D010004 ), fn0D010004, NULL},
    {{REV4(0x0D,   0x01,         0x00,         0x05)}, 0x0060, SIZE_ADDR_OF(FR_sect0, fr0D010005 ), fn0D010005, NULL},
    {{REV4(0x0D,   0x0D,         0x01,         0x00)}, 0x0020, 0, 0x00000000, fn0D0D0100, NULL},
    {{REV4(0x0D,   0x0D,         0x02,         0x00)}, 0x0020, 0, 0x00000000, fn0D0D0200, NULL},
    {{REV4(0x0D,   0x0D,         0x03,         0x00)}, 0x0020, 0, 0x00000000, fn0D0D0300, NULL},
    {{REV4(0x0D,   0x0D,         0x04,         0x00)}, 0x0020, 0, 0x00000000, fn0D0D0400, NULL},
    {{REV4(0x0D,   0x0D,         0x05,         0x00)}, 0x0020, 0, 0x00000000, NULL, NULL},
#elif defined (MEASURECHIP_ADE7858)
    {{REV4(0x0E,   0x00,         0x00,         0x00)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000000 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x01)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000001 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x02)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000002 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x03)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000003 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x04)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000004 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x05)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000005 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x06)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000006 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x07)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000007 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x08)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000008 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x09)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000009 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x0A)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00000A ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x0B)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00000B ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x0C)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00000C ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x0D)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00000D ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x0E)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00000E ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x0F)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00000F ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x10)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000010 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x11)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000011 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x12)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000012 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x13)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000013 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x14)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000014 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x15)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000015 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x16)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000016 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x17)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000017 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x18)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000018 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x19)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000019 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x1A)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00001A ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x1B)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00001B ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x1C)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00001C ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x1D)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00001D ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x1E)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00001E ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x1F)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00001F ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x20)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000020 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x21)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000021 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x22)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000022 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x23)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000023 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x24)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000024 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x25)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000025 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x26)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000026 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x27)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000027 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x28)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000028 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x29)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000029 ), fn0E000029, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x2a)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00002a ), fn0E000029, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x2b)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00002b ), fn0E000029, NULL},   
    {{REV4(0x0E,   0x00,         0x00,         0x2c)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00002c ), fn0E00002c, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x2d)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00002d ), fn0E00002c, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x2e)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00002e ), fn0E00002c, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x2f)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00002f ), fn0E00002c, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x30)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000030 ), fn0E00002c, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x31)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000031 ), fn0E00002c, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x32)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000032 ), fn0E000032, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x33)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000033 ), fn0E000032, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x34)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000034 ), fn0E000032, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x35)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000035 ), fn0E000032, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x36)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000036 ), fn0E000032, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x37)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000037 ), fn0E000032, NULL},
    {{REV4(0x0E,   0x01,         0x00,         0x01)}, 0x0020, sizeof(ra_APCF), (uint32_t)&ra_APCF[0] , NULL   , NULL},
    {{REV4(0x0E,   0x01,         0x00,         0x02)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E010002 ), fn0E010002, NULL},
    {{REV4(0x0E,   0x01,         0x00,         0x03)}, 0x0060, SIZE_ADDR_OF(FR_sect0, fr0E010003 ), fn0E010003, NULL},
    {{REV4(0x0E,   0x0E,         0x01,         0x00)}, 0x0020, 0, 0x00000000, fn0E0E0100, NULL},
    {{REV4(0x0E,   0x0E,         0x02,         0x00)}, 0x0020, 0, 0x00000000, fn0E0E0200, NULL},
    {{REV4(0x0E,   0x0E,         0x03,         0x00)}, 0x0020, 0, 0x00000000, fn0E0E0300, NULL},
    {{REV4(0x0E,   0x0E,         0x04,         0x00)}, 0x0020, 0, 0x00000000, fn0E0E0400, NULL},
    {{REV4(0x0E,   0x0E,         0x05,         0x00)}, 0x0020, 0, 0x00000000, NULL, NULL},
#endif

    {{REV4(0x0E,   0x0F,         0x00,         0x00)}, 0x0000, 3, 0x00000000, fn0E0F0000, &ds0E0F0000},
    {{REV4(0x0E,   0x0F,         0x01,         0x00)}, 0x0000, 3 * GN, 0x00000000, fn0E0F0100, &ds0E0F0100},
    /* 不支持该功能
    {{REV4(0x0E,   0x0F,         0x02,   CI0E0F0201)}, 0x1000, 4, 0x00000000, fn0E0F0201, &ds0E0F0201},
    {{REV4(0x0E,   0x0F,         0x03,   CI0E0F0301)}, 0x1000, 4, 0x00000000, fn0E0F0301, &ds0E0F0301},
    {{REV4(0x0E,   0x0F,         0x04,   CI0E0F0401)}, 0x1000, 4, 0x00000000, fn0E0F0401, &ds0E0F0401},
    */
#if defined(M_LOCAL)    
    {{REV4(0x0F,   0x00,         0x01,         0x00)}, 0x0000, 1, 0x00000000, fn0F000100, &ds0F000100},
    {{REV4(0x0F,   0x00,         0x01,         0x01)}, 0x0000, sizeof(ra0F000101), (uint32_t)&ra0F000101[0], fn0F000101, &ds0F000101},
#endif
/*
    【失压事件记录】
    {{REV4(0x10,   0x00,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee10000001      ), fn10000001, &ds10000001},
    {{REV4(0x10,   0x00,         0x00,         0x02)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee10000002      ), fn10000001, &ds10000002},
    {{REV4(0x10,   0x00,         0x01,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee10000101      ), NULL, &ds10000101},
    {{REV4(0x10,   0x00,         0x02,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee10000201      ), NULL, &ds10000201},
    {{REV4(0x10, CI10010001,     0x00,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee10010001      ), fn10010001, &ds10010001},
    {{REV4(0x10, CI10010001,     0x00,         0x02)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee10010002      ), fn10010001, &ds10010002},
    {{REV4(0x10, CI10010101,     0x01,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ01ZZ      ), NULL,       &ds10010101},
    {{REV4(0x10, CI10010102,     0x01,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ01ZZ), NULL,       &ds10010102},
    {{REV4(0x10, CI10010101,     0x02,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ02ZZ  ), fn00000000, &ds10010201},
    {{REV4(0x10, CI10010102,     0x02,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ02ZZ), fn00000000, &ds10010202},
    {{REV4(0x10, CI10010101,     0x03,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ03ZZ  ), fn00000000, &ds10010301},
    {{REV4(0x10, CI10010102,     0x03,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ03ZZ), fn00000000, &ds10010302},
    {{REV4(0x10, CI10010101,     0x04,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ04ZZ  ), fn00000000, &ds10010401},
    {{REV4(0x10, CI10010102,     0x04,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ04ZZ), fn00000000, &ds10010402},
    {{REV4(0x10, CI10010101,     0x05,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ05ZZ  ), fn00000000, &ds10010501},
    {{REV4(0x10, CI10010102,     0x05,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ05ZZ), fn00000000, &ds10010502},
    {{REV4(0x10, CI10010101,     0x06,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ06ZZ  ), fn00000000, &ds10010601},
    {{REV4(0x10, CI10010102,     0x06,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ06ZZ), fn00000000, &ds10010602},
    {{REV4(0x10, CI10010101,     0x07,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ07ZZ  ), fn00000000, &ds10010701},
    {{REV4(0x10, CI10010102,     0x07,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ07ZZ), fn00000000, &ds10010702},
    {{REV4(0x10, CI10010101,     0x08,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ08ZZ  ), fn00000000, &ds10010801},
    {{REV4(0x10, CI10010102,     0x08,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ08ZZ), fn00000000, &ds10010802},
    {{REV4(0x10, CI10010101,     0x09,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ09ZZ  ), fn00000000, &ds10010901},
    {{REV4(0x10, CI10010102,     0x09,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ09ZZ), fn00000000, &ds10010902},
    {{REV4(0x10, CI10010101,     0x0A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ0AZZ  ), fn10010A01, &ds10010A01},
    {{REV4(0x10, CI10010102,     0x0A,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ0AZZ), fn10010A01, &ds10010A02},
    {{REV4(0x10, CI10010101,     0x0B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ0BZZ  ), fn10010B01, &ds10010B01},
    {{REV4(0x10, CI10010102,     0x0B,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ0BZZ), fn10010B01, &ds10010B02},
    {{REV4(0x10, CI10010101,     0x0C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ0CZZ  ), fn10010C01, &ds10010C01},
    {{REV4(0x10, CI10010102,     0x0C,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ0CZZ), fn10010C01, &ds10010C02},
    {{REV4(0x10, CI10010101,     0x0D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ0DZZ  ), fn10010C01, &ds10010D01},
    {{REV4(0x10, CI10010102,     0x0D,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ0DZZ), fn10010C01, &ds10010D02},
    {{REV4(0x10, CI10010101,     0x0E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ0EZZ  ), NULL,       &ds10010E01},
    {{REV4(0x10, CI10010102,     0x0E,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ0EZZ), NULL,       &ds10010E02},
    {{REV4(0x10, CI10010101,     0x0F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ0FZZ  ), fn00000000, &ds10010F01},
    {{REV4(0x10, CI10010102,     0x0F,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ0FZZ), fn00000000, &ds10010F02},
    {{REV4(0x10, CI10010101,     0x10,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ10ZZ  ), fn00000000, &ds10011001},
    {{REV4(0x10, CI10010102,     0x10,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ10ZZ), fn00000000, &ds10011002},
    {{REV4(0x10, CI10010101,     0x11,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ11ZZ  ), fn00000000, &ds10011101},
    {{REV4(0x10, CI10010102,     0x11,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ11ZZ), fn00000000, &ds10011102},
    {{REV4(0x10, CI10010101,     0x12,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ12ZZ  ), fn00000000, &ds10011201},
    {{REV4(0x10, CI10010102,     0x12,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ12ZZ), fn00000000, &ds10011202},
    {{REV4(0x10, CI10010101,     0x13,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ13ZZ  ), fn10010A01, &ds10011301},
    {{REV4(0x10, CI10010102,     0x13,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ13ZZ), fn10010A01, &ds10011302},
    {{REV4(0x10, CI10010101,     0x14,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ14ZZ  ), fn10010B01, &ds10011401},
    {{REV4(0x10, CI10010102,     0x14,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ14ZZ), fn10010B01, &ds10011402},
    {{REV4(0x10, CI10010101,     0x15,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ15ZZ  ), fn10010C01, &ds10011501},
    {{REV4(0x10, CI10010102,     0x15,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ15ZZ), fn10010C01, &ds10011502},
    {{REV4(0x10, CI10010101,     0x16,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ16ZZ  ), fn10010C01, &ds10011601},
    {{REV4(0x10, CI10010102,     0x16,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ16ZZ), fn10010C01, &ds10011602},
    {{REV4(0x10, CI10010101,     0x17,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ17ZZ  ), NULL,       &ds10011701},
    {{REV4(0x10, CI10010102,     0x17,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ17ZZ), NULL,       &ds10011702},
    {{REV4(0x10, CI10010101,     0x18,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ18ZZ  ), fn00000000, &ds10011801},
    {{REV4(0x10, CI10010102,     0x18,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ18ZZ), fn00000000, &ds10011802},
    {{REV4(0x10, CI10010101,     0x19,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ19ZZ  ), fn00000000, &ds10011901},
    {{REV4(0x10, CI10010102,     0x19,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ19ZZ), fn00000000, &ds10011902},
    {{REV4(0x10, CI10010101,     0x1A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ1AZZ  ), fn00000000, &ds10011A01},
    {{REV4(0x10, CI10010102,     0x1A,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ1AZZ), fn00000000, &ds10011A02},
    {{REV4(0x10, CI10010101,     0x1B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ1BZZ  ), fn00000000, &ds10011B01},
    {{REV4(0x10, CI10010102,     0x1B,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ1BZZ), fn00000000, &ds10011B02},
    {{REV4(0x10, CI10010101,     0x1C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ1CZZ  ), fn10010A01, &ds10011C01},
    {{REV4(0x10, CI10010102,     0x1C,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ1CZZ), fn10010A01, &ds10011C02},
    {{REV4(0x10, CI10010101,     0x1D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ1DZZ  ), fn10010B01, &ds10011D01},
    {{REV4(0x10, CI10010102,     0x1D,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ1DZZ), fn10010B01, &ds10011D02},
    {{REV4(0x10, CI10010101,     0x1E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ1EZZ  ), fn10010C01, &ds10011E01},
    {{REV4(0x10, CI10010102,     0x1E,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ1EZZ), fn10010C01, &ds10011E02},
    {{REV4(0x10, CI10010101,     0x1F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ1FZZ  ), fn10010C01, &ds10011F01},
    {{REV4(0x10, CI10010102,     0x1F,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ1FZZ), fn10010C01, &ds10011F02},
    {{REV4(0x10, CI10010101,     0x20,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ20ZZ  ), NULL,       &ds10012001},
    {{REV4(0x10, CI10010102,     0x20,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ20ZZ), NULL,       &ds10012002},
    {{REV4(0x10, CI10010101,     0x21,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ21ZZ  ), fn10012101, &ds10012101},
    {{REV4(0x10, CI10010102,     0x21,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ21ZZ), fn10012101, &ds10012102},
    {{REV4(0x10, CI10010101,     0x22,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ22ZZ  ), fn10012101, &ds10012201},
    {{REV4(0x10, CI10010102,     0x22,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ22ZZ), fn10012101, &ds10012202},
    {{REV4(0x10, CI10010101,     0x23,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ23ZZ  ), fn10012101, &ds10012301},
    {{REV4(0x10, CI10010102,     0x23,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ23ZZ), fn10012101, &ds10012302},
    {{REV4(0x10, CI10010101,     0x24,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ24ZZ  ), fn10012101, &ds10012401},
    {{REV4(0x10, CI10010102,     0x24,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ24ZZ), fn10012101, &ds10012402},
    {{REV4(0x10, CI10010101,     0x25,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ25ZZ  ), NULL,       &ds10012501},
    {{REV4(0x10, CI10010102,     0x25,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ25ZZ), NULL,       &ds10012502},
    {{REV4(0x10, CI10010101,     0x26,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ26ZZ  ), fn00000000, &ds10012601},
    {{REV4(0x10, CI10010102,     0x26,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ26ZZ), fn00000000, &ds10012602},
    {{REV4(0x10, CI10010101,     0x27,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ27ZZ  ), fn00000000, &ds10012701},
    {{REV4(0x10, CI10010102,     0x27,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ27ZZ), fn00000000, &ds10012702},
    {{REV4(0x10, CI10010101,     0x28,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ28ZZ  ), fn00000000, &ds10012801},
    {{REV4(0x10, CI10010102,     0x28,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ28ZZ), fn00000000, &ds10012802},
    {{REV4(0x10, CI10010101,     0x29,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ29ZZ  ), fn00000000, &ds10012901},
    {{REV4(0x10, CI10010102,     0x29,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ29ZZ), fn00000000, &ds10012902},
    {{REV4(0x10, CI10010101,     0x2A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ2AZZ  ), fn00000000, &ds10012A01},
    {{REV4(0x10, CI10010102,     0x2A,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ2AZZ), fn00000000, &ds10012A02},
    {{REV4(0x10, CI10010101,     0x2B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ2BZZ  ), fn00000000, &ds10012B01},
    {{REV4(0x10, CI10010102,     0x2B,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ2BZZ), fn00000000, &ds10012B02},
    {{REV4(0x10, CI10010101,     0x2C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ2CZZ  ), fn00000000, &ds10012C01},
    {{REV4(0x10, CI10010102,     0x2C,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ2CZZ), fn00000000, &ds10012C02},
    {{REV4(0x10, CI10010101,     0x2D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ2DZZ  ), fn00000000, &ds10012D01},
    {{REV4(0x10, CI10010102,     0x2D,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ2DZZ), fn00000000, &ds10012D02},
    {{REV4(0x10, CI10010101,     0x2E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ2EZZ  ), fn00000000, &ds10012E01},
    {{REV4(0x10, CI10010102,     0x2E,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ2EZZ), fn00000000, &ds10012E02},
    {{REV4(0x10, CI10010101,     0x2F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ2FZZ  ), fn00000000, &ds10012F01},
    {{REV4(0x10, CI10010102,     0x2F,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ2FZZ), fn00000000, &ds10012F02},
    {{REV4(0x10, CI10010101,     0x30,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ30ZZ  ), fn00000000, &ds10013001},
    {{REV4(0x10, CI10010102,     0x30,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ30ZZ), fn00000000, &ds10013002},
    {{REV4(0x10, CI10010101,     0x31,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ31ZZ  ), fn00000000, &ds10013101},
    {{REV4(0x10, CI10010102,     0x31,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ31ZZ), fn00000000, &ds10013102},
    {{REV4(0x10, CI10010101,     0x32,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ32ZZ  ), fn00000000, &ds10013201},
    {{REV4(0x10, CI10010102,     0x32,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ32ZZ), fn00000000, &ds10013202},
    {{REV4(0x10, CI10010101,     0x33,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ33ZZ  ), fn00000000, &ds10013301},
    {{REV4(0x10, CI10010102,     0x33,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ33ZZ), fn00000000, &ds10013302},
    {{REV4(0x10, CI10010101,     0x34,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ34ZZ  ), fn00000000, &ds10013401},
    {{REV4(0x10, CI10010102,     0x34,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ34ZZ), fn00000000, &ds10013402},
    {{REV4(0x10, CI10010101,     0x35,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ35ZZ  ), fn00000000, &ds10013501},
    {{REV4(0x10, CI10010102,     0x35,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ35ZZ), fn00000000, &ds10013502},

    【欠压事件记录】
    {{REV4(0x11, CI11010001,     0x00,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee11010001                   ), fn10010001, NULL},
    {{REV4(0x11, CI11010001,     0x00,         0x02)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee11010002                   ), fn10010001, NULL},
    {{REV4(0x11, CI11010101,     0x01,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ01ZZ  ), NULL,       NULL},
    {{REV4(0x11, CI11010102,     0x01,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ01ZZ), NULL,       NULL},
    {{REV4(0x11, CI11010101,     0x02,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ02ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x02,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ02ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x03,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ03ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x03,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ03ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x04,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ04ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x04,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ04ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x05,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ05ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x05,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ05ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x06,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ06ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x06,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ06ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x07,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ07ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x07,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ07ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x08,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ08ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x08,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ08ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x09,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ09ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x09,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ09ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x0A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ0AZZ  ), fn10010A01, NULL},
    {{REV4(0x11, CI11010102,     0x0A,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ0AZZ), fn10010A01, NULL},
    {{REV4(0x11, CI11010101,     0x0B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ0BZZ  ), fn10010B01, NULL},
    {{REV4(0x11, CI11010102,     0x0B,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ0BZZ), fn10010B01, NULL},
    {{REV4(0x11, CI11010101,     0x0C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ0CZZ  ), fn10010C01, NULL},
    {{REV4(0x11, CI11010102,     0x0C,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ0CZZ), fn10010C01, NULL},
    {{REV4(0x11, CI11010101,     0x0D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ0DZZ  ), fn10010C01, NULL},
    {{REV4(0x11, CI11010102,     0x0D,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ0DZZ), fn10010C01, NULL},
    {{REV4(0x11, CI11010101,     0x0E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ0EZZ  ), NULL,       NULL},
    {{REV4(0x11, CI11010102,     0x0E,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ0EZZ), NULL,       NULL},
    {{REV4(0x11, CI11010101,     0x0F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ0FZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x0F,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ0FZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x10,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ10ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x10,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ10ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x11,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ11ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x11,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ11ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x12,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ12ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x12,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ12ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x13,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ13ZZ  ), fn10010A01, NULL},
    {{REV4(0x11, CI11010102,     0x13,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ13ZZ), fn10010A01, NULL},
    {{REV4(0x11, CI11010101,     0x14,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ14ZZ  ), fn10010B01, NULL},
    {{REV4(0x11, CI11010102,     0x14,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ14ZZ), fn10010B01, NULL},
    {{REV4(0x11, CI11010101,     0x15,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ15ZZ  ), fn10010C01, NULL},
    {{REV4(0x11, CI11010102,     0x15,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ15ZZ), fn10010C01, NULL},
    {{REV4(0x11, CI11010101,     0x16,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ16ZZ  ), fn10010C01, NULL},
    {{REV4(0x11, CI11010102,     0x16,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ16ZZ), fn10010C01, NULL},
    {{REV4(0x11, CI11010101,     0x17,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ17ZZ  ), NULL,       NULL},
    {{REV4(0x11, CI11010102,     0x17,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ17ZZ), NULL,       NULL},
    {{REV4(0x11, CI11010101,     0x18,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ18ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x18,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ18ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x19,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ19ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x19,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ19ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x1A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ1AZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x1A,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ1AZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x1B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ1BZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x1B,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ1BZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x1C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ1CZZ  ), fn10010A01, NULL},
    {{REV4(0x11, CI11010102,     0x1C,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ1CZZ), fn10010A01, NULL},
    {{REV4(0x11, CI11010101,     0x1D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ1DZZ  ), fn10010B01, NULL},
    {{REV4(0x11, CI11010102,     0x1D,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ1DZZ), fn10010B01, NULL},
    {{REV4(0x11, CI11010101,     0x1E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ1EZZ  ), fn10010C01, NULL},
    {{REV4(0x11, CI11010102,     0x1E,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ1EZZ), fn10010C01, NULL},
    {{REV4(0x11, CI11010101,     0x1F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ1FZZ  ), fn10010C01, NULL},
    {{REV4(0x11, CI11010102,     0x1F,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ1FZZ), fn10010C01, NULL},
    {{REV4(0x11, CI11010101,     0x20,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ20ZZ  ), NULL,       NULL},
    {{REV4(0x11, CI11010102,     0x20,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ20ZZ), NULL,       NULL},
    {{REV4(0x11, CI11010101,     0x21,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ21ZZ  ), fn10012101, NULL},
    {{REV4(0x11, CI11010102,     0x21,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ21ZZ), fn10012101, NULL},
    {{REV4(0x11, CI11010101,     0x22,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ22ZZ  ), fn10012101, NULL},
    {{REV4(0x11, CI11010102,     0x22,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ22ZZ), fn10012101, NULL},
    {{REV4(0x11, CI11010101,     0x23,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ23ZZ  ), fn10012101, NULL},
    {{REV4(0x11, CI11010102,     0x23,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ23ZZ), fn10012101, NULL},
    {{REV4(0x11, CI11010101,     0x24,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ24ZZ  ), fn10012101, NULL},
    {{REV4(0x11, CI11010102,     0x24,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ24ZZ), fn10012101, NULL},
    {{REV4(0x11, CI11010101,     0x25,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ25ZZ  ), NULL,       NULL},
    {{REV4(0x11, CI11010102,     0x25,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ25ZZ), NULL,       NULL},
    {{REV4(0x11, CI11010101,     0x26,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ26ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x26,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ26ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x27,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ27ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x27,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ27ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x28,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ28ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x28,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ28ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x29,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ29ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x29,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ29ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x2A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ2AZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x2A,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ2AZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x2B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ2BZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x2B,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ2BZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x2C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ2CZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x2C,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ2CZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x2D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ2DZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x2D,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ2DZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x2E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ2EZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x2E,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ2EZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x2F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ2FZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x2F,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ2FZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x30,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ30ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x30,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ30ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x31,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ31ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x31,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ31ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x32,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ32ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x32,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ32ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x33,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ33ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x33,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ33ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x34,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ34ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x34,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ34ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x35,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ35ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x35,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ35ZZ), fn00000000, NULL},

    【过压事件记录】
    {{REV4(0x12, CI12010001,     0x00,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee12010001                   ), fn10010001, NULL},
    {{REV4(0x12, CI12010001,     0x00,         0x02)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee12010002                   ), fn10010001, NULL},
    {{REV4(0x12, CI12010101,     0x01,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ01ZZ  ), NULL,       NULL},
    {{REV4(0x12, CI12010102,     0x01,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ01ZZ), NULL,       NULL},
    {{REV4(0x12, CI12010101,     0x02,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ02ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x02,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ02ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x03,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ03ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x03,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ03ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x04,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ04ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x04,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ04ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x05,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ05ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x05,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ05ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x06,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ06ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x06,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ06ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x07,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ07ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x07,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ07ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x08,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ08ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x08,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ08ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x09,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ09ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x09,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ09ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x0A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ0AZZ  ), fn10010A01, NULL},
    {{REV4(0x12, CI12010102,     0x0A,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ0AZZ), fn10010A01, NULL},
    {{REV4(0x12, CI12010101,     0x0B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ0BZZ  ), fn10010B01, NULL},
    {{REV4(0x12, CI12010102,     0x0B,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ0BZZ), fn10010B01, NULL},
    {{REV4(0x12, CI12010101,     0x0C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ0CZZ  ), fn10010C01, NULL},
    {{REV4(0x12, CI12010102,     0x0C,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ0CZZ), fn10010C01, NULL},
    {{REV4(0x12, CI12010101,     0x0D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ0DZZ  ), fn10010C01, NULL},
    {{REV4(0x12, CI12010102,     0x0D,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ0DZZ), fn10010C01, NULL},
    {{REV4(0x12, CI12010101,     0x0E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ0EZZ  ), NULL,       NULL},
    {{REV4(0x12, CI12010102,     0x0E,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ0EZZ), NULL,       NULL},
    {{REV4(0x12, CI12010101,     0x0F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ0FZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x0F,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ0FZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x10,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ10ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x10,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ10ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x11,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ11ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x11,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ11ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x12,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ12ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x12,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ12ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x13,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ13ZZ  ), fn10010A01, NULL},
    {{REV4(0x12, CI12010102,     0x13,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ13ZZ), fn10010A01, NULL},
    {{REV4(0x12, CI12010101,     0x14,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ14ZZ  ), fn10010B01, NULL},
    {{REV4(0x12, CI12010102,     0x14,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ14ZZ), fn10010B01, NULL},
    {{REV4(0x12, CI12010101,     0x15,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ15ZZ  ), fn10010C01, NULL},
    {{REV4(0x12, CI12010102,     0x15,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ15ZZ), fn10010C01, NULL},
    {{REV4(0x12, CI12010101,     0x16,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ16ZZ  ), fn10010C01, NULL},
    {{REV4(0x12, CI12010102,     0x16,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ16ZZ), fn10010C01, NULL},
    {{REV4(0x12, CI12010101,     0x17,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ17ZZ  ), NULL,       NULL},
    {{REV4(0x12, CI12010102,     0x17,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ17ZZ), NULL,       NULL},
    {{REV4(0x12, CI12010101,     0x18,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ18ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x18,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ18ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x19,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ19ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x19,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ19ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x1A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ1AZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x1A,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ1AZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x1B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ1BZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x1B,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ1BZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x1C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ1CZZ  ), fn10010A01, NULL},
    {{REV4(0x12, CI12010102,     0x1C,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ1CZZ), fn10010A01, NULL},
    {{REV4(0x12, CI12010101,     0x1D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ1DZZ  ), fn10010B01, NULL},
    {{REV4(0x12, CI12010102,     0x1D,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ1DZZ), fn10010B01, NULL},
    {{REV4(0x12, CI12010101,     0x1E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ1EZZ  ), fn10010C01, NULL},
    {{REV4(0x12, CI12010102,     0x1E,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ1EZZ), fn10010C01, NULL},
    {{REV4(0x12, CI12010101,     0x1F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ1FZZ  ), fn10010C01, NULL},
    {{REV4(0x12, CI12010102,     0x1F,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ1FZZ), fn10010C01, NULL},
    {{REV4(0x12, CI12010101,     0x20,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ20ZZ  ), NULL,       NULL},
    {{REV4(0x12, CI12010102,     0x20,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ20ZZ), NULL,       NULL},
    {{REV4(0x12, CI12010101,     0x21,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ21ZZ  ), fn10012101, NULL},
    {{REV4(0x12, CI12010102,     0x21,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ21ZZ), fn10012101, NULL},
    {{REV4(0x12, CI12010101,     0x22,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ22ZZ  ), fn10012101, NULL},
    {{REV4(0x12, CI12010102,     0x22,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ22ZZ), fn10012101, NULL},
    {{REV4(0x12, CI12010101,     0x23,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ23ZZ  ), fn10012101, NULL},
    {{REV4(0x12, CI12010102,     0x23,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ23ZZ), fn10012101, NULL},
    {{REV4(0x12, CI12010101,     0x24,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ24ZZ  ), fn10012101, NULL},
    {{REV4(0x12, CI12010102,     0x24,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ24ZZ), fn10012101, NULL},
    {{REV4(0x12, CI12010101,     0x25,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ25ZZ  ), NULL,       NULL},
    {{REV4(0x12, CI12010102,     0x25,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ25ZZ), NULL,       NULL},
    {{REV4(0x12, CI12010101,     0x26,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ26ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x26,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ26ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x27,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ27ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x27,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ27ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x28,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ28ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x28,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ28ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x29,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ29ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x29,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ29ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x2A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ2AZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x2A,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ2AZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x2B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ2BZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x2B,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ2BZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x2C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ2CZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x2C,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ2CZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x2D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ2DZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x2D,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ2DZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x2E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ2EZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x2E,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ2EZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x2F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ2FZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x2F,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ2FZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x30,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ30ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x30,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ30ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x31,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ31ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x31,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ31ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x32,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ32ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x32,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ32ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x33,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ33ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x33,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ33ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x34,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ34ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x34,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ34ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x35,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ35ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x35,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ35ZZ), fn00000000, NULL},

    【断相事件记录】
    {{REV4(0x13, CI13010001,     0x00,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee13010001      ), fn10010001, &ds13010001},
    {{REV4(0x13, CI13010001,     0x00,         0x02)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee13010002      ), fn10010001, &ds13010002},
    {{REV4(0x13, CI13010101,     0x01,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ01ZZ      ), NULL,       &ds13010101},
    {{REV4(0x13, CI13010102,     0x01,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ01ZZ), NULL,       &ds13010102},
    {{REV4(0x13, CI13010101,     0x02,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ02ZZ  ), fn00000000, &ds13010201},
    {{REV4(0x13, CI13010102,     0x02,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ02ZZ), fn00000000, &ds13010202},
    {{REV4(0x13, CI13010101,     0x03,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ03ZZ  ), fn00000000, &ds13010301},
    {{REV4(0x13, CI13010102,     0x03,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ03ZZ), fn00000000, &ds13010302},
    {{REV4(0x13, CI13010101,     0x04,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ04ZZ  ), fn00000000, &ds13010401},
    {{REV4(0x13, CI13010102,     0x04,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ04ZZ), fn00000000, &ds13010402},
    {{REV4(0x13, CI13010101,     0x05,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ05ZZ  ), fn00000000, &ds13010501},
    {{REV4(0x13, CI13010102,     0x05,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ05ZZ), fn00000000, &ds13010502},
    {{REV4(0x13, CI13010101,     0x06,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ06ZZ  ), fn00000000, &ds13010601},
    {{REV4(0x13, CI13010102,     0x06,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ06ZZ), fn00000000, &ds13010602},
    {{REV4(0x13, CI13010101,     0x07,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ07ZZ  ), fn00000000, &ds13010701},
    {{REV4(0x13, CI13010102,     0x07,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ07ZZ), fn00000000, &ds13010702},
    {{REV4(0x13, CI13010101,     0x08,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ08ZZ  ), fn00000000, &ds13010801},
    {{REV4(0x13, CI13010102,     0x08,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ08ZZ), fn00000000, &ds13010802},
    {{REV4(0x13, CI13010101,     0x09,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ09ZZ  ), fn00000000, &ds13010901},
    {{REV4(0x13, CI13010102,     0x09,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ09ZZ), fn00000000, &ds13010902},
    {{REV4(0x13, CI13010101,     0x0A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ0AZZ  ), fn10010A01, &ds13010A01},
    {{REV4(0x13, CI13010102,     0x0A,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ0AZZ), fn10010A01, &ds13010A02},
    {{REV4(0x13, CI13010101,     0x0B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ0BZZ  ), fn10010B01, &ds13010B01},
    {{REV4(0x13, CI13010102,     0x0B,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ0BZZ), fn10010B01, &ds13010B02},
    {{REV4(0x13, CI13010101,     0x0C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ0CZZ  ), fn10010C01, &ds13010C01},
    {{REV4(0x13, CI13010102,     0x0C,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ0CZZ), fn10010C01, &ds13010C02},
    {{REV4(0x13, CI13010101,     0x0D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ0DZZ  ), fn10010C01, &ds13010D01},
    {{REV4(0x13, CI13010102,     0x0D,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ0DZZ), fn10010C01, &ds13010D02},
    {{REV4(0x13, CI13010101,     0x0E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ0EZZ  ), NULL,       &ds13010E01},
    {{REV4(0x13, CI13010102,     0x0E,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ0EZZ), NULL,       &ds13010E02},
    {{REV4(0x13, CI13010101,     0x0F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ0FZZ  ), fn00000000, &ds13010F01},
    {{REV4(0x13, CI13010102,     0x0F,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ0FZZ), fn00000000, &ds13010F02},
    {{REV4(0x13, CI13010101,     0x10,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ10ZZ  ), fn00000000, &ds13011001},
    {{REV4(0x13, CI13010102,     0x10,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ10ZZ), fn00000000, &ds13011002},
    {{REV4(0x13, CI13010101,     0x11,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ11ZZ  ), fn00000000, &ds13011101},
    {{REV4(0x13, CI13010102,     0x11,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ11ZZ), fn00000000, &ds13011102},
    {{REV4(0x13, CI13010101,     0x12,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ12ZZ  ), fn00000000, &ds13011201},
    {{REV4(0x13, CI13010102,     0x12,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ12ZZ), fn00000000, &ds13011202},
    {{REV4(0x13, CI13010101,     0x13,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ13ZZ  ), fn10010A01, &ds13011301},
    {{REV4(0x13, CI13010102,     0x13,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ13ZZ), fn10010A01, &ds13011302},
    {{REV4(0x13, CI13010101,     0x14,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ14ZZ  ), fn10010B01, &ds13011401},
    {{REV4(0x13, CI13010102,     0x14,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ14ZZ), fn10010B01, &ds13011402},
    {{REV4(0x13, CI13010101,     0x15,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ15ZZ  ), fn10010C01, &ds13011501},
    {{REV4(0x13, CI13010102,     0x15,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ15ZZ), fn10010C01, &ds13011502},
    {{REV4(0x13, CI13010101,     0x16,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ16ZZ  ), fn10010C01, &ds13011601},
    {{REV4(0x13, CI13010102,     0x16,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ16ZZ), fn10010C01, &ds13011602},
    {{REV4(0x13, CI13010101,     0x17,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ17ZZ  ), NULL,       &ds13011701},
    {{REV4(0x13, CI13010102,     0x17,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ17ZZ), NULL,       &ds13011702},
    {{REV4(0x13, CI13010101,     0x18,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ18ZZ  ), fn00000000, &ds13011801},
    {{REV4(0x13, CI13010102,     0x18,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ18ZZ), fn00000000, &ds13011802},
    {{REV4(0x13, CI13010101,     0x19,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ19ZZ  ), fn00000000, &ds13011901},
    {{REV4(0x13, CI13010102,     0x19,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ19ZZ), fn00000000, &ds13011902},
    {{REV4(0x13, CI13010101,     0x1A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ1AZZ  ), fn00000000, &ds13011A01},
    {{REV4(0x13, CI13010102,     0x1A,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ1AZZ), fn00000000, &ds13011A02},
    {{REV4(0x13, CI13010101,     0x1B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ1BZZ  ), fn00000000, &ds13011B01},
    {{REV4(0x13, CI13010102,     0x1B,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ1BZZ), fn00000000, &ds13011B02},
    {{REV4(0x13, CI13010101,     0x1C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ1CZZ  ), fn10010A01, &ds13011C01},
    {{REV4(0x13, CI13010102,     0x1C,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ1CZZ), fn10010A01, &ds13011C02},
    {{REV4(0x13, CI13010101,     0x1D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ1DZZ  ), fn10010B01, &ds13011D01},
    {{REV4(0x13, CI13010102,     0x1D,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ1DZZ), fn10010B01, &ds13011D02},
    {{REV4(0x13, CI13010101,     0x1E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ1EZZ  ), fn10010C01, &ds13011E01},
    {{REV4(0x13, CI13010102,     0x1E,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ1EZZ), fn10010C01, &ds13011E02},
    {{REV4(0x13, CI13010101,     0x1F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ1FZZ  ), fn10010C01, &ds13011F01},
    {{REV4(0x13, CI13010102,     0x1F,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ1FZZ), fn10010C01, &ds13011F02},
    {{REV4(0x13, CI13010101,     0x20,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ20ZZ  ), NULL,       &ds13012001},
    {{REV4(0x13, CI13010102,     0x20,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ20ZZ), NULL,       &ds13012002},
    {{REV4(0x13, CI13010101,     0x21,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ21ZZ  ), fn10012101, &ds13012101},
    {{REV4(0x13, CI13010102,     0x21,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ21ZZ), fn10012101, &ds13012102},
    {{REV4(0x13, CI13010101,     0x22,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ22ZZ  ), fn10012101, &ds13012201},
    {{REV4(0x13, CI13010102,     0x22,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ22ZZ), fn10012101, &ds13012202},
    {{REV4(0x13, CI13010101,     0x23,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ23ZZ  ), fn10012101, &ds13012301},
    {{REV4(0x13, CI13010102,     0x23,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ23ZZ), fn10012101, &ds13012302},
    {{REV4(0x13, CI13010101,     0x24,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ24ZZ  ), fn10012101, &ds13012401},
    {{REV4(0x13, CI13010102,     0x24,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ24ZZ), fn10012101, &ds13012402},
    {{REV4(0x13, CI13010101,     0x25,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ25ZZ  ), NULL,       &ds13012501},
    {{REV4(0x13, CI13010102,     0x25,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ25ZZ), NULL,       &ds13012502},
    {{REV4(0x13, CI13010101,     0x26,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ26ZZ  ), fn00000000, &ds13012601},
    {{REV4(0x13, CI13010102,     0x26,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ26ZZ), fn00000000, &ds13012602},
    {{REV4(0x13, CI13010101,     0x27,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ27ZZ  ), fn00000000, &ds13012701},
    {{REV4(0x13, CI13010102,     0x27,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ27ZZ), fn00000000, &ds13012702},
    {{REV4(0x13, CI13010101,     0x28,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ28ZZ  ), fn00000000, &ds13012801},
    {{REV4(0x13, CI13010102,     0x28,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ28ZZ), fn00000000, &ds13012802},
    {{REV4(0x13, CI13010101,     0x29,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ29ZZ  ), fn00000000, &ds13012901},
    {{REV4(0x13, CI13010102,     0x29,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ29ZZ), fn00000000, &ds13012902},
    {{REV4(0x13, CI13010101,     0x2A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ2AZZ  ), fn00000000, &ds13012A01},
    {{REV4(0x13, CI13010102,     0x2A,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ2AZZ), fn00000000, &ds13012A02},
    {{REV4(0x13, CI13010101,     0x2B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ2BZZ  ), fn00000000, &ds13012B01},
    {{REV4(0x13, CI13010102,     0x2B,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ2BZZ), fn00000000, &ds13012B02},
    {{REV4(0x13, CI13010101,     0x2C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ2CZZ  ), fn00000000, &ds13012C01},
    {{REV4(0x13, CI13010102,     0x2C,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ2CZZ), fn00000000, &ds13012C02},
    {{REV4(0x13, CI13010101,     0x2D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ2DZZ  ), fn00000000, &ds13012D01},
    {{REV4(0x13, CI13010102,     0x2D,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ2DZZ), fn00000000, &ds13012D02},
    {{REV4(0x13, CI13010101,     0x2E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ2EZZ  ), fn00000000, &ds13012E01},
    {{REV4(0x13, CI13010102,     0x2E,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ2EZZ), fn00000000, &ds13012E02},
    {{REV4(0x13, CI13010101,     0x2F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ2FZZ  ), fn00000000, &ds13012F01},
    {{REV4(0x13, CI13010102,     0x2F,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ2FZZ), fn00000000, &ds13012F02},
    {{REV4(0x13, CI13010101,     0x30,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ30ZZ  ), fn00000000, &ds13013001},
    {{REV4(0x13, CI13010102,     0x30,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ30ZZ), fn00000000, &ds13013002},
    {{REV4(0x13, CI13010101,     0x31,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ31ZZ  ), fn00000000, &ds13013101},
    {{REV4(0x13, CI13010102,     0x31,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ31ZZ), fn00000000, &ds13013102},
    {{REV4(0x13, CI13010101,     0x32,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ32ZZ  ), fn00000000, &ds13013201},
    {{REV4(0x13, CI13010102,     0x32,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ32ZZ), fn00000000, &ds13013202},
    {{REV4(0x13, CI13010101,     0x33,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ33ZZ  ), fn00000000, &ds13013301},
    {{REV4(0x13, CI13010102,     0x33,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ33ZZ), fn00000000, &ds13013302},
    {{REV4(0x13, CI13010101,     0x34,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ34ZZ  ), fn00000000, &ds13013401},
    {{REV4(0x13, CI13010102,     0x34,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ34ZZ), fn00000000, &ds13013402},
    {{REV4(0x13, CI13010101,     0x35,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ35ZZ  ), fn00000000, &ds13013501},
    {{REV4(0x13, CI13010102,     0x35,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ35ZZ), fn00000000, &ds13013502},

    【电压逆向序事件记录】
    {{REV4(0x14,   0x00,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee14000001                   ), fn10010001, NULL},
    {{REV4(0x14,   0x00,         0x00,         0x02)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee14000002                   ), fn10010001, NULL},
    {{REV4(0x14,   0x00,         0x01,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140001ZZ   ), NULL,       NULL},
    {{REV4(0x14,   0x00,         0x02,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140002ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x03,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140003ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x04,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140004ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x05,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140005ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x06,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140006ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x07,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140007ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x08,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140008ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x09,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140009ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x0A,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14000AZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x0B,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14000BZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x0C,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14000CZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x0D,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14000DZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x0E,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14000EZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x0F,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14000FZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x10,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140010ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x11,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140011ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x12,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140012ZZ   ), NULL,       NULL},
    {{REV4(0x14,   0x00,         0x13,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140013ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x14,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140014ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x15,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140015ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x16,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140016ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x17,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140017ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x18,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140018ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x19,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140019ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x1A,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14001AZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x1B,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14001BZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x1C,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14001CZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x1D,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14001DZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x1E,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14001EZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x1F,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14001FZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x20,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140020ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x21,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140021ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x22,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140022ZZ   ), fn00000000, NULL},

     【电流逆向序事件记录】
    {{REV4(0x15,   0x00,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee15000001                   ), fn10010001, NULL},
    {{REV4(0x15,   0x00,         0x00,         0x02)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee15000002                   ), fn10010001, NULL},
    {{REV4(0x15,   0x00,         0x01,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140001ZZ   ), NULL,       NULL},
    {{REV4(0x15,   0x00,         0x02,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140002ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x03,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140003ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x04,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140004ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x05,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140005ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x06,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140006ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x07,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140007ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x08,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140008ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x09,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140009ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x0A,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14000AZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x0B,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14000BZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x0C,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14000CZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x0D,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14000DZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x0E,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14000EZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x0F,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14000FZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x10,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140010ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x11,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140011ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x12,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140012ZZ   ), NULL,       NULL},
    {{REV4(0x15,   0x00,         0x13,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140013ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x14,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140014ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x15,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140015ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x16,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140016ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x17,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140017ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x18,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140018ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x19,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140019ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x1A,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14001AZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x1B,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14001BZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x1C,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14001CZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x1D,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14001DZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x1E,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14001EZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x1F,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14001FZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x20,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140020ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x21,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140021ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x22,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140022ZZ   ), fn00000000, NULL},

    【电压不平衡事件记录】
    {{REV4(0x16,   0x00,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee16000001      ), fn10010001, &ds16000001},
    {{REV4(0x16,   0x00,         0x00,         0x02)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee16000002      ), fn10010001, &ds16000002},
    {{REV4(0x16,   0x00,         0x01,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160001ZZ     ), NULL,       &ds16000101},
    {{REV4(0x16,   0x00,         0x01,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160001ZZ   ), NULL,       &ds16000102},
    {{REV4(0x16,   0x00,         0x02,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160002ZZ     ), fn00000000, &ds16000201},
    {{REV4(0x16,   0x00,         0x02,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160002ZZ   ), fn00000000, &ds16000202},
    {{REV4(0x16,   0x00,         0x03,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160003ZZ     ), fn00000000, &ds16000301},
    {{REV4(0x16,   0x00,         0x03,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160003ZZ   ), fn00000000, &ds16000302},
    {{REV4(0x16,   0x00,         0x04,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160004ZZ     ), fn00000000, &ds16000401},
    {{REV4(0x16,   0x00,         0x04,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160004ZZ   ), fn00000000, &ds16000402},
    {{REV4(0x16,   0x00,         0x05,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160005ZZ     ), fn00000000, &ds16000501},
    {{REV4(0x16,   0x00,         0x05,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160005ZZ   ), fn00000000, &ds16000502},
    {{REV4(0x16,   0x00,         0x06,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160006ZZ     ), fn00000000, &ds16000601},
    {{REV4(0x16,   0x00,         0x06,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160006ZZ   ), fn00000000, &ds16000602},
    {{REV4(0x16,   0x00,         0x07,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160007ZZ     ), fn00000000, &ds16000701},
    {{REV4(0x16,   0x00,         0x07,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160007ZZ   ), fn00000000, &ds16000702},
    {{REV4(0x16,   0x00,         0x08,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160008ZZ     ), fn00000000, &ds16000801},
    {{REV4(0x16,   0x00,         0x08,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160008ZZ   ), fn00000000, &ds16000802},
    {{REV4(0x16,   0x00,         0x09,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160009ZZ     ), fn00000000, &ds16000901},
    {{REV4(0x16,   0x00,         0x09,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160009ZZ   ), fn00000000, &ds16000902},
    {{REV4(0x16,   0x00,         0x0A,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16000AZZ     ), fn00000000, &ds16000A01},
    {{REV4(0x16,   0x00,         0x0A,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16000AZZ   ), fn00000000, &ds16000A02},
    {{REV4(0x16,   0x00,         0x0B,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16000BZZ     ), fn00000000, &ds16000B01},
    {{REV4(0x16,   0x00,         0x0B,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16000BZZ   ), fn00000000, &ds16000B02},
    {{REV4(0x16,   0x00,         0x0C,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16000CZZ     ), fn00000000, &ds16000C01},
    {{REV4(0x16,   0x00,         0x0C,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16000CZZ   ), fn00000000, &ds16000C02},
    {{REV4(0x16,   0x00,         0x0D,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16000DZZ     ), fn00000000, &ds16000D01},
    {{REV4(0x16,   0x00,         0x0D,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16000DZZ   ), fn00000000, &ds16000D02},
    {{REV4(0x16,   0x00,         0x0E,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16000EZZ     ), fn00000000, &ds16000E01},
    {{REV4(0x16,   0x00,         0x0E,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16000EZZ   ), fn00000000, &ds16000E02},
    {{REV4(0x16,   0x00,         0x0F,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16000FZZ     ), fn00000000, &ds16000F01},
    {{REV4(0x16,   0x00,         0x0F,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16000FZZ   ), fn00000000, &ds16000F02},
    {{REV4(0x16,   0x00,         0x10,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160010ZZ     ), fn00000000, &ds16001001},
    {{REV4(0x16,   0x00,         0x10,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160010ZZ   ), fn00000000, &ds16001002},
    {{REV4(0x16,   0x00,         0x11,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160011ZZ     ), fn00000000, &ds16001101},
    {{REV4(0x16,   0x00,         0x11,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160011ZZ   ), fn00000000, &ds16001102},
    {{REV4(0x16,   0x00,         0x12,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160012ZZ     ), fn16001201, &ds16001201},
    {{REV4(0x16,   0x00,         0x12,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160012ZZ   ), fn16001201, &ds16001202},
    {{REV4(0x16,   0x00,         0x13,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160013ZZ     ), NULL,       &ds16001301},
    {{REV4(0x16,   0x00,         0x13,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160013ZZ   ), NULL,       &ds16001302},
    {{REV4(0x16,   0x00,         0x14,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160014ZZ     ), fn00000000, &ds16001401},
    {{REV4(0x16,   0x00,         0x14,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160014ZZ   ), fn00000000, &ds16001402},
    {{REV4(0x16,   0x00,         0x15,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160015ZZ     ), fn00000000, &ds16001501},
    {{REV4(0x16,   0x00,         0x15,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160015ZZ   ), fn00000000, &ds16001502},
    {{REV4(0x16,   0x00,         0x16,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160016ZZ     ), fn00000000, &ds16001601},
    {{REV4(0x16,   0x00,         0x16,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160016ZZ   ), fn00000000, &ds16001602},
    {{REV4(0x16,   0x00,         0x17,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160017ZZ     ), fn00000000, &ds16001701},
    {{REV4(0x16,   0x00,         0x17,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160017ZZ   ), fn00000000, &ds16001702},
    {{REV4(0x16,   0x00,         0x18,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160018ZZ     ), fn00000000, &ds16001801},
    {{REV4(0x16,   0x00,         0x18,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160018ZZ   ), fn00000000, &ds16001802},
    {{REV4(0x16,   0x00,         0x19,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160019ZZ     ), fn00000000, &ds16001901},
    {{REV4(0x16,   0x00,         0x19,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160019ZZ   ), fn00000000, &ds16001902},
    {{REV4(0x16,   0x00,         0x1A,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16001AZZ     ), fn00000000, &ds16001A01},
    {{REV4(0x16,   0x00,         0x1A,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16001AZZ   ), fn00000000, &ds16001A02},
    {{REV4(0x16,   0x00,         0x1B,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16001BZZ     ), fn00000000, &ds16001B01},
    {{REV4(0x16,   0x00,         0x1B,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16001BZZ   ), fn00000000, &ds16001B02},
    {{REV4(0x16,   0x00,         0x1C,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16001CZZ     ), fn00000000, &ds16001C01},
    {{REV4(0x16,   0x00,         0x1C,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16001CZZ   ), fn00000000, &ds16001C02},
    {{REV4(0x16,   0x00,         0x1D,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16001DZZ     ), fn00000000, &ds16001D01},
    {{REV4(0x16,   0x00,         0x1D,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16001DZZ   ), fn00000000, &ds16001D02},
    {{REV4(0x16,   0x00,         0x1E,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16001EZZ     ), fn00000000, &ds16001E01},
    {{REV4(0x16,   0x00,         0x1E,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16001EZZ   ), fn00000000, &ds16001E02},
    {{REV4(0x16,   0x00,         0x1F,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16001FZZ     ), fn00000000, &ds16001F01},
    {{REV4(0x16,   0x00,         0x1F,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16001FZZ   ), fn00000000, &ds16001F02},
    {{REV4(0x16,   0x00,         0x20,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160020ZZ     ), fn00000000, &ds16002001},
    {{REV4(0x16,   0x00,         0x20,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160020ZZ   ), fn00000000, &ds16002002},
    {{REV4(0x16,   0x00,         0x21,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160021ZZ     ), fn00000000, &ds16002101},
    {{REV4(0x16,   0x00,         0x21,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160021ZZ   ), fn00000000, &ds16002102},
    {{REV4(0x16,   0x00,         0x22,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160022ZZ     ), fn00000000, &ds16002201},
    {{REV4(0x16,   0x00,         0x22,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160022ZZ   ), fn00000000, &ds16002202},
    {{REV4(0x16,   0x00,         0x23,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160023ZZ     ), fn00000000, &ds16002301},
    {{REV4(0x16,   0x00,         0x23,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160023ZZ   ), fn00000000, &ds16002302},

     【电流不平衡事件记录】 
    {{REV4(0x17,   0x00,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee17000001      ), fn10010001, &ds17000001},
    {{REV4(0x17,   0x00,         0x00,         0x02)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee17000002      ), fn10010001, &ds17000002},
    {{REV4(0x17,   0x00,         0x01,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160001ZZ     ), NULL,       &ds17000101},
    {{REV4(0x17,   0x00,         0x01,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160001ZZ   ), NULL,       &ds17000102},
    {{REV4(0x17,   0x00,         0x02,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160002ZZ     ), fn00000000, &ds17000201},
    {{REV4(0x17,   0x00,         0x02,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160002ZZ   ), fn00000000, &ds17000202},
    {{REV4(0x17,   0x00,         0x03,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160003ZZ     ), fn00000000, &ds17000301},
    {{REV4(0x17,   0x00,         0x03,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160003ZZ   ), fn00000000, &ds17000302},
    {{REV4(0x17,   0x00,         0x04,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160004ZZ     ), fn00000000, &ds17000401},
    {{REV4(0x17,   0x00,         0x04,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160004ZZ   ), fn00000000, &ds17000402},
    {{REV4(0x17,   0x00,         0x05,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160005ZZ     ), fn00000000, &ds17000501},
    {{REV4(0x17,   0x00,         0x05,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160005ZZ   ), fn00000000, &ds17000502},
    {{REV4(0x17,   0x00,         0x06,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160006ZZ     ), fn00000000, &ds17000601},
    {{REV4(0x17,   0x00,         0x06,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160006ZZ   ), fn00000000, &ds17000602},
    {{REV4(0x17,   0x00,         0x07,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160007ZZ     ), fn00000000, &ds17000701},
    {{REV4(0x17,   0x00,         0x07,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160007ZZ   ), fn00000000, &ds17000702},
    {{REV4(0x17,   0x00,         0x08,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160008ZZ     ), fn00000000, &ds17000801},
    {{REV4(0x17,   0x00,         0x08,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160008ZZ   ), fn00000000, &ds17000802},
    {{REV4(0x17,   0x00,         0x09,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160009ZZ     ), fn00000000, &ds17000901},
    {{REV4(0x17,   0x00,         0x09,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160009ZZ   ), fn00000000, &ds17000902},
    {{REV4(0x17,   0x00,         0x0A,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16000AZZ     ), fn00000000, &ds17000A01},
    {{REV4(0x17,   0x00,         0x0A,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16000AZZ   ), fn00000000, &ds17000A02},
    {{REV4(0x17,   0x00,         0x0B,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16000BZZ     ), fn00000000, &ds17000B01},
    {{REV4(0x17,   0x00,         0x0B,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16000BZZ   ), fn00000000, &ds17000B02},
    {{REV4(0x17,   0x00,         0x0C,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16000CZZ     ), fn00000000, &ds17000C01},
    {{REV4(0x17,   0x00,         0x0C,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16000CZZ   ), fn00000000, &ds17000C02},
    {{REV4(0x17,   0x00,         0x0D,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16000DZZ     ), fn00000000, &ds17000D01},
    {{REV4(0x17,   0x00,         0x0D,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16000DZZ   ), fn00000000, &ds17000D02},
    {{REV4(0x17,   0x00,         0x0E,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16000EZZ     ), fn00000000, &ds17000E01},
    {{REV4(0x17,   0x00,         0x0E,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16000EZZ   ), fn00000000, &ds17000E02},
    {{REV4(0x17,   0x00,         0x0F,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16000FZZ     ), fn00000000, &ds17000F01},
    {{REV4(0x17,   0x00,         0x0F,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16000FZZ   ), fn00000000, &ds17000F02},
    {{REV4(0x17,   0x00,         0x10,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160010ZZ     ), fn00000000, &ds17001001},
    {{REV4(0x17,   0x00,         0x10,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160010ZZ   ), fn00000000, &ds17001002},
    {{REV4(0x17,   0x00,         0x11,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160011ZZ     ), fn00000000, &ds17001101},
    {{REV4(0x17,   0x00,         0x11,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160011ZZ   ), fn00000000, &ds17001102},
    {{REV4(0x17,   0x00,         0x12,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160012ZZ     ), fn16001201, &ds17001201},
    {{REV4(0x17,   0x00,         0x12,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160012ZZ   ), fn16001201, &ds17001202},
    {{REV4(0x17,   0x00,         0x13,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160013ZZ     ), NULL,       &ds17001301},
    {{REV4(0x17,   0x00,         0x13,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160013ZZ   ), NULL,       &ds17001302},
    {{REV4(0x17,   0x00,         0x14,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160014ZZ     ), fn00000000, &ds17001401},
    {{REV4(0x17,   0x00,         0x14,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160014ZZ   ), fn00000000, &ds17001402},
    {{REV4(0x17,   0x00,         0x15,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160015ZZ     ), fn00000000, &ds17001501},
    {{REV4(0x17,   0x00,         0x15,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160015ZZ   ), fn00000000, &ds17001502},
    {{REV4(0x17,   0x00,         0x16,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160016ZZ     ), fn00000000, &ds17001601},
    {{REV4(0x17,   0x00,         0x16,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160016ZZ   ), fn00000000, &ds17001602},
    {{REV4(0x17,   0x00,         0x17,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160017ZZ     ), fn00000000, &ds17001701},
    {{REV4(0x17,   0x00,         0x17,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160017ZZ   ), fn00000000, &ds17001702},
    {{REV4(0x17,   0x00,         0x18,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160018ZZ     ), fn00000000, &ds17001801},
    {{REV4(0x17,   0x00,         0x18,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160018ZZ   ), fn00000000, &ds17001802},
    {{REV4(0x17,   0x00,         0x19,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160019ZZ     ), fn00000000, &ds17001901},
    {{REV4(0x17,   0x00,         0x19,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160019ZZ   ), fn00000000, &ds17001902},
    {{REV4(0x17,   0x00,         0x1A,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16001AZZ     ), fn00000000, &ds17001A01},
    {{REV4(0x17,   0x00,         0x1A,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16001AZZ   ), fn00000000, &ds17001A02},
    {{REV4(0x17,   0x00,         0x1B,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16001BZZ     ), fn00000000, &ds17001B01},
    {{REV4(0x17,   0x00,         0x1B,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16001BZZ   ), fn00000000, &ds17001B02},
    {{REV4(0x17,   0x00,         0x1C,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16001CZZ     ), fn00000000, &ds17001C01},
    {{REV4(0x17,   0x00,         0x1C,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16001CZZ   ), fn00000000, &ds17001C02},
    {{REV4(0x17,   0x00,         0x1D,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16001DZZ     ), fn00000000, &ds17001D01},
    {{REV4(0x17,   0x00,         0x1D,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16001DZZ   ), fn00000000, &ds17001D02},
    {{REV4(0x17,   0x00,         0x1E,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16001EZZ     ), fn00000000, &ds17001E01},
    {{REV4(0x17,   0x00,         0x1E,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16001EZZ   ), fn00000000, &ds17001E02},
    {{REV4(0x17,   0x00,         0x1F,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16001FZZ     ), fn00000000, &ds17001F01},
    {{REV4(0x17,   0x00,         0x1F,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16001FZZ   ), fn00000000, &ds17001F02},
    {{REV4(0x17,   0x00,         0x20,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160020ZZ     ), fn00000000, &ds17002001},
    {{REV4(0x17,   0x00,         0x20,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160020ZZ   ), fn00000000, &ds17002002},
    {{REV4(0x17,   0x00,         0x21,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160021ZZ     ), fn00000000, &ds17002101},
    {{REV4(0x17,   0x00,         0x21,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160021ZZ   ), fn00000000, &ds17002102},
    {{REV4(0x17,   0x00,         0x22,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160022ZZ     ), fn00000000, &ds17002201},
    {{REV4(0x17,   0x00,         0x22,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160022ZZ   ), fn00000000, &ds17002202},
    {{REV4(0x17,   0x00,         0x23,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160023ZZ     ), fn00000000, &ds17002301},
    {{REV4(0x17,   0x00,         0x23,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160023ZZ   ), fn00000000, &ds17002302},

     【失流事件记录】 
    {{REV4(0x18, CI18010001,     0x00,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee18010001      ), fn10010001, &ds18010001},
    {{REV4(0x18, CI18010001,     0x00,         0x02)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee18010002      ), fn10010001, &ds18010002},
    {{REV4(0x18, CI18010101,     0x01,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ01ZZ), NULL,       &ds18010101},
    {{REV4(0x18, CI18010101,     0x02,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ02ZZ), fn00000000, &ds18010201},
    {{REV4(0x18, CI18010101,     0x03,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ03ZZ), fn00000000, &ds18010301},
    {{REV4(0x18, CI18010101,     0x04,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ04ZZ), fn00000000, &ds18010401},
    {{REV4(0x18, CI18010101,     0x05,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ05ZZ), fn00000000, &ds18010501},
    {{REV4(0x18, CI18010101,     0x06,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ06ZZ), fn00000000, &ds18010601},
    {{REV4(0x18, CI18010101,     0x07,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ07ZZ), fn00000000, &ds18010701},
    {{REV4(0x18, CI18010101,     0x08,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ08ZZ), fn00000000, &ds18010801},
    {{REV4(0x18, CI18010101,     0x09,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ09ZZ), fn00000000, &ds18010901},
    {{REV4(0x18, CI18010101,     0x0A,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ0AZZ), fn10010A01, &ds18010A01},
    {{REV4(0x18, CI18010101,     0x0B,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ0BZZ), fn10010B01, &ds18010B01},
    {{REV4(0x18, CI18010101,     0x0C,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ0CZZ), fn10010C01, &ds18010C01},
    {{REV4(0x18, CI18010101,     0x0D,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ0DZZ), fn10010C01, &ds18010D01},
    {{REV4(0x18, CI18010101,     0x0E,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ0EZZ), NULL,       &ds18010E01},
    {{REV4(0x18, CI18010101,     0x0F,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ0FZZ), fn00000000, &ds18010F01},
    {{REV4(0x18, CI18010101,     0x10,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ10ZZ), fn00000000, &ds18011001},
    {{REV4(0x18, CI18010101,     0x11,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ11ZZ), fn00000000, &ds18011101},
    {{REV4(0x18, CI18010101,     0x12,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ12ZZ), fn00000000, &ds18011201},
    {{REV4(0x18, CI18010101,     0x13,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ13ZZ), fn10010A01, &ds18011301},
    {{REV4(0x18, CI18010101,     0x14,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ14ZZ), fn10010B01, &ds18011401},
    {{REV4(0x18, CI18010101,     0x15,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ15ZZ), fn10010C01, &ds18011501},
    {{REV4(0x18, CI18010101,     0x16,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ16ZZ), fn10010C01, &ds18011601},
    {{REV4(0x18, CI18010101,     0x17,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ17ZZ), NULL,       &ds18011701},
    {{REV4(0x18, CI18010101,     0x18,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ18ZZ), fn00000000, &ds18011801},
    {{REV4(0x18, CI18010101,     0x19,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ19ZZ), fn00000000, &ds18011901},
    {{REV4(0x18, CI18010101,     0x1A,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ1AZZ), fn00000000, &ds18011A01},
    {{REV4(0x18, CI18010101,     0x1B,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ1BZZ), fn00000000, &ds18011B01},
    {{REV4(0x18, CI18010101,     0x1C,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ1CZZ), fn10010A01, &ds18011C01},
    {{REV4(0x18, CI18010101,     0x1D,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ1DZZ), fn10010B01, &ds18011D01},
    {{REV4(0x18, CI18010101,     0x1E,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ1EZZ), fn10010C01, &ds18011E01},
    {{REV4(0x18, CI18010101,     0x1F,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ1FZZ), fn10010C01, &ds18011F01},
    {{REV4(0x18, CI18010101,     0x20,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ20ZZ), NULL,       &ds18012001},
    {{REV4(0x18, CI18010101,     0x21,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ21ZZ), NULL,       &ds18012101},
    {{REV4(0x18, CI18010101,     0x22,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ22ZZ), fn00000000, &ds18012201},
    {{REV4(0x18, CI18010101,     0x23,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ23ZZ), fn00000000, &ds18012301},
    {{REV4(0x18, CI18010101,     0x24,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ24ZZ), fn00000000, &ds18012401},
    {{REV4(0x18, CI18010101,     0x25,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ25ZZ), fn00000000, &ds18012501},
    {{REV4(0x18, CI18010101,     0x26,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ26ZZ), fn00000000, &ds18012601},
    {{REV4(0x18, CI18010101,     0x27,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ27ZZ), fn00000000, &ds18012701},
    {{REV4(0x18, CI18010101,     0x28,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ28ZZ), fn00000000, &ds18012801},
    {{REV4(0x18, CI18010101,     0x29,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ29ZZ), fn00000000, &ds18012901},
    {{REV4(0x18, CI18010101,     0x2A,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ2AZZ), fn00000000, &ds18012A01},
    {{REV4(0x18, CI18010101,     0x2B,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ2BZZ), fn00000000, &ds18012B01},
    {{REV4(0x18, CI18010101,     0x2C,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ2CZZ), fn00000000, &ds18012C01},
    {{REV4(0x18, CI18010101,     0x2D,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ2DZZ), fn00000000, &ds18012D01},
    {{REV4(0x18, CI18010101,     0x2E,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ2EZZ), fn00000000, &ds18012E01},
    {{REV4(0x18, CI18010101,     0x2F,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ2FZZ), fn00000000, &ds18012F01},
    {{REV4(0x18, CI18010101,     0x30,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ30ZZ), fn00000000, &ds18013001},
    {{REV4(0x18, CI18010101,     0x31,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ31ZZ), fn00000000, &ds18013101},

     【过流事件记录】 
    {{REV4(0x19, CI19010001,     0x00,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee19010001                   ), fn10010001, NULL},
    {{REV4(0x19, CI19010001,     0x00,         0x02)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee19010002                   ), fn10010001, NULL},
    {{REV4(0x19, CI19010101,     0x01,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ01ZZ), NULL,       NULL},
    {{REV4(0x19, CI19010101,     0x02,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ02ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x03,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ03ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x04,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ04ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x05,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ05ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x06,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ06ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x07,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ07ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x08,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ08ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x09,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ09ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x0A,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ0AZZ), fn10010A01, NULL},
    {{REV4(0x19, CI19010101,     0x0B,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ0BZZ), fn10010B01, NULL},
    {{REV4(0x19, CI19010101,     0x0C,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ0CZZ), fn10010C01, NULL},
    {{REV4(0x19, CI19010101,     0x0D,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ0DZZ), fn10010C01, NULL},
    {{REV4(0x19, CI19010101,     0x0E,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ0EZZ), NULL,       NULL},
    {{REV4(0x19, CI19010101,     0x0F,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ0FZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x10,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ10ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x11,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ11ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x12,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ12ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x13,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ13ZZ), fn10010A01, NULL},
    {{REV4(0x19, CI19010101,     0x14,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ14ZZ), fn10010B01, NULL},
    {{REV4(0x19, CI19010101,     0x15,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ15ZZ), fn10010C01, NULL},
    {{REV4(0x19, CI19010101,     0x16,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ16ZZ), fn10010C01, NULL},
    {{REV4(0x19, CI19010101,     0x17,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ17ZZ), NULL,       NULL},
    {{REV4(0x19, CI19010101,     0x18,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ18ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x19,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ19ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x1A,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ1AZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x1B,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ1BZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x1C,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ1CZZ), fn10010A01, NULL},
    {{REV4(0x19, CI19010101,     0x1D,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ1DZZ), fn10010B01, NULL},
    {{REV4(0x19, CI19010101,     0x1E,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ1EZZ), fn10010C01, NULL},
    {{REV4(0x19, CI19010101,     0x1F,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ1FZZ), fn10010C01, NULL},
    {{REV4(0x19, CI19010101,     0x20,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ20ZZ), NULL,       NULL},
    {{REV4(0x19, CI19010101,     0x21,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ21ZZ), NULL,       NULL},
    {{REV4(0x19, CI19010101,     0x22,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ22ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x23,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ23ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x24,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ24ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x25,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ25ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x26,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ26ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x27,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ27ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x28,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ28ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x29,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ29ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x2A,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ2AZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x2B,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ2BZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x2C,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ2CZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x2D,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ2DZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x2E,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ2EZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x2F,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ2FZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x30,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ30ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x31,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ31ZZ), fn00000000, NULL},

     【断流事件记录】 
    {{REV4(0x1A, CI1A010001,     0x00,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1A010001                   ), fn10010001, NULL},
    {{REV4(0x1A, CI1A010001,     0x00,         0x02)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1A010002                   ), fn10010001, NULL},
    {{REV4(0x1A, CI1A010101,     0x01,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ01ZZ), NULL,       NULL},
    {{REV4(0x1A, CI1A010101,     0x02,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ02ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x03,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ03ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x04,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ04ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x05,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ05ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x06,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ06ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x07,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ07ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x08,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ08ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x09,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ09ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x0A,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ0AZZ), fn10010A01, NULL},
    {{REV4(0x1A, CI1A010101,     0x0B,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ0BZZ), fn10010B01, NULL},
    {{REV4(0x1A, CI1A010101,     0x0C,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ0CZZ), fn10010C01, NULL},
    {{REV4(0x1A, CI1A010101,     0x0D,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ0DZZ), fn10010C01, NULL},
    {{REV4(0x1A, CI1A010101,     0x0E,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ0EZZ), NULL,       NULL},
    {{REV4(0x1A, CI1A010101,     0x0F,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ0FZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x10,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ10ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x11,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ11ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x12,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ12ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x13,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ13ZZ), fn10010A01, NULL},
    {{REV4(0x1A, CI1A010101,     0x14,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ14ZZ), fn10010B01, NULL},
    {{REV4(0x1A, CI1A010101,     0x15,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ15ZZ), fn10010C01, NULL},
    {{REV4(0x1A, CI1A010101,     0x16,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ16ZZ), fn10010C01, NULL},
    {{REV4(0x1A, CI1A010101,     0x17,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ17ZZ), NULL,       NULL},
    {{REV4(0x1A, CI1A010101,     0x18,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ18ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x19,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ19ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x1A,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ1AZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x1B,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ1BZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x1C,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ1CZZ), fn10010A01, NULL},
    {{REV4(0x1A, CI1A010101,     0x1D,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ1DZZ), fn10010B01, NULL},
    {{REV4(0x1A, CI1A010101,     0x1E,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ1EZZ), fn10010C01, NULL},
    {{REV4(0x1A, CI1A010101,     0x1F,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ1FZZ), fn10010C01, NULL},
    {{REV4(0x1A, CI1A010101,     0x20,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ20ZZ), NULL,       NULL},
    {{REV4(0x1A, CI1A010101,     0x21,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ21ZZ), NULL,       NULL},
    {{REV4(0x1A, CI1A010101,     0x22,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ22ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x23,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ23ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x24,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ24ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x25,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ25ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x26,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ26ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x27,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ27ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x28,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ28ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x29,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ29ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x2A,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ2AZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x2B,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ2BZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x2C,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ2CZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x2D,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ2DZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x2E,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ2EZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x2F,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ2FZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x30,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ30ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x31,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ31ZZ), fn00000000, NULL},
    
    【有功功率反向事件记录】
    {{REV4(0x1B, CI1B010001,     0x00,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1B010001                   ), fn10010001,        NULL},
    {{REV4(0x1B, CI1B010001,     0x00,         0x02)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1B010002                   ), fn10010001,        NULL},
    {{REV4(0x1B, CI1B010101,     0x01,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140001ZZ), NULL,              NULL},
    {{REV4(0x1B, CI1B010101,     0x02,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140002ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x03,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140003ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x04,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140004ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x05,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140005ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x06,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140006ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x07,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140007ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x08,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140008ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x09,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140009ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x0A,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14000AZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x0B,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14000BZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x0C,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14000CZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x0D,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14000DZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x0E,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14000EZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x0F,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14000FZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x10,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140010ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x11,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140011ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x12,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140012ZZ), NULL,              NULL},
    {{REV4(0x1B, CI1B010101,     0x13,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140013ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x14,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140014ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x15,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140015ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x16,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140016ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x17,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140017ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x18,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140018ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x19,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140019ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x1A,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14001AZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x1B,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14001BZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x1C,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14001CZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x1D,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14001DZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x1E,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14001EZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x1F,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14001FZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x20,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140020ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x21,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140021ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x22,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140022ZZ), fn00000000,        NULL},

    【过载事件记录】
    {{REV4(0x1C, CI1C010001,     0x00,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1C010001                   ), fn10010001, NULL},
    {{REV4(0x1C, CI1C010001,     0x00,         0x02)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1C010002                   ), fn10010001, NULL},
    {{REV4(0x1C, CI1C010101,     0x01,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140001ZZ), NULL,       NULL},
    {{REV4(0x1C, CI1C010101,     0x02,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140002ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x03,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140003ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x04,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140004ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x05,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140005ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x06,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140006ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x07,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140007ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x08,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140008ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x09,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140009ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x0A,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14000AZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x0B,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14000BZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x0C,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14000CZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x0D,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14000DZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x0E,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14000EZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x0F,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14000FZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x10,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140010ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x11,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140011ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x12,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140012ZZ), NULL,       NULL},
    {{REV4(0x1C, CI1C010101,     0x13,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140013ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x14,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140014ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x15,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140015ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x16,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140016ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x17,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140017ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x18,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140018ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x19,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140019ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x1A,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14001AZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x1B,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14001BZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x1C,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14001CZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x1D,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14001DZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x1E,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14001EZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x1F,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14001FZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x20,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140020ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x21,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140021ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x22,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140022ZZ), fn00000000, NULL},
*/    
#if defined(M_LOCAL) || defined(M_REMOTE)
    /* 【拉闸事件记录】 */
    {{REV4(0x1D,   0x00,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee1D000001                   ), fn10010001, &ds1D000001},
    {{REV4(0x1D,   0x00,         0x01,   BI1D000101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee1D00ZZ01[0].m_1D0001ZZ   ), NULL,       &ds1D000101},
    {{REV4(0x1D,   0x00,         0x02,   BI1D000101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee1D00ZZ01[0].m_1D0002ZZ   ), NULL,       &ds1D000201},
    {{REV4(0x1D,   0x00,         0x03,   BI1D000101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee1D00ZZ01[0].m_1D0003ZZ   ), fn00000000, &ds1D000301},
    {{REV4(0x1D,   0x00,         0x04,   BI1D000101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee1D00ZZ01[0].m_1D0004ZZ   ), fn00000000, &ds1D000401},
//    {{REV4(0x1D,   0x00,   CI1D000501,   BI1D000101)}, 0x3000, SIZE_ADDR_OF(EE_sect4, ee1D00ZZ01[0].m_1D0005ZZ   ), fn00000000, &ds1D000501},

    /* 【合闸事件记录】 */
    {{REV4(0x1E,   0x00,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee1E000001                 ), fn10010001, &ds1E000001},
    {{REV4(0x1E,   0x00,         0x01,   BI1E000101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee1E00ZZ01[0].m_1D0001ZZ   ), NULL,       &ds1E000101},
    {{REV4(0x1E,   0x00,         0x02,   BI1E000101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee1E00ZZ01[0].m_1D0002ZZ   ), NULL,       &ds1E000201},
    {{REV4(0x1E,   0x00,         0x03,   BI1E000101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee1E00ZZ01[0].m_1D0003ZZ   ), fn00000000, &ds1E000301},
    {{REV4(0x1E,   0x00,         0x04,   BI1E000101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee1E00ZZ01[0].m_1D0004ZZ   ), fn00000000, &ds1E000401},
//    {{REV4(0x1E,   0x00,   CI1E000501,   BI1E000101)}, 0x3000, SIZE_ADDR_OF(EE_sect4, ee1E00ZZ01[0].m_1D0005ZZ   ), fn00000000, &ds1E000501},
#endif
/*
    【总功率因数超下限事件记录】
    {{REV4(0x1F,   0x00,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1F000001                   ), fn10010001, NULL},
    {{REV4(0x1F,   0x00,         0x00,         0x02)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1F000002                   ), fn10010001, NULL},
    {{REV4(0x1F,   0x00,         0x01,   BI1F000101)}, 0x1000, SIZE_ADDR_OF(DF_sect9, df1F00ZZ01._[0].m_1F0001ZZ   ), NULL,       NULL},
    {{REV4(0x1F,   0x00,         0x02,   BI1F000101)}, 0x1000, SIZE_ADDR_OF(DF_sect9, df1F00ZZ01._[0].m_1F0002ZZ   ), fn00000000, NULL},
    {{REV4(0x1F,   0x00,         0x03,   BI1F000101)}, 0x1000, SIZE_ADDR_OF(DF_sect9, df1F00ZZ01._[0].m_1F0003ZZ   ), fn00000000, NULL},
    {{REV4(0x1F,   0x00,         0x04,   BI1F000101)}, 0x1000, SIZE_ADDR_OF(DF_sect9, df1F00ZZ01._[0].m_1F0004ZZ   ), fn00000000, NULL},
    {{REV4(0x1F,   0x00,         0x05,   BI1F000101)}, 0x1000, SIZE_ADDR_OF(DF_sect9, df1F00ZZ01._[0].m_1F0005ZZ   ), fn00000000, NULL},
    {{REV4(0x1F,   0x00,         0x06,   BI1F000101)}, 0x1000, SIZE_ADDR_OF(DF_sect9, df1F00ZZ01._[0].m_1F0006ZZ   ), NULL,       NULL},
    {{REV4(0x1F,   0x00,         0x07,   BI1F000101)}, 0x1000, SIZE_ADDR_OF(DF_sect9, df1F00ZZ01._[0].m_1F0007ZZ   ), fn00000000, NULL},
    {{REV4(0x1F,   0x00,         0x08,   BI1F000101)}, 0x1000, SIZE_ADDR_OF(DF_sect9, df1F00ZZ01._[0].m_1F0008ZZ   ), fn00000000, NULL},
    {{REV4(0x1F,   0x00,         0x09,   BI1F000101)}, 0x1000, SIZE_ADDR_OF(DF_sect9, df1F00ZZ01._[0].m_1F0009ZZ   ), fn00000000, NULL},
    {{REV4(0x1F,   0x00,         0x0A,   BI1F000101)}, 0x1000, SIZE_ADDR_OF(DF_sect9, df1F00ZZ01._[0].m_1F000AZZ   ), fn00000000, NULL},
    
    【A/B/C相功率因数超下限事件记录】
    {{REV4(0x1F,   CI1F010001,   0x00,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1F010001      ),                    fn10010001, NULL},
    {{REV4(0x1F,   CI1F010001,   0x00,         0x02)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1F010002      ),                    fn10010001, NULL},
    {{REV4(0x1F,   CI1F010101,   0x01,   BI1F010101)}, 0x5200, SIZE_ADDR_OF(DF_sect9, df1F01ZZ01[0]._[0].m_1F0001ZZ      ), NULL,       NULL},
    {{REV4(0x1F,   CI1F010101,   0x02,   BI1F010101)}, 0x5200, SIZE_ADDR_OF(DF_sect9, df1F01ZZ01[0]._[0].m_1F0002ZZ      ), fn00000000, NULL},
    {{REV4(0x1F,   CI1F010101,   0x03,   BI1F010101)}, 0x5200, SIZE_ADDR_OF(DF_sect9, df1F01ZZ01[0]._[0].m_1F0003ZZ      ), fn00000000, NULL},
    {{REV4(0x1F,   CI1F010101,   0x04,   BI1F010101)}, 0x5200, SIZE_ADDR_OF(DF_sect9, df1F01ZZ01[0]._[0].m_1F0004ZZ      ), fn00000000, NULL},
    {{REV4(0x1F,   CI1F010101,   0x05,   BI1F010101)}, 0x5200, SIZE_ADDR_OF(DF_sect9, df1F01ZZ01[0]._[0].m_1F0005ZZ      ), fn00000000, NULL},
    {{REV4(0x1F,   CI1F010101,   0x06,   BI1F010101)}, 0x5200, SIZE_ADDR_OF(DF_sect9, df1F01ZZ01[0]._[0].m_1F0006ZZ      ), NULL,       NULL},
    {{REV4(0x1F,   CI1F010101,   0x07,   BI1F010101)}, 0x5200, SIZE_ADDR_OF(DF_sect9, df1F01ZZ01[0]._[0].m_1F0007ZZ      ), fn00000000, NULL},
    {{REV4(0x1F,   CI1F010101,   0x08,   BI1F010101)}, 0x5200, SIZE_ADDR_OF(DF_sect9, df1F01ZZ01[0]._[0].m_1F0008ZZ      ), fn00000000, NULL},
    {{REV4(0x1F,   CI1F010101,   0x09,   BI1F010101)}, 0x5200, SIZE_ADDR_OF(DF_sect9, df1F01ZZ01[0]._[0].m_1F0009ZZ      ), fn00000000, NULL},
    {{REV4(0x1F,   CI1F010101,   0x0A,   BI1F010101)}, 0x5200, SIZE_ADDR_OF(DF_sect9, df1F01ZZ01[0]._[0].m_1F000AZZ      ), fn00000000, NULL},
    
    【电流严重不平衡事件记录】
    {{REV4(0x20,   0x00,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee20000001      ), fn10010001, &ds17000001},
    {{REV4(0x20,   0x00,         0x00,         0x02)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee20000002      ), fn10010001, &ds17000002},
    {{REV4(0x20,   0x00,         0x01,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160001ZZ     ), NULL,       &ds17000101},
    {{REV4(0x20,   0x00,         0x01,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160001ZZ   ), NULL,       &ds17000102},
    {{REV4(0x20,   0x00,         0x02,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160002ZZ     ), fn00000000, &ds17000201},
    {{REV4(0x20,   0x00,         0x02,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160002ZZ   ), fn00000000, &ds17000202},
    {{REV4(0x20,   0x00,         0x03,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160003ZZ     ), fn00000000, &ds17000301},
    {{REV4(0x20,   0x00,         0x03,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160003ZZ   ), fn00000000, &ds17000302},
    {{REV4(0x20,   0x00,         0x04,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160004ZZ     ), fn00000000, &ds17000401},
    {{REV4(0x20,   0x00,         0x04,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160004ZZ   ), fn00000000, &ds17000402},
    {{REV4(0x20,   0x00,         0x05,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160005ZZ     ), fn00000000, &ds17000501},
    {{REV4(0x20,   0x00,         0x05,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160005ZZ   ), fn00000000, &ds17000502},
    {{REV4(0x20,   0x00,         0x06,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160006ZZ     ), fn00000000, &ds17000601},
    {{REV4(0x20,   0x00,         0x06,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160006ZZ   ), fn00000000, &ds17000602},
    {{REV4(0x20,   0x00,         0x07,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160007ZZ     ), fn00000000, &ds17000701},
    {{REV4(0x20,   0x00,         0x07,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160007ZZ   ), fn00000000, &ds17000702},
    {{REV4(0x20,   0x00,         0x08,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160008ZZ     ), fn00000000, &ds17000801},
    {{REV4(0x20,   0x00,         0x08,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160008ZZ   ), fn00000000, &ds17000802},
    {{REV4(0x20,   0x00,         0x09,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160009ZZ     ), fn00000000, &ds17000901},
    {{REV4(0x20,   0x00,         0x09,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160009ZZ   ), fn00000000, &ds17000902},
    {{REV4(0x20,   0x00,         0x0A,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16000AZZ     ), fn00000000, &ds17000A01},
    {{REV4(0x20,   0x00,         0x0A,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16000AZZ   ), fn00000000, &ds17000A02},
    {{REV4(0x20,   0x00,         0x0B,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16000BZZ     ), fn00000000, &ds17000B01},
    {{REV4(0x20,   0x00,         0x0B,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16000BZZ   ), fn00000000, &ds17000B02},
    {{REV4(0x20,   0x00,         0x0C,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16000CZZ     ), fn00000000, &ds17000C01},
    {{REV4(0x20,   0x00,         0x0C,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16000CZZ   ), fn00000000, &ds17000C02},
    {{REV4(0x20,   0x00,         0x0D,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16000DZZ     ), fn00000000, &ds17000D01},
    {{REV4(0x20,   0x00,         0x0D,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16000DZZ   ), fn00000000, &ds17000D02},
    {{REV4(0x20,   0x00,         0x0E,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16000EZZ     ), fn00000000, &ds17000E01},
    {{REV4(0x20,   0x00,         0x0E,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16000EZZ   ), fn00000000, &ds17000E02},
    {{REV4(0x20,   0x00,         0x0F,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16000FZZ     ), fn00000000, &ds17000F01},
    {{REV4(0x20,   0x00,         0x0F,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16000FZZ   ), fn00000000, &ds17000F02},
    {{REV4(0x20,   0x00,         0x10,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160010ZZ     ), fn00000000, &ds17001001},
    {{REV4(0x20,   0x00,         0x10,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160010ZZ   ), fn00000000, &ds17001002},
    {{REV4(0x20,   0x00,         0x11,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160011ZZ     ), fn00000000, &ds17001101},
    {{REV4(0x20,   0x00,         0x11,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160011ZZ   ), fn00000000, &ds17001102},
    {{REV4(0x20,   0x00,         0x12,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160012ZZ     ), fn16001201, &ds17001201},
    {{REV4(0x20,   0x00,         0x12,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160012ZZ   ), fn16001201, &ds17001202},
    {{REV4(0x20,   0x00,         0x13,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160013ZZ     ), NULL,       &ds17001301},
    {{REV4(0x20,   0x00,         0x13,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160013ZZ   ), NULL,       &ds17001302},
    {{REV4(0x20,   0x00,         0x14,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160014ZZ     ), fn00000000, &ds17001401},
    {{REV4(0x20,   0x00,         0x14,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160014ZZ   ), fn00000000, &ds17001402},
    {{REV4(0x20,   0x00,         0x15,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160015ZZ     ), fn00000000, &ds17001501},
    {{REV4(0x20,   0x00,         0x15,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160015ZZ   ), fn00000000, &ds17001502},
    {{REV4(0x20,   0x00,         0x16,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160016ZZ     ), fn00000000, &ds17001601},
    {{REV4(0x20,   0x00,         0x16,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160016ZZ   ), fn00000000, &ds17001602},
    {{REV4(0x20,   0x00,         0x17,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160017ZZ     ), fn00000000, &ds17001701},
    {{REV4(0x20,   0x00,         0x17,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160017ZZ   ), fn00000000, &ds17001702},
    {{REV4(0x20,   0x00,         0x18,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160018ZZ     ), fn00000000, &ds17001801},
    {{REV4(0x20,   0x00,         0x18,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160018ZZ   ), fn00000000, &ds17001802},
    {{REV4(0x20,   0x00,         0x19,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160019ZZ     ), fn00000000, &ds17001901},
    {{REV4(0x20,   0x00,         0x19,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160019ZZ   ), fn00000000, &ds17001902},
    {{REV4(0x20,   0x00,         0x1A,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16001AZZ     ), fn00000000, &ds17001A01},
    {{REV4(0x20,   0x00,         0x1A,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16001AZZ   ), fn00000000, &ds17001A02},
    {{REV4(0x20,   0x00,         0x1B,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16001BZZ     ), fn00000000, &ds17001B01},
    {{REV4(0x20,   0x00,         0x1B,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16001BZZ   ), fn00000000, &ds17001B02},
    {{REV4(0x20,   0x00,         0x1C,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16001CZZ     ), fn00000000, &ds17001C01},
    {{REV4(0x20,   0x00,         0x1C,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16001CZZ   ), fn00000000, &ds17001C02},
    {{REV4(0x20,   0x00,         0x1D,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16001DZZ     ), fn00000000, &ds17001D01},
    {{REV4(0x20,   0x00,         0x1D,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16001DZZ   ), fn00000000, &ds17001D02},
    {{REV4(0x20,   0x00,         0x1E,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16001EZZ     ), fn00000000, &ds17001E01},
    {{REV4(0x20,   0x00,         0x1E,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16001EZZ   ), fn00000000, &ds17001E02},
    {{REV4(0x20,   0x00,         0x1F,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16001FZZ     ), fn00000000, &ds17001F01},
    {{REV4(0x20,   0x00,         0x1F,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16001FZZ   ), fn00000000, &ds17001F02},
    {{REV4(0x20,   0x00,         0x20,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160020ZZ     ), fn00000000, &ds17002001},
    {{REV4(0x20,   0x00,         0x20,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160020ZZ   ), fn00000000, &ds17002002},
    {{REV4(0x20,   0x00,         0x21,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160021ZZ     ), fn00000000, &ds17002101},
    {{REV4(0x20,   0x00,         0x21,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160021ZZ   ), fn00000000, &ds17002102},
    {{REV4(0x20,   0x00,         0x22,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160022ZZ     ), fn00000000, &ds17002201},
    {{REV4(0x20,   0x00,         0x22,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160022ZZ   ), fn00000000, &ds17002202},
    {{REV4(0x20,   0x00,         0x23,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160023ZZ     ), fn00000000, &ds17002301},
    {{REV4(0x20,   0x00,         0x23,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160023ZZ   ), fn00000000, &ds17002302},

     潮流反向事件记录】
    {{REV4(0x21,       0x00,     0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee21000000), fn10010001, NULL},
    {{REV4(0x21,       0x00,     0x00,   BI21000001)}, 0x1000, SIZE_ADDR_OF(DF_sect8, df210000ZZ._[0]), NULL, NULL},
*/
    {{REV4(0x88,   0x88,         0x88,         0x88)}, 0x0800, sizeof(ro88888888), (uint32_t)&ro88888888, fn88888888, &ds88888888},
    {{REV4(0x99,   0x99,         0x99,         0x99)}, 0x0000, sizeof(ro04000105), (uint32_t)&ro04000105[0], fn99999999, &ds04000105},
    //{{REV4(0xF1,   0xF1,         0xF1,         0xF1)}, 0x0000, sizeof(fr.Meter_OPMode), (uint32_t)(&fr.Meter_OPMode), NULL, NULL},
    {{REV4(0xF1,   0xF1,         0xF1,         0xFE)}, 0x0434, SIZE_ADDR_OF(FR_sect0, first_verify_alignment),        NULL, NULL},
    {{REV4(0xF1,   0xF1,         0xF2,         0x00)}, 0x0400, SIZE_ADDR_OF(EE_sect9, ee_assertCnt),                  NULL, NULL},
    {{REV4(0xF1,   0xF1,         0xF2,         0x01)}, 0x0400, SIZE_ADDR_OF(EE_sect9, ee_assertRecord),               NULL, NULL},            
    {{REV4(0xF1,   0xF1,         0xF2,         0x02)}, 0x0400, SIZE_ADDR_OF(EE_sect9, ee_abnormalResetCnt),           NULL, NULL},  
    {{REV4(0xF1,   0xF1,         0xF2,         0x03)}, 0x0400, SIZE_ADDR_OF(EE_sect9, ee_useStackMax),                NULL, NULL},        
        
};

const int16_t DT_tableDim = dimof(DT_table);

#include <datatree.h>
#include <display.h>
#include "project.h"
#include "rtc.h"
#include "load_profile.h"
#include <energy.h>

NAME_THIS_FILE(_datatree)

// ---------------------------------------------------------------------- 版本号
#define SX_VER "V1.0"
// ------------------------------------------------------------------------ 市场
#define MARKET "SGCC"
// ------------------------------------------------------------------------- MCU
#if defined (__MSP430F5438__)
    #define MCU_NAME "5438"
#elif defined(__IO78F1168_A0_H__)
    #define MCU_NAME "1168"
#else
    #define MCU_NAME "?"
#endif
// -------------------------------------------------------------------- 计量芯片
#if defined (MEASURECHIP_ATT7022E)
    #define MPU_NAME "7022E"
#elif defined(MEASURECHIP_RN8302)
    #define MPU_NAME "8302"
#elif defined(MEASURECHIP_ADE7858)
    #define MPU_NAME "7858"
#else
    #define MPU_NAME "?"
#endif
// -------------------------------------------------------------------- 电表类型

#if defined(M_LOCAL)
    #define CMC    "DTZY"
    #define METER_TYPE "Local"
#elif defined(M_REMOTE)
    #define CMC    "DTZY"
    #define METER_TYPE "Remote"
#elif defined(M_SMART)
    #define CMC    "DTZ"
    #define METER_TYPE "Smart"
#else
    #define CMC    "?"
    #define METER_TYPE "?"
#endif   

// ------------------------------------------------------------------ 继电器方式
#if defined(RELAY_BUILT_IN)
    #define RELAY_TYPE
#else
    #if defined(M_LOCAL)||defined(M_REMOTE)
    #define RELAY_TYPE "_X"
    #else
    #define RELAY_TYPE
    #endif
#endif   

#define STR88888888() (SX_VER" "MARKET"_"CMC"_"METER_TYPE"_"MCU_NAME"_"MPU_NAME\
                       ""RELAY_TYPE)




// ROM区 =======================================================================
const uint8_t ro04000105[2]  = {REV2(0x00,0x80)};
const char    ro0400040D[16] = "DL/T 645 - 2007";

//#pragma location="DATA20_C_PROTECTED_AREAS"
const char ro88888888[64] = STR88888888();
 
// RAM区 =======================================================================
uint8_t  ra04000101[4];                                            // 日期及周次
uint8_t  ra04000102[3];                                                  // 时间

struct Xx02ZZZZZZ ra02ZZZZZZ;
/* 此区域的瞬时量在进入低功耗过程会在measure模块中被整块清零,增减变量时需同步调整清零长度 */
uint8_t  ra02010100[PN][2];                                        // A/B/C相电压
uint8_t  ra02020100[PN][3];                                        // A/B/C相电流
uint8_t  ra02030000[3];                                        // 瞬时有功总功率
uint8_t  ra02030100[PN][3];                                // A/B/C相瞬时有功功率
/*uint8_t  ra02040000[3];                                        // 瞬时无功总功率
uint8_t  ra02040100[3][3];                                // A/B/C相瞬时无功功率
uint8_t  ra02050000[3];                                        // 瞬时总视在功率
uint8_t  ra02050100[3][3];                                // A/B/C相瞬时视在功率*/
uint8_t  ra02060000[2] = {0x00,0x10};                              // 总功率因数
uint8_t  ra02060100[PN][2] = {{0x00,0x10}};                   // A/B/C相功率因数
uint8_t  ra02070100[PN][2];                                        // A/B/C相相角
/******************************************************************************/

//#if defined(M_SMART) 
//uint8_t  ra02080100[3][2];                              // A/B/C相电压波形失真度
//uint8_t  ra02090100[3][2];                              // A/B/C相电流波形失真度
//uint8_t  ra020A0101[3][1+HN][2];                 // A、B、C相电压0～HN次谐波含量
//uint8_t  ra020B0101[3][1+HN][2];                 // A、B、C相电流0～HN次谐波含量
//#endif
//uint8_t  ra02800001[3];                                            // 零线电流

/* 此区域的瞬时量在进入低功耗过程会在measure模块中被整块清零,增减变量时需同步调整清零长度 */
uint8_t  ra02800002[2];                                              // 电网频率
uint8_t  ra02800003[3];                                  // 一分钟有功总平均功率
uint8_t  ra02800004[3];                                          // 当前有功需量
uint8_t  ra02800005[3];                                          // 当前无功需量
uint8_t  ra02800006[3];                                        // 当前视在需量
/******************************************************************************/

uint8_t  ra02800007[2];                                              // 表内温度
uint8_t  ra02800008[2];                                    // 时钟电池电压(内部)
uint8_t  ra02800009[2];                                // 停电抄表电池电压(外部)
uint8_t  ra0280000A[4];                                      // 时钟电池工作时间
uint8_t  ra028000FC;                                           // 内部表计状态字
//uint8_t  ra02800100[3][2];                                // Uab/Uac/Ubc电压夹角

uint8_t   ra_APCF[3]={0x00,0x00,0x72};                        //高频脉冲输出设置

uint16_t ra04000501[7];                                    // 电表运行状态字1～7
uint8_t ra04001501[10];                                        // 主动上报状态字

uint8_t  ra02020100_ns[PN][3];                           // A/B/C相电流无符号数据
uint8_t  ra02030000_ns[3];                                     // 瞬时有功总功率
uint8_t  ra02030100_ns[PN][3];                             // A/B/C相瞬时有功功率
/*uint8_t  ra02040000_ns[3];                                     // 瞬时无功总功率
uint8_t  ra02040100_ns[3][3];                             // A/B/C相瞬时无功功率
uint8_t  ra02050000_ns[3];                                     // 瞬时总视在功率
uint8_t  ra02050100_ns[3][3];                             // A/B/C相瞬时视在功率*/
uint8_t  ra02060000_ns[2];                                         // 总功率因数
uint8_t  ra02060100_ns[PN][2];                                 // A/B/C相功率因数

/*========================= “可写”数据的RAM区对应 ==========================*/
uint8_t  ra04000103 = 5;
uint8_t  ra04000104 = 1;
uint8_t  ra04000106[5];                                    // 两套时区表切换时间
uint8_t  ra04000107[5];

uint16_t ra040001FC = 1;
uint8_t  ra040001FE = 3;
uint8_t  ra04000201 = ZN;
uint8_t  ra04000202 = BN;
uint8_t  ra04000203 = GN;
uint8_t  ra04000204 = TN;
uint16_t ra04000205 = 10;
uint8_t  ra04000206 = HN;
uint8_t  ra04000207 = LN -1;                                            //阶梯数

uint8_t  ra04000301 = 19;
uint8_t  ra04000302 = 5;
uint8_t  ra04000303 = 2;
uint8_t  ra04000304 = 4;
uint8_t  ra04000305 = 68;
uint8_t  ra04000308;
uint16_t ra040003EA[3] = {REV3(0x0002, 0x0000, 0x0000)};
uint16_t ra040003FA[3];
uint16_t ra040003FB[3];
uint16_t ra040003FC[3];
uint8_t  ra040003FE;

uint8_t  ra04000401[6];
uint8_t  ra04000402[6];
//uint8_t  ra04000403[32];
uint16_t ra04000404;
uint16_t ra04000405;
uint16_t ra04000406;
uint8_t  ra04000407;
uint8_t  ra04000408;
uint32_t ra04000409 = 3200;
uint32_t ra0400040A = 3200;
//uint8_t  ra0400040C[10];

uint8_t  ra04000601 = 0x09;
uint8_t  ra04000602[2] = {0x05, 0x50};

uint16_t ra04000701 = 1200;
uint16_t ra04000702 = 2400;
uint16_t ra04000703[3] = {2400, 2400, 2400};

uint8_t  ra04000801 = 0x3E;
uint8_t  ra04000802 = 1;

uint8_t  ra04000901 = 0xFF;                          // 负荷记录模式字
uint8_t  ra04000902 = 0xFF;                          // 定时冻结数据模式字
uint8_t  ra04000903 = 0xFF;                          // 瞬时冻结数据模式字
uint8_t  ra04000904 = 0xFF;                          // 约定冻结数据模式字
uint8_t  ra04000905 = 0x03;                          // 周期(整点)冻结数据模式字
uint8_t  ra04000906 = 0xFF;                          // 日冻结数据模式字

uint8_t  ra04000A01[4];
uint16_t ra04000A02[6] = {5, 5, 5, 5, 5, 5};

uint8_t  ra04000B01[3][2] = {
    {REV2(0x01,0x00)},
    {REV2(0x99,0x99)},
    {REV2(0x99,0x99)},
};

uint8_t  ra04000C01[10][4] = {
    {0, 0x00, 0x00, 0x00},
    {1, 0x00, 0x00, 0x00},
    {2, 0x00, 0x00, 0x00},
    {3, 0x00, 0x00, 0x00},
    {4, 0x00, 0x00, 0x00},
    {5, 0x00, 0x00, 0x00},
    {6, 0x00, 0x00, 0x00},
    {7, 0x00, 0x00, 0x00},
    {8, 0x00, 0x00, 0x00},
    {9, 0x00, 0x00, 0x00},
};
bool ra04000CFE;                                               // 允许进入软编程

uint8_t ra04001104[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};   //主动上报模式字

struct Xx04000D01_04 ra04000D01_04[3];
uint32_t ra04000E01 = (uint32_t)(3 * (UN * 1.5) * IMAX * 1e4 + 0.5);
uint32_t ra04000E02 = (uint32_t)(3 * (UN * 1.5) * IMAX * 1e4 + 0.5);
uint16_t ra04000E03 = (uint16_t)(UN * 1.5 * 1e1 + 0.5);
uint16_t ra04000E04 = (uint16_t)(UN * 0.6 * 1e1 + 0.5);
#if defined(M_LOCAL)
uint8_t  ra04001001[4] = {REV4(0x00, 0x00, 0x10, 0x00)};             //报警金额1
uint8_t  ra04001002[4] = {REV4(0x00, 0x00, 0x05, 0x00)};             //报警金额2
uint8_t  ra04001003[4] = {REV4(0x00, 0x00, 0x00, 0x00)};          //透支金额限值
uint8_t  ra04001004[4] = {REV4(0x99, 0x99, 0x99, 0x99)};          //囤积金额限值
uint8_t  ra04001005[4] = {REV4(0x00, 0x00, 0x00, 0x00)};      //合闸允许金额限值
#endif
uint8_t ra04001101;                                           // 电表运行特征字1
uint8_t ra04001201[5] = {0x00, 0x00, 0x01, 0x01, 0x10};      // 整点冻结起始时间
uint8_t ra04001202 = 60;                                     // 整点冻结时间间隔
uint8_t ra04001203[2] = {0x00, 0x01};                              // 日冻结时间
uint8_t ra04001301[1] = {0x00};                     //无线通信在线及强弱信号指示

uint16_t ra04001502;                                               // 插卡状态字
struct DispItem ra04040101[AN];
struct DispItem ra04040201[MN];
/*
uint16_t  ra04090101;                           // 失压事件电压触发上限
uint16_t  ra04090102;                           // 失压事件电压恢复下限
uint32_t  ra04090103;                           // 失压事件电流触发下限
uint8_t   ra04090104 = 1;                       // 失压事件触发延时时间
uint16_t  ra04090201;                           // 欠压事件电压触发上限
uint8_t   ra04090202 = 1;                       // 欠压事件触发延时时间
uint16_t  ra04090301;                           // 过压事件电压触发上限
uint8_t   ra04090302 = 1;                       // 过压事件触发延时时间
uint16_t  ra04090401;                           // 断相事件电压触发上限
uint32_t  ra04090402;                           // 断相事件电流触发上限
uint8_t   ra04090403 = 1;                       // 断相事件触发延时时间
uint16_t  ra04090501;                           // 电压不平衡率限值
uint8_t   ra04090502 = 1;                       // 电压不平衡率触发延时时间
uint16_t  ra04090601;                           // 电流不平衡率限值
uint8_t   ra04090602 = 1;                       // 电流不平衡率触发延时时间
uint16_t  ra04090701;                           // 失流事件电压触发下限
uint32_t  ra04090702;                           // 失流事件电流触发上限
uint32_t  ra04090703;                           // 失流事件电流触发下限
uint8_t   ra04090704 = 1;                       // 失流事件触发延时时间
uint16_t  ra04090801;                           // 过流事件电流触发下限
uint8_t   ra04090802 = 1;                       // 过流事件触发延时时间
uint16_t  ra04090901;                           // 断流事件电压触发下限
uint32_t  ra04090902;                           // 断流事件电流触发上限
uint8_t   ra04090903 = 1;                       // 断流事件触发延时时间
uint32_t  ra04090A01;                   // 潮流反向事件有功功率触发下限
uint8_t   ra04090A02 = 1;                   // 潮流反向事件触发延时时间
uint32_t  ra04091001;               // 有功功率反向事件有功功率触发下限
uint8_t   ra04091002 = 1;               // 有功功率反向事件判定延时时间
uint32_t  ra04090B01;                       // 过载事件有功功率触发下限
uint8_t   ra04090B02 = 1;                       // 过载事件触发延时时间
uint16_t  ra04090C01;                                   // 电压考核上限
uint16_t  ra04090C02;                                   // 电压考核下限
uint32_t  ra04090D01;                   // 有功需量超限事件需量触发下限
uint32_t  ra04090D02;                   // 无功需量超限事件需量触发下限
uint8_t   ra04090D03 = 1;                   // 需量超限事件触发延时时间
uint16_t  ra04090E01;                             // 总功率因数超限阀值
uint8_t   ra04090E02 = 1;               // 总功率因数超下限判定延时时间
uint16_t  ra04090F01;                             // 电流严重不平衡阀值
uint8_t   ra04090F02 = 1;                 // 电流严重不平衡触发延时时间
uint8_t   ra04090F11 = 60;                         //逆相序判断延时时间
*/
uint8_t ra00900200[4];                         // 当前剩余金额（用于显示、通信）
uint8_t ra0F000101[4];                                         // 购电前剩余金额
uint8_t ra00900201[4];                         // 当前透支金额（用于显示、通信）

uint8_t ra0280000B[4];                                           // 当前阶梯电价
uint8_t ra02800020[4];                                               // 当前电价
uint8_t ra02800021[4];                                           // 当前费率电价
uint8_t ra02800022[2];                                   // 身份认证时效剩余时间
uint8_t ra02800023[1];                                   // 红外认证时效剩余时间
uint8_t ra02800024[3];                                     // 本月总电压合格时间

uint8_t ra04000108[5];                                    //两套费率电价切换时间
uint8_t ra04000109[5];                                        //两套梯度切换时间
uint8_t ra04000306[3] = {REV3(0,0,1)};                         // 电流互感器变比
uint8_t ra04000307[3] = {REV3(0,0,1)};                         // 电压互感器变比
uint8_t ra0400040E[6];                                               // 客户编号

uint16_t ra04001401 = 5;                                          //跳闸延时时间


uint8_t ra04000208 = KN;                                           // 密钥总条数
uint32_t ra04000508;                                               // 密钥状态字

struct Xx0405ZZFF_TN ra040501FF;                               // 当前套费率数据
struct Xx0406ZZFF ra040604FF;                                  // 当前套阶梯数据

extern uint8_t ra_timeCheckoutMAC;

void DT_globalInit_CALLBACK(void)
{  
    /* 参变量中可写的数据可以通过writable_data_RAM_counterpart_restore()恢复, 
    ** 不可写的数据如040501FF, 040604FF需要在此恢复
    */
    D_ASSERT(!g_buf_locked);
    g_buf_locked = true;
#if defined(M_LOCAL)
    do {
        uint8_t a_id[4] = {REV4(0x04, 0x05,0x02, 0xFD)};
        /* 读取数据 */
        if (DT_get(a_id, g_buf)) {
            break;
        }
        /* 数据合法性检查 */
        if (fn0405ZZFF(DTE_FUNC_CONTEXT_WRITE_DATA_CHECK,
                                     a_id, 0xFF, g_buf, NULL,NULL))
        {
            break;
        }
        /* 转化到RAM区对应 */
        if (fn0405ZZFF(DTE_FUNC_CONTEXT_WRITE_DATA_TRANS,
                                     a_id, 0xFF, g_buf, NULL,NULL))
        {
            break;
        }
    }while(0);
    do {
        uint8_t a_id[4] = {REV4(0x04, 0x06,0x04, 0xFE)};
        /* 读取数据 */
        if (DT_get(a_id, g_buf)) {
            break;
        }
        /* 数据合法性检查 */
        if (fn0406ZZFF(DTE_FUNC_CONTEXT_WRITE_DATA_CHECK,
                                     a_id, 0xFF, g_buf, NULL,NULL))
        {
            break;
        }
        /* 转化到RAM区对应 */
        if (fn0406ZZFF(DTE_FUNC_CONTEXT_WRITE_DATA_TRANS,
                                     a_id, 0xFF, g_buf, NULL,NULL))
        {
            break;
        }
    }while(0);
#endif


    g_buf_locked = false;
}

// （非标准）处理函数 ----------------------------------------------------------
DTE_FUNC_PROTOTYPE(fn0E0F0000);
DTE_FUNC_PROTOTYPE(fn0E0F0100);
DTE_FUNC_PROTOTYPE(fn0F000100);
DTE_FUNC_PROTOTYPE(fn0F000101);
DTE_FUNC_PROTOTYPE(fn03060000);

#if defined (MEASURECHIP_ADE7858)
DTE_FUNC_PROTOTYPE(fn0E000000);
DTE_FUNC_PROTOTYPE(fn0E000029);
DTE_FUNC_PROTOTYPE(fn0E00002c);
DTE_FUNC_PROTOTYPE(fn0E000032);
DTE_FUNC_PROTOTYPE(fn0E010002);
DTE_FUNC_PROTOTYPE(fn0E010003);
DTE_FUNC_PROTOTYPE(fn0E0E0100);
DTE_FUNC_PROTOTYPE(fn0E0E0200);
DTE_FUNC_PROTOTYPE(fn0E0E0300);
DTE_FUNC_PROTOTYPE(fn0E0E0400);
#elif defined (MEASURECHIP_ATT7022E)
DTE_FUNC_PROTOTYPE(fn0D000000);
DTE_FUNC_PROTOTYPE(fn0D000016);
DTE_FUNC_PROTOTYPE(fn0D00001C);
DTE_FUNC_PROTOTYPE(fn0D010002);
DTE_FUNC_PROTOTYPE(fn0D010003);
DTE_FUNC_PROTOTYPE(fn0D010004);
DTE_FUNC_PROTOTYPE(fn0D010005);
DTE_FUNC_PROTOTYPE(fn0D0D0100);
DTE_FUNC_PROTOTYPE(fn0D0D0200);
DTE_FUNC_PROTOTYPE(fn0D0D0300);
DTE_FUNC_PROTOTYPE(fn0D0D0400);
#endif

/*============================= 数据树辅助结构 ===============================*/
const struct BiasedArraySpec DT_BASs[] = {
/*BI00000001*/ {0x01, 0x0C, DIM_SIZE_OF(EE_sect3, ee00ZZZZ01)},      // 电量
/*BI00D00001*/ {0x01, 0x04, DIM_SIZE_OF(EE_sect3, ee000DZZ01)},      // 年累计电量
/*BI00FE0001*/ {0x01, 0x0C, DIM_SIZE_OF(EE_sect3, ee00FEZZ01)},      // 电量结算时间
///*BI01010001*/ {0x01, 0x0C, DIM_SIZE_OF(EE_sect3, ee01ZZZZ01)},      // 需量
///*BI03050001*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03050001)},      // 全失压记录
#if defined(M_SMART)
///*BI03060001*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03060001)},      // 辅助电源失电
#endif
///*BI03100001*/ {0x01, 0x0C, DIM_SIZE_OF(EE_sect4, ee03100001)},      // 电压合格率统计数据
///*BI03100101*/ {0x01, 0x0C, DIM_SIZE_OF(EE_sect4, ee03100101[0])},   // A、B、C相电压合格率统计数据
///*BI03100201*/ {0x01, 0x0C, DIM_SIZE_OF(EE_sect4, ee03100101[1])},   // A、B、C相电压合格率统计数据
///*BI03100301*/ {0x01, 0x0C, DIM_SIZE_OF(EE_sect4, ee03100101[2])},   // A、B、C相电压合格率统计数据
/*BI03110001*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03110001)},      // 掉电
///*BI03120101*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03120101)},      // 正向有功需量超限记录
///*BI03120201*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03120201)},      // 反向有功需量超限记录
///*BI03120301*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03120301[0])},   // 第一、二、三四象限无功需量超限记录
///*BI03120401*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03120301[1])},   // 第一、二、三四象限无功需量超限记录
///*BI03120501*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03120301[2])},   // 第一、二、三四象限无功需量超限记录
///*BI03120601*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03120301[3])},   // 第一、二、三四象限无功需量超限记录
/*BI03300001*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300001)},      // 编程记录
/*BI03300101*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300101)},    // 电表清零记录
///*BI03300201*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, df03300201)},    // 需量清零记录
/*BI03300301*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300301)},      // 事件清零记录
/*BI03300401*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300401)},      // 校时记录
/*BI03300501*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300501)},    // 时段表编程记录
/*BI03300601*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300601)},    // 时区表编程记录
/*BI03300701*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300701)},      // 周休日编程记录
/*BI03300801*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300801)},    // 节假日编程记录
/*BI03300901*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300901)},      // 有功组合方式编程记录
///*BI03300A01*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300A01)},      // 无功组合方式1编程记录
///*BI03300B01*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300B01)},      // 无功组合方式2编程记录
/*BI03300C01*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300C01)},      // 结算日编程记录
/*BI03300D01*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300D01)},      // 开表盖记录
/*BI03300E01*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300E01)},      // 开端钮盒记录
/*BI03300F01*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03300F01)},    // 费率表编程记录
/*BI03301001*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03301001)},    // 阶梯表编程记录
/*BI03301201*/ {0x01, 0x02, DIM_SIZE_OF(EE_sect4, ee03301201)},      // 密钥更新记录
/*BI03301301*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03301301)},      // 异常插卡记录
#if defined(M_LOCAL)
/*BI03330101*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03330101)},      // 购电记录
#endif
/*BI03340001*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03340001)},      // 退费记录
/*BI03350001*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03350001)},      // 恒定磁场干扰记录
/*BI03360001*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03360001)},      // 负荷开关误动记录
/*BI03370001*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03370001)},      // 电源异常事件记录
/*BI05000001*/ {0x01, 0x3C, DIM_SIZE_OF(EE_sect5, ee0500ZZ01)},    // 定时冻结
/*BI05010001*/ {0x01, 0x03, DIM_SIZE_OF(EE_sect5, ee0501ZZ01)},    // 瞬时冻结
/*BI05020001*/ {0x01, 0x02, DIM_SIZE_OF(EE_sect5, ee0502ZZ01)},    // 两套时区表切换（约定冻结）
/*BI05030001*/ {0x01, 0x02, DIM_SIZE_OF(EE_sect5, ee0503ZZ01)},    // 两套日时段表切换（约定冻结）
/*BI05040001*/ {0x01, 0xFE, DIM_SIZE_OF(EE_sect5, ee0504ZZ01)},      // 周期（整点）冻结
#if defined(M_LOCAL)
/*BI05050001*/ {0x01, 0x02, DIM_SIZE_OF(EE_sect5, ee0505ZZ01)},    // 费率表切换冻结
#endif
/*BI05060001*/ {0x01, 0x3E, DIM_SIZE_OF(EE_sect5, ee0506ZZ01)},      // 日冻结EE区
/*BI05070001*/ {0x01, 0x02, DIM_SIZE_OF(EE_sect5, ee0507ZZ01)},    // 两套阶梯切换数据记录
///*BI10010102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect4, df1001ZZ02[0]._)}, // A、B、C相失压记录
///*BI10020102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect4, df1001ZZ02[1]._)},
///*BI10030102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect4, df1001ZZ02[2]._)},
///*BI11010102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect4, df1101ZZ02[0]._)}, // A、B、C相欠压记录
///*BI11020102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect4, df1101ZZ02[1]._)},
///*BI11030102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect4, df1101ZZ02[2]._)},
///*BI12010102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect5, df1201ZZ02[0]._)}, // A、B、C相过压记录
///*BI12020102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect5, df1201ZZ02[1]._)},
///*BI12030102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect5, df1201ZZ02[2]._)},
///*BI13010102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect5, df1301ZZ02[0]._)}, // A、B、C相断相记录
///*BI13020102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect5, df1301ZZ02[1]._)},
///*BI13030102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect5, df1301ZZ02[2]._)},
///*BI14000101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect5, df1400ZZ01._)},    // 电压逆相序记录
///*BI15000101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect6, df1500ZZ01._)},    // 电流逆相序记录
///*BI16000102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect6, df1600ZZ02._)},    // 电压不平衡记录
///*BI17000102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect6, df1700ZZ02._)},    // 电流不平衡记录
///*BI18010101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect6, df1801ZZ01[0]._)}, // A、B、C相失流记录
///*BI18020101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect6, df1801ZZ01[1]._)},
///*BI18030101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect6, df1801ZZ01[2]._)},
///*BI19010101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect7, df1901ZZ01[0]._)}, // A、B、C相过流记录
///*BI19020101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect7, df1901ZZ01[1]._)},
///*BI19030101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect7, df1901ZZ01[2]._)},
///*BI1A010101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect7, df1A01ZZ01[0]._)}, // A、B、C相断流记录
///*BI1A020101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect7, df1A01ZZ01[1]._)},
///*BI1A030101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect7, df1A01ZZ01[2]._)},
///*BI1B010101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect8, df1B01ZZ01[0]._)}, // A、B、C相有功功率反向记录
///*BI1B020101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect8, df1B01ZZ01[1]._)},
///*BI1B030101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect8, df1B01ZZ01[2]._)},
///*BI1C010101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect8, df1C01ZZ01[0]._)}, // A、B、C相过载记录
///*BI1C020101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect8, df1C01ZZ01[1]._)},
///*BI1C030101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect8, df1C01ZZ01[2]._)},
/*BI1D000101*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee1D00ZZ01)},    // 跳闸记录
/*BI1E000101*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee1E00ZZ01)},    // 合闸记录
///*BI1F000101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect9, df1F00ZZ01._)},    // 总功率因素超下限记录
///*BI1F010101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect9, df1F01ZZ01[0]._)}, // A、B、C相功率因素超下限记录
///*BI1F020101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect9, df1F01ZZ01[1]._)},
///*BI1F030101*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect9, df1F01ZZ01[2]._)},
///*BI20000102*/ {0x02, 0x0A, DIM_SIZE_OF(DF_sect6, df2000ZZ02._)},    // 电流严重不平衡记录
///*BI21000001*/ {0x01, 0x0A, DIM_SIZE_OF(DF_sect8, df210000ZZ._)},    // 潮流反向记录
///*BI03800101*/ {0x01, 0x0A, DIM_SIZE_OF(EE_sect4, ee03800101)},      // 非法校时记录(三星)
};
C_ASSERT(BI_END == dimof(DT_BASs));

const struct ConstantArraySpec DT_CASs[] = {
///*CI00030000*/ {0x03, 0x04-0x03+1, SIZE_OF(FR_sect4, fr00ZZZZ00.m_0003ZZZZ[0])},                  // 组合无功1,2
///*CI00050000*/ {0x05, 0x08-0x05+1, SIZE_OF(FR_sect4, fr00ZZZZ00.m_0005ZZZZ[0])},                  // 第一,二,三,四象限
///*CI00170000*/ {0x17, 0x18-0x17+1, SIZE_OF(FR_sect4, fr00ZZZZ00.m_0015_1E00ZZ[0].m_001700ZZ[0])}, // A相组合无功1,2
///*CI00190000*/ {0x19, 0x1C-0x19+1, SIZE_OF(FR_sect4, fr00ZZZZ00.m_0015_1E00ZZ[0].m_001900ZZ[0])}, // A相第一,二,三,四象限
///*CI002B0000*/ {0x2B, 0x2C-0x2B+1, SIZE_OF(FR_sect4, fr00ZZZZ00.m_0015_1E00ZZ[1].m_001700ZZ[0])}, // B相组合无功1,2
///*CI002D0000*/ {0x2D, 0x30-0x2D+1, SIZE_OF(FR_sect4, fr00ZZZZ00.m_0015_1E00ZZ[1].m_001900ZZ[0])}, // B相第一,二,三,四象限
///*CI003F0000*/ {0x3F, 0x40-0x3F+1, SIZE_OF(FR_sect4, fr00ZZZZ00.m_0015_1E00ZZ[2].m_001700ZZ[0])}, // C相组合无功1,2 
///*CI00410000*/ {0x41, 0x44-0x41+1, SIZE_OF(FR_sect4, fr00ZZZZ00.m_0015_1E00ZZ[2].m_001900ZZ[0])}, // C相第一,二,三,四象限
///*CI01030000*/ {0x03, 0x04-0x03+1, SIZE_OF(FR_sect4, fr01ZZZZ00.m_0103ZZZZ[0])},                  // 组合无功1,2需量
///*CI01050000*/ {0x05, 0x08-0x05+1, SIZE_OF(FR_sect4, fr01ZZZZ00.m_0105ZZZZ[0])},                  // 第一,二,三,四象限需量
//! /*CI01170000*/ {0x17, 0x18-0x17+1, SIZE_OF(FR_sect4, fr01ZZZZ00.m_0115_1E00ZZ[0].m_011700ZZ[0])},
//! /*CI01190000*/ {0x19, 0x1C-0x19+1, SIZE_OF(FR_sect4, fr01ZZZZ00.m_0115_1E00ZZ[0].m_011900ZZ[0])},
//! /*CI012B0000*/ {0x2B, 0x2C-0x2B+1, SIZE_OF(FR_sect4, fr01ZZZZ00.m_0115_1E00ZZ[1].m_011700ZZ[0])},
//! /*CI012D0000*/ {0x2D, 0x30-0x2D+1, SIZE_OF(FR_sect4, fr01ZZZZ00.m_0115_1E00ZZ[1].m_011900ZZ[0])},
//! /*CI013F0000*/ {0x3F, 0x40-0x3F+1, SIZE_OF(FR_sect4, fr01ZZZZ00.m_0115_1E00ZZ[2].m_011700ZZ[0])},
//! /*CI01410000*/ {0x41, 0x44-0x41+1, SIZE_OF(FR_sect4, fr01ZZZZ00.m_0115_1E00ZZ[2].m_011900ZZ[0])},
/*CI02010100*/ {0x01, 0x03-0x01+1, sizeof(ra02010100[0])},
/*CI02020100*/ {0x01, 0x03-0x01+1, sizeof(ra02020100[0])},
/*CI02030100*/ {0x01, 0x03-0x01+1, sizeof(ra02030100[0])},
///*CI02040100*/ {0x01, 0x03-0x01+1, sizeof(ra02040100[0])},    // 无功功率
///*CI02050100*/ {0x01, 0x03-0x01+1, sizeof(ra02050100[0])},    // 视在功率
/*CI02060100*/ {0x01, 0x03-0x01+1, sizeof(ra02060100[0])},
/*CI02070100*/ {0x01, 0x03-0x01+1, sizeof(ra02070100[0])},
#if defined(M_SMART)
///*CI02080100*/ {0x01, 0x03-0x01+1, sizeof(ra02080100[0])},      //电压波形失真度
///*CI02090100*/ {0x01, 0x03-0x01+1, sizeof(ra02090100[0])},      //电流波形失真度
#endif
/*CI04000501*/ {0x01, 0x07-0x01+1, sizeof(ra04000501[0])},
///*CI04000602*/ {0x02, 0x03-0x02+1, SIZE_OF(EE_sect2, ee04000602[0])},
/*CI04000703*/ {0x03, 0x05-0x03+1, SIZE_OF(EE_sect2, ee04000703[0])},
/*CI04000A02*/ {0x02, 0x07-0x02+1, SIZE_OF(EE_sect2, ee04000A02[0])},
/*CI04000B01*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect2, ee04000B01[0])},
/*CI04010000*/ {0x01, 0x02-0x01+1, SIZE_OF(EE_sect2, ee040100ZZ[0])},
/*CI04010001*/ {0x01,          BN, SIZE_OF(EE_sect2, ee040100ZZ[0].ee04ZZ0001[0])},
/*CI04030001*/ {0x01,          DN, SIZE_OF(EE_sect2, ee04030001[0])},
/*CI04040101*/ {0x01,          AN, SIZE_OF(EE_sect2, ee04040101[0])},
/*CI04040201*/ {0x01,          MN, SIZE_OF(EE_sect2, ee04040201[0])},
#if defined(M_LOCAL)
/*CI04050100*/ {0x01, 0x02-0x01+1, SIZE_OF(EE_sect2, ee0405ZZFF[0])},
/*CI04050101*/ {0x01,          TN, SIZE_OF(EE_sect2, ee0405ZZFF[0].m_0405ZZMO[0])}, // 费率数据
/*CI0406ZZEN*/ {0x01, LN-1-0x01+1, SIZE_OF(Xx0406ZZFF, m_0406ZZEN[0])},             // 阶梯值
/*CI0406ZZMO*/ {  LN,   LN-0x01+1, SIZE_OF(Xx0406ZZFF, m_0406ZZMO[0])},             // 阶梯电价
/*CI0406ZZYS*/ {2*LN,         YSN, SIZE_OF(Xx0406ZZFF, m_0406ZZYS[0])},             // 年结算日
#endif
///*CI05000301*/ {0x03, 0x04-0x03+1, SIZE_OF(EE_sect5, df0500ZZ01[0].m_05ZZ03ZZ[0])},
///*CI05000501*/ {0x05, 0x08-0x05+1, SIZE_OF(EE_sect5, df0500ZZ01[0].m_05ZZ05ZZ[0])},
/*CI06010000*/ {0x01, 0x06-0x01+1, 0},
#if defined(M_SMART)
/*CI020A0101*/ {0x01, 0x03-0x01+1, sizeof(ra020A0101[0])},            //谐波含量
#endif
#if defined(M_LOCAL)
/*CI0E0F0201*/ {0x01,          TN, 4},
/*CI0E0F0301*/ {0x01,        LN-1, 4},
/*CI0E0F0401*/ {0x01,          LN, 4},
#endif
///*CI10010001*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee10010001)+SIZE_OF(EE_sect5, ee10010002)},
///*CI10010101*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee1001ZZ01[0])},
///*CI10010102*/ {0x01, 0x03-0x01+1, SIZE_OF(DF_sect4, df1001ZZ02[0])},
///*CI11010001*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee11010001)+SIZE_OF(EE_sect5, ee11010002)},
///*CI11010101*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee1101ZZ01[0])},
///*CI11010102*/ {0x01, 0x03-0x01+1, SIZE_OF(DF_sect4, df1101ZZ02[0]._)},
///*CI12010001*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee12010001)+SIZE_OF(EE_sect5, ee12010002)},
///*CI12010101*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee1201ZZ01[0])},
///*CI12010102*/ {0x01, 0x03-0x01+1, SIZE_OF(DF_sect5, df1201ZZ02[0]._)},
///*CI13010001*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee13010001)+SIZE_OF(EE_sect5, ee13010002)},
///*CI13010101*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee1301ZZ01[0])},
///*CI13010102*/ {0x01, 0x03-0x01+1, SIZE_OF(DF_sect5, df1301ZZ02[0]._)},
///*CI18010001*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee18010001)+SIZE_OF(EE_sect5, ee18010002)},
///*CI18010101*/ {0x01, 0x03-0x01+1, SIZE_OF(DF_sect6, df1801ZZ01[0])},
///*CI19010001*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee19010001)+SIZE_OF(EE_sect5, ee19010002)},
///*CI19010101*/ {0x01, 0x03-0x01+1, SIZE_OF(DF_sect7, df1901ZZ01[0])},
///*CI1A010001*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee1A010001)+SIZE_OF(EE_sect5, ee1A010002)},
///*CI1A010101*/ {0x01, 0x03-0x01+1, SIZE_OF(DF_sect7, df1A01ZZ01[0])},
///*CI1B010001*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee1B010001)+SIZE_OF(EE_sect5, ee1B010002)},
///*CI1B010101*/ {0x01, 0x03-0x01+1, SIZE_OF(DF_sect8, df1B01ZZ01[0])},
///*CI1C010001*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee1C010001)+SIZE_OF(EE_sect5, ee1C010002)},
///*CI1C010101*/ {0x01, 0x03-0x01+1, SIZE_OF(DF_sect8, df1C01ZZ01[0])},
///*CI1D000501*/ {0x05, 0x08-0x05+1, SIZE_OF(DF_sect9, df1D00ZZ01[0].m_1D0005ZZ)},
///*CI1E000501*/ {0x05, 0x08-0x05+1, SIZE_OF(DF_sect9, df1E00ZZ01[0].m_1D0005ZZ)},
///*CI1F010001*/ {0x01, 0x03-0x01+1, SIZE_OF(EE_sect5, ee1F010001)+SIZE_OF(EE_sect5, ee1F010002)},
///*CI1F010101*/ {0x01, 0x03-0x01+1, SIZE_OF(DF_sect9, df1F01ZZ01[0])},
///*CI02800100*/ {0x01, 0x03-0x01+1, sizeof(ra02800100[0])},
};
C_ASSERT(CI_END - CI_OFS == dimof(DT_CASs));

const struct DynamicArraySpec DT_DASs[] = {
/*DI00000100*/ {0x01, &ra04000204, SIZE_OF(FR_sect4, fr00ZZZZ00.m_000001ZZ[0])},
///*DI01010100*/ {0x01, &ra04000204, SIZE_OF(FR_sect4, fr01ZZZZ00.m_010101ZZ[0])},
#if defined(M_SMART)
/*DI020A0101*/ {0x01, &ra04000206, sizeof(ra020A0101[0][0])},     //谐波分析次数
#endif
};
C_ASSERT(DI_END - DI_OFS == dimof(DT_DASs));


/*================================= 数据树 ===================================*/
const struct DataTreeEntry DT_table[] = {
    {{REV4(0x00,   0x00,         0x00,         0x00)}, 0x0000, 0x04, (uint32_t)&RPwrTtl_Dtr[0] ,                    fn00000000, &ds00000000},
    {{REV4(0x00,   0x00,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_000000ZZ   ), fn00000000, &ds00000001},
    {{REV4(0x00,   0x00,     DI00000100,       0x00)}, 0x2000, 0x04, (uint32_t)&RPwrTtl_Dtr[4] ,                    fn00000000, &ds00000100},
    {{REV4(0x00,   0x00,     DI00000100, BI00000001)}, 0x3000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_000001ZZ[0]), fn00000000, &ds00000101},
    {{REV4(0x00,   0x01,         0x00,         0x00)}, 0x0000, 0x04, (uint32_t)&RPPwrTtl_Dtr[0],                    fn00000000, &ds00010000},
    {{REV4(0x00,   0x01,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_000100ZZ   ), fn00000000, &ds00010001},
    {{REV4(0x00,   0x01,     DI00000100,       0x00)}, 0x2000, 0x04, (uint32_t)&RPPwrTtl_Dtr[4],                    fn00000000, &ds00010100},
    {{REV4(0x00,   0x01,     DI00000100, BI00000001)}, 0x3000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_000101ZZ[0]), fn00000000, &ds00010101},
    {{REV4(0x00,   0x02,         0x00,         0x00)}, 0x0000, 0x04, (uint32_t)&RNPwrTtl_Dtr[0],                    fn00000000, &ds00020000},
    {{REV4(0x00,   0x02,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_000200ZZ   ), fn00000000, &ds00020001},
    {{REV4(0x00,   0x02,     DI00000100,       0x00)}, 0x2000, 0x04, (uint32_t)&RNPwrTtl_Dtr[4],                    fn00000000, &ds00020100},
    {{REV4(0x00,   0x02,     DI00000100, BI00000001)}, 0x3000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_000201ZZ[0]), fn00000000, &ds00020101},
/*
    {{REV4(0x00, CI00030000,     0x00,         0x00)}, 0x4000, 0x05, (uint32_t)&RPImpwrTtl_Dtr[0] ,                 fn00000000, &ds00030000},
    {{REV4(0x00, CI00030000,     0x00,   BI00000001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0003ZZZZ[0].m_00ZZ00ZZ   ), fn00000000, &ds00030001},
    {{REV4(0x00, CI00030000, DI00000100,       0x00)}, 0x6000, 0x05, (uint32_t)&RPImpwrTtl_Dtr[5] ,                 fn00000000, &ds00030100},
    {{REV4(0x00, CI00030000, DI00000100, BI00000001)}, 0x7000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0003ZZZZ[0].m_00ZZ01ZZ[0]), fn00000000, &ds00030101},
    {{REV4(0x00, CI00050000,     0x00,         0x00)}, 0x4000, 0x05, (uint32_t)&RQ1_ImpwrTtl_Dtr[0],                fn00000000, &ds00050000},
    {{REV4(0x00, CI00050000,     0x00,   BI00000001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0005ZZZZ[0].m_00ZZ00ZZ   ), fn00000000, &ds00050001},
    {{REV4(0x00, CI00050000, DI00000100,       0x00)}, 0x6000, 0x05, (uint32_t)&RQ1_ImpwrTtl_Dtr[5],                fn00000000, &ds00050100},
    {{REV4(0x00, CI00050000, DI00000100, BI00000001)}, 0x7000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0005ZZZZ[0].m_00ZZ01ZZ[0]), fn00000000, &ds00050101},
    {{REV4(0x00,   0x09,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_000900ZZ   ), fn00000000, NULL},
    {{REV4(0x00,   0x09,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_000900ZZ   ), fn00000000, NULL},
    {{REV4(0x00,   0x09,     DI00000100,       0x00)}, 0x2000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_000901ZZ[0]), fn00000000, NULL},
    {{REV4(0x00,   0x09,     DI00000100, BI00000001)}, 0x3000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_000901ZZ[0]), fn00000000, NULL},
    {{REV4(0x00,   0x0A,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_000A00ZZ   ), fn00000000, NULL},
    {{REV4(0x00,   0x0A,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_000A00ZZ   ), fn00000000, NULL},
    {{REV4(0x00,   0x0A,     DI00000100,       0x00)}, 0x2000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_000A01ZZ[0]), fn00000000, NULL},
    {{REV4(0x00,   0x0A,     DI00000100, BI00000001)}, 0x3000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_000A01ZZ[0]), fn00000000, NULL},
*/
    {{REV4(0x00,   0x0B,         0x00,         0x00)}, 0x0000, 0x05, (uint32_t)&ra000B0000[0],     fn00000000, &ds000B0000},
    {{REV4(0x00,   0x0B,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect3, ee000B0001), fn00000000, &ds000B0001},
    
    {{REV4(0x00,   0x0C,         0x00,         0x00)}, 0x0000, 0x05, (uint32_t)&ra000C0000[0],     fn00000000, &ds000B0000},
    {{REV4(0x00,   0x0C,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect3, ee000C0001), fn00000000, &ds000B0001},
    {{REV4(0x00,   0x0D,         0x00,         0x00)}, 0x0000, 0x08, (uint32_t)0,                  fn000D0000, &ds000D0000},
    {{REV4(0x00,   0x0D,         0x00,   BI000D0001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee000DZZ01[0].m_000D0001), fn000D0000, &ds000D0001},
    {{REV4(0x00,   0x0D,         0xFE,   BI000D0001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee000DZZ01[0].m_000DFE01), NULL, NULL},        
/*
    {{REV4(0x00,   0x15,         0x00,         0x00)}, 0x0000, 0x05, (uint32_t)&RPAPPwr_Dtr[0],    fn00000000, &ds00150000},
    {{REV4(0x00,   0x15,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[0].m_001500ZZ), fn00000000, &ds00150001},
    {{REV4(0x00,   0x16,         0x00,         0x00)}, 0x0000, 0x05, (uint32_t)&RPAPPwr_Dtr[5],    fn00000000, &ds00160000},
    {{REV4(0x00,   0x16,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[0].m_001600ZZ), fn00000000, &ds00160001},
    {{REV4(0x00, CI00170000,     0x00,         0x00)}, 0x4000, 0x05, (uint32_t)&RPAPPwr_Dtr[10] ,                               fn00000000, &ds00170000},
    {{REV4(0x00, CI00170000,     0x00,   BI00000001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[0].m_001700ZZ[0]), fn00000000, &ds00170001},
    {{REV4(0x00, CI00190000,     0x00,         0x00)}, 0x4000, 0x05, (uint32_t)&RPAPPwr_Dtr[20] , fn00000000, &ds00190000},
    {{REV4(0x00, CI00190000,     0x00,   BI00000001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[0].m_001900ZZ[0]), fn00000000, &ds00190001},
    {{REV4(0x00,   0x1D,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0015_1E00ZZ[0].m_001D00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x1D,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[0].m_001D00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x1E,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0015_1E00ZZ[0].m_001E00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x1E,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[0].m_001E00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x29,         0x00,         0x00)}, 0x0000, 0x05, (uint32_t)&RPBPPwr_Dtr[0],                                   fn00000000, &ds00290000},
    {{REV4(0x00,   0x29,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[1].m_001500ZZ), fn00000000, &ds00290001},
    {{REV4(0x00,   0x2A,         0x00,         0x00)}, 0x0000, 0x05, (uint32_t)&RPBPPwr_Dtr[5],                                   fn00000000, &ds002A0000},
    {{REV4(0x00,   0x2A,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[1].m_001600ZZ), fn00000000, &ds002A0001},
    {{REV4(0x00, CI002B0000,     0x00,         0x00)}, 0x4000, 0x05, (uint32_t)&RPBPPwr_Dtr[10] ,                                  fn00000000, &ds002B0000},
    {{REV4(0x00, CI002B0000,     0x00,   BI00000001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[1].m_001700ZZ[0]), fn00000000, &ds002B0001},
    {{REV4(0x00, CI002D0000,     0x00,         0x00)}, 0x4000, 0x05, (uint32_t)&RPBPPwr_Dtr[20] , fn00000000, &ds002D0000},
    {{REV4(0x00, CI002D0000,     0x00,   BI00000001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[1].m_001900ZZ[0]), fn00000000, &ds002D0001},
    {{REV4(0x00,   0x31,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0015_1E00ZZ[1].m_001D00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x31,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[1].m_001D00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x32,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0015_1E00ZZ[1].m_001E00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x32,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[1].m_001E00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x3D,         0x00,         0x00)}, 0x0000, 0x05, (uint32_t)&RPCPPwr_Dtr[0], fn00000000, &ds003D0000},
    {{REV4(0x00,   0x3D,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[2].m_001500ZZ), fn00000000, &ds003D0001},
    {{REV4(0x00,   0x3E,         0x00,         0x00)}, 0x0000, 0x05, (uint32_t)&RPCPPwr_Dtr[5], fn00000000, &ds003E0000},
    {{REV4(0x00,   0x3E,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[2].m_001600ZZ), fn00000000, &ds003E0001},
    {{REV4(0x00, CI003F0000,     0x00,         0x00)}, 0x4000, 0x05, (uint32_t)&RPCPPwr_Dtr[10] ,                                  fn00000000, &ds003F0000},
    {{REV4(0x00, CI003F0000,     0x00,   BI00000001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[2].m_001700ZZ[0]), fn00000000, &ds003F0001},
    {{REV4(0x00, CI00410000,     0x00,         0x00)}, 0x4000, 0x05, (uint32_t)&RPCPPwr_Dtr[20] , fn00000000, &ds00410000},
    {{REV4(0x00, CI00410000,     0x00,   BI00000001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[2].m_001900ZZ[0]), fn00000000, &ds00410001},
    {{REV4(0x00,   0x45,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0015_1E00ZZ[2].m_001D00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x45,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[2].m_001D00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x46,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0015_1E00ZZ[2].m_001E00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x46,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0015_1E00ZZ[2].m_001E00ZZ), fn00000000, NULL},
    不支持数据【关联电能】
    {{REV4(0x00,   0x80,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_008000ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x80,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_008000ZZ), fn00000000, NULL},
    
#if defined(M_SMART)
    【正向有功基波电能 反向有功基波电能 正向有功谐波电能 反向有功谐波电能】
    {{REV4(0x00,   0x81,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_008100ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x81,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_008100ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x82,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_008200ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x82,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_008200ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x83,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_008300ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x83,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_008300ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x84,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_008400ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x84,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_008400ZZ), fn00000000, NULL},
#endif
    {{REV4(0x00,   0x85,         0x00,         0x00)}, 0x0000, 0x05, (uint32_t)&RPLCU_pwr_Dtr[0] ,  fn00000000, NULL},
    {{REV4(0x00,   0x85,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_008500ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x86,         0x00,         0x00)}, 0x0000, 0x05, (uint32_t)&RPLFE_pwr_Dtr[0] ,  fn00000000, NULL},
    {{REV4(0x00,   0x86,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_008600ZZ), fn00000000, NULL},
#if defined(M_LOCAL)
    //{{REV4(0x00,   0x90,         0x01,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect5, fr00900100), NULL, &ds00900100},
    //{{REV4(0x00,   0x90,         0x01,         0x01)}, 0x0000, SIZE_ADDR_OF(FR_sect5, fr00900101), NULL, &ds00900101},
    {{REV4(0x00,   0x90,         0x02,         0x00)}, 0x0000, 4, (uint32_t)&ra00900200[0], fn00900200, &ds00900200},
    {{REV4(0x00,   0x90,         0x02,         0x01)}, 0x0000, 4, (uint32_t)&ra00900201[0], fn00900201, &ds00900201},
#endif
    不支持数据【A相关联电能】
    {{REV4(0x00,   0x94,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[0].m_009400ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x94,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect2, ee00ZZZZ01[0].m_0094_9A00ZZ[0].m_009400ZZ), fn00000000, NULL},
    
#if defined(M_SMART)
    【A相 正向有功基波电能 反向有功基波电能 正向有功谐波电能 反向有功谐波电能】
    {{REV4(0x00,   0x95,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[0].m_009500ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x95,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[0].m_009500ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x96,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[0].m_009600ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x96,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[0].m_009600ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x97,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[0].m_009700ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x97,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[0].m_009700ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x98,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[0].m_009800ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x98,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[0].m_009800ZZ), fn00000000, NULL},
#endif
    {{REV4(0x00,   0x99,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[0].m_009900ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x99,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[0].m_009900ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x9A,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[0].m_009A00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0x9A,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[0].m_009A00ZZ), fn00000000, NULL},
    不支持数据【B相关联电能】
    {{REV4(0x00,   0xA8,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee00ZZZZ00   .m_0094_9A00ZZ[1].m_009400ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xA8,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[1].m_009400ZZ), fn00000000, NULL},
    
#if defined(M_SMART)
    【B相 正向有功基波电能 反向有功基波电能 正向有功谐波电能 反向有功谐波电能】
    {{REV4(0x00,   0xA9,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[1].m_009500ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xA9,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[1].m_009500ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xAA,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[1].m_009600ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xAA,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[1].m_009600ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xAB,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[1].m_009700ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xAB,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[1].m_009700ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xAC,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[1].m_009800ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xAC,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[1].m_009800ZZ), fn00000000, NULL},
#endif
    {{REV4(0x00,   0xAD,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[1].m_009900ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xAD,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[1].m_009900ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xAE,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[1].m_009A00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xAE,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[1].m_009A00ZZ), fn00000000, NULL},
    不支持数据【C相关联电能】
    {{REV4(0x00,   0xBC,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee00ZZZZ00   .m_0094_9A00ZZ[2].m_009400ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xBC,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[2].m_009400ZZ), fn00000000, NULL},
    
#if defined(M_SMART)
    【C相 正向有功基波电能 反向有功基波电能 正向有功谐波电能 反向有功谐波电能】*
    {{REV4(0x00,   0xBD,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[2].m_009500ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xBD,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[2].m_009500ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xBE,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[2].m_009600ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xBE,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[2].m_009600ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xBF,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[2].m_009700ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xBF,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[2].m_009700ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xC0,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[2].m_009800ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xC0,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[2].m_009800ZZ), fn00000000, NULL},
#endif
    {{REV4(0x00,   0xC1,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[2].m_009900ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xC1,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[2].m_009900ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xC2,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr00ZZZZ00   .m_0094_9A00ZZ[2].m_009A00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xC2,         0x00,   BI00000001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00ZZZZ01[0].m_0094_9A00ZZ[2].m_009A00ZZ), fn00000000, NULL},
    {{REV4(0x00,   0xFE,         0x00,   BI00FE0001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00FEZZ01[0].m_00FE0001), NULL       , &ds00FE0001},
    {{REV4(0x00,   0xFE,         0xFE,   BI00FE0001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee00FEZZ01[0].m_00FEFE01), NULL       , NULL},
*/
/*
    {{REV4(0x01,   0x01,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr01ZZZZ00   .m_010100ZZ   ), fn01010000, &ds01010000},
    {{REV4(0x01,   0x01,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_010100ZZ   ), fn01010000, &ds01010001},
    {{REV4(0x01,   0x01,     DI01010100,       0x00)}, 0x2000, SIZE_ADDR_OF(FR_sect4, fr01ZZZZ00   .m_010101ZZ[0]), fn01010000, &ds01010100},
    {{REV4(0x01,   0x01,     DI01010100, BI01010001)}, 0x3000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_010101ZZ[0]), fn01010000, &ds01010101},
    {{REV4(0x01,   0x02,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(FR_sect4, fr01ZZZZ00   .m_010200ZZ   ), fn01010000, &ds01020000},
    {{REV4(0x01,   0x02,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_010200ZZ   ), fn01010000, &ds01020001},
    {{REV4(0x01,   0x02,     DI01010100,       0x00)}, 0x2000, SIZE_ADDR_OF(FR_sect4, fr01ZZZZ00   .m_010201ZZ[0]), fn01010000, &ds01020100},
    {{REV4(0x01,   0x02,     DI01010100, BI01010001)}, 0x3000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_010201ZZ[0]), fn01010000, &ds01020101},
    {{REV4(0x01, CI01030000,     0x00,         0x00)}, 0x4000, SIZE_ADDR_OF(FR_sect4, fr01ZZZZ00   .m_0103ZZZZ[0].m_01ZZ00ZZ   ), fn01010000, &ds01030000},
    {{REV4(0x01, CI01030000,     0x00,   BI01010001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0103ZZZZ[0].m_01ZZ00ZZ   ), fn01010000, &ds01030001},
    {{REV4(0x01, CI01030000, DI01010100,       0x00)}, 0x6000, SIZE_ADDR_OF(FR_sect4, fr01ZZZZ00   .m_0103ZZZZ[0].m_01ZZ01ZZ[0]), fn01010000, &ds01030100},
    {{REV4(0x01, CI01030000, DI01010100, BI01010001)}, 0x7000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0103ZZZZ[0].m_01ZZ01ZZ[0]), fn01010000, &ds01030101},
    {{REV4(0x01, CI01050000,     0x00,         0x00)}, 0x4000, SIZE_ADDR_OF(FR_sect4, fr01ZZZZ00   .m_0105ZZZZ[0].m_01ZZ00ZZ   ), fn01010000, &ds01050000},
    {{REV4(0x01, CI01050000,     0x00,   BI01010001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0105ZZZZ[0].m_01ZZ00ZZ   ), fn01010000, &ds01050001},
    {{REV4(0x01, CI01050000, DI01010100,       0x00)}, 0x6000, SIZE_ADDR_OF(FR_sect4, fr01ZZZZ00   .m_0105ZZZZ[0].m_01ZZ01ZZ[0]), fn01010000, &ds01050100},
    {{REV4(0x01, CI01050000, DI01010100, BI01010001)}, 0x7000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0105ZZZZ[0].m_01ZZ01ZZ[0]), fn01010000, &ds01050101},
    不支持数据
    {{REV4(0x01,   0x09,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_010900ZZ   ), fn01010000, NULL},
    {{REV4(0x01,   0x09,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_010900ZZ   ), fn01010000, NULL},
    {{REV4(0x01,   0x09,     DI01010100,       0x00)}, 0x2000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_010901ZZ[0]), fn01010000, NULL},
    {{REV4(0x01,   0x09,     DI01010100, BI01010001)}, 0x3000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_010901ZZ[0]), fn01010000, NULL},
    {{REV4(0x01,   0x0A,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_010A00ZZ   ), fn01010000, NULL},
    {{REV4(0x01,   0x0A,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_010A00ZZ   ), fn01010000, NULL},
    {{REV4(0x01,   0x0A,     DI01010100,       0x00)}, 0x2000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_010A01ZZ[0]), fn01010000, NULL},
    {{REV4(0x01,   0x0A,     DI01010100, BI01010001)}, 0x3000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_010A01ZZ[0]), fn01010000, NULL},
    {{REV4(0x01,   0x15,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[0].m_011500ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x15,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[0].m_011500ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x16,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[0].m_011600ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x16,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[0].m_011600ZZ), fn01010000, NULL},
    {{REV4(0x01, CI01170000,     0x00,         0x00)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[0].m_011700ZZ[0]), fn01010000, NULL},
    {{REV4(0x01, CI01170000,     0x00,   BI01010001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[0].m_011700ZZ[0]), fn01010000, NULL},
    {{REV4(0x01, CI01190000,     0x00,         0x00)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[0].m_011900ZZ[0]), fn01010000, NULL},
    {{REV4(0x01, CI01190000,     0x00,   BI01010001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[0].m_011900ZZ[0]), fn01010000, NULL},
    {{REV4(0x01,   0x1D,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[0].m_011D00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x1D,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[0].m_011D00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x1E,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[0].m_011E00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x1E,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[0].m_011E00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x29,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[1].m_011500ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x29,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[1].m_011500ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x2A,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[1].m_011600ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x2A,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[1].m_011600ZZ), fn01010000, NULL},
    {{REV4(0x01, CI012B0000,     0x00,         0x00)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[1].m_011700ZZ[0]), fn01010000, NULL},
    {{REV4(0x01, CI012B0000,     0x00,   BI01010001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[1].m_011700ZZ[0]), fn01010000, NULL},
    {{REV4(0x01, CI012D0000,     0x00,         0x00)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[1].m_011900ZZ[0]), fn01010000, NULL},
    {{REV4(0x01, CI012D0000,     0x00,   BI01010001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[1].m_011900ZZ[0]), fn01010000, NULL},
    {{REV4(0x01,   0x31,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[1].m_011D00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x31,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[1].m_011D00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x32,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[1].m_011E00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x32,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[1].m_011E00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x3D,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[2].m_011500ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x3D,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[2].m_011500ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x3E,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[2].m_011600ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x3E,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[2].m_011600ZZ), fn01010000, NULL},
    {{REV4(0x01, CI013F0000,     0x00,         0x00)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[2].m_011700ZZ[0]), fn01010000, NULL},
    {{REV4(0x01, CI013F0000,     0x00,   BI01010001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[2].m_011700ZZ[0]), fn01010000, NULL},
    {{REV4(0x01, CI01410000,     0x00,         0x00)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[2].m_011900ZZ[0]), fn01010000, NULL},
    {{REV4(0x01, CI01410000,     0x00,   BI01010001)}, 0x5000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[2].m_011900ZZ[0]), fn01010000, NULL},
    {{REV4(0x01,   0x45,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[2].m_011D00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x45,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[2].m_011D00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x46,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee01ZZZZ00   .m_0115_1E00ZZ[2].m_011E00ZZ), fn01010000, NULL},
    {{REV4(0x01,   0x46,         0x00,   BI01010001)}, 0x1000, SIZE_ADDR_OF(EE_sect3, ee01ZZZZ01[0].m_0115_1E00ZZ[2].m_011E00ZZ), fn01010000, NULL},
*/
    {{REV4(0x02,   0x01,     CI02010100,       0x00)}, 0x2000, sizeof(ra02010100[0]), (uint32_t)ra02010100[0] , fn02010100, &ds02010100},
    {{REV4(0x02,   0x02,     CI02020100,       0x00)}, 0x2000, sizeof(ra02020100[0]), (uint32_t)ra02020100[0] , fn02020100_rev, &ds02020100},
    {{REV4(0x02,   0x03,         0x00,         0x00)}, 0x0000, sizeof(ra02030000)   , (uint32_t)&ra02030000[0], fn02030000, &ds02030000},
    {{REV4(0x02,   0x03,     CI02030100,       0x00)}, 0x2000, sizeof(ra02030100[0]), (uint32_t)ra02030100[0] , fn02030000, &ds02030100},
    //{{REV4(0x02,   0x04,         0x00,         0x00)}, 0x0000, sizeof(ra02040000)   , (uint32_t)&ra02040000[0], fn02030000, &ds02040000},
    //{{REV4(0x02,   0x04,     CI02040100,       0x00)}, 0x2000, sizeof(ra02040100[0]), (uint32_t)ra02040100[0] , fn02030000, &ds02040100},
    //{{REV4(0x02,   0x05,         0x00,         0x00)}, 0x0000, sizeof(ra02050000)   , (uint32_t)&ra02050000[0], fn02030000, &ds02050000},
    //{{REV4(0x02,   0x05,     CI02050100,       0x00)}, 0x2000, sizeof(ra02050100[0]), (uint32_t)ra02050100[0] , fn02030000, &ds02050100},
    {{REV4(0x02,   0x06,         0x00,         0x00)}, 0x0000, sizeof(ra02060000)   , (uint32_t)&ra02060000[0], fn02060000, &ds02060000},
    {{REV4(0x02,   0x06,     CI02060100,       0x00)}, 0x2000, sizeof(ra02060100[0]), (uint32_t)ra02060100[0] , fn02060000, &ds02060100},
    {{REV4(0x02,   0x07,     CI02070100,       0x00)}, 0x2000, sizeof(ra02070100[0]), (uint32_t)ra02070100[0] , fn02070100, &ds02070100},
#if defined(M_SMART)
    /*【电压电流失真度、谐波含量】*/
    {{REV4(0x02,   0x08,     CI02080100,       0x00)}, 0x2000, sizeof(ra02080100[0]), (uint32_t)ra02080100[0] , NULL, NULL},
    {{REV4(0x02,   0x09,     CI02090100,       0x00)}, 0x2000, sizeof(ra02090100[0]), (uint32_t)ra02090100[0] , NULL, NULL},
    {{REV4(0x02,   0x0A,     CI020A0101, DI020A0101)}, 0x3000, sizeof(ra020A0101[0][0]), (uint32_t)&ra020A0101[0][1][0], NULL, NULL},
    {{REV4(0x02,   0x0B,     CI020A0101, DI020A0101)}, 0x3000, sizeof(ra020B0101[0][0]), (uint32_t)&ra020B0101[0][1][0], NULL, NULL},
#endif
    //{{REV4(0x02,   0x80,         0x00,         0x01)}, 0x0000, sizeof(ra02800001), (uint32_t)&ra02800001[0], fn02800001, &ds02800001},
    {{REV4(0x02,   0x80,         0x00,         0x02)}, 0x0000, sizeof(ra02800002), (uint32_t)&ra02800002[0], fn02800002, &ds02800002},
    {{REV4(0x02,   0x80,         0x00,         0x03)}, 0x0000, sizeof(ra02800003), (uint32_t)&ra02800003[0], fn01010000, &ds02800003},
//    {{REV4(0x02,   0x80,         0x00,         0x04)}, 0x0000, sizeof(ra02800004), (uint32_t)&ra02800004[0], fn01010000, &ds02800004},
//    {{REV4(0x02,   0x80,         0x00,         0x05)}, 0x0000, sizeof(ra02800005), (uint32_t)&ra02800005[0], fn01010000, &ds02800005},
    //{{REV4(0x02,   0x80,         0x00,         0x06)}, 0x0000, sizeof(ra02800006), (uint32_t)&ra02800006[0], fn01010000, &ds02800006},
    {{REV4(0x02,   0x80,         0x00,         0x07)}, 0x0000, sizeof(ra02800007), (uint32_t)&ra02800007[0], fn02800007, &ds02800007},
    {{REV4(0x02,   0x80,         0x00,         0x08)}, 0x0000, sizeof(ra02800008), (uint32_t)&ra02800008[0], fn02800008, &ds02800008},
//    {{REV4(0x02,   0x80,         0x00,         0x09)}, 0x0000, sizeof(ra02800009), (uint32_t)&ra02800009[0], fn02800009, &ds02800009},
    {{REV4(0x02,   0x80,         0x00,         0x0A)}, 0x0000, SIZE_ADDR_OF(FR_sect3, fr0280000A      ), fn0280000A, &ds0280000A},
#if defined(M_LOCAL)
    /* 【当前阶梯电价】 */
    {{REV4(0x02,   0x80,         0x00,         0x0B)}, 0x0000, sizeof(ra0280000B), (uint32_t)&ra0280000B[0], fn0280000B, &ds0280000B},
    /* 【当前电价】 */
    {{REV4(0x02,   0x80,         0x00,         0x20)}, 0x0000, sizeof(ra02800020), (uint32_t)&ra02800020[0], fn0280000B, &ds02800020},
    /* 【当前费率电价】 */
    {{REV4(0x02,   0x80,         0x00,         0x21)}, 0x0000, sizeof(ra02800021), (uint32_t)&ra02800021[0], fn0280000B, NULL}, 
#endif
    {{REV4(0x02,   0x80,         0x00,         0x22)}, 0x0000, sizeof(ra02800022), (uint32_t)&ra02800022[0], NULL, NULL},
    {{REV4(0x02,   0x80,         0x00,         0x23)}, 0x0000, sizeof(ra02800023), (uint32_t)&ra02800023[0], NULL, NULL},
//    {{REV4(0x02,   0x80,         0x00,         0x24)}, 0x0000, SIZE_ADDR_OF(FR_sect3, fr02800024      ),     NULL, NULL},

    {{REV4(0x02,   0x80,         0x00,         0xFC)}, 0x0000, sizeof(ra028000FC), (uint32_t)&ra028000FC, NULL, NULL},
//    {{REV4(0x02,   0x80,     CI02800100,       0x00)}, 0x2000, sizeof(ra02800100[0]), (uint32_t)ra02800100[0] , NULL, NULL},
/*
    {{REV4(0x03,   0x05,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee03050000      ), fn03050000, &ds03050000},
    {{REV4(0x03,   0x05,         0x00,   BI03050001)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03050001[0]   ), fn03050001, &ds03050001},
#if defined(M_SMART)
    【辅助电源事件记录】
    {{REV4(0x03,   0x06,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee03060000      ), NULL, NULL},
    {{REV4(0x03,   0x06,         0x00,   BI03060001)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03060001[0]   ), NULL, NULL},
#endif
    {{REV4(0x03,   0x10,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee03100000      ), fn03100000, NULL},
    {{REV4(0x03,   0x10,         0x00,   BI03100001)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03100001[0]   ), fn03100000, NULL},
    {{REV4(0x03,   0x10,         0x01,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee03100100[0]   ), fn03100000, NULL},
    {{REV4(0x03,   0x10,         0x01,   BI03100101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03100101[0][0]), fn03100000, NULL},
    {{REV4(0x03,   0x10,         0x02,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee03100100[1]   ), fn03100000, NULL},
    {{REV4(0x03,   0x10,         0x02,   BI03100201)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03100101[1][0]), fn03100000, NULL},
    {{REV4(0x03,   0x10,         0x03,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee03100100[2]   ), fn03100000, NULL},
    {{REV4(0x03,   0x10,         0x03,   BI03100301)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03100101[2][0]), fn03100000, NULL},
*/
    {{REV4(0x03,   0x11,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03110000      ), fn03110000, &ds03110000},
    {{REV4(0x03,   0x11,         0x00,   BI03110001)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03110001[0]   ), NULL, &ds03110001},
/*
    {{REV4(0x03,   0x12,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03120000      ), NULL, NULL},
    {{REV4(0x03,   0x12,         0x01,   BI03120101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03120101[0]   ), NULL, NULL},
    {{REV4(0x03,   0x12,         0x02,   BI03120201)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03120201[0]   ), NULL, NULL},
    {{REV4(0x03,   0x12,         0x03,   BI03120301)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03120301[0][0]), NULL, NULL},
    {{REV4(0x03,   0x12,         0x04,   BI03120401)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03120301[1][0]), NULL, NULL},
    {{REV4(0x03,   0x12,         0x05,   BI03120501)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03120301[2][0]), NULL, NULL},
    {{REV4(0x03,   0x12,         0x06,   BI03120601)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03120301[3][0]), NULL, NULL},
*/
    {{REV4(0x03,   0x30,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300000      ), fn03110000, &ds03300000},
    {{REV4(0x03,   0x30,         0x00,   BI03300001)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300001[0]   ), NULL, &ds03300001},
    {{REV4(0x03,   0x30,         0x01,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300100      ), fn03110000, &ds03300100},
    {{REV4(0x03,   0x30,         0x01,   BI03300101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300101[0]   ), fn03300101, &ds03300101},
//    {{REV4(0x03,   0x30,         0x02,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300200      ), fn03110000, &ds03300200},
//    {{REV4(0x03,   0x30,         0x02,   BI03300201)}, 0x1000, SIZE_ADDR_OF(EE_sect4, df03300201[0] ), NULL, &ds03300201},
    {{REV4(0x03,   0x30,         0x03,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300300      ), fn03110000, &ds03300300},
    {{REV4(0x03,   0x30,         0x03,   BI03300301)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300301[0]   ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x04,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300400      ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x04,   BI03300401)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300401[0]   ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x05,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300500      ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x05,   BI03300501)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300501[0] ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x06,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300600      ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x06,   BI03300601)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300601[0] ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x07,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300700      ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x07,   BI03300701)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300701[0]   ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x08,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300800      ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x08,   BI03300801)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300801[0] ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x09,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300900      ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x09,   BI03300901)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300901[0]   ), NULL, NULL},
//    {{REV4(0x03,   0x30,         0x0A,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300A00      ), NULL, NULL},
//    {{REV4(0x03,   0x30,         0x0A,   BI03300A01)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300A01[0]   ), NULL, NULL},
//    {{REV4(0x03,   0x30,         0x0B,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300B00      ), NULL, NULL},
//    {{REV4(0x03,   0x30,         0x0B,   BI03300B01)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300B01[0]   ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x0C,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300C00      ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x0C,   BI03300C01)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300C01[0]   ), NULL, NULL},
    {{REV4(0x03,   0x30,         0x0D,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300D00      ), fn03110000, &ds03300D00},
    {{REV4(0x03,   0x30,         0x0D,   BI03300D01)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300D01[0]   ), fn03300D01, NULL},
    {{REV4(0x03,   0x30,         0x0E,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300E00      ), fn03110000, &ds03300E00},
    {{REV4(0x03,   0x30,         0x0E,   BI03300E01)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300E01[0]   ), fn03300D01, NULL},
#if defined(M_LOCAL)
    {{REV4(0x03,   0x30,         0x0F,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03300F00      ), fn03110000, NULL},
    {{REV4(0x03,   0x30,         0x0F,   BI03300F01)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03300F01[0] ), fn03300F01, NULL},
    {{REV4(0x03,   0x30,         0x10,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03301000      ), fn03110000, NULL},
    {{REV4(0x03,   0x30,         0x10,   BI03301001)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03301001[0] ), NULL, NULL},
#endif
    {{REV4(0x03,   0x30,         0x12,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03301200      ), fn03110000, NULL},
    {{REV4(0x03,   0x30,         0x12,   BI03301201)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03301201[0]   ), NULL, NULL},
#if defined(M_LOCAL)
    /* 【异常插卡记录】 */
    {{REV4(0x03,   0x30,         0x13,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03301300      ), fn03110000, NULL},
    {{REV4(0x03,   0x30,         0x13,   BI03301301)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03301301[0]   ), NULL, NULL},
    /* 【非法插卡总次数】 */
    {{REV4(0x03,   0x30,         0x14,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect6, ee03301400      ), fn03110000, NULL},        
    /* 【电费型购电记录】 */
    {{REV4(0x03,   0x33,         0x01,   BI03330101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03330101[0].m_03330101), NULL, &ds03330101},
    {{REV4(0x03,   0x33,         0x02,   BI03330101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03330101[0].m_03330201), fn03330201, &ds03330201},
    {{REV4(0x03,   0x33,         0x03,   BI03330101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03330101[0].m_03330301), fn03330301, &ds03330301},
    {{REV4(0x03,   0x33,         0x04,   BI03330101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03330101[0].m_03330401), fn03330301, &ds03330401},
    {{REV4(0x03,   0x33,         0x05,   BI03330101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03330101[0].m_03330501), fn03330301, &ds03330501},
    {{REV4(0x03,   0x33,         0x06,   BI03330101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03330101[0].m_03330601), fn03330301, &ds03330601},
    /* 【退费记录】 */
    {{REV4(0x03,   0x34,         0x00,   BI03340001)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03340001[0]), NULL, NULL},
#endif
    /* 【恒定磁场干扰记录】 */
    {{REV4(0x03,   0x35,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03350000), NULL, NULL},
    {{REV4(0x03,   0x35,         0x00,   BI03350001)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03350001[0]), NULL, NULL},
#if ((defined(M_LOCAL) || defined(M_REMOTE)) && defined(RELAY_BUILT_IN))
    /* 【负荷开关误动记录】 */
    {{REV4(0x03,   0x36,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03360000), NULL, NULL},
    {{REV4(0x03,   0x36,         0x00,   BI03360101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03360001[0]), NULL, NULL},
#endif        
    /* 【电源异常记录】 */
    {{REV4(0x03,   0x37,         0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03370000), NULL, NULL},
    {{REV4(0x03,   0x37,         0x00,   BI03370101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03370001[0]), NULL, NULL},

//    {{REV4(0x03,   0x80,         0x01,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee03800100), NULL, NULL},
//    {{REV4(0x03,   0x80,         0x01,   BI03800101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee03800101[0]), NULL, NULL},

    
    {{REV4(0x04,   0x00,         0x01,         0x01)}, 0x0014, sizeof(ra04000101), (uint32_t)0,    fn04000101, &ds04000101_3},
    {{REV4(0x04,   0x00,         0x01,         0x02)}, 0x0014, sizeof(ra04000102), (uint32_t)0,    fn04000102, &ds04000102_1},
//    {{REV4(0x04,   0x00,         0x01,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000103), fn04000103, &ds04000103},
//    {{REV4(0x04,   0x00,         0x01,         0x04)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000104), fn04000104, &ds04000104},
    {{REV4(0x04,   0x00,         0x01,         0x05)}, 0x0000, sizeof(ro04000105), (uint32_t)&ro04000105[0], fn04000105, NULL},
    {{REV4(0x04,   0x00,         0x01,         0x06)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000106), fn04000106, &ds04000106},
    {{REV4(0x04,   0x00,         0x01,         0x07)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000107), fn04000106, &ds04000107},
#if defined(M_LOCAL)
    /* 【两套费率切换时间】【两套阶梯切换时间】  */
    {{REV4(0x04,   0x00,         0x01,         0x08)}, 0x0057, SIZE_ADDR_OF(EE_sect2, ee04000108), fn04000108, &ds04000108},
    {{REV4(0x04,   0x00,         0x01,         0x09)}, 0x0057, SIZE_ADDR_OF(EE_sect2, ee04000109), fn04000109, &ds04000109},
#endif
    {{REV4(0x04,   0x00,         0x01,         0x0C)}, 0x0014, 0x07                 , (uint32_t)0, fn0400010C, NULL},        
#if defined(M_LOCAL)|| defined(M_REMOTE)
    {{REV4(0x04,   0x00,         0x01,         0xFC)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee040001FC), fn040001FC, NULL},
    {{REV4(0x04,   0x00,         0x01,         0xFE)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee040001FE), fn040001FE, &ds040001FE},
#endif
    {{REV4(0x04,   0x00,         0x02,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000201), fn04000201, &ds04000201},
    {{REV4(0x04,   0x00,         0x02,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000202), fn04000202, &ds04000202},
    {{REV4(0x04,   0x00,         0x02,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000203), fn04000203, &ds04000203},
    {{REV4(0x04,   0x00,         0x02,         0x04)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000204), fn04000204, &ds04000204},
    {{REV4(0x04,   0x00,         0x02,         0x05)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000205), fn04000205, &ds04000205},
#if defined(M_SMART)
    /* 【谐波分析次数】 */
    {{REV4(0x04,   0x00,         0x02,         0x06)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000206), fn04000206, &ds04000206},
#endif
#if defined(M_LOCAL)
    {{REV4(0x04,   0x00,         0x02,         0x07)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000207), fn04000207, &ds04000207},
#endif        
    {{REV4(0x04,   0x00,         0x02,         0x08)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04000208), fn04000208, NULL},        
    {{REV4(0x04,   0x00,         0x02,         0xFE)}, 0x0424, sizeof(ra_timeCheckoutMAC), (uint32_t)&ra_timeCheckoutMAC, NULL, NULL},
    {{REV4(0x04,   0x00,         0x03,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000301), fn04000301, &ds04000301},
    {{REV4(0x04,   0x00,         0x03,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000302), fn04000302, &ds04000302},
    {{REV4(0x04,   0x00,         0x03,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000303), fn04000303, &ds04000303},
    {{REV4(0x04,   0x00,         0x03,         0x04)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000304), fn04000304, &ds04000304},
    {{REV4(0x04,   0x00,         0x03,         0x05)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000305), fn04000305, &ds04000305},
    {{REV4(0x04,   0x00,         0x03,         0x06)}, 0x0057, SIZE_ADDR_OF(EE_sect2, ee04000306), fn04000306, &ds04000306},
    {{REV4(0x04,   0x00,         0x03,         0x07)}, 0x0057, SIZE_ADDR_OF(EE_sect2, ee04000307), fn04000306, &ds04000307},
    {{REV4(0x04,   0x00,         0x03,         0x08)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000308), fn04000308, NULL},
    {{REV4(0x04,   0x00,         0x03,         0xEA)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee040003EA), fn040003EA, NULL},
    {{REV4(0x04,   0x00,         0x03,         0xFA)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee040003FA), fn040003FA, NULL},
    {{REV4(0x04,   0x00,         0x03,         0xFB)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee040003FB), fn040003FB, NULL},
    {{REV4(0x04,   0x00,         0x03,         0xFC)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee040003FC), fn040003FC, NULL},
    {{REV4(0x04,   0x00,         0x03,         0xFE)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee040003FE), fn040003FE, NULL},

    {{REV4(0x04,   0x00,         0x04,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000401), fn04000401, &ds04000401},
    {{REV4(0x04,   0x00,         0x04,         0x02)}, 0x0057, SIZE_ADDR_OF(EE_sect2, ee04000402), fn04000402, &ds04000402},
    {{REV4(0x04,   0x00,         0x04,         0x03)}, 0x0854, SIZE_ADDR_OF(EE_sect2, ee04000403), fn04000403, NULL},
    {{REV4(0x04,   0x00,         0x04,         0x04)}, 0x0860, SIZE_ADDR_OF(EE_sect2, ee04000404), fn04000404, NULL},
    {{REV4(0x04,   0x00,         0x04,         0x05)}, 0x0860, SIZE_ADDR_OF(EE_sect2, ee04000405), fn04000405, NULL},
    {{REV4(0x04,   0x00,         0x04,         0x06)}, 0x0860, SIZE_ADDR_OF(EE_sect2, ee04000406), fn04000406, NULL},
    {{REV4(0x04,   0x00,         0x04,         0x07)}, 0x0860, SIZE_ADDR_OF(EE_sect2, ee04000407), fn04000407, NULL},
//    {{REV4(0x04,   0x00,         0x04,         0x08)}, 0x0860, SIZE_ADDR_OF(EE_sect2, ee04000408), fn04000408, NULL},
    {{REV4(0x04,   0x00,         0x04,         0x09)}, 0x0060, SIZE_ADDR_OF(EE_sect2, ee04000409), fn04000409, &ds04000409},
//    {{REV4(0x04,   0x00,         0x04,         0x0A)}, 0x0060, SIZE_ADDR_OF(EE_sect2, ee0400040A), fn0400040A, &ds0400040A},
    {{REV4(0x04,   0x00,         0x04,         0x0B)}, 0x0860, SIZE_ADDR_OF(EE_sect2, ee0400040B), fn0400040B, NULL},
    {{REV4(0x04,   0x00,         0x04,         0x0C)}, 0x0860, SIZE_ADDR_OF(EE_sect2, ee0400040C), fn0400040C, NULL},
    {{REV4(0x04,   0x00,         0x04,         0x0D)}, 0x0800, sizeof(ro0400040D), (uint32_t)&ro0400040D[0], NULL, NULL},
    {{REV4(0x04,   0x00,         0x04,         0x0E)}, 0x0057, SIZE_ADDR_OF(EE_sect2, ee0400040E), fn0400040E, &ds0400040E},
    {{REV4(0x04,   0x00,         0x04,         0x0F)}, 0x041C, SIZE_ADDR_OF(EE_sect2, ee0400040F), fn0400040F, NULL},
    {{REV4(0x04,   0x00,         0x05,   CI04000501)}, 0x1400, sizeof(ra04000501[0]), (uint32_t)&ra04000501[0], fn04000501, &ds04000501},
    {{REV4(0x04,   0x00,         0x05,         0x08)}, 0x0400, SIZE_ADDR_OF(EE_sect7, ee04000508), NULL,       NULL},        
    {{REV4(0x04,   0x00,         0x06,         0x01)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04000601   ), fn04000601, &ds04000601},
//    {{REV4(0x04,   0x00,         0x06,   CI04000602)}, 0x1454, SIZE_ADDR_OF(EE_sect2, ee04000602[0]), fn04000602, &ds04000602},
    {{REV4(0x04,   0x00,         0x07,         0x01)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04000701), fn04000701, &ds04000701},
/*不支持数据
    {{REV4(0x04,   0x00,         0x07,         0x02)}, 0x0414, sizeof(ra04000702), (uint32_t)&ra04000702, fn04000702, &ds04000702},
*/
    {{REV4(0x04,   0x00,         0x07,   CI04000703)}, 0x1454, SIZE_ADDR_OF(EE_sect2, ee04000703[0]), fn04000703, &ds04000703},
    {{REV4(0x04,   0x00,         0x08,         0x01)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04000801   ), fn04000801, NULL},
    {{REV4(0x04,   0x00,         0x08,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000802   ), fn04000802, NULL},
    {{REV4(0x04,   0x00,         0x09,         0x01)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04000901   ), fn04000901, &ds04000901},
    {{REV4(0x04,   0x00,         0x09,         0x02)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04000902   ), fn04000902, &ds04000902},
    {{REV4(0x04,   0x00,         0x09,         0x03)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04000903   ), fn04000903, &ds04000903},
    {{REV4(0x04,   0x00,         0x09,         0x04)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04000904   ), fn04000904, &ds04000904},
    {{REV4(0x04,   0x00,         0x09,         0x05)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04000905   ), fn04000905, &ds04000905},
    {{REV4(0x04,   0x00,         0x09,         0x06)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04000906   ), fn04000906, &ds04000906},
    {{REV4(0x04,   0x00,         0x0A,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000A01   ), fn04000A01, NULL},
    {{REV4(0x04,   0x00,         0x0A,   CI04000A02)}, 0x1054, SIZE_ADDR_OF(EE_sect2, ee04000A02[0]), fn04000A02, NULL},
    {{REV4(0x04,   0x00,         0x0B,   CI04000B01)}, 0x1054, SIZE_ADDR_OF(EE_sect2, ee04000B01[0]), fn04000B01, &ds04000B01},
    {{REV4(0x04,   0x00,         0x0C,         0x01)}, 0x00F0, SIZE_ADDR_OF(EE_sect2, ee04000C01[0]), fn04000C01, NULL},
    {{REV4(0x04,   0x00,         0x0C,         0x02)}, 0x00F1, SIZE_ADDR_OF(EE_sect2, ee04000C01[1]), fn04000C01, NULL},
    {{REV4(0x04,   0x00,         0x0C,         0x03)}, 0x00F2, SIZE_ADDR_OF(EE_sect2, ee04000C01[2]), fn04000C01, NULL},
    {{REV4(0x04,   0x00,         0x0C,         0x04)}, 0x00F3, SIZE_ADDR_OF(EE_sect2, ee04000C01[3]), fn04000C01, NULL},
    {{REV4(0x04,   0x00,         0x0C,         0x05)}, 0x00F4, SIZE_ADDR_OF(EE_sect2, ee04000C01[4]), fn04000C01, NULL},
    {{REV4(0x04,   0x00,         0x0C,         0x06)}, 0x00F5, SIZE_ADDR_OF(EE_sect2, ee04000C01[5]), fn04000C01, NULL},
//    {{REV4(0x04,   0x00,         0x0C,         0x07)}, 0x00F6, SIZE_ADDR_OF(EE_sect2, ee04000C01[6]), fn04000C01, NULL},
//    {{REV4(0x04,   0x00,         0x0C,         0x08)}, 0x00F7, SIZE_ADDR_OF(EE_sect2, ee04000C01[7]), fn04000C01, NULL},
//    {{REV4(0x04,   0x00,         0x0C,         0x09)}, 0x00F8, SIZE_ADDR_OF(EE_sect2, ee04000C01[8]), fn04000C01, NULL},
//    {{REV4(0x04,   0x00,         0x0C,         0x0A)}, 0x00F9, SIZE_ADDR_OF(EE_sect2, ee04000C01[9]), fn04000C01, NULL},
    {{REV4(0x04,   0x00,         0x0C,         0xFE)}, 0x0012, sizeof(ra04000CFE), (uint32_t)&ra04000CFE, NULL, NULL},
//    {{REV4(0x04,   0x00,         0x0D,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[0].ee04000D01), fn04000D01, NULL},
    //{{REV4(0x04,   0x00,         0x0D,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[0].ee04000D02), fn04000D02, NULL},
//    {{REV4(0x04,   0x00,         0x0D,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[0].ee04000D03), fn04000D03, NULL},
    //{{REV4(0x04,   0x00,         0x0D,         0x04)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[0].ee04000D04), fn04000D04, NULL},
//    {{REV4(0x04,   0x00,         0x0D,         0x05)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[1].ee04000D01), fn04000D01, NULL},
    //{{REV4(0x04,   0x00,         0x0D,         0x06)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[1].ee04000D02), fn04000D02, NULL},
//    {{REV4(0x04,   0x00,         0x0D,         0x07)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[1].ee04000D03), fn04000D03, NULL},
    //{{REV4(0x04,   0x00,         0x0D,         0x08)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[1].ee04000D04), fn04000D04, NULL},
//    {{REV4(0x04,   0x00,         0x0D,         0x09)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[2].ee04000D01), fn04000D01, NULL},
    //{{REV4(0x04,   0x00,         0x0D,         0x0A)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[2].ee04000D02), fn04000D02, NULL},
//    {{REV4(0x04,   0x00,         0x0D,         0x0B)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[2].ee04000D03), fn04000D03, NULL},
    //{{REV4(0x04,   0x00,         0x0D,         0x0C)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000D01_04[2].ee04000D04), fn04000D04, NULL},
//    {{REV4(0x04,   0x00,         0x0E,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000E01), fn04000E01, NULL},
//    {{REV4(0x04,   0x00,         0x0E,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000E02), fn04000E02, NULL},
//    {{REV4(0x04,   0x00,         0x0E,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000E03), fn04000E03, NULL},
//    {{REV4(0x04,   0x00,         0x0E,         0x04)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04000E04), fn04000E04, NULL},
        
#if defined(M_LOCAL)
    /* 【报警金额1，2限值、透支金额限值、囤积金额限值、合闸允许金额限值】 */
    {{REV4(0x04,   0x00,         0x10,         0x01)}, 0x0057, SIZE_ADDR_OF(EE_sect2, ee04001001), fn04001001, &ds04001001},
    {{REV4(0x04,   0x00,         0x10,         0x02)}, 0x0057, SIZE_ADDR_OF(EE_sect2, ee04001002), fn04001001, &ds04001002},
    {{REV4(0x04,   0x00,         0x10,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04001003), fn04001001, &ds04001003},
    {{REV4(0x04,   0x00,         0x10,         0x04)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04001004), fn04001001, &ds04001004},
    {{REV4(0x04,   0x00,         0x10,         0x05)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04001005), fn04001001, &ds04001005},
    {{REV4(0x04,   0x00,         0x10,         0x06)}, 0x0094, 4,                  (uint32_t)0,    fn04001006, NULL},        
#endif

    {{REV4(0x04,   0x00,         0x11,         0x01)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04001101), fn04001101, &ds04001101},
    {{REV4(0x04,   0x00,         0x11,         0x04)}, 0x0454, SIZE_ADDR_OF(EE_sect2, ee04001104), fn04001104, NULL},
    {{REV4(0x04,   0x00,         0x12,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04001201), fn04001201, NULL},
    {{REV4(0x04,   0x00,         0x12,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04001202), fn04001202, NULL},
    {{REV4(0x04,   0x00,         0x12,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04001203), fn04001203, NULL},
    {{REV4(0x04,   0x00,         0x12,         0x04)}, 0x0000, 0x04     , (uint32_t)&fr.fr04001204, NULL     , &ds04001204}, 
    {{REV4(0x04,   0x00,         0x13,         0x01)}, 0x0014, sizeof(ra04001301), (uint32_t)&ra04001301[0], fn04001301, &ds04001301}, 
#if defined(M_REMOTE) || defined(M_LOCAL)
    {{REV4(0x04,   0x00,         0x14,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04001401), fn04001401, &ds04001401},
#endif
    {{REV4(0x04,   0x00,         0x15,         0x01)}, 0x0400, sizeof(ra04001501), (uint32_t)&ra04001501[0], NULL, NULL},
#if defined(M_LOCAL)
    {{REV4(0x04,   0x00,         0x15,         0x02)}, 0x0400, sizeof(ra04001502), (uint32_t)&ra04001502, NULL, NULL},
#endif
    {{REV4(0x04, CI04010000,     0x00,         0x00)}, 0x405C, SIZE_ADDR_OF(EE_sect2, ee040100ZZ[0].ee04ZZ0000   ), fn04010000, &ds04010000},
    {{REV4(0x04, CI04010000,     0x00,   CI04010001)}, 0x505C, SIZE_ADDR_OF(EE_sect2, ee040100ZZ[0].ee04ZZ0001[0]), fn04010001, &ds04010001},
    {{REV4(0x04,   0x03,         0x00,   CI04030001)}, 0x1054, SIZE_ADDR_OF(EE_sect2, ee04030001[0]), fn04030001, NULL},
    {{REV4(0x04,   0x04,         0x01,   CI04040101)}, 0x141C, SIZE_ADDR_OF(EE_sect2, ee04040101[0]), fn04040101, NULL},
    {{REV4(0x04,   0x04,         0x02,   CI04040201)}, 0x141C, SIZE_ADDR_OF(EE_sect2, ee04040201[0]), fn04040201, NULL},
    {{REV4(0x04,   0x04,         0x03,         0x00)}, 0x0000, SIZE_OF(EE_sect2, ee04040101[0]), (uint32_t)0, fn04040300, NULL},

#if defined(M_LOCAL)
    // 当前/备用套 费率数据单条 读
    {{REV4(0x04,   0x05,     CI04050100, CI04050101)}, 0x3000, SIZE_ADDR_OF(EE_sect2,  ee0405ZZFF[0].m_0405ZZMO[0]), fn04050101, &ds04050101}, 
    // 当前套      费率数据块   读
    {{REV4(0x04,   0x05,         0x02,         0xFD)}, 0x000F, 4*TMN, 0, fn0405ZZFF, NULL}, 
    // 备用套      费率数据块   读写
    {{REV4(0x04,   0x05,         0x02,         0xFE)}, 0x001F, 4*TMN, 0, fn0405ZZFF, NULL},
    
    {{REV4(0x04,   0x06,         0x04,   CI0406ZZEN)}, 0x1000, 4, (uint32_t)&ra040604FF.m_0406ZZEN[0], NULL, &ds040604EN},
    {{REV4(0x04,   0x06,         0x04,   CI0406ZZMO)}, 0x1000, 4, (uint32_t)&ra040604FF.m_0406ZZMO[0], NULL, &ds040604MO},
    {{REV4(0x04,   0x06,         0x04,   CI0406ZZYS)}, 0x1000, 3, (uint32_t)&ra040604FF.m_0406ZZYS[0], NULL, &ds040604YS}, 
    // 当前套      阶梯数据块   读
    {{REV4(0x04,   0x06,         0x04,         0xFE)}, 0x000F, SIZE_ADDR_OF(EE_sect2, ee0406ZZFF[0]), fn0406ZZFF, NULL}, 
    // 备用套      阶梯数据块   读写
    {{REV4(0x04,   0x06,         0x05,         0xFE)}, 0x001F, SIZE_ADDR_OF(EE_sect2, ee0406ZZFF[1]), fn0406ZZFF, NULL},        
#endif    
/*
    {{REV4(0x04,   0x09,         0x01,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090101), fn04090101, &ds04090101},
    {{REV4(0x04,   0x09,         0x01,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090102), fn04090102, &ds04090102},
    {{REV4(0x04,   0x09,         0x01,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090103), fn04090103, &ds04090103},
    {{REV4(0x04,   0x09,         0x01,         0x04)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090104), fn04090104, &ds04090104},
    {{REV4(0x04,   0x09,         0x02,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090201), fn04090201, &ds04090201},
    {{REV4(0x04,   0x09,         0x02,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090202), fn04090202, &ds04090202},
    {{REV4(0x04,   0x09,         0x03,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090301), fn04090301, &ds04090301},
    {{REV4(0x04,   0x09,         0x03,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090302), fn04090302, &ds04090302},
    {{REV4(0x04,   0x09,         0x04,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090401), fn04090401, &ds04090401},
    {{REV4(0x04,   0x09,         0x04,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090402), fn04090402, &ds04090402},
    {{REV4(0x04,   0x09,         0x04,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090403), fn04090403, &ds04090403},
    {{REV4(0x04,   0x09,         0x05,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090501), fn04090501, &ds04090501},
    {{REV4(0x04,   0x09,         0x05,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090502), fn04090502, &ds04090502},
    {{REV4(0x04,   0x09,         0x06,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090601), fn04090601, &ds04090601},
    {{REV4(0x04,   0x09,         0x06,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090602), fn04090602, &ds04090602},
    {{REV4(0x04,   0x09,         0x07,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090701), fn04090701, &ds04090701},
    {{REV4(0x04,   0x09,         0x07,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090702), fn04090702, &ds04090702},
    {{REV4(0x04,   0x09,         0x07,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090703), fn04090703, &ds04090703},
    {{REV4(0x04,   0x09,         0x07,         0x04)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090704), fn04090704, &ds04090704},
    {{REV4(0x04,   0x09,         0x08,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090801), fn04090801, &ds04090801},
    {{REV4(0x04,   0x09,         0x08,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090802), fn04090802, &ds04090802},
    {{REV4(0x04,   0x09,         0x09,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090901), fn04090901, &ds04090901},
    {{REV4(0x04,   0x09,         0x09,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090902), fn04090902, &ds04090902},
    {{REV4(0x04,   0x09,         0x09,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090903), fn04090903, &ds04090903},
    {{REV4(0x04,   0x09,         0x0A,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090A01), fn04090A01, &ds04090A01},
    {{REV4(0x04,   0x09,         0x0A,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090A02), fn04090A02, &ds04090A02},
    {{REV4(0x04,   0x09,         0x0B,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090B01), fn04090B01, &ds04090B01},
    {{REV4(0x04,   0x09,         0x0B,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090B02), fn04090B02, &ds04090B02},
    {{REV4(0x04,   0x09,         0x0C,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090C01), fn04090C01, &ds04090C01},
    {{REV4(0x04,   0x09,         0x0C,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090C02), fn04090C02, &ds04090C02},
    {{REV4(0x04,   0x09,         0x0D,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090D01), fn04090D01, &ds04090D01},
    {{REV4(0x04,   0x09,         0x0D,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090D02), fn04090D02, &ds04090D02},
    {{REV4(0x04,   0x09,         0x0D,         0x03)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090D03), fn04090D03, &ds04090D03},
    {{REV4(0x04,   0x09,         0x0E,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090E01), fn04090E01, &ds04090E01},
    {{REV4(0x04,   0x09,         0x0E,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090E02), fn04090E02, &ds04090E02},
    {{REV4(0x04,   0x09,         0x0F,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090F01), fn04090F01, &ds04090F01},
    {{REV4(0x04,   0x09,         0x0F,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04090F02), fn04090F02, &ds04090F02},    
    {{REV4(0x04,   0x09,         0x10,         0x01)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04091001), fn04091001, NULL},
    {{REV4(0x04,   0x09,         0x10,         0x02)}, 0x0054, SIZE_ADDR_OF(EE_sect2, ee04091002), fn04091002, NULL},
*/
    {{REV4(0x04,   0x80,         0x00,         0x01)}, 0x0860, SIZE_ADDR_OF(EE_sect2, ee04800001), fn04800001, &ds04800001},
    {{REV4(0x04,   0x80,         0x00,         0x02)}, 0x0860, SIZE_ADDR_OF(EE_sect2, ee04800002), fn04800002, NULL/*&ds04800002*/},
    {{REV4(0x04,   0x80,         0x00,         0x03)}, 0x0860, SIZE_ADDR_OF(EE_sect2, ee04800003), fn04800003, NULL/*&ds04800003*/},
    {{REV4(0x04,   0x80,         0x00,         0x04)}, 0x0460, SIZE_ADDR_OF(EE_sect2, ee04800004), fn04800004, NULL/*&ds04800004*/},

    {{REV4(0x05,   0x00,         0x00,   BI05000001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0500ZZ01[0].m_05ZZ00ZZ   ), NULL      , &ds05000001},
    {{REV4(0x05,   0x00,         0x01,   BI05000001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0500ZZ01[0].m_05ZZ01ZZ   ), fn05000101, &ds05000101},
    {{REV4(0x05,   0x00,         0x02,   BI05000001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0500ZZ01[0].m_05ZZ02ZZ   ), fn05000101, &ds05000201},
//    {{REV4(0x05,   0x00,     CI05000301, BI05000001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0500ZZ01[0].m_05ZZ03ZZ[0]), fn05000101, &ds05000301},
//    {{REV4(0x05,   0x00,     CI05000501, BI05000001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0500ZZ01[0].m_05ZZ05ZZ[0]), fn05000101, &ds05000501},
//    {{REV4(0x05,   0x00,         0x09,   BI05000001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0500ZZ01[0].m_05ZZ09ZZ   ), fn05000901, &ds05000901},
//    {{REV4(0x05,   0x00,         0x0A,   BI05000001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0500ZZ01[0].m_05ZZ0AZZ   ), fn05000901, &ds05000A01},
    {{REV4(0x05,   0x00,         0x10,   BI05000001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0500ZZ01[0].m_05ZZ10ZZ   ), fn05001001, &ds05001001},
    {{REV4(0x05,   0x01,         0x00,   BI05010001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0501ZZ01[0].m_05ZZ00ZZ   ), NULL      , &ds05010001},
    {{REV4(0x05,   0x01,         0x01,   BI05010001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0501ZZ01[0].m_05ZZ01ZZ   ), fn05000101, &ds05010101},
    {{REV4(0x05,   0x01,         0x02,   BI05010001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0501ZZ01[0].m_05ZZ02ZZ   ), fn05000101, &ds05010201},
//    {{REV4(0x05,   0x01,     CI05000301, BI05010001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0501ZZ01[0].m_05ZZ03ZZ[0]), fn05000101, &ds05010301},
//    {{REV4(0x05,   0x01,     CI05000501, BI05010001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0501ZZ01[0].m_05ZZ05ZZ[0]), fn05000101, &ds05010501},
//    {{REV4(0x05,   0x01,         0x09,   BI05010001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0501ZZ01[0].m_05ZZ09ZZ   ), fn05000901, &ds05010901},
//    {{REV4(0x05,   0x01,         0x0A,   BI05010001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0501ZZ01[0].m_05ZZ0AZZ   ), fn05000901, &ds05010A01},
    {{REV4(0x05,   0x01,         0x10,   BI05010001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0501ZZ01[0].m_05ZZ10ZZ   ), fn05001001, &ds05011001},
    {{REV4(0x05,   0x02,         0x00,   BI05020001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0502ZZ01[0].m_05ZZ00ZZ   ), NULL      , &ds05020001},
    {{REV4(0x05,   0x02,         0x01,   BI05020001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0502ZZ01[0].m_05ZZ01ZZ   ), fn05000101, &ds05020101},
    {{REV4(0x05,   0x02,         0x02,   BI05020001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0502ZZ01[0].m_05ZZ02ZZ   ), fn05000101, &ds05020201},
//    {{REV4(0x05,   0x02,     CI05000301, BI05020001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0502ZZ01[0].m_05ZZ03ZZ[0]), fn05000101, &ds05020301},
//    {{REV4(0x05,   0x02,     CI05000501, BI05020001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0502ZZ01[0].m_05ZZ05ZZ[0]), fn05000101, &ds05020501},
//    {{REV4(0x05,   0x02,         0x09,   BI05020001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0502ZZ01[0].m_05ZZ09ZZ   ), fn05000901, &ds05020901},
//    {{REV4(0x05,   0x02,         0x0A,   BI05020001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0502ZZ01[0].m_05ZZ0AZZ   ), fn05000901, &ds05020A01},
    {{REV4(0x05,   0x02,         0x10,   BI05020001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0502ZZ01[0].m_05ZZ10ZZ   ), fn05001001, &ds05021001},
    {{REV4(0x05,   0x03,         0x00,   BI05030001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0503ZZ01[0].m_05ZZ00ZZ   ), NULL      , &ds05030001},
    {{REV4(0x05,   0x03,         0x01,   BI05030001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0503ZZ01[0].m_05ZZ01ZZ   ), fn05000101, &ds05030101},
    {{REV4(0x05,   0x03,         0x02,   BI05030001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0503ZZ01[0].m_05ZZ02ZZ   ), fn05000101, &ds05030201},
//    {{REV4(0x05,   0x03,     CI05000301, BI05030001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0503ZZ01[0].m_05ZZ03ZZ[0]), fn05000101, &ds05030301},
//    {{REV4(0x05,   0x03,     CI05000501, BI05030001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0503ZZ01[0].m_05ZZ05ZZ[0]), fn05000101, &ds05030501},
//    {{REV4(0x05,   0x03,         0x09,   BI05030001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0503ZZ01[0].m_05ZZ09ZZ   ), fn05000901, &ds05030901},
//    {{REV4(0x05,   0x03,         0x0A,   BI05030001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0503ZZ01[0].m_05ZZ0AZZ   ), fn05000901, &ds05030A01},
    {{REV4(0x05,   0x03,         0x10,   BI05030001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0503ZZ01[0].m_05ZZ10ZZ   ), fn05001001, &ds05031001},
    {{REV4(0x05,   0x04,         0x00,   BI05040001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0504ZZ01[0].m_050400ZZ   ), NULL      , &ds05040001},
    {{REV4(0x05,   0x04,         0x01,   BI05040001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0504ZZ01[0].m_050401ZZ   ), fn05040101, &ds05040101},
    {{REV4(0x05,   0x04,         0x02,   BI05040001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0504ZZ01[0].m_050402ZZ   ), fn05040101, &ds05040201},
#if defined(M_LOCAL)
    /* 【两套费率表切换冻结】 */
    {{REV4(0x05,   0x05,         0x00,   BI05050001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0505ZZ01[0].m_05ZZ00ZZ   ), NULL      , &ds05050001},
    {{REV4(0x05,   0x05,         0x01,   BI05050001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0505ZZ01[0].m_05ZZ01ZZ   ), fn05000101, &ds05050101},
    {{REV4(0x05,   0x05,         0x02,   BI05050001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0505ZZ01[0].m_05ZZ02ZZ   ), fn05000101, &ds05050201},
//    {{REV4(0x05,   0x05,     CI05000301, BI05050001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0505ZZ01[0].m_05ZZ03ZZ[0]), fn05000101, &ds05050301},
//    {{REV4(0x05,   0x05,     CI05000501, BI05050001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0505ZZ01[0].m_05ZZ05ZZ[0]), fn05000101, &ds05050501},
//    {{REV4(0x05,   0x05,         0x09,   BI05050001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0505ZZ01[0].m_05ZZ09ZZ   ), fn05000901, &ds05050901},
//    {{REV4(0x05,   0x05,         0x0A,   BI05050001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0505ZZ01[0].m_05ZZ0AZZ   ), fn05000901, &ds05050A01},
    {{REV4(0x05,   0x05,         0x10,   BI05050001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0505ZZ01[0].m_05ZZ10ZZ   ), fn05001001, &ds05051001},
#endif
    {{REV4(0x05,   0x06,         0x00,   BI05060001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0506ZZ01[0].m_050600ZZ     ), NULL      , &ds05060001},
    {{REV4(0x05,   0x06,         0x01,   BI05060001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0506ZZ01[0].m_050601ZZ     ), fn05000101, &ds05060101},
    {{REV4(0x05,   0x06,         0x02,   BI05060001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0506ZZ01[0].m_050602ZZ     ), fn05000101, &ds05060201},
//    {{REV4(0x05,   0x06,     CI05000301, BI05060001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0506ZZ01[0].m_050603ZZ[0]  ), fn05000101, &ds05060301},
//    {{REV4(0x05,   0x06,     CI05000501, BI05060001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0506ZZ01[0].m_050605ZZ[0]  ), fn05000101, &ds05060501},
//    {{REV4(0x05,   0x06,         0x09,   BI05060001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0506ZZ01[0].m_050609ZZ     ), fn05000901, &ds05060901},
//    {{REV4(0x05,   0x06,         0x0A,   BI05060001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0506ZZ01[0].m_05060AZZ     ), fn05000901, &ds05060A01},
    {{REV4(0x05,   0x06,         0x10,   BI05060001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0506ZZ01[0].m_050610ZZ     ), fn05001001, &ds05061001},

    {{REV4(0x05,   0x07,         0x00,   BI05070001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0507ZZ01[0].m_05ZZ00ZZ   ), NULL      , &ds05070001},
    {{REV4(0x05,   0x07,         0x01,   BI05070001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0507ZZ01[0].m_05ZZ01ZZ   ), fn05000101, &ds05070101},
    {{REV4(0x05,   0x07,         0x02,   BI05070001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0507ZZ01[0].m_05ZZ02ZZ   ), fn05000101, &ds05070201},
//    {{REV4(0x05,   0x07,     CI05000301, BI05070001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0507ZZ01[0].m_05ZZ03ZZ[0]), fn05000101, &ds05070301},
//    {{REV4(0x05,   0x07,     CI05000501, BI05070001)}, 0x3000, SIZE_ADDR_OF(EE_sect5, ee0507ZZ01[0].m_05ZZ05ZZ[0]), fn05000101, &ds05070501},
//    {{REV4(0x05,   0x07,         0x09,   BI05070001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0507ZZ01[0].m_05ZZ09ZZ   ), fn05000901, &ds05070901},
//    {{REV4(0x05,   0x07,         0x0A,   BI05070001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0507ZZ01[0].m_05ZZ0AZZ   ), fn05000901, &ds05070A01},
    {{REV4(0x05,   0x07,         0x10,   BI05070001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0507ZZ01[0].m_05ZZ10ZZ   ), fn05001001, &ds05071001},
#if defined(M_LOCAL)
    {{REV4(0x05,   0x08,         0x02,   BI05060001)}, 0x1000, SIZE_ADDR_OF(EE_sect5, ee0506ZZ01[0].m_050802ZZ     ), NULL, &ds05080201},
#endif
    {{REV4(0x06,   0x00,         0x00,         0x00)}, 0x0000, 0, 0x00000000, fn06000000, NULL},
    {{REV4(0x06,   0x00,         0x00,         0x01)}, 0x0000, 0, 0x00000000, fn06000000, NULL},
    {{REV4(0x06,   0x00,         0x00,         0x02)}, 0x0000, 0, 0x00000000, fn06000002, NULL},
    {{REV4(0x06, CI06010000,     0x00,         0x00)}, 0x4000, 0, 0x00000000, fn06010000, NULL},
    {{REV4(0x06, CI06010000,     0x00,         0x01)}, 0x4000, 0, 0x00000000, fn06010000, NULL},
    {{REV4(0x06, CI06010000,     0x00,         0x02)}, 0x4000, 0, 0x00000000, fn06010002, NULL},

#if defined (MEASURECHIP_ATT7022E)
    {{REV4(0x0D,   0x00,         0x00,         0x00)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000000 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x01)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000001 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x02)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000002 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x03)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000003 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x04)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000004 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x05)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000005 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x06)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000006 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x07)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000007 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x08)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000008 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x09)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000009 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x0A)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00000A ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x0B)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00000B ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x0C)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00000C ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x0D)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00000D ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x0E)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00000E ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x0F)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00000F ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x10)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000010 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x11)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000011 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x12)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000012 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x13)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000013 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x14)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000014 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x15)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000015 ), fn0D000000, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x16)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000016 ), fn0D000016, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x17)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000017 ), fn0D000016, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x18)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000018 ), fn0D000016, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x19)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000019 ), fn0D000016, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x1A)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00001A ), fn0D000016, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x1B)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00001B ), fn0D000016, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x1C)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00001C ), fn0D00001C, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x1D)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00001D ), fn0D00001C, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x1E)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00001E ), fn0D00001C, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x1F)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D00001F ), fn0D00001C, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x20)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000020 ), fn0D00001C, NULL},
    {{REV4(0x0D,   0x00,         0x00,         0x21)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D000021 ), fn0D00001C, NULL},
    
    {{REV4(0x0D,   0x01,         0x00,         0x01)}, 0x0020, sizeof(ra_APCF), (uint32_t)&ra_APCF[0] , NULL   , NULL},
    {{REV4(0x0D,   0x01,         0x00,         0x02)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0D010002 ), fn0D010002, NULL},
    {{REV4(0x0D,   0x01,         0x00,         0x03)}, 0x0060, SIZE_ADDR_OF(FR_sect0, fr0D010003 ), fn0D010003, NULL},
    {{REV4(0x0D,   0x01,         0x00,         0x04)}, 0x0060, SIZE_ADDR_OF(FR_sect0, fr0D010004 ), fn0D010004, NULL},
    {{REV4(0x0D,   0x01,         0x00,         0x05)}, 0x0060, SIZE_ADDR_OF(FR_sect0, fr0D010005 ), fn0D010005, NULL},
    {{REV4(0x0D,   0x0D,         0x01,         0x00)}, 0x0020, 0, 0x00000000, fn0D0D0100, NULL},
    {{REV4(0x0D,   0x0D,         0x02,         0x00)}, 0x0020, 0, 0x00000000, fn0D0D0200, NULL},
    {{REV4(0x0D,   0x0D,         0x03,         0x00)}, 0x0020, 0, 0x00000000, fn0D0D0300, NULL},
    {{REV4(0x0D,   0x0D,         0x04,         0x00)}, 0x0020, 0, 0x00000000, fn0D0D0400, NULL},
    {{REV4(0x0D,   0x0D,         0x05,         0x00)}, 0x0020, 0, 0x00000000, NULL, NULL},
#elif defined (MEASURECHIP_ADE7858)
    {{REV4(0x0E,   0x00,         0x00,         0x00)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000000 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x01)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000001 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x02)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000002 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x03)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000003 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x04)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000004 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x05)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000005 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x06)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000006 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x07)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000007 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x08)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000008 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x09)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000009 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x0A)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00000A ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x0B)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00000B ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x0C)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00000C ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x0D)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00000D ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x0E)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00000E ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x0F)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00000F ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x10)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000010 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x11)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000011 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x12)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000012 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x13)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000013 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x14)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000014 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x15)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000015 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x16)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000016 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x17)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000017 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x18)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000018 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x19)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000019 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x1A)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00001A ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x1B)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00001B ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x1C)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00001C ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x1D)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00001D ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x1E)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00001E ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x1F)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00001F ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x20)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000020 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x21)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000021 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x22)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000022 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x23)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000023 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x24)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000024 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x25)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000025 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x26)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000026 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x27)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000027 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x28)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000028 ), fn0E000000, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x29)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000029 ), fn0E000029, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x2a)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00002a ), fn0E000029, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x2b)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00002b ), fn0E000029, NULL},   
    {{REV4(0x0E,   0x00,         0x00,         0x2c)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00002c ), fn0E00002c, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x2d)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00002d ), fn0E00002c, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x2e)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00002e ), fn0E00002c, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x2f)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E00002f ), fn0E00002c, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x30)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000030 ), fn0E00002c, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x31)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000031 ), fn0E00002c, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x32)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000032 ), fn0E000032, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x33)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000033 ), fn0E000032, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x34)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000034 ), fn0E000032, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x35)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000035 ), fn0E000032, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x36)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000036 ), fn0E000032, NULL},
    {{REV4(0x0E,   0x00,         0x00,         0x37)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E000037 ), fn0E000032, NULL},
    {{REV4(0x0E,   0x01,         0x00,         0x01)}, 0x0020, sizeof(ra_APCF), (uint32_t)&ra_APCF[0] , NULL   , NULL},
    {{REV4(0x0E,   0x01,         0x00,         0x02)}, 0x0020, SIZE_ADDR_OF(FR_sect0, fr0E010002 ), fn0E010002, NULL},
    {{REV4(0x0E,   0x01,         0x00,         0x03)}, 0x0060, SIZE_ADDR_OF(FR_sect0, fr0E010003 ), fn0E010003, NULL},
    {{REV4(0x0E,   0x0E,         0x01,         0x00)}, 0x0020, 0, 0x00000000, fn0E0E0100, NULL},
    {{REV4(0x0E,   0x0E,         0x02,         0x00)}, 0x0020, 0, 0x00000000, fn0E0E0200, NULL},
    {{REV4(0x0E,   0x0E,         0x03,         0x00)}, 0x0020, 0, 0x00000000, fn0E0E0300, NULL},
    {{REV4(0x0E,   0x0E,         0x04,         0x00)}, 0x0020, 0, 0x00000000, fn0E0E0400, NULL},
    {{REV4(0x0E,   0x0E,         0x05,         0x00)}, 0x0020, 0, 0x00000000, NULL, NULL},
#endif

    {{REV4(0x0E,   0x0F,         0x00,         0x00)}, 0x0000, 3, 0x00000000, fn0E0F0000, &ds0E0F0000},
    {{REV4(0x0E,   0x0F,         0x01,         0x00)}, 0x0000, 3 * GN, 0x00000000, fn0E0F0100, &ds0E0F0100},
    /* 不支持该功能
    {{REV4(0x0E,   0x0F,         0x02,   CI0E0F0201)}, 0x1000, 4, 0x00000000, fn0E0F0201, &ds0E0F0201},
    {{REV4(0x0E,   0x0F,         0x03,   CI0E0F0301)}, 0x1000, 4, 0x00000000, fn0E0F0301, &ds0E0F0301},
    {{REV4(0x0E,   0x0F,         0x04,   CI0E0F0401)}, 0x1000, 4, 0x00000000, fn0E0F0401, &ds0E0F0401},
    */
#if defined(M_LOCAL)    
    {{REV4(0x0F,   0x00,         0x01,         0x00)}, 0x0000, 1, 0x00000000, fn0F000100, &ds0F000100},
    {{REV4(0x0F,   0x00,         0x01,         0x01)}, 0x0000, sizeof(ra0F000101), (uint32_t)&ra0F000101[0], fn0F000101, &ds0F000101},
#endif
/*
    【失压事件记录】
    {{REV4(0x10,   0x00,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee10000001      ), fn10000001, &ds10000001},
    {{REV4(0x10,   0x00,         0x00,         0x02)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee10000002      ), fn10000001, &ds10000002},
    {{REV4(0x10,   0x00,         0x01,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee10000101      ), NULL, &ds10000101},
    {{REV4(0x10,   0x00,         0x02,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee10000201      ), NULL, &ds10000201},
    {{REV4(0x10, CI10010001,     0x00,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee10010001      ), fn10010001, &ds10010001},
    {{REV4(0x10, CI10010001,     0x00,         0x02)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee10010002      ), fn10010001, &ds10010002},
    {{REV4(0x10, CI10010101,     0x01,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ01ZZ      ), NULL,       &ds10010101},
    {{REV4(0x10, CI10010102,     0x01,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ01ZZ), NULL,       &ds10010102},
    {{REV4(0x10, CI10010101,     0x02,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ02ZZ  ), fn00000000, &ds10010201},
    {{REV4(0x10, CI10010102,     0x02,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ02ZZ), fn00000000, &ds10010202},
    {{REV4(0x10, CI10010101,     0x03,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ03ZZ  ), fn00000000, &ds10010301},
    {{REV4(0x10, CI10010102,     0x03,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ03ZZ), fn00000000, &ds10010302},
    {{REV4(0x10, CI10010101,     0x04,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ04ZZ  ), fn00000000, &ds10010401},
    {{REV4(0x10, CI10010102,     0x04,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ04ZZ), fn00000000, &ds10010402},
    {{REV4(0x10, CI10010101,     0x05,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ05ZZ  ), fn00000000, &ds10010501},
    {{REV4(0x10, CI10010102,     0x05,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ05ZZ), fn00000000, &ds10010502},
    {{REV4(0x10, CI10010101,     0x06,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ06ZZ  ), fn00000000, &ds10010601},
    {{REV4(0x10, CI10010102,     0x06,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ06ZZ), fn00000000, &ds10010602},
    {{REV4(0x10, CI10010101,     0x07,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ07ZZ  ), fn00000000, &ds10010701},
    {{REV4(0x10, CI10010102,     0x07,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ07ZZ), fn00000000, &ds10010702},
    {{REV4(0x10, CI10010101,     0x08,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ08ZZ  ), fn00000000, &ds10010801},
    {{REV4(0x10, CI10010102,     0x08,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ08ZZ), fn00000000, &ds10010802},
    {{REV4(0x10, CI10010101,     0x09,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ09ZZ  ), fn00000000, &ds10010901},
    {{REV4(0x10, CI10010102,     0x09,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ09ZZ), fn00000000, &ds10010902},
    {{REV4(0x10, CI10010101,     0x0A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ0AZZ  ), fn10010A01, &ds10010A01},
    {{REV4(0x10, CI10010102,     0x0A,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ0AZZ), fn10010A01, &ds10010A02},
    {{REV4(0x10, CI10010101,     0x0B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ0BZZ  ), fn10010B01, &ds10010B01},
    {{REV4(0x10, CI10010102,     0x0B,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ0BZZ), fn10010B01, &ds10010B02},
    {{REV4(0x10, CI10010101,     0x0C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ0CZZ  ), fn10010C01, &ds10010C01},
    {{REV4(0x10, CI10010102,     0x0C,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ0CZZ), fn10010C01, &ds10010C02},
    {{REV4(0x10, CI10010101,     0x0D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ0DZZ  ), fn10010C01, &ds10010D01},
    {{REV4(0x10, CI10010102,     0x0D,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ0DZZ), fn10010C01, &ds10010D02},
    {{REV4(0x10, CI10010101,     0x0E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ0EZZ  ), NULL,       &ds10010E01},
    {{REV4(0x10, CI10010102,     0x0E,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ0EZZ), NULL,       &ds10010E02},
    {{REV4(0x10, CI10010101,     0x0F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ0FZZ  ), fn00000000, &ds10010F01},
    {{REV4(0x10, CI10010102,     0x0F,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ0FZZ), fn00000000, &ds10010F02},
    {{REV4(0x10, CI10010101,     0x10,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ10ZZ  ), fn00000000, &ds10011001},
    {{REV4(0x10, CI10010102,     0x10,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ10ZZ), fn00000000, &ds10011002},
    {{REV4(0x10, CI10010101,     0x11,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ11ZZ  ), fn00000000, &ds10011101},
    {{REV4(0x10, CI10010102,     0x11,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ11ZZ), fn00000000, &ds10011102},
    {{REV4(0x10, CI10010101,     0x12,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ12ZZ  ), fn00000000, &ds10011201},
    {{REV4(0x10, CI10010102,     0x12,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ12ZZ), fn00000000, &ds10011202},
    {{REV4(0x10, CI10010101,     0x13,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ13ZZ  ), fn10010A01, &ds10011301},
    {{REV4(0x10, CI10010102,     0x13,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ13ZZ), fn10010A01, &ds10011302},
    {{REV4(0x10, CI10010101,     0x14,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ14ZZ  ), fn10010B01, &ds10011401},
    {{REV4(0x10, CI10010102,     0x14,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ14ZZ), fn10010B01, &ds10011402},
    {{REV4(0x10, CI10010101,     0x15,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ15ZZ  ), fn10010C01, &ds10011501},
    {{REV4(0x10, CI10010102,     0x15,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ15ZZ), fn10010C01, &ds10011502},
    {{REV4(0x10, CI10010101,     0x16,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ16ZZ  ), fn10010C01, &ds10011601},
    {{REV4(0x10, CI10010102,     0x16,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ16ZZ), fn10010C01, &ds10011602},
    {{REV4(0x10, CI10010101,     0x17,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ17ZZ  ), NULL,       &ds10011701},
    {{REV4(0x10, CI10010102,     0x17,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ17ZZ), NULL,       &ds10011702},
    {{REV4(0x10, CI10010101,     0x18,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ18ZZ  ), fn00000000, &ds10011801},
    {{REV4(0x10, CI10010102,     0x18,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ18ZZ), fn00000000, &ds10011802},
    {{REV4(0x10, CI10010101,     0x19,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ19ZZ  ), fn00000000, &ds10011901},
    {{REV4(0x10, CI10010102,     0x19,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ19ZZ), fn00000000, &ds10011902},
    {{REV4(0x10, CI10010101,     0x1A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ1AZZ  ), fn00000000, &ds10011A01},
    {{REV4(0x10, CI10010102,     0x1A,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ1AZZ), fn00000000, &ds10011A02},
    {{REV4(0x10, CI10010101,     0x1B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ1BZZ  ), fn00000000, &ds10011B01},
    {{REV4(0x10, CI10010102,     0x1B,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ1BZZ), fn00000000, &ds10011B02},
    {{REV4(0x10, CI10010101,     0x1C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ1CZZ  ), fn10010A01, &ds10011C01},
    {{REV4(0x10, CI10010102,     0x1C,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ1CZZ), fn10010A01, &ds10011C02},
    {{REV4(0x10, CI10010101,     0x1D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ1DZZ  ), fn10010B01, &ds10011D01},
    {{REV4(0x10, CI10010102,     0x1D,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ1DZZ), fn10010B01, &ds10011D02},
    {{REV4(0x10, CI10010101,     0x1E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ1EZZ  ), fn10010C01, &ds10011E01},
    {{REV4(0x10, CI10010102,     0x1E,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ1EZZ), fn10010C01, &ds10011E02},
    {{REV4(0x10, CI10010101,     0x1F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ1FZZ  ), fn10010C01, &ds10011F01},
    {{REV4(0x10, CI10010102,     0x1F,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ1FZZ), fn10010C01, &ds10011F02},
    {{REV4(0x10, CI10010101,     0x20,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ20ZZ  ), NULL,       &ds10012001},
    {{REV4(0x10, CI10010102,     0x20,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ20ZZ), NULL,       &ds10012002},
    {{REV4(0x10, CI10010101,     0x21,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ21ZZ  ), fn10012101, &ds10012101},
    {{REV4(0x10, CI10010102,     0x21,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ21ZZ), fn10012101, &ds10012102},
    {{REV4(0x10, CI10010101,     0x22,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ22ZZ  ), fn10012101, &ds10012201},
    {{REV4(0x10, CI10010102,     0x22,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ22ZZ), fn10012101, &ds10012202},
    {{REV4(0x10, CI10010101,     0x23,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ23ZZ  ), fn10012101, &ds10012301},
    {{REV4(0x10, CI10010102,     0x23,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ23ZZ), fn10012101, &ds10012302},
    {{REV4(0x10, CI10010101,     0x24,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ24ZZ  ), fn10012101, &ds10012401},
    {{REV4(0x10, CI10010102,     0x24,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ24ZZ), fn10012101, &ds10012402},
    {{REV4(0x10, CI10010101,     0x25,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ25ZZ  ), NULL,       &ds10012501},
    {{REV4(0x10, CI10010102,     0x25,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ25ZZ), NULL,       &ds10012502},
    {{REV4(0x10, CI10010101,     0x26,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ26ZZ  ), fn00000000, &ds10012601},
    {{REV4(0x10, CI10010102,     0x26,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ26ZZ), fn00000000, &ds10012602},
    {{REV4(0x10, CI10010101,     0x27,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ27ZZ  ), fn00000000, &ds10012701},
    {{REV4(0x10, CI10010102,     0x27,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ27ZZ), fn00000000, &ds10012702},
    {{REV4(0x10, CI10010101,     0x28,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ28ZZ  ), fn00000000, &ds10012801},
    {{REV4(0x10, CI10010102,     0x28,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ28ZZ), fn00000000, &ds10012802},
    {{REV4(0x10, CI10010101,     0x29,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ29ZZ  ), fn00000000, &ds10012901},
    {{REV4(0x10, CI10010102,     0x29,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ29ZZ), fn00000000, &ds10012902},
    {{REV4(0x10, CI10010101,     0x2A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ2AZZ  ), fn00000000, &ds10012A01},
    {{REV4(0x10, CI10010102,     0x2A,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ2AZZ), fn00000000, &ds10012A02},
    {{REV4(0x10, CI10010101,     0x2B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ2BZZ  ), fn00000000, &ds10012B01},
    {{REV4(0x10, CI10010102,     0x2B,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ2BZZ), fn00000000, &ds10012B02},
    {{REV4(0x10, CI10010101,     0x2C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ2CZZ  ), fn00000000, &ds10012C01},
    {{REV4(0x10, CI10010102,     0x2C,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ2CZZ), fn00000000, &ds10012C02},
    {{REV4(0x10, CI10010101,     0x2D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ2DZZ  ), fn00000000, &ds10012D01},
    {{REV4(0x10, CI10010102,     0x2D,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ2DZZ), fn00000000, &ds10012D02},
    {{REV4(0x10, CI10010101,     0x2E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ2EZZ  ), fn00000000, &ds10012E01},
    {{REV4(0x10, CI10010102,     0x2E,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ2EZZ), fn00000000, &ds10012E02},
    {{REV4(0x10, CI10010101,     0x2F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ2FZZ  ), fn00000000, &ds10012F01},
    {{REV4(0x10, CI10010102,     0x2F,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ2FZZ), fn00000000, &ds10012F02},
    {{REV4(0x10, CI10010101,     0x30,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ30ZZ  ), fn00000000, &ds10013001},
    {{REV4(0x10, CI10010102,     0x30,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ30ZZ), fn00000000, &ds10013002},
    {{REV4(0x10, CI10010101,     0x31,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ31ZZ  ), fn00000000, &ds10013101},
    {{REV4(0x10, CI10010102,     0x31,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ31ZZ), fn00000000, &ds10013102},
    {{REV4(0x10, CI10010101,     0x32,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ32ZZ  ), fn00000000, &ds10013201},
    {{REV4(0x10, CI10010102,     0x32,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ32ZZ), fn00000000, &ds10013202},
    {{REV4(0x10, CI10010101,     0x33,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ33ZZ  ), fn00000000, &ds10013301},
    {{REV4(0x10, CI10010102,     0x33,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ33ZZ), fn00000000, &ds10013302},
    {{REV4(0x10, CI10010101,     0x34,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ34ZZ  ), fn00000000, &ds10013401},
    {{REV4(0x10, CI10010102,     0x34,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ34ZZ), fn00000000, &ds10013402},
    {{REV4(0x10, CI10010101,     0x35,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1001ZZ01[0][0].m_10ZZ35ZZ  ), fn00000000, &ds10013501},
    {{REV4(0x10, CI10010102,     0x35,   BI10010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1001ZZ02[0]._[0].m_10ZZ35ZZ), fn00000000, &ds10013502},

    【欠压事件记录】
    {{REV4(0x11, CI11010001,     0x00,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee11010001                   ), fn10010001, NULL},
    {{REV4(0x11, CI11010001,     0x00,         0x02)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee11010002                   ), fn10010001, NULL},
    {{REV4(0x11, CI11010101,     0x01,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ01ZZ  ), NULL,       NULL},
    {{REV4(0x11, CI11010102,     0x01,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ01ZZ), NULL,       NULL},
    {{REV4(0x11, CI11010101,     0x02,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ02ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x02,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ02ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x03,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ03ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x03,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ03ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x04,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ04ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x04,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ04ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x05,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ05ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x05,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ05ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x06,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ06ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x06,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ06ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x07,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ07ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x07,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ07ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x08,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ08ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x08,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ08ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x09,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ09ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x09,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ09ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x0A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ0AZZ  ), fn10010A01, NULL},
    {{REV4(0x11, CI11010102,     0x0A,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ0AZZ), fn10010A01, NULL},
    {{REV4(0x11, CI11010101,     0x0B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ0BZZ  ), fn10010B01, NULL},
    {{REV4(0x11, CI11010102,     0x0B,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ0BZZ), fn10010B01, NULL},
    {{REV4(0x11, CI11010101,     0x0C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ0CZZ  ), fn10010C01, NULL},
    {{REV4(0x11, CI11010102,     0x0C,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ0CZZ), fn10010C01, NULL},
    {{REV4(0x11, CI11010101,     0x0D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ0DZZ  ), fn10010C01, NULL},
    {{REV4(0x11, CI11010102,     0x0D,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ0DZZ), fn10010C01, NULL},
    {{REV4(0x11, CI11010101,     0x0E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ0EZZ  ), NULL,       NULL},
    {{REV4(0x11, CI11010102,     0x0E,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ0EZZ), NULL,       NULL},
    {{REV4(0x11, CI11010101,     0x0F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ0FZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x0F,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ0FZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x10,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ10ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x10,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ10ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x11,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ11ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x11,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ11ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x12,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ12ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x12,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ12ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x13,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ13ZZ  ), fn10010A01, NULL},
    {{REV4(0x11, CI11010102,     0x13,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ13ZZ), fn10010A01, NULL},
    {{REV4(0x11, CI11010101,     0x14,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ14ZZ  ), fn10010B01, NULL},
    {{REV4(0x11, CI11010102,     0x14,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ14ZZ), fn10010B01, NULL},
    {{REV4(0x11, CI11010101,     0x15,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ15ZZ  ), fn10010C01, NULL},
    {{REV4(0x11, CI11010102,     0x15,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ15ZZ), fn10010C01, NULL},
    {{REV4(0x11, CI11010101,     0x16,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ16ZZ  ), fn10010C01, NULL},
    {{REV4(0x11, CI11010102,     0x16,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ16ZZ), fn10010C01, NULL},
    {{REV4(0x11, CI11010101,     0x17,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ17ZZ  ), NULL,       NULL},
    {{REV4(0x11, CI11010102,     0x17,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ17ZZ), NULL,       NULL},
    {{REV4(0x11, CI11010101,     0x18,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ18ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x18,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ18ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x19,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ19ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x19,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ19ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x1A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ1AZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x1A,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ1AZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x1B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ1BZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x1B,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ1BZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x1C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ1CZZ  ), fn10010A01, NULL},
    {{REV4(0x11, CI11010102,     0x1C,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ1CZZ), fn10010A01, NULL},
    {{REV4(0x11, CI11010101,     0x1D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ1DZZ  ), fn10010B01, NULL},
    {{REV4(0x11, CI11010102,     0x1D,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ1DZZ), fn10010B01, NULL},
    {{REV4(0x11, CI11010101,     0x1E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ1EZZ  ), fn10010C01, NULL},
    {{REV4(0x11, CI11010102,     0x1E,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ1EZZ), fn10010C01, NULL},
    {{REV4(0x11, CI11010101,     0x1F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ1FZZ  ), fn10010C01, NULL},
    {{REV4(0x11, CI11010102,     0x1F,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ1FZZ), fn10010C01, NULL},
    {{REV4(0x11, CI11010101,     0x20,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ20ZZ  ), NULL,       NULL},
    {{REV4(0x11, CI11010102,     0x20,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ20ZZ), NULL,       NULL},
    {{REV4(0x11, CI11010101,     0x21,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ21ZZ  ), fn10012101, NULL},
    {{REV4(0x11, CI11010102,     0x21,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ21ZZ), fn10012101, NULL},
    {{REV4(0x11, CI11010101,     0x22,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ22ZZ  ), fn10012101, NULL},
    {{REV4(0x11, CI11010102,     0x22,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ22ZZ), fn10012101, NULL},
    {{REV4(0x11, CI11010101,     0x23,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ23ZZ  ), fn10012101, NULL},
    {{REV4(0x11, CI11010102,     0x23,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ23ZZ), fn10012101, NULL},
    {{REV4(0x11, CI11010101,     0x24,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ24ZZ  ), fn10012101, NULL},
    {{REV4(0x11, CI11010102,     0x24,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ24ZZ), fn10012101, NULL},
    {{REV4(0x11, CI11010101,     0x25,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ25ZZ  ), NULL,       NULL},
    {{REV4(0x11, CI11010102,     0x25,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ25ZZ), NULL,       NULL},
    {{REV4(0x11, CI11010101,     0x26,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ26ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x26,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ26ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x27,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ27ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x27,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ27ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x28,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ28ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x28,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ28ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x29,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ29ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x29,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ29ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x2A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ2AZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x2A,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ2AZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x2B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ2BZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x2B,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ2BZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x2C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ2CZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x2C,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ2CZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x2D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ2DZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x2D,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ2DZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x2E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ2EZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x2E,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ2EZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x2F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ2FZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x2F,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ2FZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x30,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ30ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x30,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ30ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x31,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ31ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x31,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ31ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x32,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ32ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x32,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ32ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x33,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ33ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x33,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ33ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x34,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ34ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x34,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ34ZZ), fn00000000, NULL},
    {{REV4(0x11, CI11010101,     0x35,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1101ZZ01[0][0].m_10ZZ35ZZ  ), fn00000000, NULL},
    {{REV4(0x11, CI11010102,     0x35,   BI11010102)}, 0x5200, SIZE_ADDR_OF(DF_sect4, df1101ZZ02[0]._[0].m_10ZZ35ZZ), fn00000000, NULL},

    【过压事件记录】
    {{REV4(0x12, CI12010001,     0x00,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee12010001                   ), fn10010001, NULL},
    {{REV4(0x12, CI12010001,     0x00,         0x02)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee12010002                   ), fn10010001, NULL},
    {{REV4(0x12, CI12010101,     0x01,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ01ZZ  ), NULL,       NULL},
    {{REV4(0x12, CI12010102,     0x01,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ01ZZ), NULL,       NULL},
    {{REV4(0x12, CI12010101,     0x02,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ02ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x02,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ02ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x03,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ03ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x03,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ03ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x04,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ04ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x04,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ04ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x05,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ05ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x05,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ05ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x06,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ06ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x06,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ06ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x07,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ07ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x07,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ07ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x08,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ08ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x08,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ08ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x09,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ09ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x09,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ09ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x0A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ0AZZ  ), fn10010A01, NULL},
    {{REV4(0x12, CI12010102,     0x0A,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ0AZZ), fn10010A01, NULL},
    {{REV4(0x12, CI12010101,     0x0B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ0BZZ  ), fn10010B01, NULL},
    {{REV4(0x12, CI12010102,     0x0B,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ0BZZ), fn10010B01, NULL},
    {{REV4(0x12, CI12010101,     0x0C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ0CZZ  ), fn10010C01, NULL},
    {{REV4(0x12, CI12010102,     0x0C,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ0CZZ), fn10010C01, NULL},
    {{REV4(0x12, CI12010101,     0x0D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ0DZZ  ), fn10010C01, NULL},
    {{REV4(0x12, CI12010102,     0x0D,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ0DZZ), fn10010C01, NULL},
    {{REV4(0x12, CI12010101,     0x0E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ0EZZ  ), NULL,       NULL},
    {{REV4(0x12, CI12010102,     0x0E,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ0EZZ), NULL,       NULL},
    {{REV4(0x12, CI12010101,     0x0F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ0FZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x0F,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ0FZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x10,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ10ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x10,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ10ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x11,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ11ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x11,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ11ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x12,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ12ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x12,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ12ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x13,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ13ZZ  ), fn10010A01, NULL},
    {{REV4(0x12, CI12010102,     0x13,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ13ZZ), fn10010A01, NULL},
    {{REV4(0x12, CI12010101,     0x14,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ14ZZ  ), fn10010B01, NULL},
    {{REV4(0x12, CI12010102,     0x14,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ14ZZ), fn10010B01, NULL},
    {{REV4(0x12, CI12010101,     0x15,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ15ZZ  ), fn10010C01, NULL},
    {{REV4(0x12, CI12010102,     0x15,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ15ZZ), fn10010C01, NULL},
    {{REV4(0x12, CI12010101,     0x16,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ16ZZ  ), fn10010C01, NULL},
    {{REV4(0x12, CI12010102,     0x16,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ16ZZ), fn10010C01, NULL},
    {{REV4(0x12, CI12010101,     0x17,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ17ZZ  ), NULL,       NULL},
    {{REV4(0x12, CI12010102,     0x17,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ17ZZ), NULL,       NULL},
    {{REV4(0x12, CI12010101,     0x18,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ18ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x18,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ18ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x19,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ19ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x19,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ19ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x1A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ1AZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x1A,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ1AZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x1B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ1BZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x1B,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ1BZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x1C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ1CZZ  ), fn10010A01, NULL},
    {{REV4(0x12, CI12010102,     0x1C,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ1CZZ), fn10010A01, NULL},
    {{REV4(0x12, CI12010101,     0x1D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ1DZZ  ), fn10010B01, NULL},
    {{REV4(0x12, CI12010102,     0x1D,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ1DZZ), fn10010B01, NULL},
    {{REV4(0x12, CI12010101,     0x1E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ1EZZ  ), fn10010C01, NULL},
    {{REV4(0x12, CI12010102,     0x1E,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ1EZZ), fn10010C01, NULL},
    {{REV4(0x12, CI12010101,     0x1F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ1FZZ  ), fn10010C01, NULL},
    {{REV4(0x12, CI12010102,     0x1F,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ1FZZ), fn10010C01, NULL},
    {{REV4(0x12, CI12010101,     0x20,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ20ZZ  ), NULL,       NULL},
    {{REV4(0x12, CI12010102,     0x20,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ20ZZ), NULL,       NULL},
    {{REV4(0x12, CI12010101,     0x21,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ21ZZ  ), fn10012101, NULL},
    {{REV4(0x12, CI12010102,     0x21,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ21ZZ), fn10012101, NULL},
    {{REV4(0x12, CI12010101,     0x22,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ22ZZ  ), fn10012101, NULL},
    {{REV4(0x12, CI12010102,     0x22,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ22ZZ), fn10012101, NULL},
    {{REV4(0x12, CI12010101,     0x23,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ23ZZ  ), fn10012101, NULL},
    {{REV4(0x12, CI12010102,     0x23,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ23ZZ), fn10012101, NULL},
    {{REV4(0x12, CI12010101,     0x24,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ24ZZ  ), fn10012101, NULL},
    {{REV4(0x12, CI12010102,     0x24,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ24ZZ), fn10012101, NULL},
    {{REV4(0x12, CI12010101,     0x25,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ25ZZ  ), NULL,       NULL},
    {{REV4(0x12, CI12010102,     0x25,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ25ZZ), NULL,       NULL},
    {{REV4(0x12, CI12010101,     0x26,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ26ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x26,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ26ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x27,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ27ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x27,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ27ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x28,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ28ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x28,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ28ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x29,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ29ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x29,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ29ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x2A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ2AZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x2A,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ2AZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x2B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ2BZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x2B,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ2BZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x2C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ2CZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x2C,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ2CZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x2D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ2DZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x2D,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ2DZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x2E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ2EZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x2E,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ2EZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x2F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ2FZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x2F,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ2FZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x30,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ30ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x30,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ30ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x31,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ31ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x31,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ31ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x32,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ32ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x32,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ32ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x33,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ33ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x33,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ33ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x34,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ34ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x34,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ34ZZ), fn00000000, NULL},
    {{REV4(0x12, CI12010101,     0x35,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1201ZZ01[0][0].m_10ZZ35ZZ  ), fn00000000, NULL},
    {{REV4(0x12, CI12010102,     0x35,   BI12010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1201ZZ02[0]._[0].m_10ZZ35ZZ), fn00000000, NULL},

    【断相事件记录】
    {{REV4(0x13, CI13010001,     0x00,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee13010001      ), fn10010001, &ds13010001},
    {{REV4(0x13, CI13010001,     0x00,         0x02)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee13010002      ), fn10010001, &ds13010002},
    {{REV4(0x13, CI13010101,     0x01,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ01ZZ      ), NULL,       &ds13010101},
    {{REV4(0x13, CI13010102,     0x01,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ01ZZ), NULL,       &ds13010102},
    {{REV4(0x13, CI13010101,     0x02,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ02ZZ  ), fn00000000, &ds13010201},
    {{REV4(0x13, CI13010102,     0x02,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ02ZZ), fn00000000, &ds13010202},
    {{REV4(0x13, CI13010101,     0x03,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ03ZZ  ), fn00000000, &ds13010301},
    {{REV4(0x13, CI13010102,     0x03,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ03ZZ), fn00000000, &ds13010302},
    {{REV4(0x13, CI13010101,     0x04,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ04ZZ  ), fn00000000, &ds13010401},
    {{REV4(0x13, CI13010102,     0x04,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ04ZZ), fn00000000, &ds13010402},
    {{REV4(0x13, CI13010101,     0x05,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ05ZZ  ), fn00000000, &ds13010501},
    {{REV4(0x13, CI13010102,     0x05,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ05ZZ), fn00000000, &ds13010502},
    {{REV4(0x13, CI13010101,     0x06,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ06ZZ  ), fn00000000, &ds13010601},
    {{REV4(0x13, CI13010102,     0x06,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ06ZZ), fn00000000, &ds13010602},
    {{REV4(0x13, CI13010101,     0x07,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ07ZZ  ), fn00000000, &ds13010701},
    {{REV4(0x13, CI13010102,     0x07,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ07ZZ), fn00000000, &ds13010702},
    {{REV4(0x13, CI13010101,     0x08,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ08ZZ  ), fn00000000, &ds13010801},
    {{REV4(0x13, CI13010102,     0x08,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ08ZZ), fn00000000, &ds13010802},
    {{REV4(0x13, CI13010101,     0x09,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ09ZZ  ), fn00000000, &ds13010901},
    {{REV4(0x13, CI13010102,     0x09,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ09ZZ), fn00000000, &ds13010902},
    {{REV4(0x13, CI13010101,     0x0A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ0AZZ  ), fn10010A01, &ds13010A01},
    {{REV4(0x13, CI13010102,     0x0A,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ0AZZ), fn10010A01, &ds13010A02},
    {{REV4(0x13, CI13010101,     0x0B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ0BZZ  ), fn10010B01, &ds13010B01},
    {{REV4(0x13, CI13010102,     0x0B,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ0BZZ), fn10010B01, &ds13010B02},
    {{REV4(0x13, CI13010101,     0x0C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ0CZZ  ), fn10010C01, &ds13010C01},
    {{REV4(0x13, CI13010102,     0x0C,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ0CZZ), fn10010C01, &ds13010C02},
    {{REV4(0x13, CI13010101,     0x0D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ0DZZ  ), fn10010C01, &ds13010D01},
    {{REV4(0x13, CI13010102,     0x0D,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ0DZZ), fn10010C01, &ds13010D02},
    {{REV4(0x13, CI13010101,     0x0E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ0EZZ  ), NULL,       &ds13010E01},
    {{REV4(0x13, CI13010102,     0x0E,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ0EZZ), NULL,       &ds13010E02},
    {{REV4(0x13, CI13010101,     0x0F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ0FZZ  ), fn00000000, &ds13010F01},
    {{REV4(0x13, CI13010102,     0x0F,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ0FZZ), fn00000000, &ds13010F02},
    {{REV4(0x13, CI13010101,     0x10,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ10ZZ  ), fn00000000, &ds13011001},
    {{REV4(0x13, CI13010102,     0x10,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ10ZZ), fn00000000, &ds13011002},
    {{REV4(0x13, CI13010101,     0x11,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ11ZZ  ), fn00000000, &ds13011101},
    {{REV4(0x13, CI13010102,     0x11,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ11ZZ), fn00000000, &ds13011102},
    {{REV4(0x13, CI13010101,     0x12,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ12ZZ  ), fn00000000, &ds13011201},
    {{REV4(0x13, CI13010102,     0x12,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ12ZZ), fn00000000, &ds13011202},
    {{REV4(0x13, CI13010101,     0x13,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ13ZZ  ), fn10010A01, &ds13011301},
    {{REV4(0x13, CI13010102,     0x13,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ13ZZ), fn10010A01, &ds13011302},
    {{REV4(0x13, CI13010101,     0x14,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ14ZZ  ), fn10010B01, &ds13011401},
    {{REV4(0x13, CI13010102,     0x14,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ14ZZ), fn10010B01, &ds13011402},
    {{REV4(0x13, CI13010101,     0x15,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ15ZZ  ), fn10010C01, &ds13011501},
    {{REV4(0x13, CI13010102,     0x15,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ15ZZ), fn10010C01, &ds13011502},
    {{REV4(0x13, CI13010101,     0x16,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ16ZZ  ), fn10010C01, &ds13011601},
    {{REV4(0x13, CI13010102,     0x16,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ16ZZ), fn10010C01, &ds13011602},
    {{REV4(0x13, CI13010101,     0x17,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ17ZZ  ), NULL,       &ds13011701},
    {{REV4(0x13, CI13010102,     0x17,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ17ZZ), NULL,       &ds13011702},
    {{REV4(0x13, CI13010101,     0x18,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ18ZZ  ), fn00000000, &ds13011801},
    {{REV4(0x13, CI13010102,     0x18,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ18ZZ), fn00000000, &ds13011802},
    {{REV4(0x13, CI13010101,     0x19,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ19ZZ  ), fn00000000, &ds13011901},
    {{REV4(0x13, CI13010102,     0x19,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ19ZZ), fn00000000, &ds13011902},
    {{REV4(0x13, CI13010101,     0x1A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ1AZZ  ), fn00000000, &ds13011A01},
    {{REV4(0x13, CI13010102,     0x1A,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ1AZZ), fn00000000, &ds13011A02},
    {{REV4(0x13, CI13010101,     0x1B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ1BZZ  ), fn00000000, &ds13011B01},
    {{REV4(0x13, CI13010102,     0x1B,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ1BZZ), fn00000000, &ds13011B02},
    {{REV4(0x13, CI13010101,     0x1C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ1CZZ  ), fn10010A01, &ds13011C01},
    {{REV4(0x13, CI13010102,     0x1C,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ1CZZ), fn10010A01, &ds13011C02},
    {{REV4(0x13, CI13010101,     0x1D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ1DZZ  ), fn10010B01, &ds13011D01},
    {{REV4(0x13, CI13010102,     0x1D,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ1DZZ), fn10010B01, &ds13011D02},
    {{REV4(0x13, CI13010101,     0x1E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ1EZZ  ), fn10010C01, &ds13011E01},
    {{REV4(0x13, CI13010102,     0x1E,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ1EZZ), fn10010C01, &ds13011E02},
    {{REV4(0x13, CI13010101,     0x1F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ1FZZ  ), fn10010C01, &ds13011F01},
    {{REV4(0x13, CI13010102,     0x1F,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ1FZZ), fn10010C01, &ds13011F02},
    {{REV4(0x13, CI13010101,     0x20,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ20ZZ  ), NULL,       &ds13012001},
    {{REV4(0x13, CI13010102,     0x20,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ20ZZ), NULL,       &ds13012002},
    {{REV4(0x13, CI13010101,     0x21,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ21ZZ  ), fn10012101, &ds13012101},
    {{REV4(0x13, CI13010102,     0x21,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ21ZZ), fn10012101, &ds13012102},
    {{REV4(0x13, CI13010101,     0x22,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ22ZZ  ), fn10012101, &ds13012201},
    {{REV4(0x13, CI13010102,     0x22,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ22ZZ), fn10012101, &ds13012202},
    {{REV4(0x13, CI13010101,     0x23,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ23ZZ  ), fn10012101, &ds13012301},
    {{REV4(0x13, CI13010102,     0x23,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ23ZZ), fn10012101, &ds13012302},
    {{REV4(0x13, CI13010101,     0x24,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ24ZZ  ), fn10012101, &ds13012401},
    {{REV4(0x13, CI13010102,     0x24,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ24ZZ), fn10012101, &ds13012402},
    {{REV4(0x13, CI13010101,     0x25,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ25ZZ  ), NULL,       &ds13012501},
    {{REV4(0x13, CI13010102,     0x25,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ25ZZ), NULL,       &ds13012502},
    {{REV4(0x13, CI13010101,     0x26,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ26ZZ  ), fn00000000, &ds13012601},
    {{REV4(0x13, CI13010102,     0x26,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ26ZZ), fn00000000, &ds13012602},
    {{REV4(0x13, CI13010101,     0x27,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ27ZZ  ), fn00000000, &ds13012701},
    {{REV4(0x13, CI13010102,     0x27,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ27ZZ), fn00000000, &ds13012702},
    {{REV4(0x13, CI13010101,     0x28,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ28ZZ  ), fn00000000, &ds13012801},
    {{REV4(0x13, CI13010102,     0x28,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ28ZZ), fn00000000, &ds13012802},
    {{REV4(0x13, CI13010101,     0x29,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ29ZZ  ), fn00000000, &ds13012901},
    {{REV4(0x13, CI13010102,     0x29,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ29ZZ), fn00000000, &ds13012902},
    {{REV4(0x13, CI13010101,     0x2A,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ2AZZ  ), fn00000000, &ds13012A01},
    {{REV4(0x13, CI13010102,     0x2A,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ2AZZ), fn00000000, &ds13012A02},
    {{REV4(0x13, CI13010101,     0x2B,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ2BZZ  ), fn00000000, &ds13012B01},
    {{REV4(0x13, CI13010102,     0x2B,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ2BZZ), fn00000000, &ds13012B02},
    {{REV4(0x13, CI13010101,     0x2C,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ2CZZ  ), fn00000000, &ds13012C01},
    {{REV4(0x13, CI13010102,     0x2C,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ2CZZ), fn00000000, &ds13012C02},
    {{REV4(0x13, CI13010101,     0x2D,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ2DZZ  ), fn00000000, &ds13012D01},
    {{REV4(0x13, CI13010102,     0x2D,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ2DZZ), fn00000000, &ds13012D02},
    {{REV4(0x13, CI13010101,     0x2E,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ2EZZ  ), fn00000000, &ds13012E01},
    {{REV4(0x13, CI13010102,     0x2E,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ2EZZ), fn00000000, &ds13012E02},
    {{REV4(0x13, CI13010101,     0x2F,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ2FZZ  ), fn00000000, &ds13012F01},
    {{REV4(0x13, CI13010102,     0x2F,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ2FZZ), fn00000000, &ds13012F02},
    {{REV4(0x13, CI13010101,     0x30,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ30ZZ  ), fn00000000, &ds13013001},
    {{REV4(0x13, CI13010102,     0x30,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ30ZZ), fn00000000, &ds13013002},
    {{REV4(0x13, CI13010101,     0x31,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ31ZZ  ), fn00000000, &ds13013101},
    {{REV4(0x13, CI13010102,     0x31,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ31ZZ), fn00000000, &ds13013102},
    {{REV4(0x13, CI13010101,     0x32,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ32ZZ  ), fn00000000, &ds13013201},
    {{REV4(0x13, CI13010102,     0x32,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ32ZZ), fn00000000, &ds13013202},
    {{REV4(0x13, CI13010101,     0x33,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ33ZZ  ), fn00000000, &ds13013301},
    {{REV4(0x13, CI13010102,     0x33,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ33ZZ), fn00000000, &ds13013302},
    {{REV4(0x13, CI13010101,     0x34,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ34ZZ  ), fn00000000, &ds13013401},
    {{REV4(0x13, CI13010102,     0x34,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ34ZZ), fn00000000, &ds13013402},
    {{REV4(0x13, CI13010101,     0x35,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1301ZZ01[0][0].m_10ZZ35ZZ  ), fn00000000, &ds13013501},
    {{REV4(0x13, CI13010102,     0x35,   BI13010102)}, 0x5200, SIZE_ADDR_OF(DF_sect5, df1301ZZ02[0]._[0].m_10ZZ35ZZ), fn00000000, &ds13013502},

    【电压逆向序事件记录】
    {{REV4(0x14,   0x00,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee14000001                   ), fn10010001, NULL},
    {{REV4(0x14,   0x00,         0x00,         0x02)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee14000002                   ), fn10010001, NULL},
    {{REV4(0x14,   0x00,         0x01,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140001ZZ   ), NULL,       NULL},
    {{REV4(0x14,   0x00,         0x02,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140002ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x03,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140003ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x04,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140004ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x05,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140005ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x06,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140006ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x07,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140007ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x08,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140008ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x09,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140009ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x0A,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14000AZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x0B,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14000BZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x0C,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14000CZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x0D,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14000DZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x0E,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14000EZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x0F,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14000FZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x10,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140010ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x11,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140011ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x12,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140012ZZ   ), NULL,       NULL},
    {{REV4(0x14,   0x00,         0x13,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140013ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x14,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140014ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x15,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140015ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x16,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140016ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x17,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140017ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x18,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140018ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x19,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140019ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x1A,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14001AZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x1B,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14001BZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x1C,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14001CZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x1D,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14001DZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x1E,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14001EZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x1F,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_14001FZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x20,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140020ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x21,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140021ZZ   ), fn00000000, NULL},
    {{REV4(0x14,   0x00,         0x22,   BI14000101)}, 0x1000, SIZE_ADDR_OF(DF_sect5, df1400ZZ01._[0].m_140022ZZ   ), fn00000000, NULL},

     【电流逆向序事件记录】
    {{REV4(0x15,   0x00,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee15000001                   ), fn10010001, NULL},
    {{REV4(0x15,   0x00,         0x00,         0x02)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee15000002                   ), fn10010001, NULL},
    {{REV4(0x15,   0x00,         0x01,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140001ZZ   ), NULL,       NULL},
    {{REV4(0x15,   0x00,         0x02,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140002ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x03,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140003ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x04,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140004ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x05,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140005ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x06,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140006ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x07,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140007ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x08,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140008ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x09,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140009ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x0A,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14000AZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x0B,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14000BZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x0C,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14000CZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x0D,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14000DZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x0E,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14000EZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x0F,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14000FZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x10,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140010ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x11,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140011ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x12,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140012ZZ   ), NULL,       NULL},
    {{REV4(0x15,   0x00,         0x13,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140013ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x14,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140014ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x15,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140015ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x16,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140016ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x17,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140017ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x18,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140018ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x19,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140019ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x1A,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14001AZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x1B,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14001BZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x1C,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14001CZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x1D,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14001DZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x1E,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14001EZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x1F,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_14001FZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x20,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140020ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x21,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140021ZZ   ), fn00000000, NULL},
    {{REV4(0x15,   0x00,         0x22,   BI15000101)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1500ZZ01._[0].m_140022ZZ   ), fn00000000, NULL},

    【电压不平衡事件记录】
    {{REV4(0x16,   0x00,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee16000001      ), fn10010001, &ds16000001},
    {{REV4(0x16,   0x00,         0x00,         0x02)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee16000002      ), fn10010001, &ds16000002},
    {{REV4(0x16,   0x00,         0x01,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160001ZZ     ), NULL,       &ds16000101},
    {{REV4(0x16,   0x00,         0x01,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160001ZZ   ), NULL,       &ds16000102},
    {{REV4(0x16,   0x00,         0x02,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160002ZZ     ), fn00000000, &ds16000201},
    {{REV4(0x16,   0x00,         0x02,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160002ZZ   ), fn00000000, &ds16000202},
    {{REV4(0x16,   0x00,         0x03,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160003ZZ     ), fn00000000, &ds16000301},
    {{REV4(0x16,   0x00,         0x03,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160003ZZ   ), fn00000000, &ds16000302},
    {{REV4(0x16,   0x00,         0x04,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160004ZZ     ), fn00000000, &ds16000401},
    {{REV4(0x16,   0x00,         0x04,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160004ZZ   ), fn00000000, &ds16000402},
    {{REV4(0x16,   0x00,         0x05,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160005ZZ     ), fn00000000, &ds16000501},
    {{REV4(0x16,   0x00,         0x05,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160005ZZ   ), fn00000000, &ds16000502},
    {{REV4(0x16,   0x00,         0x06,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160006ZZ     ), fn00000000, &ds16000601},
    {{REV4(0x16,   0x00,         0x06,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160006ZZ   ), fn00000000, &ds16000602},
    {{REV4(0x16,   0x00,         0x07,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160007ZZ     ), fn00000000, &ds16000701},
    {{REV4(0x16,   0x00,         0x07,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160007ZZ   ), fn00000000, &ds16000702},
    {{REV4(0x16,   0x00,         0x08,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160008ZZ     ), fn00000000, &ds16000801},
    {{REV4(0x16,   0x00,         0x08,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160008ZZ   ), fn00000000, &ds16000802},
    {{REV4(0x16,   0x00,         0x09,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160009ZZ     ), fn00000000, &ds16000901},
    {{REV4(0x16,   0x00,         0x09,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160009ZZ   ), fn00000000, &ds16000902},
    {{REV4(0x16,   0x00,         0x0A,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16000AZZ     ), fn00000000, &ds16000A01},
    {{REV4(0x16,   0x00,         0x0A,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16000AZZ   ), fn00000000, &ds16000A02},
    {{REV4(0x16,   0x00,         0x0B,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16000BZZ     ), fn00000000, &ds16000B01},
    {{REV4(0x16,   0x00,         0x0B,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16000BZZ   ), fn00000000, &ds16000B02},
    {{REV4(0x16,   0x00,         0x0C,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16000CZZ     ), fn00000000, &ds16000C01},
    {{REV4(0x16,   0x00,         0x0C,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16000CZZ   ), fn00000000, &ds16000C02},
    {{REV4(0x16,   0x00,         0x0D,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16000DZZ     ), fn00000000, &ds16000D01},
    {{REV4(0x16,   0x00,         0x0D,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16000DZZ   ), fn00000000, &ds16000D02},
    {{REV4(0x16,   0x00,         0x0E,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16000EZZ     ), fn00000000, &ds16000E01},
    {{REV4(0x16,   0x00,         0x0E,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16000EZZ   ), fn00000000, &ds16000E02},
    {{REV4(0x16,   0x00,         0x0F,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16000FZZ     ), fn00000000, &ds16000F01},
    {{REV4(0x16,   0x00,         0x0F,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16000FZZ   ), fn00000000, &ds16000F02},
    {{REV4(0x16,   0x00,         0x10,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160010ZZ     ), fn00000000, &ds16001001},
    {{REV4(0x16,   0x00,         0x10,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160010ZZ   ), fn00000000, &ds16001002},
    {{REV4(0x16,   0x00,         0x11,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160011ZZ     ), fn00000000, &ds16001101},
    {{REV4(0x16,   0x00,         0x11,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160011ZZ   ), fn00000000, &ds16001102},
    {{REV4(0x16,   0x00,         0x12,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160012ZZ     ), fn16001201, &ds16001201},
    {{REV4(0x16,   0x00,         0x12,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160012ZZ   ), fn16001201, &ds16001202},
    {{REV4(0x16,   0x00,         0x13,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160013ZZ     ), NULL,       &ds16001301},
    {{REV4(0x16,   0x00,         0x13,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160013ZZ   ), NULL,       &ds16001302},
    {{REV4(0x16,   0x00,         0x14,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160014ZZ     ), fn00000000, &ds16001401},
    {{REV4(0x16,   0x00,         0x14,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160014ZZ   ), fn00000000, &ds16001402},
    {{REV4(0x16,   0x00,         0x15,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160015ZZ     ), fn00000000, &ds16001501},
    {{REV4(0x16,   0x00,         0x15,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160015ZZ   ), fn00000000, &ds16001502},
    {{REV4(0x16,   0x00,         0x16,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160016ZZ     ), fn00000000, &ds16001601},
    {{REV4(0x16,   0x00,         0x16,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160016ZZ   ), fn00000000, &ds16001602},
    {{REV4(0x16,   0x00,         0x17,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160017ZZ     ), fn00000000, &ds16001701},
    {{REV4(0x16,   0x00,         0x17,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160017ZZ   ), fn00000000, &ds16001702},
    {{REV4(0x16,   0x00,         0x18,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160018ZZ     ), fn00000000, &ds16001801},
    {{REV4(0x16,   0x00,         0x18,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160018ZZ   ), fn00000000, &ds16001802},
    {{REV4(0x16,   0x00,         0x19,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160019ZZ     ), fn00000000, &ds16001901},
    {{REV4(0x16,   0x00,         0x19,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160019ZZ   ), fn00000000, &ds16001902},
    {{REV4(0x16,   0x00,         0x1A,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16001AZZ     ), fn00000000, &ds16001A01},
    {{REV4(0x16,   0x00,         0x1A,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16001AZZ   ), fn00000000, &ds16001A02},
    {{REV4(0x16,   0x00,         0x1B,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16001BZZ     ), fn00000000, &ds16001B01},
    {{REV4(0x16,   0x00,         0x1B,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16001BZZ   ), fn00000000, &ds16001B02},
    {{REV4(0x16,   0x00,         0x1C,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16001CZZ     ), fn00000000, &ds16001C01},
    {{REV4(0x16,   0x00,         0x1C,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16001CZZ   ), fn00000000, &ds16001C02},
    {{REV4(0x16,   0x00,         0x1D,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16001DZZ     ), fn00000000, &ds16001D01},
    {{REV4(0x16,   0x00,         0x1D,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16001DZZ   ), fn00000000, &ds16001D02},
    {{REV4(0x16,   0x00,         0x1E,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16001EZZ     ), fn00000000, &ds16001E01},
    {{REV4(0x16,   0x00,         0x1E,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16001EZZ   ), fn00000000, &ds16001E02},
    {{REV4(0x16,   0x00,         0x1F,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_16001FZZ     ), fn00000000, &ds16001F01},
    {{REV4(0x16,   0x00,         0x1F,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_16001FZZ   ), fn00000000, &ds16001F02},
    {{REV4(0x16,   0x00,         0x20,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160020ZZ     ), fn00000000, &ds16002001},
    {{REV4(0x16,   0x00,         0x20,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160020ZZ   ), fn00000000, &ds16002002},
    {{REV4(0x16,   0x00,         0x21,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160021ZZ     ), fn00000000, &ds16002101},
    {{REV4(0x16,   0x00,         0x21,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160021ZZ   ), fn00000000, &ds16002102},
    {{REV4(0x16,   0x00,         0x22,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160022ZZ     ), fn00000000, &ds16002201},
    {{REV4(0x16,   0x00,         0x22,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160022ZZ   ), fn00000000, &ds16002202},
    {{REV4(0x16,   0x00,         0x23,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1600ZZ01[0].m_160023ZZ     ), fn00000000, &ds16002301},
    {{REV4(0x16,   0x00,         0x23,   BI16000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1600ZZ02._[0].m_160023ZZ   ), fn00000000, &ds16002302},

     【电流不平衡事件记录】 
    {{REV4(0x17,   0x00,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee17000001      ), fn10010001, &ds17000001},
    {{REV4(0x17,   0x00,         0x00,         0x02)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee17000002      ), fn10010001, &ds17000002},
    {{REV4(0x17,   0x00,         0x01,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160001ZZ     ), NULL,       &ds17000101},
    {{REV4(0x17,   0x00,         0x01,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160001ZZ   ), NULL,       &ds17000102},
    {{REV4(0x17,   0x00,         0x02,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160002ZZ     ), fn00000000, &ds17000201},
    {{REV4(0x17,   0x00,         0x02,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160002ZZ   ), fn00000000, &ds17000202},
    {{REV4(0x17,   0x00,         0x03,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160003ZZ     ), fn00000000, &ds17000301},
    {{REV4(0x17,   0x00,         0x03,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160003ZZ   ), fn00000000, &ds17000302},
    {{REV4(0x17,   0x00,         0x04,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160004ZZ     ), fn00000000, &ds17000401},
    {{REV4(0x17,   0x00,         0x04,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160004ZZ   ), fn00000000, &ds17000402},
    {{REV4(0x17,   0x00,         0x05,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160005ZZ     ), fn00000000, &ds17000501},
    {{REV4(0x17,   0x00,         0x05,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160005ZZ   ), fn00000000, &ds17000502},
    {{REV4(0x17,   0x00,         0x06,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160006ZZ     ), fn00000000, &ds17000601},
    {{REV4(0x17,   0x00,         0x06,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160006ZZ   ), fn00000000, &ds17000602},
    {{REV4(0x17,   0x00,         0x07,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160007ZZ     ), fn00000000, &ds17000701},
    {{REV4(0x17,   0x00,         0x07,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160007ZZ   ), fn00000000, &ds17000702},
    {{REV4(0x17,   0x00,         0x08,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160008ZZ     ), fn00000000, &ds17000801},
    {{REV4(0x17,   0x00,         0x08,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160008ZZ   ), fn00000000, &ds17000802},
    {{REV4(0x17,   0x00,         0x09,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160009ZZ     ), fn00000000, &ds17000901},
    {{REV4(0x17,   0x00,         0x09,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160009ZZ   ), fn00000000, &ds17000902},
    {{REV4(0x17,   0x00,         0x0A,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16000AZZ     ), fn00000000, &ds17000A01},
    {{REV4(0x17,   0x00,         0x0A,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16000AZZ   ), fn00000000, &ds17000A02},
    {{REV4(0x17,   0x00,         0x0B,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16000BZZ     ), fn00000000, &ds17000B01},
    {{REV4(0x17,   0x00,         0x0B,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16000BZZ   ), fn00000000, &ds17000B02},
    {{REV4(0x17,   0x00,         0x0C,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16000CZZ     ), fn00000000, &ds17000C01},
    {{REV4(0x17,   0x00,         0x0C,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16000CZZ   ), fn00000000, &ds17000C02},
    {{REV4(0x17,   0x00,         0x0D,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16000DZZ     ), fn00000000, &ds17000D01},
    {{REV4(0x17,   0x00,         0x0D,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16000DZZ   ), fn00000000, &ds17000D02},
    {{REV4(0x17,   0x00,         0x0E,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16000EZZ     ), fn00000000, &ds17000E01},
    {{REV4(0x17,   0x00,         0x0E,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16000EZZ   ), fn00000000, &ds17000E02},
    {{REV4(0x17,   0x00,         0x0F,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16000FZZ     ), fn00000000, &ds17000F01},
    {{REV4(0x17,   0x00,         0x0F,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16000FZZ   ), fn00000000, &ds17000F02},
    {{REV4(0x17,   0x00,         0x10,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160010ZZ     ), fn00000000, &ds17001001},
    {{REV4(0x17,   0x00,         0x10,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160010ZZ   ), fn00000000, &ds17001002},
    {{REV4(0x17,   0x00,         0x11,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160011ZZ     ), fn00000000, &ds17001101},
    {{REV4(0x17,   0x00,         0x11,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160011ZZ   ), fn00000000, &ds17001102},
    {{REV4(0x17,   0x00,         0x12,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160012ZZ     ), fn16001201, &ds17001201},
    {{REV4(0x17,   0x00,         0x12,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160012ZZ   ), fn16001201, &ds17001202},
    {{REV4(0x17,   0x00,         0x13,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160013ZZ     ), NULL,       &ds17001301},
    {{REV4(0x17,   0x00,         0x13,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160013ZZ   ), NULL,       &ds17001302},
    {{REV4(0x17,   0x00,         0x14,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160014ZZ     ), fn00000000, &ds17001401},
    {{REV4(0x17,   0x00,         0x14,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160014ZZ   ), fn00000000, &ds17001402},
    {{REV4(0x17,   0x00,         0x15,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160015ZZ     ), fn00000000, &ds17001501},
    {{REV4(0x17,   0x00,         0x15,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160015ZZ   ), fn00000000, &ds17001502},
    {{REV4(0x17,   0x00,         0x16,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160016ZZ     ), fn00000000, &ds17001601},
    {{REV4(0x17,   0x00,         0x16,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160016ZZ   ), fn00000000, &ds17001602},
    {{REV4(0x17,   0x00,         0x17,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160017ZZ     ), fn00000000, &ds17001701},
    {{REV4(0x17,   0x00,         0x17,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160017ZZ   ), fn00000000, &ds17001702},
    {{REV4(0x17,   0x00,         0x18,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160018ZZ     ), fn00000000, &ds17001801},
    {{REV4(0x17,   0x00,         0x18,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160018ZZ   ), fn00000000, &ds17001802},
    {{REV4(0x17,   0x00,         0x19,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160019ZZ     ), fn00000000, &ds17001901},
    {{REV4(0x17,   0x00,         0x19,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160019ZZ   ), fn00000000, &ds17001902},
    {{REV4(0x17,   0x00,         0x1A,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16001AZZ     ), fn00000000, &ds17001A01},
    {{REV4(0x17,   0x00,         0x1A,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16001AZZ   ), fn00000000, &ds17001A02},
    {{REV4(0x17,   0x00,         0x1B,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16001BZZ     ), fn00000000, &ds17001B01},
    {{REV4(0x17,   0x00,         0x1B,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16001BZZ   ), fn00000000, &ds17001B02},
    {{REV4(0x17,   0x00,         0x1C,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16001CZZ     ), fn00000000, &ds17001C01},
    {{REV4(0x17,   0x00,         0x1C,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16001CZZ   ), fn00000000, &ds17001C02},
    {{REV4(0x17,   0x00,         0x1D,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16001DZZ     ), fn00000000, &ds17001D01},
    {{REV4(0x17,   0x00,         0x1D,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16001DZZ   ), fn00000000, &ds17001D02},
    {{REV4(0x17,   0x00,         0x1E,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16001EZZ     ), fn00000000, &ds17001E01},
    {{REV4(0x17,   0x00,         0x1E,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16001EZZ   ), fn00000000, &ds17001E02},
    {{REV4(0x17,   0x00,         0x1F,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_16001FZZ     ), fn00000000, &ds17001F01},
    {{REV4(0x17,   0x00,         0x1F,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_16001FZZ   ), fn00000000, &ds17001F02},
    {{REV4(0x17,   0x00,         0x20,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160020ZZ     ), fn00000000, &ds17002001},
    {{REV4(0x17,   0x00,         0x20,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160020ZZ   ), fn00000000, &ds17002002},
    {{REV4(0x17,   0x00,         0x21,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160021ZZ     ), fn00000000, &ds17002101},
    {{REV4(0x17,   0x00,         0x21,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160021ZZ   ), fn00000000, &ds17002102},
    {{REV4(0x17,   0x00,         0x22,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160022ZZ     ), fn00000000, &ds17002201},
    {{REV4(0x17,   0x00,         0x22,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160022ZZ   ), fn00000000, &ds17002202},
    {{REV4(0x17,   0x00,         0x23,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1700ZZ01[0].m_160023ZZ     ), fn00000000, &ds17002301},
    {{REV4(0x17,   0x00,         0x23,   BI17000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df1700ZZ02._[0].m_160023ZZ   ), fn00000000, &ds17002302},

     【失流事件记录】 
    {{REV4(0x18, CI18010001,     0x00,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee18010001      ), fn10010001, &ds18010001},
    {{REV4(0x18, CI18010001,     0x00,         0x02)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee18010002      ), fn10010001, &ds18010002},
    {{REV4(0x18, CI18010101,     0x01,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ01ZZ), NULL,       &ds18010101},
    {{REV4(0x18, CI18010101,     0x02,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ02ZZ), fn00000000, &ds18010201},
    {{REV4(0x18, CI18010101,     0x03,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ03ZZ), fn00000000, &ds18010301},
    {{REV4(0x18, CI18010101,     0x04,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ04ZZ), fn00000000, &ds18010401},
    {{REV4(0x18, CI18010101,     0x05,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ05ZZ), fn00000000, &ds18010501},
    {{REV4(0x18, CI18010101,     0x06,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ06ZZ), fn00000000, &ds18010601},
    {{REV4(0x18, CI18010101,     0x07,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ07ZZ), fn00000000, &ds18010701},
    {{REV4(0x18, CI18010101,     0x08,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ08ZZ), fn00000000, &ds18010801},
    {{REV4(0x18, CI18010101,     0x09,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ09ZZ), fn00000000, &ds18010901},
    {{REV4(0x18, CI18010101,     0x0A,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ0AZZ), fn10010A01, &ds18010A01},
    {{REV4(0x18, CI18010101,     0x0B,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ0BZZ), fn10010B01, &ds18010B01},
    {{REV4(0x18, CI18010101,     0x0C,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ0CZZ), fn10010C01, &ds18010C01},
    {{REV4(0x18, CI18010101,     0x0D,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ0DZZ), fn10010C01, &ds18010D01},
    {{REV4(0x18, CI18010101,     0x0E,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ0EZZ), NULL,       &ds18010E01},
    {{REV4(0x18, CI18010101,     0x0F,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ0FZZ), fn00000000, &ds18010F01},
    {{REV4(0x18, CI18010101,     0x10,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ10ZZ), fn00000000, &ds18011001},
    {{REV4(0x18, CI18010101,     0x11,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ11ZZ), fn00000000, &ds18011101},
    {{REV4(0x18, CI18010101,     0x12,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ12ZZ), fn00000000, &ds18011201},
    {{REV4(0x18, CI18010101,     0x13,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ13ZZ), fn10010A01, &ds18011301},
    {{REV4(0x18, CI18010101,     0x14,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ14ZZ), fn10010B01, &ds18011401},
    {{REV4(0x18, CI18010101,     0x15,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ15ZZ), fn10010C01, &ds18011501},
    {{REV4(0x18, CI18010101,     0x16,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ16ZZ), fn10010C01, &ds18011601},
    {{REV4(0x18, CI18010101,     0x17,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ17ZZ), NULL,       &ds18011701},
    {{REV4(0x18, CI18010101,     0x18,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ18ZZ), fn00000000, &ds18011801},
    {{REV4(0x18, CI18010101,     0x19,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ19ZZ), fn00000000, &ds18011901},
    {{REV4(0x18, CI18010101,     0x1A,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ1AZZ), fn00000000, &ds18011A01},
    {{REV4(0x18, CI18010101,     0x1B,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ1BZZ), fn00000000, &ds18011B01},
    {{REV4(0x18, CI18010101,     0x1C,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ1CZZ), fn10010A01, &ds18011C01},
    {{REV4(0x18, CI18010101,     0x1D,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ1DZZ), fn10010B01, &ds18011D01},
    {{REV4(0x18, CI18010101,     0x1E,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ1EZZ), fn10010C01, &ds18011E01},
    {{REV4(0x18, CI18010101,     0x1F,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ1FZZ), fn10010C01, &ds18011F01},
    {{REV4(0x18, CI18010101,     0x20,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ20ZZ), NULL,       &ds18012001},
    {{REV4(0x18, CI18010101,     0x21,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ21ZZ), NULL,       &ds18012101},
    {{REV4(0x18, CI18010101,     0x22,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ22ZZ), fn00000000, &ds18012201},
    {{REV4(0x18, CI18010101,     0x23,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ23ZZ), fn00000000, &ds18012301},
    {{REV4(0x18, CI18010101,     0x24,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ24ZZ), fn00000000, &ds18012401},
    {{REV4(0x18, CI18010101,     0x25,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ25ZZ), fn00000000, &ds18012501},
    {{REV4(0x18, CI18010101,     0x26,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ26ZZ), fn00000000, &ds18012601},
    {{REV4(0x18, CI18010101,     0x27,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ27ZZ), fn00000000, &ds18012701},
    {{REV4(0x18, CI18010101,     0x28,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ28ZZ), fn00000000, &ds18012801},
    {{REV4(0x18, CI18010101,     0x29,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ29ZZ), fn00000000, &ds18012901},
    {{REV4(0x18, CI18010101,     0x2A,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ2AZZ), fn00000000, &ds18012A01},
    {{REV4(0x18, CI18010101,     0x2B,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ2BZZ), fn00000000, &ds18012B01},
    {{REV4(0x18, CI18010101,     0x2C,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ2CZZ), fn00000000, &ds18012C01},
    {{REV4(0x18, CI18010101,     0x2D,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ2DZZ), fn00000000, &ds18012D01},
    {{REV4(0x18, CI18010101,     0x2E,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ2EZZ), fn00000000, &ds18012E01},
    {{REV4(0x18, CI18010101,     0x2F,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ2FZZ), fn00000000, &ds18012F01},
    {{REV4(0x18, CI18010101,     0x30,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ30ZZ), fn00000000, &ds18013001},
    {{REV4(0x18, CI18010101,     0x31,   BI18010101)}, 0x5200, SIZE_ADDR_OF(DF_sect6, df1801ZZ01[0]._[0].m_18ZZ31ZZ), fn00000000, &ds18013101},

     【过流事件记录】 
    {{REV4(0x19, CI19010001,     0x00,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee19010001                   ), fn10010001, NULL},
    {{REV4(0x19, CI19010001,     0x00,         0x02)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee19010002                   ), fn10010001, NULL},
    {{REV4(0x19, CI19010101,     0x01,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ01ZZ), NULL,       NULL},
    {{REV4(0x19, CI19010101,     0x02,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ02ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x03,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ03ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x04,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ04ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x05,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ05ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x06,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ06ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x07,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ07ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x08,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ08ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x09,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ09ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x0A,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ0AZZ), fn10010A01, NULL},
    {{REV4(0x19, CI19010101,     0x0B,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ0BZZ), fn10010B01, NULL},
    {{REV4(0x19, CI19010101,     0x0C,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ0CZZ), fn10010C01, NULL},
    {{REV4(0x19, CI19010101,     0x0D,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ0DZZ), fn10010C01, NULL},
    {{REV4(0x19, CI19010101,     0x0E,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ0EZZ), NULL,       NULL},
    {{REV4(0x19, CI19010101,     0x0F,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ0FZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x10,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ10ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x11,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ11ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x12,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ12ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x13,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ13ZZ), fn10010A01, NULL},
    {{REV4(0x19, CI19010101,     0x14,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ14ZZ), fn10010B01, NULL},
    {{REV4(0x19, CI19010101,     0x15,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ15ZZ), fn10010C01, NULL},
    {{REV4(0x19, CI19010101,     0x16,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ16ZZ), fn10010C01, NULL},
    {{REV4(0x19, CI19010101,     0x17,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ17ZZ), NULL,       NULL},
    {{REV4(0x19, CI19010101,     0x18,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ18ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x19,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ19ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x1A,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ1AZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x1B,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ1BZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x1C,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ1CZZ), fn10010A01, NULL},
    {{REV4(0x19, CI19010101,     0x1D,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ1DZZ), fn10010B01, NULL},
    {{REV4(0x19, CI19010101,     0x1E,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ1EZZ), fn10010C01, NULL},
    {{REV4(0x19, CI19010101,     0x1F,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ1FZZ), fn10010C01, NULL},
    {{REV4(0x19, CI19010101,     0x20,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ20ZZ), NULL,       NULL},
    {{REV4(0x19, CI19010101,     0x21,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ21ZZ), NULL,       NULL},
    {{REV4(0x19, CI19010101,     0x22,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ22ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x23,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ23ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x24,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ24ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x25,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ25ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x26,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ26ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x27,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ27ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x28,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ28ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x29,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ29ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x2A,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ2AZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x2B,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ2BZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x2C,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ2CZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x2D,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ2DZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x2E,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ2EZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x2F,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ2FZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x30,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ30ZZ), fn00000000, NULL},
    {{REV4(0x19, CI19010101,     0x31,   BI19010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1901ZZ01[0]._[0].m_18ZZ31ZZ), fn00000000, NULL},

     【断流事件记录】 
    {{REV4(0x1A, CI1A010001,     0x00,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1A010001                   ), fn10010001, NULL},
    {{REV4(0x1A, CI1A010001,     0x00,         0x02)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1A010002                   ), fn10010001, NULL},
    {{REV4(0x1A, CI1A010101,     0x01,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ01ZZ), NULL,       NULL},
    {{REV4(0x1A, CI1A010101,     0x02,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ02ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x03,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ03ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x04,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ04ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x05,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ05ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x06,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ06ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x07,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ07ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x08,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ08ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x09,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ09ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x0A,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ0AZZ), fn10010A01, NULL},
    {{REV4(0x1A, CI1A010101,     0x0B,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ0BZZ), fn10010B01, NULL},
    {{REV4(0x1A, CI1A010101,     0x0C,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ0CZZ), fn10010C01, NULL},
    {{REV4(0x1A, CI1A010101,     0x0D,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ0DZZ), fn10010C01, NULL},
    {{REV4(0x1A, CI1A010101,     0x0E,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ0EZZ), NULL,       NULL},
    {{REV4(0x1A, CI1A010101,     0x0F,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ0FZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x10,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ10ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x11,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ11ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x12,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ12ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x13,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ13ZZ), fn10010A01, NULL},
    {{REV4(0x1A, CI1A010101,     0x14,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ14ZZ), fn10010B01, NULL},
    {{REV4(0x1A, CI1A010101,     0x15,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ15ZZ), fn10010C01, NULL},
    {{REV4(0x1A, CI1A010101,     0x16,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ16ZZ), fn10010C01, NULL},
    {{REV4(0x1A, CI1A010101,     0x17,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ17ZZ), NULL,       NULL},
    {{REV4(0x1A, CI1A010101,     0x18,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ18ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x19,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ19ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x1A,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ1AZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x1B,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ1BZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x1C,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ1CZZ), fn10010A01, NULL},
    {{REV4(0x1A, CI1A010101,     0x1D,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ1DZZ), fn10010B01, NULL},
    {{REV4(0x1A, CI1A010101,     0x1E,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ1EZZ), fn10010C01, NULL},
    {{REV4(0x1A, CI1A010101,     0x1F,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ1FZZ), fn10010C01, NULL},
    {{REV4(0x1A, CI1A010101,     0x20,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ20ZZ), NULL,       NULL},
    {{REV4(0x1A, CI1A010101,     0x21,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ21ZZ), NULL,       NULL},
    {{REV4(0x1A, CI1A010101,     0x22,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ22ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x23,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ23ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x24,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ24ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x25,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ25ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x26,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ26ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x27,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ27ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x28,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ28ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x29,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ29ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x2A,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ2AZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x2B,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ2BZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x2C,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ2CZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x2D,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ2DZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x2E,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ2EZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x2F,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ2FZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x30,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ30ZZ), fn00000000, NULL},
    {{REV4(0x1A, CI1A010101,     0x31,   BI1A010101)}, 0x5200, SIZE_ADDR_OF(DF_sect7, df1A01ZZ01[0]._[0].m_18ZZ31ZZ), fn00000000, NULL},
    
    【有功功率反向事件记录】
    {{REV4(0x1B, CI1B010001,     0x00,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1B010001                   ), fn10010001,        NULL},
    {{REV4(0x1B, CI1B010001,     0x00,         0x02)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1B010002                   ), fn10010001,        NULL},
    {{REV4(0x1B, CI1B010101,     0x01,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140001ZZ), NULL,              NULL},
    {{REV4(0x1B, CI1B010101,     0x02,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140002ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x03,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140003ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x04,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140004ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x05,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140005ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x06,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140006ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x07,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140007ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x08,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140008ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x09,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140009ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x0A,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14000AZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x0B,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14000BZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x0C,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14000CZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x0D,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14000DZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x0E,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14000EZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x0F,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14000FZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x10,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140010ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x11,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140011ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x12,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140012ZZ), NULL,              NULL},
    {{REV4(0x1B, CI1B010101,     0x13,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140013ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x14,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140014ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x15,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140015ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x16,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140016ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x17,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140017ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x18,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140018ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x19,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140019ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x1A,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14001AZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x1B,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14001BZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x1C,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14001CZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x1D,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14001DZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x1E,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14001EZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x1F,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_14001FZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x20,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140020ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x21,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140021ZZ), fn00000000,        NULL},
    {{REV4(0x1B, CI1B010101,     0x22,   BI1B010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1B01ZZ01[0]._[0].m_140022ZZ), fn00000000,        NULL},

    【过载事件记录】
    {{REV4(0x1C, CI1C010001,     0x00,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1C010001                   ), fn10010001, NULL},
    {{REV4(0x1C, CI1C010001,     0x00,         0x02)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1C010002                   ), fn10010001, NULL},
    {{REV4(0x1C, CI1C010101,     0x01,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140001ZZ), NULL,       NULL},
    {{REV4(0x1C, CI1C010101,     0x02,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140002ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x03,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140003ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x04,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140004ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x05,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140005ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x06,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140006ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x07,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140007ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x08,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140008ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x09,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140009ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x0A,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14000AZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x0B,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14000BZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x0C,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14000CZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x0D,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14000DZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x0E,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14000EZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x0F,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14000FZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x10,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140010ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x11,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140011ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x12,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140012ZZ), NULL,       NULL},
    {{REV4(0x1C, CI1C010101,     0x13,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140013ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x14,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140014ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x15,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140015ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x16,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140016ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x17,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140017ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x18,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140018ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x19,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140019ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x1A,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14001AZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x1B,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14001BZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x1C,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14001CZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x1D,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14001DZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x1E,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14001EZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x1F,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_14001FZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x20,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140020ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x21,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140021ZZ), fn00000000, NULL},
    {{REV4(0x1C, CI1C010101,     0x22,   BI1C010101)}, 0x5200, SIZE_ADDR_OF(DF_sect8, df1C01ZZ01[0]._[0].m_140022ZZ), fn00000000, NULL},
*/    
#if defined(M_LOCAL) || defined(M_REMOTE)
    /* 【拉闸事件记录】 */
    {{REV4(0x1D,   0x00,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee1D000001                   ), fn10010001, &ds1D000001},
    {{REV4(0x1D,   0x00,         0x01,   BI1D000101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee1D00ZZ01[0].m_1D0001ZZ   ), NULL,       &ds1D000101},
    {{REV4(0x1D,   0x00,         0x02,   BI1D000101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee1D00ZZ01[0].m_1D0002ZZ   ), NULL,       &ds1D000201},
    {{REV4(0x1D,   0x00,         0x03,   BI1D000101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee1D00ZZ01[0].m_1D0003ZZ   ), fn00000000, &ds1D000301},
    {{REV4(0x1D,   0x00,         0x04,   BI1D000101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee1D00ZZ01[0].m_1D0004ZZ   ), fn00000000, &ds1D000401},
//    {{REV4(0x1D,   0x00,   CI1D000501,   BI1D000101)}, 0x3000, SIZE_ADDR_OF(EE_sect4, ee1D00ZZ01[0].m_1D0005ZZ   ), fn00000000, &ds1D000501},

    /* 【合闸事件记录】 */
    {{REV4(0x1E,   0x00,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect4, ee1E000001                 ), fn10010001, &ds1E000001},
    {{REV4(0x1E,   0x00,         0x01,   BI1E000101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee1E00ZZ01[0].m_1D0001ZZ   ), NULL,       &ds1E000101},
    {{REV4(0x1E,   0x00,         0x02,   BI1E000101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee1E00ZZ01[0].m_1D0002ZZ   ), NULL,       &ds1E000201},
    {{REV4(0x1E,   0x00,         0x03,   BI1E000101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee1E00ZZ01[0].m_1D0003ZZ   ), fn00000000, &ds1E000301},
    {{REV4(0x1E,   0x00,         0x04,   BI1E000101)}, 0x1000, SIZE_ADDR_OF(EE_sect4, ee1E00ZZ01[0].m_1D0004ZZ   ), fn00000000, &ds1E000401},
//    {{REV4(0x1E,   0x00,   CI1E000501,   BI1E000101)}, 0x3000, SIZE_ADDR_OF(EE_sect4, ee1E00ZZ01[0].m_1D0005ZZ   ), fn00000000, &ds1E000501},
#endif
/*
    【总功率因数超下限事件记录】
    {{REV4(0x1F,   0x00,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1F000001                   ), fn10010001, NULL},
    {{REV4(0x1F,   0x00,         0x00,         0x02)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee1F000002                   ), fn10010001, NULL},
    {{REV4(0x1F,   0x00,         0x01,   BI1F000101)}, 0x1000, SIZE_ADDR_OF(DF_sect9, df1F00ZZ01._[0].m_1F0001ZZ   ), NULL,       NULL},
    {{REV4(0x1F,   0x00,         0x02,   BI1F000101)}, 0x1000, SIZE_ADDR_OF(DF_sect9, df1F00ZZ01._[0].m_1F0002ZZ   ), fn00000000, NULL},
    {{REV4(0x1F,   0x00,         0x03,   BI1F000101)}, 0x1000, SIZE_ADDR_OF(DF_sect9, df1F00ZZ01._[0].m_1F0003ZZ   ), fn00000000, NULL},
    {{REV4(0x1F,   0x00,         0x04,   BI1F000101)}, 0x1000, SIZE_ADDR_OF(DF_sect9, df1F00ZZ01._[0].m_1F0004ZZ   ), fn00000000, NULL},
    {{REV4(0x1F,   0x00,         0x05,   BI1F000101)}, 0x1000, SIZE_ADDR_OF(DF_sect9, df1F00ZZ01._[0].m_1F0005ZZ   ), fn00000000, NULL},
    {{REV4(0x1F,   0x00,         0x06,   BI1F000101)}, 0x1000, SIZE_ADDR_OF(DF_sect9, df1F00ZZ01._[0].m_1F0006ZZ   ), NULL,       NULL},
    {{REV4(0x1F,   0x00,         0x07,   BI1F000101)}, 0x1000, SIZE_ADDR_OF(DF_sect9, df1F00ZZ01._[0].m_1F0007ZZ   ), fn00000000, NULL},
    {{REV4(0x1F,   0x00,         0x08,   BI1F000101)}, 0x1000, SIZE_ADDR_OF(DF_sect9, df1F00ZZ01._[0].m_1F0008ZZ   ), fn00000000, NULL},
    {{REV4(0x1F,   0x00,         0x09,   BI1F000101)}, 0x1000, SIZE_ADDR_OF(DF_sect9, df1F00ZZ01._[0].m_1F0009ZZ   ), fn00000000, NULL},
    {{REV4(0x1F,   0x00,         0x0A,   BI1F000101)}, 0x1000, SIZE_ADDR_OF(DF_sect9, df1F00ZZ01._[0].m_1F000AZZ   ), fn00000000, NULL},
    
    【A/B/C相功率因数超下限事件记录】
    {{REV4(0x1F,   CI1F010001,   0x00,         0x01)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1F010001      ),                    fn10010001, NULL},
    {{REV4(0x1F,   CI1F010001,   0x00,         0x02)}, 0x4000, SIZE_ADDR_OF(EE_sect5, ee1F010002      ),                    fn10010001, NULL},
    {{REV4(0x1F,   CI1F010101,   0x01,   BI1F010101)}, 0x5200, SIZE_ADDR_OF(DF_sect9, df1F01ZZ01[0]._[0].m_1F0001ZZ      ), NULL,       NULL},
    {{REV4(0x1F,   CI1F010101,   0x02,   BI1F010101)}, 0x5200, SIZE_ADDR_OF(DF_sect9, df1F01ZZ01[0]._[0].m_1F0002ZZ      ), fn00000000, NULL},
    {{REV4(0x1F,   CI1F010101,   0x03,   BI1F010101)}, 0x5200, SIZE_ADDR_OF(DF_sect9, df1F01ZZ01[0]._[0].m_1F0003ZZ      ), fn00000000, NULL},
    {{REV4(0x1F,   CI1F010101,   0x04,   BI1F010101)}, 0x5200, SIZE_ADDR_OF(DF_sect9, df1F01ZZ01[0]._[0].m_1F0004ZZ      ), fn00000000, NULL},
    {{REV4(0x1F,   CI1F010101,   0x05,   BI1F010101)}, 0x5200, SIZE_ADDR_OF(DF_sect9, df1F01ZZ01[0]._[0].m_1F0005ZZ      ), fn00000000, NULL},
    {{REV4(0x1F,   CI1F010101,   0x06,   BI1F010101)}, 0x5200, SIZE_ADDR_OF(DF_sect9, df1F01ZZ01[0]._[0].m_1F0006ZZ      ), NULL,       NULL},
    {{REV4(0x1F,   CI1F010101,   0x07,   BI1F010101)}, 0x5200, SIZE_ADDR_OF(DF_sect9, df1F01ZZ01[0]._[0].m_1F0007ZZ      ), fn00000000, NULL},
    {{REV4(0x1F,   CI1F010101,   0x08,   BI1F010101)}, 0x5200, SIZE_ADDR_OF(DF_sect9, df1F01ZZ01[0]._[0].m_1F0008ZZ      ), fn00000000, NULL},
    {{REV4(0x1F,   CI1F010101,   0x09,   BI1F010101)}, 0x5200, SIZE_ADDR_OF(DF_sect9, df1F01ZZ01[0]._[0].m_1F0009ZZ      ), fn00000000, NULL},
    {{REV4(0x1F,   CI1F010101,   0x0A,   BI1F010101)}, 0x5200, SIZE_ADDR_OF(DF_sect9, df1F01ZZ01[0]._[0].m_1F000AZZ      ), fn00000000, NULL},
    
    【电流严重不平衡事件记录】
    {{REV4(0x20,   0x00,         0x00,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee20000001      ), fn10010001, &ds17000001},
    {{REV4(0x20,   0x00,         0x00,         0x02)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee20000002      ), fn10010001, &ds17000002},
    {{REV4(0x20,   0x00,         0x01,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160001ZZ     ), NULL,       &ds17000101},
    {{REV4(0x20,   0x00,         0x01,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160001ZZ   ), NULL,       &ds17000102},
    {{REV4(0x20,   0x00,         0x02,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160002ZZ     ), fn00000000, &ds17000201},
    {{REV4(0x20,   0x00,         0x02,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160002ZZ   ), fn00000000, &ds17000202},
    {{REV4(0x20,   0x00,         0x03,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160003ZZ     ), fn00000000, &ds17000301},
    {{REV4(0x20,   0x00,         0x03,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160003ZZ   ), fn00000000, &ds17000302},
    {{REV4(0x20,   0x00,         0x04,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160004ZZ     ), fn00000000, &ds17000401},
    {{REV4(0x20,   0x00,         0x04,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160004ZZ   ), fn00000000, &ds17000402},
    {{REV4(0x20,   0x00,         0x05,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160005ZZ     ), fn00000000, &ds17000501},
    {{REV4(0x20,   0x00,         0x05,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160005ZZ   ), fn00000000, &ds17000502},
    {{REV4(0x20,   0x00,         0x06,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160006ZZ     ), fn00000000, &ds17000601},
    {{REV4(0x20,   0x00,         0x06,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160006ZZ   ), fn00000000, &ds17000602},
    {{REV4(0x20,   0x00,         0x07,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160007ZZ     ), fn00000000, &ds17000701},
    {{REV4(0x20,   0x00,         0x07,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160007ZZ   ), fn00000000, &ds17000702},
    {{REV4(0x20,   0x00,         0x08,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160008ZZ     ), fn00000000, &ds17000801},
    {{REV4(0x20,   0x00,         0x08,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160008ZZ   ), fn00000000, &ds17000802},
    {{REV4(0x20,   0x00,         0x09,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160009ZZ     ), fn00000000, &ds17000901},
    {{REV4(0x20,   0x00,         0x09,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160009ZZ   ), fn00000000, &ds17000902},
    {{REV4(0x20,   0x00,         0x0A,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16000AZZ     ), fn00000000, &ds17000A01},
    {{REV4(0x20,   0x00,         0x0A,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16000AZZ   ), fn00000000, &ds17000A02},
    {{REV4(0x20,   0x00,         0x0B,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16000BZZ     ), fn00000000, &ds17000B01},
    {{REV4(0x20,   0x00,         0x0B,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16000BZZ   ), fn00000000, &ds17000B02},
    {{REV4(0x20,   0x00,         0x0C,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16000CZZ     ), fn00000000, &ds17000C01},
    {{REV4(0x20,   0x00,         0x0C,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16000CZZ   ), fn00000000, &ds17000C02},
    {{REV4(0x20,   0x00,         0x0D,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16000DZZ     ), fn00000000, &ds17000D01},
    {{REV4(0x20,   0x00,         0x0D,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16000DZZ   ), fn00000000, &ds17000D02},
    {{REV4(0x20,   0x00,         0x0E,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16000EZZ     ), fn00000000, &ds17000E01},
    {{REV4(0x20,   0x00,         0x0E,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16000EZZ   ), fn00000000, &ds17000E02},
    {{REV4(0x20,   0x00,         0x0F,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16000FZZ     ), fn00000000, &ds17000F01},
    {{REV4(0x20,   0x00,         0x0F,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16000FZZ   ), fn00000000, &ds17000F02},
    {{REV4(0x20,   0x00,         0x10,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160010ZZ     ), fn00000000, &ds17001001},
    {{REV4(0x20,   0x00,         0x10,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160010ZZ   ), fn00000000, &ds17001002},
    {{REV4(0x20,   0x00,         0x11,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160011ZZ     ), fn00000000, &ds17001101},
    {{REV4(0x20,   0x00,         0x11,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160011ZZ   ), fn00000000, &ds17001102},
    {{REV4(0x20,   0x00,         0x12,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160012ZZ     ), fn16001201, &ds17001201},
    {{REV4(0x20,   0x00,         0x12,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160012ZZ   ), fn16001201, &ds17001202},
    {{REV4(0x20,   0x00,         0x13,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160013ZZ     ), NULL,       &ds17001301},
    {{REV4(0x20,   0x00,         0x13,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160013ZZ   ), NULL,       &ds17001302},
    {{REV4(0x20,   0x00,         0x14,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160014ZZ     ), fn00000000, &ds17001401},
    {{REV4(0x20,   0x00,         0x14,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160014ZZ   ), fn00000000, &ds17001402},
    {{REV4(0x20,   0x00,         0x15,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160015ZZ     ), fn00000000, &ds17001501},
    {{REV4(0x20,   0x00,         0x15,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160015ZZ   ), fn00000000, &ds17001502},
    {{REV4(0x20,   0x00,         0x16,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160016ZZ     ), fn00000000, &ds17001601},
    {{REV4(0x20,   0x00,         0x16,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160016ZZ   ), fn00000000, &ds17001602},
    {{REV4(0x20,   0x00,         0x17,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160017ZZ     ), fn00000000, &ds17001701},
    {{REV4(0x20,   0x00,         0x17,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160017ZZ   ), fn00000000, &ds17001702},
    {{REV4(0x20,   0x00,         0x18,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160018ZZ     ), fn00000000, &ds17001801},
    {{REV4(0x20,   0x00,         0x18,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160018ZZ   ), fn00000000, &ds17001802},
    {{REV4(0x20,   0x00,         0x19,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160019ZZ     ), fn00000000, &ds17001901},
    {{REV4(0x20,   0x00,         0x19,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160019ZZ   ), fn00000000, &ds17001902},
    {{REV4(0x20,   0x00,         0x1A,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16001AZZ     ), fn00000000, &ds17001A01},
    {{REV4(0x20,   0x00,         0x1A,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16001AZZ   ), fn00000000, &ds17001A02},
    {{REV4(0x20,   0x00,         0x1B,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16001BZZ     ), fn00000000, &ds17001B01},
    {{REV4(0x20,   0x00,         0x1B,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16001BZZ   ), fn00000000, &ds17001B02},
    {{REV4(0x20,   0x00,         0x1C,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16001CZZ     ), fn00000000, &ds17001C01},
    {{REV4(0x20,   0x00,         0x1C,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16001CZZ   ), fn00000000, &ds17001C02},
    {{REV4(0x20,   0x00,         0x1D,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16001DZZ     ), fn00000000, &ds17001D01},
    {{REV4(0x20,   0x00,         0x1D,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16001DZZ   ), fn00000000, &ds17001D02},
    {{REV4(0x20,   0x00,         0x1E,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16001EZZ     ), fn00000000, &ds17001E01},
    {{REV4(0x20,   0x00,         0x1E,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16001EZZ   ), fn00000000, &ds17001E02},
    {{REV4(0x20,   0x00,         0x1F,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_16001FZZ     ), fn00000000, &ds17001F01},
    {{REV4(0x20,   0x00,         0x1F,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_16001FZZ   ), fn00000000, &ds17001F02},
    {{REV4(0x20,   0x00,         0x20,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160020ZZ     ), fn00000000, &ds17002001},
    {{REV4(0x20,   0x00,         0x20,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160020ZZ   ), fn00000000, &ds17002002},
    {{REV4(0x20,   0x00,         0x21,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160021ZZ     ), fn00000000, &ds17002101},
    {{REV4(0x20,   0x00,         0x21,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160021ZZ   ), fn00000000, &ds17002102},
    {{REV4(0x20,   0x00,         0x22,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160022ZZ     ), fn00000000, &ds17002201},
    {{REV4(0x20,   0x00,         0x22,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160022ZZ   ), fn00000000, &ds17002202},
    {{REV4(0x20,   0x00,         0x23,         0x01)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee2000ZZ01[0].m_160023ZZ     ), fn00000000, &ds17002301},
    {{REV4(0x20,   0x00,         0x23,   BI20000102)}, 0x1000, SIZE_ADDR_OF(DF_sect6, df2000ZZ02._[0].m_160023ZZ   ), fn00000000, &ds17002302},

     潮流反向事件记录】
    {{REV4(0x21,       0x00,     0x00,         0x00)}, 0x0000, SIZE_ADDR_OF(EE_sect5, ee21000000), fn10010001, NULL},
    {{REV4(0x21,       0x00,     0x00,   BI21000001)}, 0x1000, SIZE_ADDR_OF(DF_sect8, df210000ZZ._[0]), NULL, NULL},
*/
    {{REV4(0x88,   0x88,         0x88,         0x88)}, 0x0800, sizeof(ro88888888), (uint32_t)&ro88888888, fn88888888, &ds88888888},
    {{REV4(0x99,   0x99,         0x99,         0x99)}, 0x0000, sizeof(ro04000105), (uint32_t)&ro04000105[0], fn99999999, &ds04000105},
    //{{REV4(0xF1,   0xF1,         0xF1,         0xF1)}, 0x0000, sizeof(fr.Meter_OPMode), (uint32_t)(&fr.Meter_OPMode), NULL, NULL},
    {{REV4(0xF1,   0xF1,         0xF1,         0xFE)}, 0x0434, SIZE_ADDR_OF(FR_sect0, first_verify_alignment),        NULL, NULL},
    {{REV4(0xF1,   0xF1,         0xF2,         0x00)}, 0x0400, SIZE_ADDR_OF(EE_sect9, ee_assertCnt),                  NULL, NULL},
    {{REV4(0xF1,   0xF1,         0xF2,         0x01)}, 0x0400, SIZE_ADDR_OF(EE_sect9, ee_assertRecord),               NULL, NULL},            
    {{REV4(0xF1,   0xF1,         0xF2,         0x02)}, 0x0400, SIZE_ADDR_OF(EE_sect9, ee_abnormalResetCnt),           NULL, NULL},  
    {{REV4(0xF1,   0xF1,         0xF2,         0x03)}, 0x0400, SIZE_ADDR_OF(EE_sect9, ee_useStackMax),                NULL, NULL},        
        
};

const int16_t DT_tableDim = dimof(DT_table);

