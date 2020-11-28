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

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvDAC.h
/// @author MStar Semiconductor Inc.
/// @brief  DAC Driver Interface
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_DAC_H_
#define _DRV_DAC_H_


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

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef enum
{
    RES_720x480I_60Hz = 0,
    RES_720x480P_60Hz,
    RES_720x576I_50Hz,
    RES_720x576P_50Hz,
    RES_1280x720P_50Hz,
    RES_1280x720P_60Hz,
    RES_1920x1080I_50Hz,
    RES_1920x1080I_60Hz,
    RES_1920x1080P_50Hz,
    RES_1920x1080P_60Hz,
    RES_1920x1080P_24Hz,
    RES_1920x1080P_25Hz,
    RES_1920x1080P_30Hz,
    RES_640x480P_60Hz,
    RES_VGA640x480P_60Hz,
    RES_TTL480X272P_60Hz,
} EN_OUTPUT_VIDEO_TIMING_TYPE;

typedef enum
{
    COLOR_8_BIT,
    COLOR_10_BIT,
    COLOR_12_BIT,
}EN_OUTPUT_BIT_TYPE;

typedef enum
{
    DAC_CLK_FROM_DISP,
    DAC_CLK_FROM_VEDAC,
    DAC_CLK_FROM_DVBC_INN,
    DAC_CLK_FROM_DVBC_EQ,
    DAC_CLK_FROM_ADCD_D,
    DAC_CLK_FROM_DFT,
} EN_DAC_CLK_TYPE;

typedef enum
{
    DAC_TO_HDGEN = 0,   //HD Gen output
    DAC_TO_VE = 1,      //VE output (CVBS + S-Video)
    DAC_TO_VE_YPBPR =3  //VE output (Y/Pb/Pr)
} EN_DAC_OUTPUT_TYPE;

typedef enum
{
    DAC_R_G_B = 0,
    DAC_R_B_G = 1,
    DAC_G_R_B = 2,
    DAC_B_G_R = 4,
    DAC_G_B_R = 5,
    DAC_B_R_G = 6,
    DAC_R_R_R = 7,
} EN_DAC_SWAP_SEL;

typedef enum
{
    DAC_OUTPUT_LEVEL_HIGH = 0,  //1.3V
    DAC_OUTPUT_LEVEL_LOW = 1    //1V
} EN_DAC_MAX_OUTPUT_LEVEL;

typedef enum
{
    DAC_SD_OFF =0,
    DAC_SD_X = 1,
    DAC_SD_Y = 2,
    DAC_SD_XY = 3,
    DAC_SD_C = 4,
    DAC_SD_XC = 5,
    DAC_SD_YC = 6,
    DAC_SD_XYC = 7,

}EN_DAC_SD_ENABLE_CTRL;

typedef enum
{
    DAC_HD_OFF =0,
    DAC_HD_R = 1,
    DAC_HD_G = 2,
    DAC_HD_RG = 3,
    DAC_HD_B = 4,
    DAC_HD_RB = 5,
    DAC_HD_GB = 6,
    DAC_HD_RGB = 7,

}EN_DAC_HD_ENABLE_CTRL;

typedef enum
{
    DAC_DETECT_PLUGIN,       //Detect  Plug_IN
    DAC_DETECT_PLUGOUT,     // Detect Plug_OUT
}EN_DAC_DETECT_TYPE;

typedef enum
{
    DAC_DETECT_HD,       //Detect HD_DAC
    DAC_DETECT_SD,     // Detect SD_DAC
}EN_DAC_DETECT;

//-------------------------------------------------------------------------------------------------
//  Function Prototype
//-------------------------------------------------------------------------------------------------
#ifdef MDRV_DAC_C
#define MDRV_INTERFACE
#else
#define MDRV_INTERFACE extern
#endif

MDRV_INTERFACE void MDrv_DAC_SetIOMapBase(MS_U32 u32NPMBase, MS_U32 u32PMBase);
MDRV_INTERFACE void MDrv_DAC_Init(void);
MDRV_INTERFACE void MDrv_DAC_Enable(MS_BOOL bEnable, MS_BOOL bIsYPbPr);
MDRV_INTERFACE void MDrv_DAC_SetClkInv(MS_BOOL bEnable, MS_BOOL bIsYPbPr);
MDRV_INTERFACE void MDrv_DAC_SetOutputSource(EN_DAC_OUTPUT_TYPE enOutputType, MS_BOOL bIsYPbPr);
MDRV_INTERFACE void MDrv_DAC_SetOutputLevel(EN_DAC_MAX_OUTPUT_LEVEL enLevel, MS_BOOL bIsYPbPr);
MDRV_INTERFACE void MDrv_DAC_SetOutputSwapSel(EN_DAC_SWAP_SEL enSwap,MS_BOOL bIsYPbPr);
MDRV_INTERFACE void MDrv_DAC_SetOutputTiming(EN_OUTPUT_VIDEO_TIMING_TYPE enTiming);
MDRV_INTERFACE void MDrv_ClkSel_Set(EN_OUTPUT_VIDEO_TIMING_TYPE enTiming, EN_OUTPUT_BIT_TYPE enBits);
MDRV_INTERFACE void MDrv_DAC_OnOffSD(EN_DAC_SD_ENABLE_CTRL enBit);
MDRV_INTERFACE void MDrv_DAC_OnOffHD(EN_DAC_HD_ENABLE_CTRL enBit);
MDRV_INTERFACE void MDrv_DAC_Exit(void);
MDRV_INTERFACE void MDrv_DAC_DumpTable(MS_U8 * pTCONTable, MS_U8 u8Tcontype);

//----------------------------------------------------------------
// DAC - set half output current
// @return none
//----------------------------------------------------------------
MDRV_INTERFACE void MDrv_DAC_SetIHalfOutput(MS_BOOL bEnable, MS_BOOL bIsYPbPr);

//----------------------------------------------------------------
// DAC - set half output current
// @return none
//----------------------------------------------------------------
MDRV_INTERFACE void MDrv_DAC_SetQuartOutput(MS_BOOL bEnable, MS_BOOL bIsYPbPr);

//----------------------------------------------------------------
// MDrv_DAC_SetDACState - Set DAC init state
// @param: bEnable: TRUE for DAC is initialized, FALSE for not initialized
// @param: bIsYPbPr: TRUE for YPbPr, FALSE for CVBS
// @return none
//----------------------------------------------------------------
MDRV_INTERFACE void MDrv_DAC_SetDACState(MS_BOOL bEnable, MS_BOOL bIsYPbPr);

//----------------------------------------------------------------
// MDrv_DAC_GetDACState - Get DAC init state
// @param: bIsYPbPr: TRUE for YPbPr, FALSE for CVBS
// @return: TRUE is DAC is initialized
//----------------------------------------------------------------
MDRV_INTERFACE MS_BOOL MDrv_DAC_GetDACState(MS_BOOL bIsYPbPr);

//----------------------------------------------------------------
// MDrv_DAC_HotPlugDetect - Get DAC HotPlug state
// @param: SelDAC: DAC_DETECT_HD, DAC_DETECT_SD
// @param: DetectType: DAC_DETECT_PLUGIN, DAC_DETECT_PLUGOUT
// @param: bIsSignIn: Report signal is in/out
// @return: TRUE is working successful
//----------------------------------------------------------------
MDRV_INTERFACE MS_BOOL MDrv_DAC_HotPlugDetect(EN_DAC_DETECT SelDAC, EN_DAC_DETECT_TYPE DetectType, MS_BOOL *State);

#ifdef __cplusplus
}
#endif

#endif // _DRV_HDMITX_H_

