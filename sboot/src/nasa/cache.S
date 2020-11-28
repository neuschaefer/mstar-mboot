#include "risc32.inc"
#include "risc32_spr.h"

    _RISC32_DCACHE_SIZE = 4096;
    _RISC32_DCACHE_LINE_SIZE = 16;
    _RISC32_DCACHE_WAYS = 2;

    .section ".loader_2nd.text", "ax"

ENTRY(mhal_dcache_flush)
    l.movhi r6,hi(_RISC32_DCACHE_SIZE)
    l.addi  r6,r6,lo(_RISC32_DCACHE_SIZE)
    l.movhi r7,hi(_RISC32_DCACHE_WAYS)
    l.addi  r7,r7,lo(_RISC32_DCACHE_WAYS)
    l.movhi r5,hi(_RISC32_DCACHE_LINE_SIZE)
    l.addi  r5,r5,lo(_RISC32_DCACHE_LINE_SIZE)

    ## (RISC32_DCACHE_SIZE / RISC32_DCACHE_WAYS - RISC32_DCACHE_LINE_SIZE)
    l.divu  r6,r6,r7
    l.sub   r6,r6,r5

    l.sfleu r4,r6
#ifdef __AEONR2__
    l.add   r4,r3,r4
    l.bf    disable_interrupt
#else
    l.bf    disable_interrupt
    l.add   r4,r3,r4
#endif
    l.add   r4,r3,r6

disable_interrupt:
    l.addi  r7,r0,SPR_SR
    l.mfspr r23,r7,0        ## save SR in r23
    l.addi  r6,r0,-7        ## ~(SPR_SR_IEE | SPR_SR_TEE)
    l.and   r6,r23,r6
    l.mtspr r7,r6,0

flush_line:
    l.flush_line       0(r3), 0
    l.flush_line       0(r3), 1
    l.invalidate_line  0(r3), 0
    l.invalidate_line  0(r3), 1

    l.sfltu r3,r4
#ifdef __AEONR2__
    l.add   r3,r3,r5
    l.bf    flush_line
#else
    l.bf    flush_line
    l.add   r3,r3,r5
#endif

#ifdef __AEONR2__
    l.syncwritebuffer

    l.mtspr r7,r23,0        ## restore interrupt mask
    l.jr    r9
#else
    l.syncwritebuffer
    l.jr    r9
    l.mtspr r7,r23,0        ## restore interrupt mask
#endif
