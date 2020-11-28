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
#ifdef HW_RC5_RC6_DECODE
#define IR_MODE_SEL             IR_TYPE_HWDECODE_RC
#else
#define IR_MODE_SEL             IR_TYPE_SWDECODE_MODE
#endif

#define IR_CHANNEL_USE_AS_UPDOWN        0
#define IR_VOLUME_USE_AS_LEFTRIGHT      1
// IR Header code define

#define IR_HEADER_CODE0     0x00    // Custom 0  // address bit
#define IR_HEADER_CODE1     0x08    // Custom 1  // no use

// IR Timing define
#define IR_HEADER_CODE_TIME    9000ul // us
#define IR_OFF_CODE_TIME       4500ul // us
#define IR_OFF_CODE_RP_TIME    2500ul // us
#define IR_LOGI_01H_TIME        560ul // us
#define IR_LOGI_0_TIME         1120ul // us
#define IR_LOGI_1_TIME         2240ul // us

#define IR_TIMEOUT_CYC         140000ul // us

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

#define BIT_DELTA                   250
#define HALF_BIT_COUNT             806     // 844/1.048
#define ONE_BIT_COUNT               1611    // 1688/1.048

#define HALF_BIT_LB                 (HALF_BIT_COUNT-BIT_DELTA)
#define HALF_BIT_UB                 (HALF_BIT_COUNT+BIT_DELTA)
#define ONE_BIT_LB                  (ONE_BIT_COUNT-BIT_DELTA)
#define ONE_BIT_UB                  (ONE_BIT_COUNT+BIT_DELTA)
// IR Format define
#define IRKEY_DUMY              0xFF
#define IRDA_KEY_MAPPING_POWER  IRKEY_POWER
#define IR_LEADER_CODE_CHECKING_OPTION 0xBF

typedef enum _IrCommandType
{
    IRKEY_TV_ANTENNA        = 0xCF,
    IRKEY_TV_RADIO          = 0x1E,    //same as IRKEY_PAGE_UP
    IRKEY_CHANNEL_LIST      = 0x75,
    IRKEY_CHANNEL_FAV_LIST  = 0x76,
    IRKEY_CHANNEL_RETURN    = 0x22,
    IRKEY_CHANNEL_PLUS      = 0x20,
    IRKEY_CHANNEL_MINUS     = 0x21,
    IRKEY_AUDIO             = 0x24,
    IRKEY_VOLUME_PLUS       = 0x10,
    IRKEY_VOLUME_MINUS      = 0x11,

    IRKEY_UP                = 0x14,//0x1C,
    IRKEY_POWER             = 0x0C,
    IRKEY_EXIT              =0x0a,// 0x53,
    IRKEY_MENU              =0x30,// 0x52,
    IRKEY_DOWN              =0x13,// 0x1D,
    IRKEY_LEFT              = 0x15,//0x2C,
    IRKEY_SELECT            =0x35,// 0x57,
    IRKEY_RIGHT             =0x16,// 0x2B,

    IRKEY_NUM_0             = 0x00,
    IRKEY_NUM_1             = 0x01,
    IRKEY_NUM_2             = 0x02,
    IRKEY_NUM_3             = 0x03,
    IRKEY_NUM_4             = 0x04,
    IRKEY_NUM_5             = 0x05,
    IRKEY_NUM_6             = 0x06,
    IRKEY_NUM_7             = 0x07,
    IRKEY_NUM_8             = 0x08,
    IRKEY_NUM_9             = 0x09,
    IRKEY_MUTE              = 0x72,

    IRKEY_FREEZE            = 0x5D,
    IRKEY_PAGE_UP           = 0xA6,
    IRKEY_PAGE_DOWN         = 0xA7,
    IRKEY_CLOCK             = 0xA8,

    IRKEY_INFO              = 0x12,
    IRKEY_RED               = 0x3e,
    IRKEY_GREEN             = 0x43,
    IRKEY_YELLOW            = 0x32,
    IRKEY_BLUE              = 0x34,
    IRKEY_MTS               = 0x23,
    IRKEY_NINE_LATTICE      = IRKEY_DUMY,
    IRKEY_TTX               = 0x3C,
    IRKEY_CC                = 0xBF,
    IRKEY_INPUT_SOURCE      = 0x38,
    IRKEY_CRADRD            = 0XBE,
    IRKEY_PICTURE           = 0x1A,
    IRKEY_ZOOM              = 0x7E, //16:9
    IRKEY_AV                = 0xA9,
    IRKEY_HDMI              = 0xAA,
    IRKEY_SCART             = 0xAB,
    IRKEY_PC                = 0xAD,
    IRKEY_DTV               = 0xAC,
    IRKEY_TV                = 0x4B,    //TV<-->DTV
    IRKEY_COMPONENT         = 0xEB,
    IRKEY_SV                = 0XEC,

    IRKEY_DASH              = 0XC0, // no use
    IRKEY_BACKWARD          = 0XC1,  // no use
    IRKEY_FORWARD           = 0XC2, // no use
    IRKEY_PLAY              = 0XC3, // no use
    IRKEY_RECORD            = 0XC4, // no use
    IRKEY_STOP              = 0XC5, // no use
    IRKEY_PAUSE             = 0XC6, // no use
    IRKEY_MEMORY_RECALL     = 0XC7, // no use

    IRKEY_SLEEP             = 0x26,
    IRKEY_EPG               = 0x78,

    IRKEY_P_CHECK           = 0xAE,
    IRKEY_S_CHECK           = 0xAF,

    IRKEY_MIX               = 0x3D,
    IRKEY_INDEX             = 0x6F,
    IRKEY_HOLD              = 0xFE,
    IRKEY_PREVIOUS          = 0xB0,
    IRKEY_NEXT              = 0xB1,

    IRKEY_POWERONLY         = 0xB4,

    IRKEY_TTX_MODE          = 0x18,
    IRKEY_RED2              = 0xB6,
    IRKEY_GREEN2            = 0xB7,
    IRKEY_UPDATE            = 0x42,
    IRKEY_SUBTITLE          = 0x4A,
    IRKEY_TIME               = 0x1D,

    IRKEY_SIZE              = 0x45,
    IRKEY_REVEAL            = 0x44,
    IRKEY_RETURN            = 0x22,
    IRKEY_ADJUST            = 0xC8,
    IRKEY_TV_INPUT          = 0xC9,
    IRKEY_MEDIA_BROWSER     = 0x39,
    IRKEY_KEY_DISABLE_KEYPAD= IRKEY_DUMY-3,
    IRKEY_BACK              = IRKEY_DUMY-2,
    IRKEY_SUBPAGE           = IRKEY_DUMY-1,
    //vestel key
    IRKEY_SUBCODE=IRKEY_DUMY-5,
    IRKEY_PIP=IRKEY_DUMY-6,
}IrCommandType;
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

#endif

