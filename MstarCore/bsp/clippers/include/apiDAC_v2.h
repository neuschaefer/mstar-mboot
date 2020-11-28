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
/// @file   apiDAC_v2.h
/// @brief  MStar Graphics Output Path API
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DAC_V2_H_
#define _DAC_V2_H_

#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

/// DAC CMD
typedef enum
{
    //DAC command
    E_DAC_GET_LIBVER,
    E_DAC_GET_INFO,
    E_DAC_GET_STATUS,
    E_DAC_SET_DBG_LEVEL,
    E_DAC_INIT,
    E_DAC_ENABLE,
    E_DAC_SET_CLKINV,
    E_DAC_SET_YPBPR_OUTPUTTIMING,
    E_DAC_SET_OUTPUT_SOURCE,
    E_DAC_SET_OUTPUT_LEVEL,
    E_DAC_SET_OUTPUT_SWAPSEL,
    E_DAC_ONOFF_SD,
    E_DAC_ONOFF_HD,
    E_DAC_CLKSEL,
    E_DAC_DUMP_TABLE,
    E_DAC_EXIT,
    E_DAC_SET_IHALF_OUTPUT,
    E_DAC_SET_QUART_OUTPUT,
    E_DAC_SET_DAC_STATE,
    E_DAC_HOTPLUG_DETECT,
}E_DAC_IOCTL_CMDS;;

typedef struct
{
    const MSIF_Version **ppVersion;
    APIDAC_Result eReturnValue;
} stDAC_GET_LIBVER,*pstDAC_GET_LIBVER;

typedef struct
{
    const DAC_ApiInfo* stReturnValue;
} stDAC_GET_INFO, *pstDAC_GET_INFO;

typedef struct
{
    DAC_ApiStatus* pDacStatus;
    MS_BOOL bReturnValue;
} stDAC_GET_STATUS,*pstDAC_GET_STATUS;

typedef struct
{
    MS_U16 u16DbgSwitch;
    MS_BOOL bReturnValue;
} stDAC_SET_DBG_LEVEL,*pstDAC_SET_DBG_LEVEL;

typedef struct
{
    MS_BOOL bReturnValue;
} stDAC_INIT,*pstDAC_INIT;

typedef struct
{
    MS_BOOL bEnable;
    MS_BOOL bIsYPbPr;
} stDAC_ENABLE, *pstDAC_ENABLE;

typedef struct
{
    MS_BOOL bEnable;
    MS_BOOL bIsYPbPr;
} stDAC_SET_CLKINV, *pstDAC_SET_CLKINV;

typedef struct
{
    E_OUTPUT_VIDEO_TIMING_TYPE eTiming;
} stDAC_SET_YPBPR_OUTPUTTIMING,*pstDAC_SET_YPBPR_OUTPUTTIMING;

typedef struct
{
    E_DAC_OUTPUT_TYPE enOutputType;
    MS_BOOL bIsYPbPr;
} stDAC_SET_OUTPUT_SOURCE,*pstDAC_SET_OUTPUT_SOURCE;

typedef struct
{
    E_DAC_MAX_OUTPUT_LEVEL enLevel;
    MS_BOOL bIsYPbPr;
} stXC_SET_OUTPUT_LEVEL, *pstXC_SET_OUTPUT_LEVEL;

typedef struct
{
    E_DAC_SWAP_SEL enSwap;
    MS_BOOL bIsYPbPr;
} stDAC_SET_OUTPUT_SWAPSEL, *pstDAC_SET_OUTPUT_SWAPSEL;

typedef struct
{
    E_DAC_SD_ENABLE_CTRL enBit;
} stDAC_ONOFF_SD,*pstDAC_ONOFF_SD;

typedef struct
{
    E_DAC_HD_ENABLE_CTRL enBit;
} stDAC_ONOFF_HD, *pstDAC_ONOFF_HD;

typedef struct
{
    E_OUTPUT_VIDEO_TIMING_TYPE eTiming;
    E_OUTPUT_BIT_TYPE ebits;
} stDAC_CLKSEL, *pstDAC_CLKSEL;

typedef struct
{
    MS_U8 *pDACTable;
    MS_U8 u8DACtype;
} stDAC_DUMP_TABLE, *pstDAC_DUMP_TABLE;

typedef struct
{
    MS_BOOL bEnable;
    MS_BOOL bIsYPbPr;
} stDAC_SET_IHALF_OUTPUT, *pstDAC_SET_IHALF_OUTPUT;

typedef struct
{
    MS_BOOL bEnable;
    MS_BOOL bIsYPbPr;
} stDAC_SET_QUART_OUTPUT, *pstDAC_SET_QUART_OUTPUT;

typedef struct
{
    MS_BOOL bEnabled;
    MS_BOOL bIsYPbPr;
} stDAC_SET_DAC_STATE, *pstDAC_SET_DAC_STATE;

typedef struct
{
    E_DAC_DETECT SelDAC;
    E_DAC_DETECT_TYPE DetectType;
    MS_BOOL *State;
    MS_BOOL bReturnValue;
} stDAC_HOTPLUG_DETECT, *pstDAC_HOTPLUG_DETECT;


#ifdef __cplusplus
}
#endif

#endif // _API_DAC_H_

