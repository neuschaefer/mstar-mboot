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
    //************************************************************
    //***             RIU Base address of each IP              ***
    //***                (Byte address [23:0])                 ***
    //************************************************************

#define    RIUBASE_PM_RIU_DBG          0x000100    //0x000100 ~ 0x0001ff
#define    RIUBASE_MENULOAD            0x000200    //0x000200 ~ 0x00021f
#define    RIUBASE_DDC                 0x000400    //0x000400 ~ 0x0004ff
#define    RIUBASE_ISP                 0x000800    //0x000800 ~ 0x0008df
#define    RIUBASE_QSPI                0x0008e0    //0x0008e0 ~ 0x0008ff
#define    RIUBASE_PM_SLEEP            0x000e00    //0x000e00 ~ 0x000eff
#define    RIUBASE_MCU                 0x001000    //0x001000 ~ 0x0010ff
#define    RIUBASE_PM_CEC              0x001100    //0x001100 ~ 0x0011ff
#define    RIUBASE_PM_RTC              0x001200    //0x001200 ~ 0x0012ff
#define    RIUBASE_PM_RTC2             0x001300    //0x001300 ~ 0x0013ff
#define    RIUBASE_PM_SAR              0x001400    //0x001400 ~ 0x0014ff
#define    RIUBASE_PM_AV_LNK           0x001500    //0x001500 ~ 0x0015ff
#define    RIUBASE_EFUSE               0x002000    //0x002000 ~ 0x0020ff
#define    RIUBASE_IRQ                 0x002b00    //0x002b00 ~ 0x002b7f
#define    RIUBASE_CACHE               0x002b80    //0x002b80 ~ 0x002bbf
#define    RIUBASE_XDMIU               0x002bc0    //0x002bc0 ~ 0x002bff
#define    RIUBASE_WDT                 0x003000    //0x003000 ~ 0x00301f
#define    RIUBASE_TIMER0              0x003020    //0x003020 ~ 0x00303f
#define    RIUBASE_TIMER1              0x003040    //0x003040 ~ 0x00305f
#define    RIUBASE_REG_PIU_MISC_0      0x003c00    //0x003c00 ~ 0x003cff
#define    RIUBASE_IR                  0x003d00    //0x003d00 ~ 0x003dff
