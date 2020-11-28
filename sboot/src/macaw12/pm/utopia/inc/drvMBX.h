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
/// @file   drvMBX.h
/// @brief  MStar Mailbox Driver DDI
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_MBX_H
#define _DRV_MBX_H

#ifdef _DRV_MBX_C
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
#include "MsTypes.h"

//=============================================================================
// Defines & Macros
//=============================================================================
/// Version string.
#define MBX_DRV_VERSION               /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x6666                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    {'M','B','X','_'},                  /* IP__                                             */  \
    {'0','2'},                          /* 0.0 ~ Z.Z                                        */  \
    {'0','4'},                          /* 00 ~ 99                                          */  \
    {'0','0','5','4','6','1','0','2'},  /* CL#                                              */  \
    MSIF_OS

/// Max Mailbox Queque Size for one Mail Class
#define MAX_MBX_QUEUE_SIZE      256
/// Max Parameter Size ( in bytes ) for one Mail Message
#define MAX_MBX_PARAM_SIZE      10
/// Max Size ( in bytes ) for SetInformation
#define MAX_MBX_INFORMATION_SIZE    8

/// Define The Queue Status of The Mail Class queue
/// Queue overflow: new incoming mail will be skip
#define MBX_STATUS_QUEUE_OVER_FLOW       0x00000001
/// Queque Has Instant Msg: there has new instant message in queue
#define MBX_STATUS_QUEUE_HAS_INSTANT_MSG 0x00000002
/// Queue Has Normal Msg: there has new normal message in queue
#define MBX_STATUS_QUEUE_HAS_NORMAL_MSG  0x00000004

/// Define The Flags for Receive Message from Message Queue
/// Recv any message class, this means, the targetClass is useless if this bit is set
//#define MBX_CHECK_ALL_MSG_CLASS 0x00000001
/// Check Instant Message
#define MBX_CHECK_INSTANT_MSG   0x00000002
/// Check Normal Message
#define MBX_CHECK_NORMAL_MSG    0x00000004
/// Recv any message class, this means, the targetClass is useless if this bit is set
#define MBX_CHECK_ALL_MSG_CLASS (MBX_CHECK_INSTANT_MSG|MBX_CHECK_NORMAL_MSG)
/// Block Receive function call until time out if no message available
#define MBX_CHECK_BLOCK_RECV    0x80000000

/// Define debug level:
/// Default Debug Level: No any Debug Message Print out
#define MBX_DBG_LEVEL_NONE       0x00
/// HAL Debug Level: Print out MBX Hal Error/Warning
#define MBX_DBG_LEVEL_MBXHAL     0x01
/// Message Queue Debug Level: Print out Message Queue Error/Warning
#define MBX_DBG_LEVEL_MSGQ       0x02
/// Interrupt HAL Debug Level: Print out Inerrut HAL Error/Warning
#define MBX_DBG_LEVEL_MBXINT     0x04
/// Critical Debug Level: Print out any Critical Error/Warning
#define MBX_DBG_LEVEL_CRITICAL   0x08
/// All Debug Level: Print out any Error/Wanring, That is, All above Debug Level Errors/Warnings
#define MBX_DBG_LEVEL_ALL        0x0F

//=============================================================================
// Type and Structure Declaration
//=============================================================================

//=============================================================================
// Enums

/// Mail Message Class Defines
typedef enum
{
    /// MBX_CLASS_SYSTEM
    E_MBX_CLASS_SYSTEM         = 0,
    /// MBX_CLASS_INPUT
    E_MBX_CLASS_INPUT          = 1,
    /// MBX_CLASS_TSP
    E_MBX_CLASS_TSP            = 2,
    /// MBX_CLASS_CHANNEL
    E_MBX_CLASS_CHANNEL        = 3,
    /// MBX_CLASS_MEMORY
    E_MBX_CLASS_MEMORY         = 4,
    /// MBX_CLASS_MPEG
    E_MBX_CLASS_MPEG           = 5,
    /// MBX_CLASS_VIDEO
    E_MBX_CLASS_VIDEO          = 6,
    /// MBX_CLASS_AUDIO
    E_MBX_CLASS_AUDIO          = 7,
    /// MBX_CLASS_MHEG5_STATE
    E_MBX_CLASS_MHEG5_STATE    = 8,
    /// MBX_CLASS_MVF
    E_MBX_CLASS_MVF            = 9,
    /// MBX_CLASS_GE
    E_MBX_CLASS_GE             = 10,
    /// MBX_CLASS_CI
    E_MBX_CLASS_CI            = 11,  //rename unused "MBX_CLASS_NUM" as "MBX_CLASS_CI" for CIMHEG usage
    /// MBX_CLASS_TEST
    E_MBX_CLASS_TEST           = 12,
    /// MBX_CLASS_MAD
    E_MBX_CLASS_MAD            = 13,

    /// MBX_CLASS_MPEG2_FS
    E_MBX_CLASS_MPEG2_FS       = 14,
    /// MBX_CLASS_MPEG2
    E_MBX_CLASS_MPEG2          = 15,
    /// MBX_CLASS_BMP
    E_MBX_CLASS_BMP            = 16,
    /// MBX_CLASS_PNG
    E_MBX_CLASS_PNG            = 17,
    /// MBX_CLASS_JPEG
    E_MBX_CLASS_JPEG           = 18,
    /// MBX_CLASS_MJPEG
    E_MBX_CLASS_MJPEG          = 19,
    /// MBX_CLASS_JPEG_ENCODER
    E_MBX_CLASS_JPEG_ENCODER   = 20,
    ///
    E_MBX_CLASS_VDPLAYER_FS    = 21,
    /// MBX_CLASS_VDPLAYER_FS
    E_MBX_CLASS_VDPLAYER       = 22,
    /// MBX_CLASS_RMPLAYER_FS
    E_MBX_CLASS_RMPLAYER_FS    = 23,
    /// MBX_CLASS_RMPLAYER
    E_MBX_CLASS_RMPLAYER       = 24,
    /// MBX_CLASS_TSPLAYER_FS
    E_MBX_CLASS_TSPLAYER_FS    = 25,
    /// MBX_CLASS_TSPLAYER
    E_MBX_CLASS_TSPLAYER       = 26,
    /// MBX_CLASS_LZSS
    E_MBX_CLASS_LZSS           = 27,
    /// MBX_CLASS_CAPE
    E_MBX_CLASS_CAPE           = 28,
    /// MBX_CLASS_CC
    E_MBX_CLASS_CC             = 29,
    /// MBX_CLASS_DLNA
    E_MBX_CLASS_DLNA           = 30,
    /// MBX_CLASS_DUMMY_LOOP
    E_MBX_CLASS_DUMMY_LOOP     = 31,
    /// MBX_CLASS_CHAKRA_SUBSYS
    E_MBX_CLASS_CHAKRA_SUBSYS  = 32,
    /// MBX_CLASS_FCNTL
    E_MBX_CLASS_FCNTL          = 33,
    /// MBX_CLASS_IRKEY
    E_MBX_CLASS_IRKEY          = 34,
    /// MBX_CLASS_BTPD
    E_MBX_CLASS_BTPD           = 35,
    /// MBX_CLASS_OBAMA_CMD
    E_MBX_CLASS_OBAMA_CMD      = 36,
    /// MBX_CLASS_OBAMA_APP
    E_MBX_CLASS_OBAMA_APP      = 37,
    /// MBX_CLASS_KTV
    E_MBX_CLASS_KTV             = 38,
    /// MBX_CLASS_CIPLUS
    E_MBX_CLASS_CIPLUS         = 39,
    /// MBX_CLASS_PRINT_MESSAGE
    E_MBX_CLASS_PRINT_MESSAGE = 40,
    /// MBX_CLASS_SHWFS
    E_MBX_CLASS_SHWFS          = 41,
    /// MBX_CLASS_AUTO_TEST
    E_MBX_CLASS_AUTO_TEST = 42,
    /// MBX_CLASS_STILLIMAGE_CMD_IO
    E_MBX_CLASS_STILLIMAGE_CMD_IO = 43,
    /// MBX_CLASS_STILLIMAGE_DATA_IO_FAST
    E_MBX_CLASS_STILLIMAGE_DATA_IO_FAST = 44,
    /// MBX_CLASS_MSTILLIMAGE_DATA_IO
    E_MBX_CLASS_STILLIMAGE_DATA_IO = 45,
    /// MBX_CLASS_NET_DEBUG
    E_MBX_CLASS_NET_DEBUG = 46,
    /// MBX_CLASS_PM_WAIT
    E_MBX_CLASS_PM_WAIT        = 47,
    /// MBX_CLASS_PM_NOWAIT
    E_MBX_CLASS_PM_NOWAIT      = 48,
    /// MBX_CLASS_IRKEY_NOWAIT
    E_MBX_CLASS_IRKEY_NOWAIT   = 49,
    /// MBX_CLASS_SAR
    E_MBX_CLASS_SAR            = 50,
    /// MBX_CLASS_SAR_NOWAIT
    E_MBX_CLASS_SAR_NOWAIT     = 51,
    /// MBX_CLASS_SECUREBOOT_WAIT
    E_MBX_CLASS_SECURE_WAIT     = 52,
    /// MBX_CLASS_SECUREBOOT_NOWAIT
    E_MBX_CLASS_SECURE_NOWAIT     = 53,
    /// MBX_CLASS_FRC
    E_MBX_CLASS_FRC = 54,
   //MBX_CLASS_PM_PWM_WAIT
    E_MBX_CLASS_PM_PWM_WAIT= 55,
    //MBX_CLASS_PM_PWM_NOWAIT
    E_MBX_CLASS_PM_PWM_NOWAIT= 56,
    /// Define the Number of Mail Class, It is very Import, must be at the end of the list!
    //put the following two enum at the end of the list
    E_MBX_CLASS_NUM,
    /// The End NUmber of Max Class ID
    E_MBX_CLASS_MAX = 0xFF
}MBX_Class;

/// Mail Box Supported CPU ID Defins
typedef enum
{
   /// CPU PM ID
   E_MBX_CPU_PM = 0,
   /// CPU AEON ID
   E_MBX_CPU_AEON = 1,
   /// CPU MIPS ID
   E_MBX_CPU_MIPS = 2,
   //  same as MIPS
   E_MBX_CPU_R2M = 2,
   /// CPU MIPS VPE0 ID, T3 Only
   E_MBX_CPU_MIPS_VPE0 = 2,
   /// CPU MIPS VPE1 ID, T3 Only
   E_MBX_CPU_MIPS_VPE1 = 3,
   //  CPU  R2M, Janus Only
   E_MBX_CPU_MAX,
}MBX_CPU_ID;

/// Mail Box Supported CPU ID Defins
typedef enum
{
    /// House Keeping Identifier
    E_MBX_ROLE_HK = 0,
    /// Co-Processer Identifier
    E_MBX_ROLE_CP = 1,
    /// PM Identifier
    E_MBX_ROLE_PM = 2,
    E_MBX_ROLE_MAX
}MBX_ROLE_ID;

/// Mail Message Class Type Defines
typedef enum
{
    /// Normal Message Class Type
    E_MBX_MSG_TYPE_NORMAL  = 0,
    /// Instant Message Class Type
    E_MBX_MSG_TYPE_INSTANT = 1
}MBX_MSG_Type;

/// MB DDI return value
typedef enum
{
    /// Success Call
    E_MBX_SUCCESS                = 0,
    /// Error: Not Initialized
    E_MBX_ERR_NOT_INITIALIZED        = 1,
    /// Error: No more Memory, Queue Memory Issue
    E_MBX_ERR_NO_MORE_MEMORY         = 2,
    /// Error: class has been used by other APP
    E_MBX_ERR_SLOT_BUSY              = 3,
    /// Error: class has been openned by this APP, you do not need to open it again
    E_MBX_ERR_SLOT_AREADY_OPENNED    = 4,
    /// Error: class not registered yet
    E_MBX_ERR_SLOT_NOT_OPENNED       = 5,
    /// Error: unknow cpu id
    E_MBX_ERR_INVALID_CPU_ID         = 6,
    /// Error: invalid parameter
    E_MBX_ERR_INVALID_PARAM          = 7,
    /// Error: peer cpu is peek Mail from Hardware, you can not send mail now
    E_MBX_ERR_PEER_CPU_BUSY          = 8,
    /// Error: peer cpu do not alive, Mail never peek out, Need check peer cpu is alive or not
    E_MBX_ERR_PEER_CPU_NOT_ALIVE     = 9,
    /// Error: peer cpu not initialized yet, not ready to receive mail message
    E_MBX_ERR_PEER_CPU_NOTREADY = 10,
    /// Error: peer cpu the dedicated class Overflow!
    E_MBX_ERR_PEER_CPU_OVERFLOW = 11,
    /// Error: the mail message has been fetched yet, there has no message in hardware
    E_MBX_ERR_MSG_ALREADY_FETCHED = 12,
    /// Error: time out with dedicated request
    E_MBX_ERR_TIME_OUT               = 13,
    /// Error: no mail message in message queue
    E_MBX_ERR_NO_MORE_MSG            = 14,
    /// Error: has mail message in queue when un-register mail class or DeInit MailBox Driver
    E_MBX_ERR_HAS_MSG_PENDING        = 15,
    /// Error: not implemente yet for request
    E_MBX_ERR_NOT_IMPLEMENTED        = 16,
    /// Error: unknow error, like system error
    E_MBX_UNKNOW_ERROR           = 0xFFFF
} MBX_Result;

//=============================================================================
// Structurs

/// Mail Message Define
typedef struct
{
    /// Role ID, for send, this is the Mail Target, for receive, this is the Source which sent this message
    MBX_ROLE_ID      eRoleID;
    /// Mail Message Type, Normal or Instant
    MBX_MSG_Type     eMsgType;

    /// Ctrl Byte in Mail Message
    MS_U8              u8Ctrl;
    /// @ref MBX_Class
    MS_U8              u8MsgClass; //should be MBX_Class, for alignment let it be S8, gcc default sizeof(enum) is 4 bytes.
    /// Command Index defined by Apps
    MS_U8              u8Index;
    /// Parameter Count
    MS_U8              u8ParameterCount;
    /// Parameters, Max Number @ref MAX_MBX_PARAM_SIZE
    MS_U8              u8Parameters[MAX_MBX_PARAM_SIZE];
    /// Status 0 byte of Mail Message
    MS_U8              u8S0;
    /// Status 1 byte of Mail Message
    MS_U8              u8S1;
}MBX_Msg;

/// Mail Message Queue status
typedef struct
{
    /// Mail message Queue status,
    /// @ref MBX_STATUS_QUEUE_OVER_FLOW
    /// @ref MBX_STATUS_QUEUE_HAS_INSTANT_MSG
    /// @ref MBX_STATUS_QUEUE_HAS_NORMAL_MSG
    MS_U32 status;
    /// pended normal message count in class message queue
    MS_U32 u32NormalMsgCount;
    /// pended Instant message count in class message queue
    MS_U32 u32InstantMsgCount;
}MBX_MSGQ_Status;

/// MBX Driver Info
typedef struct
{
    /// MBX HW Group Number
    MS_U8 u8HWMBXGroupNum;
}MBX_DrvInfo;

/// MBX Driver Status
typedef struct
{
    /// MBX Driver is enabled or not
    MS_BOOL bEnabled;
    /// The reference Cnt with this driver:
    MS_S32 s32RefCnt;
}MBX_DrvStatus;

/// Type of Mail Message callback function Define
//typedef void (*MBX_QUEUE_STATUS_NOTIFY_FUNC)(MBX_Class eMsgClass, MBX_MSGQ_Status *pMsgQueueStatus);
typedef void (*MBX_MAIL_ARRIVE_NOTIFY_FUNC)( MBX_Msg *pMsg, MS_BOOL *pbAddToQueue);

INTERFACE MBX_Result  MDrv_MBX_Init(MBX_CPU_ID eHKCPU, MBX_ROLE_ID eHostRole, MS_U32 u32TimeoutMillSecs);
INTERFACE MBX_Result  MDrv_MBX_DeInit(MS_BOOL bForceDiscardPendingMsg);
INTERFACE MBX_Result  MDrv_MBX_RegisterMSG(MBX_Class eMsgClass, MS_U16 u16MsgQueueSize);
//INTERFACE MBX_Result  MDrv_MBX_RegisterMSGWithCallBack(MBX_Class eMsgClass, MS_U16 u16MsgQueueSize, MBX_QUEUE_STATUS_NOTIFY_FUNC notifier);
INTERFACE MBX_Result  MDrv_MBX_RegisterMSGWithCallBack(MBX_Class eMsgClass, MS_U16 u16MsgQueueSize, MBX_MAIL_ARRIVE_NOTIFY_FUNC notifier);
INTERFACE MBX_Result  MDrv_MBX_UnRegisterMSG(MBX_Class eMsgClass, MS_BOOL bForceDiscardMsgQueue);
INTERFACE MBX_Result  MDrv_MBX_ClearMSG(MBX_Class eMsgClass);
INTERFACE MBX_Result  MDrv_MBX_SendMsg(MBX_Msg *pMsg);
INTERFACE MBX_Result  MDrv_MBX_GetMsgQueueStatus(MBX_Class eTargetClass, MBX_MSGQ_Status *pMsgQueueStatus);
INTERFACE MBX_Result  MDrv_MBX_RecvMsg(MBX_Class eTargetClass, MBX_Msg *pMsg, MS_U32 u32WaitMillSecs, MS_U32 u32Flag);
INTERFACE MBX_Result  MDrv_MBX_CheckMsg(MBX_Class eTargetClass, MBX_Msg *pMsg, MS_U32 u32WaitMillSecs, MS_U32 u32Flag);
INTERFACE MBX_Result  MDrv_MBX_SendMsgLoopback(MBX_Msg *pMsg, MBX_ROLE_ID eSrcRoleId);
INTERFACE MBX_Result  MDrv_MBX_Enable(MS_BOOL bEnable);//Enable receiving regisited messages in kernel
INTERFACE MBX_Result  MDrv_MBX_RemoveLatestMsg(void);

// For Application Set/Get Information API:
INTERFACE MBX_Result  MDrv_MBX_SetInformation(MBX_ROLE_ID eTargetRole, MS_U8 *pU8Info, MS_U8 u8Size);
INTERFACE MBX_Result  MDrv_MBX_GetInformation(MBX_ROLE_ID eTargetRole, MS_U8 *pU8Info, MS_U8 u8Size);

// For Debug & Version Control:
INTERFACE void        MDrv_MBX_SetDbgLevel(MS_U8 u8DbgLevel);
INTERFACE MS_BOOL     MDrv_MBX_GetLibVer(const MSIF_Version **ppVersion);
INTERFACE MS_BOOL     MDrv_MBX_GetInfo(MBX_DrvInfo *pMbxDrvInfo);
INTERFACE MS_BOOL     MDrv_MBX_GetStatus(MBX_DrvStatus *pMbxDrvStatus);

#undef INTERFACE


#ifdef __cplusplus
}
#endif

#endif //_DRV_MBX_H

