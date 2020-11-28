/*
 * January 2004 - Changed to support H4 device
 * Copyright (c) 2004-2008 Texas Instruments
 *
 * (C) Copyright 2002
 * Gary Jennejohn, DENX Software Engineering, <garyj@denx.de>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

STACK_SIZE  = 0x20000;

__assert_func = 0;

SECTIONS
{
    . = 0x00000000;

    . = ALIGN(4);
#ifdef CONFIG_MSTAR_STR_MINISIZE
    .text :
    {
        __config_text_str_start = .;
#ifdef __UBOOT_STR
        arch/arm/cpu/armv7/start_str.o (.text.mstr)
        *(.text.mstr)
        *_str.*(.text*)
        *_str.*(COMMON)
        *(.text*)
        *(COMMON)
#else
        __config_text_mark = .;
#endif
        . = ALIGN(4);
        __config_text_str_end = .;
    }
    .rodata :
    {
        __config_rodata_str_start = .;
#ifdef __UBOOT_STR
        *_str.*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
        *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
#else
        __config_rodata_mark = .;
#endif
        . = ALIGN(4);
        __config_rodata_str_end = .;
    }

    .data :
    {
        __config_data_str_start = .;
#ifdef __UBOOT_STR
        *(.data.mstr)
        *_str.*(.data*)
        *(.data*)
#else
        __config_data_mark = .;
#endif
        . = ALIGN(4);
        __config_data_str_end = .;
    }
     
    .got :
    {
        *(.got*)
        . = ALIGN(4);
    }
    
    .u_boot_cmd_str :
    {
        __config_uboot_cmd_str_start = .;
        __u_boot_cmd_str_start = .;
        KEEP(*(.u_boot_cmd_str))
        . = ALIGN(4);
        __u_boot_cmd_str_end = .;
        __config_uboot_cmd_str_end = .;
    }

    _end_str = .;

    .bss (NOLOAD) : AT(0)
    {
        __config_bss_str_start = .;
        __bss_str_start = .;
#ifdef __UBOOT_STR
        *(.bss.mstr)
        *_str.*(.bss)
        *_str.*(.bss*)
        *(.bss*)
#else
        __config_bss_mark = .;
#endif
        . = ALIGN(4);
        __config_bss_str_end = .;
        __bss_str_end__ = .;
    }
    _uboot_str_end = .;
#ifdef __UBOOT_STR
    uboot2_start = .;
#else
#ifndef __UBOOT_STR_CHK   
    .text2 _uboot_str_end : AT(LOADADDR(.u_boot_cmd_str)+SIZEOF(.u_boot_cmd_str))
    {
        __config_text_start = .;
        arch/arm/cpu/armv7/start.o (.text)
        *(.text*)
        *(COMMON)
        . = ALIGN(4);
        __config_text_end = .;
    }

    .u_boot_cmd :
    {
        __config_uboot_cmd_start = .;
        __u_boot_cmd_start = .;
        KEEP(*(.u_boot_cmd))
        . = ALIGN(4);
        __u_boot_cmd_end = .;
        __config_uboot_cmd_end = .;
    }

    .rodata2 :
    {
        __config_rodata_start = .;
        *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
        . = ALIGN(4);
        __config_rodata_end = .;
    }

    .data2 :
    {
        __config_data_start = .;
        *(.data*)
        . = ALIGN(4);
        __config_data_end = .;
    }
    .rel.dyn :
    {
        __config_rel_dyn_start = .;
        __rel_dyn_start = .;
        *(.rel*)
        . = ALIGN(4);
        __rel_dyn_end = .;
        __config_rel_dyn_end = .;
    }

    .dynsym :
    {
        __config_dynsym_start = .;
        __dynsym_start = .;
        *(.dynsym*)
        . = ALIGN(4);
        __config_dynsym_end = .;
    }
    _end = .;
    .bss2 __rel_dyn_start (NOLOAD) : AT(0)
    {
        __config_bss_start = .;
        __bss_start = .;
        *(.bss)
        *(.bss*)
        . = ALIGN(4);
        __config_bss_end = .;
        __bss_end__ = .;
    }
#else
    uboot2_start = .;
    /DISCARD/ : 
    { 
        *(.text*)
        *(COMMON)
        *(.u_boot_cmd)
        *(.rodata*)
        *(.data*)
        *(.ARM.exidx)
        *(.bss*)
    }
#endif
#endif
    /DISCARD/ : { *(*) }
#else
    .text :
    {
        __config_text_start = .;
        arch/arm/cpu/armv7/start.o (.text)
        *(.text*)
        *(COMMON)
        . = ALIGN(4);
        __config_text_end = .;
    }

    .rodata :
    {
        __config_rodata_start = .;
        *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
        . = ALIGN(4);
        __config_rodata_end = .;
    }

    .data :
    {
        __config_data_start = .;
        *(.data)
        . = ALIGN(4);
        __config_data_end = .;
    }

    .u_boot_cmd :
    {
        __config_uboot_cmd_start = .;
        __u_boot_cmd_start = .;
        *(.u_boot_cmd)
        . = ALIGN(4);
        __u_boot_cmd_end = .;
        __config_uboot_cmd_end = .;
    }

    .rel.dyn :
    {
        __config_rel_dyn_start = .;
        __rel_dyn_start = .;
        *(.rel*)
        . = ALIGN(4);
        __rel_dyn_end = .;
        __config_rel_dyn_end = .;
    }

    .dynsym :
    {
        __config_dynsym_start = .;
        __dynsym_start = .;
        *(.dynsym*)
        . = ALIGN(4);
        __config_dynsym_end = .;
    }

    _end = .;

    .bss __rel_dyn_start (OVERLAY) :
    {
        __config_bss_start = .;
        __bss_start = .;
        *(.bss)
        *(.bss*)
        . = ALIGN(4);
        __config_bss_end = .;
        __bss_end__ = .;
    }
#endif
    /* for sbrk.c */
    __heap = .;
    __heap_end = __heap + 0x640000;

    _ld_irq_stack_end = . ; . = . + STACK_SIZE; _ld_irq_stack_start = . ;
    _ld_fiq_stack_end = . ; . = . + STACK_SIZE; _ld_fiq_stack_start = . ;
    _ld_svc_stack_end = . ; . = . + STACK_SIZE; _ld_svc_stack_start = . ;

    /DISCARD/ : { *(.dynstr*) }
    /DISCARD/ : { *(.dynamic*) }
    /DISCARD/ : { *(.plt*) }
    /DISCARD/ : { *(.interp*) }
    /DISCARD/ : { *(.gnu*) }
}
