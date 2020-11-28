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
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvAESDMA.h
/// @brief  AESDMA Driver Interface
/// @author MStar Semiconductor,Inc.
///
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVAESDMA_H_
#define _DRVAESDMA_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"

//--------------------------------------------------------------------------------------------------
//  Define
//--------------------------------------------------------------------------------------------------
#define AES_ENABLE                   0x01
#define TDES_ENABLE                  0x10
#define WORD_MASK                    0x0000000F

#define MSIF_AESDMA_LIB_CODE                     {'D','M','A','_'}    //Lib code
#define MSIF_AESDMA_LIBVER                       {'0','3'}            //LIB version
#define MSIF_AESDMA_BUILDNUM                     {'0','3'}            //Build Number
#define MSIF_AESDMA_CHANGELIST                   {'0','0','3','3','1','6','3','7'} //P4 ChangeList Number

#define AESDMA_DRV_VERSION                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_AESDMA_LIB_CODE,                  /* IP__                                             */  \
    MSIF_AESDMA_LIBVER,                          /* 0.0 ~ Z.Z                                        */  \
    MSIF_AESDMA_BUILDNUM,                          /* 00 ~ 99                                          */  \
    MSIF_AESDMA_CHANGELIST,  /* CL#                                              */  \
    MSIF_OS

/// AESDMA Cipher Mode
typedef enum
{
    E_DRVAESDMA_CIPHER_ECB = 0,
    E_DRVAESDMA_CIPHER_CTR,
    E_DRVAESDMA_CIPHER_CBC,
    E_DRVAESDMA_CIPHER_DES_ECB,
    E_DRVAESDMA_CIPHER_DES_CTR,
    E_DRVAESDMA_CIPHER_DES_CBC,
    E_DRVAESDMA_CIPHER_TDES_ECB,
    E_DRVAESDMA_CIPHER_TDES_CTR,
    E_DRVAESDMA_CIPHER_TDES_CBC,
    E_DRVAESDMA_CIPHER_CTS_CBC,
    E_DRVAESDMA_CIPHER_CTS_ECB,
    E_DRVAESDMA_CIPHER_DES_CTS_CBC,
    E_DRVAESDMA_CIPHER_DES_CTS_ECB,
    E_DRVAESDMA_CIPHER_TDES_CTS_CBC,
    E_DRVAESDMA_CIPHER_TDES_CTS_ECB,
} DrvAESDMA_CipherMode;

/// SHA Mode
typedef enum
{
    E_DRVAESDMA_SHA1 = 0,
    E_DRVAESDMA_SHA256,
} DrvAESDMA_SHAMode;

/// AESDMA notification event
typedef enum //_DrvAESDMA_Event
{
    E_DRVAESDMA_EVENT_DATA_INIT         = 0x00000000,
    /// DMA Done
    E_DRVAESDMA_EVENT_DMA_DONE          = 0x00010000,
    /// DMA Pause
    E_DRVAESDMA_EVENT_DMA_PAUSE         = 0x00020000,

} DrvAESDMA_Event;

typedef enum //_DrvTSP_DbgLevel
{
    E_DRVAESDMA_DBG_Release = 0,
    E_DRVAESDMA_DBG_L1, // display error msg
    E_DRVAESDMA_DBG_L2, // display error msg and enter while(1)
} DrvAESDMA_DbgLevel;

//--------------------------------------------------------------------------------------------------
//  Driver Capability
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//  Local variable
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//  Type and Structure
//--------------------------------------------------------------------------------------------------
/// AESDMA DDI return value
typedef MS_U32                         DRVAESDMA_RESULT;

/// @name DRVAESDMA_RESULT
/// @ref DRVAESDMA_RESULT
/// return value
/// @{
#define DRVAESDMA_OK                   0x00000000
#define DRVAESDMA_FAIL                 0x00000001
#define DRVAESDMA_INVALID_PARAM        0x00000002
#define DRVAESDMA_FUNC_ERROR           0x00000003
#define DRVAESDMA_MIU_ADDR_ERROR       0x00000004

/// @}

#define AESDMA_DMA_DONE                     0x00010000
#define AESDMA_DMA_PAUSE                    0x00020000
#define AESDMA_STATES_GROUP                 (AESDMA_DMA_DONE  | \
                                             AESDMA_DMA_PAUSE  )

/// AESDMA notification function
typedef void (*P_DrvAESDMA_EvtCallback)(DrvAESDMA_Event eEvent);

//--------------------------------------------------------------------------------------------------
//  Function Prototype
//--------------------------------------------------------------------------------------------------
DRVAESDMA_RESULT MDrv_AESDMA_Init(MS_U32 u32miu0addr , MS_U32 u32miu1addr , MS_U32 u32miunum);
DRVAESDMA_RESULT MDrv_AESDMA_SelEng(DrvAESDMA_CipherMode eMode, MS_BOOL bDescrypt);
DRVAESDMA_RESULT MDrv_AESDMA_SetKey(MS_U32 *pCipherKey);
DRVAESDMA_RESULT MDrv_AESDMA_SetIV(MS_U32 *pInitVector);
DRVAESDMA_RESULT MDrv_AESDMA_SetPS(MS_U32 u32PTN, MS_U32 u32Mask, MS_BOOL bPSin_Enable, MS_BOOL bPSout_Enable);
DRVAESDMA_RESULT MDrv_AESDMA_PSRelease(void);
DRVAESDMA_RESULT MDrv_AESDMA_SetFileInOut(MS_U32 u32FileinAddr, MS_U32 u32FileInNum, MS_U32 u32FileOutSAddr, MS_U32 u32FileOutEAddr);
DRVAESDMA_RESULT MDrv_AESDMA_Start(MS_BOOL bStart);
DRVAESDMA_RESULT MDrv_AESDMA_Reset(void);
DRVAESDMA_RESULT MDrv_AESDMA_GetStatus(void);
DRVAESDMA_RESULT MDrv_AESDMA_IsFinished(void);
MS_U32 MDrv_AESDMA_GetPSMatchedByteCNT(void);
MS_U32 MDrv_AESDMA_GetPSMatchedPTN(void);
DRVAESDMA_RESULT MDrv_AESDMA_Notify(DrvAESDMA_Event eEvents, P_DrvAESDMA_EvtCallback pfCallback);
DRVAESDMA_RESULT MDrv_AESDMA_SetDbgLevel(DrvAESDMA_DbgLevel DbgLevel);
DRVAESDMA_RESULT MDrv_AESDMA_GetLibVer(const MSIF_Version **ppVersion);
DRVAESDMA_RESULT MDrv_AESDMA_Rand(MS_U32 *u32PABuf, MS_U32 u32Size);
DRVAESDMA_RESULT MDrv_AESDMA_Set_Clk(MS_BOOL benable);
DRVAESDMA_RESULT MDrv_SHA_Calculate(DrvAESDMA_SHAMode eMode, MS_U32 u32PAInBuf, MS_U32 u32Size, MS_U32 u32PAOutBuf);
DRVAESDMA_RESULT MDrv_MOBF_DmaOnly(void);
DRVAESDMA_RESULT MDrv_MOBF_Encrypt(MS_U32 u32Key, MS_BOOL bEnable);
DRVAESDMA_RESULT MDrv_MOBF_Decrypt(MS_U32 u32Key, MS_BOOL bEnable);
DRVAESDMA_RESULT MDrv_MOBF_OneWay(void);

#ifdef __cplusplus
}
#endif


#endif // _DRVAESDMA_H_
