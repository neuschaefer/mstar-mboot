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

#ifndef _API_JPEG_H_
#define _API_JPEG_H_

#ifdef __cplusplus
extern "C" {
#endif
//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define MSIF_JPEG_LIB_CODE                     {'J','P','E','G'}                    ///<Lib code
#define MSIF_JPEG_LIBVER                       {'0','1'}                            ///<LIB version
#define MSIF_JPEG_BUILDNUM                     {'0','H'}                            ///<Build Number
#define MSIF_JPEG_CHANGELIST                   {'0','0','7','1','8','4','1','5'}    ///<P4 ChangeList Number

//------------------------------------------------------------------------------
/// @brief \b JPEG_API_VERSION : JPEG Version
//------------------------------------------------------------------------------
#define JPEG_API_VERSION                /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_JPEG_LIB_CODE,                 /* IP__                                             */  \
    MSIF_JPEG_LIBVER,                   /* 0.0 ~ Z.Z                                        */  \
    MSIF_JPEG_BUILDNUM,                 /* 00 ~ 99                                          */  \
    MSIF_JPEG_CHANGELIST,               /* CL#                                              */  \
    MSIF_OS

//------------------------------------------------------------------------------
/// @brief \b JPEG_DEFAULT_EXIF_SIZE : The buffer size for thumbnail
//------------------------------------------------------------------------------
#define JPEG_DEFAULT_EXIF_SIZE  (64*1024UL + 128)

#define SUPPORT_MPO_FORMAT          1

#define SUPPORT_EXIF_EXTRA_INFO       true // false


#if SUPPORT_MPO_FORMAT
#define JPEG_MPO_MAX_SUPPORT_IMAGE  4
#endif



#define JPEG_UTOPIA20       (1)

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: JPEG_Result
/// @brief \b Enum \b Description: JPEG decode result
//-----------------------------------------------------------------------------
typedef enum
{
    E_JPEG_FAILED   = 0
  , E_JPEG_OKAY     = 1
  , E_JPEG_DONE     = 2
  , E_JPEG_RETRY    = 3
} JPEG_Result;
//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: JPEG_ErrCode
/// @brief \b Enum \b Description: JPEG error code
//-----------------------------------------------------------------------------
typedef enum
{
    E_JPEG_NO_ERROR                     = 0
  , E_JPEG_BAD_DHT_COUNTS               = -200
  , E_JPEG_BAD_DHT_INDEX                = -201
  , E_JPEG_BAD_DHT_MARKER               = -202
  , E_JPEG_BAD_DQT_MARKER               = -203
  , E_JPEG_BAD_DQT_TABLE                = -204
  , E_JPEG_BAD_PRECISION                = -205
  , E_JPEG_BAD_HEIGHT                   = -206
  , E_JPEG_BAD_WIDTH                    = -207
  , E_JPEG_TOO_MANY_COMPONENTS          = -208
  , E_JPEG_BAD_SOF_LENGTH               = -209
  , E_JPEG_BAD_VARIABLE_MARKER          = -210
  , E_JPEG_BAD_DRI_LENGTH               = -211
  , E_JPEG_BAD_SOS_LENGTH               = -212
  , E_JPEG_BAD_SOS_COMP_ID              = -213
  , E_JPEG_W_EXTRA_BYTES_BEFORE_MARKER  = -214
  , E_JPEG_NO_ARITHMETIC_SUPPORT        = -215
  , E_JPEG_UNEXPECTED_MARKER            = -216
  , E_JPEG_NOT_JPEG                     = -217
  , E_JPEG_UNSUPPORTED_MARKER           = -218
  , E_JPEG_BAD_DQT_LENGTH               = -219
  , E_JPEG_TOO_MANY_BLOCKS              = -221
  , E_JPEG_UNDEFINED_QUANT_TABLE        = -222
  , E_JPEG_UNDEFINED_HUFF_TABLE         = -223
  , E_JPEG_NOT_SINGLE_SCAN              = -224
  , E_JPEG_UNSUPPORTED_COLORSPACE       = -225
  , E_JPEG_UNSUPPORTED_SAMP_FACTORS     = -226
  , E_JPEG_DECODE_ERROR                 = -227
  , E_JPEG_BAD_RESTART_MARKER           = -228
  , E_JPEG_ASSERTION_ERROR              = -229
  , E_JPEG_BAD_SOS_SPECTRAL             = -230
  , E_JPEG_BAD_SOS_SUCCESSIVE           = -231
  , E_JPEG_STREAM_READ                  = -232
  , E_JPEG_NOTENOUGHMEM                 = -233
  , E_JPEG_STOP_DECODE                  = -234 //kevinhuang, add
  , E_JPEG_BAD_APP1_MARKER              = -235
  , E_JPEG_NO_THUMBNAIL                 = -236
  , E_JPEG_UNSUPPORTED_HUFF_DECODE      = -237
  , E_JPEG_READBUFFER_TOOSMALL          = -238
  , E_JPEG_NOT_ENOUGH_HEADER_INFO       = -240
  , E_JPEG_RE_INIT                      = -241
  , E_JPEG_NOT_INIT                     = -242
  , E_JPEG_BAD_APP0_MARKER              = -243
#if SUPPORT_MPO_FORMAT
  , E_JPEG_BAD_APP2_MARKER              = -250
#endif
  , E_JPEG_JPD_DECODE_ERROR             = 0x5566
} JPEG_ErrCode;
//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: JPEG_DecType
/// @brief \b Enum \b Description: JPEG decode type
//-----------------------------------------------------------------------------
typedef enum
{
    E_JPEG_TYPE_MAIN        = 0
  , E_JPEG_TYPE_THUMBNAIL   = 1
  , E_JPEG_TYPE_MJPEG       = 2
}JPEG_DecType;
//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: JPEG_BuffLoadType
/// @brief \b Enum \b Description: JPEG buffer loading mode
//-----------------------------------------------------------------------------
typedef enum
{
    E_JPEG_BUFFER_NONE  = 0
  , E_JPEG_BUFFER_HIGH  = 1
  , E_JPEG_BUFFER_LOW   = 2
} JPEG_BuffLoadType;
//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: JPEG_DbgLevel
/// @brief \b Enum \b Description: JPEG debug mode
//-----------------------------------------------------------------------------
typedef enum
{
    E_JPEG_DEBUG_NONE   = 0x0
  , E_JPEG_DEBUG_API    = 0x01
  , E_JPEG_DEBUG_DRV    = 0x02
  , E_JPEG_DEBUG_HAL    = 0x04
  , E_JPEG_DEBUG_MSG    = 0x07
  , E_JPEG_DEBUG_ERR    = 0x08
  , E_JPEG_DEBUG_ALL    = 0x0F
  , E_JPEG_DEBUG_MJPEG    = 0x10
} JPEG_DbgLevel;
//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: JPEG_Event
/// @brief \b Enum \b Description: JPEG decode event flag
//-----------------------------------------------------------------------------
typedef enum
{
    E_JPEG_EVENT_DEC_NONE       = 0x00
  , E_JPEG_EVENT_DEC_DONE       = 0x01
  , E_JPEG_EVENT_DEC_ECS_ERROR  = 0x02
  , E_JPEG_EVENT_DEC_IS_ERROR   = 0x04
  , E_JPEG_EVENT_DEC_RST_ERROR  = 0x08
  , E_JPEG_EVENT_DEC_MRBL_DONE  = 0x10
  , E_JPEG_EVENT_DEC_MRBH_DONE  = 0x20
  , E_JPEG_EVENT_DEC_MRB_DONE   = 0x30
  , E_JPEG_EVENT_DEC_MWB_FULL   = 0x40
  , E_JPEG_EVENT_DEC_ERROR_MASK = 0x0E
} JPEG_Event;
//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: JPEG_DecodeStatus
/// @brief \b Enum \b Description: JPEG decoder status
//-----------------------------------------------------------------------------
typedef enum
{
    E_JPEG_DEC_DONE             = 0
  , E_JPEG_DEC_FAILED           = 1
  , E_JPEG_DEC_RST_ERROR        = 2
  , E_JPEG_DEC_BITSTREAM_ERROR  = 3
  , E_JPEG_DEC_MRBL_DONE        = 4
  , E_JPEG_DEC_MRBH_DONE        = 5
  , E_JPEG_DEC_DECODING         = 6
} JPEG_DecodeStatus;
//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: JPEG_EXIF_IFD0_Orientation
/// @brief \b Enum \b Description: The orientation of JPEG EXIF
//-----------------------------------------------------------------------------
typedef enum
{
    E_JPEG_EXIF_ORIENT_NOT_FOUND              = 0
  , E_JPEG_EXIF_ORIENT_ROTATE_0               = 1
  , E_JPEG_EXIF_ORIENT_MIRROR_LR              = 2
  , E_JPEG_EXIF_ORIENT_ROTATE_180             = 3
  , E_JPEG_EXIF_ORIENT_MIRROR_TB              = 4
  , E_JPEG_EXIF_ORIENT_ROTATE_90_MIRROR_LR    = 5
  , E_JPEG_EXIF_ORIENT_ROTATE_90              = 6
  , E_JPEG_EXIF_ORIENT_ROTATE_90_MIRROR_TB    = 7
  , E_JPEG_EXIF_ORIENT_ROTATE_270             = 8
  , E_JPEG_EXIF_ORIENT_RESERVED               = 9
} JPEG_EXIF_Orientation;

typedef enum
{
    E_JPEG_GET_EXIF_MANUFACTURER            = 0
  , E_JPEG_GET_EXIF_MODEL                   = 1
  , E_JPEG_GET_EXIF_FLASH                   = 2
  , E_JPEG_GET_EXIF_ISO_SPEED_RATINGS       = 3
  , E_JPEG_GET_EXIF_SHUTTER_SPEED_VALUE     = 4
  , E_JPEG_GET_EXIF_APERTURE_VALUE          = 5
  , E_JPEG_GET_EXIF_EXPOSURE_BIAS_VALUE     = 6
  , E_JPEG_GET_EXIF_FOCAL_LENGTH            = 7
  , E_JPEG_GET_EXIF_IMAGE_WIDTH             = 8
  , E_JPEG_GET_EXIF_IMAGE_HEIGHT            = 9
  , E_JPEG_GET_EXIF_EXPOSURE_TIME           = 10
  , E_JPEG_GET_EXIF_F_NUMBER                = 11
  , E_JPEG_GET_EXIF_EXPOSURE_PROGRAM        = 12
} EN_JPEG_GET_CTRL_ID;



// the structure of NJPEG_VerificationMode should be the same as NJPD_VerificationMode
typedef enum
{
    E_NJPEG00_NONE,
    E_NJPEG01_TABLE_READ_WRITE,
    E_NJPEG13_ROI,
    E_NJPEG17_OBUF_OUTPUT_FORMAT_YC_SWAP,
    E_NJPEG17_OBUF_OUTPUT_FORMAT_UV_SWAP,
    E_NJPEG17_OBUF_OUTPUT_FORMAT_UV_7BIT,
    E_NJPEG17_OBUF_OUTPUT_FORMAT_UV_MSB,
    E_NJPEG18_IBUF_BURST_LENGTH,
    E_NJPEG21_NO_RESET_TABLE,
    E_NJPEG23_WRITE_PROTECT,
    E_NJPEG25_DOWNSCALE_1_2,
    E_NJPEG25_DOWNSCALE_1_4,
    E_NJPEG25_DOWNSCALE_1_8
}NJPEG_VerificationMode;

//-----------------------------------------------------------------------------
///@brief \b Typedef \b Name: *JPEG_FillHdrFunc
///@brief \b Typedef \b Description: the function for fill header information
///@param <IN> \b BufAddr : fill buffer address
///@param <IN> \b BufLength : fill buffer size
///@return The amount of byte read
//-----------------------------------------------------------------------------
typedef MS_S32 (*JPEG_FillHdrFunc)(MS_PHYADDR BufAddr, MS_U32 BufLength);

//-----------------------------------------------------------------------------
///@brief \b Typedef \b Name: *JPEG_IsrFuncCb
///@brief \b Typedef \b Description: the function handling JPD interrupt
///@param None
///@return None
//-----------------------------------------------------------------------------
typedef void (*JPEG_IsrFuncCb)(void);

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: JPEG_InitParam
/// @brief \b Struct \b Description: JPEG decode parameter setting
//-----------------------------------------------------------------------------
typedef struct
{
    MS_PHYADDR u32MRCBufAddr;       ///< MRC buffer address
    MS_U32 u32MRCBufSize;           ///< MRC buffer size
    MS_PHYADDR u32MWCBufAddr;       ///< MWC buffer address
    MS_U32 u32MWCBufSize;           ///< MWC buffer size
    MS_PHYADDR u32InternalBufAddr;  ///< internal buffer address
    MS_U32 u32InternalBufSize;      ///< internal buffer size
    MS_U32 u32DecByteRead;          ///< how many byte read for JPEG decoder initialization
    MS_BOOL bEOF;                   ///< has read to the end of file
    MS_U8 u8DecodeType;             ///< JPEG decode type : JPEG main, thumbnail, or MJPEG
    MS_BOOL bInitMem;               ///< initialize memory pool or not
    JPEG_FillHdrFunc pFillHdrFunc;  ///< the function for fill header information
} JPEG_InitParam;
//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: JPEG_DrvCap
/// @brief \b Struct \b Description: JPEG decode driver capability
//-----------------------------------------------------------------------------
typedef struct
{
    MS_U16 u16MaxWidth;     ///< max decoded width for baseline
    MS_U16 u16MaxHeight;    ///< max decoded height for baseline
    MS_U16 u16MaxProWidth;  ///< max decoded width for progressive
    MS_U16 u16MaxProHeight; ///< max decoded height for progressive
    MS_BOOL bBaseline;      ///< support baseline decode
    MS_BOOL bProgressive;   ///< support progressive decode
    MS_BOOL bMJPEG;         ///< support motion JPEG
} JPEG_DrvCap;
//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: JPEG_Info
/// @brief \b Struct \b Description: JPEG decode information
//-----------------------------------------------------------------------------
typedef struct
{
    const MSIF_Version* pu8DrvVer;  ///< JPEG DRV version
    MS_U8* pu8HalVer;               ///< JPEG HAL version
    MS_U8* pu8FwVer;                ///< JPEG FW version
    JPEG_DrvCap stDrvCap;           ///< JPEG driver capability
} JPEG_Info;
//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: JPEG_Status
/// @brief \b Struct \b Description: JPD driver Status
//-----------------------------------------------------------------------------
typedef struct
{
    MS_U32  u32CurMRCAddr;  ///< JPD current decoded address
    MS_U16  u16CurVidx;     ///< JPD current decoded vertical index
    MS_U16  u16CurRow;      ///< JPD current decoded row
    MS_U16  u16CurCol;      ///< JPD current decoded column
    MS_BOOL bDrvBusy;       ///< JPD status
    MS_BOOL bIsrEnable;     ///< JPD ISR status
} JPEG_Status;
//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: JPEG_EXIF_DateTime
/// @brief \b Struct \b Description: The DateTime info of JPEG EXIF.
//-----------------------------------------------------------------------------
typedef struct
{
    MS_U32 u32Year;         ///< The year info of JPEG EXIF DataTime
    MS_U32 u32Month;        ///< The month info of JPEG EXIF DataTime
    MS_U32 u32Day;          ///< The day info of JPEG EXIF DataTime
    MS_U32 u32Hour;         ///< The hour info of JPEG EXIF DataTime
    MS_U32 u32Minute;       ///< The minute info of JPEG EXIF DataTime
    MS_U32 u32Second;       ///< The second info of JPEG EXIF DataTime
    MS_BOOL bHasDataTime;   ///< JPEG EXIF DataTime info exist or not
}JPEG_EXIF_DateTime;

typedef enum
{
    E_DECODE_NONE = 0,
    E_DECODE_DONE,
    E_DECODING,
    E_DECODE_ERR,
    E_STREAM_READ_ERR
} EN_JPEG_DECODE_STATUS;

typedef struct
{
    MS_U16 u16Xdensity;      //inch or cm
    MS_U16 u16Ydensity;      //inch or cm
    MS_U8 u8Unit;                  //APP0 Mark units : 0-> no units, X and Y specify the pixel aspect ratio
                                      //                       1 -> X and Y are dots per inch
                                      //                       2 -> X and Y are dots per cm
}APP0_Unit;


typedef struct
{
    union
    {
        struct
        {
            MS_U32 numerator;
            MS_U32 denominator;
        };

        struct
        {
            MS_S32 s_numerator;
            MS_S32 s_denominator;
        };
    };
} JPEG_RATIONAL;


#if SUPPORT_MPO_FORMAT

typedef struct
{
    MS_U32 attribute;
    MS_U32 size;
    MS_U32 offset;
    MS_U16 image1_no;
    MS_U16 image2_no;
} JPEG_MPO_MP_ENTRY_INFO;


typedef struct
{
    MS_U32 start_of_offset;
    MS_U32 num_of_image;
    JPEG_MPO_MP_ENTRY_INFO mp_entry[JPEG_MPO_MAX_SUPPORT_IMAGE];
} JPEG_MPO_INDEX_INFO;


typedef struct
{
    MS_U32 MPIndividualNum;
    MS_U32 PanOrientation;
    JPEG_RATIONAL PanOverlap_H;
    JPEG_RATIONAL PanOverlap_V;
    MS_U32 BaseViewpointNum;
    JPEG_RATIONAL ConvergenceAngle;
    JPEG_RATIONAL BaselineLength;
    JPEG_RATIONAL VerticalDivergence;
    JPEG_RATIONAL AxisDistance_X;
    JPEG_RATIONAL AxisDistance_Y;
    JPEG_RATIONAL AxisDistance_Z;
    JPEG_RATIONAL YawAngle;
    JPEG_RATIONAL PitchAngle;
    JPEG_RATIONAL RollAngle;
    MS_BOOL used;
} JPEG_MPO_ATTRIBUTE_INFO;

#endif
void MApi_JPEG_EnableOJPD(MS_BOOL bOnOff);
JPEG_Result MApi_JPEG_Init_UsingOJPD(JPEG_InitParam *pInitParam);

void msAPI_JPEG_get_APP0_info( MS_U8 *unit,MS_U16 *x, MS_U16 *y );

JPEG_Result MApi_JPEG_Init(JPEG_InitParam *pInitParam);
JPEG_Result MApi_JPEG_DecodeHdr(void);
JPEG_Result MApi_JPEG_Decode(void);
void MApi_JPEG_Exit(void);
JPEG_ErrCode MApi_JPEG_GetErrorCode(void);
JPEG_Event MApi_JPEG_GetJPDEventFlag(void);
void MApi_JPEG_SetJPDEventFlag(JPEG_Event eEvtVal);
void MApi_JPEG_Rst(void);
void MApi_JPEG_PowerOn(void);
void MApi_JPEG_PowerOff(void);
MS_U16 MApi_JPEG_GetCurVidx(void);
MS_BOOL MApi_JPEG_IsProgressive(void);
MS_BOOL MApi_JPEG_ThumbnailFound(void);
MS_U16 MApi_JPEG_GetWidth(void);
MS_U16 MApi_JPEG_GetHeight(void);
MS_U16 MApi_JPEG_GetOriginalWidth(void);
MS_U16 MApi_JPEG_GetOriginalHeight(void);
MS_U16 MApi_JPEG_GetNonAlignmentWidth(void);
MS_U16 MApi_JPEG_GetNonAlignmentHeight(void);
MS_U16 MApi_JPEG_GetAlignedPitch(void);
MS_U16 MApi_JPEG_GetAlignedPitch_H(void);
MS_U16 MApi_JPEG_GetAlignedWidth(void);
MS_U16 MApi_JPEG_GetAlignedHeight(void);
MS_U8 MApi_JPEG_GetScaleDownFactor(void);
void MApi_JPEG_SetMaxDecodeResolution(MS_U16 u16Width, MS_U16 u16Height);
void MApi_JPEG_SetProMaxDecodeResolution(MS_U16 u16ProWidth, MS_U16 u16ProHeight);
void MApi_JPEG_SetMRBufferValid(JPEG_BuffLoadType u8MRBuffType);
void MApi_JPEG_UpdateReadInfo(MS_U32 u32DataRead, MS_BOOL bEOFflag);
void MApi_JPEG_ProcessEOF(JPEG_BuffLoadType u8MRBuffType);
void MApi_JPEG_SetErrCode(JPEG_ErrCode ErrStatus);
void MApi_JPEG_SetDbgLevel(MS_U8 u8DbgLevel);
MS_U8 MApi_JPEG_GetDbgLevel(void);
void MApi_JPEG_GetInfo(JPEG_Info *pJPEG_Info);
void MApi_JPEG_GetStatus(JPEG_Status *pJPEG_Status);
JPEG_Result MApi_JPEG_GetLibVer(const MSIF_Version **ppVersion);
JPEG_Result MApi_JPEG_HdlVidxChk(void);
JPEG_Result MApi_JPEG_GetBuffLoadType(JPEG_BuffLoadType *pBuffLoadType);
JPEG_Result MApi_JPEG_EnableISR(JPEG_IsrFuncCb IsrCb);
JPEG_Result MApi_JPEG_DisableISR(void);
JPEG_DecodeStatus MApi_JPEG_WaitDone(void);
JPEG_Result MApi_JPEG_GetEXIFDateTime(JPEG_EXIF_DateTime *DateTime);
JPEG_Result MApi_JPEG_GetEXIFOrientation(JPEG_EXIF_Orientation *eOrientation);
#if SUPPORT_EXIF_EXTRA_INFO
JPEG_Result MApi_JPEG_GetEXIFManufacturer(MS_U8 *pu8Manufacturer, MS_U8 u8size);
JPEG_Result MApi_JPEG_GetEXIFModel(MS_U8 *pu8Model, MS_U8 u8size);
JPEG_Result MApi_JPEG_GetEXIFFlash(MS_U16 *pu16Flash);
JPEG_Result MApi_JPEG_GetEXIFISOSpeedRatings(MS_U32 *pu32ISOSpeedRatings);
JPEG_Result MApi_JPEG_GetEXIFShutterSpeedValue(JPEG_RATIONAL *pShutterSpeedValue);
JPEG_Result MApi_JPEG_GetEXIFApertureValue(JPEG_RATIONAL *pApertureValue);
JPEG_Result MApi_JPEG_GetEXIFExposureBiasValue(JPEG_RATIONAL *pExposureBiasValue);
JPEG_Result MApi_JPEG_GetEXIFFocalLength(JPEG_RATIONAL *pFocalLength);
JPEG_Result MApi_JPEG_GetEXIFImageWidth(MS_U32 *pu32ImageWidth);
JPEG_Result MApi_JPEG_GetEXIFImageHeight(MS_U32 *pu32ImageHeight);
JPEG_Result MApi_JPEG_GetEXIFExposureTime(JPEG_RATIONAL *pExposureTime);
JPEG_Result MApi_JPEG_GetEXIFFNumber(JPEG_RATIONAL *pFNumber);
#endif
JPEG_Result MApi_JPEG_GetControl(EN_JPEG_GET_CTRL_ID eGetID, MS_U32 *param, MS_U32 u32Size);
void MApi_JPEG_DisableAddressConvert(void);
MS_PHYADDR MApi_JPEG_GetFreeMemory(MS_U32 size);
MS_U32 MApi_JPEG_GetDataOffset(void);
MS_U32 MApi_JPEG_GetSOFOffset(void);
void MApi_JPEG_SetNJPDInstance(MS_U8 JPDNum);
JPEG_Result MApi_JPEG_SupportCMYK(MS_BOOL bEnable);
JPEG_Result MApi_JPEG_SupportRGB(MS_BOOL bEnable);
void MApi_JPEG_SetMHEG5(MS_BOOL bEnable);

#if SUPPORT_MPO_FORMAT
//For MPO
MS_BOOL MApi_JPEG_IsMPOFormat(void);
MS_BOOL MApi_JPEG_GetMPOIndex(JPEG_MPO_INDEX_INFO **ppMPOIndex);
MS_BOOL MApi_JPEG_GetMPOAttr(MS_U32 image_no, JPEG_MPO_ATTRIBUTE_INFO **ppMPOAttr);
void MApi_JPEG_DumpMPO(void);
MS_BOOL MApi_JPEG_SetMPOBuffer(MS_U32 read_offset, MS_U32 output_start);
void MApi_JPEG_SetMPOMaxDecodeResolution(MS_U16 u16Width, MS_U16 u16Height);
void MApi_JPEG_SetMPOProMaxDecodeResolution(MS_U16 u16ProWidth, MS_U16 u16ProHeight);
#endif
void MApi_JPEG_SetVerificationMode(NJPEG_VerificationMode VerificationMode);
NJPEG_VerificationMode MApi_JPEG_GetVerificationMode(void);
void MApi_NJPD_Debug(void);
MS_BOOL MApi_JPEG_IsNJPD(void);

#ifdef __cplusplus
}
#endif

//------------------------------------------------------------------------------
#endif // _API_JPEG_H_
//------------------------------------------------------------------------------
