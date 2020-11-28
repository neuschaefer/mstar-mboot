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

#ifndef __DDR2_INIT_H__
#define __DDR2_INIT_H__

#include "c_riubase.h"
#include "drvGlobal.h"

#define    _DRAM_SIZE_NO_LIMIT    0x00
#define    _DRAM_SIZE_2M          0x01
#define    _DRAM_SIZE_4M          0x02
#define    _DRAM_SIZE_8M          0x03
#define    _DRAM_SIZE_16M         0x04
#define    _DRAM_SIZE_32M         0x05
#define    _DRAM_SIZE_64M         0x06
#define    _DRAM_SIZE_128M        0x07
#define    _DRAM_SIZE_256M        0x07

#define    _DRAM_ON_BAORD         _DRAM_SIZE_NO_LIMIT

// A CMD + B DATA
#define MIU0_USE_MIU1_DATA (!CHIP_HAS_DDR_A_DATA && !CHIP_HAS_DDR_B_CMD)

#define DDR2_800MHz     0x00 //mcp
#define DDR2_1066MHz    0x01 //mcp
#define DDR3_1300MHz    0x02 //mcp
#define DDR2_800MHz_e   0x11 //external
#define DDR2_1066MHz_e  0x12 //external
#define DDR3_1300MHz_e  0x13 //external
#define DDR3_1600MHz_e  0x14 //external

//#define DDR2_900MHz
//#define DDR2_960MHz

#if ( (ENABLE_MSTAR_EULER_BD_MST165A_D01B_S) \
   || (ENABLE_MSTAR_EULER_BD_MST165B_D01B_S) \
   || (ENABLE_MSTAR_EULER_BD_MST042B_EULER) \
   || (ENABLE_MSTAR_EULER_BD_MST047B_EULER) \
   || (ENABLE_MSTAR_EULER_BD_MST165C_D01B_S) \
   )
    #if ENABLE_MEM800MHz
        #define MIU_SPEED       DDR2_800MHz
    #elif ENABLE_MEM1066MHz
        #define MIU_SPEED       DDR2_1066MHz
    #elif ENABLE_MEM1300MHz
        #define MIU_SPEED       DDR3_1300MHz
    #else
        #error "Please select correct DDR2 Speed"
    #endif

#else
    #error "MIU interface isn't defined"
#endif

static const MS_REG_INIT MIU_ATOP_Init[]=
{
    //set test mode of DDRPLL
    _RV32_2(0x110d24, 0x0000),
    //Clock setting
    _RV32_2(0x110d36, 0x0000),
    _RV32_2(0x110d34, 0x0200),
    //Set the clock frequency for dram & PLL reset
  #if (MIU_SPEED == DDR2_800MHz)//MCLK 400MHz setting
    _RV32_2(0x110d30, 0xdcf9),
    _RV32_2(0x110d32, 0x0045),
  #elif (MIU_SPEED == DDR2_1066MHz)//MCLK 533MHz setting
    #ifdef DDR2_900MHz //MCLK 450MHz setting
    _RV32_2(0x110d30, 0x70a3),
    _RV32_2(0x110d32, 0x003d),
    #elif defined (DDR2_960MHz)//MCLK 480MHz setting
    _RV32_2(0x110d30, 0x9999),
    _RV32_2(0x110d32, 0x0039),
    #else//MCLK 533MHz setting
    _RV32_2(0x110d30, 0x6e1f),
    _RV32_2(0x110d32, 0x0034),
    #endif
  #elif (MIU_SPEED == DDR3_1300MHz)//MCLK 650MHz setting
    _RV32_2(0x110d30, 0x7b80),
    _RV32_2(0x110d32, 0x0029),
  #else
    #error "MIU interface isn't defined"
  #endif

    _END_OF_TBL32_
};

static const MS_REG_INIT MIU_DDR_Init[] =
{
  #if (MIU_SPEED == DDR2_800MHz)
    _RV32_2( 0x101202, 0x0292 ),
    _RV32_2( 0x101204, 0x008b ), //rd_timing
    _RV32_2( 0x101206, 0x0330 ),
    _RV32_2( 0x101208, 0x1466 ),
    _RV32_2( 0x10120a, 0x1644 ),
    _RV32_2( 0x10120c, 0x7465 ),
    _RV32_2( 0x10120e, 0x204f ),
    _RV32_2( 0x101210, 0x0a62 ),
    _RV32_2( 0x101212, 0x4004 ),
    _RV32_2( 0x101214, 0x8000 ),
    _RV32_2( 0x101216, 0xc000 ),
  #elif (MIU_SPEED == DDR2_1066MHz)
    _RV32_2( 0x101202, 0x0292 ),
    _RV32_2( 0x101204, 0x008b ), //rd_timing
    _RV32_2( 0x101206, 0x0420 ),
    _RV32_2( 0x101208, 0x1677 ),
    _RV32_2( 0x10120a, 0x1e46 ),
    _RV32_2( 0x10120c, 0x7486 ),
    _RV32_2( 0x10120e, 0x206a ),
    _RV32_2( 0x101210, 0x0e72 ),
    _RV32_2( 0x101212, 0x4004 ), //0x4042//150 ohm for DRAM ODT ON (0x101200[4] = 1)
    _RV32_2( 0x101214, 0x8000 ),
    _RV32_2( 0x101216, 0xc000 ),
  #elif (MIU_SPEED == DDR3_1300MHz)
    _RV32_2( 0x101202, 0x03a3 ),
    _RV32_2( 0x101204, 0x0049 ), //rd_timing
    _RV32_2( 0x101206, 0x1420 ),
    _RV32_2( 0x101208, 0x1899 ),
    _RV32_2( 0x10120a, 0x2155 ),
    _RV32_2( 0x10120c, 0x95a8 ),
    _RV32_2( 0x10120e, 0x404a ),
    _RV32_2( 0x101210, 0x1a50 ),
    _RV32_2( 0x101212, 0x4004 ),
    _RV32_2( 0x101214, 0x8010 ),
    _RV32_2( 0x101216, 0xc000 ),
  #else
    #error "MIU interface isn't defined"
  #endif

  #if (MIU_SPEED == DDR2_800MHz)
    _RV32_2( 0x110d54, 0x0000 ),
    _RV32_2( 0x110d00, 0x0019 ),
    //_RV32_2( 0x110d36, 0x0002 ),//reg_clkph_cko
    _RV32_2( 0x110d38, 0x0033 ),//reg_clkph_dq0             5       : [3:0]
                                //reg_clkph_dq1         5       : [7:4]
                                //reg_clkph_dqs0        0       : [11:8]
                                //reg_clkph_dqs1        0       : [15:12]
    _RV32_2( 0x110d3a, 0x0000 ),//reg_clkph_cmd             0       : [3:0]
                                //reg_clkph_dqsm0        4       : [7:4]
                                //reg_clkph_clk_a          4       : [11:8]
                                //reg_clkph_dqsm1          0       : [15:12]
    _RV32_2( 0x110d02, 0x0000 ),
    //_RV32_2( 0x10122c, 0x9300 ),
    _RV32_2( 0x110d04, 0x0000 ),//reg_dqs_pre_state : [7:0]
    _RV32_2( 0x110d3c, 0x0200 ),//reg_dqsm0_skew 0 [2:0]
                                //reg_dqsm1_skew 0 [6:4]
                                //reg_dqs_skew   2 [10:8]
                                //reg_cmd1_skew  0 [14:12]
    _RV32_2( 0x110d3e, 0x0022 ),//[2:0]   reg_oen_skew
                                //[6:4]   reg_dq_skew
                                //[10:8]  reg_cmd_skew
                                //[14:12] reg_cko_skew

    _RV32_2( 0x110d0e, 0x00e7 ),//[3:1] reg_dqsm_dly
    _RV32_2( 0x110d0e, 0x00a7 ),
    _RV32_2( 0x110d6e, 0x0077 ),//reg_dll0_ph : [3:0]
                                //reg_dll1_ph : [7:4]
    _RV32_2( 0x110d6a, 0x00c2 ),
    _RV32_2( 0x110d68, 0x00c2 ),
    _RV32_2( 0x110d54, 0x0000 ),
  #elif (MIU_SPEED == DDR2_1066MHz)
    _RV32_2( 0x110d54, 0x0000 ),
    _RV32_2( 0x110d00, 0x0019 ),
    _RV32_2( 0x110d38, 0x0033 ),//reg_clkph_dq0             3       : [3:0]
                                //reg_clkph_dq1         3       : [7:4]
                                //reg_clkph_dqs0        0       : [11:8]
                                //reg_clkph_dqs1        0       : [15:12]
    _RV32_2( 0x110d3a, 0x0000 ),//reg_clkph_cmd             0       : [3:0]
                                //reg_clkph_dqsm0        0       : [7:4]
                                //reg_clkph_clk_a          0       : [11:8]
                                //reg_clkph_dqsm1          0       : [15:12]
    _RV32_2( 0x110d02, 0x0000 ),
    _RV32_2( 0x110d04, 0x0000 ),//reg_dqs_pre_state : [7:0]
    _RV32_2( 0x110d3c, 0x0022 ),//reg_dqsm0_skew 0 [2:0]
                                //reg_dqsm1_skew 0 [6:4]
                                //reg_dqs_skew   2 [10:8]
                                //reg_cmd1_skew  0 [14:12]
    _RV32_2( 0x110d3e, 0x0000 ),//[2:0]   reg_oen_skew
                                //[6:4]   reg_dq_skew
                                //[10:8]  reg_cmd_skew
                                //[14:12] reg_cko_skew

    _RV32_2( 0x110d0e, 0x00e7 ),//[3:1] reg_dqsm_dly
    _RV32_2( 0x110d0e, 0x00a7 ),
    _RV32_2( 0x110d6e, 0x0077 ),//reg_dll0_ph : [3:0]
                                //reg_dll1_ph : [7:4]
    _RV32_2( 0x110d6a, 0x00c2 ),
    _RV32_2( 0x110d68, 0x00c2 ),
    _RV32_2( 0x110d54, 0x0000 ),
  #elif (MIU_SPEED == DDR3_1300MHz)
    _RV32_2( 0x110d54, 0x0000 ),
    _RV32_2( 0x110d7e, 0x00f8 ),
    _RV32_2( 0x110d00, 0x0018 ),
    _RV32_2( 0x110d04, 0x0080 ),//reg_dqs_pre_state : [7:0]
    _RV32_2( 0x110d38, 0x0044 ),//reg_clkph_dq0             4       : [3:0]
                                //reg_clkph_dq1         4       : [7:4]
                                //reg_clkph_dqs0        0       : [11:8]
                                //reg_clkph_dqs1        0       : [15:12]
    _RV32_2( 0x110d3a, 0x0002 ),//reg_clkph_cmd             2       : [3:0]
                                //reg_clkph_dqsm        0       : [7:4]
                                //reg_clkph_sp0          0       : [11:8]
                                //reg_clkph_sp1          0       : [15:12]
    _RV32_2( 0x110d4a, 0x0002 ),
    _RV32_2( 0x110d02, 0x0000 ),
    _RV32_2( 0x110d3c, 0x3166 ),//reg_dqsm0_skew 0 [2:0]
                                //[10:8]  reg_dqsm_skew
                                //[14:12] reg_dqs_skew
    _RV32_2( 0x110d3e, 0x1211 ),//[2:0]   reg_oen_skew
                                //[6:4]   reg_dq_skew
                                //[10:8]  reg_cmd_skew
                                //[14:12] reg_cko_skew
    _RV32_2( 0x110d50, 0x3333 ),//[3:1] reg_dqsm_dly

    _RV32_2( 0x110d0e, 0x00e5 ),//[3:1] reg_dqsm_dly
    _RV32_2( 0x110d0e, 0x00a5 ),
    _RV32_2( 0x110d6e, 0x0088 ),//reg_dll0_ph : [3:0]
                                //reg_dll1_ph : [7:4]
    _RV32_2( 0x110d6a, 0x0124 ),
    _RV32_2( 0x110d68, 0x0124 ),
    _RV32_2( 0x110d54, 0x0000 ),
  #else
    #error "MIU interface isn't defined"
  #endif

    _END_OF_TBL32_,
};

#endif /* __DDR2_INIT_H__ */

