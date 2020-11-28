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
/// @file drvSIF.h
/// @brief Subroutine for SIF
/// @author MStarSemi Inc.
////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVSIF_H_
#define _DRVSIF_H_

////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////
#include "MsTypes.h"
#include "drvAUDIO_if.h"

#ifdef __cplusplus
extern "C"
{
#endif
////////////////////////////////////////////////////////////////////////////////
// Define & data type
////////////////////////////////////////////////////////////////////////////////

//================================================================
//  Enum
//================================================================

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
void    MDrv_SIF_Init(void);
MS_BOOL MDrv_SIF_LoadCode(MS_U8 u8Type);
MS_BOOL MDrv_SIF_ReLoadCode(MS_U8 u8Type);

MS_BOOL MDrv_SIF_SetSoundMode(AUDIO_SIF_SOUND_MODE mode_type);
MS_BOOL MDrv_SIF_SetSystem(MS_U8 u8SystemType);
MS_BOOL MDrv_SIF_StartAutoDetection (void);
MS_U32 MDrv_SIF_AccessThreshold(AUDIO_SIF_SYSTEM_TYPE rw_standard_type, AUDIO_SIF_THRESHOLD_TYPE  u8Threshold_type, MS_U16 u16Value);
void    MDrv_SIF_SetThreshold(THR_TBL_TYPE code *ThrTbl, MS_U8 start_i, MS_U8 num, AUDIO_SIF_SYSTEM_TYPE standard_type);
MS_BOOL MDrv_SIF_GetOrginalGain(void);
MS_BOOL MDrv_SIF_SetPrescale(AUDIO_SIF_GAIN_TYPE u8Type,int db_value);

//////////////////////////////////////////////////////
// add for the Chakara2  & for the ¦n¥Í¬¡ coding
MS_BOOL MDrv_SIF_IsPALType(AUDIO_SIF_PAL_TYPE pal_type);
MS_BOOL MDrv_SIF_SetPALType(AUDIO_SIF_PAL_TYPE pal_type);
void  MDrv_SIF_SetStandardType(AUDIO_SIF_SET_STANDARD sif_type);
MS_U8 MDrv_SIF_GetDspType(void);
MS_U8 MDrv_SIF_GetDspCodeType(void);

MS_U8 MDrv_SIF_SendCmd(AU_SIF_CMD u8DecCmd, MS_U8 comm_arg1, MS_U8 comm_arg2);

#ifdef __cplusplus
}
#endif

#endif
