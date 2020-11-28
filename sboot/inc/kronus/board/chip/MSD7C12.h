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
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

// This file is generated by script, please do not edit it directly
#ifndef _MSD7C12_H_
#define _MSD7C12_H_

#define PAD_NC 9999
#define PAD_GND 0

#define BALL_D3 PAD_SPDIF_OUT
#define PAD_SPDIF_OUT 107
#define GPIO_PAD_107 GPIO106
#ifndef BALL_D3_IS_GPIO
#define BALL_D3_IS_GPIO 0
#endif
#ifndef PAD_SPDIF_OUT_IS_GPIO
#define PAD_SPDIF_OUT_IS_GPIO BALL_D3_IS_GPIO
#endif

#define BALL_D1 PAD_SM0_GPIO0
#define PAD_SM0_GPIO0 26
#define GPIO_PAD_26 GPIO25
#ifndef BALL_D1_IS_GPIO
#define BALL_D1_IS_GPIO 0
#endif
#ifndef PAD_SM0_GPIO0_IS_GPIO
#define PAD_SM0_GPIO0_IS_GPIO BALL_D1_IS_GPIO
#endif

#define BALL_D2 PAD_SM0_GPIO1
#define PAD_SM0_GPIO1 27
#define GPIO_PAD_27 GPIO26
#ifndef BALL_D2_IS_GPIO
#define BALL_D2_IS_GPIO 0
#endif
#ifndef PAD_SM0_GPIO1_IS_GPIO
#define PAD_SM0_GPIO1_IS_GPIO BALL_D2_IS_GPIO
#endif

#define BALL_E3 PAD_SM1_IO
#define PAD_SM1_IO 28
#define GPIO_PAD_28 GPIO27
#ifndef BALL_E3_IS_GPIO
#define BALL_E3_IS_GPIO 0
#endif
#ifndef PAD_SM1_IO_IS_GPIO
#define PAD_SM1_IO_IS_GPIO BALL_E3_IS_GPIO
#endif

#define BALL_E2 PAD_SM0_CD
#define PAD_SM0_CD 24
#define GPIO_PAD_24 GPIO23
#ifndef BALL_E2_IS_GPIO
#define BALL_E2_IS_GPIO 0
#endif
#ifndef PAD_SM0_CD_IS_GPIO
#define PAD_SM0_CD_IS_GPIO BALL_E2_IS_GPIO
#endif

#define BALL_F3 PAD_SM0_RST
#define PAD_SM0_RST 23
#define GPIO_PAD_23 GPIO22
#ifndef BALL_F3_IS_GPIO
#define BALL_F3_IS_GPIO 0
#endif
#ifndef PAD_SM0_RST_IS_GPIO
#define PAD_SM0_RST_IS_GPIO BALL_F3_IS_GPIO
#endif

#define BALL_F2 PAD_SM0_VCC
#define PAD_SM0_VCC 25
#define GPIO_PAD_25 GPIO24
#ifndef BALL_F2_IS_GPIO
#define BALL_F2_IS_GPIO 0
#endif
#ifndef PAD_SM0_VCC_IS_GPIO
#define PAD_SM0_VCC_IS_GPIO BALL_F2_IS_GPIO
#endif

#define BALL_F1 PAD_SM0_IO
#define PAD_SM0_IO 21
#define GPIO_PAD_21 GPIO20
#ifndef BALL_F1_IS_GPIO
#define BALL_F1_IS_GPIO 0
#endif
#ifndef PAD_SM0_IO_IS_GPIO
#define PAD_SM0_IO_IS_GPIO BALL_F1_IS_GPIO
#endif

#define BALL_G2 PAD_SM0_CLK
#define PAD_SM0_CLK 22
#define GPIO_PAD_22 GPIO21
#ifndef BALL_G2_IS_GPIO
#define BALL_G2_IS_GPIO 0
#endif
#ifndef PAD_SM0_CLK_IS_GPIO
#define PAD_SM0_CLK_IS_GPIO BALL_G2_IS_GPIO
#endif

#define BALL_G3 PAD_S_GPIO0
#define PAD_S_GPIO0 111
#define GPIO_PAD_111 GPIO110
#ifndef BALL_G3_IS_GPIO
#define BALL_G3_IS_GPIO 0
#endif
#ifndef PAD_S_GPIO0_IS_GPIO
#define PAD_S_GPIO0_IS_GPIO BALL_G3_IS_GPIO
#endif

#define BALL_W10 PAD_S_GPIO1
#define PAD_S_GPIO1 112
#define GPIO_PAD_112 GPIO111
#ifndef BALL_W10_IS_GPIO
#define BALL_W10_IS_GPIO 0
#endif
#ifndef PAD_S_GPIO1_IS_GPIO
#define PAD_S_GPIO1_IS_GPIO BALL_W10_IS_GPIO
#endif

#define BALL_Y10 PAD_S_GPIO2
#define PAD_S_GPIO2 113
#define GPIO_PAD_113 GPIO112
#ifndef BALL_Y10_IS_GPIO
#define BALL_Y10_IS_GPIO 0
#endif
#ifndef PAD_S_GPIO2_IS_GPIO
#define PAD_S_GPIO2_IS_GPIO BALL_Y10_IS_GPIO
#endif

#define BALL_AA12 PAD_CI_A14
#define PAD_CI_A14 54
#define GPIO_PAD_54 GPIO53
#ifndef BALL_AA12_IS_GPIO
#define BALL_AA12_IS_GPIO 0
#endif
#ifndef PAD_CI_A14_IS_GPIO
#define PAD_CI_A14_IS_GPIO BALL_AA12_IS_GPIO
#endif

#define BALL_W12 PAD_CI_A13
#define PAD_CI_A13 55
#define GPIO_PAD_55 GPIO54
#ifndef BALL_W12_IS_GPIO
#define BALL_W12_IS_GPIO 0
#endif
#ifndef PAD_CI_A13_IS_GPIO
#define PAD_CI_A13_IS_GPIO BALL_W12_IS_GPIO
#endif

#define BALL_AA13 PAD_CI_A12
#define PAD_CI_A12 56
#define GPIO_PAD_56 GPIO55
#ifndef BALL_AA13_IS_GPIO
#define BALL_AA13_IS_GPIO 0
#endif
#ifndef PAD_CI_A12_IS_GPIO
#define PAD_CI_A12_IS_GPIO BALL_AA13_IS_GPIO
#endif

#define BALL_Y13 PAD_CI_A11
#define PAD_CI_A11 57
#define GPIO_PAD_57 GPIO56
#ifndef BALL_Y13_IS_GPIO
#define BALL_Y13_IS_GPIO 0
#endif
#ifndef PAD_CI_A11_IS_GPIO
#define PAD_CI_A11_IS_GPIO BALL_Y13_IS_GPIO
#endif

#define BALL_W13 PAD_CI_A10
#define PAD_CI_A10 58
#define GPIO_PAD_58 GPIO57
#ifndef BALL_W13_IS_GPIO
#define BALL_W13_IS_GPIO 0
#endif
#ifndef PAD_CI_A10_IS_GPIO
#define PAD_CI_A10_IS_GPIO BALL_W13_IS_GPIO
#endif

#define BALL_Y14 PAD_CI_A9
#define PAD_CI_A9 59
#define GPIO_PAD_59 GPIO58
#ifndef BALL_Y14_IS_GPIO
#define BALL_Y14_IS_GPIO 0
#endif
#ifndef PAD_CI_A9_IS_GPIO
#define PAD_CI_A9_IS_GPIO BALL_Y14_IS_GPIO
#endif

#define BALL_W14 PAD_CI_A8
#define PAD_CI_A8 60
#define GPIO_PAD_60 GPIO59
#ifndef BALL_W14_IS_GPIO
#define BALL_W14_IS_GPIO 0
#endif
#ifndef PAD_CI_A8_IS_GPIO
#define PAD_CI_A8_IS_GPIO BALL_W14_IS_GPIO
#endif

#define BALL_Y15 PAD_CI_A7
#define PAD_CI_A7 61
#define GPIO_PAD_61 GPIO60
#ifndef BALL_Y15_IS_GPIO
#define BALL_Y15_IS_GPIO 0
#endif
#ifndef PAD_CI_A7_IS_GPIO
#define PAD_CI_A7_IS_GPIO BALL_Y15_IS_GPIO
#endif

#define BALL_AA15 PAD_CI_A6
#define PAD_CI_A6 62
#define GPIO_PAD_62 GPIO61
#ifndef BALL_AA15_IS_GPIO
#define BALL_AA15_IS_GPIO 0
#endif
#ifndef PAD_CI_A6_IS_GPIO
#define PAD_CI_A6_IS_GPIO BALL_AA15_IS_GPIO
#endif

#define BALL_Y21 PAD_CI_A5
#define PAD_CI_A5 63
#define GPIO_PAD_63 GPIO62
#ifndef BALL_Y21_IS_GPIO
#define BALL_Y21_IS_GPIO 0
#endif
#ifndef PAD_CI_A5_IS_GPIO
#define PAD_CI_A5_IS_GPIO BALL_Y21_IS_GPIO
#endif

#define BALL_AA19 PAD_CI_A2
#define PAD_CI_A2 66
#define GPIO_PAD_66 GPIO65
#ifndef BALL_AA19_IS_GPIO
#define BALL_AA19_IS_GPIO 0
#endif
#ifndef PAD_CI_A2_IS_GPIO
#define PAD_CI_A2_IS_GPIO BALL_AA19_IS_GPIO
#endif

#define BALL_W19 PAD_NF_CEZ
#define PAD_NF_CEZ 53
#define GPIO_PAD_53 GPIO52
#ifndef BALL_W19_IS_GPIO
#define BALL_W19_IS_GPIO 0
#endif
#ifndef PAD_NF_CEZ_IS_GPIO
#define PAD_NF_CEZ_IS_GPIO BALL_W19_IS_GPIO
#endif

#define BALL_W18 PAD_CI_A3
#define PAD_CI_A3 65
#define GPIO_PAD_65 GPIO64
#ifndef BALL_W18_IS_GPIO
#define BALL_W18_IS_GPIO 0
#endif
#ifndef PAD_CI_A3_IS_GPIO
#define PAD_CI_A3_IS_GPIO BALL_W18_IS_GPIO
#endif

#define BALL_Y19 PAD_CI_A0
#define PAD_CI_A0 68
#define GPIO_PAD_68 GPIO67
#ifndef BALL_Y19_IS_GPIO
#define BALL_Y19_IS_GPIO 0
#endif
#ifndef PAD_CI_A0_IS_GPIO
#define PAD_CI_A0_IS_GPIO BALL_Y19_IS_GPIO
#endif

#define BALL_Y20 PAD_CI_A1
#define PAD_CI_A1 67
#define GPIO_PAD_67 GPIO66
#ifndef BALL_Y20_IS_GPIO
#define BALL_Y20_IS_GPIO 0
#endif
#ifndef PAD_CI_A1_IS_GPIO
#define PAD_CI_A1_IS_GPIO BALL_Y20_IS_GPIO
#endif

#define BALL_AA20 PAD_CI_A4
#define PAD_CI_A4 64
#define GPIO_PAD_64 GPIO63
#ifndef BALL_AA20_IS_GPIO
#define BALL_AA20_IS_GPIO 0
#endif
#ifndef PAD_CI_A4_IS_GPIO
#define PAD_CI_A4_IS_GPIO BALL_AA20_IS_GPIO
#endif

#define BALL_AA18 PAD_CI_D0
#define PAD_CI_D0 76
#define GPIO_PAD_76 GPIO75
#ifndef BALL_AA18_IS_GPIO
#define BALL_AA18_IS_GPIO 0
#endif
#ifndef PAD_CI_D0_IS_GPIO
#define PAD_CI_D0_IS_GPIO BALL_AA18_IS_GPIO
#endif

#define BALL_Y18 PAD_CI_D1
#define PAD_CI_D1 75
#define GPIO_PAD_75 GPIO74
#ifndef BALL_Y18_IS_GPIO
#define BALL_Y18_IS_GPIO 0
#endif
#ifndef PAD_CI_D1_IS_GPIO
#define PAD_CI_D1_IS_GPIO BALL_Y18_IS_GPIO
#endif

#define BALL_W17 PAD_CI_D2
#define PAD_CI_D2 74
#define GPIO_PAD_74 GPIO73
#ifndef BALL_W17_IS_GPIO
#define BALL_W17_IS_GPIO 0
#endif
#ifndef PAD_CI_D2_IS_GPIO
#define PAD_CI_D2_IS_GPIO BALL_W17_IS_GPIO
#endif

#define BALL_Y17 PAD_CI_D3
#define PAD_CI_D3 73
#define GPIO_PAD_73 GPIO72
#ifndef BALL_Y17_IS_GPIO
#define BALL_Y17_IS_GPIO 0
#endif
#ifndef PAD_CI_D3_IS_GPIO
#define PAD_CI_D3_IS_GPIO BALL_Y17_IS_GPIO
#endif

#define BALL_W16 PAD_CI_D4
#define PAD_CI_D4 72
#define GPIO_PAD_72 GPIO71
#ifndef BALL_W16_IS_GPIO
#define BALL_W16_IS_GPIO 0
#endif
#ifndef PAD_CI_D4_IS_GPIO
#define PAD_CI_D4_IS_GPIO BALL_W16_IS_GPIO
#endif

#define BALL_Y16 PAD_CI_D5
#define PAD_CI_D5 71
#define GPIO_PAD_71 GPIO70
#ifndef BALL_Y16_IS_GPIO
#define BALL_Y16_IS_GPIO 0
#endif
#ifndef PAD_CI_D5_IS_GPIO
#define PAD_CI_D5_IS_GPIO BALL_Y16_IS_GPIO
#endif

#define BALL_AA16 PAD_CI_D6
#define PAD_CI_D6 70
#define GPIO_PAD_70 GPIO69
#ifndef BALL_AA16_IS_GPIO
#define BALL_AA16_IS_GPIO 0
#endif
#ifndef PAD_CI_D6_IS_GPIO
#define PAD_CI_D6_IS_GPIO BALL_AA16_IS_GPIO
#endif

#define BALL_W15 PAD_CI_D7
#define PAD_CI_D7 69
#define GPIO_PAD_69 GPIO68
#ifndef BALL_W15_IS_GPIO
#define BALL_W15_IS_GPIO 0
#endif
#ifndef PAD_CI_D7_IS_GPIO
#define PAD_CI_D7_IS_GPIO BALL_W15_IS_GPIO
#endif

#define BALL_V17 PAD_CI_IORDZ
#define PAD_CI_IORDZ 77
#define GPIO_PAD_77 GPIO76
#ifndef BALL_V17_IS_GPIO
#define BALL_V17_IS_GPIO 0
#endif
#ifndef PAD_CI_IORDZ_IS_GPIO
#define PAD_CI_IORDZ_IS_GPIO BALL_V17_IS_GPIO
#endif

#define BALL_V18 PAD_CI_IOWRZ
#define PAD_CI_IOWRZ 78
#define GPIO_PAD_78 GPIO77
#ifndef BALL_V18_IS_GPIO
#define BALL_V18_IS_GPIO 0
#endif
#ifndef PAD_CI_IOWRZ_IS_GPIO
#define PAD_CI_IOWRZ_IS_GPIO BALL_V18_IS_GPIO
#endif

#define BALL_U18 PAD_CI_OEZ
#define PAD_CI_OEZ 79
#define GPIO_PAD_79 GPIO78
#ifndef BALL_U18_IS_GPIO
#define BALL_U18_IS_GPIO 0
#endif
#ifndef PAD_CI_OEZ_IS_GPIO
#define PAD_CI_OEZ_IS_GPIO BALL_U18_IS_GPIO
#endif

#define BALL_W20 PAD_CI_WEZ
#define PAD_CI_WEZ 80
#define GPIO_PAD_80 GPIO79
#ifndef BALL_W20_IS_GPIO
#define BALL_W20_IS_GPIO 0
#endif
#ifndef PAD_CI_WEZ_IS_GPIO
#define PAD_CI_WEZ_IS_GPIO BALL_W20_IS_GPIO
#endif

#define BALL_V19 PAD_CI_REGZ
#define PAD_CI_REGZ 81
#define GPIO_PAD_81 GPIO80
#ifndef BALL_V19_IS_GPIO
#define BALL_V19_IS_GPIO 0
#endif
#ifndef PAD_CI_REGZ_IS_GPIO
#define PAD_CI_REGZ_IS_GPIO BALL_V19_IS_GPIO
#endif

#define BALL_V16 PAD_CI_CEZ
#define PAD_CI_CEZ 82
#define GPIO_PAD_82 GPIO81
#ifndef BALL_V16_IS_GPIO
#define BALL_V16_IS_GPIO 0
#endif
#ifndef PAD_CI_CEZ_IS_GPIO
#define PAD_CI_CEZ_IS_GPIO BALL_V16_IS_GPIO
#endif

#define BALL_W21 PAD_CI_IRQAZ
#define PAD_CI_IRQAZ 83
#define GPIO_PAD_83 GPIO82
#ifndef BALL_W21_IS_GPIO
#define BALL_W21_IS_GPIO 0
#endif
#ifndef PAD_CI_IRQAZ_IS_GPIO
#define PAD_CI_IRQAZ_IS_GPIO BALL_W21_IS_GPIO
#endif

#define BALL_V21 PAD_CI_WAITZ
#define PAD_CI_WAITZ 84
#define GPIO_PAD_84 GPIO83
#ifndef BALL_V21_IS_GPIO
#define BALL_V21_IS_GPIO 0
#endif
#ifndef PAD_CI_WAITZ_IS_GPIO
#define PAD_CI_WAITZ_IS_GPIO BALL_V21_IS_GPIO
#endif

#define BALL_V20 PAD_CI_RST
#define PAD_CI_RST 85
#define GPIO_PAD_85 GPIO84
#ifndef BALL_V20_IS_GPIO
#define BALL_V20_IS_GPIO 0
#endif
#ifndef PAD_CI_RST_IS_GPIO
#define PAD_CI_RST_IS_GPIO BALL_V20_IS_GPIO
#endif

#define BALL_T18 PAD_CI_CDZ
#define PAD_CI_CDZ 86
#define GPIO_PAD_86 GPIO85
#ifndef BALL_T18_IS_GPIO
#define BALL_T18_IS_GPIO 0
#endif
#ifndef PAD_CI_CDZ_IS_GPIO
#define PAD_CI_CDZ_IS_GPIO BALL_T18_IS_GPIO
#endif

#define BALL_U20 PAD_TS1_CLK
#define PAD_TS1_CLK 42
#define GPIO_PAD_42 GPIO41
#ifndef BALL_U20_IS_GPIO
#define BALL_U20_IS_GPIO 0
#endif
#ifndef PAD_TS1_CLK_IS_GPIO
#define PAD_TS1_CLK_IS_GPIO BALL_U20_IS_GPIO
#endif

#define BALL_U19 PAD_TS1_D7
#define PAD_TS1_D7 45
#define GPIO_PAD_45 GPIO44
#ifndef BALL_U19_IS_GPIO
#define BALL_U19_IS_GPIO 0
#endif
#ifndef PAD_TS1_D7_IS_GPIO
#define PAD_TS1_D7_IS_GPIO BALL_U19_IS_GPIO
#endif

#define BALL_T20 PAD_TS1_D6
#define PAD_TS1_D6 46
#define GPIO_PAD_46 GPIO45
#ifndef BALL_T20_IS_GPIO
#define BALL_T20_IS_GPIO 0
#endif
#ifndef PAD_TS1_D6_IS_GPIO
#define PAD_TS1_D6_IS_GPIO BALL_T20_IS_GPIO
#endif

#define BALL_T21 PAD_TS1_D5
#define PAD_TS1_D5 47
#define GPIO_PAD_47 GPIO46
#ifndef BALL_T21_IS_GPIO
#define BALL_T21_IS_GPIO 0
#endif
#ifndef PAD_TS1_D5_IS_GPIO
#define PAD_TS1_D5_IS_GPIO BALL_T21_IS_GPIO
#endif

#define BALL_T19 PAD_TS1_D4
#define PAD_TS1_D4 48
#define GPIO_PAD_48 GPIO47
#ifndef BALL_T19_IS_GPIO
#define BALL_T19_IS_GPIO 0
#endif
#ifndef PAD_TS1_D4_IS_GPIO
#define PAD_TS1_D4_IS_GPIO BALL_T19_IS_GPIO
#endif

#define BALL_R21 PAD_TS1_D3
#define PAD_TS1_D3 49
#define GPIO_PAD_49 GPIO48
#ifndef BALL_R21_IS_GPIO
#define BALL_R21_IS_GPIO 0
#endif
#ifndef PAD_TS1_D3_IS_GPIO
#define PAD_TS1_D3_IS_GPIO BALL_R21_IS_GPIO
#endif

#define BALL_R20 PAD_TS1_D2
#define PAD_TS1_D2 50
#define GPIO_PAD_50 GPIO49
#ifndef BALL_R20_IS_GPIO
#define BALL_R20_IS_GPIO 0
#endif
#ifndef PAD_TS1_D2_IS_GPIO
#define PAD_TS1_D2_IS_GPIO BALL_R20_IS_GPIO
#endif

#define BALL_R19 PAD_TS1_D1
#define PAD_TS1_D1 51
#define GPIO_PAD_51 GPIO50
#ifndef BALL_R19_IS_GPIO
#define BALL_R19_IS_GPIO 0
#endif
#ifndef PAD_TS1_D1_IS_GPIO
#define PAD_TS1_D1_IS_GPIO BALL_R19_IS_GPIO
#endif

#define BALL_P20 PAD_TS1_D0
#define PAD_TS1_D0 52
#define GPIO_PAD_52 GPIO51
#ifndef BALL_P20_IS_GPIO
#define BALL_P20_IS_GPIO 0
#endif
#ifndef PAD_TS1_D0_IS_GPIO
#define PAD_TS1_D0_IS_GPIO BALL_P20_IS_GPIO
#endif

#define BALL_P19 PAD_TS1_VLD
#define PAD_TS1_VLD 44
#define GPIO_PAD_44 GPIO43
#ifndef BALL_P19_IS_GPIO
#define BALL_P19_IS_GPIO 0
#endif
#ifndef PAD_TS1_VLD_IS_GPIO
#define PAD_TS1_VLD_IS_GPIO BALL_P19_IS_GPIO
#endif

#define BALL_N20 PAD_TS1_SYNC
#define PAD_TS1_SYNC 43
#define GPIO_PAD_43 GPIO42
#ifndef BALL_N20_IS_GPIO
#define BALL_N20_IS_GPIO 0
#endif
#ifndef PAD_TS1_SYNC_IS_GPIO
#define PAD_TS1_SYNC_IS_GPIO BALL_N20_IS_GPIO
#endif

#define BALL_N19 PAD_TS0_CLK
#define PAD_TS0_CLK 31
#define GPIO_PAD_31 GPIO30
#ifndef BALL_N19_IS_GPIO
#define BALL_N19_IS_GPIO 0
#endif
#ifndef PAD_TS0_CLK_IS_GPIO
#define PAD_TS0_CLK_IS_GPIO BALL_N19_IS_GPIO
#endif

#define BALL_M21 PAD_TS0_D7
#define PAD_TS0_D7 34
#define GPIO_PAD_34 GPIO33
#ifndef BALL_M21_IS_GPIO
#define BALL_M21_IS_GPIO 0
#endif
#ifndef PAD_TS0_D7_IS_GPIO
#define PAD_TS0_D7_IS_GPIO BALL_M21_IS_GPIO
#endif

#define BALL_M20 PAD_TS0_D6
#define PAD_TS0_D6 35
#define GPIO_PAD_35 GPIO34
#ifndef BALL_M20_IS_GPIO
#define BALL_M20_IS_GPIO 0
#endif
#ifndef PAD_TS0_D6_IS_GPIO
#define PAD_TS0_D6_IS_GPIO BALL_M20_IS_GPIO
#endif

#define BALL_M19 PAD_TS0_D5
#define PAD_TS0_D5 36
#define GPIO_PAD_36 GPIO35
#ifndef BALL_M19_IS_GPIO
#define BALL_M19_IS_GPIO 0
#endif
#ifndef PAD_TS0_D5_IS_GPIO
#define PAD_TS0_D5_IS_GPIO BALL_M19_IS_GPIO
#endif

#define BALL_L20 PAD_TS0_D4
#define PAD_TS0_D4 37
#define GPIO_PAD_37 GPIO36
#ifndef BALL_L20_IS_GPIO
#define BALL_L20_IS_GPIO 0
#endif
#ifndef PAD_TS0_D4_IS_GPIO
#define PAD_TS0_D4_IS_GPIO BALL_L20_IS_GPIO
#endif

#define BALL_L19 PAD_TS0_D3
#define PAD_TS0_D3 38
#define GPIO_PAD_38 GPIO37
#ifndef BALL_L19_IS_GPIO
#define BALL_L19_IS_GPIO 0
#endif
#ifndef PAD_TS0_D3_IS_GPIO
#define PAD_TS0_D3_IS_GPIO BALL_L19_IS_GPIO
#endif

#define BALL_K20 PAD_TS0_D2
#define PAD_TS0_D2 39
#define GPIO_PAD_39 GPIO38
#ifndef BALL_K20_IS_GPIO
#define BALL_K20_IS_GPIO 0
#endif
#ifndef PAD_TS0_D2_IS_GPIO
#define PAD_TS0_D2_IS_GPIO BALL_K20_IS_GPIO
#endif

#define BALL_K21 PAD_TS0_D1
#define PAD_TS0_D1 40
#define GPIO_PAD_40 GPIO39
#ifndef BALL_K21_IS_GPIO
#define BALL_K21_IS_GPIO 0
#endif
#ifndef PAD_TS0_D1_IS_GPIO
#define PAD_TS0_D1_IS_GPIO BALL_K21_IS_GPIO
#endif

#define BALL_K19 PAD_TS0_D0
#define PAD_TS0_D0 41
#define GPIO_PAD_41 GPIO40
#ifndef BALL_K19_IS_GPIO
#define BALL_K19_IS_GPIO 0
#endif
#ifndef PAD_TS0_D0_IS_GPIO
#define PAD_TS0_D0_IS_GPIO BALL_K19_IS_GPIO
#endif

#define BALL_J21 PAD_TS0_VLD
#define PAD_TS0_VLD 32
#define GPIO_PAD_32 GPIO31
#ifndef BALL_J21_IS_GPIO
#define BALL_J21_IS_GPIO 0
#endif
#ifndef PAD_TS0_VLD_IS_GPIO
#define PAD_TS0_VLD_IS_GPIO BALL_J21_IS_GPIO
#endif

#define BALL_J20 PAD_TS0_SYNC
#define PAD_TS0_SYNC 33
#define GPIO_PAD_33 GPIO32
#ifndef BALL_J20_IS_GPIO
#define BALL_J20_IS_GPIO 0
#endif
#ifndef PAD_TS0_SYNC_IS_GPIO
#define PAD_TS0_SYNC_IS_GPIO BALL_J20_IS_GPIO
#endif

#define BALL_R18 PAD_S_GPIO3
#define PAD_S_GPIO3 114
#define GPIO_PAD_114 GPIO113
#ifndef BALL_R18_IS_GPIO
#define BALL_R18_IS_GPIO 0
#endif
#ifndef PAD_S_GPIO3_IS_GPIO
#define PAD_S_GPIO3_IS_GPIO BALL_R18_IS_GPIO
#endif

#define BALL_N21 PAD_S_GPIO4
#define PAD_S_GPIO4 115
#define GPIO_PAD_115 GPIO114
#ifndef BALL_N21_IS_GPIO
#define BALL_N21_IS_GPIO 0
#endif
#ifndef PAD_S_GPIO4_IS_GPIO
#define PAD_S_GPIO4_IS_GPIO BALL_N21_IS_GPIO
#endif

#define BALL_H20 PAD_I2CM0_SDA
#define PAD_I2CM0_SDA 29
#define GPIO_PAD_29 GPIO28
#ifndef BALL_H20_IS_GPIO
#define BALL_H20_IS_GPIO 0
#endif
#ifndef PAD_I2CM0_SDA_IS_GPIO
#define PAD_I2CM0_SDA_IS_GPIO BALL_H20_IS_GPIO
#endif

#define BALL_H19 PAD_I2CM0_SCL
#define PAD_I2CM0_SCL 30
#define GPIO_PAD_30 GPIO29
#ifndef BALL_H19_IS_GPIO
#define BALL_H19_IS_GPIO 0
#endif
#ifndef PAD_I2CM0_SCL_IS_GPIO
#define PAD_I2CM0_SCL_IS_GPIO BALL_H19_IS_GPIO
#endif

#define BALL_D21 PAD_AGC_DOWN
#define PAD_AGC_DOWN 88
#define GPIO_PAD_88 GPIO87
#ifndef BALL_D21_IS_GPIO
#define BALL_D21_IS_GPIO 0
#endif
#ifndef PAD_AGC_DOWN_IS_GPIO
#define PAD_AGC_DOWN_IS_GPIO BALL_D21_IS_GPIO
#endif

#define BALL_C21 PAD_AGC_UP
#define PAD_AGC_UP 87
#define GPIO_PAD_87 GPIO86
#ifndef BALL_C21_IS_GPIO
#define BALL_C21_IS_GPIO 0
#endif
#ifndef PAD_AGC_UP_IS_GPIO
#define PAD_AGC_UP_IS_GPIO BALL_C21_IS_GPIO
#endif

#define BALL_C20 PAD_SAR0
#define PAD_SAR0 17
#define GPIO_PAD_17 GPIO16
#ifndef BALL_C20_IS_GPIO
#define BALL_C20_IS_GPIO 0
#endif
#ifndef PAD_SAR0_IS_GPIO
#define PAD_SAR0_IS_GPIO BALL_C20_IS_GPIO
#endif

#define BALL_B17 PAD_SAR1
#define PAD_SAR1 18
#define GPIO_PAD_18 GPIO17
#ifndef BALL_B17_IS_GPIO
#define BALL_B17_IS_GPIO 0
#endif
#ifndef PAD_SAR1_IS_GPIO
#define PAD_SAR1_IS_GPIO BALL_B17_IS_GPIO
#endif

#define BALL_C17 PAD_SAR2
#define PAD_SAR2 19
#define GPIO_PAD_19 GPIO18
#ifndef BALL_C17_IS_GPIO
#define BALL_C17_IS_GPIO 0
#endif
#ifndef PAD_SAR2_IS_GPIO
#define PAD_SAR2_IS_GPIO BALL_C17_IS_GPIO
#endif

#define BALL_D17 PAD_SAR3
#define PAD_SAR3 20
#define GPIO_PAD_20 GPIO19
#ifndef BALL_D17_IS_GPIO
#define BALL_D17_IS_GPIO 0
#endif
#ifndef PAD_SAR3_IS_GPIO
#define PAD_SAR3_IS_GPIO BALL_D17_IS_GPIO
#endif

#define BALL_E17 PAD_GPIO_PM9
#define PAD_GPIO_PM9 16
#define GPIO_PAD_16 GPIO15
#ifndef BALL_E17_IS_GPIO
#define BALL_E17_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM9_IS_GPIO
#define PAD_GPIO_PM9_IS_GPIO BALL_E17_IS_GPIO
#endif

#define BALL_A20 PAD_PM_SPI_CK
#define PAD_PM_SPI_CK 2
#define GPIO_PAD_2 GPIO1
#ifndef BALL_A20_IS_GPIO
#define BALL_A20_IS_GPIO 0
#endif
#ifndef PAD_PM_SPI_CK_IS_GPIO
#define PAD_PM_SPI_CK_IS_GPIO BALL_A20_IS_GPIO
#endif

#define BALL_B21 PAD_PM_SPI_DI
#define PAD_PM_SPI_DI 3
#define GPIO_PAD_3 GPIO2
#ifndef BALL_B21_IS_GPIO
#define BALL_B21_IS_GPIO 0
#endif
#ifndef PAD_PM_SPI_DI_IS_GPIO
#define PAD_PM_SPI_DI_IS_GPIO BALL_B21_IS_GPIO
#endif

#define BALL_B20 PAD_PM_SPI_DO
#define PAD_PM_SPI_DO 4
#define GPIO_PAD_4 GPIO3
#ifndef BALL_B20_IS_GPIO
#define BALL_B20_IS_GPIO 0
#endif
#ifndef PAD_PM_SPI_DO_IS_GPIO
#define PAD_PM_SPI_DO_IS_GPIO BALL_B20_IS_GPIO
#endif

#define BALL_C19 PAD_PM_SPI_CZ
#define PAD_PM_SPI_CZ 1
#define GPIO_PAD_1 GPIO0
#ifndef BALL_C19_IS_GPIO
#define BALL_C19_IS_GPIO 0
#endif
#ifndef PAD_PM_SPI_CZ_IS_GPIO
#define PAD_PM_SPI_CZ_IS_GPIO BALL_C19_IS_GPIO
#endif

#define BALL_B19 PAD_GPIO_PM0
#define PAD_GPIO_PM0 7
#define GPIO_PAD_7 GPIO6
#ifndef BALL_B19_IS_GPIO
#define BALL_B19_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM0_IS_GPIO
#define PAD_GPIO_PM0_IS_GPIO BALL_B19_IS_GPIO
#endif

#define BALL_C16 PAD_GPIO_PM1
#define PAD_GPIO_PM1 8
#define GPIO_PAD_8 GPIO7
#ifndef BALL_C16_IS_GPIO
#define BALL_C16_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM1_IS_GPIO
#define PAD_GPIO_PM1_IS_GPIO BALL_C16_IS_GPIO
#endif

#define BALL_A15 PAD_GPIO_PM4
#define PAD_GPIO_PM4 11
#define GPIO_PAD_11 GPIO10
#ifndef BALL_A15_IS_GPIO
#define BALL_A15_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM4_IS_GPIO
#define PAD_GPIO_PM4_IS_GPIO BALL_A15_IS_GPIO
#endif

#define BALL_B16 PAD_GPIO_PM2
#define PAD_GPIO_PM2 9
#define GPIO_PAD_9 GPIO8
#ifndef BALL_B16_IS_GPIO
#define BALL_B16_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM2_IS_GPIO
#define PAD_GPIO_PM2_IS_GPIO BALL_B16_IS_GPIO
#endif

#define BALL_B15 PAD_GPIO_PM5
#define PAD_GPIO_PM5 12
#define GPIO_PAD_12 GPIO11
#ifndef BALL_B15_IS_GPIO
#define BALL_B15_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM5_IS_GPIO
#define PAD_GPIO_PM5_IS_GPIO BALL_B15_IS_GPIO
#endif

#define BALL_C15 PAD_GPIO_PM3
#define PAD_GPIO_PM3 10
#define GPIO_PAD_10 GPIO9
#ifndef BALL_C15_IS_GPIO
#define BALL_C15_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM3_IS_GPIO
#define PAD_GPIO_PM3_IS_GPIO BALL_C15_IS_GPIO
#endif

#define BALL_D14 PAD_GPIO_PM6
#define PAD_GPIO_PM6 13
#define GPIO_PAD_13 GPIO12
#ifndef BALL_D14_IS_GPIO
#define BALL_D14_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM6_IS_GPIO
#define PAD_GPIO_PM6_IS_GPIO BALL_D14_IS_GPIO
#endif

#define BALL_D16 PAD_GPIO_PM7
#define PAD_GPIO_PM7 14
#define GPIO_PAD_14 GPIO13
#ifndef BALL_D16_IS_GPIO
#define BALL_D16_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM7_IS_GPIO
#define PAD_GPIO_PM7_IS_GPIO BALL_D16_IS_GPIO
#endif

#define BALL_A16 PAD_IRIN
#define PAD_IRIN 5
#define GPIO_PAD_5 GPIO4
#ifndef BALL_A16_IS_GPIO
#define BALL_A16_IS_GPIO 0
#endif
#ifndef PAD_IRIN_IS_GPIO
#define PAD_IRIN_IS_GPIO BALL_A16_IS_GPIO
#endif

#define BALL_D15 PAD_GPIO_PM8
#define PAD_GPIO_PM8 15
#define GPIO_PAD_15 GPIO14
#ifndef BALL_D15_IS_GPIO
#define BALL_D15_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM8_IS_GPIO
#define PAD_GPIO_PM8_IS_GPIO BALL_D15_IS_GPIO
#endif

#define BALL_A7 PAD_CEC
#define PAD_CEC 6
#define GPIO_PAD_6 GPIO5
#ifndef BALL_A7_IS_GPIO
#define BALL_A7_IS_GPIO 0
#endif
#ifndef PAD_CEC_IS_GPIO
#define PAD_CEC_IS_GPIO BALL_A7_IS_GPIO
#endif

#define BALL_C10 PAD_VSYNC_OUT
#define PAD_VSYNC_OUT 110
#define GPIO_PAD_110 GPIO109
#ifndef BALL_C10_IS_GPIO
#define BALL_C10_IS_GPIO 0
#endif
#ifndef PAD_VSYNC_OUT_IS_GPIO
#define PAD_VSYNC_OUT_IS_GPIO BALL_C10_IS_GPIO
#endif

#define BALL_B14 PAD_ET_MDIO
#define PAD_ET_MDIO 106
#define GPIO_PAD_106 GPIO105
#ifndef BALL_B14_IS_GPIO
#define BALL_B14_IS_GPIO 0
#endif
#ifndef PAD_ET_MDIO_IS_GPIO
#define PAD_ET_MDIO_IS_GPIO BALL_B14_IS_GPIO
#endif

#define PAD_ET_CRS 9999
#ifndef PAD_ET_CRS_IS_GPIO
#define PAD_ET_CRS_IS_GPIO 0
#endif

#define BALL_C13 PAD_ET_MDC
#define PAD_ET_MDC 105
#define GPIO_PAD_105 GPIO104
#ifndef BALL_C13_IS_GPIO
#define BALL_C13_IS_GPIO 0
#endif
#ifndef PAD_ET_MDC_IS_GPIO
#define PAD_ET_MDC_IS_GPIO BALL_C13_IS_GPIO
#endif

#define PAD_ET_TXD3 9999
#ifndef PAD_ET_TXD3_IS_GPIO
#define PAD_ET_TXD3_IS_GPIO 0
#endif

#define BALL_B13 PAD_ET_COL
#define PAD_ET_COL 90
#define GPIO_PAD_90 GPIO89
#ifndef BALL_B13_IS_GPIO
#define BALL_B13_IS_GPIO 0
#endif
#ifndef PAD_ET_COL_IS_GPIO
#define PAD_ET_COL_IS_GPIO BALL_B13_IS_GPIO
#endif

#define PAD_ET_TXD2 9999
#ifndef PAD_ET_TXD2_IS_GPIO
#define PAD_ET_TXD2_IS_GPIO 0
#endif

#define BALL_A13 PAD_ET_RXD0
#define PAD_ET_RXD0 101
#define GPIO_PAD_101 GPIO100
#ifndef BALL_A13_IS_GPIO
#define BALL_A13_IS_GPIO 0
#endif
#ifndef PAD_ET_RXD0_IS_GPIO
#define PAD_ET_RXD0_IS_GPIO BALL_A13_IS_GPIO
#endif

#define PAD_ET_TXER 9999
#ifndef PAD_ET_TXER_IS_GPIO
#define PAD_ET_TXER_IS_GPIO 0
#endif

#define BALL_C12 PAD_ET_RXD1
#define PAD_ET_RXD1 102
#define GPIO_PAD_102 GPIO101
#ifndef BALL_C12_IS_GPIO
#define BALL_C12_IS_GPIO 0
#endif
#ifndef PAD_ET_RXD1_IS_GPIO
#define PAD_ET_RXD1_IS_GPIO BALL_C12_IS_GPIO
#endif

#define PAD_ET_RXER 9999
#ifndef PAD_ET_RXER_IS_GPIO
#define PAD_ET_RXER_IS_GPIO 0
#endif

#define BALL_A12 PAD_ET_TX_CLK
#define PAD_ET_TX_CLK 96
#define GPIO_PAD_96 GPIO95
#ifndef BALL_A12_IS_GPIO
#define BALL_A12_IS_GPIO 0
#endif
#ifndef PAD_ET_TX_CLK_IS_GPIO
#define PAD_ET_TX_CLK_IS_GPIO BALL_A12_IS_GPIO
#endif

#define PAD_ET_RX_CLK 9999
#ifndef PAD_ET_RX_CLK_IS_GPIO
#define PAD_ET_RX_CLK_IS_GPIO 0
#endif

#define BALL_B12 PAD_ET_TXD0
#define PAD_ET_TXD0 94
#define GPIO_PAD_94 GPIO93
#ifndef BALL_B12_IS_GPIO
#define BALL_B12_IS_GPIO 0
#endif
#ifndef PAD_ET_TXD0_IS_GPIO
#define PAD_ET_TXD0_IS_GPIO BALL_B12_IS_GPIO
#endif

#define PAD_ET_RX_DV 9999
#ifndef PAD_ET_RX_DV_IS_GPIO
#define PAD_ET_RX_DV_IS_GPIO 0
#endif

#define BALL_C11 PAD_ET_TXD1
#define PAD_ET_TXD1 93
#define GPIO_PAD_93 GPIO92
#ifndef BALL_C11_IS_GPIO
#define BALL_C11_IS_GPIO 0
#endif
#ifndef PAD_ET_TXD1_IS_GPIO
#define PAD_ET_TXD1_IS_GPIO BALL_C11_IS_GPIO
#endif

#define PAD_ET_RXD2 9999
#ifndef PAD_ET_RXD2_IS_GPIO
#define PAD_ET_RXD2_IS_GPIO 0
#endif

#define BALL_B11 PAD_ET_TX_EN
#define PAD_ET_TX_EN 95
#define GPIO_PAD_95 GPIO94
#ifndef BALL_B11_IS_GPIO
#define BALL_B11_IS_GPIO 0
#endif
#ifndef PAD_ET_TX_EN_IS_GPIO
#define PAD_ET_TX_EN_IS_GPIO BALL_B11_IS_GPIO
#endif

#define PAD_ET_RXD3 9999
#ifndef PAD_ET_RXD3_IS_GPIO
#define PAD_ET_RXD3_IS_GPIO 0
#endif

#define PAD_S_GPIO5 9999
#ifndef PAD_S_GPIO5_IS_GPIO
#define PAD_S_GPIO5_IS_GPIO 0
#endif

#define BALL_A10 PAD_SPDIF_OUT2
#define PAD_SPDIF_OUT2 108
#define GPIO_PAD_108 GPIO107
#ifndef BALL_A10_IS_GPIO
#define BALL_A10_IS_GPIO 0
#endif
#ifndef PAD_SPDIF_OUT2_IS_GPIO
#define PAD_SPDIF_OUT2_IS_GPIO BALL_A10_IS_GPIO
#endif

#define BALL_B8 PAD_HSYNC_OUT
#define PAD_HSYNC_OUT 109
#define GPIO_PAD_109 GPIO108
#ifndef BALL_B8_IS_GPIO
#define BALL_B8_IS_GPIO 0
#endif
#ifndef PAD_HSYNC_OUT_IS_GPIO
#define PAD_HSYNC_OUT_IS_GPIO BALL_B8_IS_GPIO
#endif


// PADS group name to index
#define PADS_DDCR           1223
#define PADS_DDCR2          1224
#define PADS_TS0            1225
#define PADS_TS1            1226
#define PADS_GPIO1_GPIO2    1227
#define PADS_LHSYNC2_LVSYNC2 1228
#define PADS_PCI_AD20_AD21  1229
#define PADS_PCI            1230
#define PADS_PCM            1231
#define PADS_SAR            1232
#define PADS_DOUT           1233
#define PADS_DIN            1234
#define PADS_I2S            1235
#define PADS_PF             1236
#define PADS_EMAC           1237
#define PADS_TCON           1238
#define PADS_UART1_MODE1    1239
#define PADS_UART1_MODE2    1240
#define PADS_UART1_MODE3    1241
#define PADS_UART2_MODE1    1242
#define PADS_UART2_MODE2    1243
#define PADS_UART2_MODE3    1244
#define PADS_ET_MODE0       1245
#define PADS_ET_MODE1       1246
#define PADS_ET_MODE2       1247
#define PADS_ET_MODE3       1248
#define PADS_MIIC           1249
#define PADS_PF_MODE1       1250
#define PADS_PF_MODE2       1251
#define PADS_PF_MODE3       1252
#define PADS_SPI_CZ1        1253
#define PADS_SPI_CZ2        1254
#define PADS_SPI_CZ3        1255
#define PADS_DDCR3          1256

// chip capbilities
#define CHIP_HAS_BT656_IN          0
#define CHIP_HAS_TS0               1
#define CHIP_HAS_TS1               0
#define CHIP_HAS_LVDS_10BIT_X2     1
#define CHIP_HAS_LVDS_8BIT_X2      1
#define CHIP_HAS_LVDS_8BIT_X1      1
#define CHIP_HAS_CIMAX             0
#define CHIP_HAS_USB_P0            1
#define CHIP_HAS_USB_P1            1
#define CHIP_HAS_USBVBUS0          0
#define CHIP_HAS_USBVBUS1          0
#define CHIP_HAS_UART1_MODE1       1
#define CHIP_HAS_UART1_MODE2       1
#define CHIP_HAS_UART1_MODE3       1
#define CHIP_HAS_PCMCIA1           0
#define CHIP_HAS_PCMCIA2           0
#define CHIP_HAS_PCMCIA            0
#define CHIP_HAS_UART2_MODE1       1
#define CHIP_HAS_UART2_MODE2       1
#define CHIP_HAS_UART2_MODE3       1
#define CHIP_HAS_RGB_A             1
#define CHIP_HAS_RGB_B             1
#define CHIP_HAS_RGB_C             1
#define CHIP_HAS_HDMI_A            1
#define CHIP_HAS_HDMI_B            1
#define CHIP_HAS_HDMI_C            1
#define CHIP_HAS_SPI_CZ1           1
#define CHIP_HAS_SPI_CZ2           0
#define CHIP_HAS_SPI_CZ3           0
#define CHIP_HAS_DDCR              1
#define CHIP_HAS_DDCR2             1
#define CHIP_HAS_TCON              1
#define CHIP_HAS_ET_MODE0_MII      1
#define CHIP_HAS_ET_MODE0_RMII     1
#define CHIP_HAS_ET_MODE1_MII      1
#define CHIP_HAS_ET_MODE1_RMII     1
#define CHIP_HAS_ET_MODE2_MII      1
#define CHIP_HAS_ET_MODE2_RMII     1
#define CHIP_HAS_I2S_IN            0
#define CHIP_HAS_I2S_OUT           0
#define CHIP_HAS_SPDIF_IN          0
#define CHIP_HAS_SPDIF_OUT         0
#define CHIP_HAS_DDR_A_CMD         1
#define CHIP_HAS_DDR_A_DATA        1
#define CHIP_HAS_DDR_B_CMD         1
#define CHIP_HAS_DDR_B_DATA        1
#define CHIP_USE_PCM_CDN_IN_PCM2   0
#define CHIP_USE_I2S_IN_IN_PCM     0
#define CHIP_USE_I2S_OUT_IN_PCM    0
#define CHIP_USE_SPDIF_IN_IN_PCM   0
#define CHIP_USE_SPDIF_OUT_IN_PCM  0
#define CHIP_USE_IIC_IN_DDCR2      0
#define CHIP_USE_PWM2_IN_GPIO14    0
#define CHIP_USE_PWM3_IN_GPIO15    0

// chip additional information
#define CHIP_FAMILY_TYPE           CHIP_FAMILY_S7J

#endif /* _MSD7C12_H_*/
