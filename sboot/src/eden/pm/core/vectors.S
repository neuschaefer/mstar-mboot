#===========================================================================


        .extern _main

#include "./inc/risc32.inc"
#include "./inc/risc32_spr.h"

#===========================================================================
# Start by defining the exceptions vectors that must be placed in low
# memory, starting at location 0x100.

        .section ".vectors","ax"

#---------------------------------------------------------------------------
# Generic vector macro

.macro  exception_vector name org handler
        .p2align 8
        .globl  __exception_\name
__exception_\name:

        l.addi  sp,sp,-SIZEOF_RISC32REGS  # space for registers

        # Store General Purpose Registers (GPRs).

        l.sw     3 * RISC32_GPRSIZE(sp), r3
        l.sw     4 * RISC32_GPRSIZE(sp), r4
        l.sw     5 * RISC32_GPRSIZE(sp), r5
        l.sw     6 * RISC32_GPRSIZE(sp), r6
        l.sw     7 * RISC32_GPRSIZE(sp), r7
        l.sw     8 * RISC32_GPRSIZE(sp), r8
        l.sw     9 * RISC32_GPRSIZE(sp), r9
        l.sw    11 * RISC32_GPRSIZE(sp), r11
        l.sw    13 * RISC32_GPRSIZE(sp), r13
        l.sw    15 * RISC32_GPRSIZE(sp), r15
        l.sw    17 * RISC32_GPRSIZE(sp), r17
        l.sw    19 * RISC32_GPRSIZE(sp), r19
        l.sw    21 * RISC32_GPRSIZE(sp), r21
        l.sw    23 * RISC32_GPRSIZE(sp), r23
        l.sw    25 * RISC32_GPRSIZE(sp), r25
        l.sw    27 * RISC32_GPRSIZE(sp), r27
        l.sw    29 * RISC32_GPRSIZE(sp), r29
        l.sw    31 * RISC32_GPRSIZE(sp), r31
#---------------------------------------------------------------------------
        # R0 is not typically stored because it is always zero-valued,
        # but we store it here for consistency when examining registers
        # in the debugger.
        l.sw     0 * RISC32_GPRSIZE(sp), r0

        # Callee-saved regs don't need to be preserved across a call into
        # an ISR, but we can do so to make debugging easier.
        l.sw     2 * RISC32_GPRSIZE(sp), r2
        l.sw    10 * RISC32_GPRSIZE(sp), r10
        l.sw    12 * RISC32_GPRSIZE(sp), r12
        l.sw    14 * RISC32_GPRSIZE(sp), r14
        l.sw    16 * RISC32_GPRSIZE(sp), r16
        l.sw    18 * RISC32_GPRSIZE(sp), r18
        l.sw    20 * RISC32_GPRSIZE(sp), r20
        l.sw    22 * RISC32_GPRSIZE(sp), r22
        l.sw    24 * RISC32_GPRSIZE(sp), r24
        l.sw    26 * RISC32_GPRSIZE(sp), r26
        l.sw    28 * RISC32_GPRSIZE(sp), r28
        l.sw    30 * RISC32_GPRSIZE(sp), r30
#---------------------------------------------------------------------------

        # save MAC LO and HI regs
#ifdef __AEONR2__
        l.ori   r4,r0,SPR_MACLO
        l.mfspr r5,r4,0
        l.sw    RISC32REG_MACLO(sp),r5
        l.ori   r4,r0,SPR_MACHI
        l.mfspr r5,r4,0
        l.sw    RISC32REG_MACHI(sp),r5
        l.ori   r4,r0,SPR_MACHI2
        l.mfspr r5,r4,0
        l.sw    RISC32REG_MACHI2(sp),r5
#else
        l.mfspr r5,r0,SPR_MACLO
        l.sw    RISC32REG_MACLO(sp),r5
        l.mfspr r5,r0,SPR_MACHI
        l.sw    RISC32REG_MACHI(sp),r5
#endif
        # Save SP of interruptee in reg dump
        l.addi  r5,sp,SIZEOF_RISC32REGS
        l.sw     1 * RISC32_GPRSIZE(sp),r5

        # ...and the PC
#ifdef __AEONR2__
        l.ori   r4,r0,SPR_EPCR_BASE
        l.mfspr r5,r4,0
        l.sw    RISC32REG_PC(sp),r5
#else
        l.mfspr r5,r0,SPR_EPCR_BASE
        l.sw    RISC32REG_PC(sp),r5
#endif

        # ... and the Supervisor Register
#ifdef __AEONR2__
        l.ori   r4,r0,SPR_ESR_BASE
        l.mfspr r5,r4,0
        l.sw    RISC32REG_SR(sp),r5
#else
        l.mfspr r5,r0,SPR_ESR_BASE
        l.sw    RISC32REG_SR(sp),r5
#endif

        # ... and the exception's effective address, if there is one.
        # FIXME - don't need to do this for some exceptions
#ifdef __AEONR2__
        l.ori   r4,r0,SPR_EEAR_BASE
        l.mfspr r5,r4,0
        l.sw    RISC32REG_EEAR(sp),r5
#else
        l.mfspr r5,r0,SPR_EEAR_BASE
        l.sw    RISC32REG_EEAR(sp),r5
#endif

        # Arg 0(R3): pointer to HAL_SavedRegisters struct
        l.or    r3,r0,sp                     # Delay slot

        # Arg 1(R4): Exception Number
        # First vector is located at 0x100, second at 0x200, etc.
        # Shift right to get vector number for address lookup.
        l.ori   r4,r0,(\org>>8)
        l.sw    RISC32REG_VECTOR(sp),r4

        l.movhi r9, hi(restore_state)
#ifdef __AEONR2__
        l.ori   r9,r9,lo(restore_state)
        l.j     \handler
#else
        l.j     \handler
        l.ori   r9,r9,lo(restore_state)
#endif
.endm

#---------------------------------------------------------------------------
# Define the exception vectors.

        .extern _mhal_exception_handler
        .extern _mhal_interrupt_handler

rom_vectors:
        # These are the architecture-defined vectors that
        # are always present.
        exception_vector    bus_error               0x200   _mhal_exception_handler
        exception_vector    data_page_fault         0x300   _mhal_exception_handler
        exception_vector    instruction_page_fault  0x400   _mhal_exception_handler
        exception_vector    tick_timer              0x500   _mhal_interrupt_handler
        exception_vector    unaligned_access        0x600   _mhal_exception_handler
        exception_vector    illegal_instruction     0x700   _mhal_exception_handler
        exception_vector    external_interrupt      0x800   _mhal_interrupt_handler
        exception_vector    dtlb_miss               0x900   _mhal_exception_handler
        exception_vector    itlb_miss               0xa00   _mhal_exception_handler
        exception_vector    range                   0xb00   _mhal_exception_handler
        exception_vector    syscall                 0xc00   _mhal_exception_handler
        exception_vector    reserved                0xd00   _mhal_exception_handler
        exception_vector    trap                    0xe00   _mhal_exception_handler
rom_vectors_end:

    .section .text,"ax"

#
# Return from either an interrupt or an exception
#
# On entry:
#    SP = pointer to (HAL_SavedRegisters struct)
#
restore_state:

        # Restore General Purpose Registers (GPRs).
        # R0 is not restored because it is always zero-valued.
        # R1, R3, and R4 are used as temps, so they are restored a little later
        l.lwz   r5,   5 * RISC32_GPRSIZE(sp)
        l.lwz   r6,   6 * RISC32_GPRSIZE(sp)
        l.lwz   r7,   7 * RISC32_GPRSIZE(sp)
        l.lwz   r8,   8 * RISC32_GPRSIZE(sp)
        l.lwz   r9,   9 * RISC32_GPRSIZE(sp)
        l.lwz   r11, 11 * RISC32_GPRSIZE(sp)
        l.lwz   r13, 13 * RISC32_GPRSIZE(sp)
        l.lwz   r15, 15 * RISC32_GPRSIZE(sp)
        l.lwz   r17, 17 * RISC32_GPRSIZE(sp)
        l.lwz   r19, 19 * RISC32_GPRSIZE(sp)
        l.lwz   r21, 21 * RISC32_GPRSIZE(sp)
        l.lwz   r23, 23 * RISC32_GPRSIZE(sp)
        l.lwz   r25, 25 * RISC32_GPRSIZE(sp)
        l.lwz   r27, 27 * RISC32_GPRSIZE(sp)
        l.lwz   r29, 29 * RISC32_GPRSIZE(sp)
        l.lwz   r31, 31 * RISC32_GPRSIZE(sp)
#===========================================================================
        # Callee-saved regs don't need to be preserved across a call into
        # an ISR, but we can do so to make debugging easier.

        l.lwz   r2,   2 * RISC32_GPRSIZE(sp)
        l.lwz   r10, 10 * RISC32_GPRSIZE(sp)
        l.lwz   r12, 12 * RISC32_GPRSIZE(sp)
        l.lwz   r14, 14 * RISC32_GPRSIZE(sp)
        l.lwz   r16, 16 * RISC32_GPRSIZE(sp)
        l.lwz   r18, 18 * RISC32_GPRSIZE(sp)
        l.lwz   r20, 20 * RISC32_GPRSIZE(sp)
        l.lwz   r22, 22 * RISC32_GPRSIZE(sp)
        l.lwz   r24, 24 * RISC32_GPRSIZE(sp)
        l.lwz   r26, 26 * RISC32_GPRSIZE(sp)
        l.lwz   r28, 28 * RISC32_GPRSIZE(sp)
        l.lwz   r30, 30 * RISC32_GPRSIZE(sp)

        # Restore MAC LO and HI regs
#ifdef __AEONR2__
        l.lwz   r4, RISC32REG_MACLO(sp)
        l.ori   r3,r0,SPR_MACLO
        l.mtspr r3,r4,0
        l.lwz   r4, RISC32REG_MACHI(sp)
        l.ori   r3,r0,SPR_MACHI
        l.mtspr r3,r4,0
#else
        l.lwz   r4, RISC32REG_MACLO(sp)
        l.mtspr r0,r4,SPR_MACLO
        l.lwz   r4, RISC32REG_MACHI(sp)
        l.mtspr r0,r4,SPR_MACHI
#endif
#===========================================================================

        # Must disable interrupts, since they could clobber ESR and EPC regs
#ifdef __AEONR2__
        l.ori   r4, r0, SPR_SR
        l.mfspr r3, r4, 0
        load32i r4,~(SPR_SR_TEE|SPR_SR_IEE|SPR_SR_IME|SPR_SR_DME)
        l.and   r3, r4, r3
        l.ori   r4, r0, SPR_SR
        l.mtspr r4, r3, 0
        l.lwz   r4, RISC32REG_MACHI2(sp)
        l.ori   r3,r0,SPR_MACHI2
        l.mtspr r3,r4,0
#else
        l.mfspr r3, r0, SPR_SR
        load32i r4,~(SPR_SR_TEE|SPR_SR_IEE)
        l.and   r3, r4, r3
        l.mtspr r0, r3, SPR_SR
#endif

        # At this point we've restored all the pre-interrupt GPRs except for the SP.
        # Restore pre-interrupt SR, SP, and PC
        l.lwz    r4,  RISC32REG_SR(sp)
#ifdef __AEONR2__
        l.ori    r3, r0, SPR_ESR_BASE
        l.mtspr  r3, r4, 0
#else
        l.mtspr  r0, r4, SPR_ESR_BASE
#endif

        l.lwz    r4,  RISC32REG_PC(sp)
#ifdef __AEONR2__
        l.ori    r3, r0, SPR_EPCR_BASE
        l.mtspr  r3, r4, 0
#else
        l.mtspr  r0, r4, SPR_EPCR_BASE
#endif

        l.lwz    r4,  4 * RISC32_GPRSIZE(sp)
        l.lwz    r3,  3 * RISC32_GPRSIZE(sp)
        l.lwz    sp,  1 * RISC32_GPRSIZE(sp)

        # All done, restore CPU state and continue
        l.rfe
#ifndef __AEONR2__
        l.nop           # Delay slot
#endif


#---------------------------------------------------------------------------
# end of vectors.S
