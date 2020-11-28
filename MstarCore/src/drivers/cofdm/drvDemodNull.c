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
// Copyright (c) 2006-2008 MStar Semiconductor, Inc.
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
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
/// @file drvDemodNull.c
/// @brief Demod default Nll function
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////




#ifndef _DEMODNULL_C_
#define _DEMODNULL_C_

#include "MsCommon.h"
#include "Board.h"
#include "drvDemod.h"
#include "drvDemodNull.h"



MS_BOOL MDrv_Demod_null_init(MS_U8 u8DemodIndex)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_open(MS_U8 u8DemodIndex)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}


MS_BOOL MDrv_Demod_null_Close(MS_U8 u8DemodIndex)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}


MS_BOOL MDrv_Demod_null_Reset(MS_U8 u8DemodIndex)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}


MS_BOOL MDrv_Demod_null_TsOut(MS_U8 u8DemodIndex,MS_BOOL bEnable)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_PowerOnOff(MS_U8 u8DemodIndex,MS_BOOL bPowerOn)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}


MS_BOOL MDrv_Demod_null_SetBW(MS_U8 u8DemodIndex,MS_U32 u32BW)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}


MS_BOOL MDrv_Demod_null_GetBW(MS_U8 u8DemodIndex,MS_U32 *pu32BW)
{  
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_GetLock(MS_U8 u8DemodIndex,EN_LOCK_STATUS *peLockStatus)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_GetSNR(MS_U8 u8DemodIndex,MS_U32 *pu32SNR)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}


MS_BOOL MDrv_Demod_null_GetBER(MS_U8 u8DemodIndex,float *pfBER)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_GetPWR(MS_U8 u8DemodIndex,MS_S32 *ps32Signal)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_Config(MS_U8 u8DemodIndex,MS_U8 *pRegParam)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}


MS_BOOL MDrv_Demod_null_GetParam(MS_U8 u8DemodIndex,DEMOD_MS_FE_CARRIER_PARAM* pParam)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_Restart(MS_U8 u8DemodIndex,DEMOD_MS_FE_CARRIER_PARAM* pParam)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_SetMode(MS_U8 u8DemodIndex,Demod_Mode* pMode)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}


MS_BOOL MDrv_Demod_null_SetOutoutPath(MS_U8 u8DemodIndex,DEMOD_INTERFACE_MODE path)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

DEMOD_INTERFACE_MODE MDrv_Demod_null_GetOutoutPath(MS_U8 u8DemodIndex)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return DEMOD_INTERFACE_SERIAL;
}

MS_BOOL MDrv_Demod_null_I2C_ByPass(MS_U8 u8DemodIndex,MS_BOOL bOn)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}


MS_BOOL MDrv_Demod_null_SetCurrentDemodType(MS_U8 u8DemodIndex, MS_U8 type)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_U8 MDrv_Demod_null_GetCurrentDemodType(MS_U8 u8DemodIndex)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_GetPlpBitMap(MS_U8 u8DemodIndex, MS_U8* u8PlpBitMap)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_GetPlpGroupID(MS_U8 u8DemodIndex, MS_U8 u8PlpID, MS_U8* u8GroupID)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;

}

MS_BOOL MDrv_Demod_null_SetPlpGroupID(MS_U8 u8DemodIndex, MS_U8 u8PlpID, MS_U8 u8GroupID)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;

}

MS_BOOL MDrv_Demod_null_SetTsSerial(MS_U8 u8DemodIndex,MS_BOOL bSerial)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_TPSGetLock(MS_U8 u8DemodIndex,MS_BOOL *pbLock)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_MPEGGetLock(MS_U8 u8DemodIndex,MS_BOOL *pbLock)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_GetRollOff(MS_U8 u8DemodIndex,MS_U8 *pRollOff)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_GetRFOffset(MS_U8 u8DemodIndex,MS_S16 *ps16RFOff)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_BlindScan_Start(MS_U8 u8DemodIndex,MS_U16 u16StartFreq,MS_U16 u16EndFreq)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_BlindScan_NextFreq(MS_U8 u8DemodIndex,MS_BOOL* bBlindScanEnd)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_BlindScan_WaitCurFreqFinished(MS_U8 u8DemodIndex,MS_U8* u8Progress,MS_U8 *u8FindNum)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_BlindScan_Cancel(MS_U8 u8DemodIndex)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_BlindScan_End(MS_U8 u8DemodIndex)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_BlindScan_GetChannel(MS_U8 u8DemodIndex, MS_U16 u16ReadStart,MS_U16* u16TPNum,DEMOD_MS_FE_CARRIER_PARAM *pTable)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_BlindScan_GetCurrentFreq(MS_U8 u8DemodIndex, MS_U32 *u32CurrentFeq)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_DiSEqC_SetTone(MS_U8 u8DemodIndex, MS_BOOL bTone1)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_DiSEqC_SetLNBOut(MS_U8 u8DemodIndex, MS_BOOL bLow)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_DiSEqC_GetLNBOut(MS_U8 u8DemodIndex, MS_BOOL* bLNBOutLow)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_DiSEqC_Set22kOnOff(MS_U8 u8DemodIndex, MS_BOOL b22kOn)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_DiSEqC_Get22kOnOff(MS_U8 u8DemodIndex, MS_BOOL* b22kOn)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_DiSEqC_SendCmd(MS_U8 u8DemodIndex, MS_U8* pCmd,MS_U8 u8CmdSize)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_Extension_Function(MS_U8 u8DemodIndex, DEMOD_EXT_FUNCTION_TYPE fuction_type, void *data)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

MS_BOOL MDrv_Demod_null_CheckExist(MS_U8 u8DemodIndex)
{
    printf("%s, %d \n", __FUNCTION__,__LINE__);
    return TRUE;
}

DRV_DEMOD_TABLE_TYPE GET_DEMOD_ENTRY_NODE(DEMOD_NULL) DDI_DRV_TABLE_ENTRY(demodtab) = 
{  
     .name                         = "DEMOD_NULL",
     .data                         = DEMOD_NULL,        
     .init                         = MDrv_Demod_null_init,
     .GetLock                      = MDrv_Demod_null_GetLock,
     .GetSNR                       = MDrv_Demod_null_GetSNR,
     .GetBER                       = MDrv_Demod_null_GetBER,
     .GetPWR                       = MDrv_Demod_null_GetPWR,
     .GetParam                     = MDrv_Demod_null_GetParam,
     .Restart                      = MDrv_Demod_null_Restart,
     .I2CByPass                    = MDrv_Demod_null_I2C_ByPass,
     .CheckExist                   = MDrv_Demod_null_CheckExist,
     .Extension_Function           = MDrv_Demod_null_Extension_Function,
#if MS_DVBT2_INUSE
     .SetCurrentDemodType          = MDrv_Demod_null_SetCurrentDemodType,
     .GetCurrentDemodType          = MDrv_Demod_null_GetCurrentDemodType,
     .GetPlpBitMap                 = MDrv_Demod_null_GetPlpBitMap,
     .GetPlpGroupID                = MDrv_Demod_null_GetPlpGroupID,
     .SetPlpGroupID                = MDrv_Demod_null_SetPlpGroupID,
#endif
#if MS_DVBS_INUSE
     .BlindScanStart               = MDrv_Demod_null_BlindScan_Start,
     .BlindScanNextFreq            = MDrv_Demod_null_BlindScan_NextFreq,
     .BlindScanWaitCurFreqFinished = MDrv_Demod_null_BlindScan_WaitCurFreqFinished,
     .BlindScanCancel              = MDrv_Demod_null_BlindScan_Cancel,
     .BlindScanEnd                 = MDrv_Demod_null_BlindScan_End,
     .BlindScanGetChannel          = MDrv_Demod_null_BlindScan_GetChannel,
     .BlindScanGetCurrentFreq      = MDrv_Demod_null_BlindScan_GetCurrentFreq,
     .DiSEqCSetTone                = MDrv_Demod_null_DiSEqC_SetTone,
     .DiSEqCSetLNBOut              = MDrv_Demod_null_DiSEqC_SetLNBOut,
     .DiSEqCGetLNBOut              = MDrv_Demod_null_DiSEqC_GetLNBOut,
     .DiSEqCSet22kOnOff            = MDrv_Demod_null_DiSEqC_Set22kOnOff,
     .DiSEqCGet22kOnOff            = MDrv_Demod_null_DiSEqC_Get22kOnOff,
     .DiSEqC_SendCmd               = MDrv_Demod_null_DiSEqC_SendCmd
#endif
};

#endif

