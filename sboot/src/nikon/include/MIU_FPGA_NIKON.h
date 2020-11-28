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

#ifndef _MIU_FPGA_NIKON_H_
#define _MIU_FPGA_NIKON_H_

//MEM_PLL relative
// reg_0x101bFC       :   0:fmpll=216Mhz, 1:fmpll=432Mhz
// reg_0x110d32~110d30:   DDFSET
// reg_0x110d36[15,14]:   DDRPLL_LOOP_DIV_1st
// reg_0x110d36[13,12]:   DDRPLL_input_DIV_1st
// reg_0x110d34[7~0]  :   DDRPLL_LOOP_DIV_2nd
// reg_0x110d34[15,8] :   DDRPLL_input_DIV_2nd
//mclk1x = ( fmpll *524288 * DDRPLL_LOOP_DIV_1st * DDRPLL_LOOP_DIV_2nd ) /
//         (ddfset * DDRPLL_input_DIV_1st *DDRPLL_input_DIV_2nd )

#if (ENABLE_MSTAR_TITANIA_BD_FPGA)
const MS_REG_INIT MIU0_DDR_Init[] =
{
//===MIU0_MEMPLL===================
    _RV32_2( 0x110d3a, 0x0500 ),  // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2( 0x110d36, 0x4003 ),  // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2( 0x110d34, 0x0500 ),  // loop_div/input_div

#if (ENABLE_MEM1066MHz)
    _RV32_2( 0x110d30, 0xd72c ),  // ddfset
    _RV32_2( 0x110d32, 0x0040 ),  // ddrpll_reset/ddrpll_porst/ddrpl_pd
#endif

#if (ENABLE_MEM800MHz)
    _RV32_2( 0x110d30, 0x6666 ),  // ddfset
    _RV32_2( 0x110d32, 0x0056 ),  // ddrpll_reset/ddrpll_porst/ddrpl_pd
#endif

#if (ENABLE_MEM667MHz)
    _RV32_2( 0x110d30, 0xc8a6 ),  // ddfset
    _RV32_2( 0x110d32, 0x0067 ),  // ddrpll_reset/ddrpll_porst/ddrpl_pd
#endif

//===Miu_0 initial=================
#if (MIU0_LEN == 0x4000000)
    _RV32_2( 0x101202, 0x0292 ),  //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+4banks+10col+4x
#elif (MIU0_LEN == 0x8000000)
    _RV32_2( 0x101202, 0x02a2 ),  //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
#else
    #error mmap not correct
#endif

    _RV32_2( 0x101204, 0x008b ),  //if I64Mode =0x8b else =0x0b
    _RV32_2( 0x101206, 0x3420 ),  //refresh cycle=0x20 ,TURN_ON_SCRAMBLE=0x8420
    _RV32_2( 0x101208, 0x1877 ),  //reg_tRCD
    _RV32_2( 0x10120a, 0x1F46 ),  //reg_tRRD
    _RV32_2( 0x10120c, 0x5486 ),  //reg_tWL
    _RV32_2( 0x10120e, 0x2044 ),  //tRFC
    _RV32_2( 0x101210, 0x0E72 ),  //MR0
    _RV32_2( 0x101212, 0x4004 ),  //MR1
    _RV32_2( 0x101214, 0x8000 ),  //MR2
    _RV32_2( 0x101216, 0xC000 ),  //MR3

    //======MIU_ATOP initial======
    _RV32_2( 0x110d00, 0x0011 ),  //miu_0_atop  start
    _RV32_2( 0x110d38, 0x0033 ),  // DQ0/DQ1 phase / dqs0/dqs1 phase
    _RV32_2( 0x110d3a, 0x0000 ),  // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2( 0x110d02, 0x0000 ),
    _RV32_2( 0x110d3c, 0x0200 ),
    _RV32_2( 0x110d3e, 0x0000 ),
    _RV32_2( 0x110d0e, 0x00e7 ),  // 1/2 reg_en_mask
    _RV32_2( 0x110d0e, 0x00a7 ),  // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
    _RV32_2( 0x110d6e, 0x0088 ),  //reg_dll0_ph //
    _RV32_2( 0x110d6a, 0x00c2 ),  //reg_dll1_code	//refine when DDR_CLK change
    _RV32_2( 0x110d68, 0x00c2 ),  //reg_dll0_code	//refine when DDR_CLK change
    _RV32_2( 0x110d72, 0x3803 ),  //

    _RV32_2( 0x110d5c, 0x5553 ),  //pad driver
    _RV32_2( 0x110d5e, 0x5553 ),  //pad driver
    _RV32_2( 0x110d60, 0x2338 ),  //reg_auto calibration

    _END_OF_TBL32_,
    MIU_VER
};
//--------------------------------------------------
//--------------------------------------------------
const MS_REG_INIT MIU1_DDR_Init[] =
{
    _RV32_2( 0x110dba, 0x0500 ),  // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2( 0x110db6, 0x4003 ),  // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2( 0x110db4, 0x0500 ),  // loop_div/input_div

// MIU_1 1066Mhz
#if (ENABLE_MEM1066MHz)
    _RV32_2( 0x110db0, 0xd72c ),  // ddfset
    _RV32_2( 0x110db2, 0x0040 ),  // ddrpll_reset/ddrpll_porst/ddrpl_pd
#endif

// MIU_1 800Mhz
#if (ENABLE_MEM800MHz)
    _RV32_2( 0x110db0, 0x6666 ),  // ddfset
    _RV32_2( 0x110db2, 0x0056 ),  // ddrpll_reset/ddrpll_porst/ddrpl_pd
#endif

//===Miu_1 initial=================
#if (MIU1_LEN == 0x4000000)
    _RV32_2( 0x100602, 0x0292 ),  //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+4banks+10col+4x
#elif (MIU1_LEN == 0x8000000)
    _RV32_2( 0x100602, 0x02a2 ),  //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
#endif

    _RV32_2( 0x100604, 0x008b ),  //if I64Mode =0x8b else =0x0b
    _RV32_2( 0x100606, 0x3420 ),  //refresh cycle=0x20 ,TURN_ON_SCRAMBLE=0x8420
    _RV32_2( 0x100608, 0x1877 ),  //reg_tRCD
    _RV32_2( 0x10060a, 0x1F46 ),  //reg_tRRD
    _RV32_2( 0x10060c, 0x5486 ),  //reg_tWL
    _RV32_2( 0x10060e, 0x2044 ),  //tRFC
    _RV32_2( 0x100610, 0x0E72 ),  //MR0
    _RV32_2( 0x100612, 0x4004 ),  //MR1
    _RV32_2( 0x100614, 0x8000 ),  //MR2
    _RV32_2( 0x100616, 0xC000 ),  //MR3

    //======MIU_ATOP initial======
    _RV32_2( 0x110d80, 0x0011 ), //miu_0_atop  start
    _RV32_2( 0x110db8, 0x0033 ),  // DQ0/DQ1 phase / dqs0/dqs1 phase
    _RV32_2( 0x110dba, 0x0000 ),  // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2( 0x110d82, 0x0000 ),
    _RV32_2( 0x110dbc, 0x0000 ),
    _RV32_2( 0x110dbe, 0x0000 ),
    _RV32_2( 0x110d8e, 0x00e7 ),  // 1/2 reg_en_mask
    _RV32_2( 0x110d8e, 0x00a7 ),  // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
    _RV32_2( 0x110dee, 0x0077 ),  //reg_dll0_ph //
    _RV32_2( 0x110dea, 0x00c2 ),  //reg_dll1_code	//refine when DDR_CLK change
    _RV32_2( 0x110de8, 0x00c2 ),  //reg_dll0_code	//refine when DDR_CLK change

    _RV32_2( 0x110dDC, 0x5553 ),  //pad driver
    _RV32_2( 0x110dDE, 0x5553 ),  //pad driver
    _RV32_2( 0x110dE0, 0x2338 ),  //reg_auto calibration
    _RV32_2( 0x110dF2, 0x3803 ),  //
    _END_OF_TBL32_,
};
#endif  //ENABLE_MSTAR_TITANIA_BD_FPGA

#endif /* _MIU_FPGA_NIKON_H_ */
