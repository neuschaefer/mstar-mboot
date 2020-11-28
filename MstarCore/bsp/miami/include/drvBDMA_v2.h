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
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
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

//////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvBDMA_v2.h
/// @brief  MIU Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_BDMA_V2_H_
#define _DRV_BDMA_V2_H_

#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
// below for utopia20 structure

typedef enum {
    MDrv_CMD_BDMA_MemCopy,
    MDrv_CMD_BDMA_Search,
    MDrv_CMD_BDMA_CRC32,
    MDrv_CMD_BDMA_Pattern_Fill,
    MDrv_CMD_BDMA_FlashCopy2Dram,
    MDrv_CMD_BDMA_MOBFSearch,
    MDrv_CMD_BDMA_GetStatus,
    MDrv_CMD_BDMA_GetInfo,
    MDrv_CMD_BDMA_GetLibVer,
    MDrv_CMD_BDMA_GetMinSize,
    MDrv_CMD_BDMA_SetDbgLevel,
    MDrv_CMD_BDMA_SetSPIOffsetForMCU,
    MDrv_CMD_BDMA_WaitFlashDone,
} eBdmaIoctlOpt;

//////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------
typedef struct _BDMA_API_V1
{
}BDMA_API_V1;

typedef struct _BDMA_API_V2
{
}BDMA_API_V2;

// below are for utopia20 cmd and parameters structure
// for cmd MDrv_CMD_BDMA_MemCopy
typedef struct _BDMA_MEMCOPY_PARAM
{
    MS_PHYADDR u32SrcAddr;
    MS_PHYADDR u32DstAddr;
    MS_U32 u32Len;
}BDMA_MEMCOPY_PARAM, *PBDMA_MEMCOPY_PARAM;

// for cmd MDrv_CMD_BDMA_Search
typedef struct _BDMA_SEARCH_PARAM
{
    MS_PHYADDR u32Addr;
    MS_U32 u32Len;
    MS_U32 u32Pattern;
    MS_U32 u32ExcluBit;
    BDMA_SrcDev eDev;
    MS_U32* pSearchAddr;
}BDMA_SEARCH_PARAM, *PBDMA_SEARCH_PARAM;

// for cmd MDrv_CMD_BDMA_CRC32
typedef struct _BDMA_CRC32_PARAM
{
    MS_PHYADDR u32Addr;
    MS_U32 u32Len;
    MS_U32 u32Poly;
    MS_U32 u32Seed;
    BDMA_SrcDev eDev;
    MS_BOOL bReflect;
    MS_U32 u32CRC32;
}BDMA_CRC32_PARAM, *PBDMA_CRC32_PARAM;

// for cmd MDrv_CMD_BDMA_Pattern_Fill
typedef struct _BDMA_PATTERN_FILL_PARAM
{
    MS_PHYADDR u32Addr;
    MS_U32 u32Len;
    MS_U32 u32Pattern;
    BDMA_DstDev eDev;
}BDMA_PATTERN_FILL_PARAM, *PBDMA_PATTERN_FILL_PARAM;

// for cmd MDrv_CMD_BDMA_FlashCopy2Dram
typedef struct _BDMA_FLASHCOPY2DRAM_PARAM
{
    MS_PHYADDR u32FlashAddr;
    MS_PHYADDR u32DramAddr;
    MS_U32 u32Len;
}BDMA_FLASHCOPY2DRAM_PARAM, *PBDMA_FLASHCOPY2DRAM_PARAM;

// for cmd MDrv_CMD_BDMA_MOBFSearch
#ifdef MOBF_ENABLE
typedef struct _BDMA_MOBFSEARCH_PARAM
{
    MS_PHYADDR u32Addr;
    MS_U32 u32Len;
    BDMA_MOBF_PS* pMobfPsCfg;
    BDMA_SrcDev eDev;
    MS_U32 u32SearchAddr;
}BDMA_MOBFSEARCH_PARAM, *PBDMA_MOBFSEARCH_PARAM;
#endif

// for cmd MDrv_CMD_BDMA_GetStatus
typedef struct _BDMA_GETSTATUS_PARAM
{
    BDMA_Status *pStatus;
}BDMA_GETSTATUS_PARAM, *PBDMA_GETSTATUS_PARAM;


// for cmd MDrv_CMD_BDMA_GetInfo
typedef struct _BDMA_GETINFO_PARAM
{
    MS_U8       u8ChNum;
    MS_U16      u16ChipVer;
    MS_U32      u32IOMap;
    MS_U32      u32MIU1Base;
    MS_S32      s32Mutex;
    MS_BOOL     bInit;
    BDMA_DbgLv  eDbgLv;
    BDMA_HwInfo sHwCap;
}BDMA_GETINFO_PARAM, *PBDMA_GETINFO_PARAM;

// for cmd MDrv_CMD_BDMA_GetLibVer
typedef struct _BDMA_GETLIBVER_PARAM
{
    const MSIF_Version **ppVersion;
}BDMA_GETLIBVER_PARAM, *PBDMA_GETLIBVER_PARAM;

// for cmd MDrv_CMD_BDMA_GetMinSize
typedef struct _BDMA_GETMINSIZE_PARAM
{
    MS_U32 u32MinSize;
}BDMA_GETMINSIZE_PARAM, *PBDMA_GETMINSIZE_PARAM;

// for cmd MDrv_CMD_BDMA_SetDbgLevel
typedef struct _BDMA_SETDBGLEVEL_PARAM
{
    BDMA_DbgLv eLevel;
}BDMA_SETDBGLEVEL_PARAM, *PBDMA_SETDBGLEVEL_PARAM;

//-------------------------------------------------------------------------------------------------
// Extern Global Variabls
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Extern Functions
//-------------------------------------------------------------------------------------------------

//////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#endif // _DRV_BDMA_V2_H_

