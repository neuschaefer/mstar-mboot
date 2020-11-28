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
/// file   drvMAD2.h
/// @author MStar Semiconductor Inc.
/// @brief   Audio common driver
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVMAD2_H_
#define _DRVMAD2_H_

#include "drvAUDIO_if.h"

#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
void MDrv_MAD2_SetMemInfo(void);
MS_BOOL MDrv_MAD2_ReLoadCode(MS_U8 u8Type);
void MDrv_MAD2_SetDecCmd(AU_DVB2_DECCMD u8DecCmd);
AU_DVB_DECCMD MDrv_MAD2_GetDecCmd(void);
void MDrv_MAD2_SetFreeRun(AU_DVB2_FreeRunMode u8Freerun);
void MDrv_MAD2_RebootDsp(void);
MS_U32  MDrv_MAD2_Read_DSP_sram(MS_U16 u16Dsp_addr,AUDIO_DSP_MEMORY_TYPE dsp_memory_type);
MS_BOOL MDrv_MAD2_Write_DSP_sram(MS_U16 u16Dsp_addr, MS_U32 u32Value, AUDIO_DSP_MEMORY_TYPE dsp_memory_type);

void MDrv_MAD2_DisEn_MIUREQ(void);
void MDrv_MAD2_DisMiuReq(void);
void MDrv_MAD2_RSTMAD_DisEn_MIUREQ(void);
MS_U16 MDrv_MAD2_XPCM2_CheckIntStatus(void);

void   MDrv_MAD2_XPCM_setParam (XPCM_TYPE audioType, MS_U8  channels, MS_U16 sampleRate,
                                MS_U8  bitsPerSample, MS_U16 blockSize, MS_U16 samplePerBlock);
#ifdef __cplusplus
}
#endif

#endif   //#ifndef _DRVMAD2_H_

