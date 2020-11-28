/*
 *#############################################################################
 *
 * Copyright (c) 2006-2013 MStar Semiconductor, Inc.
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

    .text

    .global     BootRom_InitPeripheral
BootRom_InitPeripheral:

    mov         r13, lr

@//================================================================================================
    @//Initial related settings of UART
    bl          BootRom_InitUart

@//================================================================================================
    @//Enable 8051 to access MIU for MStar TV Tool
    bl          BootRom_EnableMcuAccess

@//================================================================================================
    @//Initial related settings of RIU
    bl          BootRom_InitRiu

    @//Initial MOD Trimming Control Setting
    bl          BootRom_InitModTrimmingControl

    @//Initial MHL CBus Trimming Control Setting
    bl          BootRom_InitMhlCbusTrimmingControl

    @//Initial EMAC Trimming Control Setting
    bl          BootRom_InitEmacTrimmingControl

#ifdef CONFIG_MSTAR_EDINBURGH
    bl          BootRom_InitExtDemod_Edinburgh
#endif

//#ifdef CONFIG_MSTAR_CASHMERE
//    bl          BootRom_InitExtDemod_Cashmere
//#endif

#if !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)

    @# checkpoint for autotest boottime, plz dont remove it
    DPUTK       '['
    DPUTK       'A'
    DPUTK       'T'
    DPUTK       ']'
    DPUTK       '['
    DPUTK       'M'
    DPUTK       'B'
    DPUTK       ']'
    DPUTK       '['
    DPUTK       's'
    DPUTK       't'
    DPUTK       'a'
    DPUTK       'r'
    DPUTK       't'
    DPUTK       ' '
    DPUTK       's'
    DPUTK       'b'
    DPUTK       ']'
    DPUTK       '['
    DPUTK       '0'
    DPUTK       ']'

#endif

#ifdef REG_USB30_GPIO_CONTROL
    bl          BootRom_InitUsb30Gpio
#endif

    mov         lr, r13
    bx          lr

@//-------------------------------------------------------------------------------------------------
@// BootRom_InitRiu
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitRiu
BootRom_InitRiu:

    @//Enable 32-bit RIU Write Data
    RREG        r3, (MS_BUS_RIU_ADDR + (0x101882 << 1))
    ldr         r4, =0x00008000
    orr         r3, r3, r4
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x101882 << 1))

#ifdef CONFIG_MSTAR_32BIT_RIU_MASK_ENABLE
    RREG        r3, (MS_BUS_RIU_ADDR + (0x10012E << 1))
    ldr         r4, =0x00000001
    orr         r3, r3, r4
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x10012E << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x101882 << 1))
    ldr         r4, =0x00008000
    orr         r3, r3, r4
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x101882 << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x00012E << 1))
    ldr         r4, =0x00000001
    orr         r3, r3, r4
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x00012E << 1))
#endif

    bx          lr

@//-------------------------------------------------------------------------------------------------
@// BootRom_InitUart
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitUart
BootRom_InitUart:

#ifdef CONFIG_MSTAR_TITANIA_BD_FPGA
    WREG        (MS_BUS_RIU_ADDR + (0x000E12 << 1)), 0x0800
    WREG        (MS_BUS_RIU_ADDR + (0x101EA6 << 1)), 0x2104
    WREG        (MS_BUS_RIU_ADDR + (0x10098C << 1)), 0x0083
    WREG        (MS_BUS_RIU_ADDR + (0x100980 << 1)), 0x0013
    WREG        (MS_BUS_RIU_ADDR + (0x100984 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x100988 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x10098C << 1)), 0x0003
    WREG        (MS_BUS_RIU_ADDR + (0x100988 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x100988 << 1)), 0x0007
    WREG        (MS_BUS_RIU_ADDR + (0x003008 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x00300A << 1)), 0x0000

    DPUTK       'U'
    DPUTK       'A'
    DPUTK       'R'
    DPUTK       'T'
    DPUTK       '_'
    DPUTK       '3'
    DPUTK       '8'
    DPUTK       '4'
    DPUTK       '0'
    DPUTK       '0'

    DPUTK       '\n'
    DPUTK       '\r'

#else

    WREG        (MS_BUS_RIU_ADDR + (0x100B26 << 1)), 0x0C01 @//Set CLK_UART0 to 123Mhz

    WREG        (MS_BUS_RIU_ADDR + (0x101EA6 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x101EA8 << 1)), 0x0000

.if (BOOTINFO_UART0_ENABLE == 1)
    RREG        r0, (MS_BUS_RIU_ADDR + (0x000E12 << 1))     @//Enable UART Rx via PAD_DDCA for dig_mux
    orr         r0, r0, #0x0800
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x000E12 << 1))

    RREG        r0, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))     @//Select UART0 source to PIU UART0
    orr         r0, r0, #0x0004
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))

    RREG        r0, (MS_BUS_RIU_ADDR + (0x10098C << 1))     @//Enable Divisor Latch Access
    orr         r0, r0, #0x0080
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x10098C << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x100980 << 1)), UART_DIVISOR_L   @//Set Divisor Latch LSB
    WREG        (MS_BUS_RIU_ADDR + (0x100984 << 1)), UART_DIVISOR_H   @//Set Divisor Latch MSB

    RREG        r0, (MS_BUS_RIU_ADDR + (0x10098C << 1))     @//Disable Divisor Latch Access
    ldr         r1, =0xFF7F
    and         r0, r0, r1
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x10098C << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x100988 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x100988 << 1)), 0x0007 @//Enable FIFO and Clear TX/RX FIFO

    WREG        (MS_BUS_RIU_ADDR + (0x10098C << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x10098C << 1)), 0x0003 @//8-bit Data / 1-bit Stop / No Parity Bit
    WREG        (MS_BUS_RIU_ADDR + (0x100990 << 1)), 0x0000 @//Set DTS/RTS to 1
    WREG        (MS_BUS_RIU_ADDR + (0x100984 << 1)), 0x0000 @//Disable Interrupt
.endif

.if (BOOTINFO_UART2_ENABLE == 1)
@// RREG        r0, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))     @//Select UART2 source to PIU UART0
@// orr         r0, r0, #0x0400
@// REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))

    RREG        r0, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))     @//Select UART2 source to PIU UART1
    orr         r0, r0, #0x0550
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))

    RREG        r0, (MS_BUS_RIU_ADDR + (0x11060C << 1))     @//Enable Divisor Latch Access
    orr         r0, r0, #0x0080
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x11060C << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x110600 << 1)), UART_DIVISOR_L   @//Set Divisor Latch LSB
    WREG        (MS_BUS_RIU_ADDR + (0x110604 << 1)), UART_DIVISOR_H   @//Set Divisor Latch MSB

    RREG        r0, (MS_BUS_RIU_ADDR + (0x11060C << 1))     @//Disable Divisor Latch Access
    ldr         r1, =0xFF7F
    and         r0, r0, r1
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x11060C << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x110608 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x110608 << 1)), 0x0007 @//Enable FIFO and Clear TX/RX FIFO

    WREG        (MS_BUS_RIU_ADDR + (0x11060C << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x11060C << 1)), 0x0003 @//8-bit Data / 1-bit Stop / No Parity Bit
    WREG        (MS_BUS_RIU_ADDR + (0x110610 << 1)), 0x0000 @//Set DTS/RTS to 1
    WREG        (MS_BUS_RIU_ADDR + (0x110604 << 1)), 0x0000 @//Disable Interrupt
.endif

    DPUTK       'U'
    DPUTK       'A'
    DPUTK       'R'
    DPUTK       'T'
    DPUTK       '_'
    DPUTK       '1'
    DPUTK       '1'
    DPUTK       '5'
    DPUTK       '2'
    DPUTK       '0'
    DPUTK       '0'

    DPUTK       '\n'
    DPUTK       '\r'

#endif

    bx          lr

@//-------------------------------------------------------------------------------------------------
@// BootRom_EnableMcuAccess
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_EnableMcuAccess
BootRom_EnableMcuAccess:
    WREG        (MS_BUS_RIU_ADDR + (0x002BC4 << 1)), 0x0004
    WREG        (MS_BUS_RIU_ADDR + (0x002BC6 << 1)), 0x3c11
    WREG        (MS_BUS_RIU_ADDR + (0x002BC8 << 1)), 0x0010
    WREG        (MS_BUS_RIU_ADDR + (0x002BCA << 1)), 0x403c
    WREG        (MS_BUS_RIU_ADDR + (0x002BCC << 1)), 0x0101

    bx          lr

#ifdef REG_USB30_GPIO_CONTROL
@//-------------------------------------------------------------------------------------------------
@// BootRom_InitUsb30Gpio
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
BootRom_InitUsb30Gpio:

    WREG        (MS_BUS_RIU_ADDR + (REG_USB30_GPIO_CONTROL << 1)), REG_USB30_GPIO_BANK @//offset addr
    RREG        r0, (MS_BUS_RIU_ADDR + ((REG_USB30_GPIO_CONTROL + 2) << 1))
    ldr         r1, =0x1FFF                             @//[bit 13:15] other usage
    bic         r0, r0, r1
    add         r0, r0, #(REG_USB30_GPIO_BIT << 8) @//bit8~bit10 bit count
    add         r0, r0, #(REG_USB30_GPIO_OFFSET) @//bit0~bit7 offset addr
    REG_C2M     r0, (MS_BUS_RIU_ADDR + ((REG_USB30_GPIO_CONTROL + 2) << 1))

    bx          lr

#endif

#ifdef CONFIG_MSTAR_EDINBURGH
@//-------------------------------------------------------------------------------------------------
@// BootRom_InitExtDemod_Edinburgh
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitExtDemod_Edinburgh
BootRom_InitExtDemod_Edinburgh:

    WREG_B      (MS_BUS_RIU_ADDR + (0x000e60 << 1) + 1), 0x00

    RREG        r0, (MS_BUS_RIU_ADDR + (0x101eae << 1))
    bic         r0, r0, #(0x01 << 2)
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x101eae << 1))

    WREG_B      (MS_BUS_RIU_ADDR + (0x112002 << 1) + 1), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x11280e << 1)), 0x10
    WREG_B      (MS_BUS_RIU_ADDR + (0x11286a << 1) + 1), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x11287a << 1)), 0x01
    WREG_B      (MS_BUS_RIU_ADDR + (0x112878 << 1) + 1), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x112802 << 1)), 0x0C
    WREG_B      (MS_BUS_RIU_ADDR + (0x112802 << 1) + 1), 0x00

    bx          lr

#endif

#ifdef CONFIG_MSTAR_CASHMERE
@//-------------------------------------------------------------------------------------------------
@// BootRom_InitExtDemod_Cashmere
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitExtDemod_Cashmere
BootRom_InitExtDemod_Cashmere:

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x112000 << 1))
    ldr         r3, [r12, #(0x02 << 1)]
    bic         r3, r3, #(0x03 << 13)
    str         r3, [r12, #(0x02 << 1)]

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x112800 << 1))
    ldr         r3, [r12, #(0x40 << 1)]
    bic         r3, r3, #(0x01 << 4)
    str         r3, [r12, #(0x40 << 1)]

    ldr         r3, [r12, #(0x7a << 1)]
    orr         r3, r3, #(0x01 << 0)
    str         r3, [r12, #(0x7a << 1)]

    bx          lr
#endif

#ifdef CONFIG_MSTAR_VID_ENABLE
@//-------------------------------------------------------------------------------------------------
@// BootRom_InitVid
@// @param  None
@// @return None
@// @note None
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitVid
BootRom_InitVid:

    @//Disable All-Pad-In
    RREG        r0, (MS_BUS_RIU_ADDR + (0x101EA0 << 1))
    bic         r0, r0, #0x8000
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x101EA0 << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x10050c << 1)), CONFIG_VID_POWER_LEVEL_0

#if ((CONFIG_VID_USE_SIDD == 1) || (CONFIG_VID_USE_SIDD == 2))
    @//Get SIDD Value (Bank1[21:12] = 0x00200E[5:0] + 0x00200C[15:12]
    RREG        r0, REG_EFUSE_BANK1_HIGH
    RREG        r1, REG_EFUSE_BANK1_LOW                 @//Bank1[21:12] = 0x00200E[5:0] + 0x00200C[15:12]

    and         r0, r0, #0x003f
    mov         r0, r0, lsl #4                          @//Left-shift 4-bit Data to Reserved for Lower SIDD Value

    and         r1, r1, #0xf000
    mov         r1, r1, lsr #12                         @//Right-shift 12-bit Data to Sync the Order of SIDD Value

    orr         r1, r1, r0                              @//Combine to Complete SIDD Value

    ldr         r0, =0x00
    cmp         r1, r0
    beq         BootRom_InitVid_Exit                    @//If no SIDD existed in eFuse, bypass VID flow
#endif

#if ((CONFIG_VID_USE_SIDD == 0) || (CONFIG_VID_USE_SIDD == 2))
    @//Get OSC Value (Bank1[11:2] = 0x00200C[11:2]
    RREG        r2, REG_EFUSE_BANK1_LOW                 @//Bank1[11:2] = 0x00200C[11:2]
    ldr         r0, =0x0ffc
    and         r2, r2, r0
    mov         r2, r2, lsr #2                          @//Right Shift 2-bit Data to Get OSC Value

    ldr         r0, =0x00
    cmp         r2, r0
    beq         BootRom_InitVid_Exit                    @//If no OSC existed in eFuse, bypass VID flow
#endif

#if ((CONFIG_VID_USE_SIDD == 1) || (CONFIG_VID_USE_SIDD == 2))
    ldr         r0, =CONFIG_SIDD_THRESHOLD_0
    cmp         r1, r0
    blt         BootRom_InitVid_SetVoltage_0            @//If SIDD < The Value of Threshold 0, Set Corresponding Voltage 0
#endif

#if (CONFIG_VID_USE_SIDD == 0)
    ldr         r0, =CONFIG_OSC_THRESHOLD_0
    cmp         r2, r0
    blt         BootRom_InitVid_SetVoltage_0            @//If OSC < The Value of Threshold 0, Set Corresponding Voltage 0
#endif

#if (CONFIG_VID_USE_SIDD == 2)
    ldr         r0, =CONFIG_SIDD_THRESHOLD_0_1
    cmp         r1, r0
    bge         BootRom_InitVid_Session_0_Exit          @//If SIDD >= The Value of Threshold 0-1, go to next session

    ldr         r0, =CONFIG_OSC_THRESHOLD_0
    cmp         r2, r0
    blt         BootRom_InitVid_SetVoltage_0            @//If OSC < The Value of Threshold 0, Set Corresponding Voltage 0

BootRom_InitVid_Session_0_Exit:
#endif

#if ((CONFIG_VID_USE_SIDD == 1) || (CONFIG_VID_USE_SIDD == 2))
    ldr         r0, =CONFIG_SIDD_THRESHOLD_1
    cmp         r1, r0
    blt         BootRom_InitVid_SetVoltage_1            @//If SIDD < The Value of Threshold 1, Set Corresponding Voltage 1
#endif

#if ((CONFIG_VID_USE_SIDD == 0) || (CONFIG_VID_USE_SIDD == 2))
    ldr         r0, =CONFIG_OSC_THRESHOLD_1
    cmp         r2, r0
    blt         BootRom_InitVid_SetVoltage_1            @//If OSC < The Value of Threshold 1, Set Corresponding Voltage 1
#endif

#if ((CONFIG_VID_USE_SIDD == 1) || (CONFIG_VID_USE_SIDD == 2))
    ldr         r0, =CONFIG_SIDD_THRESHOLD_2
    cmp         r1, r0
    blt         BootRom_InitVid_SetVoltage_2            @//If SIDD < The Value of Threshold 2, Set Corresponding Voltage 2
#endif

#if ((CONFIG_VID_USE_SIDD == 0) || (CONFIG_VID_USE_SIDD == 2))
    ldr         r0, =CONFIG_OSC_THRESHOLD_2
    cmp         r2, r0
    blt         BootRom_InitVid_SetVoltage_2            @//If OSC < The Value of Threshold 2, Set Corresponding Voltage 2
#endif

    b           BootRom_InitVid_SetVoltage_3            @//If SIDD / OSC >= The Value of Threshold 2, Set Corresponding Voltage 3

BootRom_InitVid_SetVoltage_0:

    WREG        (MS_BUS_RIU_ADDR + (0x10050c << 1)), CONFIG_VID_POWER_LEVEL_0

#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
#if (CONFIG_ENABLE_VID0 != 0)
    @//Set GPIO to Switch Corresponding Voltage (Case 0: 1.28V)
    RREG        r0, REG_VID0_GPIO_CONTROL
    orr         r0, r0, #REG_VID0_GPIO_MASK
    REG_C2M     r0, REG_VID0_GPIO_CONTROL               @//VID0: High
#endif

#if (CONFIG_ENABLE_VID1 != 0)
    RREG        r0, REG_VID1_GPIO_CONTROL
    orr         r0, r0, #REG_VID1_GPIO_MASK
    REG_C2M     r0, REG_VID1_GPIO_CONTROL               @//VID1: High
#endif
#endif

    b           BootRom_InitVid_Exit

BootRom_InitVid_SetVoltage_1:

    WREG        (MS_BUS_RIU_ADDR + (0x10050c << 1)), CONFIG_VID_POWER_LEVEL_1

#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
#if (CONFIG_ENABLE_VID0 != 0)
    @//Set GPIO to Switch Corresponding Voltage (Case 1: 1.20V)
    RREG        r0, REG_VID0_GPIO_CONTROL
    orr         r0, r0, #REG_VID0_GPIO_MASK
    REG_C2M     r0, REG_VID0_GPIO_CONTROL               @//VID0: High
#endif

#if (CONFIG_ENABLE_VID1 != 0)
    RREG        r0, REG_VID1_GPIO_CONTROL
    bic         r0, r0, #REG_VID1_GPIO_MASK
    REG_C2M     r0, REG_VID1_GPIO_CONTROL               @//VID1: Low
#endif
#endif

    b           BootRom_InitVid_Exit

BootRom_InitVid_SetVoltage_2:

    WREG        (MS_BUS_RIU_ADDR + (0x10050c << 1)), CONFIG_VID_POWER_LEVEL_2

#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
#if (CONFIG_ENABLE_VID0 != 0)
    @//Set GPIO to Switch Corresponding Voltage (Case 2: 1.15V)
    RREG        r0, REG_VID0_GPIO_CONTROL
    bic         r0, r0, #REG_VID0_GPIO_MASK
    REG_C2M     r0, REG_VID0_GPIO_CONTROL               @//VID0: Low
#endif

#if (CONFIG_ENABLE_VID1 != 0)
    RREG        r0, REG_VID1_GPIO_CONTROL
    bic         r0, r0, #REG_VID1_GPIO_MASK
    REG_C2M     r0, REG_VID1_GPIO_CONTROL               @//VID1: Low
#endif
#endif

    b           BootRom_InitVid_Exit

BootRom_InitVid_SetVoltage_3:

    WREG        (MS_BUS_RIU_ADDR + (0x10050c << 1)), CONFIG_VID_POWER_LEVEL_3

#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
#if (CONFIG_ENABLE_VID0 != 0)
    @//Set GPIO to Switch Corresponding Voltage (Case 3: Reserved)
    RREG        r0, REG_VID0_GPIO_CONTROL
    bic         r0, r0, #REG_VID0_GPIO_MASK
    REG_C2M     r0, REG_VID0_GPIO_CONTROL               @//VID0: Low
#endif

#if (CONFIG_ENABLE_VID1 != 0)
    RREG        r0, REG_VID1_GPIO_CONTROL
    orr         r0, r0, #REG_VID1_GPIO_MASK
    REG_C2M     r0, REG_VID1_GPIO_CONTROL               @//VID1: High
#endif
#endif

BootRom_InitVid_Exit:

    bx          lr
#endif

#ifdef CONFIG_MSTAR_DVFS_ENABLE
@//-------------------------------------------------------------------------------------------------
@// BootRom_InitDvfs
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitDvfs
BootRom_InitDvfs:

    RREG        r0, (MS_BUS_RIU_ADDR + (0x001e02 << 1))
    mov         r0, r0, lsr #8
    and         r0, r0, #0x00ff
    cmp         r0, #0x02
    blt         BootRom_InitDvfs_Exit

    WREG        (MS_BUS_RIU_ADDR + (0x100500 << 1)), 0x3697     @//The switch of DVFS flow
    WREG        (MS_BUS_RIU_ADDR + (0x100502 << 1)), CPU_CLOCK  @//Current CPU Clock
    WREG        (MS_BUS_RIU_ADDR + (0x100504 << 1)), 0          @//Current Temperature (CPU)
    WREG        (MS_BUS_RIU_ADDR + (0x100506 << 1)), 0          @//Current Temperature (PM)
    WREG        (MS_BUS_RIU_ADDR + (0x100508 << 1)), CONFIG_MSTAR_DVFS_TEMPERATURE_UPPER_BOUND  @//Upper Bound of T-sensor
    WREG        (MS_BUS_RIU_ADDR + (0x10050a << 1)), CONFIG_MSTAR_DVFS_TEMPERATURE_LOWER_BOUND  @//Lower Bound of T-sensor
    WREG        (MS_BUS_RIU_ADDR + (0x10050e << 1)), CONFIG_MSTAR_DVFS_TEMPERATURE_THRESHOLD    @//Upper Bound of Global Reset

    WREG        (MS_BUS_RIU_ADDR + (0x110ca0 << 1)), (CONFIG_DVFS_CPU_CLOCK_MIN & 0xFFFF)
    WREG        (MS_BUS_RIU_ADDR + (0x110ca2 << 1)), ((CONFIG_DVFS_CPU_CLOCK_MIN >> 16) & 0xFFFF)

    WREG        (MS_BUS_RIU_ADDR + (0x110ca4 << 1)), (CONFIG_DVFS_CPU_CLOCK_MAX & 0xFFFF)
    WREG        (MS_BUS_RIU_ADDR + (0x110ca6 << 1)), ((CONFIG_DVFS_CPU_CLOCK_MAX >> 16) & 0xFFFF)

    @//Get T-Sensor Trim Value
    @//- TR[5:0]: Bank2[29:24] = 0x002013[5:0]
    @//- GCR_TRVBE[5:0]: Bank2[31:30] + Bank3[3:0] = 0x002013[7:6] + 0x002014[3:0]
    RREG        r0, (MS_BUS_RIU_ADDR + (0x002012 << 1))
    mov         r0, r0, lsr #8
    and         r0, r0, #0x003f             @//Get T-Sensor TR[5:0] (VREF)

    RREG        r1, (MS_BUS_RIU_ADDR + (0x000e50 << 1))
    and         r1, r1, #~(0x003f << 10)
    mov         r0, r0, lsl #10
    orr         r1, r1, r0
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x000e50 << 1))

    RREG        r0, (MS_BUS_RIU_ADDR + (0x002012 << 1))
    RREG        r1, (MS_BUS_RIU_ADDR + (0x002014 << 1))
    mov         r0, r0, lsr #14
    and         r0, r0, #0x0003
    mov         r1, r1, lsl #2
    orr         r0, r0, r1
    and         r0, r0, #0x003f             @//Get T-Sensor GCR_TRVBE[5:0] (VBE)

    RREG        r1, (MS_BUS_RIU_ADDR + (0x000eca << 1))
    and         r1, r1, #~(0x003f << 1)
    mov         r0, r0, lsl #1
    orr         r1, r1, r0
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x000eca << 1))

BootRom_InitDvfs_Exit:

    bx          lr
#endif

#ifdef CONFIG_MSTAR_MOBF_ENABLE
@//-------------------------------------------------------------------------------------------------
@// BootRom_InitMobf
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitMobf
BootRom_InitMobf:

    WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0xC000  @//enable dramobf

    WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0xC001
    WREG        (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x0100
    WREG        (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x0302

    WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0002
    WREG        (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x0504
    WREG        (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x0706

    WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0003
    WREG        (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x0908
    WREG        (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x0b0a

    WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0004
    WREG        (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x1100
    WREG        (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x1302

    WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0005
    WREG        (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x1504
    WREG        (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x1706

    WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0006
    WREG        (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x1908
    WREG        (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x1b0a

    WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0007
    WREG        (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x1d0c
    WREG        (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x1f0e

    WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0008
    WREG        (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x2100
    WREG        (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x2302

    WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0009
    WREG        (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x2504
    WREG        (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x2706

    WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x000A
    WREG        (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x2908
    WREG        (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x2b0a

    WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x000B
    WREG        (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x2d0c
    WREG        (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x2f0e

    WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x000C
    WREG        (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x3100
    WREG        (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x3302

    WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x000D
    WREG        (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x3504
    WREG        (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x3706

    WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x000E
    WREG        (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x3908
    WREG        (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x3b0a

    WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x000F
    WREG        (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x3d0c
    WREG        (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x3f0e

    WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0010
    WREG        (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x4100
    WREG        (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x4302

    WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0011
    WREG        (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x4504
    WREG        (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x4706

    WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x0012
    WREG        (MS_BUS_RIU_ADDR + (0x113BE8 << 1)), 0x4908
    WREG        (MS_BUS_RIU_ADDR + (0x113BEA << 1)), 0x4b0a

    bx          lr
#endif

@//-------------------------------------------------------------------------------------------------
@// BootRom_InitTimer
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitTimer
BootRom_InitTimer:
    WREG        (MS_BUS_RIU_ADDR + (0x3024 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x3026 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x3044 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x3046 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x3020 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x3020 << 1)), 0x0001
    WREG        (MS_BUS_RIU_ADDR + (0x3040 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x3040 << 1)), 0x0001

    bx          lr

@//-------------------------------------------------------------------------------------------------
@// BootRom_InitMhlCbusTrimmingControl
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitMhlCbusTrimmingControl
BootRom_InitMhlCbusTrimmingControl:

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x2000 << 1))
    ldr         r11, =0x004f
    str         r11, [r12, #(0x4e << 1)]                    @//Set bank to read efuse

    ldr         r11, =0x0001
    str         r11, [r12, #(0x4c << 1)]                    @//Launch efuse read

BootRom_InitMhlCbusTrimmingControlLoop:
    ldr         r11, [r12, #(0x4c << 1)]                    @//Polling efuse read down
    cmp         r11, #0
    bne         BootRom_InitMhlCbusTrimmingControlLoop

    ldr         r11, [r12, #(0x50 << 1)]                    @//Get efuse data

    mov         r0, r11, lsr #8

    and         r1, r0, #0x04                               @//Check efuse data is valid
    cmp         r1, #0
    beq         BootRom_InitMhlCbusTrimmingControlExit

    mov         r0, r0, lsl #3
    and         r0, r0, #(0x03 << 3)

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x2f00 << 1))
    ldr         r11, [r12, #(0x62 << 1)]
    and         r11, r11, #~(0x03 << 3)
    orr         r11, r11, r0
    str         r11, [r12, #(0x62 << 1)]

BootRom_InitMhlCbusTrimmingControlExit:

    bx          lr

@//-------------------------------------------------------------------------------------------------
@// BootRom_InitEmacTrimmingControl
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitEmacTrimmingControl
BootRom_InitEmacTrimmingControl:

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x2000 << 1))
    ldr         r11, =0x004d
    str         r11, [r12, #(0x4e << 1)]                    @//Set bank to read efuse

    ldr         r11, =0x0001
    str         r11, [r12, #(0x4c << 1)]                    @//Launch efuse read

BootRom_InitEmacTrimmingControlLoop:
    ldr         r11, [r12, #(0x4c << 1)]                    @//Polling efuse read down
    cmp         r11, #0
    bne         BootRom_InitEmacTrimmingControlLoop

    ldr         r11, [r12, #(0x50 << 1)]                    @//Get eFuse at Bank 0x4D[13:0]

    ldr         r1, =0x3FFF
    and         r0, r11, r1

    mov         r1, r11, lsr #14
    and         r1, r1, #0x03

    ldr         r11, [r12, #(0x52 << 1)]                    @//Get eFuse at Bank 0x4D[17:14]

    and         r11, r11, #0x03
    mov         r11, r11, lsl #2
    orr         r1, r1, r11
    mov         r1, r1, lsl #8

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x3400 << 1))
    ldr         r11, [r12, #(0x60 << 1)]
    and         r11, r11, #~(0x0f << 8)
    orr         r11, r11, r1
    orr         r11, r11, #(0x01 << 2)
    str         r11, [r12, #(0x60 << 1)]                    @//0x0034_60[11:8] + 0x0034_60[2] = 1

    ldr         r11, [r12, #(0x68 << 1)]
    and         r11, r11, #0xC000
    orr         r11, r11, r0
    orr         r11, r11, #(0x01 << 15)
    str         r11, [r12, #(0x68 << 1)]                    @//0x0034_68[13:0] + 0x0034_68[15] = 1

BootRom_InitEmacTrimmingControlExit:

    bx          lr

@//-------------------------------------------------------------------------------------------------
@// BootRom_InitModTrimmingControl
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitModTrimmingControl
BootRom_InitModTrimmingControl:

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x2000 << 1))
    ldr         r11, =0x004f
    str         r11, [r12, #(0x4e << 1)]                    @//Set bank to read efuse

    ldr         r11, =0x0001
    str         r11, [r12, #(0x4c << 1)]                    @//Launch efuse read

BootRom_InitModTrimmingControlLoop:
    ldr         r11, [r12, #(0x4c << 1)]                    @//Polling efuse read down
    cmp         r11, #0
    bne         BootRom_InitModTrimmingControlLoop

    ldr         r11, [r12, #(0x50 << 1)]                    @//Get efuse data
    and         r0, r11, #(0x01 << 6)

    cmp         r0, #0
    beq         BootRom_InitModTrimmingControl_Disable

BootRom_InitModTrimmingControl_Enable:

    ldr         r11, [r12, #(0x50 << 1)]                    @//Get efuse data
    and         r11, r11, #0x3f
    add         r11, r11, #3
    mov         r0, r11, lsl #8
    orr         r11, r11, r0

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x103200 << 1))

    b           BootRom_InitModTrimmingControlExit

BootRom_InitModTrimmingControl_Disable:

    ldr         r11, =0x3f3f

BootRom_InitModTrimmingControlExit:

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x103200 << 1))
    str         r11, [r12, #(0x54 << 1)]
    str         r11, [r12, #(0x56 << 1)]
    str         r11, [r12, #(0x58 << 1)]

    bx          lr
