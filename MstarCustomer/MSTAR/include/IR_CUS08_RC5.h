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
#define IR_INT_NP_EDGE_TRIG
#define IR_MODE_SEL             IR_TYPE_SWDECODE_RC5_MODE //IR_TYPE_SWDECODE_MODE   
// IR Header code define
#define IR_HEADER_CODE0         0x00    // Custom 0
#define IR_HEADER_CODE1         0xBF    // Custom 1

#define IR_FHEADER_CODE0         	0x00//0x80    // Custom 0
#define IR_FHEADER_CODE1         	0x1C//0x7F    // Custom 1

#define IR_PHEADER_CODE0         	0x00//0x80    // Custom 0//Third  IR PC
#define IR_PHEADER_CODE1         	0x0F//0x7F    // Custom 1

#define FCTORY_HEADER_RECEIVE       0x40
#define PCCOMMAND_HEADER_RECEIVE    0x80
// IR Timing define
#define IR_HEADER_CODE_TIME     9000    // us
#define IR_OFF_CODE_TIME        4500    // us
#define IR_OFF_CODE_RP_TIME     2500    // us
#define IR_LOGI_01H_TIME        560     // us
#define IR_LOGI_0_TIME          1120    // us
#define IR_LOGI_1_TIME          2240    // us
#define IR_TIMEOUT_CYC          140000  // us

#define IR_RC5_DATA_BITS                 26
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

#define IR_LEADER_CODE_CHECKING_OPTION 0xBF
#define ENABLE_IR_MSTAR_SOURCE_HOTKEY   0


typedef enum _IrCommandType
{
    IRKEY_TV_RADIO          = 0x0C,
    IRKEY_CHANNEL_LIST      = 0x10,
    IRKEY_CHANNEL_FAV_LIST  = 0x08,
    IRKEY_CHANNEL_RETURN    = 0x5C,
    IRKEY_CHANNEL_PLUS      = 0x20,
    IRKEY_CHANNEL_MINUS     = 0x19,

    IRKEY_AUDIO             = 0x44,
    IRKEY_VOLUME_PLUS       = 0x16,
    IRKEY_VOLUME_MINUS      = 0x15,

    IRKEY_UP                = 0x52,
    IRKEY_POWER             = 0x46,
    IRKEY_EXIT              = 0x1F,
    IRKEY_MENU              = 0x2E,
    IRKEY_DOWN              = 0x13,
    IRKEY_LEFT              = 0x06,
    IRKEY_SELECT            = 0x0F,
    IRKEY_RIGHT             = 0x1A,

    IRKEY_NUM_0             = 0x50,
    IRKEY_NUM_1             = 0x49,
    IRKEY_NUM_2             = 0x55,
    IRKEY_NUM_3             = 0x59,
    IRKEY_NUM_4             = 0x4D,
    IRKEY_NUM_5             = 0x51,
    IRKEY_NUM_6             = 0x5D,
    IRKEY_NUM_7             = 0x48,
    IRKEY_NUM_8             = 0x54,
    IRKEY_NUM_9             = 0x58,

    IRKEY_MUTE              = 0x5A,
    IRKEY_PAGE_UP           = 0x03,
    IRKEY_PAGE_DOWN         = 0x05,
    IRKEY_CLOCK             = 0x5F,

    IRKEY_INFO              = 0x14,
    IRKEY_RED               = 0x47,
    IRKEY_GREEN             = 0x4B,
    IRKEY_YELLOW            = 0x57,
    IRKEY_BLUE              = 0x5B,
    IRKEY_MTS               = 0x41,
    IRKEY_NINE_LATTICE      = IRKEY_DUMY,
    IRKEY_TTX               = 0x0A,
    IRKEY_CC                = 0x09,
    IRKEY_INPUT_SOURCE      = 0x04,
    IRKEY_CRADRD            = IRKEY_DUMY-1,
//    IRKEY_PICTURE           = 0x40,
    IRKEY_ZOOM              = 0x4C,
    IRKEY_DASH              = 0x4E,
    IRKEY_SLEEP             = 0x45,
    IRKEY_EPG               = 0x4A,
    IRKEY_PIP               = 0x40,

  	IRKEY_MIX               = 0x1C,
    IRKEY_INDEX             = 0x18,
    IRKEY_HOLD              = 0x00,
    IRKEY_PREVIOUS          = 0x0E,
    IRKEY_NEXT              = 0x12,
    IRKEY_BACKWARD          = 0x02,
    IRKEY_FORWARD           = 0x1E,
    IRKEY_PLAY              = 0x01,
    IRKEY_RECORD            = 0x0D,
    IRKEY_STOP              = 0x11,
    IRKEY_PAUSE             = 0x1D,

    IRKEY_SIZE              = 0x43,
    IRKEY_REVEAL            = 0x4F,
    IRKEY_SUBCODE           = 0x53,
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

#endif

