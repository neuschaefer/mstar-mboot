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

#ifndef _DRVGOP_PRIV_H_
#define _DRVGOP_PRIV_H_

////////////////////////////////////////////////////////////////////////////////
/// @file drvBDMA.h
/// @author MStar Semiconductor Inc.
/// @brief Byte DMA control driver
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"
#include "apiGOP.h"
#include "drvGOP.h"
#include "apiGOP_v2.h"

typedef struct _GOP_RESOURCE_PRIVATE
{
    MS_U32 u32ClientIdAllocator;
    MS_U32 u32LstGOPClientId;
    MS_U16 u16PnlWidth;
    MS_U16 u16PnlHeight;
    MS_U16 u16PnlHStr;
    MS_BOOL bHMirror;
    MS_BOOL bVMirror;
    MS_U16  ScrollBufNum;
    MS_U16  ScrollBufIdx;
    MS_U32  ScrollBuffer[MAX_GOP_SW_SCROLLNUM];

    GWIN_MAP gwinMap[SHARED_GWIN_MAX_COUNT];

    GOP_FB_POOL fbPool1;
    GOP_FB_POOL fbPool2;
    GOP_FBPOOL_ID fb_currentPoolId;

    MS_S32 s32OutputColorType[SHARED_GOP_MAX_COUNT];
    MS_BOOL bGopHasInitialized[SHARED_GOP_MAX_COUNT];
    MS_BOOL bGWINEnable[SHARED_GWIN_MAX_COUNT];
#if WINFB_INSHARED
    GOP_WinFB_INFO winFB[MAX_GWIN_FB_SUPPORT+1];
#endif
    MS_U8 GOP_StereoMode[SHARED_GOP_MAX_COUNT];
    MS_U16 u16APIStretchWidth[SHARED_GOP_MAX_COUNT]; //Store API set stretch win width(May Not sync with HW register in GOP 3D SBS mode)
    MS_U16 u16APIStretchHeight[SHARED_GOP_MAX_COUNT];
    MS_U8 GOP_TestPatternMode;
}GOP_RESOURCE_PRIVATE;

typedef MS_U32 (*IOCTL_GOP_INIT)(MS_U32, MS_U32*, MS_U32);
typedef MS_U32 (*IOCTL_GOP_GET_CHIPCAPS)(MS_U32*, MS_U32, MS_U32, MS_U32);
typedef MS_U32 (*IOCTL_GOP_SET_PROPERTY)(EN_GOP_PROPERTY, MS_U32, MS_U32*, MS_U32);
typedef MS_U32 (*IOCTL_GOP_GET_PROPERTY)(EN_GOP_PROPERTY, MS_U32, MS_U32*, MS_U32);
typedef MS_U32 (*IOCTL_GOP_SET_DST)(MS_U32, MS_U32*, MS_U32);
typedef MS_U32 (*IOCTL_GOP_SET_MUX)(MS_U32, MS_U32*, MS_U32);
typedef MS_U32 (*IOCTL_GOP_TESTPATTERN)(MS_U32, EN_GOP_TST_PATTERN);

typedef MS_U32 (*IOCTL_GOP_SET_STRETCH)(EN_GOP_STRETCH_TYPE, MS_U32, MS_U32*);
typedef MS_U32 (*IOCTL_GOP_GET_STRETCH)(EN_GOP_STRETCH_TYPE, MS_U32, MS_U32*);

typedef MS_U32 (*IOCTL_GOP_MAPFB2WIN)(MS_U32, MS_U32);
typedef MS_U32 (*IOCTL_GOP_SET_WININFO)(MS_U32, MS_U32, MS_U32*, MS_U32);
typedef MS_U32 (*IOCTL_GOP_GET_WININFO)(MS_U32, MS_U32*, MS_U32*);
typedef MS_U32 (*IOCTL_GOP_SET_DISPLAY)(MS_U32, MS_U32, MS_U32*, MS_U32);

typedef MS_U32 (*IOCTL_GOP_GFLIP_CLEARQUEUE)(MS_U32);
typedef MS_U32 (*IOCTL_GOP_GFLIP_SWITCHGWIN)(MS_U32, MS_U32*, MS_U32);
typedef MS_U32 (*IOCTL_GOP_GFLIP_SWITCHMULTIGWIN)(MS_U32, MS_U32*, MS_U32);

typedef MS_U32 (*IOCTL_GOP_FB_CREATE)(MS_U32, MS_U32*, MS_U32);
typedef MS_U32 (*IOCTL_GOP_FB_DESTROY)(MS_U32, MS_U32*, MS_U32);
typedef MS_U32 (*IOCTL_GOP_FB_SETINFO)(MS_U32, MS_U32*, MS_U32);
typedef MS_U32 (*IOCTL_GOP_FB_GETINFO)(MS_U32, MS_U32*, MS_U32);


typedef MS_U32 (*IOCTL_GOP_PALETTE_SET_CONFIG)(MS_U32, MS_U32, MS_U32*, MS_U32);
typedef MS_U32 (*IOCTL_GOP_PALETTE_SET_ENTRY)(MS_U32, MS_U32, MS_U32, MS_U32*, MS_U32);
typedef MS_U32 (*IOCTL_GOP_PALETTE_GET_ENTRY)(MS_U32, MS_U32*, MS_U32);


typedef MS_U32 (*IOCTL_GOP_SET_SCROLL)(MS_U32, MS_U32*, MS_U32);
typedef MS_U32 (*IOCTL_GOP_DWIN_CAPTURE)(MS_U32,MS_U32, MS_U32*, MS_U32);
typedef MS_U32 (*IOCTL_GOP_DWIN_GETRINGBUFFERINFO)(MS_U32,MS_U32, MS_U32*, MS_U32);

typedef MS_U32 (*IOCTL_GOP_UPDATE)(MS_U32,MS_U32, MS_U32*, MS_U32);


typedef struct _GOP_INSTANT_PRIVATE
{
    IOCTL_GOP_INIT                fpGOPInit;
    IOCTL_GOP_GET_CHIPCAPS        fpGOPGetChipCaps;
    IOCTL_GOP_SET_PROPERTY        fpGOPSetProperty;
    IOCTL_GOP_GET_PROPERTY        fpGOPGetProperty;
    IOCTL_GOP_SET_DST             fpGOPSetDst;
    IOCTL_GOP_SET_MUX             fpGOPSetMux;
    IOCTL_GOP_TESTPATTERN         fpGOPTestPattern;
    IOCTL_GOP_SET_STRETCH         fpGOPSetStretch;
    IOCTL_GOP_GET_STRETCH         fpGOPGetStretch;
    IOCTL_GOP_MAPFB2WIN           fpGOPMapFB2Win;

    IOCTL_GOP_SET_WININFO         fpGOPSetWinInfo;
    IOCTL_GOP_GET_WININFO         fpGOPGetWinInfo;
    IOCTL_GOP_SET_DISPLAY         fpGOPSetDisplay;

    IOCTL_GOP_GFLIP_CLEARQUEUE    fpGOPGFlipClearQueue;
    IOCTL_GOP_GFLIP_SWITCHGWIN    fpGOPGFlipSwitchWin;
    IOCTL_GOP_GFLIP_SWITCHMULTIGWIN fpGOPGFlipSwitchMultiWin;
    IOCTL_GOP_FB_CREATE           fpGOPFBCreate;
    IOCTL_GOP_FB_DESTROY          fpGOPFBDestroy;
    IOCTL_GOP_FB_SETINFO          fpGOPFBSetInfo;
    IOCTL_GOP_FB_GETINFO          fpGOPFBGetInfo;
    IOCTL_GOP_PALETTE_SET_CONFIG  fpGOPPaletteSetConfig;
    IOCTL_GOP_PALETTE_SET_ENTRY   fpGOPPaletteSetEntry;
    IOCTL_GOP_PALETTE_GET_ENTRY   fpGOPPaletteGetEntry;

    IOCTL_GOP_SET_SCROLL          fpGOPSetScroll;
    IOCTL_GOP_DWIN_CAPTURE        fpGOPDwinCapture;

    IOCTL_GOP_DWIN_GETRINGBUFFERINFO fpGOPDwinGetRingBuffer;
    IOCTL_GOP_UPDATE              fpGOPUpdate;

}GOP_INSTANT_PRIVATE;


void GOPRegisterToUtopia(void);
MS_U32 GOPOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
MS_U32 GOPClose(void* pInstance);
MS_U32 GOPIoctl(void* pInstance, MS_U32 u32Cmd, void* pArgs);

#ifdef __cplusplus
}
#endif
#endif // _DRVBDMA_PRIV_H_
