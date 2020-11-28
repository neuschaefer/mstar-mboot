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
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvSEM_priv.h
/// @brief  SEM Driver Interface
/// @author MStar Semiconductor,Inc.
///
////////////////////////////////////////////////////////////////////////////////////////////////////



#ifndef _DRVSEM_PRIV_H_
#define _DRVSEM_PRIV_H_

#ifdef __cplusplus
extern "C"
{
#endif

// driver version
#define SEM_VERSION            0x00000001

enum {
    MDrv_CMD_SEM_Get_Resource,
    MDrv_CMD_SEM_Free_Resource,
    MDrv_CMD_SEM_Reset_Resource,
    MDrv_CMD_SEM_Get_ResourceID,
    MDrv_CMD_SEM_Get_Num,
    MDrv_CMD_SEM_GetLibVer,
    MDrv_CMD_SEM_Lock,
    MDrv_CMD_SEM_Unlock,
    MDrv_CMD_SEM_Delete,
} eSEMIoctlOpt;

//ioctl function pointer type
typedef MS_BOOL (*IOCTL_SEM_GETRESOURCE)(MS_U8, MS_U16);
typedef MS_BOOL (*IOCTL_SEM_FREERESOURCE)(MS_U8, MS_U16);
typedef MS_BOOL (*IOCTL_SEM_RESETRESOURCE)(MS_U8);
typedef MS_BOOL (*IOCTL_SEM_GETRESOURCEID)(MS_U8, MS_U16*);
typedef MS_U32 (*IOCTL_SEM_GETNUM)(void);
typedef MS_BOOL (*IOCTL_SEM_GETLIBVER)(const MSIF_Version **);
typedef MS_BOOL (*IOCTL_SEM_LOCK)(MS_U32, MS_U32);
typedef MS_BOOL (*IOCTL_SEM_UNLOCK)(MS_U32);
typedef MS_BOOL (*IOCTL_SEM_DELETE)(MS_U32);

// INSTANCE Private(ioctl function pointer)
typedef struct _SEM_INSTANT_PRIVATE
{
    IOCTL_SEM_GETRESOURCE       fpSEMGetResource;
    IOCTL_SEM_FREERESOURCE      fpSEMFreeResource;
    IOCTL_SEM_RESETRESOURCE     fpSEMResetResource;
    IOCTL_SEM_GETRESOURCEID     fpSEMGetResourceID;
    IOCTL_SEM_GETNUM            fpSEMGetNum;
    IOCTL_SEM_GETLIBVER         fpSEMGetLibVer;
    IOCTL_SEM_LOCK              fpSEMLock;
    IOCTL_SEM_UNLOCK            fpSEMUnlock;
    IOCTL_SEM_DELETE            fpSEMDelete;
}SEM_INSTANT_PRIVATE;

//////////////////////////////////////
// function parameter structure //////
//////////////////////////////////////
// for cmd MDrv_SEM_Get_Resource 
typedef struct _SEM_GETRESOURCE_PARAM
{
    MS_U8 u8SemID;
    MS_U16 u16ResId;
}SEM_GETRESOURCE_PARAM, *PSEM_GETRESOURCE_PARAM;

// for cmd MDrv_SEM_Free_Resource
typedef struct _SEM_FREERESOURCE_PARAM
{
    MS_U8 u8SemID;
    MS_U16 u16ResId;
}SEM_FREERESOURCE_PARAM, *PSEM_FREERESOURCE_PARAM;

// for cmd MDrv_SEM_Reset_Resource 
typedef struct _SEM_RESETRESOURCE_PARAM
{
    MS_U8 u8SemID;
}SEM_RESETRESOURCE_PARAM, *PSEM_RESETRESOURCE_PARAM;

// for cmd MDrv_SEM_Get_ResourceID
typedef struct _SEM_GETRESOURCEID_PARAM
{
    MS_U8 u8SemID;
    MS_U16* pu16ResId;
}SEM_GETRESOURCEID_PARAM, *PSEM_GETRESOURCEID_PARAM;

// for cmd MDrv_SEM_GetLibVer
typedef struct _SEM_GETLIBVER_PARAM
{
    const MSIF_Version **ppVersion;
}SEM_GETLIBVER_PARAM, *PSEM_GETLIBVER_PARAM;

// for cmd MDrv_SEM_Lock
typedef struct _SEM_LOCK_PARAM
{
    MS_U32 u32SemID;
    MS_U32 u32WaitMs;
}SEM_LOCK_PARAM, *PSEM_LOCK_PARAM;

// for cmd MDrv_SEM_Unlock
typedef struct _SEM_UNLOCK_PARAM
{
    MS_U32 u32SemID;
}SEM_UNLOCK_PARAM, *PSEM_UNLOCK_PARAM;

// for cmd MDrv_SEM_Delete
typedef struct _SEM_DELETE_PARAM
{
    MS_U32 u32SemID;
}SEM_DELETE_PARAM, *PSEM_DELETE_PARAM;

//////////////////////////////////////
// function for utopia2.0 ////////////
//////////////////////////////////////
void SEMRegisterToUtopia(void);
MS_U32 SEMOpen(void** pInstance, MS_U32 u32ModuleVersion, void* pAttribute);
MS_U32 SEMClose(void* pInstance);
MS_U32 SEMIoctl(void* pInstance, MS_U32 u32Cmd, void *pArgs);


// Resource_Private
typedef struct _SEM_RESOURCE_PRIVATE
{
    MS_U32 Dummy;
}SEM_RESOURCE_PRIVATE;

#ifdef __cplusplus
}
#endif

#endif // _DRVSEM_PRIV_H_
