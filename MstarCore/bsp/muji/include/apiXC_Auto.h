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
/// @file  apiXC_Auto.h
/// @brief XC api for Auto
/// @author MStar Semiconductor Inc.
///
////////////////////////////////////////////////////////////////////////////////
#ifndef _APIXC_AUTO_H_
#define _APIXC_AUTO_H_
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
#define XC_AUTO_SIGNAL_INFO_VERSION 1

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef enum
{
    E_XC_AUTO_TUNE_NULL = 0x00,

    // Basic auto-tune
    E_XC_AUTO_TUNE_VALID_DATA    =   0x01,
    E_XC_AUTO_TUNE_POSITION      =   0x02,
    E_XC_AUTO_TUNE_FREQ          =   0x04,
    E_XC_AUTO_TUNE_PHASE         =   0x08,
    E_XC_AUTO_TUNE_BASIC         =   E_XC_AUTO_TUNE_VALID_DATA | E_XC_AUTO_TUNE_POSITION | E_XC_AUTO_TUNE_FREQ | E_XC_AUTO_TUNE_PHASE,

    // Auto-tune RGB Color
    E_XC_AUTO_TUNE_RGB_OFFSET    =   0x10,
    E_XC_AUTO_TUNE_RGB_GAIN      =   0X20,
    E_XC_AUTO_TUNE_RGB_COLOR     =   E_XC_AUTO_TUNE_RGB_OFFSET | E_XC_AUTO_TUNE_RGB_GAIN,

    // Auto-tune YUV Color
    E_XC_AUTO_TUNE_YUV_COLOR     =   0X40,

    E_XC_AUTO_TUNE_SCART_RGB_GAIN =  0x80,

    // Advance auto-tune
    E_XC_AUTO_TUNE_ADVANCE       =   E_XC_AUTO_TUNE_BASIC | E_XC_AUTO_TUNE_RGB_COLOR,
} XC_Auto_TuneType;

typedef enum
{
    E_XC_INTERNAL_CALIBRATION,
    E_XC_EXTERNAL_CALIBRATION,
} XC_Auto_CalibrationType;

typedef enum
{
    E_XC_HW_CALIBRATION,
    E_XC_SW_CALIBRATION,
} XC_Auto_CalibrationMode;

typedef enum
{
    E_XC_AUTO_POR_HPVP,
    E_XC_AUTO_POR_HPVN,
    E_XC_AUTO_POR_HNVP,
    E_XC_AUTO_POR_HNVN,
}XC_Auto_SYNC_POR;

typedef struct
{

    MS_U16 u16HorizontalStart;      ///< horizontal start
    MS_U16 u16VerticalStart;        ///< vertical start
    MS_U16 u16HorizontalTotal;      ///< ADC horizontal total
    MS_U16 u16HResolution;          ///< H size
    MS_U8  u8Phase;                 ///< obsolete

} XC_Auto_Signal_Info;

typedef struct
{
    MS_U16 u16Version;              ///< version
    MS_U16 u16HorizontalStart;      ///< horizontal start
    MS_U16 u16VerticalStart;        ///< vertical start
    MS_U16 u16HorizontalTotal;      ///< ADC horizontal total
    MS_U16 u16HResolution;          ///< H size
    MS_U16 u16Phase;                ///< ADC phase
} XC_Auto_Signal_Info_Ex;

typedef struct
{
    INPUT_SOURCE_TYPE_t eCurrentSrc;
    SCALER_WIN eWindow;
    XC_Auto_SYNC_POR eSyncPolarity;
    MS_U32 u32HSyncStart;
    MS_U32 u32HSyncEnd;
}XC_AUTO_SYNC_INFO;
//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
//*************************************************************************
//Function name: MApi_XC_Auto_Geometry
//Passing parameter:
//  enAutoTuneType: Auto function select
//  ActiveInfo: Current PC mode setting
//  StandardInfo: Standard mode. (This is singal information of stardard)
//Return parameter:
//  MS_BOOL: Success status. (If faile, return FALSE.)
//Description: Auto-tune for PC mode
//*************************************************************************
MS_BOOL MApi_XC_Auto_Geometry(XC_Auto_TuneType enAutoTuneType, XC_Auto_Signal_Info *ActiveInfo, XC_Auto_Signal_Info *StandardInfo, SCALER_WIN eWindow);

MS_BOOL MApi_XC_Auto_Geometry_Ex(XC_Auto_TuneType enAutoTuneType, XC_Auto_Signal_Info_Ex *ActiveInfo, XC_Auto_Signal_Info_Ex *StandardInfo, SCALER_WIN eWindow);

MS_BOOL MApi_XC_Auto_StopAutoGeometry(void); // Call MApi_XC_Auto_Geometry to restart auto geometry again.

MS_BOOL MApi_XC_Auto_GainOffset(XC_Auto_CalibrationType type, XC_Auto_TuneType enAutoTuneType,  APIXC_AdcGainOffsetSetting *pstADCSetting, SCALER_WIN eWindow);

//***************************************************************************
///-This function is to get fixed gain for HW calibration
/// @param  enAutoTuneType      \b IN:tune type
/// @param  pstADCSetting       \b OUT:gain value
/// @return @ref MS_BOOL
//***************************************************************************
MS_BOOL MApi_XC_Auto_GetHWFixedGainOffset(XC_Auto_TuneType enAutoTuneType, APIXC_AdcGainOffsetSetting *pstADCSetting);

//***************************************************************************
///-This function is to set ValidDataThreshold by customer
/// @param  Value        \b IN:ValidDataThreshold
/// @return @ref MS_BOOL
//***************************************************************************
MS_BOOL MApi_XC_Auto_SetValidData(MS_U8 Value);

/******************************************************************************/
/// -This function will recalibration ADC offset, must be called when mode change.
/// @param bEnable \b IN:
/// - 0: Disable offset recalibration
/// - 1: Enable offset recalibration
/// @param bIsYPbPrFlag \b IN: to tell if YPbPr in
/// - 0: Vga mode
/// - 1: YPbPr mode
/******************************************************************************/
void MApi_XC_Auto_AutoOffset(MS_BOOL bEnable, MS_BOOL bIsYPbPrFlag);

/******************************************************************************/
/// -This function will try to get the actual mode width for VGA
/// @param  eWindow          \b IN: Window
/// @param  pSignalInfo      \b IN: Input signal info for distinguish
/// Note: The result of "MApi_XC_Auto_DetectWidth"  will highly depends on the HTT value of pSignalInfo
/******************************************************************************/
MS_BOOL MApi_XC_Auto_DetectWidth(XC_Auto_Signal_Info_Ex *pSignalInfo , SCALER_WIN eWindow);

//***************************************************************************
///-This function is to set HW or Sw calibration
/// @param  eMode        \b IN: HW or SW mode for calibration
/// @return @ref MS_BOOL
//***************************************************************************
MS_BOOL MApi_XC_Auto_SetCalibrationMode(XC_Auto_CalibrationMode eMode);

//***************************************************************************
///-This function is to get HW or Sw calibration
/// @param  eMode        \b OUT: HW or SW mode for calibration
//***************************************************************************
void MApi_XC_Auto_GetCalibrationMode(XC_Auto_CalibrationMode *eMode);

void MApi_XC_AUTO_GetSyncInfo(XC_AUTO_SYNC_INFO *pSyncInfo);


#ifdef __cplusplus
}
#endif

#endif /* _APIXC_AUTO_H_ */
