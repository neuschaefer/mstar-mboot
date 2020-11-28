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
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define GPIO1_PAD PAD_PM_SPI_CK
#define GPIO1_OEN 0x0f30, BIT0
#define GPIO1_OUT 0x0f30, BIT1
#define GPIO1_IN  0x0f30, BIT2
#define PAD_PM_SPI_CK_OUT_REG 0x0f30
#define PAD_PM_SPI_CK_OUT_MASK BIT1

#define GPIO2_PAD PAD_PM_SPI_DI
#define GPIO2_OEN 0x0f32, BIT0
#define GPIO2_OUT 0x0f32, BIT1
#define GPIO2_IN  0x0f32, BIT2
#define PAD_PM_SPI_DI_OUT_REG 0x0f32
#define PAD_PM_SPI_DI_OUT_MASK BIT1

#define GPIO3_PAD PAD_PM_SPI_DO
#define GPIO3_OEN 0x0f34, BIT0
#define GPIO3_OUT 0x0f34, BIT1
#define GPIO3_IN  0x0f34, BIT2
#define PAD_PM_SPI_DO_OUT_REG 0x0f34
#define PAD_PM_SPI_DO_OUT_MASK BIT1

#define GPIO4_PAD PAD_IRIN
#define GPIO4_OEN 0x0f26, BIT0
#define GPIO4_OUT 0x0f26, BIT1
#define GPIO4_IN  0x0f26, BIT2
#define PAD_IRIN_OUT_REG 0x0f26
#define PAD_IRIN_OUT_MASK BIT1

#define GPIO5_PAD PAD_CEC
#define GPIO5_OEN 0x0f2a, BIT0
#define GPIO5_OUT 0x0f2a, BIT1
#define GPIO5_IN  0x0f2a, BIT2
#define PAD_CEC_OUT_REG 0x0f2a
#define PAD_CEC_OUT_MASK BIT1

#define GPIO6_PAD PAD_AV_LNK
#define GPIO6_OEN 0x0f2c, BIT0
#define GPIO6_OUT 0x0f2c, BIT1
#define GPIO6_IN  0x0f2c, BIT2
#define PAD_AV_LNK_OUT_REG 0x0f2c
#define PAD_AV_LNK_OUT_MASK BIT1

#define GPIO7_PAD PAD_PWM_PM
#define GPIO7_OEN 0x0f28, BIT0
#define GPIO7_OUT 0x0f28, BIT1
#define GPIO7_IN  0x0f28, BIT2
#define PAD_PWM_PM_OUT_REG 0x0f28
#define PAD_PWM_PM_OUT_MASK BIT1

#define GPIO8_PAD PAD_GPIO_PM0
#define GPIO8_OEN 0x0f00, BIT0
#define GPIO8_OUT 0x0f00, BIT1
#define GPIO8_IN  0x0f00, BIT2
#define PAD_GPIO_PM0_OUT_REG 0x0f00
#define PAD_GPIO_PM0_OUT_MASK BIT1

#define GPIO9_PAD PAD_GPIO_PM1
#define GPIO9_OEN 0x0f02, BIT0
#define GPIO9_OUT 0x0f02, BIT1
#define GPIO9_IN  0x0f02, BIT2
#define PAD_GPIO_PM1_OUT_REG 0x0f02
#define PAD_GPIO_PM1_OUT_MASK BIT1

#define GPIO10_PAD PAD_GPIO_PM2
#define GPIO10_OEN 0x0f04, BIT0
#define GPIO10_OUT 0x0f04, BIT1
#define GPIO10_IN  0x0f04, BIT2
#define PAD_GPIO_PM2_OUT_REG 0x0f04
#define PAD_GPIO_PM2_OUT_MASK BIT1

#define GPIO11_PAD PAD_GPIO_PM3
#define GPIO11_OEN 0x0f06, BIT0
#define GPIO11_OUT 0x0f06, BIT1
#define GPIO11_IN  0x0f06, BIT2
#define PAD_GPIO_PM3_OUT_REG 0x0f06
#define PAD_GPIO_PM3_OUT_MASK BIT1

#define GPIO12_PAD PAD_GPIO_PM4
#define GPIO12_OEN 0x0f08, BIT0
#define GPIO12_OUT 0x0f08, BIT1
#define GPIO12_IN  0x0f08, BIT2
#define PAD_GPIO_PM4_OUT_REG 0x0f08
#define PAD_GPIO_PM4_OUT_MASK BIT1

#define GPIO13_PAD PAD_GPIO_PM5
#define GPIO13_OEN 0x0f0a, BIT0
#define GPIO13_OUT 0x0f0a, BIT1
#define GPIO13_IN  0x0f0a, BIT2
#define PAD_GPIO_PM5_OUT_REG 0x0f0a
#define PAD_GPIO_PM5_OUT_MASK BIT1

#define GPIO14_PAD PAD_GPIO_PM6
#define GPIO14_OEN 0x0f0c, BIT0
#define GPIO14_OUT 0x0f0c, BIT1
#define GPIO14_IN  0x0f0c, BIT2
#define PAD_GPIO_PM6_OUT_REG 0x0f0c
#define PAD_GPIO_PM6_OUT_MASK BIT1

#define GPIO15_PAD PAD_GPIO_PM7
#define GPIO15_OEN 0x0f0e, BIT0
#define GPIO15_OUT 0x0f0e, BIT1
#define GPIO15_IN  0x0f0e, BIT2
#define PAD_GPIO_PM7_OUT_REG 0x0f0e
#define PAD_GPIO_PM7_OUT_MASK BIT1

#define GPIO16_PAD PAD_GPIO_PM8
#define GPIO16_OEN 0x0f10, BIT0
#define GPIO16_OUT 0x0f10, BIT1
#define GPIO16_IN  0x0f10, BIT2
#define PAD_GPIO_PM8_OUT_REG 0x0f10
#define PAD_GPIO_PM8_OUT_MASK BIT1

#define GPIO17_PAD PAD_GPIO_PM9
#define GPIO17_OEN 0x0f12, BIT0
#define GPIO17_OUT 0x0f12, BIT1
#define GPIO17_IN  0x0f12, BIT2
#define PAD_GPIO_PM9_OUT_REG 0x0f12
#define PAD_GPIO_PM9_OUT_MASK BIT1

#define GPIO18_PAD PAD_GPIO_PM10
#define GPIO18_OEN 0x0f14, BIT0
#define GPIO18_OUT 0x0f14, BIT1
#define GPIO18_IN  0x0f14, BIT2
#define PAD_GPIO_PM10_OUT_REG 0x0f14
#define PAD_GPIO_PM10_OUT_MASK BIT1

#define GPIO19_PAD PAD_GPIO_PM11
#define GPIO19_OEN 0x0f16, BIT0
#define GPIO19_OUT 0x0f16, BIT1
#define GPIO19_IN  0x0f16, BIT2
#define PAD_GPIO_PM11_OUT_REG 0x0f16
#define PAD_GPIO_PM11_OUT_MASK BIT1

#define GPIO20_PAD PAD_GPIO_PM12
#define GPIO20_OEN 0x0f18, BIT0
#define GPIO20_OUT 0x0f18, BIT1
#define GPIO20_IN  0x0f18, BIT2
#define PAD_GPIO_PM12_OUT_REG 0x0f18
#define PAD_GPIO_PM12_OUT_MASK BIT1

#define GPIO21_PAD PAD_GPIO_PM13
#define GPIO21_OEN 0x0f1a, BIT0
#define GPIO21_OUT 0x0f1a, BIT1
#define GPIO21_IN  0x0f1a, BIT2
#define PAD_GPIO_PM13_OUT_REG 0x0f1a
#define PAD_GPIO_PM13_OUT_MASK BIT1

#define GPIO22_PAD PAD_GPIO_PM14
#define GPIO22_OEN 0x0f1c, BIT0
#define GPIO22_OUT 0x0f1c, BIT1
#define GPIO22_IN  0x0f1c, BIT2
#define PAD_GPIO_PM14_OUT_REG 0x0f1c
#define PAD_GPIO_PM14_OUT_MASK BIT1

#define GPIO23_PAD PAD_GPIO_PM15
#define GPIO23_OEN 0x0f1e, BIT0
#define GPIO23_OUT 0x0f1e, BIT1
#define GPIO23_IN  0x0f1e, BIT2
#define PAD_GPIO_PM15_OUT_REG 0x0f1e
#define PAD_GPIO_PM15_OUT_MASK BIT1

#define GPIO24_PAD PAD_GPIO_PM16
#define GPIO24_OEN 0x0f20, BIT0
#define GPIO24_OUT 0x0f20, BIT1
#define GPIO24_IN  0x0f20, BIT2
#define PAD_GPIO_PM16_OUT_REG 0x0f20
#define PAD_GPIO_PM16_OUT_MASK BIT1

#define GPIO25_PAD PAD_GPIO_PM17
#define GPIO25_OEN 0x0f22, BIT0
#define GPIO25_OUT 0x0f22, BIT1
#define GPIO25_IN  0x0f22, BIT2
#define PAD_GPIO_PM17_OUT_REG 0x0f22
#define PAD_GPIO_PM17_OUT_MASK BIT1

#define GPIO26_PAD PAD_GPIO_PM18
#define GPIO26_OEN 0x0f24, BIT0
#define GPIO26_OUT 0x0f24, BIT1
#define GPIO26_IN  0x0f24, BIT2
#define PAD_GPIO_PM18_OUT_REG 0x0f24
#define PAD_GPIO_PM18_OUT_MASK BIT1

#define GPIO27_PAD PAD_HOTPLUGA
#define GPIO27_OEN 0x0e4e, BIT0
#define GPIO27_OUT 0x0e4e, BIT4
#define GPIO27_IN  0x0e4f, BIT0
#define PAD_HOTPLUGA_OUT_REG 0x0e4e
#define PAD_HOTPLUGA_OUT_MASK BIT4

#define GPIO28_PAD PAD_HOTPLUGB
#define GPIO28_OEN 0x0e4e, BIT1
#define GPIO28_OUT 0x0e4e, BIT5
#define GPIO28_IN  0x0e4f, BIT1
#define PAD_HOTPLUGB_OUT_REG 0x0e4e
#define PAD_HOTPLUGB_OUT_MASK BIT5

#define GPIO29_PAD PAD_HOTPLUGC
#define GPIO29_OEN 0x0e4e, BIT2
#define GPIO29_OUT 0x0e4e, BIT6
#define GPIO29_IN  0x0e4f, BIT2
#define PAD_HOTPLUGC_OUT_REG 0x0e4e
#define PAD_HOTPLUGC_OUT_MASK BIT6

#define GPIO30_PAD PAD_HOTPLUGD
#define GPIO30_OEN 0x0e4e, BIT3
#define GPIO30_OUT 0x0e4e, BIT7
#define GPIO30_IN  0x0e4f, BIT3
#define PAD_HOTPLUGD_OUT_REG 0x0e4e
#define PAD_HOTPLUGD_OUT_MASK BIT7

#define GPIO31_PAD PAD_DDCA_CK
#define GPIO31_OEN 0x0494, BIT1
#define GPIO31_OUT 0x0494, BIT2
#define GPIO31_IN  0x0494, BIT0
#define PAD_DDCA_CK_OUT_REG 0x0494
#define PAD_DDCA_CK_OUT_MASK BIT2

#define GPIO32_PAD PAD_DDCA_DA
#define GPIO32_OEN 0x0494, BIT5
#define GPIO32_OUT 0x0494, BIT6
#define GPIO32_IN  0x0494, BIT4
#define PAD_DDCA_DA_OUT_REG 0x0494
#define PAD_DDCA_DA_OUT_MASK BIT6

#define GPIO33_PAD PAD_DDCDA_CK
#define GPIO33_OEN 0x0496, BIT1
#define GPIO33_OUT 0x0496, BIT2
#define GPIO33_IN  0x0496, BIT0
#define PAD_DDCDA_CK_OUT_REG 0x0496
#define PAD_DDCDA_CK_OUT_MASK BIT2

#define GPIO34_PAD PAD_DDCDA_DA
#define GPIO34_OEN 0x0496, BIT5
#define GPIO34_OUT 0x0496, BIT6
#define GPIO34_IN  0x0496, BIT4
#define PAD_DDCDA_DA_OUT_REG 0x0496
#define PAD_DDCDA_DA_OUT_MASK BIT6

#define GPIO35_PAD PAD_DDCDB_CK
#define GPIO35_OEN 0x0497, BIT1
#define GPIO35_OUT 0x0497, BIT2
#define GPIO35_IN  0x0497, BIT0
#define PAD_DDCDB_CK_OUT_REG 0x0497
#define PAD_DDCDB_CK_OUT_MASK BIT2

#define GPIO36_PAD PAD_DDCDB_DA
#define GPIO36_OEN 0x0497, BIT5
#define GPIO36_OUT 0x0497, BIT6
#define GPIO36_IN  0x0497, BIT4
#define PAD_DDCDB_DA_OUT_REG 0x0497
#define PAD_DDCDB_DA_OUT_MASK BIT6

#define GPIO37_PAD PAD_DDCDC_CK
#define GPIO37_OEN 0x0498, BIT1
#define GPIO37_OUT 0x0498, BIT2
#define GPIO37_IN  0x0498, BIT0
#define PAD_DDCDC_CK_OUT_REG 0x0498
#define PAD_DDCDC_CK_OUT_MASK BIT2

#define GPIO38_PAD PAD_DDCDC_DA
#define GPIO38_OEN 0x0498, BIT5
#define GPIO38_OUT 0x0498, BIT6
#define GPIO38_IN  0x0498, BIT4
#define PAD_DDCDC_DA_OUT_REG 0x0498
#define PAD_DDCDC_DA_OUT_MASK BIT6

#define GPIO39_PAD PAD_DDCDD_CK
#define GPIO39_OEN 0x0499, BIT1
#define GPIO39_OUT 0x0499, BIT2
#define GPIO39_IN  0x0499, BIT0
#define PAD_DDCDD_CK_OUT_REG 0x0499
#define PAD_DDCDD_CK_OUT_MASK BIT2

#define GPIO40_PAD PAD_DDCDD_DA
#define GPIO40_OEN 0x0499, BIT5
#define GPIO40_OUT 0x0499, BIT6
#define GPIO40_IN  0x0499, BIT4
#define PAD_DDCDD_DA_OUT_REG 0x0499
#define PAD_DDCDD_DA_OUT_MASK BIT6

#define GPIO41_PAD PAD_SAR0
#define GPIO41_OEN 0x1423, BIT0
#define GPIO41_OUT 0x1424, BIT0
#define GPIO41_IN  0x1425, BIT0
#define PAD_SAR0_OUT_REG 0x1424
#define PAD_SAR0_OUT_MASK BIT0

#define GPIO42_PAD PAD_SAR1
#define GPIO42_OEN 0x1423, BIT1
#define GPIO42_OUT 0x1424, BIT1
#define GPIO42_IN  0x1425, BIT1
#define PAD_SAR1_OUT_REG 0x1424
#define PAD_SAR1_OUT_MASK BIT1

#define GPIO43_PAD PAD_SAR2
#define GPIO43_OEN 0x1423, BIT2
#define GPIO43_OUT 0x1424, BIT2
#define GPIO43_IN  0x1425, BIT2
#define PAD_SAR2_OUT_REG 0x1424
#define PAD_SAR2_OUT_MASK BIT2

#define GPIO44_PAD PAD_SAR3
#define GPIO44_OEN 0x1423, BIT3
#define GPIO44_OUT 0x1424, BIT3
#define GPIO44_IN  0x1425, BIT3
#define PAD_SAR3_OUT_REG 0x1424
#define PAD_SAR3_OUT_MASK BIT3

#define GPIO45_PAD PAD_SAR4
#define GPIO45_OEN 0x1423, BIT4
#define GPIO45_OUT 0x1424, BIT4
#define GPIO45_IN  0x1425, BIT4
#define PAD_SAR4_OUT_REG 0x1424
#define PAD_SAR4_OUT_MASK BIT4

#define GPIO46_PAD PAD_DDCR_DA
#define GPIO46_OEN 0x102b86, BIT1
#define GPIO46_OUT 0x102b86, BIT0
#define GPIO46_IN  0x102b86, BIT2
#define PAD_DDCR_DA_OUT_REG 0x102b86
#define PAD_DDCR_DA_OUT_MASK BIT0

#define GPIO47_PAD PAD_DDCR_CK
#define GPIO47_OEN 0x102b87, BIT1
#define GPIO47_OUT 0x102b87, BIT0
#define GPIO47_IN  0x102b87, BIT2
#define PAD_DDCR_CK_OUT_REG 0x102b87
#define PAD_DDCR_CK_OUT_MASK BIT0

#define GPIO48_PAD PAD_GPIO0
#define GPIO48_OEN 0x102b00, BIT1
#define GPIO48_OUT 0x102b00, BIT0
#define GPIO48_IN  0x102b00, BIT2
#define PAD_GPIO0_OUT_REG 0x102b00
#define PAD_GPIO0_OUT_MASK BIT0

#define GPIO49_PAD PAD_GPIO1
#define GPIO49_OEN 0x102b01, BIT1
#define GPIO49_OUT 0x102b01, BIT0
#define GPIO49_IN  0x102b01, BIT2
#define PAD_GPIO1_OUT_REG 0x102b01
#define PAD_GPIO1_OUT_MASK BIT0

#define GPIO50_PAD PAD_GPIO2
#define GPIO50_OEN 0x102b02, BIT1
#define GPIO50_OUT 0x102b02, BIT0
#define GPIO50_IN  0x102b02, BIT2
#define PAD_GPIO2_OUT_REG 0x102b02
#define PAD_GPIO2_OUT_MASK BIT0

#define GPIO51_PAD PAD_GPIO3
#define GPIO51_OEN 0x102b03, BIT1
#define GPIO51_OUT 0x102b03, BIT0
#define GPIO51_IN  0x102b03, BIT2
#define PAD_GPIO3_OUT_REG 0x102b03
#define PAD_GPIO3_OUT_MASK BIT0

#define GPIO52_PAD PAD_GPIO4
#define GPIO52_OEN 0x102b04, BIT1
#define GPIO52_OUT 0x102b04, BIT0
#define GPIO52_IN  0x102b04, BIT2
#define PAD_GPIO4_OUT_REG 0x102b04
#define PAD_GPIO4_OUT_MASK BIT0

#define GPIO53_PAD PAD_GPIO5
#define GPIO53_OEN 0x102b05, BIT1
#define GPIO53_OUT 0x102b05, BIT0
#define GPIO53_IN  0x102b05, BIT2
#define PAD_GPIO5_OUT_REG 0x102b05
#define PAD_GPIO5_OUT_MASK BIT0

#define GPIO54_PAD PAD_GPIO6
#define GPIO54_OEN 0x102b06, BIT1
#define GPIO54_OUT 0x102b06, BIT0
#define GPIO54_IN  0x102b06, BIT2
#define PAD_GPIO6_OUT_REG 0x102b06
#define PAD_GPIO6_OUT_MASK BIT0

#define GPIO55_PAD PAD_GPIO7
#define GPIO55_OEN 0x102b07, BIT1
#define GPIO55_OUT 0x102b07, BIT0
#define GPIO55_IN  0x102b07, BIT2
#define PAD_GPIO7_OUT_REG 0x102b07
#define PAD_GPIO7_OUT_MASK BIT0

#define GPIO56_PAD PAD_GPIO8
#define GPIO56_OEN 0x102b08, BIT1
#define GPIO56_OUT 0x102b08, BIT0
#define GPIO56_IN  0x102b08, BIT2
#define PAD_GPIO8_OUT_REG 0x102b08
#define PAD_GPIO8_OUT_MASK BIT0

#define GPIO57_PAD PAD_GPIO9
#define GPIO57_OEN 0x102b09, BIT1
#define GPIO57_OUT 0x102b09, BIT0
#define GPIO57_IN  0x102b09, BIT2
#define PAD_GPIO9_OUT_REG 0x102b09
#define PAD_GPIO9_OUT_MASK BIT0

#define GPIO58_PAD PAD_GPIO10
#define GPIO58_OEN 0x102b0a, BIT1
#define GPIO58_OUT 0x102b0a, BIT0
#define GPIO58_IN  0x102b0a, BIT2
#define PAD_GPIO10_OUT_REG 0x102b0a
#define PAD_GPIO10_OUT_MASK BIT0

#define GPIO59_PAD PAD_GPIO11
#define GPIO59_OEN 0x102b0b, BIT1
#define GPIO59_OUT 0x102b0b, BIT0
#define GPIO59_IN  0x102b0b, BIT2
#define PAD_GPIO11_OUT_REG 0x102b0b
#define PAD_GPIO11_OUT_MASK BIT0

#define GPIO60_PAD PAD_GPIO12
#define GPIO60_OEN 0x102b0c, BIT1
#define GPIO60_OUT 0x102b0c, BIT0
#define GPIO60_IN  0x102b0c, BIT2
#define PAD_GPIO12_OUT_REG 0x102b0c
#define PAD_GPIO12_OUT_MASK BIT0

#define GPIO61_PAD PAD_GPIO13
#define GPIO61_OEN 0x102b0d, BIT1
#define GPIO61_OUT 0x102b0d, BIT0
#define GPIO61_IN  0x102b0d, BIT2
#define PAD_GPIO13_OUT_REG 0x102b0d
#define PAD_GPIO13_OUT_MASK BIT0

#define GPIO62_PAD PAD_GPIO14
#define GPIO62_OEN 0x102b0e, BIT1
#define GPIO62_OUT 0x102b0e, BIT0
#define GPIO62_IN  0x102b0e, BIT2
#define PAD_GPIO14_OUT_REG 0x102b0e
#define PAD_GPIO14_OUT_MASK BIT0

#define GPIO63_PAD PAD_GPIO15
#define GPIO63_OEN 0x102b0f, BIT1
#define GPIO63_OUT 0x102b0f, BIT0
#define GPIO63_IN  0x102b0f, BIT2
#define PAD_GPIO15_OUT_REG 0x102b0f
#define PAD_GPIO15_OUT_MASK BIT0

#define GPIO64_PAD PAD_GPIO16
#define GPIO64_OEN 0x102b10, BIT1
#define GPIO64_OUT 0x102b10, BIT0
#define GPIO64_IN  0x102b10, BIT2
#define PAD_GPIO16_OUT_REG 0x102b10
#define PAD_GPIO16_OUT_MASK BIT0

#define GPIO65_PAD PAD_GPIO17
#define GPIO65_OEN 0x102b11, BIT1
#define GPIO65_OUT 0x102b11, BIT0
#define GPIO65_IN  0x102b11, BIT2
#define PAD_GPIO17_OUT_REG 0x102b11
#define PAD_GPIO17_OUT_MASK BIT0

#define GPIO66_PAD PAD_GPIO18
#define GPIO66_OEN 0x102b12, BIT1
#define GPIO66_OUT 0x102b12, BIT0
#define GPIO66_IN  0x102b12, BIT2
#define PAD_GPIO18_OUT_REG 0x102b12
#define PAD_GPIO18_OUT_MASK BIT0

#define GPIO67_PAD PAD_GPIO19
#define GPIO67_OEN 0x102b13, BIT1
#define GPIO67_OUT 0x102b13, BIT0
#define GPIO67_IN  0x102b13, BIT2
#define PAD_GPIO19_OUT_REG 0x102b13
#define PAD_GPIO19_OUT_MASK BIT0

#define GPIO68_PAD PAD_GPIO20
#define GPIO68_OEN 0x102b14, BIT1
#define GPIO68_OUT 0x102b14, BIT0
#define GPIO68_IN  0x102b14, BIT2
#define PAD_GPIO20_OUT_REG 0x102b14
#define PAD_GPIO20_OUT_MASK BIT0

#define GPIO69_PAD PAD_GPIO21
#define GPIO69_OEN 0x102b15, BIT1
#define GPIO69_OUT 0x102b15, BIT0
#define GPIO69_IN  0x102b15, BIT2
#define PAD_GPIO21_OUT_REG 0x102b15
#define PAD_GPIO21_OUT_MASK BIT0

#define GPIO70_PAD PAD_GPIO22
#define GPIO70_OEN 0x102b16, BIT1
#define GPIO70_OUT 0x102b16, BIT0
#define GPIO70_IN  0x102b16, BIT2
#define PAD_GPIO22_OUT_REG 0x102b16
#define PAD_GPIO22_OUT_MASK BIT0

#define GPIO71_PAD PAD_GPIO23
#define GPIO71_OEN 0x102b17, BIT1
#define GPIO71_OUT 0x102b17, BIT0
#define GPIO71_IN  0x102b17, BIT2
#define PAD_GPIO23_OUT_REG 0x102b17
#define PAD_GPIO23_OUT_MASK BIT0

#define GPIO72_PAD PAD_GPIO24
#define GPIO72_OEN 0x102b18, BIT1
#define GPIO72_OUT 0x102b18, BIT0
#define GPIO72_IN  0x102b18, BIT2
#define PAD_GPIO24_OUT_REG 0x102b18
#define PAD_GPIO24_OUT_MASK BIT0

#define GPIO73_PAD PAD_GPIO25
#define GPIO73_OEN 0x102b19, BIT1
#define GPIO73_OUT 0x102b19, BIT0
#define GPIO73_IN  0x102b19, BIT2
#define PAD_GPIO25_OUT_REG 0x102b19
#define PAD_GPIO25_OUT_MASK BIT0

#define GPIO74_PAD PAD_GPIO26
#define GPIO74_OEN 0x102b1a, BIT1
#define GPIO74_OUT 0x102b1a, BIT0
#define GPIO74_IN  0x102b1a, BIT2
#define PAD_GPIO26_OUT_REG 0x102b1a
#define PAD_GPIO26_OUT_MASK BIT0

#define GPIO75_PAD PAD_GPIO27
#define GPIO75_OEN 0x102b1b, BIT1
#define GPIO75_OUT 0x102b1b, BIT0
#define GPIO75_IN  0x102b1b, BIT2
#define PAD_GPIO27_OUT_REG 0x102b1b
#define PAD_GPIO27_OUT_MASK BIT0

#define GPIO76_PAD PAD_I2S_IN_WS
#define GPIO76_OEN 0x102b36, BIT1
#define GPIO76_OUT 0x102b36, BIT0
#define GPIO76_IN  0x102b36, BIT2
#define PAD_I2S_IN_WS_OUT_REG 0x102b36
#define PAD_I2S_IN_WS_OUT_MASK BIT0

#define GPIO77_PAD PAD_I2S_IN_BCK
#define GPIO77_OEN 0x102b37, BIT1
#define GPIO77_OUT 0x102b37, BIT0
#define GPIO77_IN  0x102b37, BIT2
#define PAD_I2S_IN_BCK_OUT_REG 0x102b37
#define PAD_I2S_IN_BCK_OUT_MASK BIT0

#define GPIO78_PAD PAD_I2S_IN_SD
#define GPIO78_OEN 0x102b38, BIT1
#define GPIO78_OUT 0x102b38, BIT0
#define GPIO78_IN  0x102b38, BIT2
#define PAD_I2S_IN_SD_OUT_REG 0x102b38
#define PAD_I2S_IN_SD_OUT_MASK BIT0

#define GPIO79_PAD PAD_SPDIF_IN
#define GPIO79_OEN 0x102b39, BIT1
#define GPIO79_OUT 0x102b39, BIT0
#define GPIO79_IN  0x102b39, BIT2
#define PAD_SPDIF_IN_OUT_REG 0x102b39
#define PAD_SPDIF_IN_OUT_MASK BIT0

#define GPIO80_PAD PAD_SPDIF_OUT
#define GPIO80_OEN 0x102b3a, BIT1
#define GPIO80_OUT 0x102b3a, BIT0
#define GPIO80_IN  0x102b3a, BIT2
#define PAD_SPDIF_OUT_OUT_REG 0x102b3a
#define PAD_SPDIF_OUT_OUT_MASK BIT0

#define GPIO81_PAD PAD_I2S_OUT_WS
#define GPIO81_OEN 0x102b3b, BIT1
#define GPIO81_OUT 0x102b3b, BIT0
#define GPIO81_IN  0x102b3b, BIT2
#define PAD_I2S_OUT_WS_OUT_REG 0x102b3b
#define PAD_I2S_OUT_WS_OUT_MASK BIT0

#define GPIO82_PAD PAD_I2S_OUT_MCK
#define GPIO82_OEN 0x102b3c, BIT1
#define GPIO82_OUT 0x102b3c, BIT0
#define GPIO82_IN  0x102b3c, BIT2
#define PAD_I2S_OUT_MCK_OUT_REG 0x102b3c
#define PAD_I2S_OUT_MCK_OUT_MASK BIT0

#define GPIO83_PAD PAD_I2S_OUT_BCK
#define GPIO83_OEN 0x102b3d, BIT1
#define GPIO83_OUT 0x102b3d, BIT0
#define GPIO83_IN  0x102b3d, BIT2
#define PAD_I2S_OUT_BCK_OUT_REG 0x102b3d
#define PAD_I2S_OUT_BCK_OUT_MASK BIT0

#define GPIO84_PAD PAD_I2S_OUT_SD
#define GPIO84_OEN 0x102b3e, BIT1
#define GPIO84_OUT 0x102b3e, BIT0
#define GPIO84_IN  0x102b3e, BIT2
#define PAD_I2S_OUT_SD_OUT_REG 0x102b3e
#define PAD_I2S_OUT_SD_OUT_MASK BIT0

#define GPIO85_PAD PAD_I2S_OUT_SD1
#define GPIO85_OEN 0x102b3f, BIT1
#define GPIO85_OUT 0x102b3f, BIT0
#define GPIO85_IN  0x102b3f, BIT2
#define PAD_I2S_OUT_SD1_OUT_REG 0x102b3f
#define PAD_I2S_OUT_SD1_OUT_MASK BIT0

#define GPIO86_PAD PAD_I2S_OUT_SD2
#define GPIO86_OEN 0x102b40, BIT1
#define GPIO86_OUT 0x102b40, BIT0
#define GPIO86_IN  0x102b40, BIT2
#define PAD_I2S_OUT_SD2_OUT_REG 0x102b40
#define PAD_I2S_OUT_SD2_OUT_MASK BIT0

#define GPIO87_PAD PAD_I2S_OUT_SD3
#define GPIO87_OEN 0x102b41, BIT1
#define GPIO87_OUT 0x102b41, BIT0
#define GPIO87_IN  0x102b41, BIT2
#define PAD_I2S_OUT_SD3_OUT_REG 0x102b41
#define PAD_I2S_OUT_SD3_OUT_MASK BIT0

#define GPIO88_PAD PAD_VSYNC_Like
#define GPIO88_OEN 0x102bb0, BIT1
#define GPIO88_OUT 0x102bb0, BIT0
#define GPIO88_IN  0x102bb0, BIT2
#define PAD_VSYNC_Like_OUT_REG 0x102bb0
#define PAD_VSYNC_Like_OUT_MASK BIT0

#define GPIO89_PAD PAD_SPI1_CK
#define GPIO89_OEN 0x102bb1, BIT1
#define GPIO89_OUT 0x102bb1, BIT0
#define GPIO89_IN  0x102bb1, BIT2
#define PAD_SPI1_CK_OUT_REG 0x102bb1
#define PAD_SPI1_CK_OUT_MASK BIT0

#define GPIO90_PAD PAD_SPI1_DI
#define GPIO90_OEN 0x102bb2, BIT1
#define GPIO90_OUT 0x102bb2, BIT0
#define GPIO90_IN  0x102bb2, BIT2
#define PAD_SPI1_DI_OUT_REG 0x102bb2
#define PAD_SPI1_DI_OUT_MASK BIT0

#define GPIO91_PAD PAD_SPI2_CK
#define GPIO91_OEN 0x102bb3, BIT1
#define GPIO91_OUT 0x102bb3, BIT0
#define GPIO91_IN  0x102bb3, BIT2
#define PAD_SPI2_CK_OUT_REG 0x102bb3
#define PAD_SPI2_CK_OUT_MASK BIT0

#define GPIO92_PAD PAD_SPI2_DI
#define GPIO92_OEN 0x102bb4, BIT1
#define GPIO92_OUT 0x102bb4, BIT0
#define GPIO92_IN  0x102bb4, BIT2
#define PAD_SPI2_DI_OUT_REG 0x102bb4
#define PAD_SPI2_DI_OUT_MASK BIT0

#define GPIO93_PAD PAD_NAND_CEZ
#define GPIO93_OEN 0x102b78, BIT1
#define GPIO93_OUT 0x102b78, BIT0
#define GPIO93_IN  0x102b78, BIT2
#define PAD_NAND_CEZ_OUT_REG 0x102b78
#define PAD_NAND_CEZ_OUT_MASK BIT0

#define GPIO94_PAD PAD_NAND_CEZ1
#define GPIO94_OEN 0x102b79, BIT1
#define GPIO94_OUT 0x102b79, BIT0
#define GPIO94_IN  0x102b79, BIT2
#define PAD_NAND_CEZ1_OUT_REG 0x102b79
#define PAD_NAND_CEZ1_OUT_MASK BIT0

#define GPIO95_PAD PAD_NAND_CLE
#define GPIO95_OEN 0x102b7a, BIT1
#define GPIO95_OUT 0x102b7a, BIT0
#define GPIO95_IN  0x102b7a, BIT2
#define PAD_NAND_CLE_OUT_REG 0x102b7a
#define PAD_NAND_CLE_OUT_MASK BIT0

#define GPIO96_PAD PAD_NAND_REZ
#define GPIO96_OEN 0x102b7b, BIT1
#define GPIO96_OUT 0x102b7b, BIT0
#define GPIO96_IN  0x102b7b, BIT2
#define PAD_NAND_REZ_OUT_REG 0x102b7b
#define PAD_NAND_REZ_OUT_MASK BIT0

#define GPIO97_PAD PAD_NAND_WEZ
#define GPIO97_OEN 0x102b7c, BIT1
#define GPIO97_OUT 0x102b7c, BIT0
#define GPIO97_IN  0x102b7c, BIT2
#define PAD_NAND_WEZ_OUT_REG 0x102b7c
#define PAD_NAND_WEZ_OUT_MASK BIT0

#define GPIO98_PAD PAD_NAND_WPZ
#define GPIO98_OEN 0x102b7d, BIT1
#define GPIO98_OUT 0x102b7d, BIT0
#define GPIO98_IN  0x102b7d, BIT2
#define PAD_NAND_WPZ_OUT_REG 0x102b7d
#define PAD_NAND_WPZ_OUT_MASK BIT0

#define GPIO99_PAD PAD_NAND_ALE
#define GPIO99_OEN 0x102b7e, BIT1
#define GPIO99_OUT 0x102b7e, BIT0
#define GPIO99_IN  0x102b7e, BIT2
#define PAD_NAND_ALE_OUT_REG 0x102b7e
#define PAD_NAND_ALE_OUT_MASK BIT0

#define GPIO100_PAD PAD_NAND_RBZ
#define GPIO100_OEN 0x102b7f, BIT1
#define GPIO100_OUT 0x102b7f, BIT0
#define GPIO100_IN  0x102b7f, BIT2
#define PAD_NAND_RBZ_OUT_REG 0x102b7f
#define PAD_NAND_RBZ_OUT_MASK BIT0

#define GPIO101_PAD PAD_PCM2_CE_N
#define GPIO101_OEN 0x102b63, BIT1
#define GPIO101_OUT 0x102b63, BIT0
#define GPIO101_IN  0x102b63, BIT2
#define PAD_PCM2_CE_N_OUT_REG 0x102b63
#define PAD_PCM2_CE_N_OUT_MASK BIT0

#define GPIO102_PAD PAD_PCM2_IRQA_N
#define GPIO102_OEN 0x102b64, BIT1
#define GPIO102_OUT 0x102b64, BIT0
#define GPIO102_IN  0x102b64, BIT2
#define PAD_PCM2_IRQA_N_OUT_REG 0x102b64
#define PAD_PCM2_IRQA_N_OUT_MASK BIT0

#define GPIO103_PAD PAD_PCM2_WAIT_N
#define GPIO103_OEN 0x102b65, BIT1
#define GPIO103_OUT 0x102b65, BIT0
#define GPIO103_IN  0x102b65, BIT2
#define PAD_PCM2_WAIT_N_OUT_REG 0x102b65
#define PAD_PCM2_WAIT_N_OUT_MASK BIT0

#define GPIO104_PAD PAD_PCM2_RESET
#define GPIO104_OEN 0x102b66, BIT1
#define GPIO104_OUT 0x102b66, BIT0
#define GPIO104_IN  0x102b66, BIT2
#define PAD_PCM2_RESET_OUT_REG 0x102b66
#define PAD_PCM2_RESET_OUT_MASK BIT0

#define GPIO105_PAD PAD_PCM2_CD_N
#define GPIO105_OEN 0x102b67, BIT1
#define GPIO105_OUT 0x102b67, BIT0
#define GPIO105_IN  0x102b67, BIT2
#define PAD_PCM2_CD_N_OUT_REG 0x102b67
#define PAD_PCM2_CD_N_OUT_MASK BIT0

#define GPIO106_PAD PAD_PCM_D3
#define GPIO106_OEN 0x102b42, BIT1
#define GPIO106_OUT 0x102b42, BIT0
#define GPIO106_IN  0x102b42, BIT2
#define PAD_PCM_D3_OUT_REG 0x102b42
#define PAD_PCM_D3_OUT_MASK BIT0

#define GPIO107_PAD PAD_PCM_D4
#define GPIO107_OEN 0x102b43, BIT1
#define GPIO107_OUT 0x102b43, BIT0
#define GPIO107_IN  0x102b43, BIT2
#define PAD_PCM_D4_OUT_REG 0x102b43
#define PAD_PCM_D4_OUT_MASK BIT0

#define GPIO108_PAD PAD_PCM_D5
#define GPIO108_OEN 0x102b44, BIT1
#define GPIO108_OUT 0x102b44, BIT0
#define GPIO108_IN  0x102b44, BIT2
#define PAD_PCM_D5_OUT_REG 0x102b44
#define PAD_PCM_D5_OUT_MASK BIT0

#define GPIO109_PAD PAD_PCM_D6
#define GPIO109_OEN 0x102b45, BIT1
#define GPIO109_OUT 0x102b45, BIT0
#define GPIO109_IN  0x102b45, BIT2
#define PAD_PCM_D6_OUT_REG 0x102b45
#define PAD_PCM_D6_OUT_MASK BIT0

#define GPIO110_PAD PAD_PCM_D7
#define GPIO110_OEN 0x102b46, BIT1
#define GPIO110_OUT 0x102b46, BIT0
#define GPIO110_IN  0x102b46, BIT2
#define PAD_PCM_D7_OUT_REG 0x102b46
#define PAD_PCM_D7_OUT_MASK BIT0

#define GPIO111_PAD PAD_PCM_CE_N
#define GPIO111_OEN 0x102b47, BIT1
#define GPIO111_OUT 0x102b47, BIT0
#define GPIO111_IN  0x102b47, BIT2
#define PAD_PCM_CE_N_OUT_REG 0x102b47
#define PAD_PCM_CE_N_OUT_MASK BIT0

#define GPIO112_PAD PAD_PCM_A10
#define GPIO112_OEN 0x102b48, BIT1
#define GPIO112_OUT 0x102b48, BIT0
#define GPIO112_IN  0x102b48, BIT2
#define PAD_PCM_A10_OUT_REG 0x102b48
#define PAD_PCM_A10_OUT_MASK BIT0

#define GPIO113_PAD PAD_PCM_OE_N
#define GPIO113_OEN 0x102b49, BIT1
#define GPIO113_OUT 0x102b49, BIT0
#define GPIO113_IN  0x102b49, BIT2
#define PAD_PCM_OE_N_OUT_REG 0x102b49
#define PAD_PCM_OE_N_OUT_MASK BIT0

#define GPIO114_PAD PAD_PCM_A11
#define GPIO114_OEN 0x102b4a, BIT1
#define GPIO114_OUT 0x102b4a, BIT0
#define GPIO114_IN  0x102b4a, BIT2
#define PAD_PCM_A11_OUT_REG 0x102b4a
#define PAD_PCM_A11_OUT_MASK BIT0

#define GPIO115_PAD PAD_PCM_IORD_N
#define GPIO115_OEN 0x102b4b, BIT1
#define GPIO115_OUT 0x102b4b, BIT0
#define GPIO115_IN  0x102b4b, BIT2
#define PAD_PCM_IORD_N_OUT_REG 0x102b4b
#define PAD_PCM_IORD_N_OUT_MASK BIT0

#define GPIO116_PAD PAD_PCM_A9
#define GPIO116_OEN 0x102b4c, BIT1
#define GPIO116_OUT 0x102b4c, BIT0
#define GPIO116_IN  0x102b4c, BIT2
#define PAD_PCM_A9_OUT_REG 0x102b4c
#define PAD_PCM_A9_OUT_MASK BIT0

#define GPIO117_PAD PAD_PCM_IOWR_N
#define GPIO117_OEN 0x102b4d, BIT1
#define GPIO117_OUT 0x102b4d, BIT0
#define GPIO117_IN  0x102b4d, BIT2
#define PAD_PCM_IOWR_N_OUT_REG 0x102b4d
#define PAD_PCM_IOWR_N_OUT_MASK BIT0

#define GPIO118_PAD PAD_PCM_A8
#define GPIO118_OEN 0x102b4e, BIT1
#define GPIO118_OUT 0x102b4e, BIT0
#define GPIO118_IN  0x102b4e, BIT2
#define PAD_PCM_A8_OUT_REG 0x102b4e
#define PAD_PCM_A8_OUT_MASK BIT0

#define GPIO119_PAD PAD_PCM_A13
#define GPIO119_OEN 0x102b4f, BIT1
#define GPIO119_OUT 0x102b4f, BIT0
#define GPIO119_IN  0x102b4f, BIT2
#define PAD_PCM_A13_OUT_REG 0x102b4f
#define PAD_PCM_A13_OUT_MASK BIT0

#define GPIO120_PAD PAD_PCM_A14
#define GPIO120_OEN 0x102b50, BIT1
#define GPIO120_OUT 0x102b50, BIT0
#define GPIO120_IN  0x102b50, BIT2
#define PAD_PCM_A14_OUT_REG 0x102b50
#define PAD_PCM_A14_OUT_MASK BIT0

#define GPIO121_PAD PAD_PCM_WE_N
#define GPIO121_OEN 0x102b51, BIT1
#define GPIO121_OUT 0x102b51, BIT0
#define GPIO121_IN  0x102b51, BIT2
#define PAD_PCM_WE_N_OUT_REG 0x102b51
#define PAD_PCM_WE_N_OUT_MASK BIT0

#define GPIO122_PAD PAD_PCM_IRQA_N
#define GPIO122_OEN 0x102b52, BIT1
#define GPIO122_OUT 0x102b52, BIT0
#define GPIO122_IN  0x102b52, BIT2
#define PAD_PCM_IRQA_N_OUT_REG 0x102b52
#define PAD_PCM_IRQA_N_OUT_MASK BIT0

#define GPIO123_PAD PAD_PCM_A12
#define GPIO123_OEN 0x102b53, BIT1
#define GPIO123_OUT 0x102b53, BIT0
#define GPIO123_IN  0x102b53, BIT2
#define PAD_PCM_A12_OUT_REG 0x102b53
#define PAD_PCM_A12_OUT_MASK BIT0

#define GPIO124_PAD PAD_PCM_A7
#define GPIO124_OEN 0x102b54, BIT1
#define GPIO124_OUT 0x102b54, BIT0
#define GPIO124_IN  0x102b54, BIT2
#define PAD_PCM_A7_OUT_REG 0x102b54
#define PAD_PCM_A7_OUT_MASK BIT0

#define GPIO125_PAD PAD_PCM_A6
#define GPIO125_OEN 0x102b55, BIT1
#define GPIO125_OUT 0x102b55, BIT0
#define GPIO125_IN  0x102b55, BIT2
#define PAD_PCM_A6_OUT_REG 0x102b55
#define PAD_PCM_A6_OUT_MASK BIT0

#define GPIO126_PAD PAD_PCM_A5
#define GPIO126_OEN 0x102b56, BIT1
#define GPIO126_OUT 0x102b56, BIT0
#define GPIO126_IN  0x102b56, BIT2
#define PAD_PCM_A5_OUT_REG 0x102b56
#define PAD_PCM_A5_OUT_MASK BIT0

#define GPIO127_PAD PAD_PCM_WAIT_N
#define GPIO127_OEN 0x102b57, BIT1
#define GPIO127_OUT 0x102b57, BIT0
#define GPIO127_IN  0x102b57, BIT2
#define PAD_PCM_WAIT_N_OUT_REG 0x102b57
#define PAD_PCM_WAIT_N_OUT_MASK BIT0

#define GPIO128_PAD PAD_PCM_A4
#define GPIO128_OEN 0x102b58, BIT1
#define GPIO128_OUT 0x102b58, BIT0
#define GPIO128_IN  0x102b58, BIT2
#define PAD_PCM_A4_OUT_REG 0x102b58
#define PAD_PCM_A4_OUT_MASK BIT0

#define GPIO129_PAD PAD_PCM_A3
#define GPIO129_OEN 0x102b59, BIT1
#define GPIO129_OUT 0x102b59, BIT0
#define GPIO129_IN  0x102b59, BIT2
#define PAD_PCM_A3_OUT_REG 0x102b59
#define PAD_PCM_A3_OUT_MASK BIT0

#define GPIO130_PAD PAD_PCM_A2
#define GPIO130_OEN 0x102b5a, BIT1
#define GPIO130_OUT 0x102b5a, BIT0
#define GPIO130_IN  0x102b5a, BIT2
#define PAD_PCM_A2_OUT_REG 0x102b5a
#define PAD_PCM_A2_OUT_MASK BIT0

#define GPIO131_PAD PAD_PCM_REG_N
#define GPIO131_OEN 0x102b5b, BIT1
#define GPIO131_OUT 0x102b5b, BIT0
#define GPIO131_IN  0x102b5b, BIT2
#define PAD_PCM_REG_N_OUT_REG 0x102b5b
#define PAD_PCM_REG_N_OUT_MASK BIT0

#define GPIO132_PAD PAD_PCM_A1
#define GPIO132_OEN 0x102b5c, BIT1
#define GPIO132_OUT 0x102b5c, BIT0
#define GPIO132_IN  0x102b5c, BIT2
#define PAD_PCM_A1_OUT_REG 0x102b5c
#define PAD_PCM_A1_OUT_MASK BIT0

#define GPIO133_PAD PAD_PCM_A0
#define GPIO133_OEN 0x102b5d, BIT1
#define GPIO133_OUT 0x102b5d, BIT0
#define GPIO133_IN  0x102b5d, BIT2
#define PAD_PCM_A0_OUT_REG 0x102b5d
#define PAD_PCM_A0_OUT_MASK BIT0

#define GPIO134_PAD PAD_PCM_D0
#define GPIO134_OEN 0x102b5e, BIT1
#define GPIO134_OUT 0x102b5e, BIT0
#define GPIO134_IN  0x102b5e, BIT2
#define PAD_PCM_D0_OUT_REG 0x102b5e
#define PAD_PCM_D0_OUT_MASK BIT0

#define GPIO135_PAD PAD_PCM_D1
#define GPIO135_OEN 0x102b5f, BIT1
#define GPIO135_OUT 0x102b5f, BIT0
#define GPIO135_IN  0x102b5f, BIT2
#define PAD_PCM_D1_OUT_REG 0x102b5f
#define PAD_PCM_D1_OUT_MASK BIT0

#define GPIO136_PAD PAD_PCM_D2
#define GPIO136_OEN 0x102b60, BIT1
#define GPIO136_OUT 0x102b60, BIT0
#define GPIO136_IN  0x102b60, BIT2
#define PAD_PCM_D2_OUT_REG 0x102b60
#define PAD_PCM_D2_OUT_MASK BIT0

#define GPIO137_PAD PAD_PCM_RESET
#define GPIO137_OEN 0x102b61, BIT1
#define GPIO137_OUT 0x102b61, BIT0
#define GPIO137_IN  0x102b61, BIT2
#define PAD_PCM_RESET_OUT_REG 0x102b61
#define PAD_PCM_RESET_OUT_MASK BIT0

#define GPIO138_PAD PAD_PCM_CD_N
#define GPIO138_OEN 0x102b62, BIT1
#define GPIO138_OUT 0x102b62, BIT0
#define GPIO138_IN  0x102b62, BIT2
#define PAD_PCM_CD_N_OUT_REG 0x102b62
#define PAD_PCM_CD_N_OUT_MASK BIT0

#define GPIO139_PAD PAD_PWM0
#define GPIO139_OEN 0x102b88, BIT1
#define GPIO139_OUT 0x102b88, BIT0
#define GPIO139_IN  0x102b88, BIT2
#define PAD_PWM0_OUT_REG 0x102b88
#define PAD_PWM0_OUT_MASK BIT0

#define GPIO140_PAD PAD_PWM1
#define GPIO140_OEN 0x102b89, BIT1
#define GPIO140_OUT 0x102b89, BIT0
#define GPIO140_IN  0x102b89, BIT2
#define PAD_PWM1_OUT_REG 0x102b89
#define PAD_PWM1_OUT_MASK BIT0

#define GPIO141_PAD PAD_PWM2
#define GPIO141_OEN 0x102b8a, BIT1
#define GPIO141_OUT 0x102b8a, BIT0
#define GPIO141_IN  0x102b8a, BIT2
#define PAD_PWM2_OUT_REG 0x102b8a
#define PAD_PWM2_OUT_MASK BIT0

#define GPIO142_PAD PAD_PWM3
#define GPIO142_OEN 0x102b8b, BIT1
#define GPIO142_OUT 0x102b8b, BIT0
#define GPIO142_IN  0x102b8b, BIT2
#define PAD_PWM3_OUT_REG 0x102b8b
#define PAD_PWM3_OUT_MASK BIT0

#define GPIO143_PAD PAD_PWM4
#define GPIO143_OEN 0x102b8c, BIT1
#define GPIO143_OUT 0x102b8c, BIT0
#define GPIO143_IN  0x102b8c, BIT2
#define PAD_PWM4_OUT_REG 0x102b8c
#define PAD_PWM4_OUT_MASK BIT0

#define GPIO144_PAD PAD_EMMC_RSTN
#define GPIO144_OEN 0x102bac, BIT1
#define GPIO144_OUT 0x102bac, BIT0
#define GPIO144_IN  0x102bac, BIT2
#define PAD_EMMC_RSTN_OUT_REG 0x102bac
#define PAD_EMMC_RSTN_OUT_MASK BIT0

#define GPIO145_PAD PAD_EMMC_CLK
#define GPIO145_OEN 0x102bad, BIT1
#define GPIO145_OUT 0x102bad, BIT0
#define GPIO145_IN  0x102bad, BIT2
#define PAD_EMMC_CLK_OUT_REG 0x102bad
#define PAD_EMMC_CLK_OUT_MASK BIT0

#define GPIO146_PAD PAD_EMMC_CMD
#define GPIO146_OEN 0x102bae, BIT1
#define GPIO146_OUT 0x102bae, BIT0
#define GPIO146_IN  0x102bae, BIT2
#define PAD_EMMC_CMD_OUT_REG 0x102bae
#define PAD_EMMC_CMD_OUT_MASK BIT0

#define GPIO147_PAD PAD_TCON0
#define GPIO147_OEN 0x102b93, BIT1
#define GPIO147_OUT 0x102b93, BIT0
#define GPIO147_IN  0x102b93, BIT2
#define PAD_TCON0_OUT_REG 0x102b93
#define PAD_TCON0_OUT_MASK BIT0

#define GPIO148_PAD PAD_TCON1
#define GPIO148_OEN 0x102b92, BIT1
#define GPIO148_OUT 0x102b92, BIT0
#define GPIO148_IN  0x102b92, BIT2
#define PAD_TCON1_OUT_REG 0x102b92
#define PAD_TCON1_OUT_MASK BIT0

#define GPIO149_PAD PAD_TCON2
#define GPIO149_OEN 0x102b95, BIT1
#define GPIO149_OUT 0x102b95, BIT0
#define GPIO149_IN  0x102b95, BIT2
#define PAD_TCON2_OUT_REG 0x102b95
#define PAD_TCON2_OUT_MASK BIT0

#define GPIO150_PAD PAD_TCON3
#define GPIO150_OEN 0x102b94, BIT1
#define GPIO150_OUT 0x102b94, BIT0
#define GPIO150_IN  0x102b94, BIT2
#define PAD_TCON3_OUT_REG 0x102b94
#define PAD_TCON3_OUT_MASK BIT0

#define GPIO151_PAD PAD_TCON4
#define GPIO151_OEN 0x102b97, BIT1
#define GPIO151_OUT 0x102b97, BIT0
#define GPIO151_IN  0x102b97, BIT2
#define PAD_TCON4_OUT_REG 0x102b97
#define PAD_TCON4_OUT_MASK BIT0

#define GPIO152_PAD PAD_TCON5
#define GPIO152_OEN 0x102b96, BIT1
#define GPIO152_OUT 0x102b96, BIT0
#define GPIO152_IN  0x102b96, BIT2
#define PAD_TCON5_OUT_REG 0x102b96
#define PAD_TCON5_OUT_MASK BIT0

#define GPIO153_PAD PAD_TCON6
#define GPIO153_OEN 0x102b99, BIT1
#define GPIO153_OUT 0x102b99, BIT0
#define GPIO153_IN  0x102b99, BIT2
#define PAD_TCON6_OUT_REG 0x102b99
#define PAD_TCON6_OUT_MASK BIT0

#define GPIO154_PAD PAD_TCON7
#define GPIO154_OEN 0x102b98, BIT1
#define GPIO154_OUT 0x102b98, BIT0
#define GPIO154_IN  0x102b98, BIT2
#define PAD_TCON7_OUT_REG 0x102b98
#define PAD_TCON7_OUT_MASK BIT0

#define GPIO155_PAD PAD_TCON8
#define GPIO155_OEN 0x102b9b, BIT1
#define GPIO155_OUT 0x102b9b, BIT0
#define GPIO155_IN  0x102b9b, BIT2
#define PAD_TCON8_OUT_REG 0x102b9b
#define PAD_TCON8_OUT_MASK BIT0

#define GPIO156_PAD PAD_TCON9
#define GPIO156_OEN 0x102b9a, BIT1
#define GPIO156_OUT 0x102b9a, BIT0
#define GPIO156_IN  0x102b9a, BIT2
#define PAD_TCON9_OUT_REG 0x102b9a
#define PAD_TCON9_OUT_MASK BIT0

#define GPIO157_PAD PAD_TCON10
#define GPIO157_OEN 0x102b9d, BIT1
#define GPIO157_OUT 0x102b9d, BIT0
#define GPIO157_IN  0x102b9d, BIT2
#define PAD_TCON10_OUT_REG 0x102b9d
#define PAD_TCON10_OUT_MASK BIT0

#define GPIO158_PAD PAD_TCON11
#define GPIO158_OEN 0x102b9c, BIT1
#define GPIO158_OUT 0x102b9c, BIT0
#define GPIO158_IN  0x102b9c, BIT2
#define PAD_TCON11_OUT_REG 0x102b9c
#define PAD_TCON11_OUT_MASK BIT0

#define GPIO159_PAD PAD_TCON12
#define GPIO159_OEN 0x102b9f, BIT1
#define GPIO159_OUT 0x102b9f, BIT0
#define GPIO159_IN  0x102b9f, BIT2
#define PAD_TCON12_OUT_REG 0x102b9f
#define PAD_TCON12_OUT_MASK BIT0

#define GPIO160_PAD PAD_TCON13
#define GPIO160_OEN 0x102b9e, BIT1
#define GPIO160_OUT 0x102b9e, BIT0
#define GPIO160_IN  0x102b9e, BIT2
#define PAD_TCON13_OUT_REG 0x102b9e
#define PAD_TCON13_OUT_MASK BIT0

#define GPIO161_PAD PAD_TGPIO0
#define GPIO161_OEN 0x102b8d, BIT1
#define GPIO161_OUT 0x102b8d, BIT0
#define GPIO161_IN  0x102b8d, BIT2
#define PAD_TGPIO0_OUT_REG 0x102b8d
#define PAD_TGPIO0_OUT_MASK BIT0

#define GPIO162_PAD PAD_TGPIO1
#define GPIO162_OEN 0x102b8e, BIT1
#define GPIO162_OUT 0x102b8e, BIT0
#define GPIO162_IN  0x102b8e, BIT2
#define PAD_TGPIO1_OUT_REG 0x102b8e
#define PAD_TGPIO1_OUT_MASK BIT0

#define GPIO163_PAD PAD_TGPIO2
#define GPIO163_OEN 0x102b8f, BIT1
#define GPIO163_OUT 0x102b8f, BIT0
#define GPIO163_IN  0x102b8f, BIT2
#define PAD_TGPIO2_OUT_REG 0x102b8f
#define PAD_TGPIO2_OUT_MASK BIT0

#define GPIO164_PAD PAD_TGPIO3
#define GPIO164_OEN 0x102b90, BIT1
#define GPIO164_OUT 0x102b90, BIT0
#define GPIO164_IN  0x102b90, BIT2
#define PAD_TGPIO3_OUT_REG 0x102b90
#define PAD_TGPIO3_OUT_MASK BIT0

#define GPIO165_PAD PAD_TS0_D0
#define GPIO165_OEN 0x102b1c, BIT1
#define GPIO165_OUT 0x102b1c, BIT0
#define GPIO165_IN  0x102b1c, BIT2
#define PAD_TS0_D0_OUT_REG 0x102b1c
#define PAD_TS0_D0_OUT_MASK BIT0

#define GPIO166_PAD PAD_TS0_D1
#define GPIO166_OEN 0x102b1d, BIT1
#define GPIO166_OUT 0x102b1d, BIT0
#define GPIO166_IN  0x102b1d, BIT2
#define PAD_TS0_D1_OUT_REG 0x102b1d
#define PAD_TS0_D1_OUT_MASK BIT0

#define GPIO167_PAD PAD_TS0_D2
#define GPIO167_OEN 0x102b1e, BIT1
#define GPIO167_OUT 0x102b1e, BIT0
#define GPIO167_IN  0x102b1e, BIT2
#define PAD_TS0_D2_OUT_REG 0x102b1e
#define PAD_TS0_D2_OUT_MASK BIT0

#define GPIO168_PAD PAD_TS0_D3
#define GPIO168_OEN 0x102b1f, BIT1
#define GPIO168_OUT 0x102b1f, BIT0
#define GPIO168_IN  0x102b1f, BIT2
#define PAD_TS0_D3_OUT_REG 0x102b1f
#define PAD_TS0_D3_OUT_MASK BIT0

#define GPIO169_PAD PAD_TS0_D4
#define GPIO169_OEN 0x102b20, BIT1
#define GPIO169_OUT 0x102b20, BIT0
#define GPIO169_IN  0x102b20, BIT2
#define PAD_TS0_D4_OUT_REG 0x102b20
#define PAD_TS0_D4_OUT_MASK BIT0

#define GPIO170_PAD PAD_TS0_D5
#define GPIO170_OEN 0x102b21, BIT1
#define GPIO170_OUT 0x102b21, BIT0
#define GPIO170_IN  0x102b21, BIT2
#define PAD_TS0_D5_OUT_REG 0x102b21
#define PAD_TS0_D5_OUT_MASK BIT0

#define GPIO171_PAD PAD_TS0_D6
#define GPIO171_OEN 0x102b22, BIT1
#define GPIO171_OUT 0x102b22, BIT0
#define GPIO171_IN  0x102b22, BIT2
#define PAD_TS0_D6_OUT_REG 0x102b22
#define PAD_TS0_D6_OUT_MASK BIT0

#define GPIO172_PAD PAD_TS0_D7
#define GPIO172_OEN 0x102b23, BIT1
#define GPIO172_OUT 0x102b23, BIT0
#define GPIO172_IN  0x102b23, BIT2
#define PAD_TS0_D7_OUT_REG 0x102b23
#define PAD_TS0_D7_OUT_MASK BIT0

#define GPIO173_PAD PAD_TS0_VLD
#define GPIO173_OEN 0x102b24, BIT1
#define GPIO173_OUT 0x102b24, BIT0
#define GPIO173_IN  0x102b24, BIT2
#define PAD_TS0_VLD_OUT_REG 0x102b24
#define PAD_TS0_VLD_OUT_MASK BIT0

#define GPIO174_PAD PAD_TS0_SYNC
#define GPIO174_OEN 0x102b25, BIT1
#define GPIO174_OUT 0x102b25, BIT0
#define GPIO174_IN  0x102b25, BIT2
#define PAD_TS0_SYNC_OUT_REG 0x102b25
#define PAD_TS0_SYNC_OUT_MASK BIT0

#define GPIO175_PAD PAD_TS0_CLK
#define GPIO175_OEN 0x102b26, BIT1
#define GPIO175_OUT 0x102b26, BIT0
#define GPIO175_IN  0x102b26, BIT2
#define PAD_TS0_CLK_OUT_REG 0x102b26
#define PAD_TS0_CLK_OUT_MASK BIT0

#define GPIO176_PAD PAD_TS1_CLK
#define GPIO176_OEN 0x102b27, BIT1
#define GPIO176_OUT 0x102b27, BIT0
#define GPIO176_IN  0x102b27, BIT2
#define PAD_TS1_CLK_OUT_REG 0x102b27
#define PAD_TS1_CLK_OUT_MASK BIT0

#define GPIO177_PAD PAD_TS1_SYNC
#define GPIO177_OEN 0x102b28, BIT1
#define GPIO177_OUT 0x102b28, BIT0
#define GPIO177_IN  0x102b28, BIT2
#define PAD_TS1_SYNC_OUT_REG 0x102b28
#define PAD_TS1_SYNC_OUT_MASK BIT0

#define GPIO178_PAD PAD_TS1_VLD
#define GPIO178_OEN 0x102b29, BIT1
#define GPIO178_OUT 0x102b29, BIT0
#define GPIO178_IN  0x102b29, BIT2
#define PAD_TS1_VLD_OUT_REG 0x102b29
#define PAD_TS1_VLD_OUT_MASK BIT0

#define GPIO179_PAD PAD_TS1_D7
#define GPIO179_OEN 0x102b2a, BIT1
#define GPIO179_OUT 0x102b2a, BIT0
#define GPIO179_IN  0x102b2a, BIT2
#define PAD_TS1_D7_OUT_REG 0x102b2a
#define PAD_TS1_D7_OUT_MASK BIT0

#define GPIO180_PAD PAD_TS1_D6
#define GPIO180_OEN 0x102b2b, BIT1
#define GPIO180_OUT 0x102b2b, BIT0
#define GPIO180_IN  0x102b2b, BIT2
#define PAD_TS1_D6_OUT_REG 0x102b2b
#define PAD_TS1_D6_OUT_MASK BIT0

#define GPIO181_PAD PAD_TS1_D5
#define GPIO181_OEN 0x102b2c, BIT1
#define GPIO181_OUT 0x102b2c, BIT0
#define GPIO181_IN  0x102b2c, BIT2
#define PAD_TS1_D5_OUT_REG 0x102b2c
#define PAD_TS1_D5_OUT_MASK BIT0

#define GPIO182_PAD PAD_TS1_D4
#define GPIO182_OEN 0x102b2d, BIT1
#define GPIO182_OUT 0x102b2d, BIT0
#define GPIO182_IN  0x102b2d, BIT2
#define PAD_TS1_D4_OUT_REG 0x102b2d
#define PAD_TS1_D4_OUT_MASK BIT0

#define GPIO183_PAD PAD_TS1_D3
#define GPIO183_OEN 0x102b2e, BIT1
#define GPIO183_OUT 0x102b2e, BIT0
#define GPIO183_IN  0x102b2e, BIT2
#define PAD_TS1_D3_OUT_REG 0x102b2e
#define PAD_TS1_D3_OUT_MASK BIT0

#define GPIO184_PAD PAD_TS1_D2
#define GPIO184_OEN 0x102b2f, BIT1
#define GPIO184_OUT 0x102b2f, BIT0
#define GPIO184_IN  0x102b2f, BIT2
#define PAD_TS1_D2_OUT_REG 0x102b2f
#define PAD_TS1_D2_OUT_MASK BIT0

#define GPIO185_PAD PAD_TS1_D1
#define GPIO185_OEN 0x102b30, BIT1
#define GPIO185_OUT 0x102b30, BIT0
#define GPIO185_IN  0x102b30, BIT2
#define PAD_TS1_D1_OUT_REG 0x102b30
#define PAD_TS1_D1_OUT_MASK BIT0

#define GPIO186_PAD PAD_TS1_D0
#define GPIO186_OEN 0x102b31, BIT1
#define GPIO186_OUT 0x102b31, BIT0
#define GPIO186_IN  0x102b31, BIT2
#define PAD_TS1_D0_OUT_REG 0x102b31
#define PAD_TS1_D0_OUT_MASK BIT0

#define GPIO187_PAD PAD_TS2_D0
#define GPIO187_OEN 0x102b32, BIT1
#define GPIO187_OUT 0x102b32, BIT0
#define GPIO187_IN  0x102b32, BIT2
#define PAD_TS2_D0_OUT_REG 0x102b32
#define PAD_TS2_D0_OUT_MASK BIT0

#define GPIO188_PAD PAD_TS2_VLD
#define GPIO188_OEN 0x102b33, BIT1
#define GPIO188_OUT 0x102b33, BIT0
#define GPIO188_IN  0x102b33, BIT2
#define PAD_TS2_VLD_OUT_REG 0x102b33
#define PAD_TS2_VLD_OUT_MASK BIT0

#define GPIO189_PAD PAD_TS2_SYNC
#define GPIO189_OEN 0x102b34, BIT1
#define GPIO189_OUT 0x102b34, BIT0
#define GPIO189_IN  0x102b34, BIT2
#define PAD_TS2_SYNC_OUT_REG 0x102b34
#define PAD_TS2_SYNC_OUT_MASK BIT0

#define GPIO190_PAD PAD_TS2_CLK
#define GPIO190_OEN 0x102b35, BIT1
#define GPIO190_OUT 0x102b35, BIT0
#define GPIO190_IN  0x102b35, BIT2
#define PAD_TS2_CLK_OUT_REG 0x102b35
#define PAD_TS2_CLK_OUT_MASK BIT0

