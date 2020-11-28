OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_vector)

MEMORY
{
#if (CONFIG_EMMC_BOOT == 1)
    boot :  ORIGIN = 0x00000000,                LENGTH = 12K
#elif (CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH == 1)
    boot :  ORIGIN = 0x1fc00000,                LENGTH = 10K
    boot2 :  ORIGIN = 0x1fc00000 + 5K,          LENGTH = 5K
    boot3 :  ORIGIN = 0x1fc00000 + 5K,          LENGTH = 5K
    ram :   ORIGIN = CONFIG_BOOTRAM_LOADADDR,   LENGTH = 8K
#else
    boot :  ORIGIN = 0x00000000,                LENGTH = 8K
    rom :   ORIGIN = 0x00000000+0x2000,         LENGTH = 25K
    ram :   ORIGIN = CONFIG_BOOTRAM_LOADADDR,   LENGTH = 128K
#endif
}

SECTIONS
{
#if (CONFIG_EMMC_BOOT == 1)
     .text1 :
    {
        _ld_MEMORY_boot_start = .;
        *boot.o          (.text*)
        _ld_MEMORY_boot_end = .;
        _ld_MEMORY_rom_start = .;
        *drvRIU.o        (.text*)
        *bootrom.o       (.text*)
        *bootrom.o       (.rodata*)
        *drvPadConf.o    (.rodata*)
        *drv_miu_init.o  (.rodata*)
        . = ALIGN(16);
        _ld_MEMORY_rom_end = .;
        _ld_bootram_ROM_start = .;
    } > boot

#elif (CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH == 1)
    .text1 :
    {
        *boot.o             (.text*)

        . = ALIGN(16);
        _ld_bootrom_start = ABSOLUTE(.);

        *bootrom_rom.o      (.text*)
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
        *bootrom_rom.o      (.rodata*)
        *drvPadConf.o       (.rodata*)

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
        *drv_miu_init.o  	   (.rodata*)

        . = LENGTH(boot2) - 512;
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
        *drv_miu_init_str.o  	(.rodata*)

        . = LENGTH(boot3) - 512;
        . = LENGTH(boot3);
        _ld_miu_str_flow_end = ABSOLUTE(.);
        _ld_miu_str_flow_size = _ld_miu_str_flow_end - _ld_miu_str_flow_start;

    } > boot3

    .text4 : AT (LOADADDR(.text1) + 0x8000)
    {
        _ld_bootram_start = .;
        *bootram.o          (.text*)
        *drvRIU_ram.o       (.text*)
        *drv_miu1_init.o  	(.rodata*)
        *nandflash.o        (.text*)
        *nandflash.o        (.rodata*)
        *uart16550.o        (.text*)
        *drv_L1cache.o     (.text*)
        *drv_L1cache.o     (.rodata*)
        *setSPI.o           (.text*)
        *setSPI.o           (.rodata*)
        *apiBDMA.o          (.text*)
        *apiBDMA.o          (.rodata*)
        *MSDecompress.o     (.text*)
        *MSDecompress.o     (.rodata*)
/*		*eMMC_prg.o        (.text*)*/
/*		*eMMC_hal.o        (.text*)*/
/*		*eMMC_platform.o   (.text*)*/
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
        _ld_MEMORY_boot_start = .;
        *boot.o          (.text*)
        _ld_MEMORY_boot_end = .;
    } > boot

    .text2 : AT ( LOADADDR(.text1) + 0x2000 )
    {
        _ld_MEMORY_rom_start = .;
        *drvRIU.o        (.text*)
        *bootrom.o       (.text*)
        *bootrom.o       (.rodata*)
        *drvPadConf.o    (.rodata*)
        *drv_miu_init.o  (.rodata*)
        *drv_miu_init_str.o  (.rodata*)
        . = ALIGN(16);
        _ld_MEMORY_rom_end = .;
        _ld_bootram_ROM_start = .;
    } > rom

    .text3 : AT ( LOADADDR(.text2) + SIZEOF(.text2) )
    {
        _ld_MEMORY_ram_start = .;
        _ld_bootram_RAM_start = .;
        *bootram.o       (.text*)
        *nandflash.o     (.text*)
        *nandflash.o     (.rodata*)
        *uart16550.o     (.text*)
        *drv_L1cache.o     (.text*)
        *drv_L1cache.o     (.rodata*)
        *setSPI.o     (.text*)
        *setSPI.o     (.rodata*)
        *MSDecompress.o  (.text*)
        *apiBDMA.o  (.text*)
        *apiBDMA.o     (.rodata*)
        /*
        *apiSECURE.o  	 (.ARM*)
        *apiRSA.o  		 (.ARM*)
        *apiSHA.o  		 (.ARM*)
        *7alloc.o        (.ARM*)
        *lzmadec.o       (.ARM*)
        *zlib.o          (.ARM*)
        */
        . = ALIGN(16);
    } > ram

    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx*)
        _ld_MEMORY_ram_end = .;
        _ld_bootram_RAM_end = .;
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
#endif
    /DISCARD/ : {


	/* ABI crap starts here */

	*(.reginfo)
    }

#if (CONFIG_EMMC_BOOT == 0)
    .padding : AT(LOADADDR(.text1) + 0x10000 - 4)
#else
    .padding : AT(LOADADDR(.text1) + 0x3000 - 4)
#endif
    {
        LONG(0x0)
    } > ram
}
