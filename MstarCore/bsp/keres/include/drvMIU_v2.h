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
/// @file   drvMIU_v2.h
/// @brief  MIU Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_MIU_V2_H_
#define _DRV_MIU_V2_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
typedef enum _eMIUIoctlCmd
{
    MDrv_CMD_MIU_Init,
    MDrv_CMD_MIU_Mask_Req_OPM_R,
    MDrv_CMD_MIU_Mask_Req_DNRB_R,
    MDrv_CMD_MIU_Mask_Req_DNRB_W,
    MDrv_CMD_MIU_Mask_Req_DNRB_RW,
    MDrv_CMD_MIU_Mask_Req_SC_RW,
    MDrv_CMD_MIU_Mask_Req_MVOP_R,
    MDrv_CMD_MIU_Mask_Req_MVD_R,
    MDrv_CMD_MIU_Mask_Req_MVD_W,
    MDrv_CMD_MIU_Mask_Req_MVD_RW,
    MDrv_CMD_MIU_Mask_Req_AUDIO_RW,
    MDrv_CMD_MIU_Mask_Req,
    MDrv_CMD_MIU_UnMask_Req,
    MDrv_CMD_MIU_SetSsc,
    MDrv_CMD_MIU_SetSscValue,
    MDrv_CMD_MIU_Protect,
    MDrv_CMD_MIU_SelMIU,
    MDrv_CMD_MIU_GetProtectInfo,
    MDrv_CMD_MIU_SetGroupPriority,
    MDrv_CMD_MIU_SetHighPriority,

}eMIUIoctlCmd;

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Extern Global Variabls
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Extern Functions
//-------------------------------------------------------------------------------------------------

//////////////////////////////////////////////////////////////
// below are for utopia20 cmd and parameters structure
// for below cmds
// MDrv_CMD_MIU_Mask_Req_OPM_R,
// MDrv_CMD_MIU_Mask_Req_DNRB_R,
// MDrv_CMD_MIU_Mask_Req_DNRB_W,
// MDrv_CMD_MIU_Mask_Req_DNRB_RW,
// MDrv_CMD_MIU_Mask_Req_SC_RW,
// MDrv_CMD_MIU_Mask_Req_MVOP_R,
// MDrv_CMD_MIU_Mask_Req_MVD_R,
// MDrv_CMD_MIU_Mask_Req_MVD_W,
// MDrv_CMD_MIU_Mask_Req_MVD_RW,
// MDrv_CMD_MIU_Mask_Req_AUDIO_RW,
typedef struct _MIU_MASK
{
    MS_U8 u8Mask;
    MS_U8 u8Miu;
}MIU_MIU_MASK, *PMIU_MIU_MASK;

// for below cmds MDrv_CMD_MIU_Mask_Req, MDrv_CMD_MIU_UnMask_Req
typedef struct _MIU_MIUREQ_MASK
{
    MS_U8 u8Miu;
    eMIUClientID eClientID;
}MIU_MIUREQ_MASK, *PMIU_MIUREQ_MASK;

// for below cmds MDrv_CMD_MIU_SetSsc
typedef struct _MIU_SET_SSC
{
    MS_U16 u16Fmodulation;
    MS_U16 u16FDeviation;
    MS_BOOL bEnable;
}MIU_SET_SSC, *PMIU_SET_SSC;

// for below cmds MDrv_CMD_MIU_SetSscValue
typedef struct _MIU_SET_SSCVALUE
{
    MS_U8 u8MiuDev;
    MS_U16 u16Fmodulation;
    MS_U16 u16FDeviation;
    MS_BOOL bEnable;
}MIU_SET_SSCVALUE, *PMIU_SET_SSCVALUE;

// for below cmds MDrv_CMD_MIU_Protect
typedef struct _MIU_PROTECT
{
    MS_U8 u8Blockx;
    MS_U8 *pu8ProtectId;
    MS_U32 u32Start;
    MS_U32 u32End;
    MS_BOOL bSetFlag;
}MIU_PROTECT, *PMIU_PROTECT;

// for below cmds MDrv_CMD_MIU_SelMIU
typedef struct _MIU_SELMIU
{
    eMIUClientID eClientID;
    eMIU_SelType eType;
}MIU_SELMIU, *PMIU_SELMIU;

// for below cmds MDrv_CMD_MIU_GetProtectInfo
typedef struct _MIU_GETPROTECTINFO
{
    MS_U8 u8MiuDev;
    MIU_PortectInfo *pInfo;
}MIU_GETPROTECTINFO, *PMIU_GETPROTECTINFO;

// for below cmds MDrv_CMD_MIU_SetGroupPriority
typedef struct _MIU_SETGROUPPRIORITY
{
    MS_U8 u8MiuDev;
    MIU_GroupPriority sPriority;
}MIU_SETGROUPPRIORITY, *PMIU_SETGROUPPRIORITY;


// for below cmds MDrv_CMD_MIU_SetHighPriority
typedef struct _MIU_SETHIGHPRIORITY
{
    MS_U8 u8MiuDev;
    eMIUClientID eClientID;
    MS_BOOL bMask;
}MIU_SETHIGHPRIORITY, *PMIU_SETHIGHPRIORITY;

#ifdef __cplusplus
}
#endif

#endif // _DRV_MIU_V2_H_

