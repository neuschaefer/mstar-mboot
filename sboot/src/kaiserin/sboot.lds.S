OUTPUT(elf32-littlemips)
OUTPUT_ARCH(mips)

ENTRY(BOOT_Entry)

MEMORY
{
    boot :  ORIGIN = 0x94000000,                LENGTH = 3K
    /*rom :   ORIGIN = 0x94000000+0xC00,  LENGTH = 16K*/
    rom :   ORIGIN = 0x94000000+0xC00,          LENGTH = 16K
    ram :   ORIGIN = CONFIG_BOOTRAM_LOADADDR,   LENGTH = 128K
    sram :  ORIGIN = 0x84000000,                LENGTH = 1K
}

SECTIONS
{
    .text1 :
    {
        *boot.o          (.text*)
    } > boot

    .text2 : AT ( LOADADDR(.text1) + SIZEOF(.text1) )
    {
        *drvRIU.o        (.text*)
        *bootrom.o       (.text*)
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

    .padding : AT(LOADADDR(.text1) + 0x10000 - 4)
    {
        LONG(0x0)
    } > ram
}
