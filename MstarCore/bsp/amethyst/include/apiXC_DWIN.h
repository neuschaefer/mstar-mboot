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

#include "MsCommon.h"
//#include "mvideo_context.h"
//==============================================================================
//==============================================================================
#ifdef APIXC_DWIN_C//MVIDEO_CONTEXT_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

/// Define window type for DIP
typedef enum
{
    DIP_WINDOW = 0,         ///< DIP window
    MAX_DIP_WINDOW          /// The max support window
}SCALER_DIP_WIN;

/// Define source type for DIP
typedef enum
{
    SCALER_DIP_SOURCE_TYPE_SUB2 = 0,     ///< DIP from SUB2 
    SCALER_DIP_SOURCE_TYPE_MAIN = 1,     ///< DIP from MAIN
    SCALER_DIP_SOURCE_TYPE_SUB  = 2,     ///< DIP from SUB
    MAX_SCALER_DIP_SOURCE_NUM          /// The max support window
}SCALER_DIP_SOURCE_TYPE;

/// DWIN source data format
typedef enum
{
    /// CrYCb domain.
    DIP_DATA_FMT_YUV422 = 0,
    /// CrYCb domain.
    DIP_DATA_FMT_RGB565,
    /// RGB domain (CSC bypass).
    DIP_DATA_FMT_ARGB8888,
    /// YUV420
    DIP_DATA_FMT_YUV420,
    DIP_DATA_FMT_MAX
} EN_XC_DWIN_DATA_FMT;

/// DWIN scan mode
typedef enum
{
    /// progessive.
    DIP_SCAN_MODE_PROGRESSIVE,
    /// interlace.
    DIP_SCAN_MODE_extern,
} EN_XC_DWIN_SCAN_MODE;

E_APIXC_ReturnValue MApi_XC_DIP_Init(void);
E_APIXC_ReturnValue MApi_XC_DIP_SetFrameBufferAddress(MS_PHYADDR u32FBAddress, MS_PHYADDR u32FBSize, SCALER_DIP_WIN eWindow);
E_APIXC_ReturnValue MApi_XC_DIP_SetInputSource(INPUT_SOURCE_TYPE_t enInputSourceType, SCALER_DIP_WIN eWindow);
E_APIXC_ReturnValue MApi_XC_DIP_GetInputSource(INPUT_SOURCE_TYPE_t *enInputSourceType, SCALER_DIP_WIN eWindow);
E_APIXC_ReturnValue MApi_XC_DIP_DisableInputSource(MS_BOOL bDisable, SCALER_DIP_WIN eWindow);
E_APIXC_ReturnValue MApi_XC_DIP_SetWindow(XC_SETWIN_INFO *pstXC_SetWin_Info, MS_U32 u32InitDataLen, SCALER_DIP_WIN eWindow);
E_APIXC_ReturnValue MApi_XC_DIP_GetDEWindow(MS_WINDOW_TYPE *psWin, SCALER_DIP_WIN eWindow);
E_APIXC_ReturnValue MApi_XC_DIP_SetCaptureWindowVstart(MS_U16 u16Vstart, SCALER_DIP_WIN eWindow);
E_APIXC_ReturnValue MApi_XC_DIP_SetCaptureWindowHstart(MS_U16 u16Hstart, SCALER_DIP_WIN eWindow);
E_APIXC_ReturnValue MApi_XC_DIP_SetCaptureWindowVsize(MS_U16 u16Vsize, SCALER_DIP_WIN eWindow);
E_APIXC_ReturnValue MApi_XC_DIP_SetCaptureWindowHsize(MS_U16 u16Hsize, SCALER_DIP_WIN eWindow);
E_APIXC_ReturnValue MApi_XC_DIP_GetCaptureWindow(MS_WINDOW_TYPE* capture_win, SCALER_DIP_WIN eWindow);
E_APIXC_ReturnValue MApi_XC_DIP_EnableR2YCSC(MS_BOOL benable, SCALER_DIP_WIN eWindow);

//==============Set===================
E_APIXC_ReturnValue MApi_XC_DIP_CaptureOneFrame(void);
E_APIXC_ReturnValue MApi_XC_DIP_CaptureOneFrame2(void);
E_APIXC_ReturnValue MApi_XC_DIP_ClearIntr(MS_U16 u8mask);
E_APIXC_ReturnValue MApi_XC_DIP_Enable(MS_BOOL bEnable);
E_APIXC_ReturnValue MApi_XC_DIP_EnableIntr(MS_U16 u8mask, MS_BOOL bEnable);
E_APIXC_ReturnValue MApi_XC_DIP_SelectSourceScanType(EN_XC_DWIN_SCAN_MODE enScanMode);
E_APIXC_ReturnValue MApi_XC_DIP_DeInterlaceWrite(MS_BOOL bEnable);
E_APIXC_ReturnValue MApi_XC_DIP_SetDataFmt(EN_XC_DWIN_DATA_FMT fmt);
E_APIXC_ReturnValue MApi_XC_DIP_SetWinProperty(MS_U8 u8BufCnt, MS_U16 u16Width, MS_U16 u16Height, MS_U32 u32BufStart, MS_U32 u32BufEnd, SCALER_DIP_SOURCE_TYPE eSource);
E_APIXC_ReturnValue MApi_XC_DIP_SetY2R(MS_BOOL bEnable);
E_APIXC_ReturnValue MApi_XC_DIP_SetAlphaValue(MS_U8 u8AlphaVal);
E_APIXC_ReturnValue MApi_XC_DIP_SetUVSwap(MS_BOOL bEnable);
E_APIXC_ReturnValue MApi_XC_DIP_SetYCSwap(MS_BOOL bEnable);
E_APIXC_ReturnValue MApi_XC_DIP_SetRGBSwap(MS_BOOL bEnable);
//==============Get===================
MS_U16 MApi_XC_DIP_GetIntrStatus(void);



#endif /* APIXC_DWIN_H */

