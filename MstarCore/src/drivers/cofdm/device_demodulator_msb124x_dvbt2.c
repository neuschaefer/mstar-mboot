//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be consTRUEd as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and consTRUEd in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
/**********************************************************************
Copyright (c) 2006-2009 MStar Semiconductor, Inc.
All rights reserved.
Unless otherwise stipulated in writing, any and all information contained
herein regardless in any format shall remain the sole proprietary of
MStar Semiconductor Inc. and be kept in strict confidence
(MStar Confidential Information) by the recipient.
Any unauthorized act including without limitation unauthorized disclosure,
copying, use, reproduction, sale, distribution, modification, disassembling,
reverse engineering and compiling of the contents of MStar Confidential
Information is unlawful and strictly prohibited. MStar hereby reserves the
rights to any and all damages, losses, costs and expenses resulting therefrom.
 **********************************************************************/

//#include <math.h>
#include "MsCommon.h"
#include "drvIIC.h"
#include "MsOS.h"
#include "Board.h"
//#include "drvTuner.h"
#include "drvDemod.h"
#include "drvGPIO.h"
//#include "SysBsp.h"

#define USE_UTOPIA
#define GPIO_FE_RST 10

#if(FRONTEND_DEMOD_TYPE == MSTAR_MSB1240_DEMOD)
#include "drvDMD_EXTERN_MSB124x.h"
#include "device_demodulator_msb124x_dvbt2.h"
extern MS_U8 MSB124X_LIB[];
#if(FRONTEND_TUNER_TYPE == TUNER_MXL603)
#include "MxL603_TunerApi.h"
#define MXL603_I2C_ADDR         0xC0
#endif
#if(FRONTEND_TUNER_TYPE == TUNER_MXL608)
//#include "MxL608_TunerApi.h"
#define MXL608_I2C_ADDR         0xC0
#endif

#define UNUSED(var)     (void)((var) = (var))
#define MSB124X_DEMOD_IIC 1
#define MSB124X_SPI_IIC 2
#define MSB124X_DEBUG_ON 1
#define MSB124X_Delayus   MsOS_DelayTaskUs
#define MDrv_Timer_GetTime0  OS_SYSTEM_TIME

#define PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C 0
#define LOAD_DSP_CODE_FROM_MAIN_CHIP_I2C 1
#define SDRAM_DATA_CHECK                 0
#define TIMING_VERIFICATION              0
#define MSB124X_USE_DVBT2_ROM       0
#define MSB124X_SELECT_IF_INPUT     1// 0  // 0:dvbt_I, 1:dvbs_I
#define MSB124X_SELECT_AGC_PAD_T    0  // 0: dvbs_agc pad 1:dvbt_agc pad

#define LOAD_CODE_I2C_BLOCK_NUM          0x80
#define SDRAM_BASE                       0x5000
#define SRAM_BASE                        0x8000

// MSB124X flash size: 1Mbits
#define MAX_MSB124X_LIB_LEN             131072
#define MSB124X_BOOT  0x01
#define MSB124X_DVBT2 0x02
#define MSB124X_DVBT  0x04
#define MSB124X_DVBC  0x08
#define MSB124X_ALL   0x0F

#define REG_MB_CNTL        0x0C80
#define REG_MB_ADDR_L    0x0C82
#define REG_MB_ADDR_H    0x0C84
#define REG_MB_DATA        0x0C86
#define REG_FSM_EN           0x0CB8

#define MSB124X_BOOT_START_ADDR     0x00000
#define MSB124X_BOOT_END_ADDR       0x00FFF
#define MSB124X_DVBT2_P1_START_ADDR 0x01000
#define MSB124X_DVBT2_P1_END_ADDR   0x08FFF
#define MSB124X_DVBT2_P2_START_ADDR 0x09000
#define MSB124X_DVBT2_P2_END_ADDR   0x0FFFF
#define MSB124X_DVBT_START_ADDR     0x10000
#define MSB124X_DVBT_END_ADDR       0x17FFF
#define MSB124X_DVBT2_ROM2_START_ADDR 0x20000
#define MSB124X_DVBT2_ROM2_END_ADDR   0x27FFF
#define MSB124X_DVBT2_ROM1_START_ADDR 0x28000
#define MSB124X_DVBT2_ROM1_END_ADDR   0x2FFFF

#define MSB124X_WINDOWS_BASE                0x100
#define MSB124X_BOOT_WINDOWS_OFFSET         MSB124X_WINDOWS_BASE
#define MSB124X_DVBT2_P2_WINDOWS_OFFSET    (MSB124X_WINDOWS_BASE + 0x08)
#define MSB124X_DVBT2_P1_WINDOWS_OFFSET    (MSB124X_DVBT2_P2_WINDOWS_OFFSET + 0x08)
#define MSB124X_DVBT_WINDOWS_OFFSET        (MSB124X_DVBT2_P1_WINDOWS_OFFSET + 0x08)
#define MSB124X_DVBT2_ROM1_WINDOWS_OFFSET        (MSB124X_DVBT_WINDOWS_OFFSET + 0x08)
#define MSB124X_DVBT2_ROM2_WINDOWS_OFFSET        (MSB124X_DVBT2_ROM1_WINDOWS_OFFSET + 0x08)

#define MSB124X_MAX_FLASH_ON_RETRY_NUM 3
#define COFDMDMD_MUTEX_TIMEOUT       (2000)

static float g_MSB124X_fSNR = 0.0;

static const S_DVBT2_SQI_CN_NORDIGP1 g_msb124x_dvbt2_sqi_cn_nordigp1[] =
{
    {_T2_QPSK, _T2_CR1Y2, 3.5},
    {_T2_QPSK, _T2_CR3Y5, 4.7},
    {_T2_QPSK, _T2_CR2Y3, 5.6},
    {_T2_QPSK, _T2_CR3Y4, 6.6},
    {_T2_QPSK, _T2_CR4Y5, 7.2},
    {_T2_QPSK, _T2_CR5Y6, 7.7},

    {_T2_16QAM, _T2_CR1Y2, 8.7},
    {_T2_16QAM, _T2_CR3Y5, 10.1},
    {_T2_16QAM, _T2_CR2Y3, 11.4},
    {_T2_16QAM, _T2_CR3Y4, 12.5},
    {_T2_16QAM, _T2_CR4Y5, 13.3},
    {_T2_16QAM, _T2_CR5Y6, 13.8},

    {_T2_64QAM, _T2_CR1Y2, 13.0},
    {_T2_64QAM, _T2_CR3Y5, 14.8},
    {_T2_64QAM, _T2_CR2Y3, 16.2},
    {_T2_64QAM, _T2_CR3Y4, 17.7},
    {_T2_64QAM, _T2_CR4Y5, 18.7},
    {_T2_64QAM, _T2_CR5Y6, 19.4},

    {_T2_256QAM, _T2_CR1Y2, 17.0},
    {_T2_256QAM, _T2_CR3Y5, 19.4},
    {_T2_256QAM, _T2_CR2Y3, 20.8},
    {_T2_256QAM, _T2_CR3Y4, 22.9},
    {_T2_256QAM, _T2_CR4Y5, 24.3},
    {_T2_256QAM, _T2_CR5Y6, 25.1},
    {_T2_QAM_UNKNOWN, _T2_CR_UNKNOWN, 0.0}
};

const float fDVBT2_SSI_Pref[][6] =
{
    { -95.7, -94.4, -93.6, -92.6, -92.0, -91.5},
    { -90.8, -89.1, -87.9, -86.7, -85.8, -85.2},
    { -86.9, -84.6, -83.2, -81.4, -80.3, -79.7},
    { -83.5, -80.4, -78.6, -76.0, -74.4, -73.3},
};

#if(TIMING_VERIFICATION == 1)
static MS_U32 tmm_1 = 0x00;
static MS_U32 tmm_2 = 0x00;
static MS_U32 tmm_3 = 0x00;
static MS_U32 tmm_4 = 0x00;
static MS_U32 tmm_5 = 0x00;
static MS_U32 tmm_6 = 0x00;
static MS_U32 tmm_7 = 0x00;
static MS_U32 tmm_8 = 0x00;
static MS_U32 tmm_9 = 0x00;
static MS_U32 tmm_10 = 0x00;
static MS_U32 tmm_11 = 0x00;
static MS_U32 tmm_12 = 0x00;
static MS_U32 tmm_13 = 0x00;
static MS_U32 tmm_14 = 0x00;
static MS_U32 tmm_15 = 0x00;
static MS_U32 tmm_16 = 0x00;
static MS_U32 tmm_17 = 0x00;
static MS_U32 tmm_18 = 0x00;
static MS_U32 tmm_19 = 0x00;
static MS_U32 tmm_20 = 0x00;

#define GIVE_ME_TIME MsOS_GetSystemTime();
#endif

#define MSB124X_DEBUG   0

#if MSB124X_DEBUG
#define PRINTE(p)       printf p
#else
#define PRINTE(p)
#endif

//---------------------------------- for DVB-T
//operation

//configure
#define FS_L                    0x80
#define FS_H                    0x70
#define BW                      0x03
#define DVBT_IF_INV_PWM_OUT_EN  0x00

#if((FRONTEND_TUNER_TYPE == TUNER_R836)||(FRONTEND_TUNER_TYPE == TUNER_MXL608))
#undef FRONTEND_DEMOD_IQ_SWAP
#define FRONTEND_DEMOD_IQ_SWAP   1
#endif

#define IQ_SWAP                  FRONTEND_DEMOD_IQ_SWAP
#if TS_PARALLEL_OUTPUT
#define SERIAL_TS               0x00
#else
#define SERIAL_TS               0x01
#endif
#define TS_CLK_SEL           0x00
#define TS_DATA_SWAP       0x00
#define TS_OUT_INV             TS_CLK_INV

// FC: FC = FS = 5000 = 0x1388     (5.00MHz IF)
#if(FRONTEND_TUNER_TYPE == TUNER_RT820T)
#define FC_L           0xDA
#define FC_H           0x11  //7M AND 8M     IF=4.57MHZ

#define FC_L_6M        0xF2
#define FC_H_6M        0x0D    //6M     IF= 3.57MHZ
#else
#define FC_L           0x88    //5M
#define FC_H           0x13
#endif


//configure
//------------------------------------------------ for DVB-T2
// BW: 0->1.7M, 1->5M, 2->6M, 3->7M, 4->8M, 5->10M
#define T2_BW_VAL               0x04
#if TS_PARALLEL_OUTPUT
#define T2_TS_SERIAL_VAL       0x00
#else
#define T2_TS_SERIAL_VAL       0x01
#endif
#define T2_TS_OUT_INV_VAL      0x01
#define T2_TS_DATA_SWAP_VAL    0x00
#define T2_TS_CLK_RATE_VAL      0x03
#define T2_TS_ERR_POL_VAL      0x00
#define T2_IF_AGC_INV_PWM_EN_VAL    0x00
#define T2_LITE_VAL    0x00  // 0: T2-base, 1: T2-lite

// FC: FC = FS = 5000 = 0x1388     (5.00MHz IF)
#if(FRONTEND_TUNER_TYPE == TUNER_RT820T)
#define T2_FC_L_VAL            0xDA
#define T2_FC_H_VAL            0x11  //7M and 8M  IF=4.57MHZ

#define T2_FC_L_VAL_6M          0xF2
#define T2_FC_H_VAL_6M          0x0D    //6M  IF=3.57MHZ
#else
#define T2_FC_L_VAL            0x88    //5M
#define T2_FC_H_VAL            0x13
#endif

#define CUSTOMER_TABLE  1
#if (CUSTOMER_TABLE == 0)
static MS_U8 *MSB1236c_DVBT2_DSPREG_TABLE = NULL;
static MS_U8 *MSB1236c_DVBT_DSPREG_TABLE = NULL;
#else
static MS_U8 MSB1236c_DVBT_DSPREG_TABLE[] =
{
    BW,  FC_L,  FC_H,  SERIAL_TS,  TS_CLK_SEL,  TS_OUT_INV,  TS_DATA_SWAP,
    IQ_SWAP,  DVBT_IF_INV_PWM_OUT_EN
};
static MS_U8 MSB1236c_DVBT2_DSPREG_TABLE[] =
{
    T2_BW_VAL, T2_FC_L_VAL, T2_FC_H_VAL,  T2_TS_SERIAL_VAL, T2_TS_CLK_RATE_VAL,
    T2_TS_OUT_INV_VAL, T2_TS_DATA_SWAP_VAL, T2_TS_ERR_POL_VAL
};
#endif

typedef struct
{
    MS_BOOL     bInited;
    MS_BOOL    bOpen;
    EN_DEVICE_DEMOD_TYPE  enDemodType;
    MS_S32     s32_MSB124X_Mutex;
    MS_U8       PlpIDList[256];
    MS_U8       u8sramCode;
    MS_U8     *pMSB124X_RegDVBT;
    MS_U32     u32CurrFreq;
    MS_U8       u8CurrPlpID;
    MS_U8       u8CurrScanType;
    DEMOD_EN_TER_BW_MODE     enCurrBW;
    DEMOD_EN_TER_BW_MODE     enTuneBw;
    MS_U8       PlpIDSize;
    MS_U32     u32ChkScanTimeStart;
    MS_BOOL   bFECLock;
    MS_U8       u8ScanStatus;
} MDvr_CofdmDmd_CONFIG;
MDvr_CofdmDmd_CONFIG MSB124X;

const S_RFAGC_SSI RFAGC_SSI[] =
{
    { -19.40,    0x1B},
    { -20.40,    0x1C},
    { -21.40,    0x1D},
    { -22.40,    0x1E},
    { -23.40,    0x1F},
    { -24.40,    0x20},
    { -25.20,    0x21},
    { -26.60,    0x22},
    { -28.00,    0x23},
    { -29.20,    0x24},
    { -31.50,    0x25},
    { -32.75,    0x26},
    { -34.00,    0x27},
    { -35.25,    0x28},
    { -36.75,    0x29},
    { -38.50,    0x2a},
    { -40.00,    0x2b},
    { -42.00,    0x2c},
    { -43.50,    0x2d},
    { -44.80,    0x2e},
    { -46.20,    0x2f},
    { -47.40,    0x30},
    { -48.00,    0x31},
    { -48.40,    0x32},
    { -49.00,    0x33},
    { -99.00,    0x3f},
};

const S_IFAGC_SSI IFAGC_SSI[] =
{
    { -48,   0x3A},
    { -49,   0x3B},
    { -50,   0x3C},
    { -51,   0x3E},
    { -52,   0x40},
    { -53,   0x43},
    { -54,   0x45},
    { -55,   0x47},
    { -56,   0x49},
    { -57,   0x4C},
    { -58,   0x4f},
    { -59,   0x51},
    { -60,   0x54},
    { -61,   0x56},
    { -62,   0x59},
    { -63,   0x5C},
    { -64,   0x5F},
    { -65,   0x62},
    { -66,   0x65},
    { -67,   0x69},
    { -68,   0x6E},
    { -69,   0x73},
    { -70,   0x78},
    { -71,   0x7F},
    { -72,   0x85},
    { -73,   0x8b},
    { -74,   0x9c},
    { -85,   0xc0},
    { -99,   0xFF},
};

const S_SSI_PREF SsiPref[] =
{
    {_QPSK_1,  _CR1Y2_1, -93.0},
    {_QPSK_1,  _CR2Y3_1, -91.0},
    {_QPSK_1,  _CR3Y4_1, -90.0},
    {_QPSK_1,  _CR5Y6_1, -89.0},
    {_QPSK_1,  _CR7Y8_1, -88.0},

    {_16QAM_1, _CR1Y2_1, -87.0},
    {_16QAM_1, _CR2Y3_1, -85.0},
    {_16QAM_1, _CR3Y4_1, -84.0},
    {_16QAM_1, _CR5Y6_1, -83.0},
    {_16QAM_1, _CR7Y8_1, -82.0},

    {_64QAM_1, _CR1Y2_1, -82.0},
    {_64QAM_1, _CR2Y3_1, -80.0},
    {_64QAM_1, _CR3Y4_1, -78.0},
    {_64QAM_1, _CR5Y6_1, -77.0},
    {_64QAM_1, _CR7Y8_1, -76.0},
};

#if(TIMING_VERIFICATION == 1)
static void show_timer(void)
{
    printf("***************************\n");
    printf("[tmm1]t2-t1 = %ld (%ld - %ld)\n", tmm_2 - tmm_1, tmm_2, tmm_1);
    printf("[tmm2]t4-t3 = %ld (%ld - %ld)\n", tmm_4 - tmm_3, tmm_4, tmm_3);
    printf("[tmm3]t6-t5 = %ld (%ld - %ld)\n", tmm_6 - tmm_5, tmm_6, tmm_5);
    printf("[tmm4]t8-t7 = %ld (%ld - %ld)\n", tmm_8 - tmm_7, tmm_8, tmm_7);
    printf("[tmm5]t10-t9 = %ld (%ld - %ld)\n", tmm_10 - tmm_9, tmm_10, tmm_9);
    printf("[tmm6]t12-t11 = %ld (%ld - %ld)\n", tmm_12 - tmm_11, tmm_12, tmm_11);
    printf("[tmm7]t14-t13 = %ld (%ld - %ld)\n", tmm_14 - tmm_13, tmm_14, tmm_13);
    printf("[tmm8]t16-t15 = %ld (%ld - %ld)\n", tmm_16 - tmm_15, tmm_16, tmm_15);
    printf("[tmm9]t18-t17 = %ld (%ld - %ld)\n", tmm_18 - tmm_17, tmm_18, tmm_17);
    printf("[tmm10]t20-t19 = %ld (%ld - %ld)\n", tmm_20 - tmm_19, tmm_20, tmm_19);
    printf("[tmm11]lock_time# = %ld (%ld - %ld)\n", tmm_14 - u32StartTime, tmm_14, u32StartTime);
    printf("[tmm12]lock-setf = %ld (%ld - %ld)\n", tmm_14 - tmm_11, tmm_14, tmm_11);
    printf("[tmm13]lock-loaddsp = %ld (%ld - %ld)\n", tmm_14 - tmm_9, tmm_14, tmm_9);
    printf("***************************\n");
}
#endif

static void _msb124x_hw_reset(void)
{
#ifdef GPIO_DEMOD_RST
    int rst_pin = GPIO_DEMOD_RST;

    mdrv_gpio_set_high(rst_pin);
    MsOS_DelayTask(100);
    mdrv_gpio_set_low(rst_pin);
    MsOS_DelayTask(200);
    mdrv_gpio_set_high(rst_pin);
    MsOS_DelayTask(100);
    MDrv_DMD_MSB124X_Exit();
#endif
}

static void MApi_Demod_HWReset(void)
{
#if 0
    mdrv_gpio_set_high(GPIO_FE_RST);
    MsOS_DelayTask(100);
    mdrv_gpio_set_low(GPIO_FE_RST);
    MsOS_DelayTask(200);
    mdrv_gpio_set_high(GPIO_FE_RST);
    MsOS_DelayTask(100);
#else
    mdrv_gpio_set_high(119);
    MsOS_DelayTask(100);
    mdrv_gpio_set_low(119);
    MsOS_DelayTask(200);
    mdrv_gpio_set_high(119);
    MsOS_DelayTask(100);
#endif
}

/*================================================
==                       IIC write/read interface
=================================================*/
MS_BOOL MSB124X_WriteBytes_demod(MS_U8 u8AddrSize, MS_U8 *pu8Addr, MS_U16 u16Size, MS_U8 *pu8Data)
{
    MS_BOOL bRet = 0;
    bRet = MDrv_IIC_Write(DEMOD_DYNAMIC_SLAVE_ID_1, pu8Addr, u8AddrSize, pu8Data, u16Size);
    if (FALSE == bRet)
    {
        printf("Demod IIC write error\n");
    }
    return bRet;
}

MS_BOOL MSB124X_ReadBytes_demod(MS_U8 u8AddrSize, MS_U8 *pu8Addr, MS_U16 u16Size, MS_U8 *pu8Data)
{
    MS_BOOL bRet = 0;

    bRet = MDrv_IIC_Read(DEMOD_DYNAMIC_SLAVE_ID_1, pu8Addr, u8AddrSize, pu8Data, u16Size);
    if (FALSE == bRet)
    {
        printf("Demod IIC read error\n");
    }
    return bRet;
}

MS_BOOL MSB124X_WriteBytes_spi(MS_U8 u8AddrSize, MS_U8 *pu8Addr, MS_U16 u16Size, MS_U8 *pu8Data)
{
    MS_BOOL bRet = 0;
    bRet = MDrv_IIC_Write(DEMOD_DYNAMIC_SLAVE_ID_2, pu8Addr, u8AddrSize, pu8Data, u16Size);
    if (FALSE == bRet)
    {
        printf("Demod IIC write spi error\n");
    }
    return bRet;
}

MS_BOOL MSB124X_ReadBytes_spi(MS_U8 u8AddrSize, MS_U8 *pu8Addr, MS_U16 u16Size, MS_U8 *pu8Data)
{
    MS_BOOL bRet = 0;
    bRet = MDrv_IIC_Read(DEMOD_DYNAMIC_SLAVE_ID_2, pu8Addr, u8AddrSize, pu8Data, u16Size);
    if (FALSE == bRet)
    {
        printf("Demod IIC read spi error\n");
    }
    return bRet;
}

typedef struct
{
    MS_BOOL(*WriteBytes)(MS_U8 u8AddrSize, MS_U8 *pu8Addr, MS_U16 u16Size, MS_U8 *pu8Data);
    MS_BOOL(*ReadBytes)(MS_U8 u8AddrSize, MS_U8 *pu8Addr, MS_U16 u16Size, MS_U8 *pu8Data);
} mapi_i2c;

mapi_i2c DemodI2Chandler, SpiI2Chandler;
mapi_i2c* mapi_i2c_GetI2C_Dev(MS_U32 u32gID)
{
    mapi_i2c *handler;
    switch (u32gID)
    {
        default:
            printf("iic device not supported\n");
        case MSB124X_DEMOD_IIC:
            handler = &DemodI2Chandler;
            handler->WriteBytes = MSB124X_WriteBytes_demod;
            handler->ReadBytes = MSB124X_ReadBytes_demod;
            break;
        case MSB124X_SPI_IIC:
            handler = &SpiI2Chandler;
            handler->WriteBytes = MSB124X_WriteBytes_spi;
            handler->ReadBytes = MSB124X_ReadBytes_spi;
            break;
    }
    return handler;
}

static MS_BOOL msb124x_I2C_Access(eDMD_MSB124X_DemodI2CSlaveID eSlaveID, eDMD_MSB124X_DemodI2CMethod eMethod, MS_U8 u8AddrSize, MS_U8 *pu8Addr, MS_U16 u16Size, MS_U8 *pu8Data)
{
    MS_BOOL bRet = TRUE;
    mapi_i2c *i2c_iptr = mapi_i2c_GetI2C_Dev(MSB124X_DEMOD_IIC);
    switch (eSlaveID)
    {
        case E_DMD_MSB124X_DEMOD_I2C_DYNAMIC_SLAVE_ID_2:
            i2c_iptr = mapi_i2c_GetI2C_Dev(MSB124X_SPI_IIC);
            break;
        case E_DMD_MSB124X_DEMOD_I2C_DYNAMIC_SLAVE_ID_1:
        default:
            i2c_iptr = mapi_i2c_GetI2C_Dev(MSB124X_DEMOD_IIC);
            break;
    }

    if (i2c_iptr != NULL)
    {
        switch (eMethod)
        {
            case E_DMD_MSB124X_DEMOD_I2C_WRITE_BYTES:
                bRet = i2c_iptr->WriteBytes(u8AddrSize, pu8Addr, u16Size, pu8Data);
                break;
            case E_DMD_MSB124X_DEMOD_I2C_READ_BYTES:
                bRet = i2c_iptr->ReadBytes(u8AddrSize, pu8Addr, u16Size, pu8Data);
            default:
                break;
        }
    }
    else
    {
        bRet = FALSE;
    }

    return bRet;
}

#if (SUPPORT_MSPI_LOAD_CODE == 1)
static void msb124x_SPIPAD_En(MS_BOOL bOnOff)
{
    if (bOnOff)
    {
        SYSBSP_ENABLE_MSPI_PAD();
    }
    else
    {
        SYSBSP_DISABLE_MSPI_PAD();
    }
}
#endif

/*================================================
==               demod  msb124x  write/read interface
=================================================*/
MS_BOOL MSB124X_WriteReg(MS_U16 u16Addr, MS_U8 u8Data)
{
    return MDrv_DMD_MSB124X_SetReg(u16Addr, u8Data);
}

MS_BOOL MSB124X_WriteRegs(MS_U16 u16Addr, MS_U8* u8pData, MS_U16 data_size)
{
    return MDrv_DMD_MSB124X_SetRegs(u16Addr, u8pData, data_size);
}

MS_BOOL MSB124X_WriteReg2bytes(MS_U16 u16Addr, MS_U16 u16Data)
{
    return MDrv_DMD_MSB124X_SetReg2Bytes(u16Addr, u16Data);
}

MS_BOOL MSB124X_ReadReg(MS_U16 u16Addr, MS_U8 *pu8Data)
{
    return MDrv_DMD_MSB124X_GetReg(u16Addr, pu8Data);
}

MS_BOOL  MSB124X_WriteDspReg(MS_U16 u16Addr, MS_U8 u8Data)
{
    return MDrv_DMD_MSB124X_SetDSPReg(u16Addr, u8Data);
}

MS_BOOL MSB124X_ReadDspReg(MS_U16 u16Addr, MS_U8* pData)
{
    return MDrv_DMD_MSB124X_GetDSPReg(u16Addr, pData);
}


/*================================================
==               demod  MSB124X  base interface
=================================================*/
#if (MSB124X_DEBUG_ON == 1)
void MSB124X_Show_Version(void)
{

    MS_U8  reg = 0;
    MS_U16 ver0 = 0;
    MS_U8  ver1 = 0;

    MSB124X_ReadDspReg(E_T2_FW_VER_0, &reg);
    ver0 = reg;
    MSB124X_ReadDspReg(E_T2_FW_VER_1, &reg);
    ver0 = (ver0 << 8) | reg;
    MSB124X_ReadDspReg(E_T2_FW_VER_2, &reg);
    ver1 = reg;

    printf("\n[MSB124X]ver0 = 0x%x, ver1 = 0x%x\n", ver0, ver1);

    return;
}
#endif

MS_BOOL MSB124X_I2C_CH_Reset(MS_U8 ch_num)
{
    MS_BOOL bRet = TRUE;
    MS_U8     data[5] = {0x53, 0x45, 0x52, 0x44, 0x42};
    static MS_BOOL DemodRest = TRUE;

    // ch_num, 0: for MIU access, 3: for RIU access
    PRINTE(("[MSB124X][beg]MSB124X_I2C_CH_Reset, CH=0x%x\n", ch_num));
    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB124X_DEMOD_IIC);
    if (iptr == NULL)
    {
        return FALSE;
    }

    if (DemodRest)
    {
        DemodRest = FALSE;
        // 8'hb2(SRID)->8,h53(PWD1)->8,h45(PWD2)->8,h52(PWD3)->8,h44(PWD4)->8,h42(PWD5)
        data[0] = 0x53;
        // Don't check Ack because this passward only ack one time for the first time.
        bRet &= iptr->WriteBytes(0, NULL, 5, data);
    }

    // 8'hb2(SRID)->8,h71(CMD)  //TV.n_iic_
    data[0] = 0x71;
    bRet &= iptr->WriteBytes(0, NULL, 1, data);

    // 8'hb2(SRID)->8,h81(CMD)  //TV.n_iic_sel_b0
    data[0] = ((ch_num & 0x01) != 0) ? 0x81 : 0x80;
    bRet &= iptr->WriteBytes(0, NULL, 1, data);

    // 8'hb2(SRID)->8,h83(CMD)  //TV.n_iic_sel_b1
    data[0] = ((ch_num & 0x02) != 0) ? 0x83 : 0x82;
    bRet &= iptr->WriteBytes(0, NULL, 1, data);

    // 8'hb2(SRID)->8,h84(CMD)  //TV.n_iic_sel_b2
    data[0] = ((ch_num & 0x04) != 0) ? 0x85 : 0x84;
    bRet &= iptr->WriteBytes(0, NULL, 1, data);

    // 8'hb2(SRID)->8,h53(CMD)  //TV.n_iic_ad_byte_en2, 32bit read/write
    data[0] = 0x53;
    bRet &= iptr->WriteBytes(0, NULL, 1, data);

    // 8'hb2(SRID)->8,h7f(CMD)  //TV.n_iic_sel_use_cfg
    data[0] = 0x7f;
    bRet &= iptr->WriteBytes(0, NULL, 1, data);

    /*
    // 8'hb2(SRID)->8,h35(CMD)  //TV.n_iic_use
    data[0] = 0x35;
    iptr->WriteBytes(0, NULL, 1, data);

    // 8'hb2(SRID)->8,h71(CMD)  //TV.n_iic_Re-shape
    data[0] = 0x71;
    iptr->WriteBytes(0, NULL, 1, data);
    */
    PRINTE(("[MSB124X][end]MSB124X_I2C_CH_Reset, CH=0x%x\n", ch_num));
    return bRet;
}

// 144 ms roughly
MS_BOOL MSB124X_HW_init(void)
{
    PRINTE(("%s(),%d\n", __FUNCTION__, __LINE__));

    MS_BOOL bRet = TRUE;
    MS_U8 u8_tmp = 0;
    MS_U8 u8_timeout = 0;

    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !\n"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("pMSB124X have not inited !!!\n"));
        return FALSE;
    }

    MsOS_ObtainMutex(pMSB124X->s32_MSB124X_Mutex, MSOS_WAIT_FOREVER);

    PRINTE(("[start]MSB124X_HW_init\n"));

#if(TIMING_VERIFICATION == 1)
    tmm_1 = GIVE_ME_TIME;
#endif

    // 10us delay
    MSB124X_Delayus(10);

    // ASIC INIT for WDM DVB-T2
    // -------------------------------------------------------------------
    // Initialize DMD_ANA_MISC
    // -------------------------------------------------------------------
    // [0]	reg_tst_ldo25i
    // [1]	reg_tst_ldo25q
    // [5:4]	reg_tst_ldo25i_selfb
    // [7:6]	reg_tst_ldo25q_selfb
    // [8]	reg_pd_dm2p5ldoi = 1'b0
    // [9]	reg_pd_dm2p5ldoq = 1'b0
    bRet &= MSB124X_WriteReg2bytes(0x0A00+(0x4f)*2, 0x0000);

    // [0]	reg_tst_ldo11_clk
    // [1]	reg_tst_ldo26
    // [2]	reg_tst_ldo11_cmp
    // [3]	reg_pd_dm1p1ldo_clk = 1'b0
    // [4]	reg_pd_dm1p1ldo_cmp = 1'b0
    // [6]	reg_tst_ldo26_selfb
    // [7]	reg_pd_dm2p6ldo = 1'b0
    // [9:8]	reg_tst_ldo11_cmp_selfb
    // [11:10]	reg_tst_ldo11_clk_selfb
    bRet &= MSB124X_WriteReg2bytes(0x0A00+(0x4e)*2, 0x0000);

    // [1:0]	reg_mpll_loop_div_first       feedback divider 00:div by 1 01:div by 2 10:div by 4 11:div by 8
    // [15:8]	reg_mpll_loop_div_second      feedback divider, div by binary data number
    // `RIU_W((`RIUBASE_ADCPLL>>1)+7'h33, 2'b11, 16'h1201);  // Loop divider ; VCO = 24*(2^2)*9 = 864
    bRet &= MSB124X_WriteReg2bytes(0x0A00+(0x33)*2, 0x1201);

    // [2:0]	reg_mpll_ictrl		    charge pump current control
    // [3]	reg_mpll_in_sel		    1.8V or 3.3V reference clock domain select (1'b0=0==>3.3 V reference clock domain)
    // [4]	reg_mpll_xtal2adc_sel	    select the XTAL clock bypass to MPLL_ADC_CLK
    // [5]	reg_mpll_xtal2next_pll_sel  crystal clock bypass to next PLL select
    // [6]	reg_mpll_vco_offset	    set VCO initial offset frequency
    // [7]	reg_mpll_pd		    gated reference clock and power down PLL analog_3v: 1=power down
    // [8]	reg_xtal_en		    XTAL enable register; 1: enable
    // [10:9]	reg_xtal_sel		    XTAL driven strength select.
    // [11]  	reg_mpll_porst		    MPLL input  power on reset, connect to reg as MPLL_RESET
    // [12]  	reg_mpll_reset		    PLL software reset; 1:reset
    // [13]  	reg_pd_dmpll_clk	    XTAL to MPLL clock reference power down
    // [14]  	reg_pd_3p3_1		    XTAL to CLK_24M_3P3_1 power down
    // [15]  	reg_pd_3p3_2		    XTAL to CLK_24M_3P3_2 power down
    // `RIU_W((`RIUBASE_ADCPLL>>1)+7'h35, 2'b11, 16'h1803); // MPLL reset
    bRet &= MSB124X_WriteReg2bytes(0x0A00+(0x35)*2, 0x1803);
    // `RIU_W((`RIUBASE_ADCPLL>>1)+7'h35, 2'b11, 16'h0003); // release MPLl reset
    bRet &= MSB124X_WriteReg2bytes(0x0A00+(0x35)*2, 0x0003);

  //  // [15:0]	reg_mpll_test
  //  // [14]	mpll reset
  //  `RIU_W((`RIUBASE_ADCPLL>>1)+7'h34, 2'b11, 16'h4000);
  //  `RIU_W((`RIUBASE_ADCPLL>>1)+7'h34, 2'b11, 16'h0000);

    // [0]	reg_mpll_clk_dp_pd	dummy
    // [1]	reg_adc_clk_pd		ADC output clock power down
    // [2]	reg_mpll_div2_pd	MPLL_DIV2 power down
    // [3]	reg_mpll_div3_pd	MPLL_DIV3 power down
    // [4]	reg_mpll_div4_pd	MPLL_DIV4 power down
    // [5]	reg_mpll_div8_pd	MPLL_DIV8 power down
    // [6]	reg_mpll_div10_pd	MPLL_DIV10 power down
    // [13:8]  reg_mpll_adc_div_sel	select the ADC clock divide ratio,ADC clk=XTAL_IN * (LOOP_DIV_FIRST*LOOP_DIV_SECOND)/div_ratio

    // `ifdef SIM_ADC_96MHZ
    //      `RIU_W((`RIUBASE_ADCPLL>>1)+7'h30, 2'b11, 16'h0900);  // divide ADC clock to 48Mhz = 24*36/9
    //
    //
    // `elsif SIM_ADC_48MHZ
    //
    //      `RIU_W((`RIUBASE_ADCPLL>>1)+7'h30, 2'b11, 16'h1200);  // divide ADC clock to 48Mhz = 24*36/18
    //
    // `elsif SIM_ADC_45P47MHZ
    //
    //      `RIU_W((`RIUBASE_ADCPLL>>1)+7'h30, 2'b11, 16'h1300);  // divide ADC clock to 45.47Mhz = 24*36/19
    //
    // `elsif SIM_ADC_28P8MHZ
    //
    //      `RIU_W((`RIUBASE_ADCPLL>>1)+7'h30, 2'b11, 16'h1e00);  // divide ADC clock to 28.8Mhz = 24*36/30
    //
    // `elsif SIM_ADC_24P7MHZ
    //
    //      `RIU_W((`RIUBASE_ADCPLL>>1)+7'h30, 2'b11, 16'h2300);  // divide ADC clock to 28.8Mhz = 24*36/35
    //
    // `elsif SIM_ADC_24MHZ
    //
          // `RIU_W((`RIUBASE_ADCPLL>>1)+7'h30, 2'b11, 16'h2400);  // divide ADC clock to 24Mhz = 24*36/36
          bRet &= MSB124X_WriteReg2bytes(0x0A00+(0x30)*2, 0x2400);
    //
    // `elsif SIM_ADC_20P48MHZ
    //
    //      `RIU_W((`RIUBASE_ADCPLL>>1)+7'h30, 2'b11, 16'h2a00);  // divide ADC clock to 20.48Mhz = 24*36/42
    //
    // `else
    //
    //    `RIU_W((`RIUBASE_ADCPLL>>1)+7'h30, 2'b11, 16'h1600);  // divide ADC clock to 39.27Mhz = 24*36/22
    //
    // `endif


    // $display("--------------------------------------");
    // $display("Initialize ADC I/Q");
    // $display("--------------------------------------");

    // [0]	Q channel ADC power down
    // [1]	I channel ADC power down
    // [2]	Q channel clamp enable. 0:enable, 1:disable
    // [3]	I channel clamp enable. 0:enable, 1:disable
    // [6:4]    I channel input mux control;
    //		3'b000=I channel ADC calibration mode input
    //	    	3'b001=VIF signal from VIFPGA
    //	    	3'b100=DVB or ATSC mode input from PAD_I(Q)P(M)
    //	    	all the other combination are only for test mode, don't use without understanding.
    // [10:8]   Q channel input mux control;
    //		3'b000=Q channel ADC calibration mode input
    //	    	3'b001=VIF signal from VIFPGA 3'b010 = SSIF signal from PAD_SIFP(M)
    //	    	3'b100=DVB or ATSC mode input from PAD_I(Q)P(M)
    //	    	all the other combination are only for test mode, don't use without understanding.
    // [12]	ADC I,Q swap enable; 1: swap
    // [13]	ADC clock out select; 1: ADC_CLKQ
    // [14]	ADC linear calibration bypass enable; 1:enable
    // [15]	ADC internal 1.2v regulator control always 0 in T3
        // `RIU_W((`RIUBASE_ADCPLL>>1)+7'h01, 2'b11, 16'h0440); // Set IMUXS QMUXS
        bRet &= MSB124X_WriteReg2bytes(0x0A00+(0x01)*2, 0x0440);

    // [2:0]	reg_imuxs_s
    // [6:4]	reg_qmuxs_s
    // [9:8]	reg_iclpstr_s
    // [13:12]	reg_qclpstr_s
        // `RIU_W((`RIUBASE_ADCPLL>>1)+7'h45, 2'b01, 16'h0000); // Set IMUXS QMUXS
        bRet &= MSB124X_WriteReg2bytes(0x0A00+(0x45)*2, 0x0000);

    // [0]	reg_imux_clpz_s
    // [1]	reg_qmux_clpz_s
    // [4]	reg_in_hz
    // [8]	reg_se_en
    // [12]	reg_iflip_en_t
    // [13]	reg_iflip_en_s
    // [14]	reg_qflip_en_s
    //    `RIU_W((`RIUBASE_ADCPLL>>1)+7'h46, 2'b01, 16'h0000); // Set reg_imux_clpz_s, reg_qmux_clpz_s

    // [0]	Channel I ADC power down: 1=power dwon
    // [1]	Channel Q ADC power down: 1=power dwon
    // [2]	power down clamp buffer for test mode
    // [3]	change ADC reference voltage for SSIF
    // [6:4]    ADC source bias current control
    // [9:8]    XTAL receiver amp gain
        // `RIU_W((`RIUBASE_ADCPLL>>1)+7'h0c, 2'b11, 16'h0002); // Set enable ADC clock
        bRet &= MSB124X_WriteReg2bytes(0x0A00+(0x0c)*2, 0x0002);

    // [0]	reg_linear_cal_start_q	0	0	1
    // [1]	reg_linear_cal_mode_q	0	0	1
    // [2]	reg_linear_cal_en_q	0	0	1
    // [3]	reg_linear_cal_code0_oren_q	0	0	1
    // [6:4]	reg_linear_cal_status_sel_q	2	0	3
    // [7]	reg_pwdn_vcalbuf	0	0	1
      // `RIU_W((`RIUBASE_ADCPLL>>1)+7'h0f, 2'b01, 16'h0000); // Set reg_pwdn_vcalbuf = 1'b0
      bRet &= MSB124X_WriteReg2bytes(0x0A00+(0x0f)*2, 0x0000);

    // [3:0]	clamp voltage control
    //          3'b000 = 0.7v
    //          3'b001 = 0.75v
    //          3'b010 = 0.5v
    //          3'b011 = 0.4v
    //          3'b100 = 0.8v
    //          3'b101 = 0.9v
    //          3'b110 = 0.65v
    //          3'b111 = 0.60v
    // [4]	REFERENCE power down
      // `RIU_W((`RIUBASE_ADCPLL>>1)+7'h20, 2'b11, 16'h0000); // Disable PWDN_REF
      bRet &= MSB124X_WriteReg2bytes(0x0A00+(0x20)*2, 0x0000);

    // Set ADC gain is 1
      // `RIU_W((`RIUBASE_ADCPLL>>1)+7'h0b, 2'b11, 16'h0505);
      bRet &= MSB124X_WriteReg2bytes(0x0A00+(0x0b)*2, 0x0909);

    // Disable ADC Sign bit
      // `RIU_W((`RIUBASE_ADCPLL>>1)+7'h2e, 2'b11, 16'h0000);
      bRet &= MSB124X_WriteReg2bytes(0x0A00+(0x2e)*2, 0x0000);

    // ADC I channel offset
      // `RIU_W((`RIUBASE_ADCPLL>>1)+7'h2a, 2'b11, 16'h0c00);
      bRet &= MSB124X_WriteReg2bytes(0x0A00+(0x2a)*2, 0x0c00);

    // ADC Q channel offset
      // `RIU_W((`RIUBASE_ADCPLL>>1)+7'h2b, 2'b11, 16'h0c00);
      bRet &= MSB124X_WriteReg2bytes(0x0A00+(0x2b)*2, 0x0c00);

    // [2:0]reg_acl_ref
    // [5:4]reg_acl_isel
    // [8]	reg_xtal_pm_isel
    // [9]	reg_bond_mode
    // [10]	reg_clk_bond_mode
    // [11]	reg_clk_usb_3p3_en
    // [13:12]	reg_iq_ctrl	= 2'd1
	// `RIU_W((`RIUBASE_ADCPLL>>1)+7'h19, 2'b11, 16'h1e00);
	bRet &= MSB124X_WriteReg2bytes(0x0A00+(0x19)*2, 0x1e00);

    // [ 4:0]reg_ckg_bist[4:0]
    // [11:8]reg_ckg_adcd_d2[3:0]
	// `RIU_W((`RIUBASE_TOP>>1)+7'h1c, 2'b11, 16'h0000);
	bRet &= MSB124X_WriteReg2bytes(0x0900+(0x1c)*2, 0x0000);

    // [ 4:0]reg_ckg_dvbtm_sram_t11x_t22x[4:0]
    // [12:8]reg_ckg_dvbtm_sram_t11x_t24x[4:0]
	// `RIU_W((`RIUBASE_TOP>>1)+7'h1e, 2'b11, 16'h0000);
	bRet &= MSB124X_WriteReg2bytes(0x0900+(0x1e)*2, 0x0000);


    // -------------------------------------------------------------------
    // Release clock gating
    // -------------------------------------------------------------------

    // [0]	reg_xtal_en
    // [9:8]	reg_clk_pd_iic
    // [10]	reg_clk_pd_all
      // `RIU_W((`RIUBASE_TOP>>1)+7'h09, 2'b11, 16'h0101);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x09)*2, 0x0101);

    // [3:0]	reg_ckg_adcd
    // [7:4]	reg_ckg_sadc
    // [11:8]	reg_ckg_iicm
    // [13:12]	reg_ckg_sbus
      // `RIU_W((`RIUBASE_TOP>>1)+7'h0a, 2'b11, 16'h0000);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x0a)*2, 0x0000);

    // [5:0]	reg_ckg_mcu
    // [6]	reg_ckg_live
    // [11:8]	reg_ckg_inner
      // `RIU_W((`RIUBASE_TOP>>1)+7'h0b, 2'b11, 16'h0030);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x0b)*2, 0x0030);
    //set MCU ckg to 108MHz by jason
    // reg_ckg_mcu[4:2] = 0x0
    // reg_ckg_mcu[5] = 0x0
//      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x0b)*2, 0x0020);
//      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x0b)*2, 0x0000);

    // @0x0910
    // [3:0]	reg_ckg_dvbtm_adc
    // [6:4]	reg_ckg_dvbt_inner1x
    // [10:8]	reg_ckg_dvbt_inner2x
    // [14:12]	reg_ckg_dvbt_inner4x
    //DVBT2
      // `RIU_W((`RIUBASE_TOP>>1)+7'h10, 2'b11, 16'h1110);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x10)*2, 0x1110);

    // @0x0911
    // [2:0]	reg_ckg_dvbt_outer1x
    // [6:4]	reg_ckg_dvbt_outer2x
    // [11:8]	reg_ckg_dvbtc_outer2x
    //DVBT2
      // `RIU_W((`RIUBASE_TOP>>1)+7'h11, 2'b11, 16'h0111);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x11)*2, 0x0111);

    // @0x0912
    // [3:0]	reg_ckg_dvbtm_ts
    // [4]	reg_dvbtm_ts_out_mode
    // [5]	reg_dvbtm_ts_clk_pol
    // [15:8]	reg_dvbtm_ts_clk_divnum
      // `RIU_W((`RIUBASE_TOP>>1)+7'h12, 2'b11, 16'h1418);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x12)*2, 0x1418);

    // @0x0913
    // [5:0]	reg_ckg_spi
      // `RIU_W((`RIUBASE_TOP>>1)+7'h13, 2'b11, 16'h0020);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x13)*2, 0x0020);

    // @0x0914
    // [12:8]	reg_ckg_dvbtm_sram_t1o2x_t22x
    //DVBT2
      // `RIU_W((`RIUBASE_TOP>>1)+7'h14, 2'b11, 16'h0000);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x14)*2, 0x0000);

    // @0x0915
    // [3:0]	reg_ckg_dvbc_inner
    // [6:4]	reg_ckg_dvbc_eq
    // [10:8]	reg_ckg_dvbc_eq8x
    //DVBT2
      // `RIU_W((`RIUBASE_TOP>>1)+7'h15, 2'b11, 16'h0111);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x15)*2, 0x0111);

    // @0x0916
    // [8:4]	reg_ckg_dvbtm_sram_adc_t22x
    //DVBT2
      // `RIU_W((`RIUBASE_TOP>>1)+7'h16, 2'b11, 16'h0001);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x16)*2, 0x0001);

    // @0x0917
    // [4:0]	reg_ckg_dvbtm_sram_t12x_t22x
    // [12:8]	reg_ckg_dvbtm_sram_t12x_t24x
    //DVBT2
      // `RIU_W((`RIUBASE_TOP>>1)+7'h17, 2'b11, 16'h0000);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x17)*2, 0x0000);

    // @0x0918
    // [4:0]	reg_ckg_dvbtm_sram_t14x_t24x
    // [12:8]	reg_ckg_dvbtm_ts_in
    //DVBT2
      // `RIU_W((`RIUBASE_TOP>>1)+7'h18, 2'b11, 16'h0400);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x18)*2, 0x0400);

    // @0x0919
    // [2:0]	reg_ckg_tdp_jl_inner1x
    // [6:4]	reg_ckg_tdp_jl_inner4x
    // [15:8]	reg_ckg_miu
      // `RIU_W((`RIUBASE_TOP>>1)+7'h19, 2'b11, 16'h3c00);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x19)*2, 0x3c00);

    // @0x091a
    // [6:4]	reg_ckg_dvbt2_inner1x
    // [10:8]	reg_ckg_dvbt2_inner2x
    // [14:12]	reg_ckg_dvbt2_inner4x
     //DVBT2
      // `RIU_W((`RIUBASE_TOP>>1)+7'h1a, 2'b11, 16'h0000);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x1a)*2, 0x0000);

    // @0x090e
    // [3:0]	reg_ckg_dvbs2_ldpc_inner_sram
    // [7:4]	reg_ckg_dvbs_viterbi_sram
    //DVBT2
      // `RIU_W((`RIUBASE_TOP>>1)+7'h0e, 2'b01, 16'h0000);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x0e)*2, 0x0000);

    // @0x091b
    // [2:0]	reg_ckg_dvbt2_outer1x
    // [6:4]	reg_ckg_dvbt2_outer2x
    // [10:8]	reg_ckg_syn_miu
    // [14:12]	reg_ckg_syn_ts
    //DVBT2
      // `RIU_W((`RIUBASE_TOP>>1)+7'h1b, 2'b11, 16'h0000);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x1b)*2, 0x0000);

    // @0x091c
    // [4:0]	reg_ckg_bist
    // [11:8]	reg_ckg_adcd_d2
      // `RIU_W((`RIUBASE_TOP>>1)+7'h1c, 2'b11, 16'h0000);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x1c)*2, 0x0000);

    // @0x091d
    // [3:0]	reg_ckg_dvbtm_adc_eq_1x
    // [7:4]	reg_ckg_dvbtm_adc_eq_0p5x
      // `RIU_W((`RIUBASE_TOP>>1)+7'h1d, 2'b11, 16'h0000);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x1d)*2, 0x0000);

    // @0x0921
    // [2:0]	reg_ckg_tdp_teq_inner1x
    // [14:12]	reg_ckg_tdp_teq_inner2x
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x21)*2, 0x0000);

    // @0x0922
    // [3:0]	reg_ckg_dvbt_t2_inner0p5x_dvbc_eq1x
    // [7:4]	reg_ckg_dvbt_t2_inner2x_dvbc_eq4x
    // [11:8]	reg_ckg_dvbt_t2_inner1x
    //DVBT2
      // `RIU_W((`RIUBASE_TOP>>1)+7'h22, 2'b11, 16'h0000);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x22)*2, 0x0000);

    // [1:0]	reg_iicm_pad_sel
    // [4]	reg_i2c_sbpm_en
    // [12:8]	reg_i2c_sbpm_idle_num
      // `RIU_W((`RIUBASE_TOP>>1)+7'h08, 2'b01, 16'h0a01);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x08)*2, 0x0a01);

    // [8]	reg_turn_off_pad
      // `RIU_W((`RIUBASE_TOP>>1)+7'h28, 2'b10, 16'h0000);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x28)*2, 0x0000);

    // @0x0970
    // [3:0]	reg_ckg_dvbt_inner2x_srd0p5x
    // [7:4]	reg_ckg_dvbt2_inner2x_srd0p5x
    // [12:8]	reg_ckg_dvbtm_sram_t1outer1x_t24x
    //DVBT2
      // `RIU_W((`RIUBASE_TOP>>1)+7'h70, 2'b11, 16'h0000);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x70)*2, 0x0000);

    // @0x0971
    // [4:0]	reg_ckg_dvbtm_sram_t12x_t24x_srd1x
    // [12:8]	reg_ckg_dvbtm_sram_t14x_t24x_srd1x
    //DVBT2
      // `RIU_W((`RIUBASE_TOP>>1)+7'h71, 2'b11, 16'h0000);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x71)*2, 0x0000);

    // @0x0972
    // [6:0]	reg_ckg_dvbt2_s2_bch_out
    // [12:8]	reg_ckg_dvbt2_outer2x
    //DVBT2
      // `RIU_W((`RIUBASE_TOP>>1)+7'h72, 2'b11, 16'h0000);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x72)*2, 0x0000);

    // @0x0973
    // [3:0]	reg_ckg_dvbt2_inner4x_s2_inner
    //DVBT2
      // `RIU_W((`RIUBASE_TOP>>1)+7'h73, 2'b11, 16'h0000);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x73)*2, 0x0000);

    // @0x0974
    // [4:0]	reg_ckg_dvbtm_sram_t12x_t24x_s2inner
    // [12:8]	reg_ckg_dvbtm_sram_t14x_t24x_s2inner
    //DVBT2
      // `RIU_W((`RIUBASE_TOP>>1)+7'h74, 2'b11, 16'h0000);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x74)*2, 0x0000);

    // @0x0975
    // [4:0]	reg_ckg_dvbtc_rs
    // [11:8]	reg_ckg_dvbs_outer2x_dvbt_outer2x
    // [15:12]	reg_ckg_dvbs_outer2x_dvbt_outer2x_miu
    bRet &= MSB124X_WriteReg2bytes(0x0900+(0x75)*2, 0xc101);

    // @0x0976
    // [4:0]	reg_ckg_dvbs_outer2x_dvbt_outer2x_dvbt2_inner2x
    //DVBT2
      // `RIU_W((`RIUBASE_TOP>>1)+7'h76, 2'b11, 16'h000c);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x76)*2, 0x000c);

    // @0x0977
    // [3:0]	reg_ckg_dvbt2_inner4x_dvbtc_rs
    // [8:4]	reg_ckg_dvbtm_sram_adc_t22x_dvbtc_rs
    //DVBT2
      // `RIU_W((`RIUBASE_TOP>>1)+7'h77, 2'b11, 16'h0000);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x77)*2, 0x0000);

//    $display("--------------------------------------");
//    $display("Initialize Transport Stream synthesizer and APLL");
//    $display("--------------------------------------");

    // ////////////////////////////////////////////////////
    //
    //	According to analog APLL designer's suggest:
    //	APLL_LOOP_DIV = 5'b00000
    //	apll input frequency range 54MHz~106MHz synthesizer clock
    //	so apll_1x_out = synthesizer_out * (apll_ts_mode + 1)
    //
    //	=> apll_1x_out should 40Mhz ~ 130Mhz
    //
    //	Current setting:
    //	apll_1x_out = (432/8.0) * (1+1) = 108MHz
    //	choose reg_ckg_ts_apll_div[2:0] = 3'd4
    //	ts_clk_apll_div = 108/(2^4) = 6.75MHz
    //
    // ////////////////////////////////////////////////////


    // [15:0]	reg_synth_set[15: 0]
    // [ 7:0]	reg_synth_set[23:16]
      // `RIU_W((`RIUBASE_TOP>>1)+7'h51, 2'b11, 16'h0000);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x51)*2, 0x0000);
      // `RIU_W((`RIUBASE_TOP>>1)+7'h52, 2'b11, 16'h0040);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x52)*2, 0x0040);


    // [0]	reg_synth_reset
    // [1]	reg_synth_ssc_en
    // [2]	reg_synth_ssc_mode
    // [4]	reg_synth_sld
      // `RIU_W((`RIUBASE_TOP>>1)+7'h50, 2'b01, 16'h0010);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x50)*2, 0x0010);

    // [1:0]	reg_apll_loop_div_first
    // [15:8]	reg_apll_loop_div_second
      // `RIU_W((`RIUBASE_TOP>>1)+7'h57, 2'b11, 16'h0000);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x57)*2, 0x0000);

    // [0]	reg_apll_pd
    // [1]	reg_apll_reset
    // [2]	reg_apll_porst
    // [3]	reg_apll_vco_offset
    // [4]	reg_apll_en_ts
    // [5]	reg_apll_endcc
    // [6]	reg_apll_clkin_sel
    // [8]	reg_apll_ts_mode
      // `RIU_W((`RIUBASE_TOP>>1)+7'h55, 2'b11, 16'h0100);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x55)*2, 0x0100);
      // `RIU_W((`RIUBASE_TOP>>1)+7'h55, 2'b01, 16'h0110);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x55)*2, 0x0110);

    // [16:0]	reg_apll_test
      // `RIU_W((`RIUBASE_TOP>>1)+7'h59, 2'b11, 16'h0000);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x59)*2, 0x0000);

    // 0x0920
    // [3:0]	reg_ckg_ts_apll_div[2:0]
      // `RIU_W((`RIUBASE_TOP>>1)+7'h20, 2'b01, 16'h0004);
      bRet &= MSB124X_WriteReg2bytes(0x0900+(0x20)*2, 0x0004);


    // -------------------------------------------------------------------
    // initialize MIU
    // -------------------------------------------------------------------
    // $display("--------------------------------------");
    // $display("Initialize MIU ");
    // $display("--------------------------------------");

    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x0f)*2, 0x0000);
    // `RIU_W((`RIUBASE_MIU>>1)+7'h0f, 2'b11, 16'h0000);   //dummy register setting
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x0f)*2, 0x0000);
    // `RIU_W((`RIUBASE_MIU>>1)+7'h0f, 2'b11, 16'h0000);   //dummy register setting
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x0f)*2, 0x0000);
    // `RIU_W((`RIUBASE_MIU>>1)+7'h0f, 2'b11, 16'h0c01);   //miu software reset
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x0f)*2, 0x0c01);
    // `RIU_W((`RIUBASE_MIU>>1)+7'h0f, 2'b11, 16'h0c00);
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x0f)*2, 0x0c00);


// set frequence 180MHz
    // `RIU_W((`RIUBASE_MIU>>1)+7'h11, 2'b11, 16'h60cc);   //reg_ddrpll_rerst              : [13]   1
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x11)*2, 0x60cc);
    // `RIU_W((`RIUBASE_MIU>>1)+7'h11, 2'b11, 16'h00cc);   //reg_ddrpll_rerst              : [13]   0
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x11)*2, 0x00cc);
    // `RIU_W((`RIUBASE_MIU>>1)+7'h11, 2'b11, 16'h0066);
    //bRet &= MSB124X_WriteReg2bytes(0x1200+(0x11)*2, 0x0066);
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x11)*2, 0x004c);  // 133Mhz
    // `RIU_W((`RIUBASE_MIU>>1)+7'h10, 2'b11, 16'h2666);
    //bRet &= MSB124X_WriteReg2bytes(0x1200+(0x10)*2, 0x2666);
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x10)*2, 0x33f8);  // 133Mhz
    // yihao 20130925 for new apll model
    // `RIU_W((`RIUBASE_MIU>>1)+7'h12, 2'b11, 16'h0000);
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x12)*2, 0x0000);
    // `RIU_W((`RIUBASE_MIU>>1)+7'h13, 2'b11, 16'h0000);
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x13)*2, 0x0000);
    // `RIU_W((`RIUBASE_MIU>>1)+7'h16, 2'b11, 16'h0030);
    // yihao 20130925 for new apll model
    // `RIU_W((`RIUBASE_MIU>>1)+7'h16, 2'b11, 16'h0000);
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x16)*2, 0x0000);
    // `RIU_W((`RIUBASE_MIU>>1)+7'h1c, 2'b11, 16'h0080); //reg_fb_clk_sel                 : [7]
    //bRet &= MSB124X_WriteReg2bytes(0x1200+(0x1c)*2, 0x0080);
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x1c)*2, 0x00b0);  //fine tune by Yihao Lo

    // `RIU_W((`RIUBASE_MIU>>1)+7'h01, 2'b11, 16'h8100);
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x01)*2, 0x8100);
    // cke				: [0]
    // reg_self_refresh		: [1]
    // reg_dynamic_cke		: [2]
    // reg_dynamic_ck_odt		: [3]
    // reg_dram_bus			: [5:4] 00: 16b, 01: 32b, 10: 64b
    // reg_dram_type			: [7:6] 00: sdr, 01: ddr, 10: ddr2
    // reg_4ba			: [8]    0: 2bk,  1: 4bk
    		// reg_col_size			: [10:9]
    // reg_cke_oenz			: [12]
    // reg_dq_oenz			: [13]
    // reg_adr_oenz			: [14]
    // reg_cs_z			: [15]
    // `RIU_W((`RIUBASE_MIU>>1)+7'h01, 2'b11, 16'he100);
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x01)*2, 0xe100);
    // `RIU_W((`RIUBASE_MIU>>1)+7'h01, 2'b11, 16'h8100);
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x01)*2, 0x8100);
    // `RIU_W((`RIUBASE_MIU>>1)+7'h02, 2'b11, 16'h0360);	//in_phase
    //bRet &= MSB124X_WriteReg2bytes(0x1200+(0x02)*2, 0x0360);
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x02)*2, 0x0371);  //fine tune by Yihao Lo
    // `RIU_W((`RIUBASE_MIU>>1)+7'h03, 2'b11, 16'h0030);	//tREFRESH                      : [7:0] * 16   30
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x03)*2, 0x0030);
    // `RIU_W((`RIUBASE_MIU>>1)+7'h04, 2'b11, 16'h33c9);
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x04)*2, 0x33c9);
    // reg_tRAS                      : [3:0]        9
    // reg_tRC                       : [7:4]        c
    // reg_tRCD                      : [11:8]       3
    // reg_tRP                       : [15:12]      3
    // `RIU_W((`RIUBASE_MIU>>1)+7'h05, 2'b11, 16'h4232);
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x05)*2, 0x4232);
    // reg_tRRD                      : [3:0]         2
    // tWR                           : [7:4]         3
    // reg_tMRD                      : [11:8]        2
    // reg_tRTP			: [15:12]	4
    // `RIU_W((`RIUBASE_MIU>>1)+7'h06, 2'b11, 16'h5532);
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x06)*2, 0x5532);
    // reg_w2r_dly(tWTR)             : [3:0]         2
    // reg_w2r_oen_dly               : [7:4]         3
    // reg_r2w_dly(tRTW)             : [11:8]        5
    // reg_r2w_oen_dly               : [15:12]       5
    // `RIU_W((`RIUBASE_MIU>>1)+7'h07, 2'b11, 16'h400c);
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x07)*2, 0x400c);
    // tRFC                          : [5:0]         c
    // reg_tRAS[4]                   : [6]           0
    // reg_tRC[4]                    : [7]           0
    // reg_write_latency             : [10:8]        0
    // reg_tCCD                      : [15:14]       1
    // `RIU_W((`RIUBASE_MIU>>1)+7'h0e, 2'b11, 16'h1800);
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x0e)*2, 0x1800);

    // `RIU_W((`RIUBASE_MIU>>1)+7'h23, 2'b11, 16'h7ffe);	//mask other request
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x23)*2, 0x7ffe);

    // `RIU_W((`RIUBASE_MIU>>1)+7'h20, 2'b11, 16'hc001);	//reg_rq0_round_robin		: [0]
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x20)*2, 0xc001);

    //delay 1
    MSB124X_Delayus(100);

    // `RIU_W((`RIUBASE_MIU>>1)+7'h0f, 2'b11, 16'h0c01);	//miu software reset
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x0f)*2, 0x0c01);
    // `RIU_W((`RIUBASE_MIU>>1)+7'h0f, 2'b11, 16'h0c00);	//
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x0f)*2, 0x0c00);
    // `RIU_W((`RIUBASE_MIU>>1)+7'h0f, 2'b11, 16'h0c01);	//miu software reset
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x0f)*2, 0x0c01);
    // `RIU_W((`RIUBASE_MIU>>1)+7'h0f, 2'b11, 16'h0c00);	//
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x0f)*2, 0x0c00);

    // `RIU_W((`RIUBASE_MIU>>1)+7'h01, 2'b11, 16'h010d);
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x01)*2, 0x010d);


// $display("--------Initial DRAM start here!!!");
    // `RIU_W((`RIUBASE_MIU>>1)+7'h00, 2'b11, 16'h0001);
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x00)*2, 0x0001);

    // wait(test_chip_top.dut.i_dig_top.miu_inst.miu_reg_0.init_done);
    bRet &= MSB124X_ReadReg(0x1201, &u8_tmp);
    PRINTE(("[MSB124X]MIU wait init done, u8_tmp=0x%x, bRet=0x%x\n", u8_tmp, bRet));
    while (u8_tmp != 0x80)
    {
        if (u8_timeout++ > 200)
        {
            PRINTE(("[MSB124X][err]MIU init failure...\n"));
            return FALSE;
        }
        // 10us delay
        MSB124X_Delayus(10);
        bRet &= MSB124X_ReadReg(0x1201, &u8_tmp);
    }
    PRINTE(("[MSB124X]MIU init done, u8_tmp=0x%x, bRet=0x%x\n", u8_tmp, bRet));

    // $display("--------Initial Done");
    // `RIU_W((`RIUBASE_MIU>>1)+7'h08, 2'b11, 16'h0001);	//turn on report counter	: [0]
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x08)*2, 0x0001);

    // $display("-------------------------");
    // $display("-- miu self test start --");
    // $display("-------------------------");
    // `RIU_W((`RIUBASE_MIU>>1)+7'h71, 2'b11, 16'h0000);   //base
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x71)*2, 0x0000);
    // `RIU_W((`RIUBASE_MIU>>1)+7'h72, 2'b11, 16'h0010);   //length
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x72)*2, 0x0010);
    // `RIU_W((`RIUBASE_MIU>>1)+7'h74, 2'b11, 16'h5aa5);   //test data
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x74)*2, 0x5aa5);
    // `RIU_W((`RIUBASE_MIU>>1)+7'h70, 2'b11, 16'h0001);   //reg_test_en                   : [0]
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x70)*2, 0x0001);
    // reg_test_mode                 : [2:1] 00 : address,
    //                                      01 : test data
    //                                      10 : shift data
    // reg_inv_data                  : [3]
    // reg_test_loop                 : [4]
    // reg_force_out                 : [5]
    // reg_force_in                  : [6]
    // reg_read_only                 : [8]
    // reg_write_only                : [9]

    // #10000;
    //delay 1
    MSB124X_Delayus(100);

    //wait test_finish
    bRet &= MSB124X_ReadReg((0x1200 + (0x70) * 2 + 1), &u8_tmp);
    PRINTE(("[MSB124X]MIU wait test done, u8_tmp=0x%x,bRet=0x%x\n", u8_tmp, bRet));
    while ((u8_tmp & 0x80) != 0x80)
    {
        if (u8_timeout++ > 200)
        {
            PRINTE(("[MSB124X][err]MIU self test NOT finished...\n"));
            return FALSE;
        }
        // 10us delay
        MSB124X_Delayus(10);
        bRet &= MSB124X_ReadReg((0x1200 + (0x70) * 2 + 1), &u8_tmp);
    }

     // #10000;
     //delay 1
     MSB124X_Delayus(100);

    // MIU self test FAIL let program stuck in this while loop
    bRet &= MSB124X_ReadReg((0x1200 + (0x70) * 2 + 1), &u8_tmp);

    if (u8_tmp == 0x40)
    {
        PRINTE(("@MSB124X, error, MIU self test fail !!!!\n"));
        bRet = FALSE;
    }
    else
    {
        PRINTE(("@MSB124X, MIU self test successful.\n"));
    }


    // `RIU_W((`RIUBASE_MIU>>1)+7'h23, 2'b11, 16'h0000);   //reg_rq0_mask
    bRet &= MSB124X_WriteReg2bytes(0x1200+(0x23)*2, 0x0000);

     // $finish;
    // -------------------------------------------------------------------
    // initialize MIU  finish
    // -------------------------------------------------------------------

    // -------------------------------------------------------------------
    //  Turn on pads
    // -------------------------------------------------------------------

    // ------Turn off all pad in
    // [0] reg_set_pad_low
    // [1] reg_set_pad_high
    // [2] reg_set_i2cs_pad_low
    // [3] reg_set_i2cs_pad_high
    // [8] reg_turn_off_pad
     bRet &= MSB124X_WriteReg2bytes(0x0900+(0x28)*2, 0x0000);

    // ------I2CM pad on
    // [1:0]    reg_iicm_pad_sel[1:0]	1:iicm enable 2:UART enable
    // [4]	    reg_i2c_sbpm_en		1: enable I2CS bypass to I2CM function
    // [12:8]   reg_i2c_sbpm_idle_num[4:0]	a: default
     bRet &= MSB124X_WriteReg2bytes(0x0900+(0x08)*2, 0x0a01);

    // ------Transport Stream pad on (except TS ERR pad)
    // [15:0]   reg_en_ts_pad[15:0]	0x00ff:normal TS location 0xff00:reverse TS location
     bRet &= MSB124X_WriteReg2bytes(0x0900+(0x2d)*2, 0x00ff);

    // ------Transport Stream pad on (TS ERR pad)
    // [0]	    reg_en_ts_err_pad	1: enable
    // [4]	    reg_ts_err_pol	1: inverse 0:normal
     bRet &= MSB124X_WriteReg2bytes(0x0900+(0x2e)*2, 0x0001);

    // ------AGC pad on
    // [0] reg_ifagc_t_enable
    // [1] reg_ifagc_t_odmode
    // [2] reg_ifagc_t_data_sel
    // [4] reg_ifagc_t_force_enable
    // [5] reg_ifagc_t_force_value
    // [8] reg_ifagc_s_enable
    // [9] reg_ifagc_s_odmode
    // [10] reg_ifagc_s_data_sel
    // [12] reg_ifagc_s_force_enable
    // [13] reg_ifagc_s_force_value
    bRet &= MSB124X_WriteReg2bytes(0x0a00+(0x18)*2, 0x0001);

#if(TIMING_VERIFICATION == 1)
    tmm_2 = GIVE_ME_TIME;
#endif
    MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);
    PRINTE(("[MSB124X][end]MSB124X_HW_init, bRet=0x%x\n", bRet));
    return bRet;

}

void MSB124X_Reset(void)
{
    PRINTE(("%s(),%d\n", __FUNCTION__, __LINE__));
    MS_U8     u8Data = 0x00;
    MS_U32    u32Retry = 0x00;

    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !\n"));
        return ;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("[%s]pMSB124X have not inited !!!\n", __FUNCTION__));
        return ;
    }

    printf("Set TSP0 registers...\n");

    if (pMSB124X->enDemodType == E_DEVICE_DEMOD_DVB_T2)
    {
        printf("\nreset T2\n");
        // mask miu access for all and mcu
        MSB124X_WriteReg(0x1200 + (0x23) * 2 + 1, 0x7f);
        MSB124X_WriteReg(0x1200 + (0x23) * 2, 0xfe);
        // 10us delay
        MSB124X_Delayus(10);

        MSB124X_WriteReg(0x0B00 + (0x10) * 2, 0x01);
        MSB124X_WriteReg(0x0B00 + (0x19) * 2, 0x03);
        MSB124X_WriteReg(REG_MB_CNTL, 0x00);             //clear MB_CNTL
        MSB124X_Delayus(5 * 100);

        // enable miu access of mcu gdma
        MSB124X_WriteReg(0x1200 + (0x23) * 2, 0xf0);
        // 10us delay
        MSB124X_Delayus(10);

        MSB124X_WriteReg(0x0B00 + (0x19) * 2, 0x00);
        MSB124X_WriteReg(0x0B00 + (0x10) * 2, 0x00);
        MSB124X_Delayus(5 * 1000);
        MSB124X_ReadReg(REG_MB_CNTL, &u8Data);           //check MB_CNTL ready
        while (u8Data != 0xff)
        {
            MSB124X_Delayus(5 * 1000);
            MSB124X_ReadReg(REG_MB_CNTL, &u8Data);       //check MB_CNTL ready
            if (u32Retry++ > 200)
            {
                PRINTE((">>>MSB124X: MSB124X_Reset Fail!\n"));
                break;
            }
        }
    }
    else if (pMSB124X->enDemodType == E_DEVICE_DEMOD_DVB_T)
    {
        printf("\nreset T\n");
        // mask miu access for all and mcu
        MSB124X_WriteReg(0x1200 + (0x23) * 2 + 1, 0x7f);
        MSB124X_WriteReg(0x1200 + (0x23) * 2, 0xfe);
        // 10us delay
        MSB124X_Delayus(10);

        MSB124X_WriteReg(0x0B00 + (0x19) * 2, 0x01);
        MSB124X_WriteReg(0x0B00 + (0x10) * 2, 0x01);
        MSB124X_WriteReg(REG_MB_CNTL, 0x00);             //clear MB_CNTL
        MSB124X_Delayus(5 * 1000);

        // enable miu access of mcu gdma
        MSB124X_WriteReg(0x1200 + (0x23) * 2, 0xf0);
        // 10us delay
        MSB124X_Delayus(10);

        MSB124X_WriteReg(0x0B00 + (0x10) * 2, 0x00);
        MSB124X_WriteReg(0x0B00 + (0x19) * 2, 0x00);

        MSB124X_ReadReg(REG_MB_CNTL, &u8Data);       //check MB_CNTL ready
        while (u8Data != 0xff)
        {
            MSB124X_Delayus(5 * 1000);
            MSB124X_ReadReg(REG_MB_CNTL, &u8Data);       //check MB_CNTL ready
            if (u32Retry++ > 200)
            {
                PRINTE((">>>MSB124X: MSB124X_Reset Fail!\n"));
                break;
            }
        }

    }

    pMSB124X->u32ChkScanTimeStart = MsOS_GetSystemTime();
}

/*================================================
==               demod  MSB124X loading fw interface
=================================================*/
MS_BOOL MSB124X_MEM_switch(MS_U8 mem_type)
{
    MS_BOOL bRet = TRUE;
    MS_U8 u8_tmp = 0;
    MS_U16 timeout = 0;

#if (TIMING_VERIFICATION==1)
    MS_U32 u32tmm_15 = 0, u32tmm_16 = 0;
    u32tmm_15 = MsOS_GetSystemTime();
#endif

    PRINTE(("[start]MSB124X_MEM_switch, mem_type=0x%x\n", mem_type));

    if(mem_type == 2)
    {
        // SRAM_START_ADDR 0x0000
        bRet &= MSB124X_WriteReg2bytes(0x1000,0x0000);
        bRet &= MSB124X_WriteReg2bytes(0x1004,0x0000);

        // SRAM_END_ADDR 0x7FFF
        bRet &= MSB124X_WriteReg2bytes(0x1002,0x0000);
        bRet &= MSB124X_WriteReg2bytes(0x1006,0x7fff);

        bRet &= MSB124X_WriteReg2bytes(0x2b80, 0x000f);  //base from 0x01 to 0x10(1M)

        // DRAM_START_ADDR 0x8000 (1M+32k)
        bRet &= MSB124X_WriteReg2bytes(0x1008,0x0000);
        bRet &= MSB124X_WriteReg2bytes(0x100C,0x8000);

        // DRAM_END_ADDR    0xFFFF
        bRet &= MSB124X_WriteReg2bytes(0x100A,0x0000);
        bRet &= MSB124X_WriteReg2bytes(0x100E,0xffff);

        //set romA and start address
        bRet &= MSB124X_WriteReg2bytes(0x1020, 0x0000);
        bRet &= MSB124X_WriteReg2bytes(0x1024, 0x8000);
        //set romA and end address
        bRet &= MSB124X_WriteReg2bytes(0x1022, 0x0000);
        bRet &= MSB124X_WriteReg2bytes(0x1026, 0xffff);

        //set romB and start address
        bRet &= MSB124X_WriteReg2bytes(0x1028, 0x0001);
        bRet &= MSB124X_WriteReg2bytes(0x102c, 0x8000);
        //set romB and end address
        bRet &= MSB124X_WriteReg2bytes(0x102a, 0x0001);
        bRet &= MSB124X_WriteReg2bytes(0x102e, 0xffff);

        //rom addr - rom start addr
        bRet &= MSB124X_WriteReg2bytes(0x10aa, 0x6000);
        //romA_en & romB_en
        bRet &= MSB124X_WriteReg2bytes(0x1038, 0x0003);

        // Run code on memory mapping code space (sdram & sram & ROM enable)
        // [0:0] reg_srama_en
        // [1:1] reg_spi_en
        // [2:2] reg_dram_en
        // [3:3] reg_icache_rstz
        // [6:4] reg_test_sel
        // [7:7] reg_mcu_bank_use_xfr
        // [15:8] reg_mcu_bank_xfr
        bRet &= MSB124X_WriteReg2bytes(0x1018, 0x0085);

        // Wait memory map to be enabled
        do
        {
            bRet &= MSB124X_ReadReg(0x1018,&u8_tmp);
            if(timeout++ > 500)
            {
                printf("@msb124x, D+S+ROM memory mapping failure.!!!\n");
                return FALSE;
            }
        }
        while(u8_tmp != 0x85);
    }
    else if(mem_type == 1)
    {

        bRet &= MSB124X_WriteReg(0x2B80, 0x10);

        // SRAM_START_ADDR 0x0000
        bRet &= MSB124X_WriteReg2bytes(0x1000, 0x0000);
        bRet &= MSB124X_WriteReg2bytes(0x1004, 0x0000);

        // SRAM_END_ADDR 0x7FFF
        bRet &= MSB124X_WriteReg2bytes(0x1002, 0x0000);
        bRet &= MSB124X_WriteReg2bytes(0x1006, 0x7FFF);

        // DRAM_START_ADDR 0x8000
        bRet &= MSB124X_WriteReg2bytes(0x1008, 0x0000);
        bRet &= MSB124X_WriteReg2bytes(0x100C, 0x8000);


        // DRAM_END_ADDR    0xFFFF
        bRet &= MSB124X_WriteReg2bytes(0x100A, 0x0000);
        bRet &= MSB124X_WriteReg2bytes(0x100E, 0xFFFF);

        // Enable SRAM&SDRAM memory map
        bRet &= MSB124X_WriteReg(0x1018, 0x05);

        // Wait memory map to be enabled
        do
        {
            bRet &= MSB124X_ReadReg(0x1018, &u8_tmp);
            if (timeout++ > 500)
            {
                PRINTE(("@msb124x, D+S memory mapping failure.!!!\n"));
                return FALSE;
            }
        }
        while (u8_tmp != 0x05);
    }
    else if (mem_type == 0)
    {
        // Enable SRAM&SDRAM memory map

        bRet &= MSB124X_WriteReg(0x2B80, 0x10);

        // DRAM_START_ADDR 0x8000
        bRet &= MSB124X_WriteReg2bytes(0x1008, 0x0000);
        bRet &= MSB124X_WriteReg2bytes(0x100C, 0x0000);


        // DRAM_END_ADDR    0xFFFF
        bRet &= MSB124X_WriteReg2bytes(0x100A, 0x0000);
        bRet &= MSB124X_WriteReg2bytes(0x100E, 0x7FFF);

        // Enable SRAM&SDRAM memory map
        bRet &= MSB124X_WriteReg(0x1018, 0x04);

        // Wait memory map to be enabled
        do
        {
            bRet &= MSB124X_ReadReg(0x1018, &u8_tmp);
            if (timeout++ > 500)
            {
                PRINTE(("@msb124x, D memory mapping failure.!!!\n"));
                return FALSE;
            }
        }
        while (u8_tmp != 0x04);
    }
    else
    {
        PRINTE(("@msb124x, invalid mem type mapping.\n"));
        return FALSE;
    }
#if (TIMING_VERIFICATION==1)
    u32tmm_16 = MsOS_GetSystemTime();
    printf("[tmm8]t16-t15 = %ld (%ld - %ld)\n",u32tmm_16-u32tmm_15,u32tmm_16,u32tmm_15);
#endif
    PRINTE(("[end]MSB124X_MEM_switch, , mem_type=0x%x, bRet=0x%x\n", mem_type, bRet));

    return bRet;
}

static void MSB124X_Driving_Control(MS_BOOL bEnable)
{
    PRINTE(("%s(),%d\n", __FUNCTION__, __LINE__));
    MS_U8 u8Temp;
    MSB124X_ReadReg(0x0958, &u8Temp);
    if (bEnable)
    {
        u8Temp = 0xFF;
    }
    else
    {
        u8Temp = 0x00;
    }
    MSB124X_WriteReg(0x0958, u8Temp);

    MSB124X_ReadReg(0x0959, &u8Temp);
    if (bEnable)
    {
        u8Temp = u8Temp | 0x0F;
    }
    else
    {
        u8Temp = u8Temp & (~0x0F);
    }
    MSB124X_WriteReg(0x0959, u8Temp);
}

static MS_BOOL MSB124X_DTV_Serial_Control(MS_BOOL bEnable)
{
    UNUSED(bEnable);
    PRINTE(("%s(),%d\n", __FUNCTION__, __LINE__));
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("pMSB124X have not inited !!!"));
        return FALSE;
    }

    if (pMSB124X->enDemodType == E_DEVICE_DEMOD_DVB_T2)
    {
        //FRA_T2_BRINGUP
    }
    MSB124X_Driving_Control(1);
    return TRUE;
}

/*================================================
==               demod  MSB124X iic bypass interface
=================================================*/
MS_BOOL MSB124X_IIC_Bypass_Mode(MS_BOOL enable)
{
    MS_U8 u8Retry = 10;
    MS_BOOL bResult;

    PRINTE((">>>MSB124X: IIC_bypass() set %x\n", enable));

    while (u8Retry--)
    {
        if (enable)
            bResult = MSB124X_WriteReg(0x0900 + (0x08) * 2, 0x10); // IIC by-pass mode on
        else
            bResult = MSB124X_WriteReg(0x0900 + (0x08) * 2, 0x00); // IIC by-pass mode off

        if (bResult)
            break;
    }
    return TRUE;
}

/*================================================
==               demod  MSB124X lock and ssi sqi interface
=================================================*/
MS_BOOL MSB124X_Lock(EN_DEVICE_DEMOD_TYPE system, COFDM_LOCK_STATUS eStatus)
{
    MS_U16        u16Address = 0;
    MS_U8         cData = 0;
    MS_U8         cBitMask = 0;
    MS_U8         use_dsp_reg = 0;
    switch (eStatus)
    {
    case COFDM_P1_LOCK:
        u16Address =  0x2482; //T2 P1 lock,
        cBitMask = BIT3;
        break;

    case COFDM_P1_LOCK_HISTORY:
        use_dsp_reg = 1;
        u16Address = E_T2_DVBT2_LOCK_HIS; //T2 P1 ever lock,
        cBitMask = BIT5;
        break;

    case COFDM_L1_CRC_LOCK:
        u16Address =  0x2741; //T2 L1 CRC check,
        cBitMask = BIT5 | BIT6 | BIT7;
        break;

    case COFDM_DVBT2_NOCH_FLAG:
        use_dsp_reg = 1;
        u16Address = T_DVBT2_NOCHAN_Flag; //Pl ever lock,
        cBitMask = BIT0;
        break;

    case COFDM_DVBT_NOCH_FLAG:
        use_dsp_reg = 1;
        u16Address = T_DVBT_NOCHAN_Flag; // No DVBT CH Flag,
        cBitMask = BIT0;
        break;

    case COFDM_FEC_LOCK:
        switch (system)
        {
        case E_DEVICE_DEMOD_DVB_T2:
            use_dsp_reg = 1;
            u16Address =  E_T2_DVBT2_LOCK_HIS; //FEC lock,
            cBitMask = BIT7;
            break;
        case E_DEVICE_DEMOD_DVB_T:
            MSB124X_ReadReg(0x11E0, &cData);//DVBT state
            if (cData == 0x0B)
                return TRUE;
            else
                return FALSE;
            break;
        default:
            return FALSE;
        }
        break;

    case COFDM_TPS_LOCK:
        switch (system)
        {
        case E_DEVICE_DEMOD_DVB_T:
            use_dsp_reg = 0;
            u16Address =  0x0f22; //TPS Lock,ok
            cBitMask = BIT1;
            break;
        case E_DEVICE_DEMOD_DVB_T2:
        default:
            return FALSE;
        }
        break;
    default:
        return FALSE;
    }
    if (!use_dsp_reg)
    {
        if (MSB124X_ReadReg(u16Address, &cData) == FALSE)
        {
            return FALSE;
        }
    }
    else
    {
        if (MSB124X_ReadDspReg(u16Address, &cData) == FALSE)
        {
            return FALSE;
        }
    }
    //printf("\r\n >>> MSB124X_Lock cData = %x\n",cData);
    if ((cData & cBitMask) == cBitMask)
    {
        return TRUE;
    }
    return FALSE;
}

MS_BOOL MSB124X_Get_No_Channel_Flag(EN_DEVICE_DEMOD_TYPE system, COFDM_LOCK_STATUS eStatus)
{
    MS_U16        u16Address = 0;
    MS_U8         cData = 0;
    MS_U8         cBitMask = 0;
    MS_U8         use_dsp_reg = 0;
    switch (eStatus)
    {
    case COFDM_P1_LOCK:
        u16Address =  0x2482; //Pl lock,
        cBitMask = BIT3;
        break;

    case COFDM_P1_LOCK_HISTORY:
        use_dsp_reg = 1;
        u16Address = E_T2_DVBT2_LOCK_HIS; //Pl ever lock,
        cBitMask = BIT5;
        break;

    case COFDM_L1_CRC_LOCK:
        u16Address =  0x2741; //L1 CRC check,
        cBitMask = BIT5 | BIT6 | BIT7;
        break;

    case COFDM_DVBT2_NOCH_FLAG:
        use_dsp_reg = 1;
        u16Address = T_DVBT2_NOCHAN_Flag; //Pl ever lock,
        cBitMask = BIT0;
        break;

    case COFDM_DVBT_NOCH_FLAG:
        use_dsp_reg = 1;
        u16Address = T_DVBT_NOCHAN_Flag; // No DVBT CH Flag,
        cBitMask = BIT0;
        break;

    case COFDM_FEC_LOCK:
        switch (system)
        {
        case E_DEVICE_DEMOD_DVB_T2:
            use_dsp_reg = 1;
            u16Address =  E_T2_DVBT2_LOCK_HIS; //FEC lock,
            cBitMask = BIT7;
            break;
        case E_DEVICE_DEMOD_DVB_T:
            MSB124X_ReadReg(0x11E0, &cData);//addy update 0805
            if (cData == 0x0B)
                return TRUE;
            else
                return FALSE;
            break;
        default:
            return FALSE;
        }
        break;

    case COFDM_TPS_LOCK:
        switch (system)
        {
        case E_DEVICE_DEMOD_DVB_T:
            use_dsp_reg = 0;
            u16Address =  0x0f22; //TPS Lock,ok
            cBitMask = BIT1;
            break;
        case E_DEVICE_DEMOD_DVB_T2:
        default:
            return FALSE;
        }
        break;
    default:
        return FALSE;
    }
    if (!use_dsp_reg)
    {
        if (MSB124X_ReadReg(u16Address, &cData) == FALSE)
        {
            return FALSE;
        }
    }
    else
    {
        if (MSB124X_ReadDspReg(u16Address, &cData) == FALSE)
        {
            return FALSE;
        }
    }
    //printf("\r\n >>> MSB124X_Lock cData = %x\n",cData);
    if ((cData & cBitMask) == cBitMask)
    {
        return TRUE;
    }
    return FALSE;
}

MS_U32 gTimeoutFlag = 0;
EN_LOCK_STATUS MSB124X_DTV_GetLockStatus(void)
{
    MS_U32    u32Timeout = 0;
    MS_U32    u32LockTimeout = 2000;
    MS_BOOL   bCheckPass = FALSE;
    static MS_U32 u32LockTimeStartDVBT = 0;
    static MS_U32 u32LockTimeStartDVBT2 = 0;
    MS_U32 u32NowTime = MsOS_GetSystemTime();
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;

    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !\n"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("[%s]pMSB124X have not inited !!!\n", __FUNCTION__));
        return FALSE;
    }

    switch (pMSB124X->enDemodType)
    {
    case E_DEVICE_DEMOD_DVB_T2:
    {
        u32Timeout = DVBT2_TPS_timeout;

        if (MSB124X_Lock(E_DEVICE_DEMOD_DVB_T2, COFDM_FEC_LOCK) == TRUE)
            bCheckPass = TRUE;
        else
        {
            if (MSB124X_Lock(E_DEVICE_DEMOD_DVB_T2, COFDM_P1_LOCK_HISTORY) == TRUE)
            {
                u32Timeout = DVBT2_FEC_timeout;
                PRINTE(("====> T2 P1 Locked!\n"));
            }
        }

        if (bCheckPass)
        {
            u32LockTimeStartDVBT2 = MsOS_GetSystemTime();
            pMSB124X->bFECLock = TRUE;
            PRINTE(("====> T2 FEC Locked!\n"));
            return E_DEMOD_LOCK;
        }
        else if ((u32NowTime - pMSB124X->u32ChkScanTimeStart < u32Timeout)
                 || (u32NowTime - u32LockTimeStartDVBT2 < u32LockTimeout))
        {
            // SET u32LockTimeStartDVBT2 every time reset demodulator to T2
            //PRINTE(("NowTime: %d  -  pMSB124X->u32ChkScanTimeStart  %d = %d  \n",
            //    u32NowTime,pMSB124X->u32ChkScanTimeStart,(u32NowTime-pMSB124X->u32ChkScanTimeStart)));
            //PRINTE(("u32LockTimeout %d \n ",u32LockTimeout));
            pMSB124X->bFECLock = FALSE;
            return E_DEMOD_CHECKING;
        }
        else
        {
            pMSB124X->bFECLock = FALSE;
            return E_DEMOD_UNLOCK;
        }
    }
    break;
    case E_DEVICE_DEMOD_DVB_T:
    {
        u32Timeout = DVBT_TPS_timeout;
        gTimeoutFlag = DVBT_TPS_timeout;
        if (MSB124X_Lock(E_DEVICE_DEMOD_DVB_T, COFDM_FEC_LOCK) == TRUE)
            bCheckPass = TRUE;
        else
        {
            if (MSB124X_Lock(E_DEVICE_DEMOD_DVB_T, COFDM_TPS_LOCK) == TRUE)
            {
                PRINTE(("T TPS locked!\n"));
                u32Timeout = DVBT_FEC_timeout;
                gTimeoutFlag = DVBT_FEC_timeout;
            }
        }
        if (bCheckPass)
        {
            u32LockTimeStartDVBT = MsOS_GetSystemTime();
            pMSB124X->bFECLock = TRUE;
            PRINTE(("T FEC locked!\n"));
            return E_DEMOD_LOCK;
        }
        else if ((u32NowTime - pMSB124X->u32ChkScanTimeStart < u32Timeout)
                 || (u32NowTime - u32LockTimeStartDVBT < u32LockTimeout))
        {
            //PRINTE(("NowTime: %d  -  pMSB124X->u32ChkScanTimeStart  %d = %d  \n",
            //  u32NowTime,pMSB124X->u32ChkScanTimeStart,(u32NowTime-pMSB124X->u32ChkScanTimeStart)));
            // PRINTE(("u32LockTimeout %d \n ",u32LockTimeout));
            pMSB124X->bFECLock = FALSE;
            return E_DEMOD_CHECKING;
        }
        else
        {
            pMSB124X->bFECLock = FALSE;
            return E_DEMOD_UNLOCK;
        }
        break;
    }
    default:
        return E_DEMOD_UNLOCK;
    }
}

void MSB124X_DTV_GetSNR(void)
{
#if 0
    MS_U8   status = TRUE;
    MS_U32  snr_out = 0;
    MS_U16  snr_ave_num = 0;
    MS_U8   reg = 0, reg_frz;
    MS_U32  noise_power;
    float   f_snr = (float)0.0;
    float     fSNRDivider[] = {1024 * 2, 2048 * 2, 4096 * 2, 8192 * 2, 16384 * 2, 32768 * 2, 32768 * 2, 32768 * 2};
    float     snr_poly = 0.0;     // for SNR polynomial eq.


    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !"));
        return ;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("pMSB124X have not inited !!!"));
        return ;
    }

    switch (pMSB124X->enDemodType)
    {
        case E_DEVICE_DEMOD_DVB_T2:
        {

            float fsnr1 = 0.0;
            float fsnr2 = 0.0;
            float snr_calib_slope = 0.0;
            float snr_calib_bias  = 0.0;

            status &= MSB124X_ReadReg(0x2800 + (0x7f << 1), &reg);
            if ((reg & 0x03) == 0x03)
            {
                status &= MSB124X_ReadReg(0x2800 + (0x7d << 1) + 1, &reg);
                snr_out = (reg & 0x1f);
                status &= MSB124X_ReadReg(0x2800 + (0x7d << 1) + 0, &reg);
                snr_out = (snr_out << 8) | reg;
                status &= MSB124X_ReadReg(0x2800 + (0x7d << 1) + 3, &reg);
                snr_out = (snr_out << 8) | reg;
                status &= MSB124X_ReadReg(0x2800 + (0x7d << 1) + 2, &reg);
                snr_out = (snr_out << 8) | reg;

                status &= MSB124X_ReadReg(0x2800 + (0x7f << 1), &reg);
                status &= MSB124X_WriteReg(0x2800 + (0x7f << 1), reg & (0xff - 0x03));
                // printf("\nreg1=0x%lx\n",snr_out);
            }
            else
            {
                status &= MSB124X_ReadReg(0x2800 + (0x0e << 1) + 3, &reg);
                snr_out = (reg & 0x1f);
                status &= MSB124X_ReadReg(0x2800 + (0x0e << 1) + 2, &reg);
                snr_out = (snr_out << 8) | reg;
                status &= MSB124X_ReadReg(0x2800 + (0x0e << 1) + 1, &reg);
                snr_out = (snr_out << 8) | reg;
                status &= MSB124X_ReadReg(0x2800 + (0x0e << 1) + 0, &reg);
                snr_out = (snr_out << 8) | reg;
                // printf("\nreg2=0x%lx\n",snr_out);
            }

            status &= MSB124X_ReadReg(0x2800 + (0x0a << 1), &reg);
            snr_ave_num = reg & 0x07;
            // printf("\nsnr_ave_num=%d\n",snr_ave_num);

            fsnr1 = 10.0 * log10((float)snr_out / fSNRDivider[snr_ave_num]);

            status &= MSB124X_ReadReg(0x2800 + (0x07 << 1), &reg);

            // HW cali en?
            if ((reg & 0x10) == 0x10)
            {
                // HW calibration.
                // slope
                MSB124X_ReadReg(0x2800 + (0x08 << 1), &reg);
                snr_calib_slope = (float)reg / 32.0;
                // bias
                MSB124X_ReadReg(0x2800 + (0x08 << 1) + 1, &reg);
                snr_calib_bias = (float)((MS_S8)((reg & 0x1f) << 3)) / 32.0;
                snr_calib_bias = pow(2.0, snr_calib_bias);
                fsnr2 = snr_calib_slope * fsnr1 + 10.0 * log10(snr_calib_bias);
            }
            else
                fsnr2 = fsnr1;

            f_snr = fsnr1;

            // printf("\n[dvbt2]slope=%.3f,bias=%.3f,fsnr1=%.2f,fsnr2=%.2f\n",snr_calib_slope,snr_calib_bias,fsnr1,fsnr2);

            //use Polynomial curve fitting to fix snr
            //snr_poly = 0.0027945*pow(*fSNR,3) - 0.2266*pow(*fSNR,2) + 6.0101*(*fSNR) - 53.3621;
            f_snr = f_snr + snr_poly;
            g_MSB124X_fSNR = f_snr;
        }
        break;
        case E_DEVICE_DEMOD_DVB_T:
        {
            // bank 15 0xfe [0] reg_fdp_freeze
            status &= MSB124X_ReadReg(0x0ffe, &reg_frz);
            status &= MSB124X_WriteReg(0x0ffe, reg_frz|0x01);

            // bank 15 0xff [0] reg_fdp_load
            status &= MSB124X_WriteReg(0x0fff, 0x01);

            // bank 15 0x4a [26:0] reg_snr_accu <27,1>
            status &= MSB124X_ReadReg(0x0f4d, &reg);
            noise_power = reg & 0x07;

            status &= MSB124X_ReadReg(0x0f4c, &reg);
            noise_power = (noise_power << 8)|reg;

            status &= MSB124X_ReadReg(0x0f4b, &reg);
            noise_power = (noise_power << 8)|reg;

            status &= MSB124X_ReadReg(0x0f4a, &reg);
            noise_power = (noise_power << 8)|reg;

            noise_power = noise_power/2;

            // bank 15 0x26 [5:4] reg_transmission_mode
            status &= MSB124X_ReadReg(0x0f26, &reg);

            // bank 15 0xfe [0] reg_fdp_freeze
            status &= MSB124X_WriteReg(0x0ffe, reg_frz);

            // bank 15 0xff [0] reg_fdp_load
            status &= MSB124X_WriteReg(0x0fff, 0x01);

            if ((reg&0x30)==0x00) // 2K
            {
                if (noise_power<1512)
                    f_snr = 0.0;
                else
                    f_snr = 10*log10((float)noise_power/1512);
            }
            //else if ((reg&0x30)==0x10)//8K
            else
            {
                if (noise_power<6048)
                    f_snr = 0.0;
                else
                    f_snr = 10*log10((float)noise_power/6048);
            }
            g_MSB124X_fSNR = f_snr;
        }
        break;
        default:
            f_snr = 0.0;
            g_MSB124X_fSNR = f_snr;
            break;
    }
#endif
}

MS_BOOL MSB124X_DTV_GetPreBER(float *p_preBer)
{
    MS_U16 BitErrPeriod = 0;
    MS_U32 BitErr = 0;
    MS_U32 FecType = 0;
    MS_U8  reg = 0;
    float fber = 0;
    MS_U8 status = TRUE;

    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("pMSB124X have not inited !!!"));
        return FALSE;
    }

    switch (pMSB124X->enDemodType)
    {
    case E_DEVICE_DEMOD_DVB_T2:
    default:
        /////////// Data BER /////////////
        // bank 38 0x02 [0] freeze
        status &= MSB124X_WriteReg(0x2604, 0x01);    // avoid confliction

        // bank 38 0x12 Data BER Window[15:0]
        status &= MSB124X_ReadReg(0x2625, &reg);
        BitErrPeriod = reg;
        status &= MSB124X_ReadReg(0x2624, &reg);
        BitErrPeriod = (BitErrPeriod << 8) | reg;

        // bank 38 0x32 Data BER count[15:0]
        // bank 38 0x33 Data BER count[31:16]
        status &= MSB124X_ReadReg(0x2600 + (0x32 << 1) + 3, &reg);
        BitErr = reg;
        status &= MSB124X_ReadReg(0x2600 + (0x32 << 1) + 2, &reg);
        BitErr = (BitErr << 8) | reg;
        status &= MSB124X_ReadReg(0x2600 + (0x32 << 1) + 1, &reg);
        BitErr = (BitErr << 8) | reg;
        status &= MSB124X_ReadReg(0x2600 + (0x32 << 1) + 0, &reg);
        BitErr = (BitErr << 8) | reg;

        // bank 38 0x02 [0] freeze
        status &= MSB124X_WriteReg(0x2604, 0x00);     // avoid confliction

        if (BitErrPeriod == 0)
        { //protect 0
            BitErrPeriod = 1;
        }

        // status &= MSB124X_ReadReg(0x268e, &reg);    //FEC Type[8:7]
        status &= MSB124X_ReadReg(0x278f, &reg);    //FEC Type[8:7]
        FecType = reg;
        status &= MSB124X_ReadReg(0x278e, &reg);    //FEC Type[8:7]
        FecType = (FecType << 8) | reg;
        // if (reg&0x080)
        if (FecType & 0x0180)
        {
            if (BitErr == 0)
                fber = (float)0.5 / (float)(BitErrPeriod * 64800);
            else
                fber = (float)BitErr / (float)(BitErrPeriod * 64800);
        }
        else
        {
            if (BitErr == 0)
                fber = (float)0.5 / (float)(BitErrPeriod * 16200);
            else
                fber = (float)BitErr / (float)(BitErrPeriod * 16200);
        }
        PRINTE(("MSB124X DVBT2 PreLDPCBER = %8.3e \n ", fber));

        if (status == FALSE)
        {
            PRINTE(("DTV_DVBT2_GetPostViterbiBer Fail!\n"));
            return 0;
        }

        *p_preBer = fber;

        printf("[DVBT2] preber=%f, Err_num=%d, block_count=%d, reg=0x%x\n", fber, BitErr, BitErrPeriod, reg);
        break;
    }
    return status;
}


MS_BOOL MSB124X_DTV_GetPostBER(float *p_postBer)
{
    MS_U16 BitErrPeriod = 0;
    MS_U16 BitErr = 0;
    MS_U16 FecType = 0;
    MS_U8  reg = 0, reg_frz;
    float fber = 0;
    MS_U8 status = TRUE;

    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("pMSB124X have not inited !!!"));
        return FALSE;
    }

    switch (pMSB124X->enDemodType)
    {
    case E_DEVICE_DEMOD_DVB_T2:
        /////////// Data BER /////////////
        // bank 38 0x02 [0] freeze
        status &= MSB124X_WriteReg(0x2604, 0x01);    // avoid confliction

        // bank 38 0x12 Data BER Window[15:0]
        status &= MSB124X_ReadReg(0x2625, &reg);
        BitErrPeriod = reg;
        status &= MSB124X_ReadReg(0x2624, &reg);
        BitErrPeriod = (BitErrPeriod << 8) | reg;

        // bank 38 0x34 Data BER count[15:0]
        // bank 38 0x35 Data BER count[31:16]
        status &= MSB124X_ReadReg(0x2600 + (0x34 << 1) + 3, &reg);
        BitErr = reg;
        status &= MSB124X_ReadReg(0x2600 + (0x34 << 1) + 2, &reg);
        BitErr = (BitErr << 8) | reg;
        status &= MSB124X_ReadReg(0x2600 + (0x34 << 1) + 1, &reg);
        BitErr = (BitErr << 8) | reg;
        status &= MSB124X_ReadReg(0x2600 + (0x34 << 1) + 0, &reg);
        BitErr = (BitErr << 8) | reg;

        // bank 38 0x02 [0] freeze
        status &= MSB124X_WriteReg(0x2604, 0x00);     // avoid confliction

        if (BitErrPeriod == 0)
            //protect 0
            BitErrPeriod = 1;

        // status &= MSB124X_ReadReg(0x268e, &reg);    //FEC Type[8:7]
        status &= MSB124X_ReadReg(0x278f, &reg);    //FEC Type[8:7]
        FecType = reg;
        status &= MSB124X_ReadReg(0x278e, &reg);    //FEC Type[8:7]
        FecType = (FecType << 8) | reg;
        // if (reg&0x080)
        if (FecType & 0x0180)
        {
            if (BitErr == 0)
                fber = (float)0.5 / (float)(BitErrPeriod * 64800);
            else
                fber = (float)BitErr / (float)(BitErrPeriod * 64800);
        }
        else
        {
            if (BitErr == 0)
                fber = (float)0.5 / (float)(BitErrPeriod * 16200);
            else
                fber = (float)BitErr / (float)(BitErrPeriod * 16200);
        }
        PRINTE(("MSB124X DVBT2 PostVitBER = %8.3e \n ", fber));

        if (status == FALSE)
        {
            PRINTE(("DTV_DVBT2_GetPostViterbiBer Fail!\n"));
            return 0;
        }

        *p_postBer = fber;

        break;
    case E_DEVICE_DEMOD_DVB_T:
            /////////// Post-Viterbi BER /////////////
            // bank 17 0x32 [7] reg_bit_err_num_freeze
            status &= MSB124X_ReadReg(0x1132, &reg_frz);
            status &= MSB124X_WriteReg(0x1132, reg_frz | 0x80);
            // bank 17 0x30 [7:0] reg_bit_err_sblprd_7_0
            //             [15:8] reg_bit_err_sblprd_15_8
            status &= MSB124X_ReadReg(0x1131, &reg);
            BitErrPeriod = reg;
            status &= MSB124X_ReadReg(0x1130, &reg);
            BitErrPeriod = (BitErrPeriod << 8) | reg;
            // bank 17 0x3a [7:0] reg_bit_err_num_7_0
            //             [15:8] reg_bit_err_num_15_8
            // bank 17 0x3c [7:0] reg_bit_err_num_23_16
            //             [15:8] reg_bit_err_num_31_24
            status &= MSB124X_ReadReg(0x113D, &reg);
            BitErr = reg;
            status &= MSB124X_ReadReg(0x113C, &reg);
            BitErr = (BitErr << 8) | reg;
            status &= MSB124X_ReadReg(0x113B, &reg);
            BitErr = (BitErr << 8) | reg;
            status &= MSB124X_ReadReg(0x113A, &reg);
            BitErr = (BitErr << 8) | reg;

            // bank 17 0x32 [7] reg_bit_err_num_freeze
            status &= MSB124X_WriteReg(0x1132, reg_frz);
            if (BitErrPeriod == 0)
                //protect 0
                BitErrPeriod = 1;
            if (BitErr <= 0)
                fber = 0.5 / ((float)BitErrPeriod * 128 * 188 * 8);
            else
                fber = (float)BitErr / ((float)BitErrPeriod * 128 * 188 * 8);
            PRINTE(("MSB124X DVBT PostVitBER = %8.3e \n ", fber));

            if (status == FALSE)
            {
                PRINTE(("DTV_GetSignalQuality GetPostViterbiBer Fail!\n"));
                return 0;
            }

            *p_postBer = fber;

            break;
        default:
            break;
    }

    return TRUE;
}

MS_U32 MSB124X_DTV_GetBER(void)
{
    PRINTE(("%s(),%d\n", __FUNCTION__, __LINE__));
    MS_U8         status = TRUE;
    MS_U8             reg = 0, reg_frz = 0;
    MS_U16            BitErrPeriod = 0;
    MS_U32            BitErr = 0;
    MS_U16            PktErr = 0;

    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("pMSB124X have not inited !!!"));
        return FALSE;
    }

    if (pMSB124X->enDemodType == E_DEVICE_DEMOD_DVB_T2)
    {
        return 0;
    }
    else if (pMSB124X->enDemodType == E_DEVICE_DEMOD_DVB_T)
    {
        /////////// Post-Viterbi BER /////////////

        // bank 7 0x32 [7] reg_bit_err_num_freeze
        status &= MSB124X_ReadReg(0x1132, &reg_frz);
        status &= MSB124X_WriteReg(0x1132, reg_frz | 0x80);

        // bank 7 0x30 [7:0] reg_bit_err_sblprd_7_0
        //             [15:8] reg_bit_err_sblprd_15_8
        status &= MSB124X_ReadReg(0x1131, &reg);
        BitErrPeriod = reg;

        status &= MSB124X_ReadReg(0x1130, &reg);
        BitErrPeriod = (BitErrPeriod << 8) | reg;

        // bank 7 0x3a [7:0] reg_bit_err_num_7_0
        //             [15:8] reg_bit_err_num_15_8
        // bank 7 0x3c [7:0] reg_bit_err_num_23_16
        //             [15:8] reg_bit_err_num_31_24

        status &= MSB124X_ReadReg(0x113D, &reg);
        BitErr = reg;

        status &= MSB124X_ReadReg(0x113C, &reg);
        BitErr = (BitErr << 8) | reg;

        status &= MSB124X_ReadReg(0x113B, &reg);
        BitErr = (BitErr << 8) | reg;

        status &= MSB124X_ReadReg(0x113A, &reg);
        BitErr = (BitErr << 8) | reg;

#if 1
        // bank 7 0x3e [7:0] reg_uncrt_pkt_num_7_0
        //             [15:8] reg_uncrt_pkt_num_15_8
        status &= MSB124X_ReadReg(0x113F, &reg);
        PktErr = reg;

        status &= MSB124X_ReadReg(0x113E, &reg);
        PktErr = (PktErr << 8) | reg;
#endif

        // bank 7 0x32 [7] reg_bit_err_num_freeze
        status &= MSB124X_WriteReg(0x1132, reg_frz);

        if (BitErrPeriod == 0)  //protect 0
        {
            BitErrPeriod = 1;
        }
        if (status)
        {
            printf(" @MSB124X_GetPostViterbiBer OK\n");
            return  TRUE;
        }
        else
        {
            printf(" @MSB124X_GetPostViterbiBer NG\n");
            return FALSE;
        }
    }
    return FALSE;
}

MS_U16 MSB124X_DTV_GetSignalQuality(void)
{
#if 0
    MS_U8     status = TRUE;
    MS_U8     reg = 0; //, reg_frz;
    MS_U16    BitErrPeriod = 0;
    MS_U32    BitErr = 0;
    MS_U16    FecType = 0;
    MS_U8     u8_index = 0;
    float       fber = (float)0.0;
    float       SQI = (float)0.0;
    float       BER_SQI = (float)0.0;
    float       cn_ref = (float)0.0;
    float       cn_rec = (float)0.0;
    float       cn_rel = (float)0.0;

    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("pMSB124X have not inited !!!"));
        return FALSE;
    }

    switch (pMSB124X->enDemodType)
    {
    case E_DEVICE_DEMOD_DVB_T2:
    {
        E_T2_CONSTEL  constel =  _T2_QAM_UNKNOWN;
        E_T2_CODERATE coderate = _T2_CR_UNKNOWN;

        /////////// Check lock status /////////////
        MSB124X_ReadDspReg(0x00f0, &reg);
        if ((reg & BIT7) == 0x00)
        {
            return 0;
        }
        /////////// Data BER /////////////
        // bank 38 0x02 [0] freeze
        status &= MSB124X_WriteReg(0x2604, 0x01);    // avoid confliction

        // bank 38 0x12 Data BER Window[15:0]
        status &= MSB124X_ReadReg(0x2625, &reg);
        BitErrPeriod = reg;
        status &= MSB124X_ReadReg(0x2624, &reg);
        BitErrPeriod = (BitErrPeriod << 8) | reg;

        // bank 38 0x32 Data BER count[15:0]
        // bank 38 0x33 Data BER count[31:16]
        status &= MSB124X_ReadReg(0x2600 + (0x34 << 1) + 3, &reg);
        BitErr = reg;
        status &= MSB124X_ReadReg(0x2600 + (0x34 << 1) + 2, &reg);
        BitErr = (BitErr << 8) | reg;
        status &= MSB124X_ReadReg(0x2600 + (0x34 << 1) + 1, &reg);
        BitErr = (BitErr << 8) | reg;
        status &= MSB124X_ReadReg(0x2600 + (0x34 << 1) + 0, &reg);
        BitErr = (BitErr << 8) | reg;

        // bank 38 0x02 [0] freeze
        status &= MSB124X_WriteReg(0x2604, 0x00);     // avoid confliction

        if (BitErrPeriod == 0)
            //protect 0
            BitErrPeriod = 1;

        // status &= MSB124X_ReadReg(0x268e, &reg);    //FEC Type[8:7]
        status &= MSB124X_ReadReg(0x278f, &reg);    //FEC Type[8:7]
        FecType = reg;
        status &= MSB124X_ReadReg(0x278e, &reg);    //FEC Type[8:7]
        FecType = (FecType << 8) | reg;
        // if (reg&0x080)
        if (FecType & 0x0180)
        {
            if (BitErr == 0)
                fber = (float)0.5 / (float)(BitErrPeriod * 64800);
            else
                fber = (float)BitErr / (float)(BitErrPeriod * 64800);
        }
        else
        {
            if (BitErr == 0)
                fber = (float)0.5 / (float)(BitErrPeriod * 16200);
            else
                fber = (float)BitErr / (float)(BitErrPeriod * 16200);
        }

        if (status == FALSE)
        {
            PRINTE(("DTV_GetSignalQuality_DVBT2_GetPostViterbiBer Fail!\n"));
            return 0;
        }


        if (fber > 1E-4)
            BER_SQI = 0.0;
        else if (fber >= 1E-7)
            BER_SQI = 100.0 / 15;
        else
            BER_SQI = 100.0 / 6;

        MSB124X_ReadReg(0x2700 + 0x47 * 2, &reg);
        coderate = (E_T2_CODERATE)(reg & 0x07);
        constel = (E_T2_CONSTEL)((reg >> 3) & 0x07);

        MSB124X_DTV_GetSNR();
        cn_rec = g_MSB124X_fSNR;
        cn_ref = (float) - 1.0;
        while (g_msb124x_dvbt2_sqi_cn_nordigp1[u8_index].constel != _T2_QAM_UNKNOWN)
        {
            if ((g_msb124x_dvbt2_sqi_cn_nordigp1[u8_index].constel == constel)
                    && (g_msb124x_dvbt2_sqi_cn_nordigp1[u8_index].code_rate == coderate))
            {
                cn_ref = g_msb124x_dvbt2_sqi_cn_nordigp1[u8_index].cn_ref;
                break;
            }
            else
            {
                u8_index++;
            }
        }

        if (cn_ref == -1.0)
            SQI = (float)0.0;
        else
        {
            cn_rel = cn_rec - cn_ref;
            if (cn_rel > 3.0)
                SQI = 100;
            else if (cn_rel >= -3)
            {
                SQI = (cn_rel + 3) * BER_SQI;
                if (SQI > 100.0) SQI = 100.0;
                else if (SQI < 0.0) SQI = 0.0;
            }
            else
                SQI = (float)0.0;
        }

        return SQI;
        break;
    }
    case E_DEVICE_DEMOD_DVB_T:
    {
        float fber = 0.0;
        float log_ber = 0.0;
        MS_U8 u8Data = 0;
        if (MSB124X_ReadReg(0x112C, &u8Data) == FALSE)
        {
            PRINTE(("DTV_DVBT_GetSignalQuality ReadReg fail!!! \n"));
            return 0;
        }
        if (u8Data & 0x02 /*BIT1*/)
        {
            MS_U8 status = TRUE;
            MS_U8 reg = 0, reg_frz = 0;
            MS_U16 BitErrPeriod = 0;
            MS_U32 BitErr = 0;
            MS_U16 PktErr = 0;
            /////////// Post-Viterbi BER /////////////
            // bank 7 0x32 [7] reg_bit_err_num_freeze
            status &= MSB124X_ReadReg(0x1132, &reg_frz);
            status &= MSB124X_WriteReg(0x1132, reg_frz | 0x80);
            // bank 7 0x30 [7:0] reg_bit_err_sblprd_7_0
            //             [15:8] reg_bit_err_sblprd_15_8
            status &= MSB124X_ReadReg(0x1131, &reg);
            BitErrPeriod = reg;
            status &= MSB124X_ReadReg(0x1130, &reg);
            BitErrPeriod = (BitErrPeriod << 8) | reg;
            // bank 7 0x3a [7:0] reg_bit_err_num_7_0
            //             [15:8] reg_bit_err_num_15_8
            // bank 7 0x3c [7:0] reg_bit_err_num_23_16
            //             [15:8] reg_bit_err_num_31_24
            status &= MSB124X_ReadReg(0x113D, &reg);
            BitErr = reg;
            status &= MSB124X_ReadReg(0x113C, &reg);
            BitErr = (BitErr << 8) | reg;
            status &= MSB124X_ReadReg(0x113B, &reg);
            BitErr = (BitErr << 8) | reg;
            status &= MSB124X_ReadReg(0x113A, &reg);
            BitErr = (BitErr << 8) | reg;
            // bank 7 0x3e [7:0] reg_uncrt_pkt_num_7_0
            //             [15:8] reg_uncrt_pkt_num_15_8
            status &= MSB124X_ReadReg(0x113F, &reg);
            PktErr = reg;
            status &= MSB124X_ReadReg(0x113E, &reg);
            PktErr = (PktErr << 8) | reg;
            // bank 7 0x32 [7] reg_bit_err_num_freeze
            status &= MSB124X_WriteReg(0x1132, reg_frz);
            if (BitErrPeriod == 0)
                //protect 0
                BitErrPeriod = 1;
            if (BitErr <= 0)
                fber = 0.5 / ((float)BitErrPeriod * 128 * 188 * 8);
            else
                fber = (float)BitErr / ((float)BitErrPeriod * 128 * 188 * 8);
            PRINTE(("MSB124X PostVitBER = %8.3e \n ", fber));
            PRINTE(("MSB124X PktErr = %d \n ", (int)PktErr));

            if (status == FALSE)
            {
                PRINTE(("DTV_GetSignalQuality GetPostViterbiBer Fail!\n"));
                return 0;
            }

            log_ber = log10((double)fber);
            if (log_ber <= (- 7.0))
            {
                SQI = 100;    //*quality = 100;
            }
            else if (log_ber < -6.0)
            {
                SQI = (90 + (((- 6.0) - log_ber) / ((- 6.0) - (- 7.0)) * (100 - 90)));
            }
            else if (log_ber < -5.5)
            {
                SQI = (80 + (((- 5.5) - log_ber) / ((- 5.5) - (- 6.0)) * (90 - 80)));
            }
            else if (log_ber < -5.0)
            {
                SQI = (70 + (((- 5.0) - log_ber) / ((- 5.0) - (- 5.5)) * (80 - 70)));
            }
            else if (log_ber < -4.5)
            {
                SQI = (60 + (((- 4.5) - log_ber) / ((-4.5) - (- 5.0)) * (70 - 50)));
            }
            else if (log_ber < -4.0)
            {
                SQI = (50 + (((- 4.0) - log_ber) / ((- 4.0) - (- 45)) * (60 - 50)));
            }
            else if (log_ber < -3.5)
            {
                SQI = (40 + (((- 3.5) - log_ber) / ((- 3.5) - (- 4.0)) * (50 - 40)));
            }
            else if (log_ber < -3.0)
            {
                SQI = (30 + (((- 3.0) - log_ber) / ((- 3.0) - (- 3.5)) * (40 - 30)));
            }
            else if (log_ber < -2.5)
            {
                SQI = (20 + (((- 2.5) - log_ber) / ((- 2.5) - (-3.0)) * (30 - 20)));
            }
            else if (log_ber < -1.9)
            {
                SQI = (0 + (((- 1.9) - log_ber) / ((- 1.9) - (- 2.5)) * (20 - 0)));
            }
            else
            {
                SQI = 0;
            }
            return SQI;
        }
        else
        {
            return 0;
        }
        break;
    }
    default:
        break;
    }  // end of switch
#endif
    return 0;
}

MS_U16 MSB124X_DTV_GetSignalStrength(void)
{
#if 0
    MS_U8    status = TRUE;
    MS_U8    reg_tmp = 0;
    MS_U8    rf_agc_val = 0;
    MS_U8    if_agc_val = 0;
    MS_U8    i = 0;
    MS_U8    ssi_tbl_len = 0;
    MS_U8    tps_cnstl = 0;
    MS_U8    tps_cr = 0;
    MS_U8    ssi = 0;
    MS_U8    u8RFAGC = 0;
    MS_U16   ypIFAGC1 = 0, ypIFAGC2 = 0;
    float    ch_power_db = 0;
    float    ch_power_rf = 0;
    float    ch_power_if = 0;
    float    ch_power_ref = 0;
    float    ch_power_rel = 0;
    double fPrel = 0.0, fPinput = 0.0;
    MS_U8  demodState = 0;
    MS_U8  reg = 0;
//    S_IFAGC_SSI     *ifagc_ssi;

    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("pMSB124X have not inited !!!"));
        return FALSE;
    }

    status &= MSB124X_ReadReg(0x0990, &reg);
    demodState = reg;
    switch (pMSB124X->enDemodType)
    {
    case E_DEVICE_DEMOD_DVB_T2:
    {
        /***************************************
        * Force u8RFAGC 150 due to unknown SAR port for each demo board.
        ***************************************/
        // u8RFAGC=MDrv_SAR_Adc_GetValue(2);
        u8RFAGC = 150;
        PRINTE((">>> RFAGC = %d <<<\n", (int)u8RFAGC));
        if (u8RFAGC < 89)
        {
            ch_power_rf = -45;
        }
        else if (u8RFAGC < 111)
        {
            ch_power_rf = (-45) - (float)((u8RFAGC - 89) * 5) / (111 - 89);
        }
        else if (u8RFAGC < 149)
        {
            ch_power_rf = (-50) - (float)((u8RFAGC - 111) * 5) / (148 - 111);
        }
        else
        {
            ch_power_rf = -55;
        }
        // IFAGC
        // debug select
        MSB124X_WriteReg(0x3e00 + 0x13 * 2, 0x03);
        MSB124X_WriteReg(0x3e00 + 0x02 * 2, 0x00); //set freeze & dump [Write]
        MSB124X_WriteReg(0x3e00 + 0x02 * 2 + 1, 0x80);

        // agc gain2 24 Bit
        //MSB124X_ReadReg(0x3e00+0x14*2+1, &reg_tmp);
        MSB124X_ReadReg(0x3e00 + 0x14 * 2 + 2, &reg_tmp);
        ypIFAGC2 = reg_tmp;
        MSB124X_ReadReg(0x3e00 + 0x14 * 2 + 1, &reg_tmp);
        ypIFAGC1 = reg_tmp;
        MSB124X_ReadReg(0x3e00 + 0x14 * 2 + 0, &reg_tmp);
        ypIFAGC1 = (ypIFAGC1 << 8) | reg_tmp;
        // printf("============================>[YP] IFAGC_2 = %x, IFAGC_1 = %x\n", ypIFAGC2, ypIFAGC1);
        MSB124X_ReadReg(0x3e00 + 0x14 * 2 + 1, &reg_tmp);

        MSB124X_WriteReg(0x3e00 + 0x02 * 2, 0x00); //set freeze & dump [Write]
        MSB124X_WriteReg(0x3e00 + 0x02 * 2 + 1, 0x00);
        PRINTE((">>> reg_tmp = %x <<<\n", (int)reg_tmp));
        if_agc_val = reg_tmp;
        PRINTE((">>> if_agc_val = %d <<<\n", (int)if_agc_val));

        if (if_agc_val < 67)
        {
            ch_power_if = -55;
        }
        else if (if_agc_val < 76)
        {
            ch_power_if = (-55) - (float)((if_agc_val - 67) * 5) / (76 - 67);
        }
        else if (if_agc_val < 88)
        {
            ch_power_if = (-60) - (float)((if_agc_val - 76) * 5) / (88 - 76);
        }
        else if (if_agc_val < 99)
        {
            ch_power_if = (-65) - (float)((if_agc_val - 88) * 5) / (99 - 88);
        }
        else if (if_agc_val < 113)
        {
            ch_power_if = (-70) - (float)((if_agc_val - 99) * 5) / (113 - 99);
        }
        else if (if_agc_val < 128)
        {
            ch_power_if = (-75) - (float)((if_agc_val - 113) * 5) / (128 - 113);
        }
        else if (if_agc_val < 145)
        {
            ch_power_if = (-80) - (float)((if_agc_val - 128) * 5) / (145 - 128);
        }
        else if (if_agc_val < 165)
        {
            ch_power_if = (-85) - (float)((if_agc_val - 145) * 5) / (165 - 145);
        }
        else if (if_agc_val < 183)
        {
            ch_power_if = (-90) - (float)((if_agc_val - 165) * 5) / (183 - 165);
        }
        else
        {
            ch_power_if = -96;
        }
        if (ch_power_rf > (-55.0 + 0.5))
        {
            ch_power_db = ch_power_rf;
        }
        else if (ch_power_if < (-55.0 - 0.5))
        {
            ch_power_db = ch_power_if;
        }
        else
        {
            ch_power_db = (ch_power_if + ch_power_rf) / 2;
        }
        PRINTE(("ch_power_rf = %f\n", ch_power_rf));
        PRINTE(("ch_power_if = %f\n", ch_power_if));
        PRINTE(("ch_power_db = %f\n", ch_power_db));
        // -50 dB ~ -95 dB
        // 100 ~ 0

        if (ch_power_db > -50)
        {
            ssi = 100;
        }
        else if (ch_power_db < -95)
        {
            ssi = 0;;
        }
        else
        {
            ssi = 100 - ((-50 - ch_power_db) * 2.22);
        }
        MS_U8 u8Modulation = 0, u8CodeRate = 0;

        MSB124X_ReadReg(0x2700 + (0x47 * 2), &u8Modulation);
        u8Modulation = (((MS_U16) u8Modulation) & (BIT5 | BIT4 | BIT3)) >> 3;
        if (u8Modulation >= 3) u8Modulation = 3;
        MSB124X_ReadReg(0x2700 + (0x47 * 2), &u8CodeRate);
        u8CodeRate = (((MS_U16) u8CodeRate) & (BIT2 | BIT1 | BIT0));
        if (u8CodeRate >= 5) u8CodeRate = 5;

        //Fix me, temp solution; demod doesn't lock, then use fref = -98 to compute SSI
        if (demodState != 0x09)
        {
            fPrel = fPinput - (-50.0f);
        }
        else
        {
            fPrel = fPinput - fDVBT2_SSI_Pref[u8Modulation][u8CodeRate];
        }

        if (fPrel < -15.0)
        {
            ssi = 0;
        }
        else if (fPrel < 0.0)
        {
            ssi = (MS_U8)(((double)2.0 / 3) * (fPrel + 15.0));
        }
        else if (fPrel < 20.0)
        {
            ssi = 4 * fPrel + 10;
        }
        else if (fPrel < 35.0)
        {
            ssi = (MS_U8)(((double)2.0 / 3) * (fPrel - 20.0) + 90);
        }
        else
        {
            ssi = 100;
        }
        //printf("=============================>SSI: u8Modulation= %d, u8CodeRate=%d\n, fPinput=%f, fDVBT2_SSI_Pref=%f\n, fPrel=%f, ssi=%d\n",u8Modulation, u8CodeRate, fPinput, fDVBT2_SSI_Pref[u8Modulation][u8CodeRate], fPrel, ssi);

        PRINTE((">>> SSI = %d <<<\n", (int)ssi));
    }
    break;
    case E_DEVICE_DEMOD_DVB_T:
    {
        ///////// RF/IF-AGC Gain Out /////////////
        rf_agc_val = 0x3f;

        // ==== IFAGC_GAIN_OUT (GAIN2) ====

        // reg_agc_debug_sel[3:0]
        MSB124X_ReadReg(0x3e26, &reg_tmp);
        reg_tmp = (reg_tmp & 0xf0) | 0x03; // select ifagc_gain
        MSB124X_WriteReg(0x3e26, reg_tmp);

        // reg_agc_gain2_out
        // use only high byte value
        MSB124X_ReadReg(0x3e29, &reg_tmp);
        if_agc_val = reg_tmp;

        PRINTE(("SSI_RFAGC (SAR) = 0x%x\n", (MS_U16)rf_agc_val));
        PRINTE(("SSI_IFAGC_H = 0x%x\n", (MS_U16) if_agc_val));

        for (i = 0; i < sizeof(RFAGC_SSI) / sizeof(S_RFAGC_SSI); i++)
        {
            if (rf_agc_val <= RFAGC_SSI[i].sar3_val)
            {
                ch_power_rf = RFAGC_SSI[i].power_db;
                break;
            }
        }

//        ifagc_ssi = IFAGC_SSI;
        ssi_tbl_len = sizeof(IFAGC_SSI) / sizeof(S_IFAGC_SSI);

        for (i = 0; i < ssi_tbl_len; i++)
        {
            if (if_agc_val <= IFAGC_SSI[i].agc_val)
            {
                ch_power_if = IFAGC_SSI[i].power_db;
                break;
            }
        }

        PRINTE(("ch_power_rf = %f\n", ch_power_rf));
        PRINTE(("ch_power_if = %f\n", ch_power_if));

        ch_power_db = (ch_power_rf > ch_power_if) ? ch_power_rf : ch_power_if;

        if (MSB124X_Lock(E_DEVICE_DEMOD_DVB_T, COFDM_FEC_LOCK) == TRUE)
        {
            ///////// Get Constellation and Code Rate to determine Ref. Power //////////
            ///////// (refer to Teracom min. spec 2.0 4.1.1.6) /////

            status &= MSB124X_ReadReg(0x0f24, &reg_tmp);
            tps_cnstl = reg_tmp & 0x03;

            status &= MSB124X_ReadReg(0x0f24 + 1, &reg_tmp);
            tps_cr = (reg_tmp & 0x70) >> 4;

            for (i = 0; i < sizeof(SsiPref) / sizeof(S_SSI_PREF); i++)
            {
                if ((tps_cnstl == SsiPref[i].constel)
                        && (tps_cr == SsiPref[i].code_rate))
                {
                    ch_power_ref = SsiPref[i].p_ref;
                    break;
                }
            }
        }
        else
        {
            ch_power_ref = SsiPref[8].p_ref;
        }
        //printf("tps_cnstl=%d, tps_cr = %d\n", tps_cnstl, tps_cr);

        ch_power_rel = ch_power_db - ch_power_ref;

        //printf("ch_power_db = %f, ch_power_ref=%f, ch_power_rel=%f\n", ch_power_db, ch_power_ref, ch_power_rel);

        if (ch_power_rel < -15.0)
            ssi = 0.0;
        else if (ch_power_rel < 0.0)
            ssi = (ch_power_rel + 15.0) * (10.0 / 15.0);
        else if (ch_power_rel < 20.0)
            ssi = ch_power_rel * 4.0 + 10.0;
        else if (ch_power_rel < 35.0)
            ssi = (ch_power_rel - 20.0) * (10.0 / 15.0) + 90.0;
        else
            ssi = 100.0;

        PRINTE((">>> SSI = %d <<<\n", (int)ssi));

    }
    break;
    default:
        ssi = 0;
        PRINTE(("Undefined!!!\n"));
        break;
    }
    return ssi;
#endif
	return 0;
}

#if((FRONTEND_TUNER_TYPE == TUNER_MXL603)||(FRONTEND_TUNER_TYPE == TUNER_MXL608))
MS_U16 MSB124X_DTV_GetSignalStrengthWithRFPower(float dBmValue)
{
    MS_U8    status = TRUE;
    MS_U8    reg_tmp = 0;
    MS_U8    tps_cnstl = 0;
    MS_U8    tps_cr = 0;
    MS_U8    ssi = 0;
    MS_U8    i = 0;
    float    ch_power_ref = 0;
    float    ch_power_rel = 0;
    float    fPrel = 0.0, fPinput = 0.0;
    MS_U8    demodState = 0;
    MS_U8    reg = 0;
    MS_U8    u8Modulation = 0, u8CodeRate = 0;

    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("pMSB124X have not inited !!!"));
        return FALSE;
    }

    status &= MSB124X_ReadReg(0x0990, &reg);
    demodState = reg;
    switch (pMSB124X->enDemodType)
    {
    case E_DEVICE_DEMOD_DVB_T2:
    {
        fPinput = dBmValue;

        // Get Modulation and code Rate
        MSB124X_ReadReg(0x2700 + (0x47 * 2), &u8Modulation);
        u8Modulation = (((MS_U16) u8Modulation) & (BIT5 | BIT4 | BIT3)) >> 3;
        if (u8Modulation >= 3) u8Modulation = 3;
        MSB124X_ReadReg(0x2700 + (0x47 * 2), &u8CodeRate);
        u8CodeRate = (((MS_U16) u8CodeRate) & (BIT2 | BIT1 | BIT0));
        if (u8CodeRate >= 5) u8CodeRate = 5;

        //Fix me, temp solution; demod doesn't lock, then use fref = -98 to compute SSI
        if (demodState != 0x09)
        {
            fPrel = fPinput - (-50.0f);
        }
        else
        {
            fPrel = fPinput - fDVBT2_SSI_Pref[u8Modulation][u8CodeRate];
        }

        if (fPrel < -15.0)
        {
            ssi = 0;
        }
        else if (fPrel < 0.0)
        {
            ssi = (MS_U8)(((double)2.0 / 3) * (fPrel + 15.0));
        }
        else if (fPrel < 20.0)
        {
            ssi = 4 * fPrel + 10;
        }
        else if (fPrel < 35.0)
        {
            ssi = (MS_U8)(((double)2.0 / 3) * (fPrel - 20.0) + 90);
        }
        else
        {
            ssi = 100;
        }
        //printf("=============================>SSI: u8Modulation= %d, u8CodeRate=%d\n, fPinput=%f, fDVBT2_SSI_Pref=%f\n, fPrel=%f, ssi=%d\n",u8Modulation, u8CodeRate, fPinput, fDVBT2_SSI_Pref[u8Modulation][u8CodeRate], fPrel, ssi);

        PRINTE((">>> SSI = %d <<<\n", (int)ssi));
    }
    break;
    case E_DEVICE_DEMOD_DVB_T:
    {
        if (MSB124X_Lock(E_DEVICE_DEMOD_DVB_T, COFDM_FEC_LOCK) == TRUE)
        {
            ///////// Get Constellation and Code Rate to determine Ref. Power //////////
            ///////// (refer to Teracom min. spec 2.0 4.1.1.6) /////

            status &= MSB124X_ReadReg(0x0f24, &reg_tmp);
            tps_cnstl = reg_tmp & 0x03;

            status &= MSB124X_ReadReg(0x0f24 + 1, &reg_tmp);
            tps_cr = (reg_tmp & 0x70) >> 4;

            for (i = 0; i < sizeof(SsiPref) / sizeof(S_SSI_PREF); i++)
            {
                if ((tps_cnstl == SsiPref[i].constel)
                        && (tps_cr == SsiPref[i].code_rate))
                {
                    ch_power_ref = SsiPref[i].p_ref;
                    break;
                }
            }
        }
        else
        {
            ch_power_ref = SsiPref[8].p_ref;
        }
        //printf("tps_cnstl=%d, tps_cr = %d\n", tps_cnstl, tps_cr);

        ch_power_rel = dBmValue - ch_power_ref;

        //printf("ch_power_db = %f, ch_power_ref=%f, ch_power_rel=%f\n", ch_power_db, ch_power_ref, ch_power_rel);

        if (ch_power_rel < -15.0)
            ssi = 0.0;
        else if (ch_power_rel < 0.0)
            ssi = (ch_power_rel + 15.0) * (10.0 / 15.0);
        else if (ch_power_rel < 20.0)
            ssi = ch_power_rel * 4.0 + 10.0;
        else if (ch_power_rel < 35.0)
            ssi = (ch_power_rel - 20.0) * (10.0 / 15.0) + 90.0;
        else
            ssi = 100.0;

        PRINTE((">>> SSI = %d <<<\n", (int)ssi));

    }
    break;
    default:
        ssi = 0;
        PRINTE(("Undefined!!!\n"));
        break;
    }
    return ssi;
}
#endif

EN_DEVICE_DEMOD_TYPE MSB124X_GetCurrentDemodulatorType(void)
{
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("[%s]pMSB124X have not inited !!!\n", __FUNCTION__));
        return FALSE;
    }
    return pMSB124X->enDemodType ;
}

MS_BOOL MSB124X_SetCurrentDemodulatorType(EN_DEVICE_DEMOD_TYPE enDemodType)
{

    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !\n"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("[%s]pMSB124X have not inited !!!\n", __FUNCTION__));
        return FALSE;
    }

    if (enDemodType == pMSB124X->enDemodType)
    {
        return TRUE;
    }
    pMSB124X->enDemodType = enDemodType;
    pMSB124X->u32ChkScanTimeStart = MsOS_GetSystemTime();

    switch (enDemodType)
    {
    case E_DEVICE_DEMOD_DVB_T:
        MDrv_DMD_MSB124X_SetCurrentDemodulatorType(E_DMD_MSB124X_DEMOD_DVBT);
        break;
    case E_DEVICE_DEMOD_DVB_T2:
        MDrv_DMD_MSB124X_SetCurrentDemodulatorType(E_DMD_MSB124X_DEMOD_DVBT2);
    default:
        break;

    }
    return MDrv_DMD_MSB124X_LoadDSPCode();
}

MS_BOOL MSB124X_Active(MS_BOOL bEnable)
{
    PRINTE(("%s(),%d\n", __FUNCTION__, __LINE__));

    UNUSED(bEnable);
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !\n"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("[%s]pMSB124X have not inited !!!\n", __FUNCTION__));
        return FALSE;
    }


    if (pMSB124X->enDemodType == E_DEVICE_DEMOD_DVB_T2)
    {
        return TRUE;
    }
    else if (pMSB124X->enDemodType == E_DEVICE_DEMOD_DVB_T)
    {

        MS_BOOL status = MSB124X_WriteReg(REG_FSM_EN, 0x01); // FSM_EN

        if (status)
        {
            PRINTE((" @MSB124X_MSB124X_Active OK\n"));
        }
        else
        {
            PRINTE((" @MSB124X_MSB124X_Active NG\n"));
        }
        return status;
    }
    return FALSE;
}

/************************************************************************************************
Subject:    Get PLP-ID Bit Map
Function:   DTV_GetPlpBitMap
Parmeter:   u32PlpBitMap
Return:     BOOLEAN :
Remark:     32 byte of data to show PLP-ID existense
            |00000000|00000000|...|00000000|00011111|11111111|
             byte31   byte30   ... byte2    byte1    byte0   => 256 bit in total
*************************************************************************************************/
MS_BOOL MSB124X_DTV_GetPlpBitMap(MS_U8* u8PlpBitMap)
{
    PRINTE(("%s(),%d\n", __FUNCTION__, __LINE__));
    MS_BOOL   status = TRUE;
    MS_U8     u8Data = 0;
    MS_U8     indx = 0;

    status &= MSB124X_ReadDspReg(0x0120, &u8Data);     // check L1 ready
    if (u8Data != 0x30)
        return FALSE;

    while (indx < 32)
    {
        status &= MSB124X_ReadDspReg(0x0100 + indx, &u8Data);
        u8PlpBitMap[indx] = u8Data;
        indx++;
    }

    if (status)
    {
        printf("\n+++++++++u8PlpBitMap data+++++++++++++++\n");
        for (indx = 0; indx < 32; indx++)
            printf("[%d] ", u8PlpBitMap[indx]);
        printf("\n+++++++++u8PlpBitMap end+++++++++++++++\n");
    }
    return status;
}

/************************************************************************************************
Subject:    Get PlpID List and PlpID Size for MPLP mode
Function:   MSB124X_GetPlpIDList
Parmeter:   u8PlpID
Return:     BOOLEAN :
Remark:
 *************************************************************************************************/
MS_BOOL MSB124X_GetPlpIDList(void)
{
    MS_BOOL bRet;
    MS_U8 i, j, u8PlpBitMap[32];
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("pMSB124X have not inited !!!"));
        return FALSE;
    }

    pMSB124X->PlpIDSize = 0;
    memset(u8PlpBitMap, 0xff, sizeof(u8PlpBitMap));
    bRet = MSB124X_DTV_GetPlpBitMap(u8PlpBitMap);
    for (i = 0; i < 32; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if ((u8PlpBitMap[i] >> j) & 1)
            {
                pMSB124X->PlpIDList[pMSB124X->PlpIDSize] = i * 8 + j;
                pMSB124X->PlpIDSize++;
            }
        }
    }
    return TRUE;
}

/*************************************************************************************************
Subject:    Get GROUP_ID upon PLP_ID for MPLP mode
Function:   DTV_GetPlpGroupID
Parmeter:   u8PlpID, u8GroupID
Return:     BOOLEAN :
Remark:
 *************************************************************************************************/
MS_BOOL MSB124X_DTV_GetPlpGroupID(MS_U8 u8PlpID, MS_U8* u8GroupID)
{
    PRINTE(("%s(),%d\n", __FUNCTION__, __LINE__));
    MS_BOOL   status = TRUE;
    MS_U8 u8Data = 0;
    status &= MSB124X_ReadDspReg(0x0120, &u8Data);         // check L1 ready
    if (u8Data != 0x30)
    {
        PRINTE(("[MSB124X]dvbt2 L1 not ready yet\n"));
        return FALSE;
    }
    MSB124X_ReadDspReg(0x00f0, &u8Data);

    if ((u8Data & BIT7) == 0x00)
    {
        PRINTE(("[MSB124X]dvbt2 is un-lock\n"));
        return FALSE;
    }
    // assign PLP-ID value
    status &= MSB124X_WriteReg(0x2700 + (0x78) * 2, u8PlpID);
    status &= MSB124X_WriteReg(0x2700 + (0x01) * 2 + 1, 0x01); // MEM_EN
    MSB124X_Delayus(1000);
    status &= MSB124X_ReadReg(0x2700 + (0x79) * 2, u8GroupID);
    status &= MSB124X_WriteReg(0x2700 + (0x01) * 2 + 1, 0x00); // ~MEM_EN

    return status;
}


/************************************************************************************************
Subject:    Select PLP_ID, GROUP_ID for MPLP mode
Function:   DTV_SetPlpGroupID
Parmeter:   u8PlpID, u8GroupID
Return:     BOOLEAN :
Remark:
 *************************************************************************************************/
MS_BOOL MSB124X_DTV_SetPlpGroupID(MS_U8 u8PlpID, MS_U8 u8GroupID)
{

    MS_BOOL   status = TRUE;
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !\n"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("[%s]pMSB124X have not inited !!!\n", __FUNCTION__));
        return FALSE;
    }

    pMSB124X->u32ChkScanTimeStart = MsOS_GetSystemTime();
    PRINTE(("[start]\n"));

    // assign Group-ID and PLP-ID value (must be written in order)
    status &= MSB124X_WriteDspReg(0x0122, u8GroupID);
    status &= MSB124X_WriteDspReg(0x0121, u8PlpID);
    PRINTE(("[end, return %d]\n", status));
    return status;
}

MS_BOOL MSB124X_T2_SetPlpID(MS_U8 u8PlpID)
{
    MS_BOOL bRet = FALSE;
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("pMSB124X have not inited !!!"));
        return FALSE;
    }
    {
        MS_U32 u32Timeout;
        MS_U8 u8Data;
        MS_U16 u16RegAddress;
        MS_U8 u8LockState;
        MS_BOOL bCheckPass = FALSE;

        u32Timeout = 1500;
        u16RegAddress = 0x0990;
        u8LockState = 0x09;
        MSB124X_ReadReg(u16RegAddress, &u8Data);
        if (u8Data == u8LockState)
            bCheckPass = TRUE;
        if ((u8PlpID != 0xFF) && (pMSB124X->enDemodType == E_DEVICE_DEMOD_DVB_T2) && (bCheckPass))
        {

            MS_U16 u16Retry = 0;
            MS_U8 u8GroupId = 0;
            MSB124X_Delayus(500 * 1000);

            bRet = MSB124X_DTV_GetPlpGroupID(u8PlpID, &u8GroupId);
            while ((bRet == FALSE) && (u16Retry < 60))
            {
                u16Retry++;
                PRINTE(("DoSet_DVBT2 get groupid retry %d \n", u16Retry));
                MSB124X_Delayus(100 * 1000);
                bRet = MSB124X_DTV_GetPlpGroupID(u8PlpID, &u8GroupId);
            }
            if (bRet == FALSE)
            {
                PRINTE(("MW_DTV_FrontEnd_DVBT::DoSet_DVBT2() DTV_DVB_T2_GetPlpGroupID(%d) Error \n", u8PlpID));
                return FALSE;
            }

            bRet = MSB124X_DTV_SetPlpGroupID(u8PlpID, u8GroupId);
            if (bRet == FALSE)
            {
                PRINTE(("MW_DTV_FrontEnd_DVBT::DoSet_DVBT2() DTV_DVB_T2_SetPlpGroupID(%d,%d) Error", u8PlpID, u8GroupId));
                return FALSE;
            }
        }
    }
    return TRUE;
}



MS_BOOL  MSB124X_DTV_TUNER_IsIFChanged(MS_U8 eBandWidth)
{
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;

    printf("Demod CurrBW=%d, TuneBW=%d\n", pMSB124X->enCurrBW, pMSB124X->enTuneBw);
    if (pMSB124X->enCurrBW == pMSB124X->enTuneBw)
    {
        return FALSE;
    }
    if (((DEMOD_BW_MODE_6MHZ != pMSB124X->enCurrBW) && (DEMOD_BW_MODE_6MHZ == pMSB124X->enTuneBw)) || \
            ((DEMOD_BW_MODE_6MHZ == pMSB124X->enCurrBW) && (DEMOD_BW_MODE_6MHZ != pMSB124X->enTuneBw)))
    {


         switch (eBandWidth)
           {
         case 6:

             pMSB124X->enCurrBW= DEMOD_BW_MODE_6MHZ;
             break;
         case 7:

             pMSB124X->enCurrBW= DEMOD_BW_MODE_7MHZ;
             break;
         case 8:
         default:
             pMSB124X->enCurrBW= DEMOD_BW_MODE_8MHZ;
             break;
           }

        return TRUE;
    }
    return FALSE;
}

// DVBT2 95~101ms, DVBT 38~39ms
MS_BOOL MSB124X_DTV_SetFrequency(MS_U32 u32Frequency, MS_U8 eBandWidth, MS_U8 u8PlpID)
{
    MS_U8 bw_t2 = 0, bw_t = 0;
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !\n"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("[%s]pMSB124X have not inited !!!\n", __FUNCTION__));
        return FALSE;
    }

    printf("\n[%s]->freq=%d,bdwh=%d,PlpID %d,type %s\n", __FUNCTION__, u32Frequency, eBandWidth, u8PlpID, E_DEVICE_DEMOD_DVB_T == pMSB124X->enDemodType ? "T" : "T2");


    pMSB124X->bFECLock = FALSE;
    pMSB124X->u32ChkScanTimeStart = MsOS_GetSystemTime();

#if(TIMING_VERIFICATION == 1)
    tmm_11 = GIVE_ME_TIME;
#endif

//set freq.bw and plp id to demod

    switch (eBandWidth)
    {
    case 6:
        bw_t2 = E_DEMOD_BW_6M;
        bw_t   = E_DEMOD_BW_6M - 1;
         pMSB124X->enTuneBw = DEMOD_BW_MODE_6MHZ;
        break;
    case 7:
        bw_t2 = E_DEMOD_BW_7M;
        bw_t  = E_DEMOD_BW_7M - 1;
        pMSB124X->enTuneBw = DEMOD_BW_MODE_7MHZ;
        break;
    case 10:
        bw_t2 = E_DEMOD_BW_10M;
        break;
    case 17:
        bw_t2 = E_DEMOD_BW_17M;
        break;
    case 8:
    default:
        bw_t2 = E_DEMOD_BW_8M;
        bw_t  = E_DEMOD_BW_8M - 1;
        pMSB124X->enTuneBw = DEMOD_BW_MODE_8MHZ;
        break;
    }

    if (pMSB124X->enDemodType == E_DEVICE_DEMOD_DVB_T2)
    {
        printf("\nsetfreq T2\n");
        MSB124X_Reset();
        MSB124X_Delayus(500);
        MSB124X_WriteDspReg((MS_U16)E_T2_BW, bw_t2);      // BW: 0->1.7M, 1->5M, 2->6M, 3->7M, 4->8M, 5->10M
        MSB124X_WriteDspReg((MS_U16)E_T2_PLP_ID, u8PlpID);

        MSB124X_DTV_TUNER_IsIFChanged(eBandWidth);//fix when 820t tuner's IF changes with bandwidth,MSB1236C_SetCurrentDemodulatorType will set IF to default
#if(FRONTEND_TUNER_TYPE == TUNER_RT820T)
        MS_U8 u8FcLow,u8FcHigh;

        if (DEMOD_BW_MODE_6MHZ == pMSB124X->enTuneBw)  //6M
        {
            u8FcLow = T2_FC_L_VAL_6M;
            u8FcHigh = T2_FC_H_VAL_6M;
        }
        else     //7, 8M
        {
            u8FcLow = T2_FC_L_VAL;
            u8FcHigh = T2_FC_H_VAL;
        }
        MSB124X_WriteDspReg((MS_U16)E_T2_FC_L, (MS_U8)u8FcLow);
        MSB124X_WriteDspReg((MS_U16)E_T2_FC_H, (MS_U8)(u8FcHigh));

#endif

        MSB124X_WriteDspReg((MS_U16)E_T2_IF_AGC_INV_PWM_EN, T2_IF_AGC_INV_PWM_EN_VAL);
        MSB124X_WriteDspReg((MS_U16)E_T2_LITE, T2_LITE_VAL);

        MSB124X_WriteReg(REG_FSM_EN, 0x01); // FSM_EN
        MSB124X_Show_Version();//show dvbt2 fw version
    }
    else if (pMSB124X->enDemodType == E_DEVICE_DEMOD_DVB_T)
    {
        printf("\nsetfreq T\n");
        MSB124X_Reset();
        MSB124X_Delayus(500);

        MSB124X_WriteDspReg((MS_U8)T_CONFIG_BW, bw_t);      // BW: 1->6M, 2->7M, 3->8M

        MSB124X_DTV_TUNER_IsIFChanged(eBandWidth);//fix when 820t tuner's IF changes with bandwidth,MSB1236C_SetCurrentDemodulatorType will set IF to default
#if(FRONTEND_TUNER_TYPE == TUNER_RT820T)
            MS_U8 u8FcLow,u8FcHigh;

            if (DEMOD_BW_MODE_6MHZ == pMSB124X->enTuneBw)  //6M
            {
                u8FcLow = FC_L_6M;
                u8FcHigh = FC_H_6M;
            }
            else     //7, 8M
            {
                u8FcLow = FC_L;
                u8FcHigh = FC_H;
            }
            MSB124X_WriteDspReg((MS_U16)T_CONFIG_FC_L, (MS_U8)u8FcLow);
            MSB124X_WriteDspReg((MS_U16)T_CONFIG_FC_H, (MS_U8)(u8FcHigh));
#endif

        //pMSB124X->pMSB124X_RegDVBT[(MS_U8)T_CONFIG_BW - (MS_U8)T_OPMODE_RFAGC_EN] = (MS_U8)bw_t;
        //pMSB124X->pMSB124X_RegDVBT[(MS_U8)T_PARAM_CHECK_SUM - (MS_U8)T_OPMODE_RFAGC_EN] = MDrv_DMD_MSB124X_DTV_DVBT_DSPReg_CRC();
        //MSB124X_WriteDspReg((MS_U8)T_PARAM_CHECK_SUM, pMSB124X->pMSB124X_RegDVBT[(MS_U8)T_PARAM_CHECK_SUM - (MS_U8)T_OPMODE_RFAGC_EN]);    // BW: 1->6M, 2->7M, 3->8M
        MSB124X_Active(1);
        MSB124X_Show_Version();//show dvbt fw version
    }

#if(TIMING_VERIFICATION == 1)
    tmm_12 = GIVE_ME_TIME;
    show_timer();
#endif
    return TRUE;
}

/*================================================
==         demod  MSB124X getting dvbt/dvbt2 param interface
=================================================*/
MS_BOOL MSB124X_DTV_DVB_T2_Get_L1_Parameter(MS_U16 * pu16L1_parameter, E_SIGNAL_TYPE eSignalType)
{
    MS_U8         u8Data = 0;

    if (MSB124X_Lock(E_DEVICE_DEMOD_DVB_T2, COFDM_FEC_LOCK) == TRUE)
    {

        if (eSignalType == T2_MODUL_MODE)
        {

            if (MSB124X_ReadReg(0x2700 + (0x47 * 2), &u8Data) == FALSE)
                return FALSE;

            *pu16L1_parameter  = (((MS_U16) u8Data) & (BIT5 | BIT4 | BIT3)) >> 3;

        }

        else  if (eSignalType == T2_CODE_RATE)
        {
            if (MSB124X_ReadReg(0x2700 + (0x47 * 2), &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16L1_parameter  = (((MS_U16) u8Data) & (BIT2 | BIT1 | BIT0));

        }
        else if (eSignalType == T2_PREAMBLE)
        {
            if (MSB124X_ReadReg(0x2700 + (0x30 * 2) + 1, &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16L1_parameter  = (((MS_U16) u8Data) & (BIT4)) >> 4;
        }
        else if (eSignalType == T2_S1_SIGNALLING)
        {
            if (MSB124X_ReadReg(0x2700 + (0x30 * 2) + 1, &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16L1_parameter  = (((MS_U16) u8Data) & (BIT3 | BIT2 | BIT1)) >> 1;
        }
        else if (eSignalType == T2_PILOT_PATTERN)
        {
            if (MSB124X_ReadReg(0x2700 + (0x36 * 2), &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16L1_parameter  = (((MS_U16) u8Data) & 0x0F);
        }
        else if (eSignalType == T2_BW_EXT)
        {
            if (MSB124X_ReadReg(0x2700 + (0x30 * 2) + 1, &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16L1_parameter  = (((MS_U16) u8Data) & (BIT0));
        }
        else if (eSignalType == T2_PAPR_REDUCTION)
        {
            if (MSB124X_ReadReg(0x2700 + (0x31 * 2), &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16L1_parameter  = (((MS_U16) u8Data) & 0xF0) >> 4;
        }
        else if (eSignalType == T2_OFDM_SYMBOLS_PER_FRAME)
        {
            if (MSB124X_ReadReg(0x2700 + (0x3C * 2), &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16L1_parameter  = (MS_U16) u8Data;
            if (MSB124X_ReadReg(0x2700 + (0x3C * 2) + 1, &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16L1_parameter |= (((MS_U16) u8Data) & 0x0F) << 8;
        }
        else if (eSignalType == T2_FFT_VALUE)
        {
            if (MSB124X_ReadReg(0x2700 + (0x30 * 2) + 1, &u8Data) == FALSE)
            {
                return FALSE;
            }
            if ((u8Data & (BIT3 | BIT2)) >> 2)
            {
                return FALSE;
            }
            *pu16L1_parameter  = (((MS_U16) u8Data) & (BIT7 | BIT6 | BIT5)) >> 5;
        }
        else if (eSignalType == T2_GUARD_INTERVAL)
        {
            if (MSB124X_ReadReg(0x2700 + (0x31 * 2), &u8Data) == FALSE)
            {
                return FALSE;
            }
            *pu16L1_parameter  = (((MS_U16) u8Data) & (BIT3 | BIT2 | BIT1)) >> 1;
        }
        else
        {
            return FALSE;
        }

        return TRUE;

    }
    return FALSE;
}

MS_BOOL MSB124X_DTV_DVB_T_GetSignalTpsInfo(MS_U16 *TPS_parameter)
{
    MS_U8 u8Temp;

    if (MSB124X_ReadReg(0x0F00 + 0x22, &u8Temp) == FALSE)
        return FALSE;

    if ((u8Temp & 0x02) != 0x02)
    {
        return FALSE; //TPS unlock
    }
    else
    {
        if (MSB124X_ReadReg(0x0F00 + 0x24, &u8Temp) == FALSE)
            return FALSE;

        *TPS_parameter = u8Temp & 0x03;         //Constellation (b2 ~ b0)
        *TPS_parameter |= (u8Temp & 0x70) >> 1; //Hierarchy (b5 ~ b3)

        if (MSB124X_ReadReg(0x0F00 + 0x25, &u8Temp) == FALSE)
            return FALSE;

        *TPS_parameter |= (MS_U16)(u8Temp & 0x07) << 6; //LP Code Rate (b8 ~ b6)
        *TPS_parameter |= (MS_U16)(u8Temp & 0x70) << 5; //HP Code Rate (b11 ~ b9)

        if (MSB124X_ReadReg(0x0F00 + 0x26, &u8Temp) == FALSE)
            return FALSE;

        *TPS_parameter |= (MS_U16)(u8Temp & 0x03) << 12; //GI (b13 ~ b12)
        *TPS_parameter |= (MS_U16)(u8Temp & 0x30) << 10;  //FFT ( b14)

        if (MSB124X_ReadReg(0x0F00 + 0x0C, &u8Temp) == FALSE)
            return FALSE;

        *TPS_parameter |= (MS_U16)(u8Temp & 0x08) << 12; //Priority(bit 15)

    }
    return TRUE;
}

MS_BOOL MSB124X_DTV_DVB_T2_GetSignalL1Info(MS_U64 *L1_Info)
{
    MS_BOOL bRet = TRUE;
    MS_U16    u16Data = 0;
#if MSB124X_DEBUG
    char*  cConStr[] = {"qpsk", "16qam", "64qam", "256qam"};
    char*  cCRStr[] = {"1_2", "3_5", "2_3", "3_4", "4_5", "5_6"};
    char*  cGIStr[] = {"1_32", "1_16", "1_8", "1_4", "1_128", "19_128", "19_256"};
    char*  cFFTStr[] = {"2k", "8k", "4k", "1k", "16k", "32k", "8k", "32k"};
    char*  cPreAStr[] = {"mixed", "not_mixed"};
    char*  cS1SStr[] = {"t2_siso", "t2_miso", "non_t2", "reserved"};
    char*  cPPSStr[] = {"PP1", "PP2", "PP3", "PP4", "PP5", "PP6", "PP7", "PP8", "reserved"};
    char*  cBWStr[] = {"normal", "extension"};
    char*  cPAPRStr[] = {"none", "ace", "tr", "tr_and_ace", "reserved"};
#endif
    if (MSB124X_DTV_DVB_T2_Get_L1_Parameter(&u16Data, T2_MODUL_MODE) == FALSE)
    {
        PRINTE(("TS_MODUL_MODE Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x07;
    *L1_Info = (MS_U64)(u16Data);
    PRINTE(("Constellation:%s\n", cConStr[u16Data]));

    if (MSB124X_DTV_DVB_T2_Get_L1_Parameter(&u16Data, T2_CODE_RATE) == FALSE)
    {
        PRINTE(("TS_CODE_RATE Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x07;
    *L1_Info |= (MS_U64)(u16Data << 3);
    PRINTE(("Code Rate:%s\n", cCRStr[u16Data]));

    if (MSB124X_DTV_DVB_T2_Get_L1_Parameter(&u16Data, T2_GUARD_INTERVAL) == FALSE)
    {
        PRINTE(("TS_T2_GUARD_INTERVAL Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x07;
    *L1_Info |= (MS_U64)(u16Data << 6);
    PRINTE(("GI:%s\n", cGIStr[u16Data]));

    if (MSB124X_DTV_DVB_T2_Get_L1_Parameter(&u16Data, T2_FFT_VALUE) == FALSE)
    {
        PRINTE(("TS_T2_FFT_VALUE Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x07;
    *L1_Info |= (MS_U64)(u16Data << 9);
    PRINTE(("FFT:%s\n", cFFTStr[u16Data]));

    if (MSB124X_DTV_DVB_T2_Get_L1_Parameter(&u16Data, T2_PREAMBLE) == FALSE)
    {
        PRINTE(("TS_PREAMBLE Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x01;
    *L1_Info |= (MS_U64)(u16Data << 12);
    PRINTE(("Preamble:%s\n", cPreAStr[u16Data]));

    if (MSB124X_DTV_DVB_T2_Get_L1_Parameter(&u16Data, T2_S1_SIGNALLING) == FALSE)
    {
        PRINTE(("TS_S1_SIGNALLING Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x03;
    if (u16Data > 2)
        u16Data = 3;
    *L1_Info |= (MS_U64)(u16Data << 13);
    PRINTE(("S1Signalling:%s\n", cS1SStr[u16Data]));

    if (MSB124X_DTV_DVB_T2_Get_L1_Parameter(&u16Data, T2_PILOT_PATTERN) == FALSE)
    {
        PRINTE(("TS_PILOT_PATTERN Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x0F;
    if (u16Data > 7)
        u16Data = 8;
    *L1_Info |= (MS_U64)(u16Data << 15);
    PRINTE(("PilotPattern:%s\n", cPPSStr[u16Data]));

    if (MSB124X_DTV_DVB_T2_Get_L1_Parameter(&u16Data, T2_BW_EXT) == FALSE)
    {
        PRINTE(("TS_BW_EXT Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x01;
    *L1_Info |= (MS_U64)(u16Data << 19);
    PRINTE(("BW EXT:%s\n", cBWStr[u16Data]));

    if (MSB124X_DTV_DVB_T2_Get_L1_Parameter(&u16Data, T2_PAPR_REDUCTION) == FALSE)
    {
        PRINTE(("TS_PAPR_REDUCTION Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x07;
    if (u16Data > 3)
        u16Data = 4;
    *L1_Info |= (MS_U64)(u16Data << 20);
    PRINTE(("PAPR:%s\n", cPAPRStr[u16Data]));

    if (MSB124X_DTV_DVB_T2_Get_L1_Parameter(&u16Data, T2_OFDM_SYMBOLS_PER_FRAME) == FALSE)
    {
        PRINTE(("TS_OFDM_SYMBOLS_PER_FRAME Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0xFFF;
    *L1_Info |= (MS_U64)(u16Data << 23);
    PRINTE(("OFDM Symbols:%u\n", u16Data));

    return bRet;
}

MS_BOOL MSB124X_DTV_GetCellID(MS_U16 *pCellID)
{
    MS_U8 id = 0;
    MS_U8 status = TRUE;
    MS_U16  cell_id  = 0;
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !\n"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("[%s]pMSB124X have not inited !!!\n", __FUNCTION__));
        return FALSE;
    }

    if (pMSB124X->enDemodType == E_DEVICE_DEMOD_DVB_T2)
    {
        status &= MSB124X_ReadReg(0x2771, &id);
        cell_id = (MS_U16)id;

        status &= MSB124X_ReadReg(0x0f70, &id);
        cell_id |= (MS_U16)id << 8;
    }
    else if (pMSB124X->enDemodType == E_DEVICE_DEMOD_DVB_T)
    {
        status &= MSB124X_WriteReg(0x0ffe, 0x01);

        status &= MSB124X_ReadReg(0x0f2b, &id);
        cell_id = (MS_U16)id;

        status &= MSB124X_ReadReg(0x0f2a, &id);
        cell_id |= (MS_U16)id << 8;

        status &= MSB124X_WriteReg(0x0ffe, 0x00);

    }

    *pCellID = cell_id;

    if (status)
    {
        printf(" @MSB124X_GetCellId OK\n");
        return  TRUE;
    }
    else
    {
        printf(" @MSB124X_GetCellId NG\n");
        return FALSE;
    }

}

MS_BOOL MSB124X_DTV_GetSNR_F(float *fSNR)
{
    MSB124X_DTV_GetSNR();
    *fSNR = g_MSB124X_fSNR;
    return TRUE;
}

MS_BOOL MSB124X_DTV_Get_Current_Plp_Id(MS_U8 *plp_id)
{
    MS_BOOL  rbet = TRUE;
    MS_U8    reg;

    rbet &= MSB124X_ReadDspReg((MS_U16)E_T2_PLP_ID, &reg);
    *plp_id = reg;
    return rbet;
}

void MSB124X_DTV_ControlTsOutput(MS_BOOL bEnable)
{
    if (bEnable)
    {
        MSB124X_WriteReg(0x0900 + (0x2D * 2), 0xFF);
    }
    else
    {
        MSB124X_WriteReg(0x0900 + (0x2D * 2), 0x00);
    }
}

/****************************************************************************
**function:
**
**
****************************************************************************/
MS_U16 MSB124X_Get_FreqOffset(float *pFreqOff, MS_U8 u8BW)
{
    MS_U8 status = TRUE;
    //DVB-T
    float   N, FreqB;
    float   FreqCfoTd, FreqCfoFd, FreqIcfo;
    MS_U32  RegCfoTd, RegCfoFd, RegIcfo;
    MS_U8 reg_frz, reg, reg_debug_sel;
    MS_S32 RegTotalCfo;
    EN_DEVICE_DEMOD_TYPE eSystems;

    FreqB = (float)u8BW * 8.0 / 7.0;
    eSystems = MSB124X_GetCurrentDemodulatorType();
    PRINTE(("\nBW = %d\n", u8BW));
    if (eSystems == E_DEVICE_DEMOD_DVB_T2)
    {
        //debug select
        status &= MSB124X_ReadReg(0x3E5E, &reg_debug_sel);
        reg_debug_sel &= 0xCF;
        reg_debug_sel |= 0x10;
        status &= MSB124X_WriteReg(0x3E5E, reg_debug_sel);

        // set freeze
        status &= MSB124X_WriteReg2bytes(0x3E00 + (0x02) * 2, 0x8000);
        status &= MSB124X_ReadReg(0x3E5B, &reg);
        RegTotalCfo = reg & 0x0F;

        status &= MSB124X_ReadReg(0x3E5A, &reg);
        RegTotalCfo = (RegTotalCfo << 8) | reg;
        status &= MSB124X_ReadReg(0x3E59, &reg);
        RegTotalCfo = (RegTotalCfo << 8) | reg;
        status &= MSB124X_ReadReg(0x3E58, &reg);
        RegTotalCfo = (RegTotalCfo << 8) | reg;

        // release freeze
        status &= MSB124X_WriteReg2bytes(0x3E00 + (0x02) * 2, 0x0000);

        if (RegTotalCfo >= 0x4000000)
            RegTotalCfo = RegTotalCfo - 0x8000000;

        *pFreqOff = (float)RegTotalCfo * FreqB * 0.00000745;

        PRINTE(("$$$$$$$$$$$$$$$$$$$$  DVB-T2 CFOE = %f\n", *pFreqOff));
        return status;
    }
    else if (eSystems == E_DEVICE_DEMOD_DVB_T)
    {
        // freeze
        status &= MSB124X_ReadReg(0x0E04 + 1, &reg_frz);
        status &= MSB124X_WriteReg(0x0E04 + 1, reg_frz | 0x80);

        status &= MSB124X_ReadReg(0x0E28 + 2, &reg);
        RegCfoTd = reg;

        status &= MSB124X_ReadReg(0x0E28 + 1, &reg);
        RegCfoTd = (RegCfoTd << 8) | reg;

        status &= MSB124X_ReadReg(0x0E28, &reg);
        RegCfoTd = (RegCfoTd << 8) | reg;

        // release
        status &= MSB124X_ReadReg(0x0E04 + 1, &reg_frz);
        status &= MSB124X_WriteReg(0x0E04 + 1, reg_frz | 0x80);

        FreqCfoTd = (float)RegCfoTd;

        if (RegCfoTd & 0x800000)
            FreqCfoTd = FreqCfoTd - (float)0x1000000;

        FreqCfoTd = FreqCfoTd * FreqB * 0.00011642;

        status &= MSB124X_ReadReg(0x0ffe, &reg_frz);
        status &= MSB124X_WriteReg(0x0ffe, reg_frz | 0x01);

        status &= MSB124X_WriteReg(0x0fff, 0x01);

        status &= MSB124X_ReadReg(0x0f33, &reg);
        RegCfoFd = reg;

        status &= MSB124X_ReadReg(0x0f32, &reg);
        RegCfoFd = (RegCfoFd << 8) | reg;

        status &= MSB124X_ReadReg(0x0f31, &reg);
        RegCfoFd = (RegCfoFd << 8) | reg;

        FreqCfoFd = (float)RegCfoFd;

        if (RegCfoFd & 0x800000)
            FreqCfoFd = FreqCfoFd - (float)0x1000000;

        FreqCfoFd = FreqCfoFd * FreqB * 0.00011642;

        status &= MSB124X_ReadReg(0x0f19, &reg);
        RegIcfo = reg & 0x07;

        status &= MSB124X_ReadReg(0x0f18, &reg);
        RegIcfo = (RegIcfo << 8) | reg;

        FreqIcfo = (float)RegIcfo;

        if (RegIcfo & 0x400)
            FreqIcfo = FreqIcfo - (float)0x800;

        status &= MSB124X_ReadReg(0x0f26, &reg);
        reg = reg & 0x30;

        switch (reg)
        {
        case 0x00:
            N = 2048;
            break;
        case 0x20:
            N = 4096;
            break;
        case 0x10:
        default:
            N = 8192;
            break;
        }

        FreqIcfo = FreqIcfo * FreqB / N * 1000;     //unit: kHz
        status &= MSB124X_WriteReg(0x0ffe, reg_frz & (~0x01));
        status &= MSB124X_WriteReg(0x0fff, 0x01);

        *pFreqOff = FreqIcfo + (FreqCfoFd + FreqCfoTd) / 1000;

        status &= MSB124X_ReadReg(0x3E5E, &reg);

        if (reg & 0x01)
            *pFreqOff = -*pFreqOff;

        PRINTE(("$$$$$$$$$$$$$$$$$$$$  DVB-T CFOE = %f\n", *pFreqOff));

    }
    else
        ;

    if (status)
    {
        PRINTE((" @MSB124X_Get_FreqOffset OK\n"));
        return  TRUE;
    }
    else
    {
        PRINTE((" @MSB124X_Get_FreqOffset NG\n"));
        return FALSE;
    }
}

MS_U8 MSB124X_Get_Packet_Error(MS_U16 *u16_data)
{
    MS_U8     status = TRUE;
    MS_U8     reg = 0, reg_frz;
    MS_U16      PktErr = 0;

    if (E_DEVICE_DEMOD_DVB_T2 == MSB124X_GetCurrentDemodulatorType())
    {
        //freeze
        status &= MSB124X_WriteReg(0x2604, 0x01);
        //read packet error
        status &= MSB124X_ReadReg(0x265B, &reg);
        PktErr = reg;
        status &= MSB124X_ReadReg(0x265A, &reg);
        PktErr = (PktErr << 8) | reg;

        *u16_data = PktErr;
        //release
        status &= MSB124X_WriteReg(0x2604, 0x00);
    }
    else
    {
        reg_frz = 0;
        // bank 7 0x32 [7] reg_bit_err_num_freeze
        status &= MSB124X_ReadReg(0x1132, &reg_frz);
        status &= MSB124X_WriteReg(0x1132, reg_frz | 0x80);

        // bank 7 0x3e [7:0] reg_uncrt_pkt_num_7_0
        //         [15:8] reg_uncrt_pkt_num_15_8
        status &= MSB124X_ReadReg(0x113F, &reg);
        PktErr = reg;

        status &= MSB124X_ReadReg(0x113E, &reg);
        PktErr = (PktErr << 8) | reg;

        *u16_data = PktErr;

        // bank 7 0x32 [7] reg_bit_err_num_freeze
        status &= MSB124X_WriteReg(0x1132, reg_frz);

        PRINTE(("===================>MSB PktErr = %d \n ", (int)PktErr));
    }
    if (status)
    {
        PRINTE((" @MSB124X_Get_Packet_Error OK\n"));
        return  TRUE;
    }
    else
    {
        PRINTE((" @MSB124X_Get_Packet_Error NG\n"));
        return FALSE;
    }
}

/********************************************
Function: To control MSB1233C/1236C GPIO pin for input_out mode
Parameter: Pin_sel   0->GPIO0, 1->RFAGC
                 Ctrl_Para  0->switch to output mode  1->input mode
                 Data_Para  input/output data
*********************************************/
MS_BOOL MSB124X_DTV_GPIO_Control(MS_U8 Pin_sel, MS_U8 Ctrl_Para, MS_U8 *pData_Para)
{
    MS_U16 pin_addr, in_addr, out_addr;
    MS_U8 u8_read, u8_write, bit_num;
    MS_BOOL status = TRUE;

    //select GPIO pin contol
    switch (Pin_sel)
    {
    case 0:
        //set GPIO0 pin
        pin_addr = 0x0900 + (0x64 * 2);
        in_addr = 0x0900 + (0x65 * 2);
        out_addr = 0x0900 + (0x63 * 2);
        bit_num = 0x00;
        break;
    case 1:
        //set RFAGC pin
        pin_addr = 0x0a00 + (0x22 * 2);
        in_addr = 0x0a00 + (0x22 * 2) + 1;
        out_addr = 0x0a00 + (0x22 * 2);
        bit_num = 0x01;
        break;
    default:
        PRINTE((" @MSB124X_DTV_GPIO_Control unknown pin selection\n"));
        return FALSE;
    }

    //set input/output mode
    status &= MSB124X_ReadReg(pin_addr, &u8_read);
    u8_write = u8_read & ~(1 << bit_num);
    u8_write = u8_write | (Ctrl_Para << bit_num);
    status &= MSB124X_WriteReg(pin_addr, u8_write);

    //if RFAGC pin, set different bit_num
    if (Pin_sel == 1)
        bit_num = 0x00;

    //read/write data
    if (Ctrl_Para == 0)
    {
        //write output data
        status &= MSB124X_ReadReg(out_addr, &u8_read);
        u8_write = u8_read & ~(1 << bit_num);
        u8_write = u8_write | (*pData_Para << bit_num);
        status &= MSB124X_WriteReg(out_addr, u8_write);
    }
    else
    {
        //read input data
        status &= MSB124X_ReadReg(in_addr, &u8_read);
        *pData_Para = u8_read & (1 << bit_num);
        *pData_Para = *pData_Para >> bit_num;
    }

    if (status)
    {
        PRINTE((" @MSB124X_DTV_GPIO_Control OK\n"));
        return  TRUE;
    }
    else
    {
        PRINTE((" @MSB124X_DTV_GPIO_Control NG\n"));
        return FALSE;
    }
}

/*================================================
==                    read demod chip version interface
=================================================*/
static MS_BOOL MSB124X_ReadReg_Chip(MS_U16 u16Addr, MS_U8 *pu8Data)
{
    MS_BOOL bRet;
    MS_U8   u8MsbData[6];

    u8MsbData[0] = 0x10;
    u8MsbData[1] = 0x00;
    u8MsbData[2] = 0x00;
    u8MsbData[3] = (u16Addr >> 8) & 0xff;
    u8MsbData[4] = u16Addr & 0xff;
    u8MsbData[0] = 0x35;

    bRet = MDrv_IIC_Write(DEMOD_DYNAMIC_SLAVE_ID_1, NULL, 0, u8MsbData, 1);
    u8MsbData[0] = 0x10;
    bRet = MDrv_IIC_Write(DEMOD_DYNAMIC_SLAVE_ID_1, NULL, 0, u8MsbData, 5);
    bRet = MDrv_IIC_Read(DEMOD_DYNAMIC_SLAVE_ID_1, NULL, 0, pu8Data, 1);
    u8MsbData[0] = 0x34;
    bRet = MDrv_IIC_Write(DEMOD_DYNAMIC_SLAVE_ID_1, NULL, 0, u8MsbData, 1);
    return bRet;
}

static MS_U8 MSB124X_DTV_GetHWVer(void)
{
    MS_BOOL status = TRUE;
    MS_U8 reg = 0;
    MS_U8 u8Chip = 0;

    status &= MSB124X_ReadReg_Chip(0x0900, &reg);
    if (reg == 0x6F)
        u8Chip = 0x01;
    else if (reg == 0x55)
        u8Chip = 0x02;
    else
        u8Chip = 0xff;

    return u8Chip;
}

/********************************************
Function: To get chip version
Parameter: pu8Chip   0x01->MSB1230, 0x02->MSB124X,
                    0xff ->unknown
*********************************************/
MS_BOOL MDrv_Demo_GetChip(MS_U8 *pu8Chip)
{
    MSB124X_I2C_CH_Reset(3);
    *pu8Chip = MSB124X_DTV_GetHWVer();
    return TRUE;
}

/****************************************************************************
**function: Read demod related information
**      Get one time after demod lock
**              Pilot pattern
**              Extended
**              P1 interval
**              FFT/GI
**              P2_Dec P2_DX Data_Dec, Data_DX
**              ACI_DET/CCI_DET/Aligned
**              right most/mid point/left most/CHlen/BS/CS/FDSA_His
**              SFO/CFO
**              SNR method
**              SNR value
**              Data eflag
**              L1 parser
**      Polling after demod lock
**              right most/mid point/left most/CHlen/BS/CS/FDSA_His
**              SFO/CFO
**              SNR method
**              SNR value
**              Data eflag
****************************************************************************/
void MDrv_Demod_Get_Debug_Info_get_once(void)
{
#if 0
    MS_U8 u8Data, reg;
    MS_U16 u16Data;
    MS_U32 u32Data;
    MS_U8 status = TRUE;
    MS_U16  snr_ave_num = 0;
    //MS_U32 FW_VER;

    float   f_snr = (float)0.0;
    float   fSNRDivider[] = {1024 * 2, 2048 * 2, 4096 * 2, 8192 * 2, 16384 * 2, 32768 * 2, 32768 * 2, 32768 * 2};

    MSB124X_Show_Version();
    //printf("Demod FWT2 Version is %x\n", FW_VER);

    //State Show
    status &= MSB124X_ReadReg(0x0990, &u8Data);
    printf("[DVBT2]: State: %d\n", (u8Data & 0x0F));

    // pilot pattern, extended
    status &= MSB124X_ReadReg(0x2510, &u8Data);
    printf("[DVBT2]: PP: %d, Extended: %d\n", u8Data & 0x07, ((u8Data & 0x08) >> 3));

    // P1 interval
    status &= MSB124X_ReadReg(0x24BB, &u8Data);
    u16Data = u8Data;
    status &= MSB124X_ReadReg(0x24BA, &u8Data);
    u16Data = (u16Data << 8) | u8Data;
    printf("[DVBT2]: P1 interval: %d\n", ((u16Data & 0xFFF0) >> 4));

    // FFT/GI
    status &= MSB124X_ReadReg(0x2481, &u8Data);
    printf("[DVBT2]: FFT: %d, GI: %d\n", u8Data & 0x0F, ((u8Data & 0xF0) >> 4));

    // P2_dec, P2_dx, Data_dec, Data_dx
    status &= MSB124X_ReadReg(0x0997, &u8Data);
    u16Data = u8Data;
    status &= MSB124X_ReadReg(0x0996, &u8Data);
    u16Data = (u16Data << 8) | u8Data;
    printf("[DVBT2]: P2_Dec %d, P2_Dx: %d, Data_Dec: %d, Data_Dx: %d\n", u16Data & 0x0007, ((u8Data & 0x0078) >> 3), ((u8Data & 0x0380) >> 7), ((u8Data & 0x3c00) >> 10));

    // ACI_DET, CCI_DET, Aligned
    status &= MSB124X_ReadReg(0x0995, &u8Data);
    u16Data = u8Data;
    status &= MSB124X_ReadReg(0x0994, &u8Data);
    u16Data = (u16Data << 8) | u8Data;
    printf("[DVBT2]: ACI_DET %d, CCI_DET: %d, Aligned: %d\n", ((u8Data & 0x0020) >> 5), ((u8Data & 0x01C0) >> 6), ((u8Data & 0x0800) >> 11));

    // IIS enable, TD_coeff
    status &= MSB124X_ReadReg(0x3EA0, &reg);
    printf("[DVBT2]: IIS_enable = %d \n ", (reg&0x01));
    status &= MSB124X_ReadReg(0x1928, &reg);
    printf("[DVBT2]: TD_Ceoff = %d \n ", (reg&0x01));

    // right most, left most, midpoint, chlen, BS, CS, FDSA_HIS
    // set freeze
    status &= MSB124X_ReadReg(0x25FE, &reg);
    status &= MSB124X_WriteReg(0x25FE, reg | 0x01);
    // load
    status &= MSB124X_WriteReg(0x25FF, 0x01);

    status &= MSB124X_ReadReg(0x2581, &u8Data);
    u16Data = u8Data;
    status &= MSB124X_ReadReg(0x2580, &u8Data);
    u16Data = (u16Data << 8) | u8Data;
    printf("[DVBT2]: Right most: %d\n", u16Data);

    status &= MSB124X_ReadReg(0x25B5, &u8Data);
    u16Data = u8Data;
    status &= MSB124X_ReadReg(0x25B4, &u8Data);
    u16Data = (u16Data << 8) | u8Data;
    printf("[DVBT2]: Mid point: %d\n", u16Data);

    status &= MSB124X_ReadReg(0x2583, &u8Data);
    u16Data = u8Data;
    status &= MSB124X_ReadReg(0x2582, &u8Data);
    u16Data = (u16Data << 8) | u8Data;
    printf("[DVBT2]: Left most: %d\n", u16Data);

    status &= MSB124X_ReadReg(0x2585, &u8Data);
    u16Data = u8Data;
    status &= MSB124X_ReadReg(0x2584, &u8Data);
    u16Data = (u16Data << 8) | u8Data;
    printf("[DVBT2]: Chlen: %d\n", u16Data);

    status &= MSB124X_ReadReg(0x2587, &u8Data);
    u16Data = u8Data;
    status &= MSB124X_ReadReg(0x2586, &u8Data);
    u16Data = (u16Data << 8) | u8Data;
    printf("[DVBT2]: BS: 0x%x\n", u16Data);

    status &= MSB124X_ReadReg(0x2589, &u8Data);
    u16Data = u8Data;
    status &= MSB124X_ReadReg(0x2588, &u8Data);
    u16Data = (u16Data << 8) | u8Data;
    printf("[DVBT2]: CS: 0x%x\n", u16Data);

    status &= MSB124X_ReadReg(0x258A, &u8Data);
    u16Data = u8Data;
    printf("[DVBT2]: FDSA_HIS: 0x%x\n", u8Data & 0x1F);

    // unfreeze
    status &= MSB124X_WriteReg(0x25FE, 0x00);
    // load
    status &= MSB124X_WriteReg(0x25FF, 0x01);

    // CompareSNR_case, MinCase
    status &= MSB124X_ReadDspReg(0x0301, &u8Data);
    u32Data = u8Data;
    status &= MSB124X_ReadDspReg(0x0302, &u8Data);
    u32Data = (u32Data << 8)| u8Data;
    status &= MSB124X_ReadDspReg(0x0303, &u8Data);
    u32Data = (u32Data << 8)| u8Data;
    status &= MSB124X_ReadDspReg(0x0304, &u8Data);
    u32Data = (u32Data << 8)| u8Data;
    printf("[DVBT2]: MainCenter: %d, ", u32Data);
    status &= MSB124X_ReadDspReg(0x0315, &u8Data);
    u32Data = u8Data;
    status &= MSB124X_ReadDspReg(0x0316, &u8Data);
    u32Data = (u32Data << 8)| u8Data;
    status &= MSB124X_ReadDspReg(0x0317, &u8Data);
    u32Data = (u32Data << 8)| u8Data;
    status &= MSB124X_ReadDspReg(0x0318, &u8Data);
    u32Data = (u32Data << 8)| u8Data;
    printf("MainCenterMin: %d\n", u32Data);

    status &= MSB124X_ReadDspReg(0x0319, &u8Data);
    printf("[DVBT2]: CompareSNR_history: 0x%x, ", u8Data);
    status &= MSB124X_ReadDspReg(0x031A, &u8Data);
    printf("Min_Case: %d, ", u8Data);
    status &= MSB124X_ReadDspReg(0x031B, &u8Data);
    printf("CompareSNR_Case: %d\n", u8Data);

    // CFO, SFO
    // SNR method
    status &= MSB124X_ReadReg(0x2805, &u8Data);
    u16Data = u8Data;
    status &= MSB124X_ReadReg(0x2804, &u8Data);
    u16Data = (u16Data << 8) | u8Data;
    printf("[DVBT2]: SNR method: 0x%x\n", u16Data);

    // SNR value
    // set freeze
    status &= MSB124X_ReadReg(0x2802, &reg);
    reg |= 0x06;
    status &= MSB124X_WriteReg(0x2802, reg);

    status &= MSB124X_ReadReg(0x281F, &u8Data);
    u32Data = u8Data;
    status &= MSB124X_ReadReg(0x281E, &u8Data);
    u32Data = (u32Data << 8) | u8Data;
    status &= MSB124X_ReadReg(0x281D, &u8Data);
    u32Data = (u32Data << 8) | u8Data;
    status &= MSB124X_ReadReg(0x281C, &u8Data);
    u32Data = (u32Data << 8) | u8Data;

    // unfreeze
    status &= MSB124X_ReadReg(0x2802, &reg);
    reg &= (0xff - 0x04);
    status &= MSB124X_WriteReg(0x2802, reg);

    u32Data &= 0x1FFFFFFF;
    if (u32Data == 0)
    {
        u32Data = 1;
    }

    status &= MSB124X_ReadReg(0x2814, &reg);
    snr_ave_num = reg & 0x07;

    f_snr = (float)10.0 * log10((float)u32Data / fSNRDivider[snr_ave_num]);

    printf("[DVBT2]: SNR: %f\n", f_snr);
/*
    //T2_SNR_H
    status &= MSB124X_ReadDspReg(0x00f4, &u8Data);
    u16Data = u8Data;
    //T2_SNR_L
    status &= MSB124X_ReadDspReg(0x00f3, &u8Data);
    u16Data = (u16Data << 8)| u8Data;
    f_snr = (float)u16Data/100.0;
    printf("[DVBT2]: Avg_SNR: %f\n", f_snr);
*/
    // Data eflag2
    // set freeze
    status &= MSB124X_ReadReg(0x2604, &reg);
    reg |= 0x01;
    status &= MSB124X_WriteReg(0x2604, reg);

    status &= MSB124X_ReadReg(0x265B, &u8Data);
    u16Data = u8Data;
    status &= MSB124X_ReadReg(0x265A, &u8Data);
    u16Data = (u16Data << 8) | u8Data;

    // unfreeze
    status &= MSB124X_ReadReg(0x2604, &reg);
    reg &= (0xff - 0x01);
    status &= MSB124X_WriteReg(0x2604, reg);

    printf("[DVBT2]: Data eflag2: %d\n", u16Data);

    // get L1 parser
    status &= MSB124X_WriteReg(0x2706, 0x01);

    status &= MSB124X_ReadReg(0x2705, &u8Data);
    printf("[DVBT2]: L1 mod: %d\n", u8Data & 0x0F);

    status &= MSB124X_ReadReg(0x278A, &u8Data);
    printf("[DVBT2]: PLP ID: %d\n", u8Data);

    status &= MSB124X_ReadReg(0x278B, &u8Data);
    printf("[DVBT2]: PLP type: %d, PLP Payload: %d\n", u8Data & 0x07, ((u8Data & 0x18) >> 3));

    status &= MSB124X_ReadReg(0x278D, &u8Data);
    printf("[DVBT2]: Group ID: %d\n", u8Data);

    status &= MSB124X_ReadReg(0x278F, &u8Data);
    u16Data = u8Data;
    status &= MSB124X_ReadReg(0x278E, &u8Data);
    u16Data = (u16Data << 8) | u8Data;
    printf("[DVBT2]: PLP CR: %d, PLP mod: %d, PLP rotation: %d, PLP fec type: %d\n", u16Data & 0x0007, ((u16Data & 0x0038) >> 3), ((u16Data & 0x0040) >> 5), ((u16Data & 0x0180) >> 7));

    status &= MSB124X_ReadReg(0x2791, &u8Data);
    printf("[DVBT2]: IL type: %d\n", ((u8Data & 0x10) >> 4));

    status &= MSB124X_ReadReg(0x2792, &u8Data);
    printf("[DVBT2]: Frame interval: %d\n", u8Data);

    status &= MSB124X_ReadReg(0x2793, &u8Data);
    printf("[DVBT2]: IL Len: %d\n", u8Data);

    status &= MSB124X_ReadReg(0x27AB, &u8Data);
    u16Data = u8Data;
    status &= MSB124X_ReadReg(0x27AA, &u8Data);
    u16Data = (u16Data << 8) | u8Data;

    printf("[DVBT2]: num of blocks: %d\n", u16Data & 0x03FF);

    status &= MSB124X_ReadReg(0x2779, &u8Data);
    u16Data = u8Data;
    status &= MSB124X_ReadReg(0x2778, &u8Data);
    u16Data = (u16Data << 8) | u8Data;

    printf("[DVBT2]: num of data symbols: %d\n", u16Data & 0x0FFF);

    status &= MSB124X_ReadReg(0x2791, &u8Data);
    u16Data = u8Data;
    status &= MSB124X_ReadReg(0x2790, &u8Data);
    u16Data = (u16Data << 8) | u8Data;

    printf("[DVBT2]: num of block: %d\n", u16Data & 0x03FF);
#endif
}

MS_U16 MDrv_Demod_Get_FreqOffset(float *pFreqOff, MS_U8 u8BW)
{
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("pMSB124X have not inited !!!"));
        return FALSE;
    }
    if (MsOS_ObtainMutex(pMSB124X->s32_MSB124X_Mutex, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        PRINTE(("MDrv_Demod_SetScanTypeStatus:Obtain mutex failed !!!\n"));
        return FALSE;
    }

    MSB124X_Get_FreqOffset(pFreqOff, u8BW);

    MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);
    return TRUE;
}

MS_U8 MDrv_Demod_Get_Packet_Error(MS_U16 *u16_data)
{
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("pMSB124X have not inited !!!"));
        return FALSE;
    }
    if (MsOS_ObtainMutex(pMSB124X->s32_MSB124X_Mutex, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        PRINTE(("MDrv_Demod_SetScanTypeStatus:Obtain mutex failed !!!\n"));
        return FALSE;
    }

    MSB124X_Get_Packet_Error(u16_data);

    MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);
    return TRUE;
}

MS_BOOL MDrv_Demod_SetScanTypeStatus(MS_U8 status)
{
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("pMSB124X have not inited !!!"));
        return FALSE;
    }
    if (MsOS_ObtainMutex(pMSB124X->s32_MSB124X_Mutex, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        PRINTE(("MDrv_Demod_SetScanTypeStatus:Obtain mutex failed !!!\n"));
        return FALSE;
    }

    switch (status)
    {
    case 0:
        pMSB124X->u8ScanStatus = 0;
        break;
    case 1:
        pMSB124X->u8ScanStatus = 1;
        break;

    case 2:
        pMSB124X->u8ScanStatus = 2;
        break;

    case 3:
        pMSB124X->u8ScanStatus = 3;
        break;
    default:
        MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);
        return FALSE;

    }
    MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);
    return TRUE;
}

MS_U8 MDrv_Demod_GetScanTypeStatus(void)
{
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("pMSB124X have not inited !!!"));
        return FALSE;
    }

    return pMSB124X->u8ScanStatus;
}

MS_BOOL MDrv_Demod_InitParameter(void)
{
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("pMSB124X have not inited !!!"));
        return FALSE;
    }
    if (MsOS_ObtainMutex(pMSB124X->s32_MSB124X_Mutex, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        PRINTE(("Obtain mutex failed !!!"));
        return FALSE;
    }
    pMSB124X->u8ScanStatus = 0;
    MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);
    return TRUE;
}

MS_U8 MDrv_Demod_GetPlpIDSize(void)
{
    MS_U8    u8Size = 0;
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("pMSB124X have not inited !!!"));
        return FALSE;
    }
    if (MsOS_ObtainMutex(pMSB124X->s32_MSB124X_Mutex, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        PRINTE(("Obtain mutex failed !!!"));
        return FALSE;
    }
    u8Size = pMSB124X->PlpIDSize;
    PRINTE(("[end],PlpID size %d", u8Size));
    MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);
    return u8Size;
}

MS_U8 MDrv_Demod_GetPlpIDList(void)
{
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !"));
        return 0;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("[%s]pMSB124X have not inited !!!\n", __FUNCTION__));
        return 0;
    }

    if (MsOS_ObtainMutex(pMSB124X->s32_MSB124X_Mutex, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        PRINTE(("MDrv_Demod_Open:Obtain mutex failed !!!\n"));
        return FALSE;
    }
    if (FALSE == MSB124X_GetPlpIDList())
        pMSB124X->PlpIDSize = 0;

    MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);
    return pMSB124X->PlpIDSize;
}

MS_U8 MDrv_Demod_GetNextPlpID(MS_U8 u8Index)
{
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    MS_U8 u8PlpID;

    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !\n"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("[%s]pMSB124X have not inited !!!\n", __FUNCTION__));
        return FALSE;
    }
    if (MsOS_ObtainMutex(pMSB124X->s32_MSB124X_Mutex, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        PRINTE(("MDrv_Demod_Open:Obtain mutex failed !!!\n"));
        return FALSE;
    }

    u8PlpID = pMSB124X->PlpIDList[u8Index];
    MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);
    return u8PlpID;
}

MS_BOOL MDrv_Demod_I2C_ByPass(MS_BOOL bOn)
{
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("pMSB124X have not inited !!!"));
        return FALSE;
    }
    if (MsOS_ObtainMutex(pMSB124X->s32_MSB124X_Mutex, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        PRINTE(("MDrv_Demod_SetScanTypeStatus:Obtain mutex failed !!!\n"));
        return FALSE;
    }

    MSB124X_IIC_Bypass_Mode(bOn);

    MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);
    return TRUE;
}

MS_BOOL MDrv_Demod_SetCurrentDemodType(MS_U8  type)
{
    if (E_DEMOD_TYPE_T == type)
    {
        return MSB124X_SetCurrentDemodulatorType(E_DEVICE_DEMOD_DVB_T);
    }
    else
    {
        return MSB124X_SetCurrentDemodulatorType(E_DEVICE_DEMOD_DVB_T2);
    }
}

MS_U8 MDrv_Demod_GetCurrentDemodType(void)
{
    if (E_DEVICE_DEMOD_DVB_T == MSB124X_GetCurrentDemodulatorType())
    {
        return E_DEMOD_TYPE_T;
    }
    else
    {
        return E_DEMOD_TYPE_T2;
    }
}

MS_BOOL MDrv_Demod_Open(void)
{
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !\n"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("[%s]pMSB124X have not inited !!!\n", __FUNCTION__));
        return FALSE;
    }
    if (MsOS_ObtainMutex(pMSB124X->s32_MSB124X_Mutex, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        PRINTE(("MDrv_Demod_Open:Obtain mutex failed !!!\n"));
        return FALSE;
    }

    pMSB124X->bOpen = TRUE;
    MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);

    return TRUE;
}

MS_BOOL MDrv_Demod_PowerOnOff(MS_BOOL bPowerOn)
{

    if (bPowerOn)
    {
#ifdef GPIO_DEMOD_RST
        mdrv_gpio_set_high(GPIO_DEMOD_RST);
#else
        mdrv_gpio_set_high(GPIO_FE_RST);
#endif
    }
    else
    {
#ifdef GPIO_DEMOD_RST
        mdrv_gpio_set_low(GPIO_DEMOD_RST);
#else
        mdrv_gpio_set_low(GPIO_FE_RST);
#endif
    }

    return TRUE;
}

MS_BOOL MDrv_Demod_Close(void)
{
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !\n"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("[%s]pMSB124X have not inited !!!\n", __FUNCTION__));
        return FALSE;
    }

    if (MsOS_ObtainMutex(pMSB124X->s32_MSB124X_Mutex, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        PRINTE(("Obtain mutex failed !!!\n"));
        return FALSE;
    }
    pMSB124X->bOpen = FALSE;
    MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);

    return TRUE;
}

/****************************************************************************
**function:
**
**
****************************************************************************/
MS_BOOL MDrv_Demod_GetSignalQuality(MS_U16 *pu16Quality)
{

    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !\n"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("[%s]pMSB124X have not inited !!!\n", __FUNCTION__));
        return FALSE;
    }

    if (MsOS_ObtainMutex(pMSB124X->s32_MSB124X_Mutex, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        PRINTE(("MDrv_Demod_GetSNR:Obtain mutex failed !!!\n"));
        return FALSE;
    }
    else
    {
        *pu16Quality = 0;
        if (E_DEMOD_LOCK == MSB124X_DTV_GetLockStatus())
        {
            *pu16Quality  = MSB124X_DTV_GetSignalQuality();
        }
    }
    MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);
    return TRUE;
}


/****************************************************************************
**function:
**
**
****************************************************************************/
MS_BOOL MDrv_Demod_GetSNR(MS_U32 *pu32SNR)
{

    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !\n"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("[%s]pMSB124X have not inited !!!\n", __FUNCTION__));
        return FALSE;
    }

    if (MsOS_ObtainMutex(pMSB124X->s32_MSB124X_Mutex, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        PRINTE(("MDrv_Demod_GetSNR:Obtain mutex failed !!!\n"));
        return FALSE;
    }
    else
    {
        *pu32SNR = 0;
        if (E_DEMOD_LOCK == MSB124X_DTV_GetLockStatus())
        {
            //*pu32SNR  = MSB124X_DTV_GetSignalQuality();
            float snr;
            MSB124X_DTV_GetSNR_F(&snr);
            *pu32SNR  = (MS_U32)snr;
        }
        if (*pu32SNR > 100)
        {
            *pu32SNR = 100;
        }
        else if (*pu32SNR < 0)
        {
            *pu32SNR = 0;
        }
    }
    MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);

    return TRUE;
}

/****************************************************************************
**function:
**
**
****************************************************************************/
MS_BOOL MDrv_Demod_GetBER(float *pfBER)
{
    MS_BOOL status = TRUE;

    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;

    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !\n"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("[%s]pMSB124X have not inited !!!\n", __FUNCTION__));
        return FALSE;
    }

    if (MsOS_ObtainMutex(pMSB124X->s32_MSB124X_Mutex, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        PRINTE(("MDrv_Demod_GetBER:Obtain mutex failed !!!\n"));
        return FALSE;
    }

    //*pfBER = (float)MSB124X_DTV_GetSignalQuality();
    status = MSB124X_DTV_GetPostBER(pfBER);

    MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);

    return status;
}

MS_BOOL MDrv_Demod_GetPWR(MS_S32 *ps32Signal)
{
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !\n"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("[%s]pMSB124X have not inited !!!\n", __FUNCTION__));
        return FALSE;
    }
    if (MsOS_ObtainMutex(pMSB124X->s32_MSB124X_Mutex, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        PRINTE(("MDrv_Demod_GetPWR:Obtain mutex failed !!!\n"));
        return FALSE;
    }
    else
    {
        *ps32Signal = 0;
        if (E_DEMOD_LOCK == MSB124X_DTV_GetLockStatus())
        {
#if((FRONTEND_TUNER_TYPE == TUNER_MXL603) || (FRONTEND_TUNER_TYPE == TUNER_MXL608))
             short fSignal;

            MSB124X_IIC_Bypass_Mode(TRUE);
#if(FRONTEND_TUNER_TYPE == TUNER_MXL603)
            if (MXL_SUCCESS != MxLWare603_API_ReqTunerRxPower(MXL603_I2C_ADDR, &fSignal))
            {
                PRINTE(("MxLWare603_API_ReqTunerRxPower failed !!!\n"));
                MSB124X_IIC_Bypass_Mode(FALSE);
                return FALSE;
            }
#endif
#if(FRONTEND_TUNER_TYPE == TUNER_MXL608)
            if (MXL_SUCCESS != MxLWare608_API_ReqTunerRxPower(MXL608_I2C_ADDR, &fSignal))
            {
                PRINTE(("MxLWare608_API_ReqTunerRxPower failed !!!\n"));
                MSB124X_IIC_Bypass_Mode(FALSE);
                return FALSE;
            }
#endif
            MSB124X_IIC_Bypass_Mode(FALSE);

            *ps32Signal = (MS_U32)MSB124X_DTV_GetSignalStrengthWithRFPower((float)fSignal/100);
#else
            *ps32Signal  = (MS_U32)MSB124X_DTV_GetSignalStrength();
#endif
        }
        if (*ps32Signal > 100)
        {
            *ps32Signal = 100;
        }
        else if (*ps32Signal < 0)
        {
            *ps32Signal = 0;
        }
    }

    MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);
    return TRUE;
}

EN_LOCK_STATUS MDrv_Demod_GetT2LockStatus(void)
{
    EN_LOCK_STATUS LockStatus = E_DEMOD_UNLOCK;
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !\n"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("[%s]pMSB124X have not inited !!!\n", __FUNCTION__));
        return FALSE;
    }

    if (MsOS_ObtainMutex(pMSB124X->s32_MSB124X_Mutex, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        PRINTE(("MDrv_Demod_GetLockStatus:Obtain mutex failed !!!\n"));
        return FALSE;
    }
    else
    {
        LockStatus = MSB124X_DTV_GetLockStatus();
    }
    MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);
    return LockStatus;
}

MS_BOOL MDrv_Demod_GetLock(EN_LOCK_STATUS *peLockStatus)
{
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    *peLockStatus = E_DEMOD_CHECKING;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !\n"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("[%s]pMSB124X have not inited !!!\n", __FUNCTION__));
        return FALSE;
    }

    if (MsOS_ObtainMutex(pMSB124X->s32_MSB124X_Mutex, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        PRINTE(("MDrv_Demod_GetLock:Obtain mutex failed !!!\n"));
        return FALSE;
    }
    else
    {
        *peLockStatus = MSB124X_DTV_GetLockStatus();
    }

    MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);
    return TRUE;
}

/****************************************************************************
**function:reset bw and Plpid to demod when plp changed
**
**
****************************************************************************/
MS_BOOL MDrv_Demod_T2MI_Restart(void)
{
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    MS_U8    PlpId, BandWidth;

    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !\n"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("[%s]pMSB124X have not inited !!!\n", __FUNCTION__));
        return FALSE;
    }
    if (MsOS_ObtainMutex(pMSB124X->s32_MSB124X_Mutex, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        PRINTE(("MDrv_Demod_Restart:Obtain mutex failed !!!\n"));
        return FALSE;
    }

    if (E_DEMOD_TYPE_T2 != MDrv_Demod_GetCurrentDemodType())
    {
        MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);
        return TRUE;
    }

    MSB124X_ReadDspReg((MS_U16)E_T2_PLP_ID, &PlpId);
    if (pMSB124X->u8CurrPlpID != PlpId)
    {
        switch (pMSB124X->enCurrBW)
        {
        case DEMOD_BW_MODE_6MHZ:
            BandWidth = E_DEMOD_BW_6M;
            break;
        case DEMOD_BW_MODE_7MHZ:
            BandWidth = E_DEMOD_BW_7M;
            break;
        case DEMOD_BW_MODE_1_7MHZ: // 1.7MHz
            BandWidth = E_DEMOD_BW_17M;
            break;
        case DEMOD_BW_MODE_8MHZ:
        default:
            BandWidth = E_DEMOD_BW_8M;
            break;
        }
        PRINTE(("Curr_PLP_ID=%d, GET_PLP_ID=%d\n", pMSB124X->u8CurrPlpID, PlpId));
        MSB124X_WriteDspReg((MS_U16)E_T2_BW, BandWidth);      // BW: 0->1.7M, 1->5M, 2->6M, 3->7M, 4->8M, 5->10M
        MSB124X_WriteDspReg((MS_U16)E_T2_PLP_ID, pMSB124X->u8CurrPlpID);
        MSB124X_WriteDspReg((MS_U16)E_T2_IF_AGC_INV_PWM_EN, T2_IF_AGC_INV_PWM_EN_VAL);

        MSB124X_WriteReg(REG_FSM_EN, 0x01); // FSM_EN
    }

    MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);
    return TRUE;
}

MS_BOOL MDrv_Demod_Restart(DEMOD_MS_FE_CARRIER_PARAM *pParam)
{
    MS_U32              dwError = TRUE;
    MS_U8               BandWidth = DEMOD_BW_MODE_8MHZ;
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !\n"));
        return FALSE;
    }
    if ((!pMSB124X->bInited) || (!pMSB124X->bOpen))
    {
        PRINTE(("[%s]pMSB124X have not inited !!!\n", __FUNCTION__));
        return FALSE;
    }
    if (MsOS_ObtainMutex(pMSB124X->s32_MSB124X_Mutex, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        PRINTE(("MDrv_Demod_Restart:Obtain mutex failed !!!\n"));
        return FALSE;
    }

    pMSB124X->enTuneBw = pParam->TerParam.eBandWidth;
    printf("\n[%s]tuner demod Freq=%d, Bw=%d,type=%d,plpid=%d\n", __FUNCTION__, pParam->u32Frequency, pParam->TerParam.eBandWidth, \
           pParam->TerParam.u8ScanType, pParam->TerParam.u8PlpID);

    if (DEMOD_BW_MODE_1_7MHZ == pParam->TerParam.eBandWidth)
    {
        MDrv_Demod_SetCurrentDemodType(E_DEMOD_TYPE_T2);
    }
    else if ((E_DEMOD_TYPE_T == pParam->TerParam.u8ScanType) && (pMSB124X->u8CurrScanType != pParam->TerParam.u8ScanType))
    {
        MDrv_Demod_SetCurrentDemodType(E_DEMOD_TYPE_T);
    }
    else if ((E_DEMOD_TYPE_T2 == pParam->TerParam.u8ScanType) && (pMSB124X->u8CurrScanType != pParam->TerParam.u8ScanType))
    {
        MDrv_Demod_SetCurrentDemodType(E_DEMOD_TYPE_T2);
    }
    else
        ;

    switch (pParam->TerParam.eBandWidth)
    {
    case DEMOD_BW_MODE_6MHZ:
        BandWidth = 6;
        break;
    case DEMOD_BW_MODE_7MHZ:
        BandWidth = 7;
        break;
    case DEMOD_BW_MODE_8MHZ:
        BandWidth = 8;
        break;
    case DEMOD_BW_MODE_1_7MHZ: // 1.7MHz
        BandWidth = 17;
        break;
    }

    if ((TRUE == pMSB124X->bFECLock) && (pMSB124X->u8CurrScanType == pParam->TerParam.u8ScanType) && \
            (E_DEMOD_TYPE_T2 == pMSB124X->u8CurrScanType) && (pMSB124X->u32CurrFreq == pParam->u32Frequency) && \
            (pMSB124X->enCurrBW == pParam->TerParam.eBandWidth))
    {
    }
    else
    {
        //set freq and bw to tuner
        MSB124X_IIC_Bypass_Mode(TRUE);
        MDrv_Tuner_SetTuner(pParam->u32Frequency, BandWidth);
//		MDrv_Tuner_MXL608_SetTuner(pParam->u32Frequency, BandWidth);

        MSB124X_IIC_Bypass_Mode(FALSE);
        dwError = MSB124X_DTV_SetFrequency(pParam->u32Frequency, BandWidth, pParam->TerParam.u8PlpID);
    }

    pMSB124X->u32CurrFreq = pParam->u32Frequency;
    pMSB124X->enCurrBW = pParam->TerParam.eBandWidth;
    pMSB124X->u8CurrPlpID = pParam->TerParam.u8PlpID;
    pMSB124X->u8CurrScanType = pParam->TerParam.u8ScanType;

    if (E_DEMOD_TYPE_T2 == MDrv_Demod_GetCurrentDemodType())
    {
        dwError &= MSB124X_T2_SetPlpID(pParam->TerParam.u8PlpID);
    }
    PRINTE((" ==return %d==\n", dwError));
    MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);
    return dwError;
}

void MDrv_Demod_CtrlResetDJBFlag(MS_U8 Ctrl)
{
    MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (pMSB124X->enDemodType == E_DEVICE_DEMOD_DVB_T2)
    {

    }
}

MS_BOOL MDrv_Demod_Init(void)
{
    PRINTE(("%s(),%d\n", __FUNCTION__, __LINE__));

    MS_U8     status = TRUE;
    sDMD_MSB124X_InitData sMSB124x_InitData;

    if (MSB124X.bInited==TRUE)
    {
        printf("demod Already Init 0x%x\n",MSB124X.bInited);
        return TRUE;
    }

    MSB124X.bInited = TRUE;
    MSB124X.bOpen = TRUE;
    MSB124X.u8sramCode = 0;
    MSB124X.PlpIDSize = 0;
    MSB124X.bFECLock = FALSE;
    MSB124X.u8ScanStatus = 0;
    MSB124X.u32CurrFreq = 0;
    MSB124X.enCurrBW = DEMOD_BW_MODE_8MHZ;
    MSB124X.enTuneBw = DEMOD_BW_MODE_8MHZ;
    MSB124X.u8CurrPlpID = 0xff;
    MSB124X.enDemodType = E_DEVICE_DEMOD_DVB_T;
    MSB124X.u8CurrScanType = E_DEMOD_TYPE_T;
    MSB124X.pMSB124X_RegDVBT = MSB1236c_DVBT_DSPREG_TABLE ;

    MSB124X.s32_MSB124X_Mutex = MsOS_CreateMutex(E_MSOS_FIFO, (char *)"Mutex DVBT2", MSOS_PROCESS_SHARED);
    if (MSB124X.s32_MSB124X_Mutex < 0)
    {
        MSB124X.bInited = FALSE;
        MSB124X.bOpen = FALSE;
        PRINTE(("creat MSB124X Mutex error!!!\n"));
        return FALSE;
    }

    //extern void MApi_Demod_HWReset(void);
    //MApi_Demod_HWReset();
    _msb124x_hw_reset();
    MDrv_DMD_MSB124X_Exit();

    MsOS_DelayTask(10);

    sMSB124x_InitData.u8WO_SPI_Flash = TRUE;
    sMSB124x_InitData.bPreloadDSPCodeFromMainCHIPI2C = FALSE;
    sMSB124x_InitData.bFlashWPEnable = TRUE;
    sMSB124x_InitData.fpGPIOReset = NULL;
    sMSB124x_InitData.fpMSB124X_I2C_Access = msb124x_I2C_Access;
    sMSB124x_InitData.pDVBC_DSP_REG = NULL;
    sMSB124x_InitData.pDVBT_DSP_REG = MSB1236c_DVBT_DSPREG_TABLE;
    sMSB124x_InitData.pDVBT2_DSP_REG = MSB1236c_DVBT2_DSPREG_TABLE;
#ifdef CHIP_KERES
    sMSB124x_InitData.u8WO_Sdram = FALSE;
#endif

#if (SUPPORT_MSPI_LOAD_CODE == 1)
    sMSB124x_InitData.bEnableSPILoadCode = TRUE;
    sMSB124x_InitData.fpMSB124x_SPIPAD_En = msb124x_SPIPAD_En;
#else
    sMSB124x_InitData.bEnableSPILoadCode = FALSE;
    sMSB124x_InitData.fpMSB124x_SPIPAD_En = NULL;
#endif

    status &= MDrv_DMD_MSB124X_Init(&sMSB124x_InitData, sizeof(sDMD_MSB124X_InitData));
    if (status)
    {
        MDrv_DMD_MSB124X_SetCurrentDemodulatorType(E_DMD_MSB124X_DEMOD_DVBT);
        status &= MDrv_DMD_MSB124X_Power_On_Initialization();
#if(MSB124X_SELECT_IF_INPUT)
        status &= MSB124X_WriteReg2bytes(0x0A00+(0x51)*2, 0x0021);
#endif
#if MSB124X_SELECT_AGC_PAD_T
        status &= MSB124X_WriteReg2bytes(0x0A00+(0x18)*2, 0x0001);
#else
        status &= MSB124X_WriteReg2bytes(0x0A00+(0x18)*2, 0x0100);
#endif
    }

    if (!status)
    {
        MSB124X.bInited = FALSE;
        MSB124X.bOpen = FALSE;
        MsOS_DeleteMutex(MSB124X.s32_MSB124X_Mutex);
        return FALSE;
    }

    MSB124X_Show_Version();
#if TS_PARALLEL_OUTPUT
    MSB124X_DTV_Serial_Control(FALSE);
#else
    MSB124X_DTV_Serial_Control(TRUE);
#endif
   
    return TRUE;
}

MS_BOOL MDrv_Demod_DeInit(void)
{
   MDvr_CofdmDmd_CONFIG *pMSB124X = &MSB124X;
    if (!pMSB124X)
    {
        PRINTE(("pMSB124X error !\n"));
        return FALSE;
    }
    if ((!pMSB124X->bInited))
    {
        PRINTE(("[%s]pMSB124X have not inited !!!\n", __FUNCTION__));
        return FALSE;
    }

    if (MsOS_ObtainMutex(pMSB124X->s32_MSB124X_Mutex, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        PRINTE(("Obtain mutex failed !!!\n"));
        return FALSE;
    }

    if (MDrv_DMD_MSB124X_Exit())
    {
         pMSB124X->bInited = FALSE;
    }
    else
    {
        MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);
        return FALSE;
    }
    MsOS_ReleaseMutex(pMSB124X->s32_MSB124X_Mutex);
    MsOS_DeleteMutex(pMSB124X->s32_MSB124X_Mutex);
    pMSB124X->s32_MSB124X_Mutex = -1;
     return TRUE;
}


MS_U16 MDrv_Demod_ReadReg(MS_U16 RegAddr)
{
    MS_U8 RegData = 0;
    MSB124X_ReadReg(RegAddr, &RegData);
    return (MS_U16) RegData;
}

MS_BOOL MDrv_Demod_WriteReg(MS_U16 RegAddr, MS_U16 RegData)
{

    return MSB124X_WriteReg(RegAddr, RegData);
}

#endif

