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
#define REG_ADDR_BASE                   0xBF000000

    .text
	.set    	noreorder
    .global     BootRomInitClock
    .ent        BootRomInitClock

BootRomInitClock:
    # swch 4
    
    WREG (REG_ADDR_BASE + (0x000e40 <<1 )) , 0x1008     # clk_mcu = xtal (step 1/2)
                                                    # clk_spi = xtal (step_1/2)
#<<CLKGEN0>>
    WREG (REG_ADDR_BASE + (0x100b02 <<1 )) , 0x0007     # SRAM bist test clk 7:xtal, 6:62M, 5:86M 4:108M 3:123M 2:144M 1:172M 0:216M
#MCU
    WREG (REG_ADDR_BASE + (0x100b20 <<1 )) , 0x0400     # clk_mcu = 172M (step 1/2)
    WREG (REG_ADDR_BASE + (0x100b20 <<1 )) , 0x0401     # clk_mcu = 172M (step 2/2)

    WREG (REG_ADDR_BASE + (0x100b2c << 1)) , 0x0000     # select 216M for clk_spi
    WREG (REG_ADDR_BASE + (0x100b2c << 1)) , 0x0020     #switch to 216M

    WREG (REG_ADDR_BASE + (0x101d1e <<1 )) , 0x0021     # clk_ocp ratio and change
    WREG (REG_ADDR_BASE + (0x100b22 <<1 )) , 0x0000     # clk_ocp on
                                                    # clk_mips = 500M (step 1/2) (MIPSPLL_VCO)
    WREG (REG_ADDR_BASE + (0x100b22 <<1 )) , 0x8000     # clk_mips = 500M (step 2/2) (MIPSPLL_VCO)

#MIU
    WREG(REG_ADDR_BASE + (0x100b3c << 1))  , 0x0100     # clk_mpll_syn = 432M (for VEPLL  0: 216M, 1:432M)
    WREG(REG_ADDR_BASE + (0x100b3e << 1))  , 0x000c     # clk_miu = 216M  clk_miu_rec = 93K (clk_xtal/128)
    WREG(REG_ADDR_BASE + (0x100bfc << 1))  , 0x0001     # clk_ddr_syn = 432M (for MEMPLL  0: 216M, 1:432M)
#NAND
    WREG(REG_ADDR_BASE + (0x100bc8 <<1 ))  , 0x002C     # clk_fice = 86M

#CA
    WREG(REG_ADDR_BASE + (0x103348 <<1 ))  , 0x0000     # clk_nsk = 123M
                                                    # clk_sm_ca = 27M, clk_sm_ca2 = 27M
    WREG(REG_ADDR_BASE + (0x000e40 <<1 ))  , 0x5088     # clk_mcu = 170M set spi clock to high speed for fast mode ,must after awhile for spi command address change, or the command with speed will chaos
        
    #clk_uartx
    WREG(REG_ADDR_BASE + (0x100b28 << 1)), 0x0000       #clk_uart1 = 172M (step_1/2) clk_uart2 = 172M (step_1/2)
    WREG(REG_ADDR_BASE + (0x100b26 << 1)), 0x0c06       #clk_uart0 = 172MHz  clk_uart1 = 172M (step_2/2)  clk_uart2 = 172M (step_2/2)
    WREG(REG_ADDR_BASE + (0x100b2a << 1)), 0x0000       #clk_uart3 = 172MHz
    
    #clk_fuart
    WREG(REG_ADDR_BASE + (0x100b2e << 1)), 0x0008       #clk_fuart = 172MHz
    
    #clk_iicx
    WREG(REG_ADDR_BASE + (0x100b60 << 1)), 0x0000       #clk_miic2 = 72MHz clk_miic1 = 72MHz clk_miic0 = 72MHz
    
    #TCK
    WREG(REG_ADDR_BASE + (0x101e08 << 1)), 0x0010       #CLK_TCK_IN from PAD_FUART_TX
    WREG(REG_ADDR_BASE + (0x100b34 << 1)), 0x0000       #clk_tck = CLK_TCK_IN
    
    #VE
    WREG(REG_ADDR_BASE + (0x100b48 << 1)), 0x0800       # clk_ve = 27M  clk_vedac = 108M
    WREG(REG_ADDR_BASE + (0x100b4a << 1)), 0x001c       # clk_ve_in = 27M (clk_odclk)
    
    #TSP
    WREG(REG_ADDR_BASE + (0x101e04 << 1)), 0x0001       # CLK_TS0_IN from PAD_TS0_CLK
    WREG(REG_ADDR_BASE + (0x100b50 << 1)), 0x0000       # clk_ts0 = CLK_TS0_IN clk_ts1 = CLK_TS0_IN  clk_tsp = 144M
    WREG(REG_ADDR_BASE + (0x100b54 << 1)), 0x0000       # clk_tsp = 144M clk_stc0 = 27M (STC0_SYNTH_OUT)
    
    #VD_MHEG5
    WREG(REG_ADDR_BASE + (0x100b60 << 1)), 0x0000       #clk_vd_mheg5 160MHz
    
    #HVD
    WREG(REG_ADDR_BASE + (0x100b62 << 1)), 0x0004       #clk_hvd 160MHz
    
    #JPD
    WREG(REG_ADDR_BASE + (0x100b6a << 1)), 0x0008       # ckg_jpg = 144M (0:72m 4:108m 8:144m c:192m)
    
    #MVD
    WREG(REG_ADDR_BASE + (0x100b70 << 1)), 0x0000       #mvd_syn off
    WREG(REG_ADDR_BASE + (0x100b72 << 1)), 0x0000       #clk_mvd = 144M clk_mvd2 = 144M
    
    WREG(REG_ADDR_BASE + (0x100b74 << 1)), 0x0000       #clk_mvd_chroma on clk_mvd_luma_a on
    WREG(REG_ADDR_BASE + (0x100b76 << 1)), 0x0000       #clk_mvd_luma_b on clk_mvd_luma_c on
    WREG(REG_ADDR_BASE + (0x100b78 << 1)), 0x0000       #clk_mvd_rmem on   clk_mvd_rmem1 on
    
    #GOP
    WREG(REG_ADDR_BASE + (0x100b80 << 1)), 0x0000       # clk_gopg0 = 27M (clk_odclk) clk_gopg1 = 27M (clk_odclk)
    WREG(REG_ADDR_BASE + (0x100b82 << 1)), 0x0018       # clk_gopmix = 27M (clk_ve) clk_gopd = 27M (clk_odclk)
    WREG(REG_ADDR_BASE + (0x100b84 << 1)), 0x0004       # clk_gopg2 = 192M (clk_idclk)  clk_gopg3 = 27M (clk_odclk)
    WREG(REG_ADDR_BASE + (0x100b86 << 1)), 0x0000       # clk_psram0 on
    
    #GE
    WREG(REG_ADDR_BASE + (0x100b90 << 1)), 0x000c       # clk_ge = 144M
    
    #STB_DC
    WREG(REG_ADDR_BASE + (0x100b98 << 1)), 0x0018       # clk_dc0 = 192M
    
    #SC
    WREG(REG_ADDR_BASE + (0x100ba2 << 1)), 0x0400       # clk_ficlk = 192M (clk_fclk)
    WREG(REG_ADDR_BASE + (0x100ba4 << 1)), 0x1000       # clk_flck = 192M
    WREG(REG_ADDR_BASE + (0x100ba6 << 1)), 0x000c       # clk_odclk = 27M (CLK_OUT_DAC/8) (output pixel clock)
    WREG(REG_ADDR_BASE + (0x100baa << 1)), 0x000c       # clk_idclk = 192M (clk_dc0)
    WREG(REG_ADDR_BASE + (0x100bb0 << 1)), 0x0c00       # clk_hdgen = 27M (clk_odlck)  clk_hdgen_fir = 27M (CLK_OUT_DAC/8)
    WREG(REG_ADDR_BASE + (0x100bb2 << 1)), 0x000c       # clk_dac1 = 108M (clk_vedac) (SD)  clk_dac2 = 27M (clk_hdgen_fir) (HD)
    WREG(REG_ADDR_BASE + (0x100bb4 << 1)), 0x000c       # clk_dcs = 27M (CLK_OUT_DAC/8)  clk_dcs27 = 27M
    
    #HDMITX
    WREG(REG_ADDR_BASE + (0x103350 << 1)), 0x0000       #clk_hdmitx = 27M (clk_odclk)
    
    #BDMA
    WREG_B(REG_ADDR_BASE + (0x100b5e << 1)+1), 0x04     #clk_bdma, change to clk miu

    jr           ra
    nop

    .size       BootRomInitClock,.-BootRomInitClock
    .end        BootRomInitClock

