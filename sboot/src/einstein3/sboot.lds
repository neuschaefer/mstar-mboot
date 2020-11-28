/*
 * Automatically generated C config: don't edit
 * SBoot version: 1.0.0
 */







/*
 * Platform Configuration
 */
/*
 * Extended CPU Configuration
 */
/*
 * General Configuration
 */
/*
 * Mmap Configuartion
 */
/*
 * Build Options
 */
/*
 * Debugging Options
 */
/*
 * Installation Options
 */
/*
 * Module Options
 */
/*
 * External Demodulator
 */
/*
 * Env config
 */
/*
 *#############################################################################
 *
 * Copyright (c) 2006-2013 MStar Semiconductor, Inc.
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
OUTPUT_ARCH(arm)
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
ENTRY(_vector)
MEMORY
{
    boot : ORIGIN = 0x00000000, LENGTH = 8K
    rom : ORIGIN = 0x00000000+0x2000, LENGTH = 18K
    ram : ORIGIN = 0x20000000, LENGTH = 128K
}
SECTIONS
{
    .text1 :
    {
        _ld_boot_start = ABSOLUTE(.);
        *boot.o (.text*)
        . = ALIGN(16);
        _ld_boot_end = ABSOLUTE(.);
        _ld_boot_size = _ld_boot_end - _ld_boot_start;
    } > boot
    .text2 : AT ( LOADADDR(.text1) + 0x2000 )
    {
        _ld_bootrom_start = ABSOLUTE(.);
        *drvRIU.o (.text*)
        *bootrom.o (.text*)
        *bootrom_pll.o (.text*)
        *bootrom_clock.o (.text*)
        *bootrom_peripheral.o (.text*)
        *bootrom_cache.o (.text*)
        *bootrom_miu.o (.text*)
        *bootrom_miu_str.o (.text*)
        *bootrom_miu_txdqs.o (.text*)
        *bootrom.o (.rodata*)
        *bootrom_data_miu.o (.rodata*)
        *bootrom_data_str.o (.rodata*)
        *drvPadConf.o (.rodata*)
        . = ALIGN(16);
        _ld_bootrom_end = ABSOLUTE(.);
        _ld_bootrom_size = _ld_bootrom_end - _ld_bootrom_start;
    } > rom
    .text3 : AT (LOADADDR(.text2) + SIZEOF(.text2))
    {
        _ld_bootram_start = ABSOLUTE(.);
        *bootram.o (.text*)
        *nandflash.o (.text*)
        *nandflash.o (.rodata*)
        *uart16550.o (.text*)
        *setSPI.o (.text*)
        *setSPI.o (.rodata*)
        *apiBDMA.o (.text*)
        *apiBDMA.o (.rodata*)
        *MSDecompress.o (.text*)
        *MSDecompress.o (.rodata*)
        *(.ARM.exidx*)
    } > ram
    .data :
    {
        . = ALIGN(16);
        _ld_bootdata_start = ABSOLUTE(.);
        *(.data*)
        . = ALIGN(16);
        _ld_bootdata_end = ABSOLUTE(.);
        _ld_bootram_end = ABSOLUTE(.);
        _ld_bootram_size = _ld_bootram_end - _ld_bootram_start;
    } > ram
    .bss :
    {
        . = ALIGN(16);
        _ld_bootbss_start = ABSOLUTE(.);
        *(.bss*)
        . = ALIGN(16);
        _ld_bootbss_end = ABSOLUTE(.);
    } > ram
    /DISCARD/ :
    {
        /* ABI crap starts here */
        *(.reginfo)
    }
    .padding : AT(LOADADDR(.text1) + 0x10000 - 4)
    {
        LONG(0x0)
    } > ram
}
