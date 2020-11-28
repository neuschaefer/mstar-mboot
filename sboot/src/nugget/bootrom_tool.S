################################################################################
#
# Copyright (c) 2006-2010 MStar Semiconductor, Inc.
# All rights reserved.
#
# Unless otherwise stipulated in writing, any and all information contained
# herein regardless in any format shall remain the sole proprietary of
# MStar Semiconductor Inc. and be kept in strict confidence
# (¡§MStar Confidential Information¡¨) by the recipient.
# Any unauthorized act including without limitation unauthorized disclosure,
# copying, use, reproduction, sale, distribution, modification, disassembling,
# reverse engineering and compiling of the contents of MStar Confidential
# Information is unlawful and strictly prohibited. MStar hereby reserves the
# rights to any and all damages, losses, costs and expenses resulting therefrom.
#
################################################################################

#include "boot.inc"

#ifndef _ArchDefs_h_
#include "ArchDefs.h"
#endif

    .text
    .set        noreorder

#-------------------------------------------------------------------------------------------------
# BOOT_Entry:
# @param  None
# @return None
# @note   Entry point of Boot code
#-------------------------------------------------------------------------------------------------
    .globl      BOOTROM_Entry
BOOTROM_Entry:

#ifndef CONFIG_MSTAR_TITANIA_BD_FPGA
    #//Configure PAD top for MUX and GPIO (e.g. DDR power)
    lui         a0, %hi(padInitTbl + 10)
    bal         MDrv_WriteRegMaskTbl
    ori         a0, %lo(padInitTbl + 10)
#endif
    DBGREG      0x0002


    #// Power-On Sequence
    #bal         BootRomPowerOnSequence

    bal         BootRomInitPll
    nop


    bal         BootInitL2Cache__1
    nop

    bal         BootInitUart__1
    nop

    DBGREG      0x0004

    #//Copy image of bootram to DRAM
    bal         BOOT_CopyBootRam
    nop

    DBGREG      0x0005

    #//Jump to the entry of BOOTRAM
    la          ra, BOOTRAM_Entry
    jr          ra
    nop


#-------------------------------------------------------------------------------------------------
# SysInitPrefetchBuffer
# @param  None
# @return None
# @note   L2 cache initialization
#-------------------------------------------------------------------------------------------------
BootInitL2Cache__1:

    lw          t1, (0xbf000000 + (0x1018BA << 1))  #//Enable L2 Cache Status
    and         t1, t1, ~(0x03)
    or          t1, t1, 0x02
    sw          t1, (0xbf000000 + (0x1018BA << 1))

    lw          t1, (0xbf000000 + (0x101880 << 1))
    and         t1, t1, ~(1 << 15)                  #//Set Write Back Operation
    sw          t1, (0xbf000000 + (0x101880 << 1))

    lw          t1, (0xbf000000 + (0x101882 << 1))
    or          t1, (1 << 7)                        #//Set reg_wriu_lock_off
    #or          t1, (1 << 5)                        #//Fast sync enable
    sw          t1, (0xbf000000 + (0x101882 << 1))

    lw          t1, (0xbf000000 + (0x1018B0 << 1))
    or          t1, (1 << 3)                        #//Enable New Cache Operation
    sw          t1, (0xbf000000 + (0x1018B0 << 1))

    li          t1, 0x2FFF
    sw          t1, (0xbf000000 + (0x1018A0 << 1))  #//Wait write data for pack timeout

    lw          t1, (0xbf000000 + (0x1018B0 << 1))
    and         t1, t1, ~(0x01 << 0)                #//Clear miu request count
    sw          t1, (0xbf000000 + (0x1018B0 << 1))

    jr          ra
    nop


#-------------------------------------------------------------------------------------------------
# BootRomPowerOnSequence
# @param  None
# @return None
# @note   Power On Sequence for Chip
#-------------------------------------------------------------------------------------------------
BootRomPowerOnSequence:

    move        k1, ra

    #//Initial related settings of UART
    #bal         BootInitUart
    nop

    DBGREG      0x0032

    #//Initial related settings of cache
    bal         BootRomInitCache
    nop

    DBGREG      0x0033

#ifdef CONFIG_MSTAR_MOBF_ENABLE
    #//Enable MOBF Function for Secure Usage
    bal         BootRomInitMobf
    nop
#endif


#ifdef CONFIG_MSTAR_32BIT_RIU_MASK_ENABLE
    bal     	BootInitRiuBitMask
    nop
#endif

    bal         BootRomInitFpu
    nop

    DBGREG      0x0036

#ifndef CONFIG_MSTAR_TITANIA_BD_FPGA
    #//Initial related settings of SPI flash clock
    bal         BootRomInitSpiFlashClock
    nop

    DBGREG      0x0037

    bal         BootRomChangeSpiFlashClock
    nop
#endif

    DBGREG      0x0038

    move        ra, k1
    jr          ra
    nop

#-------------------------------------------------------------------------------------------------
# BOOT_SramToTsp  Set TSP Sram to TSP
# @param  None
# @return None
# @note   do TSP Sram init
#-------------------------------------------------------------------------------------------------
BOOT_SramToTsp:

    RREG        t9, 0xBF2226BC #//Select tsp sram to MIPS
    and         t9, t9, 0xffef
    REG_C2M     t9, 0xBF2226BC

    RREG        t9, 0xBF2226BC #//Enable nand boot operation
    or          t9, t9, 0x0008
    REG_C2M     t9, 0xBF2226BC

    RREG        t9, 0xBF2226BC #//Select tsp sram to FCIE4
    and         t9, t9, 0xfff7
    REG_C2M     t9, 0xBF2226BC

    RREG        t9, 0xBF2226BC #//Disable nand boot operation
    or          t9, t9, 0x0010
    REG_C2M     t9, 0xBF2226BC

    jr          ra
    nop

#-------------------------------------------------------------------------------------------------
# BootRomInitSpiFlashClock SPI Clock init
# @param  None
# @return None
# @note   do SPI Clock init
#-------------------------------------------------------------------------------------------------
BootRomInitSpiFlashClock:

    WREG_B      0xBF0011C4, 0xFF        #//Set CSZ deselect time to 16 SPI clock cycles
                                        #//Set CSZ setup time to 16 SPI clock cycles
    WREG_B      0xBF0011C5, 0x0F        #//Set CSZ hold time to 16 SPI clock cycles
    WREG_B      0xBF0011C8, 0x01        #//Enable fast read mode

    jr          ra
    nop
#-------------------------------------------------------------------------------------------------
# BootRomChangeSpiFlashClock
# @param  None
# @return None
# @note   change SPI clock
#-------------------------------------------------------------------------------------------------
BootRomChangeSpiFlashClock:

    WREG_B      0xBF001C81, 0x04        #//Set clock of clk_spi to 86MHz
    WREG_B      0xBF001C81, 0x44        #//Switch clk_spi between clk_mcu_p and clk_ext_xtali_buf
	WREG_B      0xBF001C80, 0x80	    #//Set clock of MCU to 170MHz
    jr          ra
    nop

#-------------------------------------------------------------------------------------------------
# BootRomOcpClockRatio
# @param  None
# @return None
# @note   do MIPS OCP clock ratio setting
#-------------------------------------------------------------------------------------------------
BootRomOcpClockRatio:

    WREG_B      0xBF203A3C, (MIPS_OCP_CLOCK_RATIO | 0x00)   #//Set clock ratio to 2:1
    WREG_B      0xBF203A3C, (MIPS_OCP_CLOCK_RATIO | 0x01)   #//Set clock ratio change pulse

    WREG      	0xBF201644, 0x0000
    WREG      	0xBF201644, 0x8000      #//Switch to CLK_MIPS to mipspll_vco

    jr          ra
    nop

#-------------------------------------------------------------------------------------------------
# BOOT_CopyBootRam
# @param  None
# @return None
# @note   Copy bootram image to DRAM
#-------------------------------------------------------------------------------------------------
BOOT_CopyBootRam:

    la          t0, _ld_bootram_ROM_start
    la          t1, _ld_bootram_RAM_start

    and         t1, t1, ~0xE0000000
    or          t1, t1, 0xA0000000

    la          t2, _ld_bootram_RAM_end
    and         t2, t2, ~0xE0000000
    or          t2, t2, 0xA0000000

1:
    ld          t3, 0(t0)               #//Read 64-bit data to reduce processing time
    ld          t5, 8(t0)

    sd          t3, 0(t1)
    sd          t5, 8(t1)

    addu        t0, t0, 16
    addu        t1, t1, 16

    bltu        t1, t2, 1b
    nop

    jr          ra
    nop

#-------------------------------------------------------------------------------------------------
# BootRomEnableAccessMiu
# @param  None
# @return None
# @note   Enable to access MIU
#-------------------------------------------------------------------------------------------------
LEAF(BootRomEnableAccessMiu)

    WREG        0xBF005788, 0x0004      #//Set XDATA2MIU read Priority
    WREG        0xBF00578C, 0x3c11      #//Set the low bound address of MCU XDATA mapping to MIU (Unit: 1K-Byte)
    WREG        0xBF005790, 0x0010      #//Set the low byte address to access xdata from MIU. The granularity is 64k bytes
    WREG        0xBF005794, 0x403c      #//Set the low bound address of MCU XDATA mapping to MIU (Unit: 1K-Byte)
    WREG        0xBF005798, 0x0101      #//Set the low byte address to access xdata from MIU. The granularity is 4k bytes.

    jr          ra
    nop

END(BootRomEnableAccessMiu)

#-------------------------------------------------------------------------------------------------
# BootInitUart
# @param  None
# @return None
# @note   Init UART
#-------------------------------------------------------------------------------------------------
BootInitUart__1:

#ifdef CONFIG_MSTAR_TITANIA_BD_FPGA

    WREG        0xbf001c24 0x0800
    WREG        0xbf203d4c 0x2104
    WREG        0xbf201318 0x0083
    WREG        0xbf201300 0x0013
    WREG        0xbf201308 0x0000
    WREG        0xbf201310 0x0000
    WREG        0xbf201318 0x0003
    WREG        0xbf201310 0x0000
    WREG        0xbf201310 0x0007
    WREG        0xbf006010 0x0000
    WREG        0xbf006014 0x0000

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

    WREG        0xbf20164c, 0x0C01      #//Set CLK_UART0 to 123Mhz

.if (BOOTINFO_UART0_ENABLE == 1)
    RREG        t3, 0xbf001c24          #//Enable UART Rx via PAD_DDCA for dig_mux
    ori         t3, t3, 0x0800
    sw          t3, 0xbf001c24

    RREG        t3, 0xbf203d4c          #//Select UART0 source to PIU UART0
    or          t3, t3, 0x0004
    sw          t3, 0xbf203d4c

.endif

.if (BOOTINFO_UART1_ENABLE == 1)
    WREG        0xbf203d4c 0x0504       #//Set UART1 select

    WREG        0xbf203d50 0x0000       #//Set UART4 source to None

    RREG        t3, 0xbf203c08          #//Set third UART mode: RX2/TX2 uses PAD_UART_RX2/PAD_UART_TX2
    ori         t3, t3, 0x0C00
    sw          t3, 0xbf203c08

    #uart1 init
    RREG        t3, 0xbf220C18          #//Enable Divisor Latch Access
    ori         t3, t3, 0x0080
    sw          t3, 0xbf220C18

    WREG        0xbf220C00 UART_DIVISOR_L   #//Set Divisor Latch LSB
    WREG        0xbf220C08 UART_DIVISOR_H   #//Set Divisor Latch MSB

    RREG        t3, 0xbf220C18          #//Disable Divisor Latch Access
    and         t3, t3, 0xFF7F
    sw          t3, 0xbf220C18

    WREG        0xbf220C10 0x0000
    WREG        0xbf220C10 0x0007       #//Enable FIFO and Clear TX/RX FIFO

    WREG        0xbf220C18 0x0000
    WREG        0xbf220C18 0x0003       #//8-bit Data / 1-bit Stop / No Parity Bit
    WREG        0xbf220C20 0x0000       #//Set DTS/RTS to 1
    WREG        0xbf220C08 0x0000       #//Disable Interrupt

.endif

.if (BOOTINFO_UART2_ENABLE == 1)
    RREG        t3, 0xbf203d4c          #//Select UART2 source to PIU UART0
    ori         t3, t3, 0x0400
    sw          t3, 0xbf203d4c

    WREG        0xbf203d50 0x0000       #//Set UART4 source to None

    RREG        t3, 0xbf203c08          #//Set third UART mode: RX2/TX2 uses PAD_UART_RX2/PAD_UART_TX2
    ori         t3, t3, 0x0800
    sw          t3, 0xbf203c08
.endif

    RREG        t3, 0xbf201318          #//Enable Divisor Latch Access
    ori         t3, t3, 0x0080
    sw          t3, 0xbf201318

    WREG        0xbf201300 UART_DIVISOR_L   #//Set Divisor Latch LSB
    WREG        0xbf201308 UART_DIVISOR_H   #//Set Divisor Latch MSB

    RREG        t3, 0xbf201318          #//Disable Divisor Latch Access
    and         t3, t3, 0xFF7F
    sw          t3, 0xbf201318

    WREG        0xbf201310 0x0000
    WREG        0xbf201310 0x0007       #//Enable FIFO and Clear TX/RX FIFO

    WREG        0xbf201318 0x0000
    WREG        0xbf201318 0x0003       #//8-bit Data / 1-bit Stop / No Parity Bit
    WREG        0xbf201320 0x0000       #//Set DTS/RTS to 1
    WREG        0xbf201308 0x0000       #//Disable Interrupt

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

    jr          ra
    nop

#-------------------------------------------------------------------------------------------------
# BootInitRiuBitMask
# @param  None
# @return None
# @note   RIU bitmask
#-------------------------------------------------------------------------------------------------
BootInitRiuBitMask:

    lw      t1, 0xBF20310C
    or      t1, t1, (0x01 << 5)
    sw      t1, 0xBF20310C

    lw      t1, 0xBF00025C
    or      t1, t1, (0x01 << 0)
    sw      t1, 0xBF00025C

    lw      t1, 0xBF20025C
    or      t1, t1, (0x01 << 0)
    sw      t1, 0xBF20025C

    jr      ra
    nop

LEAF(BootRomInitFpu)

    mfc0    t1, C0_Config1
	nop
    and     t1, t1, 0x01            #//Check Status of FPU Implemented
    beq     t1, zero, BootRomInitFpuExit
    nop

    mfc0    t0, C0_Status
	nop
    or      t0, t0, (0x01 << 29)    #//Enable Co-Processor 1
    or      t0, t0, (0x01 << 26)    #//Set floating point registers can contain any datatype
    mtc0    t0, C0_Status
    nop

    move    t0, zero                #//FS = FO = FN = 0: IEEE-compliant mode
    ctc1    t0, C1_FCSR
    nop

BootRomInitFpuExit:
    jr          ra
    nop

END(BootRomInitFpu)

#-------------------------------------------------------------------------------------------------
# BootRomDisableAvd
# @param  None
# @return None
# @note   Disable AVD before MIU init
#-------------------------------------------------------------------------------------------------
LEAF(BootRomDisableAvd)

    RREG        t9, 0xBF206C54
    or          t9, t9, 0x0010
    REG_C2M     t9, 0xBF206C54

    jr          ra
    nop

END(BootRomDisableAvd)


#ifdef CONFIG_MSTAR_MOBF_ENABLE
#-------------------------------------------------------------------------------------------------
# BootRom_InitMobf
# @param
# @return None
# @note
#-------------------------------------------------------------------------------------------------
LEAF(BootRomInitMobf)

	WREG    0xBF2277D8 0xC000

	WREG    0xBF2277D8 0x0001
	WREG    0xBF2277D0 0x0100
	WREG    0xBF2277D4 0x0302

	WREG    0xBF2277D8 0x0002
	WREG    0xBF2277D0 0x0504
	WREG    0xBF2277D4 0x0706

	WREG    0xBF2277D8 0x0003
	WREG    0xBF2277D0 0x0908
	WREG    0xBF2277D4 0x0b0a

	WREG    0xBF2277D8 0x0004
	WREG    0xBF2277D0 0x1100
	WREG    0xBF2277D4 0x1302

	WREG    0xBF2277D8 0x0005
	WREG    0xBF2277D0 0x1504
	WREG    0xBF2277D4 0x1706

	WREG    0xBF2277D8 0x0006
	WREG    0xBF2277D0 0x1908
	WREG    0xBF2277D4 0x1b0a

	WREG    0xBF2277D8 0x0007
	WREG    0xBF2277D0 0x1d0c
	WREG    0xBF2277D4 0x1f0e

	WREG    0xBF2277D8 0x0008
	WREG    0xBF2277D0 0x2100
	WREG    0xBF2277D4 0x2302

	WREG    0xBF2277D8 0x0009
	WREG    0xBF2277D0 0x2504
	WREG    0xBF2277D4 0x2706

	WREG    0xBF2277D8 0x000A
	WREG    0xBF2277D0 0x2908
	WREG    0xBF2277D4 0x2b0a

	WREG    0xBF2277D8 0x000B
	WREG    0xBF2277D0 0x2d0c
	WREG    0xBF2277D4 0x2f0e

	WREG    0xBF2277D8 0x000C
	WREG    0xBF2277D0 0x3100
	WREG    0xBF2277D4 0x3302

	WREG    0xBF2277D8 0x000D
	WREG    0xBF2277D0 0x3504
	WREG    0xBF2277D4 0x3706

	WREG    0xBF2277D8 0x000E
	WREG    0xBF2277D0 0x3908
	WREG    0xBF2277D4 0x3b0a

	WREG    0xBF2277D8 0x000F
	WREG    0xBF2277D0 0x3d0c
	WREG    0xBF2277D4 0x3f0e

	WREG    0xBF2277D8 0x0010
	WREG    0xBF2277D0 0x4100
	WREG    0xBF2277D4 0x4302

	WREG    0xBF2277D8 0x0011
	WREG    0xBF2277D0 0x4504
	WREG    0xBF2277D4 0x4706

	WREG    0xBF2277D8 0x0012
	WREG    0xBF2277D0 0x4908
	WREG    0xBF2277D4 0x4b0a

    jr          ra
    nop
END(BootRomInitMobf)
#endif