################################################################################
#
# Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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

#ifndef _BOOT_INC_
#include "boot.inc"
#endif

#ifndef _ArchDefs_h_
#include "ArchDefs.h"
#endif

    .text
	.set    	noreorder
    .global     BootRomInitClock
    .ent        BootRomInitClock

BootRomInitClock:

.if (CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51 != 1) 
                                                            #//MCU
    WREG_B      (0xBF000000 + (0x100B20 << 1) + 1), 0x00    #//Set CLK_MCU to 216MHz (Enabled)
    WREG_B      (0xBF000000 + (0x100B20 << 1)), 0x01        #//Set MCU clock to CLK_MCU
.endif
                                                            #//HK-AEON
    WREG_B      (0xBF000000 + (0x100B24 << 1)), 0x88        #//Set CLK_AEON to 172MHz (Enabled)

                                                            #//UART
    WREG_B      (0xBF000000 + (0x100B26 << 1) + 1), 0x0C    #//Set CLK_UART0 to 123MHz (Enabled)
    WREG_B      (0xBF000000 + (0x100B28 << 1)), 0x0C        #//Set CLK_UART1 to 123MHz (Enabled)
    WREG_B      (0xBF000000 + (0x100B28 << 1) + 1), 0x0C    #//Set CLK_UART2 to 123MHz (Enabled)

.if (CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51 != 1) 
                                                            #//SPI Flash
    WREG_B      (0xBF000000 + (0x100B2C << 1)), 0x14        #//Set CLK_SPI to 54MHz (Enabled)
	WREG_B    	(0xBF000000 + (0x100B2E << 1)), 0x04        #//Set CLK_SPI_M to 48MHz (Enabled)
	WREG_B    	(0xBF000000 + (0x100B2E << 1)), 0x24        #//Set CLK_SPI_M to 48MHz
.endif
                                                            #//PCM / DIG_MUX
    WREG_B      (0xBF000000 + (0x100B34 << 1)), 0x00        #//Set CLK_PCM to 27MHz (Enabled)
    WREG_B      (0xBF000000 + (0x100B34 << 1) + 1), 0x00    #//Set CLK_TCK (Enabled)

.if (CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51 != 1) 
                                                            #//MIU
    WREG_B      (0xBF000000 + (0x100B3C << 1)), 0x00        #//Set MEMPLL_CLK_BUF to mempll0_clk025x (Enabled)
    WREG_B      (0xBF000000 + (0x100B3C << 1) + 1), 0x01    #//Set CLK_MPLL_SYN to 432MHz (Enabled)
    WREG_B      (0xBF000000 + (0x100B3E << 1)), 0x0C        #//Set CLK_MIU to 216MHz (Enabled)
    WREG_B      (0xBF000000 + (0x100B3E << 1) + 1), 0x00    #//Set CLK_MIU_REC to XTAL div 2 (Enabled)
.endif
                                                            #//VD
    WREG_B      (0xBF000000 + (0x100B40 << 1)), 0x00        #//Set VD clock source to VD_ADC_CLK (Enabled)
    WREG_B      (0xBF000000 + (0x100B40 << 1) + 1), 0x01    #//Set CLK_VD (Disabled)
    WREG_B      (0xBF000000 + (0x100B42 << 1)), 0x11        #//Set CLK_VDMCU to 108MHz (Disabled)
    WREG_B      (0xBF000000 + (0x100B42 << 1) + 1), 0x05    #//Set CLK_VD200 to 216MHz (Disabled)
    WREG_B      (0xBF000000 + (0x100B44 << 1)), 0x01        #//Set CLK_MCU_MAIL0 to CLK_MCU (Disabled)
    WREG_B      (0xBF000000 + (0x100B44 << 1) + 1), 0x05    #//Set CLK_MCU_MAIL1 to CLK_MCU (Disabled)
    WREG_B      (0xBF000000 + (0x100B46 << 1)), 0x01        #//Set CLK_VD2X (Disabled)
    WREG_B      (0xBF000000 + (0x100B46 << 1) + 1), 0x01    #//Set CLK_VD32FSC to VD_ADC_CLK (Disabled)

                                                            #//VE
    WREG_B      (0xBF000000 + (0x100B48 << 1)), 0x01        #//Set CLK_VE to 27MHz (Disabled)
    WREG_B      (0xBF000000 + (0x100B48 << 1) + 1), 0x09    #//Set CLK_VEDAC to 108MHz (Disabled)
    WREG_B      (0xBF000000 + (0x100B4A << 1)), 0x01        #//Set CLK_VE_IN to CLK_ADC (Disabled)
    WREG_B      (0xBF000000 + (0x100B4C << 1)), 0x01        #//Set CLK_DACA2 to VIF clock (Disabled)
    WREG_B      (0xBF000000 + (0x100B4C << 1) + 1), 0x01    #//Set CLK_DACB2 to VIF clock (Disabled)

                                                            #//TSP
    WREG_B      (0xBF000000 + (0x100B50 << 1)), 0x01        #//Set CLK_TS0 to TS0_CLK (Disabled)
    WREG_B      (0xBF000000 + (0x100B50 << 1) + 1), 0x05    #//Set CLK_TS1 to TS1_CLK (Disabled)
    WREG_B      (0xBF000000 + (0x100B54 << 1)), 0x01        #//Set CLK_TSP to 144MHz (Disabled)
    WREG_B      (0xBF000000 + (0x100B54 << 1) + 1), 0x01    #//Set CLK_STC0 to STC0 synthesizer output (Disabled)

                                                            #//VD_MHEG5
    WREG_B      (0xBF000000 + (0x100B60 << 1)), 0x05        #//Set CLK_VD_MHEG5 to 144MHz (Disabled)

                                                            #//HVD
    WREG_B      (0xBF000000 + (0x100B62 << 1)), 0x05        #//Set CLK_HVD to 172MHz (Disabled)

                                                            #//JPD
    WREG_B      (0xBF000000 + (0x100B6A << 1)), 0x05        #//Set CLK_JPD to 108MHz (Disabled)

                                                            #//MVD
    WREG_B      (0xBF000000 + (0x100B72 << 1)), 0x01        #//Set CLK_MVD to 144MHz (Disabled)
    WREG_B      (0xBF000000 + (0x100B72 << 1) + 1), 0x05    #//Set CLK_MVD2 to 144MHz (Disabled)
    WREG_B      (0xBF000000 + (0x100B74 << 1)), 0x01        #//Set CLK_MVD_CHROMA (Disabled)
    WREG_B      (0xBF000000 + (0x100B74 << 1) + 1), 0x01    #//Set CLK_MVD_LUMMA_A (Disabled)
    WREG_B      (0xBF000000 + (0x100B76 << 1)), 0x01        #//Set CLK_MVD_LUMMA_B (Disabled)
    WREG_B      (0xBF000000 + (0x100B76 << 1) + 1), 0x01    #//Set CLK_MVD_LUMMA_C (Disabled)
    WREG_B      (0xBF000000 + (0x100B78 << 1)), 0x01        #//Set CLK_MVD_RMEM_C (Disabled)
    WREG_B      (0xBF000000 + (0x100B78 << 1) + 1), 0x01    #//Set CLK_MVD_RMEM1_C (Disabled)

                                                            #//GOP
    WREG_B      (0xBF000000 + (0x100B80 << 1)), 0x00        #//Set CLK_GOPG0 to clk_odclk_p (Enabled)
    WREG_B      (0xBF000000 + (0x100B80 << 1) + 1), 0x00    #//Set CLK_GOPG1 to clk_odclk_p (Enabled)
    WREG_B      (0xBF000000 + (0x100B82 << 1)), 0x00        #//Set CLK_GOPG2 to clk_odclk_p (Enabled)
    WREG_B      (0xBF000000 + (0x100B82 << 1) + 1), 0x04    #//Set CLK_GOPD to CLK_ODCLK (Enabled)
    WREG_B      (0xBF000000 + (0x100B84 << 1)), 0x00        #//Set CLK_GOPG3 to clk_odclk_p (Enabled)
    WREG_B      (0xBF000000 + (0x100B86 << 1)), 0x00        #//Set CLK_PSRAM0 (Enabled)
    WREG_B      (0xBF000000 + (0x100B86 << 1) + 1), 0x00    #//Set CLK_PSRAM1 (Enabled)

                                                            #//GE
    WREG_B      (0xBF000000 + (0x100B90 << 1)), 0x00        #//Set CLK_GE to 170MHz (Enabled)

                                                            #//MVOP
    WREG_B      (0xBF000000 + (0x100B98 << 1)), 0x01        #//Set CLK_DC0 to synchronous mode (Disabled)
    WREG_B      (0xBF000000 + (0x100B98 << 1) + 1), 0x01    #//Set CLK_DC1 to synchronous mode (Disabled)
    WREG_B      (0xBF000000 + (0x100B9A << 1)), 0x01        #//Set CLK_SUB_DC0 to synchronous mode (Disabled)
    WREG_B      (0xBF000000 + (0x100B9A << 1) + 1), 0x01    #//Set CLK_SUB_DC1 to synchronous mode (Disabled)

                                                            #//EMAC
    WREG_B      (0xBF000000 + (0x100BC0 << 1)), 0x00        #//Set CLK_EMAC_AHB to 123MHz (Enabled)
    WREG_B      (0xBF000000 + (0x100BC0 << 1) + 1), 0x00    #//Set CLK_EMAC_RX to CLK_EMAC_RX_in (25MHz) (Enabled)
    WREG_B      (0xBF000000 + (0x100BC2 << 1)), 0x00        #//Set CLK_EMAC_TX to CLK_EMAC_TX_IN (25MHz) (Enabled)
#// WREG_B      (0xBF000000 + (0x100BC2 << 1) + 1), 0x00    #//Set CLK_EMAC_TX_REF to CLK_EMAC_TX_IN (25MHz) (Enabled)
#// WREG_B      (0xBF000000 + (0x100BC4 << 1)), 0x00        #//Set CLK_EMAC_RX_REF to CLK_EMAC_RX_IN (50MHz) (Enabled)

                                                            #//NAND Flash
    WREG_B      (0xBF000000 + (0x100BC8 << 1)), 0x0C        #//Set CLK_NFIE to 32MHz (Enabled)
    WREG_B      (0xBF000000 + (0x100BCC << 1)), 0x09        #//Set CLK_ONIF to 27MHz (Disabled)

                                                            #//MPIF
    WREG_B      (0xBF000000 + (0x100BD0 << 1)), 0x01        #//Set CLK_MPIF to 74MHz (Disabled)

                                                            #//Scaler
    WREG_B      (0xBF000000 + (0x100BA2 << 1)), 0x04        #//Set CLK_FICLK_F1 to CLK_FCLK (Enabled)
    WREG_B      (0xBF000000 + (0x100BA2 << 1) + 1), 0x04    #//Set CLK_FICLK_F2 to CLK_FCLK (Enabled)
    WREG_B      (0xBF000000 + (0x100BA4 << 1)), 0x04        #//Set CLK_FODCLK to XTAL (Enabled)
    WREG_B      (0xBF000000 + (0x100BA4 << 1) + 1), 0x1C    #//Set CLK_VCLK to XTAL (Enabled)
    WREG_B      (0xBF000000 + (0x100BA6 << 1)), 0x1C        #//Set CLK_ODCLK to LPLL output clock (Enabled)
    WREG_B      (0xBF000000 + (0x100BA6 << 1) + 1), 0x1C    #//Set CLK_BT656 to LPLL output clock (Enabled)
    WREG_B      (0xBF000000 + (0x100BA8 << 1)), 0x20        #//Set CLK_IDCLK_F0 to XTAL (Enabled)
    WREG_B      (0xBF000000 + (0x100BA8 << 1) + 1), 0x20    #//Set CLK_IDCLK_F1 to XTAL (Enabled)
    WREG_B      (0xBF000000 + (0x100BAA << 1)), 0x20        #//Set CLK_IDCLK_F2 to XTAL (Enabled)

                                                            #//MOD
    WREG_B      (0xBF000000 + (0x100BAE << 1)), 0x00		#//Set CLK_FIFO_MINI to FIFO_CLK (Enabled)

                                                            #//LPLL
    WREG_B      (0xBF000000 + (0x100BB0 << 1)), 0x01        #//Set CLK_LPLL_SYN to 432MHz (Enabled)

                                                            #//VIF
    WREG_B      (0xBF000000 + (0x10331A << 1)), 0x01        #//Set CLK_VIFDBB_DAC to clk_dmplldiv10 (Disabled)
    WREG_B      (0xBF000000 + (0x10331A << 1) + 1), 0x01    #//Set CLK_VIFDBB_VDAC to clk_dmplldiv10 (Disabled)

                                                            #//DEMOD
    WREG_B      (0xBF000000 + (0x10331E << 1)), 0x11        #//Set CLK_DMDMCU to 108MHz (Disabled)

    WREG_B      (0xBF000000 + (0x103314 << 1)), 0x01        #//Set CLK_DVBTC_ADC to clk_demod_adcout (Disabled)
    WREG_B      (0xBF000000 + (0x103300 << 1)), 0x11        #//Set CLK_ATSC_DVB_DIV divider factor to 0x11
    WREG_B      (0xBF000000 + (0x103300 << 1) + 1), 0x05    #//Set CLK_ATSC_DVB_DIV to clk_dmplldiv2
    WREG_B      (0xBF000000 + (0x103308 << 1)), 0x01        #//Set CLK_ATSC_TS to clk_atsc_dvb_div (Disabled)
    WREG_B      (0xBF000000 + (0x103308 << 1) + 1), 0x05    #//Set CLK_DVBTC_TS to 62MHz (Disabled)

    WREG_B      (0xBF000000 + (0x10326E << 1)), 0x40        #//Patch for 2.5V MOD Setting

    jr           ra
    nop

    .size       BootRomInitClock,.-BootRomInitClock
    .end        BootRomInitClock

