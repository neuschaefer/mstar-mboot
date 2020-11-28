@-------------------------------------------------------------------------------------------------
@ Macros
@-------------------------------------------------------------------------------------------------
.macro REGB_SET_BIT reg, u8mask
    ldr    r11, =(\reg << 1)
    ldr    r12, =\reg
    and    r12, r12, #0x1
    sub    r11, r11, r12
    ldr    r12, = (MS_BUS_RIU_ADDR)
    add    r11, r11, r12
		
    ldrb   r12, [r11]
    ldr    r10, =\u8mask
    orr    r12, r12, r10
    strb   r12, [r11]
.endm

.macro REGB_CLR_BIT reg, u8mask
    ldr    r11, =(\reg << 1)
    ldr    r12, =\reg
    and    r12, r12, #0x1
    sub    r11, r11, r12
    ldr    r12, = (MS_BUS_RIU_ADDR)
    add    r11, r11, r12

    ldrb   r12, [r11]
    ldr    r10, =\u8mask
    bic    r12, r12, r10
    strb   r12, [r11]
.endm

@-------------------------------------------------
@Macro: WREG_B
@-------------------------------------------------
.macro WREG_B reg, value
LDR     r12, =\reg
LDR     r11, =\value
STRB    r11, [r12]
.endm

@-------------------------------------------------
@Macro: WREG
@-------------------------------------------------
#if !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)
.macro WREG reg, value
LDR     r12, =\reg
LDR     r11, =\value
STR     r11, [r12]
    b 1f
    .ltorg
1:
.endm
#else
.macro WREG reg, value
LDR     r12, =\reg
LDR     r11, =\value
STR     r11, [r12]
.endm
#endif

@-------------------------------------------------
@Macro: REG_C2M //write cpu register to mstar register
@-------------------------------------------------
.macro REG_C2M cpu_reg, mstar_reg
LDR     r12, =\mstar_reg
STR     \cpu_reg, [r12]
.endm

@-------------------------------------------------
@Macro: RREG
@-------------------------------------------------
.macro RREG cpu_reg, mstar_reg
LDR     r12, =\mstar_reg
LDR     \cpu_reg, [r12]
.endm

@-------------------------------------------------
@Macro: DBGREG
@-------------------------------------------------
.macro DBGREG value
    WREG    0x1F206700, \value
.endm

@-------------------------------------------------
@Macro: MEMCPY32
@src(r10), dst(r11), len(r12) should be 32bit align
@-------------------------------------------------
.macro MEMCPY32
MEMCPY32_\@:
    LDR     r9, [r10], #4
    STR     r9, [r11], #4
    SUBS    r12, r12,  #4
    BNE     MEMCPY32_\@
.endm

@-------------------------------------------------
@Macro: MEMSET32
@start(r10), end(r11), value(r12)
@-------------------------------------------------
.macro MEMSET32
MEMSET32_\@:
clear_bss:
    cmp r10, r11
    str r12, [r10], #4
    BNE MEMSET32_\@
.endm

@-------------------------------------------------
@Macro: MEMORY_FLUSH
@
@-------------------------------------------------
.macro MEMORY_FLUSH
    RREG r10,0x1f203114
    AND  r10,#0x01
    LDR  r12,=0x1f203114
    STR  r10,[r12]
MEMORY_FLUSH_done\@:
    RREG  r10,0x1f203140
    AND  r10,#0x1000
    CMP  r10, #0x1000
    BEQ  MEMORY_FLUSH_done\@
.endm

@-------------------------------------------------
@Macro: DELAYUS
@-------------------------------------------------
.macro DELAYUS us
#if 0
    LDR     r12, =\us
DELAYUS_\@:
    SUBS    r12, #1
    BNE     DELAYUS_\@
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

@-------------------------------------------------
@Macro: TIMER HEAD (for rum time mesurement)
@-------------------------------------------------
.macro TIMER_HEAD
    WREG    0x1F006080, 0x0000
    WREG    0x1F006088, 0xFFFF
    WREG    0x1F00608C, 0xFFFF
    WREG    0x1F006080, 0x0001
.endm

@-------------------------------------------------
@Macro: TIMER_TAIL (for rum time mesurement)
@-------------------------------------------------
.macro TIMER_TAIL
    RREG    r1, 0x1F006090
    REG_C2M r1, 0x1F006088
    RREG    r2, 0x1F006094
    REG_C2M r2, 0x1F00608C
.endm

.if(CONFIG_MSTAR_STR_ENABLE == 1)
MSTAR_STR_SBOOT_RESUME   = 0
MSTAR_SLEEP_MAGIC         = 0x4D535452

PMU_WAKEUP_ADDR_REGL     = 0x1F001CE0
PMU_WAKEUP_ADDR_LMASK    = 0x000000FF
PMU_WAKEUP_ADDR_REGH     = 0x1F001CE4
PMU_WAKEUP_ADDR_HMASK    = 0x0000FF00


WAKEUP_ADDR_MASK          = 0x0000FFF0
WAKEUP_FLAG_MASK          = 0x0000000F
WAKEUP_FLAG_INVALID       = 0
WAKEUP_FLAG_SLEPT         = 1
WAKEUP_FLAG_WKUP          = 2

.macro is_slept
	bl read_wkup_pmu
	and r0, r0, #WAKEUP_FLAG_MASK
	cmp r0, #WAKEUP_FLAG_SLEPT
.endm

.macro is_wakeup
	bl read_wkup_pmu
	and r0, r0, #WAKEUP_FLAG_MASK
	cmp r0, #WAKEUP_FLAG_WKUP
.endm

.macro set_wakeup
	bl read_wkup_pmu
	bic r0, r0, #WAKEUP_FLAG_MASK
	orr r0, r0, #WAKEUP_FLAG_WKUP
	bl write_wkup_pmu
.endm
.endif
