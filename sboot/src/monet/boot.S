/*
 *#############################################################################
 *
 * Copyright (c) 2006-2015 MStar Semiconductor, Inc.
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

//=================================================================================================
_synchronous_sp0:               //Offset 0x000: Synchronous (SP0)
    b           Boot_Entry

    .align      7
_irq_sp0:                       //Offset 0x080: Irq (SP0)
    b           .

    .align      7
_fiq_sp0:                       //Offset 0x100: Fiq (SP0)
    b           .

    .align      7
_system_error_sp0:              //Offset 0x180: System Error (SP0)
    b           .

//=================================================================================================
    .align      7
_synchronous_spx:               //Offset 0x200: Synchronous (SPx)
    b           .

    .align      7
_irq_spx:                       //Offset 0x280: Irq (SPx)
    b           .

    .align      7
_fiq_spx:                       //Offset 0x300: Fiq (SPx)
    b           .

    .align      7
_system_error_spx:              //Offset 0x380: System Error (SPx)
    b           .

//=================================================================================================
    .align      7
_synchronous_aarch64:           //Offset 0x400: Synchronous (AArch64)
    b           .

    .align      7
_irq_aarch64:                   //Offset 0x480: Irq (AArch64)
    b           .

    .align      7
_fiq_aarch64:                   //Offset 0x500: Fiq (AArch64)
    b           .

    .align      7
_system_error_aarch64:          //Offset 0x580: System Error (AArch64)
    b           .

//=================================================================================================
    .align      7
_synchronous_aarch32:           //Offset 0x600: Synchronous (AArch32)
//  b           .
    mov         x0, #0x441
    msr         SCR_EL3, x0
    msr         ELR_EL3, x30
    mrs         x1, spsr_el3
    bic         x1, x1, #0x03
    bic         x1, x1, #0x0F
    bic         x1, x1, #(0x01 << 4)
    orr         x1, x1, #0x01
    orr         x1, x1, #(0x01 << 3)
    msr         spsr_el3, x1
    eret

    .align      7
_irq_aarch32:                   //Offset 0x680: Irq (AArch32)
    b           .

    .align      7
_fiq_aarch32:                   //Offset 0x700: Fiq (AArch32)
    b           .

    .align      7
_system_error_aarch32:          //Offset 0x780: System Error (AArch32)
    b           .

//=================================================================================================
// Boot_Entry:
// @param  None
// @return None
// @note   Entry point of Boot code
//=================================================================================================
    .globl      Boot_Entry

Boot_Entry:

    //Set WDT period maximum value to 0 to disable watchdog timer
    WREG        (MS_BUS_RIU_ADDR + (0x3008 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x300a << 1)), 0x0000

Boot_Start:

    //Initalize the PIU timer to measure boot time
    bl          BootRom_InitTimer

    RREG        w3, (MS_BUS_RIU_ADDR + (0x000e52 << 1))
#ifndef CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51
    bic         w3, w3, #0x00001000         //Reset PM51
#endif
    orr         w3, w3, #0x0000003f         //Set deglitch period for vdd2low_rst and chip_top_powergood
    REG_C2M     w3, (MS_BUS_RIU_ADDR + (0x000e52 << 1))

    DBGREG      0x3697

    bl          Boot_InitCpuRegister        //Initialize CPU Registers

    DBGREG      0x0000

    mrs         x0, MPIDR_EL1
    and         x0, x0, #0x03               //Single Core
    cmp         x0, #0
    b.eq        Boot_PrimaryCore

    bl          Boot_SecondaryCore

Boot_PrimaryCore:

    ldr         x30, =BootRom_Entry         //Jump to Entry Point of BootRom
    ret

Boot_SecondaryCore:

                                            //Enable software interrupt
    //Enable IRQ on EL3
    mrs         x0, SCR_EL3
    orr         x0, x0, #0x02
    msr         SCR_EL3, x0

    //Set Priority Mask Register in CPU Interface
    WREG        (REG_GIC_CPU_BASE_ADDRESS + 0x04), 0xf0

    //Set Control Register in CPU Interface to Enable Software Interrupt
    WREG        (REG_GIC_CPU_BASE_ADDRESS + 0x00), 0x01

                                            //SECOND_START_ADDR_HI = 0x1f206740
                                            //SECOND_START_ADDR_LO = 0x1f206744
                                            //set LSB[1:0] of LO = 2'b11, then wait soft interrupt to wake up
    WREG        (MS_BUS_RIU_ADDR + (0x1033A2 << 1)), 0xff

    wfi

    //Core 1 must jump to DRAM space to avoid SPI flash hang issue
    ldr         x30, =Bootram_SecondaryCore
    ret

Boot_SecondaryCoreLoop:
    b           Boot_SecondaryCoreLoop

//-------------------------------------------------------------------------------------------------
// Boot_InitCpuRegister
// @param  None
// @return None
// @note   ARM internal register init setting
//-------------------------------------------------------------------------------------------------
Boot_InitCpuRegister:

    mrs         x0, SCTLR_EL3               //System Control Register (EL3)
    bic         x0, x0, #(0x01 << 0)        //Disable MMU
    bic         x0, x0, #(0x01 << 2)        //Disable D Cache
    bic         x0, x0, #(0x01 << 11)       //Disable branch prediction
    bic         x0, x0, #(0x01 << 12)       //Disable I Cache
    msr         SCTLR_EL3, x0

    mrs         x0, S3_1_C15_C2_1           //CPU extended control register, EL1
    orr         x0, x0, #(0x1 << 6)         //Enable hardware management of data coherency with other processors in SMP system
    msr         S3_1_C15_C2_1, x0

    ret

//-------------------------------------------------------------------------------------------------
// BOOT_Pad
// @param  None
// @return None
// @note   Pad with zeros (Reserve SIZE_BOOT_RESERVED Bytes for boot)
//-------------------------------------------------------------------------------------------------
    .org        (SIZE_BOOT_RESERVED - 4)
    .word       0
