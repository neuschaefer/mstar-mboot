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
#ifndef __DRV_DEMOD_NULL_H__
#define __DRV_DEMOD_NULL_H__

MS_BOOL MDrv_Demod_null_init(MS_U8 u8DemodIndex);
MS_BOOL MDrv_Demod_null_open(MS_U8 u8DemodIndex);
MS_BOOL MDrv_Demod_null_Close(MS_U8 u8DemodIndex);
MS_BOOL MDrv_Demod_null_Reset(MS_U8 u8DemodIndex);
MS_BOOL MDrv_Demod_null_TsOut(MS_U8 u8DemodIndex,MS_BOOL bEnable);
MS_BOOL MDrv_Demod_null_PowerOnOff(MS_U8 u8DemodIndex,MS_BOOL bPowerOn);
MS_BOOL MDrv_Demod_null_SetBW(MS_U8 u8DemodIndex,MS_U32 u32BW);
MS_BOOL MDrv_Demod_null_GetBW(MS_U8 u8DemodIndex,MS_U32 *pu32BW);
MS_BOOL MDrv_Demod_null_GetLock(MS_U8 u8DemodIndex,EN_LOCK_STATUS *peLockStatus);
MS_BOOL MDrv_Demod_null_GetSNR(MS_U8 u8DemodIndex,MS_U32 *pu32SNR);
MS_BOOL MDrv_Demod_null_GetBER(MS_U8 u8DemodIndex,float *pfBER);
MS_BOOL MDrv_Demod_null_GetPWR(MS_U8 u8DemodIndex,MS_S32 *ps32Signal);
MS_BOOL MDrv_Demod_null_Config(MS_U8 u8DemodIndex,MS_U8 *pRegParam);
MS_BOOL MDrv_Demod_null_GetParam(MS_U8 u8DemodIndex,DEMOD_MS_FE_CARRIER_PARAM* pParam);
MS_BOOL MDrv_Demod_null_Restart(MS_U8 u8DemodIndex,DEMOD_MS_FE_CARRIER_PARAM* pParam);
MS_BOOL MDrv_Demod_null_SetMode(MS_U8 u8DemodIndex,Demod_Mode* pMode);
MS_BOOL MDrv_Demod_null_SetOutoutPath(MS_U8 u8DemodIndex,DEMOD_INTERFACE_MODE path);
DEMOD_INTERFACE_MODE MDrv_Demod_null_GetOutoutPath(MS_U8 u8DemodIndex);
MS_BOOL MDrv_Demod_null_I2C_ByPass(MS_U8 u8DemodIndex,MS_BOOL bOn);

MS_BOOL MDrv_Demod_null_SetCurrentDemodType(MS_U8 u8DemodIndex, MS_U8 type);
MS_U8 MDrv_Demod_null_GetCurrentDemodType(MS_U8 u8DemodIndex);
MS_BOOL MDrv_Demod_null_GetPlpBitMap(MS_U8 u8DemodIndex, MS_U8* u8PlpBitMap);
MS_BOOL MDrv_Demod_null_GetPlpGroupID(MS_U8 u8DemodIndex, MS_U8 u8PlpID, MS_U8* u8GroupID);
MS_BOOL MDrv_Demod_null_SetPlpGroupID(MS_U8 u8DemodIndex, MS_U8 u8PlpID, MS_U8 u8GroupID);

MS_BOOL MDrv_Demod_null_SetTsSerial(MS_U8 u8DemodIndex,MS_BOOL bSerial);
MS_BOOL MDrv_Demod_null_TPSGetLock(MS_U8 u8DemodIndex,MS_BOOL *pbLock);
MS_BOOL MDrv_Demod_null_MPEGGetLock(MS_U8 u8DemodIndex,MS_BOOL *pbLock);
MS_BOOL MDrv_Demod_null_GetRollOff(MS_U8 u8DemodIndex,MS_U8 *pRollOff);
MS_BOOL MDrv_Demod_null_GetRFOffset(MS_U8 u8DemodIndex,MS_S16 *ps16RFOff);
MS_BOOL MDrv_Demod_null_BlindScan_Start(MS_U8 u8DemodIndex,MS_U16 u16StartFreq,MS_U16 u16EndFreq);
MS_BOOL MDrv_Demod_null_BlindScan_NextFreq(MS_U8 u8DemodIndex,MS_BOOL* bBlindScanEnd);
MS_BOOL MDrv_Demod_null_BlindScan_WaitCurFreqFinished(MS_U8 u8DemodIndex,MS_U8* u8Progress,MS_U8 *u8FindNum);
MS_BOOL MDrv_Demod_null_BlindScan_Cancel(MS_U8 u8DemodIndex);
MS_BOOL MDrv_Demod_null_BlindScan_End(MS_U8 u8DemodIndex);
MS_BOOL MDrv_Demod_null_BlindScan_GetChannel(MS_U8 u8DemodIndex, MS_U16 u16ReadStart,MS_U16* u16TPNum,DEMOD_MS_FE_CARRIER_PARAM *pTable);
MS_BOOL MDrv_Demod_null_BlindScan_GetCurrentFreq(MS_U8 u8DemodIndex, MS_U32 *u32CurrentFeq);
MS_BOOL MDrv_Demod_null_DiSEqC_SetTone(MS_U8 u8DemodIndex, MS_BOOL bTone1);
MS_BOOL MDrv_Demod_null_DiSEqC_SetLNBOut(MS_U8 u8DemodIndex, MS_BOOL bLow);
MS_BOOL MDrv_Demod_null_DiSEqC_GetLNBOut(MS_U8 u8DemodIndex, MS_BOOL* bLNBOutLow);
MS_BOOL MDrv_Demod_null_DiSEqC_Set22kOnOff(MS_U8 u8DemodIndex, MS_BOOL b22kOn);
MS_BOOL MDrv_Demod_null_DiSEqC_Get22kOnOff(MS_U8 u8DemodIndex, MS_BOOL* b22kOn);
MS_BOOL MDrv_Demod_null_DiSEqC_SendCmd(MS_U8 u8DemodIndex, MS_U8* pCmd,MS_U8 u8CmdSize);



#endif // #define __DRV_DEMOD_NULL_H__
