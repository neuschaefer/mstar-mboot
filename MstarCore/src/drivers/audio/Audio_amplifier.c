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

#include <drvGPIO.h>
#include <config.h>
#include <common.h>
#include <MsTypes.h>

#include <apiSWI2C.h>
#include <audio/Audio_amplifier.h>

#define msAPI_Timer_Delayms(x) udelay(1000*x)

#if (CONFIG_DIGITAL_TI5707) //(DIGITAL_I2S_SELECT==AUDIO_I2S_TAS5707)
#include "DevTAS5707.c"
#elif (CONFIG_DIGITAL_STA333)//(DIGITAL_I2S_SELECT==AUDIO_I2S_STA333)
#include "DevI2S_STA333.c"
#elif (CONFIG_DIGITAL_TI5708) //(DIGITAL_I2S_SELECT==AUDIO_I2S_TAS5708)
#include "Amplifier_TI5708.c"
#elif (CONFIG_DIGITAL_TI5711)//(DIGITAL_I2S_SELECT==AUDIO_I2S_TAS5711)
#include "Amplifier_TI5711.c"
#elif (CONFIG_DIGITAL_TI5727_HISENSE)//(DIGITAL_I2S_SELECT==AUDIO_I2S_TAS5727_HISENSE)
#include "Amplifier_TI5727_hisense.c"
#endif


#if 0// move all this to msI2C.c
#define MIIC_BUS_SYS    PAD_DDCR_CK,    PAD_DDCR_DA,    SWI2C_SPEED_MAPPING_100K
#define MIIC_BUS_DDCA0  PAD_DDCA_CK,    PAD_DDCA_DA,    SWI2C_SPEED_MAPPING_100K
#define MIIC_BUS_DDCD0  PAD_DDCDA_CK,   PAD_DDCDA_DA,   SWI2C_SPEED_MAPPING_100K
#define MIIC_BUS_DDCD1  PAD_DDCDB_CK,   PAD_DDCDB_DA,   SWI2C_SPEED_MAPPING_100K
#define MIIC_BUS_DDCD2  PAD_DDCDC_CK,   PAD_DDCDC_DA,   SWI2C_SPEED_MAPPING_100K

#define __I2C_BUS(scl, sda, dly)    scl, sda, dly
#define I2C_BUS( bus )      __I2C_BUS( bus )

typedef struct
{
    MS_U16 padSCL;
    MS_U16 padSDA;
    MS_U16 defDelay;
} I2C_Bus;

static MS_U8 u8BusSel = 0;

SWI2C_BusCfg g_I2CBus[] =
{
    { I2C_BUS( MIIC_BUS_SYS   ) },
	{ I2C_BUS( MIIC_BUS_DDCA0 ) },
	{ I2C_BUS( MIIC_BUS_DDCD0 ) },
	{ I2C_BUS( MIIC_BUS_DDCD1 ) },
	{ I2C_BUS( MIIC_BUS_DDCD2 ) },
};
#endif
void drvAudio_AMP_Init(void)
{

#if (CONFIG_DIGITAL_TI5707)
    //MApi_SWI2C_Init(g_I2CBus,u8BusSel);
    drvTAS5707_SW_Init();
#elif (CONFIG_DIGITAL_STA333)
    //MApi_SWI2C_Init(g_I2CBus,u8BusSel);
    Audio_Amplifier_ON();
    msAPI_Timer_Delayms(20);
    Audio_Amplifier_OFF();
    msAPI_Timer_Delayms(100);
    DevI2s_STA333_Init();
#elif (CONFIG_DIGITAL_TI5708)
    //MApi_SWI2C_Init(g_I2CBus,u8BusSel);
    Amplifier_TI5708_Init();
    Amplifier_TI5708_VolumeForSource();
#elif (CONFIG_DIGITAL_TI5711)
   // MApi_SWI2C_Init(g_I2CBus,u8BusSel);
    Amplifier_TI5711_Init();
    Amplifier_TI5711_Mute(0);
    Amplifier_TI5711_SWMute(0);
#elif (CONFIG_DIGITAL_TI5727_HISENSE)
   // MApi_SWI2C_Init(g_I2CBus,u8BusSel);
    Amplifier_TI5727_hisense_Init();
    Amplifier_TI5727_hisense_Mute(0);
    Amplifier_TI5727_hisense_SWMute(0);
#endif
}
