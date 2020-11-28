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

MS_BOOL MDrv_SOUND_SetParam( Sound_SET_Type Type, MS_U32 *p_param );

MS_BOOL MDrv_SND_ProcessEnable(Sound_ENABLE_Type Type, MS_BOOL enable);
MS_BOOL MDrv_SND_SetParam( Sound_SET_PARAM_Type Type, MS_U16 param1, MS_U16 param2);
MS_U16  MDrv_SND_GetParam( Sound_GET_PARAM_Type Type, MS_U16 param1);

#ifdef __cplusplus
}
#endif


#endif //_DRVSOUND_H_
