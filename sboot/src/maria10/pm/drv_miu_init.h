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

#ifndef __DDR2_INIT_H__
#define __DDR2_INIT_H__

#include "c_riubase.h"
#include "drvGlobal.h"

#define    _DRAM_SIZE_NO_LIMIT    0x00
#define    _DRAM_SIZE_2M          0x01
#define    _DRAM_SIZE_4M          0x02
#define    _DRAM_SIZE_8M          0x03
#define    _DRAM_SIZE_16M         0x04
#define    _DRAM_SIZE_32M         0x05
#define    _DRAM_SIZE_64M         0x06
#define    _DRAM_SIZE_128M        0x07
#define    _DRAM_SIZE_256M        0x07

#define    _DRAM_ON_BAORD         _DRAM_SIZE_NO_LIMIT

// A CMD + B DATA
#define MIU0_USE_MIU1_DATA (!CHIP_HAS_DDR_A_DATA && !CHIP_HAS_DDR_B_CMD)

#define DDR2_800MHz     0x01
#define DDR_400Mhz_2x   0x02

#if ((ENABLE_MSTAR_MARIA10_BD_MST109A_D01A_S) || (ENABLE_MSTAR_MARIA10_BD_MST109C_D01A_S) || (ENABLE_MSTAR_MARIA10_BD_MST109E_D01A_S))
#define MIU_SPEED       DDR2_800MHz
#elif ((ENABLE_MSTAR_MARIA10_BD_MST109D_D01A_S) || (ENABLE_MSTAR_MARIA10_BD_MST109F_D01A_S))
#define MIU_SPEED       DDR_400Mhz_2x
#else
#error "MIU interface isn't defined"
#endif

#if (CONFIG_MSTAR_MARIA10_PM==0)
static const MS_REG_INIT MIU_ATOP_Init[]=
{
    #if (MIU_SPEED == DDR2_800MHz)
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x3A ) , 0x0080),
      #if (ENABLE_MSTAR_MARIA10_BD_MST109C_D01A_S)
      _RV32_2( ( RIUBASE_MIU_ATOP + 0x36 ) , 0x4002),
      #else
      _RV32_2( ( RIUBASE_MIU_ATOP + 0x36 ) , 0x4004), // 0x4000 -> 0x4004
      #endif
    #elif (MIU_SPEED == DDR_400Mhz_2x)
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x3A ) , 0x0060),
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x24 ) , 0x0400),
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x36 ) , 0x4000),
    #else
    #error "MIU interface isn't defined"
    #endif

    _RV32_2( ( RIUBASE_MIU_ATOP + 0x34 ) , 0x0300),
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x30 ) , 0xd70a),
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x32 ) , 0x0033),   /*0x0033->0x002D 900MHz*/

    _END_OF_TBL32_
};

static const MS_REG_INIT MIU_DDR_Init[] =
{
    #if (MIU_SPEED == DDR2_800MHz)
    _RV32_2( 0x101202, 0x0292 ),   // 0x02a2 -> 0x0292
    _RV32_2( 0x101204, 0x008b ),
    _RV32_2( 0x101206, 0x0420 ),
    _RV32_2( 0x101208, 0x1666 ),
    _RV32_2( 0x10120a, 0x1c56 ),
    _RV32_2( 0x10120c, 0x5485 ),
    _RV32_2( 0x10120e, 0x2044 ),
    _RV32_2( 0x101210, 0x0a62 ),
    _RV32_2( 0x101212, 0x4004 ),
    _RV32_2( 0x101214, 0x8000 ),
    _RV32_2( 0x101216, 0xc000 ),

    _RV32_2( 0x110d00, 0x0011 ),
    _RV32_2( 0x110d02, 0xaaaa ),
    #if (ENABLE_MSTAR_MARIA10_BD_MST109C_D01A_S)
    _RV32_2( 0x110d38, 0x3377 ),
    #else
    _RV32_2( 0x110d38, 0x3366 ),  // 0x0033 -> 0x3366
    #endif
    _RV32_2( 0x110d3a, 0x0010 ),  // 0x0000 -> 0x0010
    _RV32_2( 0x110d3c, 0x2100 ),  // 0x2000 -> 0x2100
    _RV32_2( 0x110d3e, 0x0022 ),
    _RV32_2( 0x110d0e, 0x00e5 ),
    _RV32_2( 0x110d0e, 0x00a5 ),
    _RV32_2( 0x110d60, 0x2738 ),  // 0xA738 -> 0x2738
    #if (ENABLE_MSTAR_MARIA10_BD_MST109C_D01A_S)
    _RV32_2( 0x110d6e, 0x0044 ),
    #else
    _RV32_2( 0x110d6e, 0x0055 ),  // 0x0055 -> 0x0044
    #endif
    _RV32_2( 0x110d6a, 0x004f ),
    _RV32_2( 0x110d68, 0x004f ),
    _RV32_2( 0x110d72, 0x0007 ),  // new setting

    #elif (MIU_SPEED == DDR_400Mhz_2x)
    _RV32_2( 0x101202, 0x0151 ),
    _RV32_2( 0x101204, 0x008B ),  // 0x0089->0x008B0x008B
    _RV32_2( 0x101206, 0x0a60 ),  // 0x0a20->0x0a60
    _RV32_2( 0x101208, 0x0833 ),  // 0x1666->0x0833
    _RV32_2( 0x10120a, 0x0B52 ),  // 0x1c56->0x0B52
    _RV32_2( 0x10120c, 0x5231 ),  // 0x5481->0x5231
    _RV32_2( 0x10120e, 0x100C ),  // 0x2044->0x100C
    _RV32_2( 0x101210, 0x0032 ),  // 0x0a32->0x0032
    _RV32_2( 0x101212, 0x4004 ),
    _RV32_2( 0x101214, 0x8000 ),
    _RV32_2( 0x101216, 0xc000 ),

    _RV32_2( 0x110d00, 0x0100 ),  // 0x0010-> 0x0100
    _RV32_2( 0x110d14, 0x0100 ),
    _RV32_2( 0x110d02, 0xaaaa ),
    _RV32_2( 0x110d36, 0x4002 ),  // new
    _RV32_2( 0x110d38, 0x0033 ),
    _RV32_2( 0x110d3a, 0x0000 ),  // 0x00200->0x0060->0x0000
    _RV32_2( 0x110d3c, 0x0100 ),  // 0x0100->0x0000->0x0100
    _RV32_2( 0x110d3e, 0x0000 ),
    _RV32_2( 0x110d0e, 0x01a5 ),  // 0x00e5->0x01a5
    _RV32_2( 0x110d0e, 0x01a5 ),  // 0x00a5->0x01a5
    _RV32_2( 0x110d60, 0x2738 ),  // new feature
    _RV32_2( 0x110d6e, 0x0044 ),  // 0x0055->0x0044
    _RV32_2( 0x110d6a, 0x004f ),
    _RV32_2( 0x110d68, 0x004f ),
    _RV32_2( 0x110d72, 0x7807 ),  // new feature

    #else
    #error "MIU interface isn't defined"
    #endif

    _END_OF_TBL32_,
};
#endif

#endif /* __DDR2_INIT_H__ */
