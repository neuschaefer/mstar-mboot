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
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   apiMFE_v2.h
/// @brief  MFE Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _API_MFE_V2_H_
#define _API_MFE_V2_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "drv_mfe_st.h"

#include "MsTypes.h"
//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
// below for utopia20 structure

typedef enum {
    MApi_CMD_MFE_Init = 0x0,
    MApi_CMD_MFE_Encode,
    MApi_CMD_MFE_GetVOL,
    MApi_CMD_MFE_CompressOnePicture,
    MApi_CMD_MFE_DeInit,
    MApi_CMD_MFE_PowerOff,
    MApi_CMD_MFE_GetOutBuffer,
    MApi_CMD_MFE_SetBitrateFramerate,
    MApi_CMD_MFE_SetColorFormat,
    MApi_CMD_MFE_ResetSPSPPS,
    MApi_CMD_MFE_SetFrameType,
    MApi_CMD_MFE_SetISR,
    MApi_CMD_MFE_GetHWCap,
} E_MFE_V2_IOCTL_CMD;

typedef struct _MFE_INIT_PARAM
{
    PVR_Info* mfe_Info;
    MS_BOOL retVal;
}MFE_INIT_PARAM, *PMFE_INIT_PARAM;

typedef struct _MFE_SET_PARAM
{
    PVR_Info* mfe_Info;
    int frametype;
    MS_BOOL retVal;
}MFE_SET_PARAM, *PMFE_SET_PARAM;

typedef struct _MFE_GETVOL_PARAM
{
    PVR_Info* mfe_Info;
    void *header_info;
    MS_BOOL retVal;
}MFE_GETVOL_PARAM, *PMFE_GETVOL_PARAM;

typedef struct _MFE_COMPRESSONEPICTURE_PARAM
{
    PVR_Info* mfe_Info;
    MEMMAP_CUR_t YUVPlane;
    MS_BOOL bForceIframe;
    MS_BOOL retVal;
}MFE_COMPRESSONEPICTURE_PARAM, *PMFE_COMPRESSONEPICTURE_PARAM;

typedef struct _MFE_GET_OBUF_PARAM
{
    PVR_Info* mfe_Info;
    MEMMAP_t* outbuf;
    MS_BOOL retVal;
}MFE_GET_OBUF_PARAM, *PMFE_GET_OBUF_PARAM;

typedef struct _MFE_GET_HWCAP_PARAM
{
    PVR_Info* mfe_Info;
    MFE_HwCapV0 *pDrv;
    MS_U32 *HwCap_len;
    MS_BOOL retVal;
}MFE_GET_HWCAP_PARAM, *PMFE_GET_HWCAP_PARAM;

void MFERegisterToUtopia(FUtopiaOpen ModuleType);
MS_U32 MFE_Open(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
MS_U32 MFE_Close(void* pInstance);
MS_U32 MFE_Ioctl(void* pInstance, MS_U32 u32Cmd, void* pArgs);


#ifdef __cplusplus
}
#endif

#endif // _API_MFE_V2_H_


