################################################################################
#
# Copyright (c) 2006-2011 MStar Semiconductor, Inc.
# All rights reserved.
#
# Unless otherwise stipulated in writing, any and all information contained
# herein regardless in any format shall remain the sole proprietary of
# MStar Semiconductor Inc. and be kept in strict confidence
# (¡§MStar Confidential Information¡¨) by the recipient.
# Any unauthorized act including without limitation unauthorized disclosure,
# copying, use, reproduction, sale, distribution, modification, disassembling,
# reverse engineering and compiling of the contents of MStar Confidential
# Information is unlawful and strictly prohibited. MStar hereby reserves the
# rights to any and all damages, losses, costs and expenses resulting therefrom.
#
################################################################################

#ifndef _BOOT_INC_
#include "boot.inc"
#endif

#ifndef _ArchDefs_h_
#include "ArchDefs.h"
#endif

    .text
    .set        noreorder

#-------------------------------------------------------------------------------------------------
# BOOTRAM_Entry:
# @param  None
# @return None
# @note   Entry point of BootRam code
#-------------------------------------------------------------------------------------------------
    .globl      BOOTRAM_Entry
BOOTRAM_Entry:

    PUTC        '_'

#//================================================================================================
#// Clear data in BSS section

    la          t0, _ld_bootbss_start
    la          t1, _ld_bootbss_end

    sub         t0, 4
1:
    addi        t0, 4
    
    sw          zero, 0(t0)
    
    bltl        t0, t1, 1b
    nop

#//================================================================================================
#// Initialize system stack pointer for unzip subroutine

    li          sp, ADDR_STACK_POINTER

#ifndef CONFIG_MSTAR_TITANIA_BD_FPGA
#ifndef CONFIG_EMMC_BOOT
#//================================================================================================
    jal         DoMSDecompression
    nop

	jal		    BootRamFlushMemory
	nop

#//================================================================================================
#endif

BOOT_POINT:

    PUTC        'U'

#if defined(CONFIG_PM_SIZE_KB_FORCED) && (CONFIG_PM_SIZE_KB_FORCED!=0)
    li          t0, (0xbfc10000+(CONFIG_PM_SIZE_KB_FORCED)*0x400)
#else
    li          t0, 0xbfc20000
#endif
    lw          t1, 0x10(t0)
    nop

    jr          t1          #//Jump to The Entry Point of UBoot
    nop

#//================================================================================================
    .org        BOOT_POINT + 0x0100
    .align      4
BootRamFlushMemory:

	li		    t0, 0xa3f00000
	sw		    t0, 0(t0)
	sw		    t0, 32(t0)
	sw		    t0, 64(t0)
	sw		    t0, 96(t0)
	sw		    t0, 128(t0)

	jr		    ra
	nop

#else

#//================================================================================================
#//Copy Image to DRAM
    la          t3, FPGA_LINUX_KERNEL_FLASH_ADDRESS     #//Starting Address of Linux Kernel in SPI Flash
    la          t4, FPGA_LINUX_KERNEL_DRAM_ADDRESS      #//Dest Address of Linux Kernel in DRAM
    li          t5, FPGA_LINUX_KERNEL_SIZE              #//Image Size of Linux Kernel
    
_CopyImageLoop:

    lw          t6, 0(t3)
    sw          t6, 0(t4)

    add         t3, t3, 4
    add         t4, t4, 4
    add         t5, t5, -4

    and         t7, t5, 0x0007FFFF
    bnez        t7, _CopyImageLoop
    nop
    
    li          t7, '#' 
    sw          t7, (0xBF000000 + (0x100980 << 1))

    bnez        t5, _CopyImageLoop
    nop

#//================================================================================================
#//Jump to Kernel Entry of Linux
   
    la          t1, FPGA_LINUX_KERNEL_ENTRY    
    jr          t1
    nop

#endif

#-------------------------------------------------------------------------------------------------
# BOOTRAM_ExceptionHandler
# @param  None
# @return None
# @note   Exception handler for general exception or decompression failure at bootram code
#-------------------------------------------------------------------------------------------------
BOOTRAM_ExceptionHandler:

    la      ra, BOOT_ExceptionHandler
    j       ra
    nop

#-------------------------------------------------------------------------------------------------
# BOOTRAM_Pad
# @param  None
# @return None
# @note   Pad with zeros (Reserve SIZE_BOOTRAM_RESERVED Bytes for bootram)
#-------------------------------------------------------------------------------------------------
    .org        (SIZE_BOOTRAM_RESERVED-4)
    .word       0
