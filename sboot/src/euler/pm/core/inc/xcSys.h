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
#ifndef XC_SYS_H
#define XC_SYS_H

////////////////////////////////////////////////////////////////////////////////

#include "Enum_Device.h"
#include "drvXC_IOPort.h"
#include "apiXC.h"
#include "xc_Analog_Reg.h"
#include "apiXC_ModeParse.h"
#include "apiXC_Cus.h"
#include "MApp_Wakeup.h"

////////////////////////////////////////////////////////////////////////////////

#ifdef  _XC_SYS_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

////////////////////////////////////////////////////////////////////////////////


typedef struct
{
    XC_MODEPARSE_RESULT eModeParseResult;           ///< the result after mode parse

    XC_MODEPARSE_INPUT_INFO sModeParseInputInfo;    ///< prepare the input info for mode parse

    MS_U16 u16Hperiod;
} PCMode_Info;
INTERFACE PCMode_Info gXC_PCMode_Info;

////////////////////////////////////////////////////////////////////////////////

#define MST_XTAL_CLOCK_HZ           FREQ_12MHZ

#define MST_H_PERIOD_MASK           0x3FFF
#define MST_V_TOTAL_MASK            0x0FFF

////////////////////////////////////////////////////////////////////////////////

#define ENABLE_IP_AUTO_COAST        0
#define ENABLE_VGA_EIA_TIMING       0
#define ENABLE_VGA_JUST_CHECK_SYNC  0


#if ENABLE_VGA_EIA_TIMING
#define MIN_HFREQ_OF_RGB            140
#else
#define MIN_HFREQ_OF_RGB            270
#endif
#define MAX_HFREQ_OF_RGB            950

#if ENABLE_VGA_EIA_TIMING
#define MIN_VFREQ_OF_RGB            240
#else
#define MIN_VFREQ_OF_RGB            470
#endif

#if ENABLE_RGB_SUPPORT_85HZ
#define MAX_VFREQ_OF_RGB            870
#else
#define MAX_VFREQ_OF_RGB            770
#endif

#define MIN_VTOTAL_OF_RGB           415
#define MAX_VTOTAL_OF_RGB           1550

// Range of DVI OOR
#define MIN_HFREQ_OF_DVI            140
#define MAX_HFREQ_OF_DVI            950
#define MIN_VFREQ_OF_DVI            230
#define MAX_VFREQ_OF_DVI            770
#define MIN_VTOTAL_OF_DVI           250
#define MAX_WIDTH_OF_DVI            1930
#define MAX_VTOTAL_OF_DVI           1300
#define MAX_HEIGHT_OF_DVI           1210

////////////////////////////////////////////////////////////////////////////////

// NONPM
#define REG_MIU0_BASE               0x101200
#define REG_MIU1_BASE               0x100600
#define REG_CHIPTOP_BASE            0x100B00
#define REG_UHC0_BASE               0x102400
#define REG_UHC1_BASE               0x100D00
#define REG_ADC_ATOP_BASE           0x102500
#define REG_ADC_DTOP_BASE           0x102600
#define REG_HDMI_BASE               0x102700
#define REG_IPMUX_BASE              0x102E00
#define REG_SCALER_BASE             0x102F00
#define REG_LPLL_BASE               0x103100
#define REG_MOD_BASE                0x103200
#define REG_AFEC_BASE               0x103500
#define REG_COMB_BASE               0x103600

#define REG_DVI_ATOP_BASE           0x110900
#define REG_DVI_DTOP_BASE           0x110A00
#define REG_DVI_EQ_BASE             0x110A80     // EQ started from 0x80
#define REG_HDCP_BASE               0x110AC0     // HDCP started from 0xC0
#define REG_ADC_DTOPB_BASE          0x111200     // ADC DTOPB





////////////////////////////////////////////////////////////////////////////////

INTERFACE void msDelayTime(U32 u32Delay);

INTERFACE void _MApi_XC_Sys_Init_XC(void);

INTERFACE XC_MODEPARSE_RESULT XC_GetModeParseResult(void);
INTERFACE void XC_Get_ModeStatus(void);

#if ENABLE_VGA_JUST_CHECK_SYNC
INTERFACE BOOLEAN XC_Check_HVSync(void);
INTERFACE void XC_Clear_HVSyncCount(void);
#endif

#if ENABLE_SC_BLOCK_SYNC_WAKEUP
INTERFACE void XC_Recovery_VGA(void);
#endif

////////////////////////////////////////////////////////////////////////////////

#undef INTERFACE

#endif // XC_SYS_H

