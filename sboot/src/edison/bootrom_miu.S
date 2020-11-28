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

#ifndef _DRV_UART_INC_
#include "drv_uart.inc"
#endif

#ifndef _MACRO_INC_
#include "macro.inc"
#endif

#ifndef _MIUSEL_EDISON_2MIU_H_
#include "MIUSEL_EDISON_2MIU.h"
#endif

	.text

MIU_MESSAGE_BIST0:      .short   'B', 'I', 'S', 'T', '0', '-', 0x00
MIU_MESSAGE_BIST1:      .short   'B', 'I', 'S', 'T', '1', '-', 0x00
MIU_MESSAGE_AUTO_DQS0:  .short   'A', 'u', 't', 'o', 'D', 'Q', 'S', '0', '-', '[', 0x00
MIU_MESSAGE_AUTO_DQS1:  .short   'A', 'u', 't', 'o', 'D', 'Q', 'S', '1', '-', '[', 0x00
MIU_MESSAGE_DQS_1:      .short   ']', '-', '[', '0', 'x', 0x00
MIU_MESSAGE_OK:         .short   'O', 'K', '\n', '\r', 0x00
MIU_MESSAGE_FAIL:       .short   'F', 'A', 'I', 'L', '\n', '\r', 0x00
 
    .global     BootRom_InitMiu
BootRom_InitMiu:

    mov         r13, lr

	ldr         r0, =MIU0_PreInit
    bl          MDrv_WriteRegTbl32

.if ( ENABLE_MIU1 == 1 )
    ldr         r0, =MIU1_PreInit
    bl          MDrv_WriteRegTbl32
.endif

    DELAYUS 5000    @ delay 5ms

    WREG    (MS_BUS_RIU_ADDR + (0x110d24 <<1 )) , 0x0000
.if ( ENABLE_MIU1 == 1 )
    WREG    (MS_BUS_RIU_ADDR + (0x110da4 <<1 )) , 0x0000
.endif

    ldr r0, =MIU0_DDR_Init
    bl MDrv_WriteRegTbl32

    WREG    (MS_BUS_RIU_ADDR + (0x1012fc <<1 )), 0x8400

    DELAYUS 1000    @ delay 1ms

    WREG    (MS_BUS_RIU_ADDR + (0x10121e <<1 )) , 0x0c01   @miu_sw_rst

    DELAYUS 1      @ delay 1us

    WREG    (MS_BUS_RIU_ADDR + (0x10121e <<1 )) , 0x0c08

    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
    WREG    (MS_BUS_RIU_ADDR + (0x110d00 <<1 )) , 0x1e01   @reg_pkg_sel      1   : [0]
    #endif
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
    WREG    (MS_BUS_RIU_ADDR + (0x110d00 <<1 )) , 0x1e02   @reg_pkg_sel      1   : [0]
    #endif

    WREG    (MS_BUS_RIU_ADDR + (0x110d02 <<1 )) , 0xaaaa   @reg_cko_state        cc  : [7:0]
    WREG    (MS_BUS_RIU_ADDR + (0x110d18 <<1 )) , 0x0000
    WREG    (MS_BUS_RIU_ADDR + (0x101202 <<1 )) , 0x03a7
    WREG    (MS_BUS_RIU_ADDR + (0x110d54 <<1 )) , 0x0000

.if ( ENABLE_MIU1 == 1 )
    ldr r0, =MIU1_DDR_Init
    bl MDrv_WriteRegTbl32

    WREG    (MS_BUS_RIU_ADDR + (0x1006fc <<1 )), 0x8400

    DELAYUS 1000    @ delay 1ms

    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )) , 0x0c01   @miu_sw_rst

    DELAYUS 1      @ delay 1us

    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )) , 0x0c08

    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
    WREG    (MS_BUS_RIU_ADDR + (0x110d80 <<1 )) , 0x1e01   @reg_pkg_sel      1   : [0]
    #endif
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
    WREG    (MS_BUS_RIU_ADDR + (0x110d80 <<1 )) , 0x1e02   @reg_pkg_sel      1   : [0]
    #endif

    WREG    (MS_BUS_RIU_ADDR + (0x110d82 <<1 )) , 0xaaaa   @reg_cko_state        cc  : [7:0]
    WREG    (MS_BUS_RIU_ADDR + (0x110d98 <<1 )) , 0x0000
    WREG    (MS_BUS_RIU_ADDR + (0x100602 <<1 )) , 0x03a3
    WREG    (MS_BUS_RIU_ADDR + (0x110dd4 <<1 )) , 0x0000
.endif

    DELAYUS  100  @ delay 100us

    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
    WREG    (MS_BUS_RIU_ADDR + (0x110d08 <<1 )) , 0x703f   @reg_rx_en
    #endif
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
    WREG    (MS_BUS_RIU_ADDR + (0x110d08 <<1 )) , 0x003f   @reg_rx_en
    #endif

.if ( ENABLE_MIU1 == 1 )
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
    WREG    (MS_BUS_RIU_ADDR + (0x110d88 <<1 )) , 0x703f   @reg_rx_en
    #endif
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
    WREG    (MS_BUS_RIU_ADDR + (0x110d88 <<1 )) , 0x003f   @reg_rx_en
    #endif
.endif

    @ MIU0 INIT Cycle
    WREG    (MS_BUS_RIU_ADDR + (0x101200 <<1 )), 0x0000 @ hold miu_0
    WREG    (MS_BUS_RIU_ADDR + (0x101200 <<1 )), 0x0008 @ DRAM reset
    WREG    (MS_BUS_RIU_ADDR + (0x101200 <<1 )), 0x000c @ DRAM reset+CS
    DELAYUS 300                                         @ delay 300us
    WREG    (MS_BUS_RIU_ADDR + (0x101200 <<1 )), 0x000e @ DRAM reset+CS+CKE
    DELAYUS 500                                         @ delay 500us
    WREG    (MS_BUS_RIU_ADDR + (0x101200 <<1 )), 0x001f @ DRAM reset+CS+CKE+auto cycle+ODE
    DBGREG  0x0025

CheckMiu0Init:
    RREG    r0,(MS_BUS_RIU_ADDR + (0x101200 <<1 ))
    lsr     r0, r0, #15
    cmp     r0, #1
    bne     CheckMiu0Init

.if ( ENABLE_MIU1 == 1 )
    @ MIU1 INIT Cycle
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x0000 @ hold miu_0
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x0008 @ DRAM reset
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x000c @ DRAM reset+CS
    DELAYUS 300                                         @ delay 300us
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x000e @ DRAM reset+CS+CKE
    DELAYUS 500                                         @ delay 500us
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x001f @ DRAM reset+CS+CKE+auto cycle+ODE
CheckMiu1Init:
    RREG    r0,(MS_BUS_RIU_ADDR + (0x100600 <<1 ))
    lsr     r0, r0, #15
    cmp     r0, #1
    bne     CheckMiu1Init
.endif

    DELAYUS 200   @ delay 200us

    @ U04 last down Z switch
    RREG    r0, (MS_BUS_RIU_ADDR + (0x001e02 <<1 ))
    bic     r0, r0, #0x00FF
    lsr     r0, r0, #8
    cmp     r0, #3
    blt     U03_chip_bypass
    nop
    RREG    r0, (MS_BUS_RIU_ADDR + (0x10125E <<1 ))
    orr     r0, r0, #0x0100
    ldr     r1, =(MS_BUS_RIU_ADDR + (0x10125E <<1 ))
    str     r0, [r1]
    .if ( ENABLE_MIU1 == 1 )
    RREG    r0, (MS_BUS_RIU_ADDR + (0x10065E <<1 ))
    orr     r0, r0, #0x0100
    ldr     r1, =(MS_BUS_RIU_ADDR + (0x10065E <<1 ))
    str     r0, [r1]
    .endif

    WREG    (MS_BUS_RIU_ADDR + (0x101292 <<1 )) , 0xFFFF
.if ( ENABLE_MIU1 == 1 )
	WREG    (MS_BUS_RIU_ADDR + (0x100692 <<1 )) , 0xFFFF
.endif
    b       Next_Step
    nop

U03_chip_bypass:
    WREG    (MS_BUS_RIU_ADDR + (0x101292 <<1 )) , 0xFFFE   @GE MIU0 and MIU1 last done Z select to 128 arbit
.if ( ENABLE_MIU1 == 1 )
	WREG    (MS_BUS_RIU_ADDR + (0x100692 <<1 )) , 0xFFFE
.endif

Next_Step:
    @ last_done_z select to last stage
    WREG    (MS_BUS_RIU_ADDR + (0x101252 <<1 )) , 0xFFFF
    WREG    (MS_BUS_RIU_ADDR + (0x101272 <<1 )) , 0xFFFF
    WREG    (MS_BUS_RIU_ADDR + (0x1012B2 <<1 )) , 0xFFFF
.if ( ENABLE_MIU1 == 1 )
    WREG    (MS_BUS_RIU_ADDR + (0x100652 <<1 )) , 0xFFFF
    WREG    (MS_BUS_RIU_ADDR + (0x100672 <<1 )) , 0xFFFF
    WREG    (MS_BUS_RIU_ADDR + (0x1006B2 <<1 )) , 0xFFFF
.endif

@ 4Gb DDR3 cell run in 1866MHz only
#if 0
	#if(ENABLE_MEM1866MHz)
		RREG    r0, (MS_BUS_RIU_ADDR + (0x10125E <<1 ))
		orr     r0, r0, #0x8000
		ldr     r1, =(MS_BUS_RIU_ADDR + (0x10125E <<1 ))
		str     r0, [r1]
		.if ( ENABLE_MIU1 == 1 )
		RREG    r0, (MS_BUS_RIU_ADDR + (0x10065E <<1 ))
		orr     r0, r0, #0x8000
		ldr     r1, =(MS_BUS_RIU_ADDR + (0x10065E <<1 ))
		str     r0, [r1]
		.endif
	#endif
#endif

	bl       MIU_Init_AnalogResetPatch

    @//bl      MIU_Init_Priority

@ disable auto phase for chip bring up
NONTEST_SELF_REFRESH_3:
@@.if(CONFIG_MSTAR_STR_ENABLE == 1)
@@    is_slept
@@    beq END_OF_BIST
@@.endif

	@ Auto DQS phase
    WREG    (MS_BUS_RIU_ADDR + (0x101246 <<1 )) , 0x7FFE   @Mask MIU0_group_0
    bl      Miu0_AutoPhase 
    
.if ( ENABLE_MIU1 == 1 )
    WREG    (MS_BUS_RIU_ADDR + (0x100646 <<1 )) , 0x7FFE   @Mask MIU0_group_0
    bl      Miu1_AutoPhase
.endif

    @ BIST test
    WREG    (MS_BUS_RIU_ADDR + (0x101246 <<1 )) , 0x7FFE   @Mask MIU0_group_0
    bl      Miu0_BistTest

.if ( ENABLE_MIU1 == 1 )
    WREG    (MS_BUS_RIU_ADDR + (0x100646 <<1 )) , 0x7FFE   @Mask MIU0_group_0
    bl      Miu1_BistTest
.endif

	ldr         r0, =MIU_PostInit
    bl          MDrv_WriteRegTbl32

    RREG     r0, 0x1F202454    @Switch MIU0 client 0x0F from BIST to SC
    orr      r0, r0, #0x4000
    REG_C2M  r0, 0x1F202454

    RREG     r0, 0x1F200C54    @Switch MIU1 client 0x0F from BIST to SC
    orr      r0, r0, #0x4000
    REG_C2M  r0, 0x1F200C54

#if defined(CONFIG_MSTAR_TITANIA_MMAP_32MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x5000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_64MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x6000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_128MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x7000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_32MB_32MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x5000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_64MB_32MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x6000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_64MB_64MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x6000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_128MB_64MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x7000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_128MB_128MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x7000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_128MB_128MB_DEFAULT)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x7000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_256MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x8000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_256MB_256MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x8000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_512MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x9000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_512MB_512MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x9000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_512MB_256MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x9000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_1024MB_512MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0xa000
#elif defined(CONFIG_MSTAR_EDISON_MMAP_512MB_256MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x9000
#elif defined(CONFIG_MSTAR_EDISON_MMAP_512MB_512MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x9000
#else
    #error "Incorrect MMAP setting!!"
#endif

.if ( ENABLE_MIU1 == 1 )
#if defined(CONFIG_MSTAR_TITANIA_MMAP_32MB_32MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x5000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_64MB_32MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x5000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_64MB_64MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x6000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_128MB_64MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x6000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_128MB_128MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x7000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_128MB_128MB_DEFAULT)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x7000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_256MB_256MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x8000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_512MB_512MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x9000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_512MB_256MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x8000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_1024MB_512MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x9000
#elif defined(CONFIG_MSTAR_EDISON_MMAP_512MB_256MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x8000
#elif defined(CONFIG_MSTAR_EDISON_MMAP_512MB_512MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x9000
#else
    #error "Incorrect MMAP setting!!"
#endif
.endif

    @ MFE set to 128bit MIU bus
    RREG    r0, (MS_BUS_RIU_ADDR + (0x101e44 <<1 ))
    bic     r0, r0, #0x0180
    bic     r0, r0, #0x8000
    ldr     r1, =(MS_BUS_RIU_ADDR + (0x101e44 <<1 ))
    str     r0, [r1]

	@fix the MIU meta issue
    RREG    r0, (MS_BUS_RIU_ADDR + (0x1012b8 <<1 ))
    orr     r0, r0, #0x0001
    ldr     r1, =(MS_BUS_RIU_ADDR + (0x1012b8 <<1 ))
    str     r0, [r1]

	mov         lr, r13
    bx          lr
@//-------------------------------------------------------------------------------------------------
@// BootRom_InitMiu_fpga 
@// @param  None
@// @return None
@// @note   None
@//-------------------------------------------------------------------------------------------------
.if(IS_FPGA == 1)
    .global     BootRom_InitMiu_fpga
BootRom_InitMiu_fpga:

    @ XD2MIU init setting
    WREG    0x1F005788, 0x0004

    WREG    0x1F00578C, 0x3c11
    WREG    0x1F005790, 0x0010
    WREG    0x1F005794, 0x403c
    WREG    0x1F005798, 0x0101

    @ disable MIU random model
    WREG    0x1F202454, 0xC000
    WREG    0x1F2025FC, 0xFF00

    @T4 trigger MIU init
    WREG    0x1F202404, 0x0000
    WREG    0x1F202404, 0x0858
    WREG    0x1F202408, 0x0185
    WREG    0x1F20240C, 0x0120
    WREG    0x1F202410, 0x0833
    WREG    0x1F202414, 0x0c33
    WREG    0x1F202418, 0x7111
    WREG    0x1F20241C, 0x100e
    WREG    0x1F202420, 0x0031

    WREG    0x1F20243C, 0x0C01
    WREG    0x1F20243C, 0x0C00
    WREG    0x1F202400, 0x0008
    WREG    0x1F202400, 0x000c

    DELAYUS 100

    WREG    0x1F202400, 0x000e
    DELAYUS 0x100

    WREG    0x1F202400, 0x001f
    DELAYUS 100

    WREG    0x1F20243C, 0x0C08

    bx      lr
 .endif
@//-------------------------------------------------------------------------------------------------
@// MIU_Init_AnalogResetPatch
@// @param  None
@// @return None
@// @note   Patch for DDR Analog Reset Issue
@//-------------------------------------------------------------------------------------------------
    .global     MIU_Init_AnalogResetPatch
MIU_Init_AnalogResetPatch:

@// WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x7ffe

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0c08
    str         r11, [r12, #(0x1e << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c08
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe2 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e2 << 1)), 0x0000
    ldr         r11, =0x0011
    str         r11, [r12, #(0xe4 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e4 << 1)), 0x0011
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe6 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e6 << 1)), 0x0000
    ldr         r11, =0x5aa5
    str         r11, [r12, #(0xe8 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e8 << 1)), 0x5aa5
    ldr         r11, =0x0000
    str         r11, [r12, #(0xf0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x0000

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x110d00 << 1))
    ldr         r3, [r12, #(0x0e << 1)]     @//RREG        r3, (MS_BUS_RIU_ADDR + (0x110d0e << 1))
    orr         r3, r3, #(0x01 << 6)
    str         r3, [r12, #(0x0e << 1)]     @//REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x110d0e << 1))

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0200
    str         r11, [r12, #(0xe0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0200
    ldr         r11, =0x0201
    str         r11, [r12, #(0xe0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0201

    DELAYUS     1

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x110d00 << 1))
    ldr         r3, [r12, #(0x0e << 1)]     @//RREG        r3, (MS_BUS_RIU_ADDR + (0x110d0e << 1))
    bic         r3, r3, #(0x01 << 6)
    str         r3, [r12, #(0x0e << 1)]     @//REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x110d0e << 1))

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000

.if ( ENABLE_MIU1 == 1 )

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x8000
    str         r11, [r12, #(0xf0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x8000

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x100600 << 1))
    ldr         r11, =0x7ffe
    str         r11, [r12, #(0x46 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x7ffe

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x110d00 << 1))
    ldr         r3, [r12, #(0x8e << 1)]     @//RREG        r3, (MS_BUS_RIU_ADDR + (0x110d8e << 1))
    orr         r3, r3, #(0x01 << 6)
    str         r3, [r12, #(0x8e << 1)]     @//REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x110d8e << 1))

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0200
    str         r11, [r12, #(0xe0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0200
    ldr         r11, =0x0201
    str         r11, [r12, #(0xe0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0201

    DELAYUS     1

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x110d00 << 1))
    ldr         r3, [r12, #(0x8e << 1)]     @//RREG        r3, (MS_BUS_RIU_ADDR + (0x110d8e << 1))
    bic         r3, r3, #(0x01 << 6)
    str         r3, [r12, #(0x8e << 1)]     @//REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x110d8e << 1))

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000
    ldr         r11, =0x0000
    str         r11, [r12, #(0xf0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x0000

.endif

    DELAYUS     10   @//Delay 10us

    bx          lr
    .ltorg
 
@//-------------------------------------------------------------------------------------------------
@// MIU_Init_Priority
@// @param  None
@// @return None
@// @note   Init MIU Priority
@//-------------------------------------------------------------------------------------------------
#if 0
MIU_Init_Priority:

    @ MIU0: generate set priority pulse for "fix priority"

    RREG    r0, 0x1F202480
    and     r0, r0, #1
    cmp     r0, #1
    beq     miu0_rq0_skip

    RREG    r0, 0x1F202480
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F202480
    str     r0, [r1]

    RREG    r0, 0x1F202480
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F202480
    str     r0, [r1]

miu0_rq0_skip:

    RREG    r0, 0x1F2024C0
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu0_rq1_skip

    RREG    r0, 0x1F2024C0
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F2024C0
    str     r0, [r1]

    RREG    r0, 0x1F2024C0
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F2024C0
    str     r0, [r1]

miu0_rq1_skip:

    RREG    r0, 0x1F202500
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu0_rq2_skip

    RREG    r0, 0x1F202500
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F202500
    str     r0, [r1]

    RREG    r0, 0x1F202500
    bic     r0, r0, #0002
    ldr     r1, =0x1F202500
    str     r0, [r1]

miu0_rq2_skip:

    RREG    r0, 0x1F202540
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu0_rq3_skip

    RREG    r0, 0x1F202540
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F202540
    str     r0, [r1]

    RREG    r0, 0x1F202540
    bic     r0, r0, #0002
    ldr     r1, =0x1F202540
    str     r0, [r1]

miu0_rq3_skip:

    @ MIU1: generate set priority pulse for "fix priority"

    RREG    r0, 0x1F200C80
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu1_rq0_skip

    RREG    r0, 0x1F200C80
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F200C80
    str     r0, [r1]

    RREG    r0, 0x1F200C80
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F200C80
    str     r0, [r1]

miu1_rq0_skip:

    RREG    r0, 0x1F200CC0
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu1_rq1_skip

    RREG    r0, 0x1F200CC0
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F200CC0
    str     r0, [r1]

    RREG    r0, 0x1F200CC0
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F200CC0
    str     r0, [r1]

miu1_rq1_skip:

    RREG    r0, 0x1F200D00
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu1_rq2_skip

    RREG    r0, 0x1F200D00
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F200D00
    str     r0, [r1]

    RREG    r0, 0x1F200D00
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F200D00
    str     r0, [r1]

miu1_rq2_skip:

    RREG    r0, 0x1F200D40
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu1_rq3_skip

    RREG    r0, 0x1F200D40
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F200D40
    str     r0, [r1]

    RREG    r0, 0x1F200D40
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F200D40
    str     r0, [r1]

miu1_rq3_skip:
    bx          lr

@//-------------------------------------------------------------------------------------------------
@// MIU_Set_Group_Priority
@// @param  None
@// @return None
@// @note   Set Group Priority
@//-------------------------------------------------------------------------------------------------
MIU_Set_Group_Priority:

    @set group priority in MIU_0
    RREG    r0, 0x1F2025FC
    bic     r0, r0, #(1<<8)
    ldr     r1, =0x1F2025FC
    str     r0, [r1]

    RREG    r0, 0x1F2025FC
    and     r0, r0, #0xFF00
    orr     r0, r0, #(MIU0_GROUP_PRIORITY & 0xFF)
    ldr     r1, =0x1F2025FC
    str     r0, [r1]

    RREG    r0, 0x1F2025FC
    orr     r0, r0, #0x0100           @ set group fix priority
    ldr     r1, =0x1F2025FC
    str     r0, [r1]

    @set group priority in MIU_1
    RREG    r0, 0x1F200DFC
    bic     r0, r0, #(1<<8)
    ldr     r1, =0x1F200DFC
    str     r0, [r1]

    RREG    r0, 0x1F200DFC
    and     r0, r0, #0xFF00
    orr     r0, r0, #(MIU1_GROUP_PRIORITY & 0xFF)
    ldr     r1, =0x1F200DFC
    str     r0, [r1]

    RREG    r0, 0x1F200DFC
    orr     r0, r0, #0x0100
    ldr     r1, =0x1F200DFC
    str     r0, [r1]
    
    bx          lr
#endif
@//-------------------------------------------------------------------------------------------------
@// Miu1_BistTest
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
.if ( ENABLE_MIU1 == 1 )
	.global     Miu1_BistTest
Miu1_BistTest:

    DPUTK_STR   MIU_MESSAGE_BIST1

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000   @//1012e0 //reset bist test
    ldr         r11, =0x8000
    str         r11, [r12, #(0xf0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x8000   @//1012f0 bit_15=1 choice to MIU_1
    b           Miu_BistTest
.endif
@//-------------------------------------------------------------------------------------------------
@// Miu0_BistTest
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     Miu0_BistTest
Miu0_BistTest:

    DPUTK_STR   MIU_MESSAGE_BIST0

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000   @//1012e0 //reset bist test
    str         r11, [r12, #(0xf0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x0000   @//1012f0 bit_15=0 choice to MIU_0

@//-------------------------------------------------------------------------------------------------
@// Miu_BistTest
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     Miu_BistTest
Miu_BistTest:
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

    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0003   @//bist test mode:3

Miu_CheckBistLoop:
    RREG        r1, (MS_BUS_RIU_ADDR + (0x1012e0 << 1))
    and         r0, r1, #0x8000
    cmp         r0, #0
    beq         Miu_CheckBistLoop

    and         r0, r1, #0x6000
    cmp         r0, #0
    beq         Miu_Bist_OK

Miu_Bist_Fail:
    DPUTK_STR   MIU_MESSAGE_FAIL
    
Miu_Bist_FailLoop:
    b           Miu_Bist_FailLoop

Miu_Bist_OK:
    DPUTK_STR   MIU_MESSAGE_OK

Miu_Bist_Exit:

    bx          lr

#if 0
@//-------------------------------------------------------------------------------------------------
@// Miu0_AutoPhase
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
	.global     Miu0_AutoPhase
Miu0_AutoPhase:

#define DQS_VAL1        r10
#define DQS_VAL1_BK     r9
#define DQS_VAL0        r0
#define DQS_VAL0_BK     r8
#define miu_phase_reg0  r7
#define miu_phase_reg1  r6
#define REG_ADDR_BASE   0x1f000000

    @PUTK   '\n'
    @PUTK   '\r'
	DPUTK_STR   MIU_MESSAGE_AUTO_DQS0

    WREG    0x1F2025E0 , 0x0000    @ 1012f0 bit_15=0 choice to MIU_0

    RREG    DQS_VAL0, (REG_ADDR_BASE+(0x110D6E<<1))  @store the default phase setting to r0
    RREG    DQS_VAL1, (REG_ADDR_BASE+(0x110D6C<<1))  @store the default phase setting to r10

    mov     DQS_VAL0_BK, DQS_VAL0
    mov     DQS_VAL1_BK, DQS_VAL1

    ldr     miu_phase_reg0, =(REG_ADDR_BASE+(0x110D6E<<1))  @ reg_0x110D6E  //miu_phase_reg
    ldr     miu_phase_reg1, =(REG_ADDR_BASE+(0x110D6C<<1))  @ reg_0x110D6C  //miu_phase_reg

    bl      AutoPhaseLoop

    bx      lr

@//-------------------------------------------------------------------------------------------------
@// Miu1_AutoPhase
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
	.global     Miu1_AutoPhase
Miu1_AutoPhase:
#define DQS_VAL1        r10
#define DQS_VAL1_BK     r9
#define DQS_VAL0        r0          // $9
#define DQS_VAL0_BK     r8          // $29
#define miu_phase_reg0  r7
#define miu_phase_reg1  r6
#define REG_ADDR_BASE   0x1f000000

	DPUTK_STR   MIU_MESSAGE_AUTO_DQS1

    WREG    0x1F2025E0 , 0x8000    @ 1012f0 bit_15=1 choice to MIU_1

    RREG    DQS_VAL0, (REG_ADDR_BASE+(0x110DEE<<1))  @store the default phase setting to r0
    RREG    DQS_VAL1, (REG_ADDR_BASE+(0x110DEC<<1))  @store the default phase setting to r10

    mov     DQS_VAL0_BK, DQS_VAL0
    mov     DQS_VAL1_BK, DQS_VAL1

    ldr     miu_phase_reg0, =(REG_ADDR_BASE+(0x110DEE<<1))  @ 0x110DEE  //miu_phase_reg
    ldr     miu_phase_reg1, =(REG_ADDR_BASE+(0x110DEC<<1))  @ 0x110DEE  //miu_phase_reg

    bl      AutoPhaseLoop

    bx      lr

@//-------------------------------------------------------------------------------------------------
@// AutoPhaseLoop
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
	.global     AutoPhaseLoop
AutoPhaseLoop:
#define tmp_var0          r1          // $13
#define good_phase_cnt    r2       // $21
#define good_phase_sum    r3       // $20
#define good_phase_bit    r4       // $25
#define temp_val          r5       // $8


    @PUTK    '['
    WREG    (REG_ADDR_BASE+(0x1012e4<<1)), 0x0401   @ 1012e4~1012e7 bist test size,   (16 byte/unit)
    WREG    (REG_ADDR_BASE+(0x1012e6<<1)), 0x0000   @ 1012e4~1012e7 bist test size,   (16 byte/unit)
    WREG    (REG_ADDR_BASE+(0x1012e8<<1)), 0x00FF   @ 1012e4~1012e7 bist test pattern

    ldr     tmp_var0, =0
    ldr     good_phase_cnt, =0
    ldr     good_phase_sum, =0
    ldr     good_phase_bit, =1

StartChk_x3:

BistPatternfill:                      @write data into each region respect to bist mode 0x183,0x185,0x187

.if ( ENABLE_MIU1 == 1 )
    WREG        0x1f200DC0, 0x0000
.endif
    WREG    (REG_ADDR_BASE+(0x1012e2<<1)), 0x1000   @ 1012e2 bist test start address, (4K byte/unit)
    WREG    0x1f2025C0,0x0000
    ldr     DQS_VAL0,=0x0083             @bist mode 0x83
    b       BistRWModeTest

Check_bist85:
.if ( ENABLE_MIU1 == 1 )
    WREG    0x1f200DC0, 0x0000
.endif
    WREG    (REG_ADDR_BASE+(0x1012e2<<1)), 0x1100   @ 1012e2 bist test start address, (4K byte/unit)
    WREG    0x1f2025C0,0x0000
    ldr     DQS_VAL0,=0x0085             @bist mode 0x85
    b       BistRWModeTest

Check_bist87:
.if ( ENABLE_MIU1 == 1 )
    WREG    0x1f200DC0, 0x0000
.endif
    WREG    (REG_ADDR_BASE+(0x1012e2<<1)), 0x1200   @ 1012e2 bist test start address, (4K byte/unit)
    WREG    0x1f2025C0,0x0000
    ldr     DQS_VAL0,=0x0087             @bist mode 0x87
    b       BistRWModeTest

BistRWModeTest:
    bl      ModeChangeDelay

    ldr     temp_val,=0x1f2025c0
    str     DQS_VAL0,[temp_val]           @bist test start

CheckRWBistDone:
    RREG    DQS_VAL0, 0x1F2025C0
    and     temp_val, DQS_VAL0, #0x8000
    cmp     temp_val, #0
    beq     CheckRWBistDone           @ check done

RWBistCheckPhaseOK:
    and     temp_val, DQS_VAL0, #0x00FF
    cmp     temp_val, #0x83
    beq     Check_bist85       @x83->0x85->0x87
    cmp     temp_val, #0x85
    beq     Check_bist87

check_x3:
    bl      ClockReset
    and     DQS_VAL0, tmp_var0, #0x000F
    lsl     DQS_VAL0, DQS_VAL0, #12
    ldr     temp_val, =0x0FFF
    and     temp_val, DQS_VAL0_BK, temp_val
    orr     DQS_VAL0, DQS_VAL0, temp_val
    str     DQS_VAL0,[miu_phase_reg0]

    bl      ClockUnReset
    b       StartCheck

StartChk_x2:
    ldr     good_phase_bit, =1
    b       check_x2

check_x2:
    bl      ClockReset
    and     DQS_VAL0, tmp_var0, #0x000F
    lsl     DQS_VAL0, DQS_VAL0, #8
    ldr     temp_val, =0xF0FF
    and     temp_val, DQS_VAL0_BK, temp_val
    orr     DQS_VAL0, DQS_VAL0, temp_val
    str     DQS_VAL0,[miu_phase_reg0]

    bl      ClockUnReset
    b       StartCheck

StartChk_x1:
    ldr     good_phase_bit, =1
    b       check_x1

check_x1:
    bl      ClockReset
    and     DQS_VAL0, tmp_var0, #0x000F
    lsl     DQS_VAL0, DQS_VAL0, #4
    ldr     temp_val, =0xFF0F
    and     temp_val, DQS_VAL0_BK, temp_val
    orr     DQS_VAL0, DQS_VAL0, temp_val
    str     DQS_VAL0,[miu_phase_reg0]

    bl      ClockUnReset
    b       StartCheck

StartChk_x0:
    ldr     good_phase_bit, =1
    b       check_x0

check_x0:
    bl      ClockReset
    and     DQS_VAL0, tmp_var0, #0x000F
    lsl     DQS_VAL0, DQS_VAL0, #0
    ldr     temp_val, =0xFFF0
    and     temp_val, DQS_VAL0_BK, temp_val
    orr     DQS_VAL0, DQS_VAL0, temp_val
    str     DQS_VAL0,[miu_phase_reg0]

    bl      ClockUnReset
    b       StartCheck

StartChk_x7:
    ldr     good_phase_bit, =1
    b       check_x7

check_x7:
    bl      ClockReset
    and     DQS_VAL1, tmp_var0, #0x000F
    lsl     DQS_VAL1, DQS_VAL1, #12
    ldr     temp_val, =0x0FFF
    and     temp_val, DQS_VAL1_BK, temp_val
    orr     DQS_VAL1, DQS_VAL1, temp_val
    str     DQS_VAL1,[miu_phase_reg1]

    bl      ClockUnReset
    b       StartCheck

StartChk_x6:
    ldr     good_phase_bit, =1
    b       check_x6

check_x6:
    bl      ClockReset
    and     DQS_VAL1, tmp_var0, #0x000F
    lsl     DQS_VAL1, DQS_VAL1, #8
    ldr     temp_val, =0xF0FF
    and     temp_val, DQS_VAL1_BK, temp_val
    orr     DQS_VAL1, DQS_VAL1, temp_val
    str     DQS_VAL1,[miu_phase_reg1]

    bl      ClockUnReset
    b       StartCheck

StartChk_x5:
    ldr     good_phase_bit, =1
    b       check_x5
    nop

check_x5:
    bl      ClockReset
    and     DQS_VAL1, tmp_var0, #0x000F
    lsl     DQS_VAL1, DQS_VAL1, #4
    ldr     temp_val, =0xFF0F
    and     temp_val, DQS_VAL1_BK, temp_val
    orr     DQS_VAL1, DQS_VAL1, temp_val
    str     DQS_VAL1,[miu_phase_reg1]

    bl      ClockUnReset
    b       StartCheck

StartChk_x4:
    ldr     good_phase_bit, =1
    b       check_x4

check_x4:
    bl      ClockReset
    and     DQS_VAL1, tmp_var0, #0x000F
    lsl     DQS_VAL1, DQS_VAL1, #0
    ldr     temp_val, =0xFFF0
    and     temp_val, DQS_VAL1_BK, temp_val
    orr     DQS_VAL1, DQS_VAL1, temp_val
    str     DQS_VAL1,[miu_phase_reg1]

    bl      ClockUnReset
    b       StartCheck

StartCheck:
.if ( ENABLE_MIU1 == 1 )
    WREG    0x1f200DC0, 0x0000
.endif
    WREG    0x1f2025C0, 0x0000
    WREG    (REG_ADDR_BASE+(0x1012e2<<1)), 0x1000 @ 1012e2 bist test start address, (4K byte/unit)
    ldr     DQS_VAL0, =0x0183             @ bist mode 0x183
    b       ROBitModeTest

Check_bist185:
.if ( ENABLE_MIU1 == 1 )
    WREG    0x1f200DC0, 0x0000
.endif
    WREG    (REG_ADDR_BASE+(0x1012e2<<1)), 0x1100    @ 1012e2 bist test start address, (4K byte/unit)
    WREG    0x1f2025C0, 0x0000
    ldr     DQS_VAL0, =0x0185             @ bist mode 0x0185
    b       ROBitModeTest

Check_bist187:
.if ( ENABLE_MIU1 == 1 )
    WREG    0x1f200DC0, 0x0000
.endif

    WREG    (REG_ADDR_BASE+(0x1012e2<<1)), 0x1200
    WREG    0x1f2025C0, 0x0000
    ldr     DQS_VAL0, =0x0187             @ bist mode 0x187

ROBitModeTest:                      @ read only bist
    bl      ModeChangeDelay

    ldr     temp_val,=0x1f2025c0
    str     DQS_VAL0,[temp_val]

CheckROBistDone:
    RREG    DQS_VAL0, 0x1f2025C0
    and     temp_val, DQS_VAL0, #0x8000
    cmp     temp_val, #0
    beq     CheckROBistDone
    and     temp_val, DQS_VAL0, #0x6000
    cmp     temp_val, #0
    bne     checkloopFail         @ bist test fail if not zero

ROBistCheckPhaseOK:
    @and     r6, r0, #0x1FF
    ldr     temp_val,=0x1f2025c0
    ldr     DQS_VAL0,[temp_val]
    and     DQS_VAL0, DQS_VAL0, #0x00FF

    cmp     DQS_VAL0, #0x083
    beq     Check_bist185        @ 0x183->0x185->0x187
    nop
    cmp     DQS_VAL0, #0x085
    beq     Check_bist187

    and     DQS_VAL0, tmp_var0, #0x0f  @ move $13(loop cnt) to $9 for putchar
    @puthex @reduce boot time 2013/3/29

    add     good_phase_cnt, good_phase_cnt, #1              @ good_phase_cnt++
    and     r11, tmp_var0, #0x0f                          @ get good_phase
    add     good_phase_sum, good_phase_sum, r11              @ good_phase_sum += good phase

checkloopFail:

checkloop:
    lsl     good_phase_bit, good_phase_bit, #1
    add     tmp_var0, tmp_var0, #1                          @add loop cnt by 1
    cmp     tmp_var0, #16
    bne     CheckLoopDone

    cmp     good_phase_cnt, #0
    beq     SetToDefault_P3                              @ if good_phase cnt == 0

    mov     r11, good_phase_sum
    mov     temp_val, good_phase_cnt
    bl      div_op
    mov     DQS_VAL0, r12
    lsl     DQS_VAL0, DQS_VAL0, #12
    b       StorePhase_P3

SetToDefault_P3:
    bl      ClockReset

    mov     DQS_VAL0, DQS_VAL0_BK
    b       SetPhaseToDefault_p3

StorePhase_P3:
    bl      ClockReset

    ldr     r11, =0x0FFF
    and     r11, DQS_VAL0_BK, r11
    orr     DQS_VAL0, DQS_VAL0, r11

SetPhaseToDefault_p3:
    str     DQS_VAL0,[miu_phase_reg0]
    mov     DQS_VAL0_BK, DQS_VAL0

    bl      ClockUnReset

    ldr     good_phase_cnt, =0                  @ good_phase cnt
    ldr     good_phase_sum, =0                  @ good_phase_sum

    @PUTK    ']'
    @PUTK    '\r'
    @PUTK    '\n'
    @PUTK    '['

    @start check DQS_phase_0
    b       StartChk_x2

CheckLoopDone:
    cmp     tmp_var0, #16
    blt     check_x3
    cmp     tmp_var0, #32
    blt     check_x2             @ AutoPhaseLoop1
    cmp     tmp_var0, #32
    beq     SetP2
    cmp     tmp_var0, #48
    blt     check_x1             @ AutoPhaseLoop1
    cmp     tmp_var0, #48
    beq     SetP1
    cmp     tmp_var0, #64
    blt     check_x0             @ AutoPhaseLoop1
    cmp     tmp_var0, #64
    beq     SetP0
    cmp     tmp_var0, #80
    blt     check_x7             @ AutoPhaseLoop1
    cmp     tmp_var0, #80
    beq     SetP7
    cmp     tmp_var0, #96
    blt     check_x6             @ AutoPhaseLoop1
    cmp     tmp_var0, #96
    beq     SetP6
    cmp     tmp_var0, #112
    blt     check_x5             @ AutoPhaseLoop1
    cmp     tmp_var0, #112
    beq     SetP5
    cmp     tmp_var0, #128
    blt     check_x4             @ AutoPhaseLoop1
    cmp     tmp_var0, #128
    beq     SetP4

SetP2:
    cmp     good_phase_cnt, #0
    beq     SetToDefault_P2      @ good_phase cnt == 0
    mov     r11, good_phase_sum
    mov     temp_val, good_phase_cnt
    bl      div_op
    mov     DQS_VAL0, r12
    lsl     DQS_VAL0, DQS_VAL0, #8
    b       StorePhase_P2

SetToDefault_P2:
    bl      ClockReset

    mov     DQS_VAL0, DQS_VAL0_BK
    b       SetPhaseToDefault_P2

StorePhase_P2:
    bl      ClockReset
    ldr     r11, =0xF0FF
    and     r11, DQS_VAL0_BK, r11
    orr     DQS_VAL0, DQS_VAL0, r11

SetPhaseToDefault_P2:
    str     DQS_VAL0,[miu_phase_reg0]
    mov     DQS_VAL0_BK, DQS_VAL0

    bl      ClockUnReset

    ldr     good_phase_cnt, =0                  @ good_phase cnt
    ldr     good_phase_sum, =0                  @ good_phase_sum

    @PUTK    ']'
    @PUTK    '\r'
    @PUTK    '\n'
    @PUTK    '['

    @start check DQS_phase_0
    b       StartChk_x1

SetP1:
    cmp     good_phase_cnt, #0
    beq     SetToDefault_P1      @ good_phase cnt == 0
    mov     r11, good_phase_sum
    mov     temp_val, good_phase_cnt
    bl      div_op
    mov     DQS_VAL0, r12
    lsl     DQS_VAL0, DQS_VAL0, #4
    b       StorePhase_P1

SetToDefault_P1:
    bl      ClockReset

    mov     DQS_VAL0, DQS_VAL0_BK
    b       SetPhaseToDefault_P1

StorePhase_P1:
    bl      ClockReset
    ldr     r11, =0xFF0F
    and     r11, DQS_VAL0_BK, r11
    orr     DQS_VAL0, DQS_VAL0, r11

SetPhaseToDefault_P1:
    str     DQS_VAL0,[miu_phase_reg0]
    mov     DQS_VAL0_BK, DQS_VAL0

    bl      ClockUnReset

    ldr     good_phase_cnt, =0                  @ good_phase cnt
    ldr     good_phase_sum, =0                  @ good_phase_sum

    @PUTK    ']'
    @PUTK    '\r'
    @PUTK    '\n'
    @PUTK    '['

    @start check DQS_phase_0
    b       StartChk_x0

SetP0:
    cmp     good_phase_cnt, #0
    beq     SetToDefault_P0      @ good_phase cnt == 0
    mov     r11, good_phase_sum
    mov     temp_val, good_phase_cnt
    bl      div_op
    mov     DQS_VAL0, r12
    lsl     DQS_VAL0, DQS_VAL0, #0
    b       StorePhase_P0

SetToDefault_P0:
    bl      ClockReset

    mov     DQS_VAL0, DQS_VAL0_BK
    b       SetPhaseToDefault_P0

StorePhase_P0:
    bl      ClockReset
    ldr     r11, =0xFFF0
    and     r11, DQS_VAL0_BK, r11
    orr     DQS_VAL0, DQS_VAL0, r11

SetPhaseToDefault_P0:
    str     DQS_VAL0,[miu_phase_reg0]
    mov     DQS_VAL0_BK, DQS_VAL0

    bl      ClockUnReset

    ldr     good_phase_cnt, =0                  @ good_phase cnt
    ldr     good_phase_sum, =0                  @ good_phase_sum

    @PUTK    ']'
    PUTK    '\r'
    PUTK    '\n'
    @PUTK    '['

    @start check DQS_phase_7
    b       StartChk_x7

SetP7:
    cmp     good_phase_cnt, #0
    beq     SetToDefault_P7      @ good_phase cnt == 0
    mov     r11, good_phase_sum
    mov     temp_val, good_phase_cnt
    bl      div_op
    mov     DQS_VAL1, r12
    lsl     DQS_VAL1, DQS_VAL1, #12
    b       StorePhase_P7

SetToDefault_P7:
    bl      ClockReset

    mov     DQS_VAL1, DQS_VAL1_BK
    b       SetPhaseToDefault_P7

StorePhase_P7:
    bl      ClockReset
    ldr     r11, =0x0FFF
    and     r11, DQS_VAL1_BK, r11
    orr     DQS_VAL1, DQS_VAL1, r11

SetPhaseToDefault_P7:

    str     DQS_VAL1,[miu_phase_reg1]
    mov     DQS_VAL1_BK, DQS_VAL1

    bl      ClockUnReset

    ldr     good_phase_cnt, =0                  @ good_phase cnt
    ldr     good_phase_sum, =0                  @ good_phase_sum

    @PUTK    ']'
    @PUTK    '\r'
    @PUTK    '\n'
    @PUTK    '['

    @start check DQS_phase_6
    b       StartChk_x6

SetP6:
    cmp     good_phase_cnt, #0
    beq     SetToDefault_P6      @ good_phase cnt == 0
    mov     r11, good_phase_sum
    mov     temp_val, good_phase_cnt
    bl      div_op
    mov     DQS_VAL1, r12
    lsl     DQS_VAL1, DQS_VAL1, #8
    b       StorePhase_P6

SetToDefault_P6:
    bl      ClockReset

    mov     DQS_VAL1, DQS_VAL1_BK
    b       SetPhaseToDefault_P6

StorePhase_P6:
    bl      ClockReset
    ldr     r11, =0xF0FF
    and     r11, DQS_VAL1_BK, r11
    orr     DQS_VAL1, DQS_VAL1, r11

SetPhaseToDefault_P6:
    str     DQS_VAL1,[miu_phase_reg1]
    mov     DQS_VAL1_BK, DQS_VAL1

    bl      ClockUnReset

    ldr     good_phase_cnt, =0                  @ good_phase cnt
    ldr     good_phase_sum, =0                  @ good_phase_sum

    @PUTK    ']'
    @PUTK    '\r'
    @PUTK    '\n'
    @PUTK    '['

    @start check DQS_phase_5
    b       StartChk_x5

SetP5:
    cmp     good_phase_cnt, #0
    beq     SetToDefault_P5      @ good_phase cnt == 0
    mov     r11, good_phase_sum
    mov     temp_val, good_phase_cnt
    bl      div_op
    mov     DQS_VAL1, r12
    lsl     DQS_VAL1, DQS_VAL1, #4
    b       StorePhase_P5

SetToDefault_P5:
    bl      ClockReset

    mov     DQS_VAL1, DQS_VAL1_BK
    b       SetPhaseToDefault_P5

StorePhase_P5:
    bl      ClockReset
    ldr     r11, =0xFF0F
    and     r11, DQS_VAL1_BK, r11
    orr     DQS_VAL1, DQS_VAL1, r11

SetPhaseToDefault_P5:
    str     DQS_VAL1,[miu_phase_reg1]
    mov     DQS_VAL1_BK, DQS_VAL1

    bl      ClockUnReset

    ldr     good_phase_cnt, =0                  @ good_phase cnt
    ldr     good_phase_sum, =0                  @ good_phase_sum

    @PUTK    ']'
    @PUTK    '\r'
    @PUTK    '\n'
    @PUTK    '['

    @start check DQS_phase_4
    b       StartChk_x4

SetP4:
    cmp     good_phase_cnt, #0
    beq     SetToDefault_P4      @ good_phase cnt == 0
    mov     r11, good_phase_sum
    mov     temp_val, good_phase_cnt
    bl      div_op
    mov     DQS_VAL1, r12
    lsl     DQS_VAL1, DQS_VAL1, #0
    b       StorePhase_P4

SetToDefault_P4:
    bl      ClockReset

    mov     DQS_VAL1, DQS_VAL1_BK
    b       SetPhaseToDefault_P4

StorePhase_P4:
    bl      ClockReset
    ldr     r11, =0xFFF0
    and     r11, DQS_VAL1_BK, r11
    orr     DQS_VAL1, DQS_VAL1, r11

SetPhaseToDefault_P4:
    str     DQS_VAL1,[miu_phase_reg1]
    mov     DQS_VAL1_BK, DQS_VAL1


    bl      ClockUnReset

    ldr     good_phase_cnt, =0                  @ good_phase cnt
    ldr     good_phase_sum, =0                  @ good_phase_sum

    @PUTK    ']'
    @PUTK    '\r'
    @PUTK    '\n'
    @PUTK    '{'

    and     DQS_VAL0, DQS_VAL0_BK, #0xF000
    lsr     DQS_VAL0, DQS_VAL0, #12
    bl      puthex
    and     DQS_VAL0, DQS_VAL0_BK, #0x0F00
    lsr     DQS_VAL0, DQS_VAL0, #8
    bl      puthex
    and     DQS_VAL0, DQS_VAL0_BK, #0x00F0
    lsr     DQS_VAL0, DQS_VAL0, #4
    bl      puthex
    and     DQS_VAL0, DQS_VAL0_BK, #0x000F
    lsr     DQS_VAL0, DQS_VAL0, #0
    bl      puthex

    PUTK    '_'

    and     DQS_VAL0, DQS_VAL1_BK, #0xF000
    lsr     DQS_VAL0, DQS_VAL0, #12
    bl      puthex
    and     DQS_VAL0, DQS_VAL1_BK, #0x0F00
    lsr     DQS_VAL0, DQS_VAL0, #8
    bl      puthex
    and     DQS_VAL0, DQS_VAL1_BK, #0x00F0
    lsr     DQS_VAL0, DQS_VAL0, #4
    bl      puthex
    and     DQS_VAL0, DQS_VAL1_BK, #0x000F
    lsr     DQS_VAL0, DQS_VAL0, #0
    bl      puthex

    @PUTK    '}'
    PUTK    '\r'
    PUTK    '\n'

	bx          lr

@//-------------------------------------------------------------------------------------------------
@// puthex 
@// @param  None
@// @return None
@// @note   None
@//-------------------------------------------------------------------------------------------------
puthex:
    cmp     r0, #10
    blt     putx0_9
    nop
putxA_F:
    add     r0, r0, #0x37
    b       putx
    nop
putx0_9:
    add     r0, r0, #0x30
putx:
    ldr     r5, =0x1F201300
    str     r0,[r5]
    nop

	bx          lr

@//-------------------------------------------------------------------------------------------------
@// div_op 
@// @param  None
@// @return None
@// @note   None
@//-------------------------------------------------------------------------------------------------
div_op:
    @ldr     r11, =128    @ divide r11
    @ldr     r5, =4      @ by r5
    ldr     r12,=0      @ init counter
subtract:
    sub     r11, r11, r5
    add     r12,r12, #1
    cmp     r11,r5
    bhs     subtract

	bx          lr

@//-------------------------------------------------------------------------------------------------
@// ModeChangeDelay 
@// @param  None
@// @return None
@// @note   None
@//-------------------------------------------------------------------------------------------------
ModeChangeDelay:
#define temp_val       r5      // $8
    ldr     temp_val,=0
DelayLoop:
    add     temp_val, temp_val, #1
    cmp     temp_val, #10
    bne     DelayLoop
    nop

	bx          lr

@//-------------------------------------------------------------------------------------------------
@// ClockReset 
@// @param  None
@// @return None
@// @note   None
@//-------------------------------------------------------------------------------------------------
ClockReset:
    ldr     r11, =(REG_ADDR_BASE+(0x110D0E<<1))
    ldr     r12, [r11]
    and     r12, r12, #0x9F
    orr     r12, r12, #0x60
    strb    r12, [r11]

	bx          lr

@//-------------------------------------------------------------------------------------------------
@// ClockUnReset 
@// @param  None
@// @return None
@// @note   None
@//-------------------------------------------------------------------------------------------------
ClockUnReset:
    ldr     r11, =(REG_ADDR_BASE+(0x110D0E<<1))
    ldr     r12, [r11]
    and     r12, r12, #0x9F
    orr     r12, r12, #0x20
    strb    r12, [r11]

	bx          lr
#else
@//================================================================================================

#define MIU_PHASE_LOOP_START            0x00                    @//The Starting Phase of Auto DQS: 0
#define MIU_PHASE_LOOP_END              0x0F                    @//The Maximum Phase of Auto DQS: 15
#define MIU_PHASE_TEST_SELECTION        (MS_BUS_RIU_ADDR + (0x103382 << 1))
#define MIU_GOOD_PHASE_START_NUMBER     (MS_BUS_RIU_ADDR + (0x103384 << 1))
#define MIU_GOOD_PHASE_COUNTER          (MS_BUS_RIU_ADDR + (0x103386 << 1))
#define MIU_ORGINAL_PHASE_SETTING       (MS_BUS_RIU_ADDR + (0x103388 << 1))
#define MIU_PHASE_REGISTER              r4
#define MIU_PHASE_LOOP_COUNTER          r5


@//================================================================================================
.if ( ENABLE_MIU1 == 1 )
    .global     Miu1_AutoPhase
Miu1_AutoPhase:

    DPUTK_STR   MIU_MESSAGE_AUTO_DQS1

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x8000                 @//RREG        r0, (MS_BUS_RIU_ADDR + (0x1012f0 << 1))         @//Select BIST to MIU1 (0x1012F0[15] = 1)
    str         r11, [r12, #(0xf0 << 1)]     @//REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x1012f0 << 1))

    @//r4: MIU0 Phase Register Address (MIU0: 0x110d6e / MIU1: 0x110dee)
    ldr         MIU_PHASE_REGISTER, =(MS_BUS_RIU_ADDR + (0x110dee << 1))

    b           Miu_AutoPhase
.endif
@//================================================================================================
    .global     Miu0_AutoPhase
Miu0_AutoPhase:

    DPUTK_STR   MIU_MESSAGE_AUTO_DQS0

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000                @//RREG        r0, (MS_BUS_RIU_ADDR + (0x1012f0 << 1))         @//Select BIST to MIU0 (0x1012F0[15] = 0)
    str         r11, [r12, #(0xf0 << 1)]    @//REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x1012f0 << 1))

    @//r4: MIU0 Phase Register Address (MIU0: 0x110d6e / MIU1: 0x110dee)
    ldr         MIU_PHASE_REGISTER, =(MS_BUS_RIU_ADDR + (0x110d6e << 1))

@//================================================================================================
    .global     Miu_AutoPhase
Miu_AutoPhase:

    ldr         MIU_PHASE_LOOP_COUNTER, =MIU_PHASE_LOOP_START   @//r5: Phase Loop Counter (0 ~ 15)
    WREG        MIU_PHASE_TEST_SELECTION, 0                     @//0x103382[0]: MIU Auto Phase Test Selection
    WREG        MIU_GOOD_PHASE_START_NUMBER, 0                  @//0x103384[15:0]: Starting Number of Good Phase
    WREG        MIU_GOOD_PHASE_COUNTER, 0                       @//0x103386[15:0]: The Number of Good Phase

    ldr         r0, [MIU_PHASE_REGISTER]
    REG_C2M     r0, MIU_ORGINAL_PHASE_SETTING                   @//0x103388[15:0]: Backup Orginal Phase Setting

@//================================================================================================
Miu_AutoDqs_Bist_Setup:

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x3fff
    str         r11, [r12, #(0xe2 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e2 << 1)), 0x3fff     @//Set Testing Address of BIST
    ldr         r11, =0x0401
    str         r11, [r12, #(0xe4 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e4 << 1)), 0x0401     @//Set Testing Length of BIST
    ldr         r11, =0x00ff
    str         r11, [r12, #(0xe8 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e8 << 1)), 0x00ff     @//Set Testing Pattern of BIST

@//================================================================================================
Miu_AutoDqs_Phase_Selection:

    RREG        r0, MIU_PHASE_TEST_SELECTION                    @//Select Testing Phase of Auto DQS (0 / 1)
    and         r0, r0, #0x03
    cmp         r0, #0x00
    beq         Miu_AutoDqs_Phase0_Loop

    cmp         r0, #0x01
    beq         Miu_AutoDqs_Phase1_Loop

    cmp         r0, #0x02
    beq         Miu_AutoDqs_Phase2_Loop

@//================================================================================================
Miu_AutoDqs_Phase3_Loop:

    @//r4: MIU Phase Register Address (MIU0: 0x110d6e / MIU1: 0x110dee)
    @//r5: Phase Loop Counter (0 ~ 15)
    ldr         r0, [MIU_PHASE_REGISTER]
    ldr         r1, =0x0fff
    and         r0, r0, r1                                      @//In Phase 3, Update Higher Byte of MIU Phase Register
    mov         r1, MIU_PHASE_LOOP_COUNTER, lsl #12
    orr         r0, r0, r1
    str         r0, [MIU_PHASE_REGISTER]

    b           Miu_AutoDqs_Bist_Mode1                          @//After Phase Counter Updated, Execute BIST Again

@//================================================================================================
Miu_AutoDqs_Phase2_Loop:

    @//r4: MIU Phase Register Address (MIU0: 0x110d6e / MIU1: 0x110dee)
    @//r5: Phase Loop Counter (0 ~ 15)
    ldr         r0, [MIU_PHASE_REGISTER]
    ldr         r1, =0xf0ff
    and         r0, r0, r1                                      @//In Phase 2, Update Higher Byte of MIU Phase Register
    mov         r1, MIU_PHASE_LOOP_COUNTER, lsl #8
    orr         r0, r0, r1
    str         r0, [MIU_PHASE_REGISTER]

    b           Miu_AutoDqs_Bist_Mode1                          @//After Phase Counter Updated, Execute BIST Again

@//================================================================================================
Miu_AutoDqs_Phase1_Loop:

    @//r4: MIU Phase Register Address (MIU0: 0x110d6e / MIU1: 0x110dee)
    @//r5: Phase Loop Counter (0 ~ 15)
    ldr         r0, [MIU_PHASE_REGISTER]
    ldr         r1, =0xff0f
    and         r0, r0, r1                                      @//In Phase 1, Update Higher Byte of MIU Phase Register
    mov         r1, MIU_PHASE_LOOP_COUNTER, lsl #4
    orr         r0, r0, r1
    str         r0, [MIU_PHASE_REGISTER]

    b           Miu_AutoDqs_Bist_Mode1                          @//After Phase Counter Updated, Execute BIST Again

@//================================================================================================
Miu_AutoDqs_Phase0_Loop:

    @//r4: MIU Phase Register Address (MIU0: 0x110d6e / MIU1: 0x110dee)
    @//r5: Phase Loop Counter (0 ~ 15)
    ldr         r0, [MIU_PHASE_REGISTER]
    ldr         r1, =0xfff0
    and         r0, r0, r1                                      @//In Phase 0, Update Lower Byte of MIU Phase Register
    orr         r0, r0, MIU_PHASE_LOOP_COUNTER
    str         r0, [MIU_PHASE_REGISTER]

    b           Miu_AutoDqs_Bist_Mode1                          @//After Phase Counter Updated, Execute BIST Again

@//================================================================================================
Miu_AutoDqs_Bist_Mode_Selection:

    RREG        r0, (MS_BUS_RIU_ADDR + (0x1012e0 << 1))
    and         r0, r0, #0xff

    cmp         r0, #0x81
    beq         Miu_AutoDqs_Bist_Mode3                          @//MIU BIST Mode 1 -> MIU BIST Mode 3

    cmp         r0, #0x83
    beq         Miu_AutoDqs_Bist_Mode5                          @//MIU BIST Mode 3 -> MIU BIST Mode 5

    cmp         r0, #0x85
    beq         Miu_AutoDqs_Bist_Mode7                          @//MIU BIST Mode 5 -> MIU BIST Mode 7

    mov         r1, MIU_PHASE_LOOP_COUNTER
    mov         r2, lr
    bl          Miu_AutoDqs_PrintMessage                        @//If All Mode BIST Pass, Print Current Loop Count
    mov         lr, r2

    RREG        r0, MIU_GOOD_PHASE_COUNTER
    add         r1, r0, #1
    REG_C2M     r1, MIU_GOOD_PHASE_COUNTER                      @//If All Mode BIST Pass, Good Phase Counter + 1

    cmp         r0, #0
    bne         Miu_AutoDqs_Bist_Done

    REG_C2M     MIU_PHASE_LOOP_COUNTER, MIU_GOOD_PHASE_START_NUMBER     @//If No Found Good Phase Before,
                                                                        @//Record Current Loop Count as The Starting Good Phase

    b           Miu_AutoDqs_Bist_Done

@//================================================================================================
Miu_AutoDqs_Bist_Mode1:
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x00
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x81       @//MIU BIST Mode 1

    b           Miu_AutoDqs_Bist_Mode_Loop

@//================================================================================================
Miu_AutoDqs_Bist_Mode3:
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x00
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x83       @//MIU BIST Mode 3

    b           Miu_AutoDqs_Bist_Mode_Loop

@//================================================================================================
Miu_AutoDqs_Bist_Mode5:
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x00
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x85       @//MIU BIST Mode 5

    b           Miu_AutoDqs_Bist_Mode_Loop

@//================================================================================================
Miu_AutoDqs_Bist_Mode7:
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x00
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x87       @//MIU BIST Mode 7

@//================================================================================================
Miu_AutoDqs_Bist_Mode_Loop:
    RREG        r0, (MS_BUS_RIU_ADDR + (0x1012e0 << 1))
    and         r1, r0, #0x8000                                 @//Check MIU BIST Done Status (0x1012e0[15] = 1)
    cmp         r1, #0x0000
    beq         Miu_AutoDqs_Bist_Mode_Loop

    and         r1, r0, #0x4000                                 @//Check MIU BIST Fail Status (0x1012e0[14] = 1)
    cmp         r1, #0x4000
    bne         Miu_AutoDqs_Bist_Mode_Selection                 @//If Current MIU BIST Pass, Execute Next Mode of BIST

@//================================================================================================
Miu_AutoDqs_Bist_Done:

    add         MIU_PHASE_LOOP_COUNTER, MIU_PHASE_LOOP_COUNTER, #1  @//r5: Phase Loop Counter (0 ~ 15)
    cmp         MIU_PHASE_LOOP_COUNTER, #MIU_PHASE_LOOP_END
    ble         Miu_AutoDqs_Phase_Selection                     @//If Current Loop Counter <= Maximum Setting, Execute Next Phase Testing

    RREG        r0, MIU_PHASE_TEST_SELECTION
    and         r0, r0, #0x03

    cmp         r0, #0x00
    beq         Miu_AutoDqs_Phase0_Loop_Done

    cmp         r0, #0x01
    beq         Miu_AutoDqs_Phase1_Loop_Done

    cmp         r0, #0x02
    beq         Miu_AutoDqs_Phase2_Loop_Done

    cmp         r0, #0x03
    beq         Miu_AutoDqs_Phase3_Loop_Done                    @//If Phase 3 Testing was Executed, Terminate MIU Auto DQS

@//================================================================================================
Miu_AutoDqs_Phase0_Loop_Done:
    @//r4: MIU Phase Register Address (MIU0: 0x110d6e / MIU1: 0x110dee)
    @//r5: Phase Loop Counter (0 ~ 15)
    ldr         r0, [MIU_PHASE_REGISTER]
    ldr         r1, =0xfff0
    and         r0, r0, r1

    RREG        r1, MIU_GOOD_PHASE_START_NUMBER
    RREG        r2, MIU_GOOD_PHASE_COUNTER
    sub         r2, r2, #0x01
    mov         r2, r2, lsr #1                                  @//Get the Half Value of Good Phase Counter
    add         r1, r1, r2                                      @//Compute Final Good Phase Setting
    and         r1, r1, #0x0f
    orr         r0, r0, r1
    str         r0, [MIU_PHASE_REGISTER]                        @//Update Phase 0 Setting to Register

    b           Miu_AutoDqs_Loop_Exit

@//================================================================================================
Miu_AutoDqs_Phase1_Loop_Done:
    @//r4: MIU Phase Register Address (MIU0: 0x110d6e / MIU1: 0x110dee)
    @//r5: Phase Loop Counter (0 ~ 15)
    ldr         r0, [MIU_PHASE_REGISTER]
    ldr         r1, =0xff0f
    and         r0, r0, r1

    RREG        r1, MIU_GOOD_PHASE_START_NUMBER
    RREG        r2, MIU_GOOD_PHASE_COUNTER
    sub         r2, r2, #0x01
    mov         r2, r2, lsr #1                                  @//Get the Half Value of Good Phase Counter
    add         r1, r1, r2                                      @//Compute Final Good Phase Setting
    and         r1, r1, #0x0f
    mov         r1, r1, lsl #4
    orr         r0, r0, r1
    str         r0, [MIU_PHASE_REGISTER]                        @//Update Phase 0 Setting to Register

    b           Miu_AutoDqs_Loop_Exit

@//================================================================================================
Miu_AutoDqs_Phase2_Loop_Done:
    @//r4: MIU Phase Register Address (MIU0: 0x110d6e / MIU1: 0x110dee)
    @//r5: Phase Loop Counter (0 ~ 15)
    ldr         r0, [MIU_PHASE_REGISTER]
    ldr         r1, =0xf0ff
    and         r0, r0, r1

    RREG        r1, MIU_GOOD_PHASE_START_NUMBER
    RREG        r2, MIU_GOOD_PHASE_COUNTER
    sub         r2, r2, #0x01
    mov         r2, r2, lsr #1                                  @//Get the Half Value of Good Phase Counter
    add         r1, r1, r2                                      @//Compute Final Good Phase Setting
    and         r1, r1, #0x0f
    mov         r1, r1, lsl #8
    orr         r0, r0, r1
    str         r0, [MIU_PHASE_REGISTER]                        @//Update Phase 0 Setting to Register

@//================================================================================================
Miu_AutoDqs_Loop_Exit:

    DPUTK       ']'
    DPUTK       '['

    ldr         MIU_PHASE_LOOP_COUNTER, =MIU_PHASE_LOOP_START   @//r5: Phase Loop Counter (0 ~ 15)
    RREG        r0, MIU_PHASE_TEST_SELECTION
    add         r0, r0, #0x01
    REG_C2M     r0, MIU_PHASE_TEST_SELECTION
    WREG        MIU_GOOD_PHASE_START_NUMBER, 0
    WREG        MIU_GOOD_PHASE_COUNTER, 0
    b           Miu_AutoDqs_Phase_Selection

@//================================================================================================
Miu_AutoDqs_Phase3_Loop_Done:

    @//r4: MIU Phase Register Address (MIU0: 0x110d6e / MIU1: 0x110dee)
    @//r5: Phase Loop Counter (0 ~ 15)
    ldr         r0, [MIU_PHASE_REGISTER]
    ldr         r1, =0x0fff
    and         r0, r0, r1

    RREG        r1, MIU_GOOD_PHASE_START_NUMBER
    RREG        r2, MIU_GOOD_PHASE_COUNTER
    sub         r2, r2, #0x01
    mov         r2, r2, lsr #1                                  @//Get the Half Value of Good Phase Counter
    add         r1, r1, r2                                      @//Compute Final Good Phase Setting
    and         r1, r1, #0x0f
    mov         r1, r1, lsl #12
    orr         r0, r0, r1
    str         r0, [MIU_PHASE_REGISTER]                        @//Update Phase 1 Setting to Register

@//================================================================================================
Miu_AutoDqs_ErrorCheck:

    ldr         r0, [MIU_PHASE_REGISTER]

    ldr         r2, =0x0ff
    and         r1, r0, r2                                      @//Check the Value of MIU Phase 3
    cmp         r1, #0
    beq         Miu_AutoDqs_Restore_Default_Setting

    ldr         r2, =0xf0ff
    and         r1, r0, r2                                      @//Check the Value of MIU Phase 2
    cmp         r1, #0
    beq         Miu_AutoDqs_Restore_Default_Setting

    ldr         r2, =0xff0f
    and         r1, r0, r2                                      @//Check the Value of MIU Phase 1
    cmp         r1, #0
    beq         Miu_AutoDqs_Restore_Default_Setting

    ldr         r2, =0xfff0
    and         r1, r0, r2                                      @//Check the Value of MIU Phase 0
    cmp         r1, #0
    beq         Miu_AutoDqs_Restore_Default_Setting

    DPUTK_STR   MIU_MESSAGE_DQS_1

    ldr         r0, [MIU_PHASE_REGISTER]

    ldr         r2, =0xf000
    and         r1, r0, r2
    mov         r1, r1, lsr #12

    mov         r2, lr
    bl          Miu_AutoDqs_PrintMessage
    mov         lr, r2

    ldr         r2, =0x0f00
    and         r1, r0, r2
    mov         r1, r1, lsr #8

    mov         r2, lr
    bl          Miu_AutoDqs_PrintMessage
    mov         lr, r2

    ldr         r2, =0x00f0
    and         r1, r0, r2
    mov         r1, r1, lsr #4

    mov         r2, lr
    bl          Miu_AutoDqs_PrintMessage
    mov         lr, r2

    ldr         r2, =0x000f
    and         r1, r0, r2
    mov         r2, lr
    bl          Miu_AutoDqs_PrintMessage
    mov         lr, r2

    DPUTK       ']'

    b           Miu_AutoDqs_Exit

@//================================================================================================
Miu_AutoDqs_Restore_Default_Setting:

    RREG        r0, MIU_ORGINAL_PHASE_SETTING                   @//0x103388[15:0]: Backup Orginal Phase Setting
    str         r0, [MIU_PHASE_REGISTER]                        @//Resotre Default Setting to Phase Register

    DPUTK_STR   MIU_MESSAGE_FAIL

@//================================================================================================
Miu_AutoDqs_Exit:

    DPUTK       '\r'
    DPUTK       '\n'

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r0, [r12, #(0xf0 << 1)]     @//RREG        r0, (MS_BUS_RIU_ADDR + (0x1012f0 << 1))         @//Select BIST to MIU0 (0x1012F0[15] = 0)
    bic         r0, r0, #0x8000
    str         r0, [r12, #(0xf0 << 1)]     @//REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x1012f0 << 1))

@// WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x0000     @//Release MIU Client Mask on MIU0
@// WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0x0000
@// WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0x0000
@// WREG        (MS_BUS_RIU_ADDR + (0x1012a6 << 1)), 0x0000

@// WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x0000     @//Release MIU Client Mask on MIU1
@// WREG        (MS_BUS_RIU_ADDR + (0x100666 << 1)), 0x0000
@// WREG        (MS_BUS_RIU_ADDR + (0x100686 << 1)), 0x0000
@// WREG        (MS_BUS_RIU_ADDR + (0x1006a6 << 1)), 0x0000

    bx          lr

@//================================================================================================
Miu_AutoDqs_PrintMessage:
    cmp         r1, #0x09
    ble         Miu_AutoDqs_PrintMessage_Digit

    sub         r1, r1, #0x0a
    add         r1, r1, #'A'
    b           Miu_AutoDqs_PrintMessage_Exec

Miu_AutoDqs_PrintMessage_Digit:
    add         r1, r1, #'0'

Miu_AutoDqs_PrintMessage_Exec:
    REG_C2M     r1, (0x1F000000 + (0x100980 << 1))

    bx          lr

@//================================================================================================
#endif
	
    .size       BootRom_InitMiu,.-BootRom_InitMiu
