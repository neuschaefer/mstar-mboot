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
////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVDIP_H_
#define _DRVDIP_H_

////////////////////////////////////////////////////////////////////////////////
/// @file drvDIP.h
/// @author MStar Semiconductor Inc.
/// @brief DIP control driver
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

#define ENABLE_DI_BUFFER_VERIFY     0
#define MONITOR_INT_INTERVAL        0
#define FRAME_CHECK                 1
#define DI_BUFFER_SKIP_CHECK        0


#define MAX_NR_BUFF_CNT     2
#define MAX_DATA_BUFF_CNT   16
#define MAX_BUFF_WIDTH      0x440   //1088
#define MAX_BUFF_HEIGHT     0x240   //576

typedef struct
{
    MS_U8               u8NR_BufCnt;
    MS_U32              u32NR_RationBuf;
    MS_U32              u32NR_DataBuf[MAX_NR_BUFF_CNT];
    MS_U32              u32NR_BufWidth;
    MS_U32              u32NR_BufHeight;
} NR_INFO;

typedef struct
{
    MS_U8               u8DI_BufCnt;
    MS_U32              u32DI_YBuf[MAX_DATA_BUFF_CNT];
    MS_U32              u32DI_CBuf[MAX_DATA_BUFF_CNT];
    MS_U32              u32DI_BufWidth;
    MS_U32              u32DI_BufHeight;
    MS_U16              u16Valid_DIBuf;
    MS_U32              u32DI_FrameCnt;
} DI_INFO;


typedef struct
{
    MS_BOOL             Init;
    NR_INFO             NR_Info;
    DI_INFO             DI_Info;

} DIP_MGR;

typedef enum
{
    DIP_ERR_OK,
    DIP_ERR_FAIL,
}DIP_ERRCODE;

typedef enum
{
    E_DIP_INPUT_UNKNOWN = 0,
    E_DIP_INPUT_NTSC,
    E_DIP_INPUT_PAL,
    E_DIP_INPUT_WEBCAM,
}DIP_INPUT;

typedef enum
{
    E_DIP_YUV_ORDER_UYVY = 0,
    E_DIP_YUV_ORDER_YUYV = 1,
} DIP_YUV_ORDER;

void MDrv_DIP_Init(MS_U32 u32InputMode);
void MDrv_DIP_SetFrameInfo(MS_U32 u32FrameX, MS_U32 u32FrameY,
    MS_U32 u32FrameWidth, MS_U32 u32FrameHeight, MS_BOOL bInterLace);
void MDrv_DIP_InputMode(MS_U32 u32InputMode);
void MDrv_DIP_SetNRBuf(MS_U8 u8BufCnt, MS_U32 u32BufWidth, MS_U32 u32BufHeight,
                               MS_U32 u32BufStart, MS_U32 u32BufEnd);
void MDrv_DIP_SetDIBuf(MS_U8 u8BufCnt, MS_U32 u32BufWidth, MS_U32 u32BufHeight,
                               MS_U32 u32BufStart, MS_U32 u32BufEnd);
void MDrv_DIP_GetDIInfo(DI_INFO *pDIInfo);
void MDrv_DIP_GetNRInfo(NR_INFO *pNRInfo);
void MDrv_DIP_EnableNRDI(MS_BOOL bEnableNR, MS_BOOL bEnableSNR, MS_BOOL bEnableTNR, MS_BOOL bEnableDI);
void MDrv_DIP_GetDIBufCount(MS_U32 *pu32Count);
void MDrv_DIP_ClearDIBufStatus(MS_U8 u8Arg);
void MDrv_DIP_GetDIFrameCount(MS_U32 *pu32FrameCount);
void MDrv_DIP_GetDIBufStatus(MS_U32 *pu32DIBufStatus);
void MDrv_DIP_GetDIShow(void);
void MDrv_DIP_SetMMIOMapBase(void);
void MDrv_DIP_SetWebCamBuff(MS_U32 u32BufWidth, MS_U32 u32BufHeight,
                               MS_U32 u32BufStart, MS_U32 u32BufEnd);
void MDrv_DIP_Trigger(void);
void MDrv_DIP_SetYUVOrder(DIP_YUV_ORDER dipOrder);
MS_BOOL MDrv_DIP_OneShot(MS_U32 u32BufWidth, MS_U32 u32BufHeight
    , MS_U32 u32InputBufStart, MS_U32 u32OutputBufStart, MS_U8 u8OutputBufCnt);

#ifdef __cplusplus
}
#endif

#endif
