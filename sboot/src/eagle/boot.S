/*
 *#############################################################################
 *
 * Copyright (c) 2006-2012 MStar Semiconductor, Inc.
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
    .globl      _vector

_vector:
    b           Boot_Entry

_undefined_instruction:
    b           .

_software_interrupt:
    b           .

_prefetch_abort:
    b           .

_data_abort:
    b           .

_not_used:
    b           .

_irq:
    b           .

_fiq:
    b           .

@//-------------------------------------------------------------------------------------------------
@// Boot_Entry:
@// @param  None
@// @return None
@// @note   Entry point of Boot code
@//-------------------------------------------------------------------------------------------------
    .globl      Boot_Entry

Boot_Entry:

    # initalize the PIU timer1 to measure boot time
    WREG  0x1f006088, 0xFFFF
    WREG  0x1f00608C, 0xFFFF
    WREG  0x1f006080, 0x0000
    WREG  0x1f006080, 0x0001

#if !defined(CONFIG_EMMC_BOOT) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) && \
    !defined(CONFIG_BOOTING_FROM_EXT_EMMC_WITH_CPU)
    @// 8051 instruction: jump 0xb00
    .byte       0x02, 0x0b, 0x00, 0x00

    @//Set bonding overwrite to ARM bootup without EJTAG
    WREG        (MS_BUS_RIU_ADDR + (0x0e3e << 1)), 0x4f
#endif

#ifndef CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51
    RREG        r8, (MS_BUS_RIU_ADDR + (0x0E52 << 1))
    bic         r8, r8, #0x1000
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x0E52 << 1))
#endif

    RREG        r3, (MS_BUS_RIU_ADDR + (0x000E52 << 1))
    ldr         r4, =0x0000003F
    orr         r3, r3, r4
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x000E52 << 1))

Boot_Start:

    @//Enable SRAM
    WREG        (MS_BUS_RIU_ADDR + (0x0ecc << 1)), 0x7777
    WREG        (MS_BUS_RIU_ADDR + (0x0ece << 1)), 0x7777

    @//Set WDT period maximum value to 0 to disable watchdog timer
    WREG        (MS_BUS_RIU_ADDR + (0x3008 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x300a << 1)), 0x0000

    DBGREG      0x3697

    bl          Boot_InitCpuRegister        @//Initialize CPU Registers

    DBGREG      0x0000

#ifndef CONFIG_MSTAR_ASIC_EMULATION_ENABLE

    ldr         pc, =BootRom_Entry          @//Jump to Entry Point of BootRom

#else
    mrc         p15, 0, r0, c0, c0, 5
    and         r0, #0x03                   @//Single Core
    cmp         r0, #0
    beq         Boot_PrimaryCore

    bl          Boot_SecondaryCore

Boot_PrimaryCore:

    ldr         pc, =BootRom_Entry          @//Jump to Entry Point of BootRom

Boot_SecondaryCore:
                                            @//Enable software interrupt
    ldr         r5, =0x16000100             @//CPU_INTERFACE -> control register
    mov         r6, #0x1
    str         r6, [r5, #0x00]
    mov         r6, #0xf0
    str         r6, [r5, #0x04]             @//CPU_INTERFACE -> priority mask register

                                            @// SECOND_START_ADDR_HI = 0x1f206740
                                            @// SECOND_START_ADDR_LO = 0x1f206744
                                            @// set LSB[1:0] of LO = 2'b11, then wait soft interrupt to wake up
    WREG        (MS_BUS_RIU_ADDR + (0x1033A2 << 1)), 0xff
    wfi                                     @//wait SWI to check

    @//Core 1 must jump to DRAM space to avoid SPI flash hang issue
    ldr         pc, =Bootram_SecondaryCore

#if 0
    RREG        r0, (MS_BUS_RIU_ADDR + (0x1033A2 << 1))
    and         r0, #0x03
    cmp         r0, #0
    bne         Boot_SecondaryCore          @//make sure start address of secondary is legal

    RREG        r0, (MS_BUS_RIU_ADDR + (0x1033A0 << 1))
    RREG        r1, (MS_BUS_RIU_ADDR + (0x1033A2 << 1))
    add         r2, r1, r0, lsl #16
    mov         pc, r2
#endif

Boot_SecondaryCoreLoop:
    b           Boot_SecondaryCoreLoop

#endif

@//-------------------------------------------------------------------------------------------------
@// Boot_InitCpuRegister
@// @param  None
@// @return None
@// @note   ARM internal register init setting
@//-------------------------------------------------------------------------------------------------
Boot_InitCpuRegister:

    mrs         r0, cpsr
    orr         r0, r0, #0xc0               @//Disable IRQ and FIQ
    orr         r0, r0, #0xd3               @//Set ARM mode and Supervisor mode
    msr         cpsr_c, r0

    mrc         p15, 0, r0, c1, c0, 0
    bic         r0, r0, #0x01               @//Disable MMU
    bic         r0, r0, #0x04               @//Disable D-Cache
    bic         r0, r0, #0x1000             @//Disable I-Cache
    mcr         p15, 0, r0, c1, c0, 0

@// mov         ip, lr
@// bl          BootRom_InvalidateCache     @//Invalidate Cache
@// mov         lr, ip

    bx          lr

#if 0
@//-------------------------------------------------------------------------------------------------
@// Invalidate Caches
@// @param  None
@// @return None
@// @note   __invalidate_v7_cache
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_InvalidateCache
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

#endif

@//-------------------------------------------------------------------------------------------------
@// PM51 Byte Code
@// @param  None
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
#if !defined(CONFIG_EMMC_BOOT) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) && \
    !defined(CONFIG_BOOTING_FROM_EXT_EMMC_WITH_CPU)

    .org        0xb00

    .byte       0xc2, 0xaf                  @//;    clr     EA

    .byte       0x75, 0xa0, 0x00            @//;    MOV     P2, #00H        #//Enable SRAM
    .byte       0x90, 0x0e, 0xcc            @//;    MOV     DPTR, #0ECCH
    .byte       0x74, 0x77                  @//;    MOV     A, #077H
    .byte       0xf0                        @//;    MOVX    @DPTR, A

    .byte       0x90, 0x0e, 0xcd            @//;    MOV     DPTR, #0ECDH
    .byte       0x74, 0x77                  @//;    MOV     A, #077H
    .byte       0xf0                        @//;    MOVX    @DPTR, A

    .byte       0x90, 0x0e, 0xce            @//;    MOV     DPTR, #0ECEH
    .byte       0x74, 0x77                  @//;    MOV     A, #077H
    .byte       0xf0                        @//;    MOVX    @DPTR, A

    .byte       0x90, 0x0e, 0xcf            @//;    MOV     DPTR, #0ECFH
    .byte       0x74, 0x77                  @//;    MOV     A, #077H
    .byte       0xf0                        @//;    MOVX    @DPTR, A

    .byte       0x71, 0x37                  @//;    Call    CheckPowerGood

    .byte       0x75, 0xa0, 0x10            @//;    MOV     P2, #10H
    .byte       0x90, 0x1e, 0x03            @//;    MOV     DPTR, #1E03H
    .byte       0xe0                        @//;    MOVX    A, @DPTR
    .byte       0x54, 0xef                  @//;    ANL     A, #11101111B   #//clr bit4,  disable boot from SDRAM
    .byte       0xf0                        @//;    MOVX    @DPTR, A

    .byte       0x75, 0xa0, 0x00            @//;    MOV     P2, #00H
    .byte       0x90, 0x0e, 0x53            @//;    MOV     DPTR, #0E53H
    .byte       0x74, 0xb0                  @//;    MOV     A, #B0H
    .byte       0xf0                        @//;    MOVX    @DPTR, A        #//Reset MIPS

    .byte       0x74, 0xe0                  @//;    MOV     A, #E0H
    .byte       0xf0                        @//;    MOVX    @DPTR, A        #//Reset 8051

                                            @//;MIAN_LOOP_END:
    .byte       0x80, 0xfe                  @//;    jmp     MAIN_LOOP_END
                                            @//;
                                            @//;ckPowerGood:
    .byte       0x75, 0xa0, 0x00            @//;    MOV     P2, #00H
    .byte       0x90, 0x0e, 0xc2            @//;    MOV     DPTR, #0EC2H
    .byte       0xe0                        @//;    MOVX    A, @DPTR        #//Check Power Good (No-Die, Core, 3.3V)
    .byte       0x54, 0x07                  @//;    ANL     A, #07H
    .byte       0xb4, 0x07, 0xf4            @//;    CJNE    A, #07H, CheckPowerGood
    .byte       0x22                        @//;    ret
                                            @//;    end

#-------------------------------------------------------------------------------------------------
# BOOT_Pad
# @param  None
# @return None
# @note   Pad with zeros (Reserve SIZE_BOOT_RESERVED Bytes for boot)
#-------------------------------------------------------------------------------------------------
    .org        (SIZE_BOOT_RESERVED-4)
    .word       0
#endif
