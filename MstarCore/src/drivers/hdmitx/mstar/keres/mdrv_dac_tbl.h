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
// ("; MStar; Confidential; Information;") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

//****************************************************
// DAC Drive Chip           : Kenya_DAC_Driver
// DAC Excel CodeGen Version: 1.07
// DAC Excel SW      Version: 1.02
// DAC Excel update date    : 2012/10/18 21:07
//****************************************************

#ifndef _DRVDAC_TBL_H_
#define _DRVDAC_TBL_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define DRV_DAC_REG(reg)      ((reg>>8)&0xFF), (reg&0xFF)
#define REG_ADDR_SIZE          2
#define REG_MASK_SIZE          1
#define REG_TABLE_END          0xFFFF

#define _PK_L_(bank, addr)     ((MS_U16)(bank << 8) | (addr << 1))
#define _PK_H_(bank, addr)     ((MS_U16)(bank << 8) | ((addr << 1) + 1))

#define  REG_TC_GAMMA_BASE     0x0000
#define  REG_TC_CLK_GEN_BASE     0x0B00
#define  REG_TC_CLK_GEN1_BASE     0x3300
#define  REG_TC_CHIP_TOP_BASE     0x1E00
#define  REG_TC_LPLL_BASE     0x3100
#define  REG_TC_SC_VOP_BASE     0x2F00
#define  REG_TC_SC_OP1_BASE     0x2F00
#define  REG_TC_SC_SVOP_BASE     0x2F00
#define  REG_TC_SC_SCMI_BASE     0x2F00
#define  REG_TC_MOD_BASE     0x3200
#define  REG_TC_P2I_BASE     0x3000
#define  REG_TC_HDGEN_BASE     0x3000
#define  REG_TC_HDMITX_PLL_BASE     0x3000
#define  REG_TC_HDMITX_PM_BASE     0x2100
#define  REG_TC_DAC_PLL_BASE       0x1100

#if 0
typedef enum
{
    DAC_TABTYPE_GENERAL,
    DAC_TABTYPE_GPIO,
    DAC_TABTYPE_SCALER,
    DAC_TABTYPE_MOD,
    DAC_TABTYPE_HDGEN,
    DAC_TABTYPE_PLLSET,
    DAC_TABTYPE_GAMMA,
    DAC_TABTYPE_POWER_SEQUENCE_ON,
    DAC_TABTYPE_POWER_SEQUENCE_OFF,
} E_DAC_TAB_TYPE;
#endif

typedef enum
{
    DAC_TABTYPE_INIT,
    DAC_TABTYPE_INIT_GPIO,
    DAC_TABTYPE_INIT_SC,
    DAC_TABTYPE_INIT_MOD,
    DAC_TABTYPE_INIT_HDGEN,
    DAC_TABTYPE_INIT_HDMITX_8BIT,
    DAC_TABTYPE_INIT_HDMITX_8BIT_Divider,
    DAC_TABTYPE_INIT_HDMITX_10BIT,
    DAC_TABTYPE_INIT_HDMITX_10BIT_Divider,
    DAC_TABTYPE_INIT_HDMITX_12BIT,
    DAC_TABTYPE_INIT_HDMITX_12BIT_Divider,
    DAC_TABTYPE_Gamma,
    DAC_TABTYPE_SC1_INIT,
    DAC_TABTYPE_SC1_INIT_SC,
} E_DAC_TAB_TYPE;

typedef enum
{
    DAC_SIGNAL_POL,
    DAC_SIGNAL_VGH,
    DAC_SIGNAL_SOE,
    DAC_SIGNAL_VST,
    DAC_SIGNAL_GCLK,
    DAC_SIGNAL_NUMS,
} E_DAC_POWER_SEQUENCE_SIGNAL_TYPE;

typedef struct
{
    MS_U8           *pDacINITTab;
    E_DAC_TAB_TYPE   eINITtype;
    MS_U8           *pDacINIT_GPIOTab;
    E_DAC_TAB_TYPE   eINIT_GPIOtype;
    MS_U8           *pDacINIT_SCTab;
    E_DAC_TAB_TYPE   eINIT_SCtype;
    MS_U8           *pDacINIT_MODTab;
    E_DAC_TAB_TYPE   eINIT_MODtype;
    MS_U8           *pDacINIT_HDGENTab;
    E_DAC_TAB_TYPE   eINIT_HDGENtype;
    MS_U8           *pDacINIT_HDMITX_8BITTab;
    E_DAC_TAB_TYPE   eINIT_HDMITX_8BITtype;
    MS_U8           *pDacINIT_HDMITX_8BIT_DividerTab;
    E_DAC_TAB_TYPE   eINIT_HDMITX_8BIT_Dividertype;
    MS_U8           *pDacINIT_HDMITX_10BITTab;
    E_DAC_TAB_TYPE   eINIT_HDMITX_10BITtype;
    MS_U8           *pDacINIT_HDMITX_10BIT_DividerTab;
    E_DAC_TAB_TYPE   eINIT_HDMITX_10BIT_Dividertype;
    MS_U8           *pDacINIT_HDMITX_12BITTab;
    E_DAC_TAB_TYPE   eINIT_HDMITX_12BITtype;
    MS_U8           *pDacINIT_HDMITX_12BIT_DividerTab;
    E_DAC_TAB_TYPE   eINIT_HDMITX_12BIT_Dividertype;
    MS_U8           *pDacGammaTab;
    E_DAC_TAB_TYPE   eGammatype;
    MS_U8           *pDacSC1_INITTab;
    E_DAC_TAB_TYPE   eSC1_INITtype;
    MS_U8           *pDacSC1_INIT_SCTab;
    E_DAC_TAB_TYPE   eSC1_INIT_SCtype;
} DAC_TAB_INFO;

typedef enum
{
    DAC_PANEL_480I_60,
    DAC_PANEL_480P_60,
    DAC_PANEL_576I_50,
    DAC_PANEL_576P_50,
    DAC_PANEL_720P_50,
    DAC_PANEL_720P_60,
    DAC_PANEL_1080I_50,
    DAC_PANEL_1080I_60,
    DAC_PANEL_1080P_50,
    DAC_PANEL_1080P_60,
    DAC_PANEL_1080P_30,
    DAC_PANEL_1080P_25,
    DAC_PANEL_1080P_24,
    DAC_PANEL_640x480_60,
    DAC_PANEL_NUMS,
} E_DAC_PANEL_INDEX;

extern DAC_TAB_INFO DACMAP_Main[DAC_PANEL_NUMS];

typedef enum
{
    DAC_TAB_480I_60_INIT_ALL,
    DAC_TAB_480I_60_INIT_NUMS
} E_DAC_480I_60_INIT_TYPE;

typedef enum
{
    DAC_TAB_480I_60_INIT_GPIO_ALL,
    DAC_TAB_480I_60_INIT_GPIO_NUMS
} E_DAC_480I_60_INIT_GPIO_TYPE;

typedef enum
{
    DAC_TAB_480I_60_INIT_SC_ALL,
    DAC_TAB_480I_60_INIT_SC_NUMS
} E_DAC_480I_60_INIT_SC_TYPE;

typedef enum
{
    DAC_TAB_480I_60_INIT_MOD_ALL,
    DAC_TAB_480I_60_INIT_MOD_NUMS
} E_DAC_480I_60_INIT_MOD_TYPE;

typedef enum
{
    DAC_TAB_480I_60_INIT_HDGEN_ALL,
    DAC_TAB_480I_60_INIT_HDGEN_NUMS
} E_DAC_480I_60_INIT_HDGEN_TYPE;

typedef enum
{
    DAC_TAB_480I_60_INIT_HDMITX_8BIT_ALL,
    DAC_TAB_480I_60_INIT_HDMITX_8BIT_NUMS
} E_DAC_480I_60_INIT_HDMITX_8BIT_TYPE;

typedef enum
{
    DAC_TAB_480I_60_INIT_HDMITX_8BIT_Divider_ALL,
    DAC_TAB_480I_60_INIT_HDMITX_8BIT_Divider_NUMS
} E_DAC_480I_60_INIT_HDMITX_8BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_480I_60_INIT_HDMITX_10BIT_ALL,
    DAC_TAB_480I_60_INIT_HDMITX_10BIT_NUMS
} E_DAC_480I_60_INIT_HDMITX_10BIT_TYPE;

typedef enum
{
    DAC_TAB_480I_60_INIT_HDMITX_10BIT_Divider_ALL,
    DAC_TAB_480I_60_INIT_HDMITX_10BIT_Divider_NUMS
} E_DAC_480I_60_INIT_HDMITX_10BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_480I_60_INIT_HDMITX_12BIT_ALL,
    DAC_TAB_480I_60_INIT_HDMITX_12BIT_NUMS
} E_DAC_480I_60_INIT_HDMITX_12BIT_TYPE;

typedef enum
{
    DAC_TAB_480I_60_INIT_HDMITX_12BIT_Divider_ALL,
    DAC_TAB_480I_60_INIT_HDMITX_12BIT_Divider_NUMS
} E_DAC_480I_60_INIT_HDMITX_12BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_480I_60_SC1_INIT_ALL,
    DAC_TAB_480I_60_SC1_INIT_NUMS
} E_DAC_480I_60_SC1_INIT_TYPE;

typedef enum
{
    DAC_TAB_480I_60_SC1_INIT_SC_ALL,
    DAC_TAB_480I_60_SC1_INIT_SC_NUMS
} E_DAC_480I_60_SC1_INIT_SC_TYPE;

typedef enum
{
    DAC_TAB_480P_60_INIT_ALL,
    DAC_TAB_480P_60_INIT_NUMS
} E_DAC_480P_60_INIT_TYPE;

typedef enum
{
    DAC_TAB_480P_60_INIT_GPIO_ALL,
    DAC_TAB_480P_60_INIT_GPIO_NUMS
} E_DAC_480P_60_INIT_GPIO_TYPE;

typedef enum
{
    DAC_TAB_480P_60_INIT_SC_ALL,
    DAC_TAB_480P_60_INIT_SC_NUMS
} E_DAC_480P_60_INIT_SC_TYPE;

typedef enum
{
    DAC_TAB_480P_60_INIT_MOD_ALL,
    DAC_TAB_480P_60_INIT_MOD_NUMS
} E_DAC_480P_60_INIT_MOD_TYPE;

typedef enum
{
    DAC_TAB_480P_60_INIT_HDGEN_ALL,
    DAC_TAB_480P_60_INIT_HDGEN_NUMS
} E_DAC_480P_60_INIT_HDGEN_TYPE;

typedef enum
{
    DAC_TAB_480P_60_INIT_HDMITX_8BIT_ALL,
    DAC_TAB_480P_60_INIT_HDMITX_8BIT_NUMS
} E_DAC_480P_60_INIT_HDMITX_8BIT_TYPE;

typedef enum
{
    DAC_TAB_480P_60_INIT_HDMITX_8BIT_Divider_ALL,
    DAC_TAB_480P_60_INIT_HDMITX_8BIT_Divider_NUMS
} E_DAC_480P_60_INIT_HDMITX_8BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_480P_60_INIT_HDMITX_10BIT_ALL,
    DAC_TAB_480P_60_INIT_HDMITX_10BIT_NUMS
} E_DAC_480P_60_INIT_HDMITX_10BIT_TYPE;

typedef enum
{
    DAC_TAB_480P_60_INIT_HDMITX_10BIT_Divider_ALL,
    DAC_TAB_480P_60_INIT_HDMITX_10BIT_Divider_NUMS
} E_DAC_480P_60_INIT_HDMITX_10BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_480P_60_INIT_HDMITX_12BIT_ALL,
    DAC_TAB_480P_60_INIT_HDMITX_12BIT_NUMS
} E_DAC_480P_60_INIT_HDMITX_12BIT_TYPE;

typedef enum
{
    DAC_TAB_480P_60_INIT_HDMITX_12BIT_Divider_ALL,
    DAC_TAB_480P_60_INIT_HDMITX_12BIT_Divider_NUMS
} E_DAC_480P_60_INIT_HDMITX_12BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_576I_50_INIT_ALL,
    DAC_TAB_576I_50_INIT_NUMS
} E_DAC_576I_50_INIT_TYPE;

typedef enum
{
    DAC_TAB_576I_50_INIT_GPIO_ALL,
    DAC_TAB_576I_50_INIT_GPIO_NUMS
} E_DAC_576I_50_INIT_GPIO_TYPE;

typedef enum
{
    DAC_TAB_576I_50_INIT_SC_ALL,
    DAC_TAB_576I_50_INIT_SC_NUMS
} E_DAC_576I_50_INIT_SC_TYPE;

typedef enum
{
    DAC_TAB_576I_50_INIT_MOD_ALL,
    DAC_TAB_576I_50_INIT_MOD_NUMS
} E_DAC_576I_50_INIT_MOD_TYPE;

typedef enum
{
    DAC_TAB_576I_50_INIT_HDGEN_ALL,
    DAC_TAB_576I_50_INIT_HDGEN_NUMS
} E_DAC_576I_50_INIT_HDGEN_TYPE;

typedef enum
{
    DAC_TAB_576I_50_INIT_HDMITX_8BIT_ALL,
    DAC_TAB_576I_50_INIT_HDMITX_8BIT_NUMS
} E_DAC_576I_50_INIT_HDMITX_8BIT_TYPE;

typedef enum
{
    DAC_TAB_576I_50_INIT_HDMITX_8BIT_Divider_ALL,
    DAC_TAB_576I_50_INIT_HDMITX_8BIT_Divider_NUMS
} E_DAC_576I_50_INIT_HDMITX_8BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_576I_50_INIT_HDMITX_10BIT_ALL,
    DAC_TAB_576I_50_INIT_HDMITX_10BIT_NUMS
} E_DAC_576I_50_INIT_HDMITX_10BIT_TYPE;

typedef enum
{
    DAC_TAB_576I_50_INIT_HDMITX_10BIT_Divider_ALL,
    DAC_TAB_576I_50_INIT_HDMITX_10BIT_Divider_NUMS
} E_DAC_576I_50_INIT_HDMITX_10BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_576I_50_INIT_HDMITX_12BIT_ALL,
    DAC_TAB_576I_50_INIT_HDMITX_12BIT_NUMS
} E_DAC_576I_50_INIT_HDMITX_12BIT_TYPE;

typedef enum
{
    DAC_TAB_576I_50_INIT_HDMITX_12BIT_Divider_ALL,
    DAC_TAB_576I_50_INIT_HDMITX_12BIT_Divider_NUMS
} E_DAC_576I_50_INIT_HDMITX_12BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_576I_50_SC1_INIT_ALL,
    DAC_TAB_576I_50_SC1_INIT_NUMS
} E_DAC_576I_50_SC1_INIT_TYPE;

typedef enum
{
    DAC_TAB_576I_50_SC1_INIT_SC_ALL,
    DAC_TAB_576I_50_SC1_INIT_SC_NUMS
} E_DAC_576I_50_SC1_INIT_SC_TYPE;

typedef enum
{
    DAC_TAB_576P_50_INIT_ALL,
    DAC_TAB_576P_50_INIT_NUMS
} E_DAC_576P_50_INIT_TYPE;

typedef enum
{
    DAC_TAB_576P_50_INIT_GPIO_ALL,
    DAC_TAB_576P_50_INIT_GPIO_NUMS
} E_DAC_576P_50_INIT_GPIO_TYPE;

typedef enum
{
    DAC_TAB_576P_50_INIT_SC_ALL,
    DAC_TAB_576P_50_INIT_SC_NUMS
} E_DAC_576P_50_INIT_SC_TYPE;

typedef enum
{
    DAC_TAB_576P_50_INIT_MOD_ALL,
    DAC_TAB_576P_50_INIT_MOD_NUMS
} E_DAC_576P_50_INIT_MOD_TYPE;

typedef enum
{
    DAC_TAB_576P_50_INIT_HDGEN_ALL,
    DAC_TAB_576P_50_INIT_HDGEN_NUMS
} E_DAC_576P_50_INIT_HDGEN_TYPE;

typedef enum
{
    DAC_TAB_576P_50_INIT_HDMITX_8BIT_ALL,
    DAC_TAB_576P_50_INIT_HDMITX_8BIT_NUMS
} E_DAC_576P_50_INIT_HDMITX_8BIT_TYPE;

typedef enum
{
    DAC_TAB_576P_50_INIT_HDMITX_8BIT_Divider_ALL,
    DAC_TAB_576P_50_INIT_HDMITX_8BIT_Divider_NUMS
} E_DAC_576P_50_INIT_HDMITX_8BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_576P_50_INIT_HDMITX_10BIT_ALL,
    DAC_TAB_576P_50_INIT_HDMITX_10BIT_NUMS
} E_DAC_576P_50_INIT_HDMITX_10BIT_TYPE;

typedef enum
{
    DAC_TAB_576P_50_INIT_HDMITX_10BIT_Divider_ALL,
    DAC_TAB_576P_50_INIT_HDMITX_10BIT_Divider_NUMS
} E_DAC_576P_50_INIT_HDMITX_10BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_576P_50_INIT_HDMITX_12BIT_ALL,
    DAC_TAB_576P_50_INIT_HDMITX_12BIT_NUMS
} E_DAC_576P_50_INIT_HDMITX_12BIT_TYPE;

typedef enum
{
    DAC_TAB_576P_50_INIT_HDMITX_12BIT_Divider_ALL,
    DAC_TAB_576P_50_INIT_HDMITX_12BIT_Divider_NUMS
} E_DAC_576P_50_INIT_HDMITX_12BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_720P_50_INIT_ALL,
    DAC_TAB_720P_50_INIT_NUMS
} E_DAC_720P_50_INIT_TYPE;

typedef enum
{
    DAC_TAB_720P_50_INIT_GPIO_ALL,
    DAC_TAB_720P_50_INIT_GPIO_NUMS
} E_DAC_720P_50_INIT_GPIO_TYPE;

typedef enum
{
    DAC_TAB_720P_50_INIT_SC_ALL,
    DAC_TAB_720P_50_INIT_SC_NUMS
} E_DAC_720P_50_INIT_SC_TYPE;

typedef enum
{
    DAC_TAB_720P_50_INIT_MOD_ALL,
    DAC_TAB_720P_50_INIT_MOD_NUMS
} E_DAC_720P_50_INIT_MOD_TYPE;

typedef enum
{
    DAC_TAB_720P_50_INIT_HDGEN_ALL,
    DAC_TAB_720P_50_INIT_HDGEN_NUMS
} E_DAC_720P_50_INIT_HDGEN_TYPE;

typedef enum
{
    DAC_TAB_720P_50_INIT_HDMITX_8BIT_ALL,
    DAC_TAB_720P_50_INIT_HDMITX_8BIT_NUMS
} E_DAC_720P_50_INIT_HDMITX_8BIT_TYPE;

typedef enum
{
    DAC_TAB_720P_50_INIT_HDMITX_8BIT_Divider_ALL,
    DAC_TAB_720P_50_INIT_HDMITX_8BIT_Divider_NUMS
} E_DAC_720P_50_INIT_HDMITX_8BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_720P_50_INIT_HDMITX_10BIT_ALL,
    DAC_TAB_720P_50_INIT_HDMITX_10BIT_NUMS
} E_DAC_720P_50_INIT_HDMITX_10BIT_TYPE;

typedef enum
{
    DAC_TAB_720P_50_INIT_HDMITX_10BIT_Divider_ALL,
    DAC_TAB_720P_50_INIT_HDMITX_10BIT_Divider_NUMS
} E_DAC_720P_50_INIT_HDMITX_10BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_720P_50_INIT_HDMITX_12BIT_ALL,
    DAC_TAB_720P_50_INIT_HDMITX_12BIT_NUMS
} E_DAC_720P_50_INIT_HDMITX_12BIT_TYPE;

typedef enum
{
    DAC_TAB_720P_50_INIT_HDMITX_12BIT_Divider_ALL,
    DAC_TAB_720P_50_INIT_HDMITX_12BIT_Divider_NUMS
} E_DAC_720P_50_INIT_HDMITX_12BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_720P_60_INIT_ALL,
    DAC_TAB_720P_60_INIT_NUMS
} E_DAC_720P_60_INIT_TYPE;

typedef enum
{
    DAC_TAB_720P_60_INIT_GPIO_ALL,
    DAC_TAB_720P_60_INIT_GPIO_NUMS
} E_DAC_720P_60_INIT_GPIO_TYPE;

typedef enum
{
    DAC_TAB_720P_60_INIT_SC_ALL,
    DAC_TAB_720P_60_INIT_SC_NUMS
} E_DAC_720P_60_INIT_SC_TYPE;

typedef enum
{
    DAC_TAB_720P_60_INIT_MOD_ALL,
    DAC_TAB_720P_60_INIT_MOD_NUMS
} E_DAC_720P_60_INIT_MOD_TYPE;

typedef enum
{
    DAC_TAB_720P_60_INIT_HDGEN_ALL,
    DAC_TAB_720P_60_INIT_HDGEN_NUMS
} E_DAC_720P_60_INIT_HDGEN_TYPE;

typedef enum
{
    DAC_TAB_720P_60_INIT_HDMITX_8BIT_ALL,
    DAC_TAB_720P_60_INIT_HDMITX_8BIT_NUMS
} E_DAC_720P_60_INIT_HDMITX_8BIT_TYPE;

typedef enum
{
    DAC_TAB_720P_60_INIT_HDMITX_8BIT_Divider_ALL,
    DAC_TAB_720P_60_INIT_HDMITX_8BIT_Divider_NUMS
} E_DAC_720P_60_INIT_HDMITX_8BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_720P_60_INIT_HDMITX_10BIT_ALL,
    DAC_TAB_720P_60_INIT_HDMITX_10BIT_NUMS
} E_DAC_720P_60_INIT_HDMITX_10BIT_TYPE;

typedef enum
{
    DAC_TAB_720P_60_INIT_HDMITX_10BIT_Divider_ALL,
    DAC_TAB_720P_60_INIT_HDMITX_10BIT_Divider_NUMS
} E_DAC_720P_60_INIT_HDMITX_10BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_720P_60_INIT_HDMITX_12BIT_ALL,
    DAC_TAB_720P_60_INIT_HDMITX_12BIT_NUMS
} E_DAC_720P_60_INIT_HDMITX_12BIT_TYPE;

typedef enum
{
    DAC_TAB_720P_60_INIT_HDMITX_12BIT_Divider_ALL,
    DAC_TAB_720P_60_INIT_HDMITX_12BIT_Divider_NUMS
} E_DAC_720P_60_INIT_HDMITX_12BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_1080I_50_INIT_ALL,
    DAC_TAB_1080I_50_INIT_NUMS
} E_DAC_1080I_50_INIT_TYPE;

typedef enum
{
    DAC_TAB_1080I_50_INIT_GPIO_ALL,
    DAC_TAB_1080I_50_INIT_GPIO_NUMS
} E_DAC_1080I_50_INIT_GPIO_TYPE;

typedef enum
{
    DAC_TAB_1080I_50_INIT_SC_ALL,
    DAC_TAB_1080I_50_INIT_SC_NUMS
} E_DAC_1080I_50_INIT_SC_TYPE;

typedef enum
{
    DAC_TAB_1080I_50_INIT_MOD_ALL,
    DAC_TAB_1080I_50_INIT_MOD_NUMS
} E_DAC_1080I_50_INIT_MOD_TYPE;

typedef enum
{
    DAC_TAB_1080I_50_INIT_HDGEN_ALL,
    DAC_TAB_1080I_50_INIT_HDGEN_NUMS
} E_DAC_1080I_50_INIT_HDGEN_TYPE;

typedef enum
{
    DAC_TAB_1080I_50_INIT_HDMITX_8BIT_ALL,
    DAC_TAB_1080I_50_INIT_HDMITX_8BIT_NUMS
} E_DAC_1080I_50_INIT_HDMITX_8BIT_TYPE;

typedef enum
{
    DAC_TAB_1080I_50_INIT_HDMITX_8BIT_Divider_ALL,
    DAC_TAB_1080I_50_INIT_HDMITX_8BIT_Divider_NUMS
} E_DAC_1080I_50_INIT_HDMITX_8BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_1080I_50_INIT_HDMITX_10BIT_ALL,
    DAC_TAB_1080I_50_INIT_HDMITX_10BIT_NUMS
} E_DAC_1080I_50_INIT_HDMITX_10BIT_TYPE;

typedef enum
{
    DAC_TAB_1080I_50_INIT_HDMITX_10BIT_Divider_ALL,
    DAC_TAB_1080I_50_INIT_HDMITX_10BIT_Divider_NUMS
} E_DAC_1080I_50_INIT_HDMITX_10BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_1080I_50_INIT_HDMITX_12BIT_ALL,
    DAC_TAB_1080I_50_INIT_HDMITX_12BIT_NUMS
} E_DAC_1080I_50_INIT_HDMITX_12BIT_TYPE;

typedef enum
{
    DAC_TAB_1080I_50_INIT_HDMITX_12BIT_Divider_ALL,
    DAC_TAB_1080I_50_INIT_HDMITX_12BIT_Divider_NUMS
} E_DAC_1080I_50_INIT_HDMITX_12BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_1080I_60_INIT_ALL,
    DAC_TAB_1080I_60_INIT_NUMS
} E_DAC_1080I_60_INIT_TYPE;

typedef enum
{
    DAC_TAB_1080I_60_INIT_GPIO_ALL,
    DAC_TAB_1080I_60_INIT_GPIO_NUMS
} E_DAC_1080I_60_INIT_GPIO_TYPE;

typedef enum
{
    DAC_TAB_1080I_60_INIT_SC_ALL,
    DAC_TAB_1080I_60_INIT_SC_NUMS
} E_DAC_1080I_60_INIT_SC_TYPE;

typedef enum
{
    DAC_TAB_1080I_60_INIT_MOD_ALL,
    DAC_TAB_1080I_60_INIT_MOD_NUMS
} E_DAC_1080I_60_INIT_MOD_TYPE;

typedef enum
{
    DAC_TAB_1080I_60_INIT_HDGEN_ALL,
    DAC_TAB_1080I_60_INIT_HDGEN_NUMS
} E_DAC_1080I_60_INIT_HDGEN_TYPE;

typedef enum
{
    DAC_TAB_1080I_60_INIT_HDMITX_8BIT_ALL,
    DAC_TAB_1080I_60_INIT_HDMITX_8BIT_NUMS
} E_DAC_1080I_60_INIT_HDMITX_8BIT_TYPE;

typedef enum
{
    DAC_TAB_1080I_60_INIT_HDMITX_8BIT_Divider_ALL,
    DAC_TAB_1080I_60_INIT_HDMITX_8BIT_Divider_NUMS
} E_DAC_1080I_60_INIT_HDMITX_8BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_1080I_60_INIT_HDMITX_10BIT_ALL,
    DAC_TAB_1080I_60_INIT_HDMITX_10BIT_NUMS
} E_DAC_1080I_60_INIT_HDMITX_10BIT_TYPE;

typedef enum
{
    DAC_TAB_1080I_60_INIT_HDMITX_10BIT_Divider_ALL,
    DAC_TAB_1080I_60_INIT_HDMITX_10BIT_Divider_NUMS
} E_DAC_1080I_60_INIT_HDMITX_10BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_1080I_60_INIT_HDMITX_12BIT_ALL,
    DAC_TAB_1080I_60_INIT_HDMITX_12BIT_NUMS
} E_DAC_1080I_60_INIT_HDMITX_12BIT_TYPE;

typedef enum
{
    DAC_TAB_1080I_60_INIT_HDMITX_12BIT_Divider_ALL,
    DAC_TAB_1080I_60_INIT_HDMITX_12BIT_Divider_NUMS
} E_DAC_1080I_60_INIT_HDMITX_12BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_1080P_50_INIT_ALL,
    DAC_TAB_1080P_50_INIT_NUMS
} E_DAC_1080P_50_INIT_TYPE;

typedef enum
{
    DAC_TAB_1080P_50_INIT_GPIO_ALL,
    DAC_TAB_1080P_50_INIT_GPIO_NUMS
} E_DAC_1080P_50_INIT_GPIO_TYPE;

typedef enum
{
    DAC_TAB_1080P_50_INIT_SC_ALL,
    DAC_TAB_1080P_50_INIT_SC_NUMS
} E_DAC_1080P_50_INIT_SC_TYPE;

typedef enum
{
    DAC_TAB_1080P_50_INIT_MOD_ALL,
    DAC_TAB_1080P_50_INIT_MOD_NUMS
} E_DAC_1080P_50_INIT_MOD_TYPE;

typedef enum
{
    DAC_TAB_1080P_50_INIT_HDGEN_ALL,
    DAC_TAB_1080P_50_INIT_HDGEN_NUMS
} E_DAC_1080P_50_INIT_HDGEN_TYPE;

typedef enum
{
    DAC_TAB_1080P_50_INIT_HDMITX_8BIT_ALL,
    DAC_TAB_1080P_50_INIT_HDMITX_8BIT_NUMS
} E_DAC_1080P_50_INIT_HDMITX_8BIT_TYPE;

typedef enum
{
    DAC_TAB_1080P_50_INIT_HDMITX_8BIT_Divider_ALL,
    DAC_TAB_1080P_50_INIT_HDMITX_8BIT_Divider_NUMS
} E_DAC_1080P_50_INIT_HDMITX_8BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_1080P_50_INIT_HDMITX_10BIT_ALL,
    DAC_TAB_1080P_50_INIT_HDMITX_10BIT_NUMS
} E_DAC_1080P_50_INIT_HDMITX_10BIT_TYPE;

typedef enum
{
    DAC_TAB_1080P_50_INIT_HDMITX_10BIT_Divider_ALL,
    DAC_TAB_1080P_50_INIT_HDMITX_10BIT_Divider_NUMS
} E_DAC_1080P_50_INIT_HDMITX_10BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_1080P_50_INIT_HDMITX_12BIT_ALL,
    DAC_TAB_1080P_50_INIT_HDMITX_12BIT_NUMS
} E_DAC_1080P_50_INIT_HDMITX_12BIT_TYPE;

typedef enum
{
    DAC_TAB_1080P_50_INIT_HDMITX_12BIT_Divider_ALL,
    DAC_TAB_1080P_50_INIT_HDMITX_12BIT_Divider_NUMS
} E_DAC_1080P_50_INIT_HDMITX_12BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_1080P_60_INIT_ALL,
    DAC_TAB_1080P_60_INIT_NUMS
} E_DAC_1080P_60_INIT_TYPE;

typedef enum
{
    DAC_TAB_1080P_60_INIT_GPIO_ALL,
    DAC_TAB_1080P_60_INIT_GPIO_NUMS
} E_DAC_1080P_60_INIT_GPIO_TYPE;

typedef enum
{
    DAC_TAB_1080P_60_INIT_SC_ALL,
    DAC_TAB_1080P_60_INIT_SC_NUMS
} E_DAC_1080P_60_INIT_SC_TYPE;

typedef enum
{
    DAC_TAB_1080P_60_INIT_MOD_ALL,
    DAC_TAB_1080P_60_INIT_MOD_NUMS
} E_DAC_1080P_60_INIT_MOD_TYPE;

typedef enum
{
    DAC_TAB_1080P_60_INIT_HDGEN_ALL,
    DAC_TAB_1080P_60_INIT_HDGEN_NUMS
} E_DAC_1080P_60_INIT_HDGEN_TYPE;

typedef enum
{
    DAC_TAB_1080P_60_INIT_HDMITX_8BIT_ALL,
    DAC_TAB_1080P_60_INIT_HDMITX_8BIT_NUMS
} E_DAC_1080P_60_INIT_HDMITX_8BIT_TYPE;

typedef enum
{
    DAC_TAB_1080P_60_INIT_HDMITX_8BIT_Divider_ALL,
    DAC_TAB_1080P_60_INIT_HDMITX_8BIT_Divider_NUMS
} E_DAC_1080P_60_INIT_HDMITX_8BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_1080P_60_INIT_HDMITX_10BIT_ALL,
    DAC_TAB_1080P_60_INIT_HDMITX_10BIT_NUMS
} E_DAC_1080P_60_INIT_HDMITX_10BIT_TYPE;

typedef enum
{
    DAC_TAB_1080P_60_INIT_HDMITX_10BIT_Divider_ALL,
    DAC_TAB_1080P_60_INIT_HDMITX_10BIT_Divider_NUMS
} E_DAC_1080P_60_INIT_HDMITX_10BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_1080P_60_INIT_HDMITX_12BIT_ALL,
    DAC_TAB_1080P_60_INIT_HDMITX_12BIT_NUMS
} E_DAC_1080P_60_INIT_HDMITX_12BIT_TYPE;

typedef enum
{
    DAC_TAB_1080P_60_INIT_HDMITX_12BIT_Divider_ALL,
    DAC_TAB_1080P_60_INIT_HDMITX_12BIT_Divider_NUMS
} E_DAC_1080P_60_INIT_HDMITX_12BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_1080P_30_INIT_ALL,
    DAC_TAB_1080P_30_INIT_NUMS
} E_DAC_1080P_30_INIT_TYPE;

typedef enum
{
    DAC_TAB_1080P_30_INIT_GPIO_ALL,
    DAC_TAB_1080P_30_INIT_GPIO_NUMS
} E_DAC_1080P_30_INIT_GPIO_TYPE;

typedef enum
{
    DAC_TAB_1080P_30_INIT_SC_ALL,
    DAC_TAB_1080P_30_INIT_SC_NUMS
} E_DAC_1080P_30_INIT_SC_TYPE;

typedef enum
{
    DAC_TAB_1080P_30_INIT_MOD_ALL,
    DAC_TAB_1080P_30_INIT_MOD_NUMS
} E_DAC_1080P_30_INIT_MOD_TYPE;

typedef enum
{
    DAC_TAB_1080P_30_INIT_HDGEN_ALL,
    DAC_TAB_1080P_30_INIT_HDGEN_NUMS
} E_DAC_1080P_30_INIT_HDGEN_TYPE;

typedef enum
{
    DAC_TAB_1080P_30_INIT_HDMITX_8BIT_ALL,
    DAC_TAB_1080P_30_INIT_HDMITX_8BIT_NUMS
} E_DAC_1080P_30_INIT_HDMITX_8BIT_TYPE;

typedef enum
{
    DAC_TAB_1080P_30_INIT_HDMITX_8BIT_Divider_ALL,
    DAC_TAB_1080P_30_INIT_HDMITX_8BIT_Divider_NUMS
} E_DAC_1080P_30_INIT_HDMITX_8BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_1080P_30_INIT_HDMITX_10BIT_ALL,
    DAC_TAB_1080P_30_INIT_HDMITX_10BIT_NUMS
} E_DAC_1080P_30_INIT_HDMITX_10BIT_TYPE;

typedef enum
{
    DAC_TAB_1080P_30_INIT_HDMITX_10BIT_Divider_ALL,
    DAC_TAB_1080P_30_INIT_HDMITX_10BIT_Divider_NUMS
} E_DAC_1080P_30_INIT_HDMITX_10BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_1080P_30_INIT_HDMITX_12BIT_ALL,
    DAC_TAB_1080P_30_INIT_HDMITX_12BIT_NUMS
} E_DAC_1080P_30_INIT_HDMITX_12BIT_TYPE;

typedef enum
{
    DAC_TAB_1080P_30_INIT_HDMITX_12BIT_Divider_ALL,
    DAC_TAB_1080P_30_INIT_HDMITX_12BIT_Divider_NUMS
} E_DAC_1080P_30_INIT_HDMITX_12BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_1080P_25_INIT_ALL,
    DAC_TAB_1080P_25_INIT_NUMS
} E_DAC_1080P_25_INIT_TYPE;

typedef enum
{
    DAC_TAB_1080P_25_INIT_GPIO_ALL,
    DAC_TAB_1080P_25_INIT_GPIO_NUMS
} E_DAC_1080P_25_INIT_GPIO_TYPE;

typedef enum
{
    DAC_TAB_1080P_25_INIT_SC_ALL,
    DAC_TAB_1080P_25_INIT_SC_NUMS
} E_DAC_1080P_25_INIT_SC_TYPE;

typedef enum
{
    DAC_TAB_1080P_25_INIT_MOD_ALL,
    DAC_TAB_1080P_25_INIT_MOD_NUMS
} E_DAC_1080P_25_INIT_MOD_TYPE;

typedef enum
{
    DAC_TAB_1080P_25_INIT_HDGEN_ALL,
    DAC_TAB_1080P_25_INIT_HDGEN_NUMS
} E_DAC_1080P_25_INIT_HDGEN_TYPE;

typedef enum
{
    DAC_TAB_1080P_25_INIT_HDMITX_8BIT_ALL,
    DAC_TAB_1080P_25_INIT_HDMITX_8BIT_NUMS
} E_DAC_1080P_25_INIT_HDMITX_8BIT_TYPE;

typedef enum
{
    DAC_TAB_1080P_25_INIT_HDMITX_8BIT_Divider_ALL,
    DAC_TAB_1080P_25_INIT_HDMITX_8BIT_Divider_NUMS
} E_DAC_1080P_25_INIT_HDMITX_8BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_1080P_25_INIT_HDMITX_10BIT_ALL,
    DAC_TAB_1080P_25_INIT_HDMITX_10BIT_NUMS
} E_DAC_1080P_25_INIT_HDMITX_10BIT_TYPE;

typedef enum
{
    DAC_TAB_1080P_25_INIT_HDMITX_10BIT_Divider_ALL,
    DAC_TAB_1080P_25_INIT_HDMITX_10BIT_Divider_NUMS
} E_DAC_1080P_25_INIT_HDMITX_10BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_1080P_25_INIT_HDMITX_12BIT_ALL,
    DAC_TAB_1080P_25_INIT_HDMITX_12BIT_NUMS
} E_DAC_1080P_25_INIT_HDMITX_12BIT_TYPE;

typedef enum
{
    DAC_TAB_1080P_25_INIT_HDMITX_12BIT_Divider_ALL,
    DAC_TAB_1080P_25_INIT_HDMITX_12BIT_Divider_NUMS
} E_DAC_1080P_25_INIT_HDMITX_12BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_1080P_24_INIT_ALL,
    DAC_TAB_1080P_24_INIT_NUMS
} E_DAC_1080P_24_INIT_TYPE;

typedef enum
{
    DAC_TAB_1080P_24_INIT_GPIO_ALL,
    DAC_TAB_1080P_24_INIT_GPIO_NUMS
} E_DAC_1080P_24_INIT_GPIO_TYPE;

typedef enum
{
    DAC_TAB_1080P_24_INIT_SC_ALL,
    DAC_TAB_1080P_24_INIT_SC_NUMS
} E_DAC_1080P_24_INIT_SC_TYPE;

typedef enum
{
    DAC_TAB_1080P_24_INIT_MOD_ALL,
    DAC_TAB_1080P_24_INIT_MOD_NUMS
} E_DAC_1080P_24_INIT_MOD_TYPE;

typedef enum
{
    DAC_TAB_1080P_24_INIT_HDGEN_ALL,
    DAC_TAB_1080P_24_INIT_HDGEN_NUMS
} E_DAC_1080P_24_INIT_HDGEN_TYPE;

typedef enum
{
    DAC_TAB_1080P_24_INIT_HDMITX_8BIT_ALL,
    DAC_TAB_1080P_24_INIT_HDMITX_8BIT_NUMS
} E_DAC_1080P_24_INIT_HDMITX_8BIT_TYPE;

typedef enum
{
    DAC_TAB_1080P_24_INIT_HDMITX_8BIT_Divider_ALL,
    DAC_TAB_1080P_24_INIT_HDMITX_8BIT_Divider_NUMS
} E_DAC_1080P_24_INIT_HDMITX_8BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_1080P_24_INIT_HDMITX_10BIT_ALL,
    DAC_TAB_1080P_24_INIT_HDMITX_10BIT_NUMS
} E_DAC_1080P_24_INIT_HDMITX_10BIT_TYPE;

typedef enum
{
    DAC_TAB_1080P_24_INIT_HDMITX_10BIT_Divider_ALL,
    DAC_TAB_1080P_24_INIT_HDMITX_10BIT_Divider_NUMS
} E_DAC_1080P_24_INIT_HDMITX_10BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_1080P_24_INIT_HDMITX_12BIT_ALL,
    DAC_TAB_1080P_24_INIT_HDMITX_12BIT_NUMS
} E_DAC_1080P_24_INIT_HDMITX_12BIT_TYPE;

typedef enum
{
    DAC_TAB_1080P_24_INIT_HDMITX_12BIT_Divider_ALL,
    DAC_TAB_1080P_24_INIT_HDMITX_12BIT_Divider_NUMS
} E_DAC_1080P_24_INIT_HDMITX_12BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_640x480_60_INIT_ALL,
    DAC_TAB_640x480_60_INIT_NUMS
} E_DAC_640x480_60_INIT_TYPE;

typedef enum
{
    DAC_TAB_640x480_60_INIT_GPIO_ALL,
    DAC_TAB_640x480_60_INIT_GPIO_NUMS
} E_DAC_640x480_60_INIT_GPIO_TYPE;

typedef enum
{
    DAC_TAB_640x480_60_INIT_SC_ALL,
    DAC_TAB_640x480_60_INIT_SC_NUMS
} E_DAC_640x480_60_INIT_SC_TYPE;

typedef enum
{
    DAC_TAB_640x480_60_INIT_MOD_ALL,
    DAC_TAB_640x480_60_INIT_MOD_NUMS
} E_DAC_640x480_60_INIT_MOD_TYPE;

typedef enum
{
    DAC_TAB_640x480_60_INIT_HDGEN_ALL,
    DAC_TAB_640x480_60_INIT_HDGEN_NUMS
} E_DAC_640x480_60_INIT_HDGEN_TYPE;

typedef enum
{
    DAC_TAB_640x480_60_INIT_HDMITX_8BIT_ALL,
    DAC_TAB_640x480_60_INIT_HDMITX_8BIT_NUMS
} E_DAC_640x480_60_INIT_HDMITX_8BIT_TYPE;

typedef enum
{
    DAC_TAB_640x480_60_INIT_HDMITX_8BIT_Divider_ALL,
    DAC_TAB_640x480_60_INIT_HDMITX_8BIT_Divider_NUMS
} E_DAC_640x480_60_INIT_HDMITX_8BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_640x480_60_INIT_HDMITX_10BIT_ALL,
    DAC_TAB_640x480_60_INIT_HDMITX_10BIT_NUMS
} E_DAC_640x480_60_INIT_HDMITX_10BIT_TYPE;

typedef enum
{
    DAC_TAB_640x480_60_INIT_HDMITX_10BIT_Divider_ALL,
    DAC_TAB_640x480_60_INIT_HDMITX_10BIT_Divider_NUMS
} E_DAC_640x480_60_INIT_HDMITX_10BIT_Divider_TYPE;

typedef enum
{
    DAC_TAB_640x480_60_INIT_HDMITX_12BIT_ALL,
    DAC_TAB_640x480_60_INIT_HDMITX_12BIT_NUMS
} E_DAC_640x480_60_INIT_HDMITX_12BIT_TYPE;

typedef enum
{
    DAC_TAB_640x480_60_INIT_HDMITX_12BIT_Divider_ALL,
    DAC_TAB_640x480_60_INIT_HDMITX_12BIT_Divider_NUMS
} E_DAC_640x480_60_INIT_HDMITX_12BIT_Divider_TYPE;

//-------------------------------------------------------------------------------------------------
// register define used for TCON table
//-------------------------------------------------------------------------------------------------

#define  REG_TC_GAMMA_00           (REG_TC_GAMMA_BASE + 0x00)
#define  REG_TC_GAMMA_01           (REG_TC_GAMMA_BASE + 0x01)
#define  REG_TC_GAMMA_02           (REG_TC_GAMMA_BASE + 0x02)
#define  REG_TC_GAMMA_03           (REG_TC_GAMMA_BASE + 0x03)
#define  REG_TC_GAMMA_04           (REG_TC_GAMMA_BASE + 0x04)
#define  REG_TC_GAMMA_05           (REG_TC_GAMMA_BASE + 0x05)
#define  REG_TC_GAMMA_06           (REG_TC_GAMMA_BASE + 0x06)
#define  REG_TC_GAMMA_07           (REG_TC_GAMMA_BASE + 0x07)
#define  REG_TC_GAMMA_08           (REG_TC_GAMMA_BASE + 0x08)
#define  REG_TC_GAMMA_09           (REG_TC_GAMMA_BASE + 0x09)
#define  REG_TC_GAMMA_0A           (REG_TC_GAMMA_BASE + 0x0A)
#define  REG_TC_GAMMA_0B           (REG_TC_GAMMA_BASE + 0x0B)
#define  REG_TC_GAMMA_0C           (REG_TC_GAMMA_BASE + 0x0C)
#define  REG_TC_GAMMA_0D           (REG_TC_GAMMA_BASE + 0x0D)
#define  REG_TC_GAMMA_0E           (REG_TC_GAMMA_BASE + 0x0E)
#define  REG_TC_GAMMA_0F           (REG_TC_GAMMA_BASE + 0x0F)
#define  REG_TC_GAMMA_10           (REG_TC_GAMMA_BASE + 0x10)
#define  REG_TC_GAMMA_11           (REG_TC_GAMMA_BASE + 0x11)
#define  REG_TC_GAMMA_12           (REG_TC_GAMMA_BASE + 0x12)
#define  REG_TC_GAMMA_13           (REG_TC_GAMMA_BASE + 0x13)
#define  REG_TC_GAMMA_14           (REG_TC_GAMMA_BASE + 0x14)
#define  REG_TC_GAMMA_15           (REG_TC_GAMMA_BASE + 0x15)
#define  REG_TC_GAMMA_16           (REG_TC_GAMMA_BASE + 0x16)
#define  REG_TC_GAMMA_17           (REG_TC_GAMMA_BASE + 0x17)
#define  REG_TC_GAMMA_18           (REG_TC_GAMMA_BASE + 0x18)
#define  REG_TC_GAMMA_19           (REG_TC_GAMMA_BASE + 0x19)
#define  REG_TC_GAMMA_1A           (REG_TC_GAMMA_BASE + 0x1A)
#define  REG_TC_GAMMA_1B           (REG_TC_GAMMA_BASE + 0x1B)
#define  REG_TC_GAMMA_1C           (REG_TC_GAMMA_BASE + 0x1C)
#define  REG_TC_GAMMA_1D           (REG_TC_GAMMA_BASE + 0x1D)
#define  REG_TC_GAMMA_1E           (REG_TC_GAMMA_BASE + 0x1E)
#define  REG_TC_GAMMA_1F           (REG_TC_GAMMA_BASE + 0x1F)
#define  REG_TC_GAMMA_20           (REG_TC_GAMMA_BASE + 0x20)
#define  REG_TC_GAMMA_21           (REG_TC_GAMMA_BASE + 0x21)
#define  REG_TC_GAMMA_22           (REG_TC_GAMMA_BASE + 0x22)
#define  REG_TC_GAMMA_23           (REG_TC_GAMMA_BASE + 0x23)
#define  REG_TC_GAMMA_24           (REG_TC_GAMMA_BASE + 0x24)
#define  REG_TC_GAMMA_25           (REG_TC_GAMMA_BASE + 0x25)
#define  REG_TC_GAMMA_26           (REG_TC_GAMMA_BASE + 0x26)
#define  REG_TC_GAMMA_27           (REG_TC_GAMMA_BASE + 0x27)
#define  REG_TC_GAMMA_28           (REG_TC_GAMMA_BASE + 0x28)
#define  REG_TC_GAMMA_29           (REG_TC_GAMMA_BASE + 0x29)
#define  REG_TC_GAMMA_2A           (REG_TC_GAMMA_BASE + 0x2A)
#define  REG_TC_GAMMA_2B           (REG_TC_GAMMA_BASE + 0x2B)
#define  REG_TC_GAMMA_2C           (REG_TC_GAMMA_BASE + 0x2C)
#define  REG_TC_GAMMA_2D           (REG_TC_GAMMA_BASE + 0x2D)
#define  REG_TC_GAMMA_2E           (REG_TC_GAMMA_BASE + 0x2E)
#define  REG_TC_GAMMA_2F           (REG_TC_GAMMA_BASE + 0x2F)
#define  REG_TC_GAMMA_30           (REG_TC_GAMMA_BASE + 0x30)
#define  REG_TC_GAMMA_31           (REG_TC_GAMMA_BASE + 0x31)
#define  REG_TC_GAMMA_32           (REG_TC_GAMMA_BASE + 0x32)
#define  REG_TC_GAMMA_33           (REG_TC_GAMMA_BASE + 0x33)
#define  REG_TC_GAMMA_34           (REG_TC_GAMMA_BASE + 0x34)
#define  REG_TC_GAMMA_35           (REG_TC_GAMMA_BASE + 0x35)
#define  REG_TC_GAMMA_36           (REG_TC_GAMMA_BASE + 0x36)
#define  REG_TC_GAMMA_37           (REG_TC_GAMMA_BASE + 0x37)
#define  REG_TC_GAMMA_38           (REG_TC_GAMMA_BASE + 0x38)
#define  REG_TC_GAMMA_39           (REG_TC_GAMMA_BASE + 0x39)
#define  REG_TC_GAMMA_3A           (REG_TC_GAMMA_BASE + 0x3A)
#define  REG_TC_GAMMA_3B           (REG_TC_GAMMA_BASE + 0x3B)
#define  REG_TC_GAMMA_3C           (REG_TC_GAMMA_BASE + 0x3C)
#define  REG_TC_GAMMA_3D           (REG_TC_GAMMA_BASE + 0x3D)
#define  REG_TC_GAMMA_3E           (REG_TC_GAMMA_BASE + 0x3E)
#define  REG_TC_GAMMA_3F           (REG_TC_GAMMA_BASE + 0x3F)

#define  REG_TC_CLK_GEN_00_L       (REG_TC_CLK_GEN_BASE + 0x00)
#define  REG_TC_CLK_GEN_00_H       (REG_TC_CLK_GEN_BASE + 0x01)
#define  REG_TC_CLK_GEN_01_L       (REG_TC_CLK_GEN_BASE + 0x02)
#define  REG_TC_CLK_GEN_01_H       (REG_TC_CLK_GEN_BASE + 0x03)
#define  REG_TC_CLK_GEN_02_L       (REG_TC_CLK_GEN_BASE + 0x04)
#define  REG_TC_CLK_GEN_02_H       (REG_TC_CLK_GEN_BASE + 0x05)
#define  REG_TC_CLK_GEN_03_L       (REG_TC_CLK_GEN_BASE + 0x06)
#define  REG_TC_CLK_GEN_03_H       (REG_TC_CLK_GEN_BASE + 0x07)
#define  REG_TC_CLK_GEN_04_L       (REG_TC_CLK_GEN_BASE + 0x08)
#define  REG_TC_CLK_GEN_04_H       (REG_TC_CLK_GEN_BASE + 0x09)
#define  REG_TC_CLK_GEN_05_L       (REG_TC_CLK_GEN_BASE + 0x0A)
#define  REG_TC_CLK_GEN_05_H       (REG_TC_CLK_GEN_BASE + 0x0B)
#define  REG_TC_CLK_GEN_06_L       (REG_TC_CLK_GEN_BASE + 0x0C)
#define  REG_TC_CLK_GEN_06_H       (REG_TC_CLK_GEN_BASE + 0x0D)
#define  REG_TC_CLK_GEN_07_L       (REG_TC_CLK_GEN_BASE + 0x0E)
#define  REG_TC_CLK_GEN_07_H       (REG_TC_CLK_GEN_BASE + 0x0F)
#define  REG_TC_CLK_GEN_08_L       (REG_TC_CLK_GEN_BASE + 0x10)
#define  REG_TC_CLK_GEN_08_H       (REG_TC_CLK_GEN_BASE + 0x11)
#define  REG_TC_CLK_GEN_09_L       (REG_TC_CLK_GEN_BASE + 0x12)
#define  REG_TC_CLK_GEN_09_H       (REG_TC_CLK_GEN_BASE + 0x13)
#define  REG_TC_CLK_GEN_0A_L       (REG_TC_CLK_GEN_BASE + 0x14)
#define  REG_TC_CLK_GEN_0A_H       (REG_TC_CLK_GEN_BASE + 0x15)
#define  REG_TC_CLK_GEN_0B_L       (REG_TC_CLK_GEN_BASE + 0x16)
#define  REG_TC_CLK_GEN_0B_H       (REG_TC_CLK_GEN_BASE + 0x17)
#define  REG_TC_CLK_GEN_0C_L       (REG_TC_CLK_GEN_BASE + 0x18)
#define  REG_TC_CLK_GEN_0C_H       (REG_TC_CLK_GEN_BASE + 0x19)
#define  REG_TC_CLK_GEN_0D_L       (REG_TC_CLK_GEN_BASE + 0x1A)
#define  REG_TC_CLK_GEN_0D_H       (REG_TC_CLK_GEN_BASE + 0x1B)
#define  REG_TC_CLK_GEN_0E_L       (REG_TC_CLK_GEN_BASE + 0x1C)
#define  REG_TC_CLK_GEN_0E_H       (REG_TC_CLK_GEN_BASE + 0x1D)
#define  REG_TC_CLK_GEN_0F_L       (REG_TC_CLK_GEN_BASE + 0x1E)
#define  REG_TC_CLK_GEN_0F_H       (REG_TC_CLK_GEN_BASE + 0x1F)
#define  REG_TC_CLK_GEN_10_L       (REG_TC_CLK_GEN_BASE + 0x20)
#define  REG_TC_CLK_GEN_10_H       (REG_TC_CLK_GEN_BASE + 0x21)
#define  REG_TC_CLK_GEN_11_L       (REG_TC_CLK_GEN_BASE + 0x22)
#define  REG_TC_CLK_GEN_11_H       (REG_TC_CLK_GEN_BASE + 0x23)
#define  REG_TC_CLK_GEN_12_L       (REG_TC_CLK_GEN_BASE + 0x24)
#define  REG_TC_CLK_GEN_12_H       (REG_TC_CLK_GEN_BASE + 0x25)
#define  REG_TC_CLK_GEN_13_L       (REG_TC_CLK_GEN_BASE + 0x26)
#define  REG_TC_CLK_GEN_13_H       (REG_TC_CLK_GEN_BASE + 0x27)
#define  REG_TC_CLK_GEN_14_L       (REG_TC_CLK_GEN_BASE + 0x28)
#define  REG_TC_CLK_GEN_14_H       (REG_TC_CLK_GEN_BASE + 0x29)
#define  REG_TC_CLK_GEN_15_L       (REG_TC_CLK_GEN_BASE + 0x2A)
#define  REG_TC_CLK_GEN_15_H       (REG_TC_CLK_GEN_BASE + 0x2B)
#define  REG_TC_CLK_GEN_16_L       (REG_TC_CLK_GEN_BASE + 0x2C)
#define  REG_TC_CLK_GEN_16_H       (REG_TC_CLK_GEN_BASE + 0x2D)
#define  REG_TC_CLK_GEN_17_L       (REG_TC_CLK_GEN_BASE + 0x2E)
#define  REG_TC_CLK_GEN_17_H       (REG_TC_CLK_GEN_BASE + 0x2F)
#define  REG_TC_CLK_GEN_18_L       (REG_TC_CLK_GEN_BASE + 0x30)
#define  REG_TC_CLK_GEN_18_H       (REG_TC_CLK_GEN_BASE + 0x31)
#define  REG_TC_CLK_GEN_19_L       (REG_TC_CLK_GEN_BASE + 0x32)
#define  REG_TC_CLK_GEN_19_H       (REG_TC_CLK_GEN_BASE + 0x33)
#define  REG_TC_CLK_GEN_1A_L       (REG_TC_CLK_GEN_BASE + 0x34)
#define  REG_TC_CLK_GEN_1A_H       (REG_TC_CLK_GEN_BASE + 0x35)
#define  REG_TC_CLK_GEN_1B_L       (REG_TC_CLK_GEN_BASE + 0x36)
#define  REG_TC_CLK_GEN_1B_H       (REG_TC_CLK_GEN_BASE + 0x37)
#define  REG_TC_CLK_GEN_1C_L       (REG_TC_CLK_GEN_BASE + 0x38)
#define  REG_TC_CLK_GEN_1C_H       (REG_TC_CLK_GEN_BASE + 0x39)
#define  REG_TC_CLK_GEN_1D_L       (REG_TC_CLK_GEN_BASE + 0x3A)
#define  REG_TC_CLK_GEN_1D_H       (REG_TC_CLK_GEN_BASE + 0x3B)
#define  REG_TC_CLK_GEN_1E_L       (REG_TC_CLK_GEN_BASE + 0x3C)
#define  REG_TC_CLK_GEN_1E_H       (REG_TC_CLK_GEN_BASE + 0x3D)
#define  REG_TC_CLK_GEN_1F_L       (REG_TC_CLK_GEN_BASE + 0x3E)
#define  REG_TC_CLK_GEN_1F_H       (REG_TC_CLK_GEN_BASE + 0x3F)
#define  REG_TC_CLK_GEN_20_L       (REG_TC_CLK_GEN_BASE + 0x40)
#define  REG_TC_CLK_GEN_20_H       (REG_TC_CLK_GEN_BASE + 0x41)
#define  REG_TC_CLK_GEN_21_L       (REG_TC_CLK_GEN_BASE + 0x42)
#define  REG_TC_CLK_GEN_21_H       (REG_TC_CLK_GEN_BASE + 0x43)
#define  REG_TC_CLK_GEN_22_L       (REG_TC_CLK_GEN_BASE + 0x44)
#define  REG_TC_CLK_GEN_22_H       (REG_TC_CLK_GEN_BASE + 0x45)
#define  REG_TC_CLK_GEN_23_L       (REG_TC_CLK_GEN_BASE + 0x46)
#define  REG_TC_CLK_GEN_23_H       (REG_TC_CLK_GEN_BASE + 0x47)
#define  REG_TC_CLK_GEN_24_L       (REG_TC_CLK_GEN_BASE + 0x48)
#define  REG_TC_CLK_GEN_24_H       (REG_TC_CLK_GEN_BASE + 0x49)
#define  REG_TC_CLK_GEN_25_L       (REG_TC_CLK_GEN_BASE + 0x4A)
#define  REG_TC_CLK_GEN_25_H       (REG_TC_CLK_GEN_BASE + 0x4B)
#define  REG_TC_CLK_GEN_26_L       (REG_TC_CLK_GEN_BASE + 0x4C)
#define  REG_TC_CLK_GEN_26_H       (REG_TC_CLK_GEN_BASE + 0x4D)
#define  REG_TC_CLK_GEN_27_L       (REG_TC_CLK_GEN_BASE + 0x4E)
#define  REG_TC_CLK_GEN_27_H       (REG_TC_CLK_GEN_BASE + 0x4F)
#define  REG_TC_CLK_GEN_28_L       (REG_TC_CLK_GEN_BASE + 0x50)
#define  REG_TC_CLK_GEN_28_H       (REG_TC_CLK_GEN_BASE + 0x51)
#define  REG_TC_CLK_GEN_29_L       (REG_TC_CLK_GEN_BASE + 0x52)
#define  REG_TC_CLK_GEN_29_H       (REG_TC_CLK_GEN_BASE + 0x53)
#define  REG_TC_CLK_GEN_2A_L       (REG_TC_CLK_GEN_BASE + 0x54)
#define  REG_TC_CLK_GEN_2A_H       (REG_TC_CLK_GEN_BASE + 0x55)
#define  REG_TC_CLK_GEN_2B_L       (REG_TC_CLK_GEN_BASE + 0x56)
#define  REG_TC_CLK_GEN_2B_H       (REG_TC_CLK_GEN_BASE + 0x57)
#define  REG_TC_CLK_GEN_2C_L       (REG_TC_CLK_GEN_BASE + 0x58)
#define  REG_TC_CLK_GEN_2C_H       (REG_TC_CLK_GEN_BASE + 0x59)
#define  REG_TC_CLK_GEN_2D_L       (REG_TC_CLK_GEN_BASE + 0x5A)
#define  REG_TC_CLK_GEN_2D_H       (REG_TC_CLK_GEN_BASE + 0x5B)
#define  REG_TC_CLK_GEN_2E_L       (REG_TC_CLK_GEN_BASE + 0x5C)
#define  REG_TC_CLK_GEN_2E_H       (REG_TC_CLK_GEN_BASE + 0x5D)
#define  REG_TC_CLK_GEN_2F_L       (REG_TC_CLK_GEN_BASE + 0x5E)
#define  REG_TC_CLK_GEN_2F_H       (REG_TC_CLK_GEN_BASE + 0x5F)
#define  REG_TC_CLK_GEN_30_L       (REG_TC_CLK_GEN_BASE + 0x60)
#define  REG_TC_CLK_GEN_30_H       (REG_TC_CLK_GEN_BASE + 0x61)
#define  REG_TC_CLK_GEN_31_L       (REG_TC_CLK_GEN_BASE + 0x62)
#define  REG_TC_CLK_GEN_31_H       (REG_TC_CLK_GEN_BASE + 0x63)
#define  REG_TC_CLK_GEN_32_L       (REG_TC_CLK_GEN_BASE + 0x64)
#define  REG_TC_CLK_GEN_32_H       (REG_TC_CLK_GEN_BASE + 0x65)
#define  REG_TC_CLK_GEN_33_L       (REG_TC_CLK_GEN_BASE + 0x66)
#define  REG_TC_CLK_GEN_33_H       (REG_TC_CLK_GEN_BASE + 0x67)
#define  REG_TC_CLK_GEN_34_L       (REG_TC_CLK_GEN_BASE + 0x68)
#define  REG_TC_CLK_GEN_34_H       (REG_TC_CLK_GEN_BASE + 0x69)
#define  REG_TC_CLK_GEN_35_L       (REG_TC_CLK_GEN_BASE + 0x6A)
#define  REG_TC_CLK_GEN_35_H       (REG_TC_CLK_GEN_BASE + 0x6B)
#define  REG_TC_CLK_GEN_36_L       (REG_TC_CLK_GEN_BASE + 0x6C)
#define  REG_TC_CLK_GEN_36_H       (REG_TC_CLK_GEN_BASE + 0x6D)
#define  REG_TC_CLK_GEN_37_L       (REG_TC_CLK_GEN_BASE + 0x6E)
#define  REG_TC_CLK_GEN_37_H       (REG_TC_CLK_GEN_BASE + 0x6F)
#define  REG_TC_CLK_GEN_38_L       (REG_TC_CLK_GEN_BASE + 0x70)
#define  REG_TC_CLK_GEN_38_H       (REG_TC_CLK_GEN_BASE + 0x71)
#define  REG_TC_CLK_GEN_39_L       (REG_TC_CLK_GEN_BASE + 0x72)
#define  REG_TC_CLK_GEN_39_H       (REG_TC_CLK_GEN_BASE + 0x73)
#define  REG_TC_CLK_GEN_3A_L       (REG_TC_CLK_GEN_BASE + 0x74)
#define  REG_TC_CLK_GEN_3A_H       (REG_TC_CLK_GEN_BASE + 0x75)
#define  REG_TC_CLK_GEN_3B_L       (REG_TC_CLK_GEN_BASE + 0x76)
#define  REG_TC_CLK_GEN_3B_H       (REG_TC_CLK_GEN_BASE + 0x77)
#define  REG_TC_CLK_GEN_3C_L       (REG_TC_CLK_GEN_BASE + 0x78)
#define  REG_TC_CLK_GEN_3C_H       (REG_TC_CLK_GEN_BASE + 0x79)
#define  REG_TC_CLK_GEN_3D_L       (REG_TC_CLK_GEN_BASE + 0x7A)
#define  REG_TC_CLK_GEN_3D_H       (REG_TC_CLK_GEN_BASE + 0x7B)
#define  REG_TC_CLK_GEN_3E_L       (REG_TC_CLK_GEN_BASE + 0x7C)
#define  REG_TC_CLK_GEN_3E_H       (REG_TC_CLK_GEN_BASE + 0x7D)
#define  REG_TC_CLK_GEN_3F_L       (REG_TC_CLK_GEN_BASE + 0x7E)
#define  REG_TC_CLK_GEN_3F_H       (REG_TC_CLK_GEN_BASE + 0x7F)
#define  REG_TC_CLK_GEN_40_L       (REG_TC_CLK_GEN_BASE + 0x80)
#define  REG_TC_CLK_GEN_40_H       (REG_TC_CLK_GEN_BASE + 0x81)
#define  REG_TC_CLK_GEN_41_L       (REG_TC_CLK_GEN_BASE + 0x82)
#define  REG_TC_CLK_GEN_41_H       (REG_TC_CLK_GEN_BASE + 0x83)
#define  REG_TC_CLK_GEN_42_L       (REG_TC_CLK_GEN_BASE + 0x84)
#define  REG_TC_CLK_GEN_42_H       (REG_TC_CLK_GEN_BASE + 0x85)
#define  REG_TC_CLK_GEN_43_L       (REG_TC_CLK_GEN_BASE + 0x86)
#define  REG_TC_CLK_GEN_43_H       (REG_TC_CLK_GEN_BASE + 0x87)
#define  REG_TC_CLK_GEN_44_L       (REG_TC_CLK_GEN_BASE + 0x88)
#define  REG_TC_CLK_GEN_44_H       (REG_TC_CLK_GEN_BASE + 0x89)
#define  REG_TC_CLK_GEN_45_L       (REG_TC_CLK_GEN_BASE + 0x8A)
#define  REG_TC_CLK_GEN_45_H       (REG_TC_CLK_GEN_BASE + 0x8B)
#define  REG_TC_CLK_GEN_46_L       (REG_TC_CLK_GEN_BASE + 0x8C)
#define  REG_TC_CLK_GEN_46_H       (REG_TC_CLK_GEN_BASE + 0x8D)
#define  REG_TC_CLK_GEN_47_L       (REG_TC_CLK_GEN_BASE + 0x8E)
#define  REG_TC_CLK_GEN_47_H       (REG_TC_CLK_GEN_BASE + 0x8F)
#define  REG_TC_CLK_GEN_48_L       (REG_TC_CLK_GEN_BASE + 0x90)
#define  REG_TC_CLK_GEN_48_H       (REG_TC_CLK_GEN_BASE + 0x91)
#define  REG_TC_CLK_GEN_49_L       (REG_TC_CLK_GEN_BASE + 0x92)
#define  REG_TC_CLK_GEN_49_H       (REG_TC_CLK_GEN_BASE + 0x93)
#define  REG_TC_CLK_GEN_4A_L       (REG_TC_CLK_GEN_BASE + 0x94)
#define  REG_TC_CLK_GEN_4A_H       (REG_TC_CLK_GEN_BASE + 0x95)
#define  REG_TC_CLK_GEN_4B_L       (REG_TC_CLK_GEN_BASE + 0x96)
#define  REG_TC_CLK_GEN_4B_H       (REG_TC_CLK_GEN_BASE + 0x97)
#define  REG_TC_CLK_GEN_4C_L       (REG_TC_CLK_GEN_BASE + 0x98)
#define  REG_TC_CLK_GEN_4C_H       (REG_TC_CLK_GEN_BASE + 0x99)
#define  REG_TC_CLK_GEN_4D_L       (REG_TC_CLK_GEN_BASE + 0x9A)
#define  REG_TC_CLK_GEN_4D_H       (REG_TC_CLK_GEN_BASE + 0x9B)
#define  REG_TC_CLK_GEN_4E_L       (REG_TC_CLK_GEN_BASE + 0x9C)
#define  REG_TC_CLK_GEN_4E_H       (REG_TC_CLK_GEN_BASE + 0x9D)
#define  REG_TC_CLK_GEN_4F_L       (REG_TC_CLK_GEN_BASE + 0x9E)
#define  REG_TC_CLK_GEN_4F_H       (REG_TC_CLK_GEN_BASE + 0x9F)
#define  REG_TC_CLK_GEN_50_L       (REG_TC_CLK_GEN_BASE + 0xA0)
#define  REG_TC_CLK_GEN_50_H       (REG_TC_CLK_GEN_BASE + 0xA1)
#define  REG_TC_CLK_GEN_51_L       (REG_TC_CLK_GEN_BASE + 0xA2)
#define  REG_TC_CLK_GEN_51_H       (REG_TC_CLK_GEN_BASE + 0xA3)
#define  REG_TC_CLK_GEN_52_L       (REG_TC_CLK_GEN_BASE + 0xA4)
#define  REG_TC_CLK_GEN_52_H       (REG_TC_CLK_GEN_BASE + 0xA5)
#define  REG_TC_CLK_GEN_53_L       (REG_TC_CLK_GEN_BASE + 0xA6)
#define  REG_TC_CLK_GEN_53_H       (REG_TC_CLK_GEN_BASE + 0xA7)
#define  REG_TC_CLK_GEN_54_L       (REG_TC_CLK_GEN_BASE + 0xA8)
#define  REG_TC_CLK_GEN_54_H       (REG_TC_CLK_GEN_BASE + 0xA9)
#define  REG_TC_CLK_GEN_55_L       (REG_TC_CLK_GEN_BASE + 0xAA)
#define  REG_TC_CLK_GEN_55_H       (REG_TC_CLK_GEN_BASE + 0xAB)
#define  REG_TC_CLK_GEN_56_L       (REG_TC_CLK_GEN_BASE + 0xAC)
#define  REG_TC_CLK_GEN_56_H       (REG_TC_CLK_GEN_BASE + 0xAD)
#define  REG_TC_CLK_GEN_57_L       (REG_TC_CLK_GEN_BASE + 0xAE)
#define  REG_TC_CLK_GEN_57_H       (REG_TC_CLK_GEN_BASE + 0xAF)
#define  REG_TC_CLK_GEN_58_L       (REG_TC_CLK_GEN_BASE + 0xB0)
#define  REG_TC_CLK_GEN_58_H       (REG_TC_CLK_GEN_BASE + 0xB1)
#define  REG_TC_CLK_GEN_59_L       (REG_TC_CLK_GEN_BASE + 0xB2)
#define  REG_TC_CLK_GEN_59_H       (REG_TC_CLK_GEN_BASE + 0xB3)
#define  REG_TC_CLK_GEN_5A_L       (REG_TC_CLK_GEN_BASE + 0xB4)
#define  REG_TC_CLK_GEN_5A_H       (REG_TC_CLK_GEN_BASE + 0xB5)
#define  REG_TC_CLK_GEN_5B_L       (REG_TC_CLK_GEN_BASE + 0xB6)
#define  REG_TC_CLK_GEN_5B_H       (REG_TC_CLK_GEN_BASE + 0xB7)
#define  REG_TC_CLK_GEN_5C_L       (REG_TC_CLK_GEN_BASE + 0xB8)
#define  REG_TC_CLK_GEN_5C_H       (REG_TC_CLK_GEN_BASE + 0xB9)
#define  REG_TC_CLK_GEN_5D_L       (REG_TC_CLK_GEN_BASE + 0xBA)
#define  REG_TC_CLK_GEN_5D_H       (REG_TC_CLK_GEN_BASE + 0xBB)
#define  REG_TC_CLK_GEN_5E_L       (REG_TC_CLK_GEN_BASE + 0xBC)
#define  REG_TC_CLK_GEN_5E_H       (REG_TC_CLK_GEN_BASE + 0xBD)
#define  REG_TC_CLK_GEN_5F_L       (REG_TC_CLK_GEN_BASE + 0xBE)
#define  REG_TC_CLK_GEN_5F_H       (REG_TC_CLK_GEN_BASE + 0xBF)
#define  REG_TC_CLK_GEN_60_L       (REG_TC_CLK_GEN_BASE + 0xC0)
#define  REG_TC_CLK_GEN_60_H       (REG_TC_CLK_GEN_BASE + 0xC1)
#define  REG_TC_CLK_GEN_61_L       (REG_TC_CLK_GEN_BASE + 0xC2)
#define  REG_TC_CLK_GEN_61_H       (REG_TC_CLK_GEN_BASE + 0xC3)
#define  REG_TC_CLK_GEN_62_L       (REG_TC_CLK_GEN_BASE + 0xC4)
#define  REG_TC_CLK_GEN_62_H       (REG_TC_CLK_GEN_BASE + 0xC5)
#define  REG_TC_CLK_GEN_63_L       (REG_TC_CLK_GEN_BASE + 0xC6)
#define  REG_TC_CLK_GEN_63_H       (REG_TC_CLK_GEN_BASE + 0xC7)
#define  REG_TC_CLK_GEN_64_L       (REG_TC_CLK_GEN_BASE + 0xC8)
#define  REG_TC_CLK_GEN_64_H       (REG_TC_CLK_GEN_BASE + 0xC9)
#define  REG_TC_CLK_GEN_65_L       (REG_TC_CLK_GEN_BASE + 0xCA)
#define  REG_TC_CLK_GEN_65_H       (REG_TC_CLK_GEN_BASE + 0xCB)
#define  REG_TC_CLK_GEN_66_L       (REG_TC_CLK_GEN_BASE + 0xCC)
#define  REG_TC_CLK_GEN_66_H       (REG_TC_CLK_GEN_BASE + 0xCD)
#define  REG_TC_CLK_GEN_67_L       (REG_TC_CLK_GEN_BASE + 0xCE)
#define  REG_TC_CLK_GEN_67_H       (REG_TC_CLK_GEN_BASE + 0xCF)
#define  REG_TC_CLK_GEN_68_L       (REG_TC_CLK_GEN_BASE + 0xD0)
#define  REG_TC_CLK_GEN_68_H       (REG_TC_CLK_GEN_BASE + 0xD1)
#define  REG_TC_CLK_GEN_69_L       (REG_TC_CLK_GEN_BASE + 0xD2)
#define  REG_TC_CLK_GEN_69_H       (REG_TC_CLK_GEN_BASE + 0xD3)
#define  REG_TC_CLK_GEN_6A_L       (REG_TC_CLK_GEN_BASE + 0xD4)
#define  REG_TC_CLK_GEN_6A_H       (REG_TC_CLK_GEN_BASE + 0xD5)
#define  REG_TC_CLK_GEN_6B_L       (REG_TC_CLK_GEN_BASE + 0xD6)
#define  REG_TC_CLK_GEN_6B_H       (REG_TC_CLK_GEN_BASE + 0xD7)
#define  REG_TC_CLK_GEN_6C_L       (REG_TC_CLK_GEN_BASE + 0xD8)
#define  REG_TC_CLK_GEN_6C_H       (REG_TC_CLK_GEN_BASE + 0xD9)
#define  REG_TC_CLK_GEN_6D_L       (REG_TC_CLK_GEN_BASE + 0xDA)
#define  REG_TC_CLK_GEN_6D_H       (REG_TC_CLK_GEN_BASE + 0xDB)
#define  REG_TC_CLK_GEN_6E_L       (REG_TC_CLK_GEN_BASE + 0xDC)
#define  REG_TC_CLK_GEN_6E_H       (REG_TC_CLK_GEN_BASE + 0xDD)
#define  REG_TC_CLK_GEN_6F_L       (REG_TC_CLK_GEN_BASE + 0xDE)
#define  REG_TC_CLK_GEN_6F_H       (REG_TC_CLK_GEN_BASE + 0xDF)
#define  REG_TC_CLK_GEN_70_L       (REG_TC_CLK_GEN_BASE + 0xE0)
#define  REG_TC_CLK_GEN_70_H       (REG_TC_CLK_GEN_BASE + 0xE1)
#define  REG_TC_CLK_GEN_71_L       (REG_TC_CLK_GEN_BASE + 0xE2)
#define  REG_TC_CLK_GEN_71_H       (REG_TC_CLK_GEN_BASE + 0xE3)
#define  REG_TC_CLK_GEN_72_L       (REG_TC_CLK_GEN_BASE + 0xE4)
#define  REG_TC_CLK_GEN_72_H       (REG_TC_CLK_GEN_BASE + 0xE5)
#define  REG_TC_CLK_GEN_73_L       (REG_TC_CLK_GEN_BASE + 0xE6)
#define  REG_TC_CLK_GEN_73_H       (REG_TC_CLK_GEN_BASE + 0xE7)
#define  REG_TC_CLK_GEN_74_L       (REG_TC_CLK_GEN_BASE + 0xE8)
#define  REG_TC_CLK_GEN_74_H       (REG_TC_CLK_GEN_BASE + 0xE9)
#define  REG_TC_CLK_GEN_75_L       (REG_TC_CLK_GEN_BASE + 0xEA)
#define  REG_TC_CLK_GEN_75_H       (REG_TC_CLK_GEN_BASE + 0xEB)
#define  REG_TC_CLK_GEN_76_L       (REG_TC_CLK_GEN_BASE + 0xEC)
#define  REG_TC_CLK_GEN_76_H       (REG_TC_CLK_GEN_BASE + 0xED)
#define  REG_TC_CLK_GEN_77_L       (REG_TC_CLK_GEN_BASE + 0xEE)
#define  REG_TC_CLK_GEN_77_H       (REG_TC_CLK_GEN_BASE + 0xEF)
#define  REG_TC_CLK_GEN_78_L       (REG_TC_CLK_GEN_BASE + 0xF0)
#define  REG_TC_CLK_GEN_78_H       (REG_TC_CLK_GEN_BASE + 0xF1)
#define  REG_TC_CLK_GEN_79_L       (REG_TC_CLK_GEN_BASE + 0xF2)
#define  REG_TC_CLK_GEN_79_H       (REG_TC_CLK_GEN_BASE + 0xF3)
#define  REG_TC_CLK_GEN_7A_L       (REG_TC_CLK_GEN_BASE + 0xF4)
#define  REG_TC_CLK_GEN_7A_H       (REG_TC_CLK_GEN_BASE + 0xF5)
#define  REG_TC_CLK_GEN_7B_L       (REG_TC_CLK_GEN_BASE + 0xF6)
#define  REG_TC_CLK_GEN_7B_H       (REG_TC_CLK_GEN_BASE + 0xF7)
#define  REG_TC_CLK_GEN_7C_L       (REG_TC_CLK_GEN_BASE + 0xF8)
#define  REG_TC_CLK_GEN_7C_H       (REG_TC_CLK_GEN_BASE + 0xF9)
#define  REG_TC_CLK_GEN_7D_L       (REG_TC_CLK_GEN_BASE + 0xFA)
#define  REG_TC_CLK_GEN_7D_H       (REG_TC_CLK_GEN_BASE + 0xFB)
#define  REG_TC_CLK_GEN_7E_L       (REG_TC_CLK_GEN_BASE + 0xFC)
#define  REG_TC_CLK_GEN_7E_H       (REG_TC_CLK_GEN_BASE + 0xFD)
#define  REG_TC_CLK_GEN_7F_L       (REG_TC_CLK_GEN_BASE + 0xFE)
#define  REG_TC_CLK_GEN_7F_H       (REG_TC_CLK_GEN_BASE + 0xFF)

#define  REG_TC_CLK_GEN1_00_L       (REG_TC_CLK_GEN1_BASE + 0x00)
#define  REG_TC_CLK_GEN1_00_H       (REG_TC_CLK_GEN1_BASE + 0x01)
#define  REG_TC_CLK_GEN1_01_L       (REG_TC_CLK_GEN1_BASE + 0x02)
#define  REG_TC_CLK_GEN1_01_H       (REG_TC_CLK_GEN1_BASE + 0x03)
#define  REG_TC_CLK_GEN1_02_L       (REG_TC_CLK_GEN1_BASE + 0x04)
#define  REG_TC_CLK_GEN1_02_H       (REG_TC_CLK_GEN1_BASE + 0x05)
#define  REG_TC_CLK_GEN1_03_L       (REG_TC_CLK_GEN1_BASE + 0x06)
#define  REG_TC_CLK_GEN1_03_H       (REG_TC_CLK_GEN1_BASE + 0x07)
#define  REG_TC_CLK_GEN1_04_L       (REG_TC_CLK_GEN1_BASE + 0x08)
#define  REG_TC_CLK_GEN1_04_H       (REG_TC_CLK_GEN1_BASE + 0x09)
#define  REG_TC_CLK_GEN1_05_L       (REG_TC_CLK_GEN1_BASE + 0x0A)
#define  REG_TC_CLK_GEN1_05_H       (REG_TC_CLK_GEN1_BASE + 0x0B)
#define  REG_TC_CLK_GEN1_06_L       (REG_TC_CLK_GEN1_BASE + 0x0C)
#define  REG_TC_CLK_GEN1_06_H       (REG_TC_CLK_GEN1_BASE + 0x0D)
#define  REG_TC_CLK_GEN1_07_L       (REG_TC_CLK_GEN1_BASE + 0x0E)
#define  REG_TC_CLK_GEN1_07_H       (REG_TC_CLK_GEN1_BASE + 0x0F)
#define  REG_TC_CLK_GEN1_08_L       (REG_TC_CLK_GEN1_BASE + 0x10)
#define  REG_TC_CLK_GEN1_08_H       (REG_TC_CLK_GEN1_BASE + 0x11)
#define  REG_TC_CLK_GEN1_09_L       (REG_TC_CLK_GEN1_BASE + 0x12)
#define  REG_TC_CLK_GEN1_09_H       (REG_TC_CLK_GEN1_BASE + 0x13)
#define  REG_TC_CLK_GEN1_0A_L       (REG_TC_CLK_GEN1_BASE + 0x14)
#define  REG_TC_CLK_GEN1_0A_H       (REG_TC_CLK_GEN1_BASE + 0x15)
#define  REG_TC_CLK_GEN1_0B_L       (REG_TC_CLK_GEN1_BASE + 0x16)
#define  REG_TC_CLK_GEN1_0B_H       (REG_TC_CLK_GEN1_BASE + 0x17)
#define  REG_TC_CLK_GEN1_0C_L       (REG_TC_CLK_GEN1_BASE + 0x18)
#define  REG_TC_CLK_GEN1_0C_H       (REG_TC_CLK_GEN1_BASE + 0x19)
#define  REG_TC_CLK_GEN1_0D_L       (REG_TC_CLK_GEN1_BASE + 0x1A)
#define  REG_TC_CLK_GEN1_0D_H       (REG_TC_CLK_GEN1_BASE + 0x1B)
#define  REG_TC_CLK_GEN1_0E_L       (REG_TC_CLK_GEN1_BASE + 0x1C)
#define  REG_TC_CLK_GEN1_0E_H       (REG_TC_CLK_GEN1_BASE + 0x1D)
#define  REG_TC_CLK_GEN1_0F_L       (REG_TC_CLK_GEN1_BASE + 0x1E)
#define  REG_TC_CLK_GEN1_0F_H       (REG_TC_CLK_GEN1_BASE + 0x1F)
#define  REG_TC_CLK_GEN1_10_L       (REG_TC_CLK_GEN1_BASE + 0x20)
#define  REG_TC_CLK_GEN1_10_H       (REG_TC_CLK_GEN1_BASE + 0x21)
#define  REG_TC_CLK_GEN1_11_L       (REG_TC_CLK_GEN1_BASE + 0x22)
#define  REG_TC_CLK_GEN1_11_H       (REG_TC_CLK_GEN1_BASE + 0x23)
#define  REG_TC_CLK_GEN1_12_L       (REG_TC_CLK_GEN1_BASE + 0x24)
#define  REG_TC_CLK_GEN1_12_H       (REG_TC_CLK_GEN1_BASE + 0x25)
#define  REG_TC_CLK_GEN1_13_L       (REG_TC_CLK_GEN1_BASE + 0x26)
#define  REG_TC_CLK_GEN1_13_H       (REG_TC_CLK_GEN1_BASE + 0x27)
#define  REG_TC_CLK_GEN1_14_L       (REG_TC_CLK_GEN1_BASE + 0x28)
#define  REG_TC_CLK_GEN1_14_H       (REG_TC_CLK_GEN1_BASE + 0x29)
#define  REG_TC_CLK_GEN1_15_L       (REG_TC_CLK_GEN1_BASE + 0x2A)
#define  REG_TC_CLK_GEN1_15_H       (REG_TC_CLK_GEN1_BASE + 0x2B)
#define  REG_TC_CLK_GEN1_16_L       (REG_TC_CLK_GEN1_BASE + 0x2C)
#define  REG_TC_CLK_GEN1_16_H       (REG_TC_CLK_GEN1_BASE + 0x2D)
#define  REG_TC_CLK_GEN1_17_L       (REG_TC_CLK_GEN1_BASE + 0x2E)
#define  REG_TC_CLK_GEN1_17_H       (REG_TC_CLK_GEN1_BASE + 0x2F)
#define  REG_TC_CLK_GEN1_18_L       (REG_TC_CLK_GEN1_BASE + 0x30)
#define  REG_TC_CLK_GEN1_18_H       (REG_TC_CLK_GEN1_BASE + 0x31)
#define  REG_TC_CLK_GEN1_19_L       (REG_TC_CLK_GEN1_BASE + 0x32)
#define  REG_TC_CLK_GEN1_19_H       (REG_TC_CLK_GEN1_BASE + 0x33)
#define  REG_TC_CLK_GEN1_1A_L       (REG_TC_CLK_GEN1_BASE + 0x34)
#define  REG_TC_CLK_GEN1_1A_H       (REG_TC_CLK_GEN1_BASE + 0x35)
#define  REG_TC_CLK_GEN1_1B_L       (REG_TC_CLK_GEN1_BASE + 0x36)
#define  REG_TC_CLK_GEN1_1B_H       (REG_TC_CLK_GEN1_BASE + 0x37)
#define  REG_TC_CLK_GEN1_1C_L       (REG_TC_CLK_GEN1_BASE + 0x38)
#define  REG_TC_CLK_GEN1_1C_H       (REG_TC_CLK_GEN1_BASE + 0x39)
#define  REG_TC_CLK_GEN1_1D_L       (REG_TC_CLK_GEN1_BASE + 0x3A)
#define  REG_TC_CLK_GEN1_1D_H       (REG_TC_CLK_GEN1_BASE + 0x3B)
#define  REG_TC_CLK_GEN1_1E_L       (REG_TC_CLK_GEN1_BASE + 0x3C)
#define  REG_TC_CLK_GEN1_1E_H       (REG_TC_CLK_GEN1_BASE + 0x3D)
#define  REG_TC_CLK_GEN1_1F_L       (REG_TC_CLK_GEN1_BASE + 0x3E)
#define  REG_TC_CLK_GEN1_1F_H       (REG_TC_CLK_GEN1_BASE + 0x3F)
#define  REG_TC_CLK_GEN1_20_L       (REG_TC_CLK_GEN1_BASE + 0x40)
#define  REG_TC_CLK_GEN1_20_H       (REG_TC_CLK_GEN1_BASE + 0x41)
#define  REG_TC_CLK_GEN1_21_L       (REG_TC_CLK_GEN1_BASE + 0x42)
#define  REG_TC_CLK_GEN1_21_H       (REG_TC_CLK_GEN1_BASE + 0x43)
#define  REG_TC_CLK_GEN1_22_L       (REG_TC_CLK_GEN1_BASE + 0x44)
#define  REG_TC_CLK_GEN1_22_H       (REG_TC_CLK_GEN1_BASE + 0x45)
#define  REG_TC_CLK_GEN1_23_L       (REG_TC_CLK_GEN1_BASE + 0x46)
#define  REG_TC_CLK_GEN1_23_H       (REG_TC_CLK_GEN1_BASE + 0x47)
#define  REG_TC_CLK_GEN1_24_L       (REG_TC_CLK_GEN1_BASE + 0x48)
#define  REG_TC_CLK_GEN1_24_H       (REG_TC_CLK_GEN1_BASE + 0x49)
#define  REG_TC_CLK_GEN1_25_L       (REG_TC_CLK_GEN1_BASE + 0x4A)
#define  REG_TC_CLK_GEN1_25_H       (REG_TC_CLK_GEN1_BASE + 0x4B)
#define  REG_TC_CLK_GEN1_26_L       (REG_TC_CLK_GEN1_BASE + 0x4C)
#define  REG_TC_CLK_GEN1_26_H       (REG_TC_CLK_GEN1_BASE + 0x4D)
#define  REG_TC_CLK_GEN1_27_L       (REG_TC_CLK_GEN1_BASE + 0x4E)
#define  REG_TC_CLK_GEN1_27_H       (REG_TC_CLK_GEN1_BASE + 0x4F)
#define  REG_TC_CLK_GEN1_28_L       (REG_TC_CLK_GEN1_BASE + 0x50)
#define  REG_TC_CLK_GEN1_28_H       (REG_TC_CLK_GEN1_BASE + 0x51)
#define  REG_TC_CLK_GEN1_29_L       (REG_TC_CLK_GEN1_BASE + 0x52)
#define  REG_TC_CLK_GEN1_29_H       (REG_TC_CLK_GEN1_BASE + 0x53)
#define  REG_TC_CLK_GEN1_2A_L       (REG_TC_CLK_GEN1_BASE + 0x54)
#define  REG_TC_CLK_GEN1_2A_H       (REG_TC_CLK_GEN1_BASE + 0x55)
#define  REG_TC_CLK_GEN1_2B_L       (REG_TC_CLK_GEN1_BASE + 0x56)
#define  REG_TC_CLK_GEN1_2B_H       (REG_TC_CLK_GEN1_BASE + 0x57)
#define  REG_TC_CLK_GEN1_2C_L       (REG_TC_CLK_GEN1_BASE + 0x58)
#define  REG_TC_CLK_GEN1_2C_H       (REG_TC_CLK_GEN1_BASE + 0x59)
#define  REG_TC_CLK_GEN1_2D_L       (REG_TC_CLK_GEN1_BASE + 0x5A)
#define  REG_TC_CLK_GEN1_2D_H       (REG_TC_CLK_GEN1_BASE + 0x5B)
#define  REG_TC_CLK_GEN1_2E_L       (REG_TC_CLK_GEN1_BASE + 0x5C)
#define  REG_TC_CLK_GEN1_2E_H       (REG_TC_CLK_GEN1_BASE + 0x5D)
#define  REG_TC_CLK_GEN1_2F_L       (REG_TC_CLK_GEN1_BASE + 0x5E)
#define  REG_TC_CLK_GEN1_2F_H       (REG_TC_CLK_GEN1_BASE + 0x5F)
#define  REG_TC_CLK_GEN1_30_L       (REG_TC_CLK_GEN1_BASE + 0x60)
#define  REG_TC_CLK_GEN1_30_H       (REG_TC_CLK_GEN1_BASE + 0x61)
#define  REG_TC_CLK_GEN1_31_L       (REG_TC_CLK_GEN1_BASE + 0x62)
#define  REG_TC_CLK_GEN1_31_H       (REG_TC_CLK_GEN1_BASE + 0x63)
#define  REG_TC_CLK_GEN1_32_L       (REG_TC_CLK_GEN1_BASE + 0x64)
#define  REG_TC_CLK_GEN1_32_H       (REG_TC_CLK_GEN1_BASE + 0x65)
#define  REG_TC_CLK_GEN1_33_L       (REG_TC_CLK_GEN1_BASE + 0x66)
#define  REG_TC_CLK_GEN1_33_H       (REG_TC_CLK_GEN1_BASE + 0x67)
#define  REG_TC_CLK_GEN1_34_L       (REG_TC_CLK_GEN1_BASE + 0x68)
#define  REG_TC_CLK_GEN1_34_H       (REG_TC_CLK_GEN1_BASE + 0x69)
#define  REG_TC_CLK_GEN1_35_L       (REG_TC_CLK_GEN1_BASE + 0x6A)
#define  REG_TC_CLK_GEN1_35_H       (REG_TC_CLK_GEN1_BASE + 0x6B)
#define  REG_TC_CLK_GEN1_36_L       (REG_TC_CLK_GEN1_BASE + 0x6C)
#define  REG_TC_CLK_GEN1_36_H       (REG_TC_CLK_GEN1_BASE + 0x6D)
#define  REG_TC_CLK_GEN1_37_L       (REG_TC_CLK_GEN1_BASE + 0x6E)
#define  REG_TC_CLK_GEN1_37_H       (REG_TC_CLK_GEN1_BASE + 0x6F)
#define  REG_TC_CLK_GEN1_38_L       (REG_TC_CLK_GEN1_BASE + 0x70)
#define  REG_TC_CLK_GEN1_38_H       (REG_TC_CLK_GEN1_BASE + 0x71)
#define  REG_TC_CLK_GEN1_39_L       (REG_TC_CLK_GEN1_BASE + 0x72)
#define  REG_TC_CLK_GEN1_39_H       (REG_TC_CLK_GEN1_BASE + 0x73)
#define  REG_TC_CLK_GEN1_3A_L       (REG_TC_CLK_GEN1_BASE + 0x74)
#define  REG_TC_CLK_GEN1_3A_H       (REG_TC_CLK_GEN1_BASE + 0x75)
#define  REG_TC_CLK_GEN1_3B_L       (REG_TC_CLK_GEN1_BASE + 0x76)
#define  REG_TC_CLK_GEN1_3B_H       (REG_TC_CLK_GEN1_BASE + 0x77)
#define  REG_TC_CLK_GEN1_3C_L       (REG_TC_CLK_GEN1_BASE + 0x78)
#define  REG_TC_CLK_GEN1_3C_H       (REG_TC_CLK_GEN1_BASE + 0x79)
#define  REG_TC_CLK_GEN1_3D_L       (REG_TC_CLK_GEN1_BASE + 0x7A)
#define  REG_TC_CLK_GEN1_3D_H       (REG_TC_CLK_GEN1_BASE + 0x7B)
#define  REG_TC_CLK_GEN1_3E_L       (REG_TC_CLK_GEN1_BASE + 0x7C)
#define  REG_TC_CLK_GEN1_3E_H       (REG_TC_CLK_GEN1_BASE + 0x7D)
#define  REG_TC_CLK_GEN1_3F_L       (REG_TC_CLK_GEN1_BASE + 0x7E)
#define  REG_TC_CLK_GEN1_3F_H       (REG_TC_CLK_GEN1_BASE + 0x7F)
#define  REG_TC_CLK_GEN1_40_L       (REG_TC_CLK_GEN1_BASE + 0x80)
#define  REG_TC_CLK_GEN1_40_H       (REG_TC_CLK_GEN1_BASE + 0x81)
#define  REG_TC_CLK_GEN1_41_L       (REG_TC_CLK_GEN1_BASE + 0x82)
#define  REG_TC_CLK_GEN1_41_H       (REG_TC_CLK_GEN1_BASE + 0x83)
#define  REG_TC_CLK_GEN1_42_L       (REG_TC_CLK_GEN1_BASE + 0x84)
#define  REG_TC_CLK_GEN1_42_H       (REG_TC_CLK_GEN1_BASE + 0x85)
#define  REG_TC_CLK_GEN1_43_L       (REG_TC_CLK_GEN1_BASE + 0x86)
#define  REG_TC_CLK_GEN1_43_H       (REG_TC_CLK_GEN1_BASE + 0x87)
#define  REG_TC_CLK_GEN1_44_L       (REG_TC_CLK_GEN1_BASE + 0x88)
#define  REG_TC_CLK_GEN1_44_H       (REG_TC_CLK_GEN1_BASE + 0x89)
#define  REG_TC_CLK_GEN1_45_L       (REG_TC_CLK_GEN1_BASE + 0x8A)
#define  REG_TC_CLK_GEN1_45_H       (REG_TC_CLK_GEN1_BASE + 0x8B)
#define  REG_TC_CLK_GEN1_46_L       (REG_TC_CLK_GEN1_BASE + 0x8C)
#define  REG_TC_CLK_GEN1_46_H       (REG_TC_CLK_GEN1_BASE + 0x8D)
#define  REG_TC_CLK_GEN1_47_L       (REG_TC_CLK_GEN1_BASE + 0x8E)
#define  REG_TC_CLK_GEN1_47_H       (REG_TC_CLK_GEN1_BASE + 0x8F)
#define  REG_TC_CLK_GEN1_48_L       (REG_TC_CLK_GEN1_BASE + 0x90)
#define  REG_TC_CLK_GEN1_48_H       (REG_TC_CLK_GEN1_BASE + 0x91)
#define  REG_TC_CLK_GEN1_49_L       (REG_TC_CLK_GEN1_BASE + 0x92)
#define  REG_TC_CLK_GEN1_49_H       (REG_TC_CLK_GEN1_BASE + 0x93)
#define  REG_TC_CLK_GEN1_4A_L       (REG_TC_CLK_GEN1_BASE + 0x94)
#define  REG_TC_CLK_GEN1_4A_H       (REG_TC_CLK_GEN1_BASE + 0x95)
#define  REG_TC_CLK_GEN1_4B_L       (REG_TC_CLK_GEN1_BASE + 0x96)
#define  REG_TC_CLK_GEN1_4B_H       (REG_TC_CLK_GEN1_BASE + 0x97)
#define  REG_TC_CLK_GEN1_4C_L       (REG_TC_CLK_GEN1_BASE + 0x98)
#define  REG_TC_CLK_GEN1_4C_H       (REG_TC_CLK_GEN1_BASE + 0x99)
#define  REG_TC_CLK_GEN1_4D_L       (REG_TC_CLK_GEN1_BASE + 0x9A)
#define  REG_TC_CLK_GEN1_4D_H       (REG_TC_CLK_GEN1_BASE + 0x9B)
#define  REG_TC_CLK_GEN1_4E_L       (REG_TC_CLK_GEN1_BASE + 0x9C)
#define  REG_TC_CLK_GEN1_4E_H       (REG_TC_CLK_GEN1_BASE + 0x9D)
#define  REG_TC_CLK_GEN1_4F_L       (REG_TC_CLK_GEN1_BASE + 0x9E)
#define  REG_TC_CLK_GEN1_4F_H       (REG_TC_CLK_GEN1_BASE + 0x9F)
#define  REG_TC_CLK_GEN1_50_L       (REG_TC_CLK_GEN1_BASE + 0xA0)
#define  REG_TC_CLK_GEN1_50_H       (REG_TC_CLK_GEN1_BASE + 0xA1)
#define  REG_TC_CLK_GEN1_51_L       (REG_TC_CLK_GEN1_BASE + 0xA2)
#define  REG_TC_CLK_GEN1_51_H       (REG_TC_CLK_GEN1_BASE + 0xA3)
#define  REG_TC_CLK_GEN1_52_L       (REG_TC_CLK_GEN1_BASE + 0xA4)
#define  REG_TC_CLK_GEN1_52_H       (REG_TC_CLK_GEN1_BASE + 0xA5)
#define  REG_TC_CLK_GEN1_53_L       (REG_TC_CLK_GEN1_BASE + 0xA6)
#define  REG_TC_CLK_GEN1_53_H       (REG_TC_CLK_GEN1_BASE + 0xA7)
#define  REG_TC_CLK_GEN1_54_L       (REG_TC_CLK_GEN1_BASE + 0xA8)
#define  REG_TC_CLK_GEN1_54_H       (REG_TC_CLK_GEN1_BASE + 0xA9)
#define  REG_TC_CLK_GEN1_55_L       (REG_TC_CLK_GEN1_BASE + 0xAA)
#define  REG_TC_CLK_GEN1_55_H       (REG_TC_CLK_GEN1_BASE + 0xAB)
#define  REG_TC_CLK_GEN1_56_L       (REG_TC_CLK_GEN1_BASE + 0xAC)
#define  REG_TC_CLK_GEN1_56_H       (REG_TC_CLK_GEN1_BASE + 0xAD)
#define  REG_TC_CLK_GEN1_57_L       (REG_TC_CLK_GEN1_BASE + 0xAE)
#define  REG_TC_CLK_GEN1_57_H       (REG_TC_CLK_GEN1_BASE + 0xAF)
#define  REG_TC_CLK_GEN1_58_L       (REG_TC_CLK_GEN1_BASE + 0xB0)
#define  REG_TC_CLK_GEN1_58_H       (REG_TC_CLK_GEN1_BASE + 0xB1)
#define  REG_TC_CLK_GEN1_59_L       (REG_TC_CLK_GEN1_BASE + 0xB2)
#define  REG_TC_CLK_GEN1_59_H       (REG_TC_CLK_GEN1_BASE + 0xB3)
#define  REG_TC_CLK_GEN1_5A_L       (REG_TC_CLK_GEN1_BASE + 0xB4)
#define  REG_TC_CLK_GEN1_5A_H       (REG_TC_CLK_GEN1_BASE + 0xB5)
#define  REG_TC_CLK_GEN1_5B_L       (REG_TC_CLK_GEN1_BASE + 0xB6)
#define  REG_TC_CLK_GEN1_5B_H       (REG_TC_CLK_GEN1_BASE + 0xB7)
#define  REG_TC_CLK_GEN1_5C_L       (REG_TC_CLK_GEN1_BASE + 0xB8)
#define  REG_TC_CLK_GEN1_5C_H       (REG_TC_CLK_GEN1_BASE + 0xB9)
#define  REG_TC_CLK_GEN1_5D_L       (REG_TC_CLK_GEN1_BASE + 0xBA)
#define  REG_TC_CLK_GEN1_5D_H       (REG_TC_CLK_GEN1_BASE + 0xBB)
#define  REG_TC_CLK_GEN1_5E_L       (REG_TC_CLK_GEN1_BASE + 0xBC)
#define  REG_TC_CLK_GEN1_5E_H       (REG_TC_CLK_GEN1_BASE + 0xBD)
#define  REG_TC_CLK_GEN1_5F_L       (REG_TC_CLK_GEN1_BASE + 0xBE)
#define  REG_TC_CLK_GEN1_5F_H       (REG_TC_CLK_GEN1_BASE + 0xBF)
#define  REG_TC_CLK_GEN1_60_L       (REG_TC_CLK_GEN1_BASE + 0xC0)
#define  REG_TC_CLK_GEN1_60_H       (REG_TC_CLK_GEN1_BASE + 0xC1)
#define  REG_TC_CLK_GEN1_61_L       (REG_TC_CLK_GEN1_BASE + 0xC2)
#define  REG_TC_CLK_GEN1_61_H       (REG_TC_CLK_GEN1_BASE + 0xC3)
#define  REG_TC_CLK_GEN1_62_L       (REG_TC_CLK_GEN1_BASE + 0xC4)
#define  REG_TC_CLK_GEN1_62_H       (REG_TC_CLK_GEN1_BASE + 0xC5)
#define  REG_TC_CLK_GEN1_63_L       (REG_TC_CLK_GEN1_BASE + 0xC6)
#define  REG_TC_CLK_GEN1_63_H       (REG_TC_CLK_GEN1_BASE + 0xC7)
#define  REG_TC_CLK_GEN1_64_L       (REG_TC_CLK_GEN1_BASE + 0xC8)
#define  REG_TC_CLK_GEN1_64_H       (REG_TC_CLK_GEN1_BASE + 0xC9)
#define  REG_TC_CLK_GEN1_65_L       (REG_TC_CLK_GEN1_BASE + 0xCA)
#define  REG_TC_CLK_GEN1_65_H       (REG_TC_CLK_GEN1_BASE + 0xCB)
#define  REG_TC_CLK_GEN1_66_L       (REG_TC_CLK_GEN1_BASE + 0xCC)
#define  REG_TC_CLK_GEN1_66_H       (REG_TC_CLK_GEN1_BASE + 0xCD)
#define  REG_TC_CLK_GEN1_67_L       (REG_TC_CLK_GEN1_BASE + 0xCE)
#define  REG_TC_CLK_GEN1_67_H       (REG_TC_CLK_GEN1_BASE + 0xCF)
#define  REG_TC_CLK_GEN1_68_L       (REG_TC_CLK_GEN1_BASE + 0xD0)
#define  REG_TC_CLK_GEN1_68_H       (REG_TC_CLK_GEN1_BASE + 0xD1)
#define  REG_TC_CLK_GEN1_69_L       (REG_TC_CLK_GEN1_BASE + 0xD2)
#define  REG_TC_CLK_GEN1_69_H       (REG_TC_CLK_GEN1_BASE + 0xD3)
#define  REG_TC_CLK_GEN1_6A_L       (REG_TC_CLK_GEN1_BASE + 0xD4)
#define  REG_TC_CLK_GEN1_6A_H       (REG_TC_CLK_GEN1_BASE + 0xD5)
#define  REG_TC_CLK_GEN1_6B_L       (REG_TC_CLK_GEN1_BASE + 0xD6)
#define  REG_TC_CLK_GEN1_6B_H       (REG_TC_CLK_GEN1_BASE + 0xD7)
#define  REG_TC_CLK_GEN1_6C_L       (REG_TC_CLK_GEN1_BASE + 0xD8)
#define  REG_TC_CLK_GEN1_6C_H       (REG_TC_CLK_GEN1_BASE + 0xD9)
#define  REG_TC_CLK_GEN1_6D_L       (REG_TC_CLK_GEN1_BASE + 0xDA)
#define  REG_TC_CLK_GEN1_6D_H       (REG_TC_CLK_GEN1_BASE + 0xDB)
#define  REG_TC_CLK_GEN1_6E_L       (REG_TC_CLK_GEN1_BASE + 0xDC)
#define  REG_TC_CLK_GEN1_6E_H       (REG_TC_CLK_GEN1_BASE + 0xDD)
#define  REG_TC_CLK_GEN1_6F_L       (REG_TC_CLK_GEN1_BASE + 0xDE)
#define  REG_TC_CLK_GEN1_6F_H       (REG_TC_CLK_GEN1_BASE + 0xDF)
#define  REG_TC_CLK_GEN1_70_L       (REG_TC_CLK_GEN1_BASE + 0xE0)
#define  REG_TC_CLK_GEN1_70_H       (REG_TC_CLK_GEN1_BASE + 0xE1)
#define  REG_TC_CLK_GEN1_71_L       (REG_TC_CLK_GEN1_BASE + 0xE2)
#define  REG_TC_CLK_GEN1_71_H       (REG_TC_CLK_GEN1_BASE + 0xE3)
#define  REG_TC_CLK_GEN1_72_L       (REG_TC_CLK_GEN1_BASE + 0xE4)
#define  REG_TC_CLK_GEN1_72_H       (REG_TC_CLK_GEN1_BASE + 0xE5)
#define  REG_TC_CLK_GEN1_73_L       (REG_TC_CLK_GEN1_BASE + 0xE6)
#define  REG_TC_CLK_GEN1_73_H       (REG_TC_CLK_GEN1_BASE + 0xE7)
#define  REG_TC_CLK_GEN1_74_L       (REG_TC_CLK_GEN1_BASE + 0xE8)
#define  REG_TC_CLK_GEN1_74_H       (REG_TC_CLK_GEN1_BASE + 0xE9)
#define  REG_TC_CLK_GEN1_75_L       (REG_TC_CLK_GEN1_BASE + 0xEA)
#define  REG_TC_CLK_GEN1_75_H       (REG_TC_CLK_GEN1_BASE + 0xEB)
#define  REG_TC_CLK_GEN1_76_L       (REG_TC_CLK_GEN1_BASE + 0xEC)
#define  REG_TC_CLK_GEN1_76_H       (REG_TC_CLK_GEN1_BASE + 0xED)
#define  REG_TC_CLK_GEN1_77_L       (REG_TC_CLK_GEN1_BASE + 0xEE)
#define  REG_TC_CLK_GEN1_77_H       (REG_TC_CLK_GEN1_BASE + 0xEF)
#define  REG_TC_CLK_GEN1_78_L       (REG_TC_CLK_GEN1_BASE + 0xF0)
#define  REG_TC_CLK_GEN1_78_H       (REG_TC_CLK_GEN1_BASE + 0xF1)
#define  REG_TC_CLK_GEN1_79_L       (REG_TC_CLK_GEN1_BASE + 0xF2)
#define  REG_TC_CLK_GEN1_79_H       (REG_TC_CLK_GEN1_BASE + 0xF3)
#define  REG_TC_CLK_GEN1_7A_L       (REG_TC_CLK_GEN1_BASE + 0xF4)
#define  REG_TC_CLK_GEN1_7A_H       (REG_TC_CLK_GEN1_BASE + 0xF5)
#define  REG_TC_CLK_GEN1_7B_L       (REG_TC_CLK_GEN1_BASE + 0xF6)
#define  REG_TC_CLK_GEN1_7B_H       (REG_TC_CLK_GEN1_BASE + 0xF7)
#define  REG_TC_CLK_GEN1_7C_L       (REG_TC_CLK_GEN1_BASE + 0xF8)
#define  REG_TC_CLK_GEN1_7C_H       (REG_TC_CLK_GEN1_BASE + 0xF9)
#define  REG_TC_CLK_GEN1_7D_L       (REG_TC_CLK_GEN1_BASE + 0xFA)
#define  REG_TC_CLK_GEN1_7D_H       (REG_TC_CLK_GEN1_BASE + 0xFB)
#define  REG_TC_CLK_GEN1_7E_L       (REG_TC_CLK_GEN1_BASE + 0xFC)
#define  REG_TC_CLK_GEN1_7E_H       (REG_TC_CLK_GEN1_BASE + 0xFD)
#define  REG_TC_CLK_GEN1_7F_L       (REG_TC_CLK_GEN1_BASE + 0xFE)
#define  REG_TC_CLK_GEN1_7F_H       (REG_TC_CLK_GEN1_BASE + 0xFF)

#define  REG_TC_CHIP_TOP_00_L       (REG_TC_CHIP_TOP_BASE + 0x00)
#define  REG_TC_CHIP_TOP_00_H       (REG_TC_CHIP_TOP_BASE + 0x01)
#define  REG_TC_CHIP_TOP_01_L       (REG_TC_CHIP_TOP_BASE + 0x02)
#define  REG_TC_CHIP_TOP_01_H       (REG_TC_CHIP_TOP_BASE + 0x03)
#define  REG_TC_CHIP_TOP_02_L       (REG_TC_CHIP_TOP_BASE + 0x04)
#define  REG_TC_CHIP_TOP_02_H       (REG_TC_CHIP_TOP_BASE + 0x05)
#define  REG_TC_CHIP_TOP_03_L       (REG_TC_CHIP_TOP_BASE + 0x06)
#define  REG_TC_CHIP_TOP_03_H       (REG_TC_CHIP_TOP_BASE + 0x07)
#define  REG_TC_CHIP_TOP_04_L       (REG_TC_CHIP_TOP_BASE + 0x08)
#define  REG_TC_CHIP_TOP_04_H       (REG_TC_CHIP_TOP_BASE + 0x09)
#define  REG_TC_CHIP_TOP_05_L       (REG_TC_CHIP_TOP_BASE + 0x0A)
#define  REG_TC_CHIP_TOP_05_H       (REG_TC_CHIP_TOP_BASE + 0x0B)
#define  REG_TC_CHIP_TOP_06_L       (REG_TC_CHIP_TOP_BASE + 0x0C)
#define  REG_TC_CHIP_TOP_06_H       (REG_TC_CHIP_TOP_BASE + 0x0D)
#define  REG_TC_CHIP_TOP_07_L       (REG_TC_CHIP_TOP_BASE + 0x0E)
#define  REG_TC_CHIP_TOP_07_H       (REG_TC_CHIP_TOP_BASE + 0x0F)
#define  REG_TC_CHIP_TOP_08_L       (REG_TC_CHIP_TOP_BASE + 0x10)
#define  REG_TC_CHIP_TOP_08_H       (REG_TC_CHIP_TOP_BASE + 0x11)
#define  REG_TC_CHIP_TOP_09_L       (REG_TC_CHIP_TOP_BASE + 0x12)
#define  REG_TC_CHIP_TOP_09_H       (REG_TC_CHIP_TOP_BASE + 0x13)
#define  REG_TC_CHIP_TOP_0A_L       (REG_TC_CHIP_TOP_BASE + 0x14)
#define  REG_TC_CHIP_TOP_0A_H       (REG_TC_CHIP_TOP_BASE + 0x15)
#define  REG_TC_CHIP_TOP_0B_L       (REG_TC_CHIP_TOP_BASE + 0x16)
#define  REG_TC_CHIP_TOP_0B_H       (REG_TC_CHIP_TOP_BASE + 0x17)
#define  REG_TC_CHIP_TOP_0C_L       (REG_TC_CHIP_TOP_BASE + 0x18)
#define  REG_TC_CHIP_TOP_0C_H       (REG_TC_CHIP_TOP_BASE + 0x19)
#define  REG_TC_CHIP_TOP_0D_L       (REG_TC_CHIP_TOP_BASE + 0x1A)
#define  REG_TC_CHIP_TOP_0D_H       (REG_TC_CHIP_TOP_BASE + 0x1B)
#define  REG_TC_CHIP_TOP_0E_L       (REG_TC_CHIP_TOP_BASE + 0x1C)
#define  REG_TC_CHIP_TOP_0E_H       (REG_TC_CHIP_TOP_BASE + 0x1D)
#define  REG_TC_CHIP_TOP_0F_L       (REG_TC_CHIP_TOP_BASE + 0x1E)
#define  REG_TC_CHIP_TOP_0F_H       (REG_TC_CHIP_TOP_BASE + 0x1F)
#define  REG_TC_CHIP_TOP_10_L       (REG_TC_CHIP_TOP_BASE + 0x20)
#define  REG_TC_CHIP_TOP_10_H       (REG_TC_CHIP_TOP_BASE + 0x21)
#define  REG_TC_CHIP_TOP_11_L       (REG_TC_CHIP_TOP_BASE + 0x22)
#define  REG_TC_CHIP_TOP_11_H       (REG_TC_CHIP_TOP_BASE + 0x23)
#define  REG_TC_CHIP_TOP_12_L       (REG_TC_CHIP_TOP_BASE + 0x24)
#define  REG_TC_CHIP_TOP_12_H       (REG_TC_CHIP_TOP_BASE + 0x25)
#define  REG_TC_CHIP_TOP_13_L       (REG_TC_CHIP_TOP_BASE + 0x26)
#define  REG_TC_CHIP_TOP_13_H       (REG_TC_CHIP_TOP_BASE + 0x27)
#define  REG_TC_CHIP_TOP_14_L       (REG_TC_CHIP_TOP_BASE + 0x28)
#define  REG_TC_CHIP_TOP_14_H       (REG_TC_CHIP_TOP_BASE + 0x29)
#define  REG_TC_CHIP_TOP_15_L       (REG_TC_CHIP_TOP_BASE + 0x2A)
#define  REG_TC_CHIP_TOP_15_H       (REG_TC_CHIP_TOP_BASE + 0x2B)
#define  REG_TC_CHIP_TOP_16_L       (REG_TC_CHIP_TOP_BASE + 0x2C)
#define  REG_TC_CHIP_TOP_16_H       (REG_TC_CHIP_TOP_BASE + 0x2D)
#define  REG_TC_CHIP_TOP_17_L       (REG_TC_CHIP_TOP_BASE + 0x2E)
#define  REG_TC_CHIP_TOP_17_H       (REG_TC_CHIP_TOP_BASE + 0x2F)
#define  REG_TC_CHIP_TOP_18_L       (REG_TC_CHIP_TOP_BASE + 0x30)
#define  REG_TC_CHIP_TOP_18_H       (REG_TC_CHIP_TOP_BASE + 0x31)
#define  REG_TC_CHIP_TOP_19_L       (REG_TC_CHIP_TOP_BASE + 0x32)
#define  REG_TC_CHIP_TOP_19_H       (REG_TC_CHIP_TOP_BASE + 0x33)
#define  REG_TC_CHIP_TOP_1A_L       (REG_TC_CHIP_TOP_BASE + 0x34)
#define  REG_TC_CHIP_TOP_1A_H       (REG_TC_CHIP_TOP_BASE + 0x35)
#define  REG_TC_CHIP_TOP_1B_L       (REG_TC_CHIP_TOP_BASE + 0x36)
#define  REG_TC_CHIP_TOP_1B_H       (REG_TC_CHIP_TOP_BASE + 0x37)
#define  REG_TC_CHIP_TOP_1C_L       (REG_TC_CHIP_TOP_BASE + 0x38)
#define  REG_TC_CHIP_TOP_1C_H       (REG_TC_CHIP_TOP_BASE + 0x39)
#define  REG_TC_CHIP_TOP_1D_L       (REG_TC_CHIP_TOP_BASE + 0x3A)
#define  REG_TC_CHIP_TOP_1D_H       (REG_TC_CHIP_TOP_BASE + 0x3B)
#define  REG_TC_CHIP_TOP_1E_L       (REG_TC_CHIP_TOP_BASE + 0x3C)
#define  REG_TC_CHIP_TOP_1E_H       (REG_TC_CHIP_TOP_BASE + 0x3D)
#define  REG_TC_CHIP_TOP_1F_L       (REG_TC_CHIP_TOP_BASE + 0x3E)
#define  REG_TC_CHIP_TOP_1F_H       (REG_TC_CHIP_TOP_BASE + 0x3F)
#define  REG_TC_CHIP_TOP_20_L       (REG_TC_CHIP_TOP_BASE + 0x40)
#define  REG_TC_CHIP_TOP_20_H       (REG_TC_CHIP_TOP_BASE + 0x41)
#define  REG_TC_CHIP_TOP_21_L       (REG_TC_CHIP_TOP_BASE + 0x42)
#define  REG_TC_CHIP_TOP_21_H       (REG_TC_CHIP_TOP_BASE + 0x43)
#define  REG_TC_CHIP_TOP_22_L       (REG_TC_CHIP_TOP_BASE + 0x44)
#define  REG_TC_CHIP_TOP_22_H       (REG_TC_CHIP_TOP_BASE + 0x45)
#define  REG_TC_CHIP_TOP_23_L       (REG_TC_CHIP_TOP_BASE + 0x46)
#define  REG_TC_CHIP_TOP_23_H       (REG_TC_CHIP_TOP_BASE + 0x47)
#define  REG_TC_CHIP_TOP_24_L       (REG_TC_CHIP_TOP_BASE + 0x48)
#define  REG_TC_CHIP_TOP_24_H       (REG_TC_CHIP_TOP_BASE + 0x49)
#define  REG_TC_CHIP_TOP_25_L       (REG_TC_CHIP_TOP_BASE + 0x4A)
#define  REG_TC_CHIP_TOP_25_H       (REG_TC_CHIP_TOP_BASE + 0x4B)
#define  REG_TC_CHIP_TOP_26_L       (REG_TC_CHIP_TOP_BASE + 0x4C)
#define  REG_TC_CHIP_TOP_26_H       (REG_TC_CHIP_TOP_BASE + 0x4D)
#define  REG_TC_CHIP_TOP_27_L       (REG_TC_CHIP_TOP_BASE + 0x4E)
#define  REG_TC_CHIP_TOP_27_H       (REG_TC_CHIP_TOP_BASE + 0x4F)
#define  REG_TC_CHIP_TOP_28_L       (REG_TC_CHIP_TOP_BASE + 0x50)
#define  REG_TC_CHIP_TOP_28_H       (REG_TC_CHIP_TOP_BASE + 0x51)
#define  REG_TC_CHIP_TOP_29_L       (REG_TC_CHIP_TOP_BASE + 0x52)
#define  REG_TC_CHIP_TOP_29_H       (REG_TC_CHIP_TOP_BASE + 0x53)
#define  REG_TC_CHIP_TOP_2A_L       (REG_TC_CHIP_TOP_BASE + 0x54)
#define  REG_TC_CHIP_TOP_2A_H       (REG_TC_CHIP_TOP_BASE + 0x55)
#define  REG_TC_CHIP_TOP_2B_L       (REG_TC_CHIP_TOP_BASE + 0x56)
#define  REG_TC_CHIP_TOP_2B_H       (REG_TC_CHIP_TOP_BASE + 0x57)
#define  REG_TC_CHIP_TOP_2C_L       (REG_TC_CHIP_TOP_BASE + 0x58)
#define  REG_TC_CHIP_TOP_2C_H       (REG_TC_CHIP_TOP_BASE + 0x59)
#define  REG_TC_CHIP_TOP_2D_L       (REG_TC_CHIP_TOP_BASE + 0x5A)
#define  REG_TC_CHIP_TOP_2D_H       (REG_TC_CHIP_TOP_BASE + 0x5B)
#define  REG_TC_CHIP_TOP_2E_L       (REG_TC_CHIP_TOP_BASE + 0x5C)
#define  REG_TC_CHIP_TOP_2E_H       (REG_TC_CHIP_TOP_BASE + 0x5D)
#define  REG_TC_CHIP_TOP_2F_L       (REG_TC_CHIP_TOP_BASE + 0x5E)
#define  REG_TC_CHIP_TOP_2F_H       (REG_TC_CHIP_TOP_BASE + 0x5F)
#define  REG_TC_CHIP_TOP_30_L       (REG_TC_CHIP_TOP_BASE + 0x60)
#define  REG_TC_CHIP_TOP_30_H       (REG_TC_CHIP_TOP_BASE + 0x61)
#define  REG_TC_CHIP_TOP_31_L       (REG_TC_CHIP_TOP_BASE + 0x62)
#define  REG_TC_CHIP_TOP_31_H       (REG_TC_CHIP_TOP_BASE + 0x63)
#define  REG_TC_CHIP_TOP_32_L       (REG_TC_CHIP_TOP_BASE + 0x64)
#define  REG_TC_CHIP_TOP_32_H       (REG_TC_CHIP_TOP_BASE + 0x65)
#define  REG_TC_CHIP_TOP_33_L       (REG_TC_CHIP_TOP_BASE + 0x66)
#define  REG_TC_CHIP_TOP_33_H       (REG_TC_CHIP_TOP_BASE + 0x67)
#define  REG_TC_CHIP_TOP_34_L       (REG_TC_CHIP_TOP_BASE + 0x68)
#define  REG_TC_CHIP_TOP_34_H       (REG_TC_CHIP_TOP_BASE + 0x69)
#define  REG_TC_CHIP_TOP_35_L       (REG_TC_CHIP_TOP_BASE + 0x6A)
#define  REG_TC_CHIP_TOP_35_H       (REG_TC_CHIP_TOP_BASE + 0x6B)
#define  REG_TC_CHIP_TOP_36_L       (REG_TC_CHIP_TOP_BASE + 0x6C)
#define  REG_TC_CHIP_TOP_36_H       (REG_TC_CHIP_TOP_BASE + 0x6D)
#define  REG_TC_CHIP_TOP_37_L       (REG_TC_CHIP_TOP_BASE + 0x6E)
#define  REG_TC_CHIP_TOP_37_H       (REG_TC_CHIP_TOP_BASE + 0x6F)
#define  REG_TC_CHIP_TOP_38_L       (REG_TC_CHIP_TOP_BASE + 0x70)
#define  REG_TC_CHIP_TOP_38_H       (REG_TC_CHIP_TOP_BASE + 0x71)
#define  REG_TC_CHIP_TOP_39_L       (REG_TC_CHIP_TOP_BASE + 0x72)
#define  REG_TC_CHIP_TOP_39_H       (REG_TC_CHIP_TOP_BASE + 0x73)
#define  REG_TC_CHIP_TOP_3A_L       (REG_TC_CHIP_TOP_BASE + 0x74)
#define  REG_TC_CHIP_TOP_3A_H       (REG_TC_CHIP_TOP_BASE + 0x75)
#define  REG_TC_CHIP_TOP_3B_L       (REG_TC_CHIP_TOP_BASE + 0x76)
#define  REG_TC_CHIP_TOP_3B_H       (REG_TC_CHIP_TOP_BASE + 0x77)
#define  REG_TC_CHIP_TOP_3C_L       (REG_TC_CHIP_TOP_BASE + 0x78)
#define  REG_TC_CHIP_TOP_3C_H       (REG_TC_CHIP_TOP_BASE + 0x79)
#define  REG_TC_CHIP_TOP_3D_L       (REG_TC_CHIP_TOP_BASE + 0x7A)
#define  REG_TC_CHIP_TOP_3D_H       (REG_TC_CHIP_TOP_BASE + 0x7B)
#define  REG_TC_CHIP_TOP_3E_L       (REG_TC_CHIP_TOP_BASE + 0x7C)
#define  REG_TC_CHIP_TOP_3E_H       (REG_TC_CHIP_TOP_BASE + 0x7D)
#define  REG_TC_CHIP_TOP_3F_L       (REG_TC_CHIP_TOP_BASE + 0x7E)
#define  REG_TC_CHIP_TOP_3F_H       (REG_TC_CHIP_TOP_BASE + 0x7F)
#define  REG_TC_CHIP_TOP_40_L       (REG_TC_CHIP_TOP_BASE + 0x80)
#define  REG_TC_CHIP_TOP_40_H       (REG_TC_CHIP_TOP_BASE + 0x81)
#define  REG_TC_CHIP_TOP_41_L       (REG_TC_CHIP_TOP_BASE + 0x82)
#define  REG_TC_CHIP_TOP_41_H       (REG_TC_CHIP_TOP_BASE + 0x83)
#define  REG_TC_CHIP_TOP_42_L       (REG_TC_CHIP_TOP_BASE + 0x84)
#define  REG_TC_CHIP_TOP_42_H       (REG_TC_CHIP_TOP_BASE + 0x85)
#define  REG_TC_CHIP_TOP_43_L       (REG_TC_CHIP_TOP_BASE + 0x86)
#define  REG_TC_CHIP_TOP_43_H       (REG_TC_CHIP_TOP_BASE + 0x87)
#define  REG_TC_CHIP_TOP_44_L       (REG_TC_CHIP_TOP_BASE + 0x88)
#define  REG_TC_CHIP_TOP_44_H       (REG_TC_CHIP_TOP_BASE + 0x89)
#define  REG_TC_CHIP_TOP_45_L       (REG_TC_CHIP_TOP_BASE + 0x8A)
#define  REG_TC_CHIP_TOP_45_H       (REG_TC_CHIP_TOP_BASE + 0x8B)
#define  REG_TC_CHIP_TOP_46_L       (REG_TC_CHIP_TOP_BASE + 0x8C)
#define  REG_TC_CHIP_TOP_46_H       (REG_TC_CHIP_TOP_BASE + 0x8D)
#define  REG_TC_CHIP_TOP_47_L       (REG_TC_CHIP_TOP_BASE + 0x8E)
#define  REG_TC_CHIP_TOP_47_H       (REG_TC_CHIP_TOP_BASE + 0x8F)
#define  REG_TC_CHIP_TOP_48_L       (REG_TC_CHIP_TOP_BASE + 0x90)
#define  REG_TC_CHIP_TOP_48_H       (REG_TC_CHIP_TOP_BASE + 0x91)
#define  REG_TC_CHIP_TOP_49_L       (REG_TC_CHIP_TOP_BASE + 0x92)
#define  REG_TC_CHIP_TOP_49_H       (REG_TC_CHIP_TOP_BASE + 0x93)
#define  REG_TC_CHIP_TOP_4A_L       (REG_TC_CHIP_TOP_BASE + 0x94)
#define  REG_TC_CHIP_TOP_4A_H       (REG_TC_CHIP_TOP_BASE + 0x95)
#define  REG_TC_CHIP_TOP_4B_L       (REG_TC_CHIP_TOP_BASE + 0x96)
#define  REG_TC_CHIP_TOP_4B_H       (REG_TC_CHIP_TOP_BASE + 0x97)
#define  REG_TC_CHIP_TOP_4C_L       (REG_TC_CHIP_TOP_BASE + 0x98)
#define  REG_TC_CHIP_TOP_4C_H       (REG_TC_CHIP_TOP_BASE + 0x99)
#define  REG_TC_CHIP_TOP_4D_L       (REG_TC_CHIP_TOP_BASE + 0x9A)
#define  REG_TC_CHIP_TOP_4D_H       (REG_TC_CHIP_TOP_BASE + 0x9B)
#define  REG_TC_CHIP_TOP_4E_L       (REG_TC_CHIP_TOP_BASE + 0x9C)
#define  REG_TC_CHIP_TOP_4E_H       (REG_TC_CHIP_TOP_BASE + 0x9D)
#define  REG_TC_CHIP_TOP_4F_L       (REG_TC_CHIP_TOP_BASE + 0x9E)
#define  REG_TC_CHIP_TOP_4F_H       (REG_TC_CHIP_TOP_BASE + 0x9F)
#define  REG_TC_CHIP_TOP_50_L       (REG_TC_CHIP_TOP_BASE + 0xA0)
#define  REG_TC_CHIP_TOP_50_H       (REG_TC_CHIP_TOP_BASE + 0xA1)
#define  REG_TC_CHIP_TOP_51_L       (REG_TC_CHIP_TOP_BASE + 0xA2)
#define  REG_TC_CHIP_TOP_51_H       (REG_TC_CHIP_TOP_BASE + 0xA3)
#define  REG_TC_CHIP_TOP_52_L       (REG_TC_CHIP_TOP_BASE + 0xA4)
#define  REG_TC_CHIP_TOP_52_H       (REG_TC_CHIP_TOP_BASE + 0xA5)
#define  REG_TC_CHIP_TOP_53_L       (REG_TC_CHIP_TOP_BASE + 0xA6)
#define  REG_TC_CHIP_TOP_53_H       (REG_TC_CHIP_TOP_BASE + 0xA7)
#define  REG_TC_CHIP_TOP_54_L       (REG_TC_CHIP_TOP_BASE + 0xA8)
#define  REG_TC_CHIP_TOP_54_H       (REG_TC_CHIP_TOP_BASE + 0xA9)
#define  REG_TC_CHIP_TOP_55_L       (REG_TC_CHIP_TOP_BASE + 0xAA)
#define  REG_TC_CHIP_TOP_55_H       (REG_TC_CHIP_TOP_BASE + 0xAB)
#define  REG_TC_CHIP_TOP_56_L       (REG_TC_CHIP_TOP_BASE + 0xAC)
#define  REG_TC_CHIP_TOP_56_H       (REG_TC_CHIP_TOP_BASE + 0xAD)
#define  REG_TC_CHIP_TOP_57_L       (REG_TC_CHIP_TOP_BASE + 0xAE)
#define  REG_TC_CHIP_TOP_57_H       (REG_TC_CHIP_TOP_BASE + 0xAF)
#define  REG_TC_CHIP_TOP_58_L       (REG_TC_CHIP_TOP_BASE + 0xB0)
#define  REG_TC_CHIP_TOP_58_H       (REG_TC_CHIP_TOP_BASE + 0xB1)
#define  REG_TC_CHIP_TOP_59_L       (REG_TC_CHIP_TOP_BASE + 0xB2)
#define  REG_TC_CHIP_TOP_59_H       (REG_TC_CHIP_TOP_BASE + 0xB3)
#define  REG_TC_CHIP_TOP_5A_L       (REG_TC_CHIP_TOP_BASE + 0xB4)
#define  REG_TC_CHIP_TOP_5A_H       (REG_TC_CHIP_TOP_BASE + 0xB5)
#define  REG_TC_CHIP_TOP_5B_L       (REG_TC_CHIP_TOP_BASE + 0xB6)
#define  REG_TC_CHIP_TOP_5B_H       (REG_TC_CHIP_TOP_BASE + 0xB7)
#define  REG_TC_CHIP_TOP_5C_L       (REG_TC_CHIP_TOP_BASE + 0xB8)
#define  REG_TC_CHIP_TOP_5C_H       (REG_TC_CHIP_TOP_BASE + 0xB9)
#define  REG_TC_CHIP_TOP_5D_L       (REG_TC_CHIP_TOP_BASE + 0xBA)
#define  REG_TC_CHIP_TOP_5D_H       (REG_TC_CHIP_TOP_BASE + 0xBB)
#define  REG_TC_CHIP_TOP_5E_L       (REG_TC_CHIP_TOP_BASE + 0xBC)
#define  REG_TC_CHIP_TOP_5E_H       (REG_TC_CHIP_TOP_BASE + 0xBD)
#define  REG_TC_CHIP_TOP_5F_L       (REG_TC_CHIP_TOP_BASE + 0xBE)
#define  REG_TC_CHIP_TOP_5F_H       (REG_TC_CHIP_TOP_BASE + 0xBF)
#define  REG_TC_CHIP_TOP_60_L       (REG_TC_CHIP_TOP_BASE + 0xC0)
#define  REG_TC_CHIP_TOP_60_H       (REG_TC_CHIP_TOP_BASE + 0xC1)
#define  REG_TC_CHIP_TOP_61_L       (REG_TC_CHIP_TOP_BASE + 0xC2)
#define  REG_TC_CHIP_TOP_61_H       (REG_TC_CHIP_TOP_BASE + 0xC3)
#define  REG_TC_CHIP_TOP_62_L       (REG_TC_CHIP_TOP_BASE + 0xC4)
#define  REG_TC_CHIP_TOP_62_H       (REG_TC_CHIP_TOP_BASE + 0xC5)
#define  REG_TC_CHIP_TOP_63_L       (REG_TC_CHIP_TOP_BASE + 0xC6)
#define  REG_TC_CHIP_TOP_63_H       (REG_TC_CHIP_TOP_BASE + 0xC7)
#define  REG_TC_CHIP_TOP_64_L       (REG_TC_CHIP_TOP_BASE + 0xC8)
#define  REG_TC_CHIP_TOP_64_H       (REG_TC_CHIP_TOP_BASE + 0xC9)
#define  REG_TC_CHIP_TOP_65_L       (REG_TC_CHIP_TOP_BASE + 0xCA)
#define  REG_TC_CHIP_TOP_65_H       (REG_TC_CHIP_TOP_BASE + 0xCB)
#define  REG_TC_CHIP_TOP_66_L       (REG_TC_CHIP_TOP_BASE + 0xCC)
#define  REG_TC_CHIP_TOP_66_H       (REG_TC_CHIP_TOP_BASE + 0xCD)
#define  REG_TC_CHIP_TOP_67_L       (REG_TC_CHIP_TOP_BASE + 0xCE)
#define  REG_TC_CHIP_TOP_67_H       (REG_TC_CHIP_TOP_BASE + 0xCF)
#define  REG_TC_CHIP_TOP_68_L       (REG_TC_CHIP_TOP_BASE + 0xD0)
#define  REG_TC_CHIP_TOP_68_H       (REG_TC_CHIP_TOP_BASE + 0xD1)
#define  REG_TC_CHIP_TOP_69_L       (REG_TC_CHIP_TOP_BASE + 0xD2)
#define  REG_TC_CHIP_TOP_69_H       (REG_TC_CHIP_TOP_BASE + 0xD3)
#define  REG_TC_CHIP_TOP_6A_L       (REG_TC_CHIP_TOP_BASE + 0xD4)
#define  REG_TC_CHIP_TOP_6A_H       (REG_TC_CHIP_TOP_BASE + 0xD5)
#define  REG_TC_CHIP_TOP_6B_L       (REG_TC_CHIP_TOP_BASE + 0xD6)
#define  REG_TC_CHIP_TOP_6B_H       (REG_TC_CHIP_TOP_BASE + 0xD7)
#define  REG_TC_CHIP_TOP_6C_L       (REG_TC_CHIP_TOP_BASE + 0xD8)
#define  REG_TC_CHIP_TOP_6C_H       (REG_TC_CHIP_TOP_BASE + 0xD9)
#define  REG_TC_CHIP_TOP_6D_L       (REG_TC_CHIP_TOP_BASE + 0xDA)
#define  REG_TC_CHIP_TOP_6D_H       (REG_TC_CHIP_TOP_BASE + 0xDB)
#define  REG_TC_CHIP_TOP_6E_L       (REG_TC_CHIP_TOP_BASE + 0xDC)
#define  REG_TC_CHIP_TOP_6E_H       (REG_TC_CHIP_TOP_BASE + 0xDD)
#define  REG_TC_CHIP_TOP_6F_L       (REG_TC_CHIP_TOP_BASE + 0xDE)
#define  REG_TC_CHIP_TOP_6F_H       (REG_TC_CHIP_TOP_BASE + 0xDF)
#define  REG_TC_CHIP_TOP_70_L       (REG_TC_CHIP_TOP_BASE + 0xE0)
#define  REG_TC_CHIP_TOP_70_H       (REG_TC_CHIP_TOP_BASE + 0xE1)
#define  REG_TC_CHIP_TOP_71_L       (REG_TC_CHIP_TOP_BASE + 0xE2)
#define  REG_TC_CHIP_TOP_71_H       (REG_TC_CHIP_TOP_BASE + 0xE3)
#define  REG_TC_CHIP_TOP_72_L       (REG_TC_CHIP_TOP_BASE + 0xE4)
#define  REG_TC_CHIP_TOP_72_H       (REG_TC_CHIP_TOP_BASE + 0xE5)
#define  REG_TC_CHIP_TOP_73_L       (REG_TC_CHIP_TOP_BASE + 0xE6)
#define  REG_TC_CHIP_TOP_73_H       (REG_TC_CHIP_TOP_BASE + 0xE7)
#define  REG_TC_CHIP_TOP_74_L       (REG_TC_CHIP_TOP_BASE + 0xE8)
#define  REG_TC_CHIP_TOP_74_H       (REG_TC_CHIP_TOP_BASE + 0xE9)
#define  REG_TC_CHIP_TOP_75_L       (REG_TC_CHIP_TOP_BASE + 0xEA)
#define  REG_TC_CHIP_TOP_75_H       (REG_TC_CHIP_TOP_BASE + 0xEB)
#define  REG_TC_CHIP_TOP_76_L       (REG_TC_CHIP_TOP_BASE + 0xEC)
#define  REG_TC_CHIP_TOP_76_H       (REG_TC_CHIP_TOP_BASE + 0xED)
#define  REG_TC_CHIP_TOP_77_L       (REG_TC_CHIP_TOP_BASE + 0xEE)
#define  REG_TC_CHIP_TOP_77_H       (REG_TC_CHIP_TOP_BASE + 0xEF)
#define  REG_TC_CHIP_TOP_78_L       (REG_TC_CHIP_TOP_BASE + 0xF0)
#define  REG_TC_CHIP_TOP_78_H       (REG_TC_CHIP_TOP_BASE + 0xF1)
#define  REG_TC_CHIP_TOP_79_L       (REG_TC_CHIP_TOP_BASE + 0xF2)
#define  REG_TC_CHIP_TOP_79_H       (REG_TC_CHIP_TOP_BASE + 0xF3)
#define  REG_TC_CHIP_TOP_7A_L       (REG_TC_CHIP_TOP_BASE + 0xF4)
#define  REG_TC_CHIP_TOP_7A_H       (REG_TC_CHIP_TOP_BASE + 0xF5)
#define  REG_TC_CHIP_TOP_7B_L       (REG_TC_CHIP_TOP_BASE + 0xF6)
#define  REG_TC_CHIP_TOP_7B_H       (REG_TC_CHIP_TOP_BASE + 0xF7)
#define  REG_TC_CHIP_TOP_7C_L       (REG_TC_CHIP_TOP_BASE + 0xF8)
#define  REG_TC_CHIP_TOP_7C_H       (REG_TC_CHIP_TOP_BASE + 0xF9)
#define  REG_TC_CHIP_TOP_7D_L       (REG_TC_CHIP_TOP_BASE + 0xFA)
#define  REG_TC_CHIP_TOP_7D_H       (REG_TC_CHIP_TOP_BASE + 0xFB)
#define  REG_TC_CHIP_TOP_7E_L       (REG_TC_CHIP_TOP_BASE + 0xFC)
#define  REG_TC_CHIP_TOP_7E_H       (REG_TC_CHIP_TOP_BASE + 0xFD)
#define  REG_TC_CHIP_TOP_7F_L       (REG_TC_CHIP_TOP_BASE + 0xFE)
#define  REG_TC_CHIP_TOP_7F_H       (REG_TC_CHIP_TOP_BASE + 0xFF)

#define  REG_TC_LPLL_00_L       (REG_TC_LPLL_BASE + 0x00)
#define  REG_TC_LPLL_00_H       (REG_TC_LPLL_BASE + 0x01)
#define  REG_TC_LPLL_01_L       (REG_TC_LPLL_BASE + 0x02)
#define  REG_TC_LPLL_01_H       (REG_TC_LPLL_BASE + 0x03)
#define  REG_TC_LPLL_02_L       (REG_TC_LPLL_BASE + 0x04)
#define  REG_TC_LPLL_02_H       (REG_TC_LPLL_BASE + 0x05)
#define  REG_TC_LPLL_03_L       (REG_TC_LPLL_BASE + 0x06)
#define  REG_TC_LPLL_03_H       (REG_TC_LPLL_BASE + 0x07)
#define  REG_TC_LPLL_04_L       (REG_TC_LPLL_BASE + 0x08)
#define  REG_TC_LPLL_04_H       (REG_TC_LPLL_BASE + 0x09)
#define  REG_TC_LPLL_05_L       (REG_TC_LPLL_BASE + 0x0A)
#define  REG_TC_LPLL_05_H       (REG_TC_LPLL_BASE + 0x0B)
#define  REG_TC_LPLL_06_L       (REG_TC_LPLL_BASE + 0x0C)
#define  REG_TC_LPLL_06_H       (REG_TC_LPLL_BASE + 0x0D)
#define  REG_TC_LPLL_07_L       (REG_TC_LPLL_BASE + 0x0E)
#define  REG_TC_LPLL_07_H       (REG_TC_LPLL_BASE + 0x0F)
#define  REG_TC_LPLL_08_L       (REG_TC_LPLL_BASE + 0x10)
#define  REG_TC_LPLL_08_H       (REG_TC_LPLL_BASE + 0x11)
#define  REG_TC_LPLL_09_L       (REG_TC_LPLL_BASE + 0x12)
#define  REG_TC_LPLL_09_H       (REG_TC_LPLL_BASE + 0x13)
#define  REG_TC_LPLL_0A_L       (REG_TC_LPLL_BASE + 0x14)
#define  REG_TC_LPLL_0A_H       (REG_TC_LPLL_BASE + 0x15)
#define  REG_TC_LPLL_0B_L       (REG_TC_LPLL_BASE + 0x16)
#define  REG_TC_LPLL_0B_H       (REG_TC_LPLL_BASE + 0x17)
#define  REG_TC_LPLL_0C_L       (REG_TC_LPLL_BASE + 0x18)
#define  REG_TC_LPLL_0C_H       (REG_TC_LPLL_BASE + 0x19)
#define  REG_TC_LPLL_0D_L       (REG_TC_LPLL_BASE + 0x1A)
#define  REG_TC_LPLL_0D_H       (REG_TC_LPLL_BASE + 0x1B)
#define  REG_TC_LPLL_0E_L       (REG_TC_LPLL_BASE + 0x1C)
#define  REG_TC_LPLL_0E_H       (REG_TC_LPLL_BASE + 0x1D)
#define  REG_TC_LPLL_0F_L       (REG_TC_LPLL_BASE + 0x1E)
#define  REG_TC_LPLL_0F_H       (REG_TC_LPLL_BASE + 0x1F)
#define  REG_TC_LPLL_10_L       (REG_TC_LPLL_BASE + 0x20)
#define  REG_TC_LPLL_10_H       (REG_TC_LPLL_BASE + 0x21)
#define  REG_TC_LPLL_11_L       (REG_TC_LPLL_BASE + 0x22)
#define  REG_TC_LPLL_11_H       (REG_TC_LPLL_BASE + 0x23)
#define  REG_TC_LPLL_12_L       (REG_TC_LPLL_BASE + 0x24)
#define  REG_TC_LPLL_12_H       (REG_TC_LPLL_BASE + 0x25)
#define  REG_TC_LPLL_13_L       (REG_TC_LPLL_BASE + 0x26)
#define  REG_TC_LPLL_13_H       (REG_TC_LPLL_BASE + 0x27)
#define  REG_TC_LPLL_14_L       (REG_TC_LPLL_BASE + 0x28)
#define  REG_TC_LPLL_14_H       (REG_TC_LPLL_BASE + 0x29)
#define  REG_TC_LPLL_15_L       (REG_TC_LPLL_BASE + 0x2A)
#define  REG_TC_LPLL_15_H       (REG_TC_LPLL_BASE + 0x2B)
#define  REG_TC_LPLL_16_L       (REG_TC_LPLL_BASE + 0x2C)
#define  REG_TC_LPLL_16_H       (REG_TC_LPLL_BASE + 0x2D)
#define  REG_TC_LPLL_17_L       (REG_TC_LPLL_BASE + 0x2E)
#define  REG_TC_LPLL_17_H       (REG_TC_LPLL_BASE + 0x2F)
#define  REG_TC_LPLL_18_L       (REG_TC_LPLL_BASE + 0x30)
#define  REG_TC_LPLL_18_H       (REG_TC_LPLL_BASE + 0x31)
#define  REG_TC_LPLL_19_L       (REG_TC_LPLL_BASE + 0x32)
#define  REG_TC_LPLL_19_H       (REG_TC_LPLL_BASE + 0x33)
#define  REG_TC_LPLL_1A_L       (REG_TC_LPLL_BASE + 0x34)
#define  REG_TC_LPLL_1A_H       (REG_TC_LPLL_BASE + 0x35)
#define  REG_TC_LPLL_1B_L       (REG_TC_LPLL_BASE + 0x36)
#define  REG_TC_LPLL_1B_H       (REG_TC_LPLL_BASE + 0x37)
#define  REG_TC_LPLL_1C_L       (REG_TC_LPLL_BASE + 0x38)
#define  REG_TC_LPLL_1C_H       (REG_TC_LPLL_BASE + 0x39)
#define  REG_TC_LPLL_1D_L       (REG_TC_LPLL_BASE + 0x3A)
#define  REG_TC_LPLL_1D_H       (REG_TC_LPLL_BASE + 0x3B)
#define  REG_TC_LPLL_1E_L       (REG_TC_LPLL_BASE + 0x3C)
#define  REG_TC_LPLL_1E_H       (REG_TC_LPLL_BASE + 0x3D)
#define  REG_TC_LPLL_1F_L       (REG_TC_LPLL_BASE + 0x3E)
#define  REG_TC_LPLL_1F_H       (REG_TC_LPLL_BASE + 0x3F)
#define  REG_TC_LPLL_20_L       (REG_TC_LPLL_BASE + 0x40)
#define  REG_TC_LPLL_20_H       (REG_TC_LPLL_BASE + 0x41)
#define  REG_TC_LPLL_21_L       (REG_TC_LPLL_BASE + 0x42)
#define  REG_TC_LPLL_21_H       (REG_TC_LPLL_BASE + 0x43)
#define  REG_TC_LPLL_22_L       (REG_TC_LPLL_BASE + 0x44)
#define  REG_TC_LPLL_22_H       (REG_TC_LPLL_BASE + 0x45)
#define  REG_TC_LPLL_23_L       (REG_TC_LPLL_BASE + 0x46)
#define  REG_TC_LPLL_23_H       (REG_TC_LPLL_BASE + 0x47)
#define  REG_TC_LPLL_24_L       (REG_TC_LPLL_BASE + 0x48)
#define  REG_TC_LPLL_24_H       (REG_TC_LPLL_BASE + 0x49)
#define  REG_TC_LPLL_25_L       (REG_TC_LPLL_BASE + 0x4A)
#define  REG_TC_LPLL_25_H       (REG_TC_LPLL_BASE + 0x4B)
#define  REG_TC_LPLL_26_L       (REG_TC_LPLL_BASE + 0x4C)
#define  REG_TC_LPLL_26_H       (REG_TC_LPLL_BASE + 0x4D)
#define  REG_TC_LPLL_27_L       (REG_TC_LPLL_BASE + 0x4E)
#define  REG_TC_LPLL_27_H       (REG_TC_LPLL_BASE + 0x4F)
#define  REG_TC_LPLL_28_L       (REG_TC_LPLL_BASE + 0x50)
#define  REG_TC_LPLL_28_H       (REG_TC_LPLL_BASE + 0x51)
#define  REG_TC_LPLL_29_L       (REG_TC_LPLL_BASE + 0x52)
#define  REG_TC_LPLL_29_H       (REG_TC_LPLL_BASE + 0x53)
#define  REG_TC_LPLL_2A_L       (REG_TC_LPLL_BASE + 0x54)
#define  REG_TC_LPLL_2A_H       (REG_TC_LPLL_BASE + 0x55)
#define  REG_TC_LPLL_2B_L       (REG_TC_LPLL_BASE + 0x56)
#define  REG_TC_LPLL_2B_H       (REG_TC_LPLL_BASE + 0x57)
#define  REG_TC_LPLL_2C_L       (REG_TC_LPLL_BASE + 0x58)
#define  REG_TC_LPLL_2C_H       (REG_TC_LPLL_BASE + 0x59)
#define  REG_TC_LPLL_2D_L       (REG_TC_LPLL_BASE + 0x5A)
#define  REG_TC_LPLL_2D_H       (REG_TC_LPLL_BASE + 0x5B)
#define  REG_TC_LPLL_2E_L       (REG_TC_LPLL_BASE + 0x5C)
#define  REG_TC_LPLL_2E_H       (REG_TC_LPLL_BASE + 0x5D)
#define  REG_TC_LPLL_2F_L       (REG_TC_LPLL_BASE + 0x5E)
#define  REG_TC_LPLL_2F_H       (REG_TC_LPLL_BASE + 0x5F)
#define  REG_TC_LPLL_30_L       (REG_TC_LPLL_BASE + 0x60)
#define  REG_TC_LPLL_30_H       (REG_TC_LPLL_BASE + 0x61)
#define  REG_TC_LPLL_31_L       (REG_TC_LPLL_BASE + 0x62)
#define  REG_TC_LPLL_31_H       (REG_TC_LPLL_BASE + 0x63)
#define  REG_TC_LPLL_32_L       (REG_TC_LPLL_BASE + 0x64)
#define  REG_TC_LPLL_32_H       (REG_TC_LPLL_BASE + 0x65)
#define  REG_TC_LPLL_33_L       (REG_TC_LPLL_BASE + 0x66)
#define  REG_TC_LPLL_33_H       (REG_TC_LPLL_BASE + 0x67)
#define  REG_TC_LPLL_34_L       (REG_TC_LPLL_BASE + 0x68)
#define  REG_TC_LPLL_34_H       (REG_TC_LPLL_BASE + 0x69)
#define  REG_TC_LPLL_35_L       (REG_TC_LPLL_BASE + 0x6A)
#define  REG_TC_LPLL_35_H       (REG_TC_LPLL_BASE + 0x6B)
#define  REG_TC_LPLL_36_L       (REG_TC_LPLL_BASE + 0x6C)
#define  REG_TC_LPLL_36_H       (REG_TC_LPLL_BASE + 0x6D)
#define  REG_TC_LPLL_37_L       (REG_TC_LPLL_BASE + 0x6E)
#define  REG_TC_LPLL_37_H       (REG_TC_LPLL_BASE + 0x6F)
#define  REG_TC_LPLL_38_L       (REG_TC_LPLL_BASE + 0x70)
#define  REG_TC_LPLL_38_H       (REG_TC_LPLL_BASE + 0x71)
#define  REG_TC_LPLL_39_L       (REG_TC_LPLL_BASE + 0x72)
#define  REG_TC_LPLL_39_H       (REG_TC_LPLL_BASE + 0x73)
#define  REG_TC_LPLL_3A_L       (REG_TC_LPLL_BASE + 0x74)
#define  REG_TC_LPLL_3A_H       (REG_TC_LPLL_BASE + 0x75)
#define  REG_TC_LPLL_3B_L       (REG_TC_LPLL_BASE + 0x76)
#define  REG_TC_LPLL_3B_H       (REG_TC_LPLL_BASE + 0x77)
#define  REG_TC_LPLL_3C_L       (REG_TC_LPLL_BASE + 0x78)
#define  REG_TC_LPLL_3C_H       (REG_TC_LPLL_BASE + 0x79)
#define  REG_TC_LPLL_3D_L       (REG_TC_LPLL_BASE + 0x7A)
#define  REG_TC_LPLL_3D_H       (REG_TC_LPLL_BASE + 0x7B)
#define  REG_TC_LPLL_3E_L       (REG_TC_LPLL_BASE + 0x7C)
#define  REG_TC_LPLL_3E_H       (REG_TC_LPLL_BASE + 0x7D)
#define  REG_TC_LPLL_3F_L       (REG_TC_LPLL_BASE + 0x7E)
#define  REG_TC_LPLL_3F_H       (REG_TC_LPLL_BASE + 0x7F)
#define  REG_TC_LPLL_40_L       (REG_TC_LPLL_BASE + 0x80)
#define  REG_TC_LPLL_40_H       (REG_TC_LPLL_BASE + 0x81)
#define  REG_TC_LPLL_41_L       (REG_TC_LPLL_BASE + 0x82)
#define  REG_TC_LPLL_41_H       (REG_TC_LPLL_BASE + 0x83)
#define  REG_TC_LPLL_42_L       (REG_TC_LPLL_BASE + 0x84)
#define  REG_TC_LPLL_42_H       (REG_TC_LPLL_BASE + 0x85)
#define  REG_TC_LPLL_43_L       (REG_TC_LPLL_BASE + 0x86)
#define  REG_TC_LPLL_43_H       (REG_TC_LPLL_BASE + 0x87)
#define  REG_TC_LPLL_44_L       (REG_TC_LPLL_BASE + 0x88)
#define  REG_TC_LPLL_44_H       (REG_TC_LPLL_BASE + 0x89)
#define  REG_TC_LPLL_45_L       (REG_TC_LPLL_BASE + 0x8A)
#define  REG_TC_LPLL_45_H       (REG_TC_LPLL_BASE + 0x8B)
#define  REG_TC_LPLL_46_L       (REG_TC_LPLL_BASE + 0x8C)
#define  REG_TC_LPLL_46_H       (REG_TC_LPLL_BASE + 0x8D)
#define  REG_TC_LPLL_47_L       (REG_TC_LPLL_BASE + 0x8E)
#define  REG_TC_LPLL_47_H       (REG_TC_LPLL_BASE + 0x8F)
#define  REG_TC_LPLL_48_L       (REG_TC_LPLL_BASE + 0x90)
#define  REG_TC_LPLL_48_H       (REG_TC_LPLL_BASE + 0x91)
#define  REG_TC_LPLL_49_L       (REG_TC_LPLL_BASE + 0x92)
#define  REG_TC_LPLL_49_H       (REG_TC_LPLL_BASE + 0x93)
#define  REG_TC_LPLL_4A_L       (REG_TC_LPLL_BASE + 0x94)
#define  REG_TC_LPLL_4A_H       (REG_TC_LPLL_BASE + 0x95)
#define  REG_TC_LPLL_4B_L       (REG_TC_LPLL_BASE + 0x96)
#define  REG_TC_LPLL_4B_H       (REG_TC_LPLL_BASE + 0x97)
#define  REG_TC_LPLL_4C_L       (REG_TC_LPLL_BASE + 0x98)
#define  REG_TC_LPLL_4C_H       (REG_TC_LPLL_BASE + 0x99)
#define  REG_TC_LPLL_4D_L       (REG_TC_LPLL_BASE + 0x9A)
#define  REG_TC_LPLL_4D_H       (REG_TC_LPLL_BASE + 0x9B)
#define  REG_TC_LPLL_4E_L       (REG_TC_LPLL_BASE + 0x9C)
#define  REG_TC_LPLL_4E_H       (REG_TC_LPLL_BASE + 0x9D)
#define  REG_TC_LPLL_4F_L       (REG_TC_LPLL_BASE + 0x9E)
#define  REG_TC_LPLL_4F_H       (REG_TC_LPLL_BASE + 0x9F)
#define  REG_TC_LPLL_50_L       (REG_TC_LPLL_BASE + 0xA0)
#define  REG_TC_LPLL_50_H       (REG_TC_LPLL_BASE + 0xA1)
#define  REG_TC_LPLL_51_L       (REG_TC_LPLL_BASE + 0xA2)
#define  REG_TC_LPLL_51_H       (REG_TC_LPLL_BASE + 0xA3)
#define  REG_TC_LPLL_52_L       (REG_TC_LPLL_BASE + 0xA4)
#define  REG_TC_LPLL_52_H       (REG_TC_LPLL_BASE + 0xA5)
#define  REG_TC_LPLL_53_L       (REG_TC_LPLL_BASE + 0xA6)
#define  REG_TC_LPLL_53_H       (REG_TC_LPLL_BASE + 0xA7)
#define  REG_TC_LPLL_54_L       (REG_TC_LPLL_BASE + 0xA8)
#define  REG_TC_LPLL_54_H       (REG_TC_LPLL_BASE + 0xA9)
#define  REG_TC_LPLL_55_L       (REG_TC_LPLL_BASE + 0xAA)
#define  REG_TC_LPLL_55_H       (REG_TC_LPLL_BASE + 0xAB)
#define  REG_TC_LPLL_56_L       (REG_TC_LPLL_BASE + 0xAC)
#define  REG_TC_LPLL_56_H       (REG_TC_LPLL_BASE + 0xAD)
#define  REG_TC_LPLL_57_L       (REG_TC_LPLL_BASE + 0xAE)
#define  REG_TC_LPLL_57_H       (REG_TC_LPLL_BASE + 0xAF)
#define  REG_TC_LPLL_58_L       (REG_TC_LPLL_BASE + 0xB0)
#define  REG_TC_LPLL_58_H       (REG_TC_LPLL_BASE + 0xB1)
#define  REG_TC_LPLL_59_L       (REG_TC_LPLL_BASE + 0xB2)
#define  REG_TC_LPLL_59_H       (REG_TC_LPLL_BASE + 0xB3)
#define  REG_TC_LPLL_5A_L       (REG_TC_LPLL_BASE + 0xB4)
#define  REG_TC_LPLL_5A_H       (REG_TC_LPLL_BASE + 0xB5)
#define  REG_TC_LPLL_5B_L       (REG_TC_LPLL_BASE + 0xB6)
#define  REG_TC_LPLL_5B_H       (REG_TC_LPLL_BASE + 0xB7)
#define  REG_TC_LPLL_5C_L       (REG_TC_LPLL_BASE + 0xB8)
#define  REG_TC_LPLL_5C_H       (REG_TC_LPLL_BASE + 0xB9)
#define  REG_TC_LPLL_5D_L       (REG_TC_LPLL_BASE + 0xBA)
#define  REG_TC_LPLL_5D_H       (REG_TC_LPLL_BASE + 0xBB)
#define  REG_TC_LPLL_5E_L       (REG_TC_LPLL_BASE + 0xBC)
#define  REG_TC_LPLL_5E_H       (REG_TC_LPLL_BASE + 0xBD)
#define  REG_TC_LPLL_5F_L       (REG_TC_LPLL_BASE + 0xBE)
#define  REG_TC_LPLL_5F_H       (REG_TC_LPLL_BASE + 0xBF)
#define  REG_TC_LPLL_60_L       (REG_TC_LPLL_BASE + 0xC0)
#define  REG_TC_LPLL_60_H       (REG_TC_LPLL_BASE + 0xC1)
#define  REG_TC_LPLL_61_L       (REG_TC_LPLL_BASE + 0xC2)
#define  REG_TC_LPLL_61_H       (REG_TC_LPLL_BASE + 0xC3)
#define  REG_TC_LPLL_62_L       (REG_TC_LPLL_BASE + 0xC4)
#define  REG_TC_LPLL_62_H       (REG_TC_LPLL_BASE + 0xC5)
#define  REG_TC_LPLL_63_L       (REG_TC_LPLL_BASE + 0xC6)
#define  REG_TC_LPLL_63_H       (REG_TC_LPLL_BASE + 0xC7)
#define  REG_TC_LPLL_64_L       (REG_TC_LPLL_BASE + 0xC8)
#define  REG_TC_LPLL_64_H       (REG_TC_LPLL_BASE + 0xC9)
#define  REG_TC_LPLL_65_L       (REG_TC_LPLL_BASE + 0xCA)
#define  REG_TC_LPLL_65_H       (REG_TC_LPLL_BASE + 0xCB)
#define  REG_TC_LPLL_66_L       (REG_TC_LPLL_BASE + 0xCC)
#define  REG_TC_LPLL_66_H       (REG_TC_LPLL_BASE + 0xCD)
#define  REG_TC_LPLL_67_L       (REG_TC_LPLL_BASE + 0xCE)
#define  REG_TC_LPLL_67_H       (REG_TC_LPLL_BASE + 0xCF)
#define  REG_TC_LPLL_68_L       (REG_TC_LPLL_BASE + 0xD0)
#define  REG_TC_LPLL_68_H       (REG_TC_LPLL_BASE + 0xD1)
#define  REG_TC_LPLL_69_L       (REG_TC_LPLL_BASE + 0xD2)
#define  REG_TC_LPLL_69_H       (REG_TC_LPLL_BASE + 0xD3)
#define  REG_TC_LPLL_6A_L       (REG_TC_LPLL_BASE + 0xD4)
#define  REG_TC_LPLL_6A_H       (REG_TC_LPLL_BASE + 0xD5)
#define  REG_TC_LPLL_6B_L       (REG_TC_LPLL_BASE + 0xD6)
#define  REG_TC_LPLL_6B_H       (REG_TC_LPLL_BASE + 0xD7)
#define  REG_TC_LPLL_6C_L       (REG_TC_LPLL_BASE + 0xD8)
#define  REG_TC_LPLL_6C_H       (REG_TC_LPLL_BASE + 0xD9)
#define  REG_TC_LPLL_6D_L       (REG_TC_LPLL_BASE + 0xDA)
#define  REG_TC_LPLL_6D_H       (REG_TC_LPLL_BASE + 0xDB)
#define  REG_TC_LPLL_6E_L       (REG_TC_LPLL_BASE + 0xDC)
#define  REG_TC_LPLL_6E_H       (REG_TC_LPLL_BASE + 0xDD)
#define  REG_TC_LPLL_6F_L       (REG_TC_LPLL_BASE + 0xDE)
#define  REG_TC_LPLL_6F_H       (REG_TC_LPLL_BASE + 0xDF)
#define  REG_TC_LPLL_70_L       (REG_TC_LPLL_BASE + 0xE0)
#define  REG_TC_LPLL_70_H       (REG_TC_LPLL_BASE + 0xE1)
#define  REG_TC_LPLL_71_L       (REG_TC_LPLL_BASE + 0xE2)
#define  REG_TC_LPLL_71_H       (REG_TC_LPLL_BASE + 0xE3)
#define  REG_TC_LPLL_72_L       (REG_TC_LPLL_BASE + 0xE4)
#define  REG_TC_LPLL_72_H       (REG_TC_LPLL_BASE + 0xE5)
#define  REG_TC_LPLL_73_L       (REG_TC_LPLL_BASE + 0xE6)
#define  REG_TC_LPLL_73_H       (REG_TC_LPLL_BASE + 0xE7)
#define  REG_TC_LPLL_74_L       (REG_TC_LPLL_BASE + 0xE8)
#define  REG_TC_LPLL_74_H       (REG_TC_LPLL_BASE + 0xE9)
#define  REG_TC_LPLL_75_L       (REG_TC_LPLL_BASE + 0xEA)
#define  REG_TC_LPLL_75_H       (REG_TC_LPLL_BASE + 0xEB)
#define  REG_TC_LPLL_76_L       (REG_TC_LPLL_BASE + 0xEC)
#define  REG_TC_LPLL_76_H       (REG_TC_LPLL_BASE + 0xED)
#define  REG_TC_LPLL_77_L       (REG_TC_LPLL_BASE + 0xEE)
#define  REG_TC_LPLL_77_H       (REG_TC_LPLL_BASE + 0xEF)
#define  REG_TC_LPLL_78_L       (REG_TC_LPLL_BASE + 0xF0)
#define  REG_TC_LPLL_78_H       (REG_TC_LPLL_BASE + 0xF1)
#define  REG_TC_LPLL_79_L       (REG_TC_LPLL_BASE + 0xF2)
#define  REG_TC_LPLL_79_H       (REG_TC_LPLL_BASE + 0xF3)
#define  REG_TC_LPLL_7A_L       (REG_TC_LPLL_BASE + 0xF4)
#define  REG_TC_LPLL_7A_H       (REG_TC_LPLL_BASE + 0xF5)
#define  REG_TC_LPLL_7B_L       (REG_TC_LPLL_BASE + 0xF6)
#define  REG_TC_LPLL_7B_H       (REG_TC_LPLL_BASE + 0xF7)
#define  REG_TC_LPLL_7C_L       (REG_TC_LPLL_BASE + 0xF8)
#define  REG_TC_LPLL_7C_H       (REG_TC_LPLL_BASE + 0xF9)
#define  REG_TC_LPLL_7D_L       (REG_TC_LPLL_BASE + 0xFA)
#define  REG_TC_LPLL_7D_H       (REG_TC_LPLL_BASE + 0xFB)
#define  REG_TC_LPLL_7E_L       (REG_TC_LPLL_BASE + 0xFC)
#define  REG_TC_LPLL_7E_H       (REG_TC_LPLL_BASE + 0xFD)
#define  REG_TC_LPLL_7F_L       (REG_TC_LPLL_BASE + 0xFE)
#define  REG_TC_LPLL_7F_H       (REG_TC_LPLL_BASE + 0xFF)

#define  REG_TC_SC_VOP_BK10_00_L       _PK_L_(0x10, 0x00)
#define  REG_TC_SC_VOP_BK10_00_H       _PK_H_(0x10, 0x00)
#define  REG_TC_SC_VOP_BK10_01_L       _PK_L_(0x10, 0x01)
#define  REG_TC_SC_VOP_BK10_01_H       _PK_H_(0x10, 0x01)
#define  REG_TC_SC_VOP_BK10_02_L       _PK_L_(0x10, 0x02)
#define  REG_TC_SC_VOP_BK10_02_H       _PK_H_(0x10, 0x02)
#define  REG_TC_SC_VOP_BK10_03_L       _PK_L_(0x10, 0x03)
#define  REG_TC_SC_VOP_BK10_03_H       _PK_H_(0x10, 0x03)
#define  REG_TC_SC_VOP_BK10_04_L       _PK_L_(0x10, 0x04)
#define  REG_TC_SC_VOP_BK10_04_H       _PK_H_(0x10, 0x04)
#define  REG_TC_SC_VOP_BK10_05_L       _PK_L_(0x10, 0x05)
#define  REG_TC_SC_VOP_BK10_05_H       _PK_H_(0x10, 0x05)
#define  REG_TC_SC_VOP_BK10_06_L       _PK_L_(0x10, 0x06)
#define  REG_TC_SC_VOP_BK10_06_H       _PK_H_(0x10, 0x06)
#define  REG_TC_SC_VOP_BK10_07_L       _PK_L_(0x10, 0x07)
#define  REG_TC_SC_VOP_BK10_07_H       _PK_H_(0x10, 0x07)
#define  REG_TC_SC_VOP_BK10_08_L       _PK_L_(0x10, 0x08)
#define  REG_TC_SC_VOP_BK10_08_H       _PK_H_(0x10, 0x08)
#define  REG_TC_SC_VOP_BK10_09_L       _PK_L_(0x10, 0x09)
#define  REG_TC_SC_VOP_BK10_09_H       _PK_H_(0x10, 0x09)
#define  REG_TC_SC_VOP_BK10_0A_L       _PK_L_(0x10, 0x0A)
#define  REG_TC_SC_VOP_BK10_0A_H       _PK_H_(0x10, 0x0A)
#define  REG_TC_SC_VOP_BK10_0B_L       _PK_L_(0x10, 0x0B)
#define  REG_TC_SC_VOP_BK10_0B_H       _PK_H_(0x10, 0x0B)
#define  REG_TC_SC_VOP_BK10_0C_L       _PK_L_(0x10, 0x0C)
#define  REG_TC_SC_VOP_BK10_0C_H       _PK_H_(0x10, 0x0C)
#define  REG_TC_SC_VOP_BK10_0D_L       _PK_L_(0x10, 0x0D)
#define  REG_TC_SC_VOP_BK10_0D_H       _PK_H_(0x10, 0x0D)
#define  REG_TC_SC_VOP_BK10_0E_L       _PK_L_(0x10, 0x0E)
#define  REG_TC_SC_VOP_BK10_0E_H       _PK_H_(0x10, 0x0E)
#define  REG_TC_SC_VOP_BK10_0F_L       _PK_L_(0x10, 0x0F)
#define  REG_TC_SC_VOP_BK10_0F_H       _PK_H_(0x10, 0x0F)
#define  REG_TC_SC_VOP_BK10_10_L       _PK_L_(0x10, 0x10)
#define  REG_TC_SC_VOP_BK10_10_H       _PK_H_(0x10, 0x10)
#define  REG_TC_SC_VOP_BK10_11_L       _PK_L_(0x10, 0x11)
#define  REG_TC_SC_VOP_BK10_11_H       _PK_H_(0x10, 0x11)
#define  REG_TC_SC_VOP_BK10_12_L       _PK_L_(0x10, 0x12)
#define  REG_TC_SC_VOP_BK10_12_H       _PK_H_(0x10, 0x12)
#define  REG_TC_SC_VOP_BK10_13_L       _PK_L_(0x10, 0x13)
#define  REG_TC_SC_VOP_BK10_13_H       _PK_H_(0x10, 0x13)
#define  REG_TC_SC_VOP_BK10_14_L       _PK_L_(0x10, 0x14)
#define  REG_TC_SC_VOP_BK10_14_H       _PK_H_(0x10, 0x14)
#define  REG_TC_SC_VOP_BK10_15_L       _PK_L_(0x10, 0x15)
#define  REG_TC_SC_VOP_BK10_15_H       _PK_H_(0x10, 0x15)
#define  REG_TC_SC_VOP_BK10_16_L       _PK_L_(0x10, 0x16)
#define  REG_TC_SC_VOP_BK10_16_H       _PK_H_(0x10, 0x16)
#define  REG_TC_SC_VOP_BK10_17_L       _PK_L_(0x10, 0x17)
#define  REG_TC_SC_VOP_BK10_17_H       _PK_H_(0x10, 0x17)
#define  REG_TC_SC_VOP_BK10_18_L       _PK_L_(0x10, 0x18)
#define  REG_TC_SC_VOP_BK10_18_H       _PK_H_(0x10, 0x18)
#define  REG_TC_SC_VOP_BK10_19_L       _PK_L_(0x10, 0x19)
#define  REG_TC_SC_VOP_BK10_19_H       _PK_H_(0x10, 0x19)
#define  REG_TC_SC_VOP_BK10_1A_L       _PK_L_(0x10, 0x1A)
#define  REG_TC_SC_VOP_BK10_1A_H       _PK_H_(0x10, 0x1A)
#define  REG_TC_SC_VOP_BK10_1B_L       _PK_L_(0x10, 0x1B)
#define  REG_TC_SC_VOP_BK10_1B_H       _PK_H_(0x10, 0x1B)
#define  REG_TC_SC_VOP_BK10_1C_L       _PK_L_(0x10, 0x1C)
#define  REG_TC_SC_VOP_BK10_1C_H       _PK_H_(0x10, 0x1C)
#define  REG_TC_SC_VOP_BK10_1D_L       _PK_L_(0x10, 0x1D)
#define  REG_TC_SC_VOP_BK10_1D_H       _PK_H_(0x10, 0x1D)
#define  REG_TC_SC_VOP_BK10_1E_L       _PK_L_(0x10, 0x1E)
#define  REG_TC_SC_VOP_BK10_1E_H       _PK_H_(0x10, 0x1E)
#define  REG_TC_SC_VOP_BK10_1F_L       _PK_L_(0x10, 0x1F)
#define  REG_TC_SC_VOP_BK10_1F_H       _PK_H_(0x10, 0x1F)
#define  REG_TC_SC_VOP_BK10_20_L       _PK_L_(0x10, 0x20)
#define  REG_TC_SC_VOP_BK10_20_H       _PK_H_(0x10, 0x20)
#define  REG_TC_SC_VOP_BK10_21_L       _PK_L_(0x10, 0x21)
#define  REG_TC_SC_VOP_BK10_21_H       _PK_H_(0x10, 0x21)
#define  REG_TC_SC_VOP_BK10_22_L       _PK_L_(0x10, 0x22)
#define  REG_TC_SC_VOP_BK10_22_H       _PK_H_(0x10, 0x22)
#define  REG_TC_SC_VOP_BK10_23_L       _PK_L_(0x10, 0x23)
#define  REG_TC_SC_VOP_BK10_23_H       _PK_H_(0x10, 0x23)
#define  REG_TC_SC_VOP_BK10_24_L       _PK_L_(0x10, 0x24)
#define  REG_TC_SC_VOP_BK10_24_H       _PK_H_(0x10, 0x24)
#define  REG_TC_SC_VOP_BK10_25_L       _PK_L_(0x10, 0x25)
#define  REG_TC_SC_VOP_BK10_25_H       _PK_H_(0x10, 0x25)
#define  REG_TC_SC_VOP_BK10_26_L       _PK_L_(0x10, 0x26)
#define  REG_TC_SC_VOP_BK10_26_H       _PK_H_(0x10, 0x26)
#define  REG_TC_SC_VOP_BK10_27_L       _PK_L_(0x10, 0x27)
#define  REG_TC_SC_VOP_BK10_27_H       _PK_H_(0x10, 0x27)
#define  REG_TC_SC_VOP_BK10_28_L       _PK_L_(0x10, 0x28)
#define  REG_TC_SC_VOP_BK10_28_H       _PK_H_(0x10, 0x28)
#define  REG_TC_SC_VOP_BK10_29_L       _PK_L_(0x10, 0x29)
#define  REG_TC_SC_VOP_BK10_29_H       _PK_H_(0x10, 0x29)
#define  REG_TC_SC_VOP_BK10_2A_L       _PK_L_(0x10, 0x2A)
#define  REG_TC_SC_VOP_BK10_2A_H       _PK_H_(0x10, 0x2A)
#define  REG_TC_SC_VOP_BK10_2B_L       _PK_L_(0x10, 0x2B)
#define  REG_TC_SC_VOP_BK10_2B_H       _PK_H_(0x10, 0x2B)
#define  REG_TC_SC_VOP_BK10_2C_L       _PK_L_(0x10, 0x2C)
#define  REG_TC_SC_VOP_BK10_2C_H       _PK_H_(0x10, 0x2C)
#define  REG_TC_SC_VOP_BK10_2D_L       _PK_L_(0x10, 0x2D)
#define  REG_TC_SC_VOP_BK10_2D_H       _PK_H_(0x10, 0x2D)
#define  REG_TC_SC_VOP_BK10_2E_L       _PK_L_(0x10, 0x2E)
#define  REG_TC_SC_VOP_BK10_2E_H       _PK_H_(0x10, 0x2E)
#define  REG_TC_SC_VOP_BK10_2F_L       _PK_L_(0x10, 0x2F)
#define  REG_TC_SC_VOP_BK10_2F_H       _PK_H_(0x10, 0x2F)
#define  REG_TC_SC_VOP_BK10_30_L       _PK_L_(0x10, 0x30)
#define  REG_TC_SC_VOP_BK10_30_H       _PK_H_(0x10, 0x30)
#define  REG_TC_SC_VOP_BK10_31_L       _PK_L_(0x10, 0x31)
#define  REG_TC_SC_VOP_BK10_31_H       _PK_H_(0x10, 0x31)
#define  REG_TC_SC_VOP_BK10_32_L       _PK_L_(0x10, 0x32)
#define  REG_TC_SC_VOP_BK10_32_H       _PK_H_(0x10, 0x32)
#define  REG_TC_SC_VOP_BK10_33_L       _PK_L_(0x10, 0x33)
#define  REG_TC_SC_VOP_BK10_33_H       _PK_H_(0x10, 0x33)
#define  REG_TC_SC_VOP_BK10_34_L       _PK_L_(0x10, 0x34)
#define  REG_TC_SC_VOP_BK10_34_H       _PK_H_(0x10, 0x34)
#define  REG_TC_SC_VOP_BK10_35_L       _PK_L_(0x10, 0x35)
#define  REG_TC_SC_VOP_BK10_35_H       _PK_H_(0x10, 0x35)
#define  REG_TC_SC_VOP_BK10_36_L       _PK_L_(0x10, 0x36)
#define  REG_TC_SC_VOP_BK10_36_H       _PK_H_(0x10, 0x36)
#define  REG_TC_SC_VOP_BK10_37_L       _PK_L_(0x10, 0x37)
#define  REG_TC_SC_VOP_BK10_37_H       _PK_H_(0x10, 0x37)
#define  REG_TC_SC_VOP_BK10_38_L       _PK_L_(0x10, 0x38)
#define  REG_TC_SC_VOP_BK10_38_H       _PK_H_(0x10, 0x38)
#define  REG_TC_SC_VOP_BK10_39_L       _PK_L_(0x10, 0x39)
#define  REG_TC_SC_VOP_BK10_39_H       _PK_H_(0x10, 0x39)
#define  REG_TC_SC_VOP_BK10_3A_L       _PK_L_(0x10, 0x3A)
#define  REG_TC_SC_VOP_BK10_3A_H       _PK_H_(0x10, 0x3A)
#define  REG_TC_SC_VOP_BK10_3B_L       _PK_L_(0x10, 0x3B)
#define  REG_TC_SC_VOP_BK10_3B_H       _PK_H_(0x10, 0x3B)
#define  REG_TC_SC_VOP_BK10_3C_L       _PK_L_(0x10, 0x3C)
#define  REG_TC_SC_VOP_BK10_3C_H       _PK_H_(0x10, 0x3C)
#define  REG_TC_SC_VOP_BK10_3D_L       _PK_L_(0x10, 0x3D)
#define  REG_TC_SC_VOP_BK10_3D_H       _PK_H_(0x10, 0x3D)
#define  REG_TC_SC_VOP_BK10_3E_L       _PK_L_(0x10, 0x3E)
#define  REG_TC_SC_VOP_BK10_3E_H       _PK_H_(0x10, 0x3E)
#define  REG_TC_SC_VOP_BK10_3F_L       _PK_L_(0x10, 0x3F)
#define  REG_TC_SC_VOP_BK10_3F_H       _PK_H_(0x10, 0x3F)
#define  REG_TC_SC_VOP_BK10_40_L       _PK_L_(0x10, 0x40)
#define  REG_TC_SC_VOP_BK10_40_H       _PK_H_(0x10, 0x40)
#define  REG_TC_SC_VOP_BK10_41_L       _PK_L_(0x10, 0x41)
#define  REG_TC_SC_VOP_BK10_41_H       _PK_H_(0x10, 0x41)
#define  REG_TC_SC_VOP_BK10_42_L       _PK_L_(0x10, 0x42)
#define  REG_TC_SC_VOP_BK10_42_H       _PK_H_(0x10, 0x42)
#define  REG_TC_SC_VOP_BK10_43_L       _PK_L_(0x10, 0x43)
#define  REG_TC_SC_VOP_BK10_43_H       _PK_H_(0x10, 0x43)
#define  REG_TC_SC_VOP_BK10_44_L       _PK_L_(0x10, 0x44)
#define  REG_TC_SC_VOP_BK10_44_H       _PK_H_(0x10, 0x44)
#define  REG_TC_SC_VOP_BK10_45_L       _PK_L_(0x10, 0x45)
#define  REG_TC_SC_VOP_BK10_45_H       _PK_H_(0x10, 0x45)
#define  REG_TC_SC_VOP_BK10_46_L       _PK_L_(0x10, 0x46)
#define  REG_TC_SC_VOP_BK10_46_H       _PK_H_(0x10, 0x46)
#define  REG_TC_SC_VOP_BK10_47_L       _PK_L_(0x10, 0x47)
#define  REG_TC_SC_VOP_BK10_47_H       _PK_H_(0x10, 0x47)
#define  REG_TC_SC_VOP_BK10_48_L       _PK_L_(0x10, 0x48)
#define  REG_TC_SC_VOP_BK10_48_H       _PK_H_(0x10, 0x48)
#define  REG_TC_SC_VOP_BK10_49_L       _PK_L_(0x10, 0x49)
#define  REG_TC_SC_VOP_BK10_49_H       _PK_H_(0x10, 0x49)
#define  REG_TC_SC_VOP_BK10_4A_L       _PK_L_(0x10, 0x4A)
#define  REG_TC_SC_VOP_BK10_4A_H       _PK_H_(0x10, 0x4A)
#define  REG_TC_SC_VOP_BK10_4B_L       _PK_L_(0x10, 0x4B)
#define  REG_TC_SC_VOP_BK10_4B_H       _PK_H_(0x10, 0x4B)
#define  REG_TC_SC_VOP_BK10_4C_L       _PK_L_(0x10, 0x4C)
#define  REG_TC_SC_VOP_BK10_4C_H       _PK_H_(0x10, 0x4C)
#define  REG_TC_SC_VOP_BK10_4D_L       _PK_L_(0x10, 0x4D)
#define  REG_TC_SC_VOP_BK10_4D_H       _PK_H_(0x10, 0x4D)
#define  REG_TC_SC_VOP_BK10_4E_L       _PK_L_(0x10, 0x4E)
#define  REG_TC_SC_VOP_BK10_4E_H       _PK_H_(0x10, 0x4E)
#define  REG_TC_SC_VOP_BK10_4F_L       _PK_L_(0x10, 0x4F)
#define  REG_TC_SC_VOP_BK10_4F_H       _PK_H_(0x10, 0x4F)
#define  REG_TC_SC_VOP_BK10_50_L       _PK_L_(0x10, 0x50)
#define  REG_TC_SC_VOP_BK10_50_H       _PK_H_(0x10, 0x50)
#define  REG_TC_SC_VOP_BK10_51_L       _PK_L_(0x10, 0x51)
#define  REG_TC_SC_VOP_BK10_51_H       _PK_H_(0x10, 0x51)
#define  REG_TC_SC_VOP_BK10_52_L       _PK_L_(0x10, 0x52)
#define  REG_TC_SC_VOP_BK10_52_H       _PK_H_(0x10, 0x52)
#define  REG_TC_SC_VOP_BK10_53_L       _PK_L_(0x10, 0x53)
#define  REG_TC_SC_VOP_BK10_53_H       _PK_H_(0x10, 0x53)
#define  REG_TC_SC_VOP_BK10_54_L       _PK_L_(0x10, 0x54)
#define  REG_TC_SC_VOP_BK10_54_H       _PK_H_(0x10, 0x54)
#define  REG_TC_SC_VOP_BK10_55_L       _PK_L_(0x10, 0x55)
#define  REG_TC_SC_VOP_BK10_55_H       _PK_H_(0x10, 0x55)
#define  REG_TC_SC_VOP_BK10_56_L       _PK_L_(0x10, 0x56)
#define  REG_TC_SC_VOP_BK10_56_H       _PK_H_(0x10, 0x56)
#define  REG_TC_SC_VOP_BK10_57_L       _PK_L_(0x10, 0x57)
#define  REG_TC_SC_VOP_BK10_57_H       _PK_H_(0x10, 0x57)
#define  REG_TC_SC_VOP_BK10_58_L       _PK_L_(0x10, 0x58)
#define  REG_TC_SC_VOP_BK10_58_H       _PK_H_(0x10, 0x58)
#define  REG_TC_SC_VOP_BK10_59_L       _PK_L_(0x10, 0x59)
#define  REG_TC_SC_VOP_BK10_59_H       _PK_H_(0x10, 0x59)
#define  REG_TC_SC_VOP_BK10_5A_L       _PK_L_(0x10, 0x5A)
#define  REG_TC_SC_VOP_BK10_5A_H       _PK_H_(0x10, 0x5A)
#define  REG_TC_SC_VOP_BK10_5B_L       _PK_L_(0x10, 0x5B)
#define  REG_TC_SC_VOP_BK10_5B_H       _PK_H_(0x10, 0x5B)
#define  REG_TC_SC_VOP_BK10_5C_L       _PK_L_(0x10, 0x5C)
#define  REG_TC_SC_VOP_BK10_5C_H       _PK_H_(0x10, 0x5C)
#define  REG_TC_SC_VOP_BK10_5D_L       _PK_L_(0x10, 0x5D)
#define  REG_TC_SC_VOP_BK10_5D_H       _PK_H_(0x10, 0x5D)
#define  REG_TC_SC_VOP_BK10_5E_L       _PK_L_(0x10, 0x5E)
#define  REG_TC_SC_VOP_BK10_5E_H       _PK_H_(0x10, 0x5E)
#define  REG_TC_SC_VOP_BK10_5F_L       _PK_L_(0x10, 0x5F)
#define  REG_TC_SC_VOP_BK10_5F_H       _PK_H_(0x10, 0x5F)
#define  REG_TC_SC_VOP_BK10_60_L       _PK_L_(0x10, 0x60)
#define  REG_TC_SC_VOP_BK10_60_H       _PK_H_(0x10, 0x60)
#define  REG_TC_SC_VOP_BK10_61_L       _PK_L_(0x10, 0x61)
#define  REG_TC_SC_VOP_BK10_61_H       _PK_H_(0x10, 0x61)
#define  REG_TC_SC_VOP_BK10_62_L       _PK_L_(0x10, 0x62)
#define  REG_TC_SC_VOP_BK10_62_H       _PK_H_(0x10, 0x62)
#define  REG_TC_SC_VOP_BK10_63_L       _PK_L_(0x10, 0x63)
#define  REG_TC_SC_VOP_BK10_63_H       _PK_H_(0x10, 0x63)
#define  REG_TC_SC_VOP_BK10_64_L       _PK_L_(0x10, 0x64)
#define  REG_TC_SC_VOP_BK10_64_H       _PK_H_(0x10, 0x64)
#define  REG_TC_SC_VOP_BK10_65_L       _PK_L_(0x10, 0x65)
#define  REG_TC_SC_VOP_BK10_65_H       _PK_H_(0x10, 0x65)
#define  REG_TC_SC_VOP_BK10_66_L       _PK_L_(0x10, 0x66)
#define  REG_TC_SC_VOP_BK10_66_H       _PK_H_(0x10, 0x66)
#define  REG_TC_SC_VOP_BK10_67_L       _PK_L_(0x10, 0x67)
#define  REG_TC_SC_VOP_BK10_67_H       _PK_H_(0x10, 0x67)
#define  REG_TC_SC_VOP_BK10_68_L       _PK_L_(0x10, 0x68)
#define  REG_TC_SC_VOP_BK10_68_H       _PK_H_(0x10, 0x68)
#define  REG_TC_SC_VOP_BK10_69_L       _PK_L_(0x10, 0x69)
#define  REG_TC_SC_VOP_BK10_69_H       _PK_H_(0x10, 0x69)
#define  REG_TC_SC_VOP_BK10_6A_L       _PK_L_(0x10, 0x6A)
#define  REG_TC_SC_VOP_BK10_6A_H       _PK_H_(0x10, 0x6A)
#define  REG_TC_SC_VOP_BK10_6B_L       _PK_L_(0x10, 0x6B)
#define  REG_TC_SC_VOP_BK10_6B_H       _PK_H_(0x10, 0x6B)
#define  REG_TC_SC_VOP_BK10_6C_L       _PK_L_(0x10, 0x6C)
#define  REG_TC_SC_VOP_BK10_6C_H       _PK_H_(0x10, 0x6C)
#define  REG_TC_SC_VOP_BK10_6D_L       _PK_L_(0x10, 0x6D)
#define  REG_TC_SC_VOP_BK10_6D_H       _PK_H_(0x10, 0x6D)
#define  REG_TC_SC_VOP_BK10_6E_L       _PK_L_(0x10, 0x6E)
#define  REG_TC_SC_VOP_BK10_6E_H       _PK_H_(0x10, 0x6E)
#define  REG_TC_SC_VOP_BK10_6F_L       _PK_L_(0x10, 0x6F)
#define  REG_TC_SC_VOP_BK10_6F_H       _PK_H_(0x10, 0x6F)
#define  REG_TC_SC_VOP_BK10_70_L       _PK_L_(0x10, 0x70)
#define  REG_TC_SC_VOP_BK10_70_H       _PK_H_(0x10, 0x70)
#define  REG_TC_SC_VOP_BK10_71_L       _PK_L_(0x10, 0x71)
#define  REG_TC_SC_VOP_BK10_71_H       _PK_H_(0x10, 0x71)
#define  REG_TC_SC_VOP_BK10_72_L       _PK_L_(0x10, 0x72)
#define  REG_TC_SC_VOP_BK10_72_H       _PK_H_(0x10, 0x72)
#define  REG_TC_SC_VOP_BK10_73_L       _PK_L_(0x10, 0x73)
#define  REG_TC_SC_VOP_BK10_73_H       _PK_H_(0x10, 0x73)
#define  REG_TC_SC_VOP_BK10_74_L       _PK_L_(0x10, 0x74)
#define  REG_TC_SC_VOP_BK10_74_H       _PK_H_(0x10, 0x74)
#define  REG_TC_SC_VOP_BK10_75_L       _PK_L_(0x10, 0x75)
#define  REG_TC_SC_VOP_BK10_75_H       _PK_H_(0x10, 0x75)
#define  REG_TC_SC_VOP_BK10_76_L       _PK_L_(0x10, 0x76)
#define  REG_TC_SC_VOP_BK10_76_H       _PK_H_(0x10, 0x76)
#define  REG_TC_SC_VOP_BK10_77_L       _PK_L_(0x10, 0x77)
#define  REG_TC_SC_VOP_BK10_77_H       _PK_H_(0x10, 0x77)
#define  REG_TC_SC_VOP_BK10_78_L       _PK_L_(0x10, 0x78)
#define  REG_TC_SC_VOP_BK10_78_H       _PK_H_(0x10, 0x78)
#define  REG_TC_SC_VOP_BK10_79_L       _PK_L_(0x10, 0x79)
#define  REG_TC_SC_VOP_BK10_79_H       _PK_H_(0x10, 0x79)
#define  REG_TC_SC_VOP_BK10_7A_L       _PK_L_(0x10, 0x7A)
#define  REG_TC_SC_VOP_BK10_7A_H       _PK_H_(0x10, 0x7A)
#define  REG_TC_SC_VOP_BK10_7B_L       _PK_L_(0x10, 0x7B)
#define  REG_TC_SC_VOP_BK10_7B_H       _PK_H_(0x10, 0x7B)
#define  REG_TC_SC_VOP_BK10_7C_L       _PK_L_(0x10, 0x7C)
#define  REG_TC_SC_VOP_BK10_7C_H       _PK_H_(0x10, 0x7C)
#define  REG_TC_SC_VOP_BK10_7D_L       _PK_L_(0x10, 0x7D)
#define  REG_TC_SC_VOP_BK10_7D_H       _PK_H_(0x10, 0x7D)
#define  REG_TC_SC_VOP_BK10_7E_L       _PK_L_(0x10, 0x7E)
#define  REG_TC_SC_VOP_BK10_7E_H       _PK_H_(0x10, 0x7E)
#define  REG_TC_SC_VOP_BK10_7F_L       _PK_L_(0x10, 0x7F)
#define  REG_TC_SC_VOP_BK10_7F_H       _PK_H_(0x10, 0x7F)

#define  REG_TC_SC_OP1_BK20_00_L       _PK_L_(0x20, 0x00)
#define  REG_TC_SC_OP1_BK20_00_H       _PK_H_(0x20, 0x00)
#define  REG_TC_SC_OP1_BK20_01_L       _PK_L_(0x20, 0x01)
#define  REG_TC_SC_OP1_BK20_01_H       _PK_H_(0x20, 0x01)
#define  REG_TC_SC_OP1_BK20_02_L       _PK_L_(0x20, 0x02)
#define  REG_TC_SC_OP1_BK20_02_H       _PK_H_(0x20, 0x02)
#define  REG_TC_SC_OP1_BK20_03_L       _PK_L_(0x20, 0x03)
#define  REG_TC_SC_OP1_BK20_03_H       _PK_H_(0x20, 0x03)
#define  REG_TC_SC_OP1_BK20_04_L       _PK_L_(0x20, 0x04)
#define  REG_TC_SC_OP1_BK20_04_H       _PK_H_(0x20, 0x04)
#define  REG_TC_SC_OP1_BK20_05_L       _PK_L_(0x20, 0x05)
#define  REG_TC_SC_OP1_BK20_05_H       _PK_H_(0x20, 0x05)
#define  REG_TC_SC_OP1_BK20_06_L       _PK_L_(0x20, 0x06)
#define  REG_TC_SC_OP1_BK20_06_H       _PK_H_(0x20, 0x06)
#define  REG_TC_SC_OP1_BK20_07_L       _PK_L_(0x20, 0x07)
#define  REG_TC_SC_OP1_BK20_07_H       _PK_H_(0x20, 0x07)
#define  REG_TC_SC_OP1_BK20_08_L       _PK_L_(0x20, 0x08)
#define  REG_TC_SC_OP1_BK20_08_H       _PK_H_(0x20, 0x08)
#define  REG_TC_SC_OP1_BK20_09_L       _PK_L_(0x20, 0x09)
#define  REG_TC_SC_OP1_BK20_09_H       _PK_H_(0x20, 0x09)
#define  REG_TC_SC_OP1_BK20_0A_L       _PK_L_(0x20, 0x0A)
#define  REG_TC_SC_OP1_BK20_0A_H       _PK_H_(0x20, 0x0A)
#define  REG_TC_SC_OP1_BK20_0B_L       _PK_L_(0x20, 0x0B)
#define  REG_TC_SC_OP1_BK20_0B_H       _PK_H_(0x20, 0x0B)
#define  REG_TC_SC_OP1_BK20_0C_L       _PK_L_(0x20, 0x0C)
#define  REG_TC_SC_OP1_BK20_0C_H       _PK_H_(0x20, 0x0C)
#define  REG_TC_SC_OP1_BK20_0D_L       _PK_L_(0x20, 0x0D)
#define  REG_TC_SC_OP1_BK20_0D_H       _PK_H_(0x20, 0x0D)
#define  REG_TC_SC_OP1_BK20_0E_L       _PK_L_(0x20, 0x0E)
#define  REG_TC_SC_OP1_BK20_0E_H       _PK_H_(0x20, 0x0E)
#define  REG_TC_SC_OP1_BK20_0F_L       _PK_L_(0x20, 0x0F)
#define  REG_TC_SC_OP1_BK20_0F_H       _PK_H_(0x20, 0x0F)
#define  REG_TC_SC_OP1_BK20_10_L       _PK_L_(0x20, 0x10)
#define  REG_TC_SC_OP1_BK20_10_H       _PK_H_(0x20, 0x10)
#define  REG_TC_SC_OP1_BK20_11_L       _PK_L_(0x20, 0x11)
#define  REG_TC_SC_OP1_BK20_11_H       _PK_H_(0x20, 0x11)
#define  REG_TC_SC_OP1_BK20_12_L       _PK_L_(0x20, 0x12)
#define  REG_TC_SC_OP1_BK20_12_H       _PK_H_(0x20, 0x12)
#define  REG_TC_SC_OP1_BK20_13_L       _PK_L_(0x20, 0x13)
#define  REG_TC_SC_OP1_BK20_13_H       _PK_H_(0x20, 0x13)
#define  REG_TC_SC_OP1_BK20_14_L       _PK_L_(0x20, 0x14)
#define  REG_TC_SC_OP1_BK20_14_H       _PK_H_(0x20, 0x14)
#define  REG_TC_SC_OP1_BK20_15_L       _PK_L_(0x20, 0x15)
#define  REG_TC_SC_OP1_BK20_15_H       _PK_H_(0x20, 0x15)
#define  REG_TC_SC_OP1_BK20_16_L       _PK_L_(0x20, 0x16)
#define  REG_TC_SC_OP1_BK20_16_H       _PK_H_(0x20, 0x16)
#define  REG_TC_SC_OP1_BK20_17_L       _PK_L_(0x20, 0x17)
#define  REG_TC_SC_OP1_BK20_17_H       _PK_H_(0x20, 0x17)
#define  REG_TC_SC_OP1_BK20_18_L       _PK_L_(0x20, 0x18)
#define  REG_TC_SC_OP1_BK20_18_H       _PK_H_(0x20, 0x18)
#define  REG_TC_SC_OP1_BK20_19_L       _PK_L_(0x20, 0x19)
#define  REG_TC_SC_OP1_BK20_19_H       _PK_H_(0x20, 0x19)
#define  REG_TC_SC_OP1_BK20_1A_L       _PK_L_(0x20, 0x1A)
#define  REG_TC_SC_OP1_BK20_1A_H       _PK_H_(0x20, 0x1A)
#define  REG_TC_SC_OP1_BK20_1B_L       _PK_L_(0x20, 0x1B)
#define  REG_TC_SC_OP1_BK20_1B_H       _PK_H_(0x20, 0x1B)
#define  REG_TC_SC_OP1_BK20_1C_L       _PK_L_(0x20, 0x1C)
#define  REG_TC_SC_OP1_BK20_1C_H       _PK_H_(0x20, 0x1C)
#define  REG_TC_SC_OP1_BK20_1D_L       _PK_L_(0x20, 0x1D)
#define  REG_TC_SC_OP1_BK20_1D_H       _PK_H_(0x20, 0x1D)
#define  REG_TC_SC_OP1_BK20_1E_L       _PK_L_(0x20, 0x1E)
#define  REG_TC_SC_OP1_BK20_1E_H       _PK_H_(0x20, 0x1E)
#define  REG_TC_SC_OP1_BK20_1F_L       _PK_L_(0x20, 0x1F)
#define  REG_TC_SC_OP1_BK20_1F_H       _PK_H_(0x20, 0x1F)
#define  REG_TC_SC_OP1_BK20_20_L       _PK_L_(0x20, 0x20)
#define  REG_TC_SC_OP1_BK20_20_H       _PK_H_(0x20, 0x20)
#define  REG_TC_SC_OP1_BK20_21_L       _PK_L_(0x20, 0x21)
#define  REG_TC_SC_OP1_BK20_21_H       _PK_H_(0x20, 0x21)
#define  REG_TC_SC_OP1_BK20_22_L       _PK_L_(0x20, 0x22)
#define  REG_TC_SC_OP1_BK20_22_H       _PK_H_(0x20, 0x22)
#define  REG_TC_SC_OP1_BK20_23_L       _PK_L_(0x20, 0x23)
#define  REG_TC_SC_OP1_BK20_23_H       _PK_H_(0x20, 0x23)
#define  REG_TC_SC_OP1_BK20_24_L       _PK_L_(0x20, 0x24)
#define  REG_TC_SC_OP1_BK20_24_H       _PK_H_(0x20, 0x24)
#define  REG_TC_SC_OP1_BK20_25_L       _PK_L_(0x20, 0x25)
#define  REG_TC_SC_OP1_BK20_25_H       _PK_H_(0x20, 0x25)
#define  REG_TC_SC_OP1_BK20_26_L       _PK_L_(0x20, 0x26)
#define  REG_TC_SC_OP1_BK20_26_H       _PK_H_(0x20, 0x26)
#define  REG_TC_SC_OP1_BK20_27_L       _PK_L_(0x20, 0x27)
#define  REG_TC_SC_OP1_BK20_27_H       _PK_H_(0x20, 0x27)
#define  REG_TC_SC_OP1_BK20_28_L       _PK_L_(0x20, 0x28)
#define  REG_TC_SC_OP1_BK20_28_H       _PK_H_(0x20, 0x28)
#define  REG_TC_SC_OP1_BK20_29_L       _PK_L_(0x20, 0x29)
#define  REG_TC_SC_OP1_BK20_29_H       _PK_H_(0x20, 0x29)
#define  REG_TC_SC_OP1_BK20_2A_L       _PK_L_(0x20, 0x2A)
#define  REG_TC_SC_OP1_BK20_2A_H       _PK_H_(0x20, 0x2A)
#define  REG_TC_SC_OP1_BK20_2B_L       _PK_L_(0x20, 0x2B)
#define  REG_TC_SC_OP1_BK20_2B_H       _PK_H_(0x20, 0x2B)
#define  REG_TC_SC_OP1_BK20_2C_L       _PK_L_(0x20, 0x2C)
#define  REG_TC_SC_OP1_BK20_2C_H       _PK_H_(0x20, 0x2C)
#define  REG_TC_SC_OP1_BK20_2D_L       _PK_L_(0x20, 0x2D)
#define  REG_TC_SC_OP1_BK20_2D_H       _PK_H_(0x20, 0x2D)
#define  REG_TC_SC_OP1_BK20_2E_L       _PK_L_(0x20, 0x2E)
#define  REG_TC_SC_OP1_BK20_2E_H       _PK_H_(0x20, 0x2E)
#define  REG_TC_SC_OP1_BK20_2F_L       _PK_L_(0x20, 0x2F)
#define  REG_TC_SC_OP1_BK20_2F_H       _PK_H_(0x20, 0x2F)
#define  REG_TC_SC_OP1_BK20_30_L       _PK_L_(0x20, 0x30)
#define  REG_TC_SC_OP1_BK20_30_H       _PK_H_(0x20, 0x30)
#define  REG_TC_SC_OP1_BK20_31_L       _PK_L_(0x20, 0x31)
#define  REG_TC_SC_OP1_BK20_31_H       _PK_H_(0x20, 0x31)
#define  REG_TC_SC_OP1_BK20_32_L       _PK_L_(0x20, 0x32)
#define  REG_TC_SC_OP1_BK20_32_H       _PK_H_(0x20, 0x32)
#define  REG_TC_SC_OP1_BK20_33_L       _PK_L_(0x20, 0x33)
#define  REG_TC_SC_OP1_BK20_33_H       _PK_H_(0x20, 0x33)
#define  REG_TC_SC_OP1_BK20_34_L       _PK_L_(0x20, 0x34)
#define  REG_TC_SC_OP1_BK20_34_H       _PK_H_(0x20, 0x34)
#define  REG_TC_SC_OP1_BK20_35_L       _PK_L_(0x20, 0x35)
#define  REG_TC_SC_OP1_BK20_35_H       _PK_H_(0x20, 0x35)
#define  REG_TC_SC_OP1_BK20_36_L       _PK_L_(0x20, 0x36)
#define  REG_TC_SC_OP1_BK20_36_H       _PK_H_(0x20, 0x36)
#define  REG_TC_SC_OP1_BK20_37_L       _PK_L_(0x20, 0x37)
#define  REG_TC_SC_OP1_BK20_37_H       _PK_H_(0x20, 0x37)
#define  REG_TC_SC_OP1_BK20_38_L       _PK_L_(0x20, 0x38)
#define  REG_TC_SC_OP1_BK20_38_H       _PK_H_(0x20, 0x38)
#define  REG_TC_SC_OP1_BK20_39_L       _PK_L_(0x20, 0x39)
#define  REG_TC_SC_OP1_BK20_39_H       _PK_H_(0x20, 0x39)
#define  REG_TC_SC_OP1_BK20_3A_L       _PK_L_(0x20, 0x3A)
#define  REG_TC_SC_OP1_BK20_3A_H       _PK_H_(0x20, 0x3A)
#define  REG_TC_SC_OP1_BK20_3B_L       _PK_L_(0x20, 0x3B)
#define  REG_TC_SC_OP1_BK20_3B_H       _PK_H_(0x20, 0x3B)
#define  REG_TC_SC_OP1_BK20_3C_L       _PK_L_(0x20, 0x3C)
#define  REG_TC_SC_OP1_BK20_3C_H       _PK_H_(0x20, 0x3C)
#define  REG_TC_SC_OP1_BK20_3D_L       _PK_L_(0x20, 0x3D)
#define  REG_TC_SC_OP1_BK20_3D_H       _PK_H_(0x20, 0x3D)
#define  REG_TC_SC_OP1_BK20_3E_L       _PK_L_(0x20, 0x3E)
#define  REG_TC_SC_OP1_BK20_3E_H       _PK_H_(0x20, 0x3E)
#define  REG_TC_SC_OP1_BK20_3F_L       _PK_L_(0x20, 0x3F)
#define  REG_TC_SC_OP1_BK20_3F_H       _PK_H_(0x20, 0x3F)
#define  REG_TC_SC_OP1_BK20_40_L       _PK_L_(0x20, 0x40)
#define  REG_TC_SC_OP1_BK20_40_H       _PK_H_(0x20, 0x40)
#define  REG_TC_SC_OP1_BK20_41_L       _PK_L_(0x20, 0x41)
#define  REG_TC_SC_OP1_BK20_41_H       _PK_H_(0x20, 0x41)
#define  REG_TC_SC_OP1_BK20_42_L       _PK_L_(0x20, 0x42)
#define  REG_TC_SC_OP1_BK20_42_H       _PK_H_(0x20, 0x42)
#define  REG_TC_SC_OP1_BK20_43_L       _PK_L_(0x20, 0x43)
#define  REG_TC_SC_OP1_BK20_43_H       _PK_H_(0x20, 0x43)
#define  REG_TC_SC_OP1_BK20_44_L       _PK_L_(0x20, 0x44)
#define  REG_TC_SC_OP1_BK20_44_H       _PK_H_(0x20, 0x44)
#define  REG_TC_SC_OP1_BK20_45_L       _PK_L_(0x20, 0x45)
#define  REG_TC_SC_OP1_BK20_45_H       _PK_H_(0x20, 0x45)
#define  REG_TC_SC_OP1_BK20_46_L       _PK_L_(0x20, 0x46)
#define  REG_TC_SC_OP1_BK20_46_H       _PK_H_(0x20, 0x46)
#define  REG_TC_SC_OP1_BK20_47_L       _PK_L_(0x20, 0x47)
#define  REG_TC_SC_OP1_BK20_47_H       _PK_H_(0x20, 0x47)
#define  REG_TC_SC_OP1_BK20_48_L       _PK_L_(0x20, 0x48)
#define  REG_TC_SC_OP1_BK20_48_H       _PK_H_(0x20, 0x48)
#define  REG_TC_SC_OP1_BK20_49_L       _PK_L_(0x20, 0x49)
#define  REG_TC_SC_OP1_BK20_49_H       _PK_H_(0x20, 0x49)
#define  REG_TC_SC_OP1_BK20_4A_L       _PK_L_(0x20, 0x4A)
#define  REG_TC_SC_OP1_BK20_4A_H       _PK_H_(0x20, 0x4A)
#define  REG_TC_SC_OP1_BK20_4B_L       _PK_L_(0x20, 0x4B)
#define  REG_TC_SC_OP1_BK20_4B_H       _PK_H_(0x20, 0x4B)
#define  REG_TC_SC_OP1_BK20_4C_L       _PK_L_(0x20, 0x4C)
#define  REG_TC_SC_OP1_BK20_4C_H       _PK_H_(0x20, 0x4C)
#define  REG_TC_SC_OP1_BK20_4D_L       _PK_L_(0x20, 0x4D)
#define  REG_TC_SC_OP1_BK20_4D_H       _PK_H_(0x20, 0x4D)
#define  REG_TC_SC_OP1_BK20_4E_L       _PK_L_(0x20, 0x4E)
#define  REG_TC_SC_OP1_BK20_4E_H       _PK_H_(0x20, 0x4E)
#define  REG_TC_SC_OP1_BK20_4F_L       _PK_L_(0x20, 0x4F)
#define  REG_TC_SC_OP1_BK20_4F_H       _PK_H_(0x20, 0x4F)
#define  REG_TC_SC_OP1_BK20_50_L       _PK_L_(0x20, 0x50)
#define  REG_TC_SC_OP1_BK20_50_H       _PK_H_(0x20, 0x50)
#define  REG_TC_SC_OP1_BK20_51_L       _PK_L_(0x20, 0x51)
#define  REG_TC_SC_OP1_BK20_51_H       _PK_H_(0x20, 0x51)
#define  REG_TC_SC_OP1_BK20_52_L       _PK_L_(0x20, 0x52)
#define  REG_TC_SC_OP1_BK20_52_H       _PK_H_(0x20, 0x52)
#define  REG_TC_SC_OP1_BK20_53_L       _PK_L_(0x20, 0x53)
#define  REG_TC_SC_OP1_BK20_53_H       _PK_H_(0x20, 0x53)
#define  REG_TC_SC_OP1_BK20_54_L       _PK_L_(0x20, 0x54)
#define  REG_TC_SC_OP1_BK20_54_H       _PK_H_(0x20, 0x54)
#define  REG_TC_SC_OP1_BK20_55_L       _PK_L_(0x20, 0x55)
#define  REG_TC_SC_OP1_BK20_55_H       _PK_H_(0x20, 0x55)
#define  REG_TC_SC_OP1_BK20_56_L       _PK_L_(0x20, 0x56)
#define  REG_TC_SC_OP1_BK20_56_H       _PK_H_(0x20, 0x56)
#define  REG_TC_SC_OP1_BK20_57_L       _PK_L_(0x20, 0x57)
#define  REG_TC_SC_OP1_BK20_57_H       _PK_H_(0x20, 0x57)
#define  REG_TC_SC_OP1_BK20_58_L       _PK_L_(0x20, 0x58)
#define  REG_TC_SC_OP1_BK20_58_H       _PK_H_(0x20, 0x58)
#define  REG_TC_SC_OP1_BK20_59_L       _PK_L_(0x20, 0x59)
#define  REG_TC_SC_OP1_BK20_59_H       _PK_H_(0x20, 0x59)
#define  REG_TC_SC_OP1_BK20_5A_L       _PK_L_(0x20, 0x5A)
#define  REG_TC_SC_OP1_BK20_5A_H       _PK_H_(0x20, 0x5A)
#define  REG_TC_SC_OP1_BK20_5B_L       _PK_L_(0x20, 0x5B)
#define  REG_TC_SC_OP1_BK20_5B_H       _PK_H_(0x20, 0x5B)
#define  REG_TC_SC_OP1_BK20_5C_L       _PK_L_(0x20, 0x5C)
#define  REG_TC_SC_OP1_BK20_5C_H       _PK_H_(0x20, 0x5C)
#define  REG_TC_SC_OP1_BK20_5D_L       _PK_L_(0x20, 0x5D)
#define  REG_TC_SC_OP1_BK20_5D_H       _PK_H_(0x20, 0x5D)
#define  REG_TC_SC_OP1_BK20_5E_L       _PK_L_(0x20, 0x5E)
#define  REG_TC_SC_OP1_BK20_5E_H       _PK_H_(0x20, 0x5E)
#define  REG_TC_SC_OP1_BK20_5F_L       _PK_L_(0x20, 0x5F)
#define  REG_TC_SC_OP1_BK20_5F_H       _PK_H_(0x20, 0x5F)
#define  REG_TC_SC_OP1_BK20_60_L       _PK_L_(0x20, 0x60)
#define  REG_TC_SC_OP1_BK20_60_H       _PK_H_(0x20, 0x60)
#define  REG_TC_SC_OP1_BK20_61_L       _PK_L_(0x20, 0x61)
#define  REG_TC_SC_OP1_BK20_61_H       _PK_H_(0x20, 0x61)
#define  REG_TC_SC_OP1_BK20_62_L       _PK_L_(0x20, 0x62)
#define  REG_TC_SC_OP1_BK20_62_H       _PK_H_(0x20, 0x62)
#define  REG_TC_SC_OP1_BK20_63_L       _PK_L_(0x20, 0x63)
#define  REG_TC_SC_OP1_BK20_63_H       _PK_H_(0x20, 0x63)
#define  REG_TC_SC_OP1_BK20_64_L       _PK_L_(0x20, 0x64)
#define  REG_TC_SC_OP1_BK20_64_H       _PK_H_(0x20, 0x64)
#define  REG_TC_SC_OP1_BK20_65_L       _PK_L_(0x20, 0x65)
#define  REG_TC_SC_OP1_BK20_65_H       _PK_H_(0x20, 0x65)
#define  REG_TC_SC_OP1_BK20_66_L       _PK_L_(0x20, 0x66)
#define  REG_TC_SC_OP1_BK20_66_H       _PK_H_(0x20, 0x66)
#define  REG_TC_SC_OP1_BK20_67_L       _PK_L_(0x20, 0x67)
#define  REG_TC_SC_OP1_BK20_67_H       _PK_H_(0x20, 0x67)
#define  REG_TC_SC_OP1_BK20_68_L       _PK_L_(0x20, 0x68)
#define  REG_TC_SC_OP1_BK20_68_H       _PK_H_(0x20, 0x68)
#define  REG_TC_SC_OP1_BK20_69_L       _PK_L_(0x20, 0x69)
#define  REG_TC_SC_OP1_BK20_69_H       _PK_H_(0x20, 0x69)
#define  REG_TC_SC_OP1_BK20_6A_L       _PK_L_(0x20, 0x6A)
#define  REG_TC_SC_OP1_BK20_6A_H       _PK_H_(0x20, 0x6A)
#define  REG_TC_SC_OP1_BK20_6B_L       _PK_L_(0x20, 0x6B)
#define  REG_TC_SC_OP1_BK20_6B_H       _PK_H_(0x20, 0x6B)
#define  REG_TC_SC_OP1_BK20_6C_L       _PK_L_(0x20, 0x6C)
#define  REG_TC_SC_OP1_BK20_6C_H       _PK_H_(0x20, 0x6C)
#define  REG_TC_SC_OP1_BK20_6D_L       _PK_L_(0x20, 0x6D)
#define  REG_TC_SC_OP1_BK20_6D_H       _PK_H_(0x20, 0x6D)
#define  REG_TC_SC_OP1_BK20_6E_L       _PK_L_(0x20, 0x6E)
#define  REG_TC_SC_OP1_BK20_6E_H       _PK_H_(0x20, 0x6E)
#define  REG_TC_SC_OP1_BK20_6F_L       _PK_L_(0x20, 0x6F)
#define  REG_TC_SC_OP1_BK20_6F_H       _PK_H_(0x20, 0x6F)
#define  REG_TC_SC_OP1_BK20_70_L       _PK_L_(0x20, 0x70)
#define  REG_TC_SC_OP1_BK20_70_H       _PK_H_(0x20, 0x70)
#define  REG_TC_SC_OP1_BK20_71_L       _PK_L_(0x20, 0x71)
#define  REG_TC_SC_OP1_BK20_71_H       _PK_H_(0x20, 0x71)
#define  REG_TC_SC_OP1_BK20_72_L       _PK_L_(0x20, 0x72)
#define  REG_TC_SC_OP1_BK20_72_H       _PK_H_(0x20, 0x72)
#define  REG_TC_SC_OP1_BK20_73_L       _PK_L_(0x20, 0x73)
#define  REG_TC_SC_OP1_BK20_73_H       _PK_H_(0x20, 0x73)
#define  REG_TC_SC_OP1_BK20_74_L       _PK_L_(0x20, 0x74)
#define  REG_TC_SC_OP1_BK20_74_H       _PK_H_(0x20, 0x74)
#define  REG_TC_SC_OP1_BK20_75_L       _PK_L_(0x20, 0x75)
#define  REG_TC_SC_OP1_BK20_75_H       _PK_H_(0x20, 0x75)
#define  REG_TC_SC_OP1_BK20_76_L       _PK_L_(0x20, 0x76)
#define  REG_TC_SC_OP1_BK20_76_H       _PK_H_(0x20, 0x76)
#define  REG_TC_SC_OP1_BK20_77_L       _PK_L_(0x20, 0x77)
#define  REG_TC_SC_OP1_BK20_77_H       _PK_H_(0x20, 0x77)
#define  REG_TC_SC_OP1_BK20_78_L       _PK_L_(0x20, 0x78)
#define  REG_TC_SC_OP1_BK20_78_H       _PK_H_(0x20, 0x78)
#define  REG_TC_SC_OP1_BK20_79_L       _PK_L_(0x20, 0x79)
#define  REG_TC_SC_OP1_BK20_79_H       _PK_H_(0x20, 0x79)
#define  REG_TC_SC_OP1_BK20_7A_L       _PK_L_(0x20, 0x7A)
#define  REG_TC_SC_OP1_BK20_7A_H       _PK_H_(0x20, 0x7A)
#define  REG_TC_SC_OP1_BK20_7B_L       _PK_L_(0x20, 0x7B)
#define  REG_TC_SC_OP1_BK20_7B_H       _PK_H_(0x20, 0x7B)
#define  REG_TC_SC_OP1_BK20_7C_L       _PK_L_(0x20, 0x7C)
#define  REG_TC_SC_OP1_BK20_7C_H       _PK_H_(0x20, 0x7C)
#define  REG_TC_SC_OP1_BK20_7D_L       _PK_L_(0x20, 0x7D)
#define  REG_TC_SC_OP1_BK20_7D_H       _PK_H_(0x20, 0x7D)
#define  REG_TC_SC_OP1_BK20_7E_L       _PK_L_(0x20, 0x7E)
#define  REG_TC_SC_OP1_BK20_7E_H       _PK_H_(0x20, 0x7E)
#define  REG_TC_SC_OP1_BK20_7F_L       _PK_L_(0x20, 0x7F)
#define  REG_TC_SC_OP1_BK20_7F_H       _PK_H_(0x20, 0x7F)

#define  REG_TC_SC_SVOP_BK0F_00_L       _PK_L_(0x0F, 0x00)
#define  REG_TC_SC_SVOP_BK0F_00_H       _PK_H_(0x0F, 0x00)
#define  REG_TC_SC_SVOP_BK0F_01_L       _PK_L_(0x0F, 0x01)
#define  REG_TC_SC_SVOP_BK0F_01_H       _PK_H_(0x0F, 0x01)
#define  REG_TC_SC_SVOP_BK0F_02_L       _PK_L_(0x0F, 0x02)
#define  REG_TC_SC_SVOP_BK0F_02_H       _PK_H_(0x0F, 0x02)
#define  REG_TC_SC_SVOP_BK0F_03_L       _PK_L_(0x0F, 0x03)
#define  REG_TC_SC_SVOP_BK0F_03_H       _PK_H_(0x0F, 0x03)
#define  REG_TC_SC_SVOP_BK0F_04_L       _PK_L_(0x0F, 0x04)
#define  REG_TC_SC_SVOP_BK0F_04_H       _PK_H_(0x0F, 0x04)
#define  REG_TC_SC_SVOP_BK0F_05_L       _PK_L_(0x0F, 0x05)
#define  REG_TC_SC_SVOP_BK0F_05_H       _PK_H_(0x0F, 0x05)
#define  REG_TC_SC_SVOP_BK0F_06_L       _PK_L_(0x0F, 0x06)
#define  REG_TC_SC_SVOP_BK0F_06_H       _PK_H_(0x0F, 0x06)
#define  REG_TC_SC_SVOP_BK0F_07_L       _PK_L_(0x0F, 0x07)
#define  REG_TC_SC_SVOP_BK0F_07_H       _PK_H_(0x0F, 0x07)
#define  REG_TC_SC_SVOP_BK0F_08_L       _PK_L_(0x0F, 0x08)
#define  REG_TC_SC_SVOP_BK0F_08_H       _PK_H_(0x0F, 0x08)
#define  REG_TC_SC_SVOP_BK0F_09_L       _PK_L_(0x0F, 0x09)
#define  REG_TC_SC_SVOP_BK0F_09_H       _PK_H_(0x0F, 0x09)
#define  REG_TC_SC_SVOP_BK0F_0A_L       _PK_L_(0x0F, 0x0A)
#define  REG_TC_SC_SVOP_BK0F_0A_H       _PK_H_(0x0F, 0x0A)
#define  REG_TC_SC_SVOP_BK0F_0B_L       _PK_L_(0x0F, 0x0B)
#define  REG_TC_SC_SVOP_BK0F_0B_H       _PK_H_(0x0F, 0x0B)
#define  REG_TC_SC_SVOP_BK0F_0C_L       _PK_L_(0x0F, 0x0C)
#define  REG_TC_SC_SVOP_BK0F_0C_H       _PK_H_(0x0F, 0x0C)
#define  REG_TC_SC_SVOP_BK0F_0D_L       _PK_L_(0x0F, 0x0D)
#define  REG_TC_SC_SVOP_BK0F_0D_H       _PK_H_(0x0F, 0x0D)
#define  REG_TC_SC_SVOP_BK0F_0E_L       _PK_L_(0x0F, 0x0E)
#define  REG_TC_SC_SVOP_BK0F_0E_H       _PK_H_(0x0F, 0x0E)
#define  REG_TC_SC_SVOP_BK0F_0F_L       _PK_L_(0x0F, 0x0F)
#define  REG_TC_SC_SVOP_BK0F_0F_H       _PK_H_(0x0F, 0x0F)
#define  REG_TC_SC_SVOP_BK0F_10_L       _PK_L_(0x0F, 0x10)
#define  REG_TC_SC_SVOP_BK0F_10_H       _PK_H_(0x0F, 0x10)
#define  REG_TC_SC_SVOP_BK0F_11_L       _PK_L_(0x0F, 0x11)
#define  REG_TC_SC_SVOP_BK0F_11_H       _PK_H_(0x0F, 0x11)
#define  REG_TC_SC_SVOP_BK0F_12_L       _PK_L_(0x0F, 0x12)
#define  REG_TC_SC_SVOP_BK0F_12_H       _PK_H_(0x0F, 0x12)
#define  REG_TC_SC_SVOP_BK0F_13_L       _PK_L_(0x0F, 0x13)
#define  REG_TC_SC_SVOP_BK0F_13_H       _PK_H_(0x0F, 0x13)
#define  REG_TC_SC_SVOP_BK0F_14_L       _PK_L_(0x0F, 0x14)
#define  REG_TC_SC_SVOP_BK0F_14_H       _PK_H_(0x0F, 0x14)
#define  REG_TC_SC_SVOP_BK0F_15_L       _PK_L_(0x0F, 0x15)
#define  REG_TC_SC_SVOP_BK0F_15_H       _PK_H_(0x0F, 0x15)
#define  REG_TC_SC_SVOP_BK0F_16_L       _PK_L_(0x0F, 0x16)
#define  REG_TC_SC_SVOP_BK0F_16_H       _PK_H_(0x0F, 0x16)
#define  REG_TC_SC_SVOP_BK0F_17_L       _PK_L_(0x0F, 0x17)
#define  REG_TC_SC_SVOP_BK0F_17_H       _PK_H_(0x0F, 0x17)
#define  REG_TC_SC_SVOP_BK0F_18_L       _PK_L_(0x0F, 0x18)
#define  REG_TC_SC_SVOP_BK0F_18_H       _PK_H_(0x0F, 0x18)
#define  REG_TC_SC_SVOP_BK0F_19_L       _PK_L_(0x0F, 0x19)
#define  REG_TC_SC_SVOP_BK0F_19_H       _PK_H_(0x0F, 0x19)
#define  REG_TC_SC_SVOP_BK0F_1A_L       _PK_L_(0x0F, 0x1A)
#define  REG_TC_SC_SVOP_BK0F_1A_H       _PK_H_(0x0F, 0x1A)
#define  REG_TC_SC_SVOP_BK0F_1B_L       _PK_L_(0x0F, 0x1B)
#define  REG_TC_SC_SVOP_BK0F_1B_H       _PK_H_(0x0F, 0x1B)
#define  REG_TC_SC_SVOP_BK0F_1C_L       _PK_L_(0x0F, 0x1C)
#define  REG_TC_SC_SVOP_BK0F_1C_H       _PK_H_(0x0F, 0x1C)
#define  REG_TC_SC_SVOP_BK0F_1D_L       _PK_L_(0x0F, 0x1D)
#define  REG_TC_SC_SVOP_BK0F_1D_H       _PK_H_(0x0F, 0x1D)
#define  REG_TC_SC_SVOP_BK0F_1E_L       _PK_L_(0x0F, 0x1E)
#define  REG_TC_SC_SVOP_BK0F_1E_H       _PK_H_(0x0F, 0x1E)
#define  REG_TC_SC_SVOP_BK0F_1F_L       _PK_L_(0x0F, 0x1F)
#define  REG_TC_SC_SVOP_BK0F_1F_H       _PK_H_(0x0F, 0x1F)
#define  REG_TC_SC_SVOP_BK0F_20_L       _PK_L_(0x0F, 0x20)
#define  REG_TC_SC_SVOP_BK0F_20_H       _PK_H_(0x0F, 0x20)
#define  REG_TC_SC_SVOP_BK0F_21_L       _PK_L_(0x0F, 0x21)
#define  REG_TC_SC_SVOP_BK0F_21_H       _PK_H_(0x0F, 0x21)
#define  REG_TC_SC_SVOP_BK0F_22_L       _PK_L_(0x0F, 0x22)
#define  REG_TC_SC_SVOP_BK0F_22_H       _PK_H_(0x0F, 0x22)
#define  REG_TC_SC_SVOP_BK0F_23_L       _PK_L_(0x0F, 0x23)
#define  REG_TC_SC_SVOP_BK0F_23_H       _PK_H_(0x0F, 0x23)
#define  REG_TC_SC_SVOP_BK0F_24_L       _PK_L_(0x0F, 0x24)
#define  REG_TC_SC_SVOP_BK0F_24_H       _PK_H_(0x0F, 0x24)
#define  REG_TC_SC_SVOP_BK0F_25_L       _PK_L_(0x0F, 0x25)
#define  REG_TC_SC_SVOP_BK0F_25_H       _PK_H_(0x0F, 0x25)
#define  REG_TC_SC_SVOP_BK0F_26_L       _PK_L_(0x0F, 0x26)
#define  REG_TC_SC_SVOP_BK0F_26_H       _PK_H_(0x0F, 0x26)
#define  REG_TC_SC_SVOP_BK0F_27_L       _PK_L_(0x0F, 0x27)
#define  REG_TC_SC_SVOP_BK0F_27_H       _PK_H_(0x0F, 0x27)
#define  REG_TC_SC_SVOP_BK0F_28_L       _PK_L_(0x0F, 0x28)
#define  REG_TC_SC_SVOP_BK0F_28_H       _PK_H_(0x0F, 0x28)
#define  REG_TC_SC_SVOP_BK0F_29_L       _PK_L_(0x0F, 0x29)
#define  REG_TC_SC_SVOP_BK0F_29_H       _PK_H_(0x0F, 0x29)
#define  REG_TC_SC_SVOP_BK0F_2A_L       _PK_L_(0x0F, 0x2A)
#define  REG_TC_SC_SVOP_BK0F_2A_H       _PK_H_(0x0F, 0x2A)
#define  REG_TC_SC_SVOP_BK0F_2B_L       _PK_L_(0x0F, 0x2B)
#define  REG_TC_SC_SVOP_BK0F_2B_H       _PK_H_(0x0F, 0x2B)
#define  REG_TC_SC_SVOP_BK0F_2C_L       _PK_L_(0x0F, 0x2C)
#define  REG_TC_SC_SVOP_BK0F_2C_H       _PK_H_(0x0F, 0x2C)
#define  REG_TC_SC_SVOP_BK0F_2D_L       _PK_L_(0x0F, 0x2D)
#define  REG_TC_SC_SVOP_BK0F_2D_H       _PK_H_(0x0F, 0x2D)
#define  REG_TC_SC_SVOP_BK0F_2E_L       _PK_L_(0x0F, 0x2E)
#define  REG_TC_SC_SVOP_BK0F_2E_H       _PK_H_(0x0F, 0x2E)
#define  REG_TC_SC_SVOP_BK0F_2F_L       _PK_L_(0x0F, 0x2F)
#define  REG_TC_SC_SVOP_BK0F_2F_H       _PK_H_(0x0F, 0x2F)
#define  REG_TC_SC_SVOP_BK0F_30_L       _PK_L_(0x0F, 0x30)
#define  REG_TC_SC_SVOP_BK0F_30_H       _PK_H_(0x0F, 0x30)
#define  REG_TC_SC_SVOP_BK0F_31_L       _PK_L_(0x0F, 0x31)
#define  REG_TC_SC_SVOP_BK0F_31_H       _PK_H_(0x0F, 0x31)
#define  REG_TC_SC_SVOP_BK0F_32_L       _PK_L_(0x0F, 0x32)
#define  REG_TC_SC_SVOP_BK0F_32_H       _PK_H_(0x0F, 0x32)
#define  REG_TC_SC_SVOP_BK0F_33_L       _PK_L_(0x0F, 0x33)
#define  REG_TC_SC_SVOP_BK0F_33_H       _PK_H_(0x0F, 0x33)
#define  REG_TC_SC_SVOP_BK0F_34_L       _PK_L_(0x0F, 0x34)
#define  REG_TC_SC_SVOP_BK0F_34_H       _PK_H_(0x0F, 0x34)
#define  REG_TC_SC_SVOP_BK0F_35_L       _PK_L_(0x0F, 0x35)
#define  REG_TC_SC_SVOP_BK0F_35_H       _PK_H_(0x0F, 0x35)
#define  REG_TC_SC_SVOP_BK0F_36_L       _PK_L_(0x0F, 0x36)
#define  REG_TC_SC_SVOP_BK0F_36_H       _PK_H_(0x0F, 0x36)
#define  REG_TC_SC_SVOP_BK0F_37_L       _PK_L_(0x0F, 0x37)
#define  REG_TC_SC_SVOP_BK0F_37_H       _PK_H_(0x0F, 0x37)
#define  REG_TC_SC_SVOP_BK0F_38_L       _PK_L_(0x0F, 0x38)
#define  REG_TC_SC_SVOP_BK0F_38_H       _PK_H_(0x0F, 0x38)
#define  REG_TC_SC_SVOP_BK0F_39_L       _PK_L_(0x0F, 0x39)
#define  REG_TC_SC_SVOP_BK0F_39_H       _PK_H_(0x0F, 0x39)
#define  REG_TC_SC_SVOP_BK0F_3A_L       _PK_L_(0x0F, 0x3A)
#define  REG_TC_SC_SVOP_BK0F_3A_H       _PK_H_(0x0F, 0x3A)
#define  REG_TC_SC_SVOP_BK0F_3B_L       _PK_L_(0x0F, 0x3B)
#define  REG_TC_SC_SVOP_BK0F_3B_H       _PK_H_(0x0F, 0x3B)
#define  REG_TC_SC_SVOP_BK0F_3C_L       _PK_L_(0x0F, 0x3C)
#define  REG_TC_SC_SVOP_BK0F_3C_H       _PK_H_(0x0F, 0x3C)
#define  REG_TC_SC_SVOP_BK0F_3D_L       _PK_L_(0x0F, 0x3D)
#define  REG_TC_SC_SVOP_BK0F_3D_H       _PK_H_(0x0F, 0x3D)
#define  REG_TC_SC_SVOP_BK0F_3E_L       _PK_L_(0x0F, 0x3E)
#define  REG_TC_SC_SVOP_BK0F_3E_H       _PK_H_(0x0F, 0x3E)
#define  REG_TC_SC_SVOP_BK0F_3F_L       _PK_L_(0x0F, 0x3F)
#define  REG_TC_SC_SVOP_BK0F_3F_H       _PK_H_(0x0F, 0x3F)
#define  REG_TC_SC_SVOP_BK0F_40_L       _PK_L_(0x0F, 0x40)
#define  REG_TC_SC_SVOP_BK0F_40_H       _PK_H_(0x0F, 0x40)
#define  REG_TC_SC_SVOP_BK0F_41_L       _PK_L_(0x0F, 0x41)
#define  REG_TC_SC_SVOP_BK0F_41_H       _PK_H_(0x0F, 0x41)
#define  REG_TC_SC_SVOP_BK0F_42_L       _PK_L_(0x0F, 0x42)
#define  REG_TC_SC_SVOP_BK0F_42_H       _PK_H_(0x0F, 0x42)
#define  REG_TC_SC_SVOP_BK0F_43_L       _PK_L_(0x0F, 0x43)
#define  REG_TC_SC_SVOP_BK0F_43_H       _PK_H_(0x0F, 0x43)
#define  REG_TC_SC_SVOP_BK0F_44_L       _PK_L_(0x0F, 0x44)
#define  REG_TC_SC_SVOP_BK0F_44_H       _PK_H_(0x0F, 0x44)
#define  REG_TC_SC_SVOP_BK0F_45_L       _PK_L_(0x0F, 0x45)
#define  REG_TC_SC_SVOP_BK0F_45_H       _PK_H_(0x0F, 0x45)
#define  REG_TC_SC_SVOP_BK0F_46_L       _PK_L_(0x0F, 0x46)
#define  REG_TC_SC_SVOP_BK0F_46_H       _PK_H_(0x0F, 0x46)
#define  REG_TC_SC_SVOP_BK0F_47_L       _PK_L_(0x0F, 0x47)
#define  REG_TC_SC_SVOP_BK0F_47_H       _PK_H_(0x0F, 0x47)
#define  REG_TC_SC_SVOP_BK0F_48_L       _PK_L_(0x0F, 0x48)
#define  REG_TC_SC_SVOP_BK0F_48_H       _PK_H_(0x0F, 0x48)
#define  REG_TC_SC_SVOP_BK0F_49_L       _PK_L_(0x0F, 0x49)
#define  REG_TC_SC_SVOP_BK0F_49_H       _PK_H_(0x0F, 0x49)
#define  REG_TC_SC_SVOP_BK0F_4A_L       _PK_L_(0x0F, 0x4A)
#define  REG_TC_SC_SVOP_BK0F_4A_H       _PK_H_(0x0F, 0x4A)
#define  REG_TC_SC_SVOP_BK0F_4B_L       _PK_L_(0x0F, 0x4B)
#define  REG_TC_SC_SVOP_BK0F_4B_H       _PK_H_(0x0F, 0x4B)
#define  REG_TC_SC_SVOP_BK0F_4C_L       _PK_L_(0x0F, 0x4C)
#define  REG_TC_SC_SVOP_BK0F_4C_H       _PK_H_(0x0F, 0x4C)
#define  REG_TC_SC_SVOP_BK0F_4D_L       _PK_L_(0x0F, 0x4D)
#define  REG_TC_SC_SVOP_BK0F_4D_H       _PK_H_(0x0F, 0x4D)
#define  REG_TC_SC_SVOP_BK0F_4E_L       _PK_L_(0x0F, 0x4E)
#define  REG_TC_SC_SVOP_BK0F_4E_H       _PK_H_(0x0F, 0x4E)
#define  REG_TC_SC_SVOP_BK0F_4F_L       _PK_L_(0x0F, 0x4F)
#define  REG_TC_SC_SVOP_BK0F_4F_H       _PK_H_(0x0F, 0x4F)
#define  REG_TC_SC_SVOP_BK0F_50_L       _PK_L_(0x0F, 0x50)
#define  REG_TC_SC_SVOP_BK0F_50_H       _PK_H_(0x0F, 0x50)
#define  REG_TC_SC_SVOP_BK0F_51_L       _PK_L_(0x0F, 0x51)
#define  REG_TC_SC_SVOP_BK0F_51_H       _PK_H_(0x0F, 0x51)
#define  REG_TC_SC_SVOP_BK0F_52_L       _PK_L_(0x0F, 0x52)
#define  REG_TC_SC_SVOP_BK0F_52_H       _PK_H_(0x0F, 0x52)
#define  REG_TC_SC_SVOP_BK0F_53_L       _PK_L_(0x0F, 0x53)
#define  REG_TC_SC_SVOP_BK0F_53_H       _PK_H_(0x0F, 0x53)
#define  REG_TC_SC_SVOP_BK0F_54_L       _PK_L_(0x0F, 0x54)
#define  REG_TC_SC_SVOP_BK0F_54_H       _PK_H_(0x0F, 0x54)
#define  REG_TC_SC_SVOP_BK0F_55_L       _PK_L_(0x0F, 0x55)
#define  REG_TC_SC_SVOP_BK0F_55_H       _PK_H_(0x0F, 0x55)
#define  REG_TC_SC_SVOP_BK0F_56_L       _PK_L_(0x0F, 0x56)
#define  REG_TC_SC_SVOP_BK0F_56_H       _PK_H_(0x0F, 0x56)
#define  REG_TC_SC_SVOP_BK0F_57_L       _PK_L_(0x0F, 0x57)
#define  REG_TC_SC_SVOP_BK0F_57_H       _PK_H_(0x0F, 0x57)
#define  REG_TC_SC_SVOP_BK0F_58_L       _PK_L_(0x0F, 0x58)
#define  REG_TC_SC_SVOP_BK0F_58_H       _PK_H_(0x0F, 0x58)
#define  REG_TC_SC_SVOP_BK0F_59_L       _PK_L_(0x0F, 0x59)
#define  REG_TC_SC_SVOP_BK0F_59_H       _PK_H_(0x0F, 0x59)
#define  REG_TC_SC_SVOP_BK0F_5A_L       _PK_L_(0x0F, 0x5A)
#define  REG_TC_SC_SVOP_BK0F_5A_H       _PK_H_(0x0F, 0x5A)
#define  REG_TC_SC_SVOP_BK0F_5B_L       _PK_L_(0x0F, 0x5B)
#define  REG_TC_SC_SVOP_BK0F_5B_H       _PK_H_(0x0F, 0x5B)
#define  REG_TC_SC_SVOP_BK0F_5C_L       _PK_L_(0x0F, 0x5C)
#define  REG_TC_SC_SVOP_BK0F_5C_H       _PK_H_(0x0F, 0x5C)
#define  REG_TC_SC_SVOP_BK0F_5D_L       _PK_L_(0x0F, 0x5D)
#define  REG_TC_SC_SVOP_BK0F_5D_H       _PK_H_(0x0F, 0x5D)
#define  REG_TC_SC_SVOP_BK0F_5E_L       _PK_L_(0x0F, 0x5E)
#define  REG_TC_SC_SVOP_BK0F_5E_H       _PK_H_(0x0F, 0x5E)
#define  REG_TC_SC_SVOP_BK0F_5F_L       _PK_L_(0x0F, 0x5F)
#define  REG_TC_SC_SVOP_BK0F_5F_H       _PK_H_(0x0F, 0x5F)
#define  REG_TC_SC_SVOP_BK0F_60_L       _PK_L_(0x0F, 0x60)
#define  REG_TC_SC_SVOP_BK0F_60_H       _PK_H_(0x0F, 0x60)
#define  REG_TC_SC_SVOP_BK0F_61_L       _PK_L_(0x0F, 0x61)
#define  REG_TC_SC_SVOP_BK0F_61_H       _PK_H_(0x0F, 0x61)
#define  REG_TC_SC_SVOP_BK0F_62_L       _PK_L_(0x0F, 0x62)
#define  REG_TC_SC_SVOP_BK0F_62_H       _PK_H_(0x0F, 0x62)
#define  REG_TC_SC_SVOP_BK0F_63_L       _PK_L_(0x0F, 0x63)
#define  REG_TC_SC_SVOP_BK0F_63_H       _PK_H_(0x0F, 0x63)
#define  REG_TC_SC_SVOP_BK0F_64_L       _PK_L_(0x0F, 0x64)
#define  REG_TC_SC_SVOP_BK0F_64_H       _PK_H_(0x0F, 0x64)
#define  REG_TC_SC_SVOP_BK0F_65_L       _PK_L_(0x0F, 0x65)
#define  REG_TC_SC_SVOP_BK0F_65_H       _PK_H_(0x0F, 0x65)
#define  REG_TC_SC_SVOP_BK0F_66_L       _PK_L_(0x0F, 0x66)
#define  REG_TC_SC_SVOP_BK0F_66_H       _PK_H_(0x0F, 0x66)
#define  REG_TC_SC_SVOP_BK0F_67_L       _PK_L_(0x0F, 0x67)
#define  REG_TC_SC_SVOP_BK0F_67_H       _PK_H_(0x0F, 0x67)
#define  REG_TC_SC_SVOP_BK0F_68_L       _PK_L_(0x0F, 0x68)
#define  REG_TC_SC_SVOP_BK0F_68_H       _PK_H_(0x0F, 0x68)
#define  REG_TC_SC_SVOP_BK0F_69_L       _PK_L_(0x0F, 0x69)
#define  REG_TC_SC_SVOP_BK0F_69_H       _PK_H_(0x0F, 0x69)
#define  REG_TC_SC_SVOP_BK0F_6A_L       _PK_L_(0x0F, 0x6A)
#define  REG_TC_SC_SVOP_BK0F_6A_H       _PK_H_(0x0F, 0x6A)
#define  REG_TC_SC_SVOP_BK0F_6B_L       _PK_L_(0x0F, 0x6B)
#define  REG_TC_SC_SVOP_BK0F_6B_H       _PK_H_(0x0F, 0x6B)
#define  REG_TC_SC_SVOP_BK0F_6C_L       _PK_L_(0x0F, 0x6C)
#define  REG_TC_SC_SVOP_BK0F_6C_H       _PK_H_(0x0F, 0x6C)
#define  REG_TC_SC_SVOP_BK0F_6D_L       _PK_L_(0x0F, 0x6D)
#define  REG_TC_SC_SVOP_BK0F_6D_H       _PK_H_(0x0F, 0x6D)
#define  REG_TC_SC_SVOP_BK0F_6E_L       _PK_L_(0x0F, 0x6E)
#define  REG_TC_SC_SVOP_BK0F_6E_H       _PK_H_(0x0F, 0x6E)
#define  REG_TC_SC_SVOP_BK0F_6F_L       _PK_L_(0x0F, 0x6F)
#define  REG_TC_SC_SVOP_BK0F_6F_H       _PK_H_(0x0F, 0x6F)
#define  REG_TC_SC_SVOP_BK0F_70_L       _PK_L_(0x0F, 0x70)
#define  REG_TC_SC_SVOP_BK0F_70_H       _PK_H_(0x0F, 0x70)
#define  REG_TC_SC_SVOP_BK0F_71_L       _PK_L_(0x0F, 0x71)
#define  REG_TC_SC_SVOP_BK0F_71_H       _PK_H_(0x0F, 0x71)
#define  REG_TC_SC_SVOP_BK0F_72_L       _PK_L_(0x0F, 0x72)
#define  REG_TC_SC_SVOP_BK0F_72_H       _PK_H_(0x0F, 0x72)
#define  REG_TC_SC_SVOP_BK0F_73_L       _PK_L_(0x0F, 0x73)
#define  REG_TC_SC_SVOP_BK0F_73_H       _PK_H_(0x0F, 0x73)
#define  REG_TC_SC_SVOP_BK0F_74_L       _PK_L_(0x0F, 0x74)
#define  REG_TC_SC_SVOP_BK0F_74_H       _PK_H_(0x0F, 0x74)
#define  REG_TC_SC_SVOP_BK0F_75_L       _PK_L_(0x0F, 0x75)
#define  REG_TC_SC_SVOP_BK0F_75_H       _PK_H_(0x0F, 0x75)
#define  REG_TC_SC_SVOP_BK0F_76_L       _PK_L_(0x0F, 0x76)
#define  REG_TC_SC_SVOP_BK0F_76_H       _PK_H_(0x0F, 0x76)
#define  REG_TC_SC_SVOP_BK0F_77_L       _PK_L_(0x0F, 0x77)
#define  REG_TC_SC_SVOP_BK0F_77_H       _PK_H_(0x0F, 0x77)
#define  REG_TC_SC_SVOP_BK0F_78_L       _PK_L_(0x0F, 0x78)
#define  REG_TC_SC_SVOP_BK0F_78_H       _PK_H_(0x0F, 0x78)
#define  REG_TC_SC_SVOP_BK0F_79_L       _PK_L_(0x0F, 0x79)
#define  REG_TC_SC_SVOP_BK0F_79_H       _PK_H_(0x0F, 0x79)
#define  REG_TC_SC_SVOP_BK0F_7A_L       _PK_L_(0x0F, 0x7A)
#define  REG_TC_SC_SVOP_BK0F_7A_H       _PK_H_(0x0F, 0x7A)
#define  REG_TC_SC_SVOP_BK0F_7B_L       _PK_L_(0x0F, 0x7B)
#define  REG_TC_SC_SVOP_BK0F_7B_H       _PK_H_(0x0F, 0x7B)
#define  REG_TC_SC_SVOP_BK0F_7C_L       _PK_L_(0x0F, 0x7C)
#define  REG_TC_SC_SVOP_BK0F_7C_H       _PK_H_(0x0F, 0x7C)
#define  REG_TC_SC_SVOP_BK0F_7D_L       _PK_L_(0x0F, 0x7D)
#define  REG_TC_SC_SVOP_BK0F_7D_H       _PK_H_(0x0F, 0x7D)
#define  REG_TC_SC_SVOP_BK0F_7E_L       _PK_L_(0x0F, 0x7E)
#define  REG_TC_SC_SVOP_BK0F_7E_H       _PK_H_(0x0F, 0x7E)
#define  REG_TC_SC_SVOP_BK0F_7F_L       _PK_L_(0x0F, 0x7F)
#define  REG_TC_SC_SVOP_BK0F_7F_H       _PK_H_(0x0F, 0x7F)

#define  REG_TC_SC_SCMI_BK12_00_L       _PK_L_(0x12, 0x00)
#define  REG_TC_SC_SCMI_BK12_00_H       _PK_H_(0x12, 0x00)
#define  REG_TC_SC_SCMI_BK12_01_L       _PK_L_(0x12, 0x01)
#define  REG_TC_SC_SCMI_BK12_01_H       _PK_H_(0x12, 0x01)
#define  REG_TC_SC_SCMI_BK12_02_L       _PK_L_(0x12, 0x02)
#define  REG_TC_SC_SCMI_BK12_02_H       _PK_H_(0x12, 0x02)
#define  REG_TC_SC_SCMI_BK12_03_L       _PK_L_(0x12, 0x03)
#define  REG_TC_SC_SCMI_BK12_03_H       _PK_H_(0x12, 0x03)
#define  REG_TC_SC_SCMI_BK12_04_L       _PK_L_(0x12, 0x04)
#define  REG_TC_SC_SCMI_BK12_04_H       _PK_H_(0x12, 0x04)
#define  REG_TC_SC_SCMI_BK12_05_L       _PK_L_(0x12, 0x05)
#define  REG_TC_SC_SCMI_BK12_05_H       _PK_H_(0x12, 0x05)
#define  REG_TC_SC_SCMI_BK12_06_L       _PK_L_(0x12, 0x06)
#define  REG_TC_SC_SCMI_BK12_06_H       _PK_H_(0x12, 0x06)
#define  REG_TC_SC_SCMI_BK12_07_L       _PK_L_(0x12, 0x07)
#define  REG_TC_SC_SCMI_BK12_07_H       _PK_H_(0x12, 0x07)
#define  REG_TC_SC_SCMI_BK12_08_L       _PK_L_(0x12, 0x08)
#define  REG_TC_SC_SCMI_BK12_08_H       _PK_H_(0x12, 0x08)
#define  REG_TC_SC_SCMI_BK12_09_L       _PK_L_(0x12, 0x09)
#define  REG_TC_SC_SCMI_BK12_09_H       _PK_H_(0x12, 0x09)
#define  REG_TC_SC_SCMI_BK12_0A_L       _PK_L_(0x12, 0x0A)
#define  REG_TC_SC_SCMI_BK12_0A_H       _PK_H_(0x12, 0x0A)
#define  REG_TC_SC_SCMI_BK12_0B_L       _PK_L_(0x12, 0x0B)
#define  REG_TC_SC_SCMI_BK12_0B_H       _PK_H_(0x12, 0x0B)
#define  REG_TC_SC_SCMI_BK12_0C_L       _PK_L_(0x12, 0x0C)
#define  REG_TC_SC_SCMI_BK12_0C_H       _PK_H_(0x12, 0x0C)
#define  REG_TC_SC_SCMI_BK12_0D_L       _PK_L_(0x12, 0x0D)
#define  REG_TC_SC_SCMI_BK12_0D_H       _PK_H_(0x12, 0x0D)
#define  REG_TC_SC_SCMI_BK12_0E_L       _PK_L_(0x12, 0x0E)
#define  REG_TC_SC_SCMI_BK12_0E_H       _PK_H_(0x12, 0x0E)
#define  REG_TC_SC_SCMI_BK12_0F_L       _PK_L_(0x12, 0x0F)
#define  REG_TC_SC_SCMI_BK12_0F_H       _PK_H_(0x12, 0x0F)
#define  REG_TC_SC_SCMI_BK12_10_L       _PK_L_(0x12, 0x10)
#define  REG_TC_SC_SCMI_BK12_10_H       _PK_H_(0x12, 0x10)
#define  REG_TC_SC_SCMI_BK12_11_L       _PK_L_(0x12, 0x11)
#define  REG_TC_SC_SCMI_BK12_11_H       _PK_H_(0x12, 0x11)
#define  REG_TC_SC_SCMI_BK12_12_L       _PK_L_(0x12, 0x12)
#define  REG_TC_SC_SCMI_BK12_12_H       _PK_H_(0x12, 0x12)
#define  REG_TC_SC_SCMI_BK12_13_L       _PK_L_(0x12, 0x13)
#define  REG_TC_SC_SCMI_BK12_13_H       _PK_H_(0x12, 0x13)
#define  REG_TC_SC_SCMI_BK12_14_L       _PK_L_(0x12, 0x14)
#define  REG_TC_SC_SCMI_BK12_14_H       _PK_H_(0x12, 0x14)
#define  REG_TC_SC_SCMI_BK12_15_L       _PK_L_(0x12, 0x15)
#define  REG_TC_SC_SCMI_BK12_15_H       _PK_H_(0x12, 0x15)
#define  REG_TC_SC_SCMI_BK12_16_L       _PK_L_(0x12, 0x16)
#define  REG_TC_SC_SCMI_BK12_16_H       _PK_H_(0x12, 0x16)
#define  REG_TC_SC_SCMI_BK12_17_L       _PK_L_(0x12, 0x17)
#define  REG_TC_SC_SCMI_BK12_17_H       _PK_H_(0x12, 0x17)
#define  REG_TC_SC_SCMI_BK12_18_L       _PK_L_(0x12, 0x18)
#define  REG_TC_SC_SCMI_BK12_18_H       _PK_H_(0x12, 0x18)
#define  REG_TC_SC_SCMI_BK12_19_L       _PK_L_(0x12, 0x19)
#define  REG_TC_SC_SCMI_BK12_19_H       _PK_H_(0x12, 0x19)
#define  REG_TC_SC_SCMI_BK12_1A_L       _PK_L_(0x12, 0x1A)
#define  REG_TC_SC_SCMI_BK12_1A_H       _PK_H_(0x12, 0x1A)
#define  REG_TC_SC_SCMI_BK12_1B_L       _PK_L_(0x12, 0x1B)
#define  REG_TC_SC_SCMI_BK12_1B_H       _PK_H_(0x12, 0x1B)
#define  REG_TC_SC_SCMI_BK12_1C_L       _PK_L_(0x12, 0x1C)
#define  REG_TC_SC_SCMI_BK12_1C_H       _PK_H_(0x12, 0x1C)
#define  REG_TC_SC_SCMI_BK12_1D_L       _PK_L_(0x12, 0x1D)
#define  REG_TC_SC_SCMI_BK12_1D_H       _PK_H_(0x12, 0x1D)
#define  REG_TC_SC_SCMI_BK12_1E_L       _PK_L_(0x12, 0x1E)
#define  REG_TC_SC_SCMI_BK12_1E_H       _PK_H_(0x12, 0x1E)
#define  REG_TC_SC_SCMI_BK12_1F_L       _PK_L_(0x12, 0x1F)
#define  REG_TC_SC_SCMI_BK12_1F_H       _PK_H_(0x12, 0x1F)
#define  REG_TC_SC_SCMI_BK12_20_L       _PK_L_(0x12, 0x20)
#define  REG_TC_SC_SCMI_BK12_20_H       _PK_H_(0x12, 0x20)
#define  REG_TC_SC_SCMI_BK12_21_L       _PK_L_(0x12, 0x21)
#define  REG_TC_SC_SCMI_BK12_21_H       _PK_H_(0x12, 0x21)
#define  REG_TC_SC_SCMI_BK12_22_L       _PK_L_(0x12, 0x22)
#define  REG_TC_SC_SCMI_BK12_22_H       _PK_H_(0x12, 0x22)
#define  REG_TC_SC_SCMI_BK12_23_L       _PK_L_(0x12, 0x23)
#define  REG_TC_SC_SCMI_BK12_23_H       _PK_H_(0x12, 0x23)
#define  REG_TC_SC_SCMI_BK12_24_L       _PK_L_(0x12, 0x24)
#define  REG_TC_SC_SCMI_BK12_24_H       _PK_H_(0x12, 0x24)
#define  REG_TC_SC_SCMI_BK12_25_L       _PK_L_(0x12, 0x25)
#define  REG_TC_SC_SCMI_BK12_25_H       _PK_H_(0x12, 0x25)
#define  REG_TC_SC_SCMI_BK12_26_L       _PK_L_(0x12, 0x26)
#define  REG_TC_SC_SCMI_BK12_26_H       _PK_H_(0x12, 0x26)
#define  REG_TC_SC_SCMI_BK12_27_L       _PK_L_(0x12, 0x27)
#define  REG_TC_SC_SCMI_BK12_27_H       _PK_H_(0x12, 0x27)
#define  REG_TC_SC_SCMI_BK12_28_L       _PK_L_(0x12, 0x28)
#define  REG_TC_SC_SCMI_BK12_28_H       _PK_H_(0x12, 0x28)
#define  REG_TC_SC_SCMI_BK12_29_L       _PK_L_(0x12, 0x29)
#define  REG_TC_SC_SCMI_BK12_29_H       _PK_H_(0x12, 0x29)
#define  REG_TC_SC_SCMI_BK12_2A_L       _PK_L_(0x12, 0x2A)
#define  REG_TC_SC_SCMI_BK12_2A_H       _PK_H_(0x12, 0x2A)
#define  REG_TC_SC_SCMI_BK12_2B_L       _PK_L_(0x12, 0x2B)
#define  REG_TC_SC_SCMI_BK12_2B_H       _PK_H_(0x12, 0x2B)
#define  REG_TC_SC_SCMI_BK12_2C_L       _PK_L_(0x12, 0x2C)
#define  REG_TC_SC_SCMI_BK12_2C_H       _PK_H_(0x12, 0x2C)
#define  REG_TC_SC_SCMI_BK12_2D_L       _PK_L_(0x12, 0x2D)
#define  REG_TC_SC_SCMI_BK12_2D_H       _PK_H_(0x12, 0x2D)
#define  REG_TC_SC_SCMI_BK12_2E_L       _PK_L_(0x12, 0x2E)
#define  REG_TC_SC_SCMI_BK12_2E_H       _PK_H_(0x12, 0x2E)
#define  REG_TC_SC_SCMI_BK12_2F_L       _PK_L_(0x12, 0x2F)
#define  REG_TC_SC_SCMI_BK12_2F_H       _PK_H_(0x12, 0x2F)
#define  REG_TC_SC_SCMI_BK12_30_L       _PK_L_(0x12, 0x30)
#define  REG_TC_SC_SCMI_BK12_30_H       _PK_H_(0x12, 0x30)
#define  REG_TC_SC_SCMI_BK12_31_L       _PK_L_(0x12, 0x31)
#define  REG_TC_SC_SCMI_BK12_31_H       _PK_H_(0x12, 0x31)
#define  REG_TC_SC_SCMI_BK12_32_L       _PK_L_(0x12, 0x32)
#define  REG_TC_SC_SCMI_BK12_32_H       _PK_H_(0x12, 0x32)
#define  REG_TC_SC_SCMI_BK12_33_L       _PK_L_(0x12, 0x33)
#define  REG_TC_SC_SCMI_BK12_33_H       _PK_H_(0x12, 0x33)
#define  REG_TC_SC_SCMI_BK12_34_L       _PK_L_(0x12, 0x34)
#define  REG_TC_SC_SCMI_BK12_34_H       _PK_H_(0x12, 0x34)
#define  REG_TC_SC_SCMI_BK12_35_L       _PK_L_(0x12, 0x35)
#define  REG_TC_SC_SCMI_BK12_35_H       _PK_H_(0x12, 0x35)
#define  REG_TC_SC_SCMI_BK12_36_L       _PK_L_(0x12, 0x36)
#define  REG_TC_SC_SCMI_BK12_36_H       _PK_H_(0x12, 0x36)
#define  REG_TC_SC_SCMI_BK12_37_L       _PK_L_(0x12, 0x37)
#define  REG_TC_SC_SCMI_BK12_37_H       _PK_H_(0x12, 0x37)
#define  REG_TC_SC_SCMI_BK12_38_L       _PK_L_(0x12, 0x38)
#define  REG_TC_SC_SCMI_BK12_38_H       _PK_H_(0x12, 0x38)
#define  REG_TC_SC_SCMI_BK12_39_L       _PK_L_(0x12, 0x39)
#define  REG_TC_SC_SCMI_BK12_39_H       _PK_H_(0x12, 0x39)
#define  REG_TC_SC_SCMI_BK12_3A_L       _PK_L_(0x12, 0x3A)
#define  REG_TC_SC_SCMI_BK12_3A_H       _PK_H_(0x12, 0x3A)
#define  REG_TC_SC_SCMI_BK12_3B_L       _PK_L_(0x12, 0x3B)
#define  REG_TC_SC_SCMI_BK12_3B_H       _PK_H_(0x12, 0x3B)
#define  REG_TC_SC_SCMI_BK12_3C_L       _PK_L_(0x12, 0x3C)
#define  REG_TC_SC_SCMI_BK12_3C_H       _PK_H_(0x12, 0x3C)
#define  REG_TC_SC_SCMI_BK12_3D_L       _PK_L_(0x12, 0x3D)
#define  REG_TC_SC_SCMI_BK12_3D_H       _PK_H_(0x12, 0x3D)
#define  REG_TC_SC_SCMI_BK12_3E_L       _PK_L_(0x12, 0x3E)
#define  REG_TC_SC_SCMI_BK12_3E_H       _PK_H_(0x12, 0x3E)
#define  REG_TC_SC_SCMI_BK12_3F_L       _PK_L_(0x12, 0x3F)
#define  REG_TC_SC_SCMI_BK12_3F_H       _PK_H_(0x12, 0x3F)
#define  REG_TC_SC_SCMI_BK12_40_L       _PK_L_(0x12, 0x40)
#define  REG_TC_SC_SCMI_BK12_40_H       _PK_H_(0x12, 0x40)
#define  REG_TC_SC_SCMI_BK12_41_L       _PK_L_(0x12, 0x41)
#define  REG_TC_SC_SCMI_BK12_41_H       _PK_H_(0x12, 0x41)
#define  REG_TC_SC_SCMI_BK12_42_L       _PK_L_(0x12, 0x42)
#define  REG_TC_SC_SCMI_BK12_42_H       _PK_H_(0x12, 0x42)
#define  REG_TC_SC_SCMI_BK12_43_L       _PK_L_(0x12, 0x43)
#define  REG_TC_SC_SCMI_BK12_43_H       _PK_H_(0x12, 0x43)
#define  REG_TC_SC_SCMI_BK12_44_L       _PK_L_(0x12, 0x44)
#define  REG_TC_SC_SCMI_BK12_44_H       _PK_H_(0x12, 0x44)
#define  REG_TC_SC_SCMI_BK12_45_L       _PK_L_(0x12, 0x45)
#define  REG_TC_SC_SCMI_BK12_45_H       _PK_H_(0x12, 0x45)
#define  REG_TC_SC_SCMI_BK12_46_L       _PK_L_(0x12, 0x46)
#define  REG_TC_SC_SCMI_BK12_46_H       _PK_H_(0x12, 0x46)
#define  REG_TC_SC_SCMI_BK12_47_L       _PK_L_(0x12, 0x47)
#define  REG_TC_SC_SCMI_BK12_47_H       _PK_H_(0x12, 0x47)
#define  REG_TC_SC_SCMI_BK12_48_L       _PK_L_(0x12, 0x48)
#define  REG_TC_SC_SCMI_BK12_48_H       _PK_H_(0x12, 0x48)
#define  REG_TC_SC_SCMI_BK12_49_L       _PK_L_(0x12, 0x49)
#define  REG_TC_SC_SCMI_BK12_49_H       _PK_H_(0x12, 0x49)
#define  REG_TC_SC_SCMI_BK12_4A_L       _PK_L_(0x12, 0x4A)
#define  REG_TC_SC_SCMI_BK12_4A_H       _PK_H_(0x12, 0x4A)
#define  REG_TC_SC_SCMI_BK12_4B_L       _PK_L_(0x12, 0x4B)
#define  REG_TC_SC_SCMI_BK12_4B_H       _PK_H_(0x12, 0x4B)
#define  REG_TC_SC_SCMI_BK12_4C_L       _PK_L_(0x12, 0x4C)
#define  REG_TC_SC_SCMI_BK12_4C_H       _PK_H_(0x12, 0x4C)
#define  REG_TC_SC_SCMI_BK12_4D_L       _PK_L_(0x12, 0x4D)
#define  REG_TC_SC_SCMI_BK12_4D_H       _PK_H_(0x12, 0x4D)
#define  REG_TC_SC_SCMI_BK12_4E_L       _PK_L_(0x12, 0x4E)
#define  REG_TC_SC_SCMI_BK12_4E_H       _PK_H_(0x12, 0x4E)
#define  REG_TC_SC_SCMI_BK12_4F_L       _PK_L_(0x12, 0x4F)
#define  REG_TC_SC_SCMI_BK12_4F_H       _PK_H_(0x12, 0x4F)
#define  REG_TC_SC_SCMI_BK12_50_L       _PK_L_(0x12, 0x50)
#define  REG_TC_SC_SCMI_BK12_50_H       _PK_H_(0x12, 0x50)
#define  REG_TC_SC_SCMI_BK12_51_L       _PK_L_(0x12, 0x51)
#define  REG_TC_SC_SCMI_BK12_51_H       _PK_H_(0x12, 0x51)
#define  REG_TC_SC_SCMI_BK12_52_L       _PK_L_(0x12, 0x52)
#define  REG_TC_SC_SCMI_BK12_52_H       _PK_H_(0x12, 0x52)
#define  REG_TC_SC_SCMI_BK12_53_L       _PK_L_(0x12, 0x53)
#define  REG_TC_SC_SCMI_BK12_53_H       _PK_H_(0x12, 0x53)
#define  REG_TC_SC_SCMI_BK12_54_L       _PK_L_(0x12, 0x54)
#define  REG_TC_SC_SCMI_BK12_54_H       _PK_H_(0x12, 0x54)
#define  REG_TC_SC_SCMI_BK12_55_L       _PK_L_(0x12, 0x55)
#define  REG_TC_SC_SCMI_BK12_55_H       _PK_H_(0x12, 0x55)
#define  REG_TC_SC_SCMI_BK12_56_L       _PK_L_(0x12, 0x56)
#define  REG_TC_SC_SCMI_BK12_56_H       _PK_H_(0x12, 0x56)
#define  REG_TC_SC_SCMI_BK12_57_L       _PK_L_(0x12, 0x57)
#define  REG_TC_SC_SCMI_BK12_57_H       _PK_H_(0x12, 0x57)
#define  REG_TC_SC_SCMI_BK12_58_L       _PK_L_(0x12, 0x58)
#define  REG_TC_SC_SCMI_BK12_58_H       _PK_H_(0x12, 0x58)
#define  REG_TC_SC_SCMI_BK12_59_L       _PK_L_(0x12, 0x59)
#define  REG_TC_SC_SCMI_BK12_59_H       _PK_H_(0x12, 0x59)
#define  REG_TC_SC_SCMI_BK12_5A_L       _PK_L_(0x12, 0x5A)
#define  REG_TC_SC_SCMI_BK12_5A_H       _PK_H_(0x12, 0x5A)
#define  REG_TC_SC_SCMI_BK12_5B_L       _PK_L_(0x12, 0x5B)
#define  REG_TC_SC_SCMI_BK12_5B_H       _PK_H_(0x12, 0x5B)
#define  REG_TC_SC_SCMI_BK12_5C_L       _PK_L_(0x12, 0x5C)
#define  REG_TC_SC_SCMI_BK12_5C_H       _PK_H_(0x12, 0x5C)
#define  REG_TC_SC_SCMI_BK12_5D_L       _PK_L_(0x12, 0x5D)
#define  REG_TC_SC_SCMI_BK12_5D_H       _PK_H_(0x12, 0x5D)
#define  REG_TC_SC_SCMI_BK12_5E_L       _PK_L_(0x12, 0x5E)
#define  REG_TC_SC_SCMI_BK12_5E_H       _PK_H_(0x12, 0x5E)
#define  REG_TC_SC_SCMI_BK12_5F_L       _PK_L_(0x12, 0x5F)
#define  REG_TC_SC_SCMI_BK12_5F_H       _PK_H_(0x12, 0x5F)
#define  REG_TC_SC_SCMI_BK12_60_L       _PK_L_(0x12, 0x60)
#define  REG_TC_SC_SCMI_BK12_60_H       _PK_H_(0x12, 0x60)
#define  REG_TC_SC_SCMI_BK12_61_L       _PK_L_(0x12, 0x61)
#define  REG_TC_SC_SCMI_BK12_61_H       _PK_H_(0x12, 0x61)
#define  REG_TC_SC_SCMI_BK12_62_L       _PK_L_(0x12, 0x62)
#define  REG_TC_SC_SCMI_BK12_62_H       _PK_H_(0x12, 0x62)
#define  REG_TC_SC_SCMI_BK12_63_L       _PK_L_(0x12, 0x63)
#define  REG_TC_SC_SCMI_BK12_63_H       _PK_H_(0x12, 0x63)
#define  REG_TC_SC_SCMI_BK12_64_L       _PK_L_(0x12, 0x64)
#define  REG_TC_SC_SCMI_BK12_64_H       _PK_H_(0x12, 0x64)
#define  REG_TC_SC_SCMI_BK12_65_L       _PK_L_(0x12, 0x65)
#define  REG_TC_SC_SCMI_BK12_65_H       _PK_H_(0x12, 0x65)
#define  REG_TC_SC_SCMI_BK12_66_L       _PK_L_(0x12, 0x66)
#define  REG_TC_SC_SCMI_BK12_66_H       _PK_H_(0x12, 0x66)
#define  REG_TC_SC_SCMI_BK12_67_L       _PK_L_(0x12, 0x67)
#define  REG_TC_SC_SCMI_BK12_67_H       _PK_H_(0x12, 0x67)
#define  REG_TC_SC_SCMI_BK12_68_L       _PK_L_(0x12, 0x68)
#define  REG_TC_SC_SCMI_BK12_68_H       _PK_H_(0x12, 0x68)
#define  REG_TC_SC_SCMI_BK12_69_L       _PK_L_(0x12, 0x69)
#define  REG_TC_SC_SCMI_BK12_69_H       _PK_H_(0x12, 0x69)
#define  REG_TC_SC_SCMI_BK12_6A_L       _PK_L_(0x12, 0x6A)
#define  REG_TC_SC_SCMI_BK12_6A_H       _PK_H_(0x12, 0x6A)
#define  REG_TC_SC_SCMI_BK12_6B_L       _PK_L_(0x12, 0x6B)
#define  REG_TC_SC_SCMI_BK12_6B_H       _PK_H_(0x12, 0x6B)
#define  REG_TC_SC_SCMI_BK12_6C_L       _PK_L_(0x12, 0x6C)
#define  REG_TC_SC_SCMI_BK12_6C_H       _PK_H_(0x12, 0x6C)
#define  REG_TC_SC_SCMI_BK12_6D_L       _PK_L_(0x12, 0x6D)
#define  REG_TC_SC_SCMI_BK12_6D_H       _PK_H_(0x12, 0x6D)
#define  REG_TC_SC_SCMI_BK12_6E_L       _PK_L_(0x12, 0x6E)
#define  REG_TC_SC_SCMI_BK12_6E_H       _PK_H_(0x12, 0x6E)
#define  REG_TC_SC_SCMI_BK12_6F_L       _PK_L_(0x12, 0x6F)
#define  REG_TC_SC_SCMI_BK12_6F_H       _PK_H_(0x12, 0x6F)
#define  REG_TC_SC_SCMI_BK12_70_L       _PK_L_(0x12, 0x70)
#define  REG_TC_SC_SCMI_BK12_70_H       _PK_H_(0x12, 0x70)
#define  REG_TC_SC_SCMI_BK12_71_L       _PK_L_(0x12, 0x71)
#define  REG_TC_SC_SCMI_BK12_71_H       _PK_H_(0x12, 0x71)
#define  REG_TC_SC_SCMI_BK12_72_L       _PK_L_(0x12, 0x72)
#define  REG_TC_SC_SCMI_BK12_72_H       _PK_H_(0x12, 0x72)
#define  REG_TC_SC_SCMI_BK12_73_L       _PK_L_(0x12, 0x73)
#define  REG_TC_SC_SCMI_BK12_73_H       _PK_H_(0x12, 0x73)
#define  REG_TC_SC_SCMI_BK12_74_L       _PK_L_(0x12, 0x74)
#define  REG_TC_SC_SCMI_BK12_74_H       _PK_H_(0x12, 0x74)
#define  REG_TC_SC_SCMI_BK12_75_L       _PK_L_(0x12, 0x75)
#define  REG_TC_SC_SCMI_BK12_75_H       _PK_H_(0x12, 0x75)
#define  REG_TC_SC_SCMI_BK12_76_L       _PK_L_(0x12, 0x76)
#define  REG_TC_SC_SCMI_BK12_76_H       _PK_H_(0x12, 0x76)
#define  REG_TC_SC_SCMI_BK12_77_L       _PK_L_(0x12, 0x77)
#define  REG_TC_SC_SCMI_BK12_77_H       _PK_H_(0x12, 0x77)
#define  REG_TC_SC_SCMI_BK12_78_L       _PK_L_(0x12, 0x78)
#define  REG_TC_SC_SCMI_BK12_78_H       _PK_H_(0x12, 0x78)
#define  REG_TC_SC_SCMI_BK12_79_L       _PK_L_(0x12, 0x79)
#define  REG_TC_SC_SCMI_BK12_79_H       _PK_H_(0x12, 0x79)
#define  REG_TC_SC_SCMI_BK12_7A_L       _PK_L_(0x12, 0x7A)
#define  REG_TC_SC_SCMI_BK12_7A_H       _PK_H_(0x12, 0x7A)
#define  REG_TC_SC_SCMI_BK12_7B_L       _PK_L_(0x12, 0x7B)
#define  REG_TC_SC_SCMI_BK12_7B_H       _PK_H_(0x12, 0x7B)
#define  REG_TC_SC_SCMI_BK12_7C_L       _PK_L_(0x12, 0x7C)
#define  REG_TC_SC_SCMI_BK12_7C_H       _PK_H_(0x12, 0x7C)
#define  REG_TC_SC_SCMI_BK12_7D_L       _PK_L_(0x12, 0x7D)
#define  REG_TC_SC_SCMI_BK12_7D_H       _PK_H_(0x12, 0x7D)
#define  REG_TC_SC_SCMI_BK12_7E_L       _PK_L_(0x12, 0x7E)
#define  REG_TC_SC_SCMI_BK12_7E_H       _PK_H_(0x12, 0x7E)
#define  REG_TC_SC_SCMI_BK12_7F_L       _PK_L_(0x12, 0x7F)
#define  REG_TC_SC_SCMI_BK12_7F_H       _PK_H_(0x12, 0x7F)

#define  REG_TC_SC1_VOP_BK90_00_L       _PK_L_(0x90, 0x00)
#define  REG_TC_SC1_VOP_BK90_00_H       _PK_H_(0x90, 0x00)
#define  REG_TC_SC1_VOP_BK90_01_L       _PK_L_(0x90, 0x01)
#define  REG_TC_SC1_VOP_BK90_01_H       _PK_H_(0x90, 0x01)
#define  REG_TC_SC1_VOP_BK90_02_L       _PK_L_(0x90, 0x02)
#define  REG_TC_SC1_VOP_BK90_02_H       _PK_H_(0x90, 0x02)
#define  REG_TC_SC1_VOP_BK90_03_L       _PK_L_(0x90, 0x03)
#define  REG_TC_SC1_VOP_BK90_03_H       _PK_H_(0x90, 0x03)
#define  REG_TC_SC1_VOP_BK90_04_L       _PK_L_(0x90, 0x04)
#define  REG_TC_SC1_VOP_BK90_04_H       _PK_H_(0x90, 0x04)
#define  REG_TC_SC1_VOP_BK90_05_L       _PK_L_(0x90, 0x05)
#define  REG_TC_SC1_VOP_BK90_05_H       _PK_H_(0x90, 0x05)
#define  REG_TC_SC1_VOP_BK90_06_L       _PK_L_(0x90, 0x06)
#define  REG_TC_SC1_VOP_BK90_06_H       _PK_H_(0x90, 0x06)
#define  REG_TC_SC1_VOP_BK90_07_L       _PK_L_(0x90, 0x07)
#define  REG_TC_SC1_VOP_BK90_07_H       _PK_H_(0x90, 0x07)
#define  REG_TC_SC1_VOP_BK90_08_L       _PK_L_(0x90, 0x08)
#define  REG_TC_SC1_VOP_BK90_08_H       _PK_H_(0x90, 0x08)
#define  REG_TC_SC1_VOP_BK90_09_L       _PK_L_(0x90, 0x09)
#define  REG_TC_SC1_VOP_BK90_09_H       _PK_H_(0x90, 0x09)
#define  REG_TC_SC1_VOP_BK90_0A_L       _PK_L_(0x90, 0x0A)
#define  REG_TC_SC1_VOP_BK90_0A_H       _PK_H_(0x90, 0x0A)
#define  REG_TC_SC1_VOP_BK90_0B_L       _PK_L_(0x90, 0x0B)
#define  REG_TC_SC1_VOP_BK90_0B_H       _PK_H_(0x90, 0x0B)
#define  REG_TC_SC1_VOP_BK90_0C_L       _PK_L_(0x90, 0x0C)
#define  REG_TC_SC1_VOP_BK90_0C_H       _PK_H_(0x90, 0x0C)
#define  REG_TC_SC1_VOP_BK90_0D_L       _PK_L_(0x90, 0x0D)
#define  REG_TC_SC1_VOP_BK90_0D_H       _PK_H_(0x90, 0x0D)
#define  REG_TC_SC1_VOP_BK90_0E_L       _PK_L_(0x90, 0x0E)
#define  REG_TC_SC1_VOP_BK90_0E_H       _PK_H_(0x90, 0x0E)
#define  REG_TC_SC1_VOP_BK90_0F_L       _PK_L_(0x90, 0x0F)
#define  REG_TC_SC1_VOP_BK90_0F_H       _PK_H_(0x90, 0x0F)
#define  REG_TC_SC1_VOP_BK90_10_L       _PK_L_(0x90, 0x10)
#define  REG_TC_SC1_VOP_BK90_10_H       _PK_H_(0x90, 0x10)
#define  REG_TC_SC1_VOP_BK90_11_L       _PK_L_(0x90, 0x11)
#define  REG_TC_SC1_VOP_BK90_11_H       _PK_H_(0x90, 0x11)
#define  REG_TC_SC1_VOP_BK90_12_L       _PK_L_(0x90, 0x12)
#define  REG_TC_SC1_VOP_BK90_12_H       _PK_H_(0x90, 0x12)
#define  REG_TC_SC1_VOP_BK90_13_L       _PK_L_(0x90, 0x13)
#define  REG_TC_SC1_VOP_BK90_13_H       _PK_H_(0x90, 0x13)
#define  REG_TC_SC1_VOP_BK90_14_L       _PK_L_(0x90, 0x14)
#define  REG_TC_SC1_VOP_BK90_14_H       _PK_H_(0x90, 0x14)
#define  REG_TC_SC1_VOP_BK90_15_L       _PK_L_(0x90, 0x15)
#define  REG_TC_SC1_VOP_BK90_15_H       _PK_H_(0x90, 0x15)
#define  REG_TC_SC1_VOP_BK90_16_L       _PK_L_(0x90, 0x16)
#define  REG_TC_SC1_VOP_BK90_16_H       _PK_H_(0x90, 0x16)
#define  REG_TC_SC1_VOP_BK90_17_L       _PK_L_(0x90, 0x17)
#define  REG_TC_SC1_VOP_BK90_17_H       _PK_H_(0x90, 0x17)
#define  REG_TC_SC1_VOP_BK90_18_L       _PK_L_(0x90, 0x18)
#define  REG_TC_SC1_VOP_BK90_18_H       _PK_H_(0x90, 0x18)
#define  REG_TC_SC1_VOP_BK90_19_L       _PK_L_(0x90, 0x19)
#define  REG_TC_SC1_VOP_BK90_19_H       _PK_H_(0x90, 0x19)
#define  REG_TC_SC1_VOP_BK90_1A_L       _PK_L_(0x90, 0x1A)
#define  REG_TC_SC1_VOP_BK90_1A_H       _PK_H_(0x90, 0x1A)
#define  REG_TC_SC1_VOP_BK90_1B_L       _PK_L_(0x90, 0x1B)
#define  REG_TC_SC1_VOP_BK90_1B_H       _PK_H_(0x90, 0x1B)
#define  REG_TC_SC1_VOP_BK90_1C_L       _PK_L_(0x90, 0x1C)
#define  REG_TC_SC1_VOP_BK90_1C_H       _PK_H_(0x90, 0x1C)
#define  REG_TC_SC1_VOP_BK90_1D_L       _PK_L_(0x90, 0x1D)
#define  REG_TC_SC1_VOP_BK90_1D_H       _PK_H_(0x90, 0x1D)
#define  REG_TC_SC1_VOP_BK90_1E_L       _PK_L_(0x90, 0x1E)
#define  REG_TC_SC1_VOP_BK90_1E_H       _PK_H_(0x90, 0x1E)
#define  REG_TC_SC1_VOP_BK90_1F_L       _PK_L_(0x90, 0x1F)
#define  REG_TC_SC1_VOP_BK90_1F_H       _PK_H_(0x90, 0x1F)
#define  REG_TC_SC1_VOP_BK90_20_L       _PK_L_(0x90, 0x20)
#define  REG_TC_SC1_VOP_BK90_20_H       _PK_H_(0x90, 0x20)
#define  REG_TC_SC1_VOP_BK90_21_L       _PK_L_(0x90, 0x21)
#define  REG_TC_SC1_VOP_BK90_21_H       _PK_H_(0x90, 0x21)
#define  REG_TC_SC1_VOP_BK90_22_L       _PK_L_(0x90, 0x22)
#define  REG_TC_SC1_VOP_BK90_22_H       _PK_H_(0x90, 0x22)
#define  REG_TC_SC1_VOP_BK90_23_L       _PK_L_(0x90, 0x23)
#define  REG_TC_SC1_VOP_BK90_23_H       _PK_H_(0x90, 0x23)
#define  REG_TC_SC1_VOP_BK90_24_L       _PK_L_(0x90, 0x24)
#define  REG_TC_SC1_VOP_BK90_24_H       _PK_H_(0x90, 0x24)
#define  REG_TC_SC1_VOP_BK90_25_L       _PK_L_(0x90, 0x25)
#define  REG_TC_SC1_VOP_BK90_25_H       _PK_H_(0x90, 0x25)
#define  REG_TC_SC1_VOP_BK90_26_L       _PK_L_(0x90, 0x26)
#define  REG_TC_SC1_VOP_BK90_26_H       _PK_H_(0x90, 0x26)
#define  REG_TC_SC1_VOP_BK90_27_L       _PK_L_(0x90, 0x27)
#define  REG_TC_SC1_VOP_BK90_27_H       _PK_H_(0x90, 0x27)
#define  REG_TC_SC1_VOP_BK90_28_L       _PK_L_(0x90, 0x28)
#define  REG_TC_SC1_VOP_BK90_28_H       _PK_H_(0x90, 0x28)
#define  REG_TC_SC1_VOP_BK90_29_L       _PK_L_(0x90, 0x29)
#define  REG_TC_SC1_VOP_BK90_29_H       _PK_H_(0x90, 0x29)
#define  REG_TC_SC1_VOP_BK90_2A_L       _PK_L_(0x90, 0x2A)
#define  REG_TC_SC1_VOP_BK90_2A_H       _PK_H_(0x90, 0x2A)
#define  REG_TC_SC1_VOP_BK90_2B_L       _PK_L_(0x90, 0x2B)
#define  REG_TC_SC1_VOP_BK90_2B_H       _PK_H_(0x90, 0x2B)
#define  REG_TC_SC1_VOP_BK90_2C_L       _PK_L_(0x90, 0x2C)
#define  REG_TC_SC1_VOP_BK90_2C_H       _PK_H_(0x90, 0x2C)
#define  REG_TC_SC1_VOP_BK90_2D_L       _PK_L_(0x90, 0x2D)
#define  REG_TC_SC1_VOP_BK90_2D_H       _PK_H_(0x90, 0x2D)
#define  REG_TC_SC1_VOP_BK90_2E_L       _PK_L_(0x90, 0x2E)
#define  REG_TC_SC1_VOP_BK90_2E_H       _PK_H_(0x90, 0x2E)
#define  REG_TC_SC1_VOP_BK90_2F_L       _PK_L_(0x90, 0x2F)
#define  REG_TC_SC1_VOP_BK90_2F_H       _PK_H_(0x90, 0x2F)
#define  REG_TC_SC1_VOP_BK90_30_L       _PK_L_(0x90, 0x30)
#define  REG_TC_SC1_VOP_BK90_30_H       _PK_H_(0x90, 0x30)
#define  REG_TC_SC1_VOP_BK90_31_L       _PK_L_(0x90, 0x31)
#define  REG_TC_SC1_VOP_BK90_31_H       _PK_H_(0x90, 0x31)
#define  REG_TC_SC1_VOP_BK90_32_L       _PK_L_(0x90, 0x32)
#define  REG_TC_SC1_VOP_BK90_32_H       _PK_H_(0x90, 0x32)
#define  REG_TC_SC1_VOP_BK90_33_L       _PK_L_(0x90, 0x33)
#define  REG_TC_SC1_VOP_BK90_33_H       _PK_H_(0x90, 0x33)
#define  REG_TC_SC1_VOP_BK90_34_L       _PK_L_(0x90, 0x34)
#define  REG_TC_SC1_VOP_BK90_34_H       _PK_H_(0x90, 0x34)
#define  REG_TC_SC1_VOP_BK90_35_L       _PK_L_(0x90, 0x35)
#define  REG_TC_SC1_VOP_BK90_35_H       _PK_H_(0x90, 0x35)
#define  REG_TC_SC1_VOP_BK90_36_L       _PK_L_(0x90, 0x36)
#define  REG_TC_SC1_VOP_BK90_36_H       _PK_H_(0x90, 0x36)
#define  REG_TC_SC1_VOP_BK90_37_L       _PK_L_(0x90, 0x37)
#define  REG_TC_SC1_VOP_BK90_37_H       _PK_H_(0x90, 0x37)
#define  REG_TC_SC1_VOP_BK90_38_L       _PK_L_(0x90, 0x38)
#define  REG_TC_SC1_VOP_BK90_38_H       _PK_H_(0x90, 0x38)
#define  REG_TC_SC1_VOP_BK90_39_L       _PK_L_(0x90, 0x39)
#define  REG_TC_SC1_VOP_BK90_39_H       _PK_H_(0x90, 0x39)
#define  REG_TC_SC1_VOP_BK90_3A_L       _PK_L_(0x90, 0x3A)
#define  REG_TC_SC1_VOP_BK90_3A_H       _PK_H_(0x90, 0x3A)
#define  REG_TC_SC1_VOP_BK90_3B_L       _PK_L_(0x90, 0x3B)
#define  REG_TC_SC1_VOP_BK90_3B_H       _PK_H_(0x90, 0x3B)
#define  REG_TC_SC1_VOP_BK90_3C_L       _PK_L_(0x90, 0x3C)
#define  REG_TC_SC1_VOP_BK90_3C_H       _PK_H_(0x90, 0x3C)
#define  REG_TC_SC1_VOP_BK90_3D_L       _PK_L_(0x90, 0x3D)
#define  REG_TC_SC1_VOP_BK90_3D_H       _PK_H_(0x90, 0x3D)
#define  REG_TC_SC1_VOP_BK90_3E_L       _PK_L_(0x90, 0x3E)
#define  REG_TC_SC1_VOP_BK90_3E_H       _PK_H_(0x90, 0x3E)
#define  REG_TC_SC1_VOP_BK90_3F_L       _PK_L_(0x90, 0x3F)
#define  REG_TC_SC1_VOP_BK90_3F_H       _PK_H_(0x90, 0x3F)
#define  REG_TC_SC1_VOP_BK90_40_L       _PK_L_(0x90, 0x40)
#define  REG_TC_SC1_VOP_BK90_40_H       _PK_H_(0x90, 0x40)
#define  REG_TC_SC1_VOP_BK90_41_L       _PK_L_(0x90, 0x41)
#define  REG_TC_SC1_VOP_BK90_41_H       _PK_H_(0x90, 0x41)
#define  REG_TC_SC1_VOP_BK90_42_L       _PK_L_(0x90, 0x42)
#define  REG_TC_SC1_VOP_BK90_42_H       _PK_H_(0x90, 0x42)
#define  REG_TC_SC1_VOP_BK90_43_L       _PK_L_(0x90, 0x43)
#define  REG_TC_SC1_VOP_BK90_43_H       _PK_H_(0x90, 0x43)
#define  REG_TC_SC1_VOP_BK90_44_L       _PK_L_(0x90, 0x44)
#define  REG_TC_SC1_VOP_BK90_44_H       _PK_H_(0x90, 0x44)
#define  REG_TC_SC1_VOP_BK90_45_L       _PK_L_(0x90, 0x45)
#define  REG_TC_SC1_VOP_BK90_45_H       _PK_H_(0x90, 0x45)
#define  REG_TC_SC1_VOP_BK90_46_L       _PK_L_(0x90, 0x46)
#define  REG_TC_SC1_VOP_BK90_46_H       _PK_H_(0x90, 0x46)
#define  REG_TC_SC1_VOP_BK90_47_L       _PK_L_(0x90, 0x47)
#define  REG_TC_SC1_VOP_BK90_47_H       _PK_H_(0x90, 0x47)
#define  REG_TC_SC1_VOP_BK90_48_L       _PK_L_(0x90, 0x48)
#define  REG_TC_SC1_VOP_BK90_48_H       _PK_H_(0x90, 0x48)
#define  REG_TC_SC1_VOP_BK90_49_L       _PK_L_(0x90, 0x49)
#define  REG_TC_SC1_VOP_BK90_49_H       _PK_H_(0x90, 0x49)
#define  REG_TC_SC1_VOP_BK90_4A_L       _PK_L_(0x90, 0x4A)
#define  REG_TC_SC1_VOP_BK90_4A_H       _PK_H_(0x90, 0x4A)
#define  REG_TC_SC1_VOP_BK90_4B_L       _PK_L_(0x90, 0x4B)
#define  REG_TC_SC1_VOP_BK90_4B_H       _PK_H_(0x90, 0x4B)
#define  REG_TC_SC1_VOP_BK90_4C_L       _PK_L_(0x90, 0x4C)
#define  REG_TC_SC1_VOP_BK90_4C_H       _PK_H_(0x90, 0x4C)
#define  REG_TC_SC1_VOP_BK90_4D_L       _PK_L_(0x90, 0x4D)
#define  REG_TC_SC1_VOP_BK90_4D_H       _PK_H_(0x90, 0x4D)
#define  REG_TC_SC1_VOP_BK90_4E_L       _PK_L_(0x90, 0x4E)
#define  REG_TC_SC1_VOP_BK90_4E_H       _PK_H_(0x90, 0x4E)
#define  REG_TC_SC1_VOP_BK90_4F_L       _PK_L_(0x90, 0x4F)
#define  REG_TC_SC1_VOP_BK90_4F_H       _PK_H_(0x90, 0x4F)
#define  REG_TC_SC1_VOP_BK90_50_L       _PK_L_(0x90, 0x50)
#define  REG_TC_SC1_VOP_BK90_50_H       _PK_H_(0x90, 0x50)
#define  REG_TC_SC1_VOP_BK90_51_L       _PK_L_(0x90, 0x51)
#define  REG_TC_SC1_VOP_BK90_51_H       _PK_H_(0x90, 0x51)
#define  REG_TC_SC1_VOP_BK90_52_L       _PK_L_(0x90, 0x52)
#define  REG_TC_SC1_VOP_BK90_52_H       _PK_H_(0x90, 0x52)
#define  REG_TC_SC1_VOP_BK90_53_L       _PK_L_(0x90, 0x53)
#define  REG_TC_SC1_VOP_BK90_53_H       _PK_H_(0x90, 0x53)
#define  REG_TC_SC1_VOP_BK90_54_L       _PK_L_(0x90, 0x54)
#define  REG_TC_SC1_VOP_BK90_54_H       _PK_H_(0x90, 0x54)
#define  REG_TC_SC1_VOP_BK90_55_L       _PK_L_(0x90, 0x55)
#define  REG_TC_SC1_VOP_BK90_55_H       _PK_H_(0x90, 0x55)
#define  REG_TC_SC1_VOP_BK90_56_L       _PK_L_(0x90, 0x56)
#define  REG_TC_SC1_VOP_BK90_56_H       _PK_H_(0x90, 0x56)
#define  REG_TC_SC1_VOP_BK90_57_L       _PK_L_(0x90, 0x57)
#define  REG_TC_SC1_VOP_BK90_57_H       _PK_H_(0x90, 0x57)
#define  REG_TC_SC1_VOP_BK90_58_L       _PK_L_(0x90, 0x58)
#define  REG_TC_SC1_VOP_BK90_58_H       _PK_H_(0x90, 0x58)
#define  REG_TC_SC1_VOP_BK90_59_L       _PK_L_(0x90, 0x59)
#define  REG_TC_SC1_VOP_BK90_59_H       _PK_H_(0x90, 0x59)
#define  REG_TC_SC1_VOP_BK90_5A_L       _PK_L_(0x90, 0x5A)
#define  REG_TC_SC1_VOP_BK90_5A_H       _PK_H_(0x90, 0x5A)
#define  REG_TC_SC1_VOP_BK90_5B_L       _PK_L_(0x90, 0x5B)
#define  REG_TC_SC1_VOP_BK90_5B_H       _PK_H_(0x90, 0x5B)
#define  REG_TC_SC1_VOP_BK90_5C_L       _PK_L_(0x90, 0x5C)
#define  REG_TC_SC1_VOP_BK90_5C_H       _PK_H_(0x90, 0x5C)
#define  REG_TC_SC1_VOP_BK90_5D_L       _PK_L_(0x90, 0x5D)
#define  REG_TC_SC1_VOP_BK90_5D_H       _PK_H_(0x90, 0x5D)
#define  REG_TC_SC1_VOP_BK90_5E_L       _PK_L_(0x90, 0x5E)
#define  REG_TC_SC1_VOP_BK90_5E_H       _PK_H_(0x90, 0x5E)
#define  REG_TC_SC1_VOP_BK90_5F_L       _PK_L_(0x90, 0x5F)
#define  REG_TC_SC1_VOP_BK90_5F_H       _PK_H_(0x90, 0x5F)
#define  REG_TC_SC1_VOP_BK90_60_L       _PK_L_(0x90, 0x60)
#define  REG_TC_SC1_VOP_BK90_60_H       _PK_H_(0x90, 0x60)
#define  REG_TC_SC1_VOP_BK90_61_L       _PK_L_(0x90, 0x61)
#define  REG_TC_SC1_VOP_BK90_61_H       _PK_H_(0x90, 0x61)
#define  REG_TC_SC1_VOP_BK90_62_L       _PK_L_(0x90, 0x62)
#define  REG_TC_SC1_VOP_BK90_62_H       _PK_H_(0x90, 0x62)
#define  REG_TC_SC1_VOP_BK90_63_L       _PK_L_(0x90, 0x63)
#define  REG_TC_SC1_VOP_BK90_63_H       _PK_H_(0x90, 0x63)
#define  REG_TC_SC1_VOP_BK90_64_L       _PK_L_(0x90, 0x64)
#define  REG_TC_SC1_VOP_BK90_64_H       _PK_H_(0x90, 0x64)
#define  REG_TC_SC1_VOP_BK90_65_L       _PK_L_(0x90, 0x65)
#define  REG_TC_SC1_VOP_BK90_65_H       _PK_H_(0x90, 0x65)
#define  REG_TC_SC1_VOP_BK90_66_L       _PK_L_(0x90, 0x66)
#define  REG_TC_SC1_VOP_BK90_66_H       _PK_H_(0x90, 0x66)
#define  REG_TC_SC1_VOP_BK90_67_L       _PK_L_(0x90, 0x67)
#define  REG_TC_SC1_VOP_BK90_67_H       _PK_H_(0x90, 0x67)
#define  REG_TC_SC1_VOP_BK90_68_L       _PK_L_(0x90, 0x68)
#define  REG_TC_SC1_VOP_BK90_68_H       _PK_H_(0x90, 0x68)
#define  REG_TC_SC1_VOP_BK90_69_L       _PK_L_(0x90, 0x69)
#define  REG_TC_SC1_VOP_BK90_69_H       _PK_H_(0x90, 0x69)
#define  REG_TC_SC1_VOP_BK90_6A_L       _PK_L_(0x90, 0x6A)
#define  REG_TC_SC1_VOP_BK90_6A_H       _PK_H_(0x90, 0x6A)
#define  REG_TC_SC1_VOP_BK90_6B_L       _PK_L_(0x90, 0x6B)
#define  REG_TC_SC1_VOP_BK90_6B_H       _PK_H_(0x90, 0x6B)
#define  REG_TC_SC1_VOP_BK90_6C_L       _PK_L_(0x90, 0x6C)
#define  REG_TC_SC1_VOP_BK90_6C_H       _PK_H_(0x90, 0x6C)
#define  REG_TC_SC1_VOP_BK90_6D_L       _PK_L_(0x90, 0x6D)
#define  REG_TC_SC1_VOP_BK90_6D_H       _PK_H_(0x90, 0x6D)
#define  REG_TC_SC1_VOP_BK90_6E_L       _PK_L_(0x90, 0x6E)
#define  REG_TC_SC1_VOP_BK90_6E_H       _PK_H_(0x90, 0x6E)
#define  REG_TC_SC1_VOP_BK90_6F_L       _PK_L_(0x90, 0x6F)
#define  REG_TC_SC1_VOP_BK90_6F_H       _PK_H_(0x90, 0x6F)
#define  REG_TC_SC1_VOP_BK90_70_L       _PK_L_(0x90, 0x70)
#define  REG_TC_SC1_VOP_BK90_70_H       _PK_H_(0x90, 0x70)
#define  REG_TC_SC1_VOP_BK90_71_L       _PK_L_(0x90, 0x71)
#define  REG_TC_SC1_VOP_BK90_71_H       _PK_H_(0x90, 0x71)
#define  REG_TC_SC1_VOP_BK90_72_L       _PK_L_(0x90, 0x72)
#define  REG_TC_SC1_VOP_BK90_72_H       _PK_H_(0x90, 0x72)
#define  REG_TC_SC1_VOP_BK90_73_L       _PK_L_(0x90, 0x73)
#define  REG_TC_SC1_VOP_BK90_73_H       _PK_H_(0x90, 0x73)
#define  REG_TC_SC1_VOP_BK90_74_L       _PK_L_(0x90, 0x74)
#define  REG_TC_SC1_VOP_BK90_74_H       _PK_H_(0x90, 0x74)
#define  REG_TC_SC1_VOP_BK90_75_L       _PK_L_(0x90, 0x75)
#define  REG_TC_SC1_VOP_BK90_75_H       _PK_H_(0x90, 0x75)
#define  REG_TC_SC1_VOP_BK90_76_L       _PK_L_(0x90, 0x76)
#define  REG_TC_SC1_VOP_BK90_76_H       _PK_H_(0x90, 0x76)
#define  REG_TC_SC1_VOP_BK90_77_L       _PK_L_(0x90, 0x77)
#define  REG_TC_SC1_VOP_BK90_77_H       _PK_H_(0x90, 0x77)
#define  REG_TC_SC1_VOP_BK90_78_L       _PK_L_(0x90, 0x78)
#define  REG_TC_SC1_VOP_BK90_78_H       _PK_H_(0x90, 0x78)
#define  REG_TC_SC1_VOP_BK90_79_L       _PK_L_(0x90, 0x79)
#define  REG_TC_SC1_VOP_BK90_79_H       _PK_H_(0x90, 0x79)
#define  REG_TC_SC1_VOP_BK90_7A_L       _PK_L_(0x90, 0x7A)
#define  REG_TC_SC1_VOP_BK90_7A_H       _PK_H_(0x90, 0x7A)
#define  REG_TC_SC1_VOP_BK90_7B_L       _PK_L_(0x90, 0x7B)
#define  REG_TC_SC1_VOP_BK90_7B_H       _PK_H_(0x90, 0x7B)
#define  REG_TC_SC1_VOP_BK90_7C_L       _PK_L_(0x90, 0x7C)
#define  REG_TC_SC1_VOP_BK90_7C_H       _PK_H_(0x90, 0x7C)
#define  REG_TC_SC1_VOP_BK90_7D_L       _PK_L_(0x90, 0x7D)
#define  REG_TC_SC1_VOP_BK90_7D_H       _PK_H_(0x90, 0x7D)
#define  REG_TC_SC1_VOP_BK90_7E_L       _PK_L_(0x90, 0x7E)
#define  REG_TC_SC1_VOP_BK90_7E_H       _PK_H_(0x90, 0x7E)
#define  REG_TC_SC1_VOP_BK90_7F_L       _PK_L_(0x90, 0x7F)
#define  REG_TC_SC1_VOP_BK90_7F_H       _PK_H_(0x90, 0x7F)

#define  REG_TC_SC1_OP1_BKA0_00_L       _PK_L_(0xA0, 0x00)
#define  REG_TC_SC1_OP1_BKA0_00_H       _PK_H_(0xA0, 0x00)
#define  REG_TC_SC1_OP1_BKA0_01_L       _PK_L_(0xA0, 0x01)
#define  REG_TC_SC1_OP1_BKA0_01_H       _PK_H_(0xA0, 0x01)
#define  REG_TC_SC1_OP1_BKA0_02_L       _PK_L_(0xA0, 0x02)
#define  REG_TC_SC1_OP1_BKA0_02_H       _PK_H_(0xA0, 0x02)
#define  REG_TC_SC1_OP1_BKA0_03_L       _PK_L_(0xA0, 0x03)
#define  REG_TC_SC1_OP1_BKA0_03_H       _PK_H_(0xA0, 0x03)
#define  REG_TC_SC1_OP1_BKA0_04_L       _PK_L_(0xA0, 0x04)
#define  REG_TC_SC1_OP1_BKA0_04_H       _PK_H_(0xA0, 0x04)
#define  REG_TC_SC1_OP1_BKA0_05_L       _PK_L_(0xA0, 0x05)
#define  REG_TC_SC1_OP1_BKA0_05_H       _PK_H_(0xA0, 0x05)
#define  REG_TC_SC1_OP1_BKA0_06_L       _PK_L_(0xA0, 0x06)
#define  REG_TC_SC1_OP1_BKA0_06_H       _PK_H_(0xA0, 0x06)
#define  REG_TC_SC1_OP1_BKA0_07_L       _PK_L_(0xA0, 0x07)
#define  REG_TC_SC1_OP1_BKA0_07_H       _PK_H_(0xA0, 0x07)
#define  REG_TC_SC1_OP1_BKA0_08_L       _PK_L_(0xA0, 0x08)
#define  REG_TC_SC1_OP1_BKA0_08_H       _PK_H_(0xA0, 0x08)
#define  REG_TC_SC1_OP1_BKA0_09_L       _PK_L_(0xA0, 0x09)
#define  REG_TC_SC1_OP1_BKA0_09_H       _PK_H_(0xA0, 0x09)
#define  REG_TC_SC1_OP1_BKA0_0A_L       _PK_L_(0xA0, 0x0A)
#define  REG_TC_SC1_OP1_BKA0_0A_H       _PK_H_(0xA0, 0x0A)
#define  REG_TC_SC1_OP1_BKA0_0B_L       _PK_L_(0xA0, 0x0B)
#define  REG_TC_SC1_OP1_BKA0_0B_H       _PK_H_(0xA0, 0x0B)
#define  REG_TC_SC1_OP1_BKA0_0C_L       _PK_L_(0xA0, 0x0C)
#define  REG_TC_SC1_OP1_BKA0_0C_H       _PK_H_(0xA0, 0x0C)
#define  REG_TC_SC1_OP1_BKA0_0D_L       _PK_L_(0xA0, 0x0D)
#define  REG_TC_SC1_OP1_BKA0_0D_H       _PK_H_(0xA0, 0x0D)
#define  REG_TC_SC1_OP1_BKA0_0E_L       _PK_L_(0xA0, 0x0E)
#define  REG_TC_SC1_OP1_BKA0_0E_H       _PK_H_(0xA0, 0x0E)
#define  REG_TC_SC1_OP1_BKA0_0F_L       _PK_L_(0xA0, 0x0F)
#define  REG_TC_SC1_OP1_BKA0_0F_H       _PK_H_(0xA0, 0x0F)
#define  REG_TC_SC1_OP1_BKA0_10_L       _PK_L_(0xA0, 0x10)
#define  REG_TC_SC1_OP1_BKA0_10_H       _PK_H_(0xA0, 0x10)
#define  REG_TC_SC1_OP1_BKA0_11_L       _PK_L_(0xA0, 0x11)
#define  REG_TC_SC1_OP1_BKA0_11_H       _PK_H_(0xA0, 0x11)
#define  REG_TC_SC1_OP1_BKA0_12_L       _PK_L_(0xA0, 0x12)
#define  REG_TC_SC1_OP1_BKA0_12_H       _PK_H_(0xA0, 0x12)
#define  REG_TC_SC1_OP1_BKA0_13_L       _PK_L_(0xA0, 0x13)
#define  REG_TC_SC1_OP1_BKA0_13_H       _PK_H_(0xA0, 0x13)
#define  REG_TC_SC1_OP1_BKA0_14_L       _PK_L_(0xA0, 0x14)
#define  REG_TC_SC1_OP1_BKA0_14_H       _PK_H_(0xA0, 0x14)
#define  REG_TC_SC1_OP1_BKA0_15_L       _PK_L_(0xA0, 0x15)
#define  REG_TC_SC1_OP1_BKA0_15_H       _PK_H_(0xA0, 0x15)
#define  REG_TC_SC1_OP1_BKA0_16_L       _PK_L_(0xA0, 0x16)
#define  REG_TC_SC1_OP1_BKA0_16_H       _PK_H_(0xA0, 0x16)
#define  REG_TC_SC1_OP1_BKA0_17_L       _PK_L_(0xA0, 0x17)
#define  REG_TC_SC1_OP1_BKA0_17_H       _PK_H_(0xA0, 0x17)
#define  REG_TC_SC1_OP1_BKA0_18_L       _PK_L_(0xA0, 0x18)
#define  REG_TC_SC1_OP1_BKA0_18_H       _PK_H_(0xA0, 0x18)
#define  REG_TC_SC1_OP1_BKA0_19_L       _PK_L_(0xA0, 0x19)
#define  REG_TC_SC1_OP1_BKA0_19_H       _PK_H_(0xA0, 0x19)
#define  REG_TC_SC1_OP1_BKA0_1A_L       _PK_L_(0xA0, 0x1A)
#define  REG_TC_SC1_OP1_BKA0_1A_H       _PK_H_(0xA0, 0x1A)
#define  REG_TC_SC1_OP1_BKA0_1B_L       _PK_L_(0xA0, 0x1B)
#define  REG_TC_SC1_OP1_BKA0_1B_H       _PK_H_(0xA0, 0x1B)
#define  REG_TC_SC1_OP1_BKA0_1C_L       _PK_L_(0xA0, 0x1C)
#define  REG_TC_SC1_OP1_BKA0_1C_H       _PK_H_(0xA0, 0x1C)
#define  REG_TC_SC1_OP1_BKA0_1D_L       _PK_L_(0xA0, 0x1D)
#define  REG_TC_SC1_OP1_BKA0_1D_H       _PK_H_(0xA0, 0x1D)
#define  REG_TC_SC1_OP1_BKA0_1E_L       _PK_L_(0xA0, 0x1E)
#define  REG_TC_SC1_OP1_BKA0_1E_H       _PK_H_(0xA0, 0x1E)
#define  REG_TC_SC1_OP1_BKA0_1F_L       _PK_L_(0xA0, 0x1F)
#define  REG_TC_SC1_OP1_BKA0_1F_H       _PK_H_(0xA0, 0x1F)
#define  REG_TC_SC1_OP1_BKA0_20_L       _PK_L_(0xA0, 0x20)
#define  REG_TC_SC1_OP1_BKA0_20_H       _PK_H_(0xA0, 0x20)
#define  REG_TC_SC1_OP1_BKA0_21_L       _PK_L_(0xA0, 0x21)
#define  REG_TC_SC1_OP1_BKA0_21_H       _PK_H_(0xA0, 0x21)
#define  REG_TC_SC1_OP1_BKA0_22_L       _PK_L_(0xA0, 0x22)
#define  REG_TC_SC1_OP1_BKA0_22_H       _PK_H_(0xA0, 0x22)
#define  REG_TC_SC1_OP1_BKA0_23_L       _PK_L_(0xA0, 0x23)
#define  REG_TC_SC1_OP1_BKA0_23_H       _PK_H_(0xA0, 0x23)
#define  REG_TC_SC1_OP1_BKA0_24_L       _PK_L_(0xA0, 0x24)
#define  REG_TC_SC1_OP1_BKA0_24_H       _PK_H_(0xA0, 0x24)
#define  REG_TC_SC1_OP1_BKA0_25_L       _PK_L_(0xA0, 0x25)
#define  REG_TC_SC1_OP1_BKA0_25_H       _PK_H_(0xA0, 0x25)
#define  REG_TC_SC1_OP1_BKA0_26_L       _PK_L_(0xA0, 0x26)
#define  REG_TC_SC1_OP1_BKA0_26_H       _PK_H_(0xA0, 0x26)
#define  REG_TC_SC1_OP1_BKA0_27_L       _PK_L_(0xA0, 0x27)
#define  REG_TC_SC1_OP1_BKA0_27_H       _PK_H_(0xA0, 0x27)
#define  REG_TC_SC1_OP1_BKA0_28_L       _PK_L_(0xA0, 0x28)
#define  REG_TC_SC1_OP1_BKA0_28_H       _PK_H_(0xA0, 0x28)
#define  REG_TC_SC1_OP1_BKA0_29_L       _PK_L_(0xA0, 0x29)
#define  REG_TC_SC1_OP1_BKA0_29_H       _PK_H_(0xA0, 0x29)
#define  REG_TC_SC1_OP1_BKA0_2A_L       _PK_L_(0xA0, 0x2A)
#define  REG_TC_SC1_OP1_BKA0_2A_H       _PK_H_(0xA0, 0x2A)
#define  REG_TC_SC1_OP1_BKA0_2B_L       _PK_L_(0xA0, 0x2B)
#define  REG_TC_SC1_OP1_BKA0_2B_H       _PK_H_(0xA0, 0x2B)
#define  REG_TC_SC1_OP1_BKA0_2C_L       _PK_L_(0xA0, 0x2C)
#define  REG_TC_SC1_OP1_BKA0_2C_H       _PK_H_(0xA0, 0x2C)
#define  REG_TC_SC1_OP1_BKA0_2D_L       _PK_L_(0xA0, 0x2D)
#define  REG_TC_SC1_OP1_BKA0_2D_H       _PK_H_(0xA0, 0x2D)
#define  REG_TC_SC1_OP1_BKA0_2E_L       _PK_L_(0xA0, 0x2E)
#define  REG_TC_SC1_OP1_BKA0_2E_H       _PK_H_(0xA0, 0x2E)
#define  REG_TC_SC1_OP1_BKA0_2F_L       _PK_L_(0xA0, 0x2F)
#define  REG_TC_SC1_OP1_BKA0_2F_H       _PK_H_(0xA0, 0x2F)
#define  REG_TC_SC1_OP1_BKA0_30_L       _PK_L_(0xA0, 0x30)
#define  REG_TC_SC1_OP1_BKA0_30_H       _PK_H_(0xA0, 0x30)
#define  REG_TC_SC1_OP1_BKA0_31_L       _PK_L_(0xA0, 0x31)
#define  REG_TC_SC1_OP1_BKA0_31_H       _PK_H_(0xA0, 0x31)
#define  REG_TC_SC1_OP1_BKA0_32_L       _PK_L_(0xA0, 0x32)
#define  REG_TC_SC1_OP1_BKA0_32_H       _PK_H_(0xA0, 0x32)
#define  REG_TC_SC1_OP1_BKA0_33_L       _PK_L_(0xA0, 0x33)
#define  REG_TC_SC1_OP1_BKA0_33_H       _PK_H_(0xA0, 0x33)
#define  REG_TC_SC1_OP1_BKA0_34_L       _PK_L_(0xA0, 0x34)
#define  REG_TC_SC1_OP1_BKA0_34_H       _PK_H_(0xA0, 0x34)
#define  REG_TC_SC1_OP1_BKA0_35_L       _PK_L_(0xA0, 0x35)
#define  REG_TC_SC1_OP1_BKA0_35_H       _PK_H_(0xA0, 0x35)
#define  REG_TC_SC1_OP1_BKA0_36_L       _PK_L_(0xA0, 0x36)
#define  REG_TC_SC1_OP1_BKA0_36_H       _PK_H_(0xA0, 0x36)
#define  REG_TC_SC1_OP1_BKA0_37_L       _PK_L_(0xA0, 0x37)
#define  REG_TC_SC1_OP1_BKA0_37_H       _PK_H_(0xA0, 0x37)
#define  REG_TC_SC1_OP1_BKA0_38_L       _PK_L_(0xA0, 0x38)
#define  REG_TC_SC1_OP1_BKA0_38_H       _PK_H_(0xA0, 0x38)
#define  REG_TC_SC1_OP1_BKA0_39_L       _PK_L_(0xA0, 0x39)
#define  REG_TC_SC1_OP1_BKA0_39_H       _PK_H_(0xA0, 0x39)
#define  REG_TC_SC1_OP1_BKA0_3A_L       _PK_L_(0xA0, 0x3A)
#define  REG_TC_SC1_OP1_BKA0_3A_H       _PK_H_(0xA0, 0x3A)
#define  REG_TC_SC1_OP1_BKA0_3B_L       _PK_L_(0xA0, 0x3B)
#define  REG_TC_SC1_OP1_BKA0_3B_H       _PK_H_(0xA0, 0x3B)
#define  REG_TC_SC1_OP1_BKA0_3C_L       _PK_L_(0xA0, 0x3C)
#define  REG_TC_SC1_OP1_BKA0_3C_H       _PK_H_(0xA0, 0x3C)
#define  REG_TC_SC1_OP1_BKA0_3D_L       _PK_L_(0xA0, 0x3D)
#define  REG_TC_SC1_OP1_BKA0_3D_H       _PK_H_(0xA0, 0x3D)
#define  REG_TC_SC1_OP1_BKA0_3E_L       _PK_L_(0xA0, 0x3E)
#define  REG_TC_SC1_OP1_BKA0_3E_H       _PK_H_(0xA0, 0x3E)
#define  REG_TC_SC1_OP1_BKA0_3F_L       _PK_L_(0xA0, 0x3F)
#define  REG_TC_SC1_OP1_BKA0_3F_H       _PK_H_(0xA0, 0x3F)
#define  REG_TC_SC1_OP1_BKA0_40_L       _PK_L_(0xA0, 0x40)
#define  REG_TC_SC1_OP1_BKA0_40_H       _PK_H_(0xA0, 0x40)
#define  REG_TC_SC1_OP1_BKA0_41_L       _PK_L_(0xA0, 0x41)
#define  REG_TC_SC1_OP1_BKA0_41_H       _PK_H_(0xA0, 0x41)
#define  REG_TC_SC1_OP1_BKA0_42_L       _PK_L_(0xA0, 0x42)
#define  REG_TC_SC1_OP1_BKA0_42_H       _PK_H_(0xA0, 0x42)
#define  REG_TC_SC1_OP1_BKA0_43_L       _PK_L_(0xA0, 0x43)
#define  REG_TC_SC1_OP1_BKA0_43_H       _PK_H_(0xA0, 0x43)
#define  REG_TC_SC1_OP1_BKA0_44_L       _PK_L_(0xA0, 0x44)
#define  REG_TC_SC1_OP1_BKA0_44_H       _PK_H_(0xA0, 0x44)
#define  REG_TC_SC1_OP1_BKA0_45_L       _PK_L_(0xA0, 0x45)
#define  REG_TC_SC1_OP1_BKA0_45_H       _PK_H_(0xA0, 0x45)
#define  REG_TC_SC1_OP1_BKA0_46_L       _PK_L_(0xA0, 0x46)
#define  REG_TC_SC1_OP1_BKA0_46_H       _PK_H_(0xA0, 0x46)
#define  REG_TC_SC1_OP1_BKA0_47_L       _PK_L_(0xA0, 0x47)
#define  REG_TC_SC1_OP1_BKA0_47_H       _PK_H_(0xA0, 0x47)
#define  REG_TC_SC1_OP1_BKA0_48_L       _PK_L_(0xA0, 0x48)
#define  REG_TC_SC1_OP1_BKA0_48_H       _PK_H_(0xA0, 0x48)
#define  REG_TC_SC1_OP1_BKA0_49_L       _PK_L_(0xA0, 0x49)
#define  REG_TC_SC1_OP1_BKA0_49_H       _PK_H_(0xA0, 0x49)
#define  REG_TC_SC1_OP1_BKA0_4A_L       _PK_L_(0xA0, 0x4A)
#define  REG_TC_SC1_OP1_BKA0_4A_H       _PK_H_(0xA0, 0x4A)
#define  REG_TC_SC1_OP1_BKA0_4B_L       _PK_L_(0xA0, 0x4B)
#define  REG_TC_SC1_OP1_BKA0_4B_H       _PK_H_(0xA0, 0x4B)
#define  REG_TC_SC1_OP1_BKA0_4C_L       _PK_L_(0xA0, 0x4C)
#define  REG_TC_SC1_OP1_BKA0_4C_H       _PK_H_(0xA0, 0x4C)
#define  REG_TC_SC1_OP1_BKA0_4D_L       _PK_L_(0xA0, 0x4D)
#define  REG_TC_SC1_OP1_BKA0_4D_H       _PK_H_(0xA0, 0x4D)
#define  REG_TC_SC1_OP1_BKA0_4E_L       _PK_L_(0xA0, 0x4E)
#define  REG_TC_SC1_OP1_BKA0_4E_H       _PK_H_(0xA0, 0x4E)
#define  REG_TC_SC1_OP1_BKA0_4F_L       _PK_L_(0xA0, 0x4F)
#define  REG_TC_SC1_OP1_BKA0_4F_H       _PK_H_(0xA0, 0x4F)
#define  REG_TC_SC1_OP1_BKA0_50_L       _PK_L_(0xA0, 0x50)
#define  REG_TC_SC1_OP1_BKA0_50_H       _PK_H_(0xA0, 0x50)
#define  REG_TC_SC1_OP1_BKA0_51_L       _PK_L_(0xA0, 0x51)
#define  REG_TC_SC1_OP1_BKA0_51_H       _PK_H_(0xA0, 0x51)
#define  REG_TC_SC1_OP1_BKA0_52_L       _PK_L_(0xA0, 0x52)
#define  REG_TC_SC1_OP1_BKA0_52_H       _PK_H_(0xA0, 0x52)
#define  REG_TC_SC1_OP1_BKA0_53_L       _PK_L_(0xA0, 0x53)
#define  REG_TC_SC1_OP1_BKA0_53_H       _PK_H_(0xA0, 0x53)
#define  REG_TC_SC1_OP1_BKA0_54_L       _PK_L_(0xA0, 0x54)
#define  REG_TC_SC1_OP1_BKA0_54_H       _PK_H_(0xA0, 0x54)
#define  REG_TC_SC1_OP1_BKA0_55_L       _PK_L_(0xA0, 0x55)
#define  REG_TC_SC1_OP1_BKA0_55_H       _PK_H_(0xA0, 0x55)
#define  REG_TC_SC1_OP1_BKA0_56_L       _PK_L_(0xA0, 0x56)
#define  REG_TC_SC1_OP1_BKA0_56_H       _PK_H_(0xA0, 0x56)
#define  REG_TC_SC1_OP1_BKA0_57_L       _PK_L_(0xA0, 0x57)
#define  REG_TC_SC1_OP1_BKA0_57_H       _PK_H_(0xA0, 0x57)
#define  REG_TC_SC1_OP1_BKA0_58_L       _PK_L_(0xA0, 0x58)
#define  REG_TC_SC1_OP1_BKA0_58_H       _PK_H_(0xA0, 0x58)
#define  REG_TC_SC1_OP1_BKA0_59_L       _PK_L_(0xA0, 0x59)
#define  REG_TC_SC1_OP1_BKA0_59_H       _PK_H_(0xA0, 0x59)
#define  REG_TC_SC1_OP1_BKA0_5A_L       _PK_L_(0xA0, 0x5A)
#define  REG_TC_SC1_OP1_BKA0_5A_H       _PK_H_(0xA0, 0x5A)
#define  REG_TC_SC1_OP1_BKA0_5B_L       _PK_L_(0xA0, 0x5B)
#define  REG_TC_SC1_OP1_BKA0_5B_H       _PK_H_(0xA0, 0x5B)
#define  REG_TC_SC1_OP1_BKA0_5C_L       _PK_L_(0xA0, 0x5C)
#define  REG_TC_SC1_OP1_BKA0_5C_H       _PK_H_(0xA0, 0x5C)
#define  REG_TC_SC1_OP1_BKA0_5D_L       _PK_L_(0xA0, 0x5D)
#define  REG_TC_SC1_OP1_BKA0_5D_H       _PK_H_(0xA0, 0x5D)
#define  REG_TC_SC1_OP1_BKA0_5E_L       _PK_L_(0xA0, 0x5E)
#define  REG_TC_SC1_OP1_BKA0_5E_H       _PK_H_(0xA0, 0x5E)
#define  REG_TC_SC1_OP1_BKA0_5F_L       _PK_L_(0xA0, 0x5F)
#define  REG_TC_SC1_OP1_BKA0_5F_H       _PK_H_(0xA0, 0x5F)
#define  REG_TC_SC1_OP1_BKA0_60_L       _PK_L_(0xA0, 0x60)
#define  REG_TC_SC1_OP1_BKA0_60_H       _PK_H_(0xA0, 0x60)
#define  REG_TC_SC1_OP1_BKA0_61_L       _PK_L_(0xA0, 0x61)
#define  REG_TC_SC1_OP1_BKA0_61_H       _PK_H_(0xA0, 0x61)
#define  REG_TC_SC1_OP1_BKA0_62_L       _PK_L_(0xA0, 0x62)
#define  REG_TC_SC1_OP1_BKA0_62_H       _PK_H_(0xA0, 0x62)
#define  REG_TC_SC1_OP1_BKA0_63_L       _PK_L_(0xA0, 0x63)
#define  REG_TC_SC1_OP1_BKA0_63_H       _PK_H_(0xA0, 0x63)
#define  REG_TC_SC1_OP1_BKA0_64_L       _PK_L_(0xA0, 0x64)
#define  REG_TC_SC1_OP1_BKA0_64_H       _PK_H_(0xA0, 0x64)
#define  REG_TC_SC1_OP1_BKA0_65_L       _PK_L_(0xA0, 0x65)
#define  REG_TC_SC1_OP1_BKA0_65_H       _PK_H_(0xA0, 0x65)
#define  REG_TC_SC1_OP1_BKA0_66_L       _PK_L_(0xA0, 0x66)
#define  REG_TC_SC1_OP1_BKA0_66_H       _PK_H_(0xA0, 0x66)
#define  REG_TC_SC1_OP1_BKA0_67_L       _PK_L_(0xA0, 0x67)
#define  REG_TC_SC1_OP1_BKA0_67_H       _PK_H_(0xA0, 0x67)
#define  REG_TC_SC1_OP1_BKA0_68_L       _PK_L_(0xA0, 0x68)
#define  REG_TC_SC1_OP1_BKA0_68_H       _PK_H_(0xA0, 0x68)
#define  REG_TC_SC1_OP1_BKA0_69_L       _PK_L_(0xA0, 0x69)
#define  REG_TC_SC1_OP1_BKA0_69_H       _PK_H_(0xA0, 0x69)
#define  REG_TC_SC1_OP1_BKA0_6A_L       _PK_L_(0xA0, 0x6A)
#define  REG_TC_SC1_OP1_BKA0_6A_H       _PK_H_(0xA0, 0x6A)
#define  REG_TC_SC1_OP1_BKA0_6B_L       _PK_L_(0xA0, 0x6B)
#define  REG_TC_SC1_OP1_BKA0_6B_H       _PK_H_(0xA0, 0x6B)
#define  REG_TC_SC1_OP1_BKA0_6C_L       _PK_L_(0xA0, 0x6C)
#define  REG_TC_SC1_OP1_BKA0_6C_H       _PK_H_(0xA0, 0x6C)
#define  REG_TC_SC1_OP1_BKA0_6D_L       _PK_L_(0xA0, 0x6D)
#define  REG_TC_SC1_OP1_BKA0_6D_H       _PK_H_(0xA0, 0x6D)
#define  REG_TC_SC1_OP1_BKA0_6E_L       _PK_L_(0xA0, 0x6E)
#define  REG_TC_SC1_OP1_BKA0_6E_H       _PK_H_(0xA0, 0x6E)
#define  REG_TC_SC1_OP1_BKA0_6F_L       _PK_L_(0xA0, 0x6F)
#define  REG_TC_SC1_OP1_BKA0_6F_H       _PK_H_(0xA0, 0x6F)
#define  REG_TC_SC1_OP1_BKA0_70_L       _PK_L_(0xA0, 0x70)
#define  REG_TC_SC1_OP1_BKA0_70_H       _PK_H_(0xA0, 0x70)
#define  REG_TC_SC1_OP1_BKA0_71_L       _PK_L_(0xA0, 0x71)
#define  REG_TC_SC1_OP1_BKA0_71_H       _PK_H_(0xA0, 0x71)
#define  REG_TC_SC1_OP1_BKA0_72_L       _PK_L_(0xA0, 0x72)
#define  REG_TC_SC1_OP1_BKA0_72_H       _PK_H_(0xA0, 0x72)
#define  REG_TC_SC1_OP1_BKA0_73_L       _PK_L_(0xA0, 0x73)
#define  REG_TC_SC1_OP1_BKA0_73_H       _PK_H_(0xA0, 0x73)
#define  REG_TC_SC1_OP1_BKA0_74_L       _PK_L_(0xA0, 0x74)
#define  REG_TC_SC1_OP1_BKA0_74_H       _PK_H_(0xA0, 0x74)
#define  REG_TC_SC1_OP1_BKA0_75_L       _PK_L_(0xA0, 0x75)
#define  REG_TC_SC1_OP1_BKA0_75_H       _PK_H_(0xA0, 0x75)
#define  REG_TC_SC1_OP1_BKA0_76_L       _PK_L_(0xA0, 0x76)
#define  REG_TC_SC1_OP1_BKA0_76_H       _PK_H_(0xA0, 0x76)
#define  REG_TC_SC1_OP1_BKA0_77_L       _PK_L_(0xA0, 0x77)
#define  REG_TC_SC1_OP1_BKA0_77_H       _PK_H_(0xA0, 0x77)
#define  REG_TC_SC1_OP1_BKA0_78_L       _PK_L_(0xA0, 0x78)
#define  REG_TC_SC1_OP1_BKA0_78_H       _PK_H_(0xA0, 0x78)
#define  REG_TC_SC1_OP1_BKA0_79_L       _PK_L_(0xA0, 0x79)
#define  REG_TC_SC1_OP1_BKA0_79_H       _PK_H_(0xA0, 0x79)
#define  REG_TC_SC1_OP1_BKA0_7A_L       _PK_L_(0xA0, 0x7A)
#define  REG_TC_SC1_OP1_BKA0_7A_H       _PK_H_(0xA0, 0x7A)
#define  REG_TC_SC1_OP1_BKA0_7B_L       _PK_L_(0xA0, 0x7B)
#define  REG_TC_SC1_OP1_BKA0_7B_H       _PK_H_(0xA0, 0x7B)
#define  REG_TC_SC1_OP1_BKA0_7C_L       _PK_L_(0xA0, 0x7C)
#define  REG_TC_SC1_OP1_BKA0_7C_H       _PK_H_(0xA0, 0x7C)
#define  REG_TC_SC1_OP1_BKA0_7D_L       _PK_L_(0xA0, 0x7D)
#define  REG_TC_SC1_OP1_BKA0_7D_H       _PK_H_(0xA0, 0x7D)
#define  REG_TC_SC1_OP1_BKA0_7E_L       _PK_L_(0xA0, 0x7E)
#define  REG_TC_SC1_OP1_BKA0_7E_H       _PK_H_(0xA0, 0x7E)
#define  REG_TC_SC1_OP1_BKA0_7F_L       _PK_L_(0xA0, 0x7F)
#define  REG_TC_SC1_OP1_BKA0_7F_H       _PK_H_(0xA0, 0x7F)

#define  REG_TC_SC1_SVOP_BK8F_00_L       _PK_L_(0x8F, 0x00)
#define  REG_TC_SC1_SVOP_BK8F_00_H       _PK_H_(0x8F, 0x00)
#define  REG_TC_SC1_SVOP_BK8F_01_L       _PK_L_(0x8F, 0x01)
#define  REG_TC_SC1_SVOP_BK8F_01_H       _PK_H_(0x8F, 0x01)
#define  REG_TC_SC1_SVOP_BK8F_02_L       _PK_L_(0x8F, 0x02)
#define  REG_TC_SC1_SVOP_BK8F_02_H       _PK_H_(0x8F, 0x02)
#define  REG_TC_SC1_SVOP_BK8F_03_L       _PK_L_(0x8F, 0x03)
#define  REG_TC_SC1_SVOP_BK8F_03_H       _PK_H_(0x8F, 0x03)
#define  REG_TC_SC1_SVOP_BK8F_04_L       _PK_L_(0x8F, 0x04)
#define  REG_TC_SC1_SVOP_BK8F_04_H       _PK_H_(0x8F, 0x04)
#define  REG_TC_SC1_SVOP_BK8F_05_L       _PK_L_(0x8F, 0x05)
#define  REG_TC_SC1_SVOP_BK8F_05_H       _PK_H_(0x8F, 0x05)
#define  REG_TC_SC1_SVOP_BK8F_06_L       _PK_L_(0x8F, 0x06)
#define  REG_TC_SC1_SVOP_BK8F_06_H       _PK_H_(0x8F, 0x06)
#define  REG_TC_SC1_SVOP_BK8F_07_L       _PK_L_(0x8F, 0x07)
#define  REG_TC_SC1_SVOP_BK8F_07_H       _PK_H_(0x8F, 0x07)
#define  REG_TC_SC1_SVOP_BK8F_08_L       _PK_L_(0x8F, 0x08)
#define  REG_TC_SC1_SVOP_BK8F_08_H       _PK_H_(0x8F, 0x08)
#define  REG_TC_SC1_SVOP_BK8F_09_L       _PK_L_(0x8F, 0x09)
#define  REG_TC_SC1_SVOP_BK8F_09_H       _PK_H_(0x8F, 0x09)
#define  REG_TC_SC1_SVOP_BK8F_0A_L       _PK_L_(0x8F, 0x0A)
#define  REG_TC_SC1_SVOP_BK8F_0A_H       _PK_H_(0x8F, 0x0A)
#define  REG_TC_SC1_SVOP_BK8F_0B_L       _PK_L_(0x8F, 0x0B)
#define  REG_TC_SC1_SVOP_BK8F_0B_H       _PK_H_(0x8F, 0x0B)
#define  REG_TC_SC1_SVOP_BK8F_0C_L       _PK_L_(0x8F, 0x0C)
#define  REG_TC_SC1_SVOP_BK8F_0C_H       _PK_H_(0x8F, 0x0C)
#define  REG_TC_SC1_SVOP_BK8F_0D_L       _PK_L_(0x8F, 0x0D)
#define  REG_TC_SC1_SVOP_BK8F_0D_H       _PK_H_(0x8F, 0x0D)
#define  REG_TC_SC1_SVOP_BK8F_0E_L       _PK_L_(0x8F, 0x0E)
#define  REG_TC_SC1_SVOP_BK8F_0E_H       _PK_H_(0x8F, 0x0E)
#define  REG_TC_SC1_SVOP_BK8F_0F_L       _PK_L_(0x8F, 0x0F)
#define  REG_TC_SC1_SVOP_BK8F_0F_H       _PK_H_(0x8F, 0x0F)
#define  REG_TC_SC1_SVOP_BK8F_10_L       _PK_L_(0x8F, 0x10)
#define  REG_TC_SC1_SVOP_BK8F_10_H       _PK_H_(0x8F, 0x10)
#define  REG_TC_SC1_SVOP_BK8F_11_L       _PK_L_(0x8F, 0x11)
#define  REG_TC_SC1_SVOP_BK8F_11_H       _PK_H_(0x8F, 0x11)
#define  REG_TC_SC1_SVOP_BK8F_12_L       _PK_L_(0x8F, 0x12)
#define  REG_TC_SC1_SVOP_BK8F_12_H       _PK_H_(0x8F, 0x12)
#define  REG_TC_SC1_SVOP_BK8F_13_L       _PK_L_(0x8F, 0x13)
#define  REG_TC_SC1_SVOP_BK8F_13_H       _PK_H_(0x8F, 0x13)
#define  REG_TC_SC1_SVOP_BK8F_14_L       _PK_L_(0x8F, 0x14)
#define  REG_TC_SC1_SVOP_BK8F_14_H       _PK_H_(0x8F, 0x14)
#define  REG_TC_SC1_SVOP_BK8F_15_L       _PK_L_(0x8F, 0x15)
#define  REG_TC_SC1_SVOP_BK8F_15_H       _PK_H_(0x8F, 0x15)
#define  REG_TC_SC1_SVOP_BK8F_16_L       _PK_L_(0x8F, 0x16)
#define  REG_TC_SC1_SVOP_BK8F_16_H       _PK_H_(0x8F, 0x16)
#define  REG_TC_SC1_SVOP_BK8F_17_L       _PK_L_(0x8F, 0x17)
#define  REG_TC_SC1_SVOP_BK8F_17_H       _PK_H_(0x8F, 0x17)
#define  REG_TC_SC1_SVOP_BK8F_18_L       _PK_L_(0x8F, 0x18)
#define  REG_TC_SC1_SVOP_BK8F_18_H       _PK_H_(0x8F, 0x18)
#define  REG_TC_SC1_SVOP_BK8F_19_L       _PK_L_(0x8F, 0x19)
#define  REG_TC_SC1_SVOP_BK8F_19_H       _PK_H_(0x8F, 0x19)
#define  REG_TC_SC1_SVOP_BK8F_1A_L       _PK_L_(0x8F, 0x1A)
#define  REG_TC_SC1_SVOP_BK8F_1A_H       _PK_H_(0x8F, 0x1A)
#define  REG_TC_SC1_SVOP_BK8F_1B_L       _PK_L_(0x8F, 0x1B)
#define  REG_TC_SC1_SVOP_BK8F_1B_H       _PK_H_(0x8F, 0x1B)
#define  REG_TC_SC1_SVOP_BK8F_1C_L       _PK_L_(0x8F, 0x1C)
#define  REG_TC_SC1_SVOP_BK8F_1C_H       _PK_H_(0x8F, 0x1C)
#define  REG_TC_SC1_SVOP_BK8F_1D_L       _PK_L_(0x8F, 0x1D)
#define  REG_TC_SC1_SVOP_BK8F_1D_H       _PK_H_(0x8F, 0x1D)
#define  REG_TC_SC1_SVOP_BK8F_1E_L       _PK_L_(0x8F, 0x1E)
#define  REG_TC_SC1_SVOP_BK8F_1E_H       _PK_H_(0x8F, 0x1E)
#define  REG_TC_SC1_SVOP_BK8F_1F_L       _PK_L_(0x8F, 0x1F)
#define  REG_TC_SC1_SVOP_BK8F_1F_H       _PK_H_(0x8F, 0x1F)
#define  REG_TC_SC1_SVOP_BK8F_20_L       _PK_L_(0x8F, 0x20)
#define  REG_TC_SC1_SVOP_BK8F_20_H       _PK_H_(0x8F, 0x20)
#define  REG_TC_SC1_SVOP_BK8F_21_L       _PK_L_(0x8F, 0x21)
#define  REG_TC_SC1_SVOP_BK8F_21_H       _PK_H_(0x8F, 0x21)
#define  REG_TC_SC1_SVOP_BK8F_22_L       _PK_L_(0x8F, 0x22)
#define  REG_TC_SC1_SVOP_BK8F_22_H       _PK_H_(0x8F, 0x22)
#define  REG_TC_SC1_SVOP_BK8F_23_L       _PK_L_(0x8F, 0x23)
#define  REG_TC_SC1_SVOP_BK8F_23_H       _PK_H_(0x8F, 0x23)
#define  REG_TC_SC1_SVOP_BK8F_24_L       _PK_L_(0x8F, 0x24)
#define  REG_TC_SC1_SVOP_BK8F_24_H       _PK_H_(0x8F, 0x24)
#define  REG_TC_SC1_SVOP_BK8F_25_L       _PK_L_(0x8F, 0x25)
#define  REG_TC_SC1_SVOP_BK8F_25_H       _PK_H_(0x8F, 0x25)
#define  REG_TC_SC1_SVOP_BK8F_26_L       _PK_L_(0x8F, 0x26)
#define  REG_TC_SC1_SVOP_BK8F_26_H       _PK_H_(0x8F, 0x26)
#define  REG_TC_SC1_SVOP_BK8F_27_L       _PK_L_(0x8F, 0x27)
#define  REG_TC_SC1_SVOP_BK8F_27_H       _PK_H_(0x8F, 0x27)
#define  REG_TC_SC1_SVOP_BK8F_28_L       _PK_L_(0x8F, 0x28)
#define  REG_TC_SC1_SVOP_BK8F_28_H       _PK_H_(0x8F, 0x28)
#define  REG_TC_SC1_SVOP_BK8F_29_L       _PK_L_(0x8F, 0x29)
#define  REG_TC_SC1_SVOP_BK8F_29_H       _PK_H_(0x8F, 0x29)
#define  REG_TC_SC1_SVOP_BK8F_2A_L       _PK_L_(0x8F, 0x2A)
#define  REG_TC_SC1_SVOP_BK8F_2A_H       _PK_H_(0x8F, 0x2A)
#define  REG_TC_SC1_SVOP_BK8F_2B_L       _PK_L_(0x8F, 0x2B)
#define  REG_TC_SC1_SVOP_BK8F_2B_H       _PK_H_(0x8F, 0x2B)
#define  REG_TC_SC1_SVOP_BK8F_2C_L       _PK_L_(0x8F, 0x2C)
#define  REG_TC_SC1_SVOP_BK8F_2C_H       _PK_H_(0x8F, 0x2C)
#define  REG_TC_SC1_SVOP_BK8F_2D_L       _PK_L_(0x8F, 0x2D)
#define  REG_TC_SC1_SVOP_BK8F_2D_H       _PK_H_(0x8F, 0x2D)
#define  REG_TC_SC1_SVOP_BK8F_2E_L       _PK_L_(0x8F, 0x2E)
#define  REG_TC_SC1_SVOP_BK8F_2E_H       _PK_H_(0x8F, 0x2E)
#define  REG_TC_SC1_SVOP_BK8F_2F_L       _PK_L_(0x8F, 0x2F)
#define  REG_TC_SC1_SVOP_BK8F_2F_H       _PK_H_(0x8F, 0x2F)
#define  REG_TC_SC1_SVOP_BK8F_30_L       _PK_L_(0x8F, 0x30)
#define  REG_TC_SC1_SVOP_BK8F_30_H       _PK_H_(0x8F, 0x30)
#define  REG_TC_SC1_SVOP_BK8F_31_L       _PK_L_(0x8F, 0x31)
#define  REG_TC_SC1_SVOP_BK8F_31_H       _PK_H_(0x8F, 0x31)
#define  REG_TC_SC1_SVOP_BK8F_32_L       _PK_L_(0x8F, 0x32)
#define  REG_TC_SC1_SVOP_BK8F_32_H       _PK_H_(0x8F, 0x32)
#define  REG_TC_SC1_SVOP_BK8F_33_L       _PK_L_(0x8F, 0x33)
#define  REG_TC_SC1_SVOP_BK8F_33_H       _PK_H_(0x8F, 0x33)
#define  REG_TC_SC1_SVOP_BK8F_34_L       _PK_L_(0x8F, 0x34)
#define  REG_TC_SC1_SVOP_BK8F_34_H       _PK_H_(0x8F, 0x34)
#define  REG_TC_SC1_SVOP_BK8F_35_L       _PK_L_(0x8F, 0x35)
#define  REG_TC_SC1_SVOP_BK8F_35_H       _PK_H_(0x8F, 0x35)
#define  REG_TC_SC1_SVOP_BK8F_36_L       _PK_L_(0x8F, 0x36)
#define  REG_TC_SC1_SVOP_BK8F_36_H       _PK_H_(0x8F, 0x36)
#define  REG_TC_SC1_SVOP_BK8F_37_L       _PK_L_(0x8F, 0x37)
#define  REG_TC_SC1_SVOP_BK8F_37_H       _PK_H_(0x8F, 0x37)
#define  REG_TC_SC1_SVOP_BK8F_38_L       _PK_L_(0x8F, 0x38)
#define  REG_TC_SC1_SVOP_BK8F_38_H       _PK_H_(0x8F, 0x38)
#define  REG_TC_SC1_SVOP_BK8F_39_L       _PK_L_(0x8F, 0x39)
#define  REG_TC_SC1_SVOP_BK8F_39_H       _PK_H_(0x8F, 0x39)
#define  REG_TC_SC1_SVOP_BK8F_3A_L       _PK_L_(0x8F, 0x3A)
#define  REG_TC_SC1_SVOP_BK8F_3A_H       _PK_H_(0x8F, 0x3A)
#define  REG_TC_SC1_SVOP_BK8F_3B_L       _PK_L_(0x8F, 0x3B)
#define  REG_TC_SC1_SVOP_BK8F_3B_H       _PK_H_(0x8F, 0x3B)
#define  REG_TC_SC1_SVOP_BK8F_3C_L       _PK_L_(0x8F, 0x3C)
#define  REG_TC_SC1_SVOP_BK8F_3C_H       _PK_H_(0x8F, 0x3C)
#define  REG_TC_SC1_SVOP_BK8F_3D_L       _PK_L_(0x8F, 0x3D)
#define  REG_TC_SC1_SVOP_BK8F_3D_H       _PK_H_(0x8F, 0x3D)
#define  REG_TC_SC1_SVOP_BK8F_3E_L       _PK_L_(0x8F, 0x3E)
#define  REG_TC_SC1_SVOP_BK8F_3E_H       _PK_H_(0x8F, 0x3E)
#define  REG_TC_SC1_SVOP_BK8F_3F_L       _PK_L_(0x8F, 0x3F)
#define  REG_TC_SC1_SVOP_BK8F_3F_H       _PK_H_(0x8F, 0x3F)
#define  REG_TC_SC1_SVOP_BK8F_40_L       _PK_L_(0x8F, 0x40)
#define  REG_TC_SC1_SVOP_BK8F_40_H       _PK_H_(0x8F, 0x40)
#define  REG_TC_SC1_SVOP_BK8F_41_L       _PK_L_(0x8F, 0x41)
#define  REG_TC_SC1_SVOP_BK8F_41_H       _PK_H_(0x8F, 0x41)
#define  REG_TC_SC1_SVOP_BK8F_42_L       _PK_L_(0x8F, 0x42)
#define  REG_TC_SC1_SVOP_BK8F_42_H       _PK_H_(0x8F, 0x42)
#define  REG_TC_SC1_SVOP_BK8F_43_L       _PK_L_(0x8F, 0x43)
#define  REG_TC_SC1_SVOP_BK8F_43_H       _PK_H_(0x8F, 0x43)
#define  REG_TC_SC1_SVOP_BK8F_44_L       _PK_L_(0x8F, 0x44)
#define  REG_TC_SC1_SVOP_BK8F_44_H       _PK_H_(0x8F, 0x44)
#define  REG_TC_SC1_SVOP_BK8F_45_L       _PK_L_(0x8F, 0x45)
#define  REG_TC_SC1_SVOP_BK8F_45_H       _PK_H_(0x8F, 0x45)
#define  REG_TC_SC1_SVOP_BK8F_46_L       _PK_L_(0x8F, 0x46)
#define  REG_TC_SC1_SVOP_BK8F_46_H       _PK_H_(0x8F, 0x46)
#define  REG_TC_SC1_SVOP_BK8F_47_L       _PK_L_(0x8F, 0x47)
#define  REG_TC_SC1_SVOP_BK8F_47_H       _PK_H_(0x8F, 0x47)
#define  REG_TC_SC1_SVOP_BK8F_48_L       _PK_L_(0x8F, 0x48)
#define  REG_TC_SC1_SVOP_BK8F_48_H       _PK_H_(0x8F, 0x48)
#define  REG_TC_SC1_SVOP_BK8F_49_L       _PK_L_(0x8F, 0x49)
#define  REG_TC_SC1_SVOP_BK8F_49_H       _PK_H_(0x8F, 0x49)
#define  REG_TC_SC1_SVOP_BK8F_4A_L       _PK_L_(0x8F, 0x4A)
#define  REG_TC_SC1_SVOP_BK8F_4A_H       _PK_H_(0x8F, 0x4A)
#define  REG_TC_SC1_SVOP_BK8F_4B_L       _PK_L_(0x8F, 0x4B)
#define  REG_TC_SC1_SVOP_BK8F_4B_H       _PK_H_(0x8F, 0x4B)
#define  REG_TC_SC1_SVOP_BK8F_4C_L       _PK_L_(0x8F, 0x4C)
#define  REG_TC_SC1_SVOP_BK8F_4C_H       _PK_H_(0x8F, 0x4C)
#define  REG_TC_SC1_SVOP_BK8F_4D_L       _PK_L_(0x8F, 0x4D)
#define  REG_TC_SC1_SVOP_BK8F_4D_H       _PK_H_(0x8F, 0x4D)
#define  REG_TC_SC1_SVOP_BK8F_4E_L       _PK_L_(0x8F, 0x4E)
#define  REG_TC_SC1_SVOP_BK8F_4E_H       _PK_H_(0x8F, 0x4E)
#define  REG_TC_SC1_SVOP_BK8F_4F_L       _PK_L_(0x8F, 0x4F)
#define  REG_TC_SC1_SVOP_BK8F_4F_H       _PK_H_(0x8F, 0x4F)
#define  REG_TC_SC1_SVOP_BK8F_50_L       _PK_L_(0x8F, 0x50)
#define  REG_TC_SC1_SVOP_BK8F_50_H       _PK_H_(0x8F, 0x50)
#define  REG_TC_SC1_SVOP_BK8F_51_L       _PK_L_(0x8F, 0x51)
#define  REG_TC_SC1_SVOP_BK8F_51_H       _PK_H_(0x8F, 0x51)
#define  REG_TC_SC1_SVOP_BK8F_52_L       _PK_L_(0x8F, 0x52)
#define  REG_TC_SC1_SVOP_BK8F_52_H       _PK_H_(0x8F, 0x52)
#define  REG_TC_SC1_SVOP_BK8F_53_L       _PK_L_(0x8F, 0x53)
#define  REG_TC_SC1_SVOP_BK8F_53_H       _PK_H_(0x8F, 0x53)
#define  REG_TC_SC1_SVOP_BK8F_54_L       _PK_L_(0x8F, 0x54)
#define  REG_TC_SC1_SVOP_BK8F_54_H       _PK_H_(0x8F, 0x54)
#define  REG_TC_SC1_SVOP_BK8F_55_L       _PK_L_(0x8F, 0x55)
#define  REG_TC_SC1_SVOP_BK8F_55_H       _PK_H_(0x8F, 0x55)
#define  REG_TC_SC1_SVOP_BK8F_56_L       _PK_L_(0x8F, 0x56)
#define  REG_TC_SC1_SVOP_BK8F_56_H       _PK_H_(0x8F, 0x56)
#define  REG_TC_SC1_SVOP_BK8F_57_L       _PK_L_(0x8F, 0x57)
#define  REG_TC_SC1_SVOP_BK8F_57_H       _PK_H_(0x8F, 0x57)
#define  REG_TC_SC1_SVOP_BK8F_58_L       _PK_L_(0x8F, 0x58)
#define  REG_TC_SC1_SVOP_BK8F_58_H       _PK_H_(0x8F, 0x58)
#define  REG_TC_SC1_SVOP_BK8F_59_L       _PK_L_(0x8F, 0x59)
#define  REG_TC_SC1_SVOP_BK8F_59_H       _PK_H_(0x8F, 0x59)
#define  REG_TC_SC1_SVOP_BK8F_5A_L       _PK_L_(0x8F, 0x5A)
#define  REG_TC_SC1_SVOP_BK8F_5A_H       _PK_H_(0x8F, 0x5A)
#define  REG_TC_SC1_SVOP_BK8F_5B_L       _PK_L_(0x8F, 0x5B)
#define  REG_TC_SC1_SVOP_BK8F_5B_H       _PK_H_(0x8F, 0x5B)
#define  REG_TC_SC1_SVOP_BK8F_5C_L       _PK_L_(0x8F, 0x5C)
#define  REG_TC_SC1_SVOP_BK8F_5C_H       _PK_H_(0x8F, 0x5C)
#define  REG_TC_SC1_SVOP_BK8F_5D_L       _PK_L_(0x8F, 0x5D)
#define  REG_TC_SC1_SVOP_BK8F_5D_H       _PK_H_(0x8F, 0x5D)
#define  REG_TC_SC1_SVOP_BK8F_5E_L       _PK_L_(0x8F, 0x5E)
#define  REG_TC_SC1_SVOP_BK8F_5E_H       _PK_H_(0x8F, 0x5E)
#define  REG_TC_SC1_SVOP_BK8F_5F_L       _PK_L_(0x8F, 0x5F)
#define  REG_TC_SC1_SVOP_BK8F_5F_H       _PK_H_(0x8F, 0x5F)
#define  REG_TC_SC1_SVOP_BK8F_60_L       _PK_L_(0x8F, 0x60)
#define  REG_TC_SC1_SVOP_BK8F_60_H       _PK_H_(0x8F, 0x60)
#define  REG_TC_SC1_SVOP_BK8F_61_L       _PK_L_(0x8F, 0x61)
#define  REG_TC_SC1_SVOP_BK8F_61_H       _PK_H_(0x8F, 0x61)
#define  REG_TC_SC1_SVOP_BK8F_62_L       _PK_L_(0x8F, 0x62)
#define  REG_TC_SC1_SVOP_BK8F_62_H       _PK_H_(0x8F, 0x62)
#define  REG_TC_SC1_SVOP_BK8F_63_L       _PK_L_(0x8F, 0x63)
#define  REG_TC_SC1_SVOP_BK8F_63_H       _PK_H_(0x8F, 0x63)
#define  REG_TC_SC1_SVOP_BK8F_64_L       _PK_L_(0x8F, 0x64)
#define  REG_TC_SC1_SVOP_BK8F_64_H       _PK_H_(0x8F, 0x64)
#define  REG_TC_SC1_SVOP_BK8F_65_L       _PK_L_(0x8F, 0x65)
#define  REG_TC_SC1_SVOP_BK8F_65_H       _PK_H_(0x8F, 0x65)
#define  REG_TC_SC1_SVOP_BK8F_66_L       _PK_L_(0x8F, 0x66)
#define  REG_TC_SC1_SVOP_BK8F_66_H       _PK_H_(0x8F, 0x66)
#define  REG_TC_SC1_SVOP_BK8F_67_L       _PK_L_(0x8F, 0x67)
#define  REG_TC_SC1_SVOP_BK8F_67_H       _PK_H_(0x8F, 0x67)
#define  REG_TC_SC1_SVOP_BK8F_68_L       _PK_L_(0x8F, 0x68)
#define  REG_TC_SC1_SVOP_BK8F_68_H       _PK_H_(0x8F, 0x68)
#define  REG_TC_SC1_SVOP_BK8F_69_L       _PK_L_(0x8F, 0x69)
#define  REG_TC_SC1_SVOP_BK8F_69_H       _PK_H_(0x8F, 0x69)
#define  REG_TC_SC1_SVOP_BK8F_6A_L       _PK_L_(0x8F, 0x6A)
#define  REG_TC_SC1_SVOP_BK8F_6A_H       _PK_H_(0x8F, 0x6A)
#define  REG_TC_SC1_SVOP_BK8F_6B_L       _PK_L_(0x8F, 0x6B)
#define  REG_TC_SC1_SVOP_BK8F_6B_H       _PK_H_(0x8F, 0x6B)
#define  REG_TC_SC1_SVOP_BK8F_6C_L       _PK_L_(0x8F, 0x6C)
#define  REG_TC_SC1_SVOP_BK8F_6C_H       _PK_H_(0x8F, 0x6C)
#define  REG_TC_SC1_SVOP_BK8F_6D_L       _PK_L_(0x8F, 0x6D)
#define  REG_TC_SC1_SVOP_BK8F_6D_H       _PK_H_(0x8F, 0x6D)
#define  REG_TC_SC1_SVOP_BK8F_6E_L       _PK_L_(0x8F, 0x6E)
#define  REG_TC_SC1_SVOP_BK8F_6E_H       _PK_H_(0x8F, 0x6E)
#define  REG_TC_SC1_SVOP_BK8F_6F_L       _PK_L_(0x8F, 0x6F)
#define  REG_TC_SC1_SVOP_BK8F_6F_H       _PK_H_(0x8F, 0x6F)
#define  REG_TC_SC1_SVOP_BK8F_70_L       _PK_L_(0x8F, 0x70)
#define  REG_TC_SC1_SVOP_BK8F_70_H       _PK_H_(0x8F, 0x70)
#define  REG_TC_SC1_SVOP_BK8F_71_L       _PK_L_(0x8F, 0x71)
#define  REG_TC_SC1_SVOP_BK8F_71_H       _PK_H_(0x8F, 0x71)
#define  REG_TC_SC1_SVOP_BK8F_72_L       _PK_L_(0x8F, 0x72)
#define  REG_TC_SC1_SVOP_BK8F_72_H       _PK_H_(0x8F, 0x72)
#define  REG_TC_SC1_SVOP_BK8F_73_L       _PK_L_(0x8F, 0x73)
#define  REG_TC_SC1_SVOP_BK8F_73_H       _PK_H_(0x8F, 0x73)
#define  REG_TC_SC1_SVOP_BK8F_74_L       _PK_L_(0x8F, 0x74)
#define  REG_TC_SC1_SVOP_BK8F_74_H       _PK_H_(0x8F, 0x74)
#define  REG_TC_SC1_SVOP_BK8F_75_L       _PK_L_(0x8F, 0x75)
#define  REG_TC_SC1_SVOP_BK8F_75_H       _PK_H_(0x8F, 0x75)
#define  REG_TC_SC1_SVOP_BK8F_76_L       _PK_L_(0x8F, 0x76)
#define  REG_TC_SC1_SVOP_BK8F_76_H       _PK_H_(0x8F, 0x76)
#define  REG_TC_SC1_SVOP_BK8F_77_L       _PK_L_(0x8F, 0x77)
#define  REG_TC_SC1_SVOP_BK8F_77_H       _PK_H_(0x8F, 0x77)
#define  REG_TC_SC1_SVOP_BK8F_78_L       _PK_L_(0x8F, 0x78)
#define  REG_TC_SC1_SVOP_BK8F_78_H       _PK_H_(0x8F, 0x78)
#define  REG_TC_SC1_SVOP_BK8F_79_L       _PK_L_(0x8F, 0x79)
#define  REG_TC_SC1_SVOP_BK8F_79_H       _PK_H_(0x8F, 0x79)
#define  REG_TC_SC1_SVOP_BK8F_7A_L       _PK_L_(0x8F, 0x7A)
#define  REG_TC_SC1_SVOP_BK8F_7A_H       _PK_H_(0x8F, 0x7A)
#define  REG_TC_SC1_SVOP_BK8F_7B_L       _PK_L_(0x8F, 0x7B)
#define  REG_TC_SC1_SVOP_BK8F_7B_H       _PK_H_(0x8F, 0x7B)
#define  REG_TC_SC1_SVOP_BK8F_7C_L       _PK_L_(0x8F, 0x7C)
#define  REG_TC_SC1_SVOP_BK8F_7C_H       _PK_H_(0x8F, 0x7C)
#define  REG_TC_SC1_SVOP_BK8F_7D_L       _PK_L_(0x8F, 0x7D)
#define  REG_TC_SC1_SVOP_BK8F_7D_H       _PK_H_(0x8F, 0x7D)
#define  REG_TC_SC1_SVOP_BK8F_7E_L       _PK_L_(0x8F, 0x7E)
#define  REG_TC_SC1_SVOP_BK8F_7E_H       _PK_H_(0x8F, 0x7E)
#define  REG_TC_SC1_SVOP_BK8F_7F_L       _PK_L_(0x8F, 0x7F)
#define  REG_TC_SC1_SVOP_BK8F_7F_H       _PK_H_(0x8F, 0x7F)

#define  REG_TC_SC1_SCMI_BK92_00_L       _PK_L_(0x92, 0x00)
#define  REG_TC_SC1_SCMI_BK92_00_H       _PK_H_(0x92, 0x00)
#define  REG_TC_SC1_SCMI_BK92_01_L       _PK_L_(0x92, 0x01)
#define  REG_TC_SC1_SCMI_BK92_01_H       _PK_H_(0x92, 0x01)
#define  REG_TC_SC1_SCMI_BK92_02_L       _PK_L_(0x92, 0x02)
#define  REG_TC_SC1_SCMI_BK92_02_H       _PK_H_(0x92, 0x02)
#define  REG_TC_SC1_SCMI_BK92_03_L       _PK_L_(0x92, 0x03)
#define  REG_TC_SC1_SCMI_BK92_03_H       _PK_H_(0x92, 0x03)
#define  REG_TC_SC1_SCMI_BK92_04_L       _PK_L_(0x92, 0x04)
#define  REG_TC_SC1_SCMI_BK92_04_H       _PK_H_(0x92, 0x04)
#define  REG_TC_SC1_SCMI_BK92_05_L       _PK_L_(0x92, 0x05)
#define  REG_TC_SC1_SCMI_BK92_05_H       _PK_H_(0x92, 0x05)
#define  REG_TC_SC1_SCMI_BK92_06_L       _PK_L_(0x92, 0x06)
#define  REG_TC_SC1_SCMI_BK92_06_H       _PK_H_(0x92, 0x06)
#define  REG_TC_SC1_SCMI_BK92_07_L       _PK_L_(0x92, 0x07)
#define  REG_TC_SC1_SCMI_BK92_07_H       _PK_H_(0x92, 0x07)
#define  REG_TC_SC1_SCMI_BK92_08_L       _PK_L_(0x92, 0x08)
#define  REG_TC_SC1_SCMI_BK92_08_H       _PK_H_(0x92, 0x08)
#define  REG_TC_SC1_SCMI_BK92_09_L       _PK_L_(0x92, 0x09)
#define  REG_TC_SC1_SCMI_BK92_09_H       _PK_H_(0x92, 0x09)
#define  REG_TC_SC1_SCMI_BK92_0A_L       _PK_L_(0x92, 0x0A)
#define  REG_TC_SC1_SCMI_BK92_0A_H       _PK_H_(0x92, 0x0A)
#define  REG_TC_SC1_SCMI_BK92_0B_L       _PK_L_(0x92, 0x0B)
#define  REG_TC_SC1_SCMI_BK92_0B_H       _PK_H_(0x92, 0x0B)
#define  REG_TC_SC1_SCMI_BK92_0C_L       _PK_L_(0x92, 0x0C)
#define  REG_TC_SC1_SCMI_BK92_0C_H       _PK_H_(0x92, 0x0C)
#define  REG_TC_SC1_SCMI_BK92_0D_L       _PK_L_(0x92, 0x0D)
#define  REG_TC_SC1_SCMI_BK92_0D_H       _PK_H_(0x92, 0x0D)
#define  REG_TC_SC1_SCMI_BK92_0E_L       _PK_L_(0x92, 0x0E)
#define  REG_TC_SC1_SCMI_BK92_0E_H       _PK_H_(0x92, 0x0E)
#define  REG_TC_SC1_SCMI_BK92_0F_L       _PK_L_(0x92, 0x0F)
#define  REG_TC_SC1_SCMI_BK92_0F_H       _PK_H_(0x92, 0x0F)
#define  REG_TC_SC1_SCMI_BK92_10_L       _PK_L_(0x92, 0x10)
#define  REG_TC_SC1_SCMI_BK92_10_H       _PK_H_(0x92, 0x10)
#define  REG_TC_SC1_SCMI_BK92_11_L       _PK_L_(0x92, 0x11)
#define  REG_TC_SC1_SCMI_BK92_11_H       _PK_H_(0x92, 0x11)
#define  REG_TC_SC1_SCMI_BK92_12_L       _PK_L_(0x92, 0x12)
#define  REG_TC_SC1_SCMI_BK92_12_H       _PK_H_(0x92, 0x12)
#define  REG_TC_SC1_SCMI_BK92_13_L       _PK_L_(0x92, 0x13)
#define  REG_TC_SC1_SCMI_BK92_13_H       _PK_H_(0x92, 0x13)
#define  REG_TC_SC1_SCMI_BK92_14_L       _PK_L_(0x92, 0x14)
#define  REG_TC_SC1_SCMI_BK92_14_H       _PK_H_(0x92, 0x14)
#define  REG_TC_SC1_SCMI_BK92_15_L       _PK_L_(0x92, 0x15)
#define  REG_TC_SC1_SCMI_BK92_15_H       _PK_H_(0x92, 0x15)
#define  REG_TC_SC1_SCMI_BK92_16_L       _PK_L_(0x92, 0x16)
#define  REG_TC_SC1_SCMI_BK92_16_H       _PK_H_(0x92, 0x16)
#define  REG_TC_SC1_SCMI_BK92_17_L       _PK_L_(0x92, 0x17)
#define  REG_TC_SC1_SCMI_BK92_17_H       _PK_H_(0x92, 0x17)
#define  REG_TC_SC1_SCMI_BK92_18_L       _PK_L_(0x92, 0x18)
#define  REG_TC_SC1_SCMI_BK92_18_H       _PK_H_(0x92, 0x18)
#define  REG_TC_SC1_SCMI_BK92_19_L       _PK_L_(0x92, 0x19)
#define  REG_TC_SC1_SCMI_BK92_19_H       _PK_H_(0x92, 0x19)
#define  REG_TC_SC1_SCMI_BK92_1A_L       _PK_L_(0x92, 0x1A)
#define  REG_TC_SC1_SCMI_BK92_1A_H       _PK_H_(0x92, 0x1A)
#define  REG_TC_SC1_SCMI_BK92_1B_L       _PK_L_(0x92, 0x1B)
#define  REG_TC_SC1_SCMI_BK92_1B_H       _PK_H_(0x92, 0x1B)
#define  REG_TC_SC1_SCMI_BK92_1C_L       _PK_L_(0x92, 0x1C)
#define  REG_TC_SC1_SCMI_BK92_1C_H       _PK_H_(0x92, 0x1C)
#define  REG_TC_SC1_SCMI_BK92_1D_L       _PK_L_(0x92, 0x1D)
#define  REG_TC_SC1_SCMI_BK92_1D_H       _PK_H_(0x92, 0x1D)
#define  REG_TC_SC1_SCMI_BK92_1E_L       _PK_L_(0x92, 0x1E)
#define  REG_TC_SC1_SCMI_BK92_1E_H       _PK_H_(0x92, 0x1E)
#define  REG_TC_SC1_SCMI_BK92_1F_L       _PK_L_(0x92, 0x1F)
#define  REG_TC_SC1_SCMI_BK92_1F_H       _PK_H_(0x92, 0x1F)
#define  REG_TC_SC1_SCMI_BK92_20_L       _PK_L_(0x92, 0x20)
#define  REG_TC_SC1_SCMI_BK92_20_H       _PK_H_(0x92, 0x20)
#define  REG_TC_SC1_SCMI_BK92_21_L       _PK_L_(0x92, 0x21)
#define  REG_TC_SC1_SCMI_BK92_21_H       _PK_H_(0x92, 0x21)
#define  REG_TC_SC1_SCMI_BK92_22_L       _PK_L_(0x92, 0x22)
#define  REG_TC_SC1_SCMI_BK92_22_H       _PK_H_(0x92, 0x22)
#define  REG_TC_SC1_SCMI_BK92_23_L       _PK_L_(0x92, 0x23)
#define  REG_TC_SC1_SCMI_BK92_23_H       _PK_H_(0x92, 0x23)
#define  REG_TC_SC1_SCMI_BK92_24_L       _PK_L_(0x92, 0x24)
#define  REG_TC_SC1_SCMI_BK92_24_H       _PK_H_(0x92, 0x24)
#define  REG_TC_SC1_SCMI_BK92_25_L       _PK_L_(0x92, 0x25)
#define  REG_TC_SC1_SCMI_BK92_25_H       _PK_H_(0x92, 0x25)
#define  REG_TC_SC1_SCMI_BK92_26_L       _PK_L_(0x92, 0x26)
#define  REG_TC_SC1_SCMI_BK92_26_H       _PK_H_(0x92, 0x26)
#define  REG_TC_SC1_SCMI_BK92_27_L       _PK_L_(0x92, 0x27)
#define  REG_TC_SC1_SCMI_BK92_27_H       _PK_H_(0x92, 0x27)
#define  REG_TC_SC1_SCMI_BK92_28_L       _PK_L_(0x92, 0x28)
#define  REG_TC_SC1_SCMI_BK92_28_H       _PK_H_(0x92, 0x28)
#define  REG_TC_SC1_SCMI_BK92_29_L       _PK_L_(0x92, 0x29)
#define  REG_TC_SC1_SCMI_BK92_29_H       _PK_H_(0x92, 0x29)
#define  REG_TC_SC1_SCMI_BK92_2A_L       _PK_L_(0x92, 0x2A)
#define  REG_TC_SC1_SCMI_BK92_2A_H       _PK_H_(0x92, 0x2A)
#define  REG_TC_SC1_SCMI_BK92_2B_L       _PK_L_(0x92, 0x2B)
#define  REG_TC_SC1_SCMI_BK92_2B_H       _PK_H_(0x92, 0x2B)
#define  REG_TC_SC1_SCMI_BK92_2C_L       _PK_L_(0x92, 0x2C)
#define  REG_TC_SC1_SCMI_BK92_2C_H       _PK_H_(0x92, 0x2C)
#define  REG_TC_SC1_SCMI_BK92_2D_L       _PK_L_(0x92, 0x2D)
#define  REG_TC_SC1_SCMI_BK92_2D_H       _PK_H_(0x92, 0x2D)
#define  REG_TC_SC1_SCMI_BK92_2E_L       _PK_L_(0x92, 0x2E)
#define  REG_TC_SC1_SCMI_BK92_2E_H       _PK_H_(0x92, 0x2E)
#define  REG_TC_SC1_SCMI_BK92_2F_L       _PK_L_(0x92, 0x2F)
#define  REG_TC_SC1_SCMI_BK92_2F_H       _PK_H_(0x92, 0x2F)
#define  REG_TC_SC1_SCMI_BK92_30_L       _PK_L_(0x92, 0x30)
#define  REG_TC_SC1_SCMI_BK92_30_H       _PK_H_(0x92, 0x30)
#define  REG_TC_SC1_SCMI_BK92_31_L       _PK_L_(0x92, 0x31)
#define  REG_TC_SC1_SCMI_BK92_31_H       _PK_H_(0x92, 0x31)
#define  REG_TC_SC1_SCMI_BK92_32_L       _PK_L_(0x92, 0x32)
#define  REG_TC_SC1_SCMI_BK92_32_H       _PK_H_(0x92, 0x32)
#define  REG_TC_SC1_SCMI_BK92_33_L       _PK_L_(0x92, 0x33)
#define  REG_TC_SC1_SCMI_BK92_33_H       _PK_H_(0x92, 0x33)
#define  REG_TC_SC1_SCMI_BK92_34_L       _PK_L_(0x92, 0x34)
#define  REG_TC_SC1_SCMI_BK92_34_H       _PK_H_(0x92, 0x34)
#define  REG_TC_SC1_SCMI_BK92_35_L       _PK_L_(0x92, 0x35)
#define  REG_TC_SC1_SCMI_BK92_35_H       _PK_H_(0x92, 0x35)
#define  REG_TC_SC1_SCMI_BK92_36_L       _PK_L_(0x92, 0x36)
#define  REG_TC_SC1_SCMI_BK92_36_H       _PK_H_(0x92, 0x36)
#define  REG_TC_SC1_SCMI_BK92_37_L       _PK_L_(0x92, 0x37)
#define  REG_TC_SC1_SCMI_BK92_37_H       _PK_H_(0x92, 0x37)
#define  REG_TC_SC1_SCMI_BK92_38_L       _PK_L_(0x92, 0x38)
#define  REG_TC_SC1_SCMI_BK92_38_H       _PK_H_(0x92, 0x38)
#define  REG_TC_SC1_SCMI_BK92_39_L       _PK_L_(0x92, 0x39)
#define  REG_TC_SC1_SCMI_BK92_39_H       _PK_H_(0x92, 0x39)
#define  REG_TC_SC1_SCMI_BK92_3A_L       _PK_L_(0x92, 0x3A)
#define  REG_TC_SC1_SCMI_BK92_3A_H       _PK_H_(0x92, 0x3A)
#define  REG_TC_SC1_SCMI_BK92_3B_L       _PK_L_(0x92, 0x3B)
#define  REG_TC_SC1_SCMI_BK92_3B_H       _PK_H_(0x92, 0x3B)
#define  REG_TC_SC1_SCMI_BK92_3C_L       _PK_L_(0x92, 0x3C)
#define  REG_TC_SC1_SCMI_BK92_3C_H       _PK_H_(0x92, 0x3C)
#define  REG_TC_SC1_SCMI_BK92_3D_L       _PK_L_(0x92, 0x3D)
#define  REG_TC_SC1_SCMI_BK92_3D_H       _PK_H_(0x92, 0x3D)
#define  REG_TC_SC1_SCMI_BK92_3E_L       _PK_L_(0x92, 0x3E)
#define  REG_TC_SC1_SCMI_BK92_3E_H       _PK_H_(0x92, 0x3E)
#define  REG_TC_SC1_SCMI_BK92_3F_L       _PK_L_(0x92, 0x3F)
#define  REG_TC_SC1_SCMI_BK92_3F_H       _PK_H_(0x92, 0x3F)
#define  REG_TC_SC1_SCMI_BK92_40_L       _PK_L_(0x92, 0x40)
#define  REG_TC_SC1_SCMI_BK92_40_H       _PK_H_(0x92, 0x40)
#define  REG_TC_SC1_SCMI_BK92_41_L       _PK_L_(0x92, 0x41)
#define  REG_TC_SC1_SCMI_BK92_41_H       _PK_H_(0x92, 0x41)
#define  REG_TC_SC1_SCMI_BK92_42_L       _PK_L_(0x92, 0x42)
#define  REG_TC_SC1_SCMI_BK92_42_H       _PK_H_(0x92, 0x42)
#define  REG_TC_SC1_SCMI_BK92_43_L       _PK_L_(0x92, 0x43)
#define  REG_TC_SC1_SCMI_BK92_43_H       _PK_H_(0x92, 0x43)
#define  REG_TC_SC1_SCMI_BK92_44_L       _PK_L_(0x92, 0x44)
#define  REG_TC_SC1_SCMI_BK92_44_H       _PK_H_(0x92, 0x44)
#define  REG_TC_SC1_SCMI_BK92_45_L       _PK_L_(0x92, 0x45)
#define  REG_TC_SC1_SCMI_BK92_45_H       _PK_H_(0x92, 0x45)
#define  REG_TC_SC1_SCMI_BK92_46_L       _PK_L_(0x92, 0x46)
#define  REG_TC_SC1_SCMI_BK92_46_H       _PK_H_(0x92, 0x46)
#define  REG_TC_SC1_SCMI_BK92_47_L       _PK_L_(0x92, 0x47)
#define  REG_TC_SC1_SCMI_BK92_47_H       _PK_H_(0x92, 0x47)
#define  REG_TC_SC1_SCMI_BK92_48_L       _PK_L_(0x92, 0x48)
#define  REG_TC_SC1_SCMI_BK92_48_H       _PK_H_(0x92, 0x48)
#define  REG_TC_SC1_SCMI_BK92_49_L       _PK_L_(0x92, 0x49)
#define  REG_TC_SC1_SCMI_BK92_49_H       _PK_H_(0x92, 0x49)
#define  REG_TC_SC1_SCMI_BK92_4A_L       _PK_L_(0x92, 0x4A)
#define  REG_TC_SC1_SCMI_BK92_4A_H       _PK_H_(0x92, 0x4A)
#define  REG_TC_SC1_SCMI_BK92_4B_L       _PK_L_(0x92, 0x4B)
#define  REG_TC_SC1_SCMI_BK92_4B_H       _PK_H_(0x92, 0x4B)
#define  REG_TC_SC1_SCMI_BK92_4C_L       _PK_L_(0x92, 0x4C)
#define  REG_TC_SC1_SCMI_BK92_4C_H       _PK_H_(0x92, 0x4C)
#define  REG_TC_SC1_SCMI_BK92_4D_L       _PK_L_(0x92, 0x4D)
#define  REG_TC_SC1_SCMI_BK92_4D_H       _PK_H_(0x92, 0x4D)
#define  REG_TC_SC1_SCMI_BK92_4E_L       _PK_L_(0x92, 0x4E)
#define  REG_TC_SC1_SCMI_BK92_4E_H       _PK_H_(0x92, 0x4E)
#define  REG_TC_SC1_SCMI_BK92_4F_L       _PK_L_(0x92, 0x4F)
#define  REG_TC_SC1_SCMI_BK92_4F_H       _PK_H_(0x92, 0x4F)
#define  REG_TC_SC1_SCMI_BK92_50_L       _PK_L_(0x92, 0x50)
#define  REG_TC_SC1_SCMI_BK92_50_H       _PK_H_(0x92, 0x50)
#define  REG_TC_SC1_SCMI_BK92_51_L       _PK_L_(0x92, 0x51)
#define  REG_TC_SC1_SCMI_BK92_51_H       _PK_H_(0x92, 0x51)
#define  REG_TC_SC1_SCMI_BK92_52_L       _PK_L_(0x92, 0x52)
#define  REG_TC_SC1_SCMI_BK92_52_H       _PK_H_(0x92, 0x52)
#define  REG_TC_SC1_SCMI_BK92_53_L       _PK_L_(0x92, 0x53)
#define  REG_TC_SC1_SCMI_BK92_53_H       _PK_H_(0x92, 0x53)
#define  REG_TC_SC1_SCMI_BK92_54_L       _PK_L_(0x92, 0x54)
#define  REG_TC_SC1_SCMI_BK92_54_H       _PK_H_(0x92, 0x54)
#define  REG_TC_SC1_SCMI_BK92_55_L       _PK_L_(0x92, 0x55)
#define  REG_TC_SC1_SCMI_BK92_55_H       _PK_H_(0x92, 0x55)
#define  REG_TC_SC1_SCMI_BK92_56_L       _PK_L_(0x92, 0x56)
#define  REG_TC_SC1_SCMI_BK92_56_H       _PK_H_(0x92, 0x56)
#define  REG_TC_SC1_SCMI_BK92_57_L       _PK_L_(0x92, 0x57)
#define  REG_TC_SC1_SCMI_BK92_57_H       _PK_H_(0x92, 0x57)
#define  REG_TC_SC1_SCMI_BK92_58_L       _PK_L_(0x92, 0x58)
#define  REG_TC_SC1_SCMI_BK92_58_H       _PK_H_(0x92, 0x58)
#define  REG_TC_SC1_SCMI_BK92_59_L       _PK_L_(0x92, 0x59)
#define  REG_TC_SC1_SCMI_BK92_59_H       _PK_H_(0x92, 0x59)
#define  REG_TC_SC1_SCMI_BK92_5A_L       _PK_L_(0x92, 0x5A)
#define  REG_TC_SC1_SCMI_BK92_5A_H       _PK_H_(0x92, 0x5A)
#define  REG_TC_SC1_SCMI_BK92_5B_L       _PK_L_(0x92, 0x5B)
#define  REG_TC_SC1_SCMI_BK92_5B_H       _PK_H_(0x92, 0x5B)
#define  REG_TC_SC1_SCMI_BK92_5C_L       _PK_L_(0x92, 0x5C)
#define  REG_TC_SC1_SCMI_BK92_5C_H       _PK_H_(0x92, 0x5C)
#define  REG_TC_SC1_SCMI_BK92_5D_L       _PK_L_(0x92, 0x5D)
#define  REG_TC_SC1_SCMI_BK92_5D_H       _PK_H_(0x92, 0x5D)
#define  REG_TC_SC1_SCMI_BK92_5E_L       _PK_L_(0x92, 0x5E)
#define  REG_TC_SC1_SCMI_BK92_5E_H       _PK_H_(0x92, 0x5E)
#define  REG_TC_SC1_SCMI_BK92_5F_L       _PK_L_(0x92, 0x5F)
#define  REG_TC_SC1_SCMI_BK92_5F_H       _PK_H_(0x92, 0x5F)
#define  REG_TC_SC1_SCMI_BK92_60_L       _PK_L_(0x92, 0x60)
#define  REG_TC_SC1_SCMI_BK92_60_H       _PK_H_(0x92, 0x60)
#define  REG_TC_SC1_SCMI_BK92_61_L       _PK_L_(0x92, 0x61)
#define  REG_TC_SC1_SCMI_BK92_61_H       _PK_H_(0x92, 0x61)
#define  REG_TC_SC1_SCMI_BK92_62_L       _PK_L_(0x92, 0x62)
#define  REG_TC_SC1_SCMI_BK92_62_H       _PK_H_(0x92, 0x62)
#define  REG_TC_SC1_SCMI_BK92_63_L       _PK_L_(0x92, 0x63)
#define  REG_TC_SC1_SCMI_BK92_63_H       _PK_H_(0x92, 0x63)
#define  REG_TC_SC1_SCMI_BK92_64_L       _PK_L_(0x92, 0x64)
#define  REG_TC_SC1_SCMI_BK92_64_H       _PK_H_(0x92, 0x64)
#define  REG_TC_SC1_SCMI_BK92_65_L       _PK_L_(0x92, 0x65)
#define  REG_TC_SC1_SCMI_BK92_65_H       _PK_H_(0x92, 0x65)
#define  REG_TC_SC1_SCMI_BK92_66_L       _PK_L_(0x92, 0x66)
#define  REG_TC_SC1_SCMI_BK92_66_H       _PK_H_(0x92, 0x66)
#define  REG_TC_SC1_SCMI_BK92_67_L       _PK_L_(0x92, 0x67)
#define  REG_TC_SC1_SCMI_BK92_67_H       _PK_H_(0x92, 0x67)
#define  REG_TC_SC1_SCMI_BK92_68_L       _PK_L_(0x92, 0x68)
#define  REG_TC_SC1_SCMI_BK92_68_H       _PK_H_(0x92, 0x68)
#define  REG_TC_SC1_SCMI_BK92_69_L       _PK_L_(0x92, 0x69)
#define  REG_TC_SC1_SCMI_BK92_69_H       _PK_H_(0x92, 0x69)
#define  REG_TC_SC1_SCMI_BK92_6A_L       _PK_L_(0x92, 0x6A)
#define  REG_TC_SC1_SCMI_BK92_6A_H       _PK_H_(0x92, 0x6A)
#define  REG_TC_SC1_SCMI_BK92_6B_L       _PK_L_(0x92, 0x6B)
#define  REG_TC_SC1_SCMI_BK92_6B_H       _PK_H_(0x92, 0x6B)
#define  REG_TC_SC1_SCMI_BK92_6C_L       _PK_L_(0x92, 0x6C)
#define  REG_TC_SC1_SCMI_BK92_6C_H       _PK_H_(0x92, 0x6C)
#define  REG_TC_SC1_SCMI_BK92_6D_L       _PK_L_(0x92, 0x6D)
#define  REG_TC_SC1_SCMI_BK92_6D_H       _PK_H_(0x92, 0x6D)
#define  REG_TC_SC1_SCMI_BK92_6E_L       _PK_L_(0x92, 0x6E)
#define  REG_TC_SC1_SCMI_BK92_6E_H       _PK_H_(0x92, 0x6E)
#define  REG_TC_SC1_SCMI_BK92_6F_L       _PK_L_(0x92, 0x6F)
#define  REG_TC_SC1_SCMI_BK92_6F_H       _PK_H_(0x92, 0x6F)
#define  REG_TC_SC1_SCMI_BK92_70_L       _PK_L_(0x92, 0x70)
#define  REG_TC_SC1_SCMI_BK92_70_H       _PK_H_(0x92, 0x70)
#define  REG_TC_SC1_SCMI_BK92_71_L       _PK_L_(0x92, 0x71)
#define  REG_TC_SC1_SCMI_BK92_71_H       _PK_H_(0x92, 0x71)
#define  REG_TC_SC1_SCMI_BK92_72_L       _PK_L_(0x92, 0x72)
#define  REG_TC_SC1_SCMI_BK92_72_H       _PK_H_(0x92, 0x72)
#define  REG_TC_SC1_SCMI_BK92_73_L       _PK_L_(0x92, 0x73)
#define  REG_TC_SC1_SCMI_BK92_73_H       _PK_H_(0x92, 0x73)
#define  REG_TC_SC1_SCMI_BK92_74_L       _PK_L_(0x92, 0x74)
#define  REG_TC_SC1_SCMI_BK92_74_H       _PK_H_(0x92, 0x74)
#define  REG_TC_SC1_SCMI_BK92_75_L       _PK_L_(0x92, 0x75)
#define  REG_TC_SC1_SCMI_BK92_75_H       _PK_H_(0x92, 0x75)
#define  REG_TC_SC1_SCMI_BK92_76_L       _PK_L_(0x92, 0x76)
#define  REG_TC_SC1_SCMI_BK92_76_H       _PK_H_(0x92, 0x76)
#define  REG_TC_SC1_SCMI_BK92_77_L       _PK_L_(0x92, 0x77)
#define  REG_TC_SC1_SCMI_BK92_77_H       _PK_H_(0x92, 0x77)
#define  REG_TC_SC1_SCMI_BK92_78_L       _PK_L_(0x92, 0x78)
#define  REG_TC_SC1_SCMI_BK92_78_H       _PK_H_(0x92, 0x78)
#define  REG_TC_SC1_SCMI_BK92_79_L       _PK_L_(0x92, 0x79)
#define  REG_TC_SC1_SCMI_BK92_79_H       _PK_H_(0x92, 0x79)
#define  REG_TC_SC1_SCMI_BK92_7A_L       _PK_L_(0x92, 0x7A)
#define  REG_TC_SC1_SCMI_BK92_7A_H       _PK_H_(0x92, 0x7A)
#define  REG_TC_SC1_SCMI_BK92_7B_L       _PK_L_(0x92, 0x7B)
#define  REG_TC_SC1_SCMI_BK92_7B_H       _PK_H_(0x92, 0x7B)
#define  REG_TC_SC1_SCMI_BK92_7C_L       _PK_L_(0x92, 0x7C)
#define  REG_TC_SC1_SCMI_BK92_7C_H       _PK_H_(0x92, 0x7C)
#define  REG_TC_SC1_SCMI_BK92_7D_L       _PK_L_(0x92, 0x7D)
#define  REG_TC_SC1_SCMI_BK92_7D_H       _PK_H_(0x92, 0x7D)
#define  REG_TC_SC1_SCMI_BK92_7E_L       _PK_L_(0x92, 0x7E)
#define  REG_TC_SC1_SCMI_BK92_7E_H       _PK_H_(0x92, 0x7E)
#define  REG_TC_SC1_SCMI_BK92_7F_L       _PK_L_(0x92, 0x7F)
#define  REG_TC_SC1_SCMI_BK92_7F_H       _PK_H_(0x92, 0x7F)

#define  REG_TC_MOD_BK00_00_L       _PK_L_(0x00, 0x00)
#define  REG_TC_MOD_BK00_00_H       _PK_H_(0x00, 0x00)
#define  REG_TC_MOD_BK00_01_L       _PK_L_(0x00, 0x01)
#define  REG_TC_MOD_BK00_01_H       _PK_H_(0x00, 0x01)
#define  REG_TC_MOD_BK00_02_L       _PK_L_(0x00, 0x02)
#define  REG_TC_MOD_BK00_02_H       _PK_H_(0x00, 0x02)
#define  REG_TC_MOD_BK00_03_L       _PK_L_(0x00, 0x03)
#define  REG_TC_MOD_BK00_03_H       _PK_H_(0x00, 0x03)
#define  REG_TC_MOD_BK00_04_L       _PK_L_(0x00, 0x04)
#define  REG_TC_MOD_BK00_04_H       _PK_H_(0x00, 0x04)
#define  REG_TC_MOD_BK00_05_L       _PK_L_(0x00, 0x05)
#define  REG_TC_MOD_BK00_05_H       _PK_H_(0x00, 0x05)
#define  REG_TC_MOD_BK00_06_L       _PK_L_(0x00, 0x06)
#define  REG_TC_MOD_BK00_06_H       _PK_H_(0x00, 0x06)
#define  REG_TC_MOD_BK00_07_L       _PK_L_(0x00, 0x07)
#define  REG_TC_MOD_BK00_07_H       _PK_H_(0x00, 0x07)
#define  REG_TC_MOD_BK00_08_L       _PK_L_(0x00, 0x08)
#define  REG_TC_MOD_BK00_08_H       _PK_H_(0x00, 0x08)
#define  REG_TC_MOD_BK00_09_L       _PK_L_(0x00, 0x09)
#define  REG_TC_MOD_BK00_09_H       _PK_H_(0x00, 0x09)
#define  REG_TC_MOD_BK00_0A_L       _PK_L_(0x00, 0x0A)
#define  REG_TC_MOD_BK00_0A_H       _PK_H_(0x00, 0x0A)
#define  REG_TC_MOD_BK00_0B_L       _PK_L_(0x00, 0x0B)
#define  REG_TC_MOD_BK00_0B_H       _PK_H_(0x00, 0x0B)
#define  REG_TC_MOD_BK00_0C_L       _PK_L_(0x00, 0x0C)
#define  REG_TC_MOD_BK00_0C_H       _PK_H_(0x00, 0x0C)
#define  REG_TC_MOD_BK00_0D_L       _PK_L_(0x00, 0x0D)
#define  REG_TC_MOD_BK00_0D_H       _PK_H_(0x00, 0x0D)
#define  REG_TC_MOD_BK00_0E_L       _PK_L_(0x00, 0x0E)
#define  REG_TC_MOD_BK00_0E_H       _PK_H_(0x00, 0x0E)
#define  REG_TC_MOD_BK00_0F_L       _PK_L_(0x00, 0x0F)
#define  REG_TC_MOD_BK00_0F_H       _PK_H_(0x00, 0x0F)
#define  REG_TC_MOD_BK00_10_L       _PK_L_(0x00, 0x10)
#define  REG_TC_MOD_BK00_10_H       _PK_H_(0x00, 0x10)
#define  REG_TC_MOD_BK00_11_L       _PK_L_(0x00, 0x11)
#define  REG_TC_MOD_BK00_11_H       _PK_H_(0x00, 0x11)
#define  REG_TC_MOD_BK00_12_L       _PK_L_(0x00, 0x12)
#define  REG_TC_MOD_BK00_12_H       _PK_H_(0x00, 0x12)
#define  REG_TC_MOD_BK00_13_L       _PK_L_(0x00, 0x13)
#define  REG_TC_MOD_BK00_13_H       _PK_H_(0x00, 0x13)
#define  REG_TC_MOD_BK00_14_L       _PK_L_(0x00, 0x14)
#define  REG_TC_MOD_BK00_14_H       _PK_H_(0x00, 0x14)
#define  REG_TC_MOD_BK00_15_L       _PK_L_(0x00, 0x15)
#define  REG_TC_MOD_BK00_15_H       _PK_H_(0x00, 0x15)
#define  REG_TC_MOD_BK00_16_L       _PK_L_(0x00, 0x16)
#define  REG_TC_MOD_BK00_16_H       _PK_H_(0x00, 0x16)
#define  REG_TC_MOD_BK00_17_L       _PK_L_(0x00, 0x17)
#define  REG_TC_MOD_BK00_17_H       _PK_H_(0x00, 0x17)
#define  REG_TC_MOD_BK00_18_L       _PK_L_(0x00, 0x18)
#define  REG_TC_MOD_BK00_18_H       _PK_H_(0x00, 0x18)
#define  REG_TC_MOD_BK00_19_L       _PK_L_(0x00, 0x19)
#define  REG_TC_MOD_BK00_19_H       _PK_H_(0x00, 0x19)
#define  REG_TC_MOD_BK00_1A_L       _PK_L_(0x00, 0x1A)
#define  REG_TC_MOD_BK00_1A_H       _PK_H_(0x00, 0x1A)
#define  REG_TC_MOD_BK00_1B_L       _PK_L_(0x00, 0x1B)
#define  REG_TC_MOD_BK00_1B_H       _PK_H_(0x00, 0x1B)
#define  REG_TC_MOD_BK00_1C_L       _PK_L_(0x00, 0x1C)
#define  REG_TC_MOD_BK00_1C_H       _PK_H_(0x00, 0x1C)
#define  REG_TC_MOD_BK00_1D_L       _PK_L_(0x00, 0x1D)
#define  REG_TC_MOD_BK00_1D_H       _PK_H_(0x00, 0x1D)
#define  REG_TC_MOD_BK00_1E_L       _PK_L_(0x00, 0x1E)
#define  REG_TC_MOD_BK00_1E_H       _PK_H_(0x00, 0x1E)
#define  REG_TC_MOD_BK00_1F_L       _PK_L_(0x00, 0x1F)
#define  REG_TC_MOD_BK00_1F_H       _PK_H_(0x00, 0x1F)
#define  REG_TC_MOD_BK00_20_L       _PK_L_(0x00, 0x20)
#define  REG_TC_MOD_BK00_20_H       _PK_H_(0x00, 0x20)
#define  REG_TC_MOD_BK00_21_L       _PK_L_(0x00, 0x21)
#define  REG_TC_MOD_BK00_21_H       _PK_H_(0x00, 0x21)
#define  REG_TC_MOD_BK00_22_L       _PK_L_(0x00, 0x22)
#define  REG_TC_MOD_BK00_22_H       _PK_H_(0x00, 0x22)
#define  REG_TC_MOD_BK00_23_L       _PK_L_(0x00, 0x23)
#define  REG_TC_MOD_BK00_23_H       _PK_H_(0x00, 0x23)
#define  REG_TC_MOD_BK00_24_L       _PK_L_(0x00, 0x24)
#define  REG_TC_MOD_BK00_24_H       _PK_H_(0x00, 0x24)
#define  REG_TC_MOD_BK00_25_L       _PK_L_(0x00, 0x25)
#define  REG_TC_MOD_BK00_25_H       _PK_H_(0x00, 0x25)
#define  REG_TC_MOD_BK00_26_L       _PK_L_(0x00, 0x26)
#define  REG_TC_MOD_BK00_26_H       _PK_H_(0x00, 0x26)
#define  REG_TC_MOD_BK00_27_L       _PK_L_(0x00, 0x27)
#define  REG_TC_MOD_BK00_27_H       _PK_H_(0x00, 0x27)
#define  REG_TC_MOD_BK00_28_L       _PK_L_(0x00, 0x28)
#define  REG_TC_MOD_BK00_28_H       _PK_H_(0x00, 0x28)
#define  REG_TC_MOD_BK00_29_L       _PK_L_(0x00, 0x29)
#define  REG_TC_MOD_BK00_29_H       _PK_H_(0x00, 0x29)
#define  REG_TC_MOD_BK00_2A_L       _PK_L_(0x00, 0x2A)
#define  REG_TC_MOD_BK00_2A_H       _PK_H_(0x00, 0x2A)
#define  REG_TC_MOD_BK00_2B_L       _PK_L_(0x00, 0x2B)
#define  REG_TC_MOD_BK00_2B_H       _PK_H_(0x00, 0x2B)
#define  REG_TC_MOD_BK00_2C_L       _PK_L_(0x00, 0x2C)
#define  REG_TC_MOD_BK00_2C_H       _PK_H_(0x00, 0x2C)
#define  REG_TC_MOD_BK00_2D_L       _PK_L_(0x00, 0x2D)
#define  REG_TC_MOD_BK00_2D_H       _PK_H_(0x00, 0x2D)
#define  REG_TC_MOD_BK00_2E_L       _PK_L_(0x00, 0x2E)
#define  REG_TC_MOD_BK00_2E_H       _PK_H_(0x00, 0x2E)
#define  REG_TC_MOD_BK00_2F_L       _PK_L_(0x00, 0x2F)
#define  REG_TC_MOD_BK00_2F_H       _PK_H_(0x00, 0x2F)
#define  REG_TC_MOD_BK00_30_L       _PK_L_(0x00, 0x30)
#define  REG_TC_MOD_BK00_30_H       _PK_H_(0x00, 0x30)
#define  REG_TC_MOD_BK00_31_L       _PK_L_(0x00, 0x31)
#define  REG_TC_MOD_BK00_31_H       _PK_H_(0x00, 0x31)
#define  REG_TC_MOD_BK00_32_L       _PK_L_(0x00, 0x32)
#define  REG_TC_MOD_BK00_32_H       _PK_H_(0x00, 0x32)
#define  REG_TC_MOD_BK00_33_L       _PK_L_(0x00, 0x33)
#define  REG_TC_MOD_BK00_33_H       _PK_H_(0x00, 0x33)
#define  REG_TC_MOD_BK00_34_L       _PK_L_(0x00, 0x34)
#define  REG_TC_MOD_BK00_34_H       _PK_H_(0x00, 0x34)
#define  REG_TC_MOD_BK00_35_L       _PK_L_(0x00, 0x35)
#define  REG_TC_MOD_BK00_35_H       _PK_H_(0x00, 0x35)
#define  REG_TC_MOD_BK00_36_L       _PK_L_(0x00, 0x36)
#define  REG_TC_MOD_BK00_36_H       _PK_H_(0x00, 0x36)
#define  REG_TC_MOD_BK00_37_L       _PK_L_(0x00, 0x37)
#define  REG_TC_MOD_BK00_37_H       _PK_H_(0x00, 0x37)
#define  REG_TC_MOD_BK00_38_L       _PK_L_(0x00, 0x38)
#define  REG_TC_MOD_BK00_38_H       _PK_H_(0x00, 0x38)
#define  REG_TC_MOD_BK00_39_L       _PK_L_(0x00, 0x39)
#define  REG_TC_MOD_BK00_39_H       _PK_H_(0x00, 0x39)
#define  REG_TC_MOD_BK00_3A_L       _PK_L_(0x00, 0x3A)
#define  REG_TC_MOD_BK00_3A_H       _PK_H_(0x00, 0x3A)
#define  REG_TC_MOD_BK00_3B_L       _PK_L_(0x00, 0x3B)
#define  REG_TC_MOD_BK00_3B_H       _PK_H_(0x00, 0x3B)
#define  REG_TC_MOD_BK00_3C_L       _PK_L_(0x00, 0x3C)
#define  REG_TC_MOD_BK00_3C_H       _PK_H_(0x00, 0x3C)
#define  REG_TC_MOD_BK00_3D_L       _PK_L_(0x00, 0x3D)
#define  REG_TC_MOD_BK00_3D_H       _PK_H_(0x00, 0x3D)
#define  REG_TC_MOD_BK00_3E_L       _PK_L_(0x00, 0x3E)
#define  REG_TC_MOD_BK00_3E_H       _PK_H_(0x00, 0x3E)
#define  REG_TC_MOD_BK00_3F_L       _PK_L_(0x00, 0x3F)
#define  REG_TC_MOD_BK00_3F_H       _PK_H_(0x00, 0x3F)
#define  REG_TC_MOD_BK00_40_L       _PK_L_(0x00, 0x40)
#define  REG_TC_MOD_BK00_40_H       _PK_H_(0x00, 0x40)
#define  REG_TC_MOD_BK00_41_L       _PK_L_(0x00, 0x41)
#define  REG_TC_MOD_BK00_41_H       _PK_H_(0x00, 0x41)
#define  REG_TC_MOD_BK00_42_L       _PK_L_(0x00, 0x42)
#define  REG_TC_MOD_BK00_42_H       _PK_H_(0x00, 0x42)
#define  REG_TC_MOD_BK00_43_L       _PK_L_(0x00, 0x43)
#define  REG_TC_MOD_BK00_43_H       _PK_H_(0x00, 0x43)
#define  REG_TC_MOD_BK00_44_L       _PK_L_(0x00, 0x44)
#define  REG_TC_MOD_BK00_44_H       _PK_H_(0x00, 0x44)
#define  REG_TC_MOD_BK00_45_L       _PK_L_(0x00, 0x45)
#define  REG_TC_MOD_BK00_45_H       _PK_H_(0x00, 0x45)
#define  REG_TC_MOD_BK00_46_L       _PK_L_(0x00, 0x46)
#define  REG_TC_MOD_BK00_46_H       _PK_H_(0x00, 0x46)
#define  REG_TC_MOD_BK00_47_L       _PK_L_(0x00, 0x47)
#define  REG_TC_MOD_BK00_47_H       _PK_H_(0x00, 0x47)
#define  REG_TC_MOD_BK00_48_L       _PK_L_(0x00, 0x48)
#define  REG_TC_MOD_BK00_48_H       _PK_H_(0x00, 0x48)
#define  REG_TC_MOD_BK00_49_L       _PK_L_(0x00, 0x49)
#define  REG_TC_MOD_BK00_49_H       _PK_H_(0x00, 0x49)
#define  REG_TC_MOD_BK00_4A_L       _PK_L_(0x00, 0x4A)
#define  REG_TC_MOD_BK00_4A_H       _PK_H_(0x00, 0x4A)
#define  REG_TC_MOD_BK00_4B_L       _PK_L_(0x00, 0x4B)
#define  REG_TC_MOD_BK00_4B_H       _PK_H_(0x00, 0x4B)
#define  REG_TC_MOD_BK00_4C_L       _PK_L_(0x00, 0x4C)
#define  REG_TC_MOD_BK00_4C_H       _PK_H_(0x00, 0x4C)
#define  REG_TC_MOD_BK00_4D_L       _PK_L_(0x00, 0x4D)
#define  REG_TC_MOD_BK00_4D_H       _PK_H_(0x00, 0x4D)
#define  REG_TC_MOD_BK00_4E_L       _PK_L_(0x00, 0x4E)
#define  REG_TC_MOD_BK00_4E_H       _PK_H_(0x00, 0x4E)
#define  REG_TC_MOD_BK00_4F_L       _PK_L_(0x00, 0x4F)
#define  REG_TC_MOD_BK00_4F_H       _PK_H_(0x00, 0x4F)
#define  REG_TC_MOD_BK00_50_L       _PK_L_(0x00, 0x50)
#define  REG_TC_MOD_BK00_50_H       _PK_H_(0x00, 0x50)
#define  REG_TC_MOD_BK00_51_L       _PK_L_(0x00, 0x51)
#define  REG_TC_MOD_BK00_51_H       _PK_H_(0x00, 0x51)
#define  REG_TC_MOD_BK00_52_L       _PK_L_(0x00, 0x52)
#define  REG_TC_MOD_BK00_52_H       _PK_H_(0x00, 0x52)
#define  REG_TC_MOD_BK00_53_L       _PK_L_(0x00, 0x53)
#define  REG_TC_MOD_BK00_53_H       _PK_H_(0x00, 0x53)
#define  REG_TC_MOD_BK00_54_L       _PK_L_(0x00, 0x54)
#define  REG_TC_MOD_BK00_54_H       _PK_H_(0x00, 0x54)
#define  REG_TC_MOD_BK00_55_L       _PK_L_(0x00, 0x55)
#define  REG_TC_MOD_BK00_55_H       _PK_H_(0x00, 0x55)
#define  REG_TC_MOD_BK00_56_L       _PK_L_(0x00, 0x56)
#define  REG_TC_MOD_BK00_56_H       _PK_H_(0x00, 0x56)
#define  REG_TC_MOD_BK00_57_L       _PK_L_(0x00, 0x57)
#define  REG_TC_MOD_BK00_57_H       _PK_H_(0x00, 0x57)
#define  REG_TC_MOD_BK00_58_L       _PK_L_(0x00, 0x58)
#define  REG_TC_MOD_BK00_58_H       _PK_H_(0x00, 0x58)
#define  REG_TC_MOD_BK00_59_L       _PK_L_(0x00, 0x59)
#define  REG_TC_MOD_BK00_59_H       _PK_H_(0x00, 0x59)
#define  REG_TC_MOD_BK00_5A_L       _PK_L_(0x00, 0x5A)
#define  REG_TC_MOD_BK00_5A_H       _PK_H_(0x00, 0x5A)
#define  REG_TC_MOD_BK00_5B_L       _PK_L_(0x00, 0x5B)
#define  REG_TC_MOD_BK00_5B_H       _PK_H_(0x00, 0x5B)
#define  REG_TC_MOD_BK00_5C_L       _PK_L_(0x00, 0x5C)
#define  REG_TC_MOD_BK00_5C_H       _PK_H_(0x00, 0x5C)
#define  REG_TC_MOD_BK00_5D_L       _PK_L_(0x00, 0x5D)
#define  REG_TC_MOD_BK00_5D_H       _PK_H_(0x00, 0x5D)
#define  REG_TC_MOD_BK00_5E_L       _PK_L_(0x00, 0x5E)
#define  REG_TC_MOD_BK00_5E_H       _PK_H_(0x00, 0x5E)
#define  REG_TC_MOD_BK00_5F_L       _PK_L_(0x00, 0x5F)
#define  REG_TC_MOD_BK00_5F_H       _PK_H_(0x00, 0x5F)
#define  REG_TC_MOD_BK00_60_L       _PK_L_(0x00, 0x60)
#define  REG_TC_MOD_BK00_60_H       _PK_H_(0x00, 0x60)
#define  REG_TC_MOD_BK00_61_L       _PK_L_(0x00, 0x61)
#define  REG_TC_MOD_BK00_61_H       _PK_H_(0x00, 0x61)
#define  REG_TC_MOD_BK00_62_L       _PK_L_(0x00, 0x62)
#define  REG_TC_MOD_BK00_62_H       _PK_H_(0x00, 0x62)
#define  REG_TC_MOD_BK00_63_L       _PK_L_(0x00, 0x63)
#define  REG_TC_MOD_BK00_63_H       _PK_H_(0x00, 0x63)
#define  REG_TC_MOD_BK00_64_L       _PK_L_(0x00, 0x64)
#define  REG_TC_MOD_BK00_64_H       _PK_H_(0x00, 0x64)
#define  REG_TC_MOD_BK00_65_L       _PK_L_(0x00, 0x65)
#define  REG_TC_MOD_BK00_65_H       _PK_H_(0x00, 0x65)
#define  REG_TC_MOD_BK00_66_L       _PK_L_(0x00, 0x66)
#define  REG_TC_MOD_BK00_66_H       _PK_H_(0x00, 0x66)
#define  REG_TC_MOD_BK00_67_L       _PK_L_(0x00, 0x67)
#define  REG_TC_MOD_BK00_67_H       _PK_H_(0x00, 0x67)
#define  REG_TC_MOD_BK00_68_L       _PK_L_(0x00, 0x68)
#define  REG_TC_MOD_BK00_68_H       _PK_H_(0x00, 0x68)
#define  REG_TC_MOD_BK00_69_L       _PK_L_(0x00, 0x69)
#define  REG_TC_MOD_BK00_69_H       _PK_H_(0x00, 0x69)
#define  REG_TC_MOD_BK00_6A_L       _PK_L_(0x00, 0x6A)
#define  REG_TC_MOD_BK00_6A_H       _PK_H_(0x00, 0x6A)
#define  REG_TC_MOD_BK00_6B_L       _PK_L_(0x00, 0x6B)
#define  REG_TC_MOD_BK00_6B_H       _PK_H_(0x00, 0x6B)
#define  REG_TC_MOD_BK00_6C_L       _PK_L_(0x00, 0x6C)
#define  REG_TC_MOD_BK00_6C_H       _PK_H_(0x00, 0x6C)
#define  REG_TC_MOD_BK00_6D_L       _PK_L_(0x00, 0x6D)
#define  REG_TC_MOD_BK00_6D_H       _PK_H_(0x00, 0x6D)
#define  REG_TC_MOD_BK00_6E_L       _PK_L_(0x00, 0x6E)
#define  REG_TC_MOD_BK00_6E_H       _PK_H_(0x00, 0x6E)
#define  REG_TC_MOD_BK00_6F_L       _PK_L_(0x00, 0x6F)
#define  REG_TC_MOD_BK00_6F_H       _PK_H_(0x00, 0x6F)
#define  REG_TC_MOD_BK00_70_L       _PK_L_(0x00, 0x70)
#define  REG_TC_MOD_BK00_70_H       _PK_H_(0x00, 0x70)
#define  REG_TC_MOD_BK00_71_L       _PK_L_(0x00, 0x71)
#define  REG_TC_MOD_BK00_71_H       _PK_H_(0x00, 0x71)
#define  REG_TC_MOD_BK00_72_L       _PK_L_(0x00, 0x72)
#define  REG_TC_MOD_BK00_72_H       _PK_H_(0x00, 0x72)
#define  REG_TC_MOD_BK00_73_L       _PK_L_(0x00, 0x73)
#define  REG_TC_MOD_BK00_73_H       _PK_H_(0x00, 0x73)
#define  REG_TC_MOD_BK00_74_L       _PK_L_(0x00, 0x74)
#define  REG_TC_MOD_BK00_74_H       _PK_H_(0x00, 0x74)
#define  REG_TC_MOD_BK00_75_L       _PK_L_(0x00, 0x75)
#define  REG_TC_MOD_BK00_75_H       _PK_H_(0x00, 0x75)
#define  REG_TC_MOD_BK00_76_L       _PK_L_(0x00, 0x76)
#define  REG_TC_MOD_BK00_76_H       _PK_H_(0x00, 0x76)
#define  REG_TC_MOD_BK00_77_L       _PK_L_(0x00, 0x77)
#define  REG_TC_MOD_BK00_77_H       _PK_H_(0x00, 0x77)
#define  REG_TC_MOD_BK00_78_L       _PK_L_(0x00, 0x78)
#define  REG_TC_MOD_BK00_78_H       _PK_H_(0x00, 0x78)
#define  REG_TC_MOD_BK00_79_L       _PK_L_(0x00, 0x79)
#define  REG_TC_MOD_BK00_79_H       _PK_H_(0x00, 0x79)
#define  REG_TC_MOD_BK00_7A_L       _PK_L_(0x00, 0x7A)
#define  REG_TC_MOD_BK00_7A_H       _PK_H_(0x00, 0x7A)
#define  REG_TC_MOD_BK00_7B_L       _PK_L_(0x00, 0x7B)
#define  REG_TC_MOD_BK00_7B_H       _PK_H_(0x00, 0x7B)
#define  REG_TC_MOD_BK00_7C_L       _PK_L_(0x00, 0x7C)
#define  REG_TC_MOD_BK00_7C_H       _PK_H_(0x00, 0x7C)
#define  REG_TC_MOD_BK00_7D_L       _PK_L_(0x00, 0x7D)
#define  REG_TC_MOD_BK00_7D_H       _PK_H_(0x00, 0x7D)
#define  REG_TC_MOD_BK00_7E_L       _PK_L_(0x00, 0x7E)
#define  REG_TC_MOD_BK00_7E_H       _PK_H_(0x00, 0x7E)
#define  REG_TC_MOD_BK00_7F_L       _PK_L_(0x00, 0x7F)
#define  REG_TC_MOD_BK00_7F_H       _PK_H_(0x00, 0x7F)

#define  REG_TC_P2I_BK2_00_L       _PK_L_(0x2, 0x00)
#define  REG_TC_P2I_BK2_00_H       _PK_H_(0x2, 0x00)
#define  REG_TC_P2I_BK2_01_L       _PK_L_(0x2, 0x01)
#define  REG_TC_P2I_BK2_01_H       _PK_H_(0x2, 0x01)
#define  REG_TC_P2I_BK2_02_L       _PK_L_(0x2, 0x02)
#define  REG_TC_P2I_BK2_02_H       _PK_H_(0x2, 0x02)
#define  REG_TC_P2I_BK2_03_L       _PK_L_(0x2, 0x03)
#define  REG_TC_P2I_BK2_03_H       _PK_H_(0x2, 0x03)
#define  REG_TC_P2I_BK2_04_L       _PK_L_(0x2, 0x04)
#define  REG_TC_P2I_BK2_04_H       _PK_H_(0x2, 0x04)
#define  REG_TC_P2I_BK2_05_L       _PK_L_(0x2, 0x05)
#define  REG_TC_P2I_BK2_05_H       _PK_H_(0x2, 0x05)
#define  REG_TC_P2I_BK2_06_L       _PK_L_(0x2, 0x06)
#define  REG_TC_P2I_BK2_06_H       _PK_H_(0x2, 0x06)
#define  REG_TC_P2I_BK2_07_L       _PK_L_(0x2, 0x07)
#define  REG_TC_P2I_BK2_07_H       _PK_H_(0x2, 0x07)
#define  REG_TC_P2I_BK2_08_L       _PK_L_(0x2, 0x08)
#define  REG_TC_P2I_BK2_08_H       _PK_H_(0x2, 0x08)
#define  REG_TC_P2I_BK2_09_L       _PK_L_(0x2, 0x09)
#define  REG_TC_P2I_BK2_09_H       _PK_H_(0x2, 0x09)
#define  REG_TC_P2I_BK2_0A_L       _PK_L_(0x2, 0x0A)
#define  REG_TC_P2I_BK2_0A_H       _PK_H_(0x2, 0x0A)
#define  REG_TC_P2I_BK2_0B_L       _PK_L_(0x2, 0x0B)
#define  REG_TC_P2I_BK2_0B_H       _PK_H_(0x2, 0x0B)
#define  REG_TC_P2I_BK2_0C_L       _PK_L_(0x2, 0x0C)
#define  REG_TC_P2I_BK2_0C_H       _PK_H_(0x2, 0x0C)
#define  REG_TC_P2I_BK2_0D_L       _PK_L_(0x2, 0x0D)
#define  REG_TC_P2I_BK2_0D_H       _PK_H_(0x2, 0x0D)
#define  REG_TC_P2I_BK2_0E_L       _PK_L_(0x2, 0x0E)
#define  REG_TC_P2I_BK2_0E_H       _PK_H_(0x2, 0x0E)
#define  REG_TC_P2I_BK2_0F_L       _PK_L_(0x2, 0x0F)
#define  REG_TC_P2I_BK2_0F_H       _PK_H_(0x2, 0x0F)
#define  REG_TC_P2I_BK2_10_L       _PK_L_(0x2, 0x10)
#define  REG_TC_P2I_BK2_10_H       _PK_H_(0x2, 0x10)
#define  REG_TC_P2I_BK2_11_L       _PK_L_(0x2, 0x11)
#define  REG_TC_P2I_BK2_11_H       _PK_H_(0x2, 0x11)
#define  REG_TC_P2I_BK2_12_L       _PK_L_(0x2, 0x12)
#define  REG_TC_P2I_BK2_12_H       _PK_H_(0x2, 0x12)
#define  REG_TC_P2I_BK2_13_L       _PK_L_(0x2, 0x13)
#define  REG_TC_P2I_BK2_13_H       _PK_H_(0x2, 0x13)
#define  REG_TC_P2I_BK2_14_L       _PK_L_(0x2, 0x14)
#define  REG_TC_P2I_BK2_14_H       _PK_H_(0x2, 0x14)
#define  REG_TC_P2I_BK2_15_L       _PK_L_(0x2, 0x15)
#define  REG_TC_P2I_BK2_15_H       _PK_H_(0x2, 0x15)
#define  REG_TC_P2I_BK2_16_L       _PK_L_(0x2, 0x16)
#define  REG_TC_P2I_BK2_16_H       _PK_H_(0x2, 0x16)
#define  REG_TC_P2I_BK2_17_L       _PK_L_(0x2, 0x17)
#define  REG_TC_P2I_BK2_17_H       _PK_H_(0x2, 0x17)
#define  REG_TC_P2I_BK2_18_L       _PK_L_(0x2, 0x18)
#define  REG_TC_P2I_BK2_18_H       _PK_H_(0x2, 0x18)
#define  REG_TC_P2I_BK2_19_L       _PK_L_(0x2, 0x19)
#define  REG_TC_P2I_BK2_19_H       _PK_H_(0x2, 0x19)
#define  REG_TC_P2I_BK2_1A_L       _PK_L_(0x2, 0x1A)
#define  REG_TC_P2I_BK2_1A_H       _PK_H_(0x2, 0x1A)
#define  REG_TC_P2I_BK2_1B_L       _PK_L_(0x2, 0x1B)
#define  REG_TC_P2I_BK2_1B_H       _PK_H_(0x2, 0x1B)
#define  REG_TC_P2I_BK2_1C_L       _PK_L_(0x2, 0x1C)
#define  REG_TC_P2I_BK2_1C_H       _PK_H_(0x2, 0x1C)
#define  REG_TC_P2I_BK2_1D_L       _PK_L_(0x2, 0x1D)
#define  REG_TC_P2I_BK2_1D_H       _PK_H_(0x2, 0x1D)
#define  REG_TC_P2I_BK2_1E_L       _PK_L_(0x2, 0x1E)
#define  REG_TC_P2I_BK2_1E_H       _PK_H_(0x2, 0x1E)
#define  REG_TC_P2I_BK2_1F_L       _PK_L_(0x2, 0x1F)
#define  REG_TC_P2I_BK2_1F_H       _PK_H_(0x2, 0x1F)
#define  REG_TC_P2I_BK2_20_L       _PK_L_(0x2, 0x20)
#define  REG_TC_P2I_BK2_20_H       _PK_H_(0x2, 0x20)
#define  REG_TC_P2I_BK2_21_L       _PK_L_(0x2, 0x21)
#define  REG_TC_P2I_BK2_21_H       _PK_H_(0x2, 0x21)
#define  REG_TC_P2I_BK2_22_L       _PK_L_(0x2, 0x22)
#define  REG_TC_P2I_BK2_22_H       _PK_H_(0x2, 0x22)
#define  REG_TC_P2I_BK2_23_L       _PK_L_(0x2, 0x23)
#define  REG_TC_P2I_BK2_23_H       _PK_H_(0x2, 0x23)
#define  REG_TC_P2I_BK2_24_L       _PK_L_(0x2, 0x24)
#define  REG_TC_P2I_BK2_24_H       _PK_H_(0x2, 0x24)
#define  REG_TC_P2I_BK2_25_L       _PK_L_(0x2, 0x25)
#define  REG_TC_P2I_BK2_25_H       _PK_H_(0x2, 0x25)
#define  REG_TC_P2I_BK2_26_L       _PK_L_(0x2, 0x26)
#define  REG_TC_P2I_BK2_26_H       _PK_H_(0x2, 0x26)
#define  REG_TC_P2I_BK2_27_L       _PK_L_(0x2, 0x27)
#define  REG_TC_P2I_BK2_27_H       _PK_H_(0x2, 0x27)
#define  REG_TC_P2I_BK2_28_L       _PK_L_(0x2, 0x28)
#define  REG_TC_P2I_BK2_28_H       _PK_H_(0x2, 0x28)
#define  REG_TC_P2I_BK2_29_L       _PK_L_(0x2, 0x29)
#define  REG_TC_P2I_BK2_29_H       _PK_H_(0x2, 0x29)
#define  REG_TC_P2I_BK2_2A_L       _PK_L_(0x2, 0x2A)
#define  REG_TC_P2I_BK2_2A_H       _PK_H_(0x2, 0x2A)
#define  REG_TC_P2I_BK2_2B_L       _PK_L_(0x2, 0x2B)
#define  REG_TC_P2I_BK2_2B_H       _PK_H_(0x2, 0x2B)
#define  REG_TC_P2I_BK2_2C_L       _PK_L_(0x2, 0x2C)
#define  REG_TC_P2I_BK2_2C_H       _PK_H_(0x2, 0x2C)
#define  REG_TC_P2I_BK2_2D_L       _PK_L_(0x2, 0x2D)
#define  REG_TC_P2I_BK2_2D_H       _PK_H_(0x2, 0x2D)
#define  REG_TC_P2I_BK2_2E_L       _PK_L_(0x2, 0x2E)
#define  REG_TC_P2I_BK2_2E_H       _PK_H_(0x2, 0x2E)
#define  REG_TC_P2I_BK2_2F_L       _PK_L_(0x2, 0x2F)
#define  REG_TC_P2I_BK2_2F_H       _PK_H_(0x2, 0x2F)
#define  REG_TC_P2I_BK2_30_L       _PK_L_(0x2, 0x30)
#define  REG_TC_P2I_BK2_30_H       _PK_H_(0x2, 0x30)
#define  REG_TC_P2I_BK2_31_L       _PK_L_(0x2, 0x31)
#define  REG_TC_P2I_BK2_31_H       _PK_H_(0x2, 0x31)
#define  REG_TC_P2I_BK2_32_L       _PK_L_(0x2, 0x32)
#define  REG_TC_P2I_BK2_32_H       _PK_H_(0x2, 0x32)
#define  REG_TC_P2I_BK2_33_L       _PK_L_(0x2, 0x33)
#define  REG_TC_P2I_BK2_33_H       _PK_H_(0x2, 0x33)
#define  REG_TC_P2I_BK2_34_L       _PK_L_(0x2, 0x34)
#define  REG_TC_P2I_BK2_34_H       _PK_H_(0x2, 0x34)
#define  REG_TC_P2I_BK2_35_L       _PK_L_(0x2, 0x35)
#define  REG_TC_P2I_BK2_35_H       _PK_H_(0x2, 0x35)
#define  REG_TC_P2I_BK2_36_L       _PK_L_(0x2, 0x36)
#define  REG_TC_P2I_BK2_36_H       _PK_H_(0x2, 0x36)
#define  REG_TC_P2I_BK2_37_L       _PK_L_(0x2, 0x37)
#define  REG_TC_P2I_BK2_37_H       _PK_H_(0x2, 0x37)
#define  REG_TC_P2I_BK2_38_L       _PK_L_(0x2, 0x38)
#define  REG_TC_P2I_BK2_38_H       _PK_H_(0x2, 0x38)
#define  REG_TC_P2I_BK2_39_L       _PK_L_(0x2, 0x39)
#define  REG_TC_P2I_BK2_39_H       _PK_H_(0x2, 0x39)
#define  REG_TC_P2I_BK2_3A_L       _PK_L_(0x2, 0x3A)
#define  REG_TC_P2I_BK2_3A_H       _PK_H_(0x2, 0x3A)
#define  REG_TC_P2I_BK2_3B_L       _PK_L_(0x2, 0x3B)
#define  REG_TC_P2I_BK2_3B_H       _PK_H_(0x2, 0x3B)
#define  REG_TC_P2I_BK2_3C_L       _PK_L_(0x2, 0x3C)
#define  REG_TC_P2I_BK2_3C_H       _PK_H_(0x2, 0x3C)
#define  REG_TC_P2I_BK2_3D_L       _PK_L_(0x2, 0x3D)
#define  REG_TC_P2I_BK2_3D_H       _PK_H_(0x2, 0x3D)
#define  REG_TC_P2I_BK2_3E_L       _PK_L_(0x2, 0x3E)
#define  REG_TC_P2I_BK2_3E_H       _PK_H_(0x2, 0x3E)
#define  REG_TC_P2I_BK2_3F_L       _PK_L_(0x2, 0x3F)
#define  REG_TC_P2I_BK2_3F_H       _PK_H_(0x2, 0x3F)
#define  REG_TC_P2I_BK2_40_L       _PK_L_(0x2, 0x40)
#define  REG_TC_P2I_BK2_40_H       _PK_H_(0x2, 0x40)
#define  REG_TC_P2I_BK2_41_L       _PK_L_(0x2, 0x41)
#define  REG_TC_P2I_BK2_41_H       _PK_H_(0x2, 0x41)
#define  REG_TC_P2I_BK2_42_L       _PK_L_(0x2, 0x42)
#define  REG_TC_P2I_BK2_42_H       _PK_H_(0x2, 0x42)
#define  REG_TC_P2I_BK2_43_L       _PK_L_(0x2, 0x43)
#define  REG_TC_P2I_BK2_43_H       _PK_H_(0x2, 0x43)
#define  REG_TC_P2I_BK2_44_L       _PK_L_(0x2, 0x44)
#define  REG_TC_P2I_BK2_44_H       _PK_H_(0x2, 0x44)
#define  REG_TC_P2I_BK2_45_L       _PK_L_(0x2, 0x45)
#define  REG_TC_P2I_BK2_45_H       _PK_H_(0x2, 0x45)
#define  REG_TC_P2I_BK2_46_L       _PK_L_(0x2, 0x46)
#define  REG_TC_P2I_BK2_46_H       _PK_H_(0x2, 0x46)
#define  REG_TC_P2I_BK2_47_L       _PK_L_(0x2, 0x47)
#define  REG_TC_P2I_BK2_47_H       _PK_H_(0x2, 0x47)
#define  REG_TC_P2I_BK2_48_L       _PK_L_(0x2, 0x48)
#define  REG_TC_P2I_BK2_48_H       _PK_H_(0x2, 0x48)
#define  REG_TC_P2I_BK2_49_L       _PK_L_(0x2, 0x49)
#define  REG_TC_P2I_BK2_49_H       _PK_H_(0x2, 0x49)
#define  REG_TC_P2I_BK2_4A_L       _PK_L_(0x2, 0x4A)
#define  REG_TC_P2I_BK2_4A_H       _PK_H_(0x2, 0x4A)
#define  REG_TC_P2I_BK2_4B_L       _PK_L_(0x2, 0x4B)
#define  REG_TC_P2I_BK2_4B_H       _PK_H_(0x2, 0x4B)
#define  REG_TC_P2I_BK2_4C_L       _PK_L_(0x2, 0x4C)
#define  REG_TC_P2I_BK2_4C_H       _PK_H_(0x2, 0x4C)
#define  REG_TC_P2I_BK2_4D_L       _PK_L_(0x2, 0x4D)
#define  REG_TC_P2I_BK2_4D_H       _PK_H_(0x2, 0x4D)
#define  REG_TC_P2I_BK2_4E_L       _PK_L_(0x2, 0x4E)
#define  REG_TC_P2I_BK2_4E_H       _PK_H_(0x2, 0x4E)
#define  REG_TC_P2I_BK2_4F_L       _PK_L_(0x2, 0x4F)
#define  REG_TC_P2I_BK2_4F_H       _PK_H_(0x2, 0x4F)
#define  REG_TC_P2I_BK2_50_L       _PK_L_(0x2, 0x50)
#define  REG_TC_P2I_BK2_50_H       _PK_H_(0x2, 0x50)
#define  REG_TC_P2I_BK2_51_L       _PK_L_(0x2, 0x51)
#define  REG_TC_P2I_BK2_51_H       _PK_H_(0x2, 0x51)
#define  REG_TC_P2I_BK2_52_L       _PK_L_(0x2, 0x52)
#define  REG_TC_P2I_BK2_52_H       _PK_H_(0x2, 0x52)
#define  REG_TC_P2I_BK2_53_L       _PK_L_(0x2, 0x53)
#define  REG_TC_P2I_BK2_53_H       _PK_H_(0x2, 0x53)
#define  REG_TC_P2I_BK2_54_L       _PK_L_(0x2, 0x54)
#define  REG_TC_P2I_BK2_54_H       _PK_H_(0x2, 0x54)
#define  REG_TC_P2I_BK2_55_L       _PK_L_(0x2, 0x55)
#define  REG_TC_P2I_BK2_55_H       _PK_H_(0x2, 0x55)
#define  REG_TC_P2I_BK2_56_L       _PK_L_(0x2, 0x56)
#define  REG_TC_P2I_BK2_56_H       _PK_H_(0x2, 0x56)
#define  REG_TC_P2I_BK2_57_L       _PK_L_(0x2, 0x57)
#define  REG_TC_P2I_BK2_57_H       _PK_H_(0x2, 0x57)
#define  REG_TC_P2I_BK2_58_L       _PK_L_(0x2, 0x58)
#define  REG_TC_P2I_BK2_58_H       _PK_H_(0x2, 0x58)
#define  REG_TC_P2I_BK2_59_L       _PK_L_(0x2, 0x59)
#define  REG_TC_P2I_BK2_59_H       _PK_H_(0x2, 0x59)
#define  REG_TC_P2I_BK2_5A_L       _PK_L_(0x2, 0x5A)
#define  REG_TC_P2I_BK2_5A_H       _PK_H_(0x2, 0x5A)
#define  REG_TC_P2I_BK2_5B_L       _PK_L_(0x2, 0x5B)
#define  REG_TC_P2I_BK2_5B_H       _PK_H_(0x2, 0x5B)
#define  REG_TC_P2I_BK2_5C_L       _PK_L_(0x2, 0x5C)
#define  REG_TC_P2I_BK2_5C_H       _PK_H_(0x2, 0x5C)
#define  REG_TC_P2I_BK2_5D_L       _PK_L_(0x2, 0x5D)
#define  REG_TC_P2I_BK2_5D_H       _PK_H_(0x2, 0x5D)
#define  REG_TC_P2I_BK2_5E_L       _PK_L_(0x2, 0x5E)
#define  REG_TC_P2I_BK2_5E_H       _PK_H_(0x2, 0x5E)
#define  REG_TC_P2I_BK2_5F_L       _PK_L_(0x2, 0x5F)
#define  REG_TC_P2I_BK2_5F_H       _PK_H_(0x2, 0x5F)
#define  REG_TC_P2I_BK2_60_L       _PK_L_(0x2, 0x60)
#define  REG_TC_P2I_BK2_60_H       _PK_H_(0x2, 0x60)
#define  REG_TC_P2I_BK2_61_L       _PK_L_(0x2, 0x61)
#define  REG_TC_P2I_BK2_61_H       _PK_H_(0x2, 0x61)
#define  REG_TC_P2I_BK2_62_L       _PK_L_(0x2, 0x62)
#define  REG_TC_P2I_BK2_62_H       _PK_H_(0x2, 0x62)
#define  REG_TC_P2I_BK2_63_L       _PK_L_(0x2, 0x63)
#define  REG_TC_P2I_BK2_63_H       _PK_H_(0x2, 0x63)
#define  REG_TC_P2I_BK2_64_L       _PK_L_(0x2, 0x64)
#define  REG_TC_P2I_BK2_64_H       _PK_H_(0x2, 0x64)
#define  REG_TC_P2I_BK2_65_L       _PK_L_(0x2, 0x65)
#define  REG_TC_P2I_BK2_65_H       _PK_H_(0x2, 0x65)
#define  REG_TC_P2I_BK2_66_L       _PK_L_(0x2, 0x66)
#define  REG_TC_P2I_BK2_66_H       _PK_H_(0x2, 0x66)
#define  REG_TC_P2I_BK2_67_L       _PK_L_(0x2, 0x67)
#define  REG_TC_P2I_BK2_67_H       _PK_H_(0x2, 0x67)
#define  REG_TC_P2I_BK2_68_L       _PK_L_(0x2, 0x68)
#define  REG_TC_P2I_BK2_68_H       _PK_H_(0x2, 0x68)
#define  REG_TC_P2I_BK2_69_L       _PK_L_(0x2, 0x69)
#define  REG_TC_P2I_BK2_69_H       _PK_H_(0x2, 0x69)
#define  REG_TC_P2I_BK2_6A_L       _PK_L_(0x2, 0x6A)
#define  REG_TC_P2I_BK2_6A_H       _PK_H_(0x2, 0x6A)
#define  REG_TC_P2I_BK2_6B_L       _PK_L_(0x2, 0x6B)
#define  REG_TC_P2I_BK2_6B_H       _PK_H_(0x2, 0x6B)
#define  REG_TC_P2I_BK2_6C_L       _PK_L_(0x2, 0x6C)
#define  REG_TC_P2I_BK2_6C_H       _PK_H_(0x2, 0x6C)
#define  REG_TC_P2I_BK2_6D_L       _PK_L_(0x2, 0x6D)
#define  REG_TC_P2I_BK2_6D_H       _PK_H_(0x2, 0x6D)
#define  REG_TC_P2I_BK2_6E_L       _PK_L_(0x2, 0x6E)
#define  REG_TC_P2I_BK2_6E_H       _PK_H_(0x2, 0x6E)
#define  REG_TC_P2I_BK2_6F_L       _PK_L_(0x2, 0x6F)
#define  REG_TC_P2I_BK2_6F_H       _PK_H_(0x2, 0x6F)
#define  REG_TC_P2I_BK2_70_L       _PK_L_(0x2, 0x70)
#define  REG_TC_P2I_BK2_70_H       _PK_H_(0x2, 0x70)
#define  REG_TC_P2I_BK2_71_L       _PK_L_(0x2, 0x71)
#define  REG_TC_P2I_BK2_71_H       _PK_H_(0x2, 0x71)
#define  REG_TC_P2I_BK2_72_L       _PK_L_(0x2, 0x72)
#define  REG_TC_P2I_BK2_72_H       _PK_H_(0x2, 0x72)
#define  REG_TC_P2I_BK2_73_L       _PK_L_(0x2, 0x73)
#define  REG_TC_P2I_BK2_73_H       _PK_H_(0x2, 0x73)
#define  REG_TC_P2I_BK2_74_L       _PK_L_(0x2, 0x74)
#define  REG_TC_P2I_BK2_74_H       _PK_H_(0x2, 0x74)
#define  REG_TC_P2I_BK2_75_L       _PK_L_(0x2, 0x75)
#define  REG_TC_P2I_BK2_75_H       _PK_H_(0x2, 0x75)
#define  REG_TC_P2I_BK2_76_L       _PK_L_(0x2, 0x76)
#define  REG_TC_P2I_BK2_76_H       _PK_H_(0x2, 0x76)
#define  REG_TC_P2I_BK2_77_L       _PK_L_(0x2, 0x77)
#define  REG_TC_P2I_BK2_77_H       _PK_H_(0x2, 0x77)
#define  REG_TC_P2I_BK2_78_L       _PK_L_(0x2, 0x78)
#define  REG_TC_P2I_BK2_78_H       _PK_H_(0x2, 0x78)
#define  REG_TC_P2I_BK2_79_L       _PK_L_(0x2, 0x79)
#define  REG_TC_P2I_BK2_79_H       _PK_H_(0x2, 0x79)
#define  REG_TC_P2I_BK2_7A_L       _PK_L_(0x2, 0x7A)
#define  REG_TC_P2I_BK2_7A_H       _PK_H_(0x2, 0x7A)
#define  REG_TC_P2I_BK2_7B_L       _PK_L_(0x2, 0x7B)
#define  REG_TC_P2I_BK2_7B_H       _PK_H_(0x2, 0x7B)
#define  REG_TC_P2I_BK2_7C_L       _PK_L_(0x2, 0x7C)
#define  REG_TC_P2I_BK2_7C_H       _PK_H_(0x2, 0x7C)
#define  REG_TC_P2I_BK2_7D_L       _PK_L_(0x2, 0x7D)
#define  REG_TC_P2I_BK2_7D_H       _PK_H_(0x2, 0x7D)
#define  REG_TC_P2I_BK2_7E_L       _PK_L_(0x2, 0x7E)
#define  REG_TC_P2I_BK2_7E_H       _PK_H_(0x2, 0x7E)
#define  REG_TC_P2I_BK2_7F_L       _PK_L_(0x2, 0x7F)
#define  REG_TC_P2I_BK2_7F_H       _PK_H_(0x2, 0x7F)

#define  REG_TC_HDGEN_BK1_00_L       _PK_L_(0x1, 0x00)
#define  REG_TC_HDGEN_BK1_00_H       _PK_H_(0x1, 0x00)
#define  REG_TC_HDGEN_BK1_01_L       _PK_L_(0x1, 0x01)
#define  REG_TC_HDGEN_BK1_01_H       _PK_H_(0x1, 0x01)
#define  REG_TC_HDGEN_BK1_02_L       _PK_L_(0x1, 0x02)
#define  REG_TC_HDGEN_BK1_02_H       _PK_H_(0x1, 0x02)
#define  REG_TC_HDGEN_BK1_03_L       _PK_L_(0x1, 0x03)
#define  REG_TC_HDGEN_BK1_03_H       _PK_H_(0x1, 0x03)
#define  REG_TC_HDGEN_BK1_04_L       _PK_L_(0x1, 0x04)
#define  REG_TC_HDGEN_BK1_04_H       _PK_H_(0x1, 0x04)
#define  REG_TC_HDGEN_BK1_05_L       _PK_L_(0x1, 0x05)
#define  REG_TC_HDGEN_BK1_05_H       _PK_H_(0x1, 0x05)
#define  REG_TC_HDGEN_BK1_06_L       _PK_L_(0x1, 0x06)
#define  REG_TC_HDGEN_BK1_06_H       _PK_H_(0x1, 0x06)
#define  REG_TC_HDGEN_BK1_07_L       _PK_L_(0x1, 0x07)
#define  REG_TC_HDGEN_BK1_07_H       _PK_H_(0x1, 0x07)
#define  REG_TC_HDGEN_BK1_08_L       _PK_L_(0x1, 0x08)
#define  REG_TC_HDGEN_BK1_08_H       _PK_H_(0x1, 0x08)
#define  REG_TC_HDGEN_BK1_09_L       _PK_L_(0x1, 0x09)
#define  REG_TC_HDGEN_BK1_09_H       _PK_H_(0x1, 0x09)
#define  REG_TC_HDGEN_BK1_0A_L       _PK_L_(0x1, 0x0A)
#define  REG_TC_HDGEN_BK1_0A_H       _PK_H_(0x1, 0x0A)
#define  REG_TC_HDGEN_BK1_0B_L       _PK_L_(0x1, 0x0B)
#define  REG_TC_HDGEN_BK1_0B_H       _PK_H_(0x1, 0x0B)
#define  REG_TC_HDGEN_BK1_0C_L       _PK_L_(0x1, 0x0C)
#define  REG_TC_HDGEN_BK1_0C_H       _PK_H_(0x1, 0x0C)
#define  REG_TC_HDGEN_BK1_0D_L       _PK_L_(0x1, 0x0D)
#define  REG_TC_HDGEN_BK1_0D_H       _PK_H_(0x1, 0x0D)
#define  REG_TC_HDGEN_BK1_0E_L       _PK_L_(0x1, 0x0E)
#define  REG_TC_HDGEN_BK1_0E_H       _PK_H_(0x1, 0x0E)
#define  REG_TC_HDGEN_BK1_0F_L       _PK_L_(0x1, 0x0F)
#define  REG_TC_HDGEN_BK1_0F_H       _PK_H_(0x1, 0x0F)
#define  REG_TC_HDGEN_BK1_10_L       _PK_L_(0x1, 0x10)
#define  REG_TC_HDGEN_BK1_10_H       _PK_H_(0x1, 0x10)
#define  REG_TC_HDGEN_BK1_11_L       _PK_L_(0x1, 0x11)
#define  REG_TC_HDGEN_BK1_11_H       _PK_H_(0x1, 0x11)
#define  REG_TC_HDGEN_BK1_12_L       _PK_L_(0x1, 0x12)
#define  REG_TC_HDGEN_BK1_12_H       _PK_H_(0x1, 0x12)
#define  REG_TC_HDGEN_BK1_13_L       _PK_L_(0x1, 0x13)
#define  REG_TC_HDGEN_BK1_13_H       _PK_H_(0x1, 0x13)
#define  REG_TC_HDGEN_BK1_14_L       _PK_L_(0x1, 0x14)
#define  REG_TC_HDGEN_BK1_14_H       _PK_H_(0x1, 0x14)
#define  REG_TC_HDGEN_BK1_15_L       _PK_L_(0x1, 0x15)
#define  REG_TC_HDGEN_BK1_15_H       _PK_H_(0x1, 0x15)
#define  REG_TC_HDGEN_BK1_16_L       _PK_L_(0x1, 0x16)
#define  REG_TC_HDGEN_BK1_16_H       _PK_H_(0x1, 0x16)
#define  REG_TC_HDGEN_BK1_17_L       _PK_L_(0x1, 0x17)
#define  REG_TC_HDGEN_BK1_17_H       _PK_H_(0x1, 0x17)
#define  REG_TC_HDGEN_BK1_18_L       _PK_L_(0x1, 0x18)
#define  REG_TC_HDGEN_BK1_18_H       _PK_H_(0x1, 0x18)
#define  REG_TC_HDGEN_BK1_19_L       _PK_L_(0x1, 0x19)
#define  REG_TC_HDGEN_BK1_19_H       _PK_H_(0x1, 0x19)
#define  REG_TC_HDGEN_BK1_1A_L       _PK_L_(0x1, 0x1A)
#define  REG_TC_HDGEN_BK1_1A_H       _PK_H_(0x1, 0x1A)
#define  REG_TC_HDGEN_BK1_1B_L       _PK_L_(0x1, 0x1B)
#define  REG_TC_HDGEN_BK1_1B_H       _PK_H_(0x1, 0x1B)
#define  REG_TC_HDGEN_BK1_1C_L       _PK_L_(0x1, 0x1C)
#define  REG_TC_HDGEN_BK1_1C_H       _PK_H_(0x1, 0x1C)
#define  REG_TC_HDGEN_BK1_1D_L       _PK_L_(0x1, 0x1D)
#define  REG_TC_HDGEN_BK1_1D_H       _PK_H_(0x1, 0x1D)
#define  REG_TC_HDGEN_BK1_1E_L       _PK_L_(0x1, 0x1E)
#define  REG_TC_HDGEN_BK1_1E_H       _PK_H_(0x1, 0x1E)
#define  REG_TC_HDGEN_BK1_1F_L       _PK_L_(0x1, 0x1F)
#define  REG_TC_HDGEN_BK1_1F_H       _PK_H_(0x1, 0x1F)
#define  REG_TC_HDGEN_BK1_20_L       _PK_L_(0x1, 0x20)
#define  REG_TC_HDGEN_BK1_20_H       _PK_H_(0x1, 0x20)
#define  REG_TC_HDGEN_BK1_21_L       _PK_L_(0x1, 0x21)
#define  REG_TC_HDGEN_BK1_21_H       _PK_H_(0x1, 0x21)
#define  REG_TC_HDGEN_BK1_22_L       _PK_L_(0x1, 0x22)
#define  REG_TC_HDGEN_BK1_22_H       _PK_H_(0x1, 0x22)
#define  REG_TC_HDGEN_BK1_23_L       _PK_L_(0x1, 0x23)
#define  REG_TC_HDGEN_BK1_23_H       _PK_H_(0x1, 0x23)
#define  REG_TC_HDGEN_BK1_24_L       _PK_L_(0x1, 0x24)
#define  REG_TC_HDGEN_BK1_24_H       _PK_H_(0x1, 0x24)
#define  REG_TC_HDGEN_BK1_25_L       _PK_L_(0x1, 0x25)
#define  REG_TC_HDGEN_BK1_25_H       _PK_H_(0x1, 0x25)
#define  REG_TC_HDGEN_BK1_26_L       _PK_L_(0x1, 0x26)
#define  REG_TC_HDGEN_BK1_26_H       _PK_H_(0x1, 0x26)
#define  REG_TC_HDGEN_BK1_27_L       _PK_L_(0x1, 0x27)
#define  REG_TC_HDGEN_BK1_27_H       _PK_H_(0x1, 0x27)
#define  REG_TC_HDGEN_BK1_28_L       _PK_L_(0x1, 0x28)
#define  REG_TC_HDGEN_BK1_28_H       _PK_H_(0x1, 0x28)
#define  REG_TC_HDGEN_BK1_29_L       _PK_L_(0x1, 0x29)
#define  REG_TC_HDGEN_BK1_29_H       _PK_H_(0x1, 0x29)
#define  REG_TC_HDGEN_BK1_2A_L       _PK_L_(0x1, 0x2A)
#define  REG_TC_HDGEN_BK1_2A_H       _PK_H_(0x1, 0x2A)
#define  REG_TC_HDGEN_BK1_2B_L       _PK_L_(0x1, 0x2B)
#define  REG_TC_HDGEN_BK1_2B_H       _PK_H_(0x1, 0x2B)
#define  REG_TC_HDGEN_BK1_2C_L       _PK_L_(0x1, 0x2C)
#define  REG_TC_HDGEN_BK1_2C_H       _PK_H_(0x1, 0x2C)
#define  REG_TC_HDGEN_BK1_2D_L       _PK_L_(0x1, 0x2D)
#define  REG_TC_HDGEN_BK1_2D_H       _PK_H_(0x1, 0x2D)
#define  REG_TC_HDGEN_BK1_2E_L       _PK_L_(0x1, 0x2E)
#define  REG_TC_HDGEN_BK1_2E_H       _PK_H_(0x1, 0x2E)
#define  REG_TC_HDGEN_BK1_2F_L       _PK_L_(0x1, 0x2F)
#define  REG_TC_HDGEN_BK1_2F_H       _PK_H_(0x1, 0x2F)
#define  REG_TC_HDGEN_BK1_30_L       _PK_L_(0x1, 0x30)
#define  REG_TC_HDGEN_BK1_30_H       _PK_H_(0x1, 0x30)
#define  REG_TC_HDGEN_BK1_31_L       _PK_L_(0x1, 0x31)
#define  REG_TC_HDGEN_BK1_31_H       _PK_H_(0x1, 0x31)
#define  REG_TC_HDGEN_BK1_32_L       _PK_L_(0x1, 0x32)
#define  REG_TC_HDGEN_BK1_32_H       _PK_H_(0x1, 0x32)
#define  REG_TC_HDGEN_BK1_33_L       _PK_L_(0x1, 0x33)
#define  REG_TC_HDGEN_BK1_33_H       _PK_H_(0x1, 0x33)
#define  REG_TC_HDGEN_BK1_34_L       _PK_L_(0x1, 0x34)
#define  REG_TC_HDGEN_BK1_34_H       _PK_H_(0x1, 0x34)
#define  REG_TC_HDGEN_BK1_35_L       _PK_L_(0x1, 0x35)
#define  REG_TC_HDGEN_BK1_35_H       _PK_H_(0x1, 0x35)
#define  REG_TC_HDGEN_BK1_36_L       _PK_L_(0x1, 0x36)
#define  REG_TC_HDGEN_BK1_36_H       _PK_H_(0x1, 0x36)
#define  REG_TC_HDGEN_BK1_37_L       _PK_L_(0x1, 0x37)
#define  REG_TC_HDGEN_BK1_37_H       _PK_H_(0x1, 0x37)
#define  REG_TC_HDGEN_BK1_38_L       _PK_L_(0x1, 0x38)
#define  REG_TC_HDGEN_BK1_38_H       _PK_H_(0x1, 0x38)
#define  REG_TC_HDGEN_BK1_39_L       _PK_L_(0x1, 0x39)
#define  REG_TC_HDGEN_BK1_39_H       _PK_H_(0x1, 0x39)
#define  REG_TC_HDGEN_BK1_3A_L       _PK_L_(0x1, 0x3A)
#define  REG_TC_HDGEN_BK1_3A_H       _PK_H_(0x1, 0x3A)
#define  REG_TC_HDGEN_BK1_3B_L       _PK_L_(0x1, 0x3B)
#define  REG_TC_HDGEN_BK1_3B_H       _PK_H_(0x1, 0x3B)
#define  REG_TC_HDGEN_BK1_3C_L       _PK_L_(0x1, 0x3C)
#define  REG_TC_HDGEN_BK1_3C_H       _PK_H_(0x1, 0x3C)
#define  REG_TC_HDGEN_BK1_3D_L       _PK_L_(0x1, 0x3D)
#define  REG_TC_HDGEN_BK1_3D_H       _PK_H_(0x1, 0x3D)
#define  REG_TC_HDGEN_BK1_3E_L       _PK_L_(0x1, 0x3E)
#define  REG_TC_HDGEN_BK1_3E_H       _PK_H_(0x1, 0x3E)
#define  REG_TC_HDGEN_BK1_3F_L       _PK_L_(0x1, 0x3F)
#define  REG_TC_HDGEN_BK1_3F_H       _PK_H_(0x1, 0x3F)
#define  REG_TC_HDGEN_BK1_40_L       _PK_L_(0x1, 0x40)
#define  REG_TC_HDGEN_BK1_40_H       _PK_H_(0x1, 0x40)
#define  REG_TC_HDGEN_BK1_41_L       _PK_L_(0x1, 0x41)
#define  REG_TC_HDGEN_BK1_41_H       _PK_H_(0x1, 0x41)
#define  REG_TC_HDGEN_BK1_42_L       _PK_L_(0x1, 0x42)
#define  REG_TC_HDGEN_BK1_42_H       _PK_H_(0x1, 0x42)
#define  REG_TC_HDGEN_BK1_43_L       _PK_L_(0x1, 0x43)
#define  REG_TC_HDGEN_BK1_43_H       _PK_H_(0x1, 0x43)
#define  REG_TC_HDGEN_BK1_44_L       _PK_L_(0x1, 0x44)
#define  REG_TC_HDGEN_BK1_44_H       _PK_H_(0x1, 0x44)
#define  REG_TC_HDGEN_BK1_45_L       _PK_L_(0x1, 0x45)
#define  REG_TC_HDGEN_BK1_45_H       _PK_H_(0x1, 0x45)
#define  REG_TC_HDGEN_BK1_46_L       _PK_L_(0x1, 0x46)
#define  REG_TC_HDGEN_BK1_46_H       _PK_H_(0x1, 0x46)
#define  REG_TC_HDGEN_BK1_47_L       _PK_L_(0x1, 0x47)
#define  REG_TC_HDGEN_BK1_47_H       _PK_H_(0x1, 0x47)
#define  REG_TC_HDGEN_BK1_48_L       _PK_L_(0x1, 0x48)
#define  REG_TC_HDGEN_BK1_48_H       _PK_H_(0x1, 0x48)
#define  REG_TC_HDGEN_BK1_49_L       _PK_L_(0x1, 0x49)
#define  REG_TC_HDGEN_BK1_49_H       _PK_H_(0x1, 0x49)
#define  REG_TC_HDGEN_BK1_4A_L       _PK_L_(0x1, 0x4A)
#define  REG_TC_HDGEN_BK1_4A_H       _PK_H_(0x1, 0x4A)
#define  REG_TC_HDGEN_BK1_4B_L       _PK_L_(0x1, 0x4B)
#define  REG_TC_HDGEN_BK1_4B_H       _PK_H_(0x1, 0x4B)
#define  REG_TC_HDGEN_BK1_4C_L       _PK_L_(0x1, 0x4C)
#define  REG_TC_HDGEN_BK1_4C_H       _PK_H_(0x1, 0x4C)
#define  REG_TC_HDGEN_BK1_4D_L       _PK_L_(0x1, 0x4D)
#define  REG_TC_HDGEN_BK1_4D_H       _PK_H_(0x1, 0x4D)
#define  REG_TC_HDGEN_BK1_4E_L       _PK_L_(0x1, 0x4E)
#define  REG_TC_HDGEN_BK1_4E_H       _PK_H_(0x1, 0x4E)
#define  REG_TC_HDGEN_BK1_4F_L       _PK_L_(0x1, 0x4F)
#define  REG_TC_HDGEN_BK1_4F_H       _PK_H_(0x1, 0x4F)
#define  REG_TC_HDGEN_BK1_50_L       _PK_L_(0x1, 0x50)
#define  REG_TC_HDGEN_BK1_50_H       _PK_H_(0x1, 0x50)
#define  REG_TC_HDGEN_BK1_51_L       _PK_L_(0x1, 0x51)
#define  REG_TC_HDGEN_BK1_51_H       _PK_H_(0x1, 0x51)
#define  REG_TC_HDGEN_BK1_52_L       _PK_L_(0x1, 0x52)
#define  REG_TC_HDGEN_BK1_52_H       _PK_H_(0x1, 0x52)
#define  REG_TC_HDGEN_BK1_53_L       _PK_L_(0x1, 0x53)
#define  REG_TC_HDGEN_BK1_53_H       _PK_H_(0x1, 0x53)
#define  REG_TC_HDGEN_BK1_54_L       _PK_L_(0x1, 0x54)
#define  REG_TC_HDGEN_BK1_54_H       _PK_H_(0x1, 0x54)
#define  REG_TC_HDGEN_BK1_55_L       _PK_L_(0x1, 0x55)
#define  REG_TC_HDGEN_BK1_55_H       _PK_H_(0x1, 0x55)
#define  REG_TC_HDGEN_BK1_56_L       _PK_L_(0x1, 0x56)
#define  REG_TC_HDGEN_BK1_56_H       _PK_H_(0x1, 0x56)
#define  REG_TC_HDGEN_BK1_57_L       _PK_L_(0x1, 0x57)
#define  REG_TC_HDGEN_BK1_57_H       _PK_H_(0x1, 0x57)
#define  REG_TC_HDGEN_BK1_58_L       _PK_L_(0x1, 0x58)
#define  REG_TC_HDGEN_BK1_58_H       _PK_H_(0x1, 0x58)
#define  REG_TC_HDGEN_BK1_59_L       _PK_L_(0x1, 0x59)
#define  REG_TC_HDGEN_BK1_59_H       _PK_H_(0x1, 0x59)
#define  REG_TC_HDGEN_BK1_5A_L       _PK_L_(0x1, 0x5A)
#define  REG_TC_HDGEN_BK1_5A_H       _PK_H_(0x1, 0x5A)
#define  REG_TC_HDGEN_BK1_5B_L       _PK_L_(0x1, 0x5B)
#define  REG_TC_HDGEN_BK1_5B_H       _PK_H_(0x1, 0x5B)
#define  REG_TC_HDGEN_BK1_5C_L       _PK_L_(0x1, 0x5C)
#define  REG_TC_HDGEN_BK1_5C_H       _PK_H_(0x1, 0x5C)
#define  REG_TC_HDGEN_BK1_5D_L       _PK_L_(0x1, 0x5D)
#define  REG_TC_HDGEN_BK1_5D_H       _PK_H_(0x1, 0x5D)
#define  REG_TC_HDGEN_BK1_5E_L       _PK_L_(0x1, 0x5E)
#define  REG_TC_HDGEN_BK1_5E_H       _PK_H_(0x1, 0x5E)
#define  REG_TC_HDGEN_BK1_5F_L       _PK_L_(0x1, 0x5F)
#define  REG_TC_HDGEN_BK1_5F_H       _PK_H_(0x1, 0x5F)
#define  REG_TC_HDGEN_BK1_60_L       _PK_L_(0x1, 0x60)
#define  REG_TC_HDGEN_BK1_60_H       _PK_H_(0x1, 0x60)
#define  REG_TC_HDGEN_BK1_61_L       _PK_L_(0x1, 0x61)
#define  REG_TC_HDGEN_BK1_61_H       _PK_H_(0x1, 0x61)
#define  REG_TC_HDGEN_BK1_62_L       _PK_L_(0x1, 0x62)
#define  REG_TC_HDGEN_BK1_62_H       _PK_H_(0x1, 0x62)
#define  REG_TC_HDGEN_BK1_63_L       _PK_L_(0x1, 0x63)
#define  REG_TC_HDGEN_BK1_63_H       _PK_H_(0x1, 0x63)
#define  REG_TC_HDGEN_BK1_64_L       _PK_L_(0x1, 0x64)
#define  REG_TC_HDGEN_BK1_64_H       _PK_H_(0x1, 0x64)
#define  REG_TC_HDGEN_BK1_65_L       _PK_L_(0x1, 0x65)
#define  REG_TC_HDGEN_BK1_65_H       _PK_H_(0x1, 0x65)
#define  REG_TC_HDGEN_BK1_66_L       _PK_L_(0x1, 0x66)
#define  REG_TC_HDGEN_BK1_66_H       _PK_H_(0x1, 0x66)
#define  REG_TC_HDGEN_BK1_67_L       _PK_L_(0x1, 0x67)
#define  REG_TC_HDGEN_BK1_67_H       _PK_H_(0x1, 0x67)
#define  REG_TC_HDGEN_BK1_68_L       _PK_L_(0x1, 0x68)
#define  REG_TC_HDGEN_BK1_68_H       _PK_H_(0x1, 0x68)
#define  REG_TC_HDGEN_BK1_69_L       _PK_L_(0x1, 0x69)
#define  REG_TC_HDGEN_BK1_69_H       _PK_H_(0x1, 0x69)
#define  REG_TC_HDGEN_BK1_6A_L       _PK_L_(0x1, 0x6A)
#define  REG_TC_HDGEN_BK1_6A_H       _PK_H_(0x1, 0x6A)
#define  REG_TC_HDGEN_BK1_6B_L       _PK_L_(0x1, 0x6B)
#define  REG_TC_HDGEN_BK1_6B_H       _PK_H_(0x1, 0x6B)
#define  REG_TC_HDGEN_BK1_6C_L       _PK_L_(0x1, 0x6C)
#define  REG_TC_HDGEN_BK1_6C_H       _PK_H_(0x1, 0x6C)
#define  REG_TC_HDGEN_BK1_6D_L       _PK_L_(0x1, 0x6D)
#define  REG_TC_HDGEN_BK1_6D_H       _PK_H_(0x1, 0x6D)
#define  REG_TC_HDGEN_BK1_6E_L       _PK_L_(0x1, 0x6E)
#define  REG_TC_HDGEN_BK1_6E_H       _PK_H_(0x1, 0x6E)
#define  REG_TC_HDGEN_BK1_6F_L       _PK_L_(0x1, 0x6F)
#define  REG_TC_HDGEN_BK1_6F_H       _PK_H_(0x1, 0x6F)
#define  REG_TC_HDGEN_BK1_70_L       _PK_L_(0x1, 0x70)
#define  REG_TC_HDGEN_BK1_70_H       _PK_H_(0x1, 0x70)
#define  REG_TC_HDGEN_BK1_71_L       _PK_L_(0x1, 0x71)
#define  REG_TC_HDGEN_BK1_71_H       _PK_H_(0x1, 0x71)
#define  REG_TC_HDGEN_BK1_72_L       _PK_L_(0x1, 0x72)
#define  REG_TC_HDGEN_BK1_72_H       _PK_H_(0x1, 0x72)
#define  REG_TC_HDGEN_BK1_73_L       _PK_L_(0x1, 0x73)
#define  REG_TC_HDGEN_BK1_73_H       _PK_H_(0x1, 0x73)
#define  REG_TC_HDGEN_BK1_74_L       _PK_L_(0x1, 0x74)
#define  REG_TC_HDGEN_BK1_74_H       _PK_H_(0x1, 0x74)
#define  REG_TC_HDGEN_BK1_75_L       _PK_L_(0x1, 0x75)
#define  REG_TC_HDGEN_BK1_75_H       _PK_H_(0x1, 0x75)
#define  REG_TC_HDGEN_BK1_76_L       _PK_L_(0x1, 0x76)
#define  REG_TC_HDGEN_BK1_76_H       _PK_H_(0x1, 0x76)
#define  REG_TC_HDGEN_BK1_77_L       _PK_L_(0x1, 0x77)
#define  REG_TC_HDGEN_BK1_77_H       _PK_H_(0x1, 0x77)
#define  REG_TC_HDGEN_BK1_78_L       _PK_L_(0x1, 0x78)
#define  REG_TC_HDGEN_BK1_78_H       _PK_H_(0x1, 0x78)
#define  REG_TC_HDGEN_BK1_79_L       _PK_L_(0x1, 0x79)
#define  REG_TC_HDGEN_BK1_79_H       _PK_H_(0x1, 0x79)
#define  REG_TC_HDGEN_BK1_7A_L       _PK_L_(0x1, 0x7A)
#define  REG_TC_HDGEN_BK1_7A_H       _PK_H_(0x1, 0x7A)
#define  REG_TC_HDGEN_BK1_7B_L       _PK_L_(0x1, 0x7B)
#define  REG_TC_HDGEN_BK1_7B_H       _PK_H_(0x1, 0x7B)
#define  REG_TC_HDGEN_BK1_7C_L       _PK_L_(0x1, 0x7C)
#define  REG_TC_HDGEN_BK1_7C_H       _PK_H_(0x1, 0x7C)
#define  REG_TC_HDGEN_BK1_7D_L       _PK_L_(0x1, 0x7D)
#define  REG_TC_HDGEN_BK1_7D_H       _PK_H_(0x1, 0x7D)
#define  REG_TC_HDGEN_BK1_7E_L       _PK_L_(0x1, 0x7E)
#define  REG_TC_HDGEN_BK1_7E_H       _PK_H_(0x1, 0x7E)
#define  REG_TC_HDGEN_BK1_7F_L       _PK_L_(0x1, 0x7F)
#define  REG_TC_HDGEN_BK1_7F_H       _PK_H_(0x1, 0x7F)

#define  REG_TC_HDGEN_BK3_60_L       _PK_L_(0x3, 0x60)
#define  REG_TC_HDGEN_BK3_60_H       _PK_H_(0x3, 0x60)
#define  REG_TC_HDGEN_BK3_61_L       _PK_L_(0x3, 0x61)
#define  REG_TC_HDGEN_BK3_61_H       _PK_H_(0x3, 0x61)
#define  REG_TC_HDGEN_BK3_62_L       _PK_L_(0x3, 0x62)
#define  REG_TC_HDGEN_BK3_62_H       _PK_H_(0x3, 0x62)
#define  REG_TC_HDGEN_BK3_63_L       _PK_L_(0x3, 0x63)
#define  REG_TC_HDGEN_BK3_63_H       _PK_H_(0x3, 0x63)
#define  REG_TC_HDGEN_BK3_64_L       _PK_L_(0x3, 0x64)
#define  REG_TC_HDGEN_BK3_64_H       _PK_H_(0x3, 0x64)
#define  REG_TC_HDGEN_BK3_65_L       _PK_L_(0x3, 0x65)
#define  REG_TC_HDGEN_BK3_65_H       _PK_H_(0x3, 0x65)
#define  REG_TC_HDGEN_BK3_66_L       _PK_L_(0x3, 0x66)
#define  REG_TC_HDGEN_BK3_66_H       _PK_H_(0x3, 0x66)
#define  REG_TC_HDGEN_BK3_67_L       _PK_L_(0x3, 0x67)
#define  REG_TC_HDGEN_BK3_67_H       _PK_H_(0x3, 0x67)
#define  REG_TC_HDGEN_BK3_68_L       _PK_L_(0x3, 0x68)
#define  REG_TC_HDGEN_BK3_68_H       _PK_H_(0x3, 0x68)
#define  REG_TC_HDGEN_BK3_69_L       _PK_L_(0x3, 0x69)
#define  REG_TC_HDGEN_BK3_69_H       _PK_H_(0x3, 0x69)


#define  REG_TC_HDMITX_PLL_00_L       (REG_TC_HDMITX_PLL_BASE + 0x00)
#define  REG_TC_HDMITX_PLL_00_H       (REG_TC_HDMITX_PLL_BASE + 0x01)
#define  REG_TC_HDMITX_PLL_01_L       (REG_TC_HDMITX_PLL_BASE + 0x02)
#define  REG_TC_HDMITX_PLL_01_H       (REG_TC_HDMITX_PLL_BASE + 0x03)
#define  REG_TC_HDMITX_PLL_02_L       (REG_TC_HDMITX_PLL_BASE + 0x04)
#define  REG_TC_HDMITX_PLL_02_H       (REG_TC_HDMITX_PLL_BASE + 0x05)
#define  REG_TC_HDMITX_PLL_03_L       (REG_TC_HDMITX_PLL_BASE + 0x06)
#define  REG_TC_HDMITX_PLL_03_H       (REG_TC_HDMITX_PLL_BASE + 0x07)
#define  REG_TC_HDMITX_PLL_04_L       (REG_TC_HDMITX_PLL_BASE + 0x08)
#define  REG_TC_HDMITX_PLL_04_H       (REG_TC_HDMITX_PLL_BASE + 0x09)
#define  REG_TC_HDMITX_PLL_05_L       (REG_TC_HDMITX_PLL_BASE + 0x0A)
#define  REG_TC_HDMITX_PLL_05_H       (REG_TC_HDMITX_PLL_BASE + 0x0B)
#define  REG_TC_HDMITX_PLL_06_L       (REG_TC_HDMITX_PLL_BASE + 0x0C)
#define  REG_TC_HDMITX_PLL_06_H       (REG_TC_HDMITX_PLL_BASE + 0x0D)
#define  REG_TC_HDMITX_PLL_07_L       (REG_TC_HDMITX_PLL_BASE + 0x0E)
#define  REG_TC_HDMITX_PLL_07_H       (REG_TC_HDMITX_PLL_BASE + 0x0F)
#define  REG_TC_HDMITX_PLL_08_L       (REG_TC_HDMITX_PLL_BASE + 0x10)
#define  REG_TC_HDMITX_PLL_08_H       (REG_TC_HDMITX_PLL_BASE + 0x11)
#define  REG_TC_HDMITX_PLL_09_L       (REG_TC_HDMITX_PLL_BASE + 0x12)
#define  REG_TC_HDMITX_PLL_09_H       (REG_TC_HDMITX_PLL_BASE + 0x13)
#define  REG_TC_HDMITX_PLL_0A_L       (REG_TC_HDMITX_PLL_BASE + 0x14)
#define  REG_TC_HDMITX_PLL_0A_H       (REG_TC_HDMITX_PLL_BASE + 0x15)
#define  REG_TC_HDMITX_PLL_0B_L       (REG_TC_HDMITX_PLL_BASE + 0x16)
#define  REG_TC_HDMITX_PLL_0B_H       (REG_TC_HDMITX_PLL_BASE + 0x17)
#define  REG_TC_HDMITX_PLL_0C_L       (REG_TC_HDMITX_PLL_BASE + 0x18)
#define  REG_TC_HDMITX_PLL_0C_H       (REG_TC_HDMITX_PLL_BASE + 0x19)
#define  REG_TC_HDMITX_PLL_0D_L       (REG_TC_HDMITX_PLL_BASE + 0x1A)
#define  REG_TC_HDMITX_PLL_0D_H       (REG_TC_HDMITX_PLL_BASE + 0x1B)
#define  REG_TC_HDMITX_PLL_0E_L       (REG_TC_HDMITX_PLL_BASE + 0x1C)
#define  REG_TC_HDMITX_PLL_0E_H       (REG_TC_HDMITX_PLL_BASE + 0x1D)
#define  REG_TC_HDMITX_PLL_0F_L       (REG_TC_HDMITX_PLL_BASE + 0x1E)
#define  REG_TC_HDMITX_PLL_0F_H       (REG_TC_HDMITX_PLL_BASE + 0x1F)
#define  REG_TC_HDMITX_PLL_10_L       (REG_TC_HDMITX_PLL_BASE + 0x20)
#define  REG_TC_HDMITX_PLL_10_H       (REG_TC_HDMITX_PLL_BASE + 0x21)
#define  REG_TC_HDMITX_PLL_11_L       (REG_TC_HDMITX_PLL_BASE + 0x22)
#define  REG_TC_HDMITX_PLL_11_H       (REG_TC_HDMITX_PLL_BASE + 0x23)
#define  REG_TC_HDMITX_PLL_12_L       (REG_TC_HDMITX_PLL_BASE + 0x24)
#define  REG_TC_HDMITX_PLL_12_H       (REG_TC_HDMITX_PLL_BASE + 0x25)
#define  REG_TC_HDMITX_PLL_13_L       (REG_TC_HDMITX_PLL_BASE + 0x26)
#define  REG_TC_HDMITX_PLL_13_H       (REG_TC_HDMITX_PLL_BASE + 0x27)
#define  REG_TC_HDMITX_PLL_14_L       (REG_TC_HDMITX_PLL_BASE + 0x28)
#define  REG_TC_HDMITX_PLL_14_H       (REG_TC_HDMITX_PLL_BASE + 0x29)
#define  REG_TC_HDMITX_PLL_15_L       (REG_TC_HDMITX_PLL_BASE + 0x2A)
#define  REG_TC_HDMITX_PLL_15_H       (REG_TC_HDMITX_PLL_BASE + 0x2B)
#define  REG_TC_HDMITX_PLL_16_L       (REG_TC_HDMITX_PLL_BASE + 0x2C)
#define  REG_TC_HDMITX_PLL_16_H       (REG_TC_HDMITX_PLL_BASE + 0x2D)
#define  REG_TC_HDMITX_PLL_17_L       (REG_TC_HDMITX_PLL_BASE + 0x2E)
#define  REG_TC_HDMITX_PLL_17_H       (REG_TC_HDMITX_PLL_BASE + 0x2F)
#define  REG_TC_HDMITX_PLL_18_L       (REG_TC_HDMITX_PLL_BASE + 0x30)
#define  REG_TC_HDMITX_PLL_18_H       (REG_TC_HDMITX_PLL_BASE + 0x31)
#define  REG_TC_HDMITX_PLL_19_L       (REG_TC_HDMITX_PLL_BASE + 0x32)
#define  REG_TC_HDMITX_PLL_19_H       (REG_TC_HDMITX_PLL_BASE + 0x33)
#define  REG_TC_HDMITX_PLL_1A_L       (REG_TC_HDMITX_PLL_BASE + 0x34)
#define  REG_TC_HDMITX_PLL_1A_H       (REG_TC_HDMITX_PLL_BASE + 0x35)
#define  REG_TC_HDMITX_PLL_1B_L       (REG_TC_HDMITX_PLL_BASE + 0x36)
#define  REG_TC_HDMITX_PLL_1B_H       (REG_TC_HDMITX_PLL_BASE + 0x37)
#define  REG_TC_HDMITX_PLL_1C_L       (REG_TC_HDMITX_PLL_BASE + 0x38)
#define  REG_TC_HDMITX_PLL_1C_H       (REG_TC_HDMITX_PLL_BASE + 0x39)
#define  REG_TC_HDMITX_PLL_1D_L       (REG_TC_HDMITX_PLL_BASE + 0x3A)
#define  REG_TC_HDMITX_PLL_1D_H       (REG_TC_HDMITX_PLL_BASE + 0x3B)
#define  REG_TC_HDMITX_PLL_1E_L       (REG_TC_HDMITX_PLL_BASE + 0x3C)
#define  REG_TC_HDMITX_PLL_1E_H       (REG_TC_HDMITX_PLL_BASE + 0x3D)
#define  REG_TC_HDMITX_PLL_1F_L       (REG_TC_HDMITX_PLL_BASE + 0x3E)
#define  REG_TC_HDMITX_PLL_1F_H       (REG_TC_HDMITX_PLL_BASE + 0x3F)
#define  REG_TC_HDMITX_PLL_20_L       (REG_TC_HDMITX_PLL_BASE + 0x40)
#define  REG_TC_HDMITX_PLL_20_H       (REG_TC_HDMITX_PLL_BASE + 0x41)
#define  REG_TC_HDMITX_PLL_21_L       (REG_TC_HDMITX_PLL_BASE + 0x42)
#define  REG_TC_HDMITX_PLL_21_H       (REG_TC_HDMITX_PLL_BASE + 0x43)
#define  REG_TC_HDMITX_PLL_22_L       (REG_TC_HDMITX_PLL_BASE + 0x44)
#define  REG_TC_HDMITX_PLL_22_H       (REG_TC_HDMITX_PLL_BASE + 0x45)
#define  REG_TC_HDMITX_PLL_23_L       (REG_TC_HDMITX_PLL_BASE + 0x46)
#define  REG_TC_HDMITX_PLL_23_H       (REG_TC_HDMITX_PLL_BASE + 0x47)
#define  REG_TC_HDMITX_PLL_24_L       (REG_TC_HDMITX_PLL_BASE + 0x48)
#define  REG_TC_HDMITX_PLL_24_H       (REG_TC_HDMITX_PLL_BASE + 0x49)
#define  REG_TC_HDMITX_PLL_25_L       (REG_TC_HDMITX_PLL_BASE + 0x4A)
#define  REG_TC_HDMITX_PLL_25_H       (REG_TC_HDMITX_PLL_BASE + 0x4B)
#define  REG_TC_HDMITX_PLL_26_L       (REG_TC_HDMITX_PLL_BASE + 0x4C)
#define  REG_TC_HDMITX_PLL_26_H       (REG_TC_HDMITX_PLL_BASE + 0x4D)
#define  REG_TC_HDMITX_PLL_27_L       (REG_TC_HDMITX_PLL_BASE + 0x4E)
#define  REG_TC_HDMITX_PLL_27_H       (REG_TC_HDMITX_PLL_BASE + 0x4F)
#define  REG_TC_HDMITX_PLL_28_L       (REG_TC_HDMITX_PLL_BASE + 0x50)
#define  REG_TC_HDMITX_PLL_28_H       (REG_TC_HDMITX_PLL_BASE + 0x51)
#define  REG_TC_HDMITX_PLL_29_L       (REG_TC_HDMITX_PLL_BASE + 0x52)
#define  REG_TC_HDMITX_PLL_29_H       (REG_TC_HDMITX_PLL_BASE + 0x53)
#define  REG_TC_HDMITX_PLL_2A_L       (REG_TC_HDMITX_PLL_BASE + 0x54)
#define  REG_TC_HDMITX_PLL_2A_H       (REG_TC_HDMITX_PLL_BASE + 0x55)
#define  REG_TC_HDMITX_PLL_2B_L       (REG_TC_HDMITX_PLL_BASE + 0x56)
#define  REG_TC_HDMITX_PLL_2B_H       (REG_TC_HDMITX_PLL_BASE + 0x57)
#define  REG_TC_HDMITX_PLL_2C_L       (REG_TC_HDMITX_PLL_BASE + 0x58)
#define  REG_TC_HDMITX_PLL_2C_H       (REG_TC_HDMITX_PLL_BASE + 0x59)
#define  REG_TC_HDMITX_PLL_2D_L       (REG_TC_HDMITX_PLL_BASE + 0x5A)
#define  REG_TC_HDMITX_PLL_2D_H       (REG_TC_HDMITX_PLL_BASE + 0x5B)
#define  REG_TC_HDMITX_PLL_2E_L       (REG_TC_HDMITX_PLL_BASE + 0x5C)
#define  REG_TC_HDMITX_PLL_2E_H       (REG_TC_HDMITX_PLL_BASE + 0x5D)
#define  REG_TC_HDMITX_PLL_2F_L       (REG_TC_HDMITX_PLL_BASE + 0x5E)
#define  REG_TC_HDMITX_PLL_2F_H       (REG_TC_HDMITX_PLL_BASE + 0x5F)
#define  REG_TC_HDMITX_PLL_30_L       (REG_TC_HDMITX_PLL_BASE + 0x60)
#define  REG_TC_HDMITX_PLL_30_H       (REG_TC_HDMITX_PLL_BASE + 0x61)
#define  REG_TC_HDMITX_PLL_31_L       (REG_TC_HDMITX_PLL_BASE + 0x62)
#define  REG_TC_HDMITX_PLL_31_H       (REG_TC_HDMITX_PLL_BASE + 0x63)
#define  REG_TC_HDMITX_PLL_32_L       (REG_TC_HDMITX_PLL_BASE + 0x64)
#define  REG_TC_HDMITX_PLL_32_H       (REG_TC_HDMITX_PLL_BASE + 0x65)
#define  REG_TC_HDMITX_PLL_33_L       (REG_TC_HDMITX_PLL_BASE + 0x66)
#define  REG_TC_HDMITX_PLL_33_H       (REG_TC_HDMITX_PLL_BASE + 0x67)
#define  REG_TC_HDMITX_PLL_34_L       (REG_TC_HDMITX_PLL_BASE + 0x68)
#define  REG_TC_HDMITX_PLL_34_H       (REG_TC_HDMITX_PLL_BASE + 0x69)
#define  REG_TC_HDMITX_PLL_35_L       (REG_TC_HDMITX_PLL_BASE + 0x6A)
#define  REG_TC_HDMITX_PLL_35_H       (REG_TC_HDMITX_PLL_BASE + 0x6B)
#define  REG_TC_HDMITX_PLL_36_L       (REG_TC_HDMITX_PLL_BASE + 0x6C)
#define  REG_TC_HDMITX_PLL_36_H       (REG_TC_HDMITX_PLL_BASE + 0x6D)
#define  REG_TC_HDMITX_PLL_37_L       (REG_TC_HDMITX_PLL_BASE + 0x6E)
#define  REG_TC_HDMITX_PLL_37_H       (REG_TC_HDMITX_PLL_BASE + 0x6F)
#define  REG_TC_HDMITX_PLL_38_L       (REG_TC_HDMITX_PLL_BASE + 0x70)
#define  REG_TC_HDMITX_PLL_38_H       (REG_TC_HDMITX_PLL_BASE + 0x71)
#define  REG_TC_HDMITX_PLL_39_L       (REG_TC_HDMITX_PLL_BASE + 0x72)
#define  REG_TC_HDMITX_PLL_39_H       (REG_TC_HDMITX_PLL_BASE + 0x73)
#define  REG_TC_HDMITX_PLL_3A_L       (REG_TC_HDMITX_PLL_BASE + 0x74)
#define  REG_TC_HDMITX_PLL_3A_H       (REG_TC_HDMITX_PLL_BASE + 0x75)
#define  REG_TC_HDMITX_PLL_3B_L       (REG_TC_HDMITX_PLL_BASE + 0x76)
#define  REG_TC_HDMITX_PLL_3B_H       (REG_TC_HDMITX_PLL_BASE + 0x77)
#define  REG_TC_HDMITX_PLL_3C_L       (REG_TC_HDMITX_PLL_BASE + 0x78)
#define  REG_TC_HDMITX_PLL_3C_H       (REG_TC_HDMITX_PLL_BASE + 0x79)
#define  REG_TC_HDMITX_PLL_3D_L       (REG_TC_HDMITX_PLL_BASE + 0x7A)
#define  REG_TC_HDMITX_PLL_3D_H       (REG_TC_HDMITX_PLL_BASE + 0x7B)
#define  REG_TC_HDMITX_PLL_3E_L       (REG_TC_HDMITX_PLL_BASE + 0x7C)
#define  REG_TC_HDMITX_PLL_3E_H       (REG_TC_HDMITX_PLL_BASE + 0x7D)
#define  REG_TC_HDMITX_PLL_3F_L       (REG_TC_HDMITX_PLL_BASE + 0x7E)
#define  REG_TC_HDMITX_PLL_3F_H       (REG_TC_HDMITX_PLL_BASE + 0x7F)
#define  REG_TC_HDMITX_PLL_40_L       (REG_TC_HDMITX_PLL_BASE + 0x80)
#define  REG_TC_HDMITX_PLL_40_H       (REG_TC_HDMITX_PLL_BASE + 0x81)
#define  REG_TC_HDMITX_PLL_41_L       (REG_TC_HDMITX_PLL_BASE + 0x82)
#define  REG_TC_HDMITX_PLL_41_H       (REG_TC_HDMITX_PLL_BASE + 0x83)
#define  REG_TC_HDMITX_PLL_42_L       (REG_TC_HDMITX_PLL_BASE + 0x84)
#define  REG_TC_HDMITX_PLL_42_H       (REG_TC_HDMITX_PLL_BASE + 0x85)
#define  REG_TC_HDMITX_PLL_43_L       (REG_TC_HDMITX_PLL_BASE + 0x86)
#define  REG_TC_HDMITX_PLL_43_H       (REG_TC_HDMITX_PLL_BASE + 0x87)
#define  REG_TC_HDMITX_PLL_44_L       (REG_TC_HDMITX_PLL_BASE + 0x88)
#define  REG_TC_HDMITX_PLL_44_H       (REG_TC_HDMITX_PLL_BASE + 0x89)
#define  REG_TC_HDMITX_PLL_45_L       (REG_TC_HDMITX_PLL_BASE + 0x8A)
#define  REG_TC_HDMITX_PLL_45_H       (REG_TC_HDMITX_PLL_BASE + 0x8B)
#define  REG_TC_HDMITX_PLL_46_L       (REG_TC_HDMITX_PLL_BASE + 0x8C)
#define  REG_TC_HDMITX_PLL_46_H       (REG_TC_HDMITX_PLL_BASE + 0x8D)
#define  REG_TC_HDMITX_PLL_47_L       (REG_TC_HDMITX_PLL_BASE + 0x8E)
#define  REG_TC_HDMITX_PLL_47_H       (REG_TC_HDMITX_PLL_BASE + 0x8F)
#define  REG_TC_HDMITX_PLL_48_L       (REG_TC_HDMITX_PLL_BASE + 0x90)
#define  REG_TC_HDMITX_PLL_48_H       (REG_TC_HDMITX_PLL_BASE + 0x91)
#define  REG_TC_HDMITX_PLL_49_L       (REG_TC_HDMITX_PLL_BASE + 0x92)
#define  REG_TC_HDMITX_PLL_49_H       (REG_TC_HDMITX_PLL_BASE + 0x93)
#define  REG_TC_HDMITX_PLL_4A_L       (REG_TC_HDMITX_PLL_BASE + 0x94)
#define  REG_TC_HDMITX_PLL_4A_H       (REG_TC_HDMITX_PLL_BASE + 0x95)
#define  REG_TC_HDMITX_PLL_4B_L       (REG_TC_HDMITX_PLL_BASE + 0x96)
#define  REG_TC_HDMITX_PLL_4B_H       (REG_TC_HDMITX_PLL_BASE + 0x97)
#define  REG_TC_HDMITX_PLL_4C_L       (REG_TC_HDMITX_PLL_BASE + 0x98)
#define  REG_TC_HDMITX_PLL_4C_H       (REG_TC_HDMITX_PLL_BASE + 0x99)
#define  REG_TC_HDMITX_PLL_4D_L       (REG_TC_HDMITX_PLL_BASE + 0x9A)
#define  REG_TC_HDMITX_PLL_4D_H       (REG_TC_HDMITX_PLL_BASE + 0x9B)
#define  REG_TC_HDMITX_PLL_4E_L       (REG_TC_HDMITX_PLL_BASE + 0x9C)
#define  REG_TC_HDMITX_PLL_4E_H       (REG_TC_HDMITX_PLL_BASE + 0x9D)
#define  REG_TC_HDMITX_PLL_4F_L       (REG_TC_HDMITX_PLL_BASE + 0x9E)
#define  REG_TC_HDMITX_PLL_4F_H       (REG_TC_HDMITX_PLL_BASE + 0x9F)
#define  REG_TC_HDMITX_PLL_50_L       (REG_TC_HDMITX_PLL_BASE + 0xA0)
#define  REG_TC_HDMITX_PLL_50_H       (REG_TC_HDMITX_PLL_BASE + 0xA1)
#define  REG_TC_HDMITX_PLL_51_L       (REG_TC_HDMITX_PLL_BASE + 0xA2)
#define  REG_TC_HDMITX_PLL_51_H       (REG_TC_HDMITX_PLL_BASE + 0xA3)
#define  REG_TC_HDMITX_PLL_52_L       (REG_TC_HDMITX_PLL_BASE + 0xA4)
#define  REG_TC_HDMITX_PLL_52_H       (REG_TC_HDMITX_PLL_BASE + 0xA5)
#define  REG_TC_HDMITX_PLL_53_L       (REG_TC_HDMITX_PLL_BASE + 0xA6)
#define  REG_TC_HDMITX_PLL_53_H       (REG_TC_HDMITX_PLL_BASE + 0xA7)
#define  REG_TC_HDMITX_PLL_54_L       (REG_TC_HDMITX_PLL_BASE + 0xA8)
#define  REG_TC_HDMITX_PLL_54_H       (REG_TC_HDMITX_PLL_BASE + 0xA9)
#define  REG_TC_HDMITX_PLL_55_L       (REG_TC_HDMITX_PLL_BASE + 0xAA)
#define  REG_TC_HDMITX_PLL_55_H       (REG_TC_HDMITX_PLL_BASE + 0xAB)
#define  REG_TC_HDMITX_PLL_56_L       (REG_TC_HDMITX_PLL_BASE + 0xAC)
#define  REG_TC_HDMITX_PLL_56_H       (REG_TC_HDMITX_PLL_BASE + 0xAD)
#define  REG_TC_HDMITX_PLL_57_L       (REG_TC_HDMITX_PLL_BASE + 0xAE)
#define  REG_TC_HDMITX_PLL_57_H       (REG_TC_HDMITX_PLL_BASE + 0xAF)
#define  REG_TC_HDMITX_PLL_58_L       (REG_TC_HDMITX_PLL_BASE + 0xB0)
#define  REG_TC_HDMITX_PLL_58_H       (REG_TC_HDMITX_PLL_BASE + 0xB1)
#define  REG_TC_HDMITX_PLL_59_L       (REG_TC_HDMITX_PLL_BASE + 0xB2)
#define  REG_TC_HDMITX_PLL_59_H       (REG_TC_HDMITX_PLL_BASE + 0xB3)
#define  REG_TC_HDMITX_PLL_5A_L       (REG_TC_HDMITX_PLL_BASE + 0xB4)
#define  REG_TC_HDMITX_PLL_5A_H       (REG_TC_HDMITX_PLL_BASE + 0xB5)
#define  REG_TC_HDMITX_PLL_5B_L       (REG_TC_HDMITX_PLL_BASE + 0xB6)
#define  REG_TC_HDMITX_PLL_5B_H       (REG_TC_HDMITX_PLL_BASE + 0xB7)
#define  REG_TC_HDMITX_PLL_5C_L       (REG_TC_HDMITX_PLL_BASE + 0xB8)
#define  REG_TC_HDMITX_PLL_5C_H       (REG_TC_HDMITX_PLL_BASE + 0xB9)
#define  REG_TC_HDMITX_PLL_5D_L       (REG_TC_HDMITX_PLL_BASE + 0xBA)
#define  REG_TC_HDMITX_PLL_5D_H       (REG_TC_HDMITX_PLL_BASE + 0xBB)
#define  REG_TC_HDMITX_PLL_5E_L       (REG_TC_HDMITX_PLL_BASE + 0xBC)
#define  REG_TC_HDMITX_PLL_5E_H       (REG_TC_HDMITX_PLL_BASE + 0xBD)
#define  REG_TC_HDMITX_PLL_5F_L       (REG_TC_HDMITX_PLL_BASE + 0xBE)
#define  REG_TC_HDMITX_PLL_5F_H       (REG_TC_HDMITX_PLL_BASE + 0xBF)
#define  REG_TC_HDMITX_PLL_60_L       (REG_TC_HDMITX_PLL_BASE + 0xC0)
#define  REG_TC_HDMITX_PLL_60_H       (REG_TC_HDMITX_PLL_BASE + 0xC1)
#define  REG_TC_HDMITX_PLL_61_L       (REG_TC_HDMITX_PLL_BASE + 0xC2)
#define  REG_TC_HDMITX_PLL_61_H       (REG_TC_HDMITX_PLL_BASE + 0xC3)
#define  REG_TC_HDMITX_PLL_62_L       (REG_TC_HDMITX_PLL_BASE + 0xC4)
#define  REG_TC_HDMITX_PLL_62_H       (REG_TC_HDMITX_PLL_BASE + 0xC5)
#define  REG_TC_HDMITX_PLL_63_L       (REG_TC_HDMITX_PLL_BASE + 0xC6)
#define  REG_TC_HDMITX_PLL_63_H       (REG_TC_HDMITX_PLL_BASE + 0xC7)
#define  REG_TC_HDMITX_PLL_64_L       (REG_TC_HDMITX_PLL_BASE + 0xC8)
#define  REG_TC_HDMITX_PLL_64_H       (REG_TC_HDMITX_PLL_BASE + 0xC9)
#define  REG_TC_HDMITX_PLL_65_L       (REG_TC_HDMITX_PLL_BASE + 0xCA)
#define  REG_TC_HDMITX_PLL_65_H       (REG_TC_HDMITX_PLL_BASE + 0xCB)
#define  REG_TC_HDMITX_PLL_66_L       (REG_TC_HDMITX_PLL_BASE + 0xCC)
#define  REG_TC_HDMITX_PLL_66_H       (REG_TC_HDMITX_PLL_BASE + 0xCD)
#define  REG_TC_HDMITX_PLL_67_L       (REG_TC_HDMITX_PLL_BASE + 0xCE)
#define  REG_TC_HDMITX_PLL_67_H       (REG_TC_HDMITX_PLL_BASE + 0xCF)
#define  REG_TC_HDMITX_PLL_68_L       (REG_TC_HDMITX_PLL_BASE + 0xD0)
#define  REG_TC_HDMITX_PLL_68_H       (REG_TC_HDMITX_PLL_BASE + 0xD1)
#define  REG_TC_HDMITX_PLL_69_L       (REG_TC_HDMITX_PLL_BASE + 0xD2)
#define  REG_TC_HDMITX_PLL_69_H       (REG_TC_HDMITX_PLL_BASE + 0xD3)
#define  REG_TC_HDMITX_PLL_6A_L       (REG_TC_HDMITX_PLL_BASE + 0xD4)
#define  REG_TC_HDMITX_PLL_6A_H       (REG_TC_HDMITX_PLL_BASE + 0xD5)
#define  REG_TC_HDMITX_PLL_6B_L       (REG_TC_HDMITX_PLL_BASE + 0xD6)
#define  REG_TC_HDMITX_PLL_6B_H       (REG_TC_HDMITX_PLL_BASE + 0xD7)
#define  REG_TC_HDMITX_PLL_6C_L       (REG_TC_HDMITX_PLL_BASE + 0xD8)
#define  REG_TC_HDMITX_PLL_6C_H       (REG_TC_HDMITX_PLL_BASE + 0xD9)
#define  REG_TC_HDMITX_PLL_6D_L       (REG_TC_HDMITX_PLL_BASE + 0xDA)
#define  REG_TC_HDMITX_PLL_6D_H       (REG_TC_HDMITX_PLL_BASE + 0xDB)
#define  REG_TC_HDMITX_PLL_6E_L       (REG_TC_HDMITX_PLL_BASE + 0xDC)
#define  REG_TC_HDMITX_PLL_6E_H       (REG_TC_HDMITX_PLL_BASE + 0xDD)
#define  REG_TC_HDMITX_PLL_6F_L       (REG_TC_HDMITX_PLL_BASE + 0xDE)
#define  REG_TC_HDMITX_PLL_6F_H       (REG_TC_HDMITX_PLL_BASE + 0xDF)
#define  REG_TC_HDMITX_PLL_70_L       (REG_TC_HDMITX_PLL_BASE + 0xE0)
#define  REG_TC_HDMITX_PLL_70_H       (REG_TC_HDMITX_PLL_BASE + 0xE1)
#define  REG_TC_HDMITX_PLL_71_L       (REG_TC_HDMITX_PLL_BASE + 0xE2)
#define  REG_TC_HDMITX_PLL_71_H       (REG_TC_HDMITX_PLL_BASE + 0xE3)
#define  REG_TC_HDMITX_PLL_72_L       (REG_TC_HDMITX_PLL_BASE + 0xE4)
#define  REG_TC_HDMITX_PLL_72_H       (REG_TC_HDMITX_PLL_BASE + 0xE5)
#define  REG_TC_HDMITX_PLL_73_L       (REG_TC_HDMITX_PLL_BASE + 0xE6)
#define  REG_TC_HDMITX_PLL_73_H       (REG_TC_HDMITX_PLL_BASE + 0xE7)
#define  REG_TC_HDMITX_PLL_74_L       (REG_TC_HDMITX_PLL_BASE + 0xE8)
#define  REG_TC_HDMITX_PLL_74_H       (REG_TC_HDMITX_PLL_BASE + 0xE9)
#define  REG_TC_HDMITX_PLL_75_L       (REG_TC_HDMITX_PLL_BASE + 0xEA)
#define  REG_TC_HDMITX_PLL_75_H       (REG_TC_HDMITX_PLL_BASE + 0xEB)
#define  REG_TC_HDMITX_PLL_76_L       (REG_TC_HDMITX_PLL_BASE + 0xEC)
#define  REG_TC_HDMITX_PLL_76_H       (REG_TC_HDMITX_PLL_BASE + 0xED)
#define  REG_TC_HDMITX_PLL_77_L       (REG_TC_HDMITX_PLL_BASE + 0xEE)
#define  REG_TC_HDMITX_PLL_77_H       (REG_TC_HDMITX_PLL_BASE + 0xEF)
#define  REG_TC_HDMITX_PLL_78_L       (REG_TC_HDMITX_PLL_BASE + 0xF0)
#define  REG_TC_HDMITX_PLL_78_H       (REG_TC_HDMITX_PLL_BASE + 0xF1)
#define  REG_TC_HDMITX_PLL_79_L       (REG_TC_HDMITX_PLL_BASE + 0xF2)
#define  REG_TC_HDMITX_PLL_79_H       (REG_TC_HDMITX_PLL_BASE + 0xF3)
#define  REG_TC_HDMITX_PLL_7A_L       (REG_TC_HDMITX_PLL_BASE + 0xF4)
#define  REG_TC_HDMITX_PLL_7A_H       (REG_TC_HDMITX_PLL_BASE + 0xF5)
#define  REG_TC_HDMITX_PLL_7B_L       (REG_TC_HDMITX_PLL_BASE + 0xF6)
#define  REG_TC_HDMITX_PLL_7B_H       (REG_TC_HDMITX_PLL_BASE + 0xF7)
#define  REG_TC_HDMITX_PLL_7C_L       (REG_TC_HDMITX_PLL_BASE + 0xF8)
#define  REG_TC_HDMITX_PLL_7C_H       (REG_TC_HDMITX_PLL_BASE + 0xF9)
#define  REG_TC_HDMITX_PLL_7D_L       (REG_TC_HDMITX_PLL_BASE + 0xFA)
#define  REG_TC_HDMITX_PLL_7D_H       (REG_TC_HDMITX_PLL_BASE + 0xFB)
#define  REG_TC_HDMITX_PLL_7E_L       (REG_TC_HDMITX_PLL_BASE + 0xFC)
#define  REG_TC_HDMITX_PLL_7E_H       (REG_TC_HDMITX_PLL_BASE + 0xFD)
#define  REG_TC_HDMITX_PLL_7F_L       (REG_TC_HDMITX_PLL_BASE + 0xFE)
#define  REG_TC_HDMITX_PLL_7F_H       (REG_TC_HDMITX_PLL_BASE + 0xFF)

#define  REG_TC_HDMITX_PM_00_L       (REG_TC_HDMITX_PM_BASE + 0x00)
#define  REG_TC_HDMITX_PM_00_H       (REG_TC_HDMITX_PM_BASE + 0x01)
#define  REG_TC_HDMITX_PM_01_L       (REG_TC_HDMITX_PM_BASE + 0x02)
#define  REG_TC_HDMITX_PM_01_H       (REG_TC_HDMITX_PM_BASE + 0x03)
#define  REG_TC_HDMITX_PM_02_L       (REG_TC_HDMITX_PM_BASE + 0x04)
#define  REG_TC_HDMITX_PM_02_H       (REG_TC_HDMITX_PM_BASE + 0x05)
#define  REG_TC_HDMITX_PM_03_L       (REG_TC_HDMITX_PM_BASE + 0x06)
#define  REG_TC_HDMITX_PM_03_H       (REG_TC_HDMITX_PM_BASE + 0x07)
#define  REG_TC_HDMITX_PM_04_L       (REG_TC_HDMITX_PM_BASE + 0x08)
#define  REG_TC_HDMITX_PM_04_H       (REG_TC_HDMITX_PM_BASE + 0x09)
#define  REG_TC_HDMITX_PM_05_L       (REG_TC_HDMITX_PM_BASE + 0x0A)
#define  REG_TC_HDMITX_PM_05_H       (REG_TC_HDMITX_PM_BASE + 0x0B)
#define  REG_TC_HDMITX_PM_06_L       (REG_TC_HDMITX_PM_BASE + 0x0C)
#define  REG_TC_HDMITX_PM_06_H       (REG_TC_HDMITX_PM_BASE + 0x0D)
#define  REG_TC_HDMITX_PM_07_L       (REG_TC_HDMITX_PM_BASE + 0x0E)
#define  REG_TC_HDMITX_PM_07_H       (REG_TC_HDMITX_PM_BASE + 0x0F)
#define  REG_TC_HDMITX_PM_08_L       (REG_TC_HDMITX_PM_BASE + 0x10)
#define  REG_TC_HDMITX_PM_08_H       (REG_TC_HDMITX_PM_BASE + 0x11)
#define  REG_TC_HDMITX_PM_09_L       (REG_TC_HDMITX_PM_BASE + 0x12)
#define  REG_TC_HDMITX_PM_09_H       (REG_TC_HDMITX_PM_BASE + 0x13)
#define  REG_TC_HDMITX_PM_0A_L       (REG_TC_HDMITX_PM_BASE + 0x14)
#define  REG_TC_HDMITX_PM_0A_H       (REG_TC_HDMITX_PM_BASE + 0x15)
#define  REG_TC_HDMITX_PM_0B_L       (REG_TC_HDMITX_PM_BASE + 0x16)
#define  REG_TC_HDMITX_PM_0B_H       (REG_TC_HDMITX_PM_BASE + 0x17)
#define  REG_TC_HDMITX_PM_0C_L       (REG_TC_HDMITX_PM_BASE + 0x18)
#define  REG_TC_HDMITX_PM_0C_H       (REG_TC_HDMITX_PM_BASE + 0x19)
#define  REG_TC_HDMITX_PM_0D_L       (REG_TC_HDMITX_PM_BASE + 0x1A)
#define  REG_TC_HDMITX_PM_0D_H       (REG_TC_HDMITX_PM_BASE + 0x1B)
#define  REG_TC_HDMITX_PM_0E_L       (REG_TC_HDMITX_PM_BASE + 0x1C)
#define  REG_TC_HDMITX_PM_0E_H       (REG_TC_HDMITX_PM_BASE + 0x1D)
#define  REG_TC_HDMITX_PM_0F_L       (REG_TC_HDMITX_PM_BASE + 0x1E)
#define  REG_TC_HDMITX_PM_0F_H       (REG_TC_HDMITX_PM_BASE + 0x1F)
#define  REG_TC_HDMITX_PM_10_L       (REG_TC_HDMITX_PM_BASE + 0x20)
#define  REG_TC_HDMITX_PM_10_H       (REG_TC_HDMITX_PM_BASE + 0x21)
#define  REG_TC_HDMITX_PM_11_L       (REG_TC_HDMITX_PM_BASE + 0x22)
#define  REG_TC_HDMITX_PM_11_H       (REG_TC_HDMITX_PM_BASE + 0x23)
#define  REG_TC_HDMITX_PM_12_L       (REG_TC_HDMITX_PM_BASE + 0x24)
#define  REG_TC_HDMITX_PM_12_H       (REG_TC_HDMITX_PM_BASE + 0x25)
#define  REG_TC_HDMITX_PM_13_L       (REG_TC_HDMITX_PM_BASE + 0x26)
#define  REG_TC_HDMITX_PM_13_H       (REG_TC_HDMITX_PM_BASE + 0x27)
#define  REG_TC_HDMITX_PM_14_L       (REG_TC_HDMITX_PM_BASE + 0x28)
#define  REG_TC_HDMITX_PM_14_H       (REG_TC_HDMITX_PM_BASE + 0x29)
#define  REG_TC_HDMITX_PM_15_L       (REG_TC_HDMITX_PM_BASE + 0x2A)
#define  REG_TC_HDMITX_PM_15_H       (REG_TC_HDMITX_PM_BASE + 0x2B)
#define  REG_TC_HDMITX_PM_16_L       (REG_TC_HDMITX_PM_BASE + 0x2C)
#define  REG_TC_HDMITX_PM_16_H       (REG_TC_HDMITX_PM_BASE + 0x2D)
#define  REG_TC_HDMITX_PM_17_L       (REG_TC_HDMITX_PM_BASE + 0x2E)
#define  REG_TC_HDMITX_PM_17_H       (REG_TC_HDMITX_PM_BASE + 0x2F)
#define  REG_TC_HDMITX_PM_18_L       (REG_TC_HDMITX_PM_BASE + 0x30)
#define  REG_TC_HDMITX_PM_18_H       (REG_TC_HDMITX_PM_BASE + 0x31)
#define  REG_TC_HDMITX_PM_19_L       (REG_TC_HDMITX_PM_BASE + 0x32)
#define  REG_TC_HDMITX_PM_19_H       (REG_TC_HDMITX_PM_BASE + 0x33)
#define  REG_TC_HDMITX_PM_1A_L       (REG_TC_HDMITX_PM_BASE + 0x34)
#define  REG_TC_HDMITX_PM_1A_H       (REG_TC_HDMITX_PM_BASE + 0x35)
#define  REG_TC_HDMITX_PM_1B_L       (REG_TC_HDMITX_PM_BASE + 0x36)
#define  REG_TC_HDMITX_PM_1B_H       (REG_TC_HDMITX_PM_BASE + 0x37)
#define  REG_TC_HDMITX_PM_1C_L       (REG_TC_HDMITX_PM_BASE + 0x38)
#define  REG_TC_HDMITX_PM_1C_H       (REG_TC_HDMITX_PM_BASE + 0x39)
#define  REG_TC_HDMITX_PM_1D_L       (REG_TC_HDMITX_PM_BASE + 0x3A)
#define  REG_TC_HDMITX_PM_1D_H       (REG_TC_HDMITX_PM_BASE + 0x3B)
#define  REG_TC_HDMITX_PM_1E_L       (REG_TC_HDMITX_PM_BASE + 0x3C)
#define  REG_TC_HDMITX_PM_1E_H       (REG_TC_HDMITX_PM_BASE + 0x3D)
#define  REG_TC_HDMITX_PM_1F_L       (REG_TC_HDMITX_PM_BASE + 0x3E)
#define  REG_TC_HDMITX_PM_1F_H       (REG_TC_HDMITX_PM_BASE + 0x3F)
#define  REG_TC_HDMITX_PM_20_L       (REG_TC_HDMITX_PM_BASE + 0x40)
#define  REG_TC_HDMITX_PM_20_H       (REG_TC_HDMITX_PM_BASE + 0x41)
#define  REG_TC_HDMITX_PM_21_L       (REG_TC_HDMITX_PM_BASE + 0x42)
#define  REG_TC_HDMITX_PM_21_H       (REG_TC_HDMITX_PM_BASE + 0x43)
#define  REG_TC_HDMITX_PM_22_L       (REG_TC_HDMITX_PM_BASE + 0x44)
#define  REG_TC_HDMITX_PM_22_H       (REG_TC_HDMITX_PM_BASE + 0x45)
#define  REG_TC_HDMITX_PM_23_L       (REG_TC_HDMITX_PM_BASE + 0x46)
#define  REG_TC_HDMITX_PM_23_H       (REG_TC_HDMITX_PM_BASE + 0x47)
#define  REG_TC_HDMITX_PM_24_L       (REG_TC_HDMITX_PM_BASE + 0x48)
#define  REG_TC_HDMITX_PM_24_H       (REG_TC_HDMITX_PM_BASE + 0x49)
#define  REG_TC_HDMITX_PM_25_L       (REG_TC_HDMITX_PM_BASE + 0x4A)
#define  REG_TC_HDMITX_PM_25_H       (REG_TC_HDMITX_PM_BASE + 0x4B)
#define  REG_TC_HDMITX_PM_26_L       (REG_TC_HDMITX_PM_BASE + 0x4C)
#define  REG_TC_HDMITX_PM_26_H       (REG_TC_HDMITX_PM_BASE + 0x4D)
#define  REG_TC_HDMITX_PM_27_L       (REG_TC_HDMITX_PM_BASE + 0x4E)
#define  REG_TC_HDMITX_PM_27_H       (REG_TC_HDMITX_PM_BASE + 0x4F)
#define  REG_TC_HDMITX_PM_28_L       (REG_TC_HDMITX_PM_BASE + 0x50)
#define  REG_TC_HDMITX_PM_28_H       (REG_TC_HDMITX_PM_BASE + 0x51)
#define  REG_TC_HDMITX_PM_29_L       (REG_TC_HDMITX_PM_BASE + 0x52)
#define  REG_TC_HDMITX_PM_29_H       (REG_TC_HDMITX_PM_BASE + 0x53)
#define  REG_TC_HDMITX_PM_2A_L       (REG_TC_HDMITX_PM_BASE + 0x54)
#define  REG_TC_HDMITX_PM_2A_H       (REG_TC_HDMITX_PM_BASE + 0x55)
#define  REG_TC_HDMITX_PM_2B_L       (REG_TC_HDMITX_PM_BASE + 0x56)
#define  REG_TC_HDMITX_PM_2B_H       (REG_TC_HDMITX_PM_BASE + 0x57)
#define  REG_TC_HDMITX_PM_2C_L       (REG_TC_HDMITX_PM_BASE + 0x58)
#define  REG_TC_HDMITX_PM_2C_H       (REG_TC_HDMITX_PM_BASE + 0x59)
#define  REG_TC_HDMITX_PM_2D_L       (REG_TC_HDMITX_PM_BASE + 0x5A)
#define  REG_TC_HDMITX_PM_2D_H       (REG_TC_HDMITX_PM_BASE + 0x5B)
#define  REG_TC_HDMITX_PM_2E_L       (REG_TC_HDMITX_PM_BASE + 0x5C)
#define  REG_TC_HDMITX_PM_2E_H       (REG_TC_HDMITX_PM_BASE + 0x5D)
#define  REG_TC_HDMITX_PM_2F_L       (REG_TC_HDMITX_PM_BASE + 0x5E)
#define  REG_TC_HDMITX_PM_2F_H       (REG_TC_HDMITX_PM_BASE + 0x5F)
#define  REG_TC_HDMITX_PM_30_L       (REG_TC_HDMITX_PM_BASE + 0x60)
#define  REG_TC_HDMITX_PM_30_H       (REG_TC_HDMITX_PM_BASE + 0x61)
#define  REG_TC_HDMITX_PM_31_L       (REG_TC_HDMITX_PM_BASE + 0x62)
#define  REG_TC_HDMITX_PM_31_H       (REG_TC_HDMITX_PM_BASE + 0x63)
#define  REG_TC_HDMITX_PM_32_L       (REG_TC_HDMITX_PM_BASE + 0x64)
#define  REG_TC_HDMITX_PM_32_H       (REG_TC_HDMITX_PM_BASE + 0x65)
#define  REG_TC_HDMITX_PM_33_L       (REG_TC_HDMITX_PM_BASE + 0x66)
#define  REG_TC_HDMITX_PM_33_H       (REG_TC_HDMITX_PM_BASE + 0x67)
#define  REG_TC_HDMITX_PM_34_L       (REG_TC_HDMITX_PM_BASE + 0x68)
#define  REG_TC_HDMITX_PM_34_H       (REG_TC_HDMITX_PM_BASE + 0x69)
#define  REG_TC_HDMITX_PM_35_L       (REG_TC_HDMITX_PM_BASE + 0x6A)
#define  REG_TC_HDMITX_PM_35_H       (REG_TC_HDMITX_PM_BASE + 0x6B)
#define  REG_TC_HDMITX_PM_36_L       (REG_TC_HDMITX_PM_BASE + 0x6C)
#define  REG_TC_HDMITX_PM_36_H       (REG_TC_HDMITX_PM_BASE + 0x6D)
#define  REG_TC_HDMITX_PM_37_L       (REG_TC_HDMITX_PM_BASE + 0x6E)
#define  REG_TC_HDMITX_PM_37_H       (REG_TC_HDMITX_PM_BASE + 0x6F)
#define  REG_TC_HDMITX_PM_38_L       (REG_TC_HDMITX_PM_BASE + 0x70)
#define  REG_TC_HDMITX_PM_38_H       (REG_TC_HDMITX_PM_BASE + 0x71)
#define  REG_TC_HDMITX_PM_39_L       (REG_TC_HDMITX_PM_BASE + 0x72)
#define  REG_TC_HDMITX_PM_39_H       (REG_TC_HDMITX_PM_BASE + 0x73)
#define  REG_TC_HDMITX_PM_3A_L       (REG_TC_HDMITX_PM_BASE + 0x74)
#define  REG_TC_HDMITX_PM_3A_H       (REG_TC_HDMITX_PM_BASE + 0x75)
#define  REG_TC_HDMITX_PM_3B_L       (REG_TC_HDMITX_PM_BASE + 0x76)
#define  REG_TC_HDMITX_PM_3B_H       (REG_TC_HDMITX_PM_BASE + 0x77)
#define  REG_TC_HDMITX_PM_3C_L       (REG_TC_HDMITX_PM_BASE + 0x78)
#define  REG_TC_HDMITX_PM_3C_H       (REG_TC_HDMITX_PM_BASE + 0x79)
#define  REG_TC_HDMITX_PM_3D_L       (REG_TC_HDMITX_PM_BASE + 0x7A)
#define  REG_TC_HDMITX_PM_3D_H       (REG_TC_HDMITX_PM_BASE + 0x7B)
#define  REG_TC_HDMITX_PM_3E_L       (REG_TC_HDMITX_PM_BASE + 0x7C)
#define  REG_TC_HDMITX_PM_3E_H       (REG_TC_HDMITX_PM_BASE + 0x7D)
#define  REG_TC_HDMITX_PM_3F_L       (REG_TC_HDMITX_PM_BASE + 0x7E)
#define  REG_TC_HDMITX_PM_3F_H       (REG_TC_HDMITX_PM_BASE + 0x7F)
#define  REG_TC_HDMITX_PM_40_L       (REG_TC_HDMITX_PM_BASE + 0x80)
#define  REG_TC_HDMITX_PM_40_H       (REG_TC_HDMITX_PM_BASE + 0x81)
#define  REG_TC_HDMITX_PM_41_L       (REG_TC_HDMITX_PM_BASE + 0x82)
#define  REG_TC_HDMITX_PM_41_H       (REG_TC_HDMITX_PM_BASE + 0x83)
#define  REG_TC_HDMITX_PM_42_L       (REG_TC_HDMITX_PM_BASE + 0x84)
#define  REG_TC_HDMITX_PM_42_H       (REG_TC_HDMITX_PM_BASE + 0x85)
#define  REG_TC_HDMITX_PM_43_L       (REG_TC_HDMITX_PM_BASE + 0x86)
#define  REG_TC_HDMITX_PM_43_H       (REG_TC_HDMITX_PM_BASE + 0x87)
#define  REG_TC_HDMITX_PM_44_L       (REG_TC_HDMITX_PM_BASE + 0x88)
#define  REG_TC_HDMITX_PM_44_H       (REG_TC_HDMITX_PM_BASE + 0x89)
#define  REG_TC_HDMITX_PM_45_L       (REG_TC_HDMITX_PM_BASE + 0x8A)
#define  REG_TC_HDMITX_PM_45_H       (REG_TC_HDMITX_PM_BASE + 0x8B)
#define  REG_TC_HDMITX_PM_46_L       (REG_TC_HDMITX_PM_BASE + 0x8C)
#define  REG_TC_HDMITX_PM_46_H       (REG_TC_HDMITX_PM_BASE + 0x8D)
#define  REG_TC_HDMITX_PM_47_L       (REG_TC_HDMITX_PM_BASE + 0x8E)
#define  REG_TC_HDMITX_PM_47_H       (REG_TC_HDMITX_PM_BASE + 0x8F)
#define  REG_TC_HDMITX_PM_48_L       (REG_TC_HDMITX_PM_BASE + 0x90)
#define  REG_TC_HDMITX_PM_48_H       (REG_TC_HDMITX_PM_BASE + 0x91)
#define  REG_TC_HDMITX_PM_49_L       (REG_TC_HDMITX_PM_BASE + 0x92)
#define  REG_TC_HDMITX_PM_49_H       (REG_TC_HDMITX_PM_BASE + 0x93)
#define  REG_TC_HDMITX_PM_4A_L       (REG_TC_HDMITX_PM_BASE + 0x94)
#define  REG_TC_HDMITX_PM_4A_H       (REG_TC_HDMITX_PM_BASE + 0x95)
#define  REG_TC_HDMITX_PM_4B_L       (REG_TC_HDMITX_PM_BASE + 0x96)
#define  REG_TC_HDMITX_PM_4B_H       (REG_TC_HDMITX_PM_BASE + 0x97)
#define  REG_TC_HDMITX_PM_4C_L       (REG_TC_HDMITX_PM_BASE + 0x98)
#define  REG_TC_HDMITX_PM_4C_H       (REG_TC_HDMITX_PM_BASE + 0x99)
#define  REG_TC_HDMITX_PM_4D_L       (REG_TC_HDMITX_PM_BASE + 0x9A)
#define  REG_TC_HDMITX_PM_4D_H       (REG_TC_HDMITX_PM_BASE + 0x9B)
#define  REG_TC_HDMITX_PM_4E_L       (REG_TC_HDMITX_PM_BASE + 0x9C)
#define  REG_TC_HDMITX_PM_4E_H       (REG_TC_HDMITX_PM_BASE + 0x9D)
#define  REG_TC_HDMITX_PM_4F_L       (REG_TC_HDMITX_PM_BASE + 0x9E)
#define  REG_TC_HDMITX_PM_4F_H       (REG_TC_HDMITX_PM_BASE + 0x9F)
#define  REG_TC_HDMITX_PM_50_L       (REG_TC_HDMITX_PM_BASE + 0xA0)
#define  REG_TC_HDMITX_PM_50_H       (REG_TC_HDMITX_PM_BASE + 0xA1)
#define  REG_TC_HDMITX_PM_51_L       (REG_TC_HDMITX_PM_BASE + 0xA2)
#define  REG_TC_HDMITX_PM_51_H       (REG_TC_HDMITX_PM_BASE + 0xA3)
#define  REG_TC_HDMITX_PM_52_L       (REG_TC_HDMITX_PM_BASE + 0xA4)
#define  REG_TC_HDMITX_PM_52_H       (REG_TC_HDMITX_PM_BASE + 0xA5)
#define  REG_TC_HDMITX_PM_53_L       (REG_TC_HDMITX_PM_BASE + 0xA6)
#define  REG_TC_HDMITX_PM_53_H       (REG_TC_HDMITX_PM_BASE + 0xA7)
#define  REG_TC_HDMITX_PM_54_L       (REG_TC_HDMITX_PM_BASE + 0xA8)
#define  REG_TC_HDMITX_PM_54_H       (REG_TC_HDMITX_PM_BASE + 0xA9)
#define  REG_TC_HDMITX_PM_55_L       (REG_TC_HDMITX_PM_BASE + 0xAA)
#define  REG_TC_HDMITX_PM_55_H       (REG_TC_HDMITX_PM_BASE + 0xAB)
#define  REG_TC_HDMITX_PM_56_L       (REG_TC_HDMITX_PM_BASE + 0xAC)
#define  REG_TC_HDMITX_PM_56_H       (REG_TC_HDMITX_PM_BASE + 0xAD)
#define  REG_TC_HDMITX_PM_57_L       (REG_TC_HDMITX_PM_BASE + 0xAE)
#define  REG_TC_HDMITX_PM_57_H       (REG_TC_HDMITX_PM_BASE + 0xAF)
#define  REG_TC_HDMITX_PM_58_L       (REG_TC_HDMITX_PM_BASE + 0xB0)
#define  REG_TC_HDMITX_PM_58_H       (REG_TC_HDMITX_PM_BASE + 0xB1)
#define  REG_TC_HDMITX_PM_59_L       (REG_TC_HDMITX_PM_BASE + 0xB2)
#define  REG_TC_HDMITX_PM_59_H       (REG_TC_HDMITX_PM_BASE + 0xB3)
#define  REG_TC_HDMITX_PM_5A_L       (REG_TC_HDMITX_PM_BASE + 0xB4)
#define  REG_TC_HDMITX_PM_5A_H       (REG_TC_HDMITX_PM_BASE + 0xB5)
#define  REG_TC_HDMITX_PM_5B_L       (REG_TC_HDMITX_PM_BASE + 0xB6)
#define  REG_TC_HDMITX_PM_5B_H       (REG_TC_HDMITX_PM_BASE + 0xB7)
#define  REG_TC_HDMITX_PM_5C_L       (REG_TC_HDMITX_PM_BASE + 0xB8)
#define  REG_TC_HDMITX_PM_5C_H       (REG_TC_HDMITX_PM_BASE + 0xB9)
#define  REG_TC_HDMITX_PM_5D_L       (REG_TC_HDMITX_PM_BASE + 0xBA)
#define  REG_TC_HDMITX_PM_5D_H       (REG_TC_HDMITX_PM_BASE + 0xBB)
#define  REG_TC_HDMITX_PM_5E_L       (REG_TC_HDMITX_PM_BASE + 0xBC)
#define  REG_TC_HDMITX_PM_5E_H       (REG_TC_HDMITX_PM_BASE + 0xBD)
#define  REG_TC_HDMITX_PM_5F_L       (REG_TC_HDMITX_PM_BASE + 0xBE)
#define  REG_TC_HDMITX_PM_5F_H       (REG_TC_HDMITX_PM_BASE + 0xBF)
#define  REG_TC_HDMITX_PM_60_L       (REG_TC_HDMITX_PM_BASE + 0xC0)
#define  REG_TC_HDMITX_PM_60_H       (REG_TC_HDMITX_PM_BASE + 0xC1)
#define  REG_TC_HDMITX_PM_61_L       (REG_TC_HDMITX_PM_BASE + 0xC2)
#define  REG_TC_HDMITX_PM_61_H       (REG_TC_HDMITX_PM_BASE + 0xC3)
#define  REG_TC_HDMITX_PM_62_L       (REG_TC_HDMITX_PM_BASE + 0xC4)
#define  REG_TC_HDMITX_PM_62_H       (REG_TC_HDMITX_PM_BASE + 0xC5)
#define  REG_TC_HDMITX_PM_63_L       (REG_TC_HDMITX_PM_BASE + 0xC6)
#define  REG_TC_HDMITX_PM_63_H       (REG_TC_HDMITX_PM_BASE + 0xC7)
#define  REG_TC_HDMITX_PM_64_L       (REG_TC_HDMITX_PM_BASE + 0xC8)
#define  REG_TC_HDMITX_PM_64_H       (REG_TC_HDMITX_PM_BASE + 0xC9)
#define  REG_TC_HDMITX_PM_65_L       (REG_TC_HDMITX_PM_BASE + 0xCA)
#define  REG_TC_HDMITX_PM_65_H       (REG_TC_HDMITX_PM_BASE + 0xCB)
#define  REG_TC_HDMITX_PM_66_L       (REG_TC_HDMITX_PM_BASE + 0xCC)
#define  REG_TC_HDMITX_PM_66_H       (REG_TC_HDMITX_PM_BASE + 0xCD)
#define  REG_TC_HDMITX_PM_67_L       (REG_TC_HDMITX_PM_BASE + 0xCE)
#define  REG_TC_HDMITX_PM_67_H       (REG_TC_HDMITX_PM_BASE + 0xCF)
#define  REG_TC_HDMITX_PM_68_L       (REG_TC_HDMITX_PM_BASE + 0xD0)
#define  REG_TC_HDMITX_PM_68_H       (REG_TC_HDMITX_PM_BASE + 0xD1)
#define  REG_TC_HDMITX_PM_69_L       (REG_TC_HDMITX_PM_BASE + 0xD2)
#define  REG_TC_HDMITX_PM_69_H       (REG_TC_HDMITX_PM_BASE + 0xD3)
#define  REG_TC_HDMITX_PM_6A_L       (REG_TC_HDMITX_PM_BASE + 0xD4)
#define  REG_TC_HDMITX_PM_6A_H       (REG_TC_HDMITX_PM_BASE + 0xD5)
#define  REG_TC_HDMITX_PM_6B_L       (REG_TC_HDMITX_PM_BASE + 0xD6)
#define  REG_TC_HDMITX_PM_6B_H       (REG_TC_HDMITX_PM_BASE + 0xD7)
#define  REG_TC_HDMITX_PM_6C_L       (REG_TC_HDMITX_PM_BASE + 0xD8)
#define  REG_TC_HDMITX_PM_6C_H       (REG_TC_HDMITX_PM_BASE + 0xD9)
#define  REG_TC_HDMITX_PM_6D_L       (REG_TC_HDMITX_PM_BASE + 0xDA)
#define  REG_TC_HDMITX_PM_6D_H       (REG_TC_HDMITX_PM_BASE + 0xDB)
#define  REG_TC_HDMITX_PM_6E_L       (REG_TC_HDMITX_PM_BASE + 0xDC)
#define  REG_TC_HDMITX_PM_6E_H       (REG_TC_HDMITX_PM_BASE + 0xDD)
#define  REG_TC_HDMITX_PM_6F_L       (REG_TC_HDMITX_PM_BASE + 0xDE)
#define  REG_TC_HDMITX_PM_6F_H       (REG_TC_HDMITX_PM_BASE + 0xDF)
#define  REG_TC_HDMITX_PM_70_L       (REG_TC_HDMITX_PM_BASE + 0xE0)
#define  REG_TC_HDMITX_PM_70_H       (REG_TC_HDMITX_PM_BASE + 0xE1)
#define  REG_TC_HDMITX_PM_71_L       (REG_TC_HDMITX_PM_BASE + 0xE2)
#define  REG_TC_HDMITX_PM_71_H       (REG_TC_HDMITX_PM_BASE + 0xE3)
#define  REG_TC_HDMITX_PM_72_L       (REG_TC_HDMITX_PM_BASE + 0xE4)
#define  REG_TC_HDMITX_PM_72_H       (REG_TC_HDMITX_PM_BASE + 0xE5)
#define  REG_TC_HDMITX_PM_73_L       (REG_TC_HDMITX_PM_BASE + 0xE6)
#define  REG_TC_HDMITX_PM_73_H       (REG_TC_HDMITX_PM_BASE + 0xE7)
#define  REG_TC_HDMITX_PM_74_L       (REG_TC_HDMITX_PM_BASE + 0xE8)
#define  REG_TC_HDMITX_PM_74_H       (REG_TC_HDMITX_PM_BASE + 0xE9)
#define  REG_TC_HDMITX_PM_75_L       (REG_TC_HDMITX_PM_BASE + 0xEA)
#define  REG_TC_HDMITX_PM_75_H       (REG_TC_HDMITX_PM_BASE + 0xEB)
#define  REG_TC_HDMITX_PM_76_L       (REG_TC_HDMITX_PM_BASE + 0xEC)
#define  REG_TC_HDMITX_PM_76_H       (REG_TC_HDMITX_PM_BASE + 0xED)
#define  REG_TC_HDMITX_PM_77_L       (REG_TC_HDMITX_PM_BASE + 0xEE)
#define  REG_TC_HDMITX_PM_77_H       (REG_TC_HDMITX_PM_BASE + 0xEF)
#define  REG_TC_HDMITX_PM_78_L       (REG_TC_HDMITX_PM_BASE + 0xF0)
#define  REG_TC_HDMITX_PM_78_H       (REG_TC_HDMITX_PM_BASE + 0xF1)
#define  REG_TC_HDMITX_PM_79_L       (REG_TC_HDMITX_PM_BASE + 0xF2)
#define  REG_TC_HDMITX_PM_79_H       (REG_TC_HDMITX_PM_BASE + 0xF3)
#define  REG_TC_HDMITX_PM_7A_L       (REG_TC_HDMITX_PM_BASE + 0xF4)
#define  REG_TC_HDMITX_PM_7A_H       (REG_TC_HDMITX_PM_BASE + 0xF5)
#define  REG_TC_HDMITX_PM_7B_L       (REG_TC_HDMITX_PM_BASE + 0xF6)
#define  REG_TC_HDMITX_PM_7B_H       (REG_TC_HDMITX_PM_BASE + 0xF7)
#define  REG_TC_HDMITX_PM_7C_L       (REG_TC_HDMITX_PM_BASE + 0xF8)
#define  REG_TC_HDMITX_PM_7C_H       (REG_TC_HDMITX_PM_BASE + 0xF9)
#define  REG_TC_HDMITX_PM_7D_L       (REG_TC_HDMITX_PM_BASE + 0xFA)
#define  REG_TC_HDMITX_PM_7D_H       (REG_TC_HDMITX_PM_BASE + 0xFB)
#define  REG_TC_HDMITX_PM_7E_L       (REG_TC_HDMITX_PM_BASE + 0xFC)
#define  REG_TC_HDMITX_PM_7E_H       (REG_TC_HDMITX_PM_BASE + 0xFD)
#define  REG_TC_HDMITX_PM_7F_L       (REG_TC_HDMITX_PM_BASE + 0xFE)
#define  REG_TC_HDMITX_PM_7F_H       (REG_TC_HDMITX_PM_BASE + 0xFF)

#define  REG_TC_DAC_PLL_15_L         (REG_TC_DAC_PLL_BASE + 0x2A)
#define  REG_TC_DAC_PLL_15_H         (REG_TC_DAC_PLL_BASE + 0x2B)
#define  REG_TC_DAC_PLL_16_L         (REG_TC_DAC_PLL_BASE + 0x2C)
#define  REG_TC_DAC_PLL_16_H         (REG_TC_DAC_PLL_BASE + 0x2D)
#define  REG_TC_DAC_PLL_17_L         (REG_TC_DAC_PLL_BASE + 0x2E)
#define  REG_TC_DAC_PLL_17_H         (REG_TC_DAC_PLL_BASE + 0x2F)
#define  REG_TC_DAC_PLL_31_L         (REG_TC_DAC_PLL_BASE + 0x62)
#define  REG_TC_DAC_PLL_31_H         (REG_TC_DAC_PLL_BASE + 0x63)
#define  REG_TC_DAC_PLL_32_L         (REG_TC_DAC_PLL_BASE + 0x64)
#define  REG_TC_DAC_PLL_32_H         (REG_TC_DAC_PLL_BASE + 0x65)

#ifdef __cplusplus
}
#endif

#undef _DRVADCTBL_H_
#endif
