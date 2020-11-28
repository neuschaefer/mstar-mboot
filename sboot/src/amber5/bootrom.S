################################################################################
#
# Copyright (c) 2006-2009 MStar Semiconductor, Inc.
# All rights reserved.
#
# Unless otherwise stipulated in writing, any and all information contained
# herein regardless in any format shall remain the sole proprietary of
# MStar Semiconductor Inc. and be kept in strict confidence
# (¡§MStar Confidential Information¡¨) by the recipient.
# Any unauthorized act including without limitation unauthorized disclosure,
# copying, use, reproduction, sale, distribution, modification, disassembling,
# reverse engineering and compiling of the contents of MStar Confidential
# Information is unlawful and strictly prohibited. MStar hereby reserves the
# rights to any and all damages, losses, costs and expenses resulting therefrom.
#
################################################################################
#include "boot.inc"
#include "Board.h"
#include "drv_miu_init.h"
#include "MIUSEL_A5_2MIU.h"
#include "ArchDefs.h"

    .text
    .set    noreorder


#-------------------------------------------------------------------------------------------------
# BOOT_InitCache
# @param  None
# @return None
# @note   Init I-cache and D-cache
#-------------------------------------------------------------------------------------------------
BOOT_InitCache:

	# Clear TagLo & TagHi
	mtc0    $0, $28
	mtc0    $0, $29

    nop
    nop

	# Config1
	mfc0    $8, $16, 1

	### INIT I-CACHE ###

	# Line Size $10
	li      $9, M_Config1IL
	and     $9, $8, $9
	srl     $9, $9, S_Config1IL
	beqz    $9, Icache_done    # no Icache
	nop
	li      $10, 2
	sll     $10, $10, $9

	# Sets per way $11
	li      $9, M_Config1IS
	and     $9, $8, $9
	srl     $9, $9, S_Config1IS
	li      $11, 64
	sll     $11, $11, $9

	# Associativity $12
	li      $9, M_Config1IA
	and     $9, $8, $9
	srl     $9, $9, S_Config1IA
	add     $12, $9, 1

	li      $14, A_KSEG0BASE
	move    $15, $11
    move    $9, $12

Icache_loop:
	# Invalidate each tag entry
	cache   Index_Store_Tag_I, 0($14)
	add     $14, $10
	sub     $15, 1
	bnez    $15, Icache_loop
	nop
	move    $15, $11
	sub     $12, 1
	bnez    $12, Icache_loop
	nop

	li      $14, 0xBFC00000
	move    $15, $11
    move    $12, $9

Icachefill_loop:
	# Fill each tag entry
	cache   Address_Fill_I, 0($14)
	add     $14, $10
	sub     $15, 1
	bnez    $15, Icachefill_loop
	nop
	move    $15, $11
	sub     $12, 1
	bnez    $12, Icachefill_loop
	nop

	li      $14, A_KSEG0BASE
	move    $15, $11
    move    $12, $9
IcacheInv_loop:
	# Invalidate each tag entry again
	cache   Index_Store_Tag_I, 0($14)
	add     $14, $10
	sub     $15, 1
	bnez    $15, IcacheInv_loop
	nop
	move    $15, $11
	sub     $12, 1
	bnez    $12, IcacheInv_loop
	nop

Icache_done:
	### INIT D-CACHE ###

	# Line Size $10
	li      $9, M_Config1DL
	and     $9, $8, $9
	srl     $9, $9, S_Config1DL
	beqz    $9, Dcache_done    # no Dcache
	nop
	li      $10, 2
	sll     $10, $10, $9

	# Sets per way $11
	li      $9, M_Config1DS
	and     $9, $8, $9
	srl     $9, $9, S_Config1DS
	li      $11, 64
	sll     $11, $11, $9

	# Associativity $12
	li      $9, M_Config1DA
	and     $9, $8, $9
	srl     $9, $9, S_Config1DA
	add     $12, $9, 1

	li      $14, A_KSEG0BASE
	move    $15, $11
    move    $9, $12

Dcache_loop:
    # Invalidate each tag entry
    cache   Index_Store_Tag_D, 0($14)
    add     $14, $10
    sub     $15, 1
    bnez    $15, Dcache_loop
    nop
    move    $15, $11
    sub     $12, 1
    bnez    $12, Dcache_loop
    nop

Dcache_done:

	# Enable cache
	mfc0    $8, $16
	and     $8, (~M_ConfigK0)
#JunyouLin remove this, got logical bug
#	li      $8, (K_CacheAttrCN)
	addi    $8, $8, (K_CacheAttrCN) #JunyouLin added
	mtc0    $8, $16


	jr      $31
	nop


/************************************************************************
 *
 *                          sys_determine_icache_linesize_flash
 *  Note :
 *  ------
 *  This routine is called also from syscon.c
 *  and must obey c calling conventions - and cannot use k0/k1
 *
 *  Description :
 *  -------------
 *  Determine ICACHE linesize
 *
 *  input : a0 = processor ID
 *
 *  Return values :
 *  ---------------
 *  v0 = ICACHE linesize in bytes
 *
 ************************************************************************/
LEAF(sys_determine_icache_linesize_flash)

	j icache_linesize_mips
	 nop

	/* Unknown CPU */
icache_linesize_zero:
	jr	ra
	 move	v0, zero

icache_linesize_mips:

	/* Read CONFIG1 register, which holds implementation data */
	MFC0_SEL_OPCODE( R_t9, R_C0_Config1, R_C0_SelConfig1 )

	/* I-cache line size */
	and	t9, M_Config1IL
	beqz	t9, icache_linesize_zero
	 nop

	srl	t9, S_Config1IL
	li	v0, 0x2
	jr	ra
	 sll	v0, t9

END(sys_determine_icache_linesize_flash)

/************************************************************************
 *
 *                          sys_determine_icache_lines_flash
 *  Note :
 *  ------
 *  This routine is called also from syscon.c
 *  and must obey c calling conventions - and cannot use k0/k1
 *
 *  Description :
 *  -------------
 *  Determine number of ICACHE lines
 *
 *  input : a0 = processor ID
 *
 *  Return values :
 *  ---------------
 *  v0 = number of ICACHE lines
 *
 ************************************************************************/
LEAF(sys_determine_icache_lines_flash)



	j icache_lines_mips
	 nop

	/* Unknown CPU */
icache_lines_zero:
	jr	ra
	 move	v0, zero

icache_lines_mips:

	/* Read CONFIG1 register, which holds implementation data */
	MFC0_SEL_OPCODE( R_t9, R_C0_Config1, R_C0_SelConfig1 )

	/* I-cache lines
	 * Calculated as associativity * sets per way
	 */
	and	t8, t9, M_Config1IA
	srl	t8, S_Config1IA
	addiu	t8, 1				/* t8 = associativity	*/

	and	t9, M_Config1IS
	srl	t9, S_Config1IS
	li	t7, 0x40
	sll	t7, t9				/* t7 = sets per way	*/

	multu	t8, t7

	jr	ra
	 mflo    v0
END(sys_determine_icache_lines_flash)

/************************************************************************
 *
 *                          sys_determine_dcache_linesize_flash
 *  Note :
 *  ------
 *  This routine is called also from syscon.c
 *  and must obey c calling conventions - and cannot use k0/k1
 *
 *  Description :
 *  -------------
 *  Determine DCACHE linesize
 *
 *  input : a0 = processor ID
 *
 *  Return values :
 *  ---------------
 *  v0 = DCACHE linesize in bytes
 *
 ************************************************************************/
LEAF(sys_determine_dcache_linesize_flash)


	j dcache_linesize_mips
	 nop

	/* Unknown CPU */
dcache_linesize_zero:
	jr	ra
	 move	v0, zero

dcache_linesize_mips:

	/* Read CONFIG1 register, which holds implementation data */
	MFC0_SEL_OPCODE( R_t9, R_C0_Config1, R_C0_SelConfig1 )

	/* D-cache line size */
	and	t9, M_Config1DL
	beqz	t9, dcache_linesize_zero
	 nop

	srl	t9, S_Config1DL
	li	v0, 0x2
	jr	ra
	 sll	v0, t9
END(sys_determine_dcache_linesize_flash)


/************************************************************************
 *
 *                          sys_determine_dcache_lines_flash
 *  Note :
 *  ------
 *  This routine is called also from syscon.c
 *  and must obey c calling conventions - and cannot use k0/k1
 *
 *  Description :
 *  -------------
 *  Determine number of DCACHE lines
 *
 *  input : a0 = processor ID
 *
 *  Return values :
 *  ---------------
 *  v0 = number of DCACHE lines
 *
 ************************************************************************/
LEAF(sys_determine_dcache_lines_flash)

	j dcache_lines_mips
	 nop

	/* Unknown CPU */
dcache_lines_zero:
	jr	ra
	 move	v0, zero

dcache_lines_mips:

	/* Read CONFIG1 register, which holds implementation data */
	MFC0_SEL_OPCODE( R_t9, R_C0_Config1, R_C0_SelConfig1 )

	/* D-cache lines
	 * Calculated as associativity * sets per way
	 */
	and	t8, t9, M_Config1DA
	srl	t8, S_Config1DA
	addiu	t8, 1				/* t8 = associativity	*/

	and	t9, M_Config1DS
	srl	t9, S_Config1DS
	li	t7, 0x40
	sll	t7, t9				/* t7 = sets per way	*/

	multu	t8, t7

	jr	ra
	 mflo    v0
END(sys_determine_dcache_lines_flash)


/************************************************************************
 *
 *                          sys_init_icache
 *  Note :
 *  ------
 *  This routine is called also from sys_cpu.c and syscon_cpu.c
 *  and must obey c calling conventions - and cannot use k0/k1
 *
 *  Description :
 *  -------------
 *  Invalidate entire ICACHE
 *
 *  Inputs : a0 = cache size (bytes)
 *           a1 = line size  (bytes)
 *
 *  Return values :
 *  ---------------
 *  None
 *
 ************************************************************************/
LEAF( sys_init_icache )

	beq   a0, zero, 9f		 /* just in case cache size = 0 */
	 nop

	/* default: Clear TagHi/TagLo */

	/* Note: ITagHi/Lo == TagHi/Lo, so we can use common code */
init_icache_itaghilo:
init_icache_taghilo:
	MTC0( zero, C0_TagHi )
init_icache_itaglo:
init_icache_taglo:
	MTC0( zero, C0_TagLo )

0:
	/* Calc an address that will correspond to the first cache line */
#	li	a2, KSEG0BASE
	li	a2, KSEG1BASE


	/* Calc an address that will correspond to the last cache line  */
	addu	a3, a2, a0
	subu    a3, a1

	/* Loop through all lines, invalidating each of them */
1:
SET_MIPS3()
	cache	ICACHE_INDEX_STORE_TAG, 0(a2)	/* clear tag */
SET_MIPS0()
	bne	a2, a3, 1b
	 addu	a2, a1

9:
	jr	ra
	nop


END( sys_init_icache )


/************************************************************************
 *
 *                          sys_init_dcache
 *  Note :
 *  ------
 *  This routine is called also from sys_cpu.c
 *  and must obey c calling conventions - and cannot use k0/k1
 *
 *  Description :
 *  -------------
 *  Invalidate entire DCACHE
 *
 *  Inputs : a0 = cache size (bytes)
 *           a1 = line size  (bytes)
 *           a2 = processor ID
 *
 *  Return values :
 *  ---------------
 *  None
 *
 ************************************************************************/
LEAF( sys_init_dcache )

	/* default: Clear TagHi/TagLo */
init_dcache_taghilo:
	MTC0( zero, C0_TagHi )
init_dcache_taglo:
	MTC0( zero, C0_TagLo )

#	b	0f
#	 nop

init_dcache_dtaghilo:
	MTC0_SEL_OPCODE( R_zero, R_C0_DTagHi, R_C0_SelDTagHi )
init_dcache_dtaglo:
	MTC0_SEL_OPCODE( R_zero, R_C0_DTagLo, R_C0_SelDTagLo )

0:
	/* Calc an address that will correspond to the first cache line */
#	li	a2, KSEG0BASE
	li	a2, KSEG1BASE

	/* Calc an address that will correspond to the last cache line  */
	addu	a3, a2, a0
	subu    a3, a1

	/* Loop through all lines, invalidating each of them */
1:
SET_MIPS3()
	cache	DCACHE_INDEX_STORE_TAG, 0(a2)	/* clear tag */
SET_MIPS0()
	bne	a2, a3, 1b
	 addu	a2, a1

9:
	jr	ra
	 nop

END( sys_init_dcache )


/************************************************************************
 *
 *                          sys_init_cache
 *  Description :
 *  -------------
 *
 *  Invalidate I and D caches
 *
 *  input : k1 = processor ID
 *
 *  Return values :
 *  ---------------
 *
 *  Always 0
 *
 ************************************************************************/

LEAF(sys_init_cache)

	/**** Determine cache settings ****/

	/* This code was linked cached, but is running uncached since
	 * caches have not been initialised yet.
	 */

#define RA			t4
#define l2cache_size		t1
#define l2cache_linesize	t0
#define icache_size		t3
#define icache_linesize		t2
#define dcache_size		t1
#define dcache_linesize		t0

	move	RA, ra

	move	a0, k1

	/*
	 * MIPSCMP
	 * if v1!=0 this is a secondary CPU,
	 * so don't initialise secondary cache again

	bnez	v1, 1f
	nop
	 */


	/*
	 * MIPSCMP
	 * by definition only CPU 0 initialises the L2 cache, so
	 * reset the value of v1
	 */
	move	v1, zero

1:
	/* L1 cache */

	bal	sys_determine_icache_linesize_flash
	nop
	move	icache_linesize, v0

	bal	sys_determine_icache_lines_flash
	nop
	multu	icache_linesize, v0
	mflo	icache_size

	bal	sys_determine_dcache_linesize_flash
	nop
	move	dcache_linesize, v0

	bal	sys_determine_dcache_lines_flash
	nop
	multu	dcache_linesize, v0
	mflo	dcache_size

	beq	icache_size, zero, 1f
	nop
	beq	dcache_size, zero, 1f
	nop

	/* Initialise instruction cache */
	move	a0, icache_size
	move	a1, icache_linesize
	bal	    sys_init_icache
	 move	a2, k1

	/* Initialise data cache */
	move	a0, dcache_size
	move	a1, dcache_linesize
	bal	    sys_init_dcache
	 move	a2, k1


	MFC0(   v0, C0_Config )
	and	v0, ~M_ConfigK0
	or	v0, K_CacheAttrCN
	MTC0(   v0, C0_Config )


	/* Done */
	jr	RA
	move	v0, zero

	/* D-cache or I-cache has size 0,  set CPU uncached */
1:
	MFC0(   v0, C0_Config )
	and	v0, ~M_ConfigK0
	or	v0, K_CacheAttrU
	MTC0(   v0, C0_Config )

	/* Done */
	jr	RA
	move	v0, zero

END(sys_init_cache)

#-------------------------------------------------------------------------------------------------
# BootInitL2Cache
# @param  None
# @return None
# @note   L2 cache initialization for Amber2(the same of Janus 2)
#-------------------------------------------------------------------------------------------------
LEAF(BootInitL2Cache)
.if (ENABLE_MSTAR_MIU_HIGHWAY_ENABLE)
# H41 BIT9=1 (reg_miu_access_mode)

    lw      t0, 0xBF203104
    or      t0, t0, (1 << 9)
    sw      t0, 0xBF203104

   # H7C MIU HIGHWAY Setting    --> confirm with MIU HW designer
    lui     t0, 0xBF2025F0 >> 16
    lw      t1, (0xBF2025F0 & 0xFFFF)(t0)
    or      t1, (1<<6)
    or      t1, (1<<11)
    sw      t1, (0xBF2025F0 & 0xFFFF)(t0)

   # H7D                        --> confirm with MIU HW designer
    lui     t0, 0xBF2025F4 >> 16
    lw      t1, (0xBF2025F4 & 0x0000)(t0)
    or      t1, (1<<3)    # limit = 8
    sw      t1, (0xBF2025F4 & 0xFFFF)(t0)
.endif

.if (ENABLE_MSTAR_CPU_PREFETCH_ENABLE)
    # A5 U03/U04 cpu prefetch enable auto detection
    RREG    $4, (REG_ADDR_BASE + (0x001e02 <<1 ))
    andi    $4, $4, 0xFF00
    srl     $4, $4, 8
    bltu    $4, 3, U03_chip_cpu_prefetch_bypass
    nop

    # H40 BIT7 = 1 (reg_pfet_buf_en)
    lui     t0, 0xBF203100 >> 16
    lw      t1, (0xBF203100 & 0xFFFF)(t0)
    or      t1, (1<<7)
    sw      t1, (0xBF203100 & 0xFFFF)(t0)

.if(ENABLE_MSTAR_TITANIA_PREFETCH_LINE_32_BYTES)
    # H40 BIT8 = 0 (reg_pfet_buf_size)
    lui     t0, 0xBF203100 >> 16
    lw      t1, (0xBF203100 & 0xFFFF)(t0)
    and     t1, ~(1<<8)
    sw      t1, (0xBF203100 & 0xFFFF)(t0)
.endif

.if(ENABLE_MSTAR_TITANIA_PREFETCH_LINE_64_BYTES)
    # H40 BIT8 = 1 (reg_pfet_buf_size)
    lui     t0, 0xBF203100 >> 16
    lw      t1, (0xBF203100 & 0xFFFF)(t0)
    or      t1, (1<<8)
    sw      t1, (0xBF203100 & 0xFFFF)(t0)
.endif

U03_chip_cpu_prefetch_bypass:
.endif


.if (ENABLE_MSTAR_TITANIA_L2_CACHE_WRITE_THROUGH)
    # H40 BIT15=1 L2 write through
    lui     t0, 0xBF203100 >> 16
    lw      t1, (0xBF203100 & 0xFFFF)(t0)
    or      t1, (1<<15)
    sw      t1, (0xBF203100 & 0xFFFF)(t0)
.endif

.if (ENABLE_MSTAR_FORCE_REQUEST_INTO_CACHE)
    # H40 BIT2 = 1 (L2 Force all miu request are cacheable)
    lui     t0, 0xBF203100 >> 16
    lw      t1, (0xBF203100 & 0xFFFF)(t0)
    or      t1, (1<<2)
    sw      t1, (0xBF203100 & 0xFFFF)(t0)
.endif

# L2 cache size = 256KB
.if (ENABLE_MSTAR_TITANIA_L2_CACHE_LINE_128_BYTES)
    lui     t0, 0xBF203100 >> 16
    lw      t1, (0xBF203100 & 0xFFFF)(t0)
    or      t1, (1<<5)
    sw      t1, (0xBF203100 & 0xFFFF)(t0)
.endif
.if (ENABLE_MSTAR_TITANIA_L2_CACHE_LINE_64_BYTES)
    lui     t0, 0xBF203100 >> 16
    lw      t1, (0xBF203100 & 0xFFFF)(t0)
    and     t1, ~(1<<5)
    sw      t1, (0xBF203100 & 0xFFFF)(t0)
.endif

    # H41 BIT11 = 1 (reg_rreq_mode)
    lui     t0, 0xBF203104 >> 16
    lw      t1, (0xBF203104 & 0xFFFF)(t0)
    or      t1, (1<<11)
    sw      t1, (0xBF203104 & 0xFFFF)(t0)

    # H5D BIT1 = 1 (reg_ocp2miu_status_switch)
    lui     t0, 0xBF203174 >> 16
    lw      t1, (0xBF203174 & 0xFFFF)(t0)
    or      t1, (1<<1)
    sw      t1, (0xBF203174 & 0xFFFF)(t0)

    # H41 BIT4 = 1 (reg_cache_op_fire = 1 -> 0)
    lui     t0, 0xBF203104 >> 16
    lw      t1, (0xBF203104 & 0xFFFF)(t0)
    or      t1, (1<<4)
    sw      t1, (0xBF203104 & 0xFFFF)(t0)
1:
    # check H41 BIT8 = 1 (reg_l2_cache_active = 1)
    lw      t1, (0xBF203104 & 0xFFFF)(t0)
    and     t1, (1<<8)
    beq     t1, zero, 1b
    lw      t1, (0xBF203104 & 0xFFFF)(t0)
    and     t1, ~(1<<4)
    sw      t1, (0xBF203104 & 0xFFFF)(t0)

    # H40 BIT1 = 0 (L2 cache enable)
    lui     t0, 0xBF203100 >> 16
    lw      t1, (0xBF203100 & 0xFFFF)(t0)
    and     t1, ~(1<<1)
    sw      t1, (0xBF203100 & 0xFFFF)(t0)

    # clear MIU request count (H58 BIT0)
    lui     t0, 0xBF203160 >> 16
    lw      t1, (0xBF203160 & 0xFFFF)(t0)
    and     t1, ~(1<<0)
    sw      t1, (0xBF203160 & 0xFFFF)(t0)



.if (ENABLE_MSTAR_MEMORY_PREFETCH_ENABLE)
    # A5 U03/U04 memory prefetch enable auto detection
    RREG    $4, (REG_ADDR_BASE + (0x001e02 <<1 ))
    andi    $4, $4, 0xFF00
    srl     $4, $4, 8
    bltu    $4, 3, U03_chip_memory_prefetch_bypass
    nop

	# H41 BIT12 = 1 (reg_mfet_enable)
    lw          t1, 0xBF203104
    or          t1, t1, 0x0F                    #//0x101841[3:0]: Cache Operation Mode: 0x0F: Memory Prefetch Mode
    sw          t1, 0xBF203104

    lui         t0, 0xBF203104 >> 16
    lw          t1, (0xBF203104 & 0xFFFF)(t0)
    or          t1, (1<<11)
    or          t1, (1<<12)
    or          t1, (1<<13)
    sw          t1, (0xBF203104 & 0xFFFF)(t0)

    lw          t1, 0xBF203104
    or          t1, t1, 0x10                    #//0x101841[4]: Start to cache operation
    sw          t1, 0xBF203104

U03_chip_memory_prefetch_bypass:
.endif

    jr      $31
    nop
END(BootInitL2Cache)

#-------------------------------------------------------------------------------------------------
# turn_on_frc_power
# @param  None
# @return None
# @note   CP1 FPU initialization
#-------------------------------------------------------------------------------------------------
turn_on_frc_power:
    WREG    0xBF203C70, 0x0000
    WREG    0xBF221804, 0x0000
    WREG    0xBF2066C0, 0x0000
    WREG    0xBF221904, 0x0200
    WREG    0xBF20174C, 0x000C
    WREG    0xBF2066C4, 0x0000
    WREG    0xBF201764, 0x0000
    WREG    0xBF2066E8, 0x0000
    WREG    0xBF20781C, 0x0002
    jr      $31
    nop
#-------------------------------------------------------------------------------------------------
# sys_init_fpu
# @param  None
# @return None
# @note   CP1 FPU initialization
#-------------------------------------------------------------------------------------------------
sys_init_fpu:

    # check FP = 1
    MFC0(   t1, C0_Config1 )
    and     t1, (1<<0)
    beq     t1, $0, 1f

    # set CU1 = 1 and FR = 1
    MFC0(   t0, C0_Status  )
    or      t0, (1<<29) #CU1 = 1
    or      t0, (1<<26) #FR = 1
    MTC0(   t0, C0_Status  )

    # set FS = 1
    li      t0, (1<<24) #set FS (flush to zero) bit
    CTC1(   t0, C1_FCSR    )

    # check FIR != 0
    CFC1(   t0, C1_FIR     )
    beq     t0, $0, 1f
    nop
    nop
    nop
1:
    jr      $31
    nop

#-------------------------------------------------------------------------------------------------
# enable_riu32_bitmask
# @param  None
# @return None
# @note   RIU bitmask
#-------------------------------------------------------------------------------------------------
enable_riu32_bitmask:

.if(ENABLE_MSTAR_32BIT_RIU_MASK_ENABLE)
    lui     t0, 0xBF20025C >> 16
    lw      t1, (0xBF20025C & 0xFFFF)(t0)
    or      t1, (1<<0)
    sw      t1, (0xBF20025C & 0xFFFF)(t0)

    lui     t0, 0xBF203104 >> 16
    lw      t1, (0xBF203104 & 0xFFFF)(t0)
    or      t1, (1<<15)
    sw      t1, (0xBF203104 & 0xFFFF)(t0)

    lui     t0, 0xBF00025C >> 16
    lw      t1, (0xBF00025C & 0xFFFF)(t0)
    or      t1, (1<<0)
    sw      t1, (0xBF00025C & 0xFFFF)(t0)
.endif
    jr      $31
    nop
#-------------------------------------------------------------------------------------------------
# BOOT_Entry:
# @param  None
# @return None
# @note   Entry point of Boot code
#-------------------------------------------------------------------------------------------------
    .globl  BOOTROM_Entry
BOOTROM_Entry:

    bal     bond_clk_sel
    nop

.if(IS_FPGA == 0)
.if(SIMULATION == 0)
    # Configure PAD top for MUX and GPIO (e.g. DDR power)
    lui     $4,%hi(padInitTbl+10)
    bal     MDrv_WriteRegMaskTbl
    ori     $4,%lo(padInitTbl+10)
.else
    WREG    0xBF203D40, 0x0000  # disable all pad in
.endif
.endif

    DBGREG  0x0002
    # Enable MSTV_TOOL to access MIU
    bal     BOOT_EnableAccessMIU
    nop

    # Enable external sync
    bal BOOT_EnableExternalizeSync
    nop

    DBGREG  0x0003

    # Power On Sequence
    bal     BOOT_PowerOnSeq
    nop

    DBGREG  0x0007

#if 0
.if (ENABLE_MSTAR_TLB_SHARE_ENABLE)
    # Enable TLB Share
    bal     BOOT_EnableTLBShare
    nop
.endif
#endif

.if (EMMC_BOOT == 1)
    # Copy chunk header from EMMC boot partition to DRAM
    bal     BOOT_CopyHeader_EMMC
    nop
    # Copy uboot binary from EMMC boot partition to DRAM
    bal     BOOT_CopyUboot_EMMC
    nop
.else
    # Copy bootram from ROM to DRAM
    bal     BOOT_CopyBootRAM
    nop
.endif

.if(IS_FPGA == 1)
    PUTK 'O'
    PUTK 'T'
    PUTK '_'
    PUTK 'F'
    PUTK 'P'
    PUTK 'G'
    PUTK 'A'
.endif

    DBGREG  0x0008

.if (EMMC_BOOT == 1)
    WREG    0xBF201644, 0x0000
    WREG    0xBF201644, 0x8000      //clk_mips switch to reg_ckg_mips
    move    $31, $14                   #0x875F0600        #Jump to Uboot entry
    j       $31
    nop
.else

    # Jump to BootRam_Entry
    la      $31, BOOTRAM_Entry
    j       $31
    nop
.endif

#-------------------------------------------------------------------------------------------------
# bond_clk_sel
# @param  None
# @return None
# @note   XTAL setting
#-------------------------------------------------------------------------------------------------
bond_clk_sel:
    move    $27, $31

    RREG   $4 , (REG_ADDR_BASE + (0x001e02 <<1 ))
    andi   $4 , $4, 0xFF00
    beqz   $4 , u01_setting
    nop
    WREG    0xBF001C78, 0x87A3
    WREG    0xBF001C74, 0x0003
    j       end_clk_sel
    nop

u01_setting:
    WREG    0xBF001C78, 0x87A3
    WREG    0xBF001C74, 0x0001

end_clk_sel:

    move    $31, $27
    jr      $31
    nop

#-------------------------------------------------------------------------------------------------
# BOOT_PowerOnSeq
# @param  None
# @return None
# @note   Power On Sequence for Chip
#-------------------------------------------------------------------------------------------------
BOOT_PowerOnSeq:
    move    $27, $31

.if(IS_FPGA == 0)
    bal     BOOTROM_MPLL_INIT
    nop

    DBGREG  0x0010

    bal     BOOTROM_OCP_CLK_RATIO
    nop

    bal     BOOTROM_CLK_GEN0_DVBT_INIT
    nop

.endif

    DBGREG  0x0011

    DELAYUS  100
    # Init UART
.if(IS_FPGA == 1)
    bal     BOOT_InitUART_FPGA
    PUTK '\r'
    PUTK 'U'
    PUTK 'A'
    PUTK 'R'
    PUTK 'T'
    PUTK '_'
    PUTK '3'
    PUTK '8'
    PUTK '4'
    PUTK '0'
    PUTK '0'

    PUTK '\r'
    PUTK '\n'
.else
    bal     BOOT_InitUART
	
.endif
    nop

# checkpoint for autotest boottime, plz dont remove it
    DPUTK '['
    DPUTK 'A'
    DPUTK 'T'
    DPUTK ']'
    DPUTK '['
    DPUTK 'M'
    DPUTK 'B'
    DPUTK ']'
    DPUTK '['
    DPUTK 's'
    DPUTK 't'
    DPUTK 'a'
    DPUTK 'r'
    DPUTK 't'
    DPUTK ' '
    DPUTK 's'
    DPUTK 'b'
    DPUTK ']'
    DPUTK '['
    DPUTK '0'
    DPUTK ']'
	
    DBGREG  0x0012

.if (SIMULATION == 1)
RTL_END:
    j   RTL_END
.endif

    bal     sys_init_cache //disable L1 cache for A5 bring up
    nop

    DBGREG  0x0013

.if (ENABLE_MSTAR_L2_CACHE_ENABLE)
    #//NOTICE:
    #//Due to MIU1 timing issue, please disable MIU clock before cache initial flow
    RREG      t9, (0xBF000000 + (0x100B3A << 1))        #//Disable CLK_MIU
    or        t9, t9, 0x0100
    REG_C2M   t9, (0xBF000000 + (0x100B3A << 1))

    bal     BootInitL2Cache
    nop

    RREG      t9, (0xBF000000 + (0x100B3A << 1))        #//Enable CLK_MIU
    and       t9, t9, 0xFEFF
    REG_C2M   t9, (0xBF000000 + (0x100B3A << 1))

    .if (BOOTING_FROM_EXT_SPI_WITH_PM51 == 1)
        WREG    (REG_ADDR_BASE + (0x1012a6 <<1 )) , 0x0000   #Unmask MIU0_group_3
        WREG    (REG_ADDR_BASE + (0x1006a6 <<1 )) , 0x0000   #Unmask MIU1_group_3
    .endif
.endif

#Enable L2 status probe
    lui     t0, 0xBF203174 >> 16
    lw      t1, (0xBF203174 & 0xFFFF)(t0)
    or      t1, (1<<1)
    sw      t1, (0xBF203174 & 0xFFFF)(t0)

    DBGREG  0x0014

.if(IS_FPGA == 1)
    bal     BOOT_InitDRAM
    PUTK '\r'
    PUTK 'B'
    PUTK 'O'
.else
    .if (BOOTING_FROM_EXT_SPI_WITH_PM51 != 1)
    bal     BOOTROM_MIU_INIT
    .endif
.endif
    nop

    DBGREG  0x0015

    bal     sys_init_fpu
    nop

    bal     turn_on_frc_power
    nop

.if(IS_FPGA == 0)
    bal     enable_riu32_bitmask
    nop
.endif

    DBGREG  0x0016

.if(IS_FPGA == 0) // check with HW designer , support burst read in SPI
.if 1
	/* Caches have now been initialised, so shift to kseg0 */
	la	t0, 1f
	KSEG0A( t0)
	j	t0
	nop
1:
.endif
.endif

    DBGREG  0x0017

.if(EMMC_BOOT == 0)
.if(IS_FPGA == 0)
    bal     SPI_CLK
    nop

    bal     SPI_ChangeCLK
    nop
.endif
.endif

    DBGREG  0x0018

    move    $31, $27
    jr      $31
    nop

#-------------------------------------------------------------------------------------------------
# BOOT_EnableTLBShare
# @param  None
# @return None
# @note   Enable TLB Share
#-------------------------------------------------------------------------------------------------
BOOT_EnableTLBShare:
    li      $8, 0x00000002   # raise MVPCONTROL_VPC
    mtc0    $8, $0, 1
    li      $8, 0x00000006   # raise MVPCONTROL_VPC | MVPCONTROL_STLB
    mtc0    $8, $0, 1
    li      $8, 0x00000004   # clear MVPCONTROL_VPC
    mtc0    $8, $0, 1
    jr      $31
    nop

#-------------------------------------------------------------------------------------------------
# SPI_CLK SPI Clock init
# @param  None
# @return None
# @note   do SPI Clock init
#-------------------------------------------------------------------------------------------------
SPI_CLK:

    WREG_B 0xBF0011C4 , 0xFF #0x0f:cz_high/0x0f:cz_setup/0x0f:cz_hold time set up
    WREG_B 0xBF0011C5 , 0x0F
    WREG_B 0xBF0011C8 , 0x01 #Enable fast read mode, let isp run up to 86Mhz

    jr      $31
    nop

#-------------------------------------------------------------------------------------------------
# SPI_ChangeCLK
# @param  None
# @return None
# @note   change SPI clock
#-------------------------------------------------------------------------------------------------
SPI_ChangeCLK:

    WREG_B 0xBF001C81 , 0x04 #step 1/2:set SPI clkgen to 54M
    WREG_B 0xBF001C81 , 0x44 #step 2/2:release SPI_clk from XTAL to clock gen (above line)
	WREG_B 0xBF001C80 , 0x80 #Set clock of MCU to 170MHz

    jr      $31
    nop

#-------------------------------------------------------------------------------------------------
# BOOTROM_OCP_CLK_RATIO
# @param  None
# @return None
# @note   do MIPS OCP clock ratio setting
#-------------------------------------------------------------------------------------------------
BOOTROM_OCP_CLK_RATIO:

    WREG_B  0xBF203A3C, 0x40
    WREG_B  0xBF203A3C, 0x41

    WREG_B  0xBF203A3C, 0x40
    DELAYUS 20000
    WREG_B  0xBF203A3C, 0x41        //clk_mips:clk_ocp = 1:3 for bring up
    DELAYUS 20000

    //WREG_B  0xBF203A3C, 0x00        //clk_mips:clk_ocp = 1:1
    // DELAYUS     20000
    //WREG_B  0xBF203A3C, 0x01        //clk_mips:clk_ocp = 1:1
    // DELAYUS     20000

    //WREG_B  0xBF203A3C, 0x20        //clk_mips:clk_ocp = 1:2
    // DELAYUS     20000
    //WREG_B  0xBF203A3C, 0x21        //clk_mips:clk_ocp = 1:2
    // DELAYUS     20000

    //WREG_B  0xBF203A3C, 0x50        //clk_mips:clk_ocp = 1:4
    // DELAYUS     20000
    //WREG_B  0xBF203A3C, 0x51        //clk_mips:clk_ocp = 1:4
    // DELAYUS     20000

    //WREG_B  0xBF203A3C, 0x70        //clk_mips:clk_ocp = 1:5
    // DELAYUS     20000
    //WREG_B  0xBF203A3C, 0x71        //clk_mips:clk_ocp = 1:5
    // DELAYUS     20000

.if (EMMC_BOOT == 0)
    WREG    0xBF201644, 0x0000
    WREG    0xBF201644, 0x8000      //clk_mips switch to reg_ckg_mips
.endif
    jr      $31
    nop

#-------------------------------------------------------------------------------------------------
# BOOTROM_CLK_GEN0_DVBT_INIT
# @param  None
# @return None
# @note   do CLK_GEN0 init
#-------------------------------------------------------------------------------------------------
BOOTROM_CLK_GEN0_DVBT_INIT:
//CLKGEN0

.if (BOOTING_FROM_EXT_SPI_WITH_PM51 != 1)
    WREG    0xBF201640, 0x0000
    WREG    0xBF201640, 0x0001  // reg_ckg_mcu=216MHz
.endif

    WREG    0xBF20164C, 0x0C00  // reg_ckg_uart0=123MHz
    WREG    0xBF201650, 0x000C  // reg_ckg_uart1=123MHz

.if (BOOTING_FROM_EXT_SPI_WITH_PM51 != 1)
   WREG    0xBF201658, 0x0044  // reg_clk_spi=54MHz
.endif

    WREG    0xBF201668, 0x0000  // reg_ckg_pcm=27MHz

.if (BOOTING_FROM_EXT_SPI_WITH_PM51 != 1)
    WREG    0xBF201670, 0x0100  // reg_ckg_mpll_syn=432MHz
.if (ENABLE_MSTAR_MIU_HIGHWAY_ENABLE)
    WREG    0xBF201674, 0x1000  // reg_ckg_miu = select HEMCU fast way
.else
    //WREG    0xBF201674, 0x0808  // reg_ckg_miu
.endif
   WREG    0xBF201678, 0x0000  // reg_ckg_miu_rec=XTAL div 8
.endif

    WREG    0xBF2016A8, 0x1101  // reg_ckg_tsp and stc0/stc1 = disable clk
    WREG    0xBF201700, 0x0000  // reg_ckg_gopg0/gopg1=odlck
    WREG    0xBF201704, 0x0400  // reg_ckg_gopg2/gopd=odclk
    WREG    0xBF201708, 0x0000  // reg_ckg_gopg3=odclk
    WREG    0xBF20170C, 0x0000  // reg_ckg_psram0/1 clock on
    WREG    0xBF201720, 0x0000  // reg_clk_ge=216MHz
    WREG    0xBF201780, 0x0400  // reg_ckg_emac_rx and reg_ckg_emac_ahb = 123MHz
    WREG    0xBF201784, 0x0004  // reg_ckg_emac_tx_ref,reg_ckg_emac_tx
    WREG    0xBF201788, 0x0000  // reg_ckg_emac_rx_ref
    WREG    0xBF201790, 0x0014  // reg_ckg_nfie=40MHz
    WREG    0xBF201798, 0x000C  // reg_ckg_onif=54MHz
    WREG    0xBF2017A0, 0x001C  // reg_ckg_mpif=13.5MHz

//CLKGEN1
    WREG    0xBF20663C, 0x0010  // reg_ckg_dmdmcu=108MHz
    WREG    0xBF206670, 0x0004  // reg_ckg_disp_ipath=80MHz

    jr      $31
    nop

#-------------------------------------------------------------------------------------------------
# BOOT_InitDRAM
# @param  None
# @return None
# @note   Initial DRAM
#-------------------------------------------------------------------------------------------------
BOOT_InitDRAM:

    # XD2MIU init setting
    WREG   0xBF005788 , 0x0004
    WREG   0xBF00578C , 0x3c11
    WREG   0xBF005790 , 0x0010
    WREG   0xBF005794 , 0x403c
    WREG   0xBF005798 , 0x0101

    # disable MIU random model
    WREG   0xBF202454 , 0xC000
    WREG   0xBF2025FC , 0xFF00

    #T4 trigger MIU init
    WREG 0xBF202404  0x0000
    WREG 0xBF202404  0x0858 #support 128MB size
    WREG 0xBF202408  0x0185
    WREG 0xBF20240C  0x0120
    WREG 0xBF202410  0x0833
    WREG 0xBF202414  0x0c33
    WREG 0xBF202418  0x7111
    WREG 0xBF20241C  0x100e
    WREG 0xBF202420  0x0031


    WREG 0xBF20243C  0x0C01
    WREG 0xBF20243C  0x0C00
    WREG 0xBF202400  0x0008
    WREG 0xBF202400  0x000c

    DELAYUS 100


    WREG 0xBF202400 0x000e
    DELAYUS 100


    WREG 0xBF202400 0x001f
    DELAYUS 100

    WREG 0xBF20243C 0x0C08

    jr      $31
    nop

#-------------------------------------------------------------------------------------------------
# BOOTROM_MIU_INIT
# @param  None
# @return None
# @note   do MIU init
#-------------------------------------------------------------------------------------------------
BOOTROM_MIU_INIT:
    move    $15,$31
    WREG    0xBF201674, 0x0808
    DBGREG  0x0020

    # MIU0 Software reset
    WREG    (REG_ADDR_BASE + (0x10121e <<1 )) , 0x0000   #hold miu_0
    WREG    (REG_ADDR_BASE + (0x10121e <<1 )) , 0x0c01   #miu_sw_rst
    WREG    (REG_ADDR_BASE + (0x10121e <<1 )) , 0x0c00   #
    WREG    (REG_ADDR_BASE + (0x101202 <<1 )) , 0x0000   #disable all ddr bus out

    # MIU0 Request mask
    WREG    (REG_ADDR_BASE + (0x101246 <<1 )) , 0x7FFE   # mask group0
    WREG    (REG_ADDR_BASE + (0x101266 <<1 )) , 0xFFFF   # mask group1
    WREG    (REG_ADDR_BASE + (0x101286 <<1 )) , 0xFFFF   # mask group2
    WREG    (REG_ADDR_BASE + (0x1012A6 <<1 )) , 0xFFFF   # mask group3

.if ( ENABLE_MIU1 == 1 )
    # MIU1 Software reset
    WREG    (REG_ADDR_BASE + (0x10061e <<1 )) , 0x0000   #hold miu_0
    WREG    (REG_ADDR_BASE + (0x10061e <<1 )) , 0x0c01   #
    WREG    (REG_ADDR_BASE + (0x10061e <<1 )) , 0x0c00   #
    WREG    (REG_ADDR_BASE + (0x100602 <<1 )) , 0x0000   #

    # MIU1 Request mask
    WREG    (REG_ADDR_BASE + (0x100646 <<1 )) , 0x7FFE   # mask group0
    WREG    (REG_ADDR_BASE + (0x100666 <<1 )) , 0xFFFF   # mask group1
    WREG    (REG_ADDR_BASE + (0x100686 <<1 )) , 0xFFFF   # mask group2
    WREG    (REG_ADDR_BASE + (0x1006A6 <<1 )) , 0xFFFF   # mask group3
.endif

# MIU code base  = MIU0_16 , MIU1_16
    #if(ENABLE_MEM1600MHz)
    WREG    (REG_ADDR_BASE + (0x110d36 <<1 )) , 0x4005   # reg_DDRPLL_LOOP_DIV_FIRST	: [15:14]	divide by 4
    WREG    (REG_ADDR_BASE + (0x110d34 <<1 )) , 0x0300   # reg_DDRPLL_LOOP_DIV_SECOND	: [15:14]	divide by 3
    WREG    (REG_ADDR_BASE + (0x110d30 <<1 )) , 0xeb85   # set pll to 780 MHz
    WREG    (REG_ADDR_BASE + (0x110d32 <<1 )) , 0x0019
    #endif
    #if(ENABLE_MEM1300MHz)
    WREG    (REG_ADDR_BASE + (0x110d36 <<1 )) , 0x4000   # reg_DDRPLL_LOOP_DIV_FIRST	: [15:14]	divide by 4
    WREG    (REG_ADDR_BASE + (0x110d34 <<1 )) , 0x0300   # reg_DDRPLL_LOOP_DIV_SECOND	: [15:14]	divide by 3
    WREG    (REG_ADDR_BASE + (0x110d30 <<1 )) , 0xe6cb   # set pll to 780 MHz
    WREG    (REG_ADDR_BASE + (0x110d32 <<1 )) , 0x001f
    #endif
    #if(ENABLE_MSTAR_TITANIA_BD_MST016B_10AA5_11165)
    WREG    (REG_ADDR_BASE + (0x110d36 <<1 )) , 0x4003
    #endif
    # Avoid DDRPLL unknown(MCLK05X & MCLK025X) by resset ddrat[28]
    WREG    (REG_ADDR_BASE + (0x110d24 <<1 )) , 0x1000

.if ( ENABLE_MIU1 == 1 )
    #if(ENABLE_MEM1600MHz)
    WREG    (REG_ADDR_BASE + (0x110db6 <<1 )) , 0x4000   # reg_DDRPLL_LOOP_DIV_FIRST    : [15:14]   divide by 4
    WREG    (REG_ADDR_BASE + (0x110db4 <<1 )) , 0x0300   # reg_DDRPLL_LOOP_DIV_SECOND   : [15:14]   divide by 3
    WREG    (REG_ADDR_BASE + (0x110db0 <<1 )) , 0xeb85   # set pll to 780 MHz
    WREG    (REG_ADDR_BASE + (0x110db2 <<1 )) , 0x0019
    #endif
    #if(ENABLE_MEM1300MHz)
    WREG    (REG_ADDR_BASE + (0x110db6 <<1 )) , 0x4000   # reg_DDRPLL_LOOP_DIV_FIRST    : [15:14]   divide by 4
    WREG    (REG_ADDR_BASE + (0x110db4 <<1 )) , 0x0300   # reg_DDRPLL_LOOP_DIV_SECOND   : [15:14]   divide by 3
    WREG    (REG_ADDR_BASE + (0x110db0 <<1 )) , 0xe6cb   # set pll to 780 MHz
    WREG    (REG_ADDR_BASE + (0x110db2 <<1 )) , 0x001f
    #endif
    # Avoid DDRPLL unknown(MCLK05X & MCLK025X) by resset ddrat[28]
    WREG    (REG_ADDR_BASE + (0x110da4 <<1 )) , 0x1000
.endif

    DELAYUS 5000    # delay 5ms

    WREG    (REG_ADDR_BASE + (0x110d24 <<1 )) , 0x0000
.if ( ENABLE_MIU1 == 1 )
    WREG    (REG_ADDR_BASE + (0x110da4 <<1 )) , 0x0000
.endif

    lui     $4,%hi(MIU0_DDR_Init)
    bal     MDrv_WriteRegTbl32
    ori     $4,%lo(MIU0_DDR_Init)

    DBGREG  0x0021

    RREG   $4 , (REG_ADDR_BASE + (0x001e02 <<1 ))
    andi   $4 , $4, 0xFF00
    beqz   $4 , MIU_SW_RST
    nop
    RREG   $4 , (REG_ADDR_BASE + (0x101228 <<1 ))
    ori    $4 , $4, 0x4000
    lui    $8 , (REG_ADDR_BASE + (0x101228 <<1 )) >> 16
    sw     $4,  ((REG_ADDR_BASE + (0x101228 <<1 )) & 0xFFFF)($8)

MIU_SW_RST:
    DELAYUS 1000    # delay 1ms

    WREG    (REG_ADDR_BASE + (0x10121e <<1 )) , 0x0c01   #miu_sw_rst
    WREG    (REG_ADDR_BASE + (0x10121e <<1 )) , 0x0c08

    DELAYUS 1    # delay 1us

    #if(ENABLE_MEM1600MHz)
    WREG    (REG_ADDR_BASE + (0x110d00 <<1 )) , 0x0a01   #reg_pkg_sel      1   : [0]
    #endif
    #if(ENABLE_MEM1300MHz)
    WREG    (REG_ADDR_BASE + (0x110d00 <<1 )) , 0x0201   #reg_pkg_sel      1   : [0]
    #endif
    WREG    (REG_ADDR_BASE + (0x110d02 <<1 )) , 0xaaaa   #reg_cko_state        cc  : [7:0]

.if ( ENABLE_MIU1 == 1 )
    lui     $4,%hi(MIU1_DDR_Init)
    bal     MDrv_WriteRegTbl32
    ori     $4,%lo(MIU1_DDR_Init)

    DELAYUS 1000    # delay 1ms

    WREG    (REG_ADDR_BASE + (0x10061e <<1 )) , 0x0c01   #miu_sw_rst
    WREG    (REG_ADDR_BASE + (0x10061e <<1 )) , 0x0c08

    DELAYUS 1    # delay 1us

    #if(ENABLE_MEM1600MHz)
    WREG    (REG_ADDR_BASE + (0x110d80 <<1 )) , 0x0201   #reg_pkg_sel      1   : [0]
    #endif
    #if(ENABLE_MEM1300MHz)
    WREG    (REG_ADDR_BASE + (0x110d80 <<1 )) , 0x0201   #reg_pkg_sel      1   : [0]
    #endif
    WREG    (REG_ADDR_BASE + (0x110d82 <<1 )) , 0xaaaa   #reg_cko_state        cc  : [7:0]
.endif

    DELAYUS  100	# delay 100us

#if (MIU_CONFIG == DDR3_MIU0_32_MIU1_16_By_8BIT)
    WREG    (REG_ADDR_BASE + (0x110d08 <<1 )) , 0x403f   #reg_rx_en

.if ( ENABLE_MIU1 == 1 )
    WREG    (REG_ADDR_BASE + (0x110d88 <<1 )) , 0x403f   #reg_rx_en
.endif
#else
    WREG    (REG_ADDR_BASE + (0x110d08 <<1 )) , 0x003f   #reg_rx_en

.if ( ENABLE_MIU1 == 1 )
    WREG    (REG_ADDR_BASE + (0x110d88 <<1 )) , 0x003f   #reg_rx_en
.endif
#endif

    #bal     EnableMiuSsc
    #nop

    # MIU0 INIT Cycle
    WREG    (REG_ADDR_BASE + (0x101200 <<1 )), 0x0000 # hold miu_0
    WREG    (REG_ADDR_BASE + (0x101200 <<1 )), 0x0008 # DRAM reset
    WREG    (REG_ADDR_BASE + (0x101200 <<1 )), 0x000c # DRAM reset+CS
    DELAYUS 300    # delay 300us
    WREG    (REG_ADDR_BASE + (0x101200 <<1 )), 0x000e # DRAM reset+CS+CKE
    DELAYUS 500    # delay 500us
    WREG    (REG_ADDR_BASE + (0x101200 <<1 )), 0x001f # DRAM reset+CS+CKE+auto cycle+ODE
    DBGREG  0x0025

CheckMiu0Init:
    RREG    $9,(REG_ADDR_BASE + (0x101200 <<1 ))
    andi    $9 , $9, 0x8000
    beqz    $9 ,  CheckMiu0Init
    nop

.if ( ENABLE_MIU1 == 1 )
    # MIU1 INIT Cycle
    WREG    (REG_ADDR_BASE + (0x100600 <<1 )), 0x0000 # hold miu_0
    WREG    (REG_ADDR_BASE + (0x100600 <<1 )), 0x0008 # DRAM reset
    WREG    (REG_ADDR_BASE + (0x100600 <<1 )), 0x000c # DRAM reset+CS
    DELAYUS 300    # delay 300us
    WREG    (REG_ADDR_BASE + (0x100600 <<1 )), 0x000e # DRAM reset+CS+CKE
    DELAYUS 500    # delay 500us
    WREG    (REG_ADDR_BASE + (0x100600 <<1 )), 0x001f # DRAM reset+CS+CKE+auto cycle+ODE
CheckMiu1Init:
    RREG    $9,(REG_ADDR_BASE + (0x100600 <<1 ))
    andi    $9 , $9, 0x8000
    beqz    $9 , CheckMiu1Init
    nop
.endif

    DELAYUS 200   # delay 200us
    DBGREG  0x0027

    bal      MIU_Init_Priority
    nop

    bal      MIU_Set_Group_Priority
    nop

    DBGREG  0x0028

    WREG    (REG_ADDR_BASE + (0x101246 <<1 )) , 0x7FFE   #Mask MIU0_group_0
    bal     Miu0_AutoPhase
    nop
.if ( ENABLE_MIU1 == 1 )
    WREG    (REG_ADDR_BASE + (0x100646 <<1 )) , 0x7FFE   #Mask MIU0_group_0
    bal     Miu1_AutoPhase
    nop
.endif

    # BIST test
    WREG    (REG_ADDR_BASE + (0x101246 <<1 )) , 0x7FFE   #Mask MIU0_group_0
    bal     Miu0_BistTest
    nop
.if ( ENABLE_MIU1 == 1 )
    WREG    (REG_ADDR_BASE + (0x100646 <<1 )) , 0x7FFE   #Mask MIU0_group_0
    bal     Miu1_BistTest
    nop
.endif
    WREG    (REG_ADDR_BASE + (0x1012e0 <<1 )) , 0x0000  # stop bist test

    # open all MIU0 request mask (All IP can access MIU resource)
    WREG    (REG_ADDR_BASE + (0x101246 <<1 )) , 0x0000   #Unmask MIU0_group_0
    WREG    (REG_ADDR_BASE + (0x101266 <<1 )) , 0x0000   #Unmask MIU0_group_1
    WREG    (REG_ADDR_BASE + (0x101286 <<1 )) , 0x0000   #Unmask MIU0_group_2
    WREG    (REG_ADDR_BASE + (0x1012a6 <<1 )) , 0x0000   #Unmask MIU0_group_3

.if ( ENABLE_MIU1 == 1 )
    # open all MIU1 request mask (All IP can access MIU resource)
    WREG    (REG_ADDR_BASE + (0x100646 <<1 )) , 0x0000   #Unmask MIU0_group_0
    WREG    (REG_ADDR_BASE + (0x100666 <<1 )) , 0x0000   #Unmask MIU0_group_1
    WREG    (REG_ADDR_BASE + (0x100686 <<1 )) , 0x0000   #Unmask MIU0_group_2
    WREG    (REG_ADDR_BASE + (0x1006a6 <<1 )) , 0x0000   #Unmask MIU0_group_3

    # all MIU1 IP select MIU0 in bringup
    WREG    (REG_ADDR_BASE + (0x1006f0 <<1 )), 0x0000
    WREG    (REG_ADDR_BASE + (0x1006f2 <<1 )), 0x0000
    WREG    (REG_ADDR_BASE + (0x1006f4 <<1 )), 0x0000
    WREG    (REG_ADDR_BASE + (0x1006f6 <<1 )), 0x0000
.endif

    WREG    (REG_ADDR_BASE + (0x10121e <<1 )), 0x1808   # SW initial done and turn on arbitor
    WREG    (REG_ADDR_BASE + (0x1012fc <<1 )), 0x8400
.if ( ENABLE_MIU1 == 1 )
    WREG    (REG_ADDR_BASE + (0x10061e <<1 )), 0x1808   # SW initial done and turn on arbitor
    WREG    (REG_ADDR_BASE + (0x1006fc <<1 )), 0x8400
.endif

.if (ENABLE_MSTAR_MIU_HIGHWAY_ENABLE)
    WREG    0xBF2024A4, 0x6EF0   #0110 1110 1111 0000  G0 last_done_z_sel
    WREG    0xBF2024E4, 0x0010   #0000 0000 0001 0000  G1 last_done_z_sel
    WREG    0xBF202524, 0x6400   #0110 0100 0000 0000  G2 last_done_z_sel
    WREG    0xBF202564, 0x1EE9   #0001 1110 1110 1001  G3 last_done_z_sel
.if(ENABLE_MIU1 == 1)
    WREG    0xBF200CA4, 0x6EF0   #0110 1110 1111 0000  G0 last_done_z_sel
    WREG    0xBF200CE4, 0x0010   #0000 0000 0001 0000  G1 last_done_z_sel
    WREG    0xBF200D24, 0x6400   #0110 0100 0000 0000  G2 last_done_z_sel
    WREG    0xBF200D64, 0x1EE9   #0001 1110 1110 1001  G3 last_done_z_sel
.endif
.endif

    #default BW table
    WREG    (REG_ADDR_BASE + (0x101242 <<1 )), 0x0008
    WREG    (REG_ADDR_BASE + (0x101244 <<1 )), 0x0200
    WREG    (REG_ADDR_BASE + (0x101262 <<1 )), 0x0008
    WREG    (REG_ADDR_BASE + (0x101264 <<1 )), 0x0200
    WREG    (REG_ADDR_BASE + (0x101282 <<1 )), 0x0008
    WREG    (REG_ADDR_BASE + (0x101284 <<1 )), 0x0200
    WREG    (REG_ADDR_BASE + (0x1012A2 <<1 )), 0x0008
    WREG    (REG_ADDR_BASE + (0x1012A4 <<1 )), 0x0200
    WREG    (REG_ADDR_BASE + (0x101240 <<1 )), 0x8015
    WREG    (REG_ADDR_BASE + (0x101260 <<1 )), 0x8015
    WREG    (REG_ADDR_BASE + (0x101280 <<1 )), 0x8015
    WREG    (REG_ADDR_BASE + (0x1012A0 <<1 )), 0x8015
.if ( ENABLE_MIU1 == 1 )
    WREG    (REG_ADDR_BASE + (0x100642 <<1 )), 0x0008
    WREG    (REG_ADDR_BASE + (0x100644 <<1 )), 0x0200
    WREG    (REG_ADDR_BASE + (0x100662 <<1 )), 0x0008
    WREG    (REG_ADDR_BASE + (0x100664 <<1 )), 0x0200
    WREG    (REG_ADDR_BASE + (0x100682 <<1 )), 0x0008
    WREG    (REG_ADDR_BASE + (0x100684 <<1 )), 0x0200
    WREG    (REG_ADDR_BASE + (0x1006A2 <<1 )), 0x0008
    WREG    (REG_ADDR_BASE + (0x1006A4 <<1 )), 0x0200
    WREG    (REG_ADDR_BASE + (0x100640 <<1 )), 0x8015
    WREG    (REG_ADDR_BASE + (0x100660 <<1 )), 0x8015
    WREG    (REG_ADDR_BASE + (0x100680 <<1 )), 0x8015
    WREG    (REG_ADDR_BASE + (0x1006A0 <<1 )), 0x8015
.endif

    move     $31,$15
    jr       $31
    nop

#-------------------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------------------
EnableMiuSsc:
    # ENABLE MIU_0_SSC
    WREG    (0xbf000000 +(0x110d28 << 1 )),DDFSTEP  #DDFSTEP
    WREG    (0xbf000000 +(0x110d2A << 1 )),DDFSPAN  #DDFSPAN
    RREG    $9, (0xbf000000 +(0x110d28 << 1 ))       #ENABLE MIU_SSC
    ori     $9, $9, 0x8000
    sw      $9, (0xbf000000 +(0x110d28 << 1 ))

    # ENABLE MIU_1_SSC
    WREG    (0xbf000000 +(0x110dA8 << 1 )),DDFSTEP  #DDFSTEP
    WREG    (0xbf000000 +(0x110dAA << 1 )),DDFSPAN  #DDFSPAN
    RREG    $9,(0xbf000000 +(0x110dA8 << 1 ))       #ENABLE MIU_SSC
    ori     $9, $9, 0x8000
    sw      $9, (0xbf000000 +(0x110dA8 << 1 ))

    j       $31
    nop

#-------------------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------------------
Miu1_AutoPhase:
    WREG    0xBF2025E0 , 0x8000                      #1012f0 bit_15=1 choice to MIU_1
    li      $23, (REG_ADDR_BASE+(0x103394<<1))      # Dummy register to store miu1 DQS phase result
    li      $24, 0                                  # DQS phase result

    RREG    $9, (REG_ADDR_BASE+(0x110DEE<<1))       # store the default phase setting to r19
    move    $19, $9                                 #

    li      $11, (REG_ADDR_BASE+(0x110DEE<<1))      # reg_0x110DEE  //miu1_phase_reg
    j       AutoPhaseLoop
    nop
Miu0_AutoPhase:
    WREG   0xBF2025E0 , 0x0000                      # 1012f0 bit_15=0 choice to MIU_0
    li      $23, (REG_ADDR_BASE+(0x103390<<1))      # Dummy register to store miu 0 DQS phase result
    li      $24, 0                                  # DQS phase result

    RREG    $9, (REG_ADDR_BASE+(0x110D6E<<1))       # store the default phase setting to r19
    move    $19, $9                                 #

    li      $11, (REG_ADDR_BASE+(0x110D6E<<1))      # reg_0x110D6E  //miu0_phase_reg

AutoPhaseLoop:
    WREG    (REG_ADDR_BASE + (0x1012E8 <<1)),0x5AA5 #1012e8 //bist test pattern
    sb      $9, (0)($10)

    PUTK    '['

    WREG    (REG_ADDR_BASE+(0x1012e2<<1)), 0x1FFF   # 1012e2 bist test start address, (4K byte/unit)
    WREG    (REG_ADDR_BASE+(0x1012e4<<1)), 0x1000   # 1012e4~1012e7 bist test size,   (16 byte/unit)
    WREG    (REG_ADDR_BASE+(0x1012e6<<1)), 0x0000   # 1012e4~1012e7 bist test size,   (16 byte/unit)
    WREG    (REG_ADDR_BASE+(0x1012e8<<1)), 0x00FF   # 1012e4~1012e7 bist test pattern

    lui     $13,0                                   # $13-->tmp_var0=0;  for loop cnt
    lui     $21,0                                   # $21-->good_phase cnt
    lui     $20, 0                                  # $20-->good_phase_sum
    li      $25, 1                                  # $25-->good_phase bit

StartChk_x3:
    sw      $24, (0)($23)         # store phase 3 result
    addiu   $23, $23, 4
    li      $24, 0                # DQS phase result
    li      $25, 1
    j       check_x3
    nop
check_x3:
    #ClockReset
    li      $14, (REG_ADDR_BASE+(0x110D0E<<1))
    lb      $26, (0)($14)
    andi    $26, $26, 0x9F
    ori     $26, $26, 0x60
    sb      $26, (0)($14)

    andi    $9, $13 ,0x0f
    sll     $9, $9 ,12
    andi    $8, $19, 0x0fff           # set dqs3 delay phase to r8
    or      $9, $9, $8
    sw      $9,(0)($11)

    #ClockUnReset
    li      $14, (REG_ADDR_BASE+(0x110D0E<<1))
    lb      $26, (0)($14)
    andi    $26, $26, 0x9F
    ori     $26, $26, 0x20
    sb      $26, (0)($14)

    j       StartCheck
    nop

StartChk_x2:
    sw      $24, (0)($23)         # store phase 2 result
    addiu   $23, $23, 4
    li      $24, 0                # DQS phase result
    li      $25, 1
    j       check_x2
    nop
check_x2:
    #ClockReset
    li      $14, (REG_ADDR_BASE+(0x110D0E<<1))
    lb      $26, (0)($14)
    andi    $26, $26, 0x9F
    ori     $26, $26, 0x60
    sb      $26, (0)($14)

    andi    $9, $13 ,0x0f
    sll     $9, $9 ,8
    andi    $8, $19, 0xf0ff           # set dqs2 delay phase to r8
    or      $9, $9, $8
    sw      $9,(0)($11)

    #ClockUnReset
    li      $14, (REG_ADDR_BASE+(0x110D0E<<1))
    lb      $26, (0)($14)
    andi    $26, $26, 0x9F
    ori     $26, $26, 0x20
    sb      $26, (0)($14)

    j       StartCheck
    nop

StartChk_x1:
    sw      $24, (0)($23)         # store phase 1 result
    addiu   $23, $23, 4
    li      $24, 0                # DQS phase result
    li      $25, 1
    j       check_x1
    nop
check_x1:
    #ClockReset
    li      $14, (REG_ADDR_BASE+(0x110D0E<<1))
    lb      $26, (0)($14)
    andi    $26, $26, 0x9F
    ori     $26, $26, 0x60
    sb      $26, (0)($14)

    andi    $9, $13 ,0x0f
    sll     $9, $9 ,4
    andi    $8, $19, 0xff0f           # set dqs1 delay phase to r8
    or      $9, $9, $8
    sw      $9,(0)($11)

    #ClockUnReset
    li      $14, (REG_ADDR_BASE+(0x110D0E<<1))
    lb      $26, (0)($14)
    andi    $26, $26, 0x9F
    ori     $26, $26, 0x20
    sb      $26, (0)($14)

    j       StartCheck
    nop

StartChk_x0:
    sw      $24, (0)($23)         # store phase 0 result
    addiu   $23, $23, 4
    li      $24, 0                # DQS phase result
    li      $25, 1
    j       check_x0
    nop
check_x0:
    #ClockReset
    li      $14, (REG_ADDR_BASE+(0x110D0E<<1))
    lb      $26, (0)($14)
    andi    $26, $26, 0x9F
    ori     $26, $26, 0x60
    sb      $26, (0)($14)

    andi    $9, $13 ,0x0f
    andi    $8, $19, 0xfff0  # get the default phase setting
    or      $9, $9, $8
    sw      $9, (0)($11)
    #ClockUnReset
    li      $14, (REG_ADDR_BASE+(0x110D0E<<1))
    lb      $26, (0)($14)
    andi    $26, $26, 0x9F
    ori     $26, $26, 0x20
    sb      $26, (0)($14)

StartCheck:
.if ( ENABLE_MIU1 == 1 )
    WREG    0xbf200DC0, 0x0000
.endif
    WREG    0xbf2025C0,0x0000
    li      $9, 0x0083              # bist mode 0x83
    j       BitModeTest
    nop

Check_bist85:
.if ( ENABLE_MIU1 == 1 )
    WREG    0xbf200DC0, 0x0000
.endif
    WREG    0xbf2025C0,0x0000
    li      $9, 0x0085              # bist mode 0x85
    j       BitModeTest
    nop

Check_bist87:
.if ( ENABLE_MIU1 == 1 )
    WREG    0xbf200DC0, 0x0000
.endif
    WREG    0xbf2025C0,0x0000
    li      $9, 0x0087              # bist mode 0x87

BitModeTest:
    move    $22,$31
    bal     ModeChangeDelay
    nop
    move    $31,$22

    lui     $8, 0xBF20              # bist test start
    sw      $9, (0x25C0)($8)

CheckBistDone:
    RREG    $9, 0xBF2025C0
    andi    $8, $9, 0x8000
    beqz    $8, CheckBistDone        # check done
    nop
    andi    $8, $9, 0x6000
    bnez    $8, checkloopFail        # bist test fail if not zero
    nop

BistCheckPhaseOK:
    andi    $8, $9, 0x00FF
    beq     $8, 0x83, Check_bist85       #0x83->0x85->0x87
    nop
    beq     $8, 0x85, Check_bist87
    nop

    move    $22,$31
    andi    $9, $13, 0x0f        #move $13(loop cnt) to $9 for putchar
    bal     puthex
    nop
    move    $31,$22

    addiu   $21, $21, 1         # good_phase_cnt++;
    andi    $22, $13, 0x0f      # get good_phase
    add     $20, $20 ,$22        # good_phase_sum += good phase
    or      $24, $24, $25

checkloopFail:


CheckLoop:
    sll     $25, $25, 1
    addiu   $13, $13, 1             # add loop cnt by 1
x3_loop:
    bltu    $13,16, check_x3
    nop
    bne     $13, 16, x2_loop        # if $13=loop count > 16, jump
    nop
    beqz    $21, SetToDefault_P3    # if good_phase cnt == 0
    nop
    move    $22, $20  #good_phase_sum
    div     $22, $22 , $21
    sll     $22, $22 , 12
    j       StorePhase_P3
    nop

x2_loop:
    bltu    $13,32, check_x2
    nop
    bne     $13, 32, x1_loop        # if $13=loop count > 32, jump
    nop
    beqz    $21, SetToDefault_P2    # if good_phase cnt == 0
    nop
    move    $22, $20  #good_phase_sum
    div     $22, $22 , $21
    sll     $22, $22 , 8
    j       StorePhase_P2
    nop

x1_loop:
    bltu    $13,48, check_x1
    nop
    bne     $13, 48, x0_loop        # if $13=loop count > 48, jump
    nop
    beqz    $21, SetToDefault_P1    # if good_phase cnt == 0
    nop
    move    $22, $20  #good_phase_sum
    div     $22, $22 , $21
    sll     $22, $22 , 4
    j       StorePhase_P1
    nop

x0_loop:
    bltu	$13,64, check_x0      #AutoPhaseLoop1
    sw      $24, (0)($23)         #store phase 0  result
    nop
    beqz    $21, SetToDefault_P0  # good_phase cnt == 0
    nop
    move    $22, $20  #good_phase_sum
    div     $22, $22 , $21
    sll     $22, $22 , 0
    j       StorePhase_P0
    nop

SetToDefault_P3:
    #ClockReset
    li      $14, (REG_ADDR_BASE+(0x110D0E<<1))
    lb      $26, (0)($14)
    andi    $26, $26, 0x9F
    ori     $26, $26, 0x60
    sb      $26, (0)($14)

    move    $9, $19
    j       SetPhaseToDefault_p3
    nop
StorePhase_P3:
    #ClockReset
    li      $14, (REG_ADDR_BASE+(0x110D0E<<1))
    lb      $26, (0)($14)
    andi    $26, $26, 0x9F
    ori     $26, $26, 0x60
    sb      $26, (0)($14)

    andi    $9,  $19 , 0x0fff
    or      $9,  $9 , $22
SetPhaseToDefault_p3:
    sw      $9,  0($11)
    move    $19, $9

   #ClockUnReset
   li      $14, (REG_ADDR_BASE+(0x110D0E<<1))
   lb      $26, (0)($14)
   andi    $26, $26, 0x9F
   ori     $26, $26, 0x20
   sb      $26, (0)($14)


    lui     $21,0                  # $21-->good_phase cnt
    lui     $20,0                  # $20-->good_phase_sum

    PUTK    ']'
    #PUTK   '\r'
    #PUTK   '\n'
    PUTK    '['

    # start check DQS_phase_0
    #sw     $19, (0)($11)
    j       StartChk_x2
    nop

SetToDefault_P2:
    #ClockReset
    li      $14, (REG_ADDR_BASE+(0x110D0E<<1))
    lb      $26, (0)($14)
    andi    $26, $26, 0x9F
    ori     $26, $26, 0x60
    sb      $26, (0)($14)

    move    $9, $19
    j       SetPhaseToDefault_p2
    nop
StorePhase_P2:
    #ClockReset
    li      $14, (REG_ADDR_BASE+(0x110D0E<<1))
    lb      $26, (0)($14)
    andi    $26, $26, 0x9F
    ori     $26, $26, 0x60
    sb      $26, (0)($14)

    andi    $9,  $19 , 0xf0ff
    or      $9,  $9 , $22
SetPhaseToDefault_p2:
    sw      $9,  0($11)
    move    $19, $9

   #ClockUnReset
   li      $14, (REG_ADDR_BASE+(0x110D0E<<1))
   lb      $26, (0)($14)
   andi    $26, $26, 0x9F
   ori     $26, $26, 0x20
   sb      $26, (0)($14)


    lui     $21,0                  # $21-->good_phase cnt
    lui     $20,0                  # $20-->good_phase_sum

    PUTK    ']'
    #PUTK   '\r'
    #PUTK   '\n'
    PUTK    '['

    # start check DQS_phase_0
    #sw     $19, (0)($11)
    j       StartChk_x1
    nop

SetToDefault_P1:
    #ClockReset
    li      $14, (REG_ADDR_BASE+(0x110D0E<<1))
    lb      $26, (0)($14)
    andi    $26, $26, 0x9F
    ori     $26, $26, 0x60
    sb      $26, (0)($14)

    move    $9, $19
    j       SetPhaseToDefault_p1
    nop
StorePhase_P1:
    #ClockReset
    li      $14, (REG_ADDR_BASE+(0x110D0E<<1))
    lb      $26, (0)($14)
    andi    $26, $26, 0x9F
    ori     $26, $26, 0x60
    sb      $26, (0)($14)

    andi    $9,  $19 , 0xff0f
    or      $9,  $9 , $22
SetPhaseToDefault_p1:
    sw      $9,  0($11)
    move    $19, $9

   #ClockUnReset
   li      $14, (REG_ADDR_BASE+(0x110D0E<<1))
   lb      $26, (0)($14)
   andi    $26, $26, 0x9F
   ori     $26, $26, 0x20
   sb      $26, (0)($14)


    lui     $21,0                  # $21-->good_phase cnt
    lui     $20,0                  # $20-->good_phase_sum

    PUTK    ']'
    #PUTK   '\r'
    #PUTK   '\n'
    PUTK    '['

    # start check DQS_phase_0
    #sw     $19, (0)($11)
    j       StartChk_x0
    nop

SetToDefault_P0:
    #ClockReset
    li      $14, (REG_ADDR_BASE+(0x110D0E<<1))
    lb      $26, (0)($14)
    andi    $26, $26, 0x9F
    ori     $26, $26, 0x60
    sb      $26, (0)($14)

    move    $9 , $19
    j       SetPhaseToDefault
    nop
StorePhase_P0:
    #ClockReset
    li      $14, (REG_ADDR_BASE+(0x110D0E<<1))
    lb      $26, (0)($14)
    andi    $26, $26, 0x9F
    ori     $26, $26, 0x60
    sb      $26, (0)($14)

    andi    $9,  $19 , 0xfff0
    or      $9,  $9 , $22
SetPhaseToDefault:
    sw      $9,  0($11)
    move    $19, $9

   #ClockUnReset
   li      $14, (REG_ADDR_BASE+(0x110D0E<<1))
   lb      $26, (0)($14)
   andi    $26, $26, 0x9F
   ori     $26, $26, 0x20
   sb      $26, (0)($14)

    PUTK    ']'
    PUTK    '-'

    move    $22,$31
    andi    $9,$19,0xf000
    srl     $9,$9,12
    bal     puthex
    nop
    andi    $9,$19,0x0f00
    srl     $9,$9,8
    bal     puthex
    nop
    andi    $9,$19,0x00f0
    srl     $9,$9,4
    bal     puthex
    nop
    andi    $9,$19,0x000f
    bal     puthex
    nop
    move    $31,$22

AutoPhaseRet:
    WREG    0xbf2025C0 , 0x0000
    li      $9, 0x00             # 1012e7/1006e7 =0x00 mask DQS_1 error when test DQS_0
    sb      $9, (0)($10)

    PUTK    '\r'
    PUTK    '\n'

    jr      $31
    nop

puthex:
    bltu    $9, 10, putx0_9
    nop
putxA_F:
    addiu   $9, $9, 0x37
    j       putx
    nop
putx0_9:
    addiu   $9, $9, 0x30
putx:
    SSSW    0xBF201300, $9
    jr      $31
    nop

ModeChangeDelay:
    lui     $8, 0x0
DelayLoop:
    addiu   $8, $8, 1
    bltu    $8, 10, DelayLoop
    nop
    jr      $31
    nop

#-------------------------------------------------------------------------------------------------
# MIU_Init_Priority
# @param  None
# @return None
# @note   Init MIU Priority
#-------------------------------------------------------------------------------------------------
MIU_Init_Priority:

# MIU0: generate set priority pulse for "fix priority"

    RREG    $11, 0xBF202480
    and     $11, $11, 0x0001
    bgtz    $11, miu0_rq0_skip

    RREG    $11, 0xBF202480
    or      $11, $11, 0x0002
    lui     $8,  (0xBF202480 >> 16)
    sw      $11, (0xBF202480 & 0xFFFF)($8)

    RREG    $11, 0xBF202480
    and     $11, $11, 0xFFFD
    lui     $8,  (0xBF202480 >> 16)
    sw      $11, (0xBF202480 & 0xFFFF)($8)
miu0_rq0_skip:

    RREG    $11, 0xBF2024C0
    and     $11, $11, 0x0001
    bgtz    $11, miu0_rq1_skip

    RREG    $11, 0xBF2024C0
    or      $11, $11, 0x0002
    lui     $8,  (0xBF2024C0 >> 16)
    sw      $11, (0xBF2024C0 & 0xFFFF)($8)

    RREG    $11, 0xBF2024C0
    and     $11, $11, 0xFFFD
    lui     $8,  (0xBF2024C0 >> 16)
    sw      $11, (0xBF2024C0 & 0xFFFF)($8)
miu0_rq1_skip:

    RREG    $11, 0xBF202500
    and     $11, $11, 0x0001
    bgtz    $11, miu0_rq2_skip

    RREG    $11, 0xBF202500
    or      $11, $11, 0x0002
    lui     $8,  (0xBF202500 >> 16)
    sw      $11, (0xBF202500 & 0xFFFF)($8)

    RREG    $11, 0xBF202500
    and     $11, $11, 0xFFFD
    lui     $8,  (0xBF202500 >> 16)
    sw      $11, (0xBF202500 & 0xFFFF)($8)
miu0_rq2_skip:

    RREG    $11, 0xBF202540
    and     $11, $11, 0x0001
    bgtz    $11, miu0_rq3_skip

    RREG    $11, 0xBF202540
    or      $11, $11, 0x0002
    lui     $8,  (0xBF202540 >> 16)
    sw      $11, (0xBF202540 & 0xFFFF)($8)

    RREG    $11, 0xBF202540
    and     $11, $11, 0xFFFD
    lui     $8,  (0xBF202540 >> 16)
    sw      $11, (0xBF202540 & 0xFFFF)($8)
miu0_rq3_skip:


# MIU1: generate set priority pulse for "fix priority"

    RREG    $11, 0xBF200C80
    and     $11, $11, 0x0001
    bgtz    $11, miu1_rq0_skip

    RREG    $11, 0xBF200C80
    or      $11, $11, 0x0002
    lui     $8,  (0xBF200C80 >> 16)
    sw      $11, (0xBF200C80 & 0xFFFF)($8)

    RREG    $11, 0xBF200C80
    and     $11, $11, 0xFFFD
    lui     $8,  (0xBF200C80 >> 16)
    sw      $11, (0xBF200C80 & 0xFFFF)($8)
miu1_rq0_skip:

    RREG    $11, 0xBF200CC0
    and     $11, $11, 0x0001
    bgtz    $11, miu1_rq1_skip

    RREG    $11, 0xBF200CC0
    or      $11, $11, 0x0002
    lui     $8,  (0xBF200CC0 >> 16)
    sw      $11, (0xBF200CC0 & 0xFFFF)($8)

    RREG    $11, 0xBF200CC0
    and     $11, $11, 0xFFFD
    lui     $8,  (0xBF200CC0 >> 16)
    sw      $11, (0xBF200CC0 & 0xFFFF)($8)
miu1_rq1_skip:

    RREG    $11, 0xBF200D00
    and     $11, $11, 0x0001
    bgtz    $11, miu1_rq2_skip

    RREG    $11, 0xBF200D00
    or      $11, $11, 0x0002
    lui     $8,  (0xBF200D00 >> 16)
    sw      $11, (0xBF200D00 & 0xFFFF)($8)

    RREG    $11, 0xBF200D00
    and     $11, $11, 0xFFFD
    lui     $8,  (0xBF200D00 >> 16)
    sw      $11, (0xBF200D00 & 0xFFFF)($8)
miu1_rq2_skip:

    RREG    $11, 0xBF200D40
    and     $11, $11, 0x0001
    bgtz    $11, miu1_rq3_skip

    RREG    $11, 0xBF200D40
    or      $11, $11, 0x0002
    lui     $8,  (0xBF200D40 >> 16)
    sw      $11, (0xBF200D40 & 0xFFFF)($8)

    RREG    $11, 0xBF200D40
    and     $11, $11, 0xFFFD
    lui     $8,  (0xBF200D40 >> 16)
    sw      $11, (0xBF200D40 & 0xFFFF)($8)
miu1_rq3_skip:

    jr      $31
    nop

#-------------------------------------------------------------------------------------------------
# MIU_Set_Group_Priority
# @param  None
# @return None
# @note   Set Group Priority
#-------------------------------------------------------------------------------------------------
MIU_Set_Group_Priority:

    #set group priority in MIU_0
    RREG    $11, 0xBF2025B8
    andi    $11, $11, 0xFEFF
    lui     $8,  (0xBF2025B8 >> 16)
    sw      $11, (0xBF2025B8 & 0xFFFF)($8)

    RREG    $11, 0xBF2025B8
    and     $11, $11, 0xFF00
    ori     $11, $11, (MIU0_GROUP_PRIORITY & 0xFF)
    lui     $8,  (0xBF2025B8 >> 16)
    sw      $11, (0xBF2025B8 & 0xFFFF)($8)

    RREG    $11, 0xBF2025B8
    ori      $11, $11, 0x0100           # set group fix priority
    lui     $8,  (0xBF2025B8 >> 16)
    sw      $11, (0xBF2025B8 & 0xFFFF)($8)

    #set group priority in MIU_1
    RREG    $11, 0xBF200DB8
    andi     $11, $11, 0xFEFF
    lui     $8,  (0xBF200DB8 >> 16)
    sw      $11, (0xBF200DB8 & 0xFFFF)($8)

    RREG    $11, 0xBF200DB8
    andi     $11, $11, 0xFF00
    or      $11, $11, (MIU1_GROUP_PRIORITY & 0xFF)
    lui     $8,  (0xBF200DB8 >> 16)
    sw      $11, (0xBF200DB8 & 0xFFFF)($8)

    RREG    $11, 0xBF200DB8
    ori      $11, $11, 0x0100
    lui     $8,  (0xBF200DB8 >> 16)
    sw      $11, (0xBF200DB8 & 0xFFFF)($8)

    jr      $31
    nop

#-------------------------------------------------------------------------------------------------
# MiuBistTest
# @param
# @return None
# @note
#-------------------------------------------------------------------------------------------------
Miu1_BistTest:
   #miu_1 bist test ---128Mbyte
   WREG   0xBF2025c0 , 0x0000   #1012e0 //reset bist test
   WREG   0xBF2025E0 , 0x8000   #1012f0 bit_15=1 choice to MIU_1

   WREG   0xBF2025c4 , 0x0000   #1012e2 //start address base unit   :4k bytes
   WREG_D 0xBF2025c8 , BIST_LEN
   PUTK   'B'
   PUTK   'I'
   PUTK   'S'
   PUTK   'T'
   PUTK   '1'
   PUTK   '-'
   j      BistTest
   nop

Miu0_BistTest:
   #miu_0 bist test ---128Mbyte
   PUTK   '\n'
   PUTK   '\r'
   PUTK   'B'
   PUTK   'I'
   PUTK   'S'
   PUTK   'T'
   PUTK   '0'
   PUTK   '-'

   WREG    (REG_ADDR_BASE + (0x1012e0 <<1 )) , 0x0000   #1012e0 //reset bist test
   WREG    (REG_ADDR_BASE + (0x1012e2 <<1 )) , 0x0000   #1012e2 //start address base unit   :4k bytes
   WREG_D  (REG_ADDR_BASE + (0x1012e4 <<1 )) , BIST_LEN
   WREG    (REG_ADDR_BASE + (0x1012e8 <<1 )) , 0x5aa5   #1012e8 //bist test pattern

BistTest:
   WREG    (REG_ADDR_BASE + (0x1012e0 <<1 )) , 0x0003   #bitst test mode:3

ChkBistMiu0:
    RREG   $9 , (REG_ADDR_BASE + (0x1012e0 <<1 ))
    andi   $8 , $9, 0x8000
    beqz   $8 , ChkBistMiu0
    nop

    andi   $8 , $9, 0x6000
    beqz   $8 , BistMiu0_OK
    nop

BistMiu0_FAIL:
   PUTK   'F'
   PUTK   'A'
   PUTK   'I'
   PUTK   'L'
   j      BistRet
   nop


BistMiu0_OK:
   PUTK   'O'
   PUTK   'K'

BistRet:
   PUTK   '\n'
   PUTK   '\r'

   jr      $31
   nop

#-------------------------------------------------------------------------------------------------
# BOOTROM_MPLL_INIT
# @param  Nnoe
# @return None
# @note   do MPLL init
#-------------------------------------------------------------------------------------------------
BOOTROM_MPLL_INIT:

.if (BOOTING_FROM_EXT_SPI_WITH_PM51 != 1)
//Module: adc_atop (0x1025)
    WREG_B  0xBF204A1C, 0x3F
    WREG_B  0xBF204A1C, 0x00        //Release Soft-Reset for ADCA/PLLA/ADCB/PLLB/ATOP/Phase DAC

    WREG    0xBF204A10, 0x0000      //Power-On releated blocks in ATOP
    WREG    0xBF204A14, 0x0000
    WREG    0xBF204A18, 0x0000
    WREG    0xBF204AFC, 0x0030      //Enable SOG MUX

                                    //CVBS DAC
    WREG_B  0xBF204B20, 0x08        //Enable IDAC (Ch1)
    WREG_B  0xBF204B24, 0x08        //Enable IDAC (Ch2)
                                    //CVBSO
    WREG_B  0xBF204B40, 0x00        //Enable CVBSO1
    WREG_B  0xBF204B48, 0x00        //Enable CVBSO2

//Module: dvi_atop (0x1109)
    WREG    0xBF221218, 0x0000      //Relase soft-reset for DVI/HDMI/HDCP blocks
    WREG    0xBF221380, 0x0000      //Power-on for DVI/HDMI/HDCP blocks
    WREG    0xBF2213A4, 0x0000      //Power-on for DVT port 2
    WREG    0xBF22120C, 0x0000      //Enable clock for related dvi_atop IPs
    WREG    0xBF22139C, 0x4000      //Port A/C: ENAUTO
    WREG    0xBF221394, 0x3000      //Port A/C: TEST_CMP[1:0]
    WREG    0xBF2213FC, 0x0000      //A1 added

//Module: dvi_atop1 (0x1132)
    WREG    0xBF226418, 0x0000
    WREG    0xBF226580, 0x0000
    WREG    0xBF22659C, 0x4000      //Port B: ENAUTO
    WREG    0xBF226594, 0x3000      //Port B: TEST_CMP[1:0]
    WREG    0xBF2265D0, 0x0000      //A1 added

//Module: dvi_atop2 (0x1134)
    WREG    0xBF226818, 0x0000
    WREG    0xBF226980, 0x0000
    WREG    0xBF22699C, 0x4000      //Port D: ENAUTO
    WREG    0xBF226994, 0x3000      //Port D: TEST_CMP[1:0]
    WREG    0xBF2269D0, 0x0000      //A1 added

//Module: pm_sleep (0x000E)
    WREG    0xBF001D28, 0x0000      //Power-on dvi_atop in PM_SLEEP
    WREG    0xBF001D2C, 0x0000

//Module: chiptop (0x101E)
    WREG_B  0xBF203C70, 0x00        //Power-on for PD_3P3_1, PD_3P3_0 and PD_3P3_USB1

//Module: ana_misc (0x110C)
                                    //MPLL
    WREG    0xBF221804, 0x0000      //MPLL enable

.endif
                                    //MIPSPLL
    WREG    0xBF221844, 0x0001      //MIPSPLL enable

    //(formula:frequency = 12MHz * (16bit_address_0x13[7:0])
    .if (CPU_CLOCK == 504)
    WREG_B    0xBF22184C, 0x2A
    .endif

    .if (CPU_CLOCK == 600)
    WREG_B    0xBF22184C, 0x32
    .endif

    .if (CPU_CLOCK == 672)
    WREG_B    0xBF22184C, 0x38
    .endif

    .if (CPU_CLOCK == 684)
    WREG_B    0xBF22184C, 0x39
    .endif

    .if (CPU_CLOCK == 696)
    WREG_B    0xBF22184C, 0x3A
    .endif

    .if (CPU_CLOCK == 708)
    WREG_B    0xBF22184C, 0x3B
    .endif

    .if (CPU_CLOCK == 720)
    WREG_B    0xBF22184C, 0x3C
    .endif

    .if (CPU_CLOCK == 756)
    WREG_B    0xBF22184C, 0x3F
    .endif

    .if (CPU_CLOCK == 780)
    WREG_B  0xBF22184C, 0x41        //MIPSPLL enable --> 780MHz for bring up
    .endif

    .if (CPU_CLOCK == 900)
    WREG_B  0xBF22184C, 0x4B         //MIPSPLL enable --> 780MHz for bring up
    .endif

    WREG_B  0xBF22184C, (CPU_CLOCK / 12)

.if (BOOTING_FROM_EXT_SPI_WITH_PM51 != 1)

	  WREG    0xBF201674, 0x0001
                                     //MIU_128bit PLL  (default =~ 300 MHz)
                                    //MIU_256bit PLL  (default =~ 264 MHz)
    WREG    0xBF2218C4, 0x0000      //MIU_128BUS_PLL power on
    WREG    0xBF2218E4, 0x0000      //MIU_256BUS_PLL power on
    //WREG    0xBF201674, 0x0808      //turn on clk_miu & select clk_miu = MIU_128bit_PLL_VCO
                                    //turn on clk_miu_256bus & select clk_miu_256bus = MIU_256bit_PLL_VCO
    WREG    0xBF201674, 0x0809
    DELAYUS     1000
.endif

                                    //DSP PLL
    WREG    0xBF221884, 0x0001      //MPLL enable
    WREG_B  0xBF22188C, 0x3f        //DSPPLL_VCO_OUT =~ 378 MHz

                                    //LVDS PLL
    WREG    0xBF221904, 0x0000      //LVDS_PLL_VCO_OUT =~ 432 MHz

    #//Module: usb0 (0x1007)
    WREG_B  0xBF200E00, 0x0a        #//Disable MAC initial suspend, Reset UHC
    WREG_B  0xBF200E00, 0x28        #//Release UHC reset, enable UHC and OTG XIU function

    #//Module: utmi (0x103A)
    WREG    0xBF207544, 0x5088	    #// PLL_TEST[30:28]: 3'b101 for IBIAS current select
                                    #// PLL_TEST[23] CLK480 to digital output source selection
    WREG    0xBF207540, 0x8051      #// PLL_TEST[15]: Bypass 480MHz clock divider
                                    #// PLL_TEST[7:4]: 5'b0101_0 for 1.0x
                                    #// PLL_TEST[0]: 1: synthesizer clock, 2'b11, 0: XIN_C

    WREG    0xBF207504, 0x2084      #//Enable CLK12_SEL bit <2> for select low voltage crystal clock
    WREG    0xBF207510, 0x0000      #//#7=0 Enable band-gap current  #3=0 Disable force_pll_on
    WREG    0xBF207500, 0x6bc3      #//reg_pdn: bit<15>, bit <2> ref_pdn # Turn on reference voltage and regulator
    DELAYUS     1000

    WREG    0xBF207500, 0x69c3      #//Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000

    WREG    0xBF207500, 0x0001      #//Turn all (including hs_current) use override mode

    #//Module: usb1 (0x1007)
    WREG_B  0xBF200F00, 0x0a        #//Disable MAC initial suspend, Reset UHC
    WREG_B  0xBF200F00, 0x28        #//Release UHC reset, enable UHC and OTG XIU function

    #//Module: utmi1 (0x103A)
    WREG    0xBF207444, 0x5088      #// PLL_TEST[30:28]: 3'b101 for IBIAS current select
                                    #// PLL_TEST[23] CLK480 to digital output source selection
    WREG    0xBF207440, 0x8051      #// PLL_TEST[15]: Bypass 480MHz clock divider
                                    #// PLL_TEST[7:4]: 5'b0101_0 for 1.0x
                                    #// PLL_TEST[0]: 1: synthesizer clock, 2'b11, 0: XIN_C

    WREG    0xBF207404, 0x2084      #//Enable CLK12_SEL bit <2> for select low voltage crystal clock
    WREG    0xBF207410, 0x0000      #//Enable band-gap current
    WREG    0xBF207400, 0x6bc3      #//reg_pdn: bit<15>, bit <2> ref_pdn  # Turn on reference voltage and regulator
    DELAYUS     1000

    WREG    0xBF207400, 0x69c3      #//Turn on UPLL, reg_pdn: bit<9>
    DELAYUS     2000

    WREG    0xBF207400, 0x0001      #//Turn all (including hs_current) use override mode

    # USBC2 <--> UTMI2
            WREG_B 0xBF227000, 0x0a     # Disable MAC initial suspend, Reset UHC
            WREG_B 0xBF227000, 0x68     # Release UHC reset, enable UHC and OTG XIU function

            WREG 0xBF207244, 0x5088     # Set PLL_TEST[23:21] for enable 480MHz clock
#if 0
            WREG_B 0xBF207240, 0x03     # Set PLL_TEST[1] for PLL multiplier 20X
            WREG_B 0xBF207242, 0x80     # To have accurate 480MHz
#else
            WREG   0xBF207240, 0x8051
#endif
            WREG   0xBF207204, 0x2084   # Enable CLK12_SEL bit <2> for select low voltage crystal clock
            WREG   0xBF207210, 0x0000   # Enable band-gap current
            WREG   0xBF207200, 0x6bc3   # reg_pdn: bit<15>, bit <2> ref_pdn  # Turn on reference voltage and regulator
            DELAYUS 1000

            WREG   0xBF207200, 0x69c3   # Turn on UPLL, reg_pdn: bit<9>
            DELAYUS 2000

            WREG   0xBF207200, 0x0001   # Turn all (including hs_current) use override mode


    jr      $31
    nop

.if (EMMC_BOOT == 1)
#-------------------------------------------------------------------------------------------------
# BOOT_CopyHeader_EMMC
# @param  None
# @return None
# @note   Copy Chunk Header from EMMC to DRAM
#-------------------------------------------------------------------------------------------------
EMMC_HEADER_SIZE = 0x0002                               # Size = 1KB
EMMC_HEADER_ADDR = 0x80200000
BOOT_CopyHeader_EMMC:
    li       $11, (EMMC_HEADER_ADDR >> 3)
    li       $10, EMMC_HEADER_SIZE                      # BLOCK CNT

    lui      $8, (REG_MIU_ADDR_L >> 16)
    srl      $9, $11, 16
    sw       $9, ( (REG_MIU_ADDR_L & 0xFFFF)-4 )($8)    # Load miu address high nibble
    and      $9, $11, 0xFFFF
    sw       $9, (REG_MIU_ADDR_L & 0xFFFF)($8)          # Load low nibble

    lui      $8,  (REG_JOB_BL_CNT >> 16)
    sw       $10, (REG_JOB_BL_CNT & 0xFFFF)($8)

    STG2_BLK_R

    li      $15, EMMC_HEADER_ADDR
    lw      $8,  4($15)     # RAM_START
    lw      $9,  8($15)     # RAM_END
    sub     $10, $9, $8     # RAM_SIZE = RAM_END-RAM_START
    srl     $10, $10, 9     # SIZE = (RAM_SIZE/512)+1
    add     $10, $10, 1     # Convert byte size to sector count
    srl     $11, $8, 3      # RAM_START/miu_length convert to miu address
    lw      $14, 16($15)    # RAM_ENTRY
    jr      $31
    nop

.endif

.if (EMMC_BOOT == 1)
#-------------------------------------------------------------------------------------------------
# BOOT_CopyUboot_EMMC
# @param  None
# $11 : FCIE DMA ADDRESS
# $10 : JOB_BL_CNT
# @return None
# @note   Copy Uboot binary from EMMC to DRAM
#-------------------------------------------------------------------------------------------------
EMMC_MAX_BLK_CNT  = 4095
BOOT_CopyUboot_EMMC:

    lui      $8, (REG_MIU_ADDR_L >> 16)
    srl      $9, $11, 16
    sw       $9, ( (REG_MIU_ADDR_L & 0xFFFF)-4 )($8)    # Load high nibble
    and      $9, $11, 0xFFFF
    sw       $9, (REG_MIU_ADDR_L & 0xFFFF)($8)          # Load low nibble

    bgt      $10, EMMC_MAX_BLK_CNT, GRT_MAX_CNT
    nop
    lui      $8,  (REG_JOB_BL_CNT >> 16)
    sw       $10, (REG_JOB_BL_CNT & 0xFFFF)($8)
    lui      $10, 0
    j        SEND_STG2_BLK
    nop

GRT_MAX_CNT:
    WREG     REG_JOB_BL_CNT, EMMC_MAX_BLK_CNT
    sub      $10, EMMC_MAX_BLK_CNT

SEND_STG2_BLK:
    STG2_BLK_R
    beqz     $10, SEND_BLK_END
    nop
    RREG     $9, REG_JOB_BL_CNT
    srl      $9, 9
    add      $11, $9
    j        BOOT_CopyUboot_EMMC
    nop

SEND_BLK_END:
    WREG     REG_BOOT_CONFIG, 0x0002                   # Set EMMC boot operation end

    jr      $31
    nop

.else
#-------------------------------------------------------------------------------------------------
# BOOT_CopyBootRAM
# @param  None
# @return None
# @note   Copy bootram from ROM to DRAM
#-------------------------------------------------------------------------------------------------
BOOT_CopyBootRAM:

.if (BOOT_COPY_VIA_DMA == 1)

    la      $8, _ld_bootram_ROM_start
    la      $9, _ld_bootram_RAM_start
    la      $10, _ld_bootram_RAM_end

    and     $8, ~0xBFC00000
    and     $9, ~0xA0000000
    and     $10, ~0xA0000000

    li      $12, REG_SFSH_DMA_SIZE_L
    sub     $13, $10, $9
    add     $13, $13, SFSH_DMA_ALIGN-1
    and     $13, $13, ~(SFSH_DMA_ALIGN-1)
    and     $14, $13, 0xffff
    sw      $14, 0($12)
    li      $12, REG_SFSH_DMA_SIZE_H
    srl     $14, $13, 0x10
    sw      $14, 0($12)

    li      $12, REG_SFSH_DMA_DRAMSTART_L
    add     $13, $9, 0
    and     $14, $13, 0xffff
    sw      $14, 0($12)
    li      $12, REG_SFSH_DMA_DRAMSTART_H
    srl     $14, $13, 0x10
    sw      $14, 0($12)

    li      $12, REG_SFSH_DMA_SPISTART_L
    add     $13, $8, 0
    and     $14, $13, 0xffff
    sw      $14, 0($12)
    li      $12, REG_SFSH_DMA_SPISTART_H
    srl     $14, $13, 0x10
    sw      $14, 0($12)

    WREG    REG_SFSH_DMA_CMD, (1<<5)        #[0] trigger, [5]0: little-endian 1: big-endian
    WREG    REG_SFSH_DMA_CMD, ((1<<5) | 1)    #trigger

1:
    li      $12, REG_SFSH_DMA_STATE
    lw      $26, 0($12)
    and     $26, 0x2 #finished
    beqz    $26, 1b
    nop

.else

    la      $8, _ld_bootram_ROM_start
    la      $9, _ld_bootram_RAM_start
    and     $9, ~0xE0000000
    or      $9, 0xA0000000
    la      $10, _ld_bootram_RAM_end
    and     $10, ~0xE0000000
    or      $10, 0xA0000000

1:
    ld      $11, 0($8)      #ld=lw lw to save time
    ld      $13, 8($8)
    sd      $11, 0($9)
    sd      $13, 8($9)
    addu    $8, $8, 16
    addu    $9, $9, 16
    bltu    $9, $10, 1b
    nop

.endif

    jr      $31
    nop

.endif

#-------------------------------------------------------------------------------------------------
# BOOT_EnableAccessMIU
# @param  None
# @return None
# @note   Enable to access MIU
#-------------------------------------------------------------------------------------------------
BOOT_EnableAccessMIU:
    # swch 3 # comment by auto MSTV2TRACE32

    WREG   0xBF005788 , 0x0004
    WREG   0xBF00578C , 0x3c11
    WREG   0xBF005790 , 0x0010
    WREG   0xBF005794 , 0x403c
    WREG   0xBF005798 , 0x0101
    #WREG_B 0xBF200DE1 , 0x40

    jr      $31
    nop

#-------------------------------------------------------------------------------------------------
# BOOT_InitUART_FPGA
# @param  None
# @return None
# @note   Init UART
#-------------------------------------------------------------------------------------------------
BOOT_InitUART_FPGA:
#if 0
#T4
        WREG_L 0xbf003d54 0x0014   #  select UART0 to MIPS
        WREG   0xbf003c04 0x0400   #  UART0 rx_enable
        WREG   0xbf201308 0x00C7   # Reset receiver and transmiter UART_REG8[UART_FCR] = UART_FCR_ENABLE_FIFO | UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT | UART_FCR_TRIGGER_14;
        WREG   0xbf201304 0x0000   # Interrupt Enable Register: UART_REG8[UART_IER] = 0;
        WREG   0xbf20130C 0x0003   # Set 8 bit char, 1 stop bit, no parity UART_LCR_WLEN8 & ~(UART_LCR_STOP2 | UART_LCR_PARITY);

    # /* Set baud rate */
        WREG    0xbf20130C  0x0083
        WREG_L  0xbf201300  UART_DIVISOR
        WREG_L  0xbf201304  UART_DIVISOR_H
        WREG    0xbf20130C  0x0003
#else
#T3
        WREG 0xbf001c24 0x0800
        WREG 0xbf203d4c 0x2104
        WREG 0xbf203d50 0x0005

        WREG 0xbf201310 0x0001

        WREG 0xbf201318 0x0083
        WREG 0xbf201308 0x0000
        WREG 0xbf201300 0x0013

        //WREG 0xbf201310 0x0007

        WREG 0xbf201318 0x0003
        //WREG 0xbf201310 0x0000
        //WREG 0xbf201310 0x0007
#endif
        jr      $31
        nop

#-------------------------------------------------------------------------------------------------
BOOT_EnableExternalizeSync:
     mfc0    $8, $16, 7
     or      $8, $8, 0x100
     mtc0    $8, $16, 7

    jr      $31
    nop

#-------------------------------------------------------------------------------------------------
# BOOT_InitUART
# @param  None
# @return None
# @note   Init UART
#-------------------------------------------------------------------------------------------------
BOOT_InitUART:
    WREG (CLK_GEN0_BASE+0x13*4), 0x0C01     # 123Mhz
.if (UART0==1)
#   WREG    0xbf001c24	0x0000 # clear register as Chakra
#   WREG    0xbf001c24	0x0800
    #enable reg_uart_rx_enable
    RREG    $11,        0xbf001c24
    ori     $11, $11,   0x0800
    sw      $11,        0xbf001c24

#   WREG 0xbf203d4c 0x2104
    #Select to PIU_UART0
    RREG    $11,        0xbf203d4c
    ori     $11, $11,   0x0004
    sw      $11,        0xbf203d4c
.endif

.if (UART0==0)
##   Select UART2 source
    WREG    0xbf203d4c  0x0400
    WREG    0xbf203d50  0x0000
    #10: RX2/TX2 uses PAD_DDCR_DA2/PAD_DDCR_CK2
    RREG    $11,        0xbf203c08
    ori     $11, $11,   0x0800
    sw      $11,        0xbf203c08

    RREG    $11,        0xbf203c08
    and     $11, $11,   0xFBFF
    sw      $11,        0xbf203c08
.endif

    RREG    $11,         0xbf201318   # Divisor Latch Access;
    ori     $11, $11,    0x0080       # 1: The divisor latches can be accessed
    sw      $11,         0xbf201318

    WREG 0xbf201300 UART_DIVISOR_L
    WREG 0xbf201308 UART_DIVISOR_H

    RREG    $11,         0xbf201318    # Kernel need
    and     $11, $11,    0xFF7F
    sw      $11,         0xbf201318

    WREG 0xbf201310      0x0000        # Kernel need
    WREG 0xbf201310      0x0007

    WREG 0xbf201318      0x0000        # Kernel need
    WREG 0xbf201318      0x0003
    WREG 0xbf201320      0x0000        # Kernel need
    WREG 0xbf201308      0x0000        # Kernel need


    DPUTK 'U'
    DPUTK 'A'
    DPUTK 'R'
    DPUTK 'T'
    DPUTK '_'
    DPUTK '1'
    DPUTK '1'
    DPUTK '5'
    DPUTK '2'
    DPUTK '0'
    DPUTK '0'

    #PUTK '\n'
    #PUTK '\r'


    jr      $31
    nop
