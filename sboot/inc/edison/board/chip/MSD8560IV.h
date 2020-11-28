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
#ifndef _MSD8560IV_H_
#define _MSD8560IV_H_

#define PAD_NC 9999
#define PAD_GND 0

#define BALL_D3 PAD_PM_SPI_DI
#define PAD_PM_SPI_DI 3
#define GPIO_PAD_3 GPIO2
#ifndef BALL_D3_IS_GPIO
#define BALL_D3_IS_GPIO 0
#endif 
#ifndef PAD_PM_SPI_DI_IS_GPIO
#define PAD_PM_SPI_DI_IS_GPIO BALL_D3_IS_GPIO
#endif 

#define BALL_G9 PAD_PM_SPI_CZ
#define PAD_PM_SPI_CZ 1
#define GPIO_PAD_1 GPIO0
#ifndef BALL_G9_IS_GPIO
#define BALL_G9_IS_GPIO 0
#endif 
#ifndef PAD_PM_SPI_CZ_IS_GPIO
#define PAD_PM_SPI_CZ_IS_GPIO BALL_G9_IS_GPIO
#endif 

#define BALL_D1 PAD_PM_SPI_DO
#define PAD_PM_SPI_DO 4
#define GPIO_PAD_4 GPIO3
#ifndef BALL_D1_IS_GPIO
#define BALL_D1_IS_GPIO 0
#endif 
#ifndef PAD_PM_SPI_DO_IS_GPIO
#define PAD_PM_SPI_DO_IS_GPIO BALL_D1_IS_GPIO
#endif 

#define BALL_C1 PAD_PM_SPI_CK
#define PAD_PM_SPI_CK 2
#define GPIO_PAD_2 GPIO1
#ifndef BALL_C1_IS_GPIO
#define BALL_C1_IS_GPIO 0
#endif 
#ifndef PAD_PM_SPI_CK_IS_GPIO
#define PAD_PM_SPI_CK_IS_GPIO BALL_C1_IS_GPIO
#endif 

#define BALL_J5 PAD_DDCA_CK
#define PAD_DDCA_CK 32
#define GPIO_PAD_32 GPIO31
#ifndef BALL_J5_IS_GPIO
#define BALL_J5_IS_GPIO 0
#endif 
#ifndef PAD_DDCA_CK_IS_GPIO
#define PAD_DDCA_CK_IS_GPIO BALL_J5_IS_GPIO
#endif 

#define BALL_J6 PAD_DDCA_DA
#define PAD_DDCA_DA 33
#define GPIO_PAD_33 GPIO32
#ifndef BALL_J6_IS_GPIO
#define BALL_J6_IS_GPIO 0
#endif 
#ifndef PAD_DDCA_DA_IS_GPIO
#define PAD_DDCA_DA_IS_GPIO BALL_J6_IS_GPIO
#endif 

#define BALL_B3 PAD_GPIO_PM0
#define PAD_GPIO_PM0 9
#define GPIO_PAD_9 GPIO8
#ifndef BALL_B3_IS_GPIO
#define BALL_B3_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM0_IS_GPIO
#define PAD_GPIO_PM0_IS_GPIO BALL_B3_IS_GPIO
#endif 

#define BALL_K5 PAD_GPIO_PM1
#define PAD_GPIO_PM1 10
#define GPIO_PAD_10 GPIO9
#ifndef BALL_K5_IS_GPIO
#define BALL_K5_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM1_IS_GPIO
#define PAD_GPIO_PM1_IS_GPIO BALL_K5_IS_GPIO
#endif 

#define PAD_GPIO_PM2 9999
#ifndef PAD_GPIO_PM2_IS_GPIO
#define PAD_GPIO_PM2_IS_GPIO 0
#endif 

#define PAD_GPIO_PM3 9999
#ifndef PAD_GPIO_PM3_IS_GPIO
#define PAD_GPIO_PM3_IS_GPIO 0
#endif 

#define BALL_C3 PAD_GPIO_PM4
#define PAD_GPIO_PM4 13
#define GPIO_PAD_13 GPIO12
#ifndef BALL_C3_IS_GPIO
#define BALL_C3_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM4_IS_GPIO
#define PAD_GPIO_PM4_IS_GPIO BALL_C3_IS_GPIO
#endif 

#define BALL_J4 PAD_GPIO_PM5
#define PAD_GPIO_PM5 14
#define GPIO_PAD_14 GPIO13
#ifndef BALL_J4_IS_GPIO
#define BALL_J4_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM5_IS_GPIO
#define PAD_GPIO_PM5_IS_GPIO BALL_J4_IS_GPIO
#endif 

#define BALL_D4 PAD_GPIO_PM6
#define PAD_GPIO_PM6 15
#define GPIO_PAD_15 GPIO14
#ifndef BALL_D4_IS_GPIO
#define BALL_D4_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM6_IS_GPIO
#define PAD_GPIO_PM6_IS_GPIO BALL_D4_IS_GPIO
#endif 

#define BALL_D6 PAD_GPIO_PM7
#define PAD_GPIO_PM7 16
#define GPIO_PAD_16 GPIO15
#ifndef BALL_D6_IS_GPIO
#define BALL_D6_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM7_IS_GPIO
#define PAD_GPIO_PM7_IS_GPIO BALL_D6_IS_GPIO
#endif 

#define BALL_G8 PAD_GPIO_PM8
#define PAD_GPIO_PM8 17
#define GPIO_PAD_17 GPIO16
#ifndef BALL_G8_IS_GPIO
#define BALL_G8_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM8_IS_GPIO
#define PAD_GPIO_PM8_IS_GPIO BALL_G8_IS_GPIO
#endif 

#define PAD_GPIO_PM9 9999
#ifndef PAD_GPIO_PM9_IS_GPIO
#define PAD_GPIO_PM9_IS_GPIO 0
#endif 

#define BALL_E4 PAD_GPIO_PM10
#define PAD_GPIO_PM10 19
#define GPIO_PAD_19 GPIO18
#ifndef BALL_E4_IS_GPIO
#define BALL_E4_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM10_IS_GPIO
#define PAD_GPIO_PM10_IS_GPIO BALL_E4_IS_GPIO
#endif 

#define PAD_GPIO_PM11 9999
#ifndef PAD_GPIO_PM11_IS_GPIO
#define PAD_GPIO_PM11_IS_GPIO 0
#endif 

#define PAD_GPIO_PM12 9999
#ifndef PAD_GPIO_PM12_IS_GPIO
#define PAD_GPIO_PM12_IS_GPIO 0
#endif 

#define PAD_GPIO_PM13 9999
#ifndef PAD_GPIO_PM13_IS_GPIO
#define PAD_GPIO_PM13_IS_GPIO 0
#endif 

#define BALL_AK3 PAD_GPIO_PM14
#define PAD_GPIO_PM14 23
#define GPIO_PAD_23 GPIO22
#ifndef BALL_AK3_IS_GPIO
#define BALL_AK3_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM14_IS_GPIO
#define PAD_GPIO_PM14_IS_GPIO BALL_AK3_IS_GPIO
#endif 

#define BALL_AL3 PAD_GPIO_PM15
#define PAD_GPIO_PM15 24
#define GPIO_PAD_24 GPIO23
#ifndef BALL_AL3_IS_GPIO
#define BALL_AL3_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM15_IS_GPIO
#define PAD_GPIO_PM15_IS_GPIO BALL_AL3_IS_GPIO
#endif 

#define BALL_AJ4 PAD_GPIO_PM16
#define PAD_GPIO_PM16 25
#define GPIO_PAD_25 GPIO24
#ifndef BALL_AJ4_IS_GPIO
#define BALL_AJ4_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM16_IS_GPIO
#define PAD_GPIO_PM16_IS_GPIO BALL_AJ4_IS_GPIO
#endif 

#define PAD_GPIO_PM17 9999
#ifndef PAD_GPIO_PM17_IS_GPIO
#define PAD_GPIO_PM17_IS_GPIO 0
#endif 

#define PAD_GPIO_PM18 9999
#ifndef PAD_GPIO_PM18_IS_GPIO
#define PAD_GPIO_PM18_IS_GPIO 0
#endif 

#define BALL_M4 PAD_IRIN
#define PAD_IRIN 5
#define GPIO_PAD_5 GPIO4
#ifndef BALL_M4_IS_GPIO
#define BALL_M4_IS_GPIO 0
#endif 
#ifndef PAD_IRIN_IS_GPIO
#define PAD_IRIN_IS_GPIO BALL_M4_IS_GPIO
#endif 

#define PAD_AV_LNK 9999
#ifndef PAD_AV_LNK_IS_GPIO
#define PAD_AV_LNK_IS_GPIO 0
#endif 

#define BALL_N5 PAD_PWM_PM
#define PAD_PWM_PM 8
#define GPIO_PAD_8 GPIO7
#ifndef BALL_N5_IS_GPIO
#define BALL_N5_IS_GPIO 0
#endif 
#ifndef PAD_PWM_PM_IS_GPIO
#define PAD_PWM_PM_IS_GPIO BALL_N5_IS_GPIO
#endif 

#define BALL_R5 PAD_HOTPLUGA
#define PAD_HOTPLUGA 28
#define GPIO_PAD_28 GPIO27
#ifndef BALL_R5_IS_GPIO
#define BALL_R5_IS_GPIO 0
#endif 
#ifndef PAD_HOTPLUGA_IS_GPIO
#define PAD_HOTPLUGA_IS_GPIO BALL_R5_IS_GPIO
#endif 

#define BALL_R6 PAD_DDCDA_CK
#define PAD_DDCDA_CK 34
#define GPIO_PAD_34 GPIO33
#ifndef BALL_R6_IS_GPIO
#define BALL_R6_IS_GPIO 0
#endif 
#ifndef PAD_DDCDA_CK_IS_GPIO
#define PAD_DDCDA_CK_IS_GPIO BALL_R6_IS_GPIO
#endif 

#define BALL_T6 PAD_DDCDA_DA
#define PAD_DDCDA_DA 35
#define GPIO_PAD_35 GPIO34
#ifndef BALL_T6_IS_GPIO
#define BALL_T6_IS_GPIO 0
#endif 
#ifndef PAD_DDCDA_DA_IS_GPIO
#define PAD_DDCDA_DA_IS_GPIO BALL_T6_IS_GPIO
#endif 

#define BALL_P4 PAD_DDCDB_CK
#define PAD_DDCDB_CK 36
#define GPIO_PAD_36 GPIO35
#ifndef BALL_P4_IS_GPIO
#define BALL_P4_IS_GPIO 0
#endif 
#ifndef PAD_DDCDB_CK_IS_GPIO
#define PAD_DDCDB_CK_IS_GPIO BALL_P4_IS_GPIO
#endif 

#define BALL_T5 PAD_DDCDB_DA
#define PAD_DDCDB_DA 37
#define GPIO_PAD_37 GPIO36
#ifndef BALL_T5_IS_GPIO
#define BALL_T5_IS_GPIO 0
#endif 
#ifndef PAD_DDCDB_DA_IS_GPIO
#define PAD_DDCDB_DA_IS_GPIO BALL_T5_IS_GPIO
#endif 

#define BALL_P5 PAD_HOTPLUGB
#define PAD_HOTPLUGB 29
#define GPIO_PAD_29 GPIO28
#ifndef BALL_P5_IS_GPIO
#define BALL_P5_IS_GPIO 0
#endif 
#ifndef PAD_HOTPLUGB_IS_GPIO
#define PAD_HOTPLUGB_IS_GPIO BALL_P5_IS_GPIO
#endif 

#define BALL_M6 PAD_HOTPLUGD
#define PAD_HOTPLUGD 31
#define GPIO_PAD_31 GPIO30
#ifndef BALL_M6_IS_GPIO
#define BALL_M6_IS_GPIO 0
#endif 
#ifndef PAD_HOTPLUGD_IS_GPIO
#define PAD_HOTPLUGD_IS_GPIO BALL_M6_IS_GPIO
#endif 

#define BALL_N6 PAD_DDCDD_CK
#define PAD_DDCDD_CK 40
#define GPIO_PAD_40 GPIO39
#ifndef BALL_N6_IS_GPIO
#define BALL_N6_IS_GPIO 0
#endif 
#ifndef PAD_DDCDD_CK_IS_GPIO
#define PAD_DDCDD_CK_IS_GPIO BALL_N6_IS_GPIO
#endif 

#define BALL_P6 PAD_DDCDD_DA
#define PAD_DDCDD_DA 41
#define GPIO_PAD_41 GPIO40
#ifndef BALL_P6_IS_GPIO
#define BALL_P6_IS_GPIO 0
#endif 
#ifndef PAD_DDCDD_DA_IS_GPIO
#define PAD_DDCDD_DA_IS_GPIO BALL_P6_IS_GPIO
#endif 

#define BALL_M5 PAD_CEC
#define PAD_CEC 6
#define GPIO_PAD_6 GPIO5
#ifndef BALL_M5_IS_GPIO
#define BALL_M5_IS_GPIO 0
#endif 
#ifndef PAD_CEC_IS_GPIO
#define PAD_CEC_IS_GPIO BALL_M5_IS_GPIO
#endif 

#define BALL_U5 PAD_DDCDC_CK
#define PAD_DDCDC_CK 38
#define GPIO_PAD_38 GPIO37
#ifndef BALL_U5_IS_GPIO
#define BALL_U5_IS_GPIO 0
#endif 
#ifndef PAD_DDCDC_CK_IS_GPIO
#define PAD_DDCDC_CK_IS_GPIO BALL_U5_IS_GPIO
#endif 

#define BALL_U4 PAD_DDCDC_DA
#define PAD_DDCDC_DA 39
#define GPIO_PAD_39 GPIO38
#ifndef BALL_U4_IS_GPIO
#define BALL_U4_IS_GPIO 0
#endif 
#ifndef PAD_DDCDC_DA_IS_GPIO
#define PAD_DDCDC_DA_IS_GPIO BALL_U4_IS_GPIO
#endif 

#define BALL_U6 PAD_HOTPLUGC
#define PAD_HOTPLUGC 30
#define GPIO_PAD_30 GPIO29
#ifndef BALL_U6_IS_GPIO
#define BALL_U6_IS_GPIO 0
#endif 
#ifndef PAD_HOTPLUGC_IS_GPIO
#define PAD_HOTPLUGC_IS_GPIO BALL_U6_IS_GPIO
#endif 

#define BALL_AG2 PAD_TGPIO0
#define PAD_TGPIO0 162
#define GPIO_PAD_162 GPIO161
#ifndef BALL_AG2_IS_GPIO
#define BALL_AG2_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO0_IS_GPIO
#define PAD_TGPIO0_IS_GPIO BALL_AG2_IS_GPIO
#endif 

#define BALL_AG3 PAD_TGPIO1
#define PAD_TGPIO1 163
#define GPIO_PAD_163 GPIO162
#ifndef BALL_AG3_IS_GPIO
#define BALL_AG3_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO1_IS_GPIO
#define PAD_TGPIO1_IS_GPIO BALL_AG3_IS_GPIO
#endif 

#define BALL_AL1 PAD_TGPIO2
#define PAD_TGPIO2 164
#define GPIO_PAD_164 GPIO163
#ifndef BALL_AL1_IS_GPIO
#define BALL_AL1_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO2_IS_GPIO
#define PAD_TGPIO2_IS_GPIO BALL_AL1_IS_GPIO
#endif 

#define BALL_AL2 PAD_TGPIO3
#define PAD_TGPIO3 165
#define GPIO_PAD_165 GPIO164
#ifndef BALL_AL2_IS_GPIO
#define BALL_AL2_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO3_IS_GPIO
#define PAD_TGPIO3_IS_GPIO BALL_AL2_IS_GPIO
#endif 

#define BALL_AG15 PAD_TS0_D0
#define PAD_TS0_D0 166
#define GPIO_PAD_166 GPIO165
#ifndef BALL_AG15_IS_GPIO
#define BALL_AG15_IS_GPIO 0
#endif 
#ifndef PAD_TS0_D0_IS_GPIO
#define PAD_TS0_D0_IS_GPIO BALL_AG15_IS_GPIO
#endif 

#define BALL_AJ15 PAD_TS0_D1
#define PAD_TS0_D1 167
#define GPIO_PAD_167 GPIO166
#ifndef BALL_AJ15_IS_GPIO
#define BALL_AJ15_IS_GPIO 0
#endif 
#ifndef PAD_TS0_D1_IS_GPIO
#define PAD_TS0_D1_IS_GPIO BALL_AJ15_IS_GPIO
#endif 

#define BALL_AH15 PAD_TS0_D2
#define PAD_TS0_D2 168
#define GPIO_PAD_168 GPIO167
#ifndef BALL_AH15_IS_GPIO
#define BALL_AH15_IS_GPIO 0
#endif 
#ifndef PAD_TS0_D2_IS_GPIO
#define PAD_TS0_D2_IS_GPIO BALL_AH15_IS_GPIO
#endif 

#define BALL_AG11 PAD_TS0_D3
#define PAD_TS0_D3 169
#define GPIO_PAD_169 GPIO168
#ifndef BALL_AG11_IS_GPIO
#define BALL_AG11_IS_GPIO 0
#endif 
#ifndef PAD_TS0_D3_IS_GPIO
#define PAD_TS0_D3_IS_GPIO BALL_AG11_IS_GPIO
#endif 

#define BALL_AH11 PAD_TS0_D4
#define PAD_TS0_D4 170
#define GPIO_PAD_170 GPIO169
#ifndef BALL_AH11_IS_GPIO
#define BALL_AH11_IS_GPIO 0
#endif 
#ifndef PAD_TS0_D4_IS_GPIO
#define PAD_TS0_D4_IS_GPIO BALL_AH11_IS_GPIO
#endif 

#define BALL_AJ11 PAD_TS0_D5
#define PAD_TS0_D5 171
#define GPIO_PAD_171 GPIO170
#ifndef BALL_AJ11_IS_GPIO
#define BALL_AJ11_IS_GPIO 0
#endif 
#ifndef PAD_TS0_D5_IS_GPIO
#define PAD_TS0_D5_IS_GPIO BALL_AJ11_IS_GPIO
#endif 

#define BALL_AG12 PAD_TS0_D6
#define PAD_TS0_D6 172
#define GPIO_PAD_172 GPIO171
#ifndef BALL_AG12_IS_GPIO
#define BALL_AG12_IS_GPIO 0
#endif 
#ifndef PAD_TS0_D6_IS_GPIO
#define PAD_TS0_D6_IS_GPIO BALL_AG12_IS_GPIO
#endif 

#define BALL_AJ12 PAD_TS0_D7
#define PAD_TS0_D7 173
#define GPIO_PAD_173 GPIO172
#ifndef BALL_AJ12_IS_GPIO
#define BALL_AJ12_IS_GPIO 0
#endif 
#ifndef PAD_TS0_D7_IS_GPIO
#define PAD_TS0_D7_IS_GPIO BALL_AJ12_IS_GPIO
#endif 

#define BALL_AH14 PAD_TS0_VLD
#define PAD_TS0_VLD 174
#define GPIO_PAD_174 GPIO173
#ifndef BALL_AH14_IS_GPIO
#define BALL_AH14_IS_GPIO 0
#endif 
#ifndef PAD_TS0_VLD_IS_GPIO
#define PAD_TS0_VLD_IS_GPIO BALL_AH14_IS_GPIO
#endif 

#define BALL_AJ14 PAD_TS0_SYNC
#define PAD_TS0_SYNC 175
#define GPIO_PAD_175 GPIO174
#ifndef BALL_AJ14_IS_GPIO
#define BALL_AJ14_IS_GPIO 0
#endif 
#ifndef PAD_TS0_SYNC_IS_GPIO
#define PAD_TS0_SYNC_IS_GPIO BALL_AJ14_IS_GPIO
#endif 

#define BALL_AG14 PAD_TS0_CLK
#define PAD_TS0_CLK 176
#define GPIO_PAD_176 GPIO175
#ifndef BALL_AG14_IS_GPIO
#define BALL_AG14_IS_GPIO 0
#endif 
#ifndef PAD_TS0_CLK_IS_GPIO
#define PAD_TS0_CLK_IS_GPIO BALL_AG14_IS_GPIO
#endif 

#define BALL_AK14 PAD_TS1_CLK
#define PAD_TS1_CLK 177
#define GPIO_PAD_177 GPIO176
#ifndef BALL_AK14_IS_GPIO
#define BALL_AK14_IS_GPIO 0
#endif 
#ifndef PAD_TS1_CLK_IS_GPIO
#define PAD_TS1_CLK_IS_GPIO BALL_AK14_IS_GPIO
#endif 

#define BALL_AM12 PAD_TS1_SYNC
#define PAD_TS1_SYNC 178
#define GPIO_PAD_178 GPIO177
#ifndef BALL_AM12_IS_GPIO
#define BALL_AM12_IS_GPIO 0
#endif 
#ifndef PAD_TS1_SYNC_IS_GPIO
#define PAD_TS1_SYNC_IS_GPIO BALL_AM12_IS_GPIO
#endif 

#define BALL_AM14 PAD_TS1_VLD
#define PAD_TS1_VLD 179
#define GPIO_PAD_179 GPIO178
#ifndef BALL_AM14_IS_GPIO
#define BALL_AM14_IS_GPIO 0
#endif 
#ifndef PAD_TS1_VLD_IS_GPIO
#define PAD_TS1_VLD_IS_GPIO BALL_AM14_IS_GPIO
#endif 

#define BALL_AG13 PAD_TS1_D7
#define PAD_TS1_D7 180
#define GPIO_PAD_180 GPIO179
#ifndef BALL_AG13_IS_GPIO
#define BALL_AG13_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D7_IS_GPIO
#define PAD_TS1_D7_IS_GPIO BALL_AG13_IS_GPIO
#endif 

#define BALL_AH13 PAD_TS1_D6
#define PAD_TS1_D6 181
#define GPIO_PAD_181 GPIO180
#ifndef BALL_AH13_IS_GPIO
#define BALL_AH13_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D6_IS_GPIO
#define PAD_TS1_D6_IS_GPIO BALL_AH13_IS_GPIO
#endif 

#define BALL_AH12 PAD_TS1_D5
#define PAD_TS1_D5 182
#define GPIO_PAD_182 GPIO181
#ifndef BALL_AH12_IS_GPIO
#define BALL_AH12_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D5_IS_GPIO
#define PAD_TS1_D5_IS_GPIO BALL_AH12_IS_GPIO
#endif 

#define BALL_AL14 PAD_TS1_D4
#define PAD_TS1_D4 183
#define GPIO_PAD_183 GPIO182
#ifndef BALL_AL14_IS_GPIO
#define BALL_AL14_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D4_IS_GPIO
#define PAD_TS1_D4_IS_GPIO BALL_AL14_IS_GPIO
#endif 

#define BALL_AK13 PAD_TS1_D3
#define PAD_TS1_D3 184
#define GPIO_PAD_184 GPIO183
#ifndef BALL_AK13_IS_GPIO
#define BALL_AK13_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D3_IS_GPIO
#define PAD_TS1_D3_IS_GPIO BALL_AK13_IS_GPIO
#endif 

#define BALL_AL13 PAD_TS1_D2
#define PAD_TS1_D2 185
#define GPIO_PAD_185 GPIO184
#ifndef BALL_AL13_IS_GPIO
#define BALL_AL13_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D2_IS_GPIO
#define PAD_TS1_D2_IS_GPIO BALL_AL13_IS_GPIO
#endif 

#define BALL_AK12 PAD_TS1_D1
#define PAD_TS1_D1 186
#define GPIO_PAD_186 GPIO185
#ifndef BALL_AK12_IS_GPIO
#define BALL_AK12_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D1_IS_GPIO
#define PAD_TS1_D1_IS_GPIO BALL_AK12_IS_GPIO
#endif 

#define BALL_AL12 PAD_TS1_D0
#define PAD_TS1_D0 187
#define GPIO_PAD_187 GPIO186
#ifndef BALL_AL12_IS_GPIO
#define BALL_AL12_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D0_IS_GPIO
#define PAD_TS1_D0_IS_GPIO BALL_AL12_IS_GPIO
#endif 

#define BALL_AK10 PAD_TS2_D0
#define PAD_TS2_D0 188
#define GPIO_PAD_188 GPIO187
#ifndef BALL_AK10_IS_GPIO
#define BALL_AK10_IS_GPIO 0
#endif 
#ifndef PAD_TS2_D0_IS_GPIO
#define PAD_TS2_D0_IS_GPIO BALL_AK10_IS_GPIO
#endif 

#define BALL_AM11 PAD_TS2_VLD
#define PAD_TS2_VLD 189
#define GPIO_PAD_189 GPIO188
#ifndef BALL_AM11_IS_GPIO
#define BALL_AM11_IS_GPIO 0
#endif 
#ifndef PAD_TS2_VLD_IS_GPIO
#define PAD_TS2_VLD_IS_GPIO BALL_AM11_IS_GPIO
#endif 

#define BALL_AL11 PAD_TS2_SYNC
#define PAD_TS2_SYNC 190
#define GPIO_PAD_190 GPIO189
#ifndef BALL_AL11_IS_GPIO
#define BALL_AL11_IS_GPIO 0
#endif 
#ifndef PAD_TS2_SYNC_IS_GPIO
#define PAD_TS2_SYNC_IS_GPIO BALL_AL11_IS_GPIO
#endif 

#define BALL_AK11 PAD_TS2_CLK
#define PAD_TS2_CLK 191
#define GPIO_PAD_191 GPIO190
#ifndef BALL_AK11_IS_GPIO
#define BALL_AK11_IS_GPIO 0
#endif 
#ifndef PAD_TS2_CLK_IS_GPIO
#define PAD_TS2_CLK_IS_GPIO BALL_AK11_IS_GPIO
#endif 

#define BALL_AJ26 PAD_PCM_D4
#define PAD_PCM_D4 108
#define GPIO_PAD_108 GPIO107
#ifndef BALL_AJ26_IS_GPIO
#define BALL_AJ26_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D4_IS_GPIO
#define PAD_PCM_D4_IS_GPIO BALL_AJ26_IS_GPIO
#endif 

#define BALL_AG27 PAD_PCM_D5
#define PAD_PCM_D5 109
#define GPIO_PAD_109 GPIO108
#ifndef BALL_AG27_IS_GPIO
#define BALL_AG27_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D5_IS_GPIO
#define PAD_PCM_D5_IS_GPIO BALL_AG27_IS_GPIO
#endif 

#define BALL_AJ27 PAD_PCM_D6
#define PAD_PCM_D6 110
#define GPIO_PAD_110 GPIO109
#ifndef BALL_AJ27_IS_GPIO
#define BALL_AJ27_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D6_IS_GPIO
#define PAD_PCM_D6_IS_GPIO BALL_AJ27_IS_GPIO
#endif 

#define BALL_AH27 PAD_PCM_D7
#define PAD_PCM_D7 111
#define GPIO_PAD_111 GPIO110
#ifndef BALL_AH27_IS_GPIO
#define BALL_AH27_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D7_IS_GPIO
#define PAD_PCM_D7_IS_GPIO BALL_AH27_IS_GPIO
#endif 

#define BALL_AG17 PAD_PCM_A10
#define PAD_PCM_A10 113
#define GPIO_PAD_113 GPIO112
#ifndef BALL_AG17_IS_GPIO
#define BALL_AG17_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A10_IS_GPIO
#define PAD_PCM_A10_IS_GPIO BALL_AG17_IS_GPIO
#endif 

#define BALL_AH17 PAD_PCM_OE_N
#define PAD_PCM_OE_N 114
#define GPIO_PAD_114 GPIO113
#ifndef BALL_AH17_IS_GPIO
#define BALL_AH17_IS_GPIO 0
#endif 
#ifndef PAD_PCM_OE_N_IS_GPIO
#define PAD_PCM_OE_N_IS_GPIO BALL_AH17_IS_GPIO
#endif 

#define BALL_AG18 PAD_PCM_A11
#define PAD_PCM_A11 115
#define GPIO_PAD_115 GPIO114
#ifndef BALL_AG18_IS_GPIO
#define BALL_AG18_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A11_IS_GPIO
#define PAD_PCM_A11_IS_GPIO BALL_AG18_IS_GPIO
#endif 

#define BALL_AL16 PAD_PCM_A13
#define PAD_PCM_A13 120
#define GPIO_PAD_120 GPIO119
#ifndef BALL_AL16_IS_GPIO
#define BALL_AL16_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A13_IS_GPIO
#define PAD_PCM_A13_IS_GPIO BALL_AL16_IS_GPIO
#endif 

#define BALL_AK16 PAD_PCM_A14
#define PAD_PCM_A14 121
#define GPIO_PAD_121 GPIO120
#ifndef BALL_AK16_IS_GPIO
#define BALL_AK16_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A14_IS_GPIO
#define PAD_PCM_A14_IS_GPIO BALL_AK16_IS_GPIO
#endif 

#define BALL_AH19 PAD_PCM_A3
#define PAD_PCM_A3 130
#define GPIO_PAD_130 GPIO129
#ifndef BALL_AH19_IS_GPIO
#define BALL_AH19_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A3_IS_GPIO
#define PAD_PCM_A3_IS_GPIO BALL_AH19_IS_GPIO
#endif 

#define BALL_AJ20 PAD_PCM_A2
#define PAD_PCM_A2 131
#define GPIO_PAD_131 GPIO130
#ifndef BALL_AJ20_IS_GPIO
#define BALL_AJ20_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A2_IS_GPIO
#define PAD_PCM_A2_IS_GPIO BALL_AJ20_IS_GPIO
#endif 

#define BALL_AH18 PAD_PCM_A4
#define PAD_PCM_A4 129
#define GPIO_PAD_129 GPIO128
#ifndef BALL_AH18_IS_GPIO
#define BALL_AH18_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A4_IS_GPIO
#define PAD_PCM_A4_IS_GPIO BALL_AH18_IS_GPIO
#endif 

#define BALL_AM18 PAD_PCM_A7
#define PAD_PCM_A7 125
#define GPIO_PAD_125 GPIO124
#ifndef BALL_AM18_IS_GPIO
#define BALL_AM18_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A7_IS_GPIO
#define PAD_PCM_A7_IS_GPIO BALL_AM18_IS_GPIO
#endif 

#define BALL_AL18 PAD_PCM_A6
#define PAD_PCM_A6 126
#define GPIO_PAD_126 GPIO125
#ifndef BALL_AL18_IS_GPIO
#define BALL_AL18_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A6_IS_GPIO
#define PAD_PCM_A6_IS_GPIO BALL_AL18_IS_GPIO
#endif 

#define BALL_AJ18 PAD_PCM_A5
#define PAD_PCM_A5 127
#define GPIO_PAD_127 GPIO126
#ifndef BALL_AJ18_IS_GPIO
#define BALL_AJ18_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A5_IS_GPIO
#define PAD_PCM_A5_IS_GPIO BALL_AJ18_IS_GPIO
#endif 

#define BALL_AK17 PAD_PCM_A12
#define PAD_PCM_A12 124
#define GPIO_PAD_124 GPIO123
#ifndef BALL_AK17_IS_GPIO
#define BALL_AK17_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A12_IS_GPIO
#define PAD_PCM_A12_IS_GPIO BALL_AK17_IS_GPIO
#endif 

#define BALL_AJ17 PAD_PCM_IORD_N
#define PAD_PCM_IORD_N 116
#define GPIO_PAD_116 GPIO115
#ifndef BALL_AJ17_IS_GPIO
#define BALL_AJ17_IS_GPIO 0
#endif 
#ifndef PAD_PCM_IORD_N_IS_GPIO
#define PAD_PCM_IORD_N_IS_GPIO BALL_AJ17_IS_GPIO
#endif 

#define BALL_AL15 PAD_PCM_A9
#define PAD_PCM_A9 117
#define GPIO_PAD_117 GPIO116
#ifndef BALL_AL15_IS_GPIO
#define BALL_AL15_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A9_IS_GPIO
#define PAD_PCM_A9_IS_GPIO BALL_AL15_IS_GPIO
#endif 

#define BALL_AG21 PAD_PCM_A1
#define PAD_PCM_A1 133
#define GPIO_PAD_133 GPIO132
#ifndef BALL_AG21_IS_GPIO
#define BALL_AG21_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A1_IS_GPIO
#define PAD_PCM_A1_IS_GPIO BALL_AG21_IS_GPIO
#endif 

#define BALL_AJ21 PAD_PCM_A0
#define PAD_PCM_A0 134
#define GPIO_PAD_134 GPIO133
#ifndef BALL_AJ21_IS_GPIO
#define BALL_AJ21_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A0_IS_GPIO
#define PAD_PCM_A0_IS_GPIO BALL_AJ21_IS_GPIO
#endif 

#define BALL_AJ28 PAD_PCM_D0
#define PAD_PCM_D0 135
#define GPIO_PAD_135 GPIO134
#ifndef BALL_AJ28_IS_GPIO
#define BALL_AJ28_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D0_IS_GPIO
#define PAD_PCM_D0_IS_GPIO BALL_AJ28_IS_GPIO
#endif 

#define BALL_AH28 PAD_PCM_D1
#define PAD_PCM_D1 136
#define GPIO_PAD_136 GPIO135
#ifndef BALL_AH28_IS_GPIO
#define BALL_AH28_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D1_IS_GPIO
#define PAD_PCM_D1_IS_GPIO BALL_AH28_IS_GPIO
#endif 

#define BALL_AJ29 PAD_PCM_D2
#define PAD_PCM_D2 137
#define GPIO_PAD_137 GPIO136
#ifndef BALL_AJ29_IS_GPIO
#define BALL_AJ29_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D2_IS_GPIO
#define PAD_PCM_D2_IS_GPIO BALL_AJ29_IS_GPIO
#endif 

#define BALL_AH26 PAD_PCM_D3
#define PAD_PCM_D3 107
#define GPIO_PAD_107 GPIO106
#ifndef BALL_AH26_IS_GPIO
#define BALL_AH26_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D3_IS_GPIO
#define PAD_PCM_D3_IS_GPIO BALL_AH26_IS_GPIO
#endif 

#define BALL_AK15 PAD_PCM_A8
#define PAD_PCM_A8 119
#define GPIO_PAD_119 GPIO118
#ifndef BALL_AK15_IS_GPIO
#define BALL_AK15_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A8_IS_GPIO
#define PAD_PCM_A8_IS_GPIO BALL_AK15_IS_GPIO
#endif 

#define BALL_AH21 PAD_EMMC_RSTN
#define PAD_EMMC_RSTN 145
#define GPIO_PAD_145 GPIO144
#ifndef BALL_AH21_IS_GPIO
#define BALL_AH21_IS_GPIO 0
#endif 
#ifndef PAD_EMMC_RSTN_IS_GPIO
#define PAD_EMMC_RSTN_IS_GPIO BALL_AH21_IS_GPIO
#endif 

#define BALL_AH22 PAD_EMMC_CMD
#define PAD_EMMC_CMD 147
#define GPIO_PAD_147 GPIO146
#ifndef BALL_AH22_IS_GPIO
#define BALL_AH22_IS_GPIO 0
#endif 
#ifndef PAD_EMMC_CMD_IS_GPIO
#define PAD_EMMC_CMD_IS_GPIO BALL_AH22_IS_GPIO
#endif 

#define BALL_AG22 PAD_EMMC_CLK
#define PAD_EMMC_CLK 146
#define GPIO_PAD_146 GPIO145
#ifndef BALL_AG22_IS_GPIO
#define BALL_AG22_IS_GPIO 0
#endif 
#ifndef PAD_EMMC_CLK_IS_GPIO
#define PAD_EMMC_CLK_IS_GPIO BALL_AG22_IS_GPIO
#endif 

#define BALL_AJ24 PAD_NAND_CEZ1
#define PAD_NAND_CEZ1 95
#define GPIO_PAD_95 GPIO94
#ifndef BALL_AJ24_IS_GPIO
#define BALL_AJ24_IS_GPIO 0
#endif 
#ifndef PAD_NAND_CEZ1_IS_GPIO
#define PAD_NAND_CEZ1_IS_GPIO BALL_AJ24_IS_GPIO
#endif 

#define BALL_AG25 PAD_NAND_CEZ
#define PAD_NAND_CEZ 94
#define GPIO_PAD_94 GPIO93
#ifndef BALL_AG25_IS_GPIO
#define BALL_AG25_IS_GPIO 0
#endif 
#ifndef PAD_NAND_CEZ_IS_GPIO
#define PAD_NAND_CEZ_IS_GPIO BALL_AG25_IS_GPIO
#endif 

#define BALL_AH24 PAD_NAND_CLE
#define PAD_NAND_CLE 96
#define GPIO_PAD_96 GPIO95
#ifndef BALL_AH24_IS_GPIO
#define BALL_AH24_IS_GPIO 0
#endif 
#ifndef PAD_NAND_CLE_IS_GPIO
#define PAD_NAND_CLE_IS_GPIO BALL_AH24_IS_GPIO
#endif 

#define BALL_AH25 PAD_NAND_REZ
#define PAD_NAND_REZ 97
#define GPIO_PAD_97 GPIO96
#ifndef BALL_AH25_IS_GPIO
#define BALL_AH25_IS_GPIO 0
#endif 
#ifndef PAD_NAND_REZ_IS_GPIO
#define PAD_NAND_REZ_IS_GPIO BALL_AH25_IS_GPIO
#endif 

#define BALL_AH23 PAD_NAND_WEZ
#define PAD_NAND_WEZ 98
#define GPIO_PAD_98 GPIO97
#ifndef BALL_AH23_IS_GPIO
#define BALL_AH23_IS_GPIO 0
#endif 
#ifndef PAD_NAND_WEZ_IS_GPIO
#define PAD_NAND_WEZ_IS_GPIO BALL_AH23_IS_GPIO
#endif 

#define BALL_AJ23 PAD_NAND_WPZ
#define PAD_NAND_WPZ 99
#define GPIO_PAD_99 GPIO98
#ifndef BALL_AJ23_IS_GPIO
#define BALL_AJ23_IS_GPIO 0
#endif 
#ifndef PAD_NAND_WPZ_IS_GPIO
#define PAD_NAND_WPZ_IS_GPIO BALL_AJ23_IS_GPIO
#endif 

#define BALL_AG23 PAD_NAND_ALE
#define PAD_NAND_ALE 100
#define GPIO_PAD_100 GPIO99
#ifndef BALL_AG23_IS_GPIO
#define BALL_AG23_IS_GPIO 0
#endif 
#ifndef PAD_NAND_ALE_IS_GPIO
#define PAD_NAND_ALE_IS_GPIO BALL_AG23_IS_GPIO
#endif 

#define BALL_AG24 PAD_NAND_RBZ
#define PAD_NAND_RBZ 101
#define GPIO_PAD_101 GPIO100
#ifndef BALL_AG24_IS_GPIO
#define BALL_AG24_IS_GPIO 0
#endif 
#ifndef PAD_NAND_RBZ_IS_GPIO
#define PAD_NAND_RBZ_IS_GPIO BALL_AG24_IS_GPIO
#endif 

#define BALL_AH31 PAD_TCON0
#define PAD_TCON0 148
#define GPIO_PAD_148 GPIO147
#ifndef BALL_AH31_IS_GPIO
#define BALL_AH31_IS_GPIO 0
#endif 
#ifndef PAD_TCON0_IS_GPIO
#define PAD_TCON0_IS_GPIO BALL_AH31_IS_GPIO
#endif 

#define BALL_AH30 PAD_TCON1
#define PAD_TCON1 149
#define GPIO_PAD_149 GPIO148
#ifndef BALL_AH30_IS_GPIO
#define BALL_AH30_IS_GPIO 0
#endif 
#ifndef PAD_TCON1_IS_GPIO
#define PAD_TCON1_IS_GPIO BALL_AH30_IS_GPIO
#endif 

#define BALL_AJ31 PAD_TCON2
#define PAD_TCON2 150
#define GPIO_PAD_150 GPIO149
#ifndef BALL_AJ31_IS_GPIO
#define BALL_AJ31_IS_GPIO 0
#endif 
#ifndef PAD_TCON2_IS_GPIO
#define PAD_TCON2_IS_GPIO BALL_AJ31_IS_GPIO
#endif 

#define BALL_AJ30 PAD_TCON3
#define PAD_TCON3 151
#define GPIO_PAD_151 GPIO150
#ifndef BALL_AJ30_IS_GPIO
#define BALL_AJ30_IS_GPIO 0
#endif 
#ifndef PAD_TCON3_IS_GPIO
#define PAD_TCON3_IS_GPIO BALL_AJ30_IS_GPIO
#endif 

#define BALL_AK31 PAD_TCON4
#define PAD_TCON4 152
#define GPIO_PAD_152 GPIO151
#ifndef BALL_AK31_IS_GPIO
#define BALL_AK31_IS_GPIO 0
#endif 
#ifndef PAD_TCON4_IS_GPIO
#define PAD_TCON4_IS_GPIO BALL_AK31_IS_GPIO
#endif 

#define BALL_AK32 PAD_TCON5
#define PAD_TCON5 153
#define GPIO_PAD_153 GPIO152
#ifndef BALL_AK32_IS_GPIO
#define BALL_AK32_IS_GPIO 0
#endif 
#ifndef PAD_TCON5_IS_GPIO
#define PAD_TCON5_IS_GPIO BALL_AK32_IS_GPIO
#endif 

#define BALL_AL30 PAD_TCON6
#define PAD_TCON6 154
#define GPIO_PAD_154 GPIO153
#ifndef BALL_AL30_IS_GPIO
#define BALL_AL30_IS_GPIO 0
#endif 
#ifndef PAD_TCON6_IS_GPIO
#define PAD_TCON6_IS_GPIO BALL_AL30_IS_GPIO
#endif 

#define BALL_AM30 PAD_TCON7
#define PAD_TCON7 155
#define GPIO_PAD_155 GPIO154
#ifndef BALL_AM30_IS_GPIO
#define BALL_AM30_IS_GPIO 0
#endif 
#ifndef PAD_TCON7_IS_GPIO
#define PAD_TCON7_IS_GPIO BALL_AM30_IS_GPIO
#endif 

#define BALL_AK29 PAD_TCON8
#define PAD_TCON8 156
#define GPIO_PAD_156 GPIO155
#ifndef BALL_AK29_IS_GPIO
#define BALL_AK29_IS_GPIO 0
#endif 
#ifndef PAD_TCON8_IS_GPIO
#define PAD_TCON8_IS_GPIO BALL_AK29_IS_GPIO
#endif 

#define BALL_AM29 PAD_TCON9
#define PAD_TCON9 157
#define GPIO_PAD_157 GPIO156
#ifndef BALL_AM29_IS_GPIO
#define BALL_AM29_IS_GPIO 0
#endif 
#ifndef PAD_TCON9_IS_GPIO
#define PAD_TCON9_IS_GPIO BALL_AM29_IS_GPIO
#endif 

#define BALL_AL29 PAD_TCON10
#define PAD_TCON10 158
#define GPIO_PAD_158 GPIO157
#ifndef BALL_AL29_IS_GPIO
#define BALL_AL29_IS_GPIO 0
#endif 
#ifndef PAD_TCON10_IS_GPIO
#define PAD_TCON10_IS_GPIO BALL_AL29_IS_GPIO
#endif 

#define BALL_AK28 PAD_TCON11
#define PAD_TCON11 159
#define GPIO_PAD_159 GPIO158
#ifndef BALL_AK28_IS_GPIO
#define BALL_AK28_IS_GPIO 0
#endif 
#ifndef PAD_TCON11_IS_GPIO
#define PAD_TCON11_IS_GPIO BALL_AK28_IS_GPIO
#endif 

#define BALL_AL28 PAD_TCON12
#define PAD_TCON12 160
#define GPIO_PAD_160 GPIO159
#ifndef BALL_AL28_IS_GPIO
#define BALL_AL28_IS_GPIO 0
#endif 
#ifndef PAD_TCON12_IS_GPIO
#define PAD_TCON12_IS_GPIO BALL_AL28_IS_GPIO
#endif 

#define BALL_AK27 PAD_TCON13
#define PAD_TCON13 161
#define GPIO_PAD_161 GPIO160
#ifndef BALL_AK27_IS_GPIO
#define BALL_AK27_IS_GPIO 0
#endif 
#ifndef PAD_TCON13_IS_GPIO
#define PAD_TCON13_IS_GPIO BALL_AK27_IS_GPIO
#endif 

#define BALL_AE32 PAD_PCM2_CE_N
#define PAD_PCM2_CE_N 102
#define GPIO_PAD_102 GPIO101
#ifndef BALL_AE32_IS_GPIO
#define BALL_AE32_IS_GPIO 0
#endif 
#ifndef PAD_PCM2_CE_N_IS_GPIO
#define PAD_PCM2_CE_N_IS_GPIO BALL_AE32_IS_GPIO
#endif 

#define BALL_AE31 PAD_PCM2_IRQA_N
#define PAD_PCM2_IRQA_N 103
#define GPIO_PAD_103 GPIO102
#ifndef BALL_AE31_IS_GPIO
#define BALL_AE31_IS_GPIO 0
#endif 
#ifndef PAD_PCM2_IRQA_N_IS_GPIO
#define PAD_PCM2_IRQA_N_IS_GPIO BALL_AE31_IS_GPIO
#endif 

#define BALL_AE30 PAD_PCM2_WAIT_N
#define PAD_PCM2_WAIT_N 104
#define GPIO_PAD_104 GPIO103
#ifndef BALL_AE30_IS_GPIO
#define BALL_AE30_IS_GPIO 0
#endif 
#ifndef PAD_PCM2_WAIT_N_IS_GPIO
#define PAD_PCM2_WAIT_N_IS_GPIO BALL_AE30_IS_GPIO
#endif 

#define BALL_AG28 PAD_PCM2_RESET
#define PAD_PCM2_RESET 105
#define GPIO_PAD_105 GPIO104
#ifndef BALL_AG28_IS_GPIO
#define BALL_AG28_IS_GPIO 0
#endif 
#ifndef PAD_PCM2_RESET_IS_GPIO
#define PAD_PCM2_RESET_IS_GPIO BALL_AG28_IS_GPIO
#endif 

#define BALL_AG16 PAD_PCM_CE_N
#define PAD_PCM_CE_N 112
#define GPIO_PAD_112 GPIO111
#ifndef BALL_AG16_IS_GPIO
#define BALL_AG16_IS_GPIO 0
#endif 
#ifndef PAD_PCM_CE_N_IS_GPIO
#define PAD_PCM_CE_N_IS_GPIO BALL_AG16_IS_GPIO
#endif 

#define BALL_AH29 PAD_PCM2_CD_N
#define PAD_PCM2_CD_N 106
#define GPIO_PAD_106 GPIO105
#ifndef BALL_AH29_IS_GPIO
#define BALL_AH29_IS_GPIO 0
#endif 
#ifndef PAD_PCM2_CD_N_IS_GPIO
#define PAD_PCM2_CD_N_IS_GPIO BALL_AH29_IS_GPIO
#endif 

#define BALL_AG19 PAD_PCM_RESET
#define PAD_PCM_RESET 138
#define GPIO_PAD_138 GPIO137
#ifndef BALL_AG19_IS_GPIO
#define BALL_AG19_IS_GPIO 0
#endif 
#ifndef PAD_PCM_RESET_IS_GPIO
#define PAD_PCM_RESET_IS_GPIO BALL_AG19_IS_GPIO
#endif 

#define BALL_AH16 PAD_PCM_CD_N
#define PAD_PCM_CD_N 139
#define GPIO_PAD_139 GPIO138
#ifndef BALL_AH16_IS_GPIO
#define BALL_AH16_IS_GPIO 0
#endif 
#ifndef PAD_PCM_CD_N_IS_GPIO
#define PAD_PCM_CD_N_IS_GPIO BALL_AH16_IS_GPIO
#endif 

#define BALL_AG20 PAD_PCM_WAIT_N
#define PAD_PCM_WAIT_N 128
#define GPIO_PAD_128 GPIO127
#ifndef BALL_AG20_IS_GPIO
#define BALL_AG20_IS_GPIO 0
#endif 
#ifndef PAD_PCM_WAIT_N_IS_GPIO
#define PAD_PCM_WAIT_N_IS_GPIO BALL_AG20_IS_GPIO
#endif 

#define BALL_AM17 PAD_PCM_IRQA_N
#define PAD_PCM_IRQA_N 123
#define GPIO_PAD_123 GPIO122
#ifndef BALL_AM17_IS_GPIO
#define BALL_AM17_IS_GPIO 0
#endif 
#ifndef PAD_PCM_IRQA_N_IS_GPIO
#define PAD_PCM_IRQA_N_IS_GPIO BALL_AM17_IS_GPIO
#endif 

#define BALL_AM15 PAD_PCM_IOWR_N
#define PAD_PCM_IOWR_N 118
#define GPIO_PAD_118 GPIO117
#ifndef BALL_AM15_IS_GPIO
#define BALL_AM15_IS_GPIO 0
#endif 
#ifndef PAD_PCM_IOWR_N_IS_GPIO
#define PAD_PCM_IOWR_N_IS_GPIO BALL_AM15_IS_GPIO
#endif 

#define BALL_AH20 PAD_PCM_REG_N
#define PAD_PCM_REG_N 132
#define GPIO_PAD_132 GPIO131
#ifndef BALL_AH20_IS_GPIO
#define BALL_AH20_IS_GPIO 0
#endif 
#ifndef PAD_PCM_REG_N_IS_GPIO
#define PAD_PCM_REG_N_IS_GPIO BALL_AH20_IS_GPIO
#endif 

#define BALL_AL17 PAD_PCM_WE_N
#define PAD_PCM_WE_N 122
#define GPIO_PAD_122 GPIO121
#ifndef BALL_AL17_IS_GPIO
#define BALL_AL17_IS_GPIO 0
#endif 
#ifndef PAD_PCM_WE_N_IS_GPIO
#define PAD_PCM_WE_N_IS_GPIO BALL_AL17_IS_GPIO
#endif 

#define BALL_AD30 PAD_VSYNC_Like
#define PAD_VSYNC_Like 89
#define GPIO_PAD_89 GPIO88
#ifndef BALL_AD30_IS_GPIO
#define BALL_AD30_IS_GPIO 0
#endif 
#ifndef PAD_VSYNC_Like_IS_GPIO
#define PAD_VSYNC_Like_IS_GPIO BALL_AD30_IS_GPIO
#endif 

#define BALL_AD32 PAD_SPI1_DI
#define PAD_SPI1_DI 91
#define GPIO_PAD_91 GPIO90
#ifndef BALL_AD32_IS_GPIO
#define BALL_AD32_IS_GPIO 0
#endif 
#ifndef PAD_SPI1_DI_IS_GPIO
#define PAD_SPI1_DI_IS_GPIO BALL_AD32_IS_GPIO
#endif 

#define BALL_AD31 PAD_SPI1_CK
#define PAD_SPI1_CK 90
#define GPIO_PAD_90 GPIO89
#ifndef BALL_AD31_IS_GPIO
#define BALL_AD31_IS_GPIO 0
#endif 
#ifndef PAD_SPI1_CK_IS_GPIO
#define PAD_SPI1_CK_IS_GPIO BALL_AD31_IS_GPIO
#endif 

#define BALL_AC30 PAD_SPI2_DI
#define PAD_SPI2_DI 93
#define GPIO_PAD_93 GPIO92
#ifndef BALL_AC30_IS_GPIO
#define BALL_AC30_IS_GPIO 0
#endif 
#ifndef PAD_SPI2_DI_IS_GPIO
#define PAD_SPI2_DI_IS_GPIO BALL_AC30_IS_GPIO
#endif 

#define BALL_AC31 PAD_SPI2_CK
#define PAD_SPI2_CK 92
#define GPIO_PAD_92 GPIO91
#ifndef BALL_AC31_IS_GPIO
#define BALL_AC31_IS_GPIO 0
#endif 
#ifndef PAD_SPI2_CK_IS_GPIO
#define PAD_SPI2_CK_IS_GPIO BALL_AC31_IS_GPIO
#endif 

#define PAD_GPIO18 9999
#ifndef PAD_GPIO18_IS_GPIO
#define PAD_GPIO18_IS_GPIO 0
#endif 

#define BALL_F5 PAD_DDCR_CK
#define PAD_DDCR_CK 48
#define GPIO_PAD_48 GPIO47
#ifndef BALL_F5_IS_GPIO
#define BALL_F5_IS_GPIO 0
#endif 
#ifndef PAD_DDCR_CK_IS_GPIO
#define PAD_DDCR_CK_IS_GPIO BALL_F5_IS_GPIO
#endif 

#define BALL_C4 PAD_GPIO19
#define PAD_GPIO19 68
#define GPIO_PAD_68 GPIO67
#ifndef BALL_C4_IS_GPIO
#define BALL_C4_IS_GPIO 0
#endif 
#ifndef PAD_GPIO19_IS_GPIO
#define PAD_GPIO19_IS_GPIO BALL_C4_IS_GPIO
#endif 

#define BALL_F4 PAD_DDCR_DA
#define PAD_DDCR_DA 47
#define GPIO_PAD_47 GPIO46
#ifndef BALL_F4_IS_GPIO
#define BALL_F4_IS_GPIO 0
#endif 
#ifndef PAD_DDCR_DA_IS_GPIO
#define PAD_DDCR_DA_IS_GPIO BALL_F4_IS_GPIO
#endif 

#define BALL_A3 PAD_GPIO20
#define PAD_GPIO20 69
#define GPIO_PAD_69 GPIO68
#ifndef BALL_A3_IS_GPIO
#define BALL_A3_IS_GPIO 0
#endif 
#ifndef PAD_GPIO20_IS_GPIO
#define PAD_GPIO20_IS_GPIO BALL_A3_IS_GPIO
#endif 

#define BALL_B7 PAD_PWM0
#define PAD_PWM0 140
#define GPIO_PAD_140 GPIO139
#ifndef BALL_B7_IS_GPIO
#define BALL_B7_IS_GPIO 0
#endif 
#ifndef PAD_PWM0_IS_GPIO
#define PAD_PWM0_IS_GPIO BALL_B7_IS_GPIO
#endif 

#define PAD_GPIO21 9999
#ifndef PAD_GPIO21_IS_GPIO
#define PAD_GPIO21_IS_GPIO 0
#endif 

#define BALL_C8 PAD_PWM1
#define PAD_PWM1 141
#define GPIO_PAD_141 GPIO140
#ifndef BALL_C8_IS_GPIO
#define BALL_C8_IS_GPIO 0
#endif 
#ifndef PAD_PWM1_IS_GPIO
#define PAD_PWM1_IS_GPIO BALL_C8_IS_GPIO
#endif 

#define PAD_GPIO22 9999
#ifndef PAD_GPIO22_IS_GPIO
#define PAD_GPIO22_IS_GPIO 0
#endif 

#define BALL_B8 PAD_PWM2
#define PAD_PWM2 142
#define GPIO_PAD_142 GPIO141
#ifndef BALL_B8_IS_GPIO
#define BALL_B8_IS_GPIO 0
#endif 
#ifndef PAD_PWM2_IS_GPIO
#define PAD_PWM2_IS_GPIO BALL_B8_IS_GPIO
#endif 

#define PAD_GPIO25 9999
#ifndef PAD_GPIO25_IS_GPIO
#define PAD_GPIO25_IS_GPIO 0
#endif 

#define BALL_C7 PAD_PWM3
#define PAD_PWM3 143
#define GPIO_PAD_143 GPIO142
#ifndef BALL_C7_IS_GPIO
#define BALL_C7_IS_GPIO 0
#endif 
#ifndef PAD_PWM3_IS_GPIO
#define PAD_PWM3_IS_GPIO BALL_C7_IS_GPIO
#endif 

#define PAD_GPIO26 9999
#ifndef PAD_GPIO26_IS_GPIO
#define PAD_GPIO26_IS_GPIO 0
#endif 

#define PAD_PWM4 9999
#ifndef PAD_PWM4_IS_GPIO
#define PAD_PWM4_IS_GPIO 0
#endif 

#define PAD_GPIO7 9999
#ifndef PAD_GPIO7_IS_GPIO
#define PAD_GPIO7_IS_GPIO 0
#endif 

#define PAD_GPIO27 9999
#ifndef PAD_GPIO27_IS_GPIO
#define PAD_GPIO27_IS_GPIO 0
#endif 

#define BALL_G5 PAD_SPDIF_OUT
#define PAD_SPDIF_OUT 81
#define GPIO_PAD_81 GPIO80
#ifndef BALL_G5_IS_GPIO
#define BALL_G5_IS_GPIO 0
#endif 
#ifndef PAD_SPDIF_OUT_IS_GPIO
#define PAD_SPDIF_OUT_IS_GPIO BALL_G5_IS_GPIO
#endif 

#define BALL_H7 PAD_I2S_OUT_BCK
#define PAD_I2S_OUT_BCK 84
#define GPIO_PAD_84 GPIO83
#ifndef BALL_H7_IS_GPIO
#define BALL_H7_IS_GPIO 0
#endif 
#ifndef PAD_I2S_OUT_BCK_IS_GPIO
#define PAD_I2S_OUT_BCK_IS_GPIO BALL_H7_IS_GPIO
#endif 

#define PAD_GPIO23 9999
#ifndef PAD_GPIO23_IS_GPIO
#define PAD_GPIO23_IS_GPIO 0
#endif 

#define BALL_H5 PAD_I2S_OUT_MCK
#define PAD_I2S_OUT_MCK 83
#define GPIO_PAD_83 GPIO82
#ifndef BALL_H5_IS_GPIO
#define BALL_H5_IS_GPIO 0
#endif 
#ifndef PAD_I2S_OUT_MCK_IS_GPIO
#define PAD_I2S_OUT_MCK_IS_GPIO BALL_H5_IS_GPIO
#endif 

#define PAD_GPIO24 9999
#ifndef PAD_GPIO24_IS_GPIO
#define PAD_GPIO24_IS_GPIO 0
#endif 

#define BALL_H4 PAD_I2S_OUT_WS
#define PAD_I2S_OUT_WS 82
#define GPIO_PAD_82 GPIO81
#ifndef BALL_H4_IS_GPIO
#define BALL_H4_IS_GPIO 0
#endif 
#ifndef PAD_I2S_OUT_WS_IS_GPIO
#define PAD_I2S_OUT_WS_IS_GPIO BALL_H4_IS_GPIO
#endif 

#define BALL_G6 PAD_SPDIF_IN
#define PAD_SPDIF_IN 80
#define GPIO_PAD_80 GPIO79
#ifndef BALL_G6_IS_GPIO
#define BALL_G6_IS_GPIO 0
#endif 
#ifndef PAD_SPDIF_IN_IS_GPIO
#define PAD_SPDIF_IN_IS_GPIO BALL_G6_IS_GPIO
#endif 

#define PAD_GPIO13 9999
#ifndef PAD_GPIO13_IS_GPIO
#define PAD_GPIO13_IS_GPIO 0
#endif 

#define BALL_H6 PAD_I2S_OUT_SD
#define PAD_I2S_OUT_SD 85
#define GPIO_PAD_85 GPIO84
#ifndef BALL_H6_IS_GPIO
#define BALL_H6_IS_GPIO 0
#endif 
#ifndef PAD_I2S_OUT_SD_IS_GPIO
#define PAD_I2S_OUT_SD_IS_GPIO BALL_H6_IS_GPIO
#endif 

#define PAD_GPIO14 9999
#ifndef PAD_GPIO14_IS_GPIO
#define PAD_GPIO14_IS_GPIO 0
#endif 

#define PAD_I2S_OUT_SD1 9999
#ifndef PAD_I2S_OUT_SD1_IS_GPIO
#define PAD_I2S_OUT_SD1_IS_GPIO 0
#endif 

#define PAD_GPIO15 9999
#ifndef PAD_GPIO15_IS_GPIO
#define PAD_GPIO15_IS_GPIO 0
#endif 

#define PAD_I2S_OUT_SD2 9999
#ifndef PAD_I2S_OUT_SD2_IS_GPIO
#define PAD_I2S_OUT_SD2_IS_GPIO 0
#endif 

#define PAD_GPIO16 9999
#ifndef PAD_GPIO16_IS_GPIO
#define PAD_GPIO16_IS_GPIO 0
#endif 

#define PAD_I2S_OUT_SD3 9999
#ifndef PAD_I2S_OUT_SD3_IS_GPIO
#define PAD_I2S_OUT_SD3_IS_GPIO 0
#endif 

#define PAD_GPIO17 9999
#ifndef PAD_GPIO17_IS_GPIO
#define PAD_GPIO17_IS_GPIO 0
#endif 

#define BALL_E5 PAD_I2S_IN_WS
#define PAD_I2S_IN_WS 77
#define GPIO_PAD_77 GPIO76
#ifndef BALL_E5_IS_GPIO
#define BALL_E5_IS_GPIO 0
#endif 
#ifndef PAD_I2S_IN_WS_IS_GPIO
#define PAD_I2S_IN_WS_IS_GPIO BALL_E5_IS_GPIO
#endif 

#define BALL_E6 PAD_I2S_IN_BCK
#define PAD_I2S_IN_BCK 78
#define GPIO_PAD_78 GPIO77
#ifndef BALL_E6_IS_GPIO
#define BALL_E6_IS_GPIO 0
#endif 
#ifndef PAD_I2S_IN_BCK_IS_GPIO
#define PAD_I2S_IN_BCK_IS_GPIO BALL_E6_IS_GPIO
#endif 

#define BALL_F6 PAD_I2S_IN_SD
#define PAD_I2S_IN_SD 79
#define GPIO_PAD_79 GPIO78
#ifndef BALL_F6_IS_GPIO
#define BALL_F6_IS_GPIO 0
#endif 
#ifndef PAD_I2S_IN_SD_IS_GPIO
#define PAD_I2S_IN_SD_IS_GPIO BALL_F6_IS_GPIO
#endif 

#define PAD_GPIO0 9999
#ifndef PAD_GPIO0_IS_GPIO
#define PAD_GPIO0_IS_GPIO 0
#endif 

#define PAD_GPIO1 9999
#ifndef PAD_GPIO1_IS_GPIO
#define PAD_GPIO1_IS_GPIO 0
#endif 

#define BALL_C6 PAD_GPIO2
#define PAD_GPIO2 51
#define GPIO_PAD_51 GPIO50
#ifndef BALL_C6_IS_GPIO
#define BALL_C6_IS_GPIO 0
#endif 
#ifndef PAD_GPIO2_IS_GPIO
#define PAD_GPIO2_IS_GPIO BALL_C6_IS_GPIO
#endif 

#define BALL_B6 PAD_GPIO3
#define PAD_GPIO3 52
#define GPIO_PAD_52 GPIO51
#ifndef BALL_B6_IS_GPIO
#define BALL_B6_IS_GPIO 0
#endif 
#ifndef PAD_GPIO3_IS_GPIO
#define PAD_GPIO3_IS_GPIO BALL_B6_IS_GPIO
#endif 

#define BALL_A6 PAD_GPIO4
#define PAD_GPIO4 53
#define GPIO_PAD_53 GPIO52
#ifndef BALL_A6_IS_GPIO
#define BALL_A6_IS_GPIO 0
#endif 
#ifndef PAD_GPIO4_IS_GPIO
#define PAD_GPIO4_IS_GPIO BALL_A6_IS_GPIO
#endif 

#define PAD_GPIO5 9999
#ifndef PAD_GPIO5_IS_GPIO
#define PAD_GPIO5_IS_GPIO 0
#endif 

#define PAD_GPIO6 9999
#ifndef PAD_GPIO6_IS_GPIO
#define PAD_GPIO6_IS_GPIO 0
#endif 

#define PAD_GPIO8 9999
#ifndef PAD_GPIO8_IS_GPIO
#define PAD_GPIO8_IS_GPIO 0
#endif 

#define PAD_GPIO9 9999
#ifndef PAD_GPIO9_IS_GPIO
#define PAD_GPIO9_IS_GPIO 0
#endif 

#define PAD_GPIO10 9999
#ifndef PAD_GPIO10_IS_GPIO
#define PAD_GPIO10_IS_GPIO 0
#endif 

#define PAD_GPIO11 9999
#ifndef PAD_GPIO11_IS_GPIO
#define PAD_GPIO11_IS_GPIO 0
#endif 

#define PAD_GPIO12 9999
#ifndef PAD_GPIO12_IS_GPIO
#define PAD_GPIO12_IS_GPIO 0
#endif 

#define BALL_K6 PAD_SAR0
#define PAD_SAR0 42
#define GPIO_PAD_42 GPIO41
#ifndef BALL_K6_IS_GPIO
#define BALL_K6_IS_GPIO 0
#endif 
#ifndef PAD_SAR0_IS_GPIO
#define PAD_SAR0_IS_GPIO BALL_K6_IS_GPIO
#endif 

#define BALL_L5 PAD_SAR1
#define PAD_SAR1 43
#define GPIO_PAD_43 GPIO42
#ifndef BALL_L5_IS_GPIO
#define BALL_L5_IS_GPIO 0
#endif 
#ifndef PAD_SAR1_IS_GPIO
#define PAD_SAR1_IS_GPIO BALL_L5_IS_GPIO
#endif 

#define BALL_L6 PAD_SAR2
#define PAD_SAR2 44
#define GPIO_PAD_44 GPIO43
#ifndef BALL_L6_IS_GPIO
#define BALL_L6_IS_GPIO 0
#endif 
#ifndef PAD_SAR2_IS_GPIO
#define PAD_SAR2_IS_GPIO BALL_L6_IS_GPIO
#endif 

#define BALL_L4 PAD_SAR3
#define PAD_SAR3 45
#define GPIO_PAD_45 GPIO44
#ifndef BALL_L4_IS_GPIO
#define BALL_L4_IS_GPIO 0
#endif 
#ifndef PAD_SAR3_IS_GPIO
#define PAD_SAR3_IS_GPIO BALL_L4_IS_GPIO
#endif 

#define PAD_SAR4 9999
#ifndef PAD_SAR4_IS_GPIO
#define PAD_SAR4_IS_GPIO 0
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
#define CHIP_FAMILY_TYPE           CHIP_FAMILY_EDISON

#endif /* _MSD8560IV_H_*/
