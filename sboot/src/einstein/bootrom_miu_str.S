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

#ifndef _MIUSEL_EINSTEIN_2MIU_H_
#include "MIUSEL_EINSTEIN_2MIU.h"
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
@//    bl Miu_str_oenz_enable

    DBGREG      0x0020
#if (ENABLE_MSTAR_BD_MST181B_D01A_S) || (ENABLE_MSTAR_BD_MST181D_D01A_S) || (ENABLE_MSTAR_BD_MST051B_10ANV) || (ENABLE_MSTAR_BD_MST181B_D01A_S_CASHMERE) || (ENABLE_MSTAR_BD_MST051D_20ANV)    
    WREG        (MS_BUS_RIU_ADDR + (0x110d00 << 1)), 0x6019
    WREG        (MS_BUS_RIU_ADDR + (0x161600 << 1)), 0x6019
    WREG        (MS_BUS_RIU_ADDR + (0x110d00 << 1)), 0x0009
    WREG        (MS_BUS_RIU_ADDR + (0x161600 << 1)), 0x0009
#else
    WREG        (MS_BUS_RIU_ADDR + (0x110d00 << 1)), 0x6018
    WREG        (MS_BUS_RIU_ADDR + (0x161600 << 1)), 0x6018
    WREG        (MS_BUS_RIU_ADDR + (0x110d00 << 1)), 0x0008
    WREG        (MS_BUS_RIU_ADDR + (0x161600 << 1)), 0x0008
#endif   

    DELAYUS     1000                                         @//delay 200us

    WREG        (MS_BUS_RIU_ADDR + (0x110d7E << 1)), 0x0000   @// LD Power
    WREG        (MS_BUS_RIU_ADDR + (0x16167E << 1)), 0x0000


#ifdef CONFIG_MSTAR_TITANIA_BD_FPGA

@//    WREG        (MS_BUS_RIU_ADDR + (0x003008 << 1)), 0x0000
@//    WREG        (MS_BUS_RIU_ADDR + (0x101ea0 << 1)), 0x0000

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

    WREG        (MS_BUS_RIU_ADDR + (0x1012f8 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x1012fa << 1)), 0x03ff

_CheckDramData:

    RREG        r0, (MS_BUS_RIU_ADDR + (0x101200 << 1))
    and         r0, r0, #0x8000
    cmp         r0, #0
    beq         _CheckDramData

#else

    ldr         r0, =MIU_PreInit_STR
    bl          MDrv_WriteRegTbl32

#endif

    bl  Reset_AVD_str

#if !defined(CONFIG_MIU0_DRAM_NONE)
    ldr         r0, =MIU0_DDR_Init_STR
    bl          MDrv_WriteRegTbl32

#if !(ENABLE_MIU0_4X_MODE)
    DELAYUS     1000    
    WREG        (MS_BUS_RIU_ADDR + (0x110d60 << 1)), 0x00C0    
    WREG        (MS_BUS_RIU_ADDR + (0x110d60 << 1)), 0x33C8
#endif
    
    DELAYUS     5000

    DBGREG      0x0021

    @//Enable MIU0
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c01
    DELAYUS     1
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c08

#if (ENABLE_MSTAR_BD_MST181B_D01A_S) || (ENABLE_MSTAR_BD_MST181D_D01A_S) || (ENABLE_MSTAR_BD_MST051B_10ANV) || (ENABLE_MSTAR_BD_MST181B_D01A_S_CASHMERE) || (ENABLE_MSTAR_BD_MST051D_20ANV)    
    WREG        (MS_BUS_RIU_ADDR + (0x110d00 << 1)), 0x0009  //reg_pkg_sel		1	: [0]
#else
    WREG        (MS_BUS_RIU_ADDR + (0x110d00 << 1)), 0x0008  //reg_pkg_sel		1	: [0]
#endif
    WREG        (MS_BUS_RIU_ADDR + (0x110d02 << 1)), 0xAAAA  //reg_cko_state		cc	: [7:0]
    WREG        (MS_BUS_RIU_ADDR + (0x110d18 << 1)), 0x0000

#if (ENABLE_MIU0_4X_MODE)
    WREG        (MS_BUS_RIU_ADDR + (0x101202 << 1)), 0xF2A7
#else    
    WREG        (MS_BUS_RIU_ADDR + (0x101202 << 1)), 0xF3A7
#endif

    DELAYUS     200                                         @//delay 200us
#endif

#ifndef CONFIG_MIU1_DRAM_NONE

    ldr         r0, =MIU1_DDR_Init_STR
    bl          MDrv_WriteRegTbl32

#if !(ENABLE_MIU1_4X_MODE)
    DELAYUS     1000    
    WREG        (MS_BUS_RIU_ADDR + (0x161660 << 1)), 0x00C0    
    WREG        (MS_BUS_RIU_ADDR + (0x161660 << 1)), 0x33C8
#endif

    DELAYUS     5000

    @//Enable MIU1
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0c01
    DELAYUS     1
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0c08

#if (ENABLE_MSTAR_BD_MST181B_D01A_S) || (ENABLE_MSTAR_BD_MST181D_D01A_S) || (ENABLE_MSTAR_BD_MST051B_10ANV) || (ENABLE_MSTAR_BD_MST181B_D01A_S_CASHMERE) || (ENABLE_MSTAR_BD_MST051D_20ANV)
    WREG        (MS_BUS_RIU_ADDR + (0x161600 << 1)), 0x0009  //reg_pkg_sel		1	: [0]
#else
    WREG        (MS_BUS_RIU_ADDR + (0x161600 << 1)), 0x0008  //reg_pkg_sel		1	: [0]
#endif
    WREG        (MS_BUS_RIU_ADDR + (0x161602 << 1)), 0xAAAA  //reg_cko_state		cc	: [7:0]
    WREG        (MS_BUS_RIU_ADDR + (0x161618 << 1)), 0x0000

#if (ENABLE_MSTAR_BD_MST181A_D01A_S)
#if (ENABLE_MIU1_4X_MODE)
    WREG        (MS_BUS_RIU_ADDR + (0x100602 << 1)), 0xF2A3
#else   
    WREG        (MS_BUS_RIU_ADDR + (0x100602 << 1)), 0xF3A3
#endif
#elif (ENABLE_MSTAR_BD_MST181C_D01A_S)
    WREG        (MS_BUS_RIU_ADDR + (0x100602 << 1)), 0xF3A7
#elif (ENABLE_MSTAR_BD_MST181B_D01A_S) || (ENABLE_MSTAR_BD_MST181D_D01A_S) || (ENABLE_MSTAR_BD_MST051B_10ANV) || (ENABLE_MSTAR_BD_MST181B_D01A_S_CASHMERE) || (ENABLE_MSTAR_BD_MST051D_20ANV)
    WREG        (MS_BUS_RIU_ADDR + (0x100602 << 1)), 0xF3A7
#endif
    DELAYUS     2000                                         @//delay 200us
#endif

    @//Pack Setting
    @//WREG        (MS_BUS_RIU_ADDR + (0x101228 << 1)), 0x4000
    @//WREG        (MS_BUS_RIU_ADDR + (0x100628 << 1)), 0x4000

    @//Reduce Latency Setting
    @//WREG        (MS_BUS_RIU_ADDR + (0x10122a << 1)), 0x4040
    @//WREG        (MS_BUS_RIU_ADDR + (0x10062a << 1)), 0x4040

@// bl          EnableMiuSsc

    DBGREG      0x0024

    @//MIU0 INIT Cycle
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0000 @//hold miu_0
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0008 @//DRAM reset
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000c @//DRAM reset+CS

    DELAYUS     1000                                        @//delay 1000us
    DBGREG      0x0025

#ifndef CONFIG_MIU1_DRAM_NONE

    @//MIU1 INIT Cycle
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0000 @//hold miu_0
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0008 @//DRAM reset
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x000c @//DRAM reset+CS

    DELAYUS     1000                                        @//delay 1000us


#endif
    
    @//rx enable
 @//   WREG        (MS_BUS_RIU_ADDR + (0x110d08 << 1)), 0x003f
#ifndef CONFIG_MIU1_DRAM_NONE
    @//rx enable
 @//   WREG        (MS_BUS_RIU_ADDR + (0x161608 << 1)), 0x003f
#endif


    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000e @//DRAM reset+CS+CKE

    DELAYUS     2000                                        @//delay 2000us

    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x000e @//DRAM reset+CS+CKE

    DELAYUS     2000                                        @//delay 2000us

    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x001f @//DRAM reset+CS+CKE+auto cycle+ODE

    DELAYUS     200                                         @//delay 200us

    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x001f @//DRAM reset+CS+CKE+auto cycle+ODE

    DELAYUS     200                                         @//delay 200us


@//-----------------------------------STR--------------------------------------

    DBGREG      0x0026

    bl  Miu_auto_phase_str


    bl  Enter_DDR_RefreshMode

    DBGREG      0x1026
    bl  Miu_str_oenz_disable

    DBGREG      0x2026

    WREG        (MS_BUS_RIU_ADDR + (0x110D54 <<1 )), 0xC000 @//ATOP_PD on
#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x161654 <<1 )), 0xC000 @//ATOP_PD on
#endif
    
    @//rx enable
    WREG        (MS_BUS_RIU_ADDR + (0x110d08 << 1)), 0x003f
#ifndef CONFIG_MIU1_DRAM_NONE
    @//rx enable
    WREG        (MS_BUS_RIU_ADDR + (0x161608 << 1)), 0x003f
#endif

    bl  Exit_DDR_RefreshMode

    DBGREG      0x2626

    DELAYUS     300                                         @//delay 300us


@//    bl  Push_Dram_STR


@//-----------------------------------STR--------------------------------------

    DBGREG      0x0027

#if !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
@//    bl          MIU_Init_Priority

    bl          MIU_Set_Group_Priority

#endif

    ldr         r0, =MIU_PostInit_STR
    bl          MDrv_WriteRegTbl32

#if 0
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


#if 0
    @//all MIU1 IP select MIU0 in bringup
    WREG        (MS_BUS_RIU_ADDR + (0x1006f0 << 1)), 0x4E88 @//0x7fff
    WREG        (MS_BUS_RIU_ADDR + (0x1006f2 << 1)), 0x0000 @//0xffff
    WREG        (MS_BUS_RIU_ADDR + (0x1006f4 << 1)), 0x0000 @//0xffff
    WREG        (MS_BUS_RIU_ADDR + (0x1006f6 << 1)), 0x0120 @//0xffff
#endif
#endif

#if 0
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
#endif
    DBGREG      0x0030


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
    RREG        r8, (MS_BUS_RIU_ADDR + (0x3DB2 << 1))
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x110D6C << 1))
    RREG        r8, (MS_BUS_RIU_ADDR + (0x3DB6 << 1))
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x110D6E << 1))
#ifndef CONFIG_MIU1_DRAM_NONE
    RREG        r8, (MS_BUS_RIU_ADDR + (0x3DB8 << 1))
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x16166C << 1))
    RREG        r8, (MS_BUS_RIU_ADDR + (0x3DBA << 1))
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x16166E << 1))
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
#if (ENABLE_MSTAR_BD_MST181C_D01A_S || ENABLE_MSTAR_BD_MST181A_D01A_S)    
    WREG        (MS_BUS_RIU_ADDR + (0x101206 << 1)), 0x1E2B @//Bit[12]reg_cke_always_on
#else
    WREG        (MS_BUS_RIU_ADDR + (0x101206 << 1)), 0x1D2B @//trig refresh
#endif

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
#if (ENABLE_MSTAR_BD_MST181C_D01A_S || ENABLE_MSTAR_BD_MST181A_D01A_S)    
    WREG        (MS_BUS_RIU_ADDR + (0x100606 << 1)), 0x1E2B @//Bit[12]reg_cke_always_on
#else
    WREG        (MS_BUS_RIU_ADDR + (0x100606 << 1)), 0x1D2B @//trig refresh
#endif

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

#if (ENABLE_MSTAR_BD_MST181C_D01A_S || ENABLE_MSTAR_BD_MST181A_D01A_S)    
    WREG        (MS_BUS_RIU_ADDR + (0x101206 << 1)), 0x162B @//trig refresh   // for 181C
#else
    WREG        (MS_BUS_RIU_ADDR + (0x101206 << 1)), 0x152B @//trig refresh
#endif    

    @// [DDR3][exit] <MIU0>
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0xFFFE


 #ifndef CONFIG_MIU1_DRAM_NONE

#if (ENABLE_MSTAR_BD_MST181C_D01A_S || ENABLE_MSTAR_BD_MST181A_D01A_S)    
    WREG        (MS_BUS_RIU_ADDR + (0x100606 << 1)), 0x162B @//trig refresh  // for 181C
#else
    WREG        (MS_BUS_RIU_ADDR + (0x100606 << 1)), 0x152B @//trig refresh
#endif
#endif


   @// [DDR3][enter] <MIU1>
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x002F

    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0xFFFE

    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x022F
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x032F
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000F

 #ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x022F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x032F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x000F
#endif

    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x001F
#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x001F
#endif

#if (ENABLE_MSTAR_BD_MST181C_D01A_S || ENABLE_MSTAR_BD_MST181A_D01A_S)    
    WREG        (MS_BUS_RIU_ADDR + (0x101206 << 1)), 0x162B @//trig refresh   // for 181C
#else
    WREG        (MS_BUS_RIU_ADDR + (0x101206 << 1)), 0x152B @//trig refresh
#endif    

#ifndef CONFIG_MIU1_DRAM_NONE
#if (ENABLE_MSTAR_BD_MST181C_D01A_S || ENABLE_MSTAR_BD_MST181A_D01A_S)    
    WREG        (MS_BUS_RIU_ADDR + (0x100606 << 1)), 0x162B @//trig refresh  // for 181C
#else
    WREG        (MS_BUS_RIU_ADDR + (0x100606 << 1)), 0x152B @//trig refresh
#endif
#endif

@//    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x0000
@//    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0x0000 @//Bit[12]reg_cke_always_on
@//    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0x0000 @//reg_mrx
@//    WREG        (MS_BUS_RIU_ADDR + (0x1012A6 << 1)), 0x0000 @//Bit[05]reg_auto_ref_off

    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x7ffe
    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0xffff @//Bit[12]reg_cke_always_on
    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0xffff @//reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x1012A6 << 1)), 0xffff @//Bit[05]reg_auto_ref_off

#ifndef CONFIG_MIU1_DRAM_NONE

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
