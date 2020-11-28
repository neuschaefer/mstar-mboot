################################################################################
#
# Copyright (c) 2006-2010 MStar Semiconductor, Inc.
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

#ifndef _ArchDefs_h_
#include "ArchDefs.h"
#endif

#define icache_size		        t3
#define icache_linesize		    t2
#define dcache_size		        t1
#define dcache_linesize		    t0

    .text
	.set    	noreorder
    .global     BootRomInitCache
    .ent        BootRomInitCache

BootRomInitCache:

    move        k0, ra

    bal         sys_init_cache
    nop

    bal         SysInitPrefetchBuffer
    nop

    jr           k0
    nop

    .size       BootRomInitCache,.-BootRomInitCache
    .end        BootRomInitCache

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

	j           icache_linesize_mips
	nop

	/* Unknown CPU */
icache_linesize_zero:
	jr	        ra
	move	    v0, zero

icache_linesize_mips:

	/* Read CONFIG1 register, which holds implementation data */
	MFC0_SEL_OPCODE( R_t9, R_C0_Config1, R_C0_SelConfig1 )

	/* I-cache line size */
	and	        t9, M_Config1IL
	beqz	    t9, icache_linesize_zero
	nop

	srl	        t9, S_Config1IL
	li	        v0, 0x2
	jr	        ra
	sll	        v0, t9

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

	j           icache_lines_mips
	nop

	/* Unknown CPU */
icache_lines_zero:
	jr	        ra
	move	    v0, zero

icache_lines_mips:

	/* Read CONFIG1 register, which holds implementation data */
	MFC0_SEL_OPCODE( R_t9, R_C0_Config1, R_C0_SelConfig1 )

	/* I-cache lines
	 * Calculated as associativity * sets per way
	 */
	and	        t8, t9, M_Config1IA
	srl	        t8, S_Config1IA
	addiu	    t8, 1				/* t8 = associativity	*/

	and	        t9, M_Config1IS
	srl	        t9, S_Config1IS
	li	        t7, 0x40
	sll	        t7, t9				/* t7 = sets per way	*/

	multu	    t8, t7

	jr	        ra
	mflo        v0
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

	j           dcache_linesize_mips
	nop

	/* Unknown CPU */
dcache_linesize_zero:
	jr	        ra
	move	    v0, zero

dcache_linesize_mips:

	/* Read CONFIG1 register, which holds implementation data */
	MFC0_SEL_OPCODE(R_t9, R_C0_Config1, R_C0_SelConfig1)

	/* D-cache line size */
	and	        t9, M_Config1DL
	beqz	    t9, dcache_linesize_zero
	nop

	srl	        t9, S_Config1DL
	li	        v0, 0x2
	jr	        ra
	sll	        v0, t9
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

	j           dcache_lines_mips
	nop

	/* Unknown CPU */
dcache_lines_zero:
	jr	        ra
	move	    v0, zero

dcache_lines_mips:

	/* Read CONFIG1 register, which holds implementation data */
	MFC0_SEL_OPCODE( R_t9, R_C0_Config1, R_C0_SelConfig1 )

	/* D-cache lines
	 * Calculated as associativity * sets per way
	 */
	and	        t8, t9, M_Config1DA
	srl	        t8, S_Config1DA
	addiu	    t8, 1				/* t8 = associativity	*/

	and	        t9, M_Config1DS
	srl	        t9, S_Config1DS
	li	        t7, 0x40
	sll	        t7, t9				/* t7 = sets per way	*/

	multu	    t8, t7

	jr	        ra
	mflo        v0
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

	beq         a0, zero, 9f		 /* just in case cache size = 0 */
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
#	li	        a2, KSEG0BASE
	li	        a2, KSEG1BASE


	/* Calc an address that will correspond to the last cache line  */
	addu	    a3, a2, a0
	subu        a3, a1

	/* Loop through all lines, invalidating each of them */
1:
SET_MIPS3()
	cache	    ICACHE_INDEX_STORE_TAG, 0(a2)	/* clear tag */
SET_MIPS0()
	bne	        a2, a3, 1b
	addu	    a2, a1

9:
	jr	        ra
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

#	b	        0f
#	nop

init_dcache_dtaghilo:
	MTC0_SEL_OPCODE( R_zero, R_C0_DTagHi, R_C0_SelDTagHi )
init_dcache_dtaglo:
	MTC0_SEL_OPCODE( R_zero, R_C0_DTagLo, R_C0_SelDTagLo )

0:
	/* Calc an address that will correspond to the first cache line */
#	li	        a2, KSEG0BASE
	li	        a2, KSEG1BASE

	/* Calc an address that will correspond to the last cache line  */
	addu	    a3, a2, a0
	subu        a3, a1

	/* Loop through all lines, invalidating each of them */
1:
SET_MIPS3()
	cache	    DCACHE_INDEX_STORE_TAG, 0(a2)	/* clear tag */
SET_MIPS0()
	bne	        a2, a3, 1b
	addu	    a2, a1

9:
	jr	        ra
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

	move	    t4, ra

	move	    a0, k1

	/*
	 * MIPSCMP
	 * if v1!=0 this is a secondary CPU,
	 * so don't initialise secondary cache again

	bnez	    v1, 1f
	nop
	 */


	/*
	 * MIPSCMP
	 * by definition only CPU 0 initialises the L2 cache, so
	 * reset the value of v1
	 */
	move	    v1, zero

1:
	/* L1 cache */

	bal	        sys_determine_icache_linesize_flash
	nop
	move	    icache_linesize, v0

	bal	        sys_determine_icache_lines_flash
	nop
	multu	    icache_linesize, v0
	mflo	    icache_size

	bal	        sys_determine_dcache_linesize_flash
	nop
	move	    dcache_linesize, v0

	bal	        sys_determine_dcache_lines_flash
	nop
	multu	    dcache_linesize, v0
	mflo	    dcache_size

	beq	        icache_size, zero, 1f
	nop
	beq	        dcache_size, zero, 1f
	nop

	/* Initialise instruction cache */
	move	    a0, icache_size
	move	    a1, icache_linesize
	bal	        sys_init_icache
	move	    a2, k1

	/* Initialise data cache */
	move	    a0, dcache_size
	move	    a1, dcache_linesize
	bal	        sys_init_dcache
	move	    a2, k1

	MFC0(v0, C0_Config)
	and	        v0, ~M_ConfigK0
	or	        v0, K_CacheAttrCN
	MTC0(v0, C0_Config)

	/* Done */
	jr	        t4
	move	    v0, zero

	/* D-cache or I-cache has size 0,  set CPU uncached */
1:
	MFC0(v0, C0_Config)
	and	        v0, ~M_ConfigK0
	or	        v0, K_CacheAttrU
	MTC0(v0, C0_Config)

	/* Done */
	jr	        t4
	move	    v0, zero

END(sys_init_cache)

#-------------------------------------------------------------------------------------------------
# SysInitPrefetchBuffer
# @param  None
# @return None
# @note   L2 cache initialization
#-------------------------------------------------------------------------------------------------
LEAF(SysInitPrefetchBuffer)

#ifdef CONFIG_MSTAR_FORCE_REQUEST_INTO_CACHE
    lw          t1, 0xBF203100
    nop
    or          t1, t1, (0x01 << 2)             #//0x101840[2]: Force all MIU request are cacheable
    sw          t1, 0xBF203100
    nop   
#endif

#ifndef CONFIG_MSTAR_CPU_PREFETCH_ENABLE

    #//Set 0x101843[1] = 0
    lw          t1, 0xBF20310C
    nop
    and         t1, t1, ~(1 << 1)
    sw          t1, 0xBF20310C
    nop

    #//Set 0x101849[5:0] = 0x01
    lw          t1, 0xBF203124
    nop
    and         t1, t1, ~(0x3F)
    or          t1, t1, 1                   #//0x101849[5:0]: Start to access MIU0 when request number meet threshold
    sw          t1, 0xBF203124
    nop

    #//Set 0x10184B[5:0] = 0x01
    lw          t1, 0xBF20312C
    nop
    and         t1, t1, ~(0x3F)
    or          t1, t1, 1                   #//0x10184B[5:0]: Start to access MIU1 when request number meet threshold
    sw          t1, 0xBF20312C
    nop

#else

    lw          t1, 0xBF20310C
    nop    
    or          t1, t1, (1 << 2)            #//0x101843[2]: Fast sync enable
#// and         t1, t1, ~(1 << 1)           #//0x101843[1]: Read request pack enable
    sw          t1, 0xBF20310C
    nop

    lw          t1, 0xBF203104
    nop
    and         t1, t1, ~(0x0F)
    or          t1, t1, (1 << 4)            #//0x101841[4]: Start to cache operation
    sw          t1, 0xBF203104
    nop

_CheckCacheActiveStatus:

    lw          t1, 0xBF203104
    nop
    and         t1, t1, (0x01 << 8)            #//0x101841[8]: Data Cache Active

    beqz        t1, _CheckCacheActiveStatus
    nop

    lw          t1, 0xBF203104
    nop
    and         t1, t1, ~(0x01 << 4)           #//0x101841[4]: Start to Cache Operation
    sw          t1, 0xBF203104
    nop

    lw          t1, 0xBF203100
    nop
    and         t1, t1, ~(0x01 << 1)           #//0x101840[1]: Data Cache Disable
    sw          t1, 0xBF203100
    nop

    lw          t1, 0xBF203124
    nop
    and         t1, t1, ~(0x3F)
    or          t1, t1, (0x01 << 0)            #//0x101849[5:0]: Start to access MIU0 when request number meet threshold
    sw          t1, 0xBF203124
    nop

    lw          t1, 0xBF20312C
    nop
    and         t1, t1, ~(0x3F)
    or          t1, t1, (0x01 << 0)            #//0x10184B[5:0]: Start to access MIU1 when request number meet threshold
    sw          t1, 0xBF20312C
    nop

    lw          t1, 0xBF203100
    nop
    and         t1, t1, ~(0x03 << 4)
#ifdef CONFIG_MSTAR_TITANIA_L2_CACHE_LINE_64_BYTES    
    or          t1, t1, (0x01 << 4)            #//0x101840[5:4]: Data Buffer Cache Line Size 0: 32-bytes    1: 64-bytes   
#endif    
    sw          t1, 0xBF203100
    nop

    li          t1, 0x2FFF                     #//0x101850[15:0]: Wait write data for pack timeout
    sw          t1, 0xBF203140
    nop

    lw          t1, 0xBF203160
    nop
    and         t1, t1, ~(0x01 << 0)           #//0x101858[0]: Clear miu request count
    sw          t1, 0xBF203160
    nop

    lw          t1, 0xBF20314C
    nop
    or          t1, t1, (0x01 << 4)            #//0x101853[4]: Latch OCP bus enable
    or          t1, t1, (0x01 << 0)            #//0x101853[0]: Latch OCP address/data  0: read,  1: wrtie
    sw          t1, 0xBF20314C
    nop

#endif

#ifdef CONFIG_MSTAR_MEMORY_PREFETCH_ENABLE

    lw          t1, 0xBF203104
    nop
    or          t1, t1, 0x0F                    #//0x101841[3:0]: Cache Operation Mode: 0x0F: Memory Prefetch Mode
    sw          t1, 0xBF203104
    nop

    lw          t1, 0xBF203100
    nop
    or          t1, t1, (0x01 << 12)            #//0x101840[12]: Memory Prefetch Enable
    sw          t1, 0xBF203100
    nop
    
    lw          t1, 0xBF203104
    nop
    or          t1, t1, 0x10                    #//0x101841[4]: Start to cache operation
    sw          t1, 0xBF203104
    nop

#endif

    jr          ra
    nop

END(SysInitPrefetchBuffer)

