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
#ifndef _MSD5C52_H_
#define _MSD5C52_H_

#define PAD_NC 9999
#define PAD_GND 0

#define BALL_R16 PAD_I2CM1_SCL
#define PAD_I2CM1_SCL 50
#define GPIO_PAD_50 GPIO49
#ifndef BALL_R16_IS_GPIO
#define BALL_R16_IS_GPIO 0
#endif
#ifndef PAD_I2CM1_SCL_IS_GPIO
#define PAD_I2CM1_SCL_IS_GPIO BALL_R16_IS_GPIO
#endif

#define BALL_T16 PAD_I2CM1_SDA
#define PAD_I2CM1_SDA 49
#define GPIO_PAD_49 GPIO48
#ifndef BALL_T16_IS_GPIO
#define BALL_T16_IS_GPIO 0
#endif
#ifndef PAD_I2CM1_SDA_IS_GPIO
#define PAD_I2CM1_SDA_IS_GPIO BALL_T16_IS_GPIO
#endif

#define BALL_U16 PAD_DM_GPIO0
#define PAD_DM_GPIO0 120
#define GPIO_PAD_120 GPIO119
#ifndef BALL_U16_IS_GPIO
#define BALL_U16_IS_GPIO 0
#endif
#ifndef PAD_DM_GPIO0_IS_GPIO
#define PAD_DM_GPIO0_IS_GPIO BALL_U16_IS_GPIO
#endif

#define BALL_V16 PAD_DM_GPIO1
#define PAD_DM_GPIO1 121
#define GPIO_PAD_121 GPIO120
#ifndef BALL_V16_IS_GPIO
#define BALL_V16_IS_GPIO 0
#endif
#ifndef PAD_DM_GPIO1_IS_GPIO
#define PAD_DM_GPIO1_IS_GPIO BALL_V16_IS_GPIO
#endif

#define BALL_T18 PAD_TS2_CLK
#define PAD_TS2_CLK 73
#define GPIO_PAD_73 GPIO72
#ifndef BALL_T18_IS_GPIO
#define BALL_T18_IS_GPIO 0
#endif
#ifndef PAD_TS2_CLK_IS_GPIO
#define PAD_TS2_CLK_IS_GPIO BALL_T18_IS_GPIO
#endif

#define BALL_U19 PAD_TS2_SYNC
#define PAD_TS2_SYNC 74
#define GPIO_PAD_74 GPIO73
#ifndef BALL_U19_IS_GPIO
#define BALL_U19_IS_GPIO 0
#endif
#ifndef PAD_TS2_SYNC_IS_GPIO
#define PAD_TS2_SYNC_IS_GPIO BALL_U19_IS_GPIO
#endif

#define BALL_V18 PAD_TS2_VLD
#define PAD_TS2_VLD 75
#define GPIO_PAD_75 GPIO74
#ifndef BALL_V18_IS_GPIO
#define BALL_V18_IS_GPIO 0
#endif
#ifndef PAD_TS2_VLD_IS_GPIO
#define PAD_TS2_VLD_IS_GPIO BALL_V18_IS_GPIO
#endif

#define BALL_U18 PAD_TS2_D0
#define PAD_TS2_D0 76
#define GPIO_PAD_76 GPIO75
#ifndef BALL_U18_IS_GPIO
#define BALL_U18_IS_GPIO 0
#endif
#ifndef PAD_TS2_D0_IS_GPIO
#define PAD_TS2_D0_IS_GPIO BALL_U18_IS_GPIO
#endif

#define BALL_W17 PAD_SM1_CD
#define PAD_SM1_CD 43
#define GPIO_PAD_43 GPIO42
#ifndef BALL_W17_IS_GPIO
#define BALL_W17_IS_GPIO 0
#endif
#ifndef PAD_SM1_CD_IS_GPIO
#define PAD_SM1_CD_IS_GPIO BALL_W17_IS_GPIO
#endif

#define BALL_AA18 PAD_SM1_RST
#define PAD_SM1_RST 42
#define GPIO_PAD_42 GPIO41
#ifndef BALL_AA18_IS_GPIO
#define BALL_AA18_IS_GPIO 0
#endif
#ifndef PAD_SM1_RST_IS_GPIO
#define PAD_SM1_RST_IS_GPIO BALL_AA18_IS_GPIO
#endif

#define BALL_Y18 PAD_SM1_VCC
#define PAD_SM1_VCC 44
#define GPIO_PAD_44 GPIO43
#ifndef BALL_Y18_IS_GPIO
#define BALL_Y18_IS_GPIO 0
#endif
#ifndef PAD_SM1_VCC_IS_GPIO
#define PAD_SM1_VCC_IS_GPIO BALL_Y18_IS_GPIO
#endif

#define BALL_W18 PAD_SM1_IO
#define PAD_SM1_IO 40
#define GPIO_PAD_40 GPIO39
#ifndef BALL_W18_IS_GPIO
#define BALL_W18_IS_GPIO 0
#endif
#ifndef PAD_SM1_IO_IS_GPIO
#define PAD_SM1_IO_IS_GPIO BALL_W18_IS_GPIO
#endif

#define BALL_Y19 PAD_SM1_CLK
#define PAD_SM1_CLK 41
#define GPIO_PAD_41 GPIO40
#ifndef BALL_Y19_IS_GPIO
#define BALL_Y19_IS_GPIO 0
#endif
#ifndef PAD_SM1_CLK_IS_GPIO
#define PAD_SM1_CLK_IS_GPIO BALL_Y19_IS_GPIO
#endif

#define BALL_V17 PAD_SM1_GPIO0
#define PAD_SM1_GPIO0 45
#define GPIO_PAD_45 GPIO44
#ifndef BALL_V17_IS_GPIO
#define BALL_V17_IS_GPIO 0
#endif
#ifndef PAD_SM1_GPIO0_IS_GPIO
#define PAD_SM1_GPIO0_IS_GPIO BALL_V17_IS_GPIO
#endif

#define BALL_U17 PAD_SM1_GPIO1
#define PAD_SM1_GPIO1 46
#define GPIO_PAD_46 GPIO45
#ifndef BALL_U17_IS_GPIO
#define BALL_U17_IS_GPIO 0
#endif
#ifndef PAD_SM1_GPIO1_IS_GPIO
#define PAD_SM1_GPIO1_IS_GPIO BALL_U17_IS_GPIO
#endif

#define BALL_M21 PAD_S_GPIO0
#define PAD_S_GPIO0 137
#define GPIO_PAD_137 GPIO136
#ifndef BALL_M21_IS_GPIO
#define BALL_M21_IS_GPIO 0
#endif
#ifndef PAD_S_GPIO0_IS_GPIO
#define PAD_S_GPIO0_IS_GPIO BALL_M21_IS_GPIO
#endif

#define BALL_M20 PAD_S_GPIO2
#define PAD_S_GPIO2 138
#define GPIO_PAD_138 GPIO137
#ifndef BALL_M20_IS_GPIO
#define BALL_M20_IS_GPIO 0
#endif
#ifndef PAD_S_GPIO2_IS_GPIO
#define PAD_S_GPIO2_IS_GPIO BALL_M20_IS_GPIO
#endif

#define BALL_L19 PAD_S_GPIO4
#define PAD_S_GPIO4 139
#define GPIO_PAD_139 GPIO138
#ifndef BALL_L19_IS_GPIO
#define BALL_L19_IS_GPIO 0
#endif
#ifndef PAD_S_GPIO4_IS_GPIO
#define PAD_S_GPIO4_IS_GPIO BALL_L19_IS_GPIO
#endif

#define BALL_W19 PAD_SM0_GPIO0
#define PAD_SM0_GPIO0 38
#define GPIO_PAD_38 GPIO37
#ifndef BALL_W19_IS_GPIO
#define BALL_W19_IS_GPIO 0
#endif
#ifndef PAD_SM0_GPIO0_IS_GPIO
#define PAD_SM0_GPIO0_IS_GPIO BALL_W19_IS_GPIO
#endif

#define BALL_AA21 PAD_SM0_CD
#define PAD_SM0_CD 36
#define GPIO_PAD_36 GPIO35
#ifndef BALL_AA21_IS_GPIO
#define BALL_AA21_IS_GPIO 0
#endif
#ifndef PAD_SM0_CD_IS_GPIO
#define PAD_SM0_CD_IS_GPIO BALL_AA21_IS_GPIO
#endif

#define BALL_Y20 PAD_SM0_RST
#define PAD_SM0_RST 35
#define GPIO_PAD_35 GPIO34
#ifndef BALL_Y20_IS_GPIO
#define BALL_Y20_IS_GPIO 0
#endif
#ifndef PAD_SM0_RST_IS_GPIO
#define PAD_SM0_RST_IS_GPIO BALL_Y20_IS_GPIO
#endif

#define BALL_Y21 PAD_SM0_VCC
#define PAD_SM0_VCC 37
#define GPIO_PAD_37 GPIO36
#ifndef BALL_Y21_IS_GPIO
#define BALL_Y21_IS_GPIO 0
#endif
#ifndef PAD_SM0_VCC_IS_GPIO
#define PAD_SM0_VCC_IS_GPIO BALL_Y21_IS_GPIO
#endif

#define BALL_W20 PAD_SM0_IO
#define PAD_SM0_IO 33
#define GPIO_PAD_33 GPIO32
#ifndef BALL_W20_IS_GPIO
#define BALL_W20_IS_GPIO 0
#endif
#ifndef PAD_SM0_IO_IS_GPIO
#define PAD_SM0_IO_IS_GPIO BALL_W20_IS_GPIO
#endif

#define BALL_W21 PAD_SM0_CLK
#define PAD_SM0_CLK 34
#define GPIO_PAD_34 GPIO33
#ifndef BALL_W21_IS_GPIO
#define BALL_W21_IS_GPIO 0
#endif
#ifndef PAD_SM0_CLK_IS_GPIO
#define PAD_SM0_CLK_IS_GPIO BALL_W21_IS_GPIO
#endif

#define BALL_AA20 PAD_SM0_GPIO1
#define PAD_SM0_GPIO1 39
#define GPIO_PAD_39 GPIO38
#ifndef BALL_AA20_IS_GPIO
#define BALL_AA20_IS_GPIO 0
#endif
#ifndef PAD_SM0_GPIO1_IS_GPIO
#define PAD_SM0_GPIO1_IS_GPIO BALL_AA20_IS_GPIO
#endif

#define BALL_P14 PAD_CI_A14
#define PAD_CI_A14 77
#define GPIO_PAD_77 GPIO76
#ifndef BALL_P14_IS_GPIO
#define BALL_P14_IS_GPIO 0
#endif
#ifndef PAD_CI_A14_IS_GPIO
#define PAD_CI_A14_IS_GPIO BALL_P14_IS_GPIO
#endif

#define BALL_P12 PAD_CI_A13
#define PAD_CI_A13 78
#define GPIO_PAD_78 GPIO77
#ifndef BALL_P12_IS_GPIO
#define BALL_P12_IS_GPIO 0
#endif
#ifndef PAD_CI_A13_IS_GPIO
#define PAD_CI_A13_IS_GPIO BALL_P12_IS_GPIO
#endif

#define BALL_P11 PAD_CI_A12
#define PAD_CI_A12 79
#define GPIO_PAD_79 GPIO78
#ifndef BALL_P11_IS_GPIO
#define BALL_P11_IS_GPIO 0
#endif
#ifndef PAD_CI_A12_IS_GPIO
#define PAD_CI_A12_IS_GPIO BALL_P11_IS_GPIO
#endif

#define BALL_N11 PAD_CI_A11
#define PAD_CI_A11 80
#define GPIO_PAD_80 GPIO79
#ifndef BALL_N11_IS_GPIO
#define BALL_N11_IS_GPIO 0
#endif
#ifndef PAD_CI_A11_IS_GPIO
#define PAD_CI_A11_IS_GPIO BALL_N11_IS_GPIO
#endif

#define BALL_N12 PAD_CI_A10
#define PAD_CI_A10 81
#define GPIO_PAD_81 GPIO80
#ifndef BALL_N12_IS_GPIO
#define BALL_N12_IS_GPIO 0
#endif
#ifndef PAD_CI_A10_IS_GPIO
#define PAD_CI_A10_IS_GPIO BALL_N12_IS_GPIO
#endif

#define BALL_N13 PAD_CI_A9
#define PAD_CI_A9 82
#define GPIO_PAD_82 GPIO81
#ifndef BALL_N13_IS_GPIO
#define BALL_N13_IS_GPIO 0
#endif
#ifndef PAD_CI_A9_IS_GPIO
#define PAD_CI_A9_IS_GPIO BALL_N13_IS_GPIO
#endif

#define BALL_P13 PAD_CI_A8
#define PAD_CI_A8 83
#define GPIO_PAD_83 GPIO82
#ifndef BALL_P13_IS_GPIO
#define BALL_P13_IS_GPIO 0
#endif
#ifndef PAD_CI_A8_IS_GPIO
#define PAD_CI_A8_IS_GPIO BALL_P13_IS_GPIO
#endif

#define BALL_M11 PAD_CI_A7
#define PAD_CI_A7 84
#define GPIO_PAD_84 GPIO83
#ifndef BALL_M11_IS_GPIO
#define BALL_M11_IS_GPIO 0
#endif
#ifndef PAD_CI_A7_IS_GPIO
#define PAD_CI_A7_IS_GPIO BALL_M11_IS_GPIO
#endif

#define BALL_N15 PAD_CI_A6
#define PAD_CI_A6 85
#define GPIO_PAD_85 GPIO84
#ifndef BALL_N15_IS_GPIO
#define BALL_N15_IS_GPIO 0
#endif
#ifndef PAD_CI_A6_IS_GPIO
#define PAD_CI_A6_IS_GPIO BALL_N15_IS_GPIO
#endif

#define BALL_L11 PAD_CI_A5
#define PAD_CI_A5 86
#define GPIO_PAD_86 GPIO85
#ifndef BALL_L11_IS_GPIO
#define BALL_L11_IS_GPIO 0
#endif
#ifndef PAD_CI_A5_IS_GPIO
#define PAD_CI_A5_IS_GPIO BALL_L11_IS_GPIO
#endif

#define BALL_M12 PAD_CI_A4
#define PAD_CI_A4 87
#define GPIO_PAD_87 GPIO86
#ifndef BALL_M12_IS_GPIO
#define BALL_M12_IS_GPIO 0
#endif
#ifndef PAD_CI_A4_IS_GPIO
#define PAD_CI_A4_IS_GPIO BALL_M12_IS_GPIO
#endif

#define BALL_P15 PAD_CI_A3
#define PAD_CI_A3 88
#define GPIO_PAD_88 GPIO87
#ifndef BALL_P15_IS_GPIO
#define BALL_P15_IS_GPIO 0
#endif
#ifndef PAD_CI_A3_IS_GPIO
#define PAD_CI_A3_IS_GPIO BALL_P15_IS_GPIO
#endif

#define BALL_N14 PAD_CI_A2
#define PAD_CI_A2 89
#define GPIO_PAD_89 GPIO88
#ifndef BALL_N14_IS_GPIO
#define BALL_N14_IS_GPIO 0
#endif
#ifndef PAD_CI_A2_IS_GPIO
#define PAD_CI_A2_IS_GPIO BALL_N14_IS_GPIO
#endif

#define BALL_L12 PAD_CI_A1
#define PAD_CI_A1 90
#define GPIO_PAD_90 GPIO89
#ifndef BALL_L12_IS_GPIO
#define BALL_L12_IS_GPIO 0
#endif
#ifndef PAD_CI_A1_IS_GPIO
#define PAD_CI_A1_IS_GPIO BALL_L12_IS_GPIO
#endif

#define BALL_N10 PAD_CI_A0
#define PAD_CI_A0 91
#define GPIO_PAD_91 GPIO90
#ifndef BALL_N10_IS_GPIO
#define BALL_N10_IS_GPIO 0
#endif
#ifndef PAD_CI_A0_IS_GPIO
#define PAD_CI_A0_IS_GPIO BALL_N10_IS_GPIO
#endif

#define BALL_M13 PAD_CI_D7
#define PAD_CI_D7 92
#define GPIO_PAD_92 GPIO91
#ifndef BALL_M13_IS_GPIO
#define BALL_M13_IS_GPIO 0
#endif
#ifndef PAD_CI_D7_IS_GPIO
#define PAD_CI_D7_IS_GPIO BALL_M13_IS_GPIO
#endif

#define BALL_L13 PAD_CI_D6
#define PAD_CI_D6 93
#define GPIO_PAD_93 GPIO92
#ifndef BALL_L13_IS_GPIO
#define BALL_L13_IS_GPIO 0
#endif
#ifndef PAD_CI_D6_IS_GPIO
#define PAD_CI_D6_IS_GPIO BALL_L13_IS_GPIO
#endif

#define BALL_M15 PAD_CI_D5
#define PAD_CI_D5 94
#define GPIO_PAD_94 GPIO93
#ifndef BALL_M15_IS_GPIO
#define BALL_M15_IS_GPIO 0
#endif
#ifndef PAD_CI_D5_IS_GPIO
#define PAD_CI_D5_IS_GPIO BALL_M15_IS_GPIO
#endif

#define BALL_M14 PAD_CI_D4
#define PAD_CI_D4 95
#define GPIO_PAD_95 GPIO94
#ifndef BALL_M14_IS_GPIO
#define BALL_M14_IS_GPIO 0
#endif
#ifndef PAD_CI_D4_IS_GPIO
#define PAD_CI_D4_IS_GPIO BALL_M14_IS_GPIO
#endif

#define BALL_L14 PAD_CI_D3
#define PAD_CI_D3 96
#define GPIO_PAD_96 GPIO95
#ifndef BALL_L14_IS_GPIO
#define BALL_L14_IS_GPIO 0
#endif
#ifndef PAD_CI_D3_IS_GPIO
#define PAD_CI_D3_IS_GPIO BALL_L14_IS_GPIO
#endif

#define BALL_M10 PAD_CI_D2
#define PAD_CI_D2 97
#define GPIO_PAD_97 GPIO96
#ifndef BALL_M10_IS_GPIO
#define BALL_M10_IS_GPIO 0
#endif
#ifndef PAD_CI_D2_IS_GPIO
#define PAD_CI_D2_IS_GPIO BALL_M10_IS_GPIO
#endif

#define BALL_K10 PAD_CI_D1
#define PAD_CI_D1 98
#define GPIO_PAD_98 GPIO97
#ifndef BALL_K10_IS_GPIO
#define BALL_K10_IS_GPIO 0
#endif
#ifndef PAD_CI_D1_IS_GPIO
#define PAD_CI_D1_IS_GPIO BALL_K10_IS_GPIO
#endif

#define BALL_L10 PAD_CI_D0
#define PAD_CI_D0 99
#define GPIO_PAD_99 GPIO98
#ifndef BALL_L10_IS_GPIO
#define BALL_L10_IS_GPIO 0
#endif
#ifndef PAD_CI_D0_IS_GPIO
#define PAD_CI_D0_IS_GPIO BALL_L10_IS_GPIO
#endif

#define BALL_T19 PAD_NF_RBZ
#define PAD_NF_RBZ 123
#define GPIO_PAD_123 GPIO122
#ifndef BALL_T19_IS_GPIO
#define BALL_T19_IS_GPIO 0
#endif
#ifndef PAD_NF_RBZ_IS_GPIO
#define PAD_NF_RBZ_IS_GPIO BALL_T19_IS_GPIO
#endif

#define BALL_L15 PAD_CI_IORDZ
#define PAD_CI_IORDZ 100
#define GPIO_PAD_100 GPIO99
#ifndef BALL_L15_IS_GPIO
#define BALL_L15_IS_GPIO 0
#endif
#ifndef PAD_CI_IORDZ_IS_GPIO
#define PAD_CI_IORDZ_IS_GPIO BALL_L15_IS_GPIO
#endif

#define BALL_N19 PAD_NF_REZ
#define PAD_NF_REZ 124
#define GPIO_PAD_124 GPIO123
#ifndef BALL_N19_IS_GPIO
#define BALL_N19_IS_GPIO 0
#endif
#ifndef PAD_NF_REZ_IS_GPIO
#define PAD_NF_REZ_IS_GPIO BALL_N19_IS_GPIO
#endif

#define BALL_K14 PAD_CI_IOWRZ
#define PAD_CI_IOWRZ 101
#define GPIO_PAD_101 GPIO100
#ifndef BALL_K14_IS_GPIO
#define BALL_K14_IS_GPIO 0
#endif
#ifndef PAD_CI_IOWRZ_IS_GPIO
#define PAD_CI_IOWRZ_IS_GPIO BALL_K14_IS_GPIO
#endif

#define BALL_P21 PAD_NF_CEZ_BGA
#define PAD_NF_CEZ_BGA 122
#define GPIO_PAD_122 GPIO121
#ifndef BALL_P21_IS_GPIO
#define BALL_P21_IS_GPIO 0
#endif
#ifndef PAD_NF_CEZ_BGA_IS_GPIO
#define PAD_NF_CEZ_BGA_IS_GPIO BALL_P21_IS_GPIO
#endif

#define BALL_P16 PAD_CI_OEZ
#define PAD_CI_OEZ 102
#define GPIO_PAD_102 GPIO101
#ifndef BALL_P16_IS_GPIO
#define BALL_P16_IS_GPIO 0
#endif
#ifndef PAD_CI_OEZ_IS_GPIO
#define PAD_CI_OEZ_IS_GPIO BALL_P16_IS_GPIO
#endif

#define BALL_P20 PAD_NF_CLE
#define PAD_NF_CLE 125
#define GPIO_PAD_125 GPIO124
#ifndef BALL_P20_IS_GPIO
#define BALL_P20_IS_GPIO 0
#endif
#ifndef PAD_NF_CLE_IS_GPIO
#define PAD_NF_CLE_IS_GPIO BALL_P20_IS_GPIO
#endif

#define BALL_R18 PAD_CI_WEZ
#define PAD_CI_WEZ 103
#define GPIO_PAD_103 GPIO102
#ifndef BALL_R18_IS_GPIO
#define BALL_R18_IS_GPIO 0
#endif
#ifndef PAD_CI_WEZ_IS_GPIO
#define PAD_CI_WEZ_IS_GPIO BALL_R18_IS_GPIO
#endif

#define BALL_M19 PAD_NF_ALE
#define PAD_NF_ALE 126
#define GPIO_PAD_126 GPIO125
#ifndef BALL_M19_IS_GPIO
#define BALL_M19_IS_GPIO 0
#endif
#ifndef PAD_NF_ALE_IS_GPIO
#define PAD_NF_ALE_IS_GPIO BALL_M19_IS_GPIO
#endif

#define BALL_R17 PAD_CI_REGZ
#define PAD_CI_REGZ 104
#define GPIO_PAD_104 GPIO103
#ifndef BALL_R17_IS_GPIO
#define BALL_R17_IS_GPIO 0
#endif
#ifndef PAD_CI_REGZ_IS_GPIO
#define PAD_CI_REGZ_IS_GPIO BALL_R17_IS_GPIO
#endif

#define BALL_P19 PAD_NF_WEZ
#define PAD_NF_WEZ 127
#define GPIO_PAD_127 GPIO126
#ifndef BALL_P19_IS_GPIO
#define BALL_P19_IS_GPIO 0
#endif
#ifndef PAD_NF_WEZ_IS_GPIO
#define PAD_NF_WEZ_IS_GPIO BALL_P19_IS_GPIO
#endif

#define BALL_V19 PAD_CI_CEZ
#define PAD_CI_CEZ 105
#define GPIO_PAD_105 GPIO104
#ifndef BALL_V19_IS_GPIO
#define BALL_V19_IS_GPIO 0
#endif
#ifndef PAD_CI_CEZ_IS_GPIO
#define PAD_CI_CEZ_IS_GPIO BALL_V19_IS_GPIO
#endif

#define BALL_N20 PAD_NF_WPZ
#define PAD_NF_WPZ 128
#define GPIO_PAD_128 GPIO127
#ifndef BALL_N20_IS_GPIO
#define BALL_N20_IS_GPIO 0
#endif
#ifndef PAD_NF_WPZ_IS_GPIO
#define PAD_NF_WPZ_IS_GPIO BALL_N20_IS_GPIO
#endif

#define BALL_K11 PAD_CI_IRQAZ
#define PAD_CI_IRQAZ 106
#define GPIO_PAD_106 GPIO105
#ifndef BALL_K11_IS_GPIO
#define BALL_K11_IS_GPIO 0
#endif
#ifndef PAD_CI_IRQAZ_IS_GPIO
#define PAD_CI_IRQAZ_IS_GPIO BALL_K11_IS_GPIO
#endif

#define BALL_R21 PAD_NF_D0
#define PAD_NF_D0 129
#define GPIO_PAD_129 GPIO128
#ifndef BALL_R21_IS_GPIO
#define BALL_R21_IS_GPIO 0
#endif
#ifndef PAD_NF_D0_IS_GPIO
#define PAD_NF_D0_IS_GPIO BALL_R21_IS_GPIO
#endif

#define BALL_K12 PAD_CI_WAITZ
#define PAD_CI_WAITZ 107
#define GPIO_PAD_107 GPIO106
#ifndef BALL_K12_IS_GPIO
#define BALL_K12_IS_GPIO 0
#endif
#ifndef PAD_CI_WAITZ_IS_GPIO
#define PAD_CI_WAITZ_IS_GPIO BALL_K12_IS_GPIO
#endif

#define BALL_R19 PAD_NF_D1
#define PAD_NF_D1 130
#define GPIO_PAD_130 GPIO129
#ifndef BALL_R19_IS_GPIO
#define BALL_R19_IS_GPIO 0
#endif
#ifndef PAD_NF_D1_IS_GPIO
#define PAD_NF_D1_IS_GPIO BALL_R19_IS_GPIO
#endif

#define BALL_K15 PAD_CI_RST
#define PAD_CI_RST 108
#define GPIO_PAD_108 GPIO107
#ifndef BALL_K15_IS_GPIO
#define BALL_K15_IS_GPIO 0
#endif
#ifndef PAD_CI_RST_IS_GPIO
#define PAD_CI_RST_IS_GPIO BALL_K15_IS_GPIO
#endif

#define BALL_R20 PAD_NF_D2
#define PAD_NF_D2 131
#define GPIO_PAD_131 GPIO130
#ifndef BALL_R20_IS_GPIO
#define BALL_R20_IS_GPIO 0
#endif
#ifndef PAD_NF_D2_IS_GPIO
#define PAD_NF_D2_IS_GPIO BALL_R20_IS_GPIO
#endif

#define BALL_K13 PAD_CI_CDZ
#define PAD_CI_CDZ 109
#define GPIO_PAD_109 GPIO108
#ifndef BALL_K13_IS_GPIO
#define BALL_K13_IS_GPIO 0
#endif
#ifndef PAD_CI_CDZ_IS_GPIO
#define PAD_CI_CDZ_IS_GPIO BALL_K13_IS_GPIO
#endif

#define BALL_T20 PAD_NF_D3
#define PAD_NF_D3 132
#define GPIO_PAD_132 GPIO131
#ifndef BALL_T20_IS_GPIO
#define BALL_T20_IS_GPIO 0
#endif
#ifndef PAD_NF_D3_IS_GPIO
#define PAD_NF_D3_IS_GPIO BALL_T20_IS_GPIO
#endif

#define BALL_D17 PAD_TS0_CLK
#define PAD_TS0_CLK 51
#define GPIO_PAD_51 GPIO50
#ifndef BALL_D17_IS_GPIO
#define BALL_D17_IS_GPIO 0
#endif
#ifndef PAD_TS0_CLK_IS_GPIO
#define PAD_TS0_CLK_IS_GPIO BALL_D17_IS_GPIO
#endif

#define BALL_U21 PAD_NF_D4
#define PAD_NF_D4 133
#define GPIO_PAD_133 GPIO132
#ifndef BALL_U21_IS_GPIO
#define BALL_U21_IS_GPIO 0
#endif
#ifndef PAD_NF_D4_IS_GPIO
#define PAD_NF_D4_IS_GPIO BALL_U21_IS_GPIO
#endif

#define BALL_K18 PAD_TS0_D7
#define PAD_TS0_D7 54
#define GPIO_PAD_54 GPIO53
#ifndef BALL_K18_IS_GPIO
#define BALL_K18_IS_GPIO 0
#endif
#ifndef PAD_TS0_D7_IS_GPIO
#define PAD_TS0_D7_IS_GPIO BALL_K18_IS_GPIO
#endif

#define BALL_U20 PAD_NF_D5
#define PAD_NF_D5 134
#define GPIO_PAD_134 GPIO133
#ifndef BALL_U20_IS_GPIO
#define BALL_U20_IS_GPIO 0
#endif
#ifndef PAD_NF_D5_IS_GPIO
#define PAD_NF_D5_IS_GPIO BALL_U20_IS_GPIO
#endif

#define BALL_H19 PAD_TS0_D6
#define PAD_TS0_D6 55
#define GPIO_PAD_55 GPIO54
#ifndef BALL_H19_IS_GPIO
#define BALL_H19_IS_GPIO 0
#endif
#ifndef PAD_TS0_D6_IS_GPIO
#define PAD_TS0_D6_IS_GPIO BALL_H19_IS_GPIO
#endif

#define BALL_V21 PAD_NF_D6
#define PAD_NF_D6 135
#define GPIO_PAD_135 GPIO134
#ifndef BALL_V21_IS_GPIO
#define BALL_V21_IS_GPIO 0
#endif
#ifndef PAD_NF_D6_IS_GPIO
#define PAD_NF_D6_IS_GPIO BALL_V21_IS_GPIO
#endif

#define BALL_G18 PAD_TS0_D5
#define PAD_TS0_D5 56
#define GPIO_PAD_56 GPIO55
#ifndef BALL_G18_IS_GPIO
#define BALL_G18_IS_GPIO 0
#endif
#ifndef PAD_TS0_D5_IS_GPIO
#define PAD_TS0_D5_IS_GPIO BALL_G18_IS_GPIO
#endif

#define BALL_V20 PAD_NF_D7
#define PAD_NF_D7 136
#define GPIO_PAD_136 GPIO135
#ifndef BALL_V20_IS_GPIO
#define BALL_V20_IS_GPIO 0
#endif
#ifndef PAD_NF_D7_IS_GPIO
#define PAD_NF_D7_IS_GPIO BALL_V20_IS_GPIO
#endif

#define BALL_F18 PAD_TS0_D4
#define PAD_TS0_D4 57
#define GPIO_PAD_57 GPIO56
#ifndef BALL_F18_IS_GPIO
#define BALL_F18_IS_GPIO 0
#endif
#ifndef PAD_TS0_D4_IS_GPIO
#define PAD_TS0_D4_IS_GPIO BALL_F18_IS_GPIO
#endif

#define BALL_F16 PAD_TS0_D3
#define PAD_TS0_D3 58
#define GPIO_PAD_58 GPIO57
#ifndef BALL_F16_IS_GPIO
#define BALL_F16_IS_GPIO 0
#endif
#ifndef PAD_TS0_D3_IS_GPIO
#define PAD_TS0_D3_IS_GPIO BALL_F16_IS_GPIO
#endif

#define BALL_E18 PAD_TS0_D2
#define PAD_TS0_D2 59
#define GPIO_PAD_59 GPIO58
#ifndef BALL_E18_IS_GPIO
#define BALL_E18_IS_GPIO 0
#endif
#ifndef PAD_TS0_D2_IS_GPIO
#define PAD_TS0_D2_IS_GPIO BALL_E18_IS_GPIO
#endif

#define BALL_E17 PAD_TS0_D1
#define PAD_TS0_D1 60
#define GPIO_PAD_60 GPIO59
#ifndef BALL_E17_IS_GPIO
#define BALL_E17_IS_GPIO 0
#endif
#ifndef PAD_TS0_D1_IS_GPIO
#define PAD_TS0_D1_IS_GPIO BALL_E17_IS_GPIO
#endif

#define BALL_D18 PAD_TS0_D0
#define PAD_TS0_D0 61
#define GPIO_PAD_61 GPIO60
#ifndef BALL_D18_IS_GPIO
#define BALL_D18_IS_GPIO 0
#endif
#ifndef PAD_TS0_D0_IS_GPIO
#define PAD_TS0_D0_IS_GPIO BALL_D18_IS_GPIO
#endif

#define BALL_L18 PAD_TS0_VLD
#define PAD_TS0_VLD 52
#define GPIO_PAD_52 GPIO51
#ifndef BALL_L18_IS_GPIO
#define BALL_L18_IS_GPIO 0
#endif
#ifndef PAD_TS0_VLD_IS_GPIO
#define PAD_TS0_VLD_IS_GPIO BALL_L18_IS_GPIO
#endif

#define BALL_M18 PAD_TS0_SYNC
#define PAD_TS0_SYNC 53
#define GPIO_PAD_53 GPIO52
#ifndef BALL_M18_IS_GPIO
#define BALL_M18_IS_GPIO 0
#endif
#ifndef PAD_TS0_SYNC_IS_GPIO
#define PAD_TS0_SYNC_IS_GPIO BALL_M18_IS_GPIO
#endif

#define BALL_P17 PAD_VSYNC_OUT
#define PAD_VSYNC_OUT 119
#define GPIO_PAD_119 GPIO118
#ifndef BALL_P17_IS_GPIO
#define BALL_P17_IS_GPIO 0
#endif
#ifndef PAD_VSYNC_OUT_IS_GPIO
#define PAD_VSYNC_OUT_IS_GPIO BALL_P17_IS_GPIO
#endif

#define BALL_P18 PAD_HSYNC_OUT
#define PAD_HSYNC_OUT 118
#define GPIO_PAD_118 GPIO117
#ifndef BALL_P18_IS_GPIO
#define BALL_P18_IS_GPIO 0
#endif
#ifndef PAD_HSYNC_OUT_IS_GPIO
#define PAD_HSYNC_OUT_IS_GPIO BALL_P18_IS_GPIO
#endif

#define BALL_G17 PAD_TS1_CLK
#define PAD_TS1_CLK 62
#define GPIO_PAD_62 GPIO61
#ifndef BALL_G17_IS_GPIO
#define BALL_G17_IS_GPIO 0
#endif
#ifndef PAD_TS1_CLK_IS_GPIO
#define PAD_TS1_CLK_IS_GPIO BALL_G17_IS_GPIO
#endif

#define BALL_N18 PAD_TS1_D7
#define PAD_TS1_D7 65
#define GPIO_PAD_65 GPIO64
#ifndef BALL_N18_IS_GPIO
#define BALL_N18_IS_GPIO 0
#endif
#ifndef PAD_TS1_D7_IS_GPIO
#define PAD_TS1_D7_IS_GPIO BALL_N18_IS_GPIO
#endif

#define BALL_M16 PAD_TS1_D6
#define PAD_TS1_D6 66
#define GPIO_PAD_66 GPIO65
#ifndef BALL_M16_IS_GPIO
#define BALL_M16_IS_GPIO 0
#endif
#ifndef PAD_TS1_D6_IS_GPIO
#define PAD_TS1_D6_IS_GPIO BALL_M16_IS_GPIO
#endif

#define BALL_M17 PAD_TS1_D5
#define PAD_TS1_D5 67
#define GPIO_PAD_67 GPIO66
#ifndef BALL_M17_IS_GPIO
#define BALL_M17_IS_GPIO 0
#endif
#ifndef PAD_TS1_D5_IS_GPIO
#define PAD_TS1_D5_IS_GPIO BALL_M17_IS_GPIO
#endif

#define BALL_L17 PAD_TS1_D4
#define PAD_TS1_D4 68
#define GPIO_PAD_68 GPIO67
#ifndef BALL_L17_IS_GPIO
#define BALL_L17_IS_GPIO 0
#endif
#ifndef PAD_TS1_D4_IS_GPIO
#define PAD_TS1_D4_IS_GPIO BALL_L17_IS_GPIO
#endif

#define BALL_L16 PAD_TS1_D3
#define PAD_TS1_D3 69
#define GPIO_PAD_69 GPIO68
#ifndef BALL_L16_IS_GPIO
#define BALL_L16_IS_GPIO 0
#endif
#ifndef PAD_TS1_D3_IS_GPIO
#define PAD_TS1_D3_IS_GPIO BALL_L16_IS_GPIO
#endif

#define BALL_K16 PAD_TS1_D2
#define PAD_TS1_D2 70
#define GPIO_PAD_70 GPIO69
#ifndef BALL_K16_IS_GPIO
#define BALL_K16_IS_GPIO 0
#endif
#ifndef PAD_TS1_D2_IS_GPIO
#define PAD_TS1_D2_IS_GPIO BALL_K16_IS_GPIO
#endif

#define BALL_K17 PAD_TS1_D1
#define PAD_TS1_D1 71
#define GPIO_PAD_71 GPIO70
#ifndef BALL_K17_IS_GPIO
#define BALL_K17_IS_GPIO 0
#endif
#ifndef PAD_TS1_D1_IS_GPIO
#define PAD_TS1_D1_IS_GPIO BALL_K17_IS_GPIO
#endif

#define BALL_E15 PAD_I2S_OUT_SD3
#define PAD_I2S_OUT_SD3 111
#define GPIO_PAD_111 GPIO110
#ifndef BALL_E15_IS_GPIO
#define BALL_E15_IS_GPIO 0
#endif
#ifndef PAD_I2S_OUT_SD3_IS_GPIO
#define PAD_I2S_OUT_SD3_IS_GPIO BALL_E15_IS_GPIO
#endif

#define BALL_G16 PAD_TS1_D0
#define PAD_TS1_D0 72
#define GPIO_PAD_72 GPIO71
#ifndef BALL_G16_IS_GPIO
#define BALL_G16_IS_GPIO 0
#endif
#ifndef PAD_TS1_D0_IS_GPIO
#define PAD_TS1_D0_IS_GPIO BALL_G16_IS_GPIO
#endif

#define BALL_E14 PAD_I2S_OUT_SD2
#define PAD_I2S_OUT_SD2 112
#define GPIO_PAD_112 GPIO111
#ifndef BALL_E14_IS_GPIO
#define BALL_E14_IS_GPIO 0
#endif
#ifndef PAD_I2S_OUT_SD2_IS_GPIO
#define PAD_I2S_OUT_SD2_IS_GPIO BALL_E14_IS_GPIO
#endif

#define BALL_N17 PAD_TS1_VLD
#define PAD_TS1_VLD 64
#define GPIO_PAD_64 GPIO63
#ifndef BALL_N17_IS_GPIO
#define BALL_N17_IS_GPIO 0
#endif
#ifndef PAD_TS1_VLD_IS_GPIO
#define PAD_TS1_VLD_IS_GPIO BALL_N17_IS_GPIO
#endif

#define BALL_F15 PAD_I2S_OUT_SD1
#define PAD_I2S_OUT_SD1 113
#define GPIO_PAD_113 GPIO112
#ifndef BALL_F15_IS_GPIO
#define BALL_F15_IS_GPIO 0
#endif
#ifndef PAD_I2S_OUT_SD1_IS_GPIO
#define PAD_I2S_OUT_SD1_IS_GPIO BALL_F15_IS_GPIO
#endif

#define BALL_N16 PAD_TS1_SYNC
#define PAD_TS1_SYNC 63
#define GPIO_PAD_63 GPIO62
#ifndef BALL_N16_IS_GPIO
#define BALL_N16_IS_GPIO 0
#endif
#ifndef PAD_TS1_SYNC_IS_GPIO
#define PAD_TS1_SYNC_IS_GPIO BALL_N16_IS_GPIO
#endif

#define BALL_E13 PAD_I2S_OUT_SD0
#define PAD_I2S_OUT_SD0 116
#define GPIO_PAD_116 GPIO115
#ifndef BALL_E13_IS_GPIO
#define BALL_E13_IS_GPIO 0
#endif
#ifndef PAD_I2S_OUT_SD0_IS_GPIO
#define PAD_I2S_OUT_SD0_IS_GPIO BALL_E13_IS_GPIO
#endif

#define BALL_H20 PAD_I2CM0_SDA
#define PAD_I2CM0_SDA 47
#define GPIO_PAD_47 GPIO46
#ifndef BALL_H20_IS_GPIO
#define BALL_H20_IS_GPIO 0
#endif
#ifndef PAD_I2CM0_SDA_IS_GPIO
#define PAD_I2CM0_SDA_IS_GPIO BALL_H20_IS_GPIO
#endif

#define BALL_D12 PAD_I2S_OUT_WS
#define PAD_I2S_OUT_WS 114
#define GPIO_PAD_114 GPIO113
#ifndef BALL_D12_IS_GPIO
#define BALL_D12_IS_GPIO 0
#endif
#ifndef PAD_I2S_OUT_WS_IS_GPIO
#define PAD_I2S_OUT_WS_IS_GPIO BALL_D12_IS_GPIO
#endif

#define BALL_J19 PAD_I2CM0_SCL
#define PAD_I2CM0_SCL 48
#define GPIO_PAD_48 GPIO47
#ifndef BALL_J19_IS_GPIO
#define BALL_J19_IS_GPIO 0
#endif
#ifndef PAD_I2CM0_SCL_IS_GPIO
#define PAD_I2CM0_SCL_IS_GPIO BALL_J19_IS_GPIO
#endif

#define BALL_E11 PAD_I2S_OUT_MCK
#define PAD_I2S_OUT_MCK 117
#define GPIO_PAD_117 GPIO116
#ifndef BALL_E11_IS_GPIO
#define BALL_E11_IS_GPIO 0
#endif
#ifndef PAD_I2S_OUT_MCK_IS_GPIO
#define PAD_I2S_OUT_MCK_IS_GPIO BALL_E11_IS_GPIO
#endif

#define BALL_E20 PAD_SPDIF_OUT
#define PAD_SPDIF_OUT 110
#define GPIO_PAD_110 GPIO109
#ifndef BALL_E20_IS_GPIO
#define BALL_E20_IS_GPIO 0
#endif
#ifndef PAD_SPDIF_OUT_IS_GPIO
#define PAD_SPDIF_OUT_IS_GPIO BALL_E20_IS_GPIO
#endif

#define BALL_E12 PAD_I2S_OUT_BCK
#define PAD_I2S_OUT_BCK 115
#define GPIO_PAD_115 GPIO114
#ifndef BALL_E12_IS_GPIO
#define BALL_E12_IS_GPIO 0
#endif
#ifndef PAD_I2S_OUT_BCK_IS_GPIO
#define PAD_I2S_OUT_BCK_IS_GPIO BALL_E12_IS_GPIO
#endif

#define BALL_F21 PAD_SAR0
#define PAD_SAR0 18
#define GPIO_PAD_18 GPIO17
#ifndef BALL_F21_IS_GPIO
#define BALL_F21_IS_GPIO 0
#endif
#ifndef PAD_SAR0_IS_GPIO
#define PAD_SAR0_IS_GPIO BALL_F21_IS_GPIO
#endif

#define BALL_F20 PAD_SAR1
#define PAD_SAR1 19
#define GPIO_PAD_19 GPIO18
#ifndef BALL_F20_IS_GPIO
#define BALL_F20_IS_GPIO 0
#endif
#ifndef PAD_SAR1_IS_GPIO
#define PAD_SAR1_IS_GPIO BALL_F20_IS_GPIO
#endif

#define BALL_F19 PAD_SAR2
#define PAD_SAR2 20
#define GPIO_PAD_20 GPIO19
#ifndef BALL_F19_IS_GPIO
#define BALL_F19_IS_GPIO 0
#endif
#ifndef PAD_SAR2_IS_GPIO
#define PAD_SAR2_IS_GPIO BALL_F19_IS_GPIO
#endif

#define BALL_E19 PAD_SAR3
#define PAD_SAR3 21
#define GPIO_PAD_21 GPIO20
#ifndef BALL_E19_IS_GPIO
#define BALL_E19_IS_GPIO 0
#endif
#ifndef PAD_SAR3_IS_GPIO
#define PAD_SAR3_IS_GPIO BALL_E19_IS_GPIO
#endif

#define BALL_B21 PAD_PM_SPI_CK
#define PAD_PM_SPI_CK 2
#define GPIO_PAD_2 GPIO1
#ifndef BALL_B21_IS_GPIO
#define BALL_B21_IS_GPIO 0
#endif
#ifndef PAD_PM_SPI_CK_IS_GPIO
#define PAD_PM_SPI_CK_IS_GPIO BALL_B21_IS_GPIO
#endif

#define BALL_D21 PAD_PM_SPI_DI
#define PAD_PM_SPI_DI 3
#define GPIO_PAD_3 GPIO2
#ifndef BALL_D21_IS_GPIO
#define BALL_D21_IS_GPIO 0
#endif
#ifndef PAD_PM_SPI_DI_IS_GPIO
#define PAD_PM_SPI_DI_IS_GPIO BALL_D21_IS_GPIO
#endif

#define BALL_D20 PAD_PM_SPI_DO
#define PAD_PM_SPI_DO 4
#define GPIO_PAD_4 GPIO3
#ifndef BALL_D20_IS_GPIO
#define BALL_D20_IS_GPIO 0
#endif
#ifndef PAD_PM_SPI_DO_IS_GPIO
#define PAD_PM_SPI_DO_IS_GPIO BALL_D20_IS_GPIO
#endif

#define BALL_C21 PAD_PM_SPI_CZ
#define PAD_PM_SPI_CZ 1
#define GPIO_PAD_1 GPIO0
#ifndef BALL_C21_IS_GPIO
#define BALL_C21_IS_GPIO 0
#endif
#ifndef PAD_PM_SPI_CZ_IS_GPIO
#define PAD_PM_SPI_CZ_IS_GPIO BALL_C21_IS_GPIO
#endif

#define BALL_E16 PAD_GPIO_PM0
#define PAD_GPIO_PM0 7
#define GPIO_PAD_7 GPIO6
#ifndef BALL_E16_IS_GPIO
#define BALL_E16_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM0_IS_GPIO
#define PAD_GPIO_PM0_IS_GPIO BALL_E16_IS_GPIO
#endif

#define BALL_D16 PAD_GPIO_PM1
#define PAD_GPIO_PM1 8
#define GPIO_PAD_8 GPIO7
#ifndef BALL_D16_IS_GPIO
#define BALL_D16_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM1_IS_GPIO
#define PAD_GPIO_PM1_IS_GPIO BALL_D16_IS_GPIO
#endif

#define BALL_B1 PAD_GPIO_PM4
#define PAD_GPIO_PM4 11
#define GPIO_PAD_11 GPIO10
#ifndef BALL_B1_IS_GPIO
#define BALL_B1_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM4_IS_GPIO
#define PAD_GPIO_PM4_IS_GPIO BALL_B1_IS_GPIO
#endif

#define BALL_D15 PAD_GPIO_PM2
#define PAD_GPIO_PM2 9
#define GPIO_PAD_9 GPIO8
#ifndef BALL_D15_IS_GPIO
#define BALL_D15_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM2_IS_GPIO
#define PAD_GPIO_PM2_IS_GPIO BALL_D15_IS_GPIO
#endif

#define BALL_C14 PAD_GPIO_PM5
#define PAD_GPIO_PM5 12
#define GPIO_PAD_12 GPIO11
#ifndef BALL_C14_IS_GPIO
#define BALL_C14_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM5_IS_GPIO
#define PAD_GPIO_PM5_IS_GPIO BALL_C14_IS_GPIO
#endif

#define BALL_D14 PAD_GPIO_PM3
#define PAD_GPIO_PM3 10
#define GPIO_PAD_10 GPIO9
#ifndef BALL_D14_IS_GPIO
#define BALL_D14_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM3_IS_GPIO
#define PAD_GPIO_PM3_IS_GPIO BALL_D14_IS_GPIO
#endif

#define BALL_D13 PAD_GPIO_PM6
#define PAD_GPIO_PM6 13
#define GPIO_PAD_13 GPIO12
#ifndef BALL_D13_IS_GPIO
#define BALL_D13_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM6_IS_GPIO
#define PAD_GPIO_PM6_IS_GPIO BALL_D13_IS_GPIO
#endif

#define BALL_C13 PAD_GPIO_PM7
#define PAD_GPIO_PM7 14
#define GPIO_PAD_14 GPIO13
#ifndef BALL_C13_IS_GPIO
#define BALL_C13_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM7_IS_GPIO
#define PAD_GPIO_PM7_IS_GPIO BALL_C13_IS_GPIO
#endif

#define BALL_A12 PAD_CEC
#define PAD_CEC 6
#define GPIO_PAD_6 GPIO5
#ifndef BALL_A12_IS_GPIO
#define BALL_A12_IS_GPIO 0
#endif
#ifndef PAD_CEC_IS_GPIO
#define PAD_CEC_IS_GPIO BALL_A12_IS_GPIO
#endif

#define BALL_T17 PAD_IRIN
#define PAD_IRIN 5
#define GPIO_PAD_5 GPIO4
#ifndef BALL_T17_IS_GPIO
#define BALL_T17_IS_GPIO 0
#endif
#ifndef PAD_IRIN_IS_GPIO
#define PAD_IRIN_IS_GPIO BALL_T17_IS_GPIO
#endif

#define BALL_E10 PAD_GPIO_PM8
#define PAD_GPIO_PM8 15
#define GPIO_PAD_15 GPIO14
#ifndef BALL_E10_IS_GPIO
#define BALL_E10_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM8_IS_GPIO
#define PAD_GPIO_PM8_IS_GPIO BALL_E10_IS_GPIO
#endif

#define BALL_B14 PAD_LED_PM0
#define PAD_LED_PM0 22
#define GPIO_PAD_22 GPIO21
#ifndef BALL_B14_IS_GPIO
#define BALL_B14_IS_GPIO 0
#endif
#ifndef PAD_LED_PM0_IS_GPIO
#define PAD_LED_PM0_IS_GPIO BALL_B14_IS_GPIO
#endif

#define BALL_C8 PAD_GPIO_PM9
#define PAD_GPIO_PM9 16
#define GPIO_PAD_16 GPIO15
#ifndef BALL_C8_IS_GPIO
#define BALL_C8_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM9_IS_GPIO
#define PAD_GPIO_PM9_IS_GPIO BALL_C8_IS_GPIO
#endif

#define BALL_A14 PAD_LED_PM1
#define PAD_LED_PM1 23
#define GPIO_PAD_23 GPIO22
#ifndef BALL_A14_IS_GPIO
#define BALL_A14_IS_GPIO 0
#endif
#ifndef PAD_LED_PM1_IS_GPIO
#define PAD_LED_PM1_IS_GPIO BALL_A14_IS_GPIO
#endif

#define BALL_A8 PAD_GPIO_PM10
#define PAD_GPIO_PM10 17
#define GPIO_PAD_17 GPIO16
#ifndef BALL_A8_IS_GPIO
#define BALL_A8_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM10_IS_GPIO
#define PAD_GPIO_PM10_IS_GPIO BALL_A8_IS_GPIO
#endif

#define BALL_A21 PAD_ET_MDIO
#define PAD_ET_MDIO 31
#define GPIO_PAD_31 GPIO30
#ifndef BALL_A21_IS_GPIO
#define BALL_A21_IS_GPIO 0
#endif
#ifndef PAD_ET_MDIO_IS_GPIO
#define PAD_ET_MDIO_IS_GPIO BALL_A21_IS_GPIO
#endif

#define BALL_C20 PAD_ET_MDC
#define PAD_ET_MDC 30
#define GPIO_PAD_30 GPIO29
#ifndef BALL_C20_IS_GPIO
#define BALL_C20_IS_GPIO 0
#endif
#ifndef PAD_ET_MDC_IS_GPIO
#define PAD_ET_MDC_IS_GPIO BALL_C20_IS_GPIO
#endif

#define BALL_A20 PAD_ET_COL
#define PAD_ET_COL 24
#define GPIO_PAD_24 GPIO23
#ifndef BALL_A20_IS_GPIO
#define BALL_A20_IS_GPIO 0
#endif
#ifndef PAD_ET_COL_IS_GPIO
#define PAD_ET_COL_IS_GPIO BALL_A20_IS_GPIO
#endif

#define BALL_B20 PAD_ET_RXD0
#define PAD_ET_RXD0 25
#define GPIO_PAD_25 GPIO24
#ifndef BALL_B20_IS_GPIO
#define BALL_B20_IS_GPIO 0
#endif
#ifndef PAD_ET_RXD0_IS_GPIO
#define PAD_ET_RXD0_IS_GPIO BALL_B20_IS_GPIO
#endif

#define BALL_C19 PAD_ET_RXD1
#define PAD_ET_RXD1 26
#define GPIO_PAD_26 GPIO25
#ifndef BALL_C19_IS_GPIO
#define BALL_C19_IS_GPIO 0
#endif
#ifndef PAD_ET_RXD1_IS_GPIO
#define PAD_ET_RXD1_IS_GPIO BALL_C19_IS_GPIO
#endif

#define BALL_B19 PAD_ET_TX_CLK
#define PAD_ET_TX_CLK 32
#define GPIO_PAD_32 GPIO31
#ifndef BALL_B19_IS_GPIO
#define BALL_B19_IS_GPIO 0
#endif
#ifndef PAD_ET_TX_CLK_IS_GPIO
#define PAD_ET_TX_CLK_IS_GPIO BALL_B19_IS_GPIO
#endif

#define BALL_C18 PAD_ET_TXD0
#define PAD_ET_TXD0 27
#define GPIO_PAD_27 GPIO26
#ifndef BALL_C18_IS_GPIO
#define BALL_C18_IS_GPIO 0
#endif
#ifndef PAD_ET_TXD0_IS_GPIO
#define PAD_ET_TXD0_IS_GPIO BALL_C18_IS_GPIO
#endif

#define BALL_B18 PAD_ET_TXD1
#define PAD_ET_TXD1 28
#define GPIO_PAD_28 GPIO27
#ifndef BALL_B18_IS_GPIO
#define BALL_B18_IS_GPIO 0
#endif
#ifndef PAD_ET_TXD1_IS_GPIO
#define PAD_ET_TXD1_IS_GPIO BALL_B18_IS_GPIO
#endif

#define BALL_A18 PAD_ET_TX_EN
#define PAD_ET_TX_EN 29
#define GPIO_PAD_29 GPIO28
#ifndef BALL_A18_IS_GPIO
#define BALL_A18_IS_GPIO 0
#endif
#ifndef PAD_ET_TX_EN_IS_GPIO
#define PAD_ET_TX_EN_IS_GPIO BALL_A18_IS_GPIO
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
#define CHIP_FAMILY_TYPE           CHIP_FAMILY_K2

#endif /* _MSD5C52_H_*/
