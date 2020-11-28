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
#ifndef __DRV_SEM_H__
#define __DRV_SEM_H__

#include "MsCommon.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define SEM_DRV_VERSION                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    {'S','E','M','_'},                  /* IP__                                             */  \
    {'0','1'},                          /* 0.0 ~ Z.Z                                        */  \
    {'0','1'},                          /* 00 ~ 99                                          */  \
    {'0','0','2','6','4','8','8','5'},  /* CL#                                              */  \
    MSIF_OS

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define SEM_PM51_ID                    0x01
#define SEM_AEON_ID                    0x02
#define SEM_ARM_MIPS_ID                0x03

#if (defined(MCU_AEON))
    #define    SEM_RESOURCE_ID         SEM_AEON_ID
#else
    #define    SEM_RESOURCE_ID         SEM_ARM_MIPS_ID
#endif

#define SEM_WAIT_FOREVER               (0xffffff00)
#define SEM_ID_PREFIX                  (0x36970000)


//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------
typedef enum
{
    E_SEM_NONE = SEM_ID_PREFIX,
    E_SEM_DUMMY,
    E_SEM_GE0,
    E_SEM_GE1,
    E_SEM_BDMA,
    E_SEM_PM,
    E_SEM_MBX_RECV,
    E_SEM_MBX_SEND,
    E_SEM_TEE,
    E_SEM_USER0,
    E_SEM_USER1,
    E_SEM_USER2,
    E_SEM_USER3
}eSemId;

typedef enum _SEM_DbgLvl
{
    E_SEM_DBGLVL_NONE = 0,      /// no debug message
    E_SEM_DBGLVL_WARNING,       /// show warning only
    E_SEM_DBGLVL_ERROR,         /// show error only
    E_SEM_DBGLVL_INFO,          /// show error & informaiton
    E_SEM_DBGLVL_ALL,           /// show error, information & funciton name
}SEM_DbgLvl;

//-------------------------------------------------------------------------------------------------
// Extern Functions
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_SEM_Init(void);
MS_BOOL MDrv_SEM_Get_Resource(MS_U8 u8SemID, MS_U16 u16ResId);
MS_BOOL MDrv_SEM_Free_Resource(MS_U8 u8SemID, MS_U16 u16ResId);
MS_BOOL MDrv_SEM_Reset_Resource(MS_U8 u8SemID);
MS_BOOL MDrv_SEM_Get_ResourceID(MS_U8 u8SemID, MS_U16* pu16ResId);
MS_U32 MDrv_SEM_Get_Num(void);
MS_BOOL MDrv_SEM_GetLibVer(const MSIF_Version **ppVersion);
MS_U32 MDrv_SEM_SetPowerState(EN_POWER_MODE u16PowerState);
MS_BOOL MDrv_SEM_Lock(eSemId eSemId, MS_U32 u32WaitMs);
MS_BOOL MDrv_SEM_Unlock(eSemId eSemId);
MS_BOOL MDrv_SEM_Delete(eSemId eSemId);

//-------------------------------------------------------------------------------------------------
/// Set SEM debug function level.
/// @param eLevel \b IN: E_SEM_DBGLVL_NONE/E_SEM_DBGLVL_WARNING/E_SEM_DBGLVL_ERROR/E_SEM_DBGLVL_INFO/E_SEM_DBGLVL_ALL
/// @return TRUE: Success
/// @return other values: Failure
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_SEM_SetDbgLevel(SEM_DbgLvl eLevel);

//==============================================================================
// Semaphore Usage in Utopia
// See halSEM.c
//==============================================================================

#ifdef __cplusplus
} // closing brace for extern "C"
#endif

#endif // #ifndef __DRV_SEM_H__
