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

#ifndef _MIUSEL_MUJI_2MIU_H_
#include "MIUSEL_MUJI_2MIU.h"
#endif

    .text
    
    MIU_MESSAGE_BIST0_Str:      .short   'S', 't', 'r', '_', 'B', 'I', 'S', 'T', '0', '-', 0x00
    MIU_MESSAGE_BIST1_Str:      .short   'S', 't', 'r', '_', 'B', 'I', 'S', 'T', '1', '-', 0x00
    MIU_MESSAGE_OK_Str:         .short   'O', 'K', '\n', '\r', 0x00
    MIU_MESSAGE_FAIL_Str:       .short   'F', 'A', 'I', 'L', '\n', '\r', 0x00
    MESSAGE_DC_ON_STR:          .short  '\r', '\n', 'S', 'T', 'R', '_', 'D', 'C', '_', 'O', 'N', '\r', '\n', 0x00
    
    .align      4
    .global     BootRom_InitMiu_STR
BootRom_InitMiu_STR:

    mov         x29, x30
    
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

    ldr         x8, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
_CheckDramData:
    ldr         w7, [x8, #(0x00 << 1)]
    and         w7, w7, #0x8000
    cmp         w7, #0
    b.eq         _CheckDramData

#else

    ldr         x0, =MIU_PreInit
    bl          MDrv_WriteRegTbl32 

    #//  AVD reset
    bl          Reset_AVD_str
    
#if !defined(CONFIG_MIU0_DRAM_NONE)
    #// MIU0: DDR3-1866 PLL-SETTING
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
#elif defined(CONFIG_MIU1_DDR4_2400)
#else
    #error "Invalid DRAM Setting"
#endif     
    DELAYUS     100
    
    WREG        (MS_BUS_RIU_ADDR + (0x110d22 << 1)), 0x0004

    DELAYUS     500
    
    // ===== MIU0 DDR INIT ===== //
    ldr         x0, =MIU0_DDR_Init
    bl          MDrv_WriteRegTbl32 
  
    RREG        w8, (MS_BUS_RIU_ADDR + (0x101202 << 1))
    orr         w8, w8, #0xf000
    REG_C2M     w8, (MS_BUS_RIU_ADDR + (0x101202 << 1))
    
    RREG        w8, (MS_BUS_RIU_ADDR + (0x110d00 << 1))
    bic         w8, w8, #0x0018
    orr         w8, w8, #0x0008
    REG_C2M     w8, (MS_BUS_RIU_ADDR + (0x110d00 << 1))
    
    RREG        w8, (MS_BUS_RIU_ADDR + (0x110d54 << 1))
    orr         w8, w8, #0x0070
    REG_C2M     w8, (MS_BUS_RIU_ADDR + (0x110d54 << 1)) 
#endif /* CONFIG_MIU0_DRAM_NONE */
    
#if !defined(CONFIG_MIU1_DRAM_NONE)
    #// MIU1: DDR3-1866 PLL-SETTING
    WREG        (MS_BUS_RIU_ADDR + (0x161678 << 1)), 0x0001
    DELAYUS     10
    WREG        (MS_BUS_RIU_ADDR + (0x161624 << 1)), 0x1000
    DELAYUS     10
    WREG        (MS_BUS_RIU_ADDR + (0x161624 << 1)), 0x0000
    DELAYUS     10
    WREG        (MS_BUS_RIU_ADDR + (0x161636 << 1)), 0x0400
    WREG        (MS_BUS_RIU_ADDR + (0x161634 << 1)), 0x2004
#if defined(CONFIG_MIU0_DDR3_1666) 
    WREG        (MS_BUS_RIU_ADDR + (0x161630 << 1)), 0x7236
    WREG        (MS_BUS_RIU_ADDR + (0x161632 << 1)), 0x0023
#elif defined(CONFIG_MIU0_DDR3_1866)
    WREG        (MS_BUS_RIU_ADDR + (0x161630 << 1)), 0x8f5c
    WREG        (MS_BUS_RIU_ADDR + (0x161632 << 1)), 0x001e
#elif defined(CONFIG_MIU0_DDR3_2133)
    WREG        (MS_BUS_RIU_ADDR + (0x161630 << 1)), 0xffff
    WREG        (MS_BUS_RIU_ADDR + (0x161632 << 1)), 0x001a
#elif defined(CONFIG_MIU1_DDR4_2400)
#else
    #error "Invalid DRAM Setting"
#endif
    DELAYUS     100

    WREG        (MS_BUS_RIU_ADDR + (0x161622 << 1)), 0x0004

    DELAYUS     500

    // ===== MIU1 DDR INIT ===== //
    ldr         x0, =MIU1_DDR_Init
    bl          MDrv_WriteRegTbl32
    
    RREG        w8, (MS_BUS_RIU_ADDR + (0x100602 << 1))
    orr         w8, w8, #0xf000
    REG_C2M     w8, (MS_BUS_RIU_ADDR + (0x100602 << 1))
    
    RREG        w8, (MS_BUS_RIU_ADDR + (0x161600 << 1))
    bic         w8, w8, #0x0018
    orr         w8, w8, #0x0008
    REG_C2M     w8, (MS_BUS_RIU_ADDR + (0x161600 << 1))
    
    REG         w8, (MS_BUS_RIU_ADDR + (0x161654 << 1))
    orr         w8, w8, #0x0070
    REG_C2M     w8, (MS_BUS_RIU_ADDR + (0x161654 << 1))
#endif /* CONFIG_MIU1_DRAM_NONE */

    
#if !defined(CONFIG_MIU0_DRAM_NONE)
    #//MIU0 INIT Cycle 
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0008  //DRAM reset  
    DELAYUS     200                                          //delay 200us
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0000  //hold miu_0
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0004  //DRAM reset+CS
    DELAYUS     500                                          //delay 500us
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0006  //DRAM reset+CS+CKE
    DELAYUS     4                                            //delay 4us
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0017  //DRAM reset+CS+CKE+auto cycle+ODE
CheckMiu0Init:
    RREG        w7, (MS_BUS_RIU_ADDR + (0x101200 << 1))
    and         w7, w7, #0x8000
    cmp         w1, #0
    b.eq         CheckMiu0Init
#endif /* CONFIG_MIU0_DRAM_NONE */
  
#if !defined(CONFIG_MIU1_DRAM_NONE)
    #//MIU1 INIT Cycle
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0008  //DRAM reset
    DELAYUS     200                                          //delay 200us
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0000  //hold miu_1
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0004  //DRAM reset+CS
    DELAYUS     500                                          //delay 500us
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0006  //DRAM reset+CS+CKE
    DELAYUS     4                                            //delay 4us
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0017  //DRAM reset+CS+CKE+auto cycle+ODE
CheckMiu1Init:
    RREG        w7, (MS_BUS_RIU_ADDR + (0x100600 << 1))
    and         w7, r1, #0x8000
    cmp         w7, #0
    b.eq         CheckMiu1Init
#endif /* CONFIG_MIU1_DRAM_NONE */

//-----------------------------------STR--------------------------------------//
    bl  Miu_auto_phase_str

    #// enter refreseh 
    bl  Enter_DDR_RefreshMode
    DELAYUS     1000
     
    
    #// disable oenz
    bl  Miu_str_oenz_disable
    DELAYUS     1
    
    
    #// ATOP_PD on
#ifndef CONFIG_MIU0_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x110d54 <<1 )), 0x8000  //ATOP_PD off
#endif
#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x161654 <<1 )), 0x8000  //ATOP_PD off
#endif
#ifndef CONFIG_MIU2_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x162154 <<1 )), 0x8000  //ATOP_PD off
#endif

    #// rx enable
#ifndef CONFIG_MIU0_DRAM_NONE 
    WREG        (MS_BUS_RIU_ADDR + (0x110d08 << 1)), 0x003f
#endif

#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x161608 << 1)), 0x003f
#endif

#ifndef CONFIG_MIU2_DRAM_NONE
    WREG        (MS_BUS_RIU_ADDR + (0x162108 << 1)), 0x003f
#endif
    
    #// exit refresh 
    bl  Exit_DDR_RefreshMode
    DELAYUS     300 

    
//-----------------------------------STR--------------------------------------//

    bl          MIU_Set_Group_Priority_Str

    ldr         x0, =MIU_PostInit
    bl          MDrv_WriteRegTbl32

#endif

    mov         x30, x29
    ret
    .size       BootRom_InitMiu_STR,.-BootRom_InitMiu_STR

#//-------------------------------------------------------------------------------------------------
#// Miu_str_oenz_disable
#// @param  None
#// @return None
#// @note   Miu_str_oenz_disable
#//-------------------------------------------------------------------------------------------------
Miu_str_oenz_disable:
#ifndef CONFIG_MIU0_DRAM_NONE
    RREG        w8, (MS_BUS_RIU_ADDR + (0x101202 << 1))
    bic         w8, w8, #0xf000
    REG_C2M     w8, (MS_BUS_RIU_ADDR + (0x101202 << 1))
#endif /* CONFIG_MIU0_DRAM_NONE */

#ifndef CONFIG_MIU1_DRAM_NONE
    RREG        w8, (MS_BUS_RIU_ADDR + (0x100602 << 1))
    bic         w8, w8, #0xf000
    REG_C2M     w8, (MS_BUS_RIU_ADDR + (0x100602 << 1))
#endif /* CONFIG_MIU1_DRAM_NONE */

    ret

#//-------------------------------------------------------------------------------------------------
#// Miu_auto_phase_str
#// @param  None
#// @return None
#// @note   Miu_auto_phase_str
#//-------------------------------------------------------------------------------------------------
Miu_auto_phase_str:
    #// Re write MIU auto phase
#ifndef CONFIG_MIU0_DRAM_NONE
    RREG        w8, (MS_BUS_RIU_ADDR + (0x3DB2 << 1))
    REG_C2M     w8, (MS_BUS_RIU_ADDR + (0x110D6C << 1))
    RREG        w8, (MS_BUS_RIU_ADDR + (0x3DB6 << 1))
    REG_C2M     w8, (MS_BUS_RIU_ADDR + (0x110D6E << 1))
#endif /* CONFIG_MIU0_DRAM_NONE */

#ifndef CONFIG_MIU1_DRAM_NONE
    RREG        w8, (MS_BUS_RIU_ADDR + (0x3DB8 << 1))
    REG_C2M     w8, (MS_BUS_RIU_ADDR + (0x16166c << 1))
    RREG        w8, (MS_BUS_RIU_ADDR + (0x3DBA << 1))
    REG_C2M     w8, (MS_BUS_RIU_ADDR + (0x16166e << 1))
#endif /* CONFIG_MIU1_DRAM_NONE */
    
    ret

#//-------------------------------------------------------------------------------------------------
#// Enter_DDR_RefreshMode
#// @param  None
#// @return None
#// @note   Enter_DDR_RefreshMode
#//-------------------------------------------------------------------------------------------------
Enter_DDR_RefreshMode:
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000
    
#ifndef CONFIG_MIU0_DRAM_NONE
    #// [DDR3][enter] <MIU0>  
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0xFFFE
    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x1012a6 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x1012a6 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x161506 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x161526 << 1)), 0xFFFF
    
    DELAYUS     2000
    
    WREG        (MS_BUS_RIU_ADDR + (0x101218 << 1)), 0x0400 //reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0027 //Bit[05]reg_auto_ref_off
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0427 //trig precharge all
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0527
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0027
    
    #// Bit[11] reg_csz_always_on 
    RREG        w8, (MS_BUS_RIU_ADDR + (0x101206 << 1))
    orr         w8, w8, #0x0800
    REG_C2M     w8, (MS_BUS_RIU_ADDR + (0x101206 << 1))
    
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x2027
#endif /* CONFIG_MIU0_DRAM_NONE */

#ifndef CONFIG_MIU1_DRAM_NONE
    #// [DDR3][enter] <MIU1>
    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0xFFFE
    WREG        (MS_BUS_RIU_ADDR + (0x100666 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x100686 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x1006a6 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x162206 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x162226 << 1)), 0xFFFF
    
    DELAYUS     2000

    WREG        (MS_BUS_RIU_ADDR + (0x100618 << 1)), 0x0400 //reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0027 //Bit[05]reg_auto_ref_off
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0424 //trig precharge all
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0527
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0027
    
    #// Bit[11] reg_csz_always_on 
    RREG        w8, (MS_BUS_RIU_ADDR + (0x100606 << 1))
    orr         w8, w8, #0x0800
    REG_C2M     w8, (MS_BUS_RIU_ADDR + (0x100606 << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x2027
#endif /* CONFIG_MIU1_DRAM_NONE */

    ret

#//-------------------------------------------------------------------------------------------------
#// Exit_DDR_RefreshMode
#// @param  None
#// @return None
#// @note   Exit_DDR_RefreshMode
#//-------------------------------------------------------------------------------------------------
Exit_DDR_RefreshMode:

#ifndef CONFIG_MIU0_DRAM_NONE
    #// [DDR3][exit] <MIU0>
    #// disable Bit[11] reg_csz_always_on 
    RREG        w8, (MS_BUS_RIU_ADDR + (0x101206 << 1))
    bic         w8, w8, #0x0800
    REG_C2M     w8, (MS_BUS_RIU_ADDR + (0x101206 << 1)) 
    
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0017
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0xFFFE
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0227
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0327
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0027
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0007
    
    DELAYUS     5
    
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0017
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0xfffe
    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0xffff  //Bit[12]reg_cke_always_on
    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0xffff  //reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x1012A6 << 1)), 0xffff  //Bit[05]reg_auto_ref_off
    WREG        (MS_BUS_RIU_ADDR + (0x161506 << 1)), 0x7fff
    WREG        (MS_BUS_RIU_ADDR + (0x161526 << 1)), 0xffff
#endif /* CONFIG_MIU0_DRAM_NONE */

#ifndef CONFIG_MIU1_DRAM_NONE
    // [DDR3][enter] <MIU1>
    // disable Bit[11] reg_csz_always_on
    RREG        w8, (MS_BUS_RIU_ADDR + (0x100606 << 1))
    bic         w8, w8, #0x0800
    REG_C2M     w8, (MS_BUS_RIU_ADDR + (0x100606 << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0027
    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0xFFFE
    
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0227
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0327
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0027
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0007
    
    DELAYUS     5
    
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0017
    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0xfffe
    WREG        (MS_BUS_RIU_ADDR + (0x100666 << 1)), 0xffff  //Bit[12]reg_cke_always_on
    WREG        (MS_BUS_RIU_ADDR + (0x100686 << 1)), 0xffff  //reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x1006A6 << 1)), 0xffff  //Bit[05]reg_auto_ref_off
    WREG        (MS_BUS_RIU_ADDR + (0x162206 << 1)), 0x7fff
    WREG        (MS_BUS_RIU_ADDR + (0x162226 << 1)), 0xffff
#endif /* CONFIG_MIU1_DRAM_NONE */
    
    ret

#//-------------------------------------------------------------------------------------------------
#// Reset_AVD_str
#// @param  None
#// @return None
#// @note  Reset_AVD_str
#//-------------------------------------------------------------------------------------------------
Reset_AVD_str:
    RREG        w8, (MS_BUS_RIU_ADDR + (0x103612 << 1))
    bic         w8, w8, #0x4000
    REG_C2M     w8, (MS_BUS_RIU_ADDR + (0x103612 << 1))

    RREG        w8, (MS_BUS_RIU_ADDR + (0x103612 << 1))
    orr         w8, w8, #0x4000
    REG_C2M     w8, (MS_BUS_RIU_ADDR + (0x103612 << 1))

    RREG        w8, (MS_BUS_RIU_ADDR + (0x103612 << 1))
    bic         w8, w8, #0x4000
    REG_C2M     w8, (MS_BUS_RIU_ADDR + (0x103612 << 1))

    ret

#//-------------------------------------------------------------------------------------------------
#// Bist for str
#// @param  None
#// @return None
#// @note  Reset_AVD_str
#//-------------------------------------------------------------------------------------------------
    .global     Miu1_BistTest_Str
Miu1_BistTest_Str:

    DPUTK_STR   MIU_MESSAGE_BIST1_Str

    ldr         x8, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         w7, =0x0000
    str         w7, [x8, #(0xe0 << 1)]
    ldr         w7, =0x8000
    str         w7, [x8, #(0xf0 << 1)]
    b           Miu_BistTest_Str

    .global     Miu0_BistTest_Str
Miu0_BistTest_Str:

    DPUTK_STR   MIU_MESSAGE_BIST0_Str

    ldr         x8, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         w7, =0x0000
    str         w7, [x8, #(0xe0 << 1)]    
    str         w7, [x8, #(0xf0 << 1)] 

    .global     Miu_BistTest_Str
Miu_BistTest_Str:
    ldr         x8, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         w7, =0x0000
    str         w7, [x8, #(0xe2 << 1)]    

    ldr         w9, =0xFFFF
    ldr         w7, =BIST_LEN
    and         w7, w7, w9
    str         w7, [x8, #(0xe4 << 1)]
    ldr         w7, =BIST_LEN
    lsr         w7, w7, #16
    and         w7, w7, w9
    str         w7, [x8, #(0xe6 << 1)]

    ldr         w7, =0x5aa5
    str         w7, [x8, #(0xe8 << 1)]

#ifdef CONFIG_MSTAR_SELF_STR_TEST_ENABLE
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0101
#endif

Miu_CheckBistLoop_Str:
    RREG        w8, (MS_BUS_RIU_ADDR + (0x1012e0 << 1))
    and         w7, w8, #0x8000
    cmp         w7, #0
    b.eq        Miu_CheckBistLoop_Str

    and         w7, w8, #0x6000
    cmp         w7, #0
    b.eq         Miu_Bist_OK_Str

Miu_Bist_Fail_Str:
    DPUTK_STR   MIU_MESSAGE_FAIL_Str

Miu_Bist_FailLoop_Str:
    b           Miu_Bist_FailLoop_Str

Miu_Bist_OK_Str:
    DPUTK_STR   MIU_MESSAGE_OK_Str
    
    ret
    
#//-------------------------------------------------------------------------------------------------
#// MIU_Set_Group_Priority
#// @param  None
#// @return None
#// @note   Set Group Priority
#//-------------------------------------------------------------------------------------------------
    .global     MIU_Set_Group_Priority_Str
MIU_Set_Group_Priority_Str:
#if !defined(CONFIG_MIU0_DRAM_NONE)
    #//set group priority in MIU_0
    ldr         x9, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         w7, [x9, #(0xfe << 1)]     //RREG        r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))
    bic         w7, w7, #0x0100
    str         w7, [x9, #(0xfe << 1)]     //REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))

    bic         w7, w7, #0x00FF
    ldr         w8, =(MIU0_GROUP_PRIORITY & 0xFF)
    orr         w7, w7, w8
    str         w7, [x9, #(0xfe << 1)]     //REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))

    orr         w7, w7, #0x0100            //set group fix priority
    str         w7, [x9, #(0xfe << 1)]     //REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))
    bic         w7, w7, #0x0100
    str         w7, [x9, #(0xfe << 1)]     //REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    #//set group priority in MIU_1
    ldr         x9, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
    ldr         w7, [x9, #(0xfe << 1)]     //RREG        r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))
    bic         w7, w7, #0x0100
    str         w7, [x9, #(0xfe << 1)]     //REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))

    bic         w7, w7, #0x00FF
    ldr         w8, =(MIU1_GROUP_PRIORITY & 0xFF)
    orr         w7, w7, w8
    str         w7, [x9, #(0xfe << 1)]     //REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))

    orr         w7, w7, #0x0100            //set group fix priority
    str         w7, [x9, #(0xfe << 1)]     //REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))
    bic         w7, w7, #0x0100
    str         w7, [x9, #(0xfe << 1)]     //REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012FE << 1))
#endif

    ret
