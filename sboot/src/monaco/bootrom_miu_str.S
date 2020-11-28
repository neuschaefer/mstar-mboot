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

#ifndef _MIUSEL_MONACO_2MIU_H_
#include "MIUSEL_MONACO_2MIU.h"
#endif

    .text
    
    MIU_MESSAGE_BIST0_Str:      .short   'B', 'I', 'S', 'T', '0', '-', 0x00
    MIU_MESSAGE_BIST1_Str:      .short   'B', 'I', 'S', 'T', '1', '-', 0x00
    MIU_MESSAGE_BIST2_Str:      .short   'B', 'I', 'S', 'T', '2', '-', 0x00
    MIU_MESSAGE_OK_Str:         .short   'O', 'K', '\n', '\r', 0x00
    MIU_MESSAGE_FAIL_Str:       .short   'F', 'A', 'I', 'L', '\n', '\r', 0x00
    MESSAGE_DC_ON_STR:          .short  '\r', '\n', 'S', 'T', 'R', '_', 'O', 'N', '\r', '\n', 0x00
    
    .align      4
    .global     BootRom_InitMiu_STR
BootRom_InitMiu_STR:

    mov         r13, lr
    
    DPUTK_STR   MESSAGE_DC_ON_STR

    DBGREG      0x2001

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

    ldr         r0, =MIU_PreInit
    bl          MDrv_WriteRegTbl32 

    @//  AVD reset
    bl          Reset_AVD_str 
    
#if !defined(CONFIG_MIU0_DRAM_NONE)
    @// MIU0: DDR3-1866 PLL-SETTING
    WREG        (MS_BUS_RIU_ADDR + (0x110d78 << 1)), 0x0001
    DELAYUS     10
    WREG        (MS_BUS_RIU_ADDR + (0x110d24 << 1)), 0x1000
    DELAYUS     10
    WREG        (MS_BUS_RIU_ADDR + (0x110d24 << 1)), 0x0000
    DELAYUS     10
    WREG        (MS_BUS_RIU_ADDR + (0x110d36 << 1)), 0x0400
    WREG        (MS_BUS_RIU_ADDR + (0x110d34 << 1)), 0x2004
#if defined(CONFIG_MIU0_DDR3_1666)    
    WREG        (MS_BUS_RIU_ADDR + (0x110d30 << 1)), 0x7236
    WREG        (MS_BUS_RIU_ADDR + (0x110d32 << 1)), 0x0023
#elif defined(CONFIG_MIU0_DDR3_1866)
    WREG        (MS_BUS_RIU_ADDR + (0x110d30 << 1)), 0x8f5c
    WREG        (MS_BUS_RIU_ADDR + (0x110d32 << 1)), 0x001e
#elif defined(CONFIG_MIU0_DDR3_2133)
    WREG        (MS_BUS_RIU_ADDR + (0x110d30 << 1)), 0xffff
    WREG        (MS_BUS_RIU_ADDR + (0x110d32 << 1)), 0x001a
#elif defined(CONFIG_MIU0_DDR4_2400)
    WREG        (MS_BUS_RIU_ADDR + (0x110d30 << 1)), 0x3333
    WREG        (MS_BUS_RIU_ADDR + (0x110d32 << 1)), 0x0017
#else
    #error "Invalid DRAM Setting"
#endif        
    DELAYUS     100
    
    WREG        (MS_BUS_RIU_ADDR + (0x110d22 << 1)), 0x0004

    DELAYUS     500        
    
    @// ===== MIU0 DDR INIT ===== //@
    ldr         r0, =MIU0_DDR_Init
    bl          MDrv_WriteRegTbl32   
#endif /* CONFIG_MIU0_DRAM_NONE */
    
#if !defined(CONFIG_MIU1_DRAM_NONE)
    @// MIU1: DDR3-1866 PLL-SETTING
    WREG        (MS_BUS_RIU_ADDR + (0x161678 << 1)), 0x0001
    DELAYUS     10
    WREG        (MS_BUS_RIU_ADDR + (0x161624 << 1)), 0x1000
    DELAYUS     10
    WREG        (MS_BUS_RIU_ADDR + (0x161624 << 1)), 0x0000
    DELAYUS     10
    WREG        (MS_BUS_RIU_ADDR + (0x161636 << 1)), 0x0400
    WREG        (MS_BUS_RIU_ADDR + (0x161634 << 1)), 0x2004
#if defined(CONFIG_MIU1_DDR3_1666)    
    WREG        (MS_BUS_RIU_ADDR + (0x161630 << 1)), 0x7236
    WREG        (MS_BUS_RIU_ADDR + (0x161632 << 1)), 0x0023
#elif defined(CONFIG_MIU1_DDR3_1866)
    WREG        (MS_BUS_RIU_ADDR + (0x161630 << 1)), 0x8f5c
    WREG        (MS_BUS_RIU_ADDR + (0x161632 << 1)), 0x001e
#elif defined(CONFIG_MIU1_DDR3_2133)
    WREG        (MS_BUS_RIU_ADDR + (0x161630 << 1)), 0xffff
    WREG        (MS_BUS_RIU_ADDR + (0x161632 << 1)), 0x001a
#elif defined(CONFIG_MIU1_DDR4_2400)
    WREG        (MS_BUS_RIU_ADDR + (0x161630 << 1)), 0x3333
    WREG        (MS_BUS_RIU_ADDR + (0x161632 << 1)), 0x0017
#else
    #error "Invalid DRAM Setting"
#endif
    DELAYUS     100

    WREG        (MS_BUS_RIU_ADDR + (0x161622 << 1)), 0x0004

    DELAYUS     500

    @// ===== MIU1 DDR INIT ===== //@
    ldr         r0, =MIU1_DDR_Init
    bl          MDrv_WriteRegTbl32
#endif /* CONFIG_MIU1_DRAM_NONE */

#if !defined(CONFIG_MIU2_DRAM_NONE)
    @// MIU2: DDR3-1866 PLL-SETTING
    WREG        (MS_BUS_RIU_ADDR + (0x162178 << 1)), 0x0001
    DELAYUS     10
    WREG        (MS_BUS_RIU_ADDR + (0x162124 << 1)), 0x1000
    DELAYUS     10
    WREG        (MS_BUS_RIU_ADDR + (0x162124 << 1)), 0x0000
    DELAYUS     10
    WREG        (MS_BUS_RIU_ADDR + (0x162136 << 1)), 0x0400
    WREG        (MS_BUS_RIU_ADDR + (0x162134 << 1)), 0x2004
#if defined(CONFIG_MIU2_DDR3_1666)    
    WREG        (MS_BUS_RIU_ADDR + (0x162130 << 1)), 0x7236
    WREG        (MS_BUS_RIU_ADDR + (0x162132 << 1)), 0x0023
#elif defined(CONFIG_MIU2_DDR3_1866)
    WREG        (MS_BUS_RIU_ADDR + (0x162130 << 1)), 0x8f5c
    WREG        (MS_BUS_RIU_ADDR + (0x162132 << 1)), 0x001e
#elif defined(CONFIG_MIU2_DDR3_2133)
    WREG        (MS_BUS_RIU_ADDR + (0x162130 << 1)), 0xffff
    WREG        (MS_BUS_RIU_ADDR + (0x162132 << 1)), 0x001a
#elif defined(CONFIG_MIU2_DDR4_2400)
    WREG        (MS_BUS_RIU_ADDR + (0x162130 << 1)), 0x3333
    WREG        (MS_BUS_RIU_ADDR + (0x162132 << 1)), 0x0017
#else
    #error "Invalid DRAM Setting"
#endif
    DELAYUS     100

    WREG        (MS_BUS_RIU_ADDR + (0x162122 << 1)), 0x0004    

    DELAYUS     500
    
    ldr         r0, =MIU2_DDR_Init
    bl          MDrv_WriteRegTbl32
#endif /* CONFIG_MIU2_DRAM_NONE */
    
    @// restore deskew     
    bl  Miu_auto_phase_str
      
#if !defined(CONFIG_MIU0_DRAM_NONE)
    @//MIU0 INIT Cycle    
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0008  @//DRAM reset    
    DELAYUS     200                                          @//delay 200us
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0000  @//hold miu_0
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0004  @//DRAM reset+CS
    DELAYUS     500                                          @//delay 500us
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0006  @//DRAM reset+CS+CKE
    DELAYUS     4                                            @//delay 4us
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0017  @//DRAM reset+CS+CKE+auto cycle+ODE
CheckMiu0Init:
    RREG        r1, (MS_BUS_RIU_ADDR + (0x101200 << 1))
    and         r1, r1, #0x8000
    cmp         r1, #0
    beq         CheckMiu0Init
#endif /* CONFIG_MIU0_DRAM_NONE */
  
#if !defined(CONFIG_MIU1_DRAM_NONE)
    @//MIU1 INIT Cycle    
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0008  @//DRAM reset
    DELAYUS     200                                          @//delay 200us
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0000  @//hold miu_1
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0004  @//DRAM reset+CS
    DELAYUS     500                                          @//delay 500us
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0006  @//DRAM reset+CS+CKE
    DELAYUS     4                                            @//delay 4us
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0017  @//DRAM reset+CS+CKE+auto cycle+ODE
CheckMiu1Init:
    RREG        r1, (MS_BUS_RIU_ADDR + (0x100600 << 1))
    and         r1, r1, #0x8000
    cmp         r1, #0
    beq         CheckMiu1Init
#endif /* CONFIG_MIU1_DRAM_NONE */

#if !defined(CONFIG_MIU2_DRAM_NONE)
    @//MIU2 INIT Cycle    
    WREG        (MS_BUS_RIU_ADDR + (0x162000 << 1)), 0x0008 @//DRAM reset
    DELAYUS     200                                         @//delay 200us
    WREG        (MS_BUS_RIU_ADDR + (0x162000 << 1)), 0x0000 @//hold miu_2
    WREG        (MS_BUS_RIU_ADDR + (0x162000 << 1)), 0x0004 @//DRAM reset+CS
    DELAYUS     500                                         @//delay 500us
    WREG        (MS_BUS_RIU_ADDR + (0x162000 << 1)), 0x0006 @//DRAM reset+CS+CKE
    DELAYUS     4                                           @//delay 4us
    WREG        (MS_BUS_RIU_ADDR + (0x162000 << 1)), 0x0017 @//DRAM reset+CS+CKE+auto cycle+ODE
CheckMiu2Init:
    RREG        r1, (MS_BUS_RIU_ADDR + (0x162000 << 1))
    and         r1, r1, #0x8000
    cmp         r1, #0
    beq         CheckMiu2Init
#endif /* CONFIG_MIU2_DRAM_NONE */ 
@//-----------------------------------STR--------------------------------------   
    @// enter refreseh 
    bl  Enter_DDR_RefreshMode    
    DELAYUS     1000   
    
    @// disable oenz
    bl  Miu_str_oenz_disable

    DELAYUS     1 
    
    @// ATOP_PD on
#ifndef CONFIG_MIU0_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x110d54 <<1 )), 0xC000 @//ATOP_PD off
#endif
#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x161654 <<1 )), 0xC000 @//ATOP_PD off
#endif
#ifndef CONFIG_MIU2_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x162154 <<1 )), 0xC000 @//ATOP_PD off
#endif

    @// rx enable
#ifndef CONFIG_MIU0_DRAM_NONE    
    WREG        (MS_BUS_RIU_ADDR + (0x110d08 << 1)), 0x003f
#endif
#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x161608 << 1)), 0x003f
#endif
#ifndef CONFIG_MIU2_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x162108 << 1)), 0x003f
#endif
    
    @// exit refresh 
    bl  Exit_DDR_RefreshMode
    
    DELAYUS     300
    
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
    
    @// miu2
    ldr         r1, =(MS_BUS_RIU_ADDR + (0x162100 << 1))
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
     
@//-----------------------------------STR--------------------------------------   
    bl          MIU_Set_Group_Priority_Str

    ldr         r0, =MIU_PostInit
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
#endif /* CONFIG_MIU0_DRAM_NONE */

#ifndef CONFIG_MIU1_DRAM_NONE
    RREG        r8, (MS_BUS_RIU_ADDR + (0x100602 << 1))
    bic         r8, r8, #0xf000
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x100602 << 1))
#endif /* CONFIG_MIU1_DRAM_NONE */

#ifndef CONFIG_MIU2_DRAM_NONE
    RREG        r8, (MS_BUS_RIU_ADDR + (0x162002 << 1))
    bic         r8, r8, #0xf000
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x162002 << 1))
#endif /* CONFIG_MIU2_DRAM_NONE */

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

#ifndef CONFIG_MIU2_DRAM_NONE
    ldr         r11, =(MS_BUS_RIU_ADDR + (0x103300 << 1))
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x162100 << 1))
    ldr         r10, [r11, #(0xCE << 1)]
    str         r10, [r12, #(0x2E << 1)]  
    ldr         r10, [r11, #(0xD0 << 1)]
    str         r10, [r12, #(0xA0 << 1)]      
    ldr         r10, [r11, #(0xD2 << 1)]
    str         r10, [r12, #(0xA2 << 1)]   
    ldr         r10, [r11, #(0xD4 << 1)]
    str         r10, [r12, #(0xA4 << 1)]      
    ldr         r10, [r11, #(0xD6 << 1)]
    str         r10, [r12, #(0xA6 << 1)]       
    ldr         r10, [r11, #(0xD8 << 1)]
    str         r10, [r12, #(0xA8 << 1)]        
    ldr         r10, [r11, #(0xDA << 1)]
    str         r10, [r12, #(0xAA << 1)]        
    ldr         r10, [r11, #(0xDC << 1)]
    str         r10, [r12, #(0xAC << 1)]        
    ldr         r10, [r11, #(0xDE << 1)]
    str         r10, [r12, #(0xAE << 1)] 
    
    ldr         r11, =(MS_BUS_RIU_ADDR + (0x161500 << 1))     
    ldr         r10, [r11, #(0x9C << 1)]
    str         r10, [r12, #(0xD0 << 1)]  
    ldr         r10, [r11, #(0x9E << 1)]
    str         r10, [r12, #(0xD2 << 1)]      
    ldr         r10, [r11, #(0xAC << 1)]
    str         r10, [r12, #(0xD4 << 1)]   
    ldr         r10, [r11, #(0xAE << 1)]    
    str         r10, [r12, #(0xD6 << 1)] 
       
    ldr         r11, =(MS_BUS_RIU_ADDR + (0x162200 << 1))   
    ldr         r10, [r11, #(0x9C << 1)]
    str         r10, [r12, #(0xD8 << 1)]       
    ldr         r10, [r11, #(0x9E << 1)]
    str         r10, [r12, #(0xE0 << 1)]        
    ldr         r10, [r11, #(0xAC << 1)]
    str         r10, [r12, #(0xE2 << 1)]        
    ldr         r10, [r11, #(0xAE << 1)]         
    str         r10, [r12, #(0xE4 << 1)] 
    
    ldr         r11, =(MS_BUS_RIU_ADDR + (0x162300 << 1))        
    ldr         r10, [r11, #(0x9C << 1)]
    str         r10, [r12, #(0xE6 << 1)]
    ldr         r10, [r11, #(0x9E << 1)]
    str         r10, [r12, #(0xE8 << 1)]
#endif /* CONFIG_MIU2_DRAM_NONE */    
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
    ldr         r10, =0xFFFE
    str         r10, [r12, #(0x46 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0x66 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0x86 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0xA6 << 1)]
    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x161500 << 1)) 
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0x06 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0x26 << 1)]
    
    DELAYUS     2000
    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1)) 
    ldr         r10, =0x0400
    str         r10, [r12, #(0x18 << 1)]
    ldr         r10, =0x0027
    str         r10, [r12]
    ldr         r10, =0x0427
    str         r10, [r12]
    ldr         r10, =0x0527
    str         r10, [r12]
    ldr         r10, =0x0027
    str         r10, [r12]
    
    @// Bit[11] reg_csz_always_on 
    RREG        r8, (MS_BUS_RIU_ADDR + (0x101206 << 1))
    orr         r8, r8, #0x0800
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x101206 << 1))
    
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x2027
#endif /* CONFIG_MIU0_DRAM_NONE */

#ifndef CONFIG_MIU1_DRAM_NONE
    @// [DDR3][enter] <MIU1>
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x100600 << 1))   
    ldr         r10, =0xFFFE
    str         r10, [r12, #(0x46 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0x66 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0x86 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0xA6 << 1)]
    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x162200 << 1)) 
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0x06 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0x26 << 1)]
    
    DELAYUS     2000

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x100600 << 1)) 
    ldr         r10, =0x0400
    str         r10, [r12, #(0x18 << 1)]
    ldr         r10, =0x0027
    str         r10, [r12]
    ldr         r10, =0x0427
    str         r10, [r12]
    ldr         r10, =0x0527
    str         r10, [r12]
    ldr         r10, =0x0027
    str         r10, [r12]
    
    @// Bit[11] reg_csz_always_on 
    RREG        r8, (MS_BUS_RIU_ADDR + (0x100606 << 1))
    orr         r8, r8, #0x0800
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x100606 << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x2027
#endif /* CONFIG_MIU1_DRAM_NONE */

#ifndef CONFIG_MIU2_DRAM_NONE
    @// [DDR3][enter] <MIU2>
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x162000 << 1))   
    ldr         r10, =0xFFFE
    str         r10, [r12, #(0x46 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0x66 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0x86 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0xA6 << 1)]
    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x162300 << 1)) 
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0x06 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0x26 << 1)]
    
    DELAYUS     2000
    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x162000 << 1)) 
    ldr         r10, =0x0400
    str         r10, [r12, #(0x18 << 1)]
    ldr         r10, =0x0027
    str         r10, [r12]
    ldr         r10, =0x0427
    str         r10, [r12]
    ldr         r10, =0x0527
    str         r10, [r12]
    ldr         r10, =0x0027
    str         r10, [r12]
    
    @// Bit[11] reg_csz_always_on 
    RREG        r8, (MS_BUS_RIU_ADDR + (0x162006 << 1))
    orr         r8, r8, #0x0800
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x162006 << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x162046 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x162000 << 1)), 0x2027
#endif /* CONFIG_MIU2_DRAM_NONE */

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
    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))   
    ldr         r10, =0x0017
    str         r10, [r12]
    ldr         r10, =0xFFFE
    str         r10, [r12, #(0x46 << 1)]
    ldr         r10, =0x0227
    str         r10, [r12]
    ldr         r10, =0x0327
    str         r10, [r12]
    ldr         r10, =0x0027
    str         r10, [r12]
    ldr         r10, =0x0007
    str         r10, [r12]
    
    DELAYUS     5
    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1)) 
    ldr         r10, =0x0017
    str         r10, [r12]
    ldr         r10, =0xFFFE
    str         r10, [r12, #(0x46 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0x66 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0x86 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0xA6 << 1)]
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x161500 << 1)) 
    ldr         r10, =0x7FFF
    str         r10, [r12, #(0x06 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0x26 << 1)]  
#endif /* CONFIG_MIU0_DRAM_NONE */

#ifndef CONFIG_MIU1_DRAM_NONE
    @// [DDR3][enter] <MIU1>
    @// disable Bit[11] reg_csz_always_on 
    RREG        r8, (MS_BUS_RIU_ADDR + (0x100606 << 1))
    bic         r8, r8, #0x0800
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x100606 << 1))
    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x100600 << 1))   
    ldr         r10, =0x0017
    str         r10, [r12]
    ldr         r10, =0xFFFE
    str         r10, [r12, #(0x46 << 1)]
    ldr         r10, =0x0227
    str         r10, [r12]
    ldr         r10, =0x0327
    str         r10, [r12]
    ldr         r10, =0x0027
    str         r10, [r12]
    ldr         r10, =0x0007
    str         r10, [r12]
    
    DELAYUS     5
    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x100600 << 1)) 
    ldr         r10, =0x0017
    str         r10, [r12]
    ldr         r10, =0xFFFE
    str         r10, [r12, #(0x46 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0x66 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0x86 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0xA6 << 1)]
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x162200 << 1)) 
    ldr         r10, =0x7FFF
    str         r10, [r12, #(0x06 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0x26 << 1)]
#endif /* CONFIG_MIU1_DRAM_NONE */

#ifndef CONFIG_MIU2_DRAM_NONE
    @// [DDR3][enter] <MIU2>
    @// disable Bit[11] reg_csz_always_on 
    RREG        r8, (MS_BUS_RIU_ADDR + (0x162006 << 1))
    bic         r8, r8, #0x0800
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x162006 << 1))
    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x162000 << 1))   
    ldr         r10, =0x0017
    str         r10, [r12]
    ldr         r10, =0xFFFE
    str         r10, [r12, #(0x46 << 1)]
    ldr         r10, =0x0227
    str         r10, [r12]
    ldr         r10, =0x0327
    str         r10, [r12]
    ldr         r10, =0x0027
    str         r10, [r12]
    ldr         r10, =0x0007
    str         r10, [r12]
    
    DELAYUS     5
    
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x162000 << 1)) 
    ldr         r10, =0x0017
    str         r10, [r12]
    ldr         r10, =0xFFFE
    str         r10, [r12, #(0x46 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0x66 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0x86 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0xA6 << 1)]
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x162300 << 1)) 
    ldr         r10, =0x7FFF
    str         r10, [r12, #(0x06 << 1)]
    ldr         r10, =0xFFFF
    str         r10, [r12, #(0x26 << 1)]
#endif /* CONFIG_MIU2_DRAM_NONE */

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
    .global     Miu2_BistTest_Str
Miu2_BistTest_Str:
    DPUTK_STR   MIU_MESSAGE_BIST2_Str

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000   @//1012e0 //reset bist test
    ldr         r11, =0x0000
    str         r11, [r12, #(0xf8 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012f8 << 1)), 0x0000   @//1012f8 bit_15=0 choice to MIU_2
    WREG        (MS_BUS_RIU_ADDR + (0x1620f8 << 1)), 0x8000                                              @//1620f8 bit_15=1 choice to MIU_2
    b           Miu_BistTest_Str
   
    .global     Miu1_BistTest_Str
Miu1_BistTest_Str:
    DPUTK_STR   MIU_MESSAGE_BIST1_Str

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000   @//1012e0 //reset bist test
    ldr         r11, =0x8000
    str         r11, [r12, #(0xf8 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012f8 << 1)), 0x8000   @//1012f0 bit_15=1 choice to MIU_1
    WREG        (MS_BUS_RIU_ADDR + (0x1620f8 << 1)), 0x0000
    b           Miu_BistTest_Str

    .global     Miu0_BistTest_Str
Miu0_BistTest_Str:
    DPUTK_STR   MIU_MESSAGE_BIST0_Str

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000   @//1012e0 //reset bist test
    str         r11, [r12, #(0xf8 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x0000   @//1012f0 bit_15=0 choice to MIU_0
    WREG        (MS_BUS_RIU_ADDR + (0x1620f8 << 1)), 0x0000
    
    .global     Miu_BistTest_Str
Miu_BistTest_Str:
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe2 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e2 << 1)), 0x0000   @//1012e2 //start address base unit:4 k bytes

    ldr         r0, =0xFFFF
    ldr         r11, =0xFFFF
    and         r11, r11, r0
    str         r11, [r12, #(0xe4 << 1)]
    ldr         r11, =0x00F
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
    
