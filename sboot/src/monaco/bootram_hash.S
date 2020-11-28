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

@//-------------------------------------------------------------------------------------------------
@// BOOTRAM_Entry_Hash:
@// @param  None
@// @return None
@// @note   Entry point of Boot code
@//-------------------------------------------------------------------------------------------------
    .globl      BOOTRAM_Entry_Hash

BOOTRAM_Entry_Hash:

    DBGREG      0x000

    ldr         r0, =CONFIG_BOOTRAM_LOADADDR + 0x1400
    ldr         r1, =_ld_bootram2_size
    ldr         r2, =0x1002
    bl          eMMC_ReadData_MIU

#if defined(CONFIG_MSTAR_AUTHEN_ENABLE)
    ldr         r0, =CONFIG_BOOTRAM_LOADADDR + 0x1400                        @//Set the starting address of HASH for Authentication
    ldr         r1, =0x2000                                                  @//Set the HASH size for Authentication
    ldr         r2, =CONFIG_BOOTRAM_LOADADDR + 0x3400                        @//Set the starting address of SIG for Authentication
    ldr         r3, =0x0
    bl          MDrv_AESDMA_SecureMain
#endif

    @//If authentication fail, jump to reset whole system

    cmp         r0, #1
    bne         BootRam_AuthenticationHash3_bk
    WREG_B      MS_BUS_RIU_ADDR + (0x103380 << 1), 0x01
    bl          BootRam_AuthenticationHash3_bk

#if defined(CONFIG_MSTAR_AUTHEN_ENABLE)
BootRam_AuthenticationHash3_bk:
    ldr         r0, =CONFIG_BOOTRAM_LOADADDR + 0x1400
    ldr         r1, =_ld_bootram2_size
    ldr         r2, =0x8002
    bl          eMMC_ReadData_MIU

    ldr         r0, =CONFIG_BOOTRAM_LOADADDR + 0x1400                        @//Set the starting address of HASH for Authentication
    ldr         r1, =0x2000                                                  @//Set the HASH size for Authentication
    ldr         r2, =CONFIG_BOOTRAM_LOADADDR + 0x3400                        @//Set the starting address of SIG for Authentication
    ldr         r3, =0x0
    bl          MDrv_AESDMA_SecureMain
    @//If authentication fail, jump to reset whole system

    cmp         r0, #1
    bne         BootRam_Authentication

    WREG_B      (MS_BUS_RIU_ADDR + (0x103380 << 1) + 1), 0x01

    RREG        r0, (MS_BUS_RIU_ADDR + (0x103380 << 1))        @//check mboot.bin in MBOOT or boot2
    ldr         r1, =0x0001
    and         r0, r0, r1
    cmp         r0, r1
    bne         BootRam_ReadMBOOT2

    ldr         r0, =CONFIG_BOOTRAM_LOADADDR + 0x1400
    ldr         r1, =_ld_bootram2_size
    ldr         r2, =0x1002
    bl          eMMC_ReadData_MIU

    @//Jump to the entry of BOOTRAM_Entry
    ldr         pc, =BOOTRAM_Entry

BootRam_ReadMBOOT2:
    ldr         r0, =CONFIG_BOOTRAM_LOADADDR + 0x1400
    ldr         r1, =_ld_bootram2_size
    ldr         r2, =0x8002
    bl          eMMC_ReadData_MIU

    @//Jump to the entry of BOOTRAM_Entry
    ldr         pc, =BOOTRAM_Entry
#endif

#if defined(CONFIG_MSTAR_AUTHEN_ENABLE)
BootRam_Authentication:
    RREG        r0, (MS_BUS_RIU_ADDR + (0x103380 << 1))         @//check mboot.bin in MBOOT or boot2
    ldr         r1, =0x0001
    and         r0, r0, r1
    cmp         r0, r1
    bne         BootRam_AuthenticationFail

    ldr         r0, =CONFIG_BOOTRAM_LOADADDR + 0x1400
    ldr         r1, =_ld_bootram2_size
    ldr         r2, =0x1002
    bl          eMMC_ReadData_MIU

    @//Jump to the entry of BOOTRAM_Entry
    ldr         pc, =BOOTRAM_Entry

BootRam_AuthenticationFail:
    b           BootRam_AuthenticationFail
#endif