################################################################################
#
# Copyright (c) 2006-2009 MStar Semiconductor, Inc.
# All rights reserved.
#
# Unless otherwise stipulated in writing, any and all information contained
# herein regardless in any format shall remain the sole proprietary of
# MStar Semiconductor Inc. and be kept in strict confidence
# ("MStar Confidential Information") by the recipient.
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
    .globl      BOOT_Entry

BOOT_Entry:

    #//initalize the PIU timer1 to measure boot time
    WREG        (0xbf000000 + (0x003044 << 1)), 0xffff
    WREG        (0xbf000000 + (0x003046 << 1)), 0xffff
    WREG        (0xbf000000 + (0x003040 << 1)), 0x0000
    WREG        (0xbf000000 + (0x003040 << 1)), 0x0001
    #//clean PIU timer0
    WREG        (0xbf000000 + (0x003020 << 1)), 0x0000

ROM_Start:

    #//Clear status in cause register
    li          t1, M_CauseIV
    mtc0        t1, C0_Cause
    nop

    #//Set WDT period maximum value to 0 to disable watchdog timer
    sw          zero, (0xbf000000 + (0x3008 << 1))
    sw          zero, (0xbf000000 + (0x300A << 1))

    #//Initialize CPU Registers
    bal         BootInitCpuRegister
    nop

    DBGREG      0x0001

    #//Jump to Entry of BOOTROM
    la          ra, BOOTROM_Entry
    jr          ra
    nop

#-------------------------------------------------------------------------------------------------
# BootInitCpuRegister
# @param  None
# @return None
# @note   Init CPU Registers
#-------------------------------------------------------------------------------------------------
BootInitCpuRegister:

	#//Initial setting in watch register
	li          t0, 0x07
	mtc0        t0, C0_WatchLo
    nop

	mtc0	    zero, C0_WatchHi
	nop

	#//Disable interrupts and KSU field (power up issue)
	mfc0        t0, C0_Status
	nop

    #//Check status of Non-Maskable Interrupt
    and         t1, t0, M_StatusNMI
    bnez        t1, 1f
    nop

    #//Disable interrupt and set base mode to kernel mode
	and	        t1, t0, ~(M_StatusIE | M_StatusKSU)
	mtc0	    t1, C0_Status
	nop

#if 0
	#//Don't touch cause if we got here from an NMI
	mfc0        t0, C0_Status
	nop

    and         t1, t0, M_StatusNMI
    bnez        t1, 1f
    nop
#endif

	#//Clear status in cause register
	#//IV = 1: Use the special interrupt vector
	li	        t1, M_CauseIV
	mtc0	    t1, C0_Cause

1:
	nop

#//================================================================================================
    mtc0        zero, C0_Count
    nop

    mtc0        zero, C0_Compare
    nop

#//================================================================================================

	#//Set attribute in config register
	mfc0        t0, C0_Config
	nop

	and	        t0, t0, CONFIG0_MIPS32_64_MSK
	or          t0, t0, ((K_CacheAttrCN << S_ConfigK23) | (K_CacheAttrCN << S_ConfigKU) | (M_ConfigMM))

    #//Set merging allowed
    #//Set the cacheability of kuseg, usegm kseg2 and kseg3 to "Cacheable, noncoherent, write-back, write allocate"
	mtc0        t0, C0_Config
	nop

    #//Enable Externalize Sync
    mfc0        t0, C0_Config, 7
    nop

    or          t0, t0, 0x0100

    mtc0        t0, C0_Config, 7
    nop

#//================================================================================================

    #//Set Status Register
	mfc0        t0, C0_Status
	nop

	and         t0, t0, STATUS_MIPS32_64_MSK
	or          t0, t0, STATUS_MIPS34K

	mtc0	    t0, C0_Status                   #//Disable CorExtend block?
	nop

#//================================================================================================
    jr          ra
    nop

#-------------------------------------------------------------------------------------------------
# BOOT_ExceptionHandler
# @param  None
# @return None
# @note   Exception handler for general exception or decompression failure at boot code
#-------------------------------------------------------------------------------------------------

    #//0xBFC00380 if StatusBEV=1 StatusEXL=0 CauseIV=0
    .org        0x0380
    .globl      BOOT_ExceptionHandler
BOOT_ExceptionHandler:

    .set        noat

.if (SUPPORT_POWER_SAVING)

    #//Check status of power saving in standby mode
    #//Related flag was definied in power saving driver
    lw          t1, REG_TOP_POWER_STATUS    #//I2S_GPIO_OEN[11:0]
    nop

    li          t0, 0x03
    and         t1, t1, t0
    bne         t1, t0, _ExceptionHandlerReset
    nop

    #//Set the location of exception vectors to Normal
    mfc0        t0, C0_Status
    nop

    li          t1, ~M_StatusBEV
    and         t0, t0, t1

    mtc0        t0, C0_Status
    nop

    eret
    nop

_ExceptionHandlerReset:

.endif  #//SUPPORT_POWER_SAVING

.if !(BOOT_DEBUG_VERSION)

    la          t0, 0xBF001C00

    li          t1, 0xB8D3
    sw          t1, 0xB0(t0)                #//Set password of MIPS to 0xB8D3

    lw          t1, 0xA4(t0)
    nop

    and         t1, t1, 0xFBFF              #//Trigger MIPS Software Reset (Active High)
    sw          t1, 0xA4(t0)

    or          t1, t1, 0x0400              #//Trigger MIPS Software Reset (Active High)
    sw          t1, 0xA4(t0)

.endif  #//BOOT_DEBUG_VERSION

_ExceptionHandlerLoop:
    j           _ExceptionHandlerLoop
    nop

    .set        at


.if (SUPPORT_POWER_SAVING)
#-------------------------------------------------------------------------------------------------
# BOOT_CPU_DRAM_Standby
# @param  None
# @return None
# @note   Let DRAM & CPU enter standby mode
#-------------------------------------------------------------------------------------------------
    .org        0xa80      # Cannot change it, _MDrv_Power_EnterPowerSavingMode will call it.
BOOT_CPU_DRAM_Standby:

    #//Enable Interrupt
    mfc0        t0, C0_Status
    nop

    or          t0, t0, M_StatusIE

    mtc0        t0, C0_Status
    nop

    #//Enter MIPS power-down state
    wait
    nop

    jr          ra
    nop

    .set        at

.endif  #//SUPPORT_POWER_SAVING


#-------------------------------------------------------------------------------------------------
# BOOT_Pad
# @param  None
# @return None
# @note   Pad with zeros (Reserve SIZE_BOOT_RESERVED Bytes for boot)
#-------------------------------------------------------------------------------------------------
    .org        (SIZE_BOOT_RESERVED - 4)
    .word       0
