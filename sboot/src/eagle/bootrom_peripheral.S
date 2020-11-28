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
    .global     BootRom_InitPeripheral

BootRom_InitPeripheral:

    mov         r13, lr

@//================================================================================================
    @//Initial related settings of UART
    bl          BootRom_InitUart
    DBGREG      0x000A

	DPUTK       '['
	DPUTK       'A'
	DPUTK       'u'
	DPUTK       't'
	DPUTK       'o'
	DPUTK       'T'
	DPUTK       'e'
	DPUTK       's'
	DPUTK       't'
	DPUTK       ']'
	DPUTK       '['
	DPUTK       'M'
	DPUTK       'b'
	DPUTK       'o'
	DPUTK       'o'
	DPUTK       't'
	DPUTK       ']'
	DPUTK       '['
	DPUTK       's'
	DPUTK       't'
	DPUTK       'a'
	DPUTK       'r'
	DPUTK       't'
	DPUTK       ' '
	DPUTK       'S'
	DPUTK       'b'
	DPUTK       'o'
	DPUTK       'o'
	DPUTK       't'
	DPUTK       ']'
	DPUTK       '['
	DPUTK       '0'
	DPUTK       ']'

@//================================================================================================
    @//Enable 8051 to access MIU for MStar TV Tool
    bl          BootRom_EnableMcuAccess

@//================================================================================================
    @//Initial related settings of RIU
    bl          BootRom_InitRiu

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

    WREG        (MS_BUS_RIU_ADDR + (0x100B26 << 1)), 0x0C01 @//Set CLK_UART0 to 123Mhz

.if (BOOTINFO_UART0_ENABLE == 1)
    RREG        r0, (MS_BUS_RIU_ADDR + (0x000E12 << 1))     @//Enable UART Rx via PAD_DDCA for dig_mux
    orr         r0, r0, #0x0800
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x000E12 << 1))

    RREG        r0, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))     @//Select UART0 source to PIU UART0
    orr         r0, r0, #0x0004
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))

.endif

.if (BOOTINFO_UART2_ENABLE == 1)
    @//RREG        r0, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))     @//Select UART2 source to PIU UART0
    @//orr         r0, r0, #0x0400
    @//REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))


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

#if (CONFIG_VID_USE_SIDD == 1)

    @//Get SIDD Value (Bank1[21:12] = 0x00200E[5:0] + 0x00200C[15:12]
    RREG        r0, REG_EFUSE_BANK1_HIGH
    RREG        r1, REG_EFUSE_BANK1_LOW                 @//Bank1[21:12] = 0x00200E[5:0] + 0x00200C[15:12]

    and         r0, r0, #0x003f
    mov         r0, r0, lsl #4                          @//Left-shift 4-bit Data to Reserved for Lower SIDD Value

    and         r1, r1, #0xf000
    mov         r1, r1, lsr #12                         @//Right-shift 12-bit Data to Sync the Order of SIDD Value

    orr         r1, r1, r0                              @//Combine to Complete SIDD Value

#else

    @//Get OSC Value (Bank1[31:22] = 0x00200E[15:6]
    RREG        r0, REG_EFUSE_BANK1_HIGH                @//Bank1[31:22] = 0x00200E[15:6]
    ldr         r1, =0xffc0
    and         r0, r0, r1
    mov         r1, r0, lsr #6                          @//Right Shift 6-bit Data to Get OSC Value

#endif

	ldr		    r0, =CONFIG_VID_THRESHOLD_0
    cmp         r1, r0
    blt         BootRom_InitVid_SetVoltage_0            @//If SIDD/OSC < The Value of Threshold 0, Set Corresponding Voltage 0

	ldr		    r0, =CONFIG_VID_THRESHOLD_1
    cmp         r1, r0
    blt         BootRom_InitVid_SetVoltage_1            @//If SIDD/OSC < The Value of Threshold 1, Set Corresponding Voltage 1

	ldr		    r0, =CONFIG_VID_THRESHOLD_2
    cmp         r1, r0
    blt         BootRom_InitVid_SetVoltage_2            @//If SIDD/OSC < The Value of Threshold 2, Set Corresponding Voltage 2

    b           BootRom_InitVid_SetVoltage_3            @//If SIDD/OSC >= The Value of Threshold 2, Set Corresponding Voltage 3

BootRom_InitVid_SetVoltage_0:

#if (CONFIG_ENABLE_VID0 != 0)
    @//Set GPIO to Switch Corresponding Voltage (Case 0)
    RREG        r0, REG_VID0_GPIO_CONTROL
    orr         r0, r0, #REG_VID0_GPIO_MASK
    REG_C2M     r0, REG_VID0_GPIO_CONTROL               @//VID0: High
#endif

#if (CONFIG_ENABLE_VID1 != 0)
    RREG        r0, REG_VID1_GPIO_CONTROL
    orr         r0, r0, #REG_VID1_GPIO_MASK
    REG_C2M     r0, REG_VID1_GPIO_CONTROL               @//VID1: High
#endif

    b           BootRom_InitVid_Exit

BootRom_InitVid_SetVoltage_1:

#if (CONFIG_ENABLE_VID0 != 0)
    @//Set GPIO to Switch Corresponding Voltage (Case 1)
    RREG        r0, REG_VID0_GPIO_CONTROL
    bic         r0, r0, #REG_VID0_GPIO_MASK
    REG_C2M     r0, REG_VID0_GPIO_CONTROL               @//VID0: Low
#endif

#if (CONFIG_ENABLE_VID1 != 0)
    RREG        r0, REG_VID1_GPIO_CONTROL
    orr         r0, r0, #REG_VID1_GPIO_MASK
    REG_C2M     r0, REG_VID1_GPIO_CONTROL               @//VID1: High
#endif

    b           BootRom_InitVid_Exit

BootRom_InitVid_SetVoltage_2:

#if (CONFIG_ENABLE_VID0 != 0)
    @//Set GPIO to Switch Corresponding Voltage (Case 2)
    RREG        r0, REG_VID0_GPIO_CONTROL
    orr         r0, r0, #REG_VID0_GPIO_MASK
    REG_C2M     r0, REG_VID0_GPIO_CONTROL               @//VID0: High
#endif

#if (CONFIG_ENABLE_VID1 != 0)
    RREG        r0, REG_VID1_GPIO_CONTROL
    bic         r0, r0, #REG_VID1_GPIO_MASK
    REG_C2M     r0, REG_VID1_GPIO_CONTROL               @//VID1: Low
#endif

    b           BootRom_InitVid_Exit

BootRom_InitVid_SetVoltage_3:

#if (CONFIG_ENABLE_VID0 != 0)
    @//Set GPIO to Switch Corresponding Voltage (Case 3)
    RREG        r0, REG_VID0_GPIO_CONTROL
    bic         r0, r0, #REG_VID0_GPIO_MASK
    REG_C2M     r0, REG_VID0_GPIO_CONTROL               @//VID0: Low
#endif

#if (CONFIG_ENABLE_VID1 != 0)
    RREG        r0, REG_VID1_GPIO_CONTROL
    bic         r0, r0, #REG_VID1_GPIO_MASK
    REG_C2M     r0, REG_VID1_GPIO_CONTROL               @//VID1: Low
#endif

BootRom_InitVid_Exit:

    bx          lr
#endif
