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

#ifndef _DRV_MIU_INIT_H_
#include "drv_miu_init.h"
#endif

#ifndef _MIUSEL_CLIPPERS_2MIU_H_
#include "MIUSEL_CLIPPERS_2MIU.h"
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

    @//DBGREG      0x2001

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

    bl          MIU_PreInit_Str


    @//  AVD reset
    bl          Reset_AVD_str 

    
#if !defined(CONFIG_MIU0_DRAM_NONE)
    @// MIU0: DDR3-1866 PLL-SETTING
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x110D00 << 1))
    ldr         r2, =0x0001
    str         r2, [r1, #(0x78 << 1)]
    DELAYUS     10
    ldr         r2, =0x1000
    str         r2, [r1, #(0x24 << 1)]
    DELAYUS     10
    ldr         r2, =0x0000
    str         r2, [r1, #(0x24 << 1)]
    DELAYUS     10
    ldr         r2, =0x0400
    str         r2, [r1, #(0x36 << 1)]
    ldr         r2, =0x2004
    str         r2, [r1, #(0x34 << 1)]
#if defined(CONFIG_MIU0_DDR3_1666)    
    ldr         r2, =0x7236
    str         r2, [r1, #(0x30 << 1)]
    ldr         r2, =0x0023
    str         r2, [r1, #(0x32 << 1)]   @//1600Mhz
#elif defined(CONFIG_MIU0_DDR3_1866)
    ldr         r2, =0x8F5C
    str         r2, [r1, #(0x30 << 1)]
    ldr         r2, =0x001e
    str         r2, [r1, #(0x32 << 1)]
#else
    #error "Invalid DRAM Setting"
#endif
      
    DELAYUS     100
    
    WREG        (MS_BUS_RIU_ADDR + (0x110d22 << 1)), 0x0004

    DELAYUS     500        
    
    bl          MIU0_Load_Dig_Switch_Str
    
    @// ===== MIU0 DDR INIT ===== //@
    ldr         r0, =MIU0_DDR_Init
    bl          MDrv_WriteRegTbl32    
    
#endif /* CONFIG_MIU0_DRAM_NONE */
    
#if !defined(CONFIG_MIU1_DRAM_NONE)
    @// MIU1: DDR3-1866 PLL-SETTING
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x161600 << 1))
    ldr         r2, =0x0001
    str         r2, [r1, #(0x78 << 1)]
    DELAYUS     10
    ldr         r2, =0x1000
    str         r2, [r1, #(0x24 << 1)]
    DELAYUS     10
    ldr         r2, =0x0000
    str         r2, [r1, #(0x24 << 1)]
    DELAYUS     10
    ldr         r2, =0x0400
    str         r2, [r1, #(0x36 << 1)]
    ldr         r2, =0x2004
    str         r2, [r1, #(0x34 << 1)]
#if defined(CONFIG_MIU1_DDR3_1666)    
    ldr         r2, =0x7236
    str         r2, [r1, #(0x30 << 1)]
    ldr         r2, =0x0023
    str         r2, [r1, #(0x32 << 1)]   @//1600Mhz
#elif defined(CONFIG_MIU1_DDR3_1866)
    ldr         r2, =0x8F5C
    str         r2, [r1, #(0x30 << 1)]
    ldr         r2, =0x001e
    str         r2, [r1, #(0x32 << 1)]
#else
    #error "Invalid DRAM Setting"
#endif

    DELAYUS     100

    WREG        (MS_BUS_RIU_ADDR + (0x161622 << 1)), 0x0004

    DELAYUS     500

    bl          MIU1_Load_Dig_Switch_Str
    
    @// ===== MIU1 DDR INIT ===== //@
    ldr         r0, =MIU1_DDR_Init
    bl          MDrv_WriteRegTbl32
    
#endif /* CONFIG_MIU1_DRAM_NONE */

    @//DBGREG      0x2002
    
    @// restore deskew
    bl  Miu_auto_phase_str
    
#if !defined(CONFIG_MIU0_DRAM_NONE)
    @//MIU0 INIT Cycle    
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r2, =0x0008
    str         r2, [r1]                                     @//DRAM reset 
    DELAYUS     200                                          @//delay 200us
    ldr         r2, =0x000C                                  @//hold miu_0
    str         r2, [r1]               
    ldr         r2, =0x000E                                  @//DRAM reset+CS
    str         r2, [r1]                 
    DELAYUS     500                                          @//delay 500us
    ldr         r2, =0x001f                                  @//DRAM reset+CS+CKE+auto cycle+ODE
    str         r2, [r1]
CheckMiu0Init:
    ldr         r2, [r1]
    and         r2, r2, #0x8000
    cmp         r2, #0
    beq         CheckMiu0Init
#endif /* CONFIG_MIU0_DRAM_NONE */

    @//DBGREG      0x2003

#if !defined(CONFIG_MIU1_DRAM_NONE)
    @//MIU1 INIT Cycle    
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
    ldr         r2, =0x0008
    str         r2, [r1]                                     @//DRAM reset 
    DELAYUS     200                                          @//delay 200us
    ldr         r2, =0x000C                                  @//hold miu_1
    str         r2, [r1]               
    ldr         r2, =0x000E                                  @//DRAM reset+CS
    str         r2, [r1]                 
    DELAYUS     500                                          @//delay 500us
    ldr         r2, =0x001f                                  @//DRAM reset+CS+CKE+auto cycle+ODE
    str         r2, [r1]
CheckMiu1Init:
    ldr         r2, [r1]
    and         r2, r2, #0x8000
    cmp         r2, #0
    beq         CheckMiu1Init
#endif /* CONFIG_MIU1_DRAM_NONE */
    
    @//DBGREG      0x2004
    
    WREG        (MS_BUS_RIU_ADDR + (0x1012FE << 1)), 0x20E1     @// 256 bit sel
    
@//-----------------------------------STR--------------------------------------
    
    @// enter refreseh 
    bl          Enter_DDR_RefreshMode    
    DELAYUS     1000   
     
    
    @// disable oenz
    bl          Miu_str_oenz_disable
    DELAYUS     1
    
    
    @// ATOP_PD on
#ifndef CONFIG_MIU0_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x110d54 <<1 )), 0xC000 @//ATOP_PD off
#endif
#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x161654 <<1 )), 0xC000 @//ATOP_PD off
#endif

    @// rx enable
#ifndef CONFIG_MIU0_DRAM_NONE    
    WREG        (MS_BUS_RIU_ADDR + (0x110d08 << 1)), 0x003f
#endif
#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x161608 << 1)), 0x003f
#endif
    
    @// exit refresh 
    bl          Exit_DDR_RefreshMode
    DELAYUS     300 
    
    #if 1 
    @// push dram
    @// miu0
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x110D00 << 1))
    ldr         r2, [r1, #(0x1E << 1)]
    orr         r2, r2, #0x05   @//set bit1 & bit3 = 1
    str         r2, [r1, #(0x1E << 1)]
    
    ldr         r2, [r1, #(0x1E << 1)]
    orr         r2, r2, #0x0A   @//set bit0 & bit2 = 1 
    str         r2, [r1, #(0x1E << 1)] 
     
    ldr         r2, [r1, #(0x1E << 1)]
    bic         r2, r2, #0x0A   @// clear bit1 & bit3
    str         r2, [r1, #(0x1E << 1)]
    
    ldr         r2, [r1, #(0x1E << 1)]
    orr         r2, r2, #0x0A   @//set bit0 & bit2 = 1 
    str         r2, [r1, #(0x1E << 1)] 
     
    ldr         r2, [r1, #(0x1E << 1)]
    bic         r2, r2, #0x0A   @// clear bit1 & bit3
    str         r2, [r1, #(0x1E << 1)]
    
    @// miu1
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x161600 << 1))
    ldr         r2, [r1, #(0x1E << 1)]
    orr         r2, r2, #0x05   @//set bit1 & bit3 = 1
    str         r2, [r1, #(0x1E << 1)]
    
    ldr         r2, [r1, #(0x1E << 1)]
    orr         r2, r2, #0x0A   @//set bit0 & bit2 = 1 
    str         r2, [r1, #(0x1E << 1)] 
     
    ldr         r2, [r1, #(0x1E << 1)]
    bic         r2, r2, #0x0A   @// clear bit1 & bit3
    str         r2, [r1, #(0x1E << 1)]
    
    ldr         r2, [r1, #(0x1E << 1)]
    orr         r2, r2, #0x0A   @//set bit0 & bit2 = 1 
    str         r2, [r1, #(0x1E << 1)] 
     
    ldr         r2, [r1, #(0x1E << 1)]
    bic         r2, r2, #0x0A   @// clear bit1 & bit3
    str         r2, [r1, #(0x1E << 1)]
    
    #endif
    @//DBGREG      0x2005
    
@//-----------------------------------STR--------------------------------------   

    bl          MIU_Set_Group_Priority_Str        
    
    WREG        (MS_BUS_RIU_ADDR + (0x1012FE << 1)), 0x20E1     @// 256 bit sel
    
    @//DBGREG      0x2006
    bl          MIU_PostInit_Str
    
#endif

    @//DBGREG      0x2007
    mov         lr, r13
    bx          lr
    .size       BootRom_InitMiu_STR,.-BootRom_InitMiu_STR


@//-------------------------------------------------------------------------------------------------
@// MIU_PreInit
@// @param  None
@// @return None
@// @note   
@//-------------------------------------------------------------------------------------------------
MIU_PreInit_Str:
#if !defined(CONFIG_MIU0_DRAM_NONE)
    @//MIU0 Software reset
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r3, =0x0c00
    str         r3, [r12, #(0x1E << 1)]
    ldr         r3, =0x0c00
    str         r3, [r12, #(0x1E << 1)]
    ldr         r3, =0x0c00
    str         r3, [r12, #(0x1E << 1)]
    ldr         r3, =0x0c01
    str         r3, [r12, #(0x1E << 1)]
    ldr         r3, =0x0c00
    str         r3, [r12, #(0x02 << 1)]
    
    @//MIU0 Request mask
    ldr         r3, =0xFFFE
    str         r3, [r12, #(0x46 << 1)]
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0x66 << 1)]
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0x86 << 1)]
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0xA6 << 1)]
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x161500 << 1))
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0x06 << 1)]
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0x26 << 1)]
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    @//MIU1 Software reset
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
    ldr         r3, =0x0000
    str         r3, [r12, #(0x1E << 1)]
    ldr         r3, =0x0000
    str         r3, [r12, #(0x1E << 1)]
    ldr         r3, =0x0000
    str         r3, [r12, #(0x1E << 1)]
    ldr         r3, =0x0c01
    str         r3, [r12, #(0x1E << 1)]
    ldr         r3, =0x0c00
    str         r3, [r12, #(0x1E << 1)]
    
    @//MIU1 Request mask
    ldr         r3, =0xFFFE
    str         r3, [r12, #(0x46 << 1)]
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0x66 << 1)]
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0x86 << 1)]
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0xA6 << 1)]
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x162200 << 1))
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0x06 << 1)]
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0x26 << 1)]
#endif
    bx          lr

@//-------------------------------------------------------------------------------------------------
@// MIU_PostInit
@// @param  None
@// @return None
@// @note   
@//-------------------------------------------------------------------------------------------------
MIU_PostInit_Str:
#if !defined(CONFIG_MIU0_DRAM_NONE)
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r3, =0x0000
    str         r3, [r12, #(0xE0 << 1)]                 @//stop bist test

    @//open all MIU0 request mask (All IP can access MIU resource)
    ldr         r3, =0x0000
    str         r3, [r12, #(0x46 << 1)]                 @//Mask MIU0_group_0
    ldr         r3, =0x0000
    str         r3, [r12, #(0x66 << 1)]                 @//Mask MIU0_group_1
    ldr         r3, =0x0000
    str         r3, [r12, #(0x86 << 1)]                 @//Mask MIU0_group_2
    ldr         r3, =0x0000
    str         r3, [r12, #(0xA6 << 1)]                 @//Mask MIU0_group_3
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x161500 << 1))
    ldr         r3, =0x0000
    str         r3, [r12, #(0x06 << 1)]                 @//Mask MIU0_group_4
    ldr         r3, =0x0000
    str         r3, [r12, #(0x26 << 1)]                 @//Mask MIU0_group_5
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)

    @//open all MIU0 request mask (All IP can access MIU resource)
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
    ldr         r3, =0x0000
    str         r3, [r12, #(0x46 << 1)]                 @//Mask MIU0_group_0
    ldr         r3, =0x0000
    str         r3, [r12, #(0x66 << 1)]                 @//Mask MIU0_group_1
    ldr         r3, =0x0000
    str         r3, [r12, #(0x86 << 1)]                 @//Mask MIU0_group_2
    ldr         r3, =0x0000
    str         r3, [r12, #(0xA6 << 1)]                 @//Mask MIU0_group_3
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x162200 << 1))
    ldr         r3, =0x0000
    str         r3, [r12, #(0x06 << 1)]                 @//Mask MIU0_group_4
    ldr         r3, =0x0000
    str         r3, [r12, #(0x26 << 1)]                 @//Mask MIU0_group_5
    
    @//all IP choose sw select( not IP select )
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
    ldr         r3, =0x0000
    str         r3, [r12, #(0xF0 << 1)]
    ldr         r3, =0x0000
    str         r3, [r12, #(0xF2 << 1)]
    ldr         r3, =0x0000
    str         r3, [r12, #(0xF4 << 1)]
    ldr         r3, =0x0000
    str         r3, [r12, #(0xF6 << 1)]
    ldr         r3, =0x0000
    str         r3, [r12, #(0xF8 << 1)]
    ldr         r3, =0x0000
    str         r3, [r12, #(0xFA << 1)]  
#endif
    
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c08
    
    bx          lr

@//-------------------------------------------------------------------------------------------------
@// MIU0_Load_Dig_Switch_Str
@// @param  None
@// @return None
@// @note   
@//-------------------------------------------------------------------------------------------------
MIU0_Load_Dig_Switch_Str:

#if !defined(CONFIG_MIU0_DRAM_NONE)
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r3, =0x8001
    str         r3, [r12, #(0x2c << 1)]
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0x52 << 1)]
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0x72 << 1)]
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0x92 << 1)]
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0xB2 << 1)]
    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x161500 << 1))
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0x12 << 1)]
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0x32 << 1)]
    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r3, =0x8015
    str         r3, [r12, #(0x40 << 1)]
    ldr         r3, =0x8015
    str         r3, [r12, #(0x60 << 1)]
    ldr         r3, =0x8015
    str         r3, [r12, #(0x80 << 1)]
    ldr         r3, =0x8015
    str         r3, [r12, #(0xA0 << 1)]
    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x161500 << 1))    
    ldr         r3, =0x8015
    str         r3, [r12, #(0x00 << 1)]
    ldr         r3, =0x8015
    str         r3, [r12, #(0x20 << 1)]

#endif

     bx          lr
@//-------------------------------------------------------------------------------------------------
@// MIU1_Load_Dig_Switch_Str
@// @param  None
@// @return None
@// @note   
@//-------------------------------------------------------------------------------------------------
MIU1_Load_Dig_Switch_Str:     

#if !defined(CONFIG_MIU1_DRAM_NONE)
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
    ldr         r3, =0x8001
    str         r3, [r12, #(0x2c << 1)]
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0x52 << 1)]
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0x72 << 1)]
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0x92 << 1)]
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0xB2 << 1)]
    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x162200 << 1))
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0x12 << 1)]
    ldr         r3, =0xFFFF
    str         r3, [r12, #(0x32 << 1)]
    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
    ldr         r3, =0x8015
    str         r3, [r12, #(0x40 << 1)]
    ldr         r3, =0x8015
    str         r3, [r12, #(0x60 << 1)]
    ldr         r3, =0x8015
    str         r3, [r12, #(0x80 << 1)]
    ldr         r3, =0x8015
    str         r3, [r12, #(0xA0 << 1)]
    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x162200 << 1))    
    ldr         r3, =0x8015
    str         r3, [r12, #(0x00 << 1)]
    ldr         r3, =0x8015
    str         r3, [r12, #(0x20 << 1)]
#endif
    
    bx          lr
    
@//-------------------------------------------------------------------------------------------------
@// Miu_str_oenz_disable
@// @param  None
@// @return None
@// @note   Miu_str_oenz_disable
@//-------------------------------------------------------------------------------------------------
Miu_str_oenz_disable:
#ifndef CONFIG_MIU0_DRAM_NONE
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r8, [r12, #(0x02 << 1)] 
    bic         r8, r8, #0xF000
    str         r8, [r12, #(0x02 << 1)]
#endif /* CONFIG_MIU0_DRAM_NONE */

#ifndef CONFIG_MIU1_DRAM_NONE
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
    ldr         r8, [r12, #(0x02 << 1)] 
    bic         r8, r8, #0xF000
    str         r8, [r12, #(0x02 << 1)]
#endif /* CONFIG_MIU1_DRAM_NONE */
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
    ldr         r11, =(MS_BUS_RIU_ADDR + (0x103300 << 1))
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x110D00 << 1))  
    ldr         r10, [r11, #(0x82 << 1)]
    str         r10, [r12, #(0x2E << 1)]  
    ldr         r10, [r11, #(0x84 << 1)]
    str         r10, [r12, #(0xA0 << 1)]      
    ldr         r10, [r11, #(0x86 << 1)]
    str         r10, [r12, #(0xA2 << 1)]   
    ldr         r10, [r11, #(0x88 << 1)]
    str         r10, [r12, #(0xA4 << 1)]      
    ldr         r10, [r11, #(0x8A << 1)]
    str         r10, [r12, #(0xA6 << 1)]       
    ldr         r10, [r11, #(0x8C << 1)]
    str         r10, [r12, #(0xA8 << 1)]        
    ldr         r10, [r11, #(0x8E << 1)]
    str         r10, [r12, #(0xAA << 1)]        
    ldr         r10, [r11, #(0x90 << 1)]
    str         r10, [r12, #(0xAC << 1)]        
    ldr         r10, [r11, #(0x92 << 1)]
    str         r10, [r12, #(0xAE << 1)]      
    ldr         r10, [r11, #(0x94 << 1)]
    str         r10, [r12, #(0xD0 << 1)]  
    ldr         r10, [r11, #(0x96 << 1)]
    str         r10, [r12, #(0xD2 << 1)]      
    ldr         r10, [r11, #(0x98 << 1)]
    str         r10, [r12, #(0xD4 << 1)]   
    ldr         r10, [r11, #(0x9A << 1)]
    str         r10, [r12, #(0xD6 << 1)]      
    ldr         r10, [r11, #(0x9C << 1)]
    str         r10, [r12, #(0xD8 << 1)]       
    ldr         r10, [r11, #(0x9E << 1)]
    str         r10, [r12, #(0xE0 << 1)]        
    ldr         r10, [r11, #(0xA0 << 1)]
    str         r10, [r12, #(0xE2 << 1)]        
    ldr         r10, [r11, #(0xA2 << 1)]
    str         r10, [r12, #(0xE4 << 1)]        
    ldr         r10, [r11, #(0xA4 << 1)]
    str         r10, [r12, #(0xE6 << 1)]
    ldr         r10, [r11, #(0xA6 << 1)]
    str         r10, [r12, #(0xE8 << 1)]
#endif /* CONFIG_MIU0_DRAM_NONE */

#ifndef CONFIG_MIU1_DRAM_NONE
    ldr         r11, =(MS_BUS_RIU_ADDR + (0x103300 << 1))
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x161600 << 1))
    ldr         r10, [r11, #(0xA8 << 1)]
    str         r10, [r12, #(0x2E << 1)]  
    ldr         r10, [r11, #(0xAA << 1)]
    str         r10, [r12, #(0xA0 << 1)]      
    ldr         r10, [r11, #(0xAC << 1)]
    str         r10, [r12, #(0xA2 << 1)]   
    ldr         r10, [r11, #(0xAE << 1)]
    str         r10, [r12, #(0xA4 << 1)]      
    ldr         r10, [r11, #(0xB0 << 1)]
    str         r10, [r12, #(0xA6 << 1)]       
    ldr         r10, [r11, #(0xB2 << 1)]
    str         r10, [r12, #(0xA8 << 1)]        
    ldr         r10, [r11, #(0xB4 << 1)]
    str         r10, [r12, #(0xAA << 1)]        
    ldr         r10, [r11, #(0xB6 << 1)]
    str         r10, [r12, #(0xAC << 1)]        
    ldr         r10, [r11, #(0xB8 << 1)]
    str         r10, [r12, #(0xAE << 1)]      
    ldr         r10, [r11, #(0xBA << 1)]
    str         r10, [r12, #(0xD0 << 1)]  
    ldr         r10, [r11, #(0xBC << 1)]
    str         r10, [r12, #(0xD2 << 1)]      
    ldr         r10, [r11, #(0xBE << 1)]
    str         r10, [r12, #(0xD4 << 1)]   
    ldr         r10, [r11, #(0xC0 << 1)]
    str         r10, [r12, #(0xD6 << 1)]      
    ldr         r10, [r11, #(0xC2 << 1)]
    str         r10, [r12, #(0xD8 << 1)]       
    ldr         r10, [r11, #(0xC4 << 1)]
    str         r10, [r12, #(0xE0 << 1)]        
    ldr         r10, [r11, #(0xC6 << 1)]
    str         r10, [r12, #(0xE2 << 1)]        
    ldr         r10, [r11, #(0xC8 << 1)]
    str         r10, [r12, #(0xE4 << 1)]        
    ldr         r10, [r11, #(0xCA << 1)]
    str         r10, [r12, #(0xE6 << 1)]
    ldr         r10, [r11, #(0xCC << 1)]
    str         r10, [r12, #(0xE8 << 1)]
#endif /* CONFIG_MIU1_DRAM_NONE */
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
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r8, =0xFFFE
    str         r8, [r12, #(0x46 << 1)]
    ldr         r8, =0xFFFF
    str         r8, [r12, #(0x66 << 1)]
    ldr         r8, =0xFFFF
    str         r8, [r12, #(0x86 << 1)]    
    ldr         r8, =0xFFFF
    str         r8, [r12, #(0xA6 << 1)]    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x161500 << 1))
    ldr         r8, =0xFFFF
    str         r8, [r12, #(0x06 << 1)]
    ldr         r8, =0xFFFF
    str         r8, [r12, #(0x26 << 1)]
    
    DELAYUS     2000
    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r8, =0x0400
    str         r8, [r12, #(0x18 << 1)]
    ldr         r8, =0x002F
    str         r8, [r12]
    ldr         r8, =0x052E
    str         r8, [r12]
    ldr         r8, =0x002E
    str         r8, [r12]
    ldr         r8, =0x032E
    str         r8, [r12]
    ldr         r8, =0x002E
    str         r8, [r12]
    
    @// Bit[11] reg_csz_always_on 
    ldr         r8, [r12, #(0x06 << 1)] 
    orr         r8, r8, #0x0800
    str         r8, [r12, #(0x06 << 1)]   
    
    ldr         r8, =0xFFFF
    str         r8, [r12, #(0x46 << 1)]
    ldr         r8, =0x202E
    str         r8, [r12]
#endif /* CONFIG_MIU0_DRAM_NONE */

#ifndef CONFIG_MIU1_DRAM_NONE
    @// [DDR3][enter] <MIU1>
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
    ldr         r8, =0xFFFE
    str         r8, [r12, #(0x46 << 1)]
    ldr         r8, =0xFFFF
    str         r8, [r12, #(0x66 << 1)]
    ldr         r8, =0xFFFF
    str         r8, [r12, #(0x86 << 1)]    
    ldr         r8, =0xFFFF
    str         r8, [r12, #(0xA6 << 1)]    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x162200 << 1))
    ldr         r8, =0xFFFF
    str         r8, [r12, #(0x06 << 1)]
    ldr         r8, =0xFFFF
    str         r8, [r12, #(0x26 << 1)]
    
    DELAYUS     2000
    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
    ldr         r8, =0x0400
    str         r8, [r12, #(0x18 << 1)]
    ldr         r8, =0x002f
    str         r8, [r12]
    ldr         r8, =0x042E
    str         r8, [r12]
    ldr         r8, =0x002E
    str         r8, [r12]
    ldr         r8, =0x032E
    str         r8, [r12]
    ldr         r8, =0x002E
    str         r8, [r12]
    
    @// Bit[11] reg_csz_always_on 
    ldr         r8, [r12, #(0x06 << 1)] 
    orr         r8, r8, #0x0800
    str         r8, [r12, #(0x06 << 1)]   
    
    ldr         r8, =0xFFFF
    str         r8, [r12, #(0x46 << 1)]
    ldr         r8, =0x202E
    str         r8, [r12]
#endif /* CONFIG_MIU1_DRAM_NONE */

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
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r8, [r12, #(0x06 << 1)] 
    bic         r8, r8, #0x0800
    str         r8, [r12, #(0x06 << 1)]    
    
    ldr         r8, =0x002C
    str         r8, [r12]
    ldr         r8, =0xFFFE
    str         r8,[r12, #(0x46 << 1)]
    ldr         r8, =0x002E
    str         r8,[r12]
    ldr         r8, =0x032E
    str         r8,[r12]
    ldr         r8, =0x002E
    str         r8,[r12]
    
    DELAYUS     5
    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r8, =0x001F
    str         r8,[r12]
    ldr         r8, =0xFFFE
    str         r8,[r12, #(0x46 << 1)]
    ldr         r8, =0xFFFF
    str         r8,[r12, #(0x66 << 1)]
    ldr         r8, =0xFFFF
    str         r8,[r12, #(0x86 << 1)]
    ldr         r8, =0xFFFF
    str         r8,[r12, #(0xA6 << 1)]
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x161500 << 1))
    ldr         r8, =0x7FFF
    str         r8,[r12, #(0x06 << 1)]
    ldr         r8, =0xFFFF
    str         r8,[r12, #(0x26 << 1)]
#endif /* CONFIG_MIU0_DRAM_NONE */

#ifndef CONFIG_MIU1_DRAM_NONE
    @// [DDR3][enter] <MIU1>
    @// disable Bit[11] reg_csz_always_on 
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
    ldr         r8, [r12, #(0x06 << 1)] 
    bic         r8, r8, #0x0800
    str         r8, [r12, #(0x06 << 1)]    
    
    ldr         r8, =0x002C
    str         r8, [r12]
    ldr         r8, =0xFFFE
    str         r8,[r12, #(0x46 << 1)]
    ldr         r8, =0x002E
    str         r8,[r12]
    ldr         r8, =0x032E
    str         r8,[r12]
    ldr         r8, =0x002E
    str         r8,[r12]
    
    DELAYUS     5
    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
    ldr         r8, =0x001F
    str         r8,[r12]
    ldr         r8, =0xFFFE
    str         r8,[r12, #(0x46 << 1)]
    ldr         r8, =0xFFFF
    str         r8,[r12, #(0x66 << 1)]
    ldr         r8, =0xFFFF
    str         r8,[r12, #(0x86 << 1)]
    ldr         r8, =0xFFFF
    str         r8,[r12, #(0xA6 << 1)]
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x162200 << 1))
    ldr         r8, =0x7FFF
    str         r8,[r12, #(0x06 << 1)]
    ldr         r8, =0xFFFF
    str         r8,[r12, #(0x26 << 1)]      
#endif /* CONFIG_MIU1_DRAM_NONE */

    bx          lr

@//-------------------------------------------------------------------------------------------------
@// Reset_AVD_str
@// @param  None
@// @return None
@// @note  Reset_AVD_str
@//-------------------------------------------------------------------------------------------------
Reset_AVD_str:

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x103600 << 1))
    ldr         r8, [r12, #(0x12 << 1)] 
    bic         r8, r8, #0x4000
    str         r8, [r12, #(0x12 << 1)]

    orr         r8, r8, #0x4000
    str         r8, [r12, #(0x12 << 1)]
    
    bic         r8, r8, #0x4000
    str         r8, [r12, #(0x12 << 1)]
    
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
#endif /* CONFIG_MIU0_DRAM_NONE */

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
#endif /* CONFIG_MIU1_DRAM_NONE */

    bx          lr

@//-------------------------------------------------------------------------------------------------
@// Bist for str
@// @param  None
@// @return None
@// @note  BistTest_Str
@//-------------------------------------------------------------------------------------------------
#ifdef CONFIG_MSTAR_SELF_STR_TEST_ENABLE
    .global     Miu1_BistTest_Str
Miu1_BistTest_Str:

    DPUTK_STR   MIU_MESSAGE_BIST1_Str

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000   @//1012e0 //reset bist test
    ldr         r11, =0x8000
    str         r11, [r12, #(0xf8 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x8000   @//1012f0 bit_15=1 choice to MIU_1
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x162000 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xf8 << 1)]   
          
    b           Miu_BistTest_Str

    .global     Miu0_BistTest_Str
Miu0_BistTest_Str:

    DPUTK_STR   MIU_MESSAGE_BIST0_Str

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000   @//1012e0 //reset bist test
    str         r11, [r12, #(0xf8 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x0000   @//1012f0 bit_15=0 choice to MIU_0
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x162000 << 1))
    str         r11, [r12, #(0xf8 << 1)] 
    
    .global     Miu_BistTest_Str
Miu_BistTest_Str:
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe2 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e2 << 1)), 0x0000   @//1012e2 //start address base unit:4 k bytes

    ldr         r0, =0xFFFF
    ldr         r11, =0xFFFF                @// bist length (U16)(LENGTH), LENGTH=512
    and         r11, r11, r0
    str         r11, [r12, #(0xe4 << 1)]
    ldr         r11, =0x000F                @// bist length hight (U16) (LENGTH << 16)
    and         r11, r11, r0
    str         r11, [r12, #(0xe6 << 1)]    @//WREG_D      (MS_BUS_RIU_ADDR + (0x1012e4 << 1)), BIST_LEN

    ldr         r11, =0x5aa5
    str         r11, [r12, #(0xe8 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e8 << 1)), 0x5aa5   @//1012e8 //bist test pattern

    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0101   @//bist test mode:3 + read mode

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
#endif

@//================================================================================================
#if 0//def CONFIG_MSTAR_STR_ENABLE
#if 0   //calculate CRC for STR debug
MEM_REGION1_ST      = 0x00200000
MEM_REGION1_SZ      = 0x09F00000
@//MEM_REGION2_ST   = 0x10E00000    @//MIU0
@//MEM_REGION2_SZ   = 0x0C200000    @//MIU0

MEM_REGION2_ST      = 0x01800000    @//MIU1
MEM_REGION2_SZ      = 0x0E800000    @//MIU1

@//Input: r0-region address   r1-resion size
@//Output: r0-CRC value
BDMABank = 0x1F201200
BDMACRC_Calc_MIU:
    ldr         r2, =BDMABank

    mov         r3, #0
    str         r3, [r2, #(0x0c<<2)]
    str         r3, [r2, #(0x0d<<2)]
@// mov         r3, #0x0340
@// str         r3, [r2, #(0x02<<2)]

    str         r0, [r2, #(0x04<<2)]
    str         r0, [r2, #(0x06<<2)]
    lsr         r0, r0, #16
    str         r0, [r2, #(0x05<<2)]
    str         r0, [r2, #(0x07<<2)]

    str         r1, [r2, #(0x08<<2)]
    lsr         r1, r1, #16
    str         r1, [r2, #(0x09<<2)]

    ldr         r3, =0x1DB7
    str         r3, [r2, #(0x0a<<2)]
    ldr         r3, =0x04c1
    str         r3, [r2, #(0x0b<<2)]

    ldr         r3, [r2]
    orr         r3, r3, #1
    str         r3, [r2]

BDMACRC_Calc_agn:
    ldr         r3, [r2, #(0x01<<2)]
    tst         r3, #0x08
    beq         BDMACRC_Calc_agn

    ldr         r3, [r2, #(0x0c<<2)]
    ldr         r0, [r2, #(0x0d<<2)]
    orr         r0, r3, r0, LSL #16

    mov         pc, lr

 SBootMemCRCCheck:
    mov         r8, lr
    PUTK        'S'
    PUTK        'B'
    PUTK        'O'
    PUTK        'O'
    PUTK        'T'
    PUTK        ' '
    PUTK        'C'
    PUTK        'R'
    PUTK        'C'
    PUTK        ':'

    PUTK        '\n'
    PUTK        '\r'

    PUTK        '1'
    PUTK        '.'
    ldr         r0, =MEM_REGION1_ST
    ldr         r1, =MEM_REGION1_SZ
    WREG        (MS_BUS_RIU_ADDR + (0x100904 << 1)), 0x0340
    bl          BDMACRC_Calc_MIU
    bl          put_reg_val
    PUTK        '\n'
    PUTK        '\r'

    PUTK        '2'
    PUTK        '.'
    ldr         r0, =MEM_REGION2_ST
    ldr         r1, =MEM_REGION2_SZ
    WREG        (MS_BUS_RIU_ADDR + (0x100904 << 1)), 0x0341
    bl          BDMACRC_Calc_MIU
    bl          put_reg_val
    PUTK        '\n'
    PUTK        '\r'
    mov         pc, r8
    .ltorg
#endif

.if (MSTAR_STR_SBOOT_RESUME == 1)
read_wkup_pmu:
    ldr         r2, =PMU_WAKEUP_ADDR_REGL
    ldr         r0, [r2]

    ldr         r2, =PMU_WAKEUP_ADDR_REGH
    ldr         r1, [r2]

    and         r0, r0, #PMU_WAKEUP_ADDR_LMASK
    and         r1, r1, #PMU_WAKEUP_ADDR_HMASK
    orr         r0, r0, r1
    mov         pc, lr
    .ltorg

write_wkup_pmu:
    ldr         r3, =PMU_WAKEUP_ADDR_REGL
    ldr         r1, [r3]
    bic         r1, #PMU_WAKEUP_ADDR_LMASK
    and         r2, r0, #PMU_WAKEUP_ADDR_LMASK
    orr         r1, r1, r2
    str         r1, [r3]

    ldr         r3, =PMU_WAKEUP_ADDR_REGH
    ldr         r1, [r3]
    bic         r1, #PMU_WAKEUP_ADDR_HMASK
    and         r2, r0, #PMU_WAKEUP_ADDR_HMASK
    orr         r1, r1, r2
    str         r1, [r3]
    mov         pc, lr
    .ltorg
.endif

text_tbl: .short '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'

@// r9-r12 destroyed
put_reg_val:
    mov         r9, #32
    mov         r11, #0x0F
40:
    sub         r9, #4
    and         r10, r11, r0, LSR r9
    ldr         r12, =text_tbl
    add         r12, r12, r10, lsl #1
    ldr         r10,  [r12]
    mov         r12, #0x1F000000
    orr         r12, r12, #0x00200000
    orr         r12, r12, #0x1300
    strb        r10,[r12]
    cmp         r9, #0
    bgt         40b

@// mov         r10, #'\r'      /* new line */
@// strb        r10,[r12]
@// mov         r10, #'\n'
@// strb        r10,[r12]
    mov         r10, #'-'
    strb        r10,[r12]

    mov         pc, lr
    .ltorg
#endif