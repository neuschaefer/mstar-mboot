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
////////////////////////////////////////////////////////////////////////////////

#ifndef IR_FORMAT_H
#define IR_FORMAT_H

//*************************************************************************
// Customer IR Specification parameter define (Please modify them by IR SPEC)
//*************************************************************************
#define IR_MODE_SEL                         IR_TYPE_SWDECODE_SHA_MODE
#define IR_CHANNEL_USE_AS_UPDOWN            0
#define IR_VOLUME_USE_AS_LEFTRIGHT          0

// IR Header code define
#define IR_HEADER_CODE0             0x80    // Custom 0     //0x04
#define IR_HEADER_CODE1             0x7F    // Custom 1     //0xFB

// IR Timing define
#define IR_HEADER_CODE_TIME         9000    // us
#define IR_OFF_CODE_TIME            4500    // us
#define IR_OFF_CODE_RP_TIME         2500    // us
#define IR_LOGI_01H_TIME            560     // us
#define IR_LOGI_0_TIME              1120    // us
#define IR_LOGI_1_TIME              2240    // us
#define IR_TIMEOUT_CYC              140000  // us

#define IR_HEADER_CODE_TIME_UB      20
#define IR_HEADER_CODE_TIME_LB      -20
#define IR_OFF_CODE_TIME_UB         20
#define IR_OFF_CODE_TIME_LB         -20
#define IR_OFF_CODE_RP_TIME_UB      20
#define IR_OFF_CODE_RP_TIME_LB      -20
#define IR_LOGI_01H_TIME_UB         35
#define IR_LOGI_01H_TIME_LB         -30
#define IR_LOGI_0_TIME_UB           20
#define IR_LOGI_0_TIME_LB           -20
#define IR_LOGI_1_TIME_UB           20
#define IR_LOGI_1_TIME_LB           -20


#define IR_FIFO_CTRL_VALUE                  0x2F
#define IR_CKDIV_NUM_VALUE                  0x04


// IR Format define
#define IRKEY_DUMY                          0xFF
#define IRDA_KEY_MAPPING_POWER              IRKEY_POWER

#define IR_LEADER_CODE_CHECKING_OPTION      0xBF


typedef enum _IrCommandType
{
            IRKEY_NUM_0           =0x00,//  = 0x0A,0x2141
            IRKEY_NUM_1           =0x01,//  = 0x01,0x2021
            IRKEY_NUM_2           =0x02,//  = 0x02,0x2041
            IRKEY_NUM_3           =0x03,//  = 0x03,0x2061
            IRKEY_NUM_4           =0x04,//  = 0x04,0x2081
            IRKEY_NUM_5           =0x05,//  = 0x05,0x20A1
            IRKEY_NUM_6           =0x06,//  = 0x06,0x20C1
            IRKEY_NUM_7           =0x07,//  = 0x07,0x20E1
            IRKEY_NUM_8           =0x08,//  = 0x08,0x2101
            IRKEY_NUM_9           =0x09,//  = 0x09,0x2121
            IRKEY_UP              =0x0A,//  = 0x57,0x2AE1
            IRKEY_POWER           =0x0B,//  = 0x16,0x22C1
            IRKEY_EXIT            =0x0C,//  = 0xF5,0x3EA1
            IRKEY_MENU            =0x0D,//  = 0xC6,0x38D1
            IRKEY_DOWN            =0x0E,//  = 0x20,0x2041
            IRKEY_LEFT            =0x0F,//       = 0xD7,0x3AE1
            IRKEY_RIGHT           =0x10,//       = 0xD8,0x3B01
            IRKEY_SELECT          =0x11,//       = 0x52,0x2A41
            IRKEY_RETURN          =0x12,//       = 0xE4,0x3C81

            // channel keys
            IRKEY_CHANNEL_LIST            = 0x5C,//0x13,//  = 0xA7,0x34F1    //GUIDE_KEY
            IRKEY_CHANNEL_FAV_LIST =0x14,//   = 0xA9,0x3531
            IRKEY_CHANNEL_PLUS     =0x15,//   = 0x11,0x2221
            IRKEY_CHANNEL_MINUS    =0x16,//   = 0x12,0x2241
            IRKEY_CHANNEL_RETURN   =0x17,//   = 0x27,0x24E1

            // color keys
            IRKEY_RED              =0x18,//   = 0x48,0x2901
            IRKEY_GREEN            =0x19,//  = 0x49,0x2921
            IRKEY_YELLOW           =0x1A,//  = 0x4A,0x2941
            IRKEY_BLUE             =0x1B,//   = 0x4B,0x2961

            // audio keys
            IRKEY_MUTE             =0x1C,//  = 0x17,0x22E1
            IRKEY_MTS              =0x1D,//   = 0x18,0x2301
            IRKEY_VOLUME_PLUS      =0x1E,//   = 0x14,0x2281
            IRKEY_VOLUME_MINUS     =0x1F,//  = 0x15,0x22A1

            // TTX keys
            IRKEY_TTX              =0x20,//  = 0x34,0x2681
            IRKEY_REVEAL           =0x21,//   = 0x38,0x2701
            IRKEY_SUBTITLE         =0x22,//   = 0x9F,0x33FE
            IRKEY_HOLD             =0x23,//   = 0x33,0x2661
            IRKEY_SUBPAGE          =0x24,//  = 0xCD,0x39BE
            IRKEY_SIZE             =0x25,//  = 0x37,0x26E1

            // input source keys
            IRKEY_INPUT_SOURCE     =0x26,//   = 0x13,0x2261
            IRKEY_DTV              =0x27,//   = 0xA0,0x3411
            IRKEY_TV               =0x28,//  = 0xF3, 0x3E71
            IRKEY_TV_RADIO                = 0x29,//  = 0xA4,0x3491

            // EPG keys
            IRKEY_INFO             =0x2A,//   = 0xA8,0x3511
            IRKEY_EPG              =0x2B,//  = 0xA3,0x3471

            // misc
            IRKEY_SLEEP            =0x2C,//  = 0x1A,0x2341
            IRKEY_DISPLAY          =0x2D,//  = 0x1B,0x2361

            // advanced keys
            IRKEY_DEMO            =0x2E,//   = 0xDD,3BB1
            IRKEY_OPC             =0x2F,//   = 0x8B,317E
            IRKEY_AVMODE                = 0x30,//  = 0xF8,3F01
            IRKEY_ZOOM            =0x31,//   = 0xC8,3911
            IRKEY_FREEZE          =0x32,//   = 0xD3,3A71
            IRKEY_PnP             =0x33,//   = 0xD0,3A11
            IRKEY_SELECT2         =0x34,//  = 0xCD,39B1

            IRKEY_AUDIO                    = 0x35,
            IRKEY_RED2                    = 0x36,
            IRKEY_GREEN2                = 0x37,
            IRKEY_UPDATE                = 0x38,
            IRKEY_TTX_MODE                = 0x39,
            IRKEY_MIX                    = 0x3A,

            IRKEY_INDEX                    = 0x3C,
            IRKEY_DASH                    = 0x3D,
            IRKEY_TV_INPUT                = 0x3E,
            IRKEY_BACKWARD            = 0x3F,
            IRKEY_FORWARD            = 0x40,
            IRKEY_PAGE_UP            = 0x41,
            IRKEY_PAGE_DOWN            = 0x42,
            IRKEY_PREVIOUS            = 0x43,
            IRKEY_NEXT            = 0x44,
    IRKEY_BACK                    = 0x45,
    IRKEY_CC                    = 0x46,
    IRKEY_ADJUST                = 0x47,
    IRKEY_KEY_DISABLE_KEYPAD    = 0x48,
    IRKEY_RECORD                = 0x49,
    IRKEY_STOP                    = 0x4A,
    IRKEY_PLAY                    = 0x4B,
    IRKEY_PAUSE                    = 0x4C,
    IRKEY_INPUT2                    = 0x4D,
    IRKEY_INPUT5                    = 0x4E,
    IRKEY_PC                    = 0x4F,
    IRKEY_COMPONENT                = 0x50,
    IRKEY_EXT1                    = 0x51,
    IRKEY_SV                    = 0x52,



    IRKEY_ADJUST2                 = 0x57,
    IRKEY_ROTATE                 = 0x5A,


    IRKEY_CHANNEL_ESG,

    IRKEY_MENU30                 = 0x69,
    IRKEY_POWER_OFF,
    IRKEY_POWER_ON,

    IRKEY_AUDIO_OUT_FIXED          = 0x74,
    IRKEY_AUDIO_OUT_VARIABLE          = 0x75,

    IRKEY_COMPDIR                 = 0x79,
    IRKEY_PCDIRECT                 = 0x7A,

    IRKEY_RADIO2                = 0x82,

    IRKEY_COMPOSITE                = 0x84,
    IRKEY_ANALOGPC                = 0x85,
    IRKEY_DOLBY                    = 0x86,
    IRKEY_DIGIPC                = 0x87,
    IRKEY_CENTERSP                = 0x88,
    IRKEY_MMEMORY                = 0x89,

    IRKEY_DCXO                      = 0x8C,
    IRKEY_OSCCOLOR                  = 0x8D,
    IRKEY_EXT1_SVIDEO              = 0x8E,
    IRKEY_EXT1_RGB                  = 0x8F,
    IRKEY_EXT2_RGB                  = 0x90,
    IRKEY_EXT3_SIDE                  = 0x91,
    IRKEY_INPUT7                  = 0x92,
    IRKEY_EXT3_S                  = 0x93,
    IRKEY_ADC_EXT3              = 0x94,
    IRKEY_INPUT4                      = 0x95,
    IRKEY_INPUT6                  = 0x96,

    IRKEY_INPUT3                  = 0x98,
    IRKEY_INPUT4_AVIN            = 0x99,
    IRKEY_INPUT4_EXT4_SD         = 0x9A,
    IRKEY_INPUT1                 = 0x9B,
    IRKEY_SHIMI1_SHIWA            = 0x9C,
    IRKEY_SHIMI2_SHIWA            = 0x9D,
    IRKEY_PCINVGA                = 0x9E,
    IRKEY_COMP_HD_ADJ              = 0x9F,

    IRKEY_BKGD_PRESETTINGS        = 0xA1,
    IRKEY_VIDEO_AGC                = 0xA2,
    IRKEY_COM1080                = 0xA3,
    IRKEY_3D_Y_C                = 0xA4,
    IRKEY_SVIDEO                = 0xA5,
    IRKEY_COMP15K_4LINE            = 0xA6,

    IRKEY_RGB_ADJ                = 0xA8,
    IRKEY_AVLINK2                = 0xA9,
    IRKEY_PNL_INCH_A            = 0xAA,
    IRKEY_PNL_INCH_B            = 0xAB,
    IRKEY_PNL_INCH_C            = 0xAC,
    IRKEY_PNL_INCH_D            = 0xAD,
    IRKEY_CECTEST                = 0xAE,
    IRKEY_5V_OFF                = 0xAF,
    IRKEY_5V_ON                    = 0xB0,
    IRKEY_DTV992                = 0xB1,
    IRKEY_DTV95                    = 0xB2,
    IRKEY_HDD_ON                = 0xB3,
    IRKEY_HDD_OFF                = 0xB4,
    IRKEY_PAUSE2                = 0xB5,
    IRKEY_AUDIODIG_ON_OFF        = 0xB6,
    IRKEY_DVI_AUDIO            = 0xB7,
    IRKEY_HDMI_AUDIO            = 0xB8,
    IRKEY_PP_HDMI_WR_ENABLE        = 0xB9,
    IRKEY_MAGILINK_OFF            = 0xBA,
    IRKEY_MAGILINK_ON            = 0xBB,
    IRKEY_USB_INSPECTION        = 0xBC,
    IRKEY_SEES_SRC                = 0xBD,
    IRKEY_PC_RGB_ADJ            = 0xBF,
    IRKEY_EXT3_SD_ADJ            = 0xC0,
    IRKEY_EXT3_HD_ADJ            = 0xC1,
    IRKEY_KEYPADTEST                = 0xC2,
    IRKEY_FAC_INPUT_SOURCE = 0xC3,

    //DIRECT ADJUSTMENT
    IRKEY_CONTRAST,
    IRKEY_TINT,
    IRKEY_COLOUR,
    IRKEY_BRIGHTNESS,
    IRKEY_SHARPNESS,
    IRKEY_BALANCE,
    IRKEY_LANGUAGE,
    IRKEY_TREBLE,
    IRKEY_BASS,
    IRKEY_BACKLIGHT_MIN,
    IRKEY_BACKLIGHT_STD,
    IRKEY_BACKLIGHT_MAX,

    //FACTORY
    IRKEY_KMODE_ON,
    IRKEY_KMODE_OFF,
    IRKEY_FACTORY,
    IRKEY_PUBLIC_MODE,
    IRKEY_TEST_PATTERN,
    IRKEY_FACTORY_INIT1,
    IRKEY_FACTORY_INIT2,
    IRKEY_FACTORY_INIT4,
    IRKEY_FACTORY_INIT6,
    IRKEY_LEDCHECK,
    IRKEY_CLONE,
    IRKEY_RF_AGC,
    IRKEY_PAL_ADJ,
    IRKEY_TUNER_ADJ,
    IRKEY_COMP_SD_ADJ,
    IRKEY_PC_ADJ,
    IRKEY_AUTO_GAIN_OFFSET,
    IRKEY_AUTO_GAIN_OFFSET2,
    IRKEY_AUTO_GAIN_OFFSET3,
    IRKEY_VCOM_ADJ,

    IRKEY_SEL_CVBS,
    IRKEY_SEL_SVIDEO,
    IRKEY_SEL_COMPONENT,
    IRKEY_SEL_AUTO,

    IRKEY_NULL                  = 0xFF,
}IrCommandType;

typedef struct _CUS21SH_IRKEY_TABLE
{
    U16 u16KeyCode;
    IrCommandType u8KeyIdx;
}CUS21SH_IRKEY_TABLE;


#ifdef MS_IR_C
code CUS21SH_IRKEY_TABLE IR_CUS21SH_RAWDATA_MAPPING_TABLE[]= //[205] =
{
    //NUMERICAL & CHANNEL FUNCTIONS
    {0x2141, IRKEY_NUM_0},
    {0x2021, IRKEY_NUM_1},
    {0x2041, IRKEY_NUM_2},
    {0x2061, IRKEY_NUM_3},
    {0x2081, IRKEY_NUM_4},
    {0x20A1, IRKEY_NUM_5},
    {0x20C1, IRKEY_NUM_6},
    {0x20E1, IRKEY_NUM_7},
    {0x2101, IRKEY_NUM_8},
    {0x2121, IRKEY_NUM_9},
    {0x3451, IRKEY_CHANNEL_LIST},
    {0x34F1, IRKEY_CHANNEL_ESG},
    {0x3531, IRKEY_CHANNEL_FAV_LIST},
    {0x2221, IRKEY_CHANNEL_PLUS},
    {0x2241, IRKEY_CHANNEL_MINUS},
    {0x24E1, IRKEY_CHANNEL_RETURN},
    {0x3471, IRKEY_EPG},
    {0x3511, IRKEY_INFO},       // Show Programme information (D-TV only)
    {0x2361, IRKEY_DISPLAY},    // This is the IRKEY_INFO code

    //MENU OPERATION
    {0x38D1, IRKEY_MENU},
    {0x2AE1, IRKEY_UP},
    {0x2401, IRKEY_DOWN},
    {0x3AE1, IRKEY_LEFT},
    {0x3B01, IRKEY_RIGHT},
    {0x2A41, IRKEY_SELECT},
    {0x3C81, IRKEY_RETURN},
    {0x3EA1, IRKEY_EXIT},

    //NORMAL FUNCTION
    {0x22C1, IRKEY_POWER},
    {0x2971, IRKEY_POWER_OFF},
    {0x2951, IRKEY_POWER_ON},
    {0x22E1, IRKEY_MUTE},
    {0x2281, IRKEY_VOLUME_PLUS},
    {0x22A1, IRKEY_VOLUME_MINUS},
    {0x2301, IRKEY_MTS},
    {0x2341, IRKEY_SLEEP},
    {0x3F01, IRKEY_AVMODE},
    {0x3911, IRKEY_ZOOM},
    {0x3A71, IRKEY_FREEZE},
    {0x317E, IRKEY_OPC},

    //INPUT SOURCE FUNCTION
    {0x2261, IRKEY_INPUT_SOURCE},
    {0x3411, IRKEY_DTV},
    {0x3E71, IRKEY_TV},
    {0x3491, IRKEY_TV_RADIO},
    {0x303E, IRKEY_PCDIRECT},
    {0x3DB1, IRKEY_INPUT1},
    {0x3DD1, IRKEY_INPUT2},
    {0x3DF1, IRKEY_INPUT3},
    {0x3E91, IRKEY_INPUT4},
    {0x3EB1, IRKEY_INPUT5},
    {0x3F11, IRKEY_INPUT6},
    {0x32B1, IRKEY_INPUT7},
    {0x295E, IRKEY_SEL_CVBS},
    {0x297E, IRKEY_SEL_SVIDEO},
    {0x299E, IRKEY_SEL_COMPONENT},
    {0x29BE, IRKEY_SEL_AUTO},
    {0x2A5E, IRKEY_DVI_AUDIO},
    {0x2A3E, IRKEY_HDMI_AUDIO},

    //APPLICATION KEY
    {0x2901, IRKEY_RED},
    {0x2921, IRKEY_GREEN},
    {0x2941, IRKEY_YELLOW},
    {0x2961, IRKEY_BLUE},

    //TTX
    {0x2681, IRKEY_TTX},
    {0x2701, IRKEY_REVEAL},
    {0x399E, IRKEY_REVEAL},
    {0x33FE, IRKEY_SUBTITLE},
    {0x2661, IRKEY_HOLD},
    {0x39BE, IRKEY_SUBPAGE},
    {0x26E1, IRKEY_SIZE},

    //FACTORY
    {0x2E71, IRKEY_FAC_INPUT_SOURCE},
    {0x2EE1, IRKEY_KMODE_ON},
    {0x3D9E, IRKEY_KMODE_OFF},
    {0x2801, IRKEY_FACTORY},
    {0x38FE, IRKEY_PUBLIC_MODE},
    {0x3FC1, IRKEY_FACTORY_INIT1},// factory init1 Hong Kong
    {0x3501, IRKEY_FACTORY_INIT2},// factory init2 ASIA
    {0x3D21, IRKEY_FACTORY_INIT4},// factory init4 OTHERS
    {0x3D61, IRKEY_FACTORY_INIT6},// factory init6 CHINA
    {0x3821, IRKEY_RF_AGC},
    {0x3841, IRKEY_PAL_ADJ},
    {0x3861, IRKEY_TUNER_ADJ},
    {0x3881, IRKEY_MENU30},
    {0x221E, IRKEY_COMP_SD_ADJ},
    {0x213E, IRKEY_COMP_HD_ADJ},
    {0x23DE, IRKEY_PC_ADJ},
    /*
    {0x213E, IRKEY_AUTO_GAIN_OFFSET},
    {0x221E, IRKEY_AUTO_GAIN_OFFSET2},
    {0x23DE, IRKEY_AUTO_GAIN_OFFSET3},
    */
    {0x287E, IRKEY_VCOM_ADJ},

    //FACTORY TEST
    {0x2D01, IRKEY_TEST_PATTERN},
    {0x2ABE, IRKEY_KEYPADTEST},
    {0x3C61, IRKEY_LEDCHECK},
    {0x2C1E, IRKEY_CECTEST},

    //FACTORY FUNCTION
    {0x30E1, IRKEY_PNL_INCH_A},
    {0x3101, IRKEY_PNL_INCH_B},
    {0x3121, IRKEY_PNL_INCH_C},
    {0x3141, IRKEY_PNL_INCH_D},
    {0x319E, IRKEY_ROTATE},
    {0x3B71, IRKEY_CLONE},

    //DIRECT ADJUSTMENT
    {0x2441, IRKEY_CONTRAST},
    {0x2481, IRKEY_TINT},
    {0x24C1, IRKEY_COLOUR},
    {0x2521, IRKEY_BRIGHTNESS},
    {0x2561, IRKEY_SHARPNESS},
    {0x29C1, IRKEY_BALANCE},
    {0x2BC1, IRKEY_LANGUAGE},
    {0x2C41, IRKEY_TREBLE},
    {0x2C81, IRKEY_BASS},
    {0x38B1, IRKEY_OPC},
    {0x311E, IRKEY_BACKLIGHT_MIN},
    {0x313E, IRKEY_BACKLIGHT_STD},
    {0x315E, IRKEY_BACKLIGHT_MAX},
    {0x333E, IRKEY_AUDIO_OUT_VARIABLE},
    {0x335E, IRKEY_AUDIO_OUT_FIXED},

    {0x0000, IRKEY_NULL},//unvalid keycode (keep in the last element)
};
#endif



//*************************************************************************

//*************************************************************************
// IR system parameter define for H/W setting (Please don't modify them)
//*************************************************************************
#define IR_CKDIV_NUM             ((BIU_CLOCK + 500000UL) / 1000000UL)
#define IR_CKDIV_NUM_BOOT        13

#define IR_CLK_BOOT             (BIU_CLOCK_BOOT / 1000000.0)
#define IR_CLK                  (BIU_CLOCK / 1000000.0)
#define irGetMinCnt_BOOT(time, tolerance) (((double)time*((double)IR_CLK_BOOT)/(IR_CKDIV_NUM_BOOT+1))*((double)1-tolerance))
#define irGetMaxCnt_BOOT(time, tolerance) (((double)time*((double)IR_CLK_BOOT)/(IR_CKDIV_NUM_BOOT+1))*((double)1+tolerance))
#define irGetMinCnt(time, tolerance) (((double)time*((double)IR_CLK)/(IR_CKDIV_NUM+1))*((double)1-tolerance))
#define irGetMaxCnt(time, tolerance) (((double)time*((double)IR_CLK)/(IR_CKDIV_NUM+1))*((double)1+tolerance))

#define irGetCnt_BOOT(time) (((double)time*((double)IR_CLK_BOOT)/(IR_CKDIV_NUM_BOOT+1))+0x300000UL)
#define irGetCnt(time) (((double)time*((double)IR_CLK)/(IR_CKDIV_NUM+1))+0x300000UL)

// 12Mhz
#define IR_RP_TIMEOUT_BOOT      irGetCnt_BOOT(IR_TIMEOUT_CYC)
#define IR_HDC_UPB_BOOT         irGetMaxCnt_BOOT(IR_HEADER_CODE_TIME, 0.2)
#define IR_HDC_LOB_BOOT         irGetMinCnt_BOOT(IR_HEADER_CODE_TIME, 0.2)
#define IR_OFC_UPB_BOOT         irGetMaxCnt_BOOT(IR_OFF_CODE_TIME, 0.2)
#define IR_OFC_LOB_BOOT         irGetMinCnt_BOOT(IR_OFF_CODE_TIME, 0.2)
#define IR_OFC_RP_UPB_BOOT      irGetMaxCnt_BOOT(IR_OFF_CODE_RP_TIME, 0.2)
#define IR_OFC_RP_LOB_BOOT      irGetMinCnt_BOOT(IR_OFF_CODE_RP_TIME, 0.2)
#define IR_LG01H_UPB_BOOT       irGetMaxCnt_BOOT(IR_LOGI_01H_TIME, 0.35)
#define IR_LG01H_LOB_BOOT       irGetMinCnt_BOOT(IR_LOGI_01H_TIME, 0.3)
#define IR_LG0_UPB_BOOT         irGetMaxCnt_BOOT(IR_LOGI_0_TIME, 0.2)
#define IR_LG0_LOB_BOOT         irGetMinCnt_BOOT(IR_LOGI_0_TIME, 0.2)
#define IR_LG1_UPB_BOOT         irGetMaxCnt_BOOT(IR_LOGI_1_TIME, 0.2)
#define IR_LG1_LOB_BOOT         irGetMinCnt_BOOT(IR_LOGI_1_TIME, 0.2)

// 90Mhz
#define IR_RP_TIMEOUT           irGetCnt(IR_TIMEOUT_CYC)
#define IR_HDC_UPB              irGetMaxCnt(IR_HEADER_CODE_TIME, 0.2)
#define IR_HDC_LOB              irGetMinCnt(IR_HEADER_CODE_TIME, 0.2)
#define IR_OFC_UPB              irGetMaxCnt(IR_OFF_CODE_TIME, 0.2)
#define IR_OFC_LOB              irGetMinCnt(IR_OFF_CODE_TIME, 0.2)
#define IR_OFC_RP_UPB           irGetMaxCnt(IR_OFF_CODE_RP_TIME, 0.2)
#define IR_OFC_RP_LOB           irGetMinCnt(IR_OFF_CODE_RP_TIME, 0.2)
#define IR_LG01H_UPB            irGetMaxCnt(IR_LOGI_01H_TIME, 0.35)
#define IR_LG01H_LOB            irGetMinCnt(IR_LOGI_01H_TIME, 0.3)
#define IR_LG0_UPB              irGetMaxCnt(IR_LOGI_0_TIME, 0.2)
#define IR_LG0_LOB              irGetMinCnt(IR_LOGI_0_TIME, 0.2)
#define IR_LG1_UPB              irGetMaxCnt(IR_LOGI_1_TIME, 0.2)
#define IR_LG1_LOB              irGetMinCnt(IR_LOGI_1_TIME, 0.2)

// Power off mode
#define PM_IR_TH_VAL            (PM_TH0_VAL & 0x0F)
// PM_IR_TH_GRID specify the time (in us) for each threshold bit.
// So PM_IR_TH_GRID = (1/12M) * (2^14) * 1000000 = (2^14) / 12
#define PM_IR_TH_GRID           (16384/IR_CLK_BOOT)
#define PM_IR_HEADER_CODE_TIME  (IR_HEADER_CODE_TIME-(0x0F-PM_IR_TH_VAL)*PM_IR_TH_GRID)
#define PM_IR_HDC_UPB_BOOT      irGetMaxCnt_BOOT(PM_IR_HEADER_CODE_TIME, 0.6)
#define PM_IR_HDC_LOB_BOOT      irGetMinCnt_BOOT(PM_IR_HEADER_CODE_TIME, 0.6)
//*************************************************************************

#endif   //#ifndef IR_FORMAT_H

