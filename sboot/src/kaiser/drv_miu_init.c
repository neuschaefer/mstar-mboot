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
/// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __DDR3_INIT_H__
#define __DDR3_INIT_H__

#include "Board.h"
#include "c_riubase.h"
#include "datatype.h"
#include "drvRIU.h"
#include "hwreg_KAISER.h"

// Release note:
// Ver(0.0.0) 2010/2/3 refer to MSTV_TOOL MIU_INIT script file

#define  MIU_VER  'M','I','U','_','S','8',' ',' ','V','e','r',':','0','_','0','_','0'
#define  REG_ADDR_BASE      0x1f000000

#if 1 //ENABLE_SSC
    //#define SSC_MIU_ENABLE_DEFAULT          ENABLE
    //#define SSC_MIU_F_MODULATION_DEFAULT    200   //20000Hz < x < 30000Hz
    //#define SSC_MIU_F_DEVIATION_DEFAULT     1     //0.001   < y < 0.3

    //<1>.Caculate DDFM = (Loop_DIV_First * Loop_DIV_Second)/(Input_DIV_First * Input_DIV_Second);
    //<2>.From DDFSET register to get Fddr
    //<3>.Caculate DDFSPAN = Fddr / (4 * DDFM * Fmodulation)
    //        <3.1>  Fddr mempll clk out unit:Hz
    //        <3.2>  Fmodulation =  SSC_MIU_F_MODULATION_DEFAULT *100
    //<4>.Caculate DDFSTEP = (FDeviation * DDFSET * 1024 * 2) / (2 * DDFSPAN )
    //         <4.1> FDeviation= (u16FDeviation / 1000)
    //<5>.Set ENABLE

    #if (MIU_INTERFACE==DDR3_INTERFACE_BGA)
        //MEMPLL=1300Mhz
        #define    DDFM             12
        #define    DDFSET           0x200
        #define    DDFSPAN          0x2a3
        #define    DDFSTEP          0x8    //1% F_DEVIATION
    #else   //(  MIU_INTERFACE  ==  DDR2_INTERFACE_BGA )
        //MEMPLL=1066MHZ
        #define    DDFM             10
        #define    DDFSET           0x207
        #define    DDFSPAN          0x299
        #define    DDFSTEP          0x08  //1% F_DEVIATION
    #endif
#endif

// use ENABLE_MEM1300MHz
// use ENABLE_MEM1066MHz
// use ENABLE_MEM800MHz
// use ENABLE_MEM667MHz

#if (MIU_DRAM_LEN >= 0x10000000)
    #define DRAM_SIZE_SETTING   0x0000  // no limit
#elif (MIU_DRAM_LEN >= 0x8000000)       // 128MB
    #define DRAM_SIZE_SETTING   0x0700
#elif (MIU_DRAM_LEN >= 0x4000000)       // 64MB
    #define DRAM_SIZE_SETTING   0x0600
#elif (MIU_DRAM_LEN >= 0x2000000)       // 32MB
    #define DRAM_SIZE_SETTING   0x0500
#else
    #define DRAM_SIZE_SETTING   0x0400
#endif


#ifndef __ASSEMBLER__

//MEM_PLL relative
// reg_0x101bFC       :   0:fmpll=216Mhz, 1:fmpll=432Mhz
// reg_0x110d32~110d30:   DDFSET
// reg_0x110d36[15,14]:   DDRPLL_LOOP_DIV_1st
// reg_0x110d36[13,12]:   DDRPLL_input_DIV_1st
// reg_0x110d34[7~0]  :   DDRPLL_LOOP_DIV_2nd
// reg_0x110d34[15,8] :   DDRPLL_input_DIV_2nd
//mclk1x = ( fmpll *524288 * DDRPLL_LOOP_DIV_1st * DDRPLL_LOOP_DIV_2nd ) /
//         (ddfset * DDRPLL_input_DIV_1st *DDRPLL_input_DIV_2nd )

const MS_REG_INIT MIU0_DDR_Init[] =
{
    #if(MIU_CONFIG == DDR3_MIU0_16_MIU1_16)
    //SEL MAPPING FOR 2LB
    _RV32_2( 0x110d7e, 0x0004  ),  //20130115 select 2LB
    _RV32_2( 0x110dfe, 0x000c  ),  //20130115 select 2LB
    #endif

    #if(ENABLE_MEM1866MHz) //ENABLE_MEM1866MHz
    _RV32_2( 0x101202, 0xf3a7  ),  //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    _RV32_2( 0x101204, 0x004b  ),  //if I64Mode =0x8b else =0x0b
    _RV32_2( 0x101206, 0x0d38  ),  //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2( 0x101208, 0x20dd  ),  //reg_tRCD
    _RV32_2( 0x10120a, 0x2e76  ),  //reg_tRRD
    _RV32_2( 0x10120c, 0xc7e9  ),  //reg_tWL
    _RV32_2( 0x10120e, 0x4096  ),  //tRFC
    _RV32_2( 0x101210, 0x1f14  ),  //MR0
    _RV32_2( 0x101212, 0x4004  ),  //MR1
    _RV32_2( 0x101214, 0x8020  ),  //MR2
    _RV32_2( 0x101216, 0xC000  ),  //MR3
    #elif (ENABLE_MEM1600MHz)

    #if(MIU_CONFIG == DDR3_MIU0_16_MIU1_16)
    _RV32_2( 0x101202, 0xf3a3  ),  //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    #else
    _RV32_2( 0x101202, 0xf3a7  ),  //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    #endif
    _RV32_2( 0x101204, 0x004a  ),  //if I64Mode =0x8b else =0x0b
    _RV32_2( 0x101206, 0x0c30  ),  //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2( 0x101208, 0x1cbb  ),  //reg_tRCD
    _RV32_2( 0x10120a, 0x2766  ),  //reg_tRRD
    _RV32_2( 0x10120c, 0x96c8  ),  //reg_tWL
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_32_4GB)
    _RV32_2( 0x10120e, 0x4114  ),  //tRFC
    #else
    _RV32_2( 0x10120e, 0x4082  ),  //tRFC
    #endif
    _RV32_2( 0x101210, 0x1c70  ),  //MR0
    _RV32_2( 0x101212, 0x4040  ),  //MR1
    _RV32_2( 0x101214, 0x8018  ),  //MR2
    _RV32_2( 0x101216, 0xC000  ),  //MR3
    #else
    #error "Unsupport DDR freq!!!"
    #endif //ENABLE_MEM1866MHz

    _RV32_2( 0x101226, 0x0000  ),
    #if(ENABLE_MEM1866MHz)
    _RV32_2( 0x101228, 0x40b0  ), // enable dynamic ODT (20130515)
    #else
    #if (MIU_CONFIG == DDR3_MIU0_16_MIU1_16)
    _RV32_2( 0x101228, 0x4000  ),
    #else
    _RV32_2( 0x101228, 0x40b0  ), // enable dynamic ODT (20130515)
    #endif
    #endif
    _RV32_2( 0x10122c, 0x0000  ),

#if (ENABLE_MSTAR_MOBF_ENABLE)

    #if(ENABLE_MEM1866MHz)
    _RV32_2( 0x1012d8, 0x0200 ),       // 1866Mhz can only support bypass mode...
    //_RV32_2( 0x1012d8, 0x0400  ),    // Enable dramobf with 8 bit mode
    //_RV32_2( 0x100cec, 0xC000  ),    // MOBF enable (drm_secure)
    #else
    //enable DramOBF and MIU write cache
    //chip_top
    //_RV32_2( 0x101e80, 0x0000  ),
    //_RV32_2( 0x101e80, 0x0003  ),    //[0] sec_r2 miu_write_cache one_queue mode enable [1] sec_r2 miu_write_cache ultra mode enable
    //_RV32_2( 0x101e84, 0x0102  ),    //MIU write cache bypass [0:47], (JPD, HVD bypass miu_write_cache)
    //_RV32_2( 0x101e86, 0x0002  ),    //VP6 bypass miu_write_cache
    //_RV32_2( 0x101e88, 0x0000  ),

    #if 1
    _RV32_2( 0x101e80, 0x0001  ),    //miu_write_cache one_queue
    _RV32_2( 0x101e84, 0x0000  ),    //MIU write cache bypass [0:47], (JPD, HVD bypass miu_write_cache)
    _RV32_2( 0x101e86, 0x0000  ),    //VP6 bypass miu_write_cache
    _RV32_2( 0x101e88, 0x0000  ),
    #endif

    /*
    //_RV32_2( 0x101e80, 0x0001  ),    //miu_write_cache one_queue
    _RV32_2( 0x101e80, 0x0000  ),    //miu_write_cache one_queue
    _RV32_2( 0x101e84, 0xFFFF  ),    //MIU write cache bypass [0:47], (JPD, HVD bypass miu_write_cache)
    _RV32_2( 0x101e86, 0xFFFF  ),    //VP6 bypass miu_write_cache
    _RV32_2( 0x101e88, 0xFFFF  ),
    */

    //Must set to 0x0000?
    _RV32_2( 0x101e8a, 0x0001  ),    //[0] sec_r2 miu_write_cache one_queue mode enable [1] sec_r2 miu_write_cache ultra mode enable

    //miu_write_cache one_queue mode enable
    _RV32_2( 0x101efc, 0xFFFF  ),   // enable all module

    //miu_write_cache ultra mode enable
    _RV32_2( 0x101efe, 0xFFFF  ),   // enable all module

    //ca9 one-que mode
    _RV32_2( 0x10188a, 0x0080  ),    //un-mask last

    _RV32_2( 0x101ef8, 0x0000  ),
    _RV32_2( 0x101efc, 0xffff  ),
    _RV32_2( 0x101efe, 0xffff  ),

    //_RV32_2( 0x1012d8, 0x0400 ),    // Enable dramobf with 8 bit mode
    //_RV32_2( 0x1012d8, 0x0000 ),    // Enable dramobf with 64 bit mode (2 des)
    _RV32_2( 0x1012d8, 0x0100 ),    // Enable dramobf with 64 bit mode (4 des)
    //_RV32_2( 0x1012d8, 0x0200 ),    // Enable dramobf with bypass mode
    //_RV32_2( 0x100cec, 0xC000 ),    // MOBF enable (drm_secure)
    #endif
#endif

    //_RV32_2( 0x10125a, 0x4040  ),  // reduce 2t latency en
    //_RV32_2( 0x10125a, 0x0040  ),  // reduce 2t latency en

    _RV32_2( 0x1012d4, 0x0000  ),   // 20130108 turn off read_last_done_z_bypass
    _RV32_2( 0x1012b2, 0xffff  ),   // 20130108 change last_done_z position
    _RV32_2( 0x101292, 0xffff  ),   // 20130108 change last_done_z position
    _RV32_2( 0x101272, 0xffff  ),   // 20130108 change last_done_z position
    _RV32_2( 0x101252, 0xffff  ),   // 20130108 change last_done_z position

    #if(MIU_CONFIG == DDR3_MIU0_16_MIU1_16)
    _RV32_2( 0x110d00, 0x0a03 ),  //20130109 PAD MUX and IC side odt enable
    #else
    _RV32_2( 0x110d00, 0x0a00  ),  //reg_pkg_sel       1    [0] //IC side odt enable (20130104)
    #endif
    _RV32_2( 0x110d04, 0x0080  ),  //reg_dqs_pre_state
    _RV32_2( 0x110d10, 0x0200  ),

    #if(ENABLE_MEM1866MHz) //ENABLE_MEM1866MHz
    _RV32_2( 0x110d38, 0x0044  ),
    _RV32_2( 0x110d48, 0x0044  ),
    _RV32_2( 0x110d3a, 0x7072  ),
    _RV32_2( 0x110d4a, 0x0002  ),
    _RV32_2( 0x110d02, 0x0000  ),
    #elif(ENABLE_MEM1600MHz)
    #if(MIU_CONFIG == DDR3_MIU0_16_MIU1_16)
    _RV32_2( 0x110d38, 0x0055  ),
    _RV32_2( 0x110d48, 0x0055  ),
    _RV32_2( 0x110d3a, 0x5052  ),
    _RV32_2( 0x110d4a, 0x5052  ),
    #else
    _RV32_2( 0x110d38, 0x0044  ),
    _RV32_2( 0x110d48, 0x0044  ),
    _RV32_2( 0x110d3a, 0x7052  ),
    _RV32_2( 0x110d4a, 0x9092  ),
    #endif

    _RV32_2( 0x110d02, 0x0000  ),
    #else
    #error "Unsupport DDR freq!!!"
    #endif //ENABLE_MEM1866MHz

    #if(ENABLE_MEM1866MHz) //ENABLE_MEM1866MHz
    _RV32_2( 0x110d3c, 0x1333  ),
    _RV32_2( 0x110d4c, 0x0044  ),
    #elif(ENABLE_MEM1600MHz)
    _RV32_2( 0x110d3c, 0x1133  ),
    _RV32_2( 0x110d4c, 0x0033  ),
    #else
    #error "Unsupport DDR freq!!!"
    #endif //ENABLE_MEM1866MHz


    #if(MIU_CONFIG == DDR3_MIU0_16_MIU1_16)
    _RV32_2( 0x110d5a, 0x5555  ),
    _RV32_2( 0x110d5c, 0x5555  ),
    _RV32_2( 0x110d5e, 0x5555  ),
    #else
    _RV32_2( 0x110d5a, 0x3333  ),

    #if(ENABLE_MEM1600MHz)
    _RV32_2( 0x110d5c, 0x3333  ),
    #else
    _RV32_2( 0x110d5c, 0x4444  ),
    #endif

    _RV32_2( 0x110d5e, 0x3333  ),
    #endif

    #if(ENABLE_MEM1866MHz)
    _RV32_2( 0x110d3e, 0x1033  ),
    #elif(ENABLE_MEM1600MHz)
    _RV32_2( 0x110d3e, 0x1011  ),
    #else
    #error "Unsupport DDR freq!!!"
    #endif

    #if(MIU_CONFIG == DDR3_MIU0_16_MIU1_16)
    _RV32_2( 0x110d50, 0x1110  ),
    _RV32_2( 0x110d74, 0x4444  ),
    _RV32_2( 0x110d52, 0x0044  ),
    _RV32_2( 0x110d6c, 0xbbbb  ),
    _RV32_2( 0x110d6e, 0xbbbb  ),
    _RV32_2( 0x110d6a, 0x0020  ),
    _RV32_2( 0x110d68, 0x0020  ),
    #else
    _RV32_2( 0x110d50, 0x1110  ),
    _RV32_2( 0x110d52, 0x0000  ),
    _RV32_2( 0x110d6a, 0x0020  ),
    _RV32_2( 0x110d68, 0x0020  ),
    _RV32_2( 0x110d74, 0x2222  ), //reg_trg_lvl    2013.07.17 for K3S read phase performance
    #endif

    #if(ENABLE_MEM1600MHz)
    _RV32_2( 0x110d50, 0x1111  ),
    #else
    _RV32_2( 0x110d50, 0x1100  ),
    #endif

    _RV32_2( 0x110d52, 0x0075  ),

    _RV32_2( 0x110d6a, 0x0020  ),
    _RV32_2( 0x110d68, 0x0020  ),
    #if(ENABLE_MEM1866MHz)
    _RV32_2( 0x110d74, 0x2222  ), //reg_trg_lvl    2013.07.17 for K3S read phase performance
    #elif(ENABLE_MEM1600MHz)
    _RV32_2( 0x110d74, 0x2222  ), //reg_trg_lvl    2013.07.17 for K3S read phase performance
    #else
    #error "Unsupport DDR freq!!!"
    #endif

    _RV32_2( 0x110d72, 0x0003  ),

    //DLL calibration
    _RV32_2( 0x110d60, 0x000c  ),
    _RV32_2( 0x110d60, 0x0008  ),
    _RV32_2( 0x110d62, 0x007f  ),
    _RV32_2( 0x110d64, 0xf200  ),
    _RV32_2( 0x110d60, 0x2370  ),

    _END_OF_TBL32_,
    MIU_VER
};

const MS_REG_INIT MIU1_DDR_Init[] =
{
    #if(MIU_CONFIG == DDR3_MIU0_16_MIU1_16)
    _RV32_2( 0x100602, 0xf3a3  ),  //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    #else
    _RV32_2( 0x100602, 0xf3a7  ),  //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
    #endif

    #if(ENABLE_MEM1866MHz)
    _RV32_2( 0x100604, 0x004b  ),  //if I64Mode =0x8b else =0x0b
    _RV32_2( 0x100606, 0x0d38  ),  //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    _RV32_2( 0x100608, 0x20dd  ),  //reg_tRCD
    _RV32_2( 0x10060a, 0x2e76  ),  //reg_tRRD
    _RV32_2( 0x10060c, 0xc7e9  ),  //reg_tWL
    _RV32_2( 0x10060e, 0x4096  ),  //tRFC
    _RV32_2( 0x100610, 0x1f14  ),  //MR0
    _RV32_2( 0x100612, 0x4004  ),  //MR1
    _RV32_2( 0x100614, 0x8020  ),  //MR2
    _RV32_2( 0x100616, 0xC000  ),  //MR3
    #elif(ENABLE_MEM1600MHz)
    _RV32_2( 0x100604, 0x004a  ),  //if I64Mode =0x8b else =0x0b
    #if(MIU_CONFIG == DDR3_MIU0_16_MIU1_16)
    _RV32_2( 0x100606, 0x0430  ),  //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    #else
    _RV32_2( 0x100606, 0x0c30  ),  //refresh cycle=0x50 ,TURN_ON_SCRAMBLE=0x8450
    #endif
    _RV32_2( 0x100608, 0x1cbb  ),  //reg_tRCD
    _RV32_2( 0x10060a, 0x2766  ),  //reg_tRRD
    _RV32_2( 0x10060c, 0x96c8  ),  //reg_tWL
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_32_4GB)
    _RV32_2( 0x10060e, 0x4114  ),  //tRFC
    #else
    _RV32_2( 0x10060e, 0x4082  ),  //tRFC
    #endif
    _RV32_2( 0x100610, 0x1c70  ),  //MR0
    _RV32_2( 0x100612, 0x4040  ),  //MR1
    _RV32_2( 0x100614, 0x8018  ),  //MR2
    _RV32_2( 0x100616, 0xC000  ),  //MR3

    _RV32_2( 0x100666, 0x0000  ),  //unmask group1
    #else
    #error "Unsupport DDR freq!!!"
    #endif

    #if(ENABLE_MEM1866MHz)
    _RV32_2( 0x100628, 0x40b0  ), // enable dynamic ODT (20130515)
    #else
    #if(MIU_CONFIG == DDR3_MIU0_16_MIU1_16)
    _RV32_2( 0x100628, 0x4000  ),
    #else
    _RV32_2( 0x100628, 0x40b0  ), // enable dynamic ODT (20130515)
    #endif
    #endif
    _RV32_2( 0x10062c, 0x0000  ),

#if (ENABLE_MSTAR_MOBF_ENABLE)

    #if(ENABLE_MEM1866MHz)
    //1866MHz DO NOT support 64bit DramOBF, only 8bit mode
    _RV32_2( 0x1006d8, 0x0400  ), //Enable dramobf with 8 bit mode
    #else
    //enable DramOBF and MIU write cache

    //_RV32_2( 0x1006d8, 0x0400 ),    // Enable dramobf with 8 bit mode
    //_RV32_2( 0x1006d8, 0x0000 ),    // Enable dramobf with 64 bit mode (2 des)
    _RV32_2( 0x1006d8, 0x0100 ),    // Enable dramobf with 64 bit mode (4 des)
    //_RV32_2( 0x1006d8, 0x0200 ),    // Enable dramobf with bypass mode
    #endif
#endif //ENABLE_MSTAR_MOBF_ENABLE


    //_RV32_2( 0x10065a, 0x4040  ), //    reduce 2t latency en
    //_RV32_2( 0x10065a, 0x0040  ), //reduce 2t latency en

    _RV32_2( 0x1006d4, 0x0000  ),   // 20130108 turn off read_last_done_z_bypass
    _RV32_2( 0x1006b2, 0xffff  ),   // 20130108 change last_done_z position
    _RV32_2( 0x100692, 0xffff  ),   // 20130108 change last_done_z position
    _RV32_2( 0x100672, 0xffff  ),   // 20130108 change last_done_z position
    _RV32_2( 0x100652, 0xffff  ),   // 20130108 change last_done_z position

    #if(MIU_CONFIG == DDR3_MIU0_16_MIU1_16)
    _RV32_2( 0x110d80, 0x0a03  ),
    #else
    _RV32_2( 0x110d80, 0x0a00  ),
    #endif

    _RV32_2( 0x110d84, 0x0080  ),
    _RV32_2( 0x110d90, 0x0200  ),

    #if(ENABLE_MEM1866MHz) //ENABLE_MEM1866MHz
    _RV32_2( 0x110db8, 0x0044  ),
    _RV32_2( 0x110dc8, 0x0044  ),
    _RV32_2( 0x110dba, 0x5052  ),
    _RV32_2( 0x110dca, 0x0002  ),
    _RV32_2( 0x110d82, 0x0000  ),
    _RV32_2( 0x110dca, 0x5052  ),
    #elif(ENABLE_MEM1600MHz)
    #if(MIU_CONFIG == DDR3_MIU0_16_MIU1_16)
    _RV32_2( 0x110db8, 0x0055  ),
    _RV32_2( 0x110dc8, 0x0055  ),
    _RV32_2( 0x110dba, 0x5052  ),
    _RV32_2( 0x110dca, 0x5052  ),
    #else
    _RV32_2( 0x110db8, 0x0044  ),
    _RV32_2( 0x110dc8, 0x0044  ),
    _RV32_2( 0x110dba, 0x7072  ), //reg_clkph_cmd
    _RV32_2( 0x110dca, 0x9092  ),
    #endif

    _RV32_2( 0x110d82, 0x0000  ),
    #else
    #error "Unsupport DDR freq!!!"
    #endif //ENABLE_MEM1866MHz


    #if(ENABLE_MEM1866MHz) //ENABLE_MEM1866MHz
    _RV32_2( 0x110dbc, 0x1333  ),
    _RV32_2( 0x110dcc, 0x0044  ),
    _RV32_2( 0x110dbe, 0x1033  ),
    _RV32_2( 0x110dd0, 0x1100  ),
    _RV32_2( 0x110dd2, 0x0000  ),
    #elif(ENABLE_MEM1600MHz)
    _RV32_2( 0x110dbc, 0x1133  ),
    _RV32_2( 0x110dcc, 0x0033  ),
    _RV32_2( 0x110dbe, 0x1011  ),

    #if(MIU_CONFIG == DDR3_MIU0_16_MIU1_16)
    _RV32_2( 0x110dd0, 0x1110  ),
    _RV32_2( 0x110df4, 0x4444  ),
    _RV32_2( 0x110dd2, 0x0044  ),
    #else
    _RV32_2( 0x110dd0, 0x1111  ),
    #endif

    #else
    #error "Unsupport DDR freq!!!"
    #endif //ENABLE_MEM1866MHz

    #if(MIU_CONFIG == DDR3_MIU0_16_MIU1_16)
    _RV32_2( 0x110dda, 0x5555  ),
    _RV32_2( 0x110ddc, 0x5555  ),
    _RV32_2( 0x110dde, 0x5555  ),
    #else
    _RV32_2( 0x110dda, 0x3333  ),
    _RV32_2( 0x110ddc, 0x4444  ),
    _RV32_2( 0x110dde, 0x3333  ),
    #endif

    #if(ENABLE_MEM1866MHz) //ENABLE_MEM1866MHz
    _RV32_2( 0x110d0e, 0x00e9  ),
    _RV32_2( 0x110d0e, 0x00a9  ),
    _RV32_2( 0x110d0e, 0x00e9  ),

    _RV32_2( 0x1012f0, 0x0000  ), // SW Patch for BIST, 20130108 select MIU0
    _RV32_2( 0x1012e4, 0x0001  ), // 20130108 test one data
    _RV32_2( 0x1012e0, 0x0200  ), // 20130108 write only
    _RV32_2( 0x1012e0, 0x0201  ), // 20130108 write onlyd
    _RV32_2( 0x1012e0, 0x0201  ), // 20130108 dummy write only
    _RV32_2( 0x1012e0, 0x0000  ), // 20130108 return to original state

    _RV32_2( 0x110d0e, 0x00a9  ),
    _RV32_2( 0x110d6c, 0x6688  ), //reg_dll0_ph         [3:0]
    _RV32_2( 0x110d6e, 0x6677  ), //reg_dll0_ph         [3:0]
    #elif(ENABLE_MEM1600MHz)
    _RV32_2( 0x110d0e, 0x00e7  ),
    _RV32_2( 0x110d0e, 0x00a7  ),
    _RV32_2( 0x110d0e, 0x00e7  ),

    _RV32_2( 0x1012f0, 0x0000  ), // SW Patch for BIST, 20130108 select MIU0
    _RV32_2( 0x1012e4, 0x0001  ), // 20130108 test one data
    _RV32_2( 0x1012e0, 0x0200  ), // 20130108 write only
    _RV32_2( 0x1012e0, 0x0201  ), // 20130108 write onlyd
    _RV32_2( 0x1012e0, 0x0201  ), // 20130108 dummy write only
    _RV32_2( 0x1012e0, 0x0000  ), // 20130108 return to original state

    _RV32_2( 0x1012e0, 0x0000  ), // test write only // 20130104 for first wring data revised

    _RV32_2( 0x110d0e, 0x00a7  ),

    #if(MIU_CONFIG == DDR3_MIU0_16_MIU1_16)
    _RV32_2( 0x110d6c, 0xbbbb  ),
    _RV32_2( 0x110d6e, 0xbbbb  ),
    #else
    _RV32_2( 0x110d6c, 0x7777  ),
    _RV32_2( 0x110d6e, 0x7777  ),
    #endif

    #else
    #error "Unsupport DDR freq!!!"
    #endif //ENABLE_MEM1866MHz

    #if(ENABLE_MEM1866MHz) //ENABLE_MEM1866MHz
    _RV32_2( 0x110d8e, 0x00e9  ),
    _RV32_2( 0x110d8e, 0x00a9  ),
    _RV32_2( 0x110d8e, 0x00e9  ),

    _RV32_2( 0x1012f0, 0x8000  ), // SW Patch for BIST, 20130108 select MIU1
    _RV32_2( 0x1012e4, 0x0001  ), // 20130108 test one data
    _RV32_2( 0x1012e0, 0x0200  ), // 20130108 write only
    _RV32_2( 0x1012e0, 0x0201  ), // 0130108 write only
    _RV32_2( 0x1012e0, 0x0201  ), // 0130108 write only
    _RV32_2( 0x1012e0, 0x0000  ), // 20130108 return to original state
    _RV32_2( 0x1012f0, 0x0000  ), // 20130108 select MIU0

    _RV32_2( 0x110d8e, 0x00a9  ),
    _RV32_2( 0x110dec, 0x6677  ),
    _RV32_2( 0x110dee, 0x6677  ),
    #elif(ENABLE_MEM1600MHz)
    _RV32_2( 0x110d8e, 0x00e7  ),
    _RV32_2( 0x110d8e, 0x00a7  ),
    _RV32_2( 0x110d8e, 0x00e7  ),

    _RV32_2( 0x1012f0, 0x8000  ), // SW Patch for BIST, 20130108 select MIU1
    _RV32_2( 0x1012e4, 0x0001  ), // 20130108 test one data
    _RV32_2( 0x1012e0, 0x0200  ), // 20130108 write only
    _RV32_2( 0x1012e0, 0x0201  ), // 0130108 write only
    _RV32_2( 0x1012e0, 0x0201  ), // 0130108 write only
    _RV32_2( 0x1012e0, 0x0000  ), // 20130108 return to original state
    _RV32_2( 0x1012f0, 0x0000  ), // 20130108 select MIU0

    _RV32_2( 0x110d8e, 0x00a7  ),
    #if(MIU_CONFIG == DDR3_MIU0_16_MIU1_16)
    _RV32_2( 0x110dec, 0xbbbb  ), //reg_dll1_ph
    _RV32_2( 0x110dee, 0xbbbb  ), //reg_dll1_ph
    #else
    _RV32_2( 0x110dec, 0x7777  ), //reg_dll1_ph
    _RV32_2( 0x110dee, 0x7777  ), //reg_dll1_ph
    #endif

    #else
    #error "Unsupport DDR freq!!!"
    #endif //ENABLE_MEM1866MHz

    _RV32_2( 0x110dea, 0x0020  ),
    _RV32_2( 0x110de8, 0x0020  ),
    #if(ENABLE_MEM1866MHz) //ENABLE_MEM1866MHz
    _RV32_2( 0x110df4, 0x2222  ), //reg_trg_lvl 2013.07.17 for K3S read phase performance
    #elif(ENABLE_MEM1600MHz)
    _RV32_2( 0x110df4, 0x2222  ), //reg_trg_lvl 2013.07.17 for K3S read phase performance
    #else
    #error "Unsupport DDR freq!!!"
    #endif //ENABLE_MEM1866MHz

    _RV32_2( 0x110df2, 0x0003  ),

    //DLL calibration
    _RV32_2( 0x110de0, 0x000c  ),
    _RV32_2( 0x110de0, 0x0008  ),
    _RV32_2( 0x110de2, 0x007f  ),
    _RV32_2( 0x110de4, 0xf200  ),
    _RV32_2( 0x110de0, 0x2370  ),

    _END_OF_TBL32_,
};


#endif /* !__ASSEMBLER__ */
#endif /* __DDR3_INIT_H__ */
