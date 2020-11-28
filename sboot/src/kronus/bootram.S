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
    .text
    .set    noreorder


#-------------------------------------------------------------------------------------------------
# BOOTRAM_Entry:
# @param  None
# @return None
# @note   Entry point of BootRam code
#-------------------------------------------------------------------------------------------------
    .globl  BOOTRAM_Entry
BOOTRAM_Entry:

#   DBGREG  0x0020
    PUTC '_'

    #clear bss
    la      $8, _ld_bootbss_start
    la      $9, _ld_bootbss_end

    sub     $8, 4
1:
    addi    $8, 4
    bltl    $8, $9, 1b
    sw      $0, 0($8)

    # Initialize system stack pointer for unzip subroutine
    li      $sp, ADDR_STACK_POINTER

    PUTC 's'

    #la      $31,    NandFlash_Init
    #jalr    $31
    #nop

    PUTC 'n'

    la	     $31,    PM_MCU_Init
    jal      $31
    nop

    PUTC 'P'

    la	     $31,    DoMSDecompression
    jal      $31
    nop

	la		$15, MEMORY_FLUSH
	jal		$15
    nop

BOOT_POINT:

    PUTC 'D'

    # Copy binary from ROM to RAM
    # bal     BOOTRAM_CopyBinary
    # nop

    # PUTC 'U'

    # UBoot binary entry
    #li      $7, ADDR_UBOOT_RAM_ENTRY_CACHE  #unzip subroutine
    li      $15, 0xbfc20000
    lw      $7, 16($15)
    j       $7
    nop

    PUTC 'b'


#   DBGREG  0x0021
    PUTC 'k'

.if (BOOT_DEBUG_VERSION)
    # Record unzip or DMA count
    li      $9, 0xA0000000
    sw      $2, 0($9)

    # Record boot time
    mfc0    $8, $9
    li      $9, (CPU_CLOCK_FREQ/2/1000)
    divu    $10, $8, $9 #ms
    li      $9, 0xA0000004
    sw      $10, 0($9)
.endif

#   DBGREG  0x0022


.if (0)
#-------------------------------------------------------------------------------------------------
# BOOTRAM_CopyBinary
# @param  None
# @return None
# @note   Copy binary from ROM to RAM, could be uboot or ap, depends on what it is in ROM
#-------------------------------------------------------------------------------------------------
BOOTRAM_CopyBinary:

# Load ROM_START, RAM_START, RAM_END, ROM_END from 0xBFC20000
    li      $15, 0xbfc20000
    lw      $8,  0($15)     # ROM_START
    lw      $9,  4($15)     # RAM_START
    lw      $10, 8($15)     # RAM_END
    lw      $11, 12($15)    # ROM_END

# copy uboot or ap to ram
1:
    ld      $12, 0($8)      #ld=lw lw to save time
    ld      $14, 8($8)
    sd      $12, 0($9)
    sd      $14, 8($9)
    addu    $8, $8, 16
    addu    $9, $9, 16
    bltu    $9, $10, 1b
    nop

    jr      $31

    nop
.endif

.org BOOT_POINT+0x100
.align 4
MEMORY_FLUSH:

	li		$8, 0xA3F00000
	sw		$8, 0($8)
	sw		$8, 32($8)
	sw		$8, 64($8)
	sw		$8, 96($8)
	sw		$8, 128($8)

	j		$31
	nop

#-------------------------------------------------------------------------------------------------
# BOOTRAM_ExceptionHandler
# @param  None
# @return None
# @note   Exception handler for general exception or decompression failure at bootram code
#-------------------------------------------------------------------------------------------------
BOOTRAM_ExceptionHandler:

    la      $31,    BOOT_ExceptionHandler
    j       $31
    nop



#-------------------------------------------------------------------------------------------------
# BOOTRAM_Pad
# @param  None
# @return None
# @note   Pad with zeros (Reserve SIZE_BOOTRAM_RESERVED Bytes for bootram)
#-------------------------------------------------------------------------------------------------
    .org    (SIZE_BOOTRAM_RESERVED-4)
    .word   0
