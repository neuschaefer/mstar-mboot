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

#ifndef _APIJPEG_PRIV_H_
#define _APIJPEG_PRIV_H_

////////////////////////////////////////////////////////////////////////////////
/// @file apiJPEG.h
/// @author MStar Semiconductor Inc.
/// @brief JPEG control driver
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"
#include "apiJPEG.h"

#define SUPPORT_NJPD_NUM_MAX     2

typedef void (*IOCTL_JPEG_ENABLE_OJPD)(MS_BOOL);
typedef JPEG_Result (*IOCTL_JPEG_INIT_USING_OJPD)(JPEG_InitParam*);
typedef void (*IOCTL_JPEG_GET_APP0_INFO)(MS_U8*, MS_U16*, MS_U16*);
typedef JPEG_Result (*IOCTL_JPEG_INIT)(JPEG_InitParam*);
typedef JPEG_Result (*IOCTL_JPEG_DECODE_HDR)(void);
typedef JPEG_Result (*IOCTL_JPEG_DECODE)(void);
typedef void (*IOCTL_JPEG_EXIT)(void);
typedef JPEG_ErrCode (*IOCTL_JPEG_GET_ERROR_CODE)(void);
typedef JPEG_Event (*IOCTL_JPEG_GET_JPEG_EVENT_FLAG)(void);
typedef void (*IOCTL_JPEG_SET_JPEG_EVENT_FLAG)(JPEG_Event);
typedef void (*IOCTL_JPEG_RST)(void);
typedef void (*IOCTL_JPEG_POWER_ON)(void);
typedef void (*IOCTL_JPEG_POWER_OFF)(void);
typedef MS_U16 (*IOCTL_JPEG_GET_CUR_VIDX)(void);
typedef MS_BOOL (*IOCTL_JPEG_IS_PROGRESSIVE)(void);
typedef MS_BOOL (*IOCTL_JPEG_THUMBNAIL_FOUND)(void);
typedef MS_U16 (*IOCTL_JPEG_GET_WIDTH)(void);
typedef MS_U16 (*IOCTL_JPEG_GET_HEIGHT)(void);
typedef MS_U16 (*IOCTL_JPEG_GET_ORIGINAL_WIDTH)(void);
typedef MS_U16 (*IOCTL_JPEG_GET_ORIGINAL_HEIGHT)(void);
typedef MS_U16 (*IOCTL_JPEG_GET_NONALIGNMENT_WIDTH)(void);
typedef MS_U16 (*IOCTL_JPEG_GET_NONALIGNMENT_HEIGHT)(void);
typedef MS_U16 (*IOCTL_JPEG_GET_ALIGNED_PITCH)(void);
typedef MS_U16 (*IOCTL_JPEG_GET_ALIGNED_PITCH_H)(void);
typedef MS_U16 (*IOCTL_JPEG_GET_ALIGNED_WIDTH)(void);
typedef MS_U16 (*IOCTL_JPEG_GET_ALIGNED_HEIGHT)(void);
typedef MS_U8 (*IOCTL_JPEG_GET_SCALE_DOWN_FACTOR)(void);
typedef void (*IOCTL_JPEG_SET_MAX_DECODE_RESOLUTION)(MS_U16, MS_U16);
typedef void (*IOCTL_JPEG_SET_PRO_MAX_DECODE_RESOLUTION)(MS_U16, MS_U16);
typedef void (*IOCTL_JPEG_SET_MRBUFFER_VALID)(JPEG_BuffLoadType);
typedef void (*IOCTL_JPEG_UPDATE_READ_INFO)(MS_U32, MS_BOOL);
typedef void (*IOCTL_JPEG_PROCESS_EOF)(JPEG_BuffLoadType);
typedef void (*IOCTL_JPEG_SET_ERROR_CODE)(JPEG_ErrCode);
typedef void (*IOCTL_JPEG_SET_DBG_LEVEL)(MS_U8);
typedef MS_U8 (*IOCTL_JPEG_GET_DBG_LEVEL)(void);
typedef void (*IOCTL_JPEG_GET_INFO)(JPEG_Info*);
typedef void (*IOCTL_JPEG_GET_STATUS)(JPEG_Status*);
typedef JPEG_Result (*IOCTL_JPEG_GET_LIB_VER)(const MSIF_Version **);
typedef JPEG_Result (*IOCTL_JPEG_HDL_VIDX_CHK)(void);
typedef JPEG_Result (*IOCTL_JPEG_GET_BUFF_LOAD_TYPE)(JPEG_BuffLoadType *);
typedef JPEG_Result (*IOCTL_JPEG_ENABLE_ISR)(JPEG_IsrFuncCb);
typedef JPEG_Result (*IOCTL_JPEG_DISABLE_ISR)(void);
typedef JPEG_DecodeStatus (*IOCTL_JPEG_WAIT_DONE)(void);
typedef JPEG_Result (*IOCTL_JPEG_GET_EXIF_DATETIME)(JPEG_EXIF_DateTime*);
typedef JPEG_Result (*IOCTL_JPEG_GET_EXIF_ORIENTATION)(JPEG_EXIF_Orientation*);
typedef JPEG_Result (*IOCTL_JPEG_GET_EXIF_MANUFACTURER)(MS_U8*, MS_U8);
typedef JPEG_Result (*IOCTL_JPEG_GET_EXIF_MODEL)(MS_U8*, MS_U8);
typedef JPEG_Result (*IOCTL_JPEG_GET_EXIF_FLASH)(MS_U16*);
typedef JPEG_Result (*IOCTL_JPEG_GET_EXIF_ISO_SPEED_RATINGS)(MS_U32*);
typedef JPEG_Result (*IOCTL_JPEG_GET_EXIF_SHUTTER_SPEED_VALUE)(JPEG_RATIONAL*);
typedef JPEG_Result (*IOCTL_JPEG_GET_EXIF_APERTURE_VALUE)(JPEG_RATIONAL*);
typedef JPEG_Result (*IOCTL_JPEG_GET_EXIF_EXPOSURE_BIAS_VALUE)(JPEG_RATIONAL*);
typedef JPEG_Result (*IOCTL_JPEG_GET_EXIF_FOCAL_LENGTH)(JPEG_RATIONAL*);
typedef JPEG_Result (*IOCTL_JPEG_GET_EXIF_IMAGE_WIDTH)(MS_U32*);
typedef JPEG_Result (*IOCTL_JPEG_GET_EXIF_IMAGE_HEIGHT)(MS_U32*);
typedef JPEG_Result (*IOCTL_JPEG_GET_EXIF_EXPOSURE_TIME)(JPEG_RATIONAL*);
typedef JPEG_Result (*IOCTL_JPEG_GET_EXIF_FNUMBER)(JPEG_RATIONAL*);
typedef MS_PHYADDR (*IOCTL_JPEG_GET_FREE_MEMORY)(MS_U32);
typedef MS_U32 (*IOCTL_JPEG_GET_DATA_OFFSET)(void);
typedef MS_U32 (*IOCTL_JPEG_GET_SOF_OFFSET)(void);
typedef void (*IOCTL_JPEG_SET_NJPD_INSTANCE)(MS_U8);
typedef JPEG_Result (*IOCTL_JPEG_SUPPORT_CMYK)(MS_BOOL);
typedef JPEG_Result (*IOCTL_JPEG_SUPPORT_RGB)(MS_BOOL);
typedef void (*IOCTL_JPEG_SET_MHEG5)(MS_BOOL);
typedef MS_BOOL (*IOCTL_JPEG_IS_MPO_FORMAT)(void);
typedef MS_BOOL (*IOCTL_JPEG_GET_MPO_INDEX)(JPEG_MPO_INDEX_INFO **);
typedef MS_BOOL (*IOCTL_JPEG_GET_MPO_ATTR)(MS_U32, JPEG_MPO_ATTRIBUTE_INFO **);
typedef void (*IOCTL_JPEG_DUMP_MPO)(void);
typedef MS_BOOL (*IOCTL_JPEG_SET_MPO_BUFFER)(MS_U32, MS_U32);
typedef void (*IOCTL_JPEG_SET_MPO_MAX_DECODE_RESOLUTION)(MS_U16, MS_U16);
typedef void (*IOCTL_JPEG_SET_MPO_PRO_MAX_DECODE_RESOLUTION)(MS_U16, MS_U16);
typedef void (*IOCTL_JPEG_SET_VERIFICATION_MODE)(NJPEG_VerificationMode);
typedef NJPEG_VerificationMode (*IOCTL_JPEG_GET_VERIFICATION_MODE)(void);
typedef void (*IOCTL_JPEG_DEBUG)(void);
typedef JPEG_Result (*IOCTL_JPEG_GET_CONTROL)(EN_JPEG_GET_CTRL_ID, MS_U32 *, MS_U32);

typedef struct _JPEG_RESOURCE_PRIVATE
{
    MS_U8 u8DecoderInUse[SUPPORT_NJPD_NUM_MAX];
}JPEG_RESOURCE_PRIVATE;

typedef struct _JPEG_INSTANCE_PRIVATE
{
    // instance variable
    MS_U8                                Index_of_decoder;

    IOCTL_JPEG_ENABLE_OJPD                          fpJPEGEnableOJPD;
    IOCTL_JPEG_INIT_USING_OJPD                      fpJPEGInit_UsingOJPD;
    IOCTL_JPEG_GET_APP0_INFO                        fpJPEGget_APP0_info;
    IOCTL_JPEG_INIT                                 fpJPEGInit;
    IOCTL_JPEG_DECODE_HDR                           fpJPEGDecodeHdr;
    IOCTL_JPEG_DECODE                               fpJPEGDecode;
    IOCTL_JPEG_EXIT                                 fpJPEGExit;
    IOCTL_JPEG_GET_ERROR_CODE                       fpJPEGGetErrorCode;
    IOCTL_JPEG_GET_JPEG_EVENT_FLAG                  fpJPEGGetJPDEventFlag;
    IOCTL_JPEG_SET_JPEG_EVENT_FLAG                  fpJPEGSetJPDEventFlag;
    IOCTL_JPEG_RST                                  fpJPEGRst;
    IOCTL_JPEG_POWER_ON                             fpJPEGPowerOn;
    IOCTL_JPEG_POWER_OFF                            fpJPEGPowerOff;
    IOCTL_JPEG_GET_CUR_VIDX                         fpJPEGGetCurVidx;
    IOCTL_JPEG_IS_PROGRESSIVE                       fpJPEGIsProgressive;
    IOCTL_JPEG_THUMBNAIL_FOUND                      fpJPEGThumbnailFound;
    IOCTL_JPEG_GET_WIDTH                            fpJPEGGetWidth;
    IOCTL_JPEG_GET_HEIGHT                           fpJPEGGetHeight;
    IOCTL_JPEG_GET_ORIGINAL_WIDTH                   fpJPEGGetOriginalWidth;
    IOCTL_JPEG_GET_ORIGINAL_HEIGHT                  fpJPEGGetOriginalHeight;
    IOCTL_JPEG_GET_NONALIGNMENT_WIDTH               fpJPEGGetNonAlignmentWidth;
    IOCTL_JPEG_GET_NONALIGNMENT_HEIGHT              fpJPEGGetNonAlignmentHeight;
    IOCTL_JPEG_GET_ALIGNED_PITCH                    fpJPEGGetAlignedPitch;
    IOCTL_JPEG_GET_ALIGNED_PITCH_H                  fpJPEGGetAlignedPitch_H;
    IOCTL_JPEG_GET_ALIGNED_WIDTH                    fpJPEGGetAlignedWidth;
    IOCTL_JPEG_GET_ALIGNED_HEIGHT                   fpJPEGGetAlignedHeight;
    IOCTL_JPEG_GET_SCALE_DOWN_FACTOR                fpJPEGGetScaleDownFactor;
    IOCTL_JPEG_SET_MAX_DECODE_RESOLUTION            fpJPEGSetMaxDecodeResolution;
    IOCTL_JPEG_SET_PRO_MAX_DECODE_RESOLUTION        fpJPEGSetProMaxDecodeResolution;
    IOCTL_JPEG_SET_MRBUFFER_VALID                   fpJPEGSetMRBufferValid;
    IOCTL_JPEG_UPDATE_READ_INFO                     fpJPEGUpdateReadInfo;
    IOCTL_JPEG_PROCESS_EOF                          fpJPEGProcessEOF;
    IOCTL_JPEG_SET_ERROR_CODE                       fpJPEGSetErrCode;
    IOCTL_JPEG_SET_DBG_LEVEL                        fpJPEGSetDbgLevel;
    IOCTL_JPEG_GET_DBG_LEVEL                        fpJPEGGetDbgLevel;
    IOCTL_JPEG_GET_INFO                             fpJPEGGetInfo;
    IOCTL_JPEG_GET_STATUS                           fpJPEGGetStatus;
    IOCTL_JPEG_GET_LIB_VER                          fpJPEGGetLibVer;
    IOCTL_JPEG_HDL_VIDX_CHK                         fpJPEGHdlVidxChk;
    IOCTL_JPEG_GET_BUFF_LOAD_TYPE                   fpJPEGGetBuffLoadType;
    IOCTL_JPEG_ENABLE_ISR                           fpJPEGEnableISR;
    IOCTL_JPEG_DISABLE_ISR                          fpJPEGDisableISR;
    IOCTL_JPEG_WAIT_DONE                            fpJPEGWaitDone;
    IOCTL_JPEG_GET_EXIF_DATETIME                    fpJPEGGetEXIFDateTime;
    IOCTL_JPEG_GET_EXIF_ORIENTATION                 fpJPEGGetEXIFOrientation;
    IOCTL_JPEG_GET_EXIF_MANUFACTURER                fpJPEGGetEXIFManufacturer;
    IOCTL_JPEG_GET_EXIF_MODEL                       fpJPEGGetEXIFModel;
    IOCTL_JPEG_GET_EXIF_FLASH                       fpJPEGGetEXIFFlash;
    IOCTL_JPEG_GET_EXIF_ISO_SPEED_RATINGS           fpJPEGGetEXIFISOSpeedRatings;
    IOCTL_JPEG_GET_EXIF_SHUTTER_SPEED_VALUE         fpJPEGGetEXIFShutterSpeedValue;
    IOCTL_JPEG_GET_EXIF_APERTURE_VALUE              fpJPEGGetEXIFApertureValue;
    IOCTL_JPEG_GET_EXIF_EXPOSURE_BIAS_VALUE         fpJPEGGetEXIFExposureBiasValue;
    IOCTL_JPEG_GET_EXIF_FOCAL_LENGTH                fpJPEGGetEXIFFocalLength;
    IOCTL_JPEG_GET_EXIF_IMAGE_WIDTH                 fpJPEGGetEXIFImageWidth;
    IOCTL_JPEG_GET_EXIF_IMAGE_HEIGHT                fpJPEGGetEXIFImageHeight;
    IOCTL_JPEG_GET_EXIF_EXPOSURE_TIME               fpJPEGGetEXIFExposureTime;
    IOCTL_JPEG_GET_EXIF_FNUMBER                     fpJEPGGetEXIFFNumber;
    IOCTL_JPEG_GET_FREE_MEMORY                      fpJPEGGetFreeMemory;
    IOCTL_JPEG_GET_DATA_OFFSET                      fpJPEGGetDataOffset;
    IOCTL_JPEG_GET_SOF_OFFSET                       fpJPEGGetSOFOffset;
    IOCTL_JPEG_SET_NJPD_INSTANCE                    fpJPEGSetNJPDInstance;
    IOCTL_JPEG_SUPPORT_CMYK                         fpJPEGSupportCMYK;
    IOCTL_JPEG_SUPPORT_RGB                          fpJPEGSupportRGB;
    IOCTL_JPEG_SET_MHEG5                            fpJPEGSetMHEG5;
    IOCTL_JPEG_IS_MPO_FORMAT                        fpJPEGIsMPOFormat;
    IOCTL_JPEG_GET_MPO_INDEX                        fpJPEGGetMPOIndex;
    IOCTL_JPEG_GET_MPO_ATTR                         fpJPEGGetMPOAttr;
    IOCTL_JPEG_DUMP_MPO                             fpJPEGDumpMPO;
    IOCTL_JPEG_SET_MPO_BUFFER                       fpJPEGSetMPOBuffer;
    IOCTL_JPEG_SET_MPO_MAX_DECODE_RESOLUTION        fpJPEGSetMPOMaxDecodeResolution;
    IOCTL_JPEG_SET_MPO_PRO_MAX_DECODE_RESOLUTION    fpJPEGSetMPOProMaxDecodeResolution;
    IOCTL_JPEG_SET_VERIFICATION_MODE                fpJPEGSetVerificationMode;
    IOCTL_JPEG_GET_VERIFICATION_MODE                fpJPEGGetVerificationMode;
    IOCTL_JPEG_DEBUG                                fpJPEGDebug;
    IOCTL_JPEG_GET_CONTROL                          fpJPEGGetControl;
}JPEG_INSTANCE_PRIVATE;

void JPEGRegisterToUtopia(void);
MS_U32 JPEGOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
MS_U32 JPEGClose(void* pInstance);
MS_U32 JPEGIoctl(void* pInstance, MS_U32 u32Cmd, void* pArgs);


void _MApi_JPEG_EnableOJPD(MS_BOOL bOnOff);
JPEG_Result _MApi_JPEG_Init_UsingOJPD(JPEG_InitParam *pInitParam);

void _msAPI_JPEG_get_APP0_info( MS_U8 *unit,MS_U16 *x, MS_U16 *y );

JPEG_Result _MApi_JPEG_Init(JPEG_InitParam *pInitParam);
JPEG_Result _MApi_JPEG_DecodeHdr(void);
JPEG_Result _MApi_JPEG_Decode(void);
void _MApi_JPEG_Exit(void);
JPEG_ErrCode _MApi_JPEG_GetErrorCode(void);
JPEG_Event _MApi_JPEG_GetJPDEventFlag(void);
void _MApi_JPEG_SetJPDEventFlag(JPEG_Event eEvtVal);
void _MApi_JPEG_Rst(void);
void _MApi_JPEG_PowerOn(void);
void _MApi_JPEG_PowerOff(void);
MS_U16 _MApi_JPEG_GetCurVidx(void);
MS_BOOL _MApi_JPEG_IsProgressive(void);
MS_BOOL _MApi_JPEG_ThumbnailFound(void);
MS_U16 _MApi_JPEG_GetWidth(void);
MS_U16 _MApi_JPEG_GetHeight(void);
MS_U16 _MApi_JPEG_GetOriginalWidth(void);
MS_U16 _MApi_JPEG_GetOriginalHeight(void);
MS_U16 _MApi_JPEG_GetNonAlignmentWidth(void);
MS_U16 _MApi_JPEG_GetNonAlignmentHeight(void);
MS_U16 _MApi_JPEG_GetAlignedPitch(void);
MS_U16 _MApi_JPEG_GetAlignedPitch_H(void);
MS_U16 _MApi_JPEG_GetAlignedWidth(void);
MS_U16 _MApi_JPEG_GetAlignedHeight(void);
MS_U8 _MApi_JPEG_GetScaleDownFactor(void);
void _MApi_JPEG_SetMaxDecodeResolution(MS_U16 u16Width, MS_U16 u16Height);
void _MApi_JPEG_SetProMaxDecodeResolution(MS_U16 u16ProWidth, MS_U16 u16ProHeight);
void _MApi_JPEG_SetMRBufferValid(JPEG_BuffLoadType u8MRBuffType);
void _MApi_JPEG_UpdateReadInfo(MS_U32 u32DataRead, MS_BOOL bEOFflag);
void _MApi_JPEG_ProcessEOF(JPEG_BuffLoadType u8MRBuffType);
void _MApi_JPEG_SetErrCode(JPEG_ErrCode ErrStatus);
void _MApi_JPEG_SetDbgLevel(MS_U8 u8DbgLevel);
MS_U8 _MApi_JPEG_GetDbgLevel(void);
void _MApi_JPEG_GetInfo(JPEG_Info *pJPEG_Info);
void _MApi_JPEG_GetStatus(JPEG_Status *pJPEG_Status);
JPEG_Result _MApi_JPEG_GetLibVer(const MSIF_Version **ppVersion);
JPEG_Result _MApi_JPEG_HdlVidxChk(void);
JPEG_Result _MApi_JPEG_GetBuffLoadType(JPEG_BuffLoadType *pBuffLoadType);
JPEG_Result _MApi_JPEG_EnableISR(JPEG_IsrFuncCb IsrCb);
JPEG_Result _MApi_JPEG_DisableISR(void);
JPEG_DecodeStatus _MApi_JPEG_WaitDone(void);
JPEG_Result _MApi_JPEG_GetEXIFDateTime(JPEG_EXIF_DateTime *DateTime);
JPEG_Result _MApi_JPEG_GetEXIFOrientation(JPEG_EXIF_Orientation *eOrientation);
#if SUPPORT_EXIF_EXTRA_INFO
JPEG_Result _MApi_JPEG_GetEXIFManufacturer(MS_U8 *pu8Manufacturer, MS_U8 u8size);
JPEG_Result _MApi_JPEG_GetEXIFModel(MS_U8 *pu8Model, MS_U8 u8size);
JPEG_Result _MApi_JPEG_GetEXIFFlash(MS_U16 *pu16Flash);
JPEG_Result _MApi_JPEG_GetEXIFISOSpeedRatings(MS_U32 *pu32ISOSpeedRatings);
JPEG_Result _MApi_JPEG_GetEXIFShutterSpeedValue(JPEG_RATIONAL *pShutterSpeedValue);
JPEG_Result _MApi_JPEG_GetEXIFApertureValue(JPEG_RATIONAL *pApertureValue);
JPEG_Result _MApi_JPEG_GetEXIFExposureBiasValue(JPEG_RATIONAL *pExposureBiasValue);
JPEG_Result _MApi_JPEG_GetEXIFFocalLength(JPEG_RATIONAL *pFocalLength);
JPEG_Result _MApi_JPEG_GetEXIFImageWidth(MS_U32 *pu32ImageWidth);
JPEG_Result _MApi_JPEG_GetEXIFImageHeight(MS_U32 *pu32ImageHeight);
JPEG_Result _MApi_JPEG_GetEXIFExposureTime(JPEG_RATIONAL *pExposureTime);
JPEG_Result _MApi_JPEG_GetEXIFFNumber(JPEG_RATIONAL *pFNumber);
#endif
MS_PHYADDR _MApi_JPEG_GetFreeMemory(MS_U32 size);
MS_U32 _MApi_JPEG_GetDataOffset(void);
MS_U32 _MApi_JPEG_GetSOFOffset(void);
void _MApi_JPEG_SetNJPDInstance(MS_U8 JPDNum);
JPEG_Result _MApi_JPEG_SupportCMYK(MS_BOOL bEnable);
JPEG_Result _MApi_JPEG_SupportRGB(MS_BOOL bEnable);
void _MApi_JPEG_SetMHEG5(MS_BOOL bEnable);

#if SUPPORT_MPO_FORMAT
//For MPO
MS_BOOL _MApi_JPEG_IsMPOFormat(void);
MS_BOOL _MApi_JPEG_GetMPOIndex(JPEG_MPO_INDEX_INFO **ppMPOIndex);
MS_BOOL _MApi_JPEG_GetMPOAttr(MS_U32 image_no, JPEG_MPO_ATTRIBUTE_INFO **ppMPOAttr);
void _MApi_JPEG_DumpMPO(void);
MS_BOOL _MApi_JPEG_SetMPOBuffer(MS_U32 read_offset, MS_U32 output_start);
void _MApi_JPEG_SetMPOMaxDecodeResolution(MS_U16 u16Width, MS_U16 u16Height);
void _MApi_JPEG_SetMPOProMaxDecodeResolution(MS_U16 u16ProWidth, MS_U16 u16ProHeight);
#endif
void _MApi_JPEG_SetVerificationMode(NJPEG_VerificationMode VerificationMode);
NJPEG_VerificationMode _MApi_JPEG_GetVerificationMode(void);
void _MApi_NJPD_Debug(void);
JPEG_Result _MApi_JPEG_GetControl(EN_JPEG_GET_CTRL_ID eGetID, MS_U32 *param, MS_U32 u32size);

#ifdef __cplusplus
}
#endif
#endif // _APIJPEG_PRIV_H_





