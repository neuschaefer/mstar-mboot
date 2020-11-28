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

#ifndef _API_ACE_PRIV_H_
#define _API_ACE_PRIV_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"
//******** ENUM DEFINITIONS ********//
enum
{
    E_ACE_POOL_ID_INTERNAL = 0, // just for test, please refine.
} E_ACE_POOL_ID;


typedef enum
{
    E_ACE_CMD_INIT,
    E_ACE_CMD_EXIT,
    E_ACE_CMD_DMS,
    E_ACE_CMD_SETPCYUV2RGB,
    E_ACE_CMD_SELECTYUVTORGBMATRIX,
    E_ACE_CMD_SETCOLORCORRECTIONTABLE,
    E_ACE_CMD_SETPCSRGBTABLE,
    E_ACE_CMD_GETCOLORMATRIX,
    E_ACE_CMD_SETCOLORMATRIX,
    E_ACE_CMD_SETBYPASSCOLORMATRIX,
    E_ACE_CMD_SETIHC,
    E_ACE_CMD_PATCHDTGCOLORCHECKER,
    E_ACE_CMD_GETACEINFO,
    E_ACE_CMD_GETACEINFOEX,
    E_ACE_CMD_PICSETCONTRAST,
    E_ACE_CMD_PICSETBRIGHTNESS,
    E_ACE_CMD_PICSETBRIGHTNESSPRECISE,
    E_ACE_CMD_PICSET_PRE_Y_OFFSET,
    E_ACE_CMD_PICGET_PRE_Y_OFFSET,
    E_ACE_CMD_PICSETHUE,
    E_ACE_CMD_SKIPWAITVSYNC,
    E_ACE_CMD_PICSETSATURATION,
    E_ACE_CMD_PICSETSHARPNESS,
    E_ACE_CMD_PICSETCOLORTEMP,
    E_ACE_CMD_PICSETCOLORTEMPEX,
    E_ACE_CMD_PICSETPOSTCOLORTEMP_V02,
    E_ACE_CMD_SETFLESHTONE,
    E_ACE_CMD_SETBLACKADJUST,
    E_ACE_CMD_SET_IHC_SRAM,
    E_ACE_CMD_SET_ICC_SRAM,
    E_ACE_CMD_ENABLEMWE,
    E_ACE_CMD_MWESETMIRRORMODE,
    E_ACE_CMD_MWECLONEVISUALEFFECT,
    E_ACE_CMD_MWESETREGTABLE,
    E_ACE_CMD_SETMWELOADFROMPQ,
    E_ACE_CMD_MWESTATUS,
    E_ACE_CMD_MWEHANDLE,
    E_ACE_CMD_MWEFUNCSEL,
    E_ACE_CMD_MWESETDISPWIN,
    E_ACE_CMD_3DCLONEPQMAP,
    E_ACE_CMD_DNR_BLENDING_NRTBL,
    E_ACE_CMD_DNR_BLENDING_MISC,
    E_ACE_CMD_DNR_BLENDING,
    E_ACE_CMD_DNR_GET_PRECISIONSHIFT,
    E_ACE_CMD_DNR_GETMOTION_WEIGHT,
    E_ACE_CMD_DNR_GETLUMA_WEIGHT,
    E_ACE_CMD_DNR_GETNOISE_WEIGHT,
    E_ACE_CMD_DNR_GETMOTION,
    E_ACE_CMD_DNR_INIT_MOTION,
    E_ACE_CMD_DNR_INIT_LUMA,
    E_ACE_CMD_DNR_INIT_NOISE,
    E_ACE_CMD_DNR_SETPARAM,
    E_ACE_CMD_DNR_GETPARAM,
    E_ACE_CMD_DNR_SETNRTBL,
    E_ACE_CMD_GETLIBVER,
    E_ACE_CMD_GETINFO,
    E_ACE_CMD_GETSTATUS,
    E_ACE_CMD_SETDBGLEVEL,
    E_ACE_CMD_COLORCORRECTIONTABLE,
    E_ACE_CMD_SETCOLORMATRIXCONTROL,
    E_ACE_CMD_SETRBCHANNELRANGE,
    E_ACE_CMD_PICSETPOSTCOLORTEMP,
    E_ACE_CMD_PICSETPOSTCOLORTEMPEX,
    E_ACE_CMD_PICSETPOSTCOLORTEMP2,
    E_ACE_CMD_PICSETPOSTCOLORTEMP2EX,
    E_ACE_CMD_SET_POWERSTATE,
    E_ACE_CMD_NUM,
    E_ACE_CMD_MAX = E_ACE_CMD_NUM,
} E_ACE_IOCTL_CMDS;

typedef struct _stACE_Init
{
    XC_ACE_InitData *pstXC_ACE_InitData;
    MS_U32 u32InitDataLen;
    MS_BOOL bReturn;
} stACE_Init,*pstACE_Init;

typedef struct _stACE_Exit
{
    MS_BOOL bReturn;
} stACE_Exit,*pstACE_Exit;

typedef struct _stACE_DMS
{
    MS_BOOL eWindow;
    MS_BOOL bisATV;
} stACE_DMS,*pstACE_DMS;

typedef struct _stACE_SetPCYUV2RGB
{
    MS_BOOL eWindow;
    MS_BOOL bEnable;
} stACE_SetPCYUV2RGB,*pstACE_SetPCYUV2RGB;

typedef struct _stACE_SelectYUVtoRGBMatrix
{
    MS_BOOL eWindow;
    MS_U8 ucMatrix;
    MS_S16* psUserYUVtoRGBMatrix;
} stACE_SelectYUVtoRGBMatrix,*pstACE_SelectYUVtoRGBMatrix;

typedef struct _stACE_SetColorCorrectionTable
{
    MS_BOOL bScalerWin;
} stACE_SetColorCorrectionTable,*pstACE_SetColorCorrectionTable;

typedef struct _stACE_SetPCsRGBTable
{
    MS_BOOL bScalerWin;
} stACE_SetPCsRGBTable,*pstACE_SetPCsRGBTable;

typedef struct _stACE_ColorMatrix
{
    MS_BOOL eWindow;
    MS_U16* pu16Matrix;
} stACE_ColorMatrix,*pstACE_ColorMatrix;

typedef struct _stACE_SetBypassColorMatrix
{
    MS_BOOL bEnable;
    E_XC_ACE_RESULT eResult;
} stACE_SetBypassColorMatrix,*pstACE_SetBypassColorMatrix;

typedef struct _stACE_SetIHC
{
    MS_BOOL bScalerWin;
    XC_ACE_IHC_COLOR_TYPE eIHC;
    MS_U8 u8Val;
    MS_BOOL bReturn;
} stACE_SetIHC,*pstACE_SetIHC;

typedef struct _stACE_PatchDTGColorChecker
{
    MS_U8 u8Mode;
} stACE_PatchDTGColorChecker,*pstACE_PatchDTGColorChecker;

typedef struct _stACE_GetACEInfo
{
    MS_BOOL bWindow;
    E_XC_ACE_INFOTYPE eXCACEInfoType;
    MS_U16 u16Return;
} stACE_GetACEInfo,*pstACE_GetACEInfo;

typedef struct _stACE_GetACEInfoEx
{
    MS_BOOL bWindow;
    XC_ACE_InfoEx *pInfoEx;
} stACE_GetACEInfoEx,*pstACE_GetACEInfoEx;

typedef struct _stACE_PicSetBrightness
{
    MS_BOOL eWindow;
    MS_U8 u8Brightness_R;
    MS_U8 u8Brightness_G;
    MS_U8 u8Brightness_B;
} stACE_PicSetBrightness,*pstACE_PicSetBrightness;

typedef struct _stACE_PicSetBrightnessPrecise
{
    MS_BOOL eWindow;
    MS_U16 u16Brightness_R;
    MS_U16 u16Brightness_G;
    MS_U16 u16Brightness_B;
} stACE_PicSetBrightnessPrecise,*pstACE_PicSetBrightnessPrecise;

typedef struct _stACE_PreYOffset
{
    MS_BOOL eWindow;
    MS_U8 u8PreYOffset;
} stACE_PreYOffset,*pstACE_PreYOffset;

typedef struct _stACE_PicSetSharpness
{
    MS_BOOL eWindow;
    MS_U8 u8Sharpness;
} stACE_PicSetSharpness,*pstACE_PicSetSharpness;

typedef struct _stACE_PicSetHue
{
    MS_BOOL eWindow;
    MS_BOOL bUseYUVSpace;
    MS_U8 u8Hue;
} stACE_PicSetHue,*pstACE_PicSetHue;

typedef struct _stACE_PicSetContrast
{
    MS_BOOL eWindow;
    MS_BOOL bUseYUVSpace;
    MS_U8 u8Contrast;
} stACE_PicSetContrast,*pstACE_PicSetContrast;

typedef struct _stACE_SkipWaitVsync
{
    MS_BOOL eWindow;
    MS_BOOL bIsSkipWaitVsyn;
    E_XC_ACE_RESULT eResult;
} stACE_SkipWaitVsync,*pstACE_SkipWaitVsync;

typedef struct _stACE_PicSetSaturation
{
    MS_BOOL eWindow;
    MS_BOOL bUseYUVSpace;
    MS_U8 u8Saturation;
} stACE_PicSetSaturation,*pstACE_PicSetSaturation;

typedef struct _stACE_SetFleshTone
{
    MS_BOOL eWindow;
    MS_BOOL bEn;
    MS_U8 u8FleshTone;
} stACE_SetFleshTone,*pstACE_SetFleshTone;

typedef struct _stACE_SetBlackAdjust
{
    MS_BOOL eWindow;
    MS_U8 u8BlackAdjust;
} stACE_SetBlackAdjust,*pstACE_SetBlackAdjust;

typedef struct _stACE_PicSetColorTemp
{
    MS_BOOL eWindow;
    MS_BOOL bUseYUVSpace;
    XC_ACE_color_temp* pstColorTemp;
} stACE_PicSetColorTemp,*pstACE_PicSetColorTemp;

typedef struct _stACE_PicSetColorTempEx
{
    MS_BOOL eWindow;
    MS_BOOL bUseYUVSpace;
    XC_ACE_color_temp_ex* pstColorTemp;
} stACE_PicSetColorTempEx,*pstACE_PicSetColorTempEx;

typedef struct _stACE_PicSetPostColorTemp_V02
{
    MS_BOOL eWindow;
    XC_ACE_color_temp_ex2* pstColorTemp;
} stACE_PicSetPostColorTemp_V02,*pstACE_PicSetPostColorTemp_V02;

typedef struct _stACE_PicSetPostColorTemp
{
    MS_BOOL eWindow;
    XC_ACE_color_temp* pstColorTemp;
} stACE_PicSetPostColorTemp,*pstACE_PicSetPostColorTemp;

typedef struct _stACE_PicSetPostColorTempEx
{
    MS_BOOL eWindow;
    MS_BOOL bUseYUVSpace;
    XC_ACE_color_temp_ex* pstColorTemp;
} stACE_PicSetPostColorTempEx,*pstACE_PicSetPostColorTempEx;

typedef struct _stACE_GetLibVer
{
    const MSIF_Version **ppVersion;
    E_XC_ACE_RESULT eResult;
} stACE_GetLibVer,*pstACE_GetLibVer;

typedef struct _stACE_GetInfo
{
    const XC_ACE_ApiInfo* pstApiInfo;
} stACE_GetInfo,*pstACE_GetInfo;

typedef struct _stACE_SetDbgLevel
{
    MS_U16 u16DbgSwitch;
    MS_BOOL bReturn;
} stACE_SetDbgLevel,*pstACE_SetDbgLevel;

typedef struct _stACE_GetStatus
{
    XC_ACE_ApiStatus *pDrvStatus;
    MS_BOOL bWindow;
    MS_BOOL bReturn;
} stACE_GetStatus,*pstACE_GetStatus;

typedef struct _stACE_MWESetMirrorMode
{
    E_XC_ACE_MWE_MIRROR_TYPE eMirrorMode;
} stACE_MWESetMirrorMode,*pstACE_MWESetMirrorMode;

typedef struct _stACE_EnableMWE
{
    MS_BOOL bEnable;
} stACE_EnableMWE,*pstACE_EnableMWE;

typedef struct _stACE_3DClonePQMap
{
    XC_ACE_WEAVETYPE enWeaveType;
} stACE_3DClonePQMap,*pstACE_3DClonePQMap;

typedef struct _stACE_MWESetRegTable
{
    XC_ACE_TAB_Info *pMWETable;
    MS_BOOL bReturn;
} stACE_MWESetRegTable,*pstACE_MWESetRegTable;

typedef struct _stACE_SetMWELoadFromPQ
{
    MS_BOOL bEnable;
    MS_BOOL bReturn;
} stACE_SetMWELoadFromPQ,*pstACE_SetMWELoadFromPQ;

typedef struct _stACE_MWESetDispWin
{
    MS_U16 u16MWE_Disp_Hstart;
    MS_U16 u16MWE_Disp_Vstart;
    MS_U16 u16MWE_Disp_Width;
    MS_U16 u16MWE_Disp_Height;
} stACE_MWESetDispWin,*pstACE_MWESetDispWin;

typedef struct _stACE_MWEStatus
{
    MS_BOOL bReturn;
} stACE_MWEStatus,*pstACE_MWEStatus;

typedef struct _stACE_MWEFuncSel
{
    MS_BOOL eWindow;
    E_XC_ACE_MWE_FUNC mwe_func;
} stACE_MWEFuncSel,*pstACE_MWEFuncSel;

typedef struct _stACE_Set_IHC_SRAM
{
    MS_U16 *pBuf;
    MS_U16 u16ByteSize;
    MS_BOOL bReturn;
} stACE_Set_IHC_SRAM,*pstACE_Set_IHC_SRAM;

typedef struct _stACE_Set_ICC_SRAM
{
    MS_U16 *pBuf;
    MS_U16 u16ByteSize;
    MS_BOOL bReturn;
} stACE_Set_ICC_SRAM,*pstACE_Set_ICC_SRAM;

typedef struct _stACE_DNR_Get_PrecisionShift
{
    MS_U16 u16Return;
} stACE_DNR_Get_PrecisionShift,*pstACE_DNR_Get_PrecisionShift;

typedef struct _stACE_DNR_Blending_NRTbl
{
    MS_U8 *pu8NewNR;
    MS_U8 u8Weight;
    MS_U8 u8Step;
    MS_U16 *pu16PreY0;
    MS_U16 *pu16PreY1;
    MS_U8 *pu8NRTBL;
} stACE_DNR_Blending_NRTbl,*pstACE_DNR_Blending_NRTbl;

typedef struct _stACE_DNR_Blending
{
    MS_U8 u8NewItem;
    MS_U16 u16PreItem;
    MS_U8 u8Weight;
    MS_U8 u8Return;
} stACE_DNR_Blending,*pstACE_DNR_Blending;

typedef struct _stACE_DNR_Blending_MISC
{
    MS_U8 u8NewItem;
    MS_U16 u16PreItem;
    MS_U8 u8Weight;
    MS_U8 u8Step;
    MS_U16 u16Return;
} stACE_DNR_Blending_MISC,*pstACE_DNR_Blending_MISC;

typedef struct _stACE_DNR_GetMotion
{
    MS_U8 u8Return;
} stACE_DNR_GetMotion,*pstACE_DNR_GetMotion;

typedef struct _stACE_DNR_GetMotion_Weight
{
    MS_U8 u8CurMotion;
    MS_U8 u8PreMotion;
    MS_U8 u8CurMotionLvl;
    MS_U8 u8PreMotionLvl;
    MS_U8 u8DeFlick_Thre;
    MS_U8 u8DeFilick_Step;
    MS_U8 u8Return;
} stACE_DNR_GetMotion_Weight,*pstACE_DNR_GetMotion_Weight;

typedef struct _stACE_DNR_DNR_GetNoise_Weight
{
    MS_U8 u8CurNoise;
    MS_U8 u8PreNoise;
    MS_U8 u8Range;
    MS_U8 u8DeFlick_Th;
    MS_U8 u8DeFlick_Step;
    MS_U8 u8Return;
} stACE_DNR_GetNoise_Weight,*pstACE_DNR_GetNoise_Weight;

typedef struct _stACE_DNR_GetLuma_Weight
{
    MS_U8 u8CurAvgLuma;
    MS_U8 u8PreAvgLuam;
    MS_U8 u8CurLumaLvl;
    MS_U8 u8PreLumaLvl;
    MS_U8 u8DeFlick_Th;
    MS_U8 u8DeFlick_Step;
    MS_U8 u8Return;
} stACE_DNR_GetLuma_Weight,*pstACE_DNR_GetLuma_Weight;

typedef struct _stACE_DNR_GetParam
{
    MS_BOOL eWindow;
    XC_ACE_DNR_Param eParam;
    MS_U8 u8Return;
} stACE_DNR_GetParam,*pstACE_DNR_GetParam;

typedef struct _stACE_DNR_SetParam
{
    MS_BOOL eWindow;
    XC_ACE_DNR_Param eParam;
    MS_U16 u16val;
} stACE_DNR_SetParam,*pstACE_DNR_SetParam;

typedef struct _stACE_DNR_SetNRTbl
{
    MS_U8 *pu8Tbl;
} stACE_DNR_SetNRTbl,*pstACE_DNR_SetNRTbl;

typedef struct _stACE_ColorCorrectionTable
{
    MS_BOOL bScalerWin;
    MS_S16 *psColorCorrectionTable;
} stACE_ColorCorrectionTable,*pstACE_ColorCorrectionTable;

typedef struct _stACE_SetRBChannelRange
{
    MS_BOOL bScalerWin;
    MS_BOOL bRange;
} stACE_SetRBChannelRange,*pstACE_SetRBChannelRange;

typedef struct _stACE_SetColorMatrixControl
{
    MS_BOOL bScalerWin;
    MS_BOOL bEnable;
} stACE_SetColorMatrixControl,*pstACE_SetColorMatrixControl;

typedef struct _stACE_SetColorMatrix
{
    MS_BOOL eWindow;
    MS_U16* pu16Matrix;
} stACE_SetColorMatrix,*pstACE_SetColorMatrix;

typedef struct _stACE_Set_PowerState
{
    EN_POWER_MODE enPowerState;
    MS_U32 u32Return;
} stACE_Set_PowerState,*pstACE_Set_PowerState;


#ifdef __cplusplus
}
#endif

#undef _API_ACE_PRIV_H_
#endif //_API_ACE_PRIV_H_
