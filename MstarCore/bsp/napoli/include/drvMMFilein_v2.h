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
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  File name: mmfi.h
//  Description: MMFilein (MMFI) driver header file
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _MMFI_H_
#define _MMFI_H_

#ifdef __cplusplus
extern "C"
{
#endif

enum {
    MDrv_CMD_MMFI_Init,
    MDrv_CMD_MMFI_Exit,

    MDrv_CMD_MMFI_Set_DbgLevel,
    MDrv_CMD_MMFI_Set_Path,
    MDrv_CMD_MMFI_Set_Timer,
    MDrv_CMD_MMFI_ByteTimer_En,

    MDrv_CMD_MMFI_PidFlt_Alloc,
    MDrv_CMD_MMFI_PidFlt_Free,
    MDrv_CMD_MMFI_PidFlt_En,
    MDrv_CMD_MMFI_PidFlt_Set_Pid,

    MDrv_CMD_MMFI_CmdQ_Reset,
    MDrv_CMD_MMFI_CmdQ_Fifo_Status,
    MDrv_CMD_MMFI_CmdQ_Get_Slot,

    MDrv_CMD_MMFI_Set_Lpcr2,
    MDrv_CMD_MMFI_Get_Lpcr2,
    MDrv_CMD_MMFI_Get_Filein_Timestamp,

    MDrv_CMD_MMFI_Set_Addr,
    MDrv_CMD_MMFI_Set_SIZE,
    MDrv_CMD_MMFI_Set_PktMode,
    MDrv_CMD_MMFI_192Mode_En,
    MDrv_CMD_MMFI_192BlockSchene_En,
    MDrv_CMD_MMFI_Set_TimestampClk,

    MDrv_CMD_MMFI_DupPkt_Skip,

    MDrv_CMD_MMFI_Get_State,
    MDrv_CMD_MMFI_Chk_Status,

    MDrv_CMD_MMFI_Start,
    MDrv_CMD_MMFI_Abort,
    MDrv_CMD_MMFI_ModeEnable,

    MDrv_CMD_MMFI_ResetAll,
    MDrv_CMD_MMFI_GetCap,
    MDrv_CMD_MMFI_RemoveAVDupPkt,

    MDrv_CMD_MMFI_MobfSetKey,
} eMmfiIoctlOpt;


typedef struct _MMFI_BOOL_PARAM
{
    DrvMMFI_Path    epath;
    MS_BOOL         bEnabled;
}MMFI_BOOL_PARAM, *PMMFI_BOOL_PARAM;

typedef struct _MMFI_U8_PARAM
{
    DrvMMFI_Path    epath;
    MS_U8           u8Value;
}MMFI_U8_PARAM, *PMMFI_U8_PARAM;

typedef struct _MMFI_U8PTR_PARAM
{
    DrvMMFI_Path    epath;
    MS_U8*          pu8Value;
}MMFI_U8PTR_PARAM, *PMMFI_U8PTR_PARAM;

typedef struct _MMFI_FLT_EN_PARAM
{
    DrvMMFI_Path    epath;
    MS_U8           u8FltId;
    MS_BOOL         bEnabled;
}MMFI_FLT_EN_PARAM, *PMMFI_FLT_EN_PARAM;

typedef struct _MMFI_FLT_PID_PARAM
{
    DrvMMFI_Path    epath;
    MS_U8           u8FltId;
    MS_U16          u16Pid;
}MMFI_FLT_PID_PARAM, *PMMFI_FLT_PID_PARAM;

typedef struct _MMFI_U32PTR_PARAM
{
    DrvMMFI_Path     epath;
    MS_U32*          pu32Value;
}MMFI_U32PTR_PARAM, *PMMFI_U32PTR_PARAM;

typedef struct _MMFI_U32_PARAM
{
    DrvMMFI_Path     epath;
    MS_U32           u32Value;
}MMFI_U32_PARAM, *PMMFI_U32_PARAM;

typedef struct _MMFI_PKTMODE_PARAM
{
    DrvMMFI_Path                epath;
    DrvMMFI_PacketMode          emode;
}MMFI_PKTMODE_PARAM, *PMMFI_PKTMODE_PARAM;

typedef struct _MMFI_FI_STATE_PARAM
{
    DrvMMFI_Path                epath;
    DrvMMFI_FileinState*        peFileinState;
}MMFI_FI_STATE_PARAM, *PMMFI_FI_STATE_PARAM;

typedef struct _MMFI_STATUS_PARAM
{
    DrvMMFI_Path                epath;
    DrvMMFI_Status*             pStatus;
}MMFI_STATUS_PARAM, *PMMFI_STATUS_PARAM;

typedef struct _MMFI_MODE_EN_PARAM
{
    DrvMMFI_Path                epath;
    DrvMMFI_FileinMode          efileinmode;
    MS_BOOL                     bEnabled;
}MMFI_MODE_EN_PARAM, *PMMFI_MODE_EN_PARAM;

typedef struct _MMFI_CAP_PARAM
{
    DrvMMFI_Cap             eCap;
    void*                   pOutput;
}MMFI_CAP_PARAM, *PMMFI_CAP_PARAM;

typedef struct _MMFI_REM_AVFIFO_DUPPKT_PARAM
{
    DrvMMFI_Path            epath;
    DrvMMFI_FltType         eFifoType;
    MS_BOOL                 bEnabled;
}MMFI_REM_AVFIFO_DUPPKT_PARAM, *PMMFI_REM_AVFIFO_DUPPKT_PARAM;


#ifdef __cplusplus
}
#endif

#endif //_MMFI_H_


