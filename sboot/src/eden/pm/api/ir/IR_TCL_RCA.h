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

#ifndef IR_FORMAT_H
#define IR_FORMAT_H

//-------------------------------------------------------------------------------------------
// Customer IR Specification parameter define (Please modify them by IR SPEC)
//-------------------------------------------------------------------------------------------
#define IR_MODE_SEL                     IR_TYPE_SWDECODE_RCA_MODE
#define IR_CHANNEL_USE_AS_UPDOWN        0
#define IR_VOLUME_USE_AS_LEFTRIGHT      0
// IR Header code define
#define IR_HEADER_CODE0         0x00    // Custom 0
#define IR_HEADER_CODE1         0x0F    // Custom 1

// IR Timing define
#define IR_HEADER_CODE_TIME     4000    // us
#define IR_OFF_CODE_TIME        4000    // us
#define IR_OFF_CODE_RP_TIME     10800   // us
#define IR_LOGI_01H_TIME        500     // us
#define IR_LOGI_0_TIME          2500    // us
#define IR_LOGI_1_TIME          1500    // us
#define IR_TIMEOUT_CYC          140000  // us
#define IR_TOLERANCE_TIME       ((IR_LOGI_0_TIME-IR_LOGI_1_TIME)/2+20)

#define IR_HEADER_CODE_TIME_UB  20
#define IR_HEADER_CODE_TIME_LB  -20
#define IR_OFF_CODE_TIME_UB  20
#define IR_OFF_CODE_TIME_LB  -20
#define IR_OFF_CODE_RP_TIME_UB  20
#define IR_OFF_CODE_RP_TIME_LB  -20
#define IR_LOGI_01H_TIME_UB  35
#define IR_LOGI_01H_TIME_LB  -30
#define IR_LOGI_0_TIME_UB  20
#define IR_LOGI_0_TIME_LB  -20
#define IR_LOGI_1_TIME_UB  20
#define IR_LOGI_1_TIME_LB  -20


#define IR_FIFO_CTRL_VALUE                  0x2F


// IR Format define
#define IRKEY_DUMY                          0x00
#define IRDA_KEY_MAPPING_POWER              IRKEY_POWER

#define IR_LEADER_CODE_CHECKING_OPTION      0xBF


typedef enum _IrCommandType
{

    IRKEY_POWER             = 0xD5,
    IRKEY_MUTE              = 0xC0,

    IRKEY_NUM_0             = 0xCF,
    IRKEY_NUM_1             = 0xCE,
    IRKEY_NUM_2             = 0xCD,
    IRKEY_NUM_3             = 0xCC,
    IRKEY_NUM_4             = 0xCB,
    IRKEY_NUM_5             = 0xCA,
    IRKEY_NUM_6             = 0xC9,
    IRKEY_NUM_7             = 0xC8,
    IRKEY_NUM_8             = 0xC7,
    IRKEY_NUM_9             = 0xC6,
    IRKEY_TV                = 0xC5,

    IRKEY_INFO              = 0xC3,
    IRKEY_CHANNEL_RETURN    = 0xD8,
    IRKEY_INPUT_SOURCE      = 0x5C,
    IRKEY_MENU              = 0xF7,
    IRKEY_EXIT              = 0xF9,

    IRKEY_UP                = 0xA6,
    IRKEY_DOWN              = 0xA7,
    IRKEY_RIGHT             = 0xA8,
    IRKEY_LEFT              = 0xA9,
    IRKEY_SELECT            = 0x0B,


    IRKEY_VOLUME_PLUS       = 0xD0,
    IRKEY_VOLUME_MINUS      = 0xD1,

    IRKEY_CHANNEL_PLUS      = 0xD2,
    IRKEY_CHANNEL_MINUS     = 0xD3,

    IRKEY_ZOOM              = 0x6F,
    IRKEY_REVEAL            = 0xED,
    IRKEY_AUDIO             = 0xA5,
    IRKEY_FREEZE   	    = 0xF3,

    IRKEY_RED               = 0x07,
    IRKEY_GREEN             = 0x17,
    IRKEY_BLUE              = 0x27,
    IRKEY_YELLOW            = 0x1B,
    IRKEY_USBMENU           =0xFD,
//=====================================For RTC 198=========================
//======================================below no use========================
    IRKEY_TV_RADIO          	= 0x01,
    IRKEY_CHANNEL_LIST      	= 0x02,
    IRKEY_CHANNEL_FAV_LIST  	= 0x03,

    IRKEY_PAGE_UP           	= 0x04,//= IRKEY_DUMY+1,
    IRKEY_PAGE_DOWN         	= 0x05,//= IRKEY_DUMY+2,
    IRKEY_CLOCK             	= 0x06,//= IRKEY_DUMY+3,

    IRKEY_MTS               	= 0xFF,//0x07,//= IRKEY_DUMY+45,
    IRKEY_NINE_LATTICE      	= 0x08,//= IRKEY_DUMY+8,
    IRKEY_TTX               	= 0x09,//= IRKEY_DUMY+9,
    IRKEY_CC                	= 0x0a,//= IRKEY_DUMY+10,

    IRKEY_CRADRD            	= 0x53,//= IRKEY_DUMY+12,

    IRKEY_DASH              	= 0x0c,//= IRKEY_DUMY+13,
    IRKEY_SLEEP             	= 0x0d,//= 0xF8,
    IRKEY_EPG               	= 0x0e,//= 0xE5,
    IRKEY_PIP               	= 0x0f,//= IRKEY_DUMY+14,

    IRKEY_MIX               	= 0x10,//= IRKEY_DUMY+15,
    IRKEY_INDEX             	= 0x11,//= IRKEY_DUMY+16,
    IRKEY_HOLD              	= 0x12,//= IRKEY_DUMY+17,
    IRKEY_PREVIOUS          	= 0x13,//= 0x45,
    IRKEY_NEXT              	= 0x14,//= 0xAC,
    IRKEY_BACKWARD          	= 0x15,//= 0xE2,
    IRKEY_FORWARD           	= 0x16,//= 0xE3,

    IRKEY_PLAY              	= 0x9E,//= 0xEA,//TCL BD
    IRKEY_RECORD            	= 0x31,//= 0xE8,
    IRKEY_STOP              	= 0x32,//= 0xE0,
    IRKEY_PAUSE             	= 0x33,//= IRKEY_DUMY+18,

    IRKEY_SIZE              	= 0x34,//= 0x8A,
    IRKEY_SUBCODE           	= 0x35,//= IRKEY_DUMY+20,
    IRKEY_AV                	= 0x36,//= IRKEY_DUMY+21,
    IRKEY_HDMI              	= 0x37,//= IRKEY_DUMY+22,
    IRKEY_SCART             	= 0x38,//= IRKEY_DUMY+23,
    IRKEY_PC                	= 0x39,//= IRKEY_DUMY+24,
    IRKEY_DTV               	= 0x3a,//= IRKEY_DUMY+25,
    IRKEY_COMPONENT         	= 0x3b,//= IRKEY_DUMY+27,
    IRKEY_SV                	= 0x3c,//= IRKEY_DUMY+28,

    IRKEY_ANTENNA           	= 0x3d,//= IRKEY_DUMY+29,
    IRKEY_LOCK              	= 0x3e,//= IRKEY_DUMY+30,
    IRKEY_BACK              	= 0x3f,//= IRKEY_DUMY+31,
    IRKEY_RED2              	= 0x40,//= IRKEY_DUMY+32,
    IRKEY_GREEN2            	= 0x41,//= IRKEY_DUMY+33,
    IRKEY_SUBTITLE          	= 0x42,//= IRKEY_DUMY+34,
    IRKEY_UPDATE            	= 0x43,//= IRKEY_DUMY+35,
    IRKEY_TTX_MODE         	= 0x44,//= IRKEY_DUMY+36,
    IRKEY_ADJUST            	= 0x45,//= IRKEY_DUMY+37,
    IRKEY_KEY_DISABLE_KEYPAD	= 0x46,//= IRKEY_DUMY+38,
    IRKEY_P_CHECK      		= 0x47,//= IRKEY_DUMY+39,
    IRKEY_S_CHECK   		= 0x48,//= IRKEY_DUMY+40,
    IRKEY_PICTURE   		= 0x49,//= IRKEY_DUMY+42,
    IRKEY_TV_INPUT   		= 0x50,//= IRKEY_DUMY+43,
    IRKEY_SUBPAGE           	= 0x51,//= IRKEY_DUMY+44,
    IRKEY_HOME              	= 0x52,//= IRKEY_DUMY+46,
//==========================================================================

}IrCommandType;
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
// IR system parameter define for H/W setting (Please don't modify them)
//-------------------------------------------------------------------------------------------
#define IR_CKDIV_NUM                        ((XTAL_CLOCK_FREQ+500000)/1000000)
#define IR_CKDIV_NUM_BOOT                   XTAL_CLOCK_FREQ
#define IR_CLK_BOOT                         (XTAL_CLOCK_FREQ/1000000)
#define IR_CLK                              IR_CLK_BOOT

#define irGetMinCnt_BOOT(time, tolerance)   ((u32)(((double)time*((double)IR_CLK_BOOT)/(IR_CKDIV_NUM_BOOT+1))*((double)1-tolerance)))
#define irGetMaxCnt_BOOT(time, tolerance)   ((u32)(((double)time*((double)IR_CLK_BOOT)/(IR_CKDIV_NUM_BOOT+1))*((double)1+tolerance)))
#define irGetMinCnt(time, tolerance)        ((u32)(((double)time*((double)IR_CLK)/(IR_CKDIV_NUM+1))*((double)1-tolerance)))
#define irGetMaxCnt(time, tolerance)        ((u32)(((double)time*((double)IR_CLK)/(IR_CKDIV_NUM+1))*((double)1+tolerance)))

#define irGetCnt_BOOT(time)                 ((u32)((double)time*((double)IR_CLK_BOOT)/(IR_CKDIV_NUM_BOOT+1)))
#define irGetCnt(time)                      ((u32)((double)time*((double)IR_CLK)/(IR_CKDIV_NUM+1)))


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
//-------------------------------------------------------------------------------------------
//********************************
//
//  IR Wakeup keys for standby mode
//
//********************************
#define IR_WAKEUP_KEY0              IRKEY_POWER //configured by application
#define IR_WAKEUP_KEY1              IRKEY_POWER //configured by application
#define IR_WAKEUP_KEY2              IRKEY_POWER //configured by application
#define IR_WAKEUP_KEY3              IRKEY_POWER //configured by application

//********************************
//
//  Support 2nd NEC Full Decode
//
//********************************
// 2nd IR Header code define
#define IR_2ND_NEC_DECODE_EN        DISABLE
#define IR_HEADER_CODE_2ND0         0xFF    // 2nd Custom 0
#define IR_HEADER_CODE_2ND1         0xFF    // 2nd Custom 1

#endif

