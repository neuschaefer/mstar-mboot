/*
 *#############################################################################
 *
 * Copyright (c) 2006-2015 MStar Semiconductor, Inc.
 * All rights reserved.
 *
 * Unless otherwise stipulated in writing, any and all information contained
 * herein regardless in any format shall remain the sole proprietary of
 * MStar Semiconductor Inc. and be kept in strict confidence
 * (¡§MStar Confidential Information¡¨) by the recipient.
 * Any unauthorized act including without limitation unauthorized disclosure,
 * copying, use, reproduction, sale, distribution, modification, disassembling,
 * reverse engineering and compiling of the contents of MStar Confidential
 * Information is unlawful and strictly prohibited. MStar hereby reserves the
 * rights to any and all damages, losses, costs and expenses resulting therefrom.
 *
 *#############################################################################
 */

#ifndef _BOOT_INC_
#include "boot.inc"
#endif

    .text

    .global     BootRom_InitCache
BootRom_InitCache:

    mov         x29, x30

    mrs         x0, SCTLR_EL3                       //System Control Register (EL3)
    orr         x0, x0, #(0x01 << 2)                //Enable D Cache
    orr         x0, x0, #(0x01 << 11)               //Enable branch prediction
    orr         x0, x0, #(0x01 << 12)               //Enable I Cache
    msr         SCTLR_EL3, x0

    bl          bootrom_flush_cache_all

    ret         x29

/*
 *      __bootrom_flush_dcache_all()
 *
 *      Flush the whole D-cache.
 *
 *      Corrupted registers: x0-x7, x9-x11
 */
    .global     __bootrom_flush_dcache_all
__bootrom_flush_dcache_all:
    dmb         sy                                  // ensure ordering with previous memory accesses
    mrs         x0, clidr_el1                       // read clidr
    and         x3, x0, #0x7000000                  // extract loc from clidr
    lsr         x3, x3, #23                         // left align loc bit field
    cbz         x3, __bootrom_flush_dcache_finished // if loc is 0, then no need to clean
    mov         x10, #0                             // start clean at cache level 0
__bootrom_flush_dcache_loop1:                                              
    add         x2, x10, x10, lsr #1                // work out 3x current cache level
    lsr         x1, x0, x2                          // extract cache type bits from clidr
    and         x1, x1, #7                          // mask of the bits for current cache only
    cmp         x1, #2                              // see what cache we have at this level
    b.lt        __bootrom_flush_dcache_skip         // skip if no cache, or just i-cache
    save_and_disable_irqs x9                        // make CSSELR and CCSIDR access atomic
    msr         csselr_el1, x10                     // select current cache level in csselr
    isb                                             // isb to sych the new cssr&csidr
    mrs         x1, ccsidr_el1                      // read the new ccsidr
    restore_irqs x9
    and         x2, x1, #7                          // extract the length of the cache lines
    add         x2, x2, #4                          // add 4 (line length offset)
    mov         x4, #0x3ff                          
    and         x4, x4, x1, lsr #3                  // find maximum number on the way size
    clz         w5, w4                              // find bit position of way size increment
    mov         x7, #0x7fff                         
    and         x7, x7, x1, lsr #13                 // extract max number of the index size
__bootrom_flush_dcache_loop2:                                              
    mov         x9, x4                              // create working copy of max way size
__bootrom_flush_dcache_loop3:                                              
    lsl         x6, x9, x5                          
    orr         x11, x10, x6                        // factor way and cache number into x11
    lsl         x6, x7, x2                          
    orr         x11, x11, x6                        // factor index number into x11
    dc          cisw, x11                           // clean & invalidate by set/way
    subs        x9, x9, #1                          // decrement the way
    b.ge        __bootrom_flush_dcache_loop3                               
    subs        x7, x7, #1                          // decrement the index
    b.ge        __bootrom_flush_dcache_loop2                               
__bootrom_flush_dcache_skip:                                               
    add         x10, x10, #2                        // increment cache number
    cmp         x3, x10                             
    b.gt        __bootrom_flush_dcache_loop1                               
__bootrom_flush_dcache_finished:                                           
    mov         x10, #0                             // swith back to cache level 0
    msr         csselr_el1, x10                     // select current cache level in csselr
    dsb         sy
    isb
    ret

/*
 *      bootrom_flush_cache_all()
 *
 *      Flush the entire cache system.  The data cache flush is now achieved
 *      using atomic clean / invalidates working outwards from L1 cache. This
 *      is done using Set/Way based cache maintainance instructions.  The
 *      instruction cache can still be invalidated back to the point of
 *      unification in a single instruction.
 */
     .global     bootrom_flush_cache_all
bootrom_flush_cache_all:

    mov         x12, x30
    bl          __bootrom_flush_dcache_all
    mov         x0, #0
    ic          ialluis                         // I+BTB cache invalidate
    ret         x12

    .size       BootRom_InitCache,.-BootRom_InitCache
    .end

