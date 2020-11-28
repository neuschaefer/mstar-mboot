OUTPUT(elf32-littlemips)
OUTPUT_ARCH(mips)

#if (CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH == 1)
ENTRY(BOOTROM_Entry)
#else
ENTRY(BOOT_Entry)
#endif

MEMORY
{
#if (CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH == 1)
	boot :  ORIGIN = 0xB2000000,                        LENGTH = 14K
	ram :   ORIGIN = CONFIG_BOOTRAM_LOADADDR,           LENGTH = 128K
#elif (CONFIG_MSTAR_TOOL_ROM_PROGRAM_NAND_BIN==1)
    boot :  ORIGIN = 0x80000000,                LENGTH = 3K
    rom :   ORIGIN = 0x80000000+0xC00,          LENGTH = 16K
    ram :   ORIGIN = CONFIG_BOOTRAM_LOADADDR,   LENGTH = 128K
    sram :  ORIGIN = 0x84000000,                LENGTH = 1K

#else
	boot :  ORIGIN = 0xBFC00000,                LENGTH = 3K
    /*rom :   ORIGIN = 0x94000000+0xC00,  LENGTH = 16K*/
    rom :   ORIGIN = 0xBFC00000+0xC00,          LENGTH = 16K
    ram :   ORIGIN = CONFIG_BOOTRAM_LOADADDR,   LENGTH = 128K
    sram :  ORIGIN = 0x84000000,                LENGTH = 1K
#endif

}

SECTIONS
{
#if (CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH == 1)

	_start_address_text_section = .;

     .text1 :
    {
        *bootrom_rom.o   (.text*)
        *bootrom_pll.o   (.text*)
        *bootrom_clock.o (.text*)
        *bootrom_cache.o (.text*)
        *bootrom_miu.o   (.text*)
        *bootrom_rom.o   (.rodata*)
        *bootrom_data.o  (.rodata*)
        *drvRIU.o        (.text*)
        *drvPadConf.o    (.rodata*)
        *boot.o          (.text*)
        *nandflash.o     (.text*)
        *uart16550.o     (.text*)
    #if (CONFIG_NAND_FLASH == 1)
        *drvNAND_prg.o      (.text*)
        *drvNAND_hal.o      (.text*)
        *drvNAND_platform.o (.text*)
    #else
        *drvSPINAND.o       (.text*)
        *drvSPINAND_boot.o  (.text*)
        *halSPINAND.o       (.text*)
        *halSPINAND.o       (.rodata*)
    #endif
        *setSPI.o     (.text*)
        *apiBDMA.o     (.text*)
        *MSDecompress.o  (.text*)
        *7alloc.o        (.text*)
        *lzmadec.o       (.text*)
        *zlib.o          (.text*)
        *cache.o         (.text*)
        *zlib.o          (.scommon*)
    } > boot

    .text2 : AT (LOADADDR(.text1) + 0x8000)
    {
        *bootram_rom.o   (.text*)
    } > ram

  	. = ALIGN(16);
  	_end_address_text_section = .;
	_size_text_section = _end_address_text_section - _start_address_text_section;

/*===============================================================================================*/
/* DATA Section																					 */
    . = CONFIG_BOOTRAM_LOADADDR;

    _start_address_data_section = .;

    .data(_start_address_data_section) : AT(_end_address_text_section)
    {
        *(.data*)
    } > ram

	. = ALIGN(4);
	_end_address_data_section = .;
	_size_data_section = _end_address_data_section - _start_address_data_section;

/*===============================================================================================*/
/* BSS Section																					 */
	_start_address_bss_section = .;

    .bss :
    {
        *(.bss)
    } > ram

	. = ALIGN(4);
	_end_address_bss_section = .;
	_size_bss_section = _end_address_bss_section - _start_address_bss_section;

    _stack_pointer = CONFIG_BOOTRAM_LOADADDR + 128K - 4;
#elif (CONFIG_MSTAR_TOOL_ROM_PROGRAM_NAND_BIN==1)
    .text1 :
    {
        *boot.o          (.text*)
    } > boot

    .text2 : AT ( LOADADDR(.text1) + SIZEOF(.text1) )
    {
        *drvRIU.o        (.text*)
        *bootrom_tool.o       (.text*)
        *bootrom_pll.o   (.text*)
        *bootrom_clock.o (.text*)
        *bootrom_cache.o (.text*)
        *bootrom_miu.o   (.text*)
        *bootrom_tool.o       (.rodata*)
        *bootrom_data.o  (.rodata*)
        *drvPadConf.o    (.rodata*)
        . = ALIGN(16);
        _ld_bootram_ROM_start = .;
    } > rom

    .text3 : AT ( LOADADDR(.text2) + SIZEOF(.text2) )
    {
        _ld_bootram_RAM_start = .;
        *bootram_tool.o       (.text*)
        *nandflash.o     (.text*)
        *nandflash.o     (.rodata*)
        *uart16550.o     (.text*)
        *setSPI.o     (.text*)
        *setSPI.o     (.rodata*)
        *apiBDMA.o     (.text*)
        *apiBDMA.o     (.rodata*)
        /* *lzss.o     (.text*) */
        *MSDecompress.o  (.text*)
        *MSDecompress.o  (.rodata*)
        /* *MSDecompress.o  (.data*) */
        *MSDecompress.o  (.data*)
        *MSDecompress.o  (.bss*)
        /* *MSDecompress.o  (.scommon*)*/
        *apiSECURE.o     (.rodata*)
        *apiSECURE.o  	 (.text*)
        *apiSECURE.o  	 (.data*)
        *apiSECURE.o  	 (.bss*)
        *apiRSA.o  		 (.rodata*)
        *apiRSA.o  		 (.text*)
        *apiRSA.o  	 	 (.data*)
        *apiRSA.o  	 	 (.bss*)
        *apiSHA.o  		 (.rodata*)
        *apiSHA.o  		 (.text*)
        *apiSHA.o  		 (.data*)
        *apiSHA.o  		 (.bss*)
        *7alloc.o        (.text*)
        *lzmadec.o       (.text*)
        *zlib.o          (.text*)
        *zlib.o          (.rodata*)
        *zlib.o          (.data*)
        *zlib.o          (.bss*)
        *zlib.o          (.scommon*)
        . = ALIGN(16);
        _ld_bootram_RAM_end = .;
    } > ram

    /* dummy */
    .data :
    {
        *(.data)
    } > ram

    .bss :
    {
        . = ALIGN(16);
		_ld_bootbss_start = .;
        *(.bss)
        . = ALIGN(16);
		_ld_bootbss_end = .;
    } > ram
    /DISCARD/ : {


	/* ABI crap starts here */

	*(.reginfo)
    }
#else
    .text1 :
    {
        *boot.o          (.text*)
    } > boot

    .text2 : AT ( LOADADDR(.text1) + SIZEOF(.text1) )
    {
        *drvRIU.o        (.text*)
        *bootrom.o       (.text*)
        *bootrom_pll.o   (.text*)
        *bootrom_clock.o (.text*)
        *bootrom_cache.o (.text*)
        *bootrom_miu.o   (.text*)
        *bootrom.o       (.rodata*)
        *bootrom_data.o  (.rodata*)
        *drvPadConf.o    (.rodata*)
        . = ALIGN(16);
        _ld_bootram_ROM_start = .;
    } > rom

    .text3 : AT ( LOADADDR(.text2) + SIZEOF(.text2) )
    {
        _ld_bootram_RAM_start = .;
        *bootram.o       (.text*)
        *nandflash.o     (.text*)
        *nandflash.o     (.rodata*)
        *uart16550.o     (.text*)
        *setSPI.o     (.text*)
        *setSPI.o     (.rodata*)
        *apiBDMA.o     (.text*)
        *apiBDMA.o     (.rodata*)
        /* *lzss.o     (.text*) */
        *MSDecompress.o  (.text*)
        *MSDecompress.o  (.rodata*)
        /* *MSDecompress.o  (.data*) */
        *MSDecompress.o  (.data*)
        *MSDecompress.o  (.bss*)
        /* *MSDecompress.o  (.scommon*)*/
        *apiSECURE.o     (.rodata*)
        *apiSECURE.o  	 (.text*)
        *apiSECURE.o  	 (.data*)
        *apiSECURE.o  	 (.bss*)
        *apiRSA.o  		 (.rodata*)
        *apiRSA.o  		 (.text*)
        *apiRSA.o  	 	 (.data*)
        *apiRSA.o  	 	 (.bss*)
        *apiSHA.o  		 (.rodata*)
        *apiSHA.o  		 (.text*)
        *apiSHA.o  		 (.data*)
        *apiSHA.o  		 (.bss*)
        *7alloc.o        (.text*)
        *lzmadec.o       (.text*)
        *zlib.o          (.text*)
        *zlib.o          (.rodata*)
        *zlib.o          (.data*)
        *zlib.o          (.bss*)
        *zlib.o          (.scommon*)
        . = ALIGN(16);
        _ld_bootram_RAM_end = .;
    } > ram

    /* dummy */
    .data :
    {
        *(.data)
    } > ram

    .bss :
    {
        . = ALIGN(16);
		_ld_bootbss_start = .;
        *(.bss)
        . = ALIGN(16);
		_ld_bootbss_end = .;
    } > ram
    /DISCARD/ : {


	/* ABI crap starts here */

	*(.reginfo)
    }
#endif

#if (CONFIG_EMMC_BOOT == 1)
    .padding : AT(LOADADDR(.text1) + 0x3000 - 4)
    {
        LONG(0x0)
    } > boot
#elif (CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH == 1)
    .padding : AT(LOADADDR(.text1) + 0x8000 - 4)
    {
        /*LONG(0x0)*/
    } > ram
#else
    .padding : AT(LOADADDR(.text1) + 0x10000 - 4)
    {
        LONG(0x0)
    } > ram
#endif

}
