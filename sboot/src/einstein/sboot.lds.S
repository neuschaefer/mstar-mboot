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
#if (CONFIG_EMMC_BOOT == 1)
    boot :  ORIGIN = 0x00000000,                LENGTH = 12K
#elif (CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH == 1)
    boot :  ORIGIN = 0x1fc00000,                LENGTH = 10K
    boot2 : ORIGIN = 0x1fc00000 + 5K,           LENGTH = 5K
    boot3 : ORIGIN = 0x1fc00000 + 5K,           LENGTH = 5K
    ram :   ORIGIN = CONFIG_BOOTRAM_LOADADDR,   LENGTH = 9K
#elif (CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH == 1)
    boot :  ORIGIN = 0x1fc00000,                LENGTH = 10K
    boot2 : ORIGIN = 0x1fc00000 + 5K,           LENGTH = 5K
    boot3 : ORIGIN = 0x1fc00000 + 5K,           LENGTH = 5K
    ram :   ORIGIN = CONFIG_BOOTRAM_LOADADDR,   LENGTH = 9K
#elif (CONFIG_BOOTING_FROM_EXT_EMMC_WITH_CPU == 1)
    boot :  ORIGIN = 0x00000000,                LENGTH = 12K
    rom :   ORIGIN = 0x00000000+0x3000,         LENGTH = 0K
    ram :   ORIGIN = 0x20400000,                LENGTH = 128K
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
        _ld_boot_start = ABSOLUTE(.);
        *boot.o             (.text*)
        . = ALIGN(16);
        _ld_boot_end = ABSOLUTE(.);
        _ld_boot_size = _ld_boot_end - _ld_boot_start;

        _ld_bootrom_start = ABSOLUTE(.);
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
        *drvPadConf.o       (.rodata*)

        . = ALIGN(16);
        _ld_bootrom_end = ABSOLUTE(.);
        _ld_bootrom_size = _ld_bootrom_end - _ld_bootrom_start;

    } > boot

#elif (CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH == 1)
    .text1 :
    {
        _ld_boot_start = ABSOLUTE(.);
        *boot.o             (.text*)

        . = ALIGN(16);
        _ld_boot_end = ABSOLUTE(.);
        _ld_boot_size = _ld_boot_end - _ld_boot_start;

        _ld_bootrom_start = ABSOLUTE(.);
        *bootrom.o          (.text*)
        *bootrom_cache.o    (.text*)
        *drvRIU.o           (.text*)
        *drvAESDMA.o        (.text*)
        *halAESDMA.o        (.text*)
        *drvNAND_prg.o      (.text*)
        *drvNAND_hal.o      (.text*)
        *drvNAND_platform.o (.text*)
        *drvNAND_prg.o      (.data*)
        *drvNAND_prg.o      (.bss*)
        *drvNAND_hal.o      (.bss*)
        *drvNAND_platform.o (.bss*)

        . = LENGTH(boot) - LENGTH(boot2);

        _ld_program_reload_addr = ABSOLUTE(.);
        *bootrom_pll.o      (.text*)
        *bootrom_clock.o    (.text*)
        *bootrom_peripheral.o   (.text*)
        *bootrom.o          (.rodata*)
        KEEP (*(SORT_BY_NAME(.rodata.padInitTbl_PreInit)))

        . = LENGTH(boot) - 1024;
        /* Reserved for Secure Booting */
        . = LENGTH(boot);
        _ld_bootrom_end = ABSOLUTE(.);
        _ld_bootrom_size = _ld_bootrom_end - _ld_bootrom_start;

    } > boot

    .text2 : AT (LOADADDR(.text1) + LENGTH(boot))
    {
        _ld_miu_flow_flash_start = LENGTH(boot) - _ld_program_reload_addr;
        _ld_miu_flow_flash_size = LENGTH(boot2) - _ld_program_reload_addr;
        _ld_miu_flow_start = ABSOLUTE(.);

        *bootrom_miu.o         (.text*)
        *bootrom_data_miu.o    (.rodata*)

        . = LENGTH(boot2) - 1024;
        /* Reserved for Secure Booting */
        . = LENGTH(boot2);
        _ld_miu_flow_end = ABSOLUTE(.);
        _ld_miu_flow_size = _ld_miu_flow_end - _ld_miu_flow_start;

    } > boot2

    .text3 : AT (LOADADDR(.text2) + LENGTH(boot2))
    {
        _ld_miu_str_flow_flash_start = LENGTH(boot2) - _ld_program_reload_addr + _ld_miu_flow_flash_start;
        _ld_miu_str_flow_flash_size = LENGTH(boot3) - _ld_program_reload_addr;
        _ld_miu_str_flow_start = ABSOLUTE(.);

        *bootrom_miu_str.o      (.text*)
        *bootrom_data_str.o     (.rodata*)

        . = LENGTH(boot3) - 1024;
        /* Reserved for Secure Booting */
        . = LENGTH(boot3);
        _ld_miu_str_flow_end = ABSOLUTE(.);
        _ld_miu_str_flow_size = _ld_miu_str_flow_end - _ld_miu_str_flow_start;

    } > boot3

    .text4 : AT (LOADADDR(.text1) + 0x8000)
    {
        _ld_bootram_start = ABSOLUTE(.);
        *bootram.o          (.text*)
        KEEP (*(SORT_BY_NAME(.rodata.padInitTbl)))
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

        *(.ARM.exidx*)

        . = ALIGN(16);
        _ld_bootdata_start = .;
        *(.data*)
        . = ALIGN(16);
        _ld_bootdata_end = .;

        _ld_bootbss_start = ABSOLUTE(.);
        *(.bss*)
        . = ALIGN(16);
        _ld_bootbss_end = ABSOLUTE(.);

        . = LENGTH(ram) - 1024;
        /* Reserved for Secure Booting */
        . = LENGTH(ram);
        _ld_bootram_end = ABSOLUTE(.);
        _ld_bootram_size = _ld_bootram_end - _ld_bootram_start;

    } > ram

#elif (CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH == 1)
    .text1 :
    {
        *boot.o             (.text*)

        . = ALIGN(16);
        _ld_bootrom_start = ABSOLUTE(.);

        *bootrom.o          (.text*)
        *bootrom_cache.o    (.text*)
        *drvRIU.o           (.text*)
        *drvAESDMA.o        (.text*)
        *halAESDMA.o        (.text*)
        *eMMC_prg.o         (.text*)
        *eMMC_hal.o         (.text*)
        *eMMC_platform.o    (.text*)
        *eMMC_prg.o         (.data*)
        *eMMC_hal.o         (.data*)
        *eMMC_platform.o    (.data*)
        *eMMC_prg.o         (.bss*)
        *eMMC_hal.o         (.bss*)
        *eMMC_platform.o    (.bss*)

        . = LENGTH(boot) - LENGTH(boot2);

        _ld_program_reload_addr = ABSOLUTE(.);
        *bootrom_pll.o      (.text*)
        *bootrom_clock.o    (.text*)
        *bootrom_peripheral.o   (.text*)
        *bootrom.o          (.rodata*)
        KEEP (*(SORT_BY_NAME(.rodata.padInitTbl_PreInit)))

        . = LENGTH(boot) - 1024;
        . = LENGTH(boot);
        _ld_bootrom_end = ABSOLUTE(.);
        _ld_bootrom_size = _ld_bootrom_end - _ld_bootrom_start;

    } > boot

    .text2 : AT (LOADADDR(.text1) + LENGTH(boot))
    {
        _ld_miu_flow_flash_start = LENGTH(boot) - _ld_program_reload_addr;
        _ld_miu_flow_flash_size = LENGTH(boot2) - _ld_program_reload_addr;
        _ld_miu_flow_start = ABSOLUTE(.);

        *bootrom_miu.o         (.text*)
        *bootrom_data_miu.o    (.rodata*)

        . = LENGTH(boot2) - 1024;
        . = LENGTH(boot2);
        _ld_miu_flow_end = ABSOLUTE(.);
        _ld_miu_flow_size = _ld_miu_flow_end - _ld_miu_flow_start;

    } > boot2

    .text3 : AT (LOADADDR(.text2) + LENGTH(boot2))
    {
        _ld_miu_str_flow_flash_start = LENGTH(boot2) - _ld_program_reload_addr + _ld_miu_flow_flash_start;
        _ld_miu_str_flow_flash_size = LENGTH(boot3) - _ld_program_reload_addr;
        _ld_miu_str_flow_start = ABSOLUTE(.);

        *bootrom_miu_str.o      (.text*)
        *bootrom_data_str.o     (.rodata*)

        . = LENGTH(boot3) - 1024;
        . = LENGTH(boot3);
        _ld_miu_str_flow_end = ABSOLUTE(.);
        _ld_miu_str_flow_size = _ld_miu_str_flow_end - _ld_miu_str_flow_start;

    } > boot3

    .text4 : AT (LOADADDR(.text1) + 0x8000)
    {
        _ld_bootram_start = .;
        *bootram.o          (.text*)
        KEEP (*(SORT_BY_NAME(.rodata.padInitTbl)))
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

        *(.ARM.exidx*)

        . = ALIGN(16);
        _ld_bootdata_start = .;
        *(.data*)
        . = ALIGN(16);
        _ld_bootdata_end = .;

        _ld_bootbss_start = ABSOLUTE(.);
        *(.bss*)
        . = ALIGN(16);
        _ld_bootbss_end = ABSOLUTE(.);

        . = LENGTH(ram) - 1024;
        /* Reserved for Secure Booting */
        . = LENGTH(ram);
        _ld_bootram_end = ABSOLUTE(.);
        _ld_bootram_size = _ld_bootram_end - _ld_bootram_start;

    } > ram

#elif (CONFIG_BOOTING_FROM_EXT_EMMC_WITH_CPU == 1)
     .text1 :
    {
        *boot.o             (.text*)
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
        *drvPadConf.o       (.rodata*)

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
        *MSDecompress.o     (.data*)
        *MSDecompress.o     (.bss*)
        *7alloc.o           (.text*)
        *lzmadec.o          (.text*)
        *zlib.o             (.text*)
        *zlib.o             (.rodata*)
        *zlib.o             (.data*)
        *zlib.o             (.bss*)
        *zlib.o             (.scommon*)

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
        *(.data*)
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
        _ld_boot_start = ABSOLUTE(.);
        *boot.o             (.text*)
        . = ALIGN(16);
        _ld_boot_end = ABSOLUTE(.);
        _ld_boot_size = _ld_boot_end - _ld_boot_start;

    } > boot

    .text2 : AT ( LOADADDR(.text1) + 0x2000 )
    {
        _ld_bootrom_start = ABSOLUTE(.);
        *drvRIU.o           (.text*)
        *bootrom.o          (.text*)
        *bootrom_pll.o      (.text*)
        *bootrom_clock.o    (.text*)
        *bootrom_peripheral.o   (.text*)
        *bootrom_cache.o    (.text*)
        *bootrom_miu.o      (.text*)
        *bootrom_miu_str.o  (.text*)
        *bootrom_miu_txdqs.o (.text*)
        *bootrom.o          (.rodata*)
        *bootrom_data_miu.o (.rodata*)
        *bootrom_data_str.o (.rodata*)
        KEEP (*(SORT_BY_NAME(.rodata.padInitTbl_PreInit)))
        
        . = ALIGN(16);
        _ld_bootrom_end = ABSOLUTE(.);
        _ld_bootrom_size = _ld_bootrom_end - _ld_bootrom_start;
    } > rom

    .text3 : AT (LOADADDR(.text2) + SIZEOF(.text2))
    {
        _ld_bootram_start = ABSOLUTE(.);
        *bootram.o          (.text*)
        KEEP (*(SORT_BY_NAME(.rodata.padInitTbl)))
        *nandflash.o        (.text*)
        *nandflash.o        (.rodata*)
        *uart16550.o        (.text*)
        *setSPI.o           (.text*)
        *setSPI.o           (.rodata*)
        *apiBDMA.o          (.text*)
        *apiBDMA.o          (.rodata*)

        *MSDecompress.o     (.text*)
        *MSDecompress.o     (.rodata*)

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
        /* LONG(0x0) */
    } > ram
#elif (CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH == 1)
    .padding : AT(LOADADDR(.text1) + 0x8000 - 4)
    {
        /* LONG(0x0) */
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
