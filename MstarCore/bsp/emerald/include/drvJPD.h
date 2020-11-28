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
/// @file   drvJPD.h
/// @brief  JPD Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_JPD_H_
#define _DRV_JPD_H_

#include "jpeg_def.h"


#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define MSIF_JPD_LIB_CODE                     {'J','P','D','_'}                 ///<Lib code
#define MSIF_JPD_LIBVER                       {'0','1'}                         ///<LIB version
#define MSIF_JPD_BUILDNUM                     {'0','2'}                         ///<Build Number
#define MSIF_JPD_CHANGELIST                   {'0','0','2','8','5','2','5','1'} ///<P4 ChangeList Number


//------------------------------------------------------------------------------
/// @brief \b JPD_DRV_VERSION : JPEG Version
//------------------------------------------------------------------------------
#define JPD_DRV_VERSION                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_JPD_LIB_CODE,                  /* IP__                                             */  \
    MSIF_JPD_LIBVER,                    /* 0.0 ~ Z.Z                                        */  \
    MSIF_JPD_BUILDNUM,                  /* 00 ~ 99                                          */  \
    MSIF_JPD_CHANGELIST,                /* CL#                                              */  \
    MSIF_OS

#if 0
#if defined (__aeon__)
#define AEON_NON_CACHE_MASK  0x80000000
#elif defined (MSOS_TYPE_LINUX)
#define AEON_NON_CACHE_MASK  0x0
#else
#define AEON_NON_CACHE_MASK  0xA0000000
#endif
#endif

#define JPD_BIT(_bit_)      (1<<(_bit_))
#define JPD_BITMASK(_bits_) (JPD_BIT(((1)?_bits_)+1)-JPD_BIT(((0)?_bits_)))
#define JPD_OFFSET(x)       ((x)<<1)

/*****************Config Flag*********************/
//S-Config
#if 1//defined(CHIP_T3) || defined(CHIP_T4) || defined(CHIP_T7) || defined(CHIP_JANUS) || defined(CHIP_U4) || defined(CHIP_T8)  || defined(CHIP_T9) || defined(CHIP_J2)
#define JPD_PSAVE_EN                JPD_BIT(14)
#endif
//#define JPD_SWRST_S4              JPD_BIT(12) // Eris
//#define JPD_SWRST_S4L             JPD_BIT(13) // Titania
#define JPD_SWRST                   JPD_BIT(13) // T1/T2/T3
#define JPD_ROI_EN                  JPD_BIT(11)
#define JPD_SVLD                    JPD_BIT(10)
#define JPD_SUVQ                    JPD_BIT(9)
#define JPD_TBL_RDY                 JPD_BIT(8)
#define JPD_DEC_EN                  JPD_BIT(7)
#define JPD_RST_EN                  JPD_BIT(6)
#define JPD_UV                      JPD_BIT(3)
#define JPD_Y_VSF1                  (0<<2)
#define JPD_Y_VSF2                  JPD_BIT(2)
#define JPD_Y_HSF1                  0x01
#define JPD_Y_HSF2                  0x02
#define JPD_Y_HSF4                  0x03

//M-Config
#define JPD_H_VLD                   JPD_BIT(1)
#define JPD_L_VLD                   JPD_BIT(0)

//**********************JPD Spare Reg, For ECO usage**********************//
//Enable Redundant stuffing byte X'FF' skipping. (T4,JANUS,T7,U4,T8,T9,...)
/*
[0]: 20091214_fix0: skipping of stuffing byte X'FF' preceding restart marker; 1: fix enabled, 0: fix disabled
[1]: 20091214_fix1: toleration of restart marker index dis-order; 1: fix enabled, 0: fix disabled

[3]: reg_20100303_last: fix the problem of jpd will not alert jd2mi_last after miu_reset; 1: enable, 0: disable
[4]: reg_20100303_last_power_save: fix the problem of jpd will not alert jd2mi_last in power saving mode; 1: enable, 0: disable
[5]: reg_20100325_last_done_z : fix the problem of last_done_z; 1: enable, 0: disable
[6]: reg_20101101 : fix the problem of output data lost when clk_miu is far slower than clk_jpd. 1: enable, 0: disable (A1~)
*/
#define JPD_RST_STUFF_BYTE_HANDLE       JPD_BIT(0) | JPD_BIT(1) | JPD_BIT(3) | JPD_BIT(4) | JPD_BIT(5) | JPD_BIT(6) | JPD_BIT(7)
#if (JPD_SUPPORT_3_HUFFMAN_TABLE==true)
//Enable JPD 3 Huffman table support
#define JPD_3_HUFFMAN_TABLE_SUPPORT     JPD_BIT(2)
#endif
//************************************************************************//

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

// Chip Define
typedef enum
{
    E_MJPEG_MSTAR_CHIP_NONE = 0,
    E_MJPEG_MSTAR_CHIP_U3,
    E_MJPEG_MSTAR_CHIP_T3,
    E_MJPEG_MSTAR_CHIP_T4,
    E_MJPEG_MSTAR_CHIP_JANUS,
    E_MJPEG_MSTAR_CHIP_U4,
    E_MJPEG_MSTAR_CHIP_T8,
    E_MJPEG_MSTAR_CHIP_T9,
    E_MJPEG_MSTAR_CHIP_T13,
    E_MJPEG_MSTAR_CHIP_A1,
    E_MJPEG_MSTAR_CHIP_A6,
    E_MJPEG_MSTAR_CHIP_A7,
    E_MJPEG_MSTAR_CHIP_AMETHYST,
    E_MJPEG_MSTAR_CHIP_EAGLE,
    E_MJPEG_MSTAR_CHIP_J2,
    E_MJPEG_MSTAR_CHIP_EMERALD,
    E_MJPEG_MSTAR_CHIP_M12,
} MJPEG_MSTAR_CHIP_ID;

// JPD event
typedef enum
{
    E_JPD_EVENT_DEC_DONE    = 0x01
  , E_JPD_EVENT_ECS_ERROR   = 0x02
  , E_JPD_EVENT_IS_ERROR    = 0x04
  , E_JPD_EVENT_RST_ERROR   = 0x08
  , E_JPD_EVENT_MRBL_DONE   = 0x10
  , E_JPD_EVENT_MRBH_DONE   = 0x20
#if (JPD_SUPPORT_AUTO_PROTECT==true)
  , E_JPD_EVENT_MWB_FULL    = 0x40
#endif
  , E_JPD_EVENT_ERROR_MASK  = 0x0E
} JPD_Event;


// JPD Downscale Ratio
// Bellows are 1, 1/2, 1/4 and 1/8 in order
typedef enum
{
    E_JPD_DOWNSCALE_ORG     = 0x00
  , E_JPD_DOWNSCALE_HALF    = 0x01
  , E_JPD_DOWNSCALE_FOURTH  = 0x02
  , E_JPD_DOWNSCALE_EIGHTH  = 0x03
} JPD_DownScale;

// Mimic fwJPD_if.h
typedef enum
{
    // Invalid cmd
    E_MJPEG_CMD_INVALID = 0xffffffffUL,

    E_MJPEG_CMD_GO                             = 0x00, // Start to show
    E_MJPEG_CMD_SET_FRAME_BUFF_START_ADDR      = 0x01, // Set frame buffer address
    E_MJPEG_CMD_SET_FRAME_BUFF_UNIT_SIZE       = 0x02, // Set frame buffer size
    E_MJPEG_CMD_SET_FRAME_BUFF_TOTAL_NUM       = 0x03, // Set total number of frame buffer
    E_MJPEG_CMD_SET_FRAME_BUFF_IDX             = 0x04, // Set frame buffer index
    E_MJPEG_CMD_SET_FRAME_BUFF_IDX_READY       = 0x05, // Set frame buffer index ready for display
    E_MJPEG_CMD_SET_WIDTH                      = 0x06, // Set frame width
    E_MJPEG_CMD_SET_HEIGHT                     = 0x07, // Set frame height
    E_MJPEG_CMD_SET_PITCH                      = 0x08, // Set pitch
    E_MJPEG_CMD_SET_FRAME_ID_L                 = 0x09, // Set frame ID_L
    E_MJPEG_CMD_SET_FRAME_ID_H                 = 0x0A, // Set frame ID_H
    E_MJPEG_CMD_SET_TIMESTAMP                  = 0x0B, // Set Time Stamp
    E_MJPEG_CMD_SET_FRAMERATE                  = 0x0C, // Set FrameRate
    E_MJPEG_CMD_SET_FRAMERATE_BASE             = 0x0D, // Set FrameRate Base
    E_MJPEG_CMD_SET_FRAME_BUFF_IDX_VALID       = 0x0E, // Set frame buffer index available
    E_MJPEG_CMD_SET_CHIP_ID                    = 0x0F, // Set frame buffer index available

    E_MJPEG_CMD_PLAY                           = 0x20, // Play
    E_MJPEG_CMD_PAUSE                          = 0x21, // Pause
    E_MJPEG_CMD_RESUME                         = 0x22, // Resume
    E_MJPEG_CMD_STEP_PLAY                      = 0x23, // Step play
    E_MJPEG_CMD_SET_SPEED_TYPE                 = 0x24, // Set play speed type: default, fast, slow
    E_MJPEG_CMD_SET_SPEED                      = 0x25, // Set play speed
    E_MJPEG_CMD_FLUSH_DISP_QUEUE               = 0X26, // Flush display queue
    E_MJPEG_CMD_FREEZE_DISP                    = 0x27, // Freeze display
    E_MJPEG_CMD_ENABLE_AVSYNC                  = 0x28, // Enable AV sync
    E_MJPEG_CMD_SET_AVSYNC_DELAY               = 0x29, // Set AV sync delay
    E_MJPEG_CMD_SET_AVSYNC_TOLERENCE           = 0x2A, // Set AV sync tolerence
    E_MJPEG_CMD_SET_PTS_BASE                   = 0x2B, // Set PTS base
    E_MJPEG_CMD_SET_STC_BASE                   = 0x2C, // Set STC base
    E_MJPEG_CMD_SET_BLUE_SCREEN                = 0x2D, // Set Blue Screen

    E_MJPEG_CMD_GET_NEXT_FREE_FRAME_BUFF_IDX   = 0x40, // Get next free frame buffer index
    E_MJPEG_CMD_COMPENSATE_PTS                 = 0x41, // Ask firmware to compensate PTS

    // Display Command Queue
    E_MJPEG_CMD_ENABLE_DISP_CMD_QUEUE          = 0x80, // Enable Display Command Queue
    E_MJPEG_CMD_PUSH_DISP_CMD                  = 0x81, // Push Display Command
    E_MJPEG_CMD_GET_DISP_CMD_Q_VACANCY         = 0x82, // Check if the display command queue full or not

    E_MJPEG_CMD_IS_STEP_PLAY_DONE              = 0xFF, //
    E_MJPEG_CMD_IS_DISP_FINISH                 = 0xFE, //
    E_MJPEG_CMD_IS_PLAYING                     = 0xFC, //
    E_MJPEG_CMD_IS_DISPLAY_QUEUE_FULL          = 0xFB, //
    E_MJPEG_CMD_IS_AVSYNC_ON                   = 0xFA, //
    E_MJPEG_CMD_IS_REACH_AVSYNC                = 0xF9, //
    E_MJPEG_CMD_IS_FLUSH_DONE                  = 0xF8, // Check if flush done

} MJPEG_User_Cmd;

// JPD debug level enum
typedef enum
{
    E_JPD_DEBUG_DRV_NONE = 0x0
  , E_JPD_DEBUG_DRV_MSG  = 0x02
  , E_JPD_DEBUG_DRV_ERR  = 0x08
} JPD_DrvDbgLevel;

typedef enum
{
    E_JPD_FAILED        = 0
  , E_JPD_OK            = 1
  , E_JPD_INVALID_PARAM = 2
} JPD_Return;

// JPD Interrupt Register Function
typedef void (*JPD_IsrFuncCb)(void);

//------------------------------------------------------------------------------
// Structure for buffer
typedef struct
{
    MS_PHYADDR u32ThumbnailBufAddr;
    MS_U32 u32ThumbnailBufSize;
    MS_U32 u32ThumbnailBufOffset;
    MS_PHYADDR u32MRCBufAddr; // MRC buffer address
    MS_U32 u32MRCBufSize; // MRC buffer size
    MS_U32 u32MRCBufOffset; // MRC access byte address offset in MRC buffer relative to MRC start address
    MS_PHYADDR u32MWCBufAddr; // MWC buffer address
    MS_U16 u16MWCBufLineNum; // MWC Line number
    MS_BOOL bProgressive;
    MS_BOOL bThumbnailAccessMode;
} JPD_BufCfg;
//------------------------------------------------------------------------------
// Structure for Grpinf of Table IndirectAccess
typedef struct
{
    MS_U8 *u8DcLumaSymbol;
    MS_U16 *u16DcLumaCode;
    MS_U8 *u8DcChromaSymbol;
    MS_U16 *u16DcChromaCode;
    MS_U8 *u8DcChroma2Symbol;
    MS_U16 *u16DcChroma2Code;
    MS_U8 *u8AcLumaSymbol;
    MS_U16 *u16AcLumaCode;
    MS_U8 *u8AcChromaSymbol;
    MS_U16 *u16AcChromaCode;
    MS_U8 *u8AcChroma2Symbol;
    MS_U16 *u16AcChroma2Code;
    MS_BOOL DHT;
    MS_BOOL bUVHuffman;
} JPD_Grpinf;
//------------------------------------------------------------------------------
// Structure for Symidx of Table Indirect Access
typedef struct
{
    MS_U8 *u8DcLumaHuffVal;
    MS_U8 *u8DcChromaHuffVal;
    MS_U8 *u8DcChroma2HuffVal;
    MS_U8 *u8AcLumaHuffVal;
    MS_U8 *u8AcChromaHuffVal;
    MS_U8 *u8AcChroma2HuffVal;
    MS_BOOL DHT;
    MS_BOOL bUVHuffman;
} JPD_Symidx;
//------------------------------------------------------------------------------
// Structure for Quantization Table
typedef struct
{
    MS_U16 s16Value[64];
    MS_BOOL bValid;
} JPD_QuanTbl;
//------------------------------------------------------------------------------
// Structure for IQtbl of Table Indirect Access
typedef struct
{
    MS_U8 *u8CompQuant;
    JPD_QuanTbl *QuantTables;
    MS_U8 u8CompNum;
    MS_BOOL DQT;
} JPD_IQTbl;
//------------------------------------------------------------------------------
// Structure for JPD capability
typedef struct
{
    MS_BOOL bBaseline;
    MS_BOOL bProgressive;
    MS_BOOL bMJPEG;
} JPD_Cap;
//------------------------------------------------------------------------------
// Structure for JPD Information
typedef struct
{
    MS_U8* pu8HalVer;
    MS_U8* pu8FwVer;
    JPD_Cap stCap;
} JPD_Info;
//------------------------------------------------------------------------------
// Structure for JPD Status
typedef struct
{
    MS_U32  u32CurMRCAddr;
    MS_U16  u16CurVidx;
    MS_U16  u16CurRow;
    MS_U16  u16CurCol;
    MS_BOOL bIsBusy;
    MS_BOOL bIsrEnable;
} JPD_Status;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
//void MDrv_JPD_Initialize(MS_U8 u8ChipType);
void MDrv_JPD_InitBuf(JPD_BufCfg in);
//void MDrv_JPD_Reset(void);
//void MDrv_JPD_SW_Pause_Reset(void);
void MDrv_JPD_Rst(void);
//MS_U16 MDrv_JPD_GetSWResetMask(void);
//void MDrv_JPD_SetReadBuffer(MS_U32 u32BufAddr, MS_U32 u32BufSize);
//void MDrv_JPD_SetMRCStartAddr(MS_U32 u32ByteOffset);
//void MDrv_JPD_SetOutputFrameBuffer(MS_U32 u32BufAddr);
void MDrv_JPD_SetPicDimension(MS_U16 u16Width, MS_U16 u16Height);
//MS_U16 MDrv_JPD_ReadJPDStatus(void);
MS_U16 MDrv_JPD_GetEventFlag(void);
//void MDrv_JPD_ClearJPDStatus(MS_U16 status_bit);
void MDrv_JPD_SetEventFlag(MS_U16 u16Value);
void MDrv_JPD_SetROI(MS_U16 start_x, MS_U16 start_y, MS_U16 width, MS_U16 height);
//void MDrv_JPD_SetClock(MS_U8 on);
void MDrv_JPD_PowerOn(void);
void MDrv_JPD_PowerOff(void);
#if 0 // unused function
MS_U32 MDrv_JPD_ReadCurrentMRCAddr(void);
#endif
void MDrv_JPD_SetRSTIntv(MS_U16 u16Value);
MS_U16 MDrv_JPD_GetCurVidx(void);

void MDrv_JPD_WriteGrpinf(JPD_Grpinf in);
void MDrv_JPD_WriteSymidx(JPD_Symidx in);
void MDrv_JPD_WriteIQTbl(JPD_IQTbl in);

void MDrv_JPD_Set_M_Config(MS_U16 u16Value);
MS_U16 MDrv_JPD_Get_M_Config(void);
void MDrv_JPD_Set_S_Config(MS_U16 u16Value);
MS_U16 MDrv_JPD_Get_S_Config(void);
void MDrv_JPD_SetDbgLevel(MS_U8 u8DbgLevel);
void MDrv_JPD_GetInfo(JPD_Info *pJPD_Info);
JPD_Status* MDrv_JPD_GetStatus(void);
MS_BOOL MDrv_JPD_GetLibVer(const MSIF_Version **ppVersion);

MS_BOOL MDrv_JPD_EnableISR(JPD_IsrFuncCb IsrCb);
MS_BOOL MDrv_JPD_DisableISR(void);

MS_U32 MDrv_JPD_GetCurMRCAddr(void);
MS_U16 MDrv_JPD_GetCurRow(void);
MS_U16 MDrv_JPD_GetCurCol(void);

#if (JPD_SUPPORT_AUTO_PROTECT==true)
void MDrv_JPD_SetAutoProtect(MS_BOOL enable);
void MDrv_JPD_SetWPENEndAddr(MS_PHYADDR u32ByteOffset);
#else
#if 1//defined(CHIP_T3) || defined(CHIP_T4) || defined(CHIP_T7) || defined(CHIP_JANUS) || defined(CHIP_U4) || defined(CHIP_T8)  || defined(CHIP_T9) || defined(CHIP_J2)
void MDrv_JPD_SetWriteProtect(MS_BOOL enable);
#endif
#endif

void MDrv_JPD_SetSpare(MS_U16 u16Value);
MS_U16 MDrv_JPD_GetSpare(void);
void MDrv_JPD_PrintQTable(void);

#if USE_MJPEG_FUNCTION
/* =============================== MJPEG =====================================*/
void MDrv_JPD_StopVPU(void);
MS_BOOL MDrv_JPD_RstVPU(void);
void MDrv_JPD_ReleaseVPU(void);
MS_BOOL MDrv_JPD_LoadCode(MS_PHYADDR u32Addr, MS_U32 u32Size, MS_U32 u32BinAddr, MS_U8 u8FwSrcType);
void MDrv_JPD_ConfigVPU(MS_PHYADDR u32StAddr, MS_U8 u8dlend_en);
MS_BOOL MDrv_JPD_IsFirmwareReady(void);

#if 0
MS_BOOL MDrv_JPD_SetVPUCmd(MS_U32 u32Cmd);
MS_BOOL MDrv_JPD_SetVPUCmdArg(MS_U32 u32Arg);
MS_U32 MDrv_JPD_CheckVPUStatus(MS_U32 u32Cmd);
MS_U32 MDrv_JPD_GetNextFreeFrameBuffIdx(void);
#endif
MS_U32 MDrv_JPD_SendVPUCommand(MJPEG_User_Cmd eCmd, MS_U32 u32Arg);

MS_BOOL MDrv_JPD_IsVPUOnMiu1(void);
MS_U32 MDrv_JPD_GetMiuBase(void);
MS_U32 MDrv_JPD_GetShareMemAddr(void);
void MDrv_JPD_ClearShareMemory(void);
MS_U32 MDrv_JPD_GetPtsTableAddr(void);

MS_BOOL MDrv_JPD_ResetPTS(MS_U32 u32PtsBase);
MS_U32 MDrv_JPD_GetPTS(void);
void MDrv_JPD_GetDispFrameInfo(void *pInfo);

void MDrv_JPD_DispFrame(MS_U32 u32DispIdx);
void MDrv_JPD_FreeFrame(MS_U32 u32DispIdx);
void* MDrv_JPD_GetNextDispFrame(void);
MS_U32 MDrv_JPD_GetNextDispQPtr(void);

void MDrv_JPD_EnableTurboFWMode(MS_BOOL bEnable);

JPD_Return MDrv_JPD_InitFw(MS_PHYADDR u32Addr, MS_U32 u32Size, MS_PHYADDR u32BinAddr, MS_U8 u8FwSrcType);
MJPEG_MSTAR_CHIP_ID MDrv_JPD_Get_Chip_ID(void);
#endif

#ifdef __cplusplus
}
#endif

#endif // _DRV_JPD_H_

