////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
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
/// @file  apiXC_ModeParse.h
/// @brief MIU header file
/// @author MStar Semiconductor Inc.
///
////////////////////////////////////////////////////////////////////////////////
#ifndef _API_XC_MODEPARSE_H_
#define _API_XC_MODEPARSE_H_
#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

//------------------------------
// Mode Detect & Search
//------------------------------
#define MD_FLAG_NULL            0x00

#define MD_FLAG_POR_HPVP        0x01
#define MD_FLAG_POR_HPVN        0x02
#define MD_FLAG_POR_HNVP        0x04
#define MD_FLAG_POR_HNVN        0x08
#define MD_FLAG_INTERLACE       0x10

#define MD_FLAG_EURO_HDTV_BIT   0x20

#define MD_FLAG_YPBPR_BIT       0x40
#define MD_FLAG_HDTV_BIT        0x80


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

/// The type of result after mode searching.
typedef enum
{
    XC_MODEPARSE_NOT_PARSED = 0,        ///< timing not stable or stable no sync, not parse yet
    XC_MODEPARSE_OUT_OF_RANGE,          ///< out of spec.
    XC_MODEPARSE_UNSUPPORT_MODE,        ///< can't find in mode tables
    XC_MODEPARSE_SUPPORT_MODE,          ///< support mode
} XC_MODEPARSE_RESULT;

typedef struct
{
    // mode parse result
    MS_U8  u8ModeIndex;                    ///< OUT: mode parse will return the mode index by this variable
    MS_U16 u16ResWidth;                    ///< OUT: indicate the resolution -> width
    MS_U16 u16ResHeight;                   ///< OUT: indicate the resolution -> height

    // src type
    INPUT_SOURCE_TYPE_t eSrcType;       ///< IN: input source type

    // Analog
    MS_U16 u16HFreqx10;                    ///< IN: HFreq x 10, unit KHz after / 10
    MS_U16 u16VFreqx10;                    ///< IN: VFreq x 10, unit Hz after / 10
    MS_U16 u16Vtotal;                      ///< IN: Vertical total
    MS_U8  u8SyncStatus;                   ///< IN: from XC driver, including H/V sync polarity, interlaced or progressive, mode parse will or XC_MD_USER_MODE_BIT if new mode found

    // Digital
    MS_WINDOW_TYPE sDVI_HDMI_DE_Info;   ///< IN: DVI/HDMI input DE information

    // EuroHDTV detected or not
    MS_DETECT_EURO_HDTV_STATUS_TYPE eEuroHDTVStatus;    ///< IN: timing monitor detect Euro/Aus HDTV status
} XC_MODEPARSE_INPUT_INFO;  ///< the neccesary input timing information for mode search

typedef enum
{
    RES_640X350,     // 00
    RES_640X400,     // 01
    RES_720X400,     // 02
    RES_640X480,     // 03
    RES_800X600,     // 04
    RES_832X624,     // 05
    RES_1024X768,    // 06
    RES_1280X1024,   // 07
    RES_1600X1200,   // 08
    RES_1152X864,    // 09
    RES_1152X870,    // 10
    RES_1280X768,    // 11
    RES_1280X960,    // 12
    RES_720X480,     // 13
    RES_1920X1080,   // 14
    RES_1280X720,    // 15
    RES_720X576,     // 16
    RES_1920X1200,   // 17
    RES_1400X1050,   // 18
    RES_1440X900,    // 19
    RES_1680X1050,   // 20
    RES_1280X800,    // 21
    RES_1600X1024,   // 22
    RES_1600X900,    // 23
    RES_1360X768,    // 24
    RES_848X480,     // 25
    RES_1920X1080P,  // 26
    RES_1366X768,    // 27
    RES_864X648,     // 28
    RES_1280X1470,   // 29
    RES_1920X2205,   // 30
    RES_720X240,     // 31
    RES_720x288,     // 32
    RES_1152X900,    // 33
    RES_856x480,     // 34
    RES_MAXIMUM
}EN_RESOLUTION_TYPE;

typedef struct
{
    EN_RESOLUTION_TYPE enResolutionIndex;   ///< resolution

    MS_U16 u16HorizontalFrequency;             ///< Horizontal frequency
    MS_U16 u16VerticalFrequency;               ///< Vertical frequency

    MS_U16 u16HorizontalStart;                 ///< Horizontal start
    MS_U16 u16VerticalStart;                   ///< Vertical start

    MS_U16 u16HorizontalTotal;                 ///< Horizontal Total
    MS_U16 u16VerticalTotal;                   ///< Vertical Total
    MS_U8 u8VTotalTolerance;                   ///< VTotal tolerance

    MS_U8 u8AdcPhase;                          ///< ADC phase

    MS_U8 u8StatusFlag; ///< flags
    // b0: VSync polarity(1/0 = positive/negative)
    // b1: HSync polarity(1/0 = positive/negative)
    // b2: Sync polarity care bit
    // b4: interlace mode
}MS_PCADC_MODETABLE_TYPE;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

MS_BOOL MApi_XC_ModeParse_Init(void);
// mode search

XC_MODEPARSE_RESULT MApi_XC_ModeParse_MatchMode(MS_PCADC_MODETABLE_TYPE* ModeDB, MS_U8 u16NumberOfItems , XC_MODEPARSE_INPUT_INFO *psInputInfo);
#ifdef __cplusplus
}
#endif

#endif /* _API_XC_MODEPARSE_H_ */
