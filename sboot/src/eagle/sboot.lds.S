/*
 *#############################################################################
 *
 * Copyright (c) 2006-2012 MStar Semiconductor, Inc.
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
#if (CONFIG_EMMC_BOOT == 1)
    boot :  ORIGIN = 0x00000000,                LENGTH = 12K
#elif (CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH == 1)
    boot :  ORIGIN = 0x1fc00000,                LENGTH = 10K
    boot2 : ORIGIN = 0x1fc00000 + 4K,           LENGTH = 6K
    boot3 : ORIGIN = 0x1fc00000 + 4K,           LENGTH = 6K
    ram :   ORIGIN = CONFIG_BOOTRAM_LOADADDR,   LENGTH = 20K
#elif (CONFIG_BOOTING_FROM_EXT_EMMC_WITH_CPU == 1)
    boot :  ORIGIN = 0x00000000,                LENGTH = 12K
    rom :   ORIGIN = 0x00000000+0x3000,         LENGTH = 0K
    ram :   ORIGIN = 0x40200000,                LENGTH = 128K
#else
    boot :  ORIGIN = 0x00000000,                LENGTH = 8K
    rom :   ORIGIN = 0x00000000+0x2000,         LENGTH = 18K
    ram :   ORIGIN = CONFIG_BOOTRAM_LOADADDR,   LENGTH = 128K
#endif
}

SECTIONS
{
#if (CONFIG_EMMC_BOOT == 1)
     .text1 :
    {
        *boot.o          (.text*)
        . = ALIGN(16);
        _ld_bootrom_start = .;
        *drvRIU.o           (.text*)
        *bootrom.o          (.text*)
        *bootrom_pll.o      (.text*)
        *bootrom_clock.o    (.text*)
        *bootrom_peripheral.o   (.text*)
        *bootrom_cache.o    (.text*)
        *bootrom_miu.o      (.text*)
        *bootrom_miu_str.o  (.text*)
        *bootrom.o          (.rodata*)
        *bootrom_data_miu.o (.rodata*)
        *bootrom_data_str.o (.rodata*)
#if defined(CONFIG_MSTAR_ASIC_EMULATION_ENABLE)
        *drvPadConf_a3.o    (.rodata*)
#else
        *drvPadConf.o       (.rodata*)
#endif
        . = ALIGN(16);
        _ld_bootrom_end = .;
    } > boot
#elif (CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH == 1)
    .text1 :
    {
        *boot.o             (.text*)

        . = ALIGN(16);
        _ld_bootrom_start = .;

        *bootrom.o          (.text*)
        *bootrom_cache.o    (.text*)
        *drvRIU.o           (.text*)

        *drvNAND_prg.o      (.text*)
        *drvNAND_hal.o      (.text*)
        *drvNAND_platform.o (.text*)
        *drvNAND_prg.o      (.data*)
        *drvNAND_prg.o      (.bss*)
        *drvNAND_hal.o      (.bss*)
        *drvNAND_platform.o (.bss*)

        . = ALIGN(4096);

        _ld_program_reload_addr = .;
        *bootrom_pll.o      (.text*)
        *bootrom_clock.o    (.text*)
        *bootrom_peripheral.o   (.text*)
        *bootrom.o          (.rodata*)
        *drvPadConf.o       (.rodata*)

        . = ALIGN(16);
        _ld_bootrom_end = .;

    } > boot

    .text2 : AT (LOADADDR(.text1) + LENGTH(boot))
    {
        _ld_miu_flow_flash_start = LENGTH(boot) - _ld_program_reload_addr;
        _ld_miu_flow_flash_size = LENGTH(boot2) - _ld_program_reload_addr;
        _ld_miu_flow_start = .;

        *bootrom_miu.o         (.text*)
        *bootrom_data_miu.o    (.rodata*)

        . = ALIGN(1024);
        _ld_miu0_flow_end = .;

    } > boot2

    .text3 : AT (LOADADDR(.text2) + LENGTH(boot2))
    {
        _ld_miu_str_flow_flash_start = LENGTH(boot2) - _ld_program_reload_addr + _ld_miu_flow_flash_start;
        _ld_miu_str_flow_flash_size = LENGTH(boot3) - _ld_program_reload_addr;
        _ld_miu_str_flow_start = .;

        *bootrom_miu_str.o      (.text*)
        *bootrom_data_str.o     (.rodata*)

        . = ALIGN(1024);
        _ld_miu0_str_flow_end = .;

    } > boot3

    .text4 : AT (LOADADDR(.text1) + 0x8000)
    {
        _ld_bootram_start = .;
        *bootram.o          (.text*)
        *nandflash.o        (.text*)
        *nandflash.o        (.rodata*)
        *uart16550.o        (.text*)
        *setSPI.o           (.text*)
        *setSPI.o           (.rodata*)
        *apiBDMA.o          (.text*)
        *apiBDMA.o          (.rodata*)
        *apiBDMA.o          (.data*)
        *apiBDMA.o          (.bss*)

        *MSDecompress.o     (.text*)
        *MSDecompress.o     (.rodata*)
        *MSDecompress.o     (.data*)
        *MSDecompress.o     (.bss*)

        *(NANDCODE)

        _ld_bootram_end = .;

        . = ALIGN(16);
    } > ram

    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx*)
        _ld_bootram_end = .;
    } > ram
    __exidx_end = .;

    /* dummy */
    .data :
    {
        *(.data)
    } > ram

    .bss :
    {
        . = ALIGN(16);
        _ld_bootbss_start = .;
        *(.bss*)
        . = ALIGN(16);
        _ld_bootbss_end = .;
    } > ram


#elif (CONFIG_BOOTING_FROM_EXT_EMMC_WITH_CPU == 1)
     .text1 :
    {
        *boot.o          (.text*)
        . = ALIGN(16);
        _ld_bootrom_start = .;
        *drvRIU.o           (.text*)
        *bootrom.o          (.text*)
        *bootrom_pll.o      (.text*)
        *bootrom_clock.o    (.text*)
        *bootrom_cache.o    (.text*)
        *bootrom_peripheral.o   (.text*)
        *bootrom_miu.o      (.text*)
        *bootrom_miu_str.o  (.text*)
        *bootrom.o          (.rodata*)
        *bootrom_data_miu.o (.rodata*)
        *bootrom_data_str.o (.rodata*)
#if defined(CONFIG_MSTAR_ASIC_EMULATION_ENABLE)
        *drvPadConf_a3.o    (.rodata*)
#else
        *drvPadConf.o       (.rodata*)
#endif
        . = ALIGN(16);
        _ld_bootrom_end = .;
    } > boot

    .text2 : AT ( LOADADDR(.text1) + 0x3000 )
    {
        _ld_bootram_start = .;
        *nandflash.o        (.text*)
        *nandflash.o        (.rodata*)
        . = ALIGN(16);
        _ld_bootram_end = .;
    } > rom

    .text3 : AT (LOADADDR(.text1) + 0x3000)
    {
        _ld_bootram_RAM_start = .;
        *bootram.o          (.text*)
        *uart16550.o        (.text*)
        *MSDecompress.o     (.text*)
        *MSDecompress.o     (.rodata*)
        *MSDecompress.o  (.data*)
        *MSDecompress.o  (.bss*)
        *7alloc.o (.text*)
        *lzmadec.o (.text*)
        *zlib.o (.text*)
        *zlib.o (.rodata*)
        *zlib.o (.data*)
        *zlib.o (.bss*)
        *zlib.o (.scommon*)
        . = ALIGN(16);
        _ld_bootram_RAM_end = .;
    } > ram


    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx*)
        _ld_bootram_end = .;
    } > ram
    __exidx_end = .;

    /* dummy */
    .data :
    {
        *(.data)
    } > ram

    .bss :
    {
        . = ALIGN(16);
        _ld_bootbss_start = .;
        *(.bss*)
        . = ALIGN(16);
        _ld_bootbss_end = .;
    } > ram
#else
    .text1 :
    {
        *boot.o             (.text*)
        . = ALIGN(16);
    } > boot

    .text2 : AT ( LOADADDR(.text1) + 0x2000 )
    {
        _ld_bootrom_start = .;
        *drvRIU.o           (.text*)
        *bootrom.o          (.text*)
        *bootrom_pll.o      (.text*)
        *bootrom_clock.o    (.text*)
        *bootrom_peripheral.o   (.text*)
        *bootrom_cache.o    (.text*)
        *bootrom_miu.o      (.text*)
        *bootrom_miu_str.o  (.text*)
        *bootrom.o          (.rodata*)
        *bootrom_data_miu.o (.rodata*)
        *bootrom_data_str.o (.rodata*)
#if defined(CONFIG_MSTAR_ASIC_EMULATION_ENABLE)
        *drvPadConf_a3.o    (.rodata*)
#else
        *drvPadConf.o       (.rodata*)
#endif
        . = ALIGN(16);
        _ld_bootrom_end = .;
    } > rom

    .text3 : AT (LOADADDR(.text2) + SIZEOF(.text2))
    {
        _ld_bootram_start = .;
        *bootram.o          (.text*)
        *nandflash.o        (.text*)
        *nandflash.o        (.rodata*)
        *uart16550.o        (.text*)
        *setSPI.o           (.text*)
        *setSPI.o           (.rodata*)
        *apiBDMA.o          (.text*)
        *apiBDMA.o          (.rodata*)

        *MSDecompress.o     (.text*)
        *MSDecompress.o     (.rodata*)

/*      _ld_bootram_end = .; */

        . = ALIGN(16);
    } > ram

    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx*)
        _ld_bootram_end = .;
    } > ram
    __exidx_end = .;

    /* dummy */
    .data :
    {
        *(.data)
    } > ram

    .bss :
    {
        . = ALIGN(16);
        _ld_bootbss_start = .;
        *(.bss*)
        . = ALIGN(16);
        _ld_bootbss_end = .;
    } > ram

#endif

    /DISCARD/ :
    {
        /* ABI crap starts here */

        *(.reginfo)
    }

#if (CONFIG_EMMC_BOOT == 1)
    .padding : AT(LOADADDR(.text1) + 0x3000 - 4)
    {
        LONG(0x0)
    } > boot
#elif (CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH == 1)
    .padding : AT(LOADADDR(.text1) + 0x8000 - 4)
    {
        LONG(0x0)
    } > ram
#elif (CONFIG_BOOTING_FROM_EXT_EMMC_WITH_CPU == 1)
    .padding : AT(LOADADDR(.text1) + 0x8000 - 4)
    {
        LONG(0x0)
    } > ram
#else
    .padding : AT(LOADADDR(.text1) + 0x10000 - 4)
    {
        LONG(0x0)
    } > ram
#endif
}
