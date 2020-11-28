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

#ifndef _DRV_MIU_INIT_H_
#include "drv_miu_init.h"
#endif

#ifndef _MIUSEL_KENYA_2MIU_H_
#include "MIUSEL_KENYA_2MIU.h"
#endif

#define MIU_AUTO_DRV_N_TRG_LVL              0
#define MIU_TRIG_LVL                        0
#define MIU_AUTO_DRV                        0
#define MIU_AUTO_SKEW                       0
#define MIU_AUTO_DDL                        0
#define MIU_AUTO_DQS                        1

    .text
	.set    	noreorder

    .global     BootInitMiu
    .ent        BootInitMiu

BootInitMiu:

    move        t7, ra
    PUTK        'A'
    PUTK        'C'
    PUTK        '_'
    PUTK        'O'
    PUTK        'N'
    PUTK        '\n'
    PUTK        '\r'
#    DBGREG      0x0020
# set MIU data bus width for each IP
    WREG        0xBF203DE4, 0xf5e9
    WREG        0xBF203DE8, 0xe008
    WREG        0xBF203DEC, 0x4f80

#ifdef CONFIG_MSTAR_TITANIA_BD_FPGA

    # swch 3
    WREG        0xbf006010 0x0000
    WREG        0xbf203d40 0x0000
    WREG        0xBF00578C 0x3c11
    WREG        0xBF005794 0x403c
    WREG        0xBF005788 0x0004

    # swch 4
    WREG        0xBF202404 0x0000
    WREG        0xBF202404 0x0818
    WREG        0xBF202408 0x0185
    WREG        0xBF20240C 0x0120
    WREG        0xBF202410 0x0833
    WREG        0xBF202414 0x0c33
    WREG        0xBF202418 0x7111
    WREG        0xBF20241C 0x100e
    WREG        0xBF202420 0x0031
    WREG        0xBF20243C 0x0C01
    WREG        0xBF20243C 0x0C00
    WREG        0xBF202400 0x0008
    WREG        0xBF202400 0x000c
    WREG        0xBF202400 0x000e
    WREG        0xBF202400 0x001f
    WREG        0xBF20243C 0x0C08
    WREG        0xBF202450 0x4000
    WREG        0xBF202474 0x0001
    WREG        0xBF202478 0x03ff

_CheckDramData:
    lui         t0, 0xBF20
    ori         t0, t0,0x2400
    lw          t1, 0(t0)
    and         t1, t1, 0x8000
    beqz        t1, _CheckDramData
    nop

    move        ra, t7
    jr          ra
    nop

#else
    #//================================================
    #// Start MIU init !!!
    #//================================================
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
    WREG        (REG_ADDR_BASE + (0x101202 << 1)), 0x03a3   #//ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
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
    WREG        (REG_ADDR_BASE + (0x110d00 << 1)), 0x0038
    WREG        (REG_ADDR_BASE + (0x110d00 << 1)), 0x0030
    WREG        (REG_ADDR_BASE + (0x110d00 << 1)), 0x0220
    WREG        (REG_ADDR_BASE + (0x110d7e << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x110d54 << 1)), 0xc000
    WREG        (REG_ADDR_BASE + (0x110d08 << 1)), 0x00ff
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

#if (MIU_AUTO_DQS)
    WREG    (REG_ADDR_BASE + (0x101246 <<1 )) , 0x7FFE   #Mask MIU0_group_0
    bal         Miu0_AutoPhase
    nop
#endif

# BIST test
    WREG        (REG_ADDR_BASE + (0x101246 <<1 )) , 0x7FFE   #Un-mask MIU0_group_0
    bal         Miu0_BistTest
    nop
    WREG        (REG_ADDR_BASE + (0x1012e0 << 1)), 0x0000   # stop bist test


    #//------------------------------
    #// unmask all
    #//------------------------------
    WREG        (REG_ADDR_BASE + (0x10121e << 1)), 0x1608
    WREG        (REG_ADDR_BASE + (0x101246 << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x101266 << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x101286 << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x1012a6 << 1)), 0x0000

#endif

    move        ra, t7
    jr          ra
    nop

    .size       BootInitMiu,.-BootInitMiu
    .end        BootInitMiu

#-------------------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------------------
Miu0_AutoPhase:
    WREG        0xBF2025E0, 0x0000                          # 1012f0 bit_15=0 choice to MIU_0
    li          s7, (REG_ADDR_BASE + (0x103390 << 1))       # Dummy register to store miu 0 DQS phase result
    li          t8, 0                                       # DQS phase result

    WREG        (REG_ADDR_BASE + (0x110D6E << 1)), 0x7777   # set the default phase setting to 0x7777
    RREG        t1, (REG_ADDR_BASE + (0x110D6E << 1))       # store the default phase setting to r19
    move        s3, t1

    li          t3, (REG_ADDR_BASE + (0x110D6E << 1))      # reg_0x110D6E  //miu0_phase_reg
    li          t2, (REG_ADDR_BASE + (0x1012E7 << 1))      # reg_0x1012e7  //miu0_dqs_mask_reg

AutoPhaseLoop:
    PUTK        '['

    WREG        (REG_ADDR_BASE + (0x1012e4 << 1)), 0x0401   # 1012e4~1012e7 bist test size,   (16 byte/unit)
    WREG        (REG_ADDR_BASE + (0x1012e6 << 1)), 0x0000   # 1012e4~1012e7 bist test size,   (16 byte/unit)
    WREG        (REG_ADDR_BASE + (0x1012e8 << 1)), 0x00FF   # 1012e4~1012e7 bist test pattern

    lui         t5, 0                                   # t5-->tmp_var0=0;  for loop cnt
    lui         s5, 0                                   # s5-->good_phase cnt
    lui         s4, 0                                   # s4-->good_phase_sum
    li          t9, 1                                   # t9-->good_phase bit

StartChk_x3:

BistPatternfill:                    #write data into each region respect to bist mode 0x183,0x185,0x187
    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    andi        t1, t5, 0x0f
    sll         t1, t1, 4
    andi        t0, s3, 0x0f           # set dqs0 delay phase to r8
    or          t1, t1, t0
    sw          t1, (0)(t3)

    #ClockUnReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x20
    sb          k0, (0)(t6)

    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x1000   # 1012e2 bist test start address, (4K byte/unit)
    WREG        0xbf2025C0,0x0000
    li          t1, 0x0083              # bist mode 0x83
    j           BistRWModeTest
    nop

Check_bist85:
    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x1100   # 1012e2 bist test start address, (4K byte/unit)
    WREG        0xbf2025C0,0x0000
    li          t1, 0x0085              # bist mode 0x85
    j           BistRWModeTest
    nop

Check_bist87:
    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x1200   # 1012e2 bist test start address, (4K byte/unit)
    WREG        0xbf2025C0,0x0000
    li          t1, 0x0087              # bist mode 0x87

BistRWModeTest:                         # Read and Write bist
    move        s6, ra
    bal         ModeChangeDelay
    nop
    move        ra, s6

    lui         t0, 0xBF20              # bist test start
    sw          t1, (0x25C0)(t0)

CheckRWBistDone:
    RREG        t1, 0xBF2025C0
    andi        t0, t1, 0x8000
    beqz        t0, CheckRWBistDone        # check done
    nop

RWBistCheckPhaseOK:
    andi        t0, t1, 0x00FF
    beq         t0, 0x83, Check_bist85       #0x83->0x85->0x87
    nop
    beq         t0, 0x85, Check_bist87
    nop

check_x3:

    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    andi        t1, t5, 0x000f
    sll         t1, t1, 12
    andi        t0, s3, 0x0fff           # set dqs0 delay phase to r8
    or          t1, t1, t0
    sw          t1, (0)(t3)

    #ClockUnReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x20
    sb          k0, (0)(t6)

    j           StartCheck
    nop

StartChk_x2:
    #li          t1, 0xaa             # 1012e7/1006e7 =0xAA mask DQS_1 error when test DQS_0
    #sb          t1, (0)(t2)

    sw          t8, (0)(s7)         # store phase 0 result
    addiu       s7, s7, 4
    li          t8, 0                # DQS phase result
    li          t9, 1
    j           check_x2
    nop

check_x2:
    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    andi        t1, t5, 0x000f
    sll         t1, t1, 8
    andi        t0, s3, 0xf0ff           # set dqs0 delay phase to r8
    or          t1, t1, t0
    sw          t1, (0)(t3)

    #ClockUnReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x20
    sb          k0, (0)(t6)

    j           StartCheck
    nop
StartChk_x1:
    #li          t1, 0xaa             # 1012e7/1006e7 =0xAA mask DQS_1 error when test DQS_0
    #sb          t1, (0)(t2)

    sw          t8, (0)(s7)         # store phase 0 result
    addiu       s7, s7, 4
    li          t8, 0                # DQS phase result
    li          t9, 1
    j           check_x2
    nop

check_x1:

    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    andi        t1, t5, 0x000f
    sll         t1, t1, 4
    andi        t0, s3, 0xff0f           # set dqs0 delay phase to r8
    or          t1, t1, t0
    sw          t1, (0)(t3)

    #ClockUnReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x20
    sb          k0, (0)(t6)

    j           StartCheck
    nop
StartChk_x0:
    #li          t1, 0xaa             # 1012e7/1006e7 =0xAA mask DQS_1 error when test DQS_0
    #sb          t1, (0)(t2)

    sw          t8, (0)(s7)         # store phase 0 result
    addiu       s7, s7, 4
    li          t8, 0                # DQS phase result
    li          t9, 1
    j           check_x0
    nop
check_x0:
    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    andi        t1, t5, 0x000f
    andi        t0, s3, 0xfff0  # get the default phase setting
    or          t1, t1, t0
    sw          t1, (0)(t3)

    #ClockUnReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x20
    sb          k0, (0)(t6)

StartCheck:
    WREG        0xbf2025C0,0x0000
    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x1000   # 1012e2 bist test start address, (4K byte/unit)
    li          t1, 0x0183              # bist mode 0x183
    j           ROBitModeTest
    nop

Check_bist185:
    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x1100   # 1012e2 bist test start address, (4K byte/unit)
    WREG        0xbf2025C0,0x0000
    li          t1, 0x0185              # bist mode 0x185
    j           ROBitModeTest
    nop

Check_bist187:
    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x1200   # 1012e2 bist test start address, (4K byte/unit)
    WREG        0xbf2025C0,0x0000
    li          t1, 0x0187              # bist mode 0x187

ROBitModeTest:                      # read only bist
    move        s6, ra
    bal         ModeChangeDelay
    nop
    move        ra, s6

    lui         t0, 0xBF20              # bist test start
    sw          t1, (0x25C0)(t0)

CheckROBistDone:
    RREG        t1, 0xBF2025C0
    andi        t0, t1, 0x8000
    beqz        t0, CheckROBistDone        # check done
    nop
    andi        t0, t1, 0x6000
    bnez        t0, checkloopFail        # bist test fail if not zero
    nop

ROBistCheckPhaseOK:
    andi        t0, t1, 0x01FF
    beq         t0, 0x183, Check_bist185       #0x83->0x85->0x87
    nop
    beq         t0, 0x185, Check_bist187
    nop

    move        s6, ra
    andi        t1, t5, 0x0f        #move t5(loop cnt) to t1 for putchar
    bal         puthex
    nop
    move        ra, s6

    addiu       s5, s5, 1         # good_phase_cnt++;
    andi        s6, t5, 0x0f      # get good_phase
    add         s4, s4 ,s6        # good_phase_sum += good phase
    or          t8, t8, t9

checkloopFail:

checkloop:
    sll         t9, t9, 1
    addiu       t5, t5, 1             # add loop cnt by 1
    bne	        t5, 16 , CheckLoopDone
    nop

    beqz        s5, SetToDefault_P3    # if good_phase cnt == 0
    nop
    move        s6, s4  #good_phase_sum
    div         s6, s6 , s5
    sll         s6, s6 , 12
    j           StorePhase_P3
    nop
SetToDefault_P3:
    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    move        t1, s3
    j           SetPhaseToDefault_p3
    nop

StorePhase_P3:
    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    andi        t1, s3 , 0x0fff
    or          t1, t1 , s6
SetPhaseToDefault_p3:
    sw          t1, 0(t3)
    move        s3, t1

   #ClockUnReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x20
    sb          k0, (0)(t6)


    lui         s5, 0                  # s5-->good_phase cnt
    lui         s4, 0                  # s4-->good_phase_sum

    PUTK        ']'
    #PUTK       '\r'
    #PUTK       '\n'
    PUTK        '['

    # start check DQS_phase_0
    #sw         s3, (0)(t3)
    j           StartChk_x2
    nop

CheckLoopDone:
    bltu        t5, 16, check_x3
    nop
    bltu	    t5, 32, check_x2      #AutoPhaseLoop1
    nop
    beq         t5, 32, SetP2_
    nop
    bltu	    t5, 48, check_x1      #AutoPhaseLoop1
    nop
    beq         t5, 48, SetP1_
    nop
    bltu	    t5, 64, check_x0     #AutoPhaseLoop1
    nop
    beq         t5, 64, SetP0_
    nop

SetP2_:
    beqz        s5, SetToDefault_P2    # if good_phase cnt == 0
    nop
    move        s6, s4  #good_phase_sum
    div         s6, s6 , s5
    sll         s6, s6 , 8
    j           StorePhase_P2
    nop
SetToDefault_P2:
    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    move        t1, s3
    j           SetPhaseToDefault_p2
    nop

StorePhase_P2:
    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    andi        t1, s3 , 0xf0ff
    or          t1, t1 , s6
SetPhaseToDefault_p2:
    sw          t1, 0(t3)
    move        s3, t1

   #ClockUnReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x20
    sb          k0, (0)(t6)


    lui         s5, 0                  # s5-->good_phase cnt
    lui         s4, 0                  # s4-->good_phase_sum

    PUTK        ']'
    #PUTK       '\r'
    #PUTK       '\n'
    PUTK        '['

    # start check DQS_phase_0
    #sw         s3, (0)(t3)
    j           StartChk_x1
    nop

SetP1_:
    beqz        s5, SetToDefault_P1    # if good_phase cnt == 0
    nop
    move        s6, s4  #good_phase_sum
    div         s6, s6 , s5
    sll         s6, s6 , 4
    j           StorePhase_P1
    nop
SetToDefault_P1:
    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    move        t1, s3
    j           SetPhaseToDefault_p1
    nop

StorePhase_P1:
    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    andi        t1, s3 , 0xff0f
    or          t1, t1 , s6
SetPhaseToDefault_p1:
    sw          t1, 0(t3)
    move        s3, t1

   #ClockUnReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x20
    sb          k0, (0)(t6)


    lui         s5, 0                  # s5-->good_phase cnt
    lui         s4, 0                  # s4-->good_phase_sum

    PUTK        ']'
    #PUTK       '\r'
    #PUTK       '\n'
    PUTK        '['

    # start check DQS_phase_0
    #sw         s3, (0)(t3)
    j           StartChk_x0
    nop

SetP0_:
    sw          t8, (0)(s7)         #store phase 0  result
    nop
    beqz        s5, SetToDefault_P0  # good_phase cnt == 0
    nop
    move        s6, s4  #good_phase_sum
    div         s6, s6 , s5
    #sll        s6, s6 , 4
    j           StorePhase_P0
    nop
SetToDefault_P0:
    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    move        t1, s3
    j           SetPhaseToDefault
    nop

StorePhase_P0:
    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    andi        t1,  s3 , 0xfff0
    or          t1,  t1 , s6
SetPhaseToDefault:
    sw          t1,  0(t3)
    move        s3, t1

   #ClockUnReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x20
    sb          k0, (0)(t6)

    PUTK        ']'
    PUTK        '-'

    move        s6, ra
    andi        t1, s3, 0xf000
    srl         t1, t1, 12
    bal         puthex
    nop
    andi        t1, s3, 0x0f00
    srl         t1, t1, 8
    bal         puthex
    nop
    andi        t1, s3, 0x00f0
    srl         t1, t1, 4
    bal         puthex
    nop
    andi        t1, s3, 0x000f
    bal         puthex
    nop
    move        ra, s6

AutoPhaseRet:
    WREG        0xbf2025C0, 0x0000
    li          t1, 0x00             # 1012e7/1006e7 =0x00 mask DQS_1 error when test DQS_0
    sb          t1, (0)(t2)

    PUTK        '\r'
    PUTK        '\n'

    jr          ra
    nop

puthex:
    bltu        t1, 10, putx0_9
    nop
putxA_F:
    addiu       t1, t1, 0x37
    j           putx
    nop
putx0_9:
    addiu       t1, t1, 0x30
putx:
    SSSW        0xBF201300, t1
    jr          ra
    nop

ModeChangeDelay:
    lui         t0, 0x0
DelayLoop:
    addiu       t0, t0, 1
    bltu        t0, 10, DelayLoop
    nop
    jr          ra
    nop


#-------------------------------------------------------------------------------------------------
# MiuBistTest
# @param
# @return None
# @note
#-------------------------------------------------------------------------------------------------
Miu0_BistTest:
    #miu_0 bist test ---128Mbyte
    PUTK        '\n'
    PUTK        '\r'
    PUTK        'B'
    PUTK        'I'
    PUTK        'S'
    PUTK        'T'
    PUTK        '0'
    PUTK        '-'

    WREG        (REG_ADDR_BASE + (0x1012e0 << 1)), 0x0000   #1012e0 //reset bist test
    WREG        (REG_ADDR_BASE + (0x1012f0 << 1)), 0x0000   #1012f0 bit_15=0 choice to MIU_0
    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x0000   #1012e2 //start address base unit   :4k bytes
    WREG_D      (REG_ADDR_BASE + (0x1012e4 << 1)), BIST_LEN
    WREG        (REG_ADDR_BASE + (0x1012e8 << 1)), 0x5aa5   #1012e8 //bist test pattern

BistMiu0Test:
    WREG        (REG_ADDR_BASE + (0x1012e0 << 1)), 0x0003   #bitst test mode:3

ChkBistMiu0:
    RREG        t1, (REG_ADDR_BASE + (0x1012e0 << 1))
    andi        t0, t1, 0x8000
    beqz        t0, ChkBistMiu0
    nop

    andi        t0, t1, 0x6000
    beqz        t0, BistMiu0_OK
    nop

BistMiu0_FAIL:
    PUTK        'F'
    PUTK        'A'
    PUTK        'I'
    PUTK        'L'
    j           BistMiu0Ret
    nop


BistMiu0_OK:
    PUTK        'O'
    PUTK        'K'

BistMiu0Ret:
    PUTK        '\n'
    PUTK        '\r'

    jr          ra
    nop

