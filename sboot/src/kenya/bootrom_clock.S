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
#//swch 4


#// IP: EJTAG
    WREG_B (REG_ADDR_BASE + (0x101e08 <<1 )) , 0x10   #// CLK_TCK_IN from PAD_SM0_RST
    WREG_B (REG_ADDR_BASE + (0x100b35 <<1 )-1) , 0x00   #// clk_tck = CLK_TCK_IN

#// IP: HEMCU
    WREG (REG_ADDR_BASE + (0x101d1e <<1 )) , 0x0020
    WREG (REG_ADDR_BASE + (0x101d1e <<1 )) , 0x0021
    WREG (REG_ADDR_BASE + (0x100b22 <<1 )) , 0x0000   #// clk_ocp on
                                                  #// clk_mips = 792M (step 1/2) (MIPSPLL_VCO)
    WREG (REG_ADDR_BASE + (0x100b22 <<1 )) , 0x8000   #// clk_mips = 792M (step 2/2) (MIPSPLL_VCO)

#// IP: MCU
    WREG (REG_ADDR_BASE + (0x100b20 <<1 )) , 0x0400   #// clk_mcu = 172M (step 1/2)
    WREG (REG_ADDR_BASE + (0x100b20 <<1 )) , 0x0401   #// clk_mcu = 172M (step 2/2)



    WREG (REG_ADDR_BASE + (0x100b26 <<1 )) , 0x0c06   #// clk_uart0 = 123M
    WREG (REG_ADDR_BASE + (0x100b2a <<1 )) , 0x000c   #// clk_uart3 = 123M


    WREG (REG_ADDR_BASE + (0x100b2c <<1 )) , 0x0010   #// clk_spi = 54M (step_1/2)
    WREG (REG_ADDR_BASE + (0x100b2c <<1 )) , 0x0030   #// clk_spi = 54M (step_2/2)

    WREG (REG_ADDR_BASE + (0x100b2e <<1 )) , 0x0100   #// clk_fuart = 54M
                                                  #// uart synthesizer enable

    WREG (REG_ADDR_BASE + (0x100b60 <<1 )) , 0x0000   #// ckg_vd_mheg5 = 160M

    WREG (REG_ADDR_BASE + (0x103360 <<1 )) , 0x0000   #// clk_miic0  clk_miic1 = 72M  clk_miic2 = 72M
#// CLKGEN_PM
    WREG (REG_ADDR_BASE + (0x000e40 <<1 )) , 0x1008   #// clk_mcu = 172M (step 1/2)
                                                  #// clk_spi = 54M (step_1/2)
    WREG (REG_ADDR_BASE + (0x000e40 <<1 )) , 0x5088   #// clk_mcu = 172M (step 2/2)
                                                  #// clk_spi = 54M (step_2/2)



#// IP: MIU
    WREG (REG_ADDR_BASE + (0x100b3c <<1 )) , 0x0100   #// clk_mpll_syn = 432M (for VEPLL  0: 216M, 1:432M)
    WREG (REG_ADDR_BASE + (0x100b3e <<1 )) , 0x0018   #// clk_miu = 288M
                                                  #// clk_miu_rec = 93K (clk_xtal/128)
    WREG (REG_ADDR_BASE + (0x100bfc <<1 )) , 0x0001   #// clk_ddr_syn = 432M (for MEMPLL  0: 216M, 1:432M)


#// IP: VE
    WREG (REG_ADDR_BASE + (0x100b48 <<1 )) , 0x0800   #// clk_ve = 27M
                                                  #// clk_vedac = 108M
    WREG (REG_ADDR_BASE + (0x100b4a <<1 )) , 0x001c   #// clk_ve_in = 27M (clk_odclk)

#// IP: HDGEN, DCS27
    WREG (REG_ADDR_BASE + (0x100bb4 <<1 )) , 0x0001   #// clk_dcs27 = 27M



#// IP: TSP
    WREG (REG_ADDR_BASE + (0x101e04 <<1 )) , 0x0001   #// CLK_TS0_IN from PAD_TS0_CLK
    WREG (REG_ADDR_BASE + (0x100b50 <<1 )) , 0x0000   #// clk_ts0 = CLK_TS0_IN
                                                  #// clk_ts1 = CLK_TS0_IN
    WREG (REG_ADDR_BASE + (0x100b54 <<1 )) , 0x0000   #// clk_tsp = 144M
                                                  #// clk_stc0 = 27M (STC0_SYNTH_OUT)


#// IP: HVD
    WREG (REG_ADDR_BASE + (0x100b62 <<1 )) , 0x0004   #// ckg_HVD = 160M
    WREG (REG_ADDR_BASE + (0x100b64 <<1 )) , 0x0004   #// ckg_VP8 = 172M

#// IP: JPD
    WREG (REG_ADDR_BASE + (0x100b6a <<1 )) , 0x0008   #// ckg_jpg = 144M (0:72m 4:108m 8:144m c:192m)


#// IP: MVD
    WREG (REG_ADDR_BASE + (0x100b70 <<1 )) , 0x0000   #// mvd_syn off

    WREG (REG_ADDR_BASE + (0x100b72 <<1 )) , 0x0400   #// clk_mvd = 160M from UTMI
                                                  #// clk_mvd2 = 144M, no use

    WREG (REG_ADDR_BASE + (0x100b74 <<1 )) , 0x0000   #// clk_mvd_chroma on
                                                  #// clk_mvd_luma_a on
    WREG (REG_ADDR_BASE + (0x100b76 <<1 )) , 0x0000   #// clk_mvd_luma_b on
                                                  #// clk_mvd_luma_c on
    WREG (REG_ADDR_BASE + (0x100b78 <<1 )) , 0x0000   #// clk_mvd_rmem on
                                                  #// clk_mvd_rmem1 on


#// IP: GOP
    WREG (REG_ADDR_BASE + (0x100b80 <<1 )) , 0x0000   #// clk_gopg0 = 27M (clk_odclk)
                                                  #// clk_gopg1 = 27M (clk_odclk)
    WREG (REG_ADDR_BASE + (0x100b82 <<1 )) , 0x0018   #// clk_gopmix = 27M (clk_ve)
                                                  #// clk_gopd = 27M (clk_odclk)
    WREG (REG_ADDR_BASE + (0x100b84 <<1 )) , 0x0004   #// clk_gopg2 = 192M (clk_idclk)
                                                  #// clk_gopg3 = 27M (clk_odclk)

    WREG (REG_ADDR_BASE + (0x100b86 <<1 )) , 0x0000   #// clk_psram0 on


#// IP: GE
    WREG (REG_ADDR_BASE + (0x100b90 <<1 )) , 0x0000   #// clk_ge = clk_miu


#// IP: STB_DC
    WREG (REG_ADDR_BASE + (0x100b98 <<1 )) , 0x0018   #// clk_dc0 = 192M


#// IP: SC
    WREG (REG_ADDR_BASE + (0x100ba2 <<1 )) , 0x0400   #// clk_ficlk = 192M (clk_fclk)
    WREG (REG_ADDR_BASE + (0x100ba4 <<1 )) , 0x1000   #// clk_flck = 192M
    WREG (REG_ADDR_BASE + (0x100ba6 <<1 )) , 0x000c   #// clk_odclk = 27M (CLK_OUT_DAC/8) (output pixel clock)
    WREG (REG_ADDR_BASE + (0x100baa <<1 )) , 0x000c   #// clk_idclk = 192M (clk_dc0)
    WREG (REG_ADDR_BASE + (0x100bb0 <<1 )) , 0x0c00   #// clk_hdgen = 27M (clk_odlck)
                                                  #// clk_hdgen_fir = 27M (CLK_OUT_DAC/8)
    WREG (REG_ADDR_BASE + (0x100bb2 <<1 )) , 0x000c   #// clk_dac1 = 108M (clk_vedac) (SD)
                                                  #// clk_dac2 = 27M (clk_hdgen_fir) (HD)
    WREG (REG_ADDR_BASE + (0x100bb4 <<1 )) , 0x000c   #// clk_dcs = 27M (CLK_OUT_DAC/8)
                                                  #// clk_dcs27 = 27M


#// IP: EMAC
    WREG (REG_ADDR_BASE + (0x100bc0 <<1 )) , 0x0000   #// clk_emac_ahb = 123M
                                                  #// clk_emac_rx = CLK_EMAC_RX_IN
    WREG (REG_ADDR_BASE + (0x100bc2 <<1 )) , 0x0000   #// clk_emac_tx = CLK_EMAC_TX_IN
                                                  #// clk_emac_rx_ref = CLK_EMAC_RX_IN
#//WREG 0x100bc4 0x0000                            #// clk_emac_tx_ref = CLK_EMAC_TX_IN

#// IP: SECEMAC
    WREG (REG_ADDR_BASE + (0x103364 <<1 )) , 0x0400   #// clk_secemac_ahb = 123M
                                                  #// clk_secemac_rx = CLK_SECEMAC_MMI_RX
    WREG (REG_ADDR_BASE + (0x103366 <<1 )) , 0x0004   #// clk_secemac_tx = CLK_SECEMAC_MMI_TX
                                                  #// clk_secemac_rx_ref = PAD
    WREG (REG_ADDR_BASE + (0x103368 <<1 )) , 0x0000   #// clk_secemac_tx_ref = PAD


#// IP: NAND
    WREG (REG_ADDR_BASE + (0x100bc8 <<1 )) , 0x0028   #// clk_fice = 54M


#// IP: SM CA
    WREG (REG_ADDR_BASE + (0x103348 <<1 )) , 0x0000   #// clk_nsk = 123M
                                                  #// clk_sm_ca = 27M, clk_sm_ca2 = 27M

    WREG (REG_ADDR_BASE + (0x100b28 <<1 )) , 0x0000   #// clk_uart1 = 172M (step_1/2)
                                                  #// clk_uart2 = 172M (step_1/2)

                                                  #// clk_uart1 = 172M (step_2/2)
                                                  #// clk_uart2 = 172M (step_2/2)

#// IP: HDMITX
#//WREG -w 0x103350 0x0000                        #// clk_hdmitx = 27M (clk_odclk)
    WREG_B (REG_ADDR_BASE + (0x1130b0 <<1 )) , 0x02
    WREG_B (REG_ADDR_BASE + (0x1130b1 <<1 )-1) , 0x00
    WREG_B (REG_ADDR_BASE + (0x113038 <<1 )) , 0x00
    WREG_B (REG_ADDR_BASE + (0x113039 <<1 )-1) , 0x00   #// clock sel

    WREG_B (REG_ADDR_BASE + (0x11303a <<1 )) , 0x00
    WREG_B (REG_ADDR_BASE + (0x11303b <<1 )-1) , 0x00   #// clock inv

    WREG_B (REG_ADDR_BASE + (0x11303c <<1 )) , 0xff
    WREG_B (REG_ADDR_BASE + (0x11303d <<1 )-1) , 0xff   #// clock enable


    WREG_B (REG_ADDR_BASE + (0x11303e <<1 )) , 0x00
    WREG_B (REG_ADDR_BASE + (0x11303f <<1 )-1) , 0x00   #// clock external

    WREG_B (REG_ADDR_BASE + (0x113202 <<1 )) , 0x10
    WREG_B (REG_ADDR_BASE + (0x113203 <<1 )-1) , 0x00   #// video clock


#// IP: FSYNC
    WREG (REG_ADDR_BASE + (0x100b48 <<1 )) , 0x1004   #//[12:8]reg_ckg_vedac = syn_pll_clkout_dr_buf
                                                  #//[03:0]reg_ckg_ve = syn_pll_clkout_dr_div4_buf

#// IP: MFE
    WREG (REG_ADDR_BASE + (0x103320 <<1 )) , 0x000c   #// clk_mfe = 192MHz

#// IP: GPD
    WREG (REG_ADDR_BASE + (0x103354 <<1 )) , 0x0000   #// ckg_gpd = 216M

#// IP: BDMA
#// CLK SRC switch
    WREG_B (REG_ADDR_BASE + (0x100b5f <<1 )-1) , 0x04   #// [13:10]BDMA clock source, 0001:  clk_miu_p

    jr           ra
    nop

    .size       BootRomInitClock,.-BootRomInitClock
    .end        BootRomInitClock

