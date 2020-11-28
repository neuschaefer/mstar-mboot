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
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
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

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    regSystem.h
/// @brief  System Chip Top Registers Definition
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _REG_SYSTEM_H_
#define _REG_SYSTEM_H_


//-------------------------------------------------------------------------------------------------
//  Hardware Capability
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

#define REG_TOP_BASE                0xBF203C00
// Register access
#define TOP_READ(addr)              READ_WORD(REG_TOP_BASE + ((addr)<<2))
#define TOP_WRITE(addr, val)        WRITE_WORD((REG_TOP_BASE + ((addr)<<2)), (val))
// Register access utility
#define TOP_OR(addr, val)           TOP_WRITE(addr, TOP_READ(addr) | (val))
#define TOP_AND(addr, val)          TOP_WRITE(addr, TOP_READ(addr) & (val))
#define TOP_XOR(addr, val)          TOP_WRITE(addr, TOP_READ(addr) ^ (val))

#if 0
#define REG_TOP_CHIP_CONFIG_OW      0x0000
#define REG_TOP_UTMI_UART_SETHL     0x0001
    #define TOP_UART_RX_EN                      BIT(10)
#define REG_TOP_TEST_IN_OUT         0x0002
    #define TOP_TEST_IN_MASK                    BMASK(5:4)
    #define TOP_TEST_IN_TS0                     BITS(5:4, 1)
    #define TOP_TEST_IN_PCI                     BITS(5:4, 2)
    #define TOP_TEST_IN_I2S                     BITS(5:4, 3)
    #define TOP_TEST_OUT_MASK                   BMASK(7:6)
    #define TOP_GPIO_AU0_EN                     BIT(8)
    #define TOP_GPIO_AU1_EN                     BIT(9)
    #define TOP_GPIO_AU2_EN                     BIT(10)
    #define TOP_GPIO_AU3_EN                     BIT(11)
    #define TOP_GPIO_AU4_EN                     BIT(12)
    #define TOP_GPIO_AU5_EN                     BIT(13)
    #define TOP_GPIO_AU6_EN                     BIT(14)
    #define TOP_GPIO_AU7_EN                     BIT(15)
#define REG_TOP_PWM                 0x0003
    #define TOP_DUMMY_10_MASK                   BMASK(5:0)
    #define TOP_PWM_OEN_TS_ERR                  BIT(13)

#define REG_TOP_PCI                 0x0004
#define REG_TOP_SPI_EMAC            0x0005
    #define TOP_CKG_EMACRX_MASK                 BMASK(12:10)
    #define TOP_CKG_EMACRX_DIS                  BIT(10)
    #define TOP_CKG_EMACRX_INV                  BIT(11)
    #define TOP_CKG_EMACRX_CLK_EMAC_RX_IN_BUF   BITS(12:12, 0)
    #define TOP_CKG_EMACRX_CLK_DFT              BITS(12:12, 1)
    #define TOP_CKG_EMACTX_MASK                 BMASK(15:13)
    #define TOP_CKG_EMACTX_DIS                  BIT(13)
    #define TOP_CKG_EMACTX_INV                  BIT(14)
    #define TOP_CKG_EMACTX_CLK_EMAC_TX_IN_BUF   BITS(15:15, 0)
    #define TOP_CKG_EMACTX_CLK_DFT              BITS(15:15, 1)
#define REG_TOP_CR_CI_GPIO          0x0006
    #define TOP_SM2_GPIO_USE                    BIT(0)
    #define TOP_PAD_CI_ADHI_MASK                BMASK(2:1)
    #define TOP_PAD_CI_ADHI_CCIR                BITS(2:1, 1)            // GPIO_CI5
    #define TOP_PAD_CI_ADHI_CI                  BITS(2:1, 3)
    #define TOP_PACK1_TSO_SWITCH                BIT(3)
    #define TOP_PACK2_CI_SWITCH                 BIT(4)
    #define TOP_PACK9_CI_SWITCH                 BIT(5)
    #define TOP_PACK1_CI_SWITCH                 BIT(7)
    #define TOP_PACKAGE                         BMASK(13:10)
    #define TOP_PACKAGE_0                       BITS(13:10, 0)
    #define TOP_PACKAGE_1                       BITS(13:10, 1)
    #define TOP_PACKAGE_2                       BITS(13:10, 2)
    #define TOP_PACKAGE_3                       BITS(13:10, 3)
    #define TOP_PACKAGE_4                       BITS(13:10, 4)
    #define TOP_PACKAGE_7                       BITS(13:10, 7)
    #define TOP_PACKAGE_8                       BITS(13:10, 8)
    #define TOP_PACKAGE_9                       BITS(13:10, 9)
    #define TOP_SPICZ1_TYPE                     BIT(14)

#define REG_TOP_PCI_PD_TEST         0x0007
    #define TOP_PCI_RPU                         BMASK(9:0)
    #define TOP_PD_ALL                          BIT(10)
    #define TOP_TEST_CLK_MODE                   BIT(11)
    #define TOP_TURN_OFF_PAD                    BIT(12)
#define REG_TOP_CKG_ADCD_DVBC       0x0008
    #define TOP_CKG_ADCD_SHFT                   0
    #define TOP_CKG_ADCD_MASK                   BMASK(3:0)
    #define TOP_CKG_ADCD_DIS                    BIT(0)
    #define TOP_CKG_ADCD_INV                    BIT(1)
    #define TOP_CKG_ADCD_SRC_MASK               BMASK(3:2)
    #define TOP_CKG_ADCD_SRC_ADC                BITS(3:2, 0)
    #define TOP_CKG_ADCD_SRC_XTAL               BITS(3:2, 1)
    #define TOP_CKG_ADCD_SRC_EXTADC             BITS(3:2, 2)
    #define TOP_CKG_ADCD_SRC_DFT                BITS(3:2, 3)
    #define TOP_CKG_DVBC_ADC_SHFT               4
    #define TOP_CKG_DVBC_ADC_MASK               BMASK(7:4)
    #define TOP_CKG_DVBC_INN_SHFT               8
    #define TOP_CKG_DVBC_INN_MASK               BMASK(11:8)
    #define TOP_CKG_DVBC_INN_DIS                BIT(8)
    #define TOP_CKG_DVBC_INN_INV                BIT(9)
    #define TOP_CKG_DVBC_INN_SRC_MASK           BMASK(11:10)              // 3:DFT_Live, other:clk_31
    #define TOP_CKG_DVBC_INN_SRC_31             BITS(11:10, 0)
    #define TOP_CKG_DVBC_INN_SRC_DFT            BITS(11:10, 3)
    #define TOP_CKG_DVBC_INN2X_SHFT             12
    #define TOP_CKG_DVBC_INN2X_MASK             BMASK(15:12)
    #define TOP_CKG_DVBC_INN2X_DIS              BIT(12)
    #define TOP_CKG_DVBC_INN2X_INV              BIT(13)
    #define TOP_CKG_DVBC_INN2X_SRC              BMASK(15:14)              // 3:DFT_Live, other:clk_62
    #define TOP_CKG_DVBC_INN2X_SRC_62           BITS(15:14, 0)
    #define TOP_CKG_DVBC_INN2X_SRC_DFT          BITS(15:14, 3)

#define REG_TOP_DVBC_SC_CCIR        0x0009
    #define TOP_CKG_DVBC_EQ_SHFT                0
    #define TOP_CKG_DVBC_EQ_MASK                BMASK(3:0)
    #define TOP_CKG_DVBC_EQ_DIS                 BIT(0)
    #define TOP_CKG_DVBC_EQ_INV                 BIT(1)
    #define TOP_CKG_DVBC_EQ_SRC                 BMASK(3:2)               // 3:DFT_Live, other:clk_18
    #define TOP_CKG_DVBC_EQ_SRC_18              BITS(3:2, 0)
    #define TOP_CKG_DVBC_EQ_SRC_DFT             BITS(3:2, 3)
    #define TOP_CKG_DVBC_EQ8X_MASK              BMASK(7:4)
    #define TOP_CKG_DVBC_EQ8X_DIS               BIT(4)
    #define TOP_CKG_DVBC_EQ8X_INV               BIT(5)
    #define TOP_CKG_DVBC_EQ8X_SRC               BMASK(7:6)               // 3:DFT_Live, other:clk_144
    #define TOP_CKG_DVBC_EQ8X_SRC_144           BITS(7:6, 0)
    #define TOP_CKG_DVBC_EQ8X_SRC_DFT           BITS(7:6, 3)
    #define TOP_CKG_SC_MASK                     BMASK(13:8)
    #define TOP_CKG_SC_DIS                      BIT(8)
    #define TOP_CKG_SC_INV                      BIT(9)
    #define TOP_CKG_SC_SRC                      BMASK(13:10)
    #define TOP_CKG_SC_SRC_27                   BITS(13:10, 0)
    #define TOP_CKG_SC_SRC_54                   BITS(13:10, 1)
    #define TOP_CKG_SC_SRC_MEMPLL_DIV2          BITS(13:10, 2)
    #define TOP_CKG_SC_SRC_144                  BITS(13:10, 3)
    #define TOP_CKG_SC_SRC_173                  BITS(13:10, 4)
    #define TOP_CKG_SC_SRC_192                  BITS(13:10, 5)
    #define TOP_CKG_SC_SRC_MEMPLL               BITS(13:10, 6)
    #define TOP_CKG_SC_SRC_216                  BITS(13:10, 7)
    #define TOP_CKG_SC_SRC_DFT                  BITS(13:10, 8)
    #define TOP_CLK_CCIR_INV                    BIT(14)

#define REG_TOP_TSOUT_DISP          0x000A
    #define TOP_PCI_RPUPI                       BMASK(9:0)
    #define TOP_CLK_TSOUT_INV                   BIT(10)
    #define TOP_CKG_DISP                        BMASK(15:12)
    #define TOP_CKG_DISP_DIS                    BIT(12)
    #define TOP_CKG_DISP_INV                    BIT(13)
    #define TOP_CKG_DISP_SRC                    BMASK(15:14)
    #define TOP_CKG_DISP_CLK_27_BUF             BITS(15:14, 0)
    #define TOP_CKG_DISP_CLK_54_BUF             BITS(15:14, 1)
    #define TOP_CKG_DISP_HDMIPLL_CLK_BUF_DIV2   BITS(15:14, 2)
    #define TOP_CKG_DISP_HDMIPLL_CLK_BUF        BITS(15:14, 3)

#define REG_TOP_DVBC_HDMI_CI        0x000B
    #define TOP_CKG_DVBC_TS_MASK                BMASK(4:0)
    #define TOP_CKG_DVBC_TS_DIS                 BIT(0)
    #define TOP_CKG_DVBC_TS_INV                 BIT(1)
    #define TOP_CKG_DVBC_TS_SRC_MASK            BMASK(4:0)
    #define TOP_CKG_DVBC_TS_DIS                 BIT(0)
    #define TOP_CKG_DVBC_TS_INV                 BIT(1)
    #define TOP_CKG_DVBC_TS_SRC_62              BITS(4:2, 0)
    #define TOP_CKG_DVBC_TS_SRC_54              BITS(4:2, 1)
    #define TOP_CKG_DVBC_TS_SRC_43P2            BITS(4:2, 2)
    #define TOP_CKG_DVBC_TS_SRC_6               BITS(4:2, 3)
    #define TOP_CKG_DVBC_TS_SRC_7P2             BITS(4:2, 4)
    #define TOP_CKG_DVBC_TS_SRC_7P75            BITS(4:2, 5)
    #define TOP_CKG_DVBC_TS_SRC_9               BITS(4:2, 6)
    #define TOP_CKG_DVBC_TS_SRC_DFT             BITS(4:2, 7)
    #define TOP_PACK9_TSO_SWITCH_BIT0           BIT(5)
    #define TOP_TSI_GPIO_USE                    BIT(7)
    #define TOP_PAD_CI_CTL_MASK                 BIT(9)
    #define TOP_PAD_CI_CTL_X                    0
    #define TOP_PAD_CI_CTL_GPIO                 BIT(9)                  // GPIO_CI8_9
#define REG_TOP_GPIO_TSI_IN             0x000C
    #define TOP_OVER_CUR_PROTECTION_STATUS  BIT(3)
#define REG_TOP_PCI_RPD             0x000D
#define REG_TOP_GPIO_TSI_OUT        0x000E
    #define TOP_GPIO_CI_A23                     BIT(0)
    #define TOP_CI_USE                          BIT(1)
    #define TOP_NOR_8X                          BIT(2)
    #define TOP_SM2_OPEN_DRAIN                  BIT(3)
    #define TOP_SM1_OPEN_DRAIN                  BIT(4)
    #define TOP_GPIO_W67_USE                    BIT(5)
    #define TOP_GPIO_W89_USE                    BIT(6)
    #define TOP_PACK9_TSO_SWITCH_BIT1           BIT(9)

#define REG_TOP_GPIO_TSI_OEN        0x000F
    #define TOP_SMART_CARD_CONTROL_ENABLE_OCP0   BIT(1)
    #define TOP_SMART_CARD_CONTROL_ENABLE_OCP1   BIT(2)
    #define TOP_SMART_CARD_CONTROL_ENABLE_OCP2   BIT(3)

#define REG_TOP_POFF_MCU            0x0010
    #define TOP_POFF_TS0MUX_MASK                BMASK(7:6)
    #define TOP_POFF_TS0MUX_PAD0                BITS(7:6, 0)
    #define TOP_POFF_TS0MUX_PAD1                BITS(7:6, 1)
    #define TOP_POFF_TS0MUX_DVBC                BITS(7:6, 3)
    #define TOP_POFF_TS1MUX_MASK                BMASK(9:8)
    #define TOP_POFF_TS1MUX_PAD0                BITS(9:8, 0)
    #define TOP_POFF_TS1MUX_PAD1                BITS(9:8, 1)
    #define TOP_POFF_TS1MUX_DVBC                BITS(9:8, 3)
    #define TOP_INT_TYPE                        BMASK(12:10)
    #define TOP_INT_TYPE1                       BITS(12:10, 0)
    #define TOP_INT_TYPE2                       BITS(12:10, 1)
    #define TOP_INT_TYPE3                       BITS(12:10, 2)
    #define TOP_INT_TYPE4                       BITS(12:10, 3)
#define REG_TOP_MCU_USB_STC0        0x0011
    #define TOP_MCU_CLK_MASK                    BMASK(0:0)
    #define TOP_MCU_CLK_DFT                     BITS(0:0, 0)
    #define TOP_MCU_CLK_SRC_MCUCLK              BITS(0:0, 1)
    #define TSP_STC0_SEL                        BIT(7)
#define REG_TOP_USB_RIU_DDR_MIU     0x0012
    #define TOP_CKG_USB_MASK                    BMASK(1:0)
    #define TOP_CKG_USB_DIS                     BIT(0)
    #define TOP_CKG_USB_INV                     BIT(1)
    #define TOP_CKG_MIU_DIS                     BIT(12)
    #define TOP_CKG_MIU_INV                     BIT(13)
    #define TOP_CKG_MIU_SRC_MASK                BMASK(15:14)
    #define TOP_CKG_MIU_SRC_MEMPLL              BITS(15:14, 0)
    #define TOP_CKG_MIU_SRC_170                 BITS(15:14, 1)
    #define TOP_CKG_MIU_SRC_MEMPLL_DIV2         BITS(15:14, 2)
    #define TOP_CKG_MIU_SRC_192                 BITS(15:14, 3)
#define REG_TOP_TS0_TSP_STC0        0x0013
    #define TOP_CKG_TS0_MASK                    BMASK(3:0)
    #define TOP_CKG_TS0_DIS                     BIT(0)
    #define TOP_CKG_TS0_INV                     BIT(1)
    #define TOP_CKG_TS0_SRC_MASK                BMASK(3:2)
    #define TOP_CKG_TS0_SRC_DVB                 BITS(3:2, 0)
    #define TOP_CKG_TS0_SRC_TS0                 BITS(3:2, 0)
    #define TOP_CKG_TS0_SRC_TS1                 BITS(3:2, 1)
    #define TOP_CKG_TS0_SRC_DFT                 BITS(3:2, 3)
    #define TOP_CKG_TS0_SRC_DEMOD               TOP_CKG_TS0_SRC_DVB
    #define TOP_CKG_TS0_SRC_CI                  TOP_CKG_TS0_SRC_TS0
    #define TOP_CKG_TSP_MASK                    BMASK(11:6)
    #define TOP_CKG_TSP_DIS                     BIT(6)
    #define TOP_CKG_TSP_INV                     BIT(7)
    #define TOP_CKG_TSP_SRC_144                 BITS(11:8, 0)
    #define TOP_CKG_TSP_SRC_123                 BITS(11:8, 1)
    #define TOP_CKG_TSP_SRC_72                  BITS(11:8, 4)
    #define TOP_CKG_TSP_SRC_DFT                 BITS(11:8, 7)
    #define TOP_CKG_STC0_MASK                   BMASK(15:12)
    #define TOP_CKG_STC0_DIS                    BIT(12)
    #define TOP_CKG_STC0_INV                    BIT(13)
    #define TOP_CKG_STC0_SRC_STC0               BITS(15:14, 0)
    #define TOP_CKG_STC0_SRC_1                  BITS(15:14, 1)
    #define TOP_CKG_STC0_SRC_27                 BITS(15:14, 2)
    #define TOP_CKG_STC0_SRC_DFT                BITS(15:14, 3)
#define REG_TOP_MAD_MVD             0x0014
    #define TOP_CKG_MAD_STC_MASK                BMASK(3:0)
    #define TOP_CKG_MAD_STC_DIS                 BIT(0)
    #define TOP_CKG_MAD_STC_INV                 BIT(1)
    #define TOP_CKG_MAD_STC_SRC_STC0            BITS(3:2, 0)
    #define TOP_CKG_MAD_STC_SRC_27              BITS(3:2, 2)
    #define TOP_CKG_MAD_STC_SRC_DFT             BITS(3:2, 3)
    #define TOP_CKG_MVD_BOOT_MASK               BMASK(9:4)
    #define TOP_CKG_MVD_BOOT_DIS                BIT(4)
    #define TOP_CKG_MVD_BOOT_INV                BIT(5)
    #define TOP_CKG_MVD_BOOT_SRC_144            BITS(9:6, 0)
    #define TOP_CKG_MVD_BOOT_SRC_123            BITS(9:6, 1)
    #define TOP_CKG_MVD_BOOT_SRC_108            BITS(9:6, 2)
    #define TOP_CKG_MVD_BOOT_SRC_86             BITS(9:6, 3)
    #define TOP_CKG_MVD_BOOT_SRC_72             BITS(9:6, 4)
    #define TOP_CKG_MVD_BOOT_SRC_54             BITS(9:6, 5)
    #define TOP_CKG_MVD_BOOT_SRC_MIU            BITS(9:6, 6)
    #define TOP_CKG_MVD_BOOT_SRC_DFT            BITS(9:6, 7)
    #define TOP_CKG_MVD_MASK                    BMASK(15:10)
    #define TOP_CKG_MVD_DIS                     BIT(10)
    #define TOP_CKG_MVD_INV                     BIT(11)
    #define TOP_CKG_MVD_SRC_144                 BITS(15:12, 0)
    #define TOP_CKG_MVD_SRC_123                 BITS(15:12, 1)
    #define TOP_CKG_MVD_SRC_108                 BITS(15:12, 2)
    #define TOP_CKG_MVD_SRC_86                  BITS(15:12, 3)
    #define TOP_CKG_MVD_SRC_72                  BITS(15:12, 4)
    #define TOP_CKG_MVD_SRC_54                  BITS(15:12, 5)
    #define TOP_CKG_MVD_SRC_MIU                 BITS(15:12, 6)
    #define TOP_CKG_MVD_SRC_DFT                 BITS(15:12, 7)
#define REG_TOP_SVD_EMAC_GE         0x0015
    #define TOP_CKG_SVD_MASK                    BMASK(5:0)
    #define TOP_CKG_SVD_DIS                     BIT(0)
    #define TOP_CKG_SVD_INV                     BIT(1)
    #define TOP_CKG_SVD_SRC_240                 BITS(5:2, 0)
    #define TOP_CKG_SVD_SRC_216                 BITS(5:2, 1)
    #define TOP_CKG_SVD_SRC_192                 BITS(5:2, 2)
    #define TOP_CKG_SVD_SRC_123                 BITS(5:2, 3)
    #define TOP_CKG_SVD_SRC_86                  BITS(5:2, 4)
    #define TOP_CKG_SVD_SRC_72                  BITS(5:2, 5)
    #define TOP_CKG_SVD_SRC_54                  BITS(5:2, 6)
    #define TOP_CKG_SVD_SRC_DFT                 BITS(5:2, 7)
    #define TOP_CKG_EMACAHB_MASK                BMASK(11:8)
    #define TOP_CKG_EMACAHB_DIS                 BIT(8)
    #define TOP_CKG_EMACAHB_INV                 BIT(9)
    #define TOP_CKG_EMACAHB_SRC_123             BITS(11:10, 0)
    #define TOP_CKG_EMACAHB_SRC_108             BITS(11:10, 1)
    #define TOP_CKG_EMACAHB_SRC_86              BITS(11:10, 2)
    #define TOP_CKG_EMACAHB_SRC_DFT             BITS(11:10, 3)
    #define TOP_CKG_GE_MASK                     BMASK(15:12)
    #define TOP_CKG_GE_DIS                      BIT(12)
    #define TOP_CKG_GE_INV                      BIT(13)
    #define TOP_CKG_GE_SRC_123                  BITS(15:12, 0)
    #define TOP_CKG_GE_SRC_108                  BITS(15:12, 1)
    #define TOP_CKG_GE_SRC_86                   BITS(15:12, 2)
    #define TOP_CKG_GE_SRC_DFT                  BITS(15:12, 3)

#define REG_TOP_GOP                 0x0016
    #define TOP_CKG_GOP0_MASK                   BMASK(4:0)
    #define TOP_CKG_GOP0_DIS                    BIT(0)
    #define TOP_CKG_GOP0_INV                    BIT(1)
    #define TOP_CKG_GOP0_SRC_MASK               BMASK(4:2)
    #define TOP_CKG_GOP0_SRC_OSDI               BITS(3:2, 0)
    #define TOP_CKG_GOP0_SRC_SC                 BITS(3:2, 1)
    #define TOP_CKG_GOP0_SRC_TCON               BITS(3:2, 2)
    #define TOP_CKG_GOP0_SRC_VE                 BITS(3:2, 3)
    #define TOP_CKG_GOP0_SRC_DFT                BIT(4)
    #define TOP_CKG_GOP1_MASK                   BMASK(9:5)
    #define TOP_CKG_GOP1_DIS                    BIT(5)
    #define TOP_CKG_GOP1_INV                    BIT(6)
    #define TOP_CKG_GOP1_SRC_MASK               BMASK(9:7)
    #define TOP_CKG_GOP1_SRC_OSDI               BITS(8:7, 0)
    #define TOP_CKG_GOP1_SRC_SC                 BITS(8:7, 1)
    #define TOP_CKG_GOP1_SRC_TCON               BITS(8:7, 2)
    #define TOP_CKG_GOP1_SRC_VE                 BITS(8:7, 3)
    #define TOP_CKG_GOP1_SRC_DFT                BIT(9)
    #define TOP_CKG_GOP2_MASK                   BMASK(14:10)
    #define TOP_CKG_GOP2_DIS                    BIT(10)
    #define TOP_CKG_GOP2_INV                    BIT(11)
    #define TOP_CKG_GOP2_SRC_MASK               BMASK(14:12)
    #define TOP_CKG_GOP2_SRC_OSDI               BITS(13:12, 0)
    #define TOP_CKG_GOP2_SRC_SC                 BITS(13:12, 1)
    #define TOP_CKG_GOP2_SRC_TCON               BITS(13:12, 2)
    #define TOP_CKG_GOP2_SRC_VE                 BITS(13:12, 3)
    #define TOP_CKG_GOP2_SRC_DFT                BIT(14)
#define REG_TOP_GOP_UART            0x0017
    #define TOP_CKG_GOP_PALETTE0_MASK           BMASK(1:0)
    #define TOP_CKG_GOP_PALETTE0_DIS            BIT(0)
    #define TOP_CKG_GOP_PALETTE0_INV            BIT(1)
    #define TOP_CKG_GOP_PALETTE1_MASK           BMASK(3:2)
    #define TOP_CKG_GOP_PALETTE1_DIS            BIT(2)
    #define TOP_CKG_GOP_PALETTE1_INV            BIT(3)
    #define TOP_CKG_GOP3_MASK                   BMASK(8:4)
    #define TOP_CKG_GOP3_DIS                    BIT(4)
    #define TOP_CKG_GOP3_INV                    BIT(5)
    #define TOP_CKG_GOP3_SRC_MASK               BMASK(8:6)
    #define TOP_CKG_GOP3_SRC_OSDI               BITS(7:6, 0)
    #define TOP_CKG_GOP3_SRC_SC                 BITS(7:6, 1)
    #define TOP_CKG_GOP3_SRC_TCON               BITS(7:6, 2)
    #define TOP_CKG_GOP3_SRC_VE                 BITS(7:6, 3)
    #define TOP_CKG_GOP3_SRC_DFT                BIT(8)
    #define TOP_CKG_GOPD_MASK                   BMASK(12:9)
    #define TOP_CKG_GOPD_DIS                    BIT(9)
    #define TOP_CKG_GOPD_INV                    BIT(10)
    #define TOP_CKG_GOPD_SRC_MASK               BMASK(8:6)
    #define TOP_CKG_GOPD_SRC_TCON               BITS(12:11, 0)
    #define TOP_CKG_GOPD_SRC_SC                 BITS(12:11, 1)
    #define TOP_CKG_GOPD_SRC_OSDI               BITS(12:11, 2)
    #define TOP_CKG_GOPD_SRC_DFT                BITS(12:11, 3)
    #define TOP_CKG_UART_MASK                   BMASK(15:13)
    #define TOP_CKG_UART_DIS                    BIT(13)
    #define TOP_CKG_UART_INV                    BIT(14)
    #define TOP_CKG_UART_SRC_UART               BITS(15:15, 0)
    #define TOP_CKG_UART_SRC_DFT                BITS(15:15, 1)
#define REG_TOP_SM_PCM              0x0018
    #define TOP_CKG_SM_MASK                     BMASK(11:8)
    #define TOP_CKG_SM_DIS                      BIT(8)
    #define TOP_CKG_SM_INV                      BIT(9)
    #define TOP_CKG_SM_SRC_6                    BITS(11:10, 0)
    #define TOP_CKG_SM_SRC_4P5                  BITS(11:10, 1)
    #define TOP_CKG_SM_SRC_3                    BITS(11:10, 2)
    #define TOP_CKG_SM_SRC_DFT                  BITS(11:10, 3)
    #define TOP_CKG_PCM_MASK                    BMASK(15:12)
    #define TOP_CKG_PCM_DIS                     BIT(12)
    #define TOP_CKG_PCM_INV                     BIT(13)
    #define TOP_CKG_PCM_SRC_27                  BITS(15:14, 0)
    #define TOP_CKG_PCM_SRC_DFT                 BITS(15:14, 2)
#define REG_TOP_VE                  0x0019
    #define TOP_CKG_VE_MASK                     BMASK(11:8)
    #define TOP_CKG_VE_DIS                      BIT(8)
    #define TOP_CKG_VE_INV                      BIT(9)
    #define TOP_CKG_VE_SRC_27                   BITS(11:10, 0)
    #define TOP_CKG_VE_SRC_DFT                  BITS(11:10, 2)
    #define TOP_CKG_VEDAC_MASK                  BMASK(15:12)
    #define TOP_CKG_VEDAC_DIS                   BIT(12)
    #define TOP_CKG_VEDAC_INV                   BIT(13)
    #define TOP_CKG_VEDAC_SRC_27                BITS(15:14, 0)
    #define TOP_CKG_VEDAC_SRC_54                BITS(15:14, 1)
    #define TOP_CKG_VEDAC_SRC_108               BITS(15:14, 2)
    #define TOP_CKG_VEDAC_SRC_DFT               BITS(15:14, 3)
#define REG_TOP_DAC_SDR             0x001A
    #define TOP_CKG_DAC_MASK                    BMASK(4:0)
    #define TOP_CKG_DAC_DIS                     BIT(0)
    #define TOP_CKG_DAC_INV                     BIT(1)
    #define TOP_CKG_DAC_SRC_DISP                BITS(4:2, 0)            //[???]
    #define TOP_CKG_DAC_SRC_VEDAC               BITS(4:2, 1)
    #define TOP_CKG_DAC_SRC_DVBC_INN            BITS(4:2, 2)
    #define TOP_CKG_DAC_SRC_DVBC_EQ             BITS(4:2, 3)
    #define TOP_CKG_DAC_SRC_ADCD_D              BITS(4:2, 4)
    #define TOP_CKG_DAC_SRC_DFT                 BITS(4:2, 6)
#define REG_TOP_SDIO_EMAC_USB       0x001B
    #define TOP_USB_DRVVBUS                     BIT(14)
    #define TOP_USB_DRVVBUS1                    BIT(15)
#define REG_TOP_VE_SDIO             0x001C
    #define TOP_CKG_VEIN_MASK                   BMASK(3:0)
    #define TOP_CKG_VEIN_DIS                    BIT(0)
    #define TOP_CKG_VEIN_INV                    BIT(1)
    #define TOP_CKG_VEIN_SRC_DISP               BITS(3:2, 0)
    #define TOP_CKG_VEIN_SRC_27                 BITS(3:2, 1)
    #define TOP_CKG_VEIN_SC_P                   BITS(3:2, 2)
    #define TOP_CKG_VEIN_SRC_DFT                BITS(3:2, 3)
    #define TOP_CKG_SDIO_MASK                   BMASK(14:8)
    #define TOP_CKG_SDIO_DIS                    BIT(8)
    #define TOP_CKG_SDIO_INV                    BIT(9)
    #define TOP_CKG_SDIO_SRC_86D256             BITS(14:10, 0)
    #define TOP_CKG_SDIO_SRC_86D64              BITS(14:10, 1)
    #define TOP_CKG_SDIO_SRC_86D16              BITS(14:10, 2)
    #define TOP_CKG_SDIO_SRC_54D4               BITS(14:10, 3)
    #define TOP_CKG_SDIO_SRC_72D4               BITS(14:10, 4)
    #define TOP_CKG_SDIO_SRC_86D4               BITS(14:10, 5)
    #define TOP_CKG_SDIO_SRC_54D2               BITS(14:10, 6)
    #define TOP_CKG_SDIO_SRC_72D2               BITS(14:10, 7)
    #define TOP_CKG_SDIO_SRC_86D2               BITS(14:10, 8)
    #define TOP_CKG_SDIO_SRC_54                 BITS(14:10, 9)
    #define TOP_CKG_SDIO_SRC_72                 BITS(14:10,10)
    #define TOP_CKG_SDIO_SRC_SDIO_SSC           BITS(14:10,11)
    #define TOP_CKG_SDIO_SRC_DFT                BITS(14:10,16)
#define REG_TOP_DC0_NUM             0x0020
#define REG_TOP_DC0_DEN             0x0021
#define REG_TOP_MCU                 0x0022
    #define TOP_CKG_MCU_MASK                    BMASK(12:8)
    #define TOP_CKG_MCU_DIS                     BIT(8)
    #define TOP_CKG_MCU_INV                     BIT(9)
    #define TOP_CKG_MCU_SRC_MASK                BMASK(12:10)
    #define TOP_CKG_MCU_SRC_216                 BITS(12:10, 0)
    #define TOP_CKG_MCU_SRC_DRAM                BITS(12:10, 1)
    #define TOP_CKG_MCU_SRC_192                 BITS(12:10, 2)
    #define TOP_CKG_MCU_SRC_173                 BITS(12:10, 3)
    #define TOP_CKG_MCU_SRC_160                 BITS(12:10, 4)
    #define TOP_CKG_MCU_SRC_123                 BITS(12:10, 5)
    #define TOP_CKG_MCU_SRC_108                 BITS(12:10, 6)
    #define TOP_CKG_MCU_SRC_DFT                 BITS(12:10, 7)
#define REG_TOP_USB_CW_L            0x0024
#define REG_TOP_USB_CW_H            0x0025
#define REG_TOP_STC0_CW_L           0x0026
#define REG_TOP_STC0_CW_H           0x0027
#define REG_TOP_DC0_CW_L            0x002A
#define REG_TOP_DC0_CW_H            0x002B
#define REG_TOP_002C                0x002C
    #define TOP_GPIO_TS1_DIS                    BIT(0)
    #define TOP_CI_NOT_PF_USE                   BIT(1)
    // #define TOP_TSO_GPIO                        0x0001 // [ ???]
#define REG_TOP_TSPUART_SM2         0x002D
    #define TOP_CKG_SM2_SHFT                    8
    #define TOP_CKG_SM2_MASK                    BMASK(11:8)
    #define TOP_CKG_SM2_DIS                     BIT(8)
    #define TOP_CKG_SM2_INV                     BIT(9)
    #define TOP_CKG_SM2_SRC_6                   BITS(11:10, 0)
    #define TOP_CKG_SM2_SRC_4P5                 BITS(11:10, 1)
    #define TOP_CKG_SM2_SRC_3                   BITS(11:10, 2)
    #define TOP_CKG_SM2_SRC_DFT                 BITS(11:10, 3)
#define REG_TOP_MIU_DAC2_JPG        0x002E
    #define TOP_CKG_MIU_REC_MASK                BMASK(3:0)
    #define TOP_CKG_MIU_REC_DIS                 BIT(0)
    #define TOP_CKG_MIU_REC_INV                 BIT(1)
    #define TOP_CKG_MIU_REC_SRC_XTAL_DIV2       BITS(2:2, 0)
    #define TOP_CKG_MIU_REC_SRC_DFT             BITS(2:2, 1)
    #define TOP_CKG_DAC2_MASK                   BMASK(8:4)
    #define TOP_CKG_DAC2_DIS                    BIT(4)
    #define TOP_CKG_DAC2_INV                    BIT(5)
    #define TOP_CKG_DAC2_SRC_DISP               BITS(8:6, 0)            //[???]
    #define TOP_CKG_DAC2_SRC_VEDAC              BITS(8:6, 1)
    #define TOP_CKG_DAC2_SRC_DVBC_INN           BITS(8:6, 2)
    #define TOP_CKG_DAC2_SRC_DVBC_EQ            BITS(8:6, 3)
    #define TOP_CKG_DAC2_SRC_ADCD_D             BITS(8:6, 4)
    #define TOP_CKG_DAC2_SRC_DFT                BITS(8:6, 6)
    #define TOP_CKG_JPG_MASK                    BMASK(12:9)
    #define TOP_CKG_JPG_DIS                     BIT(9)
    #define TOP_CKG_JPG_INV                     BIT(10)
    #define TOP_CKG_JPG_SRC_123                 BITS(12:11, 0)            //[???]
    #define TOP_CKG_JPG_SRC_108                 BITS(12:11, 1)
    #define TOP_CKG_JPG_SRC_86                  BITS(12:11, 2)
    #define TOP_CKG_JPG_SRC_DFT                 BITS(12:11, 3)

#define REG_TOP_GPIO_WN_IN          0x0030
#define REG_TOP_GPIO_WN_OUT         0x0031

#define REG_TOP_GPIO_WN_OEN_DVBC    0x0036
/*
    #define TOP_GPIO_W0                         BIT(0)
    #define TOP_GPIO_W1                         BIT(1)
    #define TOP_GPIO_N0                         BIT(4)
    #define TOP_GPIO_N1                         BIT(5)
    #define TOP_GPIO_N2                         BIT(6)
    #define TOP_GPIO_N3                         BIT(7)
*/
    #define TOP_CKG_MVD_IAP_RMEM_DIS            BIT(0)
    #define TOP_CKG_MVD_IAP_RMEM_INV            BIT(1)
    #define TOP_CKG_MVD_IAP_RMEM_MVD_OR_MIU     BITS(2:2, 0)
    #define TOP_CKG_MVD_IAP_RMEM_DFT            BITS(2:2, 1)
    #define TOP_CKG_DVBC_DMA_MASK               BMASK(11:8)
    #define TOP_CKG_DVBC_DMA_EQ                 BITS(11:8, 0)
    #define TOP_CKG_DVBC_DMA_ADCD               BITS(11:8, 1)
    #define TOP_CKG_DVBC_DMA_0                  BITS(11:8, 2)
    #define TOP_CKG_DVBC_DMA_DFT                BITS(11:8, 3)
#define REG_TOP_DUMMY23             0x0037
    #define TOP_CKG_DUMMY23_MASK                BMASK(10:0)
#define REG_TOP_GPIO_PWM_CI_IN      0x0039
#define REG_TOP_GPIO_PWM_CI_OUT     0x003A
    #define TOP_TS_ERR                          BIT(0)
    #define TOP_CKG_TS1_MASK                    BMASK(3:1)
    #define TOP_GPIO_TS1_INV                    BIT(1)
    #define TOP_GPIO_TS1_SRC_MASK               BMASK(3:2)
    #define TOP_GPIO_TS1_SRC_DVB                BITS(3:2, 0)
    #define TOP_GPIO_TS1_SRC_TS0                BITS(3:2, 1)
    #define TOP_GPIO_TS1_SRC_TS1                BITS(3:2, 2)
    #define TOP_GPIO_TS1_SRC_DFT                BITS(3:2, 3)
    #define TOP_GPIO_TS1_SRC_DEMOD              TOP_GPIO_TS1_SRC_DVB
    #define TOP_GPIO_TS1_SRC_CI                 TOP_GPIO_TS1_SRC_TS0
    #define TOP_GPIO_PWM0_OUT                   BIT(4)
    #define TOP_GPIO_PWM1_OUT                   BIT(5)
/*
    #define TOP_GPIO_CI0_OUT                    BIT(6)
    #define TOP_GPIO_CI1_OUT                    BIT(7)
    #define TOP_GPIO_CI2_OUT                    BIT(8)
    #define TOP_GPIO_CI3_OUT                    BIT(9)
    #define TOP_GPIO_CI4_OUT                    BIT(10)
    #define TOP_GPIO_CI5_OUT                    BIT(11)
    #define TOP_GPIO_CI6_OUT                    BIT(12)
    #define TOP_GPIO_CI7_OUT                    BIT(13)
    #define TOP_GPIO_CI8_OUT                    BIT(14)
    #define TOP_GPIO_CI9_OUT                    BIT(15)
*/

#define REG_TOP_GPIO_PWM_CI_OEN     0x003B
    #define TOP_GPIO_PWM0_DISABLE               BIT(4)
    #define TOP_GPIO_PWM1_DISABLE               BIT(5)
/*
    #define TOP_GPIO_CI0_DISABLE                BIT(6)
    #define TOP_GPIO_CI1_DISABLE                BIT(7)
    #define TOP_GPIO_CI2_DISABLE                BIT(8)
    #define TOP_GPIO_CI3_DISABLE                BIT(9)
    #define TOP_GPIO_CI4_DISABLE                BIT(10)
    #define TOP_GPIO_CI5_DISABLE                BIT(11)
    #define TOP_GPIO_CI6_DISABLE                BIT(12)
    #define TOP_GPIO_CI7_DISABLE                BIT(13)
    #define TOP_GPIO_CI8_DISABLE                BIT(14)
    #define TOP_GPIO_CI9_DISABLE                BIT(15)
*/

/*
#define REG_TOP_GPIO_S_IN           0x003C
#define REG_TOP_GPIO_S_OUT          0x003D
    #define TOP_GPIO_S0_OUT                     BIT(0)
    #define TOP_GPIO_S1_OUT                     BIT(1)
    #define TOP_GPIO_S2_OUT                     BIT(2)
    #define TOP_GPIO_S3_OUT                     BIT(3)
    #define TOP_GPIO_S4_OUT                     BIT(4)
    #define TOP_GPIO_S5_OUT                     BIT(5)
    #define TOP_GPIO_S6_OUT                     BIT(6)


#define REG_TOP_GPIO_S_OEN          0x003E
    #define TOP_GPIO_S0_DISABLE                 BIT(0)
    #define TOP_GPIO_S1_DISABLE                 BIT(1)
    #define TOP_GPIO_S2_DISABLE                 BIT(2)
    #define TOP_GPIO_S3_DISABLE                 BIT(3)
    #define TOP_GPIO_S4_DISABLE                 BIT(4)
    #define TOP_GPIO_S5_DISABLE                 BIT(5)
    #define TOP_GPIO_S6_DISABLE                 BIT(6)


#define REG_TOP_GPIO_AU_SPI_IN      0x003F
#define REG_TOP_GPIO_AU_SPI_OUT     0x0040
#define REG_TOP_GPIO_AU_SPI_OEN     0x0041
*/

#define REG_TOP_ET_PAD              0x0040
    #define TOP_ET_PAD1_USE_MASK                BMASK(2:0)
    #define TOP_ET_PAD1_USE_DEFAULT             BITS(2:0, 0)
    #define TOP_ET_PAD1_USE_ET_TX               BITS(2:0, 1)
    #define TOP_ET_PAD1_USE_SDIO                BITS(2:0, 2)
    #define TOP_ET_PAD1_USE_CCIR                BITS(2:0, 3)
    #define TOP_ET_PAD1_USE_TSI                 BITS(2:0, 4)
    #define TOP_ET_PAD2_USE_MASK                BMASK(4:3)
    #define TOP_ET_PAD2_USE_DEFAULT             BITS(4:3, 0)
    #define TOP_ET_PAD2_USE_ET_RX               BITS(4:3, 1)
    #define TOP_ET_PAD2_USE_ET_TXRX             BITS(4:3, 2)
    #define TOP_ET_PAD2_USE_CCIR                BITS(4:3, 3)
    #define TOP_GPIO_S_USE                      BIT(5)

#define REG_TOP_DUMMY_15_16         0x004B
    #define TOP_PAD_CI_D4_OEN_OCP2                      BIT(4)
    #define TOP_PAD_CI_D4_OEN_OCP1                      BIT(5)
    #define TOP_PAD_CI_D4_OEN_OCP0                      BIT(6)
    #define TOP_SM2_VCC_GPIO_USE                BIT(5)
    #define TOP_SM1_VCC_GPIO_USE                BIT(6)
    #define TOP_DUMMY_15_MASK                   BMASK(11:8)

/*
#define REG_TOP_DUMMY_18_21         0x0051
    #define TOP_PAD_TS_ERR_FLAG                 BIT(10)
*/

#define REG_TOP_DUMMY1              0x0053
    #define TOP_DUMMY1                          BIT(0)

/*
#define REG_TOP_GPIO_DI_DO          0x0054

#define REG_TOP_UART                0x0055
*/
#define REG_TOP_JTAG_AUD_CI_GPIO_PWM 0x0056
    #define TOP_PAD_AU1_MASK                    BMASK(5:4)
    #define TOP_PAD_AU1_GPIO                    0
    #define TOP_PAD_AU1_IICM0                   BITS(5:4, 1)
    #define TOP_PAD_AU1_IICM1                   BITS(5:4, 2)
    #define TOP_PAD_AU1_X                       BITS(5:4, 3)
    #define TOP_PAD_AU2_MASK                    BMASK(7:6)
    #define TOP_PAD_AU2_GPIO                    0
    #define TOP_PAD_AU2_PCM                     BMASK(7:6, 1)
    #define TOP_PAD_AU2_X                       BMASK(7:6, 2)
    #define TOP_PAD_GPIOW0_MASK                 BIT(9)
    #define TOP_PAD_GPIOW0_X                    0
    #define TOP_PAD_GPIOW0_CEC                  BIT(9)
    #define TOP_PAD_PWM_MASK                    BIT(10)
    #define TOP_PAD_PWM_X                       0
    #define TOP_PAD_PWM_GPIO                    BIT(10)

#define REG_TOP_STAT_BOND           0x0061
#define REG_TOP_BOND_OV_KEY         0x0063
#define REG_TOP_CHIP_CONFIG_STAT    0x0065
#endif
#define REG_TOP_DEVICE_ID           0x0F00
#define REG_TOP_CHIP_VERSION        0x0F01
    #define CHIP_VERSION_SHFT                   0
    #define CHIP_VERSION_MASK                   BMASK(7:0)
    #define CHIP_REVISION_SHFT                  8
    #define CHIP_REVISION_MASK                  BMASK(15:8)
#if 0
#define REG_TOP_TESTBUS             0x0075
    #define TOP_TESTBUS_EN                      BIT(14)
#define REG_CLK_EJ_MIPS_TSJ         0x0076
    #define TOP_TESTCLK_OUT_MASK                BMASK(2:0)
    #define TOP_TESTCLK_OUT_NONE                BITS(2:0, 0)
    #define TOP_SM1_GPIO_USE                    BIT(3)
    #define TOP_SPI_GPIO_USE                    BIT(4)
#define REG_TOP_RESET_CPU0          0x0077
    #define TOP_RESET_PASSWD_MASK               BMASK(14:0)
    #define TOP_RESET_CPU0                      BIT(15)

#define REG_ECC_BASE                0xBF8069C0
#define ECC_REG(addr)               (*((volatile MS_U32*)(REG_ECC_BASE + ((addr)<<2))))

#define REG_ECC_REQUEST             0x0001
    #define ECC_MCU_BURST_READ_EN               BIT(5)


#define REG_WDT_BASE                0xBF808400
#define WDT_REG(addr)               (*((volatile MS_U32*)(REG_WDT_BASE + ((addr)<<2))))

#define REG_WDT_DISABLEWORD_L       0x0000
#define REG_WDT_DISABLEWORD_H       0x0001
#define REG_WDT_PROGRAMKEY_L        0x0002
#define REG_WDT_PROGRAMKEY_H        0x0003
#define REG_WDT_ENABLEMCURESET      0x0004
#define REG_WDT_CLEAR_STATUS        0x0010
#define REG_WDT_SETTIME             0x0012
#define REG_WDT_COUNTER_L           0x0014
#define REG_WDT_COUNTER_H           0x0015


#define REG_ANA_BASE                0xBF80A400
#define ANA_REG(addr)               (*((volatile MS_U32*)(REG_ANA_BASE + ((addr)<<2))))

#define REG_ANA_MPLL		0x0001
    #define ANA_MPLL_PD				BIT(7)
#define REG_ANA_REF		0x0006
    #define ANA_REF_TST_IRE                     BIT(0)
    #define ANA_REF_PWDN_ICAL                   BIT(1)
    #define ANA_REF_TST_BGO                     BIT(2)
    #define ANA_REF_TST_BGIE                    BIT(3)
    #define ANA_REF_VCLP                        BMASK(6:4)
    #define ANA_REF_TST_VRPM                    BIT(7)
    #define ANA_REF_TST_VCLPBW                  BMASK(9:8)
    #define ANA_REF_PWDN_CLP                    BIT(10)
    #define ANA_REF_TST_IRO                     BIT(11)
    #define ANA_REF_ICAL                        BMASK(15:12)
#define REG_ANA_REF_PWR		0x0007
    #define ANA_REF_PWDN_ICAL                   BIT(1)
    #define ANA_REF_PWDN                        BIT(3)
#define REG_ANA_ADC_PWR		0x0009
    #define ANA_ADC_APDN                        BIT(1)
    #define ANA_REF_APDN                        BIT(11)

// 0x000C
    #define ANA_EXT_DAC                         BIT(0)
    #define ANA_CLK_POL                         BIT(1)
    #define ANA_DBG_SEL                         BMASK(3:2)
    #define ANA_SEL_TUAGC                       BMASK(9:8)
    #define ANA_SEL_IFAGC                       BMASK(11:10)
    #define ANA_AGC_PAD_OEN                     BIT(12)

// 0x000D
    #define ANA_ADC_OFFSET                      BMASK(11:0)
    #define ANA_ADC_RDSEL                       BIT(13)
    #define ANA_ADCIN_SIGN                      BIT(14)
    #define ANA_ADCD_FRZ                        BIT(15)

// 0x0010
    // reg_adcin_i read only register Debug Purpose to check ADC is Input or Not!
    // If ADC is input , reading this register will find it always changing !
    #define ANA_ADCIN_I                         BMASK(10:0)
#endif

#ifdef MCU_AEON
    #define REG_IRQ_BASE            0xA0200000+(0x0c80<<2) // 0xBF805600

    #define REG_FIQ_MASK_L          0x0024
    #define REG_FIQ_MASK_H          0x0025
    #define REG_FIQEXP_MASK_L       0x0026
    #define REG_FIQEXP_MASK_H       0x0027
    #define REG_FIQ_CLEAR_L         0x002c
    #define REG_FIQ_CLEAR_H         0x002d
    #define REG_FIQEXP_CLEAR_L      0x002e
    #define REG_FIQEXP_CLEAR_H      0x002f
    #define REG_FIQ_PENDING_L       0x002c
    #define REG_FIQ_PENDING_H       0x002d
    #define REG_FIQEXP_PENDING_L    0x002e
    #define REG_FIQEXP_PENDING_H    0x002f

    #define REG_IRQ_MASK_L          0x0034
    #define REG_IRQ_MASK_H          0x0035
    #define REG_IRQEXP_MASK_L       0x0036
    #define REG_IRQEXP_MASK_H       0x0037
    #define REG_IRQ_PENDING_L       0x003c
    #define REG_IRQ_PENDING_H       0x003d
    #define REG_IRQEXP_PENDING_L    0x003e
    #define REG_IRQEXP_PENDING_H    0x003f
#else
    // for MIPS VPE 0
    #define REG_IRQ_BASE            0xBF200000+(0x0c80<<2) // 0xBF800A80

    #define REG_FIQ_MASK_L          0x0064
    #define REG_FIQ_MASK_H          0x0065
    #define REG_FIQEXP_MASK_L       0x0066
    #define REG_FIQEXP_MASK_H       0x0067
    #define REG_FIQ_CLEAR_L         0x006c
    #define REG_FIQ_CLEAR_H         0x006d
    #define REG_FIQEXP_CLEAR_L      0x006e
    #define REG_FIQEXP_CLEAR_H      0x006f
    #define REG_FIQ_PENDING_L       0x006c
    #define REG_FIQ_PENDING_H       0x006d
    #define REG_FIQEXP_PENDING_L    0x006e
    #define REG_FIQEXP_PENDING_H    0x006f

    #define REG_IRQ_MASK_L          0x0074
    #define REG_IRQ_MASK_H          0x0075
    #define REG_IRQEXP_MASK_L       0x0076
    #define REG_IRQEXP_MASK_H       0x0077
    #define REG_IRQ_PENDING_L       0x007c
    #define REG_IRQ_PENDING_H       0x007d
    #define REG_IRQEXP_PENDING_L    0x007e
    #define REG_IRQEXP_PENDING_H    0x007f
#endif

    #define IRQ_REG(addr)           (*((volatile MS_U16*)(REG_IRQ_BASE + ((addr)<<2))))

    // REG_FIQ_MASK_L
    //FIQ Low 16 bits
    #define FIQL_MASK                           0xFFFF
    #define FIQ_EXTIMER0                        (0x1 << (E_FIQ_EXTIMER0         - E_FIQL_START) )
    #define FIQ_EXTIMER1                        (0x1 << (E_FIQ_EXTIMER1         - E_FIQL_START) )
    #define FIQ_WDT                             (0x1 << (E_FIQ_WDT              - E_FIQL_START) )
    #define FIQ_HDMI_NON_PCM                    (0x1 << (E_FIQ_HDMI_NON_PCM     - E_FIQL_START) )
    #define FIQ_SPDIF_IN_NON_PCM                (0x1 << (E_FIQ_SPDIF_IN_NON_PCM - E_FIQL_START) )
    #define FIQ_EMAC                            (0x1 << (E_FIQ_EMAC             - E_FIQL_START) )
    #define FIQ_SE_DSP2UP                       (0x1 << (E_FIQ_SE_DSP2UP        - E_FIQL_START) )
    #define FIQ_TSP2AEON                        (0x1 << (E_FIQ_TSP2AEON         - E_FIQL_START) )


    // REG_FIQ_MASK_H
    //FIQ High 16 bits
    #define FIQH_MASK                           0xFFFF
    #define FIQ_VIVALDI_STR                     (0x1 << (E_FIQ_VIVALDI_STR  - E_FIQH_START) )
    #define FIQ_VIVALDI_PTS                     (0x1 << (E_FIQ_VIVALDI_PTS  - E_FIQH_START) )
    #define FIQ_DSP_MIU_PROT                    (0x1 << (E_FIQ_DSP_MIU_PROT - E_FIQH_START) )
    #define FIQ_XIU_TIMEOUT                     (0x1 << (E_FIQ_XIU_TIMEOUT  - E_FIQH_START) )
    #define FIQ_VSYNC_VE4VBI                    (0x1 << (E_FIQ_VSYNC_VE4VBI - E_FIQH_START) )
    #define FIQ_FIELD_VE4VBI                    (0x1 << (E_FIQ_FIELD_VE4VBI - E_FIQH_START) )
    #define FIQ_VDMCU2HK                        (0x1 << (E_FIQ_VDMCU2HK     - E_FIQH_START) )
    #define FIQ_VE_DONE_TT                      (0x1 << (E_FIQ_VE_DONE_TT   - E_FIQH_START) )
    #define FIQ_INT_CCFL                        (0x1 << (E_FIQ_INT_CCFL     - E_FIQH_START) )
    #define FIQ_INT                             (0x1 << (E_FIQ_INT          - E_FIQH_START) )
    #define FIQ_IR                              (0x1 << (E_FIQ_IR           - E_FIQH_START) )
    #define FIQ_AFEC_VSYNC                      (0x1 << (E_FIQ_AFEC_VSYNC   - E_FIQH_START) )
    #define FIQ_DEC_DSP2UP                      (0x1 << (E_FIQ_DEC_DSP2UP   - E_FIQH_START) )
    #define FIQ_MIPS_WDT                        (0x1 << (E_FIQ_MIPS_WDT     - E_FIQH_START) )
    #define FIQ_DSP2MIPS                        (0x1 << (E_FIQ_DSP2MIPS     - E_FIQH_START) )



    // #define REG_IRQ_PENDING_L
    #define IRQ_UART0                           (0x1 << (E_IRQ_UART0        - E_IRQL_START) )
    #define IRQ_MVD                             (0x1 << (E_IRQ_MVD          - E_IRQL_START) )
    #define IRQ_PS                              (0x1 << (E_IRQ_PS           - E_IRQL_START) )
    #define IRQ_NFIE                            (0x1 << (E_IRQ_NFIE         - E_IRQL_START) )
    #define IRQ_USB                             (0x1 << (E_IRQ_USB          - E_IRQL_START) )
    #define IRQ_UHC                             (0x1 << (E_IRQ_UHC          - E_IRQL_START) )
    #define IRQ_EC_BRIDGE                       (0x1 << (E_IRQ_EC_BRIDGE    - E_IRQL_START) )
    #define IRQ_EMAC                            (0x1 << (E_IRQ_EMAC         - E_IRQL_START) )
    #define IRQ_DISP                            (0x1 << (E_IRQ_DISP         - E_IRQL_START) )
    #define IRQ_DHC                             (0x1 << (E_IRQ_DHC          - E_IRQL_START) )
    #define IRQ_SBM                             (0x1 << (E_IRQ_SBM          - E_IRQL_START) )
    #define IRQ_COMB                            (0x1 << (E_IRQ_COMB         - E_IRQL_START) )


    // #define REG_IRQ_PENDING_H
    #define IRQH_MASK                           0xFFFF
    #define IRQ_TSP2HK                          (0x1 << (E_IRQ_TSP2HK       - E_IRQH_START) )
    #define IRQ_VE                              (0x1 << (E_IRQ_VE           - E_IRQH_START) )
    #define IRQ_CIMAX2MCU                       (0x1 << (E_IRQ_CIMAX2MCU    - E_IRQH_START) )
    #define IRQ_DC                              (0x1 << (E_IRQ_DC           - E_IRQH_START) )
    #define IRQ_GOP                             (0x1 << (E_IRQ_GOP          - E_IRQH_START) )
    #define IRQ_PCM                             (0x1 << (E_IRQ_PCM          - E_IRQH_START) )
    #define IRQ_IIC0                            (0x1 << (E_IRQ_IIC0         - E_IRQH_START) )
    #define IRQ_RTC                             (0x1 << (E_IRQ_RTC          - E_IRQH_START) )
    #define IRQ_KEYPAD                          (0x1 << (E_IRQ_KEYPAD       - E_IRQH_START) )
    #define IRQ_PM                              (0x1 << (E_IRQ_PM           - E_IRQH_START) )
    #define IRQ_DDC2BI                          (0x1 << (E_IRQ_DDC2BI       - E_IRQH_START) )
    #define IRQ_SCM                             (0x1 << (E_IRQ_SCM          - E_IRQH_START) )
    #define IRQ_VBI                             (0x1 << (E_IRQ_VBI          - E_IRQH_START) )
    #define IRQ_MLINK                           (0x1 << (E_IRQ_MLINK        - E_IRQH_START) )
    #define IRQ_AFEC                            (0x1 << (E_IRQ_AFEC         - E_IRQH_START) )
    #define IRQ_ADCDVI2RIU                      (0x1 << (E_IRQ_ADCDVI2RIU   - E_IRQH_START) )

    // 
    #define IRQEXPL_MASK                        0xFFFF
    #define IRQEXPL_HVD                         (0x1 << (E_IRQEXPL_HVD              - E_IRQEXPL_START) )
    #define IRQEXPL_USB2                        (0x1 << (E_IRQEXPL_USB2             - E_IRQEXPL_START) )
    #define IRQEXPL_UHC2                        (0x1 << (E_IRQEXPL_UHC2             - E_IRQEXPL_START) )
    #define IRQEXPL_MIU                         (0x1 << (E_IRQEXPL_MIU              - E_IRQEXPL_START) )
    #define IRQEXPL_DPTX                        (0x1 << (E_IRQEXPL_DPTX             - E_IRQEXPL_START) )
    #define IRQEXPL_TMDDRLINK                   (0x1 << (E_IRQEXPL_TMDDRLINK        - E_IRQEXPL_START) )
    #define IRQEXPL_AEON2HI                     (0x1 << (E_IRQEXPL_AEON2HI          - E_IRQEXPL_START) )
    #define IRQEXPL_UART1                       (0x1 << (E_IRQEXPL_UART1            - E_IRQEXPL_START) )
    #define IRQEXPL_UART2                       (0x1 << (E_IRQEXPL_UART2            - E_IRQEXPL_START) )
    #define IRQEXPL_MPIF                        (0x1 << (E_IRQEXPL_MPIF             - E_IRQEXPL_START) )
    #define IRQEXPL_MLINK                       (0x1 << (E_IRQEXPL_MLINK            - E_IRQEXPL_START) )
    #define IRQEXPL_JPD                         (0x1 << (E_IRQEXPL_JPD              - E_IRQEXPL_START) )
    #define IRQEXPL_DISPI                       (0x1 << (E_IRQEXPL_DISPI            - E_IRQEXPL_START) )
    #define IRQEXPL_M4VE                        (0x1 << (E_IRQEXPL_M4VE             - E_IRQEXPL_START) )

    #define IRQEXPH_MASK                        0xFFFF
    #define IRQEXPH_BDMA0                       (0x1 << (E_IRQEXPH_BDMA0            - E_IRQEXPH_START) )
    #define IRQEXPH_BDMA1                       (0x1 << (E_IRQEXPH_BDMA1            - E_IRQEXPH_START) )
    #define IRQEXPH_UART2MCU                    (0x1 << (E_IRQEXPH_UART2MCU         - E_IRQEXPH_START) )
    #define IRQEXPH_URDMA2MCU                   (0x1 << (E_IRQEXPH_URDMA2MCU        - E_IRQEXPH_START) )
    #define IRQEXPH_DVI_HDMI_HDCP               (0x1 << (E_IRQEXPH_DVI_HDMI_HDCP    - E_IRQEXPH_START) )
    #define IRQEXPH_G3D2MCU                     (0x1 << (E_IRQEXPH_G3D2MCU          - E_IRQEXPH_START) )
    #define IRQEXPH_HDCP                        (0x1 << (E_IRQEXPH_HDCP             - E_IRQEXPH_START) )

    #define FIQEXPL_MASK                        0xFFFF
    #define FIQEXPL_IR_INT_RC                   (0x1 << (E_FIQEXPL_IR_INT_RC                 - E_FIQEXPL_START) )
    #define FIQEXPL_AU_DMA_BUF_INT              (0x1 << (E_FIQEXPL_AU_DMA_BUF_INT            - E_FIQEXPL_START) )
    #define FIQEXPL_8051_TO_MIPS_VPE0           (0x1 << (E_FIQEXPL_8051_TO_MIPS_VPE0         - E_FIQEXPL_START) )
    #define FIQEXPL_8051_TO_MIPS_VPE1           (0x1 << (E_FIQEXPL_8051_TO_MIPS_VPE1         - E_FIQEXPL_START) )
    #define FIQEXPL_8051_TO_AEON                (0x1 << (E_FIQEXPL_8051_TO_AEON              - E_FIQEXPL_START) )
    #define FIQEXPL_AEON_TO_MIPS_VPE0           (0x1 << (E_FIQEXPL_AEON_TO_MIPS_VPE0         - E_FIQEXPL_START) )
    #define FIQEXPL_AEON_TO_MIPS_VPE1           (0x1 << (E_FIQEXPL_AEON_TO_MIPS_VPE1         - E_FIQEXPL_START) )
    #define FIQEXPL_AEON_TO_8051                (0x1 << (E_FIQEXPL_AEON_TO_8051              - E_FIQEXPL_START) )
    #define FIQEXPL_MIPS_VPE1_TO_MIPS_VPE0      (0x1 << (E_FIQEXPL_MIPS_VPE1_TO_MIPS_VPE0    - E_FIQEXPL_START) )
    #define FIQEXPL_MIPS_VPE1_TO_AEON           (0x1 << (E_FIQEXPL_MIPS_VPE1_TO_AEON         - E_FIQEXPL_START) )
    #define FIQEXPL_MIPS_VPE1_TO_8051           (0x1 << (E_FIQEXPL_MIPS_VPE1_TO_8051         - E_FIQEXPL_START) )

    #define FIQEXPH_MASK                        0xFFFF
    #define FIQEXPH_MIPS_VPE0_TO_MIPS_VPE1      (0x1 << (E_FIQEXPH_MIPS_VPE0_TO_MIPS_VPE1    - E_FIQEXPH_START) )
    #define FIQEXPH_MIPS_VPE0_TO_AEON           (0x1 << (E_FIQEXPH_MIPS_VPE0_TO_AEON         - E_FIQEXPH_START) )
    #define FIQEXPH_MIPS_VPE0_TO_8051           (0x1 << (E_FIQEXPH_MIPS_VPE0_TO_8051         - E_FIQEXPH_START) )

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
 
#define INTERFACE extern 

//INTERFACE MS_U32 u32_ge0_mmio_base;


//extern MS_U32 u32_bdma_mmio_base;
//extern MS_U32 u32_scaler_mmio_base;

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
//#define     REG_GE0_BASE     u32_ge0_mmio_base
//#define     REG_BDMA_BASE     u32_bdma_mmio_base
//#define     REG_SCALER_BASE   u32_scaler_mmio_base


//-------------------------------------------------------------------------------------------------

// Macros

//-------------------------------------------------------------------------------------------------

#define MReg_Write2Byte(u32Base, u32Reg, u16Val )                                                 \
    do {((volatile MS_U16*)(u32Base))[((u32Reg))] = u16Val;} while(0)

#define MReg_Read2Byte( u32Base, u32Reg )                                                         \
    ((volatile MS_U16*)(u32Base))[((u32Reg) )]

#define MReg_WriteByte(u32Base, u32Reg, u8Val )                                                 \
    do{((volatile MS_U8*)(u32Base))[((u32Reg) * 2) - ((u32Reg) & 1)] = u8Val;} while(0)

#define MReg_ReadByte( u32Base, u32Reg )                                                         \
    ((volatile MS_U8*)(u32Base))[((u32Reg) * 2) - ((u32Reg) & 1)]

 #define MReg_Write3Byte(u32Base, u32Reg, u32Val )   \
    do {                                                                     \
        if ((u32Reg) & 0x01)                                                                \
        {                                                                                               \
            MReg_WriteByte(u32Base, u32Reg , u32Val);                                    \
            MReg_Write2Byte(u32Base, (u32Reg + 1) , ((u32Val) >> 8));                                      \
        }                                                                                           \
        else                                                                                        \
        {                                                                                               \
            MReg_Write2Byte(u32Base, (u32Reg) ,  u32Val);                                                         \
            MReg_WriteByte(u32Base, (u32Reg + 2) ,  ((u32Val) >> 16));                             \
        }   \
    } while(0)

#define MReg_Write4Byte( u32Base, u32Reg, u32Val )                                               \
    do {                                                                     \
        if ((u32Reg) & 0x01)                                                      \
        {                                                                                               \
            MReg_WriteByte( u32Base, u32Reg ,  u32Val);                                         \
            MReg_Write2Byte( u32Base, (u32Reg + 1) , ( (u32Val) >> 8));                                      \
            MReg_WriteByte( u32Base, (u32Reg + 3) ,  ((u32Val) >> 24));                           \
        }                                                                                               \
        else                                                                                                \
        {                                                                                                   \
            MReg_Write2Byte(u32Base, u32Reg ,  u32Val);                                                             \
            MReg_Write2Byte(u32Base,  (u32Reg + 2) ,  ((u32Val) >> 16));                                             \
        }                                                                     \
    } while(0)

#define MReg_WriteByteMask(u32Base, u32Reg, u8Val, u8Msk )                                      \
    do {                                                                     \
        MReg_WriteByte( u32Base, u32Reg, (MReg_ReadByte(u32Base, ((u32Reg) )) & ~(u8Msk)) | ((u8Val) & (u8Msk)));                   \
    } while(0)

#define MReg_Write2ByteMask( u32Base, u32Reg, u16Val , u16Msk)                                               \
    do {                                                                     \
        if ( ((u32Reg) & 0x01) )                                                        \
        {                                                                                           \
            MReg_WriteByteMask( u32Base, ((u32Reg)+1) , (((u16Val) & 0xff00)>>8) , (((u16Msk)&0xff00)>>8) );                                                                          \
            MReg_WriteByteMask( u32Base, (u32Reg) , ((u16Val) & 0x00ff) , ((u16Msk)&0x00ff) );                                                                          \
        }                                                                               \
        else                                                                            \
        {                                                                               \
            MReg_Write2Byte(u32Base,  u32Reg ,  (((u16Val) & (u16Msk))  | (MReg_Read2Byte(u32Base,  u32Reg  ) & (~( u16Msk ))))  );                                                       \
        }      \
    } while(0)




#endif // _REG_SYSTEM_H_

