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
    ret

#//-------------------------------------------------------------------------------------------------
#// BootRom_SetL3Clock
#// @param
#// @return None
#// @note
#//-------------------------------------------------------------------------------------------------
    .global     BootRom_SetL3Clock
BootRom_SetL3Clock:

    WREG_B      (MS_BUS_RIU_ADDR + (0x101880 << 1) + 1), 0x12   //Switch L3 MIU0 to Highway
    WREG_B      (MS_BUS_RIU_ADDR + (0x101E20 << 1)), 0xE0   
    WREG_B      (MS_BUS_RIU_ADDR + (0x101882 << 1)), 0x84       //Switch L3 CLK to MIU2X  

    ret
    
    .size       BootRom_InitCache,.-BootRom_InitCache

    .end

