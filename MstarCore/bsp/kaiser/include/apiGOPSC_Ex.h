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
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   apiGOP_SC.h
/// @brief  MStar Graphics Output Path API
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _API_GOPSC_EX_H_
#define _API_GOPSC_EX_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define MSIF_GOPSC_EX_LIBVER              {'0','0'}            //LIB version
#define MSIF_GOPSC_EX_BUILDNUM            {'1','1'}            //Build Number
#define MSIF_GOPSC_EX_CHANGELIST          {'0','0','3','9','1','8','8','7'} //P4 ChangeList Number

typedef enum
{
    EN_Bilinear = 0,
    EN_Cubic
}EN_GOPSC_VScalingMode;

typedef struct
{
    MS_U16 srcWidth;
    MS_U16 srcHeight;
    MS_U16 destWidth;
    MS_U16 destHeight;
    MS_U8 bEnableScaleX;
    MS_U8 bEnableScaleY;
}GOPSC_SizeInfo;

typedef struct
{
    MS_U16 xStart;
    MS_U16 xEnd;
    MS_U16 yStart;
    MS_U16 yEnd;
    MS_U8 bEnableSkipX;
    MS_U8 bEnableSkipY;
}GOPSC_SkipPixelInfo;

typedef struct
{
    MS_U32 u32Version;
    MS_U32 u32Id;
}GOPSC_DeviceInfo;

typedef enum
{
    ///failed
    En_GOPSC_FAIL = 0,
    ///success
    En_GOPSC_OK,
    ///invalid parameter
    En_GOPSC_INVALID_PARAM,
    ///access not allow
    En_GOPSC_NotSupport,
}GOPSC_Result;

typedef enum
{
    None = 0x0,
    SetOutputRateControl = 0x1,
    EnableP2I = 0x2,
    HalfMode = 0x4,
}EN_GOPSCCmd;

typedef enum
{
    EN_Source_GOP,
    EN_Source_OP,
}EN_GOPSC_Source;

typedef struct
{
    EN_GOPSC_VScalingMode en_VScalingMode;
    EN_GOPSC_Source en_Source;
    MS_U16 dlyLineNumber; //(unit : 2-line)
    MS_BOOL P2IEnable;
    MS_BOOL HalfModeEnable; //output frame rate is half input frame rate
    MS_BOOL OutputRateControlEnable;
}GOPSC_Info;

GOPSC_Result MApi_GOPSC_Init(GOPSC_DeviceInfo* DevInfo);
GOPSC_Result MApi_GOPSC_Enable(GOPSC_DeviceInfo* DevInfo, MS_BOOL enable);
GOPSC_Result MApi_GOPSC_GetGOPSCInfo(GOPSC_DeviceInfo* DevInfo, GOPSC_Info* gopscInfo);
GOPSC_Result MApi_GOPSC_SetGOPSCInfo(GOPSC_DeviceInfo* DevInfo, GOPSC_Info* gopscInfo);
GOPSC_Result MApi_GOPSC_SetHVSPSize(GOPSC_DeviceInfo* DevInfo, const GOPSC_SizeInfo* sizeInfo, MS_U32 flag);
GOPSC_Result MApi_GOPSC_SetSkipPixel(GOPSC_DeviceInfo* DevInfo, const GOPSC_SkipPixelInfo* skippixelInfo, MS_U32 flag);
GOPSC_Result MApi_GOPSC_ScalingDownOnce(GOPSC_DeviceInfo* DevInfo, MS_U8 FrameNum);

//MS_BOOL MApi_GOPSC_SetCommand(EN_GOPSCCmd cmds);
//EN_GOPSCCmd MApi_GOPSC_GetCommand(void);

#ifdef __cplusplus
}
#endif

#endif
