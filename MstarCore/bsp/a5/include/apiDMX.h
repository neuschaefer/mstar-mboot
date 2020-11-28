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
/// @file   apiDMX.h
/// @brief  Demux API
/// @author MStar Semiconductor,Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////



#ifndef __API_DMX_H__
#define __API_DMX_H__

#include "MsCommon.h"


#ifdef __cplusplus
extern "C"
{
#endif

/// NULL PID definition
#define DMX_PID_NULL               (0x1FFF)

// Please don't change this value if you know exactly what you are doing
/// DMX Filter pattern depth
#define DMX_SECT_FLT_DEPTH         (16)

/// NULL DMX Id
#define DMX_DMXID_NULL             ((MS_U8)0xFF)
#define MSIF_DMX_LIB_CODE                     {'D','M','X','_'}    //Lib code
#define MSIF_DMX_LIBVER                       {'1','3'}            //LIB version
#define MSIF_DMX_BUILDNUM                     {'2','2'}            //Build Number
#define MSIF_DMX_CHANGELIST                   {'0','0','5','9','7','9','0','5'} //P4 ChangeList Number

/// DMX Version
#define DMX_API_VERSION                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_DMX_LIB_CODE,                  /* IP__                                             */  \
    MSIF_DMX_LIBVER,                    /* 0.0 ~ Z.Z                                        */  \
    MSIF_DMX_BUILDNUM,                  /* 00 ~ 99                                          */  \
    MSIF_DMX_CHANGELIST,  /* CL#                                              */  \
    MSIF_OS

/// DMX status indicator
typedef enum
{
    DMX_FILTER_STATUS_OK,               ///< DMX status OK
    DMX_FILTER_STATUS_ERROR,            ///< DMX status ERROR
} DMX_FILTER_STATUS;

typedef enum
{
    DMX_DBG_NONE,
    DMX_DBG_ERR,
    DMX_DBG_WARN,
    DMX_DBG_INFO,    
    DMX_DBG_PVR,
    DMX_DBG_FUNC,
} DMX_DBGMSG_LEVEL;

#if defined(MINI_TSP)
// NOTE : This enum must sync with api/drv/hal layer
typedef enum
{
    DMX_TS_MAIN_PATH = 1, ///< main TS path
    DMX_TS_MM_PATH,        ///< MM TS path
} DMX_TS_PATH;
#endif

/// DMX internal startup parameter
typedef struct _DMX_FW_Param
{
    MS_PHYADDR                          phyFWAddr;
    MS_U32                              u32FWSize;

    MS_PHYADDR                          phyVQAddr;
    MS_U32                              u32VQSize;

    MS_U32                              _zero_reserved[4];

} DMX_TSPParam;


#if 0
/// DMX fitler type and source type
typedef enum
{
    DMX_FILTER_TYPE_VIDEO,              ///< DMX video filter type
    DMX_FILTER_TYPE_AUDIO,              ///< DMX audio filter type
    DMX_FILTER_TYPE_AUDIO2,             ///< DMX audio2 filter type
    DMX_FILTER_TYPE_SECTION,            ///< DMX section filter type
    DMX_FILTER_TYPE_PES,                ///< DMX PES filter type
    DMX_FILTER_TYPE_PACKET,             ///< DMX TS packet filter type
    DMX_FILTER_TYPE_PCR,                ///< DMX PCR filter type
    DMX_FILTER_TYPE_TELETEXT,           ///< DMX teletext filter type

    DMX_FILTER_SOURCE_TYPE_MASK  =  0xC0000000,              ///< DMX filter source mask
    DMX_FILTER_SOURCE_TYPE_LIVE  =  0x80000000,              ///< DMX live stream filter source
    DMX_FILTER_SOURCE_TYPE_FILE  =  0x40000000,              ///< DMX file in filter type
} DMX_FILTER_TYPE;
#endif

#define DMX_FILTER_TYPE MS_U32

#define DMX_FILTER_TYPE_VIDEO           0x00000000   ///< DMX video filter type
#define DMX_FILTER_TYPE_AUDIO           0x00000001   ///< DMX audio filter type
#define DMX_FILTER_TYPE_AUDIO2          0x00000002   ///< DMX audio2 filter type
#define DMX_FILTER_TYPE_SECTION         0x00000003   ///< DMX section filter type
#define DMX_FILTER_TYPE_PES             0x00000004   ///< DMX PES filter type
#define DMX_FILTER_TYPE_PACKET          0x00000005   ///< DMX TS packet filter type
#define DMX_FILTER_TYPE_PCR             0x00000006   ///< DMX PCR filter type
#define DMX_FILTER_TYPE_TELETEXT        0x00000007   ///< DMX teletext filter type
#define DMX_FILTER_TYPE_VIDEO3D         0x00000008   ///< DMX V3D filter type

#define DMX_FILTER_FLT_MASK                     0xF0000000
#define DMX_FILTER_SOURCE_TYPE_MASK             0xF0000000                   ///< DMX filter source mask
#define DMX_FILTER_SOURCE_TYPE_LIVE             0x80000000                   ///< DMX live stream filter source
#define DMX_FILTER_SOURCE_TYPE_FILE             0x40000000                   ///< DMX file in filter type
#define DMX_FILTER_SOURCE_TYPE_LIVEB            DMX_FILTER_SOURCE_TYPE_FILE  ///< Input from TS1 to File PID filter
#define DMX_FILTER_SOURCE_TYPE_TS1              0xC0000000                   ///< DMX live stream filter source 1
#define DMX_FILTER_SOURCE_TYPE_TS2              0xD0000000                   ///< DMX live stream filter source 2
#define DMX_FILTER_SOURCE_TYPE_TS3              0xE0000000                   ///< DMX live stream filter source 3

// Only supported by TSP ver2.0 driver
#define DMX_FILTER_SOURCE_TYPE_PLAYBACK DMX_FILTER_SOURCE_TYPE_LIVE
#define DMX_FILTER_SOURCE_TYPE_PVR0     0x20000000   ///< DMX PVR0 stream filter source
#define DMX_FILTER_SOURCE_TYPE_PVR1     0x10000000   ///< DMX PVR1 stream filter source

#define DMX_FILTER_FLT_SCMB_MASK   		        0x20000000
#define DMX_FILTER_FLT_TYPE_SCMB                0x20000000      ///< DMX descramble filter type
#define DMX_FILTER_FLT_TYPE_SCMB_SHAREKEY       0x10000000      ///< DMX descramble filter type with sharekey

// only one playback flow or PVR flow exist
// Playback flow and PVR flow can exist simultaneously
/// DMX flow type
typedef enum
{
    DMX_FLOW_PLAYBACK                         = 0,  ///< DMX playback flow
    DMX_FLOW_PVR,                                   ///< DMX recording flow
    DMX_FLOW_PVR1,                                  ///< DMX recording flow, note: Not support for all chip

    DMX_FLOW_PVRCA,                                 ///< CI+ PVR
    DMX_FLOW_FILEIN_MM,                             ///< DMX Filein flow with Main path Vido and MMFI path Audio
    DMX_FLOW_FILEIN_MM3D,                           ///< DMX Filein flow with Main path Video, MMFI path 3DVideo, and MMFI Audio 

    DMX_FLOW_CIPHSS_PLAYBACK,                       ///< Playback flow for CI+ HSS 2 path input from CAM.
    DMX_FLOW_CIPHSS_PVRCA,                          ///< PVR flow for CI+ HSS 2 path input from CAM.
    DMX_FLOW_PVR2,                                  ///< DMX recording flow, note: Not support for all chip, PVR2
    DMX_FLOW_PVR3,                                  ///< DMX recording flow, note: Not support for all chip
    DMX_FLOW_PVR4,                                  ///< DMX recording flow, note: Not support for all chip
    DMX_FLOW_PVR5,                                  ///< DMX recording flow, note: Not support for all chip

    DMX_FLOW_TSO_PLAYBACK,                          ///< DMX TSO playback flow (version 3.0)
    DMX_FLOW_PLAYBACK1,                             ///< DMX playback flow (version 3.0)
    DMX_FLOW_PVRCA1,                                ///< CI+ PVR (version 3.0)]
    DMX_FLOW_NUM,
} DMX_FLOW;

//MMFI2
#define DMX_FLOW_FILEIN0        DMX_FLOW_FILEIN_MM      ///< DMX Filein flow with MMFI 0           
#define DMX_FLOW_FILEIN1        DMX_FLOW_FILEIN_MM3D    ///< DMX Filein flow with MMFI 1

/// DMX input type
typedef enum
{
    DMX_FLOW_INPUT_DEMOD,               ///< DMX input from internal demod
    DMX_FLOW_INPUT_MEM,                 ///< DMX input from memory
    DMX_FLOW_INPUT_EXT_INPUT0,          ///< DMX input from external input 0
    DMX_FLOW_INPUT_EXT_INPUT1,          ///< DMX input from external input 1
    DMX_FLOW_INPUT_EXT_INPUT2,          ///< DMX input from external input 2. note: Not support for all chip
    DMX_FLOW_INPUT_EXT_INPUT3 ,         ///< DMX input from external input 3. note: Not support for all chip
    DMX_FLOW_INPUT_MEM_NOPASSCA,        ///< DMX input from memory, but not pass through CA
    DMX_FLOW_INPUT_TSO,                 ///< DMX input from TSO
    DMX_FLOW_INPUT_DISABLE,
} DMX_FLOW_INPUT;

typedef enum
{
    DMX_PVR_EGN0,
    DMX_PVR_EGN1,  
    DMX_PVR_EGN2,  
    DMX_PVR_EGN3,
    DMX_PVR_EGN4,
    DMX_PVR_EGN5,
} DMX_PVR_ENG;

#if 0
// make sure what you are doing before changing the value
/// DMX callback types
typedef enum
{
    DMX_EVENT_DATA_READY           = 0x00000001, ///< DMX event ready
    DMX_EVENT_BUF_OVERFLOW         = 0x00000002, ///< DMX event overflow
    DMX_EVENT_PVRBUF_FULL          = 0x00000010, ///< DMX event PVR buffer overflow

    /// TSP self task callback // optional --> default is CB by poll
    DMX_EVENT_CB_MASK              = 0x80000000, ///< DMX callback mask
    DMX_EVENT_CB_POLL              = 0x00000000, ///< DMX callback by polling // OBSOLETE
    DMX_EVENT_CB_SELF              = 0x80000000, ///< DMX callback by demux module
    DMX_EVENT_CB_SELF_TYPE2        = 0xC0000000, ///< DMX callback by demux module
} DMX_EVENT;
#endif

#define DMX_EVENT MS_U32
#define DMX_EVENT_DATA_READY          0x00000001 ///< DMX event ready
#define DMX_EVENT_BUF_OVERFLOW        0x00000002 ///< DMX event overflow
#define DMX_EVENT_SEC_CRCERROR        0x00000004 ///< DMX event CRC error
#define DMX_EVENT_PVRBUF_FULL         0x00000010 ///< DMX event PVR buffer overflow
#define DMX_EVENT_PVR1BUF_FULL        0x00000020 ///< DMX event Channel Browser buffer overflow

#if defined(MINI_TSP)
#define DMX_EVENT_SUBTITLE_BUF_FULL   0x00000040 ///< DMX event subtitle tile buffer full
#define DMX_EVENT_BLOCKING            0x00000080 ///< DMX event threshold address meet
#define DMX_EVENT_MIDDLE              0x00000100 ///< DMX event middle address meet
#define DMX_EVENT_FILEIN_DONE         0x00000200 ///< DMX event file in command done
#endif

/// TSP self task callback // optional --> default is CB by poll
#define DMX_EVENT_CB_MASK             0x80000000 ///< DMX callback mask
#define DMX_EVENT_CB_POLL             0x00000000 ///< DMX callback by polling // OBSOLETE
#define DMX_EVENT_CB_SELF             0x80000000 ///< DMX callback by demux module
#define DMX_EVENT_CB_SELF_TYPE2       0xC0000000 ///< DMX callback by demux module

typedef enum
{
    DMX_BURSTSINGLE                = 0x00,
    DMX_BURST2BYTE                 = 0x01,
    DMX_BURST4BYTE                 = 0x02,
    DMX_BURST8BYTE                 = 0x03,
} DMX_BURSTTYPE;

#if 0
// make sure what you are doing before changing the value
/// DMX section mode setting
typedef enum
{
    DMX_SECT_MODE_CONTI            = 0x00000000, ///< DMX receive section contiguously
    DMX_SECT_MODE_ONESHOT          = 0x00000001, ///< DMX only receive one section

    // optional
    DMX_SECT_MODE_CRCCHK           = 0x00000002, ///< DMX enables CRC check
    DMX_SECT_MODE_AUTO_ADDR        = 0x00000004, ///< DMX align read pointer to write pointer when get write pointer // OBSOLETE
} DMX_SECT_MODE;
#endif

#define DMX_SECT_MODE MS_U32
#define DMX_SECT_MODE_CONTI        0x00000000 ///< DMX receive section contiguously
#define DMX_SECT_MODE_ONESHOT      0x00000001 ///< DMX only receive one section

// optional
#define DMX_SECT_MODE_CRCCHK       0x00000002 ///< DMX enables CRC check
#define DMX_SECT_MODE_AUTO_ADDR    0x00000004 ///< DMX align read pointer to write pointer when get write pointer // OBSOLETE

/// DMX filein destination types
typedef enum
{
    DMX_PES_AUDIO2_FIFO 	= 0,              ///< DMX destination is audio2 fifo
    DMX_PES_AUDIO_FIFO  	= 1,              ///< DMX destination is audio fifo
    DMX_PES_VIDEO_FIFO  	= 2,              ///< DMX destination is video fifo
    DMX_PES_NO_BYPASS_FIFO  = 3,              ///< DMX destination with no bypass
    DMX_PES_VIDEO3D_FIFO  	= 4,              ///< DMX destination is video3D fifo
#if defined(MINI_TSP)
    DMX_PES_NO_BYPASS_VIDEO_FIFO,
    DMX_PES_NO_BYPASS_AUDIO_FIFO
#endif
} DMX_FILEIN_DST; //  DMXPESDATAFIFO;

/// DMX callback prototype
typedef void (*DMX_NotifyCb)(MS_U8 u8DmxId, DMX_EVENT enEvent);
typedef void (*DMX_Type2NotifyCb)(MS_U8 u8DmxId, DMX_EVENT enEvent, MS_U32 NotifyParam1);
/// DMX callback used in copy data
typedef MS_BOOL (*DMX_CheckCb)(MS_U8 u8DmxId, MS_U8* start, MS_U8* end, MS_U8* read, MS_U8* write);

// dummy data structure
typedef struct
{
    MS_U32                      streaminfo;
} DMX_Stream_info;

/// DMX section filter information structure
typedef struct
{
    MS_PHYADDR                  SectBufAddr; ///< DMX section buffer in physical address
    MS_U32                      SectBufSize; ///< DMX section buffer size
    DMX_SECT_MODE          		SectMode;         ///< DMX section mode
    DMX_EVENT              		Event;            ///< DMX section event
    DMX_NotifyCb           		pNotify;          ///< DMX section callback
    DMX_Type2NotifyCb           pType2Notify;          ///< DMX section callback
    MS_U32           			Type2NotifyParam1;          ///< DMX section callback
} DMX_Sect_info;

/// DMX filter information structure
typedef struct
{
    union {
        DMX_Stream_info    StreamInfo; ///< DMX stream information for future use
        DMX_Sect_info      SectInfo;   ///< DMX section information
    } Info;
} DMX_Flt_info;

/// DMX PVR information structure
typedef struct
{
    MS_PHYADDR                  pPvrBuf0;       ///< DMX PVR buffer 0 starting address
    MS_PHYADDR                  pPvrBuf1;       ///< DMX PVR buffer 1 starting address
    MS_U32                      PvrBufSize0;    ///< DMX PVR buffer 0 size
    MS_U32                      PvrBufSize1;    ///< DMX PVR buffer 1 size
    DMX_EVENT              		Event;          ///< DMX PVR event
    DMX_NotifyCb           		pNotify;        ///< DMX PVR callback
} DMX_Pvr_info;

/// DMX Channel Browser information structure
typedef struct
{
    MS_PHYADDR                  pPvr1Buf0;       ///< DMX Channel Browser buffer 0 starting address
    MS_U32                      Pvr1BufSize0;    ///< DMX Channel Browser buffer 0 size
    DMX_EVENT              		Event;          ///< DMX Channel Browser event
    DMX_NotifyCb           		pNotify;        ///< DMX Channel Browser callback
} DMX_Pvr1_info;

/// DMX capability query type
typedef enum
{
    DMX_CAP_PID_FILTER_NUM = 0,     ///< Get filter number
    DMX_CAP_SEC_FILTER_NUM,         ///< Get filter number
    DMX_CAP_SEC_BUF_NUM,            ///< Get filter number

    DMX_CAP_PVR_ENG_NUM,            ///< Get pvr engine number
    DMX_CAP_PVR_FILTER_NUM,         ///< Get pvr filter number
    DMX_CAP_PVR1_FILTER_NUM,        ///< Get pvr1 filter number

    DMX_CAP_MMFI_AUDIO_FILTER_NUM,  ///< Get MM file in audio path filter number
    DMX_CAP_MMFI_V3D_FILTER_NUM,    ///< Get MM file in video 3D path filter number

    DMX_CAP_TSIF_NUM,               ///< Get ts interface number
    DMX_CAP_DEMOD_NUM,
    DMX_CAP_TS_PAD_NUM,
    DMX_CAP_VQ_NUM,

    DMX_CAP_CA_FLT_NUM,             ///< Get dscmb filter number
    DMX_CAP_CA_KEY_NUM,

    DMX_CAP_FW_ALIGN,
    DMX_CAP_VQ_ALIGN,
    DMX_CAP_VQ_PITCH,               ///< Get length in bytes of one VQ unit
    DMX_CAP_SEC_BUF_ALIGN,
    DMX_CAP_PVR_ALIGN,              ///< Get miu alignment in bytes

    DMX_CAP_PVRCA_PATH_NUM,

    DMX_CAP_NULL,
} DMX_QUERY_TYPE;

//MMFI2
#define DMX_CAP_MMFI0_FILTER_NUM            DMX_CAP_MMFI_AUDIO_FILTER_NUM   ///< Get MM file0 filter number
#define DMX_CAP_MMFI1_FILTER_NUM            DMX_CAP_MMFI_V3D_FILTER_NUM     ///< Get MM file1 filter number


/// TSP file in Packet mode
typedef enum //_DMX_Filein_Packmode
{
    DMX_PKTMODE_188 = 0x00000000,       ///< DMX file in packet size with 188
    DMX_PKTMODE_192 = 0x00000001,       ///< DMX file in packet size with 192
    DMX_PKTMODE_204 = 0x00000002,       ///< DMX file in packet size with 204
} DMX_Filein_PacketMode;

/// TSP file in information structure
typedef struct
{
    MS_U32                 Rate;   ///< DMX file in rate
    DMX_Filein_PacketMode  PKT_Mode;    ///< DMX file in packet size mode
} DMX_Filein_info;

typedef enum
{
    DMX_MMFI_AUDIO  	= 0,              ///< DMX destination with no bypass to MM Audio path
    DMX_MMFI_VIDEO  	= 1,              ///< DMX destination with no bypass to MM Video path
} DMX_MMFI_PATH;

//MMFI2
#define DMX_MMFI_PATH0      DMX_MMFI_AUDIO
#define DMX_MMFI_PATH1      DMX_MMFI_VIDEO

typedef enum
{
    DMX_MMFI_FLTTYPE_AUD    = 0x00,
    DMX_MMFI_FLTTYPE_AUDB   = 0x01,
    DMX_MMFI_FLTTYPE_VD3D   = 0x02,
    DMX_MMFI_FLTTYPE_VD     = 0x03,

    DMX_MMFI1_FLTTYPE_MASK  = 0x80,
}DMX_MMFI_FLTTYPE;

typedef enum
{
	DMX_MMFI_PES_NO_BYPASS_AU 		= 0x0000,
	DMX_MMFI_PES_PS_AU				= 0x0001,
	DMX_MMFI_PES_PS_AUB				= 0x0002,
	DMX_MMFI_PES_APID_BYPASS		= 0x0004,
	DMX_MMFI_PES_APIDB_BYPASS		= 0x0008,
    DMX_MMFI_PES_NO_BYPASS_V3D		= 0x0010,
    DMX_MMFI_PES_PS_V3D				= 0x0020,
	DMX_MMFI_PES_V3DPID_BYPASS		= 0x0040,

    DMX_MMFI_PES_NO_BYPASS_VD       = 0x0080,
    DMX_MMFI_PES_VPID_BYPASS        = 0x0100,
    DMX_MMFI_PES_NO_BYPASS_TS       = 0x0200,
    DMX_MMFI_PES_PS_VD              = 0x0400,
    
    DMX_MMFI_PES_NO_BYPASS_FIFO     = 0x0800,

    DMX_MMFI1_PES_TYPE_MASK         = 0x8000,
}DMX_MMFI_DST;

// General API
DMX_FILTER_STATUS MApi_DMX_Init(void);
DMX_FILTER_STATUS MApi_DMX_TSPInit(DMX_TSPParam *param);
DMX_FILTER_STATUS MApi_DMX_Exit(void);
DMX_FILTER_STATUS MApi_DMX_ForceExit(void);
DMX_FILTER_STATUS MApi_DMX_Reset(void);
DMX_FILTER_STATUS MApi_DMX_SetFW(MS_PHYADDR pFwAddr, MS_U32 u32FwSize); // In DRAM physical address
DMX_FILTER_STATUS MApi_DMX_Suspend(void);
DMX_FILTER_STATUS MApi_DMX_Resume(MS_U32 u32FWAddr, MS_U32 u32FWSize);
DMX_FILTER_STATUS MApi_DMX_ReleaseSemaphone(void);
DMX_FILTER_STATUS MApi_DMX_SetFwDbgParam(MS_U32 u32Addr, MS_U32 u32Size, MS_U32 u32DbgWord);
DMX_FILTER_STATUS MApi_DMX_SetDbgLevel(DMX_DBGMSG_LEVEL level);
DMX_FILTER_STATUS MApi_TSP_Get_FW_VER(MS_U32* u32FWVer);
DMX_FILTER_STATUS MApi_DMX_Get_Intr_Count(MS_U32* pu32Count);
DMX_FILTER_STATUS MApi_DMX_GetLibVer(const MSIF_Version **ppVersion);
DMX_FILTER_STATUS MApi_DMX_GetCap(DMX_QUERY_TYPE DmxQueryType, void* pOutput);
#if (!defined(MINI_TSP))
DMX_FILTER_STATUS MApi_DMX_Get_FlowInput_Status(DMX_FLOW DmxFlow, DMX_FLOW_INPUT *pDmxFlowInput, MS_BOOL *pbClkInv, MS_BOOL *pbExtSync, MS_BOOL *pbParallel);
#endif
DMX_FILTER_STATUS MApi_DMX_STC64_Mode_Enable(MS_BOOL bEnable);
DMX_FILTER_STATUS MApi_DMX_VQ_Enable(MS_BOOL bEnable);

DMX_FILTER_STATUS MApi_DMX_FlowSet(DMX_FLOW DmxFlow, DMX_FLOW_INPUT DmxFlowInput, MS_BOOL bClkInv, MS_BOOL bExtSync, MS_BOOL bParallel);
DMX_FILTER_STATUS MApi_DMX_Open(DMX_FILTER_TYPE DmxFltType, MS_U8* pu8DmxId);
DMX_FILTER_STATUS MApi_DMX_Close(MS_U8 u8DmxId);
DMX_FILTER_STATUS MApi_DMX_Start(MS_U8 u8DmxId);
DMX_FILTER_STATUS MApi_DMX_Stop(MS_U8 u8DmxId);
DMX_FILTER_STATUS MApi_DMX_IsStart(MS_U8 u8DmxId, MS_BOOL* pbEnable);
DMX_FILTER_STATUS MApi_DMX_ChkAlive(void);
DMX_FILTER_STATUS MApi_DMX_Info(MS_U8 u8DmxId, DMX_Flt_info* pDmxFltInfo, DMX_FILTER_TYPE* pDmxFltType, MS_BOOL bSet);
DMX_FILTER_STATUS MApi_DMX_Pid(MS_U8 u8DmxId, MS_U16* pu16Pid, MS_BOOL bSet);
DMX_FILTER_STATUS MApi_DMX_Stc_Get(MS_U32* pu32Stc32, MS_U32* pu32Stc);
DMX_FILTER_STATUS MApi_DMX_Stc_Set(MS_U32 u32Stc32, MS_U32 u32Stc);
DMX_FILTER_STATUS MApi_DMX_Stc_Eng_Get(MS_U8 u8Eng, MS_U32* pu32Stc32, MS_U32* pu32Stc);
DMX_FILTER_STATUS MApi_DMX_Stc_Eng_Set(MS_U8 u8Eng, MS_U32 u32Stc32, MS_U32 u32Stc);
DMX_FILTER_STATUS MApi_DMX_Pcr_Get(MS_U32* pu32Pcr32, MS_U32* pu32Pcr);
DMX_FILTER_STATUS MApi_DMX_Proc(MS_U8 u8DmxId, DMX_EVENT* pEvent);
DMX_FILTER_STATUS MApi_DMX_Parl_Invert(DMX_FLOW DmxFlow, MS_BOOL bInvert);
//DMX_FILTER_STATUS MApi_DMX_Proc(MS_U8 u8DmxId); // 0xFF for u8DmxId means check the last un-check filter
DMX_FILTER_STATUS MApi_DMX_CopyData(MS_U8 u8DmxId, MS_U8* pu8Buf, MS_U32 u32BufSize, MS_U32* pu32ActualSize, MS_U32* pu32RmnSize, DMX_CheckCb pfCheckCB);
DMX_FILTER_STATUS MApi_DMX_RemoveDupAVPkt(MS_BOOL bEnable);
DMX_FILTER_STATUS MApi_DMX_RemoveDupAVFifoPkt(DMX_FILTER_TYPE DmxFltType, MS_BOOL bEnable);
DMX_FILTER_STATUS MApi_DMX_Change_FilterSource(MS_U8 u8DmxId, DMX_FILTER_TYPE DmxFltSrcType);


// Section API
DMX_FILTER_STATUS MApi_DMX_SectPatternSet(MS_U8 u8DmxId, MS_U8* pPattern, MS_U8* pMask, MS_U8 *pu8NotMask, MS_U32 MatchSize);
// DMX_FILTER_STATUS MApi_DMX_SectGet(MS_U8 u8DmxId, MS_U8* pu8Buf, MS_U32 u32BufSize, MS_U32* pu32SectSize);
DMX_FILTER_STATUS MApi_DMX_SectReset(MS_U8 u8DmxId);
DMX_FILTER_STATUS MApi_DMX_SectReadSet(MS_U8 u8DmxId, MS_PHYADDR Read);
DMX_FILTER_STATUS MApi_DMX_SectReadGet(MS_U8 u8DmxId, MS_PHYADDR* pRead);
DMX_FILTER_STATUS MApi_DMX_SectWriteGet(MS_U8 u8DmxId, MS_PHYADDR* pWrite);
DMX_FILTER_STATUS MApi_DMX_SectStartGet(MS_U8 u8DmxId, MS_PHYADDR* pStart);
DMX_FILTER_STATUS MApi_DMX_SectEndGet(MS_U8 u8DmxId, MS_PHYADDR* pEnd);


// PVR API Old
DMX_FILTER_STATUS MApi_DMX_Pvr_Open(DMX_Pvr_info* pPvrInfo);
DMX_FILTER_STATUS MApi_DMX_Pvr_Close(void);
DMX_FILTER_STATUS MApi_DMX_Pvr_Pause(MS_BOOL bPause);
DMX_FILTER_STATUS MApi_DMX_Pvr_Pid_Open(MS_U32 Pid, MS_U8* pu8DmxId);
DMX_FILTER_STATUS MApi_DMX_Pvr_Pid_Close(MS_U8 u8DmxId);
DMX_FILTER_STATUS MApi_DMX_Pvr_Start(MS_BOOL bPvrAll);
DMX_FILTER_STATUS MApi_DMX_Pvr_Stop(void);
DMX_FILTER_STATUS MApi_DMX_Pvr_WriteGet(MS_U32* pu32Write);
DMX_FILTER_STATUS MApi_DMX_PVR_SetPacketMode(MS_BOOL bSet);
DMX_FILTER_STATUS MApi_DMX_Pvr_SetRecordStamp(MS_U32 u32Stamp);
DMX_FILTER_STATUS MApi_DMX_Pvr_GetRecordStamp(MS_U32* pu32Stamp);
DMX_FILTER_STATUS MApi_DMX_Pvr_SetPlaybackStamp(MS_U32 u32Stamp);
DMX_FILTER_STATUS MApi_DMX_Pvr_GetPlaybackStamp(MS_U32* pu32Stamp);
DMX_FILTER_STATUS MApi_DMX_Pvr_TimeStampEnable(void);
DMX_FILTER_STATUS MApi_DMX_Pvr_TimeStampDisable(void);
DMX_FILTER_STATUS MApi_DMX_Pvr_MOBF_Enable(MS_BOOL bEnable, MS_U32 u32key0, MS_U32 u32key1);
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_MOBF_Enable(MS_U8 u8Eng, MS_BOOL bEnable, MS_U32 u32key0, MS_U32 u32key1);

// PVR API New
#if (!defined(MINI_TSP))
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_Open(DMX_PVR_ENG Eng ,DMX_Pvr_info* pPvrInfo);
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_Close(DMX_PVR_ENG Eng );
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_Pause(DMX_PVR_ENG Eng ,MS_BOOL bPause);
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_Pid_Open(DMX_PVR_ENG Eng ,MS_U32 Pid, MS_U8* pu8DmxId);
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_Pid_Close(DMX_PVR_ENG Eng ,MS_U8 u8DmxId);
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_Start(DMX_PVR_ENG Eng ,MS_BOOL bPvrAll);
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_Stop(DMX_PVR_ENG Eng );
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_WriteGet(DMX_PVR_ENG Eng ,MS_U32* pu32Write);
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_SetPacketMode(DMX_PVR_ENG Eng ,MS_BOOL bSet);
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_SetRecordStamp(DMX_PVR_ENG Eng ,MS_U32 u32Stamp);
DMX_FILTER_STATUS MApi_DMX_Pvr_Eng_GetRecordStamp(DMX_PVR_ENG Eng ,MS_U32* pu32Stamp);
#endif

// File-in API
DMX_FILTER_STATUS MApi_DMX_Filein_Start(DMX_FILEIN_DST Dst, MS_PHYADDR pBuf, MS_U32 u32BufSize);   // msAPI_DMX_PESPlayback/msAPI_DMX_TSPlayback will integrate into it
DMX_FILTER_STATUS MApi_DMX_Filein_Stop(void);
DMX_FILTER_STATUS MApi_DMX_Filein_Info(DMX_Filein_info *pFileinInfo);
DMX_FILTER_STATUS MApi_DMX_Filein_Pause(void);
DMX_FILTER_STATUS MApi_DMX_Filein_Resume(void);
MS_BOOL           MApi_DMX_Filein_IsIdle(void);
MS_BOOL           MApi_DMX_Filein_IsBusy(void);
MS_BOOL           MApi_DMX_Filein_IsPause(void);
DMX_FILTER_STATUS MApi_DMX_Filein_CMDQ_Reset(void);
DMX_FILTER_STATUS MApi_DMX_Filein_CMDQ_GetEmptyNum(MS_U32 *pu32EmptySlot);
void              MApi_DMX_BypassFileInTimeStamp(MS_BOOL bbypass);
DMX_FILTER_STATUS MApi_DMX_Filein_CMDQ_FIFOWriteLevel(MS_U8 *pu8CmdQStatus);
DMX_FILTER_STATUS MApi_DMX_GetFileInTimeStamp(MS_U32 *pu32FileInTS);
DMX_FILTER_STATUS MApi_DMX_Filein_GetReadAddr(MS_U32* pu32Read);
DMX_FILTER_STATUS MApi_DMX_Filein_MOBF_Enable(MS_BOOL bEnable, MS_U32 u32key);

#if defined(MINI_TSP)
DMX_FILTER_STATUS MApi_DMX_MiniFilein_SetPath(DMX_TS_PATH eAudioPath, DMX_TS_PATH eVideoPath);
DMX_FILTER_STATUS MApi_DMX_SetThresHold(MS_BOOL bEnable, MS_PHYADDR phyAddr);
DMX_FILTER_STATUS MApi_DMX_SetMiddle(MS_BOOL bEnable, MS_PHYADDR phyAddr);
#endif

//MMFI & MINITSP
MS_BOOL 		  MApi_DMX_MMFI_Filein_IsIdle(DMX_MMFI_PATH ePath);
MS_BOOL           MApi_DMX_MMFI_Filein_IsBusy(DMX_MMFI_PATH ePath);
DMX_FILTER_STATUS MApi_DMX_MMFI_Filein_CMDQ_Reset(DMX_MMFI_PATH ePath);
DMX_FILTER_STATUS MApi_DMX_MMFI_Filein_CMDQ_GetEmptyNum(DMX_MMFI_PATH ePath, MS_U32 *pu32EmptySlot);
DMX_FILTER_STATUS MApi_DMX_MMFI_Filein_Start(DMX_MMFI_DST eDst, MS_PHYADDR pBuf, MS_U32 u32BufSize);
DMX_FILTER_STATUS MApi_DMX_MMFI_GetFileInTimeStamp(DMX_MMFI_PATH ePath, MS_U32 *pu32FileInTS);

//MMFI
DMX_FILTER_STATUS MApi_DMX_MMFI_Pid_Open(DMX_MMFI_FLTTYPE flttype, MS_U16 u16Pid, MS_U8* pu8DmxId);
DMX_FILTER_STATUS MApi_DMX_MMFI_Pid_Close(MS_U8 u8DmxId);
DMX_FILTER_STATUS MApi_DMX_MMFI_Filein_CMDQ_FIFOWriteLevel(DMX_MMFI_PATH ePath, MS_U8 *pu8CmdQStatus);
DMX_FILTER_STATUS MApi_DMX_MMFI_SetPcr2(DMX_MMFI_PATH ePath, MS_U32 u32pcr2);
DMX_FILTER_STATUS MApi_DMX_MMFI_GetPcr2(DMX_MMFI_PATH ePath, MS_U32 *pu32pcr2);
DMX_FILTER_STATUS MApi_DMX_MMFI_RemoveDupAVPkt(MS_BOOL bEnable);
DMX_FILTER_STATUS MApi_DMX_MMFI_MOBF_Enable(DMX_MMFI_PATH ePath, MS_BOOL bEnable, MS_U32 u32key);
DMX_FILTER_STATUS MApi_DMX_MMFI_MOBF_SetLevel(DMX_MMFI_PATH epath, MS_U8 u8level);


//PVR CA API
#if (!((defined(TSP_VERSION) && (TSP_VERSION == TSP_VER_2_0)) || defined(MINI_TSP)))
DMX_FILTER_STATUS MApi_DMX_PvrCA_Pid_Open(MS_U32 Pid, MS_U8* pu8DmxId);
DMX_FILTER_STATUS MApi_DMX_PvrCA_Pid_Close(MS_U8 u8DmxId);
DMX_FILTER_STATUS MApi_DMX_PvrCA_Start(MS_BOOL bPvrAll);
DMX_FILTER_STATUS MApi_DMX_PvrCA_Stop(void);

DMX_FILTER_STATUS MApi_DMX_PvrCA_Eng_Pid_Open(DMX_PVR_ENG Eng, MS_U32 Pid, MS_U8* pu8DmxId);
DMX_FILTER_STATUS MApi_DMX_PvrCA_Eng_Pid_Close(DMX_PVR_ENG Eng, MS_U8 u8DmxId);
DMX_FILTER_STATUS MApi_DMX_PvrCA_Eng_Start(DMX_PVR_ENG Eng, MS_BOOL bPvrAll);
DMX_FILTER_STATUS MApi_DMX_PvrCA_Eng_Stop(DMX_PVR_ENG Eng);
#endif

// owner ship set/checking
DMX_FILTER_STATUS MApi_DMX_SetOwner(MS_U8 u8DmxIdStart, MS_U8 u8DmxIdEnd, MS_BOOL bOwner); //OBSOLETE
DMX_FILTER_STATUS MApi_DMX_GetOwner(MS_U8 u8DmxId, MS_BOOL* pbOwner); //OBSOLETE
DMX_FILTER_STATUS MApi_DMX_GetAccess(MS_U32 u32Try); //OBSOLETE
DMX_FILTER_STATUS MApi_DMX_ReleaseAccess(void); //OBSOLETE
DMX_FILTER_STATUS MApi_DMX_SetHK(MS_BOOL bIsHK); // OBSOLETE

// AVFIFO control
DMX_FILTER_STATUS MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE DmxFltType, MS_BOOL bFlush);
DMX_FILTER_STATUS MApi_DMX_AVFifo_Status(DMX_FILTER_TYPE DmxFltType, MS_U32 *u32FifoLevel);

DMX_FILTER_STATUS MApi_DMX_SetBurstLen(DMX_BURSTTYPE BurstType);
DMX_FILTER_STATUS MApi_DMX_TTX_WriteGet(MS_U8 u8DmxId, MS_PHYADDR* pWrite);
DMX_FILTER_STATUS MApi_DMX_GetDbgPortInfo(MS_U32 u32DbgSel,MS_U32* u32DbgInfo);

DMX_FILTER_STATUS MApi_DMX_Drop_Enable(MS_BOOL bSet);

// ---------------- [NOTE] API for TSP Ver2.0 HW architecture.-------------
DMX_FILTER_STATUS MApi_DMX_Open_MultiFlt( DMX_FILTER_TYPE DmxFltType , MS_U8* pu8DmxId, MS_U8 u8TargetDmxId);
DMX_FILTER_STATUS MApi_DMX_LiveSrcSwitch(DMX_FILTER_TYPE TgtFlow);
//--------------------------------------------------------------------------------

DMX_FILTER_STATUS MApi_DMX_AU_BD_Mode_Enable(MS_BOOL bEnable);

//------------------------ TSO -----------------------------
DMX_FILTER_STATUS MApi_DMX_TSO_Filein_Info(DMX_Filein_info *pFileinInfo);
MS_BOOL           MApi_DMX_TSO_Filein_IsIdle(void);
DMX_FILTER_STATUS MApi_DMX_TSO_Filein_CMDQ_GetEmptyNum(MS_U32 *pu32EmptySlot);
DMX_FILTER_STATUS MApi_DMX_TSO_Filein_Start(MS_PHYADDR pBuf, MS_U32 u32BufSize);
DMX_FILTER_STATUS MApi_DMX_TSO_SetPlaybackTimeStamp(MS_U32 u32Stamp);
DMX_FILTER_STATUS MApi_DMX_TSO_GetPlaybackStamp(MS_U32* pu32Stamp);
DMX_FILTER_STATUS MApi_DMX_TSO_GetFileInTimeStamp(MS_U32 *pu32Stamp);

#if 0
DMX_FILTER_STATUS MApi_DMX_ResetFileinTimestamp(void)
#endif


#ifdef __cplusplus
}
#endif

#endif // #ifndef __API_DMX_H__
