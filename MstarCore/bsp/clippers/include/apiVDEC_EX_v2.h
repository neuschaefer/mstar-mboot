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
// comply with all applicable laws and regulations
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
//    or otherwise
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

#ifndef _VDEC_EX_V2_H_
#define _VDEC_EX_V2_H_

#if !defined(MSOS_TYPE_NUTTX) || defined(SUPPORT_X_MODEL_FEATURE)
#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"
//-------------------------------------------------------------------------------------------------
//  Define for Upper layer
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define MSIF_VDEC_EX_V2_LIB_CODE      {'V','E','X','2'}
#define MSIF_VDEC_EX_V2_LIBVER        {'0','5'}
#define MSIF_VDEC_EX_V2_BUILDNUM      {'0','3'}
#define MSIF_VDEC_EX_V2_CHANGELIST    {'0','0','6','9','3','0','7','7'}

/// Version string.
#define VDEC_EX_V2_API_VERSION                /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_VDEC_EX_V2_LIB_CODE,                 /* IP__                                             */  \
    MSIF_VDEC_EX_V2_LIBVER,                   /* 0.0 ~ Z.Z                                        */  \
    MSIF_VDEC_EX_V2_BUILDNUM,                 /* 00 ~ 99                                          */  \
    MSIF_VDEC_EX_V2_CHANGELIST,               /* CL#                                              */  \
    MSIF_OS

#define VDEC_EX_V2_DEFAULT_DBG_MSG_LEVEL  E_VDEC_EX_DBG_LEVEL_DBG
#define VDEC_EX_V2_RVD_BROKEN_BY_US   0x80000000
#define VDEC_EX_V2_MVD_PIC_START_FLAG 0x40000000

#define VDEC_EX_V2_BIT(_bit_)                  (1 << (_bit_))

#define VDEC_EX_V2_FPA_TYPE_CHECKERBOARD_INTERLEAVING  0
#define VDEC_EX_V2_FPA_TYPE_COLUMN_INTERLEAVEING       1
#define VDEC_EX_V2_FPA_TYPE_ROW_INTERLEAVEING          2
#define VDEC_EX_V2_FPA_TYPE_SIDE_BY_SIDE_PACKING       3
#define VDEC_EX_V2_FPA_TYPE_TOP_BOTTOM_PACKING         4
#define VDEC_EX_V2_FPA_TYPE_TEMPORAL_INTERLEAVING_FRM  5
#define VDEC_EX_V2_MAX_DEC_NUM 2

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Enum for Upper layer
//-------------------------------------------------------------------------------------------------
typedef enum
{
    E_VDEC_EX_V2_MAIN_STREAM = 0,
    E_VDEC_EX_V2_SUB_STREAM,
} VDEC_EX_V2_Stream;

/// decoder event enumerator.
typedef enum
{
    /// turn off all event
    E_VDEC_E_V2_EVENT_OFF                = 0x00,
    /// display one frame/field
    E_VDEC_EX_V2_EVENT_DISP_ONE           = VDEC_EX_V2_BIT(0),
    /// repeat one frame/field
    E_VDEC_EX_V2_EVENT_DISP_REPEAT        = VDEC_EX_V2_BIT(1),
    /// one CC data should be displayed
    E_VDEC_EX_V2_EVENT_DISP_WITH_CC       = VDEC_EX_V2_BIT(2),
    /// decode one frame
    E_VDEC_EX_V2_EVENT_DEC_ONE            = VDEC_EX_V2_BIT(3),
    /// decode one I frame
    E_VDEC_EX_V2_EVENT_DEC_I              = VDEC_EX_V2_BIT(4),
    /// decode error
    E_VDEC_EX_V2_EVENT_DEC_ERR            = VDEC_EX_V2_BIT(5),
    /// display information is changed
    E_VDEC_EX_V2_EVENT_DISP_INFO_CHG      = VDEC_EX_V2_BIT(6),
    /// find user data
    E_VDEC_EX_V2_EVENT_USER_DATA_FOUND    = VDEC_EX_V2_BIT(7),
    /// display information ready after be changed
    E_VDEC_EX_V2_EVENT_DISP_INFO_RDY      = VDEC_EX_V2_BIT(8),
    /// first frame decoded
    E_VDEC_EX_V2_EVENT_FIRST_FRAME        = VDEC_EX_V2_BIT(9),
    /// first picture found
    E_VDEC_EX_V2_EVENT_PIC_FOUND          = VDEC_EX_V2_BIT(10),
    /// video is ready to display (no garbage and avsync done)
    E_VDEC_EX_V2_EVENT_VIDEO_UNMUTE       = VDEC_EX_V2_BIT(11),
    /// new sequence header found
    E_VDEC_EX_V2_EVENT_SEQ_HDR_FOUND      = VDEC_EX_V2_BIT(12),
    /// active format description found
    E_VDEC_EX_V2_EVENT_AFD_FOUND          = VDEC_EX_V2_BIT(13),
    // ES data invalid
    E_VDEC_EX_V2_EVENT_ES_DATA_ERR        = VDEC_EX_V2_BIT(14),

} VDEC_EX_V2_EventFlag;

//define VDEC CB type
typedef enum
{
    E_VDEC_EX_V2_CB_MAIN  = 0,
    E_VDEC_EX_V2_CB_SUB,
} VDEC_EX_V2_CB_TYPE;

/// codec type enumerator
typedef enum
{
    ///unsupported codec type
    E_VDEC_EX_V2_CODEC_TYPE_NONE = 0,
    ///MPEG 1/2
    E_VDEC_EX_V2_CODEC_TYPE_MPEG2,
    ///H263 (short video header)
    E_VDEC_EX_V2_CODEC_TYPE_H263,
    ///MPEG4 (default)
    E_VDEC_EX_V2_CODEC_TYPE_MPEG4,
    ///MPEG4 (Divx311)
    E_VDEC_EX_V2_CODEC_TYPE_DIVX311,
    ///MPEG4 (Divx412)
    E_VDEC_EX_V2_CODEC_TYPE_DIVX412,
    ///FLV
    E_VDEC_EX_V2_CODEC_TYPE_FLV,
    ///VC1 advanced profile (VC1)
    E_VDEC_EX_V2_CODEC_TYPE_VC1_ADV,
    ///VC1 main profile (RCV)
    E_VDEC_EX_V2_CODEC_TYPE_VC1_MAIN,
    ///Real Video version 8
    E_VDEC_EX_V2_CODEC_TYPE_RV8,
    ///Real Video version 9 and 10
    E_VDEC_EX_V2_CODEC_TYPE_RV9,
    ///H264
    E_VDEC_EX_V2_CODEC_TYPE_H264,
    ///AVS
    E_VDEC_EX_V2_CODEC_TYPE_AVS,
    ///MJPEG
    E_VDEC_EX_V2_CODEC_TYPE_MJPEG,
    ///MVC
    E_VDEC_EX_V2_CODEC_TYPE_MVC,
    ///VP8
    E_VDEC_EX_V2_CODEC_TYPE_VP8,
    E_VDEC_EX_V2_CODEC_TYPE_NUM
} VDEC_EX_V2_CodecType;

/// input source select enumerator
typedef enum
{
    ///DTV mode
    E_VDEC_EX_V2_SRC_MODE_DTV = 0,
    ///TS file mode
    E_VDEC_EX_V2_SRC_MODE_TS_FILE,
    ///generic file mode
    E_VDEC_EX_V2_SRC_MODE_FILE,
    /// TS file and dual ES buffer mode
    E_VDEC_EX_V2_SRC_MODE_TS_FILE_DUAL_ES,
    ///generic file and dual ES buffer mode
    E_VDEC_EX_V2_SRC_MODE_FILE_DUAL_ES,
} VDEC_EX_V2_SrcMode;

/// function return enumerator
typedef enum
{
    ///failed
    E_VDEC_EX_V2_FAIL = 0,
    ///success
    E_VDEC_EX_V2_OK,
    ///invalid parameter
    E_VDEC_EX_V2_RET_INVALID_PARAM,
    ///access not allow
    E_VDEC_EX_V2_RET_ILLEGAL_ACCESS,
    ///hardware abnormal
    E_VDEC_EX_V2_RET_HARDWARE_BREAKDOWN,
     ///unsupported
    E_VDEC_EX_V2_RET_UNSUPPORTED,
     ///timeout
    E_VDEC_EX_V2_RET_TIMEOUT,
    ///not ready
    E_VDEC_EX_V2_RET_NOT_READY,
    ///not initial
    E_VDEC_EX_V2_RET_NOT_INIT,
    ///not exit after last initialization
    E_VDEC_EX_V2_RET_NOT_EXIT,
    ///not running, counter does not change
    E_VDEC_EX_V2_RET_NOT_RUNNING,
    ///max value
    E_VDEC_EX_V2_RET_NUM,
} VDEC_EX_V2_Result;

/// Action enumerator of display commands
typedef enum
{
    /// Action- display frame
    E_VDEC_EX_V2_DISP_ACTION_DISPLAY   = 1,
    /// Action - release frame
    E_VDEC_EX_V2_DISP_ACTION_RELEASE,
} VDEC_EX_V2_DispCmdAction;

/// Freeze picture select after flush decoder
typedef enum
{
    /// Freeze at current display picture
    E_VDEC_EX_V2_FREEZE_AT_CUR_PIC = 1,
    /// freeze at the latest decode picture
    E_VDEC_EX_V2_FREEZE_AT_LAST_PIC,
} VDEC_EX_V2_FreezePicSelect;

/// error code enumerator
typedef enum
{
    E_VDEC_EX_V2_ERR_CODE_BASE = 0x01000000,
    E_VDEC_EX_V2_ERR_CODE_NOT_SUPPORT,
    E_VDEC_EX_V2_ERR_CODE_ILLEGAL_ACCESS,
    E_VDEC_EX_V2_ERR_CODE_FRMRATE_NOT_SUPPORT,
    E_VDEC_EX_V2_ERR_CODE_DIVX_PLUS_UNSUPPORTED,

    E_VDEC_EX_V2_MVD_ERR_CODE_BASE = 0x02000000,
        E_VDEC_EX_V2_MVD_ERR_CODE_SHAPE,
        E_VDEC_EX_V2_MVD_ERR_CODE_USED_SPRITE,
        E_VDEC_EX_V2_MVD_ERR_CODE_NOT_8_BIT,         //error_status : bits per pixel
        E_VDEC_EX_V2_MVD_ERR_CODE_NERPRED_ENABLE,
        E_VDEC_EX_V2_MVD_ERR_CODE_REDUCED_RES_ENABLE,
        E_VDEC_EX_V2_MVD_ERR_CODE_SCALABILITY,
        E_VDEC_EX_V2_MVD_ERR_CODE_OTHER,
        E_VDEC_EX_V2_MVD_ERR_CODE_H263_ERROR,
        E_VDEC_EX_V2_MVD_ERR_CODE_RES_NOT_SUPPORT,   //error_status : none
        E_VDEC_EX_V2_MVD_ERR_CODE_MPEG4_NOT_SUPPORT, //error_status : none
        E_VDEC_EX_V2_MVD_ERR_CODE_VC1_NOT_SUPPORT,   //error_status : none
        E_VDEC_EX_V2_MVD_ERR_CODE_RCV_ERROR_OCCUR,

    E_VDEC_EX_V2_HVD_ERR_CODE_BASE = 0x03000000,
        E_VDEC_EX_V2_HVD_ERR_CODE_GENERAL_BASE = (0x0000|E_VDEC_EX_HVD_ERR_CODE_BASE),
        E_VDEC_EX_V2_HVD_ERR_CODE_OUT_OF_SPEC ,
        E_VDEC_EX_V2_HVD_ERR_CODE_UNKNOW_ERR,
        E_VDEC_EX_V2_HVD_ERR_CODE_HW_BREAK_DOWN,
        E_VDEC_EX_V2_HVD_ERR_CODE_HW_DEC_TIMEOUT,
        E_VDEC_EX_V2_HVD_ERR_CODE_OUT_OF_MEMORY,
        E_VDEC_EX_V2_HVD_ERR_CODE_UNKNOWN_CODEC,
        // AVC
        E_VDEC_EX_V2_HVD_ERR_CODE_AVC_BASE = (0x1000|E_VDEC_EX_HVD_ERR_CODE_BASE),
        E_VDEC_EX_V2_HVD_ERR_CODE_AVC_SPS_BROKEN,
        E_VDEC_EX_V2_HVD_ERR_CODE_AVC_SPS_NOT_IN_SPEC,
        E_VDEC_EX_V2_HVD_ERR_CODE_AVC_SPS_NOT_ENOUGH_FRM,   // DPB size at specified level is smaller than the specified number of reference frames. This is not allowed
        E_VDEC_EX_V2_HVD_ERR_CODE_AVC_PPS_BROKEN,           // PPS is not valid
        E_VDEC_EX_V2_HVD_ERR_CODE_AVC_REF_LIST,
        E_VDEC_EX_V2_HVD_ERR_CODE_AVC_NO_REF,
        E_VDEC_EX_V2_HVD_ERR_CODE_AVC_RES,             // out of supported resolution
        // AVS
        E_VDEC_EX_V2_HVD_ERR_CODE_AVS_BASE = (0x2000|E_VDEC_EX_HVD_ERR_CODE_BASE),
        E_VDEC_EX_V2_HVD_ERR_CODE_AVS_RES,             // out of supported resolution
        // RM
        E_VDEC_EX_V2_HVD_ERR_CODE_RM_BASE = (0x3000|E_VDEC_EX_HVD_ERR_CODE_BASE),
        E_VDEC_EX_V2_HVD_ERR_CODE_RM_PACKET_HEADER,
        E_VDEC_EX_V2_HVD_ERR_CODE_RM_FRAME_HEADER,
        E_VDEC_EX_V2_HVD_ERR_CODE_RM_SLICE_HEADER,
        E_VDEC_EX_V2_HVD_ERR_CODE_RM_BYTE_CNT,
        E_VDEC_EX_V2_HVD_ERR_CODE_RM_DISP_TIMEOUT,
        E_VDEC_EX_V2_HVD_ERR_CODE_RM_NO_REF,
        E_VDEC_EX_V2_HVD_ERR_CODE_RM_RES,              // out of supported resolution
        E_VDEC_EX_V2_HVD_ERR_CODE_RM_VLC,
        E_VDEC_EX_V2_HVD_ERR_CODE_RM_SIZE_OUT_FB_LAYOUT,

    E_VDEC_EX_V2_RVD_ERR_CODE_BASE = 0x04000000,
        E_VDEC_EX_V2_RVD_ERR_CODE_PACKET_HEADER, ///< packet header version error
        E_VDEC_EX_V2_RVD_ERR_CODE_FRAME_HEADER,  ///< frame type error
        E_VDEC_EX_V2_RVD_ERR_CODE_SLICE_HEADER,  ///<slice header error
        E_VDEC_EX_V2_RVD_ERR_CODE_DECODE_TIMEOUT,///< decode MB timeout
        E_VDEC_EX_V2_RVD_ERR_CODE_OUT_OF_MEMORY, ///< frame buffer is out of memory
        E_VDEC_EX_V2_RVD_ERR_CODE_BYTE_POS,      ///< can not find in ID table
        E_VDEC_EX_V2_RVD_ERR_CODE_DISPLAY_TIMEOUT,

    E_VDEC_EX_V2_MJPEG_ERR_CODE_BASE = 0x05000000,
        E_VDEC_EX_V2_HVD_ERR_CODE_MJPEG_RES,
} VDEC_EX_V2_ErrCode;

/// frame rate conversion mode enumerator
typedef enum
{
    /// disable FRC mode.
    E_VDEC_EX_V2_FRC_NORMAL = 0,
    /// output rate is twice of input rate (ex. 30p to 60p)
    E_VDEC_EX_V2_FRC_DISP_TWICE,
    /// 3:2 pulldown mode (ex. 24p to 60i or 60p)
    E_VDEC_EX_V2_FRC_3_2_PULLDOWN,
    /// PAL to NTSC conversion (50i to 60i)
    E_VDEC_EX_V2_FRC_PAL_TO_NTSC,
    /// NTSC to PAL conversion (60i to 50i)
    E_VDEC_EX_V2_FRC_NTSC_TO_PAL,
    /// output rate 50P ->60P
    E_VDEC_EX_V2_FRC_MODE_50P_60P,
    /// output rate 60P ->50P
    E_VDEC_EX_V2_FRC_MODE_60P_50P,
} VDEC_EX_V2_FrcMode;

/// trick decode mode enumerator
typedef enum
{
    /// decode all frame
    E_VDEC_EX_V2_TRICK_DEC_ALL = 0,
    /// decode all except of non-reference frame
    E_VDEC_EX_V2_TRICK_DEC_IP,
    /// only decode I frame
    E_VDEC_EX_V2_TRICK_DEC_I,
    E_VDEC_EX_V2_TRICK_DEC_NUM
} VDEC_EX_V2_TrickDec;

/// display speed setting enumerator
typedef enum
{
    /// default speed type
    E_VDEC_EX_V2_SPEED_DEFAULT = 0,
    /// fast display
    E_VDEC_EX_V2_SPEED_FAST,
    /// slow display
    E_VDEC_EX_V2_SPEED_SLOW,
} VDEC_EX_V2_SpeedType;

/// The display speed enumerator
typedef enum
{
    /// Normal display speed.
    E_VDEC_EX_V2_DISP_SPEED_1X = 1,
    /// 2X
    E_VDEC_EX_V2_DISP_SPEED_2X = 2,
    /// 4X
    E_VDEC_EX_V2_DISP_SPEED_4X = 4,
    /// 8X
    E_VDEC_EX_V2_DISP_SPEED_8X = 8,
    /// 16X
    E_VDEC_EX_V2_DISP_SPEED_16X = 16,
    /// 32X
    E_VDEC_EX_V2_DISP_SPEED_32X = 32,
} VDEC_EX_V2_DispSpeed;

/// motion JPEG down scale factor enumerator
typedef enum
{
    ///original size
    E_VDEC_EX_V2_MJPEG_SCALE_1to1 = 0,
    ///down scale to 1/2
    E_VDEC_EX_V2_MJPEG_SCALE_2to1,
    ///down scale to 1/4
    E_VDEC_EX_V2_MJPEG_SCALE_4to1,
    ///down scale to 1/8
    E_VDEC_EX_V2_MJPEG_SCALE_8to1,
} VDEC_EX_V2_MJpegScaleFactor;

/// timestamp type of command queue
typedef enum
{
    ///without timestamp information
    E_VDEC_EX_V2_TIME_STAMP_NONE = 0,
    ///PTS (Presentation Time Stamp)
    E_VDEC_EX_V2_TIME_STAMP_PTS,
    ///DTS (Decode Time Stamp)
    E_VDEC_EX_V2_TIME_STAMP_DTS,
    ///STS (Sorted Time Stamp)
    E_VDEC_EX_V2_TIME_STAMP_STS,
} VDEC_EX_V2_TimeStampType;

/// The debug level of VDEC
typedef enum
{
    /// disable all uart message.
    E_VDEC_EX_V2_DBG_LEVEL_NONE = 0,
    /// Only output error message
    E_VDEC_EX_V2_DBG_LEVEL_ERR,
    /// output general message, and above.
    E_VDEC_EX_V2_DBG_LEVEL_INFO,
    /// output debug message, and above.
    E_VDEC_EX_V2_DBG_LEVEL_DBG,
    /// output function tracing message, and above.
    E_VDEC_EX_V2_DBG_LEVEL_TRACE,
    /// output FW message.
    E_VDEC_EX_V2_DBG_LEVEL_FW,
} VDEC_EX_V2_DbgLevel;

/// Type of FW source
typedef enum
{
    E_VDEC_EX_V2_FW_SOURCE_NONE,
    E_VDEC_EX_V2_FW_SOURCE_DRAM,
    E_VDEC_EX_V2_FW_SOURCE_FLASH,
}VDEC_EX_V2_FWSourceType;

/// Format of CC (Closed Caption)
typedef enum
{
    E_VDEC_EX_V2_CC_NONE       = 0x00,
    E_VDEC_EX_V2_CC_608        = 0x01, //For CC608 or 157
    E_VDEC_EX_V2_CC_708        = 0x02, //For CC708
    E_VDEC_EX_V2_CC_UNPACKED   = 0x03,
} VDEC_EX_V2_CCFormat;

/// Type of CC
typedef enum
{
    E_VDEC_EX_V2_CC_TYPE_NONE = 0,
    E_VDEC_EX_V2_CC_TYPE_NTSC_FIELD1 = 1,
    E_VDEC_EX_V2_CC_TYPE_NTSC_FIELD2 = 2,
    E_VDEC_EX_V2_CC_TYPE_DTVCC = 3,
    E_VDEC_EX_V2_CC_TYPE_NTSC_TWOFIELD = 4,
} VDEC_EX_V2_CCType;

typedef enum
{
    E_VDEC_EX_V2_CC_GET_BUFF_START = 0x1,
    E_VDEC_EX_V2_CC_GET_BUFF_SIZE,
    E_VDEC_EX_V2_CC_GET_708_ENABLE
} VDEC_EX_V2_CCInfoCmd;

typedef enum
{
    E_VDEC_EX_V2_STAGE_STOP = 0,
    E_VDEC_EX_V2_STAGE_INIT,
    E_VDEC_EX_V2_STAGE_PLAY,
    E_VDEC_EX_V2_STAGE_PAUSE,
} VDEC_EX_V2_Stage;

typedef enum
{
    /// Used before MApi_VDEC_EX_Flush().
    E_VDEC_EX_V2_PATTERN_FLUSH = 0,
    /// Used after MApi_VDEC_EX_EnableLastFrameShow().
    E_VDEC_EX_V2_PATTERN_FILEEND,
}VDEC_EX_V2_PatternType;

typedef struct
{
    MS_BOOL bInit;
    MS_BOOL bIdle;
    VDEC_EX_V2_Stage  eStage;
} VDEC_EX_V2_Status;

typedef struct
{
    MS_U32 u32Tmp;
} VDEC_EX_V2_Info;

typedef enum
{
    E_VDEC_EX_V2_FRM_TYPE_I = 0,
    E_VDEC_EX_V2_FRM_TYPE_P,
    E_VDEC_EX_V2_FRM_TYPE_B,
    E_VDEC_EX_V2_FRM_TYPE_OTHER,
    E_VDEC_EX_V2_FRM_TYPE_NUM
} VDEC_EX_V2_FrameType;

typedef enum
{
    ///< no field.
    E_VDEC_EX_V2_FIELDTYPE_NONE,
    ///< Top field only.
    E_VDEC_EX_V2_FIELDTYPE_TOP,
    ///< Bottom field only.
    E_VDEC_EX_V2_FIELDTYPE_BOTTOM,
    ///< Both fields.
    E_VDEC_EX_V2_FIELDTYPE_BOTH,
    E_VDEC_EX_V2_FIELDTYPE_NUM
} VDEC_EX_V2_FieldType;

typedef enum
{
    E_VDEC_EX_V2_PATTERN_BEFORE_FRM = 0,
    E_VDEC_EX_V2_PATTERN_AFTER_FRM,
    E_VDEC_EX_V2_PATTERN_SKIP_DATA,
} VDEC_EX_V2_PatchPattern;

typedef enum
{
    E_VDEC_EX_V2_PIC_STRUCTURE_RSV = 0, //reserved
    E_VDEC_EX_V2_PIC_STRUCTURE_TOP,
    E_VDEC_EX_V2_PIC_STRUCTURE_BOT,
    E_VDEC_EX_V2_PIC_STRCUTURE_FRM,
} VDEC_EX_V2_PicStructure;

//VDEC FB reduction type
typedef enum
{
    VDEC_EX_V2_FB_REDUCTION_NONE  = 0,
    VDEC_EX_V2_FB_REDUCTION_1_2,
    VDEC_EX_V2_FB_REDUCTION_1_4
} VDEC_EX_V2_FBReductionType;

//VDEC set debug mode
typedef enum
{
    E_VDEC_EX_V2_DBG_MODE_BYPASS_INSERT_START_CODE = 0, /// for  UT
    E_VDEC_EX_V2_DBG_MODE_BYPASS_DIVX_MC_PATCH,         /// for  UT
    E_VDEC_EX_V2_DBG_MODE_NUM
} VDEC_EX_V2_DbgMode;

//VDEC set clock speed
typedef enum
{
    E_VDEC_EX_V2_CLOCK_SPEED_NONE = 0,
    E_VDEC_EX_V2_CLOCK_SPEED_HIGHEST,
    E_VDEC_EX_V2_CLOCK_SPEED_HIGH,
    E_VDEC_EX_V2_CLOCK_SPEED_MEDIUM,
    E_VDEC_EX_V2_CLOCK_SPEED_LOW,
    E_VDEC_EX_V2_CLOCK_SPEED_LOWEST,
    E_VDEC_EX_V2_CLOCK_SPEED_DEFAULT,
} VDEC_EX_V2_ClockSpeed;

//VDEC FW TYPE
typedef enum
{
    E_VDEC_EX_V2_FW_TYPE_MVD = 0,
    E_VDEC_EX_V2_FW_TYPE_HVD,
} VDEC_EX_V2_FwType;

/// DecodeMode for f/w tasks
typedef enum
{
    E_VDEC_EX_V2_DEC_MODE_DUAL_INDIE = 0,                     ///< Two independent tasks
    E_VDEC_EX_V2_DEC_MODE_DUAL_3D,                        ///< Two dependent tasks for 3D
    E_VDEC_EX_V2_DEC_MODE_SINGLE,                         ///< One task use the whole SRAM
    E_VDEC_EX_V2_DEC_MODE_MVC = E_VDEC_EX_DEC_MODE_SINGLE,
} VDEC_EX_V2_DEC_MODE;


/// argument of DecodeMode structure for f/w tasks
typedef enum
{
    //Group1:Set Korea3DTV mode
    E_VDEC_EX_V2_DEC_KR3D_MODE_BASE  = 0x0000,
    E_VDEC_EX_V2_DEC_KR3D_INTERLACE_MODE = E_VDEC_EX_DEC_KR3D_MODE_BASE,
    E_VDEC_EX_V2_DEC_KR3D_FORCE_P_MODE,
    E_VDEC_EX_V2_DEC_KR3D_INTERLACE_TWO_PITCH,
    E_VDEC_EX_V2_DEC_KR3D_FORCE_P_TWO_PITCH,

    //Group2:Set PIP mode
    E_VDEC_EX_V2_DEC_PIP_MODE_BASE = 0x1000,
    E_VDEC_EX_V2_DEC_PIP_SYNC_INDIE = E_VDEC_EX_DEC_PIP_MODE_BASE,
    E_VDEC_EX_V2_DEC_PIP_SYNC_MAIN_STC,
    E_VDEC_EX_V2_DEC_PIP_SYNC_SWITCH
} VDEC_EX_V2_DEC_MODE_ARG;

typedef enum
{
    E_VDEC_EX_V2_DIU_DRAM = 0,  //MCU mode
    E_VDEC_EX_V2_DIU_HVD = 1,
    E_VDEC_EX_V2_DIU_MVD  = 2,
    E_VDEC_EX_V2_DIU_HVD_3DLR = 3,  //MVC
    E_VDEC_EX_V2_DIU_MVD_3DLR = 4,  //Korea3D, WMV3D
    E_VDEC_EX_V2_DIU_UNKNOWN = -1
} VDEC_EX_V2_DIU;

typedef enum
{
    E_VDEC_EX_V2_CMD_GET_FREE_STREAM_ID,
    E_VDEC_EX_V2_CMD_INIT,
    E_VDEC_EX_V2_CMD_SET_CONTROL,
    E_VDEC_EX_V2_CMD_GET_CONTROL,
    E_VDEC_EX_V2_CMD_PRE_SET_CONTROL,
    E_VDEC_EX_V2_CMD_POST_SET_CONTROL,
    E_VDEC_EX_V2_CMD_NUM,
    E_VDEC_EX_V2_CMD_MAX = E_VDEC_EX_V2_CMD_NUM,
} E_VDEC_EX_V2_IOCTL_CMD;

//VDEC user command id
typedef enum
{
    //Group1:Set Control command================================
    E_VDEC_EX_V2_USER_CMD_SET_CONTROL_BASE  = 0x0000,
    E_VDEC_EX_V2_USER_CMD_REPEAT_LAST_FIELD,               // Param: 1(ON), 0(OFF)
    E_VDEC_EX_V2_USER_CMD_AVSYNC_REPEAT_TH,                // Param:0x01 ~ 0xFF(repeat times), 0xFF:always repeat when av is not sync
    E_VDEC_EX_V2_USER_CMD_DISP_ONE_FIELD,                  // Param: 1(ON), 0(OFF)
    E_VDEC_EX_V2_USER_CMD_FD_MASK_DELAY_COUNT,             // Param: unit is in vsync base for mute the fd_mask
    E_VDEC_EX_V2_USER_CMD_FRC_OUTPUT,                      // Param: the address of VDEC_FRC_OutputParam
    E_VDEC_EX_V2_USER_CMD_FRC_DROP_TYPE,                   // Param: 1(FRC_DROP_FIELD), 0(FRC_DROP_FRAME), default:0
    E_VDEC_EX_V2_USER_CMD_FAST_DISPLAY,                    // Param: TRUE(Fast display), FALSE(Display until synced)
    E_VDEC_EX_V2_USER_CMD_IGNORE_ERR_REF,                  // Param: TRUE(Ignore error reference), FALSE(Enable error reference handle)
    E_VDEC_EX_V2_USER_CMD_FORCE_FOLLOW_DTV_SPEC,           // Param: 1(ON), 0(OFF)
    E_VDEC_EX_V2_USER_CMD_AVC_MIN_FRM_GAP,                 // Param: Set the theshold of H264 frame gap, 0xFFFFFFFF don't care frame gap
    E_VDEC_EX_V2_USER_CMD_DISABLE_SEQ_CHG,                 // Param: 1(Disable), 0(Enable)
    E_VDEC_EX_V2_USER_CMD_SET_DISP_OUTSIDE_CTRL_MODE,      // Param: 1(ON) used for Openmax, 0(OFF) used for mstreamer and mm mode ,default : off
    E_VDEC_EX_V2_USER_CMD_SET_DTV_USER_DATA_MODE,          // Param: 0(Support normal DVB CC, default case), 1(Support ATSC DirectTV CC), 2,3,4(Reserved)
    E_VDEC_EX_V2_USER_CMD_SET_SINGLE_TASK_MODE,
    E_VDEC_EX_V2_USER_CMD_AVC_DISABLE_ANTI_VDEAD,
    E_VDEC_EX_V2_USER_CMD_DTV_RESET_MVD_PARSER,            // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_V2_USER_CMD_PVR_FLUSH_FRAME_BUFFER,
    E_VDEC_EX_V2_USER_CMD_FORCE_INTERLACE_MODE,
    E_VDEC_EX_V2_USER_CMD_RELEASE_FD_MASK,                 // Param: 1 to release fd mask when zooming or slow motion
    E_VDEC_EX_V2_USER_CMD_NULL,                            //  E_VDEC_EX_USER_CMD_SET_DECODE_MODE
    E_VDEC_EX_V2_USER_CMD_SUPPORT_AVC_TO_MVC,              // Param: 0(Do not support), 1(Support AVC to MVC)
    E_VDEC_EX_V2_USER_CMD_3DLR_VIEW_EXCHANGE,              // Param: 0(Disable), 1(View L/R exhange)
    E_VDEC_EX_V2_USER_CMD_SET_VSIZE_ALIGN,                 // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_V2_USER_CMD_SHOW_DECODE_ORDER,               // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_V2_USER_CMD_AVC_DISP_IGNORE_CROP,            // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_V2_USER_CMD_SET_DISP_FINISH_MODE,
    E_VDEC_EX_V2_USER_CMD_SET_AVSYNC_MODE,
    E_VDEC_EX_V2_USER_CMD_SUSPEND_DYNAMIC_SCALE,           // Param: 0(Disable, non-suspend DS), 1(Enable, suspend DS)
    E_VDEC_EX_V2_USER_CMD_FORCE_AUTO_MUTE,
    E_VDEC_EX_V2_USER_CMD_AVC_NEW_SLOW_MOTION,             // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_V2_USER_CMD_PUSH_DISPQ_WITH_REF_NUM,         // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_V2_USER_CMD_DS_RESV_N_BUFFER,                // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_V2_USER_CMD_RM_ENABLE_PTS_TBL,               // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_V2_USER_CMD_FLUSH_PTS_BUF,
    E_VDEC_EX_V2_USER_CMD_SET_IDCT_MODE,                   // Param: 0(Original), 1(new IDCT)
    E_VDEC_EX_V2_USER_CMD_DROP_ERR_FRAME,                  // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_V2_USER_CMD_SET_CC608_INFO_ENHANCE_MODE,
    E_VDEC_EX_V2_USER_CMD_IGNORE_PIC_OVERRUN,              // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_V2_USER_CMD_SET_SELF_SEQCHANGE,
    E_VDEC_EX_V2_USER_CMD_AUTO_EXHAUST_ES_MODE,            // Param: set the upper bound (arg[31:16]), and lower bound (arg[15:0])of ES level, Unit = 1KBytes, Auto drop display to consume ES data as soon as possible when ES level is higher than upper bound
    E_VDEC_EX_V2_USER_CMD_CTL_SPEED_IN_DISP_ONLY,          // Param: 0(Original: Dec and disp time), 1(In Disp only)
    E_VDEC_EX_V2_USER_CMD_AVC_SUPPORT_REF_NUM_OVER_MAX_DPB_SIZE, // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_V2_USER_CMD_RETURN_INVALID_AFD,              // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_V2_USER_CMD_FIELD_POLARITY_DISPLAY_ONE_FIELD,// Param : VDEC_EX_V2_Field_Polarity
    E_VDEC_EX_V2_USER_CMD_AVC_FORCE_BROKEN_BY_US,              // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_V2_USER_CMD_SHOW_FIRST_FRAME_DIRECT,         // Param: 0(Disable), 1(Enable), Push first frame to display queue directly..
    E_VDEC_EX_V2_USER_CMD_AVC_RESIZE_DOS_DISP_PEND_BUF,    // Param:  size of AVC display pending buffer for display outside mode
    E_VDEC_EX_V2_USER_CMD_SET_XC_LOW_DELAY_PARA,            // Param: arg0 for diff_field_number...
    E_VDEC_EX_V2_USER_CMD_SET_SECURE_MODE,                 // Param: use enum VDEC_EX_SecureMode
    E_VDEC_EX_V2_USER_CMD_RVU_SETTING_MODE,                // Param: 0(Disable), 1(drop B-frame and force IDR)
    E_VDEC_EX_V2_USER_CMD_FRAMERATE_HANDLING,              // Arg 0~60000, 0: Disable, 1000 ~ 60000: Used the arg to set frame rate when the sequence did not have frame rate info. and arg is not zero. (The frame unit is (arg/1000)fps, Exp: 30000 = 30.000 fps), others: Do not thing.
    E_VDEC_EX_V2_USER_CMD_DUAL_NON_BLOCK_MODE,             // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_V2_USER_CMD_IGNORE_PIC_STRUCT_DISPLAY,       // Param: 0(Disable), 1(Enable) Ignore Pic_struct when display progressive frame.
    E_VDEC_EX_V2_USER_CMD_INPUT_PTS_FREERUN_MODE,          // Param: 0(Disable), 1(Enable) Video free run when the difference between input PTS and current STC is large than E_HVD_CMD_FREERUN_THRESHOLD + 1s;
    E_VDEC_EX_V2_USER_CMD_ERR_CONCEAL_SLICE_1ST_MB,        // Param: 0(disable), Error concealment from current/last MB position; 1(enale) Error concealment from current slice first MB.(Need enable E_HVD_CMD_ERR_CONCEAL)
    E_VDEC_EX_V2_USER_CMD_SET_EXTERNAL_DS_BUFFER,          // Param: External DS Buffer info.
    E_VDEC_EX_V2_USER_CMD_SET_MIN_TSP_DATA_SIZE,            // Param: Resize HVD_FW_AVC_ES_MIN_TSP_DATA_SIZE
    E_VDEC_EX_V2_USER_CMD_SET_DMX_FRAMERATE,
    E_VDEC_EX_V2_USER_CMD_SET_DMX_FRAMERATEBASE,
    E_VDEC_EX_V2_USER_CMD_ENABLE_CC_608_EXTERNAL_BUFFER,      // Param: u32_ccinfo 32bits-->([31:8]+[7:0] = addr+size), addr is kb unit, if u32_ccinfo ==0, it will turn off this feature
    E_VDEC_EX_V2_USER_CMD_ENABLE_CC_708_EXTERNAL_BUFFER,      // Param: u32_ccinfo 32bits-->([31:8]+[7:0] = addr+size), addr is kb unit, if u32_ccinfo ==0, it will turn off this feature
    E_VDEC_EX_V2_USER_CMD_SET_TIME_INC_PREDICT_PARA,
    E_VDEC_EX_V2_USER_CMD_ENABLE_DECODE_ENGINE_TIMEOUT,    // Param: Enable/Disable decode timeout solution, timeout value unit:ms (VDEC_EX_Decode_Timeout_Param)
    E_VDEC_EX_V2_USER_CMD_FRAMEBUFFER_AUTO_MODE,                //Param: 0(Disable),1(Enable), this cmd is used for MVD.
    E_VDEC_EX_V2_USER_CMD_SET_SMOOTH_REWIND,                //enable/disable or support smooth rewind
    E_VDEC_EX_V2_USER_CMD_SET_ERROR_TOLERANCE,
    E_VDEC_EX_V2_USER_CMD_AUTO_DROP_DISPLAY_QUEUE,         // Param: 0(Disable), N = 1~16: Drop display queue when display queue above than N frames.
    E_VDEC_EX_V2_USER_CMD_SKIP_N_FRAME,                    // Param: 0:disable, N = 1~63. Skip N frame.
    E_VDEC_EX_V2_USER_CMD_SET_PTS_US_MODE,              //Param: 1(enable), 0(disable ) PTS output by micro second level,
    E_VDEC_EX_V2_USER_CMD_AUTO_INSERT_DUMMY_DATA,         //Param: 1(enable),0(disable), Enable/Disable utopia auto insert dummy pattern in SLQ/BBU mode.
    E_VDEC_EX_V2_USER_CMD_DROP_ONE_PTS,
    E_VDEC_EX_V2_USER_CMD_PVR_TIMESHIFT_SEAMLESS_MODE,
    E_VDEC_EX_V2_USER_CMD_EXIT,
    E_VDEC_EX_V2_USER_CMD_RST,
    E_VDEC_EX_V2_USER_CMD_CHECK_DISPINFO_READY,
    E_VDEC_EX_V2_USER_CMD_SET_FRC_MODE,
    E_VDEC_EX_V2_USER_CMD_SET_DYNSCALING_PARAMS,
    E_VDEC_EX_V2_USER_CMD_SET_DBG_LEVEL,
    E_VDEC_EX_V2_USER_CMD_PLAY,
    E_VDEC_EX_V2_USER_CMD_PAUSE,
    E_VDEC_EX_V2_USER_CMD_RESUME,
    E_VDEC_EX_V2_USER_CMD_STEP_DISP,
    E_VDEC_EX_V2_USER_CMD_STEP_DECODE,
    E_VDEC_EX_V2_USER_CMD_SET_TRICK_MODE,
    E_VDEC_EX_V2_USER_CMD_PUSH_DECQ,
    E_VDEC_EX_V2_USER_CMD_FLUSH,
    E_VDEC_EX_V2_USER_CMD_ENABLE_LAST_FRAME_SHOW,
    E_VDEC_EX_V2_USER_CMD_SET_SPEED,
    E_VDEC_EX_V2_USER_CMD_SET_FREEZE_DISP,
    E_VDEC_EX_V2_USER_CMD_SET_BLUE_SCREEN,
    E_VDEC_EX_V2_USER_CMD_RESET_PTS,
    E_VDEC_EX_V2_USER_CMD_AVSYNC_ON,
    E_VDEC_EX_V2_USER_CMD_AVSYNC_FREERUN_THRESHOLD,
    E_VDEC_EX_V2_USER_CMD_SET_EVENT_MULTICALLBACK,
    E_VDEC_EX_V2_USER_CMD_UNSET_EVENT_MULTICALLBACK,
    E_VDEC_EX_V2_USER_CMD_FIRE_DEC,
    E_VDEC_EX_V2_USER_CMD_SEEK_TO_PTS,
    E_VDEC_EX_V2_USER_CMD_SKIP_TO_PTS,
    E_VDEC_EX_V2_USER_CMD_DISABLE_DEBLOCKING,
    E_VDEC_EX_V2_USER_CMD_DISABLE_QUARTER_PIXEL,
    E_VDEC_EX_V2_USER_CMD_SET_AUTO_RM_LST_ZERO_BYTE,
    E_VDEC_EX_V2_USER_CMD_SET_BALANCE_BW,
    E_VDEC_EX_V2_USER_CMD_GEN_PATTERN,
    E_VDEC_EX_V2_USER_CMD_MHEG_DECODE_IFRAME,
    E_VDEC_EX_V2_USER_CMD_MHEG_RST_IFRAME_DEC,
    E_VDEC_EX_V2_USER_CMD_CC_START_PARSING,
    E_VDEC_EX_V2_USER_CMD_CC_STOP_PARSING,
    E_VDEC_EX_V2_USER_CMD_CC_UPDATE_READ_PTR,
    E_VDEC_EX_V2_USER_CMD_SET_BLOCK_DISPLAY,
    E_VDEC_EX_V2_USER_CMD_ENABLE_ES_BUFF_MALLOC,
    E_VDEC_EX_V2_USER_CMD_DISPLAY_FRAME,
    E_VDEC_EX_V2_USER_CMD_RELEASE_FRAME,
    E_VDEC_EX_V2_USER_CMD_CAPTURE_FRAME,
    E_VDEC_EX_V2_USER_CMD_CC_INIT,
    E_VDEC_EX_V2_USER_CMD_CC_SET_CFG,
    E_VDEC_EX_V2_USER_CMD_CC_SET_BUFF_START_ADDR,
    E_VDEC_EX_V2_USER_CMD_CC_UPDATE_WRITE_ADDR,
    E_VDEC_EX_V2_USER_CMD_CC_UPDATE_READ_ADDR,
    E_VDEC_EX_V2_USER_CMD_CC_DISABLE_PARSING,


    E_VDEC_EX_V2_USER_CMD_MVC_SET_CMD_BASE  = 0x0800,
    E_VDEC_EX_V2_USER_CMD_MVC_BBU2_PUSH_PACKET,            // Param: Packet Info.
    E_VDEC_EX_V2_USER_CMD_MVC_BBU2_FIRE_DECCMD,            // Param: Non

    E_VDEC_EX_V2_USER_CMD_UT_SET_CMD_BASE = 0x0900,
    E_VDEC_EX_V2_USER_CMD_UT_SET_DBG_MODE,                    // Param: for enable the specify dbg mode for UT
    E_VDEC_EX_V2_USER_CMD_UT_CLR_DBG_MODE,                    // Param: for disable the specify dbg mode for UT

    //Group2:Get Control command================================
    E_VDEC_EX_V2_USER_CMD_GET_CONTROL_BASE  = 0x1000,
    E_VDEC_EX_V2_USER_CMD_GET_CHROMA_TYPE,
    E_VDEC_EX_V2_USER_CMD_GET_REAL_FRAMERATE,              // Get Real FrameRate reported by decoder
    E_VDEC_EX_V2_USER_CMD_GET_COLOR_MATRIX,                // Get color matrix coefficients reported by decoder
    E_VDEC_EX_V2_USER_CMD_GET_MAIN_STREAM_ID,              // Get activated main stream ID
    E_VDEC_EX_V2_USER_CMD_GET_SUB_STREAM_ID,               // Get activated sub stream ID
    E_VDEC_EX_V2_USER_CMD_GET_DYNSCALE_ENABLED,
    E_VDEC_EX_V2_USER_CMD_GET_FPA_SEI,                     //Get SEI info
    E_VDEC_EX_V2_USER_CMD_GET_U64PTS,
    E_VDEC_EX_V2_USER_CMD_GET_ORI_INTERLACE_MODE,
    E_VDEC_EX_V2_USER_CMD_GET_MBS_ONLY_FLAG,
    E_VDEC_EX_V2_USER_CMD_GET_CRC_VALUE,                   //Get frame Y/UV crc value
    E_VDEC_EX_V2_USER_CMD_GET_BBU_Q_NUM,
    E_VDEC_EX_V2_USER_CMD_GET_DISP_FRAME_NUM,
    E_VDEC_EX_V2_USER_CMD_GET_FPA_SEI_EX,                  //Get SEI info(enhancement)
    E_VDEC_EX_V2_USER_CMD_GET_ES_BUFFER_STATUS,            //Get ES buffer over/under flow status
    E_VDEC_EX_V2_USER_CMD_GET_CODEC_TYPE,                  // Get Codec type
    E_VDEC_EX_V2_USER_CMD_GET_SHAREMEMORY_BASE,
    E_VDEC_EX_V2_USER_CMD_GET_IS_LEAST_DISPQ_SIZE_FLAG,
    E_VDEC_EX_V2_USER_CMD_GET_FIELD_PIC_FLAG,              // Param: Get Field Pic Flag
    E_VDEC_EX_V2_USER_CMD_GET_SUPPORT_2ND_MVOP_INTERFACE,  // Param: TRUE : support, FALSE : not support
    E_VDEC_EX_V2_USER_CMD_GET_FB_USAGE_MEM,                // Get FrameBuufer Size needed by decoder
    E_VDEC_EX_V2_USER_CMD_GET_XC_LOW_DELAY_INT_STATE,        // Get xc_low_delay int state...
    E_VDEC_EX_V2_USER_CMD_GET_VSYNC_BRIDGE_ADDR,
    E_VDEC_EX_V2_USER_CMD_GET_FRAME_INFO_EX,
    E_VDEC_EX_V2_USER_CMD_GET_FLUSH_PATTEN_ENTRY_NUM,
    E_VDEC_EX_V2_USER_CMD_GET_DS_BUF_MIU_SEL,               //For those chips which has 3 MIU, use this get control to get correct miu select of DS buffer
    E_VDEC_EX_V2_USER_CMD_GET_FW_STATUS_FLAG,
    E_VDEC_EX_V2_USER_CMD_GET_HW_MAX_PIXEL,

    E_VDEC_EX_V2_USER_CMD_GET_STATUS,
    E_VDEC_EX_V2_USER_CMD_CHECK_DISPINFORDY,
    E_VDEC_EX_V2_USER_CMD_IS_STEP_DISP_DONE,
    E_VDEC_EX_V2_USER_CMD_IS_STEP_DECODE_DONE,
    E_VDEC_EX_V2_USER_CMD_GET_DISP_INFO,
    E_VDEC_EX_V2_USER_CMD_IS_AVSYNC_ON,
    E_VDEC_EX_V2_USER_CMD_IS_WITH_VALID_STREAM,
    E_VDEC_EX_V2_USER_CMD_IS_DISP_FINISH,
    E_VDEC_EX_V2_USER_CMD_IS_IFRAME_FOUND,
    E_VDEC_EX_V2_USER_CMD_IS_SEQ_CHG,
    E_VDEC_EX_V2_USER_CMD_IS_REACH_SYNC,
    E_VDEC_EX_V2_USER_CMD_IS_START_SYNC,
    E_VDEC_EX_V2_USER_CMD_IS_FREERUN,
    E_VDEC_EX_V2_USER_CMD_IS_WITH_LOW_DELAY,
    E_VDEC_EX_V2_USER_CMD_IS_ALL_BUFFER_EMPTY,
    E_VDEC_EX_V2_USER_CMD_GET_EXT_DISP_INFO,
    E_VDEC_EX_V2_USER_CMD_GET_DEC_FRAME_INFO,
    E_VDEC_EX_V2_USER_CMD_GET_DISP_FRAME_INFO,
    E_VDEC_EX_V2_USER_CMD_GET_DEC_TIMECODE,
    E_VDEC_EX_V2_USER_CMD_GET_DISP_TIMECODE,
    E_VDEC_EX_V2_USER_CMD_GET_EVENT_INFO,
    E_VDEC_EX_V2_USER_CMD_GET_ACTIVE_FORMAT,
    E_VDEC_EX_V2_USER_CMD_GET_COLOUR_PRIMARIES,
    E_VDEC_EX_V2_USER_CMD_GET_FW_VERSION,
    E_VDEC_EX_V2_USER_CMD_GET_GOP_CNT,
    E_VDEC_EX_V2_USER_CMD_GET_ES_WRITE_PTR,
    E_VDEC_EX_V2_USER_CMD_GET_ES_READ_PTR,
    E_VDEC_EX_V2_USER_CMD_GET_PTS,
    E_VDEC_EX_V2_USER_CMD_GET_NEXT_PTS,
    E_VDEC_EX_V2_USER_CMD_GET_VIDEO_PTS_STC_DELTA,
    E_VDEC_EX_V2_USER_CMD_GET_ERR_CODE,
    E_VDEC_EX_V2_USER_CMD_GET_ERR_CNT,
    E_VDEC_EX_V2_USER_CMD_GET_BITRATE,
    E_VDEC_EX_V2_USER_CMD_GET_FRAME_CNT,
    E_VDEC_EX_V2_USER_CMD_GET_SKIP_CNT,
    E_VDEC_EX_V2_USER_CMD_GET_DROP_CNT,
    E_VDEC_EX_V2_USER_CMD_GET_DISP_CNT,
    E_VDEC_EX_V2_USER_CMD_GET_DECQ_VACANCY,
    E_VDEC_EX_V2_USER_CMD_IS_32_PULLDOWN,
    E_VDEC_EX_V2_USER_CMD_IS_ALIVE,
    E_VDEC_EX_V2_USER_CMD_IS_CC_AVAILABLE,
    E_VDEC_EX_V2_USER_CMD_GET_CC_INFO,
    E_VDEC_EX_V2_USER_CMD_GET_TRICK_MODE,
    E_VDEC_EX_V2_USER_CMD_GET_ACTIVE_CODEC_TYPE,
    E_VDEC_EX_V2_USER_CMD_GET_PATTERN_LEAST_LENGTH,
    E_VDEC_EX_V2_USER_CMD_MHEG_IS_IFRAME_DECODING,
    E_VDEC_EX_V2_USER_CMD_CC_GET_WRITE_PTR,
    E_VDEC_EX_V2_USER_CMD_CC_GET_READ_PTR,
    E_VDEC_EX_V2_USER_CMD_CC_GET_IS_OVERFLOW,
    E_VDEC_EX_V2_USER_CMD_GET_HW_KEY,
    E_VDEC_EX_V2_USER_CMD_GET_ES_BUFF_VACANCY,
    E_VDEC_EX_V2_USER_CMD_GET_ES_BUFF,
    E_VDEC_EX_V2_USER_CMD_GET_NEXT_DISP_FRAME,
    E_VDEC_EX_V2_USER_CMD_CC_GET_INFO,
    E_VDEC_EX_V2_USER_CMD_CC_GET_IS_RST_DONE,
    E_VDEC_EX_V2_USER_CMD_CC_GET_IS_BUFF_OVERFLOW,
    E_VDEC_EX_V2_USER_CMD_CC_GET_WRITE_ADDR,
    E_VDEC_EX_V2_USER_CMD_CC_GET_READ_ADDR,
    E_VDEC_EX_V2_USER_CMD_GETLIBVER,
    E_VDEC_EX_V2_USER_CMD_GETINFO,
    E_VDEC_EX_V2_USER_CMD_CHECKCAPS,
    E_VDEC_EX_V2_USER_CMD_IS_FRAME_RDY,


    E_VDEC_EX_V2_USER_CMD_MVC_GET_CMD_BASE  = 0x1800,
    E_VDEC_EX_V2_USER_CMD_GET_MVC_SUB_FRAME_DISP_INFO,     // Param: VDEC_FrameInfo pointer.
    E_VDEC_EX_V2_USER_CMD_GET_MVC_BBU2_DECQ_VACANCY,       // Param: BBU2 Dec Q Vacancy.
    E_VDEC_EX_V2_USER_CMD_GET_MVC_ES2_READ_PTR,            // Param: ES2 read pointer.
    E_VDEC_EX_V2_USER_CMD_GET_MVC_ES2_WRITE_PTR,           // Param: ES2 Write pointer.
    E_VDEC_EX_V2_USER_CMD_GET_ES_QUANTITY,                 // Param: Get ES buffer Level.
    E_VDEC_EX_V2_USER_CMD_GET_ES2_QUANTITY,                // Param: Get ES2 buffer Level.

    //Group3:Preset Control command======================
    //Group3-1:Common system Preset Control command
    E_VDEC_EX_V2_USER_CMD_SYSTEM_PRESET_CONTROL_BASE  = 0x2000,
    E_VDEC_EX_V2_USER_CMD_SYSTEM_PRESET_VPU_CLOCK,         //Param: VDEC_EX_ClockSpeed

    //Group3-2:HVD System Preset Control command
    E_VDEC_EX_V2_USER_CMD_SYSTEM_PRESET_HVD_BASE      = 0x2100,
    E_VDEC_EX_V2_USER_CMD_SYSTEM_PRESET_HVD_CLOCK,         //Param: VDEC_EX_ClockSpeed

    //Group3-3:MVD System Preset Control command
    E_VDEC_EX_V2_USER_CMD_SYSTEM_PRESET_MVD_BASE      = 0x2200,
    E_VDEC_EX_V2_USER_CMD_SYSTEM_PRESET_MVD_CLOCK,         //Param: VDEC_EX_ClockSpeed
    E_VDEC_EX_V2_USER_CMD_VPU_SECURITY_MODE,               //Param: 0:disable,1:enable
    E_VDEC_EX_V2_USER_CMD_PRESET_DECODE_MODE,
    E_VDEC_EX_V2_USER_CMD_PRESET_ENABLETURBOMODE,
    E_VDEC_EX_V2_USER_CMD_PRESETSINGLEDECODE,
    E_VDEC_EX_V2_USER_CMD_PREGETSTATUS,
    E_VDEC_EX_V2_USER_CMD_SETPOWERSTATE,


    //Group3-4:Preset Control command=============================
    E_VDEC_EX_V2_USER_CMD_PRESET_CONTROL_BASE           = 0x2300,
    E_VDEC_EX_V2_USER_CMD_HVD_ONE_PENDING_BUFFER_MODE,  //Param: 0(Disable), 1(Enable), use only one pending buffer instead of two for HVD
    E_VDEC_EX_V2_USER_CMD_MVD_HWBUFFER_REMAPPING_MODE,  //Param: 0(Disable), 1(Enable),Allcate HW buffer to start of frame buffer
    E_VDEC_EX_V2_USER_CMD_SET_SHAREMEMORY_BASE,
    E_VDEC_EX_V2_USER_CMD_HVD_COL_BBU_MODE,                //Param: HVD use colocated BBU mode, 0: disable, 1: enable /*johnny.ko*/
    E_VDEC_EX_V2_USER_CMD_HVD_IAPGN_BUF_SHARE_BW_MODE,   //Param: HVD IAP GN Buffer address, 0xFFFFFFFF means disable

	E_VDEC_EX_V2_USER_CMD_HVD_TS_IN_BBU_MODE,	

    //Group4:Postset Control command======================
    E_VDEC_EX_V2_USER_CMD_SYSTEM_POSTSET_CONTROL_BASE  = 0x3000,
    E_VDEC_EX_V2_USER_CMD_SYSTEM_POSTSET_CLEAR_PROCESS_RELATED,

} VDEC_EX_V2_User_Cmd;
//-------------------------------------------------------------------------------------------------
//  Structure for Upper layer
//-------------------------------------------------------------------------------------------------
typedef struct
{
    MS_U32 u32Version;
    MS_U32 u32Id;
} VDEC_EX_V2_StreamId;

typedef struct
{
    VDEC_EX_V2_StreamId*    StreamID;
    VDEC_EX_V2_User_Cmd     eUserCmd;
    void* param[8];  // at most 8 param
    void* pRet;
}VDEC_EX_V2_IO_Param;

typedef struct
{
    VDEC_EX_V2_Stream    eStream;
    VDEC_EX_V2_CodecType eCodecType;
} VDEC_EX_V2_CodecInfo;

/// Configurations of f/w decode mode
typedef struct
{
    VDEC_EX_V2_DEC_MODE    eDecMod;
    VDEC_EX_V2_CodecInfo   pstCodecInfo[VDEC_EX_V2_MAX_DEC_NUM];
    MS_U8  u8CodecCnt;
    MS_U8  u8ArgSize;
    MS_U32 u32Arg;  //ref VDEC_EX_DEC_MODE_ARG enum
} VDEC_EX_V2_DecModCfg;

typedef struct
{
    MS_BOOL bEnable;      // 0 : disable   ,  1:enable
    MS_U8   u8DisplayTop; // 0: display top,  1: display bottom
}VDEC_EX_V2_Field_Polarity;

typedef struct
{
    MS_U32 u32version;
    MS_U32 u32size;
} VDEC_EX_V2_VerCtl;

/// Data structure of CC Configuration
typedef struct
{
    VDEC_EX_V2_CCFormat eFormat;
    VDEC_EX_V2_CCType   eType;
    MS_U32       u32BufStAdd;
    MS_U32       u32BufSize;
} VDEC_EX_V2_CCCfg;

/// information for display setting
typedef struct
{
    ///bitstream horizontal size
    MS_U16 u16HorSize;
    ///bitstream vertical size
    MS_U16 u16VerSize;
    ///frame rate
    MS_U32 u32FrameRate;
    ///interlace flag
    MS_U8 u8Interlace;
    ///active frame code
    MS_U8 u8AFD;
    ///Sample aspect rate width
    MS_U16 u16SarWidth;
    ///Sample aspect rate height
    MS_U16 u16SarHeight;
    ///right cropping
    MS_U16 u16CropRight;
    ///left cropping
    MS_U16 u16CropLeft;
    ///bottom cropping
    MS_U16 u16CropBottom;
    ///top cropping
    MS_U16 u16CropTop;
    ///pitch
    MS_U16 u16Pitch;
    ///interval of PTS
    MS_U16 u16PTSInterval;
    ///MPEG1 flag
    MS_U8 u8MPEG1;
    ///play mode (fixme)
    MS_U8 u8PlayMode;
    ///FRC mode
    MS_U8 u8FrcMode;
    ///aspect ratio code
    MS_U8 u8AspectRate;
    ///if FALSE, set VOP as mono mode (only for H264)
    MS_BOOL bWithChroma;
    /// if true, color space is xvYCC (Y from 16 to 235 and Cb , Cr from 16 to 240).
    /// if false, color space is BT.601/709 (Y from  0 to 255 and Cb , Cr from  0 to 255).
    /// only MPEG might be with BT.601/709
    MS_BOOL bColorInXVYCC;
    ///Dynamic scaling buffer address
    MS_U32 u32DynScalingAddr;
    ///Dynamic scaling buffer size
    MS_U32 u32DynScalingSize;
    ///Dynamic scaling depth
    MS_U8 u8DynScalingDepth;
    ///Dynamic scaling DS buffer on miu1 or miu0
    MS_BOOL bEnableMIUSel;
    ///Display width
    MS_U32 u32AspectWidth;
    ///Display height
    MS_U32 u32AspectHeight;
} VDEC_EX_V2_DispInfo;

/// system configuration
typedef struct
{
    ///FW binary start address
    MS_PHYADDR u32FWBinaryAddr;
    ///FW binary size
    MS_U32 u32FWBinarySize;
    ///FW code buffer start address
    MS_PHYADDR u32CodeBufAddr;
    ///FW code buffer size
    MS_U32 u32CodeBufSize;
    ///frame buffer start address
    MS_PHYADDR u32FrameBufAddr;
    ///frame buffer size
    MS_U32 u32FrameBufSize;
    ///bitstream buffer start address
    MS_PHYADDR u32BitstreamBufAddr;
    ///bitstream buffer size
    MS_U32 u32BitstreamBufSize;
    ///driver process buffer start address
    MS_PHYADDR u32DrvProcBufAddr;
    ///driver process buffer size
    MS_U32 u32DrvProcBufSize;
    ///vlc table Binary address (RM only)
    MS_PHYADDR u32VlcBinarySrcAddr;
    ///vld table Binary size
    MS_U32 u32VlcTabBinarySize;
    ///debug level setting
    VDEC_EX_V2_DbgLevel eDbgMsgLevel;
    ///debug level setting
    VDEC_EX_V2_FWSourceType eFWSourceType;
} VDEC_EX_V2_SysCfg;

/// video information
typedef struct
{
    ///input source mode
    VDEC_EX_V2_SrcMode   eSrcMode;
    /// timestamp type of command queue
    VDEC_EX_V2_TimeStampType      eTimeStampType;
    ///MJPEG scale factor
    VDEC_EX_V2_MJpegScaleFactor   eMJpegScaleFactor;
    /// should be TRUE when codec type is H264 and container is MKV and MP4(MOV)
    MS_BOOL bWithoutNalStCode;
    /// needness when CodecType is MJPEG and divx311
    //MS_U16  u16FrameRate;
    MS_U32 u32FrameRate;
    MS_U32 u32FrameRateBase;
    /// if divx311; use u16Width[0]; only need other elements when RV8
    MS_U16  u16Width[8];
    /// if divx311; use u16Height[0]; only need other elements when RV8
    MS_U16  u16Height[8];
    /// video number sizes (for RM)
    MS_U16  u16NumSizes;
} VDEC_EX_V2_VideoInfo;

/// frame information
typedef struct
{
    /// frame buffer base + the start offset of current displayed luma data. Unit: byte.
    MS_PHYADDR u32LumaAddr;
    /// frame buffer base + the start offset of current displayed chroma data. Unit: byte.
    MS_PHYADDR u32ChromaAddr;
    /// Time stamp(DTS, PTS) of current displayed frame. Unit: ms (todo: 90khz)
    MS_U32 u32TimeStamp;
    /// low part of ID number
    MS_U32 u32ID_L;
    /// high part of ID number
    MS_U32 u32ID_H;
    /// pitch
    MS_U16 u16Pitch;
    /// width
    MS_U16 u16Width;
    /// hight
    MS_U16 u16Height;
    ///< Frame type: I, P, B frame
    VDEC_EX_V2_FrameType eFrameType;
    ///< Field type: Top, Bottom, Both
    VDEC_EX_V2_FieldType eFieldType;
} VDEC_EX_V2_FrameInfo;

/// Extension display information
typedef struct
{
    /// vertical size from sequene_display_extension
    MS_U16 u16VSize;
    /// horizontal size from sequene_display_extension
    MS_U16 u16HSize;
    /// vertical offset from picture_display_extension
    MS_S16 s16VOffset;
    /// horizontal offset from picture_display_extension
    MS_S16 s16HOffset;
} VDEC_EX_V2_ExtDispInfo;

/// display frame information
typedef struct
{
    ///< frame information
    VDEC_EX_V2_FrameInfo stFrmInfo;
    ///< firmware private data
    MS_U32 u32PriData;
    ///< index used by apiVDEC to manage VDEC_DispQ[][]
    MS_U32 u32Idx;
} VDEC_EX_V2_DispFrame;

/// time code structure
typedef struct
{
    ///  time_code_hours
    MS_U8   u8TimeCodeHr;
    ///  time_code_minutes
    MS_U8   u8TimeCodeMin;
    ///  time_code_seconds
    MS_U8   u8TimeCodeSec;
    ///  time_code_pictures
    MS_U8   u8TimeCodePic;
    ///  drop_frame_flag
    MS_U8   u8DropFrmFlag;
    ///  reserved fields for 4-byte alignment
    MS_U8   u8Reserved[3];
} VDEC_EX_V2_TimeCode;

/// vdec frame buffer reduction
typedef struct
{
    VDEC_EX_V2_FBReductionType eLumaFBReduction;
    VDEC_EX_V2_FBReductionType eChromaFBReduction;
    MS_BOOL              bEnableAutoMode;   /// 0: Disable, 1: Enable
} VDEC_EX_V2_FBReduction;

/// Initial parameter
typedef struct
{
    /// init param version : 0
    MS_U32          u32Version;
    /// codec type
    VDEC_EX_V2_CodecType   eCodecType;
    /// system configuration
    VDEC_EX_V2_SysCfg      SysConfig;
    /// video information from container
    VDEC_EX_V2_VideoInfo   VideoInfo;
    /// dynamic scaling control bit
    MS_BOOL             EnableDynaScale;
    /// switch for display decode error frame or not
    MS_BOOL             bDisableDropErrFrame;
    /// switch for error concealment
    MS_BOOL             bDisableErrConceal;
    /// enable repeat last field when repeat happened at interlace stream
    MS_BOOL             bRepeatLastField;
    /// threshold to judge error frame
    MS_U8               u8ErrThreshold;
    /// dynamic scaling virtual box Width
    MS_U32              u32DSVirtualBoxWidth;
    /// dynamic scaling virtual box Height
    MS_U32              u32DSVirtualBoxHeight;
    /// vdec frame buffer reduction setting
    VDEC_EX_V2_FBReduction stFBReduction;
} VDEC_EX_V2_InitParam;

/// Decode Command
typedef struct
{
    /// ID (high 4-bytes)
    MS_U32  u32ID_H;
    /// ID (low 4-bytes)
    MS_U32  u32ID_L;
    /// start address of payload
    MS_U32  u32StAddr;
    /// size of payload
    MS_U32  u32Size;
    /// timestamp of payload
    MS_U32  u32Timestamp;
} VDEC_EX_V2_DecCmd;

/// Display Command
typedef struct
{
    /// ID (high 4-bytes)
    MS_U32  u32ID_H;
    /// ID (low 4-bytes)
    MS_U32  u32ID_L;
    /// action of command
    VDEC_EX_V2_DispCmdAction  eAction;
} VDEC_EX_V2_DispCmd;

typedef struct
{
    MS_U32                  u32Version;
    /// top, bottom or frame
    VDEC_EX_V2_PicStructure    u8PicStructure;
    MS_U8                   u8TopFieldFirst;
    MS_U16                  u16TempRef;
    MS_U32                  u32Pts;
    /// address of cc data
    MS_U32                  u32UserDataBuf;
    /// size of cc data
    MS_U32                  u32UserDataSize;
    ///< Frame type: I, P, B frame
    VDEC_EX_V2_FrameType eFrameType;
} VDEC_EX_V2_CC_Info;

///CC input parameters for mstar proprietary CC library
typedef struct
{
    MS_U32 u32Ver;      ///version of this structure
    MS_U32 u32Val;
} VDEC_EX_V2_CC_InputPara;

typedef struct
{
    MS_U32      u32OutputFrameRate; ///< output frame rate, unit:vsync count
    MS_U8       u8Interlace;        ///< output scan:0:progress, 1:interlace
} VDEC_EX_V2_FRC_OutputParam;


typedef void (*VDEC_EX_V2_EventCb)(MS_U32 eFlag, void *param);

typedef struct
{
    MS_U8   u8Frm_packing_arr_cnl_flag;
    MS_U8   u8Frm_packing_arr_type;
    MS_U8   u8content_interpretation_type;
    MS_U8   u1Quincunx_sampling_flag;

    MS_U8   u1Spatial_flipping_flag;
    MS_U8   u1Frame0_flipping_flag;
    MS_U8   u1Field_views_flag;
    MS_U8   u1Current_frame_is_frame0_flag;

    MS_U8   u1Frame0_self_contained_flag;
    MS_U8   u1Frame1_self_contained_flag;
    MS_U8   u4Frame0_grid_position_x;
    MS_U8   u4Frame0_grid_position_y;

    MS_U8   u4Frame1_grid_position_x;
    MS_U8   u4Frame1_grid_position_y;
    MS_U8   u8Reserved01;
    MS_U8   u8Reserved02;
}VDEC_EX_V2_Frame_packing_SEI;

typedef struct
{
    VDEC_EX_V2_VerCtl  stVerCtl;   /// version : 0,
                                /// size : sizeof(VDEC_EX_Frame_packing_SEI_EX)
    MS_BOOL bIsCropInfo;
    MS_BOOL bValid;
    MS_BOOL bUsed;
    MS_U8   u8Frm_packing_arr_cnl_flag;
    MS_U8   u8Frm_packing_arr_type;
    MS_U8   u8content_interpretation_type;
    MS_U8   u1Quincunx_sampling_flag;
    MS_U8   u1Spatial_flipping_flag;
    MS_U8   u1Frame0_flipping_flag;
    MS_U8   u1Field_views_flag;
    MS_U8   u1Current_frame_is_frame0_flag;
    MS_U8   u1Frame0_self_contained_flag;
    MS_U8   u1Frame1_self_contained_flag;
    MS_U8   u4Frame0_grid_position_x;
    MS_U8   u4Frame0_grid_position_y;
    MS_U8   u4Frame1_grid_position_x;
    MS_U8   u4Frame1_grid_position_y;
    MS_U32  u32DataBuff;
    MS_U32  u32DataSize;
    MS_U32  left;
    MS_U32  right;
    MS_U32  top;
    MS_U32  bottom;
} VDEC_EX_V2_Frame_packing_SEI_EX;

//CRC value
typedef struct
{
    MS_U32 u32HorSize;
    MS_U32 u32VerSize;
    MS_U32 u32Strip;
    MS_U32 u32LumaStartAddr;
    MS_U32 u32ChromaStartAddr;
}VDEC_EX_V2_CrcIn;

typedef struct
{
    MS_U32 u32LumaCRC;
    MS_U32 u32ChromaCRC;
}VDEC_EX_V2_CrcOut;

typedef struct
{
    VDEC_EX_V2_CrcIn stCrcIn;
    VDEC_EX_V2_CrcOut stCrcOut;
}VDEC_EX_V2_CrcValue;

//-------------------------------------------------------------------------------------------------
//  Function pointer for Upper layer
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  API for Upper layer
//-------------------------------------------------------------------------------------------------

void VDEC_EX_V2_RegisterToUtopia(FUtopiaOpen ModuleType);
MS_U32 VDEC_EX_V2_Open(void** ppInstance, const void* const pAttribute);
MS_U32 VDEC_EX_V2_Close(void* pInstance);
MS_U32 VDEC_EX_V2_IOctl(void* pInstance, MS_U32 u32Cmd, void* pArgs);

#ifdef __cplusplus
}
#endif

#endif
#undef _VDEC_EX_V2_H_
#endif //_VDEC_EX_V2_H_
