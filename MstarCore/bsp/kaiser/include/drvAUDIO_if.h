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

#ifndef _DRV_AUDIO_IF_H_
#define _DRV_AUDIO_IF_H_

#include "MsTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define drvMAD_STOP                     0x0
#define DSP_CLK                         204//185//204

#define AUD_CHK_DSP_READ_RDY            0x08
#define AUD_CHK_DSP_WRITE_RDY           0x10

//================================================================
//  IP Security Define
//================================================================
#define  AU_DVB2_AUTHBIT_BBE            0
#define  AU_DVB2_AUTHBIT_SRS            2
#define  AU_DVB2_AUTHBIT_TSHD           3
#define  AU_DVB2_AUTHBIT_VIQ            4
#define  AU_DVB2_AUTHBIT_VDS            5
#define  AU_DVB2_AUTHBIT_VSPK           6
#define  AU_DVB2_AUTHBIT_AUDSY          9
// Dolby DD
#define  AU_DVB_AUTHBIT_AC3             11
#define  AU_DVB2_AUTHBIT_AC3_AD         11
// Dolby DDP
#define  AU_DVB_AUTHBIT_AC3P            12
#define  AU_DVB2_AUTHBIT_AC3P_AD        12
// Dolby DDCO
#define  AU_DVB2_AUTHBIT_DDE            13
// Dolby Pulse(DDT)
#define  AU_DVB_AUTHBIT_MS10_DDT        14
// DTS DMP (Core 2.0)
#define  AU_DVB_AUTHBIT_DTSDEC          15
#define  AU_DVB2_AUTHBIT_DTSDEC         15
// WMA
#define  AU_DVB_AUTHBIT_WMA             30
#define  AU_DVB2_AUTHBIT_WMA            30
// SRS StudioSound
#define  AU_DVB2_AUTHBIT_SRS_StudioSND  55
// Dolby Volume
#define  AU_DVB2_AUTHBIT_DolbyVolume    56
// Dolby DD Plus Encode
#define  AU_DVB2_AUTHBIT_DDP_ENC        57
// DTS LBR
#define  AU_DVB_AUTHBIT_DTS_LBR         58
#define  AU_DVB2_AUTHBIT_DTS_LBR        58
// DTS XLL
#define  AU_DVB_AUTHBIT_DTS_XLL         59
#define  AU_DVB2_AUTHBIT_DTS_XLL        59
#define  AU_DVB2_AUTHBIT_DBX            64
#define  AU_DVB_AUTHBIT_DRA             65
// SRS PureSound
#define  AU_DVB2_AUTHBIT_SRS_PURESND    66
//DTS StudioSound 3D(=TheaterSound3D)
#define  AU_DVB2_AUTHBIT_DTS_StudioSound3D  69
#define  AU_DVB_AUTHBIT_GAAC            70
#define  AU_DVB_AUTHBIT_GAAC_V2         71
#define  AU_DVB2_AUTHBIT_NULL           126
#define  AU_DVB_AUTHBIT_DEMOMODE        127

//================================================================
//  HDMI PC Define
//================================================================
#define  AU_HDMI_AC3                    0x01
#define  AU_HDMI_AC3P                   0x15
#define  AU_HDMI_DTS_TYPE1              0x0B
#define  AU_HDMI_DTS_TYPE2              0x0C
#define  AU_HDMI_DTS_TYPE3              0x0D



//================================================================
//  Structure
//================================================================
/// Audio register structure
typedef struct
{
    MS_U32  u32Addr;                    ///< Reg address
    MS_U8   u8Mask;                     ///<Reg Mask
    MS_U8   u8Value;                    ///<Reg Value
}AUDIO_REG_TYPE, *PAUDIO_REG_TYPE;

typedef struct
{
    MS_U32 u32Addr;
    MS_U32 u32Size;
    MS_U64 u64Idx;
}AU_DVB_ENC_FRAME_INFO, *PAU_DVB_ENC_FRAME_INFO;

typedef struct
{
    MS_U32 u32Addr;
    MS_U32 u32Size;
    MS_U32 u32Idx;
}AUDIO_UPLOAD_INFO, *PAUDIO_UPLOAD_INFO;

typedef enum
{
    AUDIO_COEF_PREVER_PEQ, //for compatible with PEQ of previous version
    AUDIO_COEF_PEQ,
    AUDIO_COEF_HPF,
    AUDIO_COEF_BASS,
    AUDIO_COEF_TREBLE,
}AUDIO_COEF_TYPE;

typedef enum
{
    AUDIO_SINGLE_PRECISION,
    AUDIO_DOUBLE_PRECISION,
}AUDIO_PRECISION_TYPE;


typedef struct
{
    MS_U8   band;                       ///< band
    MS_U8   sfs;                        ///< fs
    MS_U8   scale;                      ///< scale
    MS_U32  a0;                         ///< a0
    MS_U32  a1;                         ///< a1
    MS_U32  a2;                         ///< a2
    MS_U32  b1;                         ///< b1
    MS_U32  b2;                         ///< b2
    AUDIO_COEF_TYPE   type;  			/// PEQ, HPF or tone
    MS_BOOL enable;     				/// PEQ band enable
    AUDIO_PRECISION_TYPE precision;     /// PEQ filter precision
} AUDIO_PEQ_COEF, *PAUDIO_PEQ_COEF;
//================================================================
//  Enum
//================================================================
typedef enum
{
    AU_CHIP_T2,
    AU_CHIP_U3,
    AU_CHIP_T3,
    AU_CHIP_T4,
    AU_CHIP_T7,                         //single DSP
    AU_CHIP_JANUS,                      //single DSP
    AU_CHIP_U4,
    AU_CHIP_T8,
    AU_CHIP_T9,
    AU_CHIP_T10,
    AU_CHIP_T11,
    AU_CHIP_T13,
    AU_CHIP_T12,
    AU_CHIP_J2,
    AU_CHIP_K1,
    AU_CHIP_K2,
    AU_CHIP_A1,
    AU_CHIP_A5,
    AU_CHIP_A6,
    AU_CHIP_A7,
    AU_CHIP_A3,
    AU_CHIP_A5P,
    AU_CHIP_AMETHYST,
    AU_CHIP_EAGLE,
    AU_CHIP_EDISON,
    AU_CHIP_EMERALD,
    AU_CHIP_M12,
    AU_CHIP_EINSTEIN,
    AU_CHIP_EIFFEL,
    AU_CHIP_NIKE,
    AU_CHIP_Euler,
    AU_CHIP_NUGGET,
	AU_CHIP_NIKON,
}AU_CHIP_TYPE;

//================================================================
//  AuCommon
//================================================================
typedef enum
{
    AUDIO_PATH_GROUP_1,
    AUDIO_PATH_GROUP_2,
    AUDIO_PATH_GROUP_3,
}AUDIO_PATH_GROUP_TYPE;


///<Audio source info type
typedef enum
{
    E_AUDIO_INFO_DTV_IN,
    E_AUDIO_INFO_ATV_IN,
    E_AUDIO_INFO_HDMI_IN,
    E_AUDIO_INFO_ADC_IN,
    E_AUDIO_INFO_MM_IN,
    E_AUDIO_INFO_SPDIF_IN,
    E_AUDIO_INFO_KTV_IN,
    E_AUDIO_INFO_GAME_IN,
    E_AUDIO_INFO_KTV_STB_IN			///< Iuput source type for STB KTV mode
}AUDIO_SOURCE_INFO_TYPE;

///<Enum for Audio data capture source selection
typedef enum
{
    E_CAPTURE_CH1,                   ///< Data from DIG1 input port
    E_CAPTURE_CH2,                   ///< Data from DIG2 input port
    E_CAPTURE_CH3,                   ///< Data from DIG3 input port
    E_CAPTURE_CH4,                   ///< Data from DIG4 input port
    E_CAPTURE_CH5,                   ///< Data from DIG5 input port
    E_CAPTURE_CH6,                   ///< Data from DIG6 input port
    E_CAPTURE_CH7,                   ///< Data from DIG7 input port
    E_CAPTURE_CH8,                   ///< Data from DIG8 input port
    E_CAPTURE_PCM,                   ///< Pure PCM out =Data CH5
    E_CAPTURE_PCM_DELAY,             ///< PCM + Delay out
    E_CAPTURE_PCM_SE,                ///< PCM + Delay +SE out
    E_CAPTURE_ADC,                   ///< Data from ADC1 input port
    E_CAPTURE_AUOUT0,                ///< Data for DAC0 output port
    E_CAPTURE_AUOUT1,                ///< Data for DAC1 output port
    E_CAPTURE_AUOUT2,                ///< Data for DAC2 output port
    E_CAPTURE_AUOUT3,                ///< Data for DAC3 output port
    E_CAPTURE_I2S_OUT,               ///< Data for I2S output port
    E_CAPTURE_SPDIF_OUT,             ///< Data for SPDIF output port
    E_CAPTURE_MIXER,                 ///< Data for audio data Mixer
    E_CAPTURE_ADC2,                  ///< Data from ADC2 input port
    E_CAPTURE_ADC1_AUIN0_INPUT,      /// ADC1-Line-in[0]
    E_CAPTURE_ADC1_AUIN1_INPUT,      /// ADC1-Line-in[1]
    E_CAPTURE_ADC1_AUIN2_INPUT,      /// ADC1-Line-in[2]
    E_CAPTURE_ADC1_AUIN3_INPUT,      /// ADC1-Line-in[3]
    E_CAPTURE_ADC1_AUIN4_INPUT,      /// ADC1-Line-in[4]
    E_CAPTURE_ADC1_AUIN5_INPUT,      /// ADC1-Line-in[5]
    E_CAPTURE_ADC1_AUMIC_INPUT,      /// ADC1-Micphone-in
    E_CAPTURE_ADC2_AUIN0_INPUT,      /// ADC2-Line-in[0]
    E_CAPTURE_ADC2_AUIN1_INPUT,      /// ADC2-Line-in[1]
    E_CAPTURE_ADC2_AUIN2_INPUT,      /// ADC2-Line-in[2]
    E_CAPTURE_ADC2_AUIN3_INPUT,      /// ADC2-Line-in[3]
    E_CAPTURE_ADC2_AUIN4_INPUT,      /// ADC2-Line-in[4]
    E_CAPTURE_ADC2_AUIN5_INPUT,      /// ADC2-Line-in[5]
    E_CAPTURE_ADC2_AUMIC_INPUT,      /// ADC2-Micphone-in
    E_CAPTURE_MAX_NUM,               ///< MAX capture source number
    E_CAPTURE_NULL                   = 0xFF,  ///< No caupure source
}AUDIO_CAPTURE_SOURCE_TYPE;          // Audio capture type selection

///<Enum for Multi-Audio Device
typedef enum
{
    E_DEVICE0,    ///< 1st audio device
    E_DEVICE1,    ///< 2nd audio device
    E_DEVICE2,    ///< 3rd audio device
    E_DEVICE3,    ///< 4th audio device
    E_DEVICE4,    ///< 5th audio device
    E_DEVICE5,    ///< 6th audio device
}AUDIO_DEVICE_TYPE;   // Audio device type

///====== Audio Path Mode TYPE========
enum
{
    AUDIO_DSP1_INPUT,                   ///< 0: DSP Decoder1 Input
    AUDIO_DSP2_INPUT,                   ///< 1: DSP Decoder2 Input
    AUDIO_ADC_INPUT,                    ///< 2: ADC Input
    AUDIO_DSP3_INPUT                    = 0x06,     ///< 6: DSP Decoder3 Input
    AUDIO_DSP4_INPUT                    = 0x08,     ///< 8: DSP Decoder4 Input
    AUDIO_ADC2_INPUT                    = 0x09,     ///< 9: ADC2 Input
    AUDIO_DMA_INPUT                     = 0x0E,     ///< E: DMA Input
};

typedef enum
{
    AUDIO_PATH_0,                       ///< 0: PATH 0
    AUDIO_PATH_1,                       ///< 1: PATH 1
    AUDIO_PATH_2,                       ///< 2: PATH 2
    AUDIO_PATH_3,                       ///< 3: PATH 3
    AUDIO_PATH_4,
    AUDIO_PATH_5,
    AUDIO_PATH_6,
    AUDIO_PATH_7,                       ///< 7: New add in T3
    AUDIO_PATH_MAIN                     = 4,

    AUDIO_T3_PATH_AUOUT0                = 0x30,      ///< T3 volume path : AUOUT0
    AUDIO_T3_PATH_AUOUT1                = 0x31,      ///< T3 volume path : AUOUT1
    AUDIO_T3_PATH_AUOUT2                = 0x32,      ///< T3 volume path : AUOUT2
    AUDIO_T3_PATH_AUOUT3                = 0x33,      ///< T3 volume path : AUOUT3
    AUDIO_T3_PATH_I2S                   = 0x34,      ///< T3 volume path : I2S
    AUDIO_T3_PATH_SPDIF                 = 0x35,      ///< T3 volume path : SPDIF
    AUDIO_T3_PATH_I2S2                  = 0x36,      ///< T3 volume path : SPDIF
    AUDIO_T3_PATH_HDMI                  = 0x37,      ///< T3 volume path : HDMI
    AUDIO_T3_PATH_LR                    = 0x38,

    AUDIO_T3_PATH_MIXER_MAIN            = 0x40,      ///< Internal volume path for Mixer 1st port (CH5 in)
    AUDIO_T3_PATH_MIXER_SECONDARY       = 0x41,      ///< Internal volume path for Mixer 2nd port (CH6 in)
    AUDIO_T3_PATH_MIXER_DMA_IN          = 0x42,      ///< Internal volume path for Mixer 3rd port (CH8 in)

    AUDIO_PATH_NULL                     = 0xFF
}AUDIO_PATH_TYPE;

typedef enum
{
    INTERNAL_MULTI_1,                   ///< 0: For Multi-channel only
    INTERNAL_MULTI_2,                   ///< 1  For Multi-channel only
    INTERNAL_MULTI_3,                   ///< 2: For Multi-channel only
    INTERNAL_MULTI_4,                   ///< 3: For Multi-channel only
    INTERNAL_PCM,                       ///< 4: Pure PCM out
    INTERNAL_PCM_DELAY,                 ///< 5: PCM + Delay out
    INTERNAL_PCM_SE,                    ///< 6: PCM + Delay +SE out
    INTERNAL_SCART,                     ///< 7: SCART data
    INTERNAL_MIXER,                     ///< 8: SCART data
    INTERNAL_CH6,                       ///< 9: CH6 data
    INTERNAL_TEST,                      ///< A: Test data
    INTERNAL_LRDIV2,                    ///< B: I2S (L+R)/2 data
    INTERNAL_TONE,                      ///< C: 1KHz Tone
    INTERNAL_CH8,                       ///< D: Data from CH8
    INTERNAL_MAX_NUM,                   ///< MAX Internal path number
    INTERNAL_PATH_NULL                  = 0xFF,
}AUDIO_INTERNAL_PATH_TYPE;              // for T3 only

//====== Audio input Mode TYPE========
typedef enum
{
    AUDIO_SPDIF_INPUT                   = 3,        ///< 3: SPDIF INPUT
    AUDIO_I2S_INPUT                     = 4,        ///< 4: I2S INPUT
    AUDIO_HDMI_INPUT                    = 5,        ///< 5: HDMI INPUT
    AUDIO_SRC_INPUT                     = 7,

    AUDIO_DSP1_DVB_INPUT                = 0x00,
    AUDIO_DSP1_DVB1_INPUT               = 0x10,
    AUDIO_DSP1_SPDIF_INPUT              = 0x20,
    AUDIO_DSP1_SPDIFx1_INPUT            = 0x30,
    AUDIO_DSP1_HDMI_INPUT               = 0x40,
    AUDIO_DSP1_HDMIx1_INPUT             = 0x50,
    AUDIO_DSP1_CardRD_INPUT             = 0x60,
    AUDIO_DSP1_SIF_INPUT                = 0x70,
    AUDIO_DSP1_MM_INPUT                 = 0x80,

    AUDIO_DSP2_DVB_INPUT                = 0x01,
    AUDIO_DSP2_DVB1_INPUT               = 0x11,
    AUDIO_DSP2_SPDIF_INPUT              = 0x21,
    AUDIO_DSP2_SPDIFx1_INPUT            = 0x31,
    AUDIO_DSP2_HDMI_INPUT               = 0x41,
    AUDIO_DSP2_HDMIx1_INPUT             = 0x51,
    AUDIO_DSP2_CardRD_INPUT             = 0x61,
    AUDIO_DSP2_SIF_INPUT                = 0x71,

    AUDIO_DSP3_DVB_INPUT                = 0x06,
    AUDIO_DSP3_DVB1_INPUT               = 0x16,
    AUDIO_DSP3_SPDIF_INPUT              = 0x26,
    AUDIO_DSP3_SPDIFx1_INPUT            = 0x36,
    AUDIO_DSP3_HDMI_INPUT               = 0x46,
    AUDIO_DSP3_HDMIx1_INPUT             = 0x56,
    AUDIO_DSP3_CardRD_INPUT             = 0x66,
    AUDIO_DSP3_SIF_INPUT                = 0x76,

    AUDIO_DSP4_DMARD_INPUT              = 0x58,     /// New add in T3
    AUDIO_DSP4_SIF_INPUT                = 0x78,     /// For T3 SIF input

    AUDIO_AUIN0_INPUT                   = 0x02,     /// Line-in[0]
    AUDIO_AUIN1_INPUT                   = 0x12,     /// Line-in[1]
    AUDIO_AUIN2_INPUT                   = 0x22,     /// Line-in[2]
    AUDIO_AUIN3_INPUT                   = 0x32,     /// Line-in[3]
    AUDIO_AUIN4_INPUT                   = 0xA2,     /// Line-in[4]
    AUDIO_AUIN5_INPUT                   = 0xB2,     /// Line-in[5]
    AUDIO_AUMIC_INPUT                   = 0x72,     /// Micphone-in

    AUDIO_ADC2_AUIN0_INPUT              = 0x09,     /// Line-in[0]
    AUDIO_ADC2_AUIN1_INPUT              = 0x19,     /// Line-in[1]
    AUDIO_ADC2_AUIN2_INPUT              = 0x29,     /// Line-in[2]
    AUDIO_ADC2_AUIN3_INPUT              = 0x39,     /// Line-in[3]
    AUDIO_ADC2_AUIN4_INPUT              = 0xA9,     /// Line-in[4]
    AUDIO_ADC2_AUIN5_INPUT              = 0xB9,     /// Line-in[5]
    AUDIO_ADC2_AUMIC_INPUT              = 0x79,     /// Micphone-in

    AUDIO_DMA_READER_INPUT              = 0x0E,       ///<0x0E : DMA Reader INPUT

    AUDIO_NULL_INPUT                    = 0xFF,
} AUDIO_INPUT_TYPE;

//================================================================
//  HDMI ENUM
//================================================================

//====== HDMI Rx Mode TYPE========
typedef enum
{
    HDMI_RX_PCM                         = 0x0,      ///< HDMI RX PCM Mode
    HDMI_RX_DD                          = 0x1,      ///< HDMI RX Dolby Mode
    HDMI_RX_DTS                         = 0x2,      ///< HDMI RX DTS Mode
    HDMI_RX_DDP                         = 0x3,      ///< HDMI RX DDP Mode
    HDMI_RX_Other                       = 0x4,      ///< HDMI RX Other Mode
} AUDIO_HDMI_RX_TYPE;

//====== HDMI Tx Mode TYPE========
typedef enum
{
    HDMI_OUT_PCM,                       ///< HDMI OUTPUT PCM
    HDMI_OUT_NONPCM,                    ///< HDMI OUTPUT non-PCM
} HDMI_TX_OUTPUT_TYPE;

//====== Audio output Mode TYPE========
typedef enum
{
    AUDIO_AUOUT0_OUTPUT,                ///< 0: DAC0 OUTPUT
    AUDIO_AUOUT1_OUTPUT,                ///< 1: T2=>AA0 OUTPUT    T3=>HP OUTPUT
    AUDIO_AUOUT2_OUTPUT,                ///< 2: T2=>AA1 OUTPUT    T3=>DAC2 OUTPUT
    AUDIO_AUOUT3_OUTPUT,                ///< 3: T2=>NULL          T3=>AA OUTPUT
    AUDIO_SPDIF_OUTPUT,                 ///< 4: SPDIF OUTPUT
    AUDIO_I2S_OUTPUT,                   ///< 5: I2S OUTPUT
    AUDIO_HP_OUTPUT,                    ///< 6: OUTPUT with headphone driver
    AUDIO_I2S2_OUTPUT,                  ///< 7: I2S2 OUTPUT
    AUDIO_HDMI_ARC_OUTPUT,              ///< 8: HDMI ARC OUTPUT(HDMI_Rx,TV)
    AUDIO_HDMI_OUTPUT,                  ///< 9: HDMI Tx OUTPUT(HDMI_Tx,STB)
    AUDIO_NULL_OUTPUT                   = 0xFF,
} AUDIO_OUTPUT_TYPE;

//================================================================
//  I2S ENUM
//================================================================
//====== I2S OUTPUT Mode TYPE========
typedef enum
{
    AUDIO_I2S_MCLK,                     ///< I2S MCLK
    AUDIO_I2S_WORD_WIDTH,               ///< I2S Word-width
    AUDIO_I2S_SOURCE_CH,                ///< I2S Source
    AUDIO_I2S_FORMAT                    ///< I2S format
} AUDIO_I2S_MODE_TYPE;


typedef enum
{
    I2S_MCLK_64FS                       = 0x04,
    I2S_MCLK_128FS                      = 0x05,
    I2S_MCLK_256FS                      = 0x06,     ///< 256 Fs ==>default setting
    I2S_MCLK_384FS                      = 0x07,

    I2S_WORD_WIDTH_16BIT                = 0x4,
    I2S_WORD_WIDTH_24BIT                = 0x5,
    I2S_WORD_WIDTH_32BIT                = 0x6,      ///< 32-bit ==> default setting

    I2S_FORMAT_STANDARD                 = 0,
    I2S_FORMAT_LEFT_JUSTIFIED           = 1
} AUDIO_I2S_MODE_VALUE;

//================================================================
//  SPDIF ENUM
//================================================================
//====== SPDIF OUTPUT Mode TYPE========
typedef enum
{
    SPDIF_OUT_PCM                       = 0x0,      ///< S/PDIF always output PCM
    SPDIF_OUT_AUTO                      = 0x2,      ///< S/PDIF OUTPUT PCM or non-PCM automatic
    SPDIF_OUT_NONPCM                    = 0x2,      ///< S/PDIF OUTPUT non-PCM
    SPDIF_OUT_BYPASS,                   ///< S/PDIF OUTPUT by-pass from HDMI
    SPDIF_OUT_NONE,                     ///< S/PDIF OUTPUT nothing
} AUDIO_SPDIF_OUTPUT_TYPE;

//====== SPDIF OUTPUT CS TYPE =========
typedef enum
{
    SPDIF_CS_CategoryCode               = 0x0,      ///<
    SPDIF_CS_CopyRight                  = 0x1,      ///<
    SPDIF_CS_SourceNumber               = 0x2,      ///<
    SPDIF_CS_ChannelNumber              = 0x3,      ///<
    SPDIF_CS_SmpFreq                    = 0x4,      ///<
    SPDIF_CS_ClockAcc                   = 0x5,      ///<
    SPDIF_ChannelAB                     = 0x6,      ///<
    SPDIF_CS_CopyProtect                = 0x7,      ///<
} AUDIO_SPDIF_CS_TYPE;

//====== SPDIF OUTPUT CS Status =======
typedef enum
{
    SPDIF_CS_Category_BroadCast         = 0x00,     ///<
    SPDIF_CS_Category_General           = 0x01,     ///<
    SPDIF_CS_Category_BroadCast_JP      = 0x02,     ///<
    SPDIF_CS_Category_BroadCast_EU      = 0x03,     ///<
    SPDIF_CS_Category_BroadCast_USA     = 0x04,     ///<
    SPDIF_CS_Category_Rev4              = 0x05,     ///<
    SPDIF_CS_Category_Rev5              = 0x06,     ///<
    SPDIF_CS_Category_Rev6              = 0x07,     ///<
    SPDIF_CS_CopyRight_CP               = 0x08,     ///<
    SPDIF_CS_CopyRight_NonCP            = 0x09,     ///<SPDIF_CS_ChannelNumber_Right
    SPDIF_CS_SourceNumber_2             = 0x0A,     ///<
    SPDIF_CS_SourceNumber_5             = 0x0B,     ///<
    SPDIF_CS_SourceNumber_6             = 0x0C,     ///<
    SPDIF_CS_SourceNumber_Rev1          = 0x0D,     ///<
    SPDIF_CS_SourceNumber_Rev2          = 0x0E,     ///<
    SPDIF_CS_SourceNumber_Rev3          = 0x0F,     ///<
    SPDIF_CS_ChannelNumber_A_Left       = 0x10,     ///<
    SPDIF_CS_ChannelNumber_B_Right      = 0x11,     ///<
    SPDIF_CS_ChannelNumber_C            = 0x12,     ///<
    SPDIF_CS_ChannelNumber_D            = 0x13,     ///<
    SPDIF_CS_ChannelNumber_E            = 0x14,     ///<
    SPDIF_CS_ChannelNumber_F            = 0x15,     ///<
    SPDIF_CS_ChannelNumber_G            = 0x16,     ///<
    SPDIF_CS_ChannelNumber_H            = 0x17,     ///<
    SPDIF_CS_ChannelNumber_I            = 0x18,     ///<
    SPDIF_CS_ChannelNumber_J            = 0x19,     ///<
    SPDIF_CS_ChannelNumber_K            = 0x1A,     ///<
    SPDIF_CS_SmpFreq_192                = 0x1B,     ///<
    SPDIF_CS_SmpFreq_176                = 0x1C,     ///<
    SPDIF_CS_SmpFreq_128                = 0x1D,     ///<
    SPDIF_CS_SmpFreq_96                 = 0x1E,     ///<
    SPDIF_CS_SmpFreq_88                 = 0x1F,     ///<
    SPDIF_CS_SmpFreq_64                 = 0x20,     ///<
    SPDIF_CS_SmpFreq_48                 = 0x21,     ///<
    SPDIF_CS_SmpFreq_44                 = 0x22,     ///<
    SPDIF_CS_SmpFreq_32                 = 0x23,     ///<
    SPDIF_CS_SmpFreq_24                 = 0x24,     ///<
    SPDIF_CS_SmpFreq_22                 = 0x25,     ///<
    SPDIF_CS_SmpFreq_16                 = 0x26,     ///<
    SPDIF_CS_SmpFreq_Rev1               = 0x27,     ///<
    SPDIF_CS_SmpFreq_Rev2               = 0x28,     ///<
    SPDIF_CS_SmpFreq_Rev3               = 0x29,     ///<
    SPDIF_CS_SmpFreq_Rev4               = 0x2A,     ///<
    SPDIF_CS_SmpFreq_Rev5               = 0x2B,     ///<
    SPDIF_CS_ClockAcc_Lev1              = 0x2C,     ///<
    SPDIF_CS_ClockAcc_Lev2              = 0x2D,     ///<
    SPDIF_CS_ClockAcc_Lev3              = 0x2E,     ///<
    SPDIF_CS_ClockAcc_NotMatch          = 0x2F,     ///<
    SPDIF_ChannelAB_Invalid_ON          = 0x30,     ///<
    SPDIF_ChannelAB_Invalid_OFF         = 0x31,     ///<
    SPDIF_CS_CopyProtect_CopyFree       = 0x32,     ///<
    SPDIF_CS_CopyProtect_CopyOnce       = 0x33,     ///<
    SPDIF_CS_CopyProtect_CopyNever      = 0x34,     ///<
} AUDIO_SPDIF_CS_TYPE_STATUS;

//====== SPDIF OUTPUT CS Mode TYPE========
typedef enum
{
    SPDIF_CHANNEL_STATUS_FS,            ///< Set sampling rate in CS3
    SPDIF_CHANNEL_STATUS_CATEGORY,      ///< Set Category code in CS1
    SPDIF_CHANNEL_STATUS_PCM_FORMAT,    ///< Set PCM/NonPCM mode in CS0
    SPDIF_CHANNEL_STATUS_SOURCE_NUMBER,    ///< Set source number in CS2
    SPDIF_CHANNEL_STATUS_CHANNEL_NUMBER,    ///< Set Channel number in CS2
} SPDIF_CS_MODE_TYPE;

typedef enum
{
    SPDIF_CS_FS_32K                     = 0xC0,
    SPDIF_CS_FS_44K                     = 0x00,
    SPDIF_CS_FS_48K                     = 0x40,     ///< ==>default setting
    SPDIF_CS_CATEGORY_NONE              = 0x00,
    SPDIF_CS_CATEGORY_DVB               = 0x30,
    SPDIF_CS_CATEGORY_ATSC              = 0x26,
    SPDIF_CS_FORMAT_PCM                 = 0x00,
    SPDIF_CS_FORMAT_NONPCM              = 0x40,
}SPDIF_CS_MODE_VALUE;

//====== SPDIF OUTPUT BYPASS ================
typedef enum
{
    SPDIFOUT_FROM_HDMIIN,               ///<
    SPDIFOUT_FROM_SPDIFIN,              ///<
} INPUTSRCTYPE_FOR_SPDIFOUT;

typedef enum
{
    SPDIFOUT_BYPASS,                    ///<
    SPDIFOUT_NORMAL,                    ///<
} SPDIFOUT_MODE;

//====== SPDIF Monitor Audio TYPE FS ========
typedef enum
{
    SPDIF_Monitor_NULL,                 ///<
    SPDIF_Monitor_DD_32K,               ///<
    SPDIF_Monitor_DD_44K,               ///<
    SPDIF_Monitor_DD_48K,               ///<
    SPDIF_Monitor_DDP_32K,              ///<
    SPDIF_Monitor_DDP_44K,              ///<
    SPDIF_Monitor_DDP_48K,              ///<
    SPDIF_Monitor_AAC_32K,              ///<
    SPDIF_Monitor_AAC_44K,              ///<
    SPDIF_Monitor_AAC_48K,              ///<
    SPDIF_Monitor_DTS_32K,              ///<
    SPDIF_Monitor_DTS_44K,              ///<
    SPDIF_Monitor_DTS_48K,              ///<
    SPDIF_Monitor_OTHERS                ///<
} SPDIF_Monitor_FS;

//================================================================
//  SIF ENUM
//================================================================
//======SIF Standard========
typedef enum
{
    AU_SYS_NOT_READY,                   // 0
    AU_SYS_M_BTSC,                      // 1
    AU_SYS_M_EIAJ,                      // 2
    AU_SYS_M_A2,                        // 3

    AU_SYS_BG_A2,                       // 4
    AU_SYS_DK1_A2,                      // 5
    AU_SYS_DK2_A2,                      // 6
    AU_SYS_DK3_A2,                      // 7

    AU_SYS_BG_NICAM,                    // 8
    AU_SYS_DK_NICAM,                    // 9
    AU_SYS_I_NICAM,                     // 10
    AU_SYS_L_NICAM,                     // 11
    AU_SYS_FM_RADIO,                    // 12
    AU_SYS_HI_DEV                       = 0x10,
    AU_SYS_BUSY                         = 0x80,
    STD_SEL_AUTO                        = 0xE0
}AUDIO_SIF_SET_STANDARD;

//======SIF System Type========
typedef enum
{
    A2_M_STANDARD                       = 0x00,
    A2_BG_STANDARD,
    A2_DK_STANDARD,
    A2_I_STANDARD,
    AM_STANDARD,
    NICAM_BG_STANDARD,
    NICAM_I_STANDARD,
    HIDEV_M_STANDARD,
    HIDEV_BG_STANDARD,
    HIDEV_DK_STANDARD,
    HIDEV_I_STANDARD,
    BTSC_STANDARD,
    FM_RADIO_STANDARD,
    WRITE_THRESHOLD                     = 0x10
}AUDIO_SIF_SYSTEM_TYPE;


//======SIF Threshold Type========
typedef enum
{
    CARRIER1_ON_AMP                     = 0x00,
    CARRIER1_OFF_AMP,
    CARRIER1_ON_NSR,
    CARRIER1_OFF_NSR,
    CARRIER2_ON_AMP,
    CARRIER2_OFF_AMP,
    CARRIER2_ON_NSR,
    CARRIER2_OFF_NSR,
    A2_PILOT_ON_AMP,
    A2_PILOT_OFF_AMP,

    NICAM_ON_SIGERR                     = 0x0,
    NICAM_OFF_SIGERR                    = 0x1,

    BTSC_MONO_ON_NSR_RATIO              = 0x0,
    BTSC_MONO_OFF_NSR_RATIO             = 0x1,
    BTSC_PILOT_AMPLITUDE_ON             = 0x2,
    BTSC_PILOT_AMPLITUDE_OFF            = 0x3,
    BTSC_SAP_ON_NSR_RATIO               = 0x4,
    BTSC_SAP_OFF_NSR_RATIO              = 0x5,
    BTSC_STEREO_ON_RATIO                = 0x6,
    BTSC_STEREO_OFF_NSR_RATIO           = 0x7,
    BTSC_SAP_AMPLITUDE_ON               = 0x8,
    BTSC_SAP_AMPLITUDE_OFF              = 0x9,
    BTSC_HIDEV_ON_NSR_RATIO             = 0xA,
    BTSC_HIDEV_OFF_NSR_RATIO            = 0xB
}AUDIO_SIF_THRESHOLD_TYPE;

//======SIF Gain Type========
typedef enum
{
    PRESCALE_STEP_ONE_DB                = 0x04,
    SET_PRESCALE_A2_FM                  = 0x00,
    SET_PRESCALE_NICAM                  = 0x01,
    SET_PRESCALE_AM                     = 0x02,
    SET_PRESCALE_HIDEV                  = 0x03,
    SET_PRESCALE_FM_M                   = 0x04,
    SET_PRESCALE_HIDEV_M                = 0x05,

    SET_PRESCALE_BTSC                   = 0x00,
    SET_PRESCALE_BTSC_MONO              = 0x01,
    SET_PRESCALE_BTSC_STEREO            = 0x02,
    SET_PRESCALE_BTSC_SAP               = 0x03,

    SET_PRESCALE_FM_RADIO               = 0x00,
    SET_PRESCALE_FM_RADIO_MONO          = 0x01,
    SET_PRESCALE_FM_RADIO_STEREO        = 0x02

}AUDIO_SIF_GAIN_TYPE;

enum
{
    AU_STATUS_MUTE                      = 0x00,
    AU_STATUS_MONO                      = 0x01,    // Primary Mono
    AU_STATUS_STEREO                    = 0x02,    // Primary Stereo
    AU_STATUS_SAP                       = 0x04,    // Second Audio Program
    AU_STATUS_NICAM                     = 0x08,    // Second Audio Program
    AU_STATUS_NICAM_MONO                = 0x10
};

//  enum for sif command
typedef enum
{
    // need to compatible with En_AUD_SIF_CmdType at apiAUDIO.h
    AU_SIF_CMD_SET_STOP                 = 0x00,
    AU_SIF_CMD_SET_PLAY                 = 0x01,
    AU_SIF_CMD_ENABLE_HIDEV             = 0x02,
    AU_SIF_CMD_SET_HIDEV_FILTER_BW_LEVEL= 0x03,
    AU_SIF_CMD_RESET_FC_TRACKING        = 0x04,
    AU_SIF_CMD_ENABLE_FC_TRACKING       = 0x05,
    AU_SIF_CMD_SET_ADC_FROM_VIF_PATH    = 0x06,
    AU_SIF_CMD_ENABLE_AUTO_MUTE         = 0x07,
    AU_SIF_CMD_ENABLE_BEEPER_FUNCTION   = 0x08,
    AU_SIF_CMD_SET_BEEPER_TONE          = 0x09,
    AU_SIF_CMD_ENABLE_AGC               = 0x0A,
    AU_SIF_CMD_RESET_AGC                = 0x0B,
    AU_SIF_CMD_STANDARD_RESET           = 0x0C,
    AU_SIF_CMD_DETECT_MAIN_STD_ONLY     = 0x0D,
    AU_SIF_CMD_ENABLE_AUTO_SOUNDMODE    = 0x0E,
    AU_SIF_CMD_SET_FM_RADIO_DeEmp       = 0x0F,
    AU_SIF_CMD_SET_FM_RADIO_FC_TRACK    = 0x10,
    AU_SIF_CMD_FM_RADIO_RESET           = 0x11,

    // internal used at sif driver.
    AU_SIF_CMD_SET_STD                  = 0x40,
    AU_SIF_CMD_SET_SUB_CARRIER_STD      = 0x41,
    AU_SIF_CMD_SET_CARRIER_DEBOUNCE     = 0x42,
    AU_SIF_CMD_ENABLE_SIF_SYNTHESIZER   = 0x43,
    AU_SIF_CMD_ENABLE_CHANNEL           = 0x44,
    AU_SIF_CMD_SET_SIFFIFO_MODE         = 0x45,
    AU_SIF_CMD_DK123_MONITOR            = 0x46,

    // internal used at sif driver.
    AU_SIF_CMD_GET_HIDEV_ENABLE         = 0x80,
    AU_SIF_CMD_GET_HIDEV_FILTER_BW_LEVEL= 0x81,
    AU_SIF_CMD_GET_ADC_FROM_VIF_PATH    = 0x82,
    AU_SIF_CMD_GET_FM_A2_MODE_STATUS    = 0x83,
    AU_SIF_CMD_GET_BTSC_MODE_STATUS     = 0x84,
    AU_SIF_CMD_GET_NICAM_MODE_STATUS    = 0x85,
    AU_SIF_CMD_GET_STANDARD_STATUS      = 0x86,
    AU_SIF_CMD_GET_STANDARD_CMD         = 0x87,
    AU_SIF_CMD_GET_NSR_CMD              = 0x88,
    AU_SIF_CMD_GET_AMP_CMD              = 0x89,
    AU_SIF_CMD_GET_FM_RADIO_MODE_STATUS = 0x8A,
    AU_SIF_CMD_GET_FM_RADIO_DC_AMP      = 0x8B,
    AU_SIF_CMD_GET_FM_RADIO_NSR         = 0x8C,
    AU_SIF_CMD_GET_VIF_PATCH_ENABLE     = 0x90,
    AU_SIF_CMD_SET_SIF_SHIFT_CLK        = 0x91,

    AU_SIF_CMD2_ADC_VIA_VIF_PIN = 0x01
} AU_SIF_CMD;

typedef enum
{
    AU_SIF_PAL_MONO,
    AU_SIF_PAL_HIDEV,
    AU_SIF_PAL_A2,
    AU_SIF_PAL_NICAM
}AUDIO_SIF_PAL_TYPE;

typedef enum
{
    AU_MODE_MONO,                       ///< MONO
    AU_MODE_STEREO,                     ///< STEREO
    AU_MODE_SAP,                        ///< SAP
    AU_MODE_LANG_A,                     ///< LANG_A
    AU_MODE_LANG_B,                     ///< LANG_B
    AU_MODE_LANG_AB,                    ///< LANG_AB
    AU_MODE_FORCE_NICAM,                ///< FORCE_NICAM
    AU_MODE_NICAM_MONO,
    AU_MODE_AUTO                        = 0x80      ///< auto switch to mono & mute
} AUDIO_SIF_SOUND_MODE;


//================================================================
//  DVB/MAD ENUM
//================================================================
//====== DSP Running Counter Type========
typedef enum
{
    DSP_DEC_MAIN_COUNTER,               /// Main counter for 1st DSP
    DSP_DEC_TIMER_COUNTER,
    DSP_SE_MAIN_COUNTER,                /// Main counter for 2nd DSP
    DSP_SE_TIMER_COUNTER,
    DSP_SE_ISR_COUNTER
} AUDIO_DSP_COUNTER_TYPE;

//====== DSP DECODER ID Type ============
typedef enum
{
    DSP_DEC_BTSC                        = 0x10,
    DSP_DEC_PALSUM                      = 0x20,
    DSP_DEC_OGG                         = 0x30,
    DSP_DEC_MPEG                        = 0x40,
    DSP_DEC_DTS                         = 0x60,
    DSP_DEC_AAC                         = 0x50,
    DSP_DEC_AC3P                        = 0x70,
    DSP_DEC_AC3                         = 0x80,
    DSP_DEC_WMA                         = 0x90,
    DSP_DEC_REV1,
    DSP_DEC_REV2,
    DSP_DEC_REV3,
    DSP_DEC_REV4,
} AUDIO_DSP_DECODER_ID_TYPE;

//====== DSP code Type========
typedef enum
{
    AU_DVB_STANDARD_INVALID             = 0xFF,
    AU_DVB_NONE                         = 0x00,     //0x00
    AU_DVB_DEC_NONE,                    //0x01
    AU_DVB_ENC_NONE,                    //0x02
    AU_DVB_STANDARD_MPEG,               //0x03
    AU_DVB_STANDARD_AC3,                //0x04
    AU_DVB_STANDARD_AC3P,               //0x05
    AU_DVB_STANDARD_AAC,                //0x06
    AU_DVB_STANDARD_MP3,                //0x07
    AU_DVB_STANDARD_WMA,                //0x08
    AU_DVB_STANDARD_RESERVE3,           //0x09
    AU_DVB_STANDARD_RA8LBR,             //0x0A
    AU_DVB_STANDARD_XPCM,               //0x0B
    AU_DVB_STANDARD_TONE,               //0x0C
    AU_DVB_STANDARD_DTS,                //0x0D
    AU_DVB_STANDARD_MS10_DDT,           //0x0E
    AU_DVB_STANDARD_MS10_DDC,           //0x0F
    AU_DVB_STANDARD_WMA_PRO,            //0x10
    AU_DVB_STANDARD_FLAC,               //0x11
    AU_DVB_STANDARD_VORBIS,             //0x12
    AU_DVB_STANDARD_DTSLBR,             //0x13
    AU_DVB_STANDARD_AMR_NB,             //0x14
    AU_DVB_STANDARD_AMR_WB,             //0x15
    AU_DVB_STANDARD_DRA,                //0x16
    AU_DVB_STANDARD_MPEG_AD,            //0x17
    AU_DVB_STANDARD_MAX,

    AU_DVB_STANDARD_MPEG_EN             = 0x20,

    AU_DVB2_NONE                        = 0x30,
    AU_DVB2_STANDARD_MPEG_AD ,
    AU_DVB2_STANDARD_AC3_AD,
    AU_DVB2_STANDARD_AC3P_AD,
    AU_DVB2_STANDARD_AAC_AD,
    AU_DVB2_STANDARD_DDE,
    AU_DVB2_STANDARD_GAAC_AD,
    AU_DVB2_STANDARD_MP3,
    AU_DVB2_STANDARD_MPEG_EN,
    AU_DVB2_STANDARD_XPCM,
    AU_DVB2_STANDARD_KTV,
    AU_DVB2_STANDARD_KTV2,
    AU_DVB2_STANDARD_BTSC_EN,
    AU_DVB2_STANDARD_FM_TX,
    AU_DVB2_STANDARD_MAX,

    AU_DVB2_ADVSND_PL2                  = 0x40,
    AU_DVB2_ADVSND_BBE,
    AU_DVB2_ADVSND_SRS,
    AU_DVB2_ADVSND_VDS,
    AU_DVB2_ADVSND_VSPK,
    AU_DVB2_ADVSND_SUPV,
    AU_DVB2_ADVSND_TSHD,
    AU_DVB2_ADVSND_DTS_ULTRA_TV,
    AU_DVB2_ADVSND_TSHDVIQ,
    AU_DVB2_ADVSND_AUDSY,
    AU_DVB2_ADVSND_DBX,
    AU_DVB2_ADVSND_THEATERSOUND,
    AU_DVB2_ADVSND_PURESND,
    AU_DVB2_ADVSND_STUDIOSOUND_3D,
    AU_DVB2_ADVSND_MAX,

    AU_DEC_SYSTEM                       = 0x50,
    AU_SE_SYSTEM                        = 0x60,

    AU_KTV_ENC                          = 0x70,
    AU_KTV_FUNC                         = 0x80,
    AU_KTV_SYSTEM                       = 0x90,

    AU_SND_EFFECT                       = 0xa0,

    AU_STANDARD_SIF_TYPE                = 0xb0,
    AU_SIF_NONE                         = 0xb0,
    AU_SIF_BTSC ,
    AU_SIF_EIAJ,
    AU_SIF_PALSUM,
    AU_SIF_PALSUM_42M,
    AU_SIF_PALSUM_44M,
    AU_SIF_FM_RADIO,

}AUDIO_DSP_CODE_TYPE;

// enum for DVB system type
typedef enum
{
    AU_DVB_SYS_MPEG,                    //0
    AU_DVB_SYS_AC3,                     //1
    AU_DVB_SYS_AC3P,                    //2
    AU_DVB_SYS_AAC,                     //3
    AU_DVB_SYS_MP3,                     //4
    AU_DVB_SYS_WMA,                     //5
    AU_DVB_SYS_CDLPCM,                  //6
    AU_DVB_SYS_RA8LBR,                  //7
    AU_DVB_SYS_XPCM,                    //8
    AU_DVB_SYS_DTS,                     //9
    AU_DVB_SYS_MS10_DDT,                //A
    AU_DVB_SYS_MS10_DDC,                //B
    AU_DVB_SYS_WMA_PRO,                 //C
    AU_DVB_SYS_FLAC,                    //D
    AU_DVB_SYS_VORBIS,                  //E
    AU_DVB_SYS_RESERVE3,                //F
    AU_DVB_SYS_RESERVE2,                //0x10
    AU_DVB_SYS_RESERVE1,                //0x11
    AU_DVB_SYS_NONE                     //0x12
}AU_DVB_SYS_TYPE;

///< Audio decoder system (1st & 2nd) type
typedef enum
{
    MSAPI_AUD_DVB_INVALID               = 0xFF,     ///< 0xFF: System=Invalid

    //DTV / MM Audio main decoder
    MSAPI_AUD_DVB_NONE                  = 0x00,     ///< 0x00: System=None
    MSAPI_AUD_DVB_MPEG,                 ///< 0x01: System=MPEG
    MSAPI_AUD_DVB_AC3,                  ///< 0x02: System=AC3
    MSAPI_AUD_DVB_AC3P,                 ///< 0x03: System=AC3+
    MSAPI_AUD_DVB_AAC,                  ///< 0x04: System=AAC
    MSAPI_AUD_DVB_MP3,                  ///< 0x05: System=MP3
    MSAPI_AUD_DVB_WMA,                  ///< 0x06: System=WMA
    MSAPI_AUD_DVB_CDLPCM,               ///< 0x07: System=LPCM
    MSAPI_AUD_DVB_RA8LBR,               ///< 0x08: System=RA8 LBR
    MSAPI_AUD_DVB_XPCM,                 ///< 0x09: System=XPCM
    MSAPI_AUD_DVB_TONE,                 ///< 0x0A: System=TONE
    MSAPI_AUD_DVB_DTS,                  ///< 0x0B: System=DTS
    MSAPI_AUD_DVB_MS10_DDT,             ///< 0x0C: System=MS10 DDT
    MSAPI_AUD_DVB_MS10_DDC,             ///< 0x0D: System=MS10 DDC
    MSAPI_AUD_DVB_WMA_PRO,              ///< 0x0E: System=WMA PRO
    MSAPI_AUD_DVB_FLAC,                 ///< 0x0F: System=FLAC
    MSAPI_AUD_DVB_VORBIS,               // 0x10
    MSAPI_AUD_DVB_DTSLBR,               // 0x11
    MSAPI_AUD_DVB_AMR_NB,               // 0x12
    MSAPI_AUD_DVB_AMR_WB,               // 0x13
    MSAPI_AUD_DVB_DRA,                  // 0x14
    MSAPI_AUD_DVB_MAX,

    //DTV Audio decoder 2 (for AD)
    MSAPI_AUD_DVB2_NONE                 = 0x30,     ///< 0x30: System=None
    MSAPI_AUD_DVB2_MPEG,                ///< 0x31: System=MPEG AD
    MSAPI_AUD_DVB2_AC3,                 ///< 0x32: System=AC3 AD
    MSAPI_AUD_DVB2_MP3,                 ///< 0x33: System=2nd MP3
    MSAPI_AUD_DVB2_AAC,                 ///< 0x34: System=AAC AD
    MSAPI_AUD_DVB2_GAAC,                ///< 0x35: System=GAAC AD
    MSAPI_AUD_DVB2_AC3P,                ///< 0x36: System=AC3P AD
    MSAPI_AUD_DVB2_DDE,                 ///< 0x37: System=AC3 Encoder
    MSAPI_AUD_DVB2_DTSE,                ///< 0x38: System=DTS Encoder
    MSAPI_AUD_DVB2_XPCM,
    MSAPI_AUD_DVB2_KTV,
    MSAPI_AUD_DVB2_KTV2,
    MSAPI_AUD_DVB2_BTSCE,               ///< 0x3C: System=BTSC Encoder
    MSAPI_AUD_DVB2_FM_TX, 
    MSAPI_AUD_DVB2_MAX,

    //ATV SIF
    MSAPI_AUD_ATV_NONE                  = 0xB0,     ///< 0xB0: System=None
    MSAPI_AUD_ATV_BTSC,                 ///< 0xB1: System=BTSC
    MSAPI_AUD_ATV_EIAJ,
    MSAPI_AUD_ATV_PAL,                  ///< 0xB3: System=PALSUM
    MSAPI_AUD_ATV_FM_RADIO,             ///< 0xB4: System=FM_RADIO
    MSAPI_AUD_ATV_MAX
} En_DVB_decSystemType;

typedef enum
{
    Audio_DEC_PCM                       = 0x00000001,
    Audio_DEC_XPCM                      = 0x00000002,
    Audio_DEC_MPEG                      = 0x00000004,
    Audio_DEC_MP3                       = 0x00000008,
    Audio_DEC_AC3                       = 0x00000010,
    Audio_DEC_AC3P                      = 0x00000020,
    Audio_DEC_AAC_LC                    = 0x00000040,
    Audio_DEC_HEAAC_V1                  = 0x00000080,
    Audio_DEC_HEAAC_V2                  = 0x00000100,
    Audio_DEC_DOLBYPULSE                = 0x00000200,
    Audio_DEC_WMA                       = 0x00000400,
    Audio_DEC_WMAPRO                    = 0x00000800,
    Audio_DEC_RA8                       = 0x00001000,
    Audio_DEC_DTS                       = 0x00002000,
    Audio_DEC_FLAC                      = 0x00004000,
    Audio_DEC_VORBIS                    = 0x00008000,
    Audio_DEC_KTV                       = 0x00010000,
    Audio_DEC_KTV2                      = 0x00020000,
    Audio_DEC_AMR_NB                    = 0x00040000,
    Audio_DEC_AMR_WB                    = 0x00080000,
    Audio_DEC_DRA                       = 0x00100000,
    Audio_DEC_NULL                      = 0xFFFFFFFF

} MMA_AudioType;

//====== MMA ========
typedef enum
{
    MMA_STOP,
    MMA_PLAY,
    MMA_PLAY_FILETSP,
    MMA_RESYNC,
    MMA_PLAY_FILE,
    MMA_BROWSE,
    MMA_PAUSE,
    MMA_PLAY_FRAME,
    MMA_PLAY_FRAME_GS,

} MMA_AUDIO_CONTROL;

typedef enum
{
    Audio_MAD_ChannelMode_MONO,
    Audio_MAD_ChannelMode_DUAL_MONO,
    Audio_MAD_ChannelMode_STEREO,
    Audio_MAD_ChannelMode_MULTI_CHAN
} Audio_MAD_ChannelMode;

typedef enum
{
  /*********  New Interface ********/
    Audio_Comm_infoType_MMA_init = 0x60,
    Audio_Comm_infoType_MMA_finish,

    /*******************************************************************/
    /* If you want add new cmd below,                                  */
    /* Please make sure ADEC 1 / 2/ 3 have "same" cmd in "same" order" */
    /*******************************************************************/
    Audio_Comm_infoType_ADEC1_capability = 0x70,
    Audio_Comm_infoType_ADEC1_setAudioDecoder,
    Audio_Comm_infoType_ADEC1_currAudDecStatus,
    Audio_Comm_infoType_ADEC1_AudioSyncStatus,   // 1 : AV-Sync  0: Free-run
    Audio_Comm_infoType_ADEC1_sampleRate,
    Audio_Comm_infoType_ADEC1_bitRate,
    Audio_Comm_infoType_ADEC1_acmod,
    Audio_Comm_infoType_ADEC1_soundmod,
    Audio_Comm_infoType_ADEC1_reqDataSize,
    Audio_Comm_infoType_ADEC1_okFrmCnt,
    Audio_Comm_infoType_ADEC1_errFrmCnt,
    Audio_Comm_infoType_ADEC1_1ms_timeStamp,
    Audio_Comm_infoType_ADEC1_33bit_PTS,
    Audio_Comm_infoType_ADEC1_33bit_STCPTS_DIFF,
    Audio_Comm_infoType_ADEC1_esBuf_reqFlag,       //new
    Audio_Comm_infoType_ADEC1_esBuf_reqAddr,
    Audio_Comm_infoType_ADEC1_esBuf_reqSize,
    Audio_Comm_infoType_ADEC1_esBuf_informDataRdy, //new
    Audio_Comm_infoType_ADEC1_esBuf_currLevel,
    Audio_Comm_infoType_ADEC1_pcmBuf_currLevel,
    Audio_Comm_infoType_ADEC1_playControl,
    Audio_Comm_infoType_ADEC1_FF2X,
    Audio_Comm_infoType_ADEC1_mute,
    Audio_Comm_infoType_syncSTC_in_mmTs,
    Audio_Comm_infoType_ADEC1_play_wo_output,
    Audio_Comm_infoType_ADEC1_audio_unsupported,
    Audio_Comm_infoType_ADEC1_UNI_PCMOutCnt,       // UNI_DEC1_PCM1 -> MIPS out size
    Audio_Comm_infoType_ADEC1_UNI_pcm_wptr,        // DEC1 -> UNI_DEC1_PCM1 wptr
    Audio_Comm_infoType_ADEC1_UNI_pcm_decSize,     // DEC1 -> UNI_DEC1_PCM1 w_size
    Audio_Comm_infoType_ADEC1_UNI_PCMInput_Addr,   // MISP -> UNI_DEC1_PCM3 wptr
    Audio_Comm_infoType_ADEC1_UNI_OutPCMLevel,     // UNI_DEC1_PCM3 level count

    /********************************************************************/
    /* Please Add ADEC 1 cmd above                                      */
    /* Please make sure ADEC 1 / 2/ 3 have "same" cmd in "same" order"  */
    /********************************************************************/
    Audio_Comm_infoType_ADEC1_setDecParam = 0x8F,
    Audio_Comm_infoType_ADEC1_getDecInfo1 = 0x90,
    Audio_Comm_infoType_ADEC1_getDecInfo2,
    Audio_Comm_infoType_ADEC1_getDecInfo3,
    Audio_Comm_infoType_ADEC1_getDecInfo4,
    Audio_Comm_infoType_ADEC1_getDecInfo5,
    Audio_Comm_infoType_ADEC1_getDecInfo6,
    Audio_Comm_infoType_ADEC1_getDecInfo7,
    Audio_Comm_infoType_ADEC1_getDecInfo8,

    /********************************************************************/
    /* If you want add new cmd below,                                   */
    /* Please make sure ADEC 1 / 2/ 3 have "same" cmd in "same" order"  */
    /********************************************************************/
    Audio_Comm_infoType_ADEC2_capability = 0xA0,
    Audio_Comm_infoType_ADEC2_setAudioDecoder,
    Audio_Comm_infoType_ADEC2_currAudDecStatus,
    Audio_Comm_infoType_ADEC2_AudioSyncStatus,   // 1 : AV-Sync  0: Free-run
    Audio_Comm_infoType_ADEC2_sampleRate,
    Audio_Comm_infoType_ADEC2_bitRate,
    Audio_Comm_infoType_ADEC2_acmod,
    Audio_Comm_infoType_ADEC2_soundmod,
    Audio_Comm_infoType_ADEC2_reqDataSize,
    Audio_Comm_infoType_ADEC2_okFrmCnt,
    Audio_Comm_infoType_ADEC2_errFrmCnt,
    Audio_Comm_infoType_ADEC2_1ms_timeStamp,
    Audio_Comm_infoType_ADEC2_33bit_PTS,
    Audio_Comm_infoType_ADEC2_33bit_STCPTS_DIFF,
    Audio_Comm_infoType_ADEC2_esBuf_reqFlag,
    Audio_Comm_infoType_ADEC2_esBuf_reqAddr,
    Audio_Comm_infoType_ADEC2_esBuf_reqSize,
    Audio_Comm_infoType_ADEC2_esBuf_informDataRdy,
    Audio_Comm_infoType_ADEC2_esBuf_currLevel,
    Audio_Comm_infoType_ADEC2_pcmBuf_currLevel,
    Audio_Comm_infoType_ADEC2_playControl,
    Audio_Comm_infoType_ADEC2_FF2X,
    Audio_Comm_infoType_ADEC2_mute,
    Audio_Comm_infoType_ADEC2_syncSTC_in_mmTs,
    Audio_Comm_infoType_ADEC2_play_wo_output,
    Audio_Comm_infoType_ADEC2_audio_unsupported,
    Audio_Comm_infoType_ADEC2_UNI_PCMOutCnt,       // UNI_DEC2_PCM1 -> MIPS out size
    Audio_Comm_infoType_ADEC2_UNI_pcm_wptr,        // DEC2 -> UNI_DEC2_PCM1 wptr
    Audio_Comm_infoType_ADEC2_UNI_pcm_decSize,     // DEC2 -> UNI_DEC2_PCM1 w_size
    Audio_Comm_infoType_ADEC2_UNI_PCMInput_Addr,   // MISP -> UNI_DEC2_PCM3 wptr
    Audio_Comm_infoType_ADEC2_UNI_OutPCMLevel,     // UNI_DEC2_PCM3 level count

    /********************************************************************/
    /* Please Add ADEC 2 cmd above                                      */
    /* Please make sure ADEC 1 / 2/ 3 have "same" cmd in "same" order"  */
    /********************************************************************/
    Audio_Comm_infoType_ADEC2_setDecParam = 0xBF,
    Audio_Comm_infoType_ADEC2_getDecInfo1 = 0xC0,
    Audio_Comm_infoType_ADEC2_getDecInfo2,
    Audio_Comm_infoType_ADEC2_getDecInfo3,
    Audio_Comm_infoType_ADEC2_getDecInfo4,
    Audio_Comm_infoType_ADEC2_getDecInfo5,
    Audio_Comm_infoType_ADEC2_getDecInfo6,
    Audio_Comm_infoType_ADEC2_getDecInfo7,
    Audio_Comm_infoType_ADEC2_getDecInfo8,

    /**********************************************************************/
    /* If you want add new cmd below,                                     */
    /* Please make sure ADEC 1 / 2/ 3 have "same" cmd in "same" order"    */
    /**********************************************************************/
    Audio_Comm_infoType_ADEC3_capability = 0xD0,
    Audio_Comm_infoType_ADEC3_setAudioDecoder,
    Audio_Comm_infoType_ADEC3_currAudDecStatus,
    Audio_Comm_infoType_ADEC3_AudioSyncStatus,   // 1 : AV-Sync  0: Free-run
    Audio_Comm_infoType_ADEC3_sampleRate,
    Audio_Comm_infoType_ADEC3_bitRate,
    Audio_Comm_infoType_ADEC3_acmod,
    Audio_Comm_infoType_ADEC3_soundmod,
    Audio_Comm_infoType_ADEC3_reqDataSize,
    Audio_Comm_infoType_ADEC3_okFrmCnt,
    Audio_Comm_infoType_ADEC3_errFrmCnt,
    Audio_Comm_infoType_ADEC3_1ms_timeStamp,
    Audio_Comm_infoType_ADEC3_33bit_PTS,
    Audio_Comm_infoType_ADEC3_33bit_STCPTS_DIFF,
    Audio_Comm_infoType_ADEC3_esBuf_reqFlag,
    Audio_Comm_infoType_ADEC3_esBuf_reqAddr,
    Audio_Comm_infoType_ADEC3_esBuf_reqSize,
    Audio_Comm_infoType_ADEC3_esBuf_informDataRdy,
    Audio_Comm_infoType_ADEC3_esBuf_currLevel,
    Audio_Comm_infoType_ADEC3_pcmBuf_currLevel,
    Audio_Comm_infoType_ADEC3_playControl,
    Audio_Comm_infoType_ADEC3_FF2X,
    Audio_Comm_infoType_ADEC3_mute,
    Audio_Comm_infoType_ADEC3_syncSTC_in_mmTs,
    Audio_Comm_infoType_ADEC3_play_wo_output,
    Audio_Comm_infoType_ADEC3_audio_unsupported,
    Audio_Comm_infoType_ADEC3_UNI_PCMOutCnt,       // UNI_DEC3_PCM1 -> MIPS out size
    Audio_Comm_infoType_ADEC3_UNI_pcm_wptr,        // DEC3 -> UNI_DEC3_PCM1 wptr
    Audio_Comm_infoType_ADEC3_UNI_pcm_decSize,     // DEC3 -> UNI_DEC3_PCM1 w_size
    Audio_Comm_infoType_ADEC3_UNI_PCMInput_Addr,   // MISP -> UNI_DEC3_PCM3 wptr
    Audio_Comm_infoType_ADEC3_UNI_OutPCMLevel,     // UNI_DEC3_PCM3 level count

    /**********************************************************************/
    /* Please Add ADEC 3 cmd above                                        */
    /* Please make sure ADEC 1 / 2/ 3 have "same" cmd in "same" order"    */
    /**********************************************************************/
    Audio_Comm_infoType_ADEC3_setDecParam = 0xEF,
    Audio_Comm_infoType_ADEC3_getDecInfo1 = 0xF0,
    Audio_Comm_infoType_ADEC3_getDecInfo2,
    Audio_Comm_infoType_ADEC3_getDecInfo3,
    Audio_Comm_infoType_ADEC3_getDecInfo4,
    Audio_Comm_infoType_ADEC3_getDecInfo5,
    Audio_Comm_infoType_ADEC3_getDecInfo6,
    Audio_Comm_infoType_ADEC3_getDecInfo7,
    Audio_Comm_infoType_ADEC3_getDecInfo8,

    /****************************************************/
    /*  General audio cmd  */
    /****************************************************/
    Audio_Comm_infoType_DecStatus = 0x00,
    Audio_Comm_infoType_SampleRate,
    Audio_Comm_infoType_SoundMode,
    Audio_Comm_infoType_DecOutMode,
    Audio_Comm_infoType_ChannelMode,
    Audio_Comm_infoType_MMFileSize,
    Audio_Comm_infoType_33Bit_PTS,
    Audio_Comm_infoType_33Bit_STCPTS_DIFF,
    Audio_Comm_infoType_1ms_PTS,
    Audio_Comm_infoType_DEC1_BufferSize,
    Audio_Comm_infoType_DEC1_BufferAddr,
    Audio_Comm_infoType_DEC1_MMTag,
    Audio_Comm_infoType_DEC1_MMResidualPCM,
    Audio_Comm_infoType_DEC1_ESBufferSize,
    Audio_Comm_infoType_DEC1_PCMBufferSize,
    Audio_Comm_infoType_DEC2_BufferSize,
    Audio_Comm_infoType_DEC2_BufferAddr = 0x10,
    Audio_Comm_infoType_DEC2_MMTag,
    Audio_Comm_infoType_DEC2_MMResidualPCM,
    Audio_Comm_infoType_DecodeErrorCnt,
    Audio_Comm_infoType_MM_FFx2,
    Audio_Comm_infoType_setBypassSPDIF_PAPB_chk,
    Audio_Comm_infoType_CompressBin_LoadCode,
    Audio_Comm_infoType_CompressBin_DDRAddress,
    Audio_Comm_infoType_DMAReader_BufferLevel,
    Audio_Comm_infoType_DMAReader_Command,
    Audio_Comm_infoType_SetSCMS,
    Audio_Comm_infoType_GetSCMS,
    Audio_Comm_infoType_ADC_InputGain,
    Audio_Comm_infoType_KTV_SetType,
    Audio_Comm_infoType_getSignal_Energy,
    Audio_Comm_infoType_getNR_Status,
    Audio_Comm_infoType_setNR_Threshold = 0x20,
    Audio_Comm_infoType_setSPDIF_FS,
    Audio_Comm_infoType_getSPDIF_FS,
    Audio_Comm_infoType_setSpdifDelay,
    Audio_Comm_infoType_ReadByte,
    Audio_Comm_infoType_WriteByte,
    Audio_Comm_infoType_hdmiTx_outType,
    Audio_Comm_infoType_hdmiTx_outFreq,
    Audio_Comm_infoType_PTS_info,
    Audio_Comm_infoType_RTSP_Mem,
    Audio_Comm_infoType_setSpdif_BufferProcess,
    Audio_Comm_infoType_DEC1_setBufferProcess,
    Audio_Comm_infoType_setES_REQ_SZ,
    Audio_Comm_infoType_AD_OutputStyle,
    Audio_Comm_infoType_getHDMI_CopyRight_C_Bit,
    Audio_Comm_infoType_getHDMI_CopyRight_L_Bit,
    Audio_Comm_infoType_Set_UNI_NEED_DECODE_FRMCNT = 0x30,
    Audio_Comm_infoType_Set_UNI_ES_Wptr,
    Audio_Comm_infoType_Get_UNI_ES_MEMCNT,
    Audio_Comm_infoType_Set_MENU_WT_PTR,
    Audio_Comm_infoType_Get_MENU_WT_PTR,
    Audio_Comm_infoType_Get_MENU_KEY_CNT,
    Audio_Comm_infoType_Get_CurSynthRate,
    Audio_Comm_infoType_ADC1_InputGain,
    Audio_Comm_infoType_mainpath_mute_status,
    Audio_Comm_infoType_spdif_mute_status,
    Audio_Comm_infoType_hdmiTX_mute_status,
    Audio_Comm_infoType_SRC_Compensation,
    Audio_Comm_infoType_Dump_Dsp_Info,
    Audio_Comm_infoType_Set_Video_STCPTS_DIFF,

    Audio_Comm_infoType_Get_UNI_ES_Base,
    Audio_Comm_infoType_Get_UNI_ES_Size,
    Audio_Comm_infoType_Get_UNI_PCM_Base = 0x40,
    Audio_Comm_infoType_Get_UNI_PCM_Size,
    Audio_Comm_infoType_Get_AccumEsCnt,
    Audio_Comm_infoType_DSP_PLL_Setting,
    Audio_Comm_infoType_Set_CallBackFunc,
    Audio_Comm_infoType_Set_ALSA_Mode,  /* For OMX Dual Mono Setting */
    Audio_Comm_infoType_HDMI_Unstable_Protect,
    Audio_Comm_infoType_HDMI_Unstable_Threshold,
    Audio_Comm_infoType_Set_TEE_Capibility,
    Audio_Comm_infoType_Parser_Spec,  /* Support ISO 11172-1 for MM */
    /*******************************************************/
    /*  Please Add common audio cmd above                  */
    /*******************************************************/

} Audio_COMM_infoType;

// MPEG
typedef enum
{   //info Type name                    //Attibtue       //Parameter
    Audio_MPEG_infoType_DecStatus,      //R              //0:unlock  1:lock
    Audio_MPEG_infoType_SampleRate,     //R              //
    Audio_MPEG_infoType_BitRate,        //R              //
    Audio_MPEG_infoType_FrameNum,       //R              //
    Audio_MPEG_infoType_SoundMode,      //W              //0: LR / 1:LL / 2:RR
    Audio_MPEG_infoType_stereoMode,     //R              //0: Stereo / 1: / 2:RR
    Audio_MPEG_infoType_Layer,          //R              //1 / 2 / 3
    Audio_MPEG_infoType_Header,         //R              //
    Audio_MPEG_infoType_FFSpeed,        //W              //
    Audio_MPEG_infoType_MMFileSize,     //W              //enum FILE_SIZE
    Audio_MPEG_infoType_Emphasis,       //R              //
    Audio_MPEG_DTV_AVSYNC_OFFSET,       //W, unit= 33bits offset
    Audio_MPEG_infoType_PCMBufLev,      //RW
    Audio_MPEG_infoType_BufferDelay,    //RW
    Audio_MPEG_DTV_AVSYNC_DISABLE_SETTING,
    Audio_MPEG_MuteFrm_PcmHighLevel_Threshold_NumTimeOut,
    Audio_MPEG_MuteFrm_PcmHighLevel_MuteNum,
    Audio_MPEG_infoType_PcmHighLevel_Pcmdata
} Audio_MPEG_infoType;

typedef enum
{
    AUD_MPEG_SOUNDMODE_LL,
    AUD_MPEG_SOUNDMODE_RR,
    AUD_MPEG_SOUNDMODE_LR,
    AUD_MPEG_SOUNDMODE_MIX_LR
}AUD_MPEG_SOUNDMODE;

typedef enum
{
    MPEG_SOUND_MODE_STEREO =0,
    MPEG_SOUND_MODE_JOINT_STEREO,
    MPEG_SOUND_MODE_DUAL_CHAN,
    MPEG_SOUND_MODE_MONO
}MPEG_SOUND_MODE;

/// MP3 Layer
typedef enum
{
    Audio_MP3_LAYER_RESERVED            = 0x0,
    Audio_MP3_LAYER_3                   = 0x1,
    Audio_MP3_LAYER_2                   = 0x2,
    Audio_MP3_LAYER_1                   = 0x3,
    Audio_MP3_LAYER_NOT_DETERMINE_YET   = 0xFF,
} Audio_MP3_LAYER;

// Dolby AC3
typedef enum
{   //info Type name                    //Attribute      //Parameter
    Audio_AC3_infoType_DecStatus,       //R              //0:unlock  1:lock
    Audio_AC3_infoType_SampleRate,      //R              //
    Audio_AC3_infoType_BitRate,         //R              //
    Audio_AC3_infoType_Dialnorm,        //R              //
    Audio_AC3_infoType_Acmod,           //R              //
    Audio_AC3_infoType_DrcMode,         //RW             //
    Audio_AC3_infoType_DownmixMode,     //RW             //
    Audio_AC3_infoType_MMFileSize,      //Not supported  //
    Audio_AC3_infoType_PCMBufLevel,     //R              //
    Audio_AC3_infoType_BufferDelay,     //RW             //
    Audio_AC3_infoType_SyncwordFound_Count,
} Audio_AC3_infoType;

// Dolby AC3P
typedef enum
{   //info Type name                     //Attribute     //Parameter
    Audio_AC3P_infoType_DecStatus,       //R             //
    Audio_AC3P_infoType_SampleRate,      //R             //
    Audio_AC3P_infoType_BitRate,         //R             //
    Audio_AC3P_infoType_Dialnorm,        //R             //
    Audio_AC3P_infoType_Acmod,           //R             //
    Audio_AC3P_infoType_DrcMode,         //RW            //
    Audio_AC3P_infoType_DownmixMode,     //RW            //
    Audio_AC3P_infoType_MMFileSize,      //W             //
    Audio_AC3P_infoType_syncSTC_in_mmTs, //W             //
    Audio_AC3P_infoType_hdmiTxBypass_enable,
    Audio_AC3P_infoType_AC3Type,
    Audio_AC3P_infoType_FrameSize,
    Audio_AC3P_infoType_BSMode,
    Audio_AC3P_infoType_BYTESWAP,
    Audio_AC3P_infoType_enableDolbyBulletin11,//W       // True or False          //default is enabled
    Audio_AC3P_DTV_AVSYNC_OFFSET,        //W, unit= 33bits offset
    Audio_AC3P_infoType_hdmiAC3inSE,
    Audio_AC3P_DTV_AVSYNC_DISABLE_SETTING,
    Audio_AC3P_infoType_hdmi_in_support_DDP,
    Audio_AC3P_infoType_Drc_HighCutScale,
    Audio_AC3P_infoType_Drc_LowBootScale,
} Audio_AC3P_infoType;

typedef enum
{
    AUD_Dolby_SOUNDMODE_LR              = 0x0,
    AUD_Dolby_SOUNDMODE_LL              = 0x1,
    AUD_Dolby_SOUNDMODE_RR              = 0x2,
}AUD_Dolby_SOUNDMODE;

typedef enum
{
    DOLBY_MONO,
    DOLBY_STEREO,
    DOLBY_MULTI_CHAN
}DOLBY_AC_MODE;

typedef enum
{
    DOLBY_DOWNMIX_MODE_LTRT,
    DOLBY_DOWNMIX_MODE_LORO,
    DOLBY_DOWNMIX_MODE_AUTO
}DOLBY_DOWNMIX_MODE;

typedef enum
{
    LINE_MODE,
    RF_MODE,
}DOLBY_DRC_MODE;

typedef enum
{
    AC3_ENABLE,
    AC3_DISABLE
}AC3_DIS_EN;


// DTS
typedef enum
{   //info Type name                     //Attribute    //Parameter
    Audio_DTS_infoType_DecStatus,        //R            //
    Audio_DTS_infoType_KernelVersion,    //R            //
    Audio_DTS_infoType_SampleRate,       //R            //
    Audio_DTS_infoType_BitRate,          //R            //
    Audio_DTS_infoType_CD_MODE,          //R            //
    Audio_DTS_infoType_Amode,            //R            //
    Audio_DTS_infoType_DMIX_LFE_EN,      //RW           //
    Audio_DTS_infoType_DrcMode,          //RW           //
    Audio_DTS_infoType_DownmixMode,      //RW           //
    Audio_DTS_infoType_Dialnorm_EN,      //RW           //
    Audio_DTS_infoType_ESDataServiceMode,//RW           //
    Audio_DTS_infoType_MMFileSize,       //W            //
    Audio_DTS_infoType_syncSTC_in_mmTs,  //W            //
    Audio_DTS_infoType_ESData_ByteSwap,  //W            //
    Audio_DTS_infoType_CertMode,         //W            //
    Audio_DTS_infoType_HDMI_DSP_SEL,
} Audio_DTS_infoType;

typedef enum
{   //ctrl Type name                     //Attribute
    Audio_DTS_Ctrl_DMIX_LFE_OFF         = 0x0,
    Audio_DTS_Ctrl_DMIX_LFE_ON          = 0x1,
    Audio_DTS_Ctrl_Drc_OFF              = 0x0,
    Audio_DTS_Ctrl_Drc_50               = 0x1,
    Audio_DTS_Ctrl_Drc_100              = 0x2,
    Audio_DTS_Ctrl_Downmix_LoRo         = 0x0,
    Audio_DTS_Ctrl_Downmix_LtRt         = 0x1,
    Audio_DTS_Ctrl_Dialnorm_OFF         = 0x0,
    Audio_DTS_Ctrl_Dialnorm_ON          = 0x1,
    Audio_DTS_Ctrl_POLLINGMode          = 0x0,
    Audio_DTS_Ctrl_INTRPTMode           = 0x1,
    Audio_DTS_Ctrl_ByteSwap_OFF         = 0x0,
    Audio_DTS_Ctrl_ByteSwap_ON          = 0x1,
    Audio_DTS_Ctrl_CertMode_OFF         = 0x0,
    Audio_DTS_Ctrl_CertMode_ON          = 0x1,
} Audio_DTS_CtrlType;
    
   
typedef enum
{
    Audio_WMA_infoType_DecStatus,
    Audio_WMA_infoType_SampleRate,
    Audio_WMA_infoType_BitRate,
    Audio_WMA_infoType_Asf_Param,
    Audio_WMA_infoType_FFSpeed,
    Audio_WMA_infoType_MMFileSize
} Audio_WMA_infoType;

typedef enum
{   //info Type name                    //Attibtue      //Parameter
    Audio_AAC_error_count,              //R             //
    Audio_AAC_infoType_DrcMode,         //RW            //
    Audio_AAC_infoType_DownmixMode,     //RW            //
    Audio_AAC_dec_unsupported,          //R             //
    Audio_AAC_ts_file_end_ntfi,         //R
    Audio_AAC_DTV_AVSYNC_OFFSET,        //W, unit= 33bits offset
    Audio_AAC_DTV_AVSYNC_DISABLE_SETTING
} Audio_AAC_infoType;
 
typedef enum
{   //info Type name                    //Attibtue      //Parameter
    Audio_RA8LBR_NumCodes,              //w
    Audio_RA8LBR_Samples,               //w
    Audio_RA8LBR_SampleRate,            //w
 
    Audio_RA8LBR_Channels1,             //w
    Audio_RA8LBR_Regions1,              //w
    Audio_RA8LBR_cplStart1,             //w
    Audio_RA8LBR_cplQbits1,             //w
    Audio_RA8LBR_FrameSize1,            //w

    Audio_RA8LBR_Channels2,             //w
    Audio_RA8LBR_Regions2,              //w
    Audio_RA8LBR_cplStart2,             //w
    Audio_RA8LBR_cplQbits2,             //w
    Audio_RA8LBR_FrameSize2,            //w

    Audio_RA8LBR_Channels3,             //w
    Audio_RA8LBR_Regions3,              //w
    Audio_RA8LBR_cplStart3,             //w
    Audio_RA8LBR_cplQbits3,             //w
    Audio_RA8LBR_FrameSize3,            //w
 
    Audio_RA8LBR_Channels4,             //w
    Audio_RA8LBR_Regions4,              //w
    Audio_RA8LBR_cplStart4,             //w
    Audio_RA8LBR_cplQbits4,             //w
    Audio_RA8LBR_FrameSize4,            //w
 
    Audio_RA8LBR_Channels5,             //w
    Audio_RA8LBR_Regions5,              //w
    Audio_RA8LBR_cplStart5,             //w
    Audio_RA8LBR_cplQbits5,             //w
    Audio_RA8LBR_FrameSize5,            //w

    Audio_RA8LBR_infoType_DecStatus,    //R
} Audio_RA8LBR_infoType;

typedef enum
{
    LPCM                                = 1,
    MS_ADPCM                            = 2,
    G711_A_LAW                          = 6,
    G711_u_LAW                          = 7,
    IMA_ADPCM                           = 17
}XPCM_TYPE;
 
typedef enum
{
    SAMPLE_RATE_48000,
    SAMPLE_RATE_44100,
    SAMPLE_RATE_32000,
    SAMPLE_RATE_24000,
    SAMPLE_RATE_22050,
    SAMPLE_RATE_16000,
    SAMPLE_RATE_12000,
    SAMPLE_RATE_11025,
    SAMPLE_RATE_8000,
}SAMPLE_RATE;
 
// AD & Mixer
typedef enum
{
    MAIN_MIX_AD,
    AD_MIX_MAIN,
}AD_MIX_MODE;
 
typedef enum
{
    MIX_OFF,
    MIX_ON,
}MIX_ONOFF;
  
typedef enum
{
    FILE_SIZE_1KB,
    FILE_SIZE_2KB,
    FILE_SIZE_4KB,
    FILE_SIZE_8KB,
    FILE_SIZE_16KB,
    FILE_SIZE_32KB,
    FILE_SIZE_64KB,
    FILE_SIZE_256,
    FILE_SIZE_512,
    FILE_SIZE_64,
    FILE_SIZE_128
}FILE_SIZE;
 

typedef enum
{
    AU_DVB_MODE_STEREO,                 ///< 0:STEREO
    AU_DVB_MODE_LL,                     ///< 1: LL
    AU_DVB_MODE_RR,                     ///< 2: RR
    AU_DVB_MODE_MUTE                    ///< 3:MUTE
}AU_DVB_MODE;
  
//  enum for dvb decoder command
typedef enum
{
    AU_DVB_DECCMD_STOP                  = 0,
    AU_DVB_DECCMD_PLAY                  = 1,
    AU_DVB_DECCMD_PLAYFILETSP           = 2,
    AU_DVB_DECCMD_RESYNC                = 3,
    AU_DVB_DECCMD_PLAYFILE              = 4,
    AU_DVB_DECCMD_STARTBROWSE           = 5,
    AU_DVB_DECCMD_PAUSE                 = 6,
    AU_DVB_DECCMD_PLAYFRAME             = 8,            // Uniplayer, Mstreamer for TSP input
    AU_DVB_DECCMD_PLAYFRAME_STAGE       = 9,            // Stagecraft
    AU_DVB_DECCMD_PLAYFRAME_GS          = 10,           // Uniplayer, Gstreamer for ES copy
    AU_DVB_DECCMD_PLAYFILE2_PTS         = 11,
    AU_DVB_DECCMD_PLAY_AD                    = 12,
    AU_DVB_DECCMD_STOP_AD                    = 13,
    AU_DVB_DECCMD_AVSYNC                = 0x10,
    AU_DVB_DECCMD_FREERUN               = 0x20,
} AU_DVB_DECCMD;

typedef enum
{
    AU_DVB_ENCCMD_STOP,   // 0
    AU_DVB_ENCCMD_START   // 1
} AU_DVB_ENCCMD;

typedef enum
{
    AU_DVB_ENCBR_192K,                  // 0
    AU_DVB_ENCBR_384K,                  // 1
    AU_DVB_ENCBR_128K,                  // 2
    AU_DVB_ENCBR_64K                    // 3
} AU_DVB_ENCBR;
 
typedef enum
{
    WMA_PARAMTYPE_VERSION,
    WMA_PARAMTYPE_CHANNELS,
    WMA_PARAMTYPE_SAMPLERATE,
    WMA_PARAMTYPE_BYTERATE,
    WMA_PARAMTYPE_BLOCKALIGN,
    WMA_PARAMTYPE_ENCOPT,
    WMA_PARAMTYPE_PARSINGBYAPP,
    WMA_PARAMTYPE_BITS_PER_SAMPLE,
    WMA_PARAMTYPE_CHANNELMASK,
    WMA_PARAMTYPE_DRC_PARAM_EXIST,
    WMA_PARAMTYPE_DRC_RMS_AMP_REF,
    WMA_PARAMTYPE_DRC_RMS_AMP_TARGET,
    WMA_PARAMTYPE_DRC_PEAK_AMP_REF,
    WMA_PARAMTYPE_DRC_PEAK_AMP_TARGET,
    WMA_PARAMTYPE_MAX_PACKET_SIZE
}WMA_ASF_PARMTYPE;

enum
{
    DSP_INIT_FINISH_ACK,
    DSP_READY_FOR_RELOAD_ACK,
    DSP_RELOAD_FINISH_ACK,
    MCU_START_TO_RUN_CMD,
    MCU_START_RELOAD_CMD,
    MCU_RELOAD_FINISH_CMD
};

//================================================================
//  MAD2
//================================================================
enum
{
    AU_DVB2_SYS_MPEG_AD,
    AU_DVB2_SYS_AC3_AD,
    AU_DVB2_SYS_AC3P_AD,
    AU_DVB2_SYS_AAC_AD,
    AU_DVB2_SYS_DDE,
    AU_DVB2_SYS_GAAC_AD,
    AU_DVB2_SYS_MP3,
    AU_DVB2_SYS_MPEG_EN,
    AU_DVB2_SYS_DTSE,
    AU_DVB2_SYS_XPCM,
    AU_DVB2_SYS_KTV,
    AU_DVB2_SYS_KTV2,
    AU_DVB2_SYS_NONE,
};

// for dvb2 decoder command
typedef enum
{
    AU_DVB2_DECCMD_STOP,                //0
    AU_DVB2_DECCMD_PLAY,                //1
    AU_DVB2_DECCMD_PLAYFILETSP          = 2,
    AU_DVB2_DECCMD_RESYNC,
    AU_DVB2_DECCMD_PLAYFILE             = 4,
    AU_DVB2_DECCMD_PAUSE                = 6
}AU_DVB2_DECCMD;

// for dvb2 free run mode
typedef enum
{
    AU_DVB2_FreeRunMode_AVsync,         //0
    AU_DVB2_FreeRunMode_FreeRun,        //1
}AU_DVB2_FreeRunMode;

enum
{
    AUD_SIF,                            //0
    AUD_DVB                             //1
};
     
enum
{
    DSP_DEC,                            //0
    DSP_SE,                             //1
    DSP_ADV,                              //2
    DSP_MAD                             //3
};

enum
{
    DSP_SYSTEM,                         //0
    DSP_ALG,                            //1
};
   
// DTV decoder sample rate definition
typedef enum
{
    AUDIO_FS_NONE,
    AUDIO_FS_8KHZ,
    AUDIO_FS_11KHZ,
    AUDIO_FS_12KHZ,
    AUDIO_FS_16KHZ,
    AUDIO_FS_22KHZ,
    AUDIO_FS_24KHZ,
    AUDIO_FS_32KHZ,
    AUDIO_FS_44KHZ,
    AUDIO_FS_48KHZ,
    AUDIO_FS_64KHZ,
    AUDIO_FS_88KHZ,
    AUDIO_FS_96KHZ,
    AUDIO_FS_176KHZ,
    AUDIO_FS_192KHZ,
    AUDIO_FS_UNSUPPORT                  = 0xFF,
} AUDIO_FS_TYPE;
 
typedef struct
{
    AUDIO_HDMI_RX_TYPE      audio_type;
    AUDIO_FS_TYPE           sampleRate;
} ST_HDMI_AUDIO_STATUS;
// DTV decoder sound mode type definition
typedef enum
{
    AUD_CH_MODE_DUAL_MONO               = 0x0,              //MPEG/DDP/MS10
    AUD_CH_MODE_MONO                    = 0x1,              //MPEG/DDP/MS10
    AUD_CH_MODE_STEREO                  = 0x2,              //MPEG/DDP/MS10
    AUD_CH_MODE_3_0_MODE                = 0x3,              //     DDP/MS10
    AUD_CH_MODE_2_1_MODE                = 0x4,              //     DDP/MS10
    AUD_CH_MODE_3_1_MODE                = 0x5,              //     DDP/MS10
    AUD_CH_MODE_2_2_MODE                = 0x6,              //     DDP/MS10
    AUD_CH_MODE_3_2_MODE                = 0x7,              //     DDP/MS10
    AUD_CH_MODE_JOINT_STEREO,//MPEG
    AUD_CH_MODE_NONE,
} AUD_CH_MODE_TYPE;
 
//================================================================
//  KTV
//================================================================
typedef enum
{                                       // Chip     :   T3         U3         T12
    AUD_KTV_MODEL1,                     // Customer : iSing99      X        Multak
    AUD_KTV_MODEL2,                     // Customer : Multak     Multak
    AUD_KTV_MODEL3,                     // Customer :  thunderstone        X
    AUD_KTV_MODEL4,                     // Customer :  Konka       X
}AUDIO_KTV_MODEL;
  
typedef enum
{   /*  Model               AUD_KTV_MODEL1    AUD_KTV_MODEL2    AUD_KTV_MODEL3  *
     *  Chip                T3-iSing99        U3-Multak                         *
     *--------------------------------------------------------------------------*/
    AUD_KTV_infoType1,                  // ScoringCommand
    AUD_KTV_infoType2,                  // EchoLevel
    AUD_KTV_infoType3,                  // EchoDeep
    AUD_KTV_infoType4,                  // MICGain
    AUD_KTV_infoType5,                  // (TBD)
    AUD_KTV_infoType6,                  // (TBD)
    AUD_KTV_infoType7,                  // (TBD)
    AUD_KTV_infoType8,                  // (TBD)
    AUD_KTV_infoType9,                  // (TBD)
    AUD_KTV_infoType10,                 // (TBD)
    AUD_KTV_infoType11,                 // (TBD)
    AUD_KTV_infoType12,                 // (TBD)
    AUD_KTV_infoType13,                 // (TBD)
    AUD_KTV_infoType14,                 // (TBD)
    AUD_KTV_infoType15,                 // (TBD)
    AUD_KTV_infoType16,                 // (TBD)
}AUDIO_KTV_INFOTYPE;
  
typedef enum
{   /*  Model             AUD_KTV_MODEL1    AUD_KTV_MODEL2    AUD_KTV_MODEL3    *
     *  Chip              T3-iSing99        U3-Multak                           *
     *--------------------------------------------------------------------------*/
    AUD_KTV_ParamType1,                 // AvMICVol
    AUD_KTV_ParamType2,                 // PitchCnt
    AUD_KTV_ParamType3,                 // Pitch
    AUD_KTV_ParamType4,                 // Energy
    AUD_KTV_ParamType5,                 // (TBD)
    AUD_KTV_ParamType6,                 // (TBD)
    AUD_KTV_ParamType7,
    AUD_KTV_ParamType8,
    AUD_KTV_ParamType9,
    AUD_KTV_ParamType10,
    AUD_KTV_ParamType11,
    AUD_KTV_ParamType12,
    AUD_KTV_ParamType13,
    AUD_KTV_ParamType14,
    AUD_KTV_ParamType15,
    AUD_KTV_ParamType16,
}AUDIO_KTV_PARAMTYPE;

typedef enum
{
    PCM_VOL,
    MIC_VOL,
    MP3_VOL,
    GAME1_VOL,
    GAME2_VOL,
    ECHO1_VOL,
    ECHO2_VOL,
}AUDIO_MIX_VOL_TYPE;
   
#define code
///< Threshold table structure
typedef struct
{
    MS_U8  HiByteValue;                 ///< Threshold high-byte
    MS_U8  LowByteValue;                ///< Threshold low-byte
} THR_TBL_TYPE;
 
//================================================================
//  Sound Enum
//================================================================
// ADC Input Gain Type Definition
typedef enum
{
    AUD_ADC_GAIN_0dB = 0,               //  0dB
    AUD_ADC_GAIN_NEG_3dB,               // -3dB
    AUD_ADC_GAIN_NEG_6dB,               // -6dB
    AUD_ADC_GAIN_3dB,                   //  3dB
    AUD_ADC_GAIN_6dB,                   //  6dB
    AUD_ADC_GAIN_9dB,                   //  9dB
    AUD_ADC_GAIN_12dB,                  // 12dB
    AUD_ADC_GAIN_15dB,                  // 15dB
} AUD_ADC_GAIN_TYPE;
     
typedef struct
{
    MS_U8  param1;                      ///< param1
    MS_U8  param2;                      ///< param2
    MS_U8  param3;                      ///< param1
    MS_U8  param4;                      ///< param2
} Sound_SET_Param;
  
typedef struct
{
    MS_U8  AvcThreshold;                ///< AvcThreshold
    MS_U8  AvcMode;                     ///< AvcMode
    MS_U8  AvcAT;                       ///< AvcAT
    MS_U8  AvcRT;                       ///< AvcRT
} Sound_AVC_param;
  
typedef struct
{
    MS_U8  SurroundXA;                  ///< SurroundXA
    MS_U8  SurroundXB;                  ///< SurroundXB
    MS_U8  SurroundXK;                  ///< SurroundXK
    MS_U8  SurroundLPFGain;             ///< SurroundLPFGain
} Sound_SURR_param;

typedef enum
{
    Sound_SET_Type_SetPreScale,
    Sound_SET_Type_SetMute,
    Sound_SET_Type_SetBalance,
    Sound_SET_Type_EnableEQ,
    Sound_SET_Type_EnablePEQ,
    Sound_SET_Type_EnableTone,
    Sound_SET_Type_EnableAutoVolume,
    Sound_SET_Type_EnableSurround,
    Sound_SET_Type_SetBass,
    Sound_SET_Type_EnableBalance,
    Sound_SET_Type_AbsoluteBass,
    Sound_SET_Type_SetTreble,
    Sound_SET_Type_SetEq,
    Sound_SET_Type_SetEq_7band,
    Sound_SET_Type_SetAvc,
    Sound_SET_Type_SetAudioDelay,
    Sound_SET_Type_SetSurround,
    Sound_SET_Type_ConvertVolumeUnit,
    Sound_SET_Type_SetDCOffet,
    Sound_SET_Type_EnableSineTone,
} Sound_SET_Type;
  
typedef enum
{
    Sound_SET_PARAM_PreScale,
    Sound_SET_PARAM_Balance,
    Sound_SET_PARAM_EQ,
    Sound_SET_PARAM_Surround_XA,
    Sound_SET_PARAM_Surround_XB,
    Sound_SET_PARAM_Surround_XK,
    Sound_SET_PARAM_Surround_LPFGAIN,
    Sound_SET_PARAM_Treble,
    Sound_SET_PARAM_Bass,
    Sound_SET_PARAM_AbsoluteBass,
    Sound_SET_PARAM_Avc_Mode,
    Sound_SET_PARAM_NR_Threshold,
    Sound_SET_PARAM_Avc_Threshold,
    Sound_SET_PARAM_Avc_AT,
    Sound_SET_PARAM_Avc_RT,
    Sound_SET_PARAM_AudioDelay,
    Sound_SET_PARAM_DCOffet,
    Sound_SET_PARAM_PEQ_48K_A0,
    Sound_SET_PARAM_PEQ_48K_A1,
    Sound_SET_PARAM_PEQ_48K_A2,
    Sound_SET_PARAM_PEQ_48K_B1,
    Sound_SET_PARAM_PEQ_48K_B2,
    Sound_SET_PARAM_PEQ_32K_A0,
    Sound_SET_PARAM_PEQ_32K_A1,
    Sound_SET_PARAM_PEQ_32K_A2,
    Sound_SET_PARAM_PEQ_32K_B1,
    Sound_SET_PARAM_PEQ_32K_B2,
    Sound_SET_PARAM_PEQ_SCALE,
    Sound_SET_PARAM_AbsoluteEQ,
    Sound_SET_PARAM_Drc_Threshold,
    Sound_SET_PARAM_DMAReader,
    Sound_SET_PARAM_AVC_S_Offset,
} Sound_SET_PARAM_Type;

typedef enum
{
    Sound_GET_PARAM_PreScale,
    Sound_GET_PARAM_Balance_L,
    Sound_GET_PARAM_Balance_R,
    Sound_GET_PARAM_EQ,
    Sound_GET_PARAM_Surround_XA,
    Sound_GET_PARAM_Surround_XB,
    Sound_GET_PARAM_Surround_XK,
    Sound_GET_PARAM_Surround_LPFGAIN,
    Sound_GET_PARAM_Treble,
    Sound_GET_PARAM_Bass,
    Sound_GET_PARAM_Avc_Mode,
    Sound_GET_PARAM_Avc_Threshold,
    Sound_GET_PARAM_Avc_AT,
    Sound_GET_PARAM_Avc_RT,
    Sound_GET_PARAM_AudioDelay,
    Sound_GET_PARAM_DCOffet,
    Sound_GET_PARAM_NR_Threshold,
    Sound_GET_PARAM_NR_Status,
    Sound_GET_PARAM_getSignal_Energy,
    Sound_GET_PARAM_EQ_Status,
    Sound_GET_PARAM_PEQ_Status,
    Sound_GET_PARAM_Tone_Status,
    Sound_GET_PARAM_AutoVolume_Status,
    Sound_GET_PARAM_Surround_Status,
    Sound_GET_PARAM_HPF_Status,
    Sound_GET_PARAM_Drc_Threshold,
    Sound_GET_PARAM_DMAReader_Buffer_Addr,
} Sound_GET_PARAM_Type;

typedef enum
{
//  Sound_ENABL_Type_PreScale,
    Sound_ENABL_Type_EQ,
    Sound_ENABL_Type_PEQ,
    Sound_ENABL_Type_Tone,               //treble/bass
    Sound_ENABL_Type_AutoVolume,
    Sound_ENABL_Type_Surround,
    Sound_ENABL_Type_Balance,
    Sound_ENABL_Type_DRC,
    Sound_ENABL_Type_KTVEcho,
    Sound_ENABL_Type_Hpf,
} Sound_ENABLE_Type;

typedef enum
{
    AdvSound_SET_Type_VDS_Enable,
    AdvSound_SET_Type_VSPK_Enable,
    AdvSound_SET_Type_VSPK_SetWMod,
    AdvSound_SET_Type_VSPK_SetSMod,
    AdvSound_SET_Type_SRS_Enable,
    AdvSound_SET_Type_SRS_DC,
    AdvSound_SET_Type_SRS_TruBass,
    AdvSound_SET_Type_SRS_SetTsxtPara,
    AdvSound_SET_Type_TSHD_Enable,
    AdvSound_SET_Type_TSHD_TruBass,
    AdvSound_SET_Type_TSHD_Definition,
    AdvSound_SET_Type_TSHD_Clarity,
    AdvSound_SET_Type_TSHD_TruSurr,
    AdvSound_SET_Type_TSHD_Limiter,
    AdvSound_SET_Type_TSHD_SRS3D,
    AdvSound_SET_Type_SRS_SetTshdPara,
    AdvSound_SET_Type_TruVolume_Enable,
    AdvSound_SET_Type_BBE_SetBbeMode,
    AdvSound_SET_CV2_Enable,
    AdvSound_SET_CV2_SetPara,
    AdvSound_SET_CV_SetPara,
    AdvSound_SET_AV_SetPara,
    AdvSound_SET_SetEQPara,
    AdvSound_SET_CV_SetLevel,
    AdvSound_SET_ADSY_SetPara,
} AdvSound_SET_Type;

typedef enum
{
    ADVSOUND_EN_TYPE
} AdvSound_GET_Type;


//================================================================
//  Advance Sound Enum
//================================================================
typedef enum
{
    MDRV_AUD_ADVSND_PL2,                //ID = 0
    MDRV_AUD_ADVSND_BBE,                //ID = 1
    MDRV_AUD_ADVSND_SRS,                //ID = 2
    MDRV_AUD_ADVSND_VDS,                //ID = 3
    MDRV_AUD_ADVSND_VSPK,               //ID = 4
    MDRV_AUD_ADVSND_SUPV,               //ID = 5
    MDRV_AUD_ADVSND_TSHD,               //ID = 6
    MDRV_AUD_ADVSND_XEN                 //ID = 7
} En_ASE_advsndType;

//SRS APOLLO
typedef enum
{
    AU_SRS_APOLLO_EN,
    AU_SRS_TSHD_EN,
    AU_SRS_TRUBASS_FRONT_EN,
    AU_SRS_DEFINITION_FRONT_EN,
    AU_SRS_DIALOG_CLARITY_EN,
    AU_SRS_SURROUND_LEVEL_CTRL,
    AU_SRS_TSHD_INPUT_GAIN,
    AU_SRS_DEFINITION_FRONT_CTRL,
    AU_SRS_DIALOG_CLARITY_CTRL,
    AU_SRS_TRUBASS_FRONT_CTRL,
    AU_SRS_LOW_END_FRONT_SPEAKER_FREQ,
    AU_SRS_HL_EN,
    AU_SRS_HL_LIMIT_LEVEL,
    AU_SRS_HL_BOOST_GAIN,
    AU_SRS_APOLLO_HEADROOM_GAIN,
    AU_SRS_AEQ_PEQ_EN,
    AU_SRS_AEQ_HPF_EN,
    AU_SRS_AEQ_GEQ_EN,
    AU_SRS_VIQ_EN,
    AU_SRS_VIQ_MODE,
    AU_SRS_VIQ_VOL_REF_LEVEL,
    AU_SRS_VIQ_MAX_GAIN,
    AU_SRS_VIQ_NOISE_MNGR_THLD,
    AU_SRS_VIQ_CALIBRATE,
    AU_SRS_VIQ_NOISE_MNGR_EN,
    AU_SRS_AEQ_HPF_FC,
    AU_SRS_VIQ_INPUT_GAIN,
    AU_SRS_VIQ_OUTPUT_GAIN,
} AU_SRS_APOLLO_TYPE;


////////////////////////////////////////////////////////
/** Total Sonics modes for DBXTV_SetMode() */
typedef enum _DBXTV_TotSonMode
{
    E_TOTSON_ON        = 0,
    E_TOTSON_OFF,
} EN_DBXTV_TotSonMode;

/** Total Volume modes for DBXTV_SetMode() */
typedef enum _DBXTV_TotVolMode
{
    E_TOTVOL_NORMAL     = 0,
    E_TOTVOL_NIGHT,
    E_TOTVOL_OFF,
} EN_DBXTV_TotVolMode;

/** Total Surround modes for DBXTV_SetMode() */
typedef enum _DBXTV_TotSurMode
{
    E_TOTSUR_ON     = 0,
    E_TOTSUR_OFF,
} EN_DBXTV_TotSurMode;

/** Total Surround modes for HAL_DBXTV_SetOnOff() */
typedef enum _DBXTV_TurnOnOff
{
    E_DBXTV_TurnOff     = 0,
    E_DBXTV_TurnOn,
} EN_DBXTV_TurnOnOff;

////////////////////////////////////////////////////////


typedef enum
{
    AU_SRS_THEATER_EN,
    AU_SRS_THEATER_HPF_EN,
    AU_SRS_THEATER_VIQ_EN,
    AU_SRS_THEATER_CS_EN,
    AU_SRS_THEATER_TRUDIALOG_EN,
    AU_SRS_THEATER_INPUT_GAIN,
    AU_SRS_THEATER_OUTPUT_GAIN,
    AU_SRS_THEATER_BYPASS_GAIN,
    AU_SRS_THEATER_HEADROOM_GAIN,
    AU_SRS_THEATER_INPUT_MODE,
    AU_SRS_THEATER_VIQ_INPUT_GAIN,
    AU_SRS_THEATER_VIQ_OUTPUT_GAIN,
    AU_SRS_THEATER_VIQ_BYPASS_GAIN,
    AU_SRS_THEATER_VIQ_VOLUME_MODE,
    AU_SRS_THEATER_VOLHD_MAXGAIN_CONTROL,
    AU_SRS_THEATER_VOLHD_NORMALIZER_EN,
    AU_SRS_THEATER_VOLHD_NORMTHRESH,
    AU_SRS_THEATER_VOLHD_SMOOTH_EN,
    AU_SRS_THEATER_VOLHD_LKFS,
    AU_SRS_THEATER_CS_INPUT_GAIN,
    AU_SRS_THEATER_CS_PROCESSING_MODE,
    AU_SRS_THEATER_CS_LR_OUTPUT_GAIN,
    AU_SRS_THEATER_CS_LSRS_OUTPUT_GAIN,
    AU_SRS_THEATER_CS_CENTER_OUTPUT_GAIN,
    AU_SRS_THEATER_TRUDIALOG_INPUT_GAIN,
    AU_SRS_THEATER_TRUDIALOG_OUTPUT_GAIN,
    AU_SRS_THEATER_TRUDIALOG_BYPASS_GAIN,
    AU_SRS_THEATER_TRUDIALOG_PROCESS_GAIN,
    AU_SRS_THEATER_TRUDIALOG_CLARITY_GAIN,
    AU_SRS_THEATER_HPF_ORDER,
    AU_SRS_THEATER_HPF_COEFS,
    AU_SRS_THEATER_TSHD_EN,
    AU_SRS_THEATER_TSHD_SURR_EN,
    AU_SRS_THEATER_TSHD_TRUBASS_FRONT_EN,
    AU_SRS_THEATER_TSHD_DEFINITION_FRONT_EN,
    AU_SRS_THEATER_TSHD_DIALOG_CLARITY_EN,
    AU_SRS_THEATER_TSHD_TRUBASS_LEVEL_INDEPENDENT_EN,
    AU_SRS_THEATER_HPF_END_EN,
    AU_SRS_THEATER_HL_EN,
    AU_SRS_THEATER_TSHD_SURROUND_LEVEL_CTRL,
    AU_SRS_THEATER_TSHD_INPUT_GAIN,
    AU_SRS_THEATER_TSHD_OUTPUT_GAIN,
    AU_SRS_THEATER_TSHD_DEFINITION_FRONT_CTRL,
    AU_SRS_THEATER_TSHD_DIALOG_CLARITY_CTRL,
    AU_SRS_THEATER_TSHD_TRUBASS_FRONT_CTRL,
    AU_SRS_THEATER_TSHD_TRUBASS_SPEAKER_SIZE,
    AU_SRS_THEATER_TSHD_TRUBASS_COMPRESSOR_CTRL,
    AU_SRS_THEATER_TSHD_TRUBASS_PROCESS_MODE,
    AU_SRS_THEATER_TSHD_TRUBASS_SPEAKER_AUDIO,
    AU_SRS_THEATER_TSHD_TRUBASS_SPEAKER_ANALYSIS,
    AU_SRS_THEATER_HL_LIMIT_LEVEL_CTRL,
    AU_SRS_THEATER_HL_BOOST_GAIN,
    AU_SRS_THEATER_HPF_CUTOFF,
    AU_SRS_THEATER_HPF_END_CUTOFF,
    AU_SRS_THEATER_CC3D_EN,//param54
    AU_SRS_THEATER_CC3D_DEPTH_PROCESS_EN,//param55
    AU_SRS_THEATER_CC3D_3D_SURR_BOOST_EN,//param56
    AU_SRS_THEATER_CC3D_FADE_EN,//param57
    AU_SRS_THEATER_CC3D_TSHD_MIX_EN,//param58
    AU_SRS_THEATER_CC3D_TBHDX_EN,//param59
    AU_SRS_THEATER_CC3D_INPUT_GAIN,//param60
    AU_SRS_THEATER_CC3D_OUTPUT_GAIN,//param61
    AU_SRS_THEATER_CC3D_BYPASS_GAIN,//param62
    AU_SRS_THEATER_CC3D_APERTURE,//param63
    AU_SRS_THEATER_CC3D_GAINLIMIT,//param64
    AU_SRS_THEATER_CC3D_FF_DEPTH,//param65
    AU_SRS_THEATER_CC3D_NF_DEPTH,//param66

    AU_SRS_THEATER_CC3D_TSHD_SURR_MODE,//param67
    AU_SRS_THEATER_CC3D_TSHD_MIX_FADE_CTRL,//param68

    AU_SRS_THEATER_CC3D_TBHDX_INPUT_GAIN,//param69
    AU_SRS_THEATER_CC3D_TBHDX_BASSLEVEL,//param70
    AU_SRS_THEATER_CC3D_TBHDX_SPEAKERSIZE,//param71
    AU_SRS_THEATER_CC3D_TBHDX_MODE,//param72
    AU_SRS_THEATER_CC3D_TBHDX_DYNAMICS,//param73
    AU_SRS_THEATER_CC3D_TBHDX_HP_ORDER,//param74
    AU_SRS_THEATER_CC3D_TBHDX_CUSTOM_FILTER,
    AU_SRS_THEATER_CC3D_GEQ_EN,//param75
    AU_SRS_THEATER_CC3D_GEQ_INPUT_GAIN,
    AU_SRS_THEATER_CC3D_GEQ_BAND0_GAIN,
    AU_SRS_THEATER_CC3D_GEQ_BAND1_GAIN,
    AU_SRS_THEATER_CC3D_GEQ_BAND2_GAIN,
    AU_SRS_THEATER_CC3D_GEQ_BAND3_GAIN,
    AU_SRS_THEATER_CC3D_GEQ_BAND4_GAIN,
    AU_SRS_THEATER_CC3D_PROCESS_PATH,
    AU_SRS_THEATER_TSHD_BYPASS_GAIN,

    AU_SRS_R2_MAX=100,

    AU_SRS_PURESOUND_HL_EN,//param101
    AU_SRS_PURESOUND_HL_INPUT_GAIN,//param102
    AU_SRS_PURESOUND_HL_OUTPUT_GAIN,//param103
    AU_SRS_PURESOUND_HL_BYPASS_GAIN,//param104
    AU_SRS_PURESOUND_HL_LIMITERBOOST,//param105
    AU_SRS_PURESOUND_HL_HARDLIMIT,//param106
    AU_SRS_PURESOUND_HL_DELAYLEN,//param107

    AU_SRS_PURESOUND_AEQ_EN,//param108
    AU_SRS_PURESOUND_AEQ_INPUT_GAIN,//param109
    AU_SRS_PURESOUND_AEQ_OUTPUT_GAIN,//param110
    AU_SRS_PURESOUND_AEQ_BYPASS_GAIN,//param111
    AU_SRS_PURESOUND_FILTER_CONFIG,//param112

    AU_SRS_PURESOUND_HPF_EN,//param113
    AU_SRS_PURESOUND_HPF_FREQUENCY,//param114
    AU_SRS_PURESOUND_TBHD_EN,
    AU_SRS_PURESOUND_TBHD_TRUBASS_LEVEL,
    AU_SRS_PURESOUND_TBHD_SPEAKER_SIZE,
    AU_SRS_PURESOUND_TBHD_LEVEL_INDEPENDENT_EN,
    AU_SRS_PURESOUND_TBHD_COMPRESSOR_LEVEL,
    AU_SRS_PURESOUND_TBHD_MODE,
    AU_SRS_PURESOUND_TBHD_SPEAKER_AUDIO,
    AU_SRS_PURESOUND_TBHD_SPEAKER_ANALYSIS,

    AU_SRS_PURESOUND_INPUT_GAIN,
    AU_SRS_PURESOUND_OUTPUT_GAIN,

} AU_SRS_THEATERSOUND_TYPE;

typedef enum
{
    DOLBY_PL2VDS,
    DOLBY_PL2VDPK,
    BBE,
    SRS_TSXT,
    SRS_TSHD,
    SRS_THEATERSOUND,
    DTS_ULTRATV,
    AUDYSSEY,
    SUPER_VOICE,
    DBX,
    SRS_PURESND,
    DTS_STUDIOSOUND_3D,
    RESERVE4,
    RESERVE5,
    RESERVE6,
    ADV_NONE,
} ADVSND_TYPE;

typedef enum
{
    //SRS_TSXT
    SRS_TSXT_TRUBASS,
    SRS_TSXT_DC,

    //SRS_TSHD
    SRS_TSHD_TRUBASS,
    SRS_TSHD_DC,
    SRS_TSHD_DEFINITION,
    SRS_TSHD_SRS3D,

    //SRS_THEATERSOUND
    SRS_THEATERSOUND_TSHD,
    SRS_THEATERSOUND_TRUBASS,
    SRS_THEATERSOUND_DC,
    SRS_THEATERSOUND_DEFINITION,
    SRS_THEATERSOUND_TRUVOLUME,
    SRS_THEATERSOUND_HARDLIMITER,
    SRS_THEATERSOUND_HPF,
    SRS_THEATERSOUND_TRUEQ,
    SRS_THEATERSOUND_TRUVOLUME_NOISE_MNGR,

    //DTS_ULTRATV
    DTS_ULTRATV_EVO,
    DTS_ULTRATV_SYM,

    //AUDYSSEY
    AUDYSSEY_DYNAMICVOL,
    AUDYSSEY_DYNAMICEQ,
    AUDYSSEY_EQ,
    AUDYSSEY_ABX,

    SRS_THEATERSOUND_TSHD_SURR,
    SRS_THEATERSOUND_TSHD_LEVEL_INDPT,
    SRS_THEATERSOUND_CS,
    SRS_THEATERSOUND_TRUDIALOG,
    SRS_THEATERSOUND_TRUVOLUME_NORMALIZER,
    SRS_THEATERSOUND_TRUVOLUME_SMOOTH,
    SRS_THEATERSOUND_HPF_END,
    SRS_THEATERSOUND_TOTAL,

    SRS_PURESOUND_HL,
    SRS_PURESOUND_AEQ,
    SRS_PURESOUND_HPF,
    SRS_PURESOUND_TBHD,
    SRS_THEATERSOUND_CC3D_EN,
    SRS_THEATERSOUND_CC3D_DEPTH_PROCESS_EN,
    SRS_THEATERSOUND_CC3D_3D_SURR_BOOST_EN,
    SRS_THEATERSOUND_CC3D_FADE_EN,
    SRS_THEATERSOUND_CC3D_TSHD_MIX_EN,
    SRS_THEATERSOUND_CC3D_TBHDX_EN,
    SRS_THEATERSOUND_GEQ_EN,
    SRS_THEATERSOUND_3D_EN,
} ADVFUNC;

typedef enum
{
    //BBE
    BBE_MODE_SET,

    //DOLBY
    DOLBY_PL2VDPK_SMOD,
    DOLBY_PL2VDPK_WMOD,

    //SRS TSXT
    SRS_TSXT_SET_INPUT_GAIN,
    SRS_TSXT_SET_DC_GAIN,
    SRS_TSXT_SET_TRUBASS_GAIN,
    SRS_TSXT_SET_SPEAKERSIZE,
    SRS_TSXT_SET_INPUT_MODE,
    SRS_TSXT_SET_OUTPUT_GAIN,
    SRS_TSXT_RESERVE1,
    SRS_TSXT_RESERVE2,
    SRS_TSXT_RESERVE3,

    //SRS TSHD in SE-DSP
    SRS_TSHD_SET_INPUT_MODE,
    SRS_TSHD_SET_OUTPUT_MODE,
    SRS_TSHD_SET_SPEAKERSIZE,
    SRS_TSHD_SET_TRUBASS_CONTROL,
    SRS_TSHD_SET_DEFINITION_CONTROL,
    SRS_TSHD_SET_DC_CONTROL,
    SRS_TSHD_SET_SURROUND_LEVEL,
    SRS_TSHD_SET_INPUT_GAIN,
    SRS_TSHD_SET_WOWSPACE_CONTROL,
    SRS_TSHD_SET_WOWCENTER_CONTROL,
    SRS_TSHD_SET_WOWHDSRS3DMODE,
    SRS_TSHD_SET_LIMITERCONTROL,
    SRS_TSHD_SET_OUTPUT_GAIN,
    SRS_TSHD_RESERVE1,
    SRS_TSHD_RESERVE2,
    SRS_TSHD_RESERVE3,

    //SRS_THEATERSOUND
    SRS_THEATERSOUND_INPUT_GAIN,
    SRS_THEATERSOUND_DEFINITION_CONTROL,
    SRS_THEATERSOUND_DC_CONTROL,
    SRS_THEATERSOUND_TRUBASS_CONTROL,
    SRS_THEATERSOUND_SPEAKERSIZE,
    SRS_THEATERSOUND_HARDLIMITER_LEVEL,
    SRS_THEATERSOUND_HARDLIMITER_BOOST_GAIN,
    SRS_THEATERSOUND_HEADROOM_GAIN,
    SRS_THEATERSOUND_TRUVOLUME_MODE,
    SRS_THEATERSOUND_TRUVOLUME_REF_LEVEL,
    SRS_THEATERSOUND_TRUVOLUME_MAX_GAIN,
    SRS_THEATERSOUND_TRUVOLUME_NOISE_MNGR_THLD,
    SRS_THEATERSOUND_TRUVOLUME_CALIBRATE,
    SRS_THEATERSOUND_TRUVOLUME_INPUT_GAIN,
    SRS_THEATERSOUND_TRUVOLUME_OUTPUT_GAIN,
    SRS_THEATERSOUND_HPF_FC,
    SRS_THEATERSOUND_TSHD_INPUT_GAIN,
    SRS_THEATERSOUND_TSHD_OUTPUT_GAIN,
    SRS_THEATERSOUND_SURR_LEVEL_CONTROL,
    SRS_THEATERSOUND_TRUBASS_COMPRESSOR_CONTROL,
    SRS_THEATERSOUND_TRUBASS_PROCESS_MODE,
    SRS_THEATERSOUND_TRUBASS_SPEAKER_AUDIO,
    SRS_THEATERSOUND_TRUBASS_SPEAKER_ANALYSIS,
    SRS_THEATERSOUND_OUTPUT_GAIN,
    SRS_THEATERSOUND_BYPASS_GAIN,
    SRS_THEATERSOUND_INPUT_MODE,
    SRS_THEATERSOUND_TRUVOLUME_BYPASS_GAIN,
    SRS_THEATERSOUND_CS_INPUT_GAIN,

    //DTS_ULTRATV
    DTS_ULTRATV_EVO_MONOINPUT,
    DTS_ULTRATV_EVO_WIDENINGON,
    DTS_ULTRATV_EVO_ADD3DBON,
    DTS_ULTRATV_EVO_PCELEVEL,
    DTS_ULTRATV_EVO_VLFELEVEL,
    DTS_ULTRATV_RESERVE1,
    DTS_ULTRATV_RESERVE2,
    DTS_ULTRATV_RESERVE3,
    DTS_ULTRATV_RESERVE4,
    DTS_ULTRATV_RESERVE5,
    DTS_ULTRATV_RESERVE6,

    DTS_ULTRATV_SYM_DEFAULT,
    DTS_ULTRATV_SYM_MODE,
    DTS_ULTRATV_SYM_LEVEL,
    DTS_ULTRATV_SYM_RESET,
    DTS_ULTRATV_RESERVE7,
    DTS_ULTRATV_RESERVE8,
    DTS_ULTRATV_RESERVE9,

    //AUDYSSEY
    AUDYSSEY_DYNAMICVOL_COMPRESS_MODE,
    AUDYSSEY_DYNAMICVOL_GC,
    AUDYSSEY_DYNAMICVOL_VOLSETTING,
    AUDYSSEY_DYNAMICEQ_EQOFFSET,
    AUDYSSEY_ABX_GWET,
    AUDYSSEY_ABX_GDRY,
    AUDYSSEY_ABX_FILSET,
    AUDYSSEY_RESERVE1,
    AUDYSSEY_RESERVE2,
    AUDYSSEY_RESERVE3,
    AUDYSSEY_RESERVE4,
    AUDYSSEY_RESERVE5,
    AUDYSSEY_RESERVE6,

    //DBX
    DBX_MODE_SET,
    DBX_LOAD_PM,
    DBX_LOAD_DM,
    DBX_COPY_TotSonDM,
    DBX_COPY_TotSonPM,
    DBX_COPY_TotVolDM,
    DBX_COPY_TotVolPM,
    DBX_COPY_TotSurDM,
    DBX_COPY_TotSurPM,
    OTHERS_RESERVE9,
    OTHERS_RESERVE10,
    OTHERS_RESERVE11,
    OTHERS_RESERVE12,
    OTHERS_RESERVE13,
    OTHERS_RESERVE14,
    OTHERS_RESERVE15,
    OTHERS_RESERVE16,
    OTHERS_RESERVE17,
    OTHERS_RESERVE18,
    OTHERS_RESERVE19,
    OTHERS_RESERVE20,
    OTHERS_RESERVE21,
    OTHERS_RESERVE22,
    OTHERS_RESERVE23,
    OTHERS_RESERVE24,
    OTHERS_RESERVE25,
    OTHERS_RESERVE26,
    OTHERS_RESERVE27,
    OTHERS_RESERVE28,
    OTHERS_RESERVE29,
    OTHERS_RESERVE30,

    SRS_THEATERSOUND_CS_PROCESS_MODE,
    SRS_THEATERSOUND_CS_LR_OUTPUT_GAIN,
    SRS_THEATERSOUND_CS_LsRs_OUTPUT_GAIN,
    SRS_THEATERSOUND_CS_Center_OUTPUT_GAIN,
    SRS_THEATERSOUND_TRUDIALOG_INPUT_GAIN,
    SRS_THEATERSOUND_TRUDIALOG_OUTPUT_GAIN,
    SRS_THEATERSOUND_TRUDIALOG_BYPASS_GAIN,
    SRS_THEATERSOUND_TRUDIALOG_PROCESS_GAIN,
    SRS_THEATERSOUND_TRUDIALOG_CLARITY_GAIN,
    SRS_THEATERSOUND_TRUVOLUME_NORMALIZE_THRESH,
    SRS_THEATERSOUND_HPF_CUTOFF,
    SRS_THEATERSOUND_HPF_END_CUTOFF,


    //SRS PURESOUND
    SRS_PURESOUND_HL_INPUT_GAIN,
    SRS_PURESOUND_HL_OUTPUT_GAIN,
    SRS_PURESOUND_HL_BYPASS_GAIN,
    SRS_PURESOUND_HL_LIMITERBOOST,
    SRS_PURESOUND_HL_HARDLIMIT,
    SRS_PURESOUND_HL_DELAYLEN,
    SRS_PURESOUND_AEQ_INPUT_GAIN,
    SRS_PURESOUND_AEQ_OUTPUT_GAIN,
    SRS_PURESOUND_AEQ_BYPASS_GAIN,
    SRS_PURESOUND_FILTER_CONFIG,
    SRS_PURESOUND_HPF_FREQUENCY,
    SRS_PURESOUND_TBHD_TRUBASS_LEVEL,
    SRS_PURESOUND_TBHD_SPEAKER_SIZE,
    SRS_PURESOUND_TBHD_LEVEL_INDEPENDENT_EN,
    SRS_PURESOUND_TBHD_COMPRESSOR_LEVEL,
    SRS_PURESOUND_TBHD_MODE,
    SRS_PURESOUND_TBHD_SPEAKER_AUDIO,
    SRS_PURESOUND_TBHD_SPEAKER_ANALYSIS,
    SRS_PURESOUND_INPUT_GAIN,
    SRS_PURESOUND_OUTPUT_GAIN,

    //SRS_THEATERSOUND_3D
    SRS_THEATERSOUND_CC3D_INPUT_GAIN,
    SRS_THEATERSOUND_CC3D_OUTPUT_GAIN,
    SRS_THEATERSOUND_CC3D_BYPASS_GAIN,
    SRS_THEATERSOUND_CC3D_APERTURE,
    SRS_THEATERSOUND_CC3D_GAINLIMIT,
    SRS_THEATERSOUND_CC3D_FF_DEPTH,
    SRS_THEATERSOUND_CC3D_NF_DEPTH,

    SRS_THEATERSOUND_CC3D_TSHD_SURR_MODE,
    SRS_THEATERSOUND_CC3D_TSHD_MIX_FADE_CTRL,

    SRS_THEATERSOUND_CC3D_TBHDX_INPUT_GAIN,
    SRS_THEATERSOUND_CC3D_TBHDX_BASSLEVEL,
    SRS_THEATERSOUND_CC3D_TBHDX_SPEAKERSIZE,
    SRS_THEATERSOUND_CC3D_TBHDX_MODE,
    SRS_THEATERSOUND_CC3D_TBHDX_DYNAMICS,
    SRS_THEATERSOUND_CC3D_TBHDX_HP_ORDER,
    SRS_THEATERSOUND_CC3D_TBHDX_CUSTOM_FILTER,
    SRS_THEATERSOUND_GEQ_INPUT_GAIN,
    SRS_THEATERSOUND_GEQ_BAND0_GAIN,
    SRS_THEATERSOUND_GEQ_BAND1_GAIN,
    SRS_THEATERSOUND_GEQ_BAND2_GAIN,
    SRS_THEATERSOUND_GEQ_BAND3_GAIN,
    SRS_THEATERSOUND_GEQ_BAND4_GAIN,
    SRS_THEATERSOUND_CC3D_PROCESS_PATH,
    SRS_THEATERSOUND_TSHD_BYPASS_GAIN,

} ADVSND_PARAM;

typedef enum
{
    DSP_MEM_TYPE_PM,                    // DSP PM memory
    DSP_MEM_TYPE_DM                     // DSP DM memory
}AUDIO_DSP_MEMORY_TYPE;


//====== Certification Mode TYPE========
typedef enum
{
    AUDIO_DOLBY_DD_Cert,                ///<
    AUDIO_DOLBY_DDP_Cert,               ///<
    AUDIO_DOLBY_PULSE_Cert,             ///<
    AUDIO_DOLBY_DDCO_Cert,              ///<
    AUDIO_DOLBY_MS10_Cert,              ///<
    AUDIO_DOLBY_RESERVE1,               ///<
    AUDIO_DOLBY_RESERVE2,               ///<
    AUDIO_DOLBY_RESERVE3,               ///<
    AUDIO_DTS_DMP_Cert,                 ///<
    AUDIO_DTS_BC_Cert,                  ///<
    AUDIO_DTS_PremiumTV_Cert,           ///<
    AUDIO_DTS_SYMMETRY_Cert,            ///<
    AUDIO_DTS_ENVELO_Cert,              ///<
    AUDIO_DTS_RESERVE1,                 ///<
    AUDIO_DTS_RESERVE2,                 ///<
    AUDIO_DTS_RESERVE3,                 ///<
    AUDIO_SRS_XT_Cert,                  ///<
    AUDIO_SRS_RESERVE1,                 ///<
    AUDIO_SRS_RESERVE2,                 ///<
    AUDIO_SRS_RESERVE3,                 ///<
} Audio_CertMode;

typedef enum
{
    AUDIO_CERT_Enable,
    AUDIO_CERT_Disable
}Audio_CertEnable;

//====== VoIP Applications ========
typedef enum
{
    /* VoIP Application CallBack */
    AUDIO_VoIP_CONFIG_REGISTER_DEC_CB,
    AUDIO_VoIP_CONFIG_REGISTER_SE_CB,

    /* VoIP Application Audio In/Out */
    AUDIO_VoIP_CONFIG_ALSA_PLAYBACK,

    /* Voip Application setup pcm upload and config SRC */
    AUDIO_VOIP_CONFIG_PCM_UPLOAD,

}AUDIO_VoIP_CONFIG_TYPE;


//====== STAOS PIP START 2012/02/01 ========

typedef struct
{
    XPCM_TYPE audioType;
    MS_U16    sampleRate;
    MS_U16    blockSize;
    MS_U16    samplePerBlock;
    MS_U8     channels;
    MS_U8     bitsPerSample;

} Audio_XPCM_Param;

typedef struct
{
    #define  MAX_NUM_CODECS  5

    MS_U16 Channels[MAX_NUM_CODECS];
    MS_U16 Regions[MAX_NUM_CODECS];
    MS_U16 cplStart[MAX_NUM_CODECS];
    MS_U16 cplQbits[MAX_NUM_CODECS];
    MS_U16 FrameSize[MAX_NUM_CODECS];

    MS_U16 mNumCodecs;
    MS_U16 mSamples;
    MS_U16 mSampleRate;

} Audio_COOK_Param;

typedef struct
{
    MS_U32    u32Version;
    MS_U32    u32Channels;
    MS_U32    u32SampleRate;
    MS_U32    u32ByteRate;
    MS_U32    u32BlockAlign;
    MS_U32    u32Encopt;
    MS_U32    u32ParsingByApp;
    MS_U32    u32BitsPerSample;
    MS_U32    u32ChannelMask;
    MS_U32    u32DrcParamExist;
    MS_U32    u32DrcRmsAmpRef;
    MS_U32    u32DrcRmsAmpTarget;
    MS_U32    u32DrcPeakAmpRef;
    MS_U32    u32DrcPeakAmpTarget;
    MS_U32    u32MaxPacketSize;

} Audio_ASF_Param;

typedef struct
{
    MS_U32 U32WrtAddr;
    MS_U32 U32WrtBytes;

} Audio_MM_Data_Request;

typedef struct
{
    MS_U32  U32DecodeFrame;
    MS_U32  U32WrtAddr;
    MS_U32  U32WrtBytes;

} Audio_MM_PCM_Info;

typedef struct
{
    MS_U32  U32Name;
    MS_U32  U32IsHashkeySupported;

} Audio_Hashkey_Info;

/// Audio Decoder ID Information
typedef enum
{
    /// Audio Decoder ID invalid
    AU_DEC_INVALID                       = -1,
    /// Audio 1-Decoder ID
    AU_DEC_ID1                           =  0,
    /// Audio 2-Decoder ID
    AU_DEC_ID2                           =  1,
    /// Audio 3-Decoder ID
    AU_DEC_ID3                           =  2,
    AU_DEC_MAX                           =  3

} AUDIO_DEC_ID;

typedef enum
{
    AUDIO_DSP_ID_DEC = 0x00,
    AUDIO_DSP_ID_SND,
    AUDIO_DSP_ID_R2,

    AUDIO_DSP_ID_ALL = 0xFF
} AUDIO_DSP_ID;

typedef enum
{
    FILTER_TYPE_AUDIO_1 = 0,
    FILTER_TYPE_AUDIO_2,
    FILTER_TYPE_AUDIO_INVALID,

} AUDIO_FILTER_TYPE;

typedef enum
{
    Audio_ParamType_SoundMode = 0,
    Audio_ParamType_syncSTC,
    Audio_ParamType_PTS_info,
    Audio_ParamType_setAudioDecoder,
    Audio_ParamType_acMode,
    Audio_ParamType_MM_FFx2,
    Audio_ParamType_reqDataSize,
    Audio_ParamType_esBuf_informDataRdy,      // new
    Audio_ParamType_playControl,
    Audio_ParamType_mute,
    Audio_ParamType_predecode,                // for KTV
    Audio_ParamType_setWMADecParam,
    Audio_ParamType_setCOOKDecParam,
    Audio_ParamType_setXPCMDecParam,
    Audio_ParamType_UNI_PCM3_Input_Addr,
    Audio_ParamType_UNI_NEED_DECODE_FRMCNT,
    Audio_ParamType_UNI_ES_Wptr,
    Audio_ParamType_UNI_PCMOutCnt,
    Audio_ParamType_AllocDecoder,
    Audio_ParamType_FreeDecoder,
    Audio_ParamType_omx_spdif_mode,
    Audio_ParamType_omx_spdif_play,
    Audio_ParamType_omx_spdif_pcmLevel,

} Audio_ParamType;

typedef enum
{
    Audio_infoType_DecStatus = 0,
    Audio_infoType_SampleRate,
    Audio_infoType_SoundMode,
    Audio_infoType_capability,
    Audio_infoType_AudioSyncStatus,   // 1 : AV-Sync  0: Free-run
    Audio_infoType_bitRate,
    Audio_infoType_acmod,
    Audio_infoType_okFrmCnt,
    Audio_infoType_errFrmCnt,
    Audio_infoType_1ms_timeStamp,
    Audio_infoType_33bit_PTS          = 10,
    Audio_infoType_33bit_STCPTS_DIFF,
    Audio_infoType_esBuf_req,
    Audio_infoType_BufferSize,
    Audio_infoType_BufferAddr,
    Audio_infoType_esBuf_currLevel,
    Audio_infoType_pcmBuf_currLevel,
    Audio_infoType_get_audio_filter,
    Audio_infoType_audio_unsupported,
    Audio_infoType_getDecInfo1,
    Audio_infoType_UNI_PCM1_Info      = 20,
    Audio_infoType_UNI_PCM3_Level,
    Audio_infoType_UNI_ES_Level,
    Audio_infoType_UNI_ES_Base,
    Audio_infoType_UNI_ES_Size,
    Audio_infoType_UNI_PCM_Base,
    Audio_infoType_UNI_PCM_Size,
    Audio_infoType_Decoder_ID,
    Audio_infoType_AccumEsCnt,
    Audio_infoType_MadBaseAddr,
    Audio_infoType_hashkey,
    Audio_infoType_UNI_PCM3_Base,
    Audio_infoType_UNI_PCM3_Size,

} Audio_InfoType;

typedef MS_BOOL (*pFuncPtr_SetAudioParam2)(AUDIO_DEC_ID DecId, Audio_ParamType paramType, MS_U32 Param);
typedef MS_BOOL (*pFuncPtr_GetAudioInfo2)(AUDIO_DEC_ID DecId, Audio_InfoType paramType, void * pInfo);

//====== STAOS PIP END 2012/02/01 ========

typedef enum
{
    Audio_DumpInfo_Off          = 0x0,
    Audio_DumpInfo_Avsync       = 0x1,
    Audio_DumpInfo_Dec1         = 0x2,
    Audio_DumpInfo_IoInfo       = 0x4,
    Audio_DumpInfo_mmFileAVsync = 0x8,
    Audio_DumpInfo_All          = 0x15,
    Audio_DumpInfo_AutoTest     = 0x80,
}Audio_DumpInfo_Type;

typedef enum
{
    Audio_OMX_SPDIF_OFF,
    Audio_OMX_SPDIF_ON,
    Audio_OMX_SPDIF_STOP,
    Audio_OMX_SPDIF_PLAY,

} Audio_OMX_SPDIF_Param;

typedef enum
{
    AUDIO_USAGE_TYPE_NONE,
    AUDIO_USAGE_TYPE_DTV,
    AUDIO_USAGE_TYPE_ATV,
    AUDIO_USAGE_TYPE_HDMI,
    AUDIO_USAGE_TYPE_ADC,
    AUDIO_USAGE_TYPE_MM,
    AUDIO_USAGE_TYPE_SPDIF,
    AUDIO_USAGE_TYPE_KTV,
    AUDIO_USAGE_TYPE_GAME,

} AUDIO_USAGE_TYPE;

///<Audio output port source type
typedef enum
{
    E_CONNECT_MAIN,                   ///< output connect to main source
    E_CONNECT_SUB,                     ///< output connect to sub source
    E_CONNECT_SCART,                 ///< output connect to scart source
    E_CONNECT_DATA_CAPTURE,  ///< output connect to data capture source
    E_CONNECT_KTV,                     ///< output connect to KTV source
    E_CONNECT_NULL,                   ///< Disable output port
} AUDIO_OUTPORT_SOURCE_TYPE;

// TEE Capability
typedef enum
{
    Audio_TEE_None                            = 0x00,
    Audio_TEE_Setup,                       
    Audio_TEE_Set_DSP_Secure_Accessed,          
    Audio_TEE_Set_DSP_Normal_Accessed,          

    Audio_TEE_Setup_and_ALL_DSP_Secure_Accessed   = 0xFF     
} Audio_TEE_Capability;

//=======================================
/// Init structure for audio
typedef struct
{
    MS_U8      miu;               ///< MIU
    MS_U8      tv_system;        ///< TV system
    MS_U8      dtv_system;       ///< DTV system
    MS_U8      au_system_sel;   ///< Audio system type

    //sif threshold
    AUDIO_SIF_SET_STANDARD        standard_u8Type;   ///< SIF standard type
    AUDIO_SIF_THRESHOLD_TYPE      threshold_u8Type;  ///< SIF Threshold type
    MS_U16                        threshold_value;   ///< SIF Threshold value

} AUDIO_INIT_INFO, *PAUDIO_INIT_INFO;

//=======================================
/// structure for audio output setting
typedef struct
{
    AUDIO_OUTPUT_TYPE   SpeakerOut;  ///< Audio output port for Speaker
    AUDIO_OUTPUT_TYPE   HpOut;       ///< Audio output port for HP
    AUDIO_OUTPUT_TYPE   MonitorOut;  ///< Audio output port for Monitor out
    AUDIO_OUTPUT_TYPE   ScartOut;    ///< Audio output port for Scart out
    AUDIO_OUTPUT_TYPE   SpdifOut;    ///< Audio output port for S/PDIF out
    AUDIO_OUTPUT_TYPE   ArcOut;    ///< Audio output port for S/PDIF out
} AUDIO_OUT_INFO, *PAUDIO_OUT_INFO;

//=======================================
/// structure for audio DSP path setting
typedef struct
{
    AUDIO_PATH_TYPE   SpeakerOut;     ///< Audio DSP path for Speaker
    AUDIO_PATH_TYPE   HpOut;          ///< Audio DSP path for HP
    AUDIO_PATH_TYPE   MonitorOut;     ///< Audio DSP path for Monitor out
    AUDIO_PATH_TYPE   ScartOut;       ///< Audio DSP path for Scart out
    AUDIO_PATH_TYPE   SpdifOut;       ///< Audio DSP path for Spdif
} AUDIO_PATH_INFO, *PAUDIO_PATH_INFO;

//=======================================
/// structure for output port connection setting
typedef struct
{
    AUDIO_OUTPORT_SOURCE_TYPE   SpeakerOut;     ///<  for Speaker
    AUDIO_OUTPORT_SOURCE_TYPE   HpOut;          ///<  for HP
    AUDIO_OUTPORT_SOURCE_TYPE   MonitorOut;     ///<  for Monitor out
    AUDIO_OUTPORT_SOURCE_TYPE   ScartOut;       ///<  for Scart out
    AUDIO_OUTPORT_SOURCE_TYPE   SpdifOut;       ///<  for Spdif
    AUDIO_OUTPORT_SOURCE_TYPE   ArcOut;         ///<  for HDMI Arc
} OUTPUT_SOURCE_INFO, *POUTPUT_SOURCE_INFO;

//=======================================
/// structure for AES info in new MM mode
typedef struct
{
    MS_U32 aes_base_addr;		///<  base address of ES buffer
    MS_U32 aes_end_addr;		///<  end address of ES buffer
    MS_U32 aes_BufSize;			///<  ES buffer size
    MS_U32 aes_write_addr;		///<  write pointer
    MS_U32 aes_read_addr;		///<  read pointer
    MS_U32 aes_freeSpace;		///<  free space of ES buffer
    MS_U32 aes_level;			///<  level of ES buffer
    MS_U32 aes_ptsCnt;			///<  count of total received PTS
    MS_U64 aes_lastPTS;			///<  last received PTS
} AES_INFO;


typedef enum
{
    E_TSP_0,
    E_TSP_1,
    E_TSP_MAX,
} AUDIO_STC_SOURCE;


typedef struct
{
    MS_BOOL bStart;
    MS_BOOL bConnect;
    MS_BOOL bAVSyncOn;
    MS_BOOL bIsAD;
    AUDIO_OUTPORT_SOURCE_TYPE eGroup;
    AUDIO_DSP_ID eDSPId;
    AUDIO_SOURCE_INFO_TYPE eSourceType;
    En_DVB_decSystemType eAudFormat;
    AUDIO_STC_SOURCE eStcSource;
} AudioDecStatus_t;

#ifdef __cplusplus
}
#endif

#endif // _DRV_AUDIO_IF_H_
