////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
#include "chiptype.h"
#include "risc32_spr.h"

#define REG_BASE                0xA0000000
#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)
#define REG_BANK_RISC32			0x100200
#else
#error "please assign correct register base for R2\n"
#endif
#define HAL_ICACHE_LINE_SIZE    32
#define HAL_DCACHE_LINE_SIZE    16

        .section ".reset","ax"

.macro  hal_icache_init
    /* Invalidate I-Cache */
    l.addi  r3,r0,0
    l.ori  r4,r0,8192// HAL_ICACHE_SIZE
1:
    l.ori   r5,r0,SPR_ICBIR
    l.mtspr r5,r3,0
    l.sfne  r3,r4
    l.addi  r3,r3,HAL_ICACHE_LINE_SIZE
    l.bf    1b

                /* Enable I-Cache */
    l.ori   r5,r0,SPR_SR
    l.mfspr r3,r5,0
    l.ori   r3,r3,SPR_SR_ICE
    l.mtspr r5,r3,0

    /* Flush instructions out of instruction buffer */
    l.nop
    l.nop
    l.nop
    l.nop
    l.nop
.endm

.macro  hal_dcache_init
# Invalidate DC
    l.addi  r3,r0,0
    l.addi  r4,r0,2032          # (HAL_DCACHE_SIZE/HAL_DCACHE_WAYS) - HAL_DCACHE_LINE_SIZE
1:
    l.invalidate_line   0(r3),0  # invalidate line index=r3, way=0
    l.invalidate_line   0(r3),1  # invalidate line index=r3, way=1
    l.sfne  r3,r4
    l.addi  r3,r3,HAL_DCACHE_LINE_SIZE
    l.bf    1b

# Enable D-Cache
    l.mfspr r3,r0,SPR_SR
    l.ori   r3,r3,SPR_SR_DCE
    l.mtspr r0,r3,SPR_SR
        .endm


.macro  hal_bss_init
        l.movhi r3,hi(__bss_start)
        l.ori   r3,r3,lo(__bss_start)
        l.movhi r4,hi(__bss_end)
        l.ori   r4,r4,lo(__bss_end)

1:      l.sfgeu r3,r4
        l.bf    2f
        l.sw    0(r3),r0
        l.addi  r3,r3,4
        l.j     1b
2:
.endm

        .extern _start
        .extern _boot_stack

        .org 0x100

        .globl  __reset
__reset:
        # Initialize Supervision Register:
        # Supervisor mode on, all interrupts off, caches off
        l.ori   r3,r0,SPR_SR_SM
        l.mtspr r0,r3,SPR_SR

        #   org:map SRAM to 0xc000_0000~0xc000_0fff
        #   T3:map SRAM to 0xB000_0000~0xB000_0fff
        # qmem_dmask[7:0]
        # qmem_daddr[7:0]
        l.movhi r7,hi(REG_BASE+REG_BANK_RISC32*2)
        l.ori   r6,r7,lo(REG_BASE+REG_BANK_RISC32*2)

        l.ori   r5, r0, 0xF000
        l.sw    (0xA0*2)(r6),r5

        l.ori   r5, r0, 0xB000
        l.sw    (0x9C*2)(r6),r5

        l.ori   r5, r0, 0x9000
        l.sw    (0xAA*2)(r6),r5

        l.ori   r5, r0, 0x0017
        l.sw    (0xB0*2)(r6),r5

        # check the booting from DRAM or SPI
        l.ori   r5,r7,(0x1200 * 2)
        l.lhz   r3,0(r5)
        l.andi  r3,r3,0x8000
        l.sfeqi r3,0
        l.bf    jump_to_start
        l.nop

        l.ori   r5, r0, 0xA100
        l.sw    (0xAC*2)(r6),r5
        l.ori   r5, r0, 0xA100
        l.sw    (0x90*2)(r6),r5

        hal_icache_init
        hal_dcache_init

jump_to_start:
        hal_bss_init

        l.movhi r1,hi(_boot_stack-4)
        l.ori   r1,r1,lo(_boot_stack-4)
        l.addi  r2,r0,-3

        l.j     _start
        l.and   r1,r1,r2            # 4 byte alignment
