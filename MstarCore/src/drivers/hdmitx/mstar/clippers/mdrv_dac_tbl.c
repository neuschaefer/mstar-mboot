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
// DAC Drive Chip           : Clippers_DAC_Driver
// DAC Excel CodeGen Version: 1.03
// DAC Excel SW      Version: 1.04
// DAC Excel update date    : 2014/7/28 17:17
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
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
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
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0xE9/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0xEE/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0xDF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0xDF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x59/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x3D/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x6C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x26/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x09/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  480I_60
//****************************************************
MS_U8 MST_DAC_480I_60_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480I_60_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x68/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
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
// INIT  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
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
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0xE9/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0xEE/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0xDF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0xDF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x59/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x3D/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x7A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x6C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x26/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x09/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  480P_60
//****************************************************
MS_U8 MST_DAC_480P_60_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_480P_60_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x68/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
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
// INIT  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
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
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x5F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x84/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x84/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x6C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x26/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x09/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  576I_50
//****************************************************
MS_U8 MST_DAC_576I_50_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576I_50_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x68/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
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
// INIT  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
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
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x5F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x3D/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x84/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x84/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x53/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x6C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x66/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x26/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x09/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  576P_50
//****************************************************
MS_U8 MST_DAC_576P_50_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_576P_50_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x68/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
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
// INIT  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
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
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0xD5/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0xD9/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0xCF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0xCF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0xBB/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0xED/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  720P_50
//****************************************************
MS_U8 MST_DAC_720P_50_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_50_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
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
// INIT  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
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
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0xD5/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0xD9/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0xCF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0xCF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0xED/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  720P_60
//****************************************************
MS_U8 MST_DAC_720P_60_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_720P_60_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
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
// INIT  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
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
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x4F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x2B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0xED/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  1080I_50
//****************************************************
MS_U8 MST_DAC_1080I_50_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_50_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
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
// INIT  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
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
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x97/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x2B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x46/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x87/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0xF4/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xC6/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x4B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x46/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  1080I_60
//****************************************************
MS_U8 MST_DAC_1080I_60_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080I_60_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
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
// INIT  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
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
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x4F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x2B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0xED/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  1080P_50
//****************************************************
MS_U8 MST_DAC_1080P_50_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_50_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
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
// INIT  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
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
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x97/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x2B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0xED/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  1080P_60
//****************************************************
MS_U8 MST_DAC_1080P_60_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_60_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
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
// INIT  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
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
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x97/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x2B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0xED/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  1080P_30
//****************************************************
MS_U8 MST_DAC_1080P_30_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_30_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
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
// INIT  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
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
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x4F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x2B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0xED/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  1080P_25
//****************************************************
MS_U8 MST_DAC_1080P_25_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_25_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
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
// INIT  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
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
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x37/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0xBD/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x2B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x64/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x61/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0xED/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x34/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  1080P_24
//****************************************************
MS_U8 MST_DAC_1080P_24_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1080P_24_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
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
// INIT  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x55/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
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
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0xEA/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0xEB/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0xDF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0xDF/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x1F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x5F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x90/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x0F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x90/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x0F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x6D/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x6C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x24/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x29/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x49/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x22/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x38/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x09/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x6D/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x1B/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  640x480_60
//****************************************************
MS_U8 MST_DAC_640x480_60_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_640x480_60_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x68/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x0C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
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
// INIT  1920x2205P_24
//****************************************************
MS_U8 MST_DAC_1920x2205P_24_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1920x2205P_24_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  1920x2205P_24
//****************************************************
MS_U8 MST_DAC_1920x2205P_24_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_SC  1920x2205P_24
//****************************************************
MS_U8 MST_DAC_1920x2205P_24_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1920x2205P_24_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0xC9/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0xA1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0xA5/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x9C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x9C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0xBD/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x0A/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x2B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0xC0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x3F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  1920x2205P_24
//****************************************************
MS_U8 MST_DAC_1920x2205P_24_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  1920x2205P_24
//****************************************************
MS_U8 MST_DAC_1920x2205P_24_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  1920x2205P_24
//****************************************************
MS_U8 MST_DAC_1920x2205P_24_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1920x2205P_24_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  1920x2205P_24
//****************************************************
MS_U8 MST_DAC_1920x2205P_24_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1920x2205P_24_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  1920x2205P_24
//****************************************************
MS_U8 MST_DAC_1920x2205P_24_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1920x2205P_24_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  1920x2205P_24
//****************************************************
MS_U8 MST_DAC_1920x2205P_24_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1920x2205P_24_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  1920x2205P_24
//****************************************************
MS_U8 MST_DAC_1920x2205P_24_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1920x2205P_24_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  1920x2205P_24
//****************************************************
MS_U8 MST_DAC_1920x2205P_24_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1920x2205P_24_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  1920x2205P_24
//****************************************************
MS_U8 MST_DAC_1920x2205P_24_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1920x2205P_24_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  1920x2205P_24
//****************************************************
MS_U8 MST_DAC_1920x2205P_24_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1920x2205P_24_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  1920x2205P_24
//****************************************************
MS_U8 MST_DAC_1920x2205P_24_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT  1280x1470P_50
//****************************************************
MS_U8 MST_DAC_1280x1470P_50_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1280x1470P_50_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  1280x1470P_50
//****************************************************
MS_U8 MST_DAC_1280x1470P_50_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_SC  1280x1470P_50
//****************************************************
MS_U8 MST_DAC_1280x1470P_50_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1280x1470P_50_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0xDB/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0xC3/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0xC7/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0xBD/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0xBD/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0xBB/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  1280x1470P_50
//****************************************************
MS_U8 MST_DAC_1280x1470P_50_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  1280x1470P_50
//****************************************************
MS_U8 MST_DAC_1280x1470P_50_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  1280x1470P_50
//****************************************************
MS_U8 MST_DAC_1280x1470P_50_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1280x1470P_50_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  1280x1470P_50
//****************************************************
MS_U8 MST_DAC_1280x1470P_50_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1280x1470P_50_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  1280x1470P_50
//****************************************************
MS_U8 MST_DAC_1280x1470P_50_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1280x1470P_50_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  1280x1470P_50
//****************************************************
MS_U8 MST_DAC_1280x1470P_50_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1280x1470P_50_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  1280x1470P_50
//****************************************************
MS_U8 MST_DAC_1280x1470P_50_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1280x1470P_50_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  1280x1470P_50
//****************************************************
MS_U8 MST_DAC_1280x1470P_50_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1280x1470P_50_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  1280x1470P_50
//****************************************************
MS_U8 MST_DAC_1280x1470P_50_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1280x1470P_50_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  1280x1470P_50
//****************************************************
MS_U8 MST_DAC_1280x1470P_50_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1280x1470P_50_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  1280x1470P_50
//****************************************************
MS_U8 MST_DAC_1280x1470P_50_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT  1280x1470P_60
//****************************************************
MS_U8 MST_DAC_1280x1470P_60_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1280x1470P_60_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  1280x1470P_60
//****************************************************
MS_U8 MST_DAC_1280x1470P_60_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_SC  1280x1470P_60
//****************************************************
MS_U8 MST_DAC_1280x1470P_60_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1280x1470P_60_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0xDB/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0xC3/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0xC7/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0xBD/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0xBD/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x27/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x03/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x06/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  1280x1470P_60
//****************************************************
MS_U8 MST_DAC_1280x1470P_60_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  1280x1470P_60
//****************************************************
MS_U8 MST_DAC_1280x1470P_60_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  1280x1470P_60
//****************************************************
MS_U8 MST_DAC_1280x1470P_60_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1280x1470P_60_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  1280x1470P_60
//****************************************************
MS_U8 MST_DAC_1280x1470P_60_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1280x1470P_60_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  1280x1470P_60
//****************************************************
MS_U8 MST_DAC_1280x1470P_60_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1280x1470P_60_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  1280x1470P_60
//****************************************************
MS_U8 MST_DAC_1280x1470P_60_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1280x1470P_60_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  1280x1470P_60
//****************************************************
MS_U8 MST_DAC_1280x1470P_60_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1280x1470P_60_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  1280x1470P_60
//****************************************************
MS_U8 MST_DAC_1280x1470P_60_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1280x1470P_60_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  1280x1470P_60
//****************************************************
MS_U8 MST_DAC_1280x1470P_60_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1280x1470P_60_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0x82/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x3C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x25/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  1280x1470P_60
//****************************************************
MS_U8 MST_DAC_1280x1470P_60_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_1280x1470P_60_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x60/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  1280x1470P_60
//****************************************************
MS_U8 MST_DAC_1280x1470P_60_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT  3840x2160P_24
//****************************************************
MS_U8 MST_DAC_3840x2160P_24_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_24_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  3840x2160P_24
//****************************************************
MS_U8 MST_DAC_3840x2160P_24_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_SC  3840x2160P_24
//****************************************************
MS_U8 MST_DAC_3840x2160P_24_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_24_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0xC9/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x78/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x81/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x6F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x6F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x7B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x7F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x7F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  3840x2160P_24
//****************************************************
MS_U8 MST_DAC_3840x2160P_24_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  3840x2160P_24
//****************************************************
MS_U8 MST_DAC_3840x2160P_24_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  3840x2160P_24
//****************************************************
MS_U8 MST_DAC_3840x2160P_24_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_24_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  3840x2160P_24
//****************************************************
MS_U8 MST_DAC_3840x2160P_24_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_24_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  3840x2160P_24
//****************************************************
MS_U8 MST_DAC_3840x2160P_24_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_24_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  3840x2160P_24
//****************************************************
MS_U8 MST_DAC_3840x2160P_24_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_24_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  3840x2160P_24
//****************************************************
MS_U8 MST_DAC_3840x2160P_24_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_24_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  3840x2160P_24
//****************************************************
MS_U8 MST_DAC_3840x2160P_24_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_24_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  3840x2160P_24
//****************************************************
MS_U8 MST_DAC_3840x2160P_24_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_24_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  3840x2160P_24
//****************************************************
MS_U8 MST_DAC_3840x2160P_24_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_24_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  3840x2160P_24
//****************************************************
MS_U8 MST_DAC_3840x2160P_24_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT  3840x2160P_25
//****************************************************
MS_U8 MST_DAC_3840x2160P_25_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_25_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  3840x2160P_25
//****************************************************
MS_U8 MST_DAC_3840x2160P_25_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_SC  3840x2160P_25
//****************************************************
MS_U8 MST_DAC_3840x2160P_25_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_25_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0xC9/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x78/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x81/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x6F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x6F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x9F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x14/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x7F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x7F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  3840x2160P_25
//****************************************************
MS_U8 MST_DAC_3840x2160P_25_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  3840x2160P_25
//****************************************************
MS_U8 MST_DAC_3840x2160P_25_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  3840x2160P_25
//****************************************************
MS_U8 MST_DAC_3840x2160P_25_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_25_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  3840x2160P_25
//****************************************************
MS_U8 MST_DAC_3840x2160P_25_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_25_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  3840x2160P_25
//****************************************************
MS_U8 MST_DAC_3840x2160P_25_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_25_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  3840x2160P_25
//****************************************************
MS_U8 MST_DAC_3840x2160P_25_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_25_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  3840x2160P_25
//****************************************************
MS_U8 MST_DAC_3840x2160P_25_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_25_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  3840x2160P_25
//****************************************************
MS_U8 MST_DAC_3840x2160P_25_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_25_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  3840x2160P_25
//****************************************************
MS_U8 MST_DAC_3840x2160P_25_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_25_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  3840x2160P_25
//****************************************************
MS_U8 MST_DAC_3840x2160P_25_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_25_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  3840x2160P_25
//****************************************************
MS_U8 MST_DAC_3840x2160P_25_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT  3840x2160P_30
//****************************************************
MS_U8 MST_DAC_3840x2160P_30_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_30_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  3840x2160P_30
//****************************************************
MS_U8 MST_DAC_3840x2160P_30_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_SC  3840x2160P_30
//****************************************************
MS_U8 MST_DAC_3840x2160P_30_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_30_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0xC9/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x78/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x81/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x6F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x6F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x2F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x11/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x7F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x7F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  3840x2160P_30
//****************************************************
MS_U8 MST_DAC_3840x2160P_30_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  3840x2160P_30
//****************************************************
MS_U8 MST_DAC_3840x2160P_30_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  3840x2160P_30
//****************************************************
MS_U8 MST_DAC_3840x2160P_30_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_30_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  3840x2160P_30
//****************************************************
MS_U8 MST_DAC_3840x2160P_30_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_30_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  3840x2160P_30
//****************************************************
MS_U8 MST_DAC_3840x2160P_30_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_30_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  3840x2160P_30
//****************************************************
MS_U8 MST_DAC_3840x2160P_30_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_30_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  3840x2160P_30
//****************************************************
MS_U8 MST_DAC_3840x2160P_30_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_30_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  3840x2160P_30
//****************************************************
MS_U8 MST_DAC_3840x2160P_30_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_30_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  3840x2160P_30
//****************************************************
MS_U8 MST_DAC_3840x2160P_30_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_30_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  3840x2160P_30
//****************************************************
MS_U8 MST_DAC_3840x2160P_30_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_30_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  3840x2160P_30
//****************************************************
MS_U8 MST_DAC_3840x2160P_30_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT  3840x2160P_50
//****************************************************
MS_U8 MST_DAC_3840x2160P_50_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_50_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  3840x2160P_50
//****************************************************
MS_U8 MST_DAC_3840x2160P_50_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_SC  3840x2160P_50
//****************************************************
MS_U8 MST_DAC_3840x2160P_50_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_50_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0xC9/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x78/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x81/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x6F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x6F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x9F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x14/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x7F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x7F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  3840x2160P_50
//****************************************************
MS_U8 MST_DAC_3840x2160P_50_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  3840x2160P_50
//****************************************************
MS_U8 MST_DAC_3840x2160P_50_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  3840x2160P_50
//****************************************************
MS_U8 MST_DAC_3840x2160P_50_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_50_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  3840x2160P_50
//****************************************************
MS_U8 MST_DAC_3840x2160P_50_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_50_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  3840x2160P_50
//****************************************************
MS_U8 MST_DAC_3840x2160P_50_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_50_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  3840x2160P_50
//****************************************************
MS_U8 MST_DAC_3840x2160P_50_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_50_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  3840x2160P_50
//****************************************************
MS_U8 MST_DAC_3840x2160P_50_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_50_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  3840x2160P_50
//****************************************************
MS_U8 MST_DAC_3840x2160P_50_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_50_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  3840x2160P_50
//****************************************************
MS_U8 MST_DAC_3840x2160P_50_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_50_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  3840x2160P_50
//****************************************************
MS_U8 MST_DAC_3840x2160P_50_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_50_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  3840x2160P_50
//****************************************************
MS_U8 MST_DAC_3840x2160P_50_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT  3840x2160P_60
//****************************************************
MS_U8 MST_DAC_3840x2160P_60_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_60_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  3840x2160P_60
//****************************************************
MS_U8 MST_DAC_3840x2160P_60_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_SC  3840x2160P_60
//****************************************************
MS_U8 MST_DAC_3840x2160P_60_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_60_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0xC9/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x78/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x81/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x6F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x6F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x2F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x11/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x7F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x7F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  3840x2160P_60
//****************************************************
MS_U8 MST_DAC_3840x2160P_60_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  3840x2160P_60
//****************************************************
MS_U8 MST_DAC_3840x2160P_60_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  3840x2160P_60
//****************************************************
MS_U8 MST_DAC_3840x2160P_60_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_60_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  3840x2160P_60
//****************************************************
MS_U8 MST_DAC_3840x2160P_60_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_60_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  3840x2160P_60
//****************************************************
MS_U8 MST_DAC_3840x2160P_60_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_60_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  3840x2160P_60
//****************************************************
MS_U8 MST_DAC_3840x2160P_60_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_60_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  3840x2160P_60
//****************************************************
MS_U8 MST_DAC_3840x2160P_60_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_60_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  3840x2160P_60
//****************************************************
MS_U8 MST_DAC_3840x2160P_60_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_60_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  3840x2160P_60
//****************************************************
MS_U8 MST_DAC_3840x2160P_60_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_60_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  3840x2160P_60
//****************************************************
MS_U8 MST_DAC_3840x2160P_60_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_3840x2160P_60_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  3840x2160P_60
//****************************************************
MS_U8 MST_DAC_3840x2160P_60_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT  4096x2160P_24
//****************************************************
MS_U8 MST_DAC_4096x2160P_24_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_24_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  4096x2160P_24
//****************************************************
MS_U8 MST_DAC_4096x2160P_24_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_SC  4096x2160P_24
//****************************************************
MS_U8 MST_DAC_4096x2160P_24_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_24_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0xC9/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x78/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x81/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x6F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x6F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x7B/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0x7F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x11/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0x7F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x11/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  4096x2160P_24
//****************************************************
MS_U8 MST_DAC_4096x2160P_24_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  4096x2160P_24
//****************************************************
MS_U8 MST_DAC_4096x2160P_24_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  4096x2160P_24
//****************************************************
MS_U8 MST_DAC_4096x2160P_24_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_24_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  4096x2160P_24
//****************************************************
MS_U8 MST_DAC_4096x2160P_24_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_24_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  4096x2160P_24
//****************************************************
MS_U8 MST_DAC_4096x2160P_24_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_24_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  4096x2160P_24
//****************************************************
MS_U8 MST_DAC_4096x2160P_24_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_24_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  4096x2160P_24
//****************************************************
MS_U8 MST_DAC_4096x2160P_24_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_24_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  4096x2160P_24
//****************************************************
MS_U8 MST_DAC_4096x2160P_24_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_24_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  4096x2160P_24
//****************************************************
MS_U8 MST_DAC_4096x2160P_24_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_24_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  4096x2160P_24
//****************************************************
MS_U8 MST_DAC_4096x2160P_24_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_24_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  4096x2160P_24
//****************************************************
MS_U8 MST_DAC_4096x2160P_24_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT  4096x2160P_25
//****************************************************
MS_U8 MST_DAC_4096x2160P_25_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_25_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  4096x2160P_25
//****************************************************
MS_U8 MST_DAC_4096x2160P_25_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_SC  4096x2160P_25
//****************************************************
MS_U8 MST_DAC_4096x2160P_25_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_25_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0xC9/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x78/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x81/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x6F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x6F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x9F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x14/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0xD8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0xD7/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0xD8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0xD7/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  4096x2160P_25
//****************************************************
MS_U8 MST_DAC_4096x2160P_25_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  4096x2160P_25
//****************************************************
MS_U8 MST_DAC_4096x2160P_25_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  4096x2160P_25
//****************************************************
MS_U8 MST_DAC_4096x2160P_25_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_25_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  4096x2160P_25
//****************************************************
MS_U8 MST_DAC_4096x2160P_25_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_25_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  4096x2160P_25
//****************************************************
MS_U8 MST_DAC_4096x2160P_25_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_25_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  4096x2160P_25
//****************************************************
MS_U8 MST_DAC_4096x2160P_25_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_25_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  4096x2160P_25
//****************************************************
MS_U8 MST_DAC_4096x2160P_25_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_25_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  4096x2160P_25
//****************************************************
MS_U8 MST_DAC_4096x2160P_25_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_25_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  4096x2160P_25
//****************************************************
MS_U8 MST_DAC_4096x2160P_25_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_25_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  4096x2160P_25
//****************************************************
MS_U8 MST_DAC_4096x2160P_25_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_25_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  4096x2160P_25
//****************************************************
MS_U8 MST_DAC_4096x2160P_25_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT  4096x2160P_30
//****************************************************
MS_U8 MST_DAC_4096x2160P_30_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_30_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  4096x2160P_30
//****************************************************
MS_U8 MST_DAC_4096x2160P_30_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_SC  4096x2160P_30
//****************************************************
MS_U8 MST_DAC_4096x2160P_30_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_30_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0xC9/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x78/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x81/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x6F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x6F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x2F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x11/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0xD8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0xD7/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0xD8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0xD7/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  4096x2160P_30
//****************************************************
MS_U8 MST_DAC_4096x2160P_30_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  4096x2160P_30
//****************************************************
MS_U8 MST_DAC_4096x2160P_30_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  4096x2160P_30
//****************************************************
MS_U8 MST_DAC_4096x2160P_30_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_30_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  4096x2160P_30
//****************************************************
MS_U8 MST_DAC_4096x2160P_30_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_30_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  4096x2160P_30
//****************************************************
MS_U8 MST_DAC_4096x2160P_30_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_30_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  4096x2160P_30
//****************************************************
MS_U8 MST_DAC_4096x2160P_30_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_30_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  4096x2160P_30
//****************************************************
MS_U8 MST_DAC_4096x2160P_30_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_30_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  4096x2160P_30
//****************************************************
MS_U8 MST_DAC_4096x2160P_30_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_30_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  4096x2160P_30
//****************************************************
MS_U8 MST_DAC_4096x2160P_30_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_30_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  4096x2160P_30
//****************************************************
MS_U8 MST_DAC_4096x2160P_30_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_30_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  4096x2160P_30
//****************************************************
MS_U8 MST_DAC_4096x2160P_30_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT  4096x2160P_50
//****************************************************
MS_U8 MST_DAC_4096x2160P_50_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_50_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  4096x2160P_50
//****************************************************
MS_U8 MST_DAC_4096x2160P_50_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_SC  4096x2160P_50
//****************************************************
MS_U8 MST_DAC_4096x2160P_50_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_50_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0xC9/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x78/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x81/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x6F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x6F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x9F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x14/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0xD8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0xD7/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0xD8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0xD7/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  4096x2160P_50
//****************************************************
MS_U8 MST_DAC_4096x2160P_50_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  4096x2160P_50
//****************************************************
MS_U8 MST_DAC_4096x2160P_50_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  4096x2160P_50
//****************************************************
MS_U8 MST_DAC_4096x2160P_50_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_50_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  4096x2160P_50
//****************************************************
MS_U8 MST_DAC_4096x2160P_50_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_50_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  4096x2160P_50
//****************************************************
MS_U8 MST_DAC_4096x2160P_50_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_50_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  4096x2160P_50
//****************************************************
MS_U8 MST_DAC_4096x2160P_50_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_50_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  4096x2160P_50
//****************************************************
MS_U8 MST_DAC_4096x2160P_50_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_50_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  4096x2160P_50
//****************************************************
MS_U8 MST_DAC_4096x2160P_50_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_50_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  4096x2160P_50
//****************************************************
MS_U8 MST_DAC_4096x2160P_50_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_50_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  4096x2160P_50
//****************************************************
MS_U8 MST_DAC_4096x2160P_50_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_50_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  4096x2160P_50
//****************************************************
MS_U8 MST_DAC_4096x2160P_50_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT  4096x2160P_60
//****************************************************
MS_U8 MST_DAC_4096x2160P_60_INIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_60_INIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN_53_H), 0x01, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_CLK_GEN1_28_L), 0x0C, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_L), 0xFF, 0x88/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_30_H), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0F_H), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_L), 0xFF, 0x99/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_10_H), 0xFF, 0x19/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x0F, 0x02/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_06_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_07_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_08_H), 0xFF, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_09_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0A_H), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0B_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x80, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x20, 0x20/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x40, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_L), 0xFF, 0x50/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_31_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x07, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_L), 0x04, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_00_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0D_H), 0x10, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_0C_L), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_LPLL_03_L), 0x10, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_GPIO  4096x2160P_60
//****************************************************
MS_U8 MST_DAC_4096x2160P_60_INIT_GPIO_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_SC  4096x2160P_60
//****************************************************
MS_U8 MST_DAC_4096x2160P_60_INIT_SC_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_60_INIT_SC_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_1C_H), 0x01, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_10_H), 0xFF, 0x8C/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_L), 0xFF, 0xC9/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0D_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_L), 0xFF, 0x78/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_02_H), 0x17, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_L), 0xFF, 0x81/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_03_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_06_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_L), 0xFF, 0x6F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_07_H), 0x1F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_L), 0xFF, 0x6F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0B_H), 0x0F, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_L), 0xFF, 0x2F/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_0C_H), 0x1F, 0x11/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_01_L), 0xFF, 0x57/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_L), 0xFF, 0xD8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_04_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_L), 0xFF, 0xD7/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_05_H), 0x1F, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_L), 0xFF, 0xD8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_08_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_L), 0xFF, 0xD7/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_09_H), 0x1F, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_L), 0xFF, 0x18/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_VOP_BK10_5D_H), 0xFF, 0x12/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_SVOP_BK0F_57_H), 0x08, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_L), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_20_H), 0xFF, 0x04/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1F_L), 0xFF, 0xD2/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_L), 0xFF, 0xF8/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_19_H), 0xFF, 0x30/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_L), 0xFF, 0x08/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_21_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_L), 0xFF, 0x05/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_22_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_L), 0xFF, 0x13/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1A_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_L), 0xFF, 0x15/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_OP1_BK20_1B_H), 0x0F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_SC_444to420_BK6B_01_L), 0x03, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00 }
};

//****************************************************
// INIT_MOD  4096x2160P_60
//****************************************************
MS_U8 MST_DAC_4096x2160P_60_INIT_MOD_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDGEN  4096x2160P_60
//****************************************************
MS_U8 MST_DAC_4096x2160P_60_INIT_HDGEN_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
};

//****************************************************
// INIT_HDMITX_8BIT  4096x2160P_60
//****************************************************
MS_U8 MST_DAC_4096x2160P_60_INIT_HDMITX_8BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_60_INIT_HDMITX_8BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_8BIT_Divider  4096x2160P_60
//****************************************************
MS_U8 MST_DAC_4096x2160P_60_INIT_HDMITX_8BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_60_INIT_HDMITX_8BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT  4096x2160P_60
//****************************************************
MS_U8 MST_DAC_4096x2160P_60_INIT_HDMITX_10BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_60_INIT_HDMITX_10BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_10BIT_Divider  4096x2160P_60
//****************************************************
MS_U8 MST_DAC_4096x2160P_60_INIT_HDMITX_10BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_60_INIT_HDMITX_10BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT  4096x2160P_60
//****************************************************
MS_U8 MST_DAC_4096x2160P_60_INIT_HDMITX_12BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_60_INIT_HDMITX_12BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_12BIT_Divider  4096x2160P_60
//****************************************************
MS_U8 MST_DAC_4096x2160P_60_INIT_HDMITX_12BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_60_INIT_HDMITX_12BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT  4096x2160P_60
//****************************************************
MS_U8 MST_DAC_4096x2160P_60_INIT_HDMITX_16BIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_60_INIT_HDMITX_16BIT_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_L), 0xFF, 0xD1/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_46_H), 0xFF, 0x45/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_47_L), 0xFF, 0x17/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// INIT_HDMITX_16BIT_Divider  4096x2160P_60
//****************************************************
MS_U8 MST_DAC_4096x2160P_60_INIT_HDMITX_16BIT_Divider_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+DAC_TAB_4096x2160P_60_INIT_HDMITX_16BIT_Divider_NUMS]=
{                 // Reg           Mask  Value
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_L), 0xFF, 0x71/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_38_H), 0x1F, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_L), 0xFF, 0x80/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2B_H), 0xFF, 0x10/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2C_L), 0x0F, 0x01/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_L), 0xF0, 0xA0/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2E_H), 0x0F, 0x07/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_2F_L), 0xFF, 0x77/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_L), 0xFF, 0x40/*ALL*/, },
 { DRV_DAC_REG(REG_TC_HDMITX_PLL_34_H), 0xFF, 0x00/*ALL*/, },
 { DRV_DAC_REG(REG_TABLE_END)   , 0x00, 0x00,  }
};

//****************************************************
// Gamma  4096x2160P_60
//****************************************************
MS_U8 MST_DAC_4096x2160P_60_Gamma_TBL[][4] =
{               // Reg           Value  Value
 {  DRV_DAC_REG(REG_TABLE_END) , 0x00, 0x00  }
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
},
{
*MST_DAC_1920x2205P_24_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_1920x2205P_24_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_1920x2205P_24_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_1920x2205P_24_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_1920x2205P_24_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_1920x2205P_24_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_1920x2205P_24_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_1920x2205P_24_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_1920x2205P_24_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_1920x2205P_24_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_1920x2205P_24_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_1920x2205P_24_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_1920x2205P_24_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_1920x2205P_24_Gamma_TBL, DAC_TABTYPE_Gamma, 
},
{
*MST_DAC_1280x1470P_50_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_1280x1470P_50_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_1280x1470P_50_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_1280x1470P_50_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_1280x1470P_50_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_1280x1470P_50_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_1280x1470P_50_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_1280x1470P_50_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_1280x1470P_50_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_1280x1470P_50_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_1280x1470P_50_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_1280x1470P_50_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_1280x1470P_50_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_1280x1470P_50_Gamma_TBL, DAC_TABTYPE_Gamma, 
},
{
*MST_DAC_1280x1470P_60_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_1280x1470P_60_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_1280x1470P_60_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_1280x1470P_60_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_1280x1470P_60_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_1280x1470P_60_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_1280x1470P_60_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_1280x1470P_60_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_1280x1470P_60_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_1280x1470P_60_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_1280x1470P_60_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_1280x1470P_60_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_1280x1470P_60_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_1280x1470P_60_Gamma_TBL, DAC_TABTYPE_Gamma, 
},
{
*MST_DAC_3840x2160P_24_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_3840x2160P_24_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_3840x2160P_24_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_3840x2160P_24_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_3840x2160P_24_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_3840x2160P_24_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_3840x2160P_24_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_3840x2160P_24_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_3840x2160P_24_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_3840x2160P_24_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_3840x2160P_24_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_3840x2160P_24_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_3840x2160P_24_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_3840x2160P_24_Gamma_TBL, DAC_TABTYPE_Gamma, 
},
{
*MST_DAC_3840x2160P_25_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_3840x2160P_25_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_3840x2160P_25_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_3840x2160P_25_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_3840x2160P_25_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_3840x2160P_25_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_3840x2160P_25_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_3840x2160P_25_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_3840x2160P_25_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_3840x2160P_25_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_3840x2160P_25_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_3840x2160P_25_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_3840x2160P_25_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_3840x2160P_25_Gamma_TBL, DAC_TABTYPE_Gamma, 
},
{
*MST_DAC_3840x2160P_30_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_3840x2160P_30_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_3840x2160P_30_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_3840x2160P_30_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_3840x2160P_30_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_3840x2160P_30_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_3840x2160P_30_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_3840x2160P_30_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_3840x2160P_30_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_3840x2160P_30_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_3840x2160P_30_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_3840x2160P_30_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_3840x2160P_30_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_3840x2160P_30_Gamma_TBL, DAC_TABTYPE_Gamma, 
},
{
*MST_DAC_3840x2160P_50_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_3840x2160P_50_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_3840x2160P_50_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_3840x2160P_50_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_3840x2160P_50_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_3840x2160P_50_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_3840x2160P_50_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_3840x2160P_50_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_3840x2160P_50_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_3840x2160P_50_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_3840x2160P_50_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_3840x2160P_50_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_3840x2160P_50_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_3840x2160P_50_Gamma_TBL, DAC_TABTYPE_Gamma, 
},
{
*MST_DAC_3840x2160P_60_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_3840x2160P_60_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_3840x2160P_60_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_3840x2160P_60_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_3840x2160P_60_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_3840x2160P_60_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_3840x2160P_60_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_3840x2160P_60_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_3840x2160P_60_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_3840x2160P_60_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_3840x2160P_60_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_3840x2160P_60_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_3840x2160P_60_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_3840x2160P_60_Gamma_TBL, DAC_TABTYPE_Gamma, 
},
{
*MST_DAC_4096x2160P_24_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_4096x2160P_24_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_4096x2160P_24_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_4096x2160P_24_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_4096x2160P_24_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_4096x2160P_24_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_4096x2160P_24_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_4096x2160P_24_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_4096x2160P_24_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_4096x2160P_24_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_4096x2160P_24_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_4096x2160P_24_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_4096x2160P_24_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_4096x2160P_24_Gamma_TBL, DAC_TABTYPE_Gamma, 
},
{
*MST_DAC_4096x2160P_25_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_4096x2160P_25_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_4096x2160P_25_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_4096x2160P_25_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_4096x2160P_25_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_4096x2160P_25_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_4096x2160P_25_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_4096x2160P_25_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_4096x2160P_25_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_4096x2160P_25_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_4096x2160P_25_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_4096x2160P_25_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_4096x2160P_25_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_4096x2160P_25_Gamma_TBL, DAC_TABTYPE_Gamma, 
},
{
*MST_DAC_4096x2160P_30_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_4096x2160P_30_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_4096x2160P_30_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_4096x2160P_30_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_4096x2160P_30_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_4096x2160P_30_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_4096x2160P_30_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_4096x2160P_30_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_4096x2160P_30_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_4096x2160P_30_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_4096x2160P_30_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_4096x2160P_30_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_4096x2160P_30_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_4096x2160P_30_Gamma_TBL, DAC_TABTYPE_Gamma, 
},
{
*MST_DAC_4096x2160P_50_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_4096x2160P_50_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_4096x2160P_50_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_4096x2160P_50_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_4096x2160P_50_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_4096x2160P_50_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_4096x2160P_50_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_4096x2160P_50_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_4096x2160P_50_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_4096x2160P_50_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_4096x2160P_50_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_4096x2160P_50_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_4096x2160P_50_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_4096x2160P_50_Gamma_TBL, DAC_TABTYPE_Gamma, 
},
{
*MST_DAC_4096x2160P_60_INIT_TBL, DAC_TABTYPE_INIT, 
*MST_DAC_4096x2160P_60_INIT_GPIO_TBL, DAC_TABTYPE_INIT_GPIO, 
*MST_DAC_4096x2160P_60_INIT_SC_TBL, DAC_TABTYPE_INIT_SC, 
*MST_DAC_4096x2160P_60_INIT_MOD_TBL, DAC_TABTYPE_INIT_MOD, 
*MST_DAC_4096x2160P_60_INIT_HDGEN_TBL, DAC_TABTYPE_INIT_HDGEN, 
*MST_DAC_4096x2160P_60_INIT_HDMITX_8BIT_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT, 
*MST_DAC_4096x2160P_60_INIT_HDMITX_8BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_8BIT_Divider, 
*MST_DAC_4096x2160P_60_INIT_HDMITX_10BIT_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT, 
*MST_DAC_4096x2160P_60_INIT_HDMITX_10BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_10BIT_Divider, 
*MST_DAC_4096x2160P_60_INIT_HDMITX_12BIT_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT, 
*MST_DAC_4096x2160P_60_INIT_HDMITX_12BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_12BIT_Divider, 
*MST_DAC_4096x2160P_60_INIT_HDMITX_16BIT_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT, 
*MST_DAC_4096x2160P_60_INIT_HDMITX_16BIT_Divider_TBL, DAC_TABTYPE_INIT_HDMITX_16BIT_Divider, 
*MST_DAC_4096x2160P_60_Gamma_TBL, DAC_TABTYPE_Gamma, 
},
};

#endif
