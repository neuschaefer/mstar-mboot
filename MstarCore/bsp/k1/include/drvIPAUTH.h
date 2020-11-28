////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (!¡±MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVIPAUTH_H_
#define _DRVIPAUTH_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include "MsTypes.h"
#include "MsCommon.h"

#define MSIF_IPAUTH_LIB_CODE               {'I','P','A','_'} //Lib code
#define MSIF_IPAUTH_LIBVER                 {'0','0'}      //LIB version
#define MSIF_IPAUTH_BUILDNUM               {'0','0' }    //Build Number
#define MSIF_IPAUTH_CHANGELIST             {'0','0','1','1','5','7','5','8'} //P4 ChangeList Number

#define IPAUTH_CONTROL_VIDEO_H264           27
#define IPAUTH_CONTROL_XC_DVBC              39

#define IPAUTH_VER                         /* Character String for DRV/API version             */  \
    MSIF_TAG,                              /* 'MSIF'                                           */  \
    MSIF_CLASS,                            /* '00:driver, 02:app, 03:mw                        */  \
    MSIF_CUS,                              /* 0x6666                                           */  \
    MSIF_MOD,                              /* 0x0001                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_IPAUTH_LIB_CODE,                  /* IP__                                             */  \
    MSIF_IPAUTH_LIBVER,                    /* 0.0 ~ Z.Z                                        */  \
    MSIF_IPAUTH_BUILDNUM,                  /* 00 ~ 99                                          */  \
    MSIF_IPAUTH_CHANGELIST,                /* CL#                                              */  \
    MSIF_OS

extern MS_BOOL MApp_IPAUTH_GetLibVer(const MSIF_Version **ppVersion);
void MApi_AUTH_Process(MS_U8 *string, MS_U8 *hash);
MS_U8 MApi_AUTH_State(void);
MS_U8 MDrv_AUTH_IPCheck(MS_U8 u8Bit);

#ifdef __cplusplus

}
#endif

#endif //_DRVIPAUTH_H_
