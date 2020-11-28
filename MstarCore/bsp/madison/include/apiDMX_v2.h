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
//  File name: apiDMX_v2.h
//  Description: Demux (dmx) api header file
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DMX_H_
#define _DMX_H_

#include "MsDevice.h"

#ifdef __cplusplus
extern "C"
{
#endif


typedef enum {
    // General API                                                              //*** Args of API  ***

    MApi_CMD_DMX_Init = 0,                              // (DMX_TSPParam*)                                                              #0
    MApi_CMD_DMX_Exit,
    MApi_CMD_DMX_ForceExit,
    MApi_CMD_DMX_Suspend,
    MApi_CMD_DMX_Resume,
    MApi_CMD_DMX_ChkFwAlive,
    MApi_CMD_DMX_Reset,
    MApi_CMD_DMX_SetFwMiuDataAddr,                  // pointer to (U32_PhyAddr, U32_Size)
    MApi_CMD_DMX_WProtectEnable,                    // pointer to (U32_bEnable, U32_pStartAddr, U32_pEndAddr)
    MApi_CMD_DMX_OrzWProtectEnable,                 // pointer to (U32_bEnable, U32_pStartAddr, U32_pEndAddr)

    MApi_CMD_DMX_ReadDropCount = 10,                     // pointer to (DMX_POWSTATE_PARAM)                                      #10
    MApi_CMD_DMX_SetPowerState,
    MApi_CMD_DMX_SetOwner,                          // pointer to (U32_Start_Flt_Id, U32_End_Flt_Id, U32_IsOwner)
    MApi_CMD_DMX_GetCap,                            // pointer to (DMX_CAP_PARAM)

    MApi_CMD_DMX_SetBurstLen,                       // pointer to (DMX_BURSTTYPE)

    //Flow Control
    MApi_CMD_DMX_Flow,                              // pointer to (DMX_FLOW_PARAM)
    MApi_CMD_DMX_Flow_ParlInvert,                   // pointer to (U32_DMX_FLOW, U32_bInvert)
    MApi_CMD_DMX_Flow_ENABLE,                       // pointer to (U32_DMX_FLOW, U32_bEnable)

    //STC API
    MApi_CMD_DMX_GetPcr,                            // pointer to (U32_Eng_Id, U32_PCR_H, U32_PCR_L)
    MApi_CMD_DMX_Stc_Get,                           // pointer to (U32_Eng_Id, U32_STC_H, U32_STC_L)
    MApi_CMD_DMX_Stc_Set = 20,                           // pointer to (U32_Eng_Id, U32_STC_H, U32_STC_L)                     #20
    MApi_CMD_DMX_Stc_UpdateCtrl,                    // pointer to (U32_Eng_Id, U32_eStcUpdateCtrlMode)
    MApi_CMD_DMX_Stc_SetOffset ,                    // pointer to (U32_Eng_Id, U32_STCOffset, U32_bAdd)
    MApi_CMD_DMX_Stc_ClkAdjust,                     // pointer to (U32_Eng_Id, U32_Mutipletor64)

    //Filter API
    MApi_CMD_DMX_Open,                              // pointer to (DMX_FLT_TYPE_PARAM)
    MApi_CMD_DMX_Close,                             // pointer to (U32_DmxId)
    MApi_CMD_DMX_Start,                             // pointer to (U32_DmxId)
    MApi_CMD_DMX_Stop,                              // pointer to (U32_DmxId)
    MApi_CMD_DMX_Info,                              // pointer to (DMX_FLT_INFO_PARAM)
    MApi_CMD_DMX_Pid,                               // pointer to (U32_DmxId, U32_Pid, U32_bSet)
    MApi_CMD_DMX_IsStart = 30,                           // pointer to (U32_DmxId, U32_bEnable)                                           #30
    MApi_CMD_DMX_CopyData,                          // pointer to (DMX_FLT_COPY_PARAM)
    MApi_CMD_DMX_Proc,                              // pointer to (DMX_FLT_EVENT_PARAM)
    MApi_CMD_DMX_ChangeFltSrc,                      // pointer to (DMX_FLT_TYPE_PARAM)
    MApi_CMD_DMX_GetOwner,                          // pointer to (U32_DmxId, U32_bOwner)

    MApi_CMD_DMX_GetPESScmbSts,                     // pointer to (U32_DmxId, U32_ScmbSts)
    MApi_CMD_DMX_GetTsScmbSts,                      // pointer to (U32_DmxId, U32_ScmbSts)

    // Section API
    MApi_CMD_DMX_Sec_Reset,                         // pointer to (U32_DmxId)
    MApi_CMD_DMX_Sec_ReadAddr,                      // pointer to (U32_DmxId, U32_PhyReadAddr, U32_bSet)
    MApi_CMD_DMX_Sec_GetWriteAddr,                  // pointer to (U32_DmxId, U32_PhyWriteAddr)
    MApi_CMD_DMX_Sec_GetStartAddr = 40,             // pointer to (U32_DmxId, U32_PhyWriteAddr)                             #40
    MApi_CMD_DMX_Sec_GetEndAddr,                    // pointer to (U32_DmxId, U32_PhyEndAddr)
    MApi_CMD_DMX_Sec_SetPattern,                    // pointer to (DMX_FLT_SEC_PAT_PARAM)

    //TTX API
    MApi_CMD_DMX_GetTTXWrite,                       // pointer to (U32_DmxId, U32_PhyWriteAddr)
    MApi_CMD_DMX_GetAccess,                         // pointer to (U32_Try)
    MApi_CMD_DMX_ReleaseAccess,

    // AVFIFO control
    MApi_CMD_DMX_AVFIFO_Reset,                      // pointer to (DMX_AVFIFO_PARAM), u32Data is for setting bFlush
    MApi_CMD_DMX_AVFIFO_Status,                     // pointer to (DMX_AVFIFO_PARAM), u32Data is for getting FifoLevel
    MApi_CMD_DMX_RemoveDupAVFifoPkt,                // pointer to (DMX_AVFIFO_DROP_PARAM)
    MApi_CMD_DMX_AUBD_Enable,                       // pointer to (BOOL_bEnable)

    //PVR Playback API
    MApi_CMD_DMX_FI_PlayStamp = 50,                 // pointer to (U32_EngId, U32_Stamp, U32_bSet)                            #50
    MApi_CMD_DMX_FI_TimestampMode,                  // pointer to (U32_EngId, U32_bEnable)
    MApi_CMD_DMX_FI_SetPlaybackStampClk,            // pointer to (DMX_TIMESTAMP_CLK_PARAM)

    // PVR Engine API
    MApi_CMD_DMX_Pvr_Open,                          // pointer to (DMX_PVR_INFO_PARAM)
    MApi_CMD_DMX_Pvr_Close,                         // pointer to (U32_EngId)
    MApi_CMD_DMX_Pvr_PidOpen,                       // pointer to (DMX_PVR_FLTTYPE_PARAM)
    MApi_CMD_DMX_Pvr_PidClose,                      // pointer to (U32_EngId, U32_DmxId, U32_bDecryptRec)
    MApi_CMD_DMX_Pvr_Start,                         // pointer to (U32_EngId, MS_U32_bRecAll, U32_bDecryptRec)
    MApi_CMD_DMX_Pvr_Stop,                          // pointer to (U32_EngId, U32_bDecryptRec)
    MApi_CMD_DMX_Pvr_GetWriteAddr,                  // pointer to (U32_EngId, U32_PhyWriteAddr)
    MApi_CMD_DMX_Pvr_SetPktMode = 60,               // pointer to (U32_EngId, U32_bSet)                                           #60
    MApi_CMD_DMX_Pvr_SetRecordStamp,                // pointer to (U32_EngId, U32_Stamp)
    MApi_CMD_DMX_Pvr_GetRecordStamp,                // pointer to (U32_EngId, U32_Stamp)
    MApi_CMD_DMX_Pvr_SetMobfKey,                    // pointer to (U32_EngId, U32_Key0, U32_Key1, U32_bEnable)
    MApi_CMD_DMX_Pvr_SetRecordStampClk,             // pointer to (DMX_TIMESTAMP_CLK_PARAM)

    // File-in Engine API
    MApi_CMD_DMX_FI_Start,                          // pointer to (DMX_FILE_START_PARAM)
    MApi_CMD_DMX_FI_Stop,                           // pointer to (U32_EngId)
    MApi_CMD_DMX_FI_Info,                           // poiinter to (DMX_FILE_INFO_PARAM)
    MApi_CMD_DMX_FI_Pause,                          // pointer to (U32_EngId)
    MApi_CMD_DMX_FI_Resume,                         // pointer to (U32_EngId)
    MApi_CMD_DMX_FI_IsIdle = 70,                    // pointer to (U32_EngId, U32_bIdle)                                          #70
    MApi_CMD_DMX_FI_IsBusy,                         // pointer to (U32_EngId, U32_bBusy)
    MApi_CMD_DMX_FI_IsPause,                        // pointer to (U32_EngId, U32_bPause)
    MApi_CMD_DMX_FI_CmdQReset,                      // pointer to (U32_EngId)
    MApi_CMD_DMX_FI_CmdQGetEmptyNum,                // pointer to (U32_EngId, U32_EmptyNum)
    MApi_CMD_DMX_FI_BypassFileTimestamp,            // pointer to (U32_EngId, U32_bByPass)
    MApi_CMD_DMX_FI_CmdQGetFifoLevel,               // pointer to (U32_EngId, U32_WLevel)
    MApi_CMD_DMX_FI_GetFileTimeStamp,               // pointer to (U32_EngId, U32_TimeStamp)
    MApi_CMD_DMX_FI_GetReadAddr,                    // pointer to (U32_EngId, U32_PhyReadAddr)
    MApi_CMD_DMX_FI_SetMobfKey,                     // pointer to (U32_EngId, U32_Key, U32_bEnable)

    //MMFI  API
    MApi_CMD_DMX_MMFI_IsIdle = 80,                  // pointer to (U32_MMFIPath, U32_bIdle)                                     #80
    MApi_CMD_DMX_MMFI_IsBusy,                       // pointer to (U32_MMFIPath, U32_bBusy)
    MApi_CMD_DMX_MMFI_CmdQReset,                    // pointer to (DMX_MMFI_PATH)
    MApi_CMD_DMX_MMFI_GetEmptyNum,                  // pointer to (U32_MMFIPath, U32_EmptyNum)
    MApi_CMD_DMX_MMFI_Start,                        // pointer to (DMX_FILE_START_PARAM)
    MApi_CMD_DMX_MMFI_GetFileTimeStamp,             // pointer to (U32_EngId, U32_TimeStamp)

    MApi_CMD_DMX_MMFI_PidOpen,                      // pointer to (DMX_MMFI_FLT_PARAM)
    MApi_CMD_DMX_MMFI_PidClose,                     // pointer to (U32_EngId, U32_DmxId)
    MApi_CMD_DMX_MMFI_GetFifoLevel,                 // pointer to (U32_EngId, U32_WLevel)
    MApi_CMD_DMX_MMFI_PlayStamp_Set,                // pointer to (U32_EngId, U32_Stamp)
    MApi_CMD_DMX_MMFI_PlayStamp_Get = 90,           // pointer to (U32_EngId, U32_Stamp)                                         #90
    MApi_CMD_DMX_MMFI_SetTimeStampClk,              // pointer to (U32_MMFIPath, U32_DMX_TimeStamp_Clk)
    MApi_CMD_DMX_MMFI_RemoveDupAVPkt,               // pointer to (DMX_AVFIFO_DROP_PARAM)
    MApi_CMD_DMX_MMFI_SetMOBFKey,                   // pointer to (U32_EngId, U32_Key, U32_bEnable)

    //Debug API
    MApi_CMD_DMX_SetDbgLevel,                       // pointer to (DMX_DBGMSG_LEVEL)
    MApi_CMD_DMX_GetFwVer,                          // pointer to (U32_FwVer)

    MApi_CMD_DMX_CmdRun,                            // pointer to (DMX_CMDRUN_PARAM)

    //Utopia 1.0 compatible API
    MApi_CMD_DMX_SetFw,                             // pointer to (U32_FWAddr, U32_FWSize)
    MApi_CMD_DMX_SetHK,                              // pointer to (U32_bHK)
    MApi_CMD_DMX_Init_1_0,                          // None
    MApi_CMD_DMX_TSPInit_1_0 = 100,                 // (DMX_TSPParam*)                                                              #100
    MApi_CMD_DMX_ReleseHWSemp,                      // None
    MApi_CMD_DMX_GetLibVer,                         // const MSIF_Version **
    MApi_CMD_DMX_STC64ModeEnable,                   // pointer to (BOOL_bEnable)

    //Merge stream API
    MApi_CMD_DMX_SetPktMode,                        //// pointer to (DMX_PKT_MODE_PARAM)
    MApi_CMD_DMX_SetMergeStrSync,                   ///  pointer to (U32_SrcID, U32_SyncByte)

    MApi_CMD_DMX_PVR_Flow,                          /// pointer to (U32_PVR_ENG, DMX_PVRFLOW_PARAM)

    //TSO API
    MApi_CMD_DMX_TSO_FileInfo,                      /// poiinter to (DMX_FILE_INFO_PARAM)
    MApi_CMD_DMX_TSO_FileIsIdle,                    /// pointer to (U32_EngId, U32_bIdle)
    MApi_CMD_DMX_TSO_FileGetCmdQEmptyNum,           /// pointer to (U32_EngId, U32EmptyNum)
    MApi_CMD_DMX_TSO_FileStart = 110,               /// pointer to (U32_EngId, U32Address, U32Size)                          #110
    MApi_CMD_DMX_TSO_FileStop,                      /// pointer to (U32_EngId)
    MApi_CMD_DMX_TSO_FilePlayStamp,                 /// pointer to (U32_EngId, U32Stamp, U32_bEnable)
    MApi_CMD_DMX_TSO_FileGetTimeStamp,              /// pointer to (U32_EngId, U32Stamp)
    MApi_CMD_DMX_TSO_FileBypassStamp,               /// pointer to (U32_EngId, U32_bBypass)
    MApi_CMD_DMX_TSO_FileTimeStampEnable,           /// pointer to (U32_EngId, U32_bEnable)

    // DBG INFO API
    MApi_CMD_DMX_DBG_GET_DISCONCNT,                 /// poiinter to (DMX_PKT_DISCONCNT_PARAM)
    MApi_CMD_DMX_DBG_GET_DROPPKTCNT,                /// poiinter to (DMX_PKT_DROPCNT_PARAM)
    MApi_CMD_DMX_DBG_GET_LOCKPKTCNT,                /// poiinter to (DMX_PKT_LOCKCNT_PARAM)
    MApi_CMD_DMX_DBG_GET_AVPKTCNT,                  /// poiinter to (DMX_PKT_AVCNT_PARAM)

    MApi_CMD_DMX_GET_SECTEI_PKTCNT = 120,          /// poiinter to (DMX_PKT_SECTEI_PARAM)                                   #120
    MApi_CMD_DMX_RESET_SECTEI_PKTCNT,              /// poiinter to (DMX_FILTER_TYPE)
    MApi_CMD_DMX_GET_SECDISCON_PKTCNT,             /// poiinter to (U32_DMXID, U32_PKTCNT)
    MApi_CMD_DMX_RESET_SECDISCON_PKTCNT,           /// poiinter to (U32_DMXID)

    // BOX Series only
    MApi_CMD_DMX_Pvr_CBSize,                       /// poiinter to (U32_ENGID, U32_CBSIZE, U32_bSet)
    MApi_CMD_DMX_Pvr_SetCaMode,                    /// poiinter to (U32_ENGID, U32_CAMODE, U32_bSPSENABLE)

    MApi_CMD_DMX_Pvr_IsStart,                      /// poiinter to (U32_ENGID, U32_bIsStart)

    //TSO New
    MApi_CMD_DMX_TSO_OutClk,                      /// pointer to (DMX_TSO_OUTCLK_PARAM)

} eDmxIoctlOpt;

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------

/// DMX Output destination
typedef enum
{
    DMX_FLOW_OUT_LIVE0             = 0,
    DMX_FLOW_OUT_LIVE1             = 1,
    DMX_FLOW_OUT_LIVE2             = 2,
    DMX_FLOW_OUT_LIVE3             = 3,

    DMX_FLOW_OUT_FILE0             = 4,
    DMX_FLOW_OUT_FILE1             = 5,
    DMX_FLOW_OUT_FILE2             = 6,
    DMX_FLOW_OUT_FILE3             = 7,

    DMX_FLOW_OUT_PVR0              = 8,
    DMX_FLOW_OUT_PVR1              = 9,
    DMX_FLOW_OUT_PVR2              = 10,
    DMX_FLOW_OUT_PVR3              = 11,
    DMX_FLOW_OUT_PVR4              = 12,
    DMX_FLOW_OUT_PVR5              = 13,
    DMX_FLOW_OUT_PVRCB             = 14,

    DMX_FLOW_OUT_MMFIAU            = 15,
    DMX_FLOW_OUT_MMFI0             = DMX_FLOW_OUT_MMFIAU,
    DMX_FLOW_OUT_MMFIV3D           = 16,
    DMX_FLOW_OUT_MMFI1             = DMX_FLOW_OUT_MMFIV3D,

} DMX_FLOW_OUTPUT;


typedef struct _DMX_CAP_PARAM
{
    DMX_QUERY_TYPE          Quetype;
    void*                   pdata;

}DMX_CAP_PARAM, *PDMX_CAP_PARAM;

typedef struct _DMX_FLOW_PARAM
{
    DMX_FLOW           DmxFlow;
    DMX_FLOW_INPUT     DmxFlowInput;
    MS_BOOL            bClkInv;
    MS_BOOL            bExtSync;
    MS_BOOL            bParallel;
    MS_U32             u32CAEngSel; // 0xFFFFFFFF:None CA

    MS_BOOL            bSet;

}DMX_FLOW_PARAM, *PDMX_FLOW_PARAM;

typedef struct _DMX_PVRFLOW_PARAM
{
    MS_BOOL            bSet;

    DMX_PVR_ENG        eEng;
    DMX_TSIF           eSrcTSIf;
    MS_BOOL            bDscmbRec;

}DMX_PVRFLOWPARAM, *PDMX_PVRFLOW_PARAM;

typedef struct _DMX_FLT_TYPE_PARAM
{
    DMX_FILTER_TYPE     DmxFltType;
    MS_U32              u32DmxId;

}DMX_FLT_TYPE_PARAM, *PDMX_FLT_TYPE_PARAM;

typedef struct _DMX_FLT_INFO_PARAM
{
    MS_U32              u32DmxId;
    DMX_Flt_info*       pDmxFltInfo;
    DMX_FILTER_TYPE*    pDmxFltType;
    MS_BOOL             bSet;

}DMX_FLT_INFO_PARAM, *PDMX_FLT_INFO_PARAM;

typedef struct _DMX_FLT_COPYDATA_PARAM
{
    MS_U32              u32DmxId;
    MS_U8*              pu8Buf;
    MS_U32              u32BufSize;
    MS_U32              u32ActualSize;
    MS_U32              u32RmnSize;
    DMX_CheckCb         pfCheckCB;

}DMX_FLT_COPY_PARAM, *PDMX_FLT_COPY_PARAM;

typedef struct _DMX_FLT_EVENT_PARAM
{
    MS_U32              u32DmxId;
    DMX_EVENT*          pEvent;

}DMX_FLT_EVENT_PARAM, *PDMX_FLT_EVENT_PARAM;

typedef struct _DMX_FLT_SEC_PAT_PARAM
{
    MS_U32              u32DmxId;
    MS_U8*              pu8Pattern;
    MS_U8*              pu8Mask;
    MS_U8*              pu8NotMask;
    MS_U32              u32MatchSize;

}DMX_FLT_SEC_PAT_PARAM, *PDMX_FLT_SEC_PAT_PARAM;

typedef struct _DMX_AVFIFO_PARAM
{
    DMX_FILTER_TYPE     DmxFltType;
    MS_U32              u32Data;

}DMX_AVFIFO_PARAM, *PDMX_AVFIFO_PARAM;

typedef struct _DMX_AVFIFO_DROP_PARAM
{
    DMX_FILTER_TYPE     DmxFltType;
    MS_BOOL             bAllFifo;
    MS_BOOL             bEnable;

}DMX_AVFIFO_DROP_PARAM, *PDMX_AVFIFO_DROP_PARAM;


typedef struct _DMX_TIMESTAM_CLK_PARAM
{
    MS_U32              u32EngId;
    DMX_TimeStamp_Clk   eClk;

}DMX_TIMESTAMP_CLK_PARAM, *PDMX_TIMESTAMP_CLK_PARAM;

typedef struct _DMX_PVR_INFO_PARAM
{
    MS_U32              u32EngId;
    DMX_Pvr_info*       pPvrInfo;

}DMX_PVR_INFO_PARAM, *PDMX_PVR_INFO_PARAM;

typedef struct _DMX_PVR_FLTTYPE_PARAM
{
    MS_U32              u32EngId;
    MS_U32              u32DmxId;
    MS_U32              u32Pid;
    DMX_FILTER_TYPE     FltSrc;
    MS_U32              u32CAEngSel;            // 0xFFFFFFFF:No Dscmb
    MS_U32              u32SelShareFlt;         //0: Not use share dscmb filter

}DMX_PVR_FLTTYPE_PARAM, *PDMX_PVR_FLTTYPE_PARAM;

typedef struct _DMX_FILE_START_PARAM
{
    MS_U32              u32EngId;
    DMX_FILEIN_DST      Dst;
    MS_PHYADDR          pBuf;
    MS_U32              u32BufSize;

}DMX_FILE_START_PARAM, *PDMX_FILE_START_PARAM;

typedef struct _DMX_FILE_INFO_PARAM
{
    MS_U32              u32EngId;
    DMX_Filein_info*    pFileinInfo;

}DMX_FILE_INFO_PARAM, *PDMX_FILE_INFO_PARAM;

typedef struct _DMX_MMFI_FLT_PARAM
{
    DMX_MMFI_PATH       MMFIPath;
    DMX_MMFI_FLTTYPE    flttype;
    MS_U32              u32DmxId;
    MS_U32              u32Pid;

}DMX_MMFI_FLT_PARAM, *PDMX_MMFI_FLT_PARAM;

typedef struct _DMX_CMDRUN_PARAM
{
    MS_U32              u32Cmd;
    MS_U32              u32Config;
    MS_U32              u32DataNum;
    void*               pData;
}DMX_CMDRUN_PARAM, *PDMX_CMDRUN_PARAM;

typedef struct _DMX_POWSTATE_PARAM
{
    EN_POWER_MODE       u16PowerState;
    MS_U32              u32FWAddr;
    MS_U32              u32FWSize;
}DMX_POWSTATE_PARAM, *PDMX_POWSTATE_PARAM;

typedef struct _DMX_MMFI_START_PARAM
{
    MS_U32              u32EngId;
    DMX_MMFI_DST        Dst;
    MS_PHYADDR          pBuf;
    MS_U32              u32BufSize;

}DMX_MMFI_START_PARAM, *PDMX_MMFI_START_PARAM;

typedef struct _DMX_PKT_MODE_PARAM
{
    DMX_FLOW            eFlow;
    DMX_PacketMode      ePktMode;
}DMX_PKT_MODE_PARAM, *PDMX_PKT_MODE_PARAM;

typedef struct _DMX_PKT_DISCONCNT_PARAM
{
    DMX_DisContiCnt_info*   pInfo;
    MS_U32                  u32Cnt;
}DMX_PKT_DISCONCNT_PARAM, *PDMX_PKT_DISCONCNT_PARAM;

typedef struct _DMX_PKT_DROPCNT_PARAM
{
    DMX_DropPktCnt_info*   pInfo;
    MS_U32                 u32Cnt;
}DMX_PKT_DROPCNT_PARAM, *PDMX_PKT_DROPCNT_PARAM;

typedef struct _DMX_PKT_LOCKCNT_PARAM
{
    DMX_LockPktCnt_info*   pInfo;
    MS_U32                 u32Cnt;
}DMX_PKT_LOCKCNT_PARAM, *PDMX_PKT_LOCKCNT_PARAM;

typedef struct _DMX_PKT_AVCNT_PARAM
{
    DMX_AVPktCnt_info*     pInfo;
    MS_U32                 u32Cnt;
}DMX_PKT_AVCNT_PARAM, *PDMX_PKT_AVCNT_PARAM;

typedef struct _DMX_PKT_SECTEI_PARAM
{
    DMX_FILTER_TYPE        eType;
    MS_U32                 u32Cnt;
}DMX_PKT_SECTEI_PARAM, *PDMX_PKT_SECTEI_PARAM;

typedef struct _DMX_TSO_OUTCLK_PARAM
{
    MS_U32                 u32Eng;
    DMX_TSO_OutClk         eTsoOutClk;
    DMX_TSO_OutClkSrc      eTsoOutClkSrc;
    MS_U16                 u16DivNum;
    MS_BOOL                bClkInv;
    MS_BOOL                bSet;
}DMX_TSO_OUTCLK_PARAM, *PDMX_TSO_OUTCLK_PARAM;


#ifdef __cplusplus
}
#endif


#endif //_DMX_H_


