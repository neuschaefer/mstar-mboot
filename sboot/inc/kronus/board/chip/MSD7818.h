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
#ifndef _MSD7818_H_
#define _MSD7818_H_

#define PAD_NC 9999
#define PAD_GND 0

#define PAD_SPDIF_OUT 9999
#ifndef PAD_SPDIF_OUT_IS_GPIO
#define PAD_SPDIF_OUT_IS_GPIO 0
#endif

#define PAD_SM0_GPIO0 9999
#ifndef PAD_SM0_GPIO0_IS_GPIO
#define PAD_SM0_GPIO0_IS_GPIO 0
#endif

#define PAD_SM0_GPIO1 9999
#ifndef PAD_SM0_GPIO1_IS_GPIO
#define PAD_SM0_GPIO1_IS_GPIO 0
#endif

#define PAD_SM1_IO 9999
#ifndef PAD_SM1_IO_IS_GPIO
#define PAD_SM1_IO_IS_GPIO 0
#endif

#define PAD_SM0_CD 9999
#ifndef PAD_SM0_CD_IS_GPIO
#define PAD_SM0_CD_IS_GPIO 0
#endif

#define PAD_SM0_RST 9999
#ifndef PAD_SM0_RST_IS_GPIO
#define PAD_SM0_RST_IS_GPIO 0
#endif

#define PAD_SM0_VCC 9999
#ifndef PAD_SM0_VCC_IS_GPIO
#define PAD_SM0_VCC_IS_GPIO 0
#endif

#define PAD_SM0_IO 9999
#ifndef PAD_SM0_IO_IS_GPIO
#define PAD_SM0_IO_IS_GPIO 0
#endif

#define PAD_SM0_CLK 9999
#ifndef PAD_SM0_CLK_IS_GPIO
#define PAD_SM0_CLK_IS_GPIO 0
#endif

#define PAD_S_GPIO0 9999
#ifndef PAD_S_GPIO0_IS_GPIO
#define PAD_S_GPIO0_IS_GPIO 0
#endif

#define PAD_S_GPIO1 9999
#ifndef PAD_S_GPIO1_IS_GPIO
#define PAD_S_GPIO1_IS_GPIO 0
#endif

#define PAD_S_GPIO2 9999
#ifndef PAD_S_GPIO2_IS_GPIO
#define PAD_S_GPIO2_IS_GPIO 0
#endif

#define PAD_CI_A14 9999
#ifndef PAD_CI_A14_IS_GPIO
#define PAD_CI_A14_IS_GPIO 0
#endif

#define PAD_CI_A13 9999
#ifndef PAD_CI_A13_IS_GPIO
#define PAD_CI_A13_IS_GPIO 0
#endif

#define PAD_CI_A12 9999
#ifndef PAD_CI_A12_IS_GPIO
#define PAD_CI_A12_IS_GPIO 0
#endif

#define PAD_CI_A11 9999
#ifndef PAD_CI_A11_IS_GPIO
#define PAD_CI_A11_IS_GPIO 0
#endif

#define PAD_CI_A10 9999
#ifndef PAD_CI_A10_IS_GPIO
#define PAD_CI_A10_IS_GPIO 0
#endif

#define PAD_CI_A9 9999
#ifndef PAD_CI_A9_IS_GPIO
#define PAD_CI_A9_IS_GPIO 0
#endif

#define PAD_CI_A8 9999
#ifndef PAD_CI_A8_IS_GPIO
#define PAD_CI_A8_IS_GPIO 0
#endif

#define PAD_CI_A7 9999
#ifndef PAD_CI_A7_IS_GPIO
#define PAD_CI_A7_IS_GPIO 0
#endif

#define PAD_CI_A6 9999
#ifndef PAD_CI_A6_IS_GPIO
#define PAD_CI_A6_IS_GPIO 0
#endif

#define PAD_CI_A5 9999
#ifndef PAD_CI_A5_IS_GPIO
#define PAD_CI_A5_IS_GPIO 0
#endif

#define PAD_CI_A2 9999
#ifndef PAD_CI_A2_IS_GPIO
#define PAD_CI_A2_IS_GPIO 0
#endif

#define PAD_NF_CEZ 9999
#ifndef PAD_NF_CEZ_IS_GPIO
#define PAD_NF_CEZ_IS_GPIO 0
#endif

#define PAD_CI_A3 9999
#ifndef PAD_CI_A3_IS_GPIO
#define PAD_CI_A3_IS_GPIO 0
#endif

#define PAD_CI_A0 9999
#ifndef PAD_CI_A0_IS_GPIO
#define PAD_CI_A0_IS_GPIO 0
#endif

#define PAD_CI_A1 9999
#ifndef PAD_CI_A1_IS_GPIO
#define PAD_CI_A1_IS_GPIO 0
#endif

#define PAD_CI_A4 9999
#ifndef PAD_CI_A4_IS_GPIO
#define PAD_CI_A4_IS_GPIO 0
#endif

#define PAD_CI_D0 9999
#ifndef PAD_CI_D0_IS_GPIO
#define PAD_CI_D0_IS_GPIO 0
#endif

#define PAD_CI_D1 9999
#ifndef PAD_CI_D1_IS_GPIO
#define PAD_CI_D1_IS_GPIO 0
#endif

#define PAD_CI_D2 9999
#ifndef PAD_CI_D2_IS_GPIO
#define PAD_CI_D2_IS_GPIO 0
#endif

#define PAD_CI_D3 9999
#ifndef PAD_CI_D3_IS_GPIO
#define PAD_CI_D3_IS_GPIO 0
#endif

#define PAD_CI_D4 9999
#ifndef PAD_CI_D4_IS_GPIO
#define PAD_CI_D4_IS_GPIO 0
#endif

#define PAD_CI_D5 9999
#ifndef PAD_CI_D5_IS_GPIO
#define PAD_CI_D5_IS_GPIO 0
#endif

#define PAD_CI_D6 9999
#ifndef PAD_CI_D6_IS_GPIO
#define PAD_CI_D6_IS_GPIO 0
#endif

#define PAD_CI_D7 9999
#ifndef PAD_CI_D7_IS_GPIO
#define PAD_CI_D7_IS_GPIO 0
#endif

#define PAD_CI_IORDZ 9999
#ifndef PAD_CI_IORDZ_IS_GPIO
#define PAD_CI_IORDZ_IS_GPIO 0
#endif

#define PAD_CI_IOWRZ 9999
#ifndef PAD_CI_IOWRZ_IS_GPIO
#define PAD_CI_IOWRZ_IS_GPIO 0
#endif

#define PAD_CI_OEZ 9999
#ifndef PAD_CI_OEZ_IS_GPIO
#define PAD_CI_OEZ_IS_GPIO 0
#endif

#define PAD_CI_WEZ 9999
#ifndef PAD_CI_WEZ_IS_GPIO
#define PAD_CI_WEZ_IS_GPIO 0
#endif

#define PAD_CI_REGZ 9999
#ifndef PAD_CI_REGZ_IS_GPIO
#define PAD_CI_REGZ_IS_GPIO 0
#endif

#define PAD_CI_CEZ 9999
#ifndef PAD_CI_CEZ_IS_GPIO
#define PAD_CI_CEZ_IS_GPIO 0
#endif

#define PAD_CI_IRQAZ 9999
#ifndef PAD_CI_IRQAZ_IS_GPIO
#define PAD_CI_IRQAZ_IS_GPIO 0
#endif

#define PAD_CI_WAITZ 9999
#ifndef PAD_CI_WAITZ_IS_GPIO
#define PAD_CI_WAITZ_IS_GPIO 0
#endif

#define PAD_CI_RST 9999
#ifndef PAD_CI_RST_IS_GPIO
#define PAD_CI_RST_IS_GPIO 0
#endif

#define PAD_CI_CDZ 9999
#ifndef PAD_CI_CDZ_IS_GPIO
#define PAD_CI_CDZ_IS_GPIO 0
#endif

#define PIN_66 PAD_TS1_CLK
#define PAD_TS1_CLK 42
#define GPIO_PAD_42 GPIO41
#ifndef PIN_66_IS_GPIO
#define PIN_66_IS_GPIO 0
#endif
#ifndef PAD_TS1_CLK_IS_GPIO
#define PAD_TS1_CLK_IS_GPIO PIN_66_IS_GPIO
#endif

#define PIN_67 PAD_TS1_D7
#define PAD_TS1_D7 45
#define GPIO_PAD_45 GPIO44
#ifndef PIN_67_IS_GPIO
#define PIN_67_IS_GPIO 0
#endif
#ifndef PAD_TS1_D7_IS_GPIO
#define PAD_TS1_D7_IS_GPIO PIN_67_IS_GPIO
#endif

#define PIN_68 PAD_TS1_D6
#define PAD_TS1_D6 46
#define GPIO_PAD_46 GPIO45
#ifndef PIN_68_IS_GPIO
#define PIN_68_IS_GPIO 0
#endif
#ifndef PAD_TS1_D6_IS_GPIO
#define PAD_TS1_D6_IS_GPIO PIN_68_IS_GPIO
#endif

#define PIN_69 PAD_TS1_D5
#define PAD_TS1_D5 47
#define GPIO_PAD_47 GPIO46
#ifndef PIN_69_IS_GPIO
#define PIN_69_IS_GPIO 0
#endif
#ifndef PAD_TS1_D5_IS_GPIO
#define PAD_TS1_D5_IS_GPIO PIN_69_IS_GPIO
#endif

#define PAD_TS1_D4 9999
#ifndef PAD_TS1_D4_IS_GPIO
#define PAD_TS1_D4_IS_GPIO 0
#endif

#define PAD_TS1_D3 9999
#ifndef PAD_TS1_D3_IS_GPIO
#define PAD_TS1_D3_IS_GPIO 0
#endif

#define PAD_TS1_D2 9999
#ifndef PAD_TS1_D2_IS_GPIO
#define PAD_TS1_D2_IS_GPIO 0
#endif

#define PAD_TS1_D1 9999
#ifndef PAD_TS1_D1_IS_GPIO
#define PAD_TS1_D1_IS_GPIO 0
#endif

#define PIN_70 PAD_TS1_D0
#define PAD_TS1_D0 52
#define GPIO_PAD_52 GPIO51
#ifndef PIN_70_IS_GPIO
#define PIN_70_IS_GPIO 0
#endif
#ifndef PAD_TS1_D0_IS_GPIO
#define PAD_TS1_D0_IS_GPIO PIN_70_IS_GPIO
#endif

#define PIN_71 PAD_TS1_VLD
#define PAD_TS1_VLD 44
#define GPIO_PAD_44 GPIO43
#ifndef PIN_71_IS_GPIO
#define PIN_71_IS_GPIO 0
#endif
#ifndef PAD_TS1_VLD_IS_GPIO
#define PAD_TS1_VLD_IS_GPIO PIN_71_IS_GPIO
#endif

#define PIN_72 PAD_TS1_SYNC
#define PAD_TS1_SYNC 43
#define GPIO_PAD_43 GPIO42
#ifndef PIN_72_IS_GPIO
#define PIN_72_IS_GPIO 0
#endif
#ifndef PAD_TS1_SYNC_IS_GPIO
#define PAD_TS1_SYNC_IS_GPIO PIN_72_IS_GPIO
#endif

#define PAD_TS0_CLK 9999
#ifndef PAD_TS0_CLK_IS_GPIO
#define PAD_TS0_CLK_IS_GPIO 0
#endif

#define PAD_TS0_D7 9999
#ifndef PAD_TS0_D7_IS_GPIO
#define PAD_TS0_D7_IS_GPIO 0
#endif

#define PAD_TS0_D6 9999
#ifndef PAD_TS0_D6_IS_GPIO
#define PAD_TS0_D6_IS_GPIO 0
#endif

#define PAD_TS0_D5 9999
#ifndef PAD_TS0_D5_IS_GPIO
#define PAD_TS0_D5_IS_GPIO 0
#endif

#define PAD_TS0_D4 9999
#ifndef PAD_TS0_D4_IS_GPIO
#define PAD_TS0_D4_IS_GPIO 0
#endif

#define PAD_TS0_D3 9999
#ifndef PAD_TS0_D3_IS_GPIO
#define PAD_TS0_D3_IS_GPIO 0
#endif

#define PAD_TS0_D2 9999
#ifndef PAD_TS0_D2_IS_GPIO
#define PAD_TS0_D2_IS_GPIO 0
#endif

#define PAD_TS0_D1 9999
#ifndef PAD_TS0_D1_IS_GPIO
#define PAD_TS0_D1_IS_GPIO 0
#endif

#define PAD_TS0_D0 9999
#ifndef PAD_TS0_D0_IS_GPIO
#define PAD_TS0_D0_IS_GPIO 0
#endif

#define PAD_TS0_VLD 9999
#ifndef PAD_TS0_VLD_IS_GPIO
#define PAD_TS0_VLD_IS_GPIO 0
#endif

#define PAD_TS0_SYNC 9999
#ifndef PAD_TS0_SYNC_IS_GPIO
#define PAD_TS0_SYNC_IS_GPIO 0
#endif

#define PAD_S_GPIO3 9999
#ifndef PAD_S_GPIO3_IS_GPIO
#define PAD_S_GPIO3_IS_GPIO 0
#endif

#define PAD_S_GPIO4 9999
#ifndef PAD_S_GPIO4_IS_GPIO
#define PAD_S_GPIO4_IS_GPIO 0
#endif

#define PIN_75 PAD_I2CM0_SDA
#define PAD_I2CM0_SDA 29
#define GPIO_PAD_29 GPIO28
#ifndef PIN_75_IS_GPIO
#define PIN_75_IS_GPIO 0
#endif
#ifndef PAD_I2CM0_SDA_IS_GPIO
#define PAD_I2CM0_SDA_IS_GPIO PIN_75_IS_GPIO
#endif

#define PIN_76 PAD_I2CM0_SCL
#define PAD_I2CM0_SCL 30
#define GPIO_PAD_30 GPIO29
#ifndef PIN_76_IS_GPIO
#define PIN_76_IS_GPIO 0
#endif
#ifndef PAD_I2CM0_SCL_IS_GPIO
#define PAD_I2CM0_SCL_IS_GPIO PIN_76_IS_GPIO
#endif

#define PIN_86 PAD_AGC_DOWN
#define PAD_AGC_DOWN 88
#define GPIO_PAD_88 GPIO87
#ifndef PIN_86_IS_GPIO
#define PIN_86_IS_GPIO 0
#endif
#ifndef PAD_AGC_DOWN_IS_GPIO
#define PAD_AGC_DOWN_IS_GPIO PIN_86_IS_GPIO
#endif

#define PIN_87 PAD_AGC_UP
#define PAD_AGC_UP 87
#define GPIO_PAD_87 GPIO86
#ifndef PIN_87_IS_GPIO
#define PIN_87_IS_GPIO 0
#endif
#ifndef PAD_AGC_UP_IS_GPIO
#define PAD_AGC_UP_IS_GPIO PIN_87_IS_GPIO
#endif

#define PIN_88 PAD_SAR0
#define PAD_SAR0 17
#define GPIO_PAD_17 GPIO16
#ifndef PIN_88_IS_GPIO
#define PIN_88_IS_GPIO 0
#endif
#ifndef PAD_SAR0_IS_GPIO
#define PAD_SAR0_IS_GPIO PIN_88_IS_GPIO
#endif

#define PIN_89 PAD_SAR1
#define PAD_SAR1 18
#define GPIO_PAD_18 GPIO17
#ifndef PIN_89_IS_GPIO
#define PIN_89_IS_GPIO 0
#endif
#ifndef PAD_SAR1_IS_GPIO
#define PAD_SAR1_IS_GPIO PIN_89_IS_GPIO
#endif

#define PIN_90 PAD_SAR2
#define PAD_SAR2 19
#define GPIO_PAD_19 GPIO18
#ifndef PIN_90_IS_GPIO
#define PIN_90_IS_GPIO 0
#endif
#ifndef PAD_SAR2_IS_GPIO
#define PAD_SAR2_IS_GPIO PIN_90_IS_GPIO
#endif

#define PIN_91 PAD_SAR3
#define PAD_SAR3 20
#define GPIO_PAD_20 GPIO19
#ifndef PIN_91_IS_GPIO
#define PIN_91_IS_GPIO 0
#endif
#ifndef PAD_SAR3_IS_GPIO
#define PAD_SAR3_IS_GPIO PIN_91_IS_GPIO
#endif

#define PIN_96 PAD_GPIO_PM9
#define PAD_GPIO_PM9 16
#define GPIO_PAD_16 GPIO15
#ifndef PIN_96_IS_GPIO
#define PIN_96_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM9_IS_GPIO
#define PAD_GPIO_PM9_IS_GPIO PIN_96_IS_GPIO
#endif

#define PIN_97 PAD_PM_SPI_CK
#define PAD_PM_SPI_CK 2
#define GPIO_PAD_2 GPIO1
#ifndef PIN_97_IS_GPIO
#define PIN_97_IS_GPIO 0
#endif
#ifndef PAD_PM_SPI_CK_IS_GPIO
#define PAD_PM_SPI_CK_IS_GPIO PIN_97_IS_GPIO
#endif

#define PIN_98 PAD_PM_SPI_DI
#define PAD_PM_SPI_DI 3
#define GPIO_PAD_3 GPIO2
#ifndef PIN_98_IS_GPIO
#define PIN_98_IS_GPIO 0
#endif
#ifndef PAD_PM_SPI_DI_IS_GPIO
#define PAD_PM_SPI_DI_IS_GPIO PIN_98_IS_GPIO
#endif

#define PIN_99 PAD_PM_SPI_DO
#define PAD_PM_SPI_DO 4
#define GPIO_PAD_4 GPIO3
#ifndef PIN_99_IS_GPIO
#define PIN_99_IS_GPIO 0
#endif
#ifndef PAD_PM_SPI_DO_IS_GPIO
#define PAD_PM_SPI_DO_IS_GPIO PIN_99_IS_GPIO
#endif

#define PIN_100 PAD_PM_SPI_CZ
#define PAD_PM_SPI_CZ 1
#define GPIO_PAD_1 GPIO0
#ifndef PIN_100_IS_GPIO
#define PIN_100_IS_GPIO 0
#endif
#ifndef PAD_PM_SPI_CZ_IS_GPIO
#define PAD_PM_SPI_CZ_IS_GPIO PIN_100_IS_GPIO
#endif

#define PIN_101 PAD_GPIO_PM0
#define PAD_GPIO_PM0 7
#define GPIO_PAD_7 GPIO6
#ifndef PIN_101_IS_GPIO
#define PIN_101_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM0_IS_GPIO
#define PAD_GPIO_PM0_IS_GPIO PIN_101_IS_GPIO
#endif

#define PAD_GPIO_PM1 9999
#ifndef PAD_GPIO_PM1_IS_GPIO
#define PAD_GPIO_PM1_IS_GPIO 0
#endif

#define PIN_102 PAD_GPIO_PM4
#define PAD_GPIO_PM4 11
#define GPIO_PAD_11 GPIO10
#ifndef PIN_102_IS_GPIO
#define PIN_102_IS_GPIO 0
#endif
#ifndef PAD_GPIO_PM4_IS_GPIO
#define PAD_GPIO_PM4_IS_GPIO PIN_102_IS_GPIO
#endif

#define PAD_GPIO_PM2 9999
#ifndef PAD_GPIO_PM2_IS_GPIO
#define PAD_GPIO_PM2_IS_GPIO 0
#endif

#define PAD_GPIO_PM5 9999
#ifndef PAD_GPIO_PM5_IS_GPIO
#define PAD_GPIO_PM5_IS_GPIO 0
#endif

#define PAD_GPIO_PM3 9999
#ifndef PAD_GPIO_PM3_IS_GPIO
#define PAD_GPIO_PM3_IS_GPIO 0
#endif

#define PAD_GPIO_PM6 9999
#ifndef PAD_GPIO_PM6_IS_GPIO
#define PAD_GPIO_PM6_IS_GPIO 0
#endif

#define PAD_GPIO_PM7 9999
#ifndef PAD_GPIO_PM7_IS_GPIO
#define PAD_GPIO_PM7_IS_GPIO 0
#endif

#define PIN_103 PAD_IRIN
#define PAD_IRIN 5
#define GPIO_PAD_5 GPIO4
#ifndef PIN_103_IS_GPIO
#define PIN_103_IS_GPIO 0
#endif
#ifndef PAD_IRIN_IS_GPIO
#define PAD_IRIN_IS_GPIO PIN_103_IS_GPIO
#endif

#define PAD_GPIO_PM8 9999
#ifndef PAD_GPIO_PM8_IS_GPIO
#define PAD_GPIO_PM8_IS_GPIO 0
#endif

#define PIN_104 PAD_CEC
#define PAD_CEC 6
#define GPIO_PAD_6 GPIO5
#ifndef PIN_104_IS_GPIO
#define PIN_104_IS_GPIO 0
#endif
#ifndef PAD_CEC_IS_GPIO
#define PAD_CEC_IS_GPIO PIN_104_IS_GPIO
#endif

#define PAD_VSYNC_OUT 9999
#ifndef PAD_VSYNC_OUT_IS_GPIO
#define PAD_VSYNC_OUT_IS_GPIO 0
#endif

#define PAD_ET_MDIO 9999
#ifndef PAD_ET_MDIO_IS_GPIO
#define PAD_ET_MDIO_IS_GPIO 0
#endif

#define PAD_ET_CRS 9999
#ifndef PAD_ET_CRS_IS_GPIO
#define PAD_ET_CRS_IS_GPIO 0
#endif

#define PAD_ET_MDC 9999
#ifndef PAD_ET_MDC_IS_GPIO
#define PAD_ET_MDC_IS_GPIO 0
#endif

#define PAD_ET_TXD3 9999
#ifndef PAD_ET_TXD3_IS_GPIO
#define PAD_ET_TXD3_IS_GPIO 0
#endif

#define PAD_ET_COL 9999
#ifndef PAD_ET_COL_IS_GPIO
#define PAD_ET_COL_IS_GPIO 0
#endif

#define PAD_ET_TXD2 9999
#ifndef PAD_ET_TXD2_IS_GPIO
#define PAD_ET_TXD2_IS_GPIO 0
#endif

#define PAD_ET_RXD0 9999
#ifndef PAD_ET_RXD0_IS_GPIO
#define PAD_ET_RXD0_IS_GPIO 0
#endif

#define PAD_ET_TXER 9999
#ifndef PAD_ET_TXER_IS_GPIO
#define PAD_ET_TXER_IS_GPIO 0
#endif

#define PAD_ET_RXD1 9999
#ifndef PAD_ET_RXD1_IS_GPIO
#define PAD_ET_RXD1_IS_GPIO 0
#endif

#define PAD_ET_RXER 9999
#ifndef PAD_ET_RXER_IS_GPIO
#define PAD_ET_RXER_IS_GPIO 0
#endif

#define PAD_ET_TX_CLK 9999
#ifndef PAD_ET_TX_CLK_IS_GPIO
#define PAD_ET_TX_CLK_IS_GPIO 0
#endif

#define PAD_ET_RX_CLK 9999
#ifndef PAD_ET_RX_CLK_IS_GPIO
#define PAD_ET_RX_CLK_IS_GPIO 0
#endif

#define PAD_ET_TXD0 9999
#ifndef PAD_ET_TXD0_IS_GPIO
#define PAD_ET_TXD0_IS_GPIO 0
#endif

#define PAD_ET_RX_DV 9999
#ifndef PAD_ET_RX_DV_IS_GPIO
#define PAD_ET_RX_DV_IS_GPIO 0
#endif

#define PAD_ET_TXD1 9999
#ifndef PAD_ET_TXD1_IS_GPIO
#define PAD_ET_TXD1_IS_GPIO 0
#endif

#define PAD_ET_RXD2 9999
#ifndef PAD_ET_RXD2_IS_GPIO
#define PAD_ET_RXD2_IS_GPIO 0
#endif

#define PAD_ET_TX_EN 9999
#ifndef PAD_ET_TX_EN_IS_GPIO
#define PAD_ET_TX_EN_IS_GPIO 0
#endif

#define PAD_ET_RXD3 9999
#ifndef PAD_ET_RXD3_IS_GPIO
#define PAD_ET_RXD3_IS_GPIO 0
#endif

#define PAD_S_GPIO5 9999
#ifndef PAD_S_GPIO5_IS_GPIO
#define PAD_S_GPIO5_IS_GPIO 0
#endif

#define PIN_108 PAD_SPDIF_OUT2
#define PAD_SPDIF_OUT2 108
#define GPIO_PAD_108 GPIO107
#ifndef PIN_108_IS_GPIO
#define PIN_108_IS_GPIO 0
#endif
#ifndef PAD_SPDIF_OUT2_IS_GPIO
#define PAD_SPDIF_OUT2_IS_GPIO PIN_108_IS_GPIO
#endif

#define PIN_109 PAD_HSYNC_OUT
#define PAD_HSYNC_OUT 109
#define GPIO_PAD_109 GPIO108
#ifndef PIN_109_IS_GPIO
#define PIN_109_IS_GPIO 0
#endif
#ifndef PAD_HSYNC_OUT_IS_GPIO
#define PAD_HSYNC_OUT_IS_GPIO PIN_109_IS_GPIO
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

#endif /* _MSD7818_H_*/
