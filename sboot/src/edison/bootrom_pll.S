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
#ifndef _MACRO_INC_
#include "macro.inc"
#endif

    .text
    .global     BootRom_InitPll

BootRom_InitPll:

    @Module: adc_atop (0x1025)
    .if (BOOTING_FROM_EXT_SPI_WITH_PM51 != 1)
    WREG_B  0x1F204A1C, 0x3F
    WREG_B  0x1F204A1C, 0x00        @Release Soft-Reset for ADCA/PLLA/ADCB/PLLB/ATOP/Phase DAC

    WREG    0x1F204A10, 0x0000      @Power-On releated blocks in ATOP
    WREG    0x1F204A14, 0x0000
    WREG    0x1F204A18, 0x0000
    WREG    0x1F204AFC, 0x0030      @Enable SOG MUX

                                    @CVBS DAC
    WREG_B  0x1F204B20, 0x08        @Enable IDAC (Ch1)
    WREG_B  0x1F204B24, 0x08        @Enable IDAC (Ch2)
                                    @CVBSO
    WREG_B  0x1F204B40, 0x00        @Enable CVBSO1
    WREG_B  0x1F204B48, 0x00        @Enable CVBSO2

    @Module: dvi_atop (0x1109)
    WREG    0x1F221218, 0x0000      @Relase soft-reset for DVI/HDMI/HDCP blocks
    WREG    0x1F221380, 0x0000      @Power-on for DVI/HDMI/HDCP blocks
    WREG    0x1F2213A4, 0x0000      @Power-on for DVT port 2
    WREG    0x1F22120C, 0x0000      @Enable clock for related dvi_atop IPs
    WREG    0x1F22139C, 0x4000      @Port A/C: ENAUTO
    WREG    0x1F221394, 0x3000      @Port A/C: TEST_CMP[1:0]
    WREG    0x1F2213FC, 0x0000      @A1 added

    @Module: dvi_atop1 (0x1132)
    WREG    0x1F226418, 0x0000
    WREG    0x1F226580, 0x0000
    WREG    0x1F22659C, 0x4000      @Port B: ENAUTO
    WREG    0x1F226594, 0x3000      @Port B: TEST_CMP[1:0]
    WREG    0x1F2265D0, 0x0000      @A1 added

    @Module: dvi_atop2 (0x1134)
    WREG    0x1F226818, 0x0000
    WREG    0x1F226980, 0x0000
    WREG    0x1F22699C, 0x4000      @Port D: ENAUTO
    WREG    0x1F226994, 0x3000      @Port D: TEST_CMP[1:0]
    WREG    0x1F2269D0, 0x0000      @A1 added

    @Module: pm_sleep (0x000E)
    WREG    0x1F001D28, 0x0000      @Power-on dvi_atop in PM_SLEEP
    WREG    0x1F001D2C, 0x0000


    @Module: chiptop (0x101E)
    WREG_B  0x1F203C70, 0x00        @Power-on for PD_3P3_1, PD_3P3_0 and PD_3P3_USB1

    @Module: ana_misc (0x110C)
                                    @MPLL
    WREG    0x1F221804, 0x0000      @MPLL enable
    .endif
                                    @MIPSPLL
    WREG_B  0x1F221845, 0x00        @MIPSPLL enable  address check again  --> wriu  0x110c23  0x00

    @(formula:frequency = 12MHz * (16bit_address_0x13[7:0])

    .if (CPU_CLOCK == 432)
    WREG_B  0x1F22184C, 0x24
    .endif

    .if (CPU_CLOCK == 456)
    WREG_B  0x1F22184C, 0x26
    .endif

    .if (CPU_CLOCK == 504)
    WREG_B  0x1F22184C, 0x2A
    .endif

    .if (CPU_CLOCK == 600)
    WREG_B  0x1F22184C, 0x32
    .endif

    .if (CPU_CLOCK == 672)
    WREG_B  0x1F22184C, 0x38
    .endif

    .if (CPU_CLOCK == 684)
    WREG_B  0x1F22184C, 0x39
    .endif

    .if (CPU_CLOCK == 696)
    WREG_B  0x1F22184C, 0x3A
    .endif

    .if (CPU_CLOCK == 708)
    WREG_B  0x1F22184C, 0x3B
    .endif

    .if (CPU_CLOCK == 720)
    WREG_B  0x1F22184C, 0x3C
    .endif

    .if (CPU_CLOCK == 756)
    WREG_B  0x1F22184C, 0x3F
    .endif

    .if (CPU_CLOCK == 780)
    WREG_B  0x1F22184C, 0x41        @MIPSPLL enable --> 780MHz for bring up
    .endif

    .if (CPU_CLOCK == 840)
    WREG_B  0x1F22184C, 0x46        @MIPSPLL enable --> 840MHz for bring up
    .endif

    .if (CPU_CLOCK == 852)
    WREG_B  0x1F22184C, 0x47        @MIPSPLL enable --> 852MHz for bring up
    .endif

    .if (CPU_CLOCK == 864)
    WREG_B  0x1F22184C, 0x48        @MIPSPLL enable --> 864MHz for bring up
    .endif

    .if (CPU_CLOCK == 876)
    WREG_B  0x1F22184C, 0x49        @MIPSPLL enable --> 876MHz for bring up
    .endif

    .if (CPU_CLOCK == 888)
    WREG_B  0x1F22184C, 0x4A        @MIPSPLL enable --> 888MHz for bring up
    .endif

    .if (CPU_CLOCK == 900)
    WREG_B  0x1F22184C, 0x4B        @MIPSPLL enable --> 900MHz for bring up
    .endif

    .if (CPU_CLOCK == 1008)
    WREG_B  0x1F22184C, 0x54        @MIPSPLL enable --> 1008MHz for bring up
    .endif

    .if (CPU_CLOCK == 1152)
    WREG_B  0x1F22184C, 0x60        @MIPSPLL enable --> 1152MHz for bring up
    .endif

    WREG_B  0x1F22184C, (CPU_CLOCK / 12)


    .if (BOOTING_FROM_EXT_SPI_WITH_PM51 != 1)
    WREG_B   0x1F201674, 0x01
                                    @MIU_128bit PLL  (default =~ 300 MHz)
                                    @MIU_256bit PLL  (default =~ 264 MHz)
    WREG    0x1F2218C4, 0x0000      @MIU_128BUS_PLL power on
    WREG    0x1F2218E4, 0x0000      @MIU_256BUS_PLL power on
    WREG    0x1F201674, 0x0809      @turn on clk_miu & select clk_miu = MIU_128bit_PLL_VCO
                                    @turn on clk_miu_256bus & select clk_miu_256bus = MIU_256bit_PLL_VCO
    WREG    0x1F2218E8, 0x0120
    WREG    0x1F2218EC, 0x0058
    WREG    0x1F2218C8, 0x0120
    WREG    0x1F2218CC, 0x0032

    DELAYUS     1000

    .endif
                                    @DSP PLL
    WREG    0x1F221884, 0x0001      @MPLL enable
    WREG_B  0x1F22188C, 0x3f        @DSPPLL_VCO_OUT =~ 378 MHz

    @Module: usb0 (0x1007)
    WREG_B  0x1F200E00, 0x0a        @Disable MAC initial suspend, Reset UHC
    WREG_B  0x1F200E00, 0x28        @Release UHC reset, enable UHC and OTG XIU function

    @Module: utmi (0x103A)
    WREG    0x1F207544, 0x2088      @ PLL_TEST[30:28]: 3'b010 for IBIAS current select
                                    @ PLL_TEST[23] CLK480 to digital output source selection
    WREG    0x1F207540, 0x8051      @ PLL_TEST[15]: Bypass 480MHz clock divider
                                    @ PLL_TEST[7:4]: 5'b0101_0 for 1.0x
                                    @ PLL_TEST[0]: 1: synthesizer clock, 2'b11, 0: XIN_C

    WREG    0x1F207504, 0x2084      @ Enable CLK12_SEL bit <2> for select low voltage crystal clock
@    WREG    0x1F207510, 0x0000      @ #7=0 Enable band-gap current  #3=0 Disable force_pll_on
    @ 0x0007 for Edison
    WREG    0x1F207510, 0x0007      @ bit <0:1> defulat 2'b11, bit<2> XTAL enable
    WREG    0x1F207500, 0x6bc3      @ reg_pdn: bit<15>, bit <2> ref_pdn # Turn on reference voltage and regulator
    DELAYUS     1000

    WREG    0x1F207500, 0x69c3      @ Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000

    WREG    0x1F207500, 0x0001      @ Turn all (including hs_current) use override mode

    @Module: usb1 (0x1007)
    WREG_B  0x1F200F00, 0x0a        @ Disable MAC initial suspend, Reset UHC
    WREG_B  0x1F200F00, 0x28        @ Release UHC reset, enable UHC and OTG XIU function

    @Module: utmi1 (0x103A)
    WREG    0x1F207444, 0x2088      @ PLL_TEST[30:28]: 3'b010 for IBIAS current select
                                    @ PLL_TEST[23] CLK480 to digital output source selection
    WREG    0x1F207440, 0x8051      @ PLL_TEST[15]: Bypass 480MHz clock divider
                                    @ PLL_TEST[7:4]: 5'b0101_0 for 1.0x
                                    @ PLL_TEST[0]: 1: synthesizer clock, 2'b11, 0: XIN_C

    WREG    0x1F207404, 0x2084      @ Enable CLK12_SEL bit <2> for select low voltage crystal clock
@    WREG    0x1F207410, 0x0000      @ Enable band-gap current
    @ modify to 0x0007 for Edison
    WREG    0x1F207410, 0x0007      @ bit <0:1> defulat 2'b11, bit<2> XTAL enable
    WREG    0x1F207400, 0x6bc3      @ reg_pdn: bit<15>, bit <2> ref_pdn  # Turn on reference voltage and regulator
    DELAYUS     1000

    WREG    0x1F207400, 0x69c3      @ Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000

    WREG    0x1F207400, 0x0001      @ Turn all (including hs_current) use override mode

    @USBC2 <--> UTMI2
    WREG_B  0x1F227000, 0x0a         @ Disable MAC initial suspend, Reset UHC
    WREG_B  0x1F227000, 0x68         @ Release UHC reset, enable UHC and OTG XIU function

    WREG    0x1F207244, 0x2088       @ Set PLL_TEST[23:21] for enable 480MHz clock
    WREG    0x1F207240, 0x8051
    WREG    0x1F207204, 0x2084       @ Enable CLK12_SEL bit <2> for select low voltage crystal clock
@    WREG    0x1F207210, 0x0000       @ Enable band-gap current
    @ modify 0x0007 for Edison
    WREG    0x1F207210, 0x0007       @ bit <0:1> defulat 2'b11, bit<2> XTAL enable
    WREG    0x1F207200, 0x6bc3       @ reg_pdn: bit<15>, bit <2> ref_pdn  # Turn on reference voltage and regulator
    DELAYUS 1000

    WREG    0x1F207200, 0x69c3       @ Turn on UPLL, reg_pdn: bit<9>
    DELAYUS 2000

    WREG    0x1F207200, 0x0001       @ Turn all (including hs_current) use override mode

    bx          lr

    .size       BootRom_InitPll,.-BootRom_InitPll

    .end

