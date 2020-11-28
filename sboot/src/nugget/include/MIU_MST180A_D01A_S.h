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
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _MIU_MST180A_D01A_S_H_
#define _MIU_MST180A_D01A_S_H_
//#define _MIU_4X_MODE

#if (ENABLE_MSTAR_BD_MST180A_D01A_S)

const MS_REG_INIT MIU0_DDR_Init[] =
{
#if (MIU_INTERFACE == DDR3_INTERFACE_BGA)

#if (ENABLE_MEM1300MHz == 1)

    _RV32_2(0x110d3a, 0x0000),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110d36, 0x4000),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110d34, 0x0300),      // loop_div/input_div
    _RV32_2(0x110d30, 0x6b0e),      // ddfset
    _RV32_2(0x110d32, 0x001f),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x101202, 0x03a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x101204, 0x000A),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x101206, 0x0434),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x101208, 0x1899),      //reg_tRCD
    _RV32_2(0x10120a, 0x2155),      //reg_tRRD
    _RV32_2(0x10120c, 0x95a7),      //reg_tWL
    _RV32_2(0x10120e, 0x406b),      //tRFC
    _RV32_2(0x101210, 0x1a50),      //MR0
    _RV32_2(0x101212, 0x4004),      //MR1
    _RV32_2(0x101214, 0x8010),      //MR2
    _RV32_2(0x101216, 0xC000),      //MR3
    _RV32_2(0x101228, 0x0090),
    _RV32_2(0x10122c, 0x6199),      // Address Balance Mode
    _RV32_2(0x110d54, 0x0000),      //miu_0_atop  start
    _RV32_2(0x110d00, 0x0211),      
    _RV32_2(0x110d02, 0x0000),
    _RV32_2(0x110d04, 0x0080),
    _RV32_2(0x110d06, 0x0000),
    _RV32_2(0x110d08, 0x003F),
    _RV32_2(0x110d0a, 0x0000),
    _RV32_2(0x110d0c, 0x0000),
    _RV32_2(0x110d0e, 0x00e5),
    _RV32_2(0x110d10, 0x0600),
    _RV32_2(0x110d12, 0x0000),
    _RV32_2(0x110d14, 0x0000),
    _RV32_2(0x110d16, 0x0200),
    _RV32_2(0x110d18, 0x0000),
    _RV32_2(0x110d1a, 0x0000),
    _RV32_2(0x110d1c, 0x0000),
    _RV32_2(0x110d1e, 0xffff),
    _RV32_2(0x110d20, 0x4020),
    _RV32_2(0x110d22, 0x0000),
    _RV32_2(0x110d24, 0x0000),
    _RV32_2(0x110d24, 0x0000),
    _RV32_2(0x110d26, 0x0000),
    _RV32_2(0x110d28, 0x0000),
    _RV32_2(0x110d2a, 0x0000),
    _RV32_2(0x110d2c, 0x0014),
    _RV32_2(0x110d2e, 0x0000),
    _RV32_2(0x110d38, 0x3377),
    _RV32_2(0x110d3a, 0x0000),
    _RV32_2(0x110d3c, 0x0633),
    _RV32_2(0x110d3e, 0x0066),
    _RV32_2(0x110d40, 0x0000),
    _RV32_2(0x110d42, 0x0000),
    _RV32_2(0x110d44, 0x0000),
    _RV32_2(0x110d46, 0x0000),
    _RV32_2(0x110d48, 0x0000),
    _RV32_2(0x110d4a, 0x0000),
    _RV32_2(0x110d4c, 0x0000),
    _RV32_2(0x110d4e, 0x0000),
    _RV32_2(0x110d50, 0x0000),
    _RV32_2(0x110d52, 0x0000),
    _RV32_2(0x110d54, 0x0000),
    _RV32_2(0x110d56, 0x0000),
    _RV32_2(0x110d58, 0x0000),
    _RV32_2(0x110d5a, 0x0000),
    _RV32_2(0x110d5c, 0x5555),
    _RV32_2(0x110d5e, 0x5555),
    _RV32_2(0x110d60, 0x2370),
    _RV32_2(0x110d62, 0x00ff),
    _RV32_2(0x110d64, 0xf200),
    _RV32_2(0x110d66, 0x0000),
    _RV32_2(0x110d68, 0x0020),
    _RV32_2(0x110d6a, 0x0020),
    _RV32_2(0x110d6c, 0x0000),
    _RV32_2(0x110d6e, 0x0079),
    _RV32_2(0x110d72, 0x0008),
    _RV32_2(0x110d72, 0x6806),
    _RV32_2(0x110d0e, 0x00a5),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
    _RV32_2(0x110d7e, 0x0000),

#elif (ENABLE_MEM1600MHz == 1)

#ifdef _MIU_4X_MODE
    _RV32_2(0x110d36, 0x4000),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110d34, 0x0000),      // loop_div/input_div
    _RV32_2(0x110d30, 0x8f5c),      // ddfset
    _RV32_2(0x110d32, 0x0022),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x110d20, 0x0020),
    _RV32_2(0x110d22, 0x2000),
    _RV32_2(0x110d24, 0x2000),
    _RV32_2(0x110d2e, 0x0800),
    _RV32_2(0x110d2c, 0x0300),
    _RV32_2(0x101202, 0x02a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x101204, 0x0051),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x101206, 0x0530),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x101208, 0x22dd),      //reg_tRCD
    _RV32_2(0x10120a, 0x2e86),      //reg_tRRD
    _RV32_2(0x10120c, 0xb7f9),      //reg_tWL
    _RV32_2(0x10120e, 0x4096),      //tRFC
    _RV32_2(0x101210, 0x1f14),      //MR0
    _RV32_2(0x101212, 0x4004),      //MR1
    _RV32_2(0x101214, 0x8020),      //MR2
    _RV32_2(0x101216, 0xc000),      //MR3
    _RV32_2(0x110d02, 0xaaaa),
    _RV32_2(0x110d04, 0x0008),
    _RV32_2(0x110d14, 0x1333),
    _RV32_2(0x110d3c, 0x1344),
    _RV32_2(0x110d3e, 0x1033),
    _RV32_2(0x110d4c, 0x3344),
    _RV32_2(0x110d50, 0x1111),
    _RV32_2(0x110d38, 0x0044),
    _RV32_2(0x110d3a, 0x0002),
    _RV32_2(0x110d48, 0x0044),
    _RV32_2(0x110d4a, 0x0002),
    _RV32_2(0x110d52, 0x0000),
    _RV32_2(0x110d6c, 0x7777),
    _RV32_2(0x110d6e, 0x7777),
    _RV32_2(0x110d0e, 0x00b9),
    _RV32_2(0x110d0e, 0x00f9),
    _RV32_2(0x110d0e, 0x00b9),
    _RV32_2(0x110d62, 0x0032),
    _RV32_2(0x110d64, 0xf200),
    _RV32_2(0x110d66, 0x0000),
    _RV32_2(0x110d68, 0x0020),
    _RV32_2(0x110d6a, 0x0020),
    _RV32_2(0x110d60, 0x000c),
    _RV32_2(0x110d60, 0x0008),
    _RV32_2(0x110d60, 0x2370),
    _RV32_2(0x101228, 0x4000),     //Pack setting
    _RV32_2(0x10122a, 0x0000),     //Reduce latency setting  
    _RV32_2(0x1012d4, 0x0010),     //ratio mode = 1
    _RV32_2(0x110d00, 0x1039),
#else
    _RV32_2(0x110d36, 0x4000),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110d34, 0x0000),      // loop_div/input_div
    _RV32_2(0x110d30, 0x8f5c),      // ddfset
    _RV32_2(0x110d32, 0x0022),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x110d20, 0x0020),
    _RV32_2(0x110d22, 0x2000),
    _RV32_2(0x110d24, 0x2000),
    _RV32_2(0x110d2e, 0x0800),
    _RV32_2(0x110d2c, 0x0300),
    _RV32_2(0x101202, 0x03a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x101204, 0x004d),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x101206, 0x0538),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x101208, 0x20dd),      //reg_tRCD
    _RV32_2(0x10120a, 0x2d75),      //reg_tRRD
    _RV32_2(0x10120c, 0xa7e9),      //reg_tWL
    _RV32_2(0x10120e, 0x4096),      //tRFC
    _RV32_2(0x101210, 0x1f14),      //MR0
    _RV32_2(0x101212, 0x4004),      //MR1
    _RV32_2(0x101214, 0x8020),      //MR2
    _RV32_2(0x101216, 0xc000),      //MR3
    _RV32_2(0x110d02, 0xaaaa),
    _RV32_2(0x110d04, 0x0080),
    _RV32_2(0x110d14, 0x1333),
    _RV32_2(0x110d3c, 0x1344),
    _RV32_2(0x110d3e, 0x1033),
    _RV32_2(0x110d4c, 0x3344),
    _RV32_2(0x110d50, 0x1111),
    _RV32_2(0x110d54, 0x0000),      //1T mode
    _RV32_2(0x110d38, 0x0054),
    _RV32_2(0x110d3a, 0x0002),
    _RV32_2(0x110d48, 0x0033),
    _RV32_2(0x110d4a, 0x0002),
    _RV32_2(0x110d52, 0x0000),
    _RV32_2(0x110d6c, 0x7777),
    _RV32_2(0x110d6e, 0x7888),
    _RV32_2(0x110d0e, 0x00ad),
    _RV32_2(0x110d0e, 0x00ed),
    _RV32_2(0x110d0e, 0x00ad),
    _RV32_2(0x110d62, 0x0032),
    _RV32_2(0x110d64, 0xf200),
    _RV32_2(0x110d66, 0x0000),
    _RV32_2(0x110d68, 0x0020),
    _RV32_2(0x110d6a, 0x0020),
    _RV32_2(0x110d60, 0x000c),
    _RV32_2(0x110d60, 0x0008),
    _RV32_2(0x110d60, 0x2370),
    _RV32_2(0x101228, 0x4000),     //Pack setting
    _RV32_2(0x10122a, 0x0000),     //Reduce latency setting  
    _RV32_2(0x1012d4, 0x0000),     //ratio mode = 0
    _RV32_2(0x110d00, 0x1039),
#endif

#elif (ENABLE_MEM1866MHz == 1)

#ifdef _MIU_4X_MODE
    _RV32_2(0x110d36, 0x4000),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110d34, 0x0000),      // loop_div/input_div
    _RV32_2(0x110d30, 0xa229),      // ddfset
    _RV32_2(0x110d32, 0x001d),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x110d20, 0x0020),
    _RV32_2(0x110d22, 0x2000),
    _RV32_2(0x110d24, 0x2000),
    _RV32_2(0x110d2e, 0x0800),
    _RV32_2(0x110d2c, 0x0300),
    _RV32_2(0x101202, 0x02a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x101204, 0x004f),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x101206, 0x0530),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x101208, 0x22dd),      //reg_tRCD
    _RV32_2(0x10120a, 0x2e86),      //reg_tRRD
    _RV32_2(0x10120c, 0xb7f9),      //reg_tWL
    _RV32_2(0x10120e, 0x4096),      //tRFC
    _RV32_2(0x101210, 0x1f14),      //MR0
    _RV32_2(0x101212, 0x4004),      //MR1
    _RV32_2(0x101214, 0x8020),      //MR2
    _RV32_2(0x101216, 0xc000),      //MR3
    _RV32_2(0x110d02, 0xaaaa),
    _RV32_2(0x110d04, 0x0008),
    _RV32_2(0x110d14, 0x1333),
    _RV32_2(0x110d3c, 0x1333),
    _RV32_2(0x110d3e, 0x1033),
    _RV32_2(0x110d4c, 0x3333),
    _RV32_2(0x110d50, 0x1111),
    _RV32_2(0x110d38, 0x0033),
    _RV32_2(0x110d3a, 0x0002),
    _RV32_2(0x110d48, 0x0033),
    _RV32_2(0x110d4a, 0x0002),
    _RV32_2(0x110d52, 0x0000),
    _RV32_2(0x110d6c, 0x5555),
    _RV32_2(0x110d6e, 0x5555),
    _RV32_2(0x110d0e, 0x00b9),
    _RV32_2(0x110d0e, 0x00f9),
    _RV32_2(0x110d0e, 0x00b9),
    _RV32_2(0x110d62, 0x0032),
    _RV32_2(0x110d64, 0xf200),
    _RV32_2(0x110d66, 0x0000),
    _RV32_2(0x110d68, 0x0020),
    _RV32_2(0x110d6a, 0x0020),
    _RV32_2(0x110d60, 0x000c),
    _RV32_2(0x110d60, 0x0008),
    _RV32_2(0x110d60, 0x2370),
    _RV32_2(0x101228, 0x4000),     //Pack setting
    _RV32_2(0x10122a, 0x0000),     //Reduce latency setting  
    _RV32_2(0x1012d4, 0x0010),     //ratio mode = 1
    _RV32_2(0x110d00, 0x1039),
#else
    _RV32_2(0x110d72, 0x0004),
    _RV32_2(0x110d36, 0x4002),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110d34, 0x0000),      // loop_div/input_div
    _RV32_2(0x110d30, 0xa229),      // ddfset
    _RV32_2(0x110d32, 0x001d),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x110d20, 0x0020),
    _RV32_2(0x110d22, 0x2000),
    _RV32_2(0x110d24, 0x2000),
    _RV32_2(0x110d2e, 0x0800),
    _RV32_2(0x110d2c, 0x0300),
    _RV32_2(0x101202, 0x03a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x101204, 0x000d),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x101206, 0x0d38),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x101208, 0x20dd),      //reg_tRCD
    _RV32_2(0x10120a, 0x2d75),      //reg_tRRD
    _RV32_2(0x10120c, 0xa7e9),      //reg_tWL
    _RV32_2(0x10120e, 0x4096),      //tRFC
    _RV32_2(0x101210, 0x1f14),      //MR0
    _RV32_2(0x101212, 0x4004),      //MR1
    _RV32_2(0x101214, 0x8020),      //MR2
    _RV32_2(0x101216, 0xc000),      //MR3
    _RV32_2(0x110d02, 0xaaaa),
    _RV32_2(0x110d04, 0x0080),
    _RV32_2(0x110d14, 0x1333),
    _RV32_2(0x110d3c, 0x1344),
    _RV32_2(0x110d3e, 0x1033),
    _RV32_2(0x110d4c, 0x3344),
    _RV32_2(0x110d50, 0x1111),
    _RV32_2(0x110d38, 0x0054),
    _RV32_2(0x110d3a, 0x0000),
    _RV32_2(0x110d48, 0x0033),
    _RV32_2(0x110d4a, 0x0002),
    _RV32_2(0x110d52, 0x0000),
    _RV32_2(0x110d6c, 0x7777),
    _RV32_2(0x110d6e, 0x8977),
    _RV32_2(0x110d0e, 0x00ad),
    _RV32_2(0x110d0e, 0x00ed),
    _RV32_2(0x110d0e, 0x00ad),
    _RV32_2(0x110d62, 0x0032),
    _RV32_2(0x110d64, 0xf200),
    _RV32_2(0x110d66, 0x0000),
    _RV32_2(0x110d68, 0x0020),
    _RV32_2(0x110d6a, 0x0020),
    _RV32_2(0x110d60, 0x000c),
    _RV32_2(0x110d60, 0x0008),
    _RV32_2(0x110d60, 0x2370),
    _RV32_2(0x101228, 0x40f0),     //Pack setting
    _RV32_2(0x10122a, 0x0000),     //Reduce latency setting  
    _RV32_2(0x1012d4, 0x0000),     //ratio mode = 0
    _RV32_2(0x110d00, 0x1239),
#endif

#elif (ENABLE_MEM2133MHz == 1)

    _RV32_2(0x110d3a, 0x0000),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110d36, 0x4000),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110d34, 0x0300),      // loop_div/input_div
    _RV32_2(0x110d30, 0x716a),      // ddfset
    _RV32_2(0x110d32, 0x0013),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x101202, 0x03a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x101204, 0x000B),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x101206, 0x0634),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x101208, 0x24ee),      //reg_tRCD
    _RV32_2(0x10120a, 0x3287),      //reg_tRRD
    _RV32_2(0x10120c, 0xc80a),      //reg_tWL
    _RV32_2(0x10120e, 0xc0b8),      //tRFC
    _RV32_2(0x101210, 0x1124),      //MR0
    _RV32_2(0x101212, 0x4004),      //MR1
    _RV32_2(0x101214, 0x8028),      //MR2
    _RV32_2(0x101216, 0xC000),      //MR3
    _RV32_2(0x101228, 0x00a0),
    _RV32_2(0x10122c, 0x6199),      // Address Balance Mode
    _RV32_2(0x110d54, 0x0000),      //miu_0_atop  start
    _RV32_2(0x110d00, 0x0211),      
    _RV32_2(0x110d02, 0x0000),
    _RV32_2(0x110d04, 0x0080),
    _RV32_2(0x110d06, 0x0000),
    _RV32_2(0x110d08, 0x003F),
    _RV32_2(0x110d0a, 0x0000),
    _RV32_2(0x110d0c, 0x0000),
    _RV32_2(0x110d0e, 0x00e7),
    _RV32_2(0x110d10, 0x0600),
    _RV32_2(0x110d12, 0x0000),
    _RV32_2(0x110d14, 0x0000),
    _RV32_2(0x110d16, 0x0200),
    _RV32_2(0x110d18, 0x0000),
    _RV32_2(0x110d1a, 0x0000),
    _RV32_2(0x110d1c, 0x0000),
    _RV32_2(0x110d1e, 0xffff),
    _RV32_2(0x110d20, 0x0020),
    _RV32_2(0x110d22, 0x0000),
    _RV32_2(0x110d24, 0x0000),
    _RV32_2(0x110d24, 0x0000),
    _RV32_2(0x110d26, 0x0000),
    _RV32_2(0x110d28, 0x0000),
    _RV32_2(0x110d2a, 0x0000),
    _RV32_2(0x110d2c, 0x0014),
    _RV32_2(0x110d2e, 0x0000),
    _RV32_2(0x110d38, 0x3377),
    _RV32_2(0x110d3a, 0x0000),
    _RV32_2(0x110d3c, 0x0455),
    _RV32_2(0x110d3e, 0x0044),
    _RV32_2(0x110d40, 0x0000),
    _RV32_2(0x110d42, 0x0000),
    _RV32_2(0x110d44, 0x0000),
    _RV32_2(0x110d46, 0x0000),
    _RV32_2(0x110d48, 0x0000),
    _RV32_2(0x110d4a, 0x0000),
    _RV32_2(0x110d4c, 0x0000),
    _RV32_2(0x110d4e, 0x0000),
    _RV32_2(0x110d50, 0x0000),
    _RV32_2(0x110d52, 0x0000),
    _RV32_2(0x110d54, 0x0000),
    _RV32_2(0x110d56, 0x0000),
    _RV32_2(0x110d58, 0x0000),
    _RV32_2(0x110d5a, 0x0000),
    _RV32_2(0x110d5c, 0x5555),
    _RV32_2(0x110d5e, 0x5555),
    _RV32_2(0x110d60, 0x2370),
    _RV32_2(0x110d62, 0x00ff),
    _RV32_2(0x110d64, 0xf200),
    _RV32_2(0x110d66, 0x0000),
    _RV32_2(0x110d68, 0x0020),
    _RV32_2(0x110d6a, 0x0020),
    _RV32_2(0x110d6c, 0x0000),
    _RV32_2(0x110d6e, 0x0067),
    _RV32_2(0x110d72, 0x0008),
    _RV32_2(0x110d72, 0x5805),
    _RV32_2(0x110d0e, 0x00a7),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
    _RV32_2(0x110d7e, 0x0000),

#else   
    #error  "Invalid DRAM Freq"    
#endif

#elif (MIU_INTERFACE == DDR2_INTERFACE_BGA)

#if (ENABLE_MEM800MHz == 1)

    _RV32_2(0x110d3a, 0x0500),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110d36, 0x4003),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110d34, 0x0500),      // loop_div/input_div
    _RV32_2(0x110d30, 0xd72c),      // ddfset
    _RV32_2(0x110d32, 0x0040),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x101202, 0x02a2),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x101204, 0x008b),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x101206, 0x3450),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x101208, 0x1877),      //reg_tRCD
    _RV32_2(0x10120a, 0x1f46),      //reg_tRRD
    _RV32_2(0x10120c, 0x5486),      //reg_tWL
    _RV32_2(0x10120e, 0x2044),      //tRFC
    _RV32_2(0x101210, 0x0e72),      //MR0
    _RV32_2(0x101212, 0x4004),      //MR1
    _RV32_2(0x101214, 0x8000),      //MR2
    _RV32_2(0x101216, 0xC000),      //MR3
    _RV32_2(0x110d00, 0x0011),      //miu_0_atop  start
    _RV32_2(0x110d38, 0x0033),      // DQ0/DQ1 phase / dqs0/dqs1 phase
    _RV32_2(0x110d3a, 0x0010),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110d02, 0x0000),
    _RV32_2(0x110d3c, 0x0200),
    _RV32_2(0x110d3e, 0x0000),
    _RV32_2(0x110d0e, 0x00e7),      // 1/2 reg_en_mask
    _RV32_2(0x110d0e, 0x00a7),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
    _RV32_2(0x110d6e, 0x0088),      //reg_dll0_ph //
    _RV32_2(0x110d6a, 0x00c2),      //reg_dll1_code   //refine when DDR_CLK change
    _RV32_2(0x110d68, 0x00c2),      //reg_dll0_code   //refine when DDR_CLK change
    _RV32_2(0x110d60, 0x0374),
    _RV32_2(0x110d60, 0x0370),
    _RV32_2(0x110d54, 0x0000),      //turn off atop+pd
    _RV32_2(0x110d7e, 0x0000),

#elif (ENABLE_MEM1066MHz == 1)

    _RV32_2(0x110d3a, 0x0500),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110d36, 0xc000),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110d34, 0x0000),      // loop_div/input_div
    _RV32_2(0x110d30, 0x1eb6),      // ddfset
    _RV32_2(0x110d32, 0x0045),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x101202, 0x02a2),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x101204, 0x008b),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x101206, 0x3450),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x101208, 0x1877),      //reg_tRCD
    _RV32_2(0x10120a, 0x1f56),      //reg_tRRD
    _RV32_2(0x10120c, 0x5486),      //reg_tWL
    _RV32_2(0x10120e, 0x2044),      //tRFC
    _RV32_2(0x101210, 0x0a72),      //MR0
    _RV32_2(0x101212, 0x4004),      //MR1
    _RV32_2(0x101214, 0x8000),      //MR2
    _RV32_2(0x101216, 0xC000),      //MR3
    _RV32_2(0x110d54, 0x0000),      //miu_0_atop  start
    _RV32_2(0x110d00, 0x0011),      
    _RV32_2(0x110d10, 0x0500),
    _RV32_2(0x110d22, 0x0000),
    _RV32_2(0x110d38, 0x0033),      // DQ0/DQ1 phase / dqs0/dqs1 phase
    _RV32_2(0x110d3a, 0x4040),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110d02, 0x0000),
    _RV32_2(0x110d3c, 0x0022),
    _RV32_2(0x110d3e, 0x0000),
    _RV32_2(0x110d0e, 0x00e7),      // 1/2 reg_en_mask
    _RV32_2(0x110d0e, 0x00a7),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
    _RV32_2(0x110d5C, 0x3333),
    _RV32_2(0x110d5E, 0x3333),
    _RV32_2(0x110d62, 0x4032),
    _RV32_2(0x110d72, 0x5805),
    _RV32_2(0x110d64, 0xF200),      //reg_dll0_ph //
    _RV32_2(0x110d6e, 0x0055),      //reg_dll0_ph //
    _RV32_2(0x110d6a, 0x00c2),      //reg_dll1_code   //refine when DDR_CLK change
    _RV32_2(0x110d68, 0x00c2),      //reg_dll0_code   //refine when DDR_CLK change
    _RV32_2(0x110d60, 0x000C),
    _RV32_2(0x110d60, 0x0008),
    _RV32_2(0x110d60, 0x2378),
    _RV32_2(0x110d54, 0x0000),      //turn off atop+pd
    _RV32_2(0x110d7e, 0x0000),

#else
    #error  "Invalid DRAM Freq"
#endif

#else
    #error "Invalid MIU Interface"
#endif

    _END_OF_TBL32_,
    MIU_VER
};

#ifndef CONFIG_MIU1_DRAM_NONE
const MS_REG_INIT MIU1_DDR_Init[] =
{
#if defined(CONFIG_MIU1_DDR3_1333)

    _RV32_2(0x110dba, 0x0000),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110db4, 0x0300),      // loop_div/input_div
    _RV32_2(0x110db6, 0x4000),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110db0, 0x6b0e),      // ddfset
    _RV32_2(0x110db2, 0x001f),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x100602, 0x03a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x100604, 0x000A),
    _RV32_2(0x100606, 0x0434),      //refresh cycle=0x20 ,TURN_ON_SCRAMBLE=0x8420
    _RV32_2(0x100608, 0x1899),      //reg_tRCD
    _RV32_2(0x10060a, 0x2155),      //reg_tRRD
    _RV32_2(0x10060c, 0x95a7),      //reg_tWL
    _RV32_2(0x10060e, 0x406b),      //tRFC
    _RV32_2(0x100610, 0x1a50),      //MR0
    _RV32_2(0x100612, 0x4004),      //MR1
    _RV32_2(0x100614, 0x8010),      //MR2
    _RV32_2(0x100616, 0xC000),      //MR3
    _RV32_2(0x100628, 0x0090),
    _RV32_2(0x10062c, 0x6199),      // Address Balance Mode
    _RV32_2(0x110dd4, 0x0000),      //miu_0_atop  start
    _RV32_2(0x110d80, 0x0211),
    _RV32_2(0x110d82, 0x0000),
    _RV32_2(0x110d84, 0x0080),
    _RV32_2(0x110d86, 0x0000),
    _RV32_2(0x110d88, 0x003F),
    _RV32_2(0x110d8a, 0x0000),
    _RV32_2(0x110d8c, 0x0000),
    _RV32_2(0x110d8e, 0x00e5),
    _RV32_2(0x110d90, 0x0600),
    _RV32_2(0x110d92, 0x0000),
    _RV32_2(0x110d94, 0x0000),
    _RV32_2(0x110d96, 0x0200),
    _RV32_2(0x110d98, 0x0000),
    _RV32_2(0x110d9a, 0x0000),
    _RV32_2(0x110d9c, 0x0000),
    _RV32_2(0x110d9e, 0xffff),
    _RV32_2(0x110da0, 0x4020),
    _RV32_2(0x110da2, 0x0000),
    _RV32_2(0x110da4, 0x0000),
    _RV32_2(0x110da6, 0x0000),
    _RV32_2(0x110da8, 0x0000),
    _RV32_2(0x110daa, 0x0000),
    _RV32_2(0x110dac, 0x0014),
    _RV32_2(0x110dae, 0x0000),
    _RV32_2(0x110db8, 0x3377),
    _RV32_2(0x110dba, 0x0000),
    _RV32_2(0x110dbc, 0x0633),
    _RV32_2(0x110dbe, 0x0066),
    _RV32_2(0x110dc0, 0x0000),
    _RV32_2(0x110dc2, 0x0000),
    _RV32_2(0x110dc4, 0x0000),
    _RV32_2(0x110dc6, 0x0000),
    _RV32_2(0x110dc8, 0x0000),
    _RV32_2(0x110dca, 0x0000),
    _RV32_2(0x110dcc, 0x0000),
    _RV32_2(0x110dce, 0x0000),
    _RV32_2(0x110dd0, 0x0000),
    _RV32_2(0x110dd2, 0x0000),
    _RV32_2(0x110dd4, 0x0000),
    _RV32_2(0x110dd6, 0x0000),
    _RV32_2(0x110dd8, 0x0000),
    _RV32_2(0x110dda, 0x0000),
    _RV32_2(0x110ddc, 0x5555),
    _RV32_2(0x110dde, 0x5555),
    _RV32_2(0x110de0, 0x2370),
    _RV32_2(0x110de2, 0x00ff),
    _RV32_2(0x110de4, 0xf200),
    _RV32_2(0x110de6, 0x0000),
    _RV32_2(0x110de8, 0x0020),
    _RV32_2(0x110dea, 0x0020),
    _RV32_2(0x110dec, 0x0000),
    _RV32_2(0x110dee, 0x0057),
    _RV32_2(0x110df2, 0x0008),
    _RV32_2(0x110df2, 0x6806),
    _RV32_2(0x110d8e, 0x00a5),       // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
    _RV32_2(0x110dfe, 0x0000),

#elif defined(CONFIG_MIU1_DDR3_1666)

#ifdef _MIU_4X_MODE
    _RV32_2(0x110db6, 0x4000),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110db4, 0x0000),      // loop_div/input_div
    _RV32_2(0x110db0, 0x8f5c),      // ddfset
    _RV32_2(0x110db2, 0x0022),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x110da0, 0x0020),
    _RV32_2(0x110da2, 0x2000),
    _RV32_2(0x110da4, 0x2000),
    _RV32_2(0x110dae, 0x0800),
    _RV32_2(0x110dac, 0x0300),
    _RV32_2(0x100602, 0x02a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x100604, 0x0051),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x100606, 0x0530),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x100608, 0x22dd),      //reg_tRCD
    _RV32_2(0x10060a, 0x2e86),      //reg_tRRD
    _RV32_2(0x10060c, 0xb7f9),      //reg_tWL
    _RV32_2(0x10060e, 0x4096),      //tRFC
    _RV32_2(0x100610, 0x1f14),      //MR0
    _RV32_2(0x100612, 0x4004),      //MR1
    _RV32_2(0x100614, 0x8020),      //MR2
    _RV32_2(0x100616, 0xc000),      //MR3
    _RV32_2(0x110d82, 0xaaaa),
    _RV32_2(0x110d84, 0x0008),
    _RV32_2(0x110d94, 0x1333),
    _RV32_2(0x110dbc, 0x1344),
    _RV32_2(0x110dbe, 0x1033),
    _RV32_2(0x110dcc, 0x3344),
    _RV32_2(0x110dd0, 0x1111),
    _RV32_2(0x110db8, 0x0054),
    _RV32_2(0x110dba, 0x0002),
    _RV32_2(0x110dc8, 0x0044),
    _RV32_2(0x110dca, 0x0002),
    _RV32_2(0x110dd2, 0x0000),
    _RV32_2(0x110dec, 0x6666),
    _RV32_2(0x110dee, 0x6666),
    _RV32_2(0x110d8e, 0x00b9),
    _RV32_2(0x110d8e, 0x00f9),
    _RV32_2(0x110d8e, 0x00b9),
    _RV32_2(0x110de2, 0x0032),
    _RV32_2(0x110de4, 0xf200),
    _RV32_2(0x110de6, 0x0000),
    _RV32_2(0x110de8, 0x0020),
    _RV32_2(0x110dea, 0x0020),
    _RV32_2(0x110de0, 0x000c),
    _RV32_2(0x110de0, 0x0008),
    _RV32_2(0x110de0, 0x2370),
    _RV32_2(0x100628, 0x4000),     //Pack setting
    _RV32_2(0x10062a, 0x0000),     //Reduce latency setting  
    _RV32_2(0x1006d4, 0x0010),     //ratio mode = 1
    _RV32_2(0x110d80, 0x1039),
#else
    _RV32_2(0x110db6, 0x4000),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110db4, 0x0000),      // loop_div/input_div
    _RV32_2(0x110db0, 0x8f5c),      // ddfset
    _RV32_2(0x110db2, 0x0022),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x110da0, 0x0020),
    _RV32_2(0x110da2, 0x2000),
    _RV32_2(0x110da4, 0x2000),
    _RV32_2(0x110dae, 0x0800),
    _RV32_2(0x110dac, 0x0300),
    _RV32_2(0x100602, 0x03a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x100604, 0x004d),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x100606, 0x0538),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x100608, 0x20dd),      //reg_tRCD
    _RV32_2(0x10060a, 0x2d75),      //reg_tRRD
    _RV32_2(0x10060c, 0xa7e9),      //reg_tWL
    _RV32_2(0x10060e, 0x4096),      //tRFC
    _RV32_2(0x100610, 0x1f14),      //MR0
    _RV32_2(0x100612, 0x4004),      //MR1
    _RV32_2(0x100614, 0x8020),      //MR2
    _RV32_2(0x100616, 0xc000),      //MR3
    _RV32_2(0x110d82, 0xaaaa),
    _RV32_2(0x110d84, 0x0080),
    _RV32_2(0x110d94, 0x1333),
    _RV32_2(0x110dbc, 0x1344),
    _RV32_2(0x110dbe, 0x1033),
    _RV32_2(0x110dcc, 0x3344),
    _RV32_2(0x110dd0, 0x1111),
    _RV32_2(0x110db8, 0x0053),
    _RV32_2(0x110dba, 0x0002),
    _RV32_2(0x110dc8, 0x0033),
    _RV32_2(0x110dca, 0x0002),
    _RV32_2(0x110dd2, 0x0000),
    _RV32_2(0x110dd4, 0x0000),     //1T mode
    _RV32_2(0x110dec, 0x7777),
    _RV32_2(0x110dee, 0x7777),
    _RV32_2(0x110d8e, 0x00ad),
    _RV32_2(0x110d8e, 0x00ed),
    _RV32_2(0x110d8e, 0x00ad),
    _RV32_2(0x110de2, 0x0032),
    _RV32_2(0x110de4, 0xf200),
    _RV32_2(0x110de6, 0x0000),
    _RV32_2(0x110de8, 0x0020),
    _RV32_2(0x110dea, 0x0020),
    _RV32_2(0x110de0, 0x000c),
    _RV32_2(0x110de0, 0x0008),
    _RV32_2(0x110de0, 0x2370),
    _RV32_2(0x100628, 0x4000),     //Pack setting
    _RV32_2(0x10062a, 0x0000),     //Reduce latency setting  
    _RV32_2(0x1006d4, 0x0000),     //ratio mode = 0
    _RV32_2(0x110d80, 0x1039),
#endif

#elif defined(CONFIG_MIU1_DDR3_1866)
    
#ifdef _MIU_4X_MODE
    _RV32_2(0x110db6, 0x4000),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110db4, 0x0000),      // loop_div/input_div
    _RV32_2(0x110db0, 0xa229),      // ddfset
    _RV32_2(0x110db2, 0x001d),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x110da0, 0x0020),
    _RV32_2(0x110da2, 0x2000),
    _RV32_2(0x110da4, 0x2000),
    _RV32_2(0x110dae, 0x0800),
    _RV32_2(0x110dac, 0x0300),
    _RV32_2(0x100602, 0x02a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x100604, 0x004f),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x100606, 0x0530),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x100608, 0x22dd),      //reg_tRCD
    _RV32_2(0x10060a, 0x2e86),      //reg_tRRD
    _RV32_2(0x10060c, 0xb7f9),      //reg_tWL
    _RV32_2(0x10060e, 0x4096),      //tRFC
    _RV32_2(0x100610, 0x1f14),      //MR0
    _RV32_2(0x100612, 0x4004),      //MR1
    _RV32_2(0x100614, 0x8020),      //MR2
    _RV32_2(0x100616, 0xc000),      //MR3
    _RV32_2(0x110d82, 0xaaaa),
    _RV32_2(0x110d84, 0x0008),
    _RV32_2(0x110d94, 0x1333),
    _RV32_2(0x110dbc, 0x1333),
    _RV32_2(0x110dbe, 0x1033),
    _RV32_2(0x110dcc, 0x3333),
    _RV32_2(0x110dd0, 0x1111),
    _RV32_2(0x110db8, 0x0033),
    _RV32_2(0x110dba, 0x0002),
    _RV32_2(0x110dc8, 0x0033),
    _RV32_2(0x110dca, 0x0002),
    _RV32_2(0x110dd2, 0x0000),
    _RV32_2(0x110dec, 0x5555),
    _RV32_2(0x110dee, 0x5555),
    _RV32_2(0x110d8e, 0x00b9),
    _RV32_2(0x110d8e, 0x00f9),
    _RV32_2(0x110d8e, 0x00b9),
    _RV32_2(0x110de2, 0x0032),
    _RV32_2(0x110de4, 0xf200),
    _RV32_2(0x110de6, 0x0000),
    _RV32_2(0x110de8, 0x0020),
    _RV32_2(0x110dea, 0x0020),
    _RV32_2(0x110de0, 0x000c),
    _RV32_2(0x110de0, 0x0008),
    _RV32_2(0x110de0, 0x2370),
    _RV32_2(0x100628, 0x4000),     //Pack setting
    _RV32_2(0x10062a, 0x0000),     //Reduce latency setting  
    _RV32_2(0x1006d4, 0x0010),     //ratio mode = 1
    _RV32_2(0x110d80, 0x1039),
#else
    _RV32_2(0x110df2, 0x0004),
    _RV32_2(0x110db6, 0x4002),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110db4, 0x0000),      // loop_div/input_div
    _RV32_2(0x110db0, 0xa229),      // ddfset
    _RV32_2(0x110db2, 0x001d),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x110da0, 0x0020),
    _RV32_2(0x110da2, 0x2000),
    _RV32_2(0x110da4, 0x2000),
    _RV32_2(0x110dae, 0x0800),
    _RV32_2(0x110dac, 0x0300),
    _RV32_2(0x100602, 0x03a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x100604, 0x000d),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x100606, 0x0d38),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x100608, 0x20dd),      //reg_tRCD
    _RV32_2(0x10060a, 0x2d75),      //reg_tRRD
    _RV32_2(0x10060c, 0xa7e9),      //reg_tWL
    _RV32_2(0x10060e, 0x4096),      //tRFC
    _RV32_2(0x100610, 0x1f14),      //MR0
    _RV32_2(0x100612, 0x4004),      //MR1
    _RV32_2(0x100614, 0x8020),      //MR2
    _RV32_2(0x100616, 0xc000),      //MR3
    _RV32_2(0x110d82, 0xaaaa),
    _RV32_2(0x110d84, 0x0080),
    _RV32_2(0x110d94, 0x1333),
    _RV32_2(0x110dbc, 0x1344),
    _RV32_2(0x110dbe, 0x1033),
    _RV32_2(0x110dcc, 0x3344),
    _RV32_2(0x110dd0, 0x1111),
    _RV32_2(0x110db8, 0x0053),
    _RV32_2(0x110dba, 0x0000),
    _RV32_2(0x110dc8, 0x0033),
    _RV32_2(0x110dca, 0x0002),
    _RV32_2(0x110dd2, 0x0000),
    _RV32_2(0x110dec, 0x7777),
    _RV32_2(0x110dee, 0x7776),
    _RV32_2(0x110d8e, 0x00ad),
    _RV32_2(0x110d8e, 0x00ed),
    _RV32_2(0x110d8e, 0x00ad),
    _RV32_2(0x110de2, 0x0032),
    _RV32_2(0x110de4, 0xf200),
    _RV32_2(0x110de6, 0x0000),
    _RV32_2(0x110de8, 0x0020),
    _RV32_2(0x110dea, 0x0020),
    _RV32_2(0x110de0, 0x000c),
    _RV32_2(0x110de0, 0x0008),
    _RV32_2(0x110de0, 0x2370),
    _RV32_2(0x100628, 0x40f0),     //Pack setting
    _RV32_2(0x10062a, 0x0000),     //Reduce latency setting  
    _RV32_2(0x1006d4, 0x0000),     //ratio mode = 0
    _RV32_2(0x110d80, 0x1239),
#endif

#elif defined(CONFIG_MIU1_DDR3_2133)

    _RV32_2(0x110dba, 0x0000),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110db4, 0x0300),      // loop_div/input_div
    _RV32_2(0x110db6, 0x4000),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110db0, 0x716a),      // ddfset
    _RV32_2(0x110db2, 0x0013),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x100602, 0x03a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x100604, 0x000B),
    _RV32_2(0x100606, 0x0634),      //refresh cycle=0x20 ,TURN_ON_SCRAMBLE=0x8420
    _RV32_2(0x100608, 0x24ee),      //reg_tRCD
    _RV32_2(0x10060a, 0x3287),      //reg_tRRD
    _RV32_2(0x10060c, 0xc80a),      //reg_tWL
    _RV32_2(0x10060e, 0xc0b8),      //tRFC
    _RV32_2(0x100610, 0x1124),      //MR0
    _RV32_2(0x100612, 0x4004),      //MR1
    _RV32_2(0x100614, 0x8028),      //MR2
    _RV32_2(0x100616, 0xC000),      //MR3
    _RV32_2(0x100628, 0x00a0),
    _RV32_2(0x10062c, 0x6199),      // Address Balance Mode
    _RV32_2(0x110dd4, 0x0000),      //miu_0_atop  start
    _RV32_2(0x110d80, 0x0211),
    _RV32_2(0x110d82, 0x0000),
    _RV32_2(0x110d84, 0x0080),
    _RV32_2(0x110d86, 0x0000),
    _RV32_2(0x110d88, 0x003F),
    _RV32_2(0x110d8a, 0x0000),
    _RV32_2(0x110d8c, 0x0000),
    _RV32_2(0x110d8e, 0x00e7),
    _RV32_2(0x110d90, 0x0600),
    _RV32_2(0x110d92, 0x0000),
    _RV32_2(0x110d94, 0x0000),
    _RV32_2(0x110d96, 0x0200),
    _RV32_2(0x110d98, 0x0000),
    _RV32_2(0x110d9a, 0x0000),
    _RV32_2(0x110d9c, 0x0000),
    _RV32_2(0x110d9e, 0xffff),
    _RV32_2(0x110da0, 0x0020),
    _RV32_2(0x110da2, 0x0000),
    _RV32_2(0x110da4, 0x0000),
    _RV32_2(0x110da6, 0x0000),
    _RV32_2(0x110da8, 0x0000),
    _RV32_2(0x110daa, 0x0000),
    _RV32_2(0x110dac, 0x0014),
    _RV32_2(0x110dae, 0x0000),
    _RV32_2(0x110db8, 0x3377),
    _RV32_2(0x110dba, 0x0000),
    _RV32_2(0x110dbc, 0x0455),
    _RV32_2(0x110dbe, 0x0044),
    _RV32_2(0x110dc0, 0x0000),
    _RV32_2(0x110dc2, 0x0000),
    _RV32_2(0x110dc4, 0x0000),
    _RV32_2(0x110dc6, 0x0000),
    _RV32_2(0x110dc8, 0x0000),
    _RV32_2(0x110dca, 0x0000),
    _RV32_2(0x110dcc, 0x0000),
    _RV32_2(0x110dce, 0x0000),
    _RV32_2(0x110dd0, 0x0000),
    _RV32_2(0x110dd2, 0x0000),
    _RV32_2(0x110dd4, 0x0000),
    _RV32_2(0x110dd6, 0x0000),
    _RV32_2(0x110dd8, 0x0000),
    _RV32_2(0x110dda, 0x0000),
    _RV32_2(0x110ddc, 0x5555),
    _RV32_2(0x110dde, 0x5555),
    _RV32_2(0x110de0, 0x2370),
    _RV32_2(0x110de2, 0x00ff),
    _RV32_2(0x110de4, 0xf200),
    _RV32_2(0x110de6, 0x0000),
    _RV32_2(0x110de8, 0x0020),
    _RV32_2(0x110dea, 0x0020),
    _RV32_2(0x110dec, 0x0000),
    _RV32_2(0x110dee, 0x0057),
    _RV32_2(0x110df2, 0x0008),
    _RV32_2(0x110df2, 0x5805),
    _RV32_2(0x110d8e, 0x00a7),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
    _RV32_2(0x110dfe, 0x0000),

#elif defined(CONFIG_MIU1_DDR2_800)

    _RV32_2(0x110dba, 0x7070),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110db6, 0x4004),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110db4, 0x0500),      // loop_div/input_div
    _RV32_2(0x110d90, 0x0500),
//  _RV32_2(0x110db4, 0x0300),      // loop_div/input_div
    _RV32_2(0x110db6, 0x4000), 
    _RV32_2(0x110db0, 0xd72c),      // ddfset
    _RV32_2(0x110db2, 0x0056),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x100602, 0x02A2),      // ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+4banks+10col+4x
    _RV32_2(0x100604, 0x008b),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x100606, 0x3420),      //refresh cycle=0x20 ,TURN_ON_SCRAMBLE=0x8420
    _RV32_2(0x100608, 0x1877),      // reg_tRCD
    _RV32_2(0x10060a, 0x1F56),      // reg_tRRD
    _RV32_2(0x10060c, 0x5485),      // reg_tWL
    _RV32_2(0x10060e, 0x2044),      //tRFC
//  _RV32_2(0x100610, 0x0A62),      // MR0
    _RV32_2(0x100610, 0x0a62),      // MR0
    _RV32_2(0x100612, 0x4002),      // MR1
    _RV32_2(0x100614, 0x8000),      //MR2
    _RV32_2(0x100616, 0xC000),      //MR3
    _RV32_2(0x110d80, 0x0401),      // miu_0_atop  start
    _RV32_2(0x110db8, 0x0033),      // DQ0/DQ1 phase / dqs0/dqs1 phase
    _RV32_2(0x110d82, 0x0000),
    _RV32_2(0x110dba, 0x7070),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110dbc, 0x0200),
    _RV32_2(0x110dbe, 0x0022),
    _RV32_2(0x110d8e, 0x00e7),      // 1/2 reg_en_mask
    _RV32_2(0x110d8e, 0x00a7),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
    _RV32_2(0x110dee, 0x0088),      //reg_dll0_ph //
    _RV32_2(0x110dea, 0x00c2),      //reg_dll1_code   //refine when DDR_CLK change
    _RV32_2(0x110de8, 0x00c2),      //reg_dll0_code   //refine when DDR_CLK change
    _RV32_2(0x110de4, 0xf200),
    _RV32_2(0x110de2, 0x4032),
    _RV32_2(0x110dd4, 0x0000),
    _RV32_2(0x110dDC, 0x3333),      // pad driver
    _RV32_2(0x110dDE, 0x3333),      // pad driver
    _RV32_2(0x110dE0, 0x2378),      // reg_auto calibration
    _RV32_2(0x110dF2, 0x5855),      //
    _RV32_2(0x110dd4, 0x0000),      //turn off atop+pd
    _RV32_2(0x110dfe, 0x0000),

#elif defined(CONFIG_MIU1_DDR2_1066)

    _RV32_2(0x110dba, 0x0500),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110db6, 0xc000),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110db4, 0x0000),      // loop_div/input_div
    _RV32_2(0x110db0, 0x1eb6),      // ddfset
    _RV32_2(0x110db2, 0x0045),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x100602, 0x02a2),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x100604, 0x008b),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x100606, 0x3420),      //refresh cycle=0x20 ,TURN_ON_SCRAMBLE=0x8420
    _RV32_2(0x100608, 0x1877),      //reg_tRCD
    _RV32_2(0x10060a, 0x1f56),      //reg_tRRD
    _RV32_2(0x10060c, 0x5486),      //reg_tWL
    _RV32_2(0x10060e, 0x2044),      //tRFC
    _RV32_2(0x100610, 0x0a72),      //MR0
    _RV32_2(0x100612, 0x4004),      //MR1
    _RV32_2(0x100614, 0x8000),      //MR2
    _RV32_2(0x100616, 0xC000),      //MR3
    _RV32_2(0x110dd4, 0x0000),      //miu_0_atop  start
    _RV32_2(0x110d80, 0x0011),      
    _RV32_2(0x110d90, 0x0500),
    _RV32_2(0x110da2, 0x0000),
    _RV32_2(0x110db8, 0x0033),      // DQ0/DQ1 phase / dqs0/dqs1 phase
    _RV32_2(0x110dba, 0x4040),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110d82, 0x0000),
    _RV32_2(0x110dbc, 0x0022),
    _RV32_2(0x110dbe, 0x0000),
    _RV32_2(0x110d8e, 0x00e7),      // 1/2 reg_en_mask
    _RV32_2(0x110d8e, 0x00a7),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
    _RV32_2(0x110ddC, 0x3333),
    _RV32_2(0x110ddE, 0x3333),
    _RV32_2(0x110de2, 0x4032),
    _RV32_2(0x110de4, 0xF200),      //reg_dll0_ph //
    _RV32_2(0x110df2, 0x5805),
    _RV32_2(0x110dee, 0x0055),      //reg_dll0_ph //
    _RV32_2(0x110dea, 0x00c2),      //reg_dll1_code   //refine when DDR_CLK change
    _RV32_2(0x110de8, 0x00c2),      //reg_dll0_code   //refine when DDR_CLK change
    _RV32_2(0x110de0, 0x000C),
    _RV32_2(0x110de0, 0x0008),
    _RV32_2(0x110de0, 0x2378),
    _RV32_2(0x110dd4, 0x0000),      //turn off atop+pd
    _RV32_2(0x110dfe, 0x0000),

#else
    #error "Invalid DRAM Setting"
#endif

    _END_OF_TBL32_,
};
#endif

#endif  //ENABLE_MSTAR_BD_MST180A_D01A_S

#endif /* _MIU_MST180A_D01A_S_H_ */
