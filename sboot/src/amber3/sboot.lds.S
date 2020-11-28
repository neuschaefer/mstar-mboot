OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

ENTRY(_vector)

MEMORY
{
#if (CONFIG_EMMC_BOOT == 1)
    boot :  ORIGIN = 0x00000000,                LENGTH = 12K
#else   
    boot :  ORIGIN = 0x00000000,                LENGTH = 8K
    rom :   ORIGIN = 0x00000000+0x2000,         LENGTH = 16K
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
