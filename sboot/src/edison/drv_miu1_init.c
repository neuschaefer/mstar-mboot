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
#include "datatype.h"
#include "drvRIU_ram.h"
#include "hwreg_EDISON.h"

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

#ifndef __MIU_INIT_BD_MST159A_D01A_S_H__
#include "MIU1_INIT_BD_MST159A_D01A_S.h"
#endif

#ifndef __MIU_INIT_BD_MST147A_D01B_S_H__
#include "MIU1_INIT_BD_MST147A_D01B_S.h"
#endif

#ifndef __MIU_INIT_BD_MST036B_EDISON_H__
#include "MIU1_INIT_BD_MST036B_EDISON.h"
#endif

#ifndef __MIU_INIT_BD_MST036B_EDISON_CUS36_H__
#include "MIU1_INIT_BD_MST036B_EDISON_CUS36.h"
#endif

#ifndef __MIU_INIT_BD_MST036B_EDISON_CUS28_H__
#include "MIU1_INIT_BD_MST036B_EDISON_CUS28.h"
#endif

#ifndef __MIU_INIT_BD_MST036B_EDISON_CUS28_AP_H__
#include "MIU1_INIT_BD_MST036B_EDISON_CUS28_AP.h"
#endif

#ifndef __MIU_INIT_BD_MST036B_EDISON_CUS36_AP_H__
#include "MIU1_INIT_BD_MST036B_EDISON_CUS36_AP.h"
#endif

#ifndef __MIU_INIT_BD_MST036B_EDISON_CUS18_ATSC_H__
#include "MIU1_INIT_BD_MST036B_EDISON_CUS18_ATSC.h"
#endif

#ifndef __MIU_INIT_BD_MST036B_EDISON_CUS19_H__
#include "MIU1_INIT_BD_MST036B_EDISON_CUS19.h"
#endif

#endif /* !__ASSEMBLER__ */
#endif /* __DDR3_16_INIT_H__ */
