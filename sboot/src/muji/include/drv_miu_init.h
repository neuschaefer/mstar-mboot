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

#ifndef _DRV_MIU_INIT_H_
#define _DRV_MIU_INIT_H_

#ifndef _BOARD_H_
#include "Board.h"
#endif

#ifndef _C_RIUBASE_H_
#include "c_riubase.h"
#endif

#define MIU_VER                         'M','I','U','_','M','A','D','I','S','O','N',' ','V','e','r',':','1','_','0','_','0'
#define REG_ADDR_BASE                   0x1f000000

#ifndef __ASSEMBLER__

#ifndef __DRV_RIU_H__
#include "drvRIU.h"
#endif

#ifndef _MIU_FPGA_MUJI_H_
#include "MIU_FPGA_MUJI.h"
#endif


const MS_REG_INIT MIU_PreInit[] =
{
//  _RV32_2(0x113BEC, 0x8000),  //enable dramobf

#if !defined(CONFIG_MIU0_DRAM_NONE)
    //MIU0 Software reset
    _RV32_2(0x10121e, 0x0c00),  
    _RV32_2(0x10121e, 0x0c00),
    _RV32_2(0x10121e, 0x0c00),  
    _RV32_2(0x10121e, 0x0c01),  
    _RV32_2(0x10121e, 0x0c00),  

    //MIU0 Request mask
    _RV32_2(0x101246, 0xFFFE),  
    _RV32_2(0x101266, 0xFFFF),  
    _RV32_2(0x101286, 0xFFFF),  
    _RV32_2(0x1012A6, 0xFFFF),
    _RV32_2(0x161506, 0xFFFF),
    _RV32_2(0x161526, 0xFFFF),
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    //MIU1 Software reset
    _RV32_2(0x10061e, 0x0000),  
    _RV32_2(0x10061e, 0x0000),
    _RV32_2(0x10061e, 0x0000),
    _RV32_2(0x10061e, 0x0c01),
    _RV32_2(0x10061e, 0x0c00),

    //MIU1 Request mask
    _RV32_2(0x100646, 0xFFFE),  
    _RV32_2(0x100666, 0xFFFF),  
    _RV32_2(0x100686, 0xFFFF),  
    _RV32_2(0x1006A6, 0xFFFF),  
    _RV32_2(0x162206, 0xFFFF),  
    _RV32_2(0x162226, 0xFFFF),
#endif

#if !defined(CONFIG_MIU2_DRAM_NONE)
    //MIU2 Software reset
    _RV32_2(0x16201e, 0x0000),
    _RV32_2(0x16201e, 0x0000),
    _RV32_2(0x16201e, 0x0000),
    _RV32_2(0x16201e, 0x0c01),
    _RV32_2(0x16201e, 0x0c00),

    //MIU2 Request mask
    _RV32_2(0x162046, 0xFFFE),  
    _RV32_2(0x162066, 0xFFFF),
    _RV32_2(0x162086, 0xFFFF),
    _RV32_2(0x1620A6, 0xFFFF),
    _RV32_2(0x162306, 0xFFFF),
    _RV32_2(0x162326, 0xFFFF),
#endif
    _END_OF_TBL32_,
    MIU_VER
};

const MS_REG_INIT MIU_PostInit[] =
{
#if !defined(CONFIG_MIU0_DRAM_NONE)
    _RV32_2(0x1012e0, 0x0000),  //stop bist test

    //open all MIU0 request mask (All IP can access MIU resource)
    _RV32_2(0x101246, 0x0000),  //Mask MIU0_group_0
    _RV32_2(0x101266, 0x0000),  //Mask MIU0_group_1
    _RV32_2(0x101286, 0x0000),  //Mask MIU0_group_2
    _RV32_2(0x1012a6, 0x0000),  //Mask MIU0_group_3
    _RV32_2(0x161506, 0x0000),  //Mask MIU0_group_4
    _RV32_2(0x161526, 0x0000),  //Mask MIU0_group_5    
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    //open all MIU1 request mask (All IP can access MIU resource)
    _RV32_2(0x100646, 0x0000),  //Mask MIU1_group_0
    _RV32_2(0x100666, 0x0000),  //Mask MIU1_group_1
    _RV32_2(0x100686, 0x0000),  //Mask MIU1_group_2
    _RV32_2(0x1006a6, 0x0000),  //Mask MIU1_group_3
    _RV32_2(0x162206, 0x0000),  //Mask MIU1_group_4
    _RV32_2(0x162226, 0x0000),  //Mask MIU1_group_5

    //all IP choose sw select( not IP select )
    _RV32_2(0x1006f0, 0x0000),  
    _RV32_2(0x1006f2, 0x0000),  
    _RV32_2(0x1006f4, 0x0000),  
    _RV32_2(0x1006f6, 0x0000),  
    _RV32_2(0x1006f8, 0x0000),  
    _RV32_2(0x1006fa, 0x0000),  
#endif

#if !defined(CONFIG_MIU2_DRAM_NONE)
    //open all MIU2 request mask (All IP can access MIU resource)
    _RV32_2(0x162046, 0x0000),  //Mask MIU2_group_0
    _RV32_2(0x162066, 0x0000),  //Mask MIU2_group_1
    _RV32_2(0x162086, 0x0000),  //Mask MIU2_group_2
    _RV32_2(0x1620a6, 0x0000),  //Mask MIU2_group_3
    _RV32_2(0x162306, 0x0000),  //Mask MIU2_group_4
    _RV32_2(0x162326, 0x0000),  //Mask MIU2_group_5
#endif

    _RV32_2(0x10121e, 0x0c08),  //SW initial done and turn on arbitor

    _END_OF_TBL32_,
    MIU_VER
};

#endif /* !__ASSEMBLER__ */

#endif /* _DRV_MIU_INIT_H_ */
