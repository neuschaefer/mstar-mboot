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
////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVBDMA_PRIV_H_
#define _DRVBDMA_PRIV_H_

////////////////////////////////////////////////////////////////////////////////
/// @file drvBDMA.h
/// @author MStar Semiconductor Inc.
/// @brief Byte DMA control driver
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"
#include "drvBDMA.h"

typedef MS_U32 (*IOCTL_BDMA_MEMCPY)(MS_PHYADDR, MS_PHYADDR, MS_U32);
typedef MS_U32 (*IOCTL_BDMA_SEARCH)(MS_PHYADDR, MS_U32, MS_U32, MS_U32, BDMA_SrcDev);
typedef MS_U32 (*IOCTL_BDMA_CRC32)(MS_PHYADDR, MS_U32, MS_U32, MS_U32, BDMA_SrcDev, MS_BOOL);
typedef MS_U32 (*IOCTL_BDMA_PATTERN_FILL)(MS_PHYADDR, MS_U32, MS_U32, BDMA_DstDev);
typedef MS_U32 (*IOCTL_BDMA_FLASHCOPY2DRAM)(MS_PHYADDR, MS_PHYADDR, MS_U32);
#ifdef MOBF_ENABLE
typedef MS_U32 (*IOCTL_BDMA_MOBFSEARCH)(MS_PHYADDR, MS_U32, BDMA_MOBF_PS*, BDMA_SrcDev);
#endif
typedef void (*IOCTL_BDMA_GETSTATUS)(BDMA_Status*);
typedef BDMA_Info* (*IOCTL_BDMA_GETINFO)(void);
typedef BDMA_Result (*IOCTL_BDMA_GETLIBVER)(const MSIF_Version **);
typedef MS_U32 (*IOCTL_BDMA_GETMINSIZE)(void);
typedef BDMA_Result (*IOCTL_BDMA_SETDBGLEVEL)(BDMA_DbgLv);
typedef void (*IOCTL_BDMA_SETSPIOFFSETFORMCU)(void);
typedef BDMA_Result (*IOCTL_BDMA_WAITFLASHDONE)(void);

typedef struct _BDMA_RESOURCE_PRIVATE
{
    MS_U32 Dummy;
}BDMA_RESOURCE_PRIVATE;

typedef struct _BDMA_INSTANT_PRIVATE
{
    IOCTL_BDMA_MEMCPY           fpBDMAMemCpy;
    IOCTL_BDMA_SEARCH           fpBDMASearch;
    IOCTL_BDMA_CRC32            fpBDMACRC32;
    IOCTL_BDMA_PATTERN_FILL     fpBDMAPatternFill;
    IOCTL_BDMA_FLASHCOPY2DRAM   fpBDMAFlashCopy2Dram;
#ifdef MOBF_ENABLE
    IOCTL_BDMA_MOBFSEARCH       fpBDMAMOBFSearch;
#endif
    IOCTL_BDMA_GETSTATUS        fpBDMAGetStatus;
    IOCTL_BDMA_GETINFO              fpBDMAGetInfo;
    IOCTL_BDMA_GETLIBVER            fpBDMAGetLibVer;
    IOCTL_BDMA_GETMINSIZE           fpBDMAGetMinSize;
    IOCTL_BDMA_SETDBGLEVEL          fpBDMASetDbgLevel;
    IOCTL_BDMA_SETSPIOFFSETFORMCU   fpBDMASetSPIOffsetForMCU;
    IOCTL_BDMA_WAITFLASHDONE        fpBDMAWaitFlashDone;
}BDMA_INSTANT_PRIVATE;

void BDMARegisterToUtopia(FUtopiaOpen ModuleType);
MS_U32 BDMAOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
MS_U32 BDMAClose(void* pInstance);
MS_U32 BDMAIoctl(void* pInstance, MS_U32 u32Cmd, void* pArgs);

BDMA_Result _MDrv_BDMA_MemCopy(MS_PHYADDR u32SrcAddr, MS_PHYADDR u32DstAddr, MS_U32 u32Len);
MS_U32 _MDrv_BDMA_Search(MS_PHYADDR u32Addr, MS_U32 u32Len, MS_U32 u32Pattern, MS_U32 u32ExcluBit, BDMA_SrcDev eDev);
MS_U32 _MDrv_BDMA_CRC32(MS_PHYADDR u32Addr, MS_U32 u32Len, MS_U32 u32Poly, MS_U32 u32Seed, BDMA_SrcDev eDev, MS_BOOL bReflect);
BDMA_Result _MDrv_BDMA_PatternFill(MS_PHYADDR u32Addr, MS_U32 u32Len, MS_U32 u32Pattern, BDMA_DstDev eDev);
BDMA_Result _MDrv_BDMA_FlashCopy2Dram(MS_PHYADDR u32FlashAddr, MS_PHYADDR u32DramAddr, MS_U32 u32Len);
#ifdef MOBF_ENABLE
MS_U32 _MDrv_BDMA_MOBFSearch(MS_PHYADDR u32Addr, MS_U32 u32Len, BDMA_MOBF_PS* pMobfPsCfg, BDMA_SrcDev eDev);
#endif
void _MDrv_BDMA_GetStatus(BDMA_Status *pStatus);
void _MDrv_BDMA_SetSPIOffsetForMCU(void);
BDMA_Result _MDrv_BDMA_WaitFlashDone(void);

#ifdef __cplusplus
}
#endif
#endif // _DRVBDMA_PRIV_H_
