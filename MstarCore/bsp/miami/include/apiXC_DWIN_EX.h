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
//==============================================================================
// [apiXC_DWIN_EX.h]
// Date: 20120221
// Descriptions: structure pool
//==============================================================================
#ifndef APIXC_DWIN_EX_H
#define APIXC_DWIN_EX_H

// Common Definition
#include "MsCommon.h"

// Api
#include "apiXC_EX.h"

#ifdef __cplusplus
extern "C"
{
#endif

//#include "mvideo_context_ex.h"
//==============================================================================
//==============================================================================
#ifdef APIXC_DWIN_EX_C//MVIDEO_CONTEXT_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define XC_DIP_EX_MAX_BUFF_CNT 8
#define XC_DIP_EX_AUTO_BUFF_CNT 0
/// Define window type for DIP
typedef enum
{
    E_XC_DIP_EX_DIP_WINDOW = 0,         ///< DIP window
    E_XC_DIP_EX_MAX_WINDOW          /// The max support window
} XC_DIP_EX_WIN;

typedef enum
{
    E_XC_DIP_EX_RGB_SWAPTO_BGR = 0,         ///< RGB Swap to BGR
    E_XC_DIP_EX_RGB_SWAP_MAX                ///< The max support format
} XC_DIP_EX_RGB_SWAP_TYPE;

/// DIP source data format
typedef enum
{
    /// CrYCb domain.
    E_XC_DIP_EX_DATA_FMT_YUV422 = 0,
    /// CrYCb domain.
    E_XC_DIP_EX_DATA_FMT_RGB565,
    /// RGB domain (CSC bypass).
    E_XC_DIP_EX_DATA_FMT_ARGB8888,
    /// YUV420
    E_XC_DIP_EX_DATA_FMT_YUV420,
    E_XC_DIP_EX_DATA_FMT_MAX
} XC_DIP_EX_DATA_FMT;

/// DIP scan mode
typedef enum
{
    /// progessive.
    E_XC_DIP_EX_SCAN_MODE_PROGRESSIVE,
    /// interlace.
    E_XC_DIP_EX_SCAN_MODE_extern,
} XC_DIP_EX_SCAN_MODE;

typedef enum
{
	E_XC_DIP_EX_CAP_NOT_EXIST = 0x0,
	E_XC_DIP_EX_CAP_EXIST = 	0x1,
	E_XC_DIP_EX_CAP_420TILE = 	0x2,
	E_XC_DIP_EX_CAP_SCALING_DOWN = 	0x4,
	E_XC_DIP_EX_CAP_MIRROR = 	0x8,
	E_XC_DIP_EX_CAP_DIPR 	= 	0x10,
	E_XC_DIP_EX_CAP_R2Y 	= 	0x20,
    E_XC_DIP_EX_CAP_OP1_CAPTURE  =   0x40,
} XC_DIP_EX_CAP;

typedef enum
{
    E_XC_DIP_EX_VOP2   =0x00,
    E_XC_DIP_EX_OP2    =0x01,
    E_XC_DIP_EX_VIP    =0x02,
    E_XC_DIP_EX_BRI    =0x03,
} XC_DIP_EX_OP_CAPTURE;

typedef struct
{
    MS_U8               u8BufCnt;
    MS_U32              u32YBuf[XC_DIP_EX_MAX_BUFF_CNT];
    MS_U32              u32CBuf[XC_DIP_EX_MAX_BUFF_CNT];
} XC_DIP_EX_BUFFER_INFO;

typedef struct
{
    XC_DIP_EX_WIN      eWindow;
    MS_U32              u32DipChipCaps;
} XC_DIP_EX_CHIPCAPS;

typedef struct
{
    MS_U8  u8BufCnt;
    MS_U16 u16Width;
    MS_U16 u16Height;
	MS_U16 u16Pitch;
    MS_U32 u32BufStart;
    MS_U32 u32BufEnd;
    XC_DIP_EX_SOURCE_TYPE enSource;
} XC_DIP_EX_WINPROPERTY;

typedef struct
{
    MS_U16 u16Width;
    MS_U16 u16Height;
	MS_U16 u16Pitch;
    MS_U32 u32YBufAddr;
    MS_U32 u32CBufAddr;
    XC_DIP_EX_DATA_FMT enDataFmt;
}XC_DIP_EX_DIPR_PROPERTY;

XC_EX_RETURN_VALUE MApi_XC_DIP_EX_InitByDIP(XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_SetFrameBufferAddress(MS_PHYADDR u32FBAddress, MS_PHYADDR u32FBSize, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_SetInputSource(XC_EX_INPUT_SOURCE_TYPE enInputSourceType, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_GetInputSource(XC_EX_INPUT_SOURCE_TYPE *enInputSourceType, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_DisableInputSource(MS_BOOL bDisable, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_SetWindow(XC_EX_SETWIN_INFO *pstXC_SetWin_Info, MS_U32 u32InitDataLen, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_GetDEWindow(XC_EX_WINDOW_TYPE *psWin, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_SetCaptureWindowVstart(MS_U16 u16Vstart, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_SetCaptureWindowHstart(MS_U16 u16Hstart, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_SetCaptureWindowVsize(MS_U16 u16Vsize, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_SetCaptureWindowHsize(MS_U16 u16Hsize, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_GetCaptureWindow(XC_EX_WINDOW_TYPE* capture_win, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_EnableR2Y(MS_BOOL benable, XC_DIP_EX_WIN eWindow);

//==============Set===================
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_SWReset(XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_FrameRateCtrl(MS_BOOL bEnable,MS_U16 u16In,MS_U16 u16Out, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_CapOneFrame(XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_CapOneFrameFast(XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_SetPinpon(MS_BOOL bPinpon,MS_U32 u32PinponAddr,XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_ClearInt(MS_U16 u8mask, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_Ena(MS_BOOL bEnable, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_EnaInt(MS_U16 u8mask, MS_BOOL bEnable, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_SetSourceScanType(XC_DIP_EX_SCAN_MODE enScanMode, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_EnaInterlaceWrite(MS_BOOL bEnable, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_SetOutputDataFmt(XC_DIP_EX_DATA_FMT fmt, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_SetDIPWinProperty(XC_DIP_EX_WINPROPERTY *pstDIPWinProperty, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_EnableY2R(MS_BOOL bEnable, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_SetAlpha(MS_U8 u8AlphaVal, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_SwapUV(MS_BOOL bEnable, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_SwapYC(MS_BOOL bEnable, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_SwapRGB(MS_BOOL bEnable, XC_DIP_EX_RGB_SWAP_TYPE enSwapType, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_SetWinProperty_Ex(MS_U8 u8BufCnt ,MS_U16 u16Width, MS_U16 u16Height, MS_U32 u32BufStart ,MS_U32 u32BufEnd, XC_DIP_EX_SOURCE_TYPE eSource,XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_SetOutputCapture(MS_BOOL bEnable, XC_DIP_EX_OP_CAPTURE eOpCapture, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_SetMirror(MS_BOOL bHMirror, MS_BOOL bVMirror, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_SetDIPRProperty(XC_DIP_EX_DIPR_PROPERTY *pstDIPRProperty, XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_InterruptAttach(InterruptCb pIntCb,XC_DIP_EX_WIN eWindow);
XC_EX_RETURN_VALUE MApi_XC_DIP_EX_InterruptDetach(XC_DIP_EX_WIN eWindow);
//==============Get===================
MS_U16 MApi_XC_DIP_EX_GetIntStatus(XC_DIP_EX_WIN eWindow);
XC_DIP_EX_BUFFER_INFO MApi_XC_DIP_EX_GetBufInfo(XC_DIP_EX_WIN eWindow);
#ifdef __cplusplus
}
#endif
#endif /* APIXC_DWIN_H */

