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
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
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
/// @file  drvmiu.h
/// @brief MIU header file
/// @author MStar Semiconductor Inc.
///
////////////////////////////////////////////////////////////////////////////////
#ifndef _API_XC_CUS_H_
#define _API_XC_CUS_H_

#ifdef _API_XC_CUS_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

#define ENABLE_HDTV                 ENABLE
#if (ENABLE_HDTV == 1)
    #define SUPPORT_EURO_HDTV       DISABLE
#else
    #define SUPPORT_EURO_HDTV       DISABLE
#endif

#define ENABLE_RGB_SUPPORT_85HZ     (0)
#define ENABLE_3D_PROCESS           0

//------------------------------
// Mode index
//------------------------------
typedef enum
{
    MD_640x350_70,  // 0
#if ENABLE_RGB_SUPPORT_85HZ
    MD_640x350_85,
#endif //#if ENABLE_RGB_SUPPORT_85HZ
    MD_640x350_60,  // 1
    MD_720x400_70,  // 2
#if ENABLE_RGB_SUPPORT_85HZ
    MD_640x400_85,
#endif // #if ENABLE_RGB_SUPPORT_85HZ
    MD_640x400_70,    // 3
#if ENABLE_RGB_SUPPORT_85HZ
    MD_720x400_85,
#endif // #if ENABLE_RGB_SUPPORT_85HZ
    MD_640x480_60,    // 4
    MD_640x480_66,    // 5
    MD_640x480_72,    // 6
    MD_640x480_75,    // 7
#if ENABLE_RGB_SUPPORT_85HZ
    MD_640x480_85,
#endif // #if ENABLE_RGB_SUPPORT_85HZ
    MD_800x600_56,    // 8
    MD_800x600_60,    // 9
    MD_800x600_72,    //10
    MD_800x600_75,  // 11
#if ENABLE_RGB_SUPPORT_85HZ
    MD_800x600_85,
#endif // #if ENABLE_RGB_SUPPORT_85HZ
    MD_832x624_75,  // 12
    MD_848x480_59,    // 13
#if ENABLE_RGB_SUPPORT_85HZ
    MD_1024x768_43I,
#endif // #if ENABLE_RGB_SUPPORT_85HZ
    MD_1024x768_60, // 14
    MD_1024x768_70, // 15
    MD_1024x768_75, // 16
#if ENABLE_RGB_SUPPORT_85HZ
    MD_1024x768_85,
#endif //#if ENABLE_RGB_SUPPORT_85HZ
    MD_1152x864_60, // 17
    MD_1152x864_70, // 18
    MD_1152x864_75, // 19
#if ENABLE_RGB_SUPPORT_85HZ
    MD_1152x864_85,
#endif // #if ENABLE_RGB_SUPPORT_85HZ
    MD_1152x870_75, // 20
    MD_1280x768_60, // 21
    MD_1280x768_75, // 22
    MD_1280x960_60, // 23
    MD_1280x960_75, // 24
#if ENABLE_RGB_SUPPORT_85HZ
    MD_1280x960_85,
#endif // #if ENABLE_RGB_SUPPORT_85HZ
    MD_1280x1024_60, // 25
    MD_1280x1024_59, // 26
    MD_1280x1024_72, // 27
    MD_1280x1024_75, // 28
    MD_1280x1024_76, // 29
#if ENABLE_RGB_SUPPORT_85HZ
    MD_1280x1024_85,
#endif // #if ENABLE_RGB_SUPPORT_85HZ
    MD_1600x1200_59, // 30
    MD_1600x1200_60, // 31
    MD_1600x1200_65, // 32
    MD_1600x1200_70, // 33
    MD_1600x1200_75, // 34
    MD_1920x1200_59, // 35
    MD_1920x1200_60, // 36
    MD_1920x1200_65, // 37
    MD_1920x1200_75, // 38
    MD_1400x1050_59, // 39
    MD_1400x1050_60, // 40
    MD_1400x1050_75, // 41
    MD_1440x900_60_RB,  // 42
    MD_1440x900_75,  // 43
    MD_1680x1050_59, // 44
    MD_1680x1050_60, // 45
    MD_1680x1050_75, // 46

    /*++ Component Mode ++*/
    MD_720x480_60I,  // 47
    MD_720x480_60P,  // 48
    MD_720x576_50I,  // 49
    MD_720x576_50P,  // 50
    MD_1280x720_50P, // 51
    MD_1280x720_60P, // 52
    MD_1920x1080_50I,// 53
    MD_1920x1080_60I,// 54
#if (SUPPORT_EURO_HDTV)
    MD_1920x1080_50I_EURO,
#endif
    MD_1920x1080_24P, // 55
    MD_1920x1080_25P,//56
    MD_1920x1080_30P, // 57
    MD_1920x1080_50P, // 58
    MD_1920x1080_60P, // 59
    MD_720x480_60I_P, // 60 patch for DVD 480i -> Sherwood -> component output -> OSD unsupport mode
    MD_1280X1470_50P, // 61
    MD_1280X1470_60P, // 62
    MD_1920X2205_24P, // 63
    /*-- Component Mode --*/

    MD_1152x870_60,   // 64
    MD_1280x800_60,      // 65
    MD_1280x800_75,      // 66
    MD_1600x1024_60,  // 67
    MD_1600x1024_75,  // 68
    MD_1600x900_60,      // 69
    MD_1600x900_75,      // 70
    MD_1280x720_75,      // 71
    MD_640x480_57,    // 72
    MD_1360x768_60,      // 73
    MD_1600x1200_51,  // 74
    MD_848x480_60,    // 75
    MD_1280x768_50,      // 76
    MD_1366x768_60,   // 77
    MD_720X576_60,    // 78
    MD_864X648_60,    // 79
    MD_1920X1080_60,  // 80
    MD_720X480_60,    // 81

    MD_1440x900_60,  // 82
    MD_1280x768_60_RB,  // 83
    MD_1280x720_25P, // 84
    MD_1280x720_30P, // 85
    MD_STD_MODE_MAX_INDEX, // 86

    YPBPR_MD_START = MD_720x480_60I,
    YPBPR_MD_END = MD_1920x1080_60P,
    //PC_MD_END = YPBPR_MD_START - 1
}EN_MODE_TYPE;

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

INTERFACE MS_PCADC_MODETABLE_TYPE* MApi_XC_GetModeTable(void);
INTERFACE MS_U8 MApi_XC_GetTotalModeCount(void);




////////////////////////////////////////////////////////////////////////////////
#undef INTERFACE
#endif /* _API_XC_CUS_H_ */

