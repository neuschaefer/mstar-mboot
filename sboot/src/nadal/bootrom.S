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

    .text

BOOT_MESSAGE_AC_ON: .short  '\r', '\n', 'A', 'C', '_', 'O', 'N', '\r', '\n', 0x00
BOOT_MESSAGE_DC_ON: .short  '\r', '\n', 'D', 'C', '_', 'O', 'N', '\r', '\n', 0x00

@//-------------------------------------------------------------------------------------------------
@// BootRom_Entry:
@// @param  None
@// @return None
@// @note   Entry point of Boot code
@//-------------------------------------------------------------------------------------------------
    .globl      BootRom_Entry
BootRom_Entry:

    DBGREG      0x0001

#ifndef CONFIG_MSTAR_TITANIA_BD_FPGA

    @//Configure PAD top for MUX and GPIO (e.g. DDR power)
    ldr         r0, =padInitTbl
    add         r0, r0, #10
    bl          MDrv_WriteRegMaskTbl

#ifndef CONFIG_MSTAR_TOOL_ROM_PROGRAM_NAND_BIN

#ifdef CONFIG_MSTAR_VID_ENABLE
    @//Initial Voltage Identification
    bl          BootRom_InitVid
#endif

#if !defined(CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51)
    @//Initial releated settings of PLL
    bl          BootRom_InitPll
#endif

    @//Initial related settings of Clock
    bl          BootRom_InitClock

    DBGREG      0x0002

#if !defined(CONFIG_MSTAR_TITANIA_BD_FPGA) && \
    !defined(CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    bl          BootRom_InitSpiFlashClock
#endif
#endif
#endif

@//================================================================================================
    @//Initial related settings of UART
    bl          BootRom_InitPeripheral

@//================================================================================================

#ifdef CONFIG_MSTAR_DVFS_ENABLE
    @//Enable Dynamic Voltage / Frequency Selection (DVFS)
    bl          BootRom_InitDvfs
#endif

#ifndef CONFIG_MSTAR_TOOL_ROM_PROGRAM_NAND_BIN
#ifndef CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51

    @//Initial related settings of MIU

    RREG        r0, (MS_BUS_RIU_ADDR + (0x0E6E << 1))   @//Disable Divisor Latch Access
    bic         r0, r0, #0x00FF
    ldr         r1, =0xFF00
    cmp         r0, r1
    beq         BootRom_Str_AcFlow

#ifdef CONFIG_MSTAR_STR_ENABLE

#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)
    ldr         r0, =_ld_program_reload_addr
    ldr         r1, =_ld_miu_str_flow_flash_start
    ldr         r2, =0x1400
    bl          drvNAND_LoadBLOffset
#elif defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    ldr         r0, =_ld_program_reload_addr
    ldr         r1, =CONFIG_EMMC_HASH1_STR_SIZE
    ldr         r2, =(CONFIG_EMMC_HASH0_SIZE + CONFIG_EMMC_HASH1_SIZE + CONFIG_EMMC_HASH1_MIU_SIZE)
    mov         r2, r2, lsr #9
    bl          eMMC_LoadImages
#endif

#ifdef CONFIG_MSTAR_AUTHEN_ENABLE
    ldr         r0, =_ld_program_reload_addr                                 @//Set the starting address of HASH for Authentication
    ldr         r1, =0x1000                                                  @//Set the HASH size for Authentication
    ldr         r2, =_ld_program_reload_addr + 0x1300                        @//Set the starting address of SIG for Authentication
    ldr         r3, =0x1
    bl          MDrv_AESDMA_SecureMain

    @//If authentication fail, jump to reset whole system
    cmp         r0, #1
    bne         BootRom_AuthenticationFail
#endif

    bl          BootRom_InitMiu_STR

#else
    DPUTK_STR   BOOT_MESSAGE_DC_ON
    b           BootRom_Str_InitMiu
#endif
    b           BootRom_Str_Exit

BootRom_Str_AcFlow:
    DPUTK_STR   BOOT_MESSAGE_AC_ON

BootRom_Str_InitMiu:
#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)
    ldr         r0, =_ld_program_reload_addr
    ldr         r1, =_ld_miu_flow_flash_start
    ldr         r2, =0x1400
    bl          drvNAND_LoadBLOffset
#elif defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    ldr         r0, =_ld_program_reload_addr
    ldr         r1, =CONFIG_EMMC_HASH1_MIU_SIZE
    ldr         r2, =(CONFIG_EMMC_HASH0_SIZE + CONFIG_EMMC_HASH1_SIZE)
    mov         r2, r2, lsr #9
    bl          eMMC_LoadImages
#endif

#ifdef CONFIG_MSTAR_AUTHEN_ENABLE
    ldr         r0, =_ld_program_reload_addr                                 @//Set the starting address of HASH for Authentication
    ldr         r1, =0x1000                                                  @//Set the HASH size for Authentication
    ldr         r2, =_ld_program_reload_addr + 0x1300                        @//Set the starting address of SIG for Authentication
    ldr         r3, =0x1
    bl          MDrv_AESDMA_SecureMain

    @//If authentication fail, jump to reset whole system
    cmp         r0, #1
    bne         BootRom_AuthenticationFail
#endif

    bl          BootRom_InitMiu

BootRom_Str_Exit:

#endif
#endif

@//================================================================================================
#ifdef CONFIG_MSTAR_MOBF_ENABLE
    @//Enable MOBF Function for Secure Usage
    bl          BootRom_InitMobf
#endif

@//================================================================================================
    @//Initial related settings of cache
    bl          BootRom_InitCache

@//================================================================================================
#if defined(CONFIG_EMMC_BOOT)

    @// Copy chunk header from EMMC boot partition to DRAM
    bl          BOOT_CopyHeader_EMMC

    @//Copy uboot binary from EMMC boot partition to DRAM
    bl          BOOT_CopyUboot_EMMC

    mov         pc, r4
#else

#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)
    ldr         r0, =CONFIG_BOOTRAM_LOADADDR
    ldr         r1, =0x8000
    bl          drvNAND_Load2ndBL

#elif defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    ldr         r0, =CONFIG_BOOTRAM_LOADADDR
    ldr         r1, =_ld_bootram_size
    ldr         r2, =CONFIG_EMMC_BOOTRAM_ADDRESS
    mov         r2, r2, lsr #9
    bl          eMMC_LoadImages

#elif defined(CONFIG_BOOTING_FROM_EXT_EMMC_WITH_CPU)

    @// Copy bootram to DRAM
    bl          BOOT_CopyBootRam

#else

    @//Copy image of bootram to DRAM
    bl          BootRom_LoadBootRam

#endif

#ifdef CONFIG_MSTAR_AUTHEN_ENABLE
    ldr         r0, =CONFIG_BOOTRAM_LOADADDR                                 @//Set the starting address of HASH for Authentication
    ldr         r1, =0x2000                                                  @//Set the HASH size for Authentication
    ldr         r2, =CONFIG_BOOTRAM_LOADADDR + 0x2300                        @//Set the starting address of SIG for Authentication
    ldr         r3, =0x0
    bl          MDrv_AESDMA_SecureMain

    @//If authentication fail, jump to reset whole system
    cmp         r0, #1
    bne         BootRom_AuthenticationFail
#endif

@//================================================================================================
#ifdef CONFIG_MSTAR_STR_ENABLE
    bl          BootRom_StrEntry
#endif

@//================================================================================================
    DBGREG      0x0003
    @//Jump to the entry of BOOTRAM
    ldr         pc, =BOOTRAM_Entry

BootRom_DummyLoop:
    b           BootRom_DummyLoop

#endif

#if 0
@//-------------------------------------------------------------------------------------------------
@// BootRom_InitFpu
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
BootRom_InitFpu:

    mov         r0, #0x40000000
    vmsr        fpexc, r0

    bx          lr
#endif

@//================================================================================================
#if !defined(CONFIG_EMMC_BOOT) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH) && \
    !defined(CONFIG_BOOTING_FROM_EXT_EMMC_WITH_CPU)
@//-------------------------------------------------------------------------------------------------
@// BootRom_LoadBootRam
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
BootRom_LoadBootRam:

    ldr         r10, =_ld_bootrom_end
    ldr         r11, =_ld_bootram_start
    ldr         r12, =_ld_bootram_end
    ldr         r9, =_ld_bootram_start
    sub         r12, r12, r9

_CopyDataLoop:
    ldr         r9, [r10], #4
    str         r9, [r11], #4
    subs        r12, r12, #4
    bne         _CopyDataLoop

    bx          lr
#endif

@//================================================================================================
#ifdef CONFIG_EMMC_BOOT
@//-------------------------------------------------------------------------------------------------
@// BOOT_CopyHeader_EMMC
@// @param  None
@// @return None
@// @note   Copy Chunk Header from EMMC to DRAM
@//-------------------------------------------------------------------------------------------------
EMMC_HEADER_SIZE        = 0x0002                @//Size = 1KB
EMMC_HEADER_ADDR_BYTE   = (0x20200000 >> 3)

RAM_START   = 0x20200004
RAM_END     = 0x20200008
RAM_ENTRY   = 0x20200010

BOOT_CopyHeader_EMMC:

    @//Set the FCIE reg_dma_addr_26_16
    LDR         r12, =EMMC_HEADER_ADDR_BYTE
    MOV         r11, r12, LSR #16
    LDR         r12, =REG_MIU_ADDR_H
    STR         r11, [r12]

    @//Set the FCIE reg_dma_addr_15_0
    LDR         r1, =0xFFFF
    LDR         r12, =EMMC_HEADER_ADDR_BYTE
    AND         r11, r12, r1
    LDR         r12, =REG_MIU_ADDR_L
    STR         r11, [r12]

    @//Set the FCIE reg_job_bl_cnt
    LDR         r12, =REG_JOB_BL_CNT
    LDR         r11, =EMMC_HEADER_SIZE
    STR         r11, [r12]

    STG2_BLK_R
    MEMORY_FLUSH

    LDR         r12, =RAM_START         @// RAM_START
    LDR         r9, [r12]

    LDR         r11, =RAM_END           @// RAM_END
    LDR         r8, [r11]

    SUB         r10, r8, r9             @// RAM_SIZE = RAM_END-RAM_START

    MOV         r10, r10, LSR #9        @// SIZE = (RAM_SIZE /512)+1
    ADD         r10, r10, #1

    MOV         r8, r9, LSR #3          @// RAM_START/miu_length convert to miu address

    LDR         r12, = RAM_ENTRY        @// RAM_ENTRY
    LDR         r4, [r12]

    MOV         PC, LR                  @// return

@//-------------------------------------------------------------------------------------------------
@// BOOT_CopyUboot_EMMC
@// @param  None
@// $11 : FCIE DMA ADDRESS
@// $10 : JOB_BL_CNT
@// @return None
@// @note   Copy Uboot binary from EMMC to DRAM
@//-------------------------------------------------------------------------------------------------
EMMC_MAX_BLK_CNT = 4095
BOOT_CopyUboot_EMMC:

    @// Set the FCIE reg_dma_addr_26_16
    MOV         r11, r8, LSR #16
    LDR         r12, =REG_MIU_ADDR_H
    STR         r11, [r12]

    @// Set the FCIE reg_dma_addr_15_0
    LDR         r1, =0xFFFF
    AND         r11, r8, r1
    LDR         r12, =REG_MIU_ADDR_L
    STR         r11, [r12]

    @// If block count > 4095, goto GRT_MAX_CNT
    LDR         r9, =EMMC_MAX_BLK_CNT
    CMP         r10, r9
    BGT         GRT_MAX_CNT

    @// If block count <= 4095, set the block count
    LDR         r12, =REG_JOB_BL_CNT
    STR         r10, [r12]
    MOVS        r10, #0

    @// Goto SEND_STG2_BLK
    LDR         PC, =SEND_STG2_BLK

GRT_MAX_CNT:
    LDR         r12, =REG_JOB_BL_CNT
    STR         r9, [r12]
    SUB         r10, r10, r9

SEND_STG2_BLK:

    STG2_BLK_R
    MEMORY_FLUSH

    @// If r10 == 0, goto SEND_BLK_END (All block are transferred.)
    MOVS        r0, #0
    CMP         r10, r0
    BEQ         SEND_BLK_END

    LDR         r12, =REG_JOB_BL_CNT
    LDR         r11, [r12]
    MOV         r9, r11, LSL #9
    ADD         r8, r8, r9

    LDR         PC, =BOOT_CopyUboot_EMMC

SEND_BLK_END:
    WREG        REG_BOOT_CONFIG, 0x0002 @//Set EMMC boot operation end

    MOV         PC, LR

#endif

@//================================================================================================
#if defined(CONFIG_BOOTING_FROM_EXT_EMMC_WITH_CPU)
@//-------------------------------------------------------------------------------------------------
@// BOOT_CopyBootRam
@// @param  None
@// @return None
@// @note   Copy Chunk Header from EMMC to DRAM
@//-------------------------------------------------------------------------------------------------
EMMC_BOOTRAM_SIZE           = 0x0040            @//Size = 32KB
EMMC_BOOTRAM_BYTE           = (0x20200000 >> 3)
@//REG_BOOTRAM_JOB_BL_CNT   = (FCIE0_BASE + (0x0B + 0x08) * 4)
REG_BOOTRAM_JOB_BL_CNT      = (FCIE0_BASE + (0x0B) * 4)

BOOT_CopyBootRam:

    @//Set the FCIE reg_dma_addr_26_16
    LDR         r12, =EMMC_BOOTRAM_BYTE
    MOV         r11, r12, LSR #16
    LDR         r12, =REG_MIU_ADDR_H
    STR         r11, [r12]

    @//Set the FCIE reg_dma_addr_15_0
    LDR         r1, =0xFFFF
    LDR         r12, =EMMC_BOOTRAM_BYTE
    AND         r11, r12, r1
    LDR         r12, =REG_MIU_ADDR_L
    STR         r11, [r12]

    @//Set the FCIE reg_job_bl_cnt
    LDR         r12, =REG_BOOTRAM_JOB_BL_CNT
    LDR         r11, =EMMC_BOOTRAM_SIZE
    STR         r11, [r12]

    STG2_BLK_R
    MEMORY_FLUSH

#if 0 //cyber
    LDR         r12, =RAM_START         @// RAM_START
    LDR         r9, [r12]

    LDR         r11, =RAM_END           @// RAM_END
    LDR         r8, [r11]

    SUB         r10, r8, r9             @// RAM_SIZE = RAM_END-RAM_START

    MOV         r10, r10, LSR #9        @// SIZE = (RAM_SIZE /512)+1
    ADD         r10, r10, #1

    MOV         r8, r9, LSR #3          @// RAM_START/miu_length convert to miu address

    LDR         r12, = RAM_ENTRY        @// RAM_ENTRY
    LDR         r4, [r12]
#endif
    MOV         PC, LR                  @// return
#endif

@//-------------------------------------------------------------------------------------------------
@// BootRom_WriteUartCharactor
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .globl      BootRom_WriteUartCharactor
BootRom_WriteUartCharactor:
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x100900 << 1))
    str         r0, [r12, #(0x80 << 1)]     @//REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x100980 << 1))
BootRom_WriteUartCharactor_Loop:
    ldr         r0, [r12, #(0x94 << 1)]     @//RREG        r0, (MS_BUS_RIU_ADDR + (0x100994 << 1))
    and         r0, r0, #0x0060
    cmp         r0, #0x0060
    bne         BootRom_WriteUartCharactor_Loop

    bx          lr

@//-------------------------------------------------------------------------------------------------
@// BootRom_WriteUartString
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .globl      BootRom_WriteUartString
BootRom_WriteUartString:

    ldrb        r11, [r0], #2
    and         r11, r11, #0xff
    cmp         r11, #0x00
    beq         BootRom_WriteUartString_Exit

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x100900 << 1))
    str         r11, [r12, #(0x80 << 1)]     @//REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x100980 << 1))
BootRom_WriteUartString_Loop:
    ldr         r11, [r12, #(0x94 << 1)]     @//RREG        r0, (MS_BUS_RIU_ADDR + (0x100994 << 1))
    and         r11, r11, #0x60
    cmp         r11, #0x60
    bne         BootRom_WriteUartString_Loop
    b           BootRom_WriteUartString

BootRom_WriteUartString_Exit:

    bx          lr

@//-------------------------------------------------------------------------------------------------
@// BootRom_StrEntry
@// @param  None
@// @return None
@// @note   None
@//-------------------------------------------------------------------------------------------------
#ifdef CONFIG_MSTAR_STR_ENABLE
    .global     BootRom_StrEntry
BootRom_StrEntry:

    mov         r13, lr

.if (MSTAR_STR_SBOOT_RESUME == 1)
    bl          read_wkup_pmu
    bl          put_reg_val

    is_slept
    bne         1f

    set_wakeup
    b           2f

1:
    eor         r0, r0, r0
    bl          write_wkup_pmu

2:
    is_wakeup
    bne         3f
    PUTK        'W'
    PUTK        'K'
    PUTK        'P'
    bl          read_wkup_pmu

    bic         r0, r0, #WAKEUP_FLAG_MASK
    mov         r0, r0, lsl #16             @// wake up info addr
    ldmia       r0, {r1-r2}
    ldr         r0, =MSTAR_SLEEP_MAGIC
    cmp         r1, r0
    bne         3f

    PUTK        'J'
    cmp         r2, #0
    beq         3f

    PUTK        'M'
    mov         pc, r2                      @// jump to wakup addr
3:
.endif

    mov         lr, r13
    bx          lr

#endif

@//================================================================================================
#ifdef CONFIG_MSTAR_STR_ENABLE
#if 0   //calculate CRC for STR debug
MEM_REGION1_ST      = 0x00200000
MEM_REGION1_SZ      = 0x09F00000
@//MEM_REGION2_ST   = 0x10E00000    @//MIU0
@//MEM_REGION2_SZ   = 0x0C200000    @//MIU0

MEM_REGION2_ST      = 0x01800000    @//MIU1
MEM_REGION2_SZ      = 0x0E800000    @//MIU1

@//Input: r0-region address   r1-resion size
@//Output: r0-CRC value
BDMABank = 0x1F201200
BDMACRC_Calc_MIU:
    ldr         r2, =BDMABank

    mov         r3, #0
    str         r3, [r2, #(0x0c<<2)]
    str         r3, [r2, #(0x0d<<2)]
@// mov         r3, #0x0340
@// str         r3, [r2, #(0x02<<2)]

    str         r0, [r2, #(0x04<<2)]
    str         r0, [r2, #(0x06<<2)]
    lsr         r0, r0, #16
    str         r0, [r2, #(0x05<<2)]
    str         r0, [r2, #(0x07<<2)]

    str         r1, [r2, #(0x08<<2)]
    lsr         r1, r1, #16
    str         r1, [r2, #(0x09<<2)]

    ldr         r3, =0x1DB7
    str         r3, [r2, #(0x0a<<2)]
    ldr         r3, =0x04c1
    str         r3, [r2, #(0x0b<<2)]

    ldr         r3, [r2]
    orr         r3, r3, #1
    str         r3, [r2]

BDMACRC_Calc_agn:
    ldr         r3, [r2, #(0x01<<2)]
    tst         r3, #0x08
    beq         BDMACRC_Calc_agn

    ldr         r3, [r2, #(0x0c<<2)]
    ldr         r0, [r2, #(0x0d<<2)]
    orr         r0, r3, r0, LSL #16

    mov         pc, lr

 SBootMemCRCCheck:
    mov         r8, lr
    PUTK        'S'
    PUTK        'B'
    PUTK        'O'
    PUTK        'O'
    PUTK        'T'
    PUTK        ' '
    PUTK        'C'
    PUTK        'R'
    PUTK        'C'
    PUTK        ':'

    PUTK        '\n'
    PUTK        '\r'

    PUTK        '1'
    PUTK        '.'
    ldr         r0, =MEM_REGION1_ST
    ldr         r1, =MEM_REGION1_SZ
    WREG        (MS_BUS_RIU_ADDR + (0x100904 << 1)), 0x0340
    bl          BDMACRC_Calc_MIU
    bl          put_reg_val
    PUTK        '\n'
    PUTK        '\r'

    PUTK        '2'
    PUTK        '.'
    ldr         r0, =MEM_REGION2_ST
    ldr         r1, =MEM_REGION2_SZ
    WREG        (MS_BUS_RIU_ADDR + (0x100904 << 1)), 0x0341
    bl          BDMACRC_Calc_MIU
    bl          put_reg_val
    PUTK        '\n'
    PUTK        '\r'
    mov         pc, r8
    .ltorg
#endif

.if (MSTAR_STR_SBOOT_RESUME == 1)
read_wkup_pmu:
    ldr         r2, =PMU_WAKEUP_ADDR_REGL
    ldr         r0, [r2]

    ldr         r2, =PMU_WAKEUP_ADDR_REGH
    ldr         r1, [r2]

    and         r0, r0, #PMU_WAKEUP_ADDR_LMASK
    and         r1, r1, #PMU_WAKEUP_ADDR_HMASK
    orr         r0, r0, r1
    mov         pc, lr
    .ltorg

write_wkup_pmu:
    ldr         r3, =PMU_WAKEUP_ADDR_REGL
    ldr         r1, [r3]
    bic         r1, #PMU_WAKEUP_ADDR_LMASK
    and         r2, r0, #PMU_WAKEUP_ADDR_LMASK
    orr         r1, r1, r2
    str         r1, [r3]

    ldr         r3, =PMU_WAKEUP_ADDR_REGH
    ldr         r1, [r3]
    bic         r1, #PMU_WAKEUP_ADDR_HMASK
    and         r2, r0, #PMU_WAKEUP_ADDR_HMASK
    orr         r1, r1, r2
    str         r1, [r3]
    mov         pc, lr
    .ltorg
.endif

text_tbl: .short '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'

@// r9-r12 destroyed
put_reg_val:
    mov         r9, #32
    mov         r11, #0x0F
40:
    sub         r9, #4
    and         r10, r11, r0, LSR r9
    ldr         r12, =text_tbl
    add         r12, r12, r10, lsl #1
    ldr         r10,  [r12]
    mov         r12, #0x1F000000
    orr         r12, r12, #0x00200000
    orr         r12, r12, #0x1300
    strb        r10,[r12]
    cmp         r9, #0
    bgt         40b

@// mov         r10, #'\r'      /* new line */
@// strb        r10,[r12]
@// mov         r10, #'\n'
@// strb        r10,[r12]
    mov         r10, #'-'
    strb        r10,[r12]

    mov         pc, lr
    .ltorg
#endif

#ifdef CONFIG_MSTAR_AUTHEN_ENABLE
BootRom_AuthenticationFail:
    b           BootRom_AuthenticationFail
#endif
