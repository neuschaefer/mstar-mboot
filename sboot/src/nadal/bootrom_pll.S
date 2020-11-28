/*
 *#############################################################################
 *
 * Copyright (c) 2006-2013 MStar Semiconductor, Inc.
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

    @//AVD reset
    RREG        r8, (MS_BUS_RIU_ADDR + (0x10362A << 1))
    orr         r8, r8, #0x0010
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x10362A << 1))

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

@//================================================================================================
                                                                @//Module: chiptop (0x101E)
    WREG        (MS_BUS_RIU_ADDR + (0x101E38 << 1)), 0x0000     @//Power-on for PD_3P3_1, PD_3P3_0 and PD_3P3_USB1

@//================================================================================================
    WREG        (MS_BUS_RIU_ADDR + (0x110C02 << 1)), 0x0000     @//reg_mpll_pd = 0
                                                                @//reg_mpll_clk_adc216m_pd = 0
                                                             @//Module: ana_misc (0x110C)
                                                              @//reg_mpll_clk_adc432m_pd = 0

    WREG        (MS_BUS_RIU_ADDR + (0x110D36 << 1)), 0x0000     @// reg_DDRPLL_LOOP_DIV_FIRST   :[15:14]    divideby4
    WREG        (MS_BUS_RIU_ADDR + (0x110D34 << 1)), 0x0200     @// reg_DDRPLL_LOOP_DIV_SECOND      :[15:14]    divideby3
    WREG        (MS_BUS_RIU_ADDR + (0x110D30 << 1)), 0x147A     @// set pll to 300MHz [clk_miu_2x: 300Mhz, clk_miu_1x: 150Mhz]
    WREG        (MS_BUS_RIU_ADDR + (0x110D32 << 1)), 0x002E     @// set pll to 300MHz [clk_miu_2x: 300Mhz, clk_miu_1x: 150Mhz]
    WREG        (MS_BUS_RIU_ADDR + (0x110D2E << 1)), 0x0800     @// PLL PD
    WREG        (MS_BUS_RIU_ADDR + (0x110D20 << 1)), 0x0020     @// set pll initialvalue
    WREG        (MS_BUS_RIU_ADDR + (0x110D22 << 1)), 0x2000     @// set pll initialvalue
    WREG        (MS_BUS_RIU_ADDR + (0x110D24 << 1)), 0x2000     @// set pll initialvalue

    DELAYUS     100

    WREG        (MS_BUS_RIU_ADDR + (0x110D2C << 1)), 0x0100     @// PLL LOCK

    DELAYUS     100


#ifdef CONFIG_MSTAR_STR_ENABLE

    RREG        r0, (MS_BUS_RIU_ADDR + (0x0E6E << 1))   @//Disable Divisor Latch Access
    bic         r0, r0, #0x00FF
    ldr         r1, =0xFF00
    cmp         r0, r1
    beq         BootRom_Pll_Str_AcFlow

    WREG        (MS_BUS_RIU_ADDR + (0x101202 << 1)), 0xF300     @// MCLK PD
    b           BootRom_Pll_Str_EndFlow

BootRom_Pll_Str_AcFlow:
    WREG        (MS_BUS_RIU_ADDR + (0x101202 << 1)), 0x0300     @// MCLK PD
BootRom_Pll_Str_EndFlow:

#else
    WREG        (MS_BUS_RIU_ADDR + (0x101202 << 1)), 0x0300     @// MCLK PD
#endif

@//================================================================================================

    WREG        (MS_BUS_RIU_ADDR + (0x110C22 << 1)), 0x1E80
    WREG_B      (MS_BUS_RIU_ADDR + (0x110C24 << 1)), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x110C26 << 1)), 0x0C
    WREG        (MS_BUS_RIU_ADDR + (0x110CB0 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x110CD0 << 1)), 0x0001

#ifdef CONFIG_MSTAR_DVFS_ENABLE
    WREG        (MS_BUS_RIU_ADDR + (0x110CC0 << 1)), (CONFIG_DVFS_CPU_CLOCK_INIT & 0xFFFF)
    WREG        (MS_BUS_RIU_ADDR + (0x110CC2 << 1)), ((CONFIG_DVFS_CPU_CLOCK_INIT >> 16) & 0xFFFF)
#else
    WREG        (MS_BUS_RIU_ADDR + (0x110CC0 << 1)), (CONFIG_CPU_CLOCK & 0xFFFF)
    WREG        (MS_BUS_RIU_ADDR + (0x110CC2 << 1)), ((CONFIG_CPU_CLOCK >> 16) & 0xFFFF)
#endif
    WREG        (MS_BUS_RIU_ADDR + (0x110CC4 << 1)), 0x0001

    WREG        (MS_BUS_RIU_ADDR + (0x10051E << 1)), CPU_CLOCK

@//================================================================================================
                                                                @//Module: usb0 (0x1007)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100700 << 1)), 0x0a       @//Disable MAC initial suspend, Reset UHC
    WREG_B      (MS_BUS_RIU_ADDR + (0x100700 << 1)), 0x28       @//Release UHC reset, enable UHC and OTG XIU function

@//================================================================================================
                                                                @//Module: utmi (0x103A)
    WREG        (MS_BUS_RIU_ADDR + (0x103AA2 << 1)), 0x2088     @//PLL_TEST[30:28]: 3'b101 for IBIAS current select
    WREG        (MS_BUS_RIU_ADDR + (0x103AA0 << 1)), 0x8051     @//PLL_TEST[15]: Bypass 480MHz clock divider
    WREG        (MS_BUS_RIU_ADDR + (0x103A82 << 1)), 0x2084     @//Enable CLK12_SEL bit <2> for select low voltage crystal clock
    WREG        (MS_BUS_RIU_ADDR + (0x103A88 << 1)), 0x0406     @//bit<7>: Power down UTMI port-0 bandgap current

    WREG        (MS_BUS_RIU_ADDR + (0x103A80 << 1)), 0x6bc3     @//reg_pdn: bit<15>, bit <2> ref_pdn # Turn on reference voltage and regulator
    DELAYUS     1000

    WREG        (MS_BUS_RIU_ADDR + (0x103A80 << 1)), 0x69c3     @//Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000

    WREG        (MS_BUS_RIU_ADDR + (0x103A80 << 1)), 0x0001     @//Turn all (including hs_current) use override mode

@//================================================================================================
                                                                @//Module: usb1 (0x1007)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100780 << 1)), 0x0a       @//Disable MAC initial suspend, Reset UHC
    WREG_B      (MS_BUS_RIU_ADDR + (0x100780 << 1)), 0x28       @//Release UHC reset, enable UHC and OTG XIU function

@//================================================================================================
                                                                @//Module: utmi1 (0x103A)
    WREG        (MS_BUS_RIU_ADDR + (0x103A22 << 1)), 0x2088     @//PLL_TEST[30:28]: 3'b101 for IBIAS current select
    WREG        (MS_BUS_RIU_ADDR + (0x103A20 << 1)), 0x8051     @//PLL_TEST[15]: Bypass 480MHz clock divider
    WREG        (MS_BUS_RIU_ADDR + (0x103A02 << 1)), 0x2084     @//Enable CLK12_SEL bit <2> for select low voltage crystal clock
    WREG        (MS_BUS_RIU_ADDR + (0x103A08 << 1)), 0x0406     @//bit<7>: Power down UTMI port-0 bandgap current

    WREG        (MS_BUS_RIU_ADDR + (0x103A00 << 1)), 0x6bc3     @//reg_pdn: bit<15>, bit <2> ref_pdn  # Turn on reference voltage and regulator
    DELAYUS     1000

    WREG        (MS_BUS_RIU_ADDR + (0x103A00 << 1)), 0x69c3     @//Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000

    WREG        (MS_BUS_RIU_ADDR + (0x103A00 << 1)), 0x0001     @//Turn all (including hs_current) use override mode


@//================================================================================================
                                                                @//Module: usb2 (0x1138)
    WREG_B      (MS_BUS_RIU_ADDR + (0x113800 << 1)), 0x0a       @//Disable MAC initial suspend, Reset UHC
    WREG_B      (MS_BUS_RIU_ADDR + (0x113800 << 1)), 0x28       @//Release UHC reset, enable UHC and OTG XIU function

@//================================================================================================
                                                                @//Module: utmi1 (0x1039)
    WREG        (MS_BUS_RIU_ADDR + (0x103922 << 1)), 0x2088     @//PLL_TEST[30:28]: 3'b101 for IBIAS current select
    WREG        (MS_BUS_RIU_ADDR + (0x103920 << 1)), 0x8051     @//PLL_TEST[15]: Bypass 480MHz clock divider
    WREG        (MS_BUS_RIU_ADDR + (0x103902 << 1)), 0x2084     @//Enable CLK12_SEL bit <2> for select low voltage crystal clock
    WREG        (MS_BUS_RIU_ADDR + (0x103908 << 1)), 0x0406     @//bit<7>: Power down UTMI port-0 bandgap current

    WREG        (MS_BUS_RIU_ADDR + (0x103900 << 1)), 0x6bc3     @//reg_pdn: bit<15>, bit <2> ref_pdn  # Turn on reference voltage and regulator
    DELAYUS     1000

    WREG        (MS_BUS_RIU_ADDR + (0x103900 << 1)), 0x69c3     @//Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000

    WREG        (MS_BUS_RIU_ADDR + (0x103900 << 1)), 0x0001     @//Turn all (including hs_current) use override mode

@//================================================================================================
                                                                @//Module: usb3.0
                                                                @//Module: utmi (0x1223)
    WREG        (MS_BUS_RIU_ADDR + (0x122322 << 1)), 0x2088     @//PLL_TEST[30:28]: 3'b101 for IBIAS current select
    WREG        (MS_BUS_RIU_ADDR + (0x122320 << 1)), 0x8051     @//PLL_TEST[15]: Bypass 480MHz clock divid
    WREG        (MS_BUS_RIU_ADDR + (0x122302 << 1)), 0x2084     @//Enable CLK12_SEL bit <2> for select low voltage crystal clock
    WREG        (MS_BUS_RIU_ADDR + (0x122308 << 1)), 0x0406     @//bit<7>: Power down UTMI port-0 bandgap current

    WREG        (MS_BUS_RIU_ADDR + (0x122300 << 1)), 0x6bc3     @//reg_pdn: bit<15>, bit <2> ref_pdn  # Turn on reference voltage and regulator
    DELAYUS     1000

    WREG        (MS_BUS_RIU_ADDR + (0x122300 << 1)), 0x69c3     @//Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000

    WREG        (MS_BUS_RIU_ADDR + (0x122300 << 1)), 0x0001     @//Turn all (including hs_current) use override mode

@//================================================================================================

    bx          lr

    .size       BootRom_InitPll,.-BootRom_InitPll

    .end

