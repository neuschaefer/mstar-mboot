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
#ifndef _MST6M182VG_H_
#define _MST6M182VG_H_

#define PAD_NC 9999
#define PAD_GND 0

#define BALL_D4 PAD_HOTPLUGA
#define PAD_HOTPLUGA 16
#define GPIO_PAD_16 GPIO15
#ifndef BALL_D4_IS_GPIO
#define BALL_D4_IS_GPIO 0
#endif 
#ifndef PAD_HOTPLUGA_IS_GPIO
#define PAD_HOTPLUGA_IS_GPIO BALL_D4_IS_GPIO
#endif 

#define BALL_D3 PAD_DDCDA_DA
#define PAD_DDCDA_DA 18
#define GPIO_PAD_18 GPIO17
#ifndef BALL_D3_IS_GPIO
#define BALL_D3_IS_GPIO 0
#endif 
#ifndef PAD_DDCDA_DA_IS_GPIO
#define PAD_DDCDA_DA_IS_GPIO BALL_D3_IS_GPIO
#endif 

#define BALL_D1 PAD_DDCDA_CK
#define PAD_DDCDA_CK 17
#define GPIO_PAD_17 GPIO16
#ifndef BALL_D1_IS_GPIO
#define BALL_D1_IS_GPIO 0
#endif 
#ifndef PAD_DDCDA_CK_IS_GPIO
#define PAD_DDCDA_CK_IS_GPIO BALL_D1_IS_GPIO
#endif 

#define BALL_T8 PAD_TGPIO0
#define PAD_TGPIO0 23
#define GPIO_PAD_23 GPIO22
#ifndef BALL_T8_IS_GPIO
#define BALL_T8_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO0_IS_GPIO
#define PAD_TGPIO0_IS_GPIO BALL_T8_IS_GPIO
#endif 

#define BALL_P8 PAD_TGPIO1
#define PAD_TGPIO1 24
#define GPIO_PAD_24 GPIO23
#ifndef BALL_P8_IS_GPIO
#define BALL_P8_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO1_IS_GPIO
#define PAD_TGPIO1_IS_GPIO BALL_P8_IS_GPIO
#endif 

#define BALL_R8 PAD_TGPIO2
#define PAD_TGPIO2 25
#define GPIO_PAD_25 GPIO24
#ifndef BALL_R8_IS_GPIO
#define BALL_R8_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO2_IS_GPIO
#define PAD_TGPIO2_IS_GPIO BALL_R8_IS_GPIO
#endif 

#define BALL_R9 PAD_TGPIO3
#define PAD_TGPIO3 26
#define GPIO_PAD_26 GPIO25
#ifndef BALL_R9_IS_GPIO
#define BALL_R9_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO3_IS_GPIO
#define PAD_TGPIO3_IS_GPIO BALL_R9_IS_GPIO
#endif 

#define BALL_P9 PAD_TGPIO4
#define PAD_TGPIO4 27
#define GPIO_PAD_27 GPIO26
#ifndef BALL_P9_IS_GPIO
#define BALL_P9_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO4_IS_GPIO
#define PAD_TGPIO4_IS_GPIO BALL_P9_IS_GPIO
#endif 

#define BALL_T9 PAD_TGPIO5
#define PAD_TGPIO5 28
#define GPIO_PAD_28 GPIO27
#ifndef BALL_T9_IS_GPIO
#define BALL_T9_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO5_IS_GPIO
#define PAD_TGPIO5_IS_GPIO BALL_T9_IS_GPIO
#endif 

#define BALL_G16 PAD_TC1_GPIO0
#define PAD_TC1_GPIO0 40
#define GPIO_PAD_40 GPIO39
#ifndef BALL_G16_IS_GPIO
#define BALL_G16_IS_GPIO 0
#endif 
#ifndef PAD_TC1_GPIO0_IS_GPIO
#define PAD_TC1_GPIO0_IS_GPIO BALL_G16_IS_GPIO
#endif 

#define BALL_H14 PAD_TC1_GPIO1
#define PAD_TC1_GPIO1 41
#define GPIO_PAD_41 GPIO40
#ifndef BALL_H14_IS_GPIO
#define BALL_H14_IS_GPIO 0
#endif 
#ifndef PAD_TC1_GPIO1_IS_GPIO
#define PAD_TC1_GPIO1_IS_GPIO BALL_H14_IS_GPIO
#endif 

#define BALL_H15 PAD_TC1_GPIO2
#define PAD_TC1_GPIO2 42
#define GPIO_PAD_42 GPIO41
#ifndef BALL_H15_IS_GPIO
#define BALL_H15_IS_GPIO 0
#endif 
#ifndef PAD_TC1_GPIO2_IS_GPIO
#define PAD_TC1_GPIO2_IS_GPIO BALL_H15_IS_GPIO
#endif 

#define BALL_H16 PAD_TC1_GPIO3
#define PAD_TC1_GPIO3 43
#define GPIO_PAD_43 GPIO42
#ifndef BALL_H16_IS_GPIO
#define BALL_H16_IS_GPIO 0
#endif 
#ifndef PAD_TC1_GPIO3_IS_GPIO
#define PAD_TC1_GPIO3_IS_GPIO BALL_H16_IS_GPIO
#endif 

#define BALL_J14 PAD_TC1_GPIO4
#define PAD_TC1_GPIO4 44
#define GPIO_PAD_44 GPIO43
#ifndef BALL_J14_IS_GPIO
#define BALL_J14_IS_GPIO 0
#endif 
#ifndef PAD_TC1_GPIO4_IS_GPIO
#define PAD_TC1_GPIO4_IS_GPIO BALL_J14_IS_GPIO
#endif 

#define BALL_J15 PAD_TC1_GPIO5
#define PAD_TC1_GPIO5 45
#define GPIO_PAD_45 GPIO44
#ifndef BALL_J15_IS_GPIO
#define BALL_J15_IS_GPIO 0
#endif 
#ifndef PAD_TC1_GPIO5_IS_GPIO
#define PAD_TC1_GPIO5_IS_GPIO BALL_J15_IS_GPIO
#endif 

#define BALL_D14 PAD_TC0_GPIO0
#define PAD_TC0_GPIO0 29
#define GPIO_PAD_29 GPIO28
#ifndef BALL_D14_IS_GPIO
#define BALL_D14_IS_GPIO 0
#endif 
#ifndef PAD_TC0_GPIO0_IS_GPIO
#define PAD_TC0_GPIO0_IS_GPIO BALL_D14_IS_GPIO
#endif 

#define BALL_D15 PAD_TC0_GPIO1
#define PAD_TC0_GPIO1 30
#define GPIO_PAD_30 GPIO29
#ifndef BALL_D15_IS_GPIO
#define BALL_D15_IS_GPIO 0
#endif 
#ifndef PAD_TC0_GPIO1_IS_GPIO
#define PAD_TC0_GPIO1_IS_GPIO BALL_D15_IS_GPIO
#endif 

#define BALL_D16 PAD_TC0_GPIO2
#define PAD_TC0_GPIO2 31
#define GPIO_PAD_31 GPIO30
#ifndef BALL_D16_IS_GPIO
#define BALL_D16_IS_GPIO 0
#endif 
#ifndef PAD_TC0_GPIO2_IS_GPIO
#define PAD_TC0_GPIO2_IS_GPIO BALL_D16_IS_GPIO
#endif 

#define BALL_E14 PAD_TC0_GPIO3
#define PAD_TC0_GPIO3 32
#define GPIO_PAD_32 GPIO31
#ifndef BALL_E14_IS_GPIO
#define BALL_E14_IS_GPIO 0
#endif 
#ifndef PAD_TC0_GPIO3_IS_GPIO
#define PAD_TC0_GPIO3_IS_GPIO BALL_E14_IS_GPIO
#endif 

#define BALL_E15 PAD_TC0_GPIO4
#define PAD_TC0_GPIO4 33
#define GPIO_PAD_33 GPIO32
#ifndef BALL_E15_IS_GPIO
#define BALL_E15_IS_GPIO 0
#endif 
#ifndef PAD_TC0_GPIO4_IS_GPIO
#define PAD_TC0_GPIO4_IS_GPIO BALL_E15_IS_GPIO
#endif 

#define BALL_E16 PAD_TC0_GPIO5
#define PAD_TC0_GPIO5 34
#define GPIO_PAD_34 GPIO33
#ifndef BALL_E16_IS_GPIO
#define BALL_E16_IS_GPIO 0
#endif 
#ifndef PAD_TC0_GPIO5_IS_GPIO
#define PAD_TC0_GPIO5_IS_GPIO BALL_E16_IS_GPIO
#endif 

#define BALL_F14 PAD_TC0_GPIO6
#define PAD_TC0_GPIO6 35
#define GPIO_PAD_35 GPIO34
#ifndef BALL_F14_IS_GPIO
#define BALL_F14_IS_GPIO 0
#endif 
#ifndef PAD_TC0_GPIO6_IS_GPIO
#define PAD_TC0_GPIO6_IS_GPIO BALL_F14_IS_GPIO
#endif 

#define BALL_F15 PAD_TC0_GPIO7
#define PAD_TC0_GPIO7 36
#define GPIO_PAD_36 GPIO35
#ifndef BALL_F15_IS_GPIO
#define BALL_F15_IS_GPIO 0
#endif 
#ifndef PAD_TC0_GPIO7_IS_GPIO
#define PAD_TC0_GPIO7_IS_GPIO BALL_F15_IS_GPIO
#endif 

#define BALL_F16 PAD_TC0_GPIO8
#define PAD_TC0_GPIO8 37
#define GPIO_PAD_37 GPIO36
#ifndef BALL_F16_IS_GPIO
#define BALL_F16_IS_GPIO 0
#endif 
#ifndef PAD_TC0_GPIO8_IS_GPIO
#define PAD_TC0_GPIO8_IS_GPIO BALL_F16_IS_GPIO
#endif 

#define BALL_G14 PAD_TC0_GPIO9
#define PAD_TC0_GPIO9 38
#define GPIO_PAD_38 GPIO37
#ifndef BALL_G14_IS_GPIO
#define BALL_G14_IS_GPIO 0
#endif 
#ifndef PAD_TC0_GPIO9_IS_GPIO
#define PAD_TC0_GPIO9_IS_GPIO BALL_G14_IS_GPIO
#endif 

#define BALL_G15 PAD_TC0_GPIO10
#define PAD_TC0_GPIO10 39
#define GPIO_PAD_39 GPIO38
#ifndef BALL_G15_IS_GPIO
#define BALL_G15_IS_GPIO 0
#endif 
#ifndef PAD_TC0_GPIO10_IS_GPIO
#define PAD_TC0_GPIO10_IS_GPIO BALL_G15_IS_GPIO
#endif 

#define BALL_J16 PAD_TC1_GPIO6
#define PAD_TC1_GPIO6 46
#define GPIO_PAD_46 GPIO45
#ifndef BALL_J16_IS_GPIO
#define BALL_J16_IS_GPIO 0
#endif 
#ifndef PAD_TC1_GPIO6_IS_GPIO
#define PAD_TC1_GPIO6_IS_GPIO BALL_J16_IS_GPIO
#endif 

#define BALL_K14 PAD_TC1_GPIO7
#define PAD_TC1_GPIO7 47
#define GPIO_PAD_47 GPIO46
#ifndef BALL_K14_IS_GPIO
#define BALL_K14_IS_GPIO 0
#endif 
#ifndef PAD_TC1_GPIO7_IS_GPIO
#define PAD_TC1_GPIO7_IS_GPIO BALL_K14_IS_GPIO
#endif 

#define BALL_K15 PAD_TC1_GPIO8
#define PAD_TC1_GPIO8 48
#define GPIO_PAD_48 GPIO47
#ifndef BALL_K15_IS_GPIO
#define BALL_K15_IS_GPIO 0
#endif 
#ifndef PAD_TC1_GPIO8_IS_GPIO
#define PAD_TC1_GPIO8_IS_GPIO BALL_K15_IS_GPIO
#endif 

#define BALL_K16 PAD_TC1_GPIO9
#define PAD_TC1_GPIO9 49
#define GPIO_PAD_49 GPIO48
#ifndef BALL_K16_IS_GPIO
#define BALL_K16_IS_GPIO 0
#endif 
#ifndef PAD_TC1_GPIO9_IS_GPIO
#define PAD_TC1_GPIO9_IS_GPIO BALL_K16_IS_GPIO
#endif 

#define BALL_L14 PAD_TC1_GPIO10
#define PAD_TC1_GPIO10 50
#define GPIO_PAD_50 GPIO49
#ifndef BALL_L14_IS_GPIO
#define BALL_L14_IS_GPIO 0
#endif 
#ifndef PAD_TC1_GPIO10_IS_GPIO
#define PAD_TC1_GPIO10_IS_GPIO BALL_L14_IS_GPIO
#endif 

#define BALL_P10 PAD_B_ODD0
#define PAD_B_ODD0 51
#define GPIO_PAD_51 GPIO50
#ifndef BALL_P10_IS_GPIO
#define BALL_P10_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD0_IS_GPIO
#define PAD_B_ODD0_IS_GPIO BALL_P10_IS_GPIO
#endif 

#define BALL_R10 PAD_B_ODD1
#define PAD_B_ODD1 52
#define GPIO_PAD_52 GPIO51
#ifndef BALL_R10_IS_GPIO
#define BALL_R10_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD1_IS_GPIO
#define PAD_B_ODD1_IS_GPIO BALL_R10_IS_GPIO
#endif 

#define BALL_P11 PAD_B_ODD2
#define PAD_B_ODD2 53
#define GPIO_PAD_53 GPIO52
#ifndef BALL_P11_IS_GPIO
#define BALL_P11_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD2_IS_GPIO
#define PAD_B_ODD2_IS_GPIO BALL_P11_IS_GPIO
#endif 

#define BALL_R11 PAD_B_ODD3
#define PAD_B_ODD3 54
#define GPIO_PAD_54 GPIO53
#ifndef BALL_R11_IS_GPIO
#define BALL_R11_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD3_IS_GPIO
#define PAD_B_ODD3_IS_GPIO BALL_R11_IS_GPIO
#endif 

#define BALL_T11 PAD_B_ODD4
#define PAD_B_ODD4 55
#define GPIO_PAD_55 GPIO54
#ifndef BALL_T11_IS_GPIO
#define BALL_T11_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD4_IS_GPIO
#define PAD_B_ODD4_IS_GPIO BALL_T11_IS_GPIO
#endif 

#define BALL_P12 PAD_B_ODD5
#define PAD_B_ODD5 56
#define GPIO_PAD_56 GPIO55
#ifndef BALL_P12_IS_GPIO
#define BALL_P12_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD5_IS_GPIO
#define PAD_B_ODD5_IS_GPIO BALL_P12_IS_GPIO
#endif 

#define BALL_T12 PAD_B_ODD6
#define PAD_B_ODD6 57
#define GPIO_PAD_57 GPIO56
#ifndef BALL_T12_IS_GPIO
#define BALL_T12_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD6_IS_GPIO
#define PAD_B_ODD6_IS_GPIO BALL_T12_IS_GPIO
#endif 

#define BALL_R12 PAD_B_ODD7
#define PAD_B_ODD7 58
#define GPIO_PAD_58 GPIO57
#ifndef BALL_R12_IS_GPIO
#define BALL_R12_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD7_IS_GPIO
#define PAD_B_ODD7_IS_GPIO BALL_R12_IS_GPIO
#endif 

#define BALL_P13 PAD_G_ODD0
#define PAD_G_ODD0 59
#define GPIO_PAD_59 GPIO58
#ifndef BALL_P13_IS_GPIO
#define BALL_P13_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD0_IS_GPIO
#define PAD_G_ODD0_IS_GPIO BALL_P13_IS_GPIO
#endif 

#define BALL_R13 PAD_G_ODD1
#define PAD_G_ODD1 60
#define GPIO_PAD_60 GPIO59
#ifndef BALL_R13_IS_GPIO
#define BALL_R13_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD1_IS_GPIO
#define PAD_G_ODD1_IS_GPIO BALL_R13_IS_GPIO
#endif 

#define BALL_P14 PAD_G_ODD2
#define PAD_G_ODD2 61
#define GPIO_PAD_61 GPIO60
#ifndef BALL_P14_IS_GPIO
#define BALL_P14_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD2_IS_GPIO
#define PAD_G_ODD2_IS_GPIO BALL_P14_IS_GPIO
#endif 

#define BALL_R14 PAD_G_ODD3
#define PAD_G_ODD3 62
#define GPIO_PAD_62 GPIO61
#ifndef BALL_R14_IS_GPIO
#define BALL_R14_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD3_IS_GPIO
#define PAD_G_ODD3_IS_GPIO BALL_R14_IS_GPIO
#endif 

#define BALL_T14 PAD_G_ODD4
#define PAD_G_ODD4 63
#define GPIO_PAD_63 GPIO62
#ifndef BALL_T14_IS_GPIO
#define BALL_T14_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD4_IS_GPIO
#define PAD_G_ODD4_IS_GPIO BALL_T14_IS_GPIO
#endif 

#define BALL_T15 PAD_G_ODD5
#define PAD_G_ODD5 64
#define GPIO_PAD_64 GPIO63
#ifndef BALL_T15_IS_GPIO
#define BALL_T15_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD5_IS_GPIO
#define PAD_G_ODD5_IS_GPIO BALL_T15_IS_GPIO
#endif 

#define BALL_R15 PAD_G_ODD6
#define PAD_G_ODD6 65
#define GPIO_PAD_65 GPIO64
#ifndef BALL_R15_IS_GPIO
#define BALL_R15_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD6_IS_GPIO
#define PAD_G_ODD6_IS_GPIO BALL_R15_IS_GPIO
#endif 

#define BALL_R16 PAD_G_ODD7
#define PAD_G_ODD7 66
#define GPIO_PAD_66 GPIO65
#ifndef BALL_R16_IS_GPIO
#define BALL_R16_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD7_IS_GPIO
#define PAD_G_ODD7_IS_GPIO BALL_R16_IS_GPIO
#endif 

#define BALL_P15 PAD_R_ODD0
#define PAD_R_ODD0 67
#define GPIO_PAD_67 GPIO66
#ifndef BALL_P15_IS_GPIO
#define BALL_P15_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD0_IS_GPIO
#define PAD_R_ODD0_IS_GPIO BALL_P15_IS_GPIO
#endif 

#define BALL_P16 PAD_R_ODD1
#define PAD_R_ODD1 68
#define GPIO_PAD_68 GPIO67
#ifndef BALL_P16_IS_GPIO
#define BALL_P16_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD1_IS_GPIO
#define PAD_R_ODD1_IS_GPIO BALL_P16_IS_GPIO
#endif 

#define BALL_N14 PAD_R_ODD2
#define PAD_R_ODD2 69
#define GPIO_PAD_69 GPIO68
#ifndef BALL_N14_IS_GPIO
#define BALL_N14_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD2_IS_GPIO
#define PAD_R_ODD2_IS_GPIO BALL_N14_IS_GPIO
#endif 

#define BALL_N15 PAD_R_ODD3
#define PAD_R_ODD3 70
#define GPIO_PAD_70 GPIO69
#ifndef BALL_N15_IS_GPIO
#define BALL_N15_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD3_IS_GPIO
#define PAD_R_ODD3_IS_GPIO BALL_N15_IS_GPIO
#endif 

#define BALL_M14 PAD_R_ODD4
#define PAD_R_ODD4 71
#define GPIO_PAD_71 GPIO70
#ifndef BALL_M14_IS_GPIO
#define BALL_M14_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD4_IS_GPIO
#define PAD_R_ODD4_IS_GPIO BALL_M14_IS_GPIO
#endif 

#define BALL_M15 PAD_R_ODD5
#define PAD_R_ODD5 72
#define GPIO_PAD_72 GPIO71
#ifndef BALL_M15_IS_GPIO
#define BALL_M15_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD5_IS_GPIO
#define PAD_R_ODD5_IS_GPIO BALL_M15_IS_GPIO
#endif 

#define BALL_M16 PAD_R_ODD6
#define PAD_R_ODD6 73
#define GPIO_PAD_73 GPIO72
#ifndef BALL_M16_IS_GPIO
#define BALL_M16_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD6_IS_GPIO
#define PAD_R_ODD6_IS_GPIO BALL_M16_IS_GPIO
#endif 

#define BALL_L16 PAD_R_ODD7
#define PAD_R_ODD7 74
#define GPIO_PAD_74 GPIO73
#ifndef BALL_L16_IS_GPIO
#define BALL_L16_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD7_IS_GPIO
#define PAD_R_ODD7_IS_GPIO BALL_L16_IS_GPIO
#endif 

#define BALL_N10 PAD_LCK
#define PAD_LCK 75
#define GPIO_PAD_75 GPIO74
#ifndef BALL_N10_IS_GPIO
#define BALL_N10_IS_GPIO 0
#endif 
#ifndef PAD_LCK_IS_GPIO
#define PAD_LCK_IS_GPIO BALL_N10_IS_GPIO
#endif 

#define BALL_N11 PAD_LDE
#define PAD_LDE 76
#define GPIO_PAD_76 GPIO75
#ifndef BALL_N11_IS_GPIO
#define BALL_N11_IS_GPIO 0
#endif 
#ifndef PAD_LDE_IS_GPIO
#define PAD_LDE_IS_GPIO BALL_N11_IS_GPIO
#endif 

#define BALL_N12 PAD_LHSYNC
#define PAD_LHSYNC 77
#define GPIO_PAD_77 GPIO76
#ifndef BALL_N12_IS_GPIO
#define BALL_N12_IS_GPIO 0
#endif 
#ifndef PAD_LHSYNC_IS_GPIO
#define PAD_LHSYNC_IS_GPIO BALL_N12_IS_GPIO
#endif 

#define BALL_N13 PAD_LVSYNC
#define PAD_LVSYNC 78
#define GPIO_PAD_78 GPIO77
#ifndef BALL_N13_IS_GPIO
#define BALL_N13_IS_GPIO 0
#endif 
#ifndef PAD_LVSYNC_IS_GPIO
#define PAD_LVSYNC_IS_GPIO BALL_N13_IS_GPIO
#endif 

#define BALL_A12 PAD_PWM0
#define PAD_PWM0 21
#define GPIO_PAD_21 GPIO20
#ifndef BALL_A12_IS_GPIO
#define BALL_A12_IS_GPIO 0
#endif 
#ifndef PAD_PWM0_IS_GPIO
#define PAD_PWM0_IS_GPIO BALL_A12_IS_GPIO
#endif 

#define BALL_B12 PAD_PWM1
#define PAD_PWM1 22
#define GPIO_PAD_22 GPIO21
#ifndef BALL_B12_IS_GPIO
#define BALL_B12_IS_GPIO 0
#endif 
#ifndef PAD_PWM1_IS_GPIO
#define PAD_PWM1_IS_GPIO BALL_B12_IS_GPIO
#endif 

#define BALL_C14 PAD_DDCR_DA
#define PAD_DDCR_DA 19
#define GPIO_PAD_19 GPIO18
#ifndef BALL_C14_IS_GPIO
#define BALL_C14_IS_GPIO 0
#endif 
#ifndef PAD_DDCR_DA_IS_GPIO
#define PAD_DDCR_DA_IS_GPIO BALL_C14_IS_GPIO
#endif 

#define BALL_B14 PAD_DDCR_CK
#define PAD_DDCR_CK 20
#define GPIO_PAD_20 GPIO19
#ifndef BALL_B14_IS_GPIO
#define BALL_B14_IS_GPIO 0
#endif 
#ifndef PAD_DDCR_CK_IS_GPIO
#define PAD_DDCR_CK_IS_GPIO BALL_B14_IS_GPIO
#endif 

#define BALL_C15 PAD_PM_SPI_CK
#define PAD_PM_SPI_CK 2
#define GPIO_PAD_2 GPIO1
#ifndef BALL_C15_IS_GPIO
#define BALL_C15_IS_GPIO 0
#endif 
#ifndef PAD_PM_SPI_CK_IS_GPIO
#define PAD_PM_SPI_CK_IS_GPIO BALL_C15_IS_GPIO
#endif 

#define BALL_C16 PAD_PM_SPI_DI
#define PAD_PM_SPI_DI 3
#define GPIO_PAD_3 GPIO2
#ifndef BALL_C16_IS_GPIO
#define BALL_C16_IS_GPIO 0
#endif 
#ifndef PAD_PM_SPI_DI_IS_GPIO
#define PAD_PM_SPI_DI_IS_GPIO BALL_C16_IS_GPIO
#endif 

#define BALL_B16 PAD_PM_SPI_DO
#define PAD_PM_SPI_DO 4
#define GPIO_PAD_4 GPIO3
#ifndef BALL_B16_IS_GPIO
#define BALL_B16_IS_GPIO 0
#endif 
#ifndef PAD_PM_SPI_DO_IS_GPIO
#define PAD_PM_SPI_DO_IS_GPIO BALL_B16_IS_GPIO
#endif 

#define BALL_B15 PAD_PM_SPI_CZ
#define PAD_PM_SPI_CZ 1
#define GPIO_PAD_1 GPIO0
#ifndef BALL_B15_IS_GPIO
#define BALL_B15_IS_GPIO 0
#endif 
#ifndef PAD_PM_SPI_CZ_IS_GPIO
#define PAD_PM_SPI_CZ_IS_GPIO BALL_B15_IS_GPIO
#endif 

#define BALL_B11 PAD_SAR0
#define PAD_SAR0 12
#define GPIO_PAD_12 GPIO11
#ifndef BALL_B11_IS_GPIO
#define BALL_B11_IS_GPIO 0
#endif 
#ifndef PAD_SAR0_IS_GPIO
#define PAD_SAR0_IS_GPIO BALL_B11_IS_GPIO
#endif 

#define BALL_C11 PAD_SAR1
#define PAD_SAR1 13
#define GPIO_PAD_13 GPIO12
#ifndef BALL_C11_IS_GPIO
#define BALL_C11_IS_GPIO 0
#endif 
#ifndef PAD_SAR1_IS_GPIO
#define PAD_SAR1_IS_GPIO BALL_C11_IS_GPIO
#endif 

#define BALL_C10 PAD_SAR2
#define PAD_SAR2 14
#define GPIO_PAD_14 GPIO13
#ifndef BALL_C10_IS_GPIO
#define BALL_C10_IS_GPIO 0
#endif 
#ifndef PAD_SAR2_IS_GPIO
#define PAD_SAR2_IS_GPIO BALL_C10_IS_GPIO
#endif 

#define BALL_L15 PAD_SAR3
#define PAD_SAR3 15
#define GPIO_PAD_15 GPIO14
#ifndef BALL_L15_IS_GPIO
#define BALL_L15_IS_GPIO 0
#endif 
#ifndef PAD_SAR3_IS_GPIO
#define PAD_SAR3_IS_GPIO BALL_L15_IS_GPIO
#endif 

#define BALL_C12 PAD_PMGPIO
#define PAD_PMGPIO 11
#define GPIO_PAD_11 GPIO10
#ifndef BALL_C12_IS_GPIO
#define BALL_C12_IS_GPIO 0
#endif 
#ifndef PAD_PMGPIO_IS_GPIO
#define PAD_PMGPIO_IS_GPIO BALL_C12_IS_GPIO
#endif 

#define BALL_A11 PAD_GPIO_PM1
#define PAD_GPIO_PM1 7
#define GPIO_PAD_7 GPIO6
#ifndef BALL_A11_IS_GPIO
#define BALL_A11_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM1_IS_GPIO
#define PAD_GPIO_PM1_IS_GPIO BALL_A11_IS_GPIO
#endif 

#define BALL_A10 PAD_GPIO_PM4
#define PAD_GPIO_PM4 8
#define GPIO_PAD_8 GPIO7
#ifndef BALL_A10_IS_GPIO
#define BALL_A10_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM4_IS_GPIO
#define PAD_GPIO_PM4_IS_GPIO BALL_A10_IS_GPIO
#endif 

#define BALL_B10 PAD_GPIO_PM5
#define PAD_GPIO_PM5 9
#define GPIO_PAD_9 GPIO8
#ifndef BALL_B10_IS_GPIO
#define BALL_B10_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM5_IS_GPIO
#define PAD_GPIO_PM5_IS_GPIO BALL_B10_IS_GPIO
#endif 

#define BALL_C9 PAD_GPIO_PM6
#define PAD_GPIO_PM6 10
#define GPIO_PAD_10 GPIO9
#ifndef BALL_C9_IS_GPIO
#define BALL_C9_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM6_IS_GPIO
#define PAD_GPIO_PM6_IS_GPIO BALL_C9_IS_GPIO
#endif 

#define BALL_B9 PAD_IRIN
#define PAD_IRIN 5
#define GPIO_PAD_5 GPIO4
#ifndef BALL_B9_IS_GPIO
#define BALL_B9_IS_GPIO 0
#endif 
#ifndef PAD_IRIN_IS_GPIO
#define PAD_IRIN_IS_GPIO BALL_B9_IS_GPIO
#endif 

#define BALL_D6 PAD_CEC
#define PAD_CEC 6
#define GPIO_PAD_6 GPIO5
#ifndef BALL_D6_IS_GPIO
#define BALL_D6_IS_GPIO 0
#endif 
#ifndef PAD_CEC_IS_GPIO
#define PAD_CEC_IS_GPIO BALL_D6_IS_GPIO
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

#endif /* _MST6M182VG_H_*/
