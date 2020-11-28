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
/// @file   apiGOP.h
/// @brief  MStar Graphics Output Path API
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _GOPSCD_H_
#define _GOPSCD_H_



#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
/// GOPSCD Version

/// GOPSCD CMD
typedef enum
{
    //gop property
    MAPI_CMD_GOPSCD_INIT,
    MAPI_CMD_GOPSCD_SCALING,
    MAPI_CMD_GOPSCD_SET_INFO,
    MAPI_CMD_GOPSCD_GET_INFO,
    MAPI_CMD_GOPSCD_SET_HVSPSIZE,
    MAPI_CMD_GOPSCD_SET_SKIPPIXEL,
}E_GOPSCD_API_CMD_TYPE;

typedef enum
{
    E_GOPSCD_CMD_DISABLE       = 0x0,
    E_GOPSCD_CMD_ENABLE        = 0x1,
    E_GOPSCD_CMD_SCALING_ONCE  = 0x2,
}E_GOPSCD_SCALING_CMD;

typedef struct
{
	GOPSC_Result bReturnValue;
}GOPSCD_INIT_INFO, *PGOPSCD_INIT_INFO;

typedef struct
{
	E_GOPSCD_SCALING_CMD gopscCmd;
	GOPSC_Result bReturnValue;
	MS_U8 u8FrameCount;
}GOPSCD_SCALING, *PGOPSCD_SCALING;

typedef struct
{
	GOPSC_Info* gopscInfo;
	GOPSC_Result bReturnValue;
}GOPSCD_SET_INFO, *PGOPSCD_SET_INFO;

typedef struct
{
	GOPSC_Info* gopscInfo;
	GOPSC_Result bReturnValue;
}GOPSCD_GET_INFO, *PGOPSCD_GET_INFO;

typedef struct
{
	GOPSC_SizeInfo* sizeInfo;
	MS_U32 flag;
	GOPSC_Result bReturnValue;
}GOPSCD_SET_HVSPSZIE, *PGOPSCD_SET_HVSPSZIE;

typedef struct
{
	GOPSC_SkipPixelInfo* skippixelInfo;
	MS_U32 flag;
	GOPSC_Result bReturnValue;
}GOPSCD_SET_SKIPPIXEL, *PGOPSCD_SET_SKIPPIXEL;

#ifdef __cplusplus
}
#endif

#endif // _API_GOPSCD_H_

