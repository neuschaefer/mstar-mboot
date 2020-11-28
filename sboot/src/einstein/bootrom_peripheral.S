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

#ifdef CONFIG_MSTAR_EDINBURGH
    bl          BootRom_InitExtDemod
#endif

#ifdef CONFIG_MSTAR_CASHMERE
    bl          BootRom_InitExtDemod_Cashmere
#endif

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

#if defined(CONFIG_HDMI_USE_AS_DEBUG_PORT)
    WREG        (MS_BUS_RIU_ADDR + (0x002E3C << 1)), 0x0011
#endif

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

    PUTK        'U'
    PUTK        'A'
    PUTK        'R'
    PUTK        'T'
    PUTK        '_'
    PUTK        '3'
    PUTK        '8'
    PUTK        '4'
    PUTK        '0'
    PUTK        '0'

    PUTK        '\n'
    PUTK        '\r'

#else
    RREG        r0, (MS_BUS_RIU_ADDR + (0x000E12 << 1))
    orr         r0, r0, #0x0800
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x000E12 << 1))
    
    WREG        (MS_BUS_RIU_ADDR + (0x100B26 << 1)), 0x0C01 @//Set CLK_UART0 to 160Mhz

.if (BOOTINFO_UART0_ENABLE == 1)
    RREG        r0, (MS_BUS_RIU_ADDR + (0x000E12 << 1))     @//Enable UART Rx via PAD_DDCA for dig_mux
    orr         r0, r0, #0x0800
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x000E12 << 1))

    RREG        r0, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))     @//Select UART0 source to PIU UART0
    orr         r0, r0, #0x0004
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))

.endif


.if (BOOTINFO_UART2_ENABLE == 1)
@// RREG        r0, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))     @//Select UART2 source to PIU UART0
@// orr         r0, r0, #0x0400
@// REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))


    WREG        (MS_BUS_RIU_ADDR + (0x101EA6 << 1)), 0x0504 @//Set UART4 source to None
    WREG        (MS_BUS_RIU_ADDR + (0x101EA8 << 1)), 0x0000 @//Set UART4 source to None

    RREG        r0, (MS_BUS_RIU_ADDR + (0x101E04 << 1))     @//Set third UART mode: RX2/TX2 uses PAD_UART_RX2/PAD_UART_TX2
    @//set PAD_GPIO13 / PAD_GPIO14, HW need to pull high for this pad for PIU UART1
    @orr         r0, r0, #0x0C00
    orr         r0, r0, #0x0300
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x101E04 << 1))


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

    PUTK        'U'
    PUTK        'A'
    PUTK        'R'
    PUTK        'T'
    PUTK        '_'
    PUTK        '1'
    PUTK        '1'
    PUTK        '5'
    PUTK        '2'
    PUTK        '0'
    PUTK        '0'

    PUTK        '\n'
    PUTK        '\r'

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
    add         r0, r0, #(REG_USB30_GPIO_LOW_ACTIVE<<11) @// Turn on 5V  ( 0:  GPIO High   1: GPIO Low)
    REG_C2M     r0, (MS_BUS_RIU_ADDR + ((REG_USB30_GPIO_CONTROL + 2) << 1))

    bx          lr

#endif


#ifdef CONFIG_MSTAR_EDINBURGH
@//-------------------------------------------------------------------------------------------------
@// BootRom_InitExtDemod
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitExtDemod
BootRom_InitExtDemod:

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
    WREG_B      (MS_BUS_RIU_ADDR + (0x112002 << 1) + 1), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x112840 << 1)), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x11287a << 1)), 0x01
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

#ifdef CONFIG_MSTAR_DVFS_ENABLE
#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
    @//0x1005_0C[15:12]: Current Port (2)
    @//0x1005_0C[11:8]: Maximum Port (3)
    @//0x1005_0C[7:0]: Reserved
    ldr         r0, =0x23FF
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x10050c << 1))
#else
    @//0x1005_0C[15:8]: Max Voltage (1.45V = 0x91)
    @//0x1005_0C[7:0]: Current Voltage (1.20V = 0x78)
    ldr         r0, =0x9178
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x10050c << 1))
#endif
#endif

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

#if ((CONFIG_VID_USE_SIDD == 0) || (CONFIG_VID_USE_SIDD == 2))
    ldr         r0, =CONFIG_OSC_THRESHOLD_0
    cmp         r2, r0
    blt         BootRom_InitVid_SetVoltage_0            @//If OSC < The Value of Threshold 0, Set Corresponding Voltage 0
#endif

#if ((CONFIG_VID_USE_SIDD == 1) || (CONFIG_VID_USE_SIDD == 2))
    ldr         r0, =CONFIG_SIDD_THRESHOLD_0
    cmp         r1, r0
    blt         BootRom_InitVid_SetVoltage_0            @//If SIDD < The Value of Threshold 0, Set Corresponding Voltage 0
#endif

#if ((CONFIG_VID_USE_SIDD == 0) || (CONFIG_VID_USE_SIDD == 2))
    ldr         r0, =CONFIG_OSC_THRESHOLD_1
    cmp         r2, r0
    blt         BootRom_InitVid_SetVoltage_1            @//If OSC < The Value of Threshold 1, Set Corresponding Voltage 1
#endif

#if ((CONFIG_VID_USE_SIDD == 1) || (CONFIG_VID_USE_SIDD == 2))
    ldr         r0, =CONFIG_SIDD_THRESHOLD_1
    cmp         r1, r0
    blt         BootRom_InitVid_SetVoltage_1            @//If SIDD < The Value of Threshold 1, Set Corresponding Voltage 1
#endif

#if ((CONFIG_VID_USE_SIDD == 0) || (CONFIG_VID_USE_SIDD == 2))
    ldr         r0, =CONFIG_OSC_THRESHOLD_2
    cmp         r2, r0
    blt         BootRom_InitVid_SetVoltage_2            @//If OSC < The Value of Threshold 2, Set Corresponding Voltage 2
#endif

#if ((CONFIG_VID_USE_SIDD == 1) || (CONFIG_VID_USE_SIDD == 2))
    ldr         r0, =CONFIG_SIDD_THRESHOLD_2
    cmp         r1, r0
    blt         BootRom_InitVid_SetVoltage_2            @//If SIDD < The Value of Threshold 2, Set Corresponding Voltage 2
#endif

    b           BootRom_InitVid_SetVoltage_3            @//If SIDD / OSC >= The Value of Threshold 2, Set Corresponding Voltage 3

BootRom_InitVid_SetVoltage_0:

#ifdef CONFIG_MSTAR_DVFS_ENABLE
#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
    @//0x1005_0C[15:12]: Current Port (2)
    @//0x1005_0C[11:8]: Maximum Port (3)
    @//0x1005_0C[7:0]: Reserved
    ldr         r0, =0x23FF
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x10050c << 1))
#else
    @//0x1005_0C[15:8]: Max Voltage (1.45V = 0x91)
    @//0x1005_0C[7:0]: Current Voltage (1.20V = 0x78)
    ldr         r0, =0x9178
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x10050c << 1))
#endif
#endif

#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
#if (CONFIG_ENABLE_VID0 != 0)
    @//Set GPIO to Switch Corresponding Voltage (Case 0: 1.20V)
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

    b           BootRom_InitVid_Exit

BootRom_InitVid_SetVoltage_1:

#ifdef CONFIG_MSTAR_DVFS_ENABLE
#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
    @//0x1005_0C[15:12]: Current Port (1)
    @//0x1005_0C[11:8]: Maximum Port (3)
    @//0x1005_0C[7:0]: Reserved
    ldr         r0, =0x13FF
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x10050c << 1))
#else
    @//0x1005_0C[15:8]: Max Voltage (1.30 = 0x82)
    @//0x1005_0C[7:0]: Current Voltage (1.10 = 0x6E)
    ldr         r0, =0x826E
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x10050c << 1))
#endif
#endif

#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
#if (CONFIG_ENABLE_VID0 != 0)
    @//Set GPIO to Switch Corresponding Voltage (Case 1: 1.10V)
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

#ifdef CONFIG_MSTAR_DVFS_ENABLE
#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
    @//0x1005_0C[15:12]: Current Port (2)
    @//0x1005_0C[11:8]: Maximum Port (3)
    @//0x1005_0C[7:0]: Reserved
    ldr         r0, =0x03FF
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x10050c << 1))
#else
    @//0x1005_0C[15:8]: Max Voltage (Reserved)
    @//0x1005_0C[7:0]: Current Voltage (Reserved)
    ldr         r0, =0xFFFF
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x10050c << 1))
#endif
#endif

#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
#if (CONFIG_ENABLE_VID0 != 0)
    @//Set GPIO to Switch Corresponding Voltage (Case 2: Reserved)
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

#ifdef CONFIG_MSTAR_DVFS_ENABLE
#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
    @//0x1005_0C[15:12]: Current Port (3)
    @//0x1005_0C[11:8]: Maximum Port (3)
    @//0x1005_0C[7:0]: Reserved
    ldr         r0, =0x33FF
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x10050c << 1))
#else
    @//0x1005_0C[15:8]: Max Voltage (Reserved)
    @//0x1005_0C[7:0]: Current Voltage (Reserved)
    ldr         r0, =0xFFFF
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x10050c << 1))
#endif
#endif

#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
#if (CONFIG_ENABLE_VID0 != 0)
    @//Set GPIO to Switch Corresponding Voltage (Case 3: Reserved)
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

    WREG        (MS_BUS_RIU_ADDR + (0x100500 << 1)), 0x3697     @//The switch of DVFS flow
    WREG        (MS_BUS_RIU_ADDR + (0x100502 << 1)), CPU_CLOCK  @//Current CPU Clock
    WREG        (MS_BUS_RIU_ADDR + (0x100504 << 1)), 0          @//Current Temperature (CPU)
    WREG        (MS_BUS_RIU_ADDR + (0x100506 << 1)), 0          @//Current Temperature (PM)

@// WREG        (MS_BUS_RIU_ADDR + (0x100508 << 1)), CONFIG_MSTAR_DVFS_TEMPERATURE_UPPER_BOUND  @//Upper Bound of T-sensor
@// WREG        (MS_BUS_RIU_ADDR + (0x10050a << 1)), CONFIG_MSTAR_DVFS_TEMPERATURE_LOWER_BOUND  @//Lower Bound of T-sensor
@// WREG        (MS_BUS_RIU_ADDR + (0x10050e << 1)), CONFIG_MSTAR_DVFS_TEMPERATURE_THRESHOLD    @//Upper Bound of Global Reset

    ldr         r0, =CONFIG_MSTAR_DVFS_TEMPERATURE_UPPER_BOUND  @//Upper Bound of T-sensor
    mov         r0, r0, lsl #8
    ldr         r1, =CONFIG_MSTAR_DVFS_TEMPERATURE_LOWER_BOUND  @//Lower Bound of T-sensor
    orr         r0, r0, r1
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x100508 << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x10050a << 1)), CONFIG_MSTAR_DVFS_TEMPERATURE_THRESHOLD    @//Upper Bound of Global Reset
    WREG        (MS_BUS_RIU_ADDR + (0x10050e << 1)), 0x2454     @//Dynamic Clock Adjustment in Command Line

    WREG        (MS_BUS_RIU_ADDR + (0x110ca0 << 1)), (CONFIG_DVFS_CPU_CLOCK_MIN & 0xFFFF)
    WREG        (MS_BUS_RIU_ADDR + (0x110ca2 << 1)), ((CONFIG_DVFS_CPU_CLOCK_MIN >> 16) & 0xFFFF)

    WREG        (MS_BUS_RIU_ADDR + (0x110ca4 << 1)), (CONFIG_DVFS_CPU_CLOCK_MAX & 0xFFFF)
    WREG        (MS_BUS_RIU_ADDR + (0x110ca6 << 1)), ((CONFIG_DVFS_CPU_CLOCK_MAX >> 16) & 0xFFFF)

    @//Get T-Sensor Trim Value
    @//- TR[5:0]: Bank2[29:24] = 0x002013[5:0]
    @//- GCR_TRVBE[5:0]: 0x002013[5:0]
    @//- GCR_TRVBG[5:0]: 0x002014[3:0] + 0x002013[7:6]
    
    RREG        r0, (MS_BUS_RIU_ADDR + (0x00204a << 1))
    orr         r0, r0, #0x0100
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x00204a << 1))    
    
    RREG        r0, (MS_BUS_RIU_ADDR + (0x002012 << 1))
    mov         r0, r0, lsr #8
    and         r0, r0, #0x003f             @//Get T-Sensor GCR_TRVBE[5:0]

    cmp         r0, #0x00
    beq         BootRom_EFUSE_GCR_TRVBG

    RREG        r1, (MS_BUS_RIU_ADDR + (0x000ec6 << 1))
    and         r1, r1, #~(0x003f << 1)
    mov         r0, r0, lsl #1
    orr         r1, r1, r0
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x000ec6 << 1))

BootRom_EFUSE_GCR_TRVBG:

    RREG        r0, (MS_BUS_RIU_ADDR + (0x002012 << 1))
    RREG        r1, (MS_BUS_RIU_ADDR + (0x002014 << 1))
    mov         r0, r0, lsr #14
    and         r0, r0, #0x0003
    mov         r1, r1, lsl #2
    orr         r0, r0, r1
    and         r0, r0, #0x003f             @//Get T-Sensor GCR_TRVBG[5:0]

    cmp         r0, #0x00
    beq         BootRom_InitDvfs_Exit

    RREG        r1, (MS_BUS_RIU_ADDR + (0x000ec8 << 1))
    and         r1, r1, #~(0x003f << 1)
    mov         r0, r0, lsl #1
    orr         r1, r1, r0
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x000ec8 << 1))

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
