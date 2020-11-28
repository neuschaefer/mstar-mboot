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
    .globl      _vector

_vector:
    b           Boot_Entry      @//Offset 0x00: Reset

_undefined_instruction:
    b           .               @//Offset 0x04: Undefined Instruction

_software_interrupt:
    b           .               @//Offset 0x08: Software Interrupt or Secure Monitor Call (SMC)

_prefetch_abort:
    b           .               @//Offset 0x0C: Prefetch Abort (Instruction)

_data_abort:
    b           .               @//Offset 0x10: Data Abort (Data)

_not_used:
    b           .               @//Offset 0x14: Reserved

_irq:
    b           .               @//Offset 0x18: IRQ

_fiq:
    b           .               @//Offset 0x1C: FIQ

@//-------------------------------------------------------------------------------------------------
@// Boot_Entry:
@// @param  None
@// @return None
@// @note   Entry point of Boot code
@//-------------------------------------------------------------------------------------------------
    .globl      Boot_Entry

Boot_Entry:

#if !defined(CONFIG_EMMC_BOOT) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH) && \
    !defined(CONFIG_BOOTING_FROM_EXT_EMMC_WITH_CPU)

    @// 8051 instruction: jump 0xb00
    .byte       0x02, 0x0b, 0x00, 0x00

    @//Set bonding overwrite to ARM bootup without EJTAG
@// WREG        (MS_BUS_RIU_ADDR + (0x0e3e << 1)), 0x4f

#endif

    @//Initalize the PIU timer to measure boot time
    bl          BootRom_InitTimer

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

    @//Set WDT period maximum value to 0 to disable watchdog timer
    WREG        (MS_BUS_RIU_ADDR + (0x3008 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x300a << 1)), 0x0000

    DBGREG      0x3697

    bl          Boot_InitCpuRegister        @//Initialize CPU Registers

    DBGREG      0x0000

    mrc         p15, 0, r0, c0, c0, 5
    and         r0, #0x03                   @//Single Core
    cmp         r0, #0
    beq         Boot_PrimaryCore

    bl          Boot_SecondaryCore

Boot_PrimaryCore:

    ldr         pc, =BootRom_Entry          @//Jump to Entry Point of BootRom

Boot_SecondaryCore:
                                            @//Enable software interrupt
    @//Set Priority Mask Register in CPU Interface
    WREG        (REG_GIC_CPU_BASE_ADDRESS + 0x04), 0xf0

    @//Set Control Register in CPU Interface to Enable Software Interrupt
    WREG        (REG_GIC_CPU_BASE_ADDRESS + 0x00), 0x01

                                            @//SECOND_START_ADDR_HI = 0x1f206740
                                            @//SECOND_START_ADDR_LO = 0x1f206744
                                            @//set LSB[1:0] of LO = 2'b11, then wait soft interrupt to wake up
    WREG        (MS_BUS_RIU_ADDR + (0x1033A2 << 1)), 0xff

    wfi

    @//Core 1 must jump to DRAM space to avoid SPI flash hang issue
    ldr         pc, =Bootram_SecondaryCore

Boot_SecondaryCoreLoop:
    b           Boot_SecondaryCoreLoop

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

    mrc         p15, 0, r0, c1, c1, 2
    ldr         r1, =0x0007cc00
    orr         r0, r0, r1
    mcr         p15, 0, r0, c1, c1, 2

    mrc         p15, 0, r0, c1, c0, 1
    orr         r0, r0, #(0x01 << 6)        @//Enable ACTLR.SMP bit
    mcr         p15, 0, r0, c1, c0, 1

    mrc         p15, 0, r0, c1, c0, 2
    orr         r0, r0, #(0x0f << 20)       @//Enable Access Rights for CP10/CP11
    mcr         p15, 0, r0, c1, c0, 2
    isb

    bx          lr

@//-------------------------------------------------------------------------------------------------
@// PM51 Byte Code
@// @param  None
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
#if !defined(CONFIG_EMMC_BOOT) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH) && \
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
    .org        (SIZE_BOOT_RESERVED - 4)
    .word       0
#endif
