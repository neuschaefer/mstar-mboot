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
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse bEngineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
//  [Doxygen]
/// @file drvSOUND.h
/// @brief Subroutine for sound effect
/// @author MStarSemi Inc.
////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVSOUND_H_
#define _DRVSOUND_H_

#include "MsTypes.h"
#include "drvAUDIO_if.h"

#ifdef __cplusplus
extern "C"
{
#endif


enum
{
    SUBWOOFER=0x00,
    VOLUME_BALANCE=0x01,
    SPATIAL=0x02,
    u8BaSS_TREBLE=0x03,
    AUTO_VOLUME=0x04,
    DAC_OUTPUT=0x05,
    SOUND_EFFECT=0x06,
    STEREO_MODE=0x07,
    SOUND_MODE=0x08
};

//=====================================================
// Declare audio function here.
//=====================================================
void    MDrv_SOUND_Init(void);
void    MDrv_SOUND_SetMute(MS_U8 u8Path, MS_BOOL bEnable);
void    MDrv_SOUND_AbsoluteVolume(MS_U8 u8Path, MS_U8 u8Vol1, MS_U8 u8Vol2);
void    MDrv_SOUND_SetPreScale(MS_U8 u8Path, MS_U8 u8Prescale);
void    MDrv_SOUND_SetBalance(MS_U8 u8Balance);
void    MDrv_SOUND_SetBalance_L(MS_U8 u8Balance_L);
void    MDrv_SOUND_SetBalance_R(MS_U8 u8Balance_R);
void    MDrv_SOUND_SetBass(MS_U8 u8Level);
void    MDrv_SOUND_SetDynamicBass(MS_U8 u8Level);
void    MDrv_SOUND_AbsoluteBass(MS_U8 u8Bass);
void    MDrv_SOUND_SetTreble(MS_U8 u8Level);
void    MDrv_SOUND_AbsoluteTreble(MS_U8 u8Treble);
void    MDrv_SOUND_SetEq(MS_U8 u8Band, MS_U8 u8Level);
void    MDrv_SOUND_SetEq7(MS_U8 u8Band, MS_U8 u8Level);

void    MDrv_SOUND_SetADCThreshold(MS_U8 u8Threshold);
void    MDrv_SOUND_SetNRAttenuate(MS_U8 u8Mode);
void    MDrv_SOUND_SetAVCThreshold(MS_U8 u8Level);
void    MDrv_SOUND_SetAvcMode( MS_U8 u8AvcMode );
void    MDrv_SOUND_SetAvcAT( MS_U8 u8AvcAT );
void    MDrv_SOUND_SetAvcRT( MS_U8 u8AvcRT );
void    MDrv_SOUND_PowerDown_Wait(MS_BOOL bEnable);
void    MDrv_SOUND_SetCH1AudioDelay(MS_U8 u8Delay);
void    MDrv_SOUND_PlayMenuSound(void);
void    MDrv_SOUND_SetSurroundXA(MS_U8 u8Mode);
void    MDrv_SOUND_SetSurroundXB(MS_U8 u8Mode);
void    MDrv_SOUND_SetSurroundXK(MS_U8 u8Mode);
void    MDrv_SOUND_SetSurroundLPFGain(MS_U8 u8Mode);

//======================================================
void    MDrv_SOUND_EnableAutoVolume(MS_BOOL bEnAVC);
void    MDrv_SOUND_EnableTone(MS_BOOL bEnTone);
void    MDrv_SOUND_EnableEQ(MS_BOOL bEnEQ);
void    MDrv_SOUND_EnableSurround(MS_BOOL bEnSurround);
void    MDrv_SOUND_EnableNR(MS_U8 u8Level);
void    MDrv_SOUND_EnableBalance(MS_U8 u8Enable);
//================From DrvAudioProcess=======================
void    MDrv_SOUND_SetAdAbsoluteVolume(MS_U8 u8Vol1, MS_U8 u8Vol2);
void    MDrv_SOUND_SetAdMute(MS_BOOL bEnable);
void    MDrv_SOUND_SetPEQCoef(AUDIO_PEQ_COEF *peq_coef);
void    MDrv_SOUND_EnablePEQ(MS_BOOL Enpeq);

void    MDrv_SOUND_SetMixModeMute(AUDIO_SOURCE_INFO_TYPE eSourceType, AUDIO_MIX_VOL_TYPE VolType, MS_BOOL EnMute );
void    MDrv_SOUND_SetMixModeVolume(AUDIO_SOURCE_INFO_TYPE eSourceType, AUDIO_MIX_VOL_TYPE VolType, MS_U8 u8Vol1, MS_U8 u8Vol2  );

MS_BOOL MDrv_SOUND_EnableDcRemove(MS_BOOL EnDcRemove);
MS_BOOL MDrv_SOUND_SetParam( Sound_SET_Type Type, MS_U32 *p_param );

MS_BOOL MDrv_SND_ProcessEnable(Sound_ENABLE_Type Type, MS_BOOL enable);
MS_BOOL MDrv_SND_SetParam( Sound_SET_PARAM_Type Type, MS_U16 param1, MS_U16 param2);
MS_U16  MDrv_SND_GetParam( Sound_GET_PARAM_Type Type, MS_U16 param1);

#ifdef __cplusplus
}
#endif


#endif //_DRVSOUND_H_
