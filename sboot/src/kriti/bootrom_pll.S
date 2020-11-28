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
    .global     BootRomInitPll
    .ent        BootRomInitPll

BootRomInitPll:
# turn on MainPLL, MIPSLL
# swch 4

# MainPLL : DMPLL
    WREG_B (REG_ADDR_BASE + (0x000eca <<1 )) , 0x10   #enable LDO
    WREG (REG_ADDR_BASE + (0x101e38 <<1 )) , 0x0000   #reg_dmdtop_dmd_sel@0x1c[8]=0
    WREG (REG_ADDR_BASE + (0x112002 <<1 )) , 0x0070   #reg_dmd_ana_misc_rst@0x01[13] reg_dmdtop =0
    WREG (REG_ADDR_BASE + (0x11286a <<1 )) , 0x1e03   #reg_mpll_pd@0x35[7]=0
    WREG (REG_ADDR_BASE + (0x11286a <<1 )) , 0x0603
    WREG (REG_ADDR_BASE + (0x112866 <<1 )) , 0x1201
    WREG (REG_ADDR_BASE + (0x112860 <<1 )) , 0x1c01
    WREG (REG_ADDR_BASE + (0x112840 <<1 )) , 0x0000
    WREG (REG_ADDR_BASE + (0x112878 <<1 )) , 0x0000
    WREG (REG_ADDR_BASE + (0x101e38 <<1 )) , 0x0300

# MIPSPLL
    WREG (REG_ADDR_BASE + (0x110C34 <<1 )) , 0x0064     #PLL Freq = 0x64*6 = 600 MHz
    WREG (REG_ADDR_BASE + (0x110C30 <<1 )) , 0x0005
    WREG (REG_ADDR_BASE + (0x110c2a <<1 )) , 0x000f

# DSP_PLL
    WREG (REG_ADDR_BASE + (0x110c80 <<1 )) , 0x0028
    WREG (REG_ADDR_BASE + (0x110c82 <<1 )) , 0x0000

# Audio DSP Frequency
    WREG (REG_ADDR_BASE + (0x110C86 <<1 )) , 0x0038     #reg_mipspll_loop_div2
    //===========================================================
    // DACPLL
    //===========================================================
    WREG_B (REG_ADDR_BASE + (0x12112a <<1 )) , 0x00     #reg_dacpll_pd[0],
    WREG_B (REG_ADDR_BASE + (0x12112d <<1 )) , 0x06     #reg_dacpll_loop_div[11:8], reg_dacpll_dac_mode_en[4]
    WREG (REG_ADDR_BASE + (0x12112e <<1 )) , 0x0807     #reg_dacpll_dr_div  [4:0], reg_dacpll_pdreg[8], reg_dacpll_in_select[11]

    // dac synth
    WREG (REG_ADDR_BASE + (0x121162 <<1 )) , 0x9999     # [15:0] reg_synth_set_15_0
    WREG (REG_ADDR_BASE + (0x121164 <<1 )) , 0x0019     # [15:0] reg_synth_set_31_16
    WREG (REG_ADDR_BASE + (0x12116a <<1 )) , 0x0002     # [0] enable ssc 1: enalbe, 0:disable
                                   										// [1] ssc_sync
    WREG (REG_ADDR_BASE + (0x121166 <<1 )) , 0x0007     # step
    WREG (REG_ADDR_BASE + (0x121168 <<1 )) , 0x0445     # span

    WREG_B (REG_ADDR_BASE + (0x101a00 <<1 )) , 0x31     # [5] reg_sel_ext_hdclk, CLK_OUT_DAC is from DACPLL
                                                        # clk_spi = 54M (step_2/2) 
    //SYN_PLL
    WREG(REG_ADDR_BASE + (0x1031b8 <<1 ))  , 0x0000
    
    // UPLL (turn 480Mhz in USB)
    // USBC0 <--> UTMI0
    WREG_B(REG_ADDR_BASE + (0x100700 <<1 )) ,  0x0a     # Disable MAC initial suspend, Reset UHC
    WREG_B(REG_ADDR_BASE + (0x100700 <<1 )) ,  0x28     # Release UHC reset, enable UHC and OTG XIU function
    
    WREG(REG_ADDR_BASE + (0x103a88 <<1 ))  , 0x040f   
    WREG(REG_ADDR_BASE + (0x103aa0 <<1 ))  , 0x8051     # PLL_TEST[15]: Bypass 480MHz clock divide //PLL_TEST[7:4]: 5'b0101_0 for 1.0x //PLL_TEST[7:4]: 5'b0101_0 for 1.0x
    WREG(REG_ADDR_BASE + (0x103aa2 <<1 ))  , 0x2088     # PLL_TEST[30:28]: 3'b010 for IBIAS current select //PLL_TEST[23] CLK480 to digital output source selection
    WREG(REG_ADDR_BASE + (0x103a80 <<1 ))  , 0x6bc3     # reg_pdn: bit<15>, bit <2> ref_pdn # Turn on reference voltage and regulator
    
    DELAYUS    1000
    WREG(REG_ADDR_BASE + (0x103a80 <<1 ))  , 0x69c3     # Turn on UPLL, reg_pdn: bit<9>
    DELAYUS    1000
    
    WREG(REG_ADDR_BASE + (0x103a80 <<1 ))  , 0x0001     # Turn all (including hs_current) use override mode

    jr          ra
    nop

    .size       BootRomInitPll,.-BootRomInitPll
    .end        BootRomInitPll

