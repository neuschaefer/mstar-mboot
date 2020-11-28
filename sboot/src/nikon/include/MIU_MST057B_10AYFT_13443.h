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

#ifndef _MIU_MST057B_10AYFT_13443_H_
#define _MIU_MST057B_10AYFT_13443_H_

#if (ENABLE_MSTAR_BD_MST057B_10AYFT_13443)

const MS_REG_INIT MIU_ATOP_Init[] =
{
#if (ENABLE_MEM1066MHz == 1)
    _RV32_2(0x110d22, 0x2000),
    _RV32_2(0x110d24, 0x2000),
    _RV32_2(0x110d36, 0x4000),
    _RV32_2(0x110d34, 0x0000),
    _RV32_2(0x110d30, 0xdf59),
    _RV32_2(0x110d32, 0x0033),
    _RV32_2(0x110d24, 0x3000),
    _RV32_2(0x110d24, 0x2000),
#elif (ENABLE_MEM1300MHz == 1)
    _RV32_2(0x110d22, 0x2000),
    _RV32_2(0x110d24, 0x2000),
    _RV32_2(0x110d36, 0x4000),
    _RV32_2(0x110d34, 0x0000),
    _RV32_2(0x110d30, 0x7f46),
    _RV32_2(0x110d32, 0x0027),
    _RV32_2(0x110d24, 0x3000),
    _RV32_2(0x110d24, 0x2000),
#elif (ENABLE_MEM1600MHz == 1)
    _RV32_2(0x110d22, 0x2000),
    _RV32_2(0x110d24, 0x2000),
    _RV32_2(0x110d36, 0x4000),
    _RV32_2(0x110d34, 0x0000),
    _RV32_2(0x110d30, 0x8f6e),
    _RV32_2(0x110d32, 0x0022),
    _RV32_2(0x110d24, 0x3000),
    _RV32_2(0x110d24, 0x2000),
#elif (ENABLE_MEM1866MHz == 1)
    _RV32_2(0x110d22, 0x2000),
    _RV32_2(0x110d24, 0x2000),
    _RV32_2(0x110d36, 0x4000),
    _RV32_2(0x110d34, 0x0000),
    _RV32_2(0x110d30, 0x8f6e),
    _RV32_2(0x110d32, 0x0022),
    _RV32_2(0x110d24, 0x3000),
    _RV32_2(0x110d24, 0x2000),
#else
    #error  "Invalid DRAM Freq"
#endif
    _END_OF_TBL32_,
    MIU_VER
};


const MS_REG_INIT MIU_DDR_Init[] =
{
    _RV32_2(0x101202, 0x03a3),
    _RV32_2(0x101204, 0x000b),
    _RV32_2(0x101206, 0x1434),
    _RV32_2(0x101208, 0x1cbb),
    _RV32_2(0x10120a, 0x27b6),
    _RV32_2(0x10120c, 0xb6c8),
#if (ENABLE_MSTAR_TITANIA_MMAP_128MB == 1)    
    _RV32_2(0x10120e, 0x4060),
#elif (ENABLE_MSTAR_TITANIA_MMAP_256MB == 1)
    _RV32_2(0x10120e, 0x4080),
#else
    #error  "Invalid DRAM MMAP"
#endif
    _RV32_2(0x101210, 0x1c70),
    _RV32_2(0x101212, 0x4004),
    _RV32_2(0x101214, 0x8018),
    _RV32_2(0x101216, 0xc000),
    _RV32_2(0x110d54, 0x0000),
    _RV32_2(0x110d00, 0x0018),
    _RV32_2(0x110d04, 0x0080),
#if (ENABLE_NANYA_DRAM_EMBEDDED == 1)    
    _RV32_2(0x110d38, 0x0066),
    _RV32_2(0x110d3a, 0x0000),
#elif (ENABLE_WB_DRAM_EMBEDDED == 1)    
    _RV32_2(0x110d38, 0x0056),
    _RV32_2(0x110d3a, 0x3030),
#else
    #error  "Invalid DRAM Manufacturer"
#endif
    _RV32_2(0x110d02, 0x0000),
    _RV32_2(0x110d3c, 0x1177),
    _RV32_2(0x110d3e, 0x1011),
    _RV32_2(0x110d50, 0x1111),
    _RV32_2(0x110d52, 0x0000),
    _RV32_2(0x110d0e, 0x00c5),
    _RV32_2(0x110d0e, 0x00a5),
#if (ENABLE_NANYA_DRAM_EMBEDDED == 1)        
    _RV32_2(0x110d6e, 0x5566),
#elif (ENABLE_WB_DRAM_EMBEDDED == 1)
    _RV32_2(0x110d6e, 0x4444),
#else
    #error  "Invalid DRAM Manufacturer"
#endif
    _RV32_2(0x110d6a, 0x0124),
    _RV32_2(0x110d68, 0x0124),
    _RV32_2(0x110d54, 0xc000),

    _END_OF_TBL32_,
};


#endif  //ENABLE_MSTAR_BD_MST057B_10AYFT_13443

#endif /* _MIU_MST057B_10AYFT_13443_H_ */
