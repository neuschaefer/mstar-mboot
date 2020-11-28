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

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   apiHDMITx.h
/// @brief  HDMITx Interface
/// @author MStar Semiconductor Inc.
///
///  CL351033++:
///   Add CEC function for STB
///  CL310477++:
///   Open analog setting for the different board condition
///  CL309397++:
///   Modify apiHDMITx prototype for NDS
///  CL308729++:
///   Fix AVMUTE problem while HDCP is on
///  CL299817++:
///  i. Add I2C timeout mechanism in EDID and HDCP
///  ii. Add SET_AVMUTE API to avoid transition garbage noise while timing changed ]]>
///  CL288415++:
///   Add SRM DSA Signature Checking function
///  CL283331++:
///   Fix HDMI v1.3 deep color mode output unstable problem
///  CL282607++:
///   i. Fix YUV422 / YUV444 bugs
///   ii. Add MApi_HDMITx_GetHdcpKey() to get HDCP key from external storage.
///  CL276751++:
///   Modify HDMI / HDCP state mechine for NDS
///  CL275230++:
///   i. MApi_HDMITx_GetRxDCInfoFromEDID() to get Rx's deep color information from EDID
///   ii. MApi_HDMITx_SetHDMITxMode_CD() to set output mode and deep color setting
///  CL266666++:
///   Add event report for NDS
///  CL263961++:
///   Add CEC init and checkbuffer for NDS
///  CL260934++:
///   Add some customized APIs for NDS
///  CL259645++:
///   i. Remove EDID header check. If header is wrong, force to DVI output
///   ii. Add force output mode "MApi_HDMITx_ForceHDMIOutputMode()"
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _API_HDMITX_H_
#define _API_HDMITX_H_

#include "MsTypes.h"
//#include "halHDMITx.h"
//#include "drvHDMITx.h"
//#include "regHDMITx.h"



#ifdef __cplusplus
extern "C"
{
#endif


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef enum
{
    HDMITX_RES_640x480p        =0,
    HDMITX_RES_720x480i         = 1,
    HDMITX_RES_720x576i         = 2,
    HDMITX_RES_720x480p         = 3,
    HDMITX_RES_720x576p         = 4,
    HDMITX_RES_1280x720p_50Hz   = 5,
    HDMITX_RES_1280x720p_60Hz   = 6,
    HDMITX_RES_1920x1080i_50Hz  = 7,
    HDMITX_RES_1920x1080i_60Hz  = 8,
    HDMITX_RES_1920x1080p_24Hz  = 9,
    HDMITX_RES_1920x1080p_25Hz  = 10,
    HDMITX_RES_1920x1080p_30Hz  = 11,
    HDMITX_RES_1920x1080p_50Hz  = 12,
    HDMITX_RES_1920x1080p_60Hz  = 13,
    HDMITX_RES_MAX              = 14,
} HDMITX_VIDEO_TIMING;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

//*********************//
//        DVI / HDMI           //
//*********************//

DLL_PUBLIC MS_BOOL MApi_HDMITx2_Init(void);

DLL_PUBLIC MS_BOOL MApi_HDMITx2_Exit(void);

DLL_PUBLIC void MApi_HDMITx2_SetInitTiming(HDMITX_VIDEO_TIMING TFlag1);

#ifdef __cplusplus
}
#endif


#endif // _API_HDMITX_H_

