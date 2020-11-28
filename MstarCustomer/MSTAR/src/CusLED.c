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
//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <command.h>
#include <common.h>
#include <drvMBX.h>
#include <MsDebug.h>
#include <MsOS.h>
#include <MsSystem.h>
#include <ShareType.h>
#include <drvGPIO.h>
//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------


typedef enum
{
    //Aeon-->51 Command Index
    PM_CMDIDX_INIT = 0x01,                  /// PM Command Index is INIT
    PM_CMDIDX_GET_STATUS = 0x02,            /// PM Command Index is GET STATUS
    PM_CMDIDX_GET_LIBVER = 0x03,            /// PM Command Index is GET LIBVER
    PM_CMDIDX_POWER_DOWN = 0x04,            /// PM Command Index is POWER DOWN
    PM_CMDIDX_RTC_INIT = 0x05,              /// PM Command Index is RTC INIT
    PM_CMDIDX_RTC_SETCOUNTER = 0x06,        /// PM Command Index is SET COUNTER
    PM_CMDIDX_RTC_GETCOUNTER = 0x07,        /// PM Command Index is GET COUNTER
    PM_CMDIDX_RTC_SETMATCHCOUNTER = 0x08,   /// PM Command Index is SET MATCH COUNTER
    PM_CMDIDX_RTC_GETMATCHCOUNTER = 0x09,   /// PM Command Index is GET MATCH COUNTER
    PM_CMDIDX_GET_INFO = 0x0A,              /// PM Command Index is GET INFO
    PM_CMDIDX_GET_MASTERKEY = 0x0B,
    PM_CMDIDX_GET_DEVICEID = 0x0C,
    PM_CMDIDX_GET_CHIPID = 0x0D,
    PM_CMDIDX_GPIO_INIT = 0x0E,

    PM_CMDIDX_SET_ONBOARD_LED = 0x11,
    PM_CMDIDX_SET_POWER_LED_N_PROGRAM_TIMER_LED = 0x12,
    PM_CMDIDX_GET_SYSTEM_ALIVE_STATUS    = 0x23,
    PM_CMDIDX_WDT_STATUS  = 0x24,
    PM_CMDIDX_UPATE_POWER_LED_STATUS = 0X25,

    PM_CMDIDX_ACK_51ToAEON = 0x30,          /// PM Command Index is ACK 51 To AEON

    //51->Aeon Command Index
    PM_CMDIDX_ACK_AEONTo51 = 0xA0,          /// PM Command Index is ACK AEON To 51

} PM_CmdIndex;


typedef enum
{
    E_ON_BOARD_LED_OFF= 0,
    E_ON_BOARD_LED_PATTERN_1 = 1,
    E_ON_BOARD_LED_PATTERN_2 = 2,
    E_ON_BOARD_LED_PATTERN_3 = 3,
    E_ON_BOARD_LED_PATTERN_4 = 4,
    E_ON_BOARD_LED_PATTERN_5 = 5,
    E_ON_BOARD_LED_ON= 255,
} USB_LED_PATTERN;

typedef enum
{
    E_ON_BOARD_LED_STAGE_BIST= 0,
    E_ON_BOARD_LED_STAGE_MBOOT_SUCCESS=1,
    E_ON_BOARD_LED_STAGE_APL_SUCCESS= 2,
    E_ON_BOARD_LED_STAGE_UPDATE_SW= 3,
    E_ON_BOARD_LED_STAGE_MBOOT_FAIL=4,    
} ON_BOARD_LED_STAGE;

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
U8 Is_MBX_Init = FALSE;

//-------------------------------------------------------------------------------------------------
//  Extern Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Private Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void do_Led_Flicker_Control(void)
{
    static U8 u8LedStatus = 0;
    if(u8LedStatus != 0)
    { 
        LED_RED_ON();
    }
    else
    {
        LED_RED_OFF();
    }
    u8LedStatus = ~u8LedStatus;
}
  
MS_S32 g_s32TimerID = -1;
void SetTimerIsrDone(void)
{
    if(g_s32TimerID >= 0)
    {
        MsOS_StopTimer(g_s32TimerID);
        MsOS_DeleteTimer(g_s32TimerID);
        g_s32TimerID = -1;
        printf("\nTimer ISR finished\n");
    }
}

void TimerISR(MS_U32 u32Tick,MS_U32 u32TimerID)
{
    u32Tick    = u32Tick;
    u32TimerID = u32TimerID;
    do_Led_Flicker_Control();
}

void do_Timer_ISR_Register(MS_U32 u32Timer)
{
    if(g_s32TimerID == -1)
    {
        g_s32TimerID = MsOS_CreateTimer( (TimerCb)TimerISR,
                                                      0,
                                                      u32Timer,
                                                      TRUE,
                                                      "Check timer");
        if(g_s32TimerID >= 0)
            printf("\t Creat Timer Success,TimerId = %ld\n",g_s32TimerID);
        else
            printf("\t Creat Timer Failed...\n");
    }
}

MS_BOOL SetOnBoardLED(U8 u8Pattern, U8 u8Stage)
{
    MS_BOOL bRet = FALSE;

    MBX_Msg stMsg;
    MBX_Result  eMBXRet = E_MBX_ERR_NOT_INITIALIZED;

 if(Is_MBX_Init == FALSE)
 {
     MsApi_MBX_Init();
     eMBXRet = MDrv_MBX_RegisterMSG(E_MBX_CLASS_PM_WAIT, 6);
     if(E_MBX_SUCCESS != eMBXRet)
     {
         printf("E_MBX_CLASS_PM_WAIT - MBX register msg error\n");
     }
     Is_MBX_Init=TRUE;
 }

    memset(&stMsg, 0, sizeof(MBX_Msg));

    stMsg.eRoleID = E_MBX_ROLE_PM;
    stMsg.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    stMsg.u8Ctrl = 0;
    stMsg.u8MsgClass = E_MBX_CLASS_PM_NOWAIT;
    stMsg.u8Index = PM_CMDIDX_SET_ONBOARD_LED;
    stMsg.u8ParameterCount = 2;
    stMsg.u8Parameters[0] = u8Pattern;
    stMsg.u8Parameters[1] = u8Stage;

    if(((eMBXRet = MDrv_MBX_SendMsg(&stMsg)) != E_MBX_SUCCESS))
    {
        printf(">>>Send Mail fail: 0x%x.\n", eMBXRet);
        bRet = FALSE;
    }
    else
    {
        bRet = TRUE;
    }

    return bRet;
}

int do_led(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    char u8Pattern_mode= 0;
    int interval_time =0;    
    if (argc < 1)
    {
        cmd_usage(cmdtp);
    }        

	if(strncmp(argv[1], "mbx", 4) == 0) 
	{
		if(IsHouseKeepingBootingMode()==FALSE) // boot from 51
		{	
			u8Pattern_mode=simple_strtoul(argv[2],NULL,16);          
			SetOnBoardLED(u8Pattern_mode, E_ON_BOARD_LED_STAGE_UPDATE_SW);
		}
		else		
		{
			UBOOT_INFO("It must be 51 booting!!\n");
		}
	}	
    else if(strncmp(argv[1], "time",5) == 0) 
    {
        interval_time=simple_strtoul(argv[2],NULL,16);  //timer
        do_Timer_ISR_Register(interval_time);
    }        
    else if(strncmp(argv[1], "stop",5) == 0) 
    {
		SetTimerIsrDone();
    }
    else
    {
		cmd_usage(cmdtp);
    }
    
    return 0;    
}

