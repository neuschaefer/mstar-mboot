/*
 *#############################################################################
 *
 * Copyright (c) 2006-2014 MStar Semiconductor, Inc.
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

#ifndef _MIUSEL_MIAMI_2MIU_H_
#include "MIUSEL_MIAMI_2MIU.h"
#endif

    .text

MIU_MESSAGE_BIST0:      .short   'B', 'I', 'S', 'T', '0', '-', 0x00
MIU_MESSAGE_BIST1:      .short   'B', 'I', 'S', 'T', '1', '-', 0x00
MIU_MESSAGE_AUTO_DQS0:  .short   'A', 'u', 't', 'o', 'D', 'Q', 'S', '0', '-', 0x00
MIU_MESSAGE_AUTO_DQS1:  .short   'A', 'u', 't', 'o', 'D', 'Q', 'S', '1', '-', 0x00
MIU_MESSAGE_OK:         .short   'O', 'K', '\n', '\r', 0x00
MIU_MESSAGE_FAIL:       .short   'F', 'A', 'I', 'L', '\n', '\r', 0x00

    .align      4

    .global     BootRom_InitMiu
BootRom_InitMiu:

    mov         r13, lr

#ifdef CONFIG_MSTAR_TITANIA_BD_FPGA

@// WREG        (MS_BUS_RIU_ADDR + (0x003008 << 1)), 0x0000
@// WREG        (MS_BUS_RIU_ADDR + (0x101ea0 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x002bc6 << 1)), 0x3c11
    WREG        (MS_BUS_RIU_ADDR + (0x002bca << 1)), 0x403c
    WREG        (MS_BUS_RIU_ADDR + (0x002bc4 << 1)), 0x0004
    WREG        (MS_BUS_RIU_ADDR + (0x101220 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x101224 << 1)), 0x03FF
    WREG        (MS_BUS_RIU_ADDR + (0x101202 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x101202 << 1)), 0x0854
    WREG        (MS_BUS_RIU_ADDR + (0x101204 << 1)), 0x01c5
    WREG        (MS_BUS_RIU_ADDR + (0x101206 << 1)), 0x0120
    WREG        (MS_BUS_RIU_ADDR + (0x101208 << 1)), 0x0833
    WREG        (MS_BUS_RIU_ADDR + (0x10120a << 1)), 0x0c33
    WREG        (MS_BUS_RIU_ADDR + (0x10120c << 1)), 0x7111
    WREG        (MS_BUS_RIU_ADDR + (0x10120e << 1)), 0x100e
    WREG        (MS_BUS_RIU_ADDR + (0x101210 << 1)), 0x0031
    WREG        (MS_BUS_RIU_ADDR + (0x10122a << 1)), 0x000f
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c01
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c00
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0008
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000c
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000e
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x001f
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c08
    WREG        (MS_BUS_RIU_ADDR + (0x101228 << 1)), 0x4000
    WREG        (MS_BUS_RIU_ADDR + (0x1012f8 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x1012fa << 1)), 0x03ff

_CheckDramData:

    ldr         r1, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r0, [r1, #(0x00 << 1)]
    and         r0, r0, #0x8000
    cmp         r0, #0
    beq         _CheckDramData

#else

    @//when disabling icache/dcache/L2, we need this hardware patch
    @//bank 0x1018, reg 0x45, set bit 4 & bit 5
    WREG        (MS_BUS_RIU_ADDR + (0x10188A << 1)), 0x0031

    ldr         r0, =MIU_PreInit
    bl          MDrv_WriteRegTbl32

#if !defined(CONFIG_MIU0_DRAM_NONE)
    ldr         r0, =MIU0_DDR_Init
    bl          MDrv_WriteRegTbl32

    DELAYUS     1000
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)

    ldr         r0, =MIU1_DDR_Init
    bl          MDrv_WriteRegTbl32

    DELAYUS     1000

#endif

    bl          MIU_EnableSSC

#if !defined(CONFIG_MIU0_DRAM_NONE)
    @//rx enable
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x110d00 << 1))
    ldr         r0, =0x003f
    str         r0, [r1, #(0x08 << 1)]

    @//MIU0 INIT Cycle
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r0, =0x0000                 @//hold miu_0
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x0008                 @//DRAM reset
    str         r0, [r1, #(0x00 << 1)]

    DELAYUS     500                         @//delay 500us

    ldr         r0, =0x000c                 @//DRAM reset+CS
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x000e                 @//DRAM reset+CS+CKE
    str         r0, [r1, #(0x00 << 1)]

    DELAYUS     500                         @//delay 500us

    ldr         r0, =0x001f                 @//DRAM reset+CS+CKE+auto cycle+ODE
    str         r0, [r1, #(0x00 << 1)]

CheckMiu0Init:
    ldr         r0, [r1, #(0x00 << 1)]
    and         r0, r0, #0x8000
    cmp         r0, #0
    beq         CheckMiu0Init
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)

    @//rx enable
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x110d00 << 1))
    ldr         r0, =0x003f
    str         r0, [r1, #(0x88 << 1)]

    @//MIU1 INIT Cycle
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
    ldr         r0, =0x0000                 @//hold miu_1
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x0008                 @//DRAM reset
    str         r0, [r1, #(0x00 << 1)]

    DELAYUS     500                         @//delay 500us

    ldr         r0, =0x000c                 @//DRAM reset+CS
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x000e                 @//DRAM reset+CS+CKE
    str         r0, [r1, #(0x00 << 1)]

    DELAYUS     500                         @//delay 500us

    ldr         r0, =0x001f                 @//DRAM reset+CS+CKE+auto cycle+ODE
    str         r0, [r1, #(0x00 << 1)]

CheckMiu1Init:
    ldr         r0, [r1, #(0x00 << 1)]
    and         r0, r0, #0x8000
    cmp         r0, #0
    beq         CheckMiu1Init
#endif

    bl          MIU_AnalogReset

@// bl          MIU_Init_Priority

    bl          MIU_Set_Group_Priority

    @//for New BIST Flow
    WREG        (MS_BUS_RIU_ADDR + (0x1012fe << 1)), 0x20e1
    WREG        (MS_BUS_RIU_ADDR + (0x161506 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x162206 << 1)), 0x0000

#if defined(CONFIG_ENABLE_AUTO_DQS)
#if !defined(CONFIG_MIU0_DRAM_NONE)
    bl          Miu0_AutoPhase
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    bl          Miu1_AutoPhase
#endif
#endif

#if !defined(CONFIG_MIU0_DRAM_NONE)
    @//BIST test
    bl          Miu0_BistTest
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    bl          Miu1_BistTest
#endif

    @//Disable BIST
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r0, [r12, #(0xfe << 1)]     @//RREG        r0, (MS_BUS_RIU_ADDR + (0x1012fe << 1))
    orr         r0, r0, #(0x01 << 11)
    str         r0, [r12, #(0xfe << 1)]     @//REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x1012fe << 1))

    ldr         r0, =MIU_PostInit
    bl          MDrv_WriteRegTbl32

#endif

    mov         lr, r13
    bx          lr

@//-------------------------------------------------------------------------------------------------
MIU_EnableSSC:
#if !defined(CONFIG_MIU0_DRAM_NONE)
    @// ENABLE MIU_0_SSC
    WREG        (MS_BUS_RIU_ADDR + (0x110d28 << 1)), 0x0011     @//DDFSTEP
    WREG        (MS_BUS_RIU_ADDR + (0x110d2a << 1)), 0x0482     @//DDFSPAN
    RREG        r1, (MS_BUS_RIU_ADDR + (0x110d28 << 1))         @//ENABLE MIU_SSC
    ldr         r2, =0xc000
    orr         r1, r1, r2
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x110d28 << 1))
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    @// ENABLE MIU_1_SSC
    WREG        (MS_BUS_RIU_ADDR + (0x161628 << 1)), 0x0011     @//DDFSTEP
    WREG        (MS_BUS_RIU_ADDR + (0x16162a << 1)), 0x0482     @//DDFSPAN
    RREG        r1, (MS_BUS_RIU_ADDR + (0x161628 << 1))         @//ENABLE MIU_SSC
    ldr         r2, =0xc000
    orr         r1, r1, r2
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x161628 << 1))
#endif

    bx          lr

@//-------------------------------------------------------------------------------------------------
@// MIU_AnalogReset
@// @param  None
@// @return None
@// @note   Patch for DDR Analog Reset Issue
@//-------------------------------------------------------------------------------------------------
    .global     MIU_AnalogReset
MIU_AnalogReset:
#if !defined(CONFIG_MIU0_DRAM_NONE)
    @//====== New Sequesnce for MIU0 dqsm reset
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r0, =0x0400                 @//reg_mrx
    str         r0, [r1, #(0x18 << 1)]
    ldr         r0, =0x043f                 @//Bit[05]reg_auto_ref_off, precharge all cmd
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x053f                 @//Bit[05]reg_auto_ref_off, trig precharge all cmd enable
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x003f                 @//single cmd off
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x023f                 @//Bit[05]reg_auto_ref_off, refresh cmd
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x033f                 @//Bit[05]reg_auto_ref_off, refresh cmd enable
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x001f                 @//single cmd off, auto_ref_on
    str         r0, [r1, #(0x00 << 1)]
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)

    @//====== New Sequesnce for MIU1 dqsm reset
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
    ldr         r0, =0x0400                 @//reg_mrx
    str         r0, [r1, #(0x18 << 1)]
    ldr         r0, =0x043f                 @//Bit[05]reg_auto_ref_off, precharge all cmd
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x053f                 @//Bit[05]reg_auto_ref_off, trig precharge all cmd enable
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x003f                 @//single cmd off
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x023f                 @//Bit[05]reg_auto_ref_off, refresh cmd
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x033f                 @//Bit[05]reg_auto_ref_off, refresh cmd enable
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x001f                 @//single cmd off, auto_ref_on
    str         r0, [r1, #(0x00 << 1)]

#endif

    bx          lr
    .ltorg

@//-------------------------------------------------------------------------------------------------
@// MIU_Init_Priority
@// @param  None
@// @return None
@// @note   Init MIU Priority
@//-------------------------------------------------------------------------------------------------
#if 0
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
#endif

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
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r3, [r12, #(0xfe << 1)]     @//RREG        r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))
    bic         r3, r3, #0x0100
    str         r3, [r12, #(0xfe << 1)]     @//REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))

    bic         r3, r3, #0x00FF
    ldr         r4, =(MIU0_GROUP_PRIORITY & 0xFF)
    orr         r3, r3, r4
    str         r3, [r12, #(0xfe << 1)]     @//REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))

    orr         r3, r3, #0x0100             @//set group fix priority
    str         r3, [r12, #(0xfe << 1)]     @//REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))
    bic         r3, r3, #0x0100
    str         r3, [r12, #(0xfe << 1)]     @//REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))

#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    @//set group priority in MIU_1
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
    ldr         r3, [r12, #(0xfe << 1)]     @//RREG        r3, (MS_BUS_RIU_ADDR + (0x1006FE << 1))
    bic         r3, r3, #0x0100
    str         r3, [r12, #(0xfe << 1)]     @//REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1006FE << 1))

    bic         r3, r3, #0x00FF
    ldr         r4, =(MIU1_GROUP_PRIORITY & 0xFF)
    orr         r3, r3, r4
    str         r3, [r12, #(0xfe << 1)]     @//REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1006FE << 1))

    orr         r3, r3, #0x0100
    str         r3, [r12, #(0xfe << 1)]     @//REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1006FE << 1))
    bic         r3, r3, #0x0100
    str         r3, [r12, #(0xfe << 1)]     @//REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1006FE << 1))

#endif

    bx          lr

@//-------------------------------------------------------------------------------------------------
@// MiuBistTest
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------

    .global     Miu1_BistTest
Miu1_BistTest:

    DPUTK_STR   MIU_MESSAGE_BIST1

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe0 << 1)]    @//reset bist test

    ldr         r11, [r12, #(0xf8 << 1)]
    ldr         r0, =0x8000
    orr         r11, r11, r0
    str         r11, [r12, #(0xf8 << 1)]    @//1012f8 bit_15=1 choice to MIU_1

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x162000 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xf8 << 1)]
    b           Miu_BistTest

    .global     Miu0_BistTest
Miu0_BistTest:

    DPUTK_STR   MIU_MESSAGE_BIST0

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe0 << 1)]    @//reset bist test

    ldr         r11, [r12, #(0xf8 << 1)]
    ldr         r0, =0x8000
    bic         r11, r11, r0
    str         r11, [r12, #(0xf8 << 1)]    @//1012f8 bit_15=0 choice to MIU_0

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x162000 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xf8 << 1)]

    .global     Miu_BistTest
Miu_BistTest:
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe2 << 1)]    @//start address base unit: 4k bytes

    ldr         r0, =0xFFFF
    ldr         r11, =BIST_LEN
    and         r11, r11, r0
    str         r11, [r12, #(0xe4 << 1)]
    ldr         r11, =BIST_LEN
    lsr         r11, #16
    and         r11, r11, r0
    str         r11, [r12, #(0xe6 << 1)]

    ldr         r11, =0x5aa5
    str         r11, [r12, #(0xe8 << 1)]    @//bist test pattern

#ifdef CONFIG_MSTAR_SELF_STR_TEST_ENABLE
    RREG        r0, (MS_BUS_RIU_ADDR + (0x0E6E << 1))   @//Disable Divisor Latch Access
    bic         r0, r0, #0x00FF
    ldr         r1, =0xFF00
    cmp         r0, r1
    beq         Miu_Normal_Test_Level

    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0101   @//bist test mode:3 + read mode
    b           Miu_CheckBistLoop

Miu_Normal_Test_Level:
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0003   @//bist test mode:3

#else
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0003   @//bist test mode:3

#endif

Miu_CheckBistLoop:
    RREG        r1, (MS_BUS_RIU_ADDR + (0x1012e0 << 1))
    and         r0, r1, #0x8000
    cmp         r0, #0
    beq         Miu_CheckBistLoop

    and         r0, r1, #0x6000
    cmp         r0, #0
    beq         Miu_Bist_OK

Miu_Bist_Fail:
    DPUTK_STR   MIU_MESSAGE_FAIL

Miu_Bist_FailLoop:
    b           Miu_Bist_FailLoop

Miu_Bist_OK:
    DPUTK_STR   MIU_MESSAGE_OK

Miu_Bist_Exit:

    bx          lr

@//================================================================================================
#ifdef CONFIG_ENABLE_AUTO_DQS

#define REG_MIU_DTOP_BASE_ADDRESS       r10
#define REG_MIU_ATOP_BASE_ADDRESS       r11
#define REG_MIU_ARBITOR_BASE_ADDRESS    r12

@//================================================================================================
#if !defined(CONFIG_MIU1_DRAM_NONE)
    .global     Miu1_AutoPhase
Miu1_AutoPhase:

    DPUTK_STR   MIU_MESSAGE_AUTO_DQS1

    ldr         r10, =(MS_BUS_RIU_ADDR + (0x100600 << 1))   @//MIU1_DTOP
    ldr         r11, =(MS_BUS_RIU_ADDR + (0x161600 << 1))   @//MIU1_ATOP
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x162200 << 1))   @//MIU1_ARB_DIG

    b           Miu_AutoPhase
#endif

@//================================================================================================
#if !defined(CONFIG_MIU0_DRAM_NONE)
    .global     Miu0_AutoPhase
Miu0_AutoPhase:

    DPUTK_STR   MIU_MESSAGE_AUTO_DQS0

    ldr         r10, =(MS_BUS_RIU_ADDR + (0x101200 << 1))   @//MIU0_DTOP
    ldr         r11, =(MS_BUS_RIU_ADDR + (0x110d00 << 1))   @//MIU0_ATOP
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x161500 << 1))   @//MIU0_ARB_DIG
#endif

    .global     Miu_AutoPhase
Miu_AutoPhase:

    ldr         r9, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r0, =0x20e4
    str         r0, [r9, #(0xfe << 1)]

    ldr         r9, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
    ldr         r0, =0x0000
    str         r0, [r9, #(0xf8 << 1)]

    ldr         r9, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r0, =0x0000
    str         r0, [r9, #(0xe0 << 1)]
    ldr         r0, =0x0000
    str         r0, [r9, #(0xe2 << 1)]

    @//Set test length
    ldr         r9, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
    ldr         r0, =0x0000
    str         r0, [r9, #(0xe6 << 1)]

    @//Enable SI mode
    ldr         r9, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r0, =0x11c1
    str         r0, [r9, #(0xd4 << 1)]

    @//Enable miu_test limit mask
    ldr         r0, =0x8000
    str         r0, [r12, #(0x1c << 1)]

    @//DPAT engine pre-setting
    ldr         r9, =(MS_BUS_RIU_ADDR + (0x161500 << 1))
    ldr         r0, =0x0004
    str         r0, [r9, #(0x78 << 1)]
    ldr         r0, =0x0000
    str         r0, [r9, #(0x78 << 1)]
    
    ldr         r0, =0x0000
    str         r0, [r12, #(0x70 << 1)]
    ldr         r0, =0x0000
    str         r0, [r12, #(0x72 << 1)]
    ldr         r0, =0x0833
    str         r0, [r12, #(0x74 << 1)]
    ldr         r0, =0x8000
    str         r0, [r12, #(0x7c << 1)]

    @//STEP 1: Set RX DQS Phase = 1/2* Kcode + offset
    ldr         r0, =0x0000
    str         r0, [r11, #(0x70 << 1)]
    ldr         r0, =0xf0f1
    str         r0, [r11, #(0x90 << 1)]
    ldr         r0, =0x0800
    str         r0, [r11, #(0x70 << 1)]

    @//STEP 2 : Enable TX DQ deskew scan (by DPAT engine)
    ldr         r9, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r0, =0x0090
    str         r0, [r9, #(0xe4 << 1)]
    ldr         r0, =0x11c0
    str         r0, [r9, #(0xd4 << 1)]
    ldr         r0, =0x11c1
    str         r0, [r9, #(0xd4 << 1)]

    ldr         r0, =0xffff
    str         r0, [r11, #(0xc8 << 1)]
    ldr         r0, =0xffff
    str         r0, [r11, #(0xca << 1)]
    ldr         r0, =0x00ff
    str         r0, [r11, #(0xcc << 1)]

    ldr         r0, =0x0002
    str         r0, [r12, #(0x76 << 1)]
    ldr         r0, =0x0013
    str         r0, [r12, #(0x78 << 1)]

Miu_AutoDqs_WaitDpatLoop_0:
    ldr         r0, [r12, #(0x78 << 1)]
    ldr         r1, =0x8000
    and         r0, r0, r1
    cmp         r0, #0
    beq         Miu_AutoDqs_WaitDpatLoop_0

    @//STEP 3 : Read TX DQ deskew result & write to REGs
    ldr         r0, =0x0004
    str         r0, [r11, #(0xc0 << 1)]

    ldr         r0, [r11, #(0xc2 << 1)]
    str         r0, [r11, #(0xd0 << 1)]

    ldr         r0, [r11, #(0xc4 << 1)]
    str         r0, [r11, #(0xd2 << 1)]

    ldr         r0, [r11, #(0xc6 << 1)]
    and         r1, r0, #0x00ff
    str         r1, [r11, #(0xd8 << 1)]

    mov         r1, r0, lsr #0x08
    and         r1, r1, #0x00ff
    str         r1, [r11, #(0xe8 << 1)]

    ldr         r0, =0x0005
    str         r0, [r11, #(0xc0 << 1)]

    ldr         r0, [r11, #(0xc2 << 1)]
    str         r0, [r11, #(0xd4 << 1)]

    ldr         r0, [r11, #(0xc4 << 1)]
    str         r0, [r11, #(0xd6 << 1)]

    ldr         r0, [r11, #(0xc6 << 1)]
    str         r0, [r11, #(0x2e << 1)]

    ldr         r0, =0x0006
    str         r0, [r11, #(0xc0 << 1)]

    ldr         r0, [r11, #(0xc2 << 1)]
    str         r0, [r11, #(0xe0 << 1)]

    ldr         r0, [r11, #(0xc4 << 1)]
    str         r0, [r11, #(0xe2 << 1)]

    ldr         r0, =0x0007
    str         r0, [r11, #(0xc0 << 1)]

    ldr         r0, [r11, #(0xc2 << 1)]
    str         r0, [r11, #(0xe4 << 1)]

    ldr         r0, [r11, #(0xc4 << 1)]
    str         r0, [r11, #(0xe6 << 1)]

    @//STEP 4 : Enable RX DQ/DQS deskew (by DPAT engine)
    ldr         r9, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r0, =0x2400
    str         r0, [r9, #(0xe4 << 1)]
    ldr         r0, =0x11c0
    str         r0, [r9, #(0xd4 << 1)]
    ldr         r0, =0x11c1
    str         r0, [r9, #(0xd4 << 1)]

    ldr         r0, =0x0000
    str         r0, [r11, #(0x70 << 1)]

    ldr         r9, =(MS_BUS_RIU_ADDR + (0x161500 << 1))
    ldr         r0, =0x0000
    str         r0, [r9, #(0x78 << 1)]
    ldr         r0, =0x0004
    str         r0, [r9, #(0x78 << 1)]
    ldr         r0, =0x0000
    str         r0, [r9, #(0x78 << 1)]

    ldr         r0, =0x00f0
    str         r0, [r11, #(0x90 << 1)]
    ldr         r0, =0xffff
    str         r0, [r11, #(0x40 << 1)]
    ldr         r0, =0xffff
    str         r0, [r11, #(0x42 << 1)]
    ldr         r0, =0x000f
    str         r0, [r11, #(0x44 << 1)]
    ldr         r0, =0x0800
    str         r0, [r11, #(0x70 << 1)]
    ldr         r0, =0x0001
    str         r0, [r12, #(0x76 << 1)]
    ldr         r0, =0x0013
    str         r0, [r12, #(0x78 << 1)]

Miu_AutoDqs_WaitDpatLoop_1:
    ldr         r0, [r12, #(0x78 << 1)]
    ldr         r1, =0x8000
    and         r0, r0, r1
    cmp         r0, #0
    beq         Miu_AutoDqs_WaitDpatLoop_1

    @//STEP 5 : Read RX DQ deskew result & write to REGs
    ldr         r0, =0x0000
    str         r0, [r11, #(0xc0 << 1)]

    ldr         r0, [r11, #(0xc2 << 1)]
    str         r0, [r11, #(0xa0 << 1)]

    ldr         r0, [r11, #(0xc4 << 1)]
    str         r0, [r11, #(0xa2 << 1)]

    ldr         r0, =0x0001
    str         r0, [r11, #(0xc0 << 1)]

    ldr         r0, [r11, #(0xc2 << 1)]
    str         r0, [r11, #(0xa4 << 1)]

    ldr         r0, [r11, #(0xc4 << 1)]
    str         r0, [r11, #(0xa6 << 1)]

    ldr         r0, =0x0002
    str         r0, [r11, #(0xc0 << 1)]

    ldr         r0, [r11, #(0xc2 << 1)]
    str         r0, [r11, #(0xa8 << 1)]

    ldr         r0, [r11, #(0xc4 << 1)]
    str         r0, [r11, #(0xaa << 1)]

    ldr         r0, =0x0003
    str         r0, [r11, #(0xc0 << 1)]

    ldr         r0, [r11, #(0xc2 << 1)]
    str         r0, [r11, #(0xac << 1)]

    ldr         r0, [r11, #(0xc4 << 1)]
    str         r0, [r11, #(0xae << 1)]
    
    @//STEP 6 : Disable DPAT engine & Set DQS Phase = 1/2* Kcode+offset (ratio mode)
    ldr         r0, =0x0000
    str         r0, [r11, #(0x70 << 1)]
    ldr         r0, =0xf001
    str         r0, [r11, #(0x90 << 1)]
    ldr         r0, =0x0000
    str         r0, [r12, #(0x78 << 1)]
    ldr         r0, =0x0830
    str         r0, [r12, #(0x74 << 1)]
    ldr         r0, =0x0800
    str         r0, [r11, #(0x70 << 1)]

    ldr         r0, =0x0000
    str         r0, [r12, #(0x1c << 1)]

    @//Disable SI mode
    ldr         r9, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
@// ldr         r0, =0x08e4
@// str         r0, [r9, #(0xfe << 1)]
    ldr         r0, =0x11c0
    str         r0, [r9, #(0xd4 << 1)]

@//================================================================================================
Miu_AutoDqs_Exit:

    DPUTK_STR   MIU_MESSAGE_OK

    ldr         r1, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r0, [r1, #(0xf0 << 1)]      @//Select BIST to MIU0 (0x1012F0[15] = 0)
    bic         r0, r0, #0x8000
    str         r0, [r1, #(0xf0 << 1)]

    bx          lr

#endif
@//================================================================================================

    .size       BootRom_InitMiu,.-BootRom_InitMiu
