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
///
/// file    apiMJPEG.h
/// @brief  MJPEG API
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _API_MJPEG_H_
#define _API_MJPEG_H_

#include "MsCommon.h"


#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

typedef enum
{
    E_MJPEG_RET_FAIL                    = 0,
    E_MJPEG_RET_SUCCESS,
    E_MJPEG_RET_INVALID_PARAMETER,
    E_MJPEG_RET_DECODE_HDR_ERROR,
    E_MJPEG_RET_DECODE_ERROR,
    E_MJPEG_RET_DECODING,
} MJPEG_Result;

typedef enum
{
    E_MJPEG_SPEED_DEFAULT = 0,
    E_MJPEG_SPEED_FAST,
    E_MJPEG_SPEED_SLOW
} MJPEG_SpeedType;

typedef enum
{
    /// Normal display speed.
    E_MJPEG_DISP_SPEED_1X = 1,
    /// 2X
    E_MJPEG_DISP_SPEED_2X = 2,
    /// 4X
    E_MJPEG_DISP_SPEED_4X = 4,
    /// 8X
    E_MJPEG_DISP_SPEED_8X = 8,
    /// 16X
    E_MJPEG_DISP_SPEED_16X = 16,
    /// 32X
    E_MJPEG_DISP_SPEED_32X = 32,
} MJPEG_DispSpeed;

typedef enum
{
    /// disable all uart message.
    E_MJPEG_DBG_LEVEL_NONE = 0,
    /// Only output error message
    E_MJPEG_DBG_LEVEL_ERR,
    /// output general message, and above.
    E_MJPEG_DBG_LEVEL_INFO,
    /// output debug message, and above.
    E_MJPEG_DBG_LEVEL_DBG,
    /// output function tracing message, and above.
    E_MJPEG_DBG_LEVEL_TRACE,
    /// output FW message.
    E_MJPEG_DBG_LEVEL_FW,
} MJPEG_DbgLevel;

typedef enum
{
    E_MJPEG_FW_SOURCE_NONE,       ///< No input fw.
    E_MJPEG_FW_SOURCE_DRAM,       ///< input source from DRAM.
    E_MJPEG_FW_SOURCE_FLASH,      ///< input source from FLASH.
} MJPEG_FWSourceType;

typedef enum
{
    E_MJPEG_ERROR_CODE_NONE = 0,
    E_MJPEG_ERR_CODE_RES,
} MJPEG_ErrorCode;

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef struct
{
    MS_PHYADDR u32FwBinAddr;        // Address of firmware binary
    MS_U32 u32FwBinSize;            // Size of firmware binary
    MS_PHYADDR u32FwAddr;           // Address to load firmware
    MS_U32 u32FwSize;               // Firmware size
    MS_PHYADDR u32MRCBufAddr;       // MRC buffer address
    MS_U32 u32MRCBufSize;           // MRC buffer size
    MS_PHYADDR u32MWCBufAddr;       // MWC buffer address
    MS_U32 u32MWCBufSize;           // MWC buffer size
    MS_PHYADDR u32InternalBufAddr;  // internal buffer address
    MS_U32 u32InternalBufSize;      // internal buffer size
    //MS_U32 u32FrameTime;            // frame time
    MS_U32 u32FrameRate;
    MS_U32 u32FrameRateBase;
    MJPEG_FWSourceType eFwSrcType;  // the input FW source type.
    MS_U32 u32Width;
    MS_U32 u32Height;
} MJPEG_INIT_PARAM;

typedef struct
{
    MS_U16 u16Width;
    MS_U16 u16Height;
    MS_U32 u32FrameRate;
    MS_U16 u16CropRight;
    MS_U16 u16CropLeft;
    MS_U16 u16CropBottom;
    MS_U16 u16CropTop;
    MS_U16 u16Pitch;
} MJPEG_DISP_INFO;

typedef enum
{
    E_MJPEG_STAGE_STOP = 0,
    E_MJPEG_STAGE_INIT,
    E_MJPEG_STAGE_PLAY,
    E_MJPEG_STAGE_PAUSE,
} MJPEG_Stage;

typedef struct
{
    MS_BOOL bInit;
    MS_BOOL bIdle;
    MJPEG_Stage  eStage;
} MJPEG_Status;

typedef enum
{
    E_MJPEG_FRM_TYPE_I      = 0,
    //E_MJPEG_FRM_TYPE_P,
    //E_MJPEG_FRM_TYPE_B,
    E_MJPEG_FRM_TYPE_OTHER  = 3,
} MJPEG_FrameType;

/// frame information
typedef struct
{
    /// frame buffer base + the start offset of current displayed luma data. Unit: byte.
    MS_PHYADDR u32LumaAddr;
    /// frame buffer base + the start offset of current displayed chroma data. Unit: byte.
    MS_PHYADDR u32ChromaAddr;
    /// Time stamp(DTS, PTS) of current displayed frame. Unit: ms (todo: 90khz)
    MS_U32 u32TimeStamp;
    /// low part of ID number
    MS_U32 u32ID_L;
    /// high part of ID number
    MS_U32 u32ID_H;
    /// pitch
    MS_U16 u16Pitch;
    /// width
    MS_U16 u16Width;
    /// hight
    MS_U16 u16Height;
    ///< Frame type: I, P, B frame
    MJPEG_FrameType eFrameType;
} MJPEG_FrameInfo;

typedef struct
{
    MS_U32 u32StAddr;       ///< Packet offset from bitstream buffer base address. unit: byte.
    MS_U32 u32Size;         ///< Packet size. unit: byte.
    MS_U32 u32TimeStamp;    ///< Packet time stamp. unit: ms.
    MS_U32 u32ID_L;         ///< Packet ID low part.
    MS_U32 u32ID_H;         ///< Packet ID high part.
} MJPEG_Packet_Info;


//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
// Init
DLL_PUBLIC MJPEG_Result MApi_MJPEG_Init(MJPEG_INIT_PARAM *pInitParam);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_Rst(void);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_Stop(void);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_CheckDispInfoRdy(void);
// Decode control
DLL_PUBLIC MJPEG_Result MApi_MJPEG_Play(void);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_Pause(void);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_Resume(void);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_StepPlay(void);
DLL_PUBLIC MS_BOOL MApi_MJPEG_IsStepPlayDone(void);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_StepDecode(void);
DLL_PUBLIC MS_BOOL MApi_MJPEG_IsStepDecodeDone(void);
// Data control
//MJPEG_Result MApi_MJPEG_PushQueue(MS_PHYADDR u32StAddr, MS_U32 u32Size, MS_U32 u32TimeStamp);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_PushQueue(MJPEG_Packet_Info *pInfo);
DLL_PUBLIC MS_U32 MApi_MJPEG_GetQueueVacancy(void);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_FlushQueue(void);
DLL_PUBLIC MS_U32 MApi_MJPEG_GetESWritePtr(void);
DLL_PUBLIC MS_U32 MApi_MJPEG_GetESReadPtr(void);
// Display control
DLL_PUBLIC MJPEG_Result MApi_MJPEG_EnableLastFrameShow(MS_BOOL bEnable);
DLL_PUBLIC MS_BOOL MApi_MJPEG_IsDispFinish(void);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_SetSpeed(MJPEG_SpeedType eSpeedType, MJPEG_DispSpeed eDispSpeed);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_SetFreezeDisp(MS_BOOL bEnable);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_SetBlueScreen(MS_BOOL bOn);
// AV Sync
DLL_PUBLIC MJPEG_Result MApi_MJPEG_ResetPTS(MS_U32 u32PtsBase);
DLL_PUBLIC MS_U32 MApi_MJPEG_GetPTS(void);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_AVSyncOn(MS_BOOL bOn, MS_U32 u32SyncDelay, MS_U16 u16SyncTolerance);
DLL_PUBLIC MS_BOOL MApi_MJPEG_IsAVSyncOn(void);
DLL_PUBLIC MS_BOOL MApi_MJPEG_IsReachSync(void);
// Get Info
DLL_PUBLIC MS_BOOL MApi_MJPEG_GetStatus(MJPEG_Status *pStatus);
DLL_PUBLIC MS_U32 MApi_MJPEG_GetErrCode(void);
DLL_PUBLIC MS_U32 MApi_MJPEG_GetErrCnt(void);
DLL_PUBLIC MS_U32 MApi_MJPEG_GetFrameCnt(void);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_GetDispInfo(MJPEG_DISP_INFO *pInfo);
DLL_PUBLIC MS_BOOL MApi_MJPEG_IsPlaying(void);
DLL_PUBLIC MS_BOOL MApi_MJPEG_IsIdle(void);
DLL_PUBLIC MS_BOOL MApi_MJPEG_IsIFrameFound(void);
DLL_PUBLIC MS_BOOL MApi_MJPEG_IsWithLowDelay(void);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_GetDecFrameInfo(MJPEG_FrameInfo *pFrmInfo);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_GetDispFrameInfo(MJPEG_FrameInfo *pFrmInfo);
// Debug
DLL_PUBLIC void MApi_MJPEG_DbgSetMsgLevel(MJPEG_DbgLevel eDbgLevel);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_DbgSetData(MS_PHYADDR u32Addr, MS_U32 u32Data);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_DbgGetData(MS_PHYADDR u32Addr, MS_U32* u32Data);

// Display Control
DLL_PUBLIC MJPEG_Result MApi_MJPEG_EnableDispCmdQ(MS_BOOL bEnable);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_PushDispCmdQ(void);
DLL_PUBLIC MS_U32 MApi_MJPEG_GetDispCmdQVacancy(void);

DLL_PUBLIC MJPEG_Result MApi_MJPEG_DispFrame(MS_U32 u32DispIdx);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_FreeFrame(MS_U32 u32DispIdx);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_GetNextDispFrame(MJPEG_FrameInfo *pFrmInfo);
DLL_PUBLIC MS_U32 MApi_MJPEG_GetNextDispQPtr(void);

//
DLL_PUBLIC MJPEG_Result MApi_MJPEG_SeekToPTS(MS_U32 u32PTS);
DLL_PUBLIC MJPEG_Result MApi_MJPEG_SkipToPTS(MS_U32 u32PTS);

DLL_PUBLIC void MApi_MJPEG_EnableTurboFWMode(MS_BOOL bEnable);

#ifdef __cplusplus
}
#endif

#endif // _API_MJPEG_H_

