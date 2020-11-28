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
// [apiXC_DWIN.h]
// Date: 20120221
// Descriptions: structure pool
//==============================================================================
#ifndef APIXC_DWIN_H
#define APIXC_DWIN_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "MsCommon.h"
//#include "mvideo_context.h"
//==============================================================================
//==============================================================================
#define MAX_BUFF_CNT 8
#define AUTO_BUFF_CNT 0
/// Define window type for DIP
typedef enum
{
    DIP_WINDOW = 0,         ///< DIP window
    DWIN0_WINDOW = 1,
    DWIN1_WINDOW = 2,
    MAX_DIP_WINDOW          /// The max support window
}SCALER_DIP_WIN;

typedef enum
{
    E_XC_DIP_RGB_SWAPTO_BGR = 0,         ///< RGB Swap to BGR
    E_XC_DIP_RGB_SWAP_MAX                ///< The max support format
}EN_XC_DIP_RGB_SWAP_TYPE;

/// DIP source data format
typedef enum
{
    /// YCrYCb.
    DIP_DATA_FMT_YUV422 = 0,
    /// RGB domain
    DIP_DATA_FMT_RGB565,
    /// RGB domain
    DIP_DATA_FMT_ARGB8888,
    /// YUV420
    DIP_DATA_FMT_YUV420,
    /// YC separate 422
    DIP_DATA_FMT_YC422,
    /// YUV420_H265
    DIP_DATA_FMT_YUV420_H265,
    /// YUV420_H265_10bits
    DIP_DATA_FMT_YUV420_H265_10BITS,
    DIP_DATA_FMT_MAX
} EN_XC_DIP_DATA_FMT;

/// DIP scan mode
typedef enum
{
    /// progessive.
    DIP_SCAN_MODE_PROGRESSIVE,
    /// interlace.
    DIP_SCAN_MODE_extern,
} EN_XC_DIP_SCAN_MODE;

typedef enum
{
    DIP_CAP_NOT_EXIST = 0x0,
    DIP_CAP_EXIST =     0x1,
    DIP_CAP_420TILE =   0x2,
    DIP_CAP_SCALING_DOWN =   0x4,
    DIP_CAP_MIRROR =    0x8,
    DIP_CAP_DIPR    =   0x10,
    DIP_CAP_R2Y     =   0x20,
    DIP_CAP_OP1_CAPTURE  =   0x40,
    //not support OP1 capture when traveling main source with PIP mode
    DIP_CAP_OP1_CAPTURE_V1 = 0x40,
    //support OP1 capture in all case
    DIP_CAP_OP1_CAPTURE_V2 = 0x80,
}EN_XC_DIP_CAP;

typedef enum
{
    E_XC_DIP_VOP2   =0x00,
    E_XC_DIP_OP2    =0x01,
    E_XC_DIP_VIP    =0x02,
    E_XC_DIP_BRI    =0x03,    
    E_XC_DIP_NONE   ,
}EN_XC_DIP_OP_CAPTURE;

typedef enum
{
    E_XC_DIP_ROTATION_270   =0x00,
    E_XC_DIP_ROTATION_90    =0x01,
}EN_XC_DIP_ROTATION;

typedef struct
{
    MS_U8               u8BufCnt;
    MS_U32              u32YBuf[MAX_BUFF_CNT];
    MS_U32              u32CBuf[MAX_BUFF_CNT];
} BUFFER_INFO;

typedef struct
{
    SCALER_DIP_WIN      eWindow;
    MS_U32              u32DipChipCaps;
} ST_XC_DIP_CHIPCAPS;

typedef struct
{
    MS_U8  u8BufCnt;
    MS_U16 u16Width;
    MS_U16 u16Height;
    MS_U16 u16Pitch;
    MS_U32 u32BufStart;
    MS_U32 u32BufEnd;
    SCALER_DIP_SOURCE_TYPE enSource;
}ST_XC_DIP_WINPROPERTY;

typedef struct
{
    MS_U16 u16Width;
    MS_U16 u16Height;
    MS_U16 u16Pitch;
    MS_U32 u32YBufAddr;
    MS_U32 u32CBufAddr;
    EN_XC_DIP_DATA_FMT enDataFmt;
    MS_U32 u32YBufAddr10Bits;
    MS_U32 u32CBufAddr10Bits;
}ST_XC_DIPR_PROPERTY;

DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_QueryResource(SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_GetResource(SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_ReleaseResource(SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_InitByDIP(SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_SetFrameBufferAddress(MS_PHYADDR u32FBAddress, MS_PHYADDR u32FBSize, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_SetInputSource(INPUT_SOURCE_TYPE_t enInputSourceType, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_GetInputSource(INPUT_SOURCE_TYPE_t *enInputSourceType, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_DisableInputSource(MS_BOOL bDisable, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_SetWindow(XC_SETWIN_INFO *pstXC_SetWin_Info, MS_U32 u32InitDataLen, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_GetDEWindow(MS_WINDOW_TYPE *psWin, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_SetCaptureWindowVstart(MS_U16 u16Vstart, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_SetCaptureWindowHstart(MS_U16 u16Hstart, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_SetCaptureWindowVsize(MS_U16 u16Vsize, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_SetCaptureWindowHsize(MS_U16 u16Hsize, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_GetCaptureWindow(MS_WINDOW_TYPE* capture_win, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_EnableR2Y(MS_BOOL benable, SCALER_DIP_WIN eWindow);

//==============Set===================
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_SWReset(SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_FrameRateCtrl(MS_BOOL bEnable,MS_U16 u16In,MS_U16 u16Out, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_CapOneFrame(SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_CapOneFrameFast(SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_ClearInt(MS_U16 u8mask, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_Ena(MS_BOOL bEnable, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_EnaInt(MS_U16 u8mask, MS_BOOL bEnable, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_SetSourceScanType(EN_XC_DIP_SCAN_MODE enScanMode, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_EnaInterlaceWrite(MS_BOOL bEnable, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_SetOutputDataFmt(EN_XC_DIP_DATA_FMT fmt, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_SetDIPWinProperty(ST_XC_DIP_WINPROPERTY *pstDIPWinProperty, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_EnableY2R(MS_BOOL bEnable, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_SetAlpha(MS_U8 u8AlphaVal, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_SwapUV(MS_BOOL bEnable, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_SwapYC(MS_BOOL bEnable, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_SwapRGB(MS_BOOL bEnable, EN_XC_DIP_RGB_SWAP_TYPE enSwapType, SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_SetWinProperty_Ex(MS_U8 u8BufCnt ,MS_U16 u16Width, MS_U16 u16Height, MS_U32 u32BufStart ,MS_U32 u32BufEnd, SCALER_DIP_SOURCE_TYPE eSource,SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_SetOutputCapture(MS_BOOL bEnable,EN_XC_DIP_OP_CAPTURE eOpCapture,SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_SetMirror(MS_BOOL bHMirror,MS_BOOL bVMirror,SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_SetDIPRProperty(ST_XC_DIPR_PROPERTY *pstDIPRProperty,SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_InterruptAttach(InterruptCb pIntCb,SCALER_DIP_WIN eWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_InterruptDetach(SCALER_DIP_WIN eWindow);
DLL_PUBLIC MS_U32 MApi_XC_DIP_SetPowerState(EN_POWER_MODE u16PowerState);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_Rotation(MS_BOOL bRotation,EN_XC_DIP_ROTATION eRoDirection,SCALER_DIP_WIN eTmpWindow);
DLL_PUBLIC E_APIXC_ReturnValue MApi_XC_DIP_SetPinpon(MS_BOOL bPinpon,MS_U32 u32PinponAddr,SCALER_DIP_WIN eWindow);
//==============Get===================
DLL_PUBLIC MS_U16 MApi_XC_DIP_GetIntStatus(SCALER_DIP_WIN eWindow);
DLL_PUBLIC BUFFER_INFO MApi_XC_DIP_GetBufInfo(SCALER_DIP_WIN eWindow);
#ifdef __cplusplus
}
#endif
#endif /* APIXC_DWIN_H */

