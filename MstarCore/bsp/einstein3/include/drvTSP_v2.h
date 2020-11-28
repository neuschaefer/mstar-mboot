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
//  File name: tsp.h
//  Description: Transport Stream Processor (TSP) driver header file
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _TSP_H_
#define _TSP_H_


#ifdef __cplusplus
extern "C"
{
#endif

enum {
    MDrv_CMD_TSP_Init,
    MDrv_CMD_TSP_Exit,

    MDrv_CMD_TSP_Suspend,
    MDrv_CMD_TSP_Resume,
    MDrv_CMD_TSP_Reset,
    MDrv_CMD_TSP_PowerOff,
    MDrv_CMD_TSP_ChkAlive,
    MDrv_CMD_TSP_ParlBitOrderSwap,
    MDrv_CMD_TSP_SetBurstLen,

    #ifdef STC64_SUPPORT
    MDrv_CMD_TSP_STC64ModeEn,
    #endif

    MDrv_CMD_TSP_CmdRun,
    MDrv_CMD_TSP_FltSetOwner,
    MDrv_CMD_TSP_PidfltChkOwner,
    MDrv_CMD_TSP_SetHK,

    MDrv_CMD_TSP_TTXIsAccess,
    MDrv_CMD_TSP_TTXUnlockAccess,
    MDrv_CMD_TSP_HWLockRelease,
    MDrv_CMD_TSP_TTXSecfltGetWaddr,

    MDrv_CMD_TSP_Proc,
    MDrv_CMD_TSP_SelPad,
    MDrv_CMD_TSP_SetOperateMode,
    MDrv_CMD_TSP_GetSTC,
    MDrv_CMD_TSP_SetSTC,
    MDrv_CMD_TSP_GetPCR,
    MDrv_CMD_TSP_GetState,
    MDrv_CMD_TSP_GetTSIFStatus,
    MDrv_CMD_TSP_FltLiveSrcSwitch,
    MDrv_CMD_TSP_AVFifoReset,
    MDrv_CMD_TSP_AVFifoStatus,
    MDrv_CMD_TSP_RemoveAVDupPkt,
    MDrv_CMD_TSP_AUBDModeEn,
    MDrv_CMD_TSP_GetTsScmLevel,
    MDrv_CMD_TSP_GetScmStatus,

    MDrv_CMD_TSP_PidFltAlloc,
    MDrv_CMD_TSP_PidFltFree,
    MDrv_CMD_TSP_PidFltSetPid,
    MDrv_CMD_TSP_PidFltGetPid,
    MDrv_CMD_TSP_PidFltSelSecFlt,
    MDrv_CMD_TSP_PidFltEnable,
    MDrv_CMD_TSP_PidFltGetState,
    MDrv_CMD_TSP_PidFltPVREnable,
    MDrv_CMD_TSP_PidFltChangeSrc,

    MDrv_CMD_TSP_SecFltAlloc,
    MDrv_CMD_TSP_SecFltFree,
    MDrv_CMD_TSP_SecFltSetMode,
    MDrv_CMD_TSP_SecFltSetPattern,
    MDrv_CMD_TSP_SecFltResetBuf,
    MDrv_CMD_TSP_SecFltSetBuf,
    MDrv_CMD_TSP_SecFltSetReqCount,
    MDrv_CMD_TSP_SecFltGetBufStart,
    MDrv_CMD_TSP_SecFltGetBufSize,
    MDrv_CMD_TSP_SecFltGetReadAddr,
    MDrv_CMD_TSP_SecFltGetWriteAddr,
    MDrv_CMD_TSP_SecFltSetReadAddr,
    MDrv_CMD_TSP_SecFltNotify,
    MDrv_CMD_TSP_SecFltGetState,

    MDrv_CMD_TSP_PvrSetBuf,
    MDrv_CMD_TSP_PvrStart,
    MDrv_CMD_TSP_PvrGetWaddr,
    MDrv_CMD_TSP_PvrNotify,
    MDrv_CMD_TSP_PvrSetPktMode,
    MDrv_CMD_TSP_PvrSetRecTimestamp,
    MDrv_CMD_TSP_PvrGetRecTimestamp,
    MDrv_CMD_TSP_PvrSetPlaybackStampClk,
    MDrv_CMD_TSP_PvrSetRecStampClk,
    MDrv_CMD_TSP_PvrFileinEn,

    MDrv_CMD_TSP_PvrPidFltReserved,
    MDrv_CMD_TSP_PvrFlt1StartRec,
    MDrv_CMD_TSP_PvrClose,

    MDrv_CMD_TSP_FileSetAddr,
    MDrv_CMD_TSP_FileSetSize,
    MDrv_CMD_TSP_FileStart,
    MDrv_CMD_TSP_FileStop,
    MDrv_CMD_TSP_FilePause,
    MDrv_CMD_TSP_FileResume,
    MDrv_CMD_TSP_FileGetState,
    MDrv_CMD_TSP_FileSetRate,
    MDrv_CMD_TSP_FileSetPktMode,
    MDrv_CMD_TSP_FileGetCmdQSlot,
    MDrv_CMD_TSP_FileResetCmdQ,
    MDrv_CMD_TSP_FileGetCmdQFifoStatus,
    MDrv_CMD_TSP_File192BlockSchemeEn,
    MDrv_CMD_TSP_FilePSPathEnable,
    MDrv_CMD_TSP_FileGetReadAddr,
    MDrv_CMD_TSP_FileTimestampModeEn,
    MDrv_CMD_TSP_FileGetFileinTimestamp,

    MDrv_CMD_TSP_VQSetBuf,
    MDrv_CMD_TSP_VQEnable,
    MDrv_CMD_TSP_VQReset,
    MDrv_CMD_TSP_VQGetStatus,
    MDrv_CMD_TSP_VQOvfIntEn,
    MDrv_CMD_TSP_VQThreshold,

    MDrv_CMD_TSP_MobfSetPvrKey,
    MDrv_CMD_TSP_MobfSetFileinKey,
    MDrv_CMD_TSP_MobfPvrEnable,
    MDrv_CMD_TSP_MobfFileinEnable,

    MDrv_CMD_TSP_GetCap,
    MDrv_CMD_TSP_GetStatus,
    MDrv_CMD_TSP_GetLibVer,

    MDrv_CMD_TSP_GetFWVer,
    MDrv_CMD_TSP_GetIntrCount,
    MDrv_CMD_TSP_GetLastErr,
    MDrv_CMD_TSP_GetDbgPortInfo,
    MDrv_CMD_TSP_SetDbgLevel,
    MDrv_CMD_TSP_SetFwDbgParam,

} eTspIoctlOpt;

// for driver init parameters setting
typedef struct _TSP_INIT_PARAM
{
    MS_U32          u32FWAddr;   //miu buffer for fwtsp.bin
    MS_U32          u32FWSize;

    MS_U32          u32VQAddr;   //miu buffer for virtual queue
    MS_U32          u32VQSize;

    MS_BOOL         bIsHK;

}TSP_INIT_PARAM, *PTSP_INIT_PARAM;

typedef struct _TSP_BUF_PARAM
{
    MS_U32 u32BufAddr;
    MS_U32 u32BufSize;
}TSP_BUF_PARAM, *PTSP_BUF_PARAM;

// for cmd MDrv_CMD_TSP_ParlBitOrderSwap
typedef struct _TSP_PARL_BITORDER_SWAP_PARAM
{
    MS_U32 u32EngId;
    DrvTSP_If eIf;
    MS_BOOL bInvert;
}TSP_PARL_BITORDER_SWAP_PARAM, *PTSP_PARL_BITORDER_SWAP_PARAM;

// for cmd MDrv_CMD_TSP_CmdRun
typedef struct _TSP_CMDRUN_PARAM
{
    MS_U32 u32EngId;
    MS_U32 u32Cmd;
    MS_U32 u32Config0;
    MS_U32 u32Config1;
    void* pData;
}TSP_CMDRUN_PARAM, *PTSP_CMDRUN_PARAM;

// for cmd MDrv_CMD_TSP_FltSetOwner
typedef struct _TSP_FLT_SETOWNER_PARAM
{
    MS_U32 u32EngId;
    MS_U32 u32FltIdStart;
    MS_U32 u32FltIdEnd;
    MS_U32 u32Owner;
}TSP_FLT_SETOWNER_PARAM, *PTSP_FLT_SETOWNER_PARAM;

typedef struct _TSP_FLT_ID_PARAM
{
    MS_U32 u32EngId;
    MS_U32 u32FltId;
}TSP_FLT_ID_PARAM, *PTSP_FLT_ID_PARAM;

typedef struct _TSP_FLT_ADDR_PARAM
{
    MS_U32 u32EngId;
    MS_U32 u32FltId;
    MS_PHYADDR* pu32Addr;
}TSP_FLT_ADDR_PARAM, *PTSP_FLT_ADDR_PARAM;

// for cmd MDrv_CMD_TSP_Proc
typedef struct _TSP_PROC_PARAM
{
    MS_U32 u32EngId;
    MS_U32 u32FltId;
    TSP_Result Ret;
    DrvTSP_Event Evt;
}TSP_PROC_PARAM, *PTSP_PROC_PARAM;

// for cmd MDrv_CMD_TSP_SelPad
typedef struct _TSP_PAD_IF_PARAM
{
    MS_U32 u32EngId;
    DrvTSP_If eIf;
    DrvTSP_If_Set IfSet;
}TSP_PAD_IF_PARAM, *PTSP_PAD_IF_PARAM;

// for cmd MDrv_CMD_TSP_SetOperateMode
typedef struct _TSP_OPERATION_MODE_PARAM
{
    MS_U32 u32EngId;
    DrvTSP_CtrlMode eCtrlMode;
}TSP_OPERATION_MODE_PARAM, *PTSP_OPERATION_MODE_PARAM;

typedef struct _TSP_STC_PARAM
{
    MS_U32 u32EngId;
    MS_U32 u32STC;
    MS_U32 u32STC_32;
}TSP_STC_PARAM, *PTSP_STC_PARAM;

typedef struct _TSP_PCR_PARAM
{
    MS_U32 u32EngId;
    MS_U32 u32Pcr;
    MS_U32 u32Pcr_32;
}TSP_PCR_PARAM, *PTSP_PCR_PARAM;

typedef struct _TSP_FLT_STATE_PARAM
{
    MS_U32 u32EngId;
    MS_U32 u32FltId;
    DrvTSP_FltState eState;
}TSP_FLT_STATE_PARAM, *PTSP_FLT_STATE_PARAM;

// for cmd MDrv_CMD_TSP_AVFifoReset
typedef struct _TSP_AVFIFO_RESET_PARAM
{
    MS_U32 u32EngId;
    DrvTSP_FltType eFilterType;
    MS_BOOL bFlush;
}TSP_AVFIFO_RESET_PARAM, *PTSP_AVFIFO_RESET_PARAM;

// for cmd MDrv_CMD_TSP_AVFifoStatus
typedef struct _TSP_AVFIFO_STATUS_PARAM
{
    MS_U32 u32EngId;
    DrvTSP_FltType eFilterType;
    MS_U32 u32FifoLevel;
}TSP_AVFIFO_STATUS_PARAM, *PTSP_AVFIFO_STATUS_PARAM;

// for cmd MDrv_CMD_TSP_RemoveAVFifoDupPkt
typedef struct _TSP_REM_AVFIFO_DUPPKT_PARAM
{
    MS_U32 u32EngId;
    DrvTSP_FltType eFilterType;
    MS_BOOL bForAllFifo;
    MS_BOOL bEnable;
}TSP_REM_AVFIFO_DUPPKT_PARAM, *PTSP_REM_AVFIFO_DUPPKT_PARAM;

typedef struct _TSP_SCMB_LEVEL_PARAM
{
    MS_U32 u32EngId;
    DrvTSP_Scmb_Level ScmbLevel;
}TSP_SCMB_LEVEL_PARAM, *PTSP_SCMB_LEVEL_PARAM;

typedef struct _TSP_SCMB_STATUS_PARAM
{
    MS_U8 u8FltId;
    DrvTSP_Scmb_Level ScmbType;
    MS_U8 u8TsScmbstatus;
    MS_U8 u8PesScmbstatus;
}TSP_SCMB_STATUS_PARAM, *PTSP_SCMB_STATUS_PARAM;

typedef struct _TSP_FLT_TYPE_PARAM
{
    MS_U32 u32EngId;
    MS_U32 u32FltId;
    DrvTSP_FltType eFilterType;
}TSP_FLT_TYPE_PARAM, *PTSP_FLT_TYPE_PARAM;

typedef struct _TSP_FLT_PID_PARAM
{
    MS_U32 u32EngId;
    MS_U32 u32FltId;
    MS_U32 u32PID;
}TSP_FLT_PID_PARAM, *PTSP_FLT_PID_PARAM;

typedef struct _TSP_SECFLT_PARAM
{
    MS_U32 u32EngId;
    MS_U32 u32PidFltId;
    MS_U32 u32SecFltId;
}TSP_SECFLT_PARAM, *PTSP_SECFLT_PARAM;

// for cmd MDrv_CMD_TSP_PidFltEnable
typedef struct _TSP_PIDFLT_EN_PARAM
{
    MS_U32 u32EngId;
    MS_U32 u32PidFltId;
    MS_BOOL bEnable;
}TSP_PIDFLT_EN_PARAM, *PTSP_PIDFLT_EN_PARAM;

// for cmd MDrv_CMD_TSP_SecFltSetMode
typedef struct _TSP_SECFLT_MODE_PARAM
{
    MS_U32 u32EngId;
    MS_U32 u32FltId;
    DrvTSP_FltMode eSecFltMode;
}TSP_SECFLT_MODE_PARAM, *PTSP_SECFLT_MODE_PARAM;

// for cmd MDrv_CMD_TSP_SecFltSetPattern
typedef struct _TSP_SECFLT_PAT_PARAM
{
    MS_U32 u32EngId;
    MS_U32 u32FltId;
    MS_U8 *pu8Match;
    MS_U8 *pu8Mask;
    MS_U8 *pu8NotMask;
}TSP_SECFLT_PAT_PARAM, *PTSP_SECFLT_PAT_PARAM;

typedef struct _TSP_SECFLT_BUF_PARAM
{
    MS_U32 u32EngId;
    MS_U32 u32FltId;
    MS_PHYADDR u32StartAddr;
    MS_U32 u32BufSize;
}TSP_SECFLT_BUF_PARAM, *PTSP_SECFLT_BUF_PARAM;

typedef struct _TSP_SECFLT_DATA_PARAM
{
    MS_U32 u32EngId;
    MS_U32 u32FltId;
    MS_U32 u32Data;
}TSP_SECFLT_DATA_PARAM, *PTSP_SECFLT_DATA_PARAM;

typedef struct _TSP_SECFLT_NOTIFY_PARAM
{
    MS_U32 u32EngId;
    MS_U32 u32FltId;
    DrvTSP_Event eEvents;
    P_DrvTSP_EvtCallback pfCallback;
}TSP_SECFLT_NOTIFY_PARAM, *PTSP_SECFLT_NOTIFY_PARAM;

typedef struct _TSP_RINGBUF_PARAM
{
    MS_U32 u32EngId;
    MS_PHYADDR u32BufStart0;
    MS_U32 u32BufSize0;
    MS_PHYADDR u32BufStart1;
    MS_U32 u32BufSize1;
}TSP_RINGBUF_PARAM, *PTSP_RINGBUF_PARAM;

typedef struct _TSP_PVR_START_PARAM
{
    MS_U32 u32EngId;
    DrvTSP_RecMode eRecMode;
    MS_BOOL bStart;
}TSP_PVR_START_PARAM, *PTSP_PVR_START_PARAM;

typedef struct _TSP_ENG_DATA_PARAM
{
    MS_U32 u32EngId;
    MS_U32 u32Data;
}TSP_ENG_DATA_PARAM, *PTSP_ENG_DATA_PARAM;

typedef struct _TSP_PVR_NOTIFY_PARAM
{
    MS_U8 u8EngId;
    DrvTSP_Event eEvents;
    P_DrvTSP_EvtCallback pfCallback;
}TSP_PVR_NOTIFY_PARAM, *PTSP_PVR_NOTIFY_PARAM;

typedef struct _TSP_ENG_BOOL_PARAM
{
    MS_U8 u8EngId;
    MS_BOOL bTrue;
}TSP_ENG_BOOL_PARAM, *PTSP_ENG_BOOL_PARAM;

// for cmd MDrv_CMD_TSP_PvrFileinEn
typedef struct _TSP_PVR_FI_EN_PARAM
{
    MS_U32 u32EngId;
    MS_BOOL bBypassHD;
    MS_BOOL bEnable;
}TSP_PVR_FI_EN_PARAM, *PTSP_PVR_FI_EN_PARAM;

// for cmd MDrv_CMD_TSP_PvrPidFltReserved
typedef struct _TSP_PVR_PIDFLT_RESERVED_PARAM
{
    MS_U32 u32EngId;
    MS_U32 Pid;
    MS_U8 u8DmxId;
    MS_BOOL bReserved;
}TSP_PVR_PIDFLT_RESERVED_PARAM, *PTSP_PVR_PIDFLT_RESERVED_PARAM;

typedef struct _TSP_FI_MODE_PARAM
{
    MS_U32 u32EngId;
    DrvTSP_FileinMode eFileinMode;
}TSP_FI_MODE_PARAM, *PTSP_FI_MODE_PARAM;

typedef struct _TSP_CAP_PARAM
{
    DrvTSP_Cap eCap;
    void* pOutput;
}TSP_CAP_PARAM, *PTSP_CAP_PARAM;

typedef struct _TSP_STATE_PARAM
{
    DrvTSP_HW_Status HW_Status;
    DrvTSP_SW_Status SW_Status;
}TSP_STATE_PARAM, *PTSP_STATE_PARAM;

typedef struct _TSP_DBG_INFO_PARAM
{
    MS_U32 u32DbgSel;
    MS_U32* u32DbgInfo;
}TSP_DBG_INFO_PARAM, *PTSP_DBG_INFO_PARAM;

typedef struct _TSP_FWDBG_PARAM
{
    MS_PHYADDR phyAddr;
    MS_U32 u32Size;
    MS_U32 u32DbgWord;
}TSP_FWDBG_PARAM, *PTSP_FWDBG_PARAM;


#ifdef __cplusplus
}
#endif

#endif //_TSP_H_


