/*
 * armboot - Startup Code for OMAP3530/ARM Cortex CPU-core
 *
 * Copyright (c) 2004	Texas Instruments <r-woodruff2@ti.com>
 *
 * Copyright (c) 2001	Marius Gröger <mag@sysgo.de>
 * Copyright (c) 2002	Alex Züpke <azu@sysgo.de>
 * Copyright (c) 2002	Gary Jennejohn <garyj@denx.de>
 * Copyright (c) 2003	Richard Woodruff <r-woodruff2@ti.com>
 * Copyright (c) 2003	Kshitij <kshitij@ti.com>
 * Copyright (c) 2006-2008 Syed Mohammed Khasim <x0khasim@ti.com>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <asm-offsets.h>
#include <config.h>
#include <version.h>
#include "arm.inc"
#ifndef CONFIG_MSTAR_STR_MINISIZE
.globl _start
_start: b	reset
	ldr	pc, _undefined_instruction
	ldr	pc, _software_interrupt
	ldr	pc, _prefetch_abort
	ldr	pc, _data_abort
	ldr	pc, _not_used
	ldr	pc, _irq
	ldr	pc, _fiq

_undefined_instruction: .word undefined_handler
_software_interrupt:    .word swi_handler
_prefetch_abort:        .word prefetch_handler
_data_abort:            .word abort_handler
_not_used:              .word not_used
_irq:                   .word irq_handler
_fiq:                   .word fiq_handler
_pad:                   .word 0x12345678 /* now 16*4=64 */

.global _end_vect
_end_vect:

	.balignl 16,0xdeadbeef
/*************************************************************************
 *
 * Startup Code (reset vector)
 *
 * do important init only if we don't start from memory!
 * setup Memory and board specific bits prior to relocation.
 * relocate armboot to ram
 * setup stack
 *
 *************************************************************************/

.globl _TEXT_BASE
_TEXT_BASE:
	.word	CONFIG_SYS_TEXT_BASE

.globl _MIU0_BUS_BASE
_MIU0_BUS_BASE:
	.word	CONFIG_MIU0_BUSADDR

#ifdef CONFIG_TEGRA2
/*
 * Tegra2 uses 2 separate CPUs - the AVP (ARM7TDMI) and the CPU (dual A9s).
 * U-Boot runs on the AVP first, setting things up for the CPU (PLLs,
 * muxes, clocks, clamps, etc.). Then the AVP halts, and expects the CPU
 * to pick up its reset vector, which points here.
 */
.globl _armboot_start
_armboot_start:
	.word _start
#endif

/*
 * These are defined in the board-specific linker script.
 */
.globl _bss_start_ofs
_bss_start_ofs:
	.word __bss_start - _start

.globl _bss_end_ofs
_bss_end_ofs:
	.word __bss_end__ - _start

.globl _end_ofs
_end_ofs:
	.word _end - _start

#ifdef CONFIG_USE_IRQ
/* IRQ stack memory (calculated at run-time) */
.globl IRQ_STACK_START
IRQ_STACK_START:
	.word	0x0badc0de

/* IRQ stack memory (calculated at run-time) */
.globl FIQ_STACK_START
FIQ_STACK_START:
	.word 0x0badc0de
#endif

/* IRQ stack memory (calculated at run-time) + 8 bytes */
.globl IRQ_STACK_START_IN
IRQ_STACK_START_IN:
	.word	0x0badc0de

/*
 * the actual reset code
 */

.globl reset
reset:
#ifdef CONFIG_DYNAMIC_RELOCATE 
    ldr     r0, =(RELOCATION_INFO_ADDRESS)
    ldr     r1, [r0]
    sub    r1, r1, #1
    mov   r1, r1, lsl #20
    add    r1, r1, #CONFIG_SYS_SDRAM_BASE
    mov   sp, r1
#else
    ldr	sp, =(CONFIG_SYS_INIT_SP_ADDR)
#endif

	/*
	 * set the cpu to SVC32 mode
	 */
	mrs	r0, cpsr
	bic	r0, r0, #0x1f
	orr	r0, r0, #0xd3
	msr	cpsr,r0

#if defined(CONFIG_OMAP34XX)
	/* Copy vectors to mask ROM indirect addr */
	adr	r0, _start		@ r0 <- current position of code
	add	r0, r0, #4		@ skip reset vector
	mov	r2, #64			@ r2 <- size to copy
	add	r2, r0, r2		@ r2 <- source end address
	mov	r1, #SRAM_OFFSET0	@ build vect addr
	mov	r3, #SRAM_OFFSET1
	add	r1, r1, r3
	mov	r3, #SRAM_OFFSET2
	add	r1, r1, r3
next:
	ldmia	r0!, {r3 - r10}		@ copy from source address [r0]
	stmia	r1!, {r3 - r10}		@ copy to   target address [r1]
	cmp	r0, r2			@ until source end address [r2]
	bne	next			@ loop until equal */
#if !defined(CONFIG_SYS_NAND_BOOT) && !defined(CONFIG_SYS_ONENAND_BOOT)
	/* No need to copy/exec the clock code - DPLL adjust already done
	 * in NAND/oneNAND Boot.
	 */
	bl	cpy_clk_code		@ put dpll adjust code behind vectors
#endif /* NAND Boot */
#endif
	/* the mask ROM code should have PLL and others stable */
#ifndef CONFIG_SKIP_LOWLEVEL_INIT
	bl	cpu_init_crit
#endif
    
/*  init GIC */
    bl __init_dic
    bl __init_interrupts

/* Set stackpointer in internal RAM to call board_init_f */
call_board_init_f:
	bic	sp, sp, #7 /* 8-byte alignment for ABI compliance */
	ldr	r0,=0x00000000
	bl	board_init_f

/*------------------------------------------------------------------------------*/

/*
 * void relocate_code (addr_sp, gd, addr_moni)
 *
 * This "function" does not return, instead it continues in RAM
 * after relocating the monitor code.
 *
 */
	.globl	relocate_code
relocate_code:
	mov	r4, r0	/* save addr_sp */
	mov	r5, r1	/* save addr of gd */
	mov	r6, r2	/* save addr of destination */

	/* Set up the stack						    */
stack_setup:
	mov	sp, r4

	adr	r0, _start
#ifndef CONFIG_PRELOADER
	cmp	r0, r6
	beq	clear_bss		/* skip relocation */
#endif
	mov	r1, r6			/* r1 <- scratch for copy_loop */
	ldr	r3, _bss_start_ofs
	add	r2, r0, r3		/* r2 <- source end address	    */

copy_loop:
	ldmia	r0!, {r9-r10}		/* copy from source address [r0]    */
	stmia	r1!, {r9-r10}		/* copy to   target address [r1]    */
	cmp	r0, r2			/* until source end address [r2]    */
	blo	copy_loop

#ifndef CONFIG_PRELOADER
	/*
	 * fix .rel.dyn relocations
	 */
	ldr	r0, _TEXT_BASE		/* r0 <- Text base */
	sub	r9, r6, r0		/* r9 <- relocation offset */
	ldr	r10, _dynsym_start_ofs	/* r10 <- sym table ofs */
	add	r10, r10, r0		/* r10 <- sym table in FLASH */
	ldr	r2, _rel_dyn_start_ofs	/* r2 <- rel dyn start ofs */
	add	r2, r2, r0		/* r2 <- rel dyn start in FLASH */
	ldr	r3, _rel_dyn_end_ofs	/* r3 <- rel dyn end ofs */
	add	r3, r3, r0		/* r3 <- rel dyn end in FLASH */
fixloop:
	ldr	r0, [r2]		/* r0 <- location to fix up, IN FLASH! */
	add	r0, r0, r9		/* r0 <- location to fix up in RAM */
	ldr	r1, [r2, #4]
	and	r7, r1, #0xff
	cmp	r7, #23			/* relative fixup? */
	beq	fixrel
	cmp	r7, #2			/* absolute fixup? */
	beq	fixabs
	/* ignore unknown type of fixup */
	b	fixnext
fixabs:
	/* absolute fix: set location to (offset) symbol value */
	mov	r1, r1, LSR #4		/* r1 <- symbol index in .dynsym */
	add	r1, r10, r1		/* r1 <- address of symbol in table */
	ldr	r1, [r1, #4]		/* r1 <- symbol value */
	add	r1, r1, r9		/* r1 <- relocated sym addr */
	b	fixnext
fixrel:
	/* relative fix: increase location by offset */
	ldr	r1, [r0]
	add	r1, r1, r9
fixnext:
	str	r1, [r0]
	add	r2, r2, #8		/* each rel.dyn entry is 8 bytes */
	cmp	r2, r3
	blo	fixloop

clear_bss:
	ldr	r0, _bss_start_ofs
	ldr	r1, _bss_end_ofs
	mov	r4, r6			/* reloc addr */
	add	r0, r0, r4
	add	r1, r1, r4
	mov	r2, #0x00000000		/* clear			    */

clbss_l:str	r2, [r0]		/* clear loop...		    */
	add	r0, r0, #4
	cmp	r0, r1
	bne	clbss_l
#endif	/* #ifndef CONFIG_PRELOADER */

/*
 * We are done. Do not return, instead branch to second part of board
 * initialization, now running from RAM.
 */
jump_2_ram:
	ldr	r0, _board_init_r_ofs
	adr	r1, _start
	add	lr, r0, r1
	add	lr, lr, r9
	/* setup parameters for board_init_r */
	mov	r0, r5		/* gd_t */
	mov	r1, r6		/* dest_addr */
	/* jump to it ... */
	mov	pc, lr

_board_init_r_ofs:
	.word board_init_r - _start

_rel_dyn_start_ofs:
	.word __rel_dyn_start - _start
_rel_dyn_end_ofs:
	.word __rel_dyn_end - _start
_dynsym_start_ofs:
	.word __dynsym_start - _start

/*************************************************************************
 *
 * CPU_init_critical registers
 *
 * setup important registers
 * setup memory timing
 *
 *************************************************************************/
cpu_init_crit:
	/*
	 * Invalidate L1 I/D
	 */
	mov	r0, #0			@ set up for MCR
	mcr	p15, 0, r0, c8, c7, 0	@ invalidate TLBs
	mcr	p15, 0, r0, c7, c5, 0	@ invalidate icache

	/*
	 * disable MMU stuff and caches
	 */
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, r0, #0x00002000	@ clear bits 13 (--V-)
	bic	r0, r0, #0x00000007	@ clear bits 2:0 (-CAM)
	orr	r0, r0, #0x00000002	@ set bit 1 (--A-) Align
	orr	r0, r0, #0x00000800	@ set bit 12 (Z---) BTB
	mcr	p15, 0, r0, c1, c0, 0

	/*
	 * Jump to board specific initialization...
	 * The Mask ROM will have already initialized
	 * basic memory. Go here to bump up clock rate and handle
	 * wake up conditions.
	 */
	mov	ip, lr			@ persevere link reg across call
	bl	lowlevel_init		@ go setup pll,mux,memory
	mov	lr, ip			@ restore link
	mov	pc, lr			@ back to my caller


/*************************************************************************
 *
 * Create initial single-levle page table 
 *
 * setup vector mappoing
 *
 *************************************************************************/
.globl enable_mmu
enable_mmu:

    /* r0=tlb address */
    /* r1=relocated vector physical address */
   
    /*
    * Backup GPRs in dram
    */
    sub     sp, sp, #S_FRAME_SIZE   
    stmia   sp, {r0 - r14}                 @ copy r0-r14
    
    /*
    * Clear the 16K level 1 swapper page table
    */
    mov r4, r0
    mov r3, #0
    add r6, r0, #0x4000
1:  str r3, [r0], #4
    str r3, [r0], #4
    str r3, [r0], #4
    str r3, [r0], #4
    teq r0, r6
    bne 1b

    ldr r7, =noncache_mm_flags

    /*
    * Create identity mapping for first MB of kernel to
    * cater for the MMU enable.  This identity mapping
    * will be removed by paging_init().  We use our current program
    * counter to determine corresponding section base address.
    * VA=PA , length = 1MB
    */
    
    /*
    * Setup the pagetables vector mapped region.
    * VA=0x00000000 PA=0x40010000 , lengtg = 1MB
    */
    ldr r6, =0x00000000
    mov r6, r6, lsr #20         @ start of vector section
    mov r3, r1		            @ r1 = Vector PA base
    mov r3, r3, lsr #20         @ start of vector section
    orr r3, r7, r3, lsl #20      @ flags + ebase
    str r3, [r4, r6, lsl #2]      @ identity mapping

    
    /*
    * Setup the pagetables for SPI,RIU and ARM peripheral register direct mapping
    * mapped region.
    * VA=0x14000000 PA=0x14000000 , Length=0x01000000 (SPI)
    * VA=0x15000000 PA=0x15000000 , Length=0x01000000 (PL310)
    * VA=0x16000000 PA=0x16000000 , Length=0x01000000 (ARM peripheral register)
    * VA=0x1f000000  PA=0x20000000 , Length=0x01000000 (Mstar RIU)
    */
    ldr r3, =0x14000000
    mov r3, r3, lsr #20         @ start of AP section
    orr r3, r7, r3, lsl #20     @ flags + AP_base
    ldr r1, =0x14000000
    and r1, r1, #0xff000000
    mov r1, r1, lsr #18
    add r0, r4, r1
    ldr r1, =0x14000000
    and r1, r1, #0x00f00000
    mov r1, r1, lsr #18
    str r3, [r0, r1]!
    ldr r6, =(0x20000000 - 1)
    add r0, r0, #4
    add r6, r4, r6, lsr #18
2:  cmp r0, r6
    add r3, r3, #1 << 20
    strls   r3, [r0], #4
    bls 2b

    ldr r7, =cache_mm_flags
       
    /*
    * Setup the pagetables for 4GB-1MB direct mapping
    * mapped region.
    * VA=CONFIG_MIU0_BUSADDR PA=CONFIG_MIU0_BUSADDR , Length=0x40000000
    */
    ldr r3, _MIU0_BUS_BASE
    mov r3, r3, lsr #20         @ start of AP section
    orr r3, r7, r3, lsl #20     @ flags + AP_base
    ldr r1, _MIU0_BUS_BASE
    and r1, r1, #0xff000000
    mov r1, r1, lsr #18
    add r0, r4, r1
    ldr r1, _MIU0_BUS_BASE
    and r1, r1, #0x00f00000
    mov r1, r1, lsr #18
    str r3, [r0, r1]!
    ldr r1, _MIU0_BUS_BASE
    add r6, r1, #(0x40000000-1)
    add r0, r0, #4
    add r6, r4, r6, lsr #18
3:  cmp r0, r6
    add r3, r3, #1 << 20
    strls   r3, [r0], #4
    bls 3b

    /* setup mmu*/
    mov	r0, #(domain_val(DOMAIN_USER, DOMAIN_MANAGER) | \
		      domain_val(DOMAIN_AP, DOMAIN_MANAGER) | \
		      domain_val(DOMAIN_BOOT, DOMAIN_MANAGER))
    mcr	p15, 0, r0, c3, c0, 0		@ load domain access register
    mcr	p15, 0, r4, c2, c0, 0		@ load page table pointer

    /* enable mmu*/
    mrc	p15, 0, r0, c1, c0, 0		@ read control reg
    ldr      r1, =0x00001001
    orr	r0, r0, r1
    mov	r0, r0
    mcr	p15, 0, r0, c1, c0, 0		@ write control reg
    mrc	p15, 0, r3, c0, c0, 0		@ read id reg
    
    /*
    * Restore GPRs in dram
    */
    ldmia  sp, {r0 - lr}^			@ Restore r0 - lr
    add    sp, sp, #S_FRAME_SIZE
  
    mov pc, lr
    
/*************************************************************************
 *
 * Init data catche
 *
 *************************************************************************/
.globl dcache_init
dcache_init:

    @ Invalidate D-cache by set/way
    @ Note: for Cortex-A9, there is no instruction for invalidating
    @ the whole D-cache. Need to invalidate line by line.
    @ Read cache size from the Cache Size Identification Register
    
    mrc p15, 1, r3, c0, c0, 0           @ Read current Cache Size Identification Register
    mov r1, #0x200
    sub r1, r1, #1
    and r3, r1, r3, LSR #13             @ r3 = (number of sets - 1)
    mov r0, #0                          @ r0 -> way counter
way_loop:
    mov r1, #0                          @ r1 -> set counter
set_loop:
    mov r2, r0, LSL #30                 @
    orr r2, r1, LSL #5                  @ r2 -> set/way cache-op format
    mcr p15, 0, r2, c7, c6, 2           @ Invalidate line described by r2
    add r1, r1, #1                      @ Increment set counter
    cmp r1, r3                          @ Check if the last set is reached...
    ble set_loop                        @ ...if not, continue the set_loop...
    add r0, r0, #1                      @ ...else, Increment way counter
    cmp r0, #4                          @ Check if the last way is reached...
    blt way_loop                        @ ...if not, continue the way_loop

    @ Enable dcaches
    @ D-cache is controlled by bit 2
    mrc p15, 0, r0, c1, c0, 0           @ read CP15 register 1
    orr r0, r0, #(0x1 <<2)              @ enable D Cache
    mcr p15, 0, r0, c1, c0, 0           @ write CP15 register 1

    @ Enable Program Flow Prediction
    @ Branch prediction is controlled by the System Control Register:
    @ Set Bit 11 to enable branch prediciton and return stack
    @ Turning on branch prediction requires a general enable
    @ CP15, c1. Control Register
    @ Bit 11 [Z] bit Program flow prediction:
    @ 0 = Program flow prediction disabled
    @ 1 = Program flow prediction enabled.
    mrc p15, 0, r0, c1, c0, 0           @ Read System Control Register
    orr r0, r0, #(0x1 <<11)
    mcr p15, 0, r0, c1, c0, 0           @ Write System Control Register

    @ Enable D-side prefetch
    @ Bit 2 [DP] Dside prefetch:
    @ 0 = Dside prefetch disabled
    @ 1 = Dside prefetch enabled.
    mrc 15, 0, r0, c1, c0, 1            @ Read Auxiliary Control Register
    orr r0, r0, #(0x1 <<2)              @ Enable Dside prefetch
    mcr p15, 0, r0, c1, c0, 1           @ Write Auxiliary Control Register

    mov pc, lr
/*************************************************************************
 * 
 * setup irq stack pointer
 *
 *************************************************************************/
.globl set_irq_sp
set_irq_sp:
    /* r0=irq stack pointer */
    set_irq_mode            @ change to IRQ mode
    mov sp, r0                  @ set IRQ_SP
    set_svc32_mode       @ change back to SVC mode
     
    mov pc, lr
    
/*************************************************************************
 *
 * Init  GIC
 *
 *************************************************************************/
__init_dic:

    @ disable interrupts in DIC
    ldr   r0, =dic_pa
    ldr   r1, =0x0 @ DICControl offset
    mov   r2, #0
    str   r2, [r0, r1]
 
    @ disable all interrupt sources ID0-ID63
    ldr   r1, =0x180 @ Interrupt Clear-enable Register ID0-ID31 offset
    ldr   r2, =0xFFFFFFFF @ Disable All Interrupts. Does not affect SW interrupts (ID0-ID15)
    str   r2, [r0, r1]
    ldr   r1, =0x184 @ Interrupt Clear-enable Register ID32-ID63 offset
    str   r2, [r0, r1]
 
    @ clear all pending interrupts
    ldr   r1, =0x280 @ Interrupt Clear-pending Register ID0-ID31 offset
    ldr   r2, =0xFFFFFFFF @ Clear All Pending Interrupts
    str   r2, [r0, r1]
    ldr   r1, =0x284 @ Interrupt Clear-pending Register ID32-ID63 offset
    str   r2, [r0, r1]
 
    @ enable interrupts in DIC
    ldr   r0, =dic_pa
    ldr   r1, =0x0 @ DICControl offset
    ldr   r2, [r0, r1]
    orr   r2, r2, #0x1
    str   r2, [r0, r1]
 
    bx    lr


/*
 * Init CPU Interrupt Interface
 */

__init_interrupts:

    @ disable interrupts in CPU Interface
    ldr   r0, =cpu_if_pa
    ldr   r1, =0x0 @ CPUControl offset
    mov   r2, #0
    str   r2, [r0, r1]
    
    @ enable interrupt sources in DIC we care about
    @ ID29 = Timer counter wrap interrupt
    ldr   r0, =dic_pa
    ldr   r1, =0x100 @ Interrupt Set-enable Register ID0-ID31 offset
    ldr   r2, [r0, r1]
#ifdef CONFIG_64BIT_TO_32BIT_MODE 
    orr   r2, r2, #1 << 30
#else
    orr   r2, r2, #1 << 29
#endif
    orr   r2, r2, #1 << 31
    str   r2, [r0, r1]
    
    @ set ID29 interrupt priority to highest
    ldr   r1, =0x41C @ Priority level Register ID28-ID31 offset
    ldr   r2, [r0, r1]
#ifdef CONFIG_64BIT_TO_32BIT_MODE 
    bic   r2, r2, #0x00FF0000 @ Set ID30 priority to 0 (highest priority)
#else
    bic   r2, r2, #0x0000FF00 @ Set ID29 priority to 0 (highest priority)
#endif
    str   r2, [r0, r1]
 
    @ set priority mask to 1 (allowing interrupts with priority of 0 through)
    @ i.e. ID29 Timer Interrupt
    ldr   r0, =cpu_if_pa
    ldr   r1, =0x4 @ Priority Mask Register offset
    ldr   r2, =1 << 3
    str   r2, [r0, r1]
 
    @ enable interrupts in CPU interface
    ldr   r1, =0x0 @ CPUControl offset
    ldr   r2, [r0, r1]
    orr   r2, r2, #1
    str   r2, [r0, r1]
 
    bx    lr


/*
 *************************************************************************
 *
 * Interrupt handling
 *
 *************************************************************************
 */
.macro get_irq_stack			@ setup IRQ stack
    ldr	sp, IRQ_STACK_START
.endm

    .align  5
undefined_handler:
    ldr sp, _TEXT_BASE		           @ temporary stack pointer for undefined mode 
    sub     sp, sp, #S_FRAME_SIZE   
    stmia   sp, {r0 - r15}                 @ copy r0-r15
    add     r1, sp, #S_PSR                 
    mrs     r2, cpsr
    str       r2, [r1] 
    mov r0, sp
    bl uboot_do_undefined_instruction
undefined_loop:
    b undefined_loop

    .align  5
swi_handler:
    ldr sp, _TEXT_BASE		           @ temporary stack pointer for swi mode 
    sub     sp, sp, #S_FRAME_SIZE   
    stmia   sp, {r0 - r15}                 @ copy r0-r15
    add     r1, sp, #S_PSR                 
    mrs     r2, cpsr
    str       r2, [r1] 
    mov r0, sp
    bl uboot_do_software_interrupt 
swi_loop:
    b swi_loop

    .align  5
prefetch_handler:
    ldr sp, _TEXT_BASE		           @ temporary stack pointer for prefetch mode 
    sub     sp, sp, #S_FRAME_SIZE   
    stmia   sp, {r0 - r15}                 @ copy r0-r15
    add     r1, sp, #S_PSR                 
    mrs     r2, cpsr
    str     r2, [r1] 
    mov r0, sp
    bl uboot_do_prefetch_abort
prefetch_loop:
    b prefetch_loop

    .align  5
abort_handler:
    ldr sp, _TEXT_BASE		           @ temporary stack pointer for abort mode 
    sub     sp, sp, #S_FRAME_SIZE   
    stmia   sp, {r0 - r15}                 @ copy r0-r15
    add     r1, sp, #S_PSR                 
    mrs     r2, cpsr
    str     r2, [r1] 
    mov r0, sp                             @ pass pt_regs to from sp to r0
    bl uboot_do_data_abort 
abort_loop: 
    b abort_loop

    .align  5
not_used:
    ldr sp, _TEXT_BASE		           @ temporary stack pointer for not_used mode 
    sub     sp, sp, #S_FRAME_SIZE   
    stmia   sp, {r0 - r15}                 @ copy r0-r15
    add     r1, sp, #S_PSR                 
    mrs     r2, cpsr
    str     r2, [r1] 
    mov r0, sp                             @ pass pt_regs to from sp to r0
    bl uboot_do_not_used 
not_used_loop: 
    b not_used_loop

    .align  5
irq_handler:
    sub sp, sp, #S_FRAME_SIZE
    stmia   sp, {r0 - r12}          @ Calling r0-r12
    add r8, sp, #S_PC               @ !! R8 NEEDS to be saved !!
                                    @ a reserved stack spot would be good.
    stmdb   r8, {sp, lr}^           @ Calling SP, LR
    str lr, [r8, #0]                @ Save calling PC
    mrs r6, spsr
    str r6, [r8, #4]                @ Save CPSR
    str r0, [r8, #8]                @ Save OLD_R0
    mov r0, sp
    
    @Acknowledge Interrup
    ldr   r0, =cpu_if_pa
    ldr   r1, =0xc @ Interrupt Acknowledge Register offset
    ldr   r2, [r0, r1]
    ldr   r3, =0x3F @ ACK_INTID mask
    and   r4, r2, r3 @ INTID - we need this at irq_handler_end
#ifdef CONFIG_64BIT_TO_32BIT_MODE 
    cmp   r4, #30 @Physical timer ID
#else
    cmp   r4, #29 @Private timer ID
#endif
    bleq  timer_interrupt_handler
    blne  do_irq
    
irq_handler_end:
    @Signal End of Interrupt
    ldr   r0, =cpu_if_pa
    ldr   r1, =0x10 @ End Of Interrupt Register offset
    str   r4, [r0, r1]

    ldmia  sp, {r0 - lr}^			@ Calling r0 - lr
    mov	   r0, r0
    ldr	   lr, [sp, #S_PC]			    @ Get PC
    add    sp, sp, #S_FRAME_SIZE
    subs   pc, lr, #4			    @ return & move spsr_svc into cpsr

    .align  5
fiq_handler:
    b fiq_handler

#else
    .globl uboot2_start
uboot2_start:
    adr   r6, call_board_init_f
    sub   r5, r3, r2
    add   lr, r6, r5
    ldr   r6, _end2_ofs
    add   r5, r2, r6
    add   r6, r3, r6
    bx    r4

call_board_init_f:
    str   r1, uboot1_start
    bl    board_init_f

.globl _end2_ofs
_end2_ofs:
	.word _end - uboot2_start

.globl uboot2_ofs
uboot2_ofs:
    .word uboot2_start - CONFIG_SYS_TEXT_BASE

.globl uboot1_start
uboot1_start:
    .word 0xdeadbeaf
/*------------------------------------------------------------------------------*/

/*
 * void relocate_code (addr_sp, gd, addr_moni)
 *
 * This "function" does not return, instead it continues in RAM
 * after relocating the monitor code.
 *
 */
	.globl	relocate_code
relocate_code:
	mov	r4, r0	/* save addr_sp */
	mov	r5, r1	/* save addr of gd */
	mov	r6, r2	/* save addr of destination */
	mov	r8, r3  /* save jump addr */

	/* Set up the stack						    */
stack_setup:
	mov	sp, r4

	ldr	r0, uboot1_start
#ifndef CONFIG_PRELOADER
	cmp	r0, r6
	beq	clear_bss		/* skip relocation */
#endif
	mov	r1, r6			/* r1 <- scratch for copy_loop */
	ldr	r2, uboot2_ofs
	ldr	r3, _bss_start_ofs
	add	r3, r3, r2
	add	r2, r0, r3		/* r2 <- source end address	    */

copy_loop:
	ldmia	r0!, {r9-r10}		/* copy from source address [r0]    */
	stmia	r1!, {r9-r10}		/* copy to   target address [r1]    */
	cmp	r0, r2			/* until source end address [r2]    */
	blo	copy_loop

#ifndef CONFIG_PRELOADER
	/*
	 * fix .rel.dyn relocations
	 */
	ldr	r0, =CONFIG_SYS_TEXT_BASE		/* r0 <- Text base */
	sub	r9, r6, r0		/* r9 <- relocation offset */
	ldr	r0, uboot1_start
	ldr	r1, uboot2_ofs
	add	r1, r1, r0
	ldr	r10, _dynsym_start_ofs	/* r10 <- sym table ofs */
	add	r10, r10, r1		/* r10 <- sym table in FLASH */
	ldr	r2, _rel_dyn_start_ofs	/* r2 <- rel dyn start ofs */
	add	r2, r2, r1		/* r2 <- rel dyn start in FLASH */
	ldr	r3, _rel_dyn_end_ofs	/* r3 <- rel dyn end ofs */
	add	r3, r3, r1		/* r3 <- rel dyn end in FLASH */
fixloop:
	ldr	r0, [r2]		/* r0 <- location to fix up, IN FLASH! */
	add	r0, r0, r9		/* r0 <- location to fix up in RAM */
	ldr	r1, [r2, #4]
	and	r7, r1, #0xff
	cmp	r7, #23			/* relative fixup? */
	beq	fixrel
	cmp	r7, #2			/* absolute fixup? */
	beq	fixabs
	/* ignore unknown type of fixup */
	b	fixnext2
fixabs:
	/* absolute fix: set location to (offset) symbol value */
	mov	r1, r1, LSR #4		/* r1 <- symbol index in .dynsym */
	add	r1, r10, r1		/* r1 <- address of symbol in table */
	ldr	r1, [r1, #4]		/* r1 <- symbol value */
	add	r1, r1, r9		/* r1 <- relocated sym addr */
	b	fixnext
fixrel:
	/* relative fix: increase location by offset */
	ldr	r1, [r0]
	add	r1, r1, r9
fixnext:
	str	r1, [r0]
fixnext2:
	add	r2, r2, #8		/* each rel.dyn entry is 8 bytes */
	cmp	r2, r3
	blo	fixloop

clear_bss:
	ldr	r0, _bss_start_ofs
	ldr	r1, _bss_end_ofs
	ldr	r4, uboot2_ofs
	add	r4, r4, r6			/* reloc addr */
	add	r0, r0, r4
	add	r1, r1, r4
	mov	r2, #0x00000000		/* clear			    */

clbss_l:str	r2, [r0]		/* clear loop...		    */
	add	r0, r0, #4
	cmp	r0, r1
	bne	clbss_l
#endif	/* #ifndef CONFIG_PRELOADER */

/*
 * We are done. Do not return, instead branch to second part of board
 * initialization, now running from RAM.
 */
jump_2_ram:
    mov lr, r8
	add	lr, lr, r9
	/* setup parameters for board_init_r */
	mov	r0, r5		/* gd_t */
	mov	r1, r6		/* dest_addr */
	/* jump to it ... */
	mov	pc, lr
/*
 * These are defined in the board-specific linker script.
 */
.globl _bss_start_ofs
_bss_start_ofs:
	.word __bss_start - uboot2_start

.globl _bss_end_ofs
_bss_end_ofs:
	.word __bss_end__ - uboot2_start

.globl _end_ofs
_end_ofs:
	.word _end - uboot2_start

_rel_dyn_start_ofs:
	.word __rel_dyn_start - uboot2_start
_rel_dyn_end_ofs:
	.word __rel_dyn_end - uboot2_start
_dynsym_start_ofs:
	.word __dynsym_start - uboot2_start
#endif
