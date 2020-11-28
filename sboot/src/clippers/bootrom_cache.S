/*
 *#############################################################################
 *
 * Copyright (c) 2006-2013 MStar Semiconductor, Inc.
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

    mrc         p15, 1, r0, c9, c0, 2
    bic         r0, r0, #0x01c0                     @//Clear L2 Tag RAM Latency bits
    bic         r0, r0, #0x07                       @//Clear L2 Data RAM Latency bits
    orr         r0, r0, #0x82                       @//Configure 3 Cycle Latencies
    mcr         p15, 1, r0, c9, c0, 2

    mrc         p15, 0, r0, c1, c0, 0
    orr         r0, r0, #(0x1 << 12) | (1 << 11)    @//Enable L1 I-Cache and Branch Prediction
    orr         r0, r0, #(0x1 << 2)                 @//Enable L1 D-Cache and MMU
    isb
    mcr         p15, 0, r0, c1, c0, 0
    isb
    dsb

    bx          lr
@//-------------------------------------------------------------------------------------------------
@// BootRom_SetL3Clock
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_SetL3Clock
BootRom_SetL3Clock:


    @//Set MIU1x Mode
    RREG        r0, (MS_BUS_RIU_ADDR + (0x101e20 << 1))
    bic         r0, r0, #0x10
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x101e20 << 1))

    ldr         r1, =(MS_BUS_RIU_ADDR + (0x101800 << 1))
    ldr         r0, [r1, #(0x82 << 1)]
    orr         r0, r0, #0x0080
    str         r0, [r1, #(0x82 << 1)]
      @//Switch L3 CLK to MIU2X  

    bx          lr    

    .size       BootRom_InitCache,.-BootRom_InitCache

    .end

