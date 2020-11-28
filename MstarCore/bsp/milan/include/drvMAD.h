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
MS_BOOL MDrv_AUDIO_MM2_initAesInfo( AUDIO_DEC_ID  dec_id );
MS_BOOL MDrv_AUDIO_MM2_checkAesInfo( AUDIO_DEC_ID  dec_id, AES_INFO *aes_info );
MS_BOOL MDrv_AUDIO_MM2_inputAesFinished( AUDIO_DEC_ID dec_id, MS_U32 es_size, MS_BOOL ptsExist, MS_U64 pts );


//=====================================================
// AUDIO_MAD Common decoder Relational Driver Function
//=====================================================
//Multi Player
MS_BOOL MDrv_MAD_DecoderCmd(AUDIO_DEC_ID DecId, AU_DVB_DECCMD u8DecCmd);
MS_BOOL MDrv_MAD_GetAudioCapability(AUDIO_DEC_ID eDecId, AudioDecStatus_t * p_AudioDecStatus);
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
MS_BOOL MDrv_AUDIO_GetAudioInfo2( AUDIO_DEC_ID DecId, Audio_InfoType infoType, void * pInfo );

//====== STAOS PIP END 2012/02/02 ========

#ifdef __cplusplus
}
#endif

#endif   //#ifndef _DRVMAD_H_

