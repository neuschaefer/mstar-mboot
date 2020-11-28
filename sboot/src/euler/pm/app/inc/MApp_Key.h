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
////////////////////////////////////////////////////////////////////////////////

#ifndef MAPP_KEY_H
#define MAPP_KEY_H

#include "Board.h"

typedef enum
{
    KEY_CHANNEL_FAV_LIST    = 0x00,             //IR_KEY_FAV
    KEY_CHANNEL_RETURN      = 0x01,             //IR_KEY_FLASHBK
    KEY_CHANNEL_PLUS        = 0x02,             //IR_KEY_CH_UP
    KEY_CHANNEL_MINUS       = 0x03,             //IR_KEY_CH_DOWN

    KEY_AUDIO               = 0x04,             //IR_KEY_SOUND
    KEY_VOLUME_PLUS         = 0x05,             //IR_KEY_VOL_UP
    KEY_VOLUME_MINUS        = 0x06,             //IR_KEY_VOL_DOWN

    KEY_UP                  = 0x07,             //IR_KEY_UP_ARROW
    KEY_POWER               = 0x08,             //IR_KEY_POWER
    KEY_EXIT                = 0x09,             //IR_KEY_EXIT
    KEY_MENU                = 0x0A,             //IR_KEY_MENU
    KEY_DOWN                = 0x0B,             //IR_KEY_DOWN_ARROW
    KEY_LEFT                = 0x0C,             //IR_KEY_LEFT_ARROW
    KEY_SELECT              = 0x0D,             //IR_KEY_ENTER
    KEY_BACK                = 0x0E,             //IR_KEY_BACK
    KEY_RIGHT               = 0x0F,             //IR_KEY_RIGHT_ARROW

    KEY_0                   = 0x10,             //IR_KEY_0
    KEY_1                   = 0x11,             //IR_KEY_1
    KEY_2                   = 0x12,             //IR_KEY_2
    KEY_3                   = 0x13,             //IR_KEY_3
    KEY_4                   = 0x14,             //IR_KEY_4
    KEY_5                   = 0x15,             //IR_KEY_5
    KEY_6                   = 0x16,             //IR_KEY_6
    KEY_7                   = 0x17,             //IR_KEY_7
    KEY_8                   = 0x18,             //IR_KEY_8
    KEY_9                   = 0x19,             //IR_KEY_9

    KEY_MUTE                = 0x1A,             //IR_KEY_MUTE

    KEY_INFO                = 0x1B,             //IR_KEY_INFO
    KEY_RED                 = 0x1C,             //IR_KEY_RED
    KEY_GREEN               = 0x1D,             //IR_KEY_GREEN
    KEY_MTS                 = 0x1E,             //IR_KEY_SAP
    KEY_SUBTITLE            = 0x1F,

    KEY_INPUT_SOURCE        = 0x20,             //IR_KEY_INPUT
    KEY_PICTURE             = 0x21,             //IR_KEY_PICTURE

    KEY_SOUND               = 0x22,

    KEY_ZOOM                = 0x23,             //IR_KEY_RATIO
    KEY_DASH                = 0x24,             //IR_KEY_DASH
    KEY_SLEEP               = 0x25,             //IR_KEY_TIMER
    KEY_EPG                 = 0x26,

    KEY_HOLD                = 0x27,             //IR_KEY_HOLD

    KEY_ADJUST              = 0x28,             //IR_KEY_ADJST
    KEY_TV_INPUT            = 0x29,

    KEY_P_CHECK             = 0x2A,
    KEY_S_CHECK             = 0x2B,
    KEY_POWERONLY           = 0x2C,
    KEY_BRIGHTNESS_PLUS     = 0x2D,
    KEY_BRIGHTNESS_MINUS    = 0x2E,

    // TTX keys
    KEY_YELLOW              = 0x2F,
    KEY_BLUE                = 0x30,
    KEY_TTX                 = 0x31,
    KEY_SIZE                = 0x32,
    KEY_MIX                 = 0x33,
    KEY_INDEX               = 0x34,
    KEY_TV_RADIO            = 0x35,
    KEY_REVEAL              = 0x36,
    KEY_CHANNEL_LIST        = 0x37,
    KEY_TIME                = 0x38,     // prevent to display TIME window when press TIME key ( no teletext channel )
    KEY_CLOCK               = 0x39,
    KEY_TTX_MODE            = 0x3A,
    KEY_UPDATE              = 0x3B,     // add UPDATE key

    DSC_KEY_PWRON           = 0x3C,
    DSC_KEY_PWROFF          = 0x3D,
    DSC_KEY_ARC4X3          = 0x3E,
    DSC_KEY_ARC16X9         = 0x3F,
    DSC_KEY_ARCZOOM         = 0x40,
    DSC_KEY_TV              = 0x41,
    DSC_KEY_VIDEO1          = 0x42,
    DSC_KEY_VIDEO2          = 0x43,
    DSC_KEY_VIDEO3          = 0x44,
    DSC_KEY_COMP1           = 0x45,
    DSC_KEY_COMP2           = 0x46,
    DSC_KEY_RGBPC           = 0x47,
    DSC_KEY_RGBDTV          = 0x48,
    DSC_KEY_RGBDVI          = 0x49,
    DSC_KEY_HDMI1           = 0x4A,
    DSC_KEY_HDMI2           = 0x4B,
    DSC_KEY_MULTI_PIP       = 0x4C,
    DSC_KEY_MULTIMEDIA      = 0x4D,
    DSC_KEY_DVIPC           = 0x4E,

    KEY_MMI                 = 0x4F,
    KEY_MMI_ENTER_MENU      = 0x50,
    KEY_UARTDEBUGPORT       = 0x51,
    KEY_PAUSE               = 0x52,
    KEY_PLAY                = 0x53,
    KEY_RECORD                 = 0x54,
    KEY_STOP                   = 0x55,
    KEY_SUBCODE             = 0x56,
    KEY_DA                  = 0x57,
    KEY_SUBPAGE             = 0x58,
    KEY_DVD                 = 0x59,
    KEY_COUNTDOWN_EXIT_TT_SUBTITLE  = 0x5A,
    KEY_EPGTIMER_COUNTDOWN     = 0x5B,

    KEY_DTV                    = 0x5C,
    KEY_TV                       = 0x5D,
    KEY_SCART                   = 0x5E,
    KEY_COMPONENT               = 0x5F,
    KEY_PC                       = 0x60,
    KEY_HDMI                   = 0x61,
    KEY_AV                    = 0x62,
    KEY_SV                    = 0x63,
    KEY_FREEZE              = 0x64,             //IR_KEY_FREEZE
    KEY_FF                  = 0x65,
    KEY_REWIND              = 0x66,
    KEY_NEXT                = 0x67,
    KEY_PREVIOUS            = 0x68,
    KEY_PAGE_UP             = 0x69,
    KEY_PAGE_DOWN           = 0x6A,
    KEY_CC                  = 0x6B,
    KEY_VOLUME              = 0x6C,
    KEY_PIP                 = 0x6D,
    KEY_DMP                 = 0x6E,  
    KEY_NET                 = 0x6F,   
    KEY_HOME                 = 0x70,   
    
    KEY_UNION               = 0x71,        
    KEY_PREORDIAN           = 0x72,        
    KEY_FAV                 = 0x73,    
    KEY_AUDIO_CONTROL       = 0x74,    
    KEY_FUNTION             = 0x75,        
    KEY_ORIGNAL_SOUND       = 0x76,    
    KEY_SELECTED_SONG       = 0x77,    
    KEY_PRIORITY            = 0x78,    
    KEY_DELETE              = 0x79,    
    KEY_SCORE               = 0x7A,    
    KEY_COOCAA_TV           = 0x7B,
    KEY_VII                 = 0x7C,        
    KEY_SHUTSHORT           = 0x7D,        
    KEY_SELECT_SONG         = 0x7E,

    KEY_WAKEUP              = 0xFD,
    KEY_DISABLE_KEYPAD      = 0xFE,
    KEY_NULL                = 0xFF
} EN_KEY;

#endif // MAPP_KEY_H

