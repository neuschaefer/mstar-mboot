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

	WREG_B 0xBF201600 0x10      // turn xtal clk  #4 = 1 (CKg_RIU must be "1" in VIF input)
    WREG_B 0xBF201604 0x07      // SRAM bist test clk 7:xtal, 6:54M, 5:62M 4:72M 3:86M 2:108M 1:123M 0:144M
          		  			 	// Dig_top_pm mcu clock
    WREG_B 0xBF001E80 0x00      // step 1/2:set clk_mcu_pm to 108M
    WREG_B 0xBF001E80 0x80      // step 2/2:set clk_mcu_pm to 108M
          		  			 	// dig_top
    WREG_B 0xBF201641 0x00      //turn ckg_mcu for turn riu_bridge,db_bus....,db_bus....
    WREG_B 0xBF201640 0x01      //change to fast clock
          		  			 	// clk_aeon
    WREG_B 0xBF201648 0x00      // aeon clk aeon to 216Mhz
    WREG_B 0xBF201648 0x80      // change to fast clock
          		   			 	// clk_R2
    WREG_B 0xBF201649 0x08      // aeon clk r2 to 216Mhz
    WREG_B 0xBF201649 0x28      // change to fast clock
          		  			 	// clk_UART
    WREG_B 0xBF20164D 0x0C      // uart0 clk to 123Mhz
    WREG_B 0xBF201650 0x0C      // uart1 clk to 123Mhz
          		  			 	// clk_spi
          		  			 	// Dig_top_pm clk_spi
    #//WREG_B 0xBF001E81 0x14      // clk spi to 72Mhz
    #//WREG_B 0xBF001E81 0x54      // change to fast clock
          		  			 	// dig_top clk_spi
    WREG_B 0xBF201658 0x14      // clk spi to 72Mhz
    WREG_B 0xBF201658 0x34      // change to fast clock
          		  			 	// clk_pcm
    WREG_B 0xBF201668 0x00      // set pcm clk to 27Mhz,  pcmcia
          		  			 	// clk_jtag
    WREG_B 0xBF201669 0x00      // turn tck clk on
          		  			 	// MIU relative
    WREG_B 0xBF201679 0x01      // MPLL syn = 432MHz

    WREG_B 0xBF20167C 0x18      // CLK_MIU = 246MHz

    WREG_B 0xBF2017F8 0x01      // reg_clkgen0_reserved0 ??
          		  			 	// clk_vd
    WREG_B 0xBF201680 0x00      //clk vd_sel, 0: vd_adc_clk(Y), 1: adc_clk(RGB)
    WREG_B 0xBF201681 0x00      //ckg_vd= vd_sel
          		  			 	// clk_vd mcu
    WREG_B 0xBF201684 0x10      //ckg_vdmcu = 108Mhz , need fine tune in demod
    WREG_B 0xBF201685 0x04      //clk vd_200=216Mhz
          		  			 	// clk_mail
    WREG_B 0xBF201688 0x0c      //clk mail box0 =xtal  <<hk51 <--mail box 0--> aeon
    WREG_B 0xBF201689 0x0c      //clk mail box1 =xtal  <<hk51 <--mail box 1--> aeon
    WREG_B 0xBF20168C 0x00      //tur on vd2x
    WREG_B 0xBF20168D 0x00      //tur on vd_32fsc
          		  			 	// clk_ve
    WREG_B 0xBF201690 0x00      //ckg_Ve=27M, remove
    WREG_B 0xBF201691 0x00      //ckg_Vedec=27M, remove
    WREG_B 0xBF201694 0x0c      //ckg_Ve_in=clk_DC0, remove
    WREG_B 0xBF201698 0x04      //clk_daca2=VD_clk
          		  			 	// clk_dscb2
    WREG_B 0xBF201699 0x04      //clk_dscb2=VD_CLK
          		  			 	// clk_tsp
    WREG_B 0xBF2016A0 0x08      //clk_ts0=demode, CLK_TS1= gating
    WREG_B 0xBF2016A8 0x00      //CLK_TSP = 172M
    WREG_B 0xBF2016A9 0x00      //Ckg_stc0 = stc0_sync_output
    WREG_B 0xBF2016C0 0x00      //ckg_vd_mheg5 =160Mhz
    WREG_B 0xBF2016C4 0x08      //ckg_HVD =144Mhz
    WREG_B 0xBF2016D4 0x0c      //ckg_jpg=160M  0:72m 4:108m c:123m c:160m
          		  			 	// clk_mvdxx
    WREG_B 0xBF2016E4 0x00      //mvd_clk=144m ON
    WREG_B 0xBF2016E5 0x00      //mvd2_clk=172m ON
    WREG_B 0xBF2016E8 0x00      //mvd_chroma ON
    WREG_B 0xBF2016E9 0x00      //mvd_luma_a ON
    WREG_B 0xBF2016EC 0x00      //mvd_luma_b ON
    WREG_B 0xBF2016ED 0x00      //mvd_luma_c ON
    WREG_B 0xBF2016F0 0x00      //mvd_rmem ON
    WREG_B 0xBF2016F1 0x00      //mvd_rmem1 ON
          		  			 	// clk_gop and clk_ge
    WREG_B 0xBF201700 0x00      //clk_gop_0 ==odclk_p
    WREG_B 0xBF201701 0x00      //clk_gop_1 ==odclk_p
    WREG_B 0xBF201705 0x01      //gating first, ((clk_gopd (DWIN) = CLK_ODCLK))
    WREG_B 0xBF20170C 0x00      //psram0=on, select gop0
    WREG_B 0xBF20170D 0x00      //psram1=on, select gop0
    WREG_B 0xBF201720 0x00      //ckg_ge=216M
          		  			 	// clk_dc
    WREG_B 0xBF201730 0x00      //ckg_dc0=synchronous mode      #TBD: what is synchronous mode?
    WREG_B 0xBF201731 0x00      //ckg_dc1=synchronous mode
          		  			 	// SC
    WREG_B 0xBF201745 0x04      //main_window fclk_f2, and select fclk
    WREG_B 0xBF201748 0x04      //main_window ficlk2_f2, and select fclk
    WREG_B 0xBF201749 0x00      //flck=170M
    WREG_B 0xBF20174C 0x1c      //odclk (output pixel clock) = LPLL
    WREG_B 0xBF20174D 0x1c      //bt656 = LPLL
          		  			 	// clk_mod
    WREG_B 0xBF206400 0x00      //switch bank
    WREG_B 0xBF206481 0x00      //dot_mini_* clk= clk_lpll_buf
    WREG_B 0xBF20175C 0x00      //fifo mmini = LPLL   //LVDS   fifo_clk=mini_lvds         #TBD: not found (the same as T3, by jeff)
    WREG_B 0xBF2066C4 0x00      //ckg_tx_mod
          		  			 	// clk_vif
    WREG_B 0xBF206628 0x00      // reg_ckg_dvbtc_adc@0x0a[3:0] : ADC_CLK
    WREG_B 0xBF206629 0x01      // reg_ckg_dvbtc_innc@0x0a[11:8]
    WREG_B 0xBF206614 0x00      // reg_ckg_atsc_adcd_sync@0x05[3:0] : ADCCLK
    WREG_B 0xBF206615 0x00
    WREG_B 0xBF206634 0x04      // reg_ckg_vifdbb_dac@0x0d[3:0] : MPLLDIV10/2=43MHz
    WREG_B 0xBF206635 0x04      // reg_ckg_vifdbb_vdac@0x0d[11:8]: MPLLDIV10/2=43MHz
    WREG_B 0xBF206638 0x00      // reg_ckg_vifdbb_43m@0x0e[3:0] : MPLLDIV10/2=43MHz
    WREG_B 0xBF206639 0x00      // reg_ckg_vifdbb_144m@0x0e[11:8]: ADC_CLKOUT=144MHz
          		  			 	// ckg_idclk_lpll
    WREG_B 0xBF2066C8 0x04      // reg_ckg_idclk_lpll and select clk_idclk2
    WREG_B (0xBF000000 + (0x100B4E << 1)), 0x24 //reg_ckg_bdma
                                                      #//EMAC
    WREG_B (0xBF000000 + (0x100BC0 << 1)), 0x00       #//Set CLK_EMAC_AHB to 123MHz (Enabled)
    WREG_B (0xBF000000 + (0x100BC0 << 1) + 1), 0x00   #//Set CLK_EMAC_RX to CLK_EMAC_RX_in (25MHz) (Enabled)
    WREG_B (0xBF000000 + (0x100BC2 << 1)), 0x00       #//Set CLK_EMAC_TX to CLK_EMAC_TX_IN (25MHz) (Enabled)
    WREG_B (0xBF000000 + (0x100BC2 << 1) + 1), 0x00   #//Set CLK_EMAC_TX_REF to CLK_EMAC_TX_IN (50MHz) (Enabled)
    WREG_B (0xBF000000 + (0x100BC4 << 1)), 0x00       #//Set CLK_EMAC_RX_REF to CLK_EMAC_RX_IN (50MHz) (Enabled)

    jr           ra
    nop

    .size       BootRomInitClock,.-BootRomInitClock
    .end        BootRomInitClock

