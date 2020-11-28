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

#ifndef _API_GOP_H_
#define _API_GOP_H_

#include "MsCommon.h"

#ifdef __cplusplus
extern "C"
{
#endif
//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
/// GOP Version
#define MSIF_GOP_LIB_CODE                   {'G','O','P','_'}    //Lib code
#define MSIF_GOP_LIBVER                     {'8','9'}            //LIB version
#define MSIF_GOP_BUILDNUM                   {'0','2'}            //Build Number
#define MSIF_GOP_CHANGELIST                 {'0','0','5','2','4','9','1','6'} //P4 ChangeList Number

#define GOP_API_VERSION                   /* Character String for DRV/API version             */  \
    MSIF_TAG,                             /* 'MSIF'                                           */  \
    MSIF_CLASS,                           /* '00'                                             */  \
    MSIF_CUS,                             /* 0x0000                                           */  \
    MSIF_MOD,                             /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_GOP_LIB_CODE,                    /* IP__                                             */  \
    MSIF_GOP_LIBVER,                      /* 0.0 ~ Z.Z                                        */  \
    MSIF_GOP_BUILDNUM,                    /* 00 ~ 99                                          */  \
    MSIF_GOP_CHANGELIST,                  /* CL#                                              */  \
    MSIF_OS

///GOP_PALETTE_ENTRY_NUM
#define GOP_PALETTE_ENTRY_NUM   256
///FB_FMT_AS_DEFAULT
#define FB_FMT_AS_DEFAULT   0xFFFF
///DEFAULT_FB_FMT
#define DEFAULT_FB_FMT 0xffff
///INVALID_WIN_ID
#define INVALID_WIN_ID GWIN_NO_AVAILABLE
///GWIN_ID_INVALID
#define GWIN_ID_INVALID 0xFF
///MAX_GWIN_SUPPORT
#define MAX_GWIN_SUPPORT MApi_GOP_GWIN_GetTotalGwinNum()

#define MAX_GOP0_SUPPORT MApi_GOP_GWIN_GetGwinNum(0)
#define MAX_GOP1_SUPPORT MApi_GOP_GWIN_GetGwinNum(1)
#define MAX_GOP2_SUPPORT MApi_GOP_GWIN_GetGwinNum(2)
#define MAX_GOP3_SUPPORT MApi_GOP_GWIN_GetGwinNum(3)
#define MAX_GOP4_SUPPORT MApi_GOP_GWIN_GetGwinNum(4)
#define MAX_GOP5_SUPPORT MApi_GOP_GWIN_GetGwinNum(5)

//#define MAX_GOP_SUPPORT MApi_GOP_GWIN_GetMaxGOPNum()

#define GOP0_GWIN_START 0
#define GOP1_GWIN_START MAX_GOP0_SUPPORT
#define GOP2_GWIN_START MAX_GOP0_SUPPORT + MAX_GOP1_SUPPORT
#define GOP3_GWIN_START MAX_GOP0_SUPPORT + MAX_GOP1_SUPPORT + MAX_GOP2_SUPPORT
#define GOP4_GWIN_START MAX_GOP0_SUPPORT + MAX_GOP1_SUPPORT + MAX_GOP2_SUPPORT + MAX_GOP3_SUPPORT
#define GOP5_GWIN_START MAX_GOP0_SUPPORT + MAX_GOP1_SUPPORT + MAX_GOP2_SUPPORT + MAX_GOP3_SUPPORT + MAX_GOP4_SUPPORT

#define GOP_MULTIINFO_NUM 8
#ifndef MAX_GWIN_FB_SUPPORT
///MAX_GWIN_FB_SUPPORT
#define MAX_GWIN_FB_SUPPORT 32
#endif

/// GOP API return value
typedef enum
{
    ///GOP API return fail.
    GOP_API_FAIL                        = 0,
    ///GOP API return success.
    GOP_API_SUCCESS                     = 1,
    ///GOP API return non align address.
    GOP_API_NON_ALIGN_ADDRESS           ,
    ///GOP API return non align pitch.
    GOP_API_NON_ALIGN_PITCH             ,
    ///GOP API return depend no avail.
    GOP_API_DEPEND_NOAVAIL              ,
    ///GOP API return mutex obtain fail.
    GOP_API_MUTEX_OBTAIN_FAIL           ,
    ///GOP API return mutex obtain.
    GOP_API_MUTEX_OBTAINED              ,
    ///GOP API return invalid buffer info.
    GOP_API_INVALID_BUFF_INFO          ,
    ///GOP API return invalid parameter.
    GOP_API_INVALID_PARAMETERS,
    ///GOP API return this interface not supported.
    GOP_API_FUN_NOT_SUPPORTED,
    ///GOP API return enum not supported.
    GOP_API_ENUM_NOT_SUPPORTED,
    ///GOP API return create gwin fail.
    GOP_API_CRT_GWIN_FAIL               = 0xFE,
    ///GOP API return create no avail
    GOP_API_CRT_GWIN_NOAVAIL            = 0xFF,
} E_GOP_API_Result;

///GWIN_FAIL
#define GWIN_FAIL         GOP_API_CRT_GWIN_FAIL
///GWIN_OK
#define GWIN_OK           GOP_API_SUCCESS
///GWIN_NO_AVAILABLE
#define GWIN_NO_AVAILABLE GOP_API_CRT_GWIN_NOAVAIL


///GWINID
typedef MS_U8 GWINID;

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
/// GWIN display property
typedef struct
{
    ///gwin id.
    MS_U8 gId;
    ///gwin start x coordinate.
    MS_U16 StartX;
    ///gwin start y coordinate.
    MS_U16 StartY;
    ///gwin win width.
    MS_U16 Win_Width;
    ///gwin win height.
    MS_U16 Win_Height;
    ///gwin frame buffer offset x.
    MS_U16 FBOffset_X;
    ///gwin frame buffer offset y.
    MS_U16 FBOffset_Y;
} GOP_GwinDispProperty;

/// GOP init info
typedef struct
{
    ///panel width.
    MS_U16 u16PanelWidth;
    ///panel height.
    MS_U16 u16PanelHeight;
    ///panel h-start.
    MS_U16 u16PanelHStr;
    ///vsync interrupt flip enable flag.
    MS_BOOL bEnableVsyncIntFlip;
    ///gop frame buffer starting address.
    MS_PHYADDR u32GOPRBAdr;
    ///gop frame buffer length.
    MS_U32 u32GOPRBLen;
    ///gop regdma starting address.
    MS_PHYADDR u32GOPRegdmaAdr;
    ///gop regdma length.
    MS_U32 u32GOPRegdmaLen;
}GOP_InitInfo;

// scale direction
typedef enum
{
    // no scale
    E_GOP_NO_STRETCH = 0x00,
    // horizontal scale
    E_GOP_H_STRETCH = 0x01,
    // vertical scale
    E_GOP_V_STRETCH = 0x10,
    // both horizontal and vertical scale
    E_GOP_HV_STRETCH = 0x11,
} EN_GOP_STRETCH_DIRECTION;

/// Define GWIN color format.
typedef enum
{
    /// Color format RGB555 and Blink.
    E_GOP_COLOR_RGB555_BLINK    =E_MS_FMT_1ABFgBg12355,
    /// Color format RGB565.
    E_GOP_COLOR_RGB565          =E_MS_FMT_RGB565,
    /// Color format ARGB4444.
    E_GOP_COLOR_ARGB4444        =E_MS_FMT_ARGB4444,
    /// Color format alpha blink.
    E_GOP_COLOR_2266            =E_MS_FMT_FaBaFgBg2266,
    /// Color format I8 (256-entry palette).
    E_GOP_COLOR_I8              =E_MS_FMT_I8,
    /// Color format ARGB8888.
    E_GOP_COLOR_ARGB8888        =E_MS_FMT_ARGB8888,
    /// Color format ARGB1555.
    E_GOP_COLOR_ARGB1555        =E_MS_FMT_ARGB1555,
    /// Color format ABGR8888.    - Andriod Format
    E_GOP_COLOR_ABGR8888        =E_MS_FMT_ABGR8888,
    /// Color format RGB555/YUV422.
    E_GOP_COLOR_RGB555YUV422    =E_MS_FMT_ARGB1555_DST,
    /// Color format YUV422.
    E_GOP_COLOR_YUV422          =E_MS_FMT_YUV422,
    /// Color format RGBA5551.    - Andriod Format
    E_GOP_COLOR_RGBA5551        =E_MS_FMT_RGBA5551,
    /// Color format RGBA4444.    - Andriod Format
    E_GOP_COLOR_RGBA4444        =E_MS_FMT_RGBA4444,
    /// Color format RGBA8888.    - Andriod Format
    E_GOP_COLOR_RGBA8888        =E_MS_FMT_RGBA8888,
    /// Color format BGR565.    - Andriod Format
    E_GOP_COLOR_BGR565          =E_MS_FMT_BGR565,
    /// Color format ABGR4444.    - Andriod Format
    E_GOP_COLOR_ABGR4444        =E_MS_FMT_ABGR4444,
    /// Color format AYUV8888.    - Andriod Format
    E_GOP_COLOR_AYUV8888        =E_MS_FMT_AYUV8888,
    /// Color format ABGR1555.    - Andriod Format
    E_GOP_COLOR_ABGR1555        =E_MS_FMT_ABGR1555,
    /// Color format BGRA5551.    - Andriod Format
    E_GOP_COLOR_BGRA5551        =E_MS_FMT_BGRA5551,
    /// Color format BGRA4444.    - Andriod Format
    E_GOP_COLOR_BGRA4444        =E_MS_FMT_BGRA4444,
    /// Color format BGRA8888.    - Andriod Format
    E_GOP_COLOR_BGRA8888        =E_MS_FMT_BGRA8888,
    /// Invalid color format.
    E_GOP_COLOR_INVALID         =E_MS_FMT_GENERIC
} EN_GOP_COLOR_TYPE;


/// GWIN Information
typedef struct
{
    /// gwin v-start (unit: line).
    MS_U16 u16DispVPixelStart;
    /// gwin v-end (unit: line).
    MS_U16 u16DispVPixelEnd;
    /// gwin h-start (unit: pix).
    MS_U16 u16DispHPixelStart;
    /// gwin h-end (unit: pix).
    MS_U16 u16DispHPixelEnd;
    /// gwin dram starting address (unit: Byte).
    MS_U32 u32DRAMRBlkStart;
    /// gwin's frame buffer width (unit: pix).
    MS_U16 u16RBlkHPixSize;
    /// gwin's frame buffer height (unit: pix).
    MS_U16 u16RBlkVPixSize;
    /// gwin's frame buffer pitch (unit: Byte).
    MS_U16 u16RBlkHRblkSize;
    /// gwin's frame buffer x0 (unit: pix).
    MS_U16 u16WinX;
    ///  gwin's frame buffer v0 (unit: pix).
    MS_U16 u16WinY;
    /// no use now.
    MS_U32 u32scrX;
    /// no use now.
    MS_U32 u32scrY;
    /// gwin's frame buffer color format.
    EN_GOP_COLOR_TYPE clrType;
} GOP_GwinInfo;

/// GOP palette entry
typedef struct
{
    /// A.
    MS_U8 u8A;
    /// R.
    MS_U8 u8R;
    /// G.
    MS_U8 u8G;
    /// B.
    MS_U8 u8B;
} GOP_Palette;

/// Frame buffer attributes for GWIN
typedef struct
{
    /// frame buffer is mapped to which gwin.
    MS_U8 gWinId;
    /// frame buffer enable flag.
    MS_U8 enable:1;
    /// frame buffer allocated flag.
    MS_U8 allocated:1;
    /// frame buffer x0 (unit: pix).
    MS_U16 x0;
    /// frame buffer y0 (unit: line).
    MS_U16 y0;
    /// frame buffer x1 (unit: pix).
    MS_U16 x1;
    /// frame buffer y1 (unit: line).
    MS_U16 y1;
    /// frame buffer width (unit: pix).
    MS_U16 width;
    /// frame buffer height (unit: line).
    MS_U16 height;
    /// frame buffer pitch (unit: byte).
    MS_U16 pitch;
    /// frame buffer color format.
    MS_U16 fbFmt;
    /// frame buffer starting address.
    MS_U32 addr;
    /// frame buffer size.
    MS_U32 size;
    /// next frame buffer id in the same pool.
    MS_U8 next;
    /// previous frame buffer in the same pool.
    MS_U8 prev;
    ///store which AP use this FB.
    MS_U8 string;
    /// frame buffer s_x (unit: pix).
    MS_U16 s_x;
    /// frame buffer  s_y (unit: pix).
    MS_U16 s_y;
    /// frame buffer dispWidth (unit: pix).
    MS_U16 dispWidth;
    /// frame buffer dispHeight (unit: line).
    MS_U16 dispHeight;
} GOP_GwinFBAttr;

/// Dump Window Information
typedef struct
{
    /// dwin v-start (unit:line).
    MS_U16 u16VPixelStart;
    /// dwin v-end (unit: line).
    MS_U16 u16VPixelEnd;
    /// dwin h-start (unit: pix).
    MS_U16 u16HPixelStart;
    /// dwin h-end (unit: pix).
    MS_U16 u16HPixelEnd;
    /// dwin dram starting address (unit: Byte).
    MS_U32 u32TFDRAMAddr;
    /// dwin access address high bond (unit: Byte).
    MS_U32 u32BFDRAMAddr;
    /// dwin jump address length after each dwin line end to next line start (unit: Byte).
    MS_U16 u16DRAMJumpLen;
    /// DWIN format: 0 UV7Y8, 1 UV8Y8, 2 ARGB8888, 3 RGB565.
    MS_U8 u8fmt;
} GOP_DwinInfo;

/// DWIN property
typedef struct
{
    /// dwin h-start (unit: pix).
    MS_U16 u16x;
    /// dwin h-end (unit: pix).
    MS_U16 u16y;
    /// dwin width (unit: pix).
    MS_U16 u16w;
    /// height (unit: line).
    MS_U16 u16h;
    /// dwin dram starting address (unit: Byte).
    MS_U32 u32fbaddr0;
    ///  dwin access address high bond (unit: Byte).
    MS_U32 u32fbaddr1;
    /// Number of pixels per horizontal line.
    MS_U16 u16fbw;
} GOP_DwinProperty;

/// DWIN scan mode
typedef enum
{
    /// progessive.
    DWIN_SCAN_MODE_PROGRESSIVE,
    /// interlace.
    DWIN_SCAN_MODE_extern,
} EN_GOP_DWIN_SCAN_MODE;

/// DWIN source selection
 typedef enum
{
    /// DWIN OP source
    DWIN_SRC_OP = 0,
    /// DWIN MVOP source
    DWIN_SRC_MVOP = 1,
    /// DWIN IP source
    DWIN_SRC_IP = 2,
    /// DWIN OP1 source
    DWIN_SRC_OP1 = 3,
    /// DWIN SUBMVOP source
    DWIN_SRC_SUBMVOP = 4,
    /// DWIN GOPScaling source
    DWIN_SRC_GOPScaling = 5,
    DWIN_SRC_MAX = 6,
}EN_GOP_DWIN_SRC_SEL;

/// DWIN source data format
typedef enum
{
    /// CrYCb domain.
    DWIN_DATA_FMT_UV7Y8 = 0,
    /// CrYCb domain.
    DWIN_DATA_FMT_UV8Y8,
    /// RGB domain (CSC bypass).
    DWIN_DATA_FMT_ARGB8888,
    /// RGB domain (CSC bypass).
    DWIN_DATA_FMT_RGB565,
    DWIN_DATA_FMT_MAX
} EN_GOP_DWIN_DATA_FMT;

/// DWIN alpha source
typedef enum
{
    /// Alpha from constant.
    DWIN_ALPHA_SRC_CONST = 0,
    /// Alpha from source.
    DWIN_ALPHA_SRC_SOURCE = 1,
    DWIN_ALPHA_SRC_MAX
} EN_GOP_DWIN_ALPHA_SRC;

/// DWIN UV sample mode
typedef enum
{
    /// original.
    DWIN_UVSAMPLE_ORI = 0,
    /// left point.
    DWIN_UVSAMPLE_LEFT = 1,
    /// right point.
    DWIN_UVSAMPLE_RIGHT = 2,
    /// average point.
    DWIN_UVSAMPLE_AVG = 3,
    DWIN_UVSAMPLE_MAX
} EN_GOP_DWIN_UVSAMPLE_Mode;

/// DWIN Interrupt mask
typedef enum
{
    /// DWIN PROG INT mask
    GOPDWIN_INT_MASK_PROG   = 0x0010,
    /// DWIN TOP Field INT mask
    GOPDWIN_INT_MASK_TF     = 0x0020,
    /// DWIN Bottom Field INT mask
    GOPDWIN_INT_MASK_BF     = 0x0040,
    /// DWIN Vsync INT mask
    GOPDWIN_INT_MASK_VS     = 0x0080,
} EN_GOP_DWIN_INT_MASK;

/// GWIN output color domain
typedef enum
{
    /// output color RGB.
    GOPOUT_RGB,
    /// output color YUV.
    GOPOUT_YUV,
} EN_GOP_OUTPUT_COLOR;

/// Define GOP destination displayplane type
typedef enum
{
    ///IP0 path.
    E_GOP_DST_IP0=0,
    ///Mixer to VE path .
    E_GOP_DST_MIXER2VE,
     ///OP path.
    E_GOP_DST_OP0,
    ///VOP path.
    E_GOP_DST_VOP,
    ///IP1 path.
    E_GOP_DST_IP1,
    /// IP man path.
    E_GOP_DST_IP_MAIN,
    ///IP sub path.
    E_GOP_DST_IP_SUB,
    ///Mixer to OP Path
    E_GOP_DST_MIXER2OP,
    ///VOP path.
    E_GOP_DST_VOP_SUB,
    ///FRC path
    E_GOP_DST_FRC,
    ///DIRECT TO VE path
    E_GOP_DST_VE,
    ///OP1 path.
    E_GOP_DST_OP1,
    ///MIXER2OP1
    E_GOP_DST_MIXER2OP1,
    ///DIP path.
    E_GOP_DST_DIP,
    ///GS path.
    E_GOP_DST_GOPScaling,
    ///4K2K BYPASS path
    E_GOP_DST_BYPASS,
    MAX_GOP_DST_SUPPORT,
} EN_GOP_DST_TYPE;

/// GOP Stretch Window Information
typedef struct
{
    /// Destination Type
    EN_GOP_DST_TYPE eDstType;
    /// x start
    MS_U16 x;
    /// y start
    MS_U16 y;
    /// Stretch Window Width
    MS_U16 width;
    /// Stretch Windows Height
    MS_U16 height;
} GOP_StretchInfo;

/// Define palette read type.
typedef enum
{
    /// Palette access from GOP0 RIU.
    E_GOP_PAL_GOP_RIU    = 0,
    /// Palette access from GOP0 REGDMA.
    E_GOP_PAL_GOP_REGDMA  = 1,
    /// Palette access from GOP1 RIU.
    E_GOP1_PAL_GOP_RIU    = 2,
    /// Palette access from GOP1 REGDMA.
    E_GOP1_PAL_GOP_REGDMA  = 3,
} EN_GOP_PALETTE_READTYPE;

/// Transparent color format
typedef enum
{
    /// RGB mode transparent color.
    GOPTRANSCLR_FMT0,
    /// index mode transparent color.
    GOPTRANSCLR_FMT1,
} EN_GOP_TRANSCLR_FMT;

/// Define GOP H-Stretch mode.
typedef enum
{
    /// 6-tape (including nearest) mode.
    E_GOP_HSTRCH_6TAPE         = 0,
    /// duplicate mode.
    E_GOP_HSTRCH_DUPLICATE     = 1,
    /// 6-tape (Linear mode)
    E_GOP_HSTRCH_6TAPE_LINEAR  = 2,
    /// 6-tape (Nearest mode)
    E_GOP_HSTRCH_6TAPE_NEAREST = 3,
    /// 6-tape (Gain0)
    E_GOP_HSTRCH_6TAPE_GAIN0   = 4,
    /// 6-tape (Gain1)
    E_GOP_HSTRCH_6TAPE_GAIN1   = 5,
    /// 6-tape (Gain2)
    E_GOP_HSTRCH_6TAPE_GAIN2   = 6,
    /// 6-tape (Gain3)
    E_GOP_HSTRCH_6TAPE_GAIN3   = 7,
    /// 6-tape (Gain4)
    E_GOP_HSTRCH_6TAPE_GAIN4   = 8,
    /// 6-tape (Gain5)
    E_GOP_HSTRCH_6TAPE_GAIN5   = 9,

} EN_GOP_STRETCH_HMODE;

/// Define GOP V-Stretch mode.
typedef enum
{
    ///linear mode.
    E_GOP_VSTRCH_LINEAR = 0,
    /// duplicate mode.
    E_GOP_VSTRCH_DUPLICATE = 1,
    /// nearest mode.
    E_GOP_VSTRCH_NEAREST = 2,
    /// nearest mode.
    E_GOP_VSTRCH_LINEAR_GAIN0 = 3,
    E_GOP_VSTRCH_LINEAR_GAIN1 = 4,
} EN_GOP_STRETCH_VMODE;

/// Define GOP Transparent color Stretch Mode.
typedef enum
{
    E_GOP_TRANSPCOLOR_STRCH_DUPLICATE = 0,
    E_GOP_TRANSPCOLOR_STRCH_ASNORMAL = 1,
} EN_GOP_STRCH_TRANSPCOLORMODE;

/// Define palette color format.
typedef enum
{
    /// Palette color format is ARGB8888.
    E_GOP_PAL_ARGB8888    = 0,
    /// Invalid palette color format.
    E_GOP_PAL_INVALID
} EN_GOP_PALETTE_TYPE;

/// Define GOP FB string.
typedef enum
{
    E_GOP_FB_NULL,
    /// OSD frame buffer.
    E_GOP_FB_OSD,
    /// Mute frame buffer.
    E_GOP_FB_MUTE,
    /// subtitle frame buffer.
    E_GOP_FB_SUBTITLE,
    /// teltext frame buffer.
    E_GOP_FB_TELTEXT,
    /// MHEG5 frame buffer.
    E_GOP_FB_MHEG5,
    /// CC frame buffer.
    E_GOP_FB_CLOSEDCAPTION,
} EN_GOP_FRAMEBUFFER_STRING;


/// Define GOP Event for Notification.
typedef enum
{
    /// E_GOP_EVENT_BUF_ARRANGE. Begin of Rearrange GOP buffers.
    E_GOP_EVENT_BUF_ARRANGE_BEGIN    = 0,
    /// E_GOP_Event_Buffer_Rearrange. End of Rearrange GOP buffers.
    E_GOP_EVENT_BUF_ARRANGE_END    = 1,
} EN_GOP_EVENT_TYPE;

/// Define GOP G3D DATA FORMAT.
typedef enum
{
    /// E_GOP_TILE_DATA_16BPP. 16 BPP DATA FOR TILE MODE
    E_GOP_TILE_DATA_16BPP    = 0,
    /// E_GOP_TILE_DATA_16BPP. 32 BPP DATA FOR TILE MODE
    E_GOP_TILE_DATA_32BPP    = 1,
} EN_GOP_TILE_DATA_TYPE;

/// Define GOP MIU SEL
typedef enum
{
    /// E_GOP_SEL_MIU0. gop access miu 0
    E_GOP_SEL_MIU0    = 0,
    /// E_GOP_SEL_MIU1. gop access miu1
    E_GOP_SEL_MIU1    = 1,
} EN_GOP_SEL_TYPE;

///Define OC Bank Mode SEL
typedef enum
{
    /// SEL 2 memory bank Mode
    E_GOP_OC_SEL_2BankMode   = 1,
    /// SEL 4 memory bank Mode
    E_GOP_OC_SEL_4BankMode   = 2 ,
} EN_GOP_OC_SEL_TYPE;


/// Define the entry of palette.
typedef union
{
    ///8-bits access.
    struct
    {
        ///A.
        MS_U8 u8A;
        ///R.
        MS_U8 u8R;
        ///G.
        MS_U8 u8G;
        ///B.
        MS_U8 u8B;
    } RGB;
    /// 32-bits direct access.
    MS_U8 u8Data[4];
} GOP_PaletteEntry;

/// GOP API info
typedef struct
{
    /// Maximum support GOP number.
    MS_U8 u8MaxGOPNum;
    /// Maximum support GWIN number.
    MS_U8 u8MaxGwinNum;
    /// gop destination blending path. (save supported dst type in array)
    EN_GOP_DST_TYPE SupportGOPDst[MAX_GOP_DST_SUPPORT];
} GOP_ApiInfo;

typedef union
{
    MS_U8 u8DWinIntInfo;
    struct
    {
        MS_U8 bDWinIntWADR:1;
        MS_U8 bDWinIntPROG:1;
        MS_U8 bDWinIntTF:1;
        MS_U8 bDWinIntBF:1;
        MS_U8 bDWinIntVS:1;
        MS_U8 reserved:3;
    }sDwinIntInfo;
}GOP_DWinIntInfo;

/// GOP API run time status
typedef struct
{
    /// gop0 destination blending path. (0xFF represent not support)
    EN_GOP_DST_TYPE eGOPNumDstType[6];
    /// gop stretch window h size status. (0xFF represent not support)
    MS_U16 u16GopNumStrWinHSize[6];
    /// gop stretch window v size status. (0xFF represent not support)
    MS_U16 u16GopNumStrWinVSize[6];

    /// gop0 gwin status (Is gwin enable?).  (gop0 gwin ID: 0~3)
    MS_BOOL Gop0GwinIsEnable[4];
    /// gop1 gwin status (Is gwin enable?).  (gop1 gwin ID: 4~5)
    MS_BOOL Gop1GwinIsEnable[4];
    /// gop2 gwin status (Is gwin enable?)   (gop2 gwin ID: 6)
    MS_BOOL Gop2GwinIsEnable;
    /// gop3 gwin status (Is gwin enable?)   (gop2 gwin ID: 7)
    MS_BOOL Gop3GwinIsEnable;
    MS_BOOL Gop4GwinIsEnable;
    MS_BOOL Gop5GwinIsEnable;
} GOP_ApiStatus;

/// Define GOP Gwin Relative Priority setting info
typedef struct
{
    ///The valid number of below setting. Since Relative Priority, Must larger than 1 and smaller than 5
    /// 2 means u81stGwin & u82stGwin valid, 3 means u81stGwin, u82stGwin, u83stGwin valid
    /// 4 means all valid.
    MS_U8 u8GwinNum;
    MS_U8 u8GwinPri[4];
}GOP_GwinPri;

///the GOP and mux setting info
typedef struct
{
  //GopMux arrays record the u8GopIndex and the corresponding MuxIndex
  //u8MuxCounts: how many mux need to modify the gop settings

  struct
  {
      MS_U8 u8GopIndex;
      MS_U8 u8MuxIndex;
  }GopMux[6];
  MS_U8 u8MuxCounts;
}GOP_MuxConfig;

///the GOP and OSD Layer setting info on utopia
typedef struct _GOP_LayerConfig
{
  struct
  {
      MS_U32 u32GopIndex;
      MS_U32 u32LayerIndex;
  }stGopLayer[6];
  MS_U32 u32LayerCounts;
}GOP_LayerConfig, *PGOP_LayerConfig;

typedef struct
{
    MS_U8 gWinId;
    MS_U32 u32FlipAddr;
    MS_U32 u32SubAddr;
    MS_U16 u16WaitTagID;
    MS_U16 *pU16QueueCnt;
}GOP_FlipConfig, *PGOP_FlipConfig;

typedef struct
{
    MS_U8 u8InfoCnt;
    GOP_FlipConfig astGopInfo[GOP_MULTIINFO_NUM];
}GOP_MultiFlipInfo, *PGOP_MultiFlipInfo;

/// Define Mux
typedef enum
{
    ///Select gop output to mux0
    EN_GOP_MUX0 = 0,
    /// Select gop output to mux1
    EN_GOP_MUX1 = 1,
    /// Select gop output to mux2
    EN_GOP_MUX2 = 2,
    /// Select gop output to mux3
    EN_GOP_MUX3 = 3,
        ///Select gop output to IP0
    EN_GOP_IP0_MUX = 4,
    /// Select gop output to IP1
    EN_GOP_IP1_MUX = 5,
    /// Select gop output to vop0
    EN_GOP_VOP0_MUX = 6,
    /// Select gop output to vop1
    EN_GOP_VOP1_MUX = 7,
    /// Select gop output to FRC mux0
    EN_GOP_FRC_MUX0 = 8,
    /// Select gop output to FRC mux1
    EN_GOP_FRC_MUX1 = 9,
    /// Select gop output to FRC mux2
    EN_GOP_FRC_MUX2 = 10,
    /// Select gop output to FRC mux3
    EN_GOP_FRC_MUX3 = 11,
    /// Select gop output to BYPASS mux
    EN_GOP_BYPASS_MUX0 = 12,
    /// Select gop output to IP0_SUB
    EN_GOP_IP0_SUB_MUX = 13,
    /// Select gop output to VOP0_SUB
    EN_GOP_VOP0_SUB_MUX = 14,
    /// Select gop output to OP1
    EN_GOP_OP1_MUX = 15,
    /// Select gop output to DIP
    EN_GOP_DIP_MUX = 16,
    /// Select gop output to DIP
    EN_GOP_GS_MUX = 17,
    /// Select gop output to mux4
    EN_GOP_MUX4  = 18,
    EN_MAX_GOP_MUX_SUPPORT,
} EN_Gop_MuxSel;

/// Define DEBUG level.
typedef enum
{
    /// GOP DEBUG LEVEL LOW. Just printf error message.
    E_GOP_Debug_Level_LOW    = 0,
    /// GOP DEBUG LEVEL Medium. printf warning message and error message.
    E_GOP_Debug_Level_MED    = 1,
    /// GOP DEBUG LEVEL hIGH. printf all message with function.
    E_GOP_Debug_Level_HIGH    = 2,
} EN_GOP_DEBUG_LEVEL;

/// Define GOP bandwidth strength.
typedef enum
{
    /// bandwidth strength: strong
    E_GOP_BW_STRONG,
    /// bandwidth strength: middle
    E_GOP_BW_MIDDLE,
    /// bandwidth strength: weak
    E_GOP_BW_WEAK,
    /// bandwidth strength: error status
    E_GOP_BW_UNKNOWN,
} EN_GOP_BW_STRENGTH;

/// Define GOP gwin fade in/out.
typedef enum
{
    /// GOP gwin fade in.
    E_GOP_GWIN_FADE_IN,
    /// GOP gwin fade out.
    E_GOP_GWIN_FADE_OUT,
    /// GOP gwin fade unknow type.
    E_GOP_GWIN_FADE_UNKNOWN,
} EN_GOP_FADE_TYPE;

/// Scroll direction
typedef enum
{
    E_GOP_SCROLL_NONE = 0,
    E_GOP_SCROLL_UP,      // bottom to top
    E_GOP_SCROLL_DOWN,  // top to bottom
    E_GOP_SCROLL_LEFT,  //right to left
    E_GOP_SCROLL_RIGHT, //left to right
    E_GOP_SCROLL_SW,      //Scroll by SW
    E_GOP_SCROLL_KERNEL,      //Scroll by SW on kernel
} GOP_SCROLL_TYPE;


///the GOP MIXER timing info
typedef struct
{
    MS_U32 hstart;
    MS_U32 hend;
    MS_U32 vstart;
    MS_U32 vend;
    MS_U32 htotal;
}GOP_MixerTiming;

///the GOP MIXER2OP timing info
typedef struct
{
    MS_U32 hstart;
    MS_U32 hend;
    MS_U32 vstart;
    MS_U32 vend;
    MS_U32 htotal;
    MS_U32 hsyncdelay;
}GOP_Mixer2OPTiming;

/// GOP MIXER timing type
typedef enum
{
    GOP_NTSC ,
    GOP_PAL,
    GOP_CUSTOM,
    GOP_CUSTOM_OP,
    GOP_MIXER_TIMEING_MAX,
}GOP_MIXER_TIMINGTYPE;

/// GOP VE timing type
typedef enum
{
    GOP_VE_NTSC ,
    GOP_VE_PAL,
    GOP_VE_TIMEING_MAX,
}GOP_VE_TIMINGTYPE;

typedef enum
{
    GOP_PINPON_G3D ,
    GOP_PINPON_VE,
    GOP_PINPON_DWIN,
    GOP_PINPON_DIP,
}GOP_PINPON_MODE;

typedef struct
{
    MS_BOOL bEnable; //InOut
    MS_U8   u8FrameCount; //Out, value range: 0~3
    MS_U8   u8Result; //Out
}MS_GOP_VECAPTURESTATE, *PMS_GOP_VECAPTURESTATE;

///GOP config type
typedef enum
{
    /// This type is for not init some GOP features.
    /// That is, this is for not changing some registers state
    E_GOP_IGNOREINIT,
    E_GOP_CONSALPHA_BITS,
    E_GOP_TIMING_INFO,
    E_GOP_IS_PIXELBASE_ENABLE,
} EN_GOP_CONFIG_TYPE;

typedef enum
{
    E_GOP_VALID_6BITS             =   0,
    E_GOP_VALID_8BITS             =   1,
} EN_GOP_CONSALPHA_BITS;


/// Define GOP Ignore init value
typedef enum
{
    /// GOP init ingore mux init
    E_GOP_IGNORE_MUX              =   0x0001,
    /// GOP init ingore gwin reset
    E_GOP_IGNORE_GWIN             =   0x0002,
    /// GOP init ingore stretchwin reset
    E_GOP_IGNORE_STRETCHWIN      =   0x0004,
    /// GOP init ingore palette table reset
    E_GOP_IGNORE_PALETTE          =   0x0008,
    /// GOP init ingore rest GOP destination to OP
    E_GOP_IGNORE_SET_DST_OP       =   0x0010,
    /// GOP init ingore enable transparent color key
    E_GOP_IGNORE_ENABLE_TRANSCLR =   0x0020,
    /// GOP set destination ignore VEOSD for bootlogo case
    E_GOP_BOOTLOGO_IGNORE_VEOSDEN =  0x0040,
    /// GOP init ingore all
    E_GOP_IGNORE_ALL              =   0xFFFF,
    ///Not Ingore
    E_GOP_IGNORE_DISABLE          =   0x0000,
} EN_GOP_IGNOREINIT;

//3D OSD mode type
typedef enum
{
    E_GOP_3D_DISABLE ,
    E_GOP_3D_SWITH_BY_FRAME,
    E_GOP_3D_SIDE_BY_SYDE,
    E_GOP_3D_TOP_BOTTOM,
    E_GOP_3D_LINE_ALTERNATIVE,
    E_GOP_3D_FRAMEPACKING,
}EN_GOP_3D_MODETYPE;


//GOP Capability
typedef enum
{
    E_GOP_CAP_WORD_UNIT ,
    E_GOP_CAP_GWIN_NUM,
    E_GOP_CAP_VERSION,
    E_GOP_CAP_RESERVED,
    E_GOP_CAP_CONSALPHA_VALIDBITS,
    E_GOP_CAP_PALETTE,
    E_GOP_CAP_DWIN,
    E_GOP_CAP_GOP_MUX,
}EN_GOP_CAPS;

// GOP palette type
typedef enum
{
    E_GOP_CAP_PAL_SIZE_NONE = 0x0000,
    E_GOP_CAP_PAL_SIZE_256  = 0x0100,
    E_GOP_CAP_PAL_SIZE_64   = 0x0200,
    E_GOP_CAP_PAL_SIZE_MASK = 0x0F00,
}EN_GOP_CAP_PAL;

//GOP Test Pattern type
typedef enum
{
    E_GOP_TP_DISABLE=0,
    E_GOP_TP_GRAY16,
    E_GOP_TP_GRAY16_INVERSE,
    E_GOP_TP_GRAY32,
    E_GOP_TP_GRAY32_INVERSE,
    E_GOP_TP_GRAY64,
    E_GOP_TP_GRAY64_INVERSE,
    E_GOP_TP_GRAY256,
    E_GOP_TP_GRAY256_INVERSE,
    E_GOP_TP_BLACK,
    E_GOP_TP_WHITE,
    E_GOP_TP_CLR,
    E_GOP_TP_BW_DOT,
    E_GOP_TP_BW_LINE,
    E_GOP_TP_BW_CROSS,
    E_GOP_TP_CLR_BAR,
    E_GOP_TP_CLR_BAR_INVERSE,
}EN_GOP_TST_PATTERN;

///Dwin Capability of IC
typedef struct
{
    MS_BOOL bSupportWindowDECapture; //TRUE: Support it; FALSE:Not support, should use FrameDE to capture video
    MS_BOOL bSupportOSDCapture;      //TRUE: Support it; FALSE:Not support
}GOP_DWIN_CAP, *PGOP_DWIN_CAP;

///GOP MUX PRIORITY when gop goes OP
typedef struct
{
    MS_U8 u8MuxNumber;
    MS_U8 *pu8MuxProrityArray;
    MS_BOOL bNewMux;
    MS_BOOL bNeedSetMUX1ToIP0;
    MS_BOOL bNeedSetMUX3ToIP0;
}ST_GOP_MUX_CAP, *PST_GOP_MUX_CAP;

///GOP lib info
typedef struct
{
    MS_U32 GOP_LibVer;
    MS_U32 GOP_BuildNum;
    MS_U32 GOP_ChangeList;
}GOP_LIB_VER, *PGOP_LIB_VER;

///GOP palette info
typedef struct
{
    MS_U32 GOP_NumOfTbl;
    MS_U32 GOP_PalTbl[0x10];
    MS_U32 GOP_PalTblIdx;
}GOP_CAP_PAL_TYPE, *PGOP_CAP_PAL_TYPE;
typedef enum
{
    E_GOP_DWIN_INIT ,
    E_GOP_DWIN_ENABLE ,
    E_GOP_DWIN_ENABLEINTR ,
    E_GOP_DWIN_SRCSLCT ,
    E_GOP_DWIN_ONESHOT ,
    E_GOP_DWIN_ONESHOT2 ,
    E_GOP_DWIN_SET_INFO ,
    E_GOP_DWIN_SET_YUORD ,
    E_GOP_DWIN_GET_BUFSTUS ,
    E_GOP_DWIN_CLR_BUFSTUS ,
    E_GOP_DWIN_SET_SCANTYPE ,
    E_GOP_DWIN_SET_DATAFMT ,
    E_GOP_DWIN_SET_ALPHA ,
    E_GOP_DWIN_SET_R2Y ,
} EN_GOP_DWIN_CNTL;

///GOP timing Information
typedef struct
{
    MS_U16 u16HDTotal;// Output horizontal total
    MS_U16 u16VDTotal; //Output vertical total

    MS_U16 u16DEHStart; //Output DE horizontal start
    MS_U16 u16DEHSize;// Output DE horizontal size

    MS_U16 u16DEVStart; //Output DE vertical start
    MS_U16 u16DEVSize;//Output DE Vertical size

    MS_BOOL bInterlaceMode;
    MS_BOOL bYUVInput;
    MS_BOOL bCLK_EN;
    MS_BOOL bINVALPHA_EN;
}ST_GOP_TIMING_INFO, *PST_GOP_TIMING_INFO;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
//======================================================================================
//  GOP Common utility
//======================================================================================
DLL_PUBLIC E_GOP_API_Result MApi_GOP_Init(GOP_InitInfo *pGopInit);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GetInfo(GOP_ApiInfo* pGopApiInfo);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GetStatus(GOP_ApiStatus *pGopApiSts);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_SetDbgLevel(EN_GOP_DEBUG_LEVEL level);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GetLibVer(const MSIF_Version **ppVersion);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_InitByGOP(GOP_InitInfo *pGopInit, MS_U8 u8GOP);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SwitchGOP(MS_U8 u8GOP);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_Initialize_StretchWindow(MS_U8 u8GOPNum);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_SetGOPClk(MS_U8 gopNum, EN_GOP_DST_TYPE eDstType);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_GetCurrentGOP(void);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_GetMaxGOPNum(void);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_GetGwinNum(MS_U8 u8GopNum);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_GetTotalGwinNum(void);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_PowerOn(void); //temparially naming, maybe change
DLL_PUBLIC E_GOP_API_Result MApi_GOP_PowerOff(void); //temparially naming, maybe change

/******************************************************************************/
/// set GOP power state
/// @param enPowerState\b IN power status
/******************************************************************************/
DLL_PUBLIC E_GOP_API_Result MApi_GOP_SetPowerState(EN_POWER_MODE enPowerState);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_SetGOPBWStrength(EN_GOP_BW_STRENGTH eGOPBWStr, MS_U8 u8GOP);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GetGOPBWStrength(MS_U8 u8GOP, EN_GOP_BW_STRENGTH* curBW);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_SetGOPHStart(MS_U8 u8GOP,MS_U16 u16PanelHStr);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_SetGOPBrightness(MS_U8 u8GOP,MS_U16 u16BriVal,MS_BOOL bMSB);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GetGOPBrightness(MS_U8 u8GOP,MS_U16* u16BriVal,MS_BOOL* bMSB);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_EnableLBCouple(MS_U8 u8GOP, MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_VE_SetOutputTiming(GOP_VE_TIMINGTYPE mode);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_Enable_VEOSD(MS_U8 u8GOP, MS_BOOL bEn);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_MIXER_SetOutputTiming(GOP_MIXER_TIMINGTYPE mode, GOP_MixerTiming *pMT);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_MIXER_SetMIXER2OPOutputTiming(GOP_Mixer2OPTiming *pMT);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_MIXER_EnableVfilter(MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_MIXER_EnableOldBlendMode(MS_U8 u8GOP, MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_RestoreFromVsyncLimitation(void);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_MIUSel(MS_U8 u8GOP, EN_GOP_SEL_TYPE MiuSel);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_SetUVSwap(MS_U8 u8GOP, MS_BOOL bEn);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_SetYCSwap(MS_U8 u8GOP, MS_BOOL bEn);
DLL_PUBLIC MS_U8 MApi_GOP_GetMIUSel(MS_U8 u8GOP);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_SetGOPContrast(MS_U8 u8GOP, MS_U16 u16YContrast, MS_U16 u16UContrast, MS_U16 u16VContrast);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GetGOPContrast(MS_U8 u8GOP, MS_U16* u16YContrast, MS_U16* u16UContrast, MS_U16* u16VContrast);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_EnaVECapture(PMS_GOP_VECAPTURESTATE pstVECapState);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GetVECaptureState(PMS_GOP_VECAPTURESTATE pstVECapState);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_VECaptureWaitOnFrame(PMS_GOP_VECAPTURESTATE pstVECapState);

/*******************************************************************************/
//Set configuration for special cases
///        - This is for special case usage. Do NOT overuse this function
/// @param type \b IN:  Config type
///        - 0: E_GOP_IGNOREINIT,
///		   - 1: E_GOP_CONSALPHA_BITS
/// @param plist \b IN:  Config list for the specific type
//         - This list could be an enum or a structure
//@return GOP_API_SUCCESS - Success
/*******************************************************************************/
DLL_PUBLIC E_GOP_API_Result MApi_GOP_SetConfig(EN_GOP_CONFIG_TYPE type, MS_U32 *plist);

/********************************************************************************/
/// Set config by GOP; For dynamic usage.
/// @param u8GOP \b IN:  GOP number
/// @param enType \b IN:  GOP info type
/// @param pstInfo \b IN misc info
/// @return GOP_API_SUCCESS - Success
/// @return GOP_API_FAIL - Failure
/********************************************************************************/
E_GOP_API_Result MApi_GOP_SetConfigEx(MS_U8 u8Gop, EN_GOP_CONFIG_TYPE enType, MS_U32 *plist);

/********************************************************************************/
/// Get config by GOP.
/// @param u8GOP \b IN:  GOP number
/// @param enType \b IN:  GOP info type
/// @param pstInfo \b IN misc info
/// @return GOP_API_SUCCESS - Success
/// @return GOP_API_FAIL - Failure
/********************************************************************************/
E_GOP_API_Result MApi_GOP_GetConfigEx(MS_U8 u8Gop, EN_GOP_CONFIG_TYPE enType, MS_U32 *plist);

DLL_PUBLIC E_GOP_API_Result MApi_GOP_Set3DOSDMode(MS_U8 u8Gwin, MS_U16 u16MainFBId, MS_U16 u16SubFBId,EN_GOP_3D_MODETYPE en3DMode);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_Set3D_LR_FrameExchange(MS_U8 u8GOP);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_Set_GPIO3DPin(MS_U32 u32GPIO3DPin);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GetChipCaps(EN_GOP_CAPS eCapType, MS_U32* pRet, MS_U32 ret_size);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_TestPattern(EN_GOP_TST_PATTERN eTstPatternType, MS_U32 u32ARGB);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_TestPatternAlpha_Enable(MS_BOOL bTSTAlpha);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_IsRegUpdated(MS_U8 u8GopType);

//======================================================================================
//  GOP GWIN APIs
//======================================================================================
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Enable(MS_U8 winId, MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_EnableTransClr(EN_GOP_TRANSCLR_FMT fmt, MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_EnableTransClr_EX(MS_U8 u8GOP,EN_GOP_TRANSCLR_FMT fmt, MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_EnableProgressive(MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_EnableProgressive_EX(MS_U8 u8GOP,MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_DeleteWin(MS_U8 winId);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_ReleaseWin(MS_U8 gId);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_DestroyWin(MS_U8 gId);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_OutputLayerSwitch(MS_U8 u8GOP);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetMux(GOP_MuxConfig * pGopMuxConfig, MS_U32 u32SizeOfMuxInfo);

/*******************************************************************************/
//Set which OSD Layer select which GOP
//@param pGopLayer \b IN:information about GOP and corresponding Layer
//   #u32LayerCounts: the total GOP/Layer counts to set
//   #stGopLayer[i].u32GopIndex :the GOP which need to change Layer
//   #stGopLayer[i].u32LayerIndex :the GOP corresponding Layer
//@return GOP_API_SUCCESS - Success
/*******************************************************************************/
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetLayer(GOP_LayerConfig *pGopLayer, MS_U32 u32SizeOfLayerInfo);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_OutputColor(EN_GOP_OUTPUT_COLOR type);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_OutputColor_EX(MS_U8 u8GOP,EN_GOP_OUTPUT_COLOR type);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SwapOverlapWin(MS_U8 u8GOP, MS_U8 u8win);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetRelativeWinPrio(MS_U8 u8GOP, GOP_GwinPri *pGwinPri);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Switch2Gwin(MS_U8 winId);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetAlphaInverse(MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetAlphaInverse_EX(MS_U8 u8GOP,MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_GetAlphaInverse(MS_BOOL *bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_GetAlphaInverse_EX(MS_U8 u8GOP,MS_BOOL *bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetPalette(void);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetAlphaValue(MS_U16 * Gwin01AlphaValue, MS_U16 * Gwin23AlphaValue);
DLL_PUBLIC void MApi_GOP_GWIN_SetHScroll(MS_U8 nWinID, MS_U8 nRate, MS_BOOL bEnable);
DLL_PUBLIC void MApi_GOP_GWIN_SetVScroll(MS_U8 nWinID, MS_U8 nRate, MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetScrollRate(MS_U8 u8rate);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetScrollType(MS_U8 u8WinId, GOP_SCROLL_TYPE type,  MS_U16 u16Offset, MS_BOOL bEnable );
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetSWScrollBuffer(MS_U16 bufNum, MS_U32* pBuffer);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetFMT0TransClr(MS_U16 clr);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetFMT0TransClr_EX(MS_U8 u8GOP,MS_U16 clr);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetTransClr_8888(MS_U32 clr, MS_U32 mask);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetTransClr_8888_EX(MS_U8 u8GOP,MS_U32 clr, MS_U32 mask);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_EnableT3DMode(MS_BOOL bEnable);

/********************************************************************************/
/// Set GWIN alpha blending
/// @param u8win \b IN GWIN id
/// @param bEnable \b IN
///   - # TRUE enable pixel alpha
///   - # FALSE disable pixel alpha
/// @param u8coef \b IN alpha blending coefficient (0-7)
/// @return GOP_API_SUCCESS - Success
/// if setting constant alpha blending,please firstly set User_ConsAlpha_bits by calling MApi_GOP_SetConfig(...)
/// example:
/// MS_U32 aConf32[] = {DRV_VALID_8BITS};
/// MApi_GOP_SetConfig(E_GOP_CONSALPHA_BITS,aConf32);
/// MApi_GOP_GWIN_SetBlending(0, FALSE, 0xFF);
/********************************************************************************/
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetBlending(MS_U8 u8win, MS_BOOL bEnable, MS_U8 u8coef);

DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetDuplication(MS_U8 hext, MS_U8 vext);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetWinPosition(MS_U8 winId, MS_U16 dispX, MS_U16 dispY);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetWinPositionOffset(MS_U8 winId, MS_U16 x, MS_U16 y);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetWinProperty(GOP_GwinDispProperty WinProperty);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetGOPDst(MS_U8 u8GOP, EN_GOP_DST_TYPE dsttype);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetBlink(MS_BOOL bEnable, MS_U8 u8rate);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetFieldInver(MS_BOOL enable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetFieldInver_EX(MS_U8 u8GOP,MS_BOOL enable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Set_STRETCHWIN(MS_U8 u8GOP_num, EN_GOP_DST_TYPE eDstType,MS_U16 x, MS_U16 y, MS_U16 width, MS_U16 height);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetStretchWinPosition(MS_U8 u8GOPNum, MS_U16 u16DispX, MS_U16 u16DispY);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetHDisplaySize(MS_U8 gId, MS_U16 Width,MS_U16 X_Start);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetWinInfo(MS_U8 u8win, GOP_GwinInfo* pinfo);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetTransClr(EN_GOP_TRANSCLR_FMT fmt, MS_U16 clr);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetTransClr_EX(MS_U8 u8GOP,EN_GOP_TRANSCLR_FMT fmt, MS_U16 clr);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetWinDispPosition(MS_U8 gId, MS_U16 dispX, MS_U16 dispY);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetHMirror(MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetHMirror_EX(MS_U8 u8GOP,MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetVMirror(MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetVMirror_EX(MS_U8 u8GOP,MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_IsMirrorOn(MS_BOOL *bHMirror, MS_BOOL *bVMirror);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_IsMirrorOn_EX(MS_U8 u8GOP,MS_BOOL *bHMirror, MS_BOOL *bVMirror);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Set_HSCALE(MS_BOOL bEnable, MS_U16 src, MS_U16 dst) ;
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Set_HSCALE_EX(MS_U8 u8GOP,MS_BOOL bEnable, MS_U16 src, MS_U16 dst);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Set_VSCALE(MS_BOOL bEnable, MS_U16 src, MS_U16 dst) ;
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Set_VSCALE_EX(MS_U8 u8GOP,MS_BOOL bEnable, MS_U16 src, MS_U16 dst);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Set_HStretchMode(EN_GOP_STRETCH_HMODE HStrchMode);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Set_HStretchMode_EX(MS_U8 u8GOP,EN_GOP_STRETCH_HMODE HStrchMode);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Set_VStretchMode(EN_GOP_STRETCH_VMODE VStrchMode);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Set_VStretchMode_EX(MS_U8 u8GOP,EN_GOP_STRETCH_VMODE VStrchMode);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Set_TranspColorStretchMode(EN_GOP_STRCH_TRANSPCOLORMODE  TColorStrchMode);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Set_TranspColorStretchMode_EX(MS_U8 u8GOP,EN_GOP_STRCH_TRANSPCOLORMODE  TColorStrchMode);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetForceWrite(MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetBnkForceWrite(MS_U8 u8GOP, MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_GetAlphaValue(MS_U16 * Gwin01AlphaValue, MS_U16 * Gwin23AlphaValue);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_GetWinPosition(MS_U8 winId, MS_U16 * dispX, MS_U16 *dispY);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_GetWinProperty(GOP_GwinDispProperty *WinProperty);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_GetWinAttr(MS_U8 gId, MS_U16 *x0, MS_U16 *y0, MS_U16 *width, MS_U16 *height,  MS_U16 *fbPitch, MS_U16 *fbFmt, MS_U32 *addr, MS_U32 *size);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_GetWinInfo(MS_U8 u8win, GOP_GwinInfo* pinfo);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_UpdateRegOnceEx(MS_BOOL bWriteRegOnce, MS_BOOL bSync);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_UpdateRegOnceEx2(MS_U8 u8GOP,MS_BOOL bWriteRegOnce, MS_BOOL bSync);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_TriggerRegWriteIn(MS_U8 u8win, MS_BOOL bForceWriteIn);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_TriggerRegWriteIn_Ex(MS_U8 u8win, MS_BOOL bForceWriteIn, MS_BOOL bSync);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetFadeInOut(MS_U8 gId, EN_GOP_FADE_TYPE eGwinFadeType, MS_BOOL bEnable, MS_U8 u8FadeRate);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetGWinShared(MS_U8 winId, MS_BOOL bIsShared);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetGWinSharedCnt(MS_U8 winId, MS_U16 u16SharedCnt);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_EnableTileMode(MS_U8 winId, MS_BOOL bEnable, EN_GOP_TILE_DATA_TYPE tiletype );
DLL_PUBLIC E_GOP_API_Result MApi_GOP_SetPINPON(MS_U8 winId, MS_BOOL bEn,GOP_PINPON_MODE PINPON_Mode);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_SetGOPYUV(MS_U8 u8GOP);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_MIXER_SetMux(MS_U8 u8GOP,MS_U8 u8Mux, MS_BOOL bEn);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetNewAlphaMode(MS_U8 gWinId, MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetPreAlphaMode(MS_U8 u8GOP, MS_BOOL bEnble);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_CreateWin(MS_U16 width, MS_U16 height, MS_U16 fbFmt);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_CreateWin2(MS_U16 width, MS_U16 height, MS_U16 fbFmt, EN_GOP_FRAMEBUFFER_STRING FBString);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_CreateWin_Assign_FB(MS_U8 u8GOP, MS_U8 FBId, MS_U16 dispX, MS_U16 dispY);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_CreateWin_Assign_32FB(MS_U8 u8GOP, MS_U32 u32FBId, MS_U16 dispX, MS_U16 dispY);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_CreateStaticWin(MS_U8 u8WinId, MS_U16 width, MS_U16 height, MS_U16 fbFmt);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_CreateStaticWin2(MS_U8 u8WinId, MS_U16 width, MS_U16 height, MS_U16 fbFmt, EN_GOP_FRAMEBUFFER_STRING FBString);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_CreateStaticWin_Assign_FB(MS_U8 u8WinId, MS_U8 u8GOP, MS_U8 FBId, MS_U16 dispX, MS_U16 dispY);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_CreateStaticWin_Assign_32FB(MS_U8 u8WinId, MS_U8 u8GOP, MS_U32 u32FBId, MS_U16 dispX, MS_U16 dispY);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_IsGwinExist(MS_U8 gId);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_GetFreeWinID(void);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_GetMAXWinID(void);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_GetCurrentWinId(void);
DLL_PUBLIC MS_U16 MApi_GOP_GWIN_GetMaxActiveGwin_v(void);
DLL_PUBLIC MS_U16 MApi_GOP_GWIN_Get_HSTART(void);
DLL_PUBLIC MS_U16 MApi_GOP_GWIN_GetActiveGWIN(void);
DLL_PUBLIC MS_U16 MApi_GOP_GWIN_GetMaxVEnd(MS_BOOL bActive);
DLL_PUBLIC MS_BOOL MApi_GOP_GWIN_IsAllGWINDisabled(void);
DLL_PUBLIC MS_BOOL MApi_GOP_GWIN_IsGWINEnabled(MS_U8 winId);
DLL_PUBLIC MS_BOOL MApi_GOP_GWIN_IsEnabled(void);
DLL_PUBLIC MS_BOOL MApi_GOP_GWIN_CheckOpmodeIsOn(void);
DLL_PUBLIC MS_BOOL MApi_GOP_GWIN_CheckOpmodeIsOn_EX(MS_U8 u8GOP);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetResolution(MS_U8 u8GwinId, MS_U8 u8FbId, GOP_GwinInfo* pGwinInfo, GOP_StretchInfo* pStretchInfo, EN_GOP_STRETCH_DIRECTION direction, MS_U16 u16DstWidth, MS_U16 u16DstHeight);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetResolution_32FB(MS_U8 u8GwinId, MS_U32 u32FbId, GOP_GwinInfo* pGwinInfo, GOP_StretchInfo* pStretchInfo, EN_GOP_STRETCH_DIRECTION direction, MS_U16 u16DstWidth, MS_U16 u16DstHeight);
DLL_PUBLIC void MApi_GOP_Exit(void);


//======================================================================================
//  GOP FB management
//======================================================================================
DLL_PUBLIC E_GOP_API_Result MApi_GOP_FB_SEL(MS_U8 u8FB);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetDoubleHeap(MS_U32 u32DblHeapAdr, MS_U32 u32DblHeapLen);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_MapFB2Win(MS_U8 fbId, MS_U8 gwinId);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Map32FB2Win(MS_U32 u32fbId, MS_U8 u8gwinId);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Switch2FB(MS_U8 fbId);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Switch2_32FB(MS_U32 u32fbId);
DLL_PUBLIC MS_BOOL MApi_GOP_Switch_GWIN_2_FB(MS_U8 gWinId, MS_U8 fbId, MS_U16 u16WaitTagID, MS_U16 *pU16QueueCnt);
DLL_PUBLIC MS_BOOL MApi_GOP_Switch_GWIN_2_32FB(MS_U8 gWinId, MS_U32 u32fbId, MS_U32 u32WaitTagID, MS_U32 *pU32QueueCnt);
DLL_PUBLIC MS_BOOL MApi_GOP_Switch_GWIN_2_FB_BY_ADDR(MS_U8 gWinId, MS_U32 u32FlipAddr, MS_U16 u16WaitTagID, MS_U16 *pU16QueueCnt);
DLL_PUBLIC MS_BOOL MApi_GOP_Switch_3DGWIN_2_FB_BY_ADDR(MS_U8 gWinId, MS_U32 u32MainFlipAddr, MS_U32 u32SubFlipAddr, MS_U16 u16WaitTagID, MS_U16 *pU16QueueCnt);
DLL_PUBLIC MS_BOOL MApi_GOP_Switch_Multi_GWIN_2_FB_BY_ADDR(GOP_MultiFlipInfo GopMultiFlipInfo);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_DeleteFB(MS_U8 fbId);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Delete32FB(MS_U32 u32fbId);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_GetFBRegion(MS_U8 fbID, MS_U16 *pX,MS_U16 *pY, MS_U16 *pW, MS_U16 *pH);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Get32FBRegion(MS_U32 u32fbID, MS_U16 *pX, MS_U16 *pY, MS_U16 *pW, MS_U16 *pH);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_GetFBPosition(MS_U8 fbID, MS_U16 *pX,MS_U16 *pY);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Get32FBPosition(MS_U32 u32fbID, MS_U16 *pX, MS_U16 *pY);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetFBInfo(MS_U8 fbId, GOP_GwinFBAttr *fbAttr);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Set32FBInfo(MS_U32 u32fbId, GOP_GwinFBAttr *fbAttr);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_GetFBInfo(MS_U8 fbId, GOP_GwinFBAttr *fbAttr);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Get32FBInfo(MS_U32 u32fbId, GOP_GwinFBAttr *fbAttr);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_GetFBAddr(MS_U8 fbID, MS_U32 *pAddr);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Get32FBAddr(MS_U32 u32fbID, MS_U32 *pAddr);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_ClearFlipQueue(MS_U8 gWinId);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_GetMaxFBNum(void);
DLL_PUBLIC MS_U32 MApi_GOP_GWIN_GetMax32FBNum(void);
DLL_PUBLIC MS_U8 MApi_GOP_FB_Get(void);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_GetMAXFBID(void);
DLL_PUBLIC MS_U32 MApi_GOP_GWIN_GetMAX32FBID(void);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_DestroyFB(MS_U8 fbId);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_Destroy32FB(MS_U32 u32fbId);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_CreateFBFrom3rdSurf(MS_U16 width, MS_U16 height,  MS_U16 fbFmt, MS_U32 u32FbAddr, MS_U16 pitch, MS_U8* ret_FBId);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_Create32FBFrom3rdSurf(MS_U16 width, MS_U16 height,  MS_U16 fbFmt, MS_U32 u32FbAddr, MS_U16 pitch, MS_U32* u32ret_FBId);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_CreateFBbyStaticAddr(MS_U8 fbId, MS_U16 dispX, MS_U16 dispY, MS_U16 width, MS_U16 height,  MS_U16 fbFmt, MS_U32 u32FbAddr );
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_Create32FBbyStaticAddr(MS_U32 u32fbId, MS_U16 dispX, MS_U16 dispY, MS_U16 width, MS_U16 height,  MS_U16 fbFmt, MS_U32 u32FbAddr);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_CreateFBbyStaticAddr2(MS_U8 fbId, MS_U16 dispX, MS_U16 dispY, MS_U16 width, MS_U16 height,  MS_U16 fbFmt, MS_U32 u32FbAddr, EN_GOP_FRAMEBUFFER_STRING FBString);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_Create32FBbyStaticAddr2(MS_U32 u32fbId, MS_U16 dispX, MS_U16 dispY, MS_U16 width, MS_U16 height,  MS_U16 fbFmt, MS_U32 u32FbAddr ,EN_GOP_FRAMEBUFFER_STRING FBString);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_CreateFB2(MS_U8 FBId,MS_U16 x, MS_U16 y, MS_U16 width, MS_U16 height, MS_U16 fbFmt);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_Create32FB2(MS_U32 u32FBId, MS_U16 x, MS_U16 y, MS_U16 width, MS_U16 height, MS_U16 fbFmt);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_CreateFB2_EXT(MS_U8 FBId, MS_U16 x, MS_U16 y, MS_U16 width, MS_U16 height, MS_U16 fbFmt, EN_GOP_FRAMEBUFFER_STRING FBString);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_Create32FB2_EXT(MS_U32 u32FBId, MS_U16 x, MS_U16 y, MS_U16 width, MS_U16 height, MS_U16 fbFmt, EN_GOP_FRAMEBUFFER_STRING FBString);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_GetCurrentFBID(void);
DLL_PUBLIC MS_U32 MApi_GOP_GWIN_GetCurrent32FBID(void);
DLL_PUBLIC MS_U8  MApi_GOP_GWIN_GetFBfromGWIN(MS_U8 gwinId) ;
DLL_PUBLIC MS_U32 MApi_GOP_GWIN_Get32FBfromGWIN(MS_U8 gwinId);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_IsFBExist(MS_U8 fbId);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_Is32FBExist(MS_U32 u32fbId);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_GetFreeFBID(void);
DLL_PUBLIC MS_U32 MApi_GOP_GWIN_GetFree32FBID(void);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_CreateFB(MS_U8 fbId, MS_U16 dispX, MS_U16 dispY, MS_U16 width, MS_U16 height,  MS_U16 fbFmt);
DLL_PUBLIC MS_U8 MApi_GOP_GWIN_Create32FB(MS_U32 u32fbId, MS_U16 dispX, MS_U16 dispY, MS_U16 width, MS_U16 height, MS_U16 fbFmt);
DLL_PUBLIC MS_U16 MApi_GOP_GWIN_GetFBFmt(MS_U8 fbId);
DLL_PUBLIC MS_U16 MApi_GOP_GWIN_Get32FBFmt(MS_U32 u32fbId);



//======================================================================================
//  GOP Palette setting
//======================================================================================
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetPaletteOpt( GOP_PaletteEntry *pPalArray, MS_U16 u32PalStart, MS_U16 u32PalEnd, EN_GOP_PALETTE_TYPE ePalType);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetPaletteOpt_EX(MS_U8 u8GOP,GOP_PaletteEntry *pPalArray, MS_U16 u32PalStart, MS_U16 u32PalEnd, EN_GOP_PALETTE_TYPE ePalType);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetPaletteRead(EN_GOP_PALETTE_READTYPE type);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_SetPaletteRead_EX(MS_U8 u8GOP,EN_GOP_PALETTE_READTYPE type);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_ReadPalette(MS_U8 idx, MS_U32* clr);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_ReadPalette_EX(MS_U8 u8GOP,MS_U8 idx, MS_U32* clr);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_2GSetPaletteOpt(GOP_PaletteEntry *pPalArray, MS_U16 u32PalStart, MS_U16 u32PalEnd);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_2GSetPaletteOpt_EX(MS_U8 u8GOP,GOP_PaletteEntry *pPalArray, MS_U16 u32PalStart, MS_U16 u32PalEnd);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_2GSetPaletteRead(EN_GOP_PALETTE_READTYPE type);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_2GSetPaletteRead_EX(MS_U8 u8GOP,EN_GOP_PALETTE_READTYPE type);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_2GReadPalette(MS_U8 idx, MS_U32* clr);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_2GReadPalette_EX(MS_U8 u8GOP,MS_U8 idx, MS_U32* clr);


//======================================================================================
//  GOP DWIN APIs
//======================================================================================
DLL_PUBLIC E_GOP_API_Result MApi_GOP_DWIN_Init(void);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_DWIN_SetSourceSel(EN_GOP_DWIN_SRC_SEL enSrcSel);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_DWIN_CaptureOneFrame2(void);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_DWIN_EnableIntr(MS_U16 u8mask, MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_DWIN_CaptureOneFrame(void);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_DWIN_Enable(MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_DWIN_GetWinProperty(GOP_DwinProperty *pproperty);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_DWIN_SetWinProperty(GOP_DwinProperty *pproperty);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_DWIN_SelectSourceScanType(EN_GOP_DWIN_SCAN_MODE enScanMode);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_DWIN_SetDataFmt(EN_GOP_DWIN_DATA_FMT fmt);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_DWIN_SetAlphaValue(MS_U8 u8AlphaVal);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_DWIN_SetAlphaSrc(EN_GOP_DWIN_ALPHA_SRC source);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_DWIN_SetAlphaInverse(MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_DWIN_SetUVSample(EN_GOP_DWIN_UVSAMPLE_Mode mode);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_DWIN_SetSkipFrame(MS_U32 framecount);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_DWIN_ClearIntr(MS_U16 u8mask);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_DWIN_GetDWinIntInfo(GOP_DWinIntInfo *pDWinIntInfo);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_DWIN_GetDWinIntInfoTimeout(GOP_DWinIntInfo *pDWinIntInfo, MS_U32 u32Timeout);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_SetClkForCapture(void);   //only for source is OP path clock
DLL_PUBLIC MS_U16 MApi_GOP_DWIN_GetIntrStatus(void);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_DWIN_EnableR2YCSC(MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_DWIN_SetUVSwap(MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_BeginDraw(void);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_EndDraw(void);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Enable_BGWIN(MS_U8 bgwID, MS_BOOL bEnable);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Set_BGWIN(MS_U8 bgwID, MS_U16 x0, MS_U16 y0, MS_U16 w, MS_U16 h, MS_U16 color);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_Set_BGWIN_Alpha(MS_U8 bgwID, MS_BOOL bEnable, MS_U8 alpha);
DLL_PUBLIC E_GOP_API_Result MApi_GOP_DWIN_SetBufferPINPON(MS_U32 u32fbaddr0,MS_U32 u32fbaddr1);
//======================================================================================
//  GOP  CallBack Functions
//======================================================================================
DLL_PUBLIC E_GOP_API_Result MApi_GOP_RegisterFBFmtCB(MS_U32 (*fpGOP_CB)(MS_U16 pitch,MS_U32 addr , MS_U16 fmt )  );
DLL_PUBLIC E_GOP_API_Result MApi_GOP_RegisterXCIsInterlaceCB(MS_BOOL (*fpGOP_CB)(void));
DLL_PUBLIC E_GOP_API_Result MApi_GOP_RegisterXCGetCapHStartCB(MS_U16 (*fpGOP_CB)(void));
DLL_PUBLIC E_GOP_API_Result MApi_GOP_RegisterXCReduceBWForOSDCB(void (*fpGOP_CB)(MS_U8 PqWin, MS_BOOL enable));
DLL_PUBLIC E_GOP_API_Result MApi_GOP_RegisterEventNotify(void (*fpGOP_CB)(MS_U32 u32EventID, void* reserved0));
DLL_PUBLIC E_GOP_API_Result MApi_GOP_RegisterXCSetDwinInfo(MS_BOOL (*fpGOP_CB)(MS_U16 cmd,MS_U32 *arg,MS_U16 size));

//======================================================================================
//  OC
//======================================================================================
DLL_PUBLIC E_GOP_API_Result MApi_GOP_OC_SetOCFBinfo(MS_PHYADDR u32Addr, EN_GOP_OC_SEL_TYPE BankMode, MS_U32 enBufSize);


//================================ Obsolete Function Start =======================================
//-------------------------------------------------------------------------------------------------
/// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  Alert !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  Alert !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/// !!! below function will be "REMOVED" or "REFACTORING" later, please do not use it !!!!!!!!!
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC E_GOP_API_Result MApi_GOP_GWIN_UpdateRegOnce(MS_BOOL bWriteRegOnce);

#ifdef __cplusplus
}
#endif

#endif // _API_GOP_H_

