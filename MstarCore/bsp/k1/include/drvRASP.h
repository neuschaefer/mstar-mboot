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
///
/// file   drvRASP.h
/// @brief  RASP Driver Interface
/// @author MStar Semiconductor,Inc.
/// @attention
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVRASP_H_
#define _DRVRASP_H_

#ifdef __cplusplus
extern "C"
{
#endif

//--------------------------------------------------------------------------------------------------
//  Define
//--------------------------------------------------------------------------------------------------
#define RASP_PIDFLT_START_NUM        0
#define RASP_PIDFLT_END_NUM          24

#define RASP_PIDFLT_NUM_ALL          24

#ifdef HW_PVR_ENABLE
    #define PVR_PIDFLT_START_NUM        0
    #define PVR_PIDFLT_END_NUM          16

    #define PVR_PIDFLT_NUM_ALL          16
#endif //#endif HW_PVR_ENABLE

#define DRVRASP_PID_NULL             0x1FFF                                                 // Transport stream null PID
#define MSIF_RASP_LIB_CODE           {'R','A','S','P'}                                      // Lib code
#define MSIF_RASP_LIBVER             {'0','1'}                                              // LIB version
#define MSIF_RASP_BUILDNUM           {'0','2'}                                              // Build Number
#define MSIF_RASP_CHANGELIST         {'0','0','4','9','7','7','0','9'}                      // P4 ChangeList Number

#define RASP_DRV_VERSION                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                            /* 'MSIF'                                           */  \
    MSIF_CLASS,                          /* '00'                                             */  \
    MSIF_CUS,                            /* 0x0000                                           */  \
    MSIF_MOD,                            /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                   \
    MSIF_CPU,                                                                                    \
    MSIF_RASP_LIB_CODE,                  /* IP__                                             */  \
    MSIF_RASP_LIBVER,                    /* 0.0 ~ Z.Z                                        */  \
    MSIF_RASP_BUILDNUM,                  /* 00 ~ 99                                          */  \
    MSIF_RASP_CHANGELIST,                /* CL#                                              */  \
    MSIF_OS

//--------------------------------------------------------------------------------------------------
//  Driver Capability
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//  Type and Structure
//--------------------------------------------------------------------------------------------------

/// RASP DDI return value
/// @name TSP_Result
/// @ref TSP_Result
/// return value
/// @{
typedef enum
{
    DRVRASP_FAIL                   = 0,
    DRVRASP_OK,
    DRVRASP_INVALID_PARAM,
    DRVRASP_FUNC_ERROR,
} RASP_Result;

#define DrvRASP_Event                    MS_U32
#define E_DRVRASP_EVENT_DATA_INIT        0x00000000
/// PVR Buffer is Full
#define E_DRVRASP_EVENT_PVRBUF_FULL      0x00000001
/// PVR Double Buffer Overflow
#define E_DRVRASP_EVENT_PVRBUF_OVERFLOW  0x00000002

// Payload/Event Mask flag
//#define RASP_BYPASS_MASK            0xffffffff
#define E_DRVRASP_BYPASS_AFE             0x00000001      // adaptation field extension
#define E_DRVRASP_BYPASS_TPD             0x00000002      // transport private data
#define E_DRVRASP_BYPASS_SP              0x00000004      // splicing point
#define E_DRVRASP_BYPASS_OPCR            0x00000008      // OPCR
#define E_DRVRASP_BYPASS_PCR             0x00000010      // PCR
#define E_DRVRASP_BYPASS_ESPI            0x00000020      // elementary stream priority indicator
#define E_DRVRASP_BYPASS_RAI             0x00000040      // random access indicator
#define E_DRVRASP_BYPASS_DI              0x00000080      // discontinue indicator
#define E_DRVRASP_BYPASS_ESNS            0x00000100      // elementary stream not scrambled
#define E_DRVRASP_BYPASS_ESES            0x00000200      // elementary stream even scrambled
#define E_DRVRASP_BYPASS_ESOS            0x00000400      // elementary stream odd scrambled
#define E_DRVRASP_BYPASS_PUSI            0x00000800      // payload unit start indicator
#define E_DRVRASP_BYPASS_FPR             0x00001000      // first packet recorded
#define E_DRVRASP_BYPASS_RASP_Tick       0x80000000      // rasp tick

typedef enum
{
    E_DRVRASP_CAP_FILTER_NUM = 0,                                                                    // Get filter number
    E_DRVRASP_CAP_FILTER_PVR_NUM,                                                                    // Get pvr filter number
    E_DRVRASP_CAP_PVR_ALIGN,                                                                         // Get pvr buffer minimal alignment
} DrvRASP_Cap;

/// RASP channel state bit flags
typedef enum //_DrvTSP_FltState
{
    E_DRVRASP_FLT_STATE_FREE         = 0x00000000,                                                   ///<\n
    E_DRVRASP_FLT_STATE_ALLOC        = 0x00000001,                                                   ///<\n
    E_DRVRASP_FLT_STATE_ENABLE       = 0x00000002,                                                   ///<\n
    E_DRVRASP_FLT_STATE_OVERFLOW     = 0x00010000,                                                   //[Reserved]
    E_DRVRASP_FLT_STATE_NA           = 0xFFFFFFFF,
} DrvRASP_FltState;

/// TSP record mode
typedef enum //_DrvRASP_RecMode
{
    // Record PID
    E_DRVRASP_REC_MODE_PID  = 0x00000000,
    // Record ALL
    E_DRVRASP_REC_MODE_ALL  = 0x00000001,
} DrvRASP_RecMode;

/// TSP interface
typedef enum
{
    E_DRVRASP_IF_PLAYBACK            = 0x0, // TS interface 0
    E_DRVRASP_IF_PVR0                = 0x1, // TS interface 1, mainly for PVR
} DrvRASP_If;

typedef struct //_DrvRASP_Msg
{
    /// Union data type of message
    union
    {
        /// FltInfo message
        ///   - Byte[0] : Section filter id
        ///   - Byte[1] : TSP id
        MS_U32                          FltInfo;
        /// PvrBufId
        ///   - Byte[0] : PVR buffer id
        MS_U32                          PvrBufId;
    };

} DrvRASP_Msg;

typedef enum //_DrvRASP_RecType
{
    STR2MIU          = 0x0,
    PAYLOAD2MIU      = 0x1,
    ECM2MIU          = 0x2,
} DrvRASP_RecType;

/// TSP notification function
typedef void (*P_DrvRASP_EvtCallback)(DrvRASP_Event eEvent, DrvRASP_Msg *pMsg);

//--------------------------------------------------------------------------------------------------
//  Function Prototype
//--------------------------------------------------------------------------------------------------

// Initialization API
RASP_Result MDrv_RASP_Init(void);
RASP_Result MDrv_RASP_Exit(void);
RASP_Result MDrv_RASP_Reset(void);
RASP_Result MDrv_RASP_Alive(void);
RASP_Result MDrv_RASP_ReplacePackets(void);
RASP_Result MDrv_RASP_Confi(void);
RASP_Result MDrv_RASP_PVR_SetTSIF(MS_U32 u32RASPEng, MS_BOOL bPara, MS_BOOL bExtSync, MS_BOOL bDataSWP);
RASP_Result MDrv_RASP_PVR_FileinEnable(MS_U32 u32RASPEng, MS_BOOL bEn);

// Capacity query
RASP_Result MDrv_RASP_GetCap(DrvRASP_Cap eCap, void* pOutput);
RASP_Result MDrv_RASP_GetLibVer(const MSIF_Version **ppVersion);
RASP_Result MDrv_RASP_GetTimerAndPacketNum(const MSIF_Version **ppVersion);
RASP_Result MDrv_RASP_GetTsPayload(const MSIF_Version **ppVersion);
RASP_Result MDrv_RASP_GetEventMask(const MSIF_Version **ppVersion);

// PVR API
RASP_Result MDrv_RASP_PVR_SetBuffer(MS_U32 u32RASPEng, MS_PHYADDR u32BufStart0, MS_PHYADDR u32BufStart1, MS_U32 u32BufSize0, MS_U32 u32BufSize1);
RASP_Result MDrv_RASP_PVR_Start(MS_U32 u32RASPEng, DrvRASP_RecMode eRecMode, MS_BOOL bStart);
RASP_Result MDrv_RASP_PVR_Pause(MS_U32 u32RASPEng, MS_BOOL bPause);
RASP_Result MDrv_RASP_PVR_GetWriteAddr(MS_U32 u32RASPEng, MS_PHYADDR *pu32WriteAddr);
RASP_Result MDrv_RASP_PVR_Notify(MS_U32 u32RASPEng, DrvRASP_Event eEvents, P_DrvRASP_EvtCallback pfCallback);
RASP_Result MDrv_RASP_PVR_SetPacketMode(MS_U32 u32RASPEng, DrvRASP_RecType eRecType,MS_BOOL bSet);
RASP_Result MDrv_RASP_PVR_TimeStampSetRecordStamp(MS_U32 u32RASPEng, MS_U32 u32Stamp);
RASP_Result MDrv_RASP_PVR_TimeStampGetRecordStamp(MS_U32 u32RASPEng, MS_U32* u32Stamp);
RASP_Result MDrv_RASP_PVR_AllocFlt(MS_U32 u32RASPEng, MS_U32 *pu32PidFltId);
RASP_Result MDrv_RASP_PVR_SetPid(MS_U32 u32RASPEng, MS_U16 u16Fltid, MS_U16 u16Pid);
RASP_Result MDrv_RASP_PVR_ReleaseFlt(MS_U32 u32RASPEng, MS_U16 u32FltId);
//RASP_Result MDrv_RASP_PVR_TimeStampSetPlaybackStamp(MS_U32 u32Stamp);
//RASP_Result MDrv_RASP_PVR_TimeStampGetPlaybackStamp(MS_U32* u32Stamp);
//RASP_Result MDrv_RASP_PVR_TimeStamp(MS_BOOL bEnable);

// RASP API
RASP_Result MDrv_RASP_SetEvent(MS_U32 u32RASPEng, MS_U16 u16Flt, MS_U32 u32Event);
RASP_Result MDrv_RASP_SetPayload(MS_U32 u32RASPEng, MS_U16 u16Flt, MS_U32 u32Payload);
RASP_Result MDrv_RASP_SetDataSwap(MS_U32 u32RASPEng, MS_BOOL bEn);
#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif // _DRVRASP_H_
