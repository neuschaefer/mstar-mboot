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

#ifndef _BOOT_INC_
#include "boot.inc"
#endif

    .text
BOOT_MESSAGE_AC_ON:     .short  '\r', '\n', 'A', 'C', '_', 'O', 'N', '\r', '\n', 0x00
BOOT_MESSAGE_DC_ON:     .short  '\r', '\n', 'D', 'C', '_', 'O', 'N', '\r', '\n', 0x00
BOOT_MESSAGE_SELF_TEST: .short  '\r', '\n', 'S', 'E', 'L', 'F', '_', 'T', 'E', 'S', 'T', '\r', '\n', 0x00

    .align      4

//-------------------------------------------------------------------------------------------------
// BootRom_Entry:
// @param  None
// @return None
// @note   Entry point of Boot code
//-------------------------------------------------------------------------------------------------
    .globl      BootRom_Entry
BootRom_Entry:

    DBGREG      0x0001

#ifndef CONFIG_MSTAR_TITANIA_BD_FPGA

    //Configure PAD top for MUX and GPIO (e.g. DDR power)
    ldr         x0, =padInitTbl_PreInit
    add         x0, x0, #10
    bl          MDrv_WriteRegMaskTbl

#ifndef CONFIG_MSTAR_TOOL_ROM_PROGRAM_NAND_BIN
#ifdef CONFIG_MSTAR_VID_ENABLE
    //Initial Voltage Identification
    bl          BootRom_InitVid
#endif  /*CONFIG_MSTAR_VID_ENABLE*/

#if !defined(CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51)
    //Initial releated settings of PLL
    bl          BootRom_InitPll
#endif  /*!defined(CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51*/

    //Initial related settings of Clock
    bl          BootRom_InitClock

    DBGREG      0x0002
#endif  /*CONFIG_MSTAR_TOOL_ROM_PROGRAM_NAND_BIN*/
#endif  /*CONFIG_MSTAR_TITANIA_BD_FPGA*/

//================================================================================================
    //Initial related settings of UART
    bl          BootRom_InitPeripheral

//================================================================================================
#ifdef CONFIG_MSTAR_DVFS_ENABLE
    //Enable Dynamic Voltage / Frequency Selection (DVFS)
    bl          BootRom_InitDvfs
#endif

#if !defined(CONFIG_MSTAR_TOOL_ROM_PROGRAM_NAND_BIN) && \
    !defined(CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51)

    //Initial related settings of MIU

    RREG        w0, (MS_BUS_RIU_ADDR + (0x0E70 << 1))   //Disable Divisor Latch Access
    bic         w0, w0, #0xFF00
    ldr         w1, =0x00FF
    cmp         w0, w1
    b.eq         BootRom_Str_AcFlow

#ifdef CONFIG_MSTAR_STR_ENABLE
#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)
    ldr         x0, =_ld_program_reload_addr
    ldr         x1, =_ld_miu_str_flow_flash_start
    ldr         x2, =0x1C00
    bl          drvNAND_LoadBLOffset
#elif defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    ldr         x0, =_ld_program_reload_addr
    ldr         x1, =CONFIG_EMMC_HASH1_STR_SIZE
    ldr         x2, =(CONFIG_EMMC_HASH0_SIZE + CONFIG_EMMC_HASH1_SIZE + CONFIG_EMMC_HASH1_MIU_SIZE)
    lsr         x2, x2, #9
    bl          eMMC_LoadImages
#endif

#ifdef CONFIG_MSTAR_AUTHEN_ENABLE
    ldr         x0, =_ld_program_reload_addr            //Set the starting address of HASH for Authentication
    ldr         x1, =0x1800                             //Set the HASH size for Authentication
    ldr         x2, =(_ld_program_reload_addr + 0x1B00) //Set the starting address of SIG for Authentication
    ldr         x3, =0x1
    bl          MDrv_AESDMA_SecureMain

    //If authentication fail, jump to reset whole system
    cmp         x0, #1
    b.ne        BootRom_AuthenticationFail
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
    ldr         w0, =_ld_program_reload_addr
    ldr         w1, =_ld_miu_flow_flash_start
    ldr         w2, =0x1C00
    bl          drvNAND_LoadBLOffset
#elif defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    ldr         w0, =_ld_program_reload_addr
    ldr         w1, =CONFIG_EMMC_HASH1_MIU_SIZE
    ldr         w2, =(CONFIG_EMMC_HASH0_SIZE + CONFIG_EMMC_HASH1_SIZE)
    lsr         w2, w2, #9
    bl          eMMC_LoadImages
#endif

#ifdef CONFIG_MSTAR_AUTHEN_ENABLE
    ldr         w0, =_ld_program_reload_addr            //Set the starting address of HASH for Authentication
    ldr         w1, =0x1800                             //Set the HASH size for Authentication
    ldr         w2, =_ld_program_reload_addr + 0x1B00   //Set the starting address of SIG for Authentication
    ldr         w3, =0x1
    bl          MDrv_AESDMA_SecureMain

    //If authentication fail, jump to reset whole system
    cmp         w0, #1
    b.ne         BootRom_AuthenticationFail
#endif

    bl          BootRom_InitMiu

BootRom_Str_Exit:

#endif

//================================================================================================
#ifdef CONFIG_MSTAR_MOBF_ENABLE
    //Enable MOBF Function for Secure Usage
    bl          BootRom_InitMobf
#endif

//================================================================================================
    //Set MIU1x Mode
    bl          BootRom_SetL3Clock

    //Initial related settings of cache
    bl          BootRom_InitCache

//================================================================================================
#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)
    ldr         w0, =CONFIG_BOOTRAM_LOADADDR
    ldr         w1, =0x8000
    bl          drvNAND_Load2ndBL

#elif defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    ldr         w0, =CONFIG_BOOTRAM_LOADADDR
    ldr         w1, =_ld_bootram_size
    ldr         w2, =CONFIG_EMMC_BOOTRAM_ADDRESS
    lsr         w2, w2, #9
    bl          eMMC_LoadImages

#else

    //Copy image of bootram to DRAM
    bl          BootRom_LoadBootRam

#endif

#ifdef CONFIG_MSTAR_AUTHEN_ENABLE
    ldr         w0, =CONFIG_BOOTRAM_LOADADDR            //Set the starting address of HASH for Authentication
    ldr         w1, =0x2000                             //Set the HASH size for Authentication
    ldr         w2, =CONFIG_BOOTRAM_LOADADDR + 0x2300   //Set the starting address of SIG for Authentication
    ldr         w3, =0x0
    bl          MDrv_AESDMA_SecureMain

    //If authentication fail, jump to reset whole system
    cmp         x0, #1
    b.ne         BootRom_AuthenticationFail
#endif

//================================================================================================
#ifdef CONFIG_MSTAR_STR_ENABLE
    bl          BootRom_StrEntry
#endif

//================================================================================================
    DBGREG      0x0003
    //Jump to the entry of BOOTRAM
    ldr         x30, =BOOTRAM_Entry
    ret

BootRom_DummyLoop:
    b           BootRom_DummyLoop

//================================================================================================
#if !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
//-------------------------------------------------------------------------------------------------
// BootRom_LoadBootRam
// @param
// @return None
// @note
//-------------------------------------------------------------------------------------------------
BootRom_LoadBootRam:

    ldr         x10, =_ld_bootrom_end
    ldr         x11, =_ld_bootram_start
    ldr         w12, =_ld_bootram_end
    ldr         w9, =_ld_bootram_start
    sub         w12, w12, w9

_CopyDataLoop:
    ldr         w9, [x10], #4
    str         w9, [x11], #4
    subs        w12, w12, #4
    b.ne        _CopyDataLoop

    ret
#endif

//-------------------------------------------------------------------------------------------------
// BootRom_WriteUartCharactor
// @param
// @return None
// @note
//-------------------------------------------------------------------------------------------------
    .globl      BootRom_WriteUartCharactor
BootRom_WriteUartCharactor:
    ldr         x12, =(MS_BUS_RIU_ADDR + (0x100900 << 1))
    str         w0, [x12, #(0x80 << 1)]     //REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x100980 << 1))
BootRom_WriteUartCharactor_Loop:
    ldr         w0, [x12, #(0x94 << 1)]     //RREG        r0, (MS_BUS_RIU_ADDR + (0x100994 << 1))
    and         w0, w0, #0x0060
    cmp         w0, #0x0060
    b.ne        BootRom_WriteUartCharactor_Loop

    ret
//-------------------------------------------------------------------------------------------------
// BootRom_WriteUartString
// @param
// @return None
// @note
//-------------------------------------------------------------------------------------------------
    .globl      BootRom_WriteUartString
BootRom_WriteUartString:

    ldrb        w11, [x0], #2
    and         w11, w11, #0xff
    cmp         x11, #0x00
    b.eq        BootRom_WriteUartString_Exit

    ldr         x12, =(MS_BUS_RIU_ADDR + (0x100900 << 1))
    str         w11, [x12, #(0x80 << 1)]     //REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x100980 << 1))
BootRom_WriteUartString_Loop:
    ldr         w11, [x12, #(0x94 << 1)]     //RREG        r0, (MS_BUS_RIU_ADDR + (0x100994 << 1))
    and         w11, w11, #0x60
    cmp         w11, #0x60
    b.ne        BootRom_WriteUartString_Loop
    b           BootRom_WriteUartString

BootRom_WriteUartString_Exit:

    ret

//-------------------------------------------------------------------------------------------------
// BootRom_SetL3Clock
// @param
// @return None
// @note
//-------------------------------------------------------------------------------------------------
BootRom_SetL3Clock:

    //Set MIU1x Mode
    RREG        w0, (MS_BUS_RIU_ADDR + (0x101e20 << 1))
    bic         w0, w0, #0x30
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x101e20 << 1))

    ldr         x1, =(MS_BUS_RIU_ADDR + (0x101800 << 1))
    ldr         w0, [x1, #(0x82 << 1)]
    orr         w0, w0, #0x0080
    str         w0, [x1, #(0x82 << 1)]

    ret

//-------------------------------------------------------------------------------------------------
// BootRom_StrEntry
// @param  None
// @return None
// @note   None
//-------------------------------------------------------------------------------------------------
#ifdef CONFIG_MSTAR_STR_ENABLE
    .global     BootRom_StrEntry
BootRom_StrEntry:

    mov         x29, x30

.if (MSTAR_STR_SBOOT_RESUME == 1)
    bl          read_wkup_pmu
    bl          put_reg_val

    is_slept
    b.ne         1f

    set_wakeup
    b           2f

1:
    eor         w0, w0, w0
    bl          write_wkup_pmu

2:
    is_wakeup
    b.ne        3f
    PUTK        'W'
    PUTK        'K'
    PUTK        'P'
    bl          read_wkup_pmu

    bic         x0, x0, #WAKEUP_FLAG_MASK
    lsl         x0, x0, #16
    ldr         w1, [x0], #4
    ldr         w2, [x0], #4
    ldr         w0, =MSTAR_SLEEP_MAGIC
    cmp         w1, w0
    b.ne        3f

    PUTK        'J'
    cmp         w2, #0
    b.eq        3f

    PUTK        'M'
    br          x2                      // jump to wakup addr
3:
.endif

    mov         x30, x29
    ret

#endif

//================================================================================================
#ifdef CONFIG_MSTAR_STR_ENABLE
#if 0   //calculate CRC for STR debug
MEM_REGION1_ST      = 0x00200000
MEM_REGION1_SZ      = 0x09F00000
//MEM_REGION2_ST    = 0x10E00000    //MIU0
//MEM_REGION2_SZ    = 0x0C200000    //MIU0

MEM_REGION2_ST      = 0x01800000    //MIU1
MEM_REGION2_SZ      = 0x0E800000    //MIU1

//Input: x0-region address   x1-resion size
//Output: x0-CRC value
BDMABank = 0x1F201200
BDMACRC_Calc_MIU:
    ldr         x2, =BDMABank

    mov         w3, #0
    strh        w3, [x2, #(0x0c<<2)]
    strh        w3, [x2, #(0x0d<<2)]
//  mov         w3, #0x0340
//  str         w3, [x2, #(0x02<<2)]

    strh        w0, [x2, #(0x04<<2)]
    strh        w0, [x2, #(0x06<<2)]
    lsr         w0, w0, #16
    strh        w0, [x2, #(0x05<<2)]
    strh        w0, [x2, #(0x07<<2)]

    strh        w1, [x2, #(0x08<<2)]
    lsr         w1, w1, #16
    strh        w1, [x2, #(0x09<<2)]

    ldr         w3, =0x1DB7
    strh        w3, [x2, #(0x0a<<2)]
    ldr         w3, =0x04c1
    strh        w3, [x2, #(0x0b<<2)]

    ldr         w3, [x2]
    orr         w3, w3, #1
    strh        w3, [x2]

BDMACRC_Calc_agn:
    ldr         w3, [x2, #(0x01<<2)]
    tst         w3, #0x08
    b.eq        BDMACRC_Calc_agn

    ldrh        w3, [x2, #(0x0c<<2)]
    ldrh        w0, [x2, #(0x0d<<2)]
    orr         w0, w3, w0, lsl #16

    ret

 SBootMemCRCCheck:
    mov         x29, x30
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
    ldr         x0, =MEM_REGION1_ST
    ldr         x1, =MEM_REGION1_SZ
    WREG        (MS_BUS_RIU_ADDR + (0x100904 << 1)), 0x0340
    bl          BDMACRC_Calc_MIU
    bl          put_reg_val
    PUTK        '\n'
    PUTK        '\r'

    PUTK        '2'
    PUTK        '.'
    ldr         x0, =MEM_REGION2_ST
    ldr         x1, =MEM_REGION2_SZ
    WREG        (MS_BUS_RIU_ADDR + (0x100904 << 1)), 0x0341
    bl          BDMACRC_Calc_MIU
    bl          put_reg_val
    PUTK        '\n'
    PUTK        '\r'
    mov         x30, x29
    .ltorg

    ret
#endif

.if (MSTAR_STR_SBOOT_RESUME == 1)
read_wkup_pmu:
    ldr         x2, =PMU_WAKEUP_ADDR_REGL
    ldr         w0, [x2]

    ldr         x2, =PMU_WAKEUP_ADDR_REGH
    ldr         w1, [x2]

    and         w0, w0, #PMU_WAKEUP_ADDR_LMASK
    and         w1, w1, #PMU_WAKEUP_ADDR_HMASK
    orr         w0, w0, w1
    ret
    .ltorg

write_wkup_pmu:
    ldr         x3, =PMU_WAKEUP_ADDR_REGL
    ldr         w1, [x3]
    bic         w1, #PMU_WAKEUP_ADDR_LMASK
    and         w2, w0, #PMU_WAKEUP_ADDR_LMASK
    orr         w1, w1, w2
    str         w1, [x3]

    ldr         x3, =PMU_WAKEUP_ADDR_REGH
    ldr         w1, [x3]
    bic         w1, #PMU_WAKEUP_ADDR_HMASK
    and         w2, w0, #PMU_WAKEUP_ADDR_HMASK
    orr         w1, w1, w2
    str         w1, [x3]
    ret

.endif

text_tbl: .short '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'

// w9-w12 destroyed
put_reg_val:
    mov         w9, #32
    mov         w11, #0x0F
40:
    sub         w9, #4
    and         w10, w11, w0, LSR w9
    ldr         x12, =text_tbl
    add         x12, x12, w10, lsl #1
    ldr         w10, [x12]
    mov         x12, #0x1F000000
    orr         x12, x12, #0x00200000
    orr         x12, x12, #0x1300
    strb        w10, [x12]
    cmp         w9, #0
    b.gt        40b

// mov          w10, #'\r'      /* new line */
// strb         w10, [x12]
// mov          w10, #'\n'
// strb         w10, [x12]
    mov         w10, #'-'
    strb        w10, [x12]

    ret

#endif

#ifdef CONFIG_MSTAR_AUTHEN_ENABLE
BootRom_AuthenticationFail:
    b           BootRom_AuthenticationFail
#endif
