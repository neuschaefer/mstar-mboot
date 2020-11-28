/*
 *#############################################################################
 *
 * Copyright (c) 2006-2014 MStar Semiconductor, Inc.
 * All rights reserved.
 *
 * Unless otherwise stipulated in writing, any and all information contained
 * herein regardless in any format shall remain the sole proprietary of
 * MStar Semiconductor Inc. and be kept in strict confidence
 * (MStar Confidential Information) by the recipient.
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

#ifndef _DRV_MIU_INIT_H_
#include "drv_miu_init.h"
#endif

#ifndef _MIUSEL_MUNICH_2MIU_H_
#include "MIUSEL_MUNICH_2MIU.h"
#endif

#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
@//#define CONFIG_EFUSE_MIU_DQ_DRVN
@//#define CONFIG_EFUSE_MIU_DQ_PHASE
@//#define CONFIG_EFUSE_MIU_DESKEW
#endif

#define CONFIG_EFUSE_MIU_DESKEW

.text

MIU_MESSAGE_BIST0:  .short   'B', 'I', 'S', 'T', '0', '-', 0x00
MIU_MESSAGE_BIST1:  .short   'B', 'I', 'S', 'T', '1', '-', 0x00
MIU_MESSAGE_OK:     .short   'O', 'K', '\n', '\r', 0x00
MIU_MESSAGE_FAIL:   .short   'F', 'A', 'I', 'L', '\n', '\r', 0x00

@//-------------------------------------------------------------------------------------------------
@// MiuBistTest_Entry:
@// @param  None
@// @return None
@// @note   Entry point of Bist Test code (include Deskew function)
@//-------------------------------------------------------------------------------------------------
.global     MiuBistTest_Entry
MiuBistTest_Entry:

    mov         r13, lr
#ifndef CONFIG_MSTAR_TITANIA_BD_FPGA

    #if defined(CONFIG_EFUSE_MIU_DQ_DRVN)
        #if !defined(CONFIG_MIU0_DRAM_NONE)
            bl          Miu0_Dq_Drvn
        #endif
        #if !defined(CONFIG_MIU1_DRAM_NONE)
            bl          Miu1_Dq_Drvn
       #endif
    #endif

    #if defined(CONFIG_EFUSE_MIU_DQ_PHASE)
        #if !defined(CONFIG_MIU0_DRAM_NONE)
            bl          Miu0_DqPhase_Offset
        #endif
        #if !defined(CONFIG_MIU1_DRAM_NONE)
            bl          Miu1_DqPhase_Offset
        #endif
   #endif

   #if defined(CONFIG_EFUSE_MIU_DESKEW)
        #if !defined(CONFIG_MIU0_DRAM_NONE)
            mov         r0, #0
            bl          Miu_DeSkew
        #endif
        #if !defined(CONFIG_MIU1_DRAM_NONE)
            mov         r0, #1
            bl          Miu_DeSkew
        #endif
   #endif
#endif

@//BIST test
#if !defined(CONFIG_MIU0_DRAM_NONE)
@// WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x7FFE @//Mask MIU0_group_0
    bl          Miu0_BistTest
#endif

#ifndef CONFIG_MSTAR_TITANIA_BD_FPGA

    #if !defined(CONFIG_MIU1_DRAM_NONE)
        @// WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x7FFE @//Mask MIU1_group_0
        bl          Miu1_BistTest
    #endif
#endif

    @//Disable BIST
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r0, [r12, #(0xfe << 1)]     @//RREG        r0, (MS_BUS_RIU_ADDR + (0x1012fe << 1))
    orr         r0, r0, #(0x01 << 11)
    str         r0, [r12, #(0xfe << 1)]     @//REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x1012fe << 1))

#if 0
    bl          Miu_WriteRegTbl32
#endif
@//Enable MIU to keep servicing timeouted client when there is no other request to MIU
    RREG        r3, (MS_BUS_RIU_ADDR + (0x10121E << 1))
    ldr         r4, =0x8000
    orr         r3, r3, r4
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x10121E << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x10061E << 1))
    ldr         r4, =0x8000
    orr         r3, r3, r4
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x10061E << 1))

    mov         lr, r13
    bx          lr
//===============================================================================

#define MIU0_DRV_2                          (MS_BUS_RIU_ADDR + (0x110d5a << 1))
#define MIU0_DRVN_1                         (MS_BUS_RIU_ADDR + (0x110d5c << 1))
#define MIU0_DRVP_1                         (MS_BUS_RIU_ADDR + (0x110d5e << 1))

#define MIU1_DRV_2                          (MS_BUS_RIU_ADDR + (0x16165a << 1))
#define MIU1_DRVN_1                         (MS_BUS_RIU_ADDR + (0x16165c << 1))
#define MIU1_DRVP_1                         (MS_BUS_RIU_ADDR + (0x16165e << 1))

#define MIU0_REGION                         (MS_BUS_RIU_ADDR + (0x110d2e << 1))
#define MIU0_DQ0_7_PHASE_L                  (MS_BUS_RIU_ADDR + (0x110d80 << 1))
#define MIU0_DQ8_15_PHASE_L                 (MS_BUS_RIU_ADDR + (0x110d82 << 1))
#define MIU0_DQ16_17_PHASE_L                (MS_BUS_RIU_ADDR + (0x110d84 << 1))
#define MIU0_DQ0_7_PHASE_H                  (MS_BUS_RIU_ADDR + (0x110d86 << 1))
#define MIU0_DQ8_15_PHASE_H                 (MS_BUS_RIU_ADDR + (0x110d88 << 1))
#define MIU0_DQ16_17_PHASE_H                (MS_BUS_RIU_ADDR + (0x110d8a << 1))

#define MIU1_REGION                         (MS_BUS_RIU_ADDR + (0x16162e << 1))
#define MIU1_DQ0_7_PHASE_L                  (MS_BUS_RIU_ADDR + (0x161680 << 1))
#define MIU1_DQ8_15_PHASE_L                 (MS_BUS_RIU_ADDR + (0x161682 << 1))
#define MIU1_DQ16_17_PHASE_L                (MS_BUS_RIU_ADDR + (0x161684 << 1))
#define MIU1_DQ0_7_PHASE_H                  (MS_BUS_RIU_ADDR + (0x161686 << 1))
#define MIU1_DQ8_15_PHASE_H                 (MS_BUS_RIU_ADDR + (0x161688 << 1))
#define MIU1_DQ16_17_PHASE_H                (MS_BUS_RIU_ADDR + (0x16168a << 1))

#define EFUSE_BANK61                        0x29
    #define EFUSE_MIU0_LW_DQ_OFSET_EN           0
    #define EFUSE_MIU0_LW_DQ_OFSET_SIGN         1
    #define EFUSE_MIU0_LW_DQ_OFSET              2
    #define EFUSE_MIU0_HW_DQ_OFSET_EN           4
    #define EFUSE_MIU0_HW_DQ_OFSET_SIGN         5
    #define EFUSE_MIU0_HW_DQ_OFSET              6
    #define EFUSE_MIU1_LW_DQ_OFSET_EN           8
    #define EFUSE_MIU1_LW_DQ_OFSET_SIGN         9
    #define EFUSE_MIU1_LW_DQ_OFSET              10
    #define EFUSE_MIU1_HW_DQ_OFSET_EN           12
    #define EFUSE_MIU1_HW_DQ_OFSET_SIGN         13
    #define EFUSE_MIU1_HW_DQ_OFSET              14
    #define EFUSE_MIU0_DRV_EN                   16
    #define EFUSE_MIU0_DRVN                     17
    #define EFUSE_MIU0_DRVP                     20
    #define EFUSE_MIU1_DRV_EN                   23
    #define EFUSE_MIU1_DRVN                     24
    #define EFUSE_MIU1_DRVP                     27

#define EFUSE_BANK62                        0x2a
    #define EFUSE_MIU0_DESKEW_EN                0
    #define EFUSE_MIU1_DESKEW_EN                1
    #define EFUSE_DESKEW_BIST_MODE              2
    #define EFUSE_DESKEW_OFSET_EN               5
    #define EFUSE_MIU0_DESKEW_OFSET_SIGN        6
    #define EFUSE_MIU0_DESKEW_OFSET             7
    #define EFUSE_MIU1_DESKEW_OFSET_SIGN        10
    #define EFUSE_MIU1_DESKEW_OFSET             11

@//-------------------------------------------------------------------------------------------------
@// Miu0_Dq_Drvn
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
#if defined(CONFIG_EFUSE_MIU_DQ_DRVN)

    .global     Miu0_Dq_Drvn
Miu0_Dq_Drvn:
    REFUSE      r1, EFUSE_BANK61
    GET_BITS    r0, r1, EFUSE_MIU0_DRV_EN, 1
    cmp         r0, #1
    bxne        lr
    GET_BITS    r0, r1, EFUSE_MIU0_DRVN, 3
    mov         r2, r0
    orr         r2, r2, r0, lsl #4
    orr         r2, r2, r0, lsl #8
    orr         r2, r2, r0, lsl #12
    ldr         r3, =0x7777
    RREG        r4, MIU0_DRVN_1
    bic         r4, r4, r3
    orr         r4, r4, r2
    ldr         r3, =MIU0_DRVN_1
    str         r4, [r3]

    GET_BITS    r5, r1, EFUSE_MIU0_DRVP, 3
    mov         r2, r5
    orr         r2, r2, r5, lsl #4
    orr         r2, r2, r5, lsl #8
    orr         r2, r2, r5, lsl #12
    ldr         r3, =0x7777
    RREG        r4, MIU0_DRVP_1
    bic         r4, r4, r3
    orr         r4, r4, r2
    ldr         r3, =MIU0_DRVP_1
    str         r4, [r3]

    mov         r2, r0
    orr         r2, r2, r0, lsl #4
    orr         r2, r2, r5, lsl #8
    orr         r2, r2, r5, lsl #12
    ldr         r3, =0x7777
    RREG        r4, MIU0_DRV_2
    bic         r4, r4, r3
    orr         r4, r4, r2
    ldr         r3, =MIU0_DRV_2
    str         r4, [r3]

    bx          lr

@//-------------------------------------------------------------------------------------------------
@// Miu1_Dq_Drvn
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     Miu1_Dq_Drvn
Miu1_Dq_Drvn:
    REFUSE      r1, EFUSE_BANK61
    GET_BITS    r0, r1, EFUSE_MIU1_DRV_EN, 1
    cmp         r0, #1
    bxne        lr
    GET_BITS    r0, r1, EFUSE_MIU1_DRVN, 3
    mov         r2, r0
    orr         r2, r2, r0, lsl #4
    orr         r2, r2, r0, lsl #8
    orr         r2, r2, r0, lsl #12
    ldr         r3, =0x7777
    RREG        r4, MIU1_DRVN_1
    bic         r4, r4, r3
    orr         r4, r4, r2
    ldr         r3, =MIU1_DRVN_1
    str         r4, [r3]

    GET_BITS    r5, r1, EFUSE_MIU1_DRVP, 3
    mov         r2, r5
    orr         r2, r2, r5, lsl #4
    orr         r2, r2, r5, lsl #8
    orr         r2, r2, r5, lsl #12
    ldr         r3, =0x7777
    RREG        r4, MIU1_DRVP_1
    bic         r4, r4, r3
    orr         r4, r4, r2
    ldr         r3, =MIU1_DRVP_1
    str         r4, [r3]

    mov         r2, r0
    orr         r2, r2, r0, lsl #4
    orr         r2, r2, r5, lsl #8
    orr         r2, r2, r5, lsl #12
    ldr         r3, =0x7777
    RREG        r4, MIU1_DRV_2
    bic         r4, r4, r3
    orr         r4, r4, r2
    ldr         r3, =MIU1_DRV_2
    str         r4, [r3]
    bx          lr

#endif

@//-------------------------------------------------------------------------------------------------
@// Miu0_DqPhase_Offset
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
#if defined(CONFIG_EFUSE_MIU_DQ_PHASE)
    .global     Miu0_DqPhase_Offset
Miu0_DqPhase_Offset:
    REFUSE      r7, EFUSE_BANK61
    GET_BITS    r0, r7, EFUSE_MIU0_LW_DQ_OFSET_EN, 1
    cmp         r0, #0
    beq         _SKIP_MIU0_L
    GET_BITS    r1, r7, EFUSE_MIU0_LW_DQ_OFSET_SIGN, 1  @// sign_L
    GET_BITS    r2, r7, EFUSE_MIU0_LW_DQ_OFSET, 1       @// offset_L[0]
    GET_BITS    r3, r7, EFUSE_MIU0_LW_DQ_OFSET+1, 1     @// offset_L[1]
    RREG_BITS   r4, MIU0_DQ0_7_PHASE_L, 0, 2            @//DQ0_phase_ori[0]
    mvn         r5, r1
    bic         r5, #0xfffffffe
    and         r5, r5, r2
    and         r5, r5, r4
    add         r3, r3, r5
    mvn         r5, r4
    bic         r5, #0xfffffffe
    and         r5, r5, r2
    and         r5, r5, r1
    add         r3, r3, r5
    RREG_BITS   r5, MIU0_REGION, 12, 3
    cmp         r1, #0
    addeq       r5, r5, r3
    subne       r5, r5, r3
    WREG_BITS   MIU0_REGION, r5, 12, 3
    mov         r4, r2, lsl #0
    orr         r4, r4, r2, lsl #2
    orr         r4, r4, r2, lsl #4
    orr         r4, r4, r2, lsl #6
    orr         r4, r4, r2, lsl #8
    orr         r4, r4, r2, lsl #10
    orr         r4, r4, r2, lsl #12
    orr         r4, r4, r2, lsl #14

    RREG        r3, MIU0_DQ0_7_PHASE_L
    eor         r5, r3, r4
    ldr         r6, =0x0000aaaa
    bic         r5, r5, r6
    ldr         r6, =0x00005555
    bic         r3, r3, r6
    orr         r3, r5, r3
    ldr         r0, =MIU0_DQ0_7_PHASE_L
    str         r3, [r0]

    RREG        r3, MIU0_DQ8_15_PHASE_L
    eor         r5, r3, r4
    ldr         r6, =0x0000aaaa
    bic         r5, r5, r6
    ldr         r6, =0x00005555
    bic         r3, r3, r6
    orr         r3, r5, r3
    ldr         r0, =MIU0_DQ8_15_PHASE_L
    str         r3, [r0]

    RREG        r3, MIU0_DQ16_17_PHASE_L
    eor         r5, r3, r4
    ldr         r6, =0x0000fffa
    bic         r5, r5, r6
    ldr         r6, =0x0000fff5
    bic         r3, r3, r6
    orr         r3, r5, r3
    ldr         r0, =MIU0_DQ16_17_PHASE_L
    str         r3, [r0]

_SKIP_MIU0_L:
    GET_BITS    r0, r7, EFUSE_MIU0_HW_DQ_OFSET_EN, 1
    cmp         r0, #0
    beq         _SKIP_MIU0_H
    GET_BITS    r1, r7, EFUSE_MIU0_HW_DQ_OFSET_SIGN, 1  @// sign_H
    GET_BITS    r2, r7, EFUSE_MIU0_HW_DQ_OFSET, 1       @// offset_H[0]
    GET_BITS    r3, r7, EFUSE_MIU0_HW_DQ_OFSET+1, 1       @// offset_H[1]
    RREG_BITS   r4, MIU0_DQ0_7_PHASE_H, 0, 2            @//DQ0_phase_ori[0]
    mvn         r5, r1
    bic         r5, #0xfffffffe
    and         r5, r5, r2
    and         r5, r5, r4
    add         r3, r3, r5
    mvn         r5, r4
    bic         r5, #0xfffffffe
    and         r5, r5, r2
    and         r5, r5, r1
    add         r3, r3, r5
    RREG_BITS   r5, MIU0_REGION, 8, 3
    cmp         r1, #0
    addeq       r5, r5, r3
    subne       r5, r5, r3
    WREG_BITS   MIU0_REGION, r5, 8, 3
    mov         r4, r2, lsl #0
    orr         r4, r4, r2, lsl #2
    orr         r4, r4, r2, lsl #4
    orr         r4, r4, r2, lsl #6
    orr         r4, r4, r2, lsl #8
    orr         r4, r4, r2, lsl #10
    orr         r4, r4, r2, lsl #12
    orr         r4, r4, r2, lsl #14

    RREG        r3, MIU0_DQ0_7_PHASE_H
    eor         r5, r3, r4
    ldr         r6, =0x0000aaaa
    bic         r5, r5, r6
    ldr         r6, =0x00005555
    bic         r3, r3, r6
    orr         r3, r5, r3
    ldr         r0, =MIU0_DQ0_7_PHASE_H
    str         r3, [r0]

    RREG        r3, MIU0_DQ8_15_PHASE_H
    eor         r5, r3, r4
    ldr         r6, =0x0000aaaa
    bic         r5, r5, r6
    ldr         r6, =0x00005555
    bic         r3, r3, r6
    orr         r3, r5, r3
    ldr         r0, =MIU0_DQ8_15_PHASE_H
    str         r3, [r0]

    RREG        r3, MIU0_DQ16_17_PHASE_H
    eor         r5, r3, r4
    ldr         r6, =0x0000fffa
    bic         r5, r5, r6
    ldr         r6, =0x0000fff5
    bic         r3, r3, r6
    orr         r3, r5, r3
    ldr         r0, =MIU0_DQ16_17_PHASE_H
    str         r3, [r0]
_SKIP_MIU0_H:
    bx          lr

@//-------------------------------------------------------------------------------------------------
@// Miu1_DqPhase_Offset
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     Miu1_DqPhase_Offset
Miu1_DqPhase_Offset:
    REFUSE      r7, EFUSE_BANK61
    GET_BITS    r0, r7, EFUSE_MIU1_LW_DQ_OFSET_EN, 1
    cmp         r0, #0
    beq         _SKIP_MIU1_L
    GET_BITS    r1, r7, EFUSE_MIU1_LW_DQ_OFSET_SIGN, 1  @// sign_L
    GET_BITS    r2, r7, EFUSE_MIU1_LW_DQ_OFSET, 1       @// offset_L[0]
    GET_BITS    r3, r7, EFUSE_MIU1_LW_DQ_OFSET+1, 1     @// offset_L[1]
    RREG_BITS   r4, MIU1_DQ0_7_PHASE_L, 0, 2            @//DQ0_phase_ori[0]
    mvn         r5, r1
    bic         r5, #0xfffffffe
    and         r5, r5, r2
    and         r5, r5, r4
    add         r3, r3, r5
    mvn         r5, r4
    bic         r5, #0xfffffffe
    and         r5, r5, r2
    and         r5, r5, r1
    add         r3, r3, r5
    RREG_BITS   r5, MIU1_REGION, 12, 3
    cmp         r1, #0
    addeq       r5, r5, r3
    subne       r5, r5, r3
    WREG_BITS   MIU1_REGION, r5, 12, 3
    mov         r4, r2, lsl #0
    orr         r4, r4, r2, lsl #2
    orr         r4, r4, r2, lsl #4
    orr         r4, r4, r2, lsl #6
    orr         r4, r4, r2, lsl #8
    orr         r4, r4, r2, lsl #10
    orr         r4, r4, r2, lsl #12
    orr         r4, r4, r2, lsl #14

    RREG        r3, MIU1_DQ0_7_PHASE_L
    eor         r5, r3, r4
    ldr         r6, =0x0000aaaa
    bic         r5, r5, r6
    ldr         r6, =0x00005555
    bic         r3, r3, r6
    orr         r3, r5, r3
    ldr         r0, =MIU1_DQ0_7_PHASE_L
    str         r3, [r0]

    RREG        r3, MIU1_DQ8_15_PHASE_L
    eor         r5, r3, r4
    ldr         r6, =0x0000aaaa
    bic         r5, r5, r6
    ldr         r6, =0x00005555
    bic         r3, r3, r6
    orr         r3, r5, r3
    ldr         r0, =MIU1_DQ8_15_PHASE_L
    str         r3, [r0]

    RREG        r3, MIU1_DQ16_17_PHASE_L
    eor         r5, r3, r4
    ldr         r6, =0x0000fffa
    bic         r5, r5, r6
    ldr         r6, =0x0000fff5
    bic         r3, r3, r6
    orr         r3, r5, r3
    ldr         r0, =MIU1_DQ16_17_PHASE_L
    str         r3, [r0]

_SKIP_MIU1_L:
    //REFUSE      r7, EFUSE_BANK61
    GET_BITS    r0, r7, EFUSE_MIU1_HW_DQ_OFSET_EN, 1
    cmp         r0, #0
    beq         _SKIP_MIU1_H
    GET_BITS    r1, r7, EFUSE_MIU1_HW_DQ_OFSET_SIGN, 1  @// sign_H
    GET_BITS    r2, r7, EFUSE_MIU1_HW_DQ_OFSET, 1       @// offset_H[0]
    GET_BITS    r3, r7, EFUSE_MIU1_HW_DQ_OFSET+1, 1     @// offset_H[1]
    RREG_BITS   r4, MIU1_DQ0_7_PHASE_H, 0, 2           @//DQ0_phase_ori[0]
    mvn         r5, r1
    bic         r5, #0xfffffffe
    and         r5, r5, r2
    and         r5, r5, r4
    add         r3, r3, r5
    mvn         r5, r4
    bic         r5, #0xfffffffe
    and         r5, r5, r2
    and         r5, r5, r1
    add         r3, r3, r5
    RREG_BITS   r5, MIU1_REGION, 8, 3
    cmp         r1, #0
    addeq       r5, r5, r3
    subne       r5, r5, r3
    WREG_BITS   MIU1_REGION, r5, 8, 3
    mov         r4, r2, lsl #0
    orr         r4, r4, r2, lsl #2
    orr         r4, r4, r2, lsl #4
    orr         r4, r4, r2, lsl #6
    orr         r4, r4, r2, lsl #8
    orr         r4, r4, r2, lsl #10
    orr         r4, r4, r2, lsl #12
    orr         r4, r4, r2, lsl #14

    RREG        r3, MIU1_DQ0_7_PHASE_H
    eor         r5, r3, r4
    ldr         r6, =0x0000aaaa
    bic         r5, r5, r6
    ldr         r6, =0x00005555
    bic         r3, r3, r6
    orr         r3, r5, r3
    ldr         r0, =MIU1_DQ0_7_PHASE_H
    str         r3, [r0]

    RREG        r3, MIU1_DQ8_15_PHASE_H
    eor         r5, r3, r4
    ldr         r6, =0x0000aaaa
    bic         r5, r5, r6
    ldr         r6, =0x00005555
    bic         r3, r3, r6
    orr         r3, r5, r3
    ldr         r0, =MIU1_DQ8_15_PHASE_H
    str         r3, [r0]

    RREG        r3, MIU1_DQ16_17_PHASE_H
    eor         r5, r3, r4
    ldr         r6, =0x0000fffa
    bic         r5, r5, r6
    ldr         r6, =0x0000fff5
    bic         r3, r3, r6
    orr         r3, r5, r3
    ldr         r0, =MIU1_DQ16_17_PHASE_H
    str         r3, [r0]
_SKIP_MIU1_H:
    bx          lr

#endif

@//-------------------------------------------------------------------------------------------------
@// Miu_DeSkew
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
#if defined(CONFIG_EFUSE_MIU_DESKEW)
// r0 = miu_sel
    .global     Miu_DeSkew
Miu_DeSkew:  
//    20140507 : EFUSE don't care
//    REFUSE      r1, EFUSE_BANK62
//    GET_BITS    r2, r1, EFUSE_MIU0_DESKEW_EN, 1
//    GET_BITS    r3, r1, EFUSE_MIU1_DESKEW_EN, 1
//    cmp         r2, #0
//    bxne        lr
    //mov         r2, #0
    //WREG_BITS   (MS_BUS_RIU_ADDR + (0x1012fe << 1)), r2, 11, 1 //Enable MIU bist
    //WREG        (MS_BUS_RIU_ADDR + (0x1012fe << 1)), 0x00c9 //Enable MIU bist
    cmp         r0, #1
    beq         0f //skip MIU0 settings
    WREG        (MS_BUS_RIU_ADDR + (0x110d70 << 1)), 0x0000 //Turn off K/2-code+offset function
    WREG        (MS_BUS_RIU_ADDR + (0x110d90 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x110d70 << 1)), 0x0800
    WREG        (MS_BUS_RIU_ADDR + (0x161574 << 1)), 0x0863 //reg_live_test_en
0:
    WREG        (MS_BUS_RIU_ADDR + (0x1012e2 << 1)), 0x7000 //Base
    WREG        (MS_BUS_RIU_ADDR + (0x1012e4 << 1)), 0x8001 //Length
    WREG        (MS_BUS_RIU_ADDR + (0x1012e6 << 1)), 0x0000 //Length_h
    WREG        (MS_BUS_RIU_ADDR + (0x1012e8 << 1)), 0x00ff //Data
//    GET_BITS    r2, r1, EFUSE_DESKEW_BIST_MODE, 3
    mov         r2, #0x3
    lsl         r2, r2, #1
    ldr         r3, =0x0080
    orr         r2, r2, r3
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), r2, 0, 15 // Mode

    WREG        (MS_BUS_RIU_ADDR + (0x161578 << 1)), 0x0012 //reg_dpat_en
    WREG        (MS_BUS_RIU_ADDR + (0x110d40 << 1)), 0xffff //reg_dpat_ph_out[15:0]
    WREG        (MS_BUS_RIU_ADDR + (0x110d42 << 1)), 0xffff //reg_dpat_ph_out[31:16]
    WREG        (MS_BUS_RIU_ADDR + (0x110d44 << 1)), 0x000f //reg_dpat_ph_out[35:32]
    WREG        (MS_BUS_RIU_ADDR + (0x161576 << 1)), 0x000f //reg_dpat_sel[15:0]

    WREG        (MS_BUS_RIU_ADDR + (0x110d60 << 1)), 0x33c8 //[14:12] reg_dll_rd_out_sel = 3
    WREG        (MS_BUS_RIU_ADDR + (0x16157c << 1)), 0x8000 //dpat_log_en = 1

//    GET_BITS    r2, r1, EFUSE_MIU1_DESKEW_EN, 1
//    orr         r2, r2, r0, lsl #1 // (r2 = miu_sel << 1 | EFUSE_MIU1_DESKEW_EN)
    cmp         r0, #0
    beq         1f @//skip MIU1 settings

    WREG        (MS_BUS_RIU_ADDR + (0x161670 << 1)), 0x0000 //Turn off K/2-code+offset function
    WREG        (MS_BUS_RIU_ADDR + (0x161690 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x161670 << 1)), 0x0800

    WREG        (MS_BUS_RIU_ADDR + (0x1615f8 << 1)), 0x0012 //reg_dpat_en
    WREG        (MS_BUS_RIU_ADDR + (0x161640 << 1)), 0xffff //reg_dpat_ph_out[15:0]
    WREG        (MS_BUS_RIU_ADDR + (0x161642 << 1)), 0xffff //reg_dpat_ph_out[31:16]
    WREG        (MS_BUS_RIU_ADDR + (0x161644 << 1)), 0x000f //reg_dpat_ph_out[35:32]
    WREG        (MS_BUS_RIU_ADDR + (0x1615f4 << 1)), 0x0863 //reg_live_test_en
    WREG        (MS_BUS_RIU_ADDR + (0x1615f6 << 1)), 0x000f //reg_dpat_sel[15:0]
    WREG        (MS_BUS_RIU_ADDR + (0x161660 << 1)), 0x33c8 //[14:12] reg_dll_rd_out_sel = 3
    WREG        (MS_BUS_RIU_ADDR + (0x1615fc << 1)), 0x8000 //dpat_log_en = 1
1:
    //dpat_rst
    WREG        (MS_BUS_RIU_ADDR + (0x161578 << 1)), 0x0016
    WREG        (MS_BUS_RIU_ADDR + (0x161578 << 1)), 0x0012
    DELAYUS     (1 * 1000)
    cmp         r0, #0
    beq         2f
    WREG        (MS_BUS_RIU_ADDR + (0x1615f8 << 1)), 0x0013 //reg_dpat_en = 1
    WREG        (MS_BUS_RIU_ADDR + (0x161578 << 1)), 0x0013 //reg_dpat_en = 1
    mov         r4, #0x100
    b           21f
2:
    WREG        (MS_BUS_RIU_ADDR + (0x161578 << 1)), 0x0013 //reg_dpat_en = 1
    mov         r4, #0x1
21:
    WREG        (MS_BUS_RIU_ADDR + (0x16157c << 1)), 0x800a
//    DELAYUS     (100 * 1000)
22:
    DELAYUS     1
    RREG        r3, (MS_BUS_RIU_ADDR + (0x16157e << 1))
    and         r3, r3, r4
    cmp         r3, #0
    beq         22b
    
    
//    GET_BITS    r2, r1, EFUSE_MIU0_DESKEW_EN, 1
//    orr         r2, r2, r0, lsl #1 // (r2 = miu_sel << 1 | EFUSE_MIU0_DESKEW_EN)
    cmp         r0, #0
    bne         5f

    //#####################################################
    /// MIU0 result
    //#####################################################
    mov         r3, #0
    ldr         r4, =(MS_BUS_RIU_ADDR + (0x110da0 << 1))
3:
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x110dc0 << 1))
    str         r3, [r12]
    DELAYUS     1
    
    RREG_BITS   r9, (MS_BUS_RIU_ADDR + (0x110dc0 << 1)), 4, 7
    
    // For debug K value
    //RREG_BITS   r8, (MS_BUS_RIU_ADDR + (0x110d66 << 1)), 0, 7
    //add         r8, r8, #0x30
    //ldr         r12, =(MS_BUS_RIU_ADDR + (0x100980 << 1)) 
    //str         r8, [r12]     
    
    RREG_BITS   r10, (MS_BUS_RIU_ADDR + (0x110d66 << 1)), 0, 7
    
    mov         r8, r3, lsl #2
    subs        r9, r9, r10, lsr #1
    
    subs        r9, r9, #1    // only for MIU0
    mvnmi       r9, r9
    addmi       r9, r9, #1    // 1's complement
    movmi       r5, #8
    movpl       r5, #0
    mov         r7, #7
    cmp         r9, r7
    movhi       r9, #7
    orr         r9, r9, r5
    lsl         r9, r8
    ldr         r5, =(MS_BUS_RIU_ADDR + (0x110d92 << 1))
    ldr         r7, [r5]
    mov         r6, #0xf
    lsl         r6, r8
    bic         r7, r7, r6
    mvn         r6, r6
    bic         r9, r9, r6
    orr         r7, r7, r9
    
    mov         r2, #1
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x110D0E << 1)), r2, 6, 0
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x110D1E << 1)), r2, 2, 0
    
    str         r7, [r5]
    
    mov         r2, #0
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x110D0E << 1)), r2, 6, 0
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x110D1E << 1)), r2, 2, 0
    
    ldr         r9,  =(MS_BUS_RIU_ADDR + (0x110dc2 << 1))
    ldr         r10, =(MS_BUS_RIU_ADDR + (0x110dc4 << 1))
    mov         r6, #0

31:
    mov         r7, #0xf
    mvn         r7, r7, lsl r6
    ldr         r5, [r9]
    bic         r5, r5, r7
    lsr         r5, r5, r6
    cmp         r9, r10
    ldrne       r8, [r4]
    ldreq       r8, [r4, #4]
    bic         r8, r8, r7
    lsr         r8, r8, r6

    subs        r5, r5, r8
    mvnmi       r5, r5
    addmi       r5, r5, #1
    cmp         r5, #6
    addhi       r4, r4, #8
    bhi         4f

    add         r6, r6, #4
    cmp         r6, #16
    bne         31b
    cmpeq       r9, r10
    addne       r9, r9, #4
    movne       r6, #0
    bne         31b

    RREG        r5, (MS_BUS_RIU_ADDR + (0x110dc2 << 1))
    RREG        r8, (MS_BUS_RIU_ADDR + (0x110dc4 << 1))
    str         r5, [r4], #4
    str         r8, [r4], #4
4:
    add         r3, r3, #1
    cmp         r3, #4
    bne         3b
    
    //--------------------------------------------------------
    mov         r2, #1
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x110D0E << 1)), r2, 6, 0
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x110D1E << 1)), r2, 2, 0
    
    WREG        (MS_BUS_RIU_ADDR + (0x110d70 << 1)), 0x0000 //Turn on K/2-code+offset function
    WREG        (MS_BUS_RIU_ADDR + (0x110d90 << 1)), 0x0003
    WREG        (MS_BUS_RIU_ADDR + (0x110d70 << 1)), 0x0800
    
    
    mov         r2, #0
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x110D0E << 1)), r2, 6, 0
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x110D1E << 1)), r2, 2, 0
    
    mov         r2, #1
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x110D0E << 1)), r2, 6, 0
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x110D1E << 1)), r2, 2, 0
    
    mov         r2, #0
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x110D0E << 1)), r2, 6, 0
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x110D1E << 1)), r2, 2, 0
    
    DELAYUS     (10)
    //--------------------------------------------------------

    WREG        (MS_BUS_RIU_ADDR + (0x1615f8 << 1)), 0x0012 //reg_dpat_en = 1
    WREG        (MS_BUS_RIU_ADDR + (0x161578 << 1)), 0x0012 //reg_dpat_en = 1

    WREG        (MS_BUS_RIU_ADDR + (0x161574 << 1)), 0x0000 ////reg_live_test_en=0

    //mov         r2, #1
    //WREG_BITS   (MS_BUS_RIU_ADDR + (0x1012fe << 1)), r2, 11, 1 //Enable MIU bist
5:
//    GET_BITS    r2, r1, EFUSE_MIU1_DESKEW_EN, 1
//    orr         r2, r2, r0, lsl #1 // (r2 = miu_sel << 1 | EFUSE_MIU1_DESKEW_EN)
    cmp         r0, #1
    bne         8f

    //#####################################################
    /// MIU1 result
    //#####################################################
    mov         r3, #0
    ldr         r4, =(MS_BUS_RIU_ADDR + (0x1616a0 << 1))
6:
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x1616c0 << 1))
    str         r3, [r12]
    DELAYUS     1
    
    RREG_BITS   r9, (MS_BUS_RIU_ADDR + (0x1616c0 << 1)), 4, 7
    RREG_BITS   r10, (MS_BUS_RIU_ADDR + (0x161666 << 1)), 0, 7
    mov         r8, r3, lsl #2
    subs        r9, r9, r10, lsr #1
    mvnmi       r9, r9
    addmi       r9, r9, #1    // 1's complement
    movmi       r5, #8
    movpl       r5, #0
    mov         r7, #7
    cmp         r9, r7
    movhi       r9, #7
    orr         r9, r9, r5
    lsl         r9, r8
    ldr         r5, =(MS_BUS_RIU_ADDR + (0x161692 << 1))
    ldr         r7, [r5]
    mov         r6, #0xf
    lsl         r6, r8
    bic         r7, r7, r6
    mvn         r6, r6
    bic         r9, r9, r6
    orr         r7, r7, r9
    
    mov         r2, #1
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x16160E << 1)), r2, 6, 0
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x16161E << 1)), r2, 2, 0
    str         r7, [r5]
    mov         r2, #0
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x16160E << 1)), r2, 6, 0
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x16161E << 1)), r2, 2, 0
    
    ldr         r9,  =(MS_BUS_RIU_ADDR + (0x1616c2 << 1))
    ldr         r10, =(MS_BUS_RIU_ADDR + (0x1616c4 << 1))
    mov         r6, #0

    ldr         r9,  =(MS_BUS_RIU_ADDR + (0x1616c2 << 1))
    ldr         r10, =(MS_BUS_RIU_ADDR + (0x1616c4 << 1))
    mov         r6, #0

61:
    mov         r7, #0xf
    mvn         r7, r7, lsl r6
    ldr         r5, [r9]
    bic         r5, r5, r7
    lsr         r5, r5, r6
    cmp         r9, r10
    ldrne       r8, [r4]
    ldreq       r8, [r4, #4]
    bic         r8, r8, r7
    lsr         r8, r8, r6

    subs        r5, r5, r8
    mvnmi       r5, r5
    addmi       r5, r5, #1
    cmp         r5, #6
    addhi       r4, r4, #8
    bhi         7f

    add         r6, r6, #4
    cmp         r6, #16
    bne         61b
    cmpeq       r9, r10
    addne       r9, r9, #4
    movne       r6, #0
    bne         61b

    RREG        r5, (MS_BUS_RIU_ADDR + (0x1616c2 << 1))
    RREG        r8, (MS_BUS_RIU_ADDR + (0x1616c4 << 1))
    str         r5, [r4], #4
    str         r8, [r4], #4
7:
    add         r3, r3, #1
    cmp         r3, #4
    bne         6b

    //--------------------------------------------------------
    mov         r2, #1
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x16160E << 1)), r2, 6, 0
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x16161E << 1)), r2, 2, 0
    
    WREG        (MS_BUS_RIU_ADDR + (0x161670 << 1)), 0x0000 //Turn on K/2-code+offset function
    WREG        (MS_BUS_RIU_ADDR + (0x161690 << 1)), 0x0003
    WREG        (MS_BUS_RIU_ADDR + (0x161670 << 1)), 0x0800
    
    mov         r2, #0
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x16160E << 1)), r2, 6, 0
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x16161E << 1)), r2, 2, 0
    
    mov         r2, #1
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x16160E << 1)), r2, 6, 0
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x16161E << 1)), r2, 2, 0
    mov         r2, #0
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x16160E << 1)), r2, 6, 0
    WREG_BITS   (MS_BUS_RIU_ADDR + (0x16161E << 1)), r2, 2, 0
    DELAYUS     (10)
    //--------------------------------------------------------

    WREG        (MS_BUS_RIU_ADDR + (0x1615f8 << 1)), 0x0012 //reg_dpat_en = 1
    WREG        (MS_BUS_RIU_ADDR + (0x161578 << 1)), 0x0012 //reg_dpat_en = 1

    WREG        (MS_BUS_RIU_ADDR + (0x1615f4 << 1)), 0x0000 ////reg_live_test_en=0
    //mov         r2, #1
    //WREG_BITS   (MS_BUS_RIU_ADDR + (0x1012fe << 1)), r2, 11, 1 //Enable MIU bist
8:
    bx          lr
#endif

@//-------------------------------------------------------------------------------------------------
@// Miu_WriteRegTbl32
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
.global     Miu_WriteRegTbl32
Miu_WriteRegTbl32:

#if !defined(CONFIG_MIU0_DRAM_NONE)
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x1408  //SW initial done and turn on arbitor
    WREG        (MS_BUS_RIU_ADDR + (0x1012FC << 1)), 0x8000
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x1408  //SW initial done and turn on arbitor
    WREG        (MS_BUS_RIU_ADDR + (0x1006FC << 1)), 0x8000
#endif

#if !defined(CONFIG_MIU0_DRAM_NONE)
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000  //stop bist test

    //open all MIU0 request mask (All IP can access MIU resource)
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x0000  //Mask MIU1_group_0
    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0x0000  //Mask MIU1_group_1
    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0x0000  //Mask MIU1_group_2
    WREG        (MS_BUS_RIU_ADDR + (0x1012a6 << 1)), 0x0000  //Mask MIU1_group_3
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    //open all MIU1 request mask (All IP can access MIU resource)
    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x0000  //Mask MIU1_group_0
    WREG        (MS_BUS_RIU_ADDR + (0x100666 << 1)), 0x0000  //Mask MIU1_group_1
    WREG        (MS_BUS_RIU_ADDR + (0x100686 << 1)), 0x0000  //Mask MIU1_group_2
    WREG        (MS_BUS_RIU_ADDR + (0x1006a6 << 1)), 0x0000  //Mask MIU1_group_3

    //all MIU1 IP select MIU0 in bringup
    WREG        (MS_BUS_RIU_ADDR + (0x1006f0 << 1)), 0x4E88  //0x7fff
    WREG        (MS_BUS_RIU_ADDR + (0x1006f2 << 1)), 0x0000  //0xffff
    WREG        (MS_BUS_RIU_ADDR + (0x1006f4 << 1)), 0x0000  //0xffff
    WREG        (MS_BUS_RIU_ADDR + (0x1006f6 << 1)), 0x0120  //0xffff
#endif
    WREG        (MS_BUS_RIU_ADDR + (0x101842 << 1)), 0x0000  //Set MIU0 Size of MAU0
    WREG        (MS_BUS_RIU_ADDR + (0x101862 << 1)), 0x0000  //Set MIU0 Size of MAU1

    bx          lr
    
@//-------------------------------------------------------------------------------------------------
@// MiuBistTest
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
#if 0
#if !defined(CONFIG_MIU1_DRAM_NONE)
    .global     Miu1_BistTest
Miu1_BistTest:
    @//Setup for MIU1 BIST
    DPUTK       'B'
    DPUTK       'I'
    DPUTK       'S'
    DPUTK       'T'
    DPUTK       '1'
    DPUTK       '-'

    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000   @//1012e0 //reset bist test
    WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x8000   @//1012f0 bit_15=1 choice to MIU_1
    WREG        (MS_BUS_RIU_ADDR + (0x1012e2 << 1)), 0x0000   @//1012e2 //start address base unit:4 k bytes
    WREG_D      (MS_BUS_RIU_ADDR + (0x1012e4 << 1)), BIST_LEN
    WREG        (MS_BUS_RIU_ADDR + (0x1012e8 << 1)), 0x5aa5   @//1012e8 //bist test pattern

    b           BistTest
#endif

#if !defined(CONFIG_MIU0_DRAM_NONE)
    .global     Miu0_BistTest
Miu0_BistTest:
     @//Setup for MIU0 BIST
    DPUTK       '\n'
    DPUTK       '\r'
    DPUTK       'B'
    DPUTK       'I'
    DPUTK       'S'
    DPUTK       'T'
    DPUTK       '0'
    DPUTK       '-'

    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000   @//1012e0 //reset bist test
    WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x0000   @//1012f0 bit_15=0 choice to MIU_0
    WREG        (MS_BUS_RIU_ADDR + (0x1012e2 << 1)), 0x0000   @//1012e2 //start address base unit: 4k bytes
    WREG_D      (MS_BUS_RIU_ADDR + (0x1012e4 << 1)), BIST_LEN
    WREG        (MS_BUS_RIU_ADDR + (0x1012e8 << 1)), 0x5aa5   @//1012e8 //bist test pattern

#endif
#endif

    .global     Miu1_BistTest
Miu1_BistTest:

    DPUTK_STR   MIU_MESSAGE_BIST1
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000   @//1012e0 //reset bist test
    ldr         r11, =0x8000
    str         r11, [r12, #(0xf0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x8000   @//1012f0 bit_15=1 choice to MIU_1
    b           Miu_BistTest

    .global     Miu0_BistTest
Miu0_BistTest:

    DPUTK_STR   MIU_MESSAGE_BIST0
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000   @//1012e0 //reset bist test
    str         r11, [r12, #(0xf0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x0000   @//1012f0 bit_15=0 choice to MIU_0

    .global     Miu_BistTest
Miu_BistTest:
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe2 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e2 << 1)), 0x0000   @//1012e2 //start address base unit:4 k bytes

    ldr         r0, =0xFFFF
    ldr         r11, =BIST_LEN
    and         r11, r11, r0
    str         r11, [r12, #(0xe4 << 1)]
    ldr         r11, =BIST_LEN
    lsr         r11, #16
    and         r11, r11, r0
    str         r11, [r12, #(0xe6 << 1)]    @//WREG_D      (MS_BUS_RIU_ADDR + (0x1012e4 << 1)), BIST_LEN

    ldr         r11, =0x5aa5
    str         r11, [r12, #(0xe8 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e8 << 1)), 0x5aa5   @//1012e8 //bist test pattern

    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0003   @//bist test mode:3

Miu_CheckBistLoop:
    RREG        r1, (MS_BUS_RIU_ADDR + (0x1012e0 << 1))
    and         r0, r1, #0x8000
    cmp         r0, #0
    beq         Miu_CheckBistLoop

    and         r0, r1, #0x6000
    cmp         r0, #0
    beq         Miu_Bist_OK

Miu_Bist_Fail:
    DPUTK_STR   MIU_MESSAGE_FAIL

Miu_Bist_FailLoop:
    b           Miu_Bist_FailLoop

Miu_Bist_OK:
    DPUTK_STR   MIU_MESSAGE_OK

Miu_Bist_Exit:
    bx          lr

@//-------------------------------------------------------------------------------------------------
@// Miu_DramSizeCheck:
@// @param  None
@// @return None
@// @note   Set dram size
@//-------------------------------------------------------------------------------------------------
.global     Miu_DramSizeCheck
Miu_DramSizeCheck:
    mov         r13, lr
    
    @Check dram size if in AC on flow
    RREG        r0, (MS_BUS_RIU_ADDR + (0x0E70 << 1))
    and         r0, r0, #0xF000
    ldr         r1, =0xF000
    cmp         r0, r1
    bne         Miu_DramSize_DC_On

Miu_DramSize_AC_On:
    bl          Miu0_DramSizeCheck

#ifndef CONFIG_MSTAR_TITANIA_BD_FPGA
#if !defined(CONFIG_MIU1_DRAM_NONE)
    bl          Miu1_DramSizeCheck
#endif
#endif

    b           Miu_DramSize_Exit

Miu_DramSize_DC_On:
    RREG        r1, (MS_BUS_RIU_ADDR + (0x0EAA << 1)) @//Dummy register to store dram size setting
    and         r1, r1, #0x00F0
    mov         r1, r1, lsl #8
    ldr         r0, =(MS_BUS_RIU_ADDR + (0x1012d2 << 1))
    str         r1, [r0]
#if !defined(CONFIG_MIU1_DRAM_NONE)
    RREG        r1, (MS_BUS_RIU_ADDR + (0x0EAA << 1)) @//Dummy register to store dram size setting
    and         r1, r1, #0xF000
    ldr         r0, =(MS_BUS_RIU_ADDR + (0x1006d2 << 1))
    str         r1, [r0]
#endif

Miu_DramSize_Exit:

    mov         lr, r13
    bx          lr
@//-------------------------------------------------------------------------------------------------
@// Miu0_DramSizeCheck
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
Miu0_DramSizeCheck:
    ldr         r0, =0x20000000
    ldr         r1, =0x0
    str         r1, [r0]

Miu0_DramSize128M:
    ldr         r1, =0x7
    ldr         r2, =0x28000000
    str         r1, [r2]
    ldr         r3, [r0]
    cmp         r1, r3
    beq         Miu0_DramSizeSet 

Miu0_DramSize256M:
    ldr         r1, =0x8
    ldr         r2, =0x30000000
    str         r1, [r2]
    ldr         r3, [r0]
    cmp         r1, r3
    beq         Miu0_DramSizeSet 

Miu0_DramSize512M:
    ldr         r1, =0x9
    ldr         r2, =0x40000000
    str         r1, [r2]
    ldr         r3, [r0]
    cmp         r1, r3
    beq         Miu0_DramSizeSet 

Miu0_DramSize1024M:
    ldr         r1, =0xA

Miu0_DramSizeSet:
    ldr         r0, =(MS_BUS_RIU_ADDR + (0x1012d2 << 1))
    ldr         r2, =0xFFFF
    ldr         r3, [r0]
    and         r3, r3, r2
    mov         r1, r1, lsl #12
    orr         r3, r1, r3
    str         r3, [r0]
    bx          lr

@//-------------------------------------------------------------------------------------------------
@// Miu1_DramSizeCheck
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
Miu1_DramSizeCheck:
    ldr         r0, =0xA0000000
    ldr         r1, =0x0
    str         r1, [r0]

Miu1_DramSize128M:
    ldr         r1, =0x7
    ldr         r2, =0xA8000000
    str         r1, [r2]
    ldr         r3, [r0]
    cmp         r1, r3
    beq         Miu1_DramSizeSet 

Miu1_DramSize256M:
    ldr         r1, =0x8
    ldr         r2, =0xB0000000
    str         r1, [r2]
    ldr         r3, [r0]
    cmp         r1, r3
    beq         Miu1_DramSizeSet 

Miu1_DramSize512M:
    ldr         r1, =0x9
    ldr         r2, =0xC0000000
    str         r1, [r2]
    ldr         r3, [r0]
    cmp         r1, r3
    beq         Miu1_DramSizeSet 

Miu1_DramSize1024M:
    ldr         r1, =0xA

Miu1_DramSizeSet:
    ldr         r0, =(MS_BUS_RIU_ADDR + (0x1006d2 << 1))
    ldr         r2, =0xFFFF
    ldr         r3, [r0]
    and         r3, r3, r2
    mov         r1, r1, lsl #12
    orr         r3, r1, r3
    str         r3, [r0]
    bx          lr
