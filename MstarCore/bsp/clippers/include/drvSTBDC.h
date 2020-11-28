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
/// @file   drvMVOP.h
/// @brief  MVOP Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_STBDC_H_
#define _DRV_STBDC_H_

#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
/// Version string.
#define MSIF_STBDC_LIB_CODE              {'S','T','B','_'}    //Lib code
#define MSIF_STBDC_LIBVER                {'0','1'}            //LIB version
#define MSIF_STBDC_BUILDNUM              {'0','1'}            //Build Number
#define MSIF_STBDC_CHANGELIST            {'0','0','1','3','4','8','7','2'} //P4 ChangeList Number

#define STBDC_DRV_VERSION                /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_STBDC_LIB_CODE,                 /* IP__                                             */  \
    MSIF_STBDC_LIBVER,                   /* 0.0 ~ Z.Z                                        */  \
    MSIF_STBDC_BUILDNUM,                 /* 00 ~ 99                                          */  \
    MSIF_STBDC_CHANGELIST,               /* CL#                                              */  \
    MSIF_OS


#define _SUPPORT_IMG_OFFSET_

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef enum
{
    E_STBDC_OK    = 0,
    E_STBDC_FAIL  = 1,
    E_STBDC_INVALID_PARAM = 2
} STBDC_Result;

/// MVOP tile format
typedef enum
{
    E_STBDC_TILE_8x32  = 0,
    E_STBDC_TILE_16x32 = 1,
    E_STBDC_TILE_NONE  = 2
} STBDC_TileFormat;




typedef struct
{
    MS_PHYADDR u32LumaAddr;
    MS_PHYADDR u32ChromaAddr;
    MS_U16 u16HSize;
    MS_U16 u16VSize;
    MS_U16 u16Pitch;
    MS_BOOL bYUV422;    //!< YUV422 or YUV420
    MS_BOOL bProgressive;   //!< Progressive or Interlace
    MS_BOOL bBottomField;         // +S3, Field 0 or 1
    MS_U16 u16CropX;
    MS_U16 u16CropY;
    MS_U16 u16CropWidth;
    MS_U16 u16CropHeight;
} STBDC_InputCfg;
//---------------------



typedef enum
{
    STBDC_PATTERN_NORMAL     = 0,
    STBDC_PATTERN_COLORBAR   = 1,
    STBDC_PATTERN_FRAMECOLOR = 2,
    STBDC_PATTERN_YCBCR      = 3,
    STBDC_PATTERN_Y          = 4,
    STBDC_PATTERN_CB         = 5,
    STBDC_PATTERN_CR         = 6,
    STBDC_PATTERN_DEFAULT    = 7   //new pattern = (last parrtern + 1) % MVOP_PATTERN_DEFAULT
} STBDC_Pattern;

typedef enum
{
    E_STBDC_INPUT_DRAM = 0,
    E_STBDC_INPUT_HVD = 1,    //SVD for T2
    E_STBDC_INPUT_MVD  = 2,
    E_STBDC_INPUT_JPD  = 3,
    E_STBDC_INPUT_UNKNOWN = -1
} STBDC_InputSel;

/// MVOP VideoStat data structure
typedef struct
{
    MS_U16 u16HorSize;
    MS_U16 u16VerSize;
    MS_U16 u16FrameRate;
    MS_U8 u8AspectRate;
    MS_U8 u8Interlace;
    MS_U16 u16HorOffset;
    MS_U16 u16VerOffset;
} STBDC_VidStat;


///MVOP driver status
typedef struct _STBDC_DrvStatus
{
    MS_BOOL bIsInit;
    MS_BOOL bIsEnable;
    MS_BOOL bIsUVShift;
    MS_BOOL bIsBlackBG;
    MS_BOOL bIsMonoMode;
    MS_BOOL bIsSetTiming;
} STBDC_DrvStatus;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------





#ifdef __cplusplus
}
#endif

#endif // _DRV_MVOP_H_
