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
// comply with all applicable laws and regulations
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
//    or otherwise
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

#ifndef _MVOP_H_
#define _MVOP_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"
//******** ENUM DEFINITIONS ********//
enum
{
    E_MVOP_POOL_ID_INTERNAL = 0, // just for test, please refine.
} E_MVOP_POOL_ID;


typedef enum
{
    //Main MVOP
    E_MVOP_CMD_INIT,
    E_MVOP_CMD_EXIT,
    E_MVOP_CMD_ENABLE,
    E_MVOP_CMD_SET_INPUTCFG,
    E_MVOP_CMD_SET_OTPUTCFG,
    E_MVOP_CMD_ENABLE_BLACK_BG,
    E_MVOP_CMD_ENABLE_UV_SHIFT,
    E_MVOP_CMD_SET_MONO_MODE,

    E_MVOP_CMD_GET_HSIZE,
    E_MVOP_CMD_GET_VSIZE,
    E_MVOP_CMD_GET_HSTART,
    E_MVOP_CMD_GET_VSTART,
    E_MVOP_CMD_GET_IS_INTERLACE,
    E_MVOP_CMD_GET_IS_HDUPLICATE,
    E_MVOP_CMD_GET_IS_ENABLE,
    E_MVOP_CMD_GET_OUTPUT_TIMING,
    E_MVOP_CMD_GET_LIBVER,
    E_MVOP_CMD_CHECK_CAPABILITY,
    E_MVOP_CMD_GET_MAX_HOFFSET,
    E_MVOP_CMD_GET_MAX_VOFFSET,

    E_MVOP_CMD_SET_DBG_LEVEL,
    E_MVOP_CMD_GET_INFO,
    E_MVOP_CMD_GET_STATUS,
    E_MVOP_CMD_SET_CLK,
    E_MVOP_CMD_SET_PATTERN,
    E_MVOP_CMD_SET_TILE_FORMAT,
    E_MVOP_CMD_GET_DST_INFO,
    E_MVOP_CMD_SET_FIXVTT,
    E_MVOP_CMD_SET_MMIO_MAPBASE,
    E_MVOP_CMD_MIU_SWITCH,
    E_MVOP_CMD_SET_BASEADD,
    E_MVOP_CMD_SEL_OP_FIELD,
    E_MVOP_CMD_SET_REGSIZE_FROM_MVD,
    E_MVOP_CMD_SET_START_POS,
    E_MVOP_CMD_SET_IMAGE_WIDTH_HIGHT,
    E_MVOP_CMD_SET_VOP_MIRROR_MODE,
    E_MVOP_CMD_INV_OP_VS,
    E_MVOP_CMD_FORCE_TOP,
    E_MVOP_CMD_ENABLE_FREERUN_MODE,
    E_MVOP_CMD_GET_BASE_ADD,

    //Sub MVOP
    E_MVOP_CMD_SUB_INIT,
    E_MVOP_CMD_SUB_EXIT,
    E_MVOP_CMD_SUB_ENABLE,
    E_MVOP_CMD_SUB_SET_INPUTCFG,
    E_MVOP_CMD_SUB_SET_OTPUTCFG,

    E_MVOP_CMD_SUB_ENABLE_BLACK_BG,
    E_MVOP_CMD_SUB_ENABLE_UV_SHIFT ,
    E_MVOP_CMD_SUB_SET_MONO_MODE,
    E_MVOP_CMD_SUB_GET_HSIZE,
    E_MVOP_CMD_SUB_GET_VSIZE,
    E_MVOP_CMD_SUB_GET_HSTART,
    E_MVOP_CMD_SUB_GET_VSTART,
    E_MVOP_CMD_SUB_GET_IS_INTERLACE,
    E_MVOP_CMD_SUB_GET_IS_HDUPLICATE,
    E_MVOP_CMD_SUB_GET_IS_ENABLE,
    E_MVOP_CMD_SUB_GET_OUTPUT_TIMING,
    E_MVOP_CMD_SUB_CHECK_CAPABILITY,
    E_MVOP_CMD_SUB_GET_MAXHOFFSET,
    E_MVOP_CMD_SUB_GET_MAXVOFFSET,
    E_MVOP_CMD_SUB_SET_CLK,
    E_MVOP_CMD_SUB_SET_PATTERN,
    E_MVOP_CMD_SUB_SET_TILE_FORMAT,
    E_MVOP_CMD_SUB_GET_DST_INFO,
    E_MVOP_CMD_SUB_SET_FIXVTT,
    E_MVOP_CMD_SUB_SET_MMIO_MAPBASE,
    E_MVOP_CMD_SUB_MIU_SWITCH,
    E_MVOP_CMD_SUB_SET_BASEADD,
    E_MVOP_CMD_SUB_SET_VOP_MIRRORMODE,
    E_MVOP_CMD_SUB_ENABLE_FREERUN_MODE,
    E_MVOP_CMD_SUB_GET_BASEADD,

    //Third MVOP
    E_MVOP_CMD_EX_INIT,
    E_MVOP_CMD_EX_EXIT,
    E_MVOP_CMD_EX_ENABLE,
    E_MVOP_CMD_EX_SET_INPUTCFG,
    E_MVOP_CMD_EX_SET_OTPUTCFG,

    E_MVOP_CMD_EX_SET_CLK,
    E_MVOP_CMD_EX_SET_PATTERN,
    E_MVOP_CMD_EX_SET_TILEFORMAT,
    E_MVOP_CMD_EX_ENABLE_UV_SHIFT,
    E_MVOP_CMD_EX_ENABLE_BLACK_BG,
    E_MVOP_CMD_EX_SET_MONO_MODE,
    E_MVOP_CMD_EX_SET_FIXVTT,
    E_MVOP_CMD_EX_MIU_SWITCH,
    E_MVOP_CMD_EX_SET_VOP_MIRRORMODE,
    E_MVOP_CMD_EX_ENABLE_FREERUN_MODE,

    E_MVOP_CMD_EX_GET_OUTPUT_TIMING,
    E_MVOP_CMD_EX_GET_IS_ENABLE,
    E_MVOP_CMD_EX_GET_HSIZE,
    E_MVOP_CMD_EX_GET_VSIZE,
    E_MVOP_CMD_EX_GET_HSTART,
    E_MVOP_CMD_EX_GET_VSTART,
    E_MVOP_CMD_EX_GET_IS_INTERLACE,
    E_MVOP_CMD_EX_GET_IS_HDUPLICATE,
    E_MVOP_CMD_EX_GET_STATUS,
    E_MVOP_CMD_EX_CHECK_CAPABILITY,
    E_MVOP_CMD_EX_GET_DST_INFO,

    E_MVOP_CMD_SEND_BLUE_SCREEN,
    E_MVOP_CMD_SET_COMMAND,
    E_MVOP_CMD_GET_COMMAND,
    E_MVOP_CMD_SET_FREQUENCY,

    E_MVOP_CMD_ENABLE_INTERRUPT,
    E_MVOP_CMD_GET_INT_STATUS,
    E_MVOP_CMD_SUB_ENABLE_INTERRUPT,
    E_MVOP_CMD_SUB_GET_INT_STATUS,
    E_MVOP_CMD_EX_ENABLE_INTERRUPT,
    E_MVOP_CMD_EX_GET_INT_STATUS,

    //E_MVOP_CMD_SET_POWER_STATE,

    E_MVOP_CMD_NUM,
    E_MVOP_CMD_MAX = E_MVOP_CMD_NUM,
} E_MVOP_IOCTL_CMDS;

// Main MVOP
typedef struct
{
    MS_BOOL bEnable;
} stMVOP_ENABLE,*pstMVOP_ENABLE;

typedef struct
{
    MVOP_InputSel in;
    MVOP_InputCfg* pCfg;
    MVOP_Result eRet;
} stMVOP_SET_INPUTCFG,*pstMVOP_SET_INPUTCFG;

typedef struct
{
    MVOP_VidStat *pstVideoStatus;
    MS_BOOL bEnHDup;
    MVOP_Result eRet;
} stMVOP_SET_OTPUTCFG,*pstMVOP_SET_OTPUTCFG;

typedef struct
{
    MS_BOOL bEnable;
} stMVOP_ENABLE_UV_SHIFT,*pstMVOP_ENABLE_UV_SHIFT;

typedef struct
{
    MS_BOOL bEnable;
} stMVOP_SET_MONO_MODE,*pstMVOP_SET_MONO_MODE;

typedef struct
{
    MS_U16 u16Ret;
} stMVOP_GET_HSIZE,*pstMVOP_GET_HSIZE;

typedef struct
{
    MS_U16 u16Ret;
} stMVOP_GET_VSIZE,*pstMVOP_GET_VSIZE;

typedef struct
{
    MS_U16 u16Ret;
} stMVOP_GET_HSTART,*pstMVOP_GET_HSTART;

typedef struct
{
    MS_U16 u16Ret;
} stMVOP_GET_VSTART,*pstMVOP_GET_VSTART;

typedef struct
{
    MS_BOOL bRet;
} stMVOP_GET_IS_INTERLACE, *pstMVOP_GET_IS_INTERLACE;

typedef struct
{
    MS_BOOL bRet;
} stMVOP_GET_IS_HDUPLICATE, *pstMVOP_GET_IS_HDUPLICATE;

typedef struct
{
    MS_BOOL* pbEnable;
    MVOP_Result eRet;
} stMVOP_GET_IS_ENABLE, *pstMVOP_GET_IS_ENABLE;

typedef struct
{
    MVOP_Timing* pMVOPTiming;
    MVOP_Result eRet;
} stMVOP_GET_OUTPUT_TIMING, *pstMVOP_GET_OUTPUT_TIMING;

typedef struct
{
    const MSIF_Version **ppVersion;
    MVOP_Result eRet;
} stMVOP_GET_LIBVER,*pstMVOP_GET_LIBVER;

typedef struct
{
    MS_U16 u16HSize;
    MS_U16 u16VSize;
    MS_U16 u16Fps;
    MVOP_Result bRet;
} stMVOP_CHECK_CAPABILITY,*pstMVOP_CHECK_CAPABILITY;

typedef struct
{
    MS_U16 u16HSize;
    MS_U16 u16VSize;
    MS_U16 u16Fps;
    MS_U16 u16Ret;
} stMVOP_GET_MAX_HOFFSET, *pstMVOP_GET_MAX_HOFFSET;

typedef struct
{
    MS_U16 u16HSize;
    MS_U16 u16VSize;
    MS_U16 u16Fps;
    MS_U16 u16Ret;
} stMVOP_GET_MAX_VOFFSET, *pstMVOP_GET_MAX_VOFFSET;

typedef struct
{
    MS_U8 level;
} stMVOP_SET_DBG_LEVEL,*pstMVOP_SET_DBG_LEVEL;

typedef struct
{
    const MVOP_DrvInfo* pRet;
} stMVOP_GET_INFO, *pstMVOP_GET_INFO;

typedef struct
{
    MVOP_DrvStatus *pMVOPStat;
    MS_BOOL bRet;
} stMVOP_GET_STATUS, *pstMVOP_GET_STATUS;

typedef struct
{
    MS_BOOL bEnable;
} stMVOP_SET_CLK, *pstMVOP_SET_CLK;

typedef struct
{
    MVOP_Pattern enMVOPPattern;
} stMVOP_SET_PATTERN, *pstMVOP_SET_PATTERN;

typedef struct
{
    MVOP_TileFormat eTileFmt;
    MS_BOOL bRet;
} stMVOP_SET_TILE_FORMAT, *pstMVOP_SET_TILE_FORMAT;

typedef struct
{
    MVOP_DST_DispInfo *pDstInfo;
    MS_U32 u32SizeofDstInfo;
    MS_BOOL bRet;
} stMVOP_GET_DST_INFO, *pstMVOP_GET_DST_INFO;

typedef struct
{
    MS_U16 u16FixVtt;
    MS_BOOL bRet;
} stMVOP_SET_FIXVTT, *pstMVOP_SET_FIXVTT;

typedef struct
{
    MS_BOOL bRet;
} stMVOP_SET_MMIO_MAPBASE, *pstMVOP_SET_MMIO_MAPBASE;

typedef struct
{
    MS_U8 u8Miu;
    MVOP_Result eRet;
} stMVOP_MIU_SWITCH, *pstMVOP_MIU_SWITCH;

typedef struct
{
    MS_U32 u32YOffset;
    MS_U32 u32UVOffset;
    MS_BOOL bProgressive;
    MS_BOOL b422pack;
    MS_BOOL bRet;
} stMVOP_SET_BASEADD, *pstMVOP_SET_BASEADD;

typedef struct
{
    MS_BOOL bEnable;
} stMVOP_SEL_OP_FIELD, *pstMVOP_SEL_OP_FIELD;

typedef struct
{
    MS_BOOL bEnable;
} stMVOP_SET_REGSIZE_FROM_MVD, *pstMVOP_SET_REGSIZE_FROM_MVD;

typedef struct
{
    MS_U16 u16Xpos;
    MS_U16 u16Ypos;
} stMVOP_SET_START_POS, *pstMVOP_SET_START_POS;

typedef struct
{
    MS_U16 u16Width;
    MS_U16 u16Height;
    MS_BOOL bRet;
} stMVOP_SET_IMAGE_WIDTH_HIGHT, *pstMVOP_SET_IMAGE_WIDTH_HIGHT;

typedef struct
{
    MS_BOOL bEnable;
    MVOP_DrvMirror eMirrorMode;
} stMVOP_SET_VOP_MIRROR_MODE, *pstMVOP_SET_VOP_MIRROR_MODE;

typedef struct
{
    MS_BOOL bEnable;
} stMVOP_INV_OP_VS, *pstMVOP_INV_OP_VS;

typedef struct
{
    MS_BOOL bEnable;
} stMVOP_FORCE_TOP, *pstMVOP_FORCE_TOP;

typedef struct
{
    MS_BOOL bEnable;
    MS_BOOL bRet;
} stMVOP_ENABLE_FREERUN_MODE, *pstMVOP_ENABLE_FREERUN_MODE;

typedef struct
{
    MS_U32* u32YOffset;
    MS_U32* u32UVOffset;
} stMVOP_GET_BASE_ADD, *pstMVOP_GET_BASE_ADD;

// Sub MVOP
typedef struct
{
    MS_BOOL bEnable;
} stMVOP_SUB_ENABLE,*pstMVOP_SUB_ENABLE;

typedef struct
{
    MVOP_InputSel in;
    MVOP_InputCfg* pCfg;
    MVOP_Result eRet;
} stMVOP_SUB_SET_INPUTCFG,*pstMVOP_SUB_SET_INPUTCFG;

typedef struct
{
    MVOP_VidStat *pstVideoStatus;
    MS_BOOL bEnHDup;
    MVOP_Result eRet;
} stMVOP_SUB_SET_OTPUTCFG,*pstMVOP_SUB_SET_OTPUTCFG;

typedef struct
{
    MS_BOOL bEnable;
} stMVOP_SUB_ENABLE_UV_SHIFT,*pstMVOP_SUB_ENABLE_UV_SHIFT;

typedef struct
{
    MS_BOOL bEnable;
} stMVOP_SUB_SET_MONO_MODE,*pstMVOP_SUB_SET_MONO_MODE;

typedef struct
{
    MVOP_DrvStatus *pMVOPStat;
    MS_BOOL bRet;
} stMVOP_SUB_GET_STATUS, *pstMVOP_SUB_GET_STATUS;

typedef struct
{
    MS_U16 u16Ret;
} stMVOP_SUB_GET_HSIZE,*pstMVOP_SUB_GET_HSIZE;

typedef struct
{
    MS_U16 u16Ret;
} stMVOP_SUB_GET_VSIZE,*pstMVOP_SUB_GET_VSIZE;

typedef struct
{
    MS_U16 u16Ret;
} stMVOP_SUB_GET_HSTART,*pstMVOP_SUB_GET_HSTART;

typedef struct
{
    MS_U16 u16Ret;
} stMVOP_SUB_GET_VSTART,*pstMVOP_SUB_GET_VSTART;

typedef struct
{
    MS_BOOL bRet;
} stMVOP_SUB_GET_IS_INTERLACE, *pstMVOP_SUB_GET_IS_INTERLACE;

typedef struct
{
    MS_BOOL bRet;
} stMVOP_SUB_GET_IS_HDUPLICATE, *pstMVOP_SUB_GET_IS_HDUPLICATE;

typedef struct
{
    MS_BOOL* pbEnable;
    MVOP_Result eRet;
} stMVOP_SUB_GET_IS_ENABLE, *pstMVOP_SUB_GET_IS_ENABLE;

typedef struct
{
    MVOP_Timing* pMVOPTiming;
    MVOP_Result eRet;
} stMVOP_SUB_GET_OUTPUT_TIMING, *pstMVOP_SUB_GET_OUTPUT_TIMING;

typedef struct
{
    MS_U16 u16HSize;
    MS_U16 u16VSize;
    MS_U16 u16Fps;
    MS_BOOL bRet;
} stMVOP_SUB_CHECK_CAPABILITY,*pstMVOP_SUB_CHECK_CAPABILITY;

typedef struct
{
    MS_U16 u16HSize;
    MS_U16 u16VSize;
    MS_U16 u16Fps;
    MS_U16 u16Ret;
} stMVOP_SUB_GET_MAX_HOFFSET, *pstMVOP_SUB_GET_MAX_HOFFSET;

typedef struct
{
    MS_U16 u16HSize;
    MS_U16 u16VSize;
    MS_U16 u16Fps;
    MS_U16 u16Ret;
} stMVOP_SUB_GET_MAX_VOFFSET, *pstMVOP_SUB_GET_MAX_VOFFSET;

typedef struct
{
    MS_BOOL bEnable;
} stMVOP_SUB_SET_CLK, *pstMVOP_SUB_SET_CLK;

typedef struct
{
    MVOP_Pattern enMVOPPattern;
} stMVOP_SUB_SET_PATTERN, *pstMVOP_SUB_SET_PATTERN;

typedef struct
{
    MVOP_TileFormat eTileFmt;
    MS_BOOL bRet;
} stMVOP_SUB_SET_TILE_FORMAT, *pstMVOP_SUB_SET_TILE_FORMAT;

typedef struct
{
    MVOP_DST_DispInfo *pDstInfo;
    MS_U32 u32SizeofDstInfo;
    MS_BOOL bRet;
} stMVOP_SUB_GET_DST_INFO, *pstMVOP_SUB_GET_DST_INFO;

typedef struct
{
    MS_U16 u16FixVtt;
    MS_BOOL bRet;
} stMVOP_SUB_SET_FIXVTT, *pstMVOP_SUB_SET_FIXVTT;

typedef struct
{
    MS_BOOL bRet;
} stMVOP_SUB_SET_MMIO_MAPBASE, *pstMVOP_SUB_SET_MMIO_MAPBASE;

typedef struct
{
    MS_U8 u8Miu;
    MVOP_Result eRet;
} stMVOP_SUB_MIU_SWITCH, *pstMVOP_SUB_MIU_SWITCH;

typedef struct
{
    MS_U32 u32YOffset;
    MS_U32 u32UVOffset;
    MS_BOOL bProgressive;
    MS_BOOL b422pack;
    MS_BOOL bRet;
} stMVOP_SUB_SET_BASEADD, *pstMVOP_SUB_SET_BASEADD;

typedef struct
{
    MS_BOOL bEnable;
    MVOP_DrvMirror eMirrorMode;
} stMVOP_SUB_SET_VOP_MIRROR_MODE, *pstMVOP_SUB_SET_VOP_MIRROR_MODE;

typedef struct
{
    MS_BOOL bEnable;
    MS_BOOL bRet;
} stMVOP_SUB_ENABLE_FREERUN_MODE, *pstMVOP_SUB_ENABLE_FREERUN_MODE;

typedef struct
{
    MS_U32* u32YOffset;
    MS_U32* u32UVOffset;
} stMVOP_SUB_GET_BASE_ADD, *pstMVOP_SUB_GET_BASE_ADD;

// 3rd MVOP
typedef struct
{
    MVOP_DevID eID;
    MS_U32 u32InitParam;
    MVOP_Result eRet;
} stMVOP_EX_INIT,*pstMVOP_EX_INIT;

typedef struct
{
    MVOP_DevID eID;
    MS_U32 u32ExitParam;
    MVOP_Result eRet;
} stMVOP_EX_EXIT,*pstMVOP_EX_EXIT;

typedef struct
{
    MVOP_DevID eID;
    MS_BOOL bEnable;
    MVOP_Result eRet;
} stMVOP_EX_ENABLE,*pstMVOP_EX_ENABLE;

typedef struct
{
    MVOP_DevID eID;
    MVOP_InputSel in;
    MVOP_InputCfg* pCfg;
    MVOP_Result eRet;
} stMVOP_EX_SET_INPUTCFG,*pstMVOP_EX_SET_INPUTCFG;

typedef struct
{
    MVOP_DevID eID;
    MVOP_VidStat *pstVideoStatus;
    MS_BOOL bEnHDup;
    MVOP_Result eRet;
} stMVOP_EX_SET_OTPUTCFG,*pstMVOP_EX_SET_OTPUTCFG;

typedef struct
{
    MVOP_DevID eID;
    MS_BOOL bEnable;
} stMVOP_EX_SET_CLK, *pstMVOP_EX_SET_CLK;

typedef struct
{
    MVOP_DevID eID;
    MVOP_Pattern enMVOPPattern;
    MVOP_Result eRet;
} stMVOP_EX_SET_PATTERN, *pstMVOP_EX_SET_PATTERN;

typedef struct
{
    MVOP_DevID eID;
    MVOP_TileFormat eTileFmt;
    MVOP_Result eRet;
} stMVOP_EX_SET_TILE_FORMAT, *pstMVOP_EX_SET_TILE_FORMAT;

typedef struct
{
    MVOP_DevID eID;
    MS_BOOL bEnable;
    MVOP_Result eRet;
} stMVOP_EX_ENABLE_UV_SHIFT,*pstMVOP_EX_ENABLE_UV_SHIFT;

typedef struct
{
    MVOP_DevID eID;
    MVOP_Result eRet;
} stMVOP_EX_ENABLE_BLACK_BG,*pstMVOP_EX_ENABLE_BLACK_BG;

typedef struct
{
    MVOP_DevID eID;
    MS_BOOL bEnable;
    MVOP_Result eRet;
} stMVOP_EX_SET_MONO_MODE,*pstMVOP_EX_SET_MONO_MODE;

typedef struct
{
    MVOP_DevID eID;
    MS_U16 u16FixVtt;
    MVOP_Result eRet;
} stMVOP_EX_SET_FIXVTT, *pstMVOP_EX_SET_FIXVTT;

typedef struct
{
    MVOP_DevID eID;
    MS_U8 u8Miu;
    MVOP_Result eRet;
} stMVOP_EX_MIU_SWITCH, *pstMVOP_EX_MIU_SWITCH;

typedef struct
{
    MVOP_DevID eID;
    MS_BOOL bEnable;
    MVOP_DrvMirror eMirrorMode;
    MVOP_Result eRet;
} stMVOP_EX_SET_VOP_MIRROR_MODE, *pstMVOP_EX_SET_VOP_MIRROR_MODE;

typedef struct
{
    MVOP_DevID eID;
    MS_BOOL bEnable;
    MVOP_Result eRet;
} stMVOP_EX_ENABLE_FREERUN_MODE, *pstMVOP_EX_ENABLE_FREERUN_MODE;

typedef struct
{
    MVOP_DevID eID;
    MVOP_Timing* pMVOPTiming;
    MVOP_Result eRet;
} stMVOP_EX_GET_OUTPUT_TIMING, *pstMVOP_EX_GET_OUTPUT_TIMING;

typedef struct
{
    MVOP_DevID eID;
    MS_BOOL* pbEnable;
    MVOP_Result eRet;
} stMVOP_EX_GET_IS_ENABLE, *pstMVOP_EX_GET_IS_ENABLE;

typedef struct
{
    MVOP_DevID eID;
    MS_U16 u16Ret;
} stMVOP_EX_GET_HSIZE,*pstMVOP_EX_GET_HSIZE;

typedef struct
{
    MVOP_DevID eID;
    MS_U16 u16Ret;
} stMVOP_EX_GET_VSIZE,*pstMVOP_EX_GET_VSIZE;

typedef struct
{
    MVOP_DevID eID;
    MS_U16 u16Ret;
} stMVOP_EX_GET_HSTART,*pstMVOP_EX_GET_HSTART;

typedef struct
{
    MVOP_DevID eID;
    MS_U16 u16Ret;
} stMVOP_EX_GET_VSTART,*pstMVOP_EX_GET_VSTART;

typedef struct
{
    MVOP_DevID eID;
    MS_BOOL bRet;
} stMVOP_EX_GET_IS_INTERLACE, *pstMVOP_EX_GET_IS_INTERLACE;

typedef struct
{
    MVOP_DevID eID;
    MS_BOOL bRet;
} stMVOP_EX_GET_IS_HDUPLICATE, *pstMVOP_EX_GET_IS_HDUPLICATE;

typedef struct
{
    MVOP_DevID eID;
    MVOP_DrvStatus *pMVOPStat;
    MS_BOOL bRet;
} stMVOP_EX_GET_STATUS, *pstMVOP_EX_GET_STATUS;

typedef struct
{
    MVOP_DevID eID;
    MS_U32 u32InParam;
    MS_BOOL bRet;
} stMVOP_EX_CHECK_CAPABILITY,*pstMVOP_EX_CHECK_CAPABILITY;

typedef struct
{
    MVOP_DevID eID;
    MVOP_DST_DispInfo *pDstInfo;
    MS_U32 u32SizeofDstInfo;
    MS_BOOL bRet;
} stMVOP_EX_GET_DST_INFO, *pstMVOP_EX_GET_DST_INFO;

typedef struct
{
    MS_U16 u16Width;
    MS_U16 u16Height;
    MVOP_Result bRet;
} stMVOP_SEND_BLUE_SCREEN, *pstMVOP_SEND_BLUE_SCREEN;

typedef struct
{
    MVOP_Handle* stHd;
    MVOP_Command eCmd;
    void* pPara;
    MVOP_Result bRet;
} stMVOP_SET_COMMAND, *pstMVOP_SET_COMMAND;

typedef struct
{
    MVOP_Handle* stHd;
    MVOP_Command eCmd;
    void* pPara;
    MS_U32 u32ParaSize;
    MVOP_Result bRet;
} stMVOP_GET_COMMAND, *pstMVOP_GET_COMMAND;

typedef struct
{
    MVOP_FREQUENCY eFreq;
} stMVOP_SET_FREQUENCY, *pstMVOP_SET_FREQUENCY;

typedef struct
{
    MS_U8 eIntType;
    MS_BOOL bRet;
} stMVOP_ENABLE_INTERRUPT, *pstMVOP_ENABLE_INTERRUPT;

typedef struct
{
    MS_U8 u8Ret;
} stMVOP_GET_INT_STATUS, *pstMVOP_GET_INT_STATUS;

typedef struct
{
    MS_U8 eIntType;
    MS_BOOL bRet;
} stMVOP_SUB_ENABLE_INTERRUPT, *pstMVOP_SUB_ENABLE_INTERRUPT;

typedef struct
{
    MS_U8 u8Ret;
} stMVOP_SUB_GET_INT_STATUS, *pstMVOP_SUB_GET_INT_STATUS;

typedef struct
{
    MVOP_DevID eID;
    MS_U8 eIntType;
    MS_BOOL bRet;
} stMVOP_EX_ENABLE_INTERRUPT, *pstMVOP_EX_ENABLE_INTERRUPT;

typedef struct
{
    MVOP_DevID eID;
    MS_U8 u8Ret;
} stMVOP_EX_GET_INT_STATUS, *pstMVOP_EX_GET_INT_STATUS;

#if 0
typedef struct
{
    EN_POWER_MODE u16PowerState;
    MS_U32 u32Ret;
} stMVOP_SET_POWER_STATE, *pstMVOP_SET_POWER_STATE;
#endif

// OBSOLETE STRUCT **END**, please avoid using these

void MVOPRegisterToUtopia(FUtopiaOpen ModuleType);
MS_U32 MVOPOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
MS_U32 MVOPClose(void* pInstance);
MS_U32 MVOPIoctl(void* pInstance, MS_U32 u32Cmd, void* pArgs);

#ifdef __cplusplus
}
#endif

#undef _MVOP_H_
#endif //_mvop_H_
