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

#include "MsDevice.h"
#include "apiGOP_v2.h"
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

#ifndef MAX_GWIN_FB_SUPPORT
///MAX_GWIN_FB_SUPPORT
#define MAX_GWIN_FB_SUPPORT 32
#endif

#define MAX_NUM_GOP_API_INF_SUPPORT 6

//the macro defines only be applied for the upper user, not for the internal driver,otherwise it will cause the deadlock
#define MAX_GOP0_SUPPORT MApi_GOP_GWIN_GetGwinNum(0)
#define MAX_GOP1_SUPPORT MApi_GOP_GWIN_GetGwinNum(1)
#define MAX_GOP2_SUPPORT MApi_GOP_GWIN_GetGwinNum(2)
#define MAX_GOP3_SUPPORT MApi_GOP_GWIN_GetGwinNum(3)
#define MAX_GOP4_SUPPORT MApi_GOP_GWIN_GetGwinNum(4)
#define MAX_GOP5_SUPPORT MApi_GOP_GWIN_GetGwinNum(5)
//#define MAX_GOP_SUPPORT MApi_GOP_GWIN_GetMaxGOPNum()

//the macro defines only be applied for the upper user, not for the internal driver,otherwise it will cause the deadlock
#define GOP0_GWIN_START 0
#define GOP1_GWIN_START MAX_GOP0_SUPPORT
#define GOP2_GWIN_START MAX_GOP0_SUPPORT + MAX_GOP1_SUPPORT
#define GOP3_GWIN_START MAX_GOP0_SUPPORT + MAX_GOP1_SUPPORT + MAX_GOP2_SUPPORT
#define GOP4_GWIN_START MAX_GOP0_SUPPORT + MAX_GOP1_SUPPORT + MAX_GOP2_SUPPORT + MAX_GOP3_SUPPORT
#define GOP5_GWIN_START MAX_GOP0_SUPPORT + MAX_GOP1_SUPPORT + MAX_GOP2_SUPPORT + MAX_GOP3_SUPPORT + MAX_GOP4_SUPPORT

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



///the GOP and mux setting info on utopia
typedef struct _GOP_MuxConfig
{
  //GopMux arrays record the u8GopIndex and the corresponding MuxIndex
  //u8MuxCounts: how many mux need to modify the gop settings

  struct
  {
      MS_U8 u8GopIndex;
      MS_U8 u8MuxIndex;
  }GopMux[6];
  MS_U8 u8MuxCounts;
}GOP_MuxConfig, *PGOP_MuxConfig;

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
    E_GOP_CAP_PIXELMODE_SUPPORT,
}EN_GOP_CAPS;

// GOP palette type
typedef enum
{
    E_GOP_CAP_PAL_SIZE_NONE = 0x0000,
    E_GOP_CAP_PAL_SIZE_256  = 0x0100,
    E_GOP_CAP_PAL_SIZE_64   = 0x0200,
    E_GOP_CAP_PAL_SIZE_MASK = 0x0F00,
}EN_GOP_CAP_PAL;


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
E_GOP_API_Result Mapi_GOP_GWIN_ResetGOP(MS_U32 u32Gop);
E_GOP_API_Result MApi_GOP_GWIN_ResetPool(void);
/******************************************************************************/
/// set GOP power state
/// @param enPowerState\b IN power status
/******************************************************************************/
E_GOP_API_Result MApi_GOP_SetPowerState(EN_POWER_MODE enPowerState);
E_GOP_API_Result MApi_GOP_SetGOPBWStrength(EN_GOP_BW_STRENGTH eGOPBWStr, MS_U8 u8GOP);
E_GOP_API_Result MApi_GOP_GetGOPBWStrength(MS_U8 u8GOP, EN_GOP_BW_STRENGTH* curBW);
E_GOP_API_Result MApi_GOP_SetGOPHStart(MS_U8 u8GOP,MS_U16 u16PanelHStr);
E_GOP_API_Result MApi_GOP_SetGOPBrightness(MS_U8 u8GOP,MS_U16 u16BriVal,MS_BOOL bMSB);
E_GOP_API_Result MApi_GOP_GetGOPBrightness(MS_U8 u8GOP,MS_U16* u16BriVal,MS_BOOL* bMSB);
E_GOP_API_Result MApi_GOP_EnableLBCouple(MS_U8 u8GOP, MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_VE_SetOutputTiming(GOP_VE_TIMINGTYPE mode);
E_GOP_API_Result MApi_GOP_Enable_VEOSD(MS_U8 u8GOP, MS_BOOL bEn);
E_GOP_API_Result MApi_GOP_MIXER_SetOutputTiming(GOP_MIXER_TIMINGTYPE mode, GOP_MixerTiming *pMT);
E_GOP_API_Result MApi_GOP_MIXER_SetMIXER2OPOutputTiming(GOP_Mixer2OPTiming *pMT);
E_GOP_API_Result MApi_GOP_MIXER_EnableVfilter(MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_MIXER_EnableOldBlendMode(MS_U8 u8GOP, MS_BOOL bEnable);
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
E_GOP_API_Result MApi_GOP_SetConfig(EN_GOP_CONFIG_TYPE type, MS_U32 *plist);

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
E_GOP_API_Result MApi_GOP_GWIN_EnableTransClr_EX(MS_U8 u8GOP,EN_GOP_TRANSCLR_FMT fmt, MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_EnableProgressive(MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_EnableProgressive_EX(MS_U8 u8GOP,MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_DeleteWin(MS_U8 winId);
E_GOP_API_Result MApi_GOP_GWIN_ReleaseWin(MS_U8 gId);
E_GOP_API_Result MApi_GOP_GWIN_DestroyWin(MS_U8 gId);
E_GOP_API_Result MApi_GOP_GWIN_OutputLayerSwitch(MS_U8 u8GOP);
E_GOP_API_Result MApi_GOP_GWIN_SetMux(GOP_MuxConfig * pGopMuxConfig, MS_U32 u32SizeOfMuxInfo);
E_GOP_API_Result MApi_GOP_GWIN_DeleteWinHVSize(MS_U8 u8GOP, MS_U16 u16HSize, MS_U16 u16VSize);

/*******************************************************************************/
//Set which OSD Layer select which GOP
//@param pGopLayer \b IN:information about GOP and corresponding Layer
//   #u32LayerCounts: the total GOP/Layer counts to set
//   #stGopLayer[i].u32GopIndex :the GOP which need to change Layer
//   #stGopLayer[i].u32LayerIndex :the GOP corresponding Layer
//@return GOP_API_SUCCESS - Success
/*******************************************************************************/
E_GOP_API_Result MApi_GOP_GWIN_SetLayer(GOP_LayerConfig *pGopLayer, MS_U32 u32SizeOfLayerInfo);
E_GOP_API_Result MApi_GOP_GWIN_OutputColor(EN_GOP_OUTPUT_COLOR type);
E_GOP_API_Result MApi_GOP_GWIN_OutputColor_EX(MS_U8 u8GOP,EN_GOP_OUTPUT_COLOR type);
E_GOP_API_Result MApi_GOP_GWIN_SwapOverlapWin(MS_U8 u8GOP, MS_U8 u8win);
E_GOP_API_Result MApi_GOP_GWIN_SetRelativeWinPrio(MS_U8 u8GOP, GOP_GwinPri *pGwinPri);
E_GOP_API_Result MApi_GOP_GWIN_Switch2Gwin(MS_U8 winId);
E_GOP_API_Result MApi_GOP_GWIN_SetAlphaInverse(MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_SetAlphaInverse_EX(MS_U8 u8GOP,MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_GetAlphaInverse(MS_BOOL *bEnable);
E_GOP_API_Result MApi_GOP_GWIN_GetAlphaInverse_EX(MS_U8 u8GOP,MS_BOOL *bEnable);
E_GOP_API_Result MApi_GOP_GWIN_SetPalette(void);
E_GOP_API_Result MApi_GOP_GWIN_SetAlphaValue(MS_U16 * Gwin01AlphaValue, MS_U16 * Gwin23AlphaValue);
void MApi_GOP_GWIN_SetHScroll(MS_U8 nWinID, MS_U8 nRate, MS_BOOL bEnable);
void MApi_GOP_GWIN_SetVScroll(MS_U8 nWinID, MS_U8 nRate, MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_SetScrollRate(MS_U8 u8rate);
E_GOP_API_Result MApi_GOP_GWIN_SetScrollType(MS_U8 u8WinId, GOP_SCROLL_TYPE type,  MS_U16 u16Offset, MS_BOOL bEnable );
E_GOP_API_Result MApi_GOP_GWIN_SetSWScrollBuffer(MS_U16 bufNum, MS_U32* pBuffer);
E_GOP_API_Result MApi_GOP_GWIN_SetFMT0TransClr(MS_U16 clr);
E_GOP_API_Result MApi_GOP_GWIN_SetFMT0TransClr_EX(MS_U8 u8GOP,MS_U16 clr);
E_GOP_API_Result MApi_GOP_GWIN_SetTransClr_8888(MS_U32 clr, MS_U32 mask);
E_GOP_API_Result MApi_GOP_GWIN_SetTransClr_8888_EX(MS_U8 u8GOP,MS_U32 clr, MS_U32 mask);
E_GOP_API_Result MApi_GOP_GWIN_EnableT3DMode(MS_BOOL bEnable);

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
E_GOP_API_Result MApi_GOP_GWIN_SetBlending(MS_U8 u8win, MS_BOOL bEnable, MS_U8 u8coef);

E_GOP_API_Result MApi_GOP_GWIN_SetDuplication(MS_U8 hext, MS_U8 vext);
E_GOP_API_Result MApi_GOP_GWIN_SetWinPosition(MS_U8 winId, MS_U16 dispX, MS_U16 dispY);
E_GOP_API_Result MApi_GOP_GWIN_SetWinPositionOffset(MS_U8 winId, MS_U16 x, MS_U16 y);
E_GOP_API_Result MApi_GOP_GWIN_SetWinProperty(GOP_GwinDispProperty WinProperty);
E_GOP_API_Result MApi_GOP_GWIN_SetGOPDst(MS_U8 u8GOP, EN_GOP_DST_TYPE dsttype);
E_GOP_API_Result MApi_GOP_GWIN_SetBlink(MS_BOOL bEnable, MS_U8 u8rate);
E_GOP_API_Result MApi_GOP_GWIN_SetFieldInver(MS_BOOL enable);
E_GOP_API_Result MApi_GOP_GWIN_SetFieldInver_EX(MS_U8 u8GOP,MS_BOOL enable);
E_GOP_API_Result MApi_GOP_GWIN_Set_STRETCHWIN(MS_U8 u8GOP_num, EN_GOP_DST_TYPE eDstType,MS_U16 x, MS_U16 y, MS_U16 width, MS_U16 height);
E_GOP_API_Result MApi_GOP_GWIN_SetStretchWinPosition(MS_U8 u8GOPNum, MS_U16 u16DispX, MS_U16 u16DispY);
E_GOP_API_Result MApi_GOP_GWIN_SetHDisplaySize(MS_U8 gId, MS_U16 Width,MS_U16 X_Start);
E_GOP_API_Result MApi_GOP_GWIN_SetWinInfo(MS_U8 u8win, GOP_GwinInfo* pinfo);
E_GOP_API_Result MApi_GOP_GWIN_SetTransClr(EN_GOP_TRANSCLR_FMT fmt, MS_U16 clr);
E_GOP_API_Result MApi_GOP_GWIN_SetTransClr_EX(MS_U8 u8GOP,EN_GOP_TRANSCLR_FMT fmt, MS_U16 clr);
E_GOP_API_Result MApi_GOP_GWIN_SetWinDispPosition(MS_U8 gId, MS_U16 dispX, MS_U16 dispY);
E_GOP_API_Result MApi_GOP_GWIN_SetHMirror(MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_SetHMirror_EX(MS_U8 u8GOP,MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_SetVMirror(MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_SetVMirror_EX(MS_U8 u8GOP,MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_IsMirrorOn(MS_BOOL *bHMirror, MS_BOOL *bVMirror);
E_GOP_API_Result MApi_GOP_GWIN_IsMirrorOn_EX(MS_U8 u8GOP,MS_BOOL *bHMirror, MS_BOOL *bVMirror);
E_GOP_API_Result MApi_GOP_GWIN_Set_HSCALE(MS_BOOL bEnable, MS_U16 src, MS_U16 dst) ;
E_GOP_API_Result MApi_GOP_GWIN_Set_HSCALE_EX(MS_U8 u8GOP,MS_BOOL bEnable, MS_U16 src, MS_U16 dst);
E_GOP_API_Result MApi_GOP_GWIN_Set_VSCALE(MS_BOOL bEnable, MS_U16 src, MS_U16 dst) ;
E_GOP_API_Result MApi_GOP_GWIN_Set_VSCALE_EX(MS_U8 u8GOP,MS_BOOL bEnable, MS_U16 src, MS_U16 dst);
E_GOP_API_Result MApi_GOP_GWIN_Set_HStretchMode(EN_GOP_STRETCH_HMODE HStrchMode);
E_GOP_API_Result MApi_GOP_GWIN_Set_HStretchMode_EX(MS_U8 u8GOP,EN_GOP_STRETCH_HMODE HStrchMode);
E_GOP_API_Result MApi_GOP_GWIN_Set_VStretchMode(EN_GOP_STRETCH_VMODE VStrchMode);
E_GOP_API_Result MApi_GOP_GWIN_Set_VStretchMode_EX(MS_U8 u8GOP,EN_GOP_STRETCH_VMODE VStrchMode);
E_GOP_API_Result MApi_GOP_GWIN_Set_TranspColorStretchMode(EN_GOP_STRCH_TRANSPCOLORMODE  TColorStrchMode);
E_GOP_API_Result MApi_GOP_GWIN_Set_TranspColorStretchMode_EX(MS_U8 u8GOP,EN_GOP_STRCH_TRANSPCOLORMODE  TColorStrchMode);
E_GOP_API_Result MApi_GOP_GWIN_SetForceWrite(MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_SetBnkForceWrite(MS_U8 u8GOP, MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_GetAlphaValue(MS_U16 * Gwin01AlphaValue, MS_U16 * Gwin23AlphaValue);
E_GOP_API_Result MApi_GOP_GWIN_GetWinPosition(MS_U8 winId, MS_U16 * dispX, MS_U16 *dispY);
E_GOP_API_Result MApi_GOP_GWIN_GetWinProperty(GOP_GwinDispProperty *WinProperty);
E_GOP_API_Result MApi_GOP_GWIN_GetWinAttr(MS_U8 gId, MS_U16 *x0, MS_U16 *y0, MS_U16 *width, MS_U16 *height,  MS_U16 *fbPitch, MS_U16 *fbFmt, MS_U32 *addr, MS_U32 *size);
E_GOP_API_Result MApi_GOP_GWIN_GetWinInfo(MS_U8 u8win, GOP_GwinInfo* pinfo);
E_GOP_API_Result MApi_GOP_GWIN_UpdateRegOnceEx(MS_BOOL bWriteRegOnce, MS_BOOL bSync);
E_GOP_API_Result MApi_GOP_GWIN_UpdateRegOnceEx2(MS_U8 u8GOP,MS_BOOL bWriteRegOnce, MS_BOOL bSync);
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
MS_BOOL MApi_GOP_GWIN_CheckOpmodeIsOn_EX(MS_U8 u8GOP);
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
MS_BOOL MApi_GOP_Switch_Multi_GWIN_2_FB_BY_ADDR(GOP_MultiFlipInfo GopMultiFlipInfo);
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
E_GOP_API_Result MApi_GOP_GWIN_SetPaletteOpt_EX(MS_U8 u8GOP,GOP_PaletteEntry *pPalArray, MS_U16 u32PalStart, MS_U16 u32PalEnd, EN_GOP_PALETTE_TYPE ePalType);
E_GOP_API_Result MApi_GOP_GWIN_SetPaletteRead(EN_GOP_PALETTE_READTYPE type);
E_GOP_API_Result MApi_GOP_GWIN_SetPaletteRead_EX(MS_U8 u8GOP,EN_GOP_PALETTE_READTYPE type);
E_GOP_API_Result MApi_GOP_GWIN_ReadPalette(MS_U8 idx, MS_U32* clr);
E_GOP_API_Result MApi_GOP_GWIN_ReadPalette_EX(MS_U8 u8GOP,MS_U8 idx, MS_U32* clr);

E_GOP_API_Result MApi_GOP_GWIN_2GSetPaletteOpt(GOP_PaletteEntry *pPalArray, MS_U16 u32PalStart, MS_U16 u32PalEnd);
E_GOP_API_Result MApi_GOP_GWIN_2GSetPaletteOpt_EX(MS_U8 u8GOP,GOP_PaletteEntry *pPalArray, MS_U16 u32PalStart, MS_U16 u32PalEnd);
E_GOP_API_Result MApi_GOP_GWIN_2GSetPaletteRead(EN_GOP_PALETTE_READTYPE type);
E_GOP_API_Result MApi_GOP_GWIN_2GSetPaletteRead_EX(MS_U8 u8GOP,EN_GOP_PALETTE_READTYPE type);
E_GOP_API_Result MApi_GOP_GWIN_2GReadPalette(MS_U8 idx, MS_U32* clr);
E_GOP_API_Result MApi_GOP_GWIN_2GReadPalette_EX(MS_U8 u8GOP,MS_U8 idx, MS_U32* clr);


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
E_GOP_API_Result MApi_GOP_DWIN_SetAlphaSrc(EN_GOP_DWIN_ALPHA_SRC source);
E_GOP_API_Result MApi_GOP_DWIN_SetAlphaInverse(MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_DWIN_SetUVSample(EN_GOP_DWIN_UVSAMPLE_Mode mode);
E_GOP_API_Result MApi_GOP_DWIN_SetSkipFrame(MS_U32 framecount);
E_GOP_API_Result MApi_GOP_DWIN_ClearIntr(MS_U16 u8mask);
E_GOP_API_Result MApi_GOP_DWIN_GetDWinIntInfo(GOP_DWinIntInfo *pDWinIntInfo);
E_GOP_API_Result MApi_GOP_DWIN_GetDWinIntInfoTimeout(GOP_DWinIntInfo *pDWinIntInfo, MS_U32 u32Timeout);
E_GOP_API_Result MApi_GOP_SetClkForCapture(void);   //only for source is OP path clock
MS_U16 MApi_GOP_DWIN_GetIntrStatus(void);
E_GOP_API_Result MApi_GOP_DWIN_EnableR2YCSC(MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_DWIN_SetUVSwap(MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_BeginDraw(void);
E_GOP_API_Result MApi_GOP_GWIN_EndDraw(void);
E_GOP_API_Result MApi_GOP_GWIN_Enable_BGWIN(MS_U8 bgwID, MS_BOOL bEnable);
E_GOP_API_Result MApi_GOP_GWIN_Set_BGWIN(MS_U8 bgwID, MS_U16 x0, MS_U16 y0, MS_U16 w, MS_U16 h, MS_U16 color);
E_GOP_API_Result MApi_GOP_GWIN_Set_BGWIN_Alpha(MS_U8 bgwID, MS_BOOL bEnable, MS_U8 alpha);
E_GOP_API_Result MApi_GOP_DWIN_SetBufferPINPON(MS_U32 u32fbaddr0,MS_U32 u32fbaddr1);
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

