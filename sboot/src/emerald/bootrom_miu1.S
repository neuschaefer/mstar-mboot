################################################################################
#
# Copyright (c) 2006-2010 MStar Semiconductor, Inc.
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

#include "boot.inc"
#include "ArchDefs.h"
#include "Board.h"
#include "drv_miu_init.h"
#include "MIUSEL_EMERALD_2MIU.h"
#define ENABLE_AUTO_PHASE                   1

    .text
	.set    	noreorder

    .global     BootInitMiu1
    .ent        BootInitMiu1

BootInitMiu1:

    move        t7, ra

    DBGREG      0x0020

#ifdef CONFIG_MSTAR_TITANIA_BD_FPGA

    # swch 3 
    WREG        0xbf006010 0x0000
    WREG        0xbf203d40 0x0000
    WREG        0xBF00578C 0x3c11
    WREG        0xBF005794 0x403c
    WREG        0xBF005788 0x0004

    # swch 4 
    WREG        0xBF202404 0x0000
    WREG        0xBF202404 0x0818
    WREG        0xBF202408 0x0185
    WREG        0xBF20240C 0x0120
    WREG        0xBF202410 0x0833
    WREG        0xBF202414 0x0c33
    WREG        0xBF202418 0x7111
    WREG        0xBF20241C 0x100e
    WREG        0xBF202420 0x0031          
    WREG        0xBF20243C 0x0C01
    WREG        0xBF20243C 0x0C00
    WREG        0xBF202400 0x0008
    WREG        0xBF202400 0x000c
    WREG        0xBF202400 0x000e        
    WREG        0xBF202400 0x001f         
    WREG        0xBF20243C 0x0C08   
    WREG        0xBF202450 0x4000  
    WREG        0xBF202474 0x0001
    WREG        0xBF202478 0x03ff

_CheckDramData:
    lui         t0, 0xBF20
    ori         t0, t0,0x2400
    lw          t1, 0(t0)
    and         t1, t1, 0x8000
    beqz        t1, _CheckDramData
    nop

    move        ra, t7
    jr          ra
    nop

#else


    # MIU1 Software reset
    WREG        (REG_ADDR_BASE + (0x10061e << 1)), 0x0000   #hold miu_0
    WREG        (REG_ADDR_BASE + (0x10061e << 1)), 0x0c01   #
    WREG        (REG_ADDR_BASE + (0x10061e << 1)), 0x0e00   #
    WREG        (REG_ADDR_BASE + (0x100602 << 1)), 0x0000   #

    # MIU1 Request mask
    WREG        (REG_ADDR_BASE + (0x1006F8 << 1)) , 0x8000
    WREG        (REG_ADDR_BASE + (0x100646 << 1)) , 0xFFFE  # mask group0
    WREG        (REG_ADDR_BASE + (0x100666 << 1)) , 0xFFFF  # mask group1
    WREG        (REG_ADDR_BASE + (0x100686 << 1)) , 0xFFFF  # mask group2
    WREG        (REG_ADDR_BASE + (0x1006A6 << 1)) , 0xFFFF  # mask group3

    la          t0, MDrv_WriteRegTbl32
    lui         a0, %hi(MIU1_DDR_Init)
    ori         a0, %lo(MIU1_DDR_Init)
    jal         t0
    nop

    DELAYUS     1000

    # Enable MIU1
    WREG        (REG_ADDR_BASE + (0x10061e << 1)), 0x0c01
    WREG        (REG_ADDR_BASE + (0x10061e << 1)), 0x0c00

    DELAYUS     200                                         # delay 200us

    .if ( MIU_INTERFACE == DDR2_INTERFACE_BGA)
        WREG        (REG_ADDR_BASE + (0x110d80 << 1)), 0x0401
    .else
        WREG        (REG_ADDR_BASE + (0x110d80 << 1)), 0x0201
    .endif
    WREG        (REG_ADDR_BASE + (0x110d82 << 1)), 0xAAAA

    DBGREG      0x0024

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

    DBGREG      0x0027

    #Dram read/write operation check for MIU1
    WREG    (REG_ADDR_BASE + (0x100646 <<1 )) , 0x7FFE  
    WREG    (REG_ADDR_BASE + (0x1012e0 <<1 )) , 0x0000  
    WREG    (REG_ADDR_BASE + (0x1012e2 <<1 )) , 0x0000  
    WREG    (REG_ADDR_BASE + (0x1012e4 <<1 )) , 0x0001  
    WREG    (REG_ADDR_BASE + (0x1012e6 <<1 )) , 0x0000  
    WREG    (REG_ADDR_BASE + (0x1012e8 <<1 )) , 0x5aa5   
    WREG    (REG_ADDR_BASE + (0x1012f0 <<1 )) , 0x8000   

    RREG        t1, (REG_ADDR_BASE + (0x110d8e << 1))
    ori         t1, t1, 0x0040
    sw          t1, (REG_ADDR_BASE + (0x110d8e << 1))

    WREG    (REG_ADDR_BASE + (0x1012e0 <<1 )) , 0x0200
    WREG    (REG_ADDR_BASE + (0x1012e0 <<1 )) , 0x0201   
    WREG    (REG_ADDR_BASE + (0x1012e8 <<1 )) , 0xffff 
    WREG    (REG_ADDR_BASE + (0x1012e8 <<1 )) , 0xffff   

    RREG        t1, (REG_ADDR_BASE + (0x110d8e << 1))
    and         t1, t1, 0xFFBF
    sw          t1, (REG_ADDR_BASE + (0x110d8e << 1))

    DELAYUS     10

    WREG    (REG_ADDR_BASE + (0x1012e0 <<1 )) , 0x0000   
    WREG    (REG_ADDR_BASE + (0x1012e0 <<1 )) , 0x0100 
    WREG    (REG_ADDR_BASE + (0x1012e0 <<1 )) , 0x0101

Miu1_Done:
    RREG        t4, (REG_ADDR_BASE + (0x1012e0 <<1 ))
    andi        t6, t4, 0x8000
    beqz        t6, Miu1_Done

    andi        t0, t1, 0x4000
    beqz        t0, Miu1_Ok
    nop

Miu1_Fail:
    PUTK        'M'
    PUTK        'I'
    PUTK        'U'
    PUTK        '1'
    PUTK        '-'
    PUTK        'F'
    PUTK        'A'
    PUTK        'I'
    PUTK        'L'

Miu1_Ok:
    WREG    (REG_ADDR_BASE + (0x100646 <<1 )) , 0x7FFE   #Un-mask MIU0_group_0
    bal      Miu1_BistTest
    nop

    WREG    (REG_ADDR_BASE + (0x1012e0 << 1)), 0x0000   # stop bist test

#ifdef ENABLE_AUTO_PHASE
    WREG    (REG_ADDR_BASE + (0x100646 <<1 )) , 0x7FFE   #Mask MIU0_group_0
    bal     Miu1_AutoPhase
    nop
#endif
  
    # open all MIU1 request mask (All IP can access MIU resource)
    WREG        (REG_ADDR_BASE + (0x100646 << 1)), 0x0000   #unmask MIU0_group_0
    WREG        (REG_ADDR_BASE + (0x100666 << 1)), 0x0000   #unmask MIU0_group_1
    WREG        (REG_ADDR_BASE + (0x100686 << 1)), 0x0000   #unmask MIU0_group_2
    WREG        (REG_ADDR_BASE + (0x1006a6 << 1)), 0x0000   #unmask MIU0_group_3

    # all MIU1 IP select MIU0 in bringup
    WREG        (REG_ADDR_BASE + (0x1006f0 << 1)), 0x4088   #0x7fff
    WREG        (REG_ADDR_BASE + (0x1006f2 << 1)), 0x0000   #0xffff
    WREG        (REG_ADDR_BASE + (0x1006f4 << 1)), 0x0000   #0xffff
    WREG        (REG_ADDR_BASE + (0x1006f6 << 1)), 0x0000   #0xffff

    DBGREG      0x0029

#endif

    move        ra, t7
    jr          ra
    nop

    .size       BootInitMiu1,.-BootInitMiu1
    .end        BootInitMiu1


#-------------------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------------------
Miu1_AutoPhase:
    WREG        0xBF2025E0, 0x8000                          #1012f0 bit_15=1 choice to MIU_1
    li          s7, (REG_ADDR_BASE + (0x103394 << 1))      # Dummy register to store miu1 DQS phase result
    li          t8, 0                                  # DQS phase result

    WREG        (REG_ADDR_BASE + (0x110DEE << 1)), 0x0077   # set the default phase setting to 0x77
    RREG        t1, (REG_ADDR_BASE + (0x110DEE << 1))       # store the default phase setting to r19
    move        s3, t1                                 

    li          t3, (REG_ADDR_BASE + (0x110DEE << 1))      # reg_0x110DEE  //miu1_phase_reg
    li          t2, (REG_ADDR_BASE + (0x1006E7 << 1))      # reg_0x1006e7  //miu1_dqs_mask_reg
    j           AutoPhaseLoop
    nop
Miu0_AutoPhase:
    WREG        0xBF2025E0, 0x0000                          # 1012f0 bit_15=0 choice to MIU_0
    li          s7, (REG_ADDR_BASE + (0x103390 << 1))      # Dummy register to store miu 0 DQS phase result
    li          t8, 0                                  # DQS phase result

    WREG        (REG_ADDR_BASE + (0x110D6E << 1)), 0x0077   # set the default phase setting to 0x77
    RREG        t1, (REG_ADDR_BASE + (0x110D6E << 1))       # store the default phase setting to r19
    move        s3, t1

    li          t3, (REG_ADDR_BASE + (0x110D6E << 1))      # reg_0x110D6E  //miu0_phase_reg
    li          t2, (REG_ADDR_BASE + (0x1012E7 << 1))      # reg_0x1012e7  //miu0_dqs_mask_reg

AutoPhaseLoop:
    PUTK        '['

    WREG        (REG_ADDR_BASE + (0x1012e4 << 1)), 0x0401   # 1012e4~1012e7 bist test size,   (16 byte/unit)
    WREG        (REG_ADDR_BASE + (0x1012e6 << 1)), 0x0000   # 1012e4~1012e7 bist test size,   (16 byte/unit)
    WREG        (REG_ADDR_BASE + (0x1012e8 << 1)), 0x00FF   # 1012e4~1012e7 bist test pattern

    lui         t5, 0                                   # t5-->tmp_var0=0;  for loop cnt
    lui         s5, 0                                   # s5-->good_phase cnt
    lui         s4, 0                                  # s4-->good_phase_sum
    li          t9, 1                                  # t9-->good_phase bit

StartChk_x1:
    li          t1, 0x55
    sb          t1, (0)(t2)            # set miu0_dqs_mask_reg to 0x55

BistPatternfill:                    #write data into each region respect to bist mode 0x183,0x185,0x187
    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D8E << 1))
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
    li          t6, (REG_ADDR_BASE + (0x110D8E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x20
    sb          k0, (0)(t6)

.if ( ENABLE_MIU1 == 1 )
    WREG        0xbf200DC0, 0x0000
.endif
    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x1000   # 1012e2 bist test start address, (4K byte/unit)
    WREG        0xbf2025C0,0x0000
    li          t1, 0x0083              # bist mode 0x83
    j           BistRWModeTest
    nop

Check_bist85:
.if ( ENABLE_MIU1 == 1 )
    WREG        0xbf200DC0, 0x0000
.endif
    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x1100   # 1012e2 bist test start address, (4K byte/unit)
    WREG        0xbf2025C0,0x0000
    li          t1, 0x0085              # bist mode 0x85
    j           BistRWModeTest
    nop

Check_bist87:
.if ( ENABLE_MIU1 == 1 )
    WREG        0xbf200DC0, 0x0000
.endif
    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x1200   # 1012e2 bist test start address, (4K byte/unit)
    WREG        0xbf2025C0,0x0000
    li          t1, 0x0087              # bist mode 0x87

BistRWModeTest:                         # Read and Write bist
    move        s6, ra
    bal         ModeChangeDelay
    nop
    move        ra, s6

    lui         t0, 0xBF20              # bist test start
    sw          t1, (0x25C0)(t0)

CheckRWBistDone:
    RREG        t1, 0xBF2025C0
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
    li          t6, (REG_ADDR_BASE + (0x110D8E << 1))
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
    li          t6, (REG_ADDR_BASE + (0x110D8E << 1))
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
    li          t6, (REG_ADDR_BASE + (0x110D8E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    andi        t1, t5, 0x0f
    andi        t0, s3, 0xf0  # get the default phase setting
    or          t1, t1, t0
    sw          t1, (0)(t3)

    #ClockUnReset
    li          t6, (REG_ADDR_BASE + (0x110D8E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x20
    sb          k0, (0)(t6)

StartCheck:
.if ( ENABLE_MIU1 == 1 )
    WREG        0xbf200DC0, 0x0000
.endif
    WREG        0xbf2025C0,0x0000
    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x1000   # 1012e2 bist test start address, (4K byte/unit)
    li          t1, 0x0183              # bist mode 0x183
    j           ROBitModeTest
    nop

Check_bist185:
.if ( ENABLE_MIU1 == 1 )
    WREG        0xbf200DC0, 0x0000
.endif
    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x1100   # 1012e2 bist test start address, (4K byte/unit)
    WREG        0xbf2025C0,0x0000
    li          t1, 0x0185              # bist mode 0x185
    j           ROBitModeTest
    nop

Check_bist187:
.if ( ENABLE_MIU1 == 1 )
    WREG        0xbf200DC0, 0x0000
.endif
    WREG        (REG_ADDR_BASE + (0x1012e2 << 1)), 0x1200   # 1012e2 bist test start address, (4K byte/unit)
    WREG        0xbf2025C0,0x0000
    li          t1, 0x0187              # bist mode 0x187

ROBitModeTest:                      # read only bist
    move        s6, ra
#    bal         ModeChangeDelay
#    nop
    move        ra, s6

    lui         t0, 0xBF20              # bist test start
    sw          t1, (0x25C0)(t0)

CheckROBistDone:
    RREG        t1, 0xBF2025C0
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
    li          t6, (REG_ADDR_BASE + (0x110D8E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    move        t1, s3
    j           SetPhaseToDefault_p1
    nop

StorePhase_P1:
    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D8E << 1))
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
    li          t6, (REG_ADDR_BASE + (0x110D8E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x20
    sb          k0, (0)(t6)


    lui         s5, 0                  # s5-->good_phase cnt
    lui         s4, 0                  # s4-->good_phase_sum

    PUTK        ']'
    #PUTK       '\r'
    #PUTK       '\n'
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
    li          t6, (REG_ADDR_BASE + (0x110D8E << 1))
    lb          k0, (0)(t6)
    andi        k0, k0, 0x9F
    ori         k0, k0, 0x60
    sb          k0, (0)(t6)

    move        t1, s3
    j           SetPhaseToDefault
    nop

StorePhase_P0:
    #ClockReset
    li          t6, (REG_ADDR_BASE + (0x110D8E << 1))
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
    li          t6, (REG_ADDR_BASE + (0x110D8E << 1))
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
    WREG        0xbf2025C0, 0x0000
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
    SSSW        0xBF201300, t1
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
    j           BistTest1
    nop

BistTest1:
    WREG        (REG_ADDR_BASE + (0x1012e0 << 1)), 0x0003   #bitst test mode:3

ChkBistMiu1:
    RREG        t1, (REG_ADDR_BASE + (0x1012e0 << 1))
    andi        t0, t1, 0x8000
    beqz        t0, ChkBistMiu1
    nop

    andi        t0, t1, 0x6000
    beqz        t0, BistMiu1_OK
    nop

BistMiu1_FAIL:
    PUTK        'F'
    PUTK        'A'
    PUTK        'I'
    PUTK        'L'
    j           BistMiu1Ret
    nop


BistMiu1_OK:
    PUTK        'O'
    PUTK        'K'

BistMiu1Ret:
    PUTK        '\n'
    PUTK        '\r'

    jr          ra
    nop

