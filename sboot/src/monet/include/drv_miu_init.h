//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2014 MStar Semiconductor, Inc. All rights reserved.
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

#define MIU_VER                         'M','I','U','_','M','O','N','E','T',' ','V','e','r',':','1','_','0','_','0'
#define REG_ADDR_BASE                   0x1f000000

#ifndef __ASSEMBLER__

#ifndef __DRV_RIU_H__
#include "drvRIU.h"
#endif

#ifndef _MIU_FPGA_MONET_H_
#include "MIU_FPGA_MONET.h"
#endif

#ifndef _MIU_MST176A_D01A_S_MONET_H_
#include "MIU_MST176A_D01A_S_MONET.h"
#endif

const MS_REG_INIT MIU_PreInit[] =
{
//  _RV32_2(0x113BEC, 0x8000),  //enable dramobf

#if !defined(CONFIG_MIU0_DRAM_NONE)
//MIU0 Software reset and mask
    _RV32_2(0x10121e, 0x0c00),
    _RV32_2(0x10121e, 0x0c00),
    _RV32_2(0x10121e, 0x0c00),
    _RV32_2(0x10121e, 0x0c01),
    _RV32_2(0x10121e, 0x0c00),
    _RV32_2(0x101246, 0xfffe),
    _RV32_2(0x101266, 0xffff),
    _RV32_2(0x101286, 0xffff),
    _RV32_2(0x1012a6, 0xffff),
    _RV32_2(0x161506, 0xffff),
    _RV32_2(0x161526, 0xffff),
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
//MIU1 Software reset and mask
    _RV32_2(0x10061e, 0x0000),
    _RV32_2(0x10061e, 0x0000),
    _RV32_2(0x10061e, 0x0000),
    _RV32_2(0x10061e, 0x0c01),
    _RV32_2(0x10061e, 0x0c00),
    _RV32_2(0x100646, 0xfffe),
    _RV32_2(0x100666, 0xffff),
    _RV32_2(0x100686, 0xffff),
    _RV32_2(0x1006a6, 0xffff),
    _RV32_2(0x162206, 0xffff),
    _RV32_2(0x162226, 0xffff),
#endif

    _END_OF_TBL32_,
    MIU_VER
};

const MS_REG_INIT MIU_PostInit[] =
{
#if !defined(CONFIG_MIU0_DRAM_NONE)
    _RV32_2(0x101246, 0x0000),
    _RV32_2(0x101266, 0x0000),
    _RV32_2(0x101286, 0x0000),
    _RV32_2(0x1012a6, 0x0000),
    _RV32_2(0x161506, 0x0000),
    _RV32_2(0x161526, 0x0000),
    _RV32_2(0x10121e, 0x0c08),
#endif

#if !defined(CONFIG_MIU1_DRAM_NONE)
    _RV32_2(0x100646, 0x0000),
    _RV32_2(0x100666, 0x0000),
    _RV32_2(0x100686, 0x0000),
    _RV32_2(0x1006a6, 0x0000),
    _RV32_2(0x162206, 0x0000),
    _RV32_2(0x162226, 0x0000),
#endif

//  _RV32_2(0x101842, 0x0000),  //Set MIU0 Size of MAU0
//  _RV32_2(0x101862, 0x0000),  //Set MIU0 Size of MAU1

    _END_OF_TBL32_,
    MIU_VER
};

#endif /* !__ASSEMBLER__ */

#endif /* _DRV_MIU_INIT_H_ */
