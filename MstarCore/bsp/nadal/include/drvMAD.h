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
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
//  [for Doxygen]
/// file drvMAD.h
/// @brief Subroutine for DVB
/// @author MStarSemi Inc.
////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVMAD_H_
#define _DRVMAD_H_

////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////
#include "drvAUDIO_if.h"



#ifdef __cplusplus
extern "C"
{
#endif

////////////////////////////////////////////////////////////////////////////////
// Define & data type
////////////////////////////////////////////////////////////////////////////////

#define IS_MADGOOD() ( MDrv_MAD_Rpt_DTVES() == 0x41 || MDrv_MAD_Rpt_DTVES() == 0x81 )

//=====================================================
// AUDIO_MAD System Relational Driver Function
//=====================================================
//MS_U32  MDrv_MAD_Read_DSP_sram(MS_U16 dsp_addr,AUDIO_DSP_MEMORY_TYPE dsp_memory_type);
//MS_BOOL MDrv_MAD_Write_DSP_sram(MS_U16 dsp_addr, MS_U32 value, AUDIO_DSP_MEMORY_TYPE dsp_memory_type);
void    MDrv_MAD_Init(void);
void    MDrv_MAD_SetMemInfo(void);
void    MDrv_MAD_DisEn_MIUREQ(void);
void    MDrv_MAD_Dis_MIUREQ(void);
MS_BOOL MDrv_MAD_LoadCode(AUDIO_DSP_CODE_TYPE u8Type);
MS_BOOL MDrv_MAD_ReLoadCode(AUDIO_DSP_CODE_TYPE u8Type1);
void    MDrv_MAD_SetAdMixMode(AD_MIX_MODE mix_mode, MIX_ONOFF en_mix);

void    MDrv_AUD_Monitor_SPDIF_NONPCM_SmpRate(void);
MS_BOOL MDrv_AUDIO_SetCertMode( Audio_CertMode CertType, Audio_CertEnable enCert );

//=====================================================
// AUDIO_MAD Common decoder Relational Driver Function
//=====================================================
MS_BOOL MDrv_AUDIO_SetCommAudioInfo( Audio_COMM_infoType infoType, MS_U32 param1, MS_U32 param2 );
long long MDrv_AUDIO_GetCommAudioInfo( Audio_COMM_infoType infoType );

void    MDrv_MAD_SetDecCmd(AU_DVB_DECCMD decCmd);
AU_DVB_DECCMD   MDrv_MAD_GetDecCmd(void);

MS_U8   MDrv_MAD_Rpt_DTVES(void);
//=====================================================
// AUDIO_MAD MEPG Relational Driver Function
//=====================================================
MS_BOOL MDrv_AUDIO_SetMpegInfo( Audio_MPEG_infoType infoType, MS_U32 param1, MS_U32 param2 );
MS_U32  MDrv_AUDIO_GetMpegInfo( Audio_MPEG_infoType infoType );

//=====================================================
// AUDIO_MAD Dolby Relational Driver Function
//=====================================================
MS_BOOL MDrv_AUDIO_SetAC3Info( Audio_AC3_infoType infoType, MS_U32 param1, MS_U32 param2 );
MS_BOOL MDrv_AUDIO_SetAC3PInfo( Audio_AC3P_infoType infoType, MS_U32 param1, MS_U32 param2 );
MS_U32  MDrv_AUDIO_GetAC3Info( Audio_AC3_infoType infoType );
MS_U32  MDrv_AUDIO_GetAC3PInfo( Audio_AC3P_infoType infoType );

//=====================================================
// AUDIO_MAD DTS Relational Driver Function
//=====================================================
MS_BOOL MDrv_AUDIO_SetDTSCommonCtrl( Audio_DTS_infoType infoType, Audio_DTS_CtrlType ctrl_type );
MS_U32  MDrv_AUDIO_GetDTSInfo( Audio_DTS_infoType infoType );

//=====================================================
// AUDIO_MAD WMA Relational Hal Function
//=====================================================
MS_BOOL MDrv_AUDIO_SetWmaInfo( Audio_WMA_infoType infoType, MS_U32 param1, MS_U32 param2 );
MS_U32  MDrv_AUDIO_GetWmaInfo( Audio_WMA_infoType infoType );

//=====================================================
// AUDIO_MAD LPCM/XPCM Relational Driver Function
//=====================================================
MS_U8   MDrv_MAD_XPCM_setParam( XPCM_TYPE audioType, MS_U8  channels, MS_U16 sampleRate,
                                MS_U8  bitsPerSample, MS_U16 blockSize, MS_U16 samplePerBlock);

//=====================================================
// AUDIO_MAD RA Relational Driver Function
//=====================================================
MS_U8   MDrv_MAD_RA8_setParam(MS_U16 mNumCodecs, MS_U16 mSamples, MS_U16 mSampleRate,
                                MS_U16* Channels, MS_U16* Regions, MS_U16* cplStart, MS_U16* cplQbits,
                                MS_U16* FrameSize);

//=====================================================
// AUDIO_MAD MPEG Encoder Related Driver Function
//=====================================================
void    MDrv_MAD_SetEncCmd(AU_DVB_ENCCMD u8EncCmd);
void    MDrv_AUDIO_SetEncodeInit(AU_DVB_ENCBR u8EncBitrate, MS_U8 u8EncFrameNum);
void    MDrv_AUDIO_GetEncodeFrameInfo(AU_DVB_ENC_FRAME_INFO *FrameInfo);

//=====================================================
// AUDIO_MAD AAC Relational Driver Function
//=====================================================
MS_U32  MDrv_AUDIO_GetAACInfo( Audio_AAC_infoType infoType );
MS_U32  MDrv_AUDIO_SetAACInfo( Audio_AAC_infoType infoType, MS_U32 param1, MS_U32 param2 );

//====== STAOS PIP START 2012/02/02 ========

MS_BOOL MDrv_AUDIO_SetAudioParam2( AUDIO_DEC_ID DecId, Audio_ParamType paramType, MS_U32 Param );
MS_BOOL MDrv_AUDIO_GetAudioInfo2( AUDIO_DEC_ID DecId, Audio_InfoType infoType, void * pInfo );

//====== STAOS PIP END 2012/02/02 ========

#ifdef __cplusplus
}
#endif

#endif   //#ifndef _DRVMAD_H_

