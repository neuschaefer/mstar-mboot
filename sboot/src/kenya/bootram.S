################################################################################
#
# Copyright (c) 2006-2007 MStar Semiconductor, Inc.
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

#include "boot.inc"

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

#//================================================================================================
#// Copy Kernel Image and jump to kernel entry

.if (SBOOT_TO_KERNEL)
    PUTK        'K'
# Load ROM_START, RAM_START, RAM_END
    li      t0,  ADDR_BIN_ROM_START
    li      t1,  ADDR_BIN_RAM_START
    li      t2,  ADDR_BIN_RAM_END

# copy kernel to ram
2:
    ld      t4, 0(t0)      #ld=lw lw to save time
    ld      t6, 8(t0)
    sd      t4, 0(t1)
    sd      t6, 8(t1)
    addu    t0, t0, 16
    addu    t1, t1, 16
    bltu    t1, t2, 2b
    nop

	jal	    BootRamFlushMemory
	nop

    la      t5,KERNEL_ENTRY
    PUTK    'E'
    PUTK    '\n'
    j       t5
    nop
.endif
#//================================================================================================
    jal         DoMSDecompression
    nop

	jal		    BootRamFlushMemory
	nop

#//================================================================================================
BOOT_POINT:

    #PUTC        'U'

    li          t0, 0xbfc20000
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
