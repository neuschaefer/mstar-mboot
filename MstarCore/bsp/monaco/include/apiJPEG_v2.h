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
/// @file   apiJPEG_v2.h
/// @brief  JPEG Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _API_JPEG_V2_H_
#define _API_JPEG_V2_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"
//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
// below for utopia20 structure

typedef enum {
    MApi_CMD_JPEG_EnableOJPD,
    MApi_CMD_JPEG_Init_UsingOJPD,
    MApi_CMD_JPEG_get_APP0_info,
    MApi_CMD_JPEG_Init,
    MApi_CMD_JPEG_DecodeHdr,
    MApi_CMD_JPEG_Decode,
    MApi_CMD_JPEG_Exit,
    MApi_CMD_JPEG_GetErrorCode,
    MApi_CMD_JPEG_GetJPDEventFlag,
    MApi_CMD_JPEG_SetJPDEventFlag,
    MApi_CMD_JPEG_Rst,
    MApi_CMD_JPEG_PowerOn,
    MApi_CMD_JPEG_PowerOff,
    MApi_CMD_JPEG_GetCurVidx,
    MApi_CMD_JPEG_IsProgressive,
    MApi_CMD_JPEG_ThumbnailFound,
    MApi_CMD_JPEG_GetWidth,
    MApi_CMD_JPEG_GetHeight,
    MApi_CMD_JPEG_GetOriginalWidth,
    MApi_CMD_JPEG_GetOriginalHeight,
    MApi_CMD_JPEG_GetNonAlignmentWidth,
    MApi_CMD_JPEG_GetNonAlignmentHeight,
    MApi_CMD_JPEG_GetAlignedPitch,
    MApi_CMD_JPEG_GetAlignedPitch_H,
    MApi_CMD_JPEG_GetAlignedWidth,
    MApi_CMD_JPEG_GetAlignedHeight,
    MApi_CMD_JPEG_GetScaleDownFactor,
    MApi_CMD_JPEG_SetMaxDecodeResolution,
    MApi_CMD_JPEG_SetProMaxDecodeResolution,
    MApi_CMD_JPEG_SetMRBufferValid,
    MApi_CMD_JPEG_UpdateReadInfo,
    MApi_CMD_JPEG_ProcessEOF,
    MApi_CMD_JPEG_SetErrCode,
    MApi_CMD_JPEG_SetDbgLevel,
    MApi_CMD_JPEG_GetDbgLevel,
    MApi_CMD_JPEG_GetInfo,
    MApi_CMD_JPEG_GetStatus,
    MApi_CMD_JPEG_GetLibVer,
    MApi_CMD_JPEG_HdlVidxChk,
    MApi_CMD_JPEG_GetBuffLoadType,
    MApi_CMD_JPEG_EnableISR,
    MApi_CMD_JPEG_DisableISR,
    MApi_CMD_JPEG_WaitDone,
    MApi_CMD_JPEG_GetEXIFDateTime,
    MApi_CMD_JPEG_GetEXIFOrientation,
    MApi_CMD_JPEG_GetEXIFManufacturer,
    MApi_CMD_JPEG_GetEXIFModel,
    MApi_CMD_JPEG_GetEXIFFlash,
    MApi_CMD_JPEG_GetEXIFISOSpeedRatings,
    MApi_CMD_JPEG_GetEXIFShutterSpeedValue,
    MApi_CMD_JPEG_GetEXIFApertureValue,
    MApi_CMD_JPEG_GetEXIFExposureBiasValue,
    MApi_CMD_JPEG_GetEXIFFocalLength,
    MApi_CMD_JPEG_GetEXIFImageWidth,
    MApi_CMD_JPEG_GetEXIFImageHeight,
    MApi_CMD_JPEG_GetEXIFExposureTime,
    MApi_CMD_JPEG_GetEXIFFNumber,
    MApi_CMD_JPEG_GetFreeMemory,
    MApi_CMD_JPEG_GetDataOffset,
    MApi_CMD_JPEG_GetSOFOffset,
    MApi_CMD_JPEG_SetNJPDInstance,
    MApi_CMD_JPEG_SupportCMYK,
    MApi_CMD_JPEG_SupportRGB,
    MApi_CMD_JPEG_SetMHEG5,
    MApi_CMD_JPEG_IsMPOFormat,
    MApi_CMD_JPEG_GetMPOIndex,
    MApi_CMD_JPEG_GetMPOAttr,
    MApi_CMD_JPEG_DumpMPO,
    MApi_CMD_JPEG_SetMPOBuffer,
    MApi_CMD_JPEG_SetMPOMaxDecodeResolution,
    MApi_CMD_JPEG_SetMPOProMaxDecodeResolution,
    MApi_CMD_JPEG_SetVerificationMode,
    MApi_CMD_JPEG_GetVerificationMode,
    MApi_CMD_JPEG_Debug,
    MApi_CMD_JPEG_GetControl
} E_JPEG_V2_IOCTL_CMD;


// For MApi_JPEG_EnableOJPD(), MApi_JPEG_IsProgressive(), MApi_JPEG_ThumbnailFound(),
// For MApi_JPEG_SetMHEG5(), MApi_JPEG_IsMPOFormat()
typedef struct _JPEG_BOOL_PARAM
{
    MS_BOOL bValue;
}JPEG_BOOL_PARAM, *PJPEG_BOOL_PARAM;

typedef struct _JPEG_INIT_PARAM
{
    JPEG_InitParam *pInitParam;
    JPEG_Result retVal;
}JPEG_INIT_PARAM, *PJPEG_INIT_PARAM;

typedef struct _JPEG_GETAPP0INFO_PARAM
{
    MS_U8 *unit;
    MS_U16 *x;
    MS_U16 *y;
}JPEG_GETAPP0INFO_PARAM, *PJPEG_GETAPP0INFO_PARAM;

// For MApi_JPEG_DecodeHdr(), MApi_JPEG_Decode()
// For MApi_JPEG_HdlVidxChk(), MApi_JPEG_DisableISR()
typedef struct _JPEG_RESULT_PARAM
{
    JPEG_Result retVal;
}JPEG_RESULT_PARAM, *PJPEG_RESULT_PARAM;

typedef struct _JPEG_GETERRORCODE_PARAM
{
    JPEG_ErrCode ErrCode;
}JPEG_GETERRORCODE_PARAM, *PJPEG_GETERRORCODE_PARAM;

// For MApi_JPEG_GetJPDEventFlag() and MApi_JPEG_SetJPDEventFlag()
typedef struct _JPEG_JPEGEVENT_PARAM
{
    JPEG_Event eEvtVal;
}JPEG_JPEGEVENT_PARAM, *PJPEG_JPEGEVENT_PARAM;

// For MApi_JPEG_GetCurVidx()
// For MApi_JPEG_GetWidth(), MApi_JPEG_GetHeight()
// For MApi_JPEG_GetOriginalWidth(), MApi_JPEG_GetOriginalHeight()
// For MApi_JPEG_GetNonAlignmentWidth(), MApi_JPEG_GetNonAlignmentHeight()
// For MApi_JPEG_GetAlignedPitch(), MApi_JPEG_GetAlignedPitch_H()
// For MApi_JPEG_GetAlignedWidth(), MApi_JPEG_GetAlignedHeight()
typedef struct _JPEG_U16_PARAM
{
    MS_U16 u16Value;
}JPEG_U16_PARAM, *PJPEG_U16_PARAM;

// For MApi_JPEG_GetScaleDownFactor(), MApi_JPEG_SetDbgLevel(), MApi_JPEG_GetDbgLevel()
// For MApi_JPEG_SetNJPDInstance()
typedef struct _JPEG_U8_PARAM
{
    MS_U8 u8Value;
}JPEG_U8_PARAM, *PJPEG_U8_PARAM;


// For MApi_JPEG_SetMaxDecodeResolution(), MApi_JPEG_SetProMaxDecodeResolution()
// For MApi_JPEG_SetMPOMaxDecodeResolution(), MApi_JPEG_SetMPOProMaxDecodeResolution()
typedef struct _JPEG_RESOLUTION_PARAM
{
    MS_U16 u16Width;
    MS_U16 u16Height;
}JPEG_RESOLUTION_PARAM, *PJPEG_RESOLUTION_PARAM;

typedef struct _JPEG_SETMBUFFERVALID_PARAM
{
    JPEG_BuffLoadType u8MRBuffType;
}JPEG_SETMBUFFERVALID_PARAM, *PJPEG_SETMBUFFERVALID_PARAM;

typedef struct _JPEG_UPDATEREADINFO_PARAM
{
    MS_U32 u32DataRead;
    MS_BOOL bEOFflag;
}JPEG_UPDATEREADINFO_PARAM, *PJPEG_UPDATEREADINFO_PARAM;

typedef struct _JPEG_PROCESSEOF_PARAM
{
    JPEG_BuffLoadType u8MRBuffType;
}JPEG_PROCESSEOF_PARAM, *PJPEG_PROCESSEOF_PARAM;

typedef struct _JPEG_SETERRORCODE_PARAM
{
    JPEG_ErrCode ErrStatus;
}JPEG_SETERRORCODE_PARAM, *PJPEG_SETERRORCODE_PARAM;

typedef struct _JPEG_GETINFO_PARAM
{
    JPEG_Info *pJPEG_Info;
}JPEG_GETINFO_PARAM, *PJPEG_GETINFO_PARAM;

typedef struct _JPEG_GETSTATUS_PARAM
{
    JPEG_Status *pJPEG_Status;
}JPEG_GETSTATUS_PARAM, *PJPEG_GETSTATUS_PARAM;

typedef struct _JPEG_GETLIBVER_PARAM
{
    const MSIF_Version **ppVersion;
    JPEG_Result retVal;
}JPEG_GETLIBVER_PARAM, *PJPEG_GETLIBVER_PARAM;

typedef struct _JPEG_GETBUFFLOADTYPE_PARAM
{
    JPEG_BuffLoadType *pBuffLoadType;
    JPEG_Result retVal;
}JPEG_GETBUFFLOADTYPE_PARAM, *PJPEG_GETBUFFLOADTYPE_PARAM;

typedef struct _JPEG_ENABLEISR_PARAM
{
    JPEG_IsrFuncCb IsrCb;
    JPEG_Result retVal;
}JPEG_ENABLEISR_PARAM, *PJPEG_ENABLEISR_PARAM;

typedef struct _JPEG_WAITDONE_PARAM
{
    JPEG_DecodeStatus retVal;
}JPEG_WAITDONE_PARAM, *PJPEG_WAITDONE_PARAM;

typedef struct _JPEG_GETEXIFDATETIME_PARAM
{
    JPEG_EXIF_DateTime *DateTime;
    JPEG_Result retVal;
}JPEG_GETEXIFDATETIME_PARAM, *PJPEG_GETEXIFDATETIME_PARAM;

typedef struct _JPEG_GETEXIFORIENTATION_PARAM
{
    JPEG_EXIF_Orientation *eOrientation;
    JPEG_Result retVal;
}JPEG_GETEXIFORIENTATION_PARAM, *PJPEG_GETEXIFORIENTATION_PARAM;

// For MApi_JPEG_GetEXIFManufacturer(), MApi_JPEG_GetEXIFManufacturer()
typedef struct _JPEG_GETEXIFSTRING_PARAM
{
    MS_U8 *pu8String;
    MS_U8 u8size;
    JPEG_Result retVal;
}JPEG_GETEXIFSTRING_PARAM, *PJPEG_GETEXIFSTRING_PARAM;

// For MApi_JPEG_GetEXIFFlash()
typedef struct _JPEG_GETEXIFU16_PARAM
{
    MS_U16 *pu16Value;
    JPEG_Result retVal;
}JPEG_GETEXIFU16_PARAM, *PJPEG_GETEXIFU16_PARAM;

// For MApi_JPEG_GetEXIFISOSpeedRatings()
// For MApi_JPEG_GetEXIFImageWidth(), MApi_JPEG_GetEXIFImageHeight()
typedef struct _JPEG_GETEXIFU32_PARAM
{
    MS_U32 *pu32Value;
    JPEG_Result retVal;
}JPEG_GETEXIFU32_PARAM, *PJPEG_GETEXIFU32_PARAM;

// For MApi_JPEG_GetEXIFShutterSpeedValue(), MApi_JPEG_GetEXIFApertureValue()
// For MApi_JPEG_GetEXIFExposureBiasValue(), MApi_JPEG_GetEXIFFocalLength()
// For MApi_JPEG_GetEXIFExposureTime(), MApi_JPEG_GetEXIFFNumber()
typedef struct _JPEG_GETEXIFRATIONAL_PARAM
{
    JPEG_RATIONAL *pRational;
    JPEG_Result retVal;
}JPEG_GETEXIFRATIONAL_PARAM, *PJPEG_GETEXIFRATIONAL_PARAM;

typedef struct _JPEG_GETFREEMEMORY_PARAM
{
    MS_U32 size;
    MS_PHYADDR addr;
}JPEG_GETFREEMEMORY_PARAM, *PJPEG_GETFREEMEMORY_PARAM;

// For MApi_JPEG_GetDataOffset(), MApi_JPEG_GetSOFOffset()
typedef struct _JPEG_U32_PARAM
{
    MS_U32 u32Value;
}JPEG_U32_PARAM, *PJPEG_U32_PARAM;

// For MApi_JPEG_SupportCMYK(), MApi_JPEG_SupportRGB()
typedef struct _JPEG_SUPPORTCMYK_PARAM
{
    MS_BOOL bEnable;
    JPEG_Result retVal;
}JPEG_SUPPORTCMYK_PARAM, *PJPEG_SUPPORTCMYK_PARAM;

typedef struct _JPEG_GETMPOINDEX_PARAM
{
    JPEG_MPO_INDEX_INFO **ppMPOIndex;
    MS_BOOL bretVal;
}JPEG_GETMPOINDEX_PARAM, *PJPEG_GETMPOINDEX_PARAM;

typedef struct _JPEG_GETMPOATTR_PARAM
{
    MS_U32 image_no;
    JPEG_MPO_ATTRIBUTE_INFO **ppMPOAttr;
    MS_BOOL bretVal;
}JPEG_GETMPOATTR_PARAM, *PJPEG_GETMPOATTR_PARAM;

typedef struct _JPEG_SETMPOBUFFER_PARAM
{
    MS_U32 read_offset;
    MS_U32 output_start;
    MS_BOOL bretVal;
}JPEG_SETMPOBUFFER_PARAM, *PJPEG_SETMPOBUFFER_PARAM;

// For MApi_JPEG_SetVerificationMode(), MApi_JPEG_GetVerificationMode()
typedef struct _JPEG_VERIFICATION_PARAM
{
    NJPEG_VerificationMode VerificationMode;
}JPEG_VERIFICATION_PARAM, *PJPEG_VERIFICATION_PARAM;

typedef struct _JPEG_GET_CTRL_PARAM
{
    EN_JPEG_GET_CTRL_ID eGetID;
    MS_U32 *param;
    MS_U32 u32size;
    JPEG_Result retVal;
}JPEG_GET_CTRL_PARAM, *PJPEG_GET_CTRL_PARAM;

void NJPEG_EXRegisterToUtopia(FUtopiaOpen ModuleType);
MS_U32 JPEG_Open(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
MS_U32 JPEG_Close(void* pInstance);
MS_U32 JPEG_Ioctl(void* pInstance, MS_U32 u32Cmd, void* pArgs);
void JPEG_SetDbgLevel_V2(MS_U8 u8DbgLevel);


#ifdef __cplusplus
}
#endif

#endif // _API_JPEG_V2_H_


