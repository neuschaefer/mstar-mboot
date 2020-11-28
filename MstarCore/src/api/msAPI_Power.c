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

#define _MSPOWER_C_

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <common.h>
#include <command.h>
#include <MsTypes.h>
#include <MsIRQ.h>
#include <MsOS.h>
#include <ShareType.h>
#include <MsSystem.h>
#include <drvPM.h>
#include <drvMBX.h>
#include <drvBDMA.h>
#include <IR_MSTAR_DTV.h>
#include <msAPI_Power.h>

#if (CONFIG_BINARY_RELEASE)
#include <MsMBootConfig.h>
#endif

//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define PM_MBX_QUEUESIZE 6
#define PM_CMDIDX_GLOBAL_CHIP_RESET 0x21

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Extern Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Private Functions
//-------------------------------------------------------------------------------------------------

extern BOOLEAN msAPI_IR_Initialize(void);
extern BOOLEAN msAPI_KeyPad_Initialize(void);

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------



static int str_cfg = 0;
MS_BOOL msAPI_PM_MBX_Init(void)
{
    MsApi_MBX_Init();
    if( E_MBX_SUCCESS != MDrv_MBX_RegisterMSG(E_MBX_CLASS_PM_NOWAIT, PM_MBX_QUEUESIZE))
    {
        printf("E_MBX_CLASS_PM_NOWAIT - MBX register msg error\n");
    }
   return TRUE;
    }


MS_BOOL msAPI_PM_Reset(void)
    {
    MBX_Msg MB_Command;
    printf("\033[0;33m Do mailbox init\033[0m\n");

    msAPI_PM_MBX_Init();
    memset((void*)&MB_Command, 0, sizeof(MBX_Msg));
    MB_Command.eRoleID = E_MBX_ROLE_PM;
    MB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    MB_Command.u8Ctrl = 0;
    MB_Command.u8MsgClass = E_MBX_CLASS_PM_NOWAIT;
    MB_Command.u8Index = PM_CMDIDX_GLOBAL_CHIP_RESET;
    MB_Command.u8ParameterCount = 0;
    printf("\033[0;33m Send reset message tp PM51.\033[0m\n\n");
    MDrv_MBX_SendMsg(&MB_Command);
        return TRUE;

}

EN_POWER_ON_MODE msAPI_Power_QueryPowerOnMode(void)
{
    U8 u8PowerDownMode =  (U8)MDrv_PM_PowerOnMode();

    switch ( u8PowerDownMode )
    {
        // DC ON
        case PM_MODE_STANBY:    // 0x01
        case PM_MODE_SLEEP:     // 0x02
        case PM_MODE_DEEPSLEEP: // 0x03
        {
            printf("DC on\n");
            return EN_POWER_DC_BOOT;
        }
        // AC ON
        case PM_MODE_DEFAULT:   // 0xFF
        {
            printf("AC on\n");
            return EN_POWER_AC_BOOT;
        }
        // EXCEPTION
        default:
        {
            if(u8PowerDownMode == 0xF1)
                printf("DC on !! \n");
            else
                printf("read PM_SLEEP_AC_DC_ON error\n");

            return EN_POWER_DC_BOOT;
        }
    }
}
void msAPI_SetSPIOffsetForMCU(void)
{
    MDrv_BDMA_SetSPIOffsetForMCU();
}
void msAPI_Power_PowerDown_EXEC(void)
{

    PM_Result pmResult;
    static PM_PowerDownCfg PmPowerDownCfg;
#if 0//eric.peng
    MDrv_BDMA_SetSPIOffsetForMCU();
#endif
    if(msAPI_PM_MBX_Init()==FALSE)
    {
        return;
    }
    //MDrv_MBX_SetDbgLevel(MBX_DBG_LEVEL_ALL);
    //MDrv_PM_SetDbgLevel(E_PM_DBGLV_INFO);

	//To Do: MDrv_PM_Check_Version is used on checking PM version(zeo 2.0 or not?). However, the utopia driver for A5 doesn't update to the newest.
    // So the current head file doen't include this protoype.
    if(MDrv_PM_Check_Version(TRUE))
	{
    // Initialize IR before power down
    msAPI_IR_Initialize();
    }

    // Initialize SAR before power down
    msAPI_KeyPad_Initialize();

    static PM_WakeCfg PmWakeCfg =
    {
        .bPmWakeEnableIR = TRUE,
        .bPmWakeEnableSAR = TRUE,
        .bPmWakeEnableGPIO0 = FALSE,
        .bPmWakeEnableGPIO1 = FALSE,
        .bPmWakeEnableUART1 = FALSE,
        .bPmWakeEnableSYNC = FALSE,
        .bPmWakeEnableESYNC = FALSE,

        .bPmWakeEnableRTC0 = TRUE,
        .bPmWakeEnableRTC1 = TRUE,
        .bPmWakeEnableDVI0 = FALSE,
        .bPmWakeEnableDVI2 = FALSE,
        #if (ENABLE_MSTAR_NUGGET==1)
        .bPmWakeEnableCEC = TRUE,
        #else
		.bPmWakeEnableCEC = FALSE,
		#endif
        .bPmWakeEnableAVLINK = FALSE,
		.u8PmStrMode = TRUE,

        .u8PmWakeIR =
        {   //IR wake-up key define
            IRKEY_POWER, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF
        },

        .u8PmWakeIR2 =
        {   //IR wake-up key define
            IRKEY_POWER, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF
        }
    };
#if (CONFIG_BINARY_RELEASE)
	PmWakeCfg.bPmWakeEnableIR     =  (mboot_config.pm_wakeup_source & ( 1 << 0 )) ? 1 : 0;
	PmWakeCfg.bPmWakeEnableSAR    =  (mboot_config.pm_wakeup_source & ( 1 << 1 )) ? 1 : 0;
	PmWakeCfg.bPmWakeEnableGPIO0  =  (mboot_config.pm_wakeup_source & ( 1 << 2 )) ? 1 : 0;
	PmWakeCfg.bPmWakeEnableGPIO1  =  (mboot_config.pm_wakeup_source & ( 1 << 3 )) ? 1 : 0;
	PmWakeCfg.bPmWakeEnableUART1  =  (mboot_config.pm_wakeup_source & ( 1 << 4 )) ? 1 : 0;
	PmWakeCfg.bPmWakeEnableSYNC   =  (mboot_config.pm_wakeup_source & ( 1 << 5 )) ? 1 : 0;
	PmWakeCfg.bPmWakeEnableESYNC  =  (mboot_config.pm_wakeup_source & ( 1 << 6 )) ? 1 : 0;
	PmWakeCfg.bPmWakeEnableRTC0   =  (mboot_config.pm_wakeup_source & ( 1 << 7 )) ? 1 : 0;
	PmWakeCfg.bPmWakeEnableRTC1   =  (mboot_config.pm_wakeup_source & ( 1 << 8 )) ? 1 : 0;
	PmWakeCfg.bPmWakeEnableDVI0   =  (mboot_config.pm_wakeup_source & ( 1 << 9 )) ? 1 : 0;
	PmWakeCfg.bPmWakeEnableDVI2   =  (mboot_config.pm_wakeup_source & ( 1 << 10 )) ? 1 : 0;
	PmWakeCfg.bPmWakeEnableCEC    =  (mboot_config.pm_wakeup_source & ( 1 << 11 )) ? 1 : 0;
	PmWakeCfg.bPmWakeEnableAVLINK =  (mboot_config.pm_wakeup_source & ( 1 << 12 )) ? 1 : 0;
#endif
    char* s = getenv(POWER_KEY_NAME);
    if (s)
    {
        PmWakeCfg.u8PmWakeIR[0] = simple_strtoul(s, NULL, 16);
    }
	PmWakeCfg.u8PmStrMode = str_cfg;
    //printf("PM_Init...\n");
    flush_cache((MS_U32)&PmWakeCfg, sizeof(PM_WakeCfg));
    pmResult= MDrv_PM_Init((PM_WakeCfg*)VA2PA((MS_U32) &PmWakeCfg));


    PmPowerDownCfg.u8WakeAddress = E_PM_WAKE_ZERO ;//E_PM_LAST_TWOSTAGE_POWERDOWN;
    PmPowerDownCfg.u8PowerDownMode = E_PM_STANDBY;//E_PM_STANDBY;//E_PM_SLEEP;

    flush_cache((MS_U32)&PmPowerDownCfg, sizeof(PmPowerDownCfg));
    //printf("\n\r==== Enter Standby Mode !! ==== %d \n",(int)pmResult);
    MDrv_PM_PowerDown((PM_PowerDownCfg*)VA2PA((MS_U32) &PmPowerDownCfg));

    while(1);
}
void msAPI_Power_SetStrConfig(int para)
{
    str_cfg = para;
}