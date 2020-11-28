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
/// @file   drvCIPHER.h
/// @brief  CIPHER Driver Interface
/// @author MStar Semiconductor,Inc.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DRVCIPHER_H__
#define __DRVCIPHER_H__

#include "MsTypes.h"
#include "MsDevice.h"
#include "MsCommon.h"

//--------------------------------------------------------------------------------------------------
//  Define
//--------------------------------------------------------------------------------------------------
#define HASH_TIMEOUT_VALUE      (5000)

typedef enum
{
    CIPHER_DBG_NONE,
    CIPHER_DBG_ERR,
    CIPHER_DBG_WARN,
    CIPHER_DBG_INFO,
}CIPHER_DBGMSG_LEVEL;

#define MSIF_CIPHER_LIB_CODE                     {'D','M','A','_'}    //Lib code
#define MSIF_CIPHER_LIBVER                       {'0','1'}            //LIB version
#define MSIF_CIPHER_BUILDNUM                     {'0','1'}            //Build Number
#define MSIF_CIPHER_CHANGELIST                   {'0','0','8','2','9','9','2','7'} //P4 ChangeList Number

#define CIPHER_DRV_VERSION                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_CIPHER_LIB_CODE,                  /* IP__                                             */  \
    MSIF_CIPHER_LIBVER,                          /* 0.0 ~ Z.Z                                        */  \
    MSIF_CIPHER_BUILDNUM,                          /* 00 ~ 99                                          */  \
    MSIF_CIPHER_CHANGELIST,  /* CL#                                              */  \
    MSIF_OS


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
typedef MS_U32                         DRV_CIPHER_RET;

typedef void (*P_DrvCIPHER_EvtCallback)(MS_U32 u32CmdId, MS_BOOL bSuccess, MS_U32 u32Exception);

typedef enum
{
    E_CIPHER_MAIN_NONE,
    E_CIPHER_MAIN_AES,
    E_CIPHER_MAIN_DES,
    E_CIPHER_MAIN_TDES,
    E_CIPHER_MAIN_M6_S56_CCBC,
    E_CIPHER_MAIN_M6_S56,
    E_CIPHER_MAIN_M6_KE56,
    E_CIPHER_MAIN_RC4,
}CIPHER_MAIN_ALGO;

typedef enum
{
    E_CIPHER_SUB_NONE,
    E_CIPHER_SUB_ECB,
    E_CIPHER_SUB_CBC,
    E_CIPHER_SUB_CTR,
    E_CIPHER_SUB_CBC_MAC,
    E_CIPHER_SUB_CTR_64,
    E_CIPHER_SUB_CMAC_Key,
    E_CIPHER_SUB_CMAC_Algo,
    E_CIPHER_SUB_PCBC_ADD,
    E_CIPHER_SUB_PCBC_XOR,
}CIPHER_SUB_ALGO;

typedef enum
{
    E_CIPHER_RES_NONE,
    E_CIPHER_RES_CLR,
    E_CIPHER_RES_CTS,
    E_CIPHER_RES_SCTE52,
}CIPHER_RES_ALGO;

typedef enum
{
    E_CIPHER_SB_NONE,
    E_CIPHER_SB_CLR,
    E_CIPHER_SB_IV1,
    E_CIPHER_SB_IV2,
}CIPHER_SB_ALGO;

typedef enum
{
    E_CIPHER_KSRC_CPU,
    E_CIPHER_KSRC_KL,
    E_CIPHER_KSRC_OTP ,
}CIPHER_KEY_SRC;


typedef struct
{
    CIPHER_MAIN_ALGO    eMainAlgo;
    CIPHER_SUB_ALGO     eSubAlgo;
    CIPHER_RES_ALGO     eResAlgo;
    CIPHER_SB_ALGO      eSBAlgo;
}DRV_CIPHER_ALGO;

typedef struct
{
    CIPHER_KEY_SRC  eKeySrc;
    MS_U8           u8KeyIdx;
    MS_U8           u8KeyLen;
    MS_U8           *pu8KeyData;
    MS_U8           u8IVLen;
    MS_U8           *pu8IVData;
}DRV_CIPHER_KEY;


typedef enum
{
	E_CIPHER_DRAM = 1,
	E_CIPHER_DQMEM,
	E_CIPHER_IQMEM,
	E_CIPHER_DIRECT,
}CIPHER_MEM_TYPE;


typedef struct
{
    MS_U32 u32Addr;
    MS_U32 u32Size;
	CIPHER_MEM_TYPE    eMemoryType;
}DRV_CIPHER_DATA;

typedef struct
{
    DRV_CIPHER_ALGO stAlgo;
    DRV_CIPHER_KEY  stKey;
    DRV_CIPHER_DATA stInput;
    DRV_CIPHER_DATA stOutput;
    MS_BOOL         bDecrypt;
	MS_U32          u32CAVid;
    P_DrvCIPHER_EvtCallback pfCallback;
}DRV_CIPHER_DMACFG;

typedef enum
{
    E_CIPHER_HASH_ALGO_SHA1,
    E_CIPHER_HASH_ALGO_SHA256 ,
    E_CIPHER_HASH_ALGO_MD5 ,
}CIPHER_HASH_ALGO;

typedef enum
{
    E_CIPHER_HASH_IV_FIPS,
    E_CIPHER_HASH_IV_CMD,
    E_CIPHER_HASH_IV_PRV,
}CIPHER_HASH_IV;

typedef enum
{
    E_CIPHER_HASH_STAGE_FIRST ,
    E_CIPHER_HASH_STAGE_UPDATE ,
    E_CIPHER_HASH_STAGE_LAST ,
}CIPHER_HASH_STAGE;

typedef enum
{
    E_CIPHER_HMAC_IKPAD,
    E_CIPHER_HMAC_OKPAD,
}CIPHER_HMAC_KPAD;

typedef struct
{
    CIPHER_KEY_SRC  eKeySrc;
    MS_U8           u8KeyIdx;
    MS_U8           u8KeyLen;
    MS_U8           *pu8KeyData;
}DRV_CIPHER_HMAC_KEY;

typedef struct
{
    CIPHER_HASH_ALGO        eAlgo;
    DRV_CIPHER_DATA         stInput;
    MS_U8                   *pu8Digest_Buf;
    MS_U32                  u32Digest_Buf_Size;
    MS_U32                  u32CAVid;
    P_DrvCIPHER_EvtCallback pfCallback;
}DRV_CIPHER_HASHCFG;

typedef struct
{
    CIPHER_HASH_ALGO      eAlgo;
    DRV_CIPHER_DATA       stInput;
    MS_U8                 *pu8Digest_Buf;
    MS_U32                u32Digest_Buf_Size;
    MS_U32                u32CAVid;
    MS_U32                u32StartByte;
    MS_U8                 *pu8SetIV;
    CIPHER_HASH_IV        eIVMode;
    CIPHER_HASH_STAGE     eStage;
    CIPHER_HMAC_KPAD      eHMACKPad;
    DRV_CIPHER_HMAC_KEY   stHMACKey;
}DRV_CIPHER_HASHCFG_MANUAL;

typedef struct
{
    CIPHER_HASH_ALGO    eAlgo;
    DRV_CIPHER_DATA     stInput;
    MS_U8               *pu8Digest_Buf;
    MS_U32              u32Digest_Buf_Size;
    MS_U32              u32CAVid;
    DRV_CIPHER_HMAC_KEY stHMACKey;
    P_DrvCIPHER_EvtCallback pfCallback;
}DRV_CIPHER_HMACCFG;

#define DRV_CIPHER_OK                   (0x00000000)
#define DRV_CIPHER_FAIL                 (0x00000001)
#define DRV_CIPHER_BAD_PARAM            (0x00000002)

//Exception Message
#define DRV_CIPHER_EXCEPT_CAVID         (0x00000001)
#define DRV_CIPHER_EXCEPT_DATA          (0x00000002)
#define DRV_CIPHER_EXCEPT_ALGO          (0x00000004)
#define DRV_CIPHER_EXCEPT_DMA_KEY       (0x00000008)
#define DRV_CIPHER_EXCEPT_HMAC_KEY      (0x00000010)


//--------------------------------------------------------------------------------------------------
//  Function Prototype
//--------------------------------------------------------------------------------------------------
DLL_PUBLIC DRV_CIPHER_RET MDrv_CIPHER_Init(void);
DLL_PUBLIC DRV_CIPHER_RET MDrv_CIPHER_Reset(void);

DLL_PUBLIC DRV_CIPHER_RET MDrv_CIPHER_DMACalc(DRV_CIPHER_DMACFG stCfg, MS_U32 *pu32CmdId);
DLL_PUBLIC DRV_CIPHER_RET MDrv_CIPHER_HASH(DRV_CIPHER_HASHCFG stCfg, MS_U32 *pu32CmdId);
DLL_PUBLIC DRV_CIPHER_RET MDrv_CIPHER_HASHManual(DRV_CIPHER_HASHCFG_MANUAL stCfg, MS_U32 *pu32CmdId);
DLL_PUBLIC DRV_CIPHER_RET MDrv_CIPHER_HMAC(DRV_CIPHER_HMACCFG stCfg, MS_U32 *pu32CmdId);

DLL_PUBLIC MS_BOOL MDrv_CIPHER_IsDMADone(MS_U32 u32CmdId, MS_U32 *pu32Exception);
DLL_PUBLIC MS_BOOL MDrv_CIPHER_IsHASHDone(MS_U32 u32CmdId, MS_U32 *pu32Exception);

DLL_PUBLIC DRV_CIPHER_RET MDrv_CIPHER_SetDbgLevel(CIPHER_DBGMSG_LEVEL eDBGMsgLevel);
DLL_PUBLIC DRV_CIPHER_RET MDrv_CIPHER_GetLibVer(const MSIF_Version **ppVersion);

#ifdef ENABLE_BGC
DLL_PUBLIC DRV_CIPHER_RET MDrv_CIPHER_BGC_Enable(MS_U32 u32EngId,MS_U32 u32Algo, MS_U8 *pu8Golden, MS_U32 u32SAddr, MS_U32 u32Size);
DLL_PUBLIC DRV_CIPHER_RET MDrv_CIPHER_BGC_Check(MS_U32 u32EngId, MS_BOOL *bOK);
#endif

//////// Old Interface /////////////////
//--------------------------------------------------------------------------------------------------
//  Function Prototype
//--------------------------------------------------------------------------------------------------
#include "drvAESDMA.h"

#endif
