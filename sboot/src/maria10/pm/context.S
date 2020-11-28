#include "risc32.inc"
#include "risc32_spr.h"

.section ".text", "ax"

SIZEOF_CONTEXT = (4 * 16)

# R3: stack ptr  R4: stack size  R5: routine R6: first argument
ENTRY(mhal_context_setup)
    l.add   r3,r3,r4        # stack = ((stack + size) & ~4) - 8
    l.addi  r4,r0,-3
    l.and   r3,r3,r4
    l.addi  r4,r3,-8

    ## Dummy frame for stack backtrace
    l.sw    4(r4),r0        # LR
    l.sw    0(r4),r0        # FP

    l.addi  r7,r4,-SIZEOF_CONTEXT
    l.sw     2 * RISC32_GPRSIZE(r7), r6     # r3
    l.sw     3 * RISC32_GPRSIZE(r7), r5     # r9
    l.sw     4 * RISC32_GPRSIZE(r7), r3     # r10 (fp)
    l.sw     0 * RISC32_GPRSIZE(r7), r4     # r1
    l.mfspr r4,r0,SPR_SR
    l.jr    r9
    l.sw    15 * RISC32_GPRSIZE(r7), r4     # sr

ENTRY(mhal_context_switch)
    l.addi  sp,sp,-SIZEOF_CONTEXT
    l.sw     1 * RISC32_GPRSIZE(sp), r2
    l.sw     2 * RISC32_GPRSIZE(sp), r3
    l.sw     3 * RISC32_GPRSIZE(sp), r9
    l.sw     4 * RISC32_GPRSIZE(sp), r10
    l.sw     5 * RISC32_GPRSIZE(sp), r12
    l.sw     6 * RISC32_GPRSIZE(sp), r14
    l.sw     7 * RISC32_GPRSIZE(sp), r16
    l.sw     8 * RISC32_GPRSIZE(sp), r18
    l.sw     9 * RISC32_GPRSIZE(sp), r20
    l.sw    10 * RISC32_GPRSIZE(sp), r22
    l.sw    11 * RISC32_GPRSIZE(sp), r24
    l.sw    12 * RISC32_GPRSIZE(sp), r26
    l.sw    13 * RISC32_GPRSIZE(sp), r28
    l.sw    14 * RISC32_GPRSIZE(sp), r30
    l.addi  r5,sp,SIZEOF_CONTEXT
    l.sw    0  * RISC32_GPRSIZE(sp), r5

    l.mfspr r5,r0,SPR_SR
    l.sw    15 * RISC32_GPRSIZE(sp), r5

    l.sw    0(r4),sp

    # fall through
ENTRY(mhal_context_load)
    l.lwz   sp, 0(r3)
    l.lwz   r2,   1 * RISC32_GPRSIZE(sp)
    l.lwz   r3,   2 * RISC32_GPRSIZE(sp)
    l.lwz   r9,   3 * RISC32_GPRSIZE(sp)
    l.lwz   r10,  4 * RISC32_GPRSIZE(sp)
    l.lwz   r12,  5 * RISC32_GPRSIZE(sp)
    l.lwz   r14,  6 * RISC32_GPRSIZE(sp)
    l.lwz   r16,  7 * RISC32_GPRSIZE(sp)
    l.lwz   r18,  8 * RISC32_GPRSIZE(sp)
    l.lwz   r20,  9 * RISC32_GPRSIZE(sp)
    l.lwz   r22, 10 * RISC32_GPRSIZE(sp)
    l.lwz   r24, 11 * RISC32_GPRSIZE(sp)
    l.lwz   r26, 12 * RISC32_GPRSIZE(sp)
    l.lwz   r28, 13 * RISC32_GPRSIZE(sp)
    l.lwz   r30, 14 * RISC32_GPRSIZE(sp)

    l.movhi r5,     hi(~(SPR_SR_TEE|SPR_SR_IEE|SPR_SR_IME|SPR_SR_DME))
    l.ori   r5, r5, lo(~(SPR_SR_TEE|SPR_SR_IEE|SPR_SR_IME|SPR_SR_DME))
    l.mfspr r6, r0, SPR_SR
    l.and   r6, r5, r6
    l.lwz   r5, 15 * RISC32_GPRSIZE(sp)
    l.andi  r5, r5, (SPR_SR_TEE|SPR_SR_IEE)
    l.or    r5, r5, r6
    l.mtspr r0, r5, SPR_SR

    l.jr    lr
    l.lwz   sp, 0 * RISC32_GPRSIZE(sp)
