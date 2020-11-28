/*
 *#############################################################################
 *
 * Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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

#ifndef _BOARD_H_
#include "Board.h"
#endif

#ifndef _DRV_MIU_INIT_H_
#include "drv_miu_init.h"
#endif

#if defined(CONFIG_MSTAR_ASIC_EMULATION_ENABLE)
#ifndef _MIUSEL_A3_2MIU_H_
#include "MIUSEL_A3_2MIU.h"
#endif
#else
#ifndef _MIUSEL_EAGLE_2MIU_H_
#include "MIUSEL_EAGLE_2MIU.h"
#endif
#endif

    .text

    .global     BootRom_InitMiu
BootRom_InitMiu:

    mov         r13, lr

    DBGREG      0x0020

#ifdef CONFIG_MSTAR_TITANIA_BD_FPGA

    WREG        (MS_BUS_RIU_ADDR + (0x003008 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x101ea0 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x002bc6 << 1)), 0x3c11
    WREG        (MS_BUS_RIU_ADDR + (0x002bca << 1)), 0x403c
    WREG        (MS_BUS_RIU_ADDR + (0x002bc4 << 1)), 0x0004
    WREG        (MS_BUS_RIU_ADDR + (0x101202 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x101202 << 1)), 0x0818
    WREG        (MS_BUS_RIU_ADDR + (0x101204 << 1)), 0x0185
    WREG        (MS_BUS_RIU_ADDR + (0x101206 << 1)), 0x0120
    WREG        (MS_BUS_RIU_ADDR + (0x101208 << 1)), 0x0833
    WREG        (MS_BUS_RIU_ADDR + (0x10120a << 1)), 0x0c33
    WREG        (MS_BUS_RIU_ADDR + (0x10120c << 1)), 0x7111
    WREG        (MS_BUS_RIU_ADDR + (0x10120e << 1)), 0x100e
    WREG        (MS_BUS_RIU_ADDR + (0x101210 << 1)), 0x0031
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c01
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c00
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0008
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000c
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000e
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x001f
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c08
    WREG        (MS_BUS_RIU_ADDR + (0x101228 << 1)), 0x4000
    WREG        (MS_BUS_RIU_ADDR + (0x10123a << 1)), 0x0001
    WREG        (MS_BUS_RIU_ADDR + (0x10123c << 1)), 0x03ff

_CheckDramData:

    RREG        r0, (MS_BUS_RIU_ADDR + (0x101200 << 1))
    and         r0, r0, #0x8000
    cmp         r0, #0
    beq         _CheckDramData

#else

@// WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x8000 @//enable dramobf

#if !defined(CONFIG_MIU0_DRAM_NONE)
    @//MIU0 Software reset
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0000 @//hold miu_0
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c01 @//miu_sw_rst
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0e00 @//
    WREG        (MS_BUS_RIU_ADDR + (0x101202 << 1)), 0x0000 @//disable all ddr bus out

    @//MIU0 Request mask
    WREG        (MS_BUS_RIU_ADDR + (0x1012F8 << 1)), 0x8000
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0xFFFE @//mask group0
    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0xFFFF @//mask group1
    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0xFFFF @//mask group2
    WREG        (MS_BUS_RIU_ADDR + (0x1012A6 << 1)), 0xFFFF @//mask group3
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    @//MIU1 Software reset
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0000 @//hold miu_0
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0a01 @//
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0a00 @//
    WREG        (MS_BUS_RIU_ADDR + (0x100602 << 1)), 0x0000 @//

    @//MIU1 Request mask
    WREG        (MS_BUS_RIU_ADDR + (0x1006F8 << 1)), 0x8000
    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x7FFE @//mask group0
    WREG        (MS_BUS_RIU_ADDR + (0x100666 << 1)), 0xFFFF @//mask group1
    WREG        (MS_BUS_RIU_ADDR + (0x100686 << 1)), 0xFFFF @//mask group2
    WREG        (MS_BUS_RIU_ADDR + (0x1006A6 << 1)), 0xFFFF @//mask group3
#endif

#if !defined(CONFIG_MIU0_DRAM_NONE)
    ldr         r0, =MIU0_DDR_Init
    bl          MDrv_WriteRegTbl32

    WREG        (MS_BUS_RIU_ADDR + (0x1012fc <<1 )), 0x4400

    DELAYUS     1000

    @//Enable MIU0
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0a01
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0a00

    DELAYUS     200                                         @//delay 200us

#if (MIU_INTERFACE == DDR2_INTERFACE_BGA)
    WREG        (MS_BUS_RIU_ADDR + (0x110d00 << 1)), 0x0005
#else
#if defined(CONFIG_MSTAR_ASIC_EMULATION_ENABLE)
    WREG        (MS_BUS_RIU_ADDR + (0x110d00 << 1)), 0x1A01
#else
#if defined(CONFIG_MSTAR_BD_MST038B_10AHT_EAGLE) || \
    defined(CONFIG_MSTAR_BD_MST028B_10AFX_EAGLE)
    WREG        (MS_BUS_RIU_ADDR + (0x110d00 << 1)), 0x0400
#else
    WREG        (MS_BUS_RIU_ADDR + (0x110d00 << 1)), 0x0200
#endif
#endif
#endif
    WREG        (MS_BUS_RIU_ADDR + (0x110d02 << 1)), 0xAAAA
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)

    ldr         r0, =MIU1_DDR_Init
    bl          MDrv_WriteRegTbl32

    WREG        (MS_BUS_RIU_ADDR + (0x1006fc <<1 )), 0x4400

    DELAYUS     1000

    @//Enable MIU1
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0a01
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0a00

    DELAYUS     200                                         @//delay 200us

#if ( MIU_INTERFACE == DDR2_INTERFACE_BGA)
    WREG        (MS_BUS_RIU_ADDR + (0x110d80 << 1)), 0x0005
#else
#if defined(CONFIG_MSTAR_ASIC_EMULATION_ENABLE)
    WREG        (MS_BUS_RIU_ADDR + (0x110d80 << 1)), 0x1A01
#else
#if defined(CONFIG_MSTAR_BD_MST038B_10AHT_EAGLE) || \
    defined(CONFIG_MSTAR_BD_MST028B_10AFX_EAGLE)
    WREG        (MS_BUS_RIU_ADDR + (0x110d80 << 1)), 0x0400
#else
    WREG        (MS_BUS_RIU_ADDR + (0x110d80 << 1)), 0x0200
#endif
#endif
#endif
    WREG        (MS_BUS_RIU_ADDR + (0x110d82 << 1)), 0xAAAA
#endif

@// bl          EnableMiuSsc

#if !defined(CONFIG_MIU0_DRAM_NONE)
    @//rx enable
#if defined(CONFIG_MSTAR_BD_MST129F_D01A_S_EAGLE) && defined(CONFIG_MSTAR_ASIC_EMULATION_ENABLE)
    WREG        (MS_BUS_RIU_ADDR + (0x110d08 << 1)), 0x403f
#else
    WREG        (MS_BUS_RIU_ADDR + (0x110d08 << 1)), 0x003f
#endif

    @//MIU0 INIT Cycle
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0000 @//hold miu_0
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0008 @//DRAM reset

    DELAYUS     500                                         @//delay 500us

    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000c @//DRAM reset+CS
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000e @//DRAM reset+CS+CKE

    DELAYUS     500                                         @//delay 500us

    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x001f @//DRAM reset+CS+CKE+auto cycle+ODE

CheckMiu0Init:
    RREG        r1, (MS_BUS_RIU_ADDR + (0x101200 << 1))
    and         r1, r1, #0x8000
    cmp         r1, #0
    beq         CheckMiu0Init
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)

    @//rx enable
#if defined(CONFIG_MSTAR_BD_MST129F_D01A_S_EAGLE) && defined(CONFIG_MSTAR_ASIC_EMULATION_ENABLE)
    WREG        (MS_BUS_RIU_ADDR + (0x110d88 << 1)), 0x403f
#else
    WREG        (MS_BUS_RIU_ADDR + (0x110d88 << 1)), 0x003f
#endif

    @//MIU1 INIT Cycle
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0000 @//hold miu_0
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0008 @//DRAM reset

    DELAYUS     500                                         @//delay 500us

    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x000c @//DRAM reset+CS
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x000e @//DRAM reset+CS+CKE

    DELAYUS     500                                         @//delay 500us

    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x001f @//DRAM reset+CS+CKE+auto cycle+ODE

CheckMiu1Init:
    RREG        r1, (MS_BUS_RIU_ADDR + (0x100600 << 1))
    and         r1, r1, #0x8000
    cmp         r1, #0
    beq         CheckMiu1Init
#endif

    bl          MIU_Init_AnalogResetPatch

    bl          MIU_Init_Priority

    bl          MIU_Set_Group_Priority

#if !defined(CONFIG_EMMC_BOOT)
#if defined(CONFIG_ENABLE_AUTO_DQS)
#if !defined(CONFIG_MIU0_DRAM_NONE)
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x7FFE @//Mask MIU0_group_0
    bl          Miu0_AutoPhase
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x7FFE @//Mask MIU1_group_0
    bl          Miu1_AutoPhase
#endif
#endif
#endif

#if !defined(CONFIG_MIU0_DRAM_NONE)
    @//BIST test
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x7FFE @//Mask MIU0_group_0
    bl          Miu0_BistTest
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x7FFE @//Mask MIU1_group_0
    bl          Miu1_BistTest
#endif

#if !defined(CONFIG_MIU0_DRAM_NONE)
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000 @//stop bist test

    @//open all MIU0 request mask (All IP can access MIU resource)
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x0000 @//Mask MIU0_group_0
    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0x0000 @//Mask MIU0_group_1
    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0x0000 @//Mask MIU0_group_2
    WREG        (MS_BUS_RIU_ADDR + (0x1012a6 << 1)), 0x0000 @//Mask MIU0_group_3
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    @//open all MIU1 request mask (All IP can access MIU resource)
    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x0000 @//Mask MIU1_group_0
    WREG        (MS_BUS_RIU_ADDR + (0x100666 << 1)), 0x0000 @//Mask MIU1_group_1
    WREG        (MS_BUS_RIU_ADDR + (0x100686 << 1)), 0x0000 @//Mask MIU1_group_2
    WREG        (MS_BUS_RIU_ADDR + (0x1006a6 << 1)), 0x0000 @//Mask MIU1_group_3

    @//all MIU1 IP select MIU0 in bringup
    WREG        (MS_BUS_RIU_ADDR + (0x1006f0 << 1)), 0x4E88 @//0x7fff
    WREG        (MS_BUS_RIU_ADDR + (0x1006f2 << 1)), 0x0000 @//0xffff
    WREG        (MS_BUS_RIU_ADDR + (0x1006f4 << 1)), 0x0000 @//0xffff
    WREG        (MS_BUS_RIU_ADDR + (0x1006f6 << 1)), 0x0120 @//0xffff
#endif

#if !defined(CONFIG_MIU0_DRAM_NONE)
    WREG        (MS_BUS_RIU_ADDR + (0x10121e <<1 )), 0x0a08 @//SW initial done and turn on arbitor
@// WREG        (MS_BUS_RIU_ADDR + (0x1012fc <<1 )), 0x4400
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    WREG        (MS_BUS_RIU_ADDR + (0x10061e <<1 )), 0x0a08 @//SW initial done and turn on arbitor
@// WREG        (MS_BUS_RIU_ADDR + (0x1006fc <<1 )), 0x4400
#endif

    WREG        (MS_BUS_RIU_ADDR + (0x101842 << 1)), 0x0000 @//Set MIU0 Size of MAU0
    WREG        (MS_BUS_RIU_ADDR + (0x101862 << 1)), 0x0000 @//Set MIU0 Size of MAU1

#endif

    mov         lr, r13
    bx          lr

#if 0
@//-------------------------------------------------------------------------------------------------
EnableMiuSsc:
#if !defined(CONFIG_MIU0_DRAM_NONE)
    @// ENABLE MIU_0_SSC
    WREG        (MS_BUS_RIU_ADDR + (0x110d28 << 1)), DDFSTEP    @//DDFSTEP
    WREG        (MS_BUS_RIU_ADDR + (0x110d2A << 1)), DDFSPAN    @//DDFSPAN
    RREG        r1, (MS_BUS_RIU_ADDR + (0x110d28 << 1))         @//ENABLE MIU_SSC
    orr         r1, r1, #0xc000
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x110d28 << 1))
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    @// ENABLE MIU_1_SSC
    WREG        (MS_BUS_RIU_ADDR + (0x110dA8 << 1)), DDFSTEP    @//DDFSTEP
    WREG        (MS_BUS_RIU_ADDR + (0x110dAA << 1)), DDFSPAN    @//DDFSPAN
    RREG        r1, (MS_BUS_RIU_ADDR + (0x110dA8 << 1))         @//ENABLE MIU_SSC
    orr         r1, r1, #0xc000
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x110dA8 << 1))
#endif

    bx          lr
#endif

@//-------------------------------------------------------------------------------------------------
@// MIU_Init_AnalogResetPatch
@// @param  None
@// @return None
@// @note   Patch for DDR Analog Reset Issue
@//-------------------------------------------------------------------------------------------------
MIU_Init_AnalogResetPatch:
#if !defined(CONFIG_MIU0_DRAM_NONE)
@// WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x7ffe
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c08
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x1012e2 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x1012e4 << 1)), 0x0081
    WREG        (MS_BUS_RIU_ADDR + (0x1012e6 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x1012e8 << 1)), 0x5aa5

    WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x0000

    RREG        r3, (MS_BUS_RIU_ADDR + (0x110d0e << 1))
    orr         r3, r3, #(0x01 << 6)
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x110d0e << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0200
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0201

    RREG        r3, (MS_BUS_RIU_ADDR + (0x110d0e << 1))
    bic         r3, r3, #(0x01 << 6)
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x110d0e << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x8000
    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x7ffe

    RREG        r3, (MS_BUS_RIU_ADDR + (0x110d8e << 1))
    orr         r3, r3, #(0x01 << 6)
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x110d8e << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0200
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0201

    RREG        r3, (MS_BUS_RIU_ADDR + (0x110d8e << 1))
    bic         r3, r3, #(0x01 << 6)
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x110d8e << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x0000
#endif

    DELAYUS     10   @//Delay 10us

    bx          lr
    .ltorg

@//-------------------------------------------------------------------------------------------------
@// MIU_Init_Priority
@// @param  None
@// @return None
@// @note   Init MIU Priority
@//-------------------------------------------------------------------------------------------------
    .global     MIU_Init_Priority
MIU_Init_Priority:
#if !defined(CONFIG_MIU0_DRAM_NONE)
@// MIU0: generate set priority pulse for "fix priority"

    RREG        r3, (MS_BUS_RIU_ADDR + (0x101240 << 1))
    and         r3, r3, #0x0001
    cmp         r3, #0
    beq         miu0_rq0_skip

    RREG        r3, (MS_BUS_RIU_ADDR + (0x101240 << 1))
    orr         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x101240 << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x101240 << 1))
    bic         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x101240 << 1))

miu0_rq0_skip:

    RREG        r3, (MS_BUS_RIU_ADDR + (0x101260 << 1))
    and         r3, r3, #0x0001
    cmp         r3, #1
    beq         miu0_rq1_skip

    RREG        r3, (MS_BUS_RIU_ADDR + (0x101260 << 1))
    orr         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x101260 << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x101260 << 1))
    bic         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x101260 << 1))

miu0_rq1_skip:

    RREG        r3, (MS_BUS_RIU_ADDR + (0x101280 << 1))
    and         r3, r3, #0x0001
    cmp         r3, #1
    beq         miu0_rq2_skip

    RREG        r3, (MS_BUS_RIU_ADDR + (0x101280 << 1))
    orr         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x101280 << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x101280 << 1))
    bic         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x101280 << 1))

miu0_rq2_skip:

    RREG        r3, (MS_BUS_RIU_ADDR + (0x1012A0 << 1))
    and         r3, r3, #0x0001
    cmp         r3, #1
    beq         miu0_rq3_skip

    RREG        r3, (MS_BUS_RIU_ADDR + (0x1012A0 << 1))
    orr         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012A0 << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x1012A0 << 1))
    bic         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012A0 << 1))

miu0_rq3_skip:
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
@// MIU1: generate set priority pulse for "fix priority"

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100640 << 1))
    and         r3, r3, #0x0001
    cmp         r3, #1
    beq         miu1_rq0_skip

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100640 << 1))
    orr         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x100640 << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100640 << 1))
    bic         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x100640 << 1))

miu1_rq0_skip:

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100660 << 1))
    and         r3, r3, #0x0001
    cmp         r3, #1
    beq         miu1_rq1_skip

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100660 << 1))
    orr         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x100660 << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100660 << 1))
    bic         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x100660 << 1))

miu1_rq1_skip:

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100680 << 1))
    and         r3, r3, #0x0001
    cmp         r3, #1
    beq         miu1_rq2_skip

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100680 << 1))
    orr         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x100680 << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100680 << 1))
    bic         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x100680 << 1))

miu1_rq2_skip:

    RREG        r3, (MS_BUS_RIU_ADDR + (0x1006A0 << 1))
    and         r3, r3, #0x0001
    cmp         r3, #1
    beq         miu1_rq3_skip

    RREG        r3, (MS_BUS_RIU_ADDR + (0x1006A0 << 1))
    orr         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1006A0 << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x1006A0 << 1))
    bic         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1006A0 << 1))

miu1_rq3_skip:
#endif

    bx          lr

@//-------------------------------------------------------------------------------------------------
@// MIU_Set_Group_Priority
@// @param  None
@// @return None
@// @note   Set Group Priority
@//-------------------------------------------------------------------------------------------------
    .global     MIU_Set_Group_Priority
MIU_Set_Group_Priority:
#if !defined(CONFIG_MIU0_DRAM_NONE)
    @//set group priority in MIU_0
    RREG        r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))
    bic         r3, r3, #0x0100
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))
    bic         r3, r3, #0x00FF
    ldr         r4, =(MIU0_GROUP_PRIORITY & 0xFF)
    orr         r3, r3, r4
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))
    orr         r3, r3, #0x0100                             @//set group fix priority
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))
    bic         r3, r3, #0x0100
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    @//set group priority in MIU_1
    RREG        r3, (MS_BUS_RIU_ADDR + (0x1006FE << 1))
    bic         r3, r3, #0x0100
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1006FE << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x1006FE << 1))
    bic         r3, r3, #0x00FF
    ldr         r4, =(MIU1_GROUP_PRIORITY & 0xFF)
    orr         r3, r3, r4
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1006FE << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x1006FE << 1))
    orr         r3, r3, #0x0100
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1006FE << 1))
    bic         r3, r3, #0x0100
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1006FE << 1))
#endif

    bx          lr

@//-------------------------------------------------------------------------------------------------
@// MiuBistTest
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
#if !defined(CONFIG_MIU1_DRAM_NONE)
Miu1_BistTest:
    @//Setup for MIU1 BIST
    PUTK        'B'
    PUTK        'I'
    PUTK        'S'
    PUTK        'T'
    PUTK        '1'
    PUTK        '-'

    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000   @//1012e0 //reset bist test
    WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x8000   @//1012f0 bit_15=1 choice to MIU_1
    WREG        (MS_BUS_RIU_ADDR + (0x1012e2 << 1)), 0x0000   @//1012e2 //start address base unit:4 k bytes
    WREG_D      (MS_BUS_RIU_ADDR + (0x1012e4 << 1)), BIST_LEN
    WREG        (MS_BUS_RIU_ADDR + (0x1012e8 << 1)), 0x5aa5   @//1012e8 //bist test pattern

    b           BistTest
#endif

#if !defined(CONFIG_MIU0_DRAM_NONE)
Miu0_BistTest:
     @//Setup for MIU0 BIST
    PUTK        '\n'
    PUTK        '\r'
    PUTK        'B'
    PUTK        'I'
    PUTK        'S'
    PUTK        'T'
    PUTK        '0'
    PUTK        '-'

    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000   @//1012e0 //reset bist test
    WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x0000   @//1012f0 bit_15=0 choice to MIU_0
    WREG        (MS_BUS_RIU_ADDR + (0x1012e2 << 1)), 0x0000   @//1012e2 //start address base unit: 4k bytes
    WREG_D      (MS_BUS_RIU_ADDR + (0x1012e4 << 1)), BIST_LEN
    WREG        (MS_BUS_RIU_ADDR + (0x1012e8 << 1)), 0x5aa5   @//1012e8 //bist test pattern
#endif

BistTest:
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0003   @//bist test mode:3

ChkBistMiu0:
    RREG        r1, (MS_BUS_RIU_ADDR + (0x1012e0 << 1))
    and         r0, r1, #0x8000
    cmp         r0, #0
    beq         ChkBistMiu0

    and         r0, r1, #0x6000
    cmp         r0, #0
    beq         BistMiu0_OK

BistMiu0_FAIL:
    PUTK        'F'
    PUTK        'A'
    PUTK        'I'
    PUTK        'L'
    b           BistRet

BistMiu0_OK:
    PUTK        'O'
    PUTK        'K'

BistRet:
    PUTK        '\n'
    PUTK        '\r'

    bx          lr

@//================================================================================================
#ifdef CONFIG_ENABLE_AUTO_DQS

#define MIU_PHASE_LOOP_START            0x00                    @//The Starting Phase of Auto DQS: 0
#define MIU_PHASE_LOOP_END              0x0F                    @//The Maximum Phase of Auto DQS: 15
#define MIU_PHASE_TEST_SELECTION        (MS_BUS_RIU_ADDR + (0x103382 << 1))
#define MIU_GOOD_PHASE_START_NUMBER     (MS_BUS_RIU_ADDR + (0x103384 << 1))
#define MIU_GOOD_PHASE_COUNTER          (MS_BUS_RIU_ADDR + (0x103386 << 1))
#define MIU_ORGINAL_PHASE_SETTING       (MS_BUS_RIU_ADDR + (0x103388 << 1))
#define MIU_PHASE_REGISTER              r4
#define MIU_PHASE_LOOP_COUNTER          r5

@//================================================================================================
#if !defined(CONFIG_MIU1_DRAM_NONE)
Miu1_AutoPhase:

    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x7ffe     @//Mask All MIU Clients on MIU1
    WREG        (MS_BUS_RIU_ADDR + (0x100666 << 1)), 0xffff
    WREG        (MS_BUS_RIU_ADDR + (0x100686 << 1)), 0xffff
    WREG        (MS_BUS_RIU_ADDR + (0x1006a6 << 1)), 0xffff

    RREG        r0, (MS_BUS_RIU_ADDR + (0x1012f0 << 1))         @//Select BIST to MIU1 (0x1012F0[15] = 1)
    orr         r0, r0, #0x8000
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x1012f0 << 1))

    @//r4: MIU0 Phase Register Address (MIU0: 0x110d6e / MIU1: 0x110dee)
    ldr         MIU_PHASE_REGISTER, =(MS_BUS_RIU_ADDR + (0x110dee << 1))
    ldr         MIU_PHASE_LOOP_COUNTER, =MIU_PHASE_LOOP_START   @//r5: Phase Loop Counter (0 ~ 15)
    WREG        MIU_PHASE_TEST_SELECTION, 0                     @//0x103382[0]: MIU Auto Phase Test Selection
    WREG        MIU_GOOD_PHASE_START_NUMBER, 0                  @//0x103384[15:0]: Starting Number of Good Phase
    WREG        MIU_GOOD_PHASE_COUNTER, 0                       @//0x103386[15:0]: The Number of Good Phase

    ldr         r0, [MIU_PHASE_REGISTER]
    REG_C2M     r0, MIU_ORGINAL_PHASE_SETTING                   @//0x103388[15:0]: Backup Orginal Phase Setting

    PUTK        'A'
    PUTK        'u'
    PUTK        't'
    PUTK        'o'
    PUTK        'D'
    PUTK        'Q'
    PUTK        'S'
    PUTK        '1'
    PUTK        '-'
    PUTK        '['

    b           Miu_AutoDqs_Bist_Setup
#endif

@//================================================================================================
#if !defined(CONFIG_MIU0_DRAM_NONE)
Miu0_AutoPhase:

    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x7ffe     @//Mask All MIU Clients on MIU0
    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0xffff
    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0xffff
    WREG        (MS_BUS_RIU_ADDR + (0x1012a6 << 1)), 0xffff

    RREG        r0, (MS_BUS_RIU_ADDR + (0x1012f0 << 1))         @//Select BIST to MIU0 (0x1012F0[15] = 0)
    bic         r0, r0, #0x8000
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x1012f0 << 1))

    @//r4: MIU0 Phase Register Address (MIU0: 0x110d6e / MIU1: 0x110dee)
    ldr         MIU_PHASE_REGISTER, =(MS_BUS_RIU_ADDR + (0x110d6e << 1))
    ldr         MIU_PHASE_LOOP_COUNTER, =MIU_PHASE_LOOP_START   @//r5: Phase Loop Counter (0 ~ 15)
    WREG        MIU_PHASE_TEST_SELECTION, 0                     @//0x103382[0]: MIU Auto Phase Test Selection (Phase 0 / Phase 1)
    WREG        MIU_GOOD_PHASE_START_NUMBER, 0                  @//0x103384[15:0]: Starting Number of Good Phase (0 ~ 15)
    WREG        MIU_GOOD_PHASE_COUNTER, 0                       @//0x103386[15:0]: The Number of Good Phase (0 ~ 15)

    ldr         r0, [MIU_PHASE_REGISTER]
    REG_C2M     r0, MIU_ORGINAL_PHASE_SETTING                   @//0x103388[15:0]: Backup Orginal Phase Setting

    PUTK        '\n'
    PUTK        '\r'
    PUTK        'A'
    PUTK        'u'
    PUTK        't'
    PUTK        'o'
    PUTK        'D'
    PUTK        'Q'
    PUTK        'S'
    PUTK        '0'
    PUTK        '-'
    PUTK        '['
#endif

@//================================================================================================
Miu_AutoDqs_Bist_Setup:

    WREG        (MS_BUS_RIU_ADDR + (0x1012e2 << 1)), 0x3fff     @//Set Testing Address of BIST
    WREG        (MS_BUS_RIU_ADDR + (0x1012e4 << 1)), 0x0401     @//Set Testing Length of BIST
    WREG        (MS_BUS_RIU_ADDR + (0x1012e8 << 1)), 0x00ff     @//Set Testing Pattern of BIST

@//================================================================================================
Miu_AutoDqs_Phase_Selection:

    RREG        r0, MIU_PHASE_TEST_SELECTION                    @//Select Testing Phase of Auto DQS (0 / 1)
    and         r0, r0, #0x01
    cmp         r0, #0x00
    beq         Miu_AutoDqs_Phase0_Loop

@//================================================================================================
Miu_AutoDqs_Phase1_Loop:

    @//r4: MIU Phase Register Address (MIU0: 0x110d6e / MIU1: 0x110dee)
    @//r5: Phase Loop Counter (0 ~ 15)
    ldr         r0, [MIU_PHASE_REGISTER]
    and         r0, r0, #0x0f                                   @//In Phase 1, Update Higher Byte of MIU Phase Register
    mov         r1, MIU_PHASE_LOOP_COUNTER, lsl #4
    orr         r0, r0, r1
    str         r0, [MIU_PHASE_REGISTER]

    b           Miu_AutoDqs_Bist_Mode1                          @//After Phase Counter Updated, Execute BIST Again

@//================================================================================================
Miu_AutoDqs_Phase0_Loop:

    @//r4: MIU Phase Register Address (MIU0: 0x110d6e / MIU1: 0x110dee)
    @//r5: Phase Loop Counter (0 ~ 15)
    ldr         r0, [MIU_PHASE_REGISTER]
    and         r0, r0, #0xf0                                   @//In Phase 0, Update Lower Byte of MIU Phase Register
    orr         r0, r0, MIU_PHASE_LOOP_COUNTER
    str         r0, [MIU_PHASE_REGISTER]

    b           Miu_AutoDqs_Bist_Mode1                          @//After Phase Counter Updated, Execute BIST Again

@//================================================================================================
Miu_AutoDqs_Bist_Mode_Selection:

    RREG        r0, (MS_BUS_RIU_ADDR + (0x1012e0 << 1))
    and         r0, r0, #0xff

    cmp         r0, #0x81
    beq         Miu_AutoDqs_Bist_Mode3                          @//MIU BIST Mode 1 -> MIU BIST Mode 3

    cmp         r0, #0x83
    beq         Miu_AutoDqs_Bist_Mode5                          @//MIU BIST Mode 3 -> MIU BIST Mode 5

    cmp         r0, #0x85
    beq         Miu_AutoDqs_Bist_Mode7                          @//MIU BIST Mode 3 -> MIU BIST Mode 7

    mov         r1, MIU_PHASE_LOOP_COUNTER
    mov         r2, lr
    bl          Miu_AutoDqs_PrintMessage                        @//If All Mode BIST Pass, Print Current Loop Count
    mov         lr, r2

    RREG        r0, MIU_GOOD_PHASE_COUNTER
    add         r1, r0, #1
    REG_C2M     r1, MIU_GOOD_PHASE_COUNTER                      @//If All Mode BIST Pass, Good Phase Counter + 1

    cmp         r0, #0
    bne         Miu_AutoDqs_Bist_Done

    REG_C2M     MIU_PHASE_LOOP_COUNTER, MIU_GOOD_PHASE_START_NUMBER     @//If No Found Good Phase Before,
                                                                        @//Record Current Loop Count as The Starting Good Phase

    b           Miu_AutoDqs_Bist_Done

@//================================================================================================
Miu_AutoDqs_Bist_Mode1:
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x00
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x81       @//MIU BIST Mode 1

    b           Miu_AutoDqs_Bist_Mode_Loop

@//================================================================================================
Miu_AutoDqs_Bist_Mode3:
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x00
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x83       @//MIU BIST Mode 3

    b           Miu_AutoDqs_Bist_Mode_Loop

@//================================================================================================
Miu_AutoDqs_Bist_Mode5:
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x00
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x85       @//MIU BIST Mode 5

    b           Miu_AutoDqs_Bist_Mode_Loop

@//================================================================================================
Miu_AutoDqs_Bist_Mode7:
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x00
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x87       @//MIU BIST Mode 7

@//================================================================================================
Miu_AutoDqs_Bist_Mode_Loop:
    RREG        r0, (MS_BUS_RIU_ADDR + (0x1012e0 << 1))
    and         r1, r0, #0x8000                                 @//Check MIU BIST Done Status (0x1012e0[15] = 1)
    cmp         r1, #0x0000
    beq         Miu_AutoDqs_Bist_Mode_Loop

    and         r1, r0, #0x4000                                 @//Check MIU BIST Fail Status (0x1012e0[14] = 1)
    cmp         r1, #0x4000
    bne         Miu_AutoDqs_Bist_Mode_Selection                 @//If Current MIU BIST Pass, Execute Next Mode of BIST

@//================================================================================================
Miu_AutoDqs_Bist_Done:

    add         MIU_PHASE_LOOP_COUNTER, MIU_PHASE_LOOP_COUNTER, #1  @//r5: Phase Loop Counter (0 ~ 15)
    cmp         MIU_PHASE_LOOP_COUNTER, #MIU_PHASE_LOOP_END
    ble         Miu_AutoDqs_Phase_Selection                     @//If Current Loop Counter <= Maximum Setting, Execute Next Phase Testing

    RREG        r0, MIU_PHASE_TEST_SELECTION
    and         r0, r0, #0x01
    cmp         r0, #0x01
    beq         Miu_AutoDqs_Done                                @//If Phase 1 Testing was Executed, Terminate MIU Auto DQS

@//================================================================================================
    @//r4: MIU Phase Register Address (MIU0: 0x110d6e / MIU1: 0x110dee)
    @//r5: Phase Loop Counter (0 ~ 15)
    ldr         r0, [MIU_PHASE_REGISTER]
    and         r0, r0, #0xf0

    RREG        r1, MIU_GOOD_PHASE_START_NUMBER
    RREG        r2, MIU_GOOD_PHASE_COUNTER
    sub         r2, r2, #0x01
    mov         r2, r2, lsr #1                                  @//Get the Half Value of Good Phase Counter
    add         r1, r1, r2                                      @//Compute Final Good Phase Setting
    and         r1, r1, #0x0f
    orr         r0, r0, r1
    str         r0, [MIU_PHASE_REGISTER]                        @//Update Phase 0 Setting to Register

@//================================================================================================

    PUTK        ']'
    PUTK        '['

    ldr         MIU_PHASE_LOOP_COUNTER, =MIU_PHASE_LOOP_START   @//r5: Phase Loop Counter (0 ~ 15)
    WREG        MIU_PHASE_TEST_SELECTION, 1
    WREG        MIU_GOOD_PHASE_START_NUMBER, 0
    WREG        MIU_GOOD_PHASE_COUNTER, 0
    b           Miu_AutoDqs_Phase_Selection

@//================================================================================================
Miu_AutoDqs_Done:

    @//r4: MIU Phase Register Address (MIU0: 0x110d6e / MIU1: 0x110dee)
    @//r5: Phase Loop Counter (0 ~ 15)
    ldr         r0, [MIU_PHASE_REGISTER]
    and         r0, r0, #0x0f

    RREG        r1, MIU_GOOD_PHASE_START_NUMBER
    RREG        r2, MIU_GOOD_PHASE_COUNTER
    sub         r2, r2, #0x01
    mov         r2, r2, lsr #1                                  @//Get the Half Value of Good Phase Counter
    add         r1, r1, r2                                      @//Compute Final Good Phase Setting
    and         r1, r1, #0x0f
    mov         r1, r1, lsl #4
    orr         r0, r0, r1
    str         r0, [MIU_PHASE_REGISTER]                        @//Update Phase 1 Setting to Register

@//================================================================================================
Miu_AutoDqs_ErrorCheck:

    ldr         r0, [MIU_PHASE_REGISTER]
    and         r1, r0, #0x0f                                   @//Check the Value of MIU Phase 0
    cmp         r1, #0
    beq         Miu_AutoDqs_Restore_Default_Setting

    and         r1, r0, #0xf0                                   @//Check the Value of MIU Phase 1
    cmp         r1, #0
    beq         Miu_AutoDqs_Restore_Default_Setting

    PUTK        ']'
    PUTK        '-'
    PUTK        '['
    PUTK        '0'
    PUTK        'x'

    ldr         r0, [MIU_PHASE_REGISTER]
    and         r1, r0, #0xF0
    mov         r1, r1, lsr #4

    mov         r2, lr
    bl          Miu_AutoDqs_PrintMessage
    mov         lr, r2

    and         r1, r0, #0x0F
    mov         r2, lr
    bl          Miu_AutoDqs_PrintMessage
    mov         lr, r2

    PUTK        ']'

    b           Miu_AutoDqs_Exit

@//================================================================================================
Miu_AutoDqs_Restore_Default_Setting:

    RREG        r0, MIU_ORGINAL_PHASE_SETTING                   @//0x103388[15:0]: Backup Orginal Phase Setting
    str         r0, [MIU_PHASE_REGISTER]                        @//Resotre Default Setting to Phase Register

    PUTK        'F'
    PUTK        'a'
    PUTK        'i'
    PUTK        'l'

@//================================================================================================
Miu_AutoDqs_Exit:

    PUTK        '\r'
    PUTK        '\n'

    RREG        r0, (MS_BUS_RIU_ADDR + (0x1012f0 << 1))         @//Select BIST to MIU0 (0x1012F0[15] = 0)
    bic         r0, r0, #0x8000
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x1012f0 << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x0000     @//Release MIU Client Mask on MIU0
    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x1012a6 << 1)), 0x0000

    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x0000     @//Release MIU Client Mask on MIU1
    WREG        (MS_BUS_RIU_ADDR + (0x100666 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x100686 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x1006a6 << 1)), 0x0000

    bx          lr

@//================================================================================================
Miu_AutoDqs_PrintMessage:
    cmp         r1, #0x09
    ble         Miu_AutoDqs_PrintMessage_Digit

    sub         r1, r1, #0x0a
    add         r1, r1, #'A'
    b           Miu_AutoDqs_PrintMessage_Exec

Miu_AutoDqs_PrintMessage_Digit:
    add         r1, r1, #'0'

Miu_AutoDqs_PrintMessage_Exec:
    REG_C2M     r1, (0x1F000000 + (0x100980 << 1))

    bx          lr

#endif
@//================================================================================================

    .size       BootRom_InitMiu,.-BootRom_InitMiu
