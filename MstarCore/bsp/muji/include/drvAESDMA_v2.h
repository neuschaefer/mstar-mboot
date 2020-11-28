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
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
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

//////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvAESDMA_v2.h
/// @brief  AESDMA Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_AESDMA_V2_H_
#define _DRV_AESDMA_V2_H_

#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
// below for utopia20 structure


typedef enum {
    MDrv_CMD_AESDMA_Init,
	MDrv_CMD_AESDMA_SetIV,
    MDrv_CMD_AESDMA_Reset,
    MDrv_CMD_AESDMA_SetFileInOut,
    MDrv_CMD_AESDMA_SetKey,
    MDrv_CMD_AESDMA_SelEng,
    MDrv_CMD_AESDMA_Start,
    MDrv_CMD_AESDMA_GetStatus,
    MDrv_CMD_AESDMA_IsFinished,
    MDrv_CMD_AESDMA_SetClk,
    MDrv_CMD_AESDMA_SetSecureKey,
    MDrv_CMD_AESDMA_SetPS,
    MDrv_CMD_AESDMA_PSRelease,
    MDrv_CMD_AESDMA_GetPSMatchedByteCNT,
    MDrv_CMD_AESDMA_GetPSMatchedPTN,
    MDrv_CMD_AESDMA_Notify,
    MDrv_CMD_AESDMA_Rand,
    MDrv_CMD_RSA_Calculate,
    MDrv_CMD_RSA_IsFinished,
    MDrv_CMD_RSA_Output,
    MDrv_CMD_SHA_Calculate,
    MDrv_CMD_AESDMA_Memcpy,    
    MDrv_CMD_SHA_CalculateManual,
    MDrv_CMD_AESDMA_PARSER_MASKSCRMB,
    MDrv_CMD_AESDMA_PARSER_SETSCRMBPATTERN,
    MDrv_CMD_AESDMA_PARSER_BYPASSPID,
    MDrv_CMD_AESDMA_PARSER_SETPID,
    MDrv_CMD_AESDMA_PARSER_ENCRYPT,
    MDrv_CMD_AESDMA_PARSER_DECRYPT,
    MDrv_CMD_AESDMA_PARSER_Start,
    MDrv_CMD_AESDMA_PARSER_SETADDEDSCRMBPATTERN,
    MDrv_CMD_AESDMA_PARSER_QUERYPIDCOUNT,
    MDrv_CMD_AESDMA_ENABLE_Two_Key,
    MDrv_CMD_AESDMA_SetOddKey,
    MDrv_CMD_AESDMA_SetOddIV,
	MDrv_CMD_IS_SECRETKEY_IN_NORMAL_BLANK,
	MDrv_CMD_AESDMA_SetKey_Ex,
    MDrv_CMD_AESDMA_SetIV_Ex,
} eAesdmaIoctlOpt;

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------

typedef struct _AESDMA_INIT
{
    MS_U32 u32miu0addr;
    MS_U32 u32miu1addr;
    MS_U32 u32miunum;
}AESDMA_INIT, *PAESDMA_INIT;

typedef struct _AESDMA_FILE_INOUT
{
    MS_U32 u32FileinAddr;
    MS_U32 u32FileInNum;
    MS_U32 u32FileOutSAddr;
    MS_U32 u32FileOutEAddr;
}AESDMA_FILE_INOUT, *PAESDMA_FILE_INOUT;

typedef struct _AESDMA_SEL_ENG
{
    DrvAESDMA_CipherMode eMode;
    MS_BOOL bDescrypt;
}AESDMA_SEL_ENG, *PAESDMA_SEL_ENG;

typedef struct _AESDMA_SET_IV
{
    MS_U32 *pInitVector;
}AESDMA_SET_IV, *PAESDMA_SET_IV;

typedef struct _AESDMA_SET_KEY
{
    MS_U32 *pCipherKey;
}AESDMA_SET_KEY, *PAESDMA_SET_KEY;

typedef struct _AESDMA_SET_KEY_EX
{
    const MS_U8 *pu8Key;
    MS_U32 u32Len;
}AESDMA_SET_KEY_EX, *PAESDMA_SET_KEY_EX;

typedef struct _AESDMA_SET_IV_EX
{
    const MS_U8 *pu8IV;
    MS_U32 u32Len;
}AESDMA_SET_IV_EX, *PAESDMA_SET_IV_EX;


typedef struct _AESDMA_SET_PS
{
    MS_U32 u32PTN;
    MS_U32 u32Mask;
    MS_BOOL bPSin_Enable;
    MS_BOOL bPSout_Enable;
}AESDMA_SET_PS, *PAESDMA_SET_PS;

typedef struct _AESDMA_START
{
    MS_BOOL bStart;
}AESDMA_START, *PAESDMA_START;


typedef struct _AESDMA_NOTIFY
{
    DrvAESDMA_Event eEvents;
    P_DrvAESDMA_EvtCallback pfCallback;
}AESDMA_NOTIFY, *PAESDMA_NOTIFY;

typedef struct _AESDMA_RAND
{
    MS_U32 *u32PABuf;
    MS_U32 u32Size;
}AESDMA_RAND, *PAESDMA_RAND;

typedef struct _RSA_CALCULATE
{
    DrvAESDMA_RSASig *pstSign;
    DrvAESDMA_RSAKey *pstKey;
    DrvAESDMA_RSAMode eMode;
}RSA_CALCULATE, *PRSA_CALCULATE;

typedef struct _RSA_OUTPUT
{
    DrvAESDMA_RSAMode eMode;
    DrvAESDMA_RSAOut *pstRSAOut;
}RSA_OUTPUT, *PRSA_OUTPUT;

typedef struct _SHA_CALCULATE
{
    DrvAESDMA_SHAMode eMode;
    MS_U32 u32PAInBuf;
    MS_U32 u32Size;
    MS_U32 u32PAOutBuf;
}SHA_CALCULATE, *PSHA_CALCULATE;

typedef struct _SHA_CALCULATE_MANUAL
{
    DrvAESDMA_HASHCFG stCfg;
    DrvAESDMA_HASH_STAGE eStage;
    MS_U32 u32DoneBytes;
    MS_U8 *pu8SetIV;
}SHA_CALCULATE_MANUAL, *PSHA_CALCULATE_MANUAL;

typedef struct _AESDMA_PARSER_CONFIGURATIONS
{
    DrvAESDMA_ScrmbPattern eScrmbPattern;
    DrvAESDMA_ParserMode   eParserMode;
    DrvAESDMA_ScrmbPattern eAddedScrmbPattern;
}AESDMA_PARSER_CONFIGURATIONS, *PAESDMA_PARSER_CONFIGURATIONS;

typedef struct _AESDMA_PARSER_PID_CONFIGURATIONS
{
    //Don't care PidIndex and Pid if BypassPid is true;
    MS_BOOL bBypassPid;
    MS_U8   u8PidIndex;
    MS_U16  u16Pid;
}AESDMA_PARSER_PID_CONFIGURATIONS, *PAESDMA_PARSER_PID_CONFIGURATIONS;


//-------------------------------------------------------------------------------------------------
// Extern Global Variabls
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Extern Functions
//-------------------------------------------------------------------------------------------------

//////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#endif // _DRV_AESDMA_V2_H_

