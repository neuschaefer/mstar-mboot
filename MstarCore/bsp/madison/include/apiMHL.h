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


#ifndef _API_MHL_H_
#define _API_MHL_H_

#include "MsTypes.h"
#include "MsDevice.h"

#ifdef __cplusplus
extern "C"
{
#endif

//////////////////////////////////////////////////
//                MHL SW Version                //
//////////////////////////////////////////////////
#define P4_CHANGELIST       "00522289"
#define FW_VER_MAJOR        "04"
#define FW_VER_MINOR        "18"

typedef MS_U8 (*link_cbus_event_handle_func)(MS_U8);

typedef enum
{
    E_MHL_POWER_ON,
    E_MHL_POWER_STANDBY,
    E_MHL_POWER_DOWN
} E_MHL_POWERCTRL_Mode;

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
    RCP_KEYID_SELECT_RELEASE = 0x80,
}; // MscRcpKcode_T;

typedef enum
{
    MSC_RAP_POLL = 0x00,
    MSC_RAP_CONTENT_ON = 0x10,
    MSC_RAP_CONTENT_OFF = 0x11,
} MscRapActionCode_T;

enum
{
    MSC_RCP_NO_ERROR = 0x00,     // RCP No Error
    MSC_RCP_INEFFECTIVE_KEY_CODE = 0x01,     // The key code in the RCP sub-command is not recognized
    MSC_RCP_RESPONDER_BUSY = 0x02,     // RCP Response busy
}; //MscRcpStatusCode_T;

enum
{
    MSC_RAP_NO_ERROR = 0x00,     // RAP No Error
    MSC_RAP_UNRECOGNIZED_ACTION_CODE = 0x01,
    MSC_RAP_UNSUPPORTED_ACTION_CODE = 0x02,
    MSC_RAP_RESPONDER_BUSY = 0x03,
}; //MscRapStatusCode_T;

enum MHL_CBUS_CONTROL_TYPE
{
    MHL_FORCE_HDMI_BY_PASS = 0,
    MHL_FORCE_24BIT_MODE,
    MHL_FORCE_PACKET_PIXEL_MODE,
    MHL_CBUS_ISOLATION_ON,
    MHL_CBUS_ISOLATION_OFF,
    MHL_CBUS_FLOATING_ON,
    MHL_CBUS_FLOATING_OFF,
    MHL_CBUS_RTERM_OFF,
    MHL_CBUS_FORCE_CLEAR_HPD,
    MHL_CBUS_FORCE_RESET_HPD,
    MHL_VBUS_HW_DETCET,
    MHL_VBUS_CHARGE_ON,
    MHL_VBUS_CHARGE_OFF,
    MHL_CBUS_FORCE_READY_DEVCAP,
    MHL_CBUS_FORCE_RECEIVE_3D_REQ,
    MHL_CBUS_FORCE_SEND_COMMAND_ENABLE,
    MHL_CBUS_FORCE_SEND_COMMAND_DISABLE,
    MHL_CBUS_CHECK_CONTEND_ON_ENABLE,
    MHL_CBUS_CHECK_CONTEND_ON_DISABLE,
};

enum MHL_CBUS_STATUS_FLAG_TYPE
{
    MHL_CBUS_STATUS_FLAG_CABLE_DETECT = 0,
    MHL_CBUS_STATUS_FLAG_CBUS_CONNECT,
    MHL_CBUS_STATUS_FLAG_PATH_EN,
    MHL_CBUS_STATUS_FLAG_RECEIVE_PATH_EN,
    MHL_CBUS_STATUS_FLAG_RECEIVE_MUTED,
};

enum MHL_CABLE_DETECT_USE_TYPE
{
    MHL_CABLE_DETECT_USE_PORTA = 0x01,
    MHL_CABLE_DETECT_USE_PORTB = 0x02,
    MHL_CABLE_DETECT_USE_PORTC = 0x04,
    MHL_CABLE_DETECT_USE_PORTD = 0x08,
};

//-------------------------------------------------------------------------------------------------
//  Function Prototype
//-------------------------------------------------------------------------------------------------
// MHL system control function
void mapi_mhl_MHLSupportPath(MS_U8 ucSelect);
void mapi_mhl_init(MS_U8 *edid, MS_U8 *DevCap);
void mapi_mhl_LoadEDID(MS_U8 *edid);
void mapi_mhl_ReadEDID(MS_U16 usSize, MS_U8 *edid);
void mapi_mhl_LoadDeviceCapability(MS_U8 *devcap);
void mapi_mhl_SetVenderID(MS_U8 ucVenderID);
void mapi_mhl_InvertCableDetect(MS_BOOL bCableDetectInvert);
void mapi_mhl_VbusConfigSetting(MS_U8 ucState);
void mapi_mhl_CableDetectPadSetting(MS_U8 ucSelect);
void mapi_mhl_handler(void);
void mapi_mhl_PowerCtrl(E_MHL_POWERCTRL_Mode pctrl);
// MHL flag check function
MS_BOOL mapi_mhl_CableDetect(void);
MS_BOOL mapi_mhl_CbusStatus(void);
MS_BOOL mapi_mhl_CbusWakeupIntFlag(void);
MS_BOOL mapi_mhl_ReadDevcapFlag(void);
MS_BOOL mapi_mhl_SrcRCPSupportFlag(void);
MS_BOOL mapi_mhl_SrcRAPSupportFlag(void);
MS_BOOL mapi_mhl_SrcMSGResponseFlag(void);
// MHL Tx function
MS_BOOL mapi_mhl_SendMSGCmdFlag(void);
MS_BOOL mapi_mhl_SendRAPCmd(MS_U8 databuf);
MS_BOOL mapi_mhl_SendRCPCmd(MS_U8 databuf);
MS_BOOL mapi_mhl_SendRCP_PressRelease_Cmd(MS_U8 u8RCPKey, MS_BOOL bIsRelease);
MS_BOOL mapi_mhl_SendRCPAutoReleaseCmd(MS_U8 ucKeyCode);
MS_BOOL mapi_mhl_SendUCPCmd(MS_U8 databuf);
MS_BOOL mapi_mhl_SendWriteBurst(MS_U8 ucAddr, MS_U8 ucLength, MS_U8 *buffer);
MS_BOOL mapi_mhl_ReadDeviceCapacibility(MS_U8 ucAddr, MS_U8 *ucData);
MS_BOOL mapi_mhl_GetDeviceCapacibility(MS_U16 usDevcapMask, MS_U8 *ucDevcap);
MS_BOOL mapi_mhl_GetDeviceVenderID(MS_U8 *ucVenderID);
MS_BOOL mapi_mhl_GetWriteBurstData(MS_U8 *ucData);
void mapi_mhl_Send3DInformation(void);
void mapi_mhl_CbusSendCommand(void);
// MHL others function
void mapi_mhl_CbusIsolate(void);
void mapi_mhl_CbusWakeupIntSetting(void);
MS_BOOL mapi_mhl_AutoSwitchHandler(MS_BOOL bReset, MS_U8 *ucCbusPath);
void mapi_mhl_AdjustSettingIControl(MS_U8 ucIControl);
void mapi_mhl_AdjustImpedanceSetting(MS_U8 ucImpedance);
MS_BOOL mapi_mhl_WakeupDetect(void);
MS_U32 mapi_mhl_SetPowerState(EN_POWER_MODE u16PowerState);
void mapi_mhl_SetHPD(MS_BOOL bflag);
void mapi_mhl_SetPsCtrl(MS_U8 u8Ctrl);
void mapi_mhl_CbusControl(MS_U8 ucState);
MS_BOOL mapi_mhl_CbusGetStatusFlag(MS_U8 ucState);
void mapi_mhl_GetSWVersion(void);
char* mapi_mhl_GetP4CL(void);
char* mapi_mhl_GetMajorVersion(void);
char* mapi_mhl_GetMinorVersion(void);
void mapi_mhl_RegisterCallBackFunctions(link_cbus_event_handle_func rcp, link_cbus_event_handle_func rap);
void mapi_mhl_RegisterUcpCallBackFunction(link_cbus_event_handle_func Ucp);

#ifdef __cplusplus
}
#endif

#endif //_API_MHL_H_
