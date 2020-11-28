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

#ifndef _APIXC_DLC_PRIV_H_
#define _APIXC_DLC_PRIV_H_


////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
    MS_U32 Dummy;
}DLC_RESOURCE_PRIVATE;



typedef MS_BOOL                       (*IOCTL_DLC_INIT_EX)                                                                           (void*, XC_DLC_init * ,MS_U32);
typedef void                          (*IOCTL_DLC_SETSETTING_EX)                             (void*, XC_DLC_MFinit_Ex*);
typedef void                          (*IOCTL_DLC_SETCURVE)                                   (void*, MS_U8* ,MS_U8* ,MS_U8* );
typedef void                          (*IOCTL_DLC_SETBLESLOPPOINT)                          (void*, MS_U16*);
typedef MS_BOOL                       (*IOCTL_DLC_EXIT)                                        (void*);
typedef void                          (*IOCTL_DLC_SETONOFF)                                   (void*, MS_BOOL ,MS_BOOL);
typedef MS_BOOL                       (*IOCTL_DLC_SETHANDLERONOFF)                          (void*, MS_BOOL);
typedef MS_BOOL                       (*IOCTL_DLC_SETBLEONOFF)                               (void*, MS_BOOL);
typedef void                          (*IOCTL_DLC_ENABLEMAINSUBCURVESYNCHRONIZATION)    (void*, MS_BOOL);
typedef void                          (*IOCTL_DLC_HANDLER)                                    (void*, MS_BOOL);
typedef MS_BOOL                       (*IOCTL_DLC_GETHISTOGRAMHANDLER)                     (void*, MS_BOOL);
typedef MS_U8                         (*IOCTL_DLC_GETAVERAGEVALUE)                          (void*);
typedef MS_U16                        (*IOCTL_DLC_GETAVERAGEVALUE_EX)                      (void*);
typedef void                          (*IOCTL_DLC_INITCURVE)                                 (void*, MS_U16 ,MS_U16 ,MS_U16 ,MS_U16);
typedef void                          (*IOCTL_DLC_SPEEDUPTRIGGER)                            (void*, MS_U8);
typedef MS_BOOL                       (*IOCTL_DLC_GETLUMACURVESTATUS)                       (void*);
typedef void                          (*IOCTL_DLC_CGC_RESETCGAIN)                            (void*);
typedef void                          (*IOCTL_DLC_CGC_CHECKCGAININPQCOM)                   (void*);
typedef void                          (*IOCTL_DLC_CGC_RESETYGAIN)                            (void*);
typedef void                          (*IOCTL_DLC_CGC_CHECKYGAININPQCOM)                   (void*);
typedef void                          (*IOCTL_DLC_CGC_RESET)                                  (void*);
typedef void                          (*IOCTL_DLC_CGC_INIT)                                   (void*);
typedef void                          (*IOCTL_DLC_CGC_REINIT)                                 (void*);
typedef void                          (*IOCTL_DLC_CGC_HANDLER)                               (void*);
typedef E_XC_DLC_RESULT               (*IOCTL_DLC_GETLIBVER)                                  (void*, const MSIF_Version**);
typedef const XC_DLC_ApiInfo *        (*IOCTL_DLC_GETINFO)                                    (void*);
typedef MS_BOOL                       (*IOCTL_DLC_GETSTATUS_EX)                              (void*, XC_DLC_ApiStatus* ,MS_BOOL);
typedef MS_BOOL                       (*IOCTL_DLC_SETDBGLEVEL)                               (void*, MS_U16);
typedef MS_BOOL                       (*IOCTL_DLC_WRITECURVE)                                (void*, MS_U8*);
typedef MS_BOOL                       (*IOCTL_DLC_WRITECURVE_SUB)                            (void*, MS_U8*);
typedef MS_BOOL                       (*IOCTL_DLC_GETHISTOGRAM)                              (void*, MS_U16* ,E_XC_DLC_HISTOGRAM_TYPE);
typedef void                          (*IOCTL_DLC_DECODEEXTCMD)                              (void*, tDLC_CONTROL_PARAMS*);
typedef void                          (*IOCTL_DLC_SETCAPTURERANGE)                           (void*, XC_DLC_CAPTURE_Range*);
typedef void                          (*IOCTL_DLC_SETSETTING)                                 (void*, XC_DLC_MFinit);
typedef MS_BOOL                       (*IOCTL_DLC_INIT)                                        (void*, XC_DLC_init* ,MS_U32);
typedef MS_BOOL                       (*IOCTL_DLC_GETSTATUS)                                  (void*, XC_DLC_ApiStatus* ,MS_BOOL);
typedef MS_U32                        (*IOCTL_DLC_SET_POWERSTATE)                            (void*, EN_POWER_MODE);
typedef void                          (*IOCTL_DBC_DLC_INIT)                                   (void*, XC_DLC_DBC_MFinit);
typedef void                          (*IOCTL_DBC_INIT)                                        (void*);
typedef void                          (*IOCTL_DBC_SETSTATUS)                                  (void*, MS_BOOL);
typedef MS_BOOL                       (*IOCTL_DBC_GETSTATUS)                                  (void*);
typedef void                          (*IOCTL_DBC_SET_READY)                                  (void*, MS_BOOL);
typedef void                          (*IOCTL_DBC_SET_DEBUGMODE)                             (void*, MS_U8);
typedef MS_U8                         (*IOCTL_DBC_GET_DEBUGMODE)                             (void*);
typedef void                          (*IOCTL_DBC_UPDATEPWM)                                  (void*, MS_U8);
typedef MS_U16                        (*IOCTL_DBC_HANDLER)                                    (void*);
typedef void                          (*IOCTL_DBC_ADJUSTYCGAIN)                              (void*);
typedef void                          (*IOCTL_DBC_YCGAININIT)                                (void*, MS_U8 ,MS_U8 ,MS_U8,MS_U8);
typedef void                          (*IOCTL_DBC_RESET)                                      (void*);
typedef void                          (*IOCTL_DBC_DECODEEXTCMD)                              (void*, tDBC_CONTROL_PARAMS*);
typedef struct
{
    IOCTL_DLC_INIT_EX                                              fpDLC_Init_Ex;
    IOCTL_DLC_SETSETTING_EX                                        fpDLC_SetSetting_Ex;
    IOCTL_DLC_SETCURVE                                             fpDLC_SetCurve;
    IOCTL_DLC_SETBLESLOPPOINT                                      fpDLC_SetBleSlopPoint;
    IOCTL_DLC_EXIT                                                 fpDLC_Exit;
    IOCTL_DLC_SETONOFF                                             fpDLC_SetOnOff;
    IOCTL_DLC_SETHANDLERONOFF                                      fpDLC_SetDlcHandlerOnOff;
    IOCTL_DLC_SETBLEONOFF                                          fpDLC_SetBleOnOff;
    IOCTL_DLC_ENABLEMAINSUBCURVESYNCHRONIZATION                    fpDLC_EnableMainSubCurveSynchronization;
    IOCTL_DLC_HANDLER                                              fpDLC_Handler;
    IOCTL_DLC_GETHISTOGRAMHANDLER                                  fpDLC_GetHistogramHandler;
    IOCTL_DLC_GETAVERAGEVALUE                                      fpDLC_GetAverageValue;
    IOCTL_DLC_GETAVERAGEVALUE_EX                                   fpDLC_GetAverageValue_Ex;
    IOCTL_DLC_INITCURVE                                            fpDLC_InitCurve; 
    IOCTL_DLC_SPEEDUPTRIGGER                                       fpDLC_SpeedupTrigger;
    IOCTL_DLC_GETLUMACURVESTATUS                                   fpDLC_GetLumaCurveStatus;   
    IOCTL_DLC_CGC_RESETCGAIN                                       fpDLC_CGC_ResetCGain;    
    IOCTL_DLC_CGC_CHECKCGAININPQCOM                                fpDLC_CGC_CheckCGainInPQCom;
    IOCTL_DLC_CGC_RESETYGAIN                                       fpDLC_CGC_ResetYGain;
    IOCTL_DLC_CGC_CHECKYGAININPQCOM                                fpDLC_CGC_CheckYGainInPQCom;
    IOCTL_DLC_CGC_RESET                                            fpDLC_CGC_Reset;
    IOCTL_DLC_CGC_INIT                                             fpDLC_CGC_Init;
    IOCTL_DLC_CGC_REINIT                                           fpDLC_CGC_ReInit;
    IOCTL_DLC_CGC_HANDLER                                          fpDLC_CGC_Handler;
    IOCTL_DLC_GETLIBVER                                            fpDLC_GetLibVer;
    IOCTL_DLC_GETINFO                                              fpDLC_GetInfo;
    IOCTL_DLC_GETSTATUS_EX                                         fpDLC_GetStatus_Ex;
    IOCTL_DLC_SETDBGLEVEL                                          fpDLC_SetDbgLevel;
    IOCTL_DLC_WRITECURVE                                           fpDLC_WriteCurve;
    IOCTL_DLC_WRITECURVE_SUB                                       fpDLC_WriteCurve_Sub;
    IOCTL_DLC_GETHISTOGRAM                                         fpDLC_GetHistogram;
    IOCTL_DLC_DECODEEXTCMD                                         fpDLC_DecodeExtCmd;
    IOCTL_DLC_SETCAPTURERANGE                                      fpDLC_SetCaptureRange;
    IOCTL_DLC_SETSETTING                                           fpDLC_SetSetting;
    IOCTL_DLC_INIT                                                 fpDLC_Init;
    IOCTL_DLC_GETSTATUS                                            fpDLC_GetStatus;
    IOCTL_DLC_SET_POWERSTATE                                       fpDLC_SetPowerState;
    IOCTL_DBC_DLC_INIT                                             fpDBC_DLC_Init;
    IOCTL_DBC_INIT                                                 fpDBC_Init;
    IOCTL_DBC_SETSTATUS                                            fpDBC_Setstatus;
    IOCTL_DBC_GETSTATUS                                            fpDBC_Getstatus;
    IOCTL_DBC_SET_READY                                            fpDBC_SetReady;
    IOCTL_DBC_SET_DEBUGMODE                                        fpDBC_SetDebugMode;
    IOCTL_DBC_GET_DEBUGMODE                                        fpDBC_GetDebugMode;
    IOCTL_DBC_UPDATEPWM                                            fpDBC_UpdatePWM;
    IOCTL_DBC_HANDLER                                              fpDBC_Handler;
    IOCTL_DBC_ADJUSTYCGAIN                                         fpDBC_AdjustYCGain;
    IOCTL_DBC_YCGAININIT                                           fpDBC_YCGainInit;
    IOCTL_DBC_RESET                                                fpDBC_Reset;
    IOCTL_DBC_DECODEEXTCMD                                         fpDBC_DecodeExtCmd;
}DLC_INSTANCE_PRIVATE;


MS_BOOL MApi_XC_DLC_Init_Ex_U2(void *pInstance, XC_DLC_init *pstXC_DLC_InitData, MS_U32 u32InitDataLen);
void MApi_XC_DLC_SetSetting_Ex_U2(void *pInstance, XC_DLC_MFinit_Ex *DLC_MFinit_Ex );
void MApi_XC_DLC_SetCurve_U2(void *pInstance, MS_U8 *pNormal, MS_U8 *pLight, MS_U8 *pDark);
void MApi_XC_DLC_SetBleSlopPoint_U2(void *pInstance, MS_U16 *pBLESlopPoint);
MS_BOOL MApi_XC_DLC_Exit_U2(void *pInstance );
void    MApi_XC_DLC_SetOnOff_U2(void *pInstance, MS_BOOL bSwitch, MS_BOOL bWindow);
MS_BOOL MApi_XC_DLC_SetDlcHandlerOnOff_U2(void *pInstance, MS_BOOL bDlcEnable );
MS_BOOL MApi_XC_DLC_SetBleOnOff_U2( void *pInstance, MS_BOOL bSwitch );
void MApi_XC_DLC_EnableMainSubCurveSynchronization_U2( void *pInstance, MS_BOOL bEnable);
void    MApi_XC_DLC_Handler_U2(void *pInstance, MS_BOOL bWindow);
MS_BOOL MApi_XC_DLC_GetHistogramHandler_U2(void *pInstance, MS_BOOL bWindow);
MS_U8   MApi_XC_DLC_GetAverageValue_U2(void *pInstance);
MS_U16 MApi_XC_DLC_GetAverageValue_Ex_U2(void *pInstance);
void    MApi_XC_DLC_InitCurve_U2(void *pInstance, MS_U16 u16HStart, MS_U16 u16HEnd, MS_U16 u16VStart, MS_U16 u16VEnd);
void    MApi_XC_DLC_SpeedupTrigger_U2( void *pInstance, MS_U8 u8Loop);
MS_BOOL MApi_XC_DLC_GetLumaCurveStatus_U2( void *pInstance );
void    MApi_XC_DLC_CGC_ResetCGain_U2(void *pIstance);
void    MApi_XC_DLC_CGC_CheckCGainInPQCom_U2(void *pInstance);
void    MApi_XC_DLC_CGC_ResetYGain_U2(void *pInstance);
void    MApi_XC_DLC_CGC_CheckYGainInPQCom_U2(void *pInstance);
void    MApi_XC_DLC_CGC_Reset_U2(void *pInstance);
void    MApi_XC_DLC_CGC_Init_U2(void *pInstance);
void    MApi_XC_DLC_CGC_ReInit_U2(void *pInstance);
void    MApi_XC_DLC_CGC_Handler_U2(void *pInstance);
E_XC_DLC_RESULT MApi_XC_DLC_GetLibVer_U2(void *pInstance, const MSIF_Version **ppVersion) ;
const XC_DLC_ApiInfo * MApi_XC_DLC_GetInfo_U2(void *pInstance);                                      ///< Get info from driver (without Mutex protect)
MS_BOOL MApi_XC_DLC_GetStatus_Ex_U2(void *pInstance, XC_DLC_ApiStatus *pDrvStatus, MS_BOOL bWindow);       ///< Get panel current status
MS_BOOL MApi_XC_DLC_SetDbgLevel_U2(void *pInstance, MS_U16 u16DbgSwitch);                                  ///< Set debug level (without Mutex protect), refer to XC_DBGLEVEL_OFF
MS_BOOL MApi_XC_DLC_WriteCurve_U2(void *pInstance, MS_U8 *pu8Table);
MS_BOOL MApi_XC_DLC_WriteCurve_Sub_U2(void *pInstance, MS_U8 *pu8Table);
MS_BOOL MApi_XC_DLC_GetHistogram_U2(void *pInstance, MS_U16 *pu16Histogram, E_XC_DLC_HISTOGRAM_TYPE enHistogramType);
void MApi_XC_DLC_DecodeExtCmd_U2(void *pInstance, tDLC_CONTROL_PARAMS *params);
void MApi_XC_DLC_SetCaptureRange_U2(void *pInstance, XC_DLC_CAPTURE_Range *pu16_Range);
void MApi_XC_DLC_SetSetting_U2(void *pInstance, XC_DLC_MFinit DLC_MFinit ); // Setting DLC
MS_BOOL MApi_XC_DLC_Init_U2(void *pInstance, XC_DLC_init *pstXC_DLC_InitData, MS_U32 u32InitDataLen); // DLC initiation
MS_BOOL MApi_XC_DLC_GetStatus_U2(void *pInstance, XC_DLC_ApiStatus *pDrvStatus, MS_BOOL bWindow);  // Get DLC current status
MS_U32 MApi_XC_DLC_SetPowerState_U2(void* pInstance, EN_POWER_MODE enPowerState);
void    MApi_XC_DLC_DBC_Init_U2(void *pInstance, XC_DLC_DBC_MFinit DLC_DBC_MFinit);
void MApi_XC_DBC_Init_U2(void *pInstance );
void    MApi_XC_DLC_DBC_Setstatus_U2(void *pInstance, MS_BOOL bDBCEnable);
MS_BOOL MApi_XC_DLC_DBC_Getstatus_U2(void *pInstance);
void MApi_XC_DLC_DBC_SetReady_U2(void *pInstance, MS_BOOL bDBCReady);
void MApi_XC_DLC_DBC_SetDebugMode_U2(void *pInstance, MS_U8 ucDBC_DebugMode);
MS_U8 MApi_XC_DLC_DBC_GetDebugMode_U2(void *pInstance );
void    MApi_XC_DLC_DBC_UpdatePWM_U2(void *pInstance, MS_U8 u8PWMvalue);
MS_U16  MApi_XC_DLC_DBC_Handler_U2(void *pInstance );
void    MApi_XC_DLC_DBC_AdjustYCGain_U2(void *pInstance);
void    MApi_XC_DLC_DBC_YCGainInit_U2(void *pInstance, MS_U8 u8YGain_M, MS_U8 u8YGain_L, MS_U8 u8CGain_M, MS_U8 u8CGain_L);
void    MApi_XC_DLC_DBC_Reset_U2(void *pInstance);
void MApi_XC_DBC_DecodeExtCmd_U2(void *pInstance, tDBC_CONTROL_PARAMS *params );


void DLCRegisterToUtopia(FUtopiaOpen ModuleType);
MS_U32 DLCOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
MS_U32 DLCClose(void* pInstance);
MS_U32 DLCIoctl(void* pInstance, MS_U32 u32Cmd, void* pArgs);
#ifdef __cplusplus
}
#endif

#undef _APIXC_DLC_PRIV_H_
#endif // _APIXC_DLC_PRIV_H_