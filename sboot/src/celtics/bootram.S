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

#if defined(CONFIG_SBOOT_TO_KERNEL) && defined(CONFIG_MSTAR_TITANIA_BD_FPGA)
#define LINUX_KERNEL_FLASH_ADDRESS  0x14010000
#define LINUX_KERNEL_DRAM_ADDRESS   0x20208000
#define LINUX_KERNEL_ENTRY          0x20208000
#define LINUX_KERNEL_SIZE           0x00800000
#elif defined(CONFIG_MSTAR_TITANIA_BD_FPGA)
#define LINUX_KERNEL_FLASH_ADDRESS  0x14020000
#define LINUX_KERNEL_DRAM_ADDRESS   0x20400000
#define LINUX_KERNEL_ENTRY          0x20408000
#define LINUX_KERNEL_SIZE           0x00200000
#elif defined(CONFIG_SBOOT_TO_KERNEL)
#define LINUX_KERNEL_FLASH_ADDRESS  0x14010000
#define LINUX_KERNEL_DRAM_ADDRESS   0x20208000
#define LINUX_KERNEL_ENTRY          0x20208000
#define LINUX_KERNEL_SIZE           0x00800000
#endif

#//-------------------------------------------------------------------------------------------------
#// BOOTRAM_Entry:
#// @param  None
#// @return None
#// @note   Entry point of Boot code
#//-------------------------------------------------------------------------------------------------
    .globl      BOOTRAM_Entry

BOOTRAM_Entry:

    DPUTK       '_'

#//================================================================================================
#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) || defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)

    ldr         w7, =Bootram_SecondaryCore
    ldr         w8, =0xFFFF
    mov         w9, w7, lsr #16
    and         w9, w9, w8
    REG_C2M     w9, BOOT_INFO_REGISTER_CORE1_START_ADDR_HIGH

    and         w9, w7, w8
    REG_C2M     w9, BOOT_INFO_REGISTER_CORE1_START_ADDR_LOW

#endif

#//================================================================================================
    #//Initial Global Interrupt Interface
    WREG        (REG_GIC_DIST_BASE_ADDRESS + 0x0000), 0x00000001
    WREG        (REG_GIC_CPU_BASE_ADDRESS + 0x0004), 0x000000f0
    WREG        (REG_GIC_DIST_BASE_ADDRESS + 0x0180), 0xffff0000
    WREG        (REG_GIC_DIST_BASE_ADDRESS + 0x0100), 0x0000ffff
    WREG        (REG_GIC_CPU_BASE_ADDRESS + 0x0000), 0x00000001

    #//Initial Internal Interrupt Controller
    WREG        (REG_GIC_DIST_BASE_ADDRESS + 0x0F00), 0x000e0001

#//================================================================================================
#// Clear data in BSS section
#//================================================================================================

    ldr         x7, =_ld_bootbss_start
    ldr         x8, =_ld_bootbss_end

    cmp         x8,x7
    b.eq        _ClearBssExit

_ClearBssLoop:
    cmp         x7, x8
    str         wzr, [x7], #0x04
    b.ne         _ClearBssLoop

_ClearBssExit:

#//================================================================================================
#// Initialize system stack pointer for unzip subroutine
#//================================================================================================
    ldr         x7, =ADDR_STACK_POINTER
    mov         sp, x0

#if defined(CONFIG_MSTAR_TITANIA_BD_FPGA) 
#if defined(CONFIG_SBOOT_TO_KERNEL)
#//================================================================================================
#//Copy Image to DRAM
#//================================================================================================

    ldr         x7, =LINUX_KERNEL_FLASH_ADDRESS     //Starting Address of Linux Kernel in SPI Flash
    ldr         x8, =LINUX_KERNEL_DRAM_ADDRESS      //Dest Address of Linux Kernel in DRAM
    ldr         x9, =LINUX_KERNEL_SIZE              //Image Size of Linux Kernel

_CopyImageLoop:

    ldr         x10, [x7], #0x04
    str         x10, [x8], #0x04

    subs        x9, x9, #0x04

    ldr         x10, =0x0007FFFF
    and         x11, x9, x10
    cmp         x11, #0
    b.gt        _CopyImageLoop

    PUTK        '#'

    cmp         x9, #0
    b.gt         _CopyImageLoop

#//================================================================================================
#//Jump to Kernel Entry of Linux
#//================================================================================================

    PUTK        '\n'
    PUTK        '\r'

    ldr         x7, =LINUX_KERNEL_ENTRY
    br          x7
#else

    PUTK        'l'
    PUTK        'o'
    PUTK        'o'
    PUTK        'p'
    PUTK        '.'
    PUTK        '.'
    PUTK        '.'

BootRam_Loop:
    b BootRam_Loop

#endif /* defined(CONFIG_SBOOT_TO_KERNEL) */
#endif /* defined(CONFIG_MSTAR_TITANIA_BD_FPGA) */

#//================================================================================================
#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)
#//================================================================================================
    #//LOAD CHUNK HEADER
    ldr         x0, =CONFIG_UBOOT_LOADADDR
    ldr         x1, =0x400
    bl          drvNAND_LoaduBoot

    #// LOAD UBOOT
    ldr         x0, =CONFIG_UBOOT_LOADADDR
    ldr         w3, [x0, #0]    // UBOOT_ROM_START in MBOOT PARTITION
    ldr         w1, [x0, #4]    // UBOOT_RAM_START
    ldr         w2, [x0, #8]    // UBOOT_RAM_END
    sub         w1, w2, w1      // UBOOT_SIZE = UBOOT_RAM_END - UBOOT_RAM_START
    add         w1, w1, w3      // LOAD SIZE
    sub         w0, w0, w3
    bl          drvNAND_LoaduBoot

#elif defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    #//LOAD CHUNK HEADER
    ldr         x0, =CONFIG_UBOOT_LOADADDR
    ldr         x1, =0x400
    ldr         x2, =0x1000
    bl          eMMC_ReadData_MIU

    #// LOAD UBOOT
    ldr         x0, =CONFIG_UBOOT_LOADADDR
    ldr         x1, =0x180000
    ldr         x2, =0x1002
    bl          eMMC_ReadData_MIU
#else

    bl          DoMSDecompression

#endif

#//================================================================================================
#//Enter U-Boot
#//================================================================================================
BOOT_POINT:
    DPUTK       'U'

    WREG        0x1f006040, 0x0000          //Disable Hardware Timer 1

#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) || \
    defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    ldr         x7, =CONFIG_UBOOT_LOADADDR
    br          x7
#else

#ifndef CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51
#ifdef CONFIG_MSTAR_PM_SWIR
    ldr         x0, =0x14030000
#else
    ldr         x0, =0x14020000
#endif
#else
    ldr         x0, =0x14030000
#endif

    ldr         x7, [x0, #16]
    br          x7
#endif

#//================================================================================================
#//SecondaryCore loop
#//================================================================================================
    .globl      Bootram_SecondaryCore
Bootram_SecondaryCore:

    WREG        (MS_BUS_RIU_ADDR + (0x1033A2 << 1)), 0xff
    WREG        (CONFIG_KERNEL_START_ADDRESS + 0x8000), 0

Bootram_MpCoreLoop:

    wfi

    RREG        w1, (CONFIG_KERNEL_START_ADDRESS + 0x8000)
    ldr         w2, =0xbabe             //check magic number
    cmp         w1, w2
    b.ne        Bootram_MpCoreLoop

    RREG        w3, (CONFIG_KERNEL_START_ADDRESS + 0x8004)
    br          x3

Bootram_SecondaryCoreExit:
    b           Bootram_SecondaryCoreExit

#//-------------------------------------------------------------------------------------------------
#// BOOTRAM_Pad
#// @param  None
#// @return None
#// @note   Pad with zeros (Reserve SIZE_BOOTRAM_RESERVED Bytes for bootram)
#//-------------------------------------------------------------------------------------------------

    .org        (SIZE_BOOTRAM_RESERVED - 4)
    .word       0
