////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
/// @file  apiXC_PCMonitor.h
/// @brief header file
/// @author MStar Semiconductor Inc.
///
////////////////////////////////////////////////////////////////////////////////
#ifndef _API_XC_PC_MONITOR_H_
#define _API_XC_PC_MONITOR_H_
#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

#define ENABLE_IP_AUTO_COAST    (0)

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

/// Indecate the status of pc monitor.
typedef enum
{
    E_XC_PCMONITOR_STABLE_NOSYNC = 0,       ///< Input timing stable, no input sync detected
    E_XC_PCMONITOR_STABLE_SYNC ,            ///< Input timing stable, no input sync detected
    E_XC_PCMONITOR_UNSTABLE,                ///< Timing change, has to wait InfoFrame if HDMI input
} XC_PCMONITOR_STATUS;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

MS_BOOL MApi_XC_PCMonitor_Init(MS_U8 u8MaxWindowNum);
void MApi_XC_PCMonitor_Restart(SCALER_WIN eWindow);
void MApi_XC_PCMonitor_SetTimingCount(MS_U16 u16TimingStableCounter, MS_U16 u16TimingNosyncCounter);

XC_PCMONITOR_STATUS MApi_XC_PCMonitor(INPUT_SOURCE_TYPE_t src, SCALER_WIN eWindow);

// get input timing information
XC_PCMONITOR_STATUS MApi_XC_PCMonitor_GetCurrentState(SCALER_WIN eWindow);
MS_U8 MApi_XC_PCMonitor_GetSyncStatus(SCALER_WIN eWindow);
MS_U16 MApi_XC_PCMonitor_Get_HFreqx10(SCALER_WIN eWindow);
MS_U16 MApi_XC_PCMonitor_Get_VFreqx10(SCALER_WIN eWindow);
MS_U16 MApi_XC_PCMonitor_Get_Vtotal(SCALER_WIN eWindow);
void MApi_XC_PCMonitor_Get_Dvi_Hdmi_De_Info(SCALER_WIN eWindow,MS_WINDOW_TYPE* msWin);
MS_BOOL MApi_XC_PCMonitor_SyncLoss(SCALER_WIN eWindow);
MS_BOOL MApi_XC_PCMonitor_InvalidTimingDetect(MS_BOOL bPollingOnly, SCALER_WIN eWindow);

#ifdef __cplusplus
}
#endif

#endif /* _API_XC_PC_MONITOR_H_ */
