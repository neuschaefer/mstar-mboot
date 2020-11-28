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
#include <stddef.h>
#include <exports.h>
#include <MsCmdTable.h>
#include <config.h>

#include <MsBoot.h>
#include <ShareType.h>
#include <CusConfig.h>
#include <bootlogo/MsPoolDB.h>
#include <bootlogo/iniparser.h>
#include <drvPM.h>
#include <bootlogo/MsBootLogo.h>

#if CONFIG_RESCUE_ENV  && CONFIG_RESCUE_ENV_IR_TRIGGER
#include <MsSystem.h>
#endif

#define WDT_TIMEOUT_DEFAULT 60
#define WDT_TIMEOUT_MIN 5
#define WDT_TIMEOUT_ENV_STR "WDT_TIMEOUT"

void App_Register_Process(void)
{
#if CONFIG_RESCUE_ENV
#if CONFIG_RESCUE_ENV_AUTO_TRIGGER
    Add_Command_Table ("BrickTerminator" , 0, STAGE_PROCESS);
#else
#if CONFIG_RESCUE_ENV_IR_TRIGGER
    {
        unsigned int u32Value = 0;
        char *pEnv = getenv(BRICK_TERMINATOR_IR_TRIGGERED_STRING);
        if(NULL != pEnv)
        {
            u32Value = (unsigned int)simple_strtoul(pEnv, NULL, 10);
            if(1 == u32Value)
            {
                Add_Command_Table ("BrickTerminator" , 0, STAGE_PROCESS);
            }
        }
    }
#endif //CONFIG_RESCUE_ENV_IR_TRIGGER
#endif //CONFIG_RESCUE_ENV_AUTO_TRIGGER
#endif //CONFIG_RESCUE_ENV
    Add_Command_Table ("sync_mmap" , 0, STAGE_PROCESS);
    #if defined (CONFIG_SECURITY_BOOT)
    Add_Command_Table ("SecureInit" , 0, STAGE_PROCESS);
    #endif
    #ifdef CONFIG_DISPLAY_VERSIONINFO
    Add_Command_Table ("mversion" , 0, STAGE_PROCESS);
    #endif
    Add_Command_Table ("bootargs_set" , 0, STAGE_PROCESS);
    Add_Command_Table ("config2env" , 0, STAGE_PROCESS);
}

//you can type "showtb 0" in mboot console to see registered cmd.
void App_Register_ToKernel(void)
{
    // Add_Command_Table ("delay 0" , 0, STAGE_TOKERNEL);
    #if (CONFIG_VESTEL_MB97 == 1)  //ENHANCE_BOOTING_TIME
    MS_U8 u8RTCSrc=FALSE;
    MS_U8 u8CmdFlag=E_NewSPI;
    char* plogoEnv = NULL;

    plogoEnv = getenv("logo");
    u8CmdFlag = get_cmd_flag();

    switch(MDrv_PM_GetWakeupSource()&0x0F)
    {
        case E_PM_WAKEUPSRC_RTC:
        case E_PM_WAKEUPSRC_RTC2:
            u8RTCSrc = TRUE;
            break;
        default:
            u8RTCSrc = FALSE;
            break;
    }

    if( ( u8RTCSrc == TRUE ) || ( ( u8CmdFlag != E_NewSPI ) && ( ( u8CmdFlag & E_HasBootLogo ) == 0 ) ) || ( u8CmdFlag == E_NewSPI ) )
    {
        if ( 0 != strcmp(plogoEnv ,"0") )
        {
            printf("[LOGO] setenv logo 0\n");
            setenv("logo","0");
            saveenv();
        }
    }
    else
    {
        if ( 0 != strcmp(plogoEnv ,"1") )
        {
            printf("[LOGO] setenv logo 1\n");
            setenv("logo","1");
            saveenv();
        }
    }
    #elif (CONFIG_VESTEL_MB100 == 1)
    //#if  (CONFIG_VESTEL_MB97 == 1) || (CONFIG_VESTEL_MB100 == 1) //ORI : JOHNNY
    static char Logo_Path[BUFFER_SIZE];
    U32 filesize = 0;
    char *scr = NULL;
    MS_U8 u8RTCSrc=FALSE;

    switch(MDrv_PM_GetWakeupSource()&0x0F)
    {
        case E_PM_WAKEUPSRC_RTC:
        case E_PM_WAKEUPSRC_RTC2:
            u8RTCSrc = TRUE;
            break;
        default:
            u8RTCSrc = FALSE;
            break;
    }

    vfs_mount(CONF);
    snprintf(Logo_Path,sizeof(Logo_Path),"%s/boot0.jpg",CUSTOMER_LOGO_PATH);

    if( (vfs_getsize(Logo_Path)==-1) ||(u8RTCSrc==TRUE))
    {
        setenv("logo","0");
        saveenv();
    }
    else
    {
        setenv("logo","1");
        saveenv();
    }

#endif
#if (CONFIG_PANEL_INIT)
    #if (ENABLE_MSTAR_PUMABOOT==0)
    Add_Command_Table ("panel_pre_init" , 0, STAGE_TOKERNEL);
    #endif
#endif
#if defined(CONFIG_ENABLE_4K2K_PANEL)
#if defined(CONFIG_INX_NOVA_VB1)
    Add_Command_Table("inx_panel_set_init", 0, STAGE_TOKERNEL);
#endif
#endif

#if(ENABLE_OSDC_Init==1)
    Add_Command_Table ("xc_init" , 0, STAGE_TOKERNEL);
#endif

#if(ENABLE_CVBS_OUT==1)
    Add_Command_Table ("cvbs" , 0, STAGE_TOKERNEL);
#endif

#if (ENABLE_HDMI_TX == 1)
    #if (ENABLE_MSTAR_PUMABOOT==0)
    Add_Command_Table ("hdmi init" , 0, STAGE_TOKERNEL);
    #endif
#endif

    Add_Command_Table ("pm_power_test" , 0, STAGE_TOKERNEL);
#if (CONFIG_ENABLE_RTPM)
    Add_Command_Table ("runtime_pm" , 0, STAGE_TOKERNEL);
#endif

#if defined (CONFIG_URSA6_VB1)
    Add_Command_Table ("send_I2C_cmd_to_ursa6" , 0, STAGE_TOKERNEL);
#endif

    #ifdef CONFIG_DISPLAY_LOGO
#if 1  //ENHANCE_BOOTING_TIME
    #if defined(CONFIG_BOOTLOGO_4K2K)
        #define BOOTLOGO "bootlogo 0 0 1 1 boot0.jpg"
    #elif (ENABLE_MSTAR_KENYA == 1)
        #define BOOTLOGO "bootlogo 0 0 1 1 bootlogo.jpg"
    #else
        #if ( CONFIG_VESTEL_MB97 == 1 )
            if ( ( ( u8CmdFlag & E_HasBootLogo ) == 0 ) || ( u8CmdFlag == E_NewSPI ) )
            {
                MsDrvGOP_Init();  //force update GOP MUX setting also no bootlogo case.
                printf("[LOGO] No define BOOTLOGO\n");
            }
            else
            {
                printf("[LOGO] Have define BOOTLOGO\n");
                #define BOOTLOGO "bootlogo"
            }
        #else
            #define BOOTLOGO "bootlogo"
        #endif
    #endif
#else
    #if defined(CONFIG_BOOTLOGO_4K2K) || (CONFIG_VESTEL_MB97 == 1)
        #define BOOTLOGO "bootlogo 0 0 1 1 boot0.jpg"
    #elif (ENABLE_MSTAR_KENYA == 1)
        #define BOOTLOGO "bootlogo 0 0 1 1 bootlogo.jpg"
    #else
        #define BOOTLOGO "bootlogo"
    #endif
#endif
    char* opt_logo = NULL;



    opt_logo = getenv("logo");
    if(opt_logo != NULL)
    {
        int logo_on = 0;
        logo_on = simple_strtol(opt_logo, NULL, 10);
        if(logo_on > 0 && logo_on < 3)
        {
#if ( CONFIG_VESTEL_MB97 == 1 )
            if ( ( u8CmdFlag != E_NewSPI ) && ( u8CmdFlag & E_HasBootLogo ) )
            {
                printf("[LOGO] STAGE_TOKERNEL 1\n");
                // enable black pattern in MOD layer to avoid issue SENTOR-4164
		Write2Byte(0x103204, 0x0);
		Write2Byte(0x103206, 0x0);
		Write2Byte(0x103208, 0x0);
		Write2Byte(0x103202, 0x8000);
                Add_Command_Table (BOOTLOGO , 0, STAGE_TOKERNEL);
            }
            else
            {
                printf("[LOGO] STAGE_TOKERNEL 2\n");
            }
#else
            Add_Command_Table (BOOTLOGO , 0, STAGE_TOKERNEL);
#endif

            #if defined (CONFIG_URSA_6M40)
            Add_Command_Table ("ursa_lvds_on" , 0, STAGE_TOKERNEL);
            #endif
			#if defined (CONFIG_URSA_8)
            Add_Command_Table ("ursa8_lvds_on" , 0, STAGE_TOKERNEL);
			#endif
        }
    }
    else
    {
#if ( CONFIG_VESTEL_MB97 == 1 )
            if ( ( u8CmdFlag != E_NewSPI ) && ( u8CmdFlag & E_HasBootLogo ) )
            {
                printf("[LOGO] STAGE_TOKERNEL 3\n");
                Add_Command_Table (BOOTLOGO , 0, STAGE_TOKERNEL);
            }
            else
            {
                printf("[LOGO] STAGE_TOKERNEL 4\n");
            }
#else
            Add_Command_Table (BOOTLOGO , 0, STAGE_TOKERNEL);
#endif

            #if defined (CONFIG_URSA_6M40)
            Add_Command_Table ("ursa_lvds_on" , 0, STAGE_TOKERNEL);
            #endif
    }
    #endif

#if ENABLE_BOOT_SPI_ECOS
        Add_Command_Table ("read_boot_info" , 0, STAGE_TOKERNEL);
#endif

#if defined(CONFIG_INX_VB1) && defined(CONFIG_BOOTLOGO_4K2K)
        Add_Command_Table("panel_inx_vb1_init",0,STAGE_TOKERNEL);
#endif

    #ifdef CONFIG_POWER_MUSIC
    char* opt_music = NULL;
    opt_music = getenv("music");
    if(opt_music != NULL)
    {
        int music_on = 0;
        music_on = simple_strtol(opt_music, NULL, 10);
        if(music_on > 0 && music_on < 3)
        {
            Add_Command_Table ("bootmusic" , 0, STAGE_TOKERNEL);
        }
    }
    else
    {
        Add_Command_Table ("bootmusic" , 0, STAGE_TOKERNEL);
    }
    #endif

    #if (CONFIG_MSTAR_FASTBOOT_ENABLE)
    Add_Command_Table ("fastboot" , 0, STAGE_TOKERNEL);
    #endif

    #ifdef CONFIG_GENERIC_MMC
		Add_Command_Table ("mmc slcrelwrchk" , 0, STAGE_TOKERNEL);
    #endif
#if (CONFIG_WDT)
    {
        char cmd[CMD_BUF] = {};
        unsigned int u32Timeout = WDT_TIMEOUT_DEFAULT;
        char *pEnv = getenv(WDT_TIMEOUT_ENV_STR);

        if(pEnv != NULL)
        {
            u32Timeout = (unsigned int)simple_strtol(pEnv, NULL, 10);
        }

        // If set to 0, WDT will be disabled(required by Vestel for debugging usage), so we will skip this if block when WDT_TIMEOUT_ENV_STR is 0
        if((u32Timeout > 0) && (u32Timeout < WDT_TIMEOUT_MIN) ) // NOTE: should not be too short to prevent infinite reboot 
        {
            printf("%s: Incorrect WDT TIMEOUT, should be not less than '%u', at %d\n", __func__, WDT_TIMEOUT_MIN, __LINE__);
            u32Timeout = WDT_TIMEOUT_MIN;
        }
        printf("Setting WDT time-out to %u\n",u32Timeout);
        
        memset(cmd, 0, sizeof(cmd));
        sprintf(cmd, "wdt_enable %u", u32Timeout);
        Add_Command_Table (cmd , 0, STAGE_TOKERNEL);
    }
#endif
#if defined (CONFIG_INX_NOVA_VB1)
    Add_Command_Table ("inx_nova_set_4k2k_2division", 0, STAGE_TOKERNEL);
#endif
#if defined (CONFIG_URSA_8)
        Add_Command_Table ("ursa8_set_osd_mode" , 0, STAGE_TOKERNEL);
#endif
#if defined (CONFIG_URSA_6M40)
        Add_Command_Table ("ursa_set_osd_mode" , 0, STAGE_TOKERNEL);
#endif

    Add_Command_Table ("uart_rx" , 0, STAGE_TOKERNEL);

#if (ENABLE_MODULE_TEE==1) // alway in bottom
     //move to main.c
     //Add_Command_Table ("SecureBootCmd" , 0, STAGE_TOKERNEL);
#endif

}

