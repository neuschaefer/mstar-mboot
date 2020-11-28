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

#ifndef __MIU_BD_MST051B_10ANV_H__
#define __MIU_BD_MST051B_10ANV_H__

#if (ENABLE_MSTAR_NAPOLI_BD_MST051B_10ANV)

const MS_REG_INIT MIU0_DDR_Init[] =
{
#if defined(CONFIG_MIU0_DDR3_1666)
    _RV32_2(0x110d7E, 0x0000),
    _RV32_2(0x110d36, 0x6400),  //reg_DDRPLL_LOOP_DIV_FIRST	: [15:14]	divide by 4
    _RV32_2(0x110d34, 0x2004),  //reg_DDRPLL_LOOP_DIV_SECOND    : [15:14]   divide by 3
    _RV32_2(0x110d30, 0x8F5C),  //set pll to 780 MHz
    _RV32_2(0x110d32, 0x0022),
    _RV32_2(0x110d24, 0x1000),  //Avoid DDRPLL unknown(MCLK05X & MCLK025X) by resset ddrat[28]
    // delay 10ms
    _RV32_2(0x110d24, 0x0000),
    _RV32_2(0x110d22, 0x0004),
    _RV32_1(0x110d11, 0x00),

    _RV32_2(0x101202, 0xF3A7),  //reg_dram_type     10  : [1:0]   00 : sdr, 01 : ddr, 10 : ddr2, 11 : ddr3
    _RV32_2(0x101204, 0x000C),  //reg_rd_timing     9   : [4:0] reg_1cmd_mode
    _RV32_2(0x101206, 0x0430),  //tREFRESH      2b  : [7:0] * 16
    _RV32_2(0x101208, 0x1CBB),  //reg_tRCD      6   : [3:0]     11.25/1.875= 6
    _RV32_2(0x10120A, 0x2766),  //reg_tRRD          4   : [3:0]  10/1.875= 6  reg_tRTP(even) = 6
    _RV32_2(0x10120C, 0x96C8),  //reg_tWL           5   : [3:0]  CAS latency -1
    _RV32_2(0x10120E, 0x40D0),  //tRFC          2a  : [7:0]     127.5/1.875= 68
    _RV32_2(0x101210, 0x1C70),  //MR0               : [15:0]
    _RV32_2(0x101212, 0x4040),  //MR1               : [15:0]    [6],[2] ODT on
    _RV32_2(0x101214, 0x8018),  //MR2               : [15:0]
    _RV32_2(0x101216, 0xC000),  //MR3               : [15:0]

    _RV32_2(0x101228, 0x40B0),  //reg_pack_en
    _RV32_2(0x10122c, 0x0000),  //reg_addr_balance
    _RV32_2(0x10122a, 0x4040),  //reduce 2t latency off

    // === new phy setting ===
    _RV32_2(0x110d1A, 0x0333),
    _RV32_2(0x110d02, 0xAAAA),
    _RV32_2(0x110d04, 0x0080),
    _RV32_2(0x110d3c, 0x0255),
    _RV32_2(0x110d4c, 0x0055),

    _RV32_2(0x110d3e, 0x2022),

    _RV32_2(0x110d50, 0x2211),  //reg_cs0_skew          1       : [2:0]
                                //reg_cs1_skew          1       : [6:4]
                                //reg_cs2_skew          1       : [10:8]
                                //reg_cs3_skew          1       : [14:12]
    _RV32_2(0x110D52, 0x0022),

    _RV32_2(0x110d38, 0x0044),  //reg_clkph_dq0         4       : [3:0]
                                //reg_clkph_dq1         4       : [7:4]
                                //reg_clkph_dqs0        0       : [11:8]
                                //reg_clkph_dqs1        0       : [15:12]

    _RV32_2(0x110d48, 0x0044),  //reg_clkph_dq2         4       : [3:0]
                                //reg_clkph_dq3         4       : [7:4]
                                //reg_clkph_dqs2        0       : [11:8]
                                //reg_clkph_dqs3        0       : [15:12]

    _RV32_2(0x110d3a, 0x1035),  //reg_clkph_cmd         0       : [3:0]
                                //reg_clkph_dqsm        0       : [7:4]
                                //reg_clkph_sp0         0       : [11:8]
                                //reg_clkph_sp1         0       : [15:12]

    _RV32_2(0x110d4a, 0x0033),  //reg_clkph_cmd         0       : [3:0]
                                //reg_clkph_dqsm        0       : [7:4]
                                //reg_clkph_sp0         0       : [11:8]
                                //reg_clkph_sp1         0       : [15:12]

    //set (TX DQ/DQM phase)
    //set region
    _RV32_2(0x110d2e, 0x2200),  //reg_ddrpll2_region_sel_dq_l   2   :[14:12]
                                //reg_ddrpll2_region_sel_dq_h   2   :[10:8]
                                //reg_ddrpll1_ictrl     0    [6:4]
                                //reg_ddrpll2_ictrl     0    [2:0]

    //set reg_sel_mclk1x_skew_dq0~17 (low word)
    _RV32_2(0x110d80, 0xAAAA),
    _RV32_2(0x110d82, 0xAAAA),
    _RV32_2(0x110d84, 0x000A),

    //set reg_sel_mclk1x_skew_dq0~17 (high word)
    _RV32_2(0x110d86, 0xAAAA),
    _RV32_2(0x110d88, 0xAAAA),
    _RV32_2(0x110d8a, 0x000A),
#if 1
    //DLL DQ deskew (low word)
    _RV32_2(0x110da0, 0x1504),  //reg_dll0_3_deskew[3:0],  reg_dll0_2_deskew[3:0], //reg_dll0_1_deskew[3:0],  reg_dll0_0_deskew[3:0]
    _RV32_2(0x110da2, 0x4A5A),  //reg_dll0_7_deskew[3:0],  reg_dll0_6_deskew[3:0], //reg_dll0_5_deskew[3:0],  reg_dll0_4_deskew[3:0]
    _RV32_2(0x110da4, 0x6124),  //reg_dll0_11_deskew[3:0], reg_dll0_10_deskew[3:0],//reg_dll0_9_deskew[3:0],  reg_dll0_8_deskew[3:0]
    _RV32_2(0x110da6, 0x3031),  //reg_dll0_15_deskew[3:0], reg_dll0_14_deskew[3:0],//reg_dll0_13_deskew[3:0], reg_dll0_12_deskew[3:0]

    //DLL DQ deskew (high word)
    _RV32_2(0x110da8, 0x4817),  //reg_dll1_3_deskew[3:0],  reg_dll1_2_deskew[3:0], //reg_dll1_1_deskew[3:0],  reg_dll1_0_deskew[3:0]
    _RV32_2(0x110daa, 0x5668),  //reg_dll1_7_deskew[3:0],  reg_dll1_6_deskew[3:0], //reg_dll1_5_deskew[3:0],  reg_dll1_4_deskew[3:0]
    _RV32_2(0x110dac, 0x6346),  //reg_dll1_11_deskew[3:0], reg_dll1_10_deskew[3:0],//reg_dll1_9_deskew[3:0],  reg_dll1_8_deskew[3:0]
    _RV32_2(0x110dae, 0x3053),  //reg_dll1_15_deskew[3:0], reg_dll1_14_deskew[3:0],//reg_dll1_13_deskew[3:0], reg_dll1_12_deskew[3:0]
#endif
    //RX DQSx Phase select
    _RV32_2(0x110d70, 0x0000),  //[11]    : 'h   0 : dline_gated_control
    _RV32_2(0x110d6c, 0x1818),  //[ 6: 0] : 'h   f : reg_dll0_ph //[14: 8] : 'h   f : reg_dll1_ph
    _RV32_2(0x110d6e, 0x1818),  //[ 6: 0] : 'h   f : reg_dll2_ph //[14: 8] : 'h   f : reg_dll3_ph
    _RV32_2(0x110d70, 0x0800),  //[11]    : 'h   1 : dline_gated_control

    _RV32_2(0x110d0e, 0x00EB),
    _RV32_2(0x110d1e, 0x0007),  //reg_en_mask           1       : [0]
    _RV32_2(0x110d0e, 0x00AB),
    _RV32_2(0x110d1e, 0x0003),  //reg_en_mask           1       : [0]
    _RV32_2(0x110d0e, 0x00EB),
    _RV32_2(0x110d1e, 0x0007),  //reg_en_mask           1       : [0]
    _RV32_2(0x110d0e, 0x00AB),
    _RV32_2(0x110d1e, 0x0003),  //reg_en_mask           1       : [0]
                                //reg_dqsm_dly          1       : [3:1]
                                //reg_ref_wptr_en       0       : [4]
                                //reg_dqsm_sw_rst       1       : [5]
                                //reg_dqsm_rst_sel      0       : [6]
                                //reg_dqsm_sta_rst      1       : [7]

    _RV32_2(0x110d68, 0x2020),  //reg_dll1_code  reg_dll0_code
    _RV32_2(0x110d6a, 0x2020),  //reg_dll3_code  reg_dll2_code

    // === new phy setting ===
    _RV32_2(0x110d18, 0x0000),  //reg_gpio_pad_mode

    _RV32_2(0x110d00, 0x2011),  //reg_pkg_sel      1   : [0]
                                //reg_odt_en       1   : [12:9]

    _RV32_2(0x110d04, 0x0080),  //reg_dqs_pre_state

    _RV32_2(0x110d10, 0x0C00),  //reg_drv_cmd reg_drv_cmd_h

    _RV32_2(0x110d54, 0xC000),  //cmd_mode_sel = 2'h3

    _RV32_2(0x110d5a, 0x5555),
    _RV32_2(0x110d5c, 0x5555),
    _RV32_2(0x110d5e, 0x5555),
    _RV32_2(0x110d74, 0x0606),
    _RV32_2(0x110d76, 0x0606),

    _RV32_2(0x110d8E, 0x0006),

    _RV32_2(0x110d72, 0x0003),  //reg_trg_lvl

    //DLL calibration
    _RV32_2(0x110d62, 0x007F),  // pulse width
    _RV32_2(0x110d64, 0xF000),  // phase, code
    _RV32_2(0x110d60, 0x00C7),
    _RV32_2(0x110d60, 0x00C3),
    _RV32_2(0x110d60, 0x00CB),
    _RV32_2(0x110d60, 0x00C3),
    _RV32_2(0x110d60, 0x00CB),
    _RV32_2(0x110d60, 0x00C2),

    _END_OF_TBL32_,
    MIU_VER
#else

    _RV32_2(0x110d7E, 0x0000),
    _RV32_2(0x110d36, 0x6400),  //reg_DDRPLL_LOOP_DIV_FIRST	: [15:14]	divide by 4
    _RV32_2(0x110d34, 0x2004),  //reg_DDRPLL_LOOP_DIV_SECOND	: [15:14]	divide by 3
    _RV32_2(0x110d30, 0xEC0D),  //set pll to 780 MHz
    _RV32_2(0x110d32, 0x001D),
    _RV32_2(0x110d24, 0x1000),  //Avoid DDRPLL unknown(MCLK05X & MCLK025X) by resset ddrat[28]
    // delay 10ms
    _RV32_2(0x110d24, 0x0000),
    _RV32_2(0x110d22, 0x0004),
    _RV32_1(0x110d11, 0x00),

    _RV32_2(0x101202, 0xF3A7),  //reg_dram_type		10	: [1:0]   00 : sdr, 01 : ddr, 10 : ddr2, 11 : ddr3
    _RV32_2(0x101204, 0x000C),  //reg_rd_timing		9	: [4:0] reg_1cmd_mode
    _RV32_2(0x101206, 0x1538),  //tREFRESH		2b	: [7:0] * 16
    _RV32_2(0x101208, 0x20DD),  //reg_tRCD		6	: [3:0]		11.25/1.875= 6
    _RV32_2(0x10120A, 0x2E86),  //reg_tRRD	       	4 	: [3:0]	 10/1.875= 6  reg_tRTP(even) = 6
    _RV32_2(0x10120C, 0xC80A),  //reg_tWL	 		5	: [3:0]	 CAS latency -1
    _RV32_2(0x10120E, 0xC117),  //tRFC			2a	: [7:0]		127.5/1.875= 68
    _RV32_2(0x101210, 0x1F14),  //MR0				: [15:0]
    _RV32_2(0x101212, 0x4004),  //MR1				: [15:0]	[6],[2] ODT on
    _RV32_2(0x101214, 0x8020),  //MR2				: [15:0]
    _RV32_2(0x101216, 0xC000),  //MR3				: [15:0]

    _RV32_2(0x101228, 0x40D0),  //reg_pack_en
    _RV32_2(0x10122c, 0x0000),  //reg_addr_balance
    _RV32_2(0x10122a, 0x4040),  //reduce 2t latency off

    // === new phy setting ===
    _RV32_2(0x110d1A, 0x0222),
    _RV32_2(0x110d02, 0xAAAA),
    _RV32_2(0x110d04, 0x0080),
    _RV32_2(0x110d3c, 0x1455),
    _RV32_2(0x110d4c, 0x0055),

    _RV32_2(0x110d3e, 0x0044),

    _RV32_2(0x110d50, 0x1111),  //reg_cs0_skew          1       : [2:0]
                                //reg_cs1_skew          1       : [6:4]
                                //reg_cs2_skew          1       : [10:8]
                                //reg_cs3_skew          1       : [14:12]

    _RV32_2(0x110d38, 0x0044),  //reg_clkph_dq0         4       : [3:0]
                                //reg_clkph_dq1         4       : [7:4]
                                //reg_clkph_dqs0        0       : [11:8]
                                //reg_clkph_dqs1        0       : [15:12]

    _RV32_2(0x110d48, 0x0044),  //reg_clkph_dq2         4       : [3:0]
                                //reg_clkph_dq3         4       : [7:4]
                                //reg_clkph_dqs2        0       : [11:8]
                                //reg_clkph_dqs3        0       : [15:12]

    _RV32_2(0x110d3a, 0x6060),  //reg_clkph_cmd         0       : [3:0]
                                //reg_clkph_dqsm        0       : [7:4]
                                //reg_clkph_sp0         0       : [11:8]
                                //reg_clkph_sp1         0       : [15:12]

    _RV32_2(0x110d4a, 0x6060),  //reg_clkph_cmd         0       : [3:0]
                                //reg_clkph_dqsm        0       : [7:4]
                                //reg_clkph_sp0         0       : [11:8]
                                //reg_clkph_sp1         0       : [15:12]

    //set (TX DQ/DQM phase)
    //set region
    _RV32_2(0x110d2e, 0x2200),  //reg_ddrpll2_region_sel_dq_l   2   :[14:12]
                                //reg_ddrpll2_region_sel_dq_h   2   :[10:8]
                                //reg_ddrpll1_ictrl     0    [6:4]
                                //reg_ddrpll2_ictrl     0    [2:0]

    //set reg_sel_mclk1x_skew_dq0~17 (low word)
    _RV32_2(0x110d80, 0xAAAA),
    _RV32_2(0x110d82, 0xAAAA),
    _RV32_2(0x110d84, 0x000A),

    //set reg_sel_mclk1x_skew_dq0~17 (high word)
    _RV32_2(0x110d86, 0xAAAA),
    _RV32_2(0x110d88, 0xAAAA),
    _RV32_2(0x110d8a, 0x000A),
#if 1
    //DLL DQ deskew (low word)
    _RV32_2(0x110da0, 0x3606),  //reg_dll0_3_deskew[3:0],  reg_dll0_2_deskew[3:0], //reg_dll0_1_deskew[3:0],  reg_dll0_0_deskew[3:0]
    _RV32_2(0x110da2, 0x3838),  //reg_dll0_7_deskew[3:0],  reg_dll0_6_deskew[3:0], //reg_dll0_5_deskew[3:0],  reg_dll0_4_deskew[3:0]
    _RV32_2(0x110da4, 0x6014),  //reg_dll0_11_deskew[3:0], reg_dll0_10_deskew[3:0],//reg_dll0_9_deskew[3:0],  reg_dll0_8_deskew[3:0]
    _RV32_2(0x110da6, 0x2142),  //reg_dll0_15_deskew[3:0], reg_dll0_14_deskew[3:0],//reg_dll0_13_deskew[3:0], reg_dll0_12_deskew[3:0]

    //DLL DQ deskew (high word)
    _RV32_2(0x110da8, 0x3808),  //reg_dll1_3_deskew[3:0],  reg_dll1_2_deskew[3:0], //reg_dll1_1_deskew[3:0],  reg_dll1_0_deskew[3:0]
    _RV32_2(0x110daa, 0x7678),  //reg_dll1_7_deskew[3:0],  reg_dll1_6_deskew[3:0], //reg_dll1_5_deskew[3:0],  reg_dll1_4_deskew[3:0]
    _RV32_2(0x110dac, 0x6236),  //reg_dll1_11_deskew[3:0], reg_dll1_10_deskew[3:0],//reg_dll1_9_deskew[3:0],  reg_dll1_8_deskew[3:0]
    _RV32_2(0x110dae, 0x3034),  //reg_dll1_15_deskew[3:0], reg_dll1_14_deskew[3:0],//reg_dll1_13_deskew[3:0], reg_dll1_12_deskew[3:0]
#endif
    //RX DQSx Phase select
    _RV32_2(0x110d70, 0x0000),  //[11]    : 'h   0 : dline_gated_control
    _RV32_2(0x110d6c, 0x1919),  //[ 6: 0] : 'h   f : reg_dll0_ph //[14: 8] : 'h   f : reg_dll1_ph
    _RV32_2(0x110d6e, 0x1717),  //[ 6: 0] : 'h   f : reg_dll2_ph //[14: 8] : 'h   f : reg_dll3_ph
    _RV32_2(0x110d70, 0x0800),  //[11]    : 'h   1 : dline_gated_control

    _RV32_2(0x110d0e, 0x00ED),
    _RV32_2(0x110d1e, 0x0007),  //reg_en_mask           1       : [0]
    _RV32_2(0x110d0e, 0x00AD),
    _RV32_2(0x110d1e, 0x0003),  //reg_en_mask           1       : [0]
    _RV32_2(0x110d0e, 0x00ED),
    _RV32_2(0x110d1e, 0x0007),  //reg_en_mask           1       : [0]
    _RV32_2(0x110d0e, 0x00AD),
    _RV32_2(0x110d1e, 0x0003),  //reg_en_mask           1       : [0]
                                //reg_dqsm_dly          1       : [3:1]
                                //reg_ref_wptr_en       0       : [4]
                                //reg_dqsm_sw_rst       1       : [5]
                                //reg_dqsm_rst_sel      0       : [6]
                                //reg_dqsm_sta_rst      1       : [7]

    _RV32_2(0x110d68, 0x2020),  //reg_dll1_code  reg_dll0_code
    _RV32_2(0x110d6a, 0x2020),  //reg_dll3_code  reg_dll2_code

    // === new phy setting ===
    _RV32_2(0x110d18, 0x0000),  //reg_gpio_pad_mode

    _RV32_2(0x110d00, 0x2011),  //reg_pkg_sel      1   : [0]
                                //reg_odt_en       1   : [12:9]

    _RV32_2(0x110d04, 0x0080),  //reg_dqs_pre_state

    _RV32_2(0x110d10, 0x0C00),  //reg_drv_cmd reg_drv_cmd_h

    _RV32_2(0x110d54, 0xC000),  //cmd_mode_sel = 2'h3

    _RV32_2(0x110d5a, 0x5555),
    _RV32_2(0x110d5c, 0x5555),
    _RV32_2(0x110d5e, 0x5555),
    _RV32_2(0x110d74, 0x0606),
    _RV32_2(0x110d76, 0x0606),

    _RV32_2(0x110d72, 0x0003),  //reg_trg_lvl

    //DLL calibration
    _RV32_2(0x110d62, 0x007F),  // pulse width
    _RV32_2(0x110d64, 0xF000),  // phase, code
    _RV32_2(0x110d60, 0x00C7),
    _RV32_2(0x110d60, 0x00C3),
    _RV32_2(0x110d60, 0x00CB),
    _RV32_2(0x110d60, 0x00C3),
    _RV32_2(0x110d60, 0x00CB),
    _RV32_2(0x110d60, 0x00C2),

    _END_OF_TBL32_,
    MIU_VER
#endif
};

const MS_REG_INIT MIU1_DDR_Init[] =
{
#if defined(CONFIG_MIU1_DDR3_1666)
    _RV32_2(0x16167E, 0x0000),
    _RV32_2(0x161636, 0x6400),  //reg_DDRPLL_LOOP_DIV_FIRST : [15:14]   divide by 4
    _RV32_2(0x161634, 0x2004),  //reg_DDRPLL_LOOP_DIV_SECOND    : [15:14]   divide by 3
    _RV32_2(0x161630, 0x8F5C),  //set pll to 780 MHz
    _RV32_2(0x161632, 0x0022),
    _RV32_2(0x161624, 0x1000),  //Avoid DDRPLL unknown(MCLK05X & MCLK025X) by resset ddrat[28]
    // delay 10ms
    _RV32_2(0x161624, 0x0000),
    _RV32_2(0x161622, 0x0004),
    _RV32_1(0x161611, 0x00),

    _RV32_2(0x100602, 0xF3A7),  //reg_dram_type     10  : [1:0]   00 : sdr, 01 : ddr, 10 : ddr2, 11 : ddr3
    _RV32_2(0x100604, 0x000C),  //reg_rd_timing     9   : [4:0] reg_1cmd_mode
    _RV32_2(0x100606, 0x0430),  //tREFRESH      2b  : [7:0] * 16
    _RV32_2(0x100608, 0x1CBB),  //reg_tRCD      6   : [3:0]     11.25/1.875= 6
    _RV32_2(0x10060A, 0x2766),  //reg_tRRD          4   : [3:0]  10/1.875= 6  reg_tRTP(even) = 6
    _RV32_2(0x10060C, 0x96C8),  //reg_tWL           5   : [3:0]  CAS latency -1
    _RV32_2(0x10060E, 0x40D0),  //tRFC          2a  : [7:0]     127.5/1.875= 68
    _RV32_2(0x100610, 0x1C70),  //MR0               : [15:0]
    _RV32_2(0x100612, 0x4040),  //MR1               : [15:0]    [6],[2] ODT on
    _RV32_2(0x100614, 0x8018),  //MR2               : [15:0]
    _RV32_2(0x100616, 0xC000),  //MR3               : [15:0]

    _RV32_2(0x100628, 0x40B0),  //reg_pack_en
    _RV32_2(0x10062c, 0x0000),  //reg_addr_balance
    _RV32_2(0x10062a, 0x4040),  //reduce 2t latency off

    // === new phy setting ===
    _RV32_2(0x16161A, 0x0333),
    _RV32_2(0x161602, 0xAAAA),
    _RV32_2(0x161604, 0x0080),
    _RV32_2(0x16163c, 0x0366),
    _RV32_2(0x16164c, 0x0066),

    _RV32_2(0x16163e, 0x3033),

    _RV32_2(0x161650, 0x3322),  //reg_cs0_skew          1       : [2:0]
            //reg_cs1_skew          1       : [6:4]
            //reg_cs2_skew          1       : [10:8]
            //reg_cs3_skew          1       : [14:12]

    _RV32_2(0x161652, 0x0044),

    _RV32_2(0x161638, 0x0044),  //reg_clkph_dq0         4       : [3:0]
            //reg_clkph_dq1         4       : [7:4]
            //reg_clkph_dqs0        0       : [11:8]
            //reg_clkph_dqs1        0       : [15:12]

    _RV32_2(0x161648, 0x0044),  //reg_clkph_dq2         4       : [3:0]
            //reg_clkph_dq3         4       : [7:4]
            //reg_clkph_dqs2        0       : [11:8]
            //reg_clkph_dqs3        0       : [15:12]

    _RV32_2(0x16163a, 0x405A),  //reg_clkph_cmd         0       : [3:0]
            //reg_clkph_dqsm        0       : [7:4]
            //reg_clkph_sp0         0       : [11:8]
            //reg_clkph_sp1         0       : [15:12]

    _RV32_2(0x16164a, 0x305A),  //reg_clkph_cmd         0       : [3:0]
            //reg_clkph_dqsm        0       : [7:4]
            //reg_clkph_sp0         0       : [11:8]
            //reg_clkph_sp1         0       : [15:12]

    //set (TX DQ/DQM phase)
    //set region
    _RV32_2(0x16162e, 0x2200),  //reg_ddrpll2_region_sel_dq_l   2   :[14:12]
            //reg_ddrpll2_region_sel_dq_h   2   :[10:8]
            //reg_ddrpll1_ictrl     0    [6:4]
            //reg_ddrpll2_ictrl     0    [2:0]

    //set reg_sel_mclk1x_skew_dq0~17 (low word)
    _RV32_2(0x161680, 0xAAAA),
    _RV32_2(0x161682, 0xAAAA),
    _RV32_2(0x161684, 0x000A),

    //set reg_sel_mclk1x_skew_dq0~17 (high word)
    _RV32_2(0x161686, 0xAAAA),
    _RV32_2(0x161688, 0xAAAA),
    _RV32_2(0x16168a, 0x000A),

#if 1
    //DLL DQ deskew (low word)
    _RV32_2(0x1616a0, 0x3904),  //reg_dll0_3_deskew[3:0],  reg_dll0_2_deskew[3:0], //reg_dll0_1_deskew[3:0],  reg_dll0_0_deskew[3:0]
    _RV32_2(0x1616a2, 0x654A),  //reg_dll0_7_deskew[3:0],  reg_dll0_6_deskew[3:0], //reg_dll0_5_deskew[3:0],  reg_dll0_4_deskew[3:0]
    _RV32_2(0x1616a4, 0x9679),  //reg_dll0_11_deskew[3:0], reg_dll0_10_deskew[3:0],//reg_dll0_9_deskew[3:0],  reg_dll0_8_deskew[3:0]
    _RV32_2(0x1616a6, 0x8375),  //reg_dll0_15_deskew[3:0], reg_dll0_14_deskew[3:0],//reg_dll0_13_deskew[3:0], reg_dll0_12_deskew[3:0]

    //DLL DQ deskew (high word)
    _RV32_2(0x1616a8, 0x4704),  //reg_dll1_3_deskew[3:0],  reg_dll1_2_deskew[3:0], //reg_dll1_1_deskew[3:0],  reg_dll1_0_deskew[3:0]
    _RV32_2(0x1616aa, 0x5335),  //reg_dll1_7_deskew[3:0],  reg_dll1_6_deskew[3:0], //reg_dll1_5_deskew[3:0],  reg_dll1_4_deskew[3:0]
    _RV32_2(0x1616ac, 0x8668),  //reg_dll1_11_deskew[3:0], reg_dll1_10_deskew[3:0],//reg_dll1_9_deskew[3:0],  reg_dll1_8_deskew[3:0]
    _RV32_2(0x1616ae, 0x7466),  //reg_dll1_15_deskew[3:0], reg_dll1_14_deskew[3:0],//reg_dll1_13_deskew[3:0], reg_dll1_12_deskew[3:0]
#endif

    //RX DQSx Phase select
    _RV32_2(0x161670, 0x0000),  //[11]    : 'h   0 : dline_gated_control
    _RV32_2(0x16166c, 0x1717),  //[ 6: 0] : 'h   f : reg_dll0_ph //[14: 8] : 'h   f : reg_dll1_ph
    _RV32_2(0x16166e, 0x1A1A),  //[ 6: 0] : 'h   f : reg_dll2_ph //[14: 8] : 'h   f : reg_dll3_ph
    _RV32_2(0x161670, 0x0800),  //[11]    : 'h   1 : dline_gated_control

    _RV32_2(0x16160e, 0x00EB),
    _RV32_2(0x16161e, 0x0007),  //reg_en_mask           1       : [0]
    _RV32_2(0x16160e, 0x00AB),
    _RV32_2(0x16161e, 0x0003),  //reg_en_mask           1       : [0]
    _RV32_2(0x16160e, 0x00EB),
    _RV32_2(0x16161e, 0x0007),  //reg_en_mask           1       : [0]
    _RV32_2(0x16160e, 0x00AB),
    _RV32_2(0x16161e, 0x0003),  //reg_en_mask           1       : [0]
            //reg_dqsm_dly          1       : [3:1]
            //reg_ref_wptr_en       0       : [4]
            //reg_dqsm_sw_rst       1       : [5]
            //reg_dqsm_rst_sel      0       : [6]
            //reg_dqsm_sta_rst      1       : [7]

    _RV32_2(0x161668, 0x2020),  //reg_dll1_code  reg_dll0_code
    _RV32_2(0x16166a, 0x2020),  //reg_dll3_code  reg_dll2_code

    // === new phy setting ===
    _RV32_2(0x161618, 0x0000),  //reg_gpio_pad_mode

    _RV32_2(0x161600, 0x2011),  //reg_pkg_sel      1   : [0]
            //reg_odt_en       1   : [12:9]

    _RV32_2(0x161604, 0x0080),  //reg_dqs_pre_state

    _RV32_2(0x161610, 0x0C00),  //reg_drv_cmd reg_drv_cmd_h

    _RV32_2(0x161654, 0xC000),  //cmd_mode_sel = 2'h3

    _RV32_2(0x16165a, 0x5555),
    _RV32_2(0x16165c, 0x5555),
    _RV32_2(0x16165e, 0x5555),
    _RV32_2(0x161674, 0x0606),
    _RV32_2(0x161676, 0x0606),

    _RV32_2(0x16168E, 0x0006),

    _RV32_2(0x161672, 0x0003),  //reg_trg_lvl

    //DLL calibration
    _RV32_2(0x161662, 0x007F),  // pulse width
    _RV32_2(0x161664, 0xF000),  // phase, code
    _RV32_2(0x161660, 0x00C7),
    _RV32_2(0x161660, 0x00C3),
    _RV32_2(0x161660, 0x00CB),
    _RV32_2(0x161660, 0x00C3),
    _RV32_2(0x161660, 0x00CB),
    _RV32_2(0x161660, 0x00C2),

    _END_OF_TBL32_,

#else

    _RV32_2(0x16167E, 0x0000),
    _RV32_2(0x161636, 0x6400),  //reg_DDRPLL_LOOP_DIV_FIRST : [15:14]   divide by 4
    _RV32_2(0x161634, 0x2004),  //reg_DDRPLL_LOOP_DIV_SECOND    : [15:14]   divide by 3
    _RV32_2(0x161630, 0xEC0D),  //set pll to 780 MHz
    _RV32_2(0x161632, 0x001D),
    _RV32_2(0x161624, 0x1000),  //Avoid DDRPLL unknown(MCLK05X & MCLK025X) by resset ddrat[28]
    // delay 10ms
    _RV32_2(0x161624, 0x0000),
    _RV32_2(0x161622, 0x0004),
    _RV32_1(0x161611, 0x00),

    _RV32_2(0x100602, 0xF3A7),  //reg_dram_type		10	: [1:0]   00 : sdr, 01 : ddr, 10 : ddr2, 11 : ddr3
    _RV32_2(0x100604, 0x000C),  //reg_rd_timing		9	: [4:0] reg_1cmd_mode
    _RV32_2(0x100606, 0x1538),  //tREFRESH		2b	: [7:0] * 16
    _RV32_2(0x100608, 0x20DD),  //reg_tRCD		6	: [3:0]		11.25/1.875= 6
    _RV32_2(0x10060A, 0x2E86),  //reg_tRRD	       	4 	: [3:0]	 10/1.875= 6  reg_tRTP(even) = 6
    _RV32_2(0x10060C, 0xC80A),  //reg_tWL	 		5	: [3:0]	 CAS latency -1
    _RV32_2(0x10060E, 0xC117),  //tRFC			2a	: [7:0]		127.5/1.875= 68
    _RV32_2(0x100610, 0x1F14),  //MR0				: [15:0]
    _RV32_2(0x100612, 0x4004),  //MR1				: [15:0]	[6],[2] ODT on
    _RV32_2(0x100614, 0x8020),  //MR2				: [15:0]
    _RV32_2(0x100616, 0xC000),  //MR3				: [15:0]

    _RV32_2(0x100628, 0x40D0),  //reg_pack_en
    _RV32_2(0x10062c, 0x0000),  //reg_addr_balance
    _RV32_2(0x10062a, 0x4040),  //reduce 2t latency off

    // === new phy setting ===
    _RV32_2(0x16161A, 0x0222),
    _RV32_2(0x161602, 0xAAAA),
    _RV32_2(0x161604, 0x0080),
    _RV32_2(0x16163c, 0x1455),
    _RV32_2(0x16164c, 0x0055),

    _RV32_2(0x16163e, 0x0044),

    _RV32_2(0x161650, 0x1111),  //reg_cs0_skew          1       : [2:0]
                                //reg_cs1_skew          1       : [6:4]
                                //reg_cs2_skew          1       : [10:8]
                                //reg_cs3_skew          1       : [14:12]

    _RV32_2(0x161652, 0x0044),

    _RV32_2(0x161638, 0x0044),  //reg_clkph_dq0         4       : [3:0]
                                //reg_clkph_dq1         4       : [7:4]
                                //reg_clkph_dqs0        0       : [11:8]
                                //reg_clkph_dqs1        0       : [15:12]

    _RV32_2(0x161648, 0x0044),  //reg_clkph_dq2         4       : [3:0]
                                //reg_clkph_dq3         4       : [7:4]
                                //reg_clkph_dqs2        0       : [11:8]
                                //reg_clkph_dqs3        0       : [15:12]

    _RV32_2(0x16163a, 0x6063),  //reg_clkph_cmd         0       : [3:0]
                                //reg_clkph_dqsm        0       : [7:4]
                                //reg_clkph_sp0         0       : [11:8]
                                //reg_clkph_sp1         0       : [15:12]

    _RV32_2(0x16164a, 0x6063),  //reg_clkph_cmd         0       : [3:0]
                                //reg_clkph_dqsm        0       : [7:4]
                                //reg_clkph_sp0         0       : [11:8]
                                //reg_clkph_sp1         0       : [15:12]

    //set (TX DQ/DQM phase)
    //set region
    _RV32_2(0x16162e, 0x1100),  //reg_ddrpll2_region_sel_dq_l   2   :[14:12]
                                //reg_ddrpll2_region_sel_dq_h   2   :[10:8]
                                //reg_ddrpll1_ictrl     0    [6:4]
                                //reg_ddrpll2_ictrl     0    [2:0]

    //set reg_sel_mclk1x_skew_dq0~17 (low word)
    _RV32_2(0x161680, 0xFFFF),
    _RV32_2(0x161682, 0xFFFF),
    _RV32_2(0x161684, 0x000F),

    //set reg_sel_mclk1x_skew_dq0~17 (high word)
    _RV32_2(0x161686, 0xFFFF),
    _RV32_2(0x161688, 0xFFFF),
    _RV32_2(0x16168a, 0x000F),

#if 1
    //DLL DQ deskew (low word)
    _RV32_2(0x1616a0, 0x3703),  //reg_dll0_3_deskew[3:0],  reg_dll0_2_deskew[3:0], //reg_dll0_1_deskew[3:0],  reg_dll0_0_deskew[3:0]
    _RV32_2(0x1616a2, 0x4537),  //reg_dll0_7_deskew[3:0],  reg_dll0_6_deskew[3:0], //reg_dll0_5_deskew[3:0],  reg_dll0_4_deskew[3:0]
    _RV32_2(0x1616a4, 0x8335),  //reg_dll0_11_deskew[3:0], reg_dll0_10_deskew[3:0],//reg_dll0_9_deskew[3:0],  reg_dll0_8_deskew[3:0]
    _RV32_2(0x1616a6, 0x3032),  //reg_dll0_15_deskew[3:0], reg_dll0_14_deskew[3:0],//reg_dll0_13_deskew[3:0], reg_dll0_12_deskew[3:0]

    //DLL DQ deskew (high word)
    _RV32_2(0x1616a8, 0x4805),  //reg_dll1_3_deskew[3:0],  reg_dll1_2_deskew[3:0], //reg_dll1_1_deskew[3:0],  reg_dll1_0_deskew[3:0]
    _RV32_2(0x1616aa, 0x5456),  //reg_dll1_7_deskew[3:0],  reg_dll1_6_deskew[3:0], //reg_dll1_5_deskew[3:0],  reg_dll1_4_deskew[3:0]
    _RV32_2(0x1616ac, 0x8448),  //reg_dll1_11_deskew[3:0], reg_dll1_10_deskew[3:0],//reg_dll1_9_deskew[3:0],  reg_dll1_8_deskew[3:0]
    _RV32_2(0x1616ae, 0x6053),  //reg_dll1_15_deskew[3:0], reg_dll1_14_deskew[3:0],//reg_dll1_13_deskew[3:0], reg_dll1_12_deskew[3:0]
#endif

    //RX DQSx Phase select
    _RV32_2(0x161670, 0x0000),  //[11]    : 'h   0 : dline_gated_control
    _RV32_2(0x16166c, 0x1919),  //[ 6: 0] : 'h   f : reg_dll0_ph //[14: 8] : 'h   f : reg_dll1_ph
    _RV32_2(0x16166e, 0x1717),  //[ 6: 0] : 'h   f : reg_dll2_ph //[14: 8] : 'h   f : reg_dll3_ph
    _RV32_2(0x161670, 0x0800),  //[11]    : 'h   1 : dline_gated_control

    _RV32_2(0x16160e, 0x00ED),
    _RV32_2(0x16161e, 0x0007),  //reg_en_mask           1       : [0]
    _RV32_2(0x16160e, 0x00AD),
    _RV32_2(0x16161e, 0x0003),  //reg_en_mask           1       : [0]
    _RV32_2(0x16160e, 0x00ED),
    _RV32_2(0x16161e, 0x0007),  //reg_en_mask           1       : [0]
    _RV32_2(0x16160e, 0x00AD),
    _RV32_2(0x16161e, 0x0003),  //reg_en_mask           1       : [0]
                                //reg_dqsm_dly          1       : [3:1]
                                //reg_ref_wptr_en       0       : [4]
                                //reg_dqsm_sw_rst       1       : [5]
                                //reg_dqsm_rst_sel      0       : [6]
                                //reg_dqsm_sta_rst      1       : [7]

    _RV32_2(0x161668, 0x2020),  //reg_dll1_code  reg_dll0_code
    _RV32_2(0x16166a, 0x2020),  //reg_dll3_code  reg_dll2_code

    // === new phy setting ===
    _RV32_2(0x161618, 0x0000),  //reg_gpio_pad_mode

    _RV32_2(0x161600, 0x2011),  //reg_pkg_sel      1   : [0]
                                //reg_odt_en       1   : [12:9]

    _RV32_2(0x161604, 0x0080),  //reg_dqs_pre_state

    _RV32_2(0x161610, 0x0C00),  //reg_drv_cmd reg_drv_cmd_h

    _RV32_2(0x161654, 0xC000),  //cmd_mode_sel = 2'h3

    _RV32_2(0x16165a, 0x5555),
    _RV32_2(0x16165c, 0x5555),
    _RV32_2(0x16165e, 0x5555),
    _RV32_2(0x161674, 0x0606),
    _RV32_2(0x161676, 0x0606),

    _RV32_2(0x161672, 0x0003),  //reg_trg_lvl

    //DLL calibration
    _RV32_2(0x161662, 0x007F),  // pulse width
    _RV32_2(0x161664, 0xF000),  // phase, code
    _RV32_2(0x161660, 0x00C7),
    _RV32_2(0x161660, 0x00C3),
    _RV32_2(0x161660, 0x00CB),
    _RV32_2(0x161660, 0x00C3),
    _RV32_2(0x161660, 0x00CB),
    _RV32_2(0x161660, 0x00C2),

    _END_OF_TBL32_,
#endif
};

#endif /* ENABLE_MSTAR_BD_MST051B_10ANV */
#endif /* __MIU_INIT_BD_MST051B_10ANV_H__*/
