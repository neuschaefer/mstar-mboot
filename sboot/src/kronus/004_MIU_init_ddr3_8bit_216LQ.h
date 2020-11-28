//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all 
// or part of MStar Software is expressly prohibited, unless prior written 
// permission has been granted by MStar. 
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.  
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software. 
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s 
//    confidential information in strictest confidence and not disclose to any
//    third party.  
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.  
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or 
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.  
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>

//swch 4
_RV32_2(0x10121e, 0x0000),   //miu initial
_RV32_2(0x10121e, 0x0c00),
_RV32_2(0x10121e, 0x0c00),
_RV32_2(0x10121e, 0x0c00),
_RV32_2(0x10121e, 0x0c01),   //miu software reset
_RV32_2(0x10121e, 0x0c00),
_RV32_2(0x10121e, 0x0e00),
_RV32_2(0x101202, 0x0000),   //dram type set as '0'

_RV32_2(0x101246, 0x7FFE),   //mask group0
_RV32_2(0x101266, 0xFFFF),   //mask group1
_RV32_2(0x101286, 0xFFFF),   //mask group2
_RV32_2(0x1012A6, 0xFFFF),   //mask group3

_RV32_2(0x110d22, 0x0c10),   //ENLCKDCT , DDRAT[4]=1'b1


//====MEM_PLL0===============
//_RV32_2(0x110d36, 0x8000),   //jc_db: should be 0x4003? // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
//_RV32_2(0x110d34, 0x0300),   //jc_db: should be 0x0500? // loop_div/input_div
//freq=1560 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//_RV32_2(0x110d30, 0x2b52),   // ddfset
//_RV32_2(0x110d32, 0x0035),   // ddrpll_reset/ddrpll_porst/ddrpl_pd
//freq=1560 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#if (ENABLE_MEM1300MHz)
//DDR3 1.3Gbps
_RV32_2(0x110d30, 0xE6CB),
_RV32_2(0x110d32, 0x001F),
_RV32_2(0x110d34, 0x0300),
_RV32_2(0x110d36, 0x4003),

#elif (ENABLE_MEM1600MHz)
//DDR3 1.6Gbps
_RV32_2(0x110d30, 0xEB85),
_RV32_2(0x110d32, 0x0019),
_RV32_2(0x110d34, 0x0300),
_RV32_2(0x110d36, 0x4003),
#elif (ENABLE_MEM1066MHz)
//DDR3 1.066Gbps
_RV32_2(0x110d30, 0xE781),
_RV32_2(0x110d32, 0x0026),
_RV32_2(0x110d34, 0x0300),
_RV32_2(0x110d36, 0x4001),
#else
#error "Invalid Memory Frequency Selection"
#endif

//wait 10
#if (ENABLE_MEM1066MHz)
//===Miu_0 initial ddr3 1560MHz=================
_RV32_2(0x101202, 0x03a3),   //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
_RV32_2(0x101204, 0x000B),   //if I64Mode =0x8b else =0x0b
_RV32_2(0x101206, 0x8440),   //jc_db: should be 0x3420? //refresh cycle=0x20 ,TURN_ON_SCRAMBLE=0x8420
_RV32_2(0x101208, 0x1488),   //jc_db: should be 0x1877? //reg_tRCD
_RV32_2(0x10120a, 0x1B55),   //jc_db: should be 0x1F46? //reg_tRRD
_RV32_2(0x10120c, 0x95a7),   //jc_db: should be 0x5486? //reg_tWL
_RV32_2(0x10120e, 0x406b),   //tRFC

_RV32_2(0x101210, 0x1a50),   //jc_db: should be 0x0e72? //MR0
//_RV32_2(0x101212, 0x4000),   //MR1
_RV32_2(0x101212, 0x4004),   //MR1 DDR3 ODT 120ohm
_RV32_2(0x101214, 0x8010),   //MR2
_RV32_2(0x101216, 0xC000),   //MR3

//_RV32_2(0x101228, 0x8000),   //pack_en is i'b1 when DDR3-16 mode
_RV32_2(0x10122c, 0x0000), //Balance moe:0x0B38 default; 0x1126 enable
//======MIU_ATOP initial======
_RV32_2(0x110d00, 0x0211),   //miu_0_atop  start
_RV32_2(0x110d10, 0xc000),   //reg_drv_another_cmd / reg_drv_cmd
_RV32_2(0x110d18, 0x8600),   //reg_sel_dqs_diff

_RV32_2(0x110d28, 0x0000),   //SSC disable
//_RV32_2(0x110d38, 0x0044),   // DQ0/DQ1 phase / dqs0/dqs1 phase
_RV32_2(0x110d38, 0x1155),
//_RV32_2(0x110d3a, 0x0000),   // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
_RV32_2(0x110d3a, 0x5050),
_RV32_2(0x110d54, 0x0220), //Command driving
_RV32_2(0x110d5c, 0x2222),
_RV32_2(0x110d5e, 0x2222),
_RV32_2(0x110d74, 0x6666),
_RV32_2(0x110d02, 0x0000),
_RV32_2(0x110d3c, 0x6280),   //jc_db: should be 0x0200?
_RV32_2(0x110d3e, 0x0066),   //jc_db: should be 0x0000?
_RV32_2(0x110d0e, 0x02e5),   // 1/2 reg_en_mask
_RV32_2(0x110d0e, 0x02a5),   // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel

//_RV32_2(0x110d6e, 0x0088),   //@1.3G //reg_dll0_ph, reg_dll1_ph
_RV32_2(0x110d6e, 0x0089),   //@1.6G //reg_dll0_ph, reg_dll1_ph

_RV32_2(0x110D1E, 0x6280),   //@1.6G //reg_dll0_ph, reg_dll1_ph


_RV32_2(0x110d6a, 0x0020),   //reg_dll1_code	//refine when DDR_CLK change
_RV32_2(0x110d68, 0x0020),   //reg_dll0_code	//refine when DDR_CLK change
//_RV32_2(0x110d72, 0x3803),   //jc_db: should add this register?
//_RV32_2(0x110d5c, 0x5553),   //jc_db: should add this register? //pad driver
//_RV32_2(0x110d5e, 0x5553),   //jc_db: should add this register? //pad driver
//_RV32_2(0x110d60, 0x2338),   //jc_db: should add this register? //reg_auto calibration
_RV32_2(0x110d60, 0x000c),
_RV32_2(0x110d60, 0x0008),
_RV32_2(0x110d62, 0x007f),
_RV32_2(0x110d64, 0xf200),
_RV32_2(0x110d60, 0x2738),
#else
//===Miu_0 initial ddr3 1560MHz=================
_RV32_2(0x101202, 0x03af),   //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
_RV32_2(0x101204, 0x000c),   //if I64Mode =0x8b else =0x0b
_RV32_2(0x101206, 0x842b),   //jc_db: should be 0x3420? //refresh cycle=0x20 ,TURN_ON_SCRAMBLE=0x8420
_RV32_2(0x101208, 0x1cbb),   //jc_db: should be 0x1877? //reg_tRCD
_RV32_2(0x10120a, 0x27b6),   //jc_db: should be 0x1F46? //reg_tRRD
_RV32_2(0x10120c, 0x95c8),   //jc_db: should be 0x5486? //reg_tWL
_RV32_2(0x10120e, 0xc05a),   //tRFC

_RV32_2(0x101210, 0x1c70),   //jc_db: should be 0x0e72? //MR0
//_RV32_2(0x101212, 0x4000),   //MR1
_RV32_2(0x101212, 0x4040),   //MR1 DDR3 ODT 120ohm
_RV32_2(0x101214, 0x8018),   //MR2
_RV32_2(0x101216, 0xC000),   //MR3

//_RV32_2(0x101228, 0x8000),   //pack_en is i'b1 when DDR3-16 mode
_RV32_2(0x10122c, 0x0000), //Balance moe:0x0B38 default; 0x1126 enable
//======MIU_ATOP initial======
_RV32_2(0x110d00, 0x0211),   //miu_0_atop  start
_RV32_2(0x110d10, 0xc000),   //reg_drv_another_cmd / reg_drv_cmd
_RV32_2(0x110d18, 0x8600),   //reg_sel_dqs_diff
_RV32_2(0x110d28, 0x0000),   //SSC disable
//_RV32_2(0x110d38, 0x0044),   // DQ0/DQ1 phase / dqs0/dqs1 phase
_RV32_2(0x110d38, 0x3377),
//_RV32_2(0x110d3a, 0x0000),   // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
_RV32_2(0x110d3a, 0x6060),
_RV32_2(0x110d54, 0x0220), //Command driving
_RV32_2(0x110d5c, 0x2222),
_RV32_2(0x110d5e, 0x2222),
_RV32_2(0x110d74, 0x6666),
_RV32_2(0x110d02, 0x0000),
_RV32_2(0x110d3c, 0x0680),   //jc_db: should be 0x0200?
_RV32_2(0x110d3e, 0x0000),   //jc_db: should be 0x0000?
_RV32_2(0x110d0e, 0x06e5),   // 1/2 reg_en_mask
_RV32_2(0x110d0e, 0x06a5),   // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel

//_RV32_2(0x110d6e, 0x0088),   //@1.3G //reg_dll0_ph, reg_dll1_ph
_RV32_2(0x110d6e, 0x0008),   //@1.6G //reg_dll0_ph, reg_dll1_ph


_RV32_2(0x110d6a, 0x0020),   //reg_dll1_code	//refine when DDR_CLK change
_RV32_2(0x110d68, 0x0020),   //reg_dll0_code	//refine when DDR_CLK change
//_RV32_2(0x110d72, 0x3803),   //jc_db: should add this register?
//_RV32_2(0x110d5c, 0x5553),   //jc_db: should add this register? //pad driver
//_RV32_2(0x110d5e, 0x5553),   //jc_db: should add this register? //pad driver
//_RV32_2(0x110d60, 0x2338),   //jc_db: should add this register? //reg_auto calibration
_RV32_2(0x110d60, 0x000c),
_RV32_2(0x110d60, 0x0008),
_RV32_2(0x110d62, 0x007f),
_RV32_2(0x110d64, 0xf200),
_RV32_2(0x110d60, 0x2738),
#endif


//enable miu_0
_RV32_2(0x10121e, 0x0c01),
//_RV32_2(0x10121e, 0x0c00),
_RV32_2(0x10121e, 0x0c08),

//wait  1   // delay 1ms
_RV32_2(0x110d00, 0x0201),
_RV32_2(0x110d02, 0xaaaa),   //8x mode:0xAAAA , 4x mode :0xCCCC


_RV32_2(0x110d08, 0xFFFF),  //rx enable

_RV32_2(0x101200, 0x0000),

_RV32_2(0x101200, 0x0008),

_RV32_2(0x101200, 0x000c),

//wait 1    // delay 1ms
_RV32_2(0x101200, 0x000e),

//wait 1    // delay 1ms
_RV32_2(0x101200, 0x001f), //jc_db: should be 0x000f?


//wait 10   //check reg_101200 #15 for //wait initial done // delay 10ms

#if (ENABLE_MEM1066MHz)
_RV32_2(0x1012e0, 0x0000),
_RV32_2(0x1012e4, 0x0000),
_RV32_2(0x1012e6, 0x0200),
_RV32_2(0x1012e2, 0x0000),
_RV32_2(0x1012e8, 0x00FF),
_RV32_2(0x101e1e, 0x0002),
#else
_RV32_2(0x1012e0, 0x0000),
_RV32_2(0x1012e4, 0x0000),
_RV32_2(0x1012e6, 0x0020),
_RV32_2(0x1012e8, 0xFF00),
#endif
//open all mask
//_RV32_2(0x101246, 0x0000),   //unmask group0
//_RV32_2(0x101266, 0x0000),   //unmask group1
//_RV32_2(0x101286, 0x0000),   //unmask group2
//_RV32_2(0x1012A6, 0x0000),   //unmask group3 //jc_db: should u4 have group3

