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
//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvAVD_priv.h
/// @brief  AVD Driver private Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_AVD_PRIV_H_
#define _DRV_AVD_PRIV_H_

#include "drvAVD_v2.h"

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

extern AVD_Result Drv_AVD_Init(VD_INITDATA *pVD_InitData, MS_U32 u32InitDataLen, AVD_RESOURCE_PRIVATE *pResource);

extern void Drv_AVD_Exit(AVD_RESOURCE_PRIVATE *pResource);

extern MS_BOOL Drv_AVD_ResetMCU(AVD_RESOURCE_PRIVATE *pResource);

extern void Drv_AVD_FreezeMCU(MS_BOOL bEnable, AVD_RESOURCE_PRIVATE *pResource);

extern MS_U16 Drv_AVD_Scan_HsyncCheck(MS_U8 u8HtotalTolerance, AVD_RESOURCE_PRIVATE *pResource);

extern void Drv_AVD_StartAutoStandardDetection(AVD_RESOURCE_PRIVATE *pResource);

extern MS_BOOL Drv_AVD_ForceVideoStandard(AVD_VideoStandardType eVideoStandardType, AVD_RESOURCE_PRIVATE *pResource);

extern void Drv_AVD_3DCombSpeedup(AVD_RESOURCE_PRIVATE *pResource);

extern void Drv_AVD_LoadDSP(MS_U8 *pu8VD_DSP, MS_U32 len, AVD_RESOURCE_PRIVATE *pResource);

extern MS_U8 Drv_AVD_MBX_ReadByteByVDMbox(MS_U8 u8Addr, AVD_RESOURCE_PRIVATE *pResource);

extern void Drv_AVD_BackPorchWindowPositon(MS_BOOL bEnable , MS_U8 u8Value);


extern void Drv_AVD_SetFlag(MS_U32  u32VDPatchFlag, AVD_RESOURCE_PRIVATE *pResource);

extern void Drv_AVD_SetRegValue(MS_U16 u16Addr,MS_U8 u8Value);

extern void Drv_AVD_SetRegFromDSP(AVD_RESOURCE_PRIVATE *pResource);

extern MS_BOOL Drv_AVD_SetInput(AVD_InputSourceType eSource, MS_U8 u8ScartFB, AVD_RESOURCE_PRIVATE *pResource);

extern MS_BOOL Drv_AVD_SetVideoStandard(AVD_VideoStandardType eStandard, MS_BOOL bIsInAutoTuning, AVD_RESOURCE_PRIVATE *pResource);

extern void Drv_AVD_SetChannelChange(AVD_RESOURCE_PRIVATE *pResource);

extern void Drv_AVD_SetHsyncDetectionForTuning(MS_BOOL bEnable, AVD_RESOURCE_PRIVATE *pResource);

extern void Drv_AVD_Set3dComb(MS_BOOL bEnable, AVD_RESOURCE_PRIVATE *pResource);

extern void Drv_AVD_SetShiftClk(MS_BOOL bEnable,AVD_ATV_CLK_TYPE eShiftMode, AVD_RESOURCE_PRIVATE *pResource);

extern void Drv_AVD_SetFreerunPLL(AVD_VideoFreq eVideoFreq, AVD_RESOURCE_PRIVATE *pResource);

extern void Drv_AVD_SetFreerunFreq(AVD_FreeRunFreq eFreerunfreq, AVD_RESOURCE_PRIVATE *pResource);

extern void Drv_AVD_SetFactoryPara(AVD_Factory_Para FactoryPara,MS_U8 u8Value);

extern MS_BOOL Drv_AVD_SetDbgLevel(AVD_DbgLv u8DbgLevel, AVD_RESOURCE_PRIVATE *pResource);

extern void Drv_AVD_SetPQFineTune(AVD_RESOURCE_PRIVATE *pResource);

extern void Drv_AVD_Set3dCombSpeed(MS_U8 u8COMB57, MS_U8 u8COMB58, AVD_RESOURCE_PRIVATE *pResource);

extern void Drv_AVD_SetStillImageParam(AVD_Still_Image_Param param, AVD_RESOURCE_PRIVATE *pResource);

extern void Drv_AVD_Set2D3DPatchOnOff(MS_BOOL bEnable);

extern MS_U8 Drv_AVD_SetAutoFineGainToFixed(void);


extern MS_U8 Drv_AVD_GetRegValue(MS_U16 u16Addr);

extern MS_U16 Drv_AVD_GetStatus(void);

extern MS_U8 Drv_AVD_GetNoiseMag(void);

extern MS_U16 Drv_AVD_GetVTotal(void);

extern AVD_VideoStandardType Drv_AVD_GetStandardDetection(MS_U16 *u16LatchStatus, AVD_RESOURCE_PRIVATE *pResource);

extern void Drv_AVD_GetCaptureWindow(void *stCapWin, AVD_VideoStandardType eVideoStandardType , AVD_RESOURCE_PRIVATE *pResource);

extern AVD_VideoFreq Drv_AVD_GetVerticalFreq(void);

extern MS_U8 Drv_AVD_GetHsyncEdge(void);

extern MS_U8 Drv_AVD_GetDSPFineGain(AVD_RESOURCE_PRIVATE *pResource);

extern MS_U16 Drv_AVD_GetDSPVersion(void);

extern AVD_Result Drv_AVD_GetLibVer(const MSIF_Version **ppVersion);

extern void  Drv_AVD_GetInfo(AVD_Info* pAVD_Info, AVD_RESOURCE_PRIVATE *pResource);

extern MS_BOOL Drv_AVD_IsSyncLocked(void);

extern MS_BOOL Drv_AVD_IsSignalInterlaced(void);

extern MS_BOOL Drv_AVD_IsColorOn(void);

extern MS_U32 Drv_AVD_SetPowerState(EN_POWER_MODE u16PowerState, AVD_RESOURCE_PRIVATE *pResource);

extern MS_BOOL Drv_AVD_GetMacroVisionDetect(void);

extern MS_BOOL Drv_AVD_GetCGMSDetect(void);

//-------------------------------- functions ------------------------------------------------------------

typedef AVD_Result (*IOCTL_AVD_Init)(VD_INITDATA *, MS_U32, AVD_RESOURCE_PRIVATE *);
typedef void (*IOCTL_AVD_Exit)(AVD_RESOURCE_PRIVATE *);
typedef MS_BOOL (*IOCTL_AVD_ResetMCU)(AVD_RESOURCE_PRIVATE *);
typedef void (*IOCTL_AVD_FreezeMCU)(MS_BOOL, AVD_RESOURCE_PRIVATE *);
typedef MS_U16 (*IOCTL_AVD_Scan_HsyncCheck)(MS_U8, AVD_RESOURCE_PRIVATE *);
typedef void (*IOCTL_AVD_StartAutoStandardDetection)(AVD_RESOURCE_PRIVATE *);
typedef MS_BOOL (*IOCTL_AVD_ForceVideoStandard)(AVD_VideoStandardType, AVD_RESOURCE_PRIVATE *);
typedef void (*IOCTL_AVD_3DCombSpeedup)(AVD_RESOURCE_PRIVATE *);
typedef void (*IOCTL_AVD_LoadDSP)(MS_U8 *, MS_U32, AVD_RESOURCE_PRIVATE *);
typedef void (*IOCTL_AVD_BackPorchWindowPositon)(MS_BOOL , MS_U8);
typedef MS_U8 (*IOCTL_AVD_MBX_ReadByteByVDMbox)(MS_U8, AVD_RESOURCE_PRIVATE *);

typedef void (*IOCTL_AVD_SetFlag)(MS_U32, AVD_RESOURCE_PRIVATE *);
typedef void (*IOCTL_AVD_SetRegValue)(MS_U16 ,MS_U8);
typedef void (*IOCTL_AVD_SetRegFromDSP)(AVD_RESOURCE_PRIVATE *);
typedef MS_BOOL (*IOCTL_AVD_SetInput)(AVD_InputSourceType , MS_U8, AVD_RESOURCE_PRIVATE *);
typedef MS_BOOL (*IOCTL_AVD_SetVideoStandard)(AVD_VideoStandardType , MS_BOOL, AVD_RESOURCE_PRIVATE *);
typedef void (*IOCTL_AVD_SetChannelChange)(AVD_RESOURCE_PRIVATE *);
typedef void (*IOCTL_AVD_SetHsyncDetectionForTuning)(MS_BOOL, AVD_RESOURCE_PRIVATE *);
typedef void (*IOCTL_AVD_Set3dComb)(MS_BOOL , AVD_RESOURCE_PRIVATE *);
typedef void (*IOCTL_AVD_SetShiftClk)(MS_BOOL ,AVD_ATV_CLK_TYPE, AVD_RESOURCE_PRIVATE *);
typedef void (*IOCTL_AVD_SetFreerunPLL)(AVD_VideoFreq, AVD_RESOURCE_PRIVATE *);
typedef void (*IOCTL_AVD_SetFreerunFreq)(AVD_FreeRunFreq, AVD_RESOURCE_PRIVATE *);
typedef void (*IOCTL_AVD_SetFactoryPara)(AVD_Factory_Para ,MS_U8 );
typedef MS_BOOL (*IOCTL_AVD_SetDbgLevel)(AVD_DbgLv, AVD_RESOURCE_PRIVATE *);
typedef void (*IOCTL_AVD_SetPQFineTune)(AVD_RESOURCE_PRIVATE *);
typedef void (*IOCTL_AVD_Set3dCombSpeed)(MS_U8 , MS_U8, AVD_RESOURCE_PRIVATE *);
typedef void (*IOCTL_AVD_SetStillImageParam)(AVD_Still_Image_Param, AVD_RESOURCE_PRIVATE *);
typedef void (*IOCTL_AVD_Set2D3DPatchOnOff)(MS_BOOL);
typedef MS_U8 (*IOCTL_AVD_SetAutoFineGainToFixed)(void);

typedef MS_U8 (*IOCTL_AVD_GetRegValue)(MS_U16);
typedef MS_U16 (*IOCTL_AVD_GetStatus)(void);
typedef MS_U8 (*IOCTL_AVD_GetNoiseMag)(void);
typedef MS_U16 (*IOCTL_AVD_GetVTotal)(void);
typedef AVD_VideoStandardType (*IOCTL_AVD_GetStandardDetection)(MS_U16 *, AVD_RESOURCE_PRIVATE *);
typedef void (*IOCTL_AVD_GetCaptureWindow)(void *, AVD_VideoStandardType, AVD_RESOURCE_PRIVATE *);
typedef AVD_VideoFreq (*IOCTL_AVD_GetVerticalFreq)(void);
typedef MS_U8 (*IOCTL_AVD_GetHsyncEdge)(void);
typedef MS_U8 (*IOCTL_AVD_GetDSPFineGain)(AVD_RESOURCE_PRIVATE *);
typedef MS_U16 (*IOCTL_AVD_GetDSPVersion)(void);
typedef AVD_Result (*IOCTL_AVD_GetLibVer)(const MSIF_Version **);
typedef void (*IOCTL_AVD_GetInfo)(AVD_Info*, AVD_RESOURCE_PRIVATE *);
typedef MS_BOOL (*IOCTL_AVD_IsSyncLocked)(void);
typedef MS_BOOL (*IOCTL_AVD_IsSignalInterlaced)(void);
typedef MS_BOOL (*IOCTL_AVD_IsColorOn)(void);
typedef MS_U32 (*IOCTL_AVD_SetPowerState)(EN_POWER_MODE , AVD_RESOURCE_PRIVATE *);
typedef MS_BOOL (*IOCTL_AVD_GetMacroVisionDetect)(void);
typedef MS_BOOL (*IOCTL_AVD_GetCGMSDetect)(void);

typedef struct _AVD_INSTANT_PRIVATE
{
    IOCTL_AVD_Init                                      fpAVDInit;
    IOCTL_AVD_Exit                                     fpAVDExit;
    IOCTL_AVD_ResetMCU                            fpAVDResetMCU;
    IOCTL_AVD_FreezeMCU                           fpAVDFreezeMCU;
    IOCTL_AVD_Scan_HsyncCheck                 fpAVDScanHsyncCheck;
    IOCTL_AVD_StartAutoStandardDetection    fpAVDStartAutoStandardDetection;
    IOCTL_AVD_ForceVideoStandard               fpAVDForceVideoStandard;
    IOCTL_AVD_3DCombSpeedup                   fpAVD3DCombSpeedup;
    IOCTL_AVD_LoadDSP                               fpAVDLoadDSP;
    IOCTL_AVD_BackPorchWindowPositon       fpAVDBackPorchWindowPositon;
    IOCTL_AVD_MBX_ReadByteByVDMbox      fpAVDMBX_ReadByteByVDMbox;

    IOCTL_AVD_SetFlag                                 fpAVDSetFlag;
    IOCTL_AVD_SetRegValue                         fpAVDSetRegValue;
    IOCTL_AVD_SetRegFromDSP                    fpAVDSetRegFromDSP;
    IOCTL_AVD_SetInput                               fpAVDSetInput;
    IOCTL_AVD_SetVideoStandard                  fpAVDSetVideoStandard;
    IOCTL_AVD_SetChannelChange                fpAVDSetChannelChange;
    IOCTL_AVD_SetHsyncDetectionForTuning   fpAVDSetHsyncDetectionForTuning;
    IOCTL_AVD_Set3dComb                           fpAVDSet3dComb;
    IOCTL_AVD_SetShiftClk                            fpAVDSetShiftClk;
    IOCTL_AVD_SetFreerunPLL                        fpAVDSetFreerunPLL;
    IOCTL_AVD_SetFreerunFreq                      fpAVDSetFreerunFreq;
    IOCTL_AVD_SetFactoryPara                      fpAVDSetFactoryPara;
    IOCTL_AVD_SetDbgLevel                          fpAVDSetDbgLevel;
    IOCTL_AVD_SetPQFineTune                       fpAVDSetPQFineTune;
    IOCTL_AVD_Set3dCombSpeed                   fpAVDSet3dCombSpeed;
    IOCTL_AVD_SetStillImageParam                fpAVDSetStillImageParam;
    IOCTL_AVD_Set2D3DPatchOnOff                fpAVDSet2D3DPatchOnOff;
    IOCTL_AVD_SetAutoFineGainToFixed          fpAVDSetAutoFineGainToFixed;

    IOCTL_AVD_GetRegValue                          fpAVDGetRegValue;
    IOCTL_AVD_GetStatus                              fpAVDGetStatus;
    IOCTL_AVD_GetNoiseMag                          fpAVDGetNoiseMag;
    IOCTL_AVD_GetVTotal                              fpAVDGetVTotal;
    IOCTL_AVD_GetStandardDetection             fpAVDGetStandardDetection;
    IOCTL_AVD_GetCaptureWindow                 fpAVDGetCaptureWindow;
    IOCTL_AVD_GetVerticalFreq                      fpAVDGetVerticalFreq;
    IOCTL_AVD_GetHsyncEdge                        fpAVDGetHsyncEdge;
    IOCTL_AVD_GetDSPFineGain                     fpAVDGetDSPFineGain;
    IOCTL_AVD_GetDSPVersion                      fpAVDGetDSPVersion;
    IOCTL_AVD_GetLibVer                              fpAVDGetLibVer;
    IOCTL_AVD_GetInfo                                 fpAVDGetInfo;
    IOCTL_AVD_IsSyncLocked                       fpAVDIsSyncLocked;
    IOCTL_AVD_IsSignalInterlaced                 fpAVDIsSignalInterlaced;
    IOCTL_AVD_IsColorOn                             fpAVDIsColorOn;
    IOCTL_AVD_SetPowerState                       fpAVDSetPowerState;
    IOCTL_AVD_GetMacroVisionDetect         fpAVDGetMacroVisionDetect;
    IOCTL_AVD_GetCGMSDetect                  fpAVDGetCGMSDetect;

}AVD_INSTANT_PRIVATE;


void AVDRegisterToUtopia(void);
MS_U32 AVDOpen(void** pInstantTmp, MS_U32 u32ModuleVersion, void* pAttribute);
MS_U32 AVDClose(void* pInstantTmp);
MS_U32 AVDIoctl(void* pInstantTmp, MS_U32 u32Cmd, void* pArgs);

#endif // _DRV_AVD_PRIV_H_
