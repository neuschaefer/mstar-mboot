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
    mov         x29, x30

#//================================================================================================
    #//Initial related settings of UART
    bl          BootRom_InitUart

#//================================================================================================
    #//Enable 8051 to access MIU for MStar TV Tool
    bl          BootRom_EnableMcuAccess

#//================================================================================================
    #//Initial related settings of RIU
    bl          BootRom_InitRiu

    #//Initial MOD Trimming Control Setting
    bl          BootRom_InitModTrimmingControl

    #//Initial MHL CBus Trimming Control Setting
    bl          BootRom_InitMhlCbusTrimmingControl

    #//Initial EMAC Trimming Control Setting
    bl          BootRom_InitEmacTrimmingControl

#ifdef CONFIG_MSTAR_EDINBURGH
    bl          BootRom_InitExtDemod_Edinburgh
#endif

#ifdef CONFIG_MSTAR_CASHMERE
    bl          BootRom_InitExtDemod_Cashmere
#endif

#if !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)

    #//checkpoint for autotest boottime, plz dont remove it
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

    mov         x30, x29
    ret

#//-------------------------------------------------------------------------------------------------
#// BootRom_InitRiu
#// @param
#// @return None
#// @note
#//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitRiu
BootRom_InitRiu:

    #//Enable 32-bit RIU Write Data
    RREG        w7, (MS_BUS_RIU_ADDR + (0x101882 << 1))
    ldr         w8, =0x00008000
    orr         w7, w7, w8
    REG_C2M     w7, (MS_BUS_RIU_ADDR + (0x101882 << 1))

#ifdef CONFIG_MSTAR_32BIT_RIU_MASK_ENABLE
    RREG        w7, (MS_BUS_RIU_ADDR + (0x10012E << 1))
    ldr         w8, =0x00000001
    orr         w7, w7, w8
    REG_C2M     w7, (MS_BUS_RIU_ADDR + (0x10012E << 1))

    RREG        w7, (MS_BUS_RIU_ADDR + (0x101882 << 1))
    ldr         w8, =0x00008000
    orr         w7, w7, w8
    REG_C2M     w7, (MS_BUS_RIU_ADDR + (0x101882 << 1))

    RREG        w7, (MS_BUS_RIU_ADDR + (0x00012E << 1))
    ldr         w8, =0x00000001
    orr         w7, w7, w8
    REG_C2M     w7, (MS_BUS_RIU_ADDR + (0x00012E << 1))
#endif

    ret

#//-------------------------------------------------------------------------------------------------
#// BootRom_InitUart
#// @param
#// @return None
#// @note
#//-------------------------------------------------------------------------------------------------
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

    WREG        (MS_BUS_RIU_ADDR + (0x100B26 << 1)), 0x0C01 //Set CLK_UART0 to 123Mhz

    WREG        (MS_BUS_RIU_ADDR + (0x101EA6 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x101EA8 << 1)), 0x0100

.if (BOOTINFO_UART0_ENABLE == 1)
    RREG        w7, (MS_BUS_RIU_ADDR + (0x000E12 << 1))     //Enable UART Rx via PAD_DDCA for dig_mux
    orr         w7, w7, #0x0800
    REG_C2M     w7, (MS_BUS_RIU_ADDR + (0x000E12 << 1))

    RREG        w7, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))     //Select UART0 source to PIU UART0
    orr         w7, w7, #0x0004
    REG_C2M     w7, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))

    RREG        w7, (MS_BUS_RIU_ADDR + (0x10098C << 1))     //Enable Divisor Latch Access
    orr         w7, w7, #0x0080
    REG_C2M     w7, (MS_BUS_RIU_ADDR + (0x10098C << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x100980 << 1)), UART_DIVISOR_L   //Set Divisor Latch LSB
    WREG        (MS_BUS_RIU_ADDR + (0x100984 << 1)), UART_DIVISOR_H   //Set Divisor Latch MSB

    RREG        w7, (MS_BUS_RIU_ADDR + (0x10098C << 1))     //Disable Divisor Latch Access
    ldr         w8, =0xFF7F
    and         w7, w7, w8
    REG_C2M     w7, (MS_BUS_RIU_ADDR + (0x10098C << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x100988 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x100988 << 1)), 0x0007 //Enable FIFO and Clear TX/RX FIFO

    WREG        (MS_BUS_RIU_ADDR + (0x10098C << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x10098C << 1)), 0x0003 //8-bit Data / 1-bit Stop / No Parity Bit
    WREG        (MS_BUS_RIU_ADDR + (0x100990 << 1)), 0x0000 //Set DTS/RTS to 1
    WREG        (MS_BUS_RIU_ADDR + (0x100984 << 1)), 0x0000 //Disable Interrupt
.endif

.if (BOOTINFO_UART2_ENABLE == 1)
    RREG        w7, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))     //Select UART2 source to PIU UART1
    orr         w7, w7, #0x0550
    REG_C2M     w7, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))

    RREG        w7, (MS_BUS_RIU_ADDR + (0x11060C << 1))     //Enable Divisor Latch Access
    orr         w7, w7, #0x0080
    REG_C2M     w7, (MS_BUS_RIU_ADDR + (0x11060C << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x110600 << 1)), UART_DIVISOR_L   //Set Divisor Latch LSB
    WREG        (MS_BUS_RIU_ADDR + (0x110604 << 1)), UART_DIVISOR_H   //Set Divisor Latch MSB

    RREG        w7, (MS_BUS_RIU_ADDR + (0x11060C << 1))     //Disable Divisor Latch Access
    ldr         w8, =0xFF7F
    and         w7, w7, w8
    REG_C2M     w8, (MS_BUS_RIU_ADDR + (0x11060C << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x110608 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x110608 << 1)), 0x0007 //Enable FIFO and Clear TX/RX FIFO

    WREG        (MS_BUS_RIU_ADDR + (0x11060C << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x11060C << 1)), 0x0003 //8-bit Data / 1-bit Stop / No Parity Bit
    WREG        (MS_BUS_RIU_ADDR + (0x110610 << 1)), 0x0000 //Set DTS/RTS to 1
    WREG        (MS_BUS_RIU_ADDR + (0x110604 << 1)), 0x0000 //Disable Interrupt
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

    ret

#//-------------------------------------------------------------------------------------------------
#// BootRom_EnableMcuAccess
#// @param
#// @return None
#// @note
#//-------------------------------------------------------------------------------------------------
    .global     BootRom_EnableMcuAccess
BootRom_EnableMcuAccess:
    ldr         x8, =(MS_BUS_RIU_ADDR + (0x002b00 << 1))
    ldr         w7, =0x0004
    str         w7, [x8, #(0xc4 << 1)]
    ldr         w7, =0x3c11
    str         w7, [x8, #(0xc6 << 1)]
    ldr         w7, =0x0010
    str         w7, [x8, #(0xc8 << 1)]
    ldr         w7, =0x403c
    str         w7, [x8, #(0xca << 1)]
    ldr         w7, =0x0101
    str         w7, [x8, #(0xcc << 1)]

    ret

#ifdef REG_USB30_GPIO_CONTROL
#//-------------------------------------------------------------------------------------------------
#// BootRom_InitUsb30Gpio
#// @param
#// @return None
#// @note
#//-------------------------------------------------------------------------------------------------
BootRom_InitUsb30Gpio:

#endif

#ifdef CONFIG_MSTAR_EDINBURGH
#//-------------------------------------------------------------------------------------------------
#// BootRom_InitExtDemod_Edinburgh
#// @param
#// @return None
#// @note
#//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitExtDemod_Edinburgh
BootRom_InitExtDemod_Edinburgh:

#endif

#ifdef CONFIG_MSTAR_CASHMERE
#//-------------------------------------------------------------------------------------------------
#// BootRom_InitExtDemod_Cashmere
#// @param
#// @return None
#// @note
#//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitExtDemod_Cashmere
BootRom_InitExtDemod_Cashmere:

#endif

#ifdef CONFIG_MSTAR_VID_ENABLE
#//-------------------------------------------------------------------------------------------------
#// BootRom_InitVid
#// @param  None
#// @return None
#// @note None
#//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitVid
BootRom_InitVid:

#endif

#ifdef CONFIG_MSTAR_DVFS_ENABLE
#//-------------------------------------------------------------------------------------------------
#// BootRom_InitDvfs
#// @param
#// @return None
#// @note
#//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitDvfs
BootRom_InitDvfs:

#endif

#ifdef CONFIG_MSTAR_MOBF_ENABLE
#//-------------------------------------------------------------------------------------------------
#// BootRom_InitMobf
#// @param
#// @return None
#// @note
#//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitMobf
BootRom_InitMobf:

#endif

#//-------------------------------------------------------------------------------------------------
#// BootRom_InitTimer
#// @param
#// @return None
#// @note
#//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitTimer
BootRom_InitTimer:

    ldr         x28, =(MS_BUS_RIU_ADDR + (0x003000 << 1))
    ldr         w27, =0xffff
    strh        w27, [x28, #(0x24 << 1)]
    ldr         w27, =0xffff
    strh        w27, [x28, #(0x26 << 1)]
    ldr         w27, =0xffff
    strh        w27, [x28, #(0x44 << 1)]
    ldr         w27, =0xffff
    strh        w27, [x28, #(0x46 << 1)]
    ldr         w27, =0xffff
    strh        w27, [x28, #(0x20 << 1)]
    ldr         w27, =0xffff
    strh        w27, [x28, #(0x20 << 1)]
    ldr         w27, =0xffff
    strh        w27, [x28, #(0x40 << 1)]
    ldr         w27, =0xffff
    strh        w27, [x28, #(0x40 << 1)]

    ret

#//-------------------------------------------------------------------------------------------------
#// BootRom_InitMhlCbusTrimmingControl
#// @param
#// @return None
#// @note
#//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitMhlCbusTrimmingControl
BootRom_InitMhlCbusTrimmingControl:
    
    ret

#//-------------------------------------------------------------------------------------------------
#// BootRom_InitEmacTrimmingControl
#// @param
#// @return None
#// @note
#//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitEmacTrimmingControl
BootRom_InitEmacTrimmingControl:
    
    ret

#//-------------------------------------------------------------------------------------------------
#// BootRom_InitModTrimmingControl
#// @param
#// @return None
#// @note
#//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitModTrimmingControl
BootRom_InitModTrimmingControl:
    
    ret

