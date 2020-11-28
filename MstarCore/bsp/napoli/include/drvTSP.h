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
///////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    drvTSP.h
/// @brief  Transport Stream Processer (TSP) Driver Interface
/// @author MStar Semiconductor,Inc.
/// @attention
/// All TSP DDI are not allowed to use in any interrupt context other than TSP ISR and Callback
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_TSP_H_
#define _DRV_TSP_H_

#include "MsTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif


//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------

#define DRVTSP_FILTER_DEPTH         16                                                              // TSP_FILTER_DEPTH

/// TSP byte address alignment unit
#define DRVTSP_ALIGN_UNIT           8

/// TSP byte address alignment macro
#define DRVTSP_ALIGN(_x)            ALIGN_8((MS_U32)_x)

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
/// Transport stream null PID
#define DRVTSP_PID_NULL             0x1FFF
#define MSIF_TSP_LIB_CODE           {'T','S','P','_'}                                               // Lib code
#define MSIF_TSP_LIBVER             {'1','3'}                                                       // LIB version
#define MSIF_TSP_BUILDNUM           {'0','1'}                                                       // Build Number
#define MSIF_TSP_CHANGELIST         {'0','0','5','5','9','0','7','6'}                               // P4 ChangeList Number

#define TSP_DRV_VERSION             /* Character String for DRV/API version             */  \
    MSIF_TAG,                       /* 'MSIF'                                           */  \
    MSIF_CLASS,                     /* '00'                                             */  \
    MSIF_CUS,                       /* 0x0000                                           */  \
    MSIF_MOD,                       /* 0x0000                                           */  \
    MSIF_CHIP,                                                                              \
    MSIF_CPU,                                                                               \
    MSIF_TSP_LIB_CODE,              /* IP__                                             */  \
    MSIF_TSP_LIBVER,                /* 0.0 ~ Z.Z                                        */  \
    MSIF_TSP_BUILDNUM,              /* 00 ~ 99                                          */  \
    MSIF_TSP_CHANGELIST,            /* CL#                                              */  \
    MSIF_OS


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
/// TSP DDI return value

/// @name TSP_Result
/// @ref TSP_Result
/// return value
/// @{
typedef enum
{
    DRVTSP_FAIL                     = 0,
    DRVTSP_OK,
    DRVTSP_INVALID_PARAM,
    DRVTSP_FUNC_ERROR,
    DRVTSP_INVALID_SECFLT,
    DRVTSP_NOT_SUPPORTED,
} TSP_Result;

/// @}

#define DOUBLE_BUFFER_ENABLE        TRUE
#define DOUBLE_BUFFER_SWITCH        FALSE

#if 0
/// TSP channel Type
typedef enum //_DrvTSP_FltType
{
    // get TS from Live stream
    E_DRVTSP_FLT_TYPE_VIDEO         = 0x00000000,                                                   ///<\n
    E_DRVTSP_FLT_TYPE_AUDIO         ,                                                               ///<\n
    E_DRVTSP_FLT_TYPE_AUDIO2        ,                                                               ///<\n
    E_DRVTSP_FLT_TYPE_PVR           ,                                                               ///<\n

    // Section Filter Group
    E_DRVTSP_FLT_TYPE_SECTION_MASK  = 0x20000000,                                                   ///<\n
    E_DRVTSP_FLT_TYPE_SECTION       ,                                                               ///<\n
    E_DRVTSP_FLT_TYPE_PCR           ,                                                               ///<\n
    E_DRVTSP_FLT_TYPE_PES           ,                                                               ///<\n
    E_DRVTSP_FLT_TYPE_PACKET        ,                                                               //[Reserved]
    E_DRVTSP_FLT_TYPE_TELETEXT      ,
    E_DRVTSP_FLT_TYPE_EMM           ,                                                               //[Reserved]
    E_DRVTSP_FLT_TYPE_ECM           ,                                                               //[Reserved]


    E_DRVTSP_FLT_SOURCE_TYPE_MASK   =  0xC0000000,
    E_DRVTSP_FLT_SOURCE_TYPE_LIVE   =  0x80000000,
    E_DRVTSP_FLT_SOURCE_TYPE_FILE   =  0x40000000,

    E_DRVTSP_FLT_TYPE_LAST_ENUM

} DrvTSP_FltType;
#endif

#define DrvTSP_FltType                  MS_U32
// get TS from Live stream
#define E_DRVTSP_FLT_TYPE_VIDEO         0x00000000                                                  ///<\n
#define E_DRVTSP_FLT_TYPE_AUDIO         0x00000001                                                  ///<\n
#define E_DRVTSP_FLT_TYPE_AUDIO2        0x00000002                                                  ///<\n
#define E_DRVTSP_FLT_TYPE_PVR           0x00000003                                                  ///<\n
#define E_DRVTSP_FLT_TYPE_VIDEO3D       0x00000008
#define E_DRVTSP_FLT_TYPE_CB            0x00000009

// Section Filter Group
#define E_DRVTSP_FLT_TYPE_SECTION_MASK  0x01000000                                                  ///<\n
#define E_DRVTSP_FLT_TYPE_SECTION       0x01000001                                                  ///<\n
#define E_DRVTSP_FLT_TYPE_PCR           0x01000002                                                  ///<\n
#define E_DRVTSP_FLT_TYPE_PES           0x01000003                                                  ///<\n
#define E_DRVTSP_FLT_TYPE_PACKET        0x01000004                                                  //[Reserved]
#define E_DRVTSP_FLT_TYPE_TELETEXT      0x01000005
#define E_DRVTSP_FLT_TYPE_EMM           0x01000006                                                  //[Reserved]
#define E_DRVTSP_FLT_TYPE_ECM           0x01000007                                                  //[Reserved]
#define E_DRVTSP_FLT_TYPE_SECTION_VER   0x01000008

#define E_DRVTSP_FLT_TYPE_LAST_ENUM     0x0100000A

#define E_DRVTSP_FLT_MASK               0xF0000000
#define E_DRVTSP_FLT_SOURCE_TYPE_MASK   0xC0000000
#define E_DRVTSP_FLT_SOURCE_TYPE_LIVE   0x80000000
#define E_DRVTSP_FLT_SOURCE_TYPE_FILE   0x40000000
#define E_DRVTSP_FLT_SOURCE_TYPE_LIVEB  E_DRVTSP_FLT_SOURCE_TYPE_FILE                               // Input from TS1 to File PID filter
#define E_DRVTSP_FLT_SOURCE_TYPE_TS1    0xC0000000

#define E_DRVTSP_FLT_SCMB_MASK          0x20000000
#define E_DRVTSP_FLT_TYPE_SCMB          0x20000000
#define E_DRVTSP_FLT_TYPE_SCMB_SHAREKEY 0x10000000

#define DrvTSP_FltMode MS_U32
#define E_DRVTSP_FLT_MODE_CONTI         0x00000000
#define E_DRVTSP_FLT_MODE_ONESHOT       0x00000001
#define E_DRVTSP_FLT_MODE_PESSCMCHK     0x00000003                 //Only for PES type checking SCMB status

// optional
#define E_DRVTSP_FLT_MODE_CRCCHK        0x00000002
#define E_DRVTSP_FLT_MODE_AUTO_ADDR     0x00000004 // auto move read point mode

//--------------------------------------------------
// Debug table
typedef enum
{
    E_DRVTSP_DEBUG_CMD_NONE,
    E_DRVTSP_DEBUG_CMD_CLEAR,
    E_DRVTSP_DEBUG_CMD_ENABLE,
    E_DRVTSP_DEBUG_CMD_DISABLE,
} DrvTSP_Debug_Cmd;

typedef enum
{
    E_DRVTSP_DEBUG_SRC_TS0,
    E_DRVTSP_DEBUG_SRC_TS1,
    E_DRVTSP_DEBUG_SRC_TS2,
    E_DRVTSP_DEBUG_SRC_FILE,
} DrvTSP_Debug_Src;

typedef enum
{
    E_DRVTSP_DEBUG_TSIF_TS0,
    E_DRVTSP_DEBUG_TSIF_TS1,
    E_DRVTSP_DEBUG_TSIF_TSCB,
} DrvTSP_Debug_Tsif;

typedef enum
{
    E_DRVTSP_DEBUG_FIFO_VIDEO,
    E_DRVTSP_DEBUG_FIFO_AUDIO,
    E_DRVTSP_DEBUG_FIFO_VIDEO3D,
    E_DRVTSP_DEBUG_FIFO_AUDIOB,
} DrvTSP_Debug_Fifo;

typedef enum
{
    E_DRVTSP_DEBUG_MODE_DIS_CONT,
    E_DRVTSP_DEBUG_MODE_DROP_CONT,
} DrvTSP_Debug_Mode;

/// TSP channel state bit flags
typedef enum //_DrvTSP_FltState
{
    E_DRVTSP_FLT_STATE_FREE           = 0x00000000,                                                 ///<\n
    E_DRVTSP_FLT_STATE_ALLOC          = 0x00000001,                                                 ///<\n
    E_DRVTSP_FLT_STATE_ENABLE         = 0x00000002,                                                 ///<\n
    E_DRVTSP_FLT_STATE_SCRAMBLED      = 0x00000004,                                                 //[TODO]
    E_DRVTSP_FLT_STATE_STREAM_AVAIL   = 0x00000008,                                                 //[TODO]
    E_DRVTSP_FLT_STATE_SCRAMBLED_ORG  = 0x00000010,
    E_DRVTSP_FLT_STATE_OVERFLOW       = 0x00010000,                                                 //[Reserved]
    E_DRVTSP_FLT_STATE_NA             = 0xFFFFFFFF,
} DrvTSP_FltState;


/// TSP record mode
typedef enum //_DrvTSP_RecMode
{
    //[TODO] rename REC_MODE to PVR_MODE

    /// Record ENG0 by @ref E_DRVTSP_FLT_TYPE_PVR
    E_DRVTSP_REC_MODE_ENG0_FLTTYPE    = 0x00000000,                                                 // TSP_PVR_CTRL_ENG(0)
    /// Record ENG1 by @ref E_DRVTSP_FLT_TYPE_PVR
    E_DRVTSP_REC_MODE_ENG1_FLTTYPE    = 0x00000001,                                                 // TSP_PVR_CTRL_ENG(1)
    /// Record ENG0 bypass PID fliter
    E_DRVTSP_REC_MODE_ENG0_BYPASS     = 0x00000002,                                                 // TSP_PVR_CTRL_ENG(0) + TSP_PVR_CTRL_BYPASS
    /// Record ENG1 bypass PID fliter
    E_DRVTSP_REC_MODE_ENG1_BYPASS     = 0x00000003,                                                 // TSP_PVR_CTRL_ENG(1) + TSP_PVR_CTRL_BYPASS

    E_DRVTSP_REC_MODE_ENG0_FLT1CA     = 0x00000004,
} DrvTSP_RecMode;

/// TSP Control Mode
typedef enum //_DrvTSP_CtrlMode
{
    /// Input From Stream Source 0
    E_DRVTSP_CTRL_MODE_TS0,
    /// Input From Stream Source 1
    E_DRVTSP_CTRL_MODE_TS1,
    /// Input From Memory
    E_DRVTSP_CTRL_MODE_MEM,
    /// Input From Memory
    E_DRVTSP_CTRL_MODE_MEM_PVR,
    /// Input From Stream Source 0, enable output to MAD
    E_DRVTSP_CTRL_MODE_TS0_AUD,
    /// Input From Stream Source 1, enable output to MAD
    E_DRVTSP_CTRL_MODE_TS1_AUD,
    /// Input From Memory, enable output to MAD
    E_DRVTSP_CTRL_MODE_MEM_AUD,
    /// Enable bounding option for PVR descrambled stream
    E_DRVTSP_CTRL_MODE_PVR_TS0,
    /// Enable Video PS enable for h264 play file
    E_DRVTSP_CTRL_MODE_VID,
    /// Enable bounding option for PVR descrambled stream, from TS1
    E_DRVTSP_CTRL_MODE_PVR_CA,
    /// Input From Stream Source 2
    E_DRVTSP_CTRL_MODE_TS2,
    /// Input From Stream Source 2, enable output to MAD
    E_DRVTSP_CTRL_MODE_TS2_AUD,
    /// Input From Stream Source 1, and output to File PID filter
    E_DRVTSP_CTRL_MODE_TS1_FILEFLT,
    /// Enable bounding option for PVR descrambled stream
    E_DRVTSP_CTRL_MODE_PVR_TS0_CA,
    /// Input From Memory, but not pass through CA
    E_DRVTSP_CTRL_MODE_MEM_NOCA,
} DrvTSP_CtrlMode;

/// TSP input pad selection
typedef enum
{
    E_DRVTSP_PAD_DEMOD                = 0x0,
    E_DRVTSP_PAD_EXT_INPUT0           = 0x1,
    E_DRVTSP_PAD_EXT_INPUT1           = 0x2,
    E_DRVTSP_PAD_EXT_INPUT2           = 0x4,
    E_DRVTSP_PAD_TSO                  = 0x8,
} DrvTSP_PadIn;

/// TSP interface
typedef enum
{
    E_DRVTSP_IF_PLAYBACK              = 0x0,                                                        // TS interface 0
    E_DRVTSP_IF_PVR0                  = 0x1,
    E_DRVTSP_IF_PVR1                  = 0x2,
    E_DRVTSP_IF_NUM,

} DrvTSP_If;

typedef struct
{
    DrvTSP_PadIn        ePad;
    MS_BOOL             bClkInv;
    MS_BOOL             bExtSync;
    MS_BOOL             bParallel;
} DrvTSP_If_Set;

typedef enum
{
    /// TSP Engine 0 Transport Stream
    E_DRVTSP_FILEIN_MODE_ENG0_TS      = 0x00000000,                                                 //TSP_TSDMA_CTRL_ENG0
    /// TSP Engine 0 Video PES Only
    E_DRVTSP_FILEIN_MODE_ENG0_VPES    = 0x00000004,                                                 //TSP_TSDMA_CTRL_VPES0
    /// TSP Engine 0 Audio PES Only
    E_DRVTSP_FILEIN_MODE_ENG0_APES    = 0x00000008,                                                 //TSP_TSDMA_CTRL_APES0
    /// TSP Engine 0 Audio2 PES Only
    E_DRVTSP_FILEIN_MODE_ENG0_A2PES   = 0x00000010,                                                 //TSP_TSDMA_CTRL_A2PES0
    /// TSP Engine 0 Video3D PES Only
    E_DRVTSP_FILEIN_MODE_ENG0_V3DPES  = 0x00000020,                                                 //TSP_TSDMA_CTRL_V3DPES0
} DrvTSP_FileinMode;


typedef enum
{
    /// Command Queue is Idle
    E_DRVTSP_FILEIN_STATE_IDLE        = 0000000000,
    /// Command Queue is Busy
    E_DRVTSP_FILEIN_STATE_BUSY        = 0x00000001,
    /// Command Queue is Paused.
    E_DRVTSP_FILEIN_STATE_PAUSE       = 0x00000002,
} DrvTSP_FileinState;

#if 0
/// TSP notification event
typedef enum //_DrvTSP_Event
{
    E_DRVTSP_EVENT_DATA_INIT          = 0x00000000,
    /// Section Data Ready
    E_DRVTSP_EVENT_DATA_READY         = 0x00000001,
    /// Section Buffer Overflow
    E_DRVTSP_EVENT_BUF_OVERFLOW       = 0x00000002,
    /// PVR Buffer is Full
    E_DRVTSP_EVENT_PVRBUF_FULL        = 0x00000010,
    /// PVR Double Buffer Overflow
    E_DRVTSP_EVENT_PVRBUF_OVERFLOW    = 0x00000020,


    /// TSP self task callback // optional --> default is CB by poll
    E_DRVTSP_EVENT_CB_MASK            = 0x80000000,
    E_DRVTSP_EVENT_CB_POLL            = 0x00000000,
    E_DRVTSP_EVENT_CB_SELF            = 0x80000000,
} DrvTSP_Event;
#endif

#define DrvTSP_Event                    MS_U32
#define E_DRVTSP_EVENT_DATA_INIT        0x00000000
/// Section Data Ready
#define E_DRVTSP_EVENT_DATA_READY       0x00000001
/// Section Buffer Overflow
#define E_DRVTSP_EVENT_BUF_OVERFLOW     0x00000002
/// PVR Buffer is Full
#define E_DRVTSP_EVENT_PVRBUF_FULL      0x00000010
/// PVR Double Buffer Overflow
#define E_DRVTSP_EVENT_PVRBUF_OVERFLOW  0x00000020
/// Channel Browser Buffer is Full
#define E_DRVTSP_EVENT_CBBUF_FULL       0x00000040
#define E_DRVTSP_EVENT_CBBUF_OVERFLOW   0x00000080


/// TSP self task callback // optional --> default is CB by poll
#define E_DRVTSP_EVENT_CB_MASK          0x80000000
#define E_DRVTSP_EVENT_CB_POLL          0x00000000
#define E_DRVTSP_EVENT_CB_SELF          0x80000000

/// TSP file in Packet mode
typedef enum //_DrvTSP_PacketMode
{
    E_DRVTSP_PKTMODE_188              = 0x00000000,
    E_DRVTSP_PKTMODE_192              = 0x00000001,
    E_DRVTSP_PKTMODE_204              = 0x00000002,
    E_DRVTSP_PKTMODE_130              = 0x00000003,    // RVU
    E_DRVTSP_PKTMODE_134              = 0x00000004,    // RVU with timestamp
} DrvTSP_PacketMode;

/// TSP notification event message
typedef struct //_DrvTSP_Msg
{
    /// Union data type of message
    union
    {
        /// FltInfo message
        ///   - Byte[0] : Section filter id
        ///   - Byte[1] : TSP id
        MS_U32                          FltInfo;
        /// PvrBufId
        ///   - Byte[0] : PVR buffer id
        MS_U32                          PvrBufId;

        /// Pvr1BufId;
        ///   - Byte[0] : CB buffer id
        MS_U32                          Pvr1BufId;

    };

} DrvTSP_Msg;

typedef enum //_DrvTSP_DbgLevel
{
    E_DRVTSP_DBG_Release = 0,
    E_DRVTSP_DBG_L1, // display error msg
    E_DRVTSP_DBG_L2, // display error msg and enter while(1)
} DrvTSP_DbgLevel;

// legacy
typedef enum{
    E_DRVTSP_SCMB_NONE                = 0x00000000,
    E_DRVTSP_SCMB_TS                  = 0x00000001,
    E_DRVTSP_SCMB_PES                 = 0x00000002,
    E_DRVTSP_SCMB_TS_PES              = (E_DRVTSP_SCMB_TS| E_DRVTSP_SCMB_PES),
} DrvTSP_Scmb_Level;

/// @name DrvTSP_Msg
/// Macro definitions for manipulating DrvTSP_Msg
/// @{
#define MSG_FLTINFO_SEC_ID_MASK         0x000000FF
#define MSG_FLTINFO_SEC_ID_SHFT         0
#define MSG_FLTINFO_ENG_ID_MASK         0x0000FF00
#define MSG_FLTINFO_ENG_ID_SHFT         8
#define MSG_PVRBUF_ID_MASK              0x000000FF
#define MSG_PVRBUF_ID_SHFT              0
#define MSG_PVRBUF_ID_NULL              0xFF
#define MSG_CBBUF_ID_MASK               0x000000FF
#define MSG_CBBUF_ID_SHFT               0
#define MSG_CBBUF_ID_NULL               0xFF

/// @}

typedef enum
{
    E_DRVTSP_CAP_PID_FILTER_NUM             = 0,        // Get filter number
    E_DRVTSP_CAP_SEC_FILTER_NUM             = 1,
    E_DRVTSP_CAP_SEC_BUF_NUM                = 2,

    E_DRVTSP_CAP_PVR_ENG_NUM                = 3,
    E_DRVTSP_CAP_PVR_FILTER_NUM             = 4,        // Get pvr filter number
    E_DRVTSP_CAP_PVR1_FILTER_NUM            = 5,        // Get pvr1 filter number

    E_DRVTSP_CAP_MMFI_AUDIO_FILTER_NUM      = 6,        // Get MM file in audio path filter number
    E_DRVTSP_CAP_MMFI_V3D_FILTER_NUM        = 7,        // Get MM file in video 3D path filter number

    E_DRVTSP_CAP_TSIF_NUM                   = 8,
    E_DRVTSP_CAP_DEMOD_NUM                  = 9,
    E_DRVTSP_CAP_TS_PAD_NUM                 = 10,
    E_DRVTSP_CAP_VQ_NUM                     = 11,

    E_DRVTSP_CAP_CA_FLT_NUM                 = 12,            // Get dscmb filter number
    E_DRVTSP_CAP_CA_KEY_NUM                 = 13,

    E_DRVTSP_CAP_FW_ALIGN                   = 14,
    E_DRVTSP_CAP_VQ_ALIGN                   = 15,
    E_DRVTSP_CAP_VQ_PITCH                   = 16,
    E_DRVTSP_CAP_SEC_BUF_ALIGN              = 17,

    E_DRVTSP_CAP_PVR_ALIGN                  = 18,
    E_DRVTSP_CAP_PVRCA_PATH_NUM             = 19,
    E_DRVTSP_CAP_SHAREKEY_FLT_RANGE         = 20,
    E_DRVTSP_CAP_PVRCA0_FLT_RANGE           = 21,
    E_DRVTSP_CAP_PVRCA1_FLT_RANGE           = 22,
    E_DRVTSP_CAP_PVRCA2_FLT_RANGE           = 23,
    E_DRVTSP_CAP_SHAREKEY_FLT1_RANGE        = 24,
    E_DRVTSP_CAP_SHAREKEY_FLT2_RANGE        = 25,

    E_DRVTSP_CAP_HW_TYPE                    = 26,

    E_DRVTSP_CAP_RESOURCE_SIZE              = 27,       // Get the data structure size of private resource (share resource)

    E_DRVTSP_CAP_VFIFO_NUM                  = 28,       // Get VFIFO support number
    E_DRVTSP_CAP_AFIFO_NUM                  = 29,       // Get AFIFO support number

    E_DRVTSP_CAP_NULL,
} DrvTSP_Cap;

typedef enum
{
    E_DRVTSP_HW_STATUS = 0,
    E_DRVTSP_HW_INIT,
    E_DRVTSP_HW_ALIVE,
    E_DRVTSP_HW_DEALIVE,
} DrvTSP_HW_Status;

typedef enum
{
    E_DRVTSP_SW_INIT = 0,
    E_DRVTSP_SW_INIT_FAIL,
    E_DRVTSP_SW_SUSPEND,
    E_DRVTSP_SW_RESUME,
    E_DRVTSP_SW_POWEROFF,
    E_DRVTSP_SW_CLOSE,
    E_DRVTSP_SW_EXIT,
} DrvTSP_SW_Status;

// TSP event define
#define TSP_TASK_EVENT_SECTION_SELF     0x00000001
#define TSP_TASK_EVENT_SECTION_POLL     0x00000002
#define TSP_TASK_EVENT_PVR0_RDY_SELF    0x00000004
#define TSP_TASK_EVENT_PVR1_RDY_SELF    0x00000008
#define TSP_TASK_EVENT_PVR0_RDY_POLL    0x00000010
#define TSP_TASK_EVENT_PVR1_RDY_POLL    0x00000020
#define TSP_TASK_EVENT_FLT_FREE         0x00000040
#define TSP_TASK_EVENT_CBPVR0_RDY_SELF  0x00000080
#define TSP_TASK_EVENT_CBPVR0_RDY_POLL  0x00000100
#define TSP_TASK_EVENT_FWMSG            0x00000200
#define TSP_TASK_EVENT_GROUP_SELF       (   TSP_TASK_EVENT_SECTION_SELF     |   \
                                            TSP_TASK_EVENT_PVR0_RDY_SELF    |   \
                                            TSP_TASK_EVENT_PVR1_RDY_SELF    )

#define TSP_TASK_EVENT_GROUP_POLL       (   TSP_TASK_EVENT_SECTION_POLL     |   \
                                            TSP_TASK_EVENT_PVR0_RDY_POLL    |   \
                                            TSP_TASK_EVENT_PVR1_RDY_POLL    )

/// TSP notification function
typedef void (*P_DrvTSP_EvtCallback)(DrvTSP_Event eEvent, DrvTSP_Msg *pMsg);


////////////////////////////////////////////////////////////////////////////////
// include utopia v2  header files here
////////////////////////////////////////////////////////////////////////////////
#ifdef UTOPIA_20
#include "drvTSP_v2.h"
#endif

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

// General API
TSP_Result MDrv_TSP_InitLibResource(void *pu32ResMemAddr);
TSP_Result MDrv_TSP_Init(MS_U32 u32FWAddr, MS_U32 u32FWSize);                                       // Set FW address and size
TSP_Result MDrv_TSP_Reinit(MS_BOOL bHK); //for utopia 2.0
TSP_Result MDrv_TSP_PowerOff(void);
TSP_Result MDrv_TSP_Exit(void);
TSP_Result MDrv_TSP_Suspend(void);
TSP_Result MDrv_TSP_Resume(MS_U32 u32FWAddr, MS_U32 u32FWSize);
TSP_Result MDrv_TSP_Alive(MS_U32 u32EngId);
TSP_Result MDrv_TSP_Reset(void);
TSP_Result MDrv_TSP_HW_Lock_Release(void);
TSP_Result MDrv_TSP_RemoveDupAVPkt(MS_BOOL bEnable);
TSP_Result MDrv_TSP_RemoveDupAVFifoPkt(DrvTSP_FltType flttype, MS_BOOL bEnable);
TSP_Result MDrv_TSP_FLT_LiveSrcSwitch(DrvTSP_FltType eFltSrcType);
TSP_Result MDrv_TSP_AU_BD_Mode_Enable(MS_BOOL bEnable);

// Misc API
TSP_Result MDrv_TSP_SetFwDBGParam(MS_PHYADDR phyAddr, MS_U32 u32Size, MS_U32 u32DbgWord);           // for TSP f/w debug
TSP_Result MDrv_TSP_SetOperateMode(MS_U32 u32EngId, DrvTSP_CtrlMode eCtrlMode);                     // Set TSP internal operate
TSP_Result MDrv_TSP_SelPad(MS_U32 u32EngId, DrvTSP_If eIf, DrvTSP_If_Set* pIfSet);                  // Set TSP input pad and ts0/ts1
TSP_Result MDrv_TSP_AVFifo_Reset(DrvTSP_FltType eFilterType, MS_BOOL bFlush);
TSP_Result MDrv_TSP_AVFifo_Status(DrvTSP_FltType eFilterType, MS_U32 *u32FifoLevel);
TSP_Result MDrv_TSP_Parl_BitOrderSwap(MS_U32 u32EngId, DrvTSP_If eIf, MS_BOOL bInvert);
TSP_Result MDrv_TSP_Get_FW_VER(MS_U32* u32FWVer);
TSP_Result MDrv_TSP_Get_Intr_Count(MS_U32* pu32Count);
TSP_Result MDrv_TSP_Scmb_Status(MS_U32 u32EngId, DrvTSP_Scmb_Level* pScmbLevel);

TSP_Result MDrv_TSP_GetLastErr(void);
TSP_Result MDrv_TSP_Proc(MS_U32 u32EngId, MS_U32 u32FltId, TSP_Result* pRet, DrvTSP_Event* pEvt);   // for non-OS TSP scheduling
TSP_Result MDrv_TSP_GetSTC(MS_U32 u32EngId, MS_U32 *pu32STC_32, MS_U32 *pu32STC);
TSP_Result MDrv_TSP_SetSTC(MS_U32 u32EngId, MS_U32 u32STC_32, MS_U32 u32STC);
TSP_Result MDrv_TSP_GetPCR(MS_U32 u32EngId, MS_U32 *pu32Pcr_32, MS_U32 *pu32Pcr);
TSP_Result MDrv_TSP_Flt_GetState(MS_U32 u32EngId, MS_U32 u32FltId, DrvTSP_FltState *peState);       // Get PIDFlt and SecFlt state

#ifdef STC64_SUPPORT
TSP_Result MDrv_TSP_STC64_Mode_Enable(MS_BOOL bEnable);
#endif
TSP_Result MDrv_TSP_STCClk_Adjust(MS_U32 u32EngId, MS_BOOL bUpClk, MS_U32 u32Percentage);


// NDS --> ECM
TSP_Result MDrv_TSP_SecFlt_SetEcmIdx(MS_U32 u32EngId, MS_U32 u32SecFltId, MS_U32 u32EcmIdx);

// PIDFlt API
TSP_Result MDrv_TSP_PidFlt_Alloc(MS_U32 u32EngId, DrvTSP_FltType eFilterType, MS_U32 *pu32PidFltId);
TSP_Result MDrv_TSP_PidFlt_Free(MS_U32 u32EngId, MS_U32 u32PidFltId);
TSP_Result MDrv_TSP_PidFlt_SetPid(MS_U32 u32EngId, MS_U32 u32PidFltId, MS_U32 u32PID);
TSP_Result MDrv_TSP_PidFlt_GetPid(MS_U32 u32EngId, MS_U32 u32PidFltId, MS_U32* pu32PID);
TSP_Result MDrv_TSP_PidFlt_SelSecFlt(MS_U32 u32EngId, MS_U32 u32PidFltId, MS_U32 u32SecFltId);
TSP_Result MDrv_TSP_PidFlt_Enable(MS_U32 u32EngId, MS_U32 u32PidFltId, MS_BOOL bEnable);
TSP_Result MDrv_TSP_PidFlt_GetState(MS_U32 u32EngId, MS_U32 u32PidFltId, DrvTSP_FltState *peState);
TSP_Result MDrv_TSP_PidFlt_PVREnable(MS_U32 u32EngId, MS_U32 u32PidFltId); //only for debug
TSP_Result MDrv_TSP_PidFlt_ChangeSource(MS_U32 u32EngId, MS_U32 u32PidFltId, DrvTSP_FltType eFilterType);
TSP_Result MDrv_TSP_PidFlt_GetScmbSts(DrvTSP_FltType FltSrc, MS_U32 u32FltGroupId, MS_U32 PidFltId, MS_U32 *pu32ScmbSts);


// SecFlt API
TSP_Result MDrv_TSP_SecFlt_Alloc(MS_U32 u32EngId, MS_U32 *pu32SecFltId);
TSP_Result MDrv_TSP_SecFlt_Free(MS_U32 u32EngId, MS_U32 u32SecFltId);
TSP_Result MDrv_TSP_SecFlt_SetMode(MS_U32 u32EngId, MS_U32 u32SecFltId, DrvTSP_FltMode eSecFltMode);
TSP_Result MDrv_TSP_SecFlt_SetPattern(MS_U32 u32EngId, MS_U32 u32SecFltId, MS_U8 *pu8Match, MS_U8 *pu8Mask, MS_U8 *pu8NotMask);
TSP_Result MDrv_TSP_SecFlt_ResetBuffer(MS_U32 u32EngId, MS_U32 u32SecFltId);
TSP_Result MDrv_TSP_SecFlt_SetBuffer(MS_U32 u32EngId, MS_U32 u32SecFltId, MS_PHYADDR u32StartAddr, MS_U32 u32BufSize);
TSP_Result MDrv_TSP_SecFlt_SetReqCount(MS_U32 u32EngId, MS_U32 u32SecFltId, MS_U32 u32ReqCount);
TSP_Result MDrv_TSP_SecFlt_GetBufStart(MS_U32 u32EngId, MS_U32 u32SecFltId, MS_PHYADDR *pu32BufStart);
TSP_Result MDrv_TSP_SecFlt_GetBufSize(MS_U32 u32EngId, MS_U32 u32SecFltId, MS_U32 *pu32BufSize);
TSP_Result MDrv_TSP_SecFlt_GetReadAddr(MS_U32 u32EngId, MS_U32 u32SecFltId, MS_PHYADDR *pu32ReadAddr);
TSP_Result MDrv_TSP_SecFlt_GetWriteAddr(MS_U32 u32EngId, MS_U32 u32SecFltId, MS_PHYADDR *pu32WriteAddr);

TSP_Result MDrv_TSP_SecFlt_SetReadAddr(MS_U32 u32EngId, MS_U32 u32SecFltId, MS_PHYADDR u32ReadAddr);
TSP_Result MDrv_TSP_SecFlt_Notify(MS_U32 u32EngId, MS_U32 u32SecFltId, DrvTSP_Event eEvents, P_DrvTSP_EvtCallback pfCallback);
TSP_Result MDrv_TSP_SecFlt_GetState(MS_U32 u32EngId, MS_U32 u32SecFltId, DrvTSP_FltState *peState);

// PVR API
TSP_Result MDrv_TSP_PVR_SetBuffer(MS_PHYADDR u32BufStart0, MS_PHYADDR u32BufStart1, MS_U32 u32BufSize0, MS_U32 u32BufSize1);
TSP_Result MDrv_TSP_PVR_Start(DrvTSP_RecMode eRecMode, MS_BOOL bStart);
TSP_Result MDrv_TSP_PVR_GetWriteAddr(MS_PHYADDR *pu32WriteAddr);
TSP_Result MDrv_TSP_PVR_Notify(DrvTSP_Event eEvents, P_DrvTSP_EvtCallback pfCallback);
TSP_Result MDrv_TSP_PVR_SetPacketMode(MS_BOOL bSet);
TSP_Result MDrv_TSP_PVR_TimeStampSetRecordStamp(MS_U32 u32Stamp);
TSP_Result MDrv_TSP_PVR_TimeStampGetRecordStamp(MS_U32* u32Stamp);
TSP_Result MDrv_TSP_PVR_TimeStampSetPlaybackStamp(MS_U32 u32Stamp);
TSP_Result MDrv_TSP_PVR_TimeStampGetPlaybackStamp(MS_U32* u32Stamp);
TSP_Result MDrv_TSP_PVR_TimeStamp(MS_BOOL bEnable);
TSP_Result MDrv_TSP_PVR_Filein_Enable(MS_BOOL bBypassHD, MS_BOOL bEnable); //only for debug

//PVRCA API
TSP_Result MDrv_TSP_PVR_PidFlt_Reserved(MS_U32 Pid, MS_U8* pu8DmxId, MS_BOOL bReserved);
TSP_Result MDrv_TSP_PVR_FLT1_StartRec(MS_BOOL bEnable);
TSP_Result MDrv_TSP_PVRCA_Close(void);


// Channel Browser API
TSP_Result MDrv_TSP_PVR_Eng_SetBuffer(MS_U8 u8PVRId, MS_PHYADDR u32BufStart0, MS_PHYADDR u32BufStart1, MS_U32 u32BufSize0, MS_U32 u32BufSize1);
TSP_Result MDrv_TSP_PVR_Eng_Start(MS_U8 u8PVRId, DrvTSP_RecMode eRecMode, MS_BOOL bStart);
TSP_Result MDrv_TSP_PVR_Eng_GetWriteAddr(MS_U8 u8PVRId, MS_PHYADDR *pu32WriteAddr);
TSP_Result MDrv_TSP_PVR_Eng_Notify(MS_U8 u8PVRId, DrvTSP_Event eEvents, P_DrvTSP_EvtCallback pfCallback);
TSP_Result MDrv_TSP_PVR_Eng_SetPacketMode(MS_U8 u8PVRId, MS_BOOL bSet);
TSP_Result MDrv_TSP_PVR_Eng_TimeStampSetRecordStamp(MS_U8 u8PVRId, MS_U32 u32Stamp);
TSP_Result MDrv_TSP_PVR_Eng_TimeStampGetRecordStamp(MS_U8 u8PVRId,MS_U32* u32Stamp);
TSP_Result MDrv_TSP_PVR_Eng_SetPlaybackStampClk(MS_U32 u32EngId, MS_U32 u32Clk);
TSP_Result MDrv_TSP_PVR_Eng_SetRecordStampClk(MS_U32 u32PvrId, MS_U32 u32Clk);
// File API
TSP_Result MDrv_TSP_File_SetAddr(MS_PHYADDR u32StreamAddr);
TSP_Result MDrv_TSP_File_SetSize(MS_U32 u32StreamSize);
TSP_Result MDrv_TSP_File_Start(DrvTSP_FileinMode eFileinMode);
TSP_Result MDrv_TSP_File_Stop(void);
TSP_Result MDrv_TSP_File_Pause(void);
TSP_Result MDrv_TSP_File_Resume(void);
TSP_Result MDrv_TSP_File_GetState(DrvTSP_FileinState *peFileinState);
TSP_Result MDrv_TSP_File_SetRate(MS_U32 u32Div2);
TSP_Result MDrv_TSP_File_SetPacketMode(DrvTSP_PacketMode PKT_Mode);
TSP_Result MDrv_TSP_File_CMDQ_GetSlot(MS_U32 *pu32EmptySlot);
TSP_Result MDrv_TSP_File_CMDQ_Reset(void);
TSP_Result MDrv_TSP_CmdQFifo_Status(MS_U8 *pu8FifoLevel);
TSP_Result MDrv_TSP_File_192BlockScheme_En(MS_BOOL bEnable);
TSP_Result MDrv_TSP_File_PS_Path_Enable(DrvTSP_FileinMode eFileinMode);
TSP_Result MDrv_TSP_File_GetReadAddr(MS_PHYADDR *pu32ReadAddr);

// Capacity query
TSP_Result MDrv_TSP_GetCap(DrvTSP_Cap eCap, void* pOutput);
TSP_Result MDrv_TSP_GetStatus(DrvTSP_HW_Status *HW_Status, DrvTSP_SW_Status *SW_Status);
TSP_Result MDrv_TSP_GetLibVer(const MSIF_Version **ppVersion);
TSP_Result MDrv_TSP_SetDbgLevel(DrvTSP_DbgLevel DbgLevel);
TSP_Result MDrv_TSP_GetTSIFStatus(DrvTSP_If eIf, DrvTSP_If_Set* pIfSet);
TSP_Result MDrv_TSP_GetPesScmbSts(MS_U8 u8FltId, MS_U8 *pu8status);
TSP_Result MDrv_TSP_GetTsScmbSts(MS_U8 u8FltId, MS_U8 *pu8status);


//-------------------------------------------------------------------------------------------------
//  OBSOLETE
//-------------------------------------------------------------------------------------------------
TSP_Result MDrv_TSP_Flt_SetOwner(MS_U32 u32EngId, MS_U32 u32FltIdStart, MS_U32 u32FltIdEnd, MS_BOOL bOwner); // Set/Get the ranges of filters used, which is for AEON/MHEG5 share TSP filters resource.
TSP_Result MDrv_TSP_PidFlt_ChkOwner(MS_U32 u32EngId, MS_U32 u32PidFltId);
TSP_Result MDrv_TSP_SetHK(MS_BOOL bIsHK);
TSP_Result MDrv_TSP_IsAccess(MS_U32 u32Try);
TSP_Result MDrv_TSP_UnlockAccess(void);

TSP_Result MDrv_TSP_TTX_SecFlt_GetWriteAddr(MS_U32 u32EngId, MS_U32 u32SecFltId, MS_PHYADDR *pu32WriteAddr); // special case for TTX
TSP_Result MDrv_TSP_GetDbgPortInfo(MS_U32 u32DbgSel,MS_U32* u32DbgInfo);

TSP_Result MDrv_TSP_BurstLen(MS_U32 u32Len);
TSP_Result MDrv_TSP_GetFileInTimeStamp(MS_U32* u32TSLen);
TSP_Result MDrv_TSP_SetAVPause(MS_BOOL bSet);
#if 0
TSP_Result MDrv_TSP_ResetFileinTimestamp(void);
#endif

//--VQ , MOBF --------------
TSP_Result MDrv_TSP_SetVQueBuf(MS_PHYADDR u32VQBaseAddr, MS_U32 u32VQBufLen);
TSP_Result MDrv_TSP_VQueEnable(MS_BOOL bEnable);
TSP_Result MDrv_TSP_VQueReset(void);
TSP_Result MDrv_TSP_VQueue_OverflowInt_En(MS_BOOL bEnable);
TSP_Result MDrv_TSP_Set_VQ_Threshold(MS_U8 u8req_len);
TSP_Result MDrv_TSP_Get_VQStatus(MS_U32* pu32Status);

TSP_Result MDrv_TSP_Set_MOBF_PVRKey(MS_U32 u32Key0, MS_U32 u32Key1);
TSP_Result MDrv_TSP_Set_MOBF_FileinKey(MS_U32 u32Key);
TSP_Result MDrv_TSP_MOBF_PVR_Enable(MS_BOOL benable);
TSP_Result MDrv_TSP_MOBF_FileIn_Enable(MS_BOOL benable);

void MDrv_TSP_WriteProtect_Enable(MS_BOOL bEnable, MS_U32* pu32StartAddr, MS_U32* pu32EndAddr);
TSP_Result MDrv_TSP_TSIF_Enable(DrvTSP_If tsif, MS_BOOL bEnable);
TSP_Result MDrv_TSP_ReadDropPktCnt(MS_U16* pu16ADropCnt, MS_U16* pu16VDropCnt);

//---  Common Interface for TSP config and Api commands ------------//
TSP_Result MDrv_TSP_CMD_Run(MS_U32 u32Cmd, MS_U32 u32Config0, MS_U32 u32Config1 ,void *pData);

TSP_Result MDrv_TSP_SetFwDataAddr(MS_U32 u32DataAddr, MS_U32 u32Size);

TSP_Result MDrv_TSP_STC_UpdateCtrl(MS_U8 u8Eng, MS_BOOL bEnable);

// --Debug table --------------
TSP_Result MDrv_TSP_Get_DisContiCnt(DrvTSP_Debug_Cmd TspCmd, DrvTSP_Debug_Src TspSrc, DrvTSP_Debug_Fifo TspFifo, MS_U32 *pu32Cnt);
TSP_Result MDrv_TSP_Get_DropPktCnt(DrvTSP_Debug_Cmd TspCmd, DrvTSP_Debug_Src TspSrc, DrvTSP_Debug_Fifo TspFifo, MS_U32 *pu32Cnt);
TSP_Result MDrv_TSP_Get_LockPktCnt(DrvTSP_Debug_Cmd TspCmd, DrvTSP_Debug_Tsif TspTsif, MS_U32 *pu32Cnt);
TSP_Result MDrv_TSP_Get_AVPktCnt(DrvTSP_Debug_Cmd TspCmd, DrvTSP_Debug_Fifo TspFifo, MS_U32 *pu32Cnt);

#ifdef __cplusplus
} // closing brace for extern "C"
#endif


#endif // _DRV_TSP_H_
