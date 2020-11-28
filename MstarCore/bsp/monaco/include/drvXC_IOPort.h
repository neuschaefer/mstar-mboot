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
/// @file    drvXC_IOPort.h
/// @brief  IO ports API
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _IOPORT_H_
#define _IOPORT_H_

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

///This Enum is interface for Hal and Application level.
typedef enum
{
    INPUT_PORT_NONE_PORT = 0,

    INPUT_PORT_ANALOG0 = 1,        // Data port
    INPUT_PORT_ANALOG1,
    INPUT_PORT_ANALOG2,
    INPUT_PORT_ANALOG3,
    INPUT_PORT_ANALOG4,

    // Reserved area

    INPUT_PORT_ANALOG0_SYNC = 10,  // Sync port
    INPUT_PORT_ANALOG1_SYNC,
    INPUT_PORT_ANALOG2_SYNC,
    INPUT_PORT_ANALOG3_SYNC,
    INPUT_PORT_ANALOG4_SYNC,

    // Reserved area

    INPUT_PORT_YMUX_CVBS0 = 30,
    INPUT_PORT_YMUX_CVBS1,
    INPUT_PORT_YMUX_CVBS2,
    INPUT_PORT_YMUX_CVBS3,
    INPUT_PORT_YMUX_CVBS4,
    INPUT_PORT_YMUX_CVBS5,
    INPUT_PORT_YMUX_CVBS6,
    INPUT_PORT_YMUX_CVBS7,
    INPUT_PORT_YMUX_G0,
    INPUT_PORT_YMUX_G1,
    INPUT_PORT_YMUX_G2,

    // Reserved area

    INPUT_PORT_CMUX_CVBS0 = 50,
    INPUT_PORT_CMUX_CVBS1,
    INPUT_PORT_CMUX_CVBS2,
    INPUT_PORT_CMUX_CVBS3,
    INPUT_PORT_CMUX_CVBS4,
    INPUT_PORT_CMUX_CVBS5,
    INPUT_PORT_CMUX_CVBS6,
    INPUT_PORT_CMUX_CVBS7,
    INPUT_PORT_CMUX_R0,
    INPUT_PORT_CMUX_R1,
    INPUT_PORT_CMUX_R2,

    // Reserved area

    INPUT_PORT_DVI0 = 80,
    INPUT_PORT_DVI1,
    INPUT_PORT_DVI2,
    INPUT_PORT_DVI3,

    // Reserved area

    INPUT_PORT_MVOP = 100,
    INPUT_PORT_MVOP2,
    INPUT_PORT_MVOP3,

    INPUT_PORT_SCALER_OP = 110,

} E_MUX_INPUTPORT;

///This Enum is interface for Hal and Application level.
typedef enum
{
    E_INPUT_NOT_SUPPORT_MHL = 0x0,
    E_INPUT_SUPPORT_MHL_PORT_DVI0 = 0x1,
    E_INPUT_SUPPORT_MHL_PORT_DVI1 = 0x2,
    E_INPUT_SUPPORT_MHL_PORT_DVI2 = 0x4,
    E_INPUT_SUPPORT_MHL_PORT_DVI3 = 0x8,
    E_INPUT_ALL_SUPPORT_MHL = 0xF,

}EN_MUX_INPUTPORT_MHL_INFO;

///This Enum is interface for Hal and Application level.
typedef enum
{
    OUTPUT_PORT_NONE_PORT = 0,

    OUTPUT_PORT_SCALER_MAIN_WINDOW = 1,
    OUTPUT_PORT_SCALER2_MAIN_WINDOW = 2,

    // Reserved area

    OUTPUT_PORT_SCALER_SUB_WINDOW1 = 10,
    OUTPUT_PORT_SCALER2_SUB_WINDOW = 11,

    // Reserved area

    OUTPUT_PORT_CVBS1 = 20,
    OUTPUT_PORT_CVBS2,

    // Reserved area

    OUTPUT_PORT_YPBPR1 = 40,
    OUTPUT_PORT_YPBPR2,

    // Reserved area

    OUTPUT_PORT_HDMI1 = 60,
    OUTPUT_PORT_HDMI2,

    // Reserved area

    OUTPUT_PORT_OFFLINE_DETECT = 80,

    // Reserved area
    OUTPUT_PORT_DWIN = 100,

} E_MUX_OUTPUTPORT;

#define IsAnalogPort(x)         ( (x) >= INPUT_PORT_ANALOG0 && (x) <= INPUT_PORT_ANALOG4 )
#define IsDVIPort(x)            ( (x) >= INPUT_PORT_DVI0 && (x) <= INPUT_PORT_DVI3 )
#define IsYCVBSPort(x)          ( (x) >= INPUT_PORT_YMUX_CVBS0 && (x) <= INPUT_PORT_YMUX_CVBS7 )
#define IsCCVBSPort(x)          ( (x) >= INPUT_PORT_CMUX_CVBS0 && (x) <= INPUT_PORT_CMUX_CVBS7 )
#define IsCVBSPort(x)           ( IsYCVBSPort(x) || IsCCVBSPort(x) )

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

#endif // _IOPORT_H_
