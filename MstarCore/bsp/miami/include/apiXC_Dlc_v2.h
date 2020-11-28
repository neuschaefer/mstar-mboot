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

#ifndef _DLC_V2_H_
#define _DLC_V2_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"
//******** ENUM DEFINITIONS ********//
enum
{
    E_DLC_POOL_ID_INTERNAL = 0, // just for test, please refine.
} E_DLC_POOL_ID;


typedef enum
{
    E_DLC_CMD_INIT_EX,
    E_DLC_CMD_SET_SETTING_EX,
    E_DLC_CMD_SET_CURVE,
    E_DLC_CMD_SET_BLE_SLOP_POINT,
    E_DLC_CMD_EXIT,
    E_DLC_CMD_SET_ON_OFF,
    E_DLC_CMD_SET_HANDLER_ON_OFF,
    E_DLC_CMD_SET_BLE_ON_OFF,
    E_DLC_CMD_ENABLE_MAIN_SUB_CURVE_SYNCHRONIZATION,
    E_DLC_CMD_HANDLER,
    E_DLC_CMD_GET_HISTOGRAM_HANDLER,
    E_DLC_CMD_GET_AVERAGE_VALUE,
    E_DLC_CMD_GET_AVERAGE_VALUE_EX,
    E_DLC_CMD_INIT_CURVE,
    E_DLC_CMD_SPEEDUP_TRIGGER,
    E_DLC_CMD_GET_LUMA_CURVE_STATUS,
    E_DLC_CMD_CGC_RESET_C_GAIN,
    E_DLC_CMD_CGC_CHECK_C_GAIN_IN_PQ_COM,
    E_DLC_CMD_CGC_RESET_Y_GAIN,
    E_DLC_CMD_CGC_CHECK_Y_GAIN_IN_PQ_COM,
    E_DLC_CMD_CGC_RESET,
    E_DLC_CMD_CGC_INIT,
    E_DLC_CMD_CGC_REINIT,
    E_DLC_CMD_CGC_HANDLER,
    E_DLC_CMD_GET_LIB_VER,
    E_DLC_CMD_GET_INFO,
    E_DLC_CMD_GET_STATUS_EX,
    E_DLC_CMD_SET_DBG_LEVEL,
    E_DLC_CMD_WRITE_CURVE,
    E_DLC_CMD_WRITE_CURVE_SUB,
    E_DLC_CMD_GET_HISTOGRAM,
    E_DLC_CMD_DECODE_EXT_CMD,
    E_DLC_CMD_SET_CAPTURE_RANGE,
    E_DLC_CMD_SET_SETTING,
    E_DLC_CMD_INIT,
    E_DLC_CMD_GET_STATUS,
    E_DLC_CMD_SET_POWERSTATE,
    E_DBC_CMD_DLC_INIT,
    E_DBC_CMD_INIT,
    E_DBC_CMD_SET_STATUS,
    E_DBC_CMD_GET_STATUS,
    E_DBC_CMD_SET_READY,
    E_DBC_CMD_SET_DEBUG_MODE,
    E_DBC_CMD_GET_DEBUG_MODE,
    E_DBC_CMD_UPDATE_PWM,
    E_DBC_CMD_HANDLER,
    E_DBC_CMD_ADJUST_YC_GAIN,
    E_DBC_CMD_YC_GAIN_INIT,
    E_DBC_CMD_RESET,
    E_DBC_CMD_DECODE_EXT_CMD,
    E_DBC_CMD_NUM,
    E_DLC_CMD_MAX = E_DBC_CMD_NUM,
} E_DLC_IOCTL_CMDS;


typedef struct _stDLC_Init_Ex
{
    XC_DLC_init *pstXC_DLC_InitData;
    MS_U32 u32InitDataLen;
    MS_BOOL bReturn;
} stDLC_Init_Ex, *pstDLC_Init_Ex;


typedef struct _stDLC_SetSetting_Ex
{
    XC_DLC_MFinit_Ex *DLC_MFinit_Ex;
} stDLC_SetSetting_Ex, *pstDLC_SetSetting_Ex;


typedef struct _stDLC_SetCurve
{
    MS_U8 *pNormal;
    MS_U8 *pLight;
    MS_U8 *pDark;
} stDLC_SetCurve, *pstDLC_SetCurve;


typedef struct _stDLC_SetBleSlopPoint
{
    MS_U16 *pBLESlopPoint;
} stDLC_SetBleSlopPoint, *pstDLC_SetBleSlopPoint;


typedef struct _stDLC_Exit
{
    MS_BOOL bReturn;
} stDLC_Exit, *pstDLC_Exit;


typedef struct _stDLC_SetOnOff
{
    MS_BOOL bSwitch;
    MS_BOOL bWindow;
} stDLC_SetOnOff, *pstDLC_SetOnOff;


typedef struct _stDLC_SetDlcHandlerOnOff
{
    MS_BOOL bDlcEnable;
    MS_BOOL bReturn;
} stDLC_SetDlcHandlerOnOff, *pstDLC_SetDlcHandlerOnOff;


typedef struct _stDLC_SetBleOnOff
{
    MS_BOOL bSwitch;
    MS_BOOL bReturn;
} stDLC_SetBleOnOff, *pstDLC_SetBleOnOff;


typedef struct _stDLC_EnableMainSubCurveSynchronization
{
    MS_BOOL bEnable;
} stDLC_EnableMainSubCurveSynchronization, *pstDLC_EnableMainSubCurveSynchronization;


typedef struct _stDLC_Handler
{
    MS_BOOL bWindow;
} stDLC_Handler, *pstDLC_Handler;


typedef struct _stDLC_GetHistogramHandler
{
    MS_BOOL bWindow;
    MS_BOOL bReturn;
} stDLC_GetHistogramHandler, *pstDLC_GetHistogramHandler;


typedef struct _stDLC_GetAverageValue
{
    MS_U8 u8Return;
} stDLC_GetAverageValue, *pstDLC_GetAverageValue;


typedef struct _stDLC_GetAverageValue_Ex
{
    MS_U16 u16Return;
} stDLC_GetAverageValue_Ex, *pstDLC_GetAverageValue_Ex;


typedef struct _stDLC_InitCurve
{
    MS_U16 u16HStart;
    MS_U16 u16HEnd;
    MS_U16 u16VStart;
    MS_U16 u16VEnd;
} stDLC_InitCurve, *pstDLC_InitCurve;


typedef struct _stDLC_SpeedupTrigger
{
    MS_U8 u8Loop;
} stDLC_SpeedupTrigger, *pstDLC_SpeedupTrigger;


typedef struct _stDLC_GetLumaCurveStatus
{
    MS_BOOL bReturn;
} stDLC_GetLumaCurveStatus, *pstDLC_GetLumaCurveStatus;


typedef struct _stDLC_CGC_ResetCGain
{

} stDLC_CGC_ResetCGain, *pstDLC_CGC_ResetCGain;


typedef struct _stDLC_CGC_CheckCGainInPQCom
{

} stDLC_CGC_CheckCGainInPQCom, *pstDLC_CGC_CheckCGainInPQCom;


typedef struct _stDLC_CGC_ResetYGain
{

} stDLC_CGC_ResetYGain, *pstDLC_CGC_ResetYGain;


typedef struct _stDLC_CGC_CheckYGainInPQCom
{

} stDLC_CGC_CheckYGainInPQCom, *pstDLC_CGC_CheckYGainInPQCom;


typedef struct _stDLC_CGC_Reset
{

} stDLC_CGC_Reset, *pstDLC_CGC_Reset;


typedef struct _stDLC_CGC_Init
{

} stDLC_CGC_Init, *pstDLC_CGC_Init;


typedef struct _stDLC_CGC_ReInit
{

} stDLC_CGC_ReInit, *pstDLC_CGC_ReInit;


typedef struct _stDLC_CGC_Handler
{

} stDLC_CGC_Handler, *pstDLC_CGC_Handler;


typedef struct _stDLC_GetLibVer
{
    const MSIF_Version **ppVersion;
    E_XC_DLC_RESULT eResult;
} stDLC_GetLibVer, *pstDLC_GetLibVer;


typedef struct _stDLC_GetInfo
{
    const XC_DLC_ApiInfo * eResult;
} stDLC_GetInfo, *pstDLC_GetInfo;


typedef struct _stDLC_GetStatus_Ex
{
    XC_DLC_ApiStatus *pDrvStatus;
    MS_BOOL bWindow;
    MS_BOOL bReturn;
} stDLC_GetStatus_Ex, *pstDLC_GetStatus_Ex;


typedef struct _stDLC_SetDbgLevel
{
    MS_U16 u16DbgSwitch;
    MS_BOOL bReturn;
} stDLC_SetDbgLevel, *pstDLC_SetDbgLevel;


typedef struct _stDLC_WriteCurve
{
    MS_U8 *pu8Table;
    MS_BOOL bReturn;
} stDLC_WriteCurve, *pstDLC_WriteCurve;


typedef struct _stDLC_WriteCurve_Sub
{
    MS_U8 *pu8Table;
    MS_BOOL bReturn;
} stDLC_WriteCurve_Sub, *pstDLC_WriteCurve_Sub;


typedef struct _stDLC_GetHistogram
{
    MS_U16 *pu16Histogram;
    E_XC_DLC_HISTOGRAM_TYPE enHistogramType;
    MS_BOOL bReturn;
} stDLC_GetHistogram, *pstDLC_GetHistogram;


typedef struct _stDLC_DecodeExtCmd
{
    tDLC_CONTROL_PARAMS *params;
} stDLC_DecodeExtCmd, *pstDLC_DecodeExtCmd;


typedef struct _stDLC_SetCaptureRange
{
    XC_DLC_CAPTURE_Range *pu16_Range;
} stDLC_SetCaptureRange, *pstDLC_SetCaptureRange;


typedef struct _stDLC_SetSetting
{
    XC_DLC_MFinit DLC_MFinit;
} stDLC_SetSetting, *pstDLC_SetSetting;


typedef struct _stDLC_Init
{
    XC_DLC_init *pstXC_DLC_InitData;
    MS_U32 u32InitDataLen;
    MS_BOOL bReturn;
} stDLC_Init, *pstDLC_Init;


typedef struct _stDLC_GetStatus
{
    XC_DLC_ApiStatus *pDrvStatus;
    MS_BOOL bWindow;
    MS_BOOL bReturn;
} stDLC_GetStatus, *pstDLC_GetStatus;

typedef struct _stDLC_SetPowerState
{
    EN_POWER_MODE enPowerState;
    MS_U32 u32Return;
} stDLC_SetPowerState, *pstDLC_SetPowerState;


typedef struct _stDBC_DLC_Init
{
    XC_DLC_DBC_MFinit DLC_DBC_MFinit;
} stDBC_DLC_Init, *pstDBC_DLC_Init;


typedef struct _stDBC_Init
{

} stDBC_Init, *pstDBC_Init;


typedef struct _stDBC_Setstatus
{
    MS_BOOL bDBCEnable;
} stDBC_Setstatus, *pstDBC_Setstatus;


typedef struct _stDBC_Getstatus
{
    MS_BOOL bReturn;
} stDBC_Getstatus, *pstDBC_Getstatus;


typedef struct _stDBC_SetReady
{
    MS_BOOL bDBCReady;
} stDBC_SetReady, *pstDBC_SetReady;


typedef struct _stDBC_SetDebugMode
{
    MS_U8 ucDBC_DebugMode;
} stDBC_SetDebugMode, *pstDBC_SetDebugMode;


typedef struct _stDBC_GetDebugMode
{
    MS_U8 u8Return;
} stDBC_GetDebugMode, *pstDBC_GetDebugMode;


typedef struct _stDBC_UpdatePWM
{
    MS_U8 u8PWMvalue;
} stDBC_UpdatePWM, *pstDBC_UpdatePWM;


typedef struct _stDBC_Handler
{
    MS_U16 u16Return;
} stDBC_Handler, *pstDBC_Handler;


typedef struct _stDBC_AdjustYCGain
{

} stDBC_AdjustYCGain, *pstDBC_AdjustYCGain;


typedef struct _stDBC_YCGainInit
{
    MS_U8 u8YGain_M;
    MS_U8 u8YGain_L;
    MS_U8 u8CGain_M;
    MS_U8 u8CGain_L;
} stDBC_YCGainInit, *pstDBC_YCGainInit;


typedef struct _stDBC_Reset
{

} stDBC_Reset, *pstDBC_Reset;


typedef struct _stDBC_DecodeExtCmd
{
    tDBC_CONTROL_PARAMS *params;
} stDBC_DecodeExtCmd, *pstDBC_DecodeExtCmd;

#ifdef __cplusplus
}
#endif

#undef _DLC_V2_H_
#endif //_DLC_V2_H_

