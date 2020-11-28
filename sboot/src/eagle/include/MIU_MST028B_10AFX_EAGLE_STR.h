////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2012 MStar Semiconductor, Inc.
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

#ifndef _MIU_MST028B_10AFX_EAGLE_STR_H_
#define _MIU_MST028B_10AFX_EAGLE_STR_H_

#if (ENABLE_MSTAR_BD_MST028B_10AFX_EAGLE)

const MS_REG_INIT MIU0_DDR_Init_STR[] =
{
#if defined(CONFIG_MIU0_DDR3_1333)

    _RV32_2(0x110d3a, 0x0000),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110d36, 0x4000),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110d34, 0x0300),      // loop_div/input_div
    _RV32_2(0x110d30, 0x6b0e),      // ddfset
    _RV32_2(0x110d32, 0x001f),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x101202, 0xf3a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x101204, 0x0009),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x101206, 0x1420),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x101208, 0x1899),      //reg_tRCD
    _RV32_2(0x10120a, 0x2155),      //reg_tRRD
    _RV32_2(0x10120c, 0x95a8),      //reg_tWL
    _RV32_2(0x10120e, 0x404a),      //tRFC
    _RV32_2(0x101210, 0x1a50),      //MR0
    _RV32_2(0x101212, 0x4004),      //MR1
    _RV32_2(0x101214, 0x8010),      //MR2
    _RV32_2(0x101216, 0xC000),      //MR3
    _RV32_2(0x101228, 0x00B0),
    _RV32_2(0x10122c, 0x6199),      // Address Balance Mode

//bandwidth setting
    _RV32_2(0x101242, 0x0008),      // (member limit setting for group 0)
    _RV32_2(0x101244, 0x0200),      // (timeout setting for group 0)
    _RV32_2(0x101262, 0x0008),      // (member limit setting for group 1)
    _RV32_2(0x101264, 0x0200),      // (timeout setting for group 1)
    _RV32_2(0x101282, 0x0008),      // (member limit setting for group 2)
    _RV32_2(0x101284, 0x0200),      // (timeout setting for group 2)
    _RV32_2(0x1012a2, 0x0008),      // (member limit setting for group 3)
    _RV32_2(0x1012a4, 0x0200),      // (timeout setting for group 3)
    _RV32_2(0x101240, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group0)
    _RV32_2(0x101260, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group1)
    _RV32_2(0x101280, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group2)
    _RV32_2(0x1012a0, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group3)

    _RV32_2(0x110d54, 0x0070),      //miu_0_atop  start
    _RV32_2(0x110d00, 0x0208),      
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
    _RV32_2(0x110d38, 0x0033),
    _RV32_2(0x110d3a, 0x0000),
    _RV32_2(0x110d3c, 0x0055),
    _RV32_2(0x110d3e, 0x0200),
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
    _RV32_2(0x110d54, 0x0070),
    _RV32_2(0x110d56, 0x0000),
    _RV32_2(0x110d58, 0x0000),
    _RV32_2(0x110d5a, 0x0000),
    _RV32_2(0x110d5c, 0x3333),
    _RV32_2(0x110d5e, 0x3333),
    _RV32_2(0x110d60, 0x2370),
    _RV32_2(0x110d62, 0x0032),
    _RV32_2(0x110d64, 0xf200),
    _RV32_2(0x110d66, 0x0000),
    _RV32_2(0x110d68, 0x0020),
    _RV32_2(0x110d6a, 0x0020),
    _RV32_2(0x110d6c, 0x0000),
    _RV32_2(0x110d6e, 0x0088),
    _RV32_2(0x110d72, 0x0008),
    _RV32_2(0x110d72, 0x6806),
    _RV32_2(0x110d0e, 0x00a5),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel

    _RV32_2(0x110d7e, 0x0000),

#elif defined(CONFIG_MIU0_DDR3_1666)

    _RV32_2(0x110d3a, 0x0000),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110d36, 0x4002),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110d34, 0x0300),      // loop_div/input_div
    _RV32_2(0x110d30, 0x2e8b),      // ddfset
    _RV32_2(0x110d32, 0x001a),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x101202, 0xf3a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x101204, 0x000b),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x101206, 0x342b),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x101208, 0x1cbb),      //reg_tRCD
    _RV32_2(0x10120a, 0x2766),      //reg_tRRD
    _RV32_2(0x10120c, 0xb6c8),      //reg_tWL
    _RV32_2(0x10120e, 0x4080),      //tRFC
    _RV32_2(0x101210, 0x1c70),      //MR0
    _RV32_2(0x101212, 0x4004),      //MR1
    _RV32_2(0x101214, 0x8018),      //MR2
    _RV32_2(0x101216, 0xC000),      //MR3
    _RV32_2(0x101228, 0x72b6),
    _RV32_2(0x10122a, 0x0034),
    _RV32_2(0x10122c, 0x6199),      // Address Balance Mode

//bandwidth setting
    _RV32_2(0x101242, 0x0008),      // (member limit setting for group 0)
    _RV32_2(0x101244, 0x0200),      // (timeout setting for group 0)
    _RV32_2(0x101262, 0x0008),      // (member limit setting for group 1)
    _RV32_2(0x101264, 0x0200),      // (timeout setting for group 1)
    _RV32_2(0x101282, 0x0008),      // (member limit setting for group 2)
    _RV32_2(0x101284, 0x0200),      // (timeout setting for group 2)
    _RV32_2(0x1012a2, 0x0008),      // (member limit setting for group 3)
    _RV32_2(0x1012a4, 0x0200),      // (timeout setting for group 3)
    _RV32_2(0x101240, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group0)
    _RV32_2(0x101260, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group1)
    _RV32_2(0x101280, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group2)
    _RV32_2(0x1012a0, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group3)
    _RV32_2(0x10125a, 0x4000),

    _RV32_2(0x110d54, 0x0070),      //miu_0_atop  start
    _RV32_2(0x110d00, 0x0408),      
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
    _RV32_2(0x110d20, 0x0020),
    _RV32_2(0x110d22, 0x0000),
    _RV32_2(0x110d24, 0x0000),
    _RV32_2(0x110d24, 0x0000),
    _RV32_2(0x110d26, 0x0000),
    _RV32_2(0x110d28, 0x0000),
    _RV32_2(0x110d2a, 0x0000),
    _RV32_2(0x110d2c, 0x0014),
    _RV32_2(0x110d2e, 0x0000),
    _RV32_2(0x110d38, 0x1165),
    _RV32_2(0x110d3a, 0x7070),
    _RV32_2(0x110d3c, 0x0066),
    _RV32_2(0x110d3e, 0x0000),
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
    _RV32_2(0x110d54, 0x0070),
    _RV32_2(0x110d56, 0x0000),
    _RV32_2(0x110d58, 0x0000),
    _RV32_2(0x110d5a, 0x0000),
    _RV32_2(0x110d5c, 0x3333),
    _RV32_2(0x110d5e, 0x3333),
    _RV32_2(0x110d60, 0x2370),
    _RV32_2(0x110d62, 0x0032),
    _RV32_2(0x110d64, 0xf200),
    _RV32_2(0x110d66, 0x0000),
    _RV32_2(0x110d68, 0x0020),
    _RV32_2(0x110d6a, 0x0020),
    _RV32_2(0x110d6c, 0x0000),
    _RV32_2(0x110d6e, 0x0068),
    _RV32_2(0x110d72, 0x0008),
    _RV32_2(0x110d72, 0x5804),
    _RV32_2(0x110d0e, 0x00a5),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel

    _RV32_2(0x110d7e, 0x0000),

#elif defined(CONFIG_MIU0_DDR2_800)

    _RV32_2(0x110d3a, 0x0000),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110d36, 0x4000),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110d34, 0x0300),      // loop_div/input_div
    _RV32_2(0x110d30, 0xa123),      // ddfset
    _RV32_2(0x110d32, 0x0034),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x101202, 0x02a2),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x101204, 0x008b),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x101206, 0x0420),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x101208, 0x1066),      //reg_tRCD
    _RV32_2(0x10120a, 0x1644),      //reg_tRRD
    _RV32_2(0x10120c, 0x7465),      //reg_tWL
    _RV32_2(0x10120e, 0x204d),      //tRFC
    _RV32_2(0x101210, 0x0a62),      //MR0
    _RV32_2(0x101212, 0x4004),      //MR1
    _RV32_2(0x101214, 0x8000),      //MR2
    _RV32_2(0x101216, 0xC000),      //MR3

//bandwidth setting
    _RV32_2(0x101242, 0x0008),      // (member limit setting for group 0)
    _RV32_2(0x101244, 0x0200),      // (timeout setting for group 0)
    _RV32_2(0x101262, 0x0008),      // (member limit setting for group 1)
    _RV32_2(0x101264, 0x0200),      // (timeout setting for group 1)
    _RV32_2(0x101282, 0x0008),      // (member limit setting for group 2)
    _RV32_2(0x101284, 0x0200),      // (timeout setting for group 2)
    _RV32_2(0x1012a2, 0x0008),      // (member limit setting for group 3)
    _RV32_2(0x1012a4, 0x0200),      // (timeout setting for group 3)
    _RV32_2(0x101240, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group0)
    _RV32_2(0x101260, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group1)
    _RV32_2(0x101280, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group2)
    _RV32_2(0x1012a0, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group3)

    _RV32_2(0x110d54, 0x0070),      //miu_0_atop  start
    _RV32_2(0x110d00, 0x000d),
    _RV32_2(0x110d10, 0x0500),
    _RV32_2(0x110d22, 0x0000),
    _RV32_2(0x110d38, 0x0033),      // DQ0/DQ1 phase / dqs0/dqs1 phase
    _RV32_2(0x110d3a, 0x0000),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110d02, 0x0000),
    _RV32_2(0x110d3c, 0x0200),
    _RV32_2(0x110d3e, 0x0022),
    _RV32_2(0x110d0e, 0x00e7),      // 1/2 reg_en_mask
    _RV32_2(0x110d0e, 0x00a7),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
    _RV32_2(0x110d5C, 0x3333),
    _RV32_2(0x110d5E, 0x3333),
    _RV32_2(0x110d62, 0x4032),
    _RV32_2(0x110d72, 0x5805),
    _RV32_2(0x110d64, 0xF200),      //reg_dll0_ph //
    _RV32_2(0x110d6e, 0x0055),      //reg_dll0_ph //
    _RV32_2(0x110d6a, 0x004f),      //reg_dll1_code   //refine when DDR_CLK change
    _RV32_2(0x110d68, 0x004f),      //reg_dll0_code   //refine when DDR_CLK change
    _RV32_2(0x110d60, 0x000C),
    _RV32_2(0x110d60, 0x0008),
    _RV32_2(0x110d60, 0x2378),
    _RV32_2(0x110d54, 0x0070),      //turn off atop+pd

    _RV32_2(0x110d7e, 0x0000),

#elif defined(CONFIG_MIU0_DDR2_1066)

    _RV32_2(0x110d3a, 0x0500),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110d36, 0x4002),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110d34, 0x0300),      // loop_div/input_div
    _RV32_2(0x110d30, 0x1b87),      // ddfset
    _RV32_2(0x110d32, 0x0028),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x101202, 0x02a2),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x101204, 0x008b),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x101206, 0x0420),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x101208, 0x1677),      //reg_tRCD
    _RV32_2(0x10120a, 0x1d46),      //reg_tRRD
    _RV32_2(0x10120c, 0x7486),      //reg_tWL
    _RV32_2(0x10120e, 0x206a),      //tRFC
    _RV32_2(0x101210, 0x0e72),      //MR0
    _RV32_2(0x101212, 0x4004),      //MR1
    _RV32_2(0x101214, 0x8000),      //MR2
    _RV32_2(0x101216, 0xC000),      //MR3

//bandwidth setting
    _RV32_2(0x101242, 0x0008),      // (member limit setting for group 0)
    _RV32_2(0x101244, 0x0200),      // (timeout setting for group 0)
    _RV32_2(0x101262, 0x0008),      // (member limit setting for group 1)
    _RV32_2(0x101264, 0x0200),      // (timeout setting for group 1)
    _RV32_2(0x101282, 0x0008),      // (member limit setting for group 2)
    _RV32_2(0x101284, 0x0200),      // (timeout setting for group 2)
    _RV32_2(0x1012a2, 0x0008),      // (member limit setting for group 3)
    _RV32_2(0x1012a4, 0x0200),      // (timeout setting for group 3)
    _RV32_2(0x101240, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group0)
    _RV32_2(0x101260, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group1)
    _RV32_2(0x101280, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group2)
    _RV32_2(0x1012a0, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group3)

    _RV32_2(0x110d54, 0x0070),      //miu_0_atop  start
    _RV32_2(0x110d00, 0x000d),      
    _RV32_2(0x110d10, 0x0500),
    _RV32_2(0x110d22, 0x0000),
    _RV32_2(0x110d38, 0x0033),      // DQ0/DQ1 phase / dqs0/dqs1 phase
    _RV32_2(0x110d3a, 0x0000),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
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
    _RV32_2(0x110d6e, 0x0077),      //reg_dll0_ph //
    _RV32_2(0x110d6a, 0x00c2),      //reg_dll1_code   //refine when DDR_CLK change
    _RV32_2(0x110d68, 0x00c2),      //reg_dll0_code   //refine when DDR_CLK change
    _RV32_2(0x110d60, 0x000C),
    _RV32_2(0x110d60, 0x0008),
    _RV32_2(0x110d60, 0x2378),
    _RV32_2(0x110d54, 0x0070),      //turn off atop+pd

    _RV32_2(0x110d7e, 0x0000),

#else
    #error "Invalid DRAM Setting"
#endif

    _END_OF_TBL32_,
    MIU_VER
};

#ifndef CONFIG_MIU1_DRAM_NONE
const MS_REG_INIT MIU1_DDR_Init_STR[] =
{
#if defined(CONFIG_MIU1_DDR3_1333)

    _RV32_2(0x110dba, 0x0000),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110db6, 0x4000),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110db4, 0x0300),      // loop_div/input_div
    _RV32_2(0x110db0, 0x6b0e),      // ddfset
    _RV32_2(0x110db2, 0x001f),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x100602, 0xf3a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x100604, 0x0009),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x100606, 0x1420),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x100608, 0x1899),      //reg_tRCD
    _RV32_2(0x10060a, 0x2155),      //reg_tRRD
    _RV32_2(0x10060c, 0x95a8),      //reg_tWL
    _RV32_2(0x10060e, 0x404a),      //tRFC
    _RV32_2(0x100610, 0x1a50),      //MR0
    _RV32_2(0x100612, 0x4004),      //MR1
    _RV32_2(0x100614, 0x8010),      //MR2
    _RV32_2(0x100616, 0xC000),      //MR3
    _RV32_2(0x100628, 0x00B0),
    _RV32_2(0x10062c, 0x6199),      // Address Balance Mode

//bandwidth setting
    _RV32_2(0x100642, 0x0008),      // (member limit setting for group 0)
    _RV32_2(0x100644, 0x0200),      // (timeout setting for group 0)
    _RV32_2(0x100662, 0x0008),      // (member limit setting for group 1)
    _RV32_2(0x100664, 0x0200),      // (timeout setting for group 1)
    _RV32_2(0x100682, 0x0008),      // (member limit setting for group 2)
    _RV32_2(0x100684, 0x0200),      // (timeout setting for group 2)
    _RV32_2(0x1006a2, 0x0008),      // (member limit setting for group 3)
    _RV32_2(0x1006a4, 0x0200),      // (timeout setting for group 3)
    _RV32_2(0x100640, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group0)
    _RV32_2(0x100660, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group1)
    _RV32_2(0x100680, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group2)
    _RV32_2(0x1006a0, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group3)

    _RV32_2(0x110dd4, 0x0070),      //miu_0_atop  start
    _RV32_2(0x110d80, 0x0208),
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
    _RV32_2(0x110db8, 0x0033),
    _RV32_2(0x110dba, 0x0000),
    _RV32_2(0x110dbc, 0x0055),
    _RV32_2(0x110dbe, 0x0200),
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
    _RV32_2(0x110dd4, 0x0070),
    _RV32_2(0x110dd6, 0x0000),
    _RV32_2(0x110dd8, 0x0000),
    _RV32_2(0x110dda, 0x0000),
    _RV32_2(0x110ddc, 0x3333),
    _RV32_2(0x110dde, 0x3333),
    _RV32_2(0x110de0, 0x2370),
    _RV32_2(0x110de2, 0x0032),
    _RV32_2(0x110de4, 0xf200),
    _RV32_2(0x110de6, 0x0000),
    _RV32_2(0x110de8, 0x0020),
    _RV32_2(0x110dea, 0x0020),
    _RV32_2(0x110dec, 0x0000),
    _RV32_2(0x110dee, 0x0088),
    _RV32_2(0x110df2, 0x0008),
    _RV32_2(0x110df2, 0x6806),
    _RV32_2(0x110d8e, 0x00a5),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel

    _RV32_2(0x110dfe, 0x0000),

    // bugfix: set default miu1 sel for usb, fcie for 1st burn code after erase all env    
    _RV32_2(0x110df0, 0x4E00),
    _RV32_2(0x110df6, 0x0100),

#elif defined(CONFIG_MIU1_DDR3_1666)

    _RV32_2(0x110dba, 0x0000),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110db6, 0x4002),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110db4, 0x0300),      // loop_div/input_div
    _RV32_2(0x110db0, 0x2e8b),      // ddfset
    _RV32_2(0x110db2, 0x001a),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x100602, 0xf3a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x100604, 0x000b),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x100606, 0x342b),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x100608, 0x1cbb),      //reg_tRCD
    _RV32_2(0x10060a, 0x2766),      //reg_tRRD
    _RV32_2(0x10060c, 0xb6c8),      //reg_tWL
    _RV32_2(0x10060e, 0x4080),      //tRFC
    _RV32_2(0x100610, 0x1c70),      //MR0
    _RV32_2(0x100612, 0x4004),      //MR1
    _RV32_2(0x100614, 0x8018),      //MR2
    _RV32_2(0x100616, 0xC000),      //MR3
    _RV32_2(0x100628, 0x72b6),
    _RV32_2(0x10062a, 0x0034),
    _RV32_2(0x10062c, 0x6199),      // Address Balance Mode

//bandwidth setting
    _RV32_2(0x100642, 0x0008),      // (member limit setting for group 0)
    _RV32_2(0x100644, 0x0200),      // (timeout setting for group 0)
    _RV32_2(0x100662, 0x0008),      // (member limit setting for group 1)
    _RV32_2(0x100664, 0x0200),      // (timeout setting for group 1)
    _RV32_2(0x100682, 0x0008),      // (member limit setting for group 2)
    _RV32_2(0x100684, 0x0200),      // (timeout setting for group 2)
    _RV32_2(0x1006a2, 0x0008),      // (member limit setting for group 3)
    _RV32_2(0x1006a4, 0x0200),      // (timeout setting for group 3)
    _RV32_2(0x100640, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group0)
    _RV32_2(0x100660, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group1)
    _RV32_2(0x100680, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group2)
    _RV32_2(0x1006a0, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group3)
    _RV32_2(0x10065a, 0x4000),

    _RV32_2(0x110d54, 0x0070),      //miu_0_atop  start
    _RV32_2(0x110d80, 0x0408),
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
    _RV32_2(0x110da0, 0x0020),
    _RV32_2(0x110da2, 0x0000),
    _RV32_2(0x110da4, 0x0000),
    _RV32_2(0x110da6, 0x0000),
    _RV32_2(0x110da8, 0x0000),
    _RV32_2(0x110daa, 0x0000),
    _RV32_2(0x110dac, 0x0014),
    _RV32_2(0x110dae, 0x0000),
    _RV32_2(0x110db8, 0x1165),
    _RV32_2(0x110dba, 0x6070),
    _RV32_2(0x110dbc, 0x0066),
    _RV32_2(0x110dbe, 0x0000),
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
    _RV32_2(0x110dd4, 0x0070),
    _RV32_2(0x110dd6, 0x0000),
    _RV32_2(0x110dd8, 0x0000),
    _RV32_2(0x110dda, 0x0000),
    _RV32_2(0x110ddc, 0x3333),
    _RV32_2(0x110dde, 0x3333),
    _RV32_2(0x110de0, 0x2370),
    _RV32_2(0x110de2, 0x0032),
    _RV32_2(0x110de4, 0xf200),
    _RV32_2(0x110de6, 0x0000),
    _RV32_2(0x110de8, 0x0020),
    _RV32_2(0x110dea, 0x0020),
    _RV32_2(0x110dec, 0x0000),
    _RV32_2(0x110dee, 0x0068),
    _RV32_2(0x110df2, 0x0008),
    _RV32_2(0x110df2, 0x5804),
    _RV32_2(0x110d8e, 0x00a5),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel

    _RV32_2(0x110dfe, 0x0000),

    // bugfix: set default miu1 sel for usb, fcie for 1st burn code after erase all env    
    _RV32_2(0x110df0, 0x4E00),
    _RV32_2(0x110df6, 0x0100),

#elif defined(CONFIG_MIU1_DDR2_800)

    _RV32_2(0x110dba, 0x0000),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110db6, 0x4000),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110db4, 0x0300),      // loop_div/input_div
    _RV32_2(0x110db0, 0xa123),      // ddfset
    _RV32_2(0x110db2, 0x0034),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x100602, 0xf2a2),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x100604, 0x008b),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x100606, 0x0420),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x100608, 0x1066),      //reg_tRCD
    _RV32_2(0x10060a, 0x1644),      //reg_tRRD
    _RV32_2(0x10060c, 0x7465),      //reg_tWL
    _RV32_2(0x10060e, 0x204d),      //tRFC
    _RV32_2(0x100610, 0x0a62),      //MR0
    _RV32_2(0x100612, 0x4004),      //MR1
    _RV32_2(0x100614, 0x8000),      //MR2
    _RV32_2(0x100616, 0xC000),      //MR3

//bandwidth setting
    _RV32_2(0x100642, 0x0008),      // (member limit setting for group 0)
    _RV32_2(0x100644, 0x0200),      // (timeout setting for group 0)
    _RV32_2(0x100662, 0x0008),      // (member limit setting for group 1)
    _RV32_2(0x100664, 0x0200),      // (timeout setting for group 1)
    _RV32_2(0x100682, 0x0008),      // (member limit setting for group 2)
    _RV32_2(0x100684, 0x0200),      // (timeout setting for group 2)
    _RV32_2(0x1006a2, 0x0008),      // (member limit setting for group 3)
    _RV32_2(0x1006a4, 0x0200),      // (timeout setting for group 3)
    _RV32_2(0x100640, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group0)
    _RV32_2(0x100660, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group1)
    _RV32_2(0x100680, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group2)
    _RV32_2(0x1006a0, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group3)

    _RV32_2(0x110dd4, 0x0070),      //miu_0_atop  start
    _RV32_2(0x110d80, 0x000d),
    _RV32_2(0x110d90, 0x0500),
    _RV32_2(0x110da2, 0x0000),
    _RV32_2(0x110db8, 0x0033),      // DQ0/DQ1 phase / dqs0/dqs1 phase
    _RV32_2(0x110dba, 0x0000),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110d82, 0x0000),
    _RV32_2(0x110dbc, 0x0200),
    _RV32_2(0x110dbe, 0x0022),
    _RV32_2(0x110d8e, 0x00e7),      // 1/2 reg_en_mask
    _RV32_2(0x110d8e, 0x00a7),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
    _RV32_2(0x110ddC, 0x3333),
    _RV32_2(0x110ddE, 0x3333),
    _RV32_2(0x110de2, 0x4032),
    _RV32_2(0x110df2, 0x5805),
    _RV32_2(0x110de4, 0xF200),      //reg_dll0_ph //
    _RV32_2(0x110dee, 0x0055),      //reg_dll0_ph //
    _RV32_2(0x110dea, 0x004f),      //reg_dll1_code   //refine when DDR_CLK change
    _RV32_2(0x110de8, 0x004f),      //reg_dll0_code   //refine when DDR_CLK change
    _RV32_2(0x110de0, 0x000C),
    _RV32_2(0x110de0, 0x0008),
    _RV32_2(0x110de0, 0x2378),
    _RV32_2(0x110dd4, 0x0070),      //turn off atop+pd

    _RV32_2(0x110dfe, 0x0000),

#elif defined(CONFIG_MIU1_DDR2_1066)

    _RV32_2(0x110dba, 0x0500),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110db6, 0x4002),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110db4, 0x0300),      // loop_div/input_div
    _RV32_2(0x110db0, 0x1b87),      // ddfset
    _RV32_2(0x110db2, 0x0028),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x100602, 0xf2a2),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x100604, 0x008b),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x100606, 0x0420),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x100608, 0x1677),      //reg_tRCD
    _RV32_2(0x10060a, 0x1d46),      //reg_tRRD
    _RV32_2(0x10060c, 0x7486),      //reg_tWL
    _RV32_2(0x10060e, 0x206a),      //tRFC
    _RV32_2(0x100610, 0x0e72),      //MR0
    _RV32_2(0x100612, 0x4004),      //MR1
    _RV32_2(0x100614, 0x8000),      //MR2
    _RV32_2(0x100616, 0xC000),      //MR3

//bandwidth setting
    _RV32_2(0x100642, 0x0008),      // (member limit setting for group 0)
    _RV32_2(0x100644, 0x0200),      // (timeout setting for group 0)
    _RV32_2(0x100662, 0x0008),      // (member limit setting for group 1)
    _RV32_2(0x100664, 0x0200),      // (timeout setting for group 1)
    _RV32_2(0x100682, 0x0008),      // (member limit setting for group 2)
    _RV32_2(0x100684, 0x0200),      // (timeout setting for group 2)
    _RV32_2(0x1006a2, 0x0008),      // (member limit setting for group 3)
    _RV32_2(0x1006a4, 0x0200),      // (timeout setting for group 3)
    _RV32_2(0x100640, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group0)
    _RV32_2(0x100660, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group1)
    _RV32_2(0x100680, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group2)
    _RV32_2(0x1006a0, 0x8015),      //(timeout enable, member limit enable, round robin, arbiter skip on for group3)

    _RV32_2(0x110dd4, 0x0070),      //miu_0_atop  start
    _RV32_2(0x110d80, 0x000d),      
    _RV32_2(0x110d90, 0x0500),
    _RV32_2(0x110da2, 0x0000),
    _RV32_2(0x110db8, 0x0033),      // DQ0/DQ1 phase / dqs0/dqs1 phase
    _RV32_2(0x110dba, 0x0000),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110d82, 0x0000),
    _RV32_2(0x110dbc, 0x0022),
    _RV32_2(0x110dbe, 0x0000),
    _RV32_2(0x110d8e, 0x00e7),      // 1/2 reg_en_mask
    _RV32_2(0x110d8e, 0x00a7),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
    _RV32_2(0x110ddC, 0x3333),
    _RV32_2(0x110ddE, 0x3333),
    _RV32_2(0x110de2, 0x4032),
    _RV32_2(0x110df2, 0x5805),
    _RV32_2(0x110de4, 0xF200),      //reg_dll0_ph //
    _RV32_2(0x110dee, 0x0077),      //reg_dll0_ph //
    _RV32_2(0x110dea, 0x00c2),      //reg_dll1_code   //refine when DDR_CLK change
    _RV32_2(0x110de8, 0x00c2),      //reg_dll0_code   //refine when DDR_CLK change
    _RV32_2(0x110de0, 0x000C),
    _RV32_2(0x110de0, 0x0008),
    _RV32_2(0x110de0, 0x2378),
    _RV32_2(0x110dd4, 0x0070),      //turn off atop+pd

    _RV32_2(0x110dfe, 0x0000),

#else
    #error "Invalid DRAM Setting"
#endif

    _END_OF_TBL32_,
};
#endif

#endif  //ENABLE_MSTAR_BD_MST028B_10AFX_EAGLE

#endif /* _MIU_MST028B_10AFX_EAGLE_STR_H_ */

