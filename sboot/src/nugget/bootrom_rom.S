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

    #DBGREG      0x0002
   
    #//Set PAD_PM_GPIO0 = 1 with the setting  0x0e1e[0]=0 , 0x0e20[0]=1
    WREG  0xBF001C3C, 0xFFFE        
    WREG  0xBF001C40, 0x0001
   
    # initalize the PIU timer1 to measure boot time
    WREG  0xBF006088, 0xFFFF
    WREG  0xBF00608C, 0xFFFF
    WREG  0xBF006080, 0x0000
    WREG  0xBF006080, 0x0001
    #clean PIU timer0
    WREG  0xBF006048, 0x0000
    WREG  0xBF00604C, 0x0000
    WREG  0xBF006040, 0x0000
    WREG  0xBF006040, 0x0000

    #DBGREG      0x0003

    #// Power-On Sequence
    bal         BootRomPowerOnSequence
    nop

    #DBGREG      0x0004

    # set stack pointer
    la          sp,  _stack_pointer     #//Set stack pointer

    #DBGREG      0x0006

	la			a0, CONFIG_BOOTRAM_LOADADDR
	la			a1, 0x8000
	bal			drvNAND_Load2ndBL
    nop

    #DBGREG      0x0007

#ifdef CONFIG_MSTAR_AUTHEN_ENABLE
    la           a0, CONFIG_BOOTRAM_LOADADDR
    la           a1, 0x2000                 
    la           a2, CONFIG_BOOTRAM_LOADADDR + 0x2300
    la           a3, 0x0

    bal          MDrv_AESDMA_SecureMain
    nop
    
    #//If authentication fail, jump to reset whole system
    bne         v0, 0x0001, BootRom_AuthFailLoop
    nop
#endif

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

    #DBGREG      0x0030

    #//Initial related settings of Clock
    bal         BootRomInitClock
    nop

    #DBGREG      0x0031

    DELAYUS     100
    
    #//Initial related settings of UART
    bal         BootInitUart
    nop

    #DBGREG      0x0032

    #//Initial related settings of cache
    bal         BootRomInitCache
    nop

    #DBGREG      0x0033

    #//Disable ADV before MIU initiation
    bal     	BootRomDisableAvd
    nop

    #DBGREG      0x0034

    la          a0, _ld_program_reload_addr
    la          a1, _ld_miu_flow_flash_start
    la          a2, 0x1400
    bal         drvNAND_LoadBLOffset
    nop

#ifdef CONFIG_MSTAR_AUTHEN_ENABLE
    la           a0, _ld_program_reload_addr
    la           a1, 0x1000                 
    la           a2, _ld_program_reload_addr + 0x1300
    la           a3, 0x1

    bal          MDrv_AESDMA_SecureMain
    nop
    
    #//If authentication fail, jump to reset whole system
    bne         v0, 0x0001, BootRom_AuthFailLoop
    nop
#endif
  
  #//Initial related settings of MIU0
    bal     	BootInitMiu0
    nop


    #DBGREG      0x0035

#ifdef CONFIG_MSTAR_32BIT_RIU_MASK_ENABLE
    bal     	BootInitRiuBitMask
    nop
#endif

#ifndef CONFIG_MSTAR_TITANIA_BD_FPGA
    #//Initial related settings of SPI flash clock
    bal         BootRomInitSpiFlashClock
    nop

    #DBGREG      0x0036

    bal         BootRomChangeSpiFlashClock
    nop

    #DBGREG      0x0037
#endif

    #//Set clock ratio of OCP
    bal     	BootRomOcpClockRatio
    nop

    move        ra, k1
    jr          ra
    nop

#ifdef CONFIG_MSTAR_AUTHEN_ENABLE
BootRom_AuthFailLoop:
    PUTK        'F'
    #DELAYUS     100000
	b           BootRom_AuthFailLoop
    nop
#endif

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

    WREG      	0xBF201644, 0x0800
    DELAYUS     10
    WREG      	0xBF201644, 0x0000
    DELAYUS     10
    WREG      	0xBF201644, 0x8000      #//Switch to CLK_MIPS to mipspll_vco
    
    jr          ra
    nop

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

    #PUTK        'U'
    #PUTK        'A'
    #PUTK        'R'
    #PUTK        'T'
    #PUTK        '_'
    #PUTK        '1'
    #PUTK        '1'
    #PUTK        '5'
    #PUTK        '2'
    #PUTK        '0'
    #PUTK        '0'

    #PUTK        '\n'
    #PUTK        '\r'
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