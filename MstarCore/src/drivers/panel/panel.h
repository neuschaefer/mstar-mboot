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
#ifndef _PANEL_H_
#define _PANEL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <apiPNL.h>

#define INTERFACE extern

#ifndef LVDS_PN_SWAP_L
#define LVDS_PN_SWAP_L                  0x00
#endif
#ifndef LVDS_PN_SWAP_H
#define LVDS_PN_SWAP_H                  0x00
#endif
////////////////////////////////////////////////////
//      Type define
////////////////////////////////////////////////////

typedef enum{
    PANEL_RES_MIN = 0,

    PNL_FULLHD_SEC_LE32A = PANEL_RES_MIN,
    // FOR NORMAL LVDS PANEL
    PNL_SXGA_AU17_EN05       = 1,            // 1280X1024, PNL_AU17_EN05_SXGA
    PNL_WXGA_AU20_T200XW02   = 2,            // 1366X768, PNL_AU20_T200XW02_WXGA,
    PNL_WXGA_PLUS_CMO190_M190A1 = 3,         // 1440X900, PNL_CMO19_M190A1_WXGA, PNL_AU19PW01_WXGA
    PNL_WSXGA_AU22_M201EW01  = 4,            // 1680X1050, PNL_AU20_M201EW01_WSXGA,
    PNL_FULLHD_CMO216_H1L01  = 5,            // 1920X1080, PNL_AU37_T370HW01_HD, PNL_CMO216H1_L01_HD.H
    PANEL_RES_FULL_HD       = 5,            // for auotbuild compatitable

    // FOR DAC/HDMI TX OUTPUT
    DACOUT_480I              = 6,            // JUST FOR U3 DAC OUTPUT 480I TIMING USAGE
    DACOUT_480P              = 7,            // JUST FOR U3 DAC OUTPUT 480P TIMING USAGE
    DACOUT_576I              = 8,            // JUST FOR U3 DAC OUTPUT 576I TIMING USAGE
    DACOUT_576P              = 9,            // JUST FOR U3 DAC OUTPUT 576P TIMING USAGE
    DACOUT_720P_50           = 10,           // JUST FOR U3 DAC OUTPUT 720P TIMING USAGE
    DACOUT_720P_60           = 11,           // JUST FOR U3 DAC OUTPUT 720P TIMING USAGE
    DACOUT_1080I_50          = 12,           // JUST FOR U3 DAC OUTPUT 1080I TIMING USAGE
    DACOUT_1080I_60          = 13,           // JUST FOR U3 DAC OUTPUT 1080I TIMING USAGE
    DACOUT_1080P_50          = 14,           // JUST FOR U3 DAC OUTPUT 1080P TIMING USAGE
    DACOUT_1080P_60          = 15,           // JUST FOR U3 DAC OUTPUT 1080P TIMING USAGE

    DACOUT_1080P_30          = 16,           // JUST FOR U3 DAC OUTPUT 1080P TIMING USAGE
    DACOUT_1080P_25          = 17,           // JUST FOR U3 DAC OUTPUT 1080P TIMING USAGE
    DACOUT_1080P_24          = 18,           // JUST FOR U3 DAC OUTPUT 1080P TIMING USAGE
    DACOUT_640x480_60        = 19,           // JUST FOR U3 DAC OUTPUT 1080P TIMING USAGE
    DACOUT_1920x2205P_24     = 20,           // JUST FOR U3 DAC OUTPUT 1080P TIMING USAGE

    DACOUT_1280x1470P_50     = 21,           // JUST FOR U3 DAC OUTPUT 1080P TIMING USAGE
    DACOUT_1280x1470P_60     = 22,           // JUST FOR U3 DAC OUTPUT 1080P TIMING USAGE
    DACOUT_3840x2160P_24     = 23,           // JUST FOR U3 DAC OUTPUT 1080P TIMING USAGE
    DACOUT_3840x2160P_25     = 24,           // JUST FOR U3 DAC OUTPUT 1080P TIMING USAGE
    DACOUT_3840x2160P_30     = 25,           // JUST FOR U3 DAC OUTPUT 1080P TIMING USAGE

    DACOUT_3840x2160P_50    =26,
    DACOUT_3840x2160P_60    =27,
    DACOUT_4096x2160P_24    =28,
    DACOUT_4096x2160P_25    =29,
    DACOUT_4096x2160P_30    =30,

    DACOUT_4096x2160P_50    =31,
    DACOUT_4096x2160P_60    =32,

    PNL_WUXGA_CMO260_J2,           // 1920*1200
#if ENABLE_MFC
    MFC_DEFAULT,
    MFC120_FULLHD_CMO216_H1L01 = MFC_DEFAULT,
    MFC60_FULLHD_CMO216_H1L01,
#endif
#if ENABLE_TCON
    PNL_FULLHD_TCON,
#endif
    PNL_RES_MAX_NUM,
}PANEL_RESOLUTION_TYPE;

PanelType * MApi_XC_GetPanelSpec(PANEL_RESOLUTION_TYPE enResolutionType);
void MApi_PNL_En(MS_BOOL bPanelOn, MS_U16 u16PanelTiming);
void MApi_PNL_On(MS_U16 u16PanelOnTiming );
void MApi_PNL_Delay(MS_U32 ms);
void MApi_PNL_VCC_On(void);
void MApi_LPLL_On(MS_BOOL bEnable);
void MApi_PNL_SetBackLight(MS_BOOL bEnable);
PANEL_RESOLUTION_TYPE MApi_PNL_GetPnlTypeSetting(void);
void MApi_PNL_Dump(void);
MS_BOOL MApi_SetEnv2BootArgs(const char* name,const char* value);
MS_BOOL IsBootLogoValid(void);
#endif

