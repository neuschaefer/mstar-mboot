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

    .text

#-------------------------------------------------------------------------------------------------
# Boot_Entry:
# @param  None
# @return None
# @note   Entry point of Boot code
#-------------------------------------------------------------------------------------------------
    .globl      Boot_Entry

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

#if 0
    #//Set Priority Mask Register in CPU Interface
    WREG        (REG_GIC_CPU_BASE_ADDRESS + 0x04), 0xf0

    #//Set Control Register in CPU Interface to Enable Software Interrupt
    WREG        (REG_GIC_CPU_BASE_ADDRESS + 0x00), 0x01

                                            @//SECOND_START_ADDR_HI = 0x1f206740
                                            @//SECOND_START_ADDR_LO = 0x1f206744
                                            @//set LSB[1:0] of LO = 2'b11, then wait soft interrupt to wake up
    WREG        (MS_BUS_RIU_ADDR + (0x1033A2 << 1)), 0xff
#endif 

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
    mov     x8, #(0x8 << 12)            //Clear I bit 12 to disable I Cache
    orr     x8, x8, #(0x8 << 2)         //Clear C bit  2 to disable D Cache
    orr     x8, x8, #(0x8 << 0)         //Clear M bit  0 to disable MMU
    orr     x8, x8, #(0x8 << 11)        //Clear Z bit 11 to disable branch prediction
    bic     x7, x7, x8
    msr     SCTLR_EL3, x7               //Write System Control Register

    ret

#-------------------------------------------------------------------------------------------------
# BOOT_Pad
# @param  None
# @return None
# @note   Pad with zeros (Reserve SIZE_BOOT_RESERVED Bytes for boot)
#-------------------------------------------------------------------------------------------------
    .org        (SIZE_BOOT_RESERVED - 4)
    .word       0
