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

#ifndef __DDR3_INIT_H__
#define __DDR3_INIT_H__

#include "Board.h"
#include "c_riubase.h"

// Release note:
// Ver(0.0.0) 2010/2/3 refer to MSTV_TOOL MIU_INIT script file

#define  MIU_VER  'M','I','U','_','S','8',' ',' ','V','e','r',':','0','_','0','_','0'
#define  REG_ADDR_BASE      0xbf000000

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

    #if (  MIU_INTERFACE  ==  DDR3_INTERFACE_BGA )
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


#ifndef __ASSEMBLER__

#include "drvRIU.h"

const MS_REG_INIT MIU0_DDR_Init[] =
{
#if ( MIU_INTERFACE == DDR3_INTERFACE_BGA)
    #if (MIU_CONFIG == DDR3_MIU0_16_MIU1_16)
    _RV32_1(   0x101202, 0xa3   ),//reg_dram_type        10  : [1:0]   00 : sdr, 01 : ddr, 10 : ddr2, 11 : ddr3
    #elif ((MIU_CONFIG == DDR3_MIU0_32_MIU1_16) || (MIU_CONFIG == DDR3_MIU0_32_MIU1_16_By_8BIT))
    _RV32_1(   0x101202, 0xa7   ),//reg_dram_type        10  : [1:0]   00 : sdr, 01 : ddr, 10 : ddr2, 11 : ddr3
    #else
    #error "MIU_CONFIG isn't defined"
    #endif
    _RV32_1(   0x101203, 0x03   ),//reg_dram_type        10  : [1:0]   00 : sdr, 01 : ddr, 10 : ddr2, 11 : ddr3
    _RV32_1(   0x101204, 0x0a   ),//reg_rd_timing        9   : [4:0]
    _RV32_1(   0x101205, 0x00   ),//reg_rd_timing        9   : [4:0]
    #if(ENABLE_MEM1300MHz)
    _RV32_1(   0x101206, 0x50   ),//tREFRESH     2b  : [7:0] * 16
    _RV32_1(   0x101207, 0x04   ),//tREFRESH     2b  : [7:0] * 16
    _RV32_1(   0x101208, 0x99   ),//reg_tRCD     6   : [3:0]     11.25/1.875= 6
    _RV32_1(   0x101209, 0x18   ),//reg_tRCD     6   : [3:0]     11.25/1.875= 6
    _RV32_1(   0x10120a, 0x55   ),//reg_tRRD         4   : [3:0]  10/1.875= 6
    _RV32_1(   0x10120b, 0x22   ),//reg_tRRD         4   : [3:0]  10/1.875= 6
    _RV32_1(   0x10120c, 0xA8   ),//reg_tWL          5   : [3:0]  CAS latency -1
    _RV32_1(   0x10120d, 0xA5   ),//reg_tWL          5   : [3:0]  CAS latency -1
    _RV32_1(   0x10120e, 0xA4   ),//tRFC         2a  : [7:0]     127.5/1.875= 68
    _RV32_1(   0x10120f, 0x40   ),//tRFC         2a  : [7:0]     127.5/1.875= 68
    #endif
    #if(ENABLE_MEM1600MHz)
    _RV32_1(   0x101206, 0x60   ),//tREFRESH     2b  : [7:0] * 16
    _RV32_1(   0x101207, 0x04   ),//tREFRESH     2b  : [7:0] * 16
    _RV32_1(   0x101208, 0xbb   ),//reg_tRCD     6   : [3:0]     11.25/1.875= 6
    _RV32_1(   0x101209, 0x1c   ),//reg_tRCD     6   : [3:0]     11.25/1.875= 6
    _RV32_1(   0x10120a, 0xb6   ),//reg_tRRD         4   : [3:0]  10/1.875= 6
    _RV32_1(   0x10120b, 0x27   ),//reg_tRRD         4   : [3:0]  10/1.875= 6
    _RV32_1(   0x10120c, 0xc8   ),//reg_tWL          5   : [3:0]  CAS latency -1
    _RV32_1(   0x10120d, 0x96   ),//reg_tWL          5   : [3:0]  CAS latency -1
    _RV32_1(   0x10120e, 0x5a   ),//tRFC         2a  : [7:0]     127.5/1.875= 68
    _RV32_1(   0x10120f, 0x40   ),//tRFC         2a  : [7:0]     127.5/1.875= 68
    #endif

    _RV32_1(   0x101210, 0x70   ),//MR0              : [15:0]
    _RV32_1(   0x101211, 0x1c   ),//MR0              : [15:0]
    #if(ENABLE_MEM1600MHz)
    _RV32_1(   0x101212, 0x40   ),//MR1              : [15:0]    [6],[2] ODT on
    #endif
    #if(ENABLE_MEM1300MHz)
    _RV32_1(   0x101212, 0x40   ),//MR1              : [15:0]    [6],[2] ODT on
    #endif
    _RV32_1(   0x101213, 0x40   ),//MR1              : [15:0]    [6],[2] ODT on
    _RV32_1(   0x101214, 0x18   ),//MR2              : [15:0]
    _RV32_1(   0x101215, 0x80   ),//MR2              : [15:0]
    _RV32_1(   0x101216, 0x00   ),//MR3              : [15:0]
    _RV32_1(   0x101217, 0xc0   ),//MR3              : [15:0]
    #if(ENABLE_MEM1300MHz)
    _RV32_1(   0x101226, 0X00   ),
    _RV32_1(   0x101227, 0x00   ),
    _RV32_1(   0x101228, 0x92   ),
    _RV32_1(   0x101229, 0x64   ),
    _RV32_1(   0x10122c, 0x00   ),
    _RV32_1(   0x10122d, 0x00   ),
    #endif
    #if(ENABLE_MEM1600MHz)
    _RV32_1(   0x101226, 0X00   ),
    _RV32_1(   0x101227, 0x00   ),
    _RV32_1(   0x101228, 0x92   ),
    _RV32_1(   0x101229, 0x64   ),
    #endif

    _RV32_1(   0x110d00, 0x11   ),//reg_pkg_sel      1   : [0]
    #if(ENABLE_MEM1600MHz)
    _RV32_1(   0x110d00, 0x01   ),//reg_pkg_sel      1   : [0]
    _RV32_1(   0x110d01, 0x0a   ),//reg_pkg_sel      1   : [0]
    #endif
    #if(ENABLE_MEM1300MHz)
    _RV32_1(   0x110d01, 0x02   ),//reg_pkg_sel      1   : [0]
    #endif
    _RV32_1(   0x110d04, 0x80   ),//reg_pkg_sel      1   : [0]
    _RV32_1(   0x110d05, 0x00   ),//reg_pkg_sel      1   : [0]
    #if(ENABLE_MEM1300MHz)
    _RV32_1(   0x110d10, 0x00   ),//reg_pkg_sel      1   : [0]
    _RV32_1(   0x110d11, 0x0c   ),//reg_pkg_sel      1   : [0]
    #endif

    #if(ENABLE_MEM1300MHz)
    _RV32_1(   0x110d38, 0x44   ),//reg_clkph_dq0            3       : [3:0]
    _RV32_1(   0x110d39, 0x00   ),//reg_clkph_dq0            3       : [3:0]
    #endif
    #if(ENABLE_MEM1600MHz)
    _RV32_1(   0x110d38, 0x66   ),//reg_clkph_dq0            3       : [3:0]
    _RV32_1(   0x110d39, 0x22   ),//reg_clkph_dq0            3       : [3:0]
    #endif

    _RV32_1(   0x110d3a, 0x00   ),//reg_clkph_cmd            0       : [3:0]
    _RV32_1(   0x110d3b, 0x00   ),//reg_clkph_cmd            0       : [3:0]
    #if(ENABLE_MEM1600MHz)
    _RV32_1(   0x110d3a, 0x20   ),
    _RV32_1(   0x110d3b, 0x20   ),
    #endif

    #if ((MIU_CONFIG == DDR3_MIU0_32_MIU1_16) || (MIU_CONFIG == DDR3_MIU0_32_MIU1_16_By_8BIT))
    #if(ENABLE_MEM1300MHz)
    _RV32_1(   0x110d48, 0x44   ),
    _RV32_1(   0x110d49, 0x00   ),
    #endif
    #if(ENABLE_MEM1600MHz)
    _RV32_1(   0x110d48, 0x66   ),
    _RV32_1(   0x110d49, 0x22   ),
    #endif
    #endif

    #if ((MIU_CONFIG == DDR3_MIU0_32_MIU1_16) || (MIU_CONFIG == DDR3_MIU0_32_MIU1_16_By_8BIT))
    #if(ENABLE_MEM1600MHz)
    _RV32_1(   0x110d4a, 0x20   ),
    _RV32_1(   0x110d4b, 0x20   ),
    #endif
    #if(ENABLE_MEM1300MHz)
    _RV32_1(   0x110d4a, 0x50   ),
    _RV32_1(   0x110d4b, 0x50   ),
    #endif
    #endif
    _RV32_1(   0x110d02, 0x00   ),//reg_cko_state        00  : [7:0]
    _RV32_1(   0x110d03, 0x00   ),//reg_cko_state        00  : [7:0]
    #if(ENABLE_MEM1600MHz)
    _RV32_1(   0x110d3c, 0x77   ),//reg_dqs_pre_state    30  : [7:0]
    #endif
    #if(ENABLE_MEM1300MHz)
    _RV32_1(   0x110d3c, 0x77   ),//reg_dqs_pre_state    30  : [7:0]
    #endif
    _RV32_1(   0x110d3d, 0x00   ),//reg_dqs_pre_state    30  : [7:0]
    #if ((MIU_CONFIG == DDR3_MIU0_32_MIU1_16) || (MIU_CONFIG == DDR3_MIU0_32_MIU1_16_By_8BIT))
    #if(ENABLE_MEM1600MHz)
    _RV32_1(   0x110d4c, 0x77   ),
    #endif
    #if(ENABLE_MEM1300MHz)
    _RV32_1(   0x110d4c, 0x77   ),
    #endif
    _RV32_1(   0x110d4d, 0x00   ),
    #endif

    #if(ENABLE_MEM1600MHz)
    _RV32_1(   0x110d5a, 0x33   ),
    _RV32_1(   0x110d5b, 0x33   ),
    _RV32_1(   0x110d5c, 0x33   ),
    _RV32_1(   0x110d5d, 0x33   ),
    _RV32_1(   0x110d5e, 0x33   ),
    _RV32_1(   0x110d5f, 0x33   ),
    #endif

    #if(ENABLE_MEM1300MHz)
    _RV32_1(   0x110d5a, 0x22   ),
    _RV32_1(   0x110d5b, 0x22   ),
    _RV32_1(   0x110d5c, 0x22   ),
    _RV32_1(   0x110d5d, 0x22   ),
    _RV32_1(   0x110d5e, 0x22   ),
    _RV32_1(   0x110d5f, 0x22   ),
    #endif
    _RV32_1(   0x110d3e, 0x00   ),//reg_oen_skew     2   : [2:0]
    _RV32_1(   0x110d3f, 0x00   ),//reg_oen_skew     2   : [2:0]
    _RV32_1(   0x110d0e, 0xe5   ),//0 :0 reg_en_mask
    _RV32_1(   0x110d0f, 0x00   ),//0 :0 reg_en_mask
    _RV32_1(   0x110d0e, 0xa5   ),//release rst sel
    _RV32_1(   0x110d0f, 0x00   ),//release rst sel
    #if(ENABLE_MEM1600MHz)
    _RV32_1(   0x110d6e, 0x77   ),//reg_dll0_ph      2   : [3:0]
    _RV32_1(   0x110d6f, 0x77   ),//reg_dll0_ph      2   : [3:0]
    #endif
    #if(ENABLE_MEM1300MHz)
    _RV32_1(   0x110d6e, 0x77   ),//reg_dll0_ph      2   : [3:0]
    _RV32_1(   0x110d6f, 0x77   ),//reg_dll0_ph      2   : [3:0]
    #endif
    _RV32_1(   0x110d6a, 0x20   ),//reg_dll1_code        f   : [9:0]
    _RV32_1(   0x110d6b, 0x00   ),//reg_dll1_code        f   : [9:0]
    _RV32_1(   0x110d68, 0x20   ),//reg_dll0_code        f   : [9:0]
    _RV32_1(   0x110d69, 0x00   ),//reg_dll0_code        f   : [9:0]
    _RV32_1(   0x110d54, 0x00   ),
    _RV32_1(   0x110d55, 0x00   ),
    #if(ENABLE_MEM1600MHz)
    _RV32_1(   0x110d72, 0x04   ),
    _RV32_1(   0x110d73, 0x48   ),
    #endif
    #if(ENABLE_MEM1300MHz)
    _RV32_1(   0x110d72, 0x05   ),
    _RV32_1(   0x110d73, 0x00   ),
    #endif

    //DLL calibration
    _RV32_1(   0x110d60, 0x0c   ),// sw rst
    _RV32_1(   0x110d61, 0x00   ),// sw rst
    _RV32_1(   0x110d60, 0x08   ),// sw rst
    _RV32_1(   0x110d61, 0x00   ),// sw rst
    _RV32_1(   0x110d62, 0x7f   ),// pulse width
    _RV32_1(   0x110d63, 0x00   ),// pulse width
    _RV32_1(   0x110d64, 0x00   ),// phase, code
    _RV32_1(   0x110d65, 0xf2   ),// phase, code
    #if(ENABLE_MEM1600MHz)
    _RV32_1(   0x110d60, 0x70   ),// enable hw, dyn, rd_avg
    #endif
    #if(ENABLE_MEM1300MHz)
    _RV32_1(   0x110d60, 0x70   ),// enable hw, dyn, rd_avg
    #endif
    _RV32_1(   0x110d61, 0x23   ),// enable hw, dyn, rd_avg

#elif ( MIU_INTERFACE == DDR2_INTERFACE_BGA)
    #error "Not any init setting for DDR2"
#else
    #error "MIU interface isn't defined"
#endif

    _END_OF_TBL32_,
    MIU_VER
};

const MS_REG_INIT MIU1_DDR_Init[] =
{
#if ( MIU_INTERFACE == DDR3_INTERFACE_BGA)
    _RV32_1(  0x100602, 0xa3  ),//reg_dram_type        10  : [1:0]   00 : sdr, 01 : ddr, 10 : ddr2, 11 : ddr3
    _RV32_1(  0x100603, 0x03  ),//reg_dram_type        10  : [1:0]   00 : sdr, 01 : ddr, 10 : ddr2, 11 : ddr3
    _RV32_1(  0x100604, 0x0a  ),//reg_rd_timing        9   : [4:0]
    _RV32_1(  0x100605, 0x00  ),//reg_rd_timing        9   : [4:0]
    #if(ENABLE_MEM1300MHz)
    _RV32_1(  0x100606, 0x50  ),//tREFRESH     2b  : [7:0] * 16
    _RV32_1(  0x100607, 0x04  ),//tREFRESH     2b  : [7:0] * 16
    _RV32_1(  0x100608, 0x99  ),//reg_tRCD     6   : [3:0]     11.25/1.875= 6
    _RV32_1(  0x100609, 0x18  ),//reg_tRCD     6   : [3:0]     11.25/1.875= 6
    _RV32_1(  0x10060a, 0x55  ),//reg_tRRD         4   : [3:0]     10/1.875= 6
    _RV32_1(  0x10060b, 0x22  ),//reg_tRRD         4   : [3:0]     10/1.875= 6
    _RV32_1(  0x10060c, 0xa8  ),//reg_tWL      5   : [3:0]     CAS latency -1
    _RV32_1(  0x10060d, 0xa5  ),//reg_tWL      5   : [3:0]     CAS latency -1
    _RV32_1(  0x10060e, 0x4a  ),//tRFC         2a  : [7:0]     127.5/1.875= 68
    _RV32_1(  0x10060f, 0x40  ),//tRFC         2a  : [7:0]     127.5/1.875= 68
    #endif
    #if(ENABLE_MEM1600MHz)
    _RV32_1(  0x100606, 0x60  ),//tREFRESH     2b  : [7:0] * 16
    _RV32_1(  0x100607, 0x04  ),//tREFRESH     2b  : [7:0] * 16
    _RV32_1(  0x100608, 0xbb  ),//reg_tRCD     6   : [3:0]     11.25/1.875= 6
    _RV32_1(  0x100609, 0x1c  ),//reg_tRCD     6   : [3:0]     11.25/1.875= 6
    _RV32_1(  0x10060a, 0xb6  ),//reg_tRRD         4   : [3:0]     10/1.875= 6
    _RV32_1(  0x10060b, 0x27  ),//reg_tRRD         4   : [3:0]     10/1.875= 6
    _RV32_1(  0x10060c, 0xc8  ),//reg_tWL      5   : [3:0]     CAS latency -1
    _RV32_1(  0x10060d, 0x96  ),//reg_tWL      5   : [3:0]     CAS latency -1
    _RV32_1(  0x10060e, 0x5a  ),//tRFC         2a  : [7:0]     127.5/1.875= 68
    _RV32_1(  0x10060f, 0x40  ),//tRFC         2a  : [7:0]     127.5/1.875= 68
    #endif
    _RV32_1(  0x100610, 0x70  ),//MR0              : [15:0]
    _RV32_1(  0x100611, 0x1c  ),//MR0              : [15:0]
    #if(ENABLE_MEM1600MHz)
    _RV32_1(  0x100612, 0x40  ),//MR1              : [15:0]    [6],[2] ODT on
    #endif
    #if(ENABLE_MEM1300MHz)
    _RV32_1(  0x100612, 0x40  ),//MR1              : [15:0]    [6],[2] ODT on
    #endif
    _RV32_1(  0x100613, 0x40  ),//MR1              : [15:0]    [6],[2] ODT on
    _RV32_1(  0x100614, 0x18  ),//MR2              : [15:0]
    _RV32_1(  0x100615, 0x80  ),//MR2              : [15:0]
    _RV32_1(  0x100616, 0x00  ),//MR3              : [15:0]
    _RV32_1(  0x100617, 0xc0  ),//MR3              : [15:0]
    #if(ENABLE_MEM1300MHz)
    _RV32_1(  0x100626, 0x00  ),
    _RV32_1(  0x100627, 0x00  ),
    _RV32_1(  0x100628, 0x92  ),
    _RV32_1(  0x100629, 0x24  ),
    _RV32_1(  0x10062c, 0x00  ),
    _RV32_1(  0x10062d, 0x00  ),
    #endif
    #if(ENABLE_MEM1600MHz)
    _RV32_1(  0x100626, 0x00  ),
    _RV32_1(  0x100627, 0x00  ),
    _RV32_1(  0x100628, 0x92  ),
    _RV32_1(  0x100629, 0x24  ),
    #endif


    _RV32_1(  0x110d80, 0x11  ),//reg_pkg_sel      1   : [0]
    #if(ENABLE_MEM1600MHz)
    _RV32_1(  0x110d80, 0x01  ),//reg_pkg_sel      1   : [0]
    _RV32_1(  0x110d81, 0x02  ),//reg_pkg_sel      1   : [0]
    #endif
    #if(ENABLE_MEM1300MHz)
    _RV32_1(  0x110d81, 0x02  ),//reg_pkg_sel      1   : [0]
    #endif
    _RV32_1(  0x110d84, 0x80  ),//reg_pkg_sel      1   : [0]
    _RV32_1(  0x110d85, 0x00  ),//reg_pkg_sel      1   : [0]
    #if(ENABLE_MEM1300MHz)
    _RV32_1(  0x110d90, 0x00  ),
    _RV32_1(  0x110d91, 0x04  ),
    #endif
    _RV32_1(  0x110db8, 0x44  ),//reg_clkph_dq0            3       : [3:0]
    _RV32_1(  0x110db9, 0x00  ),//reg_clkph_dq0            3       : [3:0]
    _RV32_1(  0x110dba, 0x00  ),//reg_clkph_cmd            0       : [3:0]
    _RV32_1(  0x110dbb, 0x00  ),//reg_clkph_cmd            0       : [3:0]
    _RV32_1(  0x110d82, 0x00  ),//reg_cko_state        00  : [7:0]
    _RV32_1(  0x110d83, 0x00  ),//reg_cko_state        00  : [7:0]
    #if(ENABLE_MEM1600MHz)
    _RV32_1(  0x110db6, 0x00  ),
    _RV32_1(  0x110db7, 0x40  ),
    _RV32_1(  0x110dbc, 0x77  ),//reg_dqs_pre_state    30  : [7:0]
    #endif
    #if(ENABLE_MEM1300MHz)
    _RV32_1(  0x110dbc, 0x77  ),//reg_dqs_pre_state    30  : [7:0]
    #endif
    _RV32_1(  0x110dbd, 0x00  ),//reg_dqs_pre_state    30  : [7:0]
    _RV32_1(  0x110dbe, 0x00  ),//reg_oen_skew     2   : [2:0]
    _RV32_1(  0x110dbf, 0x00  ),//reg_oen_skew     2   : [2:0]

    #if(ENABLE_MEM1600MHz)
    _RV32_1(  0x110ddc, 0x22  ),
    _RV32_1(  0x110ddd, 0x22  ),
    _RV32_1(  0x110dde, 0x22  ),
    _RV32_1(  0x110ddf, 0x22  ),
    #endif
    #if(ENABLE_MEM1300MHz)
    _RV32_1(  0x110dda, 0x00  ),
    _RV32_1(  0x110ddb, 0x00  ),
    _RV32_1(  0x110ddc, 0x55  ),
    _RV32_1(  0x110ddd, 0x55  ),
    _RV32_1(  0x110dde, 0x55  ),
    _RV32_1(  0x110ddf, 0x55  ),
    #endif
    _RV32_1(  0x110d8e, 0xe5  ),//0 :0 reg_en_mask
    _RV32_1(  0x110d8f, 0x00  ),//0 :0 reg_en_mask
    _RV32_1(  0x110d8e, 0xa5  ),//release rst sel
    _RV32_1(  0x110d8f, 0x00  ),//release rst sel
    #if(ENABLE_MEM1600MHz)
    _RV32_1(  0x110dee, 0x77  ),//reg_dll0_ph      2   : [3:0]
    #endif
    #if(ENABLE_MEM1300MHz)
    _RV32_1(  0x110dee, 0x77  ),//reg_dll0_ph      2   : [3:0]
    #endif
    _RV32_1(  0x110def, 0x00  ),//reg_dll0_ph      2   : [3:0]
    _RV32_1(  0x110dea, 0x20  ),//reg_dll1_code        f   : [9:0]
    _RV32_1(  0x110deb, 0x00  ),//reg_dll1_code        f   : [9:0]
    _RV32_1(  0x110de8, 0x20  ),//reg_dll0_code        f   : [9:0]
    _RV32_1(  0x110de9, 0x00  ),//reg_dll0_code        f   : [9:0]
    _RV32_1(  0x110dd4, 0x00  ),
    _RV32_1(  0x110dd5, 0x00  ),
    #if(ENABLE_MEM1600MHz)
    _RV32_1(  0x110df2, 0x05  ),
    _RV32_1(  0x110df3, 0x58  ),
    #endif
    #if(ENABLE_MEM1300MHz)
    _RV32_1(  0x110df2, 0x05  ),
    _RV32_1(  0x110df3, 0x00  ),
    #endif

    //DLL calibration
    _RV32_1(  0x110de0, 0x0c  ),// sw rst
    _RV32_1(  0x110de1, 0x00  ),// sw rst
    _RV32_1(  0x110de0, 0x08  ),// sw rst
    _RV32_1(  0x110de1, 0x00  ),// sw rst
    _RV32_1(  0x110de2, 0x7f  ),// pulse width
    _RV32_1(  0x110de3, 0x00  ),// pulse width
    _RV32_1(  0x110de4, 0x00  ),// phase, code
    _RV32_1(  0x110de5, 0xf2  ),// phase, code
    #if(ENABLE_MEM1600MHz)
    _RV32_1(  0x110de0, 0x70  ),// enable hw, dyn, rd_avg
    #endif
    #if(ENABLE_MEM1300MHz)
    _RV32_1(  0x110de0, 0x70  ),// enable hw, dyn, rd_avg
    #endif
    _RV32_1(  0x110de1, 0x23  ),// enable hw, dyn, rd_avg
#elif ( MIU_INTERFACE == DDR2_INTERFACE_BGA)
    #error "Not any init setting for DDR2"
#else
    #error "MIU interface isn't defined"
#endif

    _END_OF_TBL32_,
};

#endif /* !__ASSEMBLER__ */
#endif /* __DDR2_16_INIT_H__ */
