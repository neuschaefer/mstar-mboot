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

#ifndef _MIUSEL_KRITI_2MIU_H_
#include "MIUSEL_KRITI_2MIU.h"
#endif

#define MIU_AUTO_DRV_N_TRG_LVL              0
#define MIU_TRIG_LVL                        0
#define MIU_AUTO_DRV                        0
#define MIU_AUTO_SKEW                       0
#define MIU_AUTO_DDL                        0
#define MIU_AUTO_DQS                        0

    .text
	.set    	noreorder

    .global     BootInitMiu
    .ent        BootInitMiu

BootInitMiu:

    move        t7, ra

    DBGREG      0x0020

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
    WREG        (REG_ADDR_BASE + (0x101220<< 1)), 0x0000   #//miu initial
    WREG        (REG_ADDR_BASE + (0x10121e<< 1)), 0x0c00   #//miu initial
    WREG        (REG_ADDR_BASE + (0x10121e<< 1)), 0x0c00
    WREG        (REG_ADDR_BASE + (0x10121e<< 1)), 0x0c00
    WREG        (REG_ADDR_BASE + (0x10121e<< 1)), 0x0c01   #//miu software reset
    WREG        (REG_ADDR_BASE + (0x10121e<< 1)), 0x0c00
    WREG        (REG_ADDR_BASE + (0x101202<< 1)), 0x0000   #//dram type set as '0'
    WREG        (REG_ADDR_BASE + (0x101246<< 1)), 0xFFFE   #//mask group0
    WREG        (REG_ADDR_BASE + (0x101266<< 1)), 0xFFFF   #//mask group1
    WREG        (REG_ADDR_BASE + (0x101286<< 1)), 0xFFFF   #//mask group2
    WREG        (REG_ADDR_BASE + (0x1012A6<< 1)), 0xFFFF   #//mask group3
    #//--------------------
    #//set DDRPLL0 1333MHz
    #//--------------------
    
    WREG        (REG_ADDR_BASE + (0x110d36<< 1)), 0x4000
    WREG        (REG_ADDR_BASE + (0x110d34<< 1)), 0x0400
#if ENABLE_MEM1333MHz
    WREG        (REG_ADDR_BASE + (0x110d30<< 1)), 0xf459        #//Clock generator frequency set
    WREG        (REG_ADDR_BASE + (0x110d32<< 1)), 0x0029        #//MCLK Freq (miu0)
#elif ENABLE_MEM1200MHz
    WREG        (REG_ADDR_BASE + (0x110d30<< 1)), 0x147b        #//Clock generator frequency set
    WREG        (REG_ADDR_BASE + (0x110d32<< 1)), 0x002e        #//MCLK Freq (miu0)
#endif
    WREG        (REG_ADDR_BASE + (0x110d22<< 1)), 0x2000
    WREG        (REG_ADDR_BASE + (0x110d24<< 1)), 0x2000
    WREG        (REG_ADDR_BASE + (0x110d24<< 1)), 0x3000
    WREG        (REG_ADDR_BASE + (0x110d24<< 1)), 0x2000
    #//------------------
    #// Wait PLL Stable
    #//------------------
    DELAYUS     1000
    WREG        (REG_ADDR_BASE + (0x101202<< 1)), 0x0392
    WREG        (REG_ADDR_BASE + (0x101204<< 1)), 0x00c9
    WREG        (REG_ADDR_BASE + (0x101206<< 1)), 0x1529        #//[12:12] reg_cke_always_on 
    WREG        (REG_ADDR_BASE + (0x101208<< 1)), 0x1e99
    WREG        (REG_ADDR_BASE + (0x10120a<< 1)), 0x2788
    WREG        (REG_ADDR_BASE + (0x10120c<< 1)), 0x75a6
    WREG        (REG_ADDR_BASE + (0x10120e<< 1)), 0x206a
    WREG        (REG_ADDR_BASE + (0x101210<< 1)), 0x0e73
    WREG        (REG_ADDR_BASE + (0x101212<< 1)), 0x4004
    WREG        (REG_ADDR_BASE + (0x101214<< 1)), 0x8000
    WREG        (REG_ADDR_BASE + (0x101216<< 1)), 0xc000
    WREG        (REG_ADDR_BASE + (0x110d54<< 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x110d00<< 1)), 0x0018
    WREG        (REG_ADDR_BASE + (0x110d38<< 1)), 0x0055
#if ENABLE_MEM1333MHz
    WREG        (REG_ADDR_BASE + (0x110d3a<< 1)), 0x6042
#elif ENABLE_MEM1200MHz
    WREG        (REG_ADDR_BASE + (0x110d3a<< 1)), 0x5022
#endif
    WREG        (REG_ADDR_BASE + (0x110d48<< 1)), 0x0033
    WREG        (REG_ADDR_BASE + (0x110d4a<< 1)), 0x0003
    WREG        (REG_ADDR_BASE + (0x110d02<< 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x110d04<< 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x110d3c<< 1)), 0x1533
    WREG        (REG_ADDR_BASE + (0x110d4e<< 1)), 0x0033
    WREG        (REG_ADDR_BASE + (0x110d3e<< 1)), 0x1055
    WREG        (REG_ADDR_BASE + (0x110d0a<< 1)), 0x1033
    WREG        (REG_ADDR_BASE + (0x110d50<< 1)), 0x1111
    WREG        (REG_ADDR_BASE + (0x110d52<< 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x110d0e<< 1)), 0x00a3
    WREG        (REG_ADDR_BASE + (0x110d0e<< 1)), 0x00e3
    WREG        (REG_ADDR_BASE + (0x110d0e<< 1)), 0x00a3
#if ENABLE_MEM1333MHz
    WREG        (REG_ADDR_BASE + (0x110d6e<< 1)), 0x3344
#elif ENABLE_MEM1200MHz
    WREG        (REG_ADDR_BASE + (0x110d6e<< 1)), 0x4444
#endif
    WREG        (REG_ADDR_BASE + (0x110d6a<< 1)), 0x00c2
    WREG        (REG_ADDR_BASE + (0x110d68<< 1)), 0x00c2
    WREG        (REG_ADDR_BASE + (0x110d54<< 1)), 0xc000
    WREG        (REG_ADDR_BASE + (0x10121e<< 1)), 0x0c01
    WREG        (REG_ADDR_BASE + (0x10121e<< 1)), 0x0c00
    WREG        (REG_ADDR_BASE + (0x110d7e<< 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x110d00<< 1)), 0x0018
    WREG        (REG_ADDR_BASE + (0x110d00<< 1)), 0x0010
    WREG        (REG_ADDR_BASE + (0x110d00<< 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x110d7c<< 1)), 0x000f
    WREG        (REG_ADDR_BASE + (0x110d02<< 1)), 0xaaaa
    WREG        (REG_ADDR_BASE + (0x110d08<< 1)), 0x00ff
    
    WREG        (REG_ADDR_BASE + (0x110d0e<< 1)), 0x00a3
    WREG        (REG_ADDR_BASE + (0x110d0e<< 1)), 0x00e3
    WREG        (REG_ADDR_BASE + (0x110d0e<< 1)), 0x00a3
    
    WREG        (REG_ADDR_BASE + (0x110d74<< 1)), 0x0004
    WREG        (REG_ADDR_BASE + (0x110d58<< 1)), 0x4c4c
    WREG        (REG_ADDR_BASE + (0x110d5c<< 1)), 0x4444
    WREG        (REG_ADDR_BASE + (0x110d5e<< 1)), 0x4444
    
#if ENABLE_MEM1333MHz
    WREG        (REG_ADDR_BASE + (0x110d28<< 1)), 0x0021
    WREG        (REG_ADDR_BASE + (0x110d2A<< 1)), 0x0338
#elif ENABLE_MEM1200MHz
    WREG        (REG_ADDR_BASE + (0x110d28<< 1)), 0x0028
    WREG        (REG_ADDR_BASE + (0x110d2A<< 1)), 0x02EE
#endif
    
    WREG        (REG_ADDR_BASE + (0x101200<< 1)), 0x0000
    #//-----Wait 200us<< 1)), (keep DRAM RESET = 0)-----
    DELAYUS     1000
    WREG        (REG_ADDR_BASE + (0x101200<< 1)), 0x0008
    WREG        (REG_ADDR_BASE + (0x101200<< 1)), 0x000c
    #//-----Wait 500us<< 1)), (keep DRAM RESET = 1 << 1)), CKE = 0)-----
    DELAYUS     1000
    WREG        (REG_ADDR_BASE + (0x101200<< 1)), 0x000e
    #//-----Wait tXPR=400ns-----
    DELAYUS     1000
    #//--------Initial DRAM start here!!!
    WREG        (REG_ADDR_BASE + (0x101200<< 1)), 0x001f
    #//-----Wait init done-----
    DELAYUS     1000
    #//--------Initial Done
    #//--------DDR2 wait 400ns for tXPR(? DDR3 wait 512T for tZQinit
    DELAYUS     1000
    #//-------------
    #// BW setting  
    #//-------------
    WREG        (REG_ADDR_BASE + (0x101240<< 1)), 0x8015
    WREG        (REG_ADDR_BASE + (0x101260<< 1)), 0x8015
    WREG        (REG_ADDR_BASE + (0x101280<< 1)), 0x8015
    WREG        (REG_ADDR_BASE + (0x1012a0<< 1)), 0x8015
    
    WREG        (REG_ADDR_BASE + (0x110d62<< 1)), 0x0032
    WREG        (REG_ADDR_BASE + (0x110d64<< 1)), 0xf200
    WREG        (REG_ADDR_BASE + (0x110d68<< 1)), 0x0020
    WREG        (REG_ADDR_BASE + (0x110d6a<< 1)), 0x0020
    WREG        (REG_ADDR_BASE + (0x110d60<< 1)), 0x000c
    WREG        (REG_ADDR_BASE + (0x110d60<< 1)), 0x0008
    WREG        (REG_ADDR_BASE + (0x110d60<< 1)), 0x2370
    #//--------------------
    #// MIU select setting 
    #//----------- --------
    #//---------------------------------
    #// Pack setting                    
    #//---------------------------------
    WREG        (REG_ADDR_BASE + (0x101228<< 1)), 0x4090
    #//-------------------------
    #// Reduce latency setting  
    #//-------------------------
    WREG        (REG_ADDR_BASE + (0x10122a<< 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x1012d4<< 1)), 0x0000
    #//------------------------------
    #// unmask all                   
    #//------------------------------
    WREG        (REG_ADDR_BASE + (0x10121a<< 1)), 0x0001
    WREG        (REG_ADDR_BASE + (0x1012fc<< 1)), 0x0400
    DELAYUS     1000
    WREG        (REG_ADDR_BASE + (0x101246<< 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x101266<< 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x101286<< 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x1012a6<< 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x10121e<< 1)), 0x5a08
    WREG        (REG_ADDR_BASE + (0x1012fe<< 1)), 0x00e1
    WREG        (REG_ADDR_BASE + (0x1012fe<< 1)), 0x01e1
    WREG        (REG_ADDR_BASE + (0x1012fe<< 1)), 0x00e1

#if 0    
#if ( MIU_INTERFACE == DDR2_INTERFACE_QFP_128)
    lui         t0, 0xBF20
    ori         t0, t0,0x3D80
    lw          t1, 0(t0)
    and         t1, t1, 0x200
    beqz        t1, MIU_ESMT
    
    lui         a0, %hi(MIU_DDR2_WINBOND_Init)
    bal         MDrv_WriteRegTbl32
    ori         a0, %lo(MIU_DDR2_WINBOND_Init)
    j MIU_EXIT
    nop

MIU_ESMT:
    lui         a0, %hi(MIU_DDR2_ESMT_Init)
    bal         MDrv_WriteRegTbl32
    ori         a0, %lo(MIU_DDR2_ESMT_Init)
    j MIU_EXIT
    nop

MIU_EXIT:
#elif ( MIU_INTERFACE == DDR3_INTERFACE_QFP_128)
    lui         a0, %hi(MIU_DDR3_NANYA_Init)
    bal         MDrv_WriteRegTbl32
    ori         a0, %lo(MIU_DDR3_NANYA_Init)
#else
    #error "Unspecified DRAM TYPE"
#endif

    #//=================================================================
    #// End of MIU init !!!             
    #//=================================================================

#endif
#endif
    move        ra, t7
    jr          ra
    nop

    .size       BootInitMiu,.-BootInitMiu
    .end        BootInitMiu
