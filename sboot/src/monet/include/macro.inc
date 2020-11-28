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

#ifndef _MACRO_INC_
#define _MACRO_INC_

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------
//Macro: WREG_B
//-------------------------------------------------
.macro WREG_B reg, value
    ldr         x12, =\reg
    ldr         w11, =\value
    strb        w11, [x12]
.endm

//-------------------------------------------------
//Macro: WREG
//-------------------------------------------------
.macro WREG reg, value
    ldr         x12, =\reg
    ldr         w11, =\value
    str         w11, [x12]
.endm

//-------------------------------------------------
//Macro: REG_C2M //write cpu register to mstar register
//-------------------------------------------------
.macro REG_C2M cpu_reg, mstar_reg
    ldr         x12, =\mstar_reg
    str         \cpu_reg, [x12]
.endm

#ifndef _macro_wreg_d_
.macro WREG_D reg, value
    ldr         x12, =\reg
    ldr         w11, =\value
    lsr         w11, #16
    ldr         w10, =0xFFFF
    and         w11, w11, w10
    str         w11, [x12, #4]
    ldr         w11, =\value
    ldr         w10, =0xFFFF
    and         w11, w11, w10
    str         w11, [x12]
.endm
#define _macro_wreg_d_
#endif

//-------------------------------------------------
//Macro: RREG
//-------------------------------------------------
.macro RREG cpu_reg, mstar_reg
    ldr         x12, =\mstar_reg
    ldr         \cpu_reg, [x12]
.endm

//-------------------------------------------------
//Macro: DBGREG
//-------------------------------------------------
.macro DBGREG value
    ldr         x12, =(MS_BUS_RIU_ADDR + (0x103300 << 1))
    ldr         w11, =\value
    str         w11, [x12, #(0x80 << 1)]
.endm

//-------------------------------------------------
//Macro: MEMCPY32
//src(x10), dst(x11), len(x12) should be 32bit align
//-------------------------------------------------
.macro MEMCPY32
MEMCPY32_\@:
    ldr         x9, [x10], #4
    str         x9, [x11], #4
    subs        x12, x12,  #4
    b.ge        MEMCPY32_\@
.endm

//-------------------------------------------------
//Macro: MEMSET32
//start(x10), end(x11), value(x12)
//-------------------------------------------------
.macro MEMSET32
MEMSET32_\@:
    cmp         x10, x11
    str         x12, [x10], #4
    b.ne        MEMSET32_\@
.endm

//-------------------------------------------------
//Macro: MEMORY_FLUSH
//
//-------------------------------------------------
.macro MEMORY_FLUSH
    RREG        w10, 0x1f203114
    and         w10, #0x01
    ldr         x12, =0x1f203114
    str         w10, [x12]

MEMORY_FLUSH_done\@:
    RREG        w10, 0x1f203140
    and         w10, #0x1000
    cmp         w10, #0x1000
    beq         MEMORY_FLUSH_done\@
.endm

//-------------------------------------------------
//Macro: DELAYUS
//-------------------------------------------------
.macro DELAYUS us
#if 0
    ldr         w12, =\us
DELAYUS_\@:
    subs        w12, #1
    bne         DELAYUS_\@
#else
    ldr         x12, =(MS_BUS_RIU_ADDR + (0x003000 << 1))
    ldr         w11, =((\us * 12) & 0x0000FFFF)
    strh        w11, [x12, #(0x24 << 1)]
    ldr         w11, =(\us * 12) >> 16
    strh        w11, [x12, #(0x26 << 1)]

    ldr         w11, =0x00000002
    strh        w11, [x12, #(0x20 << 1)]
DELAYUS_\@:
    ldr         w11, [x12, #(0x22 << 1)]
    subs        w11, w11, #0x00000001
    b.ne        DELAYUS_\@
#endif
.endm

//-------------------------------------------------
//Macro: TIMER HEAD (for rum time mesurement)
//-------------------------------------------------
.macro TIMER_HEAD
    WREG        0x1F006080, 0x0000
    WREG        0x1F006088, 0xFFFF
    WREG        0x1F00608C, 0xFFFF
    WREG        0x1F006080, 0x0001
.endm

//-------------------------------------------------
//Macro: TIMER_TAIL (for rum time mesurement)
//-------------------------------------------------
.macro TIMER_TAIL
    RREG        w1, 0x1F006090
    REG_C2M     w1, 0x1F006088
    RREG        w2, 0x1F006094
    REG_C2M     w2, 0x1F00608C
.endm


#if defined(CONFIG_EMMC_BOOT) || \
    defined(CONFIG_BOOTING_FROM_EXT_EMMC_WITH_CPU)
.macro STG2_BLK_R
    WREG        REG_SD_MODE, 0x0054         //SD_DATSYNC | SD_CS_EN | SD_DAT_LINE1
    WREG        REG_MMA_PATH_CTL, 0x0003    //SD_EN | MMA_EN
    WREG        REG_SD_CTRL, 0x0008         //SD_DTRX_EN
    WREG        REG_BOOT_CONFIG, 0x0001     //BOOT_STG2_EN

STG2_END_\@:
    ldr         x12, =REG_BOOT_CONFIG
    ldr         x12, [x12]
    and         x12, x12, #0x01
    cmp         x12, #0x01                  //if( REG_BOOT_CONFIG & 0x1 )
    b.eq        STG2_END_\@                 //    goto STG2_END_\@
.endm
#endif

#ifdef CONFIG_MSTAR_STR_ENABLE
MSTAR_STR_SBOOT_RESUME  = 0
MSTAR_SLEEP_MAGIC       = 0x4D535452

PMU_WAKEUP_ADDR_REGL    = 0x1F001CE0
PMU_WAKEUP_ADDR_LMASK   = 0x000000FF
PMU_WAKEUP_ADDR_REGH    = 0x1F001CE4
PMU_WAKEUP_ADDR_HMASK   = 0x0000FF00


WAKEUP_ADDR_MASK        = 0x0000FFF0
WAKEUP_FLAG_MASK        = 0x0000000F
WAKEUP_FLAG_INVALID     = 0
WAKEUP_FLAG_SLEPT       = 1
WAKEUP_FLAG_WKUP        = 2

.macro is_slept
    bl          read_wkup_pmu
    and         w0, w0, #WAKEUP_FLAG_MASK
    cmp         w0, #WAKEUP_FLAG_SLEPT
.endm

.macro is_wakeup
    bl          read_wkup_pmu
    and         w0, w0, #WAKEUP_FLAG_MASK
    cmp         w0, #WAKEUP_FLAG_WKUP
.endm

.macro set_wakeup
    bl          read_wkup_pmu
    bic         w0, w0, #WAKEUP_FLAG_MASK
    orr         w0, w0, #WAKEUP_FLAG_WKUP
    bl          write_wkup_pmu
.endm
#endif


/*
 * Enable and disable interrupts.
 */
.macro disable_irq
    msr         daifset, #2
.endm

.macro enable_irq
    msr         daifclr, #2
.endm

/*
 * Save/disable and restore interrupts.
 */
.macro save_and_disable_irqs, olddaif
    mrs         \olddaif, daif
    disable_irq
.endm

.macro restore_irqs, olddaif
    msr         daif, \olddaif
.endm

#endif
