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
 
    .global     BootRom_InitMiu_STR
BootRom_InitMiu_STR:

    mov         r13, lr

    @//WREG    0x1F201674, 0x0808  @ turn on miu clock

    WREG        (MS_BUS_RIU_ADDR + (0x110d00 << 1)), 0x2018
    WREG        (MS_BUS_RIU_ADDR + (0x110d80 << 1)), 0x2018
    
    WREG        (MS_BUS_RIU_ADDR + (0x110d18 << 1)), 0x3F80
    WREG        (MS_BUS_RIU_ADDR + (0x110d98 << 1)), 0x3F80
    DELAYUS     200                                         @//delay 200us

    WREG        (MS_BUS_RIU_ADDR + (0x110d00 << 1)), 0x0008
    WREG        (MS_BUS_RIU_ADDR + (0x110d80 << 1)), 0x0008
    
    WREG        (MS_BUS_RIU_ADDR + (0x110d18 << 1)), 0x1000
    WREG        (MS_BUS_RIU_ADDR + (0x110d98 << 1)), 0x1000
    DELAYUS     1000                                         @//delay 200us

    @ MIU0 Software reset
    WREG    (MS_BUS_RIU_ADDR + (0x10121e <<1 )) , 0x0000   @hold miu_0
    WREG    (MS_BUS_RIU_ADDR + (0x10121e <<1 )) , 0x0c01   @miu_sw_rst
    WREG    (MS_BUS_RIU_ADDR + (0x10121e <<1 )) , 0x0c00   @
    WREG    (MS_BUS_RIU_ADDR + (0x101202 <<1 )) , 0xf000   @disable all ddr bus out

    @ MIU0 Request mask
    WREG    (MS_BUS_RIU_ADDR + (0x101246 <<1 )) , 0x7FFE   @ mask group0
    WREG    (MS_BUS_RIU_ADDR + (0x101266 <<1 )) , 0xFFFF   @ mask group1
    WREG    (MS_BUS_RIU_ADDR + (0x101286 <<1 )) , 0xFFFF   @ mask group2
    WREG    (MS_BUS_RIU_ADDR + (0x1012A6 <<1 )) , 0xFFFF   @ mask group3

.if ( ENABLE_MIU1 == 1 )
    @ MIU1 Software reset
    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )) , 0x0000   @hold miu_0
    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )) , 0x0c01   @
    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )) , 0x0c00   @
    WREG    (MS_BUS_RIU_ADDR + (0x100602 <<1 )) , 0xf000   @

    @ MIU1 Request mask
    WREG    (MS_BUS_RIU_ADDR + (0x100646 <<1 )) , 0x7FFE   @ mask group0
    WREG    (MS_BUS_RIU_ADDR + (0x100666 <<1 )) , 0xFFFF   @ mask group1
    WREG    (MS_BUS_RIU_ADDR + (0x100686 <<1 )) , 0xFFFF   @ mask group2
    WREG    (MS_BUS_RIU_ADDR + (0x1006A6 <<1 )) , 0xFFFF   @ mask group3
.endif

    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
    WREG    (MS_BUS_RIU_ADDR + (0x110d36 <<1 )) , 0x4002   @ reg_DDRPLL_LOOP_DIV_FIRST	: [15:14]	divide by 4
    #endif
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
    WREG    (MS_BUS_RIU_ADDR + (0x110d36 <<1 )) , 0x4000   @ reg_DDRPLL_LOOP_DIV_FIRST	: [15:14]	divide by 4
    #endif

    WREG    (MS_BUS_RIU_ADDR + (0x110d34 <<1 )) , 0x0300   @ reg_DDRPLL_LOOP_DIV_SECOND	: [15:14]	divide by 3
    WREG    (MS_BUS_RIU_ADDR + (0x110d30 <<1 )) , 0xeb85   @ set pll to 780 MHz
    WREG    (MS_BUS_RIU_ADDR + (0x110d32 <<1 )) , 0x0019

    @ Avoid DDRPLL unknown(MCLK05X & MCLK025X) by resset ddrat[28]
    WREG    (MS_BUS_RIU_ADDR + (0x110d24 <<1 )) , 0x1000

.if ( ENABLE_MIU1 == 1 )
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
    WREG    (MS_BUS_RIU_ADDR + (0x110db6 <<1 )) , 0x4001   @ reg_DDRPLL_LOOP_DIV_FIRST    : [15:14]   divide by 4
    #endif
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
    WREG    (MS_BUS_RIU_ADDR + (0x110db6 <<1 )) , 0x4000   @ reg_DDRPLL_LOOP_DIV_FIRST    : [15:14]   divide by 4
    #endif

    WREG    (MS_BUS_RIU_ADDR + (0x110db4 <<1 )) , 0x0300   @ reg_DDRPLL_LOOP_DIV_SECOND   : [15:14]   divide by 3
    WREG    (MS_BUS_RIU_ADDR + (0x110db0 <<1 )) , 0xeb85   @ set pll to 780 MHz
    WREG    (MS_BUS_RIU_ADDR + (0x110db2 <<1 )) , 0x0019

    @ Avoid DDRPLL unknown(MCLK05X & MCLK025X) by resset ddrat[28]
    WREG    (MS_BUS_RIU_ADDR + (0x110da4 <<1 )) , 0x1000
.endif

    DELAYUS 5000    @ delay 5ms

    WREG    (MS_BUS_RIU_ADDR + (0x110d24 <<1 )) , 0x0000
.if ( ENABLE_MIU1 == 1 )
    WREG    (MS_BUS_RIU_ADDR + (0x110da4 <<1 )) , 0x0000
.endif

    ldr r0, =MIU0_DDR_Init_STR
    bl MDrv_WriteRegTbl32

    DELAYUS 1000    @ delay 1ms

    WREG    (MS_BUS_RIU_ADDR + (0x10121e <<1 )) , 0x0c01   @miu_sw_rst

    DELAYUS 1      @ delay 1us

    WREG    (MS_BUS_RIU_ADDR + (0x10121e <<1 )) , 0x0c08

    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
    WREG    (MS_BUS_RIU_ADDR + (0x110d00 <<1 )) , 0x1e09   @reg_pkg_sel      1   : [0]
    #endif
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
    WREG    (MS_BUS_RIU_ADDR + (0x110d00 <<1 )) , 0x1e0a   @reg_pkg_sel      1   : [0]
    #endif

    WREG    (MS_BUS_RIU_ADDR + (0x110d02 <<1 )) , 0xaaaa   @reg_cko_state        cc  : [7:0]
    WREG    (MS_BUS_RIU_ADDR + (0x110d18 <<1 )) , 0x1000   @STR
    WREG    (MS_BUS_RIU_ADDR + (0x101202 <<1 )) , 0xf3a7
    WREG    (MS_BUS_RIU_ADDR + (0x110d54 <<1 )) , 0x0070

.if ( ENABLE_MIU1 == 1 )
    ldr r0, =MIU1_DDR_Init_STR
    bl MDrv_WriteRegTbl32

    DELAYUS 1000    @ delay 1ms

    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )) , 0x0c01   @miu_sw_rst

    DELAYUS 1      @ delay 1us

    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )) , 0x0c08

    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
    WREG    (MS_BUS_RIU_ADDR + (0x110d80 <<1 )) , 0x1e09   @reg_pkg_sel      1   : [0]
    #endif
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
    WREG    (MS_BUS_RIU_ADDR + (0x110d80 <<1 )) , 0x1e0a   @reg_pkg_sel      1   : [0]
    #endif

    WREG    (MS_BUS_RIU_ADDR + (0x110d82 <<1 )) , 0xaaaa   @reg_cko_state        cc  : [7:0]
    WREG    (MS_BUS_RIU_ADDR + (0x110d98 <<1 )) , 0x1000   @STR
    WREG    (MS_BUS_RIU_ADDR + (0x100602 <<1 )) , 0xf3a3
    WREG    (MS_BUS_RIU_ADDR + (0x110dd4 <<1 )) , 0x0070
.endif

    DELAYUS  100  @ delay 100us

    @ MIU0 INIT Cycle
    WREG    (MS_BUS_RIU_ADDR + (0x101200 <<1 )), 0x0000 @ hold miu_0
    WREG    (MS_BUS_RIU_ADDR + (0x101200 <<1 )), 0x0008 @ DRAM reset
    WREG    (MS_BUS_RIU_ADDR + (0x101200 <<1 )), 0x000c @ DRAM reset+CS
    DELAYUS 300                                         @ delay 300us
    WREG    (MS_BUS_RIU_ADDR + (0x101200 <<1 )), 0x000e @ DRAM reset+CS+CKE
    DELAYUS 500                                         @ delay 500us
    WREG    (MS_BUS_RIU_ADDR + (0x101200 <<1 )), 0x001f @ DRAM reset+CS+CKE+auto cycle+ODE
    DBGREG  0x0025


.if ( ENABLE_MIU1 == 1 )
    @ MIU1 INIT Cycle
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x0000 @ hold miu_0
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x0008 @ DRAM reset
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x000c @ DRAM reset+CS
    DELAYUS 300                                         @ delay 300us
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x000e @ DRAM reset+CS+CKE
    DELAYUS 500                                         @ delay 500us
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x001f @ DRAM reset+CS+CKE+auto cycle+ODE
.endif

    bl Miu_auto_phase_str
    
    bl Enter_DDR_RefreshMode
 
    bl Miu_str_oenz_disable
 
    WREG        (MS_BUS_RIU_ADDR + (0x110D54 <<1 )), 0x0000 @//ATOP_PD off
.if ( ENABLE_MIU1 == 1 )
    WREG        (MS_BUS_RIU_ADDR + (0x110Dd4 <<1 )), 0x0000 @//ATOP_PD off
.endif

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

    bl Exit_DDR_RefreshMode

    bl Push_Dram_STR 


    DELAYUS 200   @ delay 200us

    @ U04 last down Z switch
    RREG    r0, (MS_BUS_RIU_ADDR + (0x001e02 <<1 ))
    bic     r0, r0, #0x00FF
    lsr     r0, r0, #8
    cmp     r0, #3 
    blt     U03_chip_bypass_str
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
U03_chip_bypass_str:

    @ last_done_z select to last stage
    WREG    (MS_BUS_RIU_ADDR + (0x101252 <<1 )) , 0xFFFF
    WREG    (MS_BUS_RIU_ADDR + (0x101272 <<1 )) , 0xFFFF
    WREG    (MS_BUS_RIU_ADDR + (0x101292 <<1 )) , 0xFFFF
    WREG    (MS_BUS_RIU_ADDR + (0x1012B2 <<1 )) , 0xFFFF
.if ( ENABLE_MIU1 == 1 )
    WREG    (MS_BUS_RIU_ADDR + (0x100652 <<1 )) , 0xFFFF
    WREG    (MS_BUS_RIU_ADDR + (0x100672 <<1 )) , 0xFFFF
    WREG    (MS_BUS_RIU_ADDR + (0x100692 <<1 )) , 0xFFFF
    WREG    (MS_BUS_RIU_ADDR + (0x1006B2 <<1 )) , 0xFFFF
.endif

    bl Push_Dram_STR
    @//bl Miu_init_priority_str

    RREG        r8, (MS_BUS_RIU_ADDR + (0x130004 << 1))
    orr         r8, r8, #0x0001
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x130004 << 1))

    RREG        r8, (MS_BUS_RIU_ADDR + (0x130004 << 1))
    bic         r8, r8, #0x0001
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x130004 << 1))

    @ open all MIU0 request mask (All IP can access MIU resource)
    WREG    (MS_BUS_RIU_ADDR + (0x101246 <<1 )) , 0x0000   @Mask MIU0_group_0
    WREG    (MS_BUS_RIU_ADDR + (0x101266 <<1 )) , 0x0000   @Mask MIU0_group_1
    WREG    (MS_BUS_RIU_ADDR + (0x101286 <<1 )) , 0x0000   @Mask MIU0_group_2
    WREG    (MS_BUS_RIU_ADDR + (0x1012a6 <<1 )) , 0x0000   @Mask MIU0_group_3

.if ( ENABLE_MIU1 == 1 )
    @ open all MIU1 request mask (All IP can access MIU resource)
    WREG    (MS_BUS_RIU_ADDR + (0x100646 <<1 )) , 0x0000   @Mask MIU0_group_0
    WREG    (MS_BUS_RIU_ADDR + (0x100666 <<1 )) , 0x0000   @Mask MIU0_group_1
    WREG    (MS_BUS_RIU_ADDR + (0x100686 <<1 )) , 0x0000   @Mask MIU0_group_2
    WREG    (MS_BUS_RIU_ADDR + (0x1006a6 <<1 )) , 0x0000   @Mask MIU0_group_3

    @ all MIU1 IP select MIU0 in bringup
    WREG    (MS_BUS_RIU_ADDR + (0x1006f0 <<1 )), 0x0000
    WREG    (MS_BUS_RIU_ADDR + (0x1006f2 <<1 )), 0x0000
    WREG    (MS_BUS_RIU_ADDR + (0x1006f4 <<1 )), 0x0000
    WREG    (MS_BUS_RIU_ADDR + (0x1006f6 <<1 )), 0x0000
.endif

    WREG    (MS_BUS_RIU_ADDR + (0x10121e <<1 )), 0x1808   @ SW initial done and turn on arbitor
    WREG    (MS_BUS_RIU_ADDR + (0x1012fc <<1 )), 0x8400
.if ( ENABLE_MIU1 == 1 )
    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )), 0x1808   @ SW initial done and turn on arbitor
    WREG    (MS_BUS_RIU_ADDR + (0x1006fc <<1 )), 0x8400
.endif


#if (ENABLE_MSTAR_EDISON_MMAP_512MB_256MB == 1)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x8000
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x7000
#elif (ENABLE_MSTAR_EDISON_MMAP_512MB_512MB == 1)
    WREG    (MS_BUS_RIU_ADDR + (0x1012C0 <<1 )), 0x8000
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x8000
#else
    #error "Incorrect MMAP setting in Edison!!"
#endif

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

	mov         lr, r13
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
.if ( ENABLE_MIU1 == 1 )
    RREG        r8, (MS_BUS_RIU_ADDR + (0x3DB8 << 1))
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x110DEC << 1))
    RREG        r8, (MS_BUS_RIU_ADDR + (0x3DBA << 1))
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x110DEE << 1))
.endif
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
    WREG        (MS_BUS_RIU_ADDR + (0x101206 << 1)), 0x1460 @//Bit[12]reg_cke_always_on
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x202F

.if ( ENABLE_MIU1 == 1 )
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
    WREG        (MS_BUS_RIU_ADDR + (0x100606 << 1)), 0x1460 @//Bit[12]reg_cke_always_on
    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x202F
.endif
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
.if ( ENABLE_MIU1 == 1 )
    RREG        r8, (MS_BUS_RIU_ADDR + (0x100602 << 1))
    bic    r8, r8, #0xf000
    REG_C2M     r8, (MS_BUS_RIU_ADDR + (0x100602 << 1))
.endif
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
    WREG        (MS_BUS_RIU_ADDR + (0x101206 << 1)), 0x1460 @//trig refresh
@//    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x0000
@//    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0x0000 @//Bit[12]reg_cke_always_on
@//    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0x0000 @//reg_mrx
@//    WREG        (MS_BUS_RIU_ADDR + (0x1012A6 << 1)), 0x0000 @//Bit[05]reg_auto_ref_off
    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x7ffe
    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0xffff @//Bit[12]reg_cke_always_on
    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0xffff @//reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x1012A6 << 1)), 0xffff @//Bit[05]reg_auto_ref_off

.if ( ENABLE_MIU1 == 1 )
    @// [DDR3][enter] <MIU1>
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0xFFFE
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x022F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x032F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x002F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x000F
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x001F
    WREG        (MS_BUS_RIU_ADDR + (0x100606 << 1)), 0x1460 @//0x342b @//trig refresh
@//    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x0000
@//    WREG        (MS_BUS_RIU_ADDR + (0x100666 << 1)), 0x0000 @//Bit[12]reg_cke_always_on
@//    WREG        (MS_BUS_RIU_ADDR + (0x100686 << 1)), 0x0000 @//reg_mrx
@//    WREG        (MS_BUS_RIU_ADDR + (0x1006A6 << 1)), 0x0000 @//Bit[05]reg_auto_ref_off
    WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x7ffe
    WREG        (MS_BUS_RIU_ADDR + (0x100666 << 1)), 0xffff @//Bit[12]reg_cke_always_on
    WREG        (MS_BUS_RIU_ADDR + (0x100686 << 1)), 0xffff @//reg_mrx
    WREG        (MS_BUS_RIU_ADDR + (0x1006A6 << 1)), 0xffff @//Bit[05]reg_auto_ref_off
.endif
    bx          lr

@//-------------------------------------------------------------------------------------------------
@// Push_Dram_STR
@// @param  None
@// @return None
@// @note   Push_Dram_STR
@//-------------------------------------------------------------------------------------------------
Push_Dram_STR:

#if 0
#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00e5 @// reg_en_mask @//Table: MIU0_DDR_Init_STR
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00a5 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00e5 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00a5
#elif(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00e7 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00a7 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00e7 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e <<1 )), 0x00a7
#endif

.if ( ENABLE_MIU1 == 1 )    
#if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
    WREG        (MS_BUS_RIU_ADDR + (0x110d8e <<1 )), 0x00e5 @// reg_en_mask @//Table: MIU1_DDR_Init_STR
    WREG        (MS_BUS_RIU_ADDR + (0x110d8e <<1 )), 0x00a5 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d8e <<1 )), 0x00e5 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d8e <<1 )), 0x00a5
#elif(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
    WREG        (MS_BUS_RIU_ADDR + (0x110d8e <<1 )), 0x00e7 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d8e <<1 )), 0x00a7 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d8e <<1 )), 0x00e7 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x110d8e <<1 )), 0x00a7
#endif
.endif
#endif

    WREG        (MS_BUS_RIU_ADDR + (0x1012e4 <<1 )), 0x0004 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0100 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0101

    DELAYUS     1                                         @//delay 200us
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0100 @// reg_en_mask
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0101
    DELAYUS     1                                         @//delay 200us
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )), 0x0000

.if ( ENABLE_MIU1 == 1 )
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
.endif
    bx          lr

@//-------------------------------------------------------------------------------------------------
@// Miu_init_priority_str
@// @param  None
@// @return None
@// @note   Miu_init_priority_str
@//-------------------------------------------------------------------------------------------------
#if 0
Miu_init_priority_str:

    @ MIU0: generate set priority pulse for "fix priority"

    RREG    r0, 0x1F202480
    and     r0, r0, #1
    cmp     r0, #1
    beq     miu0_rq0_skip_str

    RREG    r0, 0x1F202480
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F202480
    str     r0, [r1]

    RREG    r0, 0x1F202480
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F202480
    str     r0, [r1]

miu0_rq0_skip_str:

    RREG    r0, 0x1F2024C0
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu0_rq1_skip_str

    RREG    r0, 0x1F2024C0
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F2024C0
    str     r0, [r1]

    RREG    r0, 0x1F2024C0
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F2024C0
    str     r0, [r1]

miu0_rq1_skip_str:

    RREG    r0, 0x1F202500
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu0_rq2_skip_str

    RREG    r0, 0x1F202500
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F202500
    str     r0, [r1]

    RREG    r0, 0x1F202500
    bic     r0, r0, #0002
    ldr     r1, =0x1F202500
    str     r0, [r1]

miu0_rq2_skip_str:

    RREG    r0, 0x1F202540
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu0_rq3_skip_str

    RREG    r0, 0x1F202540
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F202540
    str     r0, [r1]

    RREG    r0, 0x1F202540
    bic     r0, r0, #0002
    ldr     r1, =0x1F202540
    str     r0, [r1]

miu0_rq3_skip_str:

    @ MIU1: generate set priority pulse for "fix priority"

    RREG    r0, 0x1F200C80
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu1_rq0_skip_str

    RREG    r0, 0x1F200C80
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F200C80
    str     r0, [r1]

    RREG    r0, 0x1F200C80
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F200C80
    str     r0, [r1]

miu1_rq0_skip_str:

    RREG    r0, 0x1F200CC0
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu1_rq1_skip_str

    RREG    r0, 0x1F200CC0
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F200CC0
    str     r0, [r1]

    RREG    r0, 0x1F200CC0
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F200CC0
    str     r0, [r1]

miu1_rq1_skip_str:

    RREG    r0, 0x1F200D00
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu1_rq2_skip_str

    RREG    r0, 0x1F200D00
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F200D00
    str     r0, [r1]

    RREG    r0, 0x1F200D00
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F200D00
    str     r0, [r1]

miu1_rq2_skip_str:

    RREG    r0, 0x1F200D40
    and     r0, r0, #0x0001
    cmp     r0, #1
    beq     miu1_rq3_skip_str

    RREG    r0, 0x1F200D40
    orr     r0, r0, #0x0002
    ldr     r1, =0x1F200D40
    str     r0, [r1]

    RREG    r0, 0x1F200D40
    bic     r0, r0, #0x0002
    ldr     r1, =0x1F200D40
    str     r0, [r1]

miu1_rq3_skip_str:
	bx          lr
#endif
@//-------------------------------------------------------------------------------------------------
@// BootRom_StrEntry
@// @param  None
@// @return None
@// @note   None
@//-------------------------------------------------------------------------------------------------
#ifdef CONFIG_MSTAR_STR_ENABLE
    .global     BootRom_StrEntry
BootRom_StrEntry:

    mov         r13, lr

.if (MSTAR_STR_SBOOT_RESUME == 1)
    bl          read_wkup_pmu
    bl          put_reg_val

    is_slept
    bne         1f

    set_wakeup
    b           2f

1:
    eor         r0, r0, r0
    bl          write_wkup_pmu

2:
    is_wakeup
    bne         3f
    PUTK        'W'
    PUTK        'K'
    PUTK        'P'
    bl          read_wkup_pmu

    bic         r0, r0, #WAKEUP_FLAG_MASK
    mov         r0, r0, lsl #16             @// wake up info addr
    ldmia       r0, {r1-r2}
    ldr         r0, =MSTAR_SLEEP_MAGIC
    cmp         r1, r0
    bne         3f

    PUTK        'J'
    cmp         r2, #0
    beq         3f

    PUTK        'M'
    mov         pc, r2                      @// jump to wakup addr
3:
.endif

    mov         lr, r13
    bx          lr


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
.endif    
#endif

	
    .size       BootRom_InitMiu,.-BootRom_InitMiu
