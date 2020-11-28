################################################################################
#
# Copyright (c) 2006-2007 MStar Semiconductor, Inc.
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

#define RIUBASE_PM              0xBF000000
#define RIUBASE_NONPM           0xBF200000
#define RIUBASE_NONPM_EXT12     0xBF240000  #//Support Bank 0x12XX

    .text
    .set        noreorder

#-------------------------------------------------------------------------------------------------
# BOOTRAM_Entry:
# @param  None
# @return None
# @note   Entry point of BootRam code
#-------------------------------------------------------------------------------------------------
    .globl      BOOTRAM_ROM_Entry
BOOTRAM_ROM_Entry:

    DBGREG       0x1000

    DBGREG       0x0005

    # Clear bss section
    bal          BOOTRAM_InitBss
    nop

    #// Enable 8051 to access MIU for MStar TV Tool
    bal         BootRomEnableAccessMiu
    nop

    #//Configure PAD top for MUX and GPIO (e.g. DDR power)
    la           a3, MDrv_WriteRegMaskTbl
    lui          a0, %hi(padInitTbl + 10)
    ori          a0, %lo(padInitTbl + 10)
    jal          a3
    nop

    bal         BootRomInitFpu
    nop

.if (ENABLE_MIU1 == 1)
    #//Initial related settings of MIU1
    la           a3, BootInitMiu1
    jal          a3
    nop
.endif

#ifdef CONFIG_MSTAR_EDINBURGH
    #//Init Edinburgh
    bal         BOOT_InitEdinburgh
    nop
#endif

#ifdef CONFIG_CPU_1008MHZ
    #//Trim VID from efuse 
    bal         BootRomTrimVid
    nop
#elif defined CONFIG_CPU_756MHZ
    #//Trim VID low from efuse 
    bal         BootRomTrimVidLow
    nop
#endif

    # Copy data section from sram to dram
    bal          BOOTRAM_CopyData
    nop
    #//Trim Mhl Cbus from efuse 
    bal         BootRomTrimMhlCbus
    nop

    #//Trim Emac Ephy from efuse 
    bal         BootRomTrimEmacEphy
    nop

    #// Speed up NAND Clock
    la			a3, nand_clock_setting
    la			a0, 1
    jal			a3
    nop

    #//Load chunker header
    la           a3, drvNAND_LoaduBoot
    la           a0, CONFIG_UBOOT_LOADADDR
    la           a1, 0x400
    jal          a3
    nop

#if defined(CONFIG_MSTAR_AUTHEN_ENABLE)
    #//Authenticate chunk header
    la           a0, CONFIG_UBOOT_LOADADDR
    la           a1, 0x2f0                 
    la           a2, CONFIG_UBOOT_LOADADDR + 0x300
    la           a3, 0x0

    la           t3, MDrv_AESDMA_SecureMain
    jal          t3
    nop
    
    #//If authentication fail, jump to reset whole system
    bne         v0, 0x0001, BootRam_AuthFailLoop
    nop
#endif

    #//Load Uboot
    la           a0, CONFIG_UBOOT_LOADADDR
    lw           a1, (a0)                         #// UBOOT_ROM_START in MBOOT PARTITION
    lw           a2, 4(a0)                        #// UBOOT_RAM_START
    lw           a3, 8(a0)                        #// UBOOT_RAM_END
    sub          t0, a3, a2                       #// UBOOT_RAM_END - UBOOT_RAM_START

    la           a3, drvNAND_LoaduBoot
    sub          a0, a2, a1
    add          a1, t0, a1
    
     
#if defined(CONFIG_MSTAR_AUTHEN_ENABLE)
    #//Increment load code size to get secure info.
    addi         a1, a1, 0x200                    #// LOAD SIZE
#endif

    #la           a1, 0x200000
    jal          a3
    nop 

    PUTC         'U'

#if defined(CONFIG_MSTAR_AUTHEN_ENABLE)
    #//Authenticate U-BOOT
    la           a0, CONFIG_UBOOT_LOADADDR
    lw           a2, 4(a0)                         #// UBOOT_RAM_START
    lw           a3, 8(a0)                         #// UBOOT_RAM_END
    sub          a1, a3, a2                        #// UBOOT_RAM_END - UBOOT_RAM_START
    la           a2, CONFIG_UBOOT_LOADADDR + 0x10
    add          a2, a2, a1
    la           a3, 0x0


    la           t3, MDrv_AESDMA_SecureMain
    jal          t3
    nop
    
    #//If authentication fail, jump to reset whole system
    bne         v0, 0x0001, BootRam_AuthFailLoop
    nop
#endif

    bal         BOOT_InitTSPClkMux
    nop

    #// Enable PM
		# WREG      	0xBF001D48, 0x0055   #// Luke add

    #//Jump to The Entry Point of UBoot
    la           a0, CONFIG_UBOOT_LOADADDR - 0x400 #// Chunker header
    lw           a1, 16(a0)                        #// UBOOT_RAM_ENTRY
    
	jr           a1          
    nop

#ifdef CONFIG_MSTAR_AUTHEN_ENABLE
BootRam_AuthFailLoop:
    PUTC        'F'
    DELAYUS     100000
	b           BootRam_AuthFailLoop
    nop
#endif

BOOTRAM_CopyUboot:
#//-------------------------------------------------------------------------------------------------
#// Copy Data Section to DRAM
#//-------------------------------------------------------------------------------------------------
    la	        t3, 0xa75f0180
    la	        t4, 0x875f0180
    la	        t5, 0x200000

_CopyData:
    lw          t6, 0(t3)
    sw          t6, 0(t4)

    add         t3, t3, 4
    add         t4, t4, 4
    add         t5, t5, -4

    bnez        t5, _CopyData
    nop

    jr          ra
    nop
#-------------------------------------------------------------------------------------------------
# BOOTRAM_CopyData
# @param  None
# @return None
# @note   Power On Sequence for Chip
#-------------------------------------------------------------------------------------------------
BOOTRAM_CopyData:
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
# BOOTRAM_InitBss
# @param  None
# @return None
# @note   Power On Sequence for Chip
#-------------------------------------------------------------------------------------------------
BOOTRAM_InitBss:
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
# BOOT_InitTSPClkMux  Init TSP clk de-glitch mux
# @param  None
# @return None
# @note   do enable 172MHz for TSP and AESDMA
#-------------------------------------------------------------------------------------------------
BOOT_InitTSPClkMux:

    RREG        t9, 0xBF2016A8		  #// clk_tsp_sel:0x100B54[4:0] = 5'b0
    and         t9, t9, 0xFFE0
    REG_C2M     t9, 0xBF2016A8

    RREG        t9, 0xBF2017E0        #// clk_sw_tsp_clk:0x100BF0[0] = 1'b1 
    or          t9, t9, 0x0001
    REG_C2M     t9, 0xBF2017E0

    RREG        t9, 0xBF2226BC        #// bootsram_access_sel:0x11135E[4] = 1'b0
    and         t9, t9, 0xFFEF
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
# BOOTRAM_Pad
# @param  None
# @return None
# @note   Pad with zeros (Reserve SIZE_BOOTRAM_RESERVED Bytes for bootram)
#-------------------------------------------------------------------------------------------------
    .org        (SIZE_BOOTRAM_RESERVED-4)
    .word       0
