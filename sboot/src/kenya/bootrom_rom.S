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

#ifndef _DRV_MIU_INIT_H_
#include "drv_miu_init.h"
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
    #// Enable EJ
    WREG_B  0xbf203c5c, 0x06

    DBGREG      0x0002
    #//Configure PAD top for MUX and GPIO (e.g. DDR power)
    la           a3, MDrv_WriteRegMaskTbl
    lui          a0, %hi(padInitTbl + 10)
    ori          a0, %lo(padInitTbl + 10)
    jal          a3
    nop

    #// Enable 8051 to access MIU for MStar TV Tool
    bal         BootRomEnableAccessMiu
    nop

    DBGREG      0x0003

#ifndef CONFIG_MSTAR_TITANIA_BD_FPGA
    #// Power-On Sequence
    bal         BootRomPowerOnSequence
    nop
#else
	# Init UART
    bal         FPGA_InitUART
    nop
    WREG        0xbf206740,0xaaaa
	PUTC        '\r'
    PUTC        '\n'
    WREG        0xbf206744,0xbbbb

    PUTC        'B'
    PUTC        'O'

    #//Initial related settings of cache
    bal         BootRomInitCache
    nop

    # Init FPGA RAM
    bal         FPGA_InitDRAM
    nop

	PUTC        'O'
	PUTC        'T'
#endif

    DBGREG      0x0004

    # set stack pointer
    la          sp,  _stack_pointer     #//Set stack pointer

    DBGREG      0x0006

	la			a0, CONFIG_BOOTRAM_LOADADDR
	la			a1, 0x8000
	bal			drvNAND_Load2ndBL
     nop

	DBGREG      0x0007

	#PUTK        'M'
    #PUTK        'S'
    #PUTK        't'
    #PUTK        'a'
    #PUTK        'r'
    #PUTK        '\r'
    #PUTK        '\n'

    #//Jump to the entry of BOOTRAM
    la          ra, BOOTRAM_ROM_Entry
    nop

#-------------------------------------------------------------------------------------------------
# BOOTROM_CopyData
# @param  None
# @return None
# @note   Power On Sequence for Chip
#-------------------------------------------------------------------------------------------------
BOOTROM_CopyData:
#//-------------------------------------------------------------------------------------------------
#// Copy Data Section to DRAM
#//-------------------------------------------------------------------------------------------------
    la	        t3, _end_address_text_section
    la	        t4, _start_address_data_section
    la	        t5, _size_data_section
    beqz        t5, _CopyDataToSramEnd

_CopyDataToSram:
    lw          t6, 0(t3)
    sw          t6, 0(t4)

    add         t3, t3, 4
    add         t4, t4, 4
    add         t5, t5, -4

    bnez        t5, _CopyDataToSram
    nop

_CopyDataToSramEnd:
    jr          ra
    nop

#-------------------------------------------------------------------------------------------------
# BOOTROM_InitBss
# @param  None
# @return None
# @note   Power On Sequence for Chip
#-------------------------------------------------------------------------------------------------
BOOTROM_InitBss:
#//-------------------------------------------------------------------------------------------------
#// Clear BSS Section in DRAM
#//-------------------------------------------------------------------------------------------------
    la	        t3, _start_address_bss_section
    la	        t4, _size_bss_section
    li	        t5, 0
    beqz        t4, _InitBssLoopEnd

_InitBssLoop:
    sw          t5, 0(t3)

    add         t3, t3, 4
    add         t4, t4, -4

    bnez        t5, _InitBssLoop
    nop

_InitBssLoopEnd:
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

    #//Initial releated settings of PLL
    bal         BootRomInitPll
    nop

    DBGREG      0x0030

    #//Initial related settings of Clock
    bal         BootRomInitClock
    nop

    DBGREG      0x0031

    DELAYUS     100

    #//Initial related settings of UART
    bal         BootInitUart
    nop

    DBGREG      0x0032

    #//Initial related settings of cache
    bal         BootRomInitCache
    nop

	DBGREG      0x0033

    #//Disable ADV before MIU initiation
    bal     	BootRomDisableAvd
    nop

    DBGREG      0x0034
    
    
#ifdef CONFIG_MSTAR_STR_ENABLE
    RREG        t3, (REG_ADDR_BASE + (0x0e6e << 1))
    or          t3, t3, 0xFF00
    add         t4, zero, 0xFFFF
    beq         t3, t4, BootRom_AcOn_Flow

    nop


BootRom_DcOn_Flow:
    bal         BootInitMiu_STR
    nop
    j           BootRom_Exit_Refresh

    DBGREG      0x0135
#endif

BootRom_AcOn_Flow:
    #//Initial related settings of MIU0
    bal     	BootInitMiu
    nop

    DBGREG      0x0035
    
BootRom_Exit_Refresh:

#ifdef CONFIG_MSTAR_32BIT_RIU_MASK_ENABLE
    bal     	BootInitRiuBitMask
    nop
#endif
    bal         BootRomInitFpu
    nop


#ifndef CONFIG_MSTAR_TITANIA_BD_FPGA
    #//Initial related settings of SPI flash clock
    bal         BootRomInitSpiFlashClock
    nop

    DBGREG      0x0036

    bal         BootRomChangeSpiFlashClock
    nop

    DBGREG      0x0037
#endif

    #//Set clock ratio of OCP
    bal     	BootRomOcpClockRatio
    nop

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

    RREG        t9, 0xBF2039C0 #//Select tsp sram to TSP
    or          t9, t9, 0x0001
    REG_C2M     t9, 0xBF2039C0

    jr          ra
    nop

#-------------------------------------------------------------------------------------------------
# BootRomInitSpiFlashClock SPI Clock init
# @param  None
# @return None
# @note   do SPI Clock init
#-------------------------------------------------------------------------------------------------
    BootRomInitSpiFlashClock:

        WREG_B      0xBF0015C4, 0xFF        #//Set CSZ deselect time to 16 SPI clock cycles
                                        #//Set CSZ setup time to 16 SPI clock cycles
        WREG_B      0xBF0015C5, 0x0F        #//Set CSZ hold time to 16 SPI clock cycles
        WREG_B      0xBF0015C8, 0x01        #//Enable fast read mode

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
        WREG_B      0xBF001C80, 0x80        #//Set clock of MCU to 170MHz

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

        WREG_B      0xBF201645, 0x80      #//Switch to CLK_MIPS to mipspll_vco

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
    LEAF(BootInitUart)

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

        PUTK        'R'
        PUTK        'O'
        PUTK        'M'

        PUTK        '\n'
        PUTK        '\r'

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

    END(BootInitUart)

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

#if defined(CONFIG_MSTAR_TITANIA_BD_FPGA)
#-------------------------------------------------------------------------------------------------
# FPGA_InitUART
# @param  None
# @return None
# @note   Init UART
#-------------------------------------------------------------------------------------------------
FPGA_InitUART:
    WREG        0xbf001c24 0x0800
    WREG        0xbf203d4c 0x2104

    WREG        0xbf201318 0x0083
    WREG        0xbf201300 0x0013
    WREG        0xbf201308 0x0000
    WREG        0xbf201310 0x0000

    WREG        0xbf201318 0x0003
    WREG        0xbf201310 0x0000
    WREG        0xbf201310 0x0007

    jr          ra
    nop

#-------------------------------------------------------------------------------------------------
# FPGA_InitDRAM
# @param  None
# @return None
# @note   Initial DRAM
#-------------------------------------------------------------------------------------------------
FPGA_InitDRAM:
    WREG        0xBF00578C 0x3c11
    WREG        0xBF005794 0x403c
    WREG        0xBF005788 0x0004

    WREG        0xBF202404 0x0854
    WREG        0xBF202408 0x01c5
    WREG        0xBF20240C 0x0120
    WREG        0xBF202410 0x0833
    WREG        0xBF202414 0x0c33
    WREG        0xBF202418 0x7121
    WREG        0xBF20241C 0x100e
    WREG        0xBF202420 0x0031

    WREG        0xBF202400 0x0008
    DELAYUS     10000
    WREG        0xBF202400 0x000c
    DELAYUS     10000

    WREG        0xBF202400 0x000e
    DELAYUS     10000

    WREG        0xBF202400 0x000f
    DELAYUS     10000

    WREG        0xBF202454 0x0000

    WREG        0xBF20248C 0x0000
    WREG        0xBF2024CC 0x0000
    WREG        0xBF20250C 0x0000
    WREG        0xBF20254C 0x0000
    WREG        0xBF20243C 0x0C08
    DELAYUS     10000

    WREG        0xBF2025C4 0x0000
    WREG        0xBF2025C8 0x0021
    WREG        0xBF2025CC 0x0000
    WREG        0xBF2025D0 0x5aa5
    WREG        0xBF2025C0 0x0007

    jr          ra
    nop
#endif
