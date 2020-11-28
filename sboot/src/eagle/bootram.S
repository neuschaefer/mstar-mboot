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

#if defined(CONFIG_SBOOT_TO_KERNEL) || defined(CONFIG_MSTAR_TITANIA_BD_FPGA)
#define LINUX_KERNEL_FLASH_ADDRESS  0x14010000
#define LINUX_KERNEL_DRAM_ADDRESS   0x40408000
#define LINUX_KERNEL_ENTRY          0x40408000
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

    PUTK        '_'

@//================================================================================================
@// Clear data in BSS section

    ldr         r0, =_ld_bootbss_start
    ldr         r1, =_ld_bootbss_end
    mov         r2, #0

_ClearBssLoop:
    cmp         r0, r1
    str         r2, [r0], #0x04
    bne         _ClearBssLoop

@//================================================================================================
@// Initialize system stack pointer for unzip subroutine

    ldr         r13, =ADDR_STACK_POINTER

#if defined(CONFIG_SBOOT_TO_KERNEL) || defined(CONFIG_MSTAR_TITANIA_BD_FPGA)
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

#else
    
    #ifndef CONFIG_MSTAR_TOOL_ROM_PROGRAM_NAND_BIN		//Programming NAND for ROM Boot
    bl          DoMSDecompression
    #else

	ldr			r0, =CONFIG_UBOOT_LOADADDR
	ldr			r11, = (0x40000000 + 0x20000 + 0x400)				@// UBOOT_START ADDRESS in DRAM
	ldr			r1, =0x100000	

_CopyUbootImgLoop:
	ldr 		r3, [r11], #4
	str			r3, [r0],  #4
	subs		r1, r1, #4
	bne			_CopyUbootImgLoop
    

	ldr         pc, =CONFIG_UBOOT_LOADADDR

	#endif
#endif

@//================================================================================================
BOOT_POINT:

    PUTK        'U'

    WREG        0x1f006040, 0x0000          @//Disable Hardware Timer 1

#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) || \
    defined(CONFIG_BOOTING_FROM_EXT_EMMC_WITH_CPU)
    ldr         pc, =CONFIG_UBOOT_LOADADDR
#else

#ifndef CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51
#ifdef CONFIG_MSTAR_RT_PM_IN_SPI
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
#ifdef CONFIG_MSTAR_ASIC_EMULATION_ENABLE
    .globl      Bootram_SecondaryCore
Bootram_SecondaryCore:

    wfi

    RREG        r0, (MS_BUS_RIU_ADDR + (0x1033A2 << 1))
    and         r0, #0x03
    cmp         r0, #0
    bne         Bootram_SecondaryCore       @//make sure start address of secondary is legal

    RREG        r0, (MS_BUS_RIU_ADDR + (0x1033A0 << 1))
    RREG        r1, (MS_BUS_RIU_ADDR + (0x1033A2 << 1))
    add         r2, r1, r0, lsl #16
    mov         pc, r2

Bootram_SecondaryCoreLoop:
    ldr         pc, =Bootram_SecondaryCoreLoop
#endif


@//-------------------------------------------------------------------------------------------------
@// BOOTRAM_Pad
@// @param  None
@// @return None
@// @note   Pad with zeros (Reserve SIZE_BOOTRAM_RESERVED Bytes for bootram)
@//-------------------------------------------------------------------------------------------------
    .org        (SIZE_BOOTRAM_RESERVED - 4)
    .word       0
