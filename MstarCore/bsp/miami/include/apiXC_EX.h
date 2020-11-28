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
/// @file   apiXC_EX.h
/// @brief  XC EXTENSION Interface FOR DUAL STREAMS
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _API_XC_EX_H_
#define _API_XC_EX_H_

#include "MsCommon.h"
// Driver
#include "drvXC_IOPort.h"

#ifdef __cplusplus
extern "C"
{
#endif


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
//  library information
#define MSIF_XC_EX_LIB_CODE               {'X','C','E','X'}
#define MSIF_XC_EX_LIBVER                 {'0','9'}
#define MSIF_XC_EX_BUILDNUM               {'0','8'}
#define MSIF_XC_EX_CHANGELIST             {'0','0','7','0','9','8','0','1'}
#define XC_EX_API_VERSION               /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_XC_EX_LIB_CODE  ,              /* IP__                                             */  \
    MSIF_XC_EX_LIBVER    ,              /* 0.0 ~ Z.Z                                        */  \
    MSIF_XC_EX_BUILDNUM  ,              /* 00 ~ 99                                          */  \
    MSIF_XC_EX_CHANGELIST,              /* CL#                                              */  \
    MSIF_OS

#define XC_EX_INITDATA_VERSION                            1
#define XC_EX_OUTPUT_TIMING_ADJUST_VERSION                1
/// PANEL_INFO_EX version of current XC lib
#define XC_EX_PANEL_INFO_EX_VERSION                          2
/// hw 2d to 3d para version
#define XC_EX_HW2DTO3DPARA_VERSION                           2
/// 3d detect format para version
#define XC_EX_DETECT3DFORMATPARA_VERSION                     1

/// ApiStatusEX version of current XC lib
/// Define below to distinguish from API_PNLSTATUS_EX_VERSION
#define XC_EX_APISTATUS_EX_VERSION                        2
//#define API_STATUS_EX_VERSION                          XC_EX_APISTATUS_EX_VERSION

/// 3d fp info version of current XC lib
#define XC_EX_3D_FPINFOPARA_VERSION                       1
/// report pixel info version of current XC lib
#define XC_EX_REPORT_PIXELINFO_VERSION                    1

/// osdc disp info version of current XC lib
#define XC_EX_ODSC_DISPINFO_VERSIN                          1

#define _XC_EX_BIT(_bit_)                  (1 << (_bit_))

//----------------------------
// Return value
//----------------------------

/// XC Return Value
typedef enum
{
    E_XC_EX_RET_FAIL = 0,                   ///<Fail
    E_XC_EX_RET_OK,                         ///<OK
    E_XC_EX_RET_FAIL_FUN_NOT_SUPPORT,       ///<Fail
    E_XC_EX_RET_FAIL_ENUM_NOT_SUPPORT,      ///<Fail
    E_XC_EX_RET_FAIL_INVALID_PARAMETER,     ///<Fail
} XC_EX_RETURN_VALUE;

//----------------------------
// Debug Switch
//----------------------------
#define XC_EX_DBGLEVEL_OFF             (0x0000)   ///< Turn off
#define XC_EX_DBGLEVEL_SETWINDOW       (0x0001)   ///< Set Window
#define XC_EX_DBGLEVEL_SETTIMING       (0x0002)   ///< LPLL  / SetPanelTiming
#define XC_EX_DBGLEVEL_SYNCDETECT      (0x0004)   ///< Sync detection        ======>Not using it by now
#define XC_EX_DBGLEVEL_MUX             (0x0008)   ///< Mux / Path Creation
#define XC_EX_DBGLEVEL_MODEPARSE       (0x0010)   ///< Mode Parse            ======>Not using it by now
#define XC_EX_DBGLEVEL_HDMIMONITOR     (0x0020)   ///< HDMI and Package Monitor ===>Not using it by now
#define XC_EX_DBGLEVEL_AUTOGEOMETRY    (0x0040)   ///< Auto Geometry   / Auto Calibration
#define XC_EX_DGBLEVEL_CROPCALC        (0x0080)   ///< Crop Window / Memory / OPM / IPM calculation

#define XC_EX_DBGLEVEL_SETTIMING_ISR   (0x0100)   ///< ISR / SetPanelTiming
#define XC_EX_DBGLEVEL_DWIN_SETWINDOW  (0x0200)   ///< DWIN / Set Window
#define XC_EX_DBGLEVEL_FUNCTION_TRACE  (0x0400)   ///< Trace XC function using status
#define XC_EX_DBGLEVEL_PARAMETER_TRACE (0x0800)   ///< Trace XC function parameter

//----------------------------
// Input signal detect
//----------------------------

#define XC_EX_MD_VSYNC_POR_BIT            _XC_EX_BIT(0) ///< VSnc polarity bit(0/1 = positive/negative)
#define XC_EX_MD_HSYNC_POR_BIT            _XC_EX_BIT(1) ///< HSync polarity bit(0/1 = positive/negative)
#define XC_EX_MD_HSYNC_LOSS_BIT           _XC_EX_BIT(2) ///< HSync loss bit
#define XC_EX_MD_VSYNC_LOSS_BIT           _XC_EX_BIT(3) ///< VSync loss bit
#define XC_EX_MD_INTERLACE_BIT            _XC_EX_BIT(4) ///< Interlace mode
#define XC_EX_MD_USER_MODE_BIT            _XC_EX_BIT(7) ///< User new mode (Not found in mode table)
#define XC_EX_MD_SYNC_LOSS                (XC_EX_MD_HSYNC_LOSS_BIT | XC_EX_MD_VSYNC_LOSS_BIT) ///< VSync & HSync loss bit

//----------------------------
// 3D macros
//----------------------------
#define XC_EX_DOUBLEHD_PRESCALE_VONEHDSIZE (540)

#define XC_EX_DOUBLEHD_1080X2I_FRAME_VSIZE (1080)
#define XC_EX_DOUBLEHD_1080X2I_FIELD_VSIZE (540)
#define XC_EX_DOUBLEHD_1080X2I_HSIZE (1920)
#define XC_EX_DOUBLEHD_1080X2I_VACT_SPACE1 (23)
#define XC_EX_DOUBLEHD_1080X2I_VACT_SPACE2 (22)
#define XC_EX_DOUBLEHD_1080X2I_VSIZE (XC_EX_DOUBLEHD_1080X2I_FRAME_VSIZE*2+XC_EX_DOUBLEHD_1080X2I_VACT_SPACE1*2+XC_EX_DOUBLEHD_1080X2I_VACT_SPACE2)

#define XC_EX_DOUBLEHD_1080X2P_VSIZE (2205)
#define XC_EX_DOUBLEHD_1080X2P_FRAME_VSIZE (1080)
#define XC_EX_DOUBLEHD_1080X2P_HSIZE (1920)
#define XC_EX_DOUBLEHD_1080X2P_GARBAGE_VSIZE (45)

#define XC_EX_DOUBLEHD_720X2P_VSIZE (1470)
#define XC_EX_DOUBLEHD_720X2P_FRAME_VSIZE (720)
#define XC_EX_DOUBLEHD_720X2P_HSIZE (1280)
#define XC_EX_DOUBLEHD_720X2P_GARBAGE_VSIZE (30)

#define XC_EX_DOUBLEHD_576X2P_VSIZE (1201)
#define XC_EX_DOUBLEHD_576X2P_FRAME_VSIZE (576)
#define XC_EX_DOUBLEHD_576X2P_HSIZE (720)
#define XC_EX_DOUBLEHD_576X2P_GARBAGE_VSIZE (49)


#define XC_EX_DOUBLEHD_480X2P_VSIZE (1005)
#define XC_EX_DOUBLEHD_480X2P_FRAME_VSIZE (480)
#define XC_EX_DOUBLEHD_480X2P_HSIZE (720)
#define XC_EX_DOUBLEHD_480X2P_GARBAGE_VSIZE (45)

// Field Interleave
#define XC_EX_FIELD_INTERLEAVE_1080X2I_FRAME_VSIZE  (1080)
#define XC_EX_FIELD_INTERLEAVE_1080X2I_FIELD_VISZE  (540)
#define XC_EX_FIELD_INTERLEAVE_1080X2I_HISZE        (1920)
#define XC_EX_FIELD_INTERLEAVE_1080X2I_VACT_SPACE   (23)
#define XC_EX_FIELD_INTERLEAVE_1080X2I_VISZE        (XC_EX_FIELD_INTERLEAVE_1080X2I_FRAME_VSIZE+XC_EX_FIELD_INTERLEAVE_1080X2I_VACT_SPACE)


///< When disable panel_info_ex, this means disable all valid panel info
#define XC_EX_PANEL_INFO_EX_INVALID_ALL    0xFFFF
//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

//----------------------------
// Common
//----------------------------

/// Define window type
typedef enum
{
    E_XC_EX_MAIN_WINDOW=0,          ///< main window if with PIP or without PIP
    E_XC_EX_SUB_WINDOW=1,           ///< sub window if PIP
    E_XC_EX_MAX_WINDOW              /// The max support window
} XC_EX_SCALER_WIN;

#define XC_EX_PIP_WINDOWS E_XC_EX_MAX_WINDOW

/// Define Window position and size attribute
typedef struct
{
    MS_U16 x;           ///<start x of the window
    MS_U16 y;           ///<start y of the window
    MS_U16 width;       ///<width of the window
    MS_U16 height;      ///<height of the window
} XC_EX_WINDOW_TYPE;

////////////////////////////////////////////////////////////////////////////////
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This is abstract input source for XC library. If you want to add another one.
// Please contace with XC member
////////////////////////////////////////////////////////////////////////////////

/// Define Input type
typedef enum
{
    E_XC_EX_INPUT_SOURCE_VGA,           ///<0   VGA input
    E_XC_EX_INPUT_SOURCE_TV,            ///<1   TV input

    E_XC_EX_INPUT_SOURCE_CVBS,          ///<2   AV 1
    E_XC_EX_INPUT_SOURCE_CVBS2,         ///<3   AV 2
    E_XC_EX_INPUT_SOURCE_CVBS3,         ///<4   AV 3
    E_XC_EX_INPUT_SOURCE_CVBS4,         ///<5   AV 4
    E_XC_EX_INPUT_SOURCE_CVBS5,         ///<6   AV 5
    E_XC_EX_INPUT_SOURCE_CVBS6,         ///<7   AV 6
    E_XC_EX_INPUT_SOURCE_CVBS7,         ///<8   AV 7
    E_XC_EX_INPUT_SOURCE_CVBS8,         ///<9   AV 8
    E_XC_EX_INPUT_SOURCE_CVBS_MAX,      ///<10 AV max

    E_XC_EX_INPUT_SOURCE_SVIDEO,        ///<11 S-video 1
    E_XC_EX_INPUT_SOURCE_SVIDEO2,       ///<12 S-video 2
    E_XC_EX_INPUT_SOURCE_SVIDEO3,       ///<13 S-video 3
    E_XC_EX_INPUT_SOURCE_SVIDEO4,       ///<14 S-video 4
    E_XC_EX_INPUT_SOURCE_SVIDEO_MAX,    ///<15 S-video max

    E_XC_EX_INPUT_SOURCE_YPBPR,         ///<16 Component 1
    E_XC_EX_INPUT_SOURCE_YPBPR2,        ///<17 Component 2
    E_XC_EX_INPUT_SOURCE_YPBPR3,        ///<18 Component 3
    E_XC_EX_INPUT_SOURCE_YPBPR_MAX,     ///<19 Component max

    E_XC_EX_INPUT_SOURCE_SCART,         ///<20 Scart 1
    E_XC_EX_INPUT_SOURCE_SCART2,        ///<21 Scart 2
    E_XC_EX_INPUT_SOURCE_SCART_MAX,     ///<22 Scart max

    E_XC_EX_INPUT_SOURCE_HDMI,          ///<23 HDMI 1
    E_XC_EX_INPUT_SOURCE_HDMI2,         ///<24 HDMI 2
    E_XC_EX_INPUT_SOURCE_HDMI3,         ///<25 HDMI 3
    E_XC_EX_INPUT_SOURCE_HDMI4,         ///<26 HDMI 4
    E_XC_EX_INPUT_SOURCE_HDMI_MAX,      ///<27 HDMI max

    E_XC_EX_INPUT_SOURCE_DTV,           ///<28 DTV

    E_XC_EX_INPUT_SOURCE_DVI,           ///<29 DVI 1
    E_XC_EX_INPUT_SOURCE_DVI2,          ///<30 DVI 2
    E_XC_EX_INPUT_SOURCE_DVI3,          ///<31 DVI 2
    E_XC_EX_INPUT_SOURCE_DVI4,          ///<32 DVI 4
    E_XC_EX_INPUT_SOURCE_DVI_MAX,       ///<33 DVI max

    // Application source
    E_XC_EX_INPUT_SOURCE_STORAGE,       ///<34 Storage
    E_XC_EX_INPUT_SOURCE_KTV,           ///<35 KTV
    E_XC_EX_INPUT_SOURCE_JPEG,          ///<36 JPEG

    //Support Dual MVOP port
    E_XC_EX_INPUT_SOURCE_DTV2,          ///<37 DTV
    E_XC_EX_INPUT_SOURCE_STORAGE2,	    ///<38 Storage

    //Support Third MVOP port
    E_XC_EX_INPUT_SOURCE_DTV3,          ///<39 DTV

    // Support OP capture
    E_XC_EX_INPUT_SOURCE_SCALER_OP,     ///<40 scaler OP

    E_XC_EX_INPUT_SOURCE_NUM,           ///<41 number of the source
    E_XC_EX_INPUT_SOURCE_NONE = E_XC_EX_INPUT_SOURCE_NUM,    ///<NULL input
} XC_EX_INPUT_SOURCE_TYPE;

#define XC_EX_IsSrcTypeAV(x)             (((x)>=E_XC_EX_INPUT_SOURCE_CVBS)&&((x)<=E_XC_EX_INPUT_SOURCE_CVBS_MAX))/// x is AV
#define XC_EX_IsSrcTypeSV(x)             (((x)>=E_XC_EX_INPUT_SOURCE_SVIDEO)&&((x)<=E_XC_EX_INPUT_SOURCE_SVIDEO_MAX))///< x is SV
#define XC_EX_IsSrcTypeATV(x)            ((x)==E_XC_EX_INPUT_SOURCE_TV)///< x is ATV
#define XC_EX_IsSrcTypeScart(x)          (((x)>=E_XC_EX_INPUT_SOURCE_SCART)&&((x)<=E_XC_EX_INPUT_SOURCE_SCART_MAX))///< x is Scart
#define XC_EX_IsSrcTypeHDMI(x)           (((x)>=E_XC_EX_INPUT_SOURCE_HDMI)&&((x)<=E_XC_EX_INPUT_SOURCE_HDMI_MAX))///< x is HDMI
#define XC_EX_IsSrcTypeVga(x)            ((x)==E_XC_EX_INPUT_SOURCE_VGA)///< x is VGA
#define XC_EX_IsSrcTypeYPbPr(x)          (((x)>=E_XC_EX_INPUT_SOURCE_YPBPR)&&((x)<=E_XC_EX_INPUT_SOURCE_YPBPR_MAX))///<  x is YPbPr
#define XC_EX_IsSrcTypeDTV(x)            (((x)==E_XC_EX_INPUT_SOURCE_DTV) || ((x)==E_XC_EX_INPUT_SOURCE_DTV2) || ((x)==E_XC_EX_INPUT_SOURCE_DTV3))///< x is DTV
#define XC_EX_IsSrcTypeDVI(x)            (((x)>=E_XC_EX_INPUT_SOURCE_DVI)&&((x)<=E_XC_EX_INPUT_SOURCE_DVI_MAX))///< x is DVI
#define XC_EX_IsSrcTypeJpeg(x)           ((x)==E_XC_EX_INPUT_SOURCE_JPEG)///< x is JPEG
#define XC_EX_IsSrcTypeStorage(x)        (((x)==E_XC_EX_INPUT_SOURCE_STORAGE) || ((x)==E_XC_EX_INPUT_SOURCE_STORAGE2) || XC_EX_IsSrcTypeJpeg(x))///< x is Storage
#define XC_EX_IsSrcTypeDigitalVD(x)      ( XC_EX_IsSrcTypeAV(x)||XC_EX_IsSrcTypeSV(x)||XC_EX_IsSrcTypeATV(x)||XC_EX_IsSrcTypeScart(x))///< x is VD
#define XC_EX_IsSrcTypeAnalog(x)         ( XC_EX_IsSrcTypeVga(x)|| XC_EX_IsSrcTypeYPbPr(x))///< x is Analog
#define XC_EX_IsSrcTypeVideo(x)          ( XC_EX_IsSrcTypeYPbPr(x) || XC_EX_IsSrcTypeATV(x) || XC_EX_IsSrcTypeAV(x) || XC_EX_IsSrcTypeSV(x) || XC_EX_IsSrcTypeScart(x) || XC_EX_IsSrcTypeDTV(x) ) ///< x is Video
#define XC_EX_IsSrcTypeCapture(x)        ((x)==E_XC_EX_INPUT_SOURCE_SCALER_OP)///< x is scaler OP

////////////////////////////////////////////////////////////////////////////////
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This is abstract output source for XC library. If you want to add another one.
// Please contace with XC member
////////////////////////////////////////////////////////////////////////////////

/// Define XC device ID
typedef struct
{
    MS_U32 u32Version;
    MS_U32 u32Id;
} XC_DEVICE_ID;

/// Define XC device enum
typedef enum
{
    E_XC_EX_DEVICE0,
    E_XC_EX_DEVICE1,
    E_XC_EX_DEVICE_MAX,
} XC_EX_DEVICE_NUM;

/// Define output type
typedef enum
{
    E_XC_EX_OUTPUT_NONE     = 0,                ///<NULL output
    E_XC_EX_OUTPUT_SCALER_MAIN_WINDOW,          ///<output to Scaler main window
    E_XC_EX_OUTPUT_SCALER_SUB_WINDOW  = 10,     ///<output to Scaler sub window

    E_XC_EX_OUTPUT_CVBS1    = 20,               ///<output to CVBS1
    E_XC_EX_OUTPUT_CVBS2,                       ///<output to CVBS2
    // Reserved area

    E_XC_EX_OUTPUT_YPBPR0   = 40,               ///<output to YPBPR0
    E_XC_EX_OUTPUT_YPBPR1,                      ///<output to YPBPR1
    // Reserved area

    E_XC_EX_OUTPUT_HDMI1    = 60,               ///<output to HDMI1
    E_XC_EX_OUTPUT_HDMI2,                       ///<output to HDMI2

    E_XC_EX_OUTPUT_OFFLINE_DETECT = 80,         ///<output to OFFLINE detect

    E_XC_EX_OUTPUT_SCALER_DWIN = 100,           ///<output to Dwin

    E_XC_EX_OUTPUT_NUM,                         ///<number of outputs
}XC_EX_DEST_TYPE;


/// Define DeInterlace mode
typedef enum
{

    E_XC_EX_DEINT_OFF=0,         ///<deinterlace mode off
    E_XC_EX_DEINT_2DDI_BOB,      ///<deinterlace mode: BOB
    E_XC_EX_DEINT_2DDI_AVG,      ///<deinterlace mode: AVG
    E_XC_EX_DEINT_3DDI_HISTORY,  ///<deinterlace mode: HISTORY // 24 bit
    E_XC_EX_DEINT_3DDI,          ///<deinterlace mode:3DDI// 16 bit
} XC_EX_DEINTERLACE_MODE;


/// Define the members of IP Sync Status
typedef struct
{
    MS_U8  u8SyncStatus;    ///< IP Sync status: refer to MD_VSYNC_POR_BIT, etc
    MS_U16 u16Hperiod;      ///<H Period
    MS_U16 u16Vtotal;       ///<Vertcal total
} XC_EX_IP_SYNC_STATUS;

/// Define Freerun color
typedef enum
{
    E_XC_EX_FREE_RUN_COLOR_BLACK,
    E_XC_EX_FREE_RUN_COLOR_WHITE,
    E_XC_EX_FREE_RUN_COLOR_BLUE,
    E_XC_EX_FREE_RUN_COLOR_RED,
    E_XC_EX_FREE_RUN_COLOR_GREEN,
    E_XC_EX_FREE_RUN_COLOR_MAX,
} XC_EX_FREERUN_COLOR;

/// Define which panel output timing change mode is used to change VFreq for same panel
typedef enum
{
    E_XC_EX_PNL_CHG_DCLK   = 0,        ///<change output DClk to change Vfreq.
    E_XC_EX_PNL_CHG_HTOTAL = 1,        ///<change H total to change Vfreq.
    E_XC_EX_PNL_CHG_VTOTAL = 2,        ///<change V total to change Vfreq.
} XC_EX_PNL_OUT_TIMING_MODE;

typedef enum
{
    E_XC_EX_PNL_LPLL_TTL,                              ///< TTL  type
    E_XC_EX_PNL_LPLL_LVDS,                             ///< LVDS type
    E_XC_EX_PNL_LPLL_RSDS,                             ///< RSDS type
    E_XC_EX_PNL_LPLL_MINILVDS,                         ///< TCON  //E_XC_EX_PNL_LPLL_MINILVDS_6P_2Link
    E_XC_EX_PNL_LPLL_ANALOG_MINILVDS,                  ///< Analog TCON
    E_XC_EX_PNL_LPLL_DIGITAL_MINILVDS,                 ///< Digital TCON
    E_XC_EX_PNL_LPLL_MFC,                              ///< Ursa (TTL output to Ursa)
    E_XC_EX_PNL_LPLL_DAC_I,                            ///< DAC output
    E_XC_EX_PNL_LPLL_DAC_P,                            ///< DAC output
    E_XC_EX_PNL_LPLL_PDPLVDS,                          ///< For PDP(Vsync use Manually MODE)
    E_XC_EX_PNL_LPLL_EXT,
} XC_EX_PNL_LPLL_TYPE;


typedef enum
{

    E_XC_EX_PNL_LPLL_EPI34_8P = E_XC_EX_PNL_LPLL_EXT,
    E_XC_EX_PNL_LPLL_EPI28_8P,
    E_XC_EX_PNL_LPLL_EPI34_6P,
    E_XC_EX_PNL_LPLL_EPI28_6P,

    ///< replace this with E_XC_EX_PNL_LPLL_MINILVD
    E_XC_EX_PNL_LPLL_MINILVDS_5P_2L,
    E_XC_EX_PNL_LPLL_MINILVDS_4P_2L,
    E_XC_EX_PNL_LPLL_MINILVDS_3P_2L,
    E_XC_EX_PNL_LPLL_MINILVDS_6P_1L,
    E_XC_EX_PNL_LPLL_MINILVDS_5P_1L,
    E_XC_EX_PNL_LPLL_MINILVDS_4P_1L,
    E_XC_EX_PNL_LPLL_MINILVDS_3P_1L,

    E_XC_EX_PNL_LPLL_HS_LVDS,                          ///< High speed LVDS
    E_XC_EX_PNL_LPLL_HF_LVDS,                          ///< High Freqquency LVDS

    E_XC_EX_PNL_LPLL_TTL_TCON,
    E_XC_EX_PNL_LPLL_MINILVDS_2CH_3P_8BIT,             ///< 2 channel, 3 pair, 8 bits
    E_XC_EX_PNL_LPLL_MINILVDS_2CH_4P_8BIT,             ///< 2 channel, 4 pair, 8 bits
    E_XC_EX_PNL_LPLL_MINILVDS_2CH_5P_8BIT,             ///< 2 channel, 5 pair, 8 bits
    E_XC_EX_PNL_LPLL_MINILVDS_2CH_6P_8BIT,             ///< 2 channel, 6 pair, 8 bits

    E_XC_EX_PNL_LPLL_MINILVDS_1CH_3P_8BIT,             ///< 1 channel, 3 pair, 8 bits
    E_XC_EX_PNL_LPLL_MINILVDS_1CH_4P_8BIT,             ///< 1 channel, 4 pair, 8 bits
    E_XC_EX_PNL_LPLL_MINILVDS_1CH_5P_8BIT,             ///< 1 channel, 5 pair, 8 bits
    E_XC_EX_PNL_LPLL_MINILVDS_1CH_6P_8BIT,             ///< 1 channel, 6 pair, 8 bits

    E_XC_EX_PNL_LPLL_MINILVDS_2CH_3P_6BIT,             ///< 2 channel, 3 pari, 6 bits
    E_XC_EX_PNL_LPLL_MINILVDS_2CH_4P_6BIT,             ///< 2 channel, 4 pari, 6 bits
    E_XC_EX_PNL_LPLL_MINILVDS_2CH_5P_6BIT,             ///< 2 channel, 5 pari, 6 bits
    E_XC_EX_PNL_LPLL_MINILVDS_2CH_6P_6BIT,             ///< 2 channel, 6 pari, 6 bits

    E_XC_EX_PNL_LPLL_MINILVDS_1CH_3P_6BIT,             ///< 1 channel, 3 pair, 6 bits
    E_XC_EX_PNL_LPLL_MINILVDS_1CH_4P_6BIT,             ///< 1 channel, 4 pair, 6 bits
    E_XC_EX_PNL_LPLL_MINILVDS_1CH_5P_6BIT,             ///< 1 channel, 5 pair, 6 bits
    E_XC_EX_PNL_LPLL_MINILVDS_1CH_6P_6BIT,             ///< 1 channel, 6 pair, 6 bits

} XC_EX_PNL_LPLL_EXT_TYPE;

typedef enum
{
    E_XC_EX_MOD_OUTPUT_SINGLE = 0,          ///< single channel
    E_XC_EX_MOD_OUTPUT_DUAL = 1,            ///< dual channel

    E_XC_EX_MOD_OUTPUT_QUAD = 2,            ///< quad channel

} XC_EX_OUTPUT_MODE;

typedef enum
{
    E_XC_EX_VFREQ_50HZ          = 0x00,
    E_XC_EX_VFREQ_60HZ          = 0x01,
    E_XC_EX_VFREQ_FROM_SRC      = 0x02,
    E_XC_EX_VFREQ_FROM_PANEL    = 0x03,
} XC_EX_VFREQ_SEL;

/// Sources to VE
typedef enum
{
    E_XC_EX_NONE    =0x00,
    E_XC_EX_IP     = 0x01,     ///< Scaler IP
    E_XC_EX_VOP2   = 0x02,     ///< Scaler VOP2
    E_XC_EX_BRI    = 0x04,     ///< Scaler BRI

    /// Please use this for OSD OP video capture!!!
    E_XC_EX_OP2    = 0x08,     ///< Scaler OP2 - After Blending with OSD
    E_XC_EX_GAM    = 0x10,     ///< Scaler Gamma - Without Blending with OSD
    E_XC_EX_DITHER  = 0x20,    ///< Scaler noise dither - Without Blending with OSD

    /// Please use this for non-OSD OP video capture!!!
    E_XC_EX_OVERLAP = 0x40,    ///< Scaler color overlap - Without Blending with OSD
    E_XC_EX_IP_SUB  = 0x80,    ///< Scaler IP of sub window
} XC_EX_SOURCE_TO_VE;

///Port connect to pin 8 of SCART
typedef enum
{
    E_XC_EX_SCARTID_NONE      = 0x00,  ///< No connection
    E_XC_EX_SCARTID_TO_HSYNC0 = 0x01,  ///< Pin 8 of SCART connects to Hsync 0
    E_XC_EX_SCARTID_TO_HSYNC1 = 0x02,  ///< Pin 8 of SCART connects to Hsync 1
    E_XC_EX_SCARTID_TO_HSYNC2 = 0x04,  ///< Pin 8 of SCART connects to Hsync 2
    E_XC_EX_SCARTID_TO_SOG0   = 0x08,  ///< Pin 8 of SCART connects to SOG0
    E_XC_EX_SCARTID_TO_SOG1   = 0x10,  ///< Pin 8 of SCART connects to SOG1
    E_XC_EX_SCARTID_TO_SOG2   = 0x20,  ///< Pin 8 of SCART connects to SOG2
} XC_EX_SCART_ID_PORT;

/// Items for query driver or H/W capability.
typedef enum
{
    E_XC_EX_SUPPORT_IMMESWITCH        = 0x00000001,  ///< return true if H/W support HDMI immeswitch

    E_XC_EX_SUPPORT_DVI_AUTO_EQ       = 0x00000005,  ///< return true if driver support Auto EQ.

    E_XC_EX_SUPPORT_FRC_INSIDE        = 0x00000100,  ///< return true if scaler driver support FRC (MFC) function.

} XC_EX_CAPABILITY;

typedef enum
{
    E_XC_EX_IMMESWITCH        = 0x00000001,  ///< return true if H/W support HDMI immeswitch

    E_XC_EX_DVI_AUTO_EQ       = 0x00000002,  ///< return true if driver support Auto EQ.

    E_XC_EX_FRC_INSIDE        = 0x00000004,  ///< return true if scaler driver support FRC (MFC) function.

    E_XC_EX_DIP_CHIP_CAPS     = 0x00000008,  ///< return dip chip caps.

    E_XC_EX_3D_FBL_CAPS         = 0x00000010,  ///< return true if chip support fbl 3d.attention:fbl 3d only support sbs to lbl and sbs to sbs

    E_XC_EX_HW_SEAMLESS_ZAPPING   = 0x00000020,  ///< return true if H/W support seamless zapping

    E_XC_EX_SUPPORT_DEVICE1        = 0x00000040,  ///< return true if H/W support scaler device1

    E_XC_EX_SUPPORT_DETECT3D_IN3DMODE = 0x00000080,  ///< return true if H/W support detecting 3d when already in 3d mode

    E_XC_EX_2DTO3D_VERSION = 0x00000100,  ///< return value 2D-to-3D version

    E_XC_EX_SUPPORT_FORCE_VSP_IN_DS_MODE = 0x00000200,  ///< return if H/W support force post-Vscalin-down in DS mode

} XC_EX_CAPS;

typedef enum
{
    E_XC_EX_DS_INDEX_MVOP,
    E_XC_EX_DS_INDEX_SCALER,
    E_XC_EX_DS_INDEX_MAX,
} XC_EX_DS_INDEX_SOURCE;

/// Define panel information
typedef struct
{
    // XC need below information do to frame lock

    MS_U16 u16HStart;           ///<DE H start

    MS_U16 u16VStart;           ///<DE V start

    MS_U16 u16Width;            ///<DE H width

    MS_U16 u16Height;           ///< DE V height

    MS_U16 u16HTotal;           ///<H total

    MS_U16 u16VTotal;           ///<V total

    MS_U16 u16DefaultVFreq;     ///<Panel output Vfreq., used in free run

    MS_U8  u8LPLL_Mode;         ///<0: single mode, 1: dual mode
    XC_EX_PNL_OUT_TIMING_MODE enPnl_Out_Timing_Mode;    ///<Define which panel output timing change mode is used to change VFreq for same panel

    // Later need to refine to use Min/Max SET for PDP panel, but for LCD, it maybe no need to check the Min/Max SET
    MS_U16 u16DefaultHTotal;    ///<default H total
    MS_U16 u16DefaultVTotal;    ///<default V total

    MS_U32 u32MinSET;
    MS_U32 u32MaxSET;
    XC_EX_PNL_LPLL_TYPE  eLPLL_Type;         ///
} XC_EX_PANEL_INFO;


/// Define the extern special panel information for FPLL or other usage
/// Usage:
///       The first 3 members of below structure must be set as their corresponding description
///       The other members are set according to your request, none used members should be cleared to zero
/// Example code of set VTT slowly:
///    XC_PANEL_INFO_EX stPanelInfoEx;
///    memset(&stPanelInfoEx, 0, sizeof(XC_PANEL_INFO_EX));
///    stPanelInfoEx.u32PanelInfoEx_Version = EX_PANEL_INFO_EX_VERSION;
///    stPanelInfoEx.u16PanelInfoEX_Length = sizeof(XC_PANEL_INFO_EX);
///
///    stPanelInfoEx.bVttStepsValid = TRUE;
///    stPanelInfoEx.bVttDelayValid = TRUE;
///    stPanelInfoEx.u16VttSteps = xx; //set how many steps u want to set the vtt
///    stPanelInfoEx.u16VttDelay = xx;// set the delay between steps of setting vtt
///    stPanelInfoEx.u16VFreq = 500; //this step setting info is only for 50hz
///    if(MApi_XC_EX_SetExPanelInfo(TRUE, &stPanelInfoEx))//Check the set is accepted or not
///    stPanelInfoEx.u16VFreq = 600; //set same steps info for 60 hz
///    if(MApi_XC_EX_SetExPanelInfo(TRUE, &stPanelInfoEx))//Check the set is accepted or not
///
typedef struct
{
    MS_U32 u32PanelInfoEx_Version;   ///<Version of current structure. Please always set to "EX_PANEL_INFO_EX_VERSION" as input
    MS_U16 u16PanelInfoEX_Length;    ///<Length of this structure, u16PanelInfoEX_Length=sizeof(XC_PANEL_INFO_EX)
    MS_U16 u16VFreq;                 ///<Output Vfreq, unit: (1Hz/10), range 0~EX_PANEL_INFO_EX_INVALID_ALL
                                     ///<If disable ex panel info and u16VFreq = 0xFFFF means disable all valid ex panel info
                                     ///<If disable ex panel info and u16VFreq = 600 means disable the valid ex panel info for 60 hz
    MS_U16 u16HTotal;                ///<H total of output "u16VFreq"
    MS_BOOL bHTotalValid;            ///H total setting is valid in this structure
    MS_U16 u16VTotal;                ///<V total of output "u16VFreq"
    MS_BOOL bVTotalValid;            ///V total setting is valid in this structure
    MS_U32 u32DClk;                  ///<DCLK of output "u16VFreq", unit: KHz
    MS_BOOL bDClkValid;              ///DCLK, unit: KHz
    MS_U16 u16MinHTotal;             ///<Min H total
    MS_BOOL bMinHTotalValid;         ///Min H total
    MS_U16 u16MinVTotal;             ///<Min V total
    MS_BOOL bMinVTotalValid;         ///Min V total
    MS_U32 u32MinDClk;               ///<Min DCLK, unit: KHz
    MS_BOOL bMinDClkValid;           ///Min DCLK, unit: KHz
    MS_U16 u16MaxHTotal;             ///<Max H total
    MS_BOOL bMaxHTotalValid;         ///Max H total
    MS_U16 u16MaxVTotal;             ///<Max V total
    MS_BOOL bMaxVTotalValid;         ///Max V total
    MS_U32 u32MaxDClk;               ///<Min DCLK, unit: KHz
    MS_BOOL bMaxDClkValid;           ///Min DCLK, unit: KHz
    // sync related
    MS_U16 u16HSyncWidth;            ///<VOP_01[7:0], PANEL_HSYNC_WIDTH
    MS_BOOL bHSyncWidthValid;        ///<  VOP_01[7:0], PANEL_HSYNC_WIDTH
    MS_U16 u16HSyncBackPorch;        ///<PANEL_HSYNC_BACK_PORCH, no register setting, provide value for query only
                                     ///<not support Manuel VSync Start/End now
                                     ///<VOP_02[10:0] VSync start = Vtt - VBackPorch - VSyncWidth
                                     ///<VOP_03[10:0] VSync end = Vtt - VBackPorch
    MS_BOOL bHSyncBackPorchValid;
    MS_U16 u16VSyncWidth;            ///<define PANEL_VSYNC_WIDTH
    MS_BOOL bVSyncWidthValid;
    MS_U16 u16VSyncBackPorch;        ///<define PANEL_VSYNC_BACK_PORCH
    MS_BOOL bVSyncBackPorchValid;
    //step by step adjustment when 50/60 HZ Output switch
    MS_U16 u16HttSteps;              ///<Number of adjusting step from Old Htt to new htt
    MS_BOOL bHttStepsValid;
    MS_U16 u16HttDelay;              ///<Delay time in two steps
    MS_BOOL bHttDelayValid;
    MS_U16 u16VttSteps;              ///<Number of adjusting step from Old Htt to new htt
    MS_BOOL bVttStepsValid;
    MS_U16 u16VttDelay;              ///<Delay time in two steps
    MS_BOOL bVttDelayValid;
    MS_U16 u16DclkSteps;             ///<Number of adjusting step from Old Htt to new htt
    MS_BOOL bDclkStepsValid;
    MS_U16 u16DclkDelay;             ///<Delay time in two steps
    MS_BOOL bDclkDelayValid;         ///<DclkDelay setting is valid in this structure
}XC_EX_PANEL_INFO_EX;

/// Define new panel information
typedef struct
{
    MS_U32 u32TimingAdjustSetting_version;    ///<Version of current structure. Please always set this value as XC_EX_OUTPUT_TIMING_ADJUST_VERSION

    MS_U16 u16HTotal_Step;              ///<Number of adjusting step from Old Htt to new htt
    MS_U16 u16HTotal_Delay;             ///<Delay time in two steps
    MS_U16 u16HTotal_Ratio;             ///<Ratio of Htt for change to specific framerate (X10).

    MS_U16 u16VTotal_Step;              ///<Number of adjusting step from Old Vtt to new Vtt
    MS_U16 u16VTotal_Delay;             ///<Delay time in two steps
    MS_U16 u16VTotal_Ratio;             ///<Ratio of Vtt for change to specific framerate (X10).

    MS_U16 u16Dclk_Step;                ///<Number of adjusting step from Old Dclk to new Dclk
    MS_U16 u16Dclk_Delay;               ///<Delay time in two steps
    MS_U16 u16Dclk_Ratio;               ///<Ratio of Dclk for change to specific framerate (X10).

} XC_EX_OUTPUT_TIMING_ADJUST_SETTING;

/// Define the initial data for XC
typedef struct
{
    MS_U32 u32XC_version;                   ///<Version of current structure.
    // system related
    MS_U32 u32XTAL_Clock;                   ///<Crystal clock in Hz

    // frame buffer related
    MS_PHYADDR u32Main_FB_Start_Addr;       ///<scaler main window frame buffer start address, absolute without any alignment
    MS_U32 u32Main_FB_Size;                 ///<scaler main window frame buffer size, the unit is BYTES
    MS_PHYADDR u32Sub_FB_Start_Addr;        ///<scaler sub window frame buffer start address, absolute without any alignment
    MS_U32 u32Sub_FB_Size;                  ///<scaler sub window frame buffer size, the unit is BYTES

    // HDMI related, will be moved to HDMI module
    MS_BOOL bCEC_Use_Interrupt;             ///<CEC use interrupt or not, if not, will use polling

    // This is related to chip package. ( Share Ground / Non-Share Ground )
    MS_BOOL bIsShareGround;

    // function related
    MS_BOOL bEnableIPAutoCoast;             ///<Enable IP auto coast

    MS_BOOL bMirror;                        ///<mirror mode

    // panel related
    XC_EX_PANEL_INFO stPanelInfo;              ///<panel infomation

    // DLC
    MS_BOOL bDLC_Histogram_From_VBlank;     ///<If set to TRUE, the Y max/min report value is read from V blanking area

    // This is related to layout
    MS_U16 eScartIDPort_Sel;    ///<This is port selection (E_XC_SCART_ID_PORT) of Scart ID pin 8

    // frcm frame buffer related
    MS_PHYADDR u32Main_FRCM_FB_Start_Addr;       ///<scaler main window frcm frame buffer start address, absolute without any alignment
    MS_U32 u32Main_FRCM_FB_Size;                 ///<scaler main window frcm frame buffer size, the unit is BYTES
    MS_PHYADDR u32Sub_FRCM_FB_Start_Addr;        ///<scaler sub window frcm frame buffer start address, absolute without any alignment
    MS_U32 u32Sub_FRCM_FB_Size;                  ///<scaler sub window frcm frame buffer size, the unit is BYTES
} XC_EX_INITDATA;

/// define generic API infomation
typedef struct
{
    MS_U8 u8MaxWindowNum;                   ///<max window number that XC driver supports such as MAIN/SUB window
    MS_U8 u8NumOfDigitalDDCRam;             ///<indicate how many Digital DDCRam that use can use without external EDID EEPROM
    MS_U8 u8MaxFrameNumInMem;               ///<indicate maximal number of frames (Progressive mode) supported by scaler simultaneously
    MS_U8 u8MaxFieldNumInMem;               ///<indicate maximal number of fields (Interlace mode) supported by scaler simultaneously
} XC_EX_ApiInfo;

/// define the information of set window
typedef struct
{
    //-------------
    // Input
    //-------------
    XC_EX_INPUT_SOURCE_TYPE enInputSourceType;      ///<Input source

    //-------------
    // Window
    //-------------
    XC_EX_WINDOW_TYPE stCapWin;        ///<Capture window
    XC_EX_WINDOW_TYPE stDispWin;       ///<Display window
    XC_EX_WINDOW_TYPE stCropWin;       ///<Crop window

    //-------------
    // Timing
    //-------------
    MS_BOOL bInterlace;             ///<Interlaced or Progressive
    MS_BOOL bHDuplicate;            ///<flag for vop horizontal duplicate, for MVD, YPbPr, indicate input double sampled or not
    MS_U16  u16InputVFreq;          ///<Input V Frequency, VFreqx10, for calculate output panel timing
    MS_U16  u16InputVTotal;         ///<Input Vertical total, for calculate output panel timing
    MS_U16  u16DefaultHtotal;       ///<Default Htotal for VGA/YPbPr input
    MS_U8  u8DefaultPhase;          ///<Obsolete

    //-------------------------
    // customized post scaling
    //-------------------------
    MS_BOOL bHCusScaling;               ///<assign post H customized scaling instead of using XC scaling
    MS_U16  u16HCusScalingSrc;          ///<post H customized scaling src width
    MS_U16  u16HCusScalingDst;          ///<post H customized scaling dst width
    MS_BOOL bVCusScaling;               ///<assign post V manuel scaling instead of using XC scaling
    MS_U16  u16VCusScalingSrc;          ///<post V customized scaling src height
    MS_U16  u16VCusScalingDst;          ///<post V customized scaling dst height

    //--------------
    // 9 lattice
    //--------------
    MS_BOOL bDisplayNineLattice;        ///<used to indicate where to display in panel and where to put in frame buffer

    //-------------------------
    // customized pre scaling
    //-------------------------
    MS_BOOL bPreHCusScaling;            ///<assign pre H customized scaling instead of using XC scaling
    MS_U16  u16PreHCusScalingSrc;       ///<pre H customized scaling src width
    MS_U16  u16PreHCusScalingDst;       ///<pre H customized scaling dst width
    MS_BOOL bPreVCusScaling;            ///<assign pre V manuel scaling instead of using XC scaling
    MS_U16  u16PreVCusScalingSrc;       ///<pre V customized scaling src height
    MS_U16  u16PreVCusScalingDst;       ///<pre V customized scaling dst height
    MS_U16  u16DefaultPhase;            ///<Default Phase for VGA/YPbPr input
} XC_EX_SETWIN_INFO;

/// define the information for dynamic scaling (DS)
/// one entry of DS is:
///
/// 8 bit alignment
/// LSB ----> MSB
/// OP (32bits) -> IP (32bits)
/// [7:0]   [15:8]   [23:16]          [31:24]
/// Data_L  Data_H   Reg_Addr(16bit)  Reg_Bank
///
/// 16 bit alignment
/// LSB ----> MSB
/// OP (32bits) -> IP (32bits) -> 0xFFFFFFFF, 0xFFFFFFFF (dummy)
///
/// If bIP_DS_On == FALSE, the DS will ignore the IP information
/// If bOP_DS_On == FALSE, the DS will ignore the OP information
typedef struct
{
    MS_U32 u32DS_Info_BaseAddr;         ///< The memory base address to update IP/OP dynamic scaling registers. Absolute without any alignment.
    MS_U8  u8MIU_Select;                ///< 0: MIU0, 1: MIU1, etc.
    MS_U8  u8DS_Index_Depth;            ///< The index depth (how many entries to fire per MVOP Vsync falling) of DS
    MS_BOOL bOP_DS_On;                  ///< OP dynamic scaling on/off
    MS_BOOL bIPS_DS_On;                 ///< IPS dynamic scaling on/off
    MS_BOOL bIPM_DS_On;                 ///< IPM dynamic scaling on/off
} XC_EX_DynamicScaling_Info;

/// define the prescaling destiniation size limit
typedef struct
{
    MS_U16 u16MinDstWidth;              ///Minimum destination Width
    MS_U16 u16MinDstHeight;             ///Minimum destination Height
    MS_BOOL bEna;                       ///Enable this limit
} XC_EX_PreScalingLimit_Info;

/// Define source type for DIP
typedef enum
{
    E_XC_DIP_EX_SOURCE_TYPE_SUB2 = 0,       ///< DIP from SUB2(IP_F3)
    E_XC_DIP_EX_SOURCE_TYPE_MAIN = 1,       ///< DIP from MAIN(IP_MAIN)
    E_XC_DIP_EX_SOURCE_TYPE_SUB  = 2,       ///< DIP from SUB (IP_SUB)
    E_XC_DIP_EX_SOURCE_TYPE_OP_MAIN = 3,    ///< HVSP MAIN
    E_XC_DIP_EX_SOURCE_TYPE_OP_SUB = 4,     ///< HVSP SUB
    E_XC_DIP_EX_SOURCE_TYPE_DRAM = 5,       ///< DIP from DRAM
    E_XC_DIP_EX_SOURCE_TYPE_OP_CAPTURE = 6, ///< DIP from OP capture
    E_XC_DIP_EX_SOURCE_TYPE_OP_SC1_CAPTURE = 7, ///< DIP from OP SC1 capture
    E_XC_DIP_EX_MAX_SOURCE_NUM            ///< The max support window
} XC_DIP_EX_SOURCE_TYPE;

/// Define the path type
typedef enum
{
    E_XC_EX_PATH_TYPE_SYNCHRONOUS,      ///<synchronous path type
    E_XC_EX_PATH_TYPE_ASYNCHRONOUS,     ///<asynchronous path type
} XC_EX_PATH_TYPE;

/// Define the mux path information
typedef struct
{
    XC_EX_PATH_TYPE Path_Type;      ///<path type
    XC_EX_INPUT_SOURCE_TYPE src;    ///<source input type
    XC_EX_DEST_TYPE dest;           ///<destination type of output

    void (* path_thread)(XC_EX_INPUT_SOURCE_TYPE src, MS_BOOL bRealTimeMonitorOnly);    ///<path read
    void (* SyncEventHandler )(XC_EX_INPUT_SOURCE_TYPE src, void* para);                ///<sync event handler
    void (* DestOnOff_Event_Handler )(XC_EX_INPUT_SOURCE_TYPE src, void* para);         ///<destination on off event handler
    void (* dest_periodic_handler )(XC_EX_INPUT_SOURCE_TYPE src, MS_BOOL bRealTimeMonitorOnly) ;    ///<destination periodic handler
} XC_EX_MUX_PATH_INFO;

/// Image store format in XC
typedef enum
{
    E_XC_EX_IMAGE_STORE_444_24BIT,    ///< (8+8+8)   Y Cb Cr   / B G R
    E_XC_EX_IMAGE_STORE_422_16BIT,    ///< (8+8)     Y Cb Y Cr / G B G R
    E_XC_EX_IMAGE_STORE_422_24BIT,    ///< (10+10+4) Y Cb Y Cr / G B G R -- Y7 Y6 Y5 Y4 Y3 Y2 Y1 Y0 - C5 C4 C3 C2 C1 C0 Y9 Y8 - xx xx xx xx C9 C8 C7 C6
} XC_EX_IMAGE_STORE_FMT;

/// XC API status
typedef struct
{
    //----------------------
    // Customer setting
    //----------------------
    XC_EX_INPUT_SOURCE_TYPE enInputSourceType;      ///< Input source type

    //----------------------
    // Window
    //----------------------
    XC_EX_WINDOW_TYPE stCapWin;       ///<Capture window
    XC_EX_WINDOW_TYPE stDispWin;      ///<Display window
    XC_EX_WINDOW_TYPE stCropWin;      ///<Crop window

    //----------------------
    // Timing
    //----------------------
    MS_BOOL bInterlace;             ///<Interlaced or Progressive
    MS_BOOL bHDuplicate;            ///<flag for vop horizontal duplicate, for MVD, YPbPr, indicate input double sampled or not
    MS_U16  u16InputVFreq;          ///<Input V Frequency, VFreqx10, for calculate output panel timing
    MS_U16  u16InputVTotal;         ///<Input Vertical total, for calculate output panel timing
    MS_U16  u16DefaultHtotal;       ///<Default Htotal for VGA/YPbPr input
    MS_U8   u8DefaultPhase;         ///<Obsolete, use u16DefaultPhase instead

    //----------------------
    // customized scaling
    //----------------------
    MS_BOOL bHCusScaling;           ///<assign H customized scaling instead of using XC scaling
    MS_U16  u16HCusScalingSrc;      ///<H customized scaling src width
    MS_U16  u16HCusScalingDst;      ///<H customized scaling dst width
    MS_BOOL bVCusScaling;           ///<assign V manuel scaling instead of using XC scaling
    MS_U16  u16VCusScalingSrc;      ///<V customized scaling src height
    MS_U16  u16VCusScalingDst;      ///<V customized scaling dst height

    //--------------
    // 9 lattice
    //--------------
    MS_BOOL bDisplayNineLattice;    ///<used to indicate where to display in panel and where to put in frame buffer

    //----------------------
    // XC internal setting
    //----------------------

    /* scaling ratio */
    MS_U16 u16H_SizeAfterPreScaling;         ///<Horizontal size after prescaling
    MS_U16 u16V_SizeAfterPreScaling;         ///<Vertical size after prescaling
    MS_BOOL bPreV_ScalingDown;      ///<define whether it's pre-Vertical scaling down

    /* real crop win in memory */
    XC_EX_WINDOW_TYPE ScaledCropWin;

    /* others */
    MS_U32 u32Op2DclkSet;           ///<OP to Dot clock set

    /* Video screen status */
    MS_BOOL bBlackscreenEnabled;      ///<Black screen status
    MS_BOOL bBluescreenEnabled;       ///<Blue screen status
    MS_U16 u16VideoDark;            ///<Video dark

    MS_U16 u16V_Length;             ///<for MDrv_Scaler_SetFetchNumberLimit
    MS_U16 u16BytePerWord;          ///<BytePerWord in Scaler
    MS_U16 u16OffsetPixelAlignment; ///<Pixel alignment of Offset (including IPM/OPM)
    MS_U8 u8BitPerPixel;            ///<Bits number Per Pixel
    XC_EX_DEINTERLACE_MODE eDeInterlaceMode;       ///<De-interlace mode
    MS_U8 u8DelayLines;             ///<delay lines
    MS_BOOL bMemFmt422;             ///<whether memory format is 422, for easy usage
    XC_EX_IMAGE_STORE_FMT eMemory_FMT; ///<memory format
    MS_BOOL bForceNRoff;            ///<Force NR off
    MS_BOOL bEn3DNR;                ///<whether it's 3DNR enabled
    MS_BOOL bUseYUVSpace;           ///< color format before 3x3 matrix
    MS_BOOL bMemYUVFmt;             ///< memroy color format
    MS_BOOL bForceRGBin;            ///<Force set format in memory as RGB (only for RGB input source)
    MS_BOOL bLinearMode;            ///<Is current memory format LinearMode?

    // frame lock related
    // only main can select FB/FBL because panel output timing depends on main window, sub will always use FB
    MS_BOOL bFBL;                   ///<whether it's framebufferless case
    MS_BOOL bFastFrameLock;         ///<whether framelock is enabled or not
    MS_BOOL bDoneFPLL;              ///<whether the FPLL is done
    MS_BOOL bEnableFPLL;            ///<enable FPLL or not
    MS_BOOL bFPLL_LOCK;             ///<whether FPLL is locked (in specific threshold.)

    // Capture_Memory
    MS_U32 u32IPMBase0;             ///<IPM base 0
    MS_U32 u32IPMBase1;             ///<IPM base 1
    MS_U32 u32IPMBase2;             ///<IPM base 2
    MS_U16 u16IPMOffset;            ///<IPM offset
    MS_U32 u16IPMFetch;             ///<IPM fetch
} XC_EX_ApiStatus;

/// XC API status
typedef struct
{
    MS_U32 u32ApiStatusEx_Version;   ///<Version of current structure. Please always set to "EX_PANEL_INFO_EX_VERSION" as input
    MS_U16 u16ApiStatusEX_Length;    ///<Length of this structure, u16PanelInfoEX_Length=sizeof(XC_PANEL_INFO_EX)

    //----------------------
    // Customer setting
    //----------------------
    XC_EX_INPUT_SOURCE_TYPE enInputSourceType;      ///< Input source type

    //----------------------
    // Window
    //----------------------
    XC_EX_WINDOW_TYPE stCapWin;       ///<Capture window
    XC_EX_WINDOW_TYPE stDispWin;      ///<Display window
    XC_EX_WINDOW_TYPE stCropWin;      ///<Crop window

    //----------------------
    // Timing
    //----------------------
    MS_BOOL bInterlace;             ///<Interlaced or Progressive
    MS_BOOL bHDuplicate;            ///<flag for vop horizontal duplicate, for MVD, YPbPr, indicate input double sampled or not
    MS_U16  u16InputVFreq;          ///<Input V Frequency, VFreqx10, for calculate output panel timing
    MS_U16  u16InputVTotal;         ///<Input Vertical total, for calculate output panel timing
    MS_U16  u16DefaultHtotal;       ///<Default Htotal for VGA/YPbPr input
    MS_U8   u8DefaultPhase;         ///<Obsolete, use u16DefaultPhase instead

    //----------------------
    // Post customized scaling
    //----------------------
    MS_BOOL bHCusScaling;           ///<assign H customized scaling instead of using XC scaling
    MS_U16  u16HCusScalingSrc;      ///<H customized scaling src width
    MS_U16  u16HCusScalingDst;      ///<H customized scaling dst width
    MS_BOOL bVCusScaling;           ///<assign V manuel scaling instead of using XC scaling
    MS_U16  u16VCusScalingSrc;      ///<V customized scaling src height
    MS_U16  u16VCusScalingDst;      ///<V customized scaling dst height

    //--------------
    // 9 lattice
    //--------------
    MS_BOOL bDisplayNineLattice;    ///<used to indicate where to display in panel and where to put in frame buffer

    //----------------------
    // XC internal setting
    //----------------------

    /* scaling ratio */
    MS_U16 u16H_SizeAfterPreScaling;         ///<Horizontal size after prescaling
    MS_U16 u16V_SizeAfterPreScaling;         ///<Vertical size after prescaling
    MS_BOOL bPreV_ScalingDown;      ///<define whether it's pre-Vertical scaling down

    /* real crop win in memory */
    XC_EX_WINDOW_TYPE ScaledCropWin;

    /* others */
    MS_U32 u32Op2DclkSet;           ///<OP to Dot clock set

    /* Video screen status */
    MS_BOOL bBlackscreenEnabled;      ///<Black screen status
    MS_BOOL bBluescreenEnabled;       ///<Blue screen status
    MS_U16 u16VideoDark;            ///<Video dark

    MS_U16 u16V_Length;             ///<for MDrv_Scaler_SetFetchNumberLimit
    MS_U16 u16BytePerWord;          ///<BytePerWord in Scaler
    MS_U16 u16OffsetPixelAlignment; ///<Pixel alignment of Offset (including IPM/OPM)
    MS_U8 u8BitPerPixel;            ///<Bits number Per Pixel
    XC_EX_DEINTERLACE_MODE eDeInterlaceMode;       ///<De-interlace mode
    MS_U8 u8DelayLines;             ///<delay lines
    MS_BOOL bMemFmt422;             ///<whether memory format is 422, for easy usage
    XC_EX_IMAGE_STORE_FMT eMemory_FMT; ///<memory format
    MS_BOOL bForceNRoff;            ///<Force NR off
    MS_BOOL bEn3DNR;                ///<whether it's 3DNR enabled
    MS_BOOL bUseYUVSpace;           ///< color format before 3x3 matrix
    MS_BOOL bMemYUVFmt;             ///< memroy color format
    MS_BOOL bForceRGBin;            ///<Force set format in memory as RGB (only for RGB input source)
    MS_BOOL bLinearMode;            ///<Is current memory format LinearMode?

    // frame lock related
    // only main can select FB/FBL because panel output timing depends on main window, sub will always use FB
    MS_BOOL bFBL;                   ///<whether it's framebufferless case
    MS_BOOL bFastFrameLock;         ///<whether framelock is enabled or not
    MS_BOOL bDoneFPLL;              ///<whether the FPLL is done
    MS_BOOL bEnableFPLL;            ///<enable FPLL or not
    MS_BOOL bFPLL_LOCK;             ///<whether FPLL is locked (in specific threshold.)

    // Capture_Memory
    MS_U32 u32IPMBase0;             ///<IPM base 0
    MS_U32 u32IPMBase1;             ///<IPM base 1
    MS_U32 u32IPMBase2;             ///<IPM base 2
    MS_U16 u16IPMOffset;            ///<IPM offset
    MS_U32 u16IPMFetch;             ///<IPM fetch

    //----------------------
    // Pre customized scaling
    //----------------------
    MS_BOOL bPreHCusScaling;           ///<assign H customized scaling instead of using XC scaling
    MS_U16  u16PreHCusScalingSrc;      ///<H customized scaling src width
    MS_U16  u16PreHCusScalingDst;      ///<H customized scaling dst width
    MS_BOOL bPreVCusScaling;           ///<assign V manuel scaling instead of using XC scaling
    MS_U16  u16PreVCusScalingSrc;      ///<V customized scaling src height
    MS_U16  u16PreVCusScalingDst;      ///<V customized scaling dst height

    MS_BOOL bPQSetHSD;///<H_SizeAfterPreScaling is changed manually, which will skip PQ HSD sampling and filter

    MS_U16  u16DefaultPhase;           ///<Default Phase for VGA/YPbPr input
    MS_BOOL bIsHWDepthAdjSupported;    ///<Is hw depth adjustment for real 3d supported or not
    MS_BOOL bIs2LineMode;              ///<Is 2 line mode or not
    MS_BOOL bIsPNLYUVOutput;         ///<Is Scaler YUV output

    MS_U8  u8HDMIPixelRepetition;   ///<the HDMI pixel repetition info
}XC_EX_ApiStatusEx;

/// Define the set timing information
typedef struct
{
    MS_U32  u32HighAccurateInputVFreq;      ///<high accurate input V frequency
    MS_U16  u16InputVFreq;                  ///<input V frequency
    MS_U16  u16InputVTotal;                 ///<input vertical total
    MS_BOOL bMVOPSrc;                       ///<MVOP source
    MS_BOOL bFastFrameLock;                 ///<whether it's fast frame lock case
    MS_BOOL bInterlace;                     ///<whether it's interlace
} XC_EX_SetTiming_Info;

//------------------------------
// XC Auto
//------------------------------

/// internal calibration
typedef struct
{
    MS_U16  u16CH_AVG[3];
} XC_EX_AUTOADC_TYPE;

/// get IP1 report min/max R/G/B
typedef enum
{
    E_XC_EX_AUTO_MIN_R ,
    E_XC_EX_AUTO_MIN_G ,
    E_XC_EX_AUTO_MIN_B ,
    E_XC_EX_AUTO_MAX_R ,
    E_XC_EX_AUTO_MAX_G ,
    E_XC_EX_AUTO_MAX_B ,
} XC_EX_AUTO_GAIN_TYPE;

/// the tming types for internal calibration
typedef enum
{
    E_XC_EX_OFF,
    E_XC_EX_480P,
    E_XC_EX_576P,
    E_XC_EX_720P,
    E_XC_EX_1080P,
    E_XC_EX_480I,
    E_XC_EX_576I,
    E_XC_EX_720I,
    E_XC_EX_1080I,
} XC_EX_Internal_TimingType;

//------------------------------
// Software Reset
//------------------------------
/// software reset type
typedef enum
{
    E_XC_EX_REST_SCALER_ALL  = _XC_EX_BIT(0),
    E_XC_EX_REST_IP_F1       = _XC_EX_BIT(1),
    E_XC_EX_REST_IP_F2       = _XC_EX_BIT(2),
    E_XC_EX_REST_OP          = _XC_EX_BIT(3),
    E_XC_EX_REST_IP_ALL      = _XC_EX_BIT(4),
    E_XC_EX_REST_CLK         = (_XC_EX_BIT(6)|_XC_EX_BIT(3)),
} XC_EX_SOFTWARE_REST_TYPE_t;

/// Detect Europe HDTV status type
typedef enum
{
    E_XC_EX_EURO_AUS_HDTV_NORMAL = 0,         ///<not detected Euro or Aus HDTV
    E_XC_EX_EURO_HDTV_DETECTED,               ///<Euro HDTV detected
    E_XC_EX_AUSTRALIA_HDTV_DETECTED,          ///<Aus HDTV detected
} XC_EX_DETECT_EURO_HDTV_STATUS_TYPE;


//Capture_Memory

/// Define the rectangle information
typedef struct
{
    MS_S16 s16X_Start;      ///<rectangle start x
    MS_S16 s16Y_Start;      ///<rectangle start x
    MS_S16 s16X_Size;       ///<rectangle horizontal size
    MS_S16 s16Y_Size;       ///<rectangle vertical size

    MS_U8 *pRect;           ///<the buffer address for the rectangle
    MS_U32 u32RectPitch;    ///<rectangle pitch
    MS_U16 u16PointSize;    ///<point size, consider the memory size
} XC_EX_RECT_INFO;

/// Define for format of pixel 24 bit
typedef struct
{
    MS_U8 R_Cr;
    MS_U8 G_Y;
    MS_U8 B_Cb;
} XC_EX_PIXEL_24BIT;

/// Define for format of pixel 32 bit
typedef struct
{
    MS_U32 B_Cb   :10;
    MS_U32 G_Y    :10;
    MS_U32 R_Cr   :10;
    MS_U32 u8Dummy:2;
} XC_EX_PIXEL_32BIT;

/// Define for format of pixel 16 bit
typedef struct
{
    MS_U8 u8G_Y;
    MS_U8 u8BR_CbCr;
} XC_EX_PIXEL_422_8BIT;

typedef enum
{
    E_XC_EX_OUTPUTDATA_RGB10BITS = 0x00, ///< Dummy[31:30]  R[29:20]  G[19:10] B[9:0]
    E_XC_EX_OUTPUTDATA_RGB8BITS = 0x01, ///<   R[23:16]  G[15:8] B[7:0]
    E_XC_EX_OUTPUTDATA_4228BITS = 0x03, ///<   CbCr[15:8] Y[7:0]

    E_XC_EX_OUTPUTDATA_FRC_RGB10BITS = 0x04, ///< Dummy[31:30]  R[29:20]  G[19:10] B[9:0]
    E_XC_EX_OUTPUTDATA_FRC_RGB8BITS = 0x05, ///<   R[23:16]  G[15:8] B[7:0]
    E_XC_EX_OUTPUTDATA_FRC_4228BITS = 0x06, ///<   CbCr[15:8] Y[7:0]
} XC_EX_OUTPUTDATA_TYPE;

typedef enum
{
    E_XC_EX_INPUTDATA_RGB10BITS = 0x00, ///< Dummy[31:30]  R[29:20]  G[19:10] B[9:0]
    E_XC_EX_INPUTDATA_RGB8BITS = 0x01, ///<   R[23:16]  G[15:8] B[7:0]
    E_XC_EX_INPUTDATA_4228BITS = 0x03, ///<   CbCr[15:8] Y[7:0]
} XC_EX_INPUTDATA_TYPE;


/// define for the auto calbration window type
typedef struct
{
    MS_U16 u16X;        ///<window start x
    MS_U16 u16Xsize;    ///<window horizontal size
    MS_U16 u16Y;        ///<window start y
    MS_U16 u16Ysize;    ///<window vertical size
} XC_EX_AUTO_CAL_WINDOW;

typedef struct
{
    XC_EX_IMAGE_STORE_FMT eStoreFmt;    ///<image store format
    XC_EX_AUTO_CAL_WINDOW eCal_Win_Size;    ///<auto calbration window type
    XC_EX_AUTOADC_TYPE pixelMax;    ///<maximum value among the pixels
    XC_EX_AUTOADC_TYPE pixelMin;    ///<minimum value among the pixels
    XC_EX_AUTOADC_TYPE pixelAverage;    ///<average value among the pixels
} XC_EX_IMAGE_MEM_INFO;

/// defined channel select for contrast adjusting.
typedef enum
{
    E_XC_EX_VOP_CHR = 0,    ///< Channel R
    E_XC_EX_VOP_CHG,        ///< Channel G
    E_XC_EX_VOP_CHB,        ///< Channel B
    E_XC_EX_VOP_ALL,        ///< All Channel
} XC_EX_VOP_CHANNEL;

/// Define Scaler GOP IP setting.
typedef enum
{
    E_XC_EX_IP0_SEL_GOP0,
    E_XC_EX_IP0_SEL_GOP1,
    E_XC_EX_IP0_SEL_GOP2,
    E_XC_EX_NIP_SEL_GOP0,
    E_XC_EX_NIP_SEL_GOP1,
    E_XC_EX_NIP_SEL_GOP2,
    E_XC_EX_MVOP_SEL,
} XC_EX_IPSEL_GOP;

/// Define Scaler memory format
typedef enum
{
    E_XC_EX_MEM_FMT_AUTO = 0,
    E_XC_EX_MEM_FMT_444  = 1,
    E_XC_EX_MEM_FMT_422  = 2,
} XC_EX_MEM_FMT;

/// Define the PQ path information
/**
 *  The active Window for PQ function to takes place.
 */
typedef enum
{
    /// Main window
    PQ_EX_MAIN_WINDOW=0,
    /// Sub window
    PQ_EX_SUB_WINDOW=1,
    /// The max support window of PQ
    PQ_EX_MAX_WINDOW
} PQ_EX_WIN;

/**
 *  FOURCE COLOR FMT
 */
typedef enum
{
    /// Default
    PQ_EX_FOURCE_COLOR_DEFAULT,
    /// RGB
    PQ_EX_FOURCE_COLOR_RGB,
    /// YUV
    PQ_EX_FOURCE_COLOR_YUV,
} PQ_EX_FOURCE_COLOR_FMT;

/**
 * PQ DEINTERLACE MODE
 */
typedef enum
{
    /// off
    PQ_EX_DEINT_OFF=0,
    /// 2DDI BOB
    PQ_EX_DEINT_2DDI_BOB,
    /// 2DDI AVG
    PQ_EX_DEINT_2DDI_AVG,
    /// 3DDI History(24 bit)
    PQ_EX_DEINT_3DDI_HISTORY,
    /// 3DDI(16 bit)
    PQ_EX_DEINT_3DDI,
} PQ_EX_DEINTERLACE_MODE;
/**
 *  Video data information to supply when in PQ mode.
 */
typedef struct
{
    /// is FBL or not
    MS_BOOL bFBL;
    /// is interlace mode or not
    MS_BOOL bInterlace;
    /// input Horizontal size
    MS_U16  u16input_hsize;
    /// input Vertical size
    MS_U16  u16input_vsize;
    /// input Vertical total
    MS_U16  u16input_vtotal;
    /// input Vertical frequency
    MS_U16  u16input_vfreq;
    /// output Vertical frequency
    MS_U16  u16ouput_vfreq;
    /// Display Horizontal size
    MS_U16  u16display_hsize;
    /// Display Vertical size
    MS_U16  u16display_vsize;
}MS_PQ_EX_Mode_Info;
/**
 *  INPUT SOURCE TYPE
 */
typedef enum
{
    /// VGA
    PQ_EX_INPUT_SOURCE_VGA,
    /// TV
    PQ_EX_INPUT_SOURCE_TV,

    /// CVBS
    PQ_EX_INPUT_SOURCE_CVBS,

    /// S-video
    PQ_EX_INPUT_SOURCE_SVIDEO,

    /// Component
    PQ_EX_INPUT_SOURCE_YPBPR,
    /// Scart
    PQ_EX_INPUT_SOURCE_SCART,


    /// HDMI
    PQ_EX_INPUT_SOURCE_HDMI,

    /// DTV
    PQ_EX_INPUT_SOURCE_DTV,

    /// DVI
    PQ_EX_INPUT_SOURCE_DVI,

    // Application source
    /// Storage
    PQ_EX_INPUT_SOURCE_STORAGE,
    /// KTV
    PQ_EX_INPUT_SOURCE_KTV,
    /// JPEG
    PQ_EX_INPUT_SOURCE_JPEG,

    /// The max support number of PQ input source
    PQ_EX_INPUT_SOURCE_NUM,
    /// None
    PQ_EX_INPUT_SOURCE_NONE = PQ_EX_INPUT_SOURCE_NUM,
} PQ_EX_INPUT_SOURCE_TYPE;


// PQ Function
typedef enum
{
    E_PQ_EX_IOCTL_NONE             = 0x00000000,
    E_PQ_EX_IOCTL_HSD_SAMPLING     = 0x00000001,
    E_PQ_EX_IOCTL_PREVSD_BILINEAR  = 0x00000002,
    E_PQ_EX_IOCTL_ADC_SAMPLING     = 0x00000003,
    E_PQ_EX_IOCTL_RFBL_CTRL        = 0x00000004,
    E_PQ_EX_IOCTL_PQ_SUGGESTED_FRAMENUM     = 0x00000008,
    E_PQ_EX_IOCTL_SET_UCFEATURE             = 0x00000010,
	E_PQ_EX_IOCTL_SKIP_MADI_TBL				= 0x00000020,
    E_PQ_EX_IOCTL_NUM,
} PQ_EX_IOCTL_FLAG_TYPE;

typedef struct s_PQ_EX_Function
{

    void (* pq_disable_filmmode)(PQ_EX_WIN eWindow, MS_BOOL bOn);

    MS_BOOL (* pq_load_scalingtable)(PQ_EX_WIN eWindow, MS_U8 eXRuleType, MS_BOOL bPreV_ScalingDown,
                                      MS_BOOL bInterlace, MS_BOOL bColorSpaceYUV, MS_U16 u16InputSize, MS_U16 u16SizeAfterScaling);

    MS_BOOL (* pq_set_csc)(PQ_EX_WIN eWindow, PQ_EX_FOURCE_COLOR_FMT enFourceColor);

    PQ_EX_DEINTERLACE_MODE (* pq_set_memformat)(PQ_EX_WIN eWindow, MS_BOOL bMemFmt422, MS_BOOL bFBL, MS_U8 *u8BitsPerPixel);

    void (* pq_set_420upsampling)(PQ_EX_WIN eWindow, MS_BOOL bFBL, MS_BOOL bPreV_ScalingDown, MS_U16 u16V_CropStart);

    void (* pq_set_modeInfo)(PQ_EX_WIN eWindow, PQ_EX_INPUT_SOURCE_TYPE enInputSourceType, MS_PQ_EX_Mode_Info *pstPQModeInfo);

    void (* pq_deside_srctype)(PQ_EX_WIN eWindow, PQ_EX_INPUT_SOURCE_TYPE enInputSourceType);

    MS_BOOL (* pq_get_memyuvfmt)(PQ_EX_WIN eWindow, PQ_EX_FOURCE_COLOR_FMT enFourceColor);

    MS_BOOL (* pq_ioctl)(PQ_EX_WIN eWindow, MS_U32 u32Flag, void *pBuf, MS_U32 u32BufSize);
}PQ_EX_Function_Info;

typedef struct
{
    MS_U32 u32ratio;
    MS_BOOL bADVMode;
} PQ_EX_HSD_SAMPLING_INFO;

typedef struct
{
    PQ_EX_INPUT_SOURCE_TYPE enPQSourceType;
    MS_PQ_EX_Mode_Info stPQModeInfo;
    MS_U16 u16ratio;
} PQ_EX_ADC_SAMPLING_INFO;

//Display information
typedef struct
{
    MS_U32 VDTOT; //Output vertical total
    MS_U32 DEVST; //Output DE vertical start
    MS_U32 DEVEND;//Output DE Vertical end
    MS_U32 HDTOT;// Output horizontal total
    MS_U32 DEHST; //Output DE horizontal start
    MS_U32 DEHEND;// Output DE horizontal end
    MS_BOOL bInterlaceMode;
    MS_BOOL bYUVInput;
} XC_EX_DST_DispInfo;

typedef enum
{
    ///IP2 path.
    E_XC_EX_GOP_XCDST_IP2=0,

    /// IP man path.
    E_XC_EX_GOP_XCDST_IP1_MAIN=1,

    ///IP sub path.
    E_XC_EX_GOP_XCDST_IP1_SUB=2,

    /// op1 main path.
    E_XC_EX_GOP_XCDST_OP1_MAIN=3,

    E_XC_EX_MAX_GOP_XCDST_SUPPORT

} XC_EX_GOP_XCDST_TYPE;

/// Set data mux to VE
typedef enum
{
    /// GOP mux0 to VE
    E_XC_EX_VOP_SEL_OSD_BLEND0,
    /// GOP mux1 to VE
    E_XC_EX_VOP_SEL_OSD_BLEND1,
    /// GOP mux2 to VE
    E_XC_EX_VOP_SEL_OSD_BLEND2,
    /// mux from XC MACE
    E_XC_EX_VOP_SEL_MACE_RGB,

    E_XC_EX_VOP_SEL_OSD_NONE
} XC_EX_VOP_SEL_OSD_XC2VE_MUX;

// 3D info
typedef enum
{
    //range [0000 ~ 1111] reserved for hdmi 3D spec
    E_XC_EX_3D_INPUT_FRAME_PACKING                     = 0x00, //0000
    E_XC_EX_3D_INPUT_FIELD_ALTERNATIVE                 = 0x01, //0001
    E_XC_EX_3D_INPUT_LINE_ALTERNATIVE                  = 0x02, //0010
    E_XC_EX_3D_INPUT_SIDE_BY_SIDE_FULL                 = 0x03, //0011
    E_XC_EX_3D_INPUT_L_DEPTH                           = 0x04, //0100
    E_XC_EX_3D_INPUT_L_DEPTH_GRAPHICS_GRAPHICS_DEPTH   = 0x05, //0101
    E_XC_EX_3D_INPUT_TOP_BOTTOM                        = 0x06, //0110
    E_XC_EX_3D_INPUT_SIDE_BY_SIDE_HALF                 = 0x08, //1000

    E_XC_EX_3D_INPUT_CHECK_BORAD                       = 0x09, //1001

    //user defined
    E_XC_EX_3D_INPUT_MODE_USER                         = 0x10,
    E_XC_EX_3D_INPUT_MODE_NONE                         = E_XC_EX_3D_INPUT_MODE_USER,
    E_XC_EX_3D_INPUT_FRAME_ALTERNATIVE,
    E_XC_EX_3D_INPUT_SIDE_BY_SIDE_HALF_INTERLACE,
    // optimize for format: in:E_XC_3D_INPUT_FRAME_PACKING, out:E_XC_3D_OUTPUT_TOP_BOTTOM,E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF
    E_XC_EX_3D_INPUT_FRAME_PACKING_OPT,
    // optimize for format: in:E_XC_3D_INPUT_TOP_BOTTOM, out:E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF
    E_XC_EX_3D_INPUT_TOP_BOTTOM_OPT,
    E_XC_EX_3D_INPUT_NORMAL_2D,
    E_XC_EX_3D_INPUT_NORMAL_2D_INTERLACE,
    E_XC_EX_3D_INPUT_NORMAL_2D_INTERLACE_PTP,
    E_XC_EX_3D_INPUT_SIDE_BY_SIDE_HALF_INTERLACE_OPT,
    E_XC_EX_3D_INPUT_NORMAL_2D_HW,  //for hw 2D to 3D use
    E_XC_EX_3D_INPUT_PIXEL_ALTERNATIVE,
} XC_EX_3D_INPUT_MODE;


typedef enum
{
    E_XC_EX_3D_OUTPUT_MODE_NONE,
    E_XC_EX_3D_OUTPUT_LINE_ALTERNATIVE ,
    E_XC_EX_3D_OUTPUT_TOP_BOTTOM,
    E_XC_EX_3D_OUTPUT_SIDE_BY_SIDE_HALF,
    E_XC_EX_3D_OUTPUT_FRAME_ALTERNATIVE,       //25-->50,30-->60,24-->48,50-->100,60-->120----FRC 1:2
    E_XC_EX_3D_OUTPUT_FRAME_L,
    E_XC_EX_3D_OUTPUT_FRAME_R,
    E_XC_EX_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC,  //50->50, 60->60-------------------------------FRC 1:1
    E_XC_EX_3D_OUTPUT_CHECKBOARD_HW,       //for hw 2d to 3d use
    E_XC_EX_3D_OUTPUT_LINE_ALTERNATIVE_HW,  //for hw 2d to 3d use
    E_XC_EX_3D_OUTPUT_PIXEL_ALTERNATIVE_HW, //for hw 2d to 3d use
    E_XC_EX_3D_OUTPUT_FRAME_L_HW,          //for hw 2d to 3d use
    E_XC_EX_3D_OUTPUT_FRAME_R_HW,          //for hw 2d to 3d use
    E_XC_EX_3D_OUTPUT_FRAME_ALTERNATIVE_HW, //for hw 2d to 3d use
    E_XC_EX_3D_OUTPUT_TOP_BOTTOM_HW,       //for hw 2d to 3d use, it based on E_XC_3D_OUTPUT_TOP_BOTTOM implement
    E_XC_EX_3D_OUTPUT_SIDE_BY_SIDE_HALF_HW, //for hw 2d to 3d use, it based on E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF implement
    E_XC_EX_3D_OUTPUT_FRAME_PACKING,
} XC_EX_3D_OUTPUT_MODE;

typedef enum
{
    E_XC_EX_3D_OUTPUT_FI_MODE_NONE ,
    E_XC_EX_3D_OUTPUT_FI_1920x1080 ,
    E_XC_EX_3D_OUTPUT_FI_960x1080  ,
    E_XC_EX_3D_OUTPUT_FI_1920x540  ,

    E_XC_EX_3D_OUTPUT_FI_1280x720  ,
} XC_EX_3D_OUTPUT_FI_MODE;

typedef enum
{
    E_XC_EX_3D_AUTODETECT_SW,
    E_XC_EX_3D_AUTODETECT_HW,
    E_XC_EX_3D_AUTODETECT_HW_COMPATIBLE,
    E_XC_EX_3D_AUTODETECT_MAX
} XC_EX_3D_AUTODETECT_METHOD;

typedef enum
{
    E_XC_EX_3D_PANEL_NONE,
    E_XC_EX_3D_PANEL_SHUTTER,      //240hz panel, which can process updown, leftright,vertical or horizontal line weave
    E_XC_EX_3D_PANEL_PELLICLE,     //120hz panel, which can only process horizontal line weave
    E_XC_EX_3D_PANEL_4K1K_SHUTTER, //120hz 4K1K panel, which can process updown, leftright,vertical or horizontal line weave
    E_XC_EX_3D_PANEL_MAX,
} XC_EX_3D_PANEL_TYPE;

//hw 2d to 3d para
typedef struct
{
    MS_U32  u32Hw2dTo3dPara_Version;
    MS_U16  u16Concave;
    MS_U16  u16Gain;
    MS_U16  u16Offset;
    MS_U16  u16ArtificialGain;
    MS_U16  u16EleSel;
    MS_U16  u16ModSel;
    MS_U16  u16EdgeBlackWidth;
} XC_EX_3D_HW2DTO3D_PARA;

//detect 3d format para
typedef struct
{
    MS_U32  u32Detect3DFormatPara_Version;  //version control, back compatible
//////////////////obsolete field begin///////////////////////////////////////////////////////////////////////////////////////////////////////////
    MS_U16  u16HorSearchRange;              //the horizontal range for find the similar pixel at R image
    MS_U16  u16VerSearchRange;              //the vertical range for find the similar pixel at R image
    MS_U16  u16GYPixelThreshold;            //g/y pixel threshold for define the similar pixel
    MS_U16  u16RCrPixelThreshold;           //r/cr pixel threshold for define the similar pixel
    MS_U16  u16BCbPixelThreshold;           //b/cb pixel threshold for define the similar pixel
    MS_U16  u16HorSampleCount;              //the horizontal sample count, the total checked pixel will be u16HorSampleCount*u16VerSampleCount
    MS_U16  u16VerSampleCount;              //the vertical sample count, the total checked pixel will be u16HorSampleCount*u16VerSampleCount
    MS_U16  u16MaxCheckingFrameCount;       //the max checking frame count
    MS_U16  u16HitPixelPercentage;          //the percentage about hit pixel in one frame total checked pixel, for example: 70%, need set as 70
//////////////////obsolete field end/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    MS_BOOL bEnableOverscan;                //detect 3d format for considering overscan shift
} XC_EX_3D_DETECT3DFORMAT_PARA;

//define 3d fp info para
typedef struct
{
    MS_U32  u32FPInfoPara_Version;          //version control, back compatible
    MS_U16  u16HBlank;                      //horizontal blank
    MS_BOOL bEnableUserSetting;             //enable user setting
} XC_EX_3D_FPINFO_PARA;

typedef enum
{
    E_XC_EX_DBG_FPLL_MODE_DISABLE_ALL = 0,
    E_XC_EX_DBG_FPLL_MODE_DISABLE     = 1,
    E_XC_EX_DBG_FPLL_MODE_ENABLE      = 2,
    E_XC_EX_DBG_FPLL_MODE_MAX,
} XC_EX_FPLL_DBG_MODE;//For debug purpose only!

typedef enum
{
    E_XC_EX_DBG_FPLL_FLAG_PHASELIMIT  = 0,
    E_XC_EX_DBG_FPLL_FLAG_D5D6D7      = 1,
    E_XC_EX_DBG_FPLL_FLAG_IGAIN       = 2,
    E_XC_EX_DBG_FPLL_FLAG_PGAIN       = 3,
    E_XC_EX_DBG_FPLL_FLAG_INITSETSTEP = 4,
    E_XC_EX_DBG_FPLL_FLAG_INITSETDELAY= 5,
    E_XC_EX_DBG_FPLL_FLAG_MAX,
} XC_EX_FPLL_DBG_FLAG;//For debug purpose only!

typedef enum
{
    E_XC_EX_FPLL_MODE_DISABLE_ALL = 0, /// Disable all current FPLL customer setting(then scaler will auto decide it)
    E_XC_EX_FPLL_MODE_DISABLE     = 1, /// Disable the specified(by other function parameter) FPLL customer setting
    E_XC_EX_FPLL_MODE_ENABLE      = 2, /// Enable the specified(by other function parameter) FPLL customer setting
    E_XC_EX_FPLL_MODE_MAX,
} XC_EX_FPLL_MODE;

typedef enum
{
    E_XC_EX_FPLL_FLAG_PHASELIMIT  = 0, ///Set customer setting of PHASE limit
    E_XC_EX_FPLL_FLAG_D5D6D7      = 1,///Set customer setting of D5D6D7 limit
    E_XC_EX_FPLL_FLAG_IGAIN       = 2,///Set customer setting of IGAIN
    E_XC_EX_FPLL_FLAG_PGAIN       = 3,///Set customer setting of PGAIN
    E_XC_EX_FPLL_FLAG_INITSETSTEP = 4, ///steps to set DCLK
    E_XC_EX_FPLL_FLAG_INITSETDELAY= 5, ///delay between steps when setting DCLK
    E_XC_EX_FPLL_FLAG_MAX,
} XC_EX_FPLL_FLAG;

typedef enum
{
    E_XC_EX_MLOAD_UNSUPPORTED = 0,
    E_XC_EX_MLOAD_DISABLED    = 1,
    E_XC_EX_MLOAD_ENABLED     = 2,
} XC_EX_MLOAD_TYPE;

typedef enum
{
    E_XC_EX_MLG_UNSUPPORTED = 0,
    E_XC_EX_MLG_DISABLED    = 1,
    E_XC_EX_MLG_ENABLED     = 2,
} XC_EX_MLG_TYPE;

typedef enum
{
    E_XC_EX_HDMI_SYNC_DE,
    E_XC_EX_HDMI_SYNC_HV,
} XC_EX_HDMI_SYNC_TYPE;

typedef enum
{
    E_XC_EX_FRC_1_1  = 0,
    E_XC_EX_FRC_1_2  = 1,
    E_XC_EX_FRC_5_12 = 2,
    E_XC_EX_FRC_2_5  = 3,
    E_XC_EX_FRC_1_4  = 4,
} XC_EX_FRC_TYPE;

// scaler FRC table
typedef struct
{
    MS_U16 u16LowerBound;
    MS_U16 u16HigherBound;
    MS_U8  u8FRC_In:4;          // ivs
    MS_U8  u8FRC_Out:4;         // ovs
    XC_EX_FRC_TYPE eFRC_Type;
} XC_EX_FRC_SETTING;

typedef enum
{
    E_PQ_ex_IOCTL_GET_HSD_SAMPLING,
    E_PQ_ex_IOCTL_MAX,
} E_PQ_ex_IOCTL_FLAG;


typedef enum
{
    E_XC_EX_GET_PIXEL_RET_FAIL = 0,       ///<Fail
    E_XC_EX_GET_PIXEL_RET_OK,             ///<OK
    E_XC_EX_GET_PIXEL_RET_OUT_OF_RANGE,   ///< out of range
} XC_EX_GET_PixelRGB_ReturnValue;


typedef enum
{
    E_XC_EX_GET_PIXEL_STAGE_AFTER_DLC = 0x01,
    E_XC_EX_GET_PIXEL_STAGE_PRE_GAMMA = 0x02,
    E_XC_EX_GET_PIXEL_STAGE_AFTER_OSD = 0x03,
    E_XC_EX_GET_PIXEL_STAGE_MAX       = 0xFF,
} XC_EX_GET_PIXEL_RGB_STAGE;

typedef struct
{
    XC_EX_GET_PIXEL_RGB_STAGE enStage;
    MS_U16 u16x;
    MS_U16 u16y;
    MS_U32 u32r;
    MS_U32 u32g;
    MS_U32 u32b;
} XC_EX_Get_Pixel_RGB;

typedef struct
{
    MS_U32 u32ReportPixelInfo_Version;   ///<Input: Version of current structure. Please always set to "XC_EX_REPORT_PIXELINFO_VERSION" as input
    MS_U16 u16ReportPixelInfo_Length;    ///<Input: Length of this structure, u16ReportPixelInfo_Length=sizeof(MS_XC_REPORT_PIXELINFO)
    XC_EX_GET_PIXEL_RGB_STAGE enStage;   ///<Input: Pixel info report stage
    MS_U16 u16RepWinColor;               ///<Input:Report window Color
    MS_U16 u16XStart;                    ///<Input: X start location of report window
    MS_U16 u16XEnd;                      ///<Input: X end location of report window
    MS_U16 u16YStart;                    ///<Input: Y start location of report window
    MS_U16 u16YEnd;                      ///<Input: Y end location of report window
    MS_U16 u16RCrMin;                    ///<Output:R or Cr min value
    MS_U16 u16RCrMax;                    ///<Output:R or Cr max value
    MS_U16 u16GYMin;                     ///<Output:G or Y min value
    MS_U16 u16GYMax;                     ///<Output:G or Y max value
    MS_U16 u16BCbMin;                    ///<Output:B or Cb min value
    MS_U16 u16BCbMax;                    ///<Output:B or Cb max value
    MS_U32 u32RCrSum;                    ///<Output:R or Cr sum value
    MS_U32 u32GYSum;                     ///<Output:G or Y sum value
    MS_U32 u32BCbSum;                    ///<Output:B or Cb sum value
    MS_BOOL bShowRepWin;                 ///<Input: Show report window or not
} XC_EX_REPORT_PIXELINFO;

// scaler interrupt sources
typedef enum
{
    // 0x00, first 4 bits are unused
    E_SC_EX_INT_DIPW = 1,					    //DIPW write one frame done interrupt
    E_SC_EX_INT_START = 4,
    E_SC_EX_INT_RESERVED1 = E_SC_EX_INT_START,  // before is SC_INT_TUNE_FAIL_P, FBL line buffer overrun/underrun
                                                // scaler dosen't have this interrupt now,

    E_SC_EX_INT_VSINT,                          // output Vsync interrupt, can select polarity with BK0_04[1]
    E_SC_EX_INT_F2_VTT_CHG,                     // main window, HDMI mute or Vsync polarity changed, Vtt change exceed BK1_1D[11:8]
    E_SC_EX_INT_F1_VTT_CHG,
    E_SC_EX_INT_F2_VS_LOSE,                     // didn't received Vsync for a while or Vtt count BK1_1F[10:0] exceed max value
    E_SC_EX_INT_F1_VS_LOSE,
    E_SC_EX_INT_F2_JITTER,                      // H/V start/end didn't be the same with privous value, usually used in HDMI/DVI input
    E_SC_EX_INT_F1_JITTER,
    E_SC_EX_INT_F2_IPVS_SB,                     // input V sync interrupt, can select which edge to trigger this interrupt with BK0_04[0]
    E_SC_EX_INT_F1_IPVS_SB,
    E_SC_EX_INT_F2_IPHCS_DET,                   // input H sync interrupt
    E_SC_EX_INT_F1_IPHCS_DET,

    // 0x10
    E_SC_EX_INT_PWM_RP_L_INT,                   // pwm rising edge of left frame
    E_SC_EX_INT_PWM_FP_L_INT,                   // pwm falling edge of left frame
    E_SC_EX_INT_F2_HTT_CHG,                     // Hsync polarity changed or Hperiod change exceed BK1_1D[5:0]
    E_SC_EX_INT_F1_HTT_CHG,
    E_SC_EX_INT_F2_HS_LOSE,                     // didn't received H sync for a while or Hperiod count BK1_20[13:0] exceed max value
    E_SC_EX_INT_F1_HS_LOSE,
    E_SC_EX_INT_PWM_RP_R_INT,                   // pwm rising edge of right frame
    E_SC_EX_INT_PWM_FP_R_INT,                   // pwm falling edge of right frame
    E_SC_EX_INT_F2_CSOG,                        // composite sync or SoG input signal type changed (for example, SoG signal from none -> valid, valid -> none)
    E_SC_EX_INT_F1_CSOG,
    E_SC_EX_INT_F2_RESERVED2,                   // scaler dosen't have this interrupt now, before is SC_INT_F2_ATS_READY
    E_SC_EX_INT_F1_RESERVED2,                   // scaler dosen't have this interrupt now, before is SC_INT_F1_ATS_READY
    E_SC_EX_INT_F2_ATP_READY,                   // auto phase ready interrupt
    E_SC_EX_INT_F1_ATP_READY,
    E_SC_EX_INT_F2_RESERVED3,                   // scaler dosen't have this interrupt now, before is SC_INT_F2_ATG_READY
    E_SC_EX_INT_F1_RESERVED3,                   // scaler dosen't have this interrupt now, before is SC_INT_F1_ATG_READY

    E_SC_EX_MAX_SC_INT,
} SC_EX_INT_SRC;

typedef enum
{
    // 0x00, first 4 bits are unused
    E_XC_EX_INT_RESERVED1 = 4,                  ///< scaler dosen't have this interrupt now
    E_XC_EX_INT_VSINT,                          ///< output Vsync interrupt
    E_XC_EX_INT_F2_VTT_CHG,                     ///< main window, HDMI mute or Vsync polarity changed, Vtt change exceed BK1_1D[11:8]
    E_XC_EX_INT_F1_VTT_CHG,
    E_XC_EX_INT_F2_VS_LOSE,                     ///< didn't received Vsync for a while or Vtt count BK1_1F[10:0] exceed max value
    E_XC_EX_INT_F1_VS_LOSE,
    E_XC_EX_INT_F2_JITTER,                      ///< H/V start/end didn't be the same with privous value, usually used in HDMI/DVI input
    E_XC_EX_INT_F1_JITTER,
    E_XC_EX_INT_F2_IPVS_SB,                     ///< input V sync interrupt
    E_XC_EX_INT_F1_IPVS_SB,
    E_XC_EX_INT_F2_IPHCS_DET,                   ///< input H sync interrupt
    E_XC_EX_INT_F1_IPHCS_DET,

    // 0x10
    E_XC_EX_INT_PWM_RP_L_INT,                   ///< pwm rising edge of left frame, please use MDrv_XC_InterruptAvaliable() to check if avalible or not
    E_XC_EX_INT_PWM_FP_L_INT,                   ///< pwm falling edge of left frame, please use MDrv_XC_InterruptAvaliable() to check if avalible or not
    E_XC_EX_INT_F2_HTT_CHG,                     ///< Hsync polarity changed or Hperiod change exceed BK1_1D[5:0]
    E_XC_EX_INT_F1_HTT_CHG,
    E_XC_EX_INT_F2_HS_LOSE,                     ///< didn't received H sync for a while or Hperiod count BK1_20[13:0] exceed max value
    E_XC_EX_INT_F1_HS_LOSE,
    E_XC_EX_INT_PWM_RP_R_INT,                   ///< pwm rising edge of right frame, please use MDrv_XC_InterruptAvaliable() to check if avalible or not
    E_XC_EX_INT_PWM_FP_R_INT,                   ///< pwm falling edge of right frame, please use MDrv_XC_InterruptAvaliable() to check if avalible or not
    E_XC_EX_INT_F2_CSOG,                        ///< composite sync or SoG input signal type changed (for example, SoG signal from none -> valid, valid -> none)
    E_XC_EX_INT_F1_CSOG,
    E_XC_EX_INT_F2_RESERVED2,                   ///< scaler dosen't have this interrupt now
    E_XC_EX_INT_F1_RESERVED2,
    E_XC_EX_INT_F2_ATP_READY,                   ///< auto phase ready interrupt
    E_XC_EX_INT_F1_ATP_READY,
    E_XC_EX_INT_F2_RESERVED3,                   ///< scaler dosen't have this interrupt now
    E_XC_EX_INT_F1_RESERVED3,
} XC_EX_INT_SRC;

/// OP2 Video/GOP layer switch
typedef enum
{
    E_XC_EX_VOP_LAYER_VIDEO_MUX1_MUX2 = 0,        ///<0: Video->GOP1->GOP2 (GOP2 is one pipe later than GOP1)
    E_XC_EX_VOP_LAYER_FRAME_VIDEO_MUX1_MUX2,      ///<1: FrameColor->Video->GOP1->GOP2 (GOP1/GOP2 smae pipe)
    E_XC_EX_VOP_LAYER_FRAME_VIDEO_MUX2_MUX1,      ///<2: FrameColor->Video->GOP2->GOP1 (GOP1/GOP2 smae pipe)
    E_XC_EX_VOP_LAYER_FRAME_MUX1_VIDEO_MUX2,      ///<3: FrameColor->GOP1->Video->GOP2 (GOP1/GOP2 smae pipe)
    E_XC_EX_VOP_LAYER_FRAME_MUX1_MUX2_VIDEO,      ///<4: FrameColor->GOP1->GOP2->Video (GOP1/GOP2 smae pipe)
    E_XC_EX_VOP_LAYER_FRAME_MUX2_VIDEO_MUX1,      ///<5: FrameColor->GOP2->Video->GOP1 (GOP1/GOP2 smae pipe)
    E_XC_EX_VOP_LAYER_FRAME_MUX2_MUX1_VIDEO,      ///<6: FrameColor->GOP2->GOP1->Video (GOP1/GOP2 smae pipe)
    E_XC_EX_VOP_LAYER_RESERVED,
} XC_EX_VOP_OSD_LAYER_SEL;

/// OP2VOP de select
typedef enum
{
    E_XC_EX_OP2VOPDE_MAINWINDOW = 0,  ///<0: capture main display window, no osd
    E_XC_EX_OP2VOPDE_SUBWINDOW,       ///<1: capture sub display window, no osd
    E_XC_EX_OP2VOPDE_WHOLEFRAME,      ///<2: Whole frame of panel DE, no osd
    E_XC_EX_OP2VOPDE_WHOLEFRAME_WITHOSD, ///<3: Whole frame of panel DE, with osd
} XC_EX_OP2VOP_DE_SEL;

typedef void (*SC_EX_InterruptCb) (SC_EX_INT_SRC enIntNum, void *pParam);               ///< Interrupt callback function


//Define Output Frame control
typedef struct
{
    MS_U32 u32XC_version;    ///<Version of current structure.
    MS_U16  u16InVFreq;      ///<input V frequency
    MS_U16  u16OutVFreq;     ///<output V frequncy
    MS_BOOL bInterlace;      ///<whether it's interlace

} XC_EX_OUTPUTFRAME_Info;

/// Define XC Init MISC
/// please enum use BIT0 = 1, BIT1 = 2, BIT3 = 4
typedef enum
{
    E_XC_EX_INIT_MISC_A_NULL = 0,
    E_XC_EX_INIT_MISC_A_IMMESWITCH = 1,
    E_XC_EX_INIT_MISC_A_IMMESWITCH_DVI_POWERSAVING = 2,
    E_XC_EX_INIT_MISC_A_DVI_AUTO_EQ = 4,

    E_XC_EX_INIT_MISC_A_FRC_INSIDE = 8,
    E_XC_EX_INIT_MISC_A_OSD_TO_HSLVDS = 0x10,
    E_XC_EX_INIT_MISC_A_FRC_INSIDE_60HZ = 0x20, // for 60Hz FRC case
    E_XC_EX_INIT_MISC_A_FRC_INSIDE_240HZ = 0x40, // for 240Hz FRC case
} XC_EX_INIT_MISC_A;


/// Define the initial MISC for XC
typedef struct
{
    MS_U32 u32XCMISC_version;                   ///<Version of current structure.
    MS_U32 u32MISC_A;
    MS_U32 u32MISC_B;
    MS_U32 u32MISC_C;
    MS_U32 u32MISC_D;
} XC_EX_INITMISC;

typedef enum
{
    E_XC_EX_FLOCK_DIV_OFF = 0,
    E_XC_EX_FLOCK_DIV_ON,
    E_XC_EX_FLOCK_FPLL_ON,

} XC_EX_FLOCK_TYPE;

typedef struct
{
    // memory
    MS_U32 u32FRC_MEMC_MemAddr;
    MS_U32 u32FRC_MEMC_MemSize;
    MS_U32 u32FRC_OD_MemAddr;
    MS_U32 u32FRC_OD_MemSize;
    MS_U32 u32FRC_LD_MemAddr;
    MS_U32 u32FRC_LD_MemSize;
    MS_U32 u32FRC_ME1_MemAddr;
    MS_U32 u32FRC_ME1_MemSize;
    MS_U32 u32FRC_ME2_MemAddr;
    MS_U32 u32FRC_ME2_MemSize;
    MS_U32 u32FRC_2D3D_Render_MemAddr;
    MS_U32 u32FRC_2D3D_Render_MemSize;
    MS_U32 u32FRC_2D3D_Render_Detection_MemAddr;
    MS_U32 u32FRC_2D3D_Render_Detection_MemSize;
    MS_U32 u32FRC_Halo_MemAddr;
    MS_U32 u32FRC_Halo_MemSize;
    MS_U32 u32FRC_R2_MemAddr;
    MS_U32 u32FRC_R2_MemSize;
    MS_U32 u32FRC_ADL_MemAddr;
    MS_U32 u32FRC_ADL_MemSize;

    MS_U32 u32FRC_FrameSize;

    MS_U16 u16FB_YcountLinePitch;
    MS_U16 u16PanelWidth;
    MS_U16 u16PanelHeigh;
    MS_U8 u8FRC3DPanelType;
    MS_U8 u83Dmode;
    MS_U8 u8IpMode;
    MS_U8 u8MirrorMode;
    MS_U8 u83D_FI_out;
    MS_BOOL bFRC;

} XC_EX_FRC_INFO, *p_XC_EX_FRC_INFO;

typedef struct
{
    MS_U32 u32XC_PREINIT_version;           ///<Version of current structure.
    // FRC control info
    XC_EX_FRC_INFO     FRCInfo;

    MS_U16 u16VTrigX;
    MS_U16 u16VTrigY;

    ///////////////////////////////////////////////
    // panel timing spec.
    ///////////////////////////////////////////////
    // sync related
    MS_U8 u8PanelHSyncWidth;                ///<  VOP_01[7:0], PANEL_HSYNC_WIDTH
    MS_U8 u8PanelHSyncBackPorch;            ///<  PANEL_HSYNC_BACK_PORCH, no register setting, provide value for query only

                                            ///<  not support Manuel VSync Start/End now
                                            ///<  VOP_02[10:0] VSync start = Vtt - VBackPorch - VSyncWidth
                                            ///<  VOP_03[10:0] VSync end = Vtt - VBackPorch
    MS_U8 u8PanelVSyncWidth;                ///<  define PANEL_VSYNC_WIDTH
    MS_U8 u8PanelVSyncBackPorch;            ///<  define PANEL_VSYNC_BACK_PORCH

} XC_EX_PREINIT_INFO, *p_XC_EX_PREINIT_INFO;

typedef enum
{
    E_XC_EX_PREINIT_NULL = 0x00,
    E_XC_EX_PREINIT_FRC  = 0x01,

    E_XC_EX_PREINIT_NUM,

} XC_EX_PREINIT;

typedef enum
{
    E_XC_EX_MIRROR_NORMAL,
    E_XC_EX_MIRROR_H_ONLY,
    E_XC_EX_MIRROR_V_ONLY,
    E_XC_EX_MIRROR_HV,
    E_XC_EX_MIRROR_MAX,
} XC_EX_MirrorMode;

typedef enum
{
    E_XC_EX_MEMORY_IP_READ_REQUEST,    ///< memory request for IP read
    E_XC_EX_MEMORY_IP_WRITE_REQUEST,   ///< memory request for IP write
    E_XC_EX_MEMORY_OP_READ_REQUEST,    ///< memory request for OP read
    E_XC_EX_MEMORY_OP_WRITE_REQUEST,   ///< memory request for OP write
    E_XC_EX_MEMORY_REQUEST_MAX,        ///< Invalid request
} XC_EX_MEMORY_REQUEST_TYPE;


/// OP2 Video/GOP layer switch
typedef enum
{
    E_XC_EX_VIDEO_ON_OSD_LAYER_DEAFULT = 0, ///< video -> osd layer 0 -> osd layer 1 -> osd layer 2 -> osd layer 3
    E_XC_EX_VIDEO_ON_OSD_LAYER_0 = 1,       ///< osd layer 0 -> video -> osd layer 1 -> osd layer 2 -> osd layer 3
    E_XC_EX_VIDEO_ON_OSD_LAYER_1 = 2,       ///< osd layer 0 -> osd layer 1 -> video -> osd layer 2 -> osd layer 3
    E_XC_EX_VIDEO_ON_OSD_LAYER_2 = 3,       ///< osd layer 0 -> osd layer 1 -> osd layer 2 -> video -> osd layer 3
    E_XC_EX_VIDEO_ON_OSD_LAYER_3 = 4,       ///< osd layer 0 -> osd layer 1 -> osd layer 2 -> osd layer 3 -> video
    E_XC_EX_VIDEO_ON_OSD_LAYER_NUM,
} XC_EX_VIDEO_ON_OSD_LAYER;

/// Osd Index
typedef enum
{
    E_XC_EX_OSD_0 = 0,       ///< osd0
    E_XC_EX_OSD_1 = 1,       ///< osd1
    E_XC_EX_OSD_2 = 2,       ///< osd2
    E_XC_EX_OSD_3 = 3,       ///< osd3
    E_XC_EX_OSD_NUM,
} E_XC_EX_OSD_INDEX;

/// Osd Index
typedef enum
{
    E_XC_EX_OSD_BlENDING_MODE0 = 0,       ///< a*OSD + (1-a)*Video
    E_XC_EX_OSD_BlENDING_MODE1 = 1,       ///< OSD + (1-a)*Video
    E_XC_EX_OSD_BlENDING_TYPE_NUM,
} XC_EX_OSD_BlENDING_TYPE;

/// Scaling type
typedef enum
{
    E_XC_EX_PRE_SCALING = 0,
    E_XC_EX_POST_SCALING,
    E_XC_EX_BOTH_SCALING,
} XC_EX_SCALING_TYPE;

/// HV Vector type
typedef enum
{
    E_XC_EX_H_VECTOR = 0,
    E_XC_EX_V_VECTOR,
    E_XC_EX_HV_VECTOR,
} XC_EX_VECTOR_TYPE;

/// Define MCDI buffer type
typedef enum
{
    E_XC_EX_MCDI_ME1 = 0,          ///< Main MDCI ME1
    E_XC_EX_MCDI_ME2 = 1,          ///< Main MDCI ME2
    E_XC_EX_MCDI_BOTH,             ///< Main MDCI ME1+ME2
    E_XC_EX_MCDI_SUB_ME1,          ///< Sub MDCI ME1
    E_XC_EX_MCDI_SUB_ME2,          ///< Sub MDCI ME2
    E_XC_EX_MCDI_SUB_BOTH,         ///< Sub MDCI ME1+ME2
} XC_EX_MCDI_TYPE;

typedef struct
{
    MS_U8 p1;
    MS_U8 p2;
    MS_U8 p3;
    MS_U8 p4;
    MS_U8 p5;
    MS_U8 p6;
    MS_U8 p7;
    MS_U8 p8;
} XC_EX_FRC_R2_CMD_PARAMETER, *p_XC_EX_FRC_R2_CMD_PARAMETER;
//LD

typedef enum
{
    E_XC_EX_LD_PANEL_LG32inch_LR10 = 0x0,
    E_XC_EX_LD_PANEL_LG37inch_LR10 = 0x1,
    E_XC_EX_LD_PANEL_LG42inch_LR16 = 0x2,
    E_XC_EX_LD_PANEL_LG47inch_LR16 = 0x3,
    E_XC_EX_LD_PANEL_LG55inch_LR16 = 0x4,
    E_XC_EX_LD_PANEL_LG55inch_LR12 = 0x5,
    E_XC_EX_LD_PANEL_CMO42inch_LR16 = 0x6,
    E_XC_EX_LD_PANEL_DEFAULT,
    E_XC_EX_LD_PANEL_NUMS,
} XC_EX_LD_PANEL_TYPE;

typedef enum
{
    E_XC_EX_LD_MODE_OFF  = 0,
    E_XC_EX_LD_MODE_LOW  = 1,
    E_XC_EX_LD_MODE_MID  = 2,
    E_XC_EX_LD_MODE_HIGH = 3,
} XC_EX_LD_MODE;

//parameters for detecting nine lattice
typedef struct
{
    MS_U16 u16PixelStep;        // distance between sample points
    MS_U8  u8ColorThreshold;    // max color difference
    MS_U8  u8TryTimes;          // max times for detecting
    MS_U16 u16LinearDiff;       // difference for every 3 lattice in a line
} XC_EX_DETECTNL_PARA;

#define XC_EX_FRC_PATHCTRL_ALLOFF            (0x0000)
#define XC_EX_FRC_PATHCTRL_OP2COLORMATRIX    (0x0001)
#define XC_EX_FRC_PATHCTRL_OP2CSCDITHER      (0x0002)
#define XC_EX_FRC_PATHCTRL_OP2BRIGHTNESS     (0x0004)
#define XC_EX_FRC_PATHCTRL_OP2CONTRAST       (0x0008)
#define XC_EX_FRC_PATHCTRL_OP2NOISEROUND     (0x0010)

// OSDC TIMING GEN
typedef struct
{
    MS_U16 u16OC_Tgen_HTotal;
    MS_U16 u16OC_Tgen_VTotal;

    MS_U16 u16OC_Tgen_Hsync_Start;
    MS_U16 u16OC_Tgen_Hsync_End;
    MS_U16 u16OC_Tgen_HframDE_Start;
    MS_U16 u16OC_Tgen_HframDE_End;

    MS_U16 u16OC_Tgen_Vsync_Start;
    MS_U16 u16OC_Tgen_Vsync_End;
    MS_U16 u16OC_Tgen_VframDE_Start;
    MS_U16 u16OC_Tgen_VframDE_End;
} XC_EX_OSDC_TGEN_INFO;

// OSDC MISC Control
typedef struct
{
    MS_BOOL bOC_ClK_En;
    MS_BOOL bOC_Mixer_Bypass_En;
    MS_BOOL bOC_Mixer_InvAlpha_En;
    MS_BOOL bOC_Mixer_Hsync_Vfde_Out;    // 1:hs_out = hs&vfde
    MS_BOOL bOC_Mixer_Hfde_Vfde_Out;     // 1:hs_out = de(hfde)&vfde
    MS_U16  u16OC_Lpll_type;
    MS_U8   u8OC_OutputFormat;           // output bit order
} XC_EX_OSDC_CTRL_INFO;

typedef enum
{
    E_XC_EX_OSDC_TGEN_MANUAL   = 0,
    E_XC_EX_OSDC_TGEN_1366x768,
    E_XC_EX_OSDC_TGEN_1920x1080,
    E_XC_EX_OSDC_TGEN_3840x2160,

    E_XC_EX_OSDC_TGEN_MAX,
} XC_EX_OSDC_TGEN_Type;

typedef enum
{
    E_XC_EX_OSDC_INIT   = 0,
    E_XC_EX_OSDC_CTRL_TGEN,
    E_XC_EX_OSDC_CTRL_MISC,

} XC_EX_OSDC_CTRL_TYPE;

//OSDC Display information
typedef struct
{
    MS_U32 ODSC_DISPInfo_Version;   ///<Version of current structure. Please always set to "u32Osdc_dispinfo_Version" as input

    MS_U32 VDTOT;      //Output vertical total
    MS_U32 DEVST;      //Output DE Vertical start
    MS_U32 DEVEND;     //Output DE Vertical end
    MS_U32 HDTOT;      // Output horizontal total
    MS_U32 DEHST;      //Output DE horizontal start
    MS_U32 DEHEND;     // Output DE horizontal end

    MS_U32 SYNCHST;
    MS_U32 SYNCHEND;
    MS_U32 SYNCVST;
    MS_U32 SYNCVEND;

    MS_BOOL bCLK_EN;                // OUTPUT ENABLE
    MS_BOOL bMIXER_BYPASS_EN;   // MIXER BYPASS ENABLE
    MS_BOOL bMIXER_INVALPHA_EN;
    MS_BOOL bMIXER_HSTVFDEOUT_EN;// 1:hs_out = hs&vfde
    MS_BOOL bMIXER_HFDEVFDEOUT_EN;// 1:hs_out = de(hfde)&vfde

} XC_EX_OSDC_DST_DispInfo;

//select the input for bypass mode.
typedef enum
{
    E_XC_EX_BYPASS_HDMI   = 0,
    E_XC_EX_BYPASS_DC_MAIN,
    E_XC_EX_BYPASS_DC_SUB,
}XC_EX_BYPASS_InputSource;


// For HW internal test pattern
typedef enum
{
    E_XC_EX_OP1_PATGEN_DISP_LB_MODE,   // pattern gen on display line buffer, can't support post-sclaing
    E_XC_EX_OP1_PATGEN_OPM_MODE,       // pattern gen before post scaling engine, can support post-scaling, but not implement now
}XC_EX_OP1_PATGEN_MODE;

typedef enum{
    E_XC_EX_OP1_PATTERN_OFF = 0,
    E_XC_EX_OP1_WB_PATTERN,                        // 1:
    E_XC_EX_OP1_PURE_RED_PATTERN,                  // 2: red
    E_XC_EX_OP1_PURE_GREEN_PATTERN,                // 3: green
    E_XC_EX_OP1_PURE_BLUE_PATTERN,                 // 4: blue
    E_XC_EX_OP1_PURE_WHITE_PATTERN,                // 5: white
    E_XC_EX_OP1_PURE_BLACK_PATTERN,                // 6: black
    E_XC_EX_OP1_PURE_GREY_PATTERN,                 // 7: gray
    E_XC_EX_OP1_PURE_COLOR_V_BAR_PATTERN,          // 8: vertical color-bar
    E_XC_EX_OP1_PURE_COLOR_H_BAR_PATTERN,          // 9: horizontal color-bar
    E_XC_EX_OP1_PURE_GREY_BAR_16_PATTERN,          // 10: 16 vertical gray-bar
    E_XC_EX_OP1_PURE_GREY_BAR_32_PATTERN,          // 11: 32 vertical gray-bar
    E_XC_EX_OP1_PURE_GREY_BAR_64_PATTERN,          // 12: 64 vertical gray-bar
    E_XC_EX_OP1_PURE_GREY_RGB_32_PATTERN,          // 13: 32 vertical 4 color bar
    E_XC_EX_OP1_PURE_RGB_CHECKERBOARD_PATTERN,     // 14: 3x3 checkerboard R/B/G
    E_XC_EX_OP1_DOAFADE_GRAY_PATTERN,              // 15: dotfade gary
    E_XC_EX_OP1_CALIBRATION_COLOR_DOTFADE_PATTERN, // 16: checkerboard + dotfade gary
    E_XC_EX_OP1_CALIBRATION_PATTERN,               // 17: checkerboard
    E_XC_EX_OP1_PATTERN_1,                         // 18
    E_XC_EX_OP1_PATTERN_2,                         // 19:
    E_XC_EX_OP1_PATTERN_3,                         // 20: same as pattern2, but not full screen
    E_XC_EX_OP1_3D_PATTERN,                        // 21: side-by-side, if enable 3D effect, can see the word "3D"
    E_XC_EX_OP1_PURE_RED_100IRE_PATTERN,           // 22: red
    E_XC_EX_OP1_PURE_GREEN_100IRE_PATTERN,         // 23: green
    E_XC_EX_OP1_PURE_BLUE_100IRE_PATTERN,          // 24: blue
    E_XC_EX_OP1_PURE_RED_70IRE_PATTERN,            // 25
    E_XC_EX_OP1_PURE_GREEN_70IRE_PATTERN,          // 26
    E_XC_EX_OP1_PURE_BLUE_70IRE_PATTERN,           // 27
    E_XC_EX_OP1_PURE_RED_40IRE_PATTERN,            // 28
    E_XC_EX_OP1_PURE_GREEN_40IRE_PATTERN,          // 29
    E_XC_EX_OP1_PURE_BLUE_40IRE_PATTERN,           // 30
    E_XC_EX_OP1_PURE_RED_20IRE_PATTERN,            // 31
    E_XC_EX_OP1_PURE_GREEN_20IRE_PATTERN,          // 32
    E_XC_EX_OP1_PURE_BLUE_20IRE_PATTERN,           // 33
    E_XC_EX_OP1_PURE_RED_10IRE_PATTERN,            // 34
    E_XC_EX_OP1_PURE_GREEN_10IRE_PATTERN,          // 35
    E_XC_EX_OP1_PURE_BLUE_10IRE_PATTERN,           // 36
    E_XC_EX_OP1_PURE_WHITE_100IRE_PATTERN,         // 37
    E_XC_EX_OP1_PURE_WHITE_90IRE_PATTERN,          // 38
    E_XC_EX_OP1_PURE_WHITE_80IRE_PATTERN,          // 39
    E_XC_EX_OP1_PURE_WHITE_70IRE_PATTERN,          // 40
    E_XC_EX_OP1_PURE_WHITE_60IRE_PATTERN,          // 41
    E_XC_EX_OP1_PURE_WHITE_50IRE_PATTERN,          // 42
    E_XC_EX_OP1_PURE_WHITE_40IRE_PATTERN,          // 43
    E_XC_EX_OP1_PURE_WHITE_30IRE_PATTERN,          // 44
    E_XC_EX_OP1_PURE_WHITE_20IRE_PATTERN,          // 45
    E_XC_EX_OP1_PURE_WHITE_10IRE_PATTERN,          // 46
    E_XC_EX_OP1_PURE_GAMMA_GREY1_PATTERN,          // 47: gray
    E_XC_EX_OP1_PURE_GAMMA_GREY2_PATTERN,          // 48: gray
    E_XC_EX_OP1_PURE_RGB_CHECKERBOARD_PATTERN_2,   // 49: 3x3 checkerboard R/G/B
}XC_EX_OP1_PATTERN;

////////////////////////////////////////////
//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------


//----------------------------
// Must have functions
//----------------------------
//-------------------------------------------------------------------------------------------------
/// Get XC library version
/// @param  ppVersion                  \b OUT: store the version in this member
/// @return @ref XC_EX_RETURN_VALUE
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_GetLibVer(const MSIF_Version **ppVersion);

//-------------------------------------------------------------------------------------------------
/// Get XC Information
/// @return @ref XC_ApiInfo returnthe XC information in this member
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC const XC_EX_ApiInfo * MApi_XC_EX_GetInfo(XC_DEVICE_ID *pDeviceId);

//-------------------------------------------------------------------------------------------------
/// Get XC Status of specific window(Main/Sub)
/// @param  pDrvStatus                  \b OUT: store the status
/// @param  eWindow                     \b IN: which window(Main/Sub) is going to get status
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_GetStatus(XC_DEVICE_ID *pDeviceId, XC_EX_ApiStatus *pDrvStatus, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Extended interface to Get XC Status of specific window(Main/Sub) with version info
/// usage:
///     XC_ApiStatusEx stXCStatus;
///     memset(&stXCStatus, 0, sizeof(XC_ApiStatusEx));
///     stXCStatus.u16ApiStatusEX_Length = sizeof(XC_ApiStatusEx);
///     stXCStatus.u32ApiStatusEx_Version = EX_API_STATUS_EX_VERSION;
///     if(MApi_XC_EX_GetStatusEx(&stXCStatusEx, E_XC_EX_MAIN_WINDOW) == sizeof(XC_ApiStatusEx))
///     {
///           ......
///     }
/// @param  pDrvStatusEx                  \b OUT: store the status
/// @param  eWindow                     \b IN: which window(Main/Sub) is going to get status
/// @return @ref MS_U16 return the copied length of input structure
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U16  MApi_XC_EX_GetStatusEx(XC_DEVICE_ID *pDeviceId, XC_EX_ApiStatusEx *pDrvStatusEx, XC_EX_SCALER_WIN eWindow);

//-------------------------------
// Set Debug Level
// @para  u16DbgSwitch: XC_EX_DBGLEVEL_OFF,XC_EX_DBGLEVEL_SETWINDOW,XC_EX_DBGLEVEL_SETTIMING,XC_EX_DBGLEVEL_SYNCDETECT,XC_EX_DBGLEVEL_MUX
// currently, only used XC_EX_DBGLEVEL_OFF,XC_EX_DBGLEVEL_SETTIMING
//-------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_SetDbgLevel(MS_U16 u16DbgSwitch);

//For debug purpose only!
//-------------------------------
// Set Debug Mode for scaler framelock
// @para DbgMode: Disable/Enable debug
// @para DbgFlag: The debug item
// @para u32Data: The debug data
//-------------------------------
DLL_PUBLIC void    MApi_XC_EX_FPLLDbgMode(XC_DEVICE_ID *pDeviceId, XC_EX_FPLL_DBG_MODE DbgMode, XC_EX_FPLL_DBG_FLAG DbgFlag, MS_U32 u32Data);

//-------------------------------
// Set customer mode for scaler framelock
// @para eMode: Disable/Enable customer mode
// @para eFlag: The customer item
// @para u32Data: The customer data
//-------------------------------
DLL_PUBLIC void    MApi_XC_EX_FPLLCustomerMode(XC_DEVICE_ID *pDeviceId, XC_EX_FPLL_MODE eMode, XC_EX_FPLL_FLAG eFlag, MS_U32 u32Data);

//----------------------------
// Initialize
//----------------------------
DLL_PUBLIC MS_BOOL MDrv_XC_EX_SetIOMapBase(XC_DEVICE_ID *pDeviceId);
//-------------------------------------------------------------------------------------------------

/// Initialize the XC
/// @param  pXC_InitData                  \b IN: the Initialized Data
/// @param  u32InitDataLen                \b IN: the length of the initialized data
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_Init(XC_DEVICE_ID *pDeviceId, XC_EX_INITDATA *pXC_InitData, MS_U32 u32InitDataLen);

//-------------------------------------------------------------------------------------------------
/// Initialize the XC MISC
/// @param  pXC_Init_Misc                   \b IN: the Initialized XC MISC
/// @return E_XC_EX_RET_OK or E_XC_EX_RET_FAIL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_Init_MISC(XC_DEVICE_ID *pDeviceId, XC_EX_INITMISC *pXC_Init_Misc, MS_U32 u32InitMiscDataLen);


//-------------------------------------------------------------------------------------------------
/// Get XC Init MISC Status
/// @param  pXC_Init_Misc                  \b OUT: store the status
/// @return E_XC_EX_RET_OK or E_XC_EX_RET_FAIL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_GetMISCStatus(XC_DEVICE_ID *pDeviceId, XC_EX_INITMISC *pXC_Init_Misc);


//-------------------------------------------------------------------------------------------------
/// Get XC Capability
/// @param  u32Id (you can get detail from E_XC_CAPABILITY enum)
/// @return output data for each query item.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U32  MApi_XC_EX_GetCapability(MS_U32 u32Id);

//-------------------------------------------------------------------------------------------------
/// Get XC Capability 2
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_GetChipCaps(XC_EX_CAPS eCapType, MS_U32* pRet, MS_U32 ret_size);
//-------------------------------------------------------------------------------------------------
/// Exit the XC
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_Exit(XC_DEVICE_ID *pDeviceId);

//-------------------------------
// Set Window & Scaling
//-------------------------------

//-------------------------------------------------------------------------------------------------
/// Set Dynamic Scaling
/// @param  pstDSInfo              \b IN: the information of Dynamic Scaling
/// @param  u32DSInforLen          \b IN: the length of the pstDSInfo
/// @param  eWindow                \b IN: which window we are going to set
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_SetDynamicScaling(XC_DEVICE_ID *pDeviceId, XC_EX_DynamicScaling_Info *pstDSInfo, MS_U32 u32DSInfoLen, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Get Dynamic Scaling Status
/// @return @ref MS_BOOL TRUE: dynamic scaling is enabled; FALSE: dynamic scaling is not enabled.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_GetDynamicScalingStatus(XC_DEVICE_ID *pDeviceId);

//-------------------------------------------------------------------------------------------------
/// Get DNR Base offset
/// @param  eWindow                \b IN: which window we are going to set
/// @return @ref MS_U32 return the DNR Base offset
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U32  MApi_XC_EX_Get_DNRBaseOffset(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Get the FrameStoreNum's factor number, which is usually to calcuate buffer offset
/// @param  eWindow                \b IN: which window we are going to set
/// @return @ref MS_U8 return the store frame number factor
//-------------------------------------------------------------------------------------------------
#define  MApi_XC_EX_Get_StoreFrameNum MApi_XC_EX_Get_FrameNumFactor
DLL_PUBLIC MS_U8   MApi_XC_EX_Get_FrameNumFactor(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Set Pre down scaling minimum size
/// @param  pXCPrescalingLimit     \b IN: the information of Limit size
/// @param  eWindow                \b IN: which window we are going to set
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetPreScalingLimit(XC_DEVICE_ID *pDeviceId, XC_EX_PreScalingLimit_Info *pXCPrescalingLimit, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Set the specific window
/// @param  pstXC_SetWin_Info      \b IN: the information of the window setting
/// @param  u32InitDataLen         \b IN: the length of the pstXC_SetWin_Info
/// @param  eWindow                \b IN: which window we are going to set
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_SetWindow(XC_DEVICE_ID *pDeviceId, XC_EX_SETWIN_INFO *pstXC_SetWin_Info, MS_U32 u32InitDataLen, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Set main and sub window
/// @param  pstXC_SetWin_Info_Main      \b IN: the information of the main window setting
/// @param  pstXC_SetWin_Info_Sub       \b IN: the information of the sub window setting
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_SetDualWindow(XC_DEVICE_ID *pDeviceId, XC_EX_SETWIN_INFO *pstXC_SetWin_Info_Main, XC_EX_SETWIN_INFO *pstXC_SetWin_Info_Sub);

//-------------------------------------------------------------------------------------------------
/// Set the specific window for traveling mode(VE capture function)
/// @param  pstXC_SetWin_Info      \b IN: the information of the window setting
/// @param  u32InitDataLen         \b IN: the length of the pstXC_SetWin_Info
/// @param  eWindow                \b IN: which window we are going to set
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_SetTravelingWindow(XC_DEVICE_ID *pDeviceId, XC_EX_SETWIN_INFO *pstXC_SetWin_Info, MS_U32 u32InitDataLen, XC_EX_SCALER_WIN eWindow);

//-------------------------------
// Mode Related
//-------------------------------
//-------------------------------------------------------------------------------------------------
/// Set input source type
/// @param  enInputSourceType      \b IN: which input source typewe are going to set
/// @param  eWindow                \b IN: which window we are going to set
/// @return void
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetInputSource( XC_DEVICE_ID *pDeviceId, XC_EX_INPUT_SOURCE_TYPE enInputSourceType, XC_EX_SCALER_WIN eWindow );

//-------------------------------------------------------------------------------------------------
/// check whether the specific window is YUV space
/// @param  eWindow                \b IN: which window we are going to set
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_IsYUVSpace(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// check whether specific window is memory format 422
/// @param  eWindow                \b IN: which window we are going to query
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_IsMemoryFormat422(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Enable/Disable force RGB in
/// @param  bEnable                 \b IN: enable or disable
/// @param  eWindow                 \b IN: which window we are going to enable or disable
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_EnableForceRGBin(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Set XC mirror mode for main or sub window
/// @param  eMirrorMode                 \b IN: enable or disable XC mirror mode
/// @param  eWindow                     \b IN: main or sub window
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL    MApi_XC_EX_EnableMirrorModeEx( XC_DEVICE_ID *pDeviceId, XC_EX_MirrorMode eMirrorMode,  XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Get XC mirror mode for main or sub window
/// @param  eWindow                \b IN: main or sub window
/// @return @ref MirrorMode_t
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_MirrorMode MApi_XC_EX_GetMirrorModeTypeEx(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);

//-------------------------------
// Timing detect
//-------------------------------

//-------------------------------------------------------------------------------------------------
/// Get the specific window's sync status
/// @param  eCurrentSrc             \b IN: the current input source
/// @param  sXC_Sync_Status         \b OUT:store the sync status
/// @param  eWindow                 \b IN: which window we are going to get
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_GetSyncStatus(XC_DEVICE_ID *pDeviceId, XC_EX_INPUT_SOURCE_TYPE eCurrentSrc , XC_EX_IP_SYNC_STATUS *sXC_Sync_Status, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// wait for output sync
/// @param  u8NumVSyncs        \b IN: the number of VSync we are going to wait
/// @param  u16Timeout         \b IN: time out
/// @return @ref MS_U8 retun the number of left Vsync if timeout
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U8   MApi_XC_EX_WaitOutputVSync(XC_DEVICE_ID *pDeviceId, MS_U8 u8NumVSyncs, MS_U16 u16Timeout, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// wait for input sync
/// @param  u8NumVSyncs        \b IN: the number of VSync we are going to wait
/// @param  u16Timeout         \b IN: time out
/// @return @ref MS_U8 retun the number of left Vsync if timeout
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U8   MApi_XC_EX_WaitInputVSync(XC_DEVICE_ID *pDeviceId,MS_U8 u8NumVSyncs, MS_U16 u16Timeout, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Set HDMI detect mode. (HDMI has DE  and HV mode. You can set what you want to use.)
/// @param  esynctype        \b IN: HDMI detect mode
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetHdmiSyncMode(XC_EX_HDMI_SYNC_TYPE esynctype);

//-------------------------------------------------------------------------------------------------
/// Set HDMI detect mode. (HDMI has DE  and HV mode. You can set what you want to use.)
/// @return @ref E_HDMI_SYNC_TYPE  Get current HDMI sync type
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_HDMI_SYNC_TYPE MApi_XC_EX_GetHdmiSyncMode(void);

//-------------------------------
// Display control
//-------------------------------
//-------------------------------------------------------------------------------------------------
/// Set report window
/// @param  bEnable        \b IN: enable or disable report window
/// @param  Window         \b IN: the window position and size
/// @param  u8Color        \b IN: report window's color
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetRepWindow(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_WINDOW_TYPE Window, MS_U8 u8Color);

//-------------------------------------------------------------------------------------------------
/// update the OPWriteOff variable status instead of direcly modifying the register itself
/// instead, the state machine will take care of modifying the register by checking this status.
/// @param  bMCNRPQSetting                   \b IN: MCNR PQ status enable or not.
/// @param  eWindow                          \b IN: Main or sub window
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_Set_OPWriteOffEnable(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// update the OPWriteOff variable status, set force flag, and direcly modifying the register
/// @param  bMCNRPQSetting                   \b IN: MCNR PQ status enable or not.
/// @param  eWindow                          \b IN: Main or sub window
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_ForceSet_OPWriteOffEnable(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable , XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// update display window registers with input window
/// @param  eWindow                          \b IN: Main or sub window
/// @param  pdspwin                          \b IN: window info that will be setted to registers
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetDispWinToReg(XC_DEVICE_ID *pDeviceId, XC_EX_WINDOW_TYPE *pstDspwin, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// get current display window registers setting
/// @param  eWindow                          \b IN : Main or sub window
/// @param  pdspwin                          \b OUT: Pointer for ouput disp window register
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_GetDispWinFromReg(XC_DEVICE_ID *pDeviceId, XC_EX_WINDOW_TYPE *pstDspwin, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// let display video freeze by disable scaler buffer write
/// @param  bEnable        \b IN: TRUE: enable, FALSE: otherwise
/// @param  eWindow        \b IN: which window we are going to set
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_FreezeImg(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Query whether the specific window is freeze image status or not
/// @param  eWindow                \b IN: which window we are going to query
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_IsFreezeImg(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// This function will enable/diable output black pattern
/// @param  bEnable      \b IN: TRUE: enable, FALSE: otherwise
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_GenerateBlackVideoForBothWin( XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// This function will enable/diable output black pattern
/// @param  bEnable      \b IN: TRUE: enable, FALSE: otherwise
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_Set_BLSK(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// This function will enable/diable output black pattern
/// @param  bEnable      \b IN: TRUE: enable, FALSE: otherwise
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_GenerateBlackVideo(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Query whether current XC is black video enabled or not
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_IsBlackVideoEnable(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// This function will enable/diable framebufferless mode
/// @param  bEnable      \b IN: TRUE: enable, FALSE: otherwise
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_EnableFrameBufferLess(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Query whether current XC is framebufferless or not
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_IsCurrentFrameBufferLessMode(XC_DEVICE_ID *pDeviceId);


//-------------------------------------------------------------------------------------------------
/// This function will enable/diable request framebufferless mode
/// @param  bEnable      \b IN: TRUE: enable, FALSE: otherwise
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_EnableRequest_FrameBufferLess(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Query whether current XC is request framebufferless or not
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_IsCurrentRequest_FrameBufferLessMode(XC_DEVICE_ID *pDeviceId);

//-------------------------------
// 3D control
//-------------------------------
DLL_PUBLIC MS_U16  MApi_XC_EX_Get_3D_HW_Version(XC_DEVICE_ID *pDeviceId);
DLL_PUBLIC MS_BOOL MApi_XC_EX_Get_3D_IsSupportedHW2DTo3D(XC_DEVICE_ID *pDeviceId);
DLL_PUBLIC MS_BOOL MApi_XC_EX_Set_3D_Mode(XC_DEVICE_ID *pDeviceId,
                            XC_EX_3D_INPUT_MODE e3dInputMode,
                            XC_EX_3D_OUTPUT_MODE e3dOutputMode,
                            XC_EX_3D_PANEL_TYPE e3dPanelType,
                            XC_EX_SCALER_WIN eWindow);
DLL_PUBLIC MS_BOOL MApi_XC_EX_Set_3D_MainWin_FirstMode(XC_DEVICE_ID *pDeviceId, MS_BOOL bMainFirst);
DLL_PUBLIC MS_BOOL MApi_XC_EX_Set_3D_LR_Frame_Exchg(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);
DLL_PUBLIC MS_BOOL MApi_XC_EX_3D_Is_LR_Frame_Exchged(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);
DLL_PUBLIC XC_EX_3D_INPUT_MODE MApi_XC_EX_Get_3D_Input_Mode(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);
DLL_PUBLIC XC_EX_3D_OUTPUT_MODE MApi_XC_EX_Get_3D_Output_Mode(XC_DEVICE_ID *pDeviceId);
DLL_PUBLIC XC_EX_3D_PANEL_TYPE MApi_XC_EX_Get_3D_Panel_Type(XC_DEVICE_ID *pDeviceId);
DLL_PUBLIC MS_BOOL MApi_XC_EX_Get_3D_MainWin_First(XC_DEVICE_ID *pDeviceId);
DLL_PUBLIC MS_BOOL MApi_XC_EX_3DMainSub_IPSync(XC_DEVICE_ID *pDeviceId);
DLL_PUBLIC MS_BOOL MApi_XC_EX_Set_3D_VerVideoOffset(XC_DEVICE_ID *pDeviceId, MS_U16 u163DVerVideoOffset);
DLL_PUBLIC MS_U16  MApi_XC_EX_Get_3D_VerVideoOffset(XC_DEVICE_ID *pDeviceId);
DLL_PUBLIC MS_BOOL MApi_XC_EX_Is3DFormatSupported(XC_DEVICE_ID *pDeviceId,
                                    XC_EX_3D_INPUT_MODE e3dInputMode,
                                    XC_EX_3D_OUTPUT_MODE e3dOutputMode);
DLL_PUBLIC MS_BOOL MApi_XC_EX_Set_3D_HShift(XC_DEVICE_ID *pDeviceId, MS_U16 u16HShift);
DLL_PUBLIC MS_BOOL MApi_XC_EX_Enable_3D_LR_Sbs2Line(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable);
DLL_PUBLIC MS_U16  MApi_XC_EX_Get_3D_HShift(XC_DEVICE_ID *pDeviceId);
DLL_PUBLIC MS_BOOL MApi_XC_EX_Set_3D_HW2DTo3D_Buffer(XC_DEVICE_ID *pDeviceId, MS_PHYADDR u32HW2DTO3D_DD_Buf, MS_PHYADDR u32HW2DTO3D_DR_Buf);
DLL_PUBLIC MS_BOOL MApi_XC_EX_Set_3D_HW2DTo3D_Parameters(XC_DEVICE_ID *pDeviceId, XC_EX_3D_HW2DTO3D_PARA st3DHw2DTo3DPara);
DLL_PUBLIC MS_BOOL MApi_XC_EX_Get_3D_HW2DTo3D_Parameters(XC_DEVICE_ID *pDeviceId, XC_EX_3D_HW2DTO3D_PARA *pst3DHw2DTo3DPara);
DLL_PUBLIC MS_BOOL MApi_XC_EX_Set_3D_Detect3DFormat_Parameters(XC_DEVICE_ID *pDeviceId, XC_EX_3D_DETECT3DFORMAT_PARA *pstDetect3DFormatPara);
DLL_PUBLIC MS_BOOL MApi_XC_EX_Get_3D_Detect3DFormat_Parameters(XC_DEVICE_ID *pDeviceId, XC_EX_3D_DETECT3DFORMAT_PARA *pstDetect3DFormatPara);
DLL_PUBLIC XC_EX_3D_INPUT_MODE MApi_XC_EX_Detect3DFormatByContent(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);
DLL_PUBLIC MS_BOOL MApi_XC_EX_DetectNL(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow, XC_EX_DETECTNL_PARA* pstDetectNLatticePara);
DLL_PUBLIC MS_BOOL MApi_XC_EX_3D_PostPQSetting(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);
DLL_PUBLIC MS_BOOL MApi_XC_EX_Set_3D_FPInfo(XC_DEVICE_ID *pDeviceId, XC_EX_3D_FPINFO_PARA *pstFPInfoPara);
DLL_PUBLIC MS_BOOL MApi_XC_EX_EnableAutoDetect3D(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_3D_AUTODETECT_METHOD enDetectMethod);
DLL_PUBLIC MS_BOOL MApi_XC_EX_GetAutoDetect3DFlag(XC_DEVICE_ID *pDeviceId, XC_EX_3D_AUTODETECT_METHOD *penDetectMethod, MS_BOOL *pbEnable);
DLL_PUBLIC MS_BOOL MApi_XC_EX_Set_3D_SubWinClk(XC_DEVICE_ID *pDeviceId);
//------------------------------------------------------------------------------------------------------
/// Is 3D reg_3dlr_side2line_en enabled or not
/// @return MS_BOOL                  \b OUT: TRUE: enabled FALSE: is not enabled
//------------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_3D_Is_LR_Sbs2Line(XC_DEVICE_ID *pDeviceId);

//-------------------------------------------------------------------------------------------------
/// This function will get the skip status of default flag
/// @return @ref MS_BOOL return the the skip status of default flag
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_SC_EX_3D_Is_Skip_Default_LR_Flag(XC_DEVICE_ID *pDeviceId);

//-------------------------------------------------------------------------------------------------
/// This function will enable/diable skip default LR flag
/// @param  bEnable      \b IN: TRUE: enable, FALSE: otherwise
/// @return @ref MS_BOOL               TRUE: Success, FALSE: Failed
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_3D_Enable_Skip_Default_LR_Flag(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable);

//-------------------------------
// Mux control
//-------------------------------
#define XC_EX_MAX_SYNC_DATA_PATH_SUPPORTED        (6) // (3),3 is not enough, because Main+SUB+Scart 1+Scart 2 =4, but in order to support off-line det + DWIN, modify to 6 first
#define XC_EX_MAX_ASYNC_DATA_PATH_SUPPORTED       (2)
#define XC_EX_MAX_DATA_PATH_SUPPORTED             (XC_EX_MAX_SYNC_DATA_PATH_SUPPORTED+XC_EX_MAX_ASYNC_DATA_PATH_SUPPORTED)

//-------------------------------------------------------------------------------------------------
/// Initialize Mux before using Mux controller
/// @param  input_source_to_input_port      \b IN: a function to map from input source to input port
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_Mux_Init(XC_DEVICE_ID *pDeviceId, void (*input_source_to_input_port)(XC_EX_INPUT_SOURCE_TYPE src_ids , E_MUX_INPUTPORT* port_ids , MS_U8* u8port_count ) );

//-------------------------------------------------------------------------------------------------
/// Monitor the source of Mux
/// @param  bRealTimeMonitorOnly      \b IN: define whether do the monitor routine only for real time
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_Mux_SourceMonitor(XC_DEVICE_ID *pDeviceId, MS_BOOL bRealTimeMonitorOnly);

//-------------------------------------------------------------------------------------------------
/// Create a path in Mux Controller.
/// @param  Path_Info               \b IN: the information of the path
/// @param  u32InitDataLen          \b IN: the length of the Path_Info
/// @return @ref MS_S16 return the path id, or -1 when any error is happened
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_S16  MApi_XC_EX_Mux_CreatePath(XC_DEVICE_ID *pDeviceId, XC_EX_MUX_PATH_INFO* Path_Info, MS_U32 u32InitDataLen);

//-------------------------------------------------------------------------------------------------
/// delete a path from Mux Controller.
/// @param src              \b IN: Type of input source of a path you want to delete
/// @param dest             \b IN: Type of destination of a path you want to delete
/// @return 1 if delete successfuly. Return -1 if delete fail
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_S16  MApi_XC_EX_Mux_DeletePath(XC_DEVICE_ID *pDeviceId, XC_EX_INPUT_SOURCE_TYPE src, XC_EX_DEST_TYPE dest);

//-------------------------------------------------------------------------------------------------
/// A path is disabled after creating it (\ref MApi_XC_EX_Mux_CreatePath)
/// If a path is not enabled,   \ref MApi_XC_Mux_SourceMonitor will bypass it.
/// @param PathId               \b IN: PathId The Path you want to enable
/// @return 1 if enable successfuly. Return -1 if enable fail
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_S16  MApi_XC_EX_Mux_EnablePath(XC_DEVICE_ID *pDeviceId, MS_U16 PathId);

//-------------------------------------------------------------------------------------------------
/// Trigger Sync Event on Mux Controller.
/// The Mux Controller will pass src and *para to each Sync Event Handler (refer synchronous_event_handler of MUX_DATA_PATH also).
///  ( Delegate Function:
///    Send necessary parameter to SyncEventHandler of each synchronous_path which source is 'src' )
/// @param src          \b IN: The input source which triggers Sync Event
/// @param para         \b IN: A pointer points to parameters which need to pass to Event Handler
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_Mux_TriggerPathSyncEvent(XC_DEVICE_ID *pDeviceId, XC_EX_INPUT_SOURCE_TYPE src , void* para);

//-------------------------------------------------------------------------------------------------
/// Set the specific window
/// @param  src             \b IN: the source type for handler
/// @param para         \b IN: A pointer points to parameters which need to pass to Event Handler
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_Mux_TriggerDestOnOffEvent(XC_DEVICE_ID *pDeviceId, XC_EX_INPUT_SOURCE_TYPE src , void* para);

//-------------------------------------------------------------------------------------------------
/// This function was used to enable/disable the destination periodic handler
/// After enabled periodic hander, Mux Controller will pass the parameters to this handler and execute it periodically
/// @param  src             \b IN: the source type for handler
/// @param  bEnable         \b IN: Enable/Disable the priodic handler.
/// @return 1 if successfuly. Return -1 if failed.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_S16  MApi_XC_EX_Mux_OnOffPeriodicHandler(XC_DEVICE_ID *pDeviceId, XC_EX_INPUT_SOURCE_TYPE src, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Get Paths in driver.
/// @param  Paths      \b OUT: Path information
/// @return @ref MS_U8
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U8   MApi_XC_EX_Mux_GetPathInfo(XC_DEVICE_ID *pDeviceId, XC_EX_MUX_PATH_INFO* Paths); // Return current all path info. Max path number is MAX_DATA_PATH_SUPPORTED

//-------------------------------------------------------------------------------------------------
/// Set Support MHL Path Info
/// @param u8MhlSupportInfo               \b IN:  MHL Support Info
///@return @ref MS_BOOL True if query success.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_Mux_SetSupportMhlPathInfo(XC_DEVICE_ID *pDeviceId, MS_U8 u8MhlSupportInfo);

//-------------------------------------------------------------------------------------------------
/// Set MHL Hot Plug Inverse Info
/// @param bIsMhlHotPlugInverse               \b IN:  MHL Hot Plug Inverse Info
///@return @ref MS_BOOL True if query success.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_Mux_SetMhlHotPlugInverseInfo(XC_DEVICE_ID *pDeviceId, MS_BOOL bIsMhlHotPlugInverse);

//-------------------------------------------------------------------------------------------------
/// Get input port from input HDMI source type
/// @param  src                 \b IN: the query based on the input HDMI type
/// @return @ref E_MUX_INPUTPORT
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC E_MUX_INPUTPORT MApi_XC_EX_Mux_GetHDMIPort( XC_DEVICE_ID *pDeviceId, XC_EX_INPUT_SOURCE_TYPE src );

//-------------------------------------------------------------------------------------------------
/// Map input source to VD Ymux port
/// @param  u8InputSourceType      \b IN: input source type
/// @return @ref MS_U8
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U8   MApi_XC_EX_MUX_MapInputSourceToVDYMuxPORT( XC_DEVICE_ID *pDeviceId, XC_EX_INPUT_SOURCE_TYPE u8InputSourceType );

//------------------------------
// PQ related
//------------------------------
DLL_PUBLIC void    MApi_XC_EX_Set_NR(XC_DEVICE_ID *pDeviceId, MS_BOOL bEn, XC_EX_SCALER_WIN eWindow);

DLL_PUBLIC void    MApi_XC_EX_FilmMode_P(XC_DEVICE_ID *pDeviceId);

//-------------------------------------------------------------------------------------------------
/// Check if UC is enabled
/// @param  eWindow      \b IN: which window(main or sub) to get
/// @return MS_BOOL TRUE: UC enabled, FALSE: UC disabled
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_GetUCEnabled(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);

//------------------------------
// Auto related
//------------------------------
DLL_PUBLIC void    MApi_XC_EX_GenSpecificTiming(XC_DEVICE_ID *pDeviceId, XC_EX_Internal_TimingType timingtype);

//------------------------------
// Scaler IP Related
//------------------------------
// DE-Bypass Mode
//-------------------------------------------------------------------------------------------------
/// This function get DE-Bypass Mode
/// @param  eWindow      \b IN: which window(main or sub) to get
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_GetDEBypassMode(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);

// Data enable
//-------------------------------------------------------------------------------------------------
/// This function get DE window
/// @param  psWin        \b OUT: window info to get
/// @param  eWindow      \b IN: which window(main or sub) to get
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_GetDEWindow(XC_DEVICE_ID *pDeviceId, XC_EX_WINDOW_TYPE *psWin, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// This function get DE window in DE ByPass Mode. (T12 / T13 can not support HDMI HV mode. So DE window from BK1 can not be retrieved if set to HV mode.)
/// We Bypass pre-scaling and get H/V size from BK2 MDrv_SC_get_vsd_line_count & MDrv_SC_get_hsd_pixel_count.
/// Prepare this function for using in the feature.
/// @param  psWin        \b OUT: window info to get
/// @param  eWindow      \b IN: which window(main or sub) to get
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_GetDEWidthHeightInDEByPassMode(XC_DEVICE_ID *pDeviceId, MS_U16* pu16Width,MS_U16* pu16Height ,XC_EX_SCALER_WIN eWindow);

//Get Capture Window
//-------------------------------------------------------------------------------------------------
/// Get the capture window for specific window
/// @param  capture_win      \b OUT: the window info to get
/// @param  eWindow          \b IN: which window(main or sub) to get
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_GetCaptureWindow(XC_DEVICE_ID *pDeviceId, XC_EX_WINDOW_TYPE* capture_win, XC_EX_SCALER_WIN eWindow);


//Set Capture Window
//-------------------------------------------------------------------------------------------------
/// Set the Vertical start of capture window for specific window
/// @param  u16Vstart        \b IN: the window info to get
/// @param  eWindow          \b IN: which window(main or sub) to set
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetCaptureWindowVstart(XC_DEVICE_ID *pDeviceId, MS_U16 u16Vstart , XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Set the horizontal start of capture window for specific window
/// @param  u16Hstart        \b IN: the window info to get
/// @param  eWindow          \b IN: which window(main or sub) to set
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetCaptureWindowHstart(XC_DEVICE_ID *pDeviceId, MS_U16 u16Hstart , XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Set the Vertical size of capture window for specific window
/// @param  u16Vsize         \b IN: the window info to get
/// @param  eWindow          \b IN: which window(main or sub) to set
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetCaptureWindowVsize(XC_DEVICE_ID *pDeviceId, MS_U16 u16Vsize , XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Set the Horizontal size of capture window for specific window
/// @param  u16Hsize         \b IN: the window info to get
/// @param  eWindow          \b IN: which window(main or sub) to set
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetCaptureWindowHsize(XC_DEVICE_ID *pDeviceId, MS_U16 u16Hsize , XC_EX_SCALER_WIN eWindow);

// Utility
//-------------------------------------------------------------------------------------------------
/// do the software reset for the specific window
/// @param  u8Reset             \b IN: reset IP @ref SOFTWARE_REST_TYPE_t
/// @param  eWindow             \b IN: which window we are going to set
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SoftwareReset(XC_DEVICE_ID *pDeviceId, MS_U8 u8Reset, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// This function will calculate and return H Frequency x 10
/// @param  u16HPeriod      \b IN: Horizontal period
/// @return MS_U16: H Frequency x 10
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U16  MApi_XC_EX_CalculateHFreqx10(XC_DEVICE_ID *pDeviceId, MS_U16 u16HPeriod);

//-------------------------------------------------------------------------------------------------
/// This function will calculate and return H Frequency x 1000
/// @param  u16HPeriod      \b IN: Horizontal period
/// @return MS_U32: H Frequency x 1000
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U32 MApi_XC_EX_CalculateHFreqx1K(XC_DEVICE_ID *pDeviceId, MS_U16 u16HPeriod);

//-------------------------------------------------------------------------------------------------
/// This function will calculate and return V Frequency x 10
/// @param  u16HFreq      \b IN: Horizontal frequency
/// @param  u16VTotal     \b IN: Vertical Total, usually the scan lines counts of a frame
/// @return MS_U16: V Frequency x 10
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U16  MApi_XC_EX_CalculateVFreqx10(XC_DEVICE_ID *pDeviceId, MS_U16 u16HFreq, MS_U16 u16VTotal);

//-------------------------------------------------------------------------------------------------
/// This function will calculate and return V Frequency x 1000
/// @param  u16HFreq      \b IN: Horizontal frequency
/// @param  u16VTotal     \b IN: Vertical Total, usually the scan lines counts of a frame
/// @return MS_U32: V Frequency x 1000
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U32 MApi_XC_EX_CalculateVFreqx1K(XC_DEVICE_ID *pDeviceId, MS_U32 u16HFreq, MS_U16 u16VTotal);

//-------------------------------------------------------------------------------------------------
/// This function will get V Frequency x 1000
/// @param  eWindow      \b IN: the window we are going to get V frequency
/// @return MS_U32: Accurate V Frequency x 1000
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U32 MApi_XC_EX_GetAccurateVFreqx1K(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Attach a Call back function info Interrupt.
/// @param  eIntNum         \b IN: The interrupt type (@ref SC_INT_SRC)
/// @param  pIntCb           \b IN: Call back function prototype.
/// @param  pParam           \b IN: Parameter for IntCb
/// @return MS_BOOL     True: Success ,   False: Fail
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_InterruptAttach(XC_DEVICE_ID *pDeviceId, SC_EX_INT_SRC enIntNum, SC_EX_InterruptCb pIntCb, void * pParam);

//-------------------------------------------------------------------------------------------------
/// DeAttach a Call back function info Interrupt.
/// @param  eIntNum         \b IN: The interrupt type (@ref SC_INT_SRC)
/// @param  pIntCb           \b IN: Call back function prototype.
/// @param  pParam           \b IN: Parameter for IntCb
/// @return MS_BOOL     True: Success ,   False: Fail
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_InterruptDeAttach(XC_DEVICE_ID *pDeviceId, SC_EX_INT_SRC enIntNum, SC_EX_InterruptCb pIntCb, void * pParam);

//-------------------------------------------------------------------------------------------------
/// This function will disable input source
/// @param  bDisable       \b IN: TRUE : Disable; FALSE: Enable
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_DisableInputSource(XC_DEVICE_ID *pDeviceId, MS_BOOL bDisable, XC_EX_SCALER_WIN eWidnow);

//-------------------------------------------------------------------------------------------------
/// This function will check is input source disabled or not
/// @param  eWindow          \b IN: which window(main or sub) to set
/// @return MS_BOOL     True: inputsource is disabled,   False: inputsource is not disabled
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_IsInputSourceDisabled(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// This function will change panel type dynamically
/// @param  pstPanelInfo      \b IN: the new panel type
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_ChangePanelType(XC_DEVICE_ID *pDeviceId, XC_EX_PANEL_INFO *pstPanelInfo);

//-------------------------------------------------------------------------------------------------
//
// Attention! This function should only be used in the xc interrupt!!!
//
/// This function will tell the current read bank
/// @param  eWindow          \b IN: Window
/// @return  MS_U16   Current read bank
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U16  MApi_XC_EX_GetCurrentReadBank(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
//
// Attention! This function should only be used in the xc interrupt!!!
//
/// This function will tell the current write bank
/// @param  eWindow          \b IN: Window
/// @return  MS_U16   Current write bank
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U16  MApi_XC_EX_GetCurrentWriteBank(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
///  1. calculate H/V pre-scaling down ratio accroding to frame buffer size
///	2. must be called after MApi_XC_SetFrameBufferAddress() and before MApi_XC_EX_SetWindow()
/// @param  bEnable            \b IN: Enable auto pre scaling
/// @param  eWindow          \b IN: Window
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetAutoPreScaling(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
///  Get V sync width of current input source.
/// @param  eWindow            \b IN: The Vsync width of specific window.
/// @return  MS_U8    Sync width of input V sync
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U8   MApi_XC_EX_GetVSyncWidth(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);

//------------------------------------------------------------------------------
/// Set blanding point of GOP in Scaler.
/// @param  MaxGOP          \b IN: The mux number.
/// @param  UseNum            \b IN: GOP selection.
/// @param  u8MuxNum          \b IN: The mux number.
/// @param  bEnable            \b IN: Enable GOP
/// @return  MS_BOOL   TRUE: Success   FALSE: Fail
//------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_set_GOP_Enable(XC_DEVICE_ID *pDeviceId, MS_U8 MaxGOP, MS_U8 UseNum, MS_U8 u8MuxNum, MS_BOOL bEnable);

//------------------------------------------------------------------------------
/// Set blanding point of GOP in Scaler.
/// @param  u8MuxNum          \b IN: The mux number.
/// @param  ipSelGop            \b IN: GOP selection.
//------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_ip_sel_for_gop(XC_DEVICE_ID *pDeviceId, MS_U8 u8MuxNum , XC_EX_IPSEL_GOP ipSelGop);

//------------------------------------------------------------------------------
/// Set Scaler VOP New blending level
//------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetVOPNBL(XC_DEVICE_ID *pDeviceId);

//------------------------------------------------------------------------------
/// XC IP0 Get Destination Information for GOP mixer
/// @return TRUE/FALSE
//------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_GetDstInfo(XC_DEVICE_ID *pDeviceId, XC_EX_DST_DispInfo *pDstInfo, MS_U32 u32SizeofDstInfo, XC_EX_GOP_XCDST_TYPE XCDstType);

//-------------------------------------------------------------------------------------------------
/// Allow decoder to control Field R / W bank status of scaler.
/// @param  u8Enable    \b IN:  True: Decoder can control the R/W bank status. False: Decoder can not control the R/W bank status
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_set_FD_Mask(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Get XC FD_Mask status.
/// @return TRUE/FALSE
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_Get_FD_Mask(XC_DEVICE_ID *pDeviceId);

//-------------------------------------------------------------------------------------------------
/// Allow decoder to control Field R / W bank status of scaler.
/// @param  u8Enable    \b IN:  True: Decoder can control the R/W bank status. False: Decoder can not control the R/W bank status
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_set_FD_Mask_byWin(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Get XC FD_Mask status.
/// @return TRUE/FALSE
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_Get_FD_Mask_byWin(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Set Scaler IP input test pattern.
/// @param  u8Enable    \b IN:  Set 1 to enable. Bit(0) is horizontal pattern and Bit(1) is vertical pattern
/// @param  u6Pattern_type    \b IN:  The pattern type. (the width of each pattern)
/// @param  eWindow    \b IN:  @ref XC_EX_SCALER_WIN
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetIP1TestPattern(XC_DEVICE_ID *pDeviceId, MS_U8 u8Enable, MS_U16 u6Pattern_type, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Auto create input timing. To use this feature, the system must provide clock to scaler.
/// @param  timingtype    \b IN:  the timing type.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_InitIPForInternalTiming(XC_DEVICE_ID *pDeviceId, XC_EX_Internal_TimingType timingtype);

//-------------------------------------------------------------------------------------------------
/// Set Main window IP mux directly.
/// @param  u8Val    \b IN:  The value need to be set into register
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetIPMux(XC_DEVICE_ID *pDeviceId, MS_U8 u8Val);

/// status of input H/V sync
//-------------------------------------------------------------------------------------------------
/// Return true if input H sync of scaler is exist.
/// @param  eWindow    \b IN:  @ref XC_EX_SCALER_WIN
/// @return @ref MS_BOOL   TRUE: Exist  FALSE: not Exist
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_Is_H_Sync_Active(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Return true if input V sync of scaler is exist.
/// @param  eWindow    \b IN:  @ref XC_EX_SCALER_WIN
/// @return @ref MS_BOOL   TRUE: Exist  FALSE: not Exist
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_Is_V_Sync_Active(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// get auto position window with the corresponding valid data threshold
/// @param  u8ValidData                 \b IN: valid data threshold
/// @param  eWindow                     \b IN: which window we are going to get
/// @param  pstAutoPositionWindow       \b OUT: auto position window parameters
/// @return MS_BOOL     TRUE: auto position window is valid     FALSE: auto position window is invalid
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_GetAutoPositionWindow(XC_DEVICE_ID *pDeviceId, MS_U8 u8ValidData, XC_EX_SCALER_WIN eWindow, XC_EX_WINDOW_TYPE *pstAutoPositionWindow);


//------------------------------
// Scaler & Memory
//------------------------------
//-------------------------------------------------------------------------------------------------
/// Set Frame buffer address and size for scaler.
/// @param  u32FBAddress      \b IN:  Start address of frame buffer.
/// @param  u32FBSize    \b IN:  Frame buffer size for Scaler
/// @param  eWindow    \b IN:  @ref XC_EX_SCALER_WIN
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetFrameBufferAddress(XC_DEVICE_ID *pDeviceId, MS_PHYADDR u32FBAddress, MS_PHYADDR u32FBSize, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Check if the buffer size is enough or not.
/// @param  pstXC_SetWin_Info      \b IN:  @ref E_XC_MEMORY_REQUEST_TYPE
/// @param  eWindow    \b IN:  @ref XC_EX_SCALER_WIN
/// @return @ref MS_BOOL   TRUE: Buffer size is enough  FALSE: Buffer is not enough
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_IsFrameBufferEnoughForCusScaling(XC_DEVICE_ID *pDeviceId, XC_EX_SETWIN_INFO *pstXC_SetWin_Info, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Enable or disable scaler memory read/write request
/// @param  bEnable    \b IN:  TURE=Enable memory request of 'eType';  FALSE= Disable memory request of 'eType'
/// @param  eType      \b IN:  @ref E_XC_MEMORY_REQUEST_TYPE
/// @param  eWindow    \b IN:  @ref XC_EX_SCALER_WIN
/// @return @ref XC_EX_RETURN_VALUE
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_SetScalerMemoryRequest(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_MEMORY_REQUEST_TYPE eType, XC_EX_SCALER_WIN eWindow);

//Capture_Memory

//-------------------------------------------------------------------------------------------------
/// Get pixel data specify by u16CorX and  u16CorY.
/// This pixel data is catured after scaler memory (not after OSD or gamma). And it will latch 20ms for retrieving data.
/// Also note the x , y coordinate should be small or equel to input source size. (not panel size)
/// @param  u16CorX    \b IN:  X coordinate
/// @param  u16CorY      \b IN: Y coordinate.
/// @param  eWindow    \b IN:  @ref XC_EX_SCALER_WIN
/// @return void
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_Get_PixelData(XC_DEVICE_ID *pDeviceId, MS_U16 u16CorX,  MS_U16 u16CorY, XC_EX_PIXEL_32BIT* pixel);

//-------------------------------------------------------------------------------------------------
/// calc widht or height based on existed dnr buffer and byte/pixel
/// Fomula : Scaler buffer size / u8FBNum / (byte / pixel) /  InputSize
/// @param  eWindow         \b IN:   The window need to be calc
/// @param  u8FBNum          \b IN:  frame cout
/// @param  u32InputSize    \b IN:  The input source size.
/// @return  MS_U32  The size of frames.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U32  MApi_XC_EX_GetAvailableSize(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow, MS_U8 u8FBNum, MS_U32 u32InputSize);

//------------------------------
// Display & Output
//------------------------------
// Display related

//-------------------------------------------------------------------------------------------------
/// Set Scaler Frame color
/// @param  u32aRGB             \b IN: the 4 bytes in aRGB are "a: no use, R 23:16, G 15:8, B 7:0" (B is in LSB)
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetFrameColor(XC_DEVICE_ID *pDeviceId, MS_U32 u32aRGB);

//-------------------------------------------------------------------------------------------------
/// Set color of main / sub window. This color will be shown when black screen enabled.
/// @param  u8Color             \b IN: format in a byte => R 7:5, G 4:2, B 1:0
/// @param  eWindow             \b IN: The window which need to be set.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetDispWindowColor(XC_DEVICE_ID *pDeviceId, MS_U8 u8Color, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Query the capability of scaler about source to Video encoder(VE)
/// @param  OutputCapability              \b OUT: Which part of scaler can output data to Video Encoder (VE).
///Check E_XC_SOURCE_TO_VE for capability bit. Take an example, if bit0 of OutputCapability equal to 1,
///Scaler can output data to ve from its E_XC_IP(IP)
///@return @ref MS_BOOL True if query success.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_SupportSourceToVE(XC_DEVICE_ID *pDeviceId, MS_U16* pOutputCapability);

//-------------------------------------------------------------------------------------------------
/// Enable output capture for output data to VE. Return False if current platform does not support E_XC_SOURCE_TO_VE
/// Note: this source is not only for VE, but Scaler IP or DIP
/// @param  bEnable              \b IN: Enable output capture function
/// @param  eSourceToVE       \b IN: Specific output source. The source listed in E_XC_SOURCE_TO_VE is a "point" which can be retrieve data.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_SetOutputCapture(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_SOURCE_TO_VE eSourceToVE);

//-------------------------------------------------------------------------------------------------
/// Setup Gamma function ON/OFF
/// @param  bEnable      \b IN: Enable or Disable
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetGammaOnOff (XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Set VOP Gain for Main Window(after 3x3 before Gamma)
/// @param  eVop_Channel                \b IN: Select VOP R/G/B
/// @param  u16Val                           \b IN: Set value
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetPreGammaGain(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow, XC_EX_VOP_CHANNEL eVop_Channel, MS_U16 u16Val);

//-------------------------------------------------------------------------------------------------
/// Set VOP Offset for Main Window(after 3x3 before Gamma)
/// @param  eVop_Channel                \b IN: Select VOP R/G/B
/// @param  u16Val                           \b IN: Set value
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetPreGammaOffset(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow, XC_EX_VOP_CHANNEL eVop_Channel, MS_U16 u16Val);

//-------------------------------------------------------------------------------------------------
// Output timing related
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/// Setup panel timing (output DCLK)/FRC/FramePLL, and enable input source
/// @param  pTimingInfo      \b IN: the information of the timing to set @ref XC_SetTiming_Info
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetPanelTiming(XC_DEVICE_ID *pDeviceId, XC_EX_SetTiming_Info *pTimingInfo, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Set current output type. This is set in Panel structure. You can adjust it here.
/// @param  enPnl_Out_Timing_Mode      \b IN: The output type
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetOutTimingMode(XC_DEVICE_ID *pDeviceId, XC_EX_PNL_OUT_TIMING_MODE enPnl_Out_Timing_Mode);

//-------------------------------------------------------------------------------------------------
/// set free run display window timing
/// @return void Output type.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetFreeRunTiming(XC_DEVICE_ID *pDeviceId);

//-------------------------------------------------------------------------------------------------
/// Adjust V sync FrontPorch , Sync Width for specific output frame rate (You can adjust in advance by using MApi_XC_EX_SetExPanelInfo)
/// @param  u16FrontPorch      \b IN: Front porch of output Vsync
/// @param  u16SyncWidth      \b IN: Sync width of output Vsync
/// @param  u16OutputVfreq      \b IN: The output frame rate you want to adjust.
/// @return MS_BOOL         True: Success False : Fail
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_Set_CustomerSyncInfo(XC_DEVICE_ID *pDeviceId, MS_U16 u16FrontPorch, MS_U16 u16SyncWidth, MS_U16 u16OutputVfreq);

//-------------------------------------------------------------------------------------------------
/// Wait FPLL finished
/// @return @ref MS_BOOL indicate FPLL finished or not (frame lock finished or not)
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_WaitFPLLDone(XC_DEVICE_ID *pDeviceId);

//-------------------------------------------------------------------------------------------------
/// Get scaler output vertical frequency
/// @return @ref MS_U16 return output vertical frequency x 100
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U16  MApi_XC_EX_GetOutputVFreqX100(XC_DEVICE_ID *pDeviceId);

//-------------------------------------------------------------------------------------------------
/// Frame Lock Check
/// @ref MS_BOOL  TURE=Frame Lock ;  FALSE= Not Frame Lock
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_FrameLockCheck(XC_DEVICE_ID *pDeviceId);

//-------------------------------------------------------------------------------------------------
///    Set a customize FRC table into driver
///    You can customize frc table in driver. The max number of FRC setting is 5 (Can be changed in driver layer).
///
///    Here is an example of 5 FRC items with 6 maximal number of FRC setting.
///    Please fill {0xFFFF, 0xFFFF, 1, 1, MS_FRC_1_1} at unused FRC item slot.
///
///    {0, 160, 1, 4, MS_FRC_1_4},          <-- FRC item 0
///    {160, 245, 2, 5, MS_FRC_2_5},       <-- FRC item 1
///    {245, 260, 1, 2, MS_FRC_1_2},       <-- FRC item 2
///    {260, 400, 1, 2, MS_FRC_1_2},       <-- FRC item 3
///    {400, 0xFFFF, 1, 1, MS_FRC_1_1},   <-- FRC item 4
///    {0xFFFF, 0xFFFF, 1, 1, MS_FRC_1_1}  <-- FRC item 5 (Unused)
/// @param  stFRCTable             \b IN: The pointer which point to a FRC table. You can refer above description.
///                                       if pass NULL, driver will use default frc table.
/// @return @ref XC_EX_RETURN_VALUE               Return status.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_CustomizeFRCTable(XC_DEVICE_ID *pDeviceId, XC_EX_FRC_SETTING* stFRCTable);

//-------------------------------------------------------------------------------------------------
/// Set specific in / out framerate control (Using in Box proejct only.)
/// @param  bEnable             \b IN: TRUE: Enable ouput frame control
/// @param  pPanelInfoEx        \b IN: The information about in / out framerate.
/// @param  pPanelInfoEx        \b IN: The window which need to be controlled.
/// @return @ref XC_EX_RETURN_VALUE          return type.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_OutputFrameCtrl(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_OUTPUTFRAME_Info * stOutFrameInfo,XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Set the FPLL mode:
/// @param  bTrue      \b IN: True: FSM mode, False: Non FSM mode
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_SC_EX_Enable_FPLL_FSM(XC_DEVICE_ID *pDeviceId, MS_BOOL bTrue);

//-------------------------------------------------------------------------------------------------
///     This function will force freerun in MDrv_Scaler_SetPanelTiming(),
///     otherwise MDrv_Scaler_SetPanelTiming() will decide to do framelock or not by itself.
///
///     Note: this function is difference with MDrv_SC_set_fpll() which is used to
///       unlock framelock after MDrv_Scaler_SetPanelTiming().
///       But this function is used to affect MDrv_Scaler_SetPanelTiming()'s behavior.
/// @param  bEnable             \b IN: TRUE: Enable force freerun. FALSE: disable force free run.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_SC_EX_ForceFreerun(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Get Force freerun status.
/// @return @ref MS_BOOL  True: Current is in Force freerun mode. False: Current is not in Force Freerun mode
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_SC_EX_IsForceFreerun(XC_DEVICE_ID *pDeviceId);

//-------------------------------------------------------------------------------------------------
/// Set specific in / out framerate control (Using in Box proejct only.)
/// @param  bEnable             \b IN: TRUE: Enable ouput frame control
/// @param  pPanelInfoEx        \b IN: The information about in / out framerate.
/// @param  pPanelInfoEx        \b IN: The window which need to be controlled.
/// @return @ref XC_EX_RETURN_VALUE          return type.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_SC_EX_SetFreerunVFreq(XC_DEVICE_ID *pDeviceId, XC_EX_VFREQ_SEL VFreq);

//-------------------------------------------------------------------------------------------------
/// Set external panel info for output
/// Currently, only support setting of two different vfreqs at same time
/// The set ExPanelInfo will take effect after running of function MApi_XC_SetPanelTiming
/// @param  bEnable             \b IN: TRUE: Enable this XC_PANEL_INFO_EX, FALSE: Disable this XC_PANEL_INFO_EX
/// @param  pPanelInfoEx        \b IN: The extern panel information to set @ref XC_PANEL_INFO_EX
/// @return @ref MS_BOOL               TRUE: Success, FALSE: Failed
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_SetExPanelInfo(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_PANEL_INFO_EX *pPanelInfoEx);

//-------------------------------------------------------------------------------------------------
/// Set the FPLL thresh mode:
/// @param  bEnable      \b IN: TRUE: Thresh mode, FALSE: Non-Thresh mode
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_Enable_FPLL_Thresh_Mode(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Enable auto no signal mode
/// @param  bEnable                \b IN: True: Enable auto no signal mode.
/// @eWindow                 \b IN: The window (main or sub) which need to be controled.
/// @return @ref XC_EX_RETURN_VALUE          TRUE: eWindow is in auto no signal mode.  FALSE: eWindow is not in auto no signal mode
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_EnableIPAutoNoSignal(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_SCALER_WIN eWindow );

//-------------------------------------------------------------------------------------------------
/// Return true is current is in auto nosignal mode.
/// @param  eWindow                \b IN: IP auto nosignal in specific window
/// @return @ref MS_BOOL          TRUE: eWindow is in auto no signal mode.  FALSE: eWindow is not in auto no signal mode
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_GetIPAutoNoSignal(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow );

//-------------------------------------------------------------------------------------------------
/// Enable or disable IP auto coast
/// @param  bEnable                \b IN: Enable or Disable
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_EnableIPAutoCoast(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Enable IP auto Coast debounce (the debounce time is 1 (default) in driver)
/// @return void
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_EnableIPCoastDebounce(XC_DEVICE_ID *pDeviceId);

//-------------------------------------------------------------------------------------------------
/// Clear IP auto Coast debounce
/// @return void
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_ClearIPCoastStatus(XC_DEVICE_ID *pDeviceId);

//-------------------------------------------------------------------------------------------------
/// Enable FPLL related settings not by program but by user's setting from TV tool
/// Including PhaseLimit, limitD5D6D7_RK
/// @param bEnable @ref MS_BOOL          \b IN: enable or not
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_EnableFpllManualSetting(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable);                           // debug purpose

//--------------------------------------------------------------------------------------------------------------------
/// Test if panel output is ok by changing output DClk, this is to test max range that FPLL can do
/// @param u32FpllSetOffset @ref MS_U32     \b IN: the offset to be add/minus the typical DClk output, unit is SET
/// @param u16TestCnt       @ref MS_U16     \b IN: the times to do boundary test
//--------------------------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_FpllBoundaryTest(XC_DEVICE_ID *pDeviceId, MS_U32 u32FpllSetOffset, MS_U16 u16TestCnt);       // debug purpose

//------------------------------
// Offline signal detection related
//------------------------------
//-----------------------------------------------------------------------------
/// Set the source need to be detect in offline detection.
/// @param XC_EX_INPUT_SOURCE_TYPE           \b IN: The source need to be monitor
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetOffLineDetection ( XC_DEVICE_ID *pDeviceId, XC_EX_INPUT_SOURCE_TYPE u8InputSourceType );
//-------------------------------------------------------------------------------------------------
/// Get Offline detection status to specific input source
/// @param  u8InputSourceType                \b IN: the specific input source type to do offline detection
/// @return @ref MS_U8                  TRUE: Success, FALSE: Failed
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U8   MApi_XC_EX_GetOffLineDetection( XC_DEVICE_ID *pDeviceId, XC_EX_INPUT_SOURCE_TYPE u8InputSourceType);
//-------------------------------------------------------------------------------------------------
/// Set Offline detection Sog Threshold
/// @param  u8Threshold                \b IN: threshold value t2,u3,u4: 0~31 other chip: 0~255
/// @Return TRUE: Successful FALSE: Fail
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_SetOffLineSogThreshold(XC_DEVICE_ID *pDeviceId, MS_U8 u8Threshold); //t2,u3,u4: 0~31 other chip: 0~255
//-------------------------------------------------------------------------------------------------
/// Set Offline Detection Sog filter bandwidth
/// @param  u8BW                \b IN: bandwidth value t2,u3,u4: 0~7 other chip: 0~31
/// @Return TRUE: Successful FALSE: Fail
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_SetOffLineSogBW(XC_DEVICE_ID *pDeviceId, MS_U8 u8BW);

//-----------------------------------------------------------------------------
/// Initial offline detect procedure.
/// @return @ref MS_BOOL               TRUE: Success, FALSE: Failed
//-----------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_OffLineInit(XC_DEVICE_ID *pDeviceId);

//------------------------------
// PIP
//------------------------------
//-------------------------------------------------------------------------------------------------
/// Set Extra fetch number. (This setting is usually used in PIP mode. Please set carefully)
/// @param u8val          \b IN: The extra fetch number.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_Set_Extra_fetch_adv_line(XC_DEVICE_ID *pDeviceId, MS_U8 u8val);

//-------------------------------------------------------------------------------------------------
/// Set the VGA SOG on or off
/// @param  bEnable                \b IN: bEnable =1, Turn on the VGA SOG; bEnable =0, Turn off the VGA SOG
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_SetVGASogEn(XC_DEVICE_ID *pDeviceId, MS_BOOL bVGASogEn);

//-------------------------------------------------------------------------------------------------
/// Control the output window(Main/Sub) on or off
/// @param  bEnable                \b IN: bEnable =1, Turn on the window; bEnable =0, Turn off the window
/// @param  eWindow              \b IN: eWindow =0, for MAIN; eWindow =1, for SUB;
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_EnableWindow(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// whether sub window is enable
/// @param  void                \b IN: none
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_Is_SubWindowEanble(XC_DEVICE_ID *pDeviceId);

//-------------------------------------------------------------------------------------------------
/// Set Border format
/// @param  u8WidthIn                \b IN: In-box width
/// @param  u8WidthOut               \b IN: Out-box width
/// @param  u8color                  \b IN: border color
/// @param  eWindow                  \b IN: which window we are going to set
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetBorderFormat( XC_DEVICE_ID *pDeviceId, MS_U8 u8Left, MS_U8 u8Right, MS_U8 u8Up, MS_U8 u8Down, MS_U8 u8color, XC_EX_SCALER_WIN eWindow );

//-------------------------------------------------------------------------------------------------
/// enable or disable Border
/// @param  bEnable                  \b IN: Enable or Disable
/// @param  eWindow                  \b IN: which window we are going to set
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_EnableBorder(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Set Z-order main window first or not
/// @param  bMainFirst               \b IN: TRUE: Main window first; FALSE: Sub window first
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_ZorderMainWindowFirst(XC_DEVICE_ID *pDeviceId, MS_BOOL bMainFirst);

//------------------------------
// PQ Load Function
//------------------------------
//-------------------------------------------------------------------------------------------------
/// Create a function for PQ in SC.
/// @param  PQ_Function_Info               \b IN: the information of the function
/// @param  u32InitDataLen          \b IN: the length of the PQ_Function_Info
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_PQ_LoadFunction(XC_DEVICE_ID *pDeviceId, PQ_EX_Function_Info* function_Info , MS_U32 u32InitDataLen);
//-------------------------------------------------------------------------------------------------
/// Return true if current status is H nonlinear scaling
/// @param  u32InitDataLen          \b IN: the length of the PQ_Function_Info
/// @return @ref MS_U8          True: Using HNonLinearScaling  False: Not in Nonlinear status
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_Check_HNonLinearScaling(XC_DEVICE_ID *pDeviceId);

//------------------------------
// EURO Function
//------------------------------

// Enable/Disable Euro/Australia Hdtv Detection support in driver
//-----------------------------------------------------------------------------
/// Enable/Disable Euro/Australia Hdtv Detection support in driver
/// @param  bEnable:
/// - ENABLE : enable support
/// - DISABLE : disable disable
/// @return None.
//-----------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_EnableEuroHdtvSupport(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable);

//-----------------------------------------------------------------------------
/// Enable Euro/Australia Hdtv Detection
/// @param  bEnable:
/// - ENABLE : enable detection
/// - DISABLE : disable detection
/// @return None.
//-----------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_EnableEuroHdtvDetection(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_SCALER_WIN eWindow);

//------------------------------
// Genenal R/W Function
//------------------------------

//-------------------------------------------------------------------------------------------------
/// General Read Byte Function
/// @param  u32Reg                \b IN: which value shouldn't contain xc sub bank and address
/// @return @ref MS_U8
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U8   MApi_XC_EX_ReadByte(MS_U32 u32Reg);

//-------------------------------------------------------------------------------------------------
/// General Write Byte Function
/// @param  u32Reg                \b IN: which value shouldn't contain xc sub bank and address
/// @return @ref MS_U8
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_WriteByte(MS_U32 u32Reg, MS_U8 u8Val);

//-------------------------------------------------------------------------------------------------
/// General Write Byte Function
/// @param  u32Reg                \b IN: which value shouldn't contain xc sub bank and address
/// @param  u8Val                \b IN: setting value
/// @param  u8Msk                \b IN: setting value
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_WriteByteMask(MS_U32 u32Reg, MS_U8 u8Val, MS_U8 u8Msk);

//-------------------------------------------------------------------------------------------------
/// General 2 Write Byte Function
/// @param  u32Reg                \b IN: which value shouldn't contain xc sub bank and address
/// @param  u16Val                \b IN: setting value
/// @param  u16Msk                \b IN: setting value
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_Write2ByteMask(MS_U32 u32Reg, MS_U16 u16val, MS_U16 u16Mask);

//------------------------------
// XC R/W Function, using mutex to protect
//------------------------------

//-------------------------------------------------------------------------------------------------
/// Scaler Write 2 Byte Function, and use mutex to protect while switch bank and write address
/// @param  u32Reg                \b IN: which value contain xc sub bank and address
/// @param  u16Val                \b IN: setting value
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_W2BYTE(XC_DEVICE_ID *pDeviceId, MS_U32 u32Reg, MS_U16 u16Val);

//-------------------------------------------------------------------------------------------------
/// Scaler Read 2 Byte Function, and use mutex to protect while switch bank and write address
/// @param  u32Reg                \b IN: which value contain xc sub bank and address
/// @return @ref MS_U16
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U16  MApi_XC_EX_R2BYTE(XC_DEVICE_ID *pDeviceId, MS_U32 u32Reg);

//-------------------------------------------------------------------------------------------------
/// Scaler Write 4 Byte Function, and use mutex to protect while switch bank and write address
/// @param  u32Reg                \b IN: which value contain xc sub bank and address
/// @param  u32Val                \b IN: setting value
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_W4BYTE(XC_DEVICE_ID *pDeviceId, MS_U32 u32Reg, MS_U32 u32Val);

//-------------------------------------------------------------------------------------------------
/// Scaler Read 4 Byte Function, and use mutex to protect while switch bank and write address
/// @param  u32Reg                \b IN: which value contain xc sub bank and address
/// @return @ref MS_U32
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U32  MApi_XC_EX_R4BYTE(XC_DEVICE_ID *pDeviceId, MS_U32 u32Reg);

//-------------------------------------------------------------------------------------------------
/// Scaler Read 2 Byte Mask Function, and use mutex to protect while switch bank and write address
/// @param  u32Reg                \b IN: which value contain xc sub bank and address
/// @param  u16mask              \b IN: decide which bit is valied
/// @return @ref MS_U16
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U16  MApi_XC_EX_R2BYTEMSK(XC_DEVICE_ID *pDeviceId, MS_U32 u32Reg, MS_U16 u16Mask);

//-------------------------------------------------------------------------------------------------
/// Scaler Write 2 Byte Mask Function, and use mutex to protect while switch bank and write address
/// @param  u32Reg                \b IN: which value contain xc sub bank and address
/// @param  u16Val              \b IN: Setting value
/// @param  u16mask              \b IN: decide which bit is valied
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_W2BYTEMSK(XC_DEVICE_ID *pDeviceId, MS_U32 u32Reg, MS_U16 u16Val, MS_U16 u16Mask);

//------------------------------
// MLoad Function, xc command burst
//------------------------------
//-------------------------------------------------------------------------------------------------
/// Initialize the Menuload
/// @param  PhyAddr                 \b IN: the physical address for the menuload
/// @param  u32BufByteLen           \b IN: the buffer length of the menu load commands
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_MLoad_Init(XC_DEVICE_ID *pDeviceId, MS_PHYADDR PhyAddr, MS_U32 u32BufByteLen);

//-------------------------------------------------------------------------------------------------
/// Enable/Disable the MLoad
/// @return  void
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_MLoad_Enable(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Get the status of MLoad
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_MLOAD_TYPE MApi_XC_EX_MLoad_GetStatus(XC_DEVICE_ID *pDeviceId);

//-------------------------------------------------------------------------------------------------
/// write signal command to Mload and fire
/// @param  u32Addr              \b IN: register
/// @param  u16Data              \b IN: value
/// @param  u16Mask              \b IN: mask
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_MLoad_WriteCmd_And_Fire(XC_DEVICE_ID *pDeviceId, MS_U32 u32Addr, MS_U16 u16Data, MS_U16 u16Mask);

//-------------------------------------------------------------------------------------------------
/// write multi commands to Mload and fire
/// @param  pu32Addr              \b IN: buffer of register
/// @param  pu16Data              \b IN: buffer of value
/// @param  pu16Mask              \b IN: buffer of mask
/// @param  u16CmdCnt             \b IN: counter of command
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_MLoad_WriteCmds_And_Fire(XC_DEVICE_ID *pDeviceId, MS_U32 *pu32Addr, MS_U16 *pu16Data, MS_U16 *pu16Mask, MS_U16 u16CmdCnt);

//------------------------------
// Menuload Gamma Function
//------------------------------
//-------------------------------------------------------------------------------------------------
/// Initialize the Menuload Gamma
/// @param  PhyAddr                 \b IN: the physical address for the menuload
/// @param  u32BufByteLen           \b IN: the buffer length of the menu load commands
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_MLG_Init(XC_DEVICE_ID *pDeviceId, MS_PHYADDR PhyAddr, MS_U32 u32BufByteLen);

//-------------------------------------------------------------------------------------------------
/// Enable/Disable the Menuload Gamma
/// @return  void
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_MLG_Enable(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Get the caps of Menuload Gamma
/// @return  TRUE if succeed, FALSE if failed
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_MLG_GetCaps(XC_DEVICE_ID *pDeviceId);

//-------------------------------------------------------------------------------------------------
/// Get the status of MLoad
/// @return @ref MLG_TYPE
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_MLG_TYPE MApi_XC_EX_MLG_GetStatus(XC_DEVICE_ID *pDeviceId);

//------------------------------
// For U4 set VOP data mux to VE
//------------------------------
//-------------------------------------------------------------------------------------------------
/// Select the source which need to connect to VE.
/// @param eVOPSelOSD_MUX           \b IN: The source need to connect to VE.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetOSD2VEMode(XC_DEVICE_ID *pDeviceId, XC_EX_VOP_SEL_OSD_XC2VE_MUX  eVOPSelOSD_MUX);

//-------------------------------------------------------------------------------------------------
/// Enable or disable prefilter in Scaler.
/// @param bEnable           \b IN: True: Enable: pre-filter. Disable: pre-filter
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_IP2_PreFilter_Enable(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Get pixel data with RGB format.
/// @param u16x           \b IN: X coordinate
/// @param u16Y           \b IN: Y coordinate
/// @param eWindow           \b IN: The window for retrieving data.
/// @return @ref u32r return the R data
/// @return @ref u32g return the G data
/// @return @ref u32b return the B data
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_GET_PixelRGB_ReturnValue MApi_XC_EX_Get_Pixel_RGB(XC_DEVICE_ID *pDeviceId, XC_EX_Get_Pixel_RGB *pData, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// During retrieve pixel data, system have a cursor on the screen. This function can keep the cursor on the screen.
/// @param bEnable           \b IN: Enable if you want to keep cursor on the screen
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_KeepPixelPointerAppear(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// @param  eMemFmt               \b IN: the format of memory
/// Set memory format
/// @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_Set_MemFmtEx(XC_DEVICE_ID *pDeviceId, XC_EX_MEM_FMT eMemFmt, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Get frame buffer less mode status
/// @return @ref MS_BOOL retun the status about FrameBufferLess mode
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_IsRequestFrameBufferLessMode(XC_DEVICE_ID *pDeviceId);

//-------------------------------------------------------------------------------------------------
/// Set Flag to bypass software reset in MApi_XC_EX_Init()
/// @param  bFlag \b TRUE: initialize XC by skipping SW reset; FALSE: initialize XC in normal case
/// @return E_XC_EX_RET_OK or E_XC_EX_RET_FAIL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_SkipSWReset(XC_DEVICE_ID *pDeviceId, MS_BOOL bFlag);

DLL_PUBLIC void    MApi_XC_EX_EnableRepWindowForFrameColor(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Set VOP Video and OSD Laler
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/// Set OSD Layer in Box Project  ( In TV chips, please use MApi_XC_SetVideoOnOSD)
/// @param eVOPOSDLayer     \b IN: OSD and Video layer selection
/// @param eWindow             \b IN: The window The alpha value of current window.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_SetOSDLayer(XC_DEVICE_ID *pDeviceId, XC_EX_VOP_OSD_LAYER_SEL eVOPOSDLayer, XC_EX_SCALER_WIN eWindow);
//-------------------------------------------------------------------------------------------------
/// Get OSD Layer in Box Project
/// @param eWindow             \b IN: The window The alpha value of current window.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_VOP_OSD_LAYER_SEL MApi_XC_EX_GetOSDLayer(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Set Constant Alpha of Video
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/// Set alpha value of video (now only support in box)
/// @param u8Val                \b IN: The alpha value of video with specific window
/// @param eWindow           \b IN: The window which need to be adjust
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_SetVideoAlpha(XC_DEVICE_ID *pDeviceId, MS_U8 u8Val, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Get alpha value of video (now only support in box)
/// @param pu8Val                \b IN: The alpha value of video with specific window
/// @param eWindow             \b IN: The alpha value of a window.
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_GetVideoAlpha(XC_DEVICE_ID *pDeviceId, MS_U8 *pu8Val, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Skip Wait Vsync
/// @param eWindow              \b IN: Enable
/// @param Skip wait Vsync      \b IN: Disable wait Vsync
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_SkipWaitVsync( XC_DEVICE_ID *pDeviceId, MS_BOOL eWindow, MS_BOOL bIsSkipWaitVsyn);

//-------------------------------------------------------------------------------------------------
/// Select which DE to vop
/// @param  bFlag               \b IN: @ref E_OP2VOP_DE_SEL
/// @return E_XC_EX_RET_OK or E_XC_EX_RET_FAIL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_OP2VOPDESel(XC_DEVICE_ID *pDeviceId, XC_EX_OP2VOP_DE_SEL eVopDESel);

//-------------------------------------------------------------------------------------------------
/// Set FRC Window
/// @param  e3dInputMode               \b IN: @ref E_XC_3D_INPUT_MODE
/// @param  e3dOutputMode               \b IN: @ref E_XC_3D_OUTPUT_MODE
/// @param  e3dPanelType               \b IN: @ref E_XC_3D_PANEL_TYPE
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_FRC_SetWindow(XC_DEVICE_ID *pDeviceId, XC_EX_3D_INPUT_MODE e3dInputMode, XC_EX_3D_OUTPUT_MODE e3dOutputMode, XC_EX_3D_PANEL_TYPE e3dPanelType);

//-------------------------------------------------------------------------------------------------
/// Set two initial factors mode to improve quality in FBL
/// @param  bEnable                \b IN: enable or disable two initial factors mode
/// @param  eWindow                \b IN: @ref XC_EX_SCALER_WIN
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_Enable_TwoInitFactor(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Get field packing mode support status
/// @return TRUE(success) or FALSE(fail)
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_IsFieldPackingModeSupported(void);

//-------------------------------------------------------------------------------------------------
/// Pre Init before XC Init
/// @param  u16Type               \b IN: @ref E_OP2VOP_DE_SEL
/// @param  para                     \b IN: parameter
/// @param  u32Length             \b IN: size of parameter
/// @return E_XC_EX_RET_OK or E_XC_EX_RET_FAIL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_PreInit( XC_DEVICE_ID *pDeviceId, XC_EX_PREINIT eType ,void* para, MS_U32 u32Length);

//-------------------------------------------------------------------------------------------------
/// Get RGB data from memory buffer
/// @param  eBufType               \b IN: get RGB 8 bits or 10 bits format data
/// @param  pRect                     \b IN: the widnow for getting data area in memory, need to refer to pre-scaling
/// @param  pRectBuf                \b IN: the buffer for getting data, the buffer typs must be the same as eBufType
/// @param  eWindow                \b IN: get main or sub video data from memory
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_Get_BufferData(XC_DEVICE_ID *pDeviceId, XC_EX_OUTPUTDATA_TYPE eBufType, XC_EX_WINDOW_TYPE *pRect, void *pRectBuf, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Set RGB data to memory buffer
/// @param  eBufType               \b IN: set RGB 8 bits or 10 bits format data
/// @param  pDstRect                \b IN: the widnow for setting data area in memory, need to refer to pre-scaling
/// @param  pSrcBuf                 \b IN: the buffer with RGB data for setting to memory, the buffer typs must be the same as eBufType
/// @param  pSrcRect                \b IN: the widnow for picking data area in pSrcBuf
/// @param  eWindow                \b IN: set main or sub video data to memory
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_Set_BufferData(XC_DEVICE_ID *pDeviceId, XC_EX_INPUTDATA_TYPE eBufType, XC_EX_WINDOW_TYPE *pDstRect, void *pSrcBuf, XC_EX_WINDOW_TYPE *pSrcRect, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Control the main window on or off
/// @param  bEnable                \b IN: bEnable =1, Turn on the window; bEnable =0, Turn off the window
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_EnableMainWindow(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable); // Turn on/off main/sub window

//-------------------------------------------------------------------------------------------------
/// Enable sub window and control the window size
/// @param  *pstDispWin                \b IN: Window type
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_EnableSubWindow(XC_DEVICE_ID *pDeviceId, XC_EX_WINDOW_TYPE *pstDispWin);

//-------------------------------------------------------------------------------------------------
/// Disable sub window
/// @param  void                \b IN: none
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_DisableSubWindow(XC_DEVICE_ID *pDeviceId);

//-------------------------------------------------------------------------------------------------
/// Set pixel shift
/// @param  s8H               \b IN: pixel shift H
/// @param  s8V               \b IN: pixel shift V
/// @return E_XC_EX_RET_OK or E_XC_EX_RET_FAIL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_SetPixelShift(XC_DEVICE_ID *pDeviceId, MS_S8 s8H, MS_S8 s8V);

//-------------------------------------------------------------------------------------------------
/// MApi_XC_SetVideoOnOSD
/// @param  E_VDO_ON_OSD_LAYER               \b IN: set video show on which osd layer
/// @param  eWindow                                     \b IN: set main or sub video data to memory
/// @return E_XC_EX_RET_OK or E_XC_EX_RET_FAIL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_SetVideoOnOSD(XC_DEVICE_ID *pDeviceId, XC_EX_VIDEO_ON_OSD_LAYER enlayer, XC_EX_SCALER_WIN eWindow);


//-------------------------------------------------------------------------------------------------
/// MApi_XC_SetOSDBlendingFormula
/// @param  enOsdIndex                              \b IN: osd index
/// @param  enType                                  \b IN: osd blending type
/// @param  eWindow                                 \b IN: blending with main or sub video
/// @return E_XC_EX_RET_OK or E_XC_EX_RET_FAIL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_SetOSDBlendingFormula(XC_DEVICE_ID *pDeviceId, E_XC_EX_OSD_INDEX enOsdIndex, XC_EX_OSD_BlENDING_TYPE enType, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
//  usage:
//    MS_XC_REPORT_PIXELINFO stRepPixInfo;
//    memset(&stRepPixInfo, 0, sizeof(MS_XC_REPORT_PIXELINFO));
//    stRepPixInfo.u32ReportPixelInfo_Version = XC_EX_REPORT_PIXELINFO_VERSION;
//    stRepPixInfo.u16ReportPixelInfo_Length = sizeof(MS_XC_REPORT_PIXELINFO);
//    stRepPixInfo.enStage   = E_XC_GET_PIXEL_STAGE_AFTER_OSD;
//    stRepPixInfo.u16XStart = xxxx;
//    stRepPixInfo.u16XEnd   = xxxx;
//    stRepPixInfo.u16YStart = xxxx;
//    stRepPixInfo.u16YEnd   = xxxx;
//    MApi_XC_ReportPixelInfo(&stRepPixInfo);
//
/// Report Pixel Info
/// @param   pstRepPixInfo               \b IN: pointer to struct MS_XC_REPORT_PIXELINFO
/// @return  TRUE if succeed, FALSE if failed
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_ReportPixelInfo(XC_DEVICE_ID *pDeviceId, XC_EX_REPORT_PIXELINFO *pstRepPixInfo);

//-------------------------------------------------------------------------------------------------
/// MApi_XC_SetScaling
/// @param  bEnable                               \b IN: set enable or disable
/// @param  eScaling_type                      \b IN: set scaling type, pre-scaling, post-scaling, both-scaling
/// @param  eVector_type                       \b IN: set H vector, v vector, and HV vector
/// @param  eWindow                             \b IN: set main or sub video data to memory
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetScaling( XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_SCALING_TYPE eScaling_type, XC_EX_VECTOR_TYPE eVector_type, XC_EX_SCALER_WIN eWindow );

//-------------------------------------------------------------------------------------------------
/// MApi_XC_EX_SetMCDIBufferAddress
/// @param  u32FBAddress                              \b IN: frame buffer base addr
/// @param  u32FBSize                                   \b IN: frame buffer size
/// @param  eType                                         \b IN: set frame buffer for MCDI ME1 or ME2
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_SetMCDIBufferAddress(XC_DEVICE_ID *pDeviceId, MS_PHYADDR u32FBAddress, MS_PHYADDR u32FBSize, XC_EX_MCDI_TYPE eType);

//-------------------------------------------------------------------------------------------------
/// MApi_XC_EnableMCDI
/// @param  bEnable                                      \b IN: enable/disable MCDI
/// @param  eType                                         \b IN: control MCDI ME1 or ME2 or both
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_EnableMCDI(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_MCDI_TYPE eType);


//-------------------------------------------------------------------------------------------------
/// MApi_XC_SendCmdToFRC
/// @param  u8Cmd                                      \b IN: CMD
/// @param  count                                         \b IN: parameter Counter
/// @param  pFRC_R2_Para                           \b IN: input parameter
/// @return  TRUE if succeed, FALSE if failed
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_SendCmdToFRC( XC_DEVICE_ID *pDeviceId, MS_U8 u8Cmd, MS_U8 count, XC_EX_FRC_R2_CMD_PARAMETER pFRC_R2_Para );

//-------------------------------------------------------------------------------------------------
/// MApi_XC_GetMsgFromFRC
/// @param  u8Cmd                                      \b IN: CMD
/// @param  pu8ParaCount                            \b IN: Counter
/// @param  pu8Para                                     \b IN: input parameter
/// @return  TRUE if succeed, FALSE if failed
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_GetMsgFromFRC(XC_DEVICE_ID *pDeviceId, MS_U8* pu8Cmd, MS_U8* pu8ParaCount, MS_U8* pu8Para);

//-------------------------------------------------------------------------------------------------
/// Enable/Disable RW bank auto
/// @param  bEnable                 \b IN: enable or disable
/// @param  eWindow                 \b IN: which window we are going to enable or disable
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_EX_EnableRWBankAuto(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Set XC W/R Bank Mapping Number
/// @param  u8Val                   \b IN: W/R bank mapping value
/// @param  eWindow                 \b IN: which window we are going to set
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_EX_SetWRBankMappingNum(XC_DEVICE_ID *pDeviceId, MS_U8 u8Val, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Get XC W/R Bank Mapping Number
/// @param  eWindow                 \b IN: which window we are going to get
/// @return MS_U8 W/R bank mapping number
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U8 MApi_XC_EX_GetWRBankMappingNum(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Get XC W/R Bank Mapping Number for Zap (including UC effect)
/// @param  eWindow                 \b IN: which window we are going to get
/// @return MS_U8 W/R bank mapping number
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U8 MApi_XC_EX_GetWRBankMappingNumForZap(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Set BOB mode
/// @param  bEnable                 \b IN: Enable BOB mode or not
/// @param  eWindow                 \b IN: which window we are going to set
/// @return TRUE - succeed, FALSE - fail
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_SetBOBMode(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// Set XC force read bank
/// @param  bEnable                 \b IN: Enable force read bank or not
/// @param  u8Bank                  \b IN: Force read bank index
/// @param  eWindow                 \b IN: which window we are going to set
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_EX_SetForceReadBank(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, MS_U8 u8Bank, XC_EX_SCALER_WIN eWindow);

//------------------------------
// LD
//-------------------------------------------------------------------------------------------------
/// LD set panel type
/// @param  eLdPanelType                \b IN: panel type
/// @return E_XC_EX_RET_OK or E_XC_EX_RET_FAIL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_LD_Init(XC_DEVICE_ID *pDeviceId, XC_EX_LD_PANEL_TYPE eLDPanelType );
//-------------------------------------------------------------------------------------------------
/// LD set memory address
/// @param  u8MIU                      \b IN: MIU Select
/// @param  u32LDFBase0                \b IN: LDF memeory0 address
/// @param  u32LDFBase1                \b IN: LDF memeory1 address
/// @param  u32LDBBase0                \b IN: LDB memeory0 address
/// @param  u32LDBBase1                \b IN: LDB memeory1 address
/// @param  u32EDGE2DBase               \b IN: EDGE2D memeory address
/// @param  u32LEDoffset                \b IN: LED  data offset
/// @return  E_XC_EX_RET_OK or E_XC_EX_RET_FAIL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_LD_SetMemoryAddress(XC_DEVICE_ID *pDeviceId, MS_U8 u8MIU ,MS_U32 u32LDFBase0,MS_U32 u32LDFBase1,MS_U32 u32LDBBase0,MS_U32 u32LDBBase1,MS_U32 u32EDGE2DBase,MS_U32 u32LEDoffset);
//-------------------------------------------------------------------------------------------------
/// set LD Level
/// @param  eMode                \b IN: LD level
/// @return E_XC_EX_RET_OK or E_XC_EX_RET_FAIL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_LD_SetLevel(XC_DEVICE_ID *pDeviceId, XC_EX_LD_MODE eMode);
//-------------------------------------------------------------------------------------------------
/// set  LD backlight is zero flags
/// @param  eMode                \b IN: backlight is zero flags
/// @return E_XC_EX_RET_OK or E_XC_EX_RET_FAIL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_Set_TurnoffLDBL(XC_DEVICE_ID *pDeviceId, MS_BOOL bturnoffbl);
//-------------------------------------------------------------------------------------------------
/// set not update  SPI  data Flags
/// @param  brefreshSpidata                \b IN: refresh Spi data flags
/// @return E_XC_EX_RET_OK or E_XC_EX_RET_FAIL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_Set_notUpdateSPIDataFlags(XC_DEVICE_ID *pDeviceId, MS_BOOL brefreshSpidata);
//-------------------------------------------------------------------------------------------------
/// set User mode LD Flags
/// @param  buserLDFlags                \b IN: User mode LD Flags
/// @return E_XC_EX_RET_OK or E_XC_EX_RET_FAIL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_Set_UsermodeLDFlags(XC_DEVICE_ID *pDeviceId, MS_BOOL buserLDFlags);
//-------------------------------------------------------------------------------------------------
/// set LD backlight level
/// @param  u8BLLeve              \b IN: backlight level
/// @return E_XC_EX_RET_OK or E_XC_EX_RET_FAIL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_Set_BLLevel(XC_DEVICE_ID *pDeviceId, MS_U8 u8BLLevel);

//-------------------------------------------------------------------------------------------------
/// set XC bandwidth saving X-mode
/// @param  bEnable                   \b IN: enable or disable
/// @param  eWindow                 \b IN: which window we are going to enable or disable
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_EX_Set_BWS_Mode(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// set FRC ColorPathCtrl
/// @param  epath_type               \b IN: Select one of path in the FRC_COLOR_PATH_TYPE
/// @param  bEnable                    \b IN: enable or disable
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_EX_FRC_ColorPathCtrl(XC_DEVICE_ID *pDeviceId, MS_U16 u16Path_sel, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// set FRC_OP2 SetRGBGain
/// @param  u16RedGain                 \b IN: Red Gain
/// @param  u16GreenGain              \b IN: Green Gain
/// @param  u16BlueGain                \b IN: Blue Gain
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_EX_FRC_OP2_SetRGBGain(XC_DEVICE_ID *pDeviceId, MS_U16 u16RedGain, MS_U16 u16GreenGain, MS_U16 u16BlueGain);

//-------------------------------------------------------------------------------------------------
/// set FRC_OP2 SetRGBOffset
/// @param  u16RedOffset                 \b IN: Red Offset
/// @param  u16GreenOffset              \b IN: Green Offset
/// @param  u16BlueOffset                \b IN: Blue Offset
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_EX_FRC_OP2_SetRGBOffset(XC_DEVICE_ID *pDeviceId, MS_U16 u16RedOffset, MS_U16 u16GreenOffset, MS_U16 u16BlueOffset);

//-------------------------------------------------------------------------------------------------
/// set FRC_OP2 SetDither
/// @param  u16dither                 \b IN: Dither setting
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_EX_FRC_OP2_SetDither(XC_DEVICE_ID *pDeviceId, MS_U16 u16dither);

//-------------------------------------------------------------------------------------------------
/// set XC Bypass MFC
/// @param  eEnable                \b IN: Enable or Disable
/// @return E_XC_EX_RET_OK or E_XC_EX_RET_FAIL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_FRC_BypassMFC(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// MApi_XC_ForceReadFrame
/// @param  bEnable                                 \b IN: enable/disable keep specified frame
/// @param  u16FrameIndex                           \b IN: control specified frame to show
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_ForceReadFrame(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, MS_U16 u16FrameIndex);
//-------------------------------------------------------------------------------------------------
/// MApi_XC_SetCsc
/// @param  bEnable                                 \b IN: enable/disable keep specified frame
/// @param  eWindow                 \b IN: which window we are going to enable or disable
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_EX_SetCsc( XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_SCALER_WIN eWindow );

//-------------------------------------------------------------------------------------------------
/// Register PQ Set FPLL thresh mode function
/// @param  fpPQCB              \b IN: function pointer of PQ set FPLL thresh mode
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_EX_RegisterPQSetFPLLThreshMode(XC_DEVICE_ID *pDeviceId, void (*fpPQCB)(MS_U8 u8PQWin));

//-------------------------------------------------------------------------------------------------
/// Get XC free run status
/// @return TRUE if it is free run, FALSE if not
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_GetFreeRunStatus(XC_DEVICE_ID *pDeviceId);

//-------------------------------------------------------------------------------------------------
/// MApi_XC_Get_DSForceIndexSupported
/// @param  eWindow                 \b IN: which window we are going to enable or disable
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_Get_DSForceIndexSupported(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// MApi_XC_Set_DSForceIndex
/// @param  bEnable                 \b IN: ENABLE/DISABLE force DS index or not
/// @param  u8Index                 \b IN: the index that needs to be forced in.
/// @param  eWindow                 \b IN: which window we are going to enable or disable
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_Set_DSForceIndex(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, MS_U8 u8Index, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// MApi_XC_Set_DSIndexSourceSelect
/// @param  eDSIdxSrc               \b IN: choose where the DS index comes from.
/// @param  eWindow                 \b IN: which window we are going to enable or disable
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_Set_DSIndexSourceSelect(XC_DEVICE_ID *pDeviceId, XC_EX_DS_INDEX_SOURCE eDSIdxSrc, XC_EX_SCALER_WIN eWindow);



//-------------------------------------------------------------------------------------------------
/// MApi_XC_Set_DSForceIndex
/// @param  bEnable                 \b IN: ENABLE/DISABLE force DS index or not
/// @param  u8Index                 \b IN: the index that needs to be forced in.
/// @param  eWindow                 \b IN: which window we are going to enable or disable
/// @return E_XC_EX_RET_OK or E_XC_EX_RET_FAIL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_OSDC_InitSetting(XC_DEVICE_ID *pDeviceId,
                                             XC_EX_OSDC_TGEN_Type E_XC_OSDC_TGEN_Type,
                                             XC_EX_OSDC_TGEN_INFO *pstOC_Tgen_Cus,
                                             XC_EX_OSDC_CTRL_INFO *pstOC_Ctrl);
//-------------------------------------------------------------------------------------------------
/// MApi_XC_Set_DSForceIndex
/// @param  eCtrl_type                 \b IN: ENABLE/DISABLE force DS index or not
/// @return E_XC_EX_RET_OK or E_XC_EX_RET_FAIL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_OSDC_Control(XC_DEVICE_ID *pDeviceId, MS_U32 eCtrl_type);

//-------------------------------------------------------------------------------------------------
/// MApi_XC_EX_OSDC_GetDstInfo
/// @param  pDstInfo                 \b IN: get the Desternation info
/// @param  u32SizeofDstInfo         \b IN: size check
/// @return E_XC_EX_RET_OK or E_XC_EX_RET_FAIL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_OSDC_GetDstInfo(XC_DEVICE_ID *pDeviceId, XC_EX_OSDC_DST_DispInfo *pDstInfo, MS_U32 u32SizeofDstInfo);

//-------------------------------------------------------------------------------------------------
/// MApi_XC_EX_OSDC_SetOutVfreqx10
/// @param  u16Vfreq         \b IN: output V freq x10
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_EX_OSDC_SetOutVfreqx10(XC_DEVICE_ID *pDeviceId, MS_U16 u16Vfreq);

//-------------------------------------------------------------------------------------------------
/// MApi_XC_EX_SetByPassOSDVsyncPos
/// @param  u16VsyncStart                              \b IN: OSD vsync start
/// @param  u16VsyncEnd                                \b IN: OSD vsync end
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_EX_BYPASS_SetOSDVsyncPos(XC_DEVICE_ID *pDeviceId, MS_U16 u16VsyncStart, MS_U16 u16VsyncEnd);

//-------------------------------------------------------------------------------------------------
/// MApi_XC_EX_BYPASS_SetInputSrc
/// @param  bEnable                              \b IN: ENABLE/DISABLE bypass mode
/// @param  input                                \b IN: Select the input source for bypass mode
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_EX_BYPASS_SetInputSrc(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, XC_EX_BYPASS_InputSource input);

//-------------------------------------------------------------------------------------------------
/// MApi_XC_EX_BYPASS_SetCSC
/// @param  bEnable                              \b IN: ENABLE/DISABLE the color space convert
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_EX_BYPASS_SetCSC(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// MApi_XC_EX_SetSeamlessZapping
/// @param  pDeviceId                 \b IN: which XC device we are going to enable or disable
/// @param  eWindow                 \b IN: which window we are going to enable or disable
/// @param  bEnable                 \b IN: ENABLE/DISABLE seamless zapping
/// @return E_XC_EX_RET_OK or E_XC_EX_RET_FAIL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_SetSeamlessZapping(XC_DEVICE_ID *pDeviceId, XC_EX_SCALER_WIN eWindow, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// MApi_XC_EX_Vtrack_SetPayloadData
/// @param  u16Timecode                       \b IN: The time code is coded on 16 bits. It is calculated based on the number of days from January 1st.
/// @param  u8ID                              \b IN: Operator ID
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_Vtrack_SetPayloadData(XC_DEVICE_ID *pDeviceId, MS_U16 u16Timecode, MS_U8 u8OperatorID);


//-------------------------------------------------------------------------------------------------
/// MApi_XC_EX_Vtrack_SetUserDefindedSetting
/// @param  bEnable                              \b IN: ENABLE/DISABLE Customized Setting
/// @param  pu8Setting                           \b IN: pointer to targert user definded setting data (include setting1 to setting3)
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_Vtrack_SetUserDefindedSetting(XC_DEVICE_ID *pDeviceId, MS_BOOL bUserDefinded, MS_U8 *pu8Setting);


//-------------------------------------------------------------------------------------------------
/// MApi_XC_EX_Vtrack_Enable
/// @param  u8FrameRate                          \b IN: ENABLE/DISABLE The FrameRateIn is based on the output format of the box
/// @param  bEnable                              \b IN: ENABLE/DISABLE Vtrack
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_Vtrack_Enable(XC_DEVICE_ID *pDeviceId, MS_U8 u8FrameRate, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Pre-set the specific window with PQ info
/// @param  pstXC_SetWin_Info      \b IN: the information of the window setting
/// @param  eWindow                \b IN: which window we are going to set
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_EX_PreSetPQInfo(XC_DEVICE_ID *pDeviceId, XC_EX_SETWIN_INFO *pstXC_SetWin_Info, XC_EX_SCALER_WIN eWindow);

//-------------------------------------------------------------------------------------------------
/// MApi_XC_EX_Is_OP1_TestPattern_Enabled
/// @return MS_BOOL: TRUE - enabled, FALSED - disabled
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_EX_Is_OP1_TestPattern_Enabled(XC_DEVICE_ID *pDeviceId);

//-------------------------------------------------------------------------------------------------
/// MApi_XC_EX_Set_OP1_TestPattern
/// @param  ePattern                                      \b IN: select test pattern
/// @param  eMode                                         \b IN: choose the patgen mode (only support E_XC_OP1_PATGEN_DISP_LB_MODE now)
/// @return E_APIXC_RET_OK or E_APIXC_RET_FAIL or E_APIXC_RET_FAIL_FUN_NOT_SUPPORT
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_Set_OP1_TestPattern(XC_DEVICE_ID *pDeviceId, XC_EX_OP1_PATTERN ePattern, XC_EX_OP1_PATGEN_MODE eMode);


//-------------------------------------------------------------------------------------------------
/// MApi_XC_Set_WhiteBalance_Pattern
/// @param  bEnable                  \b IN: enable/disable white balance test pattern
/// @param  u16R_CR_Data             \b IN: when enable white balance test pattern ,Data Generator for r_cr constant
/// @param  u16G_Y_Data              \b IN: when enable white balance test pattern ,Data Generator for g_y constant
/// @param  u16B_CB_Data             \b IN: when enable white balance test pattern ,Data Generator for b_cb constant
/// @return E_APIXC_RET_OK or E_APIXC_RET_FAIL or E_APIXC_RET_FAIL_FUN_NOT_SUPPORT
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC XC_EX_RETURN_VALUE MApi_XC_EX_Set_WhiteBalance_Pattern(XC_DEVICE_ID *pDeviceId, MS_BOOL bEnable, MS_U16 u16R_CR_Data, MS_U16 u16G_Y_Data ,MS_U16 u16B_CB_Data);


#ifdef __cplusplus
}
#endif

#endif /* _API_XC_EX_H_ */


