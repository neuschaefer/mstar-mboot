#ifndef _MACRO_INC_
#define _MACRO_INC_

@//-------------------------------------------------------------------------------------------------
@// Macros
@//-------------------------------------------------------------------------------------------------

@//-------------------------------------------------
@//Macro: WREG_B
@//-------------------------------------------------
.macro WREG_B reg, value
    ldr         r12, =\reg
    ldr         r11, =\value
    strb        r11, [r12]
.endm

@//-------------------------------------------------
@//Macro: WREG
@//-------------------------------------------------
.macro WREG reg, value
    ldr         r12, =\reg
    ldr         r11, =\value
    str         r11, [r12]
.endm

@//-------------------------------------------------
@//Macro: WREG_BITS
@//-------------------------------------------------
.macro WREG_BITS reg, cpu_reg, bit, num
    mov         r11, \cpu_reg
    ldr         r12, =\reg
    ldr         r10, =((1 << ((\num) + 1)) - 1)
    and         r11, r11, r10
    lsl         r11, #\bit
    ldr         r10, [r12]
    ldr         r9,  =(~(((1 << ((\num) + 1)) - 1) << (\bit)))
    and         r10, r10, r9
    orr         r11, r11, r10
    str         r11, [r12]   
.endm

@//-------------------------------------------------
@//Macro: REG_C2M //write cpu register to mstar register
@//-------------------------------------------------
.macro REG_C2M cpu_reg, mstar_reg
    ldr         r12, =\mstar_reg
    str         \cpu_reg, [r12]
.endm

#ifndef _macro_wreg_d_
.macro WREG_D reg, value
    ldr         r12, =\reg
    ldr         r11, =\value
    lsr         r11, #16
    ldr         r10, =0xFFFF
    and         r11, r11, r10
    str         r11, [r12, #4]
    ldr         r11, =\value
    ldr         r10, =0xFFFF
    and         r11, r11, r10
    str         r11, [r12]
.endm
#define _macro_wreg_d_
#endif

@//-------------------------------------------------
@//Macro: RREG
@//-------------------------------------------------
.macro RREG cpu_reg, mstar_reg
    ldr         r12, =\mstar_reg
    ldr         \cpu_reg, [r12]
.endm

@//-------------------------------------------------
@//Macro: RREG_BITS
@//-------------------------------------------------
.macro RREG_BITS cpu_reg, mstar_reg, bit, num
    ldr         r12, =\mstar_reg
    ldr         \cpu_reg, [r12]
    ldr         r11, =(32-(\bit)-(\num))
    mov         \cpu_reg, \cpu_reg, lsl r11
    ldr         r11, =(32-(\num))
    mov         \cpu_reg, \cpu_reg, lsr r11
.endm
@//-------------------------------------------------
@//Macro: GET_BITS
@//-------------------------------------------------
.macro GET_BITS target_reg, source_reg, bit, num
    ldr         r12, =(32-(\bit)-(\num))
    mov         \target_reg, \source_reg, lsl r12
    ldr         r12, =(32-(\num))
    mov         \target_reg, \target_reg, lsr r12
.endm

@//-------------------------------------------------
@//Macro: REFUSE (Read EFUSE)
@//-------------------------------------------------
.macro REFUSE reg, addr
#if 1
      nop
      ldr         r12, =(MS_BUS_RIU_ADDR + (0x2000 << 1))
      
      ldr         r11, [r12, #(0x004e << 1)]
      ldr         r10, =0x017f
      bic         r11, r11, r10
      orr         r11, r11, #\addr
      str         r11, [r12, #(0x004e << 1)]
      
      ldr         r11, [r12, #(0x004C << 1)]
      orr         r11, r11, #0x1
      str         r11, [r12, #(0x004C << 1)]
      
      ldr         r10, =0xfffffffe
_REFUSE_\@:      
      ldr         r11, [r12, #(0x004C << 1)]
      bic         r11, r11, r10
      cmp         r11, #0
      bne         _REFUSE_\@
      
      ldr         \reg, [r12, #(0x0080 << 1)]
      ldr         r11, [r12, #(0x0082 << 1)]
      orr         \reg, r11, lsl #16
                    
#else
    ldr         r12, =\addr
    ldr         r11, =0x3FFF7F5D
    ldr         r10, =0x00003FB4
    cmp         r12, #0x29
    moveq       \reg, r11
    movne       \reg, r10
#endif
.endm

@//-------------------------------------------------
@//Macro: DBGREG
@//-------------------------------------------------
.macro DBGREG value
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x103300 << 1))
    ldr         r11, =\value
    str         r11, [r12, #(0x80 << 1)]
.endm
@//-------------------------------------------------
@//Macro: MEMCPY32
@//src(r10), dst(r11), len(r12) should be 32bit align
@//-------------------------------------------------
.macro MEMCPY32
MEMCPY32_\@:
    ldr         r9, [r10], #4
    str         r9, [r11], #4
    subs        r12, r12,  #4
    bne         MEMCPY32_\@
.endm

@//-------------------------------------------------
@//Macro: MEMSET32
@//start(r10), end(r11), value(r12)
@//-------------------------------------------------
.macro MEMSET32
MEMSET32_\@:
clear_bss:
    cmp         r10, r11
    str         r12, [r10], #4
    bne         MEMSET32_\@
.endm

@//-------------------------------------------------
@//Macro: MEMORY_FLUSH
@//
@//-------------------------------------------------
.macro MEMORY_FLUSH
    RREG        r10,0x1f203114
    and         r10,#0x01
    ldr         r12,=0x1f203114
    str         r10,[r12]

MEMORY_FLUSH_done\@:
    RREG        r10,0x1f203140
    and         r10,#0x1000
    cmp         r10, #0x1000
    beq         MEMORY_FLUSH_done\@
.endm

@//-------------------------------------------------
@//Macro: DELAYUS
@//-------------------------------------------------
.macro DELAYUS us
#if 0
    ldr         r12, =\us
DELAYUS_\@:
    subs        r12, #1
    bne         DELAYUS_\@
#else
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x003000 << 1))
    ldr         r11, =(\us * 12) & 0x0000FFFF
    str         r11, [r12, #(0x24 << 1)]
    ldr         r11, =(\us * 12) >> 16
    str         r11, [r12, #(0x26 << 1)]

    ldr         r11, =0x00000002
    str         r11, [r12, #(0x20 << 1)]
DELAYUS_\@:
    ldr         r11, [r12, #(0x22 << 1)]
    subs        r11, r11, #0x00000001
    bne         DELAYUS_\@
#endif
.endm

@//-------------------------------------------------
@//Macro: TIMER HEAD (for rum time mesurement)
@//-------------------------------------------------
.macro TIMER_HEAD
    WREG        0x1F006080, 0x0000
    WREG        0x1F006088, 0xFFFF
    WREG        0x1F00608C, 0xFFFF
    WREG        0x1F006080, 0x0001
.endm

@//-------------------------------------------------
@//Macro: TIMER_TAIL (for rum time mesurement)
@//-------------------------------------------------
.macro TIMER_TAIL
    RREG        r1, 0x1F006090
    REG_C2M     r1, 0x1F006088
    RREG        r2, 0x1F006094
    REG_C2M     r2, 0x1F00608C
.endm


#if defined(CONFIG_EMMC_BOOT) || \
    defined(CONFIG_BOOTING_FROM_EXT_EMMC_WITH_CPU)
.macro STG2_BLK_R
    WREG        REG_SD_MODE, 0x0054         @//SD_DATSYNC | SD_CS_EN | SD_DAT_LINE1
    WREG        REG_MMA_PATH_CTL, 0x0003    @//SD_EN | MMA_EN
    WREG        REG_SD_CTRL, 0x0008         @//SD_DTRX_EN
    WREG        REG_BOOT_CONFIG, 0x0001     @//BOOT_STG2_EN

STG2_END_\@:

    ldr         r12, =REG_BOOT_CONFIG
    ldr         r12, [r12]
    and         r12, r12, #0x01
    cmp         r12, #0x01                  @//if( REG_BOOT_CONFIG & 0x1 )
    beq         STG2_END_\@                 @//    goto STG2_END_\@
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
    and         r0, r0, #WAKEUP_FLAG_MASK
    cmp         r0, #WAKEUP_FLAG_SLEPT
.endm

.macro is_wakeup
    bl          read_wkup_pmu
    and         r0, r0, #WAKEUP_FLAG_MASK
    cmp         r0, #WAKEUP_FLAG_WKUP
.endm

.macro set_wakeup
    bl          read_wkup_pmu
    bic         r0, r0, #WAKEUP_FLAG_MASK
    orr         r0, r0, #WAKEUP_FLAG_WKUP
    bl          write_wkup_pmu
.endm
#endif

#endif
