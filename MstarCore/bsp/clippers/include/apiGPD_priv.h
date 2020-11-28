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
////////////////////////////////////////////////////////////////////////////////

#ifndef _APIGPD_PRIV_H_
#define _APIGPD_PRIV_H_

////////////////////////////////////////////////////////////////////////////////
/// @file apiGPD.h
/// @author MStar Semiconductor Inc.
/// @brief GPD control driver
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"
#include "apiGPD.h"

#define SUPPORT_GPD_NUM_MAX     1

typedef void* (*IOCTL_GPD_INIT)(U32);
typedef S32 (*IOCTL_GPD_INPUT_SOURCE)(gpd_pic_info*, U32, U32);
typedef S32 (*IOCTL_GPD_OUTPUT_DECODE)(U32, U32, U32);
typedef S32 (*IOCTL_GPD_OUTPUT_DECODE_ROI)(U32, U32, U32, gpd_roi_info*);
typedef S32 (*IOCTL_GPD_OUTPUT_DECODE_MGIF)(U32, U32, U32);
typedef S32 (*IOCTL_GPD_GET_DURATION)(void);
typedef void (*IOCTL_GPD_SET_GIF_MODE)(int);
typedef void (*IOCTL_GPD_SCALING_ENABLE)(U32);
typedef void (*IOCTL_GPD_SCALING_DISABLE)(void);
typedef U32 (*IOCTL_GPD_SET_CONTROL)(gpd_user_cmd, U32);
typedef U32 (*IOCTL_GPD_GET_CONTROL)(gpd_get_cmd, U32*);
typedef U32 (*IOCTL_GPD_GET_CRC_RESULT)(const MS_U8 *, MS_U32);


typedef struct _GPD_RESOURCE_PRIVATE
{
    MS_U8 u8DecoderInUse[SUPPORT_GPD_NUM_MAX];
}GPD_RESOURCE_PRIVATE;

typedef struct _GPD_INSTANCE_PRIVATE
{
    void* pResource;
    // instance variable
    MS_U8                                       Index_of_decoder;

    IOCTL_GPD_INIT                              fpGPDInit;
    IOCTL_GPD_INPUT_SOURCE                      fpGPDInputSource;
    IOCTL_GPD_OUTPUT_DECODE                     fpGPDOutputDecode;
    IOCTL_GPD_OUTPUT_DECODE_ROI                 fpGPDOutputDecodeROI;
    IOCTL_GPD_OUTPUT_DECODE_MGIF                fpGPDOutputDecodeMGIF;
    IOCTL_GPD_GET_DURATION                      fpGPDGetDuration;
    IOCTL_GPD_SET_GIF_MODE                      fpGPDSetGIFMode;
    IOCTL_GPD_SCALING_ENABLE                    fpGPDScalingEnable;
    IOCTL_GPD_SCALING_DISABLE                   fpGPDScalingDisable;
    IOCTL_GPD_SET_CONTROL                       fpGPDSetControl;
    IOCTL_GPD_GET_CONTROL                       fpGPDGetControl;
    IOCTL_GPD_GET_CRC_RESULT                    fpGPDGetCRCResult;

}GPD_INSTANCE_PRIVATE;

void GPDRegisterToUtopia(FUtopiaOpen ModuleType);
MS_U32 GPDOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
MS_U32 GPDClose(void* pInstance);
MS_U32 GPDIoctl(void* pInstance, MS_U32 u32Cmd, void* pArgs);


void *_MApi_GPD_Init(U32 SrcBuf);
S32 _MApi_GPD_InputSource(gpd_pic_info* param, U32 InputBuf, U32 Size);
S32 _MApi_GPD_OutputDecode(U32 DecodeBuf, U32 ocolor, U32 Size);
S32 _MApi_GPD_OutputDecodeROI(U32 DecodeBuf, U32 ocolor, U32 Size, gpd_roi_info *roi);
S32 _MApi_GPD_OutputDecodeMGIF(U32 DecodeBuf, U32 ocolor, U32 Size);
S32 _MApi_GPD_GetDuration(void);
void _MApi_GPD_SetGIFMode(int mode);

void _MApi_GPD_ScalingEnable(U32 mode);
void _MApi_GPD_ScalingDisable(void);
U32 _MApi_GPD_SetControl(gpd_user_cmd cmd_id, U32 param);
U32 _MApi_GPD_GetControl(gpd_get_cmd cmd_id, U32* param);
U32 _MApi_GPD_GetCRCResult(const MS_U8 *pu8Data, MS_U32 u32Size, MS_U32, unsigned int);

#ifdef __cplusplus
}
#endif
#endif // _APIGPD_PRIV_H_





