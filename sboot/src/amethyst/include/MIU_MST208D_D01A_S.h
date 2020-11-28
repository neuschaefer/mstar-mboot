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

#ifndef _MIU_MST208D_D01A_S_H_
#define _MIU_MST208D_D01A_S_H_

#if (ENABLE_MSTAR_BD_MST208D_D01A_S)

const MS_REG_INIT MIU0_DDR_Init[] =
{
#if defined(CONFIG_MIU0_DDR3_1333)

    _RV32_2(0x110d3a, 0x0000),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110d36, 0x4000),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110d34, 0x0300),      // loop_div/input_div
    _RV32_2(0x110d30, 0x7316),      // ddfset
    _RV32_2(0x110d32, 0x0016),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x110d28, 0x8012),
    _RV32_2(0x110d2a, 0x03ae),
    _RV32_2(0x101202, 0x03a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x101204, 0x000c),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x101206, 0x3534),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x101208, 0x20dd),      //reg_tRCD
    _RV32_2(0x10120a, 0x2d76),      //reg_tRRD
    _RV32_2(0x10120c, 0xb7e9),      //reg_tWL
    _RV32_2(0x10120e, 0x4067),      //tRFC
    _RV32_2(0x101210, 0x1f14),      //MR0
    _RV32_2(0x101212, 0x4004),      //MR1
    _RV32_2(0x101214, 0x8020),      //MR2
    _RV32_2(0x101216, 0xC000),      //MR3
    _RV32_2(0x101228, 0x0090),      //odtm_dly
    _RV32_2(0x10122c, 0x6199),      // Address Balance Mode
    _RV32_2(0x110d54, 0x0000),      //miu_0_atop  start
    _RV32_2(0x110d00, 0x0411),
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
    _RV32_2(0x110d3a, 0x0000),
    _RV32_2(0x110d38, 0x3377),
    _RV32_2(0x110d3a, 0x0000),
    _RV32_2(0x110d3c, 0x0233),
    _RV32_2(0x110d3e, 0x0022),
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
    _RV32_2(0x110d6e, 0x0078),
    _RV32_2(0x110d72, 0x8805),
    _RV32_2(0x110d0e, 0x00a7),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
    _RV32_2(0x10121e, 0x0c01),
    _RV32_2(0x10121e, 0x0c00),
    _RV32_2(0x110d7e, 0x0000),
    _RV32_2(0x110d00, 0x0401),
    _RV32_2(0x110d02, 0xaaaa),

#elif defined(CONFIG_MIU0_DDR3_1666)

    _RV32_2(0x110d3a, 0x0000),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110d36, 0x4000),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110d34, 0x0300),      // loop_div/input_div
    _RV32_2(0x110d30, 0x2e8b),      // ddfset
    _RV32_2(0x110d32, 0x001a),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x101202, 0x03a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x101204, 0x000B),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x101206, 0x3434),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x101208, 0x1cbb),      //reg_tRCD
    _RV32_2(0x10120a, 0x2766),      //reg_tRRD
    _RV32_2(0x10120c, 0x96ca),      //reg_tWL
    _RV32_2(0x10120e, 0x4080),      //tRFC
    _RV32_2(0x101210, 0x1c70),      //MR0
    _RV32_2(0x101212, 0x4004),      //MR1
    _RV32_2(0x101214, 0x8018),      //MR2
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
    _RV32_2(0x110d3c, 0x0033),
    _RV32_2(0x110d38, 0x3377),
    _RV32_2(0x110d3a, 0x0000),
    _RV32_2(0x110d3c, 0x0077),
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
    _RV32_2(0x110d72, 0x5805),
    _RV32_2(0x110d0e, 0x00a5),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
    _RV32_2(0x110d7e, 0x0000),

#elif defined(CONFIG_MIU0_DDR2_800)

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

#elif defined(CONFIG_MIU0_DDR2_1066)

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
    #error "Invalid DRAM Setting"
#endif

    _END_OF_TBL32_,
    MIU_VER
};

#ifndef CONFIG_MIU1_DRAM_NONE
const MS_REG_INIT MIU1_DDR_Init[] =
{
#if defined(CONFIG_MIU1_DDR3_1333)

    _RV32_2(0x110dba, 0x0000),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110db6, 0x4000),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110db4, 0x0300),      // loop_div/input_div
    _RV32_2(0x110db0, 0x7316),      // ddfset
    _RV32_2(0x110db2, 0x0016),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x110da8, 0x8012),
    _RV32_2(0x110daa, 0x03ae),
    _RV32_2(0x100602, 0x03a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x100604, 0x000c),      //if I64Mode =0x8b else =0x0b
    _RV32_2(0x100606, 0x3534),      //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2(0x100608, 0x20dd),      //reg_tRCD
    _RV32_2(0x10060a, 0x2d76),      //reg_tRRD
    _RV32_2(0x10060c, 0xb7e9),      //reg_tWL
    _RV32_2(0x10060e, 0x4067),      //tRFC
    _RV32_2(0x100610, 0x1f14),      //MR0
    _RV32_2(0x100612, 0x4004),      //MR1
    _RV32_2(0x100614, 0x8020),      //MR2
    _RV32_2(0x100616, 0xC000),      //MR3
    _RV32_2(0x100628, 0x0090),      //odtm_dly
    _RV32_2(0x10062c, 0x6199),      // Address Balance Mode
    _RV32_2(0x110dd4, 0x0000),      //miu_0_atop  start
    _RV32_2(0x110d80, 0x0411),
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
    _RV32_2(0x110da4, 0x0000),
    _RV32_2(0x110da6, 0x0000),
    _RV32_2(0x110da8, 0x0000),
    _RV32_2(0x110daa, 0x0000),
    _RV32_2(0x110dac, 0x0014),
    _RV32_2(0x110dae, 0x0000),
    _RV32_2(0x110dba, 0x0000),
    _RV32_2(0x110db8, 0x3377),
    _RV32_2(0x110dba, 0x0000),
    _RV32_2(0x110dbc, 0x0233),
    _RV32_2(0x110dbe, 0x0022),
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
    _RV32_2(0x110dee, 0x0068),
    _RV32_2(0x110df2, 0x8805),
    _RV32_2(0x110d8e, 0x00a7),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
    _RV32_2(0x10061e, 0x0c01),
    _RV32_2(0x10061e, 0x0c00),
    _RV32_2(0x110dfe, 0x0000),
    _RV32_2(0x110d80, 0x0401),
    _RV32_2(0x110d82, 0xaaaa),

#elif defined(CONFIG_MIU1_DDR3_1666)

    _RV32_2(0x110dba, 0x0000),      // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2(0x110db4, 0x0300),      // loop_div/input_div
    _RV32_2(0x110db6, 0x4000),      // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2(0x110db0, 0x2e8b),      // ddfset
    _RV32_2(0x110db2, 0x001a),      // ddrpll_reset/ddrpll_porst/ddrpl_pd
    _RV32_2(0x100602, 0x03a3),      //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2(0x100604, 0x000B),
    _RV32_2(0x100606, 0x3434),      //refresh cycle=0x20 ,TURN_ON_SCRAMBLE=0x8420
    _RV32_2(0x100608, 0x1cbb),      //reg_tRCD
    _RV32_2(0x10060a, 0x2766),      //reg_tRRD
    _RV32_2(0x10060c, 0x96ca),      //reg_tWL
    _RV32_2(0x10060e, 0x4080),      //tRFC
    _RV32_2(0x100610, 0x1c70),      //MR0
    _RV32_2(0x100612, 0x4004),      //MR1
    _RV32_2(0x100614, 0x8018),      //MR2
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
    _RV32_2(0x110dbc, 0x0033),
    _RV32_2(0x110db8, 0x3377),
    _RV32_2(0x110dba, 0x0000),
    _RV32_2(0x110dbc, 0x0077),
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
    _RV32_2(0x110d8e, 0x00a5),      // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
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

#endif  //ENABLE_MSTAR_BD_MST208D_D01A_S

#endif /* _MIU_MST208D_D01A_S_H_ */
