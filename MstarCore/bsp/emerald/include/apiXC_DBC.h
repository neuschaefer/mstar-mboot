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
/// @file   apiXC_Dlc.h
/// @brief  DLC API layer Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _API_XC_DBC_H_
#define _API_XC_DBC_H_

#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
/// DLC DBC initilization
// @param DLC_DBC_MFinit               \b IN: TBD
//-------------------------------------------------------------------------------------------------
void    MApi_XC_DLC_DBC_Init(XC_DLC_DBC_MFinit DLC_DBC_MFinit);


void MApi_XC_DBC_Init(void);

//-------------------------------------------------------------------------------------------------
/// DLC DBC set status
// @param bDBCEnable               \b IN: TBD
//-------------------------------------------------------------------------------------------------
void    MApi_XC_DLC_DBC_Setstatus(MS_BOOL bDBCEnable);

//-------------------------------------------------------------------------------------------------
/// DLC DBC get status
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
MS_BOOL MApi_XC_DLC_DBC_Getstatus(void);

//-------------------------------------------------------------------------------------------------
/// Set DBC Ready Mode 
//-------------------------------------------------------------------------------------------------
void MApi_XC_DLC_DBC_SetReady(MS_BOOL bDBCReady);

//-------------------------------------------------------------------------------------------------
/// Set DLC DBC Debug Mode 
//-------------------------------------------------------------------------------------------------
void MApi_XC_DLC_DBC_SetDebugMode(MS_U8 ucDBC_DebugMode);

//-------------------------------------------------------------------------------------------------
/// DLC DBC Debug Mode Status
//-------------------------------------------------------------------------------------------------
MS_U8 MApi_XC_DLC_DBC_GetDebugMode(void);

//-------------------------------------------------------------------------------------------------
/// DLC DBC update PWM
/// @param   u8PWMvalue           \b IN: PWM value to set the lumming
//-------------------------------------------------------------------------------------------------
void    MApi_XC_DLC_DBC_UpdatePWM(MS_U8 u8PWMvalue);

//-------------------------------------------------------------------------------------------------
/// DLC DBC handler
/// @return @ref MS_U16
//-------------------------------------------------------------------------------------------------
MS_U16  MApi_XC_DLC_DBC_Handler(void);

//-------------------------------------------------------------------------------------------------
/// DLC DBC adjsut YC gain
//-------------------------------------------------------------------------------------------------
void    MApi_XC_DLC_DBC_AdjustYCGain(void);

//-------------------------------------------------------------------------------------------------
/// DLC DBC YC gain initilization
// @param u8YGain_M               \b IN: TBD
// @param u8YGain_L               \b IN: TBD
// @param u8CGain_M               \b IN: TBD
// @param u8CGain_L               \b IN: TBD
//-------------------------------------------------------------------------------------------------
void    MApi_XC_DLC_DBC_YCGainInit(MS_U8 u8YGain_M, MS_U8 u8YGain_L, MS_U8 u8CGain_M, MS_U8 u8CGain_L);

//-------------------------------------------------------------------------------------------------
/// DLC DBC reset
//-------------------------------------------------------------------------------------------------
void    MApi_XC_DLC_DBC_Reset(void);

//-------------------------------------------------------------------------------------------------
/// @brief callback functions & struct used to support debug command.
//-------------------------------------------------------------------------------------------------
typedef void   (*MApi_XC_DBC_OnOff_Callback)(MS_BOOL/*On/Off*/);

//-------------------------------------------------------------------------------------------------
/// @brief callback functions & struct used to support debug command.
//-------------------------------------------------------------------------------------------------
typedef void   (*MApi_XC_DBC_AdjustBackLight_Callback)(MS_U32 /*PWM_VALUE*/);

//-------------------------------------------------------------------------------------------------
/// @brief structure used to support debug command.
//-------------------------------------------------------------------------------------------------
typedef struct {
    MS_U8 *pCmdBuff;                                            ///<1. command buffer from UART
    MApi_XC_DBC_OnOff_Callback           fnDBC_AP_OnOff;        ///<2. Function to control DBC on/off
    MApi_XC_DBC_AdjustBackLight_Callback fnDBC_AdjustBacklight; ///<3. Functoin to control backlight
    MApi_XC_DLC_Print_Callback           fnDBC_Putchar;         ///<4. User putchar function
}tDBC_CONTROL_PARAMS;

//-------------------------------------------------------------------------------------------------
/// @brief uart debug command decoder for Dynamic Backlight Control.
/// @param params   passin params.  
//-------------------------------------------------------------------------------------------------
void MApi_XC_DBC_DecodeExtCmd(tDBC_CONTROL_PARAMS *params );

#ifdef __cplusplus
}
#endif

#endif // _API_XC_DBC_H_
