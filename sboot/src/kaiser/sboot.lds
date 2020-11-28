/*
 * Automatically generated C config: don't edit
 * SBoot version: 1.0.0
 */







/*
 * Platform Configuration
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
 * Env config
 */
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_vector)
MEMORY
{
    boot : ORIGIN = 0x14000000, LENGTH = 8K
    rom : ORIGIN = 0x14000000+0x2000, LENGTH = 16K
    ram : ORIGIN = 0x20100000, LENGTH = 128K
}
SECTIONS
{
    .text1 :
    {
        _ld_MEMORY_boot_start = .;
        *boot.o (.text*)
        _ld_MEMORY_boot_end = .;
    } > boot
    .text2 : AT ( LOADADDR(.text1) + 0x2000 )
    {
        _ld_MEMORY_rom_start = .;
        *drvRIU.o (.text*)
        *bootrom.o (.text*)
        *bootrom.o (.rodata*)
        *drvPadConf.o (.rodata*)
        *drv_miu_init.o (.rodata*)
        . = ALIGN(16);
        _ld_MEMORY_rom_end = .;
        _ld_bootram_ROM_start = .;
    } > rom
    .text3 : AT ( LOADADDR(.text2) + SIZEOF(.text2) )
    {
        _ld_MEMORY_ram_start = .;
        _ld_bootram_RAM_start = .;
        *bootram.o (.text*)
        *nandflash.o (.text*)
        *nandflash.o (.rodata*)
        *uart16550.o (.text*)
        *drv_L1cache.o (.text*)
        *drv_L1cache.o (.rodata*)
        *setSPI.o (.text*)
        *setSPI.o (.rodata*)
        *MSDecompress.o (.text*)
        *apiBDMA.o (.text*)
        *apiBDMA.o (.rodata*)
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
    .padding : AT(LOADADDR(.text1) + 0x10000 - 4)



    {
        LONG(0x0)
    } > ram
}
