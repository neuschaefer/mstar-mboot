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
/// @file   apiXC_Adc.h
/// @brief  MStar ADC API
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _API_XC_ADC_H_
#define _API_XC_ADC_H_

// Common
#include "MsCommon.h"

#include "drvXC_IOPort.h"
#include "apiXC.h"

#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

/// Struct for store ADC Gain and Offset
typedef struct
{
    MS_U16 u16RedGain;      ///< ADC red gain
    MS_U16 u16GreenGain;    ///< ADC green gain
    MS_U16 u16BlueGain;     ///< ADC blue gain
    MS_U16 u16RedOffset;    ///< ADC red offset
    MS_U16 u16GreenOffset;  ///< ADC green offset
    MS_U16 u16BlueOffset;   ///< ADC blue offset
} APIXC_AdcGainOffsetSetting;

/// ADC output internal voltage type
typedef enum
{
    E_ADC_Internal_0V,      ///< Output   0V
    E_ADC_Internal_0_1V,    ///< Output 0.1V
    E_ADC_Internal_0_6V,    ///< Output 0.6V
    E_ADC_Internal_None,    ///< OFF
}ADC_Internal_Voltage;

/// ADC output Clock type
typedef enum
{
    E_ADC_Gen_480P_Clk,     ///< ADC output 480P
    E_ADC_Gen_720P_Clk,     ///< ADC output 720P
    E_ADC_Gen_1080P_Clk,    ///< ADC output 1080P
}ADC_Gen_Clock_Type;

/// ADC V Clamping type
typedef enum
{
    E_ADC_VClamp_0_85V,     ///< Clamp to 0.85V
    E_ADC_VClamp_0_9V,      ///< Clamp to 0.9V
    E_ADC_VClamp_0_95V,     ///< Clamp to 0.95V
    E_ADC_VClamp_1_0V,      ///< Clamp to 1.0V
    E_ADC_VClamp_1_05V,     ///< Clamp to 1.05V
    E_ADC_VClamp_1_2V,      ///< Clamp to 1.2V
    E_ADC_VClamp_1_5V,      ///< Clamp to 1.5V
}ADC_VClamp_Level_Type;

/// Update Gain / Offset for specific channel. This is used in MApi_XC_ADC_SetGain or MApi_XC_ADC_SetOffset
typedef enum
{
    ADC_CHR = 0,    ///< Channel R
    ADC_CHG,        ///< Channel G
    ADC_CHB,        ///< Channel B
    ADC_ALL,        ///< All Channel
}ADC_CHANNEL_t;

/// Software reset for ADCDVIPLL block
typedef enum
{
    REST_ATOP        = _BIT(7),     ///< Reset ATOP
    REST_HDMI        = _BIT(6),
    REST_HDCP        = _BIT(5),
    REST_DVI         = _BIT(4),
    REST_PLL_DIG_B   = _BIT(3),
    REST_ADC_DIG_B   = _BIT(2),
    REST_PLL_DIG_A   = _BIT(1),
    REST_ADC_DIG_A   = _BIT(0),
    REST_PLL         = ( REST_PLL_DIG_B | REST_PLL_DIG_A ), ///< Reset PLL
    REST_ADC         = ( REST_ADC_DIG_B | REST_ADC_DIG_A ), ///< Reset All ADC
} ADC_RESET;

typedef enum
{
    E_ADC_IDAC_FULL_MODE,
    E_ADC_IDAC_HALF_MODE,
    E_ADC_IDAC_QUART_MODE,
    E_ADC_IDAC_MODE_MAX,
} ADC_DacCurrentMode_t;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
//******************************************************************************
/// Enable and Disable CVBS out. This will setup ADC part for CVBS out (monitor out).
/// @param bEnable \b IN Enable CVBS Out
/// @param enInputPortType \b IN The source need to monitor out.
/// @param isDigitalSource \b IN Tell the driver current source is digital source or not. (ex. If internal VIF used in ATV, it will be digital source)
//******************************************************************************
DLL_PUBLIC void    MApi_XC_ADC_SetCVBSOut(MS_BOOL bEnable, E_DEST_TYPE enOutputType , INPUT_SOURCE_TYPE_t enInputPortType, MS_BOOL isDigitalSource);
DLL_PUBLIC MS_BOOL MApi_XC_ADC_IsCVBSOutEnabled(E_DEST_TYPE enOutputType);

/******************************************************************************/
/// Set ADC Sample clock
/// @param u16Value \b IN value need to be set.
/******************************************************************************/
DLL_PUBLIC void    MApi_XC_ADC_SetPcClock(MS_U16 u16Clock);

/******************************************************************************/
/// Set ADC Phase, pls use MApi_XC_ADC_SetPhaseEx instead
/// @param u8Value \b IN The adc phase need to be update
/******************************************************************************/
DLL_PUBLIC void    MApi_XC_ADC_SetPhase(MS_U8 u8Value);

/******************************************************************************/
/// Set ADC Phase Ex
/// @param u16Value \b IN The adc phase need to be update
/******************************************************************************/
DLL_PUBLIC void    MApi_XC_ADC_SetPhaseEx(MS_U16 u16Value);

//******************************************************************************
/// Get current ADC Phase set
/// @return Current Phase
//******************************************************************************
DLL_PUBLIC MS_U16     MApi_XC_ADC_GetPhaseRange( void );

//******************************************************************************
/// Get current ADC Phase set
/// @return Current Phase
//******************************************************************************
DLL_PUBLIC MS_U8    MApi_XC_ADC_GetPhase( void );
DLL_PUBLIC MS_U16   MApi_XC_ADC_GetPhaseEx( void );

DLL_PUBLIC MS_BOOL MApi_XC_ADC_IsScartRGB(void);
DLL_PUBLIC MS_U16  MApi_XC_ADC_GetPcClock(void );

/******************************************************************************/
///Get SOG level range
///@param u32Min \b OUT: min of SOG level
///@param u32Max \b OUT: max of SOG level
///@param u32Recommend_value \b OUT: recommend value
/******************************************************************************/
DLL_PUBLIC void    MApi_XC_ADC_GetSoGLevelRange(MS_U32 *u32min, MS_U32 *u32max, MS_U32 *u32Recommend_value);

/******************************************************************************/
///Set SOG level
///@param u32Min \b IN: set SOG level
/******************************************************************************/
DLL_PUBLIC void    MApi_XC_ADC_SetSoGLevel(MS_U32 u32Value);

// power
//******************************************************************************
/// Turn off ADC
//******************************************************************************
DLL_PUBLIC void    MApi_XC_ADC_PowerOff(void);

// ADC calibration
//******************************************************************************
/// Get ADC Default gain / offset by referring input structure.
/// @param eSource \b IN The input source
/// @param pstADCSetting \b IN gain / offset need to be set
//******************************************************************************
DLL_PUBLIC void MApi_XC_ADC_GetDefaultGainOffset(INPUT_SOURCE_TYPE_t eSource , APIXC_AdcGainOffsetSetting* pstADCSetting);

//******************************************************************************
/// get maximal value of offset
/// @param
/// @return maximal value of offset
//******************************************************************************
DLL_PUBLIC MS_U16 MApi_XC_ADC_GetMaximalOffsetValue(void);

//******************************************************************************
/// get maximal value of gain
/// @param
/// @return maximal value of gain
//******************************************************************************
DLL_PUBLIC MS_U16  MApi_XC_ADC_GetMaximalGainValue(void);

//******************************************************************************
/// get center value of gain
/// @param
/// @return center value of gain
//******************************************************************************
DLL_PUBLIC MS_U16 MApi_XC_ADC_GetCenterGain(void);

//******************************************************************************
/// get center value of offset
/// @param
/// @return center value of offset
//******************************************************************************
DLL_PUBLIC MS_U16 MApi_XC_ADC_GetCenterOffset(void);

// Set Gain & Offset
// u8Color is one of ADC_CHANNEL_t.
//******************************************************************************
/// Set Gain value
/// @param u8color \b IN The channel type need to be set
/// @param u16value \b IN The value need to be set.
//******************************************************************************
DLL_PUBLIC void MApi_XC_ADC_SetGain(MS_U8 u8Color, MS_U16 u16Value);

//******************************************************************************
/// Set offset value
/// @param u8color \b IN The channel type need to be set
/// @param u16value \b IN The value need to be set.
//******************************************************************************
DLL_PUBLIC void MApi_XC_ADC_SetOffset(MS_U8 u8Color, MS_U16 u16Value);

//******************************************************************************
/// Set ADC gain / offset by referring input structure.
/// @param pstADCSetting \b IN gain / offset need to be set
//******************************************************************************
DLL_PUBLIC void MApi_XC_ADC_AdjustGainOffset(APIXC_AdcGainOffsetSetting* pstADCSetting);

//******************************************************************************
/// Set ADC Internal calibration. (need to be set during set mode)
/// @param enInputSourceType \b IN current input source.
//******************************************************************************
DLL_PUBLIC void MApi_XC_ADC_Source_Calibrate(INPUT_SOURCE_TYPE_t enInputSourceType);

/******************************************************************************/
///Set SOG level
///@param u32Min \b IN: set SOG calibration
/******************************************************************************/
DLL_PUBLIC void MApi_XC_ADC_SetSoGCal(void);

//Set SCART RGB PIPE Delay
DLL_PUBLIC void MApi_XC_ADC_SetRGB_PIPE_Delay(MS_U8 u8Value);

//Set Scart RGB Sync on green clamp delay value
DLL_PUBLIC void MApi_XC_ADC_ScartRGB_SOG_ClampDelay(MS_U16 u16Clpdly, MS_U16 u16Caldur);

DLL_PUBLIC void MApi_XC_ADC_Set_YPbPrLooseLPF(MS_BOOL benable);

/******************************************************************************/
///Set SOG BW
///@param u16value \b IN: set SOG BW
/******************************************************************************/
DLL_PUBLIC void MApi_XC_ADC_Set_SOGBW(MS_U16 u16value);

// Set Clamp Duration
DLL_PUBLIC void MApi_XC_ADC_SetClampDuration(MS_U16 u16Value);

/******************************************************************************/
///Enable HW calibration, will load hw adc table when changing source
///@param bEnable \b IN: enable hw calibration
/******************************************************************************/
DLL_PUBLIC MS_BOOL MApi_XC_ADC_EnableHWCalibration(MS_BOOL bEnable);

/******************************************************************************/
///This function set CVBS Out IDAC curret mode.
///@param stMode \b IDAC current mode.
/******************************************************************************/
DLL_PUBLIC MS_BOOL MApi_XC_ADC_SetIdacCurrentMode(ADC_DacCurrentMode_t eMode);

/******************************************************************************/
///This function get CVBS Out IDAC current mode.
///@return IDAC current mode.
/******************************************************************************/
DLL_PUBLIC ADC_DacCurrentMode_t MApi_XC_ADC_GetIdacCurrentMode(void);

#ifdef __cplusplus
}
#endif

#endif  // _API_XC_ADC_H_

