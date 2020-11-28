/*
 *#############################################################################
 *
 * Copyright (c) 2006-2014 MStar Semiconductor, Inc.
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
BOOT_MESSAGE_AC_ON:     .short  '\r', '\n', 'A', 'C', '_', 'O', 'N', '\r', '\n', 0x00
BOOT_MESSAGE_DC_ON:     .short  '\r', '\n', 'D', 'C', '_', 'O', 'N', '\r', '\n', 0x00
BOOT_MESSAGE_SELF_TEST: .short  '\r', '\n', 'S', 'E', 'L', 'F', '_', 'T', 'E', 'S', 'T', '\r', '\n', 0x00
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
    ldr         r0, =padInitTbl_PreInit
    add         r0, r0, #10
    bl          MDrv_WriteRegMaskTbl

#ifndef CONFIG_MSTAR_TOOL_ROM_PROGRAM_NAND_BIN
#ifdef CONFIG_MSTAR_VID_ENABLE
    @//Initial Voltage Identification
    bl          BootRom_InitVid
#endif  /*CONFIG_MSTAR_VID_ENABLE*/

#if !defined(CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51)
    @//Initial releated settings of PLL
    bl          BootRom_InitPll
#endif  /*!defined(CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51*/

    @//Initial related settings of Clock
    bl          BootRom_InitClock

    DBGREG      0x0002
#endif  /*CONFIG_MSTAR_TOOL_ROM_PROGRAM_NAND_BIN*/
#endif  /*CONFIG_MSTAR_TITANIA_BD_FPGA*/

@//================================================================================================
    @//Initial related settings of UART
    bl          BootRom_InitPeripheral

@//================================================================================================
#ifdef CONFIG_MSTAR_DVFS_ENABLE
    @//Enable Dynamic Voltage / Frequency Selection (DVFS)
    bl          BootRom_InitDvfs
#endif

#if !defined(CONFIG_MSTAR_TOOL_ROM_PROGRAM_NAND_BIN) && \
    !defined(CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51)

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
    ldr         r0, =_ld_program_reload_addr            @//Set the starting address of HASH for Authentication
    ldr         r1, =0x1000                             @//Set the HASH size for Authentication
    ldr         r2, =(_ld_program_reload_addr + 0x1300) @//Set the starting address of SIG for Authentication
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
#endif /* CONFIG_MSTAR_STR_ENABLE */

#ifdef CONFIG_MSTAR_SELF_STR_TEST_ENABLE
    DPUTK_STR   BOOT_MESSAGE_SELF_TEST
    bl          Miu0_BistTest_Str
    bl          Miu1_BistTest_Str
    
Self_Str_Test_Level:
    b           Self_Str_Test_Level
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
    ldr         r0, =_ld_program_reload_addr            @//Set the starting address of HASH for Authentication
    ldr         r1, =0x1000                             @//Set the HASH size for Authentication
    ldr         r2, =_ld_program_reload_addr + 0x1300   @//Set the starting address of SIG for Authentication
    ldr         r3, =0x1
    bl          MDrv_AESDMA_SecureMain

    @//If authentication fail, jump to reset whole system
    cmp         r0, #1
    bne         BootRom_AuthenticationFail
#endif

    bl          BootRom_InitMiu

BootRom_Str_Exit:

#endif

@//================================================================================================
#ifdef CONFIG_MSTAR_MOBF_ENABLE
    @//Enable MOBF Function for Secure Usage
    bl          BootRom_InitMobf
#endif

@//================================================================================================
#if 0
    @//Update SRAM Settings for Corner Chip
    RREG        r0, (MS_BUS_RIU_ADDR + (0x101eae << 1))
    bic         r0, r0, #0x0f00
    orr         r0, r0, #0x0900
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x101eae << 1))
#endif

    @//Initial related settings of cache
    bl          BootRom_InitCache

@//================================================================================================
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

#else

    @//Copy image of bootram to DRAM
    bl          BootRom_LoadBootRam

#endif

#ifdef CONFIG_MSTAR_AUTHEN_ENABLE
    ldr         r0, =CONFIG_BOOTRAM_LOADADDR            @//Set the starting address of HASH for Authentication
    ldr         r1, =0x2000                             @//Set the HASH size for Authentication
    ldr         r2, =CONFIG_BOOTRAM_LOADADDR + 0x2300   @//Set the starting address of SIG for Authentication
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
#if !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
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
