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

#ifndef _BOARD_H_
#include "Board.h"
#endif

#ifndef _DRV_MIU_STR_INIT_H_
#include "drv_miu_str_init.h"
#endif

#ifndef _MIUSEL_KENYA_2MIU_H_
#include "MIUSEL_KENYA_2MIU.h"
#endif

    .text
    .set    	noreorder
    .global     BootInitMiu_STR
    .ent        BootInitMiu_STR
BootInitMiu_STR:
    move        t7, ra
    
    PUTK        'D'
    PUTK        'C'
    PUTK        '_'
    PUTK        'O'
    PUTK        'N'
    PUTK        '\n'
    PUTK        '\r'

    #//================================================
    #// Start MIU re-init !!!
    #//================================================
    WREG        (REG_ADDR_BASE + (0x10121e << 1)), 0x0c01
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x0000

    WREG        (REG_ADDR_BASE + (0x101220 << 1)), 0x0000   #//miu initial
    WREG        (REG_ADDR_BASE + (0x10121e << 1)), 0x0c00
    WREG        (REG_ADDR_BASE + (0x10121e << 1)), 0x0c00
    WREG        (REG_ADDR_BASE + (0x10121e << 1)), 0x0c00
    WREG        (REG_ADDR_BASE + (0x10121e << 1)), 0x0c01   #//miu software reset
    WREG        (REG_ADDR_BASE + (0x10121e << 1)), 0x0c00
    WREG        (REG_ADDR_BASE + (0x101202 << 1)), 0x0000   #//dram type set as '0'
    WREG        (REG_ADDR_BASE + (0x101246 << 1)), 0xFFFE   #//mask group0
    WREG        (REG_ADDR_BASE + (0x101266 << 1)), 0xFFFF   #//mask group1
    WREG        (REG_ADDR_BASE + (0x101286 << 1)), 0xFFFF   #//mask group2
    WREG        (REG_ADDR_BASE + (0x1012A6 << 1)), 0xFFFF   #//mask group3

    #//DRV
    WREG        (REG_ADDR_BASE + (0x110d5c << 1)), 0xdddd
    WREG        (REG_ADDR_BASE + (0x110d5e << 1)), 0xdddd

    #//TRIG LVL
    WREG        (REG_ADDR_BASE + (0x110d74 << 1)), 0x0055

#if (ENABLE_MEM1866MHz)
    #//--------------------
    #//set DDRPLL0 1866MHz
    #//--------------------
    #//DDR3 1.8Gbps
    WREG        (REG_ADDR_BASE + (0x110d36 << 1)), 0x4000
    WREG        (REG_ADDR_BASE + (0x110d34 << 1)), 0x0400
    WREG        (REG_ADDR_BASE + (0x110d30 << 1)), 0xa229
    WREG        (REG_ADDR_BASE + (0x110d32 << 1)), 0x001d   #//  WREG(0x110d36, 0x4003),
    WREG        (REG_ADDR_BASE + (0x110d22 << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x110d24 << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x110d24 << 1)), 0x3000
    WREG        (REG_ADDR_BASE + (0x110d24 << 1)), 0x2000
#elif (ENABLE_MEM1600MHz)

    #//--------------------
    #//set DDRPLL0 1600MHz
    #//--------------------
    #//DDR3 1.6Gbps
    WREG        (REG_ADDR_BASE + (0x110d36 <<1 )) , 0x4000
    WREG        (REG_ADDR_BASE + (0x110d34 <<1 )) , 0x0400
    WREG        (REG_ADDR_BASE + (0x110d30 <<1 )) , 0x8f5b
    WREG        (REG_ADDR_BASE + (0x110d32 <<1 )) , 0x0022   #//  WREG(0x110d36, 0x4003),
    WREG        (REG_ADDR_BASE + (0x110d22 <<1 )) , 0x0000
    WREG        (REG_ADDR_BASE + (0x110d24 <<1 )) , 0x0000
    WREG        (REG_ADDR_BASE + (0x110d24 <<1 )) , 0x3000
    WREG        (REG_ADDR_BASE + (0x110d24 <<1 )) , 0x2000
#elif (ENABLE_MEM1300MHz)
#error "Not support so far"

#else
#error "Invalid Memory Frequency Selection"
#endif
    #//------------------
    #// Wait PLL Stable
    #//------------------
    #// wait 10ms
    DELAYUS     10000

#if (ENABLE_MEM1866MHz)
    #//------------------------------
    #//set DDR3_16_8X_CL13_1866_2TCMD
    #//------------------------------
    #//===Miu_0 initial ddr3 1866MHz=================
    WREG        (REG_ADDR_BASE + (0x101202 << 1)), 0xf3a3   #//ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    WREG        (REG_ADDR_BASE + (0x101204 << 1)), 0x000b   #//if I64Mode =0x8b else =0x0b
    WREG        (REG_ADDR_BASE + (0x101206 << 1)), 0x0530   #//refresh cycle=0x20 ,TURN_ON_SCRAMBLE=0x8420
    WREG        (REG_ADDR_BASE + (0x101208 << 1)), 0x20dd   #//reg_tRCD
    WREG        (REG_ADDR_BASE + (0x10120a << 1)), 0x2d76   #//reg_tRRD
    WREG        (REG_ADDR_BASE + (0x10120c << 1)), 0xb7e9   #//reg_tWL
    WREG        (REG_ADDR_BASE + (0x10120e << 1)), 0x40f3   #//tRFC
    WREG        (REG_ADDR_BASE + (0x101210 << 1)), 0x1f14   #//MR0
    WREG        (REG_ADDR_BASE + (0x101212 << 1)), 0x4004   #//MR1 DDR3 ODT 120ohm
    WREG        (REG_ADDR_BASE + (0x101214 << 1)), 0x8020   #//MR2
    WREG        (REG_ADDR_BASE + (0x101216 << 1)), 0xC000   #//MR3
                                              
    #//======MIU_ATOP initial======
    WREG        (REG_ADDR_BASE + (0x110d02 << 1)), 0xaaaa   #//miu_0_atop  start
    WREG        (REG_ADDR_BASE + (0x110d04 << 1)), 0x0080   #//reg_drv_another_cmd / reg_drv_cmd
    WREG        (REG_ADDR_BASE + (0x110d14 << 1)), 0x3444   #//reg_sel_dqs_diff
    WREG        (REG_ADDR_BASE + (0x110d3c << 1)), 0x1444   #//SSC disable
    WREG        (REG_ADDR_BASE + (0x110d3e << 1)), 0x2044
    WREG        (REG_ADDR_BASE + (0x110d4c << 1)), 0x4444
    WREG        (REG_ADDR_BASE + (0x110d50 << 1)), 0x1111
    WREG        (REG_ADDR_BASE + (0x110d38 << 1)), 0x0044   #//Command driving
    WREG        (REG_ADDR_BASE + (0x110d3a << 1)), 0x6060   #
    WREG        (REG_ADDR_BASE + (0x110d48 << 1)), 0x0044
    WREG        (REG_ADDR_BASE + (0x110d4a << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x110d52 << 1)), 0x0002
    WREG        (REG_ADDR_BASE + (0x110d6c << 1)), 0x7777
    WREG        (REG_ADDR_BASE + (0x110d6e << 1)), 0x8788   #// updated by Jeffrey @20131228

    #//For ECO_U02 add setting
    WREG        (REG_ADDR_BASE + (0x110d7a << 1)), 0x0899   #// DDR_ECO_A[7:0] = 8'h99 (for AD3 drving); updated by Jeffrey @20131228// DDR_ECO_A[7:0] = 8'hdd (for AD3 drving)
    WREG        (REG_ADDR_BASE + (0x110d14 << 1)), 0xf444   #//[14] = SEL_MCLK1X_LDO_MCLK_A (0:CKE use original skew, 1:CKE skew = cmd_skew + 1)
                                                            #//[15] = SEL_MCLK1X_CKE_A (0:use original phase, 1:use ECO phase)
    WREG        (REG_ADDR_BASE + (0x110d4a << 1)), 0x0000   #//[7:4] = reg_clkph_dqsm2 (@U02 = CKE phase)

    #//-----------------------
    #//start to program DLL0
    #//-----------------------
    WREG        (REG_ADDR_BASE + (0x110d62 << 1)), 0x007f   #//reg_dll1_code	//refine when DDR_CLK change
    WREG        (REG_ADDR_BASE + (0x110d60 << 1)), 0x000c   #//reg_dll0_code	//refine when DDR_CLK change
    WREG        (REG_ADDR_BASE + (0x110d60 << 1)), 0x0008
    WREG        (REG_ADDR_BASE + (0x110d60 << 1)), 0x2370

#elif (ENABLE_MEM1600MHz)

    #//------------------------------
    #//set DDR3_16_8X_CL13_1600_2TCMD
    #//------------------------------
    #//===Miu_0 initial ddr3 1600MHz=================
    WREG        (REG_ADDR_BASE + (0x101202 <<1 )) , 0x03a3   #//ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    WREG        (REG_ADDR_BASE + (0x101204 <<1 )) , 0x000b   #//rd_timing//if I64Mode =0x8b else =0x0b
    WREG        (REG_ADDR_BASE + (0x101206 <<1 )) , 0x0430   #//refresh cycle=0x20 ,TURN_ON_SCRAMBLE=0x8420
    WREG        (REG_ADDR_BASE + (0x101208 <<1 )) , 0x1cbb   #//reg_tRCD
    WREG        (REG_ADDR_BASE + (0x10120a <<1 )) , 0x2765   #//reg_tRRD
    WREG        (REG_ADDR_BASE + (0x10120c <<1 )) , 0xa6c8   #//reg_tWL
    WREG        (REG_ADDR_BASE + (0x10120e <<1 )) , 0x40c0   #//tRFC

    WREG        (REG_ADDR_BASE + (0x101210 <<1 )) , 0x1d70   #//MR0
    WREG        (REG_ADDR_BASE + (0x101212 <<1 )) , 0x4004   #//MR1 DDR3 ODT 120ohm
    WREG        (REG_ADDR_BASE + (0x101214 <<1 )) , 0x8018   #//MR2
    WREG        (REG_ADDR_BASE + (0x101216 <<1 )) , 0xC000   #//MR3

    #//======MIU_ATOP initial======
    WREG        (REG_ADDR_BASE + (0x110d02 <<1 )) , 0xaaaa   #//miu_0_atop  start
    WREG        (REG_ADDR_BASE + (0x110d04 <<1 )) , 0x0080   #//reg_drv_another_cmd / reg_drv_cmd
    WREG        (REG_ADDR_BASE + (0x110d14 <<1 )) , 0x3222   #//reg_sel_dqs_diff, skew + 1, enable reg_en_odt_mask

    WREG        (REG_ADDR_BASE + (0x110d3c <<1 )) , 0x1200   #//SSC disable, skew + 1, DQSM skew changed by jeffrey 08/27
    WREG        (REG_ADDR_BASE + (0x110d3e <<1 )) , 0x2022   #//skew + 1
    WREG        (REG_ADDR_BASE + (0x110d4c <<1 )) , 0x2200   #//skew + 1
    WREG        (REG_ADDR_BASE + (0x110d50 <<1 )) , 0x1111
    WREG        (REG_ADDR_BASE + (0x110d38 <<1 )) , 0x0044   #//Command driving
    WREG        (REG_ADDR_BASE + (0x110d3a <<1 )) , 0x6060   #//DQSM phase changed by jeffrey 08/27
    WREG        (REG_ADDR_BASE + (0x110d48 <<1 )) , 0x0044
    WREG        (REG_ADDR_BASE + (0x110d4a <<1 )) , 0x0000
    WREG        (REG_ADDR_BASE + (0x110d52 <<1 )) , 0x0002   #//Update from Jeffrey @20131205
    WREG        (REG_ADDR_BASE + (0x110d6c <<1 )) , 0x7777
    WREG        (REG_ADDR_BASE + (0x110d6e <<1 )) , 0x8788   #//Updated by Jeffrey @20131228// read dq phase

    #//For ECO_U02 add setting
    WREG        (REG_ADDR_BASE + (0x110d7a << 1)), 0x0899    #/ DDR_ECO_A[7:0] = 8'h99 (for AD3 drving); updated by Jeffrey @20131228
    WREG        (REG_ADDR_BASE + (0x110d14 << 1)), 0xf222    #//[14] = SEL_MCLK1X_LDO_MCLK_A (0:CKE use original skew, 1:CKE skew = cmd_skew + 1)
                                                             #//[15] = SEL_MCLK1X_CKE_A (0:use original phase, 1:use ECO phase)
    WREG        (REG_ADDR_BASE + (0x110d4a << 1)), 0x0000    #//[7:4] = reg_clkph_dqsm2 (@U02 = CKE phase)

    #//-----------------------
    #//start to program DLL0
    #//-----------------------
    WREG        (REG_ADDR_BASE + (0x110d62 <<1 )) , 0x007f   #//reg_dll1_code	//refine when DDR_CLK change
    WREG        (REG_ADDR_BASE + (0x110d60 <<1 )) , 0x000c   #//reg_dll0_code	//refine when DDR_CLK change
    WREG        (REG_ADDR_BASE + (0x110d60 <<1 )) , 0x0008
    WREG        (REG_ADDR_BASE + (0x110d60 <<1 )) , 0x2370

#elif (ENABLE_MEM1300MHz)
#error "Not support so far"

#else
#error "Invalid Memory Frequency Selection"
#endif
                                    
    #//-------------
    #//Wait CAL Done
    #//-------------
    #//wait 20
    DELAYUS 20000
                                              
    #//-------------
    #// BW setting
    #//-------------
    WREG        (REG_ADDR_BASE + (0x101240 << 1)), 0x8015
    WREG        (REG_ADDR_BASE + (0x101260 << 1)), 0x8015
    WREG        (REG_ADDR_BASE + (0x101280 << 1)), 0x8015
    WREG        (REG_ADDR_BASE + (0x1012a0 << 1)), 0x8015
    
    #//---------------------------------
    #// Pack setting
    #//---------------------------------
    WREG        (REG_ADDR_BASE + (0x101228 << 1)), 0x4090
                                              
    #//-------------------------
    #// Reduce latency setting
    #//-------------------------
    WREG        (REG_ADDR_BASE + (0x10122a << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x1012d4 << 1)), 0x0000
                                              
    #//------------------------------
    #// sync in fifo stage
    #//------------------------------
    WREG        (REG_ADDR_BASE + (0x1012fc << 1)), 0x4000
                                              
    #//enable miu_0
    WREG        (REG_ADDR_BASE + (0x10121e << 1)), 0x0c01
    WREG        (REG_ADDR_BASE + (0x10121e << 1)), 0x0c00
    WREG        (REG_ADDR_BASE + (0x110d7c << 1)), 0x0000
#    WREG        (REG_ADDR_BASE + (0x110d00 << 1)), 0x0038
#    WREG        (REG_ADDR_BASE + (0x110d00 << 1)), 0x0030
#    WREG        (REG_ADDR_BASE + (0x110d00 << 1)), 0x0220
    WREG        (REG_ADDR_BASE + (0x110d7e << 1)), 0x0000
#    WREG        (REG_ADDR_BASE + (0x110d54 << 1)), 0xc000
    WREG        (REG_ADDR_BASE + (0x110d54 << 1)), 0xc070
#    WREG        (REG_ADDR_BASE + (0x110d08 << 1)), 0x00ff
    WREG        (REG_ADDR_BASE + (0x110d0e << 1)), 0x00a9
    WREG        (REG_ADDR_BASE + (0x110d0e << 1)), 0x00e9
    WREG        (REG_ADDR_BASE + (0x110d0e << 1)), 0x00a9
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x0000
                                              
    #//-----Wait 200us, (keep DRAM RESET = 0)-----
    #//wait 1
    DELAYUS     1000
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x0008
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x000c
                                              
    #//-----Wait 500us, (keep DRAM RESET = 1 , CKE = 0)-----
    DELAYUS     1000
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x000e
    
    #//-----Wait tXPR=400ns-----
    DELAYUS     1000
    
    #//--------Initial DRAM start here!!!
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x001f
    
    #//-----Wait init done-----
    DELAYUS     100000
    
    #//--------Initial Done
    #//--------DDR2 wait 400ns for tXPR(?), DDR3 wait 512T for tZQinit
    DELAYUS     1000

    #//wait 10 //Need wait 10us for one refresh cmd
    DELAYUS     10

    #//------------------------------
    #// unmask all
    #//------------------------------
    WREG        (REG_ADDR_BASE + (0x10121e << 1)), 0x1608
#    WREG        (REG_ADDR_BASE + (0x101246 << 1)), 0x0000
#    WREG        (REG_ADDR_BASE + (0x101266 << 1)), 0x0000
#    WREG        (REG_ADDR_BASE + (0x101286 << 1)), 0x0000
#    WREG        (REG_ADDR_BASE + (0x1012a6 << 1)), 0x0000
    
    
    #========================
    #//Enter MIU Self-refresh
    #========================
    WREG        (REG_ADDR_BASE + (0x101206 << 1)), 0x3530 #//Only change [13:11] = 3'b110
    WREG        (REG_ADDR_BASE + (0x101246 << 1)), 0xfffe
    WREG        (REG_ADDR_BASE + (0x101266 << 1)), 0xffff
    WREG        (REG_ADDR_BASE + (0x101286 << 1)), 0xffff
    WREG        (REG_ADDR_BASE + (0x1012a6 << 1)), 0xffff

    DELAYUS     20000

    WREG        (REG_ADDR_BASE + (0x101218 << 1)), 0x0400
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x002f
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x042f
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x052f
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x002f
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x022f
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x032f
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x002f
    WREG        (REG_ADDR_BASE + (0x101206 << 1)), 0x1d30 #//Only change [13:11] = 3'b011
    WREG        (REG_ADDR_BASE + (0x101246 << 1)), 0xffff
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x202f #//Enter self refresh (CKE = 0)

    #//All OENz = 1
    WREG        (REG_ADDR_BASE + (0x101202 << 1)), 0xf3a3 #//Only change [15:12] = 4'hf
    WREG        (REG_ADDR_BASE + (0x110d08 << 1)), 0x0000 #//only change [5:0]   = 6'h00 (disable rx_en)
                    
    #//For Turn-off power STR mode only
    WREG        (REG_ADDR_BASE + (0x110d00 << 1)), 0x0008 #//only change [3]    = 1 //GPIO_OENZ    = 1
    WREG        (REG_ADDR_BASE + (0x110d00 << 1)), 0x0018 #//only change [4]    = 1 //SEL_GPIO     = 1
    WREG        (REG_ADDR_BASE + (0x110d7c << 1)), 0xff00 #//only change [15:8] = ff//SEL_GPIO_PAD = ff



    #========================
    #//Exit MIU Self-refresh
    #========================
    WREG        (REG_ADDR_BASE + (0x101202 << 1)), 0x03a3 #//Only change [15:12] = 4'h0
    WREG        (REG_ADDR_BASE + (0x110d00 << 1)), 0x0008 #//only change [4]     = 0  //SEL_GPIO     = 0
    WREG        (REG_ADDR_BASE + (0x110d7c << 1)), 0x0000 #//only change [15:8]  = ff //SEL_GPIO_PAD = 00
    WREG        (REG_ADDR_BASE + (0x110d00 << 1)), 0x0200 #//only change [3]     = 0  //GPIO_OENZ    = 0
 
    #//PD = 1-->0
    WREG        (REG_ADDR_BASE + (0x110d54 << 1)), 0xc000 #//only change[6:4] //@@@@ for power off DVDD STR Flow
    WREG        (REG_ADDR_BASE + (0x110d08 << 1)), 0x003f #//only change [5:0]   = 6'h3f (Enable RX EN)
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x002c
    WREG        (REG_ADDR_BASE + (0x101246 << 1)), 0xfffe
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x002f
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x022f
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x032f
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x002f
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x001f
    WREG        (REG_ADDR_BASE + (0x101206 << 1)), 0x0530 #//Only change [13:11] = 3'b000
    
    #//SEL_RST_DQS : 0->1->0
    WREG        (REG_ADDR_BASE + (0x110d0e << 1)), 0x00a9
    WREG        (REG_ADDR_BASE + (0x110d0e << 1)), 0x00e9
    WREG        (REG_ADDR_BASE + (0x110d0e << 1)), 0x00a9
    
    WREG        (REG_ADDR_BASE + (0x101246 << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x101266 << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x101286 << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x1012a6 << 1)), 0x0000
    
    move        ra, t7
    jr          ra
    nop
    
    .size       BootInitMiu_STR,.-BootInitMiu_STR
    .end        BootInitMiu_STR