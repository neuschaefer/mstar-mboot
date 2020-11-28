ENTRY(__reset)

MEMORY
{
		ram  : ORIGIN = 0x00010000, LENGTH = 0x2000000
		sram : ORIGIN = 0xB0000000, LENGTH = 0x1000    /* t2:   ORIGIN = 0xc0000000, LENGTH = 0x1000    */
}

SECTIONS
{
    .vectors 0x10000 : { . = .; KEEP(*(.reset)) KEEP(*(.vectors)) } > ram
    .interp ALIGN (0x8) : { *(.interp) } > ram
    .hash : AT ((LOADADDR (.interp) + SIZEOF (.interp) + 8 - 1) & ~ (8 - 1)) { *(.hash) } > ram
    .dynsym : AT ((LOADADDR (.hash) + SIZEOF (.hash) + 8 - 1) & ~ (8 - 1)) { *(.dynsym) } > ram
    .dynstr : AT ((LOADADDR (.dynsym) + SIZEOF (.dynsym) + 8 - 1) & ~ (8 - 1)) { *(.dynstr) } > ram
    .init ALIGN (0x8) : { . = .; KEEP (*(.init)) } > ram = 0
    .boot_data 0x00012000: { __boot_data = .; *(.boot_data) } > ram /* for system_init data */
    .text ALIGN(0x10):
    {
        __stext = .; *(.text*) *(.gnu.warning) *(.gnu.linkonce.t.*)
    } > ram

    __etext = .; PROVIDE (etext = .);
    .fini ALIGN (0x4) : { . = .; KEEP (*(.fini)) } > ram =0
    .rodata ALIGN (0x8) : { . = .; *(.rodata) *(.rodata*) *(.gnu.linkonce.r*) } > ram
    .fixup ALIGN (0x4) : { __FIXUP_START__ = ABSOLUTE(.); *(.fixup) __FIXUP_END__ = ABSOLUTE(.);} > ram
    .gcc_except_table ALIGN (0x4) : { __EXCEPT_START__ = ABSOLUTE(.); *(.gcc_except_table) __EXCEPT_END__ = ABSOLUTE(.);} > ram
    .data ALIGN (0x8) : { __ram_data_start = ABSOLUTE(.); *(.data*) *(.data.*) *(.gnu.linkonce.d*) *( .2ram.*) . = ALIGN (8); SORT(CONSTRUCTORS) } > ram
    __rom_data_start = LOADADDR(.data);
    .eh_frame ALIGN (0x8) : { . = .; __EH_FRAME_BEGIN__ = .; KEEP(*(.eh_frame)) __FRAME_END__ = .; . = . + 8; } > ram = 0
    .ctors ALIGN (0x8) : { . = .; KEEP (*crtbegin.o(.ctors)) KEEP (*_ctors.o(.ctors)) ___CTOR_LIST__ = .; PROVIDE (__CTOR_LIST__ = .); KEEP (*(.ctors)); KEEP (*(SORT(.ctors.*))) ___CTOR_END__ = .; PROVIDE (___CTOR_END__ = .); } > ram
    .dtors ALIGN (0x8) : { . = .; KEEP (*crtbegin.o(.dtors)) __DTOR_LIST__ = .; PROVIDE (__DTOR_LIST__ = .); KEEP (*(SORT(.dtors.*))) __DTOR_END__ = .; KEEP (*(.dtors)); PROVIDE (__DTOR_END__ = .); } > ram
    .got ALIGN (0x8) : { . = .; *(.got.plt) *(.got*) } > ram
    .dynamic ALIGN (0x8) : { . = .; *(.dynamic) } > ram
    .sdata ALIGN (0x8) : { __SDATA_START__ = ABSOLUTE(.); . = .; *(.sdata) *(.sdata.*) *(.gnu.linkonce.s*) } > ram
    .sbss ALIGN (0x8) : { __sbss_start = ABSOLUTE (.); __SBSS_START__ = ABSOLUTE(.); *(.sbss.*) __SBSS_END__ = ABSOLUTE(.); __SBSSx_START__ = ABSOLUTE(.); *(.sbss*) __SBSSx_END__ = ABSOLUTE(.); *(.scommon*) __sbss_end = ABSOLUTE (.); } > ram
    .lit8 ALIGN (0x8) : { . = .; *(.lit8) _MY_MARK = . ;  LONG(0xAABBCCDD) . = ALIGN(0x10); } > ram

    __text_length = .;

    .bss 0xB0000000 : AT(LOADADDR(.lit8) + SIZEOF(.lit8))     /* T2: oxc000000  */
    {
        __bss_start = ABSOLUTE (.);
        *(.dynbss*) *(.bss) *(.bss.*) *(COMMON)
        . = ALIGN(0x10);
        __bss_end = ABSOLUTE (.);
    } > sram

    .bin ALIGN (0x8) : AT(0x10000) /* AT(LOADADDR(.ld2) + SIZEOF(.ld2)) */
    {
        . = .; KEEP(*/AP.o(bin.data))
    } > ram

    _ap_bin_lma = LOADADDR(.bin);
    _ap_bin_len = SIZEOF(.bin);

    .padding : AT(LOADADDR(.vectors) + 0x10000 - 4)
    {
        LONG(0x0)
    } > ram

	PROVIDE(_boot_stack     = 0xB0000ff0);    /*T2 : 0xC0001000  */
}
