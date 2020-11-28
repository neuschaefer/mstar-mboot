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
#define MAPP_IR_C

//***********************************************************
//              Header Files
//***********************************************************
#include "datatype.h"
#include "msIR.h"
#include "msKeypad.h"
#include "MApp_IR.h"
#include "MApp_Key.h"
#include "MApp_Wakeup.h"

//***********************************************************
//              Macro Definitions
//***********************************************************
#define KEY_DEBUG(y)            y
#define KEY_NULL                0xFF

//***********************************************************
//              External Veriables
//***********************************************************


//***********************************************************
//              Local Veriables
//***********************************************************
static KEYSTAT stKeyStatus;

//***********************************************************
//              Global Veriables
//***********************************************************


//***********************************************************
//              External Functions
//***********************************************************
extern void SystemWholeChipReset(void);


//***********************************************************
//              Local Functions Definition
//***********************************************************
static void MApp_CheckKeyStatus(void)
{
    U8 key = NULL;
    U8 KeyRepeatStatus = NULL;

    if (msIR_GetIRKeyCode(&key, &KeyRepeatStatus) == MSRET_OK)
    {
        stKeyStatus.keytype = KEY_TYPE_IR;
        stKeyStatus.keydown = TRUE;
        stKeyStatus.keydata = key;
        stKeyStatus.keyrepeat = KeyRepeatStatus;
        KEY_DEBUG(printf("[IR]: Key = 0x%02X, Repeat = %d\r\n", key, KeyRepeatStatus));
    }
  #if (KEYPAD_TYPE_SEL != KEYPAD_TYPE_NONE)
    else if (msKeypad_GetKey(&key, &KeyRepeatStatus)== MSRET_OK)
    {
        stKeyStatus.keytype = KEY_TYPE_KEYPAD;
        stKeyStatus.keydown = TRUE;
        stKeyStatus.keydata = key;
        stKeyStatus.keyrepeat = KeyRepeatStatus;
        KEY_DEBUG(printf("[Keypad]: Key = 0x%02X, Repeat = %d \r\n", key, KeyRepeatStatus));

    }
  #endif
    else
    {
        stKeyStatus.keydown = FALSE;
        stKeyStatus.keydata = KEY_NULL;
        stKeyStatus.keyrepeat = FALSE;
    }

}

static void MApp_ParseKey(void)
{
    //check IR wakeup key
    if(stKeyStatus.keytype == KEY_TYPE_IR)
    {
        // Check if it is wakeup key
        if(MDrv_IR_IsWakeup(stKeyStatus.keydata))
        {
            //force it to power key
            u8KeyCode = KEY_WAKEUP;
            return;
        }
    }


    switch ( stKeyStatus.keydata )
    {
        case IRKEY_POWER:               u8KeyCode = KEY_POWER;              break;
        case IRKEY_UP:                  u8KeyCode = KEY_UP;                 break;
        case IRKEY_DOWN:                u8KeyCode = KEY_DOWN;               break;
        case IRKEY_RIGHT:               u8KeyCode = KEY_RIGHT;              break;
        case IRKEY_LEFT:                u8KeyCode = KEY_LEFT;               break;
        case IRKEY_SELECT:              u8KeyCode = KEY_SELECT;             break;

        case IRKEY_CHANNEL_PLUS:
            if ((stKeyStatus.keytype == KEY_TYPE_KEYPAD) ) //ZUI_TODO: &&
                u8KeyCode = KEY_UP;
            else
                u8KeyCode = KEY_CHANNEL_PLUS;
            break;

        case IRKEY_CHANNEL_MINUS:
            if ((stKeyStatus.keytype == KEY_TYPE_KEYPAD) )//ZUI_TODO: &&
                u8KeyCode = KEY_DOWN;
            else
                u8KeyCode = KEY_CHANNEL_MINUS;
            break;

        case IRKEY_VOLUME_PLUS:
            // special case : when in input select mode, the KEYPAD LEFT/RIGHT is interpreted as VolUP/VolDOWN
            if ((stKeyStatus.keytype == KEY_TYPE_KEYPAD) )//ZUI_TODO: &&
                u8KeyCode = KEY_VOLUME_PLUS;
            else if((stKeyStatus.keytype == KEY_TYPE_KEYPAD) )//ZUI_TODO: &&
                u8KeyCode = KEY_SELECT;
            else if((stKeyStatus.keytype == KEY_TYPE_KEYPAD) )//ZUI_TODO: &&
                u8KeyCode = KEY_RIGHT;
            else
                u8KeyCode = KEY_VOLUME_PLUS;
            break;

        case IRKEY_VOLUME_MINUS:
            if ((stKeyStatus.keytype == KEY_TYPE_KEYPAD) )//ZUI_TODO: &&
                u8KeyCode = KEY_VOLUME_MINUS;
            else if((stKeyStatus.keytype == KEY_TYPE_KEYPAD) )//ZUI_TODO: &&
                u8KeyCode = KEY_SELECT;
            else if((stKeyStatus.keytype == KEY_TYPE_KEYPAD) )//ZUI_TODO: &&
                u8KeyCode = KEY_LEFT;
            else
                u8KeyCode = KEY_VOLUME_MINUS;
            break;

        case IRKEY_MENU:                u8KeyCode = KEY_MENU;               break;
        case IRKEY_INPUT_SOURCE:        u8KeyCode = KEY_INPUT_SOURCE;       break;

        case IRKEY_NUM_0:               u8KeyCode = KEY_0;                  break;
        case IRKEY_NUM_1:               u8KeyCode = KEY_1;                  break;
        case IRKEY_NUM_2:               u8KeyCode = KEY_2;                  break;
        case IRKEY_NUM_3:               u8KeyCode = KEY_3;                  break;
        case IRKEY_NUM_4:               u8KeyCode = KEY_4;                  break;
        case IRKEY_NUM_5:               u8KeyCode = KEY_5;                  break;
        case IRKEY_NUM_6:               u8KeyCode = KEY_6;                  break;
        case IRKEY_NUM_7:               u8KeyCode = KEY_7;                  break;
        case IRKEY_NUM_8:               u8KeyCode = KEY_8;                  break;
        case IRKEY_NUM_9:               u8KeyCode = KEY_9;                  break;

        case IRKEY_EXIT:                u8KeyCode = KEY_EXIT;               break;
        case IRKEY_EPG:                 u8KeyCode = KEY_EPG;                break;
        case IRKEY_CHANNEL_RETURN:      u8KeyCode = KEY_CHANNEL_RETURN;     break;
        case IRKEY_BACK:                u8KeyCode = KEY_BACK;               break;
        case IRKEY_CHANNEL_FAV_LIST:    u8KeyCode = KEY_CHANNEL_FAV_LIST;   break;
        case IRKEY_MUTE:                u8KeyCode = KEY_MUTE;               break;
        case IRKEY_FREEZE:              u8KeyCode = KEY_FREEZE;             break;
        case IRKEY_INFO:                u8KeyCode = KEY_INFO;               break;
        case IRKEY_AUDIO:               u8KeyCode = KEY_AUDIO;              break;
        case IRKEY_MTS:                 u8KeyCode = KEY_MTS;                break;
        case IRKEY_ZOOM:                u8KeyCode = KEY_ZOOM;               break;
        case IRKEY_SUBTITLE:            u8KeyCode = KEY_SUBTITLE;           break;
        case IRKEY_UPDATE:              u8KeyCode = KEY_UPDATE;             break;        // add UPDATE key
        case IRKEY_TTX_MODE:            u8KeyCode = KEY_TTX_MODE;           break;
        case IRKEY_MIX:                 u8KeyCode = KEY_MIX;                break;
        case IRKEY_TTX:                 u8KeyCode = KEY_TTX;                break;
        case IRKEY_SIZE:                u8KeyCode = KEY_SIZE;               break;
        case IRKEY_HOLD:                u8KeyCode = KEY_HOLD;               break;
        case IRKEY_INDEX:               u8KeyCode = KEY_INDEX;              break;
        case IRKEY_CHANNEL_LIST:        u8KeyCode = KEY_CHANNEL_LIST;       break;
        case IRKEY_SLEEP:               u8KeyCode = KEY_SLEEP;              break;
        case IRKEY_DASH:                u8KeyCode = KEY_DASH;               break;
        //Because some IR key codes are defined un-correctly, so we have to change key mapping below.
        case IRKEY_BACKWARD:            u8KeyCode = KEY_PREVIOUS;           break;
        case IRKEY_FORWARD:             u8KeyCode = KEY_NEXT;               break;
        case IRKEY_PAGE_DOWN:           u8KeyCode = KEY_PAGE_DOWN;          break;
        case IRKEY_PREVIOUS:            u8KeyCode = KEY_FF;                 break;
        case IRKEY_NEXT:                u8KeyCode = KEY_REWIND;             break;
        case IRKEY_CC:                  u8KeyCode = KEY_CC;                 break;
        case IRKEY_ADJUST:              u8KeyCode = KEY_ADJUST;             break;
        case IRKEY_KEY_DISABLE_KEYPAD:  u8KeyCode = KEY_DISABLE_KEYPAD;     break;
        case IRKEY_REVEAL:              u8KeyCode = KEY_REVEAL;             break;
        case IRKEY_RECORD:              u8KeyCode = KEY_RECORD;             break;
        case IRKEY_STOP:                u8KeyCode = KEY_STOP;               break;
        case IRKEY_PLAY:                u8KeyCode = KEY_PLAY;               break;
        case IRKEY_PAUSE:               u8KeyCode = KEY_PAUSE;              break;
        case IRKEY_SUBPAGE:             u8KeyCode = KEY_SUBPAGE;            break;
        case IRKEY_RED:                 u8KeyCode = KEY_RED;                break;
        case IRKEY_GREEN:               u8KeyCode = KEY_GREEN;              break;
        case IRKEY_YELLOW:              u8KeyCode = KEY_YELLOW;             break;
        case IRKEY_BLUE:                u8KeyCode = KEY_BLUE;               break;
        case IRKEY_RED2:                u8KeyCode = KEY_RED;                break;
        case IRKEY_GREEN2:              u8KeyCode = KEY_GREEN;              break;
        case IRKEY_TV_INPUT:            u8KeyCode = KEY_TV_INPUT;           break;
        case IRKEY_DTV:                 u8KeyCode = KEY_DTV;                break;
        case IRKEY_TV:                  u8KeyCode = KEY_TV;                 break;
        case IRKEY_PC:                  u8KeyCode = KEY_PC;                 break;
        case IRKEY_COMPONENT:           u8KeyCode = KEY_COMPONENT;          break;
        case IRKEY_SV:                  u8KeyCode = KEY_SV;                 break;

    #if (IR_MODE_SEL != IR_TYPE_SWDECODE_SHA_MODE)
        case IRKEY_HOME:                u8KeyCode = KEY_HOME;               break;
        case IRKEY_PICTURE:             u8KeyCode = KEY_PICTURE;            break;
        case IRKEY_CLOCK:               u8KeyCode = KEY_CLOCK;              break;
        case IRKEY_SCART:               u8KeyCode = KEY_SCART;              break;
        case IRKEY_HDMI:                u8KeyCode = KEY_HDMI;               break;
        case IRKEY_AV:                  u8KeyCode = KEY_AV;                 break;
    #endif

        default:                        u8KeyCode = KEY_NULL;               break;
    }

}


//***********************************************************
//              Global Functions Definition
//***********************************************************
void MApp_ProcessUserInput(void)
{
    MApp_CheckKeyStatus();

    if ( stKeyStatus.keydown )
    {
        MApp_ParseKey();
    }

    switch (u8KeyCode)
    {
        case KEY_POWER:
            if ( stKeyStatus.keytype == KEY_TYPE_KEYPAD )
            {
                msAPI_Power_NotifyWakeupDeviceForAP(WakeUp_by_SAR);
                SystemWholeChipReset();
            }
            break;
        case KEY_WAKEUP:
            if ( stKeyStatus.keytype == KEY_TYPE_IR )
            {
                msAPI_Power_NotifyWakeupDeviceForAP(WakeUp_by_IR);
                SystemWholeChipReset();
            }
            break;
        default:
            break;

    }
    u8KeyCode = KEY_NULL;
}

//#############
//
//  IR, Keypad
//
//#############
U8 MApp_GetKeyCode(void)
{
    return u8KeyCode;
}

BOOLEAN MApp_IsKeyRepeat(void)
{
    return (stKeyStatus.keyrepeat) ? TRUE : FALSE;
}

void MApp_IR_Init(void)
{
//    printf(" Initialize IR \r\n");
#if 1
     msIR_Initialize_Isr();
#else
    msIR_Initialize(12);
#endif
    msIR_ProcessUserKey(TRUE);
}

void MApp_Keypad_Init(void)
{
//    printf(" Initialize Keypad \r\n");

    msKeypad_Init();
}



#undef MAPP_IR_C

