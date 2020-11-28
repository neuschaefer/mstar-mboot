/*
 *#############################################################################
 *
 * Copyright (c) 2006-2015 MStar Semiconductor, Inc.
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

    //AVD reset
    ldr         x1, =(MS_BUS_RIU_ADDR + (0x103600 << 1))
    ldr         w0, [x1, #(0x2a << 1)]
    orr         w0, w0, #0x10
    str         w0, [x1, #(0x2a << 1)]

    ldr         x1, =(MS_BUS_RIU_ADDR + (0x102500 << 1))
    ldr         w0, =0x3f                   //Soft-reset for DAC/ATOP/PLLB/ADCB/PLLA/ADCA
    strb        w0, [x1, #(0x0e << 1)]
    ldr         w0, =0x00
    strb        w0, [x1, #(0x0e << 1)]

    ldr         w0, =0x0000                 //power-on LDO
    str         w0, [x1, #(0xfc << 1)]
    ldr         w0, =0x0000
    str         w0, [x1, #(0xfe << 1)]

    ldr         w0, =0x0000                 //Power-on for related adc_atop IPs
    str         w0, [x1, #(0x08 << 1)]
    ldr         w0, =0x0000
    str         w0, [x1, #(0x0a << 1)]
    ldr         w0, =0x0000
    str         w0, [x1, #(0x0c << 1)]
    ldr         w0, =0x0030
    str         w0, [x1, #(0x7e << 1)]

    ldr         w0, =0x08
    strb        w0, [x1, #(0x90 << 1)]
    ldr         w0, =0x08
    strb        w0, [x1, #(0x92 << 1)]
    ldr         w0, =0x00
    strb        w0, [x1, #(0xa0 << 1)]
    ldr         w0, =0x00
    strb        w0, [x1, #(0xa4 << 1)]

//================================================================================================
//----- Add USB3 PHY setting BEFORE MPLL for Einstein/Napoli/Miami only ---------------
    ldr         x1, =(MS_BUS_RIU_ADDR + (0x122100 << 1))
    ldr         w0, =0x017D                 // SSC_PRD reg_ssusb_pll_ssc_prd
    str         w0, [x1, #(0x1C << 1)]
    ldr         w0, =0x0C                   // PLL RST Delay reg_ssusb_pll_rst_dly
    strb        w0, [x1, #(0x18 << 1)]
    ldr         w0, =0x50                   // [4]= Egde SA DAC full range.
    strb        w0, [x1, #(0x24 << 1)]

    ldr         x1, =(MS_BUS_RIU_ADDR + (0x153500 << 1))
    ldr         w0, =0x017D                 // SSC_PRD reg_ssusb_pll_ssc_prd
    str         w0, [x1, #(0x1C << 1)]
    ldr         w0, =0x0C                   // PLL RST Delay reg_ssusb_pll_rst_dly
    strb        w0, [x1, #(0x18 << 1)]
    ldr         w0, =0x50                   // [4]= Egde SA DAC full range.
    strb        w0, [x1, #(0x24 << 1)]

//================================================================================================
    ldr         x1, =(MS_BUS_RIU_ADDR + (0x101e00 << 1))
    ldr         w0, =0x0000                 //Power-on for PD_3P3_1, PD_3P3_0 and PD_3P3_USB1
    str         w0, [x1, #(0x38 << 1)]

    ldr         x1, =(MS_BUS_RIU_ADDR + (0x110c00 << 1))
    ldr         w0, =0x0000                 //reg_mpll_pd = 0
                                            //reg_mpll_clk_adc216m_pd = 0
                                            //Module: ana_misc (0x110C)
                                            //reg_mpll_clk_adc432m_pd = 0
    str         w0, [x1, #(0x02 << 1)]

    ldr         w0, =0x11
    strb        w0, [x1, #(0x08 << 1)]      //MPLL test enable
    ldr         w0, =0x01
    strb        w0, [x1, #(0x00 << 1)]
    ldr         w0, =0x10
    strb        w0, [x1, #((0x00 << 1) + 1)]

//================================================================================================
// MIPSPLL

    ldr         x1, =(MS_BUS_RIU_ADDR + (0x110c00 << 1))
    ldr         w0, =0x00
    strb        w0, [x1, #((0x22 << 1) + 1)]

#ifdef CONFIG_MSTAR_DVFS_ENABLE
    ldr         w0, =(CONFIG_DVFS_CPU_CLOCK_INIT & 0xFFFF)
    str         w0, [x1, #(0xc0 << 1)]
    ldr         w0, =((CONFIG_DVFS_CPU_CLOCK_INIT >> 16) & 0xFFFF)
    str         w0, [x1, #(0xc2 << 1)]
#else
    ldr         w0, =(CONFIG_CPU_CLOCK & 0xFFFF)
    str         w0, [x1, #(0xc0 << 1)]
    ldr         w0, =((CONFIG_CPU_CLOCK >> 16) & 0xFFFF)
    str         w0, [x1, #(0xc2 << 1)]
#endif
    ldr         w0, =0x0001
    str         w0, [x1, #(0xc4 << 1)]

    ldr         x1, =(MS_BUS_RIU_ADDR + (0x100500 << 1))
    ldr         w0, =CPU_CLOCK
    str         w0, [x1, #(0x1e << 1)]

//================================================================================================
// MIUPLL

    ldr         x1, =(MS_BUS_RIU_ADDR + (0x110C00 << 1))
    ldr         w0, =0x00
    strb        w0, [x1, #((0x62 << 1) + 1)]
    ldr         w0, =0x01
    strb        w0, [x1, #(0x68 << 1)]
    ldr         w0, =0x00
    strb        w0, [x1, #((0x72 << 1) + 1)]
    ldr         w0, =0x01
    strb        w0, [x1, #(0x78 << 1)]

//================================================================================================
// DSPPLL

    ldr         x1, =(MS_BUS_RIU_ADDR + (0x110C00 << 1))
    ldr         w0, =0x00
    strb        w0, [x1, #((0x42 << 1) + 1)]
    ldr         w0, =0x01
    strb        w0, [x1, #(0x48 << 1)]

//================================================================================================
// UPLL

    ldr         x1, =(MS_BUS_RIU_ADDR + (0x100800 << 1))
    ldr         w0, =0x10B0
    str         w0, [x1, #(0x00 << 1)]
    ldr         w0, =0x0110
    str         w0, [x1, #(0x04 << 1)]      // UPLL0 enable
    ldr         w0, =0x10C0
    str         w0, [x1, #(0x20 << 1)]
    ldr         w0, =0x0110
    str         w0, [x1, #(0x24 << 1)]      // UPLL1 enable

    //----- Add USB3 PHY setting BEFORE 20MHz clk for Einstein/Napoli/Miami only ---------------
    ldr         x1, =(MS_BUS_RIU_ADDR + (0x111C00 << 1))
    ldr         w0, =0x03
    strb        w0, [x1, #(0x92 << 1)]      // Auto-EQ pattern reg_ssusb_eq_isiflag_sel
    ldr         w0, =0x0418
    str         w0, [x1, #(0x68 << 1)]      // BIR setting reg_ssusb_cdr_bir_ltd1

    ldr         x1, =(MS_BUS_RIU_ADDR + (0x155300 << 1))
    ldr         w0, =0x03
    strb        w0, [x1, #(0x92 << 1)]      // Auto-EQ pattern reg_ssusb_eq_isiflag_sel
    ldr         w0, =0x0418
    str         w0, [x1, #(0x68 << 1)]      // BIR setting reg_ssusb_cdr_bir_ltd1

    ldr         x1, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
    ldr         w0, =0x8000
    str         w0, [x1, #(0xF0 << 1)]      // gap USB <-> MI rd latch

//================================================================================================
    WREG        (MS_BUS_RIU_ADDR + (0x103A88 << 1)), 0x040F     // UTMI0
    WREG        (MS_BUS_RIU_ADDR + (0x103A80 << 1)), 0x7F05
    WREG        (MS_BUS_RIU_ADDR + (0x103A08 << 1)), 0x040F     // UTMI1
    WREG        (MS_BUS_RIU_ADDR + (0x103A00 << 1)), 0x7F05
    WREG        (MS_BUS_RIU_ADDR + (0x103908 << 1)), 0x040F     // UTMI2
    WREG        (MS_BUS_RIU_ADDR + (0x103900 << 1)), 0x7F05
    WREG        (MS_BUS_RIU_ADDR + (0x122308 << 1)), 0x040F     // UTMI-SS0
    WREG        (MS_BUS_RIU_ADDR + (0x122300 << 1)), 0x7F05
    WREG        (MS_BUS_RIU_ADDR + (0x122388 << 1)), 0x040F     // UTMI-SS1
    WREG        (MS_BUS_RIU_ADDR + (0x122380 << 1)), 0x7F05

    WREG_B      (MS_BUS_RIU_ADDR + (0x122520 << 1) + 1), 0x01   //Enable MIU arbiter

//================================================================================================
                                                                //Module: usb0 (0x100700)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100700 << 1)), 0x0a       //Disable MAC initial suspend, Reset UHC
    WREG_B      (MS_BUS_RIU_ADDR + (0x100700 << 1)), 0x28       //Release UHC reset, enable UHC and OTG XIU function

//================================================================================================
                                                                //Module: utmi0 (0x103A80)
    WREG        (MS_BUS_RIU_ADDR + (0x103AA2 << 1)), 0x2088     //PLL_TEST[30:28]: 3'b101 for IBIAS current select
    WREG        (MS_BUS_RIU_ADDR + (0x103AA0 << 1)), 0x8051     //PLL_TEST[15]: Bypass 480MHz clock divider
    WREG        (MS_BUS_RIU_ADDR + (0x103A82 << 1)), 0x2084     //Enable CLK12_SEL bit <2> for select low voltage crystal clock
    WREG        (MS_BUS_RIU_ADDR + (0x103A88 << 1)), 0x0426     //bit<7>: Power down UTMI port-0 bandgap current

//================================================================================================
                                                                //Module: usb1 (0x100780)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100780 << 1)), 0x0a       //Disable MAC initial suspend, Reset UHC
    WREG_B      (MS_BUS_RIU_ADDR + (0x100780 << 1)), 0x28       //Release UHC reset, enable UHC and OTG XIU function

//================================================================================================
                                                                //Module: utmi1 (0x103A00)
    WREG        (MS_BUS_RIU_ADDR + (0x103A22 << 1)), 0x2088     //PLL_TEST[30:28]: 3'b101 for IBIAS current select
    WREG        (MS_BUS_RIU_ADDR + (0x103A20 << 1)), 0x8051     //PLL_TEST[15]: Bypass 480MHz clock divider
    WREG        (MS_BUS_RIU_ADDR + (0x103A02 << 1)), 0x2084     //Enable CLK12_SEL bit <2> for select low voltage crystal clock
    WREG        (MS_BUS_RIU_ADDR + (0x103A08 << 1)), 0x0426     //bit<7>: Power down UTMI port-0 bandgap current

//================================================================================================
                                                                //Module: usb2 (0x113800)
    WREG_B      (MS_BUS_RIU_ADDR + (0x113800 << 1)), 0x0a       //Disable MAC initial suspend, Reset UHC
    WREG_B      (MS_BUS_RIU_ADDR + (0x113800 << 1)), 0x28       //Release UHC reset, enable UHC and OTG XIU function

//================================================================================================
                                                                //Module: utmi2 (0x103900)
    WREG        (MS_BUS_RIU_ADDR + (0x103922 << 1)), 0x2088     //PLL_TEST[30:28]: 3'b101 for IBIAS current select
    WREG        (MS_BUS_RIU_ADDR + (0x103920 << 1)), 0x8051     //PLL_TEST[15]: Bypass 480MHz clock divider
    WREG        (MS_BUS_RIU_ADDR + (0x103902 << 1)), 0x2084     //Enable CLK12_SEL bit <2> for select low voltage crystal clock
    WREG        (MS_BUS_RIU_ADDR + (0x103908 << 1)), 0x0426     //bit<7>: Power down UTMI port-0 bandgap current

//================================================================================================
                                                                //Module: usb3-ss0 (0x153200)
    WREG_B      (MS_BUS_RIU_ADDR + (0x153200 << 1)), 0x0a       //Disable MAC initial suspend, Reset UHC
    WREG_B      (MS_BUS_RIU_ADDR + (0x153200 << 1)), 0x28       //Release UHC reset, enable UHC and OTG XIU function

//================================================================================================
                                                                //Module: utmi-ss0 (0x122300)
    WREG        (MS_BUS_RIU_ADDR + (0x122322 << 1)), 0x2088     //PLL_TEST[30:28]: 3'b101 for IBIAS current select
    WREG        (MS_BUS_RIU_ADDR + (0x122320 << 1)), 0x8051     //PLL_TEST[15]: Bypass 480MHz clock divid
    WREG        (MS_BUS_RIU_ADDR + (0x122302 << 1)), 0x2084     //Enable CLK12_SEL bit <2> for select low voltage crystal clock
    WREG        (MS_BUS_RIU_ADDR + (0x122308 << 1)), 0x0426     //bit<7>: Power down UTMI port-0 bandgap current

//================================================================================================
                                                                //Module: usb3-ss1 (0x153280)
    WREG_B      (MS_BUS_RIU_ADDR + (0x153280 << 1)), 0x0a       //Disable MAC initial suspend, Reset UHC
    WREG_B      (MS_BUS_RIU_ADDR + (0x153280 << 1)), 0x28       //Release UHC reset, enable UHC and OTG XIU function

//================================================================================================
                                                                //Module: utmi-ss1 (0x122380)
    WREG        (MS_BUS_RIU_ADDR + (0x1223A2 << 1)), 0x2088     //PLL_TEST[30:28]: 3'b101 for IBIAS current select
    WREG        (MS_BUS_RIU_ADDR + (0x1223A0 << 1)), 0x8051     //PLL_TEST[15]: Bypass 480MHz clock divid
    WREG        (MS_BUS_RIU_ADDR + (0x122382 << 1)), 0x2084     //Enable CLK12_SEL bit <2> for select low voltage crystal clock
    WREG        (MS_BUS_RIU_ADDR + (0x122388 << 1)), 0x0426     //bit<7>: Power down UTMI port-0 bandgap current

//================================================================================================

    WREG        (MS_BUS_RIU_ADDR + (0x103A80 << 1)), 0x6bc3     //reg_pdn: bit<15>, bit <2> ref_pdn # Turn on reference voltage and regulator
    WREG        (MS_BUS_RIU_ADDR + (0x103A00 << 1)), 0x6bc3     //reg_pdn: bit<15>, bit <2> ref_pdn  # Turn on reference voltage and regulator
    WREG        (MS_BUS_RIU_ADDR + (0x103900 << 1)), 0x6bc3     //reg_pdn: bit<15>, bit <2> ref_pdn  # Turn on reference voltage and regulator
    WREG        (MS_BUS_RIU_ADDR + (0x122300 << 1)), 0x6bc3     //reg_pdn: bit<15>, bit <2> ref_pdn  # Turn on reference voltage and regulator
    WREG        (MS_BUS_RIU_ADDR + (0x122380 << 1)), 0x6bc3     //reg_pdn: bit<15>, bit <2> ref_pdn  # Turn on reference voltage and regulator
    DELAYUS     1000

    WREG        (MS_BUS_RIU_ADDR + (0x103A80 << 1)), 0x69c3     //Turn on UPLL, reg_pdn: bit<9>
    WREG        (MS_BUS_RIU_ADDR + (0x103A00 << 1)), 0x69c3     //Turn on UPLL, reg_pdn: bit<9>
    WREG        (MS_BUS_RIU_ADDR + (0x103900 << 1)), 0x69c3     //Turn on UPLL, reg_pdn: bit<9>
    WREG        (MS_BUS_RIU_ADDR + (0x122300 << 1)), 0x69c3     //Turn on UPLL, reg_pdn: bit<9>
    WREG        (MS_BUS_RIU_ADDR + (0x122380 << 1)), 0x69c3     //Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000

    WREG        (MS_BUS_RIU_ADDR + (0x103A80 << 1)), 0x0001     //Turn all (including hs_current) use override mode
    WREG        (MS_BUS_RIU_ADDR + (0x103A00 << 1)), 0x0001     //Turn all (including hs_current) use override mode
    WREG        (MS_BUS_RIU_ADDR + (0x103900 << 1)), 0x0001     //Turn all (including hs_current) use override mode
    WREG        (MS_BUS_RIU_ADDR + (0x122300 << 1)), 0x0001     //Turn all (including hs_current) use override mode
    WREG        (MS_BUS_RIU_ADDR + (0x122380 << 1)), 0x0001     //Turn all (including hs_current) use override mode

//================================================================================================

    ret

    .size       BootRom_InitPll,.-BootRom_InitPll
    .end

