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
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
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

* Class : device_tuner_NXP_TDA18275
* File  : device_tuner_NXP_TDA18275.cpp
**********************************************************************/
/*@ </FileComment ID=1246257763274> @*/

/*@ <Include> @*/
#if 0
#include <unistd.h>
#include "debug.h"
#include "device_tuner_NXP_TDA18275.h"
#include "mapi_i2c.h"
#include "mapi_i2c_devTable.h"
#include "mapi_interface.h"
#include "MsTypes.h"
#include "drvDMD_common.h"
#include "drvDMD_INTERN_DVBT.h"
#include "drvDMD_INTERN_DVBC.h"
#include "mapi_gpio.h"
#include "mapi_gpio_devTable.h"
#include "mapi_vif.h"
#include "mapi_audio.h"
#include "mapi_demodulator_datatype.h"
#include "mapi_utility.h"
#endif
#include <apiSWI2C.h>

//#include "drvIIC.h"

//#include "msAPI_FreqTableATV.h"
//#include "msAPI_Tuning.h"
//#include "MApp_GlobalVar.h"
//#include "MApp_TopStateMachine.h"


#include "NXP_TDA18275/tmFlags.h"
#include "NXP_TDA18275/tmbslTDA18275_RegDef.c"
#include "NXP_TDA18275/tmbslTDA18275_Instance.c"
#include "NXP_TDA18275/tmbslTDA18275.c"

#define DBG_TUNER(x)   //x

// ------------------------------------------------------------
// Other Define
// ------------------------------------------------------------
#define DIVIDER_RATIO_50KHz         0x05
#define DIVIDER_RATIO_31_25KHz      0x04
#define DIVIDER_RATIO_62_5KHz       0x03
#define DIVIDER_RATIO_125KHz        0x02
#define DIVIDER_RATIO_142_85KHz     0x01
#define DIVIDER_RATIO_166_7KHz      0x00

// #define TN_FREQ_STEP                E_FREQ_STEP_50KHz
#define DIVIDER_RATIO               DIVIDER_RATIO_50KHz
#define TUNER_IF_FREQ_KHz           38900L
#define TUNER_L_PRIME_IF_FREQ_KHz   33950L

#define _TUNER_I2C_ID               0xC0
#define DIGITAL_TUNER_IF            (36.0)
#define MIN_FREQ_SUPPORT_KHz        40000
#define MAX_FREQ_SUPPORT_KHz        880000

#define TUNER_DTV_IQ_SWAP                 1// iq swap
#define TUNER_VHF_LOWMIN_FREQ             43000L//47000l//46250L
#define TUNER_VHF_LOWMAX_FREQ             147250L//142000L
#define TUNER_VHF_HIGHMIN_FREQ            154250L//149000L
#define TUNER_VHF_HIGHMAX_FREQ            431250L//426000L
#define TUNER_UHF_MIN_FREQ                434000L
#define TUNER_UHF_MAX_FREQ                863250L


#define DIVIDER_166K                0
#define DIVIDER_142K                1
#define DIVIDER_80K                 2
#define DIVIDER_62K                 3
#define DIVIDER_31K                 4
#define DIVIDER_50K                 5

#define TN_FREQ_SS_INVERSE_625      16      // 1/0.0625
#define TN_RSA_RSB_625              0x06
#define TN_RSA_RSB_50               0x05
#define TN_FREQ_SS_625              62.5    // kHz
#define TN_FREQ_SS_50               50      // kHz
#define TN_FREQ_SS_INVERSE_50       20      // 1/0.05
#define TN_FREQ_SS              TN_FREQ_SS_625

#define TN_LOW_BAND                 0x01
#define TN_MID_BAND                 0x02
#define TN_HIGH_BAND                0x04

#define IF_OUT_LEVEL_114            0
#define IF_OUT_LEVEL_112            (1<<3)
#define IF_OUT_LEVEL_110            (2<<3)
#define IF_OUT_LEVEL_108            (3<<3)
#define IF_OUT_LEVEL_106            (4<<3)
#define IF_OUT_LEVEL_104            (5<<3)
#define IF_OUT_LEVEL_105            (6<<3)
#define IF_OUT_LEVEL_Disable        (7<<3)

#define DIGITAL_IF_AGC_ON       0x00
#define DIGITAL_IF_AGC_OFF       0x08

#define CHARGE_PUMP_1            (1<<6)
#define CHARGE_PUMP_2           (2<<6)

#define CHARGE_PUMP_3           (1<<1)

#define ANALOG_IF_OUT       0x04
#define DIGITAL_IF_OUT      0x00

#define FAST_LOCK       0x20

#define BAND_SWITCH_UHF             0x04
#define BAND_SWITCH_VHF_HIGH        0x02
#define BAND_SWITCH_VHF_LOW         0x01

#define TUNER_HIBYTE(w)             ((MS_U8) (((MAPI_U16) (w) >> 8) & 0xFF))
#define TUNER_LOBYTE(w)             ((MS_U8) (w & 0xFF))
#ifndef UNUSED //to avoid compile warnings...
#define UNUSED(var) (void)((var) = (var))
#endif

#if 0
// tmbslTDA18275_InstanceCustom.h
// Digital IF
#define QAM_6M     4000L
#define QAM_8M     5000L
#define ATSC_6M    5250L
#define ISDBT_6M   3683L
#define DVBT_1p7M   850L
#define DVBT_6M    4000L
#define DVBT_7M    4500L
#define DVBT_8M    5000L
#define DVBT_10M   6000L
#define DMBT_8M    5000L

// Analog picture carrier
#define ATV_VC_MN  5400L
#define ATV_VC_B   6250L
#define ATV_VC_GH  6750L
#define ATV_VC_I   7250L
#define ATV_VC_DK  6850L
#define ATV_VC_L   6750L
#define ATV_VC_LL  1250L

// [21:0], CR_RATE for Video_Carrier_BBB KHz, HEX((Video_Carrier_BBB/43200.0) * (2^22))
#define VIF_TUNER_TYPE                  1                   // 0: RF Tuner; 1: Silicon Tuner
#define VIF_CR_RATE_B                   (MS_U32)(ATV_VC_B*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_B                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_GH                  (MS_U32)(ATV_VC_GH*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_GH                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_DK                  (MS_U32)(ATV_VC_DK*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_DK                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_I                   (MS_U32)(ATV_VC_I*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_I                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_L                   (MS_U32)(ATV_VC_L*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_L                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_LL                  (MS_U32)(ATV_VC_LL*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_LL                1                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_MN                  (MS_U32)(ATV_VC_MN*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_MN                0                   // Video carrier position; 0: high side; 1:low side
#endif
#define NXP18275_I2C_ADDR (((MS_U16)TUNER_IIC_BUS<<8)| _TUNER_I2C_ID)

/*@ </Definitions> @*/

#define TM_FALSE  1
#define TDA18275_BUSY  1
#define TDA18275_FREE  0
// static MS_U8 u8TDA18275Busy=TDA18275_FREE;
static MS_U8 bInitNXP_TDA18275 = 0;
// pthread_mutex_t m_mutexTunerInit = PTHREAD_MUTEX_INITIALIZER;

void devTDA18275TunerInit(void);

static EN_TUNER_MODE m_eMode = E_TUNER_DTV_DVB_T_MODE;//E_TUNER_INVALID;
static AUDIOSTANDARD_TYPE_ m_OtherMode = E_AUDIOSTANDARD_NOTSTANDARD_;

extern IF_FREQ MDrv_IFDM_GetIF(void);
MS_BOOL DTV_SetTune(double FreqMHz, RF_CHANNEL_BANDWIDTH eBandWidth, EN_TUNER_MODE eMode);
MS_BOOL ATV_SetTune(MS_U32 u32FreqKHz,RFBAND eBand, EN_TUNER_MODE eMode,MS_U8 u8OtherMode);

// #define ATV_VC_B   6250L
const MS_U16 VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[16]=
{
 0x03D1,0x0628,0x0406,
 0x03D4,0x0628,0x0403,
 0x01A6,0x0628,0x0200,0x0649,0x0200,
 0x03D1,0x0628,0x0200,0x0406,0x0200
};

// #define ATV_VC_B   6250L
const MS_U16 VIF_A1_A2_SOS11_SOS12_B_Mono_NICAM[16]=
{
 0x03D1,0x0628,0x0406,
 0x03D5,0x0628,0x0402,
 0x01A6,0x0628,0x0200,0x0649,0x0200,
 0x03D1,0x0628,0x0200,0x0406,0x0200
};

// #define ATV_VC_GH  6750L
const MS_U16 VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[16]=
{
 0x03C7,0x0628,0x0411,
 0x03CC,0x0628,0x0410B,
 0x00DC,0x0628,0x0200,0x071B,0x0200,
 0x03C7,0x0628,0x0200,0x0411,0x0200
};

// #define ATV_VC_GH  6750L
const MS_U16 VIF_A1_A2_SOS11_SOS12_GH_Mono_NICAM[16]=
{
 0x03C7,0x0628,0x0411,
 0x03CF,0x0628,0x0409,
 0x00DC,0x0628,0x0200,0x071B,0x0200,
 0x03C7,0x0628,0x0200,0x0411,0x0200
};

// #define ATV_VC_DK  6850L
const MS_U16 VIF_A1_A2_SOS11_SOS12_DK1_Stereo_A2[16]=
{
 0x03D6,0x0628,0x0401,
 0x03D3,0x0628,0x0404,
 0x0157,0x0628,0x0200,0x069B,0x0200,
 0x03D6,0x0628,0x0200,0x0401,0x0200
};

// #define ATV_VC_DK  6850L
const MS_U16 VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[16]=
{
 0x03D6,0x0628,0x0401,
 0x03D7,0x0628,0x0400,
 0x0157,0x0628,0x0200,0x069B,0x0200,
 0x03D6,0x0628,0x0200,0x0401,0x0200
};

// #define ATV_VC_DK  6850L
const MS_U16 VIF_A1_A2_SOS11_SOS12_DK3_Stereo_A2[16]=
{
 0x03D6,0x0628,0x0401,
 0x03CA,0x0628,0x040D,
 0x0157,0x0628,0x0200,0x069B,0x0200,
 0x03D6,0x0628,0x0200,0x0401,0x0200
};

// #define ATV_VC_DK  6850L
const MS_U16 VIF_A1_A2_SOS11_SOS12_DK_Mono_NICAM[16]=
{
 0x03D6,0x0628,0x0401,
 0x03CD,0x0628,0x040B,
 0x0157,0x0628,0x0200,0x069B,0x0200,
 0x03D6,0x0628,0x0200,0x0401,0x0200
};

// #define ATV_VC_I   7250L
const MS_U16 VIF_A1_A2_SOS11_SOS12_I[16]=
{
 0x038A,0x0661,0x0411,
 0x0395,0x0661,0x0405,
 0x00CE,0x0661,0x0200,0x071B,0x0200,
 0x038A,0x0661,0x0200,0x0411,0x0200
};

// #define ATV_VC_MN  5400L
const MS_U16 VIF_A1_A2_SOS11_SOS12_MN[16]=
{
 0x03CF,0x0628,0x0409,
 0x03D2,0x0628,0x0405,
 0x0210,0x0628,0x0200,0x05DA,0x0200,
 0x03CF,0x0628,0x0200,0x0409,0x0200
};

// #define ATV_VC_L   6750L
const MS_U16 VIF_A1_A2_SOS11_SOS12_L[16]=
{
 0x03D6,0x0628,0x0401,
 0x03CF,0x0628,0x0409,
 0x0164,0x0628,0x0200,0x068D,0x0200,
 0x03D6,0x0628,0x0200,0x0401,0x0200
};

// #define ATV_VC_LL  1250L
const MS_U16 VIF_A1_A2_SOS11_SOS12_LP[16]=
{
 0x01A6,0x0628,0x0649,
 0x01F8,0x0628,0x05F3,
 0x0000,0x0000,0x0000,0x0000,0x0200,
 0x01A6,0x0628,0x0200,0x0649,0x0200
};


#if 0
void *TunerInitThread(void* ptr)
{
    device_tuner_NXP_TDA18275* _this =(device_tuner_NXP_TDA18275*)ptr;
    printf("Tuner Init Thread\n");
    if (_this->m_bDeviceBusy == 1)
        return FALSE;

    _this->m_bDeviceBusy = 1;
    if(!bInitNXP_TDA18275) //double checklock
    {
        mapi_scope_lock(scopeLock, &m_mutexTunerInit);
        if(!bInitNXP_TDA18275)
        {
            devTDA18275TunerInit();
            bInitNXP_TDA18275 = 1;
        }
    }
    _this->m_bDeviceBusy = 0;
    pthread_exit(NULL);
}
static pthread_t TunerInitThreadId;
BOOLEAN TunerInit(void)
{
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if(0 != pthread_create(&TunerInitThreadId, &attr, TunerInitThread, (void *)this))
    {
        ASSERT(0);
    }
    return TRUE;
}

device_tuner_NXP_TDA18275(void)
{
    m_bDeviceBusy = 0;
}

BOOLEAN Connect(void)
{
    printf("device_tuner_NXP_TDA18275: Connect\n");
    if (m_bDeviceBusy == 1)
        return FALSE;

    m_bDeviceBusy = 1;


    return TRUE;
}

BOOLEAN Disconnect()
{
    printf("device_tuner_NXP_TDA18275: Disconnect\n");

    m_bDeviceBusy = 0;

    return TRUE;
}
#endif

//*--------------------------------------------------------------------------------------
//* Prototype of function to be provided by customer
//*--------------------------------------------------------------------------------------
tmErrorCode_t   UserWrittenI2CRead(tmUnitSelect_t tUnit,UInt32 AddrSize, UInt8* pAddr,UInt32 ReadLen, UInt8* pData);
tmErrorCode_t   UserWrittenI2CWrite (tmUnitSelect_t tUnit, UInt32 AddrSize, UInt8* pAddr,UInt32 WriteLen, UInt8* pData);
tmErrorCode_t   UserWrittenWait(tmUnitSelect_t tUnit, UInt32 tms);

//*--------------------------------------------------------------------------------------
//* Function Name       :   UserWrittenI2CRead
//* Object              :
//* Input Parameters    :   tmUnitSelect_t tUnit
//*                         UInt32 AddrSize,
//*                         UInt8* pAddr,
//*                         UInt32 ReadLen,
//*                         UInt8* pData
//* Output Parameters   :   tmErrorCode_t.
//*--------------------------------------------------------------------------------------
tmErrorCode_t UserWrittenI2CRead(tmUnitSelect_t tUnit, UInt32 AddrSize, UInt8* pAddr,
UInt32 ReadLen, UInt8* pData)
{
    /* Variable declarations */
    tmErrorCode_t err = TM_FALSE;
    UNUSED(tUnit);
    if(MApi_SWI2C_ReadBytes(NXP18275_I2C_ADDR, (MS_U8) AddrSize, pAddr, (MS_U16) ReadLen, pData))
    {
        err = TM_OK;
    }
    else
    {
        printf("%s, %d, i2c read Error\n",__FILE__,__LINE__);
    }

    return err;

}

//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenI2CWrite
//* Object              :
//* Input Parameters    :   tmUnitSelect_t tUnit
//*                         UInt32 AddrSize,
//*                         UInt8* pAddr,
//*                         UInt32 WriteLen,
//*                         UInt8* pData
//* Output Parameters   :   tmErrorCode_t.
//*--------------------------------------------------------------------------------------
tmErrorCode_t UserWrittenI2CWrite (tmUnitSelect_t tUnit, UInt32 AddrSize, UInt8* pAddr,
UInt32 WriteLen, UInt8* pData)
{
    /* Variable declarations */
    tmErrorCode_t err = TM_FALSE;
    UNUSED(tUnit);


    if(MApi_SWI2C_WriteBytes(NXP18275_I2C_ADDR, (MS_U8) AddrSize, pAddr, (MS_U16) WriteLen, pData))
    {
	    err = TM_OK;
    }
    else
    {
        printf("%s, %d, i2c write Error\n",__FILE__,__LINE__);
    }
    return err;

}

//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenWait
//* Object              :
//* Input Parameters    :   tmUnitSelect_t tUnit
//*                         UInt32 tms
//* Output Parameters   :   tmErrorCode_t.
//*--------------------------------------------------------------------------------------
tmErrorCode_t UserWrittenWait(tmUnitSelect_t tUnit, UInt32 tms)
{
    /* Variable declarations */
    tmErrorCode_t err = TM_OK;
    UNUSED(tUnit);
    MsOS_DelayTask(tms);
    return err;

}

void devTunerInit(void)
{
    devTDA18275TunerInit();
    return;
}

// DTV init..........
void devDigitalTuner_Init(void)
{
    devTunerInit();
    return;
}


void devTunerSetFreq(MS_U32 u32Freq)
{
    MS_BOOL retb = TRUE;

    if (bInitNXP_TDA18275 == FALSE)
    {
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return;
    }

    IF_FREQ CurrentStandard = MDrv_IFDM_GetIF();

	//printf("[CurrentStandard],%d\n",CurrentStandard);
    if(CurrentStandard==IF_FREQ_B)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_BG_;
    }
    else if  (CurrentStandard==IF_FREQ_G)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_BG_;
    }
    else if  (CurrentStandard==IF_FREQ_I)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_I_;
    }
    else if  (CurrentStandard==IF_FREQ_DK)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_DK_;
    }
    else if  (CurrentStandard==IF_FREQ_L)
    {
        m_eMode = E_TUNER_ATV_SECAM_L_MODE;
        m_OtherMode = E_AUDIOSTANDARD_L_;
    }
    else if  (CurrentStandard==IF_FREQ_L_PRIME)
    {
        m_eMode = E_TUNER_ATV_SECAM_L_PRIME_MODE;
        m_OtherMode = E_AUDIOSTANDARD_L_;
    }
    else if  (CurrentStandard==IF_FREQ_MN)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_M_;
    }
    else
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_BG_;
    }

    DBG_TUNER(printf("[devTunerSetFreq]%s, %d,  m_OtherMode=%d, u32Freq=%ld, CurrentStandard=%d\n",__FILE__,__LINE__,m_OtherMode,u32Freq,CurrentStandard);)

    retb &= ATV_SetTune(u32Freq/1000,(RFBAND)0, m_eMode,(MS_U8)m_OtherMode);

    if (retb == FALSE)
        printf("[Error]%s,%d\n",__FILE__,__LINE__);

    return;
}

void devDigitalTuner_SetFreq( double Freq,  RF_CHANNEL_BANDWIDTH eBandWidth)
{
    MS_BOOL bRet = TRUE;

    DBG_TUNER(printf("[devDigitalTuner_SetFreq]Freq=%d, eBandWidth=%d, m_eMode=%d\n",(MS_U16)Freq,(MS_U8)eBandWidth,(MS_U8)m_eMode);)

    if (bInitNXP_TDA18275 == FALSE)
    {
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return;
    }

    // Freq (MHz)
    bRet &= DTV_SetTune(Freq, eBandWidth, m_eMode);

    if (bRet == FALSE)
        printf("[Error]%s,%d\n",__FILE__,__LINE__);

    return;

}

MS_BOOL devTuner_Std_set(EN_TUNER_MODE eMode, AUDIOSTANDARD_TYPE_ OtherMode)
{
    MS_BOOL bRet = TRUE;
    m_eMode = eMode;
    m_OtherMode = OtherMode;

    DBG_TUNER(printf("devTuner_Std_set, eMode=%d, OtherMode=%d\n",eMode,OtherMode);)

    return bRet;
}

void devTDA18275TunerInit(void)
{
    /* Variable declarations */
    tmErrorCode_t err = TM_OK;
    tmbslFrontEndDependency_t sSrvTunerFunc;
#if 0
    tmTDA18275StandardMode_t stdMode = tmTDA18275_ANLG_B;
    UInt32 uRF = 55250000;
    tmbslFrontEndState_t PLLLock = tmbslFrontEndStateUnknown;
    UInt32 uIF = 0;
#endif

    if (bInitNXP_TDA18275 == 1)
    {
        printf("%s, %d, warnning\n",__FILE__,__LINE__);
        return;
    }

    /* Driver layer struct set-up to link with user written functions */
    sSrvTunerFunc.sIo.Write             = UserWrittenI2CWrite;
    sSrvTunerFunc.sIo.Read              = UserWrittenI2CRead;
    sSrvTunerFunc.sTime.Get             = Null;
    sSrvTunerFunc.sTime.Wait            = UserWrittenWait;
    sSrvTunerFunc.sDebug.Print          = Null;//UserWrittenPrint;
    sSrvTunerFunc.sMutex.Init           = Null;//UserWrittenMutexInit;
    sSrvTunerFunc.sMutex.DeInit         = Null;//UserWrittenMutexDeInit;
    sSrvTunerFunc.sMutex.Acquire        = Null;//UserWrittenMutexAcquire;
    sSrvTunerFunc.sMutex.Release        = Null;//UserWrittenMutexRelease;
    sSrvTunerFunc.dwAdditionalDataSize  = 0;
    sSrvTunerFunc.pAdditionalData       = Null;

    /* TDA18275 Driver initialization  */
    err = tmbslTDA18275_Open(0, &sSrvTunerFunc);

    if(err == TM_OK)
    {
         /* TDA18275 Hardware initialization */
         err = tmbslTDA18275_HwInit(0);
    }
#if 0
    if(err == TM_OK)
    {
         /* TDA18275 standard mode selection */
         err = tmbslTDA18275_SetStandardMode(0, stdMode);
    }
    if(err == TM_OK)
    {
         /* TDA18275 RF frequency selection */
         err = tmbslTDA18275_SetRF(0, uRF);
    }
    if(err == TM_OK)
    {
         /* Get TDA18275 PLL Lock status */
         err = tmbslTDA18275_GetLockStatus(0, &PLLLock);
    }
    if(err == TM_OK)
    {
         /* Get TDA18275 IF value */
         err = tmbslTDA18275_GetIF(0, &uIF);
    }
    if(err == TM_OK)
    {
         /* DeInitialize TDA18275 Driver */
         err = tmbslTDA18275_Close(0);
    }
#endif

    if (err != TM_OK)
    {
        printf("@@@@%s, %s, %d, Error\n",__FILE__,__FUNCTION__,__LINE__);
    }
    else
    {
printf("@@@CM>>%s %d\n",__FUNCTION__,__LINE__);
        bInitNXP_TDA18275 = 1;
    }

    return;
}

void devTDA18275DigitalTuner_Init(void)
{
    devTDA18275TunerInit();
}


MS_BOOL ATV_SetTune( MS_U32 u32FreqKHz,RFBAND eBand, EN_TUNER_MODE eMode,MS_U8 u8OtherMode)
{
    tmTDA18275StandardMode_t StandardMode = tmTDA18275_ANLG_B;
    tmErrorCode_t   err = TM_OK;
    UNUSED(eBand);

    UInt32 uRF = 55250000;
    tmbslFrontEndState_t PLLLock = tmbslFrontEndStateUnknown;
    UInt32 uIF = 0;

    uRF = u32FreqKHz * 1000;

    if(!bInitNXP_TDA18275) //double check lock
    {
        devTDA18275TunerInit();
        if (bInitNXP_TDA18275 == 0)
        {
            return FALSE;
        }
    }

    DBG_TUNER(printf("%s, %d, FreqKhz=%ld,eBand=%d,eMode=%d,u8OtherMode=%d\n",__FILE__,__LINE__,u32FreqKHz,eBand,eMode,u8OtherMode);)

    if(eMode == E_TUNER_ATV_SECAM_L_PRIME_MODE)
    {
        //printf(" \33[0;32m >>>@@@>>>@@@@>>>@@@ 111  E_TUNER_ATV_SECAM_L_PRIME_MODE \n \33[m");
        StandardMode = tmTDA18275_ANLG_LL;
    }
    else
    {
        //printf(" \33[0;32m >>>@@@>>>@@@@>>>@@@ 222  E_TUNER_ATV_PAL_MODE \n \33[m");

        //printf("OtherMode[%d]\r\n",u8OtherMode);
        if(u8OtherMode == 0xff)
        {
            StandardMode=tmTDA18275_ANLG_DK;
        }
        else
        {
            switch((AUDIOSTANDARD_TYPE_)u8OtherMode)
            {
            case E_AUDIOSTANDARD_BG_:
                StandardMode=tmTDA18275_ANLG_B;
                break;

            case E_AUDIOSTANDARD_I_:
                StandardMode=tmTDA18275_ANLG_I;
                break;

            case E_AUDIOSTANDARD_DK_:
                StandardMode=tmTDA18275_ANLG_DK;
                break;

            case E_AUDIOSTANDARD_L_:
                StandardMode=tmTDA18275_ANLG_L;
                break;

            case E_AUDIOSTANDARD_M_:
                StandardMode=tmTDA18275_ANLG_MN;
                break;
            default:
                StandardMode=tmTDA18275_ANLG_DK;
                break;
            }
        }

    }

    if(err == TM_OK)
    {
         /* TDA18275 standard mode selection */
         err = tmbslTDA18275_SetStandardMode(0, StandardMode);
    }
    if(err == TM_OK)
    {
         /* TDA18275 RF frequency selection */
         err = tmbslTDA18275_SetRF(0, uRF);
    }
    if(err == TM_OK)
    {
         /* Get TDA18275 PLL Lock status */
         err = tmbslTDA18275_GetLockStatus(0, &PLLLock);
         DBG_TUNER(printf("%s,%d,PLLLock=%d\n",__FILE__,__LINE__,PLLLock);)
    }
    if(err == TM_OK)
    {
         /* Get TDA18275 IF value */
         err = tmbslTDA18275_GetIF(0, &uIF);
         DBG_TUNER(printf("%s,%d,IF=%ld\n",__FILE__,__LINE__,uIF);)
    }
    return (err == TM_OK)?TRUE:FALSE;
}


MS_BOOL DTV_SetTune(double Freq, RF_CHANNEL_BANDWIDTH eBandWidth, EN_TUNER_MODE eMode)
{
    tmTDA18275StandardMode_t StandardMode = tmTDA18275_DVBT_8MHz;
    tmbslFrontEndState_t PLLLock = tmbslFrontEndStateUnknown;
    UInt32          uIF = 0;
    tmErrorCode_t   err = TM_OK;
    UInt32          uRF = 666000000;

    uRF = (UInt32)(Freq * 1000000.0);

    if(!bInitNXP_TDA18275)
    {
        devTDA18275DigitalTuner_Init();
        if (bInitNXP_TDA18275 == 0)
        {
            return FALSE;
        }
    }

    DBG_TUNER(printf("%s, %d, FreqKhz=%ld,bw=%d,eMode=%d,uRF=%ld\n",__FILE__,__LINE__,(UInt32)Freq,(UInt8)eBandWidth,(UInt8)eMode,(UInt32)uRF);)

    switch (eMode)
    {
        case E_TUNER_DTV_DVB_C_MODE:
            printf("\r\nSilicon  Tuner mode DVBC\n");
            StandardMode = tmTDA18275_QAM_8MHz;
            break;
        case E_TUNER_DTV_DVB_T_MODE:
        case E_TUNER_DTV_DVB_T2_MODE:
            {
                printf("\r\nSilicon  Tuner mode DVBT\n");
                switch (eBandWidth)
                {
                    case E_RF_CH_BAND_6MHz:
                        StandardMode = tmTDA18275_DVBT_6MHz;
                        break;
                    case E_RF_CH_BAND_7MHz:
                        StandardMode = tmTDA18275_DVBT_7MHz;
                        break;
                    case E_RF_CH_BAND_8MHz:
                    default:
                        StandardMode = tmTDA18275_DVBT_8MHz;
                        break;
                }
            }
            break;
        case E_TUNER_DTV_DTMB_MODE:
            StandardMode = tmTDA18275_DMBT_8MHz;
            break;
        case E_TUNER_DTV_ATSC_MODE:
            StandardMode = tmTDA18275_ATSC_6MHz;
            break;
        case E_TUNER_DTV_ISDB_MODE:
            StandardMode = tmTDA18275_ISDBT_6MHz;
            break;
        default:
            StandardMode = tmTDA18275_DVBT_8MHz;
            printf("%s, %d, Error",__FILE__,__LINE__);
            break;
    }

    if(err == TM_OK)
    {
         /* TDA18275 standard mode selection */
         err = tmbslTDA18275_SetStandardMode(0, StandardMode);
    }
    if(err == TM_OK)
    {
         /* TDA18275 RF frequency selection */
         err = tmbslTDA18275_SetRF(0, uRF);
    }
    if(err == TM_OK)
    {
         /* Get TDA18275 PLL Lock status */
         err = tmbslTDA18275_GetLockStatus(0, &PLLLock);
         DBG_TUNER(printf("%s,%d,PLLLock=%d\n",__FILE__,__LINE__,PLLLock);)
    }
    if(err == TM_OK)
    {
         /* Get TDA18275 IF value */
         err = tmbslTDA18275_GetIF(0, &uIF);
         DBG_TUNER(printf("%s,%d,IF=%ld\n",__FILE__,__LINE__,uIF);)
    }

    return (err == TM_OK)?TRUE:FALSE;
}

// return dbm value, 0dBm~-98dBm
MS_BOOL mdev_GetSignalStrength(float* f_strength)
{
    float rssi = 0;

    tmErrorCode_t err = TM_OK;
    UInt8 u8_rf_level_1_2_dubV = 0;

    err = tmbslTDA18275_GetPowerLevel(0, &u8_rf_level_1_2_dubV);

    if(err != TM_OK)
    {
        rssi = -10.0f;
        printf("NuTune TDA18275 RF Level Get Error\n");
    }
    else
    {
        rssi = (float)u8_rf_level_1_2_dubV/2.0-107.0f; // dBuV to dBm
        DBG_TUNER(printf("NXP TDA18275 RF Level %f dBm, %d(1/2dbuV)\n",rssi,u8_rf_level_1_2_dubV);)
    }
    *f_strength = rssi;
    return err;
}


#if 0
BOOLEAN ExtendCommand(MS_U8 u8SubCmd, MS_U32 u32Param1, MS_U32 u32Param2, void* pvoidParam3)
{
    DBG_TUNER(printf("ExtendCommand, u8SubCmd=%d\n",u8SubCmd);)

    switch(u8SubCmd)
    {
        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_FREQ_STEP:
        {
            EN_FREQ_STEP *eFreqStep = (EN_FREQ_STEP*)pvoidParam3;
            *eFreqStep = TN_FREQ_STEP;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_IF_FREQ:
        {
            MAPI_U16 *u16IFFreq = (MAPI_U16 *)pvoidParam3;
            *u16IFFreq = TUNER_IF_FREQ_KHz;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_L_PRIME_IF_FREQ:
        {
            MAPI_U16 *u16IFFreq = (MAPI_U16 *)pvoidParam3;
            *u16IFFreq = TUNER_L_PRIME_IF_FREQ_KHz;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VHF_LOWMIN_FREQ:
        {
            MS_U32 *u32Freq = (MS_U32 *)pvoidParam3;
            *u32Freq = TUNER_VHF_LOWMIN_FREQ;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VHF_LOWMAX_FREQ:
        {
            MS_U32 *u32Freq = (MS_U32 *)pvoidParam3;
            *u32Freq = TUNER_VHF_LOWMAX_FREQ;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VHF_HIGHMIN_FREQ:
        {
            MS_U32 *u32Freq = (MS_U32 *)pvoidParam3;
            *u32Freq = TUNER_VHF_HIGHMIN_FREQ;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VHF_HIGHMAX_FREQ:
        {
            MS_U32 *u32Freq = (MS_U32 *)pvoidParam3;
            *u32Freq = TUNER_VHF_HIGHMAX_FREQ;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_UHF_MIN_FREQ:
        {
            MS_U32 *u32Freq = (MS_U32 *)pvoidParam3;
            *u32Freq = TUNER_UHF_MIN_FREQ;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_UHF_MAX_FREQ:
        {
            MS_U32 *u32Freq = (MS_U32 *)pvoidParam3;
            *u32Freq = TUNER_UHF_MAX_FREQ;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VIF_TUNER_TYPE:
        {
            MS_U8 *u8VifTunerType = (MS_U8 *)pvoidParam3;
            *u8VifTunerType = VIF_TUNER_TYPE;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VIF_PARA:
        {
            mapi_vif_datatype::stVIFInitialIn *p_stVIFInitialIn = (mapi_vif_datatype::stVIFInitialIn *)pvoidParam3;

            p_stVIFInitialIn->VifCrRate_B = VIF_CR_RATE_B;
            p_stVIFInitialIn->VifCrInvert_B = VIF_CR_INVERT_B;
            p_stVIFInitialIn->VifCrRate_GH = VIF_CR_RATE_GH;
            p_stVIFInitialIn->VifCrInvert_GH = VIF_CR_INVERT_GH;
            p_stVIFInitialIn->VifCrRate_DK = VIF_CR_RATE_DK;
            p_stVIFInitialIn->VifCrInvert_DK = VIF_CR_INVERT_DK;
            p_stVIFInitialIn->VifCrRate_I = VIF_CR_RATE_I;
            p_stVIFInitialIn->VifCrInvert_I = VIF_CR_INVERT_I;
            p_stVIFInitialIn->VifCrRate_L = VIF_CR_RATE_L;
            p_stVIFInitialIn->VifCrInvert_L = VIF_CR_INVERT_L;
            p_stVIFInitialIn->VifCrRate_LL = VIF_CR_RATE_LL;
            p_stVIFInitialIn->VifCrInvert_LL = VIF_CR_INVERT_LL;
            p_stVIFInitialIn->VifCrRate_MN = VIF_CR_RATE_MN;
            p_stVIFInitialIn->VifCrInvert_MN = VIF_CR_INVERT_MN;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VIF_NOTCH_SOSFILTER:
        {
            MS_U32 u32NotchDataLength = u32Param2;
            MAPI_U16* pu16NotchData = (MAPI_U16 *)pvoidParam3;
            MAPI_U16* pu16SOSFilterData = ((MAPI_U16 *)pvoidParam3) + u32NotchDataLength;
            switch((mapi_vif_datatype::EN_VIF_SOUND_SYSTEM)u32Param1)
            {
                case mapi_vif_datatype::E_VIF_SOUND_B_STEREO_A2:
                    pu16NotchData[0] = 0x03D1;   //Vif_N_A1_C0
                    pu16NotchData[1] = 0x0628;   //Vif_N_A1_C1
                    pu16NotchData[2] = 0x0406;   //Vif_N_A1_C2

                    pu16NotchData[3] = 0x03D4;   //Vif_N_A2_C0
                    pu16NotchData[4] = 0x0628;   //Vif_N_A2_C1
                    pu16NotchData[5] = 0x0403;   //Vif_N_A2_C2

                    pu16SOSFilterData[0] = 0x01A6;   //Vif_SOS_11_C0
                    pu16SOSFilterData[1] = 0x0628;   //Vif_SOS_11_C1
                    pu16SOSFilterData[2] = 0x0200;   //Vif_SOS_11_C2
                    pu16SOSFilterData[3] = 0x0649;   //Vif_SOS_11_C3
                    pu16SOSFilterData[4] = 0x0200;   //Vif_SOS_11_C4

                    pu16SOSFilterData[5] = 0x03D1;   //Vif_SOS_12_C0
                    pu16SOSFilterData[6] = 0x0628;   //Vif_SOS_12_C1
                    pu16SOSFilterData[7] = 0x0200;   //Vif_SOS_12_C2
                    pu16SOSFilterData[8] = 0x0406;   //Vif_SOS_12_C3
                    pu16SOSFilterData[9] = 0x0200;   //Vif_SOS_12_C4
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_B_MONO_NICAM:
                    pu16NotchData[0] = 0x03D1;
                    pu16NotchData[1] = 0x0628;
                    pu16NotchData[2] = 0x0406;

                    pu16NotchData[3] = 0x03D5;
                    pu16NotchData[4] = 0x0628;
                    pu16NotchData[5] = 0x0402;

                    pu16SOSFilterData[0] = 0x01A6;
                    pu16SOSFilterData[1] = 0x0628;
                    pu16SOSFilterData[2] = 0x0200;
                    pu16SOSFilterData[3] = 0x0649;
                    pu16SOSFilterData[4] = 0x0200;

                    pu16SOSFilterData[5] = 0x03D1;
                    pu16SOSFilterData[6] = 0x0628;
                    pu16SOSFilterData[7] = 0x0200;
                    pu16SOSFilterData[8] = 0x0406;
                    pu16SOSFilterData[9] = 0x0200;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_GH_STEREO_A2:
                    pu16NotchData[0] = 0x03C7;
                    pu16NotchData[1] = 0x0628;
                    pu16NotchData[2] = 0x0411;

                    pu16NotchData[3] = 0x03CC;
                    pu16NotchData[4] = 0x0628;
                    pu16NotchData[5] = 0x040B;

                    pu16SOSFilterData[0] = 0x00DC;
                    pu16SOSFilterData[1] = 0x0628;
                    pu16SOSFilterData[2] = 0x0200;
                    pu16SOSFilterData[3] = 0x071B;
                    pu16SOSFilterData[4] = 0x0200;

                    pu16SOSFilterData[5] = 0x03C7;
                    pu16SOSFilterData[6] = 0x0628;
                    pu16SOSFilterData[7] = 0x0200;
                    pu16SOSFilterData[8] = 0x0411;
                    pu16SOSFilterData[9] = 0x0200;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_GH_MONO_NICAM:
                    pu16NotchData[0] = 0x03C7;
                    pu16NotchData[1] = 0x0628;
                    pu16NotchData[2] = 0x0411;

                    pu16NotchData[3] = 0x03CF;
                    pu16NotchData[4] = 0x0628;
                    pu16NotchData[5] = 0x0409;

                    pu16SOSFilterData[0] = 0x00DC;
                    pu16SOSFilterData[1] = 0x0628;
                    pu16SOSFilterData[2] = 0x0200;
                    pu16SOSFilterData[3] = 0x071B;
                    pu16SOSFilterData[4] = 0x0200;

                    pu16SOSFilterData[5] = 0x03C7;
                    pu16SOSFilterData[6] = 0x0628;
                    pu16SOSFilterData[7] = 0x0200;
                    pu16SOSFilterData[8] = 0x0411;
                    pu16SOSFilterData[9] = 0x0200;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_I:
                    pu16NotchData[0] = 0x038A;//0x03C7;
                    pu16NotchData[1] = 0x0661;//0x0628;
                    pu16NotchData[2] = 0x0411;//0x0411;

                    pu16NotchData[3] = 0x0395;//0x03D2;
                    pu16NotchData[4] = 0x0661;//0x0628;
                    pu16NotchData[5] = 0x0405;//0x0405;

                    pu16SOSFilterData[0] = 0x00CE;//0x00DC;
                    pu16SOSFilterData[1] = 0x0661;//0x0628;
                    pu16SOSFilterData[2] = 0x0200;//0x0200;
                    pu16SOSFilterData[3] = 0x071B;//0x071B;
                    pu16SOSFilterData[4] = 0x0200;//0x0200;

                    pu16SOSFilterData[5] = 0x038A;//0x03C7;
                    pu16SOSFilterData[6] = 0x0661;//0x0628;
                    pu16SOSFilterData[7] = 0x0200;//0x0200;
                    pu16SOSFilterData[8] = 0x0411;//0x0411;
                    pu16SOSFilterData[9] = 0x0200;//0x0200;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_DK1_STEREO_A2:
                    pu16NotchData[0] = 0x03D6;
                    pu16NotchData[1] = 0x0628;
                    pu16NotchData[2] = 0x0401;

                    pu16NotchData[3] = 0x03D3;
                    pu16NotchData[4] = 0x0628;
                    pu16NotchData[5] = 0x0404;

                    pu16SOSFilterData[0] = 0x0157;
                    pu16SOSFilterData[1] = 0x0628;
                    pu16SOSFilterData[2] = 0x0200;
                    pu16SOSFilterData[3] = 0x069B;
                    pu16SOSFilterData[4] = 0x0200;

                    pu16SOSFilterData[5] = 0x03D6;
                    pu16SOSFilterData[6] = 0x0628;
                    pu16SOSFilterData[7] = 0x0200;
                    pu16SOSFilterData[8] = 0x0401;
                    pu16SOSFilterData[9] = 0x0200;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_DK2_STEREO_A2:
                    pu16NotchData[0] = 0x03D6;
                    pu16NotchData[1] = 0x0628;
                    pu16NotchData[2] = 0x0401;

                    pu16NotchData[3] = 0x03D7;
                    pu16NotchData[4] = 0x0628;
                    pu16NotchData[5] = 0x0400;

                    pu16SOSFilterData[0] = 0x0157;
                    pu16SOSFilterData[1] = 0x0628;
                    pu16SOSFilterData[2] = 0x0200;
                    pu16SOSFilterData[3] = 0x069B;
                    pu16SOSFilterData[4] = 0x0200;

                    pu16SOSFilterData[5] = 0x03D6;
                    pu16SOSFilterData[6] = 0x0628;
                    pu16SOSFilterData[7] = 0x0200;
                    pu16SOSFilterData[8] = 0x0401;
                    pu16SOSFilterData[9] = 0x0200;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_DK3_STEREO_A2:
                    pu16NotchData[0] = 0x03D6;
                    pu16NotchData[1] = 0x0628;
                    pu16NotchData[2] = 0x0401;

                    pu16NotchData[3] = 0x03CA;
                    pu16NotchData[4] = 0x0628;
                    pu16NotchData[5] = 0x040D;

                    pu16SOSFilterData[0] = 0x0157;
                    pu16SOSFilterData[1] = 0x0628;
                    pu16SOSFilterData[2] = 0x0200;
                    pu16SOSFilterData[3] = 0x069B;
                    pu16SOSFilterData[4] = 0x0200;

                    pu16SOSFilterData[5] = 0x03D6;
                    pu16SOSFilterData[6] = 0x0628;
                    pu16SOSFilterData[7] = 0x0200;
                    pu16SOSFilterData[8] = 0x0401;
                    pu16SOSFilterData[9] = 0x0200;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_DK_MONO_NICAM:
                    pu16NotchData[0] = 0x03D6;
                    pu16NotchData[1] = 0x0628;
                    pu16NotchData[2] = 0x0401;

                    pu16NotchData[3] = 0x03CD;
                    pu16NotchData[4] = 0x0628;
                    pu16NotchData[5] = 0x040B;

                    pu16SOSFilterData[0] = 0x0157;
                    pu16SOSFilterData[1] = 0x0628;
                    pu16SOSFilterData[2] = 0x0200;
                    pu16SOSFilterData[3] = 0x069B;
                    pu16SOSFilterData[4] = 0x0200;

                    pu16SOSFilterData[5] = 0x03D6;
                    pu16SOSFilterData[6] = 0x0628;
                    pu16SOSFilterData[7] = 0x0200;
                    pu16SOSFilterData[8] = 0x0401;
                    pu16SOSFilterData[9] = 0x0200;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_L:
                    pu16NotchData[0] = 0x03D6;
                    pu16NotchData[1] = 0x0628;
                    pu16NotchData[2] = 0x0401;

                    pu16NotchData[3] = 0x03CF;
                    pu16NotchData[4] = 0x0628;
                    pu16NotchData[5] = 0x0409;

                    pu16SOSFilterData[0] = 0x0164;
                    pu16SOSFilterData[1] = 0x0628;
                    pu16SOSFilterData[2] = 0x0200;
                    pu16SOSFilterData[3] = 0x068D;
                    pu16SOSFilterData[4] = 0x0200;

                    pu16SOSFilterData[5] = 0x03D6;
                    pu16SOSFilterData[6] = 0x0628;
                    pu16SOSFilterData[7] = 0x0200;
                    pu16SOSFilterData[8] = 0x0401;
                    pu16SOSFilterData[9] = 0x0200;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_LL:
                    pu16NotchData[0] = 0x01A6;
                    pu16NotchData[1] = 0x0628;
                    pu16NotchData[2] = 0x0649;

                    pu16NotchData[3] = 0x01F8;
                    pu16NotchData[4] = 0x0628;
                    pu16NotchData[5] = 0x05F3;

                    pu16SOSFilterData[0] = 0x0000;
                    pu16SOSFilterData[1] = 0x0000;
                    pu16SOSFilterData[2] = 0x0000;
                    pu16SOSFilterData[3] = 0x0000;
                    pu16SOSFilterData[4] = 0x0200;

                    pu16SOSFilterData[5] = 0x01A6;
                    pu16SOSFilterData[6] = 0x0628;
                    pu16SOSFilterData[7] = 0x0200;
                    pu16SOSFilterData[8] = 0x0649;
                    pu16SOSFilterData[9] = 0x0200;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_MN:
                    pu16NotchData[0] = 0x03CF;
                    pu16NotchData[1] = 0x0628;
                    pu16NotchData[2] = 0x0409;

                    pu16NotchData[3] = 0x03D2;
                    pu16NotchData[4] = 0x0628;
                    pu16NotchData[5] = 0x0405;

                    pu16SOSFilterData[0] = 0x0210;
                    pu16SOSFilterData[1] = 0x0628;
                    pu16SOSFilterData[2] = 0x0200;
                    pu16SOSFilterData[3] = 0x05DA;
                    pu16SOSFilterData[4] = 0x0200;

                    pu16SOSFilterData[5] = 0x03CF;
                    pu16SOSFilterData[6] = 0x0628;
                    pu16SOSFilterData[7] = 0x0200;
                    pu16SOSFilterData[8] = 0x0409;
                    pu16SOSFilterData[9] = 0x0200;
                    break;

                default:
                    printf("Warning:%s(),%d\n",__func__,__LINE__);
                    break;
            }
        }
            break;


        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_DTV_IF_FREQ:
        {
            switch (u32Param1) // demod mode
            {
                case E_TUNER_DTV_DVB_T_MODE:
                case E_TUNER_DTV_DVB_T2_MODE:
                    switch(u32Param2) // bandwidth
                    {
                        case E_RF_CH_BAND_6MHz:
                            *((MS_U32 *)pvoidParam3)=DVBT_6M;
                            break;
                        case E_RF_CH_BAND_7MHz:
                            *((MS_U32 *)pvoidParam3)=DVBT_7M;
                            break;
                        case E_RF_CH_BAND_8MHz:
                            *((MS_U32 *)pvoidParam3)=DVBT_8M;
                            break;
                        default:
                            printf("Error:%s(),%d\n",__func__,__LINE__);
                            return FALSE;
                            break;
                    }
                    break;
                case E_TUNER_DTV_DVB_C_MODE:
                    *((MS_U32 *)pvoidParam3)=QAM_8M;
                    break;
                case E_TUNER_DTV_ATSC_MODE:
                    *((MS_U32 *)pvoidParam3)=ATSC_6M;
                    break;
                case E_TUNER_DTV_DTMB_MODE:
                    *((MS_U32 *)pvoidParam3)=DMBT_8M;
                    break;
                case E_TUNER_DTV_ISDB_MODE:
                    *((MS_U32 *)pvoidParam3)=ISDBT_6M;
                    break;
                default:
                    printf("Error:%s(),%d\n",__func__,__LINE__);
                    return FALSE;
                    break;
            }
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_IQ_SWAP:
        {
            MS_U8 *u8IqSwap = (MS_U8 *)pvoidParam3;
            *u8IqSwap = TUNER_DTV_IQ_SWAP;
            if ( u32Param1 )
            {
                *u8IqSwap ^= 0x01;
            }
        }
            break;
        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_RF_TABLE:
        {
            (*(DMD_SSI_TABLE **)pvoidParam3)=NULL; // if not used, should return NULL;
            return FALSE;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_RF_LEVEL:
        {
            tmErrorCode_t err = TM_OK;
            UInt8 u8_rf_level_1_2_dubV = 0;

            err = tmbslTDA18275_GetPowerLevel(0, &u8_rf_level_1_2_dubV);

            if(err != TM_OK)
            {
                *((float *)pvoidParam3)=-10.0f;
                printf("NuTune TDA18275 RF Level Get Error\n");
            }
            else
            {
                *((float *)pvoidParam3)=(float)u8_rf_level_1_2_dubV/2.0-107.0f; // dBuV to dBm
                DBG_TUNER(printf("NXP TDA18275 RF Level %f dBm, %d(1/2dbuV)\n",*((float *)pvoidParam3),u8_rf_level_1_2_dubV);)
            }
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_DEMOD_CONFIG:
        {

            switch (u32Param1) // demod mode
            {
                case E_TUNER_DTV_DVB_T_MODE:
                    /*
                    static MS_U8 u8TUNER_DVBT_DSPRegInitExt[]={
                                                                                                1, // version, should be matched with library
                                                                                                0, // reserved
                                                                                                0, // Size_L
                                                                                                0, // Size_H
                                                                                                E_DMD_DVBT_CFG_IQ_SWAP, // Addr_L
                                                                                                E_DMD_DVBT_CFG_IQ_SWAP>>8, // Addr_H
                                                                                                0xFF, // Mask
                                                                                                0x00}; // Value
                    u8TUNER_DVBT_DSPRegInitExt[2]=(sizeof(u8TUNER_DVBT_DSPRegInitExt)-4)/4;
                    u8TUNER_DVBT_DSPRegInitExt[3]=((sizeof(u8TUNER_DVBT_DSPRegInitExt)-4)/4)>>8;
                    *((MS_U8 **)pvoidParam3)=u8TUNER_DVBT_DSPRegInitExt;
                    */
                    *((MS_U8 **)pvoidParam3)=NULL;
                    break;
                case E_TUNER_DTV_DVB_C_MODE:
                    /*
                        E_DMD_DVBC_OP_ZIF_EN,                            //ZIF
                        E_DMD_DVBC_OP_NORMALIF_EN,                  //NIF
                        E_DMD_DVBC_OP_LIF_EN,                            //LIF
                        E_DMD_DVBC_OP_SAWLESS_EN,                  //SAWLESS
                        E_DMD_DVBC_OP_IQB_EN,
                        E_DMD_DVBC_CFG_ZIF,
                        E_DMD_DVBC_IF_INV_PWM_OUT_EN,           //Sony Tuner , 0x10
                    */

                    static MS_U8 u8TUNER_DVBC_DSPRegInitExt[]={
                                                                                                1, // version, should be matched with library
                                                                                                0, // reserved
                                                                                                0, // Size_L
                                                                                                0, // Size_H
                                                                                                E_DMD_DVBC_NO_SIGNAL_NUM_TH,
                                                                                                E_DMD_DVBC_NO_SIGNAL_NUM_TH>>8,
                                                                                                0xFF,
                                                                                                0x14,
                                                                                                E_DMD_DVBC_NO_SIGNAL_GAIN_TH_L,
                                                                                                E_DMD_DVBC_NO_SIGNAL_GAIN_TH_L>>8,
                                                                                                0xFF,
                                                                                                0x00,
                                                                                                E_DMD_DVBC_NO_SIGNAL_GAIN_TH_H,
                                                                                                E_DMD_DVBC_NO_SIGNAL_GAIN_TH_H>>8,
                                                                                                0xFF,
                                                                                                0x60,
                                                                                                };
                    u8TUNER_DVBC_DSPRegInitExt[2]=(sizeof(u8TUNER_DVBC_DSPRegInitExt)-4)/4;
                    u8TUNER_DVBC_DSPRegInitExt[3]=((sizeof(u8TUNER_DVBC_DSPRegInitExt)-4)/4)>>8;
                    *((MS_U8 **)pvoidParam3)=u8TUNER_DVBC_DSPRegInitExt;

                    //*((MS_U8 **)pvoidParam3)=NULL;
                    break;
                default:
                    printf("Error:%s(),%d\n",__func__,__LINE__);
                    return FALSE;
                    break;
            }
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_PEAKING_PARAMETER:
        {
            mapi_vif_datatype::stVIFUserFilter *VIF_UserFilter = (mapi_vif_datatype::stVIFUserFilter *)pvoidParam3;
            ASSERT(VIF_UserFilter);
            switch (u32Param1)
            {
                case E_RFBAND_VHF_LOW:
                    if((u32Param2==(MS_U32)mapi_demodulator_datatype::IF_FREQ_B)||(u32Param2==(MS_U32)mapi_demodulator_datatype::IF_FREQ_G))
                    {
                        VIF_UserFilter->VifSos21FilterC0  = 0x02F8;
                        VIF_UserFilter->VifSos21FilterC1  = 0x0620;
                        VIF_UserFilter->VifSos21FilterC2  = 0x0207;
                        VIF_UserFilter->VifSos21FilterC3  = 0x0508;
                        VIF_UserFilter->VifSos21FilterC4  = 0x01DA;

                        VIF_UserFilter->VifSos22FilterC0  = 0x02EE;
                        VIF_UserFilter->VifSos22FilterC1  = 0x06C4;
                        VIF_UserFilter->VifSos22FilterC2  = 0x01F5;
                        VIF_UserFilter->VifSos22FilterC3  = 0x0512;
                        VIF_UserFilter->VifSos22FilterC4  = 0x0146;

                        VIF_UserFilter->VifSos31FilterC0  = 0x028B;
                        VIF_UserFilter->VifSos31FilterC1  = 0x06A8;
                        VIF_UserFilter->VifSos31FilterC2  = 0x0158;
                        VIF_UserFilter->VifSos31FilterC3  = 0x0576;
                        VIF_UserFilter->VifSos31FilterC4  = 0x0200;
                        VIF_UserFilter->VifSos32FilterC0  = 0x02B8;
                        VIF_UserFilter->VifSos32FilterC1  = 0x0713;
                        VIF_UserFilter->VifSos32FilterC2  = 0x00ED;
                        VIF_UserFilter->VifSos32FilterC3  = 0x0548;
                        VIF_UserFilter->VifSos32FilterC4  = 0x0200;
                    }
                    else if(u32Param2==(MS_U32)mapi_demodulator_datatype::IF_FREQ_DK)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = 0x02F8;
                        VIF_UserFilter->VifSos21FilterC1  = 0x0620;
                        VIF_UserFilter->VifSos21FilterC2  = 0x0207;
                        VIF_UserFilter->VifSos21FilterC3  = 0x0508;
                        VIF_UserFilter->VifSos21FilterC4  = 0x01DA;

                        VIF_UserFilter->VifSos22FilterC0  = 0x02EE;
                        VIF_UserFilter->VifSos22FilterC1  = 0x06C4;
                        VIF_UserFilter->VifSos22FilterC2  = 0x01F5;
                        VIF_UserFilter->VifSos22FilterC3  = 0x0512;
                        VIF_UserFilter->VifSos22FilterC4  = 0x0146;

                        VIF_UserFilter->VifSos31FilterC0  = 0x028B;
                        VIF_UserFilter->VifSos31FilterC1  = 0x06A8;
                        VIF_UserFilter->VifSos31FilterC2  = 0x0158;
                        VIF_UserFilter->VifSos31FilterC3  = 0x0576;
                        VIF_UserFilter->VifSos31FilterC4  = 0x0200;
                        VIF_UserFilter->VifSos32FilterC0  = 0x02B8;
                        VIF_UserFilter->VifSos32FilterC1  = 0x0713;
                        VIF_UserFilter->VifSos32FilterC2  = 0x00ED;
                        VIF_UserFilter->VifSos32FilterC3  = 0x0548;
                        VIF_UserFilter->VifSos32FilterC4  = 0x0200;
                    }
                    else if(u32Param2==(MS_U32)mapi_demodulator_datatype::IF_FREQ_I)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = 0x02F8;
                        VIF_UserFilter->VifSos21FilterC1  = 0x0620;
                        VIF_UserFilter->VifSos21FilterC2  = 0x0207;
                        VIF_UserFilter->VifSos21FilterC3  = 0x0508;
                        VIF_UserFilter->VifSos21FilterC4  = 0x01DA;

                        VIF_UserFilter->VifSos22FilterC0  = 0x02EE;
                        VIF_UserFilter->VifSos22FilterC1  = 0x06C4;
                        VIF_UserFilter->VifSos22FilterC2  = 0x01F5;
                        VIF_UserFilter->VifSos22FilterC3  = 0x0512;
                        VIF_UserFilter->VifSos22FilterC4  = 0x0146;

                        VIF_UserFilter->VifSos31FilterC0  = 0x028B;
                        VIF_UserFilter->VifSos31FilterC1  = 0x06A8;
                        VIF_UserFilter->VifSos31FilterC2  = 0x0158;
                        VIF_UserFilter->VifSos31FilterC3  = 0x0576;
                        VIF_UserFilter->VifSos31FilterC4  = 0x0200;
                        VIF_UserFilter->VifSos32FilterC0  = 0x02B8;
                        VIF_UserFilter->VifSos32FilterC1  = 0x0713;
                        VIF_UserFilter->VifSos32FilterC2  = 0x00ED;
                        VIF_UserFilter->VifSos32FilterC3  = 0x0548;
                        VIF_UserFilter->VifSos32FilterC4  = 0x0200;
                    }
                    else if(u32Param2 == (MS_U32)mapi_demodulator_datatype::IF_FREQ_L)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = 0x02F8;
                        VIF_UserFilter->VifSos21FilterC1  = 0x0620;
                        VIF_UserFilter->VifSos21FilterC2  = 0x0207;
                        VIF_UserFilter->VifSos21FilterC3  = 0x0508;
                        VIF_UserFilter->VifSos21FilterC4  = 0x01DA;

                        VIF_UserFilter->VifSos22FilterC0  = 0x02EE;
                        VIF_UserFilter->VifSos22FilterC1  = 0x06C4;
                        VIF_UserFilter->VifSos22FilterC2  = 0x01F5;
                        VIF_UserFilter->VifSos22FilterC3  = 0x0512;
                        VIF_UserFilter->VifSos22FilterC4  = 0x0146;

                        VIF_UserFilter->VifSos31FilterC0  = 0x028B;
                        VIF_UserFilter->VifSos31FilterC1  = 0x06A8;
                        VIF_UserFilter->VifSos31FilterC2  = 0x0158;
                        VIF_UserFilter->VifSos31FilterC3  = 0x0576;
                        VIF_UserFilter->VifSos31FilterC4  = 0x0200;
                        VIF_UserFilter->VifSos32FilterC0  = 0x02B8;
                        VIF_UserFilter->VifSos32FilterC1  = 0x0713;
                        VIF_UserFilter->VifSos32FilterC2  = 0x00ED;
                        VIF_UserFilter->VifSos32FilterC3  = 0x0548;
                        VIF_UserFilter->VifSos32FilterC4  = 0x0200;
                    }
                    else if(u32Param2 == (MS_U32)mapi_demodulator_datatype::IF_FREQ_L_PRIME)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = 0x02F8;
                        VIF_UserFilter->VifSos21FilterC1  = 0x0620;
                        VIF_UserFilter->VifSos21FilterC2  = 0x0207;
                        VIF_UserFilter->VifSos21FilterC3  = 0x0508;
                        VIF_UserFilter->VifSos21FilterC4  = 0x01DA;

                        VIF_UserFilter->VifSos22FilterC0  = 0x02EE;
                        VIF_UserFilter->VifSos22FilterC1  = 0x06C4;
                        VIF_UserFilter->VifSos22FilterC2  = 0x01F5;
                        VIF_UserFilter->VifSos22FilterC3  = 0x0512;
                        VIF_UserFilter->VifSos22FilterC4  = 0x0146;

                        VIF_UserFilter->VifSos31FilterC0  = 0x028B;
                        VIF_UserFilter->VifSos31FilterC1  = 0x06A8;
                        VIF_UserFilter->VifSos31FilterC2  = 0x0158;
                        VIF_UserFilter->VifSos31FilterC3  = 0x0576;
                        VIF_UserFilter->VifSos31FilterC4  = 0x0200;
                        VIF_UserFilter->VifSos32FilterC0  = 0x02B8;
                        VIF_UserFilter->VifSos32FilterC1  = 0x0713;
                        VIF_UserFilter->VifSos32FilterC2  = 0x00ED;
                        VIF_UserFilter->VifSos32FilterC3  = 0x0548;
                        VIF_UserFilter->VifSos32FilterC4  = 0x0200;
                    }
                    else
                    {
                        printf("Error:%s(),%d\n",__func__,__LINE__);
                        return FALSE;
                    }
                    break;
                case E_RFBAND_VHF_HIGH:
                    if((u32Param2 == (MS_U32)mapi_demodulator_datatype::IF_FREQ_B) || (u32Param2 == (MS_U32)mapi_demodulator_datatype::IF_FREQ_G))
                    {
                        VIF_UserFilter->VifSos21FilterC0  = 0x02F8;
                        VIF_UserFilter->VifSos21FilterC1  = 0x0620;
                        VIF_UserFilter->VifSos21FilterC2  = 0x0207;
                        VIF_UserFilter->VifSos21FilterC3  = 0x0508;
                        VIF_UserFilter->VifSos21FilterC4  = 0x01DA;

                        VIF_UserFilter->VifSos22FilterC0  = 0x02EE;
                        VIF_UserFilter->VifSos22FilterC1  = 0x06C4;
                        VIF_UserFilter->VifSos22FilterC2  = 0x01F5;
                        VIF_UserFilter->VifSos22FilterC3  = 0x0512;
                        VIF_UserFilter->VifSos22FilterC4  = 0x0146;

                        VIF_UserFilter->VifSos31FilterC0  = 0x028B;
                        VIF_UserFilter->VifSos31FilterC1  = 0x06A8;
                        VIF_UserFilter->VifSos31FilterC2  = 0x0158;
                        VIF_UserFilter->VifSos31FilterC3  = 0x0576;
                        VIF_UserFilter->VifSos31FilterC4  = 0x0200;
                        VIF_UserFilter->VifSos32FilterC0  = 0x02B8;
                        VIF_UserFilter->VifSos32FilterC1  = 0x0713;
                        VIF_UserFilter->VifSos32FilterC2  = 0x00ED;
                        VIF_UserFilter->VifSos32FilterC3  = 0x0548;
                        VIF_UserFilter->VifSos32FilterC4  = 0x0200;
                    }
                    else if(u32Param2 == (MS_U32)mapi_demodulator_datatype::IF_FREQ_DK)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = 0x02F8;
                        VIF_UserFilter->VifSos21FilterC1  = 0x0620;
                        VIF_UserFilter->VifSos21FilterC2  = 0x0207;
                        VIF_UserFilter->VifSos21FilterC3  = 0x0508;
                        VIF_UserFilter->VifSos21FilterC4  = 0x01DA;

                        VIF_UserFilter->VifSos22FilterC0  = 0x02EE;
                        VIF_UserFilter->VifSos22FilterC1  = 0x06C4;
                        VIF_UserFilter->VifSos22FilterC2  = 0x01F5;
                        VIF_UserFilter->VifSos22FilterC3  = 0x0512;
                        VIF_UserFilter->VifSos22FilterC4  = 0x0146;

                        VIF_UserFilter->VifSos31FilterC0  = 0x028B;
                        VIF_UserFilter->VifSos31FilterC1  = 0x06A8;
                        VIF_UserFilter->VifSos31FilterC2  = 0x0158;
                        VIF_UserFilter->VifSos31FilterC3  = 0x0576;
                        VIF_UserFilter->VifSos31FilterC4  = 0x0200;
                        VIF_UserFilter->VifSos32FilterC0  = 0x02B8;
                        VIF_UserFilter->VifSos32FilterC1  = 0x0713;
                        VIF_UserFilter->VifSos32FilterC2  = 0x00ED;
                        VIF_UserFilter->VifSos32FilterC3  = 0x0548;
                        VIF_UserFilter->VifSos32FilterC4  = 0x0200;
                    }
                    else if(u32Param2 == (MS_U32)mapi_demodulator_datatype::IF_FREQ_I)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = 0x02F8;
                        VIF_UserFilter->VifSos21FilterC1  = 0x0620;
                        VIF_UserFilter->VifSos21FilterC2  = 0x0207;
                        VIF_UserFilter->VifSos21FilterC3  = 0x0508;
                        VIF_UserFilter->VifSos21FilterC4  = 0x01DA;

                        VIF_UserFilter->VifSos22FilterC0  = 0x02EE;
                        VIF_UserFilter->VifSos22FilterC1  = 0x06C4;
                        VIF_UserFilter->VifSos22FilterC2  = 0x01F5;
                        VIF_UserFilter->VifSos22FilterC3  = 0x0512;
                        VIF_UserFilter->VifSos22FilterC4  = 0x0146;

                        VIF_UserFilter->VifSos31FilterC0  = 0x028B;
                        VIF_UserFilter->VifSos31FilterC1  = 0x06A8;
                        VIF_UserFilter->VifSos31FilterC2  = 0x0158;
                        VIF_UserFilter->VifSos31FilterC3  = 0x0576;
                        VIF_UserFilter->VifSos31FilterC4  = 0x0200;
                        VIF_UserFilter->VifSos32FilterC0  = 0x02B8;
                        VIF_UserFilter->VifSos32FilterC1  = 0x0713;
                        VIF_UserFilter->VifSos32FilterC2  = 0x00ED;
                        VIF_UserFilter->VifSos32FilterC3  = 0x0548;
                        VIF_UserFilter->VifSos32FilterC4  = 0x0200;
                    }
                    else if(u32Param2 == (MS_U32)mapi_demodulator_datatype::IF_FREQ_L)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = 0x02F8;
                        VIF_UserFilter->VifSos21FilterC1  = 0x0620;
                        VIF_UserFilter->VifSos21FilterC2  = 0x0207;
                        VIF_UserFilter->VifSos21FilterC3  = 0x0508;
                        VIF_UserFilter->VifSos21FilterC4  = 0x01DA;

                        VIF_UserFilter->VifSos22FilterC0  = 0x02EE;
                        VIF_UserFilter->VifSos22FilterC1  = 0x06C4;
                        VIF_UserFilter->VifSos22FilterC2  = 0x01F5;
                        VIF_UserFilter->VifSos22FilterC3  = 0x0512;
                        VIF_UserFilter->VifSos22FilterC4  = 0x0146;

                        VIF_UserFilter->VifSos31FilterC0  = 0x028B;
                        VIF_UserFilter->VifSos31FilterC1  = 0x06A8;
                        VIF_UserFilter->VifSos31FilterC2  = 0x0158;
                        VIF_UserFilter->VifSos31FilterC3  = 0x0576;
                        VIF_UserFilter->VifSos31FilterC4  = 0x0200;
                        VIF_UserFilter->VifSos32FilterC0  = 0x02B8;
                        VIF_UserFilter->VifSos32FilterC1  = 0x0713;
                        VIF_UserFilter->VifSos32FilterC2  = 0x00ED;
                        VIF_UserFilter->VifSos32FilterC3  = 0x0548;
                        VIF_UserFilter->VifSos32FilterC4  = 0x0200;
                    }
                    else if(u32Param2 == (MS_U32)mapi_demodulator_datatype::IF_FREQ_L_PRIME)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = 0x02F8;
                        VIF_UserFilter->VifSos21FilterC1  = 0x0620;
                        VIF_UserFilter->VifSos21FilterC2  = 0x0207;
                        VIF_UserFilter->VifSos21FilterC3  = 0x0508;
                        VIF_UserFilter->VifSos21FilterC4  = 0x01DA;

                        VIF_UserFilter->VifSos22FilterC0  = 0x02EE;
                        VIF_UserFilter->VifSos22FilterC1  = 0x06C4;
                        VIF_UserFilter->VifSos22FilterC2  = 0x01F5;
                        VIF_UserFilter->VifSos22FilterC3  = 0x0512;
                        VIF_UserFilter->VifSos22FilterC4  = 0x0146;

                        VIF_UserFilter->VifSos31FilterC0  = 0x028B;
                        VIF_UserFilter->VifSos31FilterC1  = 0x06A8;
                        VIF_UserFilter->VifSos31FilterC2  = 0x0158;
                        VIF_UserFilter->VifSos31FilterC3  = 0x0576;
                        VIF_UserFilter->VifSos31FilterC4  = 0x0200;
                        VIF_UserFilter->VifSos32FilterC0  = 0x02B8;
                        VIF_UserFilter->VifSos32FilterC1  = 0x0713;
                        VIF_UserFilter->VifSos32FilterC2  = 0x00ED;
                        VIF_UserFilter->VifSos32FilterC3  = 0x0548;
                        VIF_UserFilter->VifSos32FilterC4  = 0x0200;
                    }
                    else
                    {
                        printf("Error:%s(),%d\n",__func__,__LINE__);
                        return FALSE;
                    }
                    break;
                case E_RFBAND_UHF:
                    if((u32Param2 == (MS_U32)mapi_demodulator_datatype::IF_FREQ_B) || (u32Param2 == (MS_U32)mapi_demodulator_datatype::IF_FREQ_G))
                    {
                        VIF_UserFilter->VifSos21FilterC0  = 0x02EE;
                        VIF_UserFilter->VifSos21FilterC1  = 0x062D;
                        VIF_UserFilter->VifSos21FilterC2  = 0x0209;
                        VIF_UserFilter->VifSos21FilterC3  = 0x0512;
                        VIF_UserFilter->VifSos21FilterC4  = 0x01CA;

                        VIF_UserFilter->VifSos22FilterC0  = 0x0291;
                        VIF_UserFilter->VifSos22FilterC1  = 0x070A;
                        VIF_UserFilter->VifSos22FilterC2  = 0x01D9;
                        VIF_UserFilter->VifSos22FilterC3  = 0x056F;
                        VIF_UserFilter->VifSos22FilterC4  = 0x011D;

                        VIF_UserFilter->VifSos31FilterC0  = 0x02D3;
                        VIF_UserFilter->VifSos31FilterC1  = 0x0685;
                        VIF_UserFilter->VifSos31FilterC2  = 0x017B;
                        VIF_UserFilter->VifSos31FilterC3  = 0x052D;
                        VIF_UserFilter->VifSos31FilterC4  = 0x0200;
                        VIF_UserFilter->VifSos32FilterC0  = 0x02E1;
                        VIF_UserFilter->VifSos32FilterC1  = 0x06F7;
                        VIF_UserFilter->VifSos32FilterC2  = 0x010A;
                        VIF_UserFilter->VifSos32FilterC3  = 0x051F;
                        VIF_UserFilter->VifSos32FilterC4  = 0x0200;
                    }
                    else if(u32Param2 == (MS_U32)mapi_demodulator_datatype::IF_FREQ_DK)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = 0x02EE;
                        VIF_UserFilter->VifSos21FilterC1  = 0x062D;
                        VIF_UserFilter->VifSos21FilterC2  = 0x0209;
                        VIF_UserFilter->VifSos21FilterC3  = 0x0512;
                        VIF_UserFilter->VifSos21FilterC4  = 0x01CA;

                        VIF_UserFilter->VifSos22FilterC0  = 0x0291;
                        VIF_UserFilter->VifSos22FilterC1  = 0x070A;
                        VIF_UserFilter->VifSos22FilterC2  = 0x01D9;
                        VIF_UserFilter->VifSos22FilterC3  = 0x056F;
                        VIF_UserFilter->VifSos22FilterC4  = 0x011D;

                        VIF_UserFilter->VifSos31FilterC0  = 0x02D3;
                        VIF_UserFilter->VifSos31FilterC1  = 0x0685;
                        VIF_UserFilter->VifSos31FilterC2  = 0x017B;
                        VIF_UserFilter->VifSos31FilterC3  = 0x052D;
                        VIF_UserFilter->VifSos31FilterC4  = 0x0200;
                        VIF_UserFilter->VifSos32FilterC0  = 0x02E1;
                        VIF_UserFilter->VifSos32FilterC1  = 0x06F7;
                        VIF_UserFilter->VifSos32FilterC2  = 0x010A;
                        VIF_UserFilter->VifSos32FilterC3  = 0x051F;
                        VIF_UserFilter->VifSos32FilterC4  = 0x0200;
                    }
                    else if(u32Param2 == (MS_U32)mapi_demodulator_datatype::IF_FREQ_I)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = 0x02EE;
                        VIF_UserFilter->VifSos21FilterC1  = 0x062D;
                        VIF_UserFilter->VifSos21FilterC2  = 0x0209;
                        VIF_UserFilter->VifSos21FilterC3  = 0x0512;
                        VIF_UserFilter->VifSos21FilterC4  = 0x01CA;

                        VIF_UserFilter->VifSos22FilterC0  = 0x0291;
                        VIF_UserFilter->VifSos22FilterC1  = 0x070A;
                        VIF_UserFilter->VifSos22FilterC2  = 0x01D9;
                        VIF_UserFilter->VifSos22FilterC3  = 0x056F;
                        VIF_UserFilter->VifSos22FilterC4  = 0x011D;

                        VIF_UserFilter->VifSos31FilterC0  = 0x02D3;
                        VIF_UserFilter->VifSos31FilterC1  = 0x0685;
                        VIF_UserFilter->VifSos31FilterC2  = 0x017B;
                        VIF_UserFilter->VifSos31FilterC3  = 0x052D;
                        VIF_UserFilter->VifSos31FilterC4  = 0x0200;
                        VIF_UserFilter->VifSos32FilterC0  = 0x02E1;
                        VIF_UserFilter->VifSos32FilterC1  = 0x06F7;
                        VIF_UserFilter->VifSos32FilterC2  = 0x010A;
                        VIF_UserFilter->VifSos32FilterC3  = 0x051F;
                        VIF_UserFilter->VifSos32FilterC4  = 0x0200;
                    }
                    else if(u32Param2 == (MS_U32)mapi_demodulator_datatype::IF_FREQ_L)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = 0x02EE;
                        VIF_UserFilter->VifSos21FilterC1  = 0x062D;
                        VIF_UserFilter->VifSos21FilterC2  = 0x0209;
                        VIF_UserFilter->VifSos21FilterC3  = 0x0512;
                        VIF_UserFilter->VifSos21FilterC4  = 0x01CA;

                        VIF_UserFilter->VifSos22FilterC0  = 0x0291;
                        VIF_UserFilter->VifSos22FilterC1  = 0x070A;
                        VIF_UserFilter->VifSos22FilterC2  = 0x01D9;
                        VIF_UserFilter->VifSos22FilterC3  = 0x056F;
                        VIF_UserFilter->VifSos22FilterC4  = 0x011D;

                        VIF_UserFilter->VifSos31FilterC0  = 0x02D3;
                        VIF_UserFilter->VifSos31FilterC1  = 0x0685;
                        VIF_UserFilter->VifSos31FilterC2  = 0x017B;
                        VIF_UserFilter->VifSos31FilterC3  = 0x052D;
                        VIF_UserFilter->VifSos31FilterC4  = 0x0200;
                        VIF_UserFilter->VifSos32FilterC0  = 0x02E1;
                        VIF_UserFilter->VifSos32FilterC1  = 0x06F7;
                        VIF_UserFilter->VifSos32FilterC2  = 0x010A;
                        VIF_UserFilter->VifSos32FilterC3  = 0x051F;
                        VIF_UserFilter->VifSos32FilterC4  = 0x0200;
                    }
                    else if(u32Param2 == (MS_U32)mapi_demodulator_datatype::IF_FREQ_L_PRIME)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = 0x02EE;
                        VIF_UserFilter->VifSos21FilterC1  = 0x062D;
                        VIF_UserFilter->VifSos21FilterC2  = 0x0209;
                        VIF_UserFilter->VifSos21FilterC3  = 0x0512;
                        VIF_UserFilter->VifSos21FilterC4  = 0x01CA;

                        VIF_UserFilter->VifSos22FilterC0  = 0x0291;
                        VIF_UserFilter->VifSos22FilterC1  = 0x070A;
                        VIF_UserFilter->VifSos22FilterC2  = 0x01D9;
                        VIF_UserFilter->VifSos22FilterC3  = 0x056F;
                        VIF_UserFilter->VifSos22FilterC4  = 0x011D;

                        VIF_UserFilter->VifSos31FilterC0  = 0x02D3;
                        VIF_UserFilter->VifSos31FilterC1  = 0x0685;
                        VIF_UserFilter->VifSos31FilterC2  = 0x017B;
                        VIF_UserFilter->VifSos31FilterC3  = 0x052D;
                        VIF_UserFilter->VifSos31FilterC4  = 0x0200;
                        VIF_UserFilter->VifSos32FilterC0  = 0x02E1;
                        VIF_UserFilter->VifSos32FilterC1  = 0x06F7;
                        VIF_UserFilter->VifSos32FilterC2  = 0x010A;
                        VIF_UserFilter->VifSos32FilterC3  = 0x051F;
                        VIF_UserFilter->VifSos32FilterC4  = 0x0200;
                    }
                    else
                    {
                        printf("Error:%s(),%d\n",__func__,__LINE__);
                        return FALSE;
                    }
                    break;
                default:
                    printf("Error:%s(),%d\n",__func__,__LINE__);
                    return FALSE;
                    break;
            }
        }
            break;

        default:
            UNUSED(u8SubCmd);
            UNUSED(u32Param1);
            UNUSED(u32Param2);
            UNUSED(pvoidParam3);
            return FALSE;
            break;
    }
    return TRUE;
}
#endif

