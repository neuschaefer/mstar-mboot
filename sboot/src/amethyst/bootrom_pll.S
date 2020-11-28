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
    .global     BootRomInitPll
    .ent        BootRomInitPll

BootRomInitPll:

 .if (CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51 != 1) 
   #//adc_atop
    WREG_B      (0xBF000000 + (0x10250E << 1)), 0x3F        #//Soft-reset for DAC/ATOP/PLLB/ADCB/PLLA/ADCA
    WREG_B      (0xBF000000 + (0x10250E << 1)), 0x00

    WREG        (0xBF000000 + (0x102508 << 1)), 0x0000      #//Power-on for related adc_atop IPs
    WREG        (0xBF000000 + (0x10250A << 1)), 0x0000
    WREG        (0xBF000000 + (0x10250C << 1)), 0x0000
    WREG        (0xBF000000 + (0x10257E << 1)), 0x0030
    WREG        (0xBF000000 + (0x10257E << 1)), 0x0030

    WREG_B      (0xBF000000 + (0x102590 << 1)), 0x08
    WREG_B      (0xBF000000 + (0x102592 << 1)), 0x08
    WREG_B      (0xBF000000 + (0x1025A0 << 1)), 0x00
    WREG_B      (0xBF000000 + (0x1025A4 << 1)), 0x00

                                                            #//Module: chiptop (0x101E)
    WREG        (0xBF000000 + (0x101E38 << 1)), 0x0000      #//Power-on for PD_3P3_1, PD_3P3_0 and PD_3P3_USB1

	                                                        #//Module: ana_misc (0x110C)
    WREG        (0xBF000000 + (0x110C02 << 1)), 0x0000      #//reg_mpll_pd = 0
                                                            #//reg_mpll_clk_adc216m_pd = 0
                                                            #//reg_mpll_clk_adc432m_pd = 0
.endif

#// WREG        (0xBF000000 + (0x110C20 << 1)), 0x0020
#// WREG        (0xBF000000 + (0x110C24 << 1)), 0x0411      #//Set divided by 2 control for 3.3Volt input clock: /2
                                                            #//Set MPLL input-divider control: /2
                                                            #//Set MPLL fisrt loop-divider control: /1
                                                            #//Set Loop Filter Resistance Selection: 14k Ohm
    
    WREG_B      (0xBF000000 + (0x110C26 << 1)), ((CPU_CLOCK / 12) << 1)
    
#// WREG        (0xBF000000 + (0x110C28 << 1)), 0x00A0      #//Set change-pump current and Ibias output current
    WREG_B      (0xBF000000 + (0x110C22 << 1) + 1), 0x00    #//Power-on MIPSPLL


	#//Module: usb0 (0x1007)
    WREG_B      (0xBF000000 + (0x100700 << 1)), 0x0a        #//Disable MAC initial suspend, Reset UHC
    WREG_B      (0xBF000000 + (0x100700 << 1)), 0x28        #//Release UHC reset, enable UHC and OTG XIU function

	#//Module: utmi (0x103A)
	WREG    	(0xBF000000 + (0x103AA2 << 1)), 0x5088		#// PLL_TEST[30:28]: 3'b101 for IBIAS current select
										                    #// PLL_TEST[23] CLK480 to digital output source selection
	WREG		(0xBF000000 + (0x103AA0 << 1)), 0x8051		#// PLL_TEST[15]: Bypass 480MHz clock divider
										                    #// PLL_TEST[7:4]: 5'b0101_0 for 1.0x
										                    #// PLL_TEST[0]: 1: synthesizer clock, 2'b11, 0: XIN_C

    WREG        (0xBF000000 + (0x103A82 << 1)), 0x2084      #//Enable CLK12_SEL bit <2> for select low voltage crystal clock
    WREG        (0xBF000000 + (0x103A88 << 1)), 0x0000      #//#7=0 Enable band-gap current  #3=0 Disable force_pll_on
    WREG        (0xBF000000 + (0x103A80 << 1)), 0x6bc3      #//reg_pdn: bit<15>, bit <2> ref_pdn # Turn on reference voltage and regulator
    DELAYUS     1000

    WREG        (0xBF000000 + (0x103A80 << 1)), 0x69c3      #//Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000

    WREG        (0xBF000000 + (0x103A80 << 1)), 0x0001      #//Turn all (including hs_current) use override mode

	                                                        #//Module: usb1 (0x1007)
    WREG_B      (0xBF000000 + (0x100780 << 1)), 0x0a        #//Disable MAC initial suspend, Reset UHC
    WREG_B      (0xBF000000 + (0x100780 << 1)), 0x28        #//Release UHC reset, enable UHC and OTG XIU function

	                                                        #//Module: utmi1 (0x103A)
    WREG        (0xBF000000 + (0x103A22 << 1)), 0x5088      #// PLL_TEST[30:28]: 3'b101 for IBIAS current select
										                    #// PLL_TEST[23] CLK480 to digital output source selection
    WREG        (0xBF000000 + (0x103A20 << 1)), 0x8051      #// PLL_TEST[15]: Bypass 480MHz clock divider
										                    #// PLL_TEST[7:4]: 5'b0101_0 for 1.0x
										                    #// PLL_TEST[0]: 1: synthesizer clock, 2'b11, 0: XIN_C

    WREG        (0xBF000000 + (0x103A02 << 1)), 0x2084      #//Enable CLK12_SEL bit <2> for select low voltage crystal clock
    WREG        (0xBF000000 + (0x103A08 << 1)), 0x0000      #//Enable band-gap current
    WREG        (0xBF000000 + (0x103A00 << 1)), 0x6bc3      #//reg_pdn: bit<15>, bit <2> ref_pdn  # Turn on reference voltage and regulator
    DELAYUS     1000

    WREG        (0xBF000000 + (0x103A00 << 1)), 0x69c3      #//Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000

    WREG        (0xBF000000 + (0x103A00 << 1)), 0x0001      #//Turn all (including hs_current) use override mode

    jr          ra
    nop

    .size       BootRomInitPll,.-BootRomInitPll
    .end        BootRomInitPll

