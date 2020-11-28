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
/// @file   apiHDMITx.h
/// @brief  HDMITx Interface
/// @author MStar Semiconductor Inc.
///
///  CL351033++:
///   Add CEC function for STB
///  CL310477++:
///   Open analog setting for the different board condition
///  CL309397++:
///   Modify apiHDMITx prototype for NDS
///  CL308729++:
///   Fix AVMUTE problem while HDCP is on
///  CL299817++:
///  i. Add I2C timeout mechanism in EDID and HDCP
///  ii. Add SET_AVMUTE API to avoid transition garbage noise while timing changed ]]>
///  CL288415++:
///   Add SRM DSA Signature Checking function
///  CL283331++:
///   Fix HDMI v1.3 deep color mode output unstable problem
///  CL282607++:
///   i. Fix YUV422 / YUV444 bugs
///   ii. Add MApi_HDMITx_GetHdcpKey() to get HDCP key from external storage.
///  CL276751++:
///   Modify HDMI / HDCP state mechine for NDS
///  CL275230++:
///   i. MApi_HDMITx_GetRxDCInfoFromEDID() to get Rx's deep color information from EDID
///   ii. MApi_HDMITx_SetHDMITxMode_CD() to set output mode and deep color setting
///  CL266666++:
///   Add event report for NDS
///  CL263961++:
///   Add CEC init and checkbuffer for NDS
///  CL260934++:
///   Add some customized APIs for NDS
///  CL259645++:
///   i. Remove EDID header check. If header is wrong, force to DVI output
///   ii. Add force output mode "MApi_HDMITx_ForceHDMIOutputMode()"
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _API_HDMITX_H_
#define _API_HDMITX_H_

#include "MsTypes.h"
//#include "halHDMITx.h"
//#include "drvHDMITx.h"
//#include "regHDMITx.h"



#ifdef __cplusplus
extern "C"
{
#endif


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
#define MSIF_HDMITX_LIB_CODE               {'H','D','M','I'}
#define MSIF_HDMITX_LIBVER                 {'0','0'}
#define MSIF_HDMITX_BUILDNUM               {'1','1'}
#define MSIF_HDMITX_CHANGELIST             {'0','0','4','2','5','6','2','8'}
#define HDMITX_API_VERSION              /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_HDMITX_LIB_CODE,                  /* IP__                                             */  \
    MSIF_HDMITX_LIBVER,                    /* 0.0 ~ Z.Z                                        */  \
    MSIF_HDMITX_BUILDNUM,                  /* 00 ~ 99                                          */  \
    MSIF_HDMITX_CHANGELIST,                /* CL#                                              */  \
    MSIF_OS

typedef enum
{
    HDMITX_DVI            = 0,  // DVI without HDCP
    HDMITX_DVI_HDCP       = 1,  // DVI with HDCP
    HDMITX_HDMI           = 2,  // HDMI without HDCP
    HDMITX_HDMI_HDCP      = 3,  // HDMI with HDCP
} HDMITX_OUTPUT_MODE;

typedef enum
{
    HDMITX_VIDEO_CD_NoID     = 0, // DVI mode
    HDMITX_VIDEO_CD_24Bits     = 4, // HDMI 8 bits
    HDMITX_VIDEO_CD_30Bits     = 5, // HDMI 10 bits
    HDMITX_VIDEO_CD_36Bits     = 6, // HDMI 12 bits
} HDMITX_VIDEO_COLORDEPTH_VAL;

typedef enum
{
    HDMITX_VIDEO_COLOR_RGB444     = 0,
    HDMITX_VIDEO_COLOR_YUV422     = 1,
    HDMITX_VIDEO_COLOR_YUV444     = 2,
} HDMITX_VIDEO_COLOR_FORMAT;

typedef enum
{
    HDMITX_RES_640x480p        =0,
    HDMITX_RES_720x480i         = 1,
    HDMITX_RES_720x576i         = 2,
    HDMITX_RES_720x480p         = 3,
    HDMITX_RES_720x576p         = 4,
    HDMITX_RES_1280x720p_50Hz   = 5,
    HDMITX_RES_1280x720p_60Hz   = 6,
    HDMITX_RES_1920x1080i_50Hz  = 7,
    HDMITX_RES_1920x1080i_60Hz  = 8,
    HDMITX_RES_1920x1080p_24Hz  = 9,
    HDMITX_RES_1920x1080p_25Hz  = 10,
    HDMITX_RES_1920x1080p_30Hz  = 11,
    HDMITX_RES_1920x1080p_50Hz  = 12,
    HDMITX_RES_1920x1080p_60Hz  = 13,
    HDMITX_RES_MAX              = 14,
} HDMITX_VIDEO_TIMING;

typedef enum
{
    HDMITX_VIDEO_AR_Reserved    = 0,
    HDMITX_VIDEO_AR_4_3         = 1,
    HDMITX_VIDEO_AR_16_9        = 2,
} HDMITX_VIDEO_ASPECT_RATIO;

typedef enum
{
    HDMITX_VIDEO_SI_NoData    = 0,
    HDMITX_VIDEO_SI_Overscanned         = 1,
    HDMITX_VIDEO_SI_Underscanned        = 2,
    HDMITX_VIDEO_SI_Reserved    = 3,
} HDMITX_VIDEO_SCAN_INFO;

typedef enum
{
    HDMITX_VIDEO_AFD_SameAsPictureAR    = 8, // 1000
    HDMITX_VIDEO_AFD_4_3_Center         = 9, // 1001
    HDMITX_VIDEO_AFD_16_9_Center        = 10, // 1010
    HDMITX_VIDEO_AFD_14_9_Center        = 11, // 1011
    HDMITx_VIDEO_AFD_Others = 15, // 0000~ 0111, 1100 ~ 1111
} HDMITX_VIDEO_AFD_RATIO;

typedef enum
{
    HDMITX_AUDIO_FREQ_NO_SIG  = 0,
    HDMITX_AUDIO_32K          = 1,
    HDMITX_AUDIO_44K          = 2,
    HDMITX_AUDIO_48K          = 3,
    HDMITX_AUDIO_88K          = 4,
    HDMITX_AUDIO_96K          = 5,
    HDMITX_AUDIO_176K         = 6,
    HDMITX_AUDIO_192K         = 7,
    HDMITX_AUDIO_FREQ_MAX_NUM = 8,
} HDMITX_AUDIO_FREQUENCY;

typedef enum
{
    HDMITX_AUDIO_CH_2  = 2, // 2 channels
    HDMITX_AUDIO_CH_8  = 8, // 8 channels
} HDMITX_AUDIO_CHANNEL_COUNT;

typedef enum
{
    HDMITX_AUDIO_PCM        = 0, // PCM
    HDMITX_AUDIO_NONPCM     = 1, // non-PCM
} HDMITX_AUDIO_CODING_TYPE;

typedef struct
{
    MS_U8 Reserved;
}HDMI_TX_INFO;

typedef struct
{
    MS_BOOL bIsInitialized;
    MS_BOOL bIsRunning;
}HDMI_TX_Status;

typedef struct
{
    // HDMI Tx Current, Pre-emphasis and Double termination
    MS_U8    tm_txcurrent; // TX current control(U4: 0x11302B[13:12], K1: 0x11302B[13:11])
    MS_U8    tm_pren2; // pre-emphasis mode control, 0x11302D[5]
    MS_U8    tm_precon; // TM_PRECON, 0x11302E[7:4]
    MS_U8    tm_pren; // pre-emphasis enable, 0x11302E[11:8]
    MS_U8    tm_tenpre; // Double termination pre-emphasis enable, 0x11302F[3:0]
    MS_U8    tm_ten; // Double termination enable, 0x11302F[7:4]
} HDMITX_ANALOG_TUNING;

typedef enum
{
    E_HDCP_DISABLE      = 0, // HDCP disable
    E_HDCP_FAIL = 1, // HDCP fail
    E_HDCP_PASS = 2, // HDCP pass
} HDMITX_HDCP_STATUS;

typedef enum
{
    E_UNHDCPRX_NORMAL_OUTPUT      = 0, // still display normally
    E_UNHDCPRX_HDCP_ENCRYPTION = 1, // HDCP encryption to show snow screen
    E_UNHDCPRX_BLUE_SCREEN = 2, // blue screen
} HDMITX_UNHDCPRX_CONTROL;

typedef enum
{
    E_HDCPRXFail_NORMAL_OUTPUT      = 0, // still display normally
    E_HDCPRXFail_HDCP_ENCRYPTION = 1, // HDCP encryption to show snow screen 
    E_HDCPRXFail_BLUE_SCREEN = 2, // blue screen
} HDMITX_HDCPRXFail_CONTROL;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------


//*********************//
//        DVI / HDMI           //
//*********************//

MS_BOOL MApi_HDMITx_Init(void);

MS_BOOL MApi_HDMITx_Exit(void);


// HDMI Tx module On/Off
/*
    Before turn on HDMI TX module, video and audio source should be prepared ready and set the following APIs first.
        {
            ...
            MApi_HDMITx_TurnOnOff(TRUE);
            MApi_HDMITx_SetRBChannelSwap(TRUE);
            MApi_HDMITx_SetColorFormat(HDMITX_VIDEO_COLOR_YUV444, HDMITX_VIDEO_COLOR_RGB444);
            MApi_HDMITx_SetVideoOnOff(TRUE);
            MApi_HDMITx_SetHDMITxMode_CD(HDMITX_HDMI, HDMITX_VIDEO_CD_24Bits);
            MApi_HDMITx_SetVideoOutputTiming(HDMITX_RES_1920x1080p_60Hz);
            MApi_HDMITx_Exhibit();
            ...
        }

*/
void MApi_HDMITx_TurnOnOff(MS_BOOL state);

// HDMI Tx output is DVI / HDMI mode
void MApi_HDMITx_SetHDMITxMode(HDMITX_OUTPUT_MODE mode);

// HDMI Tx output is DVI / HDMI mode and color depth
void MApi_HDMITx_SetHDMITxMode_CD(HDMITX_OUTPUT_MODE mode, HDMITX_VIDEO_COLORDEPTH_VAL val);

// HDMI Tx TMDS signal On/Off
void MApi_HDMITx_SetTMDSOnOff(MS_BOOL state);

// HDMI Tx R/B channel swap
void MApi_HDMITx_SetRBChannelSwap(MS_BOOL state);

// HDMI Tx Exhibit funtcion
void MApi_HDMITx_Exhibit(void);

// HDMI Tx force output mode
void MApi_HDMITx_ForceHDMIOutputMode(MS_BOOL bflag, HDMITX_OUTPUT_MODE output_mode);

// Get the connected HDMI Rx status
MS_BOOL MApi_HDMITx_GetRxStatus(void);

// Get Rx's deep color definition from EDID
MS_BOOL MApi_HDMITx_GetRxDCInfoFromEDID(HDMITX_VIDEO_COLORDEPTH_VAL *val);

// Get Rx's support video format from EDID
MS_BOOL MApi_HDMITx_GetRxVideoFormatFromEDID(MS_U8 *pu8Buffer, MS_U8 u8BufSize);

// Get Rx's ID Manufacturer Name from EDID
MS_BOOL MApi_HDMITx_GetRxIDManufacturerName(MS_U8 *pu8Buffer);

// Get Rx's EDID data
MS_BOOL MApi_HDMITx_GetEDIDData(MS_U8 *pu8Buffer, MS_BOOL BlockIdx);

//*********************//
//             Video                //
//*********************//

// HDMI Tx video output On/Off
void MApi_HDMITx_SetVideoOnOff(MS_BOOL state);
// HDMI Tx video color format
void MApi_HDMITx_SetColorFormat(HDMITX_VIDEO_COLOR_FORMAT in_color, HDMITX_VIDEO_COLOR_FORMAT out_color);
// HDMI Tx video output timing
void MApi_HDMITx_SetVideoOutputTiming(HDMITX_VIDEO_TIMING mode);
// HDMI Tx video output aspect ratio
void MApi_HDMITx_SetVideoOutputAsepctRatio(HDMITX_VIDEO_ASPECT_RATIO out_ar);
// HDMI Tx video output Overscan and AFD ratio
void MApi_HDMITx_SetVideoOutputOverscan_AFD(MS_BOOL bflag, HDMITX_VIDEO_SCAN_INFO out_scaninfo, MS_U8 out_afd);
void MApi_HDMITx_SetVideoOutputOverscan_AFD_II(MS_BOOL bflag, HDMITX_VIDEO_SCAN_INFO out_scaninfo, MS_U8 out_afd, MS_U8 A0 );

//*********************//
//             Audio                //
//*********************//

// HDMI Tx audio output On/Off
void MApi_HDMITx_SetAudioOnOff(MS_BOOL state);
// HDMI Tx audio output sampling frequency
// For Uranus
void MApi_HDMITx_SetAudioFrequency(HDMITX_AUDIO_FREQUENCY freq);
// HDMI Tx Module audio output: sampling frequency, channel count and coding type
// For Oberon
void MApi_HDMITx_SetAudioConfiguration(HDMITX_AUDIO_FREQUENCY freq, HDMITX_AUDIO_CHANNEL_COUNT ch, HDMITX_AUDIO_CODING_TYPE type);
// HDMI Tx get audio CTS value.
MS_U32 MApi_HDMITx_GetAudioCTS(void);
// HDMI Tx mute/unmute audio FIFO.
void MApi_HDMITx_MuteAudioFIFO(MS_BOOL bflag);

//void MApi_HDMITx_SetAudioFrequencyFromMad(void);
//*********************//
//             HDCP                //
//*********************//

// HDMI Tx Get HDCP key
void MApi_HDMITx_GetHdcpKey(MS_BOOL useinternalkey, MS_U8 *data);
// HDMI Tx HDCP encryption On/Off
void MApi_HDMITx_SetHDCPOnOff(MS_BOOL state);
// This routine set HDMI Tx AVMUTE
void MApi_HDMITx_SetAVMUTE(MS_BOOL bflag);
// This routine get HDMI Tx AVMUTE status
MS_BOOL MApi_HDMITx_GetAVMUTEStatus(void);
// HDMI Tx HDCP status
HDMITX_HDCP_STATUS MApi_HDMITx_GetHDCPStatus(void);
// HDMI video output or blank or encryption while connected with unsupport HDCP Rx
void MApi_HDMITx_UnHDCPRxControl(HDMITX_UNHDCPRX_CONTROL state);
// HDMI video output or blank or encryption while HDCP authentication fail
void MApi_HDMITx_HDCPRxFailControl(HDMITX_HDCPRXFail_CONTROL state);

// Debug
MS_BOOL  MApi_HDMITx_GetLibVer(const MSIF_Version **ppVersion);

MS_BOOL  MApi_HDMITx_GetInfo(HDMI_TX_INFO *pInfo);

MS_BOOL  MApi_HDMITx_GetStatus(HDMI_TX_Status *pStatus);

MS_BOOL MApi_HDMITx_HDCP_IsSRMSignatureValid(MS_U8 *data, MS_U32 size);

/**
* @brief set debug mask
* @param[in] u16DbgSwitch DEBUG MASK,
*   0x01: Debug HDMITX, 0x02: Debug HDCP
*/
MS_BOOL  MApi_HDMITx_SetDbgLevel(MS_U16 u16DbgSwitch);

void MApi_HDMITx_SetHPDGpioPin(MS_U8 u8pin);

// Adjust HDMITx analog setting for HDMI test or compliant issue
void MApi_HDMITx_AnalogTuning(HDMITX_ANALOG_TUNING *pInfo);

void MApi_HDMITx_DisableRegWrite(MS_BOOL bFlag);

//*********************//
//             CEC                 //
//*********************//

/// This routine get EDID physical address
void MApi_HDMITx_GetEDIDPhyAdr(MS_U8 *pdata);
// This routine turn on/off HDMI Tx CEC
void MApi_HDMITx_SetCECOnOff(MS_BOOL bflag);
// This routine get HDMI Tx CEC On/Off status
MS_BOOL MApi_HDMITx_GetCECStatus(void);
// This routine force get EDID from reciver
MS_BOOL MApi_HDMITx_EdidChecking(void);

#ifdef __cplusplus
}
#endif


#endif // _API_HDMITX_H_

