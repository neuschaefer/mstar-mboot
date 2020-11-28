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
// ( ß¡±MStar Confidential Information ßÆØ) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#include "compiler.h"
#include "hwreg.h"
#include "datatype.h"
#include "drvGlobal.h"

#define ASSERT(expr)

const char g_str_assert[] = "ASSERT: %s %d\n";

U8 __MDrv_ReadByte( U32 u32Reg )
{
    return RIU8[(u32Reg << 1) - (u32Reg & 1)];
}

U16 __MDrv_Read2Byte( U32 u32Reg )
{
    if (__unlikely(u32Reg & 0x01))
    {
        u32Reg <<= 1;
        return RIU8[u32Reg - 1] + (RIU8[u32Reg + 2] << 8);
    }
    else
    {
        return RIU[u32Reg];
    }
}

U32 __MDrv_Read3Byte( U32 u32Reg )
{
    if (__unlikely(u32Reg & 0x01))
    {
        return (RIU8[(u32Reg << 1) - 1] + (RIU[u32Reg + 1] << 8));
    }
    else
    {
        return (RIU[u32Reg] + (RIU8[(u32Reg + 2) << 1] << 16));
    }
}

U32 __MDrv_Read4Byte( U32 u32Reg )
{
    if (__unlikely(u32Reg & 0x01))
    {
        return (RIU8[(u32Reg << 1) - 1] + (RIU[u32Reg + 1] << 8) + (RIU8[(u32Reg + 3) << 1] << 24));
    }
    else
    {
        return (RIU[u32Reg] + (RIU[u32Reg + 2] << 16));
    }
}

void __MDrv_WriteByte( U32 u32Reg, U8 u8Value )
{
    RIU8[(u32Reg << 1) - (u32Reg & 1)] = u8Value;
}

void __MDrv_Write2Byte( U32 u32Reg, U16 u16Value )
{
    if (__unlikely(u32Reg & 0x01))
    {
        RIU8[(u32Reg << 1) - 1] = (U8)((u16Value));
        RIU8[(u32Reg + 1) << 1] = (U8)((u16Value) >> 8);
    }
    else
    {
        RIU[u32Reg] = u16Value;
    }
}

void __MDrv_Write3Byte( U32 u32Reg, U32 u32Value )
{
    if (__unlikely(u32Reg & 0x01))
    {
        RIU8[(u32Reg << 1) - 1] = u32Value;
        RIU[u32Reg + 1] = (u32Value >> 8);
    }
    else
    {
        RIU[u32Reg] = u32Value;
        RIU8[(u32Reg + 2) << 1] = (u32Value >> 16);
    }
}

void __MDrv_Write4Byte( U32 u32Reg, U32 u32Value )
{
    if (__unlikely(u32Reg & 0x01))
    {
        RIU8[(u32Reg << 1) - 1] = u32Value;
        RIU[u32Reg + 1] = (u32Value >> 8);
        RIU8[((u32Reg + 3) << 1)] = (u32Value >> 24);
    }
    else
    {
        RIU[u32Reg] = u32Value;
        RIU[u32Reg + 2] = (u32Value >> 16);
    }
}

void MDrv_WriteRegTbl( const MS_REG_INIT * pRegTable )
{
    U8 u8Length;
    U16 u16Index; // register index
    U16 u16Dummy;

    u16Dummy = 2000;

    do
    {
        u16Index = ((pRegTable[0] << 8) + pRegTable[1]);
        if (u16Index == 0xFFFF) // check end of table
            break;

        u8Length = u16Index >> 14;
        u16Index &= 0x3FFF;

        switch ( u8Length )
        {
        case 3:
            MDrv_Write4Byte( u16Index, pRegTable[2] +
                                      (pRegTable[3] << 8) +
                                      (pRegTable[4] << 16) +
                                      (pRegTable[5] << 24) );
            pRegTable += 6;
            break;

        case 2:
            MDrv_Write3Byte( u16Index, pRegTable[2] +
                                      (pRegTable[3] << 8) +
                                      (pRegTable[4] << 16) );
            pRegTable += 5;
            break;

        case 1:
            MDrv_Write2Byte( u16Index, pRegTable[2] +
                                      (pRegTable[3] << 8) );
            pRegTable += 4;
            break;

        case 0:
            MDrv_WriteByte( u16Index, pRegTable[2] );
            pRegTable += 3;
            break;
        default:
            ASSERT(0);
            break;
        }
    } while (--u16Dummy > 0);
}


//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void MDrv_WriteRegTbl_32( const MS_REG_INIT * pRegTable )
{
    U8 u8Length;
    U32 u32Index; // register index
    U16 u16Dummy;

    u16Dummy = 2000;

    do
    {
        u32Index = (((U32)pRegTable[0] << 16) + ((U32)pRegTable[1] << 8) + pRegTable[2] );
        if (u32Index == 0xFFFFFF) // check end of table
            break;

        u8Length = pRegTable[0]>>5;  //u32Index >> 21;
        u32Index &= 0x1FFFFF;

        switch ( u8Length )
        {
        case 3:
            MDrv_Write4Byte( u32Index, pRegTable[3] +
                                      (pRegTable[4] << 8) +
                                      (pRegTable[5] << 16) +
                                      (pRegTable[6] << 24) );
            pRegTable += 7;
            break;

        case 2:
            MDrv_Write3Byte( u32Index, pRegTable[3] +
                                      (pRegTable[4] << 8) +
                                      (pRegTable[5] << 16) );
            pRegTable += 6;
            break;

        case 1:
            MDrv_Write2Byte( u32Index, pRegTable[3] +
                                      (pRegTable[4] << 8) );
            pRegTable += 5;
            break;

        case 0:
            MDrv_WriteByte( u32Index, pRegTable[3] );
            pRegTable += 4;
            break;
        default:
            ASSERT(0);
            break;
        }
    } while (--u16Dummy > 0);
}



