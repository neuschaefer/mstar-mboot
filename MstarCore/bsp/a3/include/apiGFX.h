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
/// @file   apiGFX.h
/// @brief  MStar Graphics API
/// @author MStar Semiconductor Inc.
/// @attention
/// <b>(OBSOLETED) <em>legacy interface is only used by MStar proprietary OSD\n
/// It's API level for backward compatible and will be remove in the next version.\n
/// Please refer @ref drvGE.h for future compatibility.</em></b>
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _API_GFX_H_
#define _API_GFX_H_

//#include "drvGE.h"
//#define MAX_FONT                    20  //5
//#define MAX_BITMAP                  127

#include "MsTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

// For CHAKRA
#define GE_ALIGNED_VALUE(value, align)  ( ((value) + ((align)-1)) & ~((align)-1) )
#define GE_ADDR_ALIGNMENT(addr)         GE_ALIGNED_VALUE(addr, 8)    // 8-byte alignment

// END CHAKRA

#define ERR_HANDLE                  -1
#define ERR_NULL_INDEX                  0xFFFF

#define MSIF_GFX_LIB_CODE               {'G','F','X','_'} //Lib code
#define MSIF_GFX_LIBVER                 {'1','9'}      //LIB version
#define MSIF_GFX_BUILDNUM               {'1','4' }    //Build Number
#define MSIF_GFX_CHANGELIST             {'0','0','5','6','2','9','3','7'} //P4 ChangeList Number

#define GFX_DRV_VERSION                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_GFX_LIB_CODE,                  /* IP__                                             */  \
    MSIF_GFX_LIBVER,                    /* 0.0 ~ Z.Z                                        */  \
    MSIF_GFX_BUILDNUM,                  /* 00 ~ 99                                          */  \
    MSIF_GFX_CHANGELIST,                /* CL#                                              */  \
    MSIF_OS

//GE return code
/// GFX API return value
typedef enum
{
    GFX_FAIL                        = 0,
    GFX_SUCCESS                        ,
    GFX_NON_ALIGN_ADDRESS             ,
    GFX_NON_ALIGN_PITCH               ,
    GFX_INVALID_PARAMETERS            ,
    /// not support
    GFX_DRV_NOT_SUPPORT               ,
    /// pixel format error
    GFX_DRV_FAIL_FORMAT               ,
    /// bitblit start address error
    GFX_DRV_FAIL_BLTADDR              ,
    /// bitblt overlap (if STRETCH, ITALIC, MIRROR, ROTATE)
    GFX_DRV_FAIL_OVERLAP              ,
    /// stretch bitblt fail
    GFX_DRV_FAIL_STRETCH              ,
    /// italic bitblt fail (if MIRROR, ROTATE)
    GFX_DRV_FAIL_ITALIC               ,
    /// engine is locked by others
    GFX_DRV_FAIL_LOCKED               ,
    /// primitive will not be drawn
    GFX_DRV_NOT_DRAW                   ,
    /// Dependent functions are not linked
    GFX_DRV_NO_DEPENDENT              ,
    /// context not inited.
    GFX_DRV_CTXMAG_FAIL               ,

    GFX_INVALID_INTENSITY_ID = 0x100,
    GFX_INVALID_BUFF_INFO             ,
    GFX_INVALID_FONT_HANDLE           ,
    GFX_INVALID_BMP_HANDLE            ,
    GFX_INIT_FAIL                                  ,
} GFX_Result;


///Define Raster Operation
typedef enum
{
    /// rop_result = 0;
    ROP2_OP_ZERO                    = 0,
    /// rop_result = ~( rop_src | rop_dst );
    ROP2_OP_NOT_PS_OR_PD            ,
    /// rop_result = ((~rop_src) & rop_dst);
    ROP2_OP_NS_AND_PD               ,
    /// rop_result = ~(rop_src);
    ROP2_OP_NS                      ,
    /// rop_result = (rop_src & (~rop_dst));
    ROP2_OP_PS_AND_ND               ,
    /// rop_result = ~(rop_dst);
    ROP2_OP_ND                      ,
    /// rop_result = ( rop_src ^ rop_dst);
    ROP2_OP_PS_XOR_PD               ,
    /// rop_result = ~(rop_src & rop_dst);
    ROP2_OP_NOT_PS_AND_PD           ,
    /// rop_result = (rop_src & rop_dst);
    ROP2_OP_PS_AND_PD               ,
    /// rop_result = ~(rop_dst ^ rop_src);
    ROP2_OP_NOT_PS_XOR_PD           ,
    /// rop_result = rop_dst;
    ROP2_OP_PD                      ,
    /// rop_result = (rop_dst | (~rop_src));
    ROP2_OP_NS_OR_PD                ,
    /// rop_result = rop_src;
    ROP2_OP_PS                      ,
    /// rop_result = (rop_src | (~rop_dst));
    ROP2_OP_PS_OR_ND                ,
    /// rop_result = (rop_dst | rop_src);
    ROP2_OP_PD_OR_PS                ,
    /// rop_result = 0xffffff;
    ROP2_OP_ONE                     ,
} GFX_ROP2_Op;


/// Color Key Operation Mode
typedef enum
{
    /// If EQUAL then perform CK operation
    CK_OP_EQUAL                     = 0,
    /// If NOT EQUAL then perform CK operation
    CK_OP_NOT_EQUAL                 = 1,
} GFX_ColorKeyMode;

///Define Blending Coefficient
typedef enum
{
    /// Csrc
    COEF_ONE                        = 0,
    /// Csrc * Aconst + Cdst * (1 - Aconst)
    COEF_CONST                      ,
    ///  Csrc * Asrc + Cdst * (1 - Asrc)
    COEF_ASRC                       ,
    /// Csrc * Adst + Cdst * (1 - Adst)
    COEF_ADST                       ,

    /// Cdst
    COEF_ZERO                       ,
    /// Csrc * (1 - Aconst) + Cdst * Aconst
    COEF_1_CONST                    ,
    /// Csrc * (1 - Asrc) + Cdst * Asrc
    COEF_1_ASRC                     ,
    ///  Csrc * (1 - Adst) + Cdst * Adst
    COEF_1_ADST                     ,

    /// ((Asrc * Aconst) * Csrc + (1-(Asrc *Aconst)) * Cdst) / 2
    COEF_ROP8_ALPHA                 ,
    /// ((Asrc * Aconst) * Csrc + Adst * Cdst * (1-(Asrc * Aconst))) / (Asrc * Aconst) + Adst * (1- Asrc * Aconst))
    COEF_ROP8_SRCOVER               ,
    /// ((Asrc * Aconst) * Csrc * (1-Adst) + Adst * Cdst) / (Asrc * Aconst) * (1-Adst) + Adst)
    COEF_ROP8_DSTOVER               ,

    /// Csrc * Aconst
    ///@note
    /// <b>[URANUS] <em>It does not support COEF_CONST_SRC</em></b>
    COEF_CONST_SRC              ,
    /// Csrc * (1 - Aconst)
    ///@note
    /// <b>[URANUS] <em>It does not support COEF_1_CONST_SRC</em></b>
    COEF_1_CONST_SRC            ,

    /// Csrc * Adst * Asrc * Aconst + Cdst * Adst * (1 - Asrc * Aconst)
    ///@note
    /// <b>[URANUS] <em>It does not support COEF_SRC_ATOP_DST</em></b>
    COEF_SRC_ATOP_DST               ,
    /// Cdst * Asrc * Aconst * Adst + Csrc * Asrc * Aconst * (1 - Adst)
    ///@note
    /// <b>[URANUS] <em>It does not support COEF_DST_ATOP_SRC</em></b>
    COEF_DST_ATOP_SRC               ,
    /// (1 - Adst) * Csrc * Asrc * Aconst + Adst * Cdst * (1 - Asrc * Aconst)
    ///@note
    /// <b>[URANUS] <em>It does not support COEF_SRC_XOR_DST</em></b>
    COEF_SRC_XOR_DST                ,
} GFX_BlendCoef;

///Define Blending Source from
typedef enum
{
    /// constant
    ABL_FROM_CONST                  = 0,
    /// source alpha
    ABL_FROM_ASRC                   ,
    /// destination alpha
    ABL_FROM_ADST                   ,
    /// Aout = Asrc*Aconst
    ABL_FROM_ROP8_SRC       ,
    /// Aout = Asrc*Aconst * Adst
    ABL_FROM_ROP8_IN  ,
    /// Aout = (1-Asrc*Aconst) * Adst
    ABL_FROM_ROP8_DSTOUT  ,
    /// Aout = (1-Adst) * Asrc*Aconst
    ABL_FROM_ROP8_SRCOUT           ,
    /// Aout = (Asrc*Aconst) + Adst*(1-Asrc*Aconst) or (Asrc*Aconst)*(1-Adst) + Adst
    ABL_FROM_ROP8_OVER             ,

    /// 1 - Aconst
    ABL_FROM_ROP8_INV_CONST       ,
    /// 1 - Asrc
    ABL_FROM_ROP8_INV_ASRC         ,
    /// 1 - Adst
    ABL_FROM_ROP8_INV_ADST         ,
    /// Adst * Asrc * Aconst + Adst * (1 - Asrc * Aconst) A atop B
    ABL_FROM_ROP8_SRC_ATOP_DST    ,
    /// Asrc * Aconst * Adst + Asrc * Aconst * (1 - Adst) B atop A
    ABL_FROM_ROP8_DST_ATOP_SRC    ,
    /// (1 - Adst) * Asrc * Aconst + Adst * (1 - Asrc * Aconst) A xor B
    ABL_FROM_ROP8_SRC_XOR_DST     ,
    /// Asrc * Asrc * Aconst + Adst * (1 - Asrc * Aconst)
    ABL_FROM_ROP8_INV_SRC_ATOP_DST     ,
    /// Asrc * (1 - Asrc * Aconst) + Adst * Asrc * Aconst
    ABL_FROM_ROP8_INV_DST_ATOP_SRC
} GFX_AlphaSrcFrom;


///Define Colorkey Mode
typedef enum
{
    /// max(Asrc,Adst)
    GFX_ACMP_OP_MAX                = 0,
    /// min(Asrc,Adst)
    GFX_GE_ACMP_OP_MIN                = 1,

} GFX_ACmpOp;


/// GE buffer format
typedef enum
{
    /// font mode I1
    GFX_FMT_I1                      = E_MS_FMT_I1,
    /// font mode I2
    GFX_FMT_I2                      = E_MS_FMT_I2,
    /// font mode I4
    GFX_FMT_I4                      = E_MS_FMT_I4,
    /// color format palette 256(I8)
    GFX_FMT_I8                      = E_MS_FMT_I8,
     /// color format blinking display
    GFX_FMT_FABAFGBG2266 = E_MS_FMT_FaBaFgBg2266,
    /// Uranus GOP only support this blinking
    /// color format for blinking display format
    GFX_FMT_1ABFGBG12355            = E_MS_FMT_1ABFgBg12355,
    /// color format RGB565
    GFX_FMT_RGB565                  = E_MS_FMT_RGB565,
    // color format ORGB1555
    GFX_FMT_ARGB1555                = E_MS_FMT_ARGB1555,
    // color format ARGB4444
    GFX_FMT_ARGB4444                = E_MS_FMT_ARGB4444,
    // color format for blinking display format
    // Uranus GOP does NOT support this blinking format
    // GE_FMT_1BAAFGBG123433       = 0xb,
    // @FIXME: Venus does not have this color format. Need to take care of it.
    /// color format ARGB1555 DST
    GFX_FMT_ARGB1555_DST            = E_MS_FMT_ARGB1555_DST,
    /// color format YUV422
    GFX_FMT_YUV422                  = E_MS_FMT_YUV422,
    /// color format ARGB8888
    GFX_FMT_ARGB8888                = E_MS_FMT_ARGB8888,
    /// color format RGBA5551
    GFX_FMT_RGBA5551                = E_MS_FMT_RGBA5551,
     /// color format RGBA4444
    GFX_FMT_RGBA4444               = E_MS_FMT_RGBA4444,
    /// color format ABGR8888
    GFX_FMT_ABGR8888                = E_MS_FMT_ABGR8888,
} GFX_Buffer_Format;

///Define RGB2YUV conversion formula
typedef enum
{
    GFX_YUV_OP1            ,  // GFX_YUV_Rgb2Yuv
    GFX_YUV_OP2            ,  // GFX_YUV_OutRange
    GFX_YUV_OP3            ,  // GE_YUV_InRange
    GFX_YUV_OP4            ,  // GFX_YUV_422
} GFX_YUV_OpType;

///Define RGB2YUV conversion formula
typedef enum
{
    GFX_YUV_RGB2YUV_PC             = 0,
    GFX_YUV_RGB2YUV_255            = 1,

} GFX_YUV_Rgb2Yuv;

///Define output YUV color domain
typedef enum
{
    GFX_YUV_OUT_255                = 0,
    GFX_YUV_OUT_PC                 = 1,

} GFX_YUV_OutRange;

///Define input YUV color domain
typedef enum
{
    GFX_YUV_IN_255                 = 0,
    GFX_YUV_IN_127                 = 1,

} GFX_YUV_InRange;

///Define YOU 422 format
typedef enum
{
    GFX_YUV_YVYU                   = 0,
    GFX_YUV_YUYV                   = 1,
    GFX_YUV_VYUY                   = 2,
    GFX_YUV_UYVY                   = 3,

} GFX_YUV_422;

///Define paramter for YUV operation
typedef struct
{
    GFX_YUV_Rgb2Yuv                  rgb2yuv;
    GFX_YUV_OutRange                 out_range;
    GFX_YUV_InRange                  in_range;
    GFX_YUV_422                      dst_fmt;
    GFX_YUV_422                      src_fmt;

} GFX_YUVMode;


//-------------------------------------------------
/// Define Virtual Command Buffer Size
typedef enum
{
    /// 4K
    GFX_VCMD_4K = 0,
    /// 8K
    GFX_VCMD_8K = 1,
    /// 16K
    GFX_VCMD_16K = 2,
    /// 32K
    GFX_VCMD_32K = 3,
    /// 64K
    GFX_VCMD_64K = 4,
    /// 128K
    GFX_VCMD_128K = 5,
    /// 256K
    GFX_VCMD_256K = 6,
    /// 512K
    GFX_VCMD_512K = 7,
    /// 1024k
    GFX_VCMD_1024K = 8,
} GFX_VcmqBufSize;



//-------------------------------------------------
/// Define RGB color in LE
typedef struct
{
    /// Blue
    MS_U8 b;
    /// Green
    MS_U8 g;
    /// Red
    MS_U8 r;
    /// Alpha
    MS_U8 a;
} GFX_RgbColor;

/// Define YUV color
typedef struct
{
    MS_U32         Y:8;
    MS_U32         U:4;
    MS_U32         V:4;
} GFX_YuvColor;


/// General GFX color type, union of rgb and yuv color.
typedef struct{
    union{
        GFX_RgbColor    rgb;
        GFX_YuvColor    yuv;
    };
} GFX_Color;

//-------------------------------------------------
/// Define the start color & end color
typedef struct
{
    /// start color
    GFX_RgbColor color_s;
    /// end color
    GFX_RgbColor color_e;
} GFX_ColorRange;

//-------------------------------------------------
/// Define the position of one point.
typedef struct
{
    /// X address
    MS_U16 x;
    /// Y address
    MS_U16 y;
} GFX_Point;

//-------------------------------------------------
/// Specify the blink data
        //          1 A B Fg Bg
        //          1 2 3  5  5
typedef struct
{
    /// BG color (for blink mode use)
    MS_U8                  background;             // 5 bits
    /// FG color (for blink mode use)
    MS_U8                  foreground;             // 5 bits
    /// Control flag\n
    union{
        MS_U16             ctrl_flag;
        struct{
            MS_U16         Blink:3;                // 3 bits
            MS_U16         Alpha:2;                // 2 bits
            MS_U16         blink_en:1;
            MS_U16         reserved1:10;
        } Bits;
        struct{
            MS_U16 BlinkAlpha:4;
            MS_U16 Alpha:2;
            MS_U16 Blink:3;
            MS_U16 reserved:7;
        }Bits2;
        struct{
            MS_U16 Fa:2;
            MS_U16 Ba:2;
            MS_U16 reserved:12;

        }Bits3;
    };


} GFX_BlinkData;


/// Define the start blink color & end blink color.
typedef struct
{
    /// start blink color
    GFX_BlinkData blink_data_s;
    /// end blink color
    GFX_BlinkData blink_data_e;
} GFX_BlinkDataRange;

//-------------------------------------------------
//-------------------------------------------------
#define GFXLINE_FLAG_COLOR_CONSTANT     0x00
#define GFXLINE_FLAG_COLOR_GRADIENT     0x01

/// Define the attribute of line.
typedef struct
{
    /// start X address
    MS_U16 x1;
    /// Start Y address
    MS_U16 y1;
    /// End X address
    MS_U16 x2;
    /// End Y address
    MS_U16 y2;
    /// Color format
    GFX_Buffer_Format fmt;
    union
    {
        /// Color
        ///For all RGB color, the color set as the ARGB8888 format.\n
        ///Each color component need to shift to high bit.\n
        ///Use ARGB1555 as the example, the source color key as the following:\n
        ///ARGB1555  --> ARRRRRGGGGGBBBBB                   (every character represents one bit)\n
        ///colorRange.color_s --> A0000000RRRRR000GGGGG000BBBBB000   (every character represents one bit)\n\n
        ///For GFX_FMT_I8 format, the index set to b component (colorRange.color_s.b = b).\n
        GFX_ColorRange       colorRange;
        ///Blink attribute
        ///For GFX_FMT_1BAAFGBG123433 foramt, the foramt set as the GFX_BlinkData.\n
        GFX_BlinkDataRange  blkDataRange;
    };
    /// Line width
    MS_U32 width;
    /// GFXLINE_FLAG_COLOR_CONSTANT: Constant color\n
    /// GFXLINE_FLAG_COLOR_GRADIENT: Gradient color
    MS_U32 flag;

} GFX_DrawLineInfo;

//-------------------------------------------------

/// Define the dimension of one block
typedef struct
{
    /// X start address
    MS_U16 x;
    /// Y start address
    MS_U16 y;
    /// width
    MS_U16 width;
    /// height
    MS_U16 height;
} GFX_Block;

/*******************************************************************
// Define the Trapezoid                                            *
// [u16X0, u16Y0]: The Left point of top of Trapezoid;             *
// [u16X1, u16Y1]: The Left point of bottom of Trapezoid;          *
// [u16DeltaTop]: The Width of top of Trapezoid;                   *
// [u16DeltaBottom]: The Width of bottom of Trapezoid;             *
// To Simplify, For DIRECTION_X: u16Y0 < u16Y1                     *
// To Simplify, For DIRECTION_Y: u16X0 > u16X1                     *
********************************************************************/
typedef struct
{
    /// x0 start address
    MS_U16                          u16X0;
    /// y0 start address
    MS_U16                          u16Y0;
    /// x1 start address
    MS_U16                          u16X1;
    /// y1 start address
    MS_U16                          u16Y1;
    /// delta of Top
    MS_U16                          u16DeltaTop;
    // delta of Bottom
    MS_U16                          u16DeltaBottom;
} GFX_Trapezoid;

//-------------------------------------------------

#define GFXRECT_FLAG_COLOR_CONSTANT     0x0
#define GFXRECT_FLAG_COLOR_GRADIENT_X   0x1
#define GFXRECT_FLAG_COLOR_GRADIENT_Y   0x2
#define GFXRECT_FLAG_TRAPE_DIRECTION_X  0x4 //excluded with GFXRECT_FLAG_TRAPE_DIRECTION_Y
#define GFXRECT_FLAG_TRAPE_DIRECTION_Y  0x8 //excluded with GFXRECT_FLAG_TRAPE_DIRECTION_X

/// Define the info. of one block.
typedef struct
{
    /// dst block info
    union
    {
        GFX_Block       dstBlock;
        GFX_Trapezoid   dstTrapezoidBlk;
    };
    /// Color format
    GFX_Buffer_Format fmt;
    union
    {
        /// Color
        ///For all RGB color, the color set as the ARGB8888 format.\n
        ///Each color component need to shift to high bit.\n
        ///Use ARGB1555 as the example, the source color key as the following:\n
        ///ARGB1555  --> ARRRRRGGGGGBBBBB                   (every character represents one bit)\n
        ///color_s   --> A0000000RRRRR000GGGGG000BBBBB000   (every character represents one bit)\n\n
        ///For GFX_FMT_I8 format, the index set to b component (colorRange.color_s.b = b).\n
        GFX_ColorRange       colorRange;
        ///Blink attribute
        ///For GFX_FMT_1BAAFGBG123433 foramt, the foramt set as the GFX_BlinkData.\n
        GFX_BlinkDataRange  blkDataRange;
    };

    /// GERECT_FLAG_COLOR_CONSTANT: Constant color\n
    /// GERECT_FLAG_COLOR_GRADIENT_X: X direction gradient color\n
    /// GERECT_FLAG_COLOR_GRADIENT_Y: Y direction gradient color\n
    /// GFXRECT_FLAG_TRAPE_DIRECTION_X: for trapezoid, top & bottom in X direction parallel, excluded with GFXRECT_FLAG_TRAPE_DIRECTION_Y\n
    /// GFXRECT_FLAG_TRAPE_DIRECTION_Y: for trapezoid, top & bottom in Y direction parallel, excluded with GFXRECT_FLAG_TRAPE_DIRECTION_X\n
    MS_U32 flag;

} GFX_RectFillInfo;

/// Define structure for OVAL drawing.
typedef struct
{
    /// dst block info
    GFX_Block       dstBlock;
    /// Color format
    GFX_Buffer_Format fmt;
    union{
        GFX_RgbColor color;
        GFX_BlinkData blink_data;
    };
    MS_U32 u32LineWidth;
} GFX_OvalFillInfo;


//-------------------------------------------------
#define GFXFONT_FLAG_DEFAULT            0x0
#define GFXFONT_FLAG_ITALIC             0x1
#define GFXFONT_FLAG_SCALE              0x2
#define GFXFONT_FLAG_COMPACT            0x4
#define GFXFONT_FLAG_BACKGROUND         0x8
#define GFXFONT_FLAG_BLINK              0x10
#define GFXFONT_FLAG_VARWIDTH           0x20
#define GFXFONT_FLAG_GAP                0x40
#define GFXFONT_FLAG_BOLD               0x80

/// Define font overlap info.
typedef struct
{
    MS_S8 s8Xoffset;         ///
    MS_S8 s8Yoffset;
} GFX_GlyphOverlapInfo;

/// Glyph display information
typedef struct
{
    MS_U8  u8X0;               ///< Left position to display
    MS_U8  u8Width;            ///< Width of the glyph to display
    MS_U16 u16Index;           ///< Glyph index in the font table
    GFX_GlyphOverlapInfo overlap_info;
} GFX_GlyphDispInfo;




/// Font format
typedef struct
{
    /// GEFONT_FLAG_DEFAULT: Default font format\n
    /// GEFONT_FLAG_SCALE: scalable font\n
    /// GEFONT_FLAG_COMPACT: Compact font\n
    /// GEFONT_FLAG_GAP: Gap font\n
    /// GEFONT_FLAG_VARIABLE_WIDTH: Variable font width, depend on horizontal font length.
    MS_U32 flag;

    /// dst block first character position , and each character width , height
    GFX_Block  dstblk;

    /// set compact distant(take indent effect) when GEFONT_FLAG_COMPACT is set
    MS_U16 dis;
    MS_U16 gap;

    GFX_GlyphDispInfo *pGlyphDispInfo;

    union{
        MS_U32  u32data;
        GFX_RgbColor color;
        GFX_BlinkData blink_data;
    };

} GFX_TextOutInfo;


/// Define blink type for blinking data
typedef enum
{
    GEBLINK_NONE = 0x0,
    GEBLINK_BACKGROUND,
    GEBLINK_FOREGROUND,
    GEBLINK_BOTH,
} GFX_BlinkType;

// Define write protect type
typedef enum
{
    GFX_WP_IN_RANGE                = 0,
    GFX_WP_OUT_RANGE               = 1,
    GFX_WP_DISABLE                 = 0xFF,

} GFX_WPType;

/// Bounding box (BBox) of a glyph
typedef struct
{
    MS_U8  u8X0;       ///< Position of the left edge of the bounding box
    MS_U8  u8Width;    ///< Width of the bounding box
    MS_U8  u8Y0;       ///< Position of the top edge of the bounding box
    MS_U8  u8Height;   ///< Height of the bounding box
} GFX_GlyphBbox;

/// X-direction information of the bounding box of a glyph
typedef struct
{
    MS_U8  u8X0;       ///< Position of the left edge of the bounding box
    MS_U8  u8Width;    ///< Width of the bounding box
} GFX_GlyphBbox_X;

/// Y-direction information of the bounding box of a glyph
typedef struct
{
    MS_U8  u8Y0;       ///< Position of the top edge of the bounding box
    MS_U8  u8Height;   ///< Height of the bounding box
} GFX_GlyphBbox_Y;


/// Define structure for color delta (Gradient color)
typedef struct
{
    MS_U8 flag;
    MS_U32 delta_r;
    MS_U32 delta_g;
    MS_U32 delta_b;
} GFX_GFX_ColorDelta;


//-------------------------------------------------
/// Specify the attribute of a bitmap
typedef struct
{
    /// Do scaling operation
    MS_BOOL bScale;
    /// X start address
    MS_U16 x;
    /// Y start address
    MS_U16 y;
    /// width
    MS_U16 width;
    /// height
    MS_U16 height;
} GFX_DrawBmpInfo;


//-------------------------------------------------
/// Define rotation angle
typedef enum
{
    /// Do not rotate
    GEROTATE_0,
    /// Rotate 90 degree
    GEROTATE_90,
    /// Rotate 180 degree
    GEROTATE_180,
    /// Rotate 270 degree
    GEROTATE_270,
} GFX_RotateAngle;

//=============================================================================
// Font information
//=============================================================================
#if 0
/// Bounding box (BBox) of a glyph
typedef struct
{
    ///Position of the left edge of the bounding box
    MS_U8  u8X0;
    ///Width of the bounding box
    MS_U8  u8Width;
    ///Position of the top edge of the bounding box
    MS_U8  u8Y0;
    ///Height of the bounding box
    MS_U8  u8Height;
}GFX_GFX_GLYPH_BBOX;
#endif

/// define character information
typedef struct
{
    /// Character start address (128 bits alignment)
    MS_PHYADDR addr;
    /// Character width
    MS_U32 width;
    /// Character pitch
    MS_U32 pitch;
    /// Character height
    MS_U32 height;
    /// Character horizontal offset
    MS_U32 Hoffset;
    /// Character vertical offset
    MS_U32 Voffset;
    /// Character format
    GFX_Buffer_Format fmt;
} GFX_CharInfo;

/// Define font table information
typedef struct
{
    /// font start address
    MS_PHYADDR addr;
    /// font length
    MS_U32 len;
    /// font structure is used
    MS_BOOL inUsed;
    /// character width (pixel unit)
    MS_U32 width;
    /// character pitch (byte unit)
    MS_U32 pitch;
    /// character height (pixel unit)
    MS_U32 height;
    /// one character length (byte unit)
    MS_U32 offset;
    /// Bounding Box offset
    GFX_GlyphBbox* pBBox;
    /// font format
    GFX_Buffer_Format fmt;
} GFX_FontInfo;


//=============================================================================
// Bitmap information
//=============================================================================
typedef struct
{
    MS_PHYADDR addr;       // flat address of whole memory map
    MS_U32 len;
    MS_BOOL inUsed;
    MS_U32 width;
    MS_U32 pitch;
    MS_U32 height;
    GFX_Buffer_Format fmt;
} GFX_BitmapInfo;


//=============================================================================
// Draw Rect info
//=============================================================================
/// Define the bitblt source & destination block.
typedef struct
{
    /// Source block
    GFX_Block srcblk;

    /// Destination block
    union
    {
        GFX_Trapezoid dsttrapeblk;
        GFX_Block dstblk;
    };
}GFX_DrawRect;

/// Define the scaling factor for X & Y direction.
typedef struct
{
    MS_U32 u32DeltaX;
    MS_U32 u32DeltaY;
    MS_U32 u32InitDelatX;
    MS_U32 u32InitDelatY;
}GFX_ScaleInfo;

//=============================================================================
// Data Buffer info
//=============================================================================
/// Data buffer info.
typedef struct
{
    /// start memory address
    MS_PHYADDR u32Addr;       // flat address of whole memory map
    /// width
    MS_U32 u32Width;
    /// height
    MS_U32 u32Height;
    /// pitch
    MS_U32 u32Pitch;
    /// Color format\n
    /// - GFX_FMT_I1\n
    /// - GFX_FMT_I2\n
    /// - GFX_FMT_I4\n
    /// - GFX_FMT_I8\n
    /// - GFX_FMT_RGB565\n
    /// - GFX_FMT_ARGB1555\n
    /// - GFX_FMT_ARGB4444\n
    /// - GFX_FMT_1BAAFGBG123433\n
    /// - GFX_FMT_ARGB8888\n
    GFX_Buffer_Format u32ColorFmt;
} GFX_BufferInfo;

/// Define the GFX init parameter.
typedef struct
{
    MS_U8                           u8Miu;
    MS_U8                           u8Dither;
    MS_U32                         u32VCmdQSize;                       /// MIN:4K, MAX:512K, <MIN:Disable
    MS_PHYADDR                 u32VCmdQAddr;                       // 8-byte aligned
    MS_BOOL                       bIsHK;                                        /// Running as HK or Co-processor
    MS_BOOL                       bIsCompt;                                        /// Running as compatible mode. In compatible mode, the parameter checking loose for NOS APP compatibility.  TRUE=>compatible with 51/Chakra , FALSE=>linux OS style
}GFX_Config;

/// GE dbg info
typedef struct
{
    /// Specified format
    MS_U8                       verctrl[32];
    /// Specified format
    MS_U8                       gedump[256];
    /// Base alignment in byte unit
    MS_U32                      semstaus;
} GFX_DbgInfo;


typedef GFX_BufferInfo* PGFX_BufferInfo;



//=============================================================================
// GE palette information
//=============================================================================

typedef union
{
    /// ARGB8888
    struct
    {
        MS_U8 u8A;
        MS_U8 u8R;
        MS_U8 u8G;
        MS_U8 u8B;
    } RGB;
    // 32-bit direct access.
    MS_U8 u8Data[4];
} GFX_PaletteEntry;



#define GFXDRAW_FLAG_DEFAULT            0x0
#define GFXDRAW_FLAG_SCALE              0x1
#define GFXDRAW_FLAG_DUPLICAPE          0x2
#define GFXDRAW_FLAG_TRAPEZOID_X        0x4 // excluded with GFXDRAW_FLAG_TRAPEZOID_Y
#define GFXDRAW_FLAG_TRAPEZOID_Y        0x8 // excluded with GFXDRAW_FLAG_TRAPEZOID_X

//#define FB_FMT_AS_DEFAULT               0xFFFF

//=============================================================================
// YUV color setting
//=============================================================================
typedef MS_U8                           GFX_Rgb2yuvMode;
#define GFX_RGB2YUV_PC_MODE             ((GFX_Rgb2yuvMode)0x0)          // computer mode Y: 16~ 235, UV: 0~ 240
#define GFX_RGB2YUV_255_MODE            ((GFX_Rgb2yuvMode)0x1)          // To 0~ 255

typedef MS_U8                           GFX_YuvRangeOut;
#define GFX_YUV_RANGE_OUT_255           ((GFX_YuvRangeOut)0x0)         // To 0~ 255
#define GFX_YUV_RANGE_OUT_PC            ((GFX_YuvRangeOut)0x1)         // To Y: 16~ 235

typedef MS_U8                           GFX_YuvRangeIn;
#define GFX_YUV_RANGE_IN_255            ((GFX_YuvRangeIn)0x0)          // UV input range, 0~ 255
#define GFX_YUV_RANGE_IN_127            ((GFX_YuvRangeIn)0x1)          // UV input range, -128~ 127

typedef MS_U8                           GFX_Yuv422Fmt;
#define GFX_YUV_422_FMT_UY1VY0          ((GFX_Yuv422Fmt)0x00)          // CbY1CrY0
#define GFX_YUV_422_FMT_VY1UY0          ((GFX_Yuv422Fmt)0x01)          // CrY1CbY0
#define GFX_YUV_422_FMT_Y1UY0V          ((GFX_Yuv422Fmt)0x02)          // Y1CbY0Cr
#define GFX_YUV_422_FMT_Y1VY0U          ((GFX_Yuv422Fmt)0x03)          // Y1CrY0Cb

/// Pack of YUV CSC info
typedef struct
{
    GFX_Rgb2yuvMode                     rgb2yuv_mode;
    GFX_YuvRangeOut                    yuv_range_out;
    GFX_YuvRangeIn                     yuv_range_in;
    GFX_Yuv422Fmt                      yuv_mem_fmt_src;
    GFX_Yuv422Fmt                      yuv_mem_fmt_dst;
} GFX_YuvInfo;

//-------------------------------------------------
/// Define Stretch Bitblt with Color Key Type
typedef enum
{
    /// Do nothing
    GFX_DONOTHING = 0,
    /// Nearest When the Color Key happened
    GFX_NEAREST = 1,
    /// Replace the Key to Custom Color
    GFX_REPLACE_KEY_2_CUS = 2,
} GFX_StretchCKType;

//-------------------------------------------------
/// Define DFB Blending Related:
#define GFX_DFB_BLD_FLAG_COLORALPHA             0x0001
#define GFX_DFB_BLD_FLAG_ALPHACHANNEL           0x0002
#define GFX_DFB_BLD_FLAG_COLORIZE               0x0004
#define GFX_DFB_BLD_FLAG_SRCPREMUL              0x0008
#define GFX_DFB_BLD_FLAG_SRCPREMULCOL           0x0010
#define GFX_DFB_BLD_FLAG_DSTPREMUL              0x0020
#define GFX_DFB_BLD_FLAG_XOR                    0x0040
#define GFX_DFB_BLD_FLAG_DEMULTIPLY             0x0080
#define GFX_DFB_BLD_FLAG_SRCALPHAMASK           0x0100
#define GFX_DFB_BLD_FLAG_SRCCOLORMASK           0x0200
#define GFX_DFB_BLD_FLAG_ALL                    0x03FF

typedef enum
{
    GFX_DFB_BLD_OP_ZERO                 = 0,
    GFX_DFB_BLD_OP_ONE                  = 1,
    GFX_DFB_BLD_OP_SRCCOLOR             = 2,
    GFX_DFB_BLD_OP_INVSRCCOLOR          = 3,
    GFX_DFB_BLD_OP_SRCALPHA             = 4,
    GFX_DFB_BLD_OP_INVSRCALPHA          = 5,
    GFX_DFB_BLD_OP_DESTALPHA            = 6,
    GFX_DFB_BLD_OP_INVDESTALPHA         = 7,
    GFX_DFB_BLD_OP_DESTCOLOR            = 8,
    GFX_DFB_BLD_OP_INVDESTCOLOR         = 9,
    GFX_DFB_BLD_OP_SRCALPHASAT          = 10,
}GFX_DFBBldOP;

//=============================================================================
// GFX format capability setting
//=============================================================================
///Define Buffer Usage Type
typedef enum
{
    /// Desitination buffer for LINE, RECT, BLT
    E_GFX_BUF_DST                    = 0,
    /// Source buffer for BLT
    E_GFX_BUF_SRC                    = 1,
} EN_GFX_BUF_TYPE;

/// Define gfx format capability type
typedef enum
{
    E_GFX_FMT_CAP_NONE = 0x0,
    E_GFX_FMT_CAP_MULTI_PIXEL,
} EN_GFX_FMT_CAPS_TYPE;

typedef struct
{
    /// Color format\n
    /// - GFX_FMT_I1\n
    /// - GFX_FMT_I2\n
    /// - GFX_FMT_I4\n
    /// - GFX_FMT_I8\n
    /// - GFX_FMT_RGB565\n
    /// - GFX_FMT_ARGB1555\n
    /// - GFX_FMT_ARGB4444\n
    /// - GFX_FMT_1BAAFGBG123433\n
    /// - GFX_FMT_ARGB8888\n
    GFX_Buffer_Format    u32ColorFmt;
    EN_GFX_BUF_TYPE      eBufferType;
    EN_GFX_FMT_CAPS_TYPE eFmtCapsType;
    MS_U8                u8BaseAlign;
    MS_U8                u8PitchAlign;
}GFX_FmtAlignCapsInfo;

//=============================================================================
// GFX capability setting
//=============================================================================

//GFX Capability
typedef enum
{
    E_GFX_CAP_MULTI_PIXEL,
    E_GFX_CAP_BLT_DOWN_SCALE,
}EN_GFX_CAPS;

///GFX Capability MultiPixel Info
typedef struct
{
    MS_U16  WordUnit;
    MS_BOOL bSupportMultiPixel;
}GFX_CapMultiPixelInfo;

///GFX Capability Bitblt down scale Info
typedef struct
{
    /// Bitblt down scale range start
    MS_U8 u8RangeMax;
    /// Bitblt down scale range end
    MS_U8 u8RangeMin;
    /// Bitblt down scale continuous range end
    MS_U8 u8ContinuousRangeMin;
    /// Is full range support down scaling.
    /// - TRUE: The down scale value between u8RangeMax to u8RangeMin is fully supported.
    /// - FALSE: The down scale value between u8RangeMax to u8ContinuousRangeMin is fully supported.
    ///          The down scale value between u8ContinuousRangeMin to u8RangeMin is supported
    ///          if the value is power of two (e.g., 4, 8, 16, and 32).
    MS_BOOL bFullRangeSupport;
}GFX_BLT_DownScaleInfo;

//=============================================================================
// GE Driver Function
//=============================================================================
extern void MApi_GFX_Init(GFX_Config *geConfig);
extern GFX_Result MApi_GFX_DrawBitmap(MS_S32 handle, GFX_DrawBmpInfo *pbmpfmt);
extern GFX_Result MApi_GFX_GetFontInfo(MS_S32 handle, GFX_FontInfo* pinfo);
extern GFX_Result MApi_GFX_GetBitmapInfo(MS_S32 handle, GFX_BitmapInfo* pinfo);
extern GFX_Result MApi_GFX_GetFrameBufferInfo(MS_U32 *width, MS_U32 *height, MS_U32 *pitch, MS_U32 *fbFmt, MS_PHYADDR *addr);
extern GFX_Result MApi_GFX_DrawLine(GFX_DrawLineInfo *pline);
extern GFX_Result MApi_GFX_RectFill(GFX_RectFillInfo *pfillblock);
extern GFX_Result MApi_GFX_TrapezoidFill(GFX_RectFillInfo *pGfxFillInfo);
extern GFX_Result MApi_GFX_EnableTrapezoidAA(MS_BOOL bEnable);
extern GFX_Result MApi_GFX_EnableTrapSubPixCorr(MS_BOOL bEnable);
extern GFX_Result MApi_GFX_SetClip(GFX_Point* v0, GFX_Point* v1);
extern GFX_Result MApi_GFX_GetClip(GFX_Point* v0, GFX_Point* v1);
extern GFX_Result MApi_GFX_SetItalic(MS_BOOL enable,MS_U8 ini_line, MS_U8 ini_dis, MS_U8 delta);
extern GFX_Result MApi_GFX_SetDither(MS_BOOL enable);
extern GFX_Result MApi_GFX_SetOnePixelMode(MS_BOOL enable);
extern GFX_Result MApi_GFX_SetSrcBufferInfo(GFX_BufferInfo *bufInfo, MS_U32 offsetofByte);
extern GFX_Result MApi_GFX_SetDstBufferInfo(GFX_BufferInfo *bufInfo, MS_U32 offsetofByte);
extern GFX_Result MApi_GFX_SetNearestMode(MS_BOOL enable);
extern GFX_Result MApi_GFX_SetMirror(MS_BOOL isMirrorX, MS_BOOL isMirrorY);
extern GFX_Result MApi_GFX_SetROP2(MS_BOOL enable, GFX_ROP2_Op eRopMode);
extern GFX_Result MApi_GFX_SetRotate(GFX_RotateAngle angle);
extern GFX_Result MApi_GFX_SetSrcColorKey(MS_BOOL enable, GFX_ColorKeyMode opMode,
                                      GFX_Buffer_Format fmt, void *ps_color,
                                      void *pe_color);
extern GFX_Result MApi_GFX_SetDstColorKey(MS_BOOL enable, GFX_ColorKeyMode opMode,
                                      GFX_Buffer_Format fmt, void *ps_color,
                                      void *pe_color);
extern GFX_Result MApi_GFX_TextOut(MS_S32 fhandle, MS_U8 *pindex, MS_U32 strwidth, GFX_TextOutInfo *pfmt);
extern GFX_Result MApi_GFX_QueryTextDispLength(MS_S32 fhandle, MS_U8 *pu8index, MS_U32 u32strwidth,
                                               GFX_TextOutInfo *pfmt, MS_U32* pu32DispLength);
extern GFX_Result MApi_GFX_CharacterOut(GFX_CharInfo*  pChar, GFX_TextOutInfo *pfmt);
extern GFX_Result MApi_GFX_SetAlphaSrcFrom(GFX_AlphaSrcFrom eMode);
extern GFX_Result MApi_GFX_SetAlphaBlending(GFX_BlendCoef blendcoef, MS_U8 blendfactor);
extern GFX_Result MApi_GFX_EnableAlphaBlending(MS_BOOL enable);
extern GFX_Result MApi_GFX_QueryDFBBldCaps(MS_U16 *pU16SupportedBldFlags);
extern GFX_Result MApi_GFX_EnableDFBBlending(MS_BOOL enable);
extern GFX_Result MApi_GFX_SetDFBBldFlags(MS_U16 u16DFBBldFlags);
extern GFX_Result MApi_GFX_SetDFBBldOP(GFX_DFBBldOP gfxSrcBldOP, GFX_DFBBldOP gfxDstBldOP);
extern GFX_Result MApi_GFX_SetDFBBldConstColor(GFX_RgbColor gfxRgbColor);
extern GFX_Result MApi_GFX_SetDFBBldSrcColorMask(GFX_RgbColor gfxRgbColor);
extern GFX_Result MApi_GFX_Line_Pattern_Reset(void);
extern GFX_Result MApi_GFX_Set_Line_Pattern(MS_BOOL enable, MS_U8 linePattern, MS_U8 repeatFactor);
extern GFX_Result MApi_GFX_BitBlt(GFX_DrawRect *drawbuf,MS_U32 drawflag);
extern GFX_Result MApi_GFX_BitBltEx(GFX_DrawRect * drawbuf, MS_U32 drawflag, GFX_ScaleInfo * ScaleInfo);
extern GFX_Result MApi_GFX_SetIntensity(MS_U32 id, GFX_Buffer_Format fmt, MS_U32 *pColor);
extern GFX_Result MApi_GFX_GetIntensity(MS_U32 idx, MS_U32 *color);
extern GFX_Result MApi_GFX_BeginDraw(void);
extern GFX_Result MApi_GFX_EndDraw(void);
extern GFX_Result MApi_GFX_YUV_Get(GFX_YuvInfo* pYuvInfo);
extern void MApi_GFX_RectFrame(GFX_RectFillInfo *pblock, GFX_DrawLineInfo *plinefmt);
extern GFX_Result MApi_GFX_SetDC_CSC_FMT(GFX_YUV_Rgb2Yuv mode, GFX_YUV_OutRange yuv_out_range, GFX_YUV_InRange uv_in_range, GFX_YUV_422 srcfmt, GFX_YUV_422 dstfmt);
extern GFX_Result MApi_GFX_SetPatchMode(MS_BOOL enable);
extern GFX_Result MApi_GFX_SetNearestMode(MS_BOOL enable);
extern GFX_Result MApi_GFX_GetBufferInfo(PGFX_BufferInfo srcbufInfo, PGFX_BufferInfo dstbufInfo);


extern GFX_Result MApi_GFX_ClearFrameBufferByWord(MS_PHYADDR StrAddr, MS_U32 length, MS_U32 ClearValue);
extern GFX_Result MApi_GFX_ClearFrameBuffer(MS_PHYADDR StrAddr, MS_U32 length, MS_U8 ClearValue);
extern GFX_Result MApi_GFX_SetAlpha_ARGB1555(MS_U8 coef);
extern GFX_Result MApi_GFX_GetAlpha_ARGB1555(MS_U8* coef);
extern GFX_Result MApi_GFX_SetTAGID(MS_U16 tagID);
extern GFX_Result MApi_GFX_GetTAGID(MS_U16 *tagID);
extern GFX_Result MApi_GFX_WaitForTAGID(MS_U16 tagID);
extern MS_U16      MApi_GFX_GetNextTAGID(MS_BOOL bStepTagBefore);
extern MS_U16      MApi_GFX_SetNextTAGID(void);
extern GFX_Result MApi_GFX_RegisterGetFontCB(MS_U32 (*fpGFX_CB)(MS_S8, GFX_FontInfo*)  );
extern GFX_Result MApi_GFX_RegisterGetBMPCB(MS_U32 (*fpGFX_CB)(MS_S16, GFX_BitmapInfo*)  );
extern GFX_Result MApi_GFX_EnableVCmdQueue(MS_U16 blEnable);
extern GFX_Result MApi_GFX_SetVCmdBuffer(MS_PHYADDR u32Addr, GFX_VcmqBufSize enBufSize);
extern GFX_Result MApi_GE_SetVCmd_W_Thread(MS_U8 u8W_Threshold);
extern GFX_Result MApi_GE_SetVCmd_R_Thread(MS_U8 u8R_Threshold);
extern GFX_Result MApi_GFX_SetAlphaCmp(MS_BOOL enable, GFX_ACmpOp eMode);
extern void MApi_GFX_SetDbgLevel(MS_U32 level);
extern GFX_Result MApi_GFX_FlushQueue(void) ;
extern GFX_Result MApi_GFX_SetStrBltSckType(GFX_StretchCKType type, GFX_RgbColor *color);
extern GFX_Result MApi_GFX_SetHK(MS_BOOL bIsHK) ;
extern GFX_Result MApi_GFX_GetHK(MS_BOOL *bIsHK) ;
extern GFX_Result MApi_GFX_DrawOval(GFX_OvalFillInfo *pOval);
extern GFX_Result MApi_GFX_GetStatus( MS_BOOL *pStatus );
extern GFX_Result MApi_GFX_GetLibVer(const MSIF_Version **ppVersion);
extern GFX_Result MApi_GFX_GetInfo( GFX_DbgInfo *dbg );
extern GFX_Result MApi_GFX_PowerOn(void);
extern GFX_Result MApi_GFX_PowerOff(void);
extern GFX_Result MApi_GFX_WriteProtect(MS_U8 miu,MS_U32 addr_low,MS_U32 addr_high,GFX_WPType eWPType);
extern GFX_Result MApi_GFX_GetAlignCaps(GFX_FmtAlignCapsInfo* pAlignCapsInfo);
extern GFX_Result MApi_GFX_GetGECaps(EN_GFX_CAPS eCapType, MS_U32* pRet, MS_U32 ret_size);

extern GFX_Result MApi_GFX_SetAlpha(MS_BOOL enable, GFX_BlendCoef coef, GFX_AlphaSrcFrom db_abl, MS_U8 abl_const);
extern GFX_Result MApi_GFX_SetPaletteOpt( GFX_PaletteEntry *pPalArray, MS_U16 u32PalStart, MS_U16 u32PalEnd);
extern void msAPI_GE_ClearFrameBufferByWord (MS_PHYADDR StrAddr, MS_U32 length, MS_U32 ClearValue);
extern GFX_Result MDrv_GE_EnableAlphaBlending(MS_BOOL enable);
extern GFX_Result MDrv_GE_SetAlphaBlending(GFX_BlendCoef blendcoef, MS_U8 u8ConstantAlpha);
extern void MDrv_GE_PE_SetIntensity(MS_U8 id, GFX_Buffer_Format fmt, MS_U32* pcolor);
void MApi_GE_Exit(void);

#ifdef __cplusplus
}
#endif

#endif //_API_GFX_H_

