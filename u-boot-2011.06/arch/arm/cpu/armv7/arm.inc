#ifndef _ARM_INC
#define _ARM_INC

##=============================================================================
##
##    arm.inc
##
##    ARM assembler header file
##
##=============================================================================

@-------------------------------------------------------------------------------------------------
@ Difinitions
@-------------------------------------------------------------------------------------------------
/*
 * Domain numbers
 *
 *  DOMAIN_IO     - domain 2 includes all IO only
 *  DOMAIN_USER   - domain 1 includes all user memory only
 *  DOMAIN_KERNEL - domain 0 includes all kernel memory only
 *
 * The domain numbering depends on whether we support 36 physical
 * address for I/O or not.  Addresses above the 32 bit boundary can
 * only be mapped using supersections and supersections can only
 * be set for domain 0.  We could just default to DOMAIN_IO as zero,
 * but there may be systems with supersection support and no 36-bit
 * addressing.  In such cases, we want to map system memory with
 * supersections to reduce TLB misses and footprint.
 *
 * 36-bit addressing and supersections are only available on
 * CPUs based on ARMv6+ or the Intel XSC3 core.
 */
#define DOMAIN_USER 2
#define DOMAIN_AP   1
#define DOMAIN_BOOT 0

/*
 * Domain types
 */
#define DOMAIN_NOACCESS 0
#define DOMAIN_CLIENT   1
#define DOMAIN_MANAGER  3

/*
 * Address
 */
#define MIU0_VA_ADDR 0x00000000
#define MIU0_PA_ARRD CONFIG_MIU0_BUSADDR

/*
 * Domain value
 */
#define domain_val(dom,type)	((type) << (2*(dom)))

/*
 * Hardware page table definitions.
 *
 * + Level 1 descriptor (PMD)
 *   - common
 */
#define PMD_TYPE_MASK      (3 << 0)
#define PMD_TYPE_FAULT     (0 << 0)
#define PMD_TYPE_TABLE     (1 << 0)
#define PMD_TYPE_SECT      (2 << 0)
#define PMD_BIT4       (1 << 4)
#define PMD_DOMAIN(x)      ((x) << 5)
#define PMD_PROTECTION     (1 << 9)    /* v5 */

/*
 *   - section
 */
#define PMD_SECT_BUFFERABLE  (1 << 2)
#define PMD_SECT_CACHEABLE   (1 << 3)
#define PMD_SECT_XN      (1 << 4)    /* v6 */
#define PMD_SECT_AP_WRITE    (1 << 10)
#define PMD_SECT_AP_READ (1 << 11)
#define PMD_SECT_TEX(x)      ((x) << 12) /* v5 */
#define PMD_SECT_APX     (1 << 15)   /* v6 */
#define PMD_SECT_S       (1 << 16)   /* v6 */
#define PMD_SECT_nG      (1 << 17)   /* v6 */
#define PMD_SECT_SUPER       (1 << 18)   /* v6 */

#define PMD_SECT_UNCACHED    (0)
#define PMD_SECT_BUFFERED    (PMD_SECT_BUFFERABLE)
#define PMD_SECT_WT      (PMD_SECT_CACHEABLE)
#define PMD_SECT_WB      (PMD_SECT_CACHEABLE | PMD_SECT_BUFFERABLE)
#define PMD_SECT_MINICACHE   (PMD_SECT_TEX(1) | PMD_SECT_CACHEABLE)
#define PMD_SECT_WBWA        (PMD_SECT_TEX(1) | PMD_SECT_CACHEABLE | PMD_SECT_BUFFERABLE)
#define PMD_SECT_NONSHARED_DEV   (PMD_SECT_TEX(2))

/*
 *   - mm_flags
 */
#define noncache_mm_flags (PMD_TYPE_SECT |\
                           PMD_DOMAIN(DOMAIN_BOOT)|\
                           PMD_SECT_AP_WRITE |\
                           PMD_SECT_AP_READ)

#define cache_mm_flags (PMD_TYPE_SECT |\
                        PMD_DOMAIN(DOMAIN_BOOT)|\
                        PMD_SECT_AP_WRITE |\
                        PMD_SECT_BUFFERABLE |\
                        PMD_SECT_CACHEABLE |\
                        PMD_SECT_AP_READ)
/*
 * IRQ stack frame.
 */
#define S_FRAME_SIZE	72
#define S_OLD_R0	68
#define S_PSR		64
#define S_PC		60
#define S_LR		56
#define S_SP		52
#define S_IP		48
#define S_FP		44
#define S_R10		40
#define S_R9		36
#define S_R8		32
#define S_R7		28
#define S_R6		24
#define S_R5		20
#define S_R4		16
#define S_R3		12
#define S_R2		8
#define S_R1		4
#define S_R0		0

/*
 * Cortex-A9 MPCore Private Memory Map
 */
#define timer_pa  0x16000600
#define dic_pa    0x16001000

#if defined(CONFIG_MSTAR_NIKE) || defined(CONFIG_MSTAR_MADISON) || defined(CONFIG_MSTAR_CLIPPERS) || \
    defined(CONFIG_MSTAR_NADAL) || defined(CONFIG_MSTAR_MONACO) || defined(CONFIG_MSTAR_MUJI) 
@//Cortex-A7
#define cpu_if_pa 0x16002000
#define cpu_if_va 0xFC002000
#else
@//Cortex-A9
#define cpu_if_pa 0x16000100
#define cpu_if_va 0xFC000100
#endif

##-----------------------------------------------------------------------------
## Standard ARM register names:


@-------------------------------------------------------------------------------------------------
@ Macros
@-------------------------------------------------------------------------------------------------

@-------------------------------------------------------------------------------------------------
@Macros: FUNC_START/FUNC_END
@-------------------------------------------------------------------------------------------------
@        .thumb;                 \
@        .thumb_func;
#define FUNC_START(name)        \
        .globl name;            \
        .type name,%function;   \
name:

#define FUNC_END(name)          \
name##_end:                     \
        .end name

@-------------------------------------------------
@Macro: WREG_B
@-------------------------------------------------
.macro WREG_B reg, value
LDR     r12, =\reg
LDR     r11, =\value
STRB    r11, [r12]
.endm

@-------------------------------------------------
@Macro: WREG
@-------------------------------------------------
.macro WREG reg, value
LDR     r12, =\reg
LDR     r11, =\value
STR     r11, [r12]
.endm

@-------------------------------------------------
@Macro: DBGREG
@-------------------------------------------------
.macro DBGREG value
    WREG    0x1F206700, \value
.endm

@-------------------------------------------------
@Macro: MEMCPY32
@src(r10), dst(r11), len(r12) should be 32bit align
@-------------------------------------------------
.macro MEMCPY32
MEMCPY32_loop:
    LDR     r9, [r10], #4
    STR     r9, [r11], #4
    SUBS    r12, r12,  #4
    BNE     MEMCPY32_loop
.endm

@-------------------------------------------------
@Macro: DELAYUS
@-------------------------------------------------
.macro DELAYUS us
    LDR     r12, =\us
DELAYUS1:
    SUBS    r12, 1
    BNE     DELAYUS1
.endm

@-------------------------------------------------
@Macro: SET_SVC32_MODE
@-------------------------------------------------
.macro set_svc32_mode
    mrs r1, cpsr
    bic r1, r1, #0x1f
    orr r1, r1, #0xd3
    msr cpsr,r1
.endm

@-------------------------------------------------
@Macro: SET_IRQ_MODE
@-------------------------------------------------
.macro set_irq_mode
    mrs r1, cpsr
    bic r1, r1, #0x1f
    orr r1, r1, #0xd2
    msr cpsr,r1
.endm

@-------------------------------------------------
@Macro: SET_FIQ_MODE
@-------------------------------------------------
.macro set_fiq_mode
    mrs r1, cpsr
    bic r1, r1, #0x1f
    orr r1, r1, #0xd1
    msr cpsr,r1
.endm

@-------------------------------------------------
@Macro: DISABLE_MMU_DCACHE
@-------------------------------------------------
.macro disable_mmu_dcache
    mrc p15, 0, r0, c1, c0, 0 @ Read Control Register configuration data
    bic r0, r0, #0x1
    bic r0, r0, #(0x1 << 2)   @ Disable D Cache
    mcr p15, 0, r0, c1, c0, 0 @ Write Control Register configuration data
.endm

@-------------------------------------------------
@Macro: INVALIATE_DCACHE_TLB
@-------------------------------------------------
.macro invaliate_dcache_tlb
    @ Read cache size from the Cache Size Identification Register
    mrc p15, 1, r3, c0, c0, 0          @ Read current Cache Size Identification Register
    @mov r1, #0x1ff
    mov r1, #0x100
    orr r1, r1, #0xff
    and r3, r1, r3, LSR #13            @ r3 = (number of sets - 1)
    mov r0, #0                         @ r0 -> way counter
way_loop:
    mov r1, #0                         @ r1 -> set counter
set_loop:
    mov r2, r0, LSL #30                @
    orr r2, r1, LSL #5                 @ r2 -> set/way cache-op format
    mcr p15, 0, r2, c7, c6, 2          @ Invalidate line described by r2
    add r1, r1, #1                     @ Increment set counter
    cmp r1, r3                         @ Check if the last set is reached...
    ble set_loop                       @ ...if not, continue the set_loop...
    add r0, r0, #1                     @ ...else, Increment way counter
    cmp r0, #4                         @ Check if the last way is reached...
    blt way_loop                       @ ...if not, continue the way_loop

    @invaliate tlb
    mov r0, #0
    mcr p15, 0, r0, c8, c7, 0
.endm

@-------------------------------------------------
@Macro: MACRO GLOBAL_BP_ENABLE
@-------------------------------------------------
.macro global_bp_enable
    mrc p15, 0, r0, c1, c0, 0 @ Read Control Register configuration data
    orr r0, r0, #(0x1 << 11)  @ Global BP Enable
    mcr p15, 0, r0, c1, c0, 0 @ Write Control Register configuration data
    .endm

    .macro enable_d_side_prefetch
    mrc p15, 0, r0, c1, c0, 1 @ Read Auxiliary Control Register
    orr r0, r0, #(0x1 <<2)    @ Enable D-side prefetch
    mcr p15, 0, r0, c1, c0, 1 @ Write Auxiliary Control Register
.endm


#endif
# end of arm.inc
