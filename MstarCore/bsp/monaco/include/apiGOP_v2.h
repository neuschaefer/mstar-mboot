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

#ifndef _GOP_H_
#define _GOP_H_

#include "MsTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
/// GOP Version

#define DWIN_SUPPORT_BUFFER     0x2
#define GOP_MULTIINFO_NUM       8

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


///GOP config type
typedef enum
{
    /// This type is for not init some GOP features.
    /// That is, this is for not changing some registers state
    E_GOP_IGNOREINIT,
    E_GOP_CONSALPHA_BITS,
    E_GOP_TIMING_INFO,
    E_GOP_IS_PIXELBASE_ENABLE,
    E_GOP_GET_MAXFBNUM,
} EN_GOP_CONFIG_TYPE;

/// Transparent color format
typedef enum
{
    /// RGB mode transparent color.
    GOPTRANSCLR_FMT0,
    /// index mode transparent color.
    GOPTRANSCLR_FMT1,
    /// ARGB8888 mode transparent color.
    GOPTRANSCLR_FMT2,
} EN_GOP_TRANSCLR_FMT;


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

typedef enum
{
    E_GOP_GPU_TILE_LINEAR=0,
    E_GOP_GPU_TILE_DIP8X,
    E_GOP_GPU_TILE_DIP16X,
    E_GOP_GPU_TILE_GPU,
}EN_GOP_GPU_TILE_MODE;

/// Define palette color format.
typedef enum
{
    /// Palette color format is ARGB8888.
    E_GOP_PAL_ARGB8888    = 0,
    /// Invalid palette color format.
    E_GOP_PAL_INVALID
} EN_GOP_PALETTE_TYPE;

typedef enum
{
    E_GOP_4G_PALETTE,
    E_GOP_2G_PALETTE,
}EN_GOP_PALETTE;

/// DWIN scan mode
typedef enum
{
    /// progessive.
    DWIN_SCAN_MODE_PROGRESSIVE,
    /// interlace.
    DWIN_SCAN_MODE_extern,
} EN_GOP_DWIN_SCAN_MODE;

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

/// Define GOP Transparent color Stretch Mode.
typedef enum
{
    E_GOP_TRANSPCOLOR_STRCH_DUPLICATE = 0,
    E_GOP_TRANSPCOLOR_STRCH_ASNORMAL = 1,
} EN_GOP_STRCH_TRANSPCOLORMODE;

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
    /// 4-tap filer
    E_GOP_HSTRCH_4TAPE         = 0xA,
    ///2-tape
    E_GOP_HSTRCH_2TAPE         = 0xB,
} EN_GOP_STRETCH_HMODE;

/// Define GOP V-Stretch mode.
typedef enum
{
    ///2-TAP mode.
    E_GOP_VSTRCH_LINEAR = 0,
    /// duplicate mode.
    E_GOP_VSTRCH_DUPLICATE = 1,
    /// nearest mode.
    E_GOP_VSTRCH_NEAREST = 2,
    /// nearest mode.
    E_GOP_VSTRCH_LINEAR_GAIN0 = 3,
    E_GOP_VSTRCH_LINEAR_GAIN1 = 4,
    /// Linear
    E_GOP_VSTRCH_LINEAR_GAIN2 = 5,
} EN_GOP_STRETCH_VMODE;


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

//PINPON
typedef enum
{
    E_GOP_PINPON_G3D ,
    E_GOP_PINPON_VE,
    E_GOP_PINPON_DWIN,
    E_GOP_PINPON_DIP,
} EN_GOP_PINPON_MODE;

/// GOP MIXER timing type
typedef enum
{
    GOP_NTSC ,
    GOP_PAL,
    GOP_CUSTOM,
    GOP_CUSTOM_OP,
    GOP_MIXER_TIMEING_MAX,
}GOP_MIXER_TIMINGTYPE;


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


/// GOP VE timing type
typedef enum
{
    GOP_VE_NTSC ,
    GOP_VE_PAL,
    GOP_VE_TIMEING_MAX,
}GOP_VE_TIMINGTYPE;


///Define OC Bank Mode SEL
typedef enum
{
    /// SEL 2 memory bank Mode
    E_GOP_OC_SEL_2BankMode   = 1,
    /// SEL 4 memory bank Mode
    E_GOP_OC_SEL_4BankMode   = 2 ,
} EN_GOP_OC_SEL_TYPE;


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

typedef enum
{
    GOP_DWIN_SEL0,  //add this for extend the dwin number in the future
}EN_GOP_DWIN_SEL;
//===================================================
//struct
//===================================================

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

/// Define GOP Gwin Relative Priority setting info
typedef struct
{
    ///The valid number of below setting. Since Relative Priority, Must larger than 1 and smaller than 5
    /// 2 means u81stGwin & u82stGwin valid, 3 means u81stGwin, u82stGwin, u83stGwin valid
    /// 4 means all valid.
    MS_U8 u8GwinNum;
    MS_U8 u8GwinPri[4];
}GOP_GwinPri;

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

#ifdef __cplusplus
}
#endif

#endif // _API_GOP_H_

