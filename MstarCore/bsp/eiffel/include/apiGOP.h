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



#ifdef __cplusplus
extern "C"
{
#endif
//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
/// GOP Version
#define MSIF_GOP_LIB_CODE                   {'G','O','P','_'}    //Lib code
#define MSIF_GOP_LIBVER                     {'8','8'}            //LIB version
#define MSIF_GOP_BUILDNUM                   {'0','4'}            //Build Number
#define MSIF_GOP_CHANGELIST                 {'0','0','6','4','3','2','0','0'} //P4 ChangeList Number

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

//#define MAX_GOP_SUPPORT MApi_GOP_GWIN_GetMaxGOPNum()

#define GOP0_GWIN_START 0
#define GOP1_GWIN_START MAX_GOP0_SUPPORT
#define GOP2_GWIN_START MAX_GOP0_SUPPORT + MAX_GOP1_SUPPORT
#define GOP3_GWIN_START MAX_GOP0_SUPPORT + MAX_GOP1_SUPPORT + MAX_GOP2_SUPPORT


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
    E_GOP_COLOR_RGB555_BLINK    =0,
    /// Color format RGB565.
    E_GOP_COLOR_RGB565          =1,
    /// Color format ARGB4444.
    E_GOP_COLOR_ARGB4444        =2,
    /// Color format alpha blink.
    E_GOP_COLOR_2266      =3,
    /// Color format I8 (256-entry palette).
    E_GOP_COLOR_I8              =4,
    /// Color format ARGB8888.
    E_GOP_COLOR_ARGB8888        =5,
    /// Color format ARGB1555.
    E_GOP_COLOR_ARGB1555        =6,
    /// Color format ABGR8888.    - Andriod Format
    E_GOP_COLOR_ABGR8888        =7,
    /// Color format RGB555/YUV422.
    E_GOP_COLOR_RGB555YUV422    =8,
    /// Color format YUV422.
    E_GOP_COLOR_YUV422          =9,
    /// Color format RGBA5551.    - Andriod Format
    E_GOP_COLOR_RGBA5551        =10,
    /// Color format RGBA4444.    - Andriod Format
    E_GOP_COLOR_RGBA4444        =11,
    /// Invalid color format.
    E_GOP_COLOR_INVALID
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
    DWIN_SRC_MAX = 3,
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
    EN_GOP_DST_TYPE eGOPNumDstType[4];
    /// gop stretch window h size status. (0xFF represent not support)
    MS_U16 u16GopNumStrWinHSize[4];
    /// gop stretch window v size status. (0xFF represent not support)
    MS_U16 u16GopNumStrWinVSize[4];

    /// gop0 gwin status (Is gwin enable?).  (gop0 gwin ID: 0~3)
    MS_BOOL Gop0GwinIsEnable[4];
    /// gop1 gwin status (Is gwin enable?).  (gop1 gwin ID: 4~5)
    MS_BOOL Gop1GwinIsEnable[2];
    /// gop2 gwin status (Is gwin enable?)   (gop2 gwin ID: 6)
    MS_BOOL Gop2GwinIsEnable;
    /// gop3 gwin status (Is gwin enable?)   (gop2 gwin ID: 7)
    MS_BOOL Gop3GwinIsEnable;
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
    /// GOP init ingore all
    E_GOP_IGNORE_ALL              =   0xFFFF,
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

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
//======================================================================================
//  GOP Common utility
//======================================================================================
E_GOP_API_Result MApi_GOP_Init(GOP_InitInfo *pGopInit);
E_GOP_API_Result MApi_GOP_GetInfo(GOP_ApiInfo* pGopApiInfo);
E_GOP_API_Result MApi_GOP_GetStatus(GOP_ApiStatus *pGopApiSts);
E_GOP_API_Result MApi_GOP_SetDbgLevel(EN_GOP_DEBUG_LEVEL level);
E_GOP_API_Result MApi_GOP_GetLibVer(const MSIF_Version **ppVersion);
E_GOP_API_Result MApi_GOP_InitByGOP(GOP_InitInfo *pGopInit, MS_U8 u8GOP);
E_GOP_API_Result MApi_GOP_GWIN_SwitchGOP(MS_U8 u8GOP);
E_GOP_API_Result MApi_GOP_Initialize_StretchWindow(MS_U8 u8GOPNum);
E_GOP_API_Result MApi_GOP_SetGOPClk(MS_U8 gopNum, EN_GOP_DST_TYPE eDstType);
MS_U8 MApi_GOP_GWIN_GetCurrentGOP(void);
MS_U8 MApi_GOP_GWIN_GetMaxGOPNum(void);
MS_U8 MApi_GOP_GWIN_GetGwinNum(MS_U8 u8GopNum);
MS_U8 MApi_GOP_GWIN_GetTotalGwinNum(void);
E_GOP_API_Result MApi_GOP_PowerOn(void); //temparially naming, maybe change
E_GOP_API_Result MApi_GOP_PowerOff(void); //temparially naming, maybe change
E_GOP_API_Result MApi_GOP_SetGOPBWStrength(EN_GOP_BW_STRENGTH eGOPBWStr, MS_U8 u8GOP);
E_GOP_API_Result MApi_GOP_GetGOPBWStrength(MS_U8 u8GOP, EN_GOP_BW_STRENGTH* curBW);
E_GOP_API_Result MApi_GOP_SetGOPHStart(MS_U8 u8GOP,MS_U16 u16PanelHStr);
E_GOP_API_Result MApi_GOP_SetGOPBrightness(MS_U8 u8GOP,MS_U16 u16BriVal,MS_BOOL bMSB);
E_GOP_API_Result MApi_GOP_GetGOPBrightness(MS_U8 u8GOP,MS_U16* u16BriVal,MS_BOOL* bMSB);
E_GOP_API_Result MApi_GOP_EnableLBCouple(MS_U8 u8GOP, MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_VE_SetOutputTiming(GOP_VE_TIMINGTYPE mode);
E_GOP_API_Result MApi_GOP_MIXER_SetOutputTiming(GOP_MIXER_TIMINGTYPE mode, GOP_MixerTiming *pMT);
E_GOP_API_Result MApi_GOP_MIXER_SetMIXER2OPOutputTiming(GOP_Mixer2OPTiming *pMT);
E_GOP_API_Result MApi_GOP_RestoreFromVsyncLimitation(void);
E_GOP_API_Result MApi_GOP_MIUSel(MS_U8 u8GOP, EN_GOP_SEL_TYPE MiuSel);
E_GOP_API_Result MApi_GOP_SetUVSwap(MS_U8 u8GOP, MS_BOOL bEn);
E_GOP_API_Result MApi_GOP_SetYCSwap(MS_U8 u8GOP, MS_BOOL bEn);
MS_U8 MApi_GOP_GetMIUSel(MS_U8 u8GOP);
E_GOP_API_Result MApi_GOP_SetGOPContrast(MS_U8 u8GOP, MS_U16 u16YContrast, MS_U16 u16UContrast, MS_U16 u16VContrast);
E_GOP_API_Result MApi_GOP_GetGOPContrast(MS_U8 u8GOP, MS_U16* u16YContrast, MS_U16* u16UContrast, MS_U16* u16VContrast);
E_GOP_API_Result MApi_GOP_EnaVECapture(PMS_GOP_VECAPTURESTATE pstVECapState);
E_GOP_API_Result MApi_GOP_GetVECaptureState(PMS_GOP_VECAPTURESTATE pstVECapState);
E_GOP_API_Result MApi_GOP_VECaptureWaitOnFrame(PMS_GOP_VECAPTURESTATE pstVECapState);
E_GOP_API_Result MApi_GOP_SetConfig(EN_GOP_CONFIG_TYPE type, MS_U32 *plist);
E_GOP_API_Result MApi_GOP_Set3DOSDMode(MS_U8 u8Gwin, MS_U16 u16MainFBId, MS_U16 u16SubFBId,EN_GOP_3D_MODETYPE en3DMode);
E_GOP_API_Result MApi_GOP_Set3D_LR_FrameExchange(MS_U8 u8GOP);
E_GOP_API_Result MApi_GOP_Set_GPIO3DPin(MS_U32 u32GPIO3DPin);
E_GOP_API_Result MApi_GOP_GetChipCaps(EN_GOP_CAPS eCapType, MS_U32* pRet, MS_U32 ret_size);
E_GOP_API_Result MApi_GOP_TestPattern(EN_GOP_TST_PATTERN eTstPatternType, MS_U32 u32ARGB);
E_GOP_API_Result MApi_GOP_TestPatternAlpha_Enable(MS_BOOL bTSTAlpha);
E_GOP_API_Result MApi_GOP_IsRegUpdated(MS_U8 u8GopType);

//======================================================================================
//  GOP GWIN APIs
//======================================================================================
E_GOP_API_Result MApi_GOP_GWIN_Enable(MS_U8 winId, MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_EnableTransClr(EN_GOP_TRANSCLR_FMT fmt, MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_EnableProgressive(MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_DeleteWin(MS_U8 winId);
E_GOP_API_Result MApi_GOP_GWIN_ReleaseWin(MS_U8 gId);
E_GOP_API_Result MApi_GOP_GWIN_DestroyWin(MS_U8 gId);
E_GOP_API_Result MApi_GOP_GWIN_OutputLayerSwitch(MS_U8 u8GOP);
E_GOP_API_Result MApi_GOP_GWIN_SetMux(GOP_MuxConfig * pGopMuxConfig, MS_U32 u32SizeOfMuxInfo);
E_GOP_API_Result MApi_GOP_GWIN_OutputColor(EN_GOP_OUTPUT_COLOR type);
E_GOP_API_Result MApi_GOP_GWIN_SwapOverlapWin(MS_U8 u8GOP, MS_U8 u8win);
E_GOP_API_Result MApi_GOP_GWIN_SetRelativeWinPrio(MS_U8 u8GOP, GOP_GwinPri *pGwinPri);
E_GOP_API_Result MApi_GOP_GWIN_Switch2Gwin(MS_U8 winId);
E_GOP_API_Result MApi_GOP_GWIN_SetAlphaInverse(MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_GetAlphaInverse(MS_BOOL *bEnable);
E_GOP_API_Result MApi_GOP_GWIN_SetPalette(void);
E_GOP_API_Result MApi_GOP_GWIN_SetAlphaValue(MS_U16 * Gwin01AlphaValue, MS_U16 * Gwin23AlphaValue);
void MApi_GOP_GWIN_SetHScroll(MS_U8 nWinID, MS_U8 nRate, MS_BOOL bEnable);
void MApi_GOP_GWIN_SetVScroll(MS_U8 nWinID, MS_U8 nRate, MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_SetScrollRate(MS_U8 u8rate);
E_GOP_API_Result MApi_GOP_GWIN_SetScrollType(MS_U8 u8WinId, GOP_SCROLL_TYPE type,  MS_U16 u16Offset, MS_BOOL bEnable );
E_GOP_API_Result MApi_GOP_GWIN_SetSWScrollBuffer(MS_U16 bufNum, MS_U32* pBuffer);
E_GOP_API_Result MApi_GOP_GWIN_SetFMT0TransClr(MS_U16 clr);
E_GOP_API_Result MApi_GOP_GWIN_SetTransClr_8888(MS_U32 clr, MS_U32 mask);
E_GOP_API_Result MApi_GOP_GWIN_SetBlending(MS_U8 u8win, MS_BOOL bEnable, MS_U8 u8coef);
E_GOP_API_Result MApi_GOP_GWIN_SetDuplication(MS_U8 hext, MS_U8 vext);
E_GOP_API_Result MApi_GOP_GWIN_SetWinPosition(MS_U8 winId, MS_U16 dispX, MS_U16 dispY);
E_GOP_API_Result MApi_GOP_GWIN_SetWinPositionOffset(MS_U8 winId, MS_U16 x, MS_U16 y);
E_GOP_API_Result MApi_GOP_GWIN_SetWinProperty(GOP_GwinDispProperty WinProperty);
E_GOP_API_Result MApi_GOP_GWIN_SetGOPDst(MS_U8 u8GOP, EN_GOP_DST_TYPE dsttype);
E_GOP_API_Result MApi_GOP_GWIN_SetBlink(MS_BOOL bEnable, MS_U8 u8rate);
E_GOP_API_Result MApi_GOP_GWIN_SetFieldInver(MS_BOOL enable);
E_GOP_API_Result MApi_GOP_GWIN_Set_STRETCHWIN(MS_U8 u8GOP_num, EN_GOP_DST_TYPE eDstType,MS_U16 x, MS_U16 y, MS_U16 width, MS_U16 height);
E_GOP_API_Result MApi_GOP_GWIN_SetStretchWinPosition(MS_U8 u8GOPNum, MS_U16 u16DispX, MS_U16 u16DispY);
E_GOP_API_Result MApi_GOP_GWIN_SetHDisplaySize(MS_U8 gId, MS_U16 Width,MS_U16 X_Start);
E_GOP_API_Result MApi_GOP_GWIN_SetWinInfo(MS_U8 u8win, GOP_GwinInfo* pinfo);
E_GOP_API_Result MApi_GOP_GWIN_SetTransClr(EN_GOP_TRANSCLR_FMT fmt, MS_U16 clr);
E_GOP_API_Result MApi_GOP_GWIN_SetWinDispPosition(MS_U8 gId, MS_U16 dispX, MS_U16 dispY);
E_GOP_API_Result MApi_GOP_GWIN_SetHMirror(MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_SetVMirror(MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_IsMirrorOn(MS_BOOL *bHMirror, MS_BOOL *bVMirror);
E_GOP_API_Result MApi_GOP_GWIN_Set_HSCALE(MS_BOOL bEnable, MS_U16 src, MS_U16 dst) ;
E_GOP_API_Result MApi_GOP_GWIN_Set_VSCALE(MS_BOOL bEnable, MS_U16 src, MS_U16 dst) ;
E_GOP_API_Result MApi_GOP_GWIN_Set_HStretchMode(EN_GOP_STRETCH_HMODE HStrchMode);
E_GOP_API_Result MApi_GOP_GWIN_Set_VStretchMode(EN_GOP_STRETCH_VMODE VStrchMode);
E_GOP_API_Result MApi_GOP_GWIN_Set_TranspColorStretchMode(EN_GOP_STRCH_TRANSPCOLORMODE  TColorStrchMode);
E_GOP_API_Result MApi_GOP_GWIN_SetForceWrite(MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_SetBnkForceWrite(MS_U8 u8GOP, MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_GetAlphaValue(MS_U16 * Gwin01AlphaValue, MS_U16 * Gwin23AlphaValue);
E_GOP_API_Result MApi_GOP_GWIN_GetWinPosition(MS_U8 winId, MS_U16 * dispX, MS_U16 *dispY);
E_GOP_API_Result MApi_GOP_GWIN_GetWinProperty(GOP_GwinDispProperty *WinProperty);
E_GOP_API_Result MApi_GOP_GWIN_GetWinAttr(MS_U8 gId, MS_U16 *x0, MS_U16 *y0, MS_U16 *width, MS_U16 *height,  MS_U16 *fbPitch, MS_U16 *fbFmt, MS_U32 *addr, MS_U32 *size);
E_GOP_API_Result MApi_GOP_GWIN_GetWinInfo(MS_U8 u8win, GOP_GwinInfo* pinfo);
E_GOP_API_Result MApi_GOP_GWIN_UpdateRegOnceEx(MS_BOOL bWriteRegOnce, MS_BOOL bSync);
E_GOP_API_Result MApi_GOP_TriggerRegWriteIn(MS_U8 u8win, MS_BOOL bForceWriteIn);
E_GOP_API_Result MApi_GOP_TriggerRegWriteIn_Ex(MS_U8 u8win, MS_BOOL bForceWriteIn, MS_BOOL bSync);
E_GOP_API_Result MApi_GOP_GWIN_SetFadeInOut(MS_U8 gId, EN_GOP_FADE_TYPE eGwinFadeType, MS_BOOL bEnable, MS_U8 u8FadeRate);
E_GOP_API_Result MApi_GOP_GWIN_SetGWinShared(MS_U8 winId, MS_BOOL bIsShared);
E_GOP_API_Result MApi_GOP_GWIN_SetGWinSharedCnt(MS_U8 winId, MS_U16 u16SharedCnt);
E_GOP_API_Result MApi_GOP_GWIN_EnableTileMode(MS_U8 winId, MS_BOOL bEnable, EN_GOP_TILE_DATA_TYPE tiletype );
E_GOP_API_Result MApi_GOP_SetPINPON(MS_U8 winId, MS_BOOL bEn,GOP_PINPON_MODE PINPON_Mode);
E_GOP_API_Result MApi_GOP_SetGOPYUV(MS_U8 u8GOP);
E_GOP_API_Result MApi_GOP_MIXER_SetMux(MS_U8 u8GOP,MS_U8 u8Mux, MS_BOOL bEn);
E_GOP_API_Result MApi_GOP_GWIN_SetNewAlphaMode(MS_U8 gWinId, MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_SetPreAlphaMode(MS_U8 u8GOP, MS_BOOL bEnble);
MS_U8 MApi_GOP_GWIN_CreateWin(MS_U16 width, MS_U16 height, MS_U16 fbFmt);
MS_U8 MApi_GOP_GWIN_CreateWin2(MS_U16 width, MS_U16 height, MS_U16 fbFmt, EN_GOP_FRAMEBUFFER_STRING FBString);
MS_U8 MApi_GOP_GWIN_CreateWin_Assign_FB(MS_U8 u8GOP, MS_U8 FBId, MS_U16 dispX, MS_U16 dispY);
MS_U8 MApi_GOP_GWIN_CreateWin_Assign_32FB(MS_U8 u8GOP, MS_U32 u32FBId, MS_U16 dispX, MS_U16 dispY);
MS_U8 MApi_GOP_GWIN_CreateStaticWin(MS_U8 u8WinId, MS_U16 width, MS_U16 height, MS_U16 fbFmt);
MS_U8 MApi_GOP_GWIN_CreateStaticWin2(MS_U8 u8WinId, MS_U16 width, MS_U16 height, MS_U16 fbFmt, EN_GOP_FRAMEBUFFER_STRING FBString);
MS_U8 MApi_GOP_GWIN_CreateStaticWin_Assign_FB(MS_U8 u8WinId, MS_U8 u8GOP, MS_U8 FBId, MS_U16 dispX, MS_U16 dispY);
MS_U8 MApi_GOP_GWIN_CreateStaticWin_Assign_32FB(MS_U8 u8WinId, MS_U8 u8GOP, MS_U32 u32FBId, MS_U16 dispX, MS_U16 dispY);
MS_U8 MApi_GOP_GWIN_IsGwinExist(MS_U8 gId);
MS_U8 MApi_GOP_GWIN_GetFreeWinID(void);
MS_U8 MApi_GOP_GWIN_GetMAXWinID(void);
MS_U8 MApi_GOP_GWIN_GetCurrentWinId(void);
MS_U16 MApi_GOP_GWIN_GetMaxActiveGwin_v(void);
MS_U16 MApi_GOP_GWIN_Get_HSTART(void);
MS_U16 MApi_GOP_GWIN_GetActiveGWIN(void);
MS_U16 MApi_GOP_GWIN_GetMaxVEnd(MS_BOOL bActive);
MS_BOOL MApi_GOP_GWIN_IsAllGWINDisabled(void);
MS_BOOL MApi_GOP_GWIN_IsGWINEnabled(MS_U8 winId);
MS_BOOL MApi_GOP_GWIN_IsEnabled(void);
MS_BOOL MApi_GOP_GWIN_CheckOpmodeIsOn(void);
E_GOP_API_Result MApi_GOP_GWIN_SetResolution(MS_U8 u8GwinId, MS_U8 u8FbId, GOP_GwinInfo* pGwinInfo, GOP_StretchInfo* pStretchInfo, EN_GOP_STRETCH_DIRECTION direction, MS_U16 u16DstWidth, MS_U16 u16DstHeight);
E_GOP_API_Result MApi_GOP_GWIN_SetResolution_32FB(MS_U8 u8GwinId, MS_U32 u32FbId, GOP_GwinInfo* pGwinInfo, GOP_StretchInfo* pStretchInfo, EN_GOP_STRETCH_DIRECTION direction, MS_U16 u16DstWidth, MS_U16 u16DstHeight);
void MApi_GOP_Exit(void);


//======================================================================================
//  GOP FB management
//======================================================================================
E_GOP_API_Result MApi_GOP_FB_SEL(MS_U8 u8FB);
E_GOP_API_Result MApi_GOP_GWIN_SetDoubleHeap(MS_U32 u32DblHeapAdr, MS_U32 u32DblHeapLen);
E_GOP_API_Result MApi_GOP_GWIN_MapFB2Win(MS_U8 fbId, MS_U8 gwinId);
E_GOP_API_Result MApi_GOP_GWIN_Map32FB2Win(MS_U32 u32fbId, MS_U8 u8gwinId);
E_GOP_API_Result MApi_GOP_GWIN_Switch2FB(MS_U8 fbId);
E_GOP_API_Result MApi_GOP_GWIN_Switch2_32FB(MS_U32 u32fbId);
MS_BOOL MApi_GOP_Switch_GWIN_2_FB(MS_U8 gWinId, MS_U8 fbId, MS_U16 u16WaitTagID, MS_U16 *pU16QueueCnt);
MS_BOOL MApi_GOP_Switch_GWIN_2_32FB(MS_U8 gWinId, MS_U32 u32fbId, MS_U32 u32WaitTagID, MS_U32 *pU32QueueCnt);
MS_BOOL MApi_GOP_Switch_GWIN_2_FB_BY_ADDR(MS_U8 gWinId, MS_U32 u32FlipAddr, MS_U16 u16WaitTagID, MS_U16 *pU16QueueCnt);
MS_BOOL MApi_GOP_Switch_3DGWIN_2_FB_BY_ADDR(MS_U8 gWinId, MS_U32 u32MainFlipAddr, MS_U32 u32SubFlipAddr, MS_U16 u16WaitTagID, MS_U16 *pU16QueueCnt);
E_GOP_API_Result MApi_GOP_GWIN_DeleteFB(MS_U8 fbId);
E_GOP_API_Result MApi_GOP_GWIN_Delete32FB(MS_U32 u32fbId);
E_GOP_API_Result MApi_GOP_GWIN_GetFBRegion(MS_U8 fbID, MS_U16 *pX,MS_U16 *pY, MS_U16 *pW, MS_U16 *pH);
E_GOP_API_Result MApi_GOP_GWIN_Get32FBRegion(MS_U32 u32fbID, MS_U16 *pX, MS_U16 *pY, MS_U16 *pW, MS_U16 *pH);
E_GOP_API_Result MApi_GOP_GWIN_GetFBPosition(MS_U8 fbID, MS_U16 *pX,MS_U16 *pY);
E_GOP_API_Result MApi_GOP_GWIN_Get32FBPosition(MS_U32 u32fbID, MS_U16 *pX, MS_U16 *pY);
E_GOP_API_Result MApi_GOP_GWIN_SetFBInfo(MS_U8 fbId, GOP_GwinFBAttr *fbAttr);
E_GOP_API_Result MApi_GOP_GWIN_Set32FBInfo(MS_U32 u32fbId, GOP_GwinFBAttr *fbAttr);
E_GOP_API_Result MApi_GOP_GWIN_GetFBInfo(MS_U8 fbId, GOP_GwinFBAttr *fbAttr);
E_GOP_API_Result MApi_GOP_GWIN_Get32FBInfo(MS_U32 u32fbId, GOP_GwinFBAttr *fbAttr);
E_GOP_API_Result MApi_GOP_GWIN_GetFBAddr(MS_U8 fbID, MS_U32 *pAddr);
E_GOP_API_Result MApi_GOP_GWIN_Get32FBAddr(MS_U32 u32fbID, MS_U32 *pAddr);
E_GOP_API_Result MApi_GOP_GWIN_ClearFlipQueue(MS_U8 gWinId);
MS_U8 MApi_GOP_GWIN_GetMaxFBNum(void);
MS_U32 MApi_GOP_GWIN_GetMax32FBNum(void);
MS_U8 MApi_GOP_FB_Get(void);
MS_U8 MApi_GOP_GWIN_GetMAXFBID(void);
MS_U32 MApi_GOP_GWIN_GetMAX32FBID(void);
MS_U8 MApi_GOP_GWIN_DestroyFB(MS_U8 fbId);
MS_U8 MApi_GOP_GWIN_Destroy32FB(MS_U32 u32fbId);
MS_U8 MApi_GOP_GWIN_CreateFBFrom3rdSurf(MS_U16 width, MS_U16 height,  MS_U16 fbFmt, MS_U32 u32FbAddr, MS_U16 pitch, MS_U8* ret_FBId);
MS_U8 MApi_GOP_GWIN_Create32FBFrom3rdSurf(MS_U16 width, MS_U16 height,  MS_U16 fbFmt, MS_U32 u32FbAddr, MS_U16 pitch, MS_U32* u32ret_FBId);
MS_U8 MApi_GOP_GWIN_CreateFBbyStaticAddr(MS_U8 fbId, MS_U16 dispX, MS_U16 dispY, MS_U16 width, MS_U16 height,  MS_U16 fbFmt, MS_U32 u32FbAddr );
MS_U8 MApi_GOP_GWIN_Create32FBbyStaticAddr(MS_U32 u32fbId, MS_U16 dispX, MS_U16 dispY, MS_U16 width, MS_U16 height,  MS_U16 fbFmt, MS_U32 u32FbAddr);
MS_U8 MApi_GOP_GWIN_CreateFBbyStaticAddr2(MS_U8 fbId, MS_U16 dispX, MS_U16 dispY, MS_U16 width, MS_U16 height,  MS_U16 fbFmt, MS_U32 u32FbAddr, EN_GOP_FRAMEBUFFER_STRING FBString);
MS_U8 MApi_GOP_GWIN_Create32FBbyStaticAddr2(MS_U32 u32fbId, MS_U16 dispX, MS_U16 dispY, MS_U16 width, MS_U16 height,  MS_U16 fbFmt, MS_U32 u32FbAddr ,EN_GOP_FRAMEBUFFER_STRING FBString);
MS_U8 MApi_GOP_GWIN_CreateFB2(MS_U8 FBId,MS_U16 x, MS_U16 y, MS_U16 width, MS_U16 height, MS_U16 fbFmt);
MS_U8 MApi_GOP_GWIN_Create32FB2(MS_U32 u32FBId, MS_U16 x, MS_U16 y, MS_U16 width, MS_U16 height, MS_U16 fbFmt);
MS_U8 MApi_GOP_GWIN_CreateFB2_EXT(MS_U8 FBId, MS_U16 x, MS_U16 y, MS_U16 width, MS_U16 height, MS_U16 fbFmt, EN_GOP_FRAMEBUFFER_STRING FBString);
MS_U8 MApi_GOP_GWIN_Create32FB2_EXT(MS_U32 u32FBId, MS_U16 x, MS_U16 y, MS_U16 width, MS_U16 height, MS_U16 fbFmt, EN_GOP_FRAMEBUFFER_STRING FBString);
MS_U8 MApi_GOP_GWIN_GetCurrentFBID(void);
MS_U32 MApi_GOP_GWIN_GetCurrent32FBID(void);
MS_U8  MApi_GOP_GWIN_GetFBfromGWIN(MS_U8 gwinId) ;
MS_U32 MApi_GOP_GWIN_Get32FBfromGWIN(MS_U8 gwinId);
MS_U8 MApi_GOP_GWIN_IsFBExist(MS_U8 fbId);
MS_U8 MApi_GOP_GWIN_Is32FBExist(MS_U32 u32fbId);
MS_U8 MApi_GOP_GWIN_GetFreeFBID(void);
MS_U32 MApi_GOP_GWIN_GetFree32FBID(void);
MS_U8 MApi_GOP_GWIN_CreateFB(MS_U8 fbId, MS_U16 dispX, MS_U16 dispY, MS_U16 width, MS_U16 height,  MS_U16 fbFmt);
MS_U8 MApi_GOP_GWIN_Create32FB(MS_U32 u32fbId, MS_U16 dispX, MS_U16 dispY, MS_U16 width, MS_U16 height, MS_U16 fbFmt);
MS_U16 MApi_GOP_GWIN_GetFBFmt(MS_U8 fbId);
MS_U16 MApi_GOP_GWIN_Get32FBFmt(MS_U32 u32fbId);



//======================================================================================
//  GOP Palette setting
//======================================================================================
E_GOP_API_Result MApi_GOP_GWIN_SetPaletteOpt( GOP_PaletteEntry *pPalArray, MS_U16 u32PalStart, MS_U16 u32PalEnd, EN_GOP_PALETTE_TYPE ePalType);
E_GOP_API_Result MApi_GOP_GWIN_SetPaletteRead(EN_GOP_PALETTE_READTYPE type);
E_GOP_API_Result MApi_GOP_GWIN_ReadPalette(MS_U8 idx, MS_U32* clr);
E_GOP_API_Result MApi_GOP_GWIN_2GSetPaletteOpt(GOP_PaletteEntry *pPalArray, MS_U16 u32PalStart, MS_U16 u32PalEnd);
E_GOP_API_Result MApi_GOP_GWIN_2GSetPaletteRead(EN_GOP_PALETTE_READTYPE type);
E_GOP_API_Result MApi_GOP_GWIN_2GReadPalette(MS_U8 idx, MS_U32* clr);


//======================================================================================
//  GOP DWIN APIs
//======================================================================================
E_GOP_API_Result MApi_GOP_DWIN_Init(void);
E_GOP_API_Result MApi_GOP_DWIN_SetSourceSel(EN_GOP_DWIN_SRC_SEL enSrcSel);
E_GOP_API_Result MApi_GOP_DWIN_CaptureOneFrame2(void);
E_GOP_API_Result MApi_GOP_DWIN_EnableIntr(MS_U16 u8mask, MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_DWIN_CaptureOneFrame(void);
E_GOP_API_Result MApi_GOP_DWIN_Enable(MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_DWIN_GetWinProperty(GOP_DwinProperty *pproperty);
E_GOP_API_Result MApi_GOP_DWIN_SetWinProperty(GOP_DwinProperty *pproperty);
E_GOP_API_Result MApi_GOP_DWIN_SelectSourceScanType(EN_GOP_DWIN_SCAN_MODE enScanMode);
E_GOP_API_Result MApi_GOP_DWIN_SetDataFmt(EN_GOP_DWIN_DATA_FMT fmt);
E_GOP_API_Result MApi_GOP_DWIN_SetAlphaValue(MS_U8 u8AlphaVal);
E_GOP_API_Result MApi_GOP_DWIN_ClearIntr(MS_U16 u8mask);
E_GOP_API_Result MApi_GOP_DWIN_GetDWinIntInfo(GOP_DWinIntInfo *pDWinIntInfo);
E_GOP_API_Result MApi_GOP_DWIN_GetDWinIntInfoTimeout(GOP_DWinIntInfo *pDWinIntInfo, MS_U32 u32Timeout);
E_GOP_API_Result MApi_GOP_SetClkForCapture(void);   //only for source is OP path clock
MS_U16 MApi_GOP_DWIN_GetIntrStatus(void);
E_GOP_API_Result MApi_GOP_DWIN_EnableR2YCSC(MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_DWIN_SetUVSwap(MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_BeginDraw(void);
E_GOP_API_Result MApi_GOP_GWIN_EndDraw(void);

//======================================================================================
//  GOP  CallBack Functions
//======================================================================================
E_GOP_API_Result MApi_GOP_RegisterFBFmtCB(MS_U32 (*fpGOP_CB)(MS_U16 pitch,MS_U32 addr , MS_U16 fmt )  );
E_GOP_API_Result MApi_GOP_RegisterXCIsInterlaceCB(MS_BOOL (*fpGOP_CB)(void));
E_GOP_API_Result MApi_GOP_RegisterXCGetCapHStartCB(MS_U16 (*fpGOP_CB)(void));
E_GOP_API_Result MApi_GOP_RegisterXCReduceBWForOSDCB(void (*fpGOP_CB)(MS_U8 PqWin, MS_BOOL enable));
E_GOP_API_Result MApi_GOP_RegisterEventNotify(void (*fpGOP_CB)(MS_U32 u32EventID, void* reserved0));
E_GOP_API_Result MApi_GOP_RegisterXCSetDwinInfo(MS_BOOL (*fpGOP_CB)(MS_U16 cmd,MS_U32 *arg,MS_U16 size));

//======================================================================================
//  OC
//======================================================================================
E_GOP_API_Result MApi_GOP_OC_SetOCFBinfo(MS_PHYADDR u32Addr, EN_GOP_OC_SEL_TYPE BankMode, MS_U32 enBufSize);


//================================ Obsolete Function Start =======================================
//-------------------------------------------------------------------------------------------------
/// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  Alert !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  Alert !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/// !!! below function will be "REMOVED" or "REFACTORING" later, please do not use it !!!!!!!!!
//-------------------------------------------------------------------------------------------------
E_GOP_API_Result MApi_GOP_GWIN_UpdateRegOnce(MS_BOOL bWriteRegOnce);

#ifdef __cplusplus
}
#endif

#endif // _API_GOP_H_

