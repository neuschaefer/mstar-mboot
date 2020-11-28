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

#define RIUBASE_PM              0xBF000000
#define RIUBASE_NONPM           0xBF200000
#define RIUBASE_NONPM_EXT12     0xBF240000  #//Support Bank 0x12XX

    .text
    .set        noreorder

#-------------------------------------------------------------------------------------------------
# BOOTRAM_Entry:
# @param  None
# @return None
# @note   Entry point of BootRam code
#-------------------------------------------------------------------------------------------------
    .globl      BOOTRAM_ROM_Entry
BOOTRAM_ROM_Entry:

    DBGREG       0x1000

    # Copy data section from sram to dram
    bal          BOOTRAM_CopyData
    nop

	DBGREG       0x0005

    # Clear bss section
    bal          BOOTRAM_InitBss
    nop

#ifdef CONFIG_MSTAR_EDINBURGH
    #//Init Edinburgh
    bal         BOOT_InitEdinburgh
    nop
#endif

    #//Trim Emac Ephy from efuse
    bal         BootRomTrimEmacEphy
    nop

    #//Load chunker header
    la           a3, drvNAND_LoaduBoot
#ifdef CONFIG_ENABLE_BOOTING_FROM_ROM_WITH_COMPRESS_UBOOT
    #//Put the compressed uboot at CONFIG_UBOOT_LOADADDR-0x2000000 location.
    la           a0, CONFIG_UBOOT_LOADADDR
    sub          a0, a0, 0x2000000
#else
    la           a0, CONFIG_UBOOT_LOADADDR
#endif
    la           a1, 0x400
    jal          a3
    nop

    #//Load Uboot
#ifdef CONFIG_ENABLE_BOOTING_FROM_ROM_WITH_COMPRESS_UBOOT
    la           a0,CONFIG_UBOOT_LOADADDR
    sub          a0,a0,0x2000000
#else
    la           a0, CONFIG_UBOOT_LOADADDR
#endif
    lw           a1, (a0)               #// UBOOT_ROM_START in MBOOT PARTITION
    lw           a2, 4(a0)              #// UBOOT_RAM_START
    lw           a3, 8(a0)              #// UBOOT_RAM_END
    sub          t0, a3, a2             #// UBOOT_RAM_END - UBOOT_RAM_START

    la           a3, drvNAND_LoaduBoot
#ifdef CONFIG_ENABLE_BOOTING_FROM_ROM_WITH_COMPRESS_UBOOT
    #// a0 is target address, a1 is load size.
    la           a0, CONFIG_UBOOT_LOADADDR
    sub          a0, a0, 0x2000000

    lw           a1, (a0)               #// UBOOT_ROM_START
    lw           a2, 12(a0)             #// UBOOT_ROM_END
    sub          a1, a2, a1             #// UBOOT_ROM_END - UBOOT_ROM_START
    add          a1, a1, 0x400
#else
    sub          a0, a2, a1
    add          a1, t0, a1
#endif

    jal          a3
    nop
#ifdef CONFIG_ENABLE_BOOTING_FROM_ROM_WITH_COMPRESS_UBOOT
    jal          DoMSDecompression
    nop
#endif

    #PUTC         'U'

    #//Jump to The Entry Point of UBoot
#ifdef CONFIG_ENABLE_BOOTING_FROM_ROM_WITH_COMPRESS_UBOOT
    la           a0, CONFIG_UBOOT_LOADADDR
    sub          a0, a0, 0x2000000
#else
    la           a0, CONFIG_UBOOT_LOADADDR - 0x400 #// Chunker header
#endif
    lw           a1, 16(a0)                        #// UBOOT_RAM_ENTRY

	jr           a1
    nop

BOOTRAM_CopyUboot:
#//-------------------------------------------------------------------------------------------------
#// Copy Data Section to DRAM
#//-------------------------------------------------------------------------------------------------
    la	        t3, 0xa75f0180
    la	        t4, 0x875f0180
    la	        t5, 0x200000

_CopyData:
    lw          t6, 0(t3)
    sw          t6, 0(t4)

    add         t3, t3, 4
    add         t4, t4, 4
    add         t5, t5, -4

    bnez        t5, _CopyData
    nop

    jr          ra
    nop
#-------------------------------------------------------------------------------------------------
# BOOTRAM_CopyData
# @param  None
# @return None
# @note   Power On Sequence for Chip
#-------------------------------------------------------------------------------------------------
BOOTRAM_CopyData:
#//-------------------------------------------------------------------------------------------------
#// Copy Data Section to DRAM
#//-------------------------------------------------------------------------------------------------
    la	        t3, _end_address_text_section
    la	        t4, _start_address_data_section
    la	        t5, _size_data_section
    beqz        t5, _CopyDataToSramEnd

_CopyDataToSram:
    lw          t6, 0(t3)
    sw          t6, 0(t4)

    add         t3, t3, 4
    add         t4, t4, 4
    add         t5, t5, -4

    bnez        t5, _CopyDataToSram
    nop

_CopyDataToSramEnd:
    jr          ra
    nop

#-------------------------------------------------------------------------------------------------
# BOOTRAM_InitBss
# @param  None
# @return None
# @note   Power On Sequence for Chip
#-------------------------------------------------------------------------------------------------
BOOTRAM_InitBss:
#//-------------------------------------------------------------------------------------------------
#// Clear BSS Section in DRAM
#//-------------------------------------------------------------------------------------------------
    la	        t3, _start_address_bss_section
    la	        t4, _size_bss_section
    li	        t5, 0
    beqz        t4, _InitBssLoopEnd

_InitBssLoop:
    sw          t5, 0(t3)

    add         t3, t3, 4
    add         t4, t4, -4

    bnez        t5, _InitBssLoop
    nop

_InitBssLoopEnd:
    jr          ra
    nop

#-------------------------------------------------------------------------------------------------
# BOOT_InitEdinburgh  Init Demod Edinburgh
# @param  None
# @return None
# @note   do enable Xtal for Edinburgh
#-------------------------------------------------------------------------------------------------
BOOT_InitEdinburgh:

    RREG        t9, 0xBF001C24
    and         t9, t9, 0xfbff
    REG_C2M     t9, 0xBF001C24

    WREG        0xBF203C70, 0x0000

    RREG        t9, 0xBF224004
    and         t9, t9, 0xdfff
    REG_C2M     t9, 0xBF224004

    RREG        t9, 0xBF2250F0
    and         t9, t9, 0xefff
    REG_C2M     t9, 0xBF2250F0

    RREG        t9, 0xBF2250D4
    and         t9, t9, 0xbfff
    REG_C2M     t9, 0xBF2250D4

    RREG        t9, 0xBF2250F4
    or          t9, t9, 0x0001
    REG_C2M     t9, 0xBF2250F4

    RREG        t9, 0xBF22501C
    or          t9, t9, 0x0010
    REG_C2M     t9, 0xBF22501C

    jr          ra
    nop

#-------------------------------------------------------------------------------------------------
# BOOTRAM_Pad
# @param  None
# @return None
# @note   Pad with zeros (Reserve SIZE_BOOTRAM_RESERVED Bytes for bootram)
#-------------------------------------------------------------------------------------------------
    .org        (SIZE_BOOTRAM_RESERVED-4)
    .word       0

#-------------------------------------------------------------------------------------------------
# BootRomTrimEmacEphy
# @param  None
# @return None
# @note   Trim Emac Ephy from efuse
#-------------------------------------------------------------------------------------------------
LEAF(BootRomTrimEmacEphy)


    RREG        k0, 0xBF004038        #//Get efuse data from bank 0x4d[13:0]
    srl         k0, k0, 14
    andi        k0, k0, 0x0003
    RREG        t9, 0xBF00403C
    andi        t9, t9, 0x0FFF
    sll         t9, t9, 2
    or          t9, t9, k0


    RREG        k1, 0xBF00403C        #//Get efuse data from bank 0x4d[17:14]
    andi        k1, k1, 0xF000
    srl         k1, k1, 4


    RREG        k0, 0xBF2434C0        #//0x121a60[11:8] + 0x121a60[2] = 1
    andi        k0, k0, 0xf0ff
    or          k0, k0, k1
    ori         k0, k0, 0x0004
    REG_C2M     k0, 0xBF2434C0

    RREG        k0, 0xBF2434D0        #//0x121a68[13:0] + 0x121a68[15] = 1
    andi        k0, k0, 0xc000
    or          k0, k0, t9
    ori         k0, k0, 0x8000
    REG_C2M     k0, 0xBF2434D0

    jr          ra
    nop

END(BootRomTrimEmacEphy)