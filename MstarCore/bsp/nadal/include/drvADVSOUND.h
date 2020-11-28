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
//  [for Doxygen]
/// @file drvADVSOUND.h
/// @brief Subroutine for advance sound effect
/// @author MStarSemi Inc.
////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVADVSOUND_H_
#define _DRVADVSOUND_H_

#include "MsTypes.h"
#include "drvAUDIO_if.h"


#ifdef __cplusplus
extern "C"
{
#endif

//=====================================================
// Declare audio function here.
//=====================================================
void  MDrv_SOUND_AseSetBinAddress(MS_U8 u8Index, MS_U32 BinAddr);
//void  MDrv_SOUND_ReLoadAseCode(MS_U8 u8Type);
void  MDrv_SOUND_VDS_Enable(MS_U8 u8enVDS);
void  MDrv_SOUND_VSPK_Enable(MS_U8 u8enVSPK);
void  MDrv_SOUND_SRS_SetTsxtPara(MS_U8 u8mode, MS_U8 u8value);
void  MDrv_SOUND_SRS_SetTshdPara(MS_U8 u8mode, MS_U8 u8value);
void  MDrv_SOUND_SRS_Enable(MS_U8 u8enSRS);
void  MDrv_SOUND_TSHD_Enable(MS_U8 u8enSRS);
void  MDrv_SOUND_VSPK_SetWMod(MS_U8 u8VSPK_WMode);
void  MDrv_SOUND_VSPK_SetSMod(MS_U8 u8VSPK_SMode);
void  MDrv_SOUND_BBE_SetBbeMode(MS_U8 u8EnBBE, MS_U8 u8BBEMode);
void  MDrv_SOUND_SetPara(MS_U8 u8Addr1 , MS_U8 u8Addr2, MS_U8 u8Value1, MS_U8 u8Value2, MS_U8 u8Value3);
void  MDrv_SOUND_SRS_DC(MS_U8 u8SRSenDC);
void  MDrv_SOUND_SRS_TruBass(MS_U8 u8SRSenTruBass);
void  MDrv_SOUND_TSHD_TruBass(MS_U8 u8TSHDenTruBass);
void  MDrv_SOUND_TSHD_Definition(MS_U8 u8TSHDenDefinition);
void  MDrv_SOUND_TSHD_Clarity(MS_U8 u8TSHDenClarity);
void  MDrv_SOUND_TSHD_TruSurr(MS_U8 u8TSHDenTruSurr);
void  MDrv_SOUND_TSHD_Limiter(MS_U8 u8TSHDenLimiter);
void  MDrv_SOUND_TSHD_SRS3D(MS_U8 u8TSHDenSRS3D);
void  MDrv_SOUND_TruVolume_Enable(MS_U8 u8TSHDenTVol);
void  MDrv_SOUND_CV2_Enable(MS_U8 u8enCV2);
void  MDrv_SOUND_CV2_SetPara(MS_U8 u8Addr1, MS_U8 u8Addr2, MS_U32 u32Value);
void  MDrv_SOUND_CV_SetPara(MS_U8 level, MS_U32 *p_cv_info);
void  MDrv_SOUND_AV_SetPara(MS_U32 *p_av_info);
void  MDrv_SOUND_SetEQPara(MS_U32 *p_eq_info);
void  MDrv_SOUND_CV_SetLevel(MS_U8 level);
void  MDrv_SOUND_ADSY_SetPara(MS_U8 u8mode, MS_U8 u8value);
MS_BOOL MDrv_ADVSOUND_ProcessEnable(ADVSND_TYPE type);
MS_BOOL MDrv_ADVSOUND_SubProcessEnable(ADVFUNC proc, MS_BOOL enable);
MS_BOOL MDrv_ADVSOUND_SetParam(ADVSND_PARAM param, MS_U16 u16value1, MS_U16 u16value2);
void  MDrv_AUDIO_COPY_Parameter(ADVSND_PARAM type, MS_U32 *Parameter_ptr,MS_U32 size);
void MDrv_DBXTV_SetMode(EN_DBXTV_TotSonMode totsonmode, EN_DBXTV_TotVolMode totvolmode, EN_DBXTV_TotSurMode totsurmode,MS_U32 enable);
#ifdef __cplusplus
}
#endif
#endif //_DRVADVSOUND_H_
