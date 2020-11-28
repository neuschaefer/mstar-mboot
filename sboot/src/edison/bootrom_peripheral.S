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
#ifndef _MACRO_INC_
#include "macro.inc"
#endif
#ifndef _DRV_UART_INC_
#include "drv_uart.inc"
#endif
#include "Board.h"
    .text
@//-------------------------------------------------------------------------------------------------
@// BootRom_InitUart_fpga
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
.if(IS_FPGA == 1)
    .global     BootRom_InitUart_fpga
BootRom_InitUart_fpga:

#   WREG 0x1F001c24, 0x0800
    WREG 0x1F201310, 0x0001
    WREG 0x1F201318, 0x0083
    WREG 0x1F201308, 0x0000
    WREG 0x1F201300, 0x0013
    WREG 0x1F201318, 0x0003
    WREG 0x1F203d50, 0x0005
    WREG 0x1F203d4c, 0x2104

    bx          lr
.endif    
@//-------------------------------------------------------------------------------------------------
@// BootRom_InitUart
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_InitUart
BootRom_InitUart:

#if 0
    WREG        (CLK_GEN0_BASE+0x13*4) 0x0C01     @ 123Mhz
#else
    WREG        0x1F20164C  0x0C01
#endif

.if (UART0==1)
    #enable reg_uart_rx_enable
    RREG        r0,     0x1F001c24
    orr         r0,     r0,#0x0800
    REG_C2M     r0,     0x1F001c24

    #Select to PIU_UART0
    #if (ENABLE_MSTAR_BD_MST036B_EDISON \
    || ENABLE_MSTAR_BD_MST036B_EDISON_CUS36 \
    || ENABLE_MSTAR_BD_MST036B_EDISON_CUS28 \
    || ENABLE_MSTAR_BD_MST036B_EDISON_CUS28_AP \
    || ENABLE_MSTAR_BD_MST036B_EDISON_CUS36_AP \
    || ENABLE_MSTAR_BD_MST036B_EDISON_CUS18_ATSC \
    || ENABLE_MSTAR_BD_MST036B_EDISON_CUS19)
    RREG        r0,     0x1F203d4c
    orr         r0,     #0x0004
    REG_C2M     r0,     0x1F203d4c
    #endif

.endif

.if (UART0==0)
##   Select UART2 source
    WREG        0x1F203d4c  0x0400
    WREG        0x1F203d50  0x0000
    #10: RX2/TX2 uses PAD_DDCR_DA2/PAD_DDCR_CK2
    RREG        r0,         0x1F203c08
    orr         r0,         r0,     #0x0800
    REG_C2M     r0,         0x1F203c08

    RREG        r0,         0x1F203c08
    and         r0,         r0,     #0xFBFF
    REG_C2M     r0,         0x1F203c08
.endif

.if (UART0==2)
    #enable reg_uart_rx_enable
    RREG        r0,     0x1F001c24
    orr         r0,     r0,#0x0800
    REG_C2M     r0,     0x1F001c24
##   Select UART1 source
    WREG        0x1F203d4c  0x0504
    WREG        0x1F203d50  0x0000

	# according to board define h file to set pad mux
	#WREG        0x1F203c08  0x0800
.endif

    RREG        r0,         0x1F220c18   @ Divisor Latch Access;
    orr         r0,         r0,     #0x0080       @ 1: The divisor latches can be accessed
    REG_C2M     r0,         0x1F220c18

    WREG        0x1F220c00  UART_DIVISOR_L
    WREG        0x1F220c08  UART_DIVISOR_H

    RREG        r0,         0x1F220c18    @ Kernel need
#if 0
    and         r0,         r0,     #0xFF7F
#else
    bic         r0,         r0,     #0x0080
#endif


#if !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) && !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
	WREG        0x1F203c08  0x0800  @set uart pad mux
	WREG        0x1F201650  0x0C0C  @set uart1/uart2 uart_clock
#endif


    REG_C2M     r0,         0x1F220c18

    WREG        0x1F220c10  0x0000        @ Kernel need
    WREG        0x1F220c10  0x0007

    WREG        0x1F220c18  0x0000        @ Kernel need
    WREG        0x1F220c18  0x0003
    WREG        0x1F220c20  0x0000        @ Kernel need
    WREG        0x1F220c08  0x0000        @ Kernel need

	RREG        r0,         0x1F201318   @ Divisor Latch Access;
    orr         r0,         r0,     #0x0080       @ 1: The divisor latches can be accessed
    REG_C2M     r0,         0x1F201318

    WREG        0x1F201300  UART_DIVISOR_L
    WREG        0x1F201308  UART_DIVISOR_H

    RREG        r0,         0x1F201318    @ Kernel need
#if 0
    and         r0,         r0,     #0xFF7F
#else
    bic         r0,         r0,     #0x0080
#endif
    REG_C2M     r0,         0x1F201318

    WREG        0x1F201310  0x0000        @ Kernel need
    WREG        0x1F201310  0x0007

    WREG        0x1F201318  0x0000        @ Kernel need
    WREG        0x1F201318  0x0003
    WREG        0x1F201320  0x0000        @ Kernel need
    WREG        0x1F201308  0x0000        @ Kernel need

	
#if !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) && !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
	RREG        r0,         0x1F220c98   @ Divisor Latch Access;
    orr         r0,         r0,     #0x0080       @ 1: The divisor latches can be accessed
    REG_C2M     r0,         0x1F220c98

    WREG        0x1F220c80  UART_DIVISOR_L
    WREG        0x1F220c88  UART_DIVISOR_H

    RREG        r0,         0x1F220c98    @ Kernel need
#if 0
    and         r0,         r0,     #0xFF7F
#else
    bic         r0,         r0,     #0x0080
#endif
    REG_C2M     r0,         0x1F220c98

    WREG        0x1F220c90  0x0000        @ Kernel need
    WREG        0x1F220c90  0x0007

    WREG        0x1F220c98  0x0000        @ Kernel need
    WREG        0x1F220c98  0x0003
    WREG        0x1F220ca0  0x0000        @ Kernel need
    WREG        0x1F220c88  0x0000        @ Kernel need
#endif

#if !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)
    DPUTK 'U'
    DPUTK 'A'
    DPUTK 'R'
    DPUTK 'T'
    DPUTK '_'
    DPUTK '1'
    DPUTK '1'
    DPUTK '5'
    DPUTK '2'
    DPUTK '0'
    DPUTK '0'
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

@//-------------------------------------------------------------------------------------------------
@// BootRom_PLLRecovery
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
	.global     BootRom_PLLRecovery
BootRom_PLLRecovery:

	WREG        (MS_BUS_RIU_ADDR + (0x101882 << 1)), 0x0404     @//Set L3 switch to xtali
	WREG        (MS_BUS_RIU_ADDR + (0x110C72 << 1)), 0x0101     @//MIU_256BUS_PLL power down
	WREG        (MS_BUS_RIU_ADDR + (0x110C62 << 1)), 0x0101     @//MIU_128BUS_PLL power down
	WREG        (MS_BUS_RIU_ADDR + (0x100B22 << 1)), 0x0800     @//set CA9 switch to slow clk (xtali, by deglitch mux)
	WREG        (MS_BUS_RIU_ADDR + (0x100B22 << 1)), 0x0000     @//keep CA9 at slow clk, but switch fast clk (from 216 to 1G)
    
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

#ifdef CONFIG_MSTAR_VID_ENABLE
@//-------------------------------------------------------------------------------------------------
@// BootRom_InitVid
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
	.global     BootRom_InitVid
BootRom_InitVid:
    RREG    r0, (MS_BUS_RIU_ADDR + (SIDD_MSB << 1))
    RREG    r1, (MS_BUS_RIU_ADDR + (SIDD_LSB << 1))
    and     r0, r0, #0x003F
    mov     r0, r0, lsl #4
    and     r1, r1, #0xF000
    mov     r1, r1, lsr #12
    orr     r1, r1, r0
   
    ldr     r0, =0x0000
    cmp     r1,r0
    beq     ToSetFFVol  
    nop   
    ldr	    r0, = FF_THRESHOLD
    cmp     r1,r0
    bge     ToSetFFVol        @  eFuse >= 10'b FF_THRESHOLD  
    nop                       @  eFuse < 10'b FF_THRESHOLD  
    
.if(ENABLE_MSTAR_BD_MST159A_D01A_S == 1) 
ToSetTTSSVol:
    REGB_SET_BIT  VID1_REG, VID1_REG_MASK    @ VID1 = 1
    REGB_CLR_BIT  VID0_REG, VID0_REG_MASK    @ VID0 = 0
    b		    BootRom_InitVid_Exit
    nop
ToSetFFVol:
    REGB_CLR_BIT  VID1_REG, VID1_REG_MASK    @ VID1 = 0
    REGB_SET_BIT  VID0_REG, VID0_REG_MASK    @ VID0 = 1
.endif
    
.if(ENABLE_MSTAR_BD_MST147A_D01B_S == 1 || ENABLE_MSTAR_BD_MST036B_EDISON == 1 || ENABLE_MSTAR_BD_MST036B_EDISON_CUS18_ATSC ==1 || ENABLE_MSTAR_BD_MST036B_EDISON_CUS19 ==1)
ToSetTTSSVol:
    REGB_SET_BIT  VID1_REG, VID1_REG_MASK   
    WREG_B  0x1F22184C, 0x57                
    b       BootRom_InitVid_Exit
    nop
ToSetFFVol:
    REGB_CLR_BIT  VID1_REG, VID1_REG_MASK    
    WREG_B  0x1F22184C, 0x60                
.endif

BootRom_InitVid_Exit:
    bx          lr
#endif
    
#if 0
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
    add         r0, r0, #((REG_USB30_GPIO_BIT << 7) + REG_USB30_GPIO_OFFSET) @//bit0~bit7 offset addr bit8~bit10 bit count
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

    ldr         r0, =0x00
    cmp         r1, r0
    beq         BootRom_InitVid_Exit                    @//If no SIDD/OSC existed in eFuse, bypass VID flow

    ldr         r0, =CONFIG_VID_THRESHOLD_0
    cmp         r1, r0
    blt         BootRom_InitVid_SetVoltage_0            @//If SIDD/OSC < The Value of Threshold 0, Set Corresponding Voltage 0

    ldr         r0, =CONFIG_VID_THRESHOLD_1
    cmp         r1, r0
    blt         BootRom_InitVid_SetVoltage_1            @//If SIDD/OSC < The Value of Threshold 1, Set Corresponding Voltage 1

    ldr         r0, =CONFIG_VID_THRESHOLD_2
    cmp         r1, r0
    blt         BootRom_InitVid_SetVoltage_2            @//If SIDD/OSC < The Value of Threshold 2, Set Corresponding Voltage 2

    b           BootRom_InitVid_SetVoltage_3            @//If SIDD/OSC >= The Value of Threshold 2, Set Corresponding Voltage 3

BootRom_InitVid_SetVoltage_0:

#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
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
#endif

    b           BootRom_InitVid_Exit

BootRom_InitVid_SetVoltage_1:

#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
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
#endif

    b           BootRom_InitVid_Exit

BootRom_InitVid_SetVoltage_2:

#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
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
#endif

    b           BootRom_InitVid_Exit

BootRom_InitVid_SetVoltage_3:

#if defined(CONFIG_MSTAR_VID_CTRL_GPIO)
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

    @//Set upper bound value of temperature in DVFS mode (CH7)
    WREG        (MS_BUS_RIU_ADDR + (0x00144c << 1)), CONFIG_MSTAR_DVFS_TEMPERATURE_UPPER_BOUND

    @//Set lower bound value of temperature in DVFS mode (CH7)
    WREG        (MS_BUS_RIU_ADDR + (0x00146c << 1)), CONFIG_MSTAR_DVFS_TEMPERATURE_LOWER_BOUND

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

BootRom_ReadEfuseLoop:
    ldr         r11, [r12, #(0x4c << 1)]                    @//Polling efuse read down
    cmp         r11, #0
    bne         BootRom_ReadEfuseLoop

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
#endif    
