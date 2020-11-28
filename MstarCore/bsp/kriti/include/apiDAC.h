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
/// @file   apiDAC.h
/// @brief  DAC Interface
/// @author MStar Semiconductor Inc.
//  CL162321++:
//   update HDGen table. tPanelDACOUT480I_60 output for U4
//  CL 216439++:
//   Adds DACOUT_1080P_24, DACOUT_1080P_25, DACOUT_1080P_30.
//  CL 223188++:
//   i. Modify HDGEN settings in "U4_DAC_Driver.xls" for HDMITx 480i/576i/1080i
//   ii. Add CLKGEN1 setting in halClkSel.c for HDMITx 1080i
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _API_DAC_H_
#define _API_DAC_H_

#ifdef __cplusplus
extern "C" {
#endif

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
// library information
#define MSIF_DAC_LIB_CODE               {'D','A','C','_'}
#define MSIF_DAC_LIBVER                 {'0','0'}
#define MSIF_DAC_BUILDNUM               {'3','0'}
#define MSIF_DAC_CHANGELIST             {'0','0','5','2','9','8','2','4'}

#define DAC_API_VERSION                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'    */  \
    MSIF_CLASS,                         /* '00'      */  \
    MSIF_CUS,                           /* 0x0000    */  \
    MSIF_MOD,                           /* 0x0000    */  \
    MSIF_CHIP,                                           \
    MSIF_CPU,                                            \
    MSIF_DAC_LIB_CODE  ,                /* IP__      */  \
    MSIF_DAC_LIBVER    ,                /* 0.0 ~ Z.Z */  \
    MSIF_DAC_BUILDNUM  ,                /* 00 ~ 99   */  \
    MSIF_DAC_CHANGELIST,                /* CL#       */  \
    MSIF_OS

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
/// Define return value of MApi_DAC
typedef enum
{
    E_APIDAC_FAIL = 0,
    E_APIDAC_OK = 1,
    E_APIDAC_GET_BASEADDR_FAIL,            ///< get base address failed when initialize panel driver
    E_APIDAC_OBTAIN_MUTEX_FAIL,            ///< obtain mutex timeout when calling this function
} APIDAC_Result;

/// Define output video timing
/// Shall align to E_DAC_PANEL_INDEX.
typedef enum
{
    E_RES_720x480I_60Hz = 0,
    E_RES_720x480P_60Hz,
    E_RES_720x576I_50Hz,
    E_RES_720x576P_50Hz,
    E_RES_1280x720P_50Hz,
    E_RES_1280x720P_60Hz,
    E_RES_1920x1080I_50Hz,
    E_RES_1920x1080I_60Hz,
    E_RES_1920x1080P_50Hz,
    E_RES_1920x1080P_60Hz,
    E_RES_1920x1080P_30Hz,
    E_RES_1920x1080P_25Hz,
    E_RES_1920x1080P_24Hz,
    E_RES_640x480P_60Hz,
    E_RES_1920X2205P_24Hz,
    E_RES_1280X1470P_50Hz,
    E_RES_1280X1470P_60Hz,
    E_RES_VGA_START = 0x40,      ///< Resolution for VGA output
    E_RES_VGA640x480P_60Hz = E_RES_VGA_START,
    E_RES_TTL_START = 0xC0,      ///< Resolution for TTL output(will not coexist with VGA).
    E_RES_TTL480X272P_60Hz = E_RES_TTL_START,
} E_OUTPUT_VIDEO_TIMING_TYPE;

/// Define the color depth of output
typedef enum
{
    E_COLOR_8_BIT,
    E_COLOR_10_BIT,
    E_COLOR_12_BIT,
}E_OUTPUT_BIT_TYPE;

typedef enum
{
    E_DAC_TO_HDGEN = 0,     //HD Gen output
    E_DAC_TO_VE = 1,        //VE output (CVBS + S-Video)
    E_DAC_TO_VE_YPBPR =3    //VE output (Y/Pb/Pr)
} E_DAC_OUTPUT_TYPE;

typedef enum
{
    E_DAC_R_G_B = 0,
    E_DAC_R_B_G = 1,
    E_DAC_G_R_B = 2,
    E_DAC_B_G_R = 4,
    E_DAC_G_B_R = 5,
    E_DAC_B_R_G = 6,
    E_DAC_R_R_R = 7,
} E_DAC_SWAP_SEL;

typedef enum
{
    E_DAC_OUTPUT_LEVEL_HIGH = 0,  //1.3V for CVBS + S-Video
    E_DAC_OUTPUT_LEVEL_LOW = 1    //1.0V for YPbPr
} E_DAC_MAX_OUTPUT_LEVEL;

typedef enum
{
    E_DAC_SD_OFF =0,
    E_DAC_SD_X = 1,
    E_DAC_SD_Y = 2,
    E_DAC_SD_XY = 3,
    E_DAC_SD_C = 4,
    E_DAC_SD_XC = 5,
    E_DAC_SD_YC = 6,
    E_DAC_SD_XYC = 7,
}E_DAC_SD_ENABLE_CTRL;

typedef enum
{
    E_DAC_HD_OFF =0,
    E_DAC_HD_R = 1,
    E_DAC_HD_G = 2,
    E_DAC_HD_RG = 3,
    E_DAC_HD_B = 4,
    E_DAC_HD_RB = 5,
    E_DAC_HD_GB = 6,
    E_DAC_HD_RGB = 7,

}E_DAC_HD_ENABLE_CTRL;

typedef enum
{
    E_DAC_DETECT_PLUGIN,       //Detect  Plug_IN
    E_DAC_DETECT_PLUGOUT,     // Detect Plug_OUT
}E_DAC_DETECT_TYPE;

typedef enum
{
    E_DAC_DETECT_HD,       //Detect  Plug_IN
    E_DAC_DETECT_SD,     // Detect Plug_OUT
}E_DAC_DETECT;

typedef struct
{
    MS_U32 u32Type;
}APIDAC_OUTPUT_TYPE;

typedef struct
{
    APIDAC_OUTPUT_TYPE eSupportOutputType;   ///< Gamma type supported by apiPNL
} DAC_ApiInfo;

typedef struct
{
    MS_BOOL bDac_Initialized;       ///< DAC initialized or not
    MS_BOOL bDac_VE_enabled;        ///< DAC CVBS/S-Video enabled or not
    MS_BOOL bDac_YPbPr_enabled;     ///< DAC YPbPr enabled or not
} DAC_ApiStatus;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

/******************************************************************************/
/*                     Variable                                            */
/* ****************************************************************************/
/**
*
*  The global interface for panel manipulation.
*
*  @attention <b>Call "MApi_DAC_Init()" first before using this obj</b>
*/

//-------------------------------------------------------------------------------------------------
/// Get version (without Mutex protect)
/// @param  ppVersion                 \b OUT: Version information of DAC lib.
/// @return @ref APIDAC_Result
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC APIDAC_Result MApi_DAC_GetLibVer(const MSIF_Version **ppVersion);

//-------------------------------------------------------------------------------------------------
/// Get DAC driver info
/// @return the pointer to DAC_ApiInfo structure
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC const DAC_ApiInfo * MApi_DAC_GetInfo(void);

//-------------------------------------------------------------------------------------------------
/// Get DAC status
/// @param  pDacStatus                \b OUT: the pointer to DAC_ApiStatus structure
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_DAC_GetStatus(DAC_ApiStatus *pDacStatus);

//-------------------------------------------------------------------------------------------------
/// Set DAC debug level
/// @param  pDacStatus                \b IN: debug level
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_DAC_SetDbgLevel(MS_U16 u16DbgSwitch);

//-------------------------------------------------------------------------------------------------
/// DAC Initialization
/// @return @ref MS_BOOL
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_DAC_Init(void);

//-------------------------------------------------------------------------------------------------
/// DAC configuration enable
// @param  bEnable                 \b IN: Enable or Disable DAC
// @param  bIsYPbPr                \b IN: The DAC output signal type: YPbPr or CVBS/S-VIDEO
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_DAC_Enable(MS_BOOL bEnable, MS_BOOL bIsYPbPr);

//-------------------------------------------------------------------------------------------------
/// Set DAC clock inv
// @param  bEnable                 \b IN: Enable or Disable clock INV
// @param  bIsYPbPr                \b IN: The DAC output signal type: YPbPr or CVBS/S-VIDEO
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_DAC_SetClkInv(MS_BOOL bEnable, MS_BOOL bIsYPbPr);

//-------------------------------------------------------------------------------------------------
/// Set DAC output timing for hdgen(YPbPr)
// @param  eTiming                   \b IN: The output timing type for YPbPr
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_DAC_SetYPbPrOutputTiming(E_OUTPUT_VIDEO_TIMING_TYPE eTiming);

//-------------------------------------------------------------------------------------------------
/// Set DAC output sourcec
// @param  enOutputType         \b IN: The output source type
// @param  bIsYPbPr                \b IN: The DAC output signal type: YPbPr or CVBS/S-VIDEO
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_DAC_SetOutputSource(E_DAC_OUTPUT_TYPE enOutputType, MS_BOOL bIsYPbPr);

//-------------------------------------------------------------------------------------------------
/// Set DAC output Voltage
// @param  enLevel                  \b IN: The output maximun output Voltage
// @param  bIsYPbPr                \b IN: The DAC output signal type: YPbPr or CVBS/S-VIDEO
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_DAC_SetOutputLevel(E_DAC_MAX_OUTPUT_LEVEL enLevel, MS_BOOL bIsYPbPr);

//-------------------------------------------------------------------------------------------------
/// Set DAC Swap three output
// @param  enSwap                 \b IN: swap three output (RGB/XYC)
// @param  bIsYPbPr                \b IN: The DAC output signal type: YPbPr or CVBS/S-VIDEO
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_DAC_SetOutputSwapSel(E_DAC_SWAP_SEL enSwap,MS_BOOL bIsYPbPr);

//-------------------------------------------------------------------------------------------------
/// Control DAC SD output En/Disable
// @param  enBit                \b IN: XYC
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_DAC_OnOffSD(E_DAC_SD_ENABLE_CTRL enBit);

//-------------------------------------------------------------------------------------------------
/// Control DAC HD output En/Disable
// @param  enBit                \b IN: RGB
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_DAC_OnOffHD(E_DAC_HD_ENABLE_CTRL enBit);

//-------------------------------------------------------------------------------------------------
/// Set common clock mux for DAC & HDMITx
// @param  eTiming                   \b IN: The output timing type
// @param  ebits                     \b IN: The output bit type
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC void MApi_DAC_ClkSel(E_OUTPUT_VIDEO_TIMING_TYPE eTiming, E_OUTPUT_BIT_TYPE ebits);

DLL_PUBLIC void MApi_DAC_DumpTable(MS_U8 *pDACTable, MS_U8 u8DACtype);

DLL_PUBLIC void MApi_DAC_Exit(void);

//----------------------------------------------------------------
// DAC - set half output current
// @return none
//----------------------------------------------------------------
DLL_PUBLIC void MApi_DAC_SetIHalfOutput(MS_BOOL bEnable, MS_BOOL bIsYPbPr);

//----------------------------------------------------------------
// DAC - set quart output current
// @return none
//----------------------------------------------------------------
DLL_PUBLIC void MApi_DAC_SetQuartOutput(MS_BOOL bEnable,MS_BOOL bIsYPbPr);

//----------------------------------------------------------------
// DAC - SetDacState
// When DAC is already enabled in the MBoot, we can use this function to
// mark the DAC init state as "enabled".
// @bInited: TRUE: enabled, FALSE: not enabled
// @bIsYPbPr: TRUE: HD, FALSE: SD
// @return none
//----------------------------------------------------------------
DLL_PUBLIC void MApi_DAC_SetDacState(MS_BOOL bEnabled, MS_BOOL bIsYPbPr);

//----------------------------------------------------------------
// MApi_DAC_HotPlugDetect - Get DAC HotPlug state
// @param: SelDAC: DAC_DETECT_HD, DAC_DETECT_SD
// @param: DetectType: DAC_DETECT_PLUGIN, DAC_DETECT_PLUGOUT
// @param: bIsSignIn: Report signal is in/out
// @return: TRUE is working successful
//----------------------------------------------------------------
DLL_PUBLIC MS_BOOL MApi_DAC_HotPlugDetect(E_DAC_DETECT SelDAC,E_DAC_DETECT_TYPE DetectType, MS_BOOL *State);

#ifdef __cplusplus
}
#endif

#endif

