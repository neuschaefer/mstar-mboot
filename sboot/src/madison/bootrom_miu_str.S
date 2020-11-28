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

#ifndef _MIUSEL_MADISON_2MIU_H_
#include "MIUSEL_MADISON_2MIU.h"
#endif

    .text
    
    MIU_MESSAGE_BIST0_Str:      .short   'S', 't', 'r', '_', 'B', 'I', 'S', 'T', '0', '-', 0x00
    MIU_MESSAGE_BIST1_Str:      .short   'S', 't', 'r', '_', 'B', 'I', 'S', 'T', '1', '-', 0x00
    MIU_MESSAGE_OK_Str:         .short   'O', 'K', '\n', '\r', 0x00
    MIU_MESSAGE_FAIL_Str:       .short   'F', 'A', 'I', 'L', '\n', '\r', 0x00
    MESSAGE_DC_ON_STR:          .short  '\r', '\n', 'S', 'T', 'R', '_', 'D', 'C', '_', 'O', 'N', '\r', '\n', 0x00
    
    .global     BootRom_InitMiu_STR
BootRom_InitMiu_STR:

    mov         r13, lr
    
    DPUTK_STR   MESSAGE_DC_ON_STR

    DBGREG      0x0020

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

    ldr         r1, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
_CheckDramData:   
    ldr         r0, [r1, #(0x00 << 1)]
    and         r0, r0, #0x8000
    cmp         r0, #0
    beq         _CheckDramData

#else

    ldr         r0, =MIU_PreInit_STR
    bl          MDrv_WriteRegTbl32 

    @//  AVD reset
    bl          Reset_AVD_str 
    
#if !defined(CONFIG_MIU0_DRAM_NONE)
    @// ===== MIU0 DDR INIT ===== //@
    ldr         r0, =MIU0_DDR_Init
    bl          MDrv_WriteRegTbl32
  
    DELAYUS     1000
    
    @//Enable MIU0
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c01
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c00      
    
    WREG        (MS_BUS_RIU_ADDR + (0x110d7e << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x110d1c << 1)), 0x0020
   
    DELAYUS     2000                                         @//delay 200us
#endif /* CONFIG_MIU0_DRAM_NONE */
    
#if !defined(CONFIG_MIU1_DRAM_NONE)
    @// ===== MIU1 DDR INIT ===== //@
    ldr         r0, =MIU1_DDR_Init
    bl          MDrv_WriteRegTbl32

    DELAYUS     1000

    @//Enable MIU1
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0c01
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0c00
    
    WREG        (MS_BUS_RIU_ADDR + (0x110dfe << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x110d9c << 1)), 0x0020

    DELAYUS     2000                                         @//delay 200us
#endif /* CONFIG_MIU1_DRAM_NONE */

    DBGREG      0x0024
    
#if !defined(CONFIG_MIU0_DRAM_NONE)

    @//MIU0 INIT Cycle
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0000  @//hold miu_0
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0008  @//DRAM reset
    DELAYUS     1000
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000c @//DRAM reset+CS
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000e @//DRAM reset+CS+CKE
    DELAYUS     1000                                        @//delay 2000us    
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x001f @//DRAM reset+CS+CKE+auto cycle+ODE
    
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
CheckMiu0Init:  
    ldr         r0, [r1, #(0x00 << 1)]
    and         r0, r0, #0x8000
    cmp         r0, #0
    beq         CheckMiu0Init
#endif /* CONFIG_MIU0_DRAM_NONE */
  
#if !defined(CONFIG_MIU1_DRAM_NONE)

    @//MIU1 INIT Cycle
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0000  @//hold miu_1
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0008  @//DRAM reset
    DELAYUS     1000                         @//delay 500us
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x000c  @//DRAM reset+CS
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x000e  @//DRAM reset+CS+CKE
    DELAYUS     1000                         @//delay 500us
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x001f  @//DRAM reset+CS+CKE+auto cycle+ODE

    ldr         r1, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
CheckMiu1Init:
    ldr         r0, [r1, #(0x00 << 1)]
    and         r0, r0, #0x8000
    cmp         r0, #0
    beq         CheckMiu1Init
#endif /* CONFIG_MIU1_DRAM_NONE */

@//-----------------------------------STR--------------------------------------

    DBGREG      0x0025

    bl  Miu_auto_phase_str
    
    DBGREG      0x0026

    @// enter refreseh 
    bl  Enter_DDR_RefreshMode    
    DELAYUS     1000   
     
    DBGREG      0x0027
    
    @// disable oenz
    bl  Miu_str_oenz_disable
    DELAYUS     1
    
    DBGREG      0x0028
    
    @// ATOP_PD on
#ifndef CONFIG_MIU0_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x110d54 <<1 )), 0xC000 
#endif
#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x110dd4 <<1 )), 0xC000 
#endif

    @// rx enable
#ifndef CONFIG_MIU0_DRAM_NONE    
    WREG        (MS_BUS_RIU_ADDR + (0x110d08 << 1)), 0x003f
#endif
#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x110d88 << 1)), 0x003f
#endif
    
    @// exit refresh 
    bl  Exit_DDR_RefreshMode
    DELAYUS     300 
@//-----------------------------------STR--------------------------------------   

    DBGREG      0x0029

#if !defined(CONFIG_MIU0_DRAM_NONE)
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x110d00 << 1))
#if defined(CONFIG_MIU1_DDR3_1866)
    ldr         r0, =0x00e9
    str         r0, [r1, #(0x0e << 1)]
    ldr         r0, =0x00a9
    str         r0, [r1, #(0x0e << 1)]
    ldr         r0, =0x00e9
    str         r0, [r1, #(0x0e << 1)]
    ldr         r0, =0x00a9
    str         r0, [r1, #(0x0e << 1)]
#else
    ldr         r0, =0x00e7
    str         r0, [r1, #(0x0e << 1)]
    ldr         r0, =0x00a7
    str         r0, [r1, #(0x0e << 1)]
    ldr         r0, =0x00e7
    str         r0, [r1, #(0x0e << 1)]
    ldr         r0, =0x00a7
    str         r0, [r1, #(0x0e << 1)]
#endif

    ldr         r1, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r0, =0x0400                 @//reg_mrx
    str         r0, [r1, #(0x18 << 1)]
    ldr         r0, =0x043f                 @//Bit[05]reg_auto_ref_off, precharge all cmd
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x053f                 @//Bit[05]reg_auto_ref_off, trig precharge all cmd enable
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x003f                 @//single cmd off
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x023f                 @//Bit[05]reg_auto_ref_off, refresh cmd
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x033f                 @//Bit[05]reg_auto_ref_off, refresh cmd enable
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x001f                 @//single cmd off, auto_ref_on
    str         r0, [r1, #(0x00 << 1)]
#endif


#if !defined(CONFIG_MIU1_DRAM_NONE)

    @//====== New Sequesnce for MIU1 dqsm reset
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x110d00 << 1))
#if defined(CONFIG_MIU1_DDR3_1866)
    ldr         r0, =0x00e9
    str         r0, [r1, #(0x8e << 1)]
    ldr         r0, =0x00a9
    str         r0, [r1, #(0x8e << 1)]
    ldr         r0, =0x00e9
    str         r0, [r1, #(0x8e << 1)]
    ldr         r0, =0x00a9
    str         r0, [r1, #(0x8e << 1)]
#else
    ldr         r0, =0x00e7
    str         r0, [r1, #(0x8e << 1)]
    ldr         r0, =0x00a7
    str         r0, [r1, #(0x8e << 1)]
    ldr         r0, =0x00e7
    str         r0, [r1, #(0x8e << 1)]
    ldr         r0, =0x00a7
    str         r0, [r1, #(0x8e << 1)]
#endif

    ldr         r1, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
    ldr         r0, =0x0400                 @//reg_mrx
    str         r0, [r1, #(0x18 << 1)]
    ldr         r0, =0x043f                 @//Bit[05]reg_auto_ref_off, precharge all cmd
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x053f                 @//Bit[05]reg_auto_ref_off, trig precharge all cmd enable
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x003f                 @//single cmd off
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x023f                 @//Bit[05]reg_auto_ref_off, refresh cmd
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x033f                 @//Bit[05]reg_auto_ref_off, refresh cmd enable
    str         r0, [r1, #(0x00 << 1)]
    ldr         r0, =0x001f                 @//single cmd off, auto_ref_on
    str         r0, [r1, #(0x00 << 1)]
    DELAYUS     100  
#endif

    DBGREG      0x002a

    bl          MIU_Set_Group_Priority_Str

    DBGREG      0x002b
    
    ldr         r0, =MIU_PostInit_STR
    bl          MDrv_WriteRegTbl32

#endif

    mov         lr, r13
    bx          lr
    .size       BootRom_InitMiu_STR,.-BootRom_InitMiu_STR

@//-------------------------------------------------------------------------------------------------
@// Miu_str_oenz_disable
@// @param  None
@// @return None
@// @note   Miu_str_oenz_disable
@//-------------------------------------------------------------------------------------------------
Miu_str_oenz_disable:
#ifndef CONFIG_MIU0_DRAM_NONE
    RREG        r8, (MS_BUS_RIU_ADDR + (0x101202 << 1))
    bic         r8, r8, #0xf000
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x101202 << 1))
#endif
#ifndef CONFIG_MIU1_DRAM_NONE
    RREG        r8, (MS_BUS_RIU_ADDR + (0x100602 << 1))
    bic         r8, r8, #0xf000
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
#ifndef CONFIG_MIU0_DRAM_NONE
    RREG        r8, (MS_BUS_RIU_ADDR + (0x3DB2 << 1))
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x110D6C << 1))
    RREG        r8, (MS_BUS_RIU_ADDR + (0x3DB6 << 1))
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x110D6E << 1))
#endif
#ifndef CONFIG_MIU1_DRAM_NONE
    RREG        r8, (MS_BUS_RIU_ADDR + (0x3DB8 << 1))
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x110dec << 1))
    RREG        r8, (MS_BUS_RIU_ADDR + (0x3DBA << 1))
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x110dee << 1))    
#endif    
    bx          lr

@//-------------------------------------------------------------------------------------------------
@// Enter_DDR_RefreshMode
@// @param  None
@// @return None
@// @note   Enter_DDR_RefreshMode
@//-------------------------------------------------------------------------------------------------
Enter_DDR_RefreshMode:
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000
    
#ifndef CONFIG_MIU0_DRAM_NONE
    @// [DDR3][enter] <MIU0>    
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x7FFE
    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x1012a6 << 1)), 0xFFFF

    WREG        (MS_BUS_RIU_ADDR + (0x101218 << 1)), 0x0400 @//reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x002F @//Bit[05]reg_auto_ref_off
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x042F @//trig precharge all
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x052F
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x002F

    @// Bit[11] reg_csz_always_on 
    RREG        r8, (MS_BUS_RIU_ADDR + (0x101206 << 1))
    orr         r8, r8, #0x0800
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x101206 << 1))
    
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x202F
#endif
#ifndef CONFIG_MIU1_DRAM_NONE
    @// [DDR3][enter] <MIU1>
    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x7FFE
    WREG        (MS_BUS_RIU_ADDR + (0x100666 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x100686 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x1006a6 << 1)), 0xFFFF

    WREG        (MS_BUS_RIU_ADDR + (0x100618 << 1)), 0x0400 @//reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x002F @//Bit[05]reg_auto_ref_off
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x042F @//trig precharge all
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x052F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x002F
    
    @// Bit[11] reg_csz_always_on 
    RREG        r8, (MS_BUS_RIU_ADDR + (0x100606 << 1))
    orr         r8, r8, #0x0800
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x100606 << 1))

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
#ifndef CONFIG_MIU0_DRAM_NONE
    @// [DDR3][exit] <MIU0>
    @// disable Bit[11] reg_csz_always_on 
    RREG        r8, (MS_BUS_RIU_ADDR + (0x101206 << 1))
    bic         r8, r8, #0x0800
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x101206 << 1))
    
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0xFFFE    
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x022F
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x032F
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000F
    DELAYUS     5
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x001F
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x7ffe
    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0xffff @//Bit[12]reg_cke_always_on
    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0xffff @//reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x1012A6 << 1)), 0xffff @//Bit[05]reg_auto_ref_off
#endif
#ifndef CONFIG_MIU1_DRAM_NONE
    @// [DDR3][enter] <MIU1>
    @// disable Bit[11] reg_csz_always_on 
    RREG        r8, (MS_BUS_RIU_ADDR + (0x100606 << 1))
    bic         r8, r8, #0x0800
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x100606 << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0xFFFE
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x022F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x032F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x000F
    
    DELAYUS     5
    
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x001F
    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x7ffe
    WREG        (MS_BUS_RIU_ADDR + (0x100666 << 1)), 0xffff @//Bit[12]reg_cke_always_on
    WREG        (MS_BUS_RIU_ADDR + (0x100686 << 1)), 0xffff @//reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x1006A6 << 1)), 0xffff @//Bit[05]reg_auto_ref_off
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
    bic         r8, r8, #0x4000
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x103612 << 1))

    RREG        r8, (MS_BUS_RIU_ADDR + (0x103612 << 1))
    orr         r8, r8, #0x4000
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x103612 << 1))

    RREG        r8, (MS_BUS_RIU_ADDR + (0x103612 << 1))
    bic         r8, r8, #0x4000
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x103612 << 1))

    bx          lr

@//-------------------------------------------------------------------------------------------------
@// Bist for str
@// @param  None
@// @return None
@// @note  Reset_AVD_str
@//-------------------------------------------------------------------------------------------------
    .global     Miu1_BistTest_Str
Miu1_BistTest_Str:

    DPUTK_STR   MIU_MESSAGE_BIST1_Str

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000   @//1012e0 //reset bist test
    ldr         r11, =0x8000
    str         r11, [r12, #(0xf0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x8000   @//1012f0 bit_15=1 choice to MIU_1
    b           Miu_BistTest_Str

    .global     Miu0_BistTest_Str
Miu0_BistTest_Str:

    DPUTK_STR   MIU_MESSAGE_BIST0_Str

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000   @//1012e0 //reset bist test
    str         r11, [r12, #(0xf0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x0000   @//1012f0 bit_15=0 choice to MIU_0

    .global     Miu_BistTest_Str
Miu_BistTest_Str:
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe2 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e2 << 1)), 0x0000   @//1012e2 //start address base unit:4 k bytes

    ldr         r0, =0xFFFF
    ldr         r11, =BIST_LEN
    and         r11, r11, r0
    str         r11, [r12, #(0xe4 << 1)]
    ldr         r11, =BIST_LEN
    lsr         r11, #16
    and         r11, r11, r0
    str         r11, [r12, #(0xe6 << 1)]    @//WREG_D      (MS_BUS_RIU_ADDR + (0x1012e4 << 1)), BIST_LEN

    ldr         r11, =0x5aa5
    str         r11, [r12, #(0xe8 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e8 << 1)), 0x5aa5   @//1012e8 //bist test pattern

#ifdef CONFIG_MSTAR_SELF_STR_TEST_ENABLE
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0101   @//bist test mode:3 + read mode
#endif

Miu_CheckBistLoop_Str:
    RREG        r1, (MS_BUS_RIU_ADDR + (0x1012e0 << 1))
    and         r0, r1, #0x8000
    cmp         r0, #0
    beq         Miu_CheckBistLoop_Str

    and         r0, r1, #0x6000
    cmp         r0, #0
    beq         Miu_Bist_OK_Str

Miu_Bist_Fail_Str:
    DPUTK_STR   MIU_MESSAGE_FAIL_Str

Miu_Bist_FailLoop_Str:
    b           Miu_Bist_FailLoop_Str

Miu_Bist_OK_Str:
    DPUTK_STR   MIU_MESSAGE_OK_Str
    
    bx          lr
    
    
@//-------------------------------------------------------------------------------------------------
@// MIU_Set_Group_Priority
@// @param  None
@// @return None
@// @note   Set Group Priority
@//-------------------------------------------------------------------------------------------------
    .global     MIU_Set_Group_Priority_Str
MIU_Set_Group_Priority_Str:
#if !defined(CONFIG_MIU0_DRAM_NONE)
    @//set group priority in MIU_0
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r3, [r12, #(0xfe << 1)]     @//RREG        r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))
    bic         r3, r3, #0x0100
    str         r3, [r12, #(0xfe << 1)]     @//REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))

    bic         r3, r3, #0x00FF
    ldr         r4, =(MIU0_GROUP_PRIORITY & 0xFF)
    orr         r3, r3, r4
    str         r3, [r12, #(0xfe << 1)]     @//REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))

    orr         r3, r3, #0x0100             @//set group fix priority
    str         r3, [r12, #(0xfe << 1)]     @//REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))
    bic         r3, r3, #0x0100
    str         r3, [r12, #(0xfe << 1)]     @//REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    @//set group priority in MIU_1
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
    ldr         r3, [r12, #(0xfe << 1)]     @//RREG        r3, (MS_BUS_RIU_ADDR + (0x1006FE << 1))
    bic         r3, r3, #0x0100
    str         r3, [r12, #(0xfe << 1)]     @//REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1006FE << 1))

    bic         r3, r3, #0x00FF
    ldr         r4, =(MIU1_GROUP_PRIORITY & 0xFF)
    orr         r3, r3, r4
    str         r3, [r12, #(0xfe << 1)]     @//REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1006FE << 1))

    orr         r3, r3, #0x0100
    str         r3, [r12, #(0xfe << 1)]     @//REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1006FE << 1))
    bic         r3, r3, #0x0100
    str         r3, [r12, #(0xfe << 1)]     @//REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1006FE << 1))

#endif

    bx          lr    
    
