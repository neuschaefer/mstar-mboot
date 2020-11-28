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

#define DDR2_800MHz     0x01
#define DDR2_1066MHz    0x02
#define DDR2_1150MHz    0x03
#define DDR2_1200MHz    0x04
#define DDR2_1333MHz    0x05

#define DDR2_830MHz //based on 800

//#define DDR2_MIU_264MHz
//#define DDR2_MIU_246MHz
//#define DDR2_MIU_216MHz
//#define DDR2_MIU_192MHz

#if ( (ENABLE_MSTAR_NASA_BD_MST195A_D01A_S) \
   || (ENABLE_MSTAR_NASA_BD_MST195B_D01A_S) \
   || (ENABLE_MSTAR_NASA_BD_MST195C_D01A_S) \
   || (ENABLE_MSTAR_NASA_BD_MST186A_D01A_S) \
   || (ENABLE_MSTAR_NASA_BD_MST186E_D01A_S) \
   || (ENABLE_MSTAR_NASA_BD_MST060B_10AZBT_S) \
   || (ENABLE_MSTAR_NASA_BD_MST061B_10AZU_S) \
   || (ENABLE_MSTAR_NASA_BD_XL3_MEGA) \
   )
    #if ENABLE_MEM800MHz
        #define MIU_SPEED       DDR2_800MHz
    #elif ENABLE_MEM1066MHz
        #define MIU_SPEED       DDR2_1066MHz
    #elif ENABLE_MEM1150MHz
        #define MIU_SPEED       DDR2_1150MHz
    #elif ENABLE_MEM1200MHz
        #define MIU_SPEED       DDR2_1200MHz
    #elif ENABLE_MEM1333MHz
        #define MIU_SPEED       DDR2_1333MHz
    #else
        #error "Please select correct DDR2 Speed"
    #endif

#else
    #error "MIU interface isn't defined"
#endif

#if (MIU_SPEED == DDR2_800MHz)//MCLK 400MHz setting
static const MS_REG_INIT MIU_ATOP_Init[]=
{
    //set test mode of DDRPLL
    _RV32_2( 0x110d24 , 0x0000),
    //Clock setting
    _RV32_2( 0x110d36 , 0x0000),
    _RV32_2( 0x110d34 , 0x0200),
    //Set the clock frequency for dram & PLL reset
    #ifdef DDR2_830MHz//MCLK 415MHz setting
    _RV32_2( 0x110d30 , 0x9f26),
    _RV32_2( 0x110d32 , 0x0042),
    #else//MCLK 400MHz setting
    _RV32_2( 0x110d30 , 0xdcfa),
    _RV32_2( 0x110d32 , 0x0045),
    #endif
    _END_OF_TBL32_
};
#else
static const MS_REG_INIT MIU_ATOP_Init_1066[]=//G_1066
{
    //set test mode of DDRPLL
    _RV32_2( 0x110d22 , 0x2000),
    _RV32_2( 0x110d24 , 0x2000),
    //Clock setting
    _RV32_2( 0x110d36 , 0x0000),
    _RV32_2( 0x110d34 , 0x0200),
    //Set the clock frequency for dram & PLL reset
    #if defined (DDR2_MIU_264MHz)
    _RV32_2( 0x110d30 , 0x5d16),
    _RV32_2( 0x110d32 , 0x0034),
    #elif defined (DDR2_MIU_246MHz)
    _RV32_2( 0x110d30 , 0x31f2),
    _RV32_2( 0x110d32 , 0x0038),
    #elif defined (DDR2_MIU_216MHz)
    _RV32_2( 0x110d30 , 0xe141),
    _RV32_2( 0x110d32 , 0x003f),
    #elif defined (DDR2_MIU_192MHz)
    _RV32_2( 0x110d30 , 0xdd69),
    _RV32_2( 0x110d32 , 0x0047),
    #else
    _RV32_2( 0x110d30 , 0xdf56),
    _RV32_2( 0x110d32 , 0x0033),
    #endif
    _RV32_2( 0x110d24 , 0x3000),
    _RV32_2( 0x110da4 , 0x1000),
    _RV32_2( 0x110d24 , 0x2000),
    _RV32_2( 0x110da4 , 0x0000),
    _END_OF_TBL32_
};

static const MS_REG_INIT MIU_ATOP_Init_1333[]=//G_1333
{
    //set test mode of DDRPLL
    _RV32_2( 0x110d24 , 0x0000),
    //Clock setting
    _RV32_2( 0x110d36 , 0x0000),
    _RV32_2( 0x110d34 , 0x0200),
    //Set the clock frequency for dram & PLL reset
    #if (MIU_SPEED == DDR2_1150MHz)//MCLK 575MHz setting
    _RV32_2( 0x110d30, 0x06dc ),
    _RV32_2( 0x110d32, 0x0031 ),
    #elif (MIU_SPEED == DDR2_1200MHz)//MCLK 600MHz setting
    _RV32_2( 0x110d30, 0x8000 ),
    _RV32_2( 0x110d32, 0x002e ),
    #elif (MIU_SPEED == DDR2_1333MHz)//MCLK 666MHz setting
    _RV32_2( 0x110d30, 0xedab ),
    _RV32_2( 0x110d32, 0x0029 ),
    #endif
    _END_OF_TBL32_
};
#endif


#if (MIU_SPEED == DDR2_800MHz)//MCLK 400MHz setting
static const MS_REG_INIT MIU_DDR_Init[] =
{
    #if (ENABLE_MSTAR_NASA_MMAP_32MB)
    _RV32_2( 0x101202, 0x0252 ),
    #else
    _RV32_2( 0x101202, 0x0292 ),
    #endif
    _RV32_2( 0x101204, 0x008b ), //rd_timing
    #ifdef DDR2_830MHz//MCLK 415MHz setting
    _RV32_2( 0x101206, 0x0332 ),
    #else//MCLK 400MHz setting
    _RV32_2( 0x101206, 0x0330 ),
    #endif
    _RV32_2( 0x101208, 0x1666 ),
    _RV32_2( 0x10120a, 0x1c56 ),
    _RV32_2( 0x10120c, 0x7485 ),
    _RV32_2( 0x10120e, 0x202a ),
    _RV32_2( 0x101210, 0x0a62 ),
    _RV32_2( 0x101212, 0x4006 ),
    _RV32_2( 0x101214, 0x8000 ),
    _RV32_2( 0x101216, 0xc000 ),
    #ifdef DDR2_830MHz//MCLK 415MHz setting
    _RV32_2( 0x110d38, 0x0077 ),//reg_clkph_dq0             5       : [3:0]
                                //reg_clkph_dq1         5       : [7:4]
                                //reg_clkph_dqs0        0       : [11:8]
                                //reg_clkph_dqs1        0       : [15:12]
    _RV32_2( 0x110d3a, 0x0552 ),//reg_clkph_cmd             0       : [3:0]
                                //reg_clkph_dqsm0        4       : [7:4]
                                //reg_clkph_clk_a          4       : [11:8]
                                //reg_clkph_dqsm1          0       : [15:12]
    #else//MCLK 400MHz setting
    _RV32_2( 0x110d36, 0x0002 ),//reg_clkph_cko
    _RV32_2( 0x110d38, 0x2288 ),//reg_clkph_dq0             5       : [3:0]
                                //reg_clkph_dq1         5       : [7:4]
                                //reg_clkph_dqs0        0       : [11:8]
                                //reg_clkph_dqs1        0       : [15:12]
    _RV32_2( 0x110d3a, 0x0110 ),//reg_clkph_cmd             0       : [3:0]
                                //reg_clkph_dqsm0        4       : [7:4]
                                //reg_clkph_clk_a          4       : [11:8]
                                //reg_clkph_dqsm1          0       : [15:12]
    #endif
    _RV32_2( 0x110d02, 0x0000 ),
    _RV32_2( 0x10122c, 0x9300 ),
    _RV32_2( 0x110d04, 0x0000 ),//reg_dqs_pre_state : [7:0]
    _RV32_2( 0x110d3c, 0x0200 ),//reg_dqsm0_skew 0 [2:0]
                                //reg_dqsm1_skew 0 [6:4]
                                //reg_dqs_skew   2 [10:8]
                                //reg_cmd1_skew  0 [14:12]
    _RV32_2( 0x110d3e, 0x0022 ),//[2:0]   reg_oen_skew
                                //[6:4]   reg_dq_skew
                                //[10:8]  reg_cmd_skew
                                //[14:12] reg_cko_skew

    _RV32_2( 0x110d0e, 0x00e9 ),//[3:1] reg_dqsm_dly
    _RV32_2( 0x110d0e, 0x00a9 ),
    #ifdef DDR2_830MHz//MCLK 415MHz setting
    _RV32_2( 0x110d6e, 0x0065 ),//reg_dll0_ph : [3:0]
                                //reg_dll1_ph : [7:4]
    #else//MCLK 400MHz setting
    _RV32_2( 0x110d6e, 0x0076 ),//reg_dll0_ph : [3:0]
                                //reg_dll1_ph : [7:4]
    #endif
    _RV32_2( 0x110d6a, 0x004f ),
    _RV32_2( 0x110d68, 0x004f ),

    _END_OF_TBL32_,
};
#else
static const MS_REG_INIT MIU_DDR_Init_1066_64m[]=//G_1066_64m
{
    _RV32_2( 0x101202, 0x0292 ),
    _RV32_2( 0x101204, 0x008c ), //rd_timing
    #if defined (DDR2_MIU_264MHz)
    _RV32_2( 0x101206, 0x0420 ),
    #elif defined (DDR2_MIU_246MHz)
    _RV32_2( 0x101206, 0x0420 ),
    #elif defined (DDR2_MIU_216MHz)
    _RV32_2( 0x101206, 0x0428 ),
    #elif defined (DDR2_MIU_192MHz)
    _RV32_2( 0x101206, 0x0420 ),
    #else
    _RV32_2( 0x101206, 0x0430 ),
    #endif
    _RV32_2( 0x101208, 0x1888 ),
    _RV32_2( 0x10120a, 0x2246 ),
    _RV32_2( 0x10120c, 0x54a6 ),
    _RV32_2( 0x10120e, 0x2038 ),
    _RV32_2( 0x101210, 0x0e72 ),
    _RV32_2( 0x101212, 0x4006 ), //0x4042//150 ohm for DRAM ODT ON (0x101200[4] = 1)
    _RV32_2( 0x101214, 0x8000 ),
    _RV32_2( 0x101216, 0xc000 ),
    _RV32_2( 0x110d54, 0x0000 ),
    _RV32_2( 0x110d00, 0x0018 ),

    _RV32_2( 0x110d38, 0x0055 ),//reg_clkph_dq0             5       : [3:0]
                                //reg_clkph_dq1         5       : [7:4]
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

    _RV32_2( 0x110d6e, 0x6666 ),//reg_dll0_ph : [3:0]
                                //reg_dll1_ph : [7:4]
    _RV32_2( 0x110d6a, 0x004f ),
    _RV32_2( 0x110d68, 0x004f ),
    _RV32_2( 0x110d54, 0x0000 ),
    _END_OF_TBL32_,
};

static const MS_REG_INIT MIU_DDR_Init_1066_32m[]=//G_1066_32m
{
    _RV32_2( 0x101202, 0x0252 ), //@@@
    _RV32_2( 0x101204, 0x008c ), //rd_timing
    _RV32_2( 0x101206, 0x0430 ),
    _RV32_2( 0x101208, 0x1888 ),
    _RV32_2( 0x10120a, 0x2046 ), //@@@
    _RV32_2( 0x10120c, 0x5486 ), //@@@
    _RV32_2( 0x10120e, 0x2030 ), //@@@
    _RV32_2( 0x101210, 0x0e72 ),
    _RV32_2( 0x101212, 0x4006 ), //0x4042//150 ohm for DRAM ODT ON (0x101200[4] = 1)
    _RV32_2( 0x101214, 0x8000 ),
    _RV32_2( 0x101216, 0xc000 ),
    _RV32_2( 0x110d54, 0x0000 ),
    _RV32_2( 0x110d00, 0x0018 ),

    _RV32_2( 0x110d38, 0x0055 ),//reg_clkph_dq0             5       : [3:0]
                                //reg_clkph_dq1         5       : [7:4]
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

    _RV32_2( 0x110d6e, 0x6666 ),//reg_dll0_ph : [3:0]
                                //reg_dll1_ph : [7:4]
    _RV32_2( 0x110d6a, 0x004f ),
    _RV32_2( 0x110d68, 0x004f ),
    _RV32_2( 0x110d54, 0x0000 ),
    _END_OF_TBL32_,
};

static const MS_REG_INIT MIU_DDR_Init_1333[]=//G_1066
{
    _RV32_2( 0x101202, 0x0292 ),
    _RV32_2( 0x101204, 0x008d ), //rd_timing
    #if (MIU_SPEED == DDR2_1150MHz)//MCLK 575MHz setting
    _RV32_2( 0x101206, 0x0330 ),
    _RV32_2( 0x101208, 0x1b99 ),
    _RV32_2( 0x10120a, 0x2356 ),
    _RV32_2( 0x10120c, 0x55a8 ),
    _RV32_2( 0x10120e, 0x203f ),
    _RV32_2( 0x101210, 0x0002 ),
    #elif (MIU_SPEED == DDR2_1200MHz)//MCLK 600MHz setting
    _RV32_2( 0x101206, 0x0330 ),
    _RV32_2( 0x101208, 0x1b99 ),
    _RV32_2( 0x10120a, 0x2356 ),
    _RV32_2( 0x10120c, 0x55a8 ),
    _RV32_2( 0x10120e, 0x203f ),
    _RV32_2( 0x101210, 0x0002 ),
    #elif (MIU_SPEED == DDR2_1333MHz)//MCLK 666MHz setting
    _RV32_2( 0x101206, 0x0330 ),
    _RV32_2( 0x101208, 0x1e99 ),
    _RV32_2( 0x10120a, 0x2757 ),
    _RV32_2( 0x10120c, 0x55a8 ),
    _RV32_2( 0x10120e, 0x2046 ),
    _RV32_2( 0x101210, 0x0002 ),
    #endif
    _RV32_2( 0x101212, 0x4006 ), //0x4042//150 ohm for DRAM ODT ON (0x101200[4] = 1)
    _RV32_2( 0x101214, 0x8000 ),
    _RV32_2( 0x101216, 0xc000 ),

    _RV32_2( 0x110d38, 0x0055 ),//reg_clkph_dq0             5       : [3:0]
                                //reg_clkph_dq1         5       : [7:4]
                                //reg_clkph_dqs0        0       : [11:8]
                                //reg_clkph_dqs1        0       : [15:12]
    _RV32_2( 0x110d3a, 0x0000 ),//reg_clkph_cmd             0       : [3:0]
                                //reg_clkph_dqsm0        0       : [7:4]
                                //reg_clkph_clk_a          0       : [11:8]
                                //reg_clkph_dqsm1          0       : [15:12]
    _RV32_2( 0x110d02, 0x0000 ),
    _RV32_2( 0x10122c, 0x9300 ),
    _RV32_2( 0x110d04, 0x0000 ),//reg_dqs_pre_state : [7:0]
    _RV32_2( 0x110d3c, 0x0022 ),//reg_dqsm0_skew 0 [2:0]
                                //reg_dqsm1_skew 0 [6:4]
                                //reg_dqs_skew   2 [10:8]
                                //reg_cmd1_skew  0 [14:12]
    _RV32_2( 0x110d3e, 0x0000 ),//[2:0]   reg_oen_skew
                                //[6:4]   reg_dq_skew
                                //[10:8]  reg_cmd_skew
                                //[14:12] reg_cko_skew

    //##################==
    _RV32_2( 0x110d0e, 0x00eb ),//[3:1] reg_dqsm_dly
    _RV32_2( 0x110d0e, 0x00ab ),
    //##################==
    _RV32_2( 0x110d6e, 0x0065 ),//reg_dll0_ph : [3:0]
                                //reg_dll1_ph : [7:4]
    _RV32_2( 0x110d6a, 0x004f ),
    _RV32_2( 0x110d68, 0x004f ),
    _END_OF_TBL32_,
};
#endif

#endif /* __DDR2_INIT_H__ */

