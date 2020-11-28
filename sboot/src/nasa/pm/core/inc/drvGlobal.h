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
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef DRV_GLOBAL_H
#define DRV_GLOBAL_H

#include "datatype.h"

/********************************************************************************/
/*                           BDMA definition                                              */
/********************************************************************************/
//---------------------------------------
//add  for T3

#define     DW_1BYTE	                           0x00
#define     DW_2BYTE	                           0x10
#define     DW_4BYTE	                           0x20
#define     DW_8BYTE	                           0x30
#define     DW_16BYTE	                    0x40
//-----------------------------------------

/********************************************************************************/
/*                           Macro                                              */
/********************************************************************************/

typedef U8 MS_REG_INIT;

#define _RV1(addr, value)   (((addr) >> 8) & 0x3F), (U8)(addr), (U8)(value)
#define _RV2(addr, value)   0x40 + _RV1(addr, value), (U8)((value) >> 8)
#define _RV3(addr, value)   0x40 + _RV2(addr, value), (U8)((value) >> 16)
#define _RV4(addr, value)   0x40 + _RV3(addr, value), (U8)((value) >> 24)


#define _RV32_1(addr, value)    (U8)(((addr) >> 16) & 0xFF),(U8)(((addr) >> 8) & 0xFF), (U8)(addr), (U8)(value)
#define _RV32_2(addr, value)   0x20 + _RV32_1(addr, value), (U8)((value) >> 8)
#define _RV32_3(addr, value)   0x20 + _RV32_2(addr, value), (U8)((value) >> 16)
#define _RV32_4(addr, value)   0x20 + _RV32_3(addr, value), (U8)((value) >> 24)
#define _END_OF_TBL32_         0xFF, 0xFF, 0xFF


#define _RVM1(addr, value, mask) (((addr) >> 8) & 0x3F), (U8)(addr), (U8)(value), (U8)(mask)
#define _RVM2(addr, value, mask) 0x40 + _RVM1(addr, value, mask), (U8)((value) >> 8), (U8)((mask) >> 8)
#define _RVM3(addr, value, mask) 0x40 + _RVM2(addr, value, mask), (U8)((value) >> 16), (U8)((mask) >> 16)
#define _RVM4(addr, value, mask) 0x40 + _RVM3(addr, value, mask), (U8)((value) >> 24), (U8)((mask) >> 24)

#define _END_OF_TBL2_       0xFF, 0xFF

/******************************************************************************/
/*                   Function Prototypes                                      */
/******************************************************************************/

#ifdef DRV_GLOBAL_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define MDrv_ReadByte( u32Reg )                                                         \
    (__builtin_constant_p( u32Reg ) ?                                                   \
        (((u32Reg) & 0x01) ? RIU8[(u32Reg) * 2 - 1] : RIU8[(u32Reg) * 2]) :             \
        __MDrv_ReadByte( u32Reg ))

#define MDrv_Read2Byte( u32Reg )                                                        \
    (__builtin_constant_p( u32Reg ) && !((u32Reg) & 0x01) ?                             \
        RIU[u32Reg] : __MDrv_Read2Byte( u32Reg ))

#define MDrv_Read3Byte( u32Reg )    __MDrv_Read3Byte( u32Reg )

#define MDrv_Read4Byte( u32Reg )                                                        \
    ({                                                                                  \
    U32 value;                                                                          \
    if ( __builtin_constant_p( u32Reg ) && !((u32Reg) & 0x01) )                         \
    {                                                                                   \
        value = ((U32)RIU[(u32Reg) + 2] << 16) | RIU[u32Reg];                           \
    }                                                                                   \
    else                                                                                \
    {                                                                                   \
        value = __MDrv_Read4Byte( u32Reg );                                             \
    }                                                                                   \
    value;                                                                              \
    })

#define MDrv_ReadRegBit( u32Reg, u8Mask )                                               \
        (RIU8[(u32Reg) * 2 - ((u32Reg) & 1)] & (u8Mask))

#define MDrv_WriteRegBit( u32Reg, bEnable, u8Mask )                                     \
    MST_MACRO_START                                                                     \
    U32 u32Reg8 = ((u32Reg) * 2) - ((u32Reg) & 1);                                      \
    RIU8[u32Reg8] = (bEnable) ? (RIU8[u32Reg8] |  (u8Mask)) :                           \
                                (RIU8[u32Reg8] & ~(u8Mask));                            \
    MST_MACRO_END

#define MDrv_WriteByte( u32Reg, u8Val )                                                 \
    MST_MACRO_START                                                                     \
    if ( __builtin_constant_p( u32Reg ) )                                               \
    {                                                                                   \
        RIU8[((u32Reg) * 2) - ((u32Reg) & 1)] = u8Val;                                  \
    }                                                                                   \
    else                                                                                \
    {                                                                                   \
        __MDrv_WriteByte( u32Reg, u8Val );                                              \
    }                                                                                   \
    MST_MACRO_END

#define MDrv_Write2Byte( u32Reg, u16Val )                                               \
    MST_MACRO_START                                                                     \
    if ( __builtin_constant_p( u32Reg ) )                                               \
    {                                                                                   \
        if ( ((u32Reg) & 0x01) )                                                        \
        {                                                                               \
            RIU8[((u32Reg) * 2) - 1] = (U8)((u16Val));                                  \
            RIU8[((u32Reg) + 1) * 2] = (U8)((u16Val) >> 8);                             \
        }                                                                               \
        else                                                                            \
        {                                                                               \
            RIU[u32Reg] = u16Val;                                                       \
        }                                                                               \
    }                                                                                   \
    else                                                                                \
    {                                                                                   \
        __MDrv_Write2Byte( u32Reg, u16Val );                                            \
    }                                                                                   \
    MST_MACRO_END

#define MDrv_Write3Byte( u32Reg, u32Val )   __MDrv_Write3Byte( u32Reg, u32Val )

#define MDrv_Write4Byte( u32Reg, u32Val )                                               \
    MST_MACRO_START                                                                     \
    if ( __builtin_constant_p( u32Reg ) && !((u32Reg) & 0x01) )                         \
    {                                                                                   \
        RIU[u32Reg] = (U16)(u32Val);                                                    \
        RIU[(u32Reg) + 2] = (U16)((u32Val) >> 16);                                      \
    }                                                                                   \
    else                                                                                \
    {                                                                                   \
        __MDrv_Write4Byte( u32Reg, u32Val );                                            \
    }                                                                                   \
    MST_MACRO_END

#define MDrv_WriteByteMask( u32Reg, u8Val, u8Msk )                                      \
    MST_MACRO_START                                                                     \
    U32 u32Reg8 = ((u32Reg) * 2) - ((u32Reg) & 1);                                      \
    RIU8[u32Reg8] = (RIU8[u32Reg8] & ~(u8Msk)) | ((u8Val) & (u8Msk));                   \
    MST_MACRO_END

INTERFACE U8   __MDrv_ReadByte( U32 u32Reg );
INTERFACE U16  __MDrv_Read2Byte( U32 u32Reg );
INTERFACE U32  __MDrv_Read3Byte( U32 u32Reg );
INTERFACE U32  __MDrv_Read4Byte( U32 u32Reg );

INTERFACE void __MDrv_WriteByte( U32 u32Reg, U8 u8Val );
INTERFACE void __MDrv_Write2Byte( U32 u32Reg, U16 u16Val );
INTERFACE void __MDrv_Write3Byte( U32 u32Reg, U32 u32Val );
INTERFACE void __MDrv_Write4Byte( U32 u32Reg, U32 u32Val );

INTERFACE void MDrv_WriteRegTbl ( const MS_REG_INIT *pRegTable );
INTERFACE void MDrv_WriteRegTbl_32 ( const MS_REG_INIT *pRegTable );

#define MDrv_WriteRegTbl2( pRegTable )  MDrv_WriteRegTbl( pRegTable )

#undef INTERFACE

#endif /* DRV_GLOBAL_H */
