/*
 *#############################################################################
 *
 * Copyright (c) 2006-2014 MStar Semiconductor, Inc.
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
    @//bl          BootRom_InitModTrimmingControl

    @//Initial MHL CBus Trimming Control Setting
    bl          BootRom_InitMhlCbusTrimmingControl

    @//Initial EMAC Trimming Control Setting
    @//bl          BootRom_InitEmacTrimmingControl

#ifdef CONFIG_MSTAR_EDINBURGH
    bl          BootRom_InitExtDemod_Edinburgh
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

    ldr         r1, =(MS_BUS_RIU_ADDR + (0x100b00 << 1))
    ldr         r0, =0x0c01
    str         r0, [r1, #(0x26 << 1)]                      @//Set CLK_UART0 to 123Mhz

    ldr         r1, =(MS_BUS_RIU_ADDR + (0x101e00 << 1))
    ldr         r0, =0x0000
    str         r0, [r1, #(0xa6 << 1)]
    ldr         r0, =0x0100
    str         r0, [r1, #(0xa8 << 1)]

.if (BOOTINFO_UART0_ENABLE == 1)
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x000e00 << 1))
    ldr         r0, [r1, #(0x12 << 1)]
    orr         r0, r0, #0x0800
    str         r0, [r1, #(0x12 << 1)]                      @//Enable UART Rx via PAD_DDCA for dig_mux

    ldr         r1, =(MS_BUS_RIU_ADDR + (0x101e00 << 1))
    ldr         r0, [r1, #(0xa6 << 1)]
    orr         r0, r0, #0x0004
    str         r0, [r1, #(0xa6 << 1)]                      @//Select UART0 source to PIU UART0

    ldr         r1, =(MS_BUS_RIU_ADDR + (0x100900 << 1))
    ldr         r0, [r1, #(0x8c << 1)]
    orr         r0, r0, #0x0080
    str         r0, [r1, #(0x8c << 1)]                      @//Enable Divisor Latch Access

    ldr         r0, =UART_DIVISOR_L
    str         r0, [r1, #(0x80 << 1)]                      @//Set Divisor Latch LSB
    
    ldr         r0, =UART_DIVISOR_H
    str         r0, [r1, #(0x84 << 1)]                      @//Set Divisor Latch MSB

    ldr         r0, [r1, #(0x8c << 1)] 
    bic         r0, r0, #0x0080
    str         r0, [r1, #(0x8c << 1)]                      @//Disable Divisor Latch Access

    ldr         r0, =0x0000
    str         r0, [r1, #(0x88 << 1)] 
    ldr         r0, =0x0007
    str         r0, [r1, #(0x88 << 1)]                      @//Enable FIFO and Clear TX/RX FIFO

    ldr         r0, =0x0000
    str         r0, [r1, #(0x8c << 1)] 
    ldr         r0, =0x0003
    str         r0, [r1, #(0x8c << 1)]                      @//8-bit Data / 1-bit Stop / No Parity Bit

    ldr         r0, =0x0000
    str         r0, [r1, #(0x90 << 1)]                      @//Set DTS/RTS to 1

    ldr         r0, =0x0000
    str         r0, [r1, #(0x84 << 1)]                      @//Disable Interrupt
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

.if (BOOTINFO_UART3_ENABLE == 1)

		ldr         r1, =(MS_BUS_RIU_ADDR + (0x100b00 << 1))    @//Set CLK_UART3 to 123Mhz
    ldr         r0, =0x000c
    str         r0, [r1, #(0x32 << 1)]
    
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x101e00 << 1))    @//Select UART3 source to PIU_UART3 (check Bond.h)
    ldr         r0, [r1, #(0xa8 << 1)]
    orr         r0, r0, #0x0030
    str         r0, [r1, #(0xa8 << 1)]
    
    ldr         r0, [r1, #(0x08 << 1)]                      @// uart mode pad mux (P6/N6 uses PAD_GPIO35/PAD_GPIO34)
    orr         r0, r0, #0x0040
    str         r0, [r1, #(0x08 << 1)] 
 		
		RREG        r0, (MS_BUS_RIU_ADDR + (0x10090C << 1))     @//Enable Divisor Latch Access
    orr         r0, r0, #0x0080
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x10090C << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x100900 << 1)), UART_DIVISOR_L   @//Set Divisor Latch LSB
    WREG        (MS_BUS_RIU_ADDR + (0x100904 << 1)), UART_DIVISOR_H   @//Set Divisor Latch MSB

    RREG        r0, (MS_BUS_RIU_ADDR + (0x10090C << 1))     @//Disable Divisor Latch Access
    ldr         r1, =0xFF7F
    and         r0, r0, r1
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x10090C << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x100908 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x100908 << 1)), 0x0007 @//Enable FIFO and Clear TX/RX FIFO

    WREG        (MS_BUS_RIU_ADDR + (0x10090C << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x10090C << 1)), 0x0003 @//8-bit Data / 1-bit Stop / No Parity Bit
    WREG        (MS_BUS_RIU_ADDR + (0x100910 << 1)), 0x0000 @//Set DTS/RTS to 1
    WREG        (MS_BUS_RIU_ADDR + (0x100904 << 1)), 0x0000 @//Disable Interrupt
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
@// BootRom_PLLRecovery
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_PLLRecovery
BootRom_PLLRecovery:

    WREG        (MS_BUS_RIU_ADDR + (0x101E26 << 1)), 0x0200     @//set ejtag padmux
    WREG        (MS_BUS_RIU_ADDR + (0x101882 << 1)), 0x0404     @//Set L3 switch to xtali
    WREG        (MS_BUS_RIU_ADDR + (0x110C72 << 1)), 0x0101     @//MIU_256BUS_PLL power down
    WREG        (MS_BUS_RIU_ADDR + (0x110C62 << 1)), 0x0101     @//MIU_128BUS_PLL power down
    
    bx          lr
@//-------------------------------------------------------------------------------------------------
@// BootRom_EnableMcuAccess
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_EnableMcuAccess
BootRom_EnableMcuAccess:

    ldr         r1, =(MS_BUS_RIU_ADDR + (0x002b00 << 1))
    ldr         r0, =0x0004
    str         r0, [r1, #(0xc4 << 1)]
    ldr         r0, =0x3c11
    str         r0, [r1, #(0xc6 << 1)]
    ldr         r0, =0x0010
    str         r0, [r1, #(0xc8 << 1)]
    ldr         r0, =0x403c
    str         r0, [r1, #(0xca << 1)]
    ldr         r0, =0x0101
    str         r0, [r1, #(0xcc << 1)]

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

#ifdef ENABLE_USB30_GPIO_PORT2
    WREG        (MS_BUS_RIU_ADDR + (REG_USB30_PORT2_GPIO_CONTROL << 1)), REG_USB30_PORT2_GPIO_BANK @//offset addr
    RREG        r0, (MS_BUS_RIU_ADDR + ((REG_USB30_PORT2_GPIO_CONTROL + 2) << 1))
    ldr         r1, =0x1FFF                             @//[bit 13:15] other usage
    bic         r0, r0, r1
    add         r0, r0, #(REG_USB30_PORT2_GPIO_BIT << 8) @//bit8~bit10 bit count
    add         r0, r0, #(REG_USB30_PORT2_GPIO_OFFSET) @//bit0~bit7 offset addr
    add         r0, r0, #(REG_USB30_PORT2_GPIO_LOW_ACTIVE<<11) @// Turn on 5V  ( 0:  GPIO High   1: GPIO Low)    
    REG_C2M     r0, (MS_BUS_RIU_ADDR + ((REG_USB30_PORT2_GPIO_CONTROL + 2) << 1))
#endif

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
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x101e00 << 1))
    ldr         r0, [r1, #(0xa0 << 1)]
    bic         r0, r0, #0x8000
    str         r0, [r1, #(0xa0 << 1)]

#ifdef CONFIG_MSTAR_DVFS_ENABLE
    @//0x1005_0C[15:8]: Core Power (1.00V = 0x64)
    @//0x1005_0C[7:0]: CPU Power (1.10V = 0x6E)
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x100500 << 1))
    ldr         r0, =0x646E
    str         r0, [r1, #(0x0c << 1)]

#if defined(CONFIG_MSTAR_VID_CPU_POWER_UPPER_BOUND)
    ldr         r0, [r1, #(0x0c << 1)]
    bic         r0, r0, #0xFF
    ldr         r2, =CONFIG_MSTAR_VID_CPU_POWER_UPPER_BOUND
    and         r2, r2, #0xFF
    orr         r0, r0, r2
    str         r0, [r1, #(0x0c << 1)]
#endif
#endif

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

    @//Get OSC Value (Bank1[11:2] = 0x00200C[11:2]
    RREG        r2, REG_EFUSE_BANK1_LOW                 @//Bank1[11:2] = 0x00200C[11:2]
    ldr         r0, =0x0ffc
    and         r2, r2, r0
    mov         r2, r2, lsr #2                          @//Right Shift 2-bit Data to Get OSC Value

    ldr         r0, =0x00
    cmp         r2, r0
    beq         BootRom_InitVid_Exit                    @//If no OSC existed in eFuse, bypass VID flow

    ldr         r7, =CONFIG_MSTAR_VID_CPU_POWER_UPPER_BOUND
    ldr         r0, =CONFIG_OSC_THRESHOLD_CPU_L0
    cmp         r2, r0
    bls         BootRom_InitVid_SetCpuVoltage           @//If OSC <= The Value of Threshold 0, Set Corresponding Voltage 0

    ldr         r0, =CONFIG_SIDD_THRESHOLD_CPU_L0
    cmp         r1, r0
    bls         BootRom_InitVid_SetCpuVoltage           @//If SIDD <= The Value of Threshold 0, Set Corresponding Voltage 0

    ldr         r7, =CONFIG_MSTAR_VID_CPU_POWER_LOWER_BOUND
    ldr         r0, =CONFIG_OSC_THRESHOLD_CPU_L1
    cmp         r2, r0
    bls         BootRom_InitVid_SetCpuVoltage           @//If OSC < The Value of Threshold 1, Set Corresponding Voltage 1

    ldr         r0, =CONFIG_SIDD_THRESHOLD_CPU_L1
    cmp         r1, r0
    bls         BootRom_InitVid_SetCpuVoltage           @//If SIDD < The Value of Threshold 1, Set Corresponding Voltage 1

    ldr         r7, =CONFIG_MSTAR_VID_CPU_POWER_UPPER_BOUND

BootRom_InitVid_SetCpuVoltage:

#ifdef CONFIG_MSTAR_DVFS_ENABLE
    @//0x1005_0C[15:8]: Core Power (1.00V = 0x64)
    @//0x1005_0C[7:0]: CPU Power (1.10V = 0x6E)
    ldr         r3, =(MS_BUS_RIU_ADDR + (0x100500 << 1))

#if defined(CONFIG_MSTAR_VID_CPU_POWER_UPPER_BOUND)
    ldr         r0, [r3, #(0x0c << 1)]
    ldr         r4, =0x00FF
    bic         r0, r0, r4
    and         r7, r7, r4
    orr         r0, r0, r7
    str         r0, [r3, #(0x0c << 1)]
#endif
#endif

    ldr         r8, =CONFIG_MSTAR_VID_CORE_POWER_UPPER_BOUND
    ldr         r0, =CONFIG_OSC_THRESHOLD_CORE_L0
    cmp         r2, r0
    bls         BootRom_InitVid_SetCoreVoltage          @//If OSC <= The Value of Threshold 0, Set Corresponding Voltage 0

    ldr         r0, =CONFIG_SIDD_THRESHOLD_CORE_L0
    cmp         r1, r0
    bls         BootRom_InitVid_SetCoreVoltage          @//If SIDD <= The Value of Threshold 0, Set Corresponding Voltage 0

    ldr         r8, =CONFIG_MSTAR_VID_CORE_POWER_LOWER_BOUND
    ldr         r0, =CONFIG_OSC_THRESHOLD_CORE_L1
    cmp         r2, r0
    bls         BootRom_InitVid_SetCoreVoltage          @//If OSC < The Value of Threshold 1, Set Corresponding Voltage 1

    ldr         r0, =CONFIG_SIDD_THRESHOLD_CORE_L1
    cmp         r1, r0
    bls         BootRom_InitVid_SetCoreVoltage          @//If SIDD < The Value of Threshold 1, Set Corresponding Voltage 1

    ldr         r8, =CONFIG_MSTAR_VID_CORE_POWER_UPPER_BOUND

BootRom_InitVid_SetCoreVoltage:

#ifdef CONFIG_MSTAR_DVFS_ENABLE
    @//0x1005_0C[15:8]: Core Power (1.00V = 0x64)
    @//0x1005_0C[7:0]: CPU Power (1.10V = 0x6E)
    ldr         r3, =(MS_BUS_RIU_ADDR + (0x100500 << 1))

#if defined(CONFIG_MSTAR_VID_CORE_POWER_UPPER_BOUND)
    ldr         r0, [r3, #(0x0c << 1)]
    ldr         r4, =0xFF00
    bic         r0, r0, r4
    and         r8, r8, #0xFF
    mov         r8, r8, lsl #8
    orr         r0, r0, r8
    str         r0, [r3, #(0x0c << 1)]
#endif
#endif

    ldr         r3, =(MS_BUS_RIU_ADDR + (0x110c00 << 1))
    ldr         r0, =0x1310
    str         r0, [r3, #(0xb2 << 1)]

    ldr         r3, =(MS_BUS_RIU_ADDR + (0x000e00 << 1))
    str         r0, [r3, #(0x38 << 1)]
    ldr         r4, =(0x01 << 10)
    bic         r0, r0, r4
    str         r0, [r3, #(0x38 << 1)]

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

    ldr         r1, =(MS_BUS_RIU_ADDR + (0x100500 << 1))
    ldr         r0, =0x3697
    str         r0, [r1, #(0x00 << 1)]                          @//The switch of DVFS flow

    ldr         r0, =CPU_CLOCK
    str         r0, [r1, #(0x02 << 1)]                          @//Current CPU Clock

    ldr         r0, =0x00
    str         r0, [r1, #(0x04 << 1)]                          @//Current Temperature (CPU)
    str         r0, [r1, #(0x06 << 1)]                          @//Current Temperature (PM)

    ldr         r2, =CONFIG_MSTAR_DVFS_TEMPERATURE_UPPER_BOUND  @//Upper Bound of T-sensor
    mov         r2, r2, lsl #8
    ldr         r3, =CONFIG_MSTAR_DVFS_TEMPERATURE_LOWER_BOUND  @//Lower Bound of T-sensor
    orr         r2, r2, r3
    str         r2, [r1, #(0x08 << 1)]

#ifndef CONFIG_MSTAR_VID_VOLTAGE_SHIFT_ENABLE
    ldr         r2, =CONFIG_MSTAR_DVFS_TEMPERATURE_THRESHOLD    @//Upper Bound of Global Reset
    str         r2, [r1, #(0x0a << 1)]
#else
    ldr         r2, =CONFIG_MSTAR_VID_CPU_POWER_STEP_VALUE
    mov         r2, r2, lsl #12
    ldr         r3, =CONFIG_MSTAR_VID_CORE_POWER_STEP_VALUE
    mov         r3, r3, lsl #8
    orr         r2, r2, r3
    ldr         r3, =CONFIG_MSTAR_DVFS_TEMPERATURE_THRESHOLD    @//Upper Bound of Global Reset
    orr         r2, r2, r3
    str         r2, [r1, #(0x0a << 1)]
#endif

    ldr         r0, =0x2454
    str         r0, [r1, #(0x0e << 1)]                          @//Dynamic Clock Adjustment in Command Line

    ldr         r1, =(MS_BUS_RIU_ADDR + (0x110c00 << 1))
    ldr         r0, =(CONFIG_DVFS_CPU_CLOCK_MIN & 0xFFFF)
    str         r0, [r1, #(0xa0 << 1)] 
    ldr         r0, =((CONFIG_DVFS_CPU_CLOCK_MIN >> 16) & 0xFFFF)
    str         r0, [r1, #(0xa2 << 1)] 

    ldr         r0, =(CONFIG_DVFS_CPU_CLOCK_MAX & 0xFFFF)
    str         r0, [r1, #(0xa4 << 1)] 
    ldr         r0, =((CONFIG_DVFS_CPU_CLOCK_MAX >> 16) & 0xFFFF)
    str         r0, [r1, #(0xa6 << 1)] 

    @//Get Trim Value of T_Sensor in eFuse
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x002000 << 1))
    ldr         r0, =0x0144
    str         r0, [r1, #(0x50 << 1)]
    ldr         r0, =(0x0001 << 13)
    str         r0, [r1, #(0x50 << 1)] 
BootRom_ReadEfuseLoop:
    ldr         r0, [r1, #(0x50 << 1)]
    and         r0, r0, #(0x0001 << 13)
    cmp         r0, #0
    bne         BootRom_ReadEfuseLoop

    ldr         r0, [r1, #(0x58 << 1)]
    and         r0, r0, #0x003f
    mov         r0, r0, lsl #1

    ldr         r1, =(MS_BUS_RIU_ADDR + (0x000e00 << 1))
    str         r0, [r1, #(0xc8 << 1)]
    ldr         r2, =0x0401
    orr         r0, r0, r2
    str         r0, [r1, #(0xc8 << 1)]

    ldr         r0, [r1, #(0x5e << 1)]
    orr         r0, r0, #0x04
    str         r0, [r1, #(0x5e << 1)]

    ldr         r0, [r1, #(0xc6 << 1)]
    orr         r0, r0, #0x01
    str         r0, [r1, #(0xc6 << 1)]

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

    ldr         r1, =(MS_BUS_RIU_ADDR + (0x003000 << 1))
    ldr         r0, =0xffff
    str         r0, [r1, #(0x24 << 1)]
    ldr         r0, =0xffff
    str         r0, [r1, #(0x26 << 1)]
    ldr         r0, =0xffff
    str         r0, [r1, #(0x44 << 1)]
    ldr         r0, =0xffff
    str         r0, [r1, #(0x46 << 1)]
    ldr         r0, =0x0000
    str         r0, [r1, #(0x20 << 1)]
    ldr         r0, =0x0001
    str         r0, [r1, #(0x20 << 1)]
    ldr         r0, =0x0000
    str         r0, [r1, #(0x40 << 1)]
    ldr         r0, =0x0001
    str         r0, [r1, #(0x40 << 1)]

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
    ldr         r11, =0x0138
    str         r11, [r12, #(0x50 << 1)]                    @//Set bank to read efuse

    ldr         r11, =0x2138
    str         r11, [r12, #(0x50 << 1)]                    @//Launch efuse read

BootRom_InitMhlCbusTrimmingControlLoop:
    ldr         r11, [r12, #(0x50 << 1)]                    @//Polling efuse read down
    ldr         r1, =0x2000
    and         r11, r11, r1
    cmp         r11, #0
    bne         BootRom_InitMhlCbusTrimmingControlLoop

    ldr         r11, [r12, #(0x5a << 1)]                    @//Get efuse data

    mov         r0, r11, lsr #8

    and         r1, r0, #0x40                               @//Check efuse data is valid
    cmp         r1, #0
    beq         BootRom_InitMhlCbusTrimmingControlExit

    mov         r0, r11, lsl #2
    ldr         r1, =0xF000
    and         r0, r0, r1

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x151000 << 1))
    ldr         r11, [r12, #(0xd6 << 1)]  
    orr         r11, r11, r0
    str         r11, [r12, #(0xd6 << 1)]
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x151200 << 1))
    ldr         r11, [r12, #(0xd6 << 1)]  
    orr         r11, r11, r0
    str         r11, [r12, #(0xd6 << 1)]
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x151400 << 1))
    ldr         r11, [r12, #(0xd6 << 1)]  
    orr         r11, r11, r0
    str         r11, [r12, #(0xd6 << 1)]
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x151600 << 1))
    ldr         r11, [r12, #(0xd6 << 1)]  
    orr         r11, r11, r0
    str         r11, [r12, #(0xd6 << 1)]

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
