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
#ifndef _MSD393SSV_H_
#define _MSD393SSV_H_

#define PAD_NC 9999
#define PAD_GND 0

#define BALL_G9 PAD_GPIO_PM19
#define PAD_GPIO_PM19 20
#define GPIO_PAD_20 GPIO19
#ifndef BALL_G9_IS_GPIO
#define BALL_G9_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM19_IS_GPIO
#define PAD_GPIO_PM19_IS_GPIO BALL_G9_IS_GPIO
#endif 

#define BALL_F8 PAD_GPIO_PM18
#define PAD_GPIO_PM18 19
#define GPIO_PAD_19 GPIO18
#ifndef BALL_F8_IS_GPIO
#define BALL_F8_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM18_IS_GPIO
#define PAD_GPIO_PM18_IS_GPIO BALL_F8_IS_GPIO
#endif 

#define BALL_C2 PAD_GPIO_PM17
#define PAD_GPIO_PM17 18
#define GPIO_PAD_18 GPIO17
#ifndef BALL_C2_IS_GPIO
#define BALL_C2_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM17_IS_GPIO
#define PAD_GPIO_PM17_IS_GPIO BALL_C2_IS_GPIO
#endif 

#define BALL_C1 PAD_GPIO_PM16
#define PAD_GPIO_PM16 17
#define GPIO_PAD_17 GPIO16
#ifndef BALL_C1_IS_GPIO
#define BALL_C1_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM16_IS_GPIO
#define PAD_GPIO_PM16_IS_GPIO BALL_C1_IS_GPIO
#endif 

#define BALL_D3 PAD_GPIO_PM15
#define PAD_GPIO_PM15 16
#define GPIO_PAD_16 GPIO15
#ifndef BALL_D3_IS_GPIO
#define BALL_D3_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM15_IS_GPIO
#define PAD_GPIO_PM15_IS_GPIO BALL_D3_IS_GPIO
#endif 

#define BALL_D2 PAD_GPIO_PM14
#define PAD_GPIO_PM14 15
#define GPIO_PAD_15 GPIO14
#ifndef BALL_D2_IS_GPIO
#define BALL_D2_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM14_IS_GPIO
#define PAD_GPIO_PM14_IS_GPIO BALL_D2_IS_GPIO
#endif 

#define BALL_F3 PAD_GPIO_PM13
#define PAD_GPIO_PM13 14
#define GPIO_PAD_14 GPIO13
#ifndef BALL_F3_IS_GPIO
#define BALL_F3_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM13_IS_GPIO
#define PAD_GPIO_PM13_IS_GPIO BALL_F3_IS_GPIO
#endif 

#define BALL_C6 PAD_GPIO_PM10
#define PAD_GPIO_PM10 11
#define GPIO_PAD_11 GPIO10
#ifndef BALL_C6_IS_GPIO
#define BALL_C6_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM10_IS_GPIO
#define PAD_GPIO_PM10_IS_GPIO BALL_C6_IS_GPIO
#endif 

#define BALL_G4 PAD_GPIO_PM9
#define PAD_GPIO_PM9 10
#define GPIO_PAD_10 GPIO9
#ifndef BALL_G4_IS_GPIO
#define BALL_G4_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM9_IS_GPIO
#define PAD_GPIO_PM9_IS_GPIO BALL_G4_IS_GPIO
#endif 

#define BALL_J6 PAD_GPIO_PM8
#define PAD_GPIO_PM8 9
#define GPIO_PAD_9 GPIO8
#ifndef BALL_J6_IS_GPIO
#define BALL_J6_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM8_IS_GPIO
#define PAD_GPIO_PM8_IS_GPIO BALL_J6_IS_GPIO
#endif 

#define BALL_G3 PAD_IRIN
#define PAD_IRIN 21
#define GPIO_PAD_21 GPIO20
#ifndef BALL_G3_IS_GPIO
#define BALL_G3_IS_GPIO 0
#endif 
#ifndef PAD_IRIN_IS_GPIO
#define PAD_IRIN_IS_GPIO BALL_G3_IS_GPIO
#endif 

#define BALL_J5 PAD_GPIO_PM7
#define PAD_GPIO_PM7 8
#define GPIO_PAD_8 GPIO7
#ifndef BALL_J5_IS_GPIO
#define BALL_J5_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM7_IS_GPIO
#define PAD_GPIO_PM7_IS_GPIO BALL_J5_IS_GPIO
#endif 

#define BALL_B6 PAD_GPIO_PM6
#define PAD_GPIO_PM6 7
#define GPIO_PAD_7 GPIO6
#ifndef BALL_B6_IS_GPIO
#define BALL_B6_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM6_IS_GPIO
#define PAD_GPIO_PM6_IS_GPIO BALL_B6_IS_GPIO
#endif 

#define BALL_H4 PAD_GPIO_PM3
#define PAD_GPIO_PM3 4
#define GPIO_PAD_4 GPIO3
#ifndef BALL_H4_IS_GPIO
#define BALL_H4_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM3_IS_GPIO
#define PAD_GPIO_PM3_IS_GPIO BALL_H4_IS_GPIO
#endif 

#define BALL_E2 PAD_GPIO_PM5
#define PAD_GPIO_PM5 6
#define GPIO_PAD_6 GPIO5
#ifndef BALL_E2_IS_GPIO
#define BALL_E2_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM5_IS_GPIO
#define PAD_GPIO_PM5_IS_GPIO BALL_E2_IS_GPIO
#endif 

#define BALL_D1 PAD_GPIO_PM12
#define PAD_GPIO_PM12 13
#define GPIO_PAD_13 GPIO12
#ifndef BALL_D1_IS_GPIO
#define BALL_D1_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM12_IS_GPIO
#define PAD_GPIO_PM12_IS_GPIO BALL_D1_IS_GPIO
#endif 

#define BALL_H8 PAD_GPIO_PM4
#define PAD_GPIO_PM4 5
#define GPIO_PAD_5 GPIO4
#ifndef BALL_H8_IS_GPIO
#define BALL_H8_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM4_IS_GPIO
#define PAD_GPIO_PM4_IS_GPIO BALL_H8_IS_GPIO
#endif 

#define BALL_J7 PAD_GPIO_PM2
#define PAD_GPIO_PM2 3
#define GPIO_PAD_3 GPIO2
#ifndef BALL_J7_IS_GPIO
#define BALL_J7_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM2_IS_GPIO
#define PAD_GPIO_PM2_IS_GPIO BALL_J7_IS_GPIO
#endif 

#define BALL_E1 PAD_GPIO_PM1
#define PAD_GPIO_PM1 2
#define GPIO_PAD_2 GPIO1
#ifndef BALL_E1_IS_GPIO
#define BALL_E1_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM1_IS_GPIO
#define PAD_GPIO_PM1_IS_GPIO BALL_E1_IS_GPIO
#endif 

#define BALL_E5 PAD_GPIO_PM11
#define PAD_GPIO_PM11 12
#define GPIO_PAD_12 GPIO11
#ifndef BALL_E5_IS_GPIO
#define BALL_E5_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM11_IS_GPIO
#define PAD_GPIO_PM11_IS_GPIO BALL_E5_IS_GPIO
#endif 

#define BALL_K7 PAD_GPIO_PM0
#define PAD_GPIO_PM0 1
#define GPIO_PAD_1 GPIO0
#ifndef BALL_K7_IS_GPIO
#define BALL_K7_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM0_IS_GPIO
#define PAD_GPIO_PM0_IS_GPIO BALL_K7_IS_GPIO
#endif 

#define BALL_L7 PAD_SAR4
#define PAD_SAR4 38
#define GPIO_PAD_38 GPIO37
#ifndef BALL_L7_IS_GPIO
#define BALL_L7_IS_GPIO 0
#endif 
#ifndef PAD_SAR4_IS_GPIO
#define PAD_SAR4_IS_GPIO BALL_L7_IS_GPIO
#endif 

#define BALL_K6 PAD_SAR3
#define PAD_SAR3 37
#define GPIO_PAD_37 GPIO36
#ifndef BALL_K6_IS_GPIO
#define BALL_K6_IS_GPIO 0
#endif 
#ifndef PAD_SAR3_IS_GPIO
#define PAD_SAR3_IS_GPIO BALL_K6_IS_GPIO
#endif 

#define BALL_K5 PAD_SAR2
#define PAD_SAR2 36
#define GPIO_PAD_36 GPIO35
#ifndef BALL_K5_IS_GPIO
#define BALL_K5_IS_GPIO 0
#endif 
#ifndef PAD_SAR2_IS_GPIO
#define PAD_SAR2_IS_GPIO BALL_K5_IS_GPIO
#endif 

#define BALL_L5 PAD_SAR1
#define PAD_SAR1 35
#define GPIO_PAD_35 GPIO34
#ifndef BALL_L5_IS_GPIO
#define BALL_L5_IS_GPIO 0
#endif 
#ifndef PAD_SAR1_IS_GPIO
#define PAD_SAR1_IS_GPIO BALL_L5_IS_GPIO
#endif 

#define BALL_M6 PAD_SAR0
#define PAD_SAR0 34
#define GPIO_PAD_34 GPIO33
#ifndef BALL_M6_IS_GPIO
#define BALL_M6_IS_GPIO 0
#endif 
#ifndef PAD_SAR0_IS_GPIO
#define PAD_SAR0_IS_GPIO BALL_M6_IS_GPIO
#endif 

#define BALL_A6 PAD_PM_SPI_CZ
#define PAD_PM_SPI_CZ 23
#define GPIO_PAD_23 GPIO22
#ifndef BALL_A6_IS_GPIO
#define BALL_A6_IS_GPIO 0
#endif 
#ifndef PAD_PM_SPI_CZ_IS_GPIO
#define PAD_PM_SPI_CZ_IS_GPIO BALL_A6_IS_GPIO
#endif 

#define BALL_C7 PAD_PM_SPI_DO
#define PAD_PM_SPI_DO 26
#define GPIO_PAD_26 GPIO25
#ifndef BALL_C7_IS_GPIO
#define BALL_C7_IS_GPIO 0
#endif 
#ifndef PAD_PM_SPI_DO_IS_GPIO
#define PAD_PM_SPI_DO_IS_GPIO BALL_C7_IS_GPIO
#endif 

#define BALL_A7 PAD_PM_SPI_DI
#define PAD_PM_SPI_DI 25
#define GPIO_PAD_25 GPIO24
#ifndef BALL_A7_IS_GPIO
#define BALL_A7_IS_GPIO 0
#endif 
#ifndef PAD_PM_SPI_DI_IS_GPIO
#define PAD_PM_SPI_DI_IS_GPIO BALL_A7_IS_GPIO
#endif 

#define BALL_B7 PAD_PM_SPI_CK
#define PAD_PM_SPI_CK 24
#define GPIO_PAD_24 GPIO23
#ifndef BALL_B7_IS_GPIO
#define BALL_B7_IS_GPIO 0
#endif 
#ifndef PAD_PM_SPI_CK_IS_GPIO
#define PAD_PM_SPI_CK_IS_GPIO BALL_B7_IS_GPIO
#endif 

#define BALL_AF9 PAD_TGPIO0
#define PAD_TGPIO0 180
#define GPIO_PAD_180 GPIO179
#ifndef BALL_AF9_IS_GPIO
#define BALL_AF9_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO0_IS_GPIO
#define PAD_TGPIO0_IS_GPIO BALL_AF9_IS_GPIO
#endif 

#define BALL_AD10 PAD_TGPIO1
#define PAD_TGPIO1 181
#define GPIO_PAD_181 GPIO180
#ifndef BALL_AD10_IS_GPIO
#define BALL_AD10_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO1_IS_GPIO
#define PAD_TGPIO1_IS_GPIO BALL_AD10_IS_GPIO
#endif 

#define BALL_AD9 PAD_TGPIO2
#define PAD_TGPIO2 182
#define GPIO_PAD_182 GPIO181
#ifndef BALL_AD9_IS_GPIO
#define BALL_AD9_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO2_IS_GPIO
#define PAD_TGPIO2_IS_GPIO BALL_AD9_IS_GPIO
#endif 

#define BALL_AE9 PAD_TGPIO3
#define PAD_TGPIO3 183
#define GPIO_PAD_183 GPIO182
#ifndef BALL_AE9_IS_GPIO
#define BALL_AE9_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO3_IS_GPIO
#define PAD_TGPIO3_IS_GPIO BALL_AE9_IS_GPIO
#endif 

#define BALL_AE2 PAD_DDCDA_CK
#define PAD_DDCDA_CK 206
#define GPIO_PAD_206 GPIO205
#ifndef BALL_AE2_IS_GPIO
#define BALL_AE2_IS_GPIO 0
#endif 
#ifndef PAD_DDCDA_CK_IS_GPIO
#define PAD_DDCDA_CK_IS_GPIO BALL_AE2_IS_GPIO
#endif 

#define BALL_AE1 PAD_DDCDA_DA
#define PAD_DDCDA_DA 207
#define GPIO_PAD_207 GPIO206
#ifndef BALL_AE1_IS_GPIO
#define BALL_AE1_IS_GPIO 0
#endif 
#ifndef PAD_DDCDA_DA_IS_GPIO
#define PAD_DDCDA_DA_IS_GPIO BALL_AE1_IS_GPIO
#endif 

#define BALL_V5 PAD_DDCDB_CK
#define PAD_DDCDB_CK 208
#define GPIO_PAD_208 GPIO207
#ifndef BALL_V5_IS_GPIO
#define BALL_V5_IS_GPIO 0
#endif 
#ifndef PAD_DDCDB_CK_IS_GPIO
#define PAD_DDCDB_CK_IS_GPIO BALL_V5_IS_GPIO
#endif 

#define BALL_W5 PAD_DDCDB_DA
#define PAD_DDCDB_DA 209
#define GPIO_PAD_209 GPIO208
#ifndef BALL_W5_IS_GPIO
#define BALL_W5_IS_GPIO 0
#endif 
#ifndef PAD_DDCDB_DA_IS_GPIO
#define PAD_DDCDB_DA_IS_GPIO BALL_W5_IS_GPIO
#endif 

#define BALL_Y5 PAD_HOTPLUGB
#define PAD_HOTPLUGB 28
#define GPIO_PAD_28 GPIO27
#ifndef BALL_Y5_IS_GPIO
#define BALL_Y5_IS_GPIO 0
#endif 
#ifndef PAD_HOTPLUGB_IS_GPIO
#define PAD_HOTPLUGB_IS_GPIO BALL_Y5_IS_GPIO
#endif 

#define BALL_R5 PAD_DDCDC_DA
#define PAD_DDCDC_DA 31
#define GPIO_PAD_31 GPIO30
#ifndef BALL_R5_IS_GPIO
#define BALL_R5_IS_GPIO 0
#endif 
#ifndef PAD_DDCDC_DA_IS_GPIO
#define PAD_DDCDC_DA_IS_GPIO BALL_R5_IS_GPIO
#endif 

#define BALL_R4 PAD_DDCDC_CK
#define PAD_DDCDC_CK 30
#define GPIO_PAD_30 GPIO29
#ifndef BALL_R4_IS_GPIO
#define BALL_R4_IS_GPIO 0
#endif 
#ifndef PAD_DDCDC_CK_IS_GPIO
#define PAD_DDCDC_CK_IS_GPIO BALL_R4_IS_GPIO
#endif 

#define BALL_U6 PAD_HOTPLUGC
#define PAD_HOTPLUGC 210
#define GPIO_PAD_210 GPIO209
#ifndef BALL_U6_IS_GPIO
#define BALL_U6_IS_GPIO 0
#endif 
#ifndef PAD_HOTPLUGC_IS_GPIO
#define PAD_HOTPLUGC_IS_GPIO BALL_U6_IS_GPIO
#endif 

#define BALL_W4 PAD_DDCDD_DA
#define PAD_DDCDD_DA 33
#define GPIO_PAD_33 GPIO32
#ifndef BALL_W4_IS_GPIO
#define BALL_W4_IS_GPIO 0
#endif 
#ifndef PAD_DDCDD_DA_IS_GPIO
#define PAD_DDCDD_DA_IS_GPIO BALL_W4_IS_GPIO
#endif 

#define BALL_U4 PAD_DDCDD_CK
#define PAD_DDCDD_CK 32
#define GPIO_PAD_32 GPIO31
#ifndef BALL_U4_IS_GPIO
#define BALL_U4_IS_GPIO 0
#endif 
#ifndef PAD_DDCDD_CK_IS_GPIO
#define PAD_DDCDD_CK_IS_GPIO BALL_U4_IS_GPIO
#endif 

#define BALL_T5 PAD_HOTPLUGD
#define PAD_HOTPLUGD 29
#define GPIO_PAD_29 GPIO28
#ifndef BALL_T5_IS_GPIO
#define BALL_T5_IS_GPIO 0
#endif 
#ifndef PAD_HOTPLUGD_IS_GPIO
#define PAD_HOTPLUGD_IS_GPIO BALL_T5_IS_GPIO
#endif 

#define BALL_AE3 PAD_HOTPLUGA
#define PAD_HOTPLUGA 27
#define GPIO_PAD_27 GPIO26
#ifndef BALL_AE3_IS_GPIO
#define BALL_AE3_IS_GPIO 0
#endif 
#ifndef PAD_HOTPLUGA_IS_GPIO
#define PAD_HOTPLUGA_IS_GPIO BALL_AE3_IS_GPIO
#endif 

#define BALL_R6 PAD_CEC
#define PAD_CEC 22
#define GPIO_PAD_22 GPIO21
#ifndef BALL_R6_IS_GPIO
#define BALL_R6_IS_GPIO 0
#endif 
#ifndef PAD_CEC_IS_GPIO
#define PAD_CEC_IS_GPIO BALL_R6_IS_GPIO
#endif 

#define BALL_U20 PAD_TS2_D0
#define PAD_TS2_D0 89
#define GPIO_PAD_89 GPIO88
#ifndef BALL_U20_IS_GPIO
#define BALL_U20_IS_GPIO 0
#endif 
#ifndef PAD_TS2_D0_IS_GPIO
#define PAD_TS2_D0_IS_GPIO BALL_U20_IS_GPIO
#endif 

#define BALL_W20 PAD_TS2_VLD
#define PAD_TS2_VLD 90
#define GPIO_PAD_90 GPIO89
#ifndef BALL_W20_IS_GPIO
#define BALL_W20_IS_GPIO 0
#endif 
#ifndef PAD_TS2_VLD_IS_GPIO
#define PAD_TS2_VLD_IS_GPIO BALL_W20_IS_GPIO
#endif 

#define BALL_Y20 PAD_TS2_CLK
#define PAD_TS2_CLK 92
#define GPIO_PAD_92 GPIO91
#ifndef BALL_Y20_IS_GPIO
#define BALL_Y20_IS_GPIO 0
#endif 
#ifndef PAD_TS2_CLK_IS_GPIO
#define PAD_TS2_CLK_IS_GPIO BALL_Y20_IS_GPIO
#endif 

#define BALL_V20 PAD_TS2_SYNC
#define PAD_TS2_SYNC 91
#define GPIO_PAD_91 GPIO90
#ifndef BALL_V20_IS_GPIO
#define BALL_V20_IS_GPIO 0
#endif 
#ifndef PAD_TS2_SYNC_IS_GPIO
#define PAD_TS2_SYNC_IS_GPIO BALL_V20_IS_GPIO
#endif 

#define BALL_AE21 PAD_TS0_D0
#define PAD_TS0_D0 67
#define GPIO_PAD_67 GPIO66
#ifndef BALL_AE21_IS_GPIO
#define BALL_AE21_IS_GPIO 0
#endif 
#ifndef PAD_TS0_D0_IS_GPIO
#define PAD_TS0_D0_IS_GPIO BALL_AE21_IS_GPIO
#endif 

#define BALL_AF21 PAD_TS0_D1
#define PAD_TS0_D1 68
#define GPIO_PAD_68 GPIO67
#ifndef BALL_AF21_IS_GPIO
#define BALL_AF21_IS_GPIO 0
#endif 
#ifndef PAD_TS0_D1_IS_GPIO
#define PAD_TS0_D1_IS_GPIO BALL_AF21_IS_GPIO
#endif 

#define BALL_AD22 PAD_TS0_D2
#define PAD_TS0_D2 69
#define GPIO_PAD_69 GPIO68
#ifndef BALL_AD22_IS_GPIO
#define BALL_AD22_IS_GPIO 0
#endif 
#ifndef PAD_TS0_D2_IS_GPIO
#define PAD_TS0_D2_IS_GPIO BALL_AD22_IS_GPIO
#endif 

#define BALL_AD15 PAD_TS0_D3
#define PAD_TS0_D3 70
#define GPIO_PAD_70 GPIO69
#ifndef BALL_AD15_IS_GPIO
#define BALL_AD15_IS_GPIO 0
#endif 
#ifndef PAD_TS0_D3_IS_GPIO
#define PAD_TS0_D3_IS_GPIO BALL_AD15_IS_GPIO
#endif 

#define BALL_AE15 PAD_TS0_D4
#define PAD_TS0_D4 71
#define GPIO_PAD_71 GPIO70
#ifndef BALL_AE15_IS_GPIO
#define BALL_AE15_IS_GPIO 0
#endif 
#ifndef PAD_TS0_D4_IS_GPIO
#define PAD_TS0_D4_IS_GPIO BALL_AE15_IS_GPIO
#endif 

#define BALL_AF15 PAD_TS0_D5
#define PAD_TS0_D5 72
#define GPIO_PAD_72 GPIO71
#ifndef BALL_AF15_IS_GPIO
#define BALL_AF15_IS_GPIO 0
#endif 
#ifndef PAD_TS0_D5_IS_GPIO
#define PAD_TS0_D5_IS_GPIO BALL_AF15_IS_GPIO
#endif 

#define BALL_AD16 PAD_TS0_D6
#define PAD_TS0_D6 73
#define GPIO_PAD_73 GPIO72
#ifndef BALL_AD16_IS_GPIO
#define BALL_AD16_IS_GPIO 0
#endif 
#ifndef PAD_TS0_D6_IS_GPIO
#define PAD_TS0_D6_IS_GPIO BALL_AD16_IS_GPIO
#endif 

#define BALL_AE16 PAD_TS0_D7
#define PAD_TS0_D7 74
#define GPIO_PAD_74 GPIO73
#ifndef BALL_AE16_IS_GPIO
#define BALL_AE16_IS_GPIO 0
#endif 
#ifndef PAD_TS0_D7_IS_GPIO
#define PAD_TS0_D7_IS_GPIO BALL_AE16_IS_GPIO
#endif 

#define BALL_AF20 PAD_TS0_VLD
#define PAD_TS0_VLD 75
#define GPIO_PAD_75 GPIO74
#ifndef BALL_AF20_IS_GPIO
#define BALL_AF20_IS_GPIO 0
#endif 
#ifndef PAD_TS0_VLD_IS_GPIO
#define PAD_TS0_VLD_IS_GPIO BALL_AF20_IS_GPIO
#endif 

#define BALL_AD21 PAD_TS0_SYNC
#define PAD_TS0_SYNC 76
#define GPIO_PAD_76 GPIO75
#ifndef BALL_AD21_IS_GPIO
#define BALL_AD21_IS_GPIO 0
#endif 
#ifndef PAD_TS0_SYNC_IS_GPIO
#define PAD_TS0_SYNC_IS_GPIO BALL_AD21_IS_GPIO
#endif 

#define BALL_AE20 PAD_TS0_CLK
#define PAD_TS0_CLK 77
#define GPIO_PAD_77 GPIO76
#ifndef BALL_AE20_IS_GPIO
#define BALL_AE20_IS_GPIO 0
#endif 
#ifndef PAD_TS0_CLK_IS_GPIO
#define PAD_TS0_CLK_IS_GPIO BALL_AE20_IS_GPIO
#endif 

#define BALL_AD19 PAD_TS1_CLK
#define PAD_TS1_CLK 78
#define GPIO_PAD_78 GPIO77
#ifndef BALL_AD19_IS_GPIO
#define BALL_AD19_IS_GPIO 0
#endif 
#ifndef PAD_TS1_CLK_IS_GPIO
#define PAD_TS1_CLK_IS_GPIO BALL_AD19_IS_GPIO
#endif 

#define BALL_AF16 PAD_TS1_SYNC
#define PAD_TS1_SYNC 79
#define GPIO_PAD_79 GPIO78
#ifndef BALL_AF16_IS_GPIO
#define BALL_AF16_IS_GPIO 0
#endif 
#ifndef PAD_TS1_SYNC_IS_GPIO
#define PAD_TS1_SYNC_IS_GPIO BALL_AF16_IS_GPIO
#endif 

#define BALL_AE18 PAD_TS1_VLD
#define PAD_TS1_VLD 80
#define GPIO_PAD_80 GPIO79
#ifndef BALL_AE18_IS_GPIO
#define BALL_AE18_IS_GPIO 0
#endif 
#ifndef PAD_TS1_VLD_IS_GPIO
#define PAD_TS1_VLD_IS_GPIO BALL_AE18_IS_GPIO
#endif 

#define BALL_AD20 PAD_TS1_D7
#define PAD_TS1_D7 88
#define GPIO_PAD_88 GPIO87
#ifndef BALL_AD20_IS_GPIO
#define BALL_AD20_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D7_IS_GPIO
#define PAD_TS1_D7_IS_GPIO BALL_AD20_IS_GPIO
#endif 

#define BALL_AF19 PAD_TS1_D6
#define PAD_TS1_D6 87
#define GPIO_PAD_87 GPIO86
#ifndef BALL_AF19_IS_GPIO
#define BALL_AF19_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D6_IS_GPIO
#define PAD_TS1_D6_IS_GPIO BALL_AF19_IS_GPIO
#endif 

#define BALL_AE19 PAD_TS1_D5
#define PAD_TS1_D5 86
#define GPIO_PAD_86 GPIO85
#ifndef BALL_AE19_IS_GPIO
#define BALL_AE19_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D5_IS_GPIO
#define PAD_TS1_D5_IS_GPIO BALL_AE19_IS_GPIO
#endif 

#define BALL_AF18 PAD_TS1_D4
#define PAD_TS1_D4 85
#define GPIO_PAD_85 GPIO84
#ifndef BALL_AF18_IS_GPIO
#define BALL_AF18_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D4_IS_GPIO
#define PAD_TS1_D4_IS_GPIO BALL_AF18_IS_GPIO
#endif 

#define BALL_AD18 PAD_TS1_D3
#define PAD_TS1_D3 84
#define GPIO_PAD_84 GPIO83
#ifndef BALL_AD18_IS_GPIO
#define BALL_AD18_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D3_IS_GPIO
#define PAD_TS1_D3_IS_GPIO BALL_AD18_IS_GPIO
#endif 

#define BALL_AF17 PAD_TS1_D2
#define PAD_TS1_D2 83
#define GPIO_PAD_83 GPIO82
#ifndef BALL_AF17_IS_GPIO
#define BALL_AF17_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D2_IS_GPIO
#define PAD_TS1_D2_IS_GPIO BALL_AF17_IS_GPIO
#endif 

#define BALL_AE17 PAD_TS1_D1
#define PAD_TS1_D1 82
#define GPIO_PAD_82 GPIO81
#ifndef BALL_AE17_IS_GPIO
#define BALL_AE17_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D1_IS_GPIO
#define PAD_TS1_D1_IS_GPIO BALL_AE17_IS_GPIO
#endif 

#define BALL_AD17 PAD_TS1_D0
#define PAD_TS1_D0 81
#define GPIO_PAD_81 GPIO80
#ifndef BALL_AD17_IS_GPIO
#define BALL_AD17_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D0_IS_GPIO
#define PAD_TS1_D0_IS_GPIO BALL_AD17_IS_GPIO
#endif 

#define BALL_M23 PAD_PCM_D3
#define PAD_PCM_D3 105
#define GPIO_PAD_105 GPIO104
#ifndef BALL_M23_IS_GPIO
#define BALL_M23_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D3_IS_GPIO
#define PAD_PCM_D3_IS_GPIO BALL_M23_IS_GPIO
#endif 

#define BALL_AD26 PAD_PCM_D4
#define PAD_PCM_D4 106
#define GPIO_PAD_106 GPIO105
#ifndef BALL_AD26_IS_GPIO
#define BALL_AD26_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D4_IS_GPIO
#define PAD_PCM_D4_IS_GPIO BALL_AD26_IS_GPIO
#endif 

#define BALL_N21 PAD_PCM_D5
#define PAD_PCM_D5 107
#define GPIO_PAD_107 GPIO106
#ifndef BALL_N21_IS_GPIO
#define BALL_N21_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D5_IS_GPIO
#define PAD_PCM_D5_IS_GPIO BALL_N21_IS_GPIO
#endif 

#define BALL_N22 PAD_PCM_D6
#define PAD_PCM_D6 108
#define GPIO_PAD_108 GPIO107
#ifndef BALL_N22_IS_GPIO
#define BALL_N22_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D6_IS_GPIO
#define PAD_PCM_D6_IS_GPIO BALL_N22_IS_GPIO
#endif 

#define BALL_AD25 PAD_PCM_D7
#define PAD_PCM_D7 109
#define GPIO_PAD_109 GPIO108
#ifndef BALL_AD25_IS_GPIO
#define BALL_AD25_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D7_IS_GPIO
#define PAD_PCM_D7_IS_GPIO BALL_AD25_IS_GPIO
#endif 

#define BALL_AC23 PAD_PCM_CE_N
#define PAD_PCM_CE_N 110
#define GPIO_PAD_110 GPIO109
#ifndef BALL_AC23_IS_GPIO
#define BALL_AC23_IS_GPIO 0
#endif 
#ifndef PAD_PCM_CE_N_IS_GPIO
#define PAD_PCM_CE_N_IS_GPIO BALL_AC23_IS_GPIO
#endif 

#define BALL_R22 PAD_PCM_A10
#define PAD_PCM_A10 111
#define GPIO_PAD_111 GPIO110
#ifndef BALL_R22_IS_GPIO
#define BALL_R22_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A10_IS_GPIO
#define PAD_PCM_A10_IS_GPIO BALL_R22_IS_GPIO
#endif 

#define BALL_AB22 PAD_PCM_OE_N
#define PAD_PCM_OE_N 112
#define GPIO_PAD_112 GPIO111
#ifndef BALL_AB22_IS_GPIO
#define BALL_AB22_IS_GPIO 0
#endif 
#ifndef PAD_PCM_OE_N_IS_GPIO
#define PAD_PCM_OE_N_IS_GPIO BALL_AB22_IS_GPIO
#endif 

#define BALL_P23 PAD_PCM_A11
#define PAD_PCM_A11 113
#define GPIO_PAD_113 GPIO112
#ifndef BALL_P23_IS_GPIO
#define BALL_P23_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A11_IS_GPIO
#define PAD_PCM_A11_IS_GPIO BALL_P23_IS_GPIO
#endif 

#define BALL_AB23 PAD_PCM_IORD_N
#define PAD_PCM_IORD_N 114
#define GPIO_PAD_114 GPIO113
#ifndef BALL_AB23_IS_GPIO
#define BALL_AB23_IS_GPIO 0
#endif 
#ifndef PAD_PCM_IORD_N_IS_GPIO
#define PAD_PCM_IORD_N_IS_GPIO BALL_AB23_IS_GPIO
#endif 

#define BALL_N23 PAD_PCM_A9
#define PAD_PCM_A9 115
#define GPIO_PAD_115 GPIO114
#ifndef BALL_N23_IS_GPIO
#define BALL_N23_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A9_IS_GPIO
#define PAD_PCM_A9_IS_GPIO BALL_N23_IS_GPIO
#endif 

#define BALL_AA21 PAD_PCM_IOWR_N
#define PAD_PCM_IOWR_N 116
#define GPIO_PAD_116 GPIO115
#ifndef BALL_AA21_IS_GPIO
#define BALL_AA21_IS_GPIO 0
#endif 
#ifndef PAD_PCM_IOWR_N_IS_GPIO
#define PAD_PCM_IOWR_N_IS_GPIO BALL_AA21_IS_GPIO
#endif 

#define BALL_P22 PAD_PCM_A8
#define PAD_PCM_A8 117
#define GPIO_PAD_117 GPIO116
#ifndef BALL_P22_IS_GPIO
#define BALL_P22_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A8_IS_GPIO
#define PAD_PCM_A8_IS_GPIO BALL_P22_IS_GPIO
#endif 

#define BALL_W23 PAD_PCM_A13
#define PAD_PCM_A13 118
#define GPIO_PAD_118 GPIO117
#ifndef BALL_W23_IS_GPIO
#define BALL_W23_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A13_IS_GPIO
#define PAD_PCM_A13_IS_GPIO BALL_W23_IS_GPIO
#endif 

#define BALL_V23 PAD_PCM_A14
#define PAD_PCM_A14 119
#define GPIO_PAD_119 GPIO118
#ifndef BALL_V23_IS_GPIO
#define BALL_V23_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A14_IS_GPIO
#define PAD_PCM_A14_IS_GPIO BALL_V23_IS_GPIO
#endif 

#define BALL_AA22 PAD_PCM_WE_N
#define PAD_PCM_WE_N 120
#define GPIO_PAD_120 GPIO119
#ifndef BALL_AA22_IS_GPIO
#define BALL_AA22_IS_GPIO 0
#endif 
#ifndef PAD_PCM_WE_N_IS_GPIO
#define PAD_PCM_WE_N_IS_GPIO BALL_AA22_IS_GPIO
#endif 

#define BALL_AA23 PAD_PCM_IRQA_N
#define PAD_PCM_IRQA_N 121
#define GPIO_PAD_121 GPIO120
#ifndef BALL_AA23_IS_GPIO
#define BALL_AA23_IS_GPIO 0
#endif 
#ifndef PAD_PCM_IRQA_N_IS_GPIO
#define PAD_PCM_IRQA_N_IS_GPIO BALL_AA23_IS_GPIO
#endif 

#define BALL_AE25 PAD_PCM_A12
#define PAD_PCM_A12 122
#define GPIO_PAD_122 GPIO121
#ifndef BALL_AE25_IS_GPIO
#define BALL_AE25_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A12_IS_GPIO
#define PAD_PCM_A12_IS_GPIO BALL_AE25_IS_GPIO
#endif 

#define BALL_T21 PAD_PCM_A7
#define PAD_PCM_A7 123
#define GPIO_PAD_123 GPIO122
#ifndef BALL_T21_IS_GPIO
#define BALL_T21_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A7_IS_GPIO
#define PAD_PCM_A7_IS_GPIO BALL_T21_IS_GPIO
#endif 

#define BALL_R21 PAD_PCM_A6
#define PAD_PCM_A6 124
#define GPIO_PAD_124 GPIO123
#ifndef BALL_R21_IS_GPIO
#define BALL_R21_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A6_IS_GPIO
#define PAD_PCM_A6_IS_GPIO BALL_R21_IS_GPIO
#endif 

#define BALL_T22 PAD_PCM_A5
#define PAD_PCM_A5 125
#define GPIO_PAD_125 GPIO124
#ifndef BALL_T22_IS_GPIO
#define BALL_T22_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A5_IS_GPIO
#define PAD_PCM_A5_IS_GPIO BALL_T22_IS_GPIO
#endif 

#define BALL_Y22 PAD_PCM_WAIT_N
#define PAD_PCM_WAIT_N 126
#define GPIO_PAD_126 GPIO125
#ifndef BALL_Y22_IS_GPIO
#define BALL_Y22_IS_GPIO 0
#endif 
#ifndef PAD_PCM_WAIT_N_IS_GPIO
#define PAD_PCM_WAIT_N_IS_GPIO BALL_Y22_IS_GPIO
#endif 

#define BALL_U23 PAD_PCM_A4
#define PAD_PCM_A4 127
#define GPIO_PAD_127 GPIO126
#ifndef BALL_U23_IS_GPIO
#define BALL_U23_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A4_IS_GPIO
#define PAD_PCM_A4_IS_GPIO BALL_U23_IS_GPIO
#endif 

#define BALL_R23 PAD_PCM_A3
#define PAD_PCM_A3 128
#define GPIO_PAD_128 GPIO127
#ifndef BALL_R23_IS_GPIO
#define BALL_R23_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A3_IS_GPIO
#define PAD_PCM_A3_IS_GPIO BALL_R23_IS_GPIO
#endif 

#define BALL_U21 PAD_PCM_A2
#define PAD_PCM_A2 129
#define GPIO_PAD_129 GPIO128
#ifndef BALL_U21_IS_GPIO
#define BALL_U21_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A2_IS_GPIO
#define PAD_PCM_A2_IS_GPIO BALL_U21_IS_GPIO
#endif 

#define BALL_Y23 PAD_PCM_REG_N
#define PAD_PCM_REG_N 130
#define GPIO_PAD_130 GPIO129
#ifndef BALL_Y23_IS_GPIO
#define BALL_Y23_IS_GPIO 0
#endif 
#ifndef PAD_PCM_REG_N_IS_GPIO
#define PAD_PCM_REG_N_IS_GPIO BALL_Y23_IS_GPIO
#endif 

#define BALL_T23 PAD_PCM_A1
#define PAD_PCM_A1 131
#define GPIO_PAD_131 GPIO130
#ifndef BALL_T23_IS_GPIO
#define BALL_T23_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A1_IS_GPIO
#define PAD_PCM_A1_IS_GPIO BALL_T23_IS_GPIO
#endif 

#define BALL_U22 PAD_PCM_A0
#define PAD_PCM_A0 132
#define GPIO_PAD_132 GPIO131
#ifndef BALL_U22_IS_GPIO
#define BALL_U22_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A0_IS_GPIO
#define PAD_PCM_A0_IS_GPIO BALL_U22_IS_GPIO
#endif 

#define BALL_AD24 PAD_PCM_D0
#define PAD_PCM_D0 133
#define GPIO_PAD_133 GPIO132
#ifndef BALL_AD24_IS_GPIO
#define BALL_AD24_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D0_IS_GPIO
#define PAD_PCM_D0_IS_GPIO BALL_AD24_IS_GPIO
#endif 

#define BALL_AB26 PAD_PCM_D1
#define PAD_PCM_D1 134
#define GPIO_PAD_134 GPIO133
#ifndef BALL_AB26_IS_GPIO
#define BALL_AB26_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D1_IS_GPIO
#define PAD_PCM_D1_IS_GPIO BALL_AB26_IS_GPIO
#endif 

#define BALL_AF25 PAD_PCM_D2
#define PAD_PCM_D2 135
#define GPIO_PAD_135 GPIO134
#ifndef BALL_AF25_IS_GPIO
#define BALL_AF25_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D2_IS_GPIO
#define PAD_PCM_D2_IS_GPIO BALL_AF25_IS_GPIO
#endif 

#define BALL_Y21 PAD_PCM_RESET
#define PAD_PCM_RESET 136
#define GPIO_PAD_136 GPIO135
#ifndef BALL_Y21_IS_GPIO
#define BALL_Y21_IS_GPIO 0
#endif 
#ifndef PAD_PCM_RESET_IS_GPIO
#define PAD_PCM_RESET_IS_GPIO BALL_Y21_IS_GPIO
#endif 

#define BALL_AF24 PAD_PCM_CD_N
#define PAD_PCM_CD_N 137
#define GPIO_PAD_137 GPIO136
#ifndef BALL_AF24_IS_GPIO
#define BALL_AF24_IS_GPIO 0
#endif 
#ifndef PAD_PCM_CD_N_IS_GPIO
#define PAD_PCM_CD_N_IS_GPIO BALL_AF24_IS_GPIO
#endif 

#define BALL_AC25 PAD_PCM2_CE_N
#define PAD_PCM2_CE_N 138
#define GPIO_PAD_138 GPIO137
#ifndef BALL_AC25_IS_GPIO
#define BALL_AC25_IS_GPIO 0
#endif 
#ifndef PAD_PCM2_CE_N_IS_GPIO
#define PAD_PCM2_CE_N_IS_GPIO BALL_AC25_IS_GPIO
#endif 

#define BALL_M22 PAD_PCM2_IRQA_N
#define PAD_PCM2_IRQA_N 139
#define GPIO_PAD_139 GPIO138
#ifndef BALL_M22_IS_GPIO
#define BALL_M22_IS_GPIO 0
#endif 
#ifndef PAD_PCM2_IRQA_N_IS_GPIO
#define PAD_PCM2_IRQA_N_IS_GPIO BALL_M22_IS_GPIO
#endif 

#define BALL_AA25 PAD_PCM2_WAIT_N
#define PAD_PCM2_WAIT_N 140
#define GPIO_PAD_140 GPIO139
#ifndef BALL_AA25_IS_GPIO
#define BALL_AA25_IS_GPIO 0
#endif 
#ifndef PAD_PCM2_WAIT_N_IS_GPIO
#define PAD_PCM2_WAIT_N_IS_GPIO BALL_AA25_IS_GPIO
#endif 

#define BALL_AB24 PAD_PCM2_RESET
#define PAD_PCM2_RESET 141
#define GPIO_PAD_141 GPIO140
#ifndef BALL_AB24_IS_GPIO
#define BALL_AB24_IS_GPIO 0
#endif 
#ifndef PAD_PCM2_RESET_IS_GPIO
#define PAD_PCM2_RESET_IS_GPIO BALL_AB24_IS_GPIO
#endif 

#define BALL_AC24 PAD_PCM2_CD_N
#define PAD_PCM2_CD_N 142
#define GPIO_PAD_142 GPIO141
#ifndef BALL_AC24_IS_GPIO
#define BALL_AC24_IS_GPIO 0
#endif 
#ifndef PAD_PCM2_CD_N_IS_GPIO
#define PAD_PCM2_CD_N_IS_GPIO BALL_AC24_IS_GPIO
#endif 

#define BALL_W22 PAD_NAND_CEZ
#define PAD_NAND_CEZ 159
#define GPIO_PAD_159 GPIO158
#ifndef BALL_W22_IS_GPIO
#define BALL_W22_IS_GPIO 0
#endif 
#ifndef PAD_NAND_CEZ_IS_GPIO
#define PAD_NAND_CEZ_IS_GPIO BALL_W22_IS_GPIO
#endif 

#define BALL_W21 PAD_NAND_CEZ1
#define PAD_NAND_CEZ1 160
#define GPIO_PAD_160 GPIO159
#ifndef BALL_W21_IS_GPIO
#define BALL_W21_IS_GPIO 0
#endif 
#ifndef PAD_NAND_CEZ1_IS_GPIO
#define PAD_NAND_CEZ1_IS_GPIO BALL_W21_IS_GPIO
#endif 

#define BALL_Y24 PAD_ONE_A15
#define PAD_ONE_A15 161
#define GPIO_PAD_161 GPIO160
#ifndef BALL_Y24_IS_GPIO
#define BALL_Y24_IS_GPIO 0
#endif 
#ifndef PAD_ONE_A15_IS_GPIO
#define PAD_ONE_A15_IS_GPIO BALL_Y24_IS_GPIO
#endif 

#define BALL_Y25 PAD_ONE_D13
#define PAD_ONE_D13 162
#define GPIO_PAD_162 GPIO161
#ifndef BALL_Y25_IS_GPIO
#define BALL_Y25_IS_GPIO 0
#endif 
#ifndef PAD_ONE_D13_IS_GPIO
#define PAD_ONE_D13_IS_GPIO BALL_Y25_IS_GPIO
#endif 

#define BALL_AA24 PAD_ONE_D14
#define PAD_ONE_D14 163
#define GPIO_PAD_163 GPIO162
#ifndef BALL_AA24_IS_GPIO
#define BALL_AA24_IS_GPIO 0
#endif 
#ifndef PAD_ONE_D14_IS_GPIO
#define PAD_ONE_D14_IS_GPIO BALL_AA24_IS_GPIO
#endif 

#define BALL_AE26 PAD_ONE_D15
#define PAD_ONE_D15 164
#define GPIO_PAD_164 GPIO163
#ifndef BALL_AE26_IS_GPIO
#define BALL_AE26_IS_GPIO 0
#endif 
#ifndef PAD_ONE_D15_IS_GPIO
#define PAD_ONE_D15_IS_GPIO BALL_AE26_IS_GPIO
#endif 

#define BALL_AE24 PAD_ONE_CLK
#define PAD_ONE_CLK 165
#define GPIO_PAD_165 GPIO164
#ifndef BALL_AE24_IS_GPIO
#define BALL_AE24_IS_GPIO 0
#endif 
#ifndef PAD_ONE_CLK_IS_GPIO
#define PAD_ONE_CLK_IS_GPIO BALL_AE24_IS_GPIO
#endif 

#define BALL_P21 PAD_ONE_CEN
#define PAD_ONE_CEN 166
#define GPIO_PAD_166 GPIO165
#ifndef BALL_P21_IS_GPIO
#define BALL_P21_IS_GPIO 0
#endif 
#ifndef PAD_ONE_CEN_IS_GPIO
#define PAD_ONE_CEN_IS_GPIO BALL_P21_IS_GPIO
#endif 

#define BALL_AA26 PAD_ONE_OEN
#define PAD_ONE_OEN 167
#define GPIO_PAD_167 GPIO166
#ifndef BALL_AA26_IS_GPIO
#define BALL_AA26_IS_GPIO 0
#endif 
#ifndef PAD_ONE_OEN_IS_GPIO
#define PAD_ONE_OEN_IS_GPIO BALL_AA26_IS_GPIO
#endif 

#define BALL_AC26 PAD_ONE_WEN
#define PAD_ONE_WEN 168
#define GPIO_PAD_168 GPIO167
#ifndef BALL_AC26_IS_GPIO
#define BALL_AC26_IS_GPIO 0
#endif 
#ifndef PAD_ONE_WEN_IS_GPIO
#define PAD_ONE_WEN_IS_GPIO BALL_AC26_IS_GPIO
#endif 

#define BALL_AB25 PAD_ONE_RPN
#define PAD_ONE_RPN 169
#define GPIO_PAD_169 GPIO168
#ifndef BALL_AB25_IS_GPIO
#define BALL_AB25_IS_GPIO 0
#endif 
#ifndef PAD_ONE_RPN_IS_GPIO
#define PAD_ONE_RPN_IS_GPIO BALL_AB25_IS_GPIO
#endif 

#define BALL_M21 PAD_ONE_AVDN
#define PAD_ONE_AVDN 170
#define GPIO_PAD_170 GPIO169
#ifndef BALL_M21_IS_GPIO
#define BALL_M21_IS_GPIO 0
#endif 
#ifndef PAD_ONE_AVDN_IS_GPIO
#define PAD_ONE_AVDN_IS_GPIO BALL_M21_IS_GPIO
#endif 

#define BALL_V21 PAD_ONE_INT
#define PAD_ONE_INT 171
#define GPIO_PAD_171 GPIO170
#ifndef BALL_V21_IS_GPIO
#define BALL_V21_IS_GPIO 0
#endif 
#ifndef PAD_ONE_INT_IS_GPIO
#define PAD_ONE_INT_IS_GPIO BALL_V21_IS_GPIO
#endif 

#define BALL_V22 PAD_ONE_RDY
#define PAD_ONE_RDY 172
#define GPIO_PAD_172 GPIO171
#ifndef BALL_V22_IS_GPIO
#define BALL_V22_IS_GPIO 0
#endif 
#ifndef PAD_ONE_RDY_IS_GPIO
#define PAD_ONE_RDY_IS_GPIO BALL_V22_IS_GPIO
#endif 

#define BALL_AF13 PAD_GPIO0
#define PAD_GPIO0 39
#define GPIO_PAD_39 GPIO38
#ifndef BALL_AF13_IS_GPIO
#define BALL_AF13_IS_GPIO 0
#endif 
#ifndef PAD_GPIO0_IS_GPIO
#define PAD_GPIO0_IS_GPIO BALL_AF13_IS_GPIO
#endif 

#define BALL_AF14 PAD_GPIO1
#define PAD_GPIO1 40
#define GPIO_PAD_40 GPIO39
#ifndef BALL_AF14_IS_GPIO
#define BALL_AF14_IS_GPIO 0
#endif 
#ifndef PAD_GPIO1_IS_GPIO
#define PAD_GPIO1_IS_GPIO BALL_AF14_IS_GPIO
#endif 

#define BALL_AC13 PAD_GPIO2
#define PAD_GPIO2 41
#define GPIO_PAD_41 GPIO40
#ifndef BALL_AC13_IS_GPIO
#define BALL_AC13_IS_GPIO 0
#endif 
#ifndef PAD_GPIO2_IS_GPIO
#define PAD_GPIO2_IS_GPIO BALL_AC13_IS_GPIO
#endif 

#define BALL_AE14 PAD_GPIO3
#define PAD_GPIO3 42
#define GPIO_PAD_42 GPIO41
#ifndef BALL_AE14_IS_GPIO
#define BALL_AE14_IS_GPIO 0
#endif 
#ifndef PAD_GPIO3_IS_GPIO
#define PAD_GPIO3_IS_GPIO BALL_AE14_IS_GPIO
#endif 

#define BALL_AB14 PAD_GPIO4
#define PAD_GPIO4 43
#define GPIO_PAD_43 GPIO42
#ifndef BALL_AB14_IS_GPIO
#define BALL_AB14_IS_GPIO 0
#endif 
#ifndef PAD_GPIO4_IS_GPIO
#define PAD_GPIO4_IS_GPIO BALL_AB14_IS_GPIO
#endif 

#define BALL_AC14 PAD_GPIO5
#define PAD_GPIO5 44
#define GPIO_PAD_44 GPIO43
#ifndef BALL_AC14_IS_GPIO
#define BALL_AC14_IS_GPIO 0
#endif 
#ifndef PAD_GPIO5_IS_GPIO
#define PAD_GPIO5_IS_GPIO BALL_AC14_IS_GPIO
#endif 

#define BALL_AD13 PAD_GPIO6
#define PAD_GPIO6 45
#define GPIO_PAD_45 GPIO44
#ifndef BALL_AD13_IS_GPIO
#define BALL_AD13_IS_GPIO 0
#endif 
#ifndef PAD_GPIO6_IS_GPIO
#define PAD_GPIO6_IS_GPIO BALL_AD13_IS_GPIO
#endif 

#define BALL_AB10 PAD_GPIO7
#define PAD_GPIO7 46
#define GPIO_PAD_46 GPIO45
#ifndef BALL_AB10_IS_GPIO
#define BALL_AB10_IS_GPIO 0
#endif 
#ifndef PAD_GPIO7_IS_GPIO
#define PAD_GPIO7_IS_GPIO BALL_AB10_IS_GPIO
#endif 

#define BALL_AC10 PAD_GPIO8
#define PAD_GPIO8 47
#define GPIO_PAD_47 GPIO46
#ifndef BALL_AC10_IS_GPIO
#define BALL_AC10_IS_GPIO 0
#endif 
#ifndef PAD_GPIO8_IS_GPIO
#define PAD_GPIO8_IS_GPIO BALL_AC10_IS_GPIO
#endif 

#define BALL_AC11 PAD_GPIO9
#define PAD_GPIO9 48
#define GPIO_PAD_48 GPIO47
#ifndef BALL_AC11_IS_GPIO
#define BALL_AC11_IS_GPIO 0
#endif 
#ifndef PAD_GPIO9_IS_GPIO
#define PAD_GPIO9_IS_GPIO BALL_AC11_IS_GPIO
#endif 

#define BALL_H21 PAD_GPIO10
#define PAD_GPIO10 49
#define GPIO_PAD_49 GPIO48
#ifndef BALL_H21_IS_GPIO
#define BALL_H21_IS_GPIO 0
#endif 
#ifndef PAD_GPIO10_IS_GPIO
#define PAD_GPIO10_IS_GPIO BALL_H21_IS_GPIO
#endif 

#define BALL_J20 PAD_GPIO11
#define PAD_GPIO11 50
#define GPIO_PAD_50 GPIO49
#ifndef BALL_J20_IS_GPIO
#define BALL_J20_IS_GPIO 0
#endif 
#ifndef PAD_GPIO11_IS_GPIO
#define PAD_GPIO11_IS_GPIO BALL_J20_IS_GPIO
#endif 

#define BALL_AB11 PAD_GPIO12
#define PAD_GPIO12 51
#define GPIO_PAD_51 GPIO50
#ifndef BALL_AB11_IS_GPIO
#define BALL_AB11_IS_GPIO 0
#endif 
#ifndef PAD_GPIO12_IS_GPIO
#define PAD_GPIO12_IS_GPIO BALL_AB11_IS_GPIO
#endif 

#define BALL_AB13 PAD_GPIO13
#define PAD_GPIO13 52
#define GPIO_PAD_52 GPIO51
#ifndef BALL_AB13_IS_GPIO
#define BALL_AB13_IS_GPIO 0
#endif 
#ifndef PAD_GPIO13_IS_GPIO
#define PAD_GPIO13_IS_GPIO BALL_AB13_IS_GPIO
#endif 

#define BALL_AC17 PAD_GPIO14
#define PAD_GPIO14 53
#define GPIO_PAD_53 GPIO52
#ifndef BALL_AC17_IS_GPIO
#define BALL_AC17_IS_GPIO 0
#endif 
#ifndef PAD_GPIO14_IS_GPIO
#define PAD_GPIO14_IS_GPIO BALL_AC17_IS_GPIO
#endif 

#define BALL_AC18 PAD_GPIO15
#define PAD_GPIO15 54
#define GPIO_PAD_54 GPIO53
#ifndef BALL_AC18_IS_GPIO
#define BALL_AC18_IS_GPIO 0
#endif 
#ifndef PAD_GPIO15_IS_GPIO
#define PAD_GPIO15_IS_GPIO BALL_AC18_IS_GPIO
#endif 

#define BALL_AB17 PAD_GPIO16
#define PAD_GPIO16 55
#define GPIO_PAD_55 GPIO54
#ifndef BALL_AB17_IS_GPIO
#define BALL_AB17_IS_GPIO 0
#endif 
#ifndef PAD_GPIO16_IS_GPIO
#define PAD_GPIO16_IS_GPIO BALL_AB17_IS_GPIO
#endif 

#define BALL_AB18 PAD_GPIO17
#define PAD_GPIO17 56
#define GPIO_PAD_56 GPIO55
#ifndef BALL_AB18_IS_GPIO
#define BALL_AB18_IS_GPIO 0
#endif 
#ifndef PAD_GPIO17_IS_GPIO
#define PAD_GPIO17_IS_GPIO BALL_AB18_IS_GPIO
#endif 

#define BALL_AA17 PAD_GPIO18
#define PAD_GPIO18 57
#define GPIO_PAD_57 GPIO56
#ifndef BALL_AA17_IS_GPIO
#define BALL_AA17_IS_GPIO 0
#endif 
#ifndef PAD_GPIO18_IS_GPIO
#define PAD_GPIO18_IS_GPIO BALL_AA17_IS_GPIO
#endif 

#define BALL_AA18 PAD_GPIO19
#define PAD_GPIO19 58
#define GPIO_PAD_58 GPIO57
#ifndef BALL_AA18_IS_GPIO
#define BALL_AA18_IS_GPIO 0
#endif 
#ifndef PAD_GPIO19_IS_GPIO
#define PAD_GPIO19_IS_GPIO BALL_AA18_IS_GPIO
#endif 

#define BALL_AC20 PAD_GPIO20
#define PAD_GPIO20 59
#define GPIO_PAD_59 GPIO58
#ifndef BALL_AC20_IS_GPIO
#define BALL_AC20_IS_GPIO 0
#endif 
#ifndef PAD_GPIO20_IS_GPIO
#define PAD_GPIO20_IS_GPIO BALL_AC20_IS_GPIO
#endif 

#define BALL_AB21 PAD_GPIO21
#define PAD_GPIO21 60
#define GPIO_PAD_60 GPIO59
#ifndef BALL_AB21_IS_GPIO
#define BALL_AB21_IS_GPIO 0
#endif 
#ifndef PAD_GPIO21_IS_GPIO
#define PAD_GPIO21_IS_GPIO BALL_AB21_IS_GPIO
#endif 

#define BALL_AC21 PAD_GPIO22
#define PAD_GPIO22 61
#define GPIO_PAD_61 GPIO60
#ifndef BALL_AC21_IS_GPIO
#define BALL_AC21_IS_GPIO 0
#endif 
#ifndef PAD_GPIO22_IS_GPIO
#define PAD_GPIO22_IS_GPIO BALL_AC21_IS_GPIO
#endif 

#define BALL_AC22 PAD_GPIO23
#define PAD_GPIO23 62
#define GPIO_PAD_62 GPIO61
#ifndef BALL_AC22_IS_GPIO
#define BALL_AC22_IS_GPIO 0
#endif 
#ifndef PAD_GPIO23_IS_GPIO
#define PAD_GPIO23_IS_GPIO BALL_AC22_IS_GPIO
#endif 

#define BALL_AB19 PAD_GPIO24
#define PAD_GPIO24 63
#define GPIO_PAD_63 GPIO62
#ifndef BALL_AB19_IS_GPIO
#define BALL_AB19_IS_GPIO 0
#endif 
#ifndef PAD_GPIO24_IS_GPIO
#define PAD_GPIO24_IS_GPIO BALL_AB19_IS_GPIO
#endif 

#define BALL_AA19 PAD_GPIO25
#define PAD_GPIO25 64
#define GPIO_PAD_64 GPIO63
#ifndef BALL_AA19_IS_GPIO
#define BALL_AA19_IS_GPIO 0
#endif 
#ifndef PAD_GPIO25_IS_GPIO
#define PAD_GPIO25_IS_GPIO BALL_AA19_IS_GPIO
#endif 

#define BALL_AB20 PAD_GPIO26
#define PAD_GPIO26 65
#define GPIO_PAD_65 GPIO64
#ifndef BALL_AB20_IS_GPIO
#define BALL_AB20_IS_GPIO 0
#endif 
#ifndef PAD_GPIO26_IS_GPIO
#define PAD_GPIO26_IS_GPIO BALL_AB20_IS_GPIO
#endif 

#define BALL_AA20 PAD_GPIO27
#define PAD_GPIO27 66
#define GPIO_PAD_66 GPIO65
#ifndef BALL_AA20_IS_GPIO
#define BALL_AA20_IS_GPIO 0
#endif 
#ifndef PAD_GPIO27_IS_GPIO
#define PAD_GPIO27_IS_GPIO BALL_AA20_IS_GPIO
#endif 

#define BALL_AF22 PAD_PWM0
#define PAD_PWM0 175
#define GPIO_PAD_175 GPIO174
#ifndef BALL_AF22_IS_GPIO
#define BALL_AF22_IS_GPIO 0
#endif 
#ifndef PAD_PWM0_IS_GPIO
#define PAD_PWM0_IS_GPIO BALL_AF22_IS_GPIO
#endif 

#define BALL_AF23 PAD_PWM3
#define PAD_PWM3 178
#define GPIO_PAD_178 GPIO177
#ifndef BALL_AF23_IS_GPIO
#define BALL_AF23_IS_GPIO 0
#endif 
#ifndef PAD_PWM3_IS_GPIO
#define PAD_PWM3_IS_GPIO BALL_AF23_IS_GPIO
#endif 

#define BALL_AE22 PAD_PWM1
#define PAD_PWM1 176
#define GPIO_PAD_176 GPIO175
#ifndef BALL_AE22_IS_GPIO
#define BALL_AE22_IS_GPIO 0
#endif 
#ifndef PAD_PWM1_IS_GPIO
#define PAD_PWM1_IS_GPIO BALL_AE22_IS_GPIO
#endif 

#define BALL_AD23 PAD_PWM4
#define PAD_PWM4 179
#define GPIO_PAD_179 GPIO178
#ifndef BALL_AD23_IS_GPIO
#define BALL_AD23_IS_GPIO 0
#endif 
#ifndef PAD_PWM4_IS_GPIO
#define PAD_PWM4_IS_GPIO BALL_AD23_IS_GPIO
#endif 

#define BALL_AE23 PAD_PWM2
#define PAD_PWM2 177
#define GPIO_PAD_177 GPIO176
#ifndef BALL_AE23_IS_GPIO
#define BALL_AE23_IS_GPIO 0
#endif 
#ifndef PAD_PWM2_IS_GPIO
#define PAD_PWM2_IS_GPIO BALL_AE23_IS_GPIO
#endif 

#define BALL_H22 PAD_DDCR_DA
#define PAD_DDCR_DA 173
#define GPIO_PAD_173 GPIO172
#ifndef BALL_H22_IS_GPIO
#define BALL_H22_IS_GPIO 0
#endif 
#ifndef PAD_DDCR_DA_IS_GPIO
#define PAD_DDCR_DA_IS_GPIO BALL_H22_IS_GPIO
#endif 

#define BALL_H23 PAD_DDCR_CK
#define PAD_DDCR_CK 174
#define GPIO_PAD_174 GPIO173
#ifndef BALL_H23_IS_GPIO
#define BALL_H23_IS_GPIO 0
#endif 
#ifndef PAD_DDCR_CK_IS_GPIO
#define PAD_DDCR_CK_IS_GPIO BALL_H23_IS_GPIO
#endif 

#define BALL_E6 PAD_I2S_IN_WS
#define PAD_I2S_IN_WS 93
#define GPIO_PAD_93 GPIO92
#ifndef BALL_E6_IS_GPIO
#define BALL_E6_IS_GPIO 0
#endif 
#ifndef PAD_I2S_IN_WS_IS_GPIO
#define PAD_I2S_IN_WS_IS_GPIO BALL_E6_IS_GPIO
#endif 

#define BALL_D7 PAD_I2S_IN_BCK
#define PAD_I2S_IN_BCK 94
#define GPIO_PAD_94 GPIO93
#ifndef BALL_D7_IS_GPIO
#define BALL_D7_IS_GPIO 0
#endif 
#ifndef PAD_I2S_IN_BCK_IS_GPIO
#define PAD_I2S_IN_BCK_IS_GPIO BALL_D7_IS_GPIO
#endif 

#define BALL_E7 PAD_I2S_IN_SD
#define PAD_I2S_IN_SD 95
#define GPIO_PAD_95 GPIO94
#ifndef BALL_E7_IS_GPIO
#define BALL_E7_IS_GPIO 0
#endif 
#ifndef PAD_I2S_IN_SD_IS_GPIO
#define PAD_I2S_IN_SD_IS_GPIO BALL_E7_IS_GPIO
#endif 

#define BALL_J21 PAD_I2S_OUT_MCK
#define PAD_I2S_OUT_MCK 99
#define GPIO_PAD_99 GPIO98
#ifndef BALL_J21_IS_GPIO
#define BALL_J21_IS_GPIO 0
#endif 
#ifndef PAD_I2S_OUT_MCK_IS_GPIO
#define PAD_I2S_OUT_MCK_IS_GPIO BALL_J21_IS_GPIO
#endif 

#define BALL_K21 PAD_I2S_OUT_WS
#define PAD_I2S_OUT_WS 98
#define GPIO_PAD_98 GPIO97
#ifndef BALL_K21_IS_GPIO
#define BALL_K21_IS_GPIO 0
#endif 
#ifndef PAD_I2S_OUT_WS_IS_GPIO
#define PAD_I2S_OUT_WS_IS_GPIO BALL_K21_IS_GPIO
#endif 

#define BALL_K20 PAD_I2S_OUT_SD1
#define PAD_I2S_OUT_SD1 102
#define GPIO_PAD_102 GPIO101
#ifndef BALL_K20_IS_GPIO
#define BALL_K20_IS_GPIO 0
#endif 
#ifndef PAD_I2S_OUT_SD1_IS_GPIO
#define PAD_I2S_OUT_SD1_IS_GPIO BALL_K20_IS_GPIO
#endif 

#define BALL_K22 PAD_I2S_OUT_BCK
#define PAD_I2S_OUT_BCK 100
#define GPIO_PAD_100 GPIO99
#ifndef BALL_K22_IS_GPIO
#define BALL_K22_IS_GPIO 0
#endif 
#ifndef PAD_I2S_OUT_BCK_IS_GPIO
#define PAD_I2S_OUT_BCK_IS_GPIO BALL_K22_IS_GPIO
#endif 

#define BALL_J22 PAD_I2S_OUT_SD
#define PAD_I2S_OUT_SD 101
#define GPIO_PAD_101 GPIO100
#ifndef BALL_J22_IS_GPIO
#define BALL_J22_IS_GPIO 0
#endif 
#ifndef PAD_I2S_OUT_SD_IS_GPIO
#define PAD_I2S_OUT_SD_IS_GPIO BALL_J22_IS_GPIO
#endif 

#define BALL_J23 PAD_I2S_OUT_SD2
#define PAD_I2S_OUT_SD2 103
#define GPIO_PAD_103 GPIO102
#ifndef BALL_J23_IS_GPIO
#define BALL_J23_IS_GPIO 0
#endif 
#ifndef PAD_I2S_OUT_SD2_IS_GPIO
#define PAD_I2S_OUT_SD2_IS_GPIO BALL_J23_IS_GPIO
#endif 

#define BALL_K23 PAD_I2S_OUT_SD3
#define PAD_I2S_OUT_SD3 104
#define GPIO_PAD_104 GPIO103
#ifndef BALL_K23_IS_GPIO
#define BALL_K23_IS_GPIO 0
#endif 
#ifndef PAD_I2S_OUT_SD3_IS_GPIO
#define PAD_I2S_OUT_SD3_IS_GPIO BALL_K23_IS_GPIO
#endif 

#define BALL_A8 PAD_TCON0
#define PAD_TCON0 184
#define GPIO_PAD_184 GPIO183
#ifndef BALL_A8_IS_GPIO
#define BALL_A8_IS_GPIO 0
#endif 
#ifndef PAD_TCON0_IS_GPIO
#define PAD_TCON0_IS_GPIO BALL_A8_IS_GPIO
#endif 

#define BALL_A9 PAD_TCON01
#define PAD_TCON01 185
#define GPIO_PAD_185 GPIO184
#ifndef BALL_A9_IS_GPIO
#define BALL_A9_IS_GPIO 0
#endif 
#ifndef PAD_TCON01_IS_GPIO
#define PAD_TCON01_IS_GPIO BALL_A9_IS_GPIO
#endif 

#define BALL_A10 PAD_TCON02
#define PAD_TCON02 186
#define GPIO_PAD_186 GPIO185
#ifndef BALL_A10_IS_GPIO
#define BALL_A10_IS_GPIO 0
#endif 
#ifndef PAD_TCON02_IS_GPIO
#define PAD_TCON02_IS_GPIO BALL_A10_IS_GPIO
#endif 

#define BALL_A11 PAD_TCON03
#define PAD_TCON03 187
#define GPIO_PAD_187 GPIO186
#ifndef BALL_A11_IS_GPIO
#define BALL_A11_IS_GPIO 0
#endif 
#ifndef PAD_TCON03_IS_GPIO
#define PAD_TCON03_IS_GPIO BALL_A11_IS_GPIO
#endif 

#define BALL_B8 PAD_TCON04
#define PAD_TCON04 188
#define GPIO_PAD_188 GPIO187
#ifndef BALL_B8_IS_GPIO
#define BALL_B8_IS_GPIO 0
#endif 
#ifndef PAD_TCON04_IS_GPIO
#define PAD_TCON04_IS_GPIO BALL_B8_IS_GPIO
#endif 

#define BALL_B9 PAD_TCON05
#define PAD_TCON05 189
#define GPIO_PAD_189 GPIO188
#ifndef BALL_B9_IS_GPIO
#define BALL_B9_IS_GPIO 0
#endif 
#ifndef PAD_TCON05_IS_GPIO
#define PAD_TCON05_IS_GPIO BALL_B9_IS_GPIO
#endif 

#define PAD_TCON06 9999
#ifndef PAD_TCON06_IS_GPIO
#define PAD_TCON06_IS_GPIO 0
#endif 

#define PAD_TCON07 9999
#ifndef PAD_TCON07_IS_GPIO
#define PAD_TCON07_IS_GPIO 0
#endif 

#define PAD_TCON08 9999
#ifndef PAD_TCON08_IS_GPIO
#define PAD_TCON08_IS_GPIO 0
#endif 

#define BALL_B10 PAD_TCON09
#define PAD_TCON09 193
#define GPIO_PAD_193 GPIO192
#ifndef BALL_B10_IS_GPIO
#define BALL_B10_IS_GPIO 0
#endif 
#ifndef PAD_TCON09_IS_GPIO
#define PAD_TCON09_IS_GPIO BALL_B10_IS_GPIO
#endif 

#define BALL_B11 PAD_TCON10
#define PAD_TCON10 194
#define GPIO_PAD_194 GPIO193
#ifndef BALL_B11_IS_GPIO
#define BALL_B11_IS_GPIO 0
#endif 
#ifndef PAD_TCON10_IS_GPIO
#define PAD_TCON10_IS_GPIO BALL_B11_IS_GPIO
#endif 

#define BALL_C8 PAD_TCON11
#define PAD_TCON11 195
#define GPIO_PAD_195 GPIO194
#ifndef BALL_C8_IS_GPIO
#define BALL_C8_IS_GPIO 0
#endif 
#ifndef PAD_TCON11_IS_GPIO
#define PAD_TCON11_IS_GPIO BALL_C8_IS_GPIO
#endif 

#define BALL_C9 PAD_TCON12
#define PAD_TCON12 196
#define GPIO_PAD_196 GPIO195
#ifndef BALL_C9_IS_GPIO
#define BALL_C9_IS_GPIO 0
#endif 
#ifndef PAD_TCON12_IS_GPIO
#define PAD_TCON12_IS_GPIO BALL_C9_IS_GPIO
#endif 

#define BALL_C10 PAD_TCON13
#define PAD_TCON13 197
#define GPIO_PAD_197 GPIO196
#ifndef BALL_C10_IS_GPIO
#define BALL_C10_IS_GPIO 0
#endif 
#ifndef PAD_TCON13_IS_GPIO
#define PAD_TCON13_IS_GPIO BALL_C10_IS_GPIO
#endif 

#define BALL_C11 PAD_TCON14
#define PAD_TCON14 198
#define GPIO_PAD_198 GPIO197
#ifndef BALL_C11_IS_GPIO
#define BALL_C11_IS_GPIO 0
#endif 
#ifndef PAD_TCON14_IS_GPIO
#define PAD_TCON14_IS_GPIO BALL_C11_IS_GPIO
#endif 

#define BALL_L26 PAD_TCON15
#define PAD_TCON15 199
#define GPIO_PAD_199 GPIO198
#ifndef BALL_L26_IS_GPIO
#define BALL_L26_IS_GPIO 0
#endif 
#ifndef PAD_TCON15_IS_GPIO
#define PAD_TCON15_IS_GPIO BALL_L26_IS_GPIO
#endif 

#define PAD_TCON16 9999
#ifndef PAD_TCON16_IS_GPIO
#define PAD_TCON16_IS_GPIO 0
#endif 

#define BALL_L25 PAD_TCON17
#define PAD_TCON17 201
#define GPIO_PAD_201 GPIO200
#ifndef BALL_L25_IS_GPIO
#define BALL_L25_IS_GPIO 0
#endif 
#ifndef PAD_TCON17_IS_GPIO
#define PAD_TCON17_IS_GPIO BALL_L25_IS_GPIO
#endif 

#define PAD_TCON18 9999
#ifndef PAD_TCON18_IS_GPIO
#define PAD_TCON18_IS_GPIO 0
#endif 

#define PAD_TCON19 9999
#ifndef PAD_TCON19_IS_GPIO
#define PAD_TCON19_IS_GPIO 0
#endif 

#define BALL_L24 PAD_TCON20
#define PAD_TCON20 204
#define GPIO_PAD_204 GPIO203
#ifndef BALL_L24_IS_GPIO
#define BALL_L24_IS_GPIO 0
#endif 
#ifndef PAD_TCON20_IS_GPIO
#define PAD_TCON20_IS_GPIO BALL_L24_IS_GPIO
#endif 

#define BALL_M26 PAD_TCON21
#define PAD_TCON21 205
#define GPIO_PAD_205 GPIO204
#ifndef BALL_M26_IS_GPIO
#define BALL_M26_IS_GPIO 0
#endif 
#ifndef PAD_TCON21_IS_GPIO
#define PAD_TCON21_IS_GPIO BALL_M26_IS_GPIO
#endif 

#define BALL_B3 PAD_MPIF_CLK
#define PAD_MPIF_CLK 152
#define GPIO_PAD_152 GPIO151
#ifndef BALL_B3_IS_GPIO
#define BALL_B3_IS_GPIO 0
#endif 
#ifndef PAD_MPIF_CLK_IS_GPIO
#define PAD_MPIF_CLK_IS_GPIO BALL_B3_IS_GPIO
#endif 

#define BALL_C3 PAD_MPIF_D3
#define PAD_MPIF_D3 158
#define GPIO_PAD_158 GPIO157
#ifndef BALL_C3_IS_GPIO
#define BALL_C3_IS_GPIO 0
#endif 
#ifndef PAD_MPIF_D3_IS_GPIO
#define PAD_MPIF_D3_IS_GPIO BALL_C3_IS_GPIO
#endif 

#define BALL_D4 PAD_MPIF_D2
#define PAD_MPIF_D2 157
#define GPIO_PAD_157 GPIO156
#ifndef BALL_D4_IS_GPIO
#define BALL_D4_IS_GPIO 0
#endif 
#ifndef PAD_MPIF_D2_IS_GPIO
#define PAD_MPIF_D2_IS_GPIO BALL_D4_IS_GPIO
#endif 

#define BALL_E4 PAD_MPIF_D1
#define PAD_MPIF_D1 156
#define GPIO_PAD_156 GPIO155
#ifndef BALL_E4_IS_GPIO
#define BALL_E4_IS_GPIO 0
#endif 
#ifndef PAD_MPIF_D1_IS_GPIO
#define PAD_MPIF_D1_IS_GPIO BALL_E4_IS_GPIO
#endif 

#define BALL_B4 PAD_MPIF_D0
#define PAD_MPIF_D0 155
#define GPIO_PAD_155 GPIO154
#ifndef BALL_B4_IS_GPIO
#define BALL_B4_IS_GPIO 0
#endif 
#ifndef PAD_MPIF_D0_IS_GPIO
#define PAD_MPIF_D0_IS_GPIO BALL_B4_IS_GPIO
#endif 

#define BALL_A4 PAD_MPIF_CS_N
#define PAD_MPIF_CS_N 154
#define GPIO_PAD_154 GPIO153
#ifndef BALL_A4_IS_GPIO
#define BALL_A4_IS_GPIO 0
#endif 
#ifndef PAD_MPIF_CS_N_IS_GPIO
#define PAD_MPIF_CS_N_IS_GPIO BALL_A4_IS_GPIO
#endif 

#define BALL_C4 PAD_MPIF_BUSY_ERR
#define PAD_MPIF_BUSY_ERR 153
#define GPIO_PAD_153 GPIO152
#ifndef BALL_C4_IS_GPIO
#define BALL_C4_IS_GPIO 0
#endif 
#ifndef PAD_MPIF_BUSY_ERR_IS_GPIO
#define PAD_MPIF_BUSY_ERR_IS_GPIO BALL_C4_IS_GPIO
#endif 

#define BALL_A5 PAD_SPDIF_IN
#define PAD_SPDIF_IN 96
#define GPIO_PAD_96 GPIO95
#ifndef BALL_A5_IS_GPIO
#define BALL_A5_IS_GPIO 0
#endif 
#ifndef PAD_SPDIF_IN_IS_GPIO
#define PAD_SPDIF_IN_IS_GPIO BALL_A5_IS_GPIO
#endif 

#define BALL_B5 PAD_SPDIF_OUT
#define PAD_SPDIF_OUT 97
#define GPIO_PAD_97 GPIO96
#ifndef BALL_B5_IS_GPIO
#define BALL_B5_IS_GPIO 0
#endif 
#ifndef PAD_SPDIF_OUT_IS_GPIO
#define PAD_SPDIF_OUT_IS_GPIO BALL_B5_IS_GPIO
#endif 

#define BALL_F5 PAD_ET_COL
#define PAD_ET_COL 151
#define GPIO_PAD_151 GPIO150
#ifndef BALL_F5_IS_GPIO
#define BALL_F5_IS_GPIO 0
#endif 
#ifndef PAD_ET_COL_IS_GPIO
#define PAD_ET_COL_IS_GPIO BALL_F5_IS_GPIO
#endif 

#define BALL_H6 PAD_ET_TXD1
#define PAD_ET_TXD1 149
#define GPIO_PAD_149 GPIO148
#ifndef BALL_H6_IS_GPIO
#define BALL_H6_IS_GPIO 0
#endif 
#ifndef PAD_ET_TXD1_IS_GPIO
#define PAD_ET_TXD1_IS_GPIO BALL_H6_IS_GPIO
#endif 

#define BALL_H7 PAD_ET_TXD0
#define PAD_ET_TXD0 148
#define GPIO_PAD_148 GPIO147
#ifndef BALL_H7_IS_GPIO
#define BALL_H7_IS_GPIO 0
#endif 
#ifndef PAD_ET_TXD0_IS_GPIO
#define PAD_ET_TXD0_IS_GPIO BALL_H7_IS_GPIO
#endif 

#define BALL_H5 PAD_ET_TX_EN
#define PAD_ET_TX_EN 150
#define GPIO_PAD_150 GPIO149
#ifndef BALL_H5_IS_GPIO
#define BALL_H5_IS_GPIO 0
#endif 
#ifndef PAD_ET_TX_EN_IS_GPIO
#define PAD_ET_TX_EN_IS_GPIO BALL_H5_IS_GPIO
#endif 

#define BALL_F4 PAD_ET_TX_CLK
#define PAD_ET_TX_CLK 147
#define GPIO_PAD_147 GPIO146
#ifndef BALL_F4_IS_GPIO
#define BALL_F4_IS_GPIO 0
#endif 
#ifndef PAD_ET_TX_CLK_IS_GPIO
#define PAD_ET_TX_CLK_IS_GPIO BALL_F4_IS_GPIO
#endif 

#define BALL_G6 PAD_ET_RXD0
#define PAD_ET_RXD0 145
#define GPIO_PAD_145 GPIO144
#ifndef BALL_G6_IS_GPIO
#define BALL_G6_IS_GPIO 0
#endif 
#ifndef PAD_ET_RXD0_IS_GPIO
#define PAD_ET_RXD0_IS_GPIO BALL_G6_IS_GPIO
#endif 

#define BALL_G7 PAD_ET_MDC
#define PAD_ET_MDC 144
#define GPIO_PAD_144 GPIO143
#ifndef BALL_G7_IS_GPIO
#define BALL_G7_IS_GPIO 0
#endif 
#ifndef PAD_ET_MDC_IS_GPIO
#define PAD_ET_MDC_IS_GPIO BALL_G7_IS_GPIO
#endif 

#define BALL_F6 PAD_ET_MDIO
#define PAD_ET_MDIO 143
#define GPIO_PAD_143 GPIO142
#ifndef BALL_F6_IS_GPIO
#define BALL_F6_IS_GPIO 0
#endif 
#ifndef PAD_ET_MDIO_IS_GPIO
#define PAD_ET_MDIO_IS_GPIO BALL_F6_IS_GPIO
#endif 

#define BALL_G5 PAD_ET_RXD1
#define PAD_ET_RXD1 146
#define GPIO_PAD_146 GPIO145
#ifndef BALL_G5_IS_GPIO
#define BALL_G5_IS_GPIO 0
#endif 
#ifndef PAD_ET_RXD1_IS_GPIO
#define PAD_ET_RXD1_IS_GPIO BALL_G5_IS_GPIO
#endif 

#define PAD_RF_AGC 9998
#ifndef PAD_RF_AGC_IS_GPIO
#define PAD_RF_AGC_IS_GPIO 0
#endif

#define PAD_IF_AGC 9997
#ifndef PAD_IF_AGC_IS_GPIO
#define PAD_IF_AGC_IS_GPIO 0
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
#define CHIP_FAMILY_TYPE           CHIP_FAMILY_A2

#endif /* _MSD393SSV_H_*/
