 @@!
 @\brief
 @@
 .macro _enable_cache

    MRC     p15, 0, r0, c1, c0, 0       @ read CP15 register 1 into r0
    ORR     r0, r0, #(0x1  <<12)        @  I Cache enable
    @ORR     r0, r0, #(0x1  <<2)         @  D Cache enable
    MCR     p15, 0, r0, c1, c0, 0       @ write CP15 register 1
  .endm

 .macro _disable_cache

    MRC     p15, 0, r0, c1, c0, 0       @ read CP15 register 1 into r0
    BIC     r0, r0, #(0x1  <<12)        @  I Cache enable
    BIC     r0, r0, #(0x1  <<2)         @  D Cache enable
    MCR     p15, 0, r0, c1, c0, 0       @ write CP15 register 1
.endm


@@!
 @\brief  Initialise MMU for v7 processors
 @@
 .macro _cpu_mmu_init_v7

    STMFD   sp!,{r4-r5,r14}

    LDR     r0,=0x40400000   @ set TTB to DRAM start address
    MCR     p15, 0, r0, c2, c0, 0   @ Write address to TTB

init_ttb :
    MRC     p15, 0, r0, c2, c0, 0       @ read Translation Table base from CP15 register 2
    @ Create translation table for flat mapping

    @ Top 12 bits of VA is pointer into table
    @ Create 4096 entries from 000xxxxx to fffxxxxx

    LDR     r1,=0xfff                   @ loop counter
@    LDR     r4,=0x0c12                  @ pte flags for uncached section
@    LDR     r5,=0x1c0e                  @ pte flags for WA cached section
    LDR     r4,=0x0c02                  @ pte flags for uncached section
    LDR     r5,=0x0c0e                  @ pte flags for WA cached section
    MOV     r2, r5

init_ttb_1 :
    ORR     r3, r2, r1, LSL#20          @ use loop counter to create individual table entries
    STR     r3, [r0, r1, LSL#2]         @ str table entry at TTB base + loopcount*4
    CMP     r1, #0x200
    MOVEQ   r2, r4                      @ Do not cache or buffer peripheral regions
    CMP     r1, #0x100
    MOVEQ   r2, r5                      @ ...but do cache and buffer below the peripheral regions

@ IF :DEF: USE_TCM
@  IF USE_TCM = 1
@    CMP     r1, #0x80
@    MOVEQ   r2, r4                      @ Do not cache or buffer TCM regions
@  ENDIF
@ ENDIF

    SUBS    r1, r1, #1                  @ decrement loop counter
    BPL     init_ttb_1

    @ init_domains

    @LDR     r0,=0x1              @
    LDR     r0,=0x55555555              @
    MCR     p15, 0, r0, c3, c0, 0       @ write to CP15 register 5

    @ enable mmu
#if 0
    MRC     p15, 0, r0, c1, c0, 0       @ read CP15 register 1 into r0
    BIC     r0, r0, #(0x1  <<12)        @ ensure I Cache disabled
    BIC     r0, r0, #(0x1  <<2)         @ ensure D Cache disabled
    ORR     r0, r0, #0x1                @ enable MMU before scatter loading
    MCR     p15, 0, r0, c1, c0, 0       @ write CP15 register 1
#endif
    LDMFD   sp!, {r4-r5,r14}

 .endm






@ single core
.macro initial_pagetable

  @ Create Translation Table
  @
  @ Create 4096 1MB section descriptors
  @  31                  20 19 18 17 16  15 14 12 11 10  9  8    5  4 3 2 1 0
  @ |<section base address>| 0  0|nG| S|APX| TEX |  AP |IMP|Domain|XN| CB|1 0|
  @
  @ nG     = 2_0    - Page description is Global
  @ S      = 2_0    - Page is Non-shared
  @ APX    = 2_0
  @ AP     = 2_11   - Access Permissions are Full Access
  @ TEX    = 2_000
  @ CB     = 2_00   - Memory Attribute is Strongly Ordered
  @                   (except for the first descriptor, see below)
  @ IMP    = 2_0    - Ignored
  @ Domain = 2_1111 - Page Domain is 15
  @ XN     = 2_0    - Execute Never disabled
  @LDR   r2, =2_00000000000000000000110111100010
  LDR   r2, =0xDE2
  @ Load base address for this cores Translation Table
  @MRC   p15, 0, r4, c0, c0, 5 @ Read Multiprocessor Affinity Register
  @AND   r4, r4, #0x3 @ Extract CPU ID bits
  @ADR   r0, 0x40000000 @ttb_addresses
  LDR   r0, =0x40000000
  @LDR   r0, [r0, r4, LSL #2]

  LDR   r1, =0xfff @ loop counter

  @ r0 is the Translation Table Base address
  @ r1 is the loop counter
  @ r2 is the non-address part of descriptor
  @ r3 is used to create complete descriptor
  @ r4 is the CPU ID
  @ Last descriptor in table is written first
write_descriptor:
  ORR   r3, r2, r1, LSL #20  @ OR in address to creat complete descriptor
  STR   r3, [r0, r1, LSL #2] @ write descriptor to TTB base + loopcounter*4
  SUBS  r1, r1, #1           @ decrement loop counter
  BPL   write_descriptor

  @ Modify second virtual page descriptor to point at a different Physical
  @ address for each CPU
  @ADD   r3, r4, #1
  @LSL   r3, r3, #20                  @ Set Physical address for this CPU
  @ORR   r3, r3, r2                   @ OR in non-address part of descriptor
  @BIC   r3, r3, #0xC @#2_1100              @ clear CB bits
  @BIC   r3, r3, #0x7000 @#2_111000000000000   @ clear TEX bits

  @ Set different cacheable attributes for each CPUs Dhrystone

  @ Make CPU0 second page Outer cacheable, Inner cacheable
  @CMP   r4, #0
  @ORREQ r3, r3, #0x4 @#2_0100              @ inner write back, write allocate
  @ORREQ r3, r3, #0x5000 @#2_101000000000000   @ outer write back, write allocate

  @ Make CPU1 second page Outer cacheable, Inner non-cacheable
  @CMP   r4, #1
  @ORREQ r3, r3, #0x0 @#2_0000              @ inner non-cacheable
  @ORREQ r3, r3, #0x5000 @#2_101000000000000   @ outer write back, write allocate

  @ Make CPU2 second page Outer non-cacheable, Inner cacheable
  @CMP   r4, #2
  @ORREQ r3, r3, #0x4 @#2_0100              @ inner write back, write allocate
  @ORREQ r3, r3, #0x4000 @#2_100000000000000   @ outer non-cacheable

  @ Make CPU3 second page Outer non-cacheable, Inner non-cacheable
  @CMP   r4, #3
  @ORREQ r3, r3, #0x0 @#2_0000              @ inner non-cacheable
  @ORREQ r3, r3, #0x4000 @#2_100000000000000   @ outer non-cacheable
  @STR   r3, [r0, #0x4]

  BIC   r3, r3, #0xC @#2_1100              ; clear CB bits
  ORR   r3, r3, #0x4 @#2_0100              ; inner write back, write allocate
  BIC   r3, r3, #0x7000 @#2_111000000000000   ; clear TEX bits
  ORR   r3, r3, #0x5000 @#2_101000000000000   ; set TEX as write back, write allocat

  STR   r3, [r0]

.endm




.macro initial_mmu

  @ Set Translation Table base address for this CPU
  @ Enable TTB0 only
  MOV   r0,#0x0
  MCR   p15, 0, r0, c2, c0, 2 @ Write Translation Table Base Control Register

  @MRC   p15, 0, r1, c0, c0, 5 @ Read Multiprocessor Affinity Register
  @AND   r1, r1, #0x3 @ Extract CPU ID bits
  @ADR   r0, 0x40000000 @ttb_addresses
  LDR   r0, =0x40000000
  @LDR   r0, [r0, r1, LSL #2]

  MCR   p15, 0, r0, c2, c0, 0 @ Write Translation Table Base Register 0

  @ Set all Domains to Client
  MRC   p15, 0, r0, c3, c0, 0 @ Read Domain Access Control Register
  LDR   r0, =0x55555555
  MCR   p15, 0, r0, c3, c0, 0 @ Write Domain Access Control Register

.endm




.macro v7_flush_dcache_all
    dmb                 @ ensure ordering with previous memory accesses
    mrc p15, 1, r0, c0, c0, 1       @ read clidr
    ands    r3, r0, #0x7000000      @ extract loc from clidr
    mov r3, r3, lsr #23         @ left align loc bit field
    beq finished            @ if loc is 0, then no need to clean
    mov r10, #0             @ start clean at cache level 0
loop_1:
    add r2, r10, r10, lsr #1        @ work out 3x current cache level
    mov r1, r0, lsr r2          @ extract cache type bits from clidr
    and r1, r1, #7          @ mask of the bits for current cache only
    cmp r1, #2              @ see what cache we have at this level
    blt skip                @ skip if no cache, or just i-cache
    mcr p15, 2, r10, c0, c0, 0      @ select current cache level in cssr
    isb                 @ isb to sych the new cssr&csidr
    mrc p15, 1, r1, c0, c0, 0       @ read the new csidr
    and r2, r1, #7          @ extract the length of the cache lines
    add r2, r2, #4          @ add 4 (line length offset)
    ldr r4, =0x3ff
    ands    r4, r4, r1, lsr #3      @ find maximum number on the way size
    clz r5, r4              @ find bit position of way size increment
    ldr r7, =0x7fff
    ands    r7, r7, r1, lsr #13     @ extract max number of the index size
loop_2:
    mov r9, r4              @ create working copy of max way size
loop_3:
 orr r11, r10, r9, lsl r5     @ factor way and cache number into r11

 orr r11, r11, r7, lsl r2     @ factor index number into r11

    mcr p15, 0, r11, c7, c14, 2     @ clean & invalidate by set/way
    subs    r9, r9, #1          @ decrement the way
    bge loop_3
    subs    r7, r7, #1          @ decrement the index
    bge loop_2
skip:
    add r10, r10, #2            @ increment cache number
    cmp r3, r10
    bgt loop_1
finished:
    mov r10, #0             @ swith back to cache level 0
    mcr p15, 2, r10, c0, c0, 0      @ select current cache level in cssr
    dsb
    isb

.endm
