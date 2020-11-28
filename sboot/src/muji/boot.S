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

#define CPUECTLR_EL1 S3_1_C15_C2_1

    .text

#-------------------------------------------------------------------------------------------------
# Boot_Entry:
# @param  None
# @return None
# @note   Entry point of Boot code
#-------------------------------------------------------------------------------------------------
    .globl      Boot_Entry


#if defined(CONFIG_64BIT_TO_32BIT_MODE)
    .globl      vectors



vectors:
    ventry      el1_sync_invalid                // Synchronous EL1t
    ventry      el1_irq_invalid                 // IRQ EL1t
    ventry      el1_fiq_invalid                 // FIQ EL1t
    ventry      el1_error_invalid               // Error EL1t

    ventry      el1_sync                        // Synchronous el1h
    ventry      el1_irq                         // IRQ EL1h
    ventry      el1_fiq_invalid                 // FIQ EL1h
    ventry      el1_error_invalid               // Error EL1h

    ventry      el0_sync                        // Synchronous 64-bit EL0
    ventry      el0_irq                         // IRQ 64-bit EL0
    ventry      el0_fiq_invalid                 // FIQ 64-bit EL0
    ventry      el0_error_invalid               // Error 64-bit EL0

    ventry      el0_sync_invalid                // Synchronous 32-bit EL0
    ventry      el0_irq_invalid                 // IRQ 32-bit EL0
    ventry      el0_fiq_invalid                 // FIQ 32-bit EL0
    ventry      el0_error_invalid               // Error 32-bit EL0

el1_sync_invalid:
    //b  .
    b Boot_Entry
el1_irq_invalid:
    b  .
el1_fiq_invalid:
    b  .
el1_error_invalid:
    b  .
el1_sync:
    b  .
el1_irq:
    b  .
el0_sync:
    b  .
el0_irq:
    b  .
el0_fiq_invalid:
    b  .
el0_error_invalid:
    b  .
el0_sync_invalid:
    b CH_EXEC_MODE
    //b  .
el0_irq_invalid:
    b  .

CH_EXEC_MODE:

    mov      x0, #0x441
    msr      SCR_EL3, x0
    msr      ELR_EL3, x30

    mrs      x1,spsr_el3
    //orr      x1, x1,#0x3
    bic      x1,x1,#0x3
    bic      x1,x1,#0xF
    bic      x1,x1,#(1 << 4)
    //orr      x1, x1,#(1 << 4)
    orr      x1, x1,#0x1
    orr      x1, x1,#(1 << 3)
    msr      spsr_el3, x1

    //mov              x0, #0x1d3
    //msr              SPSR_EL2, x0
    //msr              ELR_EL2, x30
    eret

#endif

Boot_Entry:
    #//Set WDT period maximum value to 0 to disable watchdog timer
    WREG        (MS_BUS_RIU_ADDR + (0x3008 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x300a << 1)), 0x0000
Boot_Start:

    #//Initalize the PIU timer to measure boot time
    bl          BootRom_InitTimer
    
    RREG        w7, (MS_BUS_RIU_ADDR + (0x000e52 << 1))
#ifndef CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51
    #//Reset PM51
    bic         w7, w7, #0x00001000         
#endif
    #//Set deglitch period for vdd2low_rst and chip_top_powergood
    orr         w7, w7, #0x0000003f         
    REG_C2M     w7, (MS_BUS_RIU_ADDR + (0x000e52 << 1))

    DBGREG      0x3697
    
    #//Initialize CPU Registers
    bl          Boot_InitCpuRegister        

    DBGREG      0x0000
   
    #//Only CPU0 continues to execute and the secondary CPUs execute Boot_SecondaryCore
    mrs         x7, MPIDR_EL1               //Read Multiprocessor Affinity Register
    ands        x7, x7, #0x03               //Mask off, leaving the CPU ID field
    b.ne        Boot_SecondaryCore

Boot_PrimaryCore:    
    ldr         x7, =BootRom_Entry          //Jump to Entry Point of BootRom
    br          x7                          //Jump to Entry Point of BootRom

Boot_SecondaryCore:

    #//Enable IRQ on EL3
    mrs         x7, SCR_EL3
    orr         x7, x7, #0x02
    msr         SCR_EL3, x7

    #//Set Priority Mask Register in CPU Interface
    WREG        (REG_GIC_CPU_BASE_ADDRESS + 0x04), 0xf0

    #//Set Control Register in CPU Interface to Enable Software Interrupt
    WREG        (REG_GIC_CPU_BASE_ADDRESS + 0x00), 0x01

    WREG        (MS_BUS_RIU_ADDR + (0x1033A2 << 1)), 0xff
    
    wfi

    #//Core 1/2/3 must jump to DRAM space to avoid SPI flash hang issue
    ldr         x7, =Bootram_SecondaryCore
    br          x7

Boot_SecondaryCoreLoop:
    b           Boot_SecondaryCoreLoop

#-------------------------------------------------------------------------------------------------
# Boot_InitCpuRegister
# @param  None
# @return None
# @note   ARM internal register init setting
#-------------------------------------------------------------------------------------------------
Boot_InitCpuRegister:
    mrs     x7, SCTLR_EL3               //System Control Register (EL3)
    mov     x8, #(0x1 << 12)            //Clear I bit 12 to disable I Cache
    orr     x8, x8, #(0x1 << 2)         //Clear C bit  2 to disable D Cache
    orr     x8, x8, #(0x1 << 0)         //Clear M bit  0 to disable MMU
    orr     x8, x8, #(0x1 << 11)        //Clear Z bit 11 to disable branch prediction
    bic     x7, x7, x8
    msr     SCTLR_EL3, x7               //Write System Control Register

    mrs     x7, CPUECTLR_EL1            //CPU extended control register, EL1
    orr     x7, x7, #(0x1 << 6)         //Enable hardware management of data coherency with other processors in SMP system
    msr     CPUECTLR_EL1, x7

    ret

#-------------------------------------------------------------------------------------------------
# BOOT_Pad
# @param  None
# @return None
# @note   Pad with zeros (Reserve SIZE_BOOT_RESERVED Bytes for boot)
#-------------------------------------------------------------------------------------------------
    .org        (SIZE_BOOT_RESERVED - 4)
    .word       0
