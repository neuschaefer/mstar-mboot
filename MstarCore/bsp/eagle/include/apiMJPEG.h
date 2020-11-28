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

//for Dual Decode
typedef enum
{
    E_MJPEG_API_STREAM_NONE = 0,
    E_MJPEG_API_MAIN_STREAM,
    E_MJPEG_API_SUB_STREAM
} MJPEG_API_StreamType;


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
    MS_PHYADDR u32LumaAddr;     /// frame buffer base + the start offset of current displayed luma data. Unit: byte.
    MS_PHYADDR u32ChromaAddr;   /// frame buffer base + the start offset of current displayed chroma data. Unit: byte.
    MS_U32 u32TimeStamp;        /// Time stamp(DTS, PTS) of current displayed frame. Unit: ms (todo: 90khz)
    MS_U32 u32ID_L;              /// low part of ID number
    MS_U32 u32ID_H;              /// high part of ID number
    MS_U16 u16Pitch;             /// pitch
    MS_U16 u16Width;             /// width
    MS_U16 u16Height;            /// hight
    MJPEG_FrameType  eFrameType;///< Frame type: I, P, B frame
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
MJPEG_Result MApi_MJPEG_Init(MS_U32 u32Id, MJPEG_INIT_PARAM *pInitParam);
MJPEG_Result MApi_MJPEG_Rst(MS_U32 u32Id);
MJPEG_Result MApi_MJPEG_Stop(MS_U32 u32Id);
MJPEG_Result MApi_MJPEG_CheckDispInfoRdy(void);
// Decode control
MJPEG_Result MApi_MJPEG_Play(MS_U32 u32Id);
MJPEG_Result MApi_MJPEG_Pause(MS_U32 u32Id);
MJPEG_Result MApi_MJPEG_Resume(MS_U32 u32Id);
MJPEG_Result MApi_MJPEG_StepPlay(MS_U32 u32Id);
MS_BOOL MApi_MJPEG_IsStepPlayDone(MS_U32 u32Id);
MJPEG_Result MApi_MJPEG_StepDecode(MS_U32 u32Id);
MS_BOOL MApi_MJPEG_IsStepDecodeDone(MS_U32 u32Id);
// Data control
//MJPEG_Result MApi_MJPEG_PushQueue(MS_PHYADDR u32StAddr, MS_U32 u32Size, MS_U32 u32TimeStamp);
MJPEG_Result MApi_MJPEG_PushQueue(MS_U32 u32Id, MJPEG_Packet_Info *pInfo);
MS_U32 MApi_MJPEG_GetQueueVacancy(MS_U32 u32Id);
MJPEG_Result MApi_MJPEG_FlushQueue(MS_U32 u32Id);
MS_U32 MApi_MJPEG_GetESWritePtr(MS_U32 u32Id);
MS_U32 MApi_MJPEG_GetESReadPtr(MS_U32 u32Id);
// Display control
MJPEG_Result MApi_MJPEG_EnableLastFrameShow(MS_U32 u32Id, MS_BOOL bEnable);
MS_BOOL MApi_MJPEG_IsDispFinish(MS_U32 u32Id);
MJPEG_Result MApi_MJPEG_SetSpeed(MS_U32 u32Id, MJPEG_SpeedType eSpeedType, MJPEG_DispSpeed eDispSpeed);
MJPEG_Result MApi_MJPEG_SetFreezeDisp(MS_U32 u32Id, MS_BOOL bEnable);
MJPEG_Result MApi_MJPEG_SetBlueScreen(MS_U32 u32Id, MS_BOOL bOn);
// AV Sync
MJPEG_Result MApi_MJPEG_ResetPTS(MS_U32 u32Id, MS_U32 u32PtsBase);
MS_U32 MApi_MJPEG_GetPTS(MS_U32 u32Id);
MJPEG_Result MApi_MJPEG_AVSyncOn(MS_U32 u32Id, MS_BOOL bOn, MS_U32 u32SyncDelay, MS_U16 u16SyncTolerance);
MS_BOOL MApi_MJPEG_IsAVSyncOn(MS_U32 u32Id);
MS_BOOL MApi_MJPEG_IsReachSync(MS_U32 u32Id);
// Get Info
MS_BOOL MApi_MJPEG_GetStatus(MJPEG_Status *pStatus);
MS_U32 MApi_MJPEG_GetErrCode(MS_U32 u32Id);
MS_U32 MApi_MJPEG_GetErrCnt(void);
MS_U32 MApi_MJPEG_GetFrameCnt(MS_U32 u32Id);
MJPEG_Result MApi_MJPEG_GetDispInfo(MS_U32 u32Id, MJPEG_DISP_INFO *pInfo);
MS_BOOL MApi_MJPEG_IsPlaying(MS_U32 u32Id);
MS_BOOL MApi_MJPEG_IsIdle(void);
MS_BOOL MApi_MJPEG_IsIFrameFound(void);
MS_BOOL MApi_MJPEG_IsWithLowDelay(void);
MJPEG_Result MApi_MJPEG_GetDecFrameInfo(MS_U32 u32Id, MJPEG_FrameInfo *pFrmInfo);
MJPEG_Result MApi_MJPEG_GetDispFrameInfo(MS_U32 u32Id, MJPEG_FrameInfo *pFrmInfo);
// Debug
void MApi_MJPEG_DbgSetMsgLevel(MJPEG_DbgLevel eDbgLevel);
MJPEG_Result MApi_MJPEG_DbgSetData(MS_PHYADDR u32Addr, MS_U32 u32Data);
MJPEG_Result MApi_MJPEG_DbgGetData(MS_PHYADDR u32Addr, MS_U32* u32Data);

// Display Control
MJPEG_Result MApi_MJPEG_EnableDispCmdQ(MS_U32 u32Id, MS_BOOL bEnable);
MJPEG_Result MApi_MJPEG_PushDispCmdQ(MS_U32 u32Id);
MS_U32 MApi_MJPEG_GetDispCmdQVacancy(MS_U32 u32Id);

MJPEG_Result MApi_MJPEG_DispFrame(MS_U32 u32Id, MS_U32 u32DispIdx);
MJPEG_Result MApi_MJPEG_FreeFrame(MS_U32 u32Id, MS_U32 u32DispIdx);
MJPEG_Result MApi_MJPEG_GetNextDispFrame(MS_U32 u32Id, MJPEG_FrameInfo *pFrmInfo);
MS_U32 MApi_MJPEG_GetNextDispQPtr(void);

//
MJPEG_Result MApi_MJPEG_SeekToPTS(MS_U32 u32Id, MS_U32 u32PTS);
MJPEG_Result MApi_MJPEG_SkipToPTS(MS_U32 u32Id, MS_U32 u32PTS);

void MApi_MJPEG_EnableTurboFWMode(MS_BOOL bEnable);

//for Dual Decode
MJPEG_Result MApi_MJPEG_GetFreeStream(MS_U32 *pu32Id, MJPEG_API_StreamType eStreamType);


#ifdef __cplusplus
}
#endif

#endif // _API_MJPEG_H_

