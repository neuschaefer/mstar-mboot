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

    @//adc_atop
    WREG_B      (MS_BUS_RIU_ADDR + (0x10250E << 1)), 0x3F       @//Soft-reset for DAC/ATOP/PLLB/ADCB/PLLA/ADCA
    WREG_B      (MS_BUS_RIU_ADDR + (0x10250E << 1)), 0x00

    WREG        (MS_BUS_RIU_ADDR + (0x1025FC << 1)), 0x0000     //power-on LDO
    WREG        (MS_BUS_RIU_ADDR + (0x1025FE << 1)), 0x0000     //power-on LDO

    WREG        (MS_BUS_RIU_ADDR + (0x102508 << 1)), 0x0000     @//Power-on for related adc_atop IPs
    WREG        (MS_BUS_RIU_ADDR + (0x10250A << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x10250C << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x10257E << 1)), 0x0030

    WREG_B      (MS_BUS_RIU_ADDR + (0x102590 << 1)), 0x08
    WREG_B      (MS_BUS_RIU_ADDR + (0x102592 << 1)), 0x08
    WREG_B      (MS_BUS_RIU_ADDR + (0x1025A0 << 1)), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x1025A4 << 1)), 0x00


    @//----- Add USB3 PHY setting BEFORE MPLL for Einstein/Napoli only ---------------
    WREG        (MS_BUS_RIU_ADDR + (0x12211C << 1)), 0x017D @// SSC_PRD reg_ssusb_pll_ssc_prd
    WREG_B      (MS_BUS_RIU_ADDR + (0x122118 << 1)), 0x0C   @// PLL RST Delay reg_ssusb_pll_rst_dly
    WREG_B      (MS_BUS_RIU_ADDR + (0x122124 << 1)), 0x50   @// [4]= Egde SA DAC full range.
    @//------------------------------------------------------------------------

@// initial MPLL =====================================================================================
                                                                @//Module: chiptop (0x101E)
    WREG        (MS_BUS_RIU_ADDR + (0x101E38 << 1)), 0x0000     @//Power-on for PD_3P3_1, PD_3P3_0 and PD_3P3_USB1

                                                                @//Module: ana_misc (0x110C)
    WREG_B        (MS_BUS_RIU_ADDR + (0x110C02 << 1) +1 ), 0x00     @//reg_mpll_pd = 0
                                                                @//reg_mpll_clk_adc216m_pd = 0
                                                                @//reg_mpll_clk_adc432m_pd = 0

    WREG_B      (MS_BUS_RIU_ADDR + (0x110C08 << 1)), 0x11       @//MPLL test enable
    WREG_B      (MS_BUS_RIU_ADDR + (0x110C00 << 1)), 0x01       @//MPLL test ctrl
    WREG_B      (MS_BUS_RIU_ADDR + (0x110C00 << 1) +1 ), 0x10       @//MPLL test ctrl

@// initial ARMPLL ===================================================================================
    WREG_B      (MS_BUS_RIU_ADDR + (0x110C22 << 1) + 1), 0x00
#ifdef CONFIG_MSTAR_DVFS_ENABLE
    WREG        (MS_BUS_RIU_ADDR + (0x110CC0 << 1)), (CONFIG_DVFS_CPU_CLOCK_INIT & 0xFFFF)
    WREG        (MS_BUS_RIU_ADDR + (0x110CC2 << 1)), ((CONFIG_DVFS_CPU_CLOCK_INIT >> 16) & 0xFFFF)
#else
    WREG        (MS_BUS_RIU_ADDR + (0x110CC0 << 1)), (CONFIG_CPU_CLOCK & 0xFFFF)
    WREG        (MS_BUS_RIU_ADDR + (0x110CC2 << 1)), ((CONFIG_CPU_CLOCK >> 16) & 0xFFFF)
#endif
    WREG_B      (MS_BUS_RIU_ADDR + (0x110CC4 << 1)), 0x01

@// initial MIUPLL ===================================================================================
    WREG_B      (MS_BUS_RIU_ADDR + (0x110C62 << 1) + 1), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x110C68 << 1)), 0x01
    WREG_B      (MS_BUS_RIU_ADDR + (0x110C72 << 1) + 1), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x110C78 << 1)), 0x01
    WREG        (MS_BUS_RIU_ADDR + (0x100B3A << 1)), 0x0808

@// initial DSPPLL ===================================================================================
    WREG_B      (MS_BUS_RIU_ADDR + (0x110C42 << 1) + 1), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x110C48 << 1)), 0x01

@// initial GMACPLL ===================================================================================
    WREG_B      (MS_BUS_RIU_ADDR + (0x110CE6 << 1)), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x110CF6 << 1)), 0x19

#if 0
@// initial UPLL ===================================================================================
    WREG        (MS_BUS_RIU_ADDR + (0x100804 << 1)), 0x0110	@// UPLL0 enable
    WREG_B      (MS_BUS_RIU_ADDR + (0x100800 << 1)), 0x90       @// Enable 320MHz clk from UPLL0
    WREG_B      (MS_BUS_RIU_ADDR + (0x100820 << 1)), 0xC0       @// Enable 20MHz crystal from UPLL1
    WREG        (MS_BUS_RIU_ADDR + (0x103A08 << 1)), 0x040F	@// UTMI1
    WREG        (MS_BUS_RIU_ADDR + (0x103A00 << 1)), 0x7F05
    WREG        (MS_BUS_RIU_ADDR + (0x103A88 << 1)), 0x040F
    WREG        (MS_BUS_RIU_ADDR + (0x103A82 << 1)), 0x9084
    WREG        (MS_BUS_RIU_ADDR + (0x103A94 << 1)), 0x400B
    WREG        (MS_BUS_RIU_ADDR + (0x103A80 << 1)), 0x0001
    WREG        (MS_BUS_RIU_ADDR + (0x103A80 << 1)), 0x6BC3
    WREG        (MS_BUS_RIU_ADDR + (0x103A80 << 1)), 0x69C3
    WREG        (MS_BUS_RIU_ADDR + (0x103A80 << 1)), 0x0001
    WREG        (MS_BUS_RIU_ADDR + (0x100700 << 1)), 0x0228
    WREG        (MS_BUS_RIU_ADDR + (0x100702 << 1)), 0x0001
    WREG        (MS_BUS_RIU_ADDR + (0x103A88 << 1)), 0x040F

@// initial G3DPLL ===================================================================================
    WREG_B      (MS_BUS_RIU_ADDR + (0x11088A << 1)), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x11088C << 1)), 0x08
    WREG        (MS_BUS_RIU_ADDR + (0x103340 << 1)), 0x0000

#endif

@// initial UPLL ===================================================================================
    WREG        (MS_BUS_RIU_ADDR + (0x100804 << 1)), 0x0110	@// UPLL0 enable
    WREG        (MS_BUS_RIU_ADDR + (0x100824 << 1)), 0x0110	@// UPLL1 enable
    WREG_B      (MS_BUS_RIU_ADDR + (0x100800 << 1)), 0x90       @// Enable 320MHz clk from UPLL0
    @//----- Add USB3 PHY setting BEFORE 20MHz clk for Einstein/Napoli only ---------------
    WREG_B      (MS_BUS_RIU_ADDR + (0x111C92 << 1)), 0x03   @// Auto-EQ pattern reg_ssusb_eq_isiflag_sel
    WREG        (MS_BUS_RIU_ADDR + (0x111C68 << 1)), 0x418  @// BIR setting reg_ssusb_cdr_bir_ltd1
    @//--------------------------------------------------------
    DELAYUS     1000                                           @// Add 1ms delay before enable 20MHz
    WREG_B      (MS_BUS_RIU_ADDR + (0x100820 << 1)), 0x80      @// Enable 20MHz crystal from UPLL1  [0]:Power-reset UPLL [1]:Power-down UPLL [2:3]:NC
                                                               @// [4]:Power-down for 20MHz [5]:Power-down for 320MHz [6]:Enable UPLL test clock [7]:Enable UPLL XTAL mode
    WREG        (MS_BUS_RIU_ADDR + (0x103A88 << 1)), 0x040F	@// UTMI0
    WREG        (MS_BUS_RIU_ADDR + (0x103A80 << 1)), 0x7F05
    WREG        (MS_BUS_RIU_ADDR + (0x103A08 << 1)), 0x040F	@// UTMI1
    WREG        (MS_BUS_RIU_ADDR + (0x103A00 << 1)), 0x7F05
    WREG        (MS_BUS_RIU_ADDR + (0x103908 << 1)), 0x040F	@// UTMI2
    WREG        (MS_BUS_RIU_ADDR + (0x103900 << 1)), 0x7F05
    WREG        (MS_BUS_RIU_ADDR + (0x122088 << 1)), 0x040F	@// UTMI3
    WREG        (MS_BUS_RIU_ADDR + (0x122080 << 1)), 0x7F05
    WREG        (MS_BUS_RIU_ADDR + (0x122308 << 1)), 0x040F	@// UTMI-usb3
    WREG        (MS_BUS_RIU_ADDR + (0x122300 << 1)), 0x7F05

@// initial G3DPLL ===================================================================================
    WREG_B      (MS_BUS_RIU_ADDR + (0x11088A << 1)), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x11088C << 1)), 0x08
    WREG        (MS_BUS_RIU_ADDR + (0x103340 << 1)), 0x0000

@// initial USBPLL ===================================================================================
                                                                @//Module: usb0 (0x100700)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100700 << 1)), 0x0a       @//Disable MAC initial suspend, Reset UHC
    WREG_B      (MS_BUS_RIU_ADDR + (0x100700 << 1)), 0x28       @//Release UHC reset, enable UHC and OTG XIU function

                                                                @//Module: utmi0 (0x103A80)
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
                                                                @//Module: usb1 (0x100780)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100780 << 1)), 0x0a       @//Disable MAC initial suspend, Reset UHC
    WREG_B      (MS_BUS_RIU_ADDR + (0x100780 << 1)), 0x28       @//Release UHC reset, enable UHC and OTG XIU function

                                                                @//Module: utmi1 (0x103A00)
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
                                                                @//Module: usb2 (0x113800)
    WREG_B      (MS_BUS_RIU_ADDR + (0x113800 << 1)), 0x0a       @//Disable MAC initial suspend, Reset UHC
    WREG_B      (MS_BUS_RIU_ADDR + (0x113800 << 1)), 0x28       @//Release UHC reset, enable UHC and OTG XIU function

                                                                @//Module: utmi2 (0x103900)
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
                                                                @//Module: usb3 (0x113880)
    WREG_B      (MS_BUS_RIU_ADDR + (0x113880 << 1)), 0x0a       @//Disable MAC initial suspend, Reset UHC
    WREG_B      (MS_BUS_RIU_ADDR + (0x113880 << 1)), 0x28       @//Release UHC reset, enable UHC and OTG XIU function

                                                                @//Module: utmi3 (0x122080)
    WREG        (MS_BUS_RIU_ADDR + (0x1220A2 << 1)), 0x2088     @//PLL_TEST[30:28]: 3'b101 for IBIAS current select
    WREG        (MS_BUS_RIU_ADDR + (0x1220A0 << 1)), 0x8051     @//PLL_TEST[15]: Bypass 480MHz clock divider
    WREG        (MS_BUS_RIU_ADDR + (0x122082 << 1)), 0x2084     @//Enable CLK12_SEL bit <2> for select low voltage crystal clock
    WREG        (MS_BUS_RIU_ADDR + (0x122088 << 1)), 0x0406     @//bit<7>: Power down UTMI port-0 bandgap current

    WREG        (MS_BUS_RIU_ADDR + (0x122080 << 1)), 0x6bc3     @//reg_pdn: bit<15>, bit <2> ref_pdn  # Turn on reference voltage and regulator
    DELAYUS     1000

    WREG        (MS_BUS_RIU_ADDR + (0x122080 << 1)), 0x69c3     @//Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000

    WREG        (MS_BUS_RIU_ADDR + (0x122080 << 1)), 0x0001     @//Turn all (including hs_current) use override mode

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
#if 0
@//=================================================================================================
@//Module: dvi_atop (0x1109)

    WREG        (MS_BUS_RIU_ADDR + ( 0x11090C << 1)), 0x0000          @//Relase soft-reset for DVI/HDMI/HDCP blocks
    WREG        (MS_BUS_RIU_ADDR + ( 0x1109C0 << 1)), 0x0000          @//Power-on for DVI/HDMI/HDCP blocks
    WREG        (MS_BUS_RIU_ADDR + ( 0x1109D2 << 1)), 0x0000          @//Power-on for DVT port 2
    WREG        (MS_BUS_RIU_ADDR + ( 0x110906 << 1)), 0x0000          @//Enable clock for related dvi_atop IPs
    WREG        (MS_BUS_RIU_ADDR + ( 0x1109CE << 1)), 0x4000          @//Port A/C: ENAUTO
    WREG        (MS_BUS_RIU_ADDR + ( 0x1109CA << 1)), 0x3000          @//Port A/C: TEST_CMP[1:0]
    WREG        (MS_BUS_RIU_ADDR + ( 0x1109FE << 1)), 0x0000          @//A1 added

@//=================================================================================================
@//Module: dvi_atop1 (0x1132)

    WREG        (MS_BUS_RIU_ADDR + ( 0x11320C << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + ( 0x1132C0 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + ( 0x1132CE << 1)), 0x4000          @//Port B: ENAUTO
    WREG        (MS_BUS_RIU_ADDR + ( 0x1132CA << 1)), 0x3000          @//Port B: TEST_CMP[1:0]
    WREG        (MS_BUS_RIU_ADDR + ( 0x1132E8 << 1)), 0x0000          @//A1 added

@//=================================================================================================
@//Module: dvi_atop2 (0x1134)

    WREG        (MS_BUS_RIU_ADDR + ( 0x11340C << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + ( 0x1134C0 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + ( 0x1134CE << 1)), 0x4000          @//Port D: ENAUTO
    WREG        (MS_BUS_RIU_ADDR + ( 0x1134CA << 1)), 0x3000          @//Port D: TEST_CMP[1:0]
    WREG        (MS_BUS_RIU_ADDR + ( 0x1134E8 << 1)), 0x0000          @//A1 added

@//=================================================================================================
@//Module: pm_sleep (0x000E)

    WREG        (MS_BUS_RIU_ADDR + ( 0x000E94 << 1)), 0x0000          @//Power-on dvi_atop in PM_SLEEP
    WREG        (MS_BUS_RIU_ADDR + ( 0x000E96 << 1)), 0x0000

@//=================================================================================================
#endif
    bx          lr

    .size       BootRom_InitPll,.-BootRom_InitPll

    .end

