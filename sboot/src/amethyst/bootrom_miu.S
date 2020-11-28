################################################################################
#
# Copyright (c) 2006-2011 MStar Semiconductor, Inc.
# All rights reserved.
#
# Unless otherwise stipulated in writing, any and all information contained
# herein regardless in any format shall remain the sole proprietary of
# MStar Semiconductor Inc. and be kept in strict confidence
# (¡§MStar Confidential Information¡¨) by the recipient.
# Any unauthorized act including without limitation unauthorized disclosure,
# copying, use, reproduction, sale, distribution, modification, disassembling,
# reverse engineering and compiling of the contents of MStar Confidential
# Information is unlawful and strictly prohibited. MStar hereby reserves the
# rights to any and all damages, losses, costs and expenses resulting therefrom.
#
################################################################################

#ifndef _BOOT_INC_
#include "boot.inc"
#endif

#ifndef _ArchDefs_h_
#include "ArchDefs.h"
#endif

#ifndef _BOARD_H_
#include "Board.h"
#endif

#ifndef _DRV_MIU_INIT_H_
#include "drv_miu_init.h"
#endif

#ifndef _MIUSEL_AMETHYST_2MIU_H_
#include "MIUSEL_AMETHYST_2MIU.h"
#endif

#define MIU_AUTO_DRV_N_TRG_LVL              0
#define MIU_TRIG_LVL                        0
#define MIU_AUTO_DRV                        0
#define MIU_AUTO_SKEW                       0
#define MIU_AUTO_DDL                        0

    .text
	.set    	noreorder

    .global     BootInitMiu
    .ent        BootInitMiu

BootInitMiu:

    move        t7, ra

    DBGREG      0x0020

#ifdef CONFIG_MSTAR_TITANIA_BD_FPGA

    WREG        (REG_ADDR_BASE + (0x003008 << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x101EA0 << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x002BC6 << 1)), 0x3c11
    WREG        (REG_ADDR_BASE + (0x002BCA << 1)), 0x403c
    WREG        (REG_ADDR_BASE + (0x002BC4 << 1)), 0x0004
    WREG        (REG_ADDR_BASE + (0x101202 << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x101202 << 1)), 0x0818
    WREG        (REG_ADDR_BASE + (0x101204 << 1)), 0x0185
    WREG        (REG_ADDR_BASE + (0x101206 << 1)), 0x0120
    WREG        (REG_ADDR_BASE + (0x101208 << 1)), 0x0833
    WREG        (REG_ADDR_BASE + (0x10120A << 1)), 0x0c33
    WREG        (REG_ADDR_BASE + (0x10120C << 1)), 0x7111
    WREG        (REG_ADDR_BASE + (0x10120E << 1)), 0x100e
    WREG        (REG_ADDR_BASE + (0x101210 << 1)), 0x0031          
    WREG        (REG_ADDR_BASE + (0x10121E << 1)), 0x0C01
    WREG        (REG_ADDR_BASE + (0x10121E << 1)), 0x0C00
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x0008
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x000c
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x000e        
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x001f         
    WREG        (REG_ADDR_BASE + (0x10121E << 1)), 0x0C08   
    WREG        (REG_ADDR_BASE + (0x101228 << 1)), 0x4000  
    WREG        (REG_ADDR_BASE + (0x10123A << 1)), 0x0001
    WREG        (REG_ADDR_BASE + (0x10123C << 1)), 0x03ff

_CheckDramData:

    lw          t1, (REG_ADDR_BASE + (0x101200 << 1))
    and         t1, t1, 0x8000
    beqz        t1, _CheckDramData
    nop

    move        ra, t7
    jr          ra
    nop

#else

#ifndef CONFIG_MIU0_DRAM_NONE
    # MIU0 Software reset
    WREG        (REG_ADDR_BASE + (0x10121e << 1)), 0x0000   #hold miu_0
    WREG        (REG_ADDR_BASE + (0x10121e << 1)), 0x0c01   #miu_sw_rst
    WREG        (REG_ADDR_BASE + (0x10121e << 1)), 0x0e00   #
    WREG        (REG_ADDR_BASE + (0x101202 << 1)), 0x0000   #disable all ddr bus out

    # MIU0 Request mask
    WREG        (REG_ADDR_BASE + (0x1012F8 << 1)), 0x8000
    WREG        (REG_ADDR_BASE + (0x101246 << 1)), 0xFFFE   # mask group0
    WREG        (REG_ADDR_BASE + (0x101266 << 1)), 0xFFFF   # mask group1
    WREG        (REG_ADDR_BASE + (0x101286 << 1)), 0xFFFF   # mask group2
    WREG        (REG_ADDR_BASE + (0x1012A6 << 1)), 0xFFFF   # mask group3
#endif

#ifndef CONFIG_MIU1_DRAM_NONE
    # MIU1 Software reset
    WREG        (REG_ADDR_BASE + (0x10061e << 1)), 0x0000   #hold miu_0
    WREG        (REG_ADDR_BASE + (0x10061e << 1)), 0x0c01   #
    WREG        (REG_ADDR_BASE + (0x10061e << 1)), 0x0e00   #
    WREG        (REG_ADDR_BASE + (0x100602 << 1)), 0x0000   #

    # MIU1 Request mask
    WREG        (REG_ADDR_BASE + (0x1006F8 << 1)), 0x8000
    WREG        (REG_ADDR_BASE + (0x100646 << 1)), 0xFFFE   # mask group0
    WREG        (REG_ADDR_BASE + (0x100666 << 1)), 0xFFFF   # mask group1
    WREG        (REG_ADDR_BASE + (0x100686 << 1)), 0xFFFF   # mask group2
    WREG        (REG_ADDR_BASE + (0x1006A6 << 1)), 0xFFFF   # mask group3
#endif

#ifndef CONFIG_MIU0_DRAM_NONE
    lui         a0, %hi(MIU0_DDR_Init)
    bal         MDrv_WriteRegTbl32
    ori         a0, %lo(MIU0_DDR_Init)

    DELAYUS     1000
    
    DBGREG      0x0021

    # Enable MIU0
    WREG        (REG_ADDR_BASE + (0x10121e << 1)), 0x0c01
    WREG        (REG_ADDR_BASE + (0x10121e << 1)), 0x0c08

    DELAYUS     200                                         # delay 200us
    
.if ( MIU_INTERFACE == DDR2_INTERFACE_BGA)
    WREG        (REG_ADDR_BASE + (0x110d00 << 1)), 0x0401
.else
#if defined(CONFIG_MIU0_DDR3_1666)   
        WREG        (REG_ADDR_BASE + (0x110d00 << 1)), 0x0401  
#else
        WREG        (REG_ADDR_BASE + (0x110d00 << 1)), 0x0201
#endif
.endif
    WREG        (REG_ADDR_BASE + (0x110d02 << 1)), 0xAAAA
    DBGREG      0x0023
#endif

#ifndef CONFIG_MIU1_DRAM_NONE
    lui         a0, %hi(MIU1_DDR_Init)
    ori         a0, %lo(MIU1_DDR_Init)
    bal         MDrv_WriteRegTbl32
    nop

    DELAYUS     1000

    # Enable MIU1
    WREG        (REG_ADDR_BASE + (0x10061e << 1)), 0x0c01
    WREG        (REG_ADDR_BASE + (0x10061e << 1)), 0x0c00

    DELAYUS     200                                         # delay 200us

    .if ( MIU_INTERFACE == DDR2_INTERFACE_BGA)
        WREG        (REG_ADDR_BASE + (0x110d80 << 1)), 0x0401
    .else  
#if defined(CONFIG_MIU1_DDR3_1666)   
        WREG        (REG_ADDR_BASE + (0x110d80 << 1)), 0x0401  
#else
        WREG        (REG_ADDR_BASE + (0x110d80 << 1)), 0x0201
#endif
    .endif
    WREG        (REG_ADDR_BASE + (0x110d82 << 1)), 0xAAAA
#endif

#// bal        EnableMiuSsc
#// nop

    DBGREG      0x0024

#ifndef CONFIG_MIU0_DRAM_NONE
    # rx enable
    WREG        (REG_ADDR_BASE + (0x110d08 << 1)), 0x003f

    # MIU0 INIT Cycle
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x0000   # hold miu_0
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x0008   # DRAM reset
    DELAYUS     500                                         # delay 500us    
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x000c   # DRAM reset+CS
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x000e   # DRAM reset+CS+CKE
    DELAYUS     500                                         # delay 500us
    WREG        (REG_ADDR_BASE + (0x101200 << 1)), 0x001f   # DRAM reset+CS+CKE+auto cycle+ODE
    DBGREG      0x0025

CheckMiu0Init:
    RREG        t1, (REG_ADDR_BASE + (0x101200 << 1))
    andi        t1, t1, 0x8000
    beqz        t1, CheckMiu0Init
    nop
#endif

    DBGREG      0x0026

#ifndef CONFIG_MIU1_DRAM_NONE
    # rx enable
    WREG        (REG_ADDR_BASE + (0x110d88 << 1)), 0x003f

    # MIU1 INIT Cycle
    WREG        (REG_ADDR_BASE + (0x100600 << 1)), 0x0000   # hold miu_0
    WREG        (REG_ADDR_BASE + (0x100600 << 1)), 0x0008   # DRAM reset
    DELAYUS     500                                         # delay 500us    
    WREG        (REG_ADDR_BASE + (0x100600 << 1)), 0x000c   # DRAM reset+CS
    WREG        (REG_ADDR_BASE + (0x100600 << 1)), 0x000e   # DRAM reset+CS+CKE
    DELAYUS     500                                         # delay 500us
    WREG        (REG_ADDR_BASE + (0x100600 << 1)), 0x001f   # DRAM reset+CS+CKE+auto cycle+ODE
CheckMiu1Init:
    RREG        t1, (REG_ADDR_BASE + (0x100600 << 1))
    andi        t1, t1, 0x8000
    beqz        t1, CheckMiu1Init
    nop
#endif

    DBGREG      0x0027

    bal         MIU_Init_AnalogResetPatch
    nop

    bal         MIU_Init_Priority
    nop

    bal         MIU_Set_Group_Priority
    nop

    DBGREG      0x0028

#ifndef CONFIG_MIU0_DRAM_NONE
    # BIST test
    WREG        (REG_ADDR_BASE + (0x101246 << 1)), 0x7FFE   #Mask MIU0_group_0
    bal         Miu0_BistTest
    nop
#endif
#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (REG_ADDR_BASE + (0x100646 << 1)), 0x7FFE   #Mask MIU0_group_0
    bal         Miu1_BistTest
    nop
#endif
    WREG        (REG_ADDR_BASE + (0x1012e0 << 1)), 0x0000   # stop bist test

#ifdef ENABLE_AUTO_PHASE
#ifndef CONFIG_MIU0_DRAM_NONE
    WREG        (REG_ADDR_BASE + (0x101246 << 1)), 0x7FFE   #Mask MIU0_group_0
    bal         Miu0_AutoPhase
    nop
#endif   
#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (REG_ADDR_BASE + (0x100646 << 1)), 0x7FFE   #Mask MIU0_group_0
    bal         Miu1_AutoPhase
    nop
#endif
#endif

#ifndef CONFIG_MIU0_DRAM_NONE  
    # open all MIU0 request mask (All IP can access MIU resource)
    WREG        (REG_ADDR_BASE + (0x101246 << 1)), 0x0000   #Mask MIU0_group_0
    WREG        (REG_ADDR_BASE + (0x101266 << 1)), 0x0000   #Mask MIU0_group_1
    WREG        (REG_ADDR_BASE + (0x101286 << 1)), 0x0000   #Mask MIU0_group_2
    WREG        (REG_ADDR_BASE + (0x1012a6 << 1)), 0x0000   #Mask MIU0_group_3
#endif

#ifndef CONFIG_MIU1_DRAM_NONE
    # open all MIU1 request mask (All IP can access MIU resource)
    WREG        (REG_ADDR_BASE + (0x100646 << 1)), 0x0000   #Mask MIU0_group_0
    WREG        (REG_ADDR_BASE + (0x100666 << 1)), 0x0000   #Mask MIU0_group_1
    WREG        (REG_ADDR_BASE + (0x100686 << 1)), 0x0000   #Mask MIU0_group_2
    WREG        (REG_ADDR_BASE + (0x1006a6 << 1)), 0x0000   #Mask MIU0_group_3

    # all MIU1 IP select MIU0 in bringup
    WREG        (REG_ADDR_BASE + (0x1006f0 << 1)), 0x4088   #0x7fff
    WREG        (REG_ADDR_BASE + (0x1006f2 << 1)), 0x0000   #0xffff
    WREG        (REG_ADDR_BASE + (0x1006f4 << 1)), 0x0000   #0xffff
    WREG        (REG_ADDR_BASE + (0x1006f6 << 1)), 0x0000   #0xffff
#endif

    WREG        (REG_ADDR_BASE + (0x10121e << 1)), 0x0c08   # SW initial done and turn on arbitor

#if (MIU_AUTO_DDL == 1)
    bal         auto_ddl
    nop
#endif

    DBGREG      0x0029

#if (MIU_AUTO_SKEW == 1)
    bal         Auto_Skew
    nop
#endif

#if (MIU_AUTO_DRV_N_TRG_LVL == 1)
    bal         Adj_TriggerLvl_and_DriverStrength
    nop
#endif

    WREG        (REG_ADDR_BASE + (0x101842 << 1)), 0x0000        #//Set MIU0 Size of MAU0
    WREG        (REG_ADDR_BASE + (0x101862 << 1)), 0x0000        #//Set MIU0 Size of MAU1

#endif

    move        ra, t7
    jr          ra
    nop

    .size       BootInitMiu,.-BootInitMiu
    .end        BootInitMiu

#-------------------------------------------------------------------------------------------------
#if (MIU_AUTO_DRV_N_TRG_LVL == 1)

Adj_TriggerLvl_and_DriverStrength:
#if (MIU_TRIG_LVL == 1)
    RREG	    t1, (REG_ADDR_BASE + (0x002012 << 1))
    andi        t0, t1, 0x0001
    beqz	    t0, CheckMiu_1_triggerLvl
    nop
CheckMiu_0_triggerLvl:
    lui         t0, 0xbf22
    lw          t1, (0x1ae0)(t0)                            # get reg_0x110d70
    ori         t1, t1, 0x0302                              # set bit9,8,1 = 1
    sw          t1, (0x1ae0)(t0)

    li          t2, 0x0000                                  # tmp_var_0 =0 for loop cnt
    li          t4, 0x00                                    # tmp_var_2 =0

    move        s6, ra
    bal         ClearMailboxVar
    nop
    move        ra, s6
ChkTrigLvlLoop:

    move        s6, ra
    bal         Delay_1us
    nop
    move        ra, s6


    RREG	    t3, (REG_ADDR_BASE + (0x110d72 << 1))
    srl         t3, t3, 12
    sll         t4, t3, 1
    li          t0, (REG_ADDR_BASE + (0x103380 << 1))   # t0 pointer to 1st mailbox
    add         t4, t4, t0
    andi        t1, t3, 0x0001
    beqz	    t1, StoreParametr
    nop
    add         t4, t4, 1
StoreParametr:
    lb          t3, 0(t4)
    addi        t3, t3, 1
    sb          t3, 0(t4)
    addiu       t2, t2, 1
    bltu        t2, 50, ChkTrigLvlLoop
    nop
    lui         t0, 0xbf22
    lw          t1, (0x0d70 << 1)(t0)                       # get reg_0x110d70
    andi        t1, t1, 0xfcfd                          # clr bit9,8,0 = 0
    sw          t1, (0x0d70 << 1)(t0)


    move        s6, ra
    bal         GetMaxCntInMbxReg                           #reture value t4
    nop
    move        ra, s6

    RREG        t1, (REG_ADDR_BASE + (0x2012 << 1))
    srl         t1, t1, 4                                   # bit [86~84]
    andi        t0, t1, 0x0004
    beqz	    t0, PlusMiu0trgLvl
    nop
MiussMiu0trgLvl:
    andi        t1, t1, 0x0003
    sub         t4, t4, t1
    j           SetMiu0_trglvl
    nop
PlusMiu0trgLvl:
    andi        t1, t1, 0x0003
    add         t4, t4, t1

SetMiu0_trglvl:
    lui         t0, 0xbf22
    lw          t1, (0x0d72 << 1)(t0)                       # set trig_level to reg_0x110d72 bit3~0
    andi        t1, t1, 0xfff0
    or          t1, t1, t4
    sw          t1, (0x0d72 << 1)(t0)                       # set trig_level to reg_0x110d72 bit3~0

    lw          t1, (0x0d62 << 1)(t0)                       # set trig_level to reg_0x110d62 bit12~15
    andi        t1, t1, 0x0fff
    sll         t4, t4, 12
    or          t1, t1, t4
    sw          t1, (0x0d62 << 1)(t0)                       # set trig_level to reg_0x110d62 bit12~15


CheckMiu_1_triggerLvl:
    RREG	    t1, (REG_ADDR_BASE + (0x002012 << 1))
    andi        t0, t1, 0x0002
    beqz	    t0, CheckMiu_trgLvl_over
    nop

    lui         t0, 0xbf22
    lw          t1, (0x0df0 << 1)(t0)                       # get reg_0x110df0
    ori         t1, t1, 0x0302                              # set bit9,8,1 = 1
    sw          t1, (0x0df0 << 1)(t0)

    li          t2, 0x0000                                  # tmp_var_0 =0 for loop cnt
    li          t4, 0x00                                    # tmp_var_2 =0


    move        s6, ra
    bal         ClearMailboxVar
    nop
    move        ra, s6
ChkMiu1_TrigLvlLoop:

    move        s6, ra
    bal         Delay_1us
    nop
    move        ra, s6

    RREG	    t3, (REG_ADDR_BASE + (0x110df2 << 1))
    srl         t3, t3, 12
    sll         t4, t3, 1
    li          t0, (REG_ADDR_BASE + (0x103380 << 1))   # t0 pointer to 1st mailbox
    add         t4, t4, t0
    andi        t1, t3, 0x0001
    beqz	    t1, Miu1_StoreParametr
    nop
    add         t4, t4, 1
Miu1_StoreParametr:
    lb          t3, 0(t4)
    addi        t3, t3, 1
    sb          t3, 0(t4)
    addiu       t2, t2, 1
    bltu        t2, 50, ChkMiu1_TrigLvlLoop
    nop
    lui         t0, 0xbf22
    lw          t1, (0x0df0 << 1)(t0)                       # get reg_0x110df0
    andi        t1, t1, 0xfcfd                              # clr bit9,8,0 = 0
    sw          t1, (0x0df0 << 1)(t0)


    move        s6, ra
    bal         GetMaxCntInMbxReg
    nop
    move        ra, s6

    RREG        t1, (REG_ADDR_BASE + (0x2012 << 1))
    srl         t1, t1, 7                                   # bit [86~87]
    andi        t0, t1, 0x0004
    beqz	    t0, PlusMiu1trgLvl
    nop
MiussMiu1trgLvl:
    andi        t1, t1, 0x0003
    sub         t4, t4, t1
    j           SetMiu1_trglvl
    nop
PlusMiu1trgLvl:
    andi        t1, t1, 0x0003
    add         t4, t4, t1

SetMiu1_trglvl:

    lui         t0, 0xbf22
    lw          t1, (0x0df2 << 1)(t0)                       # set trig_level to reg_0x110d72 bit3~0
    andi        t1, t1, 0xfff0
    or          t1, t1, t4
    sw          t1, (0x0df2 << 1)(t0)                       # set trig_level to reg_0x110d72 bit3~0

    lw          t1, (0x0de2 << 1)(t0)                       # set trig_level to reg_0x110d62 bit12~15
    andi        t1, t1, 0x0fff
    sll         t4, t4, 12
    or          t1, t1, t4
    sw          t1, (0x0de2 << 1)(t0)                       # set trig_level to reg_0x110d62 bit12~15

CheckMiu_trgLvl_over:

#endif   #// if MIU_TRIG_LVL == 1


#if (MIU_AUTO_DRV == 1)
CheckMiu_DriverPatch:
    RREG	    t1, (REG_ADDR_BASE + (0x002012 << 1))
    andi        t0, t1, 0x000c
    beqz	    t0, AutoMiuAtopRet
    nop

    srl         t3, t1, 10                                  # [90~91] = miu0 data offset
    andi        t3, t3, 0x0003                              # t3 = miu0 data offset
    RREG	    t1, (REG_ADDR_BASE + (0x002014 << 1))
    srl         t2, t1, 1                                   # [99~97]= data driver strength
    and         t2, t2, 0x0007                              # t2 = Data_driving_strength
    addu        t2, t2, t3                                  #  driver_sum=Data_driving_strength +0ffset


    RREG	    t1, (REG_ADDR_BASE + (0x002012 << 1))
    andi        t0, t1, 0x0004
    beqz	    t0, Miu_1_DrvPatch
    nop
Miu_0_DrvPatch:
    RREG        t1, (REG_ADDR_BASE + (0x110d42 << 1))          # pull down driver strength
    and         t1, t1, 0xfff8
    or          t1, t1, t2
    sw          t1, (REG_ADDR_BASE + (0x110d42 << 1))

    RREG        t1, (REG_ADDR_BASE + (0x110d4a << 1))          # pull up driver strength
    and         t1, t1, 0xfff8
    or          t1, t1, t2
    sw          t1, (REG_ADDR_BASE + (0x110d4a << 1))

    move        t3, t2
    sll         t2, t2, 4
    sll         t3, t3, 8
    addu        t2, t2, t3                                  # bit 8~10

Miu_0_DrvPatch_2:
    RREG        t1, (REG_ADDR_BASE + (0x110d46 << 1))
    and         t1, t1, 0xf88f
    or          t1, t1, t2
    sw          t1, (REG_ADDR_BASE + (0x110d46 << 1))

    RREG        t1, (REG_ADDR_BASE + (0x110d4e << 1))
    and         t1, t1, 0xf88f
    or          t1, t1, t2
    sw          t1, (REG_ADDR_BASE + (0x110d4e << 1))

Miu_1_DrvPatch:
    RREG	    t1, (REG_ADDR_BASE + (0x002012 << 1))
    andi        t0, t1, 0x0008
    beqz	    t0, Miu_DataDrvPatch_over
    nop

    RREG	    t1, (REG_ADDR_BASE + (0x002014 << 1))
    srl         t2, t1, 1                                   # [99~97]= MIU0/MIU1 data driver strength
    and         t2, t2, 0x0007                              # t2 = Data_driving_strength

    RREG	    t1, (REG_ADDR_BASE + (0x002012 << 1))
    srl         t3, t1, 12
    and         t3, t3, 0x0003                              #  t3 = MIU1 CMD/Data offset
    addu        t2, t2, t3                                  #  miu1 driver_sum=Data_driving_strength +0ffset


    RREG        t1, (REG_ADDR_BASE + (0x110d40 << 1))          # pull down driver strength
    and         t1, t1, 0xfff8
    or          t1, t1, t2
    sw          t1, (REG_ADDR_BASE + (0x110d40 << 1))          #

    RREG        t1, (REG_ADDR_BASE + (0x110d48 << 1))          # pull up driver strength
    and         t1, t1, 0xfff8
    or          t1, t1, t2
    sw          t1, (REG_ADDR_BASE + (0x110d48 << 1))          #

Miu_1_DrvPatch_2:
    move        t3, t2
    sll         t2, t2, 4
    sll         t3, t3, 8
    addu        t2, t2, t3                                  # bit 8~10 / bit 4~6

    RREG        t1, (REG_ADDR_BASE + (0x110d44 << 1))          #
    and         t1, t1, 0xf88f
    or          t1, t1, t2
    sw          t1, (REG_ADDR_BASE + (0x110d44 << 1))          #

    RREG        t1, (REG_ADDR_BASE + (0x110d4c << 1))          #
    and         t1, t1, 0xf88f
    or          t1, t1, t2
    sw          t1, (REG_ADDR_BASE + (0x110d4c << 1))
Miu_DataDrvPatch_over:
# CMD driver strength
    RREG	    t1, (REG_ADDR_BASE + (0x002012 << 1))
    andi        t0, t1, 0x0004
    beqz	    t0, Miu_1_CmdDrvPatch
    nop

    RREG	    t1, (REG_ADDR_BASE + (0x002012 << 1))
    srl         t3, t1, 10                                  # [90~91] = miu0 CMD offset
    and         t3, t3, 0x0003                              # t3 = miu0 CMD offset

    srl         t2, t1, 14                                  # [94~95] = miu_0 /MIU_1 cmd_driver
    and         t2, t2, 0x0003                              #
    RREG	    t1, (REG_ADDR_BASE + (0x002014 << 1))
    and         t1, t1, 0x0001                              # [96] = miu0 cmd_driver b__
    sll         t1, t1, 2
    addu        t2, t2, t1                                  # t2 = CMD/ADR driver strength
    addu        t2, t2, t3                                  # CMD_driver_sum=cmd_driving_strength +0ffset

    sll         t3, t2, 8

Miu_0_CmdDrvPatch:
    RREG        t1, (REG_ADDR_BASE + (0x110d42 << 1))          #
    and         t1, t1, 0xf8ff
    or          t1, t1, t3
    sw          t1, (REG_ADDR_BASE + (0x110d42 << 1))          #

    RREG        t1, (REG_ADDR_BASE + (0x110d4a << 1))          #
    and         t1, t1, 0xf8ff
    or          t1, t1, t3
    sw          t1, (REG_ADDR_BASE + (0x110d4A << 1))          #


    sll         t3, t2, 12
    or          t2, t2, t3
    and         t2, t2, 0x7007

Miu_0_CmdPatch_2:
    RREG        t1, (REG_ADDR_BASE + (0x110d46 << 1))          #
    and         t1, t1, 0x8ff8
    or          t1, t1, t2
    sw          t1, (REG_ADDR_BASE + (0x110d46 << 1))

    RREG        t1, (REG_ADDR_BASE + (0x110d4e << 1))          #
    and         t1, t1, 0x8ff8
    or          t1, t1, t2
    sw          t1, (REG_ADDR_BASE + (0x110d4e << 1))


Miu_1_CmdDrvPatch:
    RREG	    t1, (REG_ADDR_BASE + (0x002012 << 1))
    andi        t0, t1, 0x0008
    beqz	    t0, Miu_CmdDrvPatch_over
    nop


    RREG	    t1, (REG_ADDR_BASE + (0x002012 << 1))
    srl         t3, t1, 12                                  # [90~91] = miu0 CMD offset
    and         t3, t3, 0x0003                              # t3 = miu0 CMD offset

    srl         t2, t1, 14                                  # [94~95] = miu_0 /MIU_1 cmd_driver
    and         t2, t2, 0x0003                              #
    RREG	    t1, (REG_ADDR_BASE + (0x002014 << 1))
    and         t1, t1, 0x0001                              # [96] = miu0 cmd_driver b__
    sll         t1, t1, 2
    addu        t2, t2, t1                                  # t2 = CMD/ADR driver strength
    addu        t2, t2, t3                                  # CMD_driver_sum=cmd_driving_strength +0ffset

    sll         t3, t2, 12
    and         t3, t3, 0x7000
    RREG        t1, (REG_ADDR_BASE + (0x110d42 << 1))
    and         t1, t1, 0x8fff
    or          t1, t1, t3
    sw          t1, (REG_ADDR_BASE + (0x110d42 << 1))

    RREG        t1, (REG_ADDR_BASE + (0x110d4a << 1))
    and         t1, t1, 0x8fff
    or          t1, t1, t3
    sw          t1, (REG_ADDR_BASE + (0x110d4A << 1))

Miu_CmdDrvPatch_2:
    sll         t3, t2, 12
    or          t2, t2, t3
    and         t2, t2, 0x7007

    RREG        t1, (REG_ADDR_BASE + (0x110d44 << 1))
    and         t1, t1, 0x8ff8
    or          t1, t1, t2
    sw          t1, (REG_ADDR_BASE + (0x110d44 << 1))

    RREG        t1, (REG_ADDR_BASE + (0x110d4c << 1))
    and         t1, t1, 0x8ff8
    or          t1, t1, t2
    sw          t1, (REG_ADDR_BASE + (0x110d4c << 1))

Miu_CmdDrvPatch_over:

#endif  #//if MIU_AUTO_DRV == 1

AutoMiuAtopRet:
    jr          ra
    nop
#-------------------------------------------
#-------------------------------------------
Delay_1us:
    li          t3, 0x00                                    # tmp_var_1 =0 for delay 1us
ChkTrigLvlDly:
    addiu       t3, t3, 1
    bltu        t3, 200, ChkTrigLvlDly
    nop
    jr          ra
    nop

#if (MIU_TRIG_LVL == 1)

#--------------------------------------------------
# Mailbox reg : 0x103380~0x10338f for store the
# trigger level that gotten by auto test proceure!!
#
#-------------------------------------------
ClearMailboxVar:
    WREG        (REG_ADDR_BASE + (0x103380 << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x103382 << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x103384 << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x103386 << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x103388 << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x10338A << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x10338C << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x10338E << 1)), 0x0000
    jr          ra
    nop

#--------------------------------------------------
# Mailbox reg : 0x103380~0x10338f for store the
# get the trigger level in mailbox reg
# and get the maximum cnt in read 50 time
#return value store in : t4
#--------------------------------------------------
GetMaxCntInMbxReg:
#get maximum value
    li          t0, (REG_ADDR_BASE + (0x103380 << 1))
    li          t1, 0
    li          t4, 0                                       #final setting here
    add         t0, t1, t0
    lb          t3, 0(t0)

Miu_ChkNextTrgLvl:
    addi        t1, t1, 1
    bgeu        t1, 0x10, Chkmiu_TrgLvlOver

    srl         t2, t1, 1
    sll         t2, t2, 2
    andi        t0, t1, 0x0001
    beqz        t0, Miu_ShiftOffset_0
    nop
    addi        t2, t2, 1

Miu_ShiftOffset_0:
    li          t0, (REG_ADDR_BASE + (0x103380 << 1))
    add         t0, t2, t0
    lb          t2, 0(t0)
    bltu        t2, t3, Miu_ChkNextTrgLvl
    nop
    move        t3, t2
    move        t4, t1
    j           Miu_ChkNextTrgLvl
    nop

Chkmiu_TrgLvlOver:
    jr          ra
    nop
#-------------------------------------------
#-------------------------------------------
#endif  // if(MIU_TRIG_LVL == 1)

#-------------------------------------------
#endif

#-------------------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------------------
#if (MIU_AUTO_SKEW == 1)
Auto_Skew:
    move    fp, ra

    #For MIU 0
    li          s4, (REG_ADDR_BASE + (0x10122C << 1))   #0x122D reg_dqsm
    li          s5, (REG_ADDR_BASE + (0x101228 << 1))   #reg_clkph
    li          s6, 0                                   #bist type for miu 0
    jal         Do_skew
    nop

    li          s4, (REG_ADDR_BASE + (0x10123E << 1))   #0x123F reg_qsm1
    li          s5, (REG_ADDR_BASE + (0x101228 << 1))   #clkph
    li          s6, 0x8000                              #bist type for miu 1
    jal         Do_skew
    nop

    move        ra, fp
    jr          ra
    nop

/*
    Function Do_skew
*/
Do_skew:
    move        sp, ra

loop:
    lw          t3, 0(s4)                                 #dqsm

    # get dqsm value
    andi        t4, t3, 0x0700
    srl         t4, t4, 8

Skew_add:
    li          t5, 0                                       #flag
    # dqsm + 1
    addiu       t4, t4, 1
    # a3 is adjust offset
    addi        a3, zero, -2
    j           Skew_check
    nop

Skew_sub:
    li          t5, 1                                       #flag
    # dqsm - 1
    subu        t4, t4, 1
    # a3 is adjust offset
    addi        a3, zero, 2

Skew_check:
    jal         Save_dqsm
    nop
    jal         Skew_bist
    nop
    bnez        t6, Skew_Adjust
    nop
    beqz        t5, Skew_sub
    nop
    bnez        t6, loop
    nop

    move        ra, sp
    jr          ra
    nop

/*
    Function Save_dqsm
*/
Skew_Adjust:
    move        gp, ra

    PUTK        '$'
    # a3 = clph_cmd
    lw          a3, 0(s5)
    andi        a3, a3, 0x000F

    #s1 = dqsm * 10 + clkph_cmd - 2
    addi        s0, zero, 10
    mult        t3, s0
    mflo        s1
    add         s1, s1, t4
    sub         s1, s1, -2

    #dqsm = s1/10
    #clkph_cmd = s1 % 10
    div         s1, s0
    mflo        t4
    jal         Save_dqsm
    nop

    mfhi        s1

Save_clkph:
    #save clkph_cmd & clkph_dqsm
    andi        s1, s1, 0x000F
    srl         s2, s1, 4
    or          s1, s1, s2
    or          a3, a3, s1
    sw          a3, 0(s5)

    move        ra, gp
    jr          ra
    nop

/*
    Function Save_dqsm
*/
Save_dqsm:
    # t4 << 8
    sll         t4, t4, 8

    andi        t6, t3, 0xF8FF
    or          t3, t6, t4
    sw          t3, 0(s4)
    jr          ra
    nop

/*
    Function Skew_bist
*/
Skew_bist:
    li          t4, (REG_ADDR_BASE + (0x1012F0 << 1))
    sw          s6, 0(t4)                                   #//1012f0 select BIST miu
    WREG        (REG_ADDR_BASE + (0x1012E0 << 1)), 0        #//1012e0 reset BIST test
    WREG        (REG_ADDR_BASE + (0x1012E2<< 1)), 0x1FFF    #//1012e2 bist test start address, (4K byte/unit)
    WREG        (REG_ADDR_BASE + (0x1012E4 << 1)), 0x1000   #//1012e4~1012e7 bist test size, (16 byte/unit)
    WREG        (REG_ADDR_BASE + (0x1012E6 << 1)), 0x0000   #//1012e4~1012e7 bist test size, (16 byte/unit)
    WREG        (REG_ADDR_BASE + (0x1012E0 << 1)), 0x0007   #//bitst test x7 mode

Bist_done:
    RREG        t4, (REG_ADDR_BASE + (0x1012E0 << 1))
    andi        t6, t4, 0x8000
    beqz        t6, Bist_done
    nop

    andi        t6, t4, 0x6000
    jr          ra
    nop
#endif

#-------------------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------------------
#if (MIU_AUTO_DDL == 1)
# auto ddl begin
# read MIU_ATOP[0x33] bit 0~9
# S1. read back ddl value
# restrict the range (0x9A-0x75)
# add to pool
# delay 7ms
# loop to S1 for 4 times
# pool div by 4
# save the ddl code (pool) to 2 register
# disable auto dll calibration
# set read value mode back to 2 (reg_r_avg)
# loop to S0 for resting MIU

auto_ddl:
    move        t7, ra

# MIU0
    li          t4, 0x0000  // pool
    li          t5, 0x0     // counter

Check_calibration_value:

    RREG        t3, (REG_ADDR_BASE + (0x110D66 << 1))
    and         t3, t3, 0x03FF
    bgtu        t3, 0x009A, dll_rd_out_bigger_9A
    nop
    j           dll_rd_out_check_75
    nop

dll_rd_out_bigger_9A:
    and         t3, t3, 0xFC00
    or          t3, 0x9A
    j           dll_rd_out_end
    nop

dll_rd_out_check_75:
    bltu        t3, 0x0075, dll_rd_out_less_75
    nop
    j           dll_rd_out_end
    nop

dll_rd_out_less_75:
    and         t3, 0xFC00
    or          t3, 0x75

dll_rd_out_end:

# add to pool
# delay 7ms
# loop to S1 for 4 times
# pool div by 4

    add         t4, t3
    add         t5, 0x1
    DELAYUS     7000
    bltu        t5, 0x4, Check_calibration_value
    nop
    divu        t4, t4, 0x4

    # save the ddl code (pool) to 2 register
    li          t3, (REG_ADDR_BASE + (0x101236 << 1))
    sw          t4, 0(t3)
    li          t3, (REG_ADDR_BASE + (0x101238 << 1))
    sw          t4, 0(t3)

    # set read value mode back to 2 (reg_r_avg)
    RREG        t3, (REG_ADDR_BASE + (0x110D60 << 1))
    and         t3, t3, 0x8FFF
    or          t3, t3, 0x2000

    # disable auto dll calibration
    WREG_B      (REG_ADDR_BASE + (0x110D60 << 1) + 1), 0x20

# MIU1
    li          t4, 0x0000  // pool
    li          t5, 0x0     // counter

miu1_Check_calibration_value:

    RREG        t3, (REG_ADDR_BASE + (0x110DE6 << 1))
    and         t3, t3, 0x03FF
    bgtu        t3, 0x009A, miu1_dll_rd_out_bigger_9A
    nop
    j           miu1_dll_rd_out_check_75
    nop

miu1_dll_rd_out_bigger_9A:
    and         t3, t3, 0xFC00
    or          t3, 0x9A
    j           miu1_dll_rd_out_end
    nop

miu1_dll_rd_out_check_75:
    bltu        t3, 0x0075, miu1_dll_rd_out_less_75
    nop
    j           miu1_dll_rd_out_end
    nop

miu1_dll_rd_out_less_75:
    and         t3, 0xFC00
    or          t3, 0x75

miu1_dll_rd_out_end:

# add to pool
# delay 7ms
# loop to S1 for 4 times
# pool div by 4

    add         t4, t3
    add         t5, 0x1
    DELAYUS     7000
    bltu        t5, 0x4, miu1_Check_calibration_value
    nop

    divu        t4, t4, 0x4

    # save the ddl code (pool) to 2 register
    li          t3, (REG_ADDR_BASE + (0x100636 << 1))
    sw          t4, 0(t3)
    li          t3, (REG_ADDR_BASE + (0x100638 << 1))
    sw          t4, 0(t3)

    # set read value mode back to 2 (reg_r_avg)
    RREG        t3, (REG_ADDR_BASE + (0x110DE0 << 1))
    and         t3, t3, 0x8FFF
    or          t3, t3, 0x2000

    # disable auto dll calibration
    WREG_B      (REG_ADDR_BASE + (0x110DE0 << 1) + 1), 0x20
    # auto ddl end

    move        ra, t7
    jr          ra
    nop
#endif

#-------------------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------------------
EnableMiuSsc:
    # ENABLE MIU_0_SSC
    WREG        (REG_ADDR_BASE + (0x110d28 << 1)), DDFSTEP     #DDFSTEP
    WREG        (REG_ADDR_BASE + (0x110d2A << 1)), DDFSPAN     #DDFSPAN
    RREG        t1, (REG_ADDR_BASE + (0x110d28 << 1))          #ENABLE MIU_SSC
    ori         t1, t1, 0x8000
    sw          t1, (REG_ADDR_BASE + (0x110d28 << 1))

    # ENABLE MIU_1_SSC
    WREG        (REG_ADDR_BASE + (0x110dA8 << 1)),DDFSTEP      #DDFSTEP
    WREG        (REG_ADDR_BASE + (0x110dAA << 1)),DDFSPAN      #DDFSPAN
    RREG        t1, (REG_ADDR_BASE + (0x110dA8 << 1))          #ENABLE MIU_SSC
    ori         t1, t1, 0x8000
    sw          t1, (REG_ADDR_BASE + (0x110dA8 << 1))

    j           ra
    nop

#-------------------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------------------
Miu1_AutoPhase:
    WREG        (REG_ADDR_BASE + (0x1012F0 << 1)), 0x8000   #1012f0 bit_15=1 choice to MIU_1
    li          s7, (REG_ADDR_BASE + (0x103394 << 1))       # Dummy register to store miu1 DQS phase result
    li          t8, 0                                       # DQS phase result

    WREG        (REG_ADDR_BASE + (0x110DEE << 1)), 0x0077   # set the default phase setting to 0x77
    RREG        t1, (REG_ADDR_BASE + (0x110DEE << 1))       # store the default phase setting to r19
    move        s3, t1                                 

    li          t3, (REG_ADDR_BASE + (0x110DEE << 1))       # reg_0x110DEE  //miu1_phase_reg
    li          t2, (REG_ADDR_BASE + (0x1006E7 << 1))       # reg_0x1006e7  //miu1_dqs_mask_reg
    j           AutoPhaseLoop
    nop
Miu0_AutoPhase:
    WREG        (REG_ADDR_BASE + (0x1012F0 << 1)), 0x0000   # 1012f0 bit_15=0 choice to MIU_0
    li          s7, (REG_ADDR_BASE + (0x103390 << 1))       # Dummy register to store miu 0 DQS phase result
    li          t8, 0                                       # DQS phase result

    WREG        (REG_ADDR_BASE + (0x110D6E << 1)), 0x0077   # set the default phase setting to 0x77
    RREG        t1, (REG_ADDR_BASE + (0x110D6E << 1))       # store the default phase setting to r19
    move        s3, t1

    li          t3, (REG_ADDR_BASE + (0x110D6E << 1))       # reg_0x110D6E  //miu0_phase_reg
    li          t2, (REG_ADDR_BASE + (0x1012E7 << 1))       # reg_0x1012e7  //miu0_dqs_mask_reg

AutoPhaseLoop:
    PUTK        '['

    WREG        (REG_ADDR_BASE + (0x1012e4 << 1)), 0x0401   # 1012e4~1012e7 bist test size,   (16 byte/unit)
    WREG        (REG_ADDR_BASE + (0x1012e6 << 1)), 0x0000   # 1012e4~1012e7 bist test size,   (16 byte/unit)
    WREG        (REG_ADDR_BASE + (0x1012e8 << 1)), 0x00FF   # 1012e4~1012e7 bist test pattern

    lui         t5, 0                                       # t5-->tmp_var0=0;  for loop cnt
    lui         s5, 0                                       # s5-->good_phase cnt
    lui         s4, 0                                       # s4-->good_phase_sum
    li          t9, 1                                       # t9-->good_phase bit

StartChk_x1:
    li          t1, 0x55
    sb          t1, (0)(t2)            # set miu0_dqs_mask_reg to 0x55

BistPatternfill:                    #write data into each region respect to bist mode 0x183,0x185,0x187
    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    andi        t1, t5, 0x0f
    sll         t1, t1, 4
    andi        t0, s3, 0x0f           # set dqs0 delay phase to r8
    or          t1, t1, t0
    sw          t1, (0)(t3)

    #ClockUnReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x20
    sb          k0, (0)(t6)

#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (REG_ADDR_BASE + (0x1006E0 << 1)), 0x0000
#endif
    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x1000   # 1012e2 bist test start address, (4K byte/unit)
    WREG        (REG_ADDR_BASE + (0x1012E0 << 1)), 0x0000
    li          t1, 0x0083              # bist mode 0x83
    j           BistRWModeTest
    nop

Check_bist85:
#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (REG_ADDR_BASE + (0x1006E0 << 1)), 0x0000
#endif
    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x1100   # 1012e2 bist test start address, (4K byte/unit)
    WREG        (REG_ADDR_BASE + (0x1012E0 << 1)), 0x0000
    li          t1, 0x0085              # bist mode 0x85
    j           BistRWModeTest
    nop

Check_bist87:
#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (REG_ADDR_BASE + (0x1006E0 << 1)), 0x0000
#endif
    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x1200   # 1012e2 bist test start address, (4K byte/unit)
    WREG        (REG_ADDR_BASE + (0x1012E0 << 1)), 0x0000
    li          t1, 0x0087              # bist mode 0x87

BistRWModeTest:                         # Read and Write bist
    move        s6, ra
    bal         ModeChangeDelay
    nop
    move        ra, s6

    sw          t1, (REG_ADDR_BASE + (0x1012E0 << 1))  # bist test start

CheckRWBistDone:
    RREG        t1, (REG_ADDR_BASE + (0x1012E0 << 1))
    andi        t0, t1, 0x8000
    beqz        t0, CheckRWBistDone        # check done
    nop

RWBistCheckPhaseOK:
    andi        t0, t1, 0x00FF
    beq         t0, 0x83, Check_bist85       #0x83->0x85->0x87
    nop
    beq         t0, 0x85, Check_bist87
    nop

check_x1:

    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    andi        t1, t5, 0x0f
    sll         t1, t1, 4
    andi        t0, s3, 0x0f           # set dqs0 delay phase to r8
    or          t1, t1, t0
    sw          t1, (0)(t3)

    #ClockUnReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x20
    sb          k0, (0)(t6)

    j           StartCheck
    nop
StartChk_x0:
    li          t1, 0xaa             # 1012e7/1006e7 =0xAA mask DQS_1 error when test DQS_0
    sb          t1, (0)(t2)

    sw          t8, (0)(s7)         # store phase 0 result
    addiu       s7, s7, 4
    li          t8, 0                # DQS phase result
    li          t9, 1
    j           check_x0
    nop
check_x0:
    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    andi        t1, t5, 0x0f
    andi        t0, s3, 0xf0  # get the default phase setting
    or          t1, t1, t0
    sw          t1, (0)(t3)

    #ClockUnReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x20
    sb          k0, (0)(t6)

StartCheck:
#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (REG_ADDR_BASE + (0x1006E0 << 1)), 0x0000
#endif
    WREG        (REG_ADDR_BASE + (0x1012E0 << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x1000   # 1012e2 bist test start address, (4K byte/unit)
    li          t1, 0x0183              # bist mode 0x183
    j           ROBitModeTest
    nop

Check_bist185:
#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (REG_ADDR_BASE + (0x1006E0 << 1)), 0x0000
#endif
    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x1100   # 1012e2 bist test start address, (4K byte/unit)
    WREG        (REG_ADDR_BASE + (0x1012E0 << 1)), 0x0000
    li          t1, 0x0185              # bist mode 0x185
    j           ROBitModeTest
    nop

Check_bist187:
#ifndef CONFIG_MIU1_DRAM_NONE
    WREG        (REG_ADDR_BASE + (0x1006E0 << 1)), 0x0000
#endif
    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x1200   # 1012e2 bist test start address, (4K byte/unit)
    WREG        (REG_ADDR_BASE + (0x1012E0 << 1)), 0x0000
    li          t1, 0x0187              # bist mode 0x187

ROBitModeTest:                      # read only bist
    move        s6, ra
    bal         ModeChangeDelay
    nop
    move        ra, s6

    sw          t1, (REG_ADDR_BASE + (0x1012E0 << 1))  # bist test start

CheckROBistDone:
    RREG        t1, (REG_ADDR_BASE + (0x1012E0 << 1))
    andi        t0, t1, 0x8000
    beqz        t0, CheckROBistDone        # check done
    nop
    andi        t0, t1, 0x6000
    bnez        t0, checkloopFail        # bist test fail if not zero
    nop

ROBistCheckPhaseOK:
    andi        t0, t1, 0x01FF
    beq         t0, 0x183, Check_bist185       #0x83->0x85->0x87
    nop
    beq         t0, 0x185, Check_bist187
    nop

    move        s6, ra
    andi        t1, t5, 0x0f        #move t5(loop cnt) to t1 for putchar
    bal         puthex
    nop
    move        ra, s6

    addiu       s5, s5, 1         # good_phase_cnt++;
    andi        s6, t5, 0x0f      # get good_phase
    add         s4, s4 ,s6        # good_phase_sum += good phase
    or          t8, t8, t9

checkloopFail:

checkloop:
    sll         t9, t9, 1
    addiu       t5, t5, 1             # add loop cnt by 1
    bne	        t5, 16 , CheckLoopDone
    nop

    beqz        s5, SetToDefault_P1    # if good_phase cnt == 0
    nop
    move        s6, s4  #good_phase_sum
    div         s6, s6 , s5
    sll         s6, s6 , 4
    j           StorePhase_P1
    nop
SetToDefault_P1:
    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    move        t1, s3
    j           SetPhaseToDefault_p1
    nop

StorePhase_P1:
    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    andi        t1, s3 , 0x0f
    or          t1, t1 , s6
SetPhaseToDefault_p1:
    sw          t1, 0(t3)
    move        s3, t1

   #ClockUnReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x20
    sb          k0, (0)(t6)


    lui         s5, 0                  # s5-->good_phase cnt
    lui         s4, 0                  # s4-->good_phase_sum

    PUTK        ']'
    PUTK       '\r'
    PUTK       '\n'
    PUTK        '['

    # start check DQS_phase_0
    #sw         s3, (0)(t3)
    j           StartChk_x0
    nop

CheckLoopDone:
    bltu        t5, 16, check_x1
    nop
    bltu	    t5, 32, check_x0      #AutoPhaseLoop1
    sw          t8, (0)(s7)         #store phase 0  result
    nop
    beqz        s5, SetToDefault_P0  # good_phase cnt == 0
    nop
    move        s6, s4  #good_phase_sum
    div         s6, s6 , s5
    #sll        s6, s6 , 4
    j           StorePhase_P0
    nop
SetToDefault_P0:
    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    move        t1, s3
    j           SetPhaseToDefault
    nop

StorePhase_P0:
    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    andi        t1,  s3 , 0xf0
    or          t1,  t1 , s6
SetPhaseToDefault:
    sw          t1,  0(t3)
    move        s3, t1

   #ClockUnReset
    li          t6, (REG_ADDR_BASE + (0x110D0E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x20
    sb          k0, (0)(t6)

    PUTK        ']'
    PUTK        '-'

    move        s6, ra
    andi        t1, s3, 0xf0
    srl         t1, t1, 4
    bal         puthex
    nop
    andi        t1, s3, 0x0f
    bal         puthex
    nop
    move        ra, s6

AutoPhaseRet:
    WREG        (REG_ADDR_BASE + (0x1012E0 << 1)), 0x0000
    li          t1, 0x00             # 1012e7/1006e7 =0x00 mask DQS_1 error when test DQS_0
    sb          t1, (0)(t2)

    PUTK        '\r'
    PUTK        '\n'

    jr          ra
    nop

puthex:
    bltu        t1, 10, putx0_9
    nop
putxA_F:
    addiu       t1, t1, 0x37
    j           putx
    nop
putx0_9:
    addiu       t1, t1, 0x30
putx:
    SSSW        (REG_ADDR_BASE + (0x100980 << 1)), t1
    jr          ra
    nop

ModeChangeDelay:
    lui         t0, 0x0
DelayLoop:
    addiu       t0, t0, 1
    bltu        t0, 10, DelayLoop
    nop
    jr          ra
    nop

#//-------------------------------------------------------------------------------------------------
#// MIU_Init_AnalogResetPatch
#// @param  None
#// @return None
#// @note   Patch for DDR Analog Reset Issue
#//-------------------------------------------------------------------------------------------------
MIU_Init_AnalogResetPatch:

    WREG        (REG_ADDR_BASE + (0x101246 << 1)), 0x7ffe
    WREG        (REG_ADDR_BASE + (0x10121e << 1)), 0x0c08
    WREG        (REG_ADDR_BASE + (0x1012e0 << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x1012e4 << 1)), 0x0081
    WREG        (REG_ADDR_BASE + (0x1012e6 << 1)), 0x0000
    WREG        (REG_ADDR_BASE + (0x1012e8 << 1)), 0x5aa5

#ifndef CONFIG_MIU0_DRAM_NONE      
    WREG        (REG_ADDR_BASE + (0x1012f0 << 1)), 0x0000

    RREG        t3, (REG_ADDR_BASE + (0x110d0e << 1))
    or          t3, t3, (0x01 << 6)
    sw          t3, (REG_ADDR_BASE + (0x110d0e << 1))
    
    WREG        (REG_ADDR_BASE + (0x1012e0 << 1)), 0x0200
    WREG        (REG_ADDR_BASE + (0x1012e0 << 1)), 0x0201

    RREG        t3, (REG_ADDR_BASE + (0x110d0e << 1))
    and         t3, t3, ~(0x01 << 6)
    sw          t3, (REG_ADDR_BASE + (0x110d0e << 1))
    
    WREG        (REG_ADDR_BASE + (0x1012e0 << 1)), 0x0000
#endif
    
#ifndef CONFIG_MIU1_DRAM_NONE    
    WREG        (REG_ADDR_BASE + (0x1012f0 << 1)), 0x8000
    WREG        (REG_ADDR_BASE + (0x100646 << 1)), 0x7ffe

    RREG        t3, (REG_ADDR_BASE + (0x110d8e << 1))
    or          t3, t3, (0x01 << 6)
    sw          t3, (REG_ADDR_BASE + (0x110d8e << 1))
    
    WREG        (REG_ADDR_BASE + (0x1012e0 << 1)), 0x0200
    WREG        (REG_ADDR_BASE + (0x1012e0 << 1)), 0x0201

    RREG        t3, (REG_ADDR_BASE + (0x110d8e << 1))
    and         t3, t3, ~(0x01 << 6)
    sw          t3, (REG_ADDR_BASE + (0x110d8e << 1))
    
    WREG        (REG_ADDR_BASE + (0x1012e0 << 1)), 0x0000 
    WREG        (REG_ADDR_BASE + (0x1012f0 << 1)), 0x0000
#endif
    
    DELAYUS     10   #//Delay 10us

    jr          ra
    nop

#-------------------------------------------------------------------------------------------------
# MIU_Init_Priority
# @param  None
# @return None
# @note   Init MIU Priority
#-------------------------------------------------------------------------------------------------
MIU_Init_Priority:

# MIU0: generate set priority pulse for "fix priority"

    RREG        t3, (REG_ADDR_BASE + (0x101240 << 1))
    and         t3, t3, 0x0001
    bgtz        t3, miu0_rq0_skip

    RREG        t3, (REG_ADDR_BASE + (0x101240 << 1))
    or          t3, t3, 0x0002
    sw          t3, (REG_ADDR_BASE + (0x101240 << 1))

    RREG        t3, (REG_ADDR_BASE + (0x101240 << 1))
    and         t3, t3, 0xFFFD
    sw          t3, (REG_ADDR_BASE + (0x101240 << 1))
miu0_rq0_skip:

    RREG        t3, (REG_ADDR_BASE + (0x101260 << 1))
    and         t3, t3, 0x0001
    bgtz        t3, miu0_rq1_skip

    RREG        t3, (REG_ADDR_BASE + (0x101260 << 1))
    or          t3, t3, 0x0002
    sw          t3, (REG_ADDR_BASE + (0x101260 << 1))

    RREG        t3, (REG_ADDR_BASE + (0x101260 << 1))
    and         t3, t3, 0xFFFD
    sw          t3, (REG_ADDR_BASE + (0x101260 << 1))
miu0_rq1_skip:

    RREG        t3, (REG_ADDR_BASE + (0x101280 << 1))
    and         t3, t3, 0x0001
    bgtz        t3, miu0_rq2_skip

    RREG        t3, (REG_ADDR_BASE + (0x101280 << 1))
    or          t3, t3, 0x0002
    sw          t3, (REG_ADDR_BASE + (0x101280 << 1))

    RREG        t3, (REG_ADDR_BASE + (0x101280 << 1))
    and         t3, t3, 0xFFFD
    sw          t3, (REG_ADDR_BASE + (0x101280 << 1))
miu0_rq2_skip:

    RREG        t3, (REG_ADDR_BASE + (0x1012A0 << 1))
    and         t3, t3, 0x0001
    bgtz        t3, miu0_rq3_skip

    RREG        t3, (REG_ADDR_BASE + (0x1012A0 << 1))
    or          t3, t3, 0x0002
    sw          t3, (REG_ADDR_BASE + (0x1012A0 << 1))

    RREG        t3, (REG_ADDR_BASE + (0x1012A0 << 1))
    and         t3, t3, 0xFFFD
    sw          t3, (REG_ADDR_BASE + (0x1012A0 << 1))
miu0_rq3_skip:


# MIU1: generate set priority pulse for "fix priority"

    RREG        t3, (REG_ADDR_BASE + (0x100640 << 1))
    and         t3, t3, 0x0001
    bgtz        t3, miu1_rq0_skip

    RREG        t3, (REG_ADDR_BASE + (0x100640 << 1))
    or          t3, t3, 0x0002
    sw          t3, (REG_ADDR_BASE + (0x100640 << 1))

    RREG        t3, (REG_ADDR_BASE + (0x100640 << 1))
    and         t3, t3, 0xFFFD
    sw          t3, (REG_ADDR_BASE + (0x100640 << 1))
miu1_rq0_skip:

    RREG        t3, (REG_ADDR_BASE + (0x100660 << 1))
    and         t3, t3, 0x0001
    bgtz        t3, miu1_rq1_skip

    RREG        t3, (REG_ADDR_BASE + (0x100660 << 1))
    or          t3, t3, 0x0002
    sw          t3, (REG_ADDR_BASE + (0x100660 << 1))

    RREG        t3, (REG_ADDR_BASE + (0x100660 << 1))
    and         t3, t3, 0xFFFD
    sw          t3, (REG_ADDR_BASE + (0x100660 << 1))
miu1_rq1_skip:

    RREG        t3, (REG_ADDR_BASE + (0x100680 << 1))
    and         t3, t3, 0x0001
    bgtz        t3, miu1_rq2_skip

    RREG        t3, (REG_ADDR_BASE + (0x100680 << 1))
    or          t3, t3, 0x0002
    sw          t3, (REG_ADDR_BASE + (0x100680 << 1))

    RREG        t3, (REG_ADDR_BASE + (0x100680 << 1))
    and         t3, t3, 0xFFFD
    sw          t3, (REG_ADDR_BASE + (0x100680 << 1))
miu1_rq2_skip:

    RREG        t3, (REG_ADDR_BASE + (0x1006A0 << 1))
    and         t3, t3, 0x0001
    bgtz        t3, miu1_rq3_skip

    RREG        t3, (REG_ADDR_BASE + (0x1006A0 << 1))
    or          t3, t3, 0x0002
    sw          t3, (REG_ADDR_BASE + (0x1006A0 << 1))

    RREG        t3, (REG_ADDR_BASE + (0x1006A0 << 1))
    and         t3, t3, 0xFFFD
    sw          t3, (REG_ADDR_BASE + (0x1006A0 << 1))
miu1_rq3_skip:

    jr          ra
    nop

#-------------------------------------------------------------------------------------------------
# MIU_Set_Group_Priority
# @param  None
# @return None
# @note   Set Group Priority
#-------------------------------------------------------------------------------------------------
MIU_Set_Group_Priority:

#ifndef CONFIG_MIU0_DRAM_NONE
    #set group priority in MIU_0
    RREG        t3, (REG_ADDR_BASE + (0x1012FE << 1))
    andi        t3, t3, 0xFEFF
    sw          t3, (REG_ADDR_BASE + (0x1012FE << 1))

    RREG        t3, (REG_ADDR_BASE + (0x1012FE << 1))
    and         t3, t3, 0xFF00
    ori         t3, t3, (MIU0_GROUP_PRIORITY & 0xFF)
    sw          t3, (REG_ADDR_BASE + (0x1012FE << 1))

    RREG        t3, (REG_ADDR_BASE + (0x1012FE << 1))
    ori         t3, t3, 0x0100                              #// set group fix priority
    sw          t3, (REG_ADDR_BASE + (0x1012FE << 1))
    and         t3, t3, 0xFEFF
    sw          t3, (REG_ADDR_BASE + (0x1012FE << 1))
#endif
#ifndef CONFIG_MIU1_DRAM_NONE
    #set group priority in MIU_1
    RREG        t3, (REG_ADDR_BASE + (0x1006FE << 1))
    andi        t3, t3, 0xFEFF
    sw          t3, (REG_ADDR_BASE + (0x1006FE << 1))

    RREG        t3, (REG_ADDR_BASE + (0x1006FE << 1))
    andi        t3, t3, 0xFF00
    or          t3, t3, (MIU1_GROUP_PRIORITY & 0xFF)
    sw          t3, (REG_ADDR_BASE + (0x1006FE << 1))

    RREG        t3, (REG_ADDR_BASE + (0x1006FE << 1))
    ori         t3, t3, 0x0100
    sw          t3, (REG_ADDR_BASE + (0x1006FE << 1))
    and         t3, t3, 0xFEFF
    sw          t3, (REG_ADDR_BASE + (0x1006FE << 1))
#endif

    jr          ra
    nop

#-------------------------------------------------------------------------------------------------
# MiuBistTest
# @param
# @return None
# @note
#-------------------------------------------------------------------------------------------------
Miu1_BistTest:
    #miu_1 bist test ---128Mbyte
    WREG        (REG_ADDR_BASE + (0x1012e0 << 1)), 0x0000   #1012e0 //reset bist test
    WREG        (REG_ADDR_BASE + (0x1012f0 << 1)), 0x8000   #1012f0 bit_15=1 choice to MIU_1

    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x0000   #1012e2 //start address base unit   :4k bytes
    WREG_D      (REG_ADDR_BASE + (0x1012e4 << 1)), BIST_LEN
    PUTK        'B'
    PUTK        'I'
    PUTK        'S'
    PUTK        'T'
    PUTK        '1'
    PUTK        '-'
    j           BistTest
    nop

Miu0_BistTest:
    #miu_0 bist test ---128Mbyte
    PUTK        '\n'
    PUTK        '\r'
    PUTK        'B'
    PUTK        'I'
    PUTK        'S'
    PUTK        'T'
    PUTK        '0'
    PUTK        '-'

    WREG        (REG_ADDR_BASE + (0x1012e0 << 1)), 0x0000   #1012e0 //reset bist test
    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x0000   #1012e2 //start address base unit   :4k bytes
    WREG_D      (REG_ADDR_BASE + (0x1012e4 << 1)), BIST_LEN
    WREG        (REG_ADDR_BASE + (0x1012e8 << 1)), 0x5aa5   #1012e8 //bist test pattern

BistTest:
    WREG        (REG_ADDR_BASE + (0x1012e0 << 1)), 0x0003   #bitst test mode:3

ChkBistMiu0:
    RREG        t1, (REG_ADDR_BASE + (0x1012e0 << 1))
    andi        t0, t1, 0x8000
    beqz        t0, ChkBistMiu0
    nop

    andi        t0, t1, 0x6000
    beqz        t0, BistMiu0_OK
    nop

BistMiu0_FAIL:
    PUTK        'F'
    PUTK        'A'
    PUTK        'I'
    PUTK        'L'
    j           BistRet
    nop


BistMiu0_OK:
    PUTK        'O'
    PUTK        'K'

BistRet:
    PUTK        '\n'
    PUTK        '\r'

    jr          ra
    nop

