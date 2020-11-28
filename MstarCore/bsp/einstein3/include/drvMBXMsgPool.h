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


///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file   drvMBXMsgPool.h
/// @brief  MStar Mailbox msg pool Driver DDI
/// @author MStar Semiconductor Inc.
/// @attention
/// <b>(OBSOLETED) <em>legacy interface is only used by MStar proprietary Mail Message communication\n
/// It's API level for backward compatible and will be remove in the next version.\n
/// Please refer @ref drvGE.h for future compatibility.</em></b>
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_MBX_MSGPOOL_H
#define _DRV_MBX_MSGPOOL_H

#ifdef _DRV_MBX__MSGPOOL_C
#define INTERFACE
#else
#define INTERFACE extern
#endif



#ifdef __cplusplus
extern "C"
{
#endif

//=============================================================================
// Includs
//=============================================================================

//=============================================================================
// Defines & Macros
//=============================================================================
#define INVALID_PTR  (-1)
#define IS_VALID_PTR(ptr)  (ptr != INVALID_PTR)

/// MSG Pool return value
typedef MBX_Result MSGPOOL_Result;

#define E_MSGPOOL_SUCCESS                    E_MBX_SUCCESS
#define E_MSGPOOL_ERR_NOT_INITIALIZED       E_MBX_ERR_NOT_INITIALIZED
#define E_MSGPOOL_ERR_NO_MORE_MEMORY        E_MBX_ERR_NO_MORE_MEMORY
#define E_MSGPOOL_ERR_SLOT_BUSY              E_MBX_ERR_SLOT_BUSY
#define E_MSGPOOL_ERR_SLOT_AREADY_OPENNED   E_MBX_ERR_SLOT_AREADY_OPENNED
#define E_MSGPOOL_ERR_SLOT_NOT_OPENNED      E_MBX_ERR_SLOT_NOT_OPENNED
#define E_MSGPOOL_ERR_INVALID_PARAM          E_MBX_ERR_INVALID_PARAM
#define E_MSGPOOL_ERR_HAS_MSG_PENDING       E_MBX_ERR_HAS_MSG_PENDING
#define E_MSGPOOL_ERR_NO_MORE_MSG            E_MBX_ERR_NO_MORE_MSG
#define E_MSGPOOL_ERR_NOT_IMPLEMENTED       E_MBX_ERR_NOT_IMPLEMENTED
#define E_MSGPOOL_UNKNOW_ERROR               E_MBX_UNKNOW_ERROR

//=============================================================================
// Type and Structure Declaration
//=============================================================================
//Enum:
typedef enum
{
    E_MSGQ_INVALID    = 0x00,
    E_MSGQ_NORMAL     = 0x01,
    E_MSGQ_EMPTY      = 0x02,
    E_MSGQ_OVERFLOW   = 0x03
} MSGPOOL_MsgQStatus;

typedef enum
{
    E_MSGQ_R2TASK_INVALID    = 0x00,
    E_MSGQ_R2TASK_TEST     = 0x01,
    E_MSGQ_R2TASK_PNL      = 0x02,
    E_MSGQ_R2TASK_LOGO   = 0x03,
    E_MSGQ_R2TASK_MUSIC   = 0x04,
    E_MSGQ_R2TASK_OSD   = 0x05,
    E_MSGQ_R2TASK_SECURE   = 0x06
} MSGPOOL_R2TaskID;

//Structs:
typedef struct
{
    MBX_Msg mbxMsg; //the msg in slot.
    MS_S16 s16Next;  //next item in pool;
    MS_U16 u16Usage; //the slot is used or free;
}MSGPOOL_MsgPoolItem; //sizeof(MSGPOOL_MsgPoolItem) == 28 bytes

typedef struct
{
    volatile MSGPOOL_MsgPoolItem * pMsgPool; //pointer to the reserved msg pool
    MS_U16 u16Slots; //the total number of MsgPoolItem in the MsgPool
    MS_U16 u16FreeSlots; //the free number of MsgPoolItem in the MsgPool
    MS_U16 u16RegistedSlots; //the registed(resevered for registed msg class) number of MsgPoolItem in the MsgPool.
}MSGPOOL_MsgPoolInfo;

typedef struct
{
    MS_S16 s16MsgFirst; //the first MsgPoolItem slot idx in MsgPool
    MS_S16 s16MsgEnd; //the end MsgPoolItem slot idx in MsgPool

    MS_S16 s16InstantMsgFirst; //the first instant MsgPoolItem slot idx in MsgPool
    MS_S16 s16InstantMsgEnd; //the end instant MsgPoolItem slot idx in MsgPool

    MS_U16 u16MsgNum; //the number of MsgPoolItem in MsgQ;
    MS_U16 u16InstantMsgNum; //the number of instant MsgPoolItem in MsgQ;

    MS_U16 u16MsgQStatus; //the MsgQ Status: invalid; normal, empty; voerflow;
    MS_U16 u16MsgQSize; //the MsgQ size when the msg class is registed; should be no larger than MAX_MBX_QUEUE_SIZE
}MSGPOOL_MsgQMgr; //message queue manager, per class per queue.

////////////////////////////////////////////////////////////////////////////////////////////
// interface to control the Msg Pool:
INTERFACE MSGPOOL_Result MDrv_MSGPOOL_Init(void);
INTERFACE void MDrv_MSGPOOL_DeInit(void);

////////////////////////////////////////////////////////////////////////////////////////////
// interface to control the Msg Queue:
INTERFACE MSGPOOL_Result MDrv_MSGQ_Init(void);
INTERFACE MSGPOOL_Result MDrv_MSGQ_DeInit(MS_BOOL bForceDiscardPendingMsg);

INTERFACE MSGPOOL_Result MDrv_MSGQ_RegisterMSG(MS_S16 s16MsgQID, MS_U16 u16MsgQSize);
INTERFACE MSGPOOL_Result MDrv_MSGQ_UnRegisterMSG(MS_S16 s16MsgQID, MS_BOOL bForceDiscardMsgQueue);
INTERFACE MSGPOOL_Result MDrv_MSGQ_ClearMSG(MS_S16 s16MsgQID);

INTERFACE MSGPOOL_Result MDrv_MSGQ_GetMsgQStatus(MS_S16 s16MsgQID, MBX_MSGQ_Status *pMsgQStatus);

INTERFACE MSGPOOL_Result MDrv_MSGQ_RecvMsg(MS_S16 s16MsgQIdx, MBX_Msg* pMsg, MS_BOOL bInstantMsg);
INTERFACE MSGPOOL_Result MDrv_MSGQ_AddMSG(MBX_Msg* pMbxMsg);

#undef INTERFACE


#ifdef __cplusplus
}
#endif

#endif //_DRV_MBX_MSGPOOL_H

