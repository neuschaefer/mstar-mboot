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
#ifndef _MST6110VS_H_
#define _MST6110VS_H_

#define PAD_NC 9999
#define PAD_GND 0

#define PIN_4 PAD_HOTPLUGA
#define PAD_HOTPLUGA 16
#define GPIO_PAD_16 GPIO15
#ifndef PIN_4_IS_GPIO
#define PIN_4_IS_GPIO 0
#endif 
#ifndef PAD_HOTPLUGA_IS_GPIO
#define PAD_HOTPLUGA_IS_GPIO PIN_4_IS_GPIO
#endif 

#define PIN_12 PAD_DDCDA_DA
#define PAD_DDCDA_DA 18
#define GPIO_PAD_18 GPIO17
#ifndef PIN_12_IS_GPIO
#define PIN_12_IS_GPIO 0
#endif 
#ifndef PAD_DDCDA_DA_IS_GPIO
#define PAD_DDCDA_DA_IS_GPIO PIN_12_IS_GPIO
#endif 

#define PIN_15 PAD_DDCDA_CK
#define PAD_DDCDA_CK 17
#define GPIO_PAD_17 GPIO16
#ifndef PIN_15_IS_GPIO
#define PIN_15_IS_GPIO 0
#endif 
#ifndef PAD_DDCDA_CK_IS_GPIO
#define PAD_DDCDA_CK_IS_GPIO PIN_15_IS_GPIO
#endif 

#define PIN_80 PAD_TGPIO0
#define PAD_TGPIO0 23
#define GPIO_PAD_23 GPIO22
#ifndef PIN_80_IS_GPIO
#define PIN_80_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO0_IS_GPIO
#define PAD_TGPIO0_IS_GPIO PIN_80_IS_GPIO
#endif 

#define PIN_81 PAD_TGPIO1
#define PAD_TGPIO1 24
#define GPIO_PAD_24 GPIO23
#ifndef PIN_81_IS_GPIO
#define PIN_81_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO1_IS_GPIO
#define PAD_TGPIO1_IS_GPIO PIN_81_IS_GPIO
#endif 

#define PIN_82 PAD_TGPIO2
#define PAD_TGPIO2 25
#define GPIO_PAD_25 GPIO24
#ifndef PIN_82_IS_GPIO
#define PIN_82_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO2_IS_GPIO
#define PAD_TGPIO2_IS_GPIO PIN_82_IS_GPIO
#endif 

#define PIN_83 PAD_TGPIO3
#define PAD_TGPIO3 26
#define GPIO_PAD_26 GPIO25
#ifndef PIN_83_IS_GPIO
#define PIN_83_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO3_IS_GPIO
#define PAD_TGPIO3_IS_GPIO PIN_83_IS_GPIO
#endif 

#define PIN_84 PAD_TGPIO4
#define PAD_TGPIO4 27
#define GPIO_PAD_27 GPIO26
#ifndef PIN_84_IS_GPIO
#define PIN_84_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO4_IS_GPIO
#define PAD_TGPIO4_IS_GPIO PIN_84_IS_GPIO
#endif 

#define PIN_85 PAD_TGPIO5
#define PAD_TGPIO5 28
#define GPIO_PAD_28 GPIO27
#ifndef PIN_85_IS_GPIO
#define PIN_85_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO5_IS_GPIO
#define PAD_TGPIO5_IS_GPIO PIN_85_IS_GPIO
#endif 

#define PAD_TC1_GPIO0 9999
#ifndef PAD_TC1_GPIO0_IS_GPIO
#define PAD_TC1_GPIO0_IS_GPIO 0
#endif 

#define PAD_TC1_GPIO1 9999
#ifndef PAD_TC1_GPIO1_IS_GPIO
#define PAD_TC1_GPIO1_IS_GPIO 0
#endif 

#define PAD_TC1_GPIO2 9999
#ifndef PAD_TC1_GPIO2_IS_GPIO
#define PAD_TC1_GPIO2_IS_GPIO 0
#endif 

#define PAD_TC1_GPIO3 9999
#ifndef PAD_TC1_GPIO3_IS_GPIO
#define PAD_TC1_GPIO3_IS_GPIO 0
#endif 

#define PAD_TC1_GPIO4 9999
#ifndef PAD_TC1_GPIO4_IS_GPIO
#define PAD_TC1_GPIO4_IS_GPIO 0
#endif 

#define PAD_TC1_GPIO5 9999
#ifndef PAD_TC1_GPIO5_IS_GPIO
#define PAD_TC1_GPIO5_IS_GPIO 0
#endif 

#define PIN_88 PAD_TC0_GPIO0
#define PAD_TC0_GPIO0 29
#define GPIO_PAD_29 GPIO28
#ifndef PIN_88_IS_GPIO
#define PIN_88_IS_GPIO 0
#endif 
#ifndef PAD_TC0_GPIO0_IS_GPIO
#define PAD_TC0_GPIO0_IS_GPIO PIN_88_IS_GPIO
#endif 

#define PAD_TC0_GPIO1 9999
#ifndef PAD_TC0_GPIO1_IS_GPIO
#define PAD_TC0_GPIO1_IS_GPIO 0
#endif 

#define PIN_89 PAD_TC0_GPIO2
#define PAD_TC0_GPIO2 31
#define GPIO_PAD_31 GPIO30
#ifndef PIN_89_IS_GPIO
#define PIN_89_IS_GPIO 0
#endif 
#ifndef PAD_TC0_GPIO2_IS_GPIO
#define PAD_TC0_GPIO2_IS_GPIO PIN_89_IS_GPIO
#endif 

#define PAD_TC0_GPIO3 9999
#ifndef PAD_TC0_GPIO3_IS_GPIO
#define PAD_TC0_GPIO3_IS_GPIO 0
#endif 

#define PIN_90 PAD_TC0_GPIO4
#define PAD_TC0_GPIO4 33
#define GPIO_PAD_33 GPIO32
#ifndef PIN_90_IS_GPIO
#define PIN_90_IS_GPIO 0
#endif 
#ifndef PAD_TC0_GPIO4_IS_GPIO
#define PAD_TC0_GPIO4_IS_GPIO PIN_90_IS_GPIO
#endif 

#define PAD_TC0_GPIO5 9999
#ifndef PAD_TC0_GPIO5_IS_GPIO
#define PAD_TC0_GPIO5_IS_GPIO 0
#endif 

#define PAD_TC0_GPIO6 9999
#ifndef PAD_TC0_GPIO6_IS_GPIO
#define PAD_TC0_GPIO6_IS_GPIO 0
#endif 

#define PAD_TC0_GPIO7 9999
#ifndef PAD_TC0_GPIO7_IS_GPIO
#define PAD_TC0_GPIO7_IS_GPIO 0
#endif 

#define PIN_91 PAD_TC0_GPIO8
#define PAD_TC0_GPIO8 37
#define GPIO_PAD_37 GPIO36
#ifndef PIN_91_IS_GPIO
#define PIN_91_IS_GPIO 0
#endif 
#ifndef PAD_TC0_GPIO8_IS_GPIO
#define PAD_TC0_GPIO8_IS_GPIO PIN_91_IS_GPIO
#endif 

#define PIN_92 PAD_TC0_GPIO9
#define PAD_TC0_GPIO9 38
#define GPIO_PAD_38 GPIO37
#ifndef PIN_92_IS_GPIO
#define PIN_92_IS_GPIO 0
#endif 
#ifndef PAD_TC0_GPIO9_IS_GPIO
#define PAD_TC0_GPIO9_IS_GPIO PIN_92_IS_GPIO
#endif 

#define PIN_93 PAD_TC0_GPIO10
#define PAD_TC0_GPIO10 39
#define GPIO_PAD_39 GPIO38
#ifndef PIN_93_IS_GPIO
#define PIN_93_IS_GPIO 0
#endif 
#ifndef PAD_TC0_GPIO10_IS_GPIO
#define PAD_TC0_GPIO10_IS_GPIO PIN_93_IS_GPIO
#endif 

#define PIN_94 PAD_TC1_GPIO6
#define PAD_TC1_GPIO6 46
#define GPIO_PAD_46 GPIO45
#ifndef PIN_94_IS_GPIO
#define PIN_94_IS_GPIO 0
#endif 
#ifndef PAD_TC1_GPIO6_IS_GPIO
#define PAD_TC1_GPIO6_IS_GPIO PIN_94_IS_GPIO
#endif 

#define PAD_TC1_GPIO7 9999
#ifndef PAD_TC1_GPIO7_IS_GPIO
#define PAD_TC1_GPIO7_IS_GPIO 0
#endif 

#define PIN_95 PAD_TC1_GPIO8
#define PAD_TC1_GPIO8 48
#define GPIO_PAD_48 GPIO47
#ifndef PIN_95_IS_GPIO
#define PIN_95_IS_GPIO 0
#endif 
#ifndef PAD_TC1_GPIO8_IS_GPIO
#define PAD_TC1_GPIO8_IS_GPIO PIN_95_IS_GPIO
#endif 

#define PAD_TC1_GPIO9 9999
#ifndef PAD_TC1_GPIO9_IS_GPIO
#define PAD_TC1_GPIO9_IS_GPIO 0
#endif 

#define PIN_96 PAD_TC1_GPIO10
#define PAD_TC1_GPIO10 50
#define GPIO_PAD_50 GPIO49
#ifndef PIN_96_IS_GPIO
#define PIN_96_IS_GPIO 0
#endif 
#ifndef PAD_TC1_GPIO10_IS_GPIO
#define PAD_TC1_GPIO10_IS_GPIO PIN_96_IS_GPIO
#endif 

#define PIN_98 PAD_B_ODD0
#define PAD_B_ODD0 51
#define GPIO_PAD_51 GPIO50
#ifndef PIN_98_IS_GPIO
#define PIN_98_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD0_IS_GPIO
#define PAD_B_ODD0_IS_GPIO PIN_98_IS_GPIO
#endif 

#define PIN_99 PAD_B_ODD1
#define PAD_B_ODD1 52
#define GPIO_PAD_52 GPIO51
#ifndef PIN_99_IS_GPIO
#define PIN_99_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD1_IS_GPIO
#define PAD_B_ODD1_IS_GPIO PIN_99_IS_GPIO
#endif 

#define PIN_100 PAD_B_ODD2
#define PAD_B_ODD2 53
#define GPIO_PAD_53 GPIO52
#ifndef PIN_100_IS_GPIO
#define PIN_100_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD2_IS_GPIO
#define PAD_B_ODD2_IS_GPIO PIN_100_IS_GPIO
#endif 

#define PIN_101 PAD_B_ODD3
#define PAD_B_ODD3 54
#define GPIO_PAD_54 GPIO53
#ifndef PIN_101_IS_GPIO
#define PIN_101_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD3_IS_GPIO
#define PAD_B_ODD3_IS_GPIO PIN_101_IS_GPIO
#endif 

#define PIN_102 PAD_B_ODD4
#define PAD_B_ODD4 55
#define GPIO_PAD_55 GPIO54
#ifndef PIN_102_IS_GPIO
#define PIN_102_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD4_IS_GPIO
#define PAD_B_ODD4_IS_GPIO PIN_102_IS_GPIO
#endif 

#define PIN_103 PAD_B_ODD5
#define PAD_B_ODD5 56
#define GPIO_PAD_56 GPIO55
#ifndef PIN_103_IS_GPIO
#define PIN_103_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD5_IS_GPIO
#define PAD_B_ODD5_IS_GPIO PIN_103_IS_GPIO
#endif 

#define PIN_104 PAD_B_ODD6
#define PAD_B_ODD6 57
#define GPIO_PAD_57 GPIO56
#ifndef PIN_104_IS_GPIO
#define PIN_104_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD6_IS_GPIO
#define PAD_B_ODD6_IS_GPIO PIN_104_IS_GPIO
#endif 

#define PIN_105 PAD_B_ODD7
#define PAD_B_ODD7 58
#define GPIO_PAD_58 GPIO57
#ifndef PIN_105_IS_GPIO
#define PIN_105_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD7_IS_GPIO
#define PAD_B_ODD7_IS_GPIO PIN_105_IS_GPIO
#endif 

#define PIN_106 PAD_G_ODD0
#define PAD_G_ODD0 59
#define GPIO_PAD_59 GPIO58
#ifndef PIN_106_IS_GPIO
#define PIN_106_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD0_IS_GPIO
#define PAD_G_ODD0_IS_GPIO PIN_106_IS_GPIO
#endif 

#define PIN_107 PAD_G_ODD1
#define PAD_G_ODD1 60
#define GPIO_PAD_60 GPIO59
#ifndef PIN_107_IS_GPIO
#define PIN_107_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD1_IS_GPIO
#define PAD_G_ODD1_IS_GPIO PIN_107_IS_GPIO
#endif 

#define PIN_109 PAD_G_ODD2
#define PAD_G_ODD2 61
#define GPIO_PAD_61 GPIO60
#ifndef PIN_109_IS_GPIO
#define PIN_109_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD2_IS_GPIO
#define PAD_G_ODD2_IS_GPIO PIN_109_IS_GPIO
#endif 

#define PIN_110 PAD_G_ODD3
#define PAD_G_ODD3 62
#define GPIO_PAD_62 GPIO61
#ifndef PIN_110_IS_GPIO
#define PIN_110_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD3_IS_GPIO
#define PAD_G_ODD3_IS_GPIO PIN_110_IS_GPIO
#endif 

#define PIN_111 PAD_G_ODD4
#define PAD_G_ODD4 63
#define GPIO_PAD_63 GPIO62
#ifndef PIN_111_IS_GPIO
#define PIN_111_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD4_IS_GPIO
#define PAD_G_ODD4_IS_GPIO PIN_111_IS_GPIO
#endif 

#define PIN_112 PAD_G_ODD5
#define PAD_G_ODD5 64
#define GPIO_PAD_64 GPIO63
#ifndef PIN_112_IS_GPIO
#define PIN_112_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD5_IS_GPIO
#define PAD_G_ODD5_IS_GPIO PIN_112_IS_GPIO
#endif 

#define PIN_113 PAD_G_ODD6
#define PAD_G_ODD6 65
#define GPIO_PAD_65 GPIO64
#ifndef PIN_113_IS_GPIO
#define PIN_113_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD6_IS_GPIO
#define PAD_G_ODD6_IS_GPIO PIN_113_IS_GPIO
#endif 

#define PIN_114 PAD_G_ODD7
#define PAD_G_ODD7 66
#define GPIO_PAD_66 GPIO65
#ifndef PIN_114_IS_GPIO
#define PIN_114_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD7_IS_GPIO
#define PAD_G_ODD7_IS_GPIO PIN_114_IS_GPIO
#endif 

#define PIN_115 PAD_R_ODD0
#define PAD_R_ODD0 67
#define GPIO_PAD_67 GPIO66
#ifndef PIN_115_IS_GPIO
#define PIN_115_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD0_IS_GPIO
#define PAD_R_ODD0_IS_GPIO PIN_115_IS_GPIO
#endif 

#define PIN_116 PAD_R_ODD1
#define PAD_R_ODD1 68
#define GPIO_PAD_68 GPIO67
#ifndef PIN_116_IS_GPIO
#define PIN_116_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD1_IS_GPIO
#define PAD_R_ODD1_IS_GPIO PIN_116_IS_GPIO
#endif 

#define PIN_117 PAD_R_ODD2
#define PAD_R_ODD2 69
#define GPIO_PAD_69 GPIO68
#ifndef PIN_117_IS_GPIO
#define PIN_117_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD2_IS_GPIO
#define PAD_R_ODD2_IS_GPIO PIN_117_IS_GPIO
#endif 

#define PIN_118 PAD_R_ODD3
#define PAD_R_ODD3 70
#define GPIO_PAD_70 GPIO69
#ifndef PIN_118_IS_GPIO
#define PIN_118_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD3_IS_GPIO
#define PAD_R_ODD3_IS_GPIO PIN_118_IS_GPIO
#endif 

#define PIN_119 PAD_R_ODD4
#define PAD_R_ODD4 71
#define GPIO_PAD_71 GPIO70
#ifndef PIN_119_IS_GPIO
#define PIN_119_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD4_IS_GPIO
#define PAD_R_ODD4_IS_GPIO PIN_119_IS_GPIO
#endif 

#define PIN_120 PAD_R_ODD5
#define PAD_R_ODD5 72
#define GPIO_PAD_72 GPIO71
#ifndef PIN_120_IS_GPIO
#define PIN_120_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD5_IS_GPIO
#define PAD_R_ODD5_IS_GPIO PIN_120_IS_GPIO
#endif 

#define PIN_121 PAD_R_ODD6
#define PAD_R_ODD6 73
#define GPIO_PAD_73 GPIO72
#ifndef PIN_121_IS_GPIO
#define PIN_121_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD6_IS_GPIO
#define PAD_R_ODD6_IS_GPIO PIN_121_IS_GPIO
#endif 

#define PIN_122 PAD_R_ODD7
#define PAD_R_ODD7 74
#define GPIO_PAD_74 GPIO73
#ifndef PIN_122_IS_GPIO
#define PIN_122_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD7_IS_GPIO
#define PAD_R_ODD7_IS_GPIO PIN_122_IS_GPIO
#endif 

#define PIN_126 PAD_LCK
#define PAD_LCK 75
#define GPIO_PAD_75 GPIO74
#ifndef PIN_126_IS_GPIO
#define PIN_126_IS_GPIO 0
#endif 
#ifndef PAD_LCK_IS_GPIO
#define PAD_LCK_IS_GPIO PIN_126_IS_GPIO
#endif 

#define PIN_127 PAD_LDE
#define PAD_LDE 76
#define GPIO_PAD_76 GPIO75
#ifndef PIN_127_IS_GPIO
#define PIN_127_IS_GPIO 0
#endif 
#ifndef PAD_LDE_IS_GPIO
#define PAD_LDE_IS_GPIO PIN_127_IS_GPIO
#endif 

#define PIN_128 PAD_LHSYNC
#define PAD_LHSYNC 77
#define GPIO_PAD_77 GPIO76
#ifndef PIN_128_IS_GPIO
#define PIN_128_IS_GPIO 0
#endif 
#ifndef PAD_LHSYNC_IS_GPIO
#define PAD_LHSYNC_IS_GPIO PIN_128_IS_GPIO
#endif 

#define PIN_129 PAD_LVSYNC
#define PAD_LVSYNC 78
#define GPIO_PAD_78 GPIO77
#ifndef PIN_129_IS_GPIO
#define PIN_129_IS_GPIO 0
#endif 
#ifndef PAD_LVSYNC_IS_GPIO
#define PAD_LVSYNC_IS_GPIO PIN_129_IS_GPIO
#endif 

#define PIN_131 PAD_PWM0
#define PAD_PWM0 21
#define GPIO_PAD_21 GPIO20
#ifndef PIN_131_IS_GPIO
#define PIN_131_IS_GPIO 0
#endif 
#ifndef PAD_PWM0_IS_GPIO
#define PAD_PWM0_IS_GPIO PIN_131_IS_GPIO
#endif 

#define PIN_132 PAD_PWM1
#define PAD_PWM1 22
#define GPIO_PAD_22 GPIO21
#ifndef PIN_132_IS_GPIO
#define PIN_132_IS_GPIO 0
#endif 
#ifndef PAD_PWM1_IS_GPIO
#define PAD_PWM1_IS_GPIO PIN_132_IS_GPIO
#endif 

#define PIN_192 PAD_DDCR_DA
#define PAD_DDCR_DA 19
#define GPIO_PAD_19 GPIO18
#ifndef PIN_192_IS_GPIO
#define PIN_192_IS_GPIO 0
#endif 
#ifndef PAD_DDCR_DA_IS_GPIO
#define PAD_DDCR_DA_IS_GPIO PIN_192_IS_GPIO
#endif 

#define PIN_194 PAD_DDCR_CK
#define PAD_DDCR_CK 20
#define GPIO_PAD_20 GPIO19
#ifndef PIN_194_IS_GPIO
#define PIN_194_IS_GPIO 0
#endif 
#ifndef PAD_DDCR_CK_IS_GPIO
#define PAD_DDCR_CK_IS_GPIO PIN_194_IS_GPIO
#endif 

#define PIN_203 PAD_PM_SPI_CK
#define PAD_PM_SPI_CK 2
#define GPIO_PAD_2 GPIO1
#ifndef PIN_203_IS_GPIO
#define PIN_203_IS_GPIO 0
#endif 
#ifndef PAD_PM_SPI_CK_IS_GPIO
#define PAD_PM_SPI_CK_IS_GPIO PIN_203_IS_GPIO
#endif 

#define PIN_204 PAD_PM_SPI_DI
#define PAD_PM_SPI_DI 3
#define GPIO_PAD_3 GPIO2
#ifndef PIN_204_IS_GPIO
#define PIN_204_IS_GPIO 0
#endif 
#ifndef PAD_PM_SPI_DI_IS_GPIO
#define PAD_PM_SPI_DI_IS_GPIO PIN_204_IS_GPIO
#endif 

#define PIN_205 PAD_PM_SPI_DO
#define PAD_PM_SPI_DO 4
#define GPIO_PAD_4 GPIO3
#ifndef PIN_205_IS_GPIO
#define PIN_205_IS_GPIO 0
#endif 
#ifndef PAD_PM_SPI_DO_IS_GPIO
#define PAD_PM_SPI_DO_IS_GPIO PIN_205_IS_GPIO
#endif 

#define PIN_206 PAD_PM_SPI_CZ
#define PAD_PM_SPI_CZ 1
#define GPIO_PAD_1 GPIO0
#ifndef PIN_206_IS_GPIO
#define PIN_206_IS_GPIO 0
#endif 
#ifndef PAD_PM_SPI_CZ_IS_GPIO
#define PAD_PM_SPI_CZ_IS_GPIO PIN_206_IS_GPIO
#endif 

#define PIN_207 PAD_SAR0
#define PAD_SAR0 12
#define GPIO_PAD_12 GPIO11
#ifndef PIN_207_IS_GPIO
#define PIN_207_IS_GPIO 0
#endif 
#ifndef PAD_SAR0_IS_GPIO
#define PAD_SAR0_IS_GPIO PIN_207_IS_GPIO
#endif 

#define PIN_208 PAD_SAR1
#define PAD_SAR1 13
#define GPIO_PAD_13 GPIO12
#ifndef PIN_208_IS_GPIO
#define PIN_208_IS_GPIO 0
#endif 
#ifndef PAD_SAR1_IS_GPIO
#define PAD_SAR1_IS_GPIO PIN_208_IS_GPIO
#endif 

#define PIN_209 PAD_SAR2
#define PAD_SAR2 14
#define GPIO_PAD_14 GPIO13
#ifndef PIN_209_IS_GPIO
#define PIN_209_IS_GPIO 0
#endif 
#ifndef PAD_SAR2_IS_GPIO
#define PAD_SAR2_IS_GPIO PIN_209_IS_GPIO
#endif 

#define PAD_SAR3 9999
#ifndef PAD_SAR3_IS_GPIO
#define PAD_SAR3_IS_GPIO 0
#endif 

#define PIN_210 PAD_PMGPIO
#define PAD_PMGPIO 11
#define GPIO_PAD_11 GPIO10
#ifndef PIN_210_IS_GPIO
#define PIN_210_IS_GPIO 0
#endif 
#ifndef PAD_PMGPIO_IS_GPIO
#define PAD_PMGPIO_IS_GPIO PIN_210_IS_GPIO
#endif 

#define PIN_213 PAD_GPIO_PM1
#define PAD_GPIO_PM1 7
#define GPIO_PAD_7 GPIO6
#ifndef PIN_213_IS_GPIO
#define PIN_213_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM1_IS_GPIO
#define PAD_GPIO_PM1_IS_GPIO PIN_213_IS_GPIO
#endif 

#define PIN_214 PAD_GPIO_PM4
#define PAD_GPIO_PM4 8
#define GPIO_PAD_8 GPIO7
#ifndef PIN_214_IS_GPIO
#define PIN_214_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM4_IS_GPIO
#define PAD_GPIO_PM4_IS_GPIO PIN_214_IS_GPIO
#endif 

#define PIN_215 PAD_GPIO_PM5
#define PAD_GPIO_PM5 9
#define GPIO_PAD_9 GPIO8
#ifndef PIN_215_IS_GPIO
#define PIN_215_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM5_IS_GPIO
#define PAD_GPIO_PM5_IS_GPIO PIN_215_IS_GPIO
#endif 

#define PIN_216 PAD_GPIO_PM6
#define PAD_GPIO_PM6 10
#define GPIO_PAD_10 GPIO9
#ifndef PIN_216_IS_GPIO
#define PIN_216_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM6_IS_GPIO
#define PAD_GPIO_PM6_IS_GPIO PIN_216_IS_GPIO
#endif 

#define PIN_1 PAD_IRIN
#define PAD_IRIN 5
#define GPIO_PAD_5 GPIO4
#ifndef PIN_1_IS_GPIO
#define PIN_1_IS_GPIO 0
#endif 
#ifndef PAD_IRIN_IS_GPIO
#define PAD_IRIN_IS_GPIO PIN_1_IS_GPIO
#endif 

#define PIN_2 PAD_CEC
#define PAD_CEC 6
#define GPIO_PAD_6 GPIO5
#ifndef PIN_2_IS_GPIO
#define PIN_2_IS_GPIO 0
#endif 
#ifndef PAD_CEC_IS_GPIO
#define PAD_CEC_IS_GPIO PIN_2_IS_GPIO
#endif 


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
#define CHIP_HAS_I2S_IN            1 
#define CHIP_HAS_I2S_OUT           1
#define CHIP_HAS_SPDIF_IN          0 
#define CHIP_HAS_SPDIF_OUT         1
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
#define CHIP_FAMILY_TYPE           CHIP_FAMILY_M10

#endif /* _MST6110VS_H_*/
