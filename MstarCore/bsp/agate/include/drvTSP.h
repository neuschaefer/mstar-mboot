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



#ifdef __cplusplus
extern "C"
{
#endif

#define TSP_VER_1_0                     0x0100
#define TSP_VER_2_0                     0x0200
#define TSP_VER_3_0                     0x0300

#define TSP_VERSION                     TSP_VER_3_0


//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------

#define DRVTSP_FILTER_DEPTH         16                                                              // TSP_FILTER_DEPTH

/// TSP byte address alignment unit
#define DRVTSP_ALIGN_UNIT           8

/// TSP byte address alignment macro
#define DRVTSP_ALIGN(_x)            ALIGN_8((MS_U32)_x)

#define DSCMB_FLT_START_ID					16
#define DSCMB_FLT_END_ID					31
#define DSCMB_FLT_NUM						16

#define DSCMB1_FLT_START_ID					48
#define DSCMB1_FLT_END_ID					63
#define DSCMB1_FLT_NUM						16

#define DSCMB_FLT_SHAREKEY_START_ID			0
#define DSCMB_FLT_SHAREKEY_END_ID			15
#define DSCMB_FLT_SHAREKEY_NUM				16

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
/// Transport stream null PID
#define DRVTSP_PID_NULL             0x1FFF
#define MSIF_TSP_LIB_CODE           {'T','S','P','3'}                                               // Lib code
#define MSIF_TSP_LIBVER             {'1','2'}                                                       // LIB version
#define MSIF_TSP_BUILDNUM           {'2','7'}                                                       // Build Number
#define MSIF_TSP_CHANGELIST         {'0','0','6','0','0','7','4','0'}                               // P4 ChangeList Number

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
#define E_DRVTSP_FLT_TYPE_PVR1          0x00000004
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

#define E_DRVTSP_FLT_TYPE_LAST_ENUM     0x0100000A

#define E_DRVTSP_FLT_MASK               0xF0E00000
#define E_DRVTSP_FLT_SOURCE_TYPE_MASK   0xC0E00000
#define E_DRVTSP_FLT_SOURCE_TYPE_LIVE   0x80000000
#define E_DRVTSP_FLT_SOURCE_TYPE_FILE   0x40000000
#define E_DRVTSP_FLT_SOURCE_TYPE_TS1    0x00800000
#define E_DRVTSP_FLT_SOURCE_TYPE_TS2    0x00400000
#define E_DRVTSP_FLT_SOURCE_TYPE_TSCB   0x00200000

#define E_DRVTSP_FLT_SCMB_MASK          0x30000000
#define E_DRVTSP_FLT_TYPE_SCMB          0x20000000
#define E_DRVTSP_FLT_TYPE_SCMB_SHAREKEY 0x10000000

#define DrvTSP_FltMode MS_U32
#define E_DRVTSP_FLT_MODE_CONTI         0x00000000
#define E_DRVTSP_FLT_MODE_ONESHOT       0x00000001

// optional
#define E_DRVTSP_FLT_MODE_CRCCHK        0x00000002
#define E_DRVTSP_FLT_MODE_AUTO_ADDR     0x00000004 // auto move read point mode

#define DrvTSP_PKTDMXSrcType            MS_U32
#define E_DRVTSP_PKTSRC_DEMUX0          0x00000001
#define E_DRVTSP_PKTSRC_DEMUXFILE       0x00000002
#define E_DRVTSP_PKTSRC_DEMUX1          0x00000003
#define E_DRVTSP_PKTSRC_DEMUX2          0x00000004
#define E_DRVTSP_PKTSRC_DEMUXMMFI0      0x00000006
#define E_DRVTSP_PKTSRC_DEMUXMMFI1      0x00000007

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
    E_DRVTSP_REC_MODE_ENG1_FLTTYPE    = 0x00010000,                                                 // TSP_PVR_CTRL_ENG(1)
    /// Record ENG0 bypass PID fliter
    E_DRVTSP_REC_MODE_ENG0_BYPASS     = 0x00000002,                                                 // TSP_PVR_CTRL_ENG(0) + TSP_PVR_CTRL_BYPASS
    /// Record ENG1 bypass PID fliter
    E_DRVTSP_REC_MODE_ENG1_BYPASS     = 0x00010002,                                                 // TSP_PVR_CTRL_ENG(1) + TSP_PVR_CTRL_BYPASS

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
    /// Enable bounding option for PVR descrambled stream, from TS0
    E_DRVTSP_CTRL_MODE_PVR_CA,
    /// Input From Stream Source 2
    E_DRVTSP_CTRL_MODE_TS2,
    /// Input From Stream Source 2, enable output to MAD
    E_DRVTSP_CTRL_MODE_TS2_AUD,
    /// Input From Stream Source 1, and not descramble stream
    E_DRVTSP_CTRL_MODE_TS1_NOCA,
    /// Enable bounding option for PVR descrambled stream
    E_DRVTSP_CTRL_MODE_PVR_TS0_CA,
   /// Input From Memory, but not pass through CA
    E_DRVTSP_CTRL_MODE_MEM_NOCA,
    /// Input From Stream Source 3
    E_DRVTSP_CTRL_MODE_TS3,
    /// Input From Stream Source 3, enable output to MAD
    E_DRVTSP_CTRL_MODE_TS3_AUD,
    /// Enable bounding option for PVR descrambled stream, from TS1
    E_DRVTSP_CTRL_MODE_PVR_CA1,
} DrvTSP_CtrlMode;

/// TSP input pad selection
typedef enum
{
    E_DRVTSP_PAD_EXT_INPUT0           = 0x0,
    E_DRVTSP_PAD_EXT_INPUT1           = 0x1,
    E_DRVTSP_PAD_EXT_INPUT2           = 0x2,
    E_DRVTSP_PAD_TSO                  = 0x5,
    E_DRVTSP_PAD_EXT_INPUT3           = 0x6,
    E_DRVTSP_PAD_DEMOD                = 0x7,
} DrvTSP_PadIn;

/// TSP interface
typedef enum
{
    E_DRVTSP_IF_TS0                   = 0x0,        //TSIF0
    E_DRVTSP_IF_TS1                   = 0x1,        //TSIF1
    E_DRVTSP_IF_TS2                   = 0x2,        //TSIF2
    E_DRVTSP_IF_TS3                   = 0x3,        //TSIF3
    E_DRVTSP_IF_INVALID               = 0xFFFFFFFF,
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
///PVR2 Buffer is Full
#define E_DRVTSP_EVENT_PVR2BUF_FULL     0x00000100
#define E_DRVTSP_EVENT_PVR2BUF_OVERFLOW 0x00000200


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
        ///   - Byte[1] : PVR engine id
        MS_U32                          PvrBufId;
    };

} DrvTSP_Msg;

typedef enum //_DrvTSP_DbgLevel
{
    E_DRVTSP_DBG_Release = 0,
    E_DRVTSP_DBG_L1, // display error msg
    E_DRVTSP_DBG_L2, // display error msg and enter while(1)
} DrvTSP_DbgLevel;

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
#define MSG_PVR_ID_MASK                 0x0000FF00
#define MSG_PVR_ID_SHFT                 8

/// @}

typedef enum
{
    E_DRVTSP_CAP_PID_FILTER_NUM = 0,    // Get filter number
    E_DRVTSP_CAP_SEC_FILTER_NUM,
    E_DRVTSP_CAP_SEC_BUF_NUM,

    E_DRVTSP_CAP_PVR_ENG_NUM,
    E_DRVTSP_CAP_PVR_FILTER_NUM,             // Get pvr filter number
    E_DRVTSP_CAP_PVR1_FILTER_NUM,            // Get pvr1 filter number

    E_DRVTSP_CAP_MMFI0_FILTER_NUM,           // Get MMFI0 filter number
    E_DRVTSP_CAP_MMFI1_FILTER_NUM,           // Get MMFI1 filter number

    E_DRVTSP_CAP_TSIF_NUM,
    E_DRVTSP_CAP_DEMOD_NUM,
    E_DRVTSP_CAP_TS_PAD_NUM,
    E_DRVTSP_CAP_VQ_NUM,

    E_DRVTSP_CAP_CA_FLT_NUM,            // Get dscmb filter number
    E_DRVTSP_CAP_CA_KEY_NUM,

    E_DRVTSP_CAP_FW_ALIGN = 0x0100,
    E_DRVTSP_CAP_VQ_ALIGN,
    E_DRVTSP_CAP_VQ_PITCH,
    E_DRVTSP_CAP_SEC_BUF_ALIGN,

    E_DRVTSP_CAP_PVR_ALIGN,

    E_DRVTSP_CAP_PVRCA_PATH_NUM,

    E_DRVTSP_CAP_NULL     = 0xFFFF
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

// legacy
typedef enum{
    E_DRVTSP_SCMB_NONE                = 0x00000000,
    E_DRVTSP_SCMB_TS                  = 0x00000001,
    E_DRVTSP_SCMB_PES                 = 0x00000002,
    E_DRVTSP_SCMB_TS_PES              = (E_DRVTSP_SCMB_TS| E_DRVTSP_SCMB_PES),
} DrvTSP_Scmb_Level;

// TSP event define

#define TSP_TASK_EVENT_SECTION_SELF         0x00000001
#define TSP_TASK_EVENT_SECTION_POLL         0x00000002
#define TSP_TASK_EVENT_PVR0_RDY_SELF        0x00000004 //PVR1 buffer0
#define TSP_TASK_EVENT_PVR1_RDY_SELF        0x00000008 //PVR1 buffer0
#define TSP_TASK_EVENT_PVR0_RDY_POLL        0x00000010 //PVR1 buffer0
#define TSP_TASK_EVENT_PVR1_RDY_POLL        0x00000020 //PVR1 buffer0
#define TSP_TASK_EVENT_FLT_FREE             0x00000040
#define TSP_TASK_EVENT_CBPVR0_RDY_SELF      0x00000080
#define TSP_TASK_EVENT_CBPVR0_RDY_POLL      0x00000100
#define TSP_TASK_EVENT_FWMSG                0x00000200
#define TSP_TASK_EVENT_PVR2PVR0_RDY_SELF    0x00000400 //PVR2 buffer0
#define TSP_TASK_EVENT_PVR2PVR1_RDY_SELF    0x00000800 //PVR2 buffer1
#define TSP_TASK_EVENT_PVR2PVR0_RDY_POLL    0x00001000 //PVR2 buffer0
#define TSP_TASK_EVENT_PVR2PVR1_RDY_POLL    0x00002000 //PVR2 buffer1

#define TSP_TASK_EVENT_PVR_SELF       (     TSP_TASK_EVENT_PVR0_RDY_SELF    |   \
                                            TSP_TASK_EVENT_PVR1_RDY_SELF    |   \
                                            TSP_TASK_EVENT_CBPVR0_RDY_SELF  |   \
                                            TSP_TASK_EVENT_PVR2PVR0_RDY_SELF|   \
                                            TSP_TASK_EVENT_PVR2PVR1_RDY_SELF)
#define TSP_TASK_EVENT_PVR_POLL       (     TSP_TASK_EVENT_PVR0_RDY_POLL    |   \
                                            TSP_TASK_EVENT_PVR1_RDY_POLL    |   \
                                            TSP_TASK_EVENT_CBPVR0_RDY_POLL  |   \
                                            TSP_TASK_EVENT_PVR2PVR0_RDY_POLL|   \
                                            TSP_TASK_EVENT_PVR2PVR1_RDY_POLL)


#define TSP_TASK_EVENT_GROUP_SELF       (   TSP_TASK_EVENT_SECTION_SELF     |   \
                                            TSP_TASK_EVENT_PVR0_RDY_SELF    |   \
                                            TSP_TASK_EVENT_PVR1_RDY_SELF    |   \
                                            TSP_TASK_EVENT_CBPVR0_RDY_SELF  |   \
                                            TSP_TASK_EVENT_PVR2PVR0_RDY_SELF|   \
                                            TSP_TASK_EVENT_PVR2PVR1_RDY_SELF)
#define TSP_TASK_EVENT_GROUP_POLL       (   TSP_TASK_EVENT_SECTION_POLL     |   \
                                            TSP_TASK_EVENT_PVR0_RDY_POLL    |   \
                                            TSP_TASK_EVENT_PVR1_RDY_POLL    |   \
                                            TSP_TASK_EVENT_CBPVR0_RDY_POLL  |   \
                                            TSP_TASK_EVENT_PVR2PVR0_RDY_POLL|   \
                                            TSP_TASK_EVENT_PVR2PVR1_RDY_POLL)

/// TSP notification function
typedef void (*P_DrvTSP_EvtCallback)(DrvTSP_Event eEvent, DrvTSP_Msg *pMsg);


//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

// General API
TSP_Result MDrv_TSP_Init(MS_U32 u32FWAddr, MS_U32 u32FWSize);                                       // Set FW address and size
TSP_Result MDrv_TSP_PowerOff(void);
TSP_Result MDrv_TSP_Exit(void);
TSP_Result MDrv_TSP_Suspend(void);
TSP_Result MDrv_TSP_Resume(MS_U32 u32FWAddr, MS_U32 u32FWSize);
TSP_Result MDrv_TSP_Alive(MS_U32 u32EngId);
TSP_Result MDrv_TSP_Reset(void);
TSP_Result MDrv_TSP_HW_Lock_Release(void);
TSP_Result MDrv_TSP_RemoveDupAVPkt(MS_BOOL bEnable);
TSP_Result MDrv_TSP_AU_BD_Mode_Enable(MS_BOOL bEnable);

// Misc API
TSP_Result MDrv_TSP_SetFwDBGParam(MS_PHYADDR phyAddr, MS_U32 u32Size, MS_U32 u32DbgWord);           // for TSP f/w debug
TSP_Result MDrv_TSP_SetOperateMode(MS_U32 u32EngId, DrvTSP_CtrlMode eCtrlMode);                     // Set TSP internal operate
TSP_Result MDrv_TSP_SelPad(MS_U32 u32EngId, DrvTSP_If eIf, DrvTSP_If_Set* pIfSet);                  // Set TSP input pad and ts0/ts1
TSP_Result MDrv_TSP_AVFifo_Reset(DrvTSP_FltType eFilterType, MS_BOOL bFlush);
TSP_Result MDrv_TSP_AVFifo_Status(DrvTSP_FltType eFilterType, MS_U32 *u32FifoLevel);
TSP_Result MDrv_TSP_AVFifo_SourceSelect(DrvTSP_PKTDMXSrcType ePKTSrc, MS_U32 u32FifoType);
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
TSP_Result MDrv_TSP_GetDscmbFltId_Range(MS_U32 u32EngId, MS_U32 *pu32StartId, MS_U32 *pu32EndId);
TSP_Result MDrv_TSP_STC64_Mode_Enable(MS_BOOL bEnable);

// NDS --> ECM
TSP_Result MDrv_TSP_SecFlt_SetEcmIdx(MS_U32 u32EngId, MS_U32 u32SecFltId, MS_U32 u32EcmIdx);

// PIDFlt API
TSP_Result MDrv_TSP_PidFlt_Alloc(MS_U32 u32EngId, DrvTSP_FltType eFilterType, MS_U32 *pu32PidFltId);
TSP_Result MDrv_TSP_PidFlt_Free(MS_U32 u32EngId, MS_U32 u32PidFltId);
TSP_Result MDrv_TSP_PidFlt_SetPid(MS_U32 u32EngId, MS_U32 u32PidFltId, MS_U16 u16PID);
TSP_Result MDrv_TSP_PidFlt_GetPid(MS_U32 u32EngId, MS_U32 u32PidFltId, MS_U32* pu32PID);
TSP_Result MDrv_TSP_PidFlt_SelSecFlt(MS_U32 u32EngId, MS_U32 u32PidFltId, MS_U32 u32SecFltId);
TSP_Result MDrv_TSP_PidFlt_Enable(MS_U32 u32EngId, MS_U32 u32PidFltId, MS_BOOL bEnable);
TSP_Result MDrv_TSP_PidFlt_GetState(MS_U32 u32EngId, MS_U32 u32PidFltId, DrvTSP_FltState *peState);
TSP_Result MDrv_TSP_PidFlt_ChangeSource(MS_U32 u32EngId, MS_U32 u32PidFltId, DrvTSP_FltType eFilterType);
TSP_Result MDrv_TSP_FLT_LiveSrcSwitch(DrvTSP_FltType eFltSrcType);


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
TSP_Result MDrv_TSP_PVR_Eng_SetBuffer(MS_U8 u8PVRId, MS_PHYADDR u32BufStart0, MS_PHYADDR u32BufStart1, MS_U32 u32BufSize0, MS_U32 u32BufSize1);
TSP_Result MDrv_TSP_PVR_Eng_Start(MS_U8 u8PVRId, DrvTSP_RecMode eRecMode, MS_BOOL bStart);
TSP_Result MDrv_TSP_PVR_Eng_GetWriteAddr(MS_U8 u8PVRId, MS_PHYADDR *pu32WriteAddr);
TSP_Result MDrv_TSP_PVR_Eng_Notify(MS_U8 u8PVRId, DrvTSP_Event eEvents, P_DrvTSP_EvtCallback pfCallback);
TSP_Result MDrv_TSP_PVR_Eng_SetPacketMode(MS_U8 u8PVRId, MS_BOOL bSet);
TSP_Result MDrv_TSP_PVR_Eng_SelSrc(MS_U8 u8PVRId, DrvTSP_PKTDMXSrcType ePktSrc);
TSP_Result MDrv_TSP_PVR_Eng_TimeStampSetRecordStamp(MS_U8 u8PVRId, MS_U32 u32Stamp);
TSP_Result MDrv_TSP_PVR_Eng_TimeStampGetRecordStamp(MS_U8 u8PVRId,MS_U32* u32Stamp);
TSP_Result MDrv_TSP_PVR_TimeStampSetPlaybackStamp(MS_U32 u32Stamp);
TSP_Result MDrv_TSP_PVR_TimeStampGetPlaybackStamp(MS_U32* u32Stamp);
TSP_Result MDrv_TSP_PVR_TimeStamp(MS_BOOL bEnable);

TSP_Result MDrv_TSP_PVRCA_Close(void);


#define MDrv_TSP_PVR_Notify(eEvents, pfCallback)    MDrv_TSP_PVR_Eng_Notify(0, eEvents, pfCallback)

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
TSP_Result MDrv_TSP_ResetFileinTimestamp(void);
TSP_Result MDrv_TSP_File_GetReadAddr(MS_PHYADDR *pu32ReadAddr);
TSP_Result MDrv_TSP_File_192BlockScheme_En(MS_BOOL bEnable);
TSP_Result MDrv_TSP_File_PS_Path_Enable(DrvTSP_FileinMode eFileinMode);

// Capacity query
TSP_Result MDrv_TSP_GetCap(DrvTSP_Cap eCap, void* pOutput);
TSP_Result MDrv_TSP_GetStatus(DrvTSP_HW_Status *HW_Status, DrvTSP_SW_Status *SW_Status);
TSP_Result MDrv_TSP_GetLibVer(const MSIF_Version **ppVersion);
TSP_Result MDrv_TSP_SetDbgLevel(DrvTSP_DbgLevel DbgLevel);
TSP_Result MDrv_TSP_GetTSIFStatus(DrvTSP_If eIf, DrvTSP_If_Set* pIfSet);


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
#if 0
TSP_Result MDrv_TSP_ResetFileinTimestamp(void);
#endif

TSP_Result MDrv_TSP_SetVQueBuf(MS_PHYADDR u32VQBaseAddr, MS_U32 u32VQBufLen);
TSP_Result MDrv_TSP_VQueEnable(MS_BOOL bEnable);
TSP_Result MDrv_TSP_VQueReset(MS_U8 u8VQID);
TSP_Result MDrv_TSP_VQueue_OverflowInt_En(MS_BOOL bEnable);
TSP_Result MDrv_TSP_Set_VQ_Threshold(MS_U8 u8req_len);
TSP_Result MDrv_TSP_Get_VQStatus(MS_U32* pu32Status);

TSP_Result MDrv_TSP_Set_MOBF_Set(MS_U8 u8Model, MS_U8 u8MobfIndex0, MS_U8 u8MobfIndex1);

#define MDrv_TSP_PVR_SetBuffer(p1, p2...)                   MDrv_TSP_PVR_Eng_SetBuffer(0, p1, p2)
#define MDrv_TSP_PVR_Start(p1, p2...)                       MDrv_TSP_PVR_Eng_Start(0, p1, p2)
#define MDrv_TSP_PVR_GetWriteAddr(p1)                       MDrv_TSP_PVR_Eng_GetWriteAddr(0, p1)
#define MDrv_TSP_PVR_SetPacketMode(p1 )                     MDrv_TSP_PVR_Eng_SetPacketMode(0, p1)
#define MDrv_TSP_PVR_TimeStampSetRecordStamp(p1)            MDrv_TSP_PVR_Eng_TimeStampSetRecordStamp(0, p1)
#define MDrv_TSP_PVR_TimeStampGetRecordStamp(p1 )           MDrv_TSP_PVR_Eng_TimeStampGetRecordStamp(0, p1)


#ifdef __cplusplus
} // closing brace for extern "C"
#endif


#endif // _DRV_TSP_H_
