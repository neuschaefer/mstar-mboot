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
    DIP_ERR_INVALID_BUFFER_CNT,
    DIP_ERR_INVALID_BUFFER_START,
    DIP_ERR_INVALID_BUFFER_WIDTH,
    DIP_ERR_INVALID_BUFFER_HEIGHT,
    DIP_ERR_INVALID_BUFFER_SZIE
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

typedef enum
{
    E_DIP_INIT ,
    E_DIP_ENABLE ,
    E_DIP_ONESHOT ,
    E_DIP_SET_INFO ,
    E_DIP_SET_YUORD ,
    E_DIP_GET_BUFSTUS ,    
    E_DIP_CLR_BUFSTUS ,
    E_DIP_SET_SCANTYPE ,
    E_DIP_SET_INPUTMODE ,
    E_DIP_SET_WEBCAM ,
} DIP_CNTL;

typedef enum
{
    //By HW or SW DIP
    E_DIP_CAP_CONFIG,
}
EN_DIP_CAPS;

typedef enum
{
    E_DIP_CFG_SW =0,
    E_DIP_CFG_HW =1,
}
EN_DIP_Config;

typedef struct
{           
    /// dwin dram starting address (unit: Byte).
    MS_U32 u32FbAddr0;
    ///  dwin access address high bond (unit: Byte).
    MS_U32 u32FbAddr1;
    /// dwin width (unit: pix).
    MS_U16 u16W;
    /// height (unit: line).
    MS_U16 u16H;
    
    MS_U8  u8BufCnt;
    
} DIP_PROPERTY;

typedef struct
{           
    /// dwin dram starting address (unit: Byte).
    MS_U32 u32WebCamAddr0;
    ///  dwin access address high bond (unit: Byte).
    MS_U32 u32WebCamAddr1;
    /// dwin width (unit: pix).
    MS_U16 u16WebCamW;
    /// height (unit: line).
    MS_U16 u16WebCamH;
    
} DIP_WEBCAM_PROPERTY;

DIP_ERRCODE MDrv_DIP_GetChipCaps(EN_DIP_CAPS eCapType, MS_U32* pRet, MS_U32 ret_size);

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
MS_BOOL MDrv_DIP_RegisterXCSetDIPInfo(DIP_ERRCODE (*fpDIP_CB)(MS_U16 cmd,MS_U32 *arg,MS_U16 size));

#ifdef __cplusplus
}
#endif

#endif
