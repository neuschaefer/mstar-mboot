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
/// @file   drvRVD.h
/// @brief  RVD Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DRV_RVD_H_
#define _DRV_RVD_H_
#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Constant & Macro Definition
////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define MSIF_RVD_LIB_CODE    {'R','V','D','_'}    //Lib code
#define MSIF_RVD_LIBVER      {'0','1'}            //LIB version
#define MSIF_RVD_BUILDNUM    {'0','1'}            //Build Number
#define MSIF_RVD_CHANGELIST  {'0','0','1','3','2','9','3','7'} //P4 ChangeList Number


//------------------------------------------------------------------------------
/// @brief \b RVD_DRV_VERSION : RVD Version
//------------------------------------------------------------------------------
#define RVD_DRV_VERSION                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_RVD_LIB_CODE,                  /* IP__                                             */  \
    MSIF_RVD_LIBVER,                    /* 0.0 ~ Z.Z                                        */  \
    MSIF_RVD_BUILDNUM,                  /* 00 ~ 99                                          */  \
    MSIF_RVD_CHANGELIST,                /* CL#                                              */  \
    MSIF_OS

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// @brief \b Name: RVD_InterruptCb
/// @brief \b Description:  RVD Interrupt callback pointer
//-----------------------------------------------------------------------------
typedef void (*RVD_InterruptCb)(void);

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: E_RVD_DEBUG_LEVEL
/// @brief \b Enum \b Description:  SHOW MGS DEBUG LEVEL of RVD
//-----------------------------------------------------------------------------
typedef enum
{
    E_RVD_DEBUG_NONE = 0x0,  ///< Disable all uart message
    E_RVD_DEBUG_INF  = 0x01, ///< output general message
    E_RVD_DEBUG_DRV  = 0x02, ///< output drv layer message
    E_RVD_DEBUG_HAL  = 0x04, ///< output hal layer message
    E_RVD_DEBUG_ERR  = 0x08  ///< Only output error message
} RVD_DebugLevel;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: RVD_DisplayMode
/// @brief \b Enum \b Description:  RVD Trick(Play)Mode (F/W used)
//-----------------------------------------------------------------------------
typedef enum
{
    E_RVD_DISPLAYMODE_NULL = 0x7000, ///<Display null
    E_RVD_DISPLAYMODE_SHOW = 0x7001, ///<Show Display
    E_RVD_DISPLAYMODE_DONE = 0x7002  ///<Display completed(One frame showed)
}  RVD_DisplayMode;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: RVD_Skip_Decode
/// @brief \b Enum \b Description:  The RVD decoding frame types.
//-----------------------------------------------------------------------------
typedef enum
{
    E_RVD_TRICKMODE_DECODE_ALL = 0, ///<DECODE ALL
    E_RVD_TRICKMODE_DECODE_I   = 1, ///<DECODE I Frame only
    E_RVD_TRICKMODE_DECODE_IP  = 2  ///<DECODE I P Frame
}  RVD_TrickMode;//FOR PLAYER USED

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: RVD_FWSourceType
/// @brief \b Enum \b Description:  The type of fw binary input source
//-----------------------------------------------------------------------------
typedef enum
{
    E_RVD_FW_SOURCE_NONE,  ///< No input fw.
    E_RVD_FW_SOURCE_DRAM,  ///< input source from DRAM.
    E_RVD_FW_SOURCE_FLASH, ///< input source from FLASH.
}RVD_FWSourceType;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: RVD_DrvStatus
/// @brief \b Struct \b Description:  Store the RVD driver status
//-----------------------------------------------------------------------------
typedef struct
{
    MS_BOOL bInit;   ///< - TRUE: Initialization success.  - FALSE: Initialization failed or not initialized yet.
    MS_BOOL bBusy;   ///< - TRUE: Driver is processing  - FALSE: Driver is Idle.
} RVD_DrvStatus;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: RVD_RVType
/// @brief \b Enum \b Description:  The RVD RV Version flag
//-----------------------------------------------------------------------------
typedef enum
{
    E_RVD_RVTYPE_FLAGRV8 = 0,///<Real Video version 8
    E_RVD_RVTYPE_FLAGRV9 = 1 ///<Real Video version 9
}  RVD_RVType;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: E_RVD_Result
/// @brief \b Enum \b Description:  General result of RVD functions
//-----------------------------------------------------------------------------
typedef enum
{
    E_RVD_RET_FAIL           = 0, ///< General fail cases.
    E_RVD_RET_SUCCESS        = 1, ///< Action success.
    E_RVD_RET_UNSUPPORTED    = 2, ///< Function is not supported by RVD driver.
    E_RVD_RET_ILLEGAL_ACCESS = 3, ///< Illegal access. like driver not initialized.
    E_RVD_RET_TIMEOUT        = 4, ///< Action timeout.
    E_RVD_RET_NOTREADY       = 5, ///< Action not ready. User needs to call it again later.
    E_RVD_RET_INVALID_PARAM  = 6, ///< Function has invalid input.
    E_RVD_RET_RE_INIT             ///< RVD driver had initialized.Avoid create new task for RVD
}  RVD_Result;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: RVD_User_Cmd
/// @brief \b Enum \b Description:  General command of RVD functions
//-----------------------------------------------------------------------------
typedef enum
{
    E_RVD_CMD_NULL = 0x0, // Null
    
    // Base
    E_RVD_CMD_NEW_BASE = 0x00010000,//Rvd cmd based
    
    //*********************************
    // Action
    //*********************************
    E_RVD_CMD_TYPE_ACTION_MASK = (0x0100|E_RVD_CMD_NEW_BASE),
    // state machine action
    E_RVD_CMD_PLAY,            // AVCH264_CMD_GO
    E_RVD_CMD_PAUSE,           // AVCH264_CMD_PAUSE
    E_RVD_CMD_STOP,            // AVCH264_CMD_STOP
    // run-time action
    E_RVD_CMD_STEP_DECODE,     // AVCH264_CMD_STEP
    E_RVD_CMD_FLUSH,           // BBU: AVCH264_CMD_DROP ,  DISP: AVCH264_CMD_FLUSH_DISPLAY , AVCH264_CMD_SKIPTOI
    // internal control action
    E_RVD_CMD_MIN_FRAME_GAP,   // For file mode only; AVCH264_CMD_MIN_FRAME_GAP
    E_RVD_CMD_DIS_VDEAD,       // 1: on :For PVR , file mode only ; 0 : off: AVCH264_CMD_DIS_VDEAD
    E_RVD_CMD_FLUSH_DEC_Q,     // DECODED: AVCH264_CMD_FLUSH_QUEUE
    E_RVD_CMD_BLUE_SCREEN,
    E_RVD_CMD_FREEZE_IMG,
    E_RVD_CMD_JUMP_TO_PTS,     // JUMP TO PTS POSITION
    E_RVD_CMD_SKIP_TO_PTS,
    E_RVD_CMD_SYNC_TOLERANCE,
    E_RVD_CMD_SYNC_VIDEO_DELAY,
    E_RVD_CMD_FREERUN_THRESHOLD,// 0x1010F

    //*********************************
    // FW settings ( only for driver init)
    //*********************************
    E_RVD_CMD_SETTINGS_MASK = (0x0200|E_RVD_CMD_NEW_BASE),
    E_RVD_CMD_DYNAMIC_SCALE,   // 0x10201
    E_RVD_CMD_SCALER_INFO,     // 0x10202
    
    //*********************************
    // Mode ( for AP run-time)
    //*********************************
    E_RVD_CMD_MODE_MASK = (0x0300|E_RVD_CMD_NEW_BASE),
    E_RVD_CMD_SKIP_DEC,        // E_HVD_DECODE_ALL ;E_HVD_DECODE_I;E_HVD_DECODE_IP; AVCH264_CMD_DEC_I , AVCH264_CMD_SKIP_NONREF
    E_RVD_CMD_SYNC_ACTIVE,     // 0: sync off; 1: sync on
    E_RVD_CMD_DISP_SPEED,      // AVCH264_CMD_TRICKY  0,1: normal speed N(>0): show N times, slow motion Nx(2,4...) ; N(<0): FF speed Nx(-2,-4,...) AVCH264_CMD_2X_SPEED
    E_RVD_CMD_DISP_ERR_FRM,    // True: display and error frame; FALSE: not show error frame ; AVCH264_CMD_ERR_TH
    E_RVD_CMD_ERR_CONCEAL,     // 1: on ; 0: off ; AVCH264_CMD_PASTE
    E_RVD_CMD_DROP_DISP_AUTO,  // ??? can we input no arg, 1:on AVCH264_CMD_DISP_DROP, 0:off AVCH264_CMD_DIS_DISP_DROP
    E_RVD_CMD_DROP_DISP_ONCE,  // AVCH264_CMD_DROP_CNT
    E_RVD_CMD_DISP_REPEAT_MAX, // Display repeat times 
    
    //*********************************
    // test cmd
    //*********************************
    E_RVD_CMD_TEST_MASK = (0x0400|E_RVD_CMD_NEW_BASE),
    E_RVD_CMD_ENABLE_LAST_FRAME_SHOW,
    E_RVD_CMD_ISR_TYPE
} RVD_User_Cmd;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: RVD_FileInfo
/// @brief \b Struct \b Description:  RVD file information
//-----------------------------------------------------------------------------
typedef struct
{
    MS_U16 RV_Version;      ///< Real Video Bitstream version
    MS_U16 ulNumSizes;      ///< Real Video Number sizes
    MS_U16 ulPicSizes_w[8]; ///< Real Video file width
    MS_U16 ulPicSizes_h[8]; ///< Real Video file height
    MS_U16 ulBufMode;       ///< Info F/W support HD/SD
    MS_U32 ulFBAddr;        ///< Frame buffer start addr
    MS_U32 ulFBSize;        ///< Frame Buffer total size + IAP size (need to be protected)
    MS_U32 ulVLCAddr;       ///< VLC Table address size :0x20000 
} RVD_FileInfo;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: RVD_MiuInfo
/// @brief \b Struct \b Description:  Store the RVD driver info
//-----------------------------------------------------------------------------
typedef struct 
{
    MS_BOOL bRVD_MiuSel;       ///<Miu select
    MS_BOOL bRVD_FWBinInMIU1;  ///<FW Binary source on miu 1
    MS_BOOL bRVD_VLCBinInMIU1; ///<VLC Binary source on miu 1 
    MS_BOOL bRVD_HWinMIU1;     ///<RVD H/W run on miu 1
    MS_BOOL bRVD_FWinMIU1;     ///<RVD F/W run on miu 1
    MS_U32 u32VLC_DstAddr;     ///<VLC Binary source addr
    MS_U32 u32VLC_DstSize;     ///<VLC Binary source size
    MS_U32 u32VLC_ScrAddr;     ///<VLC Binary source addr
    MS_U32 u32VLC_ScrSize;     ///<VLC Binary source size
    MS_U32 u32FW_ScrAddr;      ///<F/W source addr
    MS_U32 u32FW_ScrSize;      ///<F/W source size
    MS_U32 u32FW_DstAddr;      ///<F/W Dst addr
    MS_U32 u32FW_PhyAddr;      ///<F/W size <remove late>
    MS_U32 u32BDMAFlag;        ///<BDMA action flag
} RVD_MiuInfo;
extern RVD_MiuInfo gRVDInfo;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: RVD_Packet_ID
/// @brief \b Struct \b Description:  RVD Packet ID
//-----------------------------------------------------------------------------
typedef struct
{
    MS_U32 u32PacketID_HI; ///< RVD Packet ID High Addr
    MS_U32 u32PacketID_LO; ///< RVD Packet ID Low Addr

} RVD_Packet_ID;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: RVD_MEMCfg
/// @brief \b Struct \b Description:  RVD Memory Config
//-----------------------------------------------------------------------------
typedef struct
{
    RVD_FWSourceType eFWSourceType; ///< the input FW source type.
    MS_U32 u32FWAddr;               ///<RVD Open bin address
    MS_U32 u32FWSize;               ///<RVD Open bin size
    MS_U32 u32FBAddr;               ///<RVD Frame buffer start address
    MS_U32 u32FBSize;               ///<RVD Frame buffer size
    MS_U32 u32BSAddr;               ///<RVD Bitstream buffer start address
    MS_U32 u32BSSize;               ///<RVD Bitstream buffer size
    MS_U32 u32PBAddr;               ///<RVD Dummy data process buffer start address
    MS_U32 u32PBSize;               ///<RVD Dummy data process buffer size
    MS_U32 u32FWBinAddr;            ///<RVD open binary data process buffer start address
    MS_U32 u32FWBinSize;            ///<RVD open binary data process buffer size
    MS_U32 u32VLCBinAddr;           ///<RVD open binary data process buffer start address
    MS_U32 u32VLCBinSize;           ///<RVD open binary data process buffer size
} RVD_MEMCfg;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: RVD_FrameInfo
/// @brief \b Struct \b Description:  Used for RVD Video Crop
//----------------------------------------------------------------------------
typedef struct
{
    MS_U16 u16HorSize;        ///<RVD Pic weight
    MS_U16 u16VerSize;        ///<RVD Pic height
    MS_U16 u16Sar_width;      ///<RVD Par width ratio
    MS_U16 u16Sar_height;     ///<RVD Par height ratio
    MS_U8 u8par_width;        ///<RVD Par width ratio
    MS_U8 u8par_height;       ///<RVD Par height ratio
    MS_U16 u16FrameRate;      ///<RVD Frame Rate;
    MS_U16 u16CropRight;      ///<RVD Crop Right
    MS_U16 u16CropLeft;       ///<RVD Crop Left
    MS_U16 u16CropBottom;     ///<RVD Crop Bottom
    MS_U16 u16CropTop;        ///<RVD Crop Top
    MS_U32 u32DynScalingAddr; ///<DS Addr
    MS_U8 u8DynScalingDepth;  ///<DS depth
    MS_BOOL bEnableMIUSel;    ///<enable  miu select (DS used)
    MS_U32 u32AspectWidth;    ///Display width
    MS_U32 u32AspectHeight;   ///Display height
} RVD_FrameInfo;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: RVD_FrameBuff_Info
/// @brief \b Struct \b Description:  Get current frame info
//----------------------------------------------------------------------------
typedef struct
{
    MS_U32 u32LumaAddr;   ///< frame buffer base + the start offset of current displayed luma data. Unit: byte.
    MS_U32 u32ChromaAddr; ///< frame buffer base + the start offset of current displayed chroma data. Unit: byte.
    MS_U32 u32TimeStamp;  ///< Time stamp(DTS, PTS) of current displayed frame. Unit: ms (todo: 90khz)
    MS_U32 u32ID_L;       ///< low part of ID number decided by MDrv_RVD_PushQueue(). (todo)
    MS_U32 u32ID_H;       ///< high part of ID number decided by MDrv_RVD_PushQueue(). (todo)
    MS_U16 u16FrmType;    ///< RVD_Picture_Type, picture type: I, P, B frame ---> T_RVPicCodType (temp)
    MS_U16 u16Pitch;      ///<RVD frame pitch
    MS_U16 u16Width;      ///<RVD frame width
    MS_U16 u16Height;     ///<RVD frame hight
} RVD_FrameBuff_Info;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: E_RVD_CMD_SKIP_DEC_ARG
/// @brief \b Enum \b Description:  The argument of Skip Decode Mode
//-----------------------------------------------------------------------------
typedef enum
{
    E_RVD_SKIP_DECB_NONE = 0,
    E_RVD_SKIP_DECB_ONCE,
    E_RVD_SKIP_DECB_ALL
} RVD_CmdSkipDecArg;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: E_RVD_CMD_AV_SYNC_ARG
/// @brief \b Enum \b Description:  The argument of AV Sync Mode
//-----------------------------------------------------------------------------
typedef enum
{
    E_RVD_FREERUN = -1,
    E_RVD_DISABLE = 0,
    E_RVD_VIDEO_DELAY
} RVD_CmdAVSyncArg;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: E_RVD_CMD_DISP_SPEED_ARG
/// @brief \b Enum \b Description:  The argument of Display Speed
//-----------------------------------------------------------------------------
typedef enum
{
    E_RVD_SPEED_SLOW,
    E_RVD_SPEED_NORMAL,
    E_RVD_SPEED_FF
} RVD_CmdDispSpeedArg;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: E_RVD_CMD_DROP_DISP_AUTO_ARG
/// @brief \b Enum \b Description:  The argument of DROP DISPLAY
//-----------------------------------------------------------------------------
typedef enum
{
    E_RVD_DROPDISPAUTO_DISABLE = 0, ///< drop once, drop the number of non-ref frames
    E_RVD_DROPDISPAUTO_ENABLE       ///< automatic drop mode, drop frame if display queue is more than threshold
} RVD_CmdDropDispAutoArg;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: RVD_Disp_Speed
/// @brief \b Enum \b Description:  The current mode type of RVD display speed
//-----------------------------------------------------------------------------
typedef enum
{
    E_RVD_DISP_SPEED_FF_32X    = -32, ///< Speed fast forward 32x.
    E_RVD_DISP_SPEED_FF_16X    = -16, ///< Speed fast forward 16x.
    E_RVD_DISP_SPEED_FF_8X     = -8,  ///< Speed fast forward 8x.
    E_RVD_DISP_SPEED_FF_4X     = -4,  ///< Speed fast forward 4x.
    E_RVD_DISP_SPEED_FF_2X     = -2,  ///< Speed fast forward 2x.
    E_RVD_DISP_SPEED_NORMAL_1X = 1,   ///< Normal display speed.
    E_RVD_DISP_SPEED_SF_2X     = 2,   ///< Slow forward 2X.
    E_RVD_DISP_SPEED_SF_4X     = 4,   ///< Slow forward 4X.
    E_RVD_DISP_SPEED_SF_8X     = 8,   ///< Slow forward 8X.
    E_RVD_DISP_SPEED_SF_16X    = 16,  ///< Slow forward 16X.
    E_RVD_DISP_SPEED_SF_32X    = 32,  ///< Slow forward 32X.
}RVD_Disp_Speed;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: RVD_Drop_Disp
/// @brief \b Enum \b Description:  The current mode type of RVD dropping decoded frames.
//-----------------------------------------------------------------------------
typedef enum
{
    E_RVD_DROP_DISPLAY_AUTO = (1<<0),
    E_RVD_DROP_DISPLAY_ONCE = (1<<1),
}RVD_Drop_Disp;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: RVD_MMAP_Type
/// @brief \b Enum \b Description:Memory Config
//-----------------------------------------------------------------------------
typedef enum
{
    E_RVD_MMAP_FW      = 0, //firmware
    E_RVD_MMAP_BS      = 1, //bitstream buffer
    E_RVD_MMAP_FB      = 2, //frame buffer
    E_RVD_MMAP_PB      = 3, //process buffer
    E_RVD_MMAP_FW_BIN  = 4, //firmware binary format
    E_RVD_MMAP_VLC_BIN = 5, //VLC table binary format
    E_RVD_MMAP_ALL     = 6  //get all memory map
} RVD_MMAP_Type;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: RVD_ActionMode
/// @brief \b Enum \b Description:Action Mode
//-----------------------------------------------------------------------------
typedef enum
{
    E_RVD_ACTIONMODE_IDEL       = 0, //action mode in idel
    E_RVD_ACTIONMODE_PLAY       = 1, //play mode
    E_RVD_ACTIONMODE_PAUSE      = 2, //pause mode
    E_RVD_ACTIONMODE_STOP       = 3, //stop mode
    E_RVD_ACTIONMODE_STEPDECODE = 4  //step play mode
} RVD_ActionMode;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: RVD_ActionMode
/// @brief \b Enum \b Description:Action Mode
//-----------------------------------------------------------------------------
typedef enum
{
    E_RVD_PICCODTYPE_INTRAPIC,        /* 0 (00) */
    E_RVD_PICCODTYPE_FORCED_INTRAPIC, /* 1 (01) */
    E_RVD_PICCODTYPE_INTERPIC,        /* 2 (10) */
    E_RVD_PICCODTYPE_TRUEBPIC         /* 3 (11) */
} RVD_PicCodType;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: RVD_StatusType
/// @brief \b Enum \b Description:Status Type
//-----------------------------------------------------------------------------
typedef enum
{
    E_RVD_STATUSTYPE_AVSYNCON               = BIT(0), ///AV Sync mode on
    E_RVD_STATUSTYPE_IFRAMEFOUND            = BIT(1), ///The I frame found
    E_RVD_STATUSTYPE_PLAYBACK_FINISH        = BIT(2), ///the display finish
    E_RVD_STATUSTYPE_ENABLE_LAST_FRAME_SHOW = BIT(3), ///the last frame show be enabled
    E_RVD_STATUSTYPE_BLUE_SCREEN            = BIT(4), ///the blue screen had be enabled
    E_RVD_STATUSTYPE_FREEZE_IMG             = BIT(5), ///the freeze img had be enabled
    E_RVD_STATUSTYPE_SKIP_DECODE            = BIT(6),
    E_RVD_STATUSTYPE_1ST_FRAMERDY           = BIT(7)
} RVD_StatusType;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: RVD_ErrorCode
/// @brief \b Enum \b Description:Error code reported by F/W
//-----------------------------------------------------------------------------
typedef enum
{
    E_ERROR_NONE = 0,       ///no error
    E_ERROR_PACKET_HEADER,  ///< packet header version error
    E_ERROR_FRAME_HEADER,   ///< frame type error
    E_ERROR_SLICE_HEADER,   ///<slice header error
    E_ERROR_DECODE_TIMEOUT, ///< decode MB timeout
    E_ERROR_OUT_OF_MEMORY,  ///< frame buffer is out of memory
    E_ERROR_BYTE_POS,       ///< can not find in ID table
    E_ERROR_DISPLAY_TIMEOUT
} RVD_ErrorCode;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: RVD_DrvInfo
/// @brief \b Struct \b Description:  Store the RVD driver information
//-----------------------------------------------------------------------------
typedef struct
{
    MS_BOOL bRVD;     ///< - TRUE: HW does support RM.  - FALSE: HW does not support RM.
    MS_U32 HWversion; ///<- HW version number.
    MS_U32 FWversion; ///<  FW version number.
}RVD_DrvInfo;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: HVD_ISR_Event
/// @brief \b Enum \b Description:  The information type of ISR event.
//-----------------------------------------------------------------------------
typedef enum
{
    E_RVD_ISR_NONE                 = 0,       ///< disable ISR
    // DISP
    E_RVD_ISR_DISP_ONE             = BIT(0),  ///< RVD display one frame on screen.
    E_RVD_ISR_DISP_REPEAT          = BIT(1),  ///< The current displayed frame is repeated frame.
    E_RVD_ISR_DISP_WITH_CC         = BIT(2),  ///< Current displayed frame should be displayed with user data.
    // DEC
    E_RVD_ISR_DEC_ONE              = BIT(8),  ///< RVD decoded one frame done.
    E_RVD_ISR_DEC_I                = BIT(9),  ///< RVD decoded one I frame done.
    E_RVD_ISR_DEC_HW_ERR           = BIT(10), ///< RVD HW found decode error.
    E_RVD_ISR_DEC_CC_FOUND         = BIT(11), ///< RVD found one user data with decoded frame.
    E_RVD_ISR_DEC_DISP_INFO_CHANGE = BIT(12), ///< RVD found display information change.
    E_RVD_ISR_DEC_DATA_ERR         = BIT(13), ///< RVD HW found decode error.
} RVD_ISR_Event;

/************* RVD debug define *************/
#define RVD_MSG_INF(format, args...)  do{if(MDrv_RVD_IsDbgEnable(E_RVD_DEBUG_INF)) printf(format, ##args);}while(0) ///< output general message
#define RVD_MSG_DRV(format, args...)  do{if(MDrv_RVD_IsDbgEnable(E_RVD_DEBUG_DRV)) printf(format, ##args);}while(0)///< output drv layer message
#define RVD_MSG_HAL(format, args...)  do{if(MDrv_RVD_IsDbgEnable(E_RVD_DEBUG_HAL)) printf(format, ##args);}while(0)///< output hal layer message
#define RVD_MSG_ERR(format, args...)  do{if(MDrv_RVD_IsDbgEnable(E_RVD_DEBUG_ERR)) printf(format, ##args);}while(0)///< Only output error message


//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
extern void MDrv_RVD_SetBBU_OffsetLength(MS_U32 u32Address,MS_U32 u32offset, MS_U32 u32length);
extern MS_S16 MDrv_RVD_GetQmemSwBbuVacancy(void);
extern void MDrv_RVD_GetFrameSize(MS_U16*  u16Width,MS_U16*  u16Height);
extern MS_U32 MDrv_RVD_GetBBUStartAddr(void);
extern MS_U32 MDrv_RVD_GetTimeStamp(void);
extern MS_U32 MDrv_RVD_GetDecodeCnt(void);
extern void MDrv_RVD_SetBBUDepth(MS_U32 u32Rptr);
extern void MDrv_RVD_SetBBUReadPtr(MS_U32 u32Rptr);
extern void MDrv_RVD_SetBBUWritePtr(MS_U32 u32Wptr);
extern MS_U32 MDrv_RVD_GetBBUReadPtr(void);
extern MS_U32 MDrv_RVD_GetBBUWritePtr(void);
extern MS_U16 MDrv_RVD_GetBBUDepth(void);
extern void MDrv_RVD_SetPictureSize(MS_U16 u16Width, MS_U16 u16Height);
extern void MDrv_RVD_SetDisplay(RVD_DisplayMode u32PlayMode);
extern void MDrv_RVD_PushBBU (MS_U32 u32offset, MS_U32 u32length ,RVD_Packet_ID *rvdPackerInfo);
extern void MDrv_RVD_SetFileInfo(RVD_FileInfo *pFileInfo);
extern RVD_Result MDrv_RVD_Init(RVD_FileInfo *pFileInfo,RVD_MEMCfg* memCfg);
extern RVD_Result MDrv_RVD_EnableDynamicScaling(MS_BOOL bEnable);
extern void MDrv_RVD_SetVirtualBox(MS_U16 u16Width, MS_U16 u16Height);
extern RVD_Result MDrv_RVD_SetDynScalingParam(MS_U32 u32StAddr, MS_U32 u32Size);
extern RVD_Result MDrv_RVD_FlushQueue(void);
extern MS_U32 MDrv_RVD_GetESReadPtr(void);
extern MS_U32 MDrv_RVD_ReadSVDProgramCounter(void);
extern RVD_Result MDrv_RVD_ChkCmdRdy(void);
extern RVD_Result MDrv_RVD_SetCmd(RVD_User_Cmd u32Command,MS_U32 u32Argument);
extern RVD_Result MDrv_RVD_SetSpeed(RVD_Disp_Speed u32DispSpeed);
extern MS_BOOL MDrv_RVD_IsDbgEnable(MS_U8 u8DbgLevel);
extern MS_U8 MDrv_RVD_GetDbgLevel(void);
extern void MDrv_RVD_SetDbgLevel(MS_U8 u8DbgLevel);
extern RVD_Result MDrv_RVD_SetCfg( RVD_MEMCfg* memCfg);
extern void MDrv_RVD_SetOSRegBase(MS_U32 u32RegBaseAddr );
extern MS_U32 MDrv_RVD_GetFrameCnt(void);
extern MS_U32 MDrv_RVD_GetESWritePtr(void);
extern MS_BOOL MDrv_RVD_CheckDispInfoRdy(void);
extern MS_BOOL MDrv_RVD_CheckCaps(void);
extern MS_BOOL MDrv_RVD_IsTSPlaying(void);
extern void MDrv_RVD_SetTrickMode(RVD_TrickMode u32TrickMode);
extern RVD_Result MDrv_RVD_Play(void);
extern RVD_Result MDrv_RVD_AVSyncOn(MS_BOOL  bEnable,MS_U16 u16SyncDelay, MS_U16 u16SyncTolerance);
extern MS_BOOL MDrv_RVD_IsAVSyncOn(void);
extern RVD_Result MDrv_RVD_Pause(void);
extern RVD_Result MDrv_RVD_Exit(void);
extern RVD_Result MDrv_RVD_Resume(void);
extern RVD_Result MDrv_RVD_EnableLastFrameShowed(MS_BOOL bEnabled);
extern RVD_Result MDrv_RVD_StepPlay(void);
extern MS_BOOL MDrv_RVD_IsStepPlayDone(void);
extern MS_BOOL MDrv_RVD_IsIdle(void);
extern MS_BOOL MDrv_RVD_IsDispFinish(void);
extern MS_BOOL MDrv_RVD_IsIFrameFound(void);
extern MS_U32 MDrv_RVD_GetErrCode(void);
extern RVD_Result MDrv_RVD_DbgGetData(MS_U32 u32Addr , MS_U32 *u32Data);
extern RVD_Result MDrv_RVD_GetLibVer(const MSIF_Version **ppVersion);
extern MS_BOOL MDrv_RVD_DispSetupDone(void);
extern RVD_Result  MDrv_RVD_GetDispInfo(RVD_FrameInfo *pinfo);
extern MS_BOOL MDrv_RVD_GetStatus( RVD_DrvStatus *pstatus);
extern void MDrv_RVD_SetBBU_ID(MS_U32 u32Address,MS_U32 u32Byte_Pos,MS_U32 u32ID_High, MS_U32 u32ID_Low);
const RVD_DrvInfo* MDrv_RVD_GetInfo( void );
extern MS_U32 MDrv_RVD_GetIDReadPtr(void);
extern MS_U32 MDrv_RVD_GetIDWritePtr(void);
extern void MDrv_RVD_SetIDWritePtr(MS_U32 u32Wptr);
extern void MDrv_RVD_SetIDReadPtr(MS_U32 u32Wptr);
extern RVD_Result MDrv_RVD_GetFrameInfo(RVD_FrameBuff_Info *framebuffinfo ,MS_BOOL bGETDISP);
extern MS_BOOL MDrv_RVD_SetForceISR(MS_BOOL bEnable);
extern MS_BOOL MDrv_RVD_GetISRInfo( RVD_ISR_Event* eType );
extern MS_BOOL MDrv_RVD_SetEnableISR(MS_BOOL bEnable);
extern RVD_Result MDrv_RVD_SetISREvent(RVD_ISR_Event eEvent ,RVD_InterruptCb fnISRHandler );
extern RVD_Result MDrv_RVD_SetDispRepeatCnt(MS_U32 u32Num);
//extern void MDrv_RVD_ResetSTCBase(MS_U32 u32time_ms);
extern RVD_Result MDrv_RVD_JumpToPTS(MS_U32 u32time_ms);
extern RVD_Result MDrv_RVD_SkipToPTS(MS_U32 u32time_ms);
extern MS_U32 MDrv_RVD_GetTrickMode(void);
extern MS_BOOL MDrv_RVD_IsStepDecodeDone(void);
extern RVD_Result MDrv_RVD_StepDecode(void);
extern RVD_Result MDrv_RVD_Rst(void );
extern RVD_Result MDrv_RVD_SetFreezeImg(MS_BOOL bEnabled);
extern RVD_Result MDrv_RVD_SetBlueScreen(MS_BOOL bEnabled);
extern RVD_Result MDrv_RVD_FireDecCmd(void);
extern MS_BOOL MDrv_RVD_Is1stFrameRdy(void);
extern MS_U32 MDrv_RVD_GetDecErrCnt(void);
extern MS_U32 MDrv_RVD_GetDataErrCnt(void);
extern MS_U32 MDrv_RVD_GetSkipCnt(void);
extern MS_U32 MDrv_RVD_GetDropCnt(void);
extern MS_U32 MDrv_RVD_GetDispQueNum(void);
extern RVD_Result MDrv_RVD_DbgSetCmd(RVD_User_Cmd u32Command,MS_U32 u32Argument);
extern void MDrv_RVD_DbgSetData(MS_U32 u32Addr,MS_U32 data);
extern void MDrv_RVD_Dump_Status(void);
#if 0
#if defined(REDLION_LINUX_KERNEL_ENVI)
extern MS_S32 _DRV_RVD_ISRHandler(void);
#else
extern void _DRV_RVD_ISRHandler(void);
#endif
#endif

extern void MDrv_RVD_EnableTurboFWMode(MS_BOOL bEnable);

extern RVD_Result MDrv_RVD_SetAVSyncFreerunThreshold(MS_U32 u32Th);

#ifdef __cplusplus
}
#endif

#endif // _DRV_RVD_H_


