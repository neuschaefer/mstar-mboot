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
#define LINUX_KERNEL_DRAM_ADDRESS   0x20200000
#define LINUX_KERNEL_ENTRY          0x20208000
#define LINUX_KERNEL_SIZE           0x00200000
#elif defined(CONFIG_SBOOT_TO_KERNEL)
#define LINUX_KERNEL_FLASH_ADDRESS  0x14010000
#define LINUX_KERNEL_DRAM_ADDRESS   0x20208000
#define LINUX_KERNEL_ENTRY          0x20208000
#define LINUX_KERNEL_SIZE           0x00800000
#endif

@//-------------------------------------------------------------------------------------------------
@// BOOTRAM_Entry:
@// @param  None
@// @return None
@// @note   Entry point of Boot code
@//-------------------------------------------------------------------------------------------------
    .globl      BOOTRAM_Entry

BOOTRAM_Entry:

    DPUTK       '_'

@//================================================================================================
#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) || \
    defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)

    ldr         r0, =Bootram_SecondaryCore
    ldr         r1, =0xFFFF
    mov         r2, r0, lsr #16
    and         r2, r2, r1
    REG_C2M     r2, BOOT_INFO_REGISTER_CORE1_START_ADDR_HIGH

    and         r2, r0, r1
    REG_C2M     r2, BOOT_INFO_REGISTER_CORE1_START_ADDR_LOW

#endif

@//================================================================================================
    @//Initial Global Interrupt Interface
    WREG        (REG_GIC_DIST_BASE_ADDRESS + 0x0000), 0x00000001
    WREG        (REG_GIC_CPU_BASE_ADDRESS + 0x0004), 0x000000f0
    WREG        (REG_GIC_DIST_BASE_ADDRESS + 0x0180), 0xffff0000
    WREG        (REG_GIC_DIST_BASE_ADDRESS + 0x0100), 0x0000ffff
    WREG        (REG_GIC_CPU_BASE_ADDRESS + 0x0000), 0x00000001

    @//Initial Internal Interrupt Controller
    WREG        (REG_GIC_DIST_BASE_ADDRESS + 0x0F00), 0x000e0001

@//================================================================================================
@// Clear data in BSS section

    ldr         r0, =_ld_bootbss_start
    ldr         r1, =_ld_bootbss_end
    mov         r2, #0

    cmp         r0, r1
    beq         _ClearBssExit

_ClearBssLoop:
    cmp         r0, r1
    str         r2, [r0], #0x04
    bne         _ClearBssLoop

_ClearBssExit:

@//================================================================================================
@// Initialize system stack pointer for unzip subroutine

#ifdef CONFIG_MSTAR_STR_MINISIZE
    ldr         r13, =CONFIG_KERNEL_START_ADDRESS
#else
    ldr         r13, =ADDR_STACK_POINTER
#endif

#if defined(CONFIG_MSTAR_TITANIA_BD_FPGA) || defined(CONFIG_SBOOT_TO_KERNEL)
@//================================================================================================
@//Copy Image to DRAM

    ldr         r0, =LINUX_KERNEL_FLASH_ADDRESS     @//Starting Address of Linux Kernel in SPI Flash
    ldr         r1, =LINUX_KERNEL_DRAM_ADDRESS      @//Dest Address of Linux Kernel in DRAM
    ldr         r2, =LINUX_KERNEL_SIZE              @//Image Size of Linux Kernel

_CopyImageLoop:

    ldr         r3, [r0], #0x04
    str         r3, [r1], #0x04

    subs        r2, r2, #0x04

    ldr         r3, =0x0007FFFF
    and         r4, r2, r3
    cmp         r4, #0
    bgt         _CopyImageLoop

    PUTK        '#'

    cmp         r2, #0
    bgt         _CopyImageLoop

@//================================================================================================
@//Jump to Kernel Entry of Linux

    PUTK        '\n'
    PUTK        '\r'

    ldr         pc, =LINUX_KERNEL_ENTRY

#endif

@//================================================================================================
#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)
    @//LOAD CHUNK HEADER
    ldr         r0, =CONFIG_UBOOT_LOADADDR
    ldr         r1, =0x400
    bl          drvNAND_LoaduBoot

    @// LOAD UBOOT
    ldr         r0, =CONFIG_UBOOT_LOADADDR
    ldr         r3, [r0, #0]    @// UBOOT_ROM_START in MBOOT PARTITION
    ldr         r1, [r0, #4]    @// UBOOT_RAM_START
    ldr         r2, [r0, #8]    @// UBOOT_RAM_END
    sub         r1, r2, r1      @// UBOOT_SIZE = UBOOT_RAM_END - UBOOT_RAM_START
    add         r1, r1, r3      @// LOAD SIZE
    sub         r0, r0, r3
    bl          drvNAND_LoaduBoot

#elif defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    @//LOAD CHUNK HEADER
    ldr         r0, =CONFIG_UBOOT_LOADADDR
    ldr         r1, =0x400
    ldr         r2, =0x1000
    bl          eMMC_ReadData_MIU

    @// LOAD UBOOT
    ldr         r0, =CONFIG_UBOOT_LOADADDR
    ldr         r5, [r0, #4]    @// UBOOT_RAM_START
    ldr         r6, [r0, #8]    @// UBOOT_RAM_END
    sub         r1, r6 , r5
    ldr         r2, =0x1002
    bl          eMMC_ReadData_MIU

#else

    bl          DoMSDecompression

#endif

@//================================================================================================
BOOT_POINT:

    DPUTK       'U'

    WREG        0x1f006040, 0x0000          @//Disable Hardware Timer 1

#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) || \
    defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    ldr         pc, =CONFIG_UBOOT_LOADADDR
#else

#ifndef CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51
#ifdef CONFIG_MSTAR_PM_SWIR
    ldr         r0, =0x14030000
#else
    ldr         r0, =0x14020000
#endif
#else
    ldr         r0, =0x14030000
#endif

    ldr         pc, [r0, #16]
#endif

@//================================================================================================
    .globl      Bootram_SecondaryCore
Bootram_SecondaryCore:

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

    WREG        (MS_BUS_RIU_ADDR + (0x1033A2 << 1)), 0xff
    WREG        (CONFIG_KERNEL_START_ADDRESS + 0x8000), 0

Bootram_MpCoreLoop:

    wfi

    RREG        r1, (CONFIG_KERNEL_START_ADDRESS + 0x8000)
    ldr         r2, =0xbabe             @//check magic number
    cmp         r1, r2
    bne         Bootram_MpCoreLoop

    RREG        pc, (CONFIG_KERNEL_START_ADDRESS + 0x8004)

Bootram_SecondaryCoreExit:
    b           Bootram_SecondaryCoreExit

@//-------------------------------------------------------------------------------------------------
@// BOOTRAM_Pad
@// @param  None
@// @return None
@// @note   Pad with zeros (Reserve SIZE_BOOTRAM_RESERVED Bytes for bootram)
@//-------------------------------------------------------------------------------------------------
    .org        (SIZE_BOOTRAM_RESERVED - 4)
    .word       0
