/*
 *#############################################################################
 *
 * Copyright (c) 2006-2014 MStar Semiconductor, Inc.
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

    mrc         p15, 1, r3, c9, c0, 2
    bic         r3, r3, #0xff00                     @//Clear L2 Tag RAM Latency bits
    bic         r3, r3, #0x00ff                     @//Clear L2 Tag RAM Latency bits
    orr         r3, r3, #0x51                       @//Configure 2 Cycle Latencies
    mcr         p15, 1, r3, c9, c0, 2

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

                                                                @//MCU
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B20 << 1) + 1), 0x00   @//Set CLK_MCU to 216MHz (Enabled)
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B20 << 1)), 0x01       @//Set MCU clock to CLK_MCU

    WREG_B      (MS_BUS_RIU_ADDR + (0x101880 << 1) + 1), 0x12   @//Switch L3 MIU0 to Highway
    WREG_B      (MS_BUS_RIU_ADDR + (0x101E20 << 1)), 0xE0   
    WREG_B      (MS_BUS_RIU_ADDR + (0x101882 << 1)), 0x84       @//Switch L3 CLK to MIU2X  

    bx          lr    

    .size       BootRom_InitCache,.-BootRom_InitCache

    .end

