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
/// @file   apiVDEC_EX.h
/// @brief  VDEC EXTENSION API FOR DUAL STREAMS
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _API_VDEC_EX_H_
#define _API_VDEC_EX_H_

#ifdef __cplusplus
extern "C"
{
#endif
//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define MSIF_VDEC_EX_LIB_CODE      {'V','E','X','_'}
#define MSIF_VDEC_EX_LIBVER        {'0','1'}
#define MSIF_VDEC_EX_BUILDNUM      {'0','9'}
#define MSIF_VDEC_EX_CHANGELIST    {'0','0','5','2','1','2','0','6'}

/// Version string.
#define VDEC_EX_API_VERSION                /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_VDEC_EX_LIB_CODE,                 /* IP__                                             */  \
    MSIF_VDEC_EX_LIBVER,                   /* 0.0 ~ Z.Z                                        */  \
    MSIF_VDEC_EX_BUILDNUM,                 /* 00 ~ 99                                          */  \
    MSIF_VDEC_EX_CHANGELIST,               /* CL#                                              */  \
    MSIF_OS

#define VDEC_EX_DEFAULT_DBG_MSG_LEVEL  E_VDEC_EX_DBG_LEVEL_DBG
#define VDEC_EX_RVD_BROKEN_BY_US   0x80000000
#define VDEC_EX_MVD_PIC_START_FLAG 0x40000000

#define VDEC_EX_BIT(_bit_)                  (1 << (_bit_))
//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

#define VDEC_EX_FPA_TYPE_CHECKERBOARD_INTERLEAVING  0
#define VDEC_EX_FPA_TYPE_COLUMN_INTERLEAVEING       1
#define VDEC_EX_FPA_TYPE_ROW_INTERLEAVEING          2
#define VDEC_EX_FPA_TYPE_SIDE_BY_SIDE_PACKING       3
#define VDEC_EX_FPA_TYPE_TOP_BOTTOM_PACKING         4
#define VDEC_EX_FPA_TYPE_TEMPORAL_INTERLEAVING_FRM  5

#define VDEC_MAX_DEC_NUM 2

typedef enum
{
    E_VDEC_EX_MAIN_STREAM = 0,
    E_VDEC_EX_SUB_STREAM,
} VDEC_EX_Stream;

/// decoder event enumerator.
typedef enum
{
    /// turn off all event
    E_VDEC_EX_EVENT_OFF                = 0x00,
    /// display one frame/field
    E_VDEC_EX_EVENT_DISP_ONE           = VDEC_EX_BIT(0),
    /// repeat one frame/field
    E_VDEC_EX_EVENT_DISP_REPEAT        = VDEC_EX_BIT(1),
    /// one CC data should be displayed
    E_VDEC_EX_EVENT_DISP_WITH_CC       = VDEC_EX_BIT(2),
    /// decode one frame
    E_VDEC_EX_EVENT_DEC_ONE            = VDEC_EX_BIT(3),
    /// decode one I frame
    E_VDEC_EX_EVENT_DEC_I              = VDEC_EX_BIT(4),
    /// decode error
    E_VDEC_EX_EVENT_DEC_ERR            = VDEC_EX_BIT(5),
    /// display information is changed
    E_VDEC_EX_EVENT_DISP_INFO_CHG      = VDEC_EX_BIT(6),
    /// find user data
    E_VDEC_EX_EVENT_USER_DATA_FOUND    = VDEC_EX_BIT(7),
    /// display information ready after be changed
    E_VDEC_EX_EVENT_DISP_INFO_RDY      = VDEC_EX_BIT(8),
    /// first frame decoded
    E_VDEC_EX_EVENT_FIRST_FRAME        = VDEC_EX_BIT(9),
    /// first picture found
    E_VDEC_EX_EVENT_PIC_FOUND          = VDEC_EX_BIT(10),
    /// video is ready to display (no garbage and avsync done)
    E_VDEC_EX_EVENT_VIDEO_UNMUTE       = VDEC_EX_BIT(11),
    /// new sequence header found
    E_VDEC_EX_EVENT_SEQ_HDR_FOUND      = VDEC_EX_BIT(12),
    /// active format description found
    E_VDEC_EX_EVENT_AFD_FOUND          = VDEC_EX_BIT(13),
} VDEC_EX_EventFlag;

//define VDEC CB type
typedef enum
{
    E_VDEC_EX_CB_MAIN  = 0,
    E_VDEC_EX_CB_SUB,
} VDEC_EX_CB_TYPE;

/// codec type enumerator
typedef enum
{
    ///unsupported codec type
    E_VDEC_EX_CODEC_TYPE_NONE = 0,
    ///MPEG 1/2
    E_VDEC_EX_CODEC_TYPE_MPEG2,
    ///H263 (short video header)
    E_VDEC_EX_CODEC_TYPE_H263,
    ///MPEG4 (default)
    E_VDEC_EX_CODEC_TYPE_MPEG4,
    ///MPEG4 (Divx311)
    E_VDEC_EX_CODEC_TYPE_DIVX311,
    ///MPEG4 (Divx412)
    E_VDEC_EX_CODEC_TYPE_DIVX412,
    ///FLV
    E_VDEC_EX_CODEC_TYPE_FLV,
    ///VC1 advanced profile (VC1)
    E_VDEC_EX_CODEC_TYPE_VC1_ADV,
    ///VC1 main profile (RCV)
    E_VDEC_EX_CODEC_TYPE_VC1_MAIN,
    ///Real Video version 8
    E_VDEC_EX_CODEC_TYPE_RV8,
    ///Real Video version 9 and 10
    E_VDEC_EX_CODEC_TYPE_RV9,
    ///H264
    E_VDEC_EX_CODEC_TYPE_H264,
    ///AVS
    E_VDEC_EX_CODEC_TYPE_AVS,
    ///MJPEG
    E_VDEC_EX_CODEC_TYPE_MJPEG,
    ///MVC
    E_VDEC_EX_CODEC_TYPE_MVC,
    ///VP8
    E_VDEC_EX_CODEC_TYPE_VP8,
    E_VDEC_EX_CODEC_TYPE_NUM
} VDEC_EX_CodecType;

/// input source select enumerator
typedef enum
{
    ///DTV mode
    E_VDEC_EX_SRC_MODE_DTV = 0,
    ///TS file mode
    E_VDEC_EX_SRC_MODE_TS_FILE,
    ///generic file mode
    E_VDEC_EX_SRC_MODE_FILE,
    /// TS file and dual ES buffer mode
    E_VDEC_EX_SRC_MODE_TS_FILE_DUAL_ES,
    ///generic file and dual ES buffer mode
    E_VDEC_EX_SRC_MODE_FILE_DUAL_ES,
} VDEC_EX_SrcMode;

/// function return enumerator
typedef enum
{
    ///failed
    E_VDEC_EX_FAIL = 0,
    ///success
    E_VDEC_EX_OK,
    ///invalid parameter
    E_VDEC_EX_RET_INVALID_PARAM,
    ///access not allow
    E_VDEC_EX_RET_ILLEGAL_ACCESS,
    ///hardware abnormal
    E_VDEC_EX_RET_HARDWARE_BREAKDOWN,
     ///unsupported
    E_VDEC_EX_RET_UNSUPPORTED,
     ///timeout
    E_VDEC_EX_RET_TIMEOUT,
    ///not ready
    E_VDEC_EX_RET_NOT_READY,
    ///not initial
    E_VDEC_EX_RET_NOT_INIT,
    ///not exit after last initialization
    E_VDEC_EX_RET_NOT_EXIT,
    ///not running, counter does not change
    E_VDEC_EX_RET_NOT_RUNNING,
    ///max value
    E_VDEC_EX_RET_NUM,
} VDEC_EX_Result;

/// Action enumerator of display commands
typedef enum
{
    /// Action- display frame
    E_VDEC_EX_DISP_ACTION_DISPLAY   = 1,
    /// Action - release frame
    E_VDEC_EX_DISP_ACTION_RELEASE,
} VDEC_EX_DispCmdAction;

/// Freeze picture select after flush decoder
typedef enum
{
    /// Freeze at current display picture
    E_VDEC_EX_FREEZE_AT_CUR_PIC = 1,
    /// freeze at the latest decode picture
    E_VDEC_EX_FREEZE_AT_LAST_PIC,
} VDEC_EX_FreezePicSelect;

/// error code enumerator
typedef enum
{
    E_VDEC_EX_ERR_CODE_BASE = 0x01000000,
    E_VDEC_EX_ERR_CODE_NOT_SUPPORT,
    E_VDEC_EX_ERR_CODE_ILLEGAL_ACCESS,
    E_VDEC_EX_ERR_CODE_FRMRATE_NOT_SUPPORT,

    E_VDEC_EX_MVD_ERR_CODE_BASE = 0x02000000,
        E_VDEC_EX_MVD_ERR_CODE_SHAPE,
        E_VDEC_EX_MVD_ERR_CODE_USED_SPRITE,
        E_VDEC_EX_MVD_ERR_CODE_NOT_8_BIT,         //error_status : bits per pixel
        E_VDEC_EX_MVD_ERR_CODE_NERPRED_ENABLE,
        E_VDEC_EX_MVD_ERR_CODE_REDUCED_RES_ENABLE,
        E_VDEC_EX_MVD_ERR_CODE_SCALABILITY,
        E_VDEC_EX_MVD_ERR_CODE_OTHER,
        E_VDEC_EX_MVD_ERR_CODE_H263_ERROR,
        E_VDEC_EX_MVD_ERR_CODE_RES_NOT_SUPPORT,   //error_status : none
        E_VDEC_EX_MVD_ERR_CODE_MPEG4_NOT_SUPPORT, //error_status : none
        E_VDEC_EX_MVD_ERR_CODE_VC1_NOT_SUPPORT,   //error_status : none
        E_VDEC_EX_MVD_ERR_CODE_RCV_ERROR_OCCUR,

    E_VDEC_EX_HVD_ERR_CODE_BASE = 0x03000000,
        E_VDEC_EX_HVD_ERR_CODE_GENERAL_BASE = (0x0000|E_VDEC_EX_HVD_ERR_CODE_BASE),
        E_VDEC_EX_HVD_ERR_CODE_OUT_OF_SPEC ,
        E_VDEC_EX_HVD_ERR_CODE_UNKNOW_ERR,
        E_VDEC_EX_HVD_ERR_CODE_HW_BREAK_DOWN,
        E_VDEC_EX_HVD_ERR_CODE_HW_DEC_TIMEOUT,
        E_VDEC_EX_HVD_ERR_CODE_OUT_OF_MEMORY,
        E_VDEC_EX_HVD_ERR_CODE_UNKNOWN_CODEC,
        // AVC
        E_VDEC_EX_HVD_ERR_CODE_AVC_BASE = (0x1000|E_VDEC_EX_HVD_ERR_CODE_BASE),
        E_VDEC_EX_HVD_ERR_CODE_AVC_SPS_BROKEN,
        E_VDEC_EX_HVD_ERR_CODE_AVC_SPS_NOT_IN_SPEC,
        E_VDEC_EX_HVD_ERR_CODE_AVC_SPS_NOT_ENOUGH_FRM,   // DPB size at specified level is smaller than the specified number of reference frames. This is not allowed
        E_VDEC_EX_HVD_ERR_CODE_AVC_PPS_BROKEN,           // PPS is not valid
        E_VDEC_EX_HVD_ERR_CODE_AVC_REF_LIST,
        E_VDEC_EX_HVD_ERR_CODE_AVC_NO_REF,
        E_VDEC_EX_HVD_ERR_CODE_AVC_RES,             // out of supported resolution
        // AVS
        E_VDEC_EX_HVD_ERR_CODE_AVS_BASE = (0x2000|E_VDEC_EX_HVD_ERR_CODE_BASE),
        E_VDEC_EX_HVD_ERR_CODE_AVS_RES,             // out of supported resolution
        // RM
        E_VDEC_EX_HVD_ERR_CODE_RM_BASE = (0x3000|E_VDEC_EX_HVD_ERR_CODE_BASE),
        E_VDEC_EX_HVD_ERR_CODE_RM_PACKET_HEADER,
        E_VDEC_EX_HVD_ERR_CODE_RM_FRAME_HEADER,
        E_VDEC_EX_HVD_ERR_CODE_RM_SLICE_HEADER,
        E_VDEC_EX_HVD_ERR_CODE_RM_BYTE_CNT,
        E_VDEC_EX_HVD_ERR_CODE_RM_DISP_TIMEOUT,
        E_VDEC_EX_HVD_ERR_CODE_RM_NO_REF,
        E_VDEC_EX_HVD_ERR_CODE_RM_RES,              // out of supported resolution
        E_VDEC_EX_HVD_ERR_CODE_RM_VLC,
        E_VDEC_EX_HVD_ERR_CODE_RM_SIZE_OUT_FB_LAYOUT,

    E_VDEC_EX_RVD_ERR_CODE_BASE = 0x04000000,
        E_VDEC_EX_RVD_ERR_CODE_PACKET_HEADER, ///< packet header version error
        E_VDEC_EX_RVD_ERR_CODE_FRAME_HEADER,  ///< frame type error
        E_VDEC_EX_RVD_ERR_CODE_SLICE_HEADER,  ///<slice header error
        E_VDEC_EX_RVD_ERR_CODE_DECODE_TIMEOUT,///< decode MB timeout
        E_VDEC_EX_RVD_ERR_CODE_OUT_OF_MEMORY, ///< frame buffer is out of memory
        E_VDEC_EX_RVD_ERR_CODE_BYTE_POS,      ///< can not find in ID table
        E_VDEC_EX_RVD_ERR_CODE_DISPLAY_TIMEOUT,

    E_VDEC_EX_MJPEG_ERR_CODE_BASE = 0x05000000,
        E_VDEC_EX_HVD_ERR_CODE_MJPEG_RES,
} VDEC_EX_ErrCode;

/// frame rate conversion mode enumerator
typedef enum
{
    /// disable FRC mode.
    E_VDEC_EX_FRC_NORMAL = 0,
    /// output rate is twice of input rate (ex. 30p to 60p)
    E_VDEC_EX_FRC_DISP_TWICE,
    /// 3:2 pulldown mode (ex. 24p to 60i or 60p)
    E_VDEC_EX_FRC_3_2_PULLDOWN,
    /// PAL to NTSC conversion (50i to 60i)
    E_VDEC_EX_FRC_PAL_TO_NTSC,
    /// NTSC to PAL conversion (60i to 50i)
    E_VDEC_EX_FRC_NTSC_TO_PAL,
    /// output rate 50P ->60P
    E_VDEC_EX_FRC_MODE_50P_60P,
    /// output rate 60P ->50P
    E_VDEC_EX_FRC_MODE_60P_50P,
} VDEC_EX_FrcMode;

/// trick decode mode enumerator
typedef enum
{
    /// decode all frame
    E_VDEC_EX_TRICK_DEC_ALL = 0,
    /// decode all except of non-reference frame
    E_VDEC_EX_TRICK_DEC_IP,
    /// only decode I frame
    E_VDEC_EX_TRICK_DEC_I,
    E_VDEC_EX_TRICK_DEC_NUM
} VDEC_EX_TrickDec;

/// display speed setting enumerator
typedef enum
{
    /// default speed type
    E_VDEC_EX_SPEED_DEFAULT = 0,
    /// fast display
    E_VDEC_EX_SPEED_FAST,
    /// slow display
    E_VDEC_EX_SPEED_SLOW,
} VDEC_EX_SpeedType;

/// The display speed enumerator
typedef enum
{
    /// Normal display speed.
    E_VDEC_EX_DISP_SPEED_1X = 1,
    /// 2X
    E_VDEC_EX_DISP_SPEED_2X = 2,
    /// 4X
    E_VDEC_EX_DISP_SPEED_4X = 4,
    /// 8X
    E_VDEC_EX_DISP_SPEED_8X = 8,
    /// 16X
    E_VDEC_EX_DISP_SPEED_16X = 16,
    /// 32X
    E_VDEC_EX_DISP_SPEED_32X = 32,
} VDEC_EX_DispSpeed;

/// motion JPEG down scale factor enumerator
typedef enum
{
    ///original size
    E_VDEC_EX_MJPEG_SCALE_1to1 = 0,
    ///down scale to 1/2
    E_VDEC_EX_MJPEG_SCALE_2to1,
    ///down scale to 1/4
    E_VDEC_EX_MJPEG_SCALE_4to1,
    ///down scale to 1/8
    E_VDEC_EX_MJPEG_SCALE_8to1,
} VDEC_EX_MJpegScaleFactor;

/// timestamp type of command queue
typedef enum
{
    ///without timestamp information
    E_VDEC_EX_TIME_STAMP_NONE = 0,
    ///PTS (Presentation Time Stamp)
    E_VDEC_EX_TIME_STAMP_PTS,
    ///DTS (Decode Time Stamp)
    E_VDEC_EX_TIME_STAMP_DTS,
    ///STS (Sorted Time Stamp)
    E_VDEC_EX_TIME_STAMP_STS,
} VDEC_EX_TimeStampType;

/// The debug level of VDEC
typedef enum
{
    /// disable all uart message.
    E_VDEC_EX_DBG_LEVEL_NONE = 0,
    /// Only output error message
    E_VDEC_EX_DBG_LEVEL_ERR,
    /// output general message, and above.
    E_VDEC_EX_DBG_LEVEL_INFO,
    /// output debug message, and above.
    E_VDEC_EX_DBG_LEVEL_DBG,
    /// output function tracing message, and above.
    E_VDEC_EX_DBG_LEVEL_TRACE,
    /// output FW message.
    E_VDEC_EX_DBG_LEVEL_FW,
} VDEC_EX_DbgLevel;

/// Type of FW source
typedef enum
{
    E_VDEC_EX_FW_SOURCE_NONE,
    E_VDEC_EX_FW_SOURCE_DRAM,
    E_VDEC_EX_FW_SOURCE_FLASH,
}VDEC_EX_FWSourceType;

/// Format of CC (Closed Caption)
typedef enum
{
    E_VDEC_EX_CC_NONE       = 0x00,
    E_VDEC_EX_CC_608        = 0x01, //For CC608 or 157
    E_VDEC_EX_CC_708        = 0x02, //For CC708
    E_VDEC_EX_CC_UNPACKED   = 0x03,
} VDEC_EX_CCFormat;

/// Type of CC
typedef enum
{
    E_VDEC_EX_CC_TYPE_NONE = 0,
    E_VDEC_EX_CC_TYPE_NTSC_FIELD1 = 1,
    E_VDEC_EX_CC_TYPE_NTSC_FIELD2 = 2,
    E_VDEC_EX_CC_TYPE_DTVCC = 3,
    E_VDEC_EX_CC_TYPE_NTSC_TWOFIELD = 4,
} VDEC_EX_CCType;

typedef enum
{
    E_VDEC_EX_CC_GET_BUFF_START = 0x1,
    E_VDEC_EX_CC_GET_BUFF_SIZE,
    E_VDEC_EX_CC_GET_708_ENABLE
} VDEC_EX_CCInfoCmd;

typedef enum
{
    E_VDEC_EX_STAGE_STOP = 0,
    E_VDEC_EX_STAGE_INIT,
    E_VDEC_EX_STAGE_PLAY,
    E_VDEC_EX_STAGE_PAUSE,
} VDEC_EX_Stage;


typedef enum
{
    /// Used before MApi_VDEC_EX_Flush().
    E_VDEC_EX_PATTERN_FLUSH = 0,
    /// Used after MApi_VDEC_EX_EnableLastFrameShow().
    E_VDEC_EX_PATTERN_FILEEND,
}VDEC_EX_PatternType;

typedef struct
{
    MS_BOOL bInit;
    MS_BOOL bIdle;
    VDEC_EX_Stage  eStage;
} VDEC_EX_Status;

typedef struct
{
    MS_U32 u32Tmp;
} VDEC_EX_Info;

typedef enum
{
    E_VDEC_EX_FRM_TYPE_I = 0,
    E_VDEC_EX_FRM_TYPE_P,
    E_VDEC_EX_FRM_TYPE_B,
    E_VDEC_EX_FRM_TYPE_OTHER,
    E_VDEC_EX_FRM_TYPE_NUM
} VDEC_EX_FrameType;

typedef enum
{
    ///< no field.
    E_VDEC_EX_FIELDTYPE_NONE,
    ///< Top field only.
    E_VDEC_EX_FIELDTYPE_TOP,
    ///< Bottom field only.
    E_VDEC_EX_FIELDTYPE_BOTTOM,
    ///< Both fields.
    E_VDEC_EX_FIELDTYPE_BOTH,
    E_VDEC_EX_FIELDTYPE_NUM
} VDEC_EX_FieldType;

typedef enum
{
    E_VDEC_EX_PATTERN_BEFORE_FRM = 0,
    E_VDEC_EX_PATTERN_AFTER_FRM,
    E_VDEC_EX_PATTERN_SKIP_DATA,
} VDEC_EX_PatchPattern;

typedef enum
{
    E_VDEC_EX_PIC_STRUCTURE_RSV = 0, //reserved
    E_VDEC_EX_PIC_STRUCTURE_TOP,
    E_VDEC_EX_PIC_STRUCTURE_BOT,
    E_VDEC_EX_PIC_STRCUTURE_FRM,
} VDEC_EX_PicStructure;

//VDEC FB reduction type
typedef enum
{
    VDEC_EX_FB_REDUCTION_NONE  = 0,
    VDEC_EX_FB_REDUCTION_1_2,
    VDEC_EX_FB_REDUCTION_1_4
} VDEC_EX_FBReductionType;

//VDEC user command id
typedef enum
{
    //Group1:Set Control command
    E_VDEC_EX_USER_CMD_SET_CONTROL_BASE  = 0x0000,
    E_VDEC_EX_USER_CMD_REPEAT_LAST_FIELD,               // Param: 1(ON), 0(OFF)
    E_VDEC_EX_USER_CMD_AVSYNC_REPEAT_TH,                // Param:0x01 ~ 0xFF(repeat times), 0xFF:always repeat when av is not sync
    E_VDEC_EX_USER_CMD_DISP_ONE_FIELD,                  // Param: 1(ON), 0(OFF)
    E_VDEC_EX_USER_CMD_FD_MASK_DELAY_COUNT,             // Param: unit is in vsync base for mute the fd_mask
    E_VDEC_EX_USER_CMD_FRC_OUTPUT,                      // Param: the address of VDEC_FRC_OutputParam
    E_VDEC_EX_USER_CMD_FRC_DROP_TYPE,                   // Param: 1(FRC_DROP_FIELD), 0(FRC_DROP_FRAME), default:0
    E_VDEC_EX_USER_CMD_FAST_DISPLAY,                    // Param: TRUE(Fast display), FALSE(Display until synced)
    E_VDEC_EX_USER_CMD_IGNORE_ERR_REF,                  // Param: TRUE(Ignore error reference), FALSE(Enable error reference handle)
    E_VDEC_EX_USER_CMD_FORCE_FOLLOW_DTV_SPEC,           // Param: 1(ON), 0(OFF)
    E_VDEC_EX_USER_CMD_AVC_MIN_FRM_GAP,                 // Param: Set the theshold of H264 frame gap, 0xFFFFFFFF don't care frame gap
    E_VDEC_EX_USER_CMD_DISABLE_SEQ_CHG,                 // Param: 1(Disable), 0(Enable)
    E_VDEC_EX_USER_CMD_SET_DISP_OUTSIDE_CTRL_MODE,      // Param: 1(ON) used for Openmax, 0(OFF) used for mstreamer and mm mode ,default : off
    E_VDEC_EX_USER_CMD_SET_DTV_USER_DATA_MODE,          // Param: 0(Support normal DVB CC, default case), 1(Support ATSC DirectTV CC), 2,3,4(Reserved)
    E_VDEC_EX_USER_CMD_SET_SINGLE_TASK_MODE,
    E_VDEC_EX_USER_CMD_AVC_DISABLE_ANTI_VDEAD,
    E_VDEC_EX_USER_CMD_DTV_RESET_MVD_PARSER,            // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_PVR_FLUSH_FRAME_BUFFER,
    E_VDEC_EX_USER_CMD_FORCE_INTERLACE_MODE,
    E_VDEC_EX_USER_CMD_RELEASE_FD_MASK,                 // Param: 1 to release fd mask when zooming or slow motion
    E_VDEC_EX_USER_CMD_SET_DECODE_MODE,
    E_VDEC_EX_USER_CMD_SUPPORT_AVC_TO_MVC,              // Param: 0(Do not support), 1(Support AVC to MVC)
    E_VDEC_EX_USER_CMD_3DLR_VIEW_EXCHANGE,              // Param: 0(Disable), 1(View L/R exhange)
    E_VDEC_EX_USER_CMD_SET_VSIZE_ALIGN,                 // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_SHOW_DECODE_ORDER,               // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_AVC_DISP_IGNORE_CROP,            // Param: 0(Disable), 1(Enable)
    E_VDEC_EX_USER_CMD_SET_DISP_FINISH_MODE,
    E_VDEC_EX_USER_CMD_SET_AVSYNC_MODE,
    E_VDEC_EX_USER_CMD_SUSPEND_DYNAMIC_SCALE,           // Param: 0(Disable, non-suspend DS), 1(Enable, suspend DS)
    E_VDEC_EX_USER_CMD_FORCE_AUTO_MUTE,
    E_VDEC_EX_USER_CMD_PUSH_DISPQ_WITH_REF_NUM,         // Param: 0(Disable), 1(Enable)

    E_VDEC_EX_USER_CMD_MVC_SET_CMD_BASE  = 0x0800,
    E_VDEC_EX_USER_CMD_MVC_BBU2_PUSH_PACKET,            // Param: Packet Info.
    E_VDEC_EX_USER_CMD_MVC_BBU2_FIRE_DECCMD,            // Param: Non

    //Group2:Get Control command
    E_VDEC_EX_USER_CMD_GET_CONTROL_BASE  = 0x1000,
    E_VDEC_EX_USER_CMD_GET_CHROMA_TYPE,
    E_VDEC_EX_USER_CMD_GET_REAL_FRAMERATE,              // Get Real FrameRate reported by decoder
    E_VDEC_EX_USER_CMD_GET_COLOR_MATRIX,                // Get color matrix coefficients reported by decoder
    E_VDEC_EX_USER_CMD_GET_MAIN_STREAM_ID,              // Get activated main stream ID
    E_VDEC_EX_USER_CMD_GET_SUB_STREAM_ID,               // Get activated sub stream ID
    E_VDEC_EX_USER_CMD_GET_DYNSCALE_ENABLED,
    E_VDEC_EX_USER_CMD_GET_FPA_SEI,
    E_VDEC_EX_USER_CMD_GET_U64PTS,
    E_VDEC_EX_USER_CMD_GET_ORI_INTERLACE_MODE,
    E_VDEC_EX_USER_CMD_GET_MBS_ONLY_FLAG,
    E_VDEC_EX_USER_CMD_GET_CRC_VALUE,                   //Get frame Y/UV crc value

    E_VDEC_EX_USER_CMD_MVC_GET_CMD_BASE  = 0x1800,
    E_VDEC_EX_USER_CMD_GET_MVC_SUB_FRAME_DISP_INFO,     // Param: VDEC_FrameInfo pointer.
    E_VDEC_EX_USER_CMD_GET_MVC_BBU2_DECQ_VACANCY,       // Param: BBU2 Dec Q Vacancy.
    E_VDEC_EX_USER_CMD_GET_MVC_ES2_READ_PTR,            // Param: ES2 read pointer.
    E_VDEC_EX_USER_CMD_GET_MVC_ES2_WRITE_PTR,           // Param: ES2 Write pointer.
    E_VDEC_EX_USER_CMD_GET_ES_QUANTITY,                 // Param: Get ES buffer Level.
    E_VDEC_EX_USER_CMD_GET_ES2_QUANTITY,                // Param: Get ES2 buffer Level.
} VDEC_EX_User_Cmd;

//VDEC FW TYPE
typedef enum
{
    E_VDEC_EX_FW_TYPE_MVD = 0,
    E_VDEC_EX_FW_TYPE_HVD,
} VDEC_EX_FwType;

/// DecodeMode for f/w tasks
typedef enum
{
    E_VDEC_EX_DEC_MODE_DUAL_INDIE = 0,                     ///< Two independent tasks
    E_VDEC_EX_DEC_MODE_DUAL_3D,                        ///< Two dependent tasks for 3D
    E_VDEC_EX_DEC_MODE_SINGLE,                         ///< One task use the whole SRAM
    E_VDEC_EX_DEC_MODE_MVC = E_VDEC_EX_DEC_MODE_SINGLE,
} VDEC_EX_DEC_MODE;

typedef struct
{
    VDEC_EX_Stream    eStream;
    VDEC_EX_CodecType eCodecType;
} VDEC_EX_CodecInfo;

/// Configurations of f/w decode mode
typedef struct
{
    VDEC_EX_DEC_MODE    eDecMod;
    VDEC_EX_CodecInfo   pstCodecInfo[VDEC_MAX_DEC_NUM];
    MS_U8  u8CodecCnt;
    MS_U8  u8ArgSize;
    MS_U32 u32Arg;  //ref VDEC_EX_DEC_MODE_ARG enum
} VDEC_EX_DecModCfg;

/// argument of DecodeMode structure for f/w tasks
typedef enum
{
    //Group1:Set Korea3DTV mode
    E_VDEC_EX_DEC_KR3D_MODE_BASE  = 0x0000,
    E_VDEC_EX_DEC_KR3D_INTERLACE_MODE = E_VDEC_EX_DEC_KR3D_MODE_BASE,
    E_VDEC_EX_DEC_KR3D_FORCE_P_MODE,

    //Group2:Set PIP mode
    E_VDEC_EX_DEC_PIP_MODE_BASE = 0x1000,
    E_VDEC_EX_DEC_PIP_SYNC_INDIE = E_VDEC_EX_DEC_PIP_MODE_BASE,
    E_VDEC_EX_DEC_PIP_SYNC_MAIN_STC,
    E_VDEC_EX_DEC_PIP_SYNC_SWITCH
} VDEC_EX_DEC_MODE_ARG;

typedef enum
{
    E_VDEC_EX_DIU_DRAM = 0,  //MCU mode
    E_VDEC_EX_DIU_HVD = 1,
    E_VDEC_EX_DIU_MVD  = 2,
    E_VDEC_EX_DIU_HVD_3DLR = 3,  //MVC
    E_VDEC_EX_DIU_MVD_3DLR = 4,  //Korea3D, WMV3D
    E_VDEC_EX_DIU_UNKNOWN = -1
} VDEC_EX_DIU;

/// Data structure of CC Configuration
typedef struct
{
    VDEC_EX_CCFormat eFormat;
    VDEC_EX_CCType   eType;
    MS_U32       u32BufStAdd;
    MS_U32       u32BufSize;
} VDEC_EX_CCCfg;

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
} VDEC_EX_DispInfo;

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
    VDEC_EX_DbgLevel eDbgMsgLevel;
    ///debug level setting
    VDEC_EX_FWSourceType eFWSourceType;
} VDEC_EX_SysCfg;

/// video information
typedef struct
{
    ///input source mode
    VDEC_EX_SrcMode   eSrcMode;
    /// timestamp type of command queue
    VDEC_EX_TimeStampType      eTimeStampType;
    ///MJPEG scale factor
    VDEC_EX_MJpegScaleFactor   eMJpegScaleFactor;
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
} VDEC_EX_VideoInfo;

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
    VDEC_EX_FrameType eFrameType;
    ///< Field type: Top, Bottom, Both
    VDEC_EX_FieldType eFieldType;
} VDEC_EX_FrameInfo;

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
} VDEC_EX_ExtDispInfo;

/// display frame information
typedef struct
{
    ///< frame information
    VDEC_EX_FrameInfo stFrmInfo;
    ///< firmware private data
    MS_U32 u32PriData;
    ///< index used by apiVDEC to manage VDEC_DispQ[][]
    MS_U32 u32Idx;
} VDEC_EX_DispFrame;

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
} VDEC_EX_TimeCode;

/// vdec frame buffer reduction
typedef struct
{
    VDEC_EX_FBReductionType eLumaFBReduction;
    VDEC_EX_FBReductionType eChromaFBReduction;
    MS_BOOL              bEnableAutoMode;   /// 0: Disable, 1: Enable
} VDEC_EX_FBReduction;

/// Initial parameter
typedef struct
{
    /// init param version : 0
    MS_U32          u32Version;
    /// codec type
    VDEC_EX_CodecType   eCodecType;
    /// system configuration
    VDEC_EX_SysCfg      SysConfig;
    /// video information from container
    VDEC_EX_VideoInfo   VideoInfo;
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
    VDEC_EX_FBReduction stFBReduction;
} VDEC_EX_InitParam;

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
} VDEC_EX_DecCmd;

/// Display Command
typedef struct
{
    /// ID (high 4-bytes)
    MS_U32  u32ID_H;
    /// ID (low 4-bytes)
    MS_U32  u32ID_L;
    /// action of command
    VDEC_EX_DispCmdAction  eAction;
} VDEC_EX_DispCmd;

typedef struct
{
    MS_U32                  u32Version;
    /// top, bottom or frame
    VDEC_EX_PicStructure    u8PicStructure;
    MS_U8                   u8TopFieldFirst;
    MS_U16                  u16TempRef;
    MS_U32                  u32Pts;
    /// address of cc data
    MS_U32                  u32UserDataBuf;
    /// size of cc data
    MS_U32                  u32UserDataSize;
} VDEC_EX_CC_Info;

///CC input parameters for mstar proprietary CC library
typedef struct
{
    MS_U32 u32Ver;      ///version of this structure
    MS_U32 u32Val;
} VDEC_EX_CC_InputPara;

typedef struct
{
    MS_U32      u32OutputFrameRate; ///< output frame rate, unit:vsync count
    MS_U8       u8Interlace;        ///< output scan:0:progress, 1:interlace
} VDEC_EX_FRC_OutputParam;

typedef struct
{
    MS_U32 u32Version;
    MS_U32 u32Id;
} VDEC_StreamId;

typedef void (*VDEC_EX_EventCb)(MS_U32 eFlag, void *param);

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
}VDEC_EX_Frame_packing_SEI;

//CRC value
typedef struct
{
    MS_U32 u32HorSize;
    MS_U32 u32VerSize;
    MS_U32 u32Strip;
    MS_U32 u32LumaStartAddr;
    MS_U32 u32ChromaStartAddr;
}VDEC_EX_CrcIn;

typedef struct
{
    MS_U32 u32LumaCRC;
    MS_U32 u32ChromaCRC;
}VDEC_EX_CrcOut;

typedef struct
{
    VDEC_EX_CrcIn stCrcIn;
    VDEC_EX_CrcOut stCrcOut;
}VDEC_EX_CrcValue;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
VDEC_EX_Result MApi_VDEC_EX_GetLibVer(const MSIF_Version **ppVersion);
VDEC_EX_Result MApi_VDEC_EX_GetInfo(const VDEC_EX_Info **ppInfo);
MS_BOOL MApi_VDEC_EX_GetStatus(VDEC_StreamId *pStreamId, VDEC_EX_Status *pStatus);
VDEC_EX_Result MApi_VDEC_EX_EnableTurboMode(MS_BOOL bEnable);
MS_BOOL MApi_VDEC_EX_CheckCaps(VDEC_StreamId *pStreamId, VDEC_EX_CodecType eCodecType);

VDEC_EX_Result MApi_VDEC_EX_SetSingleDecode(MS_BOOL bEnable);
VDEC_EX_Result MApi_VDEC_EX_GetFreeStream(void *pInfo, MS_U32 u32Size, VDEC_EX_Stream eStreamType, VDEC_EX_CodecType eCodecType);
VDEC_EX_Result MApi_VDEC_EX_Init(VDEC_StreamId *eStreamId, VDEC_EX_InitParam *pInitParam);
VDEC_EX_Result MApi_VDEC_EX_Rst(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_Exit(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_CheckDispInfoRdy(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_SetFrcMode(VDEC_StreamId *pStreamId, VDEC_EX_FrcMode eFrcMode);
VDEC_EX_Result MApi_VDEC_EX_SetDynScalingParams(VDEC_StreamId *pStreamId, MS_PHYADDR u32Addr, MS_U32 u32Size);
VDEC_EX_Result MApi_VDEC_EX_SetDbgLevel(VDEC_StreamId *pStreamId, VDEC_EX_DbgLevel eDbgLevel);

VDEC_EX_Result MApi_VDEC_EX_Play(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_Pause(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_Resume(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_StepDisp(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_IsStepDispDone(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_StepDecode(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_IsStepDecodeDone(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_SetTrickMode(VDEC_StreamId *pStreamId, VDEC_EX_TrickDec eTrickDec);

VDEC_EX_Result MApi_VDEC_EX_PushDecQ(VDEC_StreamId *pStreamId, VDEC_EX_DecCmd *pCmd);
VDEC_EX_Result MApi_VDEC_EX_Flush(VDEC_StreamId *pStreamId, VDEC_EX_FreezePicSelect eFreezePic);
VDEC_EX_Result MApi_VDEC_EX_EnableLastFrameShow(VDEC_StreamId *pStreamId, MS_BOOL bEnable);
VDEC_EX_Result MApi_VDEC_EX_SetSpeed(VDEC_StreamId *pStreamId, VDEC_EX_SpeedType eSpeedType, VDEC_EX_DispSpeed eSpeed);
VDEC_EX_Result MApi_VDEC_EX_SetFreezeDisp(VDEC_StreamId *pStreamId, MS_BOOL bEnable);
VDEC_EX_Result MApi_VDEC_EX_SetBlueScreen(VDEC_StreamId *pStreamId, MS_BOOL bOn);
VDEC_EX_Result MApi_VDEC_EX_ResetPTS(VDEC_StreamId *pStreamId, MS_U32 u32PtsBase);
VDEC_EX_Result MApi_VDEC_EX_AVSyncOn(VDEC_StreamId *pStreamId, MS_BOOL bOn, MS_U32 u32SyncDelay, MS_U16 u16SyncTolerance);
VDEC_EX_Result MApi_VDEC_EX_SetAVSyncFreerunThreshold(VDEC_StreamId *pStreamId, MS_U32 u32Threshold );

VDEC_EX_Result MApi_VDEC_EX_GetDispInfo(VDEC_StreamId *pStreamId, VDEC_EX_DispInfo *pDispinfo);
VDEC_EX_Result MApi_VDEC_EX_IsAVSyncOn(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_IsWithValidStream(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_IsDispFinish(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_IsFrameRdy(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_IsIFrameFound(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_IsSeqChg(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_IsReachSync(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_IsStartSync(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_IsFreerun(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_IsWithLowDelay(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_IsAllBufferEmpty(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_GetExtDispInfo(VDEC_StreamId *pStreamId, VDEC_EX_ExtDispInfo *pExtDispinfo);
VDEC_EX_Result MApi_VDEC_EX_GetDecFrameInfo(VDEC_StreamId *pStreamId, VDEC_EX_FrameInfo *pFrmInfo);
VDEC_EX_Result MApi_VDEC_EX_GetDispFrameInfo(VDEC_StreamId *pStreamId, VDEC_EX_FrameInfo *pFrmInfo);
VDEC_EX_Result MApi_VDEC_EX_GetDecTimeCode(VDEC_StreamId *pStreamId, VDEC_EX_TimeCode* pTimeCode);
VDEC_EX_Result MApi_VDEC_EX_GetDispTimeCode(VDEC_StreamId *pStreamId, VDEC_EX_TimeCode* pTimeCode);
VDEC_EX_Result MApi_VDEC_EX_SetEvent(VDEC_StreamId *pStreamId, MS_U32 u32EventFlag, VDEC_EX_EventCb pfn, void* param);
VDEC_EX_Result MApi_VDEC_EX_UnsetEvent(VDEC_StreamId *pStreamId, MS_U32 u32EventFlag);
VDEC_EX_Result MApi_VDEC_EX_SetEvent_MultiCallback(VDEC_StreamId *pStreamId, VDEC_EX_CB_TYPE cb_type, MS_U32 u32EventFlag, VDEC_EX_EventCb pfn, void *param);
VDEC_EX_Result MApi_VDEC_EX_UnsetEvent_MultiCallback(VDEC_StreamId *pStreamId, VDEC_EX_CB_TYPE cb_type, MS_U32 u32EventFlag);
VDEC_EX_Result MApi_VDEC_EX_GetEventInfo(VDEC_StreamId *pStreamId, MS_U32* u32EventFlag);

VDEC_EX_Result MApi_VDEC_EX_FireDecCmd(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_SeekToPTS(VDEC_StreamId *pStreamId, MS_U32 u32PTS);
VDEC_EX_Result MApi_VDEC_EX_SkipToPTS(VDEC_StreamId *pStreamId, MS_U32 u32PTS);

// Advanced Settings / Mode
VDEC_EX_Result MApi_VDEC_EX_DisableDeblocking(VDEC_StreamId *pStreamId, MS_BOOL bDisable);
VDEC_EX_Result MApi_VDEC_EX_DisableQuarterPixel(VDEC_StreamId *pStreamId, MS_BOOL bDisable);
VDEC_EX_Result MApi_VDEC_EX_SetAutoRmLstZeroByte(VDEC_StreamId *pStreamId, MS_BOOL bOn);
VDEC_EX_Result MApi_VDEC_EX_SetBalanceBW(VDEC_StreamId *pStreamId,
                                        MS_U8 u8QuarPixelTH, MS_U8 u8DeBlockingTH, MS_U8 u8UpperBound, MS_U8 u8SafeCoef);

MS_U8 MApi_VDEC_EX_GetActiveFormat(VDEC_StreamId *pStreamId);
MS_U8 MApi_VDEC_EX_GetColourPrimaries(VDEC_StreamId *pStreamId);
MS_U32 MApi_VDEC_EX_GetFwVersion(VDEC_StreamId *pStreamId, VDEC_EX_FwType eFwType);
MS_U8 MApi_VDEC_EX_GetGOPCnt(VDEC_StreamId *pStreamId);
MS_U32 MApi_VDEC_EX_GetESWritePtr(VDEC_StreamId *pStreamId);
MS_U32 MApi_VDEC_EX_GetESReadPtr(VDEC_StreamId *pStreamId);
MS_U32 MApi_VDEC_EX_GetPTS(VDEC_StreamId *pStreamId);
MS_U32 MApi_VDEC_EX_GetNextPTS(VDEC_StreamId *pStreamId);
MS_S64 MApi_VDEC_EX_GetVideoPtsStcDelta(VDEC_StreamId *pStreamId);
MS_U32 MApi_VDEC_EX_GetErrCode(VDEC_StreamId *pStreamId);
MS_U32 MApi_VDEC_EX_GetErrCnt(VDEC_StreamId *pStreamId);
MS_U32 MApi_VDEC_EX_GetBitsRate(VDEC_StreamId *pStreamId);
MS_U32 MApi_VDEC_EX_GetFrameCnt(VDEC_StreamId *pStreamId);
MS_U32 MApi_VDEC_EX_GetSkipCnt(VDEC_StreamId *pStreamId);
MS_U32 MApi_VDEC_EX_GetDropCnt(VDEC_StreamId *pStreamId);
MS_U32 MApi_VDEC_EX_GetDispCnt(VDEC_StreamId *pStreamId);
MS_U32 MApi_VDEC_EX_GetDecQVacancy(VDEC_StreamId *pStreamId);
MS_BOOL MApi_VDEC_EX_Is32PullDown(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_IsAlive(VDEC_StreamId *pStreamId);
MS_BOOL MApi_VDEC_EX_IsCCAvailable(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_GetCCInfo(VDEC_StreamId *pStreamId, void *pInfo, MS_U32 u32Size);

VDEC_EX_TrickDec MApi_VDEC_EX_GetTrickMode(VDEC_StreamId *pStreamId);
VDEC_EX_CodecType MApi_VDEC_EX_GetActiveCodecType(VDEC_StreamId *pStreamId);

VDEC_EX_Result MApi_VDEC_EX_GenPattern(VDEC_StreamId *pStreamId,
                                    VDEC_EX_PatternType ePatternType,
                                    MS_PHYADDR u32Addr,
                                    MS_U32* u32Size);
MS_U32 MApi_VDEC_EX_GetPatternLeastLength(VDEC_StreamId *pStreamId, VDEC_EX_PatternType ePatternType);

VDEC_EX_Result MApi_VDEC_EX_MHEG_DecodeIFrame(VDEC_StreamId *pStreamId,
                                            MS_PHYADDR u32FrameBufAddr,
                                            MS_PHYADDR u32SrcSt,
                                            MS_PHYADDR u32SrcEnd);
VDEC_EX_Result MApi_VDEC_EX_MHEG_IsIFrameDecoding(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_MHEG_RstIFrameDec(VDEC_StreamId *pStreamId);

//ATSC Closed Caption control
#ifndef ANDROID
VDEC_EX_Result MApi_VDEC_EX_CC_StartParsing(VDEC_StreamId *pStreamId, VDEC_EX_CCCfg *pCCParam);
VDEC_EX_Result MApi_VDEC_EX_CC_StopParsing(VDEC_StreamId *pStreamId);
VDEC_EX_Result MApi_VDEC_EX_CC_GetWritePtr(VDEC_StreamId *pStreamId, MS_U32 *pu32Write);
VDEC_EX_Result MApi_VDEC_EX_CC_GetReadPtr(VDEC_StreamId *pStreamId, MS_U32 *pu32Read);
VDEC_EX_Result MApi_VDEC_EX_CC_UpdateReadPtr(VDEC_StreamId *pStreamId, MS_U32 u32EachPacketSize);
VDEC_EX_Result MApi_VDEC_EX_CC_GetIsOverflow(VDEC_StreamId *pStreamId, MS_BOOL *pbOverflow);
#endif
VDEC_EX_Result MApi_VDEC_EX_DbgCmd(VDEC_StreamId *pStreamId, MS_U32 u8Cmd, MS_U32 u32CmdArg);
VDEC_EX_Result MApi_VDEC_EX_DbgSetData(VDEC_StreamId *pStreamId, MS_U32 u32Addr, MS_U32 u32Data);
VDEC_EX_Result MApi_VDEC_EX_DbgGetData(VDEC_StreamId *pStreamId, MS_U32 u32Addr, MS_U32 *u32Data);

VDEC_EX_Result MApi_VDEC_EX_SetControl(VDEC_StreamId *pStreamId, VDEC_EX_User_Cmd cmd_id, MS_U32 param);
VDEC_EX_Result MApi_VDEC_EX_GetControl(VDEC_StreamId *pStreamId, VDEC_EX_User_Cmd cmd_id, MS_U32 *param);

//???
VDEC_EX_Result MApi_VDEC_EX_EnableDispOneField(VDEC_StreamId *pStreamId, MS_BOOL bEnable);
VDEC_EX_Result MApi_VDEC_EX_GetHWKey(VDEC_StreamId *pStreamId, MS_U8 *pu8Key);
void MApi_VDEC_EX_DbgDumpStatus(VDEC_StreamId *pStreamId);
MS_U32 MApi_VDEC_EX_DbgGetProgCnt(void);

VDEC_EX_Result MApi_VDEC_EX_SetBlockDisplay(VDEC_StreamId *pStreamId, MS_BOOL bEnable);
VDEC_EX_Result MApi_VDEC_EX_EnableESBuffMalloc(VDEC_StreamId *pStreamId, MS_BOOL bEnable);
MS_U32 MApi_VDEC_EX_GetESBuffVacancy(VDEC_StreamId *pStreamId, void *pData);
VDEC_EX_Result  MApi_VDEC_EX_GetESBuff(VDEC_StreamId *pStreamId, MS_U32 u32ReqSize, MS_U32 *u32AvailSize, MS_PHYADDR *u32Addr);
VDEC_EX_Result  MApi_VDEC_EX_GetNextDispFrame(VDEC_StreamId *pStreamId, VDEC_EX_DispFrame **ppDispFrm);
VDEC_EX_Result  MApi_VDEC_EX_DisplayFrame(VDEC_StreamId *pStreamId, VDEC_EX_DispFrame *pDispFrm);
VDEC_EX_Result  MApi_VDEC_EX_ReleaseFrame(VDEC_StreamId *pStreamId, VDEC_EX_DispFrame *pDispFrm);
VDEC_EX_Result  MApi_VDEC_EX_CaptureFrame(VDEC_StreamId *pStreamId, MS_U32 u32FrmPriData, MS_BOOL bEnable);
#ifndef ANDROID
VDEC_EX_Result MApi_VDEC_EX_CC_Init(VDEC_StreamId *pStreamId, MS_U32 *pIn);
VDEC_EX_Result MApi_VDEC_EX_CC_SetCfg(VDEC_StreamId *pStreamId, VDEC_EX_CCFormat eFmt, VDEC_EX_CCType eType, MS_U32 *pIn);
VDEC_EX_Result MApi_VDEC_EX_CC_SetBuffStartAdd(VDEC_StreamId *pStreamId, VDEC_EX_CCFormat eFmt, MS_U32 *pIn);
VDEC_EX_Result MApi_VDEC_EX_CC_UpdateWriteAdd(VDEC_StreamId *pStreamId, VDEC_EX_CCFormat eFmt, MS_U32 *pIn);
VDEC_EX_Result MApi_VDEC_EX_CC_UpdateReadAdd(VDEC_StreamId *pStreamId, VDEC_EX_CCFormat eFmt, MS_U32 *pIn);
VDEC_EX_Result MApi_VDEC_EX_CC_DisableParsing(VDEC_StreamId *pStreamId, VDEC_EX_CCFormat eFmt);
VDEC_EX_Result MApi_VDEC_EX_CC_GetInfo(VDEC_StreamId *pStreamId, VDEC_EX_CCFormat eFmt, VDEC_EX_CCInfoCmd eCmd, MS_U32 *pOut);
VDEC_EX_Result MApi_VDEC_EX_CC_GetIsRstDone(VDEC_StreamId *pStreamId, VDEC_EX_CCFormat eFmt);
VDEC_EX_Result MApi_VDEC_EX_CC_GetIsBuffOverflow(VDEC_StreamId *pStreamId, VDEC_EX_CCFormat eFmt);
MS_PHYADDR MApi_VDEC_EX_CC_GetWriteAdd(VDEC_StreamId *pStreamId, VDEC_EX_CCFormat eFmt);
MS_PHYADDR MApi_VDEC_EX_CC_GetReadAdd(VDEC_StreamId *pStreamId, VDEC_EX_CCFormat eFmt);
#endif
#ifdef __cplusplus
}
#endif

#endif // _API_VDEC_EX_H_

