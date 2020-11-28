@###############################################################################
@
@ Copyright (c) 2006-2009 MStar Semiconductor, Inc.
@ All rights reserved.
@
@ Unless otherwise stipulated in writing, any and all information contained
@ herein regardless in any format shall remain the sole proprietary of
@ MStar Semiconductor Inc. and be kept in strict confidence
@ ("MStar Confidential Information") by the recipient.
@ Any unauthorized act including without limitation unauthorized disclosure,
@ copying, use, reproduction, sale, distribution, modification, disassembling,
@ reverse engineering and compiling of the contents of MStar Confidential
@ Information is unlawful and strictly prohibited. MStar hereby reserves the
@ rights to any and all damages, losses, costs and expenses resulting therefrom.
@
@###############################################################################

#include "boot.inc"
#include "macro.inc"
#include "drv_arm.inc"
    .text

.globl _vector
_vector:
    b BOOT_Entry
_undefined_instruction:
    b .
_software_interrupt:
    b .
_prefetch_abort:
    b .
_data_abort:
    b .
_not_used:
    b .
_irq:
    b .
_fiq:
    b .
#-------------------------------------------------------------------------------------------------
# BOOT_Entry:
# @param  None
# @return None
# @note   Entry point of Boot code
#-------------------------------------------------------------------------------------------------
    .globl  BOOT_Entry
BOOT_Entry:

#if !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)
    # inital PIU timers to measure boot time
    WREG  0x1f006040, 0x0000
    WREG  0x1f006040, 0x0001
    WREG  0x1f006088, 0xFFFF
    WREG  0x1f00608C, 0xFFFF
    WREG  0x1f006080, 0x0000
    WREG  0x1f006080, 0x0001
#endif

ROM_start:

    # disable watch dog
    WREG  0x1f006010, 0x0000
    WREG  0x1f006014, 0x0000

    DBGREG  0x0001

#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) || \
    defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)

	@//enable PM51 can access nonPM RIU(TV tool access MIU also)
	RREG        r3, (MS_BUS_RIU_ADDR + (0x123960 << 1))
    ldr         r4, =0x00000004
    orr         r3, r3, r4
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x123960 << 1))

    ldr         r0, =__secondary_a_core
    ldr         r1, =0xFFFF
    mov         r2, r0, lsr #16
    and         r2, r2, r1
    REG_C2M     r2, BOOT_INFO_REGISTER_CORE1_START_ADDR_HIGH

    and         r2, r0, r1
    REG_C2M     r2, BOOT_INFO_REGISTER_CORE1_START_ADDR_LOW

#endif

#ifndef CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51 
    RREG        r8, (MS_BUS_RIU_ADDR + (0x2E52 << 1))
    bic         r8, r8, #0x1000
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x2E52 << 1))
#endif

    #//disable vdd2low_rst function  and change chip_top_password to non-default value
    RREG        r3, (MS_BUS_RIU_ADDR + (0x002E52 << 1))
    ldr         r4, =0x0000003F
    orr         r3, r3, r4
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x002E52 << 1))

#if !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)
    @
    @ First ensure all interrupts are disabled.
    @
    MRS     r0, CPSR
    ORR     r0, r0, #0xc0  @ Disable IRQ & FIQ
    ORR     r0, r0, #0xd3      @ARM mode,Supervisor mode
    MSR     CPSR_c, r0

    @
    @ Ensure that the MMU and caches are off
    @
    MRC     p15, 0, r0, c1, c0, 0           @ Get control register
    BIC     r0, r0, #0x1                  @ Disable MMU
    BIC     r0, r0, #0x4                  @ Disable D Cache
    BIC     r0, r0, #0x1000                  @ Disable I Cache
    MCR     p15, 0, r0, c1, c0, 0           @ Write control register
#endif

     @
     @ If Cortex A Class handle secondary cores
     @
    mrc     p15, 0, r0, c0, c0, 5
    and r0, #0x3
    cmp r0, #0
    beq Core0_Next

    BL      __secondary_a_core                @ Will not return

 Core0_Next :
    # Jump to BOOTROM_Entry
    ldr   pc, =BOOTROM_Entry

__secondary_a_core:
    @Enable software interrupt
    ldr r5 , =0x16000100    @CPU_INTERFACE -> control register
    mov r6, #0x1
    str r6, [r5,#0x0]
    mov r6, #0xf0
    str r6, [r5,#0x4]       @CPU_INTERFACE -> priority mask register

    @ SECOND_START_ADDR_HI = 0x1f206740
    @ SECOND_START_ADDR_LO = 0x1f206744
    @ set LSB[1:0] of LO = 2'b11, then wait soft interrupt to wake up
    WREG 0x1f206744, 0xff
    #WREG 0x1f20674c, 0x3344  @debug
    wfi   @wait SWI to check
    ARM_INIT

    @let core1 go to bootram.S
    ldr pc, =core1_loop
    #WREG 0x1f20674c, 0x7788  @debug
    @RREG r0, 0x1f206744
    @and  r0, #0x3
    @cmp  r0, #0
    @bne __secondary_a_core   @make sure start address of secondary is legal
    #WREG 0x1f20674c, 0x5566  @debug
    @RREG r0, 0x1f206740
    @RREG r1, 0x1f206744
    @add r2, r1,r0,lsl #16
    @mov pc, r2

    #ldr   pc,=__secondary_a_core
    @ core1 will not run here
    loop:
    ldr pc, =loop


#-------------------------------------------------------------------------------------------------
# BOOT_Pad
# @param  None
# @return None
# @note   Pad with zeros (Reserve SIZE_BOOT_RESERVED Bytes for boot)
#-------------------------------------------------------------------------------------------------
    @.org    (SIZE_BOOT_RESERVED-4)
    @.word   0
