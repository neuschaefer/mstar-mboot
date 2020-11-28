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

typedef struct
{

    MS_U16 u16HorizontalStart;      ///< horizontal start
    MS_U16 u16VerticalStart;        ///< vertical start
    MS_U16 u16HorizontalTotal;      ///< ADC horizontal total
    MS_U16 u16HResolution;          ///< H size
    MS_U8  u8Phase;                 ///< ADC phase

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

#ifdef __cplusplus
}
#endif

#endif /* _APIXC_AUTO_H_ */
