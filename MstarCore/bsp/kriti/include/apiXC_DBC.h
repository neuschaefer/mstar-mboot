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
DLL_PUBLIC void    MApi_XC_DLC_DBC_Init(XC_DLC_DBC_MFinit DLC_DBC_MFinit);


DLL_PUBLIC void MApi_XC_DBC_Init(void);

//-------------------------------------------------------------------------------------------------
/// DLC DBC set status
// @param bDBCEnable               \b IN: TBD
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_DLC_DBC_Setstatus(MS_BOOL bDBCEnable);

//-------------------------------------------------------------------------------------------------
/// DLC DBC get status
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_XC_DLC_DBC_Getstatus(void);

//-------------------------------------------------------------------------------------------------
/// Set DBC Ready Mode 
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_DLC_DBC_SetReady(MS_BOOL bDBCReady);

//-------------------------------------------------------------------------------------------------
/// Set DLC DBC Debug Mode 
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_XC_DLC_DBC_SetDebugMode(MS_U8 ucDBC_DebugMode);

//-------------------------------------------------------------------------------------------------
/// DLC DBC Debug Mode Status
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U8 MApi_XC_DLC_DBC_GetDebugMode(void);

//-------------------------------------------------------------------------------------------------
/// DLC DBC update PWM
/// @param   u8PWMvalue           \b IN: PWM value to set the lumming
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_DLC_DBC_UpdatePWM(MS_U8 u8PWMvalue);

//-------------------------------------------------------------------------------------------------
/// DLC DBC handler
/// @return @ref MS_U16
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_U16  MApi_XC_DLC_DBC_Handler(void);

//-------------------------------------------------------------------------------------------------
/// DLC DBC adjsut YC gain
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_DLC_DBC_AdjustYCGain(void);

//-------------------------------------------------------------------------------------------------
/// DLC DBC YC gain initilization
// @param u8YGain_M               \b IN: TBD
// @param u8YGain_L               \b IN: TBD
// @param u8CGain_M               \b IN: TBD
// @param u8CGain_L               \b IN: TBD
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_DLC_DBC_YCGainInit(MS_U8 u8YGain_M, MS_U8 u8YGain_L, MS_U8 u8CGain_M, MS_U8 u8CGain_L);

//-------------------------------------------------------------------------------------------------
/// DLC DBC reset
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void    MApi_XC_DLC_DBC_Reset(void);

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
DLL_PUBLIC void MApi_XC_DBC_DecodeExtCmd(tDBC_CONTROL_PARAMS *params );

#ifdef __cplusplus
}
#endif

#endif // _API_XC_DBC_H_
