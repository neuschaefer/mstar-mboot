################################################################################
#
# Copyright (c) 2006-2009 MStar Semiconductor, Inc.
# All rights reserved.
#
# Unless otherwise stipulated in writing, any and all information contained
# herein regardless in any format shall remain the sole proprietary of
# MStar Semiconductor Inc. and be kept in strict confidence
# (¡§MStar Confidential Information¡¨) by the recipient.
# Any unauthorized act including without limitation unauthorized disclosure,
# copying, use, reproduction, sale, distribution, modification, disassembling,
# reverse engineering and compiling of the contents of MStar Confidential
# Information is unlawful and strictly prohibited. MStar hereby reserves the
# rights to any and all damages, losses, costs and expenses resulting therefrom.
#
################################################################################


#include "boot.inc"
#include "macro.inc"
#include "drv_miu.inc"
#include "drv_uart.inc"
#include "drv_clk.inc"
#include "drv_arm.inc"
#include "drv_misc.inc"

#[*] Copy bootram from ROM to DRAM
@-------------------------------------------------
@Macro: BOOTROM_LoadBootRAM
@-------------------------------------------------
.macro BOOTROM_LoadBootRAM
    LDR     r10, =_ld_bootram_ROM_start
    LDR     r11, =_ld_bootram_RAM_start
    LDR     r12, =_ld_bootram_RAM_end
    LDR     r9,  =_ld_bootram_RAM_start
    SUB     r12, r12, r9
    MEMCPY32
.endm

#-------------------------------------------------------------------------------------------------
# BOOTROM_Entry:
# @param  None
# @return None
# @note   Entry point of Boot code
#-------------------------------------------------------------------------------------------------
    .globl  BOOTROM_Entry
BOOTROM_Entry:
    DBGREG  0x0003
    drv_misc_tvtool_access_miu
    DBGREG  0x0004
.if(IS_FPGA == 0)
    drv_clk_mpll_init
    DBGREG  0x0006
    drv_clk_gen0_dvbt_init
    DBGREG  0x0008
.endif
.if(IS_FPGA == 0)
    drv_clk_L2_clk_ratio
.if (BOOTING_FROM_EXT_SPI_WITH_PM51 != 1)
    bl BootRom_InitSpiFlashClock
    bl BootRom_ChangeSpiFlashClock
.endif
.endif
    ARM_INIT
.if(IS_FPGA == 0)
    ldr r0, =padInitTbl
    add r0, r0, #10
    bl MDrv_WriteRegMaskTbl
.endif

.if(IS_FPGA == 1)
    drv_uart_init_fpga
    DBGREG  0x0009
    drv_miu_init_fpga
    DBGREG  0x000A
.else
    drv_uart_init	
    DBGREG  0x0009

# checkpoint for autotest boottime, plz dont remove it
    DPUTK '['
    DPUTK 'A'
    DPUTK 'T'
    DPUTK ']'
    DPUTK '['
    DPUTK 'M'
    DPUTK 'B'
    DPUTK ']'
    DPUTK '['
    DPUTK 's'
    DPUTK 't'
    DPUTK 'a'
    DPUTK 'r'
    DPUTK 't'
    DPUTK ' '
    DPUTK 's'
    DPUTK 'b'
    DPUTK ']'
    DPUTK '['
    DPUTK '0'
    DPUTK ']'
	
.if (BOOTING_FROM_EXT_SPI_WITH_PM51 != 1)
    drv_miu_init
.endif
    DBGREG  0x000A
    WREG  0x1f203104, 0x8404  @RIU support 32 bit write data enable
.endif

#ifdef CONFIG_MSTAR_MOBF_ENABLE
    @//Enable MOBF Function for Secure Usage
    bl          BootRom_InitMobf
#endif

    drv_arm_fpu_init
    DBGREG  0x000D
    #drv_misc_riu32_bitmask

    DBGREG  0x0010
.if (EMMC_BOOT == 1)
    @ Copy chunk header from EMMC boot partition to DRAM
    bl     BOOT_CopyHeader_EMMC
    nop
    @ Copy uboot binary from EMMC boot partition to DRAM
    bl     BOOT_CopyUboot_EMMC
    nop

    mov		pc, r4

.else
    @ Copy bootram from ROM to DRAM
    BOOTROM_LoadBootRAM

    drv_arm_gic_init
    drv_arm_Set_Intr_Core0_1
    DBGREG  0x0011

.if(CONFIG_MSTAR_STR_ENABLE == 1)
.if(MSTAR_STR_SBOOT_RESUME==1)
    bl  read_wkup_pmu
    bl  put_reg_val

    is_slept
    bne   1f
    set_wakeup
    b     2f
1:
    eor   r0, r0, r0
    bl    write_wkup_pmu
2:
    is_wakeup
    bne 3f
    PUTK 'W'
    PUTK 'K'
    PUTK 'P'
    bl  read_wkup_pmu
    bic r0, r0, #WAKEUP_FLAG_MASK
    mov r0, r0, lsl #16                   //@ wake up info addr
    ldmia r0, {r1-r2}
    ldr   r0, =MSTAR_SLEEP_MAGIC
    cmp   r1, r0
    bne   3f
    PUTK 'J'
    cmp   r2, #0
    beq   3f
    PUTK 'M'
    mov   pc, r2                          //@ jump to wakup addr
3:
.endif
.endif
    # Jump to BOOTRAM_Entry
    ldr   pc, =BOOTRAM_Entry
.endif


.if (EMMC_BOOT == 1)
@-------------------------------------------------------------------------------------------------
@ BOOT_CopyHeader_EMMC
@ @param  None
@ @return None
@ @note   Copy Chunk Header from EMMC to DRAM
@-------------------------------------------------------------------------------------------------
EMMC_HEADER_SIZE = 0x0002                             @ Size = 1KB
EMMC_HEADER_ADDR_BYTE = (0x40200000 >> 3)

RAM_START = 0x40200004
RAM_END = 0x40200008
RAM_ENTRY = 0x40200010

BOOT_CopyHeader_EMMC:

	@ Set the FCIE reg_dma_addr_26_16
	LDR		r12, =EMMC_HEADER_ADDR_BYTE
	MOV		r11, r12, LSR #16
	LDR		r12, =REG_MIU_ADDR_H
	STR		r11, [r12]

	@ Set the FCIE reg_dma_addr_15_0
	LDR		r1, =0xFFFF
    LDR     r12, =EMMC_HEADER_ADDR_BYTE
    AND     r11, r12, r1
    LDR     r12, =REG_MIU_ADDR_L
    STR     r11, [r12]

    @ Set the FCIE reg_job_bl_cnt
    LDR     r12, =REG_JOB_BL_CNT
    LDR     r11, =EMMC_HEADER_SIZE
    STR     r11, [r12]

    STG2_BLK_R
    MEMORY_FLUSH

    LDR		r12, =RAM_START			@ RAM_START
    LDR		r9, [r12]

    LDR		r11, =RAM_END			@ RAM_END
    LDR		r8, [r11]

    SUB		r10, r8, r9				@ RAM_SIZE = RAM_END-RAM_START

    MOV		r10, r10, LSR #9			@SIZE = (RAM_SIZE /512)+1
    ADD		r10, r10, #1

    MOV		r8, r9, LSR #3			@ RAM_START/miu_length convert to miu address

    LDR		r12, = RAM_ENTRY		@ RAM_ENTRY
    LDR		r4, [r12]

    MOV     PC, LR						@ return
.endif

.if(CONFIG_MSTAR_STR_ENABLE == 1)
read_wkup_pmu:
    ldr r2, =PMU_WAKEUP_ADDR_REGL
    ldr r0, [r2]

    ldr r2, =PMU_WAKEUP_ADDR_REGH
    ldr r1, [r2]

    and r0, r0, #PMU_WAKEUP_ADDR_LMASK
    and r1, r1, #PMU_WAKEUP_ADDR_HMASK
    orr r0, r0, r1
    mov pc, lr
    .ltorg

write_wkup_pmu:
    ldr r3, =PMU_WAKEUP_ADDR_REGL
    ldr r1, [r3]
    bic r1, #PMU_WAKEUP_ADDR_LMASK
    and r2, r0, #PMU_WAKEUP_ADDR_LMASK
    orr r1, r1, r2
    str r1, [r3]

    ldr r3, =PMU_WAKEUP_ADDR_REGH
    ldr r1, [r3]
    bic r1, #PMU_WAKEUP_ADDR_HMASK
    and r2, r0, #PMU_WAKEUP_ADDR_HMASK
    orr r1, r1, r2
    str r1, [r3]
    mov pc, lr
    .ltorg
text_tbl: .long '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
/* r9-r12 destroyed */
put_reg_val:
    mov   r9, #32
    mov   r11, #0x0F
40:
    sub   r9, #4
    and   r10, r11, r0, LSR r9
    ldr   r12, =text_tbl
    add   r12, r12, r10, lsl #2
    ldr   r10,  [r12]
    mov   r12, #0x1F000000
    orr   r12, r12, #0x00200000
    orr   r12, r12, #0x1300
    strb  r10,[r12]
    cmp   r9, #0
    bgt   40b

    //mov   r10, #'\r'      /* new line */
    //strb  r10,[r12]
    //mov   r10, #'\n'
    //strb  r10,[r12]
    mov   r10, #'-'
    strb  r10,[r12]

    mov pc, lr
    .ltorg
.endif

.if (EMMC_BOOT == 1)
#-------------------------------------------------------------------------------------------------
# BOOT_CopyUboot_EMMC
# @param  None
# $11 : FCIE DMA ADDRESS
# $10 : JOB_BL_CNT
# @return None
# @note   Copy Uboot binary from EMMC to DRAM
#-------------------------------------------------------------------------------------------------
EMMC_MAX_BLK_CNT = 4095
BOOT_CopyUboot_EMMC:

	@ Set the FCIE reg_dma_addr_26_16
	MOV		r11, r8, LSR #16
	LDR		r12, =REG_MIU_ADDR_H
	STR		r11, [r12]

	@ Set the FCIE reg_dma_addr_15_0
	LDR		r1, =0xFFFF
    AND     r11, r8, r1
    LDR     r12, =REG_MIU_ADDR_L
    STR     r11, [r12]

	@ If block count > 4095, goto GRT_MAX_CNT
	LDR		r9, =EMMC_MAX_BLK_CNT
	CMP		r10, r9
	BGT		GRT_MAX_CNT

	@ If block count <= 4095, set the block count
    LDR     r12, =REG_JOB_BL_CNT
    STR     r10, [r12]
    MOVS	r10, #0

	@ Goto SEND_STG2_BLK
	LDR		PC, =SEND_STG2_BLK

GRT_MAX_CNT:
	LDR     r12, =REG_JOB_BL_CNT
    STR     r9, [r12]
    SUB		r10, r10, r9

SEND_STG2_BLK:

    STG2_BLK_R
    MEMORY_FLUSH

    @ If r10 == 0, goto SEND_BLK_END (All block are transferred.)
    MOVS	r0, #0
    CMP		r10, r0
    BEQ		SEND_BLK_END

    LDR     r12, =REG_JOB_BL_CNT
    LDR		r11, [r12]
    MOV		r9, r11, LSL #9
    ADD		r8, r8, r9

    LDR		PC, =BOOT_CopyUboot_EMMC

SEND_BLK_END:
    WREG     REG_BOOT_CONFIG, 0x0002	@ Set EMMC boot operation end

    MOV		PC, LR

.endif


BootRom_InitSpiFlashClock:

    WREG_B      (MS_BUS_RIU_ADDR + (0x0008E2 << 1)), 0xFF       @//Set CSZ deselect time to 16 SPI clock cycles
                                                                @//Set CSZ setup time to 16 SPI clock cycles
    WREG_B      (MS_BUS_RIU_ADDR + (0x0008E2 << 1) + 1), 0x0F   @//Set CSZ hold time to 16 SPI clock cycles
    WREG_B      (MS_BUS_RIU_ADDR + (0x0008E4 << 1)), 0x01       @//Enable fast read mode

    bx          lr

BootRom_ChangeSpiFlashClock:

    WREG_B      (MS_BUS_RIU_ADDR + (0x000E40 << 1) + 1), 0x04   @//Set clock of clk_spi to 86MHz
    WREG_B      (MS_BUS_RIU_ADDR + (0x000E40 << 1) + 1), 0x44   @//Switch clk_spi between clk_mcu_p and clk_ext_xtali_buf
    WREG_B      (MS_BUS_RIU_ADDR + (0x000E40 << 1)), 0x80		@//Set clock of MCU to 170MHz

    bx          lr

#ifdef CONFIG_MSTAR_MOBF_ENABLE
@//-------------------------------------------------------------------------------------------------
@// BootRom_InitMobf
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
BootRom_InitMobf:

    WREG    (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0xC000  @//enable dramobf

    WREG    (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0xC001
    WREG    (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x0100
    WREG    (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x0302

    WREG    (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0002
    WREG    (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x0504
    WREG    (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x0706

    WREG    (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0003
    WREG    (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x0908
    WREG    (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x0b0a

    WREG    (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0004
    WREG    (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x1100
    WREG    (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x1302

    WREG    (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0005
    WREG    (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x1504
    WREG    (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x1706

    WREG    (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0006
    WREG    (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x1908
    WREG    (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x1b0a

    WREG    (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0007
    WREG    (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x1d0c
    WREG    (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x1f0e

    WREG    (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0008
    WREG    (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x2100
    WREG    (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x2302

    WREG    (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0009
    WREG    (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x2504
    WREG    (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x2706

    WREG    (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x000A
    WREG    (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x2908
    WREG    (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x2b0a

    WREG    (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x000B
    WREG    (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x2d0c
    WREG    (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x2f0e

    WREG    (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x000C
    WREG    (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x3100
    WREG    (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x3302

    WREG    (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x000D
    WREG    (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x3504
    WREG    (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x3706

    WREG    (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x000E
    WREG    (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x3908
    WREG    (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x3b0a

    WREG    (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x000F
    WREG    (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x3d0c
    WREG    (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x3f0e

    WREG    (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0010
    WREG    (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x4100
    WREG    (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x4302

    WREG    (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0011
    WREG    (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x4504
    WREG    (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x4706

    WREG    (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0012
    WREG    (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x4908
    WREG    (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x4b0a

    bx          lr
#endif
