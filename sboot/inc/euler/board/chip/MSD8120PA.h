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
#ifndef _MSD8120PA_H_
#define _MSD8120PA_H_

#define PAD_NC 9999
#define PAD_GND 0

#define PIN_40 PAD_GPIO0
#define PAD_GPIO0 45
#define GPIO_PAD_45 GPIO44
#ifndef PIN_40_IS_GPIO
#define PIN_40_IS_GPIO 0
#endif 
#ifndef PAD_GPIO0_IS_GPIO
#define PAD_GPIO0_IS_GPIO PIN_40_IS_GPIO
#endif 

#define PIN_41 PAD_GPIO1
#define PAD_GPIO1 46
#define GPIO_PAD_46 GPIO45
#ifndef PIN_41_IS_GPIO
#define PIN_41_IS_GPIO 0
#endif 
#ifndef PAD_GPIO1_IS_GPIO
#define PAD_GPIO1_IS_GPIO PIN_41_IS_GPIO
#endif 

#define PIN_42 PAD_GPIO2
#define PAD_GPIO2 47
#define GPIO_PAD_47 GPIO46
#ifndef PIN_42_IS_GPIO
#define PIN_42_IS_GPIO 0
#endif 
#ifndef PAD_GPIO2_IS_GPIO
#define PAD_GPIO2_IS_GPIO PIN_42_IS_GPIO
#endif 

#define PIN_43 PAD_GPIO3
#define PAD_GPIO3 48
#define GPIO_PAD_48 GPIO47
#ifndef PIN_43_IS_GPIO
#define PIN_43_IS_GPIO 0
#endif 
#ifndef PAD_GPIO3_IS_GPIO
#define PAD_GPIO3_IS_GPIO PIN_43_IS_GPIO
#endif 

#define PAD_GPIO4 9999
#ifndef PAD_GPIO4_IS_GPIO
#define PAD_GPIO4_IS_GPIO 0
#endif 

#define PIN_44 PAD_GPIO5
#define PAD_GPIO5 50
#define GPIO_PAD_50 GPIO49
#ifndef PIN_44_IS_GPIO
#define PIN_44_IS_GPIO 0
#endif 
#ifndef PAD_GPIO5_IS_GPIO
#define PAD_GPIO5_IS_GPIO PIN_44_IS_GPIO
#endif 

#define PAD_GPIO6 9999
#ifndef PAD_GPIO6_IS_GPIO
#define PAD_GPIO6_IS_GPIO 0
#endif 

#define PAD_GPIO7 9999
#ifndef PAD_GPIO7_IS_GPIO
#define PAD_GPIO7_IS_GPIO 0
#endif 

#define PAD_GPIO8 9999
#ifndef PAD_GPIO8_IS_GPIO
#define PAD_GPIO8_IS_GPIO 0
#endif 

#define PAD_GPIO9 9999
#ifndef PAD_GPIO9_IS_GPIO
#define PAD_GPIO9_IS_GPIO 0
#endif 

#define PAD_B_ODD0 9999
#ifndef PAD_B_ODD0_IS_GPIO
#define PAD_B_ODD0_IS_GPIO 0
#endif 

#define PAD_B_ODD1 9999
#ifndef PAD_B_ODD1_IS_GPIO
#define PAD_B_ODD1_IS_GPIO 0
#endif 

#define PAD_B_ODD2 9999
#ifndef PAD_B_ODD2_IS_GPIO
#define PAD_B_ODD2_IS_GPIO 0
#endif 

#define PAD_B_ODD3 9999
#ifndef PAD_B_ODD3_IS_GPIO
#define PAD_B_ODD3_IS_GPIO 0
#endif 

#define PIN_45 PAD_B_ODD4
#define PAD_B_ODD4 40
#define GPIO_PAD_40 GPIO39
#ifndef PIN_45_IS_GPIO
#define PIN_45_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD4_IS_GPIO
#define PAD_B_ODD4_IS_GPIO PIN_45_IS_GPIO
#endif 

#define PIN_46 PAD_B_ODD5
#define PAD_B_ODD5 39
#define GPIO_PAD_39 GPIO38
#ifndef PIN_46_IS_GPIO
#define PIN_46_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD5_IS_GPIO
#define PAD_B_ODD5_IS_GPIO PIN_46_IS_GPIO
#endif 

#define PIN_47 PAD_B_ODD6
#define PAD_B_ODD6 38
#define GPIO_PAD_38 GPIO37
#ifndef PIN_47_IS_GPIO
#define PIN_47_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD6_IS_GPIO
#define PAD_B_ODD6_IS_GPIO PIN_47_IS_GPIO
#endif 

#define PIN_48 PAD_B_ODD7
#define PAD_B_ODD7 37
#define GPIO_PAD_37 GPIO36
#ifndef PIN_48_IS_GPIO
#define PIN_48_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD7_IS_GPIO
#define PAD_B_ODD7_IS_GPIO PIN_48_IS_GPIO
#endif 

#define PIN_49 PAD_G_ODD0
#define PAD_G_ODD0 36
#define GPIO_PAD_36 GPIO35
#ifndef PIN_49_IS_GPIO
#define PIN_49_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD0_IS_GPIO
#define PAD_G_ODD0_IS_GPIO PIN_49_IS_GPIO
#endif 

#define PIN_50 PAD_G_ODD1
#define PAD_G_ODD1 35
#define GPIO_PAD_35 GPIO34
#ifndef PIN_50_IS_GPIO
#define PIN_50_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD1_IS_GPIO
#define PAD_G_ODD1_IS_GPIO PIN_50_IS_GPIO
#endif 

#define PIN_51 PAD_G_ODD2
#define PAD_G_ODD2 34
#define GPIO_PAD_34 GPIO33
#ifndef PIN_51_IS_GPIO
#define PIN_51_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD2_IS_GPIO
#define PAD_G_ODD2_IS_GPIO PIN_51_IS_GPIO
#endif 

#define PIN_52 PAD_G_ODD3
#define PAD_G_ODD3 33
#define GPIO_PAD_33 GPIO32
#ifndef PIN_52_IS_GPIO
#define PIN_52_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD3_IS_GPIO
#define PAD_G_ODD3_IS_GPIO PIN_52_IS_GPIO
#endif 

#define PIN_53 PAD_G_ODD4
#define PAD_G_ODD4 32
#define GPIO_PAD_32 GPIO31
#ifndef PIN_53_IS_GPIO
#define PIN_53_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD4_IS_GPIO
#define PAD_G_ODD4_IS_GPIO PIN_53_IS_GPIO
#endif 

#define PIN_54 PAD_G_ODD5
#define PAD_G_ODD5 31
#define GPIO_PAD_31 GPIO30
#ifndef PIN_54_IS_GPIO
#define PIN_54_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD5_IS_GPIO
#define PAD_G_ODD5_IS_GPIO PIN_54_IS_GPIO
#endif 

#define PAD_G_ODD6 9999
#ifndef PAD_G_ODD6_IS_GPIO
#define PAD_G_ODD6_IS_GPIO 0
#endif 

#define PAD_G_ODD7 9999
#ifndef PAD_G_ODD7_IS_GPIO
#define PAD_G_ODD7_IS_GPIO 0
#endif 

#define PIN_55 PAD_R_ODD0
#define PAD_R_ODD0 28
#define GPIO_PAD_28 GPIO27
#ifndef PIN_55_IS_GPIO
#define PIN_55_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD0_IS_GPIO
#define PAD_R_ODD0_IS_GPIO PIN_55_IS_GPIO
#endif 

#define PIN_56 PAD_R_ODD1
#define PAD_R_ODD1 27
#define GPIO_PAD_27 GPIO26
#ifndef PIN_56_IS_GPIO
#define PIN_56_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD1_IS_GPIO
#define PAD_R_ODD1_IS_GPIO PIN_56_IS_GPIO
#endif 

#define PAD_R_ODD2 9999
#ifndef PAD_R_ODD2_IS_GPIO
#define PAD_R_ODD2_IS_GPIO 0
#endif 

#define PAD_R_ODD3 9999
#ifndef PAD_R_ODD3_IS_GPIO
#define PAD_R_ODD3_IS_GPIO 0
#endif 

#define PIN_58 PAD_R_ODD4
#define PAD_R_ODD4 24
#define GPIO_PAD_24 GPIO23
#ifndef PIN_58_IS_GPIO
#define PIN_58_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD4_IS_GPIO
#define PAD_R_ODD4_IS_GPIO PIN_58_IS_GPIO
#endif 

#define PIN_59 PAD_R_ODD5
#define PAD_R_ODD5 23
#define GPIO_PAD_23 GPIO22
#ifndef PIN_59_IS_GPIO
#define PIN_59_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD5_IS_GPIO
#define PAD_R_ODD5_IS_GPIO PIN_59_IS_GPIO
#endif 

#define PIN_60 PAD_R_ODD6
#define PAD_R_ODD6 22
#define GPIO_PAD_22 GPIO21
#ifndef PIN_60_IS_GPIO
#define PIN_60_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD6_IS_GPIO
#define PAD_R_ODD6_IS_GPIO PIN_60_IS_GPIO
#endif 

#define PIN_61 PAD_R_ODD7
#define PAD_R_ODD7 21
#define GPIO_PAD_21 GPIO20
#ifndef PIN_61_IS_GPIO
#define PIN_61_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD7_IS_GPIO
#define PAD_R_ODD7_IS_GPIO PIN_61_IS_GPIO
#endif 

#define PIN_62 PAD_LCK
#define PAD_LCK 20
#define GPIO_PAD_20 GPIO19
#ifndef PIN_62_IS_GPIO
#define PIN_62_IS_GPIO 0
#endif 
#ifndef PAD_LCK_IS_GPIO
#define PAD_LCK_IS_GPIO PIN_62_IS_GPIO
#endif 

#define PIN_63 PAD_LDE
#define PAD_LDE 19
#define GPIO_PAD_19 GPIO18
#ifndef PIN_63_IS_GPIO
#define PIN_63_IS_GPIO 0
#endif 
#ifndef PAD_LDE_IS_GPIO
#define PAD_LDE_IS_GPIO PIN_63_IS_GPIO
#endif 

#define PAD_LHSYNC 9999
#ifndef PAD_LHSYNC_IS_GPIO
#define PAD_LHSYNC_IS_GPIO 0
#endif 

#define PAD_LVSYNC 9999
#ifndef PAD_LVSYNC_IS_GPIO
#define PAD_LVSYNC_IS_GPIO 0
#endif 

#define PAD_GPIO19 9999
#ifndef PAD_GPIO19_IS_GPIO
#define PAD_GPIO19_IS_GPIO 0
#endif 

#define PAD_GPIO18 9999
#ifndef PAD_GPIO18_IS_GPIO
#define PAD_GPIO18_IS_GPIO 0
#endif 

#define PAD_GPIO17 9999
#ifndef PAD_GPIO17_IS_GPIO
#define PAD_GPIO17_IS_GPIO 0
#endif 

#define PAD_GPIO16 9999
#ifndef PAD_GPIO16_IS_GPIO
#define PAD_GPIO16_IS_GPIO 0
#endif 

#define PIN_64 PAD_GPIO15
#define PAD_GPIO15 60
#define GPIO_PAD_60 GPIO59
#ifndef PIN_64_IS_GPIO
#define PIN_64_IS_GPIO 0
#endif 
#ifndef PAD_GPIO15_IS_GPIO
#define PAD_GPIO15_IS_GPIO PIN_64_IS_GPIO
#endif 

#define PAD_GPIO14 9999
#ifndef PAD_GPIO14_IS_GPIO
#define PAD_GPIO14_IS_GPIO 0
#endif 

#define PAD_PWM3 9999
#ifndef PAD_PWM3_IS_GPIO
#define PAD_PWM3_IS_GPIO 0
#endif 

#define PAD_PWM2 9999
#ifndef PAD_PWM2_IS_GPIO
#define PAD_PWM2_IS_GPIO 0
#endif 

#define PAD_TCON11 9999
#ifndef PAD_TCON11_IS_GPIO
#define PAD_TCON11_IS_GPIO 0
#endif 

#define PAD_TCON10 9999
#ifndef PAD_TCON10_IS_GPIO
#define PAD_TCON10_IS_GPIO 0
#endif 

#define PAD_TCON9 9999
#ifndef PAD_TCON9_IS_GPIO
#define PAD_TCON9_IS_GPIO 0
#endif 

#define PAD_TCON8 9999
#ifndef PAD_TCON8_IS_GPIO
#define PAD_TCON8_IS_GPIO 0
#endif 

#define PAD_TCON7 9999
#ifndef PAD_TCON7_IS_GPIO
#define PAD_TCON7_IS_GPIO 0
#endif 

#define PAD_TCON6 9999
#ifndef PAD_TCON6_IS_GPIO
#define PAD_TCON6_IS_GPIO 0
#endif 

#define PAD_TCON5 9999
#ifndef PAD_TCON5_IS_GPIO
#define PAD_TCON5_IS_GPIO 0
#endif 

#define PAD_TCON4 9999
#ifndef PAD_TCON4_IS_GPIO
#define PAD_TCON4_IS_GPIO 0
#endif 

#define PAD_TCON3 9999
#ifndef PAD_TCON3_IS_GPIO
#define PAD_TCON3_IS_GPIO 0
#endif 

#define PAD_TCON2 9999
#ifndef PAD_TCON2_IS_GPIO
#define PAD_TCON2_IS_GPIO 0
#endif 

#define PAD_TCON1 9999
#ifndef PAD_TCON1_IS_GPIO
#define PAD_TCON1_IS_GPIO 0
#endif 

#define PAD_TCON0 9999
#ifndef PAD_TCON0_IS_GPIO
#define PAD_TCON0_IS_GPIO 0
#endif 

#define PAD_HOTPLUG_C 9999
#ifndef PAD_HOTPLUG_C_IS_GPIO
#define PAD_HOTPLUG_C_IS_GPIO 0
#endif 

#define PAD_HOTPLUG_A 9999
#ifndef PAD_HOTPLUG_A_IS_GPIO
#define PAD_HOTPLUG_A_IS_GPIO 0
#endif 

#define PIN_65 PAD_PWM1
#define PAD_PWM1 15
#define GPIO_PAD_15 GPIO14
#ifndef PIN_65_IS_GPIO
#define PIN_65_IS_GPIO 0
#endif 
#ifndef PAD_PWM1_IS_GPIO
#define PAD_PWM1_IS_GPIO PIN_65_IS_GPIO
#endif 

#define PIN_66 PAD_PWM0
#define PAD_PWM0 16
#define GPIO_PAD_16 GPIO15
#ifndef PIN_66_IS_GPIO
#define PIN_66_IS_GPIO 0
#endif 
#ifndef PAD_PWM0_IS_GPIO
#define PAD_PWM0_IS_GPIO PIN_66_IS_GPIO
#endif 

#define PAD_GPIO13 9999
#ifndef PAD_GPIO13_IS_GPIO
#define PAD_GPIO13_IS_GPIO 0
#endif 

#define PAD_GPIO12 9999
#ifndef PAD_GPIO12_IS_GPIO
#define PAD_GPIO12_IS_GPIO 0
#endif 

#define PIN_73 PAD_TESTPIN
#define PAD_TESTPIN 66
#define GPIO_PAD_66 GPIO65
#ifndef PIN_73_IS_GPIO
#define PIN_73_IS_GPIO 0
#endif 
#ifndef PAD_TESTPIN_IS_GPIO
#define PAD_TESTPIN_IS_GPIO PIN_73_IS_GPIO
#endif 

#define PIN_74 PAD_CEC
#define PAD_CEC 72
#define GPIO_PAD_72 GPIO71
#ifndef PIN_74_IS_GPIO
#define PIN_74_IS_GPIO 0
#endif 
#ifndef PAD_CEC_IS_GPIO
#define PAD_CEC_IS_GPIO PIN_74_IS_GPIO
#endif 

#define PIN_75 PAD_IRIN
#define PAD_IRIN 77
#define GPIO_PAD_77 GPIO76
#ifndef PIN_75_IS_GPIO
#define PIN_75_IS_GPIO 0
#endif 
#ifndef PAD_IRIN_IS_GPIO
#define PAD_IRIN_IS_GPIO PIN_75_IS_GPIO
#endif 

#define PIN_76 PAD_INT
#define PAD_INT 65
#define GPIO_PAD_65 GPIO64
#ifndef PIN_76_IS_GPIO
#define PIN_76_IS_GPIO 0
#endif 
#ifndef PAD_INT_IS_GPIO
#define PAD_INT_IS_GPIO PIN_76_IS_GPIO
#endif 

#define PIN_81 PAD_SAR0
#define PAD_SAR0 76
#define GPIO_PAD_76 GPIO75
#ifndef PIN_81_IS_GPIO
#define PIN_81_IS_GPIO 0
#endif 
#ifndef PAD_SAR0_IS_GPIO
#define PAD_SAR0_IS_GPIO PIN_81_IS_GPIO
#endif 

#define PIN_82 PAD_SAR1
#define PAD_SAR1 75
#define GPIO_PAD_75 GPIO74
#ifndef PIN_82_IS_GPIO
#define PIN_82_IS_GPIO 0
#endif 
#ifndef PAD_SAR1_IS_GPIO
#define PAD_SAR1_IS_GPIO PIN_82_IS_GPIO
#endif 

#define PAD_SAR2 9999
#ifndef PAD_SAR2_IS_GPIO
#define PAD_SAR2_IS_GPIO 0
#endif 

#define PAD_SAR3 9999
#ifndef PAD_SAR3_IS_GPIO
#define PAD_SAR3_IS_GPIO 0
#endif 

#define PAD_GPIO11 9999
#ifndef PAD_GPIO11_IS_GPIO
#define PAD_GPIO11_IS_GPIO 0
#endif 

#define PAD_GPIO10 9999
#ifndef PAD_GPIO10_IS_GPIO
#define PAD_GPIO10_IS_GPIO 0
#endif 

#define PAD_DDCDC_DAT 9999
#ifndef PAD_DDCDC_DAT_IS_GPIO
#define PAD_DDCDC_DAT_IS_GPIO 0
#endif 

#define PAD_DDCDC_CLK 9999
#ifndef PAD_DDCDC_CLK_IS_GPIO
#define PAD_DDCDC_CLK_IS_GPIO 0
#endif 

#define PAD_DDCDA_DAT 9999
#ifndef PAD_DDCDA_DAT_IS_GPIO
#define PAD_DDCDA_DAT_IS_GPIO 0
#endif 

#define PAD_DDCDA_CLK 9999
#ifndef PAD_DDCDA_CLK_IS_GPIO
#define PAD_DDCDA_CLK_IS_GPIO 0
#endif 

#define PAD_PMGPIO 9999
#ifndef PAD_PMGPIO_IS_GPIO
#define PAD_PMGPIO_IS_GPIO 0
#endif 

#define PAD_GPIO_PM1 9999
#ifndef PAD_GPIO_PM1_IS_GPIO
#define PAD_GPIO_PM1_IS_GPIO 0
#endif 

#define PAD_GPIO_PM6 9999
#ifndef PAD_GPIO_PM6_IS_GPIO
#define PAD_GPIO_PM6_IS_GPIO 0
#endif 

#define PAD_GPIO_PM5 9999
#ifndef PAD_GPIO_PM5_IS_GPIO
#define PAD_GPIO_PM5_IS_GPIO 0
#endif 

#define PAD_GPIO_PM4 9999
#ifndef PAD_GPIO_PM4_IS_GPIO
#define PAD_GPIO_PM4_IS_GPIO 0
#endif 

#define PIN_85 PAD_MHL_DET
#define PAD_MHL_DET 87
#define GPIO_PAD_87 GPIO86
#ifndef PIN_85_IS_GPIO
#define PIN_85_IS_GPIO 0
#endif 
#ifndef PAD_MHL_DET_IS_GPIO
#define PAD_MHL_DET_IS_GPIO PIN_85_IS_GPIO
#endif 

#define PIN_86 PAD_DDCDB_DAT
#define PAD_DDCDB_DAT 82
#define GPIO_PAD_82 GPIO81
#ifndef PIN_86_IS_GPIO
#define PIN_86_IS_GPIO 0
#endif 
#ifndef PAD_DDCDB_DAT_IS_GPIO
#define PAD_DDCDB_DAT_IS_GPIO PIN_86_IS_GPIO
#endif 

#define PIN_87 PAD_DDCDB_CLK
#define PAD_DDCDB_CLK 81
#define GPIO_PAD_81 GPIO80
#ifndef PIN_87_IS_GPIO
#define PIN_87_IS_GPIO 0
#endif 
#ifndef PAD_DDCDB_CLK_IS_GPIO
#define PAD_DDCDB_CLK_IS_GPIO PIN_87_IS_GPIO
#endif 

#define PIN_88 PAD_HOTPLUG_B
#define PAD_HOTPLUG_B 83
#define GPIO_PAD_83 GPIO82
#ifndef PIN_88_IS_GPIO
#define PIN_88_IS_GPIO 0
#endif 
#ifndef PAD_HOTPLUG_B_IS_GPIO
#define PAD_HOTPLUG_B_IS_GPIO PIN_88_IS_GPIO
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
#define CHIP_FAMILY_TYPE           CHIP_FAMILY_EULER

#endif /* _MSD8120PA_H_*/
