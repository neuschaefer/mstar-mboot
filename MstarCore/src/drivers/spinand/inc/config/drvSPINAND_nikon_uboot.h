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

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    regSPINAND.h
/// @brief  Serial Flash Register Definition
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _REG_SPINAND_H_
#define _REG_SPINAND_H_


//-------------------------------------------------------------------------------------------------
//  Hardware Capability
//-------------------------------------------------------------------------------------------------

// !!! Uranus Serial Flash Notes: !!!
//  - The clock of DMA & Read via XIU operations must be < 3*CPU clock
//  - The clock of DMA & Read via XIU operations are determined by only REG_ISP_CLK_SRC; other operations by REG_ISP_CLK_SRC only
//  - DMA program can't run on DRAM, but in flash ONLY
//  - DMA from SPI to DRAM => size/DRAM start/DRAM end must be 8-B aligned


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

#define REG(Reg_Addr)               (*(volatile U16*)(Reg_Addr))
#define REG_OFFSET_SHIFT_BITS       2
#define GET_REG_ADDR(x, y)          (x+((y)<<REG_OFFSET_SHIFT_BITS))

// BASEADDR & BK
//------------------------------
#define RIU_PM_BASE                         0xBF000000
#define RIU_BASE                            0xBF200000

#define BK_ISP                              0x1000
#define BK_FSP                              0x1200
#define BK_QSPI                             0x1400
#define BK_PMSLP                            0x1E00
#define BK_CLK0                             0x1600
#define BK_BDMA                             0x1200
#define BK_CHIP                             0x3C00
#define FSP_REG_BASE_ADDR                   GET_REG_ADDR(RIU_BASE, BK_FSP)
#define QSPI_REG_BASE_ADDR                  GET_REG_ADDR(RIU_BASE, BK_QSPI)
#define PMSLP_REG_BASE_ADDR                 GET_REG_ADDR(RIU_BASE, BK_PMSLP)
#define CLK0_REG_BASE_ADDR                  GET_REG_ADDR(RIU_BASE, BK_CLK0)
#define BDMA_REG_BASE_ADDR                  GET_REG_ADDR(RIU_BASE, BK_BDMA)
#define CHIP_REG_BASE_ADDR                  GET_REG_ADDR(RIU_BASE, BK_CHIP)

#define REG_BANK_TIMER                      (0x1800)
#define TIMER_REG_BASE_ADDR                 GET_REG_ADDR(RIU_PM_BASE, REG_BANK_TIMER)
#define TIMER1_ENABLE                       GET_REG_ADDR(TIMER_REG_BASE_ADDR, 0x20)
#define TIMER1_HIT                          GET_REG_ADDR(TIMER_REG_BASE_ADDR, 0x21)
#define TIMER1_MAX_LOW                      GET_REG_ADDR(TIMER_REG_BASE_ADDR, 0x22)
#define TIMER1_MAX_HIGH                     GET_REG_ADDR(TIMER_REG_BASE_ADDR, 0x23)
#define TIMER1_CAP_LOW                      GET_REG_ADDR(TIMER_REG_BASE_ADDR, 0x24)
#define TIMER1_CAP_HIGH                     GET_REG_ADDR(TIMER_REG_BASE_ADDR, 0x25)

//----- Chip flash -------------------------
#include"drvSPINAND_reg.h"
#endif // _REG_SPINAND_H_
