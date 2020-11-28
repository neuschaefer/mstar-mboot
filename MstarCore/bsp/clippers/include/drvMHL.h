//<MStar Software>//******************************************************************************// MStar Software// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.// All software, firmware and related documentation herein ("MStar Software") are// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by// law, including, but not limited to, copyright law and international treaties.// Any use, modification, reproduction, retransmission, or republication of all// or part of MStar Software is expressly prohibited, unless prior written// permission has been granted by MStar.//// By accessing, browsing and/or using MStar Software, you acknowledge that you// have read, understood, and agree, to be bound by below terms ("Terms") and to// comply with all applicable laws and regulations://// 1. MStar shall retain any and all right, ownership and interest to MStar//    Software and any modification/derivatives thereof.//    No right, ownership, or interest to MStar Software and any//    modification/derivatives thereof is transferred to you under Terms.//// 2. You understand that MStar Software might include, incorporate or be//    supplied together with third party`s software and the use of MStar//    Software may require additional licenses from third parties.//    Therefore, you hereby agree it is your sole responsibility to separately//    obtain any and all third party right and license necessary for your use of//    such third party`s software.//// 3. MStar Software and any modification/derivatives thereof shall be deemed as//    MStar`s confidential information and you agree to keep MStar`s//    confidential information in strictest confidence and not disclose to any//    third party.//// 4. MStar Software is provided on an "AS IS" basis without warranties of any//    kind. Any warranties are hereby expressly disclaimed by MStar, including//    without limitation, any warranties of merchantability, non-infringement of//    intellectual property rights, fitness for a particular purpose, error free//    and in conformity with any international standard.  You agree to waive any//    claim against MStar for any loss, damage, cost or expense that you may//    incur related to your use of MStar Software.//    In no event shall MStar be liable for any direct, indirect, incidental or//    consequential damages, including without limitation, lost of profit or//    revenues, lost or damage of data, and unauthorized system use.//    You agree that this Section 4 shall still apply without being affected//    even if MStar Software has been modified by MStar in accordance with your//    request or instruction for your use, except otherwise agreed by both//    parties in writing.//// 5. If requested, MStar may from time to time provide technical supports or//    services in relation with MStar Software to you for your use of//    MStar Software in conjunction with your or your customer`s product//    ("Services").//    You understand and agree that, except otherwise agreed by both parties in//    writing, Services are provided on an "AS IS" basis and the warranty//    disclaimer set forth in Section 4 above shall apply.//// 6. Nothing contained herein shall be construed as by implication, estoppels//    or otherwise://    (a) conferring any license or right to use MStar name, trademark, service//        mark, symbol or any other identification;//    (b) obligating MStar or any of its affiliates to furnish any person,//        including without limitation, you and your customers, any assistance//        of any kind whatsoever, or any information; or//    (c) conferring any license or right under any intellectual property right.//// 7. These terms shall be governed by and construed in accordance with the laws//    of Taiwan, R.O.C., excluding its conflict of law rules.//    Any and all dispute arising out hereof or related hereto shall be finally//    settled by arbitration referred to the Chinese Arbitration Association,//    Taipei in accordance with the ROC Arbitration Law and the Arbitration//    Rules of the Association by three (3) arbitrators appointed in accordance//    with the said Rules.//    The place of arbitration shall be in Taipei, Taiwan and the language shall//    be English.//    The arbitration award shall be final and binding to both parties.////******************************************************************************//<MStar Software>///////////////////////////////////////////////////////////////////////////////////////////////////////// @file   Mdrv_mhl.h/// @author MStar Semiconductor Inc./// @brief  MHL driver Function///////////////////////////////////////////////////////////////////////////////////////////////////#ifndef _DRV_MHL_H_#define _DRV_MHL_H_#include "mdrv_mhl_st.h"//-------------------------------------------------------------------------------------------------//  Macro and Define//-------------------------------------------------------------------------------------------------#ifndef UNUSED#define UNUSED(x) (void)(x)#endifenum MHL_SYSTEM_CONTROL_TYPE{    MHL_CABLE_PLUGGED = 0,    MHL_CABLE_UNPLUGGED,    MHL_INPUT_SOURCE_CHANGE,    MHL_CBUS_UNCONNECTION,    MHL_CBUS_CONNECTION,    MHL_CBUS_NORMAL_24BIT_MODE,    MHL_CBUS_PACKET_PIXEL_MODE,    MHL_CBUS_AUTO_EQ_SETTING,    MHL_CBUS_WAKE_UP_DETECT,    MHL_CBUS_TEST_RASING,    MHL_CBUS_TEST_FALLING,};enum MHL_CABLE_DETECT_TYPE{    MHL_CABLE_DETECT_PORTA_FLAG = 0x01,    MHL_CABLE_DETECT_PORTB_FLAG = 0x02,    MHL_CABLE_DETECT_PORTC_FLAG = 0x04,    MHL_CABLE_DETECT_PORTD_FLAG = 0x08,};enum MHL_ENABLE_FUNCTION_TYPE{    MHL_ENABLE_FORCE_SEND_COMMAND_FLAG = BIT(0),    MHL_INTERRUPT_USE_PM_IRQ_FLAG = BIT(1),};//-------------------------------------------------------------------------------------------------//  Type and Structure//-------------------------------------------------------------------------------------------------extern MS_U8 ucMHLCbusSelect;extern MS_U8 ucMHLClockMode;extern MS_U8 ucMHLCableDetect;extern MS_U8 ucMHLWriteBurstSequence;extern MS_U8 ucMHL3DTotalEntryDTD;extern MS_U8 ucMHL3DTotalEntryVIC;extern MS_U8 ucMHL3DInformationDTD[];extern MS_U8 ucMHL3DInformationVIC[];extern MS_U8 ucMHLFunctionCapability;#define GET_MHL_CABLE_DETECT_PORTA()    (MS_BOOL)((ucMHLCableDetect & MHL_CABLE_DETECT_PORTA_FLAG) ?TRUE :FALSE)#define SET_MHL_CABLE_DETECT_PORTA()    (ucMHLCableDetect |= MHL_CABLE_DETECT_PORTA_FLAG)#define CLR_MHL_CABLE_DETECT_PORTA()    (ucMHLCableDetect &= ~MHL_CABLE_DETECT_PORTA_FLAG)#define GET_MHL_CABLE_DETECT_PORTB()    (MS_BOOL)((ucMHLCableDetect & MHL_CABLE_DETECT_PORTB_FLAG) ?TRUE :FALSE)#define SET_MHL_CABLE_DETECT_PORTB()    (ucMHLCableDetect |= MHL_CABLE_DETECT_PORTB_FLAG)#define CLR_MHL_CABLE_DETECT_PORTB()    (ucMHLCableDetect &= ~MHL_CABLE_DETECT_PORTB_FLAG)#define GET_MHL_CABLE_DETECT_PORTC()    (MS_BOOL)((ucMHLCableDetect & MHL_CABLE_DETECT_PORTC_FLAG) ?TRUE :FALSE)#define SET_MHL_CABLE_DETECT_PORTC()    (ucMHLCableDetect |= MHL_CABLE_DETECT_PORTC_FLAG)#define CLR_MHL_CABLE_DETECT_PORTC()    (ucMHLCableDetect &= ~MHL_CABLE_DETECT_PORTC_FLAG)#define GET_MHL_CABLE_DETECT_PORTD()    (MS_BOOL)((ucMHLCableDetect & MHL_CABLE_DETECT_PORTD_FLAG) ?TRUE :FALSE)#define SET_MHL_CABLE_DETECT_PORTD()    (ucMHLCableDetect |= MHL_CABLE_DETECT_PORTD_FLAG)#define CLR_MHL_CABLE_DETECT_PORTD()    (ucMHLCableDetect &= ~MHL_CABLE_DETECT_PORTD_FLAG)#define GET_MHL_CABLE_DETECT_PORT(a)    (MS_BOOL)((ucMHLCableDetect & BIT(a)) ?TRUE :FALSE)#define SET_MHL_CABLE_DETECT_PORT(a)    (ucMHLCableDetect |= BIT(a))#define CLR_MHL_CABLE_DETECT_PORT(a)    (ucMHLCableDetect &= ~(BIT(a)))#define GET_MHL_CABLE_DETECT_ALL()      (ucMHLCableDetect)#define GET_MHL_WRITE_BURST_SEQUENCE()  (ucMHLWriteBurstSequence)#define SET_MHL_WRITE_BURST_SEQUENCE(a) (ucMHLWriteBurstSequence = a)#define GET_MHL_CBUS_SELECT_PATH()      (ucMHLCbusSelect)#define SET_MHL_CBUS_SELECT_PATH(a)     (ucMHLCbusSelect = a)#define GET_MHL_INPUT_CLOCK_MODE()      (ucMHLClockMode)#define SET_MHL_INPUT_CLOCK_MODE(a)     (ucMHLClockMode = a)#define GET_MHL_3D_TOT_ENT_DTD()        (ucMHL3DTotalEntryDTD)#define SET_MHL_3D_TOT_ENT_DTD(a)       (ucMHL3DTotalEntryDTD = a)#define GET_MHL_3D_TOT_ENT_VIC()        (ucMHL3DTotalEntryVIC)#define SET_MHL_3D_TOT_ENT_VIC(a)       (ucMHL3DTotalEntryVIC = a)#define GET_MHL_3D_DTD_INFORMATION(a)   (ucMHL3DInformationDTD[a])#define SET_MHL_3D_DTD_INFORMATION(a,b) (ucMHL3DInformationDTD[a] = b)#define GET_MHL_3D_VIC_INFORMATION(a)   (ucMHL3DInformationVIC[a])#define SET_MHL_3D_VIC_INFORMATION(a,b) (ucMHL3DInformationVIC[a] = b)#define GET_MHL_ENABLE_FORCE_SEND()     (MS_BOOL)((ucMHLFunctionCapability & MHL_ENABLE_FORCE_SEND_COMMAND_FLAG) ?TRUE :FALSE)#define GET_MHL_INTERRUPT_USE_PM_IRQ()  (MS_BOOL)((ucMHLFunctionCapability & MHL_INTERRUPT_USE_PM_IRQ_FLAG) ?TRUE :FALSE)//-------------------------------------------------------------------------------------------------//  Function Prototype//-------------------------------------------------------------------------------------------------void mdrv_mhl_MHLSupportPath(MS_U8 ucSelect);void mdrv_mhl_initial(MS_U8 *edid, MS_U8 *DevCap);void mdrv_mhl_LoadEDID(MS_U8 *edid);void mdrv_mhl_ReadEDID(MS_U16 usSize, MS_U8 *edid);void mdrv_mhl_LoadDeviceCapability(MS_U8 *devcap);MS_BOOL mdrv_mhl_CheckIsrUsePMPath(void);void mdrv_mhl_ParsingEDIDfor3D(MS_U8 *pEdid);MS_BOOL mdrv_mhl_GetDTDBurstfor3D(MS_U8 *pData, MS_U8 *uc3DSequence);MS_BOOL mdrv_mhl_GetVICBurstfor3D(MS_U8 *pData, MS_U8 *uc3DSequence);void mdrv_mhl_SetVenderID(MS_U8 ucVenderID);void mdrv_mhl_InvertCableDetect(MS_BOOL bCableDetectInvert);void mdrv_mhl_VbusConfigSetting(MS_U8 ucState);void mdrv_mhl_CableDetectPadSetting(MS_U8 ucSelect);MS_U8 mdrv_mhl_GetInputPort(void);MS_BOOL mdrv_mhl_CheckInputPort(void);MS_U8 mdrv_mhl_GetCbusPath(void);MS_BOOL mdrv_mhl_CheckSendCommand(MS_BOOL bForceSendCommand);MS_BOOL mdrv_mhl_CableDetect(void);MS_BOOL mdrv_mhl_CheckInputCbusSelect(MS_U8 ucPort);MS_BOOL mdrv_mhl_AutoSwitchCbusSelect(void);MS_BOOL mdrv_mhl_CbusInitialProc(void);void mdrv_mhl_CbusConnectProc(void);MS_U8 mdrv_mhl_CbusStucktoLowProc(void);void mdrv_mhl_ClockModeSwitch(MS_U8 ucSelect);void mdrv_mhl_SourceChangeProc(MS_U8 ucPort);MS_BOOL mdrv_mhl_CBusStablePolling(MS_BOOL bFlag);void mdrv_mhl_CbusWakeupIntSetting(MS_BOOL bFlag);void mdrv_mhl_CbusIsolate(MS_BOOL bFlag);MS_U16 mdrv_mhl_CbusStatus(void);MS_BOOL mdrv_mhl_CbusIsMscMsgReceived(void);MS_BOOL mdrv_mhl_CbusStucktoLowFlag(void);MS_BOOL mdrv_mhl_CbusWakeupIntFlag(void);MS_BOOL mdrv_mhl_CbusIntCB(CbusReq_S *preq, MS_BOOL *bflag);MS_U8 mdrv_mhl_GetDevCap(MS_U8 ucIndex);MS_U8 mdrv_mhl_GetVenderID(void);MS_U8 mdrv_mhl_GetDDCErrorCode(void);void mdrv_mhl_Cbus_SetPathEn(MS_BOOL bFlag);MS_BOOL mdrv_mhl_CbusReply (MS_U8 ctrlpky, MS_BOOL bflag, MS_U8 databuf);MS_BOOL mdrv_mhl_CBusWriteCmd(CbusReq_S *pReq);void mdrv_mhl_CbusControl(MS_U8 ucState);void mdrv_mhl_CbusConfigControl(MS_BOOL bState);void mdrv_mhl_CbusPadConfigSwitch(MS_BOOL bFlag);void mdrv_mhl_RtermControlHWMode(MS_BOOL bFlag);void mdrv_mhl_AdjustSettingIControl(MS_U8 ucIControl);void mdrv_mhl_AdjustImpedanceSetting(MS_U8 ucImpedance);MS_BOOL mdrv_mhl_GetRAPEnableFlag(void);#if(MHL_CBUS_OPERATION_MODE == MHL_CBUS_HW_REPLY_MODE)MS_BOOL mdrv_mhl_CheckSRAMReceiveBuffer(void);MS_U16 mdrv_mhl_GetSRAMReceiveData(void);#endifvoid mdrv_mhl_SetHPD(MS_BOOL bflag);void mdrv_mhl_PowerOn(void);void mdrv_mhl_PowerStandby(MS_BOOL bFlag);void mdrv_mhl_PowerDown(void);#endif //_MDRV_MHL_H_