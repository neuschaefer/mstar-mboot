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
/// @file   apiCEC.h
/// @brief  CEC Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _APICEC_H_
#define _APICEC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define MSIF_CEC_LIB_CODE               {'C','E','C','_'}
#define MSIF_CEC_LIBVER                 {'0','0'}                         /* 0.0 ~ Z.Z */
#define MSIF_CEC_BUILDNUM               {'0','8'}                         /* 00 ~ 99   */
#define MSIF_CEC_CHANGELIST             {'0','0','4','4','9','9','9','1'} /* CL#       */
#define CEC_API_VERSION                  /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_CEC_LIB_CODE,                  /* IP__                                             */  \
    MSIF_CEC_LIBVER,                    /* 0.0 ~ Z.Z                                        */  \
    MSIF_CEC_BUILDNUM,                  /* 00 ~ 99                                          */  \
    MSIF_CEC_CHANGELIST,                /* CL#                                              */  \
    MSIF_OS

#define CEC_VERSION_11      0   //CEC1.1
#define CEC_VERSION_12      1   //CEC1.2
#define CEC_VERSION_12a     2   //CEC1.2a
#define CEC_VERSION_13      3   //CEC1.3
#define CEC_VERSION_13a     4   //CEC1.3a
#define CEC_VERSION_14      5   //CEC1.4

#define HDMI_CEC_VERSION    CEC_VERSION_14

#define CEC_FIFO_CNT       4
#define RETRY_CNT          1
#define FrameInterval      7
#define BusFreeTime        5
#define ReTxInterval       3

#define ENABLE_CEC_INT                  ENABLE
#define ENABLE_CUST01_CEC               ENABLE
#define ENABLE_SW_CEC_WAKEUP            ENABLE
#define ENABLE_CEC_MULTIPLE             DISABLE

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

typedef enum _CEC_ERROR_CODE
{
    E_CEC_FEATURE_ABORT = 0x00,
    E_CEC_RX_SUCCESS    = 0x01,
    E_CEC_TX_SUCCESS    = 0x02,
    E_CEC_RF            = 0x04,
    E_CEC_LOST_ABT      = 0x08,
    E_CEC_BIT_SHORT     = 0x10,
    E_CEC_BIT_LONG      = 0x20,
    E_CEC_NACK          = 0x40,
    E_CEC_SYSTEM_BUSY   = 0x80,
} CEC_ERROR_CODE;

//Logical Address
typedef enum _MsCEC_DEVICELA
{
    E_LA_TV              =0,
    E_LA_RECORDER1       =1,
    E_LA_RECORDER2       =2,
    E_LA_TUNER1          =3,
    E_LA_PLAYBACK1       =4,
    E_LA_AUDIO_SYS       =5,
    E_LA_TUNER2          =6,
    E_LA_TUNER3          =7,
    E_LA_PLAYBACK2       =8,
    E_LA_RECORER3        =9,
#if(HDMI_CEC_VERSION >= CEC_VERSION_13a)
    E_LA_TUNER4          =10,
    E_LA_PLYBACK3        =11,
#endif
    RESERVED_1            =12,
    RESERVED_2            =13,
    E_LA_FREE_USE        =14,
    E_LA_UNREGISTERED    =15,
    E_LA_BROADCAST       =15,
    E_LA_MAX =15,
} MsCEC_DEVICELA;

//the opcode is referenced from CEC1.3a table 7 ~ 27
typedef enum _MsCEC_MSGLIST
{
//----- One Touch Play ----------------------------
    E_MSG_ACTIVE_SOURCE                         = 0x82,
    E_MSG_OTP_IMAGE_VIEW_ON                     = 0x04,
    E_MSG_OTP_TEXT_VIEW_ON                      = 0x0D,

//----- Routing Control ---------------------------
    //E_MSG_RC_ACTIVE_SOURCE                    = 0x82,
    E_MSG_RC_INACTIVE_SOURCE                    = 0x9D,
    E_MSG_RC_REQ_ACTIVE_SOURCE                  = 0x85,
    E_MSG_RC_ROUTING_CHANGE                     = 0x80,
    E_MSG_RC_ROUTING_INFO                       = 0x81,
    E_MSG_RC_SET_STREM_PATH                     = 0x86,

//----- Standby Command ---------------------------
    E_MSG_STANDBY                               = 0x36,

//----- One Touch Record---------------------------
    E_MSG_OTR_RECORD_ON                         = 0x09,
    E_MSG_OTR_RECORD_OFF                        = 0x0B,
    E_MSG_OTR_RECORD_STATUS                     = 0x0A,
    E_MSG_OTR_RECORD_TV_SCREEN                  = 0x0F,

//----- Timer programmer -------------------------- CEC1.3a
    E_MSG_TP_CLEAR_ANALOG_TIMER                 = 0x33,
    E_MSG_TP_CLEAR_DIGITAL_TIMER                = 0x99,
    E_MSG_TP_CLEAR_EXT_TIMER                    = 0xA1,
    E_MSG_TP_SET_ANALOG_TIMER                   = 0x34,
    E_MSG_TP_SET_DIGITAL_TIMER                  = 0x97,
    E_MSG_TP_SET_EXT_TIMER                      = 0xA2,
    E_MSG_TP_SET_TIMER_PROGRAM_TITLE            = 0x67,
    E_MSG_TP_TIMER_CLEARD_STATUS                = 0x43,
    E_MSG_TP_TIMER_STATUS                       = 0x35,

//----- System Information ------------------------
    E_MSG_SI_CEC_VERSION                        = 0x9E,       //1.3a
    E_MSG_SI_GET_CEC_VERSION                    = 0x9F,       //1.3a

    E_MSG_SI_REQUEST_PHY_ADDR                   = 0x83,
    E_MSG_SI_REPORT_PHY_ADDR                    = 0x84,
    E_MSG_SI_GET_MENU_LANGUAGE                  = 0x91,
    E_MSG_SI_SET_MENU_LANGUAGE                  = 0x32,
    //E_MSG_SI_POLLING_MESSAGE                  = ?,

    //E_MSG_SI_REC_TYPE_PRESET                  = 0x00,  //parameter   ?
    //E_MSG_SI_REC_TYPE_OWNSRC                  = 0x01,  //parameter   ?

//----- Deck Control Feature-----------------------
    E_MSG_DC_DECK_CTRL                          = 0x42,
    E_MSG_DC_DECK_STATUS                        = 0x1B,
    E_MSG_DC_GIVE_DECK_STATUS                   = 0x1A,
    E_MSG_DC_PLAY                               = 0x41,

//----- Tuner Control ------------------------------
    E_MSG_TC_GIVE_TUNER_STATUS                  = 0x08,
    E_MSG_TC_SEL_ANALOG_SERVICE                 = 0x92,
    E_MSG_TC_SEL_DIGITAL_SERVICE                = 0x93,
    E_MSG_TC_TUNER_DEVICE_STATUS                = 0x07,
    E_MSG_TC_TUNER_STEP_DEC                     = 0x06,
    E_MSG_TC_TUNER_STEP_INC                     = 0x05,

//---------Vendor Specific -------------------------
    //E_MSG_VS_CEC_VERSION                      = 0x9E,       //1.3a
    //E_MSG_VS_GET_CEC_VERSION                  = 0x9F,       //1.3a
    E_MSG_VS_DEVICE_VENDOR_ID                   = 0x87,
    E_MSG_VS_GIVE_VENDOR_ID                     = 0x8C,
    E_MSG_VS_VENDOR_COMMAND                     = 0x89,
    E_MSG_VS_VENDOR_COMMAND_WITH_ID             = 0xA0,      //1.3a
    E_MSG_VS_VENDOR_RC_BUT_DOWN                 = 0x8A,
    E_MSG_VS_VENDOR_RC_BUT_UP                   = 0x8B,

//----- OSD Display --------------------------------
    E_MSG_SET_OSD_STRING                        = 0x64,

//----- Device OSD Name Transfer  -------------------------
    E_MSG_OSDNT_GIVE_OSD_NAME                   = 0x46,
    E_MSG_OSDNT_SET_OSD_NAME                    = 0x47,

//----- Device Menu Control ------------------------
    E_MSG_DMC_MENU_REQUEST                      = 0x8D,
    E_MSG_DMC_MENU_STATUS                       = 0x8E,
    //E_MSG_DMC_MENU_ACTIVATED                  = 0x00,   //parameter
    //E_MSG_DMC_MENU_DEACTIVATED                = 0x01,   //parameter
    E_MSG_UI_PRESS                              = 0x44,
    E_MSG_UI_RELEASE                            = 0x45,

//----- Remote Control Passthrough ----------------
//----- UI Message --------------------------------
//#define UI_PRESS             0x44
//#define UI_RELEASE           0x45

//----- Power Status  ------------------------------
    E_MSG_PS_GIVE_POWER_STATUS                  = 0x8F,
    E_MSG_PS_REPORT_POWER_STATUS                = 0x90,

//----- General Protocal Message ------------------
//----- Abort Message -----------------------------
    E_MSG_ABORT_MESSAGE                         = 0xFF,
//----- Feature Abort -----------------------------
    E_MSG_FEATURE_ABORT                         = 0x00,

//----- System Audio Control ------------------
    E_MSG_SAC_GIVE_AUDIO_STATUS                 = 0x71,
    E_MSG_SAC_GIVE_SYSTEM_AUDIO_MODE_STATUS     = 0x7D,
    E_MSG_SAC_REPORT_AUDIO_STATUS               = 0x7A,
    E_MSG_SAC_SET_SYSTEM_AUDIO_MODE             = 0x72,
    E_MSG_SAC_SYSTEM_AUDIO_MODE_REQUEST         = 0x70,
    E_MSG_SAC_SYSTEM_AUDIO_MODE_STATUS          = 0x7E,

//----- System Audio Control ------------------
    E_MSG_SAC_SET_AUDIO_RATE                    = 0x9A,

//----- Audio Return Channel  Control ------------------
    E_MSG_ARC_INITIATE_ARC                    = 0xC0,
    E_MSG_ARC_REPORT_ARC_INITIATED                    = 0xC1,
    E_MSG_ARC_REPORT_ARC_TERMINATED                    = 0xC2,
    E_MSG_ARC_REQUEST_ARC_INITATION                    = 0xC3,
    E_MSG_ARC_REQUEST_ARC_TERMINATION                    = 0xC4,
    E_MSG_ARC_TERMINATED_ARC                    = 0xC5,
} MsCEC_MSGLIST;

typedef enum _MsCEC_MSG_TRANS_TYPE
{
    E_TRANS_BROADCAST_MSG   = 0,
    E_TRANS_DIRECT_MSG      = 1,
    E_TRANS_BOTHTYPE_MSG    = 2,
} MsCEC_MSG_TRANS_TYPE;


//Device Type, 1byte
typedef enum _MsCEC_DEVICE_TYPE
{
    E_DEVICE_TYPE_TV                    =0,
    E_DEVICE_TYPE_RECORDING_DEVICE      =1,
    E_DEVICE_TYPE_RESERVED              =2,
    E_DEVICE_TYPE_TUNER                 =3,
    E_DEVICE_TYPE_PLAYBACK_DEVICE       =4,
    E_DEVICE_TYPE_AUDIO_SYSTEM          =5,
} MsCEC_DEVICE_TYPE;


//Deck Control, Deck Control Mode 1 byte
typedef enum _MsCEC_MSG_DC_DECK_CTRL_PARM
{
    E_MSG_DCM_CMD_SKIP_FORWARD          = 1,  //parameter
    E_MSG_DCM_CMD_SKIP_REVERSE          = 2,  //parameter
    E_MSG_DCM_CMD_STOP                  = 3,  //parameter
    E_MSG_DCM_CMD_EJECT                 = 4,  //parameter
} MsCEC_MSG_DC_DECK_CTRL_PARM;

//Deck status, Deck info 1 byte
typedef enum _MsCEC_MSG_DC_DECK_STATUS_PARM
{
    E_MSG_DI_CMD_PLAY                   = 0x11,  //parameter
    E_MSG_DI_CMD_RECORD                 = 0x12,  //parameter
    E_MSG_DI_CMD_PLAY_REVERSE           = 0x13,  //parameter
    E_MSG_DI_CMD_STILL                  = 0x14,  //parameter
    E_MSG_DI_CMD_SLOW                   = 0x15,  //parameter
    E_MSG_DI_CMD_SLOW_REVERSE           = 0x16,  //parameter
    E_MSG_DI_CMD_FAST_FORWARD           = 0x17,  //parameter
    E_MSG_DI_CMD_FAST_REVERSE           = 0x18,  //parameter
    E_MSG_DI_CMD_NO_MEDIA               = 0x19,  //parameter
    E_MSG_DI_CMD_STOP                   = 0x1A,  //parameter
    E_MSG_DI_CMD_SKIP_FORWARD           = 0x1B,  //parameter
    E_MSG_DI_CMD_SKIP_REVERSE           = 0x1C,  //parameter
    E_MSG_DI_CMD_INDEX_SEARCH_FORWARD   = 0x1D,  //parameter
    E_MSG_DI_CMD_INDEX_SEARCH_REVERSE   = 0x1E,  //parameter
    E_MSG_DI_CMD_OTHER_STATUS           = 0x1F,  //parameter
} MsCEC_MSG_DC_DECK_STATUS_PARM;


//Give deck status, Status request 1 byte
typedef enum _MsCEC_MSG_STATUS_REQUEST_PARM
{
    E_MSG_SR_CMD_ON                     = 1,  //parameter
    E_MSG_SR_CMD_OFF                    = 2,  //parameter
    E_MSG_SR_CMD_ONCE                   = 3,  //parameter
} MsCEC_MSG_STATUS_REQUEST_PARM;


//Play, [Play Mode] 1 byte
typedef enum _MsCEC_MSG_DC_PLAY_PARM
{
    E_MSG_PM_CMD_PLAY_FORWARD               = 0x24,  //parameter
    E_MSG_PM_CMD_PLAY_REVERSE               = 0x20,  //parameter
    E_MSG_PM_CMD_PLAY_STILL                 = 0x25,  //parameter
    E_MSG_PM_CMD_FAST_FORWARD_MINI_SPEED    = 0x05,  //parameter
    E_MSG_PM_CMD_FAST_FORWARD_MEDIUM_SPEED  = 0x06,  //parameter
    E_MSG_PM_CMD_FAST_FORWARD_MAXI_SPEED    = 0x07,  //parameter
    E_MSG_PM_CMD_FAST_REVERSE_MINI_SPEED    = 0x09,  //parameter
    E_MSG_PM_CMD_FAST_REVERSE_MEDIUM_SPEED  = 0x0A,  //parameter
    E_MSG_PM_CMD_FAST_REVERSE_MAXI_SPEED    = 0x0B,  //parameter
    E_MSG_PM_CMD_SLOW_FORWARD_MINI_SPEED    = 0x15,  //parameter
    E_MSG_PM_CMD_SLOW_FORWARD_MEDIUM_SPEED  = 0x16,  //parameter
    E_MSG_PM_CMD_SLOW_FORWARD_MAXI_SPEED    = 0x17,  //parameter
    E_MSG_PM_CMD_SLOW_REVERSE_MINI_SPEED    = 0x19,  //parameter
    E_MSG_PM_CMD_SLOW_REVERSE_MEDIUM_SPEED  = 0x1A,  //parameter
    E_MSG_PM_CMD_SLOW_REVERSE_MAXI_SPEED    = 0x1B,  //parameter
} MsCEC_MSG_DC_PLAY_PARM;


//Power status 1 byte
typedef enum _MsCEC_MSG_POWER_STATUS_PARM
{
    E_MSG_PWRSTA_ON             = 0x00,
    E_MSG_PWRSTA_STANDBY        = 0x01,
    E_MSG_PWRSTA_STANDBY2ON     = 0x02,
    E_MSG_PWRSTA_ON2STANDBY     = 0x03,
    E_MSG_PWRSTA_UNKNOW                 = 0x04,
} MsCEC_MSG_POWER_STATUS_PARM;


typedef enum _MsCEC_MSG_ABORT_REASON
{
    E_MSG_AR_UNRECOGNIZE_OPCDE  = 0x00,  // abort reason
    E_MSG_AR_CANNOTRESPOND      = 0x01,  // abort reason
    E_MSG_AR_CANNOTPROVIDESCR   = 0x02,  // abort reason
    E_MSG_AR_INVALID_OPCODE     = 0x03,  // abort reason
    E_MSG_AR_REFUSED            = 0x04,  // abort reason
    E_MSG_AR_IGNORED            = 0x05,
    E_MSG_AR_SUCCESSED        = 0x06,
} MsCEC_MSG_ABORT_REASON;


typedef enum _MsCEC_MSG_MENU_REQ_TYPE
{
    E_MSG_MENU_REQ_ACTIVATED    = 0,  // menu request activated status
    E_MSG_MENU_REQ_DEACTIVATED  = 1,  // menu request deactivated status
    E_MSG_MENU_REQ_QUERY        = 2,  // menu request query status
} MsCEC_MSG_MENU_REQ_TYPE;


typedef enum _MsCEC_MSG_MENU_STATE
{
    E_MSG_MENU_ACTIVATED    = 0,  // menu activated
    E_MSG_MENU_DEACTIVATED  = 1,  // menu deactivated
} MsCEC_MSG_MENU_STATE;


typedef enum _MsCEC_MSG_RECORD_SOURCE_TYPE
{
    E_MSG_RECORD_TYPE_OWN_SOURCE                = 1,  // own source
    E_MSG_RECORD_TYPE_DIGITAL_SERVICE           = 2,  // digital service
#if(HDMI_CEC_VERSION >= CEC_VERSION_13a)
    E_MSG_RECORD_TYPE_ANALOGUE_SERVICE          = 3,  // Analogue Service
    E_MSG_RECORD_TYPE_EXTERNAL_PLUG             = 4,  // External Plug
    E_MSG_RECORD_TYPE_EXTERNAL_PHYSICAL_ADDRESS = 5,  // External Physical Address
#endif
} MsCEC_MSG_RECORD_SOURCE_TYPE;


typedef enum _MsCEC_MSG_RECORD_STATUS_INFO
{
    E_MSG_RECORD_INFO_RECORDING_OWN_SOURCE   = 0x01,  // Recording currently selected source
    E_MSG_RECORD_INFO_RECORDING_DIGITAL_SERVICE   = 0x02,  // Recording Digital Service
#if(HDMI_CEC_VERSION >= CEC_VERSION_13a)
    E_MSG_RECORD_INFO_RECORDING_ANALOGUE_SERVICE   = 0x03,  // Recording Analogue Service
    E_MSG_RECORD_INFO_RECORDING_EXTERNAL_INPUT   = 0x04,  // Recording External input
#endif
    E_MSG_RECORD_INFO_NO_RECORDING_DIGITAL_SERVICE   = 0x05,  // unable to record Digital Service, no suitable tuner.
#if(HDMI_CEC_VERSION >= CEC_VERSION_13a)
    E_MSG_RECORD_INFO_NO_RECORDING_ANALOGUE_SERVICE   = 0x06,  // unable to record Analogue Service, no suitable tuner.
    E_MSG_RECORD_INFO_NO_RECORDING_REQ_SERVICE   = 0x07,  // unable to select required service, Has suitable tuner, but the requested parameters are invalid or out of range for that tuner.
    E_MSG_RECORD_INFO_NO_RECORDING_INVALID_EXTERNAL_PLUG_NUMBER   = 0x09,  // invalid External plug number
    E_MSG_RECORD_INFO_NO_RECORDING_INVALID_EXTERNAL_PHYSICAL_ADDRESS   = 0x0A,  // invalid External Physical Address
    E_MSG_RECORD_INFO_NO_RECORDING_CA_NOT_SUPPORT   = 0x0B,  // CA system not supported
    E_MSG_RECORD_INFO_NO_RECORDING_CA_NO   = 0x0C,  // No or Insufficient CA Entitlements
    E_MSG_RECORD_INFO_NO_RECORDING_COPY_NEVER   = 0x0D,  // Not allowed to copy source, source is ¡§copy never¡¨.
    E_MSG_RECORD_INFO_NO_RECORDING_NO_FURTHER_COPY   = 0x0E,  // No further copies allowed
#endif
    E_MSG_RECORD_INFO_NO_RECORDING_NO_MEDIA   = 0x10,  // no media
    E_MSG_RECORD_INFO_NO_RECORDING_PLAYING   = 0x11,  // Playing
    E_MSG_RECORD_INFO_NO_RECORDING_ALREADY_RECORDING   = 0x12,  // already recording
    E_MSG_RECORD_INFO_NO_RECORDING_MEDIA_PROTECTED   = 0x13,  // media protected
    E_MSG_RECORD_INFO_NO_RECORDING_NO_SOURCE  = 0x14,  // no source signal
    E_MSG_RECORD_INFO_NO_RECORDING_MEDIA_PROBLEM  = 0x15,  // media problem
#if(HDMI_CEC_VERSION >= CEC_VERSION_13a)
    E_MSG_RECORD_INFO_NO_RECORDING_NOT_ENOUGH_SPACE  = 0x16,  // not enough space available
    E_MSG_RECORD_INFO_NO_RECORDING_PARENTAL_LOCK  = 0x17,  // Parental Lock On
    E_MSG_RECORD_INFO_RECORDING_TERMINATED_NORMALLY  = 0x1A,  // Recording terminated normally, can optionally be sent in response to a <Record Off> message.
    E_MSG_RECORD_INFO_RECORDING_ALREADY_TERMINATED  = 0x1B,  // Recording has already terminated, can optionally be sent in response to a <Record Off> message.
#endif
    E_MSG_RECORD_INFO_NO_RECORDING_OTHER_REASON  = 0x1F,  // No recording ¡V other reason
} MsCEC_MSG_RECORD_STATUS_INFO;


//UI command parameter: Table 27 User Control Codes
typedef enum _MsCEC_MSG_USER_CTRL_PARM
{
    E_MSG_UI_SELECT             = 0x00,
    E_MSG_UI_UP                 = 0x01,
    E_MSG_UI_DOWN               = 0x02,
    E_MSG_UI_LEFT               = 0x03,
    E_MSG_UI_RIGHT              = 0x04,
    E_MSG_UI_RIGHT_UP           = 0x05,
    E_MSG_UI_RIGHT_DOWN         = 0x06,
    E_MSG_UI_LEFT_UP            = 0x07,
    E_MSG_UI_LEFT_DOWN          = 0x08,
    E_MSG_UI_ROOTMENU           = 0x09,
    E_MSG_UI_SETUP_MENU         = 0x0A,
    E_MSG_UI_CONTENTS_MENU      = 0x0B,
    E_MSG_UI_FAVORITE_MENU      = 0x0C,
    E_MSG_UI_EXIT               = 0x0D,

// 0x0E ~ 0x1F  reserved

    E_MSG_UI_NUMBER_0           = 0x20,
    E_MSG_UI_NUMBER_1           = 0x21,
    E_MSG_UI_NUMBER_2           = 0x22,
    E_MSG_UI_NUMBER_3           = 0x23,
    E_MSG_UI_NUMBER_4           = 0x24,
    E_MSG_UI_NUMBER_5           = 0x25,
    E_MSG_UI_NUMBER_6           = 0x26,
    E_MSG_UI_NUMBER_7           = 0x27,
    E_MSG_UI_NUMBER_8           = 0x28,
    E_MSG_UI_NUMBER_9           = 0x29,

    E_MSG_UI_DOT                = 0x2A,
    E_MSG_UI_ENTER              = 0x2B,
    E_MSG_UI_CLEAR              = 0x2C,

// 0x2D ~ 0x2E reserved
    E_MSG_UI_NEXT_FAVORITE      = 0x2F,

    E_MSG_UI_CHANNEL_UP         = 0x30,
    E_MSG_UI_CHANNEL_DOWN       = 0x31,
    E_MSG_UI_PREVIOUS_CHANNEL   = 0x32,
    E_MSG_UI_SOUND_SELECT       = 0x33,
    E_MSG_UI_INPUT_SELECT       = 0x34,
    E_MSG_UI_DISPLAY_INFO       = 0x35,
    E_MSG_UI_HELP               = 0x36,
    E_MSG_UI_PAGE_UP            = 0x37,
    E_MSG_UI_PAGE_DOWN          = 0x38,

// 0x39 ~ 0x3F reserved

    E_MSG_UI_POWER              = 0x40,
    E_MSG_UI_VOLUME_UP          = 0x41,
    E_MSG_UI_VOLUME_DOWN        = 0x42,
    E_MSG_UI_MUTE               = 0x43,
    E_MSG_UI_PLAY               = 0x44,
    E_MSG_UI_STOP               = 0x45,
    E_MSG_UI_PAUSE              = 0x46,
    E_MSG_UI_RECORD             = 0x47,
    E_MSG_UI_REWIND             = 0x48,
    E_MSG_UI_FAST_FORWARD       = 0x49,
    E_MSG_UI_EJECT              = 0x4A,
    E_MSG_UI_FORWARD            = 0x4B,
    E_MSG_UI_BACKWARD           = 0x4C,
    E_MSG_UI_STOP_RECORD        = 0x4D,
    E_MSG_UI_PAUSE_RECORD       = 0x4E,

// 0x4F reserved

    E_MSG_UI_ANGLE                      = 0x50,
    E_MSG_UI_SUB_PICTURE                = 0x51,
    E_MSG_UI_VIDEO_ON_DEMAND            = 0x52,
    E_MSG_UI_ELECTRONIC_PROGRAM_GUIDE   = 0x53,
    E_MSG_UI_TIMER_PROGRAMMING          = 0x54,
    E_MSG_UI_INITIAL_CONFIGURATION      = 0x55,

// 0x56 ~ 0x5F reserved

  //0x60 ~ 0x6D, identified as function
    E_MSG_UI_PLAY_FUN               = 0x60,
    E_MSG_UI_PSUSE_PLAY_FUN         = 0x61,
    E_MSG_UI_RECORD_FUN             = 0x62,
    E_MSG_UI_PAUSE_RECORD_FUN       = 0x63,
    E_MSG_UI_STOP_FUN               = 0x64,
    E_MSG_UI_MUTE_FUN               = 0x65,
    E_MSG_UI_RESTORE_VOLUME_FUN     = 0x66,
    E_MSG_UI_TUNE_FUN               = 0x67,
    E_MSG_UI_SELECT_MEDIA_FUN       = 0x68,
    E_MSG_UI_SELECT_AV_INPUT_FUN    = 0x69,
    E_MSG_UI_SELECT_AUDIO_INPUT_FUN = 0x6A,
    E_MSG_UI_POWER_TOGGLE_FUN       = 0x6B,
    E_MSG_UI_POWER_OFF_FUN          = 0x6C,
    E_MSG_UI_POWER_ON_FUN           = 0x6D,

// 0x6E ~ 0x70 reserved

    E_MSG_UI_F1_BLUE            = 0x71,
    E_MSG_UI_F2_RED             = 0x72,
    E_MSG_UI_F3_GREEN           = 0x73,
    E_MSG_UI_F4_YELLOW          = 0x74,
    E_MSG_UI_F5                 = 0x75,
    E_MSG_UI_DATA               = 0x76,

// 0x77 ~ 0xFF reserved
} MsCEC_MSG_USER_CTRL_PARM;

//query the power on mode through mailbox
#define CP_READ_POWERON_MODE  0x9A

//mailbox report CEC wake up system
#define M_POWER_ON_BY_HDMI_CEC  0x2F


typedef struct _MDrv_Cec_RxData_Info
{
    MS_U8 ucLength;
    MS_U8 tRxData[16];
} MS_CEC_RxData_Info;

typedef struct _MDrv_CEC_INFO_LIST
{
    MS_U8 CecFifoIdxS;
    MS_U8 CecFifoIdxE;
    MS_U8 bCecMsgCnt;
    MS_BOOL fCecInitFinish;
    MS_CEC_RxData_Info CecRxBuf[CEC_FIFO_CNT];   //TV CEC H/W part
    MsCEC_DEVICELA MyLogicalAddress;                         //TV related
    MS_U8 MyPhysicalAddress[2];
    MsCEC_DEVICE_TYPE MyDeviceType;
    MsCEC_MSG_POWER_STATUS_PARM MyPowerStatus;
    MS_BOOL CecDevicesExisted[15];

    MS_U8 ActiveDeviceCECVersion;
    MsCEC_DEVICE_TYPE ActiveDeviceType;
    MsCEC_DEVICELA ActiveLogicalAddress;    //the remoter controller's active device
    MS_U8 ActivePhysicalAddress[2];
    MsCEC_MSG_POWER_STATUS_PARM ActivePowerStatus;

#if ENABLE_CEC_MULTIPLE
    MsCEC_DEVICELA MyLogicalAddress2;  
    MS_U8 MyPhysicalAddress2[2];
    MsCEC_DEVICE_TYPE MyDeviceType2;
    MsCEC_DEVICE_TYPE IniLogicalAddress;
#endif
} MS_CEC_INFO_LIST;

typedef struct
{
    MS_U32 u32XTAL_CLK_Hz;
}MS_CEC_INIT_INFO;



//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
/**
*   @brief HDMI Status
*/
typedef struct
{
    MS_BOOL bIsInitialized;
    MS_BOOL bIsRunning;
}MS_CEC_Status;

MS_BOOL  MApi_CEC_GetLibVer(const MSIF_Version **ppVersion);      ///< Get version (without Mutex protect)
MS_BOOL  MApi_DDC2BI_GetInfo(MS_CEC_INFO_LIST *pInfo);
MS_BOOL  MApi_DDC2BI_GetStatus(MS_CEC_Status *pStatus);
MS_BOOL  MApi_DDC2BI_SetDbgLevel(MS_U16 u16DbgSwitch);

void MApi_CEC_Exit(void);

//                  CEC initial sequence
void MApi_CEC_Init(MS_CEC_INIT_INFO *pCECInfo);

//                  CEC initial chip relatived part
void MApi_CEC_InitChip(MS_CEC_INIT_INFO *pCECInfo);

//                  CEC set own logical address
void MApi_CEC_SetMyLogicalAddress(MsCEC_DEVICELA myLA);

//                  Use to store CEC received messages
void MApi_CEC_ChkRxBuf(void);


//                   Use to send any CEC message by user defined
CEC_ERROR_CODE MApi_CEC_TxSendMsg(MsCEC_DEVICELA header,MsCEC_MSGLIST opcode,MS_U8* operand_ptr,MS_U8 len);

//                   Use to send CEC polling msg
CEC_ERROR_CODE MsAPI_CecTxSendPollingMsg(MsCEC_DEVICELA dst_address);

//*****************************//
//    One Touch Play &
//    Routing Control Feature
//*****************************//

//                   Used by a new source to indicate that it has started to transmit a stream or
//                   used in response to a <Request Active Source>
CEC_ERROR_CODE MApi_CEC_Msg_ActiveSource(void);


//*****************************//
//    Routing Control Feature
//*****************************//

//                   Used by a CEC switch when it's manually switched to inform akk other devices
CEC_ERROR_CODE MApi_CEC_Msg_RoutingChange(MS_U8* orig_address, MS_U8* new_address);

//                   Used by a new device to discover the status of the system.
CEC_ERROR_CODE MApi_CEC_Msg_ReqActiveSource(void);

//                   Used by the TV to request a streaming path from the specified physical address.
CEC_ERROR_CODE MApi_CEC_Msg_SetStreamPath(MS_U8* new_address);


//*****************************//
//    Standby Feature
//*****************************//

//                   Use to switch one or all devices into standby mode.
//                   One device: it's specific logical address, like "E_LA_RECORDER1"
//                   All device:   Use broadcast logical address, "E_LA_BROADCAST"
CEC_ERROR_CODE MApi_CEC_Msg_Standby(MsCEC_DEVICELA dst_address);


//*****************************//
//    On Touch Record
//*****************************//

//                   Requests a device to stop a recording.
CEC_ERROR_CODE MApi_CEC_Msg_RecordOff(MsCEC_DEVICELA dst_address);

//                   Attempt to record the specified source.
CEC_ERROR_CODE MsAPI_CEC_Msg_RecordOn(MsCEC_DEVICELA dst_address, MsCEC_MSG_RECORD_SOURCE_TYPE cmd);


//*****************************//
//    System Information Feature
//*****************************//

//                   Used to indicate the supported CEC version, in response to a <Get CEC Version>
CEC_ERROR_CODE MApi_CEC_Msg_ReportCECVersion(MsCEC_DEVICELA dst_address, MS_U8 version);

//                   Used by a device to enquire which version of CEC the target supports
CEC_ERROR_CODE MApi_CEC_Msg_ReqCECVersion(MsCEC_DEVICELA dst_address);

//                   Use to inform all other devices of the mapping between physical and logical address of the initiator
CEC_ERROR_CODE MApi_CEC_Msg_ReportPhycalAddress(void);

//                   A request to a device to return its physical address
CEC_ERROR_CODE MApi_CEC_Msg_ReqPhycalAddress(MsCEC_DEVICELA dst_address);


//*****************************//
//    Deck Control Feature
//*****************************//

//                   Use to control a device's media functions
CEC_ERROR_CODE MApi_CEC_Msg_DeckControl(MsCEC_DEVICELA dst_address, MsCEC_MSG_DC_DECK_CTRL_PARM cmd);

//                   Use to provide a device's status when received "Give Deck Status"
CEC_ERROR_CODE MApi_CEC_Msg_DecStatus(MsCEC_DEVICELA dst_address, MsCEC_MSG_DC_DECK_STATUS_PARM cmd);

//                   Use to request device's status
CEC_ERROR_CODE MApi_CEC_MSg_GiveDeckStatus(MsCEC_DEVICELA dst_address, MsCEC_MSG_STATUS_REQUEST_PARM cmd);

//                   Use to control the playback behaviour of a source device
CEC_ERROR_CODE MApi_CEC_MSg_DCPlay(MsCEC_DEVICELA dst_address, MsCEC_MSG_DC_PLAY_PARM cmd);


//*****************************//
//    Device Menu Control &
//    Remote Control Passthrough Feature
//*****************************//

//                   Request from TV for a device to show/remove a menu or to query status
CEC_ERROR_CODE MApi_CEC_Msg_ReqMenuStatus(MsCEC_DEVICELA dst_address, MsCEC_MSG_MENU_REQ_TYPE cmd);

//                   Use to indicated that user pressed which control button
CEC_ERROR_CODE MApi_CEC_Msg_UserCtrlPressed(MS_BOOL bUserCtrlEn, MsCEC_DEVICELA dst_address, MsCEC_MSG_USER_CTRL_PARM cmd);

//                   Use to indicated that user released which control button
CEC_ERROR_CODE MApi_CEC_Msg_UserCtrlReleased(MsCEC_DEVICELA dst_address);


//*****************************//
//    Power Status Feature
//*****************************//

//                   Use to inform a requesting device of the current power status
CEC_ERROR_CODE MApi_CEC_Msg_ReportPowerStatus(MsCEC_DEVICELA dst_address);


//                   Use to determine the current power status of a target device
CEC_ERROR_CODE MApi_CEC_Msg_ReqPowerStatus(MsCEC_DEVICELA dst_address);


//*****************************//
//    General Protocol Feature
//*****************************//

//                   Use to indicate that device doesn't support message type
CEC_ERROR_CODE MApi_CEC_Msg_FeatureAbort(MsCEC_DEVICELA dst_address, MsCEC_MSGLIST msg, MsCEC_MSG_ABORT_REASON cmd);

//                   This message is reserved for testing purposes.
CEC_ERROR_CODE MApi_CEC_Msg_Abort(MsCEC_DEVICELA dst_address);

//
CEC_ERROR_CODE MApi_CEC_Msg_SendMenuLanguage(MS_U8* pu8MenuLanguageCode);

CEC_ERROR_CODE MsAPI_CecMsg_ReqARCInitiation(MsCEC_DEVICELA dst_address);
CEC_ERROR_CODE MsAPI_CecMsg_ReqARCTermination(MsCEC_DEVICELA dst_address);
CEC_ERROR_CODE MsAPI_CecMsg_AudioModeReq(MsCEC_DEVICELA dst_address, MS_BOOL amp_switch, MS_U8* my_address );
CEC_ERROR_CODE MApi_CEC_Msg_GiveAudioStatus(MsCEC_DEVICELA dst_address);

MS_U8 MApi_CEC_Get_Header(void);
MS_U8 MApi_CEC_Get_OpCode(void);
MS_U8 MApi_CEC_Get_Para(MS_U8 u8Idx);
MS_U8 MApi_CEC_GetCmdLen(void);
void MApi_CEC_SetActiveLogicalAddress(MsCEC_DEVICELA Addr);
MsCEC_DEVICELA MApi_CEC_GetActiveLogicalAddress(void);

MsCEC_MSG_POWER_STATUS_PARM MApi_CEC_GetPowerStatus(void);
MS_U8 MApi_CEC_GetFifoIdx(void);
void MApi_CEC_SetFifoIdx(MS_U8 u8Idx);

void MApi_CEC_SetActivePowerStatus(MsCEC_MSG_POWER_STATUS_PARM Status);
MsCEC_MSG_POWER_STATUS_PARM MApi_CEC_GetActivePowerStatus(void);

void MApi_CEC_SetActivePhysicalAddress(MS_U8 u8Para1, MS_U8 u8Para2);
void MApi_CEC_SetActiveDeviceCECVersion(MS_U8 u8Ver);
void MApi_CEC_SetActiveDeviceType(MsCEC_DEVICE_TYPE Type);

MS_U8 MApi_CEC_GetMsgCnt(void);
void MApi_CEC_SetMsgCnt(MS_U8 u8Cnt);

MS_U8 MApi_CEC_GetRxData(MS_U8 u8Fifoidx, MS_U8 u8Idx);
MS_BOOL MApi_CEC_CheckFrame(MsCEC_MSG_TRANS_TYPE msg_type, MS_U8 ucLen);
void MApi_CEC_CheckExistDevices(void);
void MApi_CEC_ConfigWakeUp(void);
void MApi_CEC_Enabled(MS_BOOL bEnableFlag);
void MApi_CEC_SetMyPhysicalAddress(MS_U8 *pdata);
#if ENABLE_CEC_MULTIPLE
void MApi_CEC_SetMyLogicalAddress2(MsCEC_DEVICELA myLA);
CEC_ERROR_CODE MApi_CEC_Msg_ReportPhycalAddress2(void);
void MApi_CEC_SetMyPhysicalAddress2(MS_U8 *pdata);
void MApi_CEC_SetInitiator(MsCEC_DEVICELA IniLA);
#endif
//[Bit0]: CEC receives a new message.
//[Bit1]: CEC transmits a message successfully.
//[Bit2]: CEC retry fail for TX.
//[Bit3]: CEC lost arbitration to the second initiator.
MS_U8 MApi_CEC_GetTxStatus(void);

#ifdef __cplusplus
}
#endif

#endif //_API_CEC_H_

