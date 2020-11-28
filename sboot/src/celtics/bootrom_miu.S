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

#ifndef _MIUSEL_CELTICS_2MIU_H_
#include "MIUSEL_CELTICS_2MIU.h"
#endif

#define MIU0_ENABLE_AUTO_PHASE              1

    .text

MIU_MESSAGE_BIST0:      .short   'B', 'I', 'S', 'T', '0', '-', 0x00
MIU_MESSAGE_BIST1:      .short   'B', 'I', 'S', 'T', '1', '-', 0x00
MIU_MESSAGE_BIST2:      .short   'B', 'I', 'S', 'T', '2', '-', 0x00
MIU_MESSAGE_AUTO_DQS0:  .short   'A', 'u', 't', 'o', 'D', 'Q', 'S', '0', '-', '[', 0x00
MIU_MESSAGE_AUTO_DQS1:  .short   'A', 'u', 't', 'o', 'D', 'Q', 'S', '1', '-', '[', 0x00
MIU_MESSAGE_AUTO_DQS2:  .short   'A', 'u', 't', 'o', 'D', 'Q', 'S', '2', '-', '[', 0x00
MIU_MESSAGE_DQS_1:      .short   ']', '-', '[', '0', 'x', 0x00
MIU_MESSAGE_OK:         .short   'O', 'K', '\n', '\r', 0x00
MIU_MESSAGE_FAIL:       .short   'F', 'A', 'I', 'L', '\n', '\r', 0x00

    .align      4
    .global     BootRom_InitMiu
BootRom_InitMiu:

#ifdef CONFIG_MSTAR_TITANIA_BD_FPGA
    mov         x29, x30

    WREG        (MS_BUS_RIU_ADDR + (0x002bc6 << 1)), 0x3c11
    WREG        (MS_BUS_RIU_ADDR + (0x002bca << 1)), 0x403c
    WREG        (MS_BUS_RIU_ADDR + (0x002bc4 << 1)), 0x0004

    WREG        (MS_BUS_RIU_ADDR + (0x101202 << 1)), 0x0854
    WREG        (MS_BUS_RIU_ADDR + (0x101204 << 1)), 0x01C5
    WREG        (MS_BUS_RIU_ADDR + (0x101206 << 1)), 0x0120
    WREG        (MS_BUS_RIU_ADDR + (0x101208 << 1)), 0x0833
    WREG        (MS_BUS_RIU_ADDR + (0x10120a << 1)), 0x0c33
    WREG        (MS_BUS_RIU_ADDR + (0x10120c << 1)), 0x7111
    WREG        (MS_BUS_RIU_ADDR + (0x10120e << 1)), 0x100e
    WREG        (MS_BUS_RIU_ADDR + (0x101210 << 1)), 0x0031

    WREG        (MS_BUS_RIU_ADDR + (0x10122a << 1)), 0x000f
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0C00  
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0C01
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0C00       

    WREG        (MS_BUS_RIU_ADDR + (0x100602 << 1)), 0x0854
    WREG        (MS_BUS_RIU_ADDR + (0x100604 << 1)), 0x01C5
    WREG        (MS_BUS_RIU_ADDR + (0x100606 << 1)), 0x0120
    WREG        (MS_BUS_RIU_ADDR + (0x100608 << 1)), 0x0833
    WREG        (MS_BUS_RIU_ADDR + (0x10060a << 1)), 0x0c33
    WREG        (MS_BUS_RIU_ADDR + (0x10060c << 1)), 0x7111
    WREG        (MS_BUS_RIU_ADDR + (0x10060e << 1)), 0x100e
    WREG        (MS_BUS_RIU_ADDR + (0x100610 << 1)), 0x0031

    WREG        (MS_BUS_RIU_ADDR + (0x10062a << 1)), 0x000f
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0C00  
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0C01
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0C00

    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0008
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000c
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000e
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x001f

    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0008
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x000c
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x000e
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x001f

    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0C08
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0C08

_CheckDramData:

    RREG        w0, (MS_BUS_RIU_ADDR + (0x101200 << 1))
    and         w0, w0, #0x8000
    cmp         w0, #0
    b.eq         _CheckDramData

    mov         x30, x29
#else

#if defined(CONFIG_BOOTING_FROM_EXT_SPI_WITH_CPU)
    #//Switch SRAM Access Right to ARM
    RREG        w0, (MS_BUS_RIU_ADDR + (0x11135E << 1))
    orr         w0, w0, #0x0008
    bic         w0, w0, #0x0010
    REG_C2M     w0, (MS_BUS_RIU_ADDR + (0x11135E << 1))

    #//Set stack pointer
    ldr         x0, =0x1fc02000
    mov         sp, x0
#endif

    subs        x0, sp, #16 
    mov         sp, x0 
    str         x30, [sp]

    ldr         x0, =MIU_PreInit
    bl          MDrv_WriteRegTbl32

#if !defined(CONFIG_MIU0_DRAM_NONE)
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

    #//Enable MIU0
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c01
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c00
    WREG        (MS_BUS_RIU_ADDR + (0x101202 << 1)), 0x03a3

    DELAYUS     200                                         //delay 200us

    ldr         x0, =MIU0_DDR_Init
    bl          MDrv_WriteRegTbl32
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)

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

    #//Enable MIU1
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0c01
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0c00
    WREG        (MS_BUS_RIU_ADDR + (0x100602 << 1)), 0x03a3

    DELAYUS     200                                         //delay 200us

    ldr         x0, =MIU1_DDR_Init
    bl          MDrv_WriteRegTbl32
#endif

    #//MIU0 ODT value setting
    RREG        w8, (MS_BUS_RIU_ADDR + (0x110d0e << 1))
    and         w8, w8, #0x1E
    mov         w8, w8, lsl #3

    RREG        w7, (MS_BUS_RIU_ADDR + (0x101228 << 1))
    bic         w7, w7, #0xF0

    orr         w7, w7, w8
    REG_C2M     w7, (MS_BUS_RIU_ADDR + (0x101228 << 1))

    RREG        w8, (MS_BUS_RIU_ADDR + (0x110d3c << 1))
    and         w8, w8, #0xFF

    RREG        w7, (MS_BUS_RIU_ADDR + (0x110d4e << 1))
    bic         w7, w7, #0xFF

    orr         w7, w7, w8
    REG_C2M     w7, (MS_BUS_RIU_ADDR + (0x110d4e << 1))
    
    #//MIU1 ODT value setting
    RREG        w8, (MS_BUS_RIU_ADDR + (0x16160e << 1))
    and         w8, w8, #0x1E
    mov         w8, w8, lsl #3

    RREG        w7, (MS_BUS_RIU_ADDR + (0x100628 << 1))
    bic         w7, w7, #0xF0

    orr         w7, w7, w8
    REG_C2M     w7, (MS_BUS_RIU_ADDR + (0x100628 << 1))

    RREG        w8, (MS_BUS_RIU_ADDR + (0x16163c << 1))
    and         w8, w8, #0xFF

    RREG        w7, (MS_BUS_RIU_ADDR + (0x16164e << 1))
    bic         w7, w7, #0xFF

    orr         w7, w7, w8
    REG_C2M     w7, (MS_BUS_RIU_ADDR + (0x16164e << 1))

    #//MIU2 ODT value setting
    RREG        w8, (MS_BUS_RIU_ADDR + (0x16210e << 1))
    and         w8, w8, #0x1E
    mov         w8, w8, lsl #3

    RREG        w7, (MS_BUS_RIU_ADDR + (0x162028 << 1))
    bic         w7, w7, #0xF0

    orr         w7, w7, w8
    REG_C2M     w7, (MS_BUS_RIU_ADDR + (0x162028 << 1))

    RREG        w8, (MS_BUS_RIU_ADDR + (0x16213c << 1))
    and         w8, w8, #0xFF

    RREG        w7, (MS_BUS_RIU_ADDR + (0x16214e << 1))
    bic         w7, w7, #0xFF

    orr         w7, w7, w8
    REG_C2M     w7, (MS_BUS_RIU_ADDR + (0x16214e << 1))

#if !defined(CONFIG_MIU0_DRAM_NONE)
    #//rx enable
    WREG        (MS_BUS_RIU_ADDR + (0x110d08 << 1)), 0x003f

    #//MIU0 INIT Cycle
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0000 //hold miu_0
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0008 //DRAM reset

    DELAYUS     500                                         //delay 500us

    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0004 //DRAM reset+CS
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0006 //DRAM reset+CS+CKE

    DELAYUS     500                                         //delay 500us

    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0017 //DRAM reset+CS+CKE+auto cycle+ODE

CheckMiu0Init:
    RREG        w7, (MS_BUS_RIU_ADDR + (0x101200 << 1))
    and         w7, w7, #0x8000
    cmp         w7, #0
    b.eq         CheckMiu0Init
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    #//rx enable
    WREG        (MS_BUS_RIU_ADDR + (0x161608 << 1)), 0x003f

    #//MIU1 INIT Cycle
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0000 //hold miu_0
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0008 //DRAM reset

    DELAYUS     500                                         //delay 500us

    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0004 //DRAM reset+CS
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0006 //DRAM reset+CS+CKE

    DELAYUS     500                                         //delay 500us

    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0017 //DRAM reset+CS+CKE+auto cycle+ODE

CheckMiu1Init:
    RREG        w7, (MS_BUS_RIU_ADDR + (0x100600 << 1))
    and         w7, w7, #0x8000
    cmp         w7, #0
    b.eq        CheckMiu1Init
#endif

    bl          MIU_Init_AnalogResetPatch

    bl          MIU_Set_Group_Priority

#if !defined(CONFIG_MIU0_DRAM_NONE)
    #//MIU0 BIST test
    WREG        (MS_BUS_RIU_ADDR + (0x161506 << 1)), 0x7FFF @//unmask MIU0_group_4 bit15
    bl          Miu0_BistTest
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    #//MIU1 BIST test
    WREG        (MS_BUS_RIU_ADDR + (0x162206 << 1)), 0x7FFF @//unmask MIU1_group_4 bit15
    bl          Miu1_BistTest
#endif

#if !defined(CONFIG_MIU2_DRAM_NONE)
    #//MIU2 BIST test
    WREG        (MS_BUS_RIU_ADDR + (0x162306 << 1)), 0x7FFF @//unmask MIU2_group_4 bit15
    bl          Miu2_BistTest
#endif

#ifdef MIU_ENABLE_AUTO_PHASE
#if !defined(CONFIG_MIU0_DRAM_NONE)
    #//Scan MIU0 DQS
    ldr         x0, =0             
    bl          BootRom_MiuDdr3Dqs
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    #//Scan MIU1 DQS
    ldr         x0, =1             
    bl          BootRom_MiuDdr3Dqs
#endif

#if !defined(CONFIG_MIU2_DRAM_NONE)
    #//Scan MIU2 DQS
    ldr         x0, =2          
    bl          BootRom_MiuDdr3Dqs
#endif
#endif

    ldr         x0, =MIU_PostInit
    bl          MDrv_WriteRegTbl32

    ldr         x30, [sp]
    add         x0, sp, #16 
    mov         sp, x0
#endif

    ret

#//-------------------------------------------------------------------------------------------------
#// MIU_Init_AnalogResetPatch
#// @param  None
#// @return None
#// @note   Patch for DDR Analog Reset Issue
#//-------------------------------------------------------------------------------------------------
    .global     MIU_Init_AnalogResetPatch
MIU_Init_AnalogResetPatch:
#if !defined(CONFIG_MIU0_DRAM_NONE)
    #//new sequence for MIU0 dqsm reset
    WREG        (MS_BUS_RIU_ADDR + (0x101218 << 1)), 0x0400  //reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0437  //Bit[05]reg_auto_ref_off, precharge all cmd
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0537  //Bit[05]reg_auto_ref_off, trig precharge all cmd enable
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0037  //single cmd off
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0237  //Bit[05]reg_auto_ref_off, refresh cmd
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0337  //Bit[05]reg_auto_ref_off, refresh cmd enable
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0017  //single cmd off , auto_ref_on
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    #//new sequence for MIU1 dqsm reset
    WREG        (MS_BUS_RIU_ADDR + (0x100618 << 1)), 0x0400  //reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0437  //Bit[05]reg_auto_ref_off, precharge all cmd
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0537  //Bit[05]reg_auto_ref_off, trig precharge all cmd enable
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0037  //single cmd off
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0237  //Bit[05]reg_auto_ref_off, refresh cmd
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0337  //Bit[05]reg_auto_ref_off, refresh cmd enable
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0017  //single cmd off , auto_ref_on
#endif

#if !defined(CONFIG_MIU2_DRAM_NONE)
    #//new sequence for MIU2 dqsm reset
    WREG        (MS_BUS_RIU_ADDR + (0x162018 << 1)), 0x0400  //reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x162000 << 1)), 0x0437  //Bit[05]reg_auto_ref_off, precharge all cmd
    WREG        (MS_BUS_RIU_ADDR + (0x162000 << 1)), 0x0537  //Bit[05]reg_auto_ref_off, trig precharge all cmd enable
    WREG        (MS_BUS_RIU_ADDR + (0x162000 << 1)), 0x0037  //single cmd off
    WREG        (MS_BUS_RIU_ADDR + (0x162000 << 1)), 0x0237  //Bit[05]reg_auto_ref_off, refresh cmd
    WREG        (MS_BUS_RIU_ADDR + (0x162000 << 1)), 0x0337  //Bit[05]reg_auto_ref_off, refresh cmd enable
    WREG        (MS_BUS_RIU_ADDR + (0x162000 << 1)), 0x0017  //single cmd off , auto_ref_on
#endif

    DELAYUS     800   //Delay 800us

    ret
    .ltorg

#//-------------------------------------------------------------------------------------------------
#// MIU_Set_Group_Priority
#// @param  None
#// @return None
#// @note   Set Group Priority
#//-------------------------------------------------------------------------------------------------
    .global     MIU_Set_Group_Priority
MIU_Set_Group_Priority:
#if !defined(CONFIG_MIU0_DRAM_NONE)
    #//set group priority in MIU_0
    ldr         x7, =(MS_BUS_RIU_ADDR + (0x1012fe << 1))
    ldr         x8, [x7] 
    bic         x8, x8, #0x0100
    str         x8, [x7]      

    bic         x8, x8, #0x00FF
    ldr         x9, =(MIU0_GROUP_PRIORITY & 0xFF)
    orr         x8, x8, x9
    str         x8, [x7]

    orr         x8, x8, #0x0100             //set group fix priority
    str         x8, [x7]
    bic         x8, x8, #0x0100
    str         x8, [x7]
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    #//set group priority in MIU_1
    ldr         x7, =(MS_BUS_RIU_ADDR + (0x1006fe << 1))
    ldr         x8, [x7]
    bic         x8, x8, #0x0100
    str         x8, [x7]

    bic         x8, x8, #0x00FF
    ldr         x9, =(MIU1_GROUP_PRIORITY & 0xFF)
    orr         x8, x8, x9
    str         x8, [x7]

    orr         x8, x8, #0x0100             //set group fix priority
    str         x8, [x7] 
    bic         x8, x8, #0x0100
    str         x8, [x7]
#endif

    ret

#//-------------------------------------------------------------------------------------------------
#// MiuBistTest
#// @param
#// @return None
#// @note
#//-------------------------------------------------------------------------------------------------
    .global     Miu2_BistTest
Miu2_BistTest:

    DPUTK_STR   MIU_MESSAGE_BIST2

    ldr         x8, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         w7, =0x0000
    strh        w7, [x8, #(0xe0 << 1)]       
    ldr         w7, =0x0000
    strh        w7, [x8, #(0xf8 << 1)]      
    WREG        (MS_BUS_RIU_ADDR + (0x1620f8 << 1)), 0x8000  
    b           Miu_BistTest

    .global     Miu1_BistTest
Miu1_BistTest:

    DPUTK_STR   MIU_MESSAGE_BIST1

    ldr         x8, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         w7, =0x0000
    strh        w7, [x8, #(0xe0 << 1)] 
    ldr         w7, =0x8000
    strh        w7, [x8, #(0xf8 << 1)] 
    WREG        (MS_BUS_RIU_ADDR + (0x1620f8 << 1)), 0x0000 
    b           Miu_BistTest

    .global     Miu0_BistTest
Miu0_BistTest:

    DPUTK_STR   MIU_MESSAGE_BIST0

    ldr         x8, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         w7, =0x0000
    strh        w7, [x8, #(0xe0 << 1)]    
    strh        w7, [x8, #(0xf8 << 1)]    
    WREG        (MS_BUS_RIU_ADDR + (0x1620f8 << 1)), 0x0000 

    .global     Miu_BistTest
Miu_BistTest:
    ldr         x8, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         w7, =0x0000
    strh        w7, [x8, #(0xe2 << 1)]

    ldr         w9, =0xFFFF
    ldr         w7, =BIST_LEN
    and         w7, w7, w9
    strh        w7, [x8, #(0xe4 << 1)]
    ldr         w7, =BIST_LEN
    lsr         w7, w7, #16
    and         w7, w7, w9
    strh        w7, [x8, #(0xe6 << 1)]    

    ldr         w7, =0x5aa5
    strh        w7, [x8, #(0xe8 << 1)]    

    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0002   
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0003   //bist test mode:3

Miu_CheckBistLoop:
    RREG        w8, (MS_BUS_RIU_ADDR + (0x1012e0 << 1))
    and         w7, w8, #0x8000
    cmp         w7, #0
    b.eq        Miu_CheckBistLoop

    and         w7, w8, #0x6000
    cmp         w7, #0
    b.eq        Miu_Bist_OK

Miu_Bist_Fail:
    DPUTK_STR   MIU_MESSAGE_FAIL
    
Miu_Bist_FailLoop:
    b           Miu_Bist_FailLoop

Miu_Bist_OK:
    DPUTK_STR   MIU_MESSAGE_OK

Miu_Bist_Exit:

    ret

#//================================================================================================
    .size       BootRom_InitMiu,.-BootRom_InitMiu
