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
#include "autoconf.h"
#include "drv_miu_init.h"
#include "MIUSEL_K1_2MIU.h"
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
# sys_init_L2_cache
# @param  None
# @return None
# @note   L2 cache initialization
#-------------------------------------------------------------------------------------------------
#//sys_init_L2_cache:
LEAF( sys_init_L2_cache )



 // turn OFF L2 init for T8 bring up status

    lw          t1, 0xBF20310C
    nop
    or          t1, t1, (1 << 2)            #//0x101843[2]: Fast sync enable
#// or          t1, t1, (1 << 3)
    and         t1, t1, ~(1 << 1)           #//0x101843[1]: Read request pack enable
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
    and         t1, t1, (1 << 8)            #//0x101841[8]: L2 cache active

    beqz        t1, _CheckCacheActiveStatus
    nop

    lw          t1, 0xBF203104
    nop
    and         t1, t1, ~(1 << 4)           #//0x101841[4]: Start to cache operation
    sw          t1, 0xBF203104
    nop

    lw          t1, 0xBF203100
    nop
    and         t1, t1, ~(1 << 1)           #//0x101840[1]: L2 cache disable
    sw          t1, 0xBF203100
    nop

    lw          t1, 0xBF203124
    nop
    and         t1, t1, ~(0x0000003F)
    #or          t1, t1, (1 << 0)            #//0x101849[5:0]: Start to access MIU0 when request number meet threshold
    or          t1, t1, (1 << 2)            #//0x101849[5:0]: Start to access MIU0 when request number meet threshold
    sw          t1, 0xBF203124
    nop

    lw          t1, 0xBF20312C
    nop
    and         t1, t1, ~(0x0000003F)
    or          t1, t1, (1 << 0)            #//0x10184B[5:0]: Start to access MIU1 when request number meet threshold
    sw          t1, 0xBF20312C
    nop

    lw          t1, 0xBF203100
    nop
    or          t1, t1, (1 << 4)            #//0x101840[4]: L2 cache line size 0: 32-bytes    1: 64-bytes
    or          t1, t1, (1 << 7)            #//0x101840[4]: L2 cache line size 0: 32-bytes    1: 64-bytes
    or          t1, t1, (1 << 12)            #//0x101840[4]: L2 cache line size 0: 32-bytes    1: 64-bytes
    or          t1, t1, (1 << 13)            #//0x101840[4]: L2 cache line size 0: 32-bytes    1: 64-bytes
    sw          t1, 0xBF203100
    nop

    lw          t1, 0xBF20310c
    nop
    or          t1, t1, (1 << 0)            #//0x101843[0]: Write through enable when write hit
    sw          t1, 0xBF20310c
    nop

    #li          t1, 0x2FFF                  #//0x101850[15:0]: Wait write data for pack timeout
    li          t1, 0x07FF                  #//0x101850[15:0]: Wait write data for pack timeout
    sw          t1, 0xBF203140
    nop

    lw          t1, 0xBF203160
    nop
    and         t1, t1, ~(1 << 0)           #//0x101858[0]: Clear miu request count
    sw          t1, 0xBF203160
    nop

    lw          t1, 0xBF20314C
    nop
    or          t1, t1, (1 << 4)            #//0x101853[4]: Latch OCP bus enable
    or          t1, t1, (1 << 0)            #//0x101853[0]: Latch OCP address/data  0: read,  1: wrtie
    sw          t1, 0xBF20314C
    nop


    jr          ra
    nop

END( sys_init_L2_cache )

#-------------------------------------------------------------------------------------------------
# sys_init_fpu
# @param  None
# @return None
# @note   CP1 FPU initialization
#-------------------------------------------------------------------------------------------------
#sys_init_fpu:
LEAF( sys_init_fpu )

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
END( sys_init_fpu )


#-------------------------------------------------------------------------------------------------
# BOOT_Entry:
# @param  None
# @return None
# @note   Entry point of Boot code
#-------------------------------------------------------------------------------------------------
    .globl  BOOTROM_Entry
BOOTROM_Entry:

ecb_setting:                                        # same as T3 U02 setting
    WREG  0xbf203184, READ_DATA_HITABLE_BURST_SIZE  # 0x01, Read Data hitable/burst size
    WREG  0xbf203188, READ_INST_HITABLE_BURST_SIZE  # 0x02, Read Instruction hitable/burst size
    WREG  0xbf20318C, WRITE_BUFFER_TIMEOUT          # write buffer flush timeout
    WREG  0xbf203190, WRITE_BUFFER_THRESHOLD        # write buffer threshhold <-- 6 level

    DBGREG  0x0004

entry_continue0:
    # Configure PAD top for MUX and GPIO (e.g. DDR power)
    lui     $4,%hi(padInitTbl+10)
    bal     MDrv_WriteRegMaskTbl
    ori     $4,%lo(padInitTbl+10)

    DBGREG  0x0005

    # Enable MSTV_TOOL to access MIU
    bal     BOOT_EnableAccessMIU
    nop

    DBGREG  0x0006

    # Power On Sequence
    bal     BOOT_PowerOnSeq
    nop

    DBGREG  0x0007

.if ( ENABLE_TLB_SHARE == 1 )
    # Enable TLB Share
    bal     BOOT_EnableTLBShare
    nop
.endif

    # Copy bootram from ROM to DRAM
    bal     BOOT_CopyBootRAM
    nop

    DBGREG  0x0008

    # Jump to BootRam_Entry
    la      $31, BOOTRAM_Entry
    j       $31
    nop


#-------------------------------------------------------------------------------------------------
# CPU_InitDSPRAM_34K
# @param  None
# @return None
# @note   Power On Sequence for Chip
#-------------------------------------------------------------------------------------------------
CPU_InitDSPRAM_34K:
        #.set push
        #.set noreorder
        li      $4, ERRCTL_SPR
        mtc0    $4, $26                             #Set ErrCtl[SPR]
        li      $4, A_DSPRAM
        li      $5, TAG_SPRAM_EN
        or      $4, $4, $5                          #paddr | en
        mtc0    $4, $28, 2                          #move to TagLo1
        #ehb                                         #
        li      $4, DSPRAM_VBASE
        cache   Index_Store_Tag_D,0($4)   #store tag to SPRAM
        mtc0    $0, $26                         #Clear ErrCtl[SPR]
        #ehb
        #.set pop

        jr $31
        nop

#-------------------------------------------------------------------------------------------------
# BOOT_PowerOnSeq
# @param  None
# @return None
# @note   Power On Sequence for Chip
#-------------------------------------------------------------------------------------------------
BOOT_PowerOnSeq:
    move    $27, $31
    bal     BOOTROM_MPLL_INIT
    nop

    DBGREG  0x0010

    bal     BOOTROM_CLK_GEN0_DVBT_INIT
    nop

    # stb_dc
    # K1 U01, wriu -b 0x103d9f  0xc0 0xc0 // Pass dc2mvd_vsync - 11 : every opvs
    # K1 U02, set b'00
    RREG    $11,                    0xbf203600      #read MVD version
    bne     $11, 0xD050,            1f              # for other than U01
    nop
    WREG    0xbf207b3c,             0xC000          # for U01 only
    b                               2f
    nop
1:
    WREG    0xbf207b3c,             0x0000
2:

    DBGREG  0x0011

    DELAYUS  100
    # Init UART
    bal     BOOT_InitUART
    nop

    DBGREG  0x0012

    # For patch Kronus 34K bug, need to init DSPRAM to bus address 128MB
    # Intialize DSPRAM
    # K1 DSPRAM default to 0xddd58000, no need to set in mboot
    # bal CPU_InitDSPRAM_34K
    # nop

    bal     BOOTROM_MIU_INIT
    nop

    DBGREG  0x0013

    bal     sys_init_cache
    nop



    bal     sys_init_L2_cache
    nop

    bal     sys_init_fpu
    nop

.if 1
	/* Caches have now been initialised, so shift to kseg0 */
	la	t0, 1f
	KSEG0A( t0)
	j	t0
	nop
1:
.endif

    DBGREG  0x0014

   #Init EMAC clk
    WREG  0xbf203d40, 0x0000 # emac out pad

    bal	    BOOTROM_MCU_INIT  #with OCP and MIPS speed up
    nop

    DBGREG  0x0015

    bal     SPI_CLK
    nop

    DBGREG  0x0016

    lui     $4,%hi(padInitTbl+10)
    bal     MDrv_WriteRegMaskTbl
    ori     $4,%lo(padInitTbl+10)

    DBGREG  0x0017

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

    WREG_B 0xBF001C81 , 0x10 #step 1/2:set SPI clkgen to 54M
    WREG_B 0xBF001C81 , 0x50 #step 2/2:release SPI_clk from XTAL to clock gen (above line)

    WREG_B 0xBF001C80 , 0x18 #step 1/2:set MCU clkgen to 108M
    WREG_B 0xBF001C80 , 0x98 #step 2/2:release reg_sw_mcu_clk from XTAL to clock gen (above line)

    jr      $31
    nop

#-------------------------------------------------------------------------------------------------
# BOOTROM_MCU Clock init
# @param  None
# @return None
# @note   do MCU Clock init
#-------------------------------------------------------------------------------------------------
BOOTROM_MCU_INIT:

.if (CPU_CLOCK>=252)
    WREG_B  0xBF203a3c, 0x50 # ocp 1:1
    DELAYUS 20000
    WREG_B  0xBF203a3c, 0x51 # fire
    DELAYUS 20000
    WREG_B  0xBF203a3c, 0x20 # ocp 1:2
    DELAYUS 20000
    WREG_B  0xBF203a3c, 0x21 # fire

    #WREG_B  0xBF203a3c, 0x30 # ocp 1:3
    #DELAYUS 20000
    #WREG_B  0xBF203a3c, 0x31 # fire

    DELAYUS 20000
.endif

    WREG_B 0xBF201644, 0x00 #turn OCP clk

.if (CPU_CLOCK>12)
    # switch to clk_mipspll_vco
    WREG_B 0xBF201645, 0x00
    WREG_B 0xBF201645, 0x80  # trigger
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

    #include "script_clk_gen.S"
    
    RREG    $11, (REG_ADDR_BASE + (0x001E02 <<1 ))
    andi    $11, $11, 0x0C00
    beqz    $11, CLK_GEN0_DONE

    WREG    (REG_ADDR_BASE + (0x100b3e <<1 )) , 0x0018

CLK_GEN0_DONE:
    #<<SPI>>
    WREG_B  0xBF201658, 0x10     # 54MHz
    WREG_B  0xBF201658, 0x30     # clk_spi by glitch-free clock switch

    jr      $31
    nop





#-------------------------------------------------------------------------------------------------
# the function of MIU_INIT
#-------------------------------------------------------------------------------------------------
T4_Miu0_Reset:
    WREG    (REG_ADDR_BASE + (0x10121e <<1 )) , 0x0000   #hold miu_0
    WREG    (REG_ADDR_BASE + (0x10121e <<1 )) , 0x0c01   #
    WREG    (REG_ADDR_BASE + (0x10121e <<1 )) , 0x0e00   #
    WREG    (REG_ADDR_BASE + (0x101202 <<1 )) , 0x0000   #

MaskMiu0AllGroup:
    WREG    (REG_ADDR_BASE + (0x1012f8 <<1 )) , 0x8000
    WREG    (REG_ADDR_BASE + (0x101246 <<1 )) , 0xFFFE   #Mask MIU0_group_0
    WREG    (REG_ADDR_BASE + (0x101266 <<1 )) , 0xFFFF   #Mask MIU0_group_1
    WREG    (REG_ADDR_BASE + (0x101286 <<1 )) , 0xFFFF   #Mask MIU0_group_2
    jr      $31
    nop
#--------------------------------------------------------
#--------------------------------------------------------
UnMaskMiu0AllGroup:
    WREG    (REG_ADDR_BASE + (0x101246 <<1 )) , 0x0000   #Mask MIU0_group_0
    WREG    (REG_ADDR_BASE + (0x101266 <<1 )) , 0x0000   #Mask MIU0_group_1
    WREG    (REG_ADDR_BASE + (0x101286 <<1 )) , 0x0000   #Mask MIU0_group_2
    jr      $31
    nop
#--------------------------------------------------------
#--------------------------------------------------------
AutoInitialMiuCycle:
    #auto initial MIU cycle
    WREG    0xBF202400 , 0x0000   #hold miu_0
    WREG    0xBF200C00 , 0x0000   #hold miu_1
    DELAYUS 200 #delay 200us

    //set ODT
    WREG    0xBF202400 , 0x0010   #hold miu_0
    WREG    0xBF200C00 , 0x0010   #hold miu_1

    WREG    0xBF202400 , 0x0018   # miu_0 #DRAM reset
    WREG    0xBF200C00 , 0x0018   # miu_1 DRAM reset

    WREG    0xBF202400 , 0x001C   #DRAmreset+DRAM chip select
    WREG    0xBF200C00 , 0x001C   # miu_1 DRAM reset

    DELAYUS 500 # delay 500us

    WREG    0xBF202400 , 0x001E   #DRAmreset+DRAM chip select+enable CKE
    WREG    0xBF200C00 , 0x001E

    DELAYUS 400 # delay 400us

    WREG    0xBF202400 , 0x001F   #0x001F #DRAmreset+DRAM chip select+enable CKE +auto initial dram cycle
    WREG    0xBF200C00 , 0x001F   #0x001F #DRAmreset+DRAM chip select+enable CKE +auto initial dram cycle
    jr      $31
    nop
#--------------------------------------------------------
#--------------------------------------------------------



#--------------------------------------------------------
#miu initial for MIU_1
#--------------------------------------------------------
.if ( ENABLE_MIU1 == 1 )
#====MIU_1 ___start___ ====================================
T4_Miu1_Reset:
    WREG    (REG_ADDR_BASE + (0x10061e <<1 )) , 0x0000   #hold miu_0
    WREG    (REG_ADDR_BASE + (0x10061e <<1 )) , 0x0c01   #
    WREG    (REG_ADDR_BASE + (0x10061e <<1 )) , 0x0e00   #
    WREG    (REG_ADDR_BASE + (0x100602 <<1 )) , 0x0000   #

.endif

MaskMiu1AllGroup:
    WREG    (REG_ADDR_BASE + (0x1006f8 <<1 )) , 0x8000
    WREG    (REG_ADDR_BASE + (0x100646 <<1 )) , 0xFFFE   #Mask MIU0_group_0
    WREG    (REG_ADDR_BASE + (0x100666 <<1 )) , 0xFFFF   #Mask MIU0_group_1
    WREG    (REG_ADDR_BASE + (0x100686 <<1 )) , 0xFFFF   #Mask MIU0_group_2
    jr      $31
    nop
#--------------------------------------------------------
#--------------------------------------------------------
UnMaskMiu1AllGroup:
    WREG    (REG_ADDR_BASE + (0x100646 <<1 )) , 0x0000   #Mask MIU0_group_0
    WREG    (REG_ADDR_BASE + (0x100666 <<1 )) , 0x0000   #Mask MIU0_group_1
    WREG    (REG_ADDR_BASE + (0x100686 <<1 )) , 0x0000   #Mask MIU0_group_2
    jr      $31
    nop

#--------------------------------------------------------
#--------------------------------------------------------


#====MIU_1 ___END___  ====================================


#--------------------------------------------------------
#--------------------------------------------------------


#-------------------------------------------------------------------------------------------------
# BOOTROM_MIU_INIT
# @param  None
# @return None
# @note   do MIU init
#-------------------------------------------------------------------------------------------------
BOOTROM_MIU_INIT:
    move    $15,$31

    DBGREG  0x0020

    bal     T4_Miu0_Reset
    nop
.if ( ENABLE_MIU1 == 1 )
    bal     T4_Miu1_Reset
    nop
.endif
    lui     $4,%hi(MIU0_DDR_Init)
    bal     MDrv_WriteRegTbl32
    ori     $4,%lo(MIU0_DDR_Init)

    DBGREG  0x0022

EnableMiu0:
    WREG    (REG_ADDR_BASE + (0x10121e <<1 )), 0x0c01

#if ( (MIU_INTERFACE == DDR3_INTERFACE_QFP) || (MIU_INTERFACE == DDR3_INTERFACE_QFP_128) || (MIU_INTERFACE == DDR3_INTERFACE_QFP_156) || (MIU_INTERFACE == DDR3_INTERFACE_BGA))
    WREG    (REG_ADDR_BASE + (0x10121e <<1 )), 0x0708   //DDR3-16 mode
#else
    WREG    (REG_ADDR_BASE + (0x10121e <<1 )), 0x0c08
#endif
    DELAYUS 100    # delay 100us
#.if (ENABLE_MIU1 == 0)
#    WREG    (REG_ADDR_BASE + (0x110d00 <<1 )), 0x0000
#.else
#if ( MIU_INTERFACE == DDR2_INTERFACE_QFP_128)
#elif (MIU_INTERFACE == DDR2_INTERFACE_QFP)
#elif ( MIU_INTERFACE == DDR3_INTERFACE_QFP)
#elif ( MIU_INTERFACE == DDR3_INTERFACE_QFP_128)
#elif ( MIU_INTERFACE == DDR3_INTERFACE_QFP_128_8BIT_MODE)
#elif ( MIU_INTERFACE == DDR3_INTERFACE_QFP_156)
#elif ( MIU_INTERFACE == DDR3_INTERFACE_QFP_156_8BIT_MODE)
#elif (MIU_INTERFACE == DDR2_INTERFACE_BGA)
#elif (MIU_INTERFACE == DDR3_INTERFACE_BGA)
#else
#if (ENABLE_MEM1066MHz)
    WREG    (REG_ADDR_BASE + (0x110d00 <<1 )), 0x0201
#else
    WREG    (REG_ADDR_BASE + (0x110d00 <<1 )), 0x0001
#endif
#endif
#.endif
    WREG    (REG_ADDR_BASE + (0x110d02 <<1 )), 0xAAAA

    DBGREG  0x0023

    lui     $4,%hi(MIU1_DDR_Init)
    bal     MDrv_WriteRegTbl32
    ori     $4,%lo(MIU1_DDR_Init)

    WREG    (REG_ADDR_BASE + (0x10061e <<1 )), 0x0c01
    WREG    (REG_ADDR_BASE + (0x10061e <<1 )), 0x0c08
    DELAYUS 100    # delay 100us
.if (ENABLE_MIU1 == 0)
    WREG    (REG_ADDR_BASE + (0x110d80 <<1 )), 0x0000
.else
    WREG    (REG_ADDR_BASE + (0x110d80 <<1 )), 0x0001
.endif
    WREG    (REG_ADDR_BASE + (0x110d82 <<1 )), 0xAAAA

    DBGREG  0x0024

    WREG    (REG_ADDR_BASE + (0x110d08 <<1 )), 0xffff   #rxenable
    WREG    (REG_ADDR_BASE + (0x110d88 <<1 )), 0xffff   #rxenable
    bal      AutoInitialMiuCycle
    nop
    DBGREG  0x0025


CheckMiu0Init:
    RREG    $9,(REG_ADDR_BASE + (0x101200 <<1 ))
    andi    $9 , $9, 0x8000
    beqz    $9 ,  CheckMiu0Init
    nop

    DBGREG  0x0026

.if ( ENABLE_MIU1 == 1 )
CheckMiu1Init:
    RREG    $9,(REG_ADDR_BASE + (0x100600 <<1 ))
    andi    $9 , $9, 0x8000
    beqz    $9 , CheckMiu1Init
    nop
.endif

    DBGREG  0x0027

#ifdef CONFIG_DDR_GOODPHASE_AUTOSCAN
#warning "Enable DDR_GOODPHASE_AUTOSCAN"
    WREG    (REG_ADDR_BASE + (0x101246 <<1 )) , 0x7FFE   #Mask MIU0_group_0
    bal     Miu0_AutoPhase
    nop
.if ( ENABLE_MIU1 == 1 )
    WREG    (REG_ADDR_BASE + (0x100646 <<1 )) , 0x7FFE   #Mask MIU0_group_0
    bal     Miu1_AutoPhase
    nop
.endif
#endif
    DBGREG  0x0028

    #bist test here
    bal     Miu0_BistTest
    nop
.if ( ENABLE_MIU1 == 1 )
    bal     Miu1_BistTest
    nop
.endif

    bal     UnMaskMiu0AllGroup  #open all miu_0 mask
    nop
#.if ( ENABLE_MIU1 == 1 )
    bal     UnMaskMiu1AllGroup  #open all miu_0 mask
    nop
    # all IP select MIU0 in bringup
    WREG    (REG_ADDR_BASE + (0x1006f0 <<1 )), 0x7fff
    WREG    (REG_ADDR_BASE + (0x1006f2 <<1 )), 0xffff
    WREG    (REG_ADDR_BASE + (0x1006f4 <<1 )), 0xffff
#.endif
    DBGREG  0x0029

    #WREG    (REG_ADDR_BASE + (0x101230 <<1 )) , 0x4000  # reg_adc_test_en for RASP1
    WREG    (REG_ADDR_BASE + (0x1012e0 <<1 )) , 0x0000  # stop bist test
    move    $31,$15
    jr      $31
    nop


#####  Setting for t3
#    bal     MIU_Init_Priority
#    nop
#    bal     MIU_Set_Group_Priority
#    nop
    #bist test here
#    bal     Miu0_AutoPhase
#    nop
#    bal     Miu1_AutoPhase
#    nop
#    WREG    0xBF2025E0 , 0x0000   #1012f0 bit_15=1 choice to MIU_1
#    bal     MIU_Mau_Memory_Arrange
#    WREG    0xBF20243C , 0x0c08 #reg_0x10121e#3 control all miu mask

#-------------------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------------------
Miu1_AutoPhase:
    WREG    0xBF2025E0 , 0x8000                      #1012f0 bit_15=1 choice to MIU_1
    li      $23, (REG_ADDR_BASE+(0x103394<<1))      # Dummy register to store miu1 DQS phase result
    li      $24, 0                                  # DQS phase result

    RREG    $9, (REG_ADDR_BASE+(0x110DEE<<1))       # store the default phase setting to r19
    move    $19, $9                                 #

    li      $11, (REG_ADDR_BASE+(0x110DEE<<1))      # reg_0x110DEE  //miu1_phase_reg
    li      $10, (REG_ADDR_BASE+(0x1006E7<<1))      # reg_0x1006e7  //miu1_dqs_mask_reg
    j       AutoPhaseLoop
    nop
Miu0_AutoPhase:
    WREG   0xBF2025E0 , 0x0000                      # 1012f0 bit_15=0 choice to MIU_0
    li      $23, (REG_ADDR_BASE+(0x103390<<1))      # Dummy register to store miu 0 DQS phase result
    li      $24, 0                                  # DQS phase result

    RREG    $9, (REG_ADDR_BASE+(0x110D6E<<1))       # store the default phase setting to r19
    move    $19, $9                                 #

    li      $11, (REG_ADDR_BASE+(0x110D6E<<1))      # reg_0x110D6E  //miu0_phase_reg
    li      $10, (REG_ADDR_BASE+(0x1012E7<<1))      # reg_0x1012e7  //miu0_dqs_mask_reg

AutoPhaseLoop:
    PUTK    '['

    WREG    (REG_ADDR_BASE+(0x1012e2<<1)), 0x1FFF   # 1012e2 bist test start address, (4K byte/unit)
    WREG    (REG_ADDR_BASE+(0x1012e4<<1)), 0x1000   # 1012e4~1012e7 bist test size,   (16 byte/unit)
    WREG    (REG_ADDR_BASE+(0x1012e6<<1)), 0x0000   # 1012e4~1012e7 bist test size,   (16 byte/unit)
    WREG    (REG_ADDR_BASE+(0x1012e8<<1)), 0x00FF   # 1012e4~1012e7 bist test pattern

    lui     $13,0                                   # $13-->tmp_var0=0;  for loop cnt
    lui     $21,0                                   # $21-->good_phase cnt
    lui     $20, 0                                  # $20-->good_phase_sum
    li      $25, 1                                  # $25-->good_phase bit

StartChk_x1:
    li      $9, 0x55
    sb      $9, (0)($10)            # set miu0_dqs_mask_reg to 0x55
check_x1:

    #ClockReset
    li      $14, (REG_ADDR_BASE+(0x110D0E<<1))
    lb      $26, (0)($14)
    andi    $26, $26, 0x9F
    ori     $26, $26, 0x60
    sb      $26, (0)($14)

    andi    $9, $13 ,0x0f
    sll     $9, $9 ,4
    andi    $8, $19, 0x0f           # set dqs0 delay phase to r8
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
    li      $9, 0xaa             # 1012e7/1006e7 =0xAA mask DQS_1 error when test DQS_0
    sb      $9, (0)($10)

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
    andi    $8, $19, 0xf0  # get the default phase setting
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

checkloop:
    sll     $25, $25, 1
    addiu   $13, $13, 1             # add loop cnt by 1
    bne	    $13, 16 , CheckLoopDone
    nop

    beqz    $21, SetToDefault_P1    # if good_phase cnt == 0
    nop
    move    $22, $20  #good_phase_sum
    div     $22, $22 , $21
    sll     $22, $22 , 4
    j       StorePhase_P1
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

    andi    $9,  $19 , 0x0f
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

CheckLoopDone:
    bltu    $13,16, check_x1
    nop
    bltu	$13,32, check_x0      #AutoPhaseLoop1
    sw      $24, (0)($23)         #store phase 0  result
    nop
    beqz    $21, SetToDefault_P0  # good_phase cnt == 0
    nop
    move    $22, $20  #good_phase_sum
    div     $22, $22 , $21
    #sll     $22, $22 , 4
    j       StorePhase_P0
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

    andi    $9,  $19 , 0xf0
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
    andi    $9,$19,0xf0
    srl     $9,$9,4
    bal     puthex
    nop
    andi    $9,$19,0x0f
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
    bltu    $9, 10 , putx0_9
    nop
putxA_F:
    addiu   $9 , $9, 0x37
    j       putx
    nop
putx0_9:
    addiu   $9 , $9, 0x30
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
    andi     $11, $11, 0xFEFF
    lui     $8,  (0xBF2025B8 >> 16)
    sw      $11, (0xBF2025B8 & 0xFFFF)($8)

    RREG    $11, 0xBF2025B8
    and     $11, $11, 0xFF00
    ori      $11, $11, (MIU0_GROUP_PRIORITY & 0xFF)
    lui     $8,  (0xBF2025B8 >> 16)
    sw      $11, (0xBF2025B8 & 0xFFFF)($8)

    RREG    $11, 0xBF2025B8
    ori      $11, $11, 0x0100
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
   WREG_D 0xBF2025c8 , ( BIST_LEN >> 3 )
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
   WREG_D  (REG_ADDR_BASE + (0x1012e4 <<1 )) , ( BIST_LEN >> 3 )
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
   WREG   0xBF2025E0 , 0x0000   #reset 0x1012f0 bit_15=0

   jr      $31
   nop



#-------------------------------------------------------------------------------------------------
# MIU_Mau_Memory_Arrange
# @param  None
# @return None
# @note   Set AEON/51 MAU 64MB+64MB or 128MB+128MB
#-------------------------------------------------------------------------------------------------
MIU_Mau_Memory_Arrange:

#if(AEON_51_MAU_64MB==1)
    WREG_B  0xBF203085, 0x0     # Set reg_miu0_size 64MB in MAU0
    WREG_B  0xBF2030C5, 0x0     # Set reg_miu0_size 64MB in MAU1
#else
    WREG_B  0xBF203085, 0x1     # Set reg_miu0_size 128MB in MAU0
    WREG_B  0xBF2030C5, 0x1     # Set reg_miu0_size 128MB in MAU1
#endif

   jr      $31
   nop



#-------------------------------------------------------------------------------------------------
# BOOTROM_MPLL_INIT
# @param  Nnoe
# @return None
# @note   do MPLL init
#-------------------------------------------------------------------------------------------------
BOOTROM_MPLL_INIT:

    #include "script_MainPll_MIPSPLL_UPLL.S"
    jr      $31
    nop


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
# BOOT_InitUART
# @param  None
# @return None
# @note   Init UART
#-------------------------------------------------------------------------------------------------
BOOT_InitUART:
    WREG (CLK_GEN0_BASE+0x13*4), 0x0C01

### Switch PAD ISP###################################################
.if (UART0==1)
#    WREG    0xbf001c24	0x0000 # clear register as Chakra
#    WREG    0xbf001c24	0x0800
    #enable reg_uart_rx_enable
    RREG    $11,        0xbf001c24
    ori     $11, $11,   0x0800
    sw      $11,        0xbf001c24

#    WREG 0xbf203d4c 0x2104 # ???
    #Select to PIU_UART0
    RREG    $11,        0xbf203d4c
    ori     $11, $11,   0x0004
    sw      $11,        0xbf203d4c

    #enable reg_uart_rx_enable      #TBD: this register T4 is removed
    #RREG    $11,        0xbf203c04
    #ori     $11, $11,   0x0400
    #sw      $11,        0xbf203c04

.endif # .if(UART0==1)
### Switch PAD ISP end###################################################

### Switch PAD RS232#################################################
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

    #0xF52 bit 7 =0 Disable I2C GPIO
#    RREG    $11,        0xbf203d44
#    and     $11, $11,   0x7FFF
#    sw      $11,        0xbf203d44

#    WREG    0xbf203d58, 0x0010 # for UART2 internal loop testing
.endif  #.if (UART0==0)
### Switch PAD RS232 end#################################################

    RREG    $11,         0xbf201318   # Kernel need
    ori     $11, $11,    0x0080
    sw      $11,         0xbf201318

    WREG 0xbf201300 UART_DIVISOR_L
    WREG 0xbf201308 UART_DIVISOR_H

    RREG    $11,         0xbf201318   # Kernel need
    and     $11, $11,    0xFF7F
    sw      $11,         0xbf201318

    WREG 0xbf201310      0x0000        # Kernel need
    WREG 0xbf201310      0x0007

    WREG 0xbf201318      0x0000        # Kernel need
    WREG 0xbf201318      0x0003
    WREG 0xbf201320      0x0000        # Kernel need
    WREG 0xbf201308      0x0000        # Kernel need


    PUTK 'U'
    PUTK 'A'
    PUTK 'R'
    PUTK 'T'
    PUTK '_'
    PUTK '1'
    PUTK '1'
    PUTK '5'
    PUTK '2'
    PUTK '0'
    PUTK '0'

    #PUTK '\n'
    #PUTK '\r'


    jr      $31
    nop
