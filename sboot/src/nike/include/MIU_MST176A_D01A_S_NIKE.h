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

#ifndef _MIU_MST176A_D01A_S_NIKE_H_
#define _MIU_MST176A_D01A_S_NIKE_H_

#if ((ENABLE_MSTAR_BD_MST176A_D01A_S_NIKE == 1) || \
     (ENABLE_MSTAR_BD_MST176A_D01A_S_NIKEU == 1) || \
     (ENABLE_MSTAR_BD_MST176A_D01A_S_NIKEC == 1))

const MS_REG_INIT MIU0_DDR_Init[] =
{
#if defined(CONFIG_MIU0_DDR3_1333)

    _RV32_2(0x110d3a, 0x0000),      //mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110d36, 0x4000),      //mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110d34, 0x0000),      //loop_div/input_div
    _RV32_2(0x110d30, 0x114a),      //ddfset
    _RV32_2(0x110d32, 0x0029),      //ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x110d2e, 0x0800),      //PLL SELECT locked by PLL clock
    _RV32_2(0x110d2c, 0x0100),      //PLL SELECT locked by PLL clock
    _RV32_2(0x101202, 0xf3a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x101204, 0x000a),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x101206, 0x0538),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x101208, 0x1899),      //reg_tRCD
    _RV32_2(0x10120a, 0x2155),      //reg_tRRD
    _RV32_2(0x10120c, 0x95a8),      //reg_tWL
    _RV32_2(0x10120e, 0x40c8),      //tRFC (512MB)
    _RV32_2(0x101210, 0x1a50),      //MR0
    _RV32_2(0x101212, 0x4004),      //MR1
    _RV32_2(0x101214, 0x8010),      //MR2
    _RV32_2(0x101216, 0xC000),      //MR3
    _RV32_2(0x10122c, 0x0000),      //Address Balance Mode

                                    //bandwidth setting
    _RV32_2(0x101242, 0x0008),      //(member limit setting for group 0)
    _RV32_2(0x101244, 0x0200),      //(timeout setting for group 0)
    _RV32_2(0x101262, 0x0008),      //(member limit setting for group 1)
    _RV32_2(0x101264, 0x0200),      //(timeout setting for group 1)
    _RV32_2(0x101282, 0x0008),      //(member limit setting for group 2)
    _RV32_2(0x101284, 0x0200),      //(timeout setting for group 2)
    _RV32_2(0x1012a2, 0x0008),      //(member limit setting for group 3)
    _RV32_2(0x1012a4, 0x0200),      //(timeout setting for group 3)
    _RV32_2(0x101240, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group0)
    _RV32_2(0x101260, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group1)
    _RV32_2(0x101280, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group2)
    _RV32_2(0x1012a0, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group3)

    _RV32_2(0x1012d4, 0x0000),      // turn off read_last_done_z_bypass

    _RV32_2(0x110d54, 0xc000),      //miu_0_atop  start
    _RV32_2(0x110d00, 0x0200),
    _RV32_2(0x110d02, 0xaaaa),
    _RV32_2(0x110d04, 0x0080),
    _RV32_2(0x110d3c, 0x3155),
    _RV32_2(0x110d14, 0x0000),
    _RV32_2(0x110d3e, 0x1211),
    _RV32_2(0x110d4c, 0x1111),
    _RV32_2(0x110d50, 0x1111),
    _RV32_2(0x110d38, 0x0033),
    _RV32_2(0x110d3a, 0x7070),
    _RV32_2(0x110d48, 0x0000),
    _RV32_2(0x110d4a, 0x0000),
    _RV32_2(0x110d52, 0x0000),
    _RV32_2(0x110d6c, 0x6666),
    _RV32_2(0x110d6e, 0x6666),
    _RV32_2(0x110d0e, 0x00e7),
    _RV32_2(0x110d0e, 0x00a7),
    _RV32_2(0x110d0e, 0x00e7),
    _RV32_2(0x1012e4, 0x0001),      // test one data
    _RV32_2(0x1012e0, 0x0200),      // test write only
    _RV32_2(0x1012e0, 0x0201),      // test write only
    _RV32_2(0x1012e0, 0x0201),      // test write only
    _RV32_2(0x1012e0, 0x0000),      // retrn to original state
    _RV32_2(0x1012e4, 0x0000),      // retrn to original state
    _RV32_2(0x110d0e, 0x00a7),
    _RV32_2(0x110d00, 0x0038),
    _RV32_2(0x110d00, 0x0030),
    _RV32_2(0x110d00, 0x0020),
    _RV32_2(0x110d7e, 0x0000),

    _RV32_2(0x110d00, 0x0200),

    _RV32_2(0x110d60, 0x2370),  //DLL Setting
    _RV32_2(0x110d62, 0x0032),
    _RV32_2(0x110d64, 0xf200),
    _RV32_2(0x110d66, 0x0000),
    _RV32_2(0x110d68, 0x0020),
    _RV32_2(0x110d6a, 0x0020),

#elif defined(CONFIG_MIU0_DDR3_1666)

    _RV32_2(0x110d3a, 0x0000),      //mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110d36, 0x4000),      //mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110d34, 0x0000),      //loop_div/input_div
    _RV32_2(0x110d30, 0xe8ba),      //ddfset
    _RV32_2(0x110d32, 0x0022),      //ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x110d22, 0x2000),
    _RV32_2(0x110d24, 0x2200),
    _RV32_2(0x110d20, 0x0030),

    _RV32_2(0x101202, 0xf3a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x101204, 0x000c),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x101206, 0x0c30),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x101208, 0x1cbb),      //reg_tRCD
    _RV32_2(0x10120a, 0x2766),      //reg_tRRD
    _RV32_2(0x10120c, 0xb6c8),      //reg_tWL
    _RV32_2(0x10120e, 0x40f0),      //tRFC (512MB)
    _RV32_2(0x101210, 0x1d70),      //MR0
    _RV32_2(0x101212, 0x4004),      //MR1
    _RV32_2(0x101214, 0x8018),      //MR2
    _RV32_2(0x101216, 0xC000),      //MR3
    _RV32_2(0x10122c, 0x0000),      //Address Balance Mode

                                    //bandwidth setting
    _RV32_2(0x101242, 0x0008),      //(member limit setting for group 0)
    _RV32_2(0x101244, 0x0200),      //(timeout setting for group 0)
    _RV32_2(0x101262, 0x0008),      //(member limit setting for group 1)
    _RV32_2(0x101264, 0x0200),      //(timeout setting for group 1)
    _RV32_2(0x101282, 0x0008),      //(member limit setting for group 2)
    _RV32_2(0x101284, 0x0200),      //(timeout setting for group 2)
    _RV32_2(0x1012a2, 0x0008),      //(member limit setting for group 3)
    _RV32_2(0x1012a4, 0x0200),      //(timeout setting for group 3)
    _RV32_2(0x101240, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group0)
    _RV32_2(0x101260, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group1)
    _RV32_2(0x101280, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group2)
    _RV32_2(0x1012a0, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group3)

    _RV32_2(0x110d54, 0x8000),      //miu_0_atop  start
    _RV32_2(0x110d00, 0x0200),
    _RV32_2(0x110d02, 0xaaaa),
    _RV32_2(0x110d04, 0x0080),
    _RV32_2(0x110d3c, 0x0133),
    _RV32_2(0x110d14, 0x0000),
    _RV32_2(0x110d3e, 0x1011),
    _RV32_2(0x110d4c, 0x1133),
    _RV32_2(0x110d50, 0x1111),
    _RV32_2(0x110d38, 0x0043),
    _RV32_2(0x110d3a, 0x9094),
    _RV32_2(0x110d48, 0x0033),
    _RV32_2(0x110d4a, 0x0002),
    _RV32_2(0x110d52, 0x0000),
    _RV32_2(0x110d5c, 0x6666),
    _RV32_2(0x110d5e, 0x6666),
    _RV32_2(0x110d6c, 0xaaaa),
    _RV32_2(0x110d6e, 0xaaaa),
    _RV32_2(0x110d0e, 0x00eb),
    _RV32_2(0x110d0e, 0x00ab),
    _RV32_2(0x110d0e, 0x00eb),
    _RV32_2(0x1012e2, 0x0001),      // test one data
    _RV32_2(0x1012e0, 0x0200),      // test write only
    _RV32_2(0x1012e0, 0x0201),      // test write only
    _RV32_2(0x1012e0, 0x0201),      // test write only
    _RV32_2(0x1012e0, 0x0000),      // retrn to original state
    _RV32_2(0x1012e2, 0x0000),      // retrn to original state
    _RV32_2(0x110d0e, 0x00ab),
    _RV32_2(0x110d72, 0x0004),
    _RV32_2(0x110d7e, 0x0000),

    _RV32_2(0x110d00, 0x0200),

    _RV32_2(0x110d60, 0x2370),  //DLL Setting
    _RV32_2(0x110d62, 0x0032),
    _RV32_2(0x110d64, 0xf200),
    _RV32_2(0x110d66, 0x0000),
    _RV32_2(0x110d68, 0x0020),
    _RV32_2(0x110d6a, 0x0020),

#elif defined(CONFIG_MIU0_DDR3_1866)

    _RV32_2(0x110d3a, 0x0000),      //mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110d36, 0x4000),      //mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110d34, 0x0000),      //loop_div/input_div
    _RV32_2(0x110d30, 0xf45a),      //ddfset
    _RV32_2(0x110d32, 0x001d),      //ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x110d22, 0x2000),
    _RV32_2(0x110d24, 0x2200),
    _RV32_2(0x110d20, 0x0030),

    _RV32_2(0x101202, 0xf3a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x101204, 0x000c),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x101206, 0x0d38),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x101208, 0x20dd),      //reg_tRCD
    _RV32_2(0x10120a, 0x2e76),      //reg_tRRD
    _RV32_2(0x10120c, 0xc7e9),      //reg_tWL
    _RV32_2(0x10120e, 0x4120),      //tRFC (512MB)
    _RV32_2(0x101210, 0x1f14),      //MR0
    _RV32_2(0x101212, 0x4004),      //MR1
    _RV32_2(0x101214, 0x8020),      //MR2
    _RV32_2(0x101216, 0xC000),      //MR3
    _RV32_2(0x10122c, 0x0000),      //Address Balance Mode

                                    //bandwidth setting
    _RV32_2(0x101242, 0x0008),      //(member limit setting for group 0)
    _RV32_2(0x101244, 0x0200),      //(timeout setting for group 0)
    _RV32_2(0x101262, 0x0008),      //(member limit setting for group 1)
    _RV32_2(0x101264, 0x0200),      //(timeout setting for group 1)
    _RV32_2(0x101282, 0x0008),      //(member limit setting for group 2)
    _RV32_2(0x101284, 0x0200),      //(timeout setting for group 2)
    _RV32_2(0x1012a2, 0x0008),      //(member limit setting for group 3)
    _RV32_2(0x1012a4, 0x0200),      //(timeout setting for group 3)
    _RV32_2(0x101240, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group0)
    _RV32_2(0x101260, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group1)
    _RV32_2(0x101280, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group2)
    _RV32_2(0x1012a0, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group3)

    _RV32_2(0x1012d4, 0x0000),      // turn off read_last_done_z_bypass

    _RV32_2(0x110d54, 0x8000),      //miu_0_atop start
    _RV32_2(0x110d00, 0x0400),
    _RV32_2(0x110d02, 0xaaaa),
    _RV32_2(0x110d04, 0x0080),
    _RV32_2(0x110d3c, 0x0344),
    _RV32_2(0x110d3e, 0x1033),
    _RV32_2(0x110d4c, 0x0000),
    _RV32_2(0x110d50, 0x1111),
    _RV32_2(0x110d36, 0x4000),
    _RV32_2(0x110d38, 0x0033),
    _RV32_2(0x110d3a, 0x0004),
    _RV32_2(0x110d48, 0x0000),
    _RV32_2(0x110d4a, 0x0000),
    _RV32_2(0x110d52, 0x0000),
    _RV32_2(0x110d5c, 0x6666),
    _RV32_2(0x110d5e, 0x6666),
    _RV32_2(0x110d6c, 0x77aa),
    _RV32_2(0x110d6e, 0x77aa),
    _RV32_2(0x110d0e, 0x00ed),
    _RV32_2(0x110d0e, 0x00ad),
    _RV32_2(0x110d0e, 0x00ed),
    _RV32_2(0x1012e4, 0x0001),      // test one data
    _RV32_2(0x1012e0, 0x0200),      // test write only
    _RV32_2(0x1012e0, 0x0201),      // test write only
    _RV32_2(0x1012e0, 0x0201),      // test write only
    _RV32_2(0x1012e0, 0x0000),      // retrn to original state
    _RV32_2(0x1012e4, 0x0000),      // retrn to original state
    _RV32_2(0x110d0e, 0x00ad),
    _RV32_2(0x110d72, 0x0005),
    _RV32_2(0x110d7e, 0x0000),

    _RV32_2(0x110d00, 0x0400),

    _RV32_2(0x110d60, 0x2370),      //DLL Setting
    _RV32_2(0x110d62, 0x0032),
    _RV32_2(0x110d64, 0xf200),
    _RV32_2(0x110d66, 0x0000),
    _RV32_2(0x110d68, 0x0020),
    _RV32_2(0x110d6a, 0x0020),

#elif defined(CONFIG_MIU0_DDR3_2133)

    _RV32_2(0x110d3a, 0x0000),      //mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110d36, 0x4000),      //mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110d34, 0x0000),      //loop_div/input_div
    _RV32_2(0x110d30, 0xec8e),      //ddfset
    _RV32_2(0x110d32, 0x0019),      //ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x110d22, 0x2000),
    _RV32_2(0x110d24, 0x2200),

    _RV32_2(0x101202, 0xf3a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x101204, 0x000d),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x101206, 0x0640),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x101208, 0x24ee),      //reg_tRCD
    _RV32_2(0x10120a, 0x3487),      //reg_tRRD
    _RV32_2(0x10120c, 0xc80a),      //reg_tWL
    _RV32_2(0x10120e, 0xc142),      //tRFC (512MB)
    _RV32_2(0x101210, 0x1124),      //MR0
    _RV32_2(0x101212, 0x4004),      //MR1
    _RV32_2(0x101214, 0x8028),      //MR2
    _RV32_2(0x101216, 0xC000),      //MR3
    _RV32_2(0x10122c, 0x0000),      //Address Balance Mode

                                    //bandwidth setting
    _RV32_2(0x101242, 0x0008),      //(member limit setting for group 0)
    _RV32_2(0x101244, 0x0200),      //(timeout setting for group 0)
    _RV32_2(0x101262, 0x0008),      //(member limit setting for group 1)
    _RV32_2(0x101264, 0x0200),      //(timeout setting for group 1)
    _RV32_2(0x101282, 0x0008),      //(member limit setting for group 2)
    _RV32_2(0x101284, 0x0200),      //(timeout setting for group 2)
    _RV32_2(0x1012a2, 0x0008),      //(member limit setting for group 3)
    _RV32_2(0x1012a4, 0x0200),      //(timeout setting for group 3)
    _RV32_2(0x101240, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group0)
    _RV32_2(0x101260, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group1)
    _RV32_2(0x101280, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group2)
    _RV32_2(0x1012a0, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group3)

    _RV32_2(0x1012d4, 0x0000),      // turn off read_last_done_z_bypass

    _RV32_2(0x110d54, 0xc000),      //miu_0_atop start
    _RV32_2(0x110d00, 0x0200),
    _RV32_2(0x110d02, 0xaaaa),
    _RV32_2(0x110d04, 0x0080),
    _RV32_2(0x110d3c, 0x1522),
    _RV32_2(0x110d3e, 0x1055),
    _RV32_2(0x110d4c, 0x5511),
    _RV32_2(0x110d50, 0x1111),
    _RV32_2(0x110d36, 0x4002),
    _RV32_2(0x110d38, 0x0033),
    _RV32_2(0x110d3a, 0x0002),
    _RV32_2(0x110d48, 0x0033),
    _RV32_2(0x110d4a, 0x0002),
    _RV32_2(0x110d52, 0x0000),
    _RV32_2(0x110d6c, 0x9999),
    _RV32_2(0x110d6e, 0x9999),
    _RV32_2(0x110d72, 0x0003),
    _RV32_2(0x110d0e, 0x00ef),
    _RV32_2(0x110d0e, 0x00af),
    _RV32_2(0x110d0e, 0x00ef),
    _RV32_2(0x1012e4, 0x0001),      // test one data
    _RV32_2(0x1012e0, 0x0200),      // test write only
    _RV32_2(0x1012e0, 0x0201),      // test write only
    _RV32_2(0x1012e0, 0x0201),      // test write only
    _RV32_2(0x1012e0, 0x0000),      // retrn to original state
    _RV32_2(0x1012e4, 0x0000),      // retrn to original state
    _RV32_2(0x110d0e, 0x00af),
    _RV32_2(0x110d7e, 0x0000),
    _RV32_2(0x110d00, 0x0200),

    _RV32_2(0x110d60, 0x2370),      //DLL SETTING
    _RV32_2(0x110d62, 0x0032),
    _RV32_2(0x110d64, 0xf200),
    _RV32_2(0x110d66, 0x0000),
    _RV32_2(0x110d68, 0x0020),
    _RV32_2(0x110d6a, 0x0020),


#else
    #error "Invalid DRAM Setting"
#endif

    _END_OF_TBL32_,
    MIU_VER
};

#ifndef CONFIG_MIU1_DRAM_NONE
const MS_REG_INIT MIU1_DDR_Init[] =
{
#if defined(CONFIG_MIU1_DDR3_1333)

    _RV32_2(0x110dba, 0x0000),      //mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110db6, 0x4000),      //mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110db4, 0x0000),      //loop_div/input_div
    _RV32_2(0x110db0, 0x114a),      //ddfset
    _RV32_2(0x110db2, 0x0029),      //ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x110d2e, 0x0800),      //PLL SELECT locked by PLL clock
    _RV32_2(0x110d2c, 0x0100),      //PLL SELECT locked by PLL clock
    _RV32_2(0x100602, 0xf3a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x100604, 0x000a),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x100606, 0x0538),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x100608, 0x1899),      //reg_tRCD
    _RV32_2(0x10060a, 0x2155),      //reg_tRRD
    _RV32_2(0x10060c, 0x95a8),      //reg_tWL
    _RV32_2(0x10060e, 0x40c8),      //tRFC (512MB)
    _RV32_2(0x100610, 0x1a50),      //MR0
    _RV32_2(0x100612, 0x4004),      //MR1
    _RV32_2(0x100614, 0x8010),      //MR2
    _RV32_2(0x100616, 0xC000),      //MR3
    _RV32_2(0x10062c, 0x0000),      //Address Balance Mode

                                    //bandwidth setting
    _RV32_2(0x100642, 0x0008),      //(member limit setting for group 0)
    _RV32_2(0x100644, 0x0200),      //(timeout setting for group 0)
    _RV32_2(0x100662, 0x0008),      //(member limit setting for group 1)
    _RV32_2(0x100664, 0x0200),      //(timeout setting for group 1)
    _RV32_2(0x100682, 0x0008),      //(member limit setting for group 2)
    _RV32_2(0x100684, 0x0200),      //(timeout setting for group 2)
    _RV32_2(0x1006a2, 0x0008),      //(member limit setting for group 3)
    _RV32_2(0x1006a4, 0x0200),      //(timeout setting for group 3)
    _RV32_2(0x100640, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group0)
    _RV32_2(0x100660, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group1)
    _RV32_2(0x100680, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group2)
    _RV32_2(0x1006a0, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group3)

    _RV32_2(0x1006d4, 0x0000),      // turn off read_last_done_z_bypass

    _RV32_2(0x110dd4, 0xc000),      //miu_0_atop  start
    _RV32_2(0x110d80, 0x0200),
    _RV32_2(0x110d82, 0xaaaa),
    _RV32_2(0x110d84, 0x0080),
    _RV32_2(0x110dbc, 0x3155),
    _RV32_2(0x110d94, 0x0000),
    _RV32_2(0x110dbe, 0x1211),
    _RV32_2(0x110dcc, 0x1111),
    _RV32_2(0x110dd0, 0x1111),
    _RV32_2(0x110db8, 0x0033),
    _RV32_2(0x110dba, 0x7070),
    _RV32_2(0x110dc8, 0x0000),
    _RV32_2(0x110dca, 0x0000),
    _RV32_2(0x110dd2, 0x0000),
    _RV32_2(0x110dec, 0x6666),
    _RV32_2(0x110dee, 0x6666),
    _RV32_2(0x110d8e, 0x00e7),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
    _RV32_2(0x110d8e, 0x00a7),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
    _RV32_2(0x110d8e, 0x00e7),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
    _RV32_2(0x110df0, 0x8000),      // change to MIU1
    _RV32_2(0x1012e4, 0x0001),      // test one data
    _RV32_2(0x1012e0, 0x0200),      // test write only
    _RV32_2(0x1012e0, 0x0201),      // test write only
    _RV32_2(0x1012e0, 0x0201),      // test write only
    _RV32_2(0x1012e0, 0x0000),      // retrn to original state
    _RV32_2(0x1012e4, 0x0000),      // retrn to original state
    _RV32_2(0x110df0, 0x0000),      // change to MIU0
    _RV32_2(0x110d8e, 0x00a7),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
    _RV32_2(0x110d80, 0x0038),
    _RV32_2(0x110d80, 0x0030),
    _RV32_2(0x110d80, 0x0020),
    _RV32_2(0x110dfe, 0x0000),

    _RV32_2(0x110d80, 0x0200),

    _RV32_2(0x110de0, 0x2370),  //DLL Setting
    _RV32_2(0x110de2, 0x0032),
    _RV32_2(0x110de4, 0xf200),
    _RV32_2(0x110de6, 0x0000),
    _RV32_2(0x110de8, 0x0020),
    _RV32_2(0x110dea, 0x0020),

#elif defined(CONFIG_MIU1_DDR3_1666)

    _RV32_2(0x110dba, 0x0000),      //mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110db6, 0x4000),      //mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110db4, 0x0000),      //loop_div/input_div
    _RV32_2(0x110db0, 0xe8ba),      //ddfset
    _RV32_2(0x110db2, 0x0022),      //ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x110da2, 0x2000),
    _RV32_2(0x110da4, 0x2200),
    _RV32_2(0x110da0, 0x0030),

    _RV32_2(0x100602, 0xf3a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x100604, 0x000c),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x100606, 0x0c30),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x100608, 0x1cbb),      //reg_tRCD
    _RV32_2(0x10060a, 0x2766),      //reg_tRRD
    _RV32_2(0x10060c, 0xb6c8),      //reg_tWL
    _RV32_2(0x10060e, 0x40f0),      //tRFC (512MB)
    _RV32_2(0x100610, 0x1d70),      //MR0
    _RV32_2(0x100612, 0x4004),      //MR1
    _RV32_2(0x100614, 0x8018),      //MR2
    _RV32_2(0x100616, 0xC000),      //MR3
    _RV32_2(0x10062c, 0x0000),      //Address Balance Mode

                                    //bandwidth setting
    _RV32_2(0x100642, 0x0008),      //(member limit setting for group 0)
    _RV32_2(0x100644, 0x0200),      //(timeout setting for group 0)
    _RV32_2(0x100662, 0x0008),      //(member limit setting for group 1)
    _RV32_2(0x100664, 0x0200),      //(timeout setting for group 1)
    _RV32_2(0x100682, 0x0008),      //(member limit setting for group 2)
    _RV32_2(0x100684, 0x0200),      //(timeout setting for group 2)
    _RV32_2(0x1006a2, 0x0008),      //(member limit setting for group 3)
    _RV32_2(0x1006a4, 0x0200),      //(timeout setting for group 3)
    _RV32_2(0x100640, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group0)
    _RV32_2(0x100660, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group1)
    _RV32_2(0x100680, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group2)
    _RV32_2(0x1006a0, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group3)

    _RV32_2(0x110dd4, 0x8000),      //miu_0_atop  start
    _RV32_2(0x110d80, 0x0200),
    _RV32_2(0x110d82, 0xaaaa),
    _RV32_2(0x110d84, 0x0080),
    _RV32_2(0x110dbc, 0x0133),
    _RV32_2(0x110d94, 0x0000),
    _RV32_2(0x110dbe, 0x1011),
    _RV32_2(0x110dcc, 0x1133),
    _RV32_2(0x110dd0, 0x1111),
    _RV32_2(0x110db8, 0x0043),
    _RV32_2(0x110dba, 0x9094),
    _RV32_2(0x110dc8, 0x0033),
    _RV32_2(0x110dca, 0x0002),
    _RV32_2(0x110dd2, 0x0000),
    _RV32_2(0x110ddc, 0x6666),
    _RV32_2(0x110dde, 0x6666),
    _RV32_2(0x110dec, 0xaaaa),
    _RV32_2(0x110dee, 0xaaaa),
    _RV32_2(0x110d8e, 0x00eb),
    _RV32_2(0x110d8e, 0x00ab),
    _RV32_2(0x110d8e, 0x00eb),
    _RV32_2(0x110df0, 0x8000),      // change to MIU1
    _RV32_2(0x1012e2, 0x0001),      // test one data
    _RV32_2(0x1012e0, 0x0200),      // test write only
    _RV32_2(0x1012e0, 0x0201),      // test write only
    _RV32_2(0x1012e0, 0x0201),      // test write only
    _RV32_2(0x1012e0, 0x0000),      // retrn to original state
    _RV32_2(0x1012e2, 0x0000),      // retrn to original state
    _RV32_2(0x110df0, 0x0000),      // change to MIU0
    _RV32_2(0x110d8e, 0x00ab),
    _RV32_2(0x110df2, 0x0004),
    _RV32_2(0x110dfe, 0x0000),

    _RV32_2(0x110d80, 0x0200),

    _RV32_2(0x110de0, 0x2370),  //DLL Setting
    _RV32_2(0x110de2, 0x0032),
    _RV32_2(0x110de4, 0xf200),
    _RV32_2(0x110de6, 0x0000),
    _RV32_2(0x110de8, 0x0020),
    _RV32_2(0x110dea, 0x0020),

#elif defined(CONFIG_MIU1_DDR3_1866)

    _RV32_2(0x110dba, 0x0000),      //mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110db6, 0x4000),      //mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110db4, 0x0000),      //loop_div/input_div
    _RV32_2(0x110db0, 0xf45a),      //ddfset
    _RV32_2(0x110db2, 0x001d),      //ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x110da2, 0x2000),
    _RV32_2(0x110da4, 0x2000),
    _RV32_2(0x110da0, 0x0030),

    _RV32_2(0x100602, 0xf3a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x100604, 0x000c),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x100606, 0x0d38),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x100608, 0x20dd),      //reg_tRCD
    _RV32_2(0x10060a, 0x2e76),      //reg_tRRD
    _RV32_2(0x10060c, 0xc7e9),      //reg_tWL
    _RV32_2(0x10060e, 0x4120),      //tRFC (512MB)
    _RV32_2(0x100610, 0x1f14),      //MR0
    _RV32_2(0x100612, 0x4004),      //MR1
    _RV32_2(0x100614, 0x8020),      //MR2
    _RV32_2(0x100616, 0xC000),      //MR3
    _RV32_2(0x10062c, 0x0000),      //Address Balance Mode

                                    //bandwidth setting
    _RV32_2(0x100642, 0x0008),      //(member limit setting for group 0)
    _RV32_2(0x100644, 0x0200),      //(timeout setting for group 0)
    _RV32_2(0x100662, 0x0008),      //(member limit setting for group 1)
    _RV32_2(0x100664, 0x0200),      //(timeout setting for group 1)
    _RV32_2(0x100682, 0x0008),      //(member limit setting for group 2)
    _RV32_2(0x100684, 0x0200),      //(timeout setting for group 2)
    _RV32_2(0x1006a2, 0x0008),      //(member limit setting for group 3)
    _RV32_2(0x1006a4, 0x0200),      //(timeout setting for group 3)
    _RV32_2(0x100640, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group0)
    _RV32_2(0x100660, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group1)
    _RV32_2(0x100680, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group2)
    _RV32_2(0x1006a0, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group3)

    _RV32_2(0x1006d4, 0x0000),      // turn off read_last_done_z_bypass

    _RV32_2(0x110dd4, 0x8000),      //miu_0_atop  start
    _RV32_2(0x110d80, 0x0400),
    _RV32_2(0x110d82, 0xaaaa),
    _RV32_2(0x110d84, 0x0080),
    _RV32_2(0x110dbc, 0x0344),
    _RV32_2(0x110dbe, 0x1033),
    _RV32_2(0x110dcc, 0x0000),
    _RV32_2(0x110dd0, 0x1111),
    _RV32_2(0x110db6, 0x4000),
    _RV32_2(0x110db8, 0x0033),
    _RV32_2(0x110dba, 0x0004),
    _RV32_2(0x110dc8, 0x0000),
    _RV32_2(0x110dca, 0x0000),
    _RV32_2(0x110dd2, 0x0000),
    _RV32_2(0x110ddc, 0x6666),
    _RV32_2(0x110dde, 0x6666),
    _RV32_2(0x110dec, 0x7799),
    _RV32_2(0x110dee, 0x7799),
    _RV32_2(0x110de2, 0x0003),
    _RV32_2(0x110d8e, 0x00ed),
    _RV32_2(0x110d8e, 0x00ad),
    _RV32_2(0x110d8e, 0x00ed),
    _RV32_2(0x110df0, 0x8000),      // change to MIU1
    _RV32_2(0x1012e4, 0x0001),      // test one data
    _RV32_2(0x1012e0, 0x0200),      // test write only
    _RV32_2(0x1012e0, 0x0201),      // test write only
    _RV32_2(0x1012e0, 0x0201),      // test write only
    _RV32_2(0x1012e0, 0x0000),      // retrn to original state
    _RV32_2(0x1012e4, 0x0000),      // retrn to original state
    _RV32_2(0x110df0, 0x0000),      // change to MIU0
    _RV32_2(0x110d8e, 0x00ad),
    _RV32_2(0x110df2, 0x0005),
    _RV32_2(0x110dfe, 0x0000),

    _RV32_2(0x110d80, 0x0400),

    _RV32_2(0x110de0, 0x2370),      //DLL Setting
    _RV32_2(0x110de2, 0x0032),
    _RV32_2(0x110de4, 0xf200),
    _RV32_2(0x110de6, 0x0000),
    _RV32_2(0x110de8, 0x0020),
    _RV32_2(0x110dea, 0x0020),

#elif defined(CONFIG_MIU1_DDR3_2133)

    _RV32_2(0x110dba, 0x0000),      //mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110db6, 0x4000),      //mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110db4, 0x0000),      //loop_div/input_div
    _RV32_2(0x110db0, 0xec8e),      //ddfset
    _RV32_2(0x110db2, 0x0019),      //ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x110da0, 0x0030),
    _RV32_2(0x110da2, 0x2000),
    _RV32_2(0x110da4, 0x2000),

    _RV32_2(0x100602, 0xf3a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x100604, 0x000d),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x100606, 0x0640),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x100608, 0x24ee),      //reg_tRCD
    _RV32_2(0x10060a, 0x3487),      //reg_tRRD
    _RV32_2(0x10060c, 0xc80a),      //reg_tWL
    _RV32_2(0x10060e, 0xc142),      //tRFC (512MB)
    _RV32_2(0x100610, 0x1124),      //MR0
    _RV32_2(0x100612, 0x4004),      //MR1
    _RV32_2(0x100614, 0x8028),      //MR2
    _RV32_2(0x100616, 0xC000),      //MR3
    _RV32_2(0x10062c, 0x0000),      //Address Balance Mode

                                    //bandwidth setting
    _RV32_2(0x100642, 0x0008),      //(member limit setting for group 0)
    _RV32_2(0x100644, 0x0200),      //(timeout setting for group 0)
    _RV32_2(0x100662, 0x0008),      //(member limit setting for group 1)
    _RV32_2(0x100664, 0x0200),      //(timeout setting for group 1)
    _RV32_2(0x100682, 0x0008),      //(member limit setting for group 2)
    _RV32_2(0x100684, 0x0200),      //(timeout setting for group 2)
    _RV32_2(0x1006a2, 0x0008),      //(member limit setting for group 3)
    _RV32_2(0x1006a4, 0x0200),      //(timeout setting for group 3)
    _RV32_2(0x100640, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group0)
    _RV32_2(0x100660, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group1)
    _RV32_2(0x100680, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group2)
    _RV32_2(0x1006a0, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group3)

    _RV32_2(0x1006d4, 0x0000),      // turn off read_last_done_z_bypass

    _RV32_2(0x110dd4, 0xc000),      //miu_0_atop  start
    _RV32_2(0x110d80, 0x0200),
    _RV32_2(0x110d82, 0xaaaa),
    _RV32_2(0x110d84, 0x0080),
    _RV32_2(0x110dbc, 0x1522),
    _RV32_2(0x110dbe, 0x1055),
    _RV32_2(0x110dcc, 0x5511),
    _RV32_2(0x110dd0, 0x1111),
    _RV32_2(0x110db6, 0x4002),
    _RV32_2(0x110db8, 0x0033),
    _RV32_2(0x110dba, 0x0002),
    _RV32_2(0x110dc8, 0x0033),
    _RV32_2(0x110dca, 0x0002),
    _RV32_2(0x110dd2, 0x0000),
    _RV32_2(0x110dec, 0x9999),
    _RV32_2(0x110dee, 0x9999),
    _RV32_2(0x110de2, 0x0003),
    _RV32_2(0x110d8e, 0x00ef),
    _RV32_2(0x110d8e, 0x00af),
    _RV32_2(0x110d8e, 0x00ef),
    _RV32_2(0x110df0, 0x8000),      // change to MIU1
    _RV32_2(0x1012e4, 0x0001),      // test one data
    _RV32_2(0x1012e0, 0x0200),      // test write only
    _RV32_2(0x1012e0, 0x0201),      // test write only
    _RV32_2(0x1012e0, 0x0201),      // test write only
    _RV32_2(0x1012e0, 0x0000),      // retrn to original state
    _RV32_2(0x1012e4, 0x0000),      // retrn to original state
    _RV32_2(0x110df0, 0x0000),      // change to MIU0
    _RV32_2(0x110d8e, 0x00af),
    _RV32_2(0x110dfe, 0x0000),
    _RV32_2(0x110d80, 0x0200),

    _RV32_2(0x110de0, 0x2370),      //DLL SETTING
    _RV32_2(0x110de2, 0x0032),
    _RV32_2(0x110de4, 0xf200),
    _RV32_2(0x110de6, 0x0000),
    _RV32_2(0x110de8, 0x0020),
    _RV32_2(0x110dea, 0x0020),

#else
    #error "Invalid DRAM Selection"
#endif

    _END_OF_TBL32_,
};
#endif

#endif  //ENABLE_MSTAR_BD_MST176A_D01A_S_NIKE

#endif /* _MIU_MST176A_D01A_S_NIKE_H_ */
