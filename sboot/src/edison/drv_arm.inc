#[*] Enable external sync
@-------------------------------------------------
@Macro: drv_arm_en_ext_sync
@-------------------------------------------------
.macro drv_arm_en_ext_sync
.endm

#[*] sys_init_cache
@-------------------------------------------------
@Macro: drv_arm_cache_init
@-------------------------------------------------
.macro drv_arm_cache_init

    @ Invalidate D-cache by set/way
    @ Note: for Cortex-A9, there is no instruction for invalidating
    @ the whole D-cache. Need to invalidate line by line.
    @ Read cache size from the Cache Size Identification Register
    mrc p15, 1, r3, c0, c0, 0           @ Read current Cache Size Identification Register
#if 0
    mov r1, #0x1ff                      @ compile error :invalid constant (1ff) after fixup
#else
    mov r1, #0x200
    sub r1, r1, #1
#endif
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

.endm

#[*] sys_init_fpu
@-------------------------------------------------
@Macro: drv_arm_fpu_init
@-------------------------------------------------
.macro drv_arm_fpu_init
.endm

#[*] Enable share TLB
@-------------------------------------------------
@Macro: drv_arm_enable_share_tlb
@-------------------------------------------------
.macro drv_arm_enable_share_tlb
.endm

@-------------------------------------------------
@Macro: drv_arm_init_mmu
@-------------------------------------------------
.macro drv_arm_init_mmu
.endm


@-------------------------------------------------
@Macro: ARM_INIT
@-------------------------------------------------
.macro  ARM_INIT

 
# ------------------------------------------------------------
#
# Invalidate caches
#__invalidate_v7_cache      
        MOV     r0, #0
        MCR     p15, 0, r0, c8, c7, 0      @ Invalidate Inst TLB and Data TLB
        MCR     p15, 0, r0, c7, c5, 0      @ Invalidate I Cache
    
        # Must iterate over the caches in order to synthesise a complete clean
        # of data/unified cache
        MRC     p15, 1, r0, c0, c0, 1      @ read Cache Level ID register (clidr)
        ANDS    r3, r0, #0x7000000         @ extract level of coherency from clidr
        MOV     r3, r3, lsr #23            @ left align level of coherency bit field
        BEQ     finished                   @ if loc is 0, then no need to clean
        
        MOV     r10, #0                    @ start clean at cache level 0 (in r10)
loop1:
        ADD     r2, r10, r10, lsr #1       @ work out 3x current cache level
        MOV     r1, r0, lsr r2             @ extract cache type bits from clidr
        AND     r1, r1, #7                 @ mask of the bits for current cache only
        CMP     r1, #2                     @ see what cache we have at this level
        BLT     skip                       @ skip if no cache, or just i-cache
        MCR     p15, 2, r10, c0, c0, 0     @ select current cache level in cssr
        MOV     r1, #0
        MCR     p15, 0, r1, c7, c5, 4      @ prefetchflush to synch the new cssr&csidr
        MRC     p15, 1, r1, c0, c0, 0      @ read the new csidr
        AND     r2, r1, #7                 @ extract the length of the cache lines
        ADD     r2, r2, #4                 @ add 4 (line length offset)
        LDR     r6, =0x3ff
        ANDS    r6, r6, r1, lsr #3         @ find maximum number on the way size
        .WORD   0xE16F5F16                 @DCI   0xE16F5F16 @CLZ r5, r6 @ find bit position of way size increment
        LDR     r7, =0x7fff
        ANDS    r7, r7, r1, lsr #13        @ extract max number of the index size
loop2:
        MOV     r8, r6                     @ create working copy of max way size
loop3:
        ORR     r11, r10, r8, lsl r5       @ factor way and cache number into r11
        ORR     r11, r11, r7, lsl r2       @ factor index number into r11
        MCR     p15, 0, r11, c7, c6, 2     @ invalidate by set/way
        SUBS    r8, r8, #1                 @ decrement the way
        BGE     loop3
        SUBS    r7, r7, #1                 @ decrement the index
        BGE     loop2
skip:
        ADD     r10, r10, #2               @ increment cache number
        CMP     r3, r10
        BGT     loop1

finished:
        nop
.endm

@-------------------------------------------------
@Macro: drv_arm_gic_init
@-------------------------------------------------
.macro drv_arm_gic_init
    WREG    0x16001000, 0x1
    WREG    0x16000104, 0xf0
    WREG    0x16001180, 0xffff0000
    WREG    0x16001100, 0x0000ffff
    WREG    0x16000100, 0x1
.endm

@-------------------------------------------------
@Macro: drv_arm_Set_Intr_Core0_1
@-------------------------------------------------
.macro drv_arm_Set_Intr_Core0_1
     WREG    0x16001f00, 0x00020001
     @WREG    0x16001f02, 0x2
     @WREG    0x16001f00, 0x2
.endm

@-------------------------------------------------
@Macro: drv_arm_exldr_exstr_enable
@-------------------------------------------------
.macro drv_arm_exldr_exstr_enable
     WREG    0x1F203114, 0x0030
.endm
