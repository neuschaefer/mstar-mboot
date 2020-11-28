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

#ifndef _MIUSEL_EINSTEIN3_2MIU_H_
#include "MIUSEL_EINSTEIN3_2MIU.h"
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

#ifdef CONFIG_MSTAR_TITANIA_BD_FPGA
    WREG        (MS_BUS_RIU_ADDR + (0x101202 << 1)), 0x0854
    WREG        (MS_BUS_RIU_ADDR + (0x101204 << 1)), 0x01c5
    WREG        (MS_BUS_RIU_ADDR + (0x101206 << 1)), 0x0120
    WREG        (MS_BUS_RIU_ADDR + (0x101208 << 1)), 0x0833
    WREG        (MS_BUS_RIU_ADDR + (0x10120a << 1)), 0x0c33
    WREG        (MS_BUS_RIU_ADDR + (0x10120c << 1)), 0x7111
    WREG        (MS_BUS_RIU_ADDR + (0x10120e << 1)), 0x100e
    WREG        (MS_BUS_RIU_ADDR + (0x101210 << 1)), 0x0031
    WREG        (MS_BUS_RIU_ADDR + (0x101224 << 1)), 0x000f
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c00
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c01
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c00
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0008
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000c
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000e
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x001f
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c08
    DELAYUS     100000

    WREG        (MS_BUS_RIU_ADDR + (0x100602 << 1)), 0x0854
    WREG        (MS_BUS_RIU_ADDR + (0x100604 << 1)), 0x01c5
    WREG        (MS_BUS_RIU_ADDR + (0x100606 << 1)), 0x0120
    WREG        (MS_BUS_RIU_ADDR + (0x100608 << 1)), 0x0833
    WREG        (MS_BUS_RIU_ADDR + (0x10060a << 1)), 0x0c33
    WREG        (MS_BUS_RIU_ADDR + (0x10060c << 1)), 0x7111
    WREG        (MS_BUS_RIU_ADDR + (0x10060e << 1)), 0x100e
    WREG        (MS_BUS_RIU_ADDR + (0x100610 << 1)), 0x0031
    WREG        (MS_BUS_RIU_ADDR + (0x100624 << 1)), 0x000f
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0c00
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0c01
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0c00
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0008
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x000c
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x000e
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x001f
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0c08
    DELAYUS     100000

    WREG        (MS_BUS_RIU_ADDR + (0x100602 << 1)), 0x0854
    WREG        (MS_BUS_RIU_ADDR + (0x162002 << 1)), 0x0854
    WREG        (MS_BUS_RIU_ADDR + (0x162004 << 1)), 0x01c5
    WREG        (MS_BUS_RIU_ADDR + (0x162006 << 1)), 0x0120
    WREG        (MS_BUS_RIU_ADDR + (0x162008 << 1)), 0x0833
    WREG        (MS_BUS_RIU_ADDR + (0x16200a << 1)), 0x0c33
    WREG        (MS_BUS_RIU_ADDR + (0x16200c << 1)), 0x7111
    WREG        (MS_BUS_RIU_ADDR + (0x16200e << 1)), 0x100e
    WREG        (MS_BUS_RIU_ADDR + (0x162010 << 1)), 0x0031
    WREG        (MS_BUS_RIU_ADDR + (0x162024 << 1)), 0x000f
    WREG        (MS_BUS_RIU_ADDR + (0x16201e << 1)), 0x0c00
    WREG        (MS_BUS_RIU_ADDR + (0x16201e << 1)), 0x0c01
    WREG        (MS_BUS_RIU_ADDR + (0x16201e << 1)), 0x0c00
    WREG        (MS_BUS_RIU_ADDR + (0x162000 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x162000 << 1)), 0x0008
    WREG        (MS_BUS_RIU_ADDR + (0x162000 << 1)), 0x000c
    WREG        (MS_BUS_RIU_ADDR + (0x162000 << 1)), 0x000e
    WREG        (MS_BUS_RIU_ADDR + (0x162000 << 1)), 0x001f
    WREG        (MS_BUS_RIU_ADDR + (0x16201e << 1)), 0x0c08
    DELAYUS     100000

    WREG        (MS_BUS_RIU_ADDR + (0x162402 << 1)), 0x0854
    WREG        (MS_BUS_RIU_ADDR + (0x162404 << 1)), 0x01c5
    WREG        (MS_BUS_RIU_ADDR + (0x162406 << 1)), 0x0120
    WREG        (MS_BUS_RIU_ADDR + (0x162408 << 1)), 0x0833
    WREG        (MS_BUS_RIU_ADDR + (0x16240a << 1)), 0x0c33
    WREG        (MS_BUS_RIU_ADDR + (0x16240c << 1)), 0x7111
    WREG        (MS_BUS_RIU_ADDR + (0x16240e << 1)), 0x100e
    WREG        (MS_BUS_RIU_ADDR + (0x162410 << 1)), 0x0031
    WREG        (MS_BUS_RIU_ADDR + (0x162424 << 1)), 0x000f
    WREG        (MS_BUS_RIU_ADDR + (0x16241e << 1)), 0x0c00
    WREG        (MS_BUS_RIU_ADDR + (0x16241e << 1)), 0x0c01
    WREG        (MS_BUS_RIU_ADDR + (0x16241e << 1)), 0x0c00
    WREG        (MS_BUS_RIU_ADDR + (0x162400 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x162400 << 1)), 0x0008
    WREG        (MS_BUS_RIU_ADDR + (0x162400 << 1)), 0x000c
    WREG        (MS_BUS_RIU_ADDR + (0x162400 << 1)), 0x000e
    WREG        (MS_BUS_RIU_ADDR + (0x162400 << 1)), 0x001f
    WREG        (MS_BUS_RIU_ADDR + (0x16241e << 1)), 0x0c08
    DELAYUS     100000

#else

    ldr         r0, =MIU_PreInit
    bl          MDrv_WriteRegTbl32

#if !defined(CONFIG_MIU0_DRAM_NONE)
    ldr         r0, =MIU0_DDR_Init
    bl          MDrv_WriteRegTbl32

    DELAYUS     1000
    WREG        (MS_BUS_RIU_ADDR + (0x110d60 << 1)), 0x00C0
    WREG        (MS_BUS_RIU_ADDR + (0x110d60 << 1)), 0x33C8

    DELAYUS     5000

    @//Enable MIU0
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0c01
    DELAYUS     1
    WREG        (MS_BUS_RIU_ADDR + (0x10121e << 1)), 0x0C08

#if (ENABLE_MSTAR_BD_MST181B_D01A_S) || (ENABLE_MSTAR_BD_MST181D_D01A_S) || (ENABLE_MSTAR_BD_MST051B_10ANV) || (ENABLE_MSTAR_BD_MST181B_D01A_S_CASHMERE)
    WREG        (MS_BUS_RIU_ADDR + (0x110d00 << 1)), 0x0001  //reg_pkg_sel		1	: [0]
#else
    WREG        (MS_BUS_RIU_ADDR + (0x110d00 << 1)), 0x0000  //reg_pkg_sel		1	: [0]
#endif
    WREG        (MS_BUS_RIU_ADDR + (0x110d02 << 1)), 0xAAAA  //reg_cko_state		cc	: [7:0]
    WREG        (MS_BUS_RIU_ADDR + (0x110d18 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x101202 << 1)), 0x03A7

    DELAYUS     200                                         @//delay 200us

#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)

    ldr         r0, =MIU1_DDR_Init
    bl          MDrv_WriteRegTbl32

    DELAYUS     1000
    WREG        (MS_BUS_RIU_ADDR + (0x161660 << 1)), 0x00C0
    WREG        (MS_BUS_RIU_ADDR + (0x161660 << 1)), 0x33C8

    DELAYUS     5000

    @//Enable MIU1
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0c01
    DELAYUS     1
    WREG        (MS_BUS_RIU_ADDR + (0x10061e << 1)), 0x0C08

#if (ENABLE_MSTAR_BD_MST181B_D01A_S) || (ENABLE_MSTAR_BD_MST181D_D01A_S) || (ENABLE_MSTAR_BD_MST051B_10ANV) || (ENABLE_MSTAR_BD_MST181B_D01A_S_CASHMERE)
    WREG        (MS_BUS_RIU_ADDR + (0x161600 << 1)), 0x0001  //reg_pkg_sel		1	: [0]
#else
    WREG        (MS_BUS_RIU_ADDR + (0x161600 << 1)), 0x0000  //reg_pkg_sel		1	: [0]
#endif
    WREG        (MS_BUS_RIU_ADDR + (0x161602 << 1)), 0xAAAA  //reg_cko_state		cc	: [7:0]
    WREG        (MS_BUS_RIU_ADDR + (0x161618 << 1)), 0x0000

#if (ENABLE_MSTAR_BD_MST181A_D01A_S)
    WREG        (MS_BUS_RIU_ADDR + (0x100602 << 1)), 0x03A3
#elif (ENABLE_MSTAR_BD_MST181C_D01A_S)
    WREG        (MS_BUS_RIU_ADDR + (0x100602 << 1)), 0x03A7
#elif (ENABLE_MSTAR_BD_MST181B_D01A_S) || (ENABLE_MSTAR_BD_MST181D_D01A_S) || (ENABLE_MSTAR_BD_MST051B_10ANV) || (ENABLE_MSTAR_BD_MST181B_D01A_S_CASHMERE)
    WREG        (MS_BUS_RIU_ADDR + (0x100602 << 1)), 0x03A7
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

#if !defined(CONFIG_MIU0_DRAM_NONE)
    @//rx enable
    WREG        (MS_BUS_RIU_ADDR + (0x161608 << 1)), 0x003f

    @//MIU0 INIT Cycle
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0000 @//hold miu_0
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x0008 @//DRAM reset
    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000c @//DRAM reset+CS

    DELAYUS     1000                                        @//delay 1000us

    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x000e @//DRAM reset+CS+CKE

    DELAYUS     2000                                        @//delay 2000us

    WREG        (MS_BUS_RIU_ADDR + (0x101200 << 1)), 0x001f @//DRAM reset+CS+CKE+auto cycle+ODE

    DELAYUS     200                                         @//delay 200us

    WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x1012A6 << 1)), 0x0000

#if (ENABLE_MSTAR_BD_MST181A_D01A_S)
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e << 1)), 0x00ED
#else
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e << 1)), 0x00EF
#endif
    WREG        (MS_BUS_RIU_ADDR + (0x110d1e << 1)), 0x0007

    WREG        (MS_BUS_RIU_ADDR + (0x1012E4 << 1)), 0x0001
    WREG        (MS_BUS_RIU_ADDR + (0x1012E0 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x1012E0 << 1)), 0x0200
    WREG        (MS_BUS_RIU_ADDR + (0x1012E0 << 1)), 0x0201
#if (ENABLE_MSTAR_BD_MST181C_D01A_S) || (ENABLE_MSTAR_BD_MST181A_D01A_S)
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e << 1)), 0x00AF
#else
    WREG        (MS_BUS_RIU_ADDR + (0x110d0e << 1)), 0x00AD
#endif
    WREG        (MS_BUS_RIU_ADDR + (0x110d1e << 1)), 0x0003

    WREG        (MS_BUS_RIU_ADDR + (0x1012E0 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x1012E0 << 1)), 0x0200
    WREG        (MS_BUS_RIU_ADDR + (0x1012E0 << 1)), 0x0201
    WREG        (MS_BUS_RIU_ADDR + (0x1012E0 << 1)), 0x0000

	@ when disabling icache/dcache/L2, we need this hardware patch
	@ bank 0x1018, reg 0x45, set bit 4 & bit 5
    WREG        (MS_BUS_RIU_ADDR + (0x10188A << 1)), 0x0031

CheckMiu0Init:
    RREG        r1, (MS_BUS_RIU_ADDR + (0x101200 << 1))
    and         r1, r1, #0x8000
    cmp         r1, #0
    beq         CheckMiu0Init

#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)

    @//rx enable
    WREG        (MS_BUS_RIU_ADDR + (0x110d08 << 1)), 0x003f

    @//MIU1 INIT Cycle
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0000 @//hold miu_0
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x0008 @//DRAM reset
    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x000c @//DRAM reset+CS

    DELAYUS     1000                                        @//delay 1000us

    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x000e @//DRAM reset+CS+CKE

    DELAYUS     2000                                        @//delay 2000us

    WREG        (MS_BUS_RIU_ADDR + (0x100600 << 1)), 0x001f @//DRAM reset+CS+CKE+auto cycle+ODE

    DELAYUS     200                                         @//delay 200us

#if (ENABLE_MSTAR_BD_MST181A_D01A_S)
    WREG        (MS_BUS_RIU_ADDR + (0x16160e << 1)), 0x00EF
#else
    WREG        (MS_BUS_RIU_ADDR + (0x16160e << 1)), 0x00ED
#endif
    WREG        (MS_BUS_RIU_ADDR + (0x16161e << 1)), 0x0007

    WREG        (MS_BUS_RIU_ADDR + (0x1012F0 << 1)), 0x8000

    WREG        (MS_BUS_RIU_ADDR + (0x1012E4 << 1)), 0x0001
    WREG        (MS_BUS_RIU_ADDR + (0x1012E0 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x1012E0 << 1)), 0x0200
    WREG        (MS_BUS_RIU_ADDR + (0x1012E0 << 1)), 0x0201
#if (ENABLE_MSTAR_BD_MST181C_D01A_S) || (ENABLE_MSTAR_BD_MST181A_D01A_S)
    WREG        (MS_BUS_RIU_ADDR + (0x16160e << 1)), 0x00AF
#else
    WREG        (MS_BUS_RIU_ADDR + (0x16160e << 1)), 0x00AD
#endif
    WREG        (MS_BUS_RIU_ADDR + (0x16161e << 1)), 0x0003

    WREG        (MS_BUS_RIU_ADDR + (0x1012E0 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x1012E0 << 1)), 0x0200
    WREG        (MS_BUS_RIU_ADDR + (0x1012E0 << 1)), 0x0201
    WREG        (MS_BUS_RIU_ADDR + (0x1012E0 << 1)), 0x0000

    WREG        (MS_BUS_RIU_ADDR + (0x1012F0 << 1)), 0x0000
CheckMiu1Init:
    RREG        r1, (MS_BUS_RIU_ADDR + (0x100600 << 1))
    and         r1, r1, #0x8000
    cmp         r1, #0
    beq         CheckMiu1Init

#endif

#if 0
    @//set MIU BIST Base/Length/data/Mode
    WREG        (MS_BUS_RIU_ADDR + (0x1012FE << 1)), 0x00C9
    WREG        (MS_BUS_RIU_ADDR + (0x1012E2 << 1)), 0x7000
    WREG        (MS_BUS_RIU_ADDR + (0x1012E4 << 1)), 0x8001
    WREG        (MS_BUS_RIU_ADDR + (0x1012E6 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x1012E8 << 1)), 0x00FF
    WREG        (MS_BUS_RIU_ADDR + (0x1012E0 << 1)), 0x0084

#if !defined(CONFIG_MIU0_DRAM_NONE)
    WREG        (MS_BUS_RIU_ADDR + (0x110DA0 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x110DA2 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x110DA4 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x110DA6 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x110DA8 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x110DAA << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x110DAC << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x110DAE << 1)), 0x0000

    WREG        (MS_BUS_RIU_ADDR + (0x161578 << 1)), 0x0012
    WREG        (MS_BUS_RIU_ADDR + (0x110D40 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x110D42 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x110D44 << 1)), 0x000F
    WREG        (MS_BUS_RIU_ADDR + (0x161574 << 1)), 0x0863
    WREG        (MS_BUS_RIU_ADDR + (0x161576 << 1)), 0x000F
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    WREG        (MS_BUS_RIU_ADDR + (0x1616A0 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x1616A2 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x1616A4 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x1616A6 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x1616A8 << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x1616AA << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x1616AC << 1)), 0x0000
    WREG        (MS_BUS_RIU_ADDR + (0x1616AE << 1)), 0x0000

    WREG        (MS_BUS_RIU_ADDR + (0x1615F8 << 1)), 0x0012
    WREG        (MS_BUS_RIU_ADDR + (0x161640 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x161642 << 1)), 0xFFFF
    WREG        (MS_BUS_RIU_ADDR + (0x161644 << 1)), 0x000F
    WREG        (MS_BUS_RIU_ADDR + (0x1615F4 << 1)), 0x0863
    WREG        (MS_BUS_RIU_ADDR + (0x1615F6 << 1)), 0x000F
#endif
    WREG        (MS_BUS_RIU_ADDR + (0x110D60 << 1)), 0x33C8
    WREG        (MS_BUS_RIU_ADDR + (0x16157C << 1)), 0x8000

    WREG        (MS_BUS_RIU_ADDR + (0x161660 << 1)), 0x33C8
    WREG        (MS_BUS_RIU_ADDR + (0x1615FC << 1)), 0x8000

    WREG        (MS_BUS_RIU_ADDR + (0x161578 << 1)), 0x0016
    WREG        (MS_BUS_RIU_ADDR + (0x161578 << 1)), 0x0012
    WREG        (MS_BUS_RIU_ADDR + (0x1615F8 << 1)), 0x0013
    WREG        (MS_BUS_RIU_ADDR + (0x161578 << 1)), 0x0013

    DELAYUS     1000

#if !defined(CONFIG_MIU0_DRAM_NONE)
    WREG        (MS_BUS_RIU_ADDR + (0x110DC0 << 1)), 0x0000
    DELAYUS     30000
    RREG        r1, (MS_BUS_RIU_ADDR + (0x110DC0 << 1))
    and         r1,r1,#2032
    mov         r1,r1,LSR#4
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x103390 << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x110DC0 << 1)), 0x0001
    DELAYUS     30000
    RREG        r1, (MS_BUS_RIU_ADDR + (0x110DC0 << 1))
    RREG        r2, (MS_BUS_RIU_ADDR + (0x103390 << 1))
    and         r1,r1,#2032
    mov         r1,r1,LSL#4
    orr         r1, r1, r2
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x103390 << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x110DC0 << 1)), 0x0002
    DELAYUS     30000
    RREG        r1, (MS_BUS_RIU_ADDR + (0x110DC0 << 1))
    and         r1,r1,#2032
    mov         r1,r1,LSR#4
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x1033a0 << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x110DC0 << 1)), 0x0003
    DELAYUS     30000
    RREG        r1, (MS_BUS_RIU_ADDR + (0x110DC0 << 1))
    RREG        r2, (MS_BUS_RIU_ADDR + (0x1033a0 << 1))
    and         r1,r1,#2032
    mov         r1,r1,LSL#4
    orr         r1, r1, r2
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x1033a0 << 1))
#endif


#if !defined(CONFIG_MIU1_DRAM_NONE)
    WREG        (MS_BUS_RIU_ADDR + (0x1616C0 << 1)), 0x0000
    DELAYUS     30000
    RREG        r1, (MS_BUS_RIU_ADDR + (0x1616C0 << 1))
    and         r1,r1,#2032
    mov         r1,r1,LSR#4
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x1033b0 << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x1616C0 << 1)), 0x0001
    DELAYUS     30000
    RREG        r1, (MS_BUS_RIU_ADDR + (0x1616C0 << 1))
    RREG        r2, (MS_BUS_RIU_ADDR + (0x1033b0 << 1))
    and         r1,r1,#2032
    mov         r1,r1,LSL#4
    orr         r1, r1, r2
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x1033b0 << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x1616C0 << 1)), 0x0002
    DELAYUS     30000
    RREG        r1, (MS_BUS_RIU_ADDR + (0x1616C0 << 1))
    and         r1,r1,#2032
    mov         r1,r1,LSR#4
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x1033c0 << 1))

    WREG        (MS_BUS_RIU_ADDR + (0x1616C0 << 1)), 0x0003
    DELAYUS     30000
    RREG        r1, (MS_BUS_RIU_ADDR + (0x1616C0 << 1))
    RREG        r2, (MS_BUS_RIU_ADDR + (0x1033C0 << 1))
    and         r1,r1,#2032
    mov         r1,r1,LSL#4
    orr         r1, r1, r2
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x1033c0 << 1))
#endif

    WREG        (MS_BUS_RIU_ADDR + (0x1615F8 << 1)), 0x0012
    WREG        (MS_BUS_RIU_ADDR + (0x161578 << 1)), 0x0012

#if (ENABLE_MSTAR_BD_MST181A_D01A_S)
    WREG        (MS_BUS_RIU_ADDR + (0x110da0 << 1)), 0x3706
    WREG        (MS_BUS_RIU_ADDR + (0x110da2 << 1)), 0x1425
    WREG        (MS_BUS_RIU_ADDR + (0x110da4 << 1)), 0x2143
    WREG        (MS_BUS_RIU_ADDR + (0x110da6 << 1)), 0x3152

    WREG        (MS_BUS_RIU_ADDR + (0x110da8 << 1)), 0x3402
    WREG        (MS_BUS_RIU_ADDR + (0x110daa << 1)), 0x1312
    WREG        (MS_BUS_RIU_ADDR + (0x110dac << 1)), 0x3341
    WREG        (MS_BUS_RIU_ADDR + (0x110dae << 1)), 0x2030

    WREG        (MS_BUS_RIU_ADDR + (0x1616a0 << 1)), 0x5401
    WREG        (MS_BUS_RIU_ADDR + (0x1616a2 << 1)), 0x2405
    WREG        (MS_BUS_RIU_ADDR + (0x1616a4 << 1)), 0x7586
    WREG        (MS_BUS_RIU_ADDR + (0x1616a6 << 1)), 0x7396

    WREG        (MS_BUS_RIU_ADDR + (0x1616a8 << 1)), 0x1111
    WREG        (MS_BUS_RIU_ADDR + (0x1616aa << 1)), 0x1111
    WREG        (MS_BUS_RIU_ADDR + (0x1616ac << 1)), 0x1111
    WREG        (MS_BUS_RIU_ADDR + (0x1616ae << 1)), 0x1111

#elif (ENABLE_MSTAR_BD_MST181B_D01A_S) || (ENABLE_MSTAR_BD_MST181D_D01A_S) || (ENABLE_MSTAR_BD_MST051B_10ANV) || (ENABLE_MSTAR_BD_MST181B_D01A_S_CASHMERE)
    WREG        (MS_BUS_RIU_ADDR + (0x110da0 << 1)), 0x3704
    WREG        (MS_BUS_RIU_ADDR + (0x110da2 << 1)), 0x5859
    WREG        (MS_BUS_RIU_ADDR + (0x110da4 << 1)), 0xA246
    WREG        (MS_BUS_RIU_ADDR + (0x110da6 << 1)), 0x5253

    WREG        (MS_BUS_RIU_ADDR + (0x110da8 << 1)), 0x2705
    WREG        (MS_BUS_RIU_ADDR + (0x110daa << 1)), 0x5647
    WREG        (MS_BUS_RIU_ADDR + (0x110dac << 1)), 0x6355
    WREG        (MS_BUS_RIU_ADDR + (0x110dae << 1)), 0x4253

    WREG        (MS_BUS_RIU_ADDR + (0x1616a0 << 1)), 0x4604
    WREG        (MS_BUS_RIU_ADDR + (0x1616a2 << 1)), 0x6658
    WREG        (MS_BUS_RIU_ADDR + (0x1616a4 << 1)), 0xB698
    WREG        (MS_BUS_RIU_ADDR + (0x1616a6 << 1)), 0x9397

    WREG        (MS_BUS_RIU_ADDR + (0x1616a8 << 1)), 0x6704
    WREG        (MS_BUS_RIU_ADDR + (0x1616aa << 1)), 0x5566
    WREG        (MS_BUS_RIU_ADDR + (0x1616ac << 1)), 0x8567
    WREG        (MS_BUS_RIU_ADDR + (0x1616ae << 1)), 0x9596

#elif (ENABLE_MSTAR_BD_MST181C_D01A_S)
    WREG        (MS_BUS_RIU_ADDR + (0x110da0 << 1)), 0x5524
    WREG        (MS_BUS_RIU_ADDR + (0x110da2 << 1)), 0x3424
    WREG        (MS_BUS_RIU_ADDR + (0x110da4 << 1)), 0x4140
    WREG        (MS_BUS_RIU_ADDR + (0x110da6 << 1)), 0x4152

    WREG        (MS_BUS_RIU_ADDR + (0x110da8 << 1)), 0x5425
    WREG        (MS_BUS_RIU_ADDR + (0x110daa << 1)), 0x4233
    WREG        (MS_BUS_RIU_ADDR + (0x110dac << 1)), 0x2231
    WREG        (MS_BUS_RIU_ADDR + (0x110dae << 1)), 0x2042

    WREG        (MS_BUS_RIU_ADDR + (0x1616a0 << 1)), 0x4402
    WREG        (MS_BUS_RIU_ADDR + (0x1616a2 << 1)), 0x2204
    WREG        (MS_BUS_RIU_ADDR + (0x1616a4 << 1)), 0x6455
    WREG        (MS_BUS_RIU_ADDR + (0x1616a6 << 1)), 0x5262

    WREG        (MS_BUS_RIU_ADDR + (0x1616a8 << 1)), 0x6400
    WREG        (MS_BUS_RIU_ADDR + (0x1616aa << 1)), 0x2223
    WREG        (MS_BUS_RIU_ADDR + (0x1616ac << 1)), 0x7576
    WREG        (MS_BUS_RIU_ADDR + (0x1616ae << 1)), 0x5477

#endif

    WREG        (MS_BUS_RIU_ADDR + (0x110d70 << 1)), 0x0000
    RREG        r1, (MS_BUS_RIU_ADDR + (0x103390 << 1))
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x110d6c << 1))
    RREG        r1, (MS_BUS_RIU_ADDR + (0x1033a0 << 1))
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x110d6E << 1))
    WREG        (MS_BUS_RIU_ADDR + (0x110d70 << 1)), 0x0800

    WREG        (MS_BUS_RIU_ADDR + (0x161670 << 1)), 0x0000
    RREG        r1, (MS_BUS_RIU_ADDR + (0x1033b0 << 1))
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x16166c << 1))
    RREG        r1, (MS_BUS_RIU_ADDR + (0x1033c0 << 1))
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x16166E << 1))
    WREG        (MS_BUS_RIU_ADDR + (0x161670 << 1)), 0x0800

#else
#if (ENABLE_MSTAR_BD_MST181A_D01A_S)
    WREG        (MS_BUS_RIU_ADDR + (0x110d70 << 1)), 0x0000
    RREG        r1, (MS_BUS_RIU_ADDR + (0x110D66 << 1))
    mov         r1,r1,LSR#1
    add         r2,r1, #1
    mov         r3,r2,LSL#8
    orr         r2,r2,r3

    REG_C2M     r2, (MS_BUS_RIU_ADDR + (0x110d6c << 1))
    mov         r3,r1,LSL#8
    orr         r3,r3,r1
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x110d6E << 1))
    WREG        (MS_BUS_RIU_ADDR + (0x110d70 << 1)), 0x0800

    WREG        (MS_BUS_RIU_ADDR + (0x161670 << 1)), 0x0000
    RREG        r1, (MS_BUS_RIU_ADDR + (0x161666 << 1))
    mov         r1,r1,LSR#1
    add         r2,r1, #2
    mov         r3,r2,LSL#8
    orr         r2,r2,r3

    REG_C2M     r2, (MS_BUS_RIU_ADDR + (0x16166c << 1))
    add         r1,r1, #3
    mov         r3,r1,LSL#8
    orr         r3,r3,r1
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x16166E << 1))
    WREG        (MS_BUS_RIU_ADDR + (0x161670 << 1)), 0x0800

#elif (ENABLE_MSTAR_BD_MST181B_D01A_S) || (ENABLE_MSTAR_BD_MST051B_10ANV) || (ENABLE_MSTAR_BD_MST181B_D01A_S_CASHMERE)
    WREG        (MS_BUS_RIU_ADDR + (0x110d70 << 1)), 0x0000
    RREG        r1, (MS_BUS_RIU_ADDR + (0x110D66 << 1))
    mov         r1,r1,LSR#1
    add         r2,r1, #8
    mov         r3,r2,LSL#8
    orr         r2,r2,r3

    REG_C2M     r2, (MS_BUS_RIU_ADDR + (0x110d6c << 1))
    add         r1,r1, #6
    mov         r3,r1,LSL#8
    orr         r3,r3,r1
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x110d6E << 1))
    WREG        (MS_BUS_RIU_ADDR + (0x110d70 << 1)), 0x0800

    WREG        (MS_BUS_RIU_ADDR + (0x161670 << 1)), 0x0000
    RREG        r1, (MS_BUS_RIU_ADDR + (0x161666 << 1))
    mov         r1,r1,LSR#1
    add         r2,r1, #9
    mov         r3,r2,LSL#8
    orr         r2,r2,r3

    REG_C2M     r2, (MS_BUS_RIU_ADDR + (0x16166c << 1))
    add         r1,r1, #9
    mov         r3,r1,LSL#8
    orr         r3,r3,r1
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x16166E << 1))
    WREG        (MS_BUS_RIU_ADDR + (0x161670 << 1)), 0x0800
#elif (ENABLE_MSTAR_BD_MST181C_D01A_S)
    WREG        (MS_BUS_RIU_ADDR + (0x110d70 << 1)), 0x0000
    RREG        r1, (MS_BUS_RIU_ADDR + (0x110D66 << 1))
    mov         r1,r1,LSR#1
    add         r2,r1, #1
    mov         r3,r2,LSL#8
    orr         r2,r2,r3

    REG_C2M     r2, (MS_BUS_RIU_ADDR + (0x110d6c << 1))
    mov         r3,r1,LSL#8
    orr         r3,r3,r1
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x110d6E << 1))
    WREG        (MS_BUS_RIU_ADDR + (0x110d70 << 1)), 0x0800

    WREG        (MS_BUS_RIU_ADDR + (0x161670 << 1)), 0x0000
    RREG        r1, (MS_BUS_RIU_ADDR + (0x161666 << 1))
    mov         r1,r1,LSR#1
    add         r2,r1, #2
    mov         r3,r2,LSL#8
    orr         r2,r2,r3

    REG_C2M     r2, (MS_BUS_RIU_ADDR + (0x16166c << 1))
    add         r1,r1, #3
    mov         r3,r1,LSL#8
    orr         r3,r3,r1
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x16166E << 1))
    WREG        (MS_BUS_RIU_ADDR + (0x161670 << 1)), 0x0800
#elif (ENABLE_MSTAR_BD_MST181D_D01A_S)
    WREG        (MS_BUS_RIU_ADDR + (0x110d70 << 1)), 0x0000
    RREG        r1, (MS_BUS_RIU_ADDR + (0x110D66 << 1))
    mov         r1,r1,LSR#1
    add         r2,r1, #8
    mov         r3,r2,LSL#8
    orr         r2,r2,r3

    REG_C2M     r2, (MS_BUS_RIU_ADDR + (0x110d6c << 1))
    add         r1,r1, #6
    mov         r3,r1,LSL#8
    orr         r3,r3,r1
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x110d6E << 1))
    WREG        (MS_BUS_RIU_ADDR + (0x110d70 << 1)), 0x0800

    WREG        (MS_BUS_RIU_ADDR + (0x161670 << 1)), 0x0000
    RREG        r1, (MS_BUS_RIU_ADDR + (0x161666 << 1))
    mov         r1,r1,LSR#1
    add         r2,r1, #9
    mov         r3,r2,LSL#8
    orr         r2,r2,r3

    REG_C2M     r2, (MS_BUS_RIU_ADDR + (0x16166c << 1))
    add         r1,r1, #9
    mov         r3,r1,LSL#8
    orr         r3,r3,r1
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x16166E << 1))
    WREG        (MS_BUS_RIU_ADDR + (0x161670 << 1)), 0x0800
#endif
#endif

@// bl          MIU_Init_AnalogResetPatch

@// bl          MIU_Init_Priority

    bl          MIU_Set_Group_Priority


WREG        (MS_BUS_RIU_ADDR + (0x1012FE << 1)), 0x0087
#if !defined(CONFIG_EMMC_BOOT)
#if defined(CONFIG_ENABLE_AUTO_DQS)
#if !defined(CONFIG_MIU0_DRAM_NONE)
@// WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x7FFE @//Mask MIU0_group_0
    bl          Miu0_AutoPhase
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
@// WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x7FFE @//Mask MIU1_group_0
    bl          Miu1_AutoPhase
#endif
#endif
#endif

#if !defined(CONFIG_MIU0_DRAM_NONE)
    @//BIST test
@// WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x7FFE @//Mask MIU0_group_0
    bl          Miu0_BistTest
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
@// WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x7FFE @//Mask MIU1_group_0
    bl          Miu1_BistTest
#endif

    @//Disable BIST
    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r0, [r12, #(0xfe << 1)]     @//RREG        r0, (MS_BUS_RIU_ADDR + (0x1012fe << 1))
    orr         r0, r0, #(0x01 << 11)
    str         r0, [r12, #(0xfe << 1)]     @//REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x1012fe << 1))

    ldr         r0, =MIU_PostInit
    bl          MDrv_WriteRegTbl32

#endif

    mov         lr, r13
    bx          lr

#if 0
@//-------------------------------------------------------------------------------------------------
EnableMiuSsc:
#if !defined(CONFIG_MIU0_DRAM_NONE)
    @// ENABLE MIU_0_SSC
    WREG        (MS_BUS_RIU_ADDR + (0x110d28 << 1)), DDFSTEP    @//DDFSTEP
    WREG        (MS_BUS_RIU_ADDR + (0x110d2A << 1)), DDFSPAN    @//DDFSPAN
    RREG        r1, (MS_BUS_RIU_ADDR + (0x110d28 << 1))         @//ENABLE MIU_SSC
    orr         r1, r1, #0xc000
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x110d28 << 1))
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    @// ENABLE MIU_1_SSC
    WREG        (MS_BUS_RIU_ADDR + (0x110dA8 << 1)), DDFSTEP    @//DDFSTEP
    WREG        (MS_BUS_RIU_ADDR + (0x110dAA << 1)), DDFSPAN    @//DDFSPAN
    RREG        r1, (MS_BUS_RIU_ADDR + (0x110dA8 << 1))         @//ENABLE MIU_SSC
    orr         r1, r1, #0xc000
    REG_C2M     r1, (MS_BUS_RIU_ADDR + (0x110dA8 << 1))
#endif

    bx          lr
#endif

@//-------------------------------------------------------------------------------------------------
@// MIU_Init_AnalogResetPatch
@// @param  None
@// @return None
@// @note   Patch for DDR Analog Reset Issue
@//-------------------------------------------------------------------------------------------------
    .global     MIU_Init_AnalogResetPatch
MIU_Init_AnalogResetPatch:
#if !defined(CONFIG_MIU0_DRAM_NONE)

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

#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)

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

#endif

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
    .global     MIU_Init_Priority
MIU_Init_Priority:
#if !defined(CONFIG_MIU0_DRAM_NONE)
@// MIU0: generate set priority pulse for "fix priority"

    RREG        r3, (MS_BUS_RIU_ADDR + (0x101240 << 1))
    and         r3, r3, #0x0001
    cmp         r3, #0
    beq         miu0_rq0_skip

    RREG        r3, (MS_BUS_RIU_ADDR + (0x101240 << 1))
    orr         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x101240 << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x101240 << 1))
    bic         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x101240 << 1))

miu0_rq0_skip:

    RREG        r3, (MS_BUS_RIU_ADDR + (0x101260 << 1))
    and         r3, r3, #0x0001
    cmp         r3, #1
    beq         miu0_rq1_skip

    RREG        r3, (MS_BUS_RIU_ADDR + (0x101260 << 1))
    orr         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x101260 << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x101260 << 1))
    bic         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x101260 << 1))

miu0_rq1_skip:

    RREG        r3, (MS_BUS_RIU_ADDR + (0x101280 << 1))
    and         r3, r3, #0x0001
    cmp         r3, #1
    beq         miu0_rq2_skip

    RREG        r3, (MS_BUS_RIU_ADDR + (0x101280 << 1))
    orr         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x101280 << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x101280 << 1))
    bic         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x101280 << 1))

miu0_rq2_skip:

    RREG        r3, (MS_BUS_RIU_ADDR + (0x1012A0 << 1))
    and         r3, r3, #0x0001
    cmp         r3, #1
    beq         miu0_rq3_skip

    RREG        r3, (MS_BUS_RIU_ADDR + (0x1012A0 << 1))
    orr         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012A0 << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x1012A0 << 1))
    bic         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1012A0 << 1))

miu0_rq3_skip:
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
@// MIU1: generate set priority pulse for "fix priority"

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100640 << 1))
    and         r3, r3, #0x0001
    cmp         r3, #1
    beq         miu1_rq0_skip

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100640 << 1))
    orr         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x100640 << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100640 << 1))
    bic         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x100640 << 1))

miu1_rq0_skip:

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100660 << 1))
    and         r3, r3, #0x0001
    cmp         r3, #1
    beq         miu1_rq1_skip

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100660 << 1))
    orr         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x100660 << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100660 << 1))
    bic         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x100660 << 1))

miu1_rq1_skip:

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100680 << 1))
    and         r3, r3, #0x0001
    cmp         r3, #1
    beq         miu1_rq2_skip

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100680 << 1))
    orr         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x100680 << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100680 << 1))
    bic         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x100680 << 1))

miu1_rq2_skip:

    RREG        r3, (MS_BUS_RIU_ADDR + (0x1006A0 << 1))
    and         r3, r3, #0x0001
    cmp         r3, #1
    beq         miu1_rq3_skip

    RREG        r3, (MS_BUS_RIU_ADDR + (0x1006A0 << 1))
    orr         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1006A0 << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x1006A0 << 1))
    bic         r3, r3, #0x0002
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x1006A0 << 1))

miu1_rq3_skip:
#endif

    bx          lr
#endif

@//-------------------------------------------------------------------------------------------------
@// MIU_Set_Group_Priority
@// @param  None
@// @return None
@// @note   Set Group Priority
@//-------------------------------------------------------------------------------------------------
    .global     MIU_Set_Group_Priority
MIU_Set_Group_Priority:
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

@//-------------------------------------------------------------------------------------------------
@// MiuBistTest
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
#if 0
#if !defined(CONFIG_MIU1_DRAM_NONE)
    .global     Miu1_BistTest
Miu1_BistTest:
    @//Setup for MIU1 BIST
    DPUTK       'B'
    DPUTK       'I'
    DPUTK       'S'
    DPUTK       'T'
    DPUTK       '1'
    DPUTK       '-'

    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000   @//1012e0 //reset bist test
    WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x8000   @//1012f0 bit_15=1 choice to MIU_1
    WREG        (MS_BUS_RIU_ADDR + (0x1012e2 << 1)), 0x0000   @//1012e2 //start address base unit:4 k bytes
    WREG_D      (MS_BUS_RIU_ADDR + (0x1012e4 << 1)), BIST_LEN
    WREG        (MS_BUS_RIU_ADDR + (0x1012e8 << 1)), 0x5aa5   @//1012e8 //bist test pattern

    b           BistTest
#endif

#if !defined(CONFIG_MIU0_DRAM_NONE)
    .global     Miu0_BistTest
Miu0_BistTest:
     @//Setup for MIU0 BIST
    DPUTK       '\n'
    DPUTK       '\r'
    DPUTK       'B'
    DPUTK       'I'
    DPUTK       'S'
    DPUTK       'T'
    DPUTK       '0'
    DPUTK       '-'

    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000   @//1012e0 //reset bist test
    WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x0000   @//1012f0 bit_15=0 choice to MIU_0
    WREG        (MS_BUS_RIU_ADDR + (0x1012e2 << 1)), 0x0000   @//1012e2 //start address base unit: 4k bytes
    WREG_D      (MS_BUS_RIU_ADDR + (0x1012e4 << 1)), BIST_LEN
    WREG        (MS_BUS_RIU_ADDR + (0x1012e8 << 1)), 0x5aa5   @//1012e8 //bist test pattern

#endif
#endif

    .global     Miu1_BistTest
Miu1_BistTest:

    DPUTK_STR   MIU_MESSAGE_BIST1

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000   @//1012e0 //reset bist test
    ldr         r11, =0x8000
    str         r11, [r12, #(0xf0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x8000   @//1012f0 bit_15=1 choice to MIU_1
    b           Miu_BistTest

    .global     Miu0_BistTest
Miu0_BistTest:

    DPUTK_STR   MIU_MESSAGE_BIST0

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000
    str         r11, [r12, #(0xe0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000   @//1012e0 //reset bist test
    str         r11, [r12, #(0xf0 << 1)]    @//WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x0000   @//1012f0 bit_15=0 choice to MIU_0

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

@//================================================================================================
#ifdef CONFIG_ENABLE_AUTO_DQS

#define MIU_PHASE_LOOP_START            0x00                    @//The Starting Phase of Auto DQS: 0
#define MIU_PHASE_LOOP_END              0x0F                    @//The Maximum Phase of Auto DQS: 15
#define MIU_PHASE_TEST_SELECTION        (MS_BUS_RIU_ADDR + (0x103382 << 1))
#define MIU_GOOD_PHASE_START_NUMBER     (MS_BUS_RIU_ADDR + (0x103384 << 1))
#define MIU_GOOD_PHASE_COUNTER          (MS_BUS_RIU_ADDR + (0x103386 << 1))
#define MIU_ORGINAL_PHASE_SETTING       (MS_BUS_RIU_ADDR + (0x103388 << 1))
#define MIU_PHASE_REGISTER              r4
#define MIU_PHASE_LOOP_COUNTER          r5

#if 0
@//================================================================================================
#if !defined(CONFIG_MIU1_DRAM_NONE)
    .global     Miu1_AutoPhase
Miu1_AutoPhase:

@// WREG        (MS_BUS_RIU_ADDR + (0x100646 << 1)), 0x7ffe     @//Mask All MIU Clients on MIU1
@// WREG        (MS_BUS_RIU_ADDR + (0x100666 << 1)), 0xffff
@// WREG        (MS_BUS_RIU_ADDR + (0x100686 << 1)), 0xffff
@// WREG        (MS_BUS_RIU_ADDR + (0x1006a6 << 1)), 0xffff

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r0, [r12, #(0xf0 << 1)]     @//RREG        r0, (MS_BUS_RIU_ADDR + (0x1012f0 << 1))         @//Select BIST to MIU1 (0x1012F0[15] = 1)
    orr         r0, r0, #0x8000
    str         r0, [r12, #(0xf0 << 1)]     @//REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x1012f0 << 1))

    @//r4: MIU0 Phase Register Address (MIU0: 0x110d6e / MIU1: 0x110dee)
    ldr         MIU_PHASE_REGISTER, =(MS_BUS_RIU_ADDR + (0x110dee << 1))
    ldr         MIU_PHASE_LOOP_COUNTER, =MIU_PHASE_LOOP_START   @//r5: Phase Loop Counter (0 ~ 15)
    WREG        MIU_PHASE_TEST_SELECTION, 0                     @//0x103382[0]: MIU Auto Phase Test Selection
    WREG        MIU_GOOD_PHASE_START_NUMBER, 0                  @//0x103384[15:0]: Starting Number of Good Phase
    WREG        MIU_GOOD_PHASE_COUNTER, 0                       @//0x103386[15:0]: The Number of Good Phase

    ldr         r0, [MIU_PHASE_REGISTER]
    REG_C2M     r0, MIU_ORGINAL_PHASE_SETTING                   @//0x103388[15:0]: Backup Orginal Phase Setting

    DPUTK       'A'
    DPUTK       'u'
    DPUTK       't'
    DPUTK       'o'
    DPUTK       'D'
    DPUTK       'Q'
    DPUTK       'S'
    DPUTK       '1'
    DPUTK       '-'
    DPUTK       '['

    b           Miu_AutoDqs_Bist_Setup
#endif

@//================================================================================================
#if !defined(CONFIG_MIU0_DRAM_NONE)
    .global     Miu0_AutoPhase
Miu0_AutoPhase:

@// WREG        (MS_BUS_RIU_ADDR + (0x101246 << 1)), 0x7ffe     @//Mask All MIU Clients on MIU0
@// WREG        (MS_BUS_RIU_ADDR + (0x101266 << 1)), 0xffff
@// WREG        (MS_BUS_RIU_ADDR + (0x101286 << 1)), 0xffff
@// WREG        (MS_BUS_RIU_ADDR + (0x1012a6 << 1)), 0xffff

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r0, [r12, #(0xf0 << 1)]     @//RREG        r0, (MS_BUS_RIU_ADDR + (0x1012f0 << 1))         @//Select BIST to MIU0 (0x1012F0[15] = 0)
    bic         r0, r0, #0x8000
    str         r0, [r12, #(0xf0 << 1)]     @//REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x1012f0 << 1))

    @//r4: MIU0 Phase Register Address (MIU0: 0x110d6e / MIU1: 0x110dee)
    ldr         MIU_PHASE_REGISTER, =(MS_BUS_RIU_ADDR + (0x110d6e << 1))
    ldr         MIU_PHASE_LOOP_COUNTER, =MIU_PHASE_LOOP_START   @//r5: Phase Loop Counter (0 ~ 15)
    WREG        MIU_PHASE_TEST_SELECTION, 0                     @//0x103382[0]: MIU Auto Phase Test Selection (Phase 0 / Phase 1)
    WREG        MIU_GOOD_PHASE_START_NUMBER, 0                  @//0x103384[15:0]: Starting Number of Good Phase (0 ~ 15)
    WREG        MIU_GOOD_PHASE_COUNTER, 0                       @//0x103386[15:0]: The Number of Good Phase (0 ~ 15)

    ldr         r0, [MIU_PHASE_REGISTER]
    REG_C2M     r0, MIU_ORGINAL_PHASE_SETTING                   @//0x103388[15:0]: Backup Orginal Phase Setting

    DPUTK       '\n'
    DPUTK       '\r'
    DPUTK       'A'
    DPUTK       'u'
    DPUTK       't'
    DPUTK       'o'
    DPUTK       'D'
    DPUTK       'Q'
    DPUTK       'S'
    DPUTK       '0'
    DPUTK       '-'
    DPUTK       '['
#endif
#endif

@//================================================================================================
#if !defined(CONFIG_MIU1_DRAM_NONE)
    .global     Miu1_AutoPhase
Miu1_AutoPhase:

    DPUTK_STR   MIU_MESSAGE_AUTO_DQS1

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x8000                 @//RREG        r0, (MS_BUS_RIU_ADDR + (0x1012f0 << 1))         @//Select BIST to MIU1 (0x1012F0[15] = 1)
    str         r11, [r12, #(0xf0 << 1)]     @//REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x1012f0 << 1))

    @//r4: MIU0 Phase Register Address (MIU0: 0x110d6e / MIU1: 0x110dee)
    ldr         MIU_PHASE_REGISTER, =(MS_BUS_RIU_ADDR + (0x110dee << 1))

    b           Miu_AutoPhase
#endif

@//================================================================================================
#if !defined(CONFIG_MIU0_DRAM_NONE)
    .global     Miu0_AutoPhase
Miu0_AutoPhase:

    DPUTK_STR   MIU_MESSAGE_AUTO_DQS0

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x101200 << 1))
    ldr         r11, =0x0000                @//RREG        r0, (MS_BUS_RIU_ADDR + (0x1012f0 << 1))         @//Select BIST to MIU0 (0x1012F0[15] = 0)
    str         r11, [r12, #(0xf0 << 1)]    @//REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x1012f0 << 1))

    @//r4: MIU0 Phase Register Address (MIU0: 0x110d6e / MIU1: 0x110dee)
    ldr         MIU_PHASE_REGISTER, =(MS_BUS_RIU_ADDR + (0x110d6e << 1))
#endif

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

#endif

@//-------------------------------------------------------------------------------------------------
@// BootRom_SetL3Clock
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
    .global     BootRom_SetL3Clock
BootRom_SetL3Clock:
#if 0
    RREG        r3, (MS_BUS_RIU_ADDR + (0x100B3E << 1))
    ldr         r4, =0x0000EFFF
    and         r3, r3, r4
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x100B3E << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100B3E << 1))
    ldr         r4, =0x00001000
    orr         r3, r3, r4
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x100B3E << 1))

    RREG        r3, (MS_BUS_RIU_ADDR + (0x100B3E << 1))
    ldr         r4, =0x0000EFFF
    and         r3, r3, r4
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x100B3E << 1))
#endif
    WREG_B      (MS_BUS_RIU_ADDR + (0x101E20 << 1)), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x100B22 << 1) + 1), 0x80
#if 1
    RREG        r3, (MS_BUS_RIU_ADDR + (0x101882 << 1))
    ldr         r4, =0x00000084
    orr         r3, r3, r4
    REG_C2M     r3, (MS_BUS_RIU_ADDR + (0x101882 << 1))
#endif

    bx          lr

@//================================================================================================

    .size       BootRom_InitMiu,.-BootRom_InitMiu
