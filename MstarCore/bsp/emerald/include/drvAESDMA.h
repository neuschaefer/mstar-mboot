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
