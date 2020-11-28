/*
 *  Startup Code for MIPS32 CPU-core
 *
 *  Copyright (c) 2003	Wolfgang Denk <wd@denx.de>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <asm-offsets.h>
#include <config.h>
#include <asm/regdef.h>
#include <asm/mipsregs.h>


#define STORE_OP        sw
#define BLOCK_SHIFT     5
#define mips_regsize    4
#define mips_regsize32  4

#define mipsreg_regs    0
#define mipsreg_hi      (mips_regsize*32)
#define mipsreg_lo      (mipsreg_hi+1*mips_regsize)
#define mipsreg_sr      (mipsreg_hi+2*mips_regsize)
#define mipsreg_vector  (mipsreg_hi+3*mips_regsize)
#define mipsreg_pc      (mipsreg_hi+4*mips_regsize)
#define mipsreg_cause   (mipsreg_hi+5*mips_regsize)
#define mipsreg_badvr   (mipsreg_hi+6*mips_regsize)

/*
 * The variant HAL should specify which additional registers it needs,
 * but older HALs don't do this.
 */

#define mipsreg_cachectrl   (mipsreg_badvr+mips_regsize)
#define mipsreg_prid        (mipsreg_cachectrl+mips_regsize32)
#define mipsreg_config      (mipsreg_prid+mips_regsize32)
#define mipsreg_size        (mipsreg_config+mips_regsize32)

/*
 * The following expression ensures that the decrement is always a
 * multiple of 16 bytes. This is a requirement of the MEABI used in
 * MIPS32/64 targets.
 */

#define mips_exception_decrement    ((mipsreg_size*2)&~0xF)

.macro sgpr reg,ptr
    sw      $\reg,(mipsreg_regs+\reg*mips_regsize)(\ptr)
.endm

.macro lgpr reg,ptr
    lw     $\reg,(mipsreg_regs+\reg*mips_regsize)(\ptr)
.endm

.macro WREG reg, value
    lui     $8, \reg >> 16
    li      $9, \value
    sw      $9, (\reg & 0xFFFF)($8)
.endm

.macro	mfc0_delay
    nop
    nop
    nop
    nop
.endm

.macro DBGREG value
    WREG    0xBF206700, \value
.endm

	.set noreorder
    .set noat

	.globl other_vector
    .ent other_vector
other_vector:
    b romExcHandle
    nop
    .end other_vector
    
	.globl _start
    .ent _start
_start:
    /* Clear cause */
    mtc0    zero, CP0_CAUSE
    mfc0_delay

    /* Set status register */
    li	    k0, 0x10000000
    mtc0    k0, CP0_STATUS
    mfc0_delay

    /* Clear count */
    mtc0    zero, CP0_COUNT
    mfc0_delay

	/* Initialize $gp */
	bal	4f
	 nop
	.word	_gp
4:
	lw	gp, 0(ra)

    /*
     * Set interrupt mode to compaitible mode.
     * Need not to fill IntCtlVs, the default value is already 0.
     * Set CauseIv = 0. Use general exception vector. page 66, 117.
     */
    mfc0    k0, CP0_CAUSE
    mfc0_delay

    li      k1, ~(1<<23)
    and     k0, k0, k1
    mtc0    k0, CP0_CAUSE
    mfc0_delay


    /* Set StatusBEV  = 1 and adjust EBASE coprocessor */
    mfc0    k0, CP0_STATUS
    mfc0_delay
/*
    li      k1, (1<<22)
    or      k0, k0, k1
*/
    mtc0    k0, CP0_STATUS
    mfc0_delay
    li      k0, 0x0FFFF000
    la      k1, other_vector
    and     k1, k1,k0
    nop
    mfc0    k0, $15, 1
    mfc0_delay
    or      k0, k0, k1
    mtc0    k0, $15, 1
    mfc0_delay

    /* Set StatusBEV & StatusEXL to be zero. page 66, */
    mfc0    k0, CP0_STATUS
    mfc0_delay

    li      k1, ~((1<<22)|(1<<1))
    and     k0, k0, k1
    mtc0    k0, CP0_STATUS
    mfc0_delay

    /* Disable all interrupts. */
    mfc0    k0, CP0_STATUS
    mfc0_delay

    li      k1, 0xffff00fe
    and     k0, k0, k1
    mtc0    k0, CP0_STATUS
    mfc0_delay

    /* Clear BSS */
    la      a0, __bss_start                     # start of bss
    la      a1, __bss_end                       # end of bss
    andi    a2, a0, mips_regsize-1              # is bss aligned?
    bne     a2, zero, 1f                        # skip word copy
    nop

    # loop with 8 stores per loop
    subu            a3,a1,a0                    # get length
    srl             a3,a3,BLOCK_SHIFT           # get number of blocks
    sll             a3,a3,BLOCK_SHIFT           # get length of blocks
    addu            a3,a0,a3                    # get end addr of blocks
2:  STORE_OP        zero,(mips_regsize*0)(a0)
    STORE_OP        zero,(mips_regsize*1)(a0)
    STORE_OP        zero,(mips_regsize*2)(a0)
    STORE_OP        zero,(mips_regsize*3)(a0)
    STORE_OP        zero,(mips_regsize*4)(a0)
    STORE_OP        zero,(mips_regsize*5)(a0)
    STORE_OP        zero,(mips_regsize*6)(a0)
    STORE_OP        zero,(mips_regsize*7)(a0)
    addu            a0,a0,mips_regsize*8        # next addr
    bne             a3,a0,2b                    # to next store
    nop

    # If length is a multiple of block size then we
    # are done and need to skip the byte loop
    beq		a1,a0,3f
    nop

    # finish 1 byte at a time
1:  sb      zero,0(a0)                          # zero memory
    addiu   a0,a0,1                             # next addr
    bne     a0,a1,1b                            # to next store
    nop
3:

    /* Clear stack.*/
    li      t0, 0xDEADBEEF
    la      k0, .stack_end
    la      k1, __stack_begin
5:
    sw      t0, 0(k0)
    addi    k0, 4
    bne     k1, k0, 5b
    nop

    /* Set the correct user stack pointer. */
    la      sp, __stack_begin-16
    move    fp, sp
    la      a0,__stack_begin

	la	t9, board_init_f
	jr	t9
	nop

	.end	_start


	/* Exception handlers */
romReserved:
	b	romReserved

romExcHandle:
    /* Save all registers */
    addi    sp, sp, -mips_exception_decrement
    sgpr    0, sp
    sgpr    1, sp
    sgpr    2, sp
    sgpr    3, sp
    sgpr    4, sp
    sgpr    5, sp
    sgpr    6, sp
    sgpr    7, sp
    sgpr    8, sp
    sgpr    9, sp
    sgpr    10, sp
    sgpr    11, sp
    sgpr    12, sp
    sgpr    13, sp
    sgpr    14, sp
    sgpr    15, sp
    sgpr    16, sp
    sgpr    17, sp
    sgpr    18, sp
    sgpr    19, sp
    sgpr    20, sp
    sgpr    21, sp
    sgpr    22, sp
    sgpr    23, sp
    sgpr    24, sp
    sgpr    25, sp
    sgpr    26, sp    # == K0
    sgpr    27, sp    # == K1
    sgpr    28, sp    # == GP
    sgpr    29, sp    # == SP
    sgpr    30, sp    # == FP
    sgpr    31, sp    # == RA
   
    mfc0    t1, CP0_STATUS
    mfc0_delay
    mfc0    t2, CP0_EPC
    mfc0_delay
    mfc0    t3, CP0_CAUSE
    mfc0_delay
    sw      t1, mipsreg_sr(sp)
    sw      t2, mipsreg_pc(sp)
    sw      t3, mipsreg_cause(sp)

    /* Initialize $gp */
    bal	5f
    nop
    .word	_gp
5:
    lw	gp, 0(ra)

    la      gp, _gp
    sw      sp, (gp)

    /* judge if it is an exception. */
    mfc0    k0, CP0_CAUSE
    mfc0_delay
    andi    k0, k0, 0x7c                    # exccode, page 119
    beqz    k0, 9f
    nop

    b       Process_Exception
    nop
9:
    mfc0    k0, CP0_STATUS
    mfc0_delay
    li      k1, 0xfffffffe
    and     k0, k0, k1
    mtc0    k0, CP0_STATUS
    mfc0_delay

    lgpr    26, sp    # == K0
    lgpr    27, sp    # == K1

    jal     mhal_interrupt_handler
    nop

    la      gp, _gp
    lw      sp, (gp)

    lw      k1, mipsreg_sr(sp)      # K1 = saved SR
    lw      k0, mipsreg_pc(sp)      # K0 = return PC

    ori     k1, k1, 1
    ori     k1, k1, 2               # prevent interrupts until eret
    mtc0	k1,CP0_STATUS	        # put SR back
    nop
    nop
    nop
    mtc0    k0,CP0_EPC	            # put PC in EPC
    nop
    nop
    nop

    lgpr    0, sp
    lgpr    1, sp
    lgpr    2, sp
    lgpr    3, sp
    lgpr    4, sp
    lgpr    5, sp
    lgpr    6, sp
    lgpr    7, sp
    lgpr    8, sp
    lgpr    9, sp
    lgpr    10, sp
    lgpr    11, sp
    lgpr    12, sp
    lgpr    13, sp
    lgpr    14, sp
    lgpr    15, sp
    lgpr    16, sp
    lgpr    17, sp
    lgpr    18, sp
    lgpr    19, sp
    lgpr    20, sp
    lgpr    21, sp
    lgpr    22, sp
    lgpr    23, sp
    lgpr    24, sp
    lgpr    25, sp
    lgpr    26, sp    # == K0
    lgpr    27, sp    # == K1
    lgpr    28, sp    # == GP
    lgpr    29, sp    # == SP
    lgpr    30, sp    # == FP
    lgpr    31, sp    # == RA

    addi    sp, sp, mips_exception_decrement

    nop
    nop
    nop
    sync	                    # settle things down
    eret	                    # return
    nop	                        # just to be safe

Process_Exception:
    move    a0, sp                          # arg0 - HAL_SavedRegisters
    mfc0    a1, CP0_CAUSE                       # arg1 - vector index
    mfc0_delay
    addi    sp, sp, -mips_exception_decrement
    mfc0_delay
    jal     mhal_exception_handler
    nop
