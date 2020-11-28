################################################################################
#
# Copyright (c) 2006-2010 MStar Semiconductor, Inc.
# All rights reserved.
#
# Unless otherwise stipulated in writing, any and all information contained
# herein regardless in any format shall remain the sole proprietary of
# MStar Semiconductor Inc. and be kept in strict confidence
# (¡§MStar Confidential Information¡¨) by the recipient.
# Any unauthorized act including without limitation unauthorized disclosure,
# copying, use, reproduction, sale, distribution, modification, disassembling,
# reverse engineering and compiling of the contents of MStar Confidential
# Information is unlawful and strictly prohibited. MStar hereby reserves the
# rights to any and all damages, losses, costs and expenses resulting therefrom.
#
################################################################################

#include "boot.inc"

#ifndef _ArchDefs_h_
#include "ArchDefs.h"
#endif

    .text
	.set    	noreorder
    .global     BootRomInitClock
    .ent        BootRomInitClock

BootRomInitClock:

                                        #//MCU
    WREG_B      0xBF201641, 0x00        #//Set CLK_MCU to 216MHz (Enabled)
    WREG_B      0xBF201640, 0x01        #//Set MCU clock to CLK_MCU

    WREG_B      0xBF201648, 0x88        #//Set CLK_AEON to 172MHz (Enabled)
    WREG_B      0xBF20164D, 0x0C        #//Set CLK_UART0 to 123MHz (Enabled)
    WREG_B      0xBF201650, 0x0C        #//Set CLK_UART1 to 123MHz (Enabled)
    WREG_B      0xBF201651, 0x0C        #//Set CLK_FUART to 123MHz (Enabled)
    WREG_B      0xBF201654, 0x0C        #//Set CLK_UART2 to 123MHz (Enabled)
    WREG_B      0xBF201664, 0x0C        #//Set CLK_UART3 to 123MHz (Enabled)

                                        #//SPI Flash
    WREG_B      0xBF201658, 0x14        #//Set CLK_SPI to 54MHz (Enabled)
	WREG_B    	0xBF20165C, 0x04        #//Set CLK_SPI_M to 48MHz (Enabled)
	WREG_B    	0xBF20165C, 0x24        #//Set CLK_SPI_M to 48MHz

                                        #//PCM / DIG_MUX
    WREG_B      0xBF201668, 0x00        #//Set CLK_PCM to 27MHz (Enabled)
    WREG_B      0xBF201669, 0x00        #//Set CLK_TCK (Enabled)

                                        #//MIU
    WREG_B      0xBF201678, 0x04        #//Set MEMPLL_CLK_BUF to mempll0_clk025x (Enabled)
    WREG_B      0xBF201679, 0x01        #//Set CLK_MPLL_SYN to 432MHz (Enabled)
    WREG_B      0xBF20167C, 0x00        #//Set CLK_MIU to 216MHz (Enabled)
    WREG_B      0xBF20167D, 0x00        #//Set CLK_MIU_REC to XTAL div 2 (Enabled)

                                        #//EMAC
    WREG_B      0xBF201780, 0x00        #//Set CLK_EMAC_AHB to 123MHz (Enabled)
    WREG_B      0xBF201781, 0x00        #//Set CLK_EMAC_RX to CLK_EMAC_RX_in (25MHz) (Enabled)
    WREG_B      0xBF201784, 0x00        #//Set CLK_EMAC_TX to CLK_EMAC_TX_IN (25MHz) (Enabled)
#// WREG_B      0xBF201785, 0x00        #//Set CLK_EMAC_TX_REF to CLK_EMAC_TX_IN (25MHz) (Enabled)
#// WREG_B      0xBF201788, 0x00        #//Set CLK_EMAC_RX_REF to CLK_EMAC_RX_IN (50MHz) (Enabled)

                                        #//GOP
    WREG_B      0xBF201700, 0x00        #//Set CLK_GOPG0 to clk_odclk_p (Enabled)
    WREG_B      0xBF201701, 0x00        #//Set CLK_GOPG1 to clk_odclk_p (Enabled)
    WREG_B      0xBF201704, 0x00        #//Set CLK_GOPG2 to clk_odclk_p (Enabled)
    WREG_B      0xBF201705, 0x04        #//Set CLK_GOPD to CLK_ODCLK (Enabled)
    WREG_B      0xBF201708, 0x00        #//Set CLK_GOPG3 to clk_odclk_p (Enabled)
    WREG_B      0xBF20170C, 0x00        #//Set CLK_PSRAM0 (Enabled)
    WREG_B      0xBF20170D, 0x00        #//Set CLK_PSRAM1 (Enabled)

                                        #//GE
    WREG_B      0xBF201720, 0x00        #//Set CLK_GE to 216MHz (Enabled)

                                        #//Scaler
    WREG_B      0xBF20175C, 0x00		#//Set CLK_FIFO_MINI to FIFO_CLK (Enabled)
    WREG_B      0xBF201760, 0x01        #//Set CLK_LPLL_SYN to 432MHz (Enabled)
                                        #//SC
    WREG_B      0xBF201744, 0x04        #//Set CLK_FICLK_F1 to CLK_FCLK (Enabled)
    WREG_B      0xBF201745, 0x04        #//Set CLK_FICLK_F2 to CLK_FCLK (Enabled)
    WREG_B      0xBF201748, 0x04        #//Set CLK_FODCLK to XTAL (Enabled)
    WREG_B      0xBF201749, 0x1C        #//Set CLK_VCLK to XTAL (Enabled)
    WREG_B      0xBF20174C, 0x1C        #//Set CLK_ODCLK to LPLL output clock (Enabled)
    WREG_B      0xBF20174D, 0x1C        #//Set CLK_BT656 to LPLL output clock (Enabled)
    WREG_B      0xBF201750, 0x20        #//Set CLK_IDCLK_F0 to XTAL (Enabled)
    WREG_B      0xBF201751, 0x20        #//Set CLK_IDCLK_F1 to XTAL (Enabled)
    WREG_B      0xBF201754, 0x20        #//Set CLK_IDCLK_F2 to XTAL (Enabled)
                                        
#ifdef CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH
    #ifndef CONFIG_MSTAR_AUTHEN_ENABLE
        WREG        0xBF221A6C, 0x0000      #// reg_DDRPLL_LOOP_DIV_FIRST   :[15:14]    divideby4
        WREG        0xBF221A68, 0x0200      #// reg_DDRPLL_LOOP_DIV_SECOND      :[15:14]    divideby3
        WREG        0xBF221A60, 0x147A      #// set pll to 300MHz [clk_miu_2x: 300Mhz, clk_miu_1x: 150Mhz]
        WREG        0xBF221A64, 0x002E      #// set pll to 300MHz [clk_miu_2x: 300Mhz, clk_miu_1x: 150Mhz]
        WREG        0xBF221A5C, 0x0800      #// PLL PD
        WREG        0xBF221A40, 0x0020      #// set pll initialvalue
        WREG        0xBF221A44, 0x2020      #// set pll initialvalue
        WREG        0xBF221A48, 0x2000      #// set pll initialvalue
        WREG        0xBF221A58, 0x0100      #// PLL LOCK
        WREG        0xBF202404, 0x0300      #// MCLK PD
    #endif
#endif

    WREG_B       0xBF203AF8, 0x01        #//Set TC0 to 1

    jr           ra
    nop

    .size       BootRomInitClock,.-BootRomInitClock
    .end        BootRomInitClock

