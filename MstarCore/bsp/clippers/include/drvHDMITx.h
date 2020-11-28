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
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvHDMITx.h
/// @author MStar Semiconductor Inc.
/// @brief  HDMI Tx Driver Interface
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_HDMITX_H_
#define _DRV_HDMITX_H_


#ifdef __cplusplus
extern "C"
{
#endif

#include "halHDMITx.h"
#ifdef CUSTOMER_NDS
#include "apiHDMITx_NDS.h"
#endif // CUSTOMER_NDS

//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

#ifdef MSOS_TYPE_LINUX_KERNEL
#define HDMITX_ISR_ENABLE              1
#else
#define HDMITX_ISR_ENABLE              1
#endif

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

//*********************//
//        DVI / HDMI   //
//*********************//

/*
       Bit1:
          - 0: DVI
          - 1: HDMI
       Bit0:
          - 0: without HDCP
          - 1: with HDCP
*/
typedef enum
{
    E_HDMITX_DVI            = 0,  // DVI without HDCP
    E_HDMITX_DVI_HDCP       = 1,  // DVI with HDCP
    E_HDMITX_HDMI           = 2,  // HDMI without HDCP
    E_HDMITX_HDMI_HDCP      = 3,  // HDMI with HDCP
} MsHDMITX_OUTPUT_MODE;

typedef enum
{
    E_HDMITX_EVENT_RUN = 0x00000001,
    E_HDMITX_EVENT_IRQ = 0x00000002,
    E_HDMITX_EVENT_RITIMER = 0x00000004,
    E_HDMITX_EVENT_RXTIMER = 0x00000008,
    E_HDMITX_EVENT_CECRX = 0x00000010,
} MDrvHDMITXEvent;


typedef enum
{
    E_HDMITX_FSM_PENDING                    = 0,
    E_HDMITX_FSM_CHECK_HPD                  = 1,
    E_HDMITX_FSM_VALIDATE_EDID              = 2,
    E_HDMITX_FSM_HDCP_AUTH_WAIT_RX          = 3,
    E_HDMITX_FSM_HDCP_AUTH_CHECK_R0         = 4,
    E_HDMITX_FSM_HDCP_AUTH_CHECK_REPEATER   = 5,
    E_HDMITX_FSM_HDCP_AUTH_DONE             = 6,
    E_HDMITX_FSM_HDCP_AUTH_FAIL             = 7,
} MDrvHDMITX_FSM_STATE;

typedef enum
{
    E_NORMAL_OUTPUT      = 0, // still display normally
    E_HDCP_ENCRYPTION = 1, // HDCP encryption to show snow screen
    E_BLUE_SCREEN = 2, // blue screen
} MDrvHDMITX_UNHDCPRX_CONTROL;

typedef enum
{
    E_CHECK_NOT_READY = 0,
    E_CHECK_REVOKED = 1,
    E_CHECK_NOT_REVOKED = 2,
}MDrvHDMITX_REVOCATION_STATE;

typedef enum
{
    E_RXFail_NORMAL_OUTPUT      = 0, // still display normally
    E_RXFail_HDCP_ENCRYPTION = 1, // HDCP encryption to show snow screen
    E_RXFail_BLUE_SCREEN = 2, // blue screen
} MDrvHDMITX_HDCPRXFail_CONTROL;

typedef enum
{
    E_HDMITX_HDCP_RESET                                = 0x01,
    E_HDMITX_HDCP_WAITING_ACTIVE_RX 	     = 0x02,
    E_HDMITX_HDCP_CHECK_REPEATER_READY = 0x03,
    E_HDMITX_HDCP_CHECK_R0 			     = 0x04,
    E_HDMITX_HDCP_AUTH_DONE 			     = 0x05,
    E_HDMITX_HDCP_AUTH_FAIL 			     = 0x06,

    // bit[7:6]=00 for checking valid rx
    E_HDMITX_HDCP_RX_IS_NOT_VALID		= 0x00, // 00 00
    E_HDMITX_HDCP_RX_IS_VALID         = 0x10, // 00 01
    E_HDMITX_HDCP_RX_KEY_FAIL			= 0x20, // 00 10
    E_HDMITX_HDCP_TX_KEY_FAIL         = 0x30, // 00 11
    E_HDMITX_HDCP_RX_KEY_REVOKED        = 0x0F, // 00 00 11 11

    // bit[7:6]=01 for repeater
    E_HDMITX_HDCP_REPEATER_TIMEOUT 	= 0x40, // 01 00
    E_HDMITX_HDCP_REPEATER_READY 		= 0x50, // 01 01
    E_HDMITX_HDCP_REPEATER_NOT_READY 	= 0x60, // 01 10
    E_HDMITX_HDCP_REPEATER_VALID 		= 0x70, // 01 11

    // bit[7:6]=10 for SHA1
    E_HDMITX_HDCP_REPEATER_SHA1_FAIL 	= 0x80, // 10 00
    E_HDMITX_HDCP_REPEATER_SHA1_PASS 	= 0x90, // 10 01

    // bit[7:6]=11 for Ri
    E_HDMITX_HDCP_SYNC_RI_FAIL 		    = 0xC0, // 11 00
    E_HDMITX_HDCP_SYNC_RI_PASS 		    = 0xD0  // 11 01
}MsHDMITX_HDCP_AUTH_STATUS;

typedef struct
{
    MS_BOOL                            hdmitx_enable_flag;     ///< hdmitx module actived
    MS_BOOL                            hdmitx_tmds_flag;       ///< hdmitx tmds on/off
    MS_BOOL                            hdmitx_video_flag;      ///< hdmitx video on/off
    MS_BOOL                            hdmitx_audio_flag;      ///< hdmitx audio on/off
    MS_BOOL                            hdmitx_hdcp_flag;       ///< hdmitx hdcp encryption on/off
    MS_BOOL                            hdmitx_csc_flag;        ///< hdmitx csc on/off
    MS_BOOL                            hdmitx_audio_supportAI; ///< hdmitx audio support AI
    MS_BOOL                            hdmitx_RB_swap_flag;    ///< hdmitx R/B swap
    MS_BOOL                            hdmitx_force_mode;     ///< hdmitx output force mode: auto/force
    MS_BOOL                            hdmitx_force_output_color;     ///< hdmitx output force color format: auto/force
    MS_BOOL                            hdmitx_AFD_override_mode;     ///< hdmitx AFD override mode: auto/override
    MS_BOOL                            hdmitx_edid_ready;  ///< hdmitx get ready to Rx's EDID
    MS_BOOL                            hdmitx_avmute_flag;     ///< hdmitx AVMUTE status

    // HDCP
    MS_BOOL                            hdmitx_HdcpUseInternalKey_flag;    ///< hdmitx HDCP key source
    MS_BOOL                            hdmitx_HdcpStartAuth_flag;    ///< hdmitx HDCP start authentication flag
    MS_BOOL                            hdmitx_HdcpAuthDone_flag;    ///< hdmitx HDCP authentication done flag
    MS_BOOL                            hdmitx_HdcpCheckRepeater_flag;    ///< hdmitx HDCP check repeater flag

    // CEC
    MS_BOOL                            hdmitx_CECEnable_flag;    ///< hdmitx CEC enable flag

    MDrvHDMITX_FSM_STATE               hdmitx_fsm_state;       ///< hdmitx fsm state
    MDrvHDMITX_FSM_STATE               hdmitx_fsm_prestate;       ///< hdmitx fsm pre-state
    MsHDMITX_RX_STATUS                 hdmitx_preRX_status;  ///< hdmitx previous Rx status
    MsHDMITX_HDCP_AUTH_STATUS          hdmitx_HDCPAuth_Status;  ///< hdmitx HDCP authentication status
    MDrvHDMITX_UNHDCPRX_CONTROL        hdmitx_unHDCPRx_Control;  ///< hdmitx unHDCP Rx ouput way
    MDrvHDMITX_HDCPRXFail_CONTROL      hdmitx_HDCPRxFail_Control; ///< hdmitx HDCP Rx fail output way

    MsHDMITX_OUTPUT_MODE               output_mode;            ///< output DVI / HDMI mode
    MsHDMITX_OUTPUT_MODE               force_output_mode;            ///< output DVI / HDMI mode
    MsHDMITX_VIDEO_COLORDEPTH_VAL      output_colordepth_val;    // output video color depth
    MsHDMITX_VIDEO_COLORDEPTH_VAL      edid_colordepth_val;    // EDID video color depth
    MsHDMITX_VIDEO_TIMING              output_video_timing;    ///< output video timing
    MsHDMITX_VIDEO_TIMING              output_video_prevtiming;    ///< output video previous timing
    MsHDMITX_VIDEO_COLOR_FORMAT        input_color;            ///< RGB444 / YUV444
    MsHDMITX_VIDEO_COLOR_FORMAT        output_color;           ///< RGB444 / YUV444
    MsHDMITX_VIDEO_COLOR_FORMAT        force_output_color;            ///< RGB444 / YUV444
    MsHDMITX_VIDEO_ASPECT_RATIO        output_aspect_ratio;    // Aspect ratio
    MsHDMITX_VIDEO_SCAN_INFO           output_scan_info; // overscan / underscan
    MsHDMITX_VIDEO_AFD_RATIO           output_afd_ratio; // AFD
    MS_U8		                       output_activeformat_present; // Active format information present
    MsHDMITX_AUDIO_FREQUENCY           output_audio_frequncy;  ///< audio sampling frequency
    MsHDMITX_AUDIO_CHANNEL_COUNT       output_audio_channel;   // audio channel count
    MsHDMITX_AUDIO_CODING_TYPE         output_audio_type;    // audio coding type
    MS_U8                              edid_phyadr[2];    // EDID physical address
    MS_U8                              hdcp_srmlist[5116]; // maximum length of the 1st generation
    MS_U8                              hdcp_revocationlist[5068]; // 5x max number of device
    MS_BOOL                            revocationlist_ready; // revocationlist update flag
    MS_U8                              revocation_size;
    MDrvHDMITX_REVOCATION_STATE        revocation_state; // revocation check state
    MS_U8	                           short_video_descriptor[32]; // short video descriptor of EDID
    MS_U8                              short_audio_descriptor[32]; // short audio descriptor of EDID
    MS_U8                              data_block_length[8]; // data block length of each data block
    MS_U8	                           id_manufacturer_name[3]; // ID Manufacturer Name
    MS_U8                              edid_block0[128]; //EDID's 1st 128 data
    MS_U8                              edid_block1[128]; //EDID's 2nd 128 data
#ifdef CUSTOMER_NDS
    MS_U32 events;
    MS_U32     hdcp_encryptionStartTime;
    MS_BOOL   hdcp_checkPjIntegrity;
#endif
    MsHDMITX_ANALOG_TUNING             analog_setting;        // HDMI Tx Pre-emphasis and Double termination
    MsHDMITX_VIDEO_VS_FORMAT           vs_pkt_format;       // VS packet video format
    MsHDMITX_VIDEO_3D_STRUCTURE        vs_pkt_3d;        // VS packet 3d structur
    MsHDMITX_VIDEO_4k2k_VIC            vs_4k2k_vic;          // VS packet 3d structur
    MS_BOOL                            edid_2D_50hz_support;
	MS_BOOL                            edid_2D_60hz_support;
    MS_BOOL                            edid_3D_50hz_support;
	MS_BOOL                            edid_3D_60hz_support;
	MS_BOOL                            edid_3D_present;
	MS_BOOL                            edid_HDMI_support;
	MsHDMITX_EDID_3D_SUPPORT_TIMING    edid_3D_support_timing[32];
    MS_U8                              HDCP_AKSV[5];
    MS_U8                              HDCP_BKSV[5];
	MS_BOOL                            HDCP_74_check;
} MDrvHDMITX_PARAMETER_LIST;

// debug mask definition
#define HDMITX_DBG              0x01///< Debug PQ Table
#define HDMITX_DBG_HDCP         0x02///< Debug S RULE
#define HDMITX_DBG_UTILTX       0x04///< Debug S RULE

//-------------------------------------------------------------------------------------------------
//  Function Prototype
//-------------------------------------------------------------------------------------------------
#ifdef MDRV_HDMITX_C
#define INTERFACED
#else
#define INTERFACED extern
#endif

INTERFACED MS_BOOL MDrv_HDMITx_Init(void);

// HDMI Tx get HDCP key
INTERFACED void MDrv_HDMITx_GetHdcpKey(MS_BOOL useinternalkey, MS_U8 *data);

// HDMI Tx clock power On/Off
INTERFACED void MDrv_HDMITx_Power_OnOff(MS_BOOL bEnable);

// HDMI Tx module On/Off
INTERFACED void MDrv_HDMITx_TurnOnOff(void);

// HDMI Tx output is DVI / HDMI mode
INTERFACED void MDrv_HDMITx_SetHDMITxMode(void);

// HDMI Tx TMDS signal On/Off
INTERFACED void MDrv_HDMITx_SetTMDSOnOff(void);

// This routine set video output On/Off
INTERFACED void MDrv_HDMITx_SetVideoOnOff(void);

// This routine set video color format
INTERFACED void MDrv_HDMITx_SetColorFormat(void);

// This routine set VS infoframe content for 3D or 4k2k
INTERFACED void MDrv_HDMITx_Set_VS_InfoFrame(void);

// This routine set video output mode (color/repetition/regen)
INTERFACED void MDrv_HDMITx_SetVideoOutputMode(void);

// This routine set video aspect ratio
INTERFACED void MDrv_HDMITx_SetVideoOutputAsepctRatio(void);

// This routine set video scan info and AFD
INTERFACED void MDrv_HDMITx_SetVideoOutputOverscan_AFD(void);

// This routine turn On/off Audio module.
INTERFACED void MDrv_HDMITx_SetAudioOnOff(void);

// This routine set audio sampling freq.
INTERFACED void MDrv_HDMITx_SetAudioFrequency(void);

// This routine get audio CTS value.
INTERFACEE MS_U32 MDrv_HDMITx_GetAudioCTS(void);

// This routine mute audio FIFO.
INTERFACEE void MDrv_HDMITx_MuteAudioFIFO(MS_BOOL bflag);

// This routine set HDMI Tx HDCP encryption On/Off
INTERFACED void MDrv_HDMITx_SetHDCPOnOff(void);

// This routine set HDMI Tx audio sorce format
INTERFACED void MDrv_HDMITx_SetAudioSourceFormat(MsHDMITX_AUDIO_SOURCE_FORMAT fmt);

INTERFACED void MDrv_HDMITx_Exhibit(void);

// This routine control HDMI packet generation
INTERFACED void MDrv_HDMITx_EnablePacketGen(MS_BOOL bflag);
// This routine force HDMITx output mode
INTERFACED void MDrv_HDMITx_ForceHDMIOutputMode(MS_BOOL bflag, MsHDMITX_OUTPUT_MODE output_mode);

// This routine force HDMITx output color format
INTERFACED MS_BOOL MDrv_HDMITx_ForceHDMIOutputColorFormat(MS_BOOL bflag, MsHDMITX_VIDEO_COLOR_FORMAT output_color);

// This routine set HDMI Tx AVMUTE
INTERFACED void MDrv_HDMITx_SetAVMUTE(MS_BOOL bflag);

// This routine check and set the related format by EDID
INTERFACED MS_BOOL MDrv_HDMITx_EdidChecking(void);

// This routine gets Rx's supported 3D structures of specific timing from EDID
INTERFACED MS_BOOL MDrv_HDMITx_GetRx3DStructureFromEDID(MsHDMITX_VIDEO_TIMING timing, MsHDMITX_EDID_3D_STRUCTURE_ALL *p3DStructure);

// This function do the RxBypass mode related setting
INTERFACED MS_BOOL MDrv_HDMITx_RxBypass_Mode(MsHDMITX_INPUT_FREQ freq, MS_BOOL bflag);

// This function disable RxBypass mode
INTERFACED MS_BOOL MDrv_HDMITx_Disable_RxBypass(void);

// This function clear settings of user defined packet
INTERFACEE void MDrv_HDMITx_PKT_User_Define_Clear(void);

// This function set user defined hdmi packet
INTERFACEE void MDrv_HDMITx_PKT_User_Define(MsHDMITX_PACKET_TYPE packet_type, MS_BOOL def_flag,
MsHDMITX_PACKET_PROCESS def_process, MS_U8 def_fcnt);

// This function let user define hdmi packet content
INTERFACEE MS_BOOL MDrv_HDMITx_PKT_Content_Define(MsHDMITX_PACKET_TYPE packet_type, MS_U8* data, MS_U8 length);

// The function to set the time interval from sent aksv to R0.
INTERFACEE void MDrv_HDMITx_SetAksv2R0Interval(MS_U32 u32Interval);

// The function start/stop HDCP authentication
INTERFACEE void MDrv_HDMITx_HDCP_StartAuth(MS_BOOL bFlag);

// Debug
/**
*   @brief HDMI Info
*/
typedef struct
{
    MS_U8 Reserved;
}MS_HDMI_TX_INFO;

/**
*   @brief HDMI Status
*/
typedef struct
{
    MS_BOOL bIsInitialized;
    MS_BOOL bIsRunning;
}MS_HDMI_TX_Status;

MS_BOOL  MDrv_HDMITx_GetLibVer(const MSIF_Version **ppVersion);      ///< Get version (without Mutex protect)
MS_BOOL  MDrv_HDMITx_GetInfo(MS_HDMI_TX_INFO *pInfo);
MS_BOOL  MDrv_HDMITx_GetStatus(MS_HDMI_TX_Status *pStatus);

/**
* @brief set debug mask
* @param[in] u16DbgSwitch DEBUG MASK,
*   0x01: Debug HDMITX,
*   0x02: Debug HDCP
*/
MS_BOOL  MDrv_HDMITx_SetDbgLevel(MS_U16 u16DbgSwitch);

void MDrv_HDMITx_SetHPDGpioPin(MS_U8 u8pin);
MS_BOOL MDrv_HDMITx_IsHDCPRxValid(void);
MS_BOOL MDrv_HDMITx_IsSupportDVIMode(void);
void MDrv_HDMITx_HDCP_RevocationKey_List(MS_U8 *data, MS_U16 size);
MDrvHDMITX_REVOCATION_STATE MDrv_HDMITx_HDCP_RevocationKey_Check(void);

// *************  For customer NDS **************//
MS_BOOL MDrv_HDMITx_GetRxStatus(void);
MS_BOOL MDrv_HDMITx_HDCP_IsSRMSignatureValid(MS_U8 *data, MS_U32 size);
MS_BOOL MDrv_HDMITx_HDCP_CheckRevokedKey(void);
#ifdef CUSTOMER_NDS
void MDrv_HDMITx_EnableRxStatusChecking(MS_BOOL bflag);
MS_BOOL MDrv_HDMITx_EdidReadBlock(MS_U8 num, MS_U8 *data);
void MDrv_HDMITx_Set_AVI_InfoFrame(MsHDMITX_AVI_CONTENT_TYPE content_type, MS_U16 *data);
void MDrv_HDMITx_Set_AVMUTE(MS_BOOL bflag);
MS_BOOL MDrv_HDMITx_HDCP_Get_BCaps(MS_U8 *u8bcaps);
MS_BOOL MDrv_HDMITx_HDCP_Get_BStatus(MS_U16 *u16bstatus);
void MDrv_HDMITx_HDCP_Reset_SRM(void);
MS_BOOL MDrv_HDMITx_HDCP_Start_Authentication(void);
MS_BOOL MDrv_HDMITx_HDCP_Stop_Authentication(void);
void MDrv_HDMITx_HdcpSetEncrypt(MS_BOOL bflag);
void MDrv_HDMITx_HDCP_Get_HDCP_Status(MS_U8 *status);
void MDrv_HDMITx_HDCP_Configure(HDMIHDCPConfiguration *arg);
void MDrv_HDMITx_FSM_ChangeState(MDrvHDMITX_FSM_STATE state);
#endif

#ifdef __cplusplus
}
#endif

#endif // _DRV_HDMITX_H_

