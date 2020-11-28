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
/// @file   apiXC_ACE.h
/// @brief  ACE API layer Interface
/// @author MStar Semiconductor Inc.
/// CL 227231+:In box case, there is no need to do YUV2RGB transform.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _API_XC_ACE_H_
#define _API_XC_ACE_H_

// Common Definition
#include "MsCommon.h"
#include "MsVersion.h"

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
#define MSIF_ACE_LIB_CODE               {'A','C','E','_'}
#define MSIF_ACE_LIBVER                 {'0','0'}
#define MSIF_ACE_BUILDNUM               {'5','9'}
#define MSIF_ACE_CHANGELIST             {'0','0','6','2','1','0','5','3'}
#define XC_ACE_API_VERSION              /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_ACE_LIB_CODE,                  /* IP__                                             */  \
    MSIF_ACE_LIBVER,                    /* 0.0 ~ Z.Z                                        */  \
    MSIF_ACE_BUILDNUM,                  /* 00 ~ 99                                          */  \
    MSIF_ACE_CHANGELIST,                /* CL#                                              */  \
    MSIF_OS

/*!
   The color information setting.
*/
typedef enum
{
    /// Version
    E_XC_ACE_INFO_TYPE_VERSION,
    /// Contrast
    E_XC_ACE_INFO_TYPE_CONTRAST,
    /// R Gain
    E_XC_ACE_INFO_TYPE_R_GAIN,
    /// G Gain
    E_XC_ACE_INFO_TYPE_G_GAIN,
    /// B Gain
    E_XC_ACE_INFO_TYPE_B_GAIN,
    /// Saturation
    E_XC_ACE_INFO_TYPE_SATURATION,
    /// Hue
    E_XC_ACE_INFO_TYPE_HUE,
    /// Color correction XY R
    E_XC_ACE_INFO_TYPE_COLOR_CORRECTION_XY_R,
    /// Color correction XY G
    E_XC_ACE_INFO_TYPE_COLOR_CORRECTION_XY_G,
    /// Color correction XY B
    E_XC_ACE_INFO_TYPE_COLOR_CORRECTION_XY_B,
    /// Color correction Offset R
    E_XC_ACE_INFO_TYPE_COLOR_CORRECTION_OFFSET_R,
    /// Color correction Offset G
    E_XC_ACE_INFO_TYPE_COLOR_CORRECTION_OFFSET_G,
    /// Color correction Offset B
    E_XC_ACE_INFO_TYPE_COLOR_CORRECTION_OFFSET_B,
    /// R Brightness
    E_XC_ACE_INFO_TYPE_BRIGHTNESS_R,
    /// G Brightness
    E_XC_ACE_INFO_TYPE_BRIGHTNESS_G,
    /// B Brightness
    E_XC_ACE_INFO_TYPE_BRIGHTNESS_B,

    /// Dummy
    E_XC_ACE_INFO_TYPE_DUMMY
} E_XC_ACE_INFOTYPE;

/*!
    The convert method of YUV to RGB
*/
typedef enum
{
    /// YUV to RGB matrix - Use Std CSCM for SDTV
    E_XC_ACE_YUV_TO_RGB_MATRIX_SDTV,
    /// YUV to RGB matrix - Use Std CSCM for HDTV
    E_XC_ACE_YUV_TO_RGB_MATRIX_HDTV,
    /// Use user define CSCM, specified by tUserYVUtoRGBMatrix
    E_XC_ACE_YUV_TO_RGB_MATRIX_USER,
} E_XC_ACE_YUVTORGBTYPE;

/*!
   The Effect Settings of Multi Window
*/
typedef enum
{
    /// off
    E_XC_ACE_MWE_MODE_OFF,
    /// H split, reference window at right side,default
    E_XC_ACE_MWE_MODE_H_SPLIT,
    /// Move
    E_XC_ACE_MWE_MODE_MOVE,
    /// Zoom
    E_XC_ACE_MWE_MODE_ZOOM,
    /// H Scan
    E_XC_ACE_MWE_MODE_H_SCAN,
    /// H split, reference window at left side
    E_XC_ACE_MWE_MODE_H_SPLIT_LEFT,
    /// The number of Scaler ACE MWE functoin
    E_XC_ACE_MWE_MODE_NUMS,
} E_XC_ACE_MWE_FUNC;

/*!
   The Result of XC_ACE function call.
*/
typedef enum
{
    /// fail
    E_XC_ACE_FAIL = 0,
    /// ok
    E_XC_ACE_OK = 1,
    /// get base address failed when initialize panel driver
    E_XC_ACE_GET_BASEADDR_FAIL,
    /// obtain mutex timeout when calling this function
    E_XC_ACE_OBTAIN_MUTEX_FAIL,
} E_XC_ACE_RESULT;


typedef enum
{
    E_XC_ACE_MWE_MIRROR_NORMAL,
    E_XC_ACE_MWE_MIRROR_H_ONLY,
    E_XC_ACE_MWE_MIRROR_V_ONLY,
    E_XC_ACE_MWE_MIRROR_HV,
    E_XC_ACE_MWE_MIRROR_MAX,
}E_XC_ACE_MWE_MIRROR_TYPE;

/*!
   obosolte!! use XC_ACE_color_temp_ex2 instead
*/
typedef struct
{
    /// red color offset
    MS_U8 cRedOffset;
    /// green color offset
    MS_U8 cGreenOffset;
    /// blue color offset
    MS_U8 cBlueOffset;

    /// red color
    MS_U8 cRedColor;
    /// green color
    MS_U8 cGreenColor;
    /// blue color
    MS_U8 cBlueColor;

    /// scale 100 value of red color
    MS_U8 cRedScaleValue;
    /// scale 100 value of green color
    MS_U8 cGreenScaleValue;
    /// scale 100 value of blue color
    MS_U8 cBlueScaleValue;
} XC_ACE_color_temp;

/*!
   obosolte!! use XC_ACE_color_temp_ex2 instead
*/
typedef struct
{
    /// red color offset
    MS_U16 cRedOffset;
    /// green color offset
    MS_U16 cGreenOffset;
    /// blue color offset
    MS_U16 cBlueOffset;

    /// red color
    MS_U8 cRedColor;
    /// green color
    MS_U8 cGreenColor;
    /// blue color
    MS_U8 cBlueColor;

    /// scale 100 value of red color
    MS_U8 cRedScaleValue;
    /// scale 100 value of green color
    MS_U8 cGreenScaleValue;
    /// scale 100 value of blue color
    MS_U8 cBlueScaleValue;
} XC_ACE_color_temp_ex;

/*!
   The color temp settings ex2.
*/
typedef struct
{
    /// red color offset
    MS_U16 cRedOffset;
    /// green color offset
    MS_U16 cGreenOffset;
    /// blue color offset
    MS_U16 cBlueOffset;

    /// red color
    MS_U16 cRedColor;
    /// green color
    MS_U16 cGreenColor;
    /// blue color
    MS_U16 cBlueColor;

    /// scale 100 value of red color
    MS_U16 cRedScaleValue;
    /// scale 100 value of green color
    MS_U16 cGreenScaleValue;
    /// scale 100 value of blue color
    MS_U16 cBlueScaleValue;
} XC_ACE_color_temp_ex2;

//----------------------------
// XC ACE initialize
//----------------------------
/*!
   The ACE initialze DATA.
*/
typedef struct
{
    MS_BOOL    eWindow;                  ///< initial eWindow

    MS_S16*    S16ColorCorrectionMatrix; ///< initial Color Correction Matrix

    MS_S16*    S16RGB;                   ///< initial RGB

    MS_U16     u16MWEHstart;             ///< initial Horizontal start


    MS_U16     u16MWEVstart;             ///< initial Vertical start

    MS_U16     u16MWEWidth;              ///< initial MWE Width

    MS_U16     u16MWEHeight;             ///< initial MWE Height

    MS_U16     u16MWE_Disp_Hstart;       ///< initial MWE Display Horizontal start

    MS_U16     u16MWE_Disp_Vstart;       ///< initial MWE Display Vertical start

    MS_U16     u16MWE_Disp_Width;        ///< initial MWE Display width

    MS_U16     u16MWE_Disp_Height;       ///< initial MWE Display height

    MS_BOOL    bMWE_Enable;              ///< Enable or not
} XC_ACE_InitData;

/*!
   The XC_ACE library infomation.
*/
typedef struct
{

} XC_ACE_ApiInfo;

/*!
   The XC_ACE status infomation.
*/
typedef struct
{
    /// Scaler ACE API status
    XC_ACE_InitData ACEinit;
} XC_ACE_ApiStatus;


/*!
   The XC_ACE DNR parameters settings.
*/
typedef enum
{
    /// NR ONOFF
    E_ACE_DNR_NR_ONOFF,
    /// SNR
    E_ACE_DNR_SNR,
    /// Spike NR 0
    E_ACE_DNR_SPIKE_NR_0,
    /// Spike NR 1
    E_ACE_DNR_SPIKE_NR_1,
    /// Gray ground gain
    E_ACE_DNR_GRAY_GROUND_GAIN,
    /// Gray ground EN
    E_ACE_DNR_GRAY_GROUND_EN,
    /// Peaking bank coring
    E_ACE_DNR_PEAKING_BANK_CORING,
    /// Guassin SNR threshold
    E_ACE_DNR_GUASSIN_SNR_THRESHOLD,
    /// Motion
    E_ACE_DNR_MOTION,
    /// Peaking coring threshold
    E_ACE_DNR_PEAKING_CORING_THRESHOLD,
    /// Sharpness adjust
    E_ACE_DNR_SHARPNESS_ADJUST,
    /// NM V
    E_ACE_DNR_NM_V,
    /// GNR 0
    E_ACE_DNR_GNR_0,
    /// GNR 1
    E_ACE_DNR_GNR_1,
    /// CP
    E_ACE_DNR_CP,
    /// DP
    E_ACE_DNR_DP,
    /// NM H 0
    E_ACE_DNR_NM_H_0,
    /// HM H 1
    E_ACE_DNR_NM_H_1,
    /// SC coring
    E_ACE_DNR_SC_CORING,
    /// NM
    E_ACE_DNR_SNR_NM,
}XC_ACE_DNR_Param;

typedef enum
{
    E_ACE_IHC_COLOR_R,
    E_ACE_IHC_COLOR_G,
    E_ACE_IHC_COLOR_B,
    E_ACE_IHC_COLOR_C,
    E_ACE_IHC_COLOR_M,
    E_ACE_IHC_COLOR_Y,
    E_ACE_IHC_COLOR_F,
    E_ACE_IHC_COLOR_MAX,
}XC_ACE_IHC_COLOR_TYPE;

#define ACE_INFOEX_MODE_POST_RGB_GAIN           0x1
#define ACE_INFOEX_MODE_POST_RGB_OFFSET         0x2
typedef struct
{
    MS_U32 u32Mode;
    MS_U32 u32Reserved;
}XC_ACE_InfoEx;

//--------------------------------------------------------------------------------------------------
// MWE Load Visual Effect Table related
//--------------------------------------------------------------------------------------------------
#define ACE_TABINFO_VERSION                0

#define ACE_TABINFO_REG_ADDR_SIZE          (2)
#define ACE_TABINFO_REG_MASK_SIZE          (1)
#define ACE_TABINFO_REG_DATA_SIZE          (2)

typedef struct
{
    MS_U8 *pTable;
    MS_U8 u8TabCols;
    MS_U8 u8TabRows;
    MS_U8 u8TabIdx;
    MS_U32 u32ACE_TabInfo_version; //Version of current structure, including the content of pTable
}XC_ACE_TAB_Info;
//--------------------------------------------------------------------------------------------------

//------------------------------
// Weave Type: used for 3D
//------------------------------
typedef enum
{
    E_ACE_WEAVETYPE_NONE        = 0x00,
    E_ACE_WEAVETYPE_H          = 0x01,
    E_ACE_WEAVETYPE_V          = 0x02,
    E_ACE_WEAVETYPE_DUALVIEW    = 0x04,
    E_ACE_WEAVETYPE_NUM,
}XC_ACE_WEAVETYPE;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
#define XC_ACE_BYPASS_COLOR_GAIN  128 //necessary for HW color tempture adjustment,
                                      //used after T2, i.e: T3/T4/T7/T8/Janus..

/********************************************************************************/
/*                   msAPI_ACE.c                   */
/********************************************************************************/

//-------------------------------------------------------------------------------------------------
/// ACE Initiation
/// @param  pstXC_ACE_InitData                  \b IN: @ref XC_ACE_InitData
/// @param  u32InitDataLen                      \b IN: The Length of pstXC_ACE_InitData.
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_ACE_Init(XC_ACE_InitData *pstXC_ACE_InitData, MS_U32 u32InitDataLen);


//-------------------------------------------------------------------------------------------------
/// ACE Exit
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_ACE_Exit(void);

//-------------------------------------------------------------------------------------------------
/// ACE DMS
/// @param  eWindow                 \b IN: Indicates the window where the ACE function applies to.
/// @param  bisATV                  \b IN: Whether the active input source is or not ATV.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_ACE_DMS(MS_BOOL eWindow, MS_BOOL bisATV);

//-------------------------------------------------------------------------------------------------
/// Set PC YUV to RGB
/// @param  eWindow                  \b IN: Indicates the window where the ACE function applies to.
/// @param  bEnable                  \b IN: Enable or Disalbe the function.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_ACE_SetPCYUV2RGB(MS_BOOL eWindow, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Select YUV to RGB Matrix, if the ucMatrix type is ACE_YUV_TO_RGB_MATRIX_USER, then apply the
/// psUserYUVtoRGBMatrix supplied by user.
// @param  eWindow                       \b IN: Indicates the window where the ACE function applies to.
// @param  ucMatrix                      \b IN: @ref E_ACE_YUVTORGBInfoType.
// @param  psUserYUVtoRGBMatrix          \b IN: User-Defined color transformed matrix.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_ACE_SelectYUVtoRGBMatrix(MS_BOOL eWindow, MS_U8 ucMatrix, MS_S16* psUserYUVtoRGBMatrix);

//-------------------------------------------------------------------------------------------------
/// Set color correction table
/// @param  bScalerWin                      \b IN: Indicates the window where the ACE function
///                                                 applies to, 0: Main Window, 1: Sub Window.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_ACE_SetColorCorrectionTable( MS_BOOL bScalerWin);

//-------------------------------------------------------------------------------------------------
/// Set PCs RGB table
/// @param  bScalerWin                      \b IN: Indicates the window where the ACE function
///                                                 applies to, 0: Main Window, 1: Sub Window.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_ACE_SetPCsRGBTable( MS_BOOL bScalerWin);

//-------------------------------------------------------------------------------------------------
/// Get color matrix
/// @param  eWindow                      \b IN: Indicates the window where the ACE function applies to.
/// @param  pu16Matrix                   \b OUT: a MS_U16 matrix represents current color matrix
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_ACE_GetColorMatrix(MS_BOOL eWindow, MS_U16* pu16Matrix);

//-------------------------------------------------------------------------------------------------
/// Set color matrix
/// @param  eWindow                      \b IN: Indicates the window where the ACE function applies to.
/// @param  pu16Matrix                   \b IN: The Matrix given to set the color transformation.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_ACE_SetColorMatrix( MS_BOOL eWindow, MS_U16* pu16Matrix);

//-------------------------------------------------------------------------------------------------
/// Set Bypass Color Matrix
/// @param bEnable      \b IN:  Enable : Bypass Set Color Matrix
/// @return @ref E_XC_ACE_RESULT
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC E_XC_ACE_RESULT MApi_XC_ACE_SetBypassColorMatrix(MS_BOOL bEnable );

//-------------------------------------------------------------------------------------------------
/// Set IHC value
/// @param  bScalerWin                   \b IN: Indicates the window where the ACE function applies to.
/// @param  eIHC                         \b IN: Indicates the color to be set.
/// @param  u8Val                        \b IN: The value set to the color(0 ~ 127).
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_ACE_SetIHC(MS_BOOL bScalerWin, XC_ACE_IHC_COLOR_TYPE eIHC, MS_U8 u8Val);

//-------------------------------------------------------------------------------------------------
/// Patch DTG color checker
// @param  u8Mode                       \b IN: TBD
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_ACE_PatchDTGColorChecker( MS_U8 u8Mode);

//-------------------------------------------------------------------------------------------------
/// Get ACE information
/// @param  bWindow                      \b IN: Indicates the window where the ACE function
///                                              applies to, 0: Main Window, 1: Sub Window.
/// @param  eXCACEInfoType                \b IN: Specify the information type users interested in.
/// @retval The information returned.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U16  MApi_XC_ACE_GetACEInfo( MS_BOOL bWindow, E_XC_ACE_INFOTYPE eXCACEInfoType );

//-------------------------------------------------------------------------------------------------
/// Get ACE extra information
/// @param  bWindow                      \b IN: Indicates the window where the ACE function
///                                              applies to, 0: Main Window, 1: Sub Window.
/// @param  XC_ACE_InfoEx                \b OUT: Specify the extra information returned by driver.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_ACE_GetACEInfoEx( MS_BOOL bWindow, XC_ACE_InfoEx *pInfoEx);

/********************************************************************************/
/*                   msAPI_ACE_Ext.c                   */
/********************************************************************************/
//-------------------------------------------------------------------------------------------------
/// Picture set contrast
/// @param  eWindow                       \b IN: Indicates the window where the ACE function applies to.
/// @param  bUseYUVSpace                  \b IN: Use YUV format or RGB format.
/// @param  u8Contrast                    \b IN: Contrase value given by user.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_ACE_PicSetContrast( MS_BOOL eWindow, MS_BOOL bUseYUVSpace, MS_U8 u8Contrast);

//-------------------------------------------------------------------------------------------------
/// Picture set brightness
/// @param  u8Brightness_R                    \b IN: R value given by user.
/// @param  u8Brightness_G                    \b IN: G value given by user.
/// @param  u8Brightness_B                    \b IN: B value given by user.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_ACE_PicSetBrightness( MS_BOOL eWindow, MS_U8 u8Brightness_R, MS_U8 u8Brightness_G, MS_U8 u8Brightness_B);

//-------------------------------------------------------------------------------------------------
/// Picture set precise brightness
/// @param  u16Brightness_R                    \b IN: R value given by user.
/// @param  u16Brightness_G                    \b IN: G value given by user.
/// @param  u16Brightness_B                    \b IN: B value given by user.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_ACE_PicSetBrightnessPrecise(MS_BOOL eWindow, MS_U16 u16Brightness_R, MS_U16 u16Brightness_G, MS_U16 u16Brightness_B);

//-------------------------------------------------------------------------------------------------
///-This function will set Pre Y Offset
///@param eWindow        \b IN: Window type
///@param u8PreYOffset \b IN: Pre Y Offset value
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC E_XC_ACE_RESULT MApi_XC_ACE_PicSetPreYOffset(MS_BOOL eWindow, MS_U8 u8PreYOffset);

//-------------------------------------------------------------------------------------------------
///-This function will get Pre Y Offset
///@param eWindow        \b IN: Window type
///@param pu8PreYOffset \b OUT: Pre Y Offset value
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U8 MApi_XC_ACE_PicGetPreYOffset(MS_BOOL eWindow);

//-------------------------------------------------------------------------------------------------
/// Picture set Hue
/// @param  eWindow                  \b IN: Indicates the window where the ACE function applies to.
/// @param  bUseYUVSpace             \b IN: Use YUV format or RGB format.
/// @param  u8Hue                    \b IN: Hue value given by user.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_ACE_PicSetHue( MS_BOOL eWindow, MS_BOOL bUseYUVSpace, MS_U8 u8Hue );

//-------------------------------------------------------------------------------------------------
/// Skip Wait Vsync
/// @param eWindow               \b IN: Enable
/// @param Skip wait Vsync      \b IN: Disable wait Vsync
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC E_XC_ACE_RESULT MApi_XC_ACE_SkipWaitVsync( MS_BOOL eWindow,MS_BOOL bIsSkipWaitVsyn);

//-------------------------------------------------------------------------------------------------
/// Picture set Saturation
/// @param  eWindow                  \b IN: Indicates the window where the ACE function applies to.
/// @param  bUseYUVSpace             \b IN: Use YUV format or RGB format.
/// @param  u8Saturation             \b IN: Saturation value given by user.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_ACE_PicSetSaturation(MS_BOOL eWindow, MS_BOOL bUseYUVSpace, MS_U8 u8Saturation );

//-------------------------------------------------------------------------------------------------
///-Adjust sharpness
/// @param  eWindow                  \b IN: Indicates the window where the ACE function applies to.
/// @param u8Sharpness                \b IN: sharpness value
///- 0 -0x3f
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_ACE_PicSetSharpness(  MS_BOOL eWindow, MS_U8 u8Sharpness );

//-------------------------------------------------------------------------------------------------
/// Picture set color temp.
/// @param  eWindow                  \b IN: Indicates the window where the ACE function applies to.
/// @param  bUseYUVSpace             \b IN: Use YUV format or RGB format.
/// @param  pstColorTemp             \b IN: Color temp info given by user.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_ACE_PicSetColorTemp( MS_BOOL eWindow, MS_BOOL bUseYUVSpace, XC_ACE_color_temp* pstColorTemp);
//-------------------------------------------------------------------------------------------------
/// Picture set color temp ex.
/// @param  eWindow                  \b IN: Indicates the window where the ACE function applies to.
/// @param  bUseYUVSpace             \b IN: Use YUV format or RGB format.
/// @param  pstColorTemp             \b IN: Color temp info given by user.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_ACE_PicSetColorTempEx( MS_BOOL eWindow, MS_BOOL bUseYUVSpace, XC_ACE_color_temp_ex* pstColorTemp);

//-------------------------------------------------------------------------------------------------
/// Picture set post color temp
/// V02. Change the fields in XC_ACE_color_temp_ex structure to MS_U16
/// @param  eWindow                  \b IN: Indicates the window where the ACE function applies to.
/// @param  pstColorTemp             \b IN: Color temp info given by user.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_ACE_PicSetPostColorTemp_V02(MS_BOOL eWindow, XC_ACE_color_temp_ex2* pstColorTemp);

#ifndef _API_XC_ACE_C_
// Projects without ENABLE_NEW_COLORTEMP_METHOD defined will set ENABLE_NEW_COLORTEMP_METHOD to 0
#ifndef ENABLE_NEW_COLORTEMP_METHOD
  #define ENABLE_NEW_COLORTEMP_METHOD 0
#endif

#ifndef ENABLE_PRECISE_RGBBRIGHTNESS
  #define ENABLE_PRECISE_RGBBRIGHTNESS 0
#endif

#if ENABLE_NEW_COLORTEMP_METHOD
    #if ENABLE_PRECISE_RGBBRIGHTNESS
        #define MApi_XC_ACE_PicSetColorTemp(x, y, z) MApi_XC_ACE_PicSetPostColorTemp2Ex(x, y, z)
    #else
        #define MApi_XC_ACE_PicSetColorTemp(x, y, z) MApi_XC_ACE_PicSetPostColorTemp2(x, y, z)
    #endif
#else
    #if ENABLE_PRECISE_RGBBRIGHTNESS
        #define MApi_XC_ACE_PicSetColorTemp(x, y, z) MApi_XC_ACE_PicSetColorTempEx(x, y, z)
    #endif
#endif

#define MApi_XC_ACE_PicSetBrightnessInVsync(bWin, x, y, z) {MApi_XC_WaitOutputVSync(2, 100, bWin); MApi_XC_ACE_PicSetBrightness(bWin, x, y, z);}
#define MApi_XC_ACE_PicSetBrightnessPreciseInVsync(bWin, x, y, z) {MApi_XC_WaitOutputVSync(2, 100, bWin); MApi_XC_ACE_PicSetBrightnessPrecise(bWin, x, y, z);}

#endif

//-------------------------------------------------------------------------------------------------
/// Set Flesh tone
/// @param  eWindow                  \b IN: Indicates the window where the ACE function applies to.
/// @param  bEn                      \b IN: @ref MS_BOOL
/// @param  u8FleshTone              \b IN: Flesh Tone Value
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_ACE_SetFleshTone(MS_BOOL eWindow, MS_BOOL bEn, MS_U8 u8FleshTone);

//-------------------------------------------------------------------------------------------------
/// black adjsutment
/// @param  eWindow                           \b IN: window type.
/// @param  u8BlackAdjust                     \b IN: adjust value given.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_ACE_SetBlackAdjust(MS_BOOL eWindow, MS_U8 u8BlackAdjust);

//-------------------------------------------------------------------------------------------------
/// IHC sram
/// @param  pBuf                            \b IN: sram data
/// @param  u16ByteSize                     \b IN: size of sram
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_ACE_Set_IHC_SRAM(MS_U16 *pBuf, MS_U16 u16ByteSize);

//-------------------------------------------------------------------------------------------------
/// IHC sram
/// @param  pBuf                            \b IN: sram data
/// @param  u16ByteSize                     \b IN: size of sram
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_ACE_Set_ICC_SRAM(MS_U16 *pBuf, MS_U16 u16ByteSize);

/********************************************************************************/
/*                  MWE function                  */
/********************************************************************************/

//-------------------------------------------------------------------------------------------------
/// Enable MWE
/// @param  bEnable                     \b IN: @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_ACE_EnableMWE(MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// MWE Clone Main Window Visual Effect
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_ACE_MWECloneVisualEffect(void);

//-------------------------------------------------------------------------------------------------
/// MWE Apply Visual Effect From Reg Table
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_ACE_MWESetRegTable(XC_ACE_TAB_Info *pMWETable);

//-------------------------------------------------------------------------------------------------
/// Flag for MWE Visual Effect Coming From Reg Table
/// @param  bEnable                     \b IN: @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_ACE_SetMWELoadFromPQ(MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// MWE status
/// @retval  @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_ACE_MWEStatus(void);

//-------------------------------------------------------------------------------------------------
/// MWE Handle
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_ACE_MWEHandle( void );

//-------------------------------------------------------------------------------------------------
/// MWE function selection
/// @param  eWindow                 \b IN: Indicates the window where the ACE function applies to.
/// @param  mwe_func                     \b IN: @ref E_XC_ACE_MWE_FUNC
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_ACE_MWEFuncSel( MS_BOOL eWindow, E_XC_ACE_MWE_FUNC  mwe_func); 
//-------------------------------------------------------------------------------------------------
/// MWE set display window
/// @param  u16MWE_Disp_Hstart             \b IN: Horizotal position of start point. 0:means leftest position.
/// @param  u16MWE_Disp_Vstart             \b IN: Vertical position of start point, 0: mean up most position.
/// @param  u16MWE_Disp_Width              \b IN: Width of display window.
/// @param  u16MWE_Disp_Height             \b IN: Height of display winodw.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_ACE_MWESetDispWin(MS_U16 u16MWE_Disp_Hstart, MS_U16 u16MWE_Disp_Vstart, MS_U16 u16MWE_Disp_Width, MS_U16 u16MWE_Disp_Height);

//-------------------------------------------------------------------------------------------------
/// 3D clone main and sub window's PQmap
/// @param  enWeaveType             \b IN: Output WeaveType
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_ACE_3DClonePQMap(XC_ACE_WEAVETYPE enWeaveType);

/********************************************************************************/
/*                  DynamicNR function                                          */
/********************************************************************************/

//-------------------------------------------------------------------------------------------------
/// DNR Blending NR table
/// @param  pu8NewNR              \b IN: new NR target values.
/// @param  u8Weight              \b IN: Blending weighting.
/// @param  u8Step                \b IN: maxmium step size.
/// @param  pu16PreY0             \b IN: previous NR value 0.
/// @param  pu16PreY1             \b IN: previous NR value 1.
/// @param  pu8NRTBL              \b OUT: The new NR Table.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void   MApi_XC_ACE_DNR_Blending_NRTbl(MS_U8 *pu8NewNR, MS_U8 u8Weight, MS_U8 u8Step, MS_U16 *pu16PreY0, MS_U16 *pu16PreY1, MS_U8 *pu8NRTBL);

//-------------------------------------------------------------------------------------------------
/// DNR Blending MISC
/// @param  u8NewItem              \b IN: New DNR blending target value.
/// @param  u16PreItem             \b IN: previous value.
/// @param  u8Weight               \b IN: Blending weighting.
/// @param  u8Step                 \b IN: Maxmium step size.
/// @retval new DNR blending value.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U16 MApi_XC_ACE_DNR_Blending_MISC(MS_U8 u8NewItem, MS_U16 u16PreItem, MS_U8 u8Weight, MS_U8 u8Step);

//-------------------------------------------------------------------------------------------------
/// DNR Blending
/// @param  u8NewItem              \b IN: New DNR blending target value.
/// @param  u16PreItem             \b IN: previous value.
/// @param  u8Weight               \b IN: Blending weighting.
/// @retval new DNR blending value.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U8  MApi_XC_ACE_DNR_Blending(MS_U8 u8NewItem, MS_U16 u16PreItem, MS_U8 u8Weight);

//-------------------------------------------------------------------------------------------------
/// DNR get precision shift
/// @retval shift value.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U16 MApi_XC_ACE_DNR_Get_PrecisionShift(void);

//-------------------------------------------------------------------------------------------------
/// DNR get motion weight
/// @param  u8CurMotion                 \b IN: current motion value
/// @param  u8PreMotion                 \b IN: previous motion value
/// @param  u8CurMotionLvl              \b IN: current motion catalog-level
/// @param  u8PreMotionLvl              \b IN: previous motion catalog-level
/// @param  u8DeFlick_Thre              \b IN: de-flick threshold.
/// @param  u8DeFilick_Step             \b IN: de-flick step size.
/// @retval motion weight
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U8  MApi_XC_ACE_DNR_GetMotion_Weight(MS_U8 u8CurMotion, MS_U8 u8PreMotion, MS_U8 u8CurMotionLvl, MS_U8 u8PreMotionLvl, MS_U8 u8DeFlick_Thre, MS_U8 u8DeFilick_Step);

//-------------------------------------------------------------------------------------------------
/// DNR get Luma weight
/// @param  u8CurAvgLuma                 \b IN: current avergae luma
/// @param  u8PreAvgLuam                 \b IN: previous average luma
/// @param  u8CurLumaLvl                 \b IN: current avergae luma catalog-level
/// @param  u8PreLumaLvl                 \b IN: previous avergae luma catalog-level
/// @param  u8DeFlick_Th                 \b IN: de-flick threshold.
/// @param  u8DeFlick_Step               \b IN: de-flick step size.
/// @retval luma weight
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U8  MApi_XC_ACE_DNR_GetLuma_Weight(MS_U8 u8CurAvgLuma, MS_U8 u8PreAvgLuam, MS_U8 u8CurLumaLvl, MS_U8 u8PreLumaLvl, MS_U8 u8DeFlick_Th,  MS_U8 u8DeFlick_Step);

//-------------------------------------------------------------------------------------------------
/// DNR get noise weight
/// @param  u8CurNoise                 \b IN: current noise.
/// @param  u8PreNoise                 \b IN: previous noise.
/// @param  u8Range                    \b IN: noise threshold, if difference between PreNoise and
///                                          CurNoise > this value, then the stable status is down
///                                          -grade for 1 degree.
/// @param  u8DeFlick_Th              \b IN: de-flick threshold.
/// @param  u8DeFlick_Step            \b IN: de-flick step size.
/// @retval Noise weighting value.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U8  MApi_XC_ACE_DNR_GetNoise_Weight(MS_U8 u8CurNoise, MS_U8 u8PreNoise, MS_U8 u8Range, MS_U8 u8DeFlick_Th, MS_U8 u8DeFlick_Step);

//-------------------------------------------------------------------------------------------------
/// DNR get motion degree, lower one means its more like a still video.
/// @retval motion degree value.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U8  MApi_XC_ACE_DNR_GetMotion(void);

//-------------------------------------------------------------------------------------------------
/// DNR init motion
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void   MApi_XC_ACE_DNR_Init_Motion(void);

//-------------------------------------------------------------------------------------------------
/// DNR init luma
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void   MApi_XC_ACE_DNR_Init_Luma(void);

//-------------------------------------------------------------------------------------------------
/// DNR init noise
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void   MApi_XC_ACE_DNR_Init_Noise(void);

//-------------------------------------------------------------------------------------------------
/// Set parameter of a DNR item specified by user.
/// @param  eWindow                 \b IN: Indicates the window where the ACE function applies to.
/// @param  eParam                 \b IN: @ref XC_ACE_DNR_Param
/// @param  u16val                 \b IN: Setting value of DNR item.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void   MApi_XC_ACE_DNR_SetParam(MS_BOOL eWindow, XC_ACE_DNR_Param eParam, MS_U16 u16val);

//-------------------------------------------------------------------------------------------------
/// Get parameter of a DNR item specified by user.
/// @param  eWindow                 \b IN: Indicates the window where the ACE function applies to.
/// @param  eParam                 \b IN: @ref XC_ACE_DNR_Param
/// @return @ref MS_U8
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U8  MApi_XC_ACE_DNR_GetParam(MS_BOOL eWindow, XC_ACE_DNR_Param eParam);

//-------------------------------------------------------------------------------------------------
/// Set NR table
/// @param  pu8Tbl                 \b IN: NR table given by user.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void   MApi_XC_ACE_DNR_SetNRTbl(MS_U8 *pu8Tbl);

// must have functions
//-------------------------------------------------------------------------------------------------
/// Get version (without Mutex protect)
/// @param  ppVersion                 \b OUT: Version information of ACE lib.
/// @return @ref E_XC_ACE_RESULT
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC E_XC_ACE_RESULT MApi_XC_ACE_GetLibVer(const MSIF_Version **ppVersion);

//-------------------------------------------------------------------------------------------------
/// Get info from driver (without Mutex protect)
/// @return XC_ACE_ApiInfo
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC const XC_ACE_ApiInfo * MApi_XC_ACE_GetInfo(void);

//-------------------------------------------------------------------------------------------------
/// Get panel current status
/// @param  pDrvStatus                 \b IN: @ref XC_ACE_ApiStatus
/// @param  bWindow                    \b IN: Indicates the window where the ACE function
///                                           applies to, 0: Main Window, 1: Sub Window.
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_ACE_GetStatus(XC_ACE_ApiStatus *pDrvStatus, MS_BOOL bWindow);

//-------------------------------------------------------------------------------------------------
/// Set debug level (without Mutex protect)
/// @param  u16DbgSwitch                 \b IN: debug switch value, use TRUE/FALSE to turn on/off.
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_ACE_SetDbgLevel(MS_U16 u16DbgSwitch);


DLL_PUBLIC void MApi_XC_ACE_ColorCorrectionTable( MS_BOOL bScalerWin, MS_S16 *psColorCorrectionTable );

DLL_PUBLIC void MApi_XC_ACE_SetColorMatrixControl( MS_BOOL bScalerWin, MS_BOOL bEnable );
DLL_PUBLIC void MApi_XC_ACE_SetRBChannelRange( MS_BOOL bScalerWin, MS_BOOL bRange );


//////////////////////////////////////////////
// Below functions are obosolted ! Please do not use them if you do not use them yet.
//////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
///-obosolte!! use MApi_XC_ACE_PicSetPostColorTemp_V02 instead
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_ACE_PicSetPostColorTemp(MS_BOOL eWindow, XC_ACE_color_temp* pstColorTemp);

//-------------------------------------------------------------------------------------------------
///-obosolte!! use MApi_XC_ACE_PicSetPostColorTemp_V02 instead
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_ACE_PicSetPostColorTempEx(MS_BOOL eWindow, XC_ACE_color_temp_ex* pstColorTemp);

//-------------------------------------------------------------------------------------------------
///-obosolte!! use MApi_XC_ACE_PicSetPostColorTempWithBypassACESetting instead
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_ACE_PicSetPostColorTemp2(MS_BOOL eWindow, MS_BOOL bUseYUVSpace, XC_ACE_color_temp* pstColorTemp);

//*************************************************************************
///-obosolte!! Please bypass color temp by using MApi_XC_ACE_PicSetColorTemp and then set post color temp by using MApi_XC_ACE_PicSetPostColorTemp_V02
//*************************************************************************
DLL_PUBLIC void MApi_XC_ACE_PicSetPostColorTemp2Ex(MS_BOOL eWindow, MS_BOOL bUseYUVSpace, XC_ACE_color_temp_ex* pstColorTemp);



#ifdef __cplusplus
}
#endif

#endif // _API_XC_ACE_H_

