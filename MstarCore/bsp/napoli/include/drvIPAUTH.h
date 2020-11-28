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

#ifndef DLL_PUBLIC
#define DLL_PUBLIC __attribute__ ((visibility ("default"))) 
#endif

#ifndef DLL_LOCAL
#define DLL_LOCAL __attribute__ ((visibility ("hidden")))
#endif

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

#define IPAUTH_SHM_NAME    "Linux IPAUTH driver"
typedef struct
{
    MS_U32  g_ShmID;
    MS_U32  g_u32ClientCounter;
    MS_U8   g_IpControl[16];
}IPAUTH_SHARED_VARS;



extern MS_BOOL MApp_IPAUTH_GetLibVer(const MSIF_Version **ppVersion);
DLL_PUBLIC void MApi_AUTH_Process(MS_U8 *string, MS_U8 *hash);
DLL_PUBLIC MS_U8 MApi_AUTH_State(void);
DLL_PUBLIC MS_U8 MDrv_AUTH_IPCheck(MS_U8 u8Bit);
DLL_PUBLIC MS_BOOL MDrv_AUTH_InitialVars(void);
DLL_PUBLIC IPAUTH_SHARED_VARS * MDrv_AUTH_AllocateVars(void);
DLL_PUBLIC MS_BOOL MDrv_AUTH_ResetDefaultVars(IPAUTH_SHARED_VARS * pIPAUTHShared);
DLL_PUBLIC void MDrv_AUTH_GetHashInfo (MS_U8 *hashinfo);
#ifdef __cplusplus

}
#endif

#endif //_DRVIPAUTH_H_
