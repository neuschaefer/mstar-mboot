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

    .text
    
    .global     BootRom_InitCache
BootRom_InitCache:

    @//Invalidate D-cache by set/way
    @//Note: for Cortex-A9, there is no instruction for invalidating
    @//the whole D-cache. Need to invalidate line by line.
    @//Read cache size from the Cache Size Identification Register
    
    mrc         p15, 1, r3, c0, c0, 0       @//Read current Cache Size Identification Register

    ldr         r1, =0x01ff

    and         r3, r1, r3, LSR #13         @//r3 = (number of sets - 1)
    mov         r0, #0                      @//r0 -> way counter
way_loop:
    mov         r1, #0                      @//r1 -> set counter
set_loop:
    mov         r2, r0, LSL #30
    orr         r2, r1, LSL #5              @//r2 -> set/way cache-op format
    mcr         p15, 0, r2, c7, c6, 2       @//Invalidate line described by r2
    add         r1, r1, #1                  @//Increment set counter
    cmp         r1, r3                      @//Check if the last set is reached...
    ble         set_loop                    @//...if not, continue the set_loop...
    add         r0, r0, #1                  @//...else, Increment way counter
    cmp         r0, #4                      @//Check if the last way is reached...
    blt         way_loop                    @//...if not, continue the way_loop

    @//Enable dcaches
    @//D-cache is controlled by bit 2
    mrc         p15, 0, r0, c1, c0, 0       @//read CP15 register 1
    orr         r0, r0, #(0x1 <<2)          @//enable D Cache
    mcr         p15, 0, r0, c1, c0, 0       @//write CP15 register 1

    @//Enable Program Flow Prediction
    @//Branch prediction is controlled by the System Control Register:
    @//Set Bit 11 to enable branch prediciton and return stack
    @//Turning on branch prediction requires a general enable
    @//CP15, c1. Control Register
    @//Bit 11 [Z] bit Program flow prediction:
    @//0 = Program flow prediction disabled
    @//1 = Program flow prediction enabled.
    mrc         p15, 0, r0, c1, c0, 0       @//Read System Control Register
    orr         r0, r0, #(0x1 <<11)
    mcr         p15, 0, r0, c1, c0, 0       @//Write System Control Register

    @//Enable D-side prefetch
    @//Bit 2 [DP] Dside prefetch:
    @//0 = Dside prefetch disabled
    @//1 = Dside prefetch enabled.
    mrc         p15, 0, r0, c1, c0, 1       @//Read Auxiliary Control Register
    orr         r0, r0, #(0x1 <<2)          @//Enable Dside prefetch
    mcr         p15, 0, r0, c1, c0, 1       @//Write Auxiliary Control Register

    bx          lr

    .size       BootRom_InitCache,.-BootRom_InitCache
    
    .end

