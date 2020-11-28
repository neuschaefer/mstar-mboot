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
//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   apiJPEG.h
/// @brief  JPEG API
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _API_JPEG_OJPD_H_
#define _API_JPEG_OJPD_H_

#ifdef __cplusplus
extern "C" {
#endif


void msAPI_JPEG_get_APP0_info_OJPD( MS_U8 *unit,MS_U16 *x, MS_U16 *y );

JPEG_Result MApi_JPEG_Init_OJPD(JPEG_InitParam *pInitParam);
JPEG_Result MApi_JPEG_DecodeHdr_OJPD(void);
JPEG_Result MApi_JPEG_Decode_OJPD(void);
void MApi_JPEG_Exit_OJPD(void);
JPEG_ErrCode MApi_JPEG_GetErrorCode_OJPD(void);
JPEG_Event MApi_JPEG_GetJPDEventFlag_OJPD(void);
void MApi_JPEG_SetJPDEventFlag_OJPD(JPEG_Event eEvtVal);
void MApi_JPEG_Rst_OJPD(void);
void MApi_JPEG_PowerOn_OJPD(void);
void MApi_JPEG_PowerOff_OJPD(void);
MS_U16 MApi_JPEG_GetCurVidx_OJPD(void);
MS_BOOL MApi_JPEG_IsProgressive_OJPD(void);
MS_BOOL MApi_JPEG_ThumbnailFound_OJPD(void);
MS_U16 MApi_JPEG_GetWidth_OJPD(void);
MS_U16 MApi_JPEG_GetHeight_OJPD(void);
MS_U16 MApi_JPEG_GetOriginalWidth_OJPD(void);
MS_U16 MApi_JPEG_GetOriginalHeight_OJPD(void);
MS_U16 MApi_JPEG_GetNonAlignmentWidth_OJPD(void);
MS_U16 MApi_JPEG_GetNonAlignmentHeight_OJPD(void);
MS_U16 MApi_JPEG_GetAlignedPitch_OJPD(void);
MS_U16 MApi_JPEG_GetAlignedPitch_H_OJPD(void);
MS_U16 MApi_JPEG_GetAlignedWidth_OJPD(void);
MS_U16 MApi_JPEG_GetAlignedHeight_OJPD(void);
MS_U8 MApi_JPEG_GetScaleDownFactor_OJPD(void);
void MApi_JPEG_SetMaxDecodeResolution_OJPD(MS_U16 u16Width, MS_U16 u16Height);
void MApi_JPEG_SetProMaxDecodeResolution_OJPD(MS_U16 u16ProWidth, MS_U16 u16ProHeight);
void MApi_JPEG_SetMRBufferValid_OJPD(JPEG_BuffLoadType u8MRBuffType);
void MApi_JPEG_UpdateReadInfo_OJPD(MS_U32 u32DataRead, MS_BOOL bEOFflag);
void MApi_JPEG_ProcessEOF_OJPD(JPEG_BuffLoadType u8MRBuffType);
void MApi_JPEG_SetErrCode_OJPD(JPEG_ErrCode ErrStatus);
void MApi_JPEG_SetDbgLevel_OJPD(MS_U8 u8DbgLevel);
MS_U8 MApi_JPEG_GetDbgLevel_OJPD(void);
void MApi_JPEG_GetInfo_OJPD(JPEG_Info *pJPEG_Info);
void MApi_JPEG_GetStatus_OJPD(JPEG_Status *pJPEG_Status);
JPEG_Result MApi_JPEG_GetLibVer_OJPD(const MSIF_Version **ppVersion);
JPEG_Result MApi_JPEG_HdlVidxChk_OJPD(void);
JPEG_Result MApi_JPEG_GetBuffLoadType_OJPD(JPEG_BuffLoadType *pBuffLoadType);
JPEG_Result MApi_JPEG_EnableISR_OJPD(JPEG_IsrFuncCb IsrCb);
JPEG_Result MApi_JPEG_DisableISR_OJPD(void);
JPEG_DecodeStatus MApi_JPEG_WaitDone_OJPD(void);
JPEG_Result MApi_JPEG_GetEXIFDateTime_OJPD(JPEG_EXIF_DateTime *DateTime);
JPEG_Result MApi_JPEG_GetEXIFOrientation_OJPD(JPEG_EXIF_Orientation *eOrientation);
#if SUPPORT_EXIF_EXTRA_INFO
JPEG_Result MApi_JPEG_GetEXIFManufacturer_OJPD(MS_U8 *pu8Manufacturer, MS_U8 u8size);
JPEG_Result MApi_JPEG_GetEXIFModel_OJPD(MS_U8 *pu8Model, MS_U8 u8size);
JPEG_Result MApi_JPEG_GetEXIFFlash_OJPD(MS_U16 *pu16Flash);
JPEG_Result MApi_JPEG_GetEXIFISOSpeedRatings_OJPD(MS_U32 *pu32ISOSpeedRatings);
JPEG_Result MApi_JPEG_GetEXIFShutterSpeedValue_OJPD(JPEG_RATIONAL *pShutterSpeedValue);
JPEG_Result MApi_JPEG_GetEXIFApertureValue_OJPD(JPEG_RATIONAL *pApertureValue);
JPEG_Result MApi_JPEG_GetEXIFExposureBiasValue_OJPD(JPEG_RATIONAL *pExposureBiasValue);
JPEG_Result MApi_JPEG_GetEXIFFocalLength_OJPD(JPEG_RATIONAL *pFocalLength);
JPEG_Result MApi_JPEG_GetEXIFImageWidth_OJPD(MS_U32 *pu32ImageWidth);
JPEG_Result MApi_JPEG_GetEXIFImageHeight_OJPD(MS_U32 *pu32ImageHeight);
JPEG_Result MApi_JPEG_GetEXIFExposureTime_OJPD(JPEG_RATIONAL *pExposureTime);
JPEG_Result MApi_JPEG_GetEXIFFNumber_OJPD(JPEG_RATIONAL *pFNumber);
#endif
JPEG_Result MApi_JPEG_GetControl_OJPD(EN_JPEG_GET_CTRL_ID eGetID, MS_U32 *param, MS_U32 u32Size);

MS_PHYADDR MApi_JPEG_GetFreeMemory_OJPD(MS_U32 size);
MS_U32 MApi_JPEG_GetDataOffset_OJPD(void);
MS_U32 MApi_JPEG_GetSOFOffset_OJPD(void);
void MApi_JPEG_SetNJPDInstance_OJPD(MS_U8 JPDNum);
JPEG_Result MApi_JPEG_SupportCMYK_OJPD(MS_BOOL bEnable);
JPEG_Result MApi_JPEG_SupportRGB_OJPD(MS_BOOL bEnable);
void MApi_JPEG_SetMHEG5_OJPD(MS_BOOL bEnable);

#if SUPPORT_MPO_FORMAT
//For MPO
MS_BOOL MApi_JPEG_IsMPOFormat_OJPD(void);
MS_BOOL MApi_JPEG_GetMPOIndex_OJPD(JPEG_MPO_INDEX_INFO **ppMPOIndex);
MS_BOOL MApi_JPEG_GetMPOAttr_OJPD(MS_U32 image_no, JPEG_MPO_ATTRIBUTE_INFO **ppMPOAttr);
void MApi_JPEG_DumpMPO_OJPD(void);
MS_BOOL MApi_JPEG_SetMPOBuffer_OJPD(MS_U32 read_offset, MS_U32 output_start);
void MApi_JPEG_SetMPOMaxDecodeResolution_OJPD(MS_U16 u16Width, MS_U16 u16Height);
void MApi_JPEG_SetMPOProMaxDecodeResolution_OJPD(MS_U16 u16ProWidth, MS_U16 u16ProHeight);
#endif
void MApi_JPEG_SetVerificationMode_OJPD(NJPEG_VerificationMode VerificationMode);
NJPEG_VerificationMode MApi_JPEG_GetVerificationMode_OJPD(void);
void MApi_NJPD_Debug_OJPD(void);
void MApi_JPEG_DisableAddressConvert_OJPD(void);



#ifdef __cplusplus
}
#endif

//------------------------------------------------------------------------------
#endif // _API_JPEG_OJPD_H_
//------------------------------------------------------------------------------
