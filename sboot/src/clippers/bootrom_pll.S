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



@//================================================================================================
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x110C00 << 1))
    ldr         r0, =0x00
    strb        r0, [r1, #((0x02 << 1)+1)]                      @//MPLL enable
    ldr         r0, =0x00
    strb        r0, [r1, #(0x0A << 1)]                          @//MPLL CLK_33 power on
    ldr         r0, =0x0c
    strb        r0, [r1, #((0x12 << 1)+1)]                      @//PD_MPLL=0	 PD_MPLL_CLK_ADC_VCO_DIV2=0

@//================================================================================================
    
    ldr         r0, =0x00
    strb        r0, [r1, #((0x22 << 1)+1)]                      @//reg_mipspll_pd = 0
    
#ifdef CONFIG_MSTAR_DVFS_ENABLE
    ldr         r0, =(CONFIG_DVFS_CPU_CLOCK_INIT & 0xFFFF)
    str         r0, [r1, #(0XC0 << 1)]
    ldr         r0, =((CONFIG_DVFS_CPU_CLOCK_INIT >> 16) & 0xFFFF)
    str         r0, [r1, #(0XC2 << 1)]
    
#else
    ldr         r0, =(CONFIG_CPU_CLOCK & 0xFFFF)
    str         r0, [r1, #(0XC0 << 1)]
    ldr         r0, =((CONFIG_CPU_CLOCK >> 16) & 0xFFFF)
    str         r0, [r1, #(0XC2 << 1)]

#endif
    ldr         r0, =0x0001
    str         r0, [r1, #(0xC4 << 1)]
       

@//================================================================================================
   
#if !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    WREG        (MS_BUS_RIU_ADDR + (0x110C62 << 1)), 0x0001     @//MIU_128BUS_PLL power on                                                     
    WREG        (MS_BUS_RIU_ADDR + (0x110C72 << 1)), 0x0001     @//MIU_256BUS_PLL power on
	
#else
    ldr         r0, =0x0000
    str         r0, [r1, #(0x64 << 1)]                          @//MIU_128BUS_PLL power on
    ldr         r0, =0x0019
    str         r0, [r1, #(0x66 << 1)]                          @//MIU_128BUS_PLL power on
    ldr         r0, =0x0001
    str         r0, [r1, #(0x62 << 1)]                          @//MIU_128BUS_PLL power on
    
    ldr         r2, =(MS_BUS_RIU_ADDR + (0x101800 << 1))
    ldr         r0, =0x04
    strb        r0, [r2, #(0x82 << 1)]                          @//Switch L3 CLK to xtal
    ldr         r0, =0x0200
    str         r0, [r1, #(0x74 << 1)]                          @//MIU_256BUS_PLL power on
    ldr         r0, =0x000b
    str         r0, [r1, #(0x76 << 1)]                          @//MIU_256BUS_PLL power on
    ldr         r0, =0x0001
    str         r0, [r1, #(0x72 << 1)]                          @//MIU_256BUS_PLL power on
    
#endif
@//================================================================================================
@// initial UPLL ===================================================================================
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x100800 << 1))
    ldr         r0, =0x0110
    str         r0, [r1, #(0x04 << 1)]                          @// UPLL0 enable
    ldr         r0, =0x0110
    str         r0, [r1, #(0x24 << 1)]                          @// UPLL1 enable
    ldr         r0, =0x1090
    str         r0, [r1]                                        @// UPLL0 enable
    ldr         r0, =0x01
    strb        r0, [r1, #(0x0E << 1)]                          @// enable 384MHz clk from UPLL0 (EVD HVD)
    ldr         r0, =0x1090
    str         r0, [r1, #(0x20 << 1)]                          @// UPLL1 enable
    
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x103A00 << 1))
    ldr         r0, =0x040F
    str         r0, [r1, #(0x88 << 1)]                          @// UTMI0
    ldr         r0, =0x7F05 
    str         r0, [r1, #(0x80 << 1)]
    ldr         r0, =0x040F
    str         r0, [r1, #(0x08 << 1)]                          @// UTMI1
    ldr         r0, =0x7F05
    str         r0, [r1]
    
    ldr         r2, =(MS_BUS_RIU_ADDR + (0x103900 << 1))
    ldr         r0, =0x040F       
    str         r0, [r2, #(0x08 << 1)]                           @// UTMI2
    ldr         r0, =0x7F05
    str         r0, [r2]                    
    
@// initial USBPLL ===================================================================================
                                                                @//Module: usb0 (0x100700)
    ldr         r3, =(MS_BUS_RIU_ADDR + (0x100700 << 1))                                                            
    ldr         r0, =0x0a               
    strb        r0, [r3]                                        @//Disable MAC initial suspend, Reset UHC
    ldr         r0, =0x28       
    strb        r0, [r3]                                        @//Release UHC reset, enable UHC and OTG XIU function                                       
                                                                @//Module: utmi0 (0x103A80)
    ldr         r0, =0x2088       
    str         r0, [r1, #(0xA2 << 1)]                          @//PLL_TEST[30:28]: 3'b101 for IBIAS current select
    ldr         r0, =0x8051       
    str         r0, [r1, #(0xA0 << 1)]                          @//PLL_TEST[15]: Bypass 480MHz clock divider
    ldr         r0, =0x2084       
    str         r0, [r1, #(0x82 << 1)]                          @//Enable CLK12_SEL bit <2> for select low voltage crystal clock
    ldr         r0, =0x0406       
    str         r0, [r1, #(0x88 << 1)]                          @//bit<7>: Power down UTMI port-0 bandgap current
    ldr         r0, =0x6bc3       
    str         r0, [r1, #(0x80 << 1)]                          @//reg_pdn: bit<15>, bit <2> ref_pdn # Turn on reference voltage and regulator
    DELAYUS     1000
    ldr         r0, =0x69c3       
    str         r0, [r1, #(0x80 << 1)]                          @//Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000
    ldr         r0, =0x0001       
    str         r0, [r1, #(0x80 << 1)]                          @//Turn all (including hs_current) use override mode

@//================================================================================================
                                                                @//Module: usb1 (0x100780)                                                         
    ldr         r0, =0x0a               
    strb        r0, [r3]                                        @//Disable MAC initial suspend, Reset UHC
    ldr         r0, =0x28       
    strb        r0, [r3]                                        @//Release UHC reset, enable UHC and OTG XIU function 
                                          
                                                                @//Module: utmi1 (0x103A00)
    ldr         r0, =0x2088       
    str         r0, [r1, #(0x22 << 1)]                          @//PLL_TEST[30:28]: 3'b101 for IBIAS current select
    ldr         r0, =0x8051       
    str         r0, [r1, #(0x20 << 1)]                          @//PLL_TEST[15]: Bypass 480MHz clock divider
    ldr         r0, =0x2084       
    str         r0, [r1, #(0x02 << 1)]                          @//Enable CLK12_SEL bit <2> for select low voltage crystal clock
    ldr         r0, =0x0406       
    str         r0, [r1, #(0x08 << 1)]                          @//bit<7>: Power down UTMI port-0 bandgap current
    ldr         r0, =0x6bc3       
    str         r0, [r1]                                        @//reg_pdn: bit<15>, bit <2> ref_pdn # Turn on reference voltage and regulator
    DELAYUS     1000
    ldr         r0, =0x69c3       
    str         r0, [r1]                                        @//Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000
    ldr         r0, =0x0001       
    str         r0, [r1]                                        @//Turn all (including hs_current) use override mode  
    
                                                                @//Module: usb1 (0x100780

@//================================================================================================

                                                                @//Module: usb2 (0x113800) 
    ldr         r3, =(MS_BUS_RIU_ADDR + (0x113800 << 1))                                                                                                                    
    ldr         r0, =0x0a               
    strb        r0, [r3]                                        @//Disable MAC initial suspend, Reset UHC
    ldr         r0, =0x28       
    strb        r0, [r3]                                        @//Release UHC reset, enable UHC and OTG XIU function 
                                          
                                                                @//Module: utmi2 (0x103900)
    ldr         r0, =0x2088       
    str         r0, [r2, #(0x22 << 1)]                          @//PLL_TEST[30:28]: 3'b101 for IBIAS current select
    ldr         r0, =0x8051       
    str         r0, [r2, #(0x20 << 1)]                          @//PLL_TEST[15]: Bypass 480MHz clock divider
    ldr         r0, =0x2084       
    str         r0, [r2, #(0x02 << 1)]                          @//Enable CLK12_SEL bit <2> for select low voltage crystal clock
    ldr         r0, =0x0406       
    str         r0, [r2, #(0x08 << 1)]                          @//bit<7>: Power down UTMI port-0 bandgap current
    ldr         r0, =0x6bc3       
    str         r0, [r2]                                        @//reg_pdn: bit<15>, bit <2> ref_pdn # Turn on reference voltage and regulator
    DELAYUS     1000
    ldr         r0, =0x69c3       
    str         r0, [r2]                                        @//Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000
    ldr         r0, =0x0001       
    str         r0, [r2]                                        @//Turn all (including hs_current) use override mode  



@//================================================================================================

    bx          lr

    .size       BootRom_InitPll,.-BootRom_InitPll

    .end

