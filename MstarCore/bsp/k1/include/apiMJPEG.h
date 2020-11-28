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
MJPEG_Result MApi_MJPEG_Init(MJPEG_INIT_PARAM *pInitParam);
MJPEG_Result MApi_MJPEG_Rst(void);
MJPEG_Result MApi_MJPEG_Stop(void);
MJPEG_Result MApi_MJPEG_CheckDispInfoRdy(void);
// Decode control
MJPEG_Result MApi_MJPEG_Play(void);
MJPEG_Result MApi_MJPEG_Pause(void);
MJPEG_Result MApi_MJPEG_Resume(void);
MJPEG_Result MApi_MJPEG_StepPlay(void);
MS_BOOL MApi_MJPEG_IsStepPlayDone(void);
MJPEG_Result MApi_MJPEG_StepDecode(void);
MS_BOOL MApi_MJPEG_IsStepDecodeDone(void);
// Data control
//MJPEG_Result MApi_MJPEG_PushQueue(MS_PHYADDR u32StAddr, MS_U32 u32Size, MS_U32 u32TimeStamp);
MJPEG_Result MApi_MJPEG_PushQueue(MJPEG_Packet_Info *pInfo);
MS_U32 MApi_MJPEG_GetQueueVacancy(void);
MJPEG_Result MApi_MJPEG_FlushQueue(void);
MS_U32 MApi_MJPEG_GetESWritePtr(void);
MS_U32 MApi_MJPEG_GetESReadPtr(void);
// Display control
MJPEG_Result MApi_MJPEG_EnableLastFrameShow(MS_BOOL bEnable);
MS_BOOL MApi_MJPEG_IsDispFinish(void);
MJPEG_Result MApi_MJPEG_SetSpeed(MJPEG_SpeedType eSpeedType, MJPEG_DispSpeed eDispSpeed);
MJPEG_Result MApi_MJPEG_SetFreezeDisp(MS_BOOL bEnable);
MJPEG_Result MApi_MJPEG_SetBlueScreen(MS_BOOL bOn);
// AV Sync
MJPEG_Result MApi_MJPEG_ResetPTS(MS_U32 u32PtsBase);
MS_U32 MApi_MJPEG_GetPTS(void);
MJPEG_Result MApi_MJPEG_AVSyncOn(MS_BOOL bOn, MS_U32 u32SyncDelay, MS_U16 u16SyncTolerance);
MS_BOOL MApi_MJPEG_IsAVSyncOn(void);
MS_BOOL MApi_MJPEG_IsReachSync(void);
// Get Info
MS_BOOL MApi_MJPEG_GetStatus(MJPEG_Status *pStatus);
MS_U32 MApi_MJPEG_GetErrCode(void);
MS_U32 MApi_MJPEG_GetErrCnt(void);
MS_U32 MApi_MJPEG_GetFrameCnt(void);
MJPEG_Result MApi_MJPEG_GetDispInfo(MJPEG_DISP_INFO *pInfo);
MS_BOOL MApi_MJPEG_IsPlaying(void);
MS_BOOL MApi_MJPEG_IsIdle(void);
MS_BOOL MApi_MJPEG_IsIFrameFound(void);
MS_BOOL MApi_MJPEG_IsWithLowDelay(void);
MJPEG_Result MApi_MJPEG_GetDecFrameInfo(MJPEG_FrameInfo *pFrmInfo);
MJPEG_Result MApi_MJPEG_GetDispFrameInfo(MJPEG_FrameInfo *pFrmInfo);
// Debug
void MApi_MJPEG_DbgSetMsgLevel(MJPEG_DbgLevel eDbgLevel);
MJPEG_Result MApi_MJPEG_DbgSetData(MS_PHYADDR u32Addr, MS_U32 u32Data);
MJPEG_Result MApi_MJPEG_DbgGetData(MS_PHYADDR u32Addr, MS_U32* u32Data);

// Display Control
MJPEG_Result MApi_MJPEG_EnableDispCmdQ(MS_BOOL bEnable);
MJPEG_Result MApi_MJPEG_PushDispCmdQ(void);
MS_U32 MApi_MJPEG_GetDispCmdQVacancy(void);

MJPEG_Result MApi_MJPEG_DispFrame(MS_U32 u32DispIdx);
MJPEG_Result MApi_MJPEG_FreeFrame(MS_U32 u32DispIdx);
MJPEG_Result MApi_MJPEG_GetNextDispFrame(MJPEG_FrameInfo *pFrmInfo);
MS_U32 MApi_MJPEG_GetNextDispQPtr(void);

//
MJPEG_Result MApi_MJPEG_SeekToPTS(MS_U32 u32PTS);
MJPEG_Result MApi_MJPEG_SkipToPTS(MS_U32 u32PTS);

void MApi_MJPEG_EnableTurboFWMode(MS_BOOL bEnable);

#ifdef __cplusplus
}
#endif

#endif // _API_MJPEG_H_

