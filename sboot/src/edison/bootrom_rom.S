################################################################################
#
# Copyright (c) 2006-2009 MStar Semiconductor, Inc.
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
#include "macro.inc"
#include "drv_uart.inc"
    .text

BOOT_MESSAGE_AC_ON: .short  '\r', '\n', 'A', 'C', '_', 'O', 'N', '\r', '\n', 0x00
BOOT_MESSAGE_DC_ON: .short  '\r', '\n', 'D', 'C', '_', 'O', 'N', '\r', '\n', 0x00

#-------------------------------------------------------------------------------------------------
# BOOTROM_Entry:
# @param  None
# @return None
# @note   Entry point of Boot code
#-------------------------------------------------------------------------------------------------
    .globl  BOOTROM_Entry
BOOTROM_Entry:

    @//DBGREG  0x0002
    @//XIU Time out
    WREG  0x1f000250, 0xFFFF
    WREG  0x1f000254, 0xFFFF
    WREG  0x1f000264, 0xFFFF
		
    bl 		 BootRom_PLLRecovery
    @//DBGREG  0x0003

    bl 		BootRom_EnableMcuAccess
    @//DBGREG  0x0004

    @// AVD write control BIT4=1 Disable (for STR)
    RREG        r8, (MS_BUS_RIU_ADDR + (0x10362A << 1))
    orr         r8, r8, #0x0010
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x10362A << 1))

    bl      BootRom_InitPll
    @//DBGREG  0x0005

    bl      BootRom_InitClock
    @//DBGREG  0x0006

    #ifdef CONFIG_MSTAR_VID_ENABLE
    ldr r0, =padInitTbl
    add r0, r0, #10
    bl MDrv_WriteRegMaskTbl
    bl BootRom_InitVid
    #endif
    
    bl      BootRom_SetClockRatio
    @//DBGREG  0x0007

    @//ARM_INIT
    @//DBGREG  0x0008

    bl      BootRom_InitUart
    @//DBGREG  0x0009


    @//Initial related settings of MIU

    WREG    0x1F201674, 0x0808  @ turn on miu clock

    RREG        r0, (MS_BUS_RIU_ADDR + (0x0E70 << 1))     @//Disable Divisor Latch Access
    orr         r0, r0, #0x00FF
    ldr         r1, =0xFFFF
    cmp         r0, r1
    beq         BootRom_Str_AcFlow

    #ifdef CONFIG_MSTAR_STR_ENABLE
    ldr         r0, =_ld_program_reload_addr
    ldr         r1, =CONFIG_EMMC_HASH1_STR_SIZE
    ldr         r2, =(CONFIG_EMMC_HASH0_SIZE + CONFIG_EMMC_HASH1_SIZE + CONFIG_EMMC_HASH1_MIU_SIZE)
    mov         r2, r2, lsr #9
    bl          eMMC_LoadImages

    #ifdef CONFIG_MSTAR_AUTHEN_ENABLE
    ldr         r0, =_ld_program_reload_addr                                 @//Set the starting address of HASH for Authentication
    ldr         r1, =0x1200              	                                 @//Set the HASH size for Authentication
    ldr         r2, =_ld_program_reload_addr + 0x1300                        @//Set the starting address of SIG for Authentication
    ldr         r3, =0x1
    bl          MDrv_AESDMA_SecureMain

    @//If authentication fail, jump to reset whole system
    cmp         r0, #1
    bne         BootRom_AuthenticationFail
    #endif

    bl          BootRom_InitMiu_STR

    #else
    DPUTK_STR   BOOT_MESSAGE_DC_ON
    b           BootRom_Str_InitMiu
    #endif
    b           BootRom_Str_Exit

BootRom_Str_AcFlow:
    DPUTK_STR   BOOT_MESSAGE_AC_ON

BootRom_Str_InitMiu:

    ldr         r0, =_ld_program_reload_addr
    ldr         r1, =CONFIG_EMMC_HASH1_MIU_SIZE
    ldr         r2, =(CONFIG_EMMC_HASH0_SIZE + CONFIG_EMMC_HASH1_SIZE)
    mov         r2, r2, lsr #9
    bl          eMMC_LoadImages

    #ifdef CONFIG_MSTAR_AUTHEN_ENABLE
    ldr         r0, =_ld_program_reload_addr                                 @//Set the starting address of HASH for Authentication
    ldr         r1, =0x1200                             	                 @//Set the HASH size for Authentication
    ldr         r2, =_ld_program_reload_addr + 0x1300                        @//Set the starting address of SIG for Authentication
    ldr         r3, =0x1
    bl          MDrv_AESDMA_SecureMain

    @//If authentication fail, jump to reset whole system
    cmp         r0, #1
    bne         BootRom_AuthenticationFail
    #endif

    bl          BootRom_InitMiu

BootRom_Str_Exit:

    WREG_B    0x1F203104, 0x84      @switch L3 CLK to MIU2X

    @//DBGREG  0x000B

    ldr         r0, =CONFIG_BOOTRAM_LOADADDR
    ldr         r1, =CONFIG_EMMC_BOOTRAM_SIZE
    ldr         r2, =CONFIG_EMMC_BOOTRAM_ADDRESS
    mov         r2, r2, lsr #9
    bl          eMMC_LoadImages
    @//DBGREG  0x000C

    #ifdef CONFIG_MSTAR_AUTHEN_ENABLE
    ldr         r0, =CONFIG_BOOTRAM_LOADADDR                     @//Set the starting address of HASH2 for Authentication
    ldr         r1, =SIZE_BOOT_HASH2            	             @//Set the HASH2 size for Authentication
    ldr         r2, =CONFIG_BOOTRAM_LOADADDR + 0x2300            @//Set the starting address of SIG2 for Authentication
    ldr         r3, =0x0
    bl          MDrv_AESDMA_SecureMain

    @//If authentication fail, jump to reset whole system
    cmp         r0, #1
    bne         BootRom_AuthenticationFail
    #endif
    @//DBGREG  0x000D

    #ifdef CONFIG_MSTAR_STR_ENABLE
    @//bl          BootRom_StrEntry
    #endif
    
BootRom_AuthHash2Exit:
    # Jump to BOOTRAM_Entry
    ldr   pc, =BOOTRAM_Entry

@//-------------------------------------------------------------------------------------------------
@// BootRom_WriteUartCharactor
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .globl      BootRom_WriteUartCharactor
BootRom_WriteUartCharactor:
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x100900 << 1))
    str         r0, [r12, #(0x80 << 1)]     @//REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x100980 << 1))
BootRom_WriteUartCharactor_Loop:
    ldr         r0, [r12, #(0x94 << 1)]     @//RREG        r0, (MS_BUS_RIU_ADDR + (0x100994 << 1))
    and         r0, r0, #0x0060
    cmp         r0, #0x0060
    bne         BootRom_WriteUartCharactor_Loop

    bx          lr

@//-------------------------------------------------------------------------------------------------
@// BootRom_WriteUartString
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .globl      BootRom_WriteUartString
BootRom_WriteUartString:

    ldrb        r11, [r0], #2
    and         r11, r11, #0xff
    cmp         r11, #0x00
    beq         BootRom_WriteUartString_Exit

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x100900 << 1))
    str         r11, [r12, #(0x80 << 1)]     @//REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x100980 << 1))
BootRom_WriteUartString_Loop:
    ldr         r11, [r12, #(0x94 << 1)]     @//RREG        r0, (MS_BUS_RIU_ADDR + (0x100994 << 1))
    and         r11, r11, #0x60
    cmp         r11, #0x60
    bne         BootRom_WriteUartString_Loop
    b           BootRom_WriteUartString

BootRom_WriteUartString_Exit:

    bx          lr

#ifdef CONFIG_MSTAR_AUTHEN_ENABLE
BootRom_AuthenticationFail:
	b           BootRom_AuthenticationFail
#endif

