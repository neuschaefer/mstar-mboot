/*
 *#############################################################################
 *
 * Copyright (c) 2006-2012 MStar Semiconductor, Inc.
 * All rights reserved.
 *
 * Unless otherwise stipulated in writing, any and all information contained
 * herein regardless in any format shall remain the sole proprietary of
 * MStar Semiconductor Inc. and be kept in strict confidence
 * (¡§MStar Confidential Information¡¨) by the recipient.
 * Any unauthorized act including without limitation unauthorized disclosure,
 * copying, use, reproduction, sale, distribution, modification, disassembling,
 * reverse engineering and compiling of the contents of MStar Confidential
 * Information is unlawful and strictly prohibited. MStar hereby reserves the
 * rights to any and all damages, losses, costs and expenses resulting therefrom.
 *
 *#############################################################################
 */

#ifndef _BOOT_INC_
#include "boot.inc"
#endif

    .text
    .global     BootRom_InitPll

BootRom_InitPll:

#if defined(CONFIG_MSTAR_ASIC_EMULATION_ENABLE)

                                                                @//Module: adc_atop (0x1025)
    WREG_B      (MS_BUS_RIU_ADDR + (0x10250E << 1)), 0x3F
    WREG_B      (MS_BUS_RIU_ADDR + (0x10250E << 1)), 0x00       @//Release Soft-Reset for ADCA/PLLA/ADCB/PLLB/ATOP/Phase DAC

    WREG        (MS_BUS_RIU_ADDR + (0x102508 << 1)), 0x0000     @//Power-On releated blocks in ATOP
    WREG        (MS_BUS_RIU_ADDR + (0x10250A << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x10250C << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x10257E << 1)), 0x0030     @//Enable SOG MUX

                                                                @//CVBS DAC
    WREG_B      (MS_BUS_RIU_ADDR + (0x102590 << 1)), 0x08       @//Enable IDAC (Ch1)
    WREG_B      (MS_BUS_RIU_ADDR + (0x102592 << 1)), 0x08       @//Enable IDAC (Ch2)
                                                                @//CVBSO
    WREG_B      (MS_BUS_RIU_ADDR + (0x1025A0 << 1)), 0x00       @//Enable CVBSO1
    WREG_B      (MS_BUS_RIU_ADDR + (0x1025A0 << 1)), 0x00       @//Enable CVBSO2

                                                                @//Module: chiptop (0x101E)
    WREG_B      (MS_BUS_RIU_ADDR + (0x101E38 << 1)), 0x00       @//Power-on for PD_3P3_1, PD_3P3_0 and PD_3P3_USB1


                                                                @//Module: ana_misc (0x110C)
    WREG        (MS_BUS_RIU_ADDR + (0x110C02 << 1)), 0x0000     @//reg_mpll_pd = 0
                                                                @//reg_mpll_clk_adc216m_pd = 0
                                                                @//reg_mpll_clk_adc432m_pd = 0

    WREG_B      (MS_BUS_RIU_ADDR + (0x110C26 << 1)), (CPU_CLOCK / 12)

    WREG_B      (MS_BUS_RIU_ADDR + (0x110C22 << 1) + 1), 0x00   @//Power-on MIPSPLL


                                                                @//MIU_128bit PLL  (default =~ 300 MHz)
                                                                @//MIU_256bit PLL  (default =~ 264 MHz)
    WREG        (MS_BUS_RIU_ADDR + (0x110C62 << 1)), 0x0000     @//MIU_128BUS_PLL power on
    WREG        (MS_BUS_RIU_ADDR + (0x110C72 << 1)), 0x0000     @//MIU_256BUS_PLL power on
    WREG        (MS_BUS_RIU_ADDR + (0x100B3A << 1)), 0x0808     @//turn on clk_miu & select clk_miu = MIU_128bit_PLL_VCO
                                                                @//turn on clk_miu_256bus & select clk_miu_256bus = MIU_256bit_PLL_VCO

                                                                @//DSP PLL
    WREG        (MS_BUS_RIU_ADDR + (0x110C42 << 1)), 0x0001     @//MPLL enable
    WREG_B      (MS_BUS_RIU_ADDR + (0x110C46 << 1)), 0x3f       @//DSPPLL_VCO_OUT =~ 378 MHz

                                                                @//LVDS PLL
    WREG        (MS_BUS_RIU_ADDR + (0x110C82 << 1)), 0x0000     @//LVDS_PLL_VCO_OUT =~ 432 MHz

                                                                @//Module: usb0 (0x1007)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100700 << 1)), 0x0a       @//Disable MAC initial suspend, Reset UHC
    WREG_B      (MS_BUS_RIU_ADDR + (0x100700 << 1)), 0x28       @//Release UHC reset, enable UHC and OTG XIU function

                                                                @//Module: utmi (0x103A)
    WREG        (MS_BUS_RIU_ADDR + (0x103AA2 << 1)), 0x5088     @// PLL_TEST[30:28]: 3b101 for IBIAS current select
                                                                @// PLL_TEST[23] CLK480 to digital output source selection
    WREG        (MS_BUS_RIU_ADDR + (0x103AA0 << 1)), 0x8051     @// PLL_TEST[15]: Bypass 480MHz clock divider
                                                                @// PLL_TEST[7:4]: 5b0101_0 for 1.0x
                                                                @// PLL_TEST[0]: 1: synthesizer clock, 2b11, 0: XIN_C
    WREG        (MS_BUS_RIU_ADDR + (0x103A82 << 1)), 0x2084     @// Enable CLK12_SEL bit <2> for select low voltage crystal clock
    WREG        (MS_BUS_RIU_ADDR + (0x103A88 << 1)), 0x0000     @// #7=0 Enable band-gap current  #3=0 Disable force_pll_on
    WREG        (MS_BUS_RIU_ADDR + (0x103A80 << 1)), 0x6bc3     @// reg_pdn: bit<15>, bit <2> ref_pdn # Turn on reference voltage and regulator
    DELAYUS     1000
    WREG        (MS_BUS_RIU_ADDR + (0x103A80 << 1)), 0x69c3     @// Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000
    WREG        (MS_BUS_RIU_ADDR + (0x103A80 << 1)), 0x0001     @// Turn all (including hs_current) use override mode

                                                                @//Module: usb1 (0x1007)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100780 << 1)), 0x0a       @// Disable MAC initial suspend, Reset UHC
    WREG_B      (MS_BUS_RIU_ADDR + (0x100780 << 1)), 0x28       @// Release UHC reset, enable UHC and OTG XIU function

                                                                @//Module: utmi1 (0x103A)
    WREG        (MS_BUS_RIU_ADDR + (0x103A22 << 1)), 0x5088     @// PLL_TEST[30:28]: 3b101 for IBIAS current select
                                                                @// PLL_TEST[23] CLK480 to digital output source selection
    WREG        (MS_BUS_RIU_ADDR + (0x103A20 << 1)), 0x8051     @// PLL_TEST[15]: Bypass 480MHz clock divider
                                                                @// PLL_TEST[7:4]: 5b0101_0 for 1.0x
                                                                @// PLL_TEST[0]: 1: synthesizer clock, 2b11, 0: XIN_C
    WREG        (MS_BUS_RIU_ADDR + (0x103A02 << 1)), 0x2084     @// Enable CLK12_SEL bit <2> for select low voltage crystal clock
    WREG        (MS_BUS_RIU_ADDR + (0x103A08 << 1)), 0x0000     @// Enable band-gap current
    WREG        (MS_BUS_RIU_ADDR + (0x103A00 << 1)), 0x6bc3     @// reg_pdn: bit<15>, bit <2> ref_pdn  # Turn on reference voltage and regulator
    DELAYUS     1000
    WREG        (MS_BUS_RIU_ADDR + (0x103A00 << 1)), 0x69c3     @// Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000
    WREG        (MS_BUS_RIU_ADDR + (0x103A00 << 1)), 0x0001     @// Turn all (including hs_current) use override mode

                                                                @//USBC2 <--> UTMI2
    WREG_B      (MS_BUS_RIU_ADDR + (0x113800 << 1)), 0x0a       @// Disable MAC initial suspend, Reset UHC
    WREG_B      (MS_BUS_RIU_ADDR + (0x113800 << 1)), 0x68       @// Release UHC reset, enable UHC and OTG XIU function
    WREG        (MS_BUS_RIU_ADDR + (0x103922 << 1)), 0x5088     @// Set PLL_TEST[23:21] for enable 480MHz clock
    WREG        (MS_BUS_RIU_ADDR + (0x103920 << 1)), 0x8051
    WREG        (MS_BUS_RIU_ADDR + (0x103902 << 1)), 0x2084     @// Enable CLK12_SEL bit <2> for select low voltage crystal clock
    WREG        (MS_BUS_RIU_ADDR + (0x103908 << 1)), 0x0000     @// Enable band-gap current
    WREG        (MS_BUS_RIU_ADDR + (0x103900 << 1)), 0x6bc3     @// reg_pdn: bit<15>, bit <2> ref_pdn  # Turn on reference voltage and regulator
    DELAYUS     1000
    WREG        (MS_BUS_RIU_ADDR + (0x103900 << 1)), 0x69c3     @// Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000
    WREG        (MS_BUS_RIU_ADDR + (0x103900 << 1)), 0x0001     @// Turn all (including hs_current) use override mode

#else

    @//adc_atop
    WREG_B      (MS_BUS_RIU_ADDR + (0x10250E << 1)), 0x7F       @//Soft-reset for DAC/ATOP/PLLB/ADCB/PLLA/ADCA
    WREG_B      (MS_BUS_RIU_ADDR + (0x10250E << 1)), 0x00

    WREG        (MS_BUS_RIU_ADDR + (0x102508 << 1)), 0x0000     @//Power-on for related adc_atop IPs
    WREG        (MS_BUS_RIU_ADDR + (0x10250A << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x10250C << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x10257E << 1)), 0x0030

    WREG_B      (MS_BUS_RIU_ADDR + (0x102590 << 1)), 0x08
    WREG_B      (MS_BUS_RIU_ADDR + (0x102592 << 1)), 0x08
    WREG_B      (MS_BUS_RIU_ADDR + (0x1025A0 << 1)), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x1025A4 << 1)), 0x00

                                                                @//Module: chiptop (0x101E)
    WREG        (MS_BUS_RIU_ADDR + (0x101E38 << 1)), 0x0000     @//Power-on for PD_3P3_1, PD_3P3_0 and PD_3P3_USB1

                                                                @//Module: ana_misc (0x110C)
    WREG        (MS_BUS_RIU_ADDR + (0x110C02 << 1)), 0x0000     @//reg_mpll_pd = 0
                                                                @//reg_mpll_clk_adc216m_pd = 0
                                                                @//reg_mpll_clk_adc432m_pd = 0

    WREG_B      (MS_BUS_RIU_ADDR + (0x110C26 << 1) + 1), 0x11
    WREG_B      (MS_BUS_RIU_ADDR + (0x110C26 << 1)), (CPU_CLOCK / 12)

    WREG_B      (MS_BUS_RIU_ADDR + (0x110C22 << 1) + 1), 0x00   @//Power-on MIPSPLL


                                                                @//Module: usb0 (0x1007)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100700 << 1)), 0x0a       @//Disable MAC initial suspend, Reset UHC
    WREG_B      (MS_BUS_RIU_ADDR + (0x100700 << 1)), 0x28       @//Release UHC reset, enable UHC and OTG XIU function

                                                                @//Module: utmi (0x103A)
    WREG        (MS_BUS_RIU_ADDR + (0x103AA2 << 1)), 0x2088     @// PLL_TEST[30:28]:
                                                                @// PLL_TEST[23] CLK480 to digital output source selection
    WREG        (MS_BUS_RIU_ADDR + (0x103AA0 << 1)), 0x8051     @// PLL_TEST[15]: Bypass 480MHz clock divider
                                                                @// PLL_TEST[7:4]: 5b01010 for 1.0x
                                                                @// PLL_TEST[0]: 1: synthesizer clock, 2b11, 0: XIN_C

    WREG        (MS_BUS_RIU_ADDR + (0x103A82 << 1)), 0x2084     @//Enable CLK12_SEL bit <2> for select low voltage crystal clock
    WREG        (MS_BUS_RIU_ADDR + (0x103A88 << 1)), 0x0000     @//#7=0 Enable band-gap current  #3=0 Disable force_pll_on
    WREG        (MS_BUS_RIU_ADDR + (0x103A80 << 1)), 0x6bc3     @//reg_pdn: bit<15>, bit <2> ref_pdn # Turn on reference voltage and regulator
    DELAYUS     1000

    WREG        (MS_BUS_RIU_ADDR + (0x103A80 << 1)), 0x69c3     @//Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000

    WREG        (MS_BUS_RIU_ADDR + (0x103A80 << 1)), 0x0001     @//Turn all (including hs_current) use override mode

                                                                @//Module: usb1 (0x1007)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100780 << 1)), 0x0a       @//Disable MAC initial suspend, Reset UHC
    WREG_B      (MS_BUS_RIU_ADDR + (0x100780 << 1)), 0x28       @//Release UHC reset, enable UHC and OTG XIU function

                                                                @//Module: utmi1 (0x103A)
    WREG        (MS_BUS_RIU_ADDR + (0x103A22 << 1)), 0x2088     @// PLL_TEST[30:28]:
                                                                @// PLL_TEST[23] CLK480 to digital output source selection
    WREG        (MS_BUS_RIU_ADDR + (0x103A20 << 1)), 0x8051     @// PLL_TEST[15]: Bypass 480MHz clock divider
                                                                @// PLL_TEST[7:4]: 5b0101_0 for 1.0x
                                                                @// PLL_TEST[0]: 1: synthesizer clock, 2b11, 0: XIN_C

    WREG        (MS_BUS_RIU_ADDR + (0x103A02 << 1)), 0x2084     @//Enable CLK12_SEL bit <2> for select low voltage crystal clock
    WREG        (MS_BUS_RIU_ADDR + (0x103A08 << 1)), 0x0000     @//Enable band-gap current
    WREG        (MS_BUS_RIU_ADDR + (0x103A00 << 1)), 0x6bc3     @//reg_pdn: bit<15>, bit <2> ref_pdn  # Turn on reference voltage and regulator
    DELAYUS     1000

    WREG        (MS_BUS_RIU_ADDR + (0x103A00 << 1)), 0x69c3     @//Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000

    WREG        (MS_BUS_RIU_ADDR + (0x103A00 << 1)), 0x0001     @//Turn all (including hs_current) use override mode

                                                                @//Module: usb2 (0x1138)
    WREG_B      (MS_BUS_RIU_ADDR + (0x113800 << 1)), 0x0a       @//Disable MAC initial suspend, Reset UHC
    WREG_B      (MS_BUS_RIU_ADDR + (0x113800 << 1)), 0x28       @//Release UHC reset, enable UHC and OTG XIU function

                                                                @//Module: utmi2 (0x1039)
    WREG        (MS_BUS_RIU_ADDR + (0x103922 << 1)), 0x2088     @// PLL_TEST[30:28]:
                                                                @// PLL_TEST[23] CLK480 to digital output source selection
    WREG        (MS_BUS_RIU_ADDR + (0x103920 << 1)), 0x8051     @// PLL_TEST[15]: Bypass 480MHz clock divider
                                                                @// PLL_TEST[7:4]: 5b0101_0 for 1.0x
                                                                @// PLL_TEST[0]: 1: synthesizer clock, 2b11, 0: XIN_C

    WREG        (MS_BUS_RIU_ADDR + (0x103902 << 1)), 0x2084     @//Enable CLK12_SEL bit <2> for select low voltage crystal clock
    WREG        (MS_BUS_RIU_ADDR + (0x103908 << 1)), 0x0000     @//Enable band-gap current
    WREG        (MS_BUS_RIU_ADDR + (0x103900 << 1)), 0x6bc3     @//reg_pdn: bit<15>, bit <2> ref_pdn  # Turn on reference voltage and regulator
    DELAYUS     1000

    WREG        (MS_BUS_RIU_ADDR + (0x103900 << 1)), 0x69c3     @//Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000

    WREG        (MS_BUS_RIU_ADDR + (0x103900 << 1)), 0x0001     @//Turn all (including hs_current) use override mode
#endif

    bx          lr

    .size       BootRom_InitPll,.-BootRom_InitPll

    .end

