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

//************************************************************
//***             RIU Base address of each IP              ***
//***                (2 Byte address [23:0])               ***
//************************************************************

#ifndef _C_DMD_RIUBASE_H_
#define _C_DMD_RIUBASE_H_

#define RIUBASE_DMD_RIU_DBG         0x000100    //0x000100 ~ 0x0001ff
#define RIUBASE_DMDMCU51            0x001000    //0x001000 ~ 0x0010ff
#define RIUBASE_DUM0                0x001400    //0x001400 ~ 0x0014ff
#define RIUBASE_DUM1                0x001500    //0x001500 ~ 0x0015ff
#define RIUBASE_DUM2                0x001600    //0x001600 ~ 0x0016ff
#define RIUBASE_DUM3                0x001700    //0x001700 ~ 0x0017ff
#define RIUBASE_DMDMCU51_IRQ        0x001b00    //0x001b00 ~ 0x001bff
#define RIUBASE_DMD_SAWLESS         0x001e00    //0x001e00 ~ 0x001eff
#define RIUBASE_DMD_BACKEND         0x001f00    //0x001f00 ~ 0x001fff
#define RIUBASE_DMD_DEMOD_0         0x002000    //0x002000 ~ 0x0020ff
#define RIUBASE_DMD_DEMOD_1         0x002100    //0x002100 ~ 0x0021ff
#define RIUBASE_DMD_DEMOD_2         0x002200    //0x002200 ~ 0x0022ff
#define RIUBASE_DMD_DEMOD_3         0x002300    //0x002300 ~ 0x0023ff
#define RIUBASE_DMD_DEMOD_4         0x002400    //0x002400 ~ 0x0024ff
#define RIUBASE_DMD_DEMOD_5         0x002500    //0x002500 ~ 0x0025ff
#define RIUBASE_DMD_DEMOD_6         0x002600    //0x002600 ~ 0x0026ff
#define RIUBASE_DMD_DEMOD_7         0x002700    //0x002700 ~ 0x0027ff
#define RIUBASE_DMD_DEMOD_8         0x002800    //0x002800 ~ 0x0028ff
#define RIUBASE_DMD_DEMOD_9         0x002900    //0x002900 ~ 0x0029ff
#define RIUBASE_DMD_DEMOD_A         0x002a00    //0x002a00 ~ 0x002aff
#define RIUBASE_DMD_DEMOD_B         0x002b00    //0x002b00 ~ 0x002bff
#define RIUBASE_DMD_DEMOD_C         0x002c00    //0x002c00 ~ 0x002cff
#define RIUBASE_DMD_DEMOD_D         0x002d00    //0x002d00 ~ 0x002dff
#define RIUBASE_DMD_DEMOD_E         0x002e00    //0x002e00 ~ 0x002eff
#define RIUBASE_DMD_DEMOD_F         0x002f00    //0x002f00 ~ 0x002fff
#define RIUBASE_DEMOD_VIF_RF        0x003100    //0x003100 ~ 0x0031ff
#define RIUBASE_DEMOD_VIF_DBB1      0x003200    //0x003200 ~ 0x0032ff
#define RIUBASE_DEMOD_VIF_DBB2      0x003300    //0x003300 ~ 0x0033ff
#define RIUBASE_DEMOD_VIF_DBB3      0x003400    //0x003400 ~ 0x0034ff
#define RIUBASE_DMD_CLKGEN          0x003500    //0x003500 ~ 0x0035ff

#endif  //_C_DMD_RIUBASE_H_