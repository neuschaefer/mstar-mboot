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
////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVAUDSP_H_
#define _DRVAUDSP_H_

////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////
#include "MsTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif


////////////////////////////////////////////////////////////////////////////////
// Define & data type
////////////////////////////////////////////////////////////////////////////////
/// Version string.
#define MSIF_AUDSP_LIB_CODE                     {'A','D','S','P'}    //Lib code
#define MSIF_AUDSP_LIBVER                       {'0','0'}            //LIB version
#define MSIF_AUDSP_BUILDNUM                     {'3','F'}            //Build Number
#define MSIF_AUDSP_CHANGELIST                   {'0','0','0','0','0','0','0','0'} //P4 ChangeList Number

#define AUDSP_DRV_VERSION                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_AUDSP_LIB_CODE,                        /* IP__                                             */  \
    MSIF_AUDSP_LIBVER,                          /* 0.0 ~ Z.Z                                        */  \
    MSIF_AUDSP_BUILDNUM,                        /* 00 ~ 99                                          */  \
    MSIF_AUDSP_CHANGELIST,                      /* CL#                                              */  \
    MSIF_OS

//================================================================
//  AUDSP version informtion functions
//================================================================
extern MS_BOOL MDrv_AUD_GetLibVer(const MSIF_Version **ppVersion);

//================================================================
//  AUDSP Load Code functions
//================================================================
MS_BOOL MDrv_AUDSP_DspLoadCode(MS_U8 u8Type);
void MDrv_AUDSP_SetDspLoadCodeInfo(AUDIO_ALG_INFO *pau_info, MS_U8 DSP_select);
LOAD_CODE_INFO* MDrv_AUDSP_GetDspLoadCodeInfo(void);

#ifdef __cplusplus
}
#endif

#endif
