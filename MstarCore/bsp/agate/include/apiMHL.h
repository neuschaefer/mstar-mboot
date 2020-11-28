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
///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   Mapi_mhl.h
/// @author MStar Semiconductor Inc.
/// @brief  MHL driver Function
///////////////////////////////////////////////////////////////////////////////////////////////////

/*
    1. Check whether MHL cable is plugged or not in Rx side
    2. Disable R-term and output Vbus
    3. Check whether Cbus is connected(discovery pulse completed)
    4. Sink -> Source: "SET_HPD"
    5. Sink -> Source: Write_Stat - "DCAP_RDY" and Write_INT - "DCAP_CHG"
    6. Sink -> Source: Write_Stat - "PATH_EN"
*/


#ifndef _MAPI_MHL_H_
#define _MAPI_MHL_H_

#include "MsTypes.h"
#include "mdrv_mhl_st.h"

#ifdef __cplusplus
extern "C"
{
#endif

#if 0
//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

#define DMHL_INT_ENABLE    0 // MHL interrupt enable
#define DMHLCDRMODE    1 // MHL CDR mode

#define DEM_POLLING_DELAY       10     // Main Loop Polling interval (ms)
#define CBUS_FW_COMMAND_TIMEOUT_SECS    5       // No response for 1 second means we hold off and move
#define CBUS_FW_HOLD_OFF_SECS           2       // Allow bus to quieten down when ABORTs are received.

#define DMHL_ADOPTER_ID    0x02CB // Mstar: 715
#define DMHL_DEVICE_ID    0x0000 // Chip ID?
#define DMHL_VENDOR_ID    0x00 // ?

#define MHL_MSC_SCRATCHPAD_SIZE    17// offset + maxi 16 packets
#define MHL_CBUS_DATA_SIZE    MHL_MSC_SCRATCHPAD_SIZE
#define MHL_CBUS_COMMAND_BUFFER    4
#define DMHL_CBUS_TX_FIFO    MHL_MSC_SCRATCHPAD_SIZE+2 // Write_Burst(0x6C) + offset(0x40 ~ 0x7F) + maxi 16 packets + EOF(0x32)

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef enum
{
    CBUS_STATE_IDLE = 0,    // Cbus idle
    CBUS_STATE_SENT,    // Cbus command sent
    CBUS_STATE_ACK,    // Cbus command has been acked
    CBUS_STATE_RECEIVED,    // Cbus message received
    CBUS_STATE_WAITING_ACK,    // Cbus waiting RCPK or PAPK
} CbusState_T;

typedef enum
{
    CBUS_REQ_IDLE       = 0,
    CBUS_REQ_PENDING,           // Request is waiting to be sent
    CBUS_REQ_SENT,              // Request has been sent
    CBUS_REQ_RECEIVED,          // Request data has been received
} CbusReqState_T;

enum
{
    MSC_ACK = 0x33, // Command/Data byte acknowledged
    MSC_NACK = 0x34, // Command or Data byte not acknowledge
    MSC_ABORT = 0x35, // Transaction abort
    MSC_WRITE_STAT_OR_SET_INT = 0x60,  // Write one status or interrupt register
    MSC_READ_DEVCAP = 0x61, // Read one register
    MSC_GET_STATE = 0x62, // Read CBUS revision level from follower
    MSC_GET_VENDOR_ID = 0x63, // Read vendor ID value from follower.
    MSC_SET_HPD = 0x64, // Set Hot Plug Detect in follower
    MSC_CLR_HPD = 0x65, // Clear Hot Plug Detect in follower
    MSC_MSC_MSG = 0x68, // VS command to send RCP sub-commands
    MSC_GET_SC1_ERRORCODE = 0x69, // Get Vendor-Specific command error code.
    MSC_GET_DDC_ERRORCODE = 0x6A, // Get DDC channel command error code.
    MSC_GET_MSC_ERRORCODE = 0x6B, // Get MSC command error code.
    MSC_WRITE_BURST = 0x6C, // Write 1-16 bytes to responder’s scratchpad.
    MSC_GET_SC3_ERRORCODE = 0x6D, // Get channel 3 command error code.
    MSC_EOF = 0x32, // End of Frame
}; //MscCtrlPkt_T;

enum
{
    SI_HPD_ACTIVE               = 0x00,     // HPD HI, HDCP, EDID, RX Term enabled
    SI_HPD_INACTIVE,                        // HPD LOW, HDCP, RX Term disabled
    SI_HPD_ACTIVE_EX,                       // EDID, RX Term enabled
    SI_HPD_INACTIVE_EX,                     // HPD HI, HDCP, EDID, RX Term disabled
    SI_HPD_TOGGLE,                  // Special use for CBUS connect
};

typedef enum
{
    STATUS_SUCCESS = 0,
    ERROR_CBUS_CAN_RETRY,
    ERROR_CBUS_ABORT,
    ERROR_CBUS_TIMEOUT,
    ERROR_CBUS_LINK_DOWN,
    ERROR_INVALID,
    ERROR_INIT,
    ERROR_WRITE_FAILED,
    ERROR_NACK_FROM_PEER,
    ERROR_NO_HEARTBEAT,

} CBUS_SOFTWARE_ERRORS_t;

enum
{
    MSC_MSG_MSGE = 0x02,    // MSG Error sub-command
    MSC_MSG_RCP = 0x10,    // RCP sub-command
    MSC_MSG_RCPK = 0x11,    // RCP Acknowledge sub-command
    MSC_MSG_RCPE = 0x12,    // RCP Error sub-command
    MSC_MSG_RAP = 0x20,    // Mode Change Warning sub-command
    MSC_MSG_RAPK = 0x21,     // MCW Acknowledge sub-command
}; //MscMsgSubCmd_T;

enum
{
    MSC_MSGE_NO_ERROR = 0x00,     // No Error
    MSC_MSGE_INVALID_SUB_COMMAND_CODE = 0x01,     // The sub-command code is not valid
}; //MsceStatusCode_T;

enum
{
    MSC_RCP_NO_ERROR = 0x00,     // RCP No Error
    MSC_RCP_INEFFECTIVE_KEY_CODE = 0x01,     // The key code in the RCP sub-command is not recognized
    MSC_RCP_RESPONDER_BUSY = 0x02,     // RCP Response busy
}; //MscRcpStatusCode_T;

typedef enum
{
    MSC_RAP_POLL = 0x00,
    MSC_RAP_CONTENT_ON = 0x10,
    MSC_RAP_CONTENT_OFF = 0x11,
} MscRapActionCode_T;

enum
{
    MSC_RAP_NO_ERROR = 0x00,     // RAP No Error
    MSC_RAP_UNRECOGNIZED_ACTION_CODE = 0x01,
    MSC_RAP_UNSUPPORTED_ACTION_CODE = 0x02,
    MSC_RAP_RESPONDER_BUSY = 0x03,
}; //MscRapStatusCode_T;


enum
{
    RCP_KEYID_SELECT = 0x00,
    RCP_KEYID_UP = 0x01,
    RCP_KEYID_DOWN = 0x02,
    RCP_KEYID_LEFT = 0x03,
    RCP_KEYID_RIGHT = 0x04,
    RCP_KEYID_RIGHT_UP = 0x05,
    RCP_KEYID_RIGHT_DOWN = 0x06,
    RCP_KEYID_LEFT_UP = 0x07,
    RCP_KEYID_LEFT_DOWN = 0x08,
    RCP_KEYID_ROOT_MENU = 0x09,
    RCP_KEYID_SETUP_MENU = 0x0A,
    RCP_KEYID_CONTENTS_MENU = 0x0B,
    RCP_KEYID_FAVORITE_MENU = 0x0C,
    RCP_KEYID_EXIT = 0x0D,
    //0x0E - 0x1F are reserved
    RCP_KEYID_NUM_0 = 0x20,
    RCP_KEYID_NUM_1 = 0x21,
    RCP_KEYID_NUM_2 = 0x22,
    RCP_KEYID_NUM_3 = 0x23,
    RCP_KEYID_NUM_4 = 0x24,
    RCP_KEYID_NUM_5 = 0x25,
    RCP_KEYID_NUM_6 = 0x26,
    RCP_KEYID_NUM_7 = 0x27,
    RCP_KEYID_NUM_8 = 0x28,
    RCP_KEYID_NUM_9 = 0x29,
    RCP_KEYID_DOT = 0x2A,
    RCP_KEYID_ENTER = 0x2B,
    RCP_KEYID_CLEAR = 0x2C,
    //0x2D - 0x2F are reserved
    RCP_KEYID_CH_UP = 0x30,
    RCP_KEYID_CH_DOWN = 0x31,
    RCP_KEYID_PRE_CH = 0x32,
    RCP_KEYID_SOUND_SELECT = 0x33,
    RCP_KEYID_INPUT_SELECT = 0x34,
    RCP_KEYID_SHOW_INFO = 0x35,
    RCP_KEYID_HELP = 0x36,
    RCP_KEYID_PAGE_UP = 0x37,
    RCP_KEYID_PAGE_DOWN = 0x38,
    //0x39 - 0x40 are reserved
    RCP_KEYID_VOL_UP = 0x41,
    RCP_KEYID_VOL_DOWN = 0x42,
    RCP_KEYID_MUTE = 0x43,
    RCP_KEYID_PLAY = 0x44,
    RCP_KEYID_STOP = 0x45,
    RCP_KEYID_PAUSE = 0x46,
    RCP_KEYID_RECORD = 0x47,
    RCP_KEYID_REWIND = 0x48,
    RCP_KEYID_FAST_FWD = 0x49,
    RCP_KEYID_EJECT  = 0x4A,
    RCP_KEYID_FORWARD = 0x4B,
    RCP_KEYID_BACKWARD = 0x4C,
    //0x4D - 0x4F are reserved
    RCP_KEYID_ANGLE = 0x50,
    RCP_KEYID_SUBPICTURE = 0x51,
    //0x52 - 0x5F are reserved
    RCP_KEYID_PLAY_FUNC = 0x60,
    RCP_KEYID_PAUSE_PLAY_FUNC = 0x61,
    RCP_KEYID_RECORD_FUNC = 0x62,
    RCP_KEYID_PAUSE_REC_FUNC = 0x63,
    RCP_KEYID_STOP_FUNC = 0x64,
    RCP_KEYID_MUTE_FUNC = 0x65,
    RCP_KEYID_UN_MUTE_FUNC = 0x66,
    RCP_KEYID_TUNE_FUNC = 0x67,
    RCP_KEYID_MEDIA_FUNC = 0x68,
    //0x69 - 0x70 are reserved
    RCP_KEYID_F1 = 0x71,
    RCP_KEYID_F2 = 0x72,
    RCP_KEYID_F3 = 0x73,
    RCP_KEYID_F4 = 0x74,
    RCP_KEYID_F5 = 0x75,
    //0x76 - 0x7D are reserved
    RCP_KEYID_VENDOR_SPECIFIC = 0x7E,
    RCP_KEYID_RESERVED = 0x7F,
}; // MscRcpKcode_T;


typedef struct
{
    MS_BOOL bDCAP_CHG; // 0x20[0], device capability changed
    MS_BOOL bDSCR_CHG; // 0x20[1], device scratchpad changed
    MS_BOOL bREQ_WRT; // 0x20[2], Request-to-Write
    MS_BOOL bGRT_WRT; // 0x20[3], Grant-to-Write
    MS_BOOL bEDID_CHG; // 0x21[1], EDID changed
} DevIntReg_S;


typedef struct
{
    MS_BOOL bDCAP_RDY; // 0x30[0], device capability ready
    MS_U8 CLK_MODE; // 0x31[2:0], MHL clock mode
    MS_BOOL bPATH_EN; // 0x31[3], device TMDS path enable
    MS_BOOL bMUTED; // 0x31[4], device content stream is muted
} DevStatusReg_S;


typedef struct
{
    MS_U8 msgData[MHL_CBUS_DATA_SIZE];    // Cbus message data
    MS_U8 cmd;    // MSC command
    MS_U8 len;    // message length
    MS_U8 rcState;    // received state
    CbusReqState_T reqStatus;    // Cbus request status
} CbusReq_S;

typedef struct
{
    CbusReq_S request[MHL_CBUS_COMMAND_BUFFER];
    MS_U32 reqWrtTimer;    // Timer for RAP command response
    MS_U16 abortTimer;    // abortTimer
    MS_BOOL bMhlCbusConnected;    // True if a connected MHD port
    CbusState_T MhlCbusState;    // MHL Cbus state
    MS_U16 timeout;    // Timer for message response (must be able to indicate at least 3000ms).
    MS_U8 curIdx;    // current index.
    MS_BOOL bMhlHpdState;    // SET_HPD(TRUE) / CLR_HPD(FALSE)
    MS_BOOL reqWrt;    // request to write peer's scratchpad regs
    DevIntReg_S MhlDevIntReg;
    DevStatusReg_S MhlDevStatusReg;
} CbusInfo_S;

typedef struct
{
    MS_BOOL bMhlCablePlugged; // MHL cable plugged
    CbusInfo_S MhlCbusInfo;
} MHLInfo_S;

typedef struct
{
    MS_U8 lens;
    MS_U16 databuf[DMHL_CBUS_TX_FIFO];
} mhalCbusFifo_S;

typedef enum
{
    RX_HDMI_RTERM = 0,    // HDMI mode
    RX_MHL_RTERM,    // MHL mode
    RX_RTERM_OFF,    // R-term off
} RXRtermControl_T;

typedef MS_U8 (*link_cbus_event_handle_func)(MS_U8);
#endif

//-------------------------------------------------------------------------------------------------
//  Function Prototype
//-------------------------------------------------------------------------------------------------
void mapi_mhl_SetHPD(MS_BOOL bflag);
void mapi_mhl_SetARC(MS_BOOL bEable);
MS_BOOL mapi_mhl_HDMI_5V_Detect(void);
MS_BOOL mapi_mhl_CableDetect(void);
MS_BOOL mapi_mhl_CbusStatus(void);
void mapi_mhl_CbusConnectionCheck(void);
void mapi_mhl_init(void);
void mapi_mhl_init_EDID(MS_U8 *edid);
MS_BOOL mapi_mhl_CbusRcpReply (MS_U8 statusCode, MS_U8 keyCode);
MS_BOOL mapi_mhl_CbusRapReply (MS_U8 statusCode);
MS_BOOL mapi_mhl_Cbus_SetHPDState(MS_BOOL bflag);
void mapi_mhl_Cbus_SetPathEn(MS_BOOL bflag);
void mapi_mhl_Cbus_SetDCapRdy(MS_BOOL bflag);
void mapi_mhl_Cbus_SetDCapChg(MS_BOOL bflag);
void mapi_mhl_SetCbusReqState(CbusReqState_T cbusState);
void mapi_mhl_CbusIntCB(void);
void mapi_mhl_CbusIntHandler(void);
MS_U8 mapi_mhl_CBusNextCmdQueue(void);
MS_U8 mapi_mhl_CBusGetQueueSize(void);
MS_BOOL mapi_mhl_CbusSendMsg (CbusReq_S *pReq);
MS_BOOL mapi_mhl_CBusProcessMSCSubCmd (MS_U8 cmd);
void mapi_mhl_RegisterCallBackFunctions(link_cbus_event_handle_func rcp, link_cbus_event_handle_func rap);
void mapi_mhl_CbusRxHandler (void);
MS_U8 mapi_mhl_CbusTxHandler (void);
MS_U8 mapi_mhl_CbusMSCAckCmdStatus(void);
MS_BOOL msapi_mhl_SendRCPCmd(MS_U8 databuf);
MS_BOOL msapi_mhl_SendRAPCmd(MS_U8 databuf);
void mapi_mhl_SetDevCapTbl(MS_U8* pu8Tbl);

#ifdef __cplusplus
}
#endif

#endif //_MAPI_MHL_H_


