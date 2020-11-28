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
    .global     BootRomInitPll
    .ent        BootRomInitPll

BootRomInitPll:

    #//adc_atop
    WREG_B      0xBF204A1C, 0x3F        #//Soft-reset for DAC/ATOP/PLLB/ADCB/PLLA/ADCA
    WREG_B      0xBF204A1C, 0x00

    WREG        0xBF204A10, 0x0000      #//Power-on for related adc_atop IPs
    WREG        0xBF204A14, 0x0000
    WREG        0xBF204A18, 0x0000
    WREG        0xBF204AFC, 0x0030

    WREG        0xBF204AFC, 0x0030      #//Enable SOG MUX
    WREG_B      0xBF204B20, 0x08        #//Enable IDAC (Ch1)
    WREG_B      0xBF204B40, 0x00        #//Enable CVBSO1

    #//Module: dvi_atop (0x1109)
    WREG        0xBF221218, 0x0000      #//Relase soft-reset for DVI/HDMI/HDCP blocks
    WREG        0xBF221380, 0x0000      #//Power-on for DVI/HDMI/HDCP blocks
    WREG        0xBF2213A4, 0x0000      #//Power-on for DVT port 2
    WREG        0xBF22120C, 0x0000      #//Enable clock for related dvi_atop IPs

    WREG        0xBF22139C, 0x4000      #//Port A/C: ENAUTO
    WREG        0xBF221394, 0x3000      #//Port A/C: TEST_CMP[1:0]
    WREG		0xBF2213FC, 0x0000      #//Power-on DVI DPLPHI/DPLPHQ

    #//Module: dvi_atop1 (0x1132)
    WREG        0xBF226418, 0x0000      #//Enable clock for related dvi_atop_p1 IPs
    WREG        0xBF226580, 0x0000      #//Power-on for related dvi_atop_p1 IPs

    WREG        0xBF22659C, 0x4000      #//Port B: ENAUTO
    WREG        0xBF226594, 0x3000      #//Port B: TEST_CMP[1:0]
    WREG        0xBF2265D0, 0x0000      #//Power-on DVI DPLPHI/DPLPHQ Port 1

	#//Module: dvi_atop2 (0x1134)
    WREG        0xBF226818, 0x0000      #//Enable clock for related dvi_atop_p2 IPs
    WREG        0xBF226980, 0x0000      #//Power-on for related dvi_atop_p2 IPs

    WREG        0xBF22699C, 0x4000      #//Port D: ENAUTO
    WREG        0xBF226994, 0x3000      #//Port D: TEST_CMP[1:0]
    WREG        0xBF2269D0, 0x0000      #//Power-on DVI DPLPHI/DPLPHQ Port 2

    #//Module: pm_sleep (0x000E)
    WREG        0xBF001D28, 0x0000      #//Power-on dvi_atop in PM_SLEEP
    WREG        0xBF001D2C, 0x0000

    #//Module: chiptop (0x101E)
    WREG_B      0xBF203C70, 0x00        #//Power-on for PD_3P3_1, PD_3P3_0 and PD_3P3_USB1

	#//Module: ana_misc (0x110C)
    WREG_B      0xBF221805, 0x00      
    WREG_B      0xBF221810, 0x01
    WREG_B      0xBF221800, 0x44
    WREG_B      0xBF221845, 0x00      
                                        
    #//Set MIPS to 800MHZ
    WREG_B      0xBF22184C, (CPU_CLOCK / 12)
    WREG_B      0xBF221854, 0x08
  
  #//================================================================================================
	#//Module: usb0 (0x1007)
	  WREG_B      (0xBF000000 + (0x100700 << 1)), 0x0a        #//Disable MAC initial suspend, Reset UHC
	  WREG_B      (0xBF000000 + (0x100700 << 1)), 0x28        #//Release UHC reset, enable UHC and OTG XIU function

  #//================================================================================================
	#//Module: utmi (0x103A)
    WREG        (0xBF000000 + (0x103AA2 << 1)), 0x2088			#// PLL_TEST[30:28]:
                                                            #// PLL_TEST[23] CLK480 to digital output source selection
	  WREG				(0xBF000000 + (0x103AA0 << 1)), 0x8051		  #// PLL_TEST[15]: Bypass 480MHz clock divider
                                                            #// PLL_TEST[7:4]: 5b01010 for 1.0x
                                                            #// PLL_TEST[0]: 1: synthesizer clock, 2b11, 0: XIN_C
		WREG				(0xBF000000 + (0x103A82 << 1)), 0x2084			#//Enable CLK12_SEL bit <2> for select low voltage crystal clock
		WREG				(0xBF000000 + (0x103A88 << 1)), 0x040f			#//#7=0 Enable band-gap current  #3=0 Disable force_pll_on
		WREG				(0xBF000000 + (0x103A80 << 1)), 0x6bc3   		#//reg_pdn: bit<15>, bit <2> ref_pdn # Turn on reference voltage and regulator

    DELAYUS     1000
    
    WREG				(0xBF000000 + (0x103A80 << 1)), 0x69c3			#//Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000
    
    WREG				(0xBF000000 + (0x103A80 << 1)), 0x0001			#//Turn all (including hs_current) use override mode   
  #//================================================================================================
	#//Module: usb1 (0x1007)
    WREG_B      (0xBF000000 + (0x100780 << 1)), 0x0a       	#//Disable MAC initial suspend, Reset UHC
    WREG_B      (0xBF000000 + (0x100780 << 1)), 0x28       	#//Release UHC reset, enable UHC and OTG XIU function

                                                            #//Module: utmi1 (0x103A)
    WREG        (0xBF000000 + (0x103A22 << 1)), 0x2088     	#// PLL_TEST[30:28]:
                                                            #// PLL_TEST[23] CLK480 to digital output source selection
    WREG        (0xBF000000 + (0x103A20 << 1)), 0x8051     	#// PLL_TEST[15]: Bypass 480MHz clock divider
                                                            #// PLL_TEST[7:4]: 5b0101_0 for 1.0x
                                                            #// PLL_TEST[0]: 1: synthesizer clock, 2b11, 0: XIN_C

    WREG        (0xBF000000 + (0x103A02 << 1)), 0x2084     	#//Enable CLK12_SEL bit <2> for select low voltage crystal clock
    WREG        (0xBF000000 + (0x103A08 << 1)), 0x040f     	#//Enable band-gap current
    WREG        (0xBF000000 + (0x103A00 << 1)), 0x6bc3     	#//reg_pdn: bit<15>, bit <2> ref_pdn  # Turn on reference voltage and regulator
    DELAYUS     1000

    WREG        (0xBF000000 + (0x103A00 << 1)), 0x69c3     	#//Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000

    WREG        (0xBF000000 + (0x103A00 << 1)), 0x0001     	#//Turn all (including hs_current) use override mode

  #//================================================================================================ 

    jr          ra
    nop

    .size       BootRomInitPll,.-BootRomInitPll
    .end        BootRomInitPll

