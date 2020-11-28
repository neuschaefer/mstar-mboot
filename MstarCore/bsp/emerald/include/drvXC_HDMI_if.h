////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (!¡±MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvXC_HDMI_if.h
/// @brief  HDMI Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef DRVXC_HDMI_IF_H
#define DRVXC_HDMI_IF_H



#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------

#ifdef MDRV_HDMI_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define _BYTE_0  0x00
#define _BYTE_1  0x01
#define _BYTE_2  0x02
#define _BYTE_3  0x03
#define _BYTE_4  0x04
#define _BYTE_5  0x05
#define _BYTE_6  0x06
#define _BYTE_7  0x07
#define _BYTE_8  0x08
#define _BYTE_9  0x09
#define _BYTE_10  0x0A
#define _BYTE_11  0x0B
#define _BYTE_12  0x0C
#define _BYTE_13  0x0D
// library information
#define MSIF_HDMI_LIB_CODE               {'H','D','M','I'}
#define MSIF_HDMI_LIBVER                 {'0','1'}
#define MSIF_HDMI_BUILDNUM               {'0','7'}
#define MSIF_HDMI_CHANGELIST             {'0','0','3','5','1','6','6','3'}
#define HDMI_DRV_VERSION                  /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_HDMI_LIB_CODE  ,                  /* IP__                                             */  \
    MSIF_HDMI_LIBVER    ,                          /* 0.0 ~ Z.Z                                        */  \
    MSIF_HDMI_BUILDNUM  ,                          /* 00 ~ 99                                          */  \
    MSIF_HDMI_CHANGELIST,  /* CL#                                              */  \
    MSIF_OS

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

/// HDMI reset type
typedef enum
{
    REST_AVMUTE = _BIT(8),    ///<HDMI Reset bit[8]
    REST_Y_COLOR = _BIT(9),    ///<HDMI Reset bit[9]
    REST_PIXEL_REPETITION  = _BIT(10),    ///<HDMI Reset bit[10]
    REST_FRAME_REPETITION  = _BIT(11),    ///<HDMI Reset bit[11]
    REST_GCP_PKT  = _BIT(12),    ///<HDMI Reset bit[12]
    REST_DEEP_COLOR_FIFO  = _BIT(13),    ///<HDMI Reset bit[13]
    REST_RESERVE = _BIT(14),    ///<HDMI Reset bit[14]
    REST_HDMI_STATUS = _BIT(15),    ///<HDMI Reset bit[15]
}HDMI_REST_t;

/*!
    HDMI Aspect Ratio TYPE
*/
typedef enum
{
    // Active Format Aspect Ratio - AFAR
//    HDMI_AF_AR_Not_Present   = -1,    ///< IF0[11..8] AFD not present, or AFD not yet found
    HDMI_AF_AR_Reserve_0  = 0x00,    ///< IF0[11..8] 0000, Reserved
    HDMI_AF_AR_Reserve_1  = 0x01,    ///< IF0[11..8] 0001, Reserved
    HDMI_AF_AR_16x9_Top = 0x02,    ///< IF0[11..8] 0010, box 16:9 (top).
    HDMI_AF_AR_14x9_Top = 0x03,    ///< IF0[11..8] 0011, box 14:9 (top).
    HDMI_AF_AR_GT_16x9 = 0x04,    ///< IF0[11..8] 0100, box >16:9 (centre)
    HDMI_AF_AR_Reserve_5  = 0x05,    ///< IF0[11..8] 0101, Reserved
    HDMI_AF_AR_Reserve_6  = 0x06,    ///< IF0[11..8] 0110, Reserved
    HDMI_AF_AR_Reserve_7  = 0x07,    ///< IF0[11..8] 0111, Reserved
    HDMI_AF_AR_SAME   = 0x08,    ///< IF0[11..8] 1000, same as picture
    HDMI_AF_AR_4x3_C  = 0x09,    ///< IF0[11..8] 1001, 4:3 Center
    HDMI_AF_AR_16x9_C = 0x0A,    ///< IF0[11..8] 1010, 16:9 Center
    HDMI_AF_AR_14x9_C = 0x0B,    ///< IF0[11..8] 1011, 14:9 Center
    HDMI_AF_AR_Reserve_12   = 0x0C,    ///< IF0[11..8] 1100, Reserved.
    HDMI_AF_AR_4x3_with_14x9_C  = 0x0D,    ///< IF0[11..8] 1101, 4:3 with shoot and protect 14:9 centre.
    HDMI_AF_AR_16x9_with_14x9_C = 0x0E,    ///< IF0[11..8] 1110, 16:9 with shoot and protect 14:9 centre.
    HDMI_AF_AR_16x9_with_4x3_C = 0x0F,    ///< IF0[11..8] 1111, 16:9 with shoot and protect 4:3 centre.

    // Picture Aspect Ratio - PAR
    HDMI_Pic_AR_NODATA = 0x00,     ///< IF0[13..12] 00
    HDMI_Pic_AR_4x3    = 0x10,     ///< IF0[13..12] 01, 4:3
    HDMI_Pic_AR_16x9   = 0x20,     ///< IF0[13..12] 10, 16:9
    HDMI_Pic_AR_RSV    = 0x30,     ///< IF0[13..12] 11, reserved
} MS_HDMI_AR_TYPE;

#define HDMI_AR_INIT_VALUE          (HDMI_Pic_AR_RSV)
#define HDMI_AR_REG_MASK            (0x3F)
#define HDMI_AFAR_MASK              (0x0F)      // mask to get the AFAR
#define HDMI_AR_MASK                (0x30)      // mask to get the PAR

/// HDMI GControl package type.
typedef enum
{
    G_CTRL_AVMUTE = 0,    ///< bit[0]: AVMUTE
    G_Ctrl_DEFAULT_PHASE,    ///< bit[1]: Default_Phase
    G_Ctrl_LAST_PP,    ///< bit[4:2]: LAST_PP[2:0]
    G_Ctrl_PRE_LPP,    ///< bit[7:5]: PRE_LPP[2:0]
    G_Ctrl_CD_VAL,    ///< bit[11:8]: CD_VAL[3:0]
    G_Ctrl_PP_VAL,    ///< bit[15:12]: PP_VAL[3:0]
    G_Ctrl_ALL
}HDMI_GControl_INFO_t;

/// HDMI PLL control type
typedef enum
{
    PLL_CTRL_L=0,    ///< HDMI_PLL_CTRL1_L  7:0
    PLL_CTRL_MANUAL_DIV,    ///< MANUAL_PLL_DIV    7
    PLL_CTRL_PORST,    ///< PLL_PORST 6
    PLL_CTRL_RESET_TP,    ///< RESET_TP 5
    PLL_CTRL_RESET_TF,    ///< RESET_TF 4
    PLL_CTRL_RESET_TI,    ///< RESET_TI 3
    PLL_CTRL_VCO_OFFSET,    ///< VCO_OFFSET    2
    PLL_CTRL_RESET,    ///< PLL_RESET 1
    PLL_CTRL_PWRDOWN,    ///< PWRDOWN  0

    PLL_CTRL_H,    ///< HDMI_PLL_CTRL1_H 7:0
    PLL_CTRL_KN,    ///< KN[1:0]    7:6
    PLL_CTRL_RCTRL,    ///< RCTRL 5:3
    PLL_CTRL_ICTRL,    ///< ICTRL 2:0
}HDMI_PLL_CTRL_t;

/// HDMI PLL control type
typedef enum
{
    PLL_CTRL2_L,    ///< HDMI_PLL_CTRL2_L 7:0
    PLL_CTRL2_KP,    ///< KP[3:0]   7:4
    PLL_CTRL2_KM,    ///< KM[3:0]   3:0

    PLL_CTRL2_H,    ///< HDMI_PLL_CTRL2_H  7:0
    PLL_CTRL2_DDIV,    ///< DDIV[3:0] 7:4
    PLL_CTRL2_FBDIV,    ///< FBDIV[3:0]    3:0
}HDMI_PLL_CTRL2_t;

////===========================>>HDMI
typedef struct
{
    MS_BOOL bIsHDMIMode;
    MS_BOOL bMuteHDMIVideo;

    MS_BOOL bMuteHDMIAudio;
    MS_BOOL bEnableNonPCM;
    MS_U8      u8AudioStbCnt;      // If stable more than HDMI_AUDIO_STABLE_CNT, enable audio
    // In 199M case, audio on->off->on->off->on, so, we wait 4 * HDMI_AUDIO_STABLE_CNT, if unstable,
    // enable audio still to prevent mute audio always because of un-stable
    MS_U8      u8AudioForceEnableCnt;

    MS_U8      u8ColorFormat;
    MS_U8      u8LostHDMICounter;
    MS_BOOL bColorFMTChange;
    MS_U8      u8PreClolrFormat;
    MS_U8      u8AspectRatio;
} HDMI_POLLING_STATUS_t;

typedef enum
{
    MS_DVI_CHANNEL_R,
    MS_DVI_CHANNEL_G,
    MS_DVI_CHANNEL_B,
} MS_DVI_CHANNEL_TYPE;

/// HDMI COLOR FORMAT
typedef enum
{
    MS_HDMI_COLOR_RGB,    ///< HDMI RGB 444 Color Format
    MS_HDMI_COLOR_YUV_422,    ///< HDMI YUV 422 Color Format
    MS_HDMI_COLOR_YUV_444,    ///< HDMI YUV 444 Color Format
    MS_HDMI_COLOR_RESERVED,    ///< Reserve
    MS_HDMI_COLOR_DEFAULT = MS_HDMI_COLOR_RGB,    ///< Default setting
    MS_HDMI_COLOR_UNKNOWN = 7,    ///< Unknow Color Format
} MS_HDMI_COLOR_FORMAT;

/// HDMI Equalize Level
typedef enum
{
    MS_HDMI_EQ_2M,    ///< HDMI EQ 2M
    MS_HDMI_EQ_10M,    ///< HDMI EQ 10M
    MS_HDMI_EQ_15M,    ///< HDMI EQ 15M
    MS_HDMI_EQ_MAX,    ///< HDMI EQ MAX
    MS_HDMI_EQ_USER_DEFINE,    ///< HDMI EQ User define
} MS_HDMI_EQ;

/// HDMI Packet nauber
typedef enum
{
    PKT_MPEG  = _BIT(0),    ///< Pactet[0]
    PKT_AUI  = _BIT(1),    ///< Pactet[1]
    PKT_SPD  = _BIT(2),    ///< Pactet[2]
    PKT_AVI  = _BIT(3),    ///< Pactet[3]
    PKT_GC  = _BIT(4),    ///< Pactet[4]
    PKT_ASAMPLE  = _BIT(5),    ///< Pactet[5]
    PKT_ACR  = _BIT(6),    ///< Pactet[6]
    PKT_VS  = _BIT(7),    ///< Pactet[7]
    PKT_NULL  = _BIT(8),    ///< Pactet[8]
    PKT_ISRC2  = _BIT(9),    ///< Pactet[9]
    PKT_ISRC1  = _BIT(10),    ///< Pactet[10]
    PKT_ACP  = _BIT(11),    ///< Pactet[11]
    PKT_ONEBIT_AUD  = _BIT(12),    ///< Pactet[12]
}MS_HDMI_PACKET_STATE_t;

typedef enum
{
    CAPS_DVI_ADJ_70M = _BIT(0),
    CAPS_VSYNC_END_EN = _BIT(1),
}MS_HDMI_FUNC_CAPS;

/// HDMI PACKET VALUE structure
typedef struct
{
    MS_U16 PKT_MPEG_VALUE;    ///< MPEG packet content
    MS_U16 PKT_AUI_VALUE;    ///< AUI packet content
    MS_U16 PKT_SPD_VALUE;    ///< SPD packet content
    MS_U16 PKT_AVI_VALUE;    ///< AVI packet content
    MS_U16 PKT_GC_VALUE;    ///< GC packet content
    MS_U16 PKT_ASAMPLE_VALUE;    ///< ASAMPLE packet content
    MS_U16 PKT_ACR_VALUE;    ///< ACR packet content
    MS_U16 PKT_VS_VALUE;    ///< VS packet content
    MS_U16 PKT_NULL_VALUE;    ///< NULL packet content
    MS_U16 PKT_ISRC2_VALUE;    ///< ISRC2 packet content
    MS_U16 PKT_ISRC1_VALUE;    ///< ISRC1 packet content
    MS_U16 PKT_ACP_VALUE;    ///< ACP packet content
    MS_U16 PKT_ONEBIT_AUD_VALUE;    ///< ONE bit AUD packet content
}MS_HDMI_PACKET_VALUE_t;

typedef struct
{
    MS_U8 AVMuteStatus;
    MS_U8 AudioNotPCM;
    MS_U8 PreAudiostatus;
    MS_U8 ChecksumErrOrBCHParityErr;
    MS_U8 PacketColorFormat;
    MS_U8 AspectRatio;
    MS_U8 AudioPacketErr;
    MS_U8 ACPType;
} MS_HDMI_PACKET_STATUS_t;


typedef struct
{
    MS_HDMI_PACKET_VALUE_t enPKT_Value;
    MS_HDMI_PACKET_STATUS_t enPKT_Status;
} HDMI_PACKET_INFO_t, *P_HDMI_PACKET_INFO_t;

/// HDCP STATUS INFO structure
typedef struct
{
    MS_BOOL b_St_HDMI_Mode;     ///> HDCP_STATUS[0] & BIT0
    MS_BOOL b_St_Reserve_1;     ///> (HDCP_STATUS[0] & BIT1)>>1
    MS_BOOL b_St_HDCP_Ver;      ///> (HDCP_STATUS[0] & BIT2)>>2
    MS_BOOL b_St_AVMute;        ///> (HDCP_STATUS[0] & BIT3)>>3
    MS_BOOL b_St_ENC_En;        ///> (HDCP_STATUS[0] & BIT4)>>4
    MS_BOOL b_St_AKsv_Rcv;      ///> (HDCP_STATUS[0] & BIT5)>>5
    MS_BOOL b_St_ENC_Dis;       ///> (HDCP_STATUS[0] & BIT6)>>6
    MS_BOOL b_St_Reserve_7;     ///> (HDCP_STATUS[0] & BIT7)>>7
}MS_HDCP_STATUS_INFO_t;

/// HDMI Black Level
typedef enum
{
    E_BLACK_LEVEL_LOW = 0,    ///> HDMI black level low
    E_BLACK_LEVEL_HIGH,    ///> HDMI black level high
} BLACK_LEVEL;

/// VGA/DVI/HDMI EDID
typedef enum
{
    E_XC_PROG_DVI0_EDID = 0x00,
    E_XC_PROG_DVI1_EDID = 0x01,
    E_XC_PROG_DVI2_EDID = 0x02,
    E_XC_PROG_DVI3_EDID = 0x03,
    E_XC_PROG_VGA_EDID  = 0x10,
} E_XC_DDCRAM_PROG_TYPE;

typedef struct
{
    MS_U8 *EDID;                            ///< customer EDID
    MS_U16 u16EDIDSize;                       ///< 128 for VGA/DVI , 256 for HDMI
    E_XC_DDCRAM_PROG_TYPE eDDCProgType;     ///< what kind of DDCRam to program

    MS_U16 u16CECPhyAddr;                   ///< if only 1 Digital DDCRam (get this information from MApi_XC_GetInfo()), you need to specify CEC physical address here
    MS_U8  u8CECPhyAddrIdxL;                ///< start point of CEC physical address (low byte) in EDID
    MS_U8  u8CECPhyAddrIdxH;                ///< start point of CEC physical address (high byte) in EDID
} XC_DDCRAM_PROG_INFO;

////===========================>>HDCP

///HDCP polling status
typedef struct
{
    MS_BOOL bHPD_OK;    ///< HPD OK
    MS_U16     u16HPD_Counter;    ///< HPD times counter
    MS_U16     u16HDCP_KeyCounter;    /// > HDCP key number
    MS_U16     u16HDCP_KeyChkSum;    ///> HDCP key check sum
    MS_BOOL bIsPullHighHPD;    ///> HPD is high or not
    MS_U8      u8BKSV[5];    ///> BKSV

} HDCP_POLLING_STATUS_t;

/**
 *  The return value for HDMI fuction.
 */
typedef enum
{
    /// fail
    E_HDMI_RET_FAIL = 0,
    /// success
    E_HDMI_RET_OK,
} HDMI_Ret_Value;


// HDMI v1.4 new feature - T8 and T9
typedef enum
{
    E_HDMI_NO_ADDITIONAL_FORMAT, // 000
    E_HDMI_4Kx2K_FORMAT,                 // 001
    E_HDMI_3D_FORMAT,                      // 010
    E_HDMI_RESERVED,                         // 011 ~ 111
    E_HDMI_NA                                     // Not available
} E_HDMI_ADDITIONAL_VIDEO_FORMAT;

typedef enum
{
    E_VIC_4Kx2K_30Hz = 0x01, // 1920(x2)x1080(x2) @ 29.97/30Hz
    E_VIC_4Kx2K_25Hz = 0x02, // 1920(x2)x1080(x2) @ 25Hz
    E_VIC_4Kx2K_24Hz = 0x03, // 1920(x2)x1080(x2) @ 23.976/24Hz
    E_VIC_4Kx2K_24Hz_SMPTE = 0x04, // 2048(x2)x1080(x2) @ 24Hz
    E_VIC_RESERVED,                // 0x00, 0x05 ~ 0xFF
    E_VIC_NA                             // Not available
} E_HDMI_VIC_4Kx2K_CODE;

typedef enum
{
    E_3D_EXT_DATA_HOR_SUB_SAMPL_0,      //0000
    E_3D_EXT_DATA_HOR_SUB_SAMPL_1,      //0001
    E_3D_EXT_DATA_HOR_SUB_SAMPL_2,      //0010
    E_3D_EXT_DATA_HOR_SUB_SAMPL_3,      //0011
    E_3D_EXT_DATA_QUINCUNX_MATRIX_0,    //0100
    E_3D_EXT_DATA_QUINCUNX_MATRIX_1,    //0101
    E_3D_EXT_DATA_QUINCUNX_MATRIX_2,    //0110
    E_3D_EXT_DATA_QUINCUNX_MATRIX_3,    //0111
    E_3D_EXT_DATA_RESERVE,              //1000 ~ 1111
    E_3D_EXT_DATA_MODE_MAX,
} E_HDMI_3D_EXT_DATA_T;

typedef enum
{
    E_3D_META_DATA_PARALLAX_ISO23002_3,      //0000
    E_3D_META_DATA_RESERVE,              //001 ~ 1111
    E_3D_META_DATA_MAX,
} E_HDMI_3D_META_DATA_TYPE;

typedef struct
{
    MS_BOOL b3D_Meta_Present;
    E_HDMI_3D_META_DATA_TYPE t3D_Metadata_Type;
    MS_U8 u83D_Metadata_Length;
    MS_U8 u83D_Metadata[23]; // Maximum length of VS is 31 - 8 = 23
} sHDMI_3D_META_FIELD;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

//HDMI/DVI
INTERFACE HDMI_POLLING_STATUS_t    g_HdmiPollingStatus;

//HDCP
INTERFACE HDCP_POLLING_STATUS_t    g_HdcpPollingStatus;

INTERFACE MS_U16 g_AVMUTEMissingCounter;
INTERFACE MS_U16 g_AVIMissingCounter;
INTERFACE MS_U16 g_ACPMissingCounter;

#ifdef DVI_NEW_Patch
    // 20081226 - DVI+HDCP snow noise patch - start ...
INTERFACE MS_U16 g_DVI70MhzPollingCounter;
INTERFACE MS_U8 g_DVI70MhzUnstableCounter;
INTERFACE MS_BOOL g_bDVILess70MHz;
    // 20081226 - DVI+HDCP snow noise patch - end ...
#endif


//HDMI
INTERFACE MS_U16 MDrv_HDMI_Func_Caps(void);
INTERFACE void MDrv_HDMI_init( void );
INTERFACE void MDrv_HDMI_Exit( void );
INTERFACE void MDrv_HDMI_pkt_reset( HDMI_REST_t breset );
INTERFACE void MDrv_HDMI_pullhpd( MS_BOOL bHighLow, E_MUX_INPUTPORT enInputPortType, MS_BOOL bInverse);
INTERFACE MS_U16 MDrv_HDMI_GC_Info(HDMI_GControl_INFO_t gcontrol);
INTERFACE MS_HDMI_PACKET_VALUE_t MDrv_HDMI_Packet_Received(MS_BOOL bEnable);
INTERFACE MS_HDMI_COLOR_FORMAT MDrv_HDMI_Get_ColorFormat(void);

INTERFACE void MDrv_HDMI_Set_EQ(MS_HDMI_EQ enEq, MS_U8 u8EQValue);
INTERFACE void MDrv_HDMI_Audio_MUTE_Enable(MS_U16 u16MuteEvent, MS_U16 u16MuteMask);
INTERFACE void MDrv_HDMI_Audio_Status_Clear(void);

INTERFACE MS_HDMI_AR_TYPE MDrv_HDMI_Get_AspectRatio(MS_BOOL bEn_PAR, MS_BOOL bEn_AFAR);
INTERFACE MS_HDMI_AR_TYPE MDrv_HDMI_Get_ActiveFormat_AspectRatio(MS_BOOL bEn_AFAR);

INTERFACE MS_U8 MDrv_HDMI_err_status_update(MS_U8 u8value, MS_BOOL bread);
INTERFACE void MDrv_HDMI_Get_PollingStatus(HDMI_POLLING_STATUS_t **pStatus);
INTERFACE MS_BOOL MDrv_HDMI_IsHDMI_Mode(void);

INTERFACE void MDrv_HDMI_Get_MID_info(MS_U8 * pu8ManufactorData);
INTERFACE MS_BOOL MDrv_HDMI_get_packet_value(MS_HDMI_PACKET_STATE_t u8state, MS_U8 u8byte_idx, MS_U8 *pValue);

//DVI
INTERFACE MS_U16 MDrv_DVI_ChannelPhaseStatus( MS_DVI_CHANNEL_TYPE u8Channel);
INTERFACE void MDrv_DVI_SoftwareReset( MS_U16 u16Reset );
INTERFACE void mdrv_dvi_reset(void);
INTERFACE void MDrv_DVI_ClkPullLow(MS_BOOL bPullLow, E_MUX_INPUTPORT enInputPortType);
INTERFACE void MDrv_DVI_SwitchSrc(E_MUX_INPUTPORT enInputPortType);
INTERFACE MS_BOOL MDrv_HDMI_SetForClockLessThan70Mhz( E_MUX_INPUTPORT InputSourceType  );
INTERFACE void MDrv_HDMI_dvi_adjust( MS_BOOL bClockLessThan70MHz);
INTERFACE void MDrv_HDMI_SetUpdatePhaseLineCount(INPUT_SOURCE_TYPE_t enInputSourceType);

//HDCP
INTERFACE void MDrv_HDCP_Enable(MS_BOOL bEnable);
INTERFACE void MDrv_HDCP_ClearStatus( void );
INTERFACE void MDrv_HDCP_initproductionkey( MS_U8 * pu8HdcpKeyData );
INTERFACE MS_HDCP_STATUS_INFO_t* MDrv_HDCP_GetStatus(void );
INTERFACE void MDrv_HDCP_Vsync_end_en(MS_BOOL bStable);

//Audio
INTERFACE void MDrv_HDMI_audio_output( MS_BOOL bEnable );
INTERFACE MS_U8 MDrv_HDMI_audio_cp_hdr_info(void);
INTERFACE MS_U8 MDrv_HDMI_audio_channel_status(MS_U8 u8byte);


// Debug
/**
*   HDMI Info
*/
typedef struct
{
    MS_U8 u8SupportPorts;
}MS_HDMI_INFO;

/**
*   HDMI Status
*/
typedef struct
{
    MS_BOOL bIsInitialized;
    MS_BOOL bIsRunning;
}MS_HDMI_Status;
INTERFACE HDMI_Ret_Value  MDrv_HDMI_GetLibVer(const MSIF_Version **ppVersion);      ///< Get version (without Mutex protect)
INTERFACE HDMI_Ret_Value  MDrv_HDMI_GetInfo(MS_HDMI_INFO *pInfo);
INTERFACE HDMI_Ret_Value  MDrv_HDMI_GetStatus(MS_HDMI_Status *pStatus);

// DDC Ram
INTERFACE void MDrv_HDMI_PROG_DDCRAM(XC_DDCRAM_PROG_INFO *pstDDCRam_Info, MS_U32 u32SizeOfInfo);
INTERFACE MS_U8 MDrv_HDMI_Get_Pixel_Repetition(void);

//#if defined(CHIP_T8) || defined(CHIP_J2) // HDMI 1.4 new feature
INTERFACE void MDrv_HDMI_3D_4Kx2K_Process(void);
INTERFACE E_HDMI_ADDITIONAL_VIDEO_FORMAT MDrv_HDMI_Check_Additional_Format(void);
INTERFACE E_XC_3D_INPUT_MODE MDrv_HDMI_Get_3D_Structure(void);
INTERFACE E_HDMI_3D_EXT_DATA_T MDrv_HDMI_Get_3D_Ext_Data(void);
INTERFACE void MDrv_HDMI_Get_3D_Meta_Field(sHDMI_3D_META_FIELD *pdata);
INTERFACE MS_U8 MDrv_HDMI_Get_VIC_Code(void);
INTERFACE E_HDMI_VIC_4Kx2K_CODE MDrv_HDMI_Get_4Kx2K_VIC_Code(void);
// HDMI ARC pin control
INTERFACE void MDrv_HDMI_ARC_PINControl(E_MUX_INPUTPORT enInputPortType, MS_BOOL bEnable, MS_BOOL bDrivingHigh);
//#endif


#if 0
INTERFACE MS_U8 u8PSDVIStableCount[4];
void MDrv_HDMI_ImmeswitchPS_Handler(void);
void MDrv_DVI_ForceAllPortsEnterPS(void);
#endif
#undef INTERFACE


#ifdef __cplusplus
}
#endif

#endif /* MDRV_HDMI_H */

