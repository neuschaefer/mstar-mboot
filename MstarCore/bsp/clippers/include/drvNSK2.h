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
////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVNSK2_H_
#define _DRVNSK2_H_

////////////////////////////////////////////////////////////////////////////////
/// @file drvNSK2.h
/// @author MStar Semiconductor Inc.
/// @brief
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"
//#include "ndstypes.h"
////////////////////////////////////////////////////////////////////////////////
// Define & data type
////////////////////////////////////////////////////////////////////////////////


typedef void (*NSK2_IntNotify)(MS_U32 reason, MS_U32 acpuError);


////////////////////////////////////////////////////////////////////////////////
// Extern Function
////////////////////////////////////////////////////////////////////////////////
MS_U32 MDrv_NSK2_Init(void);
MS_U32 MDrv_NSK2_OTPCheck(MS_U8 *pSecret,  MS_U32 CheckSum,
                          MS_U32 KeyValid, MS_U32 SecMode  );

MS_U32 MDrv_NSK2_ColdReset(void);

MS_U32 MDrv_NSK2_Compare(MS_U32 StartAddr, MS_U32 CompareLens, MS_U32 CompareSim,
                         MS_U32 Mask, MS_U32 ExpectResult);
MS_U32 MDrv_NSK2_CompareMem(MS_U32 reserved, MS_U32 StartAddr, MS_U32 CompareLens,
                            MS_U32 CompareSim, MS_U32 ExpectResult, void *pGolden);

MS_U32 MDrv_NSK2_WriteMem(MS_U32 reserved, MS_U32 StartAddr, MS_U32 WriteLens, void *pWriteData);
MS_U32 MDrv_NSK2_WriteSFR(MS_U32 StartAddr, MS_U32 Data);

MS_U32 MDrv_NSK2_CompareKTvalid(MS_U32 reserved_1, MS_U32 reserved_2,
                                MS_U8 KTE_Mode, MS_U16 PID, MS_U8 SCB, MS_U8 Expected);

MS_U32 MDrv_NSK2_CompareKTE(MS_U32 reserved_1, MS_U32 reserved_2, void *pLabel);

MS_U32 MDrv_NSK2_CompareOut(MS_U32 reserved_1, MS_U32 reserved_2, MS_U32 HighDWord, MS_U32 LowDWord);

MS_U32 MDrv_NSK2_WriteESA(MS_U16 PID, MS_U8 ESASelect, MS_U8 ESASubSelect);


MS_U32 MDrv_NSK2_WriteTransportKey(MS_U16 PID, MS_U8 SCB, MS_U8 ForceSCB, void *pLabel);
MS_U32 MDrv_NSK2_SetRNG(MS_U32 reserved_1, MS_U16 RNG_Value);

MS_U32 MDrv_NSK2_BasicInitializationComplete(void);
MS_U32 MDrv_NSK2_DriveKteAck(void);

MS_U32 MDrv_NSK2_WriteM2MKey(void *pIV, MS_U8 SubAlgo);
MS_U32 MDrv_NSK2_WriteSCPUKey(void);

MS_U32 MDrv_NSK2_CompareIRQ(MS_U32 reserved_1, MS_U32 reserved_2, MS_U32 reserved_3);

MS_U32 MDrv_NSK2_MDrv_NSK2_WriteESA(MS_U16 PID, MS_U8 ESASelect, MS_U8 ESASubSelect);
MS_U32 MDrv_NSK2_WriteTransportKey(MS_U16 PID, MS_U8 SCB, MS_U8 ForceSCB, void *pLabel);
MS_U32 MDrv_NSK2_NSKBasicInitializationComplete(void);
MS_U32 MDrv_NSK2_TestIncomplete(void);

MS_U32 MDrv_NSK2_FillJTagPswd(void);
MS_U32 MDrv_NSK2_CheckPubOTPConfig(void *pCheck);
MS_U32 MDrv_NSK2_AssociatePID(MS_U32 PrimaryPID, MS_U32 SecondaryPID, MS_U32 CCmode);

MS_U32 MDrv_NSK2_UnlockOTPCtrl(void);

MS_U32 MDrv_NSK2_ReadData(MS_U32 addr_offset, MS_U32 data_size, MS_U8 *data);
MS_U32 MDrv_NSK2_WriteData(MS_U32 addr_offset, MS_U32 data_size, MS_U8 *data);

MS_U32 MDrv_NSK2_ReadData8(MS_U32 addr_offset, MS_U32 data_size, MS_U8 *data);
MS_U32 MDrv_NSK2_WriteData8(MS_U32 addr_offset, MS_U32 data_size, MS_U8 *data);
MS_U32 MDrv_NSK2_ReadData32(MS_U32 addr_offset, MS_U32 data_size, MS_U32 *data);
MS_U32 MDrv_NSK2_WriteData32(MS_U32 addr_offset, MS_U32 data_size, MS_U32 *data);

MS_U32 MDrv_NSK2_SetIntNotify(NSK2_IntNotify IntNotify);

MS_U32 MDrv_NSK2_ExcuteCmd(MS_U32 command, MS_U32 control,
                           MS_U32 register_offset, MS_U32 data_size,
                           const MS_U8    *data);

MS_U32 MDrv_NSK2_SetPidNo(MS_U8 u8PidNo);
MS_U32 MDrv_NSK2_SetSecondaryPidNo(MS_U8 u8PidNo);
MS_U32 MDrv_NSK2_GetPid_PidNo(MS_U16 Pid);
MS_U32 MDrv_NSK2_SetPid_PidNo(MS_U16 Pid, MS_U8 u8PidNo, MS_U8 SrcType);
MS_U32 MDrv_NSK2_GetMaxXConn(void);
MS_U32 MDrv_NSK2_ReadSwitch(MS_U32 SCB, MS_U32 pid_no);
MS_U32 MDrv_NSK2_ReadKTEValid(void);
void   MDrv_NSK2_AllTSPPidFilter(void);
void   MDrv_NSK2_ChangePidFilter(MS_U32 pid_no, MS_U32 Data);
void   MDrv_NSK2_EnableKTEValidPatch(void);
MS_U32 MDrv_NSK2_GetOTPValue(MS_U32 u32Offset);
MS_U32 MDrv_NSK2_CMChannelNum(void);
void   MDrv_NSK2_DumpPktView(MS_U32 u32Eng , MS_U32 u32FltId, MS_BOOL reset);
#if 0
void MDrv_NSK2_BurstLen(MS_U32 u32PVREng, MS_U32 u32BurstMode);
void MDrv_NSK2_CCDrop(MS_U32 u32FltId, MS_BOOL bEnable);
void MDrv_NSK2_SPD_BypassEnable(MS_BOOL bByPassEn);
void MDrv_NSK2_SPD_Reset(MS_U32 u32FltId);
#endif
MS_U32 MDrv_NSK2_GetOTPFieldValue(MS_U8 u8Tag, MS_U8 *pLength, MS_U32 *pRetValue);
void MDrv_NSK2_SetDbgLevel(MS_U32 u32Level);
void MDrv_NSK2_SetPollingCnt(MS_U32 u32Cnt);

#ifdef __cplusplus
}
#endif
#endif//_DRVNSK2_H_

