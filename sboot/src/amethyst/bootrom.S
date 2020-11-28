################################################################################
#
# Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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

#ifndef _BOOT_INC_
#include "boot.inc"
#endif

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

#ifdef CONFIG_EMMC_BOOT
    #//Copy chunk header from EMMC boot partition to DRAM
    bal         BOOT_CopyEmmcHeader
    nop

    #//Copy uboot binary from EMMC boot partition to DRAM
    bal         BOOT_CopyEmmcUboot
    nop

    #//Set clock ratio of OCP
    bal     	BootRomOcpClockRatio
    nop

    #//Jump to Uboot entry
    jr          t6
    nop
#else
    #//Copy image of bootram to DRAM
    bal         BOOT_CopyBootRam
    nop

    DBGREG      0x0005

    #//Jump to the entry of BOOTRAM
    la          ra, BOOTRAM_Entry
    jr          ra
    nop
#endif

#-------------------------------------------------------------------------------------------------
# BootRomPowerOnSequence
# @param  None
# @return None
# @note   Power On Sequence for Chip
#-------------------------------------------------------------------------------------------------
BootRomPowerOnSequence:

    move        k1, ra

#ifndef CONFIG_MSTAR_TITANIA_BD_FPGA

    #//AVD Reset 
    RREG        t0, (0xbf000000 + (0x10362a << 1))
    or          t0, t0, 0x0010
    sw          t0, (0xbf000000 + (0x10362a << 1))

    #//Initial releated settings of PLL
    bal         BootRomInitPll
    nop

    DBGREG      0x0030

#ifndef CONFIG_EMMC_BOOT
    #//Set clock ratio of OCP
    bal     	BootRomOcpClockRatio
    nop
#endif

    #//Initial related settings of Clock
    bal         BootRomInitClock
    nop

    DBGREG      0x0031

    DELAYUS     100

#endif

    #//Initial related settings of UART
    bal         BootInitUart
    nop
	
# checkpoint for autotest boottime, plz dont remove it
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
	
    DBGREG      0x0032

    #//NOTICE:
    #//Due to MIU1 timing issue, please disable MIU clock before cache initial flow
    WREG_B      (0xBF000000 + (0x100B3E << 1)), 0x0D        #//Set CLK_MIU to 216MHz (Disabled)

    #//Initial related settings of cache
    bal         BootRomInitCache
    nop

    WREG_B      (0xBF000000 + (0x100B3E << 1)), 0x0C        #//Set CLK_MIU to 216MHz (Enabled)

    DBGREG      0x0033

.if (CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51 != 1)
    #//Initial related settings of MIU
    bal     	BootInitMiu
    nop
.endif

    DBGREG      0x0034

#ifdef CONFIG_MSTAR_32BIT_RIU_MASK_ENABLE
    bal     	BootInitRiuBitMask
    nop
#endif

    bal         BootRomInitFpu
    nop

    DBGREG      0x0035

	#//Jump to cacheable address
	la	        t0, 1f
	and         t0, t0, ~(KSEG_MSK)
	or          t0, t0, KSEG0BASE
	j	        t0
	nop
1:

    DBGREG      0x0036

#ifndef CONFIG_MSTAR_TITANIA_BD_FPGA
#ifndef CONFIG_EMMC_BOOT
    #//Initial related settings of SPI flash clock
    bal         BootRomInitSpiFlashClock
    nop

    bal         BootRomChangeSpiFlashClock
    nop
#endif
#endif

    DBGREG      0x0037

    move        ra, k1
    jr          ra
    nop

#-------------------------------------------------------------------------------------------------
# BootRomInitSpiFlashClock SPI Clock init
# @param  None
# @return None
# @note   do SPI Clock init
#-------------------------------------------------------------------------------------------------
BootRomInitSpiFlashClock:

    WREG_B      (0xBF000000 + (0x0008E2 << 1)), 0xFF        #//Set CSZ deselect time to 16 SPI clock cycles
                                                            #//Set CSZ setup time to 16 SPI clock cycles
    WREG_B      (0xBF000000 + (0x0008E2 << 1) + 1), 0x0F    #//Set CSZ hold time to 16 SPI clock cycles
    WREG_B      (0xBF000000 + (0x0008E4 << 1)), 0x01        #//Enable fast read mode

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

    WREG_B      (0xBF000000 + (0x101D1E << 1)), 0x40    #//Set clock ratio to 1:1
    DELAYUS     2000                                    #//Delay 2ms
    WREG_B      (0xBF000000 + (0x101D1E << 1)), 0x41    #//Set clock ratio change pulse
    DELAYUS     2000                                    #//Delay 2ms
    WREG_B      (0xBF000000 + (0x101D1E << 1)), (MIPS_OCP_CLOCK_RATIO | 0x00)   #//Set clock ratio to 2:1
    DELAYUS     2000                                    #//Delay 2ms
    WREG_B      (0xBF000000 + (0x101D1E << 1)), (MIPS_OCP_CLOCK_RATIO | 0x01)   #//Set clock ratio change pulse
    DELAYUS     2000                                    #//Delay 2ms

    WREG      	(0xBF000000 + (0x100B22 << 1)), 0x0000
    WREG      	(0xBF000000 + (0x100B22 << 1)), 0x8000  #//Switch to CLK_MIPS to mipspll_vco

    jr          ra
    nop

#ifdef CONFIG_EMMC_BOOT
#-------------------------------------------------------------------------------------------------
# BOOT_CopyEmmcHeader
# @param  None
# @return None
# @note   Copy Chunk Header from EMMC to DRAM
#-------------------------------------------------------------------------------------------------
#define         EMMC_HEADER_SIZE    0x0002              #//Size = 1KB
#define         EMMC_HEADER_ADDR    0x80200000
#define         EMMC_MAX_BLK_CNT    4095

BOOT_CopyEmmcHeader:
    li          t3, (EMMC_HEADER_ADDR >> 3)
    li          t2, EMMC_HEADER_SIZE                    #//BLOCK CNT

    lui         t0, (REG_MIU_ADDR_L >> 16)
    srl         t1, t3, 16
    sw          t1, ((REG_MIU_ADDR_L & 0xFFFF) - 4)(t0) #//Load miu address high nibble
    and         t1, t3, 0xFFFF
    sw          t1, (REG_MIU_ADDR_L & 0xFFFF)(t0)       #//Load low nibble

    lui         t0,  (REG_JOB_BL_CNT >> 16)
    sw          t2, (REG_JOB_BL_CNT & 0xFFFF)(t0)

    STG2_BLK_R

    li          t7, EMMC_HEADER_ADDR
    lw          t0, 4(t7)                               #//RAM_START
    lw          t1, 8(t7)                               #//RAM_END
    sub         t2, t1, t0                              #//RAM_SIZE = RAM_END-RAM_START
    srl         t2, t2, 9                               #//SIZE = (RAM_SIZE/512)+1
    add         t2, t2, 1                               #//Convert byte size to sector count
    srl         t3, t0, 3                               #//RAM_START/miu_length convert to miu address
    lw          t6, 16(t7)                              #//AM_ENTRY
    jr          ra
    nop

#-------------------------------------------------------------------------------------------------
# BOOT_CopyEmmcUboot
# @param  None
# t3 : FCIE DMA ADDRESS
# t2 : JOB_BL_CNT
# @return None
# @note   Copy Uboot binary from EMMC to DRAM
#-------------------------------------------------------------------------------------------------
BOOT_CopyEmmcUboot:

    lui         t0, (REG_MIU_ADDR_L >> 16)
    srl         t1, t3, 16
    sw          t1, ((REG_MIU_ADDR_L & 0xFFFF) - 4)(t0) #//Load high nibble
    and         t1, t3, 0xFFFF
    sw          t1, (REG_MIU_ADDR_L & 0xFFFF)(t0)       #//Load low nibble

    bgt         t2, EMMC_MAX_BLK_CNT, GRT_MAX_CNT
    nop
    lui         t0, (REG_JOB_BL_CNT >> 16)
    sw          t2, (REG_JOB_BL_CNT & 0xFFFF)(t0)
    lui         t2, 0
    j           SEND_STG2_BLK
    nop

GRT_MAX_CNT:
    WREG        REG_JOB_BL_CNT, EMMC_MAX_BLK_CNT
    sub         t2, EMMC_MAX_BLK_CNT

SEND_STG2_BLK:
    STG2_BLK_R
    beqz        t2, SEND_BLK_END
    nop
    RREG        t1, REG_JOB_BL_CNT
    srl         t1, 9
    add         t3, t1
    j           BOOT_CopyEmmcUboot
    nop

SEND_BLK_END:
    WREG        REG_BOOT_CONFIG, 0x0002                 #//Set EMMC boot operation end

    jr          ra
    nop

#else
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

#endif

#-------------------------------------------------------------------------------------------------
# BootRomEnableAccessMiu
# @param  None
# @return None
# @note   Enable to access MIU
#-------------------------------------------------------------------------------------------------
LEAF(BootRomEnableAccessMiu)

    WREG        (0xBF000000 + (0x002BC4 << 1)), 0x0004      #//Set XDATA2MIU read Priority
    WREG        (0xBF000000 + (0x002BC6 << 1)), 0x3c11      #//Set the low bound address of MCU XDATA mapping to MIU (Unit: 1K-Byte)
    WREG        (0xBF000000 + (0x002BC8 << 1)), 0x0010      #//Set the low byte address to access xdata from MIU. The granularity is 64k bytes
    WREG        (0xBF000000 + (0x002BCA << 1)), 0x403c      #//Set the low bound address of MCU XDATA mapping to MIU (Unit: 1K-Byte)
    WREG        (0xBF000000 + (0x002BCC << 1)), 0x0101      #//Set the low byte address to access xdata from MIU. The granularity is 4k bytes.

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

    WREG        (0xBF000000 + (0x000E12 << 1)), 0x0800
    WREG        (0xBF000000 + (0x101EA6 << 1)), 0x2104
    WREG        (0xBF000000 + (0x10098C << 1)), 0x0083
    WREG        (0xBF000000 + (0x100980 << 1)), 0x0013
    WREG        (0xBF000000 + (0x100984 << 1)), 0x0000
    WREG        (0xBF000000 + (0x100988 << 1)), 0x0000
    WREG        (0xBF000000 + (0x10098C << 1)), 0x0003
    WREG        (0xBF000000 + (0x100988 << 1)), 0x0000
    WREG        (0xBF000000 + (0x100988 << 1)), 0x0007
    WREG        (0xBF000000 + (0x003008 << 1)), 0x0000
    WREG        (0xBF000000 + (0x00300A << 1)), 0x0000

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

    WREG        (0xBF000000 + (0x100B26 << 1)), 0x0C01      #//Set CLK_UART0 to 123Mhz

.if (BOOTINFO_UART0_ENABLE == 1)
    RREG        t3, (0xBF000000 + (0x000E12 << 1))          #//Enable UART Rx via PAD_DDCA for dig_mux
    ori         t3, t3, 0x0800
    sw          t3, (0xBF000000 + (0x000E12 << 1))

    RREG        t3, (0xBF000000 + (0x101EA6 << 1))          #//Select UART0 source to PIU UART0
    or          t3, t3, 0x0004
    sw          t3, (0xBF000000 + (0x101EA6 << 1))

.endif

.if (BOOTINFO_UART2_ENABLE == 1)
    RREG        t3, (0xBF000000 + (0x101EA6 << 1))          #//Select UART2 source to PIU UART0
    ori         t3, t3, 0x0400
    sw          t3, (0xBF000000 + (0x101EA6 << 1))

    WREG        (0xBF000000 + (0x101EA8 << 1)), 0x0000      #//Set UART4 source to None

    RREG        t3, (0xBF000000 + (0x101E04 << 1))          #//Set third UART mode: RX2/TX2 uses PAD_UART_RX2/PAD_UART_TX2
    ori         t3, t3, 0x0800
    sw          t3, (0xBF000000 + (0x101E04 << 1))
.endif

    RREG        t3, (0xBF000000 + (0x10098C << 1))           #//Enable Divisor Latch Access
    ori         t3, t3, 0x0080
    sw          t3, (0xBF000000 + (0x10098C << 1))

    WREG        (0xBF000000 + (0x100980 << 1)), UART_DIVISOR_L   #//Set Divisor Latch LSB
    WREG        (0xBF000000 + (0x100984 << 1)), UART_DIVISOR_H   #//Set Divisor Latch MSB

    RREG        t3, (0xBF000000 + (0x10098C << 1))           #//Disable Divisor Latch Access
    and         t3, t3, 0xFF7F
    sw          t3, (0xBF000000 + (0x10098C << 1))

    WREG        (0xBF000000 + (0x100988 << 1)), 0x0000
    WREG        (0xBF000000 + (0x100988 << 1)), 0x0007       #//Enable FIFO and Clear TX/RX FIFO

    WREG        (0xBF000000 + (0x10098C << 1)), 0x0000
    WREG        (0xBF000000 + (0x10098C << 1)), 0x0003       #//8-bit Data / 1-bit Stop / No Parity Bit
    WREG        (0xBF000000 + (0x100990 << 1)), 0x0000       #//Set DTS/RTS to 1
    WREG        (0xBF000000 + (0x100984 << 1)), 0x0000       #//Disable Interrupt

    DPUTK        'U'
    DPUTK        'A'
    DPUTK        'R'
    DPUTK        'T'
    DPUTK        '_'
    DPUTK        '1'
    DPUTK        '1'
    DPUTK        '5'
    DPUTK        '2'
    DPUTK        '0'
    DPUTK        '0'

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

    lw      t1, (0xBF000000 + (0x0101886 << 1))
    or      t1, t1, (0x01 << 5)
    sw      t1, (0xBF000000 + (0x101886 << 1))

    lw      t1, (0xBF000000 + (0x00012E << 1))
    or      t1, t1, (0x01 << 0)
    sw      t1, (0xBF000000 + (0x00012E << 1))

    lw      t1, (0xBF000000 + (0x10012E << 1))
    or      t1, t1, (0x01 << 0)
    sw      t1, (0xBF000000 + (0x10012E << 1))

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
