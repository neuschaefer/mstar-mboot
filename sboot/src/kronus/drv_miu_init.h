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

#define  MIU_VER  'M','I','U','_','U','4',' ',' ','V','e','r',':','1','_','1','_','0'
#define  REG_ADDR_BASE      0xbf000000


#define  MEMCLK_DEFAULT      0
#define  MEMCLK_1066MHZ      1
#define  MEMCLK_1300MHZ      2
#define  MEMCLK_800MHZ       3


#define  MEMPLL_SEL         MEMCLK_DEFAULT   //DDR3:1300Mhz; DDr2:1066Mhz



#define    _DRAM_SIZE_NO_LIMIT    0x00
#define    _DRAM_SIZE_2M          0x01
#define    _DRAM_SIZE_4M          0x02
#define    _DRAM_SIZE_8M          0x03
#define    _DRAM_SIZE_16M         0x04
#define    _DRAM_SIZE_32M         0x05
#define    _DRAM_SIZE_64M         0x06
#define    _DRAM_SIZE_128M        0x07
#define    _DRAM_SIZE_256M        0x08

#define    _DRAM_ON_BAORD         _DRAM_SIZE_NO_LIMIT

// A CMD + B DATA
#define MIU0_USE_MIU1_DATA (!CHIP_HAS_DDR_A_DATA && !CHIP_HAS_DDR_B_CMD)

#if (MIU_DRAM_LEN >= 0x10000000)
    #define DRAM_SIZE_SETTING   0x0000  // no limit
#elif (MIU_DRAM_LEN >= 0x8000000)
    #define DRAM_SIZE_SETTING   0x0700
#elif (MIU_DRAM_LEN >= 0x4000000)
    #define DRAM_SIZE_SETTING   0x0600
#elif (MIU_DRAM_LEN >= 0x2000000)
    #define DRAM_SIZE_SETTING   0x0500
#else
    #define DRAM_SIZE_SETTING   0x0400
#endif


#ifndef __ASSEMBLER__

#include "drvRIU.h"


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

#if ( MIU_INTERFACE == DDR2_INTERFACE_QFP)
    #include "004_MIU_init_ddr2_1066_216Pin.h"
#elif ( MIU_INTERFACE == DDR3_INTERFACE_QFP)
    #include "004_MIU_init_ddr3_216LQ.h"
#elif ( MIU_INTERFACE == DDR2_INTERFACE_QFP_128)
    #include "004_MIU_init_ddr2_1066_128Pin.h"
#elif ( MIU_INTERFACE == DDR3_INTERFACE_QFP_128)
    #include "004_MIU_init_ddr3_128LQ.h"
#elif ( MIU_INTERFACE == DDR3_INTERFACE_QFP_8BIT_MODE)
    #include "004_MIU_init_ddr3_8bit_216LQ.h"
#elif ( MIU_INTERFACE == DDR3_INTERFACE_QFP_156)
    #include "004_MIU_init_ddr3_156LQ.h"
#elif ( MIU_INTERFACE == DDR3_INTERFACE_QFP_156_8BIT_MODE)
	#include "004_MIU_init_ddr3_8bit_156LQ.h"
#elif ( MIU_INTERFACE == DDR2_INTERFACE_BGA)
    #include "004_MIU_init_ddr2_BGA.h"
#elif ( MIU_INTERFACE == DDR3_INTERFACE_BGA)
    #include "004_MIU_init_ddr3_BGA.h"
#else
#error DDR type not defined
#endif
    _END_OF_TBL32_,
    MIU_VER
};
//--------------------------------------------------
//--------------------------------------------------
const MS_REG_INIT MIU1_DDR_Init[] =
{

    _END_OF_TBL32_,
};





#endif /* !__ASSEMBLER__ */


#endif /* __DDR2_16_INIT_H__ */
