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
    
    .global     BootRom_InitCache
BootRom_InitCache:

    mov         ip, lr
    bl          BootRom_InvalidateCache     @//Invalidate Cache
    mov         lr, ip

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

@//-------------------------------------------------------------------------------------------------
@// Invalidate Caches
@// @param  None
@// @return None
@// @note   __invalidate_v7_cache
@//-------------------------------------------------------------------------------------------------
BootRom_InvalidateCache:

    mov         r0, #0
    mcr         p15, 0, r0, c8, c7, 0       @//Invalidate Inst TLB and Data TLB
    mcr         p15, 0, r0, c7, c5, 0       @//Invalidate I-Cache

    @//Must iterate over the caches in order to synthesise a complete clean
    @//of data / unified cache

    mrc         p15, 1, r0, c0, c0, 1       @//read Cache Level ID register (clidr)
    ands        r3, r0, #0x7000000          @//extract level of coherency from clidr
    mov         r3, r3, lsr #23             @//left align level of coherency bit field
    beq         _InvalidateCache_Finished   @//if loc is 0, then no need to clean

    mov         r10, #0                     @//start clean at cache level 0 (in r10)

_InvalidateCache_Loop1:
    add         r2, r10, r10, lsr #1        @//work out 3x current cache level
    mov         r1, r0, lsr r2              @//extract cache type bits from clidr
    and         r1, r1, #7                  @//mask of the bits for current cache only
    cmp         r1, #2                      @//see what cache we have at this level
    blt         _InvalidateCache_Skip       @//skip if no cache, or just i-cache

    mcr         p15, 2, r10, c0, c0, 0      @//select current cache level in cssr
    mov         r1, #0
    mcr         p15, 0, r1, c7, c5, 4       @//prefetchflush to synch the new cssr&csidr
    mrc         p15, 1, r1, c0, c0, 0       @//read the new csidr
    and         r2, r1, #7                  @//extract the length of the cache lines
    add         r2, r2, #4                  @//add 4 (line length offset)
    ldr         r6, =0x03ff
    ands        r6, r6, r1, lsr #3          @//find maximum number on the way size

    .word       0xe16f5f16                  @//DCI   0xE16F5F16 @CLZ r5, r6 @ find bit position of way size increment
    ldr         r7, =0x7fff
    ands        r7, r7, r1, lsr #13         @//extract max number of the index size

_InvalidateCache_Loop2:
    mov         r8, r6                      @//create working copy of max way size

_InvalidateCache_Loop3:
    orr         r11, r10, r8, lsl r5        @//factor way and cache number into r11
    orr         r11, r11, r7, lsl r2        @//factor index number into r11
    mcr         p15, 0, r11, c7, c6, 2      @//invalidate by set/way
    subs        r8, r8, #1                  @//decrement the way
    bge         _InvalidateCache_Loop3

    subs        r7, r7, #1                  @//decrement the index
    bge         _InvalidateCache_Loop2

_InvalidateCache_Skip:
    add         r10, r10, #2                @//increment cache number
    cmp         r3, r10
    bgt         _InvalidateCache_Loop1

_InvalidateCache_Finished:
    bx          lr

    .size       BootRom_InitCache,.-BootRom_InitCache
    
    .end

