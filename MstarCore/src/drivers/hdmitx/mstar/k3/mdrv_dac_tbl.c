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
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
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
////////////////////////////////////////////////////////////////////////////////

//****************************************************
// DAC Drive Chip           : Kaiser_DAC_Driver
// DAC Excel CodeGen Version: 1.09
// DAC Excel SW      Version: 1.06
// DAC Excel update date    : 2013/12/16 21:27
//****************************************************

#ifndef _DRVDAC_TBL_C_
#define _DRVDAC_TBL_C_

#include "MsCommon.h"
#include "mdrv_dac_tbl.h"

//****************************************************
// INIT  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x1C, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_L), 0x0C, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_H), 0x1C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_5A_L), 0x1C, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_GPIO_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_INIT_GPIO_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_L), 0x00, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_H), 0x00, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_SC  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0xE9/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0xEE/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0xDF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0xDF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x59/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x3D/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_MOD_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_INIT_MOD_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_L), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_H), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDGEN  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_HDGEN_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_INIT_HDGEN_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_L), 0xFF, 0x43/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_05_L), 0xFF, 0x46/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_05_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_06_L), 0xFF, 0x56/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_06_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_L), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_L), 0xFF, 0x8c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_L), 0xFF, 0x59/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_L), 0xFF, 0x3f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_L), 0xFF, 0xc0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_H), 0xFF, 0x0f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_L), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_L), 0xFF, 0x11/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_L), 0xFF, 0xda/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_L), 0xFF, 0xc0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_H), 0xFF, 0x0f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_L), 0xFF, 0x11/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_L), 0xFF, 0x7e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_L), 0xFF, 0x6e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_L), 0xFF, 0x2c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_L), 0xFF, 0x16/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_L), 0xFF, 0xd4/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_L), 0xFF, 0x9a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_L), 0xFF, 0x3e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_L), 0xFF, 0x3e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_L), 0xFF, 0x3e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_L), 0xFF, 0x3e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_L), 0xFF, 0x3e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_L), 0xFF, 0x3e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_L), 0xFF, 0x3e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_L), 0xFF, 0x3e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_L), 0xFF, 0x6b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_L), 0xFF, 0x16/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_L), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_L), 0xFF, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_L), 0xFF, 0x1a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_L), 0xFF, 0x28/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_L), 0xFF, 0xfa/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_L), 0xFF, 0x2e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_L), 0xFF, 0x1e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_L), 0xFF, 0xd4/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_L), 0xFF, 0x2d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_L), 0xFF, 0xa7/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_L), 0xFF, 0xa7/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_L), 0xFF, 0x11/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_L), 0xFF, 0x85/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_L), 0xFF, 0x4a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_L), 0xFF, 0x23/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_L), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_L), 0xFF, 0x7e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_L), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_L), 0xFF, 0x4b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_L), 0xFF, 0x63/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_L), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_L), 0xFF, 0x8c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_L), 0xFF, 0x1d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_L), 0xFF, 0xd0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_L), 0xFF, 0xd0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDMITX_8BIT  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x6C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x26/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x09/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x68/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// SC1_INIT  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_SC1_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_SC1_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_6C_H), 0x0C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// SC1_INIT_SC  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_SC1_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_SC1_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_H), 0xFF, 0xCC/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_L), 0xFF, 0xFD/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_L), 0xFF, 0xFF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_L), 0xFF, 0xEF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_L), 0xFF, 0xEF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_L), 0xFF, 0x59/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_01_L), 0xFF, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_SVOP_BK8F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_L), 0xFF, 0x09/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_L), 0xFF, 0x0B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x1C, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_L), 0x0C, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_H), 0x1C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_5A_L), 0x1C, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_GPIO_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_GPIO_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_L), 0x00, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_H), 0x00, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_SC  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0xE9/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0xEE/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0xDF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0xDF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x59/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x3D/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_MOD_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_MOD_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_L), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_H), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDGEN  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_HDGEN_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_HDGEN_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_L), 0xFF, 0x54/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_L), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_L), 0xFF, 0x0f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_L), 0xFF, 0x0c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_L), 0xFF, 0x59/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_L), 0xFF, 0x1a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_L), 0xFF, 0x0a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_L), 0xFF, 0x3e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_L), 0xFF, 0x6e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_L), 0xFF, 0x2c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_L), 0xFF, 0x16/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_L), 0xFF, 0xd4/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_L), 0xFF, 0x9a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_L), 0xFF, 0x6b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_L), 0xFF, 0x16/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_L), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_L), 0xFF, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_L), 0xFF, 0x1a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_L), 0xFF, 0x28/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_L), 0xFF, 0xfa/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_L), 0xFF, 0x2e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_L), 0xFF, 0x1e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_L), 0xFF, 0xd4/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_L), 0xFF, 0x2d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_L), 0xFF, 0xa7/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_L), 0xFF, 0xa7/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_L), 0xFF, 0x11/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_L), 0xFF, 0x85/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_L), 0xFF, 0x4a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_L), 0xFF, 0x23/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_L), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_L), 0xFF, 0x7e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_L), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_L), 0xFF, 0x4b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_L), 0xFF, 0x63/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_L), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_L), 0xFF, 0x8c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_L), 0xFF, 0x1d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_L), 0xFF, 0xd0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_L), 0xFF, 0xd0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDMITX_8BIT  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x6C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x26/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x09/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x68/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// SC1_INIT  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_SC1_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_SC1_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_6C_H), 0x0C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// SC1_INIT_SC  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_SC1_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_SC1_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_H), 0xFF, 0xCC/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_L), 0xFF, 0xFD/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_L), 0xFF, 0xFF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_L), 0xFF, 0xEF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_L), 0xFF, 0xEF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_L), 0xFF, 0x59/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_01_L), 0xFF, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_SVOP_BK8F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_L), 0xFF, 0x09/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_L), 0xFF, 0x0B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x1C, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_L), 0x0C, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_H), 0x1C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_5A_L), 0x1C, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_GPIO_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_GPIO_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_L), 0x00, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_H), 0x00, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_SC  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0x70/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x5F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x84/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x84/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_MOD_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_MOD_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_L), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_H), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDGEN  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_HDGEN_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_HDGEN_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_L), 0xFF, 0x4b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_05_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_05_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_06_L), 0xFF, 0x52/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_06_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_L), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_L), 0xFF, 0x8d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_L), 0xFF, 0x5f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_L), 0xFF, 0x3f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_L), 0xFF, 0xe0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_L), 0xFF, 0x6a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_L), 0xFF, 0x0e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_L), 0xFF, 0xe0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_L), 0xFF, 0xe0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_L), 0xFF, 0x69/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_L), 0xFF, 0x0e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_L), 0xFF, 0x7e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_L), 0xFF, 0x6e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_L), 0xFF, 0x2c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_L), 0xFF, 0x16/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_L), 0xFF, 0xd4/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_L), 0xFF, 0x9a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_L), 0xFF, 0x6a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_L), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_L), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_L), 0xFF, 0x16/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_L), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_L), 0xFF, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_L), 0xFF, 0x1a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_L), 0xFF, 0x28/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_L), 0xFF, 0xfa/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_L), 0xFF, 0x2e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_L), 0xFF, 0x1e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_L), 0xFF, 0xd4/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_L), 0xFF, 0x2d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_L), 0xFF, 0xa7/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_L), 0xFF, 0xa7/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_L), 0xFF, 0x11/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_L), 0xFF, 0x85/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_L), 0xFF, 0x4a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_L), 0xFF, 0x23/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_L), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_L), 0xFF, 0x7e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_L), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_L), 0xFF, 0x4b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_L), 0xFF, 0x63/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_L), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_L), 0xFF, 0x8c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_L), 0xFF, 0x1d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_L), 0xFF, 0xd0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_L), 0xFF, 0xd0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDMITX_8BIT  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x6C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x26/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x09/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x68/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// SC1_INIT  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_SC1_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_SC1_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_6C_H), 0x0C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// SC1_INIT_SC  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_SC1_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_SC1_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_H), 0xFF, 0xCC/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_L), 0xFF, 0x21/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_L), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_L), 0xFF, 0x1F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_L), 0xFF, 0x1F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_L), 0xFF, 0x5F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_01_L), 0xFF, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_L), 0xFF, 0x84/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_L), 0xFF, 0x84/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_SVOP_BK8F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x1C, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_L), 0x0C, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_H), 0x1C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_5A_L), 0x1C, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_GPIO_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_GPIO_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_L), 0x00, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_H), 0x00, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_SC  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0x70/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x5F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x3D/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x84/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x84/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_MOD_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_MOD_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_L), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_H), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDGEN  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_HDGEN_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_HDGEN_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_L), 0xFF, 0x5f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_L), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_L), 0xFF, 0x0f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_L), 0xFF, 0x0c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_L), 0xFF, 0x5f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_L), 0xFF, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_L), 0xFF, 0x70/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_L), 0xFF, 0x3e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_L), 0xFF, 0x6e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_L), 0xFF, 0x2c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_L), 0xFF, 0x16/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_L), 0xFF, 0xd4/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_L), 0xFF, 0x9a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_L), 0xFF, 0x4f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_L), 0xFF, 0x4f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_L), 0xFF, 0x4f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_L), 0xFF, 0x4f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_L), 0xFF, 0x4f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_L), 0xFF, 0x4f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_L), 0xFF, 0x4f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_L), 0xFF, 0x4f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_L), 0xFF, 0x6b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_L), 0xFF, 0x16/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_L), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_L), 0xFF, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_L), 0xFF, 0x1a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_L), 0xFF, 0x28/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_L), 0xFF, 0xfa/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_L), 0xFF, 0x2e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_L), 0xFF, 0x1e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_L), 0xFF, 0xd4/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_L), 0xFF, 0x2d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_L), 0xFF, 0xa7/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_L), 0xFF, 0xa7/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_L), 0xFF, 0x11/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_L), 0xFF, 0x85/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_L), 0xFF, 0x4a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_L), 0xFF, 0x23/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_L), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_L), 0xFF, 0x7e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_L), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_L), 0xFF, 0x4b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_L), 0xFF, 0x63/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_L), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_L), 0xFF, 0x8c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_L), 0xFF, 0x1d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_L), 0xFF, 0xd0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_L), 0xFF, 0xd0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDMITX_8BIT  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x6C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x26/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x09/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x68/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// SC1_INIT  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_SC1_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_SC1_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_6C_H), 0x0C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// SC1_INIT_SC  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_SC1_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_SC1_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_H), 0xFF, 0xCC/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_L), 0xFF, 0x21/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_L), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_L), 0xFF, 0x1F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_L), 0xFF, 0x1F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_L), 0xFF, 0x5F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_01_L), 0xFF, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_L), 0xFF, 0x84/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_L), 0xFF, 0x84/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_SVOP_BK8F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x1C, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_L), 0x0C, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_H), 0x1C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_5A_L), 0x1C, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_GPIO_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_GPIO_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_L), 0x00, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_H), 0x00, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_SC  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0xED/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0xD5/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0xD9/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0xCF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0xCF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0xBB/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x0F, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x0F, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_MOD_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_MOD_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_L), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_H), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDGEN  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_HDGEN_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_HDGEN_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_L), 0xFF, 0x89/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_H), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_L), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_L), 0xFF, 0x0f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_L), 0xFF, 0x4c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_L), 0xFF, 0xbb/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_H), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_L), 0xFF, 0x2c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_H), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_L), 0xFF, 0x2c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_L), 0xFF, 0xec/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_L), 0xFF, 0x29/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_H), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_L), 0xFF, 0x4f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_H), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_L), 0xFF, 0x4f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_L), 0xFF, 0x6e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_L), 0xFF, 0x2c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_L), 0xFF, 0x16/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_L), 0xFF, 0xd4/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_L), 0xFF, 0x9a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_L), 0xFF, 0x6b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_L), 0xFF, 0x56/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_L), 0xFF, 0x0d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_L), 0xFF, 0x0b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_L), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_L), 0xFF, 0x28/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_L), 0xFF, 0x87/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_L), 0xFF, 0x87/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_L), 0xFF, 0x1d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_L), 0xFF, 0x3a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_L), 0xFF, 0x1d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_L), 0xFF, 0x51/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_L), 0xFF, 0x4f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_L), 0xFF, 0x5e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_L), 0xFF, 0x5c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_L), 0xFF, 0xdc/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_L), 0xFF, 0xdc/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_L), 0xFF, 0x5c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDMITX_8BIT  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0xBE/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0xED/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x23/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// SC1_INIT  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_SC1_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_SC1_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_6C_H), 0x0C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// SC1_INIT_SC  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_SC1_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_SC1_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_H), 0xFF, 0xCC/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_L), 0xFF, 0x21/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_L), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_L), 0xFF, 0x1F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_L), 0xFF, 0x1F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_L), 0xFF, 0x5F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_01_L), 0xFF, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_L), 0xFF, 0x84/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_L), 0xFF, 0x84/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_SVOP_BK8F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x1C, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_L), 0x0C, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_H), 0x1C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_5A_L), 0x1C, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_GPIO_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_GPIO_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_L), 0x00, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_H), 0x00, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_SC  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0xED/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0xD5/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0xD9/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0xCF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0xCF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x0F, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x0F, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x0F, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_MOD_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_MOD_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_L), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_H), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDGEN  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_HDGEN_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_HDGEN_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_L), 0xFF, 0x41/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_L), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_L), 0xFF, 0x0f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_L), 0xFF, 0x4c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_L), 0xFF, 0x2c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_H), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_L), 0xFF, 0x2c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_L), 0xFF, 0xec/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_L), 0xFF, 0x29/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_H), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_L), 0xFF, 0x4f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_H), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_L), 0xFF, 0x4f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_L), 0xFF, 0x6e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_L), 0xFF, 0x2c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_L), 0xFF, 0x16/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_L), 0xFF, 0xd4/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_L), 0xFF, 0x9a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_L), 0xFF, 0x6b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_L), 0xFF, 0x56/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_L), 0xFF, 0x0d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_L), 0xFF, 0x0b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_L), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_L), 0xFF, 0x28/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_L), 0xFF, 0x87/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_L), 0xFF, 0x87/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_L), 0xFF, 0x1d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_L), 0xFF, 0x3a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_L), 0xFF, 0x1d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_L), 0xFF, 0x51/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_L), 0xFF, 0x4f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_L), 0xFF, 0x5e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_L), 0xFF, 0x5c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_L), 0xFF, 0xdc/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_L), 0xFF, 0xdc/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_L), 0xFF, 0x5c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDMITX_8BIT  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0xBE/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0xED/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x23/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// SC1_INIT  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_SC1_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_SC1_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_6C_H), 0x0C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// SC1_INIT_SC  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_SC1_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_SC1_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_H), 0xFF, 0xCC/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_L), 0xFF, 0xFD/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_L), 0xFF, 0xFF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_L), 0xFF, 0xEF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_L), 0xFF, 0xEF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_L), 0xFF, 0x59/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_01_L), 0xFF, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_SVOP_BK8F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_L), 0xFF, 0x09/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_L), 0xFF, 0x0B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x1C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_L), 0x0C, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_H), 0x1C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_5A_L), 0x1C, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_GPIO_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_GPIO_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_L), 0x00, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_H), 0x00, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_SC  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x4F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x0F, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x2B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_MOD_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_MOD_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_L), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_H), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDGEN  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_HDGEN_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_HDGEN_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_L), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_L), 0xFF, 0x8a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_H), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_05_L), 0xFF, 0xE6/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_05_H), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_06_L), 0xFF, 0xF6/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_06_H), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_L), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_L), 0xFF, 0xcc/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_H), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_L), 0xFF, 0xfe/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_H), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_L), 0xFF, 0x63/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_L), 0xFF, 0x0b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_L), 0xFF, 0xaf/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_H), 0xFF, 0x70/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_L), 0xFF, 0x1f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_L), 0xFF, 0xff/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_L), 0xFF, 0x63/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_L), 0xFF, 0x0b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_H), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_H), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_L), 0xFF, 0x6e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_L), 0xFF, 0x2c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_L), 0xFF, 0x16/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_L), 0xFF, 0xd4/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_L), 0xFF, 0x9a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_L), 0xFF, 0xa0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_L), 0xFF, 0x6b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_L), 0xFF, 0x56/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_L), 0xFF, 0x0d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_L), 0xFF, 0x0b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_L), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_L), 0xFF, 0x28/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_L), 0xFF, 0x87/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_L), 0xFF, 0x87/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_L), 0xFF, 0x1d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_L), 0xFF, 0x3a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_L), 0xFF, 0x1d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_L), 0xFF, 0x51/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_L), 0xFF, 0x4f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_L), 0xFF, 0x5e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_L), 0xFF, 0x5c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_L), 0xFF, 0xdc/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_L), 0xFF, 0xdc/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_L), 0xFF, 0x5c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDMITX_8BIT  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0xBE/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0xED/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x23/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// SC1_INIT  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_SC1_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_SC1_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_6C_H), 0x0C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// SC1_INIT_SC  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_SC1_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_SC1_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_H), 0xFF, 0xCC/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_L), 0xFF, 0x21/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_L), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_L), 0xFF, 0x1F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_L), 0xFF, 0x1F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_L), 0xFF, 0x5F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_01_L), 0xFF, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_L), 0xFF, 0x84/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_L), 0xFF, 0x84/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_SVOP_BK8F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x1C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_L), 0x0C, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_H), 0x1C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_5A_L), 0x1C, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_GPIO_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_GPIO_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_L), 0x00, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_H), 0x00, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_SC  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x97/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x2B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_MOD_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_MOD_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_L), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_H), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDGEN  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_HDGEN_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_HDGEN_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_L), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_L), 0xFF, 0x1a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_05_L), 0xFF, 0x76/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_05_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_06_L), 0xFF, 0x86/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_06_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_L), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_L), 0xFF, 0xcc/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_L), 0xFF, 0x4b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_L), 0xFF, 0xfe/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_H), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_L), 0xFF, 0x63/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_L), 0xFF, 0x0b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_L), 0xFF, 0xaf/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_H), 0xFF, 0x70/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_L), 0xFF, 0x1f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_L), 0xFF, 0xff/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_L), 0xFF, 0x63/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_L), 0xFF, 0x0b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_H), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_H), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_L), 0xFF, 0x6e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_L), 0xFF, 0x2c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_L), 0xFF, 0x16/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_L), 0xFF, 0xd4/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_L), 0xFF, 0x9a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_L), 0xFF, 0xa0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_L), 0xFF, 0x6b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_L), 0xFF, 0x56/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_L), 0xFF, 0x0d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_L), 0xFF, 0x0b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_L), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_L), 0xFF, 0x28/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_L), 0xFF, 0x87/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_L), 0xFF, 0x87/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_L), 0xFF, 0x1d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_L), 0xFF, 0x3a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_L), 0xFF, 0x1d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_L), 0xFF, 0x51/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_L), 0xFF, 0x4f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_L), 0xFF, 0x5e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_L), 0xFF, 0x5c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_L), 0xFF, 0xdc/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_L), 0xFF, 0xdc/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_L), 0xFF, 0x5c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDMITX_8BIT  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0xA6/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x46/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0xFC/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x87/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0xF4/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x23/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0xA7/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0xC6/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x4B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0xA6/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x46/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// SC1_INIT  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_SC1_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_SC1_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_6C_H), 0x0C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// SC1_INIT_SC  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_SC1_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_SC1_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_H), 0xFF, 0xCC/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_L), 0xFF, 0xFD/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_L), 0xFF, 0xFF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_L), 0xFF, 0xEF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_L), 0xFF, 0xEF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_L), 0xFF, 0x59/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_01_L), 0xFF, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_SVOP_BK8F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_L), 0xFF, 0x09/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_L), 0xFF, 0x0B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x1C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_L), 0x0C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_H), 0x1C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_5A_L), 0x1C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_GPIO_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_GPIO_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_L), 0x00, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_H), 0x00, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_SC  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x4F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x0F, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x2B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_MOD_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_MOD_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_L), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_H), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDGEN  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_HDGEN_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_HDGEN_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_L), 0xFF, 0x1a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_H), 0xFF, 0x0a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_L), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_L), 0xFF, 0x0f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_L), 0xFF, 0x4c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_L), 0xFF, 0x4f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_H), 0xFF, 0x0a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_L), 0xFF, 0xaf/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_H), 0xFF, 0x70/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_L), 0xFF, 0x6b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_H), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_L), 0xFF, 0x63/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_H), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_H), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_L), 0xFF, 0x6e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_L), 0xFF, 0x2c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_L), 0xFF, 0x16/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_L), 0xFF, 0xd4/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_L), 0xFF, 0x9a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_L), 0xFF, 0x6b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_L), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_L), 0xFF, 0x0a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_L), 0xFF, 0x1b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_L), 0xFF, 0x2f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_L), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_L), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_L), 0xFF, 0x39/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_L), 0xFF, 0x39/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_L), 0xFF, 0x0c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_L), 0xFF, 0x33/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_L), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_L), 0xFF, 0x69/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_L), 0xFF, 0xdc/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_L), 0xFF, 0x2e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_L), 0xFF, 0x23/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_L), 0xFF, 0xa3/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_L), 0xFF, 0xa3/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_L), 0xFF, 0x23/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_L), 0xFF, 0x11/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_L), 0xFF, 0x85/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_L), 0xFF, 0x4a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_L), 0xFF, 0x23/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_L), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_L), 0xFF, 0x7e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_L), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_L), 0xFF, 0x4b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_L), 0xFF, 0x63/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_L), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_L), 0xFF, 0x8c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_L), 0xFF, 0x1d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_L), 0xFF, 0xd0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_L), 0xFF, 0xd0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDMITX_8BIT  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0xBE/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0xED/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x70/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// SC1_INIT  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_SC1_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_SC1_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_6C_H), 0x0C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// SC1_INIT_SC  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_SC1_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_SC1_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_H), 0xFF, 0xCC/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_L), 0xFF, 0x21/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_L), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_L), 0xFF, 0x1F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_L), 0xFF, 0x1F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_L), 0xFF, 0x5F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_01_L), 0xFF, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_L), 0xFF, 0x84/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_L), 0xFF, 0x84/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_SVOP_BK8F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x1C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_L), 0x0C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_H), 0x1C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_5A_L), 0x1C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_GPIO_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_GPIO_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_L), 0x00, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_H), 0x00, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_SC  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x97/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x2B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_MOD_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_MOD_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_L), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_H), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDGEN  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_HDGEN_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_HDGEN_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_L), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_H), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_L), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_L), 0xFF, 0x0f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_L), 0xFF, 0x4c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_L), 0xFF, 0x97/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_H), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_L), 0xFF, 0xaf/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_H), 0xFF, 0x70/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_L), 0xFF, 0x6b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_H), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_L), 0xFF, 0x63/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_H), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_H), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_L), 0xFF, 0x6e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_L), 0xFF, 0x2c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_L), 0xFF, 0x16/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_L), 0xFF, 0xd4/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_L), 0xFF, 0x9a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_L), 0xFF, 0x6b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_L), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_L), 0xFF, 0x0a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_L), 0xFF, 0x1b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_L), 0xFF, 0x2f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_L), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_L), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_L), 0xFF, 0x39/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_L), 0xFF, 0x39/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_L), 0xFF, 0x0c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_L), 0xFF, 0x33/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_L), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_L), 0xFF, 0x69/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_L), 0xFF, 0xdc/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_L), 0xFF, 0x2e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_L), 0xFF, 0x23/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_L), 0xFF, 0xa3/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_L), 0xFF, 0xa3/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_L), 0xFF, 0x23/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_L), 0xFF, 0x11/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_L), 0xFF, 0x85/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_L), 0xFF, 0x4a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_L), 0xFF, 0x23/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_L), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_L), 0xFF, 0x7e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_L), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_L), 0xFF, 0x4b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_L), 0xFF, 0x63/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_L), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_L), 0xFF, 0x8c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_L), 0xFF, 0x1d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_L), 0xFF, 0xd0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_L), 0xFF, 0xd0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDMITX_8BIT  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0xBE/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0xED/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x70/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// SC1_INIT  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_SC1_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_SC1_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_6C_H), 0x0C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// SC1_INIT_SC  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_SC1_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_SC1_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_H), 0xFF, 0xCC/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_L), 0xFF, 0xFD/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_L), 0xFF, 0xFF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_L), 0xFF, 0xEF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_L), 0xFF, 0xEF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_L), 0xFF, 0x59/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_01_L), 0xFF, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_SVOP_BK8F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_L), 0xFF, 0x09/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_L), 0xFF, 0x0B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x1C, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_L), 0x0C, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_H), 0x1C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_5A_L), 0x1C, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_GPIO_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_GPIO_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_L), 0x00, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_H), 0x00, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_SC  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x97/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x2B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_MOD_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_MOD_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_L), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_H), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDGEN  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_HDGEN_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_HDGEN_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_L), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_H), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_L), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_L), 0xFF, 0x0f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_L), 0xFF, 0x4c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_L), 0xFF, 0x97/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_H), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_L), 0xFF, 0xaf/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_H), 0xFF, 0x70/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_L), 0xFF, 0x6b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_H), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_L), 0xFF, 0x63/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_H), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_H), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_L), 0xFF, 0x6e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_L), 0xFF, 0x2c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_L), 0xFF, 0x16/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_L), 0xFF, 0xd4/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_L), 0xFF, 0x9a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_L), 0xFF, 0x6b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_L), 0xFF, 0x56/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_L), 0xFF, 0x0d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_L), 0xFF, 0x0b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_L), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_L), 0xFF, 0x28/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_L), 0xFF, 0x87/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_L), 0xFF, 0x87/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_L), 0xFF, 0x1d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_L), 0xFF, 0x3a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_L), 0xFF, 0x1d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_L), 0xFF, 0x51/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_L), 0xFF, 0x4f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_L), 0xFF, 0x5e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_L), 0xFF, 0x5c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_L), 0xFF, 0xdc/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_L), 0xFF, 0xdc/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_L), 0xFF, 0x5c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDMITX_8BIT  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0xBE/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0xED/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x23/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// SC1_INIT  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_SC1_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_SC1_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_6C_H), 0x0C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// SC1_INIT_SC  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_SC1_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_SC1_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_H), 0xFF, 0xCC/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_L), 0xFF, 0xFD/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_L), 0xFF, 0xFF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_L), 0xFF, 0xEF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_L), 0xFF, 0xEF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_L), 0xFF, 0x59/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_01_L), 0xFF, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_SVOP_BK8F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_L), 0xFF, 0x09/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_L), 0xFF, 0x0B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x1C, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_L), 0x0C, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_H), 0x1C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_5A_L), 0x1C, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_GPIO_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_GPIO_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_L), 0x00, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_H), 0x00, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_SC  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x4F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x0F, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x2B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_MOD_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_MOD_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_L), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_H), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDGEN  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_HDGEN_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_HDGEN_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_L), 0xFF, 0x1a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_H), 0xFF, 0x0a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_L), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_L), 0xFF, 0x0f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_L), 0xFF, 0x4c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_L), 0xFF, 0x4f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_H), 0xFF, 0x0a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_L), 0xFF, 0xaf/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_H), 0xFF, 0x70/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_L), 0xFF, 0x6b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_H), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_L), 0xFF, 0x63/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_H), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_H), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_L), 0xFF, 0x6e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_L), 0xFF, 0x2c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_L), 0xFF, 0x16/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_L), 0xFF, 0xd4/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_L), 0xFF, 0x9a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_L), 0xFF, 0x6b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_L), 0xFF, 0x56/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_L), 0xFF, 0x0d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_L), 0xFF, 0x0b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_L), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_L), 0xFF, 0x28/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_L), 0xFF, 0x87/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_L), 0xFF, 0x87/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_L), 0xFF, 0x1d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_L), 0xFF, 0x3a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_L), 0xFF, 0x1d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_L), 0xFF, 0x51/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_L), 0xFF, 0x4f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_L), 0xFF, 0x5e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_L), 0xFF, 0x5c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_L), 0xFF, 0xdc/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_L), 0xFF, 0xdc/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_L), 0xFF, 0x5c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDMITX_8BIT  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0xBE/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0xED/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x23/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// SC1_INIT  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_SC1_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_SC1_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_6C_H), 0x0C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// SC1_INIT_SC  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_SC1_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_SC1_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_H), 0xFF, 0xCC/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_L), 0xFF, 0x21/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_L), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_L), 0xFF, 0x1F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_L), 0xFF, 0x1F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_L), 0xFF, 0x5F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_01_L), 0xFF, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_L), 0xFF, 0x84/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_L), 0xFF, 0x84/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_SVOP_BK8F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x1C, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_L), 0x0C, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_H), 0x1C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_5A_L), 0x1C, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_GPIO_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_GPIO_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_L), 0x00, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_H), 0x00, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_SC  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x07, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0xBD/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x0F, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x2B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_MOD_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_MOD_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_L), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_H), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDGEN  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_HDGEN_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_HDGEN_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_L), 0xFF, 0x8c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_H), 0xFF, 0x0a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_L), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_L), 0xFF, 0x0f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_L), 0xFF, 0x4c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_L), 0xFF, 0xbd/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_H), 0xFF, 0x0a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_L), 0xFF, 0xaf/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_H), 0xFF, 0x70/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_L), 0xFF, 0x6b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_H), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_L), 0xFF, 0x63/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_H), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_H), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_L), 0xFF, 0x6e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_L), 0xFF, 0x2c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_L), 0xFF, 0x16/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_L), 0xFF, 0xd4/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_L), 0xFF, 0x9a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_L), 0xFF, 0x3d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_L), 0xFF, 0x6b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_L), 0xFF, 0x56/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_L), 0xFF, 0x2b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_L), 0xFF, 0x0d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_L), 0xFF, 0x0b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_L), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_L), 0xFF, 0x28/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_L), 0xFF, 0x87/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_L), 0xFF, 0x87/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_L), 0xFF, 0x1d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_L), 0xFF, 0x3a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_L), 0xFF, 0x1d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_L), 0xFF, 0x51/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_L), 0xFF, 0x4f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_L), 0xFF, 0x5e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_L), 0xFF, 0x5c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_L), 0xFF, 0xdc/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_L), 0xFF, 0xdc/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_L), 0xFF, 0x5c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDMITX_8BIT  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0xBE/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0xED/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x23/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// SC1_INIT  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_SC1_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_SC1_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_6C_H), 0x0C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// SC1_INIT_SC  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_SC1_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_SC1_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_H), 0xFF, 0xCC/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_L), 0xFF, 0xFD/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_L), 0xFF, 0xFF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_L), 0xFF, 0xEF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_L), 0xFF, 0xEF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_L), 0xFF, 0x59/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_01_L), 0xFF, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_SVOP_BK8F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_L), 0xFF, 0x09/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_L), 0xFF, 0x0B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x1C, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_L), 0x0C, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_58_H), 0x1C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_5A_L), 0x1C, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_GPIO_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_GPIO_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_L), 0x00, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CHIP_TOP_2B_H), 0x00, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_SC  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x07, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0xEA/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0xEB/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0xDF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0xDF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x1F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x5F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x90/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x0F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x90/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x0F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_MOD_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_MOD_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_L), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_MOD_BK00_00_H), 0x00, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDGEN  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_HDGEN_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_HDGEN_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_02_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_04_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_0F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_10_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_11_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_12_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_13_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_L), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_14_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_15_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_16_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_L), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_P2I_BK2_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_L), 0xFF, 0x0f/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_01_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_0D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_L), 0xFF, 0x0c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_10_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_L), 0xFF, 0x59/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_12_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_L), 0xFF, 0x1a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_13_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_14_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_15_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_16_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_17_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_18_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_19_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_1F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_20_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_L), 0xFF, 0x0a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_21_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_22_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_L), 0xFF, 0x3e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_23_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_24_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_25_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_26_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_27_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_L), 0xFF, 0x6e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_28_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_L), 0xFF, 0x2c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_29_H), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2B_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_L), 0xFF, 0x16/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_L), 0xFF, 0xd4/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_2F_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_L), 0xFF, 0x9a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_30_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_31_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_L), 0xFF, 0x91/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_32_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_33_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_35_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_36_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_37_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_38_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_39_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_L), 0xFF, 0x74/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3C_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_L), 0xFF, 0x6b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3D_H), 0xFF, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_7B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_3E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_40_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_41_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_L), 0xFF, 0x16/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_42_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_43_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_L), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_44_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_L), 0xFF, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_45_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_L), 0xFF, 0x1a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_46_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_L), 0xFF, 0x28/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_47_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_48_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_49_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_L), 0xFF, 0xfa/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4A_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_L), 0xFF, 0x2e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4B_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_L), 0xFF, 0x1e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_L), 0xFF, 0xd4/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4E_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_L), 0xFF, 0x2d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_4F_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_50_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_L), 0xFF, 0xa7/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_51_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_L), 0xFF, 0xa7/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_52_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_53_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_L), 0xFF, 0x11/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_54_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_55_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_L), 0xFF, 0x85/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_56_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_L), 0xFF, 0x4a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_57_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_L), 0xFF, 0x23/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_58_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_L), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_59_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_L), 0xFF, 0x7e/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5A_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_L), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5B_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_L), 0xFF, 0x2a/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5C_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_L), 0xFF, 0x42/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5D_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_L), 0xFF, 0x4b/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5E_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_L), 0xFF, 0x63/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_5F_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_L), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_60_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_L), 0xFF, 0x8c/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_61_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_L), 0xFF, 0x1d/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_62_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_63_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_64_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_L), 0xFF, 0xd0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_65_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_L), 0xFF, 0xd0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_66_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDGEN_BK1_67_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_HDMITX_8BIT  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x6D/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x6C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x29/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x22/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x09/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_10_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_L), 0xFF, 0x6D/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_11_H), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_L), 0xFF, 0x68/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_38_H), 0xFF, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PM_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// SC1_INIT  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_SC1_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_SC1_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_6C_H), 0x0C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// SC1_INIT_SC  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_SC1_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_SC1_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_10_H), 0xFF, 0xCC/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0D_H), 0x07, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_L), 0xFF, 0xFD/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_02_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_L), 0xFF, 0xFF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_03_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_06_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_L), 0xFF, 0xEF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_07_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0A_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_L), 0xFF, 0xEF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0B_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_L), 0xFF, 0x59/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_0C_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_01_L), 0xFF, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_04_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_05_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_08_H), 0x07, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_09_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_14_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_VOP_BK90_5D_H), 0xFF, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_SVOP_BK8F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_L), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_L), 0xFF, 0x09/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_L), 0xFF, 0x0B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC1_OP1_BKA0_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

DAC_TAB_INFO DACMAP_Main[DAC_PANEL_NUMS]=
{
{
*MST_DAC_480I_60_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_480I_60_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_480I_60_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_480I_60_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_480I_60_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_480I_60_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_480I_60_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_480I_60_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_480I_60_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_480I_60_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_480I_60_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_480I_60_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_480I_60_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_480I_60_Gamma_TBL, DAC_TABTYPE_Gamma, 
*MST_DAC_480I_60_SC1_INIT_TBL, DAC_TABTYPE_SC1_INIT, 
*MST_DAC_480I_60_SC1_INIT_SC_TBL, DAC_TABTYPE_SC1_INIT_SC, 
},
{
*MST_DAC_480P_60_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_480P_60_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_480P_60_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_480P_60_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_480P_60_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_480P_60_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_480P_60_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_480P_60_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_480P_60_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_480P_60_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_480P_60_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_480P_60_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_480P_60_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_480P_60_Gamma_TBL, DAC_TABTYPE_Gamma, 
*MST_DAC_480P_60_SC1_INIT_TBL, DAC_TABTYPE_SC1_INIT, 
*MST_DAC_480P_60_SC1_INIT_SC_TBL, DAC_TABTYPE_SC1_INIT_SC, 
},
{
*MST_DAC_576I_50_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_576I_50_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_576I_50_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_576I_50_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_576I_50_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_576I_50_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_576I_50_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_576I_50_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_576I_50_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_576I_50_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_576I_50_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_576I_50_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_576I_50_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_576I_50_Gamma_TBL, DAC_TABTYPE_Gamma, 
*MST_DAC_576I_50_SC1_INIT_TBL, DAC_TABTYPE_SC1_INIT, 
*MST_DAC_576I_50_SC1_INIT_SC_TBL, DAC_TABTYPE_SC1_INIT_SC, 
},
{
*MST_DAC_576P_50_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_576P_50_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_576P_50_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_576P_50_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_576P_50_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_576P_50_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_576P_50_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_576P_50_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_576P_50_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_576P_50_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_576P_50_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_576P_50_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_576P_50_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_576P_50_Gamma_TBL, DAC_TABTYPE_Gamma, 
*MST_DAC_576P_50_SC1_INIT_TBL, DAC_TABTYPE_SC1_INIT, 
*MST_DAC_576P_50_SC1_INIT_SC_TBL, DAC_TABTYPE_SC1_INIT_SC, 
},
{
*MST_DAC_720P_50_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_720P_50_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_720P_50_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_720P_50_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_720P_50_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_720P_50_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_720P_50_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_720P_50_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_720P_50_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_720P_50_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_720P_50_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_720P_50_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_720P_50_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_720P_50_Gamma_TBL, DAC_TABTYPE_Gamma, 
*MST_DAC_720P_50_SC1_INIT_TBL, DAC_TABTYPE_SC1_INIT, 
*MST_DAC_720P_50_SC1_INIT_SC_TBL, DAC_TABTYPE_SC1_INIT_SC, 
},
{
*MST_DAC_720P_60_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_720P_60_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_720P_60_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_720P_60_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_720P_60_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_720P_60_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_720P_60_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_720P_60_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_720P_60_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_720P_60_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_720P_60_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_720P_60_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_720P_60_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_720P_60_Gamma_TBL, DAC_TABTYPE_Gamma, 
*MST_DAC_720P_60_SC1_INIT_TBL, DAC_TABTYPE_SC1_INIT, 
*MST_DAC_720P_60_SC1_INIT_SC_TBL, DAC_TABTYPE_SC1_INIT_SC, 
},
{
*MST_DAC_1080I_50_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_1080I_50_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_1080I_50_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_1080I_50_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_1080I_50_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_1080I_50_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_1080I_50_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_1080I_50_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_1080I_50_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_1080I_50_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_1080I_50_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_1080I_50_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_1080I_50_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_1080I_50_Gamma_TBL, DAC_TABTYPE_Gamma, 
*MST_DAC_1080I_50_SC1_INIT_TBL, DAC_TABTYPE_SC1_INIT, 
*MST_DAC_1080I_50_SC1_INIT_SC_TBL, DAC_TABTYPE_SC1_INIT_SC, 
},
{
*MST_DAC_1080I_60_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_1080I_60_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_1080I_60_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_1080I_60_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_1080I_60_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_1080I_60_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_1080I_60_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_1080I_60_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_1080I_60_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_1080I_60_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_1080I_60_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_1080I_60_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_1080I_60_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_1080I_60_Gamma_TBL, DAC_TABTYPE_Gamma, 
*MST_DAC_1080I_60_SC1_INIT_TBL, DAC_TABTYPE_SC1_INIT, 
*MST_DAC_1080I_60_SC1_INIT_SC_TBL, DAC_TABTYPE_SC1_INIT_SC, 
},
{
*MST_DAC_1080P_50_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_1080P_50_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_1080P_50_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_1080P_50_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_1080P_50_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_1080P_50_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_1080P_50_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_1080P_50_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_1080P_50_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_1080P_50_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_1080P_50_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_1080P_50_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_1080P_50_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_1080P_50_Gamma_TBL, DAC_TABTYPE_Gamma, 
*MST_DAC_1080P_50_SC1_INIT_TBL, DAC_TABTYPE_SC1_INIT, 
*MST_DAC_1080P_50_SC1_INIT_SC_TBL, DAC_TABTYPE_SC1_INIT_SC, 
},
{
*MST_DAC_1080P_60_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_1080P_60_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_1080P_60_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_1080P_60_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_1080P_60_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_1080P_60_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_1080P_60_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_1080P_60_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_1080P_60_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_1080P_60_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_1080P_60_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_1080P_60_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_1080P_60_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_1080P_60_Gamma_TBL, DAC_TABTYPE_Gamma, 
*MST_DAC_1080P_60_SC1_INIT_TBL, DAC_TABTYPE_SC1_INIT, 
*MST_DAC_1080P_60_SC1_INIT_SC_TBL, DAC_TABTYPE_SC1_INIT_SC, 
},
{
*MST_DAC_1080P_30_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_1080P_30_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_1080P_30_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_1080P_30_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_1080P_30_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_1080P_30_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_1080P_30_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_1080P_30_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_1080P_30_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_1080P_30_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_1080P_30_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_1080P_30_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_1080P_30_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_1080P_30_Gamma_TBL, DAC_TABTYPE_Gamma, 
*MST_DAC_1080P_30_SC1_INIT_TBL, DAC_TABTYPE_SC1_INIT, 
*MST_DAC_1080P_30_SC1_INIT_SC_TBL, DAC_TABTYPE_SC1_INIT_SC, 
},
{
*MST_DAC_1080P_25_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_1080P_25_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_1080P_25_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_1080P_25_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_1080P_25_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_1080P_25_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_1080P_25_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_1080P_25_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_1080P_25_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_1080P_25_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_1080P_25_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_1080P_25_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_1080P_25_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_1080P_25_Gamma_TBL, DAC_TABTYPE_Gamma, 
*MST_DAC_1080P_25_SC1_INIT_TBL, DAC_TABTYPE_SC1_INIT, 
*MST_DAC_1080P_25_SC1_INIT_SC_TBL, DAC_TABTYPE_SC1_INIT_SC, 
},
{
*MST_DAC_1080P_24_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_1080P_24_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_1080P_24_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_1080P_24_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_1080P_24_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_1080P_24_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_1080P_24_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_1080P_24_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_1080P_24_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_1080P_24_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_1080P_24_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_1080P_24_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_1080P_24_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_1080P_24_Gamma_TBL, DAC_TABTYPE_Gamma, 
*MST_DAC_1080P_24_SC1_INIT_TBL, DAC_TABTYPE_SC1_INIT, 
*MST_DAC_1080P_24_SC1_INIT_SC_TBL, DAC_TABTYPE_SC1_INIT_SC, 
},
{
*MST_DAC_640x480_60_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_640x480_60_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_640x480_60_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_640x480_60_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_640x480_60_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_640x480_60_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_640x480_60_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_640x480_60_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_640x480_60_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_640x480_60_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_640x480_60_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_640x480_60_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_640x480_60_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_640x480_60_Gamma_TBL, DAC_TABTYPE_Gamma, 
*MST_DAC_640x480_60_SC1_INIT_TBL, DAC_TABTYPE_SC1_INIT, 
*MST_DAC_640x480_60_SC1_INIT_SC_TBL, DAC_TABTYPE_SC1_INIT_SC, 
},
};

#endif
