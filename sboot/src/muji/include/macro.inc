#ifndef _MACRO_INC_
#define _MACRO_INC_

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------
//Macro: WREG_B
//-------------------------------------------------
.macro WREG_B reg, value
    ldr         x26, =\reg
    ldr         w25, =\value
    strb        w25, [x26]
.endm

//-------------------------------------------------
//Macro: WREG
//-------------------------------------------------
.macro WREG reg, value
    ldr         x26, =\reg
    ldr         w25, =\value
    str         w25, [x26]
.endm

//-------------------------------------------------
//Macro: REG_C2M //write cpu register to mstar register
//-------------------------------------------------
.macro REG_C2M cpu_reg, mstar_reg
    ldr         x26, =\mstar_reg
    str         \cpu_reg, [x26]
.endm

//-------------------------------------------------
//Macro: RREG
//-------------------------------------------------
.macro RREG cpu_reg, mstar_reg
    ldr         x26, =\mstar_reg
    ldr         \cpu_reg, [x26]
.endm

//-------------------------------------------------
//Macro: DBGREG
//-------------------------------------------------
.macro DBGREG value
    ldr         x26, =(MS_BUS_RIU_ADDR + (0x103300 << 1))
    ldr         w25, =\value
    str         w25, [x26, #(0x80 << 1)]
.endm

//-------------------------------------------------
//Macro: MEMCPY32
//src(w28), dst(w29), len(w30) should be 32bit align
//-------------------------------------------------
.macro MEMCPY32
MEMCPY32_\@:
    ldr         w24, [w25], #4
    str         w24, [w26], #4
    subs        w27, w27,  #4
    b.ge        MEMCPY32_\@
.endm

//-------------------------------------------------
//Macro: MEMSET32
//start(w27), end(w28), value(w29)
//-------------------------------------------------
.macro MEMSET32
MEMSET32_\@:
    cmp         w25, w26
    str         w26, [w25], #4
    b.ne        MEMSET32_\@
.endm

//-------------------------------------------------
//Macro: MEMORY_FLUSH
//
//-------------------------------------------------
.macro MEMORY_FLUSH
.endm

//-------------------------------------------------
//Macro: DELAYUS
//-------------------------------------------------
.macro DELAYUS us
    ldr         x25, =(MS_BUS_RIU_ADDR + (0x003000 << 1))
    ldr         w24, =((\us * 12) & 0x0000FFFF)
    strh        w24, [x25, #(0x24 << 1)]
    ldr         w24, =(\us * 12) >> 16
    strh        w24, [x25, #(0x26 << 1)]

    ldr         w24, =0x00000002
    strh        w24, [x25, #(0x20 << 1)]
DELAYUS_\@:
    ldr         w24, [x25, #(0x22 << 1)]
    subs        w24, w24, #0x00000001
    b.ne         DELAYUS_\@
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
    RREG        w25, 0x1F006090
    REG_C2M     w25, 0x1F006088
    RREG        w27, 0x1F006094
    REG_C2M     w27, 0x1F00608C
.endm


#if defined(CONFIG_EMMC_BOOT) || \
    defined(CONFIG_BOOTING_FROM_EXT_EMMC_WITH_CPU)
.macro STG2_BLK_R
    WREG        REG_SD_MODE, 0x0054         //SD_DATSYNC | SD_CS_EN | SD_DAT_LINE1
    WREG        REG_MMA_PATH_CTL, 0x0003    //SD_EN | MMA_EN
    WREG        REG_SD_CTRL, 0x0008         //SD_DTRX_EN
    WREG        REG_BOOT_CONFIG, 0x0001     //BOOT_STG2_EN

STG2_END_\@:
    ldr         x25, =REG_BOOT_CONFIG
    ldr         x25, [x25]
    and         x25, x25, #0x01
    cmp         x25, #0x01                  //if( REG_BOOT_CONFIG & 0x1 )
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


#ifdef CONFIG_64BIT_TO_32BIT_MODE

.macro ventry  label
    .align  7
    b           \label
.endm

#endif


#endif
