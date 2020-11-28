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

    #// Enable 8051 to access MIU for MStar TV Tool
    bal         BootRomEnableAccessMiu
    nop

    DBGREG      0x0003

    #// Power-On Sequence
    bal         BootRomPowerOnSequence
    nop

    DBGREG      0x0004

    #//Copy image of bootram to DRAM
    bal         BOOT_CopyBootRam
    nop

    DBGREG      0x0005

    #//Set TSP Sram be used by TSP
    bal         BOOT_SramToTsp
    nop

    DBGREG      0x0006

#ifdef CONFIG_MSTAR_EDINBURGH
    #//Init Edinburgh
    bal         BOOT_InitEdinburgh
    nop
#endif

    DBGREG      0x0006
    
    #//Trim VID from efuse 
    bal         BootRomTrimVid
    nop

    #//Trim Mhl Cbus from efuse 
    bal         BootRomTrimMhlCbus
    nop

    #//Trim Emac Ephy from efuse 
    bal         BootRomTrimEmacEphy
    nop

    #//Jump to the entry of BOOTRAM
    la          ra, BOOTRAM_Entry
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

#ifndef CONFIG_MSTAR_TITANIA_BD_FPGA

    #//Initial releated settings of PLL
    bal         BootRomInitPll
    nop

    DBGREG      0x0030

    #//Set clock ratio of OCP
    bal     	BootRomOcpClockRatio
    nop

    #//Initial related settings of Clock
    bal         BootRomInitClock
    nop

    DBGREG      0x0031

    DELAYUS     100

#endif

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

    #//Initial related settings of MIU
    bal     	BootInitMiu0
    nop

.if (ENABLE_MIU1 == 1)
    #//Initial related settings of MIU1
    bal         BootInitMiu1
    nop
.endif

    DBGREG      0x0035

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

                                        #//TSP
    WREG_B      0xBF2016A8, 0x00        #//Set CLK_TSP to 172MHz (Enabled)
    WREG_B      0xBF2017E0, 0x01        #//Select the output according to reg_ckg_tsp

    RREG        t9, 0xBF2226BC          #//Select tsp sram to MIPS
    and         t9, t9, 0xffef
    REG_C2M     t9, 0xBF2226BC

    RREG        t9, 0xBF2226BC          #//Enable nand boot operation
    or          t9, t9, 0x0008
    REG_C2M     t9, 0xBF2226BC

    RREG        t9, 0xBF2226BC          #//Select tsp sram to FCIE4
    and         t9, t9, 0xfff7
    REG_C2M     t9, 0xBF2226BC

    jr          ra
    nop

#-------------------------------------------------------------------------------------------------
# BOOT_InitEdinburgh  Init Demod Edinburgh
# @param  None
# @return None
# @note   do enable Xtal for Edinburgh
#-------------------------------------------------------------------------------------------------
BOOT_InitEdinburgh:

    RREG        t9, 0xBF224004
    and         t9, t9, 0xdfff
    REG_C2M     t9, 0xBF224004

    RREG        t9, 0xBF225080
    and         t9, t9, 0xffef
    REG_C2M     t9, 0xBF225080

    RREG        t9, 0xBF2250F4
    or          t9, t9, 0x0001
    REG_C2M     t9, 0xBF2250F4

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

    WREG_B      0xBF203A3C, (MIPS_OCP_CLOCK_RATIO | 0x40)   #//Set clock ratio to 2:1
    DELAYUS     10
    WREG_B      0xBF203A3C, (MIPS_OCP_CLOCK_RATIO | 0x00)   #//Set clock ratio to 2:1
    DELAYUS     10
    WREG_B      0xBF203A3C, (MIPS_OCP_CLOCK_RATIO | 0x01)   #//Set clock ratio change pulse
    DELAYUS     10

    WREG      	0xBF201644, 0x0800
    DELAYUS     10
    WREG      	0xBF201644, 0x0000
    DELAYUS     10
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

    DPUTK '['
    DPUTK 'A'
    DPUTK 'T'
    DPUTK ']'
    DPUTK '['
    DPUTK 'M'
    DPUTK 'B'
    DPUTK ']'
    DPUTK '['
    DPUTK 's'
    DPUTK 't'
    DPUTK 'a'
    DPUTK 'r'
    DPUTK 't'
    DPUTK ' '
    DPUTK 's'
    DPUTK 'b'
    DPUTK ']'
    DPUTK '['
    DPUTK '0'
    DPUTK ']'

    DPUTK        '\n'
    DPUTK        '\r'
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

#-------------------------------------------------------------------------------------------------
# BootRomTrimMhlCbus
# @param  None
# @return None
# @note   Trim Mhl Cbus from efuse
#-------------------------------------------------------------------------------------------------
LEAF(BootRomTrimMhlCbus)

	WREG        0xBF00409C 0x004f     #//Set bank 0x4f to read efuse
	WREG        0xBF004098 0x0001     #//Launch efuse read

BootRomTrimMhlCbusLoop:               #//Polling efuse read complete
    RREG        t9, 0xBF004098
    bnez        t9, BootRomTrimMhlCbusLoop
    nop
    
    RREG        t9, 0xBF0040A0        #//Get efuse data from bank 0x4F[9:8]
    andi        t9, 0x00000300

    beq         t9, 0x00000000, BootRomMhlCbusMode0
    nop
    beq         t9, 0x00000100, BootRomMhlCbusMode1
    nop
    beq         t9, 0x00000200, BootRomMhlCbusMode2
    nop
    beq         t9, 0x00000300, BootRomMhlCbusMode3
    nop

BootRomMhlCbusMode0:                   #//Case switch from efuse value
    li          t9, 0x0000
    j           BootRomSetMhlCbus
    nop
BootRomMhlCbusMode1:
    li          t9, 0x0110
    j           BootRomSetMhlCbus
    nop
BootRomMhlCbusMode2:
    li          t9, 0x0088
    j           BootRomSetMhlCbus
    nop
BootRomMhlCbusMode3:
    li          t9, 0x0198
    j           BootRomSetMhlCbus
    nop

BootRomSetMhlCbus:                  
    RREG        t0, 0xBF005EC4
    andi        t0, t0, 0xfe67
    or          t9, t9, t0
    REG_C2M     t9, 0xBF005EC4
    
    jr          ra
    nop

END(BootRomTrimMhlCbus)

#-------------------------------------------------------------------------------------------------
# BootRomTrimEmacEphy
# @param  None
# @return None
# @note   Trim Emac Ephy from efuse
#-------------------------------------------------------------------------------------------------
LEAF(BootRomTrimEmacEphy)

	WREG        0xBF00409C 0x004d     #//Set bank 0x4d to read efuse
	WREG        0xBF004098 0x0001     #//Launch efuse read

BootRomTrimEmacEphyLoop:              #//Polling efuse read complete
    RREG        t9, 0xBF004098
    bnez        t9, BootRomTrimEmacEphyLoop
    nop
    
    RREG        t9, 0xBF0040A0        #//Get efuse data from bank 0x4d[13:0]
    srl         k0, t9, 14
    andi        k0, k0, 0x0003
    andi        t9, 0x3fff

    RREG        k1, 0xBF0040A4        #//Get efuse data from bank 0x4d[17:14]
    andi        k1, 0x0003
    sll         k1, k1, 2
    or          k1, k1, k0
    sll         k1, k1, 8

    RREG        k0, 0xBF2434C0        #//0x121a60[11:8] + 0x121a60[2] = 1
    andi        k0, k0, 0xf0ff
    or          k0, k0, k1
    ori         k0, k0, 0x0004
    REG_C2M     k0, 0xBF2434C0
    
    RREG        k0, 0xBF2434D0        #//0x121a68[13:0] + 0x121a68[15] = 1
    andi        k0, k0, 0xc000
    or          k0, k0, t9
    ori         k0, k0, 0x8000
    REG_C2M     k0, 0xBF2434D0
    
    jr          ra
    nop

END(BootRomTrimEmacEphy)

#-------------------------------------------------------------------------------------------------
# BootRomTrimVid
# @param  None
# @return None
# @note   Trim VID from efuse
#-------------------------------------------------------------------------------------------------
LEAF(BootRomTrimVid)
    
    RREG        t9, 0xBF004018        #//Get efuse data about OSC value from {0x20_06[11:2]}
    srl         t9, t9, 2
    andi        t9, 0x03ff

    RREG        k0, 0xBF004018        #//Get efuse data about SIDD value from {0x20_07[5:0], 0x20_06[15:12]}
    srl         k0, k0, 12
    andi        k0, 0x000f
    RREG        k1, 0xBF00401C        
    sll         k1, k1, 4
    andi        k1, 0x03f0
    or          k0, k1, k0
    
    li          k1, 109
    blt         t9, k1, BootRomTrimVidHigh
    nop
    
    li          k1, 70 
    blt         k0, k1, BootRomTrimVidHigh
    nop
    
BootRomTrimVidLow:
    RREG        t9, 0xBF001C3C        #//Set PAD_PM_GPIO0 = 1 with the setting  0x0e1e[0]=0 , 0x0e20[0]=0
    andi        t9, 0xfffe
    REG_C2M     t9, 0xBF001C3C
    
    RREG        t9, 0xBF001C40
    andi        t9, 0xfffe
    REG_C2M     t9, 0xBF001C40
    
    b           BootRomTrimVidExit
    nop
BootRomTrimVidHigh:
    RREG        t9, 0xBF001C3C        #//Set PAD_PM_GPIO0 = 1 with the setting  0x0e1e[0]=0 , 0x0e20[0]=1
    andi        t9, 0xfffe
    REG_C2M     t9, 0xBF001C3C
    
    RREG        t9, 0xBF001C40
    ori         t9, 0x0001
    REG_C2M     t9, 0xBF001C40

BootRomTrimVidExit:

    jr          ra
    nop

END(BootRomTrimVid)
