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

#ifndef _BOARD_H_
#include "Board.h"
#endif

#ifndef _DRV_MIU_INIT_STR_H_
#include "drv_miu_init_str.h"
#endif

#ifndef _MIUSEL_EIFFEL_2MIU_H_
#include "MIUSEL_EIFFEL_2MIU.h"
#endif

    .text

    .global     BootRom_InitMiu_STR
BootRom_InitMiu_STR:

    mov         r13, lr

    PUTK        'S'
    PUTK        'T'
    PUTK        'R'
    PUTK        '_'
    PUTK        'D'
    PUTK        'C'
    PUTK        '_'
    PUTK        'O'
    PUTK        'N'
    PUTK        '\r'
    PUTK        '\n'

    @//  <1>  set OENZ =1
    @//bl Miu_str_oenz_enable

    DBGREG      0x0020

    WREG        (MS_BUS_RIU_ADDR + (0x110d00 << 1)), 0x0018
    WREG        (MS_BUS_RIU_ADDR + (0x110d80 << 1)), 0x0018
    DELAYUS     200                                         @//delay 200us

    WREG        (MS_BUS_RIU_ADDR + (0x110d00 << 1)), 0x0008
    WREG        (MS_BUS_RIU_ADDR + (0x110d80 << 1)), 0x0008
    DELAYUS     1000                                         @//delay 200us



#ifdef CONFIG_MSTAR_TITANIA_BD_FPGA

    WREG        (MS_BUS_RIU_ADDR + (0x003008 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x101ea0 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x002bc6 << 1)), 0x3c11
    WREG        (MS_BUS_RIU_ADDR + (0x002bca << 1)), 0x403c
    WREG        (MS_BUS_RIU_ADDR + (0x002bc4 << 1)), 0x0004
    WREG        (MS_BUS_RIU_ADDR + (0x101202 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x101202 << 1)), 0x0818
    WREG        (MS_BUS_RIU_ADDR + (0x101204 << 1)), 0x0185
    WREG        (MS_BUS_RIU_ADDR + (0x101206 << 1)), 0x0120
    WREG        (MS_BUS_RIU_ADDR + (0x101208 << 1)), 0x0833
    WREG        (MS_BUS_RIU_ADDR + (0x10120a << 1)), 0x0c33
    WREG        (MS_BUS_RIU_ADDR + (0x10120c << 1)), 0x7111
    WREG        (MS_BUS_RIU_ADDR + (0x10120e << 1)), 0x100e
    WREG        (MS_BUS_RIU_ADDR + (0x101210 << 1)), 0x0031
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c01
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c00
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0008
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000c
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000e
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x001f
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c08
    WREG        (MS_BUS_RIU_ADDR + (0x101228 << 1)), 0x4000
    WREG        (MS_BUS_RIU_ADDR + (0x10123a << 1)), 0x0001
    WREG        (MS_BUS_RIU_ADDR + (0x10123c << 1)), 0x03ff

_CheckDramData:

    RREG        r0, (MS_BUS_RIU_ADDR + (0x101200 << 1))
    and         r0, r0, #0x8000
    cmp         r0, #0
    beq         _CheckDramData

#else

@// WREG        (MS_BUS_RIU_ADDR + (0x113BEC << 1)), 0x8000 @//enable dramobf

    @//MIU0 Software reset
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0000 @//hold miu_0
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c01 @//miu_sw_rst
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0e00 @//
    WREG        (MS_BUS_RIU_ADDR + (0x101202 << 1)), 0xf000 @// (For STR) disable all ddr bus out

    @//MIU0 Request mask
    WREG        (MS_BUS_RIU_ADDR + (0x1012F8 << 1)), 0x8000
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0xFFFE @//mask group0
    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0xFFFF @//mask group1
    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0xFFFF @//mask group2
    WREG        (MS_BUS_RIU_ADDR + (0x1012A6 << 1)), 0xFFFF @//mask group3

#ifndef CONFIG_MIU1_DRAM_NONE
    @//MIU1 Software reset
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0000 @//hold miu_0
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0a01 @//
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0a00 @//
    WREG        (MS_BUS_RIU_ADDR + (0x100602 << 1)), 0xf000 @// (For STR) disable all ddr bus out

    @//MIU1 Request mask
    WREG        (MS_BUS_RIU_ADDR + (0x1006F8 << 1)), 0x8000
    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x7FFE @//mask group0
    WREG        (MS_BUS_RIU_ADDR + (0x100666 << 1)), 0xFFFF @//mask group1
    WREG        (MS_BUS_RIU_ADDR + (0x100686 << 1)), 0xFFFF @//mask group2
    WREG        (MS_BUS_RIU_ADDR + (0x1006A6 << 1)), 0xFFFF @//mask group3
#endif

    bl  Reset_AVD_str

    ldr         r0, =MIU0_DDR_Init_STR
    bl          MDrv_WriteRegTbl32

    DELAYUS     1000

    DBGREG      0x0021

    @//Enable MIU0
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0a01
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0a00

    DELAYUS     200                                         @//delay 200us

    WREG        (MS_BUS_RIU_ADDR + (0x110d00 << 1)), 0x0208
    WREG        (MS_BUS_RIU_ADDR + (0x110d02 << 1)), 0xAAAA

    DBGREG      0x0023

#ifndef CONFIG_MIU1_DRAM_NONE

    ldr         r0, =MIU1_DDR_Init_STR
    bl          MDrv_WriteRegTbl32

    DELAYUS     1000

    @//Enable MIU1
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0a01
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0a00

    DELAYUS     200                                         @//delay 200us


    WREG        (MS_BUS_RIU_ADDR + (0x110d80 << 1)), 0x0208
    WREG        (MS_BUS_RIU_ADDR + (0x110d82 << 1)), 0xAAAA
#endif

@// bl          EnableMiuSsc

    DBGREG      0x0024



    @//MIU0 INIT Cycle
    @//WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0000 @//hold miu_0
    @//WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0008 @//DRAM reset

    DELAYUS     500                                         @//delay 500us

    @//WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000c @//DRAM reset+CS
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000e @//DRAM reset+CS+CKE

    DELAYUS     500                                         @//delay 500us

    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x001f @//DRAM reset+CS+CKE+auto cycle+ODE

    DBGREG      0x0025


#ifndef CONFIG_MIU1_DRAM_NONE
    @//MIU1 INIT Cycle
    @//WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0000 @//hold miu_0
    @//WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0008 @//DRAM reset

    DELAYUS     500                                         @//delay 500us

    @//WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x000c @//DRAM reset+CS
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x000e @//DRAM reset+CS+CKE

    DELAYUS     500                                         @//delay 500us

    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x001f @//DRAM reset+CS+CKE+auto cycle+ODE
#endif
@//-----------------------------------STR--------------------------------------

    DBGREG      0x0026

    bl  Miu_auto_phase_str


    bl  Enter_DDR_RefreshMode

    bl  Miu_str_oenz_disable


    WREG        (MS_BUS_RIU_ADDR + (0x110D54 <<1 )), 0x0000 @//ATOP_PD off
#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x110Dd4 <<1 )), 0x0000 @//ATOP_PD off
#endif

    @//rx enable
#if defined(CONFIG_MSTAR_BD_MST129F_D01A_S_EAGLE) && defined(CONFIG_MSTAR_ASIC_EMULATION_ENABLE)
    WREG        (MS_BUS_RIU_ADDR + (0x110d08 << 1)), 0x403f
#else
    WREG        (MS_BUS_RIU_ADDR + (0x110d08 << 1)), 0x003f
#endif
#ifndef CONFIG_MIU1_DRAM_NONE
    @//rx enable
#if defined(CONFIG_MSTAR_BD_MST129F_D01A_S_EAGLE) && defined(CONFIG_MSTAR_ASIC_EMULATION_ENABLE)
    WREG        (MS_BUS_RIU_ADDR + (0x110d88 << 1)), 0x403f
#else
    WREG        (MS_BUS_RIU_ADDR + (0x110d88 << 1)), 0x003f
#endif
#endif
    bl  Exit_DDR_RefreshMode

    DBGREG      0x2626

    DELAYUS     300                                         @//delay 300us

    bl  Push_Dram_STR

@//-----------------------------------STR--------------------------------------

    DBGREG      0x0027

#if !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    bl          MIU_Init_Priority

    bl          MIU_Set_Group_Priority
#endif

    DBGREG      0x0028
    @//open all MIU0 request mask (All IP can access MIU resource)
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x0000 @//Mask MIU0_group_0
    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0x0000 @//Mask MIU0_group_1
    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0x0000 @//Mask MIU0_group_2
    WREG        (MS_BUS_RIU_ADDR + (0x1012a6 << 1)), 0x0000 @//Mask MIU0_group_3

#ifndef CONFIG_MIU1_DRAM_NONE
    @//open all MIU1 request mask (All IP can access MIU resource)
    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x0000 @//Mask MIU1_group_0
    WREG        (MS_BUS_RIU_ADDR + (0x100666 << 1)), 0x0000 @//Mask MIU1_group_1
    WREG        (MS_BUS_RIU_ADDR + (0x100686 << 1)), 0x0000 @//Mask MIU1_group_2
    WREG        (MS_BUS_RIU_ADDR + (0x1006a6 << 1)), 0x0000 @//Mask MIU1_group_3


    @//all MIU1 IP select MIU0 in bringup
    WREG        (MS_BUS_RIU_ADDR + (0x1006f0 << 1)), 0x4E88 @//0x7fff
    WREG        (MS_BUS_RIU_ADDR + (0x1006f2 << 1)), 0x0000 @//0xffff
    WREG        (MS_BUS_RIU_ADDR + (0x1006f4 << 1)), 0x0000 @//0xffff
    WREG        (MS_BUS_RIU_ADDR + (0x1006f6 << 1)), 0x0120 @//0xffff
#endif

    WREG        (MS_BUS_RIU_ADDR + (0x10121e <<1 )), 0x0a08 @//SW initial done and turn on arbitor
    WREG        (MS_BUS_RIU_ADDR + (0x1012fc <<1 )), 0x4400

#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x10061e <<1 )), 0x0a08 @//SW initial done and turn on arbitor
    WREG        (MS_BUS_RIU_ADDR + (0x1006fc <<1 )), 0x4400
#endif

    DBGREG      0x0029

    WREG        (MS_BUS_RIU_ADDR + (0x101842 << 1)), 0x0000 @//Set MIU0 Size of MAU0
    WREG        (MS_BUS_RIU_ADDR + (0x101862 << 1)), 0x0000 @//Set MIU0 Size of MAU1

#endif

    mov         lr, r13
    bx          lr
    .size       BootRom_InitMiu_STR,.-BootRom_InitMiu_STR

@//-------------------------------------------------------------------------------------------------
@// Miu_str_oenz_enable
@// @param  None
@// @return None
@// @note   Miu_str_oenz_enable
@//-------------------------------------------------------------------------------------------------
Miu_str_oenz_enable:

    RREG        r8, (MS_BUS_RIU_ADDR + (0x101202 << 1))
    orr         r8, r8, #0xf000
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x101202 << 1))
#ifndef CONFIG_MIU1_DRAM_NONE
    RREG        r8, (MS_BUS_RIU_ADDR + (0x100602 << 1))
    orr         r8, r8, #0xf000
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x100602 << 1))
#endif
    bx          lr

@//-------------------------------------------------------------------------------------------------
@// Miu_str_oenz_disable
@// @param  None
@// @return None
@// @note   Miu_str_oenz_disable
@//-------------------------------------------------------------------------------------------------
Miu_str_oenz_disable:

    RREG        r8, (MS_BUS_RIU_ADDR + (0x101202 << 1))
    bic    r8, r8, #0xf000
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x101202 << 1))
#ifndef CONFIG_MIU1_DRAM_NONE
    RREG        r8, (MS_BUS_RIU_ADDR + (0x100602 << 1))
    bic    r8, r8, #0xf000
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x100602 << 1))
#endif
    bx          lr

@//-------------------------------------------------------------------------------------------------
@// Miu_auto_phase_str
@// @param  None
@// @return None
@// @note   Miu_auto_phase_str
@//-------------------------------------------------------------------------------------------------
Miu_auto_phase_str:

    @ // Re write MIU auto phase
    RREG        r8, (MS_BUS_RIU_ADDR + (0x0EA4 << 1))
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x110D6E << 1))
#ifndef CONFIG_MIU1_DRAM_NONE
    RREG        r8, (MS_BUS_RIU_ADDR + (0x0EA6 << 1))
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x110DEE << 1))
#endif
    bx          lr

@//-------------------------------------------------------------------------------------------------
@// Enter_DDR_RefreshMode
@// @param  None
@// @return None
@// @note   Enter_DDR_RefreshMode
@//-------------------------------------------------------------------------------------------------

Enter_DDR_RefreshMode:

    @// [DDR3][enter] <MIU0>
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000

    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x7FFE
    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x1012a6 << 1)), 0xFFFF

    WREG        (MS_BUS_RIU_ADDR + (0x101218 << 1)), 0x0400 @//reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x002F @//Bit[05]reg_auto_ref_off
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x042F @//trig precharge all
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x052F
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x022F @//trig refresh
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x032F
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x101206 << 1)), 0x1430 @//Bit[12]reg_cke_always_on

    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x202F

 #ifndef CONFIG_MIU1_DRAM_NONE
   @// [DDR3][enter] <MIU1>
    WREG        (MS_BUS_RIU_ADDR + (0x1006e0 << 1)), 0x0000

    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x7FFE
    WREG        (MS_BUS_RIU_ADDR + (0x100666 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x100686 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x1006a6 << 1)), 0xFFFF

    WREG        (MS_BUS_RIU_ADDR + (0x100618 << 1)), 0x0400 @//reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x002F @//Bit[05]reg_auto_ref_off
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x042F @//trig precharge all
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x052F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x022F @//trig refresh
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x032F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x100606 << 1)), 0x1430 @//Bit[12]reg_cke_always_on

    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x202F
#endif
    bx          lr

@//-------------------------------------------------------------------------------------------------
@// Exit_DDR_RefreshMode
@// @param  None
@// @return None
@// @note   Exit_DDR_RefreshMode
@//-------------------------------------------------------------------------------------------------

Exit_DDR_RefreshMode:

    @// [DDR3][exit] <MIU0>
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x002F

    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0xFFFE
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x022F
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x032F
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000F

    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x001F

    WREG        (MS_BUS_RIU_ADDR + (0x101206 << 1)), 0x342b @//trig refresh

@//    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x0000
@//    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0x0000 @//Bit[12]reg_cke_always_on
@//    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0x0000 @//reg_mrx
@//    WREG        (MS_BUS_RIU_ADDR + (0x1012A6 << 1)), 0x0000 @//Bit[05]reg_auto_ref_off

    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x7ffe
    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0xffff @//Bit[12]reg_cke_always_on
    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0xffff @//reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x1012A6 << 1)), 0xffff @//Bit[05]reg_auto_ref_off

#ifndef CONFIG_MIU1_DRAM_NONE
    @// [DDR3][enter] <MIU1>
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x002F

    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0xFFFE
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x022F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x032F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x000F

    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x001F

    WREG        (MS_BUS_RIU_ADDR + (0x100606 << 1)), 0x342b @//trig refresh

@//    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x0000
@//    WREG        (MS_BUS_RIU_ADDR + (0x100666 << 1)), 0x0000 @//Bit[12]reg_cke_always_on
@//    WREG        (MS_BUS_RIU_ADDR + (0x100686 << 1)), 0x0000 @//reg_mrx
@//    WREG        (MS_BUS_RIU_ADDR + (0x1006A6 << 1)), 0x0000 @//Bit[05]reg_auto_ref_off

    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x7ffe
    WREG        (MS_BUS_RIU_ADDR + (0x100666 << 1)), 0xffff @//Bit[12]reg_cke_always_on
    WREG        (MS_BUS_RIU_ADDR + (0x100686 << 1)), 0xffff @//reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x1006A6 << 1)), 0xffff @//Bit[05]reg_auto_ref_off
#endif
    bx          lr


@//-------------------------------------------------------------------------------------------------
@// Push_Dram_STR
@// @param  None
@// @return None
@// @note   Push_Dram_STR
@//-------------------------------------------------------------------------------------------------
Push_Dram_STR:

#if defined(CONFIG_MSTAR_BD_MST038B_10AHT_EAGLE)
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00e7 @// reg_en_mask @//Table: MIU0_DDR_Init_STR
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00a7 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00e7 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00a7
#elif defined(CONFIG_MSTAR_BD_MST028B_10AFX_EAGLE)
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00e5 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00a5 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00e5 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00a5
#endif

#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x110d8e <<1 )), 0x00e5 @// reg_en_mask @//Table: MIU1_DDR_Init_STR
    WREG        (MS_BUS_RIU_ADDR + (0x110d8e <<1 )), 0x00a5 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d8e <<1 )), 0x00e5 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d8e <<1 )), 0x00a5
#endif


    WREG        (MS_BUS_RIU_ADDR + (0x1012e4 <<1 )), 0x0004 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0100 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0101

    DELAYUS     1                                         @//delay 200us
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0100 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0101
    DELAYUS     1                                         @//delay 200us
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0000

#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x1012f0 <<1 )), 0x8000
    WREG        (MS_BUS_RIU_ADDR + (0x1012e4 <<1 )), 0x0004 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0100 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0101

    DELAYUS     1                                         @//delay 200us
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0100 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0101
    DELAYUS     1                                         @//delay 200us
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0000

    WREG        (MS_BUS_RIU_ADDR + (0x1012f0 <<1 )), 0x0000
#endif
    bx          lr

@//-------------------------------------------------------------------------------------------------
@// Reset_AVD_str
@// @param  None
@// @return None
@// @note  Reset_AVD_str
@//-------------------------------------------------------------------------------------------------

Reset_AVD_str:

    RREG        r8, (MS_BUS_RIU_ADDR + (0x103612 << 1))
    bic    r8, r8, #0x4000
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x103612 << 1))

    RREG        r8, (MS_BUS_RIU_ADDR + (0x103612 << 1))
    orr         r8, r8, #0x4000
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x103612 << 1))

    RREG        r8, (MS_BUS_RIU_ADDR + (0x103612 << 1))
    bic    r8, r8, #0x4000
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x103612 << 1))

    bx           lr
