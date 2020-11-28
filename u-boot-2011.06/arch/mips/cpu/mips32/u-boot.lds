OUTPUT_FORMAT("elf32-tradlittlemips")


OUTPUT_ARCH(mips)

/* STARTUP(vectors.o) */
ENTRY(_start)

MEMORY
{
    ram : ORIGIN = 0x8F1F0180, LENGTH = 0x1000000 /* 16MB */
}

SECTIONS
{
    /*.rom_vectors : { __ram_code_start = .; KEEP(*(.other_vector)) . = . + 0x80; . = ALIGN (0x100); KEEP (*(.reset_vector))} > ram*/
    . = ALIGN(4096);_readonly_start = .;
    .text ALIGN (0x40) : { *(.text) *(.text.*) } > ram
    .rodata ALIGN (0x40) : { . = .; *(.rodata) *(.rodata.*) } > ram
    . = ALIGN(4096);_readonly_end = .;
	.data ALIGN (0x40) : { *(.data) *(.data.*)} > ram
	.reginfo ALIGN (0x40) : { *(.reginfo) } > ram
	.eh_frame ALIGN (0x40) : { *(.eh_frame) } > ram
	.MIPS ALIGN (0x40) : { *(.MIPS.*) } > ram

	_gp = ALIGN(16);
	__got_start = .;
	.got  : { *(.got) } > ram
	__got_end = .;

	__u_boot_cmd_start = .;
	.u_boot_cmd : { *(.u_boot_cmd) } > ram
	__u_boot_cmd_end = .;

	__bss_start = .;
	uboot_end_data = .;
    num_got_entries = (__got_end - __got_start) >> 2;
	.bss ALIGN (0x40) : { *(.dynbss) *(.bss) *(.bss.*) *(.common) } > ram
	.sbss ALIGN (0x40) : { *(.dynsbss) *(.sbss) *(.sbss.*) *(.scommon) } > ram
	uboot_end = .;
	__bss_end = .;

	/* Stack is 16384-byte, ISR and user uses the same stack */
    . = ALIGN(0x40); .stack_end = .; . = . + 16384; __stack_begin = .;

    /* for sbrk.c */
    . = ALIGN (0x8);
    __heap = .; . = . + 0x640000; __heap_end = .;

    /* for boot params() */
    . = ALIGN (0x8);
    __boot_params = .; . = . + 1024*128;  __boot_params_end = .;
}

