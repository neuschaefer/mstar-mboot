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
#// turn on MainPLL, MIPSLL and VEPLL
#// swch 4

#// MainPLL : DMPLL

    WREG (REG_ADDR_BASE + (0x101e38 <<1 )) , 0x0000   #//reg_dmdtop_dmd_sel@0x1c[8]=0
    WREG (REG_ADDR_BASE + (0x112002 <<1 )) , 0x0000   #//reg_dmd_ana_misc_rst@0x01[13] reg_dmdtop =0
    WREG (REG_ADDR_BASE + (0x11286a <<1 )) , 0x1e03   #//reg_mpll_pd@0x35[7]=0
    DELAYUS 1000                                      #//wait 1  // delay 1ms
    WREG (REG_ADDR_BASE + (0x11286a <<1 )) , 0x0603   #//reg_mpll_pd@0x35[7]=0
    DELAYUS 1000                                      #//wait 1  // delay 1ms
    WREG (REG_ADDR_BASE + (0x112866 <<1 )) , 0x1201   #//reg_pwdn_ref@0x20[4]=0
    WREG (REG_ADDR_BASE + (0x112860 <<1 )) , 0x1c01   #//reg_pwdn_adci@0x0c[0]=0, reg_pwdn_adcq@0x0c[1]=0, reg_pwdn_clpbuf@0x0c[2]=0
    WREG (REG_ADDR_BASE + (0x112840 <<1 )) , 0x0000   #//reg_dmldo_en@0x3c[12]=1
    WREG_B (REG_ADDR_BASE + (0x112879 <<1 )-1) , 0x00   #//reg_mpll_divX_pd@0x30[9:1]=0, reg_mpll_adc_div_sel@0x30[15:10]=6'h09=6'd09
    WREG (REG_ADDR_BASE + (0x101e38 <<1 )) , 0x0300   #//reg_mpll_loop_div_second@0x33[15:8]=8'h24=8'd36

#// IP: DEMOD
#// [2:0] : reg_mpll_ictrl   set 3'h3
#// [3]   : reg_mpll_in_sel  set 1'h0
#// [4]   : reg_mpll_xtal2adc_sel if 1'h1 ADC_CLK=XTAL.
#// [5]   : reg_mpll_xtal2next_pll_sel
#// [6]   : reg_mpll_vco_offset(T8), reg_mpll_adc_clk_cc_mode(T9)
#// [7]   : reg_mpll_pd      set 1'b1
#// [8]   : reg_xtal_en      set 1'b0
#// [10:9]: reg_xtal_sel     set 2'h3 XTAL strength
#// [11]  : reg_mpll_porst   set 1'b1
#// [12]  : reg_mpll_reset   set 1'b1
#// [13]  : reg_pd_dmpll_clk XTAL to MPLL clock reference power down
#// [14]  : reg_pd_3p3_1     XTAL to CLK_24M_3P3_1 power down
#// [15]  : reg_pd_3p3_2     XTAL to CLK_24M_3P3_2 power down
#// Set MPLL_RESET=MPLL_PORST=1
#// `M3_RIU_W((`RIUBASE_DMD_ANA_MISC_M3>>1)+7'h35, 2'b11, 16'h1e03);
    WREG_B (REG_ADDR_BASE + (0x11286b <<1 )-1) , 0x1e
    WREG_B (REG_ADDR_BASE + (0x11286a <<1 )) , 0x03

#// #20
#//wait 0
    DELAYUS 0
#// Set MPLL_RESET=MPLL_PORST=0
#// `M3_RIU_W((`RIUBASE_DMD_ANA_MISC_M3>>1)+7'h35, 2'b11, 16'h0603);
    WREG_B (REG_ADDR_BASE + (0x11286b << 1 )-1) , 0x06
    WREG_B (REG_ADDR_BASE + (0x11286a << 1 )) , 0x03
#// #10000;
#//wait 1
    DELAYUS 1000

#// DVBC : 24*36/19=45.47 MHz
#// Set MPLL_LOOP_DIV_FIRST and SECOND
#// [1:0] : reg_mpll_loop_div_first : feedback divider
#//         00:div by 1
#//         01:div by 2
#//         10:div by 4
#//         11:div by 8
#// [15:8]: reg_mpll_loop_div_second
#// `M3_RIU_W((`RIUBASE_DMD_ANA_MISC_M3>>1)+7'h33, 2'b11, 16'h1201);
    WREG_B (REG_ADDR_BASE + (0x112867 <<1 )-1) , 0x12
    WREG_B (REG_ADDR_BASE + (0x112866 <<1 )) , 0x01


#// Set MPLL_ADC_DIV_SE
#// [0]   : reg_mpll_clk_dp_pd(T8)/reg_mpll_adc_clk_cc_en(T9)
#// [1]   : reg_adc_clk_pd
#// [2]   : reg_mpll_div2_pd
#// [3]   : reg_mpll_div3_pd
#// [4]   : reg_mpll_div4_pd
#// [5]   : reg_mpll_div8_pd
#// [6]   : reg_mpll_div10_pd
#// [13:8]: reg_mpll_adc_div_sel set 6'd19
#// `M3_RIU_W((`RIUBASE_DMD_ANA_MISC_M3>>1)+7'h30, 2'b11, 16'h1e01);
    WREG_B (REG_ADDR_BASE + (0x112861 <<1 )-1) , 0x1e
    WREG_B (REG_ADDR_BASE + (0x112860 <<1 )) , 0x01




#// MIPSPLL
    WREG (REG_ADDR_BASE + (0x110C30 <<1 )) , 0x0065   #//clr bit4, disable power down
    WREG (REG_ADDR_BASE + (0x110C30 <<1 )) , 0x0045   #//clr Bit5, disable reset
    WREG (REG_ADDR_BASE + (0x110C30 <<1 )) , 0x0005   #//clr bit6, disable power reset
    WREG (REG_ADDR_BASE + (0x110C2a <<1 )) , 0x000f   #//Enable clk_mips

#// Output frequency = 24MHz / (2^reg_mipspll_input_div1) * (2^reg_mipspll_loop_div1) * reg_mipspll_loop_div2 / 2 / (2^ reg_mipspll_output_div1)
#// Reg_mipspll_input_div1 must be 2'b10
#// Reg_mipspll_loop_div1 must be 2'b10
#if (ENABLE_CPU_792MHZ)
#// 792 MHz
WREG (REG_ADDR_BASE + (0x110C32 <<1 )) , 0x000a   #//output_div1
WREG (REG_ADDR_BASE + (0x110C34 <<1 )) , 0x0042   #//loop_div2
#elif (ENABLE_CPU_852MHZ)
#// 852 MHz
WREG (REG_ADDR_BASE + (0x110C32 <<1 )) , 0x000a   #//output_div1
WREG (REG_ADDR_BASE + (0x110C34 <<1 )) , 0x0047   #//loop_div2
#elif (ENABLE_CPU_936MHZ)
#// 936 MHz
WREG (REG_ADDR_BASE + (0x110C32 <<1 )) , 0x000a   #//output_div1
WREG (REG_ADDR_BASE + (0x110C34 <<1 )) , 0x004e   #//loop_div2
#else
#error "Invalid CPU Frequency Selection"
#endif

#// VEPLL
    WREG (REG_ADDR_BASE + (0x1031b8 <<1 )) , 0x001c   #// [1]reg_aupll_pd_kp0, [0]reg_aupll_pd

#// DACPLL
    WREG_B (REG_ADDR_BASE + (0x110e02 <<1 )) , 0x01   #// Set MPLL_432
    WREG_B (REG_ADDR_BASE + (0x110e03 <<1 )-1) , 0x00
    WREG_B (REG_ADDR_BASE + (0x12112a <<1 )) , 0x00   #// Set DACPLL
    WREG_B (REG_ADDR_BASE + (0x12112d <<1 )-1) , 0x06
    WREG_B (REG_ADDR_BASE + (0x12112e <<1 )) , 0x07
    WREG_B (REG_ADDR_BASE + (0x12112f <<1 )-1) , 0x08
    WREG_B (REG_ADDR_BASE + (0x121162 <<1 )) , 0x99   #// Set dac synth
    WREG_B (REG_ADDR_BASE + (0x121163 <<1 )-1) , 0x99
    WREG_B (REG_ADDR_BASE + (0x121164 <<1 )) , 0x19
    WREG_B (REG_ADDR_BASE + (0x121165 <<1 )-1) , 0x00
    WREG_B (REG_ADDR_BASE + (0x12116a <<1 )) , 0x00
    WREG_B (REG_ADDR_BASE + (0x12116b <<1 )-1) , 0x00
    WREG_B (REG_ADDR_BASE + (0x121166 <<1 )) , 0x07
    WREG_B (REG_ADDR_BASE + (0x121167 <<1 )-1) , 0x00
    WREG_B (REG_ADDR_BASE + (0x121166 <<1 )) , 0x00
    WREG_B (REG_ADDR_BASE + (0x121168 <<1 )) , 0x45
    WREG_B (REG_ADDR_BASE + (0x121169 <<1 )-1) , 0x04

    #Disable idac to prevent CVBS output color bar
    #WREG (REG_ADDR_BASE + (0x101a00 <<1 )) , 0x0011   #// Enable idac
    #WREG (REG_ADDR_BASE + (0x101a06 <<1 )) , 0x0007

#// DSPPLL
    WREG_B (REG_ADDR_BASE + (0x1128a2 <<1 )) , 0x01
    WREG_B (REG_ADDR_BASE + (0x110c82 <<1 )) , 0x00
    WREG_B (REG_ADDR_BASE + (0x110c83 <<1 )-1) , 0x00
    WREG_B (REG_ADDR_BASE + (0x110c88 <<1 )) , 0x00
    WREG_B (REG_ADDR_BASE + (0x110c89 <<1 )-1) , 0x01
    WREG_B (REG_ADDR_BASE + (0x110c8a <<1 )) , 0x4c
    WREG_B (REG_ADDR_BASE + (0x110c8b <<1 )-1) , 0x00

#// HDMITX PLL
    WREG_B (REG_ADDR_BASE + (0x110102 <<1 )) , 0x01

#// TXPLL (216Mhz for 480p)
#//WREG (REG_ADDR_BASE + (0x103350 <<1 )) , 0x0000   #// enable clk_hdmi_tx_p
#//WREG (REG_ADDR_BASE + (0x11303c <<1 )) , 0xffff   #// clkgen enable
#//WREG (REG_ADDR_BASE + (0x11308a <<1 )) , 0x0000   #// power on synth pll
#//WREG (REG_ADDR_BASE + (0x113066 <<1 )) , 0x0000   #// power on tx pll
#//WREG (REG_ADDR_BASE + (0x113054 <<1 )) , 0x0000   #// power on tm atop
#//WREG (REG_ADDR_BASE + (0x11305c <<1 )) , 0x000f   #// enable tm atop

#//WREG (REG_ADDR_BASE + (0x113056 <<1 )) , 0x0000   #// power on tm atop on tm_reg
#//WREG (REG_ADDR_BASE + (0x113058 <<1 )) , 0x0000   #// power on tm atop on tm_reg

#//WREG (REG_ADDR_BASE + (0x113000 <<1 )) , 0x0080   #// software reset synthesizer
#//WREG (REG_ADDR_BASE + (0x113000 <<1 )) , 0x0000
#//WREG (REG_ADDR_BASE + (0x113100 <<1 )) , 0x0804   #// [12]: BYPASS_DC_FIFO, [11]: REG_HPLL_LOCK_CHK, [10]: REG_DC_FIFO_RST, [9:8]: START_DE_PH
                                                     #// [7:6]: REG_DC_MODE, [5]: REG_EN_CLAMP, [4]: PKT_MANUAL_MODE, [3]: REG_USER_ENABLE, [2]: REG_EN_PKT, [1]: REG_PHYMODE, [0]: REG_DVIMODE

#// HDMITX setting (8bits 1080p)
#// synthesizer clock setting
    WREG_B (REG_ADDR_BASE + (0x11308c <<1 )) , 0x4a
    WREG_B (REG_ADDR_BASE + (0x11308d <<1 )-1) , 0x29
    WREG_B (REG_ADDR_BASE + (0x11308e <<1 )) , 0x25
    WREG_B (REG_ADDR_BASE + (0x11308f <<1 )-1) , 0x00
    DELAYUS 2000                                      #//wait 2

#// analog setting
    WREG_B (REG_ADDR_BASE + (0x113054 <<1 )) , 0x00
    WREG_B (REG_ADDR_BASE + (0x113055 <<1 )-1) , 0x00   #// [3:0] : reg_tm_pdn
                                                  #// [4] : reg_tm_reset
                                                  #// [5] : reg_tm_pd_refgen
                                                  #// [11:8] : reg_tm_bist
                                                  #// [14] : reg_tm_detect

    WREG_B (REG_ADDR_BASE + (0x113056 <<1 )) , 0x00
    WREG_B (REG_ADDR_BASE + (0x113057 <<1 )-1) , 0x00   #// [15:0] : reg_tm_reg_15_0

    WREG_B (REG_ADDR_BASE + (0x113058 <<1 )) , 0x00
    WREG_B (REG_ADDR_BASE + (0x113059 <<1 )-1) , 0x00   #// [15:0] : reg_tm_reg_31_16

    WREG_B (REG_ADDR_BASE + (0x11305c <<1 )) , 0x0f
    WREG_B (REG_ADDR_BASE + (0x11305d <<1 )-1) , 0x00   #// [3:0] reg_tm_dinen_async
                                                  #// [7:4] reg_tm_precon
                                                  #// [11:8] reg_tm_pren

    WREG_B (REG_ADDR_BASE + (0x11305e <<1 )) , 0x00
    WREG_B (REG_ADDR_BASE + (0x11305f <<1 )-1) , 0x00   #// [3:0] reg_tm_tenpre
                                                  #// [7:4] reg_tm_ten
                                                  #// [12:8] reg_override_value
                                                  #// [13] reg_rctrl_ph_rd_en
                                                  #// [14] reg_dvi_ovride
                                                  #// [15] reg_dvi_init_en

    WREG_B (REG_ADDR_BASE + (0x113066 <<1 )) , 0x30
    WREG_B (REG_ADDR_BASE + (0x113067 <<1 )-1) , 0x00   #// [6:4] : reg_dvipll_ictl
                                                  #//[7] : reg_dvipll_pd
                                                  #//[8] : reg_dvipll_pdbg
                                                  #//[9] : reg_dvipll_vco_offset
                                                  #//[10] : reg_dvipll_porst
                                                  #//[11] : reg_dvipll_reset
                                                  #//[12] : reg_dvipll_pdreg
                                                  #//[13] : reg_dvipll_dac_mode_en

    WREG_B (REG_ADDR_BASE + (0x113068 <<1 )) , 0x00
    WREG_B (REG_ADDR_BASE + (0x113069 <<1 )-1) , 0x00   #//[15:0] : reg_dvipll_test

    WREG_B (REG_ADDR_BASE + (0x113070 <<1 )) , 0x60
    WREG_B (REG_ADDR_BASE + (0x113071 <<1 )-1) , 0x60   #//[1:0] reg_dvipll_regsel
                                                  #//[3:2] reg_dvipll_tx_div
                                                  #//[7:4] reg_dvipll_loop_div
                                                  #//[12:8] reg_dvipll_dr_div
                                                  #//[15:13] reg_dvipll_dac_div

#// UPLL
    WREG_B (REG_ADDR_BASE + (0x103a88 <<1 )) , 0x0f
    WREG_B (REG_ADDR_BASE + (0x103aa0 <<1 )) , 0x51
    WREG_B (REG_ADDR_BASE + (0x103aa1 <<1 )-1) , 0x80
    WREG_B (REG_ADDR_BASE + (0x103aa2 <<1 )) , 0x88
    WREG_B (REG_ADDR_BASE + (0x103aa3 <<1 )-1) , 0x20
    WREG_B (REG_ADDR_BASE + (0x103a81 <<1 )-1) , 0x6b
    WREG_B (REG_ADDR_BASE + (0x103a80 <<1 )) , 0xc3
    DELAYUS 1000                                      #//wait 1   // delay 1ms

    WREG_B (REG_ADDR_BASE + (0x103a81 <<1 )-1) , 0x69
    DELAYUS 2000                                      #//wait 2   // delay 2ms

    WREG_B (REG_ADDR_BASE + (0x103a80 <<1 )) , 0x01   #// Turn all (including hs_current) use override mode
    WREG_B (REG_ADDR_BASE + (0x103a81 <<1 )-1) , 0x00

#// USBC2
    WREG_B (REG_ADDR_BASE + (0x103a08 <<1 )) , 0x0f
    WREG_B (REG_ADDR_BASE + (0x103a20 <<1 )) , 0x51
    WREG_B (REG_ADDR_BASE + (0x103a21 <<1 )-1) , 0x80
    WREG_B (REG_ADDR_BASE + (0x103a22 <<1 )) , 0x88
    WREG_B (REG_ADDR_BASE + (0x103a23 <<1 )-1) , 0x20
    WREG_B (REG_ADDR_BASE + (0x103a01 <<1 )-1) , 0x6b
    WREG_B (REG_ADDR_BASE + (0x103a00 <<1 )) , 0xc3
    DELAYUS 1000                                      #//wait 1   // delay 1ms

    WREG_B (REG_ADDR_BASE + (0x103a01 <<1 )-1) , 0x69
    DELAYUS 2000                                      #//wait 2   // delay 2ms

    WREG_B (REG_ADDR_BASE + (0x103a00 <<1 )) , 0x01
    WREG_B (REG_ADDR_BASE + (0x103a01 <<1 )-1) , 0x00

    WREG_B (REG_ADDR_BASE + (0x103a2c <<1 )) , 0x23   #//improve eye pattern
    WREG_B (REG_ADDR_BASE + (0x103aac <<1 )) , 0x23

    jr          ra
    nop

    .size       BootRomInitPll,.-BootRomInitPll
    .end        BootRomInitPll

