/*
 *#############################################################################
 *
 * Copyright (c) 2006-2015 MStar Semiconductor, Inc.
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

//================================================================================================
    //Initial related settings of UART
    bl          BootRom_InitUart

//================================================================================================
    //Enable 8051 to access MIU for MStar TV Tool
    bl          BootRom_EnableMcuAccess

//================================================================================================
    //Initial related settings of RIU
    bl          BootRom_InitRiu

    //Initial MOD Trimming Control Setting
    bl          BootRom_InitModTrimmingControl

    //Initial MHL CBus Trimming Control Setting
    bl          BootRom_InitMhlCbusTrimmingControl

    //Initial EMAC Trimming Control Setting
    bl          BootRom_InitEmacTrimmingControl

#ifdef CONFIG_MSTAR_EDINBURGH
    bl          BootRom_InitExtDemod_Edinburgh
#endif

#ifdef CONFIG_MSTAR_CASHMERE
    bl          BootRom_InitExtDemod_Cashmere
#endif

#if !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)

    //checkpoint for autotest boottime, plz dont remove it
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

    ret         x29

//-------------------------------------------------------------------------------------------------
// BootRom_InitRiu
// @param
// @return None
// @note
//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitRiu
BootRom_InitRiu:

    //Enable 32-bit RIU Write Data
    RREG        w3, (MS_BUS_RIU_ADDR + (0x101882 << 1))
    ldr         w4, =0x00008000
    orr         w3, w3, w4
    REG_C2M     w3, (MS_BUS_RIU_ADDR + (0x101882 << 1))

#ifdef CONFIG_MSTAR_32BIT_RIU_MASK_ENABLE
    RREG        w3, (MS_BUS_RIU_ADDR + (0x10012E << 1))
    ldr         w4, =0x00000001
    orr         w3, w3, w4
    REG_C2M     w3, (MS_BUS_RIU_ADDR + (0x10012E << 1))

    RREG        w3, (MS_BUS_RIU_ADDR + (0x101882 << 1))
    ldr         w4, =0x00008000
    orr         w3, w3, w4
    REG_C2M     w3, (MS_BUS_RIU_ADDR + (0x101882 << 1))

    RREG        w3, (MS_BUS_RIU_ADDR + (0x00012E << 1))
    ldr         w4, =0x00000001
    orr         w3, w3, w4
    REG_C2M     w3, (MS_BUS_RIU_ADDR + (0x00012E << 1))
#endif

    ret

//-------------------------------------------------------------------------------------------------
// BootRom_InitUart
// @param
// @return None
// @note
//-------------------------------------------------------------------------------------------------
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
    RREG        w0, (MS_BUS_RIU_ADDR + (0x000E12 << 1))     //Enable UART Rx via PAD_DDCA for dig_mux
    orr         w0, w0, #0x0800
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x000E12 << 1))

    RREG        w0, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))     //Select UART0 source to PIU UART0
    orr         w0, w0, #0x0004
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))

    RREG        w0, (MS_BUS_RIU_ADDR + (0x10098C << 1))     //Enable Divisor Latch Access
    orr         w0, w0, #0x0080
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x10098C << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x100980 << 1)), UART_DIVISOR_L   //Set Divisor Latch LSB
    WREG        (MS_BUS_RIU_ADDR + (0x100984 << 1)), UART_DIVISOR_H   //Set Divisor Latch MSB

    RREG        w0, (MS_BUS_RIU_ADDR + (0x10098C << 1))     //Disable Divisor Latch Access
    ldr         w1, =0xFF7F
    and         w0, w0, w1
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x10098C << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x100988 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x100988 << 1)), 0x0007 //Enable FIFO and Clear TX/RX FIFO

    WREG        (MS_BUS_RIU_ADDR + (0x10098C << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x10098C << 1)), 0x0003 //8-bit Data / 1-bit Stop / No Parity Bit
    WREG        (MS_BUS_RIU_ADDR + (0x100990 << 1)), 0x0000 //Set DTS/RTS to 1
    WREG        (MS_BUS_RIU_ADDR + (0x100984 << 1)), 0x0000 //Disable Interrupt
.endif

.if (BOOTINFO_UART2_ENABLE == 1)
//  RREG        w0, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))     //Select UART2 source to PIU UART0
//  orr         w0, w0, #0x0400
//  REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))

    RREG        w0, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))     //Select UART2 source to PIU UART1
    ldr         w0, =0x0550
    orr         w0, w0, w1
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x101EA6 << 1))

    RREG        w0, (MS_BUS_RIU_ADDR + (0x11060C << 1))     //Enable Divisor Latch Access
    orr         w0, w0, #0x0080
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x11060C << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x110600 << 1)), UART_DIVISOR_L   //Set Divisor Latch LSB
    WREG        (MS_BUS_RIU_ADDR + (0x110604 << 1)), UART_DIVISOR_H   //Set Divisor Latch MSB

    RREG        w0, (MS_BUS_RIU_ADDR + (0x11060C << 1))     //Disable Divisor Latch Access
    ldr         w1, =0xFF7F
    and         w0, w0, w1
    REG_C2M     w1, (MS_BUS_RIU_ADDR + (0x11060C << 1))

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

//-------------------------------------------------------------------------------------------------
// BootRom_EnableMcuAccess
// @param
// @return None
// @note
//-------------------------------------------------------------------------------------------------
    .global     BootRom_EnableMcuAccess
BootRom_EnableMcuAccess:

    ldr         x1, =(MS_BUS_RIU_ADDR + (0x002b00 << 1))
    ldr         w0, =0x0004
    str         w0, [x1, #(0xc4 << 1)]
    ldr         w0, =0x3c11
    str         w0, [x1, #(0xc6 << 1)]
    ldr         w0, =0x0010
    str         w0, [x1, #(0xc8 << 1)]
    ldr         w0, =0x403c
    str         w0, [x1, #(0xca << 1)]
    ldr         w0, =0x0101
    str         w0, [x1, #(0xcc << 1)]

    ret

#ifdef REG_USB30_GPIO_CONTROL
//-------------------------------------------------------------------------------------------------
// BootRom_InitUsb30Gpio
// @param
// @return None
// @note
//-------------------------------------------------------------------------------------------------
BootRom_InitUsb30Gpio:

    WREG        (MS_BUS_RIU_ADDR + (REG_USB30_GPIO_CONTROL << 1)), REG_USB30_GPIO_BANK  //offset addr
    RREG        w0, (MS_BUS_RIU_ADDR + ((REG_USB30_GPIO_CONTROL + 2) << 1))
    ldr         w1, =0x1FFF                                 //[bit 13:15] other usage
    bic         w0, w0, w1
    add         w0, w0, #(REG_USB30_GPIO_BIT << 8)          //bit8~bit10 bit count
    add         w0, w0, #(REG_USB30_GPIO_OFFSET)            //bit0~bit7 offset addr
    add         w0, w0, #(REG_USB30_GPIO_LOW_ACTIVE << 11)  //Turn on 5V (0: GPIO High Active / 1: GPIO Low Active)
    REG_C2M     w0, (MS_BUS_RIU_ADDR + ((REG_USB30_GPIO_CONTROL + 2) << 1))

    ret

#endif

#ifdef CONFIG_MSTAR_EDINBURGH
//-------------------------------------------------------------------------------------------------
// BootRom_InitExtDemod_Edinburgh
// @param
// @return None
// @note
//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitExtDemod_Edinburgh
BootRom_InitExtDemod_Edinburgh:

    WREG_B      (MS_BUS_RIU_ADDR + (0x000e60 << 1) + 1), 0x00

    RREG        w0, (MS_BUS_RIU_ADDR + (0x101eae << 1))
    bic         w0, w0, #(0x01 << 2)
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x101eae << 1))

    WREG_B      (MS_BUS_RIU_ADDR + (0x112002 << 1) + 1), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x11280e << 1)), 0x10
    WREG_B      (MS_BUS_RIU_ADDR + (0x11286a << 1) + 1), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x11287a << 1)), 0x01
    WREG_B      (MS_BUS_RIU_ADDR + (0x112878 << 1) + 1), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x112802 << 1)), 0x0C
    WREG_B      (MS_BUS_RIU_ADDR + (0x112802 << 1) + 1), 0x00

    ret

#endif

#ifdef CONFIG_MSTAR_CASHMERE
//-------------------------------------------------------------------------------------------------
// BootRom_InitExtDemod_Cashmere
// @param
// @return None
// @note
//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitExtDemod_Cashmere
BootRom_InitExtDemod_Cashmere:

    ldr         x12, =(MS_BUS_RIU_ADDR + (0x112000 << 1))
    ldr         w3, [x12, #(0x02 << 1)]
    bic         w3, w3, #(0x03 << 13)
    str         w3, [x12, #(0x02 << 1)]

    ldr         x12, =(MS_BUS_RIU_ADDR + (0x112800 << 1))
    ldr         w3, [x12, #(0x40 << 1)]
    bic         w3, w3, #(0x01 << 4)
    str         w3, [x12, #(0x40 << 1)]

    ldr         w3, [x12, #(0x7a << 1)]
    orr         w3, w3, #(0x01 << 0)
    str         w3, [x12, #(0x7a << 1)]

    ret
#endif

#ifdef CONFIG_MSTAR_VID_ENABLE
//-------------------------------------------------------------------------------------------------
// BootRom_InitVid
// @param  None
// @return None
// @note None
//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitVid
BootRom_InitVid:

    //Disable All-Pad-In
    RREG        w0, (MS_BUS_RIU_ADDR + (0x101EA0 << 1))
    bic         w0, w0, #0x8000
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x101EA0 << 1))

#ifdef CONFIG_MSTAR_DVFS_ENABLE
#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
    //0x1005_0C[15:12]: Current Port (2)
    //0x1005_0C[11:8]: Maximum Port (3)
    //0x1005_0C[7:0]: Reserved
    ldr         w0, =0x23FF
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x10050c << 1))
#else
    //0x1005_0C[15:8]: Core Power (1.15V = 0x73)
    //0x1005_0C[7:0]: CPU Power (1.15V = 0x73)
    ldr         w0, =0x7373
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x10050c << 1))
#endif
#endif

#if ((CONFIG_VID_USE_SIDD == 1) || (CONFIG_VID_USE_SIDD == 2))
    //Get SIDD Value (Bank1[21:12] = 0x00200E[5:0] + 0x00200C[15:12]
    RREG        w0, REG_EFUSE_BANK1_HIGH
    RREG        w1, REG_EFUSE_BANK1_LOW                 //Bank1[21:12] = 0x00200E[5:0] + 0x00200C[15:12]

    and         w0, w0, #0x003f
    lsl         w0, w0, #4                              //Left-shift 4-bit Data to Reserved for Lower SIDD Value

    and         w1, w1, #0xf000
    lsr         w1, w1, #12                             //Right-shift 12-bit Data to Sync the Order of SIDD Value

    orr         w1, w1, w0                              //Combine to Complete SIDD Value

    ldr         w0, =0x00
    cmp         w1, w0
    b.eq        BootRom_InitVid_Exit                    //If no SIDD existed in eFuse, bypass VID flow
#endif

#if ((CONFIG_VID_USE_SIDD == 0) || (CONFIG_VID_USE_SIDD == 2))
    //Get OSC Value (Bank1[11:2] = 0x00200C[11:2]
    RREG        w2, REG_EFUSE_BANK1_LOW                 //Bank1[11:2] = 0x00200C[11:2]
    ldr         w0, =0x0ffc
    and         w2, w2, w0
    lsr         w2, w2, #2                              //Right Shift 2-bit Data to Get OSC Value

    ldr         w0, =0x00
    cmp         w2, w0
    b.eq        BootRom_InitVid_Exit                    //If no OSC existed in eFuse, bypass VID flow
#endif

#if ((CONFIG_VID_USE_SIDD == 0) || (CONFIG_VID_USE_SIDD == 2))
    ldr         w0, =CONFIG_OSC_THRESHOLD_0
    cmp         w2, w0
    b.lt        BootRom_InitVid_SetVoltage_0            //If OSC < The Value of Threshold 0, Set Corresponding Voltage 0
#endif

#if ((CONFIG_VID_USE_SIDD == 1) || (CONFIG_VID_USE_SIDD == 2))
    ldr         w0, =CONFIG_SIDD_THRESHOLD_0
    cmp         w1, w0
    b.lt        BootRom_InitVid_SetVoltage_0            //If SIDD < The Value of Threshold 0, Set Corresponding Voltage 0
#endif

#if ((CONFIG_VID_USE_SIDD == 0) || (CONFIG_VID_USE_SIDD == 2))
    ldr         w0, =CONFIG_OSC_THRESHOLD_1
    cmp         w2, w0
    b.lt        BootRom_InitVid_SetVoltage_1            //If OSC < The Value of Threshold 1, Set Corresponding Voltage 1
#endif

#if ((CONFIG_VID_USE_SIDD == 1) || (CONFIG_VID_USE_SIDD == 2))
    ldr         w0, =CONFIG_SIDD_THRESHOLD_1
    cmp         w1, w0
    b.lt        BootRom_InitVid_SetVoltage_1            //If SIDD < The Value of Threshold 1, Set Corresponding Voltage 1
#endif

#if ((CONFIG_VID_USE_SIDD == 0) || (CONFIG_VID_USE_SIDD == 2))
    ldr         w0, =CONFIG_OSC_THRESHOLD_2
    cmp         w2, w0
    b.lt        BootRom_InitVid_SetVoltage_2            //If OSC < The Value of Threshold 2, Set Corresponding Voltage 2
#endif

#if ((CONFIG_VID_USE_SIDD == 1) || (CONFIG_VID_USE_SIDD == 2))
    ldr         w0, =CONFIG_SIDD_THRESHOLD_2
    cmp         w1, w0
    b.lt        BootRom_InitVid_SetVoltage_2            //If SIDD < The Value of Threshold 2, Set Corresponding Voltage 2
#endif

    b           BootRom_InitVid_SetVoltage_3            //If SIDD / OSC >= The Value of Threshold 2, Set Corresponding Voltage 3

BootRom_InitVid_SetVoltage_0:

#ifdef CONFIG_MSTAR_DVFS_ENABLE
#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
    //0x1005_0C[15:12]: Current Port (2)
    //0x1005_0C[11:8]: Maximum Port (3)
    //0x1005_0C[7:0]: Reserved
    ldr         w0, =0x23FF
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x10050c << 1))
#else
    //0x1005_0C[15:8]: Core Power (1.15V = 0x73)
    //0x1005_0C[7:0]: CPU Power (1.15V = 0x73)
#if defined(CONFIG_MSTAR_VID_CPU_POWER_UPPER_BOUND) && defined(CONFIG_MSTAR_VID_CORE_POWER_UPPER_BOUND)
    ldr         w0, =CONFIG_MSTAR_VID_CORE_POWER_UPPER_BOUND
    lsl         w0, w0, #8
    orr         w0, w0, #CONFIG_MSTAR_VID_CPU_POWER_UPPER_BOUND
#else
    ldr         w0, =0x7373
#endif
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x10050c << 1))
#endif
#endif

#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
#if (CONFIG_ENABLE_VID0 != 0)
    //Set GPIO to Switch Corresponding Voltage (Case 0: 1.28V)
    RREG        w0, REG_VID0_GPIO_CONTROL
    bic         w0, w0, #REG_VID0_GPIO_MASK
    REG_C2M     w0, REG_VID0_GPIO_CONTROL               //VID0: Low
#endif

#if (CONFIG_ENABLE_VID1 != 0)
    RREG        w0, REG_VID1_GPIO_CONTROL
    orr         w0, w0, #REG_VID1_GPIO_MASK
    REG_C2M     w0, REG_VID1_GPIO_CONTROL               //VID1: High
#endif
#endif

    b           BootRom_InitVid_Exit

BootRom_InitVid_SetVoltage_1:

#ifdef CONFIG_MSTAR_DVFS_ENABLE
#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
    //0x1005_0C[15:12]: Current Port (1)
    //0x1005_0C[11:8]: Maximum Port (3)
    //0x1005_0C[7:0]: Reserved
    ldr         w0, =0x13FF
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x10050c << 1))
#else
    //0x1005_0C[15:8]: Core Power (1.13V = 0x71)
    //0x1005_0C[7:0]: CPU Power (1.15V = 0x73)
#if defined(CONFIG_MSTAR_VID_CPU_POWER_LOWER_BOUND) && defined(CONFIG_MSTAR_VID_CORE_POWER_LOWER_BOUND)
    ldr         w0, =CONFIG_MSTAR_VID_CORE_POWER_LOWER_BOUND
    lsl         w0, w0, #8
    orr         w0, w0, #CONFIG_MSTAR_VID_CPU_POWER_LOWER_BOUND
#else
    ldr         w0, =0x7173
#endif
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x10050c << 1))
#endif
#endif

#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
#if (CONFIG_ENABLE_VID0 != 0)
    //Set GPIO to Switch Corresponding Voltage (Case 1: 1.20V)
    RREG        w0, REG_VID0_GPIO_CONTROL
    orr         w0, w0, #REG_VID0_GPIO_MASK
    REG_C2M     w0, REG_VID0_GPIO_CONTROL               //VID0: High
#endif

#if (CONFIG_ENABLE_VID1 != 0)
    RREG        w0, REG_VID1_GPIO_CONTROL
    bic         w0, w0, #REG_VID1_GPIO_MASK
    REG_C2M     w0, REG_VID1_GPIO_CONTROL               //VID1: Low
#endif
#endif

    b           BootRom_InitVid_Exit

BootRom_InitVid_SetVoltage_2:

#ifdef CONFIG_MSTAR_DVFS_ENABLE
#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
    //0x1005_0C[15:12]: Current Port (2)
    //0x1005_0C[11:8]: Maximum Port (3)
    //0x1005_0C[7:0]: Reserved
    ldr         w0, =0x03FF
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x10050c << 1))
#else
    //0x1005_0C[15:8]: Max Voltage (Reserved)
    //0x1005_0C[7:0]: Current Voltage (Reserved)
    ldr         w0, =0xFFFF
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x10050c << 1))
#endif
#endif

#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
#if (CONFIG_ENABLE_VID0 != 0)
    //Set GPIO to Switch Corresponding Voltage (Case 2: Reserved)
    RREG        w0, REG_VID0_GPIO_CONTROL
    bic         w0, w0, #REG_VID0_GPIO_MASK
    REG_C2M     w0, REG_VID0_GPIO_CONTROL               //VID0: Low
#endif

#if (CONFIG_ENABLE_VID1 != 0)
    RREG        w0, REG_VID1_GPIO_CONTROL
    bic         w0, w0, #REG_VID1_GPIO_MASK
    REG_C2M     w0, REG_VID1_GPIO_CONTROL               //VID1: Low
#endif
#endif

    b           BootRom_InitVid_Exit

BootRom_InitVid_SetVoltage_3:

#ifdef CONFIG_MSTAR_DVFS_ENABLE
#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
    //0x1005_0C[15:12]: Current Port (3)
    //0x1005_0C[11:8]: Maximum Port (3)
    //0x1005_0C[7:0]: Reserved
    ldr         w0, =0x33FF
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x10050c << 1))
#else
    //0x1005_0C[15:8]: Max Voltage (Reserved)
    //0x1005_0C[7:0]: Current Voltage (Reserved)
    ldr         w0, =0xFFFF
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x10050c << 1))
#endif
#endif

#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
#if (CONFIG_ENABLE_VID0 != 0)
    //Set GPIO to Switch Corresponding Voltage (Case 3: Reserved)
    RREG        w0, REG_VID0_GPIO_CONTROL
    orr         w0, w0, #REG_VID0_GPIO_MASK
    REG_C2M     w0, REG_VID0_GPIO_CONTROL               //VID0: High
#endif

#if (CONFIG_ENABLE_VID1 != 0)
    RREG        w0, REG_VID1_GPIO_CONTROL
    orr         w0, w0, #REG_VID1_GPIO_MASK
    REG_C2M     w0, REG_VID1_GPIO_CONTROL               //VID1: High
#endif
#endif

BootRom_InitVid_Exit:

    ret
#endif

#ifdef CONFIG_MSTAR_DVFS_ENABLE
//-------------------------------------------------------------------------------------------------
// BootRom_InitDvfs
// @param
// @return None
// @note
//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitDvfs
BootRom_InitDvfs:

    WREG        (MS_BUS_RIU_ADDR + (0x100500 << 1)), 0x3697     //The switch of DVFS flow
    WREG        (MS_BUS_RIU_ADDR + (0x100502 << 1)), CPU_CLOCK  //Current CPU Clock
    WREG        (MS_BUS_RIU_ADDR + (0x100504 << 1)), 0          //Current Temperature (CPU)
    WREG        (MS_BUS_RIU_ADDR + (0x100506 << 1)), 0          //Current Temperature (PM)

    ldr         w0, =CONFIG_MSTAR_DVFS_TEMPERATURE_UPPER_BOUND  //Upper Bound of T-sensor
    lsl         w0, w0, #8
    ldr         w1, =CONFIG_MSTAR_DVFS_TEMPERATURE_LOWER_BOUND  //Lower Bound of T-sensor
    orr         w0, w0, w1
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x100508 << 1))

#ifndef CONFIG_MSTAR_VID_VOLTAGE_SHIFT_ENABLE
    ldr         w0, =CONFIG_MSTAR_DVFS_TEMPERATURE_THRESHOLD    //Upper Bound of Global Reset
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x10050a << 1))
#else
    ldr         w0, =CONFIG_MSTAR_VID_CPU_POWER_STEP_VALUE
    lsl         w0, w0, #12
    ldr         w1, =CONFIG_MSTAR_VID_CORE_POWER_STEP_VALUE
    lsl         w1, w1, #8
    orr         w0, w0, w1
    ldr         w1, =CONFIG_MSTAR_DVFS_TEMPERATURE_THRESHOLD    //Upper Bound of Global Reset
    orr         w0, w0, w1
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x10050a << 1))
#endif

    WREG        (MS_BUS_RIU_ADDR + (0x10050e << 1)), 0x2454     //Dynamic Clock Adjustment in Command Line

    WREG        (MS_BUS_RIU_ADDR + (0x110ca0 << 1)), (CONFIG_DVFS_CPU_CLOCK_MIN & 0xFFFF)
    WREG        (MS_BUS_RIU_ADDR + (0x110ca2 << 1)), ((CONFIG_DVFS_CPU_CLOCK_MIN >> 16) & 0xFFFF)

    WREG        (MS_BUS_RIU_ADDR + (0x110ca4 << 1)), (CONFIG_DVFS_CPU_CLOCK_MAX & 0xFFFF)
    WREG        (MS_BUS_RIU_ADDR + (0x110ca6 << 1)), ((CONFIG_DVFS_CPU_CLOCK_MAX >> 16) & 0xFFFF)

    //Get Trim Value of T_Sensor in eFuse
    WREG        (MS_BUS_RIU_ADDR + (0x002050 << 1)), 0x2144
BootRom_ReadEfuseLoop:
    RREG        w0, (MS_BUS_RIU_ADDR + (0x002050 << 1))
    and         w0, w0, #0x2000
    cmp         w0, #0
    b.ne        BootRom_ReadEfuseLoop

    RREG        w0, (MS_BUS_RIU_ADDR + (0x002058 << 1))
    and         w0, w0, #0x003f
    lsl         w0, w0, #10

    RREG        w1, (MS_BUS_RIU_ADDR + (0x000e50 << 1))
    and         w1, w1, #~(0x003f << 10)
    orr         w1, w1, w0
    REG_C2M     w1, (MS_BUS_RIU_ADDR + (0x000e50 << 1))

BootRom_InitDvfs_Exit:

    ret
#endif

#ifdef CONFIG_MSTAR_MOBF_ENABLE
//-------------------------------------------------------------------------------------------------
// BootRom_InitMobf
// @param
// @return None
// @note
//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitMobf
BootRom_InitMobf:

    WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0xC000  //enable dramobf

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

    ret
#endif

//-------------------------------------------------------------------------------------------------
// BootRom_InitTimer
// @param
// @return None
// @note
//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitTimer
BootRom_InitTimer:

    ldr         x1, =(MS_BUS_RIU_ADDR + (0x003000 << 1))
    ldr         w0, =0xffff
    strh        w0, [x1, #(0x24 << 1)]
    ldr         w0, =0xffff
    strh        w0, [x1, #(0x26 << 1)]
    ldr         w0, =0xffff
    strh        w0, [x1, #(0x44 << 1)]
    ldr         w0, =0xffff
    strh        w0, [x1, #(0x46 << 1)]
    ldr         w0, =0xffff
    strh        w0, [x1, #(0x20 << 1)]
    ldr         w0, =0xffff
    strh        w0, [x1, #(0x20 << 1)]
    ldr         w0, =0xffff
    strh        w0, [x1, #(0x40 << 1)]
    ldr         w0, =0xffff
    strh        w0, [x1, #(0x40 << 1)]

    ret

//-------------------------------------------------------------------------------------------------
// BootRom_InitMhlCbusTrimmingControl
// @param
// @return None
// @note
//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitMhlCbusTrimmingControl
BootRom_InitMhlCbusTrimmingControl:
#if 0
    ldr         x12, =(MS_BUS_RIU_ADDR + (0x2000 << 1))
    ldr         w11, =0x004f
    str         w11, [x12, #(0x4e << 1)]                    //Set bank to read efuse

    ldr         w11, =0x0001
    str         w11, [x12, #(0x4c << 1)]                    //Launch efuse read

BootRom_InitMhlCbusTrimmingControlLoop:
    ldr         w11, [x12, #(0x4c << 1)]                    //Polling efuse read down
    cmp         w11, #0
    b.ne        BootRom_InitMhlCbusTrimmingControlLoop

    ldr         w11, [x12, #(0x50 << 1)]                    //Get efuse data

    lsr         w0, w11, #8

    and         w1, w0, #0x04                               //Check efuse data is valid
    cmp         w1, #0
    b.eq        BootRom_InitMhlCbusTrimmingControlExit

    lsl         w0, w0, #3
    and         w0, w0, #(0x03 << 3)

    ldr         x12, =(MS_BUS_RIU_ADDR + (0x2f00 << 1))
    ldr         w11, [x12, #(0x62 << 1)]
    and         w11, w11, #~(0x03 << 3)
    orr         w11, w11, w0
    str         w11, [x12, #(0x62 << 1)]

BootRom_InitMhlCbusTrimmingControlExit:
#endif
    ret

//-------------------------------------------------------------------------------------------------
// BootRom_InitEmacTrimmingControl
// @param
// @return None
// @note
//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitEmacTrimmingControl
BootRom_InitEmacTrimmingControl:
#if 0
    ldr         x12, =(MS_BUS_RIU_ADDR + (0x2000 << 1))
    ldr         w11, =0x004d
    str         w11, [x12, #(0x4e << 1)]                    //Set bank to read efuse

    ldr         w11, =0x0001
    str         w11, [x12, #(0x4c << 1)]                    //Launch efuse read

BootRom_InitEmacTrimmingControlLoop:
    ldr         w11, [x12, #(0x4c << 1)]                    //Polling efuse read down
    cmp         w11, #0
    b.ne        BootRom_InitEmacTrimmingControlLoop

    ldr         w11, [x12, #(0x50 << 1)]                    //Get eFuse at Bank 0x4D[13:0]

    ldr         w1, =0x3FFF
    and         w0, w11, w1

    lsr         w1, w11, #14
    and         w1, w1, #0x03

    ldr         w11, [x12, #(0x52 << 1)]                    //Get eFuse at Bank 0x4D[17:14]

    and         w11, w11, #0x03
    lsl         w11, w11, #2
    orr         w1, w1, w11
    lsl         w1, w1, #8

    ldr         x12, =(MS_BUS_RIU_ADDR + (0x3400 << 1))
    ldr         w11, [x12, #(0x60 << 1)]
    and         w11, w11, #~(0x0f << 8)
    orr         w11, w11, w1
    orr         w11, w11, #(0x01 << 2)
    str         w11, [x12, #(0x60 << 1)]                    //0x0034_60[11:8] + 0x0034_60[2] = 1

    ldr         w11, [x12, #(0x68 << 1)]
    and         w11, w11, #0xC000
    orr         w11, w11, w0
    orr         w11, w11, #(0x01 << 15)
    str         w11, [x12, #(0x68 << 1)]                    //0x0034_68[13:0] + 0x0034_68[15] = 1

BootRom_InitEmacTrimmingControlExit:
#endif
    ret

//-------------------------------------------------------------------------------------------------
// BootRom_InitModTrimmingControl
// @param
// @return None
// @note
//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitModTrimmingControl
BootRom_InitModTrimmingControl:
#if 0
    ldr         x12, =(MS_BUS_RIU_ADDR + (0x2000 << 1))
    ldr         w11, =0x004f
    str         w11, [x12, #(0x4e << 1)]                    //Set bank to read efuse

    ldr         w11, =0x0001
    str         w11, [x12, #(0x4c << 1)]                    //Launch efuse read

BootRom_InitModTrimmingControlLoop:
    ldr         w11, [x12, #(0x4c << 1)]                    //Polling efuse read down
    cmp         w11, #0
    b.ne        BootRom_InitModTrimmingControlLoop

    ldr         w11, [x12, #(0x50 << 1)]                    //Get efuse data
    and         w0, w11, #(0x01 << 6)

    cmp         w0, #0
    b.eq        BootRom_InitModTrimmingControl_Disable

BootRom_InitModTrimmingControl_Enable:

    ldr         w11, [x12, #(0x50 << 1)]                    //Get efuse data
    and         w11, w11, #0x3f
    add         w11, w11, #3
    lsl         w0, w11, #8
    orr         w11, w11, w0

    ldr         x12, =(MS_BUS_RIU_ADDR + (0x103200 << 1))

    b           BootRom_InitModTrimmingControlExit

BootRom_InitModTrimmingControl_Disable:

    ldr         w11, =0x3f3f

BootRom_InitModTrimmingControlExit:

    ldr         x12, =(MS_BUS_RIU_ADDR + (0x103200 << 1))
    str         w11, [x12, #(0x54 << 1)]
    str         w11, [x12, #(0x56 << 1)]
    str         w11, [x12, #(0x58 << 1)]
#endif
    ret
