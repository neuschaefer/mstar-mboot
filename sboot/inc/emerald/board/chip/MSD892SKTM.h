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
////////////////////////////////////////////////////////////////////////////////

// This file is generated by script, please do not edit it directly 
#ifndef _MCP_17_H_
#define _MCP_17_H_

#define PAD_NC 9999
#define PAD_GND 0

#define BALL_L6 PAD_HOTPLUGD
#define PAD_HOTPLUGD 26
#define GPIO_PAD_26 GPIO25
#ifndef BALL_L6_IS_GPIO
#define BALL_L6_IS_GPIO 0
#endif 
#ifndef PAD_HOTPLUGD_IS_GPIO
#define PAD_HOTPLUGD_IS_GPIO BALL_L6_IS_GPIO
#endif 

#define BALL_E5 PAD_GPIO_PM15
#define PAD_GPIO_PM15 22
#define GPIO_PAD_22 GPIO21
#ifndef BALL_E5_IS_GPIO
#define BALL_E5_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM15_IS_GPIO
#define PAD_GPIO_PM15_IS_GPIO BALL_E5_IS_GPIO
#endif 

#define BALL_W11 PAD_TGPIO0
#define PAD_TGPIO0 77
#define GPIO_PAD_77 GPIO76
#ifndef BALL_W11_IS_GPIO
#define BALL_W11_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO0_IS_GPIO
#define PAD_TGPIO0_IS_GPIO BALL_W11_IS_GPIO
#endif 

#define BALL_Y11 PAD_TGPIO1
#define PAD_TGPIO1 78
#define GPIO_PAD_78 GPIO77
#ifndef BALL_Y11_IS_GPIO
#define BALL_Y11_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO1_IS_GPIO
#define PAD_TGPIO1_IS_GPIO BALL_Y11_IS_GPIO
#endif 

#define BALL_Y13 PAD_TGPIO2
#define PAD_TGPIO2 79
#define GPIO_PAD_79 GPIO78
#ifndef BALL_Y13_IS_GPIO
#define BALL_Y13_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO2_IS_GPIO
#define PAD_TGPIO2_IS_GPIO BALL_Y13_IS_GPIO
#endif 

#define BALL_AA13 PAD_TGPIO3
#define PAD_TGPIO3 80
#define GPIO_PAD_80 GPIO79
#ifndef BALL_AA13_IS_GPIO
#define BALL_AA13_IS_GPIO 0
#endif 
#ifndef PAD_TGPIO3_IS_GPIO
#define PAD_TGPIO3_IS_GPIO BALL_AA13_IS_GPIO
#endif 

#define BALL_V6 PAD_DDCDC_DA
#define PAD_DDCDC_DA 32
#define GPIO_PAD_32 GPIO31
#ifndef BALL_V6_IS_GPIO
#define BALL_V6_IS_GPIO 0
#endif 
#ifndef PAD_DDCDC_DA_IS_GPIO
#define PAD_DDCDC_DA_IS_GPIO BALL_V6_IS_GPIO
#endif 

#define BALL_U6 PAD_DDCDC_CK
#define PAD_DDCDC_CK 31
#define GPIO_PAD_31 GPIO30
#ifndef BALL_U6_IS_GPIO
#define BALL_U6_IS_GPIO 0
#endif 
#ifndef PAD_DDCDC_CK_IS_GPIO
#define PAD_DDCDC_CK_IS_GPIO BALL_U6_IS_GPIO
#endif 

#define BALL_T6 PAD_HOTPLUGC
#define PAD_HOTPLUGC 25
#define GPIO_PAD_25 GPIO24
#ifndef BALL_T6_IS_GPIO
#define BALL_T6_IS_GPIO 0
#endif 
#ifndef PAD_HOTPLUGC_IS_GPIO
#define PAD_HOTPLUGC_IS_GPIO BALL_T6_IS_GPIO
#endif 

#define BALL_AA18 PAD_NAND_REZ
#define PAD_NAND_REZ 143
#define GPIO_PAD_143 GPIO142
#ifndef BALL_AA18_IS_GPIO
#define BALL_AA18_IS_GPIO 0
#endif 
#ifndef PAD_NAND_REZ_IS_GPIO
#define PAD_NAND_REZ_IS_GPIO BALL_AA18_IS_GPIO
#endif 

#define BALL_Y17 PAD_NAND_CLE
#define PAD_NAND_CLE 140
#define GPIO_PAD_140 GPIO139
#ifndef BALL_Y17_IS_GPIO
#define BALL_Y17_IS_GPIO 0
#endif 
#ifndef PAD_NAND_CLE_IS_GPIO
#define PAD_NAND_CLE_IS_GPIO BALL_Y17_IS_GPIO
#endif 

#define BALL_W16 PAD_NAND_ALE
#define PAD_NAND_ALE 145
#define GPIO_PAD_145 GPIO144
#ifndef BALL_W16_IS_GPIO
#define BALL_W16_IS_GPIO 0
#endif 
#ifndef PAD_NAND_ALE_IS_GPIO
#define PAD_NAND_ALE_IS_GPIO BALL_W16_IS_GPIO
#endif 

#define BALL_Y18 PAD_NAND_CEZ
#define PAD_NAND_CEZ 141
#define GPIO_PAD_141 GPIO140
#ifndef BALL_Y18_IS_GPIO
#define BALL_Y18_IS_GPIO 0
#endif 
#ifndef PAD_NAND_CEZ_IS_GPIO
#define PAD_NAND_CEZ_IS_GPIO BALL_Y18_IS_GPIO
#endif 

#define PAD_TS0_VLD 9999
#ifndef PAD_TS0_VLD_IS_GPIO
#define PAD_TS0_VLD_IS_GPIO 0
#endif 

#define BALL_W17 PAD_NAND_CEZ1
#define PAD_NAND_CEZ1 142
#define GPIO_PAD_142 GPIO141
#ifndef BALL_W17_IS_GPIO
#define BALL_W17_IS_GPIO 0
#endif 
#ifndef PAD_NAND_CEZ1_IS_GPIO
#define PAD_NAND_CEZ1_IS_GPIO BALL_W17_IS_GPIO
#endif 

#define PAD_TS0_CLK 9999
#ifndef PAD_TS0_CLK_IS_GPIO
#define PAD_TS0_CLK_IS_GPIO 0
#endif 

#define BALL_AA16 PAD_NAND_WPZ
#define PAD_NAND_WPZ 197
#define GPIO_PAD_197 GPIO196
#ifndef BALL_AA16_IS_GPIO
#define BALL_AA16_IS_GPIO 0
#endif 
#ifndef PAD_NAND_WPZ_IS_GPIO
#define PAD_NAND_WPZ_IS_GPIO BALL_AA16_IS_GPIO
#endif 

#define PAD_TS0_SYNC 9999
#ifndef PAD_TS0_SYNC_IS_GPIO
#define PAD_TS0_SYNC_IS_GPIO 0
#endif 

#define BALL_Y16 PAD_NAND_WEZ
#define PAD_NAND_WEZ 144
#define GPIO_PAD_144 GPIO143
#ifndef BALL_Y16_IS_GPIO
#define BALL_Y16_IS_GPIO 0
#endif 
#ifndef PAD_NAND_WEZ_IS_GPIO
#define PAD_NAND_WEZ_IS_GPIO BALL_Y16_IS_GPIO
#endif 

#define PAD_TS0_D3 9999
#ifndef PAD_TS0_D3_IS_GPIO
#define PAD_TS0_D3_IS_GPIO 0
#endif 

#define BALL_W18 PAD_NAND_RBZ
#define PAD_NAND_RBZ 146
#define GPIO_PAD_146 GPIO145
#ifndef BALL_W18_IS_GPIO
#define BALL_W18_IS_GPIO 0
#endif 
#ifndef PAD_NAND_RBZ_IS_GPIO
#define PAD_NAND_RBZ_IS_GPIO BALL_W18_IS_GPIO
#endif 

#define PAD_TS0_D4 9999
#ifndef PAD_TS0_D4_IS_GPIO
#define PAD_TS0_D4_IS_GPIO 0
#endif 

#define PAD_TS0_D1 9999
#ifndef PAD_TS0_D1_IS_GPIO
#define PAD_TS0_D1_IS_GPIO 0
#endif 

#define PAD_TS0_D0 9999
#ifndef PAD_TS0_D0_IS_GPIO
#define PAD_TS0_D0_IS_GPIO 0
#endif 

#define PAD_TS0_D2 9999
#ifndef PAD_TS0_D2_IS_GPIO
#define PAD_TS0_D2_IS_GPIO 0
#endif 

#define PAD_TS0_D6 9999
#ifndef PAD_TS0_D6_IS_GPIO
#define PAD_TS0_D6_IS_GPIO 0
#endif 

#define PAD_TS0_D5 9999
#ifndef PAD_TS0_D5_IS_GPIO
#define PAD_TS0_D5_IS_GPIO 0
#endif 

#define PAD_TS0_D7 9999
#ifndef PAD_TS0_D7_IS_GPIO
#define PAD_TS0_D7_IS_GPIO 0
#endif 

#define BALL_U17 PAD_TS1_D5
#define PAD_TS1_D5 97
#define GPIO_PAD_97 GPIO96
#ifndef BALL_U17_IS_GPIO
#define BALL_U17_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D5_IS_GPIO
#define PAD_TS1_D5_IS_GPIO BALL_U17_IS_GPIO
#endif 

#define BALL_T17 PAD_TS1_D7
#define PAD_TS1_D7 99
#define GPIO_PAD_99 GPIO98
#ifndef BALL_T17_IS_GPIO
#define BALL_T17_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D7_IS_GPIO
#define PAD_TS1_D7_IS_GPIO BALL_T17_IS_GPIO
#endif 

#define BALL_V17 PAD_TS1_D4
#define PAD_TS1_D4 96
#define GPIO_PAD_96 GPIO95
#ifndef BALL_V17_IS_GPIO
#define BALL_V17_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D4_IS_GPIO
#define PAD_TS1_D4_IS_GPIO BALL_V17_IS_GPIO
#endif 

#define BALL_U15 PAD_TS1_D6
#define PAD_TS1_D6 98
#define GPIO_PAD_98 GPIO97
#ifndef BALL_U15_IS_GPIO
#define BALL_U15_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D6_IS_GPIO
#define PAD_TS1_D6_IS_GPIO BALL_U15_IS_GPIO
#endif 

#define BALL_V16 PAD_TS1_D3
#define PAD_TS1_D3 95
#define GPIO_PAD_95 GPIO94
#ifndef BALL_V16_IS_GPIO
#define BALL_V16_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D3_IS_GPIO
#define PAD_TS1_D3_IS_GPIO BALL_V16_IS_GPIO
#endif 

#define BALL_T16 PAD_TS1_CLK
#define PAD_TS1_CLK 102
#define GPIO_PAD_102 GPIO101
#ifndef BALL_T16_IS_GPIO
#define BALL_T16_IS_GPIO 0
#endif 
#ifndef PAD_TS1_CLK_IS_GPIO
#define PAD_TS1_CLK_IS_GPIO BALL_T16_IS_GPIO
#endif 

#define BALL_V18 PAD_TS1_D2
#define PAD_TS1_D2 94
#define GPIO_PAD_94 GPIO93
#ifndef BALL_V18_IS_GPIO
#define BALL_V18_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D2_IS_GPIO
#define PAD_TS1_D2_IS_GPIO BALL_V18_IS_GPIO
#endif 

#define BALL_U16 PAD_TS1_SYNC
#define PAD_TS1_SYNC 101
#define GPIO_PAD_101 GPIO100
#ifndef BALL_U16_IS_GPIO
#define BALL_U16_IS_GPIO 0
#endif 
#ifndef PAD_TS1_SYNC_IS_GPIO
#define PAD_TS1_SYNC_IS_GPIO BALL_U16_IS_GPIO
#endif 

#define BALL_U18 PAD_TS1_D1
#define PAD_TS1_D1 93
#define GPIO_PAD_93 GPIO92
#ifndef BALL_U18_IS_GPIO
#define BALL_U18_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D1_IS_GPIO
#define PAD_TS1_D1_IS_GPIO BALL_U18_IS_GPIO
#endif 

#define BALL_R18 PAD_TS1_VLD
#define PAD_TS1_VLD 100
#define GPIO_PAD_100 GPIO99
#ifndef BALL_R18_IS_GPIO
#define BALL_R18_IS_GPIO 0
#endif 
#ifndef PAD_TS1_VLD_IS_GPIO
#define PAD_TS1_VLD_IS_GPIO BALL_R18_IS_GPIO
#endif 

#define BALL_T18 PAD_TS1_D0
#define PAD_TS1_D0 92
#define GPIO_PAD_92 GPIO91
#ifndef BALL_T18_IS_GPIO
#define BALL_T18_IS_GPIO 0
#endif 
#ifndef PAD_TS1_D0_IS_GPIO
#define PAD_TS1_D0_IS_GPIO BALL_T18_IS_GPIO
#endif 

#define BALL_P18 PAD_PCM_D4
#define PAD_PCM_D4 123
#define GPIO_PAD_123 GPIO122
#ifndef BALL_P18_IS_GPIO
#define BALL_P18_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D4_IS_GPIO
#define PAD_PCM_D4_IS_GPIO BALL_P18_IS_GPIO
#endif 

#define PAD_PCM_A10 9999
#ifndef PAD_PCM_A10_IS_GPIO
#define PAD_PCM_A10_IS_GPIO 0
#endif 

#define BALL_R16 PAD_PCM_D6
#define PAD_PCM_D6 121
#define GPIO_PAD_121 GPIO120
#ifndef BALL_R16_IS_GPIO
#define BALL_R16_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D6_IS_GPIO
#define PAD_PCM_D6_IS_GPIO BALL_R16_IS_GPIO
#endif 

#define PAD_PCM_OE_N 9999
#ifndef PAD_PCM_OE_N_IS_GPIO
#define PAD_PCM_OE_N_IS_GPIO 0
#endif 

#define BALL_U14 PAD_PCM_A3
#define PAD_PCM_A3 125
#define GPIO_PAD_125 GPIO124
#ifndef BALL_U14_IS_GPIO
#define BALL_U14_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A3_IS_GPIO
#define PAD_PCM_A3_IS_GPIO BALL_U14_IS_GPIO
#endif 

#define BALL_P16 PAD_PCM_D3
#define PAD_PCM_D3 124
#define GPIO_PAD_124 GPIO123
#ifndef BALL_P16_IS_GPIO
#define BALL_P16_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D3_IS_GPIO
#define PAD_PCM_D3_IS_GPIO BALL_P16_IS_GPIO
#endif 

#define BALL_V15 PAD_PCM_A2
#define PAD_PCM_A2 126
#define GPIO_PAD_126 GPIO125
#ifndef BALL_V15_IS_GPIO
#define BALL_V15_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A2_IS_GPIO
#define PAD_PCM_A2_IS_GPIO BALL_V15_IS_GPIO
#endif 

#define BALL_P17 PAD_PCM_D5
#define PAD_PCM_D5 122
#define GPIO_PAD_122 GPIO121
#ifndef BALL_P17_IS_GPIO
#define BALL_P17_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D5_IS_GPIO
#define PAD_PCM_D5_IS_GPIO BALL_P17_IS_GPIO
#endif 

#define PAD_PCM_REG_N 9999
#ifndef PAD_PCM_REG_N_IS_GPIO
#define PAD_PCM_REG_N_IS_GPIO 0
#endif 

#define BALL_R17 PAD_PCM_D7
#define PAD_PCM_D7 120
#define GPIO_PAD_120 GPIO119
#ifndef BALL_R17_IS_GPIO
#define BALL_R17_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D7_IS_GPIO
#define PAD_PCM_D7_IS_GPIO BALL_R17_IS_GPIO
#endif 

#define BALL_W15 PAD_PCM_A1
#define PAD_PCM_A1 128
#define GPIO_PAD_128 GPIO127
#ifndef BALL_W15_IS_GPIO
#define BALL_W15_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A1_IS_GPIO
#define PAD_PCM_A1_IS_GPIO BALL_W15_IS_GPIO
#endif 

#define PAD_PCM_CE_N 9999
#ifndef PAD_PCM_CE_N_IS_GPIO
#define PAD_PCM_CE_N_IS_GPIO 0
#endif 

#define BALL_V14 PAD_PCM_A0
#define PAD_PCM_A0 129
#define GPIO_PAD_129 GPIO128
#ifndef BALL_V14_IS_GPIO
#define BALL_V14_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A0_IS_GPIO
#define PAD_PCM_A0_IS_GPIO BALL_V14_IS_GPIO
#endif 

#define PAD_PCM_A11 9999
#ifndef PAD_PCM_A11_IS_GPIO
#define PAD_PCM_A11_IS_GPIO 0
#endif 

#define BALL_N16 PAD_PCM_D0
#define PAD_PCM_D0 130
#define GPIO_PAD_130 GPIO129
#ifndef BALL_N16_IS_GPIO
#define BALL_N16_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D0_IS_GPIO
#define PAD_PCM_D0_IS_GPIO BALL_N16_IS_GPIO
#endif 

#define PAD_PCM_IORD_N 9999
#ifndef PAD_PCM_IORD_N_IS_GPIO
#define PAD_PCM_IORD_N_IS_GPIO 0
#endif 

#define BALL_N18 PAD_PCM_D1
#define PAD_PCM_D1 131
#define GPIO_PAD_131 GPIO130
#ifndef BALL_N18_IS_GPIO
#define BALL_N18_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D1_IS_GPIO
#define PAD_PCM_D1_IS_GPIO BALL_N18_IS_GPIO
#endif 

#define PAD_PCM_A9 9999
#ifndef PAD_PCM_A9_IS_GPIO
#define PAD_PCM_A9_IS_GPIO 0
#endif 

#define BALL_N17 PAD_PCM_D2
#define PAD_PCM_D2 132
#define GPIO_PAD_132 GPIO131
#ifndef BALL_N17_IS_GPIO
#define BALL_N17_IS_GPIO 0
#endif 
#ifndef PAD_PCM_D2_IS_GPIO
#define PAD_PCM_D2_IS_GPIO BALL_N17_IS_GPIO
#endif 

#define PAD_PCM_IOWR_N 9999
#ifndef PAD_PCM_IOWR_N_IS_GPIO
#define PAD_PCM_IOWR_N_IS_GPIO 0
#endif 

#define PAD_PCM_A8 9999
#ifndef PAD_PCM_A8_IS_GPIO
#define PAD_PCM_A8_IS_GPIO 0
#endif 

#define PAD_PCM_WE_N 9999
#ifndef PAD_PCM_WE_N_IS_GPIO
#define PAD_PCM_WE_N_IS_GPIO 0
#endif 

#define PAD_PCM_A13 9999
#ifndef PAD_PCM_A13_IS_GPIO
#define PAD_PCM_A13_IS_GPIO 0
#endif 

#define PAD_PCM_RESET 9999
#ifndef PAD_PCM_RESET_IS_GPIO
#define PAD_PCM_RESET_IS_GPIO 0
#endif 

#define PAD_PCM_A14 9999
#ifndef PAD_PCM_A14_IS_GPIO
#define PAD_PCM_A14_IS_GPIO 0
#endif 

#define BALL_T15 PAD_PCM_A5
#define PAD_PCM_A5 105
#define GPIO_PAD_105 GPIO104
#ifndef BALL_T15_IS_GPIO
#define BALL_T15_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A5_IS_GPIO
#define PAD_PCM_A5_IS_GPIO BALL_T15_IS_GPIO
#endif 

#define PAD_PCM_IRQA_N 9999
#ifndef PAD_PCM_IRQA_N_IS_GPIO
#define PAD_PCM_IRQA_N_IS_GPIO 0
#endif 

#define PAD_PCM_WAIT_N 9999
#ifndef PAD_PCM_WAIT_N_IS_GPIO
#define PAD_PCM_WAIT_N_IS_GPIO 0
#endif 

#define PAD_PCM_A12 9999
#ifndef PAD_PCM_A12_IS_GPIO
#define PAD_PCM_A12_IS_GPIO 0
#endif 

#define BALL_T14 PAD_PCM_A4
#define PAD_PCM_A4 103
#define GPIO_PAD_103 GPIO102
#ifndef BALL_T14_IS_GPIO
#define BALL_T14_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A4_IS_GPIO
#define PAD_PCM_A4_IS_GPIO BALL_T14_IS_GPIO
#endif 

#define BALL_W14 PAD_PCM_A7
#define PAD_PCM_A7 107
#define GPIO_PAD_107 GPIO106
#ifndef BALL_W14_IS_GPIO
#define BALL_W14_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A7_IS_GPIO
#define PAD_PCM_A7_IS_GPIO BALL_W14_IS_GPIO
#endif 

#define BALL_K19 PAD_PCM2_IRQA_N
#define PAD_PCM2_IRQA_N 136
#define GPIO_PAD_136 GPIO135
#ifndef BALL_K19_IS_GPIO
#define BALL_K19_IS_GPIO 0
#endif 
#ifndef PAD_PCM2_IRQA_N_IS_GPIO
#define PAD_PCM2_IRQA_N_IS_GPIO BALL_K19_IS_GPIO
#endif 

#define BALL_Y14 PAD_PCM_A6
#define PAD_PCM_A6 106
#define GPIO_PAD_106 GPIO105
#ifndef BALL_Y14_IS_GPIO
#define BALL_Y14_IS_GPIO 0
#endif 
#ifndef PAD_PCM_A6_IS_GPIO
#define PAD_PCM_A6_IS_GPIO BALL_Y14_IS_GPIO
#endif 

#define BALL_J20 PAD_PCM2_WAIT_N
#define PAD_PCM2_WAIT_N 137
#define GPIO_PAD_137 GPIO136
#ifndef BALL_J20_IS_GPIO
#define BALL_J20_IS_GPIO 0
#endif 
#ifndef PAD_PCM2_WAIT_N_IS_GPIO
#define PAD_PCM2_WAIT_N_IS_GPIO BALL_J20_IS_GPIO
#endif 

#define PAD_PCM_CD_N 9999
#ifndef PAD_PCM_CD_N_IS_GPIO
#define PAD_PCM_CD_N_IS_GPIO 0
#endif 

#define BALL_J21 PAD_PCM2_RESET
#define PAD_PCM2_RESET 138
#define GPIO_PAD_138 GPIO137
#ifndef BALL_J21_IS_GPIO
#define BALL_J21_IS_GPIO 0
#endif 
#ifndef PAD_PCM2_RESET_IS_GPIO
#define PAD_PCM2_RESET_IS_GPIO BALL_J21_IS_GPIO
#endif 

#define BALL_K21 PAD_PCM2_CE_N
#define PAD_PCM2_CE_N 135
#define GPIO_PAD_135 GPIO134
#ifndef BALL_K21_IS_GPIO
#define BALL_K21_IS_GPIO 0
#endif 
#ifndef PAD_PCM2_CE_N_IS_GPIO
#define PAD_PCM2_CE_N_IS_GPIO BALL_K21_IS_GPIO
#endif 

#define BALL_J19 PAD_PCM2_CD_N
#define PAD_PCM2_CD_N 139
#define GPIO_PAD_139 GPIO138
#ifndef BALL_J19_IS_GPIO
#define BALL_J19_IS_GPIO 0
#endif 
#ifndef PAD_PCM2_CD_N_IS_GPIO
#define PAD_PCM2_CD_N_IS_GPIO BALL_J19_IS_GPIO
#endif 

#define BALL_Y19 PAD_B_ODD0
#define PAD_B_ODD0 160
#define GPIO_PAD_160 GPIO159
#ifndef BALL_Y19_IS_GPIO
#define BALL_Y19_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD0_IS_GPIO
#define PAD_B_ODD0_IS_GPIO BALL_Y19_IS_GPIO
#endif 

#define BALL_AA19 PAD_B_ODD1
#define PAD_B_ODD1 161
#define GPIO_PAD_161 GPIO160
#ifndef BALL_AA19_IS_GPIO
#define BALL_AA19_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD1_IS_GPIO
#define PAD_B_ODD1_IS_GPIO BALL_AA19_IS_GPIO
#endif 

#define BALL_W20 PAD_B_ODD2
#define PAD_B_ODD2 162
#define GPIO_PAD_162 GPIO161
#ifndef BALL_W20_IS_GPIO
#define BALL_W20_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD2_IS_GPIO
#define PAD_B_ODD2_IS_GPIO BALL_W20_IS_GPIO
#endif 

#define BALL_Y20 PAD_B_ODD3
#define PAD_B_ODD3 163
#define GPIO_PAD_163 GPIO162
#ifndef BALL_Y20_IS_GPIO
#define BALL_Y20_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD3_IS_GPIO
#define PAD_B_ODD3_IS_GPIO BALL_Y20_IS_GPIO
#endif 

#define BALL_W19 PAD_B_ODD4
#define PAD_B_ODD4 164
#define GPIO_PAD_164 GPIO163
#ifndef BALL_W19_IS_GPIO
#define BALL_W19_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD4_IS_GPIO
#define PAD_B_ODD4_IS_GPIO BALL_W19_IS_GPIO
#endif 

#define BALL_W21 PAD_B_ODD5
#define PAD_B_ODD5 165
#define GPIO_PAD_165 GPIO164
#ifndef BALL_W21_IS_GPIO
#define BALL_W21_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD5_IS_GPIO
#define PAD_B_ODD5_IS_GPIO BALL_W21_IS_GPIO
#endif 

#define BALL_V20 PAD_B_ODD6
#define PAD_B_ODD6 166
#define GPIO_PAD_166 GPIO165
#ifndef BALL_V20_IS_GPIO
#define BALL_V20_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD6_IS_GPIO
#define PAD_B_ODD6_IS_GPIO BALL_V20_IS_GPIO
#endif 

#define BALL_V21 PAD_B_ODD7
#define PAD_B_ODD7 167
#define GPIO_PAD_167 GPIO166
#ifndef BALL_V21_IS_GPIO
#define BALL_V21_IS_GPIO 0
#endif 
#ifndef PAD_B_ODD7_IS_GPIO
#define PAD_B_ODD7_IS_GPIO BALL_V21_IS_GPIO
#endif 

#define BALL_U20 PAD_G_ODD0
#define PAD_G_ODD0 168
#define GPIO_PAD_168 GPIO167
#ifndef BALL_U20_IS_GPIO
#define BALL_U20_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD0_IS_GPIO
#define PAD_G_ODD0_IS_GPIO BALL_U20_IS_GPIO
#endif 

#define BALL_V19 PAD_G_ODD1
#define PAD_G_ODD1 169
#define GPIO_PAD_169 GPIO168
#ifndef BALL_V19_IS_GPIO
#define BALL_V19_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD1_IS_GPIO
#define PAD_G_ODD1_IS_GPIO BALL_V19_IS_GPIO
#endif 

#define BALL_T20 PAD_G_ODD2
#define PAD_G_ODD2 170
#define GPIO_PAD_170 GPIO169
#ifndef BALL_T20_IS_GPIO
#define BALL_T20_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD2_IS_GPIO
#define PAD_G_ODD2_IS_GPIO BALL_T20_IS_GPIO
#endif 

#define BALL_U19 PAD_G_ODD3
#define PAD_G_ODD3 171
#define GPIO_PAD_171 GPIO170
#ifndef BALL_U19_IS_GPIO
#define BALL_U19_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD3_IS_GPIO
#define PAD_G_ODD3_IS_GPIO BALL_U19_IS_GPIO
#endif 

#define BALL_T19 PAD_G_ODD4
#define PAD_G_ODD4 172
#define GPIO_PAD_172 GPIO171
#ifndef BALL_T19_IS_GPIO
#define BALL_T19_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD4_IS_GPIO
#define PAD_G_ODD4_IS_GPIO BALL_T19_IS_GPIO
#endif 

#define BALL_T21 PAD_G_ODD5
#define PAD_G_ODD5 173
#define GPIO_PAD_173 GPIO172
#ifndef BALL_T21_IS_GPIO
#define BALL_T21_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD5_IS_GPIO
#define PAD_G_ODD5_IS_GPIO BALL_T21_IS_GPIO
#endif 

#define BALL_R20 PAD_G_ODD6
#define PAD_G_ODD6 174
#define GPIO_PAD_174 GPIO173
#ifndef BALL_R20_IS_GPIO
#define BALL_R20_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD6_IS_GPIO
#define PAD_G_ODD6_IS_GPIO BALL_R20_IS_GPIO
#endif 

#define BALL_R21 PAD_G_ODD7
#define PAD_G_ODD7 175
#define GPIO_PAD_175 GPIO174
#ifndef BALL_R21_IS_GPIO
#define BALL_R21_IS_GPIO 0
#endif 
#ifndef PAD_G_ODD7_IS_GPIO
#define PAD_G_ODD7_IS_GPIO BALL_R21_IS_GPIO
#endif 

#define BALL_P20 PAD_R_ODD0
#define PAD_R_ODD0 176
#define GPIO_PAD_176 GPIO175
#ifndef BALL_P20_IS_GPIO
#define BALL_P20_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD0_IS_GPIO
#define PAD_R_ODD0_IS_GPIO BALL_P20_IS_GPIO
#endif 

#define BALL_R19 PAD_R_ODD1
#define PAD_R_ODD1 177
#define GPIO_PAD_177 GPIO176
#ifndef BALL_R19_IS_GPIO
#define BALL_R19_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD1_IS_GPIO
#define PAD_R_ODD1_IS_GPIO BALL_R19_IS_GPIO
#endif 

#define BALL_N20 PAD_R_ODD2
#define PAD_R_ODD2 178
#define GPIO_PAD_178 GPIO177
#ifndef BALL_N20_IS_GPIO
#define BALL_N20_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD2_IS_GPIO
#define PAD_R_ODD2_IS_GPIO BALL_N20_IS_GPIO
#endif 

#define BALL_P19 PAD_R_ODD3
#define PAD_R_ODD3 179
#define GPIO_PAD_179 GPIO178
#ifndef BALL_P19_IS_GPIO
#define BALL_P19_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD3_IS_GPIO
#define PAD_R_ODD3_IS_GPIO BALL_P19_IS_GPIO
#endif 

#define BALL_N19 PAD_R_ODD4
#define PAD_R_ODD4 180
#define GPIO_PAD_180 GPIO179
#ifndef BALL_N19_IS_GPIO
#define BALL_N19_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD4_IS_GPIO
#define PAD_R_ODD4_IS_GPIO BALL_N19_IS_GPIO
#endif 

#define BALL_N21 PAD_R_ODD5
#define PAD_R_ODD5 181
#define GPIO_PAD_181 GPIO180
#ifndef BALL_N21_IS_GPIO
#define BALL_N21_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD5_IS_GPIO
#define PAD_R_ODD5_IS_GPIO BALL_N21_IS_GPIO
#endif 

#define BALL_M20 PAD_R_ODD6
#define PAD_R_ODD6 182
#define GPIO_PAD_182 GPIO181
#ifndef BALL_M20_IS_GPIO
#define BALL_M20_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD6_IS_GPIO
#define PAD_R_ODD6_IS_GPIO BALL_M20_IS_GPIO
#endif 

#define BALL_M21 PAD_R_ODD7
#define PAD_R_ODD7 183
#define GPIO_PAD_183 GPIO182
#ifndef BALL_M21_IS_GPIO
#define BALL_M21_IS_GPIO 0
#endif 
#ifndef PAD_R_ODD7_IS_GPIO
#define PAD_R_ODD7_IS_GPIO BALL_M21_IS_GPIO
#endif 

#define BALL_M19 PAD_LCK
#define PAD_LCK 192
#define GPIO_PAD_192 GPIO191
#ifndef BALL_M19_IS_GPIO
#define BALL_M19_IS_GPIO 0
#endif 
#ifndef PAD_LCK_IS_GPIO
#define PAD_LCK_IS_GPIO BALL_M19_IS_GPIO
#endif 

#define BALL_L20 PAD_LDE
#define PAD_LDE 193
#define GPIO_PAD_193 GPIO192
#ifndef BALL_L20_IS_GPIO
#define BALL_L20_IS_GPIO 0
#endif 
#ifndef PAD_LDE_IS_GPIO
#define PAD_LDE_IS_GPIO BALL_L20_IS_GPIO
#endif 

#define BALL_L19 PAD_LHSYNC
#define PAD_LHSYNC 194
#define GPIO_PAD_194 GPIO193
#ifndef BALL_L19_IS_GPIO
#define BALL_L19_IS_GPIO 0
#endif 
#ifndef PAD_LHSYNC_IS_GPIO
#define PAD_LHSYNC_IS_GPIO BALL_L19_IS_GPIO
#endif 

#define BALL_K20 PAD_LVSYNC
#define PAD_LVSYNC 195
#define GPIO_PAD_195 GPIO194
#ifndef BALL_K20_IS_GPIO
#define BALL_K20_IS_GPIO 0
#endif 
#ifndef PAD_LVSYNC_IS_GPIO
#define PAD_LVSYNC_IS_GPIO BALL_K20_IS_GPIO
#endif 

#define PAD_TCON7 9999
#ifndef PAD_TCON7_IS_GPIO
#define PAD_TCON7_IS_GPIO 0
#endif 

#define PAD_TCON6 9999
#ifndef PAD_TCON6_IS_GPIO
#define PAD_TCON6_IS_GPIO 0
#endif 

#define PAD_TCON5 9999
#ifndef PAD_TCON5_IS_GPIO
#define PAD_TCON5_IS_GPIO 0
#endif 

#define PAD_TCON4 9999
#ifndef PAD_TCON4_IS_GPIO
#define PAD_TCON4_IS_GPIO 0
#endif 

#define PAD_TCON3 9999
#ifndef PAD_TCON3_IS_GPIO
#define PAD_TCON3_IS_GPIO 0
#endif 

#define PAD_TCON2 9999
#ifndef PAD_TCON2_IS_GPIO
#define PAD_TCON2_IS_GPIO 0
#endif 

#define PAD_TCON1 9999
#ifndef PAD_TCON1_IS_GPIO
#define PAD_TCON1_IS_GPIO 0
#endif 

#define PAD_TCON0 9999
#ifndef PAD_TCON0_IS_GPIO
#define PAD_TCON0_IS_GPIO 0
#endif 

#define PAD_mini_LVDS0 9999
#ifndef PAD_mini_LVDS0_IS_GPIO
#define PAD_mini_LVDS0_IS_GPIO 0
#endif 

#define PAD_mini_LVDS1 9999
#ifndef PAD_mini_LVDS1_IS_GPIO
#define PAD_mini_LVDS1_IS_GPIO 0
#endif 

#define PAD_mini_LVDS2 9999
#ifndef PAD_mini_LVDS2_IS_GPIO
#define PAD_mini_LVDS2_IS_GPIO 0
#endif 

#define PAD_mini_LVDS3 9999
#ifndef PAD_mini_LVDS3_IS_GPIO
#define PAD_mini_LVDS3_IS_GPIO 0
#endif 

#define PAD_mini_LVDS4 9999
#ifndef PAD_mini_LVDS4_IS_GPIO
#define PAD_mini_LVDS4_IS_GPIO 0
#endif 

#define PAD_mini_LVDS5 9999
#ifndef PAD_mini_LVDS5_IS_GPIO
#define PAD_mini_LVDS5_IS_GPIO 0
#endif 

#define PAD_mini_LVDS6 9999
#ifndef PAD_mini_LVDS6_IS_GPIO
#define PAD_mini_LVDS6_IS_GPIO 0
#endif 

#define PAD_mini_LVDS7 9999
#ifndef PAD_mini_LVDS7_IS_GPIO
#define PAD_mini_LVDS7_IS_GPIO 0
#endif 

#define PAD_VSYNC_LIKE 9999
#ifndef PAD_VSYNC_LIKE_IS_GPIO
#define PAD_VSYNC_LIKE_IS_GPIO 0
#endif 

#define PAD_SPI2_DI 9999
#ifndef PAD_SPI2_DI_IS_GPIO
#define PAD_SPI2_DI_IS_GPIO 0
#endif 

#define PAD_SPI2_CK 9999
#ifndef PAD_SPI2_CK_IS_GPIO
#define PAD_SPI2_CK_IS_GPIO 0
#endif 

#define PAD_SPI1_DI 9999
#ifndef PAD_SPI1_DI_IS_GPIO
#define PAD_SPI1_DI_IS_GPIO 0
#endif 

#define PAD_SPI1_CK 9999
#ifndef PAD_SPI1_CK_IS_GPIO
#define PAD_SPI1_CK_IS_GPIO 0
#endif 

#define BALL_H20 PAD_PWM0
#define PAD_PWM0 70
#define GPIO_PAD_70 GPIO69
#ifndef BALL_H20_IS_GPIO
#define BALL_H20_IS_GPIO 0
#endif 
#ifndef PAD_PWM0_IS_GPIO
#define PAD_PWM0_IS_GPIO BALL_H20_IS_GPIO
#endif 

#define BALL_H19 PAD_PWM1
#define PAD_PWM1 71
#define GPIO_PAD_71 GPIO70
#ifndef BALL_H19_IS_GPIO
#define BALL_H19_IS_GPIO 0
#endif 
#ifndef PAD_PWM1_IS_GPIO
#define PAD_PWM1_IS_GPIO BALL_H19_IS_GPIO
#endif 

#define BALL_G20 PAD_PWM2
#define PAD_PWM2 72
#define GPIO_PAD_72 GPIO71
#ifndef BALL_G20_IS_GPIO
#define BALL_G20_IS_GPIO 0
#endif 
#ifndef PAD_PWM2_IS_GPIO
#define PAD_PWM2_IS_GPIO BALL_G20_IS_GPIO
#endif 

#define BALL_G21 PAD_PWM3
#define PAD_PWM3 73
#define GPIO_PAD_73 GPIO72
#ifndef BALL_G21_IS_GPIO
#define BALL_G21_IS_GPIO 0
#endif 
#ifndef PAD_PWM3_IS_GPIO
#define PAD_PWM3_IS_GPIO BALL_G21_IS_GPIO
#endif 

#define PAD_PWM4 9999
#ifndef PAD_PWM4_IS_GPIO
#define PAD_PWM4_IS_GPIO 0
#endif 

#define BALL_F21 PAD_DDCR_CK
#define PAD_DDCR_CK 76
#define GPIO_PAD_76 GPIO75
#ifndef BALL_F21_IS_GPIO
#define BALL_F21_IS_GPIO 0
#endif 
#ifndef PAD_DDCR_CK_IS_GPIO
#define PAD_DDCR_CK_IS_GPIO BALL_F21_IS_GPIO
#endif 

#define BALL_G19 PAD_DDCR_DA
#define PAD_DDCR_DA 75
#define GPIO_PAD_75 GPIO74
#ifndef BALL_G19_IS_GPIO
#define BALL_G19_IS_GPIO 0
#endif 
#ifndef PAD_DDCR_DA_IS_GPIO
#define PAD_DDCR_DA_IS_GPIO BALL_G19_IS_GPIO
#endif 

#define BALL_F20 PAD_UART_RX2
#define PAD_UART_RX2 68
#define GPIO_PAD_68 GPIO67
#ifndef BALL_F20_IS_GPIO
#define BALL_F20_IS_GPIO 0
#endif 
#ifndef PAD_UART_RX2_IS_GPIO
#define PAD_UART_RX2_IS_GPIO BALL_F20_IS_GPIO
#endif 

#define BALL_F19 PAD_UART_TX2
#define PAD_UART_TX2 69
#define GPIO_PAD_69 GPIO68
#ifndef BALL_F19_IS_GPIO
#define BALL_F19_IS_GPIO 0
#endif 
#ifndef PAD_UART_TX2_IS_GPIO
#define PAD_UART_TX2_IS_GPIO BALL_F19_IS_GPIO
#endif 

#define BALL_A16 PAD_I2S_IN_WS
#define PAD_I2S_IN_WS 148
#define GPIO_PAD_148 GPIO147
#ifndef BALL_A16_IS_GPIO
#define BALL_A16_IS_GPIO 0
#endif 
#ifndef PAD_I2S_IN_WS_IS_GPIO
#define PAD_I2S_IN_WS_IS_GPIO BALL_A16_IS_GPIO
#endif 

#define BALL_C17 PAD_I2S_IN_BCK
#define PAD_I2S_IN_BCK 149
#define GPIO_PAD_149 GPIO148
#ifndef BALL_C17_IS_GPIO
#define BALL_C17_IS_GPIO 0
#endif 
#ifndef PAD_I2S_IN_BCK_IS_GPIO
#define PAD_I2S_IN_BCK_IS_GPIO BALL_C17_IS_GPIO
#endif 

#define BALL_B16 PAD_I2S_IN_SD
#define PAD_I2S_IN_SD 150
#define GPIO_PAD_150 GPIO149
#ifndef BALL_B16_IS_GPIO
#define BALL_B16_IS_GPIO 0
#endif 
#ifndef PAD_I2S_IN_SD_IS_GPIO
#define PAD_I2S_IN_SD_IS_GPIO BALL_B16_IS_GPIO
#endif 

#define BALL_C14 PAD_I2S_OUT_MCK
#define PAD_I2S_OUT_MCK 153
#define GPIO_PAD_153 GPIO152
#ifndef BALL_C14_IS_GPIO
#define BALL_C14_IS_GPIO 0
#endif 
#ifndef PAD_I2S_OUT_MCK_IS_GPIO
#define PAD_I2S_OUT_MCK_IS_GPIO BALL_C14_IS_GPIO
#endif 

#define BALL_C16 PAD_I2S_OUT_WS
#define PAD_I2S_OUT_WS 154
#define GPIO_PAD_154 GPIO153
#ifndef BALL_C16_IS_GPIO
#define BALL_C16_IS_GPIO 0
#endif 
#ifndef PAD_I2S_OUT_WS_IS_GPIO
#define PAD_I2S_OUT_WS_IS_GPIO BALL_C16_IS_GPIO
#endif 

#define PAD_I2S_OUT_SD1 9999
#ifndef PAD_I2S_OUT_SD1_IS_GPIO
#define PAD_I2S_OUT_SD1_IS_GPIO 0
#endif 

#define BALL_B14 PAD_I2S_OUT_BCK
#define PAD_I2S_OUT_BCK 155
#define GPIO_PAD_155 GPIO154
#ifndef BALL_B14_IS_GPIO
#define BALL_B14_IS_GPIO 0
#endif 
#ifndef PAD_I2S_OUT_BCK_IS_GPIO
#define PAD_I2S_OUT_BCK_IS_GPIO BALL_B14_IS_GPIO
#endif 

#define BALL_F12 PAD_GPIO9
#define PAD_GPIO9 49
#define GPIO_PAD_49 GPIO48
#ifndef BALL_F12_IS_GPIO
#define BALL_F12_IS_GPIO 0
#endif 
#ifndef PAD_GPIO9_IS_GPIO
#define PAD_GPIO9_IS_GPIO BALL_F12_IS_GPIO
#endif 

#define BALL_C15 PAD_I2S_OUT_SD
#define PAD_I2S_OUT_SD 156
#define GPIO_PAD_156 GPIO155
#ifndef BALL_C15_IS_GPIO
#define BALL_C15_IS_GPIO 0
#endif 
#ifndef PAD_I2S_OUT_SD_IS_GPIO
#define PAD_I2S_OUT_SD_IS_GPIO BALL_C15_IS_GPIO
#endif 

#define BALL_F11 PAD_GPIO10
#define PAD_GPIO10 50
#define GPIO_PAD_50 GPIO49
#ifndef BALL_F11_IS_GPIO
#define BALL_F11_IS_GPIO 0
#endif 
#ifndef PAD_GPIO10_IS_GPIO
#define PAD_GPIO10_IS_GPIO BALL_F11_IS_GPIO
#endif 

#define PAD_I2S_OUT_SD2 9999
#ifndef PAD_I2S_OUT_SD2_IS_GPIO
#define PAD_I2S_OUT_SD2_IS_GPIO 0
#endif 

#define BALL_B17 PAD_GPIO11
#define PAD_GPIO11 51
#define GPIO_PAD_51 GPIO50
#ifndef BALL_B17_IS_GPIO
#define BALL_B17_IS_GPIO 0
#endif 
#ifndef PAD_GPIO11_IS_GPIO
#define PAD_GPIO11_IS_GPIO BALL_B17_IS_GPIO
#endif 

#define PAD_I2S_OUT_SD3 9999
#ifndef PAD_I2S_OUT_SD3_IS_GPIO
#define PAD_I2S_OUT_SD3_IS_GPIO 0
#endif 

#define BALL_A18 PAD_GPIO12
#define PAD_GPIO12 52
#define GPIO_PAD_52 GPIO51
#ifndef BALL_A18_IS_GPIO
#define BALL_A18_IS_GPIO 0
#endif 
#ifndef PAD_GPIO12_IS_GPIO
#define PAD_GPIO12_IS_GPIO BALL_A18_IS_GPIO
#endif 

#define BALL_A13 PAD_SPDIF_IN
#define PAD_SPDIF_IN 151
#define GPIO_PAD_151 GPIO150
#ifndef BALL_A13_IS_GPIO
#define BALL_A13_IS_GPIO 0
#endif 
#ifndef PAD_SPDIF_IN_IS_GPIO
#define PAD_SPDIF_IN_IS_GPIO BALL_A13_IS_GPIO
#endif 

#define BALL_A17 PAD_GPIO13
#define PAD_GPIO13 53
#define GPIO_PAD_53 GPIO52
#ifndef BALL_A17_IS_GPIO
#define BALL_A17_IS_GPIO 0
#endif 
#ifndef PAD_GPIO13_IS_GPIO
#define PAD_GPIO13_IS_GPIO BALL_A17_IS_GPIO
#endif 

#define BALL_B13 PAD_SPDIF_OUT
#define PAD_SPDIF_OUT 152
#define GPIO_PAD_152 GPIO151
#ifndef BALL_B13_IS_GPIO
#define BALL_B13_IS_GPIO 0
#endif 
#ifndef PAD_SPDIF_OUT_IS_GPIO
#define PAD_SPDIF_OUT_IS_GPIO BALL_B13_IS_GPIO
#endif 

#define PAD_GPIO14 9999
#ifndef PAD_GPIO14_IS_GPIO
#define PAD_GPIO14_IS_GPIO 0
#endif 

#define BALL_E11 PAD_GPIO0
#define PAD_GPIO0 40
#define GPIO_PAD_40 GPIO39
#ifndef BALL_E11_IS_GPIO
#define BALL_E11_IS_GPIO 0
#endif 
#ifndef PAD_GPIO0_IS_GPIO
#define PAD_GPIO0_IS_GPIO BALL_E11_IS_GPIO
#endif 

#define PAD_GPIO15 9999
#ifndef PAD_GPIO15_IS_GPIO
#define PAD_GPIO15_IS_GPIO 0
#endif 

#define BALL_D11 PAD_GPIO1
#define PAD_GPIO1 41
#define GPIO_PAD_41 GPIO40
#ifndef BALL_D11_IS_GPIO
#define BALL_D11_IS_GPIO 0
#endif 
#ifndef PAD_GPIO1_IS_GPIO
#define PAD_GPIO1_IS_GPIO BALL_D11_IS_GPIO
#endif 

#define BALL_C13 PAD_GPIO16
#define PAD_GPIO16 56
#define GPIO_PAD_56 GPIO55
#ifndef BALL_C13_IS_GPIO
#define BALL_C13_IS_GPIO 0
#endif 
#ifndef PAD_GPIO16_IS_GPIO
#define PAD_GPIO16_IS_GPIO BALL_C13_IS_GPIO
#endif 

#define BALL_D12 PAD_GPIO2
#define PAD_GPIO2 42
#define GPIO_PAD_42 GPIO41
#ifndef BALL_D12_IS_GPIO
#define BALL_D12_IS_GPIO 0
#endif 
#ifndef PAD_GPIO2_IS_GPIO
#define PAD_GPIO2_IS_GPIO BALL_D12_IS_GPIO
#endif 

#define PAD_GPIO17 9999
#ifndef PAD_GPIO17_IS_GPIO
#define PAD_GPIO17_IS_GPIO 0
#endif 

#define BALL_E12 PAD_GPIO3
#define PAD_GPIO3 43
#define GPIO_PAD_43 GPIO42
#ifndef BALL_E12_IS_GPIO
#define BALL_E12_IS_GPIO 0
#endif 
#ifndef PAD_GPIO3_IS_GPIO
#define PAD_GPIO3_IS_GPIO BALL_E12_IS_GPIO
#endif 

#define PAD_GPIO18 9999
#ifndef PAD_GPIO18_IS_GPIO
#define PAD_GPIO18_IS_GPIO 0
#endif 

#define BALL_B19 PAD_GPIO4
#define PAD_GPIO4 44
#define GPIO_PAD_44 GPIO43
#ifndef BALL_B19_IS_GPIO
#define BALL_B19_IS_GPIO 0
#endif 
#ifndef PAD_GPIO4_IS_GPIO
#define PAD_GPIO4_IS_GPIO BALL_B19_IS_GPIO
#endif 

#define BALL_B9 PAD_GPIO19
#define PAD_GPIO19 59
#define GPIO_PAD_59 GPIO58
#ifndef BALL_B9_IS_GPIO
#define BALL_B9_IS_GPIO 0
#endif 
#ifndef PAD_GPIO19_IS_GPIO
#define PAD_GPIO19_IS_GPIO BALL_B9_IS_GPIO
#endif 

#define BALL_A19 PAD_GPIO5
#define PAD_GPIO5 45
#define GPIO_PAD_45 GPIO44
#ifndef BALL_A19_IS_GPIO
#define BALL_A19_IS_GPIO 0
#endif 
#ifndef PAD_GPIO5_IS_GPIO
#define PAD_GPIO5_IS_GPIO BALL_A19_IS_GPIO
#endif 

#define BALL_B11 PAD_GPIO22
#define PAD_GPIO22 62
#define GPIO_PAD_62 GPIO61
#ifndef BALL_B11_IS_GPIO
#define BALL_B11_IS_GPIO 0
#endif 
#ifndef PAD_GPIO22_IS_GPIO
#define PAD_GPIO22_IS_GPIO BALL_B11_IS_GPIO
#endif 

#define BALL_B20 PAD_GPIO6
#define PAD_GPIO6 46
#define GPIO_PAD_46 GPIO45
#ifndef BALL_B20_IS_GPIO
#define BALL_B20_IS_GPIO 0
#endif 
#ifndef PAD_GPIO6_IS_GPIO
#define PAD_GPIO6_IS_GPIO BALL_B20_IS_GPIO
#endif 

#define BALL_C9 PAD_GPIO20
#define PAD_GPIO20 60
#define GPIO_PAD_60 GPIO59
#ifndef BALL_C9_IS_GPIO
#define BALL_C9_IS_GPIO 0
#endif 
#ifndef PAD_GPIO20_IS_GPIO
#define PAD_GPIO20_IS_GPIO BALL_C9_IS_GPIO
#endif 

#define BALL_A14 PAD_GPIO7
#define PAD_GPIO7 47
#define GPIO_PAD_47 GPIO46
#ifndef BALL_A14_IS_GPIO
#define BALL_A14_IS_GPIO 0
#endif 
#ifndef PAD_GPIO7_IS_GPIO
#define PAD_GPIO7_IS_GPIO BALL_A14_IS_GPIO
#endif 

#define PAD_GPIO24 9999
#ifndef PAD_GPIO24_IS_GPIO
#define PAD_GPIO24_IS_GPIO 0
#endif 

#define BALL_D13 PAD_GPIO8
#define PAD_GPIO8 48
#define GPIO_PAD_48 GPIO47
#ifndef BALL_D13_IS_GPIO
#define BALL_D13_IS_GPIO 0
#endif 
#ifndef PAD_GPIO8_IS_GPIO
#define PAD_GPIO8_IS_GPIO BALL_D13_IS_GPIO
#endif 

#define PAD_GPIO27 9999
#ifndef PAD_GPIO27_IS_GPIO
#define PAD_GPIO27_IS_GPIO 0
#endif 

#define PAD_GPIO21 9999
#ifndef PAD_GPIO21_IS_GPIO
#define PAD_GPIO21_IS_GPIO 0
#endif 

#define BALL_C12 PAD_GPIO26
#define PAD_GPIO26 66
#define GPIO_PAD_66 GPIO65
#ifndef BALL_C12_IS_GPIO
#define BALL_C12_IS_GPIO 0
#endif 
#ifndef PAD_GPIO26_IS_GPIO
#define PAD_GPIO26_IS_GPIO BALL_C12_IS_GPIO
#endif 

#define PAD_GPIO23 9999
#ifndef PAD_GPIO23_IS_GPIO
#define PAD_GPIO23_IS_GPIO 0
#endif 

#define BALL_B12 PAD_GPIO25
#define PAD_GPIO25 65
#define GPIO_PAD_65 GPIO64
#ifndef BALL_B12_IS_GPIO
#define BALL_B12_IS_GPIO 0
#endif 
#ifndef PAD_GPIO25_IS_GPIO
#define PAD_GPIO25_IS_GPIO BALL_B12_IS_GPIO
#endif 

#define BALL_C5 PAD_PM_SPI_CK
#define PAD_PM_SPI_CK 2
#define GPIO_PAD_2 GPIO1
#ifndef BALL_C5_IS_GPIO
#define BALL_C5_IS_GPIO 0
#endif 
#ifndef PAD_PM_SPI_CK_IS_GPIO
#define PAD_PM_SPI_CK_IS_GPIO BALL_C5_IS_GPIO
#endif 

#define BALL_D8 PAD_SAR0
#define PAD_SAR0 35
#define GPIO_PAD_35 GPIO34
#ifndef BALL_D8_IS_GPIO
#define BALL_D8_IS_GPIO 0
#endif 
#ifndef PAD_SAR0_IS_GPIO
#define PAD_SAR0_IS_GPIO BALL_D8_IS_GPIO
#endif 

#define BALL_B4 PAD_PM_SPI_DI
#define PAD_PM_SPI_DI 3
#define GPIO_PAD_3 GPIO2
#ifndef BALL_B4_IS_GPIO
#define BALL_B4_IS_GPIO 0
#endif 
#ifndef PAD_PM_SPI_DI_IS_GPIO
#define PAD_PM_SPI_DI_IS_GPIO BALL_B4_IS_GPIO
#endif 

#define BALL_C4 PAD_PM_SPI_DO
#define PAD_PM_SPI_DO 4
#define GPIO_PAD_4 GPIO3
#ifndef BALL_C4_IS_GPIO
#define BALL_C4_IS_GPIO 0
#endif 
#ifndef PAD_PM_SPI_DO_IS_GPIO
#define PAD_PM_SPI_DO_IS_GPIO BALL_C4_IS_GPIO
#endif 

#define BALL_E8 PAD_SAR1
#define PAD_SAR1 36
#define GPIO_PAD_36 GPIO35
#ifndef BALL_E8_IS_GPIO
#define BALL_E8_IS_GPIO 0
#endif 
#ifndef PAD_SAR1_IS_GPIO
#define PAD_SAR1_IS_GPIO BALL_E8_IS_GPIO
#endif 

#define BALL_A11 PAD_GPIO_PM3
#define PAD_GPIO_PM3 10
#define GPIO_PAD_10 GPIO9
#ifndef BALL_A11_IS_GPIO
#define BALL_A11_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM3_IS_GPIO
#define PAD_GPIO_PM3_IS_GPIO BALL_A11_IS_GPIO
#endif 

#define BALL_C3 PAD_PM_SPI_CZ
#define PAD_PM_SPI_CZ 1
#define GPIO_PAD_1 GPIO0
#ifndef BALL_C3_IS_GPIO
#define BALL_C3_IS_GPIO 0
#endif 
#ifndef PAD_PM_SPI_CZ_IS_GPIO
#define PAD_PM_SPI_CZ_IS_GPIO BALL_C3_IS_GPIO
#endif 

#define BALL_C10 PAD_SAR2
#define PAD_SAR2 37
#define GPIO_PAD_37 GPIO36
#ifndef BALL_C10_IS_GPIO
#define BALL_C10_IS_GPIO 0
#endif 
#ifndef PAD_SAR2_IS_GPIO
#define PAD_SAR2_IS_GPIO BALL_C10_IS_GPIO
#endif 

#define BALL_B3 PAD_GPIO_PM6
#define PAD_GPIO_PM6 13
#define GPIO_PAD_13 GPIO12
#ifndef BALL_B3_IS_GPIO
#define BALL_B3_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM6_IS_GPIO
#define PAD_GPIO_PM6_IS_GPIO BALL_B3_IS_GPIO
#endif 

#define BALL_J6 PAD_HOTPLUGA
#define PAD_HOTPLUGA 23
#define GPIO_PAD_23 GPIO22
#ifndef BALL_J6_IS_GPIO
#define BALL_J6_IS_GPIO 0
#endif 
#ifndef PAD_HOTPLUGA_IS_GPIO
#define PAD_HOTPLUGA_IS_GPIO BALL_J6_IS_GPIO
#endif 

#define BALL_E7 PAD_SAR3
#define PAD_SAR3 38
#define GPIO_PAD_38 GPIO37
#ifndef BALL_E7_IS_GPIO
#define BALL_E7_IS_GPIO 0
#endif 
#ifndef PAD_SAR3_IS_GPIO
#define PAD_SAR3_IS_GPIO BALL_E7_IS_GPIO
#endif 

#define BALL_C11 PAD_GPIO_PM7
#define PAD_GPIO_PM7 14
#define GPIO_PAD_14 GPIO13
#ifndef BALL_C11_IS_GPIO
#define BALL_C11_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM7_IS_GPIO
#define PAD_GPIO_PM7_IS_GPIO BALL_C11_IS_GPIO
#endif 

#define BALL_K6 PAD_HOTPLUGB
#define PAD_HOTPLUGB 24
#define GPIO_PAD_24 GPIO23
#ifndef BALL_K6_IS_GPIO
#define BALL_K6_IS_GPIO 0
#endif 
#ifndef PAD_HOTPLUGB_IS_GPIO
#define PAD_HOTPLUGB_IS_GPIO BALL_K6_IS_GPIO
#endif 

#define BALL_D7 PAD_SAR4
#define PAD_SAR4 39
#define GPIO_PAD_39 GPIO38
#ifndef BALL_D7_IS_GPIO
#define BALL_D7_IS_GPIO 0
#endif 
#ifndef PAD_SAR4_IS_GPIO
#define PAD_SAR4_IS_GPIO BALL_D7_IS_GPIO
#endif 

#define BALL_G4 PAD_IRIN
#define PAD_IRIN 5
#define GPIO_PAD_5 GPIO4
#ifndef BALL_G4_IS_GPIO
#define BALL_G4_IS_GPIO 0
#endif 
#ifndef PAD_IRIN_IS_GPIO
#define PAD_IRIN_IS_GPIO BALL_G4_IS_GPIO
#endif 

#define BALL_J5 PAD_DDCDA_CK
#define PAD_DDCDA_CK 27
#define GPIO_PAD_27 GPIO26
#ifndef BALL_J5_IS_GPIO
#define BALL_J5_IS_GPIO 0
#endif 
#ifndef PAD_DDCDA_CK_IS_GPIO
#define PAD_DDCDA_CK_IS_GPIO BALL_J5_IS_GPIO
#endif 

#define BALL_F6 PAD_GPIO_PM8
#define PAD_GPIO_PM8 15
#define GPIO_PAD_15 GPIO14
#ifndef BALL_F6_IS_GPIO
#define BALL_F6_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM8_IS_GPIO
#define PAD_GPIO_PM8_IS_GPIO BALL_F6_IS_GPIO
#endif 

#define BALL_J4 PAD_DDCDA_DA
#define PAD_DDCDA_DA 28
#define GPIO_PAD_28 GPIO27
#ifndef BALL_J4_IS_GPIO
#define BALL_J4_IS_GPIO 0
#endif 
#ifndef PAD_DDCDA_DA_IS_GPIO
#define PAD_DDCDA_DA_IS_GPIO BALL_J4_IS_GPIO
#endif 

#define BALL_H5 PAD_CEC
#define PAD_CEC 6
#define GPIO_PAD_6 GPIO5
#ifndef BALL_H5_IS_GPIO
#define BALL_H5_IS_GPIO 0
#endif 
#ifndef PAD_CEC_IS_GPIO
#define PAD_CEC_IS_GPIO BALL_H5_IS_GPIO
#endif 

#define BALL_K4 PAD_DDCDB_CK
#define PAD_DDCDB_CK 29
#define GPIO_PAD_29 GPIO28
#ifndef BALL_K4_IS_GPIO
#define BALL_K4_IS_GPIO 0
#endif 
#ifndef PAD_DDCDB_CK_IS_GPIO
#define PAD_DDCDB_CK_IS_GPIO BALL_K4_IS_GPIO
#endif 

#define BALL_F4 PAD_PWM_PM
#define PAD_PWM_PM 198
#define GPIO_PAD_198 GPIO197
#ifndef BALL_F4_IS_GPIO
#define BALL_F4_IS_GPIO 0
#endif 
#ifndef PAD_PWM_PM_IS_GPIO
#define PAD_PWM_PM_IS_GPIO BALL_F4_IS_GPIO
#endif 

#define BALL_K5 PAD_DDCDB_DA
#define PAD_DDCDB_DA 30
#define GPIO_PAD_30 GPIO29
#ifndef BALL_K5_IS_GPIO
#define BALL_K5_IS_GPIO 0
#endif 
#ifndef PAD_DDCDB_DA_IS_GPIO
#define PAD_DDCDB_DA_IS_GPIO BALL_K5_IS_GPIO
#endif 

#define BALL_G6 PAD_GPIO_PM9
#define PAD_GPIO_PM9 16
#define GPIO_PAD_16 GPIO15
#ifndef BALL_G6_IS_GPIO
#define BALL_G6_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM9_IS_GPIO
#define PAD_GPIO_PM9_IS_GPIO BALL_G6_IS_GPIO
#endif 

#define BALL_L5 PAD_DDCDD_CK
#define PAD_DDCDD_CK 33
#define GPIO_PAD_33 GPIO32
#ifndef BALL_L5_IS_GPIO
#define BALL_L5_IS_GPIO 0
#endif 
#ifndef PAD_DDCDD_CK_IS_GPIO
#define PAD_DDCDD_CK_IS_GPIO BALL_L5_IS_GPIO
#endif 

#define BALL_M5 PAD_DDCDD_DA
#define PAD_DDCDD_DA 34
#define GPIO_PAD_34 GPIO33
#ifndef BALL_M5_IS_GPIO
#define BALL_M5_IS_GPIO 0
#endif 
#ifndef PAD_DDCDD_DA_IS_GPIO
#define PAD_DDCDD_DA_IS_GPIO BALL_M5_IS_GPIO
#endif 

#define BALL_F5 PAD_GPIO_PM0
#define PAD_GPIO_PM0 7
#define GPIO_PAD_7 GPIO6
#ifndef BALL_F5_IS_GPIO
#define BALL_F5_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM0_IS_GPIO
#define PAD_GPIO_PM0_IS_GPIO BALL_F5_IS_GPIO
#endif 

#define PAD_AV_LNK 9999
#ifndef PAD_AV_LNK_IS_GPIO
#define PAD_AV_LNK_IS_GPIO 0
#endif 

#define BALL_B6 PAD_GPIO_PM11
#define PAD_GPIO_PM11 18
#define GPIO_PAD_18 GPIO17
#ifndef BALL_B6_IS_GPIO
#define BALL_B6_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM11_IS_GPIO
#define PAD_GPIO_PM11_IS_GPIO BALL_B6_IS_GPIO
#endif 

#define BALL_A3 PAD_GPIO_PM10
#define PAD_GPIO_PM10 17
#define GPIO_PAD_17 GPIO16
#ifndef BALL_A3_IS_GPIO
#define BALL_A3_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM10_IS_GPIO
#define PAD_GPIO_PM10_IS_GPIO BALL_A3_IS_GPIO
#endif 

#define BALL_G5 PAD_GPIO_PM1
#define PAD_GPIO_PM1 8
#define GPIO_PAD_8 GPIO7
#ifndef BALL_G5_IS_GPIO
#define BALL_G5_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM1_IS_GPIO
#define PAD_GPIO_PM1_IS_GPIO BALL_G5_IS_GPIO
#endif 

#define BALL_C6 PAD_GPIO_PM12
#define PAD_GPIO_PM12 19
#define GPIO_PAD_19 GPIO18
#ifndef BALL_C6_IS_GPIO
#define BALL_C6_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM12_IS_GPIO
#define PAD_GPIO_PM12_IS_GPIO BALL_C6_IS_GPIO
#endif 

#define BALL_D6 PAD_GPIO_PM2
#define PAD_GPIO_PM2 9
#define GPIO_PAD_9 GPIO8
#ifndef BALL_D6_IS_GPIO
#define BALL_D6_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM2_IS_GPIO
#define PAD_GPIO_PM2_IS_GPIO BALL_D6_IS_GPIO
#endif 

#define BALL_E4 PAD_GPIO_PM14
#define PAD_GPIO_PM14 21
#define GPIO_PAD_21 GPIO20
#ifndef BALL_E4_IS_GPIO
#define BALL_E4_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM14_IS_GPIO
#define PAD_GPIO_PM14_IS_GPIO BALL_E4_IS_GPIO
#endif 

#define BALL_C7 PAD_GPIO_PM4
#define PAD_GPIO_PM4 11
#define GPIO_PAD_11 GPIO10
#ifndef BALL_C7_IS_GPIO
#define BALL_C7_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM4_IS_GPIO
#define PAD_GPIO_PM4_IS_GPIO BALL_C7_IS_GPIO
#endif 

#define BALL_E6 PAD_GPIO_PM5
#define PAD_GPIO_PM5 12
#define GPIO_PAD_12 GPIO11
#ifndef BALL_E6_IS_GPIO
#define BALL_E6_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM5_IS_GPIO
#define PAD_GPIO_PM5_IS_GPIO BALL_E6_IS_GPIO
#endif 

#define BALL_D5 PAD_GPIO_PM13
#define PAD_GPIO_PM13 20
#define GPIO_PAD_20 GPIO19
#ifndef BALL_D5_IS_GPIO
#define BALL_D5_IS_GPIO 0
#endif 
#ifndef PAD_GPIO_PM13_IS_GPIO
#define PAD_GPIO_PM13_IS_GPIO BALL_D5_IS_GPIO
#endif 


// PADS group name to index
#define PADS_DDCR           1223
#define PADS_DDCR2          1224
#define PADS_TS0            1225
#define PADS_TS1            1226
#define PADS_GPIO1_GPIO2    1227
#define PADS_LHSYNC2_LVSYNC2 1228
#define PADS_PCI_AD20_AD21  1229
#define PADS_PCI            1230
#define PADS_PCM            1231
#define PADS_SAR            1232
#define PADS_DOUT           1233
#define PADS_DIN            1234
#define PADS_I2S            1235
#define PADS_PF             1236
#define PADS_EMAC           1237
#define PADS_TCON           1238
#define PADS_UART1_MODE1    1239
#define PADS_UART1_MODE2    1240
#define PADS_UART1_MODE3    1241
#define PADS_UART2_MODE1    1242
#define PADS_UART2_MODE2    1243
#define PADS_UART2_MODE3    1244
#define PADS_ET_MODE0       1245
#define PADS_ET_MODE1       1246
#define PADS_ET_MODE2       1247
#define PADS_ET_MODE3       1248
#define PADS_MIIC           1249
#define PADS_PF_MODE1       1250
#define PADS_PF_MODE2       1251
#define PADS_PF_MODE3       1252
#define PADS_SPI_CZ1        1253
#define PADS_SPI_CZ2        1254
#define PADS_SPI_CZ3        1255
#define PADS_DDCR3          1256

// chip capbilities
#define CHIP_HAS_BT656_IN          0
#define CHIP_HAS_TS0               1
#define CHIP_HAS_TS1               0 
#define CHIP_HAS_LVDS_10BIT_X2     1
#define CHIP_HAS_LVDS_8BIT_X2      1
#define CHIP_HAS_LVDS_8BIT_X1      1
#define CHIP_HAS_CIMAX             0
#define CHIP_HAS_USB_P0            1
#define CHIP_HAS_USB_P1            1
#define CHIP_HAS_USBVBUS0          0
#define CHIP_HAS_USBVBUS1          0
#define CHIP_HAS_UART1_MODE1       1 
#define CHIP_HAS_UART1_MODE2       1
#define CHIP_HAS_UART1_MODE3       1 
#define CHIP_HAS_PCMCIA1           0
#define CHIP_HAS_PCMCIA2           0
#define CHIP_HAS_PCMCIA            0
#define CHIP_HAS_UART2_MODE1       1 
#define CHIP_HAS_UART2_MODE2       1 
#define CHIP_HAS_UART2_MODE3       1 
#define CHIP_HAS_RGB_A             1 
#define CHIP_HAS_RGB_B             1 
#define CHIP_HAS_RGB_C             1 
#define CHIP_HAS_HDMI_A            1 
#define CHIP_HAS_HDMI_B            1 
#define CHIP_HAS_HDMI_C            1 
#define CHIP_HAS_SPI_CZ1           1 
#define CHIP_HAS_SPI_CZ2           0 
#define CHIP_HAS_SPI_CZ3           0
#define CHIP_HAS_DDCR              1 
#define CHIP_HAS_DDCR2             1 
#define CHIP_HAS_TCON              1
#define CHIP_HAS_ET_MODE0_MII      1 
#define CHIP_HAS_ET_MODE0_RMII     1 
#define CHIP_HAS_ET_MODE1_MII      1 
#define CHIP_HAS_ET_MODE1_RMII     1 
#define CHIP_HAS_ET_MODE2_MII      1
#define CHIP_HAS_ET_MODE2_RMII     1
#define CHIP_HAS_I2S_IN            1 
#define CHIP_HAS_I2S_OUT           1
#define CHIP_HAS_SPDIF_IN          0 
#define CHIP_HAS_SPDIF_OUT         1
#define CHIP_HAS_DDR_A_CMD         1
#define CHIP_HAS_DDR_A_DATA        1
#define CHIP_HAS_DDR_B_CMD         1
#define CHIP_HAS_DDR_B_DATA        1
#define CHIP_USE_PCM_CDN_IN_PCM2   0
#define CHIP_USE_I2S_IN_IN_PCM     0
#define CHIP_USE_I2S_OUT_IN_PCM    0
#define CHIP_USE_SPDIF_IN_IN_PCM   0
#define CHIP_USE_SPDIF_OUT_IN_PCM  0
#define CHIP_USE_IIC_IN_DDCR2      0
#define CHIP_USE_PWM2_IN_GPIO14    0
#define CHIP_USE_PWM3_IN_GPIO15    0

// chip additional information
#define CHIP_FAMILY_TYPE           CHIP_FAMILY_EMERALD

#endif /* _MCP_17_H_*/
