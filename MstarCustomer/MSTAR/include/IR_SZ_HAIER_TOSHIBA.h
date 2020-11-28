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

#ifndef IR_FORMAT_H
#define IR_FORMAT_H

//*************************************************************************
// Customer IR Specification parameter define (Please modify them by IR SPEC)
//*************************************************************************
#define IR_MODE_SEL             IR_TYPE_SWDECODE_TOSHIBA_MODE
#define IR_LG_MAP               0
#define IR_CHANNEL_USE_AS_UPDOWN   1
#define IR_VOLUME_USE_AS_LEFTRIGHT      1
// IR Header code define

#define IR_HEADER_CODE0         0x18    // Custom 0
#define IR_HEADER_CODE1         0x18    // Custom 1
//--------------------------------------------------
// [Function] IR NEC 2nd customer code support
// [Support] Chip series after T8/T9 included can support 
// (CODE20!=0xFF) || (CODE21!=0xFF) ==> enable
// (CODE20==0xFF) && (CODE21==0xFF) ==> disable
// default set to disable
#define IR_HEADER_CODE20        0xFF    // NEC 2nd Custom 0 
#define IR_HEADER_CODE21        0xFF    // NEC 2nd Custom 1
#define IR_HEADER_CODE_UNI      0x1818

// IR Timing define
#define IR_HEADER_CODE_TIME     9000    // us
#define IR_OFF_CODE_TIME        3000    // us
#define IR_OFF_CODE_RP_TIME     4500    // us
#define IR_LOGI_01H_TIME        570     // us
#define IR_LOGI_0_TIME          1130    // us
#define IR_LOGI_1_TIME          2250    // us
#define IR_TIMEOUT_CYC          70000  // us

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

#define IR_KON_PWS3_HEADER_CNT_LB       8000
#define IR_KON_PWS3_HEADER_CNT_UB     10000
#define IR_KON_PWS3_LOGIC0_CNT_LB       1000
#define IR_KON_PWS3_LOGIC0_CNT_UB       1300
#define IR_KON_PWS3_LOGIC1_CNT_LB       2000
#define IR_KON_PWS3_LOGIC1_CNT_UB       2500
#define IR_KON_PWS3_STOP_CNT_LB       4000
#define IR_KON_PWS3_STOP_CNT_UB       3000
#define IR_KON_PWS3_REPEATE_TIMEOUT     150

// IR Format define
#define IRKEY_DUMY              0xFF
#define IRDA_KEY_MAPPING_POWER  IRKEY_POWER
#define IR_LEADER_CODE_CHECKING_OPTION 0xBF


#define IR_LEADER_CODE_CHECKING_OPTION 0xBF
typedef enum _IrCommandType
{
     IRKEY_TV_RADIO          = IRKEY_DUMY,
    IRKEY_CHANNEL_LIST      = 0x3E,
    IRKEY_CHANNEL_FAV_LIST  =0xBC,
    IRKEY_CHANNEL_RETURN    = 0x50,  //
    IRKEY_CHANNEL_PLUS      = 0x98,  //
    IRKEY_CHANNEL_MINUS     = 0x18,  //

    IRKEY_AUDIO             = 0x48,  // sound mode
    IRKEY_VOLUME_PLUS       = 0xD8,  //
    IRKEY_VOLUME_MINUS      = 0x58,  //
    IRKEY_UP                = 0x26,  //
    IRKEY_POWER             = 0xD0,  //
    IRKEY_EXIT              = 0xB8,  //
    IRKEY_MENU              = 0x38,  //
    IRKEY_DOWN              = 0x66,  //
    IRKEY_LEFT              = 0xA6,  //
    IRKEY_SELECT            = 0x16,  //
    IRKEY_RIGHT             = 0xE6,  //
    IRKEY_DNR                =0xD4,
    IRKEY_TIME              = IRKEY_DUMY-3,
    IRKEY_LIST              = IRKEY_DUMY-4,
    IRKEY_NUM_0             = 0x90,  //
    IRKEY_NUM_1             = 0x00,  //
    IRKEY_NUM_2             = 0x80,  //
    IRKEY_NUM_3             = 0x40,  //
    IRKEY_NUM_4             = 0xC0,  //
    IRKEY_NUM_5             = 0x20,  //
    IRKEY_NUM_6             = 0xA0,  //
    IRKEY_NUM_7             = 0x60,  //
    IRKEY_NUM_8             = 0xE0,  //
    IRKEY_NUM_9             = 0x10,  //

    IRKEY_MUTE              = 0x30,  //
    IRKEY_FREEZE            = 0xF0,
    IRKEY_PAGE_UP           = IRKEY_DUMY-5,  //
    IRKEY_PAGE_DOWN         = IRKEY_DUMY-6,  //
    IRKEY_CLOCK             = IRKEY_DUMY-48,
    IRKEY_TV_INPUT           = IRKEY_DUMY-8,
    IRKEY_INFO              = 0x04,  //

    IRKEY_RED               = 0x62,
    IRKEY_GREEN             =  0x42,
    IRKEY_YELLOW            =0x02,
    IRKEY_BLUE              =0xF8,
    IRKEY_MTS               =  0x7E,//
    IRKEY_NINE_LATTICE      = IRKEY_DUMY-9,
    IRKEY_TTX               = IRKEY_DUMY-10,
    IRKEY_CC                = 0xBE,  //
    IRKEY_INPUT_SOURCE      = 0xA8,  //
    IRKEY_CRADRD            = IRKEY_DUMY-11,
    IRKEY_PICTURE           = 0xB0,  // Picture Mode
    IRKEY_ZOOM              = 0xC8,  //
    IRKEY_DASH              = 0xD2, //
    IRKEY_SLEEP             = 0xE8,
    IRKEY_EPG               = 0xDA,  //IRKEY_DUMY-30

    IRKEY_MIX               = IRKEY_DUMY-14,
    IRKEY_INDEX             = IRKEY_DUMY-60,
    IRKEY_HOLD              = IRKEY_DUMY-16,
    IRKEY_PREVIOUS          = IRKEY_DUMY-46,
    IRKEY_NEXT              = IRKEY_DUMY-18,
    IRKEY_BACKWARD          = 0x56,
    IRKEY_FORWARD           = 0xD6,
    IRKEY_PLAY              =0x36,
    IRKEY_RECORD            = IRKEY_DUMY-19,
    IRKEY_STOP              = IRKEY_DUMY-20,
    IRKEY_PAUSE             = IRKEY_DUMY-21,

    IRKEY_SIZE              = IRKEY_DUMY-22,
    IRKEY_REVEAL            = IRKEY_DUMY-49,
    IRKEY_SUBCODE           =  IRKEY_DUMY-24,
    IRKEY_ANTENNA           = IRKEY_DUMY-25,
     IRKEY_LOCK                = 0x82,
     IRKEY_QMENU            =0xC6,
     IRKEY_REPEAT           =0x6C,
     IRKEY_MM_ZOOM       =0x4C,
  IRKEY_BACK                 = IRKEY_DUMY-27,
  IRKEY_RED2                  = IRKEY_DUMY-28,
  IRKEY_GREEN2              = IRKEY_DUMY-29,
  IRKEY_SUBTITLE            = IRKEY_DUMY-30,
  IRKEY_UPDATE              =IRKEY_DUMY-44,
  IRKEY_TTX_MODE         = IRKEY_DUMY-32,

  IRKEY_ADJUST               = IRKEY_DUMY-33,
  IRKEY_KEY_DISABLE_KEYPAD = IRKEY_DUMY-34,
   IRKEY_P_CHECK      = IRKEY_DUMY-35,
   IRKEY_S_CHECK   =   IRKEY_DUMY-36,


    // source switching hotkeys
    IRKEY_AV                 = IRKEY_DUMY-54,
    IRKEY_HDMI            = IRKEY_DUMY-58,
    IRKEY_USB              =IRKEY_DUMY-56,
    IRKEY_SCART         = IRKEY_DUMY-52,
    IRKEY_PC                = IRKEY_DUMY-38,
    IRKEY_TV                = IRKEY_DUMY-59,
    IRKEY_DTV              = IRKEY_DUMY-51,
    IRKEY_COMPONENT  = IRKEY_DUMY-40,
    IRKEY_SV                = IRKEY_DUMY-53,

    IRKEY_SUBPAGE   =   IRKEY_DUMY-42,

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
