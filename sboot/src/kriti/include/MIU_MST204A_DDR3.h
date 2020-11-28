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

#ifndef _MIU_MST204A_DDR3_H_
#define _MIU_MST204A_DDR3_H_

const MS_REG_INIT MIU_DDR3_NANYA_Init[] =
{
_RV32_2(0x101220, 0x0000),   //miu initial
_RV32_2(0x10121e, 0x0c00),   //miu initial
_RV32_2(0x10121e, 0x0c00),
_RV32_2(0x10121e, 0x0c00),
_RV32_2(0x10121e, 0x0c01),   //miu software reset
_RV32_2(0x10121e, 0x0c00),
_RV32_2(0x101202, 0x0000),   //dram type set as '0'
_RV32_2(0x101246, 0xFFFE),   //mask group0
_RV32_2(0x101266, 0xFFFF),   //mask group1
_RV32_2(0x101286, 0xFFFF),   //mask group2
_RV32_2(0x1012A6, 0xFFFF),   //mask group3
//--------------------
//set DDRPLL0 1600MHz
//--------------------
_RV32_2(0x110d36, 0x4000),
_RV32_2(0x110d34, 0x0400),
#if ENABLE_MEM1600MHz
_RV32_2(0x110d30, 0xE8BA),		//Clock generator frequency set
_RV32_2(0x110d32, 0x0022),		//MCLK Freq (miu0)
#elif ENABLE_MEM1333MHz
_RV32_2(0x110d30, 0x7b7c),		//Clock generator frequency set
_RV32_2(0x110d32, 0x0029),		//MCLK Freq (miu0)
#endif
_RV32_2(0x110d22, 0x2000),
_RV32_2(0x110d24, 0x2000),
_RV32_2(0x110d24, 0x3000),
_RV32_2(0x110d24, 0x2000),
//------------------
// Wait PLL Stable
//------------------

_RV32_2(0x101202, 0x03a3),
_RV32_2(0x101204, 0x004a),
_RV32_2(0x101206, 0x1430),//[12:12] reg_cke_always_on	
_RV32_2(0x101208, 0x1cbb),
_RV32_2(0x10120a, 0x2767),
_RV32_2(0x10120c, 0xb6c8),
_RV32_2(0x10120e, 0x4080),
_RV32_2(0x101210, 0x1d70),
_RV32_2(0x101212, 0x4004),
_RV32_2(0x101214, 0x8018),
_RV32_2(0x101216, 0xc000),
_RV32_2(0x10122c, 0x0000),
_RV32_2(0x110d02, 0xaaaa),
_RV32_2(0x110d04, 0x0080),
_RV32_2(0x110d3c, 0x1133),
_RV32_2(0x110d4e, 0x0033),
_RV32_2(0x110d3e, 0x1011),
_RV32_2(0x110d4c, 0x1133),
_RV32_2(0x110d0a, 0x1022),
_RV32_2(0x110d50, 0x1111),
_RV32_2(0x110d38, 0x0065),
_RV32_2(0x110d3a, 0x4042),
_RV32_2(0x110d48, 0x0033),
_RV32_2(0x110d4a, 0x0002),
_RV32_2(0x110d52, 0x0002),
_RV32_2(0x110d74, 0x2077),
_RV32_2(0x110d78, 0x0002),
_RV32_2(0x110d7a, 0x3800),
_RV32_2(0x110d6c, 0x5555),
_RV32_2(0x110d6e, 0x3344),
_RV32_2(0x110d0e, 0x00a7),
_RV32_2(0x110d0e, 0x00e7),
_RV32_2(0x110d0e, 0x00a7),
_RV32_2(0x10121e, 0x0c01),
_RV32_2(0x10121e, 0x0c00),
_RV32_2(0x110d00, 0x0039),
_RV32_2(0x110d00, 0x0031),
_RV32_2(0x110d00, 0x0021),
_RV32_2(0x110d7c, 0x000f),
_RV32_2(0x110d7e, 0x0000),
_RV32_2(0x110d54, 0xc000),
_RV32_2(0x110d08, 0x00ff),
_RV32_2(0x110d0e, 0x00a7),
_RV32_2(0x110d0e, 0x00e7),
_RV32_2(0x110d0e, 0x00a7),
_RV32_2(0x110d74, 0x0007),
_RV32_2(0x110d58, 0x5c5c),
_RV32_2(0x110d5c, 0x5555),
_RV32_2(0x110d5e, 0x5555),
_RV32_2(0x110d28, 0x0017),
_RV32_2(0x110d2a, 0x03DE),
_RV32_2(0x101200, 0x0000),
//-----Wait 200us, (keep DRAM RESET = 0)-----

_RV32_2(0x101200, 0x0008),
_RV32_2(0x101200, 0x000c),
//-----Wait 500us, (keep DRAM RESET = 1 , CKE = 0)-----

_RV32_2(0x101200, 0x000e),
//-----Wait tXPR=400ns-----

//--------Initial DRAM start here!!!
_RV32_2(0x101200, 0x001f),
//-----Wait init done-----

//--------Initial Done
//--------DDR2 wait 400ns for tXPR(?), DDR3 wait 512T for tZQinit

//-------------
// BW setting  
//-------------
_RV32_2(0x101240, 0x8015),
_RV32_2(0x101260, 0x8015),
_RV32_2(0x101280, 0x8015),
_RV32_2(0x1012a0, 0x8015),
_RV32_2(0x110d62, 0x0032),
_RV32_2(0x110d64, 0xf200),
_RV32_2(0x110d68, 0x0020),
_RV32_2(0x110d6a, 0x0020),
_RV32_2(0x110d60, 0x000c),
_RV32_2(0x110d60, 0x0008),
_RV32_2(0x110d60, 0x2370),
//--------------------
// MIU select setting 
//----------- --------
//---------------------------------
// Pack setting                    
//---------------------------------
_RV32_2(0x101228, 0x4090),
//-------------------------
// Reduce latency setting  
//-------------------------
_RV32_2(0x10122a, 0x0000),
_RV32_2(0x1012d4, 0x0000),
//------------------------------
// unmask all                   
//------------------------------
_RV32_2(0x10121a, 0x0001),
_RV32_2(0x1012fc, 0x0400),

_RV32_2(0x101246, 0x0000),
_RV32_2(0x101266, 0x0000),
_RV32_2(0x101286, 0x0000),
_RV32_2(0x1012a6, 0x0000),
_RV32_2(0x10121e, 0x5a08),
_RV32_2(0x1012fe, 0x00e1),
_RV32_2(0x1012fe, 0x01e1),
_RV32_2(0x1012fe, 0x00e1),
    _END_OF_TBL32_,
};

#endif /* _MIU_MST204A_DDR3_H_ */
