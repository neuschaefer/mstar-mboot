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
// Copyright (c) 2013-2015 MStar Semiconductor, Inc.
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
//  File name: apiDMX_private.h
//  Description: Demux  (DMX) API private header file
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DMX_PRIV_H_
#define _DMX_PRIV_H_

#include "apiDMX.h"
#include "MsTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

// General API
typedef DMX_FILTER_STATUS (*IOCTL_DMX_INIT_LIBRES)(void*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SET_FW)(MS_U32, MS_U32);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SET_FW_DATAADDR)(MS_U32, MS_U32);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SET_HK)(MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_INIT)(void);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_TSPINIT)(DMX_TSPParam*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_EXIT)(void);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FORCE_EXIT)(void);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SUSPEND)(void);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_RESUME)(MS_U32, MS_U32);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_CHK_ALIVE)(void);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_RESET)(void);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_RELEASE_HWSEMP)(void);
typedef void              (*IOCTL_DMX_WPROTECT_EN)(MS_BOOL, MS_U32*, MS_U32*);
typedef void              (*IOCTL_DMX_ORZWPROTECT_EN)(MS_BOOL, MS_U32, MS_U32);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_READ_DROP_COUNT)(MS_U16*, MS_U16*);
typedef MS_U32            (*IOCTL_DMX_SET_POWER_STATE)(EN_POWER_MODE, MS_U32, MS_U32);


typedef DMX_FILTER_STATUS (*IOCTL_DMX_SET_OWNER)(MS_U8, MS_U8, MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_GET_CAP)(DMX_QUERY_TYPE, void*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PARL_INVERT)(DMX_FLOW, MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SET_BURSTLEN)(DMX_BURSTTYPE);

//Flow Control
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SET_FLOW)(DMX_FLOW, DMX_FLOW_INPUT, MS_BOOL, MS_BOOL, MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SET_PVRFLOW)(DMX_PVR_ENG, DMX_TSIF, MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_GET_FLOWINPUT_STS)(DMX_FLOW, DMX_FLOW_INPUT*, MS_BOOL*, MS_BOOL*, MS_BOOL*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FLOW_ENABLE)(DMX_FLOW, MS_BOOL);
//STC API
typedef DMX_FILTER_STATUS (*IOCTL_DMX_STC64_MODE_EN)(MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_GET_PCR_ENG)(MS_U8, MS_U32*, MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_GET_STC_ENG)(MS_U8, MS_U32*, MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SET_STC_ENG)(MS_U8, MS_U32, MS_U32);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SET_STC_UPDATECTL)(MS_U8, eStcUpdateCtrlMode);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SET_STC_OFFSET)(MS_U32, MS_U32, MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SET_STC_CLK_ADJUST)(MS_U32, MS_BOOL, MS_U32);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SEL_STC)(DMX_FILTER_TYPE, MS_U32);


//Filter API
typedef DMX_FILTER_STATUS (*IOCTL_DMX_OPEN)(DMX_FILTER_TYPE, MS_U8*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_CLOSE)(MS_U8);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_START)(MS_U8);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_STOP)(MS_U8);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_INFO)(MS_U8, DMX_Flt_info*, DMX_FILTER_TYPE*, MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PID)(MS_U8, MS_U16*, MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_IS_START)(MS_U8, MS_BOOL*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_COPY_DATA)(MS_U8, MS_U8*, MS_U32, MS_U32*, MS_U32*, DMX_CheckCb);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PROC)(MS_U8, DMX_EVENT*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_CHANGE_FLTSRC)(MS_U8, DMX_FILTER_TYPE);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SWITCH_LIVE_FLTSRC)(DMX_FILTER_TYPE);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_GET_OWNER)(MS_U8, MS_BOOL*);

typedef DMX_FILTER_STATUS (*IOCTL_DMX_GET_FLTSCMBSTS)(DMX_FILTER_TYPE, MS_U32, MS_U32, MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_GET_PESSCMBSTS)(MS_U8, MS_U8*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_GET_TSSCMBSTS)(MS_U8, MS_U8*);

// Section API
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SEC_RESET)(MS_U8);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SEC_SET_READADDR)(MS_U8, MS_U32);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SEC_GET_READADDR)(MS_U8, MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SEC_GET_WRITEADDR)(MS_U8, MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SEC_GET_STARTADDR)(MS_U8, MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SEC_GET_ENDADDR)(MS_U8, MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SEC_SET_PATTERN)(MS_U8, MS_U8*, MS_U8*, MS_U8*, MS_U32);

//TTX API
typedef DMX_FILTER_STATUS (*IOCTL_DMX_GET_TTX_WRITE)(MS_U8, MS_PHYADDR*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_GET_ACCESS)(MS_U32);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_RELEASE_ACCESS)(void);

// AVFIFO control
typedef DMX_FILTER_STATUS (*IOCTL_DMX_AVFIFO_RESET)(DMX_FILTER_TYPE, MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_AVFIFO_STATUS)(DMX_FILTER_TYPE, DMX_FIFO_STATUS*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_REMOVE_DUPAVFPKT)(MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_REMOVE_DUPAVFIFOPKT)(DMX_FILTER_TYPE, MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_AUBD_MODE_EN)(MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SET_PKTMODE)(DMX_FLOW, DMX_PacketMode);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SET_MERSTR_SYNC)(MS_U32, MS_U8);

//PVR Playback API (Old)
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FILE_SET_PLAYSTAMP)(MS_U32);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FILE_GET_PLAYSTAMP)(MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FILE_TIMESTAMP_ENABLE)(void);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FILE_TIMESTAMP_DISABLE)(void);

// PVR Engine API  (New)
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PVR_ENG_OPEN)(DMX_PVR_ENG, DMX_Pvr_info*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PVR_ENG_CLOSE)(DMX_PVR_ENG);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PVR_ENG_PAUSE)(DMX_PVR_ENG, MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PVR_ENG_PID_OPEN)(DMX_PVR_ENG, MS_U32, MS_U8*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PVR_ENG_PID_CLOSE)(DMX_PVR_ENG, MS_U8);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PVR_ENG_START)(DMX_PVR_ENG, MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PVR_ENG_STOP)(DMX_PVR_ENG);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PVR_ENG_GET_WRITEADDR)(DMX_PVR_ENG, MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PVR_ENG_SET_PKTMODE)(DMX_PVR_ENG, MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PVR_ENG_SET_RECORDSTAMP)(DMX_PVR_ENG, MS_U32);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PVR_ENG_GET_RECORDSTAMP)(DMX_PVR_ENG, MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PVR_ENG_MOBF_EN)(MS_U8 , MS_BOOL, MS_U32, MS_U32);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PVR_ENG_SET_RECORDSTAMP_CLK)(DMX_PVR_ENG, DMX_TimeStamp_Clk);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PVR_ENG_CBSIZE)(DMX_PVR_ENG, MS_U32*, MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PVR_ENG_SET_CAMODE)(DMX_PVR_ENG, DMX_CA_PVRMODE, MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PVR_ENG_IS_START)(DMX_PVR_ENG, MS_BOOL*);

//PVR Playback API (New)
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FILE_ENG_SET_PLAYSTAMP_CLK)(MS_U8, DMX_TimeStamp_Clk);

//PVR CA Engine API (New)
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PVRCA_ENG_PID_OPEN)(DMX_PVR_ENG, MS_U32, MS_U8*, MS_U8);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PVRCA_ENG_PID_CLOSE)(DMX_PVR_ENG, MS_U8);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PVRCA_ENG_START)(DMX_PVR_ENG, MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_PVRCA_ENG_STOP)(DMX_PVR_ENG);

// File-in API (Old)
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FILE_START)(DMX_FILEIN_DST, MS_U32, MS_U32);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FILE_STOP)(void);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FILE_INFO)(DMX_Filein_info*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FILE_PAUSE)(void);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FILE_RESUME)(void);
typedef MS_BOOL           (*IOCTL_DMX_FILE_IS_IDLE)(void);
typedef MS_BOOL           (*IOCTL_DMX_FILE_IS_BUSY)(void);
typedef MS_BOOL           (*IOCTL_DMX_FILE_IS_PAUSE)(void);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FILE_CMDQ_RESET)(void);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FILE_CMDQ_GET_EMPTY_NUM)(MS_U32*);
typedef void              (*IOCTL_DMX_FILE_BYPASS_FILE_TIMESTAMP)(MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FILE_CMDQ_GET_FIFO_WLEVEL)(MS_U8*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FILE_GET_FILE_TIMESTAMP)(MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FILE_GET_READADDR)(MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FILE_MOBF_EN)(MS_BOOL, MS_U32);

//MMFI & MINITSP API
typedef MS_BOOL           (*IOCTL_DMX_MMFI_IS_IDLE)(DMX_MMFI_PATH);
typedef MS_BOOL           (*IOCTL_DMX_MMFI_IS_BUSY)(DMX_MMFI_PATH);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_MMFI_CMDQ_RESET)(DMX_MMFI_PATH);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_MMFI_CMDQ_Get_EMPTY_NUM)(DMX_MMFI_PATH, MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_MMFI_START)(DMX_MMFI_DST, MS_PHYADDR, MS_U32);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_MMFI_GET_FILE_TIMESTAMP)(DMX_MMFI_PATH, MS_U32*);

//MMFI  (MMFI Only) API
typedef DMX_FILTER_STATUS (*IOCTL_DMX_MMFI_PID_OPEN)(DMX_MMFI_FLTTYPE, MS_U16, MS_U8*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_MMFI_PID_CLOSE)(MS_U8);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_MMFI_CMDQ_GET_FIFOLEVEL)(DMX_MMFI_PATH, MS_U8*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_MMFI_SET_PLAYTIMESTAMP)(DMX_MMFI_PATH, MS_U32);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_MMFI_GET_PLAYTIMESTAMP)(DMX_MMFI_PATH, MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_MMFI_SET_TIMESTAMPCLK)(DMX_MMFI_PATH, DMX_TimeStamp_Clk);

typedef DMX_FILTER_STATUS (*IOCTL_DMX_MMFI_REMOVE_DUPAVPKT)(MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_MMFI_MOBF_EN)(DMX_MMFI_PATH, MS_BOOL, MS_U32);

//TSO API
typedef DMX_FILTER_STATUS (*IOCTL_DMX_TSO_FI_INFO)(MS_U8, DMX_Filein_info*);
typedef MS_BOOL           (*IOCTL_DMX_TSO_FI_ISIDLE)(MS_U8);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_TSO_FI_CMDQ_GET_EMPTYNUM)(MS_U8, MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_TSO_FI_CMDQ_RESET)(MS_U8);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_TSO_FI_START)(MS_U8, MS_PHYADDR, MS_U32);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_TSO_FI_STOP)(MS_U8);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_TSO_FI_SET_PLAYTIMESTAMP)(MS_U8, MS_U32);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_TSO_FI_GET_PLAYSTAMP)(MS_U8, MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_TSO_FI_GETSTAMP)(MS_U8, MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_TSO_FI_BYPASS_STAMP)(MS_U8, MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_TSO_FI_STAMP_EN)(MS_U8);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_TSO_FI_STAMP_DISABLE)(MS_U8);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_TSO_SET_OUTCLK)(MS_U8, DMX_TSO_OutClk, DMX_TSO_OutClkSrc, MS_U16, MS_BOOL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_TSO_LOCSTRID)(MS_U8, DMX_TSO_InputIf, MS_U8*, MS_BOOL);

//Debug API
typedef DMX_FILTER_STATUS (*IOCTL_DMX_SET_DBGLEVEL)(DMX_DBGMSG_LEVEL);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_GET_FWVER)(MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_GET_LIBVER)(const MSIF_Version **);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_GET_DISCONCNT)(DMX_DisContiCnt_info*, MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_GET_DROPPKTCNT)(DMX_DropPktCnt_info*, MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_GET_LOCKPKTCNT)(DMX_LockPktCnt_info*, MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_GET_AVPKTCNT)(DMX_AVPktCnt_info*, MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_GET_SECTEI_PKTCNT)(DMX_FILTER_TYPE, MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_RESET_SECTEI_PKTCNT)(DMX_FILTER_TYPE);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_GET_SECDISCON_PKTCNT)(MS_U32, MS_U32*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_RESET_SECDISCONT_PKTCNT)(MS_U32);

typedef DMX_FILTER_STATUS (*IOCTL_DMX_CMD_RUN)(MS_U32, MS_U32, MS_U32, void*);

//FQ
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FQ_SET_FLT_RUSH_PASS)(MS_U8, MS_U8);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FQ_INIT)(MS_U32, DMX_FQ_Info*);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FQ_EXIT)(MS_U32);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FQ_RUSH_EN)(MS_U32);
typedef DMX_FILTER_STATUS (*IOCTL_DMX_FQ_SKIP_RUSH_DATA)(MS_U32,DMX_FQ_SkipPath);


typedef struct _MMFI_INSTANT_PRIVATE
{
    IOCTL_DMX_INIT_LIBRES                   fpDMXInitLibRes;
    IOCTL_DMX_SET_FW                        fpDMXSetFWBuf;
    IOCTL_DMX_SET_FW_DATAADDR               fpDMXSetFWMiuDataAddr;
    IOCTL_DMX_SET_HK                        fpDMXSetHK;
    IOCTL_DMX_INIT                          fpDMXInit;
    IOCTL_DMX_TSPINIT                       fpDMXTSPInit;
    IOCTL_DMX_EXIT                          fpDMXExit;
    IOCTL_DMX_FORCE_EXIT                    fpDMXForceExit;
    IOCTL_DMX_SUSPEND                       fpDMXSuspend;
    IOCTL_DMX_RESUME                        fpDMXResume;
    IOCTL_DMX_CHK_ALIVE                     fpDMXChkFwAlive;
    IOCTL_DMX_RESET                         fpDMXReset;
    IOCTL_DMX_RELEASE_HWSEMP                fpDMXReleaseHwSemp;
    IOCTL_DMX_WPROTECT_EN                   fpDMXWProtectEnable;
    IOCTL_DMX_ORZWPROTECT_EN                fpDMXOrzWProtectEnable;
    IOCTL_DMX_READ_DROP_COUNT               fpDMXReadDropCount;
    IOCTL_DMX_SET_POWER_STATE               fpDMXSetPowerState;

    IOCTL_DMX_SET_OWNER                     fpDMXSetOwner;
    IOCTL_DMX_GET_CAP                       fpDMXGetCap;
    IOCTL_DMX_PARL_INVERT                   fpDMXParlInvert;
    IOCTL_DMX_SET_BURSTLEN                  fpDMXSetBurstLen;

    IOCTL_DMX_SET_FLOW                      fpDMXFlowSet;
    IOCTL_DMX_SET_PVRFLOW                   fpDMXPvrFlowSet;
    IOCTL_DMX_GET_FLOWINPUT_STS             fpDMXGetFlowInputSts;
    IOCTL_DMX_FLOW_ENABLE                   fpDMXFlowEnable;

    IOCTL_DMX_STC64_MODE_EN                 fpDMX64bitModeEn;
    IOCTL_DMX_GET_PCR_ENG                   fpDMXGetPcrEng;
    IOCTL_DMX_GET_STC_ENG                   fpDMXGetStcEng;
    IOCTL_DMX_SET_STC_ENG                   fpDMXSetStcEng;
    IOCTL_DMX_SET_STC_UPDATECTL             fpDMXStcUpdateCtrl;
    IOCTL_DMX_SET_STC_OFFSET                fpDMXSetStcOffset;
    IOCTL_DMX_SET_STC_CLK_ADJUST            fpDMXStcClkAdjust;
    IOCTL_DMX_SEL_STC                       fpDMXStcSel;

    IOCTL_DMX_OPEN                          fpDMXOpen;
    IOCTL_DMX_CLOSE                         fpDMXClose;
    IOCTL_DMX_START                         fpDMXStart;
    IOCTL_DMX_STOP                          fpDMXStop;
    IOCTL_DMX_INFO                          fpDMXInfo;
    IOCTL_DMX_PID                           fpDMXPid;
    IOCTL_DMX_IS_START                      fpDMXIsStart;
    IOCTL_DMX_COPY_DATA                     fpDMXCopyData;
    IOCTL_DMX_PROC                          fpDMXProc;
    IOCTL_DMX_CHANGE_FLTSRC                 fpDMXChangeFltSrc;
    IOCTL_DMX_SWITCH_LIVE_FLTSRC            fpDMXSwitchLiveFltSrc;
    IOCTL_DMX_GET_OWNER                     fpDMXGetOnwer;

    IOCTL_DMX_GET_FLTSCMBSTS                fpDMXGetFltScmbSts;
    IOCTL_DMX_GET_PESSCMBSTS                fpDMXGetPesScmbSts;
    IOCTL_DMX_GET_TSSCMBSTS                 fpDMXGetTsScmbSts;

    IOCTL_DMX_SEC_RESET                     fpDMXSecReset;
    IOCTL_DMX_SEC_SET_READADDR              fpDMXSecSetReadAddr;
    IOCTL_DMX_SEC_GET_READADDR              fpDMXSecGetReadAddr;
    IOCTL_DMX_SEC_GET_WRITEADDR             fpDMXSecGetWriteAddr;
    IOCTL_DMX_SEC_GET_STARTADDR             fpDMXSecGetStartAddr;
    IOCTL_DMX_SEC_GET_ENDADDR               fpDMXSecGetEndAddr;
    IOCTL_DMX_SEC_SET_PATTERN               fpDMXSecSetPattern;

    IOCTL_DMX_GET_TTX_WRITE                 fpDMXGetTTXWrite;
    IOCTL_DMX_GET_ACCESS                    fpDMXGetAccess;
    IOCTL_DMX_RELEASE_ACCESS                fpDMXReleaseAccess;

    IOCTL_DMX_AVFIFO_RESET                  fpDMXAVFifoReset;
    IOCTL_DMX_AVFIFO_STATUS                 fpDMXAVFifoStatus;
    IOCTL_DMX_REMOVE_DUPAVFPKT              fpDMXRemoveDupAVPkt;
    IOCTL_DMX_REMOVE_DUPAVFIFOPKT           fpDMXRemoveDupAVFifoPkt;
    IOCTL_DMX_AUBD_MODE_EN                  fpDMXAUBDModeEn;
    IOCTL_DMX_SET_PKTMODE                   fpDMXSetPktMode;
    IOCTL_DMX_SET_MERSTR_SYNC               fpDMXSetMerStrSyc;

    IOCTL_DMX_FILE_SET_PLAYSTAMP            fpDMXFileSetPlayStamp;
    IOCTL_DMX_FILE_GET_PLAYSTAMP            fpDMXFileGetPlayStamp;
    IOCTL_DMX_FILE_TIMESTAMP_ENABLE         fpDMXFileTimestampEnable;
    IOCTL_DMX_FILE_TIMESTAMP_DISABLE        fpDMXFileTimestampDisable;

    IOCTL_DMX_PVR_ENG_OPEN                  fpDMXPvrEngOpen;
    IOCTL_DMX_PVR_ENG_CLOSE                 fpDMXPvrEngClose;
    IOCTL_DMX_PVR_ENG_PAUSE                 fpDMXPvrEngPause;
    IOCTL_DMX_PVR_ENG_PID_OPEN              fpDMXPvrEngPidOpen;
    IOCTL_DMX_PVR_ENG_PID_CLOSE             fpDMXPvrEngPidClose;
    IOCTL_DMX_PVR_ENG_START                 fpDMXPvrEngStart;
    IOCTL_DMX_PVR_ENG_STOP                  fpDMXPvrEngStop;
    IOCTL_DMX_PVR_ENG_GET_WRITEADDR         fpDMXPvrEngGetWriteAddr;
    IOCTL_DMX_PVR_ENG_SET_PKTMODE           fpDMXPvrEngSetPktMode;
    IOCTL_DMX_PVR_ENG_SET_RECORDSTAMP       fpDMXPvrEngSetRecordStamp;
    IOCTL_DMX_PVR_ENG_GET_RECORDSTAMP       fpDMXPvrEngGetRecordStamp;
    IOCTL_DMX_PVR_ENG_MOBF_EN               fpDMXPvrEngMobfEn;
    IOCTL_DMX_PVR_ENG_SET_RECORDSTAMP_CLK   fpDMXPvrEngSetRecordStampClk;
    IOCTL_DMX_PVR_ENG_CBSIZE                fpDMXPvrEngCBSize;
    IOCTL_DMX_PVR_ENG_SET_CAMODE            fpDMXPvrEngSetCaMode;
    IOCTL_DMX_PVR_ENG_IS_START              fpDMXPvrIsStart;

    IOCTL_DMX_FILE_ENG_SET_PLAYSTAMP_CLK    fpDMXFileEngSetPlayStampClk;

    IOCTL_DMX_PVRCA_ENG_PID_OPEN            fpDMXPvrcaEngPidOpen;
    IOCTL_DMX_PVRCA_ENG_PID_CLOSE           fpDMXPvrcaEngPidClose;
    IOCTL_DMX_PVRCA_ENG_START               fpDMXPvrcaEngStart;
    IOCTL_DMX_PVRCA_ENG_STOP                fpDMXPvrcaEngStop;

    IOCTL_DMX_FILE_START                    fpDMXFileStart;
    IOCTL_DMX_FILE_STOP                     fpDMXFileStop;
    IOCTL_DMX_FILE_INFO                     fpDMXFileInfo;
    IOCTL_DMX_FILE_PAUSE                    fpDMXFilePause;
    IOCTL_DMX_FILE_RESUME                   fpDMXFileResume;
    IOCTL_DMX_FILE_IS_IDLE                  fpDMXFileIsIdle;
    IOCTL_DMX_FILE_IS_BUSY                  fpDMXFileIsBusy;
    IOCTL_DMX_FILE_IS_PAUSE                 fpDMXFileIsPause;
    IOCTL_DMX_FILE_CMDQ_RESET               fpDMXFileCmdQReset;
    IOCTL_DMX_FILE_CMDQ_GET_EMPTY_NUM       fpDMXFileCmdQGetEmptyNum;
    IOCTL_DMX_FILE_BYPASS_FILE_TIMESTAMP    fpDMXFileBypassFileTimeStamp;
    IOCTL_DMX_FILE_CMDQ_GET_FIFO_WLEVEL     fpDMXFileCmdQGetFifoWLevel;
    IOCTL_DMX_FILE_GET_FILE_TIMESTAMP       fpDMXFileGetFileTimestamp;
    IOCTL_DMX_FILE_GET_READADDR             fpDMXFileGetReadAddr;
    IOCTL_DMX_FILE_MOBF_EN                  fpDMXFileMobfEn;

    IOCTL_DMX_MMFI_IS_IDLE                  fpDMXMMFIIsIdle;
    IOCTL_DMX_MMFI_IS_BUSY                  fpDMXMMFIIsBusy;
    IOCTL_DMX_MMFI_CMDQ_RESET               fpDMXMMFICmdQReset;
    IOCTL_DMX_MMFI_CMDQ_Get_EMPTY_NUM       fpDMXMMFIGetEmptyNum;
    IOCTL_DMX_MMFI_START                    fpDMXMMFIStart;
    IOCTL_DMX_MMFI_GET_FILE_TIMESTAMP       fpDMXMMFIGetFileTimestamp;

    IOCTL_DMX_MMFI_PID_OPEN                 fpDMXMMFIPidOpen;
    IOCTL_DMX_MMFI_PID_CLOSE                fpDMXMMFIPidClose;
    IOCTL_DMX_MMFI_CMDQ_GET_FIFOLEVEL       fpDMXMMFIGetFifoLevel;
    IOCTL_DMX_MMFI_SET_PLAYTIMESTAMP        fpDMXMMFISetPlayTimestamp;
    IOCTL_DMX_MMFI_GET_PLAYTIMESTAMP        fpDMXMMFIGetPlayTimestamp;
    IOCTL_DMX_MMFI_SET_TIMESTAMPCLK         fpDMXMMFISetTimestampClk;
    IOCTL_DMX_MMFI_REMOVE_DUPAVPKT          fpDMXMMFIRemoveDupAVPkt;
    IOCTL_DMX_MMFI_MOBF_EN                  fpDMXMMFIMobfEn;

    IOCTL_DMX_TSO_FI_INFO                   fpDMXTsoFileInfo;
    IOCTL_DMX_TSO_FI_ISIDLE                 fpDMXTsoFileIsIdle;
    IOCTL_DMX_TSO_FI_CMDQ_GET_EMPTYNUM      fpDMXTsoFileGetCmdQEmptyNum;
    IOCTL_DMX_TSO_FI_CMDQ_RESET             fpDMXTsoFileGetCmdQReset;
    IOCTL_DMX_TSO_FI_START                  fpDMXTsoFileStart;
    IOCTL_DMX_TSO_FI_STOP                   fpDMXTsoFileStop;
    IOCTL_DMX_TSO_FI_SET_PLAYTIMESTAMP      fpDMXTsoFileSetPlayStamp;
    IOCTL_DMX_TSO_FI_GET_PLAYSTAMP          fpDMXTsoFileGetPlayStamp;
    IOCTL_DMX_TSO_FI_GETSTAMP               fpDMXTsoFileGetTimeStamp;
    IOCTL_DMX_TSO_FI_BYPASS_STAMP           fpDMXTsoFileBypassStamp;
    IOCTL_DMX_TSO_FI_STAMP_EN               fpDMXTsoFileTimeStampEnable;
    IOCTL_DMX_TSO_FI_STAMP_DISABLE          fpDMXTsoFileTimeStampDisable;
    IOCTL_DMX_TSO_SET_OUTCLK                fpDMXTsoSetOutClk;
    IOCTL_DMX_TSO_LOCSTRID                  fpDMXTsoLocStrId;

    IOCTL_DMX_SET_DBGLEVEL                  fpDMXSetDbgLevel;
    IOCTL_DMX_GET_FWVER                     fpDMXGetFwVer;
    IOCTL_DMX_GET_LIBVER                    fpDMXGetLibVer;
    IOCTL_DMX_GET_DISCONCNT                 fpDMXGetDisConCnt;
    IOCTL_DMX_GET_DROPPKTCNT                fpDMXGetDropPktCnt;
    IOCTL_DMX_GET_LOCKPKTCNT                fpDMXGetLockPktCnt;
    IOCTL_DMX_GET_AVPKTCNT                  fpDMXGetAVPktCnt;
    IOCTL_DMX_GET_SECTEI_PKTCNT             fpDMXGetSecTeiPktCnt;
    IOCTL_DMX_RESET_SECTEI_PKTCNT           fpDMXResetSecTeiPktCnt;
    IOCTL_DMX_GET_SECDISCON_PKTCNT          fpDMXGetSecDisConPktCnt;
    IOCTL_DMX_RESET_SECDISCONT_PKTCNT       fpDMXResetSecDisContPktCnt;

    IOCTL_DMX_CMD_RUN                       fpDMXCmdRun;

    IOCTL_DMX_FQ_SET_FLT_RUSH_PASS          fpDMXFQSetFltRushPass;
    IOCTL_DMX_FQ_INIT                       fpDMXFQInit;
    IOCTL_DMX_FQ_EXIT                       fpDMXFQExit;
    IOCTL_DMX_FQ_RUSH_EN                    fpDMXFQRushEn;
    IOCTL_DMX_FQ_SKIP_RUSH_DATA             fpDMXFQSkipRushData;

}DMX_INSTANT_PRIVATE;


void    DMXRegisterToUtopia(FUtopiaOpen ModuleType);
MS_U32  DMXOpen(void** pInstance, void* pAttribute);
MS_U32  DMXClose(void* pInstance);
MS_U32  DMXIoctl(void* pInstance, MS_U32 u32Cmd, void* pArgs);


//----------------------
// Utopia 1.0 body API
//----------------------
DMX_FILTER_STATUS _MApi_DMX_SetFW(MS_PHYADDR pFwAddr, MS_U32 u32FwSize);
DMX_FILTER_STATUS _MApi_DMX_Init(void);
DMX_FILTER_STATUS _MApi_DMX_TSPInit(DMX_TSPParam *param);
DMX_FILTER_STATUS _MApi_DMX_Exit(void);
DMX_FILTER_STATUS _MApi_DMX_Reset(void);
DMX_FILTER_STATUS _MApi_DMX_ForceExit(void);
DMX_FILTER_STATUS _MApi_DMX_Resume(MS_U32 u32FWAddr, MS_U32 u32FWSize);
DMX_FILTER_STATUS _MApi_DMX_Suspend(void);
DMX_FILTER_STATUS _MApi_DMX_SetHK(MS_BOOL bIsHK);
DMX_FILTER_STATUS _MApi_DMX_ReleaseSemaphone(void);
DMX_FILTER_STATUS _MApi_DMX_Get_FlowInput_Status(DMX_FLOW DmxFlow, DMX_FLOW_INPUT *pDmxFlowInput, MS_BOOL *pbClkInv, MS_BOOL *pbExtSync, MS_BOOL *pbParallel);
DMX_FILTER_STATUS _MApi_DMX_FlowSet(DMX_FLOW DmxFlow, DMX_FLOW_INPUT DmxFlowInput, MS_BOOL bClkInv, MS_BOOL bExtSync, MS_BOOL bParallel);
DMX_FILTER_STATUS _MApi_DMX_PVR_FlowSet(DMX_PVR_ENG Eng, DMX_TSIF ePvrSrcTSIf, MS_BOOL bDscmbRec);
DMX_FILTER_STATUS _MApi_DMX_Open(DMX_FILTER_TYPE DmxFltType, MS_U8* pu8DmxId);
DMX_FILTER_STATUS _MApi_DMX_Close(MS_U8 u8DmxId);
DMX_FILTER_STATUS _MApi_DMX_Start(MS_U8 u8DmxId);
DMX_FILTER_STATUS _MApi_DMX_Stop(MS_U8 u8DmxId);
DMX_FILTER_STATUS _MApi_DMX_IsStart(MS_U8 u8DmxId, MS_BOOL* pbEnable);
DMX_FILTER_STATUS _MApi_DMX_Get_FltScmbSts(DMX_FILTER_TYPE FltSrc, MS_U32 u32FltGroupId, MS_U32 PidFltId, MS_U32 *pu32ScmbSts);
DMX_FILTER_STATUS _MApi_DMX_Get_PesScmbSts(MS_U8 u8DmxId, MS_U8* pu8scmb);
DMX_FILTER_STATUS _MApi_DMX_Get_TsScmbSts(MS_U8 u8DmxId, MS_U8* pu8ScmSts);
DMX_FILTER_STATUS _MApi_DMX_ChkAlive(void);
DMX_FILTER_STATUS _MApi_DMX_Info(MS_U8 u8DmxId, DMX_Flt_info* pDmxFltInfo, DMX_FILTER_TYPE* pDmxFltType, MS_BOOL bSet);
DMX_FILTER_STATUS _MApi_DMX_Pid(MS_U8 u8DmxId, MS_U16* pu16Pid, MS_BOOL bSet);
DMX_FILTER_STATUS _MApi_DMX_SectPatternSet(MS_U8 u8DmxId, MS_U8* pPattern, MS_U8* pMask, MS_U8 *pu8NotMask, MS_U32 MatchSize);
DMX_FILTER_STATUS _MApi_DMX_SectReset(MS_U8 u8DmxId);
DMX_FILTER_STATUS _MApi_DMX_SectReadSet(MS_U8 u8DmxId, MS_PHYADDR Read);
DMX_FILTER_STATUS _MApi_DMX_SectReadGet(MS_U8 u8DmxId, MS_PHYADDR* pRead);
DMX_FILTER_STATUS _MApi_DMX_SectWriteGet(MS_U8 u8DmxId, MS_PHYADDR* pWrite);
DMX_FILTER_STATUS _MApi_DMX_SectStartGet(MS_U8 u8DmxId, MS_PHYADDR* pStart);
DMX_FILTER_STATUS _MApi_DMX_SectEndGet(MS_U8 u8DmxId, MS_PHYADDR* pEnd);
DMX_FILTER_STATUS _MApi_DMX_SetFwDataAddr(MS_U32 u32DataAddr, MS_U32 u32size);
DMX_FILTER_STATUS _MApi_DMX_TTX_WriteGet(MS_U8 u8DmxId, MS_PHYADDR* pWrite);
DMX_FILTER_STATUS _MApi_DMX_Pvr_SetPlaybackStamp(MS_U32 u32Stamp);
DMX_FILTER_STATUS _MApi_DMX_Pvr_GetPlaybackStamp(MS_U32* pu32Stamp);
DMX_FILTER_STATUS _MApi_DMX_Pvr_TimeStampEnable(void);
DMX_FILTER_STATUS _MApi_DMX_Pvr_TimeStampDisable(void);
DMX_FILTER_STATUS _MApi_DMX_PvrCA_Eng_Pid_Open(DMX_PVR_ENG Eng, MS_U32 Pid, MS_U8* pu8DmxId, MS_U8 u8ShareKeyType);
DMX_FILTER_STATUS _MApi_DMX_PvrCA_Eng_Pid_Close(DMX_PVR_ENG Eng, MS_U8 u8DmxId);
DMX_FILTER_STATUS _MApi_DMX_PvrCA_Eng_Start(DMX_PVR_ENG Eng, MS_BOOL bPvrAll);
DMX_FILTER_STATUS _MApi_DMX_PvrCA_Eng_Stop(DMX_PVR_ENG Eng);
DMX_FILTER_STATUS _MApi_DMX_Filein_Info(DMX_Filein_info *pFileinInfo);
DMX_FILTER_STATUS _MApi_DMX_Filein_Start(DMX_FILEIN_DST Dst, MS_PHYADDR pBuf, MS_U32 u32BufSize);
DMX_FILTER_STATUS _MApi_DMX_Filein_Stop(void);
DMX_FILTER_STATUS _MApi_DMX_Filein_Pause(void);
DMX_FILTER_STATUS _MApi_DMX_Filein_Resume(void);
DMX_FILTER_STATUS _MApi_DMX_Filein_CMDQ_Reset(void);
DMX_FILTER_STATUS _MApi_DMX_Filein_CMDQ_GetEmptyNum(MS_U32 *pu32EmptySlot);
DMX_FILTER_STATUS _MApi_DMX_Filein_CMDQ_FIFOWriteLevel(MS_U8 *pu8CmdQStatus);
MS_BOOL           _MApi_DMX_Filein_IsIdle(void);
MS_BOOL           _MApi_DMX_Filein_IsBusy(void);
MS_BOOL           _MApi_DMX_Filein_IsPause(void);
DMX_FILTER_STATUS _MApi_DMX_Stc_Eng_Get(MS_U8 u8Eng, MS_U32* pu32Stc32, MS_U32* pu32Stc);
DMX_FILTER_STATUS _MApi_DMX_Stc_Eng_Set(MS_U8 u8Eng, MS_U32 u32Stc32, MS_U32 u32Stc);
DMX_FILTER_STATUS _MApi_DMX_STC_UpdateCtrl(MS_U8 u8Eng, eStcUpdateCtrlMode eMode);
DMX_FILTER_STATUS _MApi_DMX_Stc_Eng_SetOffset(MS_U32 u32Eng, MS_U32 u32Offset, MS_BOOL bAdd);
DMX_FILTER_STATUS _MApi_DMX_Stc_Clk_Adjust(MS_U32 u32EngId, MS_BOOL bUpClk, MS_U32 u32Percentage);
DMX_FILTER_STATUS _MApi_DMX_Stc_Select(DMX_FILTER_TYPE eFltSrc, MS_U32 u32StcEng);
DMX_FILTER_STATUS _MApi_DMX_Pcr_Eng_Get(MS_U8 u8Eng, MS_U32* pu32Pcr32, MS_U32* pu32Pcr);
DMX_FILTER_STATUS _MApi_DMX_Proc(MS_U8 u8DmxId, DMX_EVENT* pEvent);
DMX_FILTER_STATUS _MApi_DMX_Parl_Invert(DMX_FLOW DmxFlow, MS_BOOL bInvert);
DMX_FILTER_STATUS _MApi_DMX_CopyData(MS_U8 u8DmxId, MS_U8* pu8Buf, MS_U32 u32BufSize, MS_U32* pu32ActualSize, MS_U32* pu32RmnSize, DMX_CheckCb pfCheckCB);
void              _MApi_DMX_WriteProtect_Enable(MS_BOOL bEnable, MS_U32* pu32StartAddr, MS_U32* pu32EndAddr);
void              _MApi_DMX_OrzWriteProtect_Enable(MS_BOOL bEnable, MS_U32 u32StartAddr, MS_U32 u32EndAddr);
DMX_FILTER_STATUS _MApi_DMX_FlowEnable(DMX_FLOW DmxFlow, MS_BOOL bEnable);
DMX_FILTER_STATUS _MApi_DMX_Read_DropPktCnt(MS_U16* pu16ADropCnt, MS_U16* pu16VDropCnt);
DMX_FILTER_STATUS _MApi_DMX_SetOwner(MS_U8 u8DmxIdStart, MS_U8 u8DmxIdEnd, MS_BOOL bOwner);
DMX_FILTER_STATUS _MApi_DMX_GetOwner(MS_U8 u8DmxId, MS_BOOL* pbOwner);
DMX_FILTER_STATUS _MApi_DMX_GetAccess(MS_U32 u32Try);
DMX_FILTER_STATUS _MApi_DMX_ReleaseAccess(void);
DMX_FILTER_STATUS _MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE DmxFltType, MS_BOOL bReset);
DMX_FILTER_STATUS _MApi_DMX_AVFifo_Status(DMX_FILTER_TYPE DmxFltType, DMX_FIFO_STATUS* u32FifoLevel);
DMX_FILTER_STATUS _MApi_DMX_GetLibVer(const MSIF_Version **ppVersion);
DMX_FILTER_STATUS _MApi_DMX_GetCap(DMX_QUERY_TYPE DmxQueryType, void* pOutput);
DMX_FILTER_STATUS _MApi_DMX_SetBurstLen(DMX_BURSTTYPE BurstType);
DMX_FILTER_STATUS _MApi_DMX_GetFileInTimeStamp(MS_U32 *pu32FileInTS);
DMX_FILTER_STATUS _MApi_DMX_Filein_GetReadAddr(MS_U32* pu32Read);
void              _MApi_DMX_BypassFileInTimeStamp(MS_BOOL bbypass);
DMX_FILTER_STATUS _MApi_TSP_Get_FW_VER(MS_U32* u32FWVer);
DMX_FILTER_STATUS _MApi_DMX_RemoveDupAVPkt(MS_BOOL bEnable);
DMX_FILTER_STATUS _MApi_DMX_RemoveDupAVFifoPkt(DMX_FILTER_TYPE DmxFltType, MS_BOOL bEnable);
DMX_FILTER_STATUS _MApi_DMX_SetPacketMode(DMX_FLOW DmxFlow, DMX_PacketMode ePktMode);
DMX_FILTER_STATUS _MApi_DMX_SetMergeStrSyncByte(MS_U32 u32SrcID, MS_U8 u8SyncByte);
DMX_FILTER_STATUS _MApi_DMX_Change_FilterSource(MS_U8 u8DmxId, DMX_FILTER_TYPE DmxFltSrcType);
DMX_FILTER_STATUS _MApi_DMX_SetDbgLevel(DMX_DBGMSG_LEVEL level);
DMX_FILTER_STATUS _MApi_DMX_STC64_Mode_Enable(MS_BOOL bEnable);
MS_BOOL           _MApi_DMX_MMFI_Filein_IsIdle(DMX_MMFI_PATH ePath);
MS_BOOL           _MApi_DMX_MMFI_Filein_IsBusy(DMX_MMFI_PATH ePath);
DMX_FILTER_STATUS _MApi_DMX_MMFI_Filein_CMDQ_Reset(DMX_MMFI_PATH ePath);
DMX_FILTER_STATUS _MApi_DMX_MMFI_Filein_CMDQ_GetEmptyNum(DMX_MMFI_PATH ePath, MS_U32 *pu32EmptySlot);
DMX_FILTER_STATUS _MApi_DMX_MMFI_Filein_Start(DMX_MMFI_DST eDst, MS_PHYADDR pBuf, MS_U32 u32BufSize);
DMX_FILTER_STATUS _MApi_DMX_MMFI_GetFileInTimeStamp(DMX_MMFI_PATH ePath, MS_U32 *pu32FileInTS);
DMX_FILTER_STATUS _MApi_DMX_MMFI_Pid_Open(DMX_MMFI_FLTTYPE flttype, MS_U16 u16Pid, MS_U8* pu8DmxId);
DMX_FILTER_STATUS _MApi_DMX_MMFI_Pid_Close(MS_U8 u8DmxId);
DMX_FILTER_STATUS _MApi_DMX_MMFI_Filein_CMDQ_FIFOWriteLevel(DMX_MMFI_PATH ePath, MS_U8 *pu8CmdQStatus);
DMX_FILTER_STATUS _MApi_DMX_MMFI_SetPlaybackTimeStamp(DMX_MMFI_PATH ePath, MS_U32 u32pcr2);
DMX_FILTER_STATUS _MApi_DMX_MMFI_GetPlaybackTimeStamp(DMX_MMFI_PATH ePath, MS_U32 *pu32pcr2);
DMX_FILTER_STATUS _MApi_DMX_MMFI_TimeStampClk(DMX_MMFI_PATH ePath, DMX_TimeStamp_Clk eClk);
DMX_FILTER_STATUS _MApi_DMX_MMFI_RemoveDupAVPkt(MS_BOOL bEnable);
DMX_FILTER_STATUS _MApi_DMX_MMFI_MOBF_Enable(DMX_MMFI_PATH ePath, MS_BOOL bEnable, MS_U32 u32key);
DMX_FILTER_STATUS _MApi_DMX_Pvr_Eng_MOBF_Enable(MS_U8 u8Eng, MS_BOOL bEnable, MS_U32 u32key0, MS_U32 u32key1);
DMX_FILTER_STATUS _MApi_DMX_Filein_MOBF_Enable(MS_BOOL bEnable, MS_U32 u32key);
DMX_FILTER_STATUS _MApi_DMX_Pvr_Eng_Open(DMX_PVR_ENG Eng ,DMX_Pvr_info* pPvrInfo);
DMX_FILTER_STATUS _MApi_DMX_Pvr_Eng_Close(DMX_PVR_ENG Eng );
DMX_FILTER_STATUS _MApi_DMX_Pvr_Eng_Pid_Open(DMX_PVR_ENG Eng ,MS_U32 Pid, MS_U8* pu8DmxId);
DMX_FILTER_STATUS _MApi_DMX_Pvr_Eng_Pid_Close(DMX_PVR_ENG Eng ,MS_U8 u8DmxId);
DMX_FILTER_STATUS _MApi_DMX_Pvr_Eng_Start(DMX_PVR_ENG Eng, MS_BOOL bPvrAll);
DMX_FILTER_STATUS _MApi_DMX_Pvr_Eng_Stop(DMX_PVR_ENG Eng);
DMX_FILTER_STATUS _MApi_DMX_Pvr_Eng_WriteGet(DMX_PVR_ENG Eng ,MS_U32* pu32Write);
DMX_FILTER_STATUS _MApi_DMX_Pvr_Eng_SetPacketMode(DMX_PVR_ENG Eng ,MS_BOOL bSet);
DMX_FILTER_STATUS _MApi_DMX_Pvr_Eng_SetRecordStamp(DMX_PVR_ENG Eng ,MS_U32 u32Stamp);
DMX_FILTER_STATUS _MApi_DMX_Pvr_Eng_GetRecordStamp(DMX_PVR_ENG Eng ,MS_U32* pu32Stamp);
DMX_FILTER_STATUS _MApi_DMX_Pvr_Eng_SetPlaybackStampClk(MS_U8 u8Eng, DMX_TimeStamp_Clk eClkSrc);
DMX_FILTER_STATUS _MApi_DMX_Pvr_Eng_SetRecordStampClk(DMX_PVR_ENG Eng, DMX_TimeStamp_Clk eClkSrc);
DMX_FILTER_STATUS _MApi_DMX_Pvr_Eng_CallbackSize(DMX_PVR_ENG Eng, MS_U32* pu32CallbackSize, MS_BOOL bSet);
DMX_FILTER_STATUS _MApi_DMX_Pvr_Eng_SetCaMode(DMX_PVR_ENG Eng, DMX_CA_PVRMODE eCaMode, MS_BOOL bspsEnable);
DMX_FILTER_STATUS _MApi_DMX_Pvr_Eng_IsStart(DMX_PVR_ENG Eng, MS_BOOL *pbIsStart);
DMX_FILTER_STATUS _MApi_DMX_TSO_Filein_Info(MS_U8 u8Eng, DMX_Filein_info *pFileinInfo);
MS_BOOL           _MApi_DMX_TSO_Filein_IsIdle(MS_U8 u8Eng);
DMX_FILTER_STATUS _MApi_DMX_TSO_Filein_CMDQ_GetEmptyNum(MS_U8 u8Eng, MS_U32 *pu32EmptySlot);
DMX_FILTER_STATUS _MApi_DMX_TSO_Filein_CMDQ_Reset(MS_U8 u8Eng);
DMX_FILTER_STATUS _MApi_DMX_TSO_Filein_Start(MS_U8 u8Eng, MS_PHYADDR pBuf, MS_U32 u32BufSize);
DMX_FILTER_STATUS _MApi_DMX_TSO_Filein_Stop(MS_U8 u8Eng);
DMX_FILTER_STATUS _MApi_DMX_TSO_SetPlaybackTimeStamp(MS_U8 u8Eng, MS_U32 u32Stamp);
DMX_FILTER_STATUS _MApi_DMX_TSO_GetPlaybackStamp(MS_U8 u8Eng, MS_U32* pu32Stamp);
DMX_FILTER_STATUS _MApi_DMX_TSO_GetFileInTimeStamp(MS_U8 u8Eng, MS_U32 *pu32Stamp);
DMX_FILTER_STATUS _MApi_DMX_TSO_BypassFileInTimeStamp(MS_U8 u8Eng, MS_BOOL bbypass);
DMX_FILTER_STATUS _MApi_DMX_TSO_TimeStampEnable(MS_U8 u8Eng);
DMX_FILTER_STATUS _MApi_DMX_TSO_TimeStampDisable(MS_U8 u8Eng);
DMX_FILTER_STATUS _MApi_DMX_TSO_SetOutClk(MS_U8 u8Eng, DMX_TSO_OutClk eTsOutClk, DMX_TSO_OutClkSrc eTsOutClkSrc, MS_U16 u16DivNum, MS_BOOL bClkInv);
DMX_FILTER_STATUS _MApi_DMX_TSO_LocalStreamId(MS_U8 u8Eng, DMX_TSO_InputIf eIf, MS_U8* pu8StrId, MS_BOOL bSet);

DMX_FILTER_STATUS _MApi_DMX_LiveSrcSwitch(DMX_FILTER_TYPE TgtFlow);
DMX_FILTER_STATUS _MApi_DMX_AU_BD_Mode_Enable(MS_BOOL bEnable);
DMX_FILTER_STATUS _MApi_DMX_CMD_Run(MS_U32 u32Cmd, MS_U32 u32Config, MS_U32 u32DataNum, void *pData);
MS_U32            _MApi_DMX_SetPowerState(EN_POWER_MODE u16PowerState, MS_U32 u32FWAddr, MS_U32 u32FWSize);
DMX_FILTER_STATUS _MApi_DMX_Get_DisContiCnt(DMX_DisContiCnt_info* pDmxInfo, MS_U32* pu32Cnt);
DMX_FILTER_STATUS _MApi_DMX_Get_DropPktCnt(DMX_DropPktCnt_info* pDmxInfo, MS_U32* pu32Cnt);
DMX_FILTER_STATUS _MApi_DMX_Get_LockPktCnt(DMX_LockPktCnt_info* pDmxInfo, MS_U32* pu32Cnt);
DMX_FILTER_STATUS _MApi_DMX_Get_AVPktCnt(DMX_AVPktCnt_info* DmxInfo, MS_U32* pu32Cnt);
DMX_FILTER_STATUS _MApi_DMX_Get_SecTEI_PktCount(DMX_FILTER_TYPE FltSrc, MS_U32* pu32PktCnt);
DMX_FILTER_STATUS _MApi_DMX_Reset_SecTEI_PktCount(DMX_FILTER_TYPE FltSrc);
DMX_FILTER_STATUS _MApi_DMX_Get_SecDisCont_PktCount(MS_U32 u32DmxID, MS_U32* pu32PktCnt);
DMX_FILTER_STATUS _MApi_DMX_Reset_SecDisCont_PktCount(MS_U32 u32DmxID);

DMX_FILTER_STATUS _MApi_DMX_FQ_SetFltRushPass(MS_U8 u8DmxId, MS_U8 u8Enable);
DMX_FILTER_STATUS _MApi_DMX_FQ_Init(MS_U32 u32FQEng, DMX_FQ_Info* pFQInfo);
DMX_FILTER_STATUS _MApi_DMX_FQ_Exit(MS_U32 u32FQEng);
DMX_FILTER_STATUS _MApi_DMX_FQ_RushEnable(MS_U32 u32FQEng);
DMX_FILTER_STATUS _MApi_DMX_FQ_SkipRushData(MS_U32 u32FQEng, DMX_FQ_SkipPath eSkipPath);

#ifdef __cplusplus
}
#endif

#endif //_DMX_PRIV_H_

