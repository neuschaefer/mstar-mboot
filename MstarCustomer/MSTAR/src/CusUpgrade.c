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
#include <common.h>
#include <MsTypes.h>
#include <CusUpgrade.h>
#include <CusUpgradeUtility.h>
#include <MsUpgrade.h>
#include <MsUpgradeUtility.h>
#include <MsSystem.h>
#include <MsUtility.h>
#include <MsVfs.h>
#include <MsDebug.h>
#include <fat.h>
#include <MsBoot.h>
#include <MsAppCB.h>
#include <MsOS.h>
#include <ursa/ursa_6m40.h>
#include <apiSWI2C.h>


#if (ENABLE_MODULE_USB == 1)
#include <usb.h>
#endif
#if (ENABLE_MODULE_DISPLAY_OSD==1)
int display_osd = 0;
#endif

//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define GWIN_WIDTH              720
#define GWIN_HEIGHT             576
#define GRAPHIC_WIDTH           600
#define GRAPHIC_HEIGHT          400
#define GRAPHIC_X               60
#define GRAPHIC_Y               88
#define LINE_HEIGHT             50
#define RECT_LEFT_INTERVAL      50

#if (CONFIG_BINARY_RELEASE)
#include <MsMBootConfig.h>
#define OAD_BIN_PATH            (char*)mboot_config.default_oad_bin_path
#define NET_BIN_PATH            (char*)mboot_config.default_net_bin_path
#define AP_BIN_PATH             (char*)mboot_config.default_ap_bin_path
#define MBOOT_BIN_PATH          (char*)mboot_config.default_mboot_bin_path
#define SBOOT_BIN_PATH          (char*)mboot_config.defalut_sboot_bin_path
#define URSA_BIN_PATH           (char*)mboot_config.default_ursa_bin_path
#define OTA_ZIP_PATH            (char*)mboot_config.default_ota_zip_path
#else
#define AP_BIN_PATH             getenv("ForceUpgradePath")==NULL?"/MstarUpgrade.bin":getenv("ForceUpgradePath")
#define OAD_BIN_PATH            AP_BIN_PATH
#define NET_BIN_PATH            AP_BIN_PATH
#define MBOOT_BIN_PATH          "/MbootUpgrade.bin"
#define SBOOT_BIN_PATH          "/SbootUpgrade.bin"
#define URSA_BIN_PATH           "/UrsaUpgrade.bin"
#define OTA_ZIP_PATH            "/update_signed.zip"
#endif

#define UPGRADE_STATE_URSA_BIN            (BIT0)
#define UPGRADE_STATE_SBOOT_BIN           (BIT1)
#define UPGRADE_STATE_MBOOT_BIN           (BIT2)
#define UPGRADE_STATE_AP_BIN              (BIT3)
//============for ISP Upgrade============
#if defined (CONFIG_URSA_6M40)
#define URSA7_UPGRADE_BIN_PATH  "/UrsaUpgrade.bin"

#define URSA_ISP_I2C_BUS_SEL 0x0
#define SPI_WRITE           0x10
#define SPI_READ            0x11
#define SPI_STOP            0x12

#define SLAVEADDR        0x98//  0x94//0x98

#define BANKSIZE    0x10000
#define BLOCKNUM  0xff
#define BLOCKSIZE 0x100

#define ENTER_ISP_ERROR_MAX     20
#define GET_ID_ERROR_MAX        10

#define  SW_IIC_READ             0
#define  SW_IIC_WRITE            1

MS_U8 g_ucFlashType;
MS_U8 g_ucBankNumber;
SFlashType sFlash;

MS_U8 g_u8CurPercent;
MS_U32 g_u32ISPSrcAddr;
MS_U32 g_u32ISPCodeSize;
FlashProgErrorType ErrorFlag;
FlashProgStateType g_eFlashProgramState;

#endif
//========ISP END=================

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
#if (CONFIG_DISPLAY_OSD)
static const U32 progress_max_value = 1000;

#if ((ENABLE_MODULE_USB == 1) || \
     (ENABLE_MODULE_NETUPDATE == 1) || \
     (ENABLE_MODULE_OAD == 1))
static U32 progress_cnt = 0;
static U32 progress_start_load_value = 10;
static U32 progress_finish_load_value = 200;
#endif

#endif

//-------------------------------------------------------------------------------------------------
//  Extern Functions
//-------------------------------------------------------------------------------------------------
extern int snprintf(char *str, size_t size, const char *fmt, ...);

//-------------------------------------------------------------------------------------------------
//  Private Functions
//-------------------------------------------------------------------------------------------------
#if (ENABLE_MODULE_USB == 1)
static int check_bin_flag(void);
#endif

#if (((ENABLE_MODULE_USB == 1)||(ENABLE_MODULE_NETUPDATE == 1)||(ENABLE_MODULE_OAD == 1))&&(ENABLE_MODULE_DISPLAY_OSD==1))
static int show_LoadData(int var);
static int show_StartUpgrading(int var);
static int show_Upgrading(int current_cnt, int total_cnt);
static int show_Error(int var);
static int show_Finish(int var);
#endif

//-------------------------------------------------------------------------------------------------
//  Public Functions
//-------------------------------------------------------------------------------------------------
#if (((ENABLE_MODULE_USB == 1)||(ENABLE_MODULE_NETUPDATE == 1)||(ENABLE_MODULE_OAD == 1))&&(ENABLE_MODULE_DISPLAY_OSD==1))
static int show_LoadData(int var)
{
    if (-1 == display_osd)
		return -1;
    char buffer[CMD_BUF]="\0";
    int ret = 0;
    UBOOT_TRACE("IN\n");
//TODO: find the root cause this line cause upgrade issue    run_command("led time 1000",0);
    progress_cnt = 0;
    progress_start_load_value = 10;
    progress_finish_load_value = 200;
    snprintf(buffer, CMD_BUF, "osd_create %d %d", GWIN_WIDTH, GWIN_HEIGHT);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    ret = run_command(buffer, 0);
    if (-1 == ret)
    {
    	display_osd = -1;
        return -1;
    }
    memset(buffer, 0 , CMD_BUF);
    snprintf(buffer, CMD_BUF, "draw_rect %d %d %d %d 0x800000ff", GRAPHIC_X, GRAPHIC_Y, GRAPHIC_WIDTH, GRAPHIC_HEIGHT);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    run_command(buffer, 0);
    memset(buffer, 0 , CMD_BUF);
    snprintf(buffer, CMD_BUF, "draw_string %d %d 0x3fffffff 1 LOADING DATA...", GRAPHIC_X, GRAPHIC_Y + LINE_HEIGHT * 2);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    run_command(buffer, 0);
    memset(buffer, 0 , CMD_BUF);
    snprintf(buffer, CMD_BUF, "draw_progress %d %d 0x3fffffff %d", GRAPHIC_X + RECT_LEFT_INTERVAL, GRAPHIC_Y + LINE_HEIGHT * 5, progress_start_load_value/10);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    run_command(buffer, 0);
    memset(buffer, 0 , CMD_BUF);
    snprintf(buffer, CMD_BUF, "osd_flush");
    UBOOT_DEBUG("cmd=%s\n",buffer);
    run_command(buffer, 0);
    UBOOT_TRACE("OK\n");
    return 0;
}

static int show_StartUpgrading(int var)
{
    if (-1 == display_osd)
		return -1;
    char buffer[CMD_BUF]="\0";
    UBOOT_TRACE("IN\n");
    snprintf(buffer, CMD_BUF, "draw_rect %d %d %d %d 0x800000ff", GRAPHIC_X, GRAPHIC_Y, GRAPHIC_WIDTH, GRAPHIC_HEIGHT);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    run_command(buffer, 0);
    memset(buffer, 0 , CMD_BUF);
    snprintf(buffer, CMD_BUF, "draw_string %d %d 0x3fffffff 1 UPGRADING SOFTWARE", GRAPHIC_X, GRAPHIC_Y + LINE_HEIGHT * 2);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    run_command(buffer, 0);
    memset(buffer, 0 , CMD_BUF);
    snprintf(buffer, CMD_BUF, "draw_string %d %d 0x3fffffff 1 PLEASE DO NOT TURN OFF", GRAPHIC_X,  GRAPHIC_Y + LINE_HEIGHT * 3);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    run_command(buffer, 0);
    memset(buffer, 0 , CMD_BUF);
    snprintf(buffer, CMD_BUF, "draw_progress %d %d 0x3fffffff %d", GRAPHIC_X + RECT_LEFT_INTERVAL, GRAPHIC_Y + LINE_HEIGHT * 5, progress_finish_load_value/10);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    run_command(buffer, 0);
    memset(buffer, 0 , CMD_BUF);
    snprintf(buffer, CMD_BUF, "osd_flush");
    run_command(buffer, 0);
    UBOOT_TRACE("OK\n");
    return 0;
}

static int show_Upgrading(int current_cnt, int total_cnt)
{
    if (-1 == display_osd)
		return -1;

    char buffer[CMD_BUF]="\0";
    UBOOT_TRACE("IN\n");
    progress_cnt = (((progress_max_value - progress_finish_load_value)*1000)/total_cnt); //(1000-200)/cmd_cnt
    progress_cnt = (progress_cnt *current_cnt+progress_finish_load_value*1000)/(10*1000);
    printf("--%d %%\n", progress_cnt);

    memset(buffer, 0 , CMD_BUF);
    snprintf(buffer, CMD_BUF, "draw_rect %d %d %d %d 0x800000ff", GRAPHIC_X, GRAPHIC_Y + LINE_HEIGHT * 5, GRAPHIC_WIDTH, LINE_HEIGHT);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    run_command(buffer, 0);
    memset(buffer, 0 , CMD_BUF);
    snprintf(buffer, CMD_BUF, "draw_progress %d %d 0x3fffffff %d", GRAPHIC_X + RECT_LEFT_INTERVAL,GRAPHIC_Y + LINE_HEIGHT * 5, progress_cnt);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    run_command(buffer, 0);
    memset(buffer, 0 , CMD_BUF);
    snprintf(buffer, CMD_BUF, "osd_flush");
    UBOOT_DEBUG("cmd=%s\n",buffer);
    run_command(buffer, 0);
    UBOOT_TRACE("OK\n");

    return 0;
}

static int show_Error(int var)
{
    if (-1 == display_osd)
		return -1;
    char buffer[CMD_BUF]="\0";
    UBOOT_TRACE("IN\n");
    memset(buffer, 0 , CMD_BUF);
    snprintf(buffer, CMD_BUF, "draw_rect %d %d %d %d 0x800000ff", GRAPHIC_X, GRAPHIC_Y, GRAPHIC_WIDTH, GRAPHIC_HEIGHT);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    run_command(buffer, 0);
    memset(buffer, 0 , CMD_BUF);
    snprintf(buffer, CMD_BUF, "draw_string %d %d 0x3fffffff 1 SOFTWARE UPGRADE ERROR", GRAPHIC_X, GRAPHIC_Y + LINE_HEIGHT * 3);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    run_command(buffer, 0);
    memset(buffer, 0 , CMD_BUF);
    snprintf(buffer, CMD_BUF, "osd_flush");
    UBOOT_DEBUG("cmd=%s\n",buffer);
    run_command(buffer, 0);
    run_command("led stop",0);
    UBOOT_TRACE("OK\n");
    return 0;
}

static int show_Finish(int var)
{
    if (-1 == display_osd)
		return -1;

    char buffer[CMD_BUF]="\0";
    UBOOT_TRACE("IN\n");
    memset(buffer, 0 , CMD_BUF);
    snprintf(buffer, CMD_BUF, "draw_rect %d %d %d %d 0x800000ff", GRAPHIC_X, GRAPHIC_Y, GRAPHIC_WIDTH, GRAPHIC_HEIGHT);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    run_command(buffer, 0);
    memset(buffer, 0 , CMD_BUF);
    snprintf(buffer, CMD_BUF, "draw_string %d %d 0x3fffffff 1 SOFTWARE UPGRADE COMPLETE", GRAPHIC_X, GRAPHIC_Y + LINE_HEIGHT * 2);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    run_command(buffer, 0);
    memset(buffer, 0 , CMD_BUF);
    snprintf(buffer, CMD_BUF, "draw_progress %d %d 0x3fffffff %d", GRAPHIC_X + RECT_LEFT_INTERVAL, GRAPHIC_Y + LINE_HEIGHT * 5, 100);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    run_command(buffer, 0);
    memset(buffer, 0 , CMD_BUF);
    snprintf(buffer, CMD_BUF, "osd_flush");
    UBOOT_DEBUG("cmd=%s\n",buffer);
    run_command(buffer, 0);
    udelay(2000000);
    run_command("led stop",0);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    UBOOT_TRACE("OK\n");
    return 0;
}
#endif


#if (ENABLE_MODULE_USB == 1)
static int check_bin_flag(void)
{
    int stage = 0;
    UBOOT_TRACE("IN\n");

    if(check_file_partition(AP_BIN_PATH,NULL,NULL)==0)//check Supernova file
    {
      stage |= UPGRADE_STATE_AP_BIN;
      UBOOT_DEBUG("has app upgrade bin\n");
    }

    if(check_file_partition(SBOOT_BIN_PATH,NULL,NULL)==0)//check sboot file
    {
      stage |= UPGRADE_STATE_SBOOT_BIN;
      UBOOT_DEBUG("has sboot upgrade bin\n");
    }

    if(check_file_partition(MBOOT_BIN_PATH,NULL,NULL)==0)//check mboot file
    {
      stage |= UPGRADE_STATE_MBOOT_BIN;
      UBOOT_DEBUG("has mboot upgrade bin\n");
    }
#if defined (CONFIG_URSA_6M40)
    if(check_file_partition(URSA7_UPGRADE_BIN_PATH,NULL,NULL)==0)//check mboot file
    {
        stage |= UPGRADE_STATE_URSA_BIN;
        UBOOT_DEBUG("has mboot upgrade bin\n");
    }
#else
    if(check_file_partition(URSA_BIN_PATH,NULL,NULL)==0)//check ursa file
    {
      stage |= UPGRADE_STATE_URSA_BIN;
      UBOOT_DEBUG("has ursa upgrade bin\n");
    }
#endif
    UBOOT_TRACE("OK\n");

    return stage;
}

int do_custar(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{

    char cmd[128];
    char upgrade_state_flag[] = "0x00";
    char* env_state = NULL;
    int state=0;
    UBOOT_TRACE("IN\n");
    //usb init
    if (-1 == appInitUsbDisk())
    {
       printf("FAIL : can not init usb!! \n");
       return -1;
    }

    #if (ENABLE_MODULE_DISPLAY_OSD==1)
	UnRegisterShowCb();
	RegisterCBShowError((show_Error_cb)show_Error);
	RegisterCBShowFinish((show_Finish_cb)show_Finish);
	RegisterCBShowLoadData((show_LoadData_cb)show_LoadData);
    RegisterCBShowStartUpgrading((show_StartUpgrading_cb)show_StartUpgrading);
    RegisterCBShowUpgrading((show_Upgrading_cb)show_Upgrading);
    #endif    

    //check upgrade file content
    env_state = getenv(ENV_FORCEUPGRADE);
    if(env_state != NULL )
    {
         state = (int)simple_strtoul(env_state, NULL, 16);
    }
    else
    {
        state=check_bin_flag();
        if(state == 0 )
        {
          UBOOT_INFO("warn!! no upgrade file in usb. \n");
          UBOOT_TRACE("OK\n");
          return 0;
        }
        snprintf(upgrade_state_flag, sizeof(upgrade_state_flag)-1, "0x%02x",state);
        setenv(ENV_FORCEUPGRADE,upgrade_state_flag);
        saveenv();
    }

    UBOOT_INFO("Current state ->[0x%x]\n",state);
#if defined (CONFIG_URSA_6M40)
    if(state&UPGRADE_STATE_URSA_BIN) // upgrade Ursa
    {
        UBOOT_DEBUG("cmd= ursa7_upgrade \n");
        if(-1 == run_command("ursa7_upgrade", 0))
        {
            UBOOT_ERROR("Upgrade Ursa error!\n");
            setenv(ENV_FORCEUPGRADE,NULL);
            return -1;
        }
        state = state&(~UPGRADE_STATE_URSA_BIN);
        UBOOT_INFO("Ursa 7 upgrade OK!~\n");
    }
#else
    if(state&UPGRADE_STATE_URSA_BIN) // upgrade Ursa
    {
        memset(cmd, 0, 128);
        snprintf(cmd, sizeof(cmd)-1, "ustar %s",URSA_BIN_PATH);
        UBOOT_DEBUG("cmd=%s\n",cmd);
        if(-1 == run_command(cmd, 0))
        {
            UBOOT_ERROR("Upgrade Ursa error!\n");
            setenv(ENV_FORCEUPGRADE,NULL);
            return -1;
        }
        state = state&(~UPGRADE_STATE_URSA_BIN);
        UBOOT_INFO("Ursa upgrade OK!~\n");
    }
#endif
    else if(state&UPGRADE_STATE_SBOOT_BIN)//upgrade Sboot
    {
        memset(cmd, 0, 128);
        snprintf(cmd, sizeof(cmd)-1, "ustar %s",SBOOT_BIN_PATH);
        UBOOT_DEBUG("cmd=%s\n",cmd);
        if(-1 == run_command(cmd, 0))
        {
            UBOOT_ERROR("Upgrade Sboot error!\n");
            setenv(ENV_FORCEUPGRADE,NULL);
            return -1;
        }
        state = state&(~UPGRADE_STATE_SBOOT_BIN);
        UBOOT_INFO("Sboot upgrade OK!~\n");
    }

    else if(state&UPGRADE_STATE_MBOOT_BIN)//upgrade Mboot
    {
        memset(cmd, 0, 128);
        snprintf(cmd, sizeof(cmd)-1, "ustar %s",MBOOT_BIN_PATH);
        UBOOT_DEBUG("cmd=%s\n",cmd);
        if(-1 == run_command(cmd, 0))
        {
            UBOOT_ERROR("Upgrade Mboot error!\n");
            setenv(ENV_FORCEUPGRADE,NULL);
            return -1;
        }
        state = state&(~UPGRADE_STATE_MBOOT_BIN);
        UBOOT_INFO("Mboot upgrade OK!~\n");
    }
    else if(state&UPGRADE_STATE_AP_BIN)//upgrade Supernova
    {
        memset(cmd, 0, 128);
        snprintf(cmd, sizeof(cmd)-1, "ustar %s",AP_BIN_PATH);
        UBOOT_DEBUG("cmd=%s\n",cmd);
        if(-1 == run_command(cmd, 0))
        {
            UBOOT_ERROR("Upgrade Application error!\n");
            setenv(ENV_FORCEUPGRADE,NULL);
            return -1;
        }
        state = state&(~UPGRADE_STATE_AP_BIN);
        UBOOT_INFO("AP upgrade OK!~\n");
    }

    if(state == 0)
    {
        UBOOT_INFO("All Upgrade File Had Finished !!\n");
        setenv(ENV_FORCEUPGRADE,NULL);
    }
    else
    {
        snprintf(upgrade_state_flag, sizeof(upgrade_state_flag)-1, "0x%02x",state);
        UBOOT_DEBUG("upgrade_state_flag=%s\n",upgrade_state_flag);
        setenv(ENV_FORCEUPGRADE,upgrade_state_flag);
    }
#ifdef CONFIG_BOOTCOUNT_LIMIT
    setenv ("bootcount", "0");
#endif
    setenv ("sync_mmap", "1");
    saveenv();
    UBOOT_TRACE("OK\n");
    run_command("reset",0);
    return 0;
}
#endif

#if (ENABLE_MODULE_OAD == 1)
int do_costar(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    char buffer[CMD_BUF] = "\0";
    int ret=0;

    UBOOT_TRACE("IN\n");
    #if (ENABLE_MODULE_DISPLAY_OSD==1)
    UnRegisterShowCb();
    RegisterCBShowError((show_Error_cb)show_Error);
    RegisterCBShowFinish((show_Finish_cb)show_Finish);
    RegisterCBShowLoadData((show_LoadData_cb)show_LoadData);
    RegisterCBShowStartUpgrading((show_StartUpgrading_cb)show_StartUpgrading);
    RegisterCBShowUpgrading((show_Upgrading_cb)show_Upgrading);
    #endif
    snprintf(buffer,CMD_BUF,"ostar %s",OAD_BIN_PATH);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    ret=run_command(buffer,0);
    if(ret==-1)
    {
        UBOOT_ERROR("do ostar fail\n");
        return -1;
    }

    UBOOT_TRACE("OK\n");
    return 0;
}
#endif

#if (ENABLE_MODULE_NETUPDATE == 1)
int do_cnstar(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    char buffer[CMD_BUF] = "\0";
    int ret=0;

    UBOOT_TRACE("IN\n");

    #if (ENABLE_MODULE_DISPLAY_OSD==1)
    UnRegisterShowCb();
    RegisterCBShowError((show_Error_cb)show_Error);
    RegisterCBShowFinish((show_Finish_cb)show_Finish);
    RegisterCBShowLoadData((show_LoadData_cb)show_LoadData);
    RegisterCBShowStartUpgrading((show_StartUpgrading_cb)show_StartUpgrading);
    RegisterCBShowUpgrading((show_Upgrading_cb)show_Upgrading);
    #endif
    snprintf(buffer,CMD_BUF,"nstar %s",NET_BIN_PATH);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    ret=run_command(buffer,0);
    if(ret==-1)
    {
        UBOOT_ERROR("do nstar fail\n");
        return -1;
    }

    UBOOT_TRACE("OK\n");
    return 0;
}


#endif

#if (ENABLE_MODULE_USB == 1)
int do_usb_bin_check(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    char cmd[128];
    int ret = -1;
    UBOOT_TRACE("IN\n");
    //usb init
    if (-1 == appInitUsbDisk())
    {
       printf("FAIL : can not init usb!! \n");
       return -1;
    }
    //we try usb upgrade first
    ret = check_file_partition(AP_BIN_PATH,NULL,NULL);
    if(ret == 0)
    {
        UBOOT_DEBUG("has app upgrade bin\n");
        memset(cmd, 0, 128);
        snprintf(cmd, sizeof(cmd)-1, "ustar %s",AP_BIN_PATH);
        UBOOT_DEBUG("cmd=%s\n",cmd);
        if(-1 == run_command(cmd, 0))
        {
            UBOOT_ERROR("Upgrade Application error!\n");
            return -1;
        }
        else
        {
            UBOOT_INFO("AP upgrade OK!~\n");
            UBOOT_TRACE("OK\n");
            run_command("reset",0);
            return 0;
        }
    }
    else
    {
        UBOOT_DEBUG("no %s in usb disk\n",AP_BIN_PATH);
    }
    return -1;
}
int do_ota_zip_check(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    char cmd[128];
    int ret = -1;
    UBOOT_TRACE("IN\n");
    //usb init
    if (-1 == appInitUsbDisk())
    {
       printf("FAIL : can not init usb!! \n");
       return -1;
    }
    char label[128] = "\0";
    char uuid[128] = "\0";
    struct bootloader_message p_msg;

    ret = check_file_partition(OTA_ZIP_PATH,NULL,NULL);
    if(ret == 0)//OTA upgrade
    {
        getFatVolumeLabel(label,uuid);
        UBOOT_DEBUG("label:%s\nuuid:%s\n",label,uuid);
        memset(cmd,0,128);
        memset(&p_msg,0,sizeof(struct bootloader_message));
        strcpy(p_msg.command,BOOT_MODE_RECOVERY_STR);
        strcpy(p_msg.recovery,"recovery\n");
        strcat(p_msg.recovery,"--update_package=/mnt/usb/sda1/update_signed.zip\n");
        strcat(p_msg.recovery,"--label=");
        strcat(p_msg.recovery,label);
        strcat(p_msg.recovery,"\n");
        strcat(p_msg.recovery,"--uuid=");
        strcat(p_msg.recovery,uuid);
        strcat(p_msg.recovery,"\n");
        UBOOT_DEBUG("command:%s\n",p_msg.recovery);
        #if (ENABLE_MODULE_MMC == 1)
        snprintf(cmd, sizeof(cmd)-1, "mmc write.p 0x%X misc 0x%x", &p_msg,sizeof(struct bootloader_message));
        #else
        snprintf(cmd, sizeof(cmd)-1, "nand write.e 0x%X misc 0x%x", &p_msg,sizeof(struct bootloader_message));
        #endif
        if(-1 == run_command(cmd,0))
        {
            UBOOT_ERROR("cmd:%s error\n",cmd);
            return -1;
        }
        UBOOT_INFO("OTA upgrade OK!~\n");
        UBOOT_TRACE("OK\n");
        return 0;
    }
    else
    {
        UBOOT_DEBUG("no %s in usb disk\n",OTA_ZIP_PATH);
        return -1;
    }
}
#endif

int do_wipe_datacache_check(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    char cmd[128];
    UBOOT_TRACE("IN\n");

    struct bootloader_message p_msg;
    memset(cmd,0,128);
    memset(&p_msg,0,sizeof(struct bootloader_message));
    strcpy(p_msg.command,BOOT_MODE_RECOVERY_STR);
    strcpy(p_msg.recovery,"recovery\n");
    if(0 == strcmp(argv[1],"data"))
    {
        strcat(p_msg.recovery,"--wipe_data\n");
    }
    if(0 == strcmp(argv[1],"cache"))
    {
        strcat(p_msg.recovery,"--wipe_cache\n");
    }
    UBOOT_DEBUG("command:%s\n",p_msg.recovery);
    #if (ENABLE_MODULE_MMC == 1)
        snprintf(cmd, sizeof(cmd)-1, "mmc write.p 0x%X misc 0x%x", &p_msg,sizeof(struct bootloader_message));
    #else
        snprintf(cmd, sizeof(cmd)-1, "nand write.e 0x%X misc 0x%x", &p_msg,sizeof(struct bootloader_message));
    #endif
    if(-1 == run_command(cmd,0))
    {
        UBOOT_ERROR("cmd:%s error\n",cmd);
        return -1;
    }
    UBOOT_INFO(" OK!~\n");
    UBOOT_TRACE("OK\n");
    return 0;
 }

#if (ENABLE_MODULE_SYSTEM_RESTORE == 1)
int do_systemrestore(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    char cmd[128];
    UBOOT_TRACE("IN\n");

    struct bootloader_message p_msg;
    memset(cmd,0,128);
    memset(&p_msg,0,sizeof(struct bootloader_message));
    strcpy(p_msg.command,BOOT_MODE_RECOVERY_STR);
    strcpy(p_msg.recovery,"recovery\n");
    strcat(p_msg.recovery,"--update_package=/systembackup/update_signed.zip\n");
    UBOOT_DEBUG("command:%s\n",p_msg.recovery);
    #if (ENABLE_MODULE_MMC == 1)
       snprintf(cmd, sizeof(cmd)-1, "mmc write.p 0x%X misc 0x%x", &p_msg,sizeof(struct bootloader_message));
    #else
       snprintf(cmd, sizeof(cmd)-1, "nand write.e 0x%X misc 0x%x", &p_msg,sizeof(struct bootloader_message));
    #endif
    if(-1 == run_command(cmd,0))
    {
       UBOOT_ERROR("cmd:%s error\n",cmd);
       return -1;
    }
    UBOOT_INFO(" OK!~\n");
    UBOOT_TRACE("OK\n");
    return 0;
}
#endif
//==============ISP functions for Upgrade===================
#if defined (CONFIG_URSA_6M40)
//------------------------------------------------------------------------------
SFlashType SupportSFlash[Flash_NUMS]=
{
// 1-4:size ,5:manufacturer_id,6:device_id,7:WREN,8:WRDI,9:RDSR,10:WRSR,11:READ,12:FAST_READ,
// 13:PG_PROG,14:SECTOR_ERASE,15:BLOCK_ERASE,16:CHIP_ERASE,17:RDID,18:LOCK,19-20: ChipEraseMaxTime

//                    1-4    ,5   ,6   ,7   ,8   ,9   ,10  ,11  ,12  ,13  ,14  ,15  ,16  ,17  ,18  ,19-20
//PMC
{/*"PMC25LV512A", */  0x20000,0x9D,0x7B,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD7,0xD8,0xC7,0xAB,0x0C,40  },
{/*" PMC25LV010", */  0x20000,0x9D,0x7C,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD7,0xD8,0xC7,0xAB,0x0C,40  },
{/*" PMC25LV020", */  0x40000,0x9D,0x7D,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD7,0xD8,0xC7,0xAB,0x0C,40  },
{/*" PMC25LV040", */  0x80000,0x9D,0x7E,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD7,0xD8,0xC7,0xAB,0x1C,40  },
//EON
{/*"    EN25P10", */  0x20000,0x1C,0x10,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x0C,80  },
{/*"    EN25P20", */  0x40000,0x1C,0x11,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x0C,80  },
{/*"    EN25P40", */  0x80000,0x1C,0x12,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,80  },
{/*"    EN25P80", */  0x100000,0x1C,0x13,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,80  },
{/*"    EN25F40", */  0x80000,0x1C,0x12,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,80  },
{/*"    EN25F80", */  0x100000,0x1C,0x13,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,220  },
{/*"    EN25F16", */  0x200000,0x1C,0x14,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,440  },
{/*"    EN25P16", */  0x80000,0x1C,0x14,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,220 },
{/*"    EN25B20", */  0x40000,0x1C,0x41,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x0C,80  },
{/*"    EN25B40", */  0x80000,0x1C,0x42,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,80  },
{/*"   EN25B40T", */  0x80000,0x1C,0x42,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,80  },
{/*"    EN25B16", */  0x80000,0x1C,0x34,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,220 },
{/*"   EN25B16T", */  0x80000,0x1C,0x34,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,220 },
{/*"    EN25B32", */  0x80000,0x1C,0x35,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,440 },
//                    1-4    ,5   ,6   ,7   ,8   ,9   ,10  ,11  ,12  ,13  ,14  ,15  ,16  ,17  ,18  ,19-20
//SPANSION
{/*"  S25FL004A", */  0x80000,0x01,0x12,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,260 },
{/*"  S25FL016A", */0x1000000,0x01,0x14,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,1000},
{/*"  S25FL040A", */  0x80000,0x01,0x25,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,260 },
//Winbond & NX
{/*"    NX25P16", */0x1000000,0xEF,0x15,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,250 },
{/*"     W25X10", */  0x20000,0xEF,0x10,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x0C,70  },
{/*"     W25X20", */  0x40000,0xEF,0x51,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,250 },
{/*"     W25X40", */  0x80000,0xEF,0x52,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,250 },
{/*"     W25P20", */  0x40000,0xEF,0x11,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,250 },
{/*"     W25P40", */  0x80000,0xEF,0x12,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,250 },
{/*"     W25X16", */  0x20000,0xEF,0x14,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x0C,256  },
{/*"     W25X32", */  0x40000,0xEF,0x15,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,512 },
{/*"     W25X64", */  0x80000,0xEF,0x16,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,1000 },
//SST
{/*"SST25VF016B", */0x1000000,0xBF,0x41,0x06,0x04,0x05,0x01,0x03,NULL,0xAD,0xD8,0xD8,0xC7,0xAB,0x1C,40  },
{/*"SST25VF040B", */  0x80000,0xBF,0x8D,0x06,0x04,0x05,0x01,0x03,NULL,0xAD,0xD8,0xD8,0xC7,0xAB,0x1C,40  },
//MX
{/*" MX25L4005A", */  0x80000,0xC2,0x12,0x06,0x04,0x05,0x01,0x03,0x0B,0x02,0x20,0xD8,0xC7,0xAB,0x1C,80  },
{/*" MX25L8005", */  0x100000,0xC2,0x13,0x06,0x04,0x05,0x01,0x03,0x0B,0x02,0x20,0xD8,0xC7,0xAB,0x1C,160  },
{/*"  MX25L2005", */  0x40000,0xC2,0x11,0x06,0x04,0x05,0x01,0x03,0x0B,0x02,0x20,0xD8,0xC7,0xAB,0x1C,50  },
{/*"  MX25L1605", */0x1000000,0xC2,0x14,0x06,0x04,0x05,0x01,0x03,0x0B,0x02,0x20,0xD8,0xC7,0xAB,0x1C,550 },
{/*"  MX25L3205", */0x1000000,0xC2,0x15,0x06,0x04,0x05,0x01,0x03,0x0B,0x02,0x20,0xD8,0xC7,0xAB,0x1C,750 },
{/*"  MX25L6405", */0x1000000,0xC2,0x16,0x06,0x04,0x05,0x01,0x03,0x0B,0x02,0x20,0xD8,0xC7,0xAB,0x1C,1000 },
//INTEL
{/*"QB25F160S33B8", */  0x20000,0x89,0x11,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD7,0xD8,0xC7,0xAB,0x0C,128  },
{/*"QB25F320S33B8", */  0x40000,0x89,0x12,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD7,0xD8,0xC7,0xAB,0x0C,256  },
{/*"QB25F640S33B8", */  0x80000,0x89,0x13,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD7,0xD8,0xC7,0xAB,0x1C,512  },
//AMIC
{/*" A25L40P", */  0x80000,0x37,0x13,0x06,0x04,0x05,0x01,0x03,0x0B,0x02,0x20,0xD8,0xC7,0xAB,0x1C,128  },
{/*" GD25Q32", */  0x40000,0xC8,0x16,0x06,0x04,0x05,0x01,0x03,0x0B,0x02,0x20,0xD8,0xC7,0xAB,0x1C,512  },
{/*" EN25Q32A", */  0x40000,0x1C,0x15,0x06,0x04,0x05,0x01,0x03,NULL,0x02,0xD8,0xD8,0xC7,0xAB,0x1C,256  },

};

MS_BOOL GetsFlashType(void)
{
    MS_U8 temp;
    MS_U8 ucTmpBuf[4];

    MDrv_Ursa_6M40__ReadChipJEDEC_ID(ucTmpBuf);
    printf("\n***ReadChipJEDEC_ID[%x]",ucTmpBuf[0]);
    switch(ucTmpBuf[0])
    {
         //AL
        case 0x37:
            printf("\n  AL or AMIC");
            temp=MDrv_Ursa_6M40_ReadChipID();
            printf("\n  AL or AMIC ChipID=%x",temp);
            if (temp == 0x12)
            {
                g_ucFlashType=Flash_A25L40P;
                g_ucBankNumber=8;
                printf("\n   A25L40P");
            }
            else
            {
              return FALSE;
            }
            break;
    ///////////////////////////////////////////////

        //PMC
        case 0x7F:
            printf("\n  PMC or AMIC");
            temp=MDrv_Ursa_6M40_ReadChipID();
            printf("\n  PMC or AMIC ChipID=%x",temp);
            if (temp == 0x7C)
            {
                g_ucFlashType=Flash_PMC010;
                g_ucBankNumber=2;
            }
            else if (temp == 0x7D)
            {
                g_ucFlashType=Flash_PMC020;
                g_ucBankNumber=4;
            }
            else if (temp == 0x7E)
            {
                g_ucFlashType=Flash_PMC040;
                g_ucBankNumber=8;
            }
            else if (temp == 0x12)
            {
                g_ucFlashType=Flash_A25L40P;
                g_ucBankNumber=8;
                printf("\n   A25L40P");
            }
            else
            {
                return FALSE;
            }
            break;
        //EON
        case 0x1C:
            printf("\n  EON");
            temp=MDrv_Ursa_6M40_ReadChipID();
            printf("\n  EON ChipID=%x",temp);
            if (ucTmpBuf[2] == 0x20)
            {
                if (ucTmpBuf[1] == 0x11 && temp == 0x10)
                {
                    g_ucFlashType = Flash_EN25P10;
                    g_ucBankNumber=2;
                    printf("\n   EN25P10");
                }
                else if (ucTmpBuf[1] == 0x12 && temp == 0x11)
                {
                    g_ucFlashType = Flash_EN25P20;
                    g_ucBankNumber=4;
                    printf("\n   EN25P20");
                }
                else if (ucTmpBuf[1] == 0x13 && temp == 0x12)
                {
                    g_ucFlashType = Flash_EN25P40;
                    g_ucBankNumber=8;
                    printf("\n   EN25P40");
                }
                else if (ucTmpBuf[1] == 0x14 && temp == 0x13)
                {
                    g_ucFlashType = Flash_EN25P80;
                    g_ucBankNumber=16;
                    printf("\n   EN25P80");
                }
                else if (ucTmpBuf[1] == 0x12 && temp == 0x41)
                {
                    g_ucFlashType = Flash_EN25B20;
                    g_ucBankNumber=4;
                    printf("\n   EN25B20");
                }
                else if (ucTmpBuf[1] == 0x13 && temp == 0x32)
                {
                    g_ucFlashType = Flash_EN25B40;
                    g_ucBankNumber=8;
                    printf("\n   EN25B40");
                }
                else if (ucTmpBuf[1] == 0x13 && temp == 0x42)
                {
                    g_ucFlashType = Flash_EN25B40T;
                    g_ucBankNumber=8;
                    printf("\n   EN25B40T");
                }
                else if (ucTmpBuf[1] == 0x15 && temp == 0x14)
                {
                    g_ucFlashType = Flash_EN25P16;
                    g_ucBankNumber = 32;
                    printf("\n   EN25P16");
                }
                else if (ucTmpBuf[1] == 0x15 && temp == 0x34)
                {
                    g_ucFlashType = Flash_EN25B16;
                    g_ucBankNumber = 32;
                    printf("\n   EN25B16");
                }
                else if (ucTmpBuf[1] == 0x15 && temp == 0x44)
                {
                    g_ucFlashType = Flash_EN25B16T;
                    g_ucBankNumber = 32;
                    printf("\n   EN25B16T");
                }
                else if (ucTmpBuf[1] == 0x16 && temp == 0x35)
                {
                    g_ucFlashType = Flash_EN25B32;
                    g_ucBankNumber = 64;
                    printf("\n   EN25B32");
                }
                else
                {
                    return FALSE;
                }
            }
            else if (ucTmpBuf[2] == 0x31)
            {
                if (ucTmpBuf[1] == 0x13 && temp == 0x12)
                {
                    g_ucFlashType = Flash_EN25F40;
                    g_ucBankNumber=8;
                    printf("\n   EN25F40");
                }
                else if (ucTmpBuf[1] == 0x14 && temp == 0x13)
                {
                    g_ucFlashType = Flash_EN25F80;
                    g_ucBankNumber=16;
                    printf("\n   EN25F80");
                }
                else if (ucTmpBuf[1] == 0x15 && temp == 0x14)
                {
                    g_ucFlashType = Flash_EN25F16;
                    g_ucBankNumber=32;
                    printf("\n   EN25F16");
                }
            }
            else if (ucTmpBuf[2] == 0x30)
            {
                if (ucTmpBuf[1] == 0x16 && temp == 0x15)
                {
                    g_ucFlashType = Flash_EN25Q32A;
                    g_ucBankNumber = 64;
                    printf("\n   EN25Q32A");
                }
            }
            else
                {
                    return FALSE;
                }
            break;
        case 0x01:
            printf("\n  SPANSION");
            printf("\n   chip ID=%x",ucTmpBuf[1]);
            if (ucTmpBuf[1] == 0x14)
            {
                g_ucFlashType = Flash_S25FL016A;
                g_ucBankNumber = 32;
                printf("\n   S25FL016A");
            }
            else if (ucTmpBuf[1] == 0x12)
            {
                g_ucFlashType = Flash_S25FL004A;
                g_ucBankNumber = 8;
                printf("\n   S25FL004A");
            }
            else if (ucTmpBuf[1] == 0x25)
            {
                g_ucFlashType = Flash_S25FL040A;
                g_ucBankNumber = 8;
                printf("\n   S25FL040A");
            }
            else
            {
                return FALSE;
            }
            break;
        case 0xEF:
            printf("\n  WINBOND & NX");
            if (ucTmpBuf[1] == 0x15 && ucTmpBuf[2] == 0x20)
            {
                g_ucFlashType = Flash_NX25P16;
                g_ucBankNumber = 32;
                printf("\n   NX25P16 or W25P16");
            }
            else if (ucTmpBuf[1] == 0x11 && ucTmpBuf[2] == 0x30)
            {
                g_ucFlashType = Flash_W25X10;
                g_ucBankNumber = 2;
                printf("\n   W25X10");
            }
            else if (ucTmpBuf[1] == 0x12 && ucTmpBuf[2] == 0x30)
            {
                g_ucFlashType = Flash_W25X20;
                g_ucBankNumber = 4;
                printf("\n   W25X20");
            }
            else if (ucTmpBuf[1] == 0x13 && ucTmpBuf[2] == 0x30)
            {
                g_ucFlashType = Flash_W25X40;
                g_ucBankNumber = 8;
                printf("\n   W25X40");
            }
            else if (ucTmpBuf[1] == 0x15 && ucTmpBuf[2] == 0x00)
            {
                g_ucFlashType = Flash_W25X16;
                g_ucBankNumber = 32;
                printf("\n   W25X16");
            }
            else if (ucTmpBuf[1] == 0x16 && ucTmpBuf[2] == 0x00)
            {
                g_ucFlashType = Flash_W25X32;
                g_ucBankNumber = 64;
                printf("\n   W25X32");
            }
            else if (ucTmpBuf[1] == 0x17 && ucTmpBuf[2] == 0x00)
            {
                g_ucFlashType = Flash_W25X64;
                g_ucBankNumber = 128;
                printf("\n   W25X64");
            }
            else
            {
                temp=MDrv_Ursa_6M40_ReadChipID();
                printf("\n ID 2:%x",temp);
                if (temp == 0x51)
                {//because some W25X20 have no ucTmpBuf[2](=0x00)
                    g_ucFlashType = Flash_W25X20;
                    g_ucBankNumber = 4;
                    printf("\n   W25X20-0");
                }
                else if(temp == 0x10)
                {
                    g_ucFlashType = Flash_W25X10;
                    g_ucBankNumber = 2;
                    printf("\n   W25X10-0");
                }
                else if(temp == 0x52)
                {//because some W25X40 have no ucTmpBuf[2](=0x00)
                    g_ucFlashType = Flash_W25X40;
                    g_ucBankNumber = 8;
                    printf("\n   W25X40-0");
                }
                else if(temp == 0x11)
                {//because some W25X40 have no ucTmpBuf[2](=0x00)
                    g_ucFlashType = Flash_W25P20;
                    g_ucBankNumber = 4;
                    printf("\n   W25P20");
                }
                else if(temp == 0x12)
                {//because some W25X40 have no ucTmpBuf[2](=0x00)
                    g_ucFlashType = Flash_W25P40;
                    g_ucBankNumber = 8;
                    printf("\n   W25P40");
                }
                else if(temp == 0x14)
                {
                    g_ucFlashType = Flash_NX25P16;
                    g_ucBankNumber = 32;
                    printf("\n   W25P16");
                }
                else
                {
                   return FALSE;
                }
            }
            break;
        case 0xBF:
            printf("\n  SST");
            if ((ucTmpBuf[1] == 0x41) & (ucTmpBuf[2] == 0x25))
            {
                g_ucFlashType = Flash_SST25VF016B;
                g_ucBankNumber = 32;
                printf("\n   SST25VF016B");
            }
            else if ((ucTmpBuf[1] == 0x8D) & (ucTmpBuf[2] == 0x25))
            {
                g_ucFlashType = Flash_SST25VF040B;
                g_ucBankNumber = 8;
                printf("\n   SST25VF040B");
            }
            else
            {
                 return FALSE;
            }
            break;
        case 0xC2:
            printf("\n MX");

            printf("\n JEDEC_ID1 0:%x",ucTmpBuf[0]);
            printf("\n JEDEC_ID1 1:%x",ucTmpBuf[1]);
            printf("\n JEDEC_ID1 2:%x",ucTmpBuf[2]);

            if ((ucTmpBuf[1] == 0x13) & (ucTmpBuf[2] == 0x20))
            {
                g_ucFlashType = Flash_MX25L4005A;
                g_ucBankNumber = 8;
                printf("\n   MX25L4005A");
            }
            else if ((ucTmpBuf[1] == 0x14) & (ucTmpBuf[2] == 0x20))
            {
                g_ucFlashType = Flash_MX25L8005;
                g_ucBankNumber = 16;
                printf("\n   MX25L8005");
            }
            else if ((ucTmpBuf[1] == 0x12) & (ucTmpBuf[2] == 0x20))
            {
                g_ucFlashType = Flash_MX25L2005;
                g_ucBankNumber = 4;
                printf("\n   MX25L2005");
            }
            else if((ucTmpBuf[1] == 0x15) & (ucTmpBuf[2] == 0x20))
            {
                g_ucFlashType = Flash_MX25L1605;
                g_ucBankNumber = 32;
                printf("\n   MX25L1605");
            }
            else if((ucTmpBuf[1] == 0x16) & (ucTmpBuf[2] == 0x20))
            {
                g_ucFlashType = Flash_MX25L3205;
                g_ucBankNumber = 32;
                printf("\n   MX25L3205");
            }
            else if((ucTmpBuf[1] == 0x17) & (ucTmpBuf[2] == 0x20))
            {
                g_ucFlashType = Flash_MX25L6405;
                g_ucBankNumber = 128;
                printf("\n   MX25L6405");
            }
            else
            {
                 return FALSE;
            }
            break;
        //intel
        case 0x89:
            printf("\n  INTEL");
            temp=MDrv_Ursa_6M40_ReadChipID();
            printf("\n  INTEL ChipID=%x",temp);
            if (ucTmpBuf[1] == 0x11)
            {
                g_ucFlashType=Flash_QB25F160S;
                g_ucBankNumber=32;
                printf("\n   INTS33_16");
            }
            else if (ucTmpBuf[1] == 0x12)
            {
                g_ucFlashType=Flash_QB25F320S;
                g_ucBankNumber=64;
                printf("\n   INTS33_32");
            }
            else if (ucTmpBuf[1] == 0x13)
            {
                g_ucFlashType=Flash_QB25F640S;
                g_ucBankNumber=128;
                printf("\n   INTS33_64");
            }
            else
            {
                return FALSE;
            }
            break;
            //GD
        case 0xC8:
            printf("\n  GD");
            if ((ucTmpBuf[1] == 0x16) && (ucTmpBuf[2] == 0x40))
            {
                g_ucFlashType = Flash_GD25Q32;
                g_ucBankNumber = 32;
                printf("\n  GD25Q32");
            }
            else
            {
                 return FALSE;
            }
            break;
        default:
            printf("\n JEDEC_ID 0:%x",ucTmpBuf[0]);
            printf("\n JEDEC_ID 1:%x",ucTmpBuf[1]);
            printf("\n JEDEC_ID 2:%x",ucTmpBuf[2]);
            MDrv_Ursa_6M40_ReadChipIDBuffer(ucTmpBuf);
            printf("\n RDID 0:%x",ucTmpBuf[0]);
            printf("\n RDID 1:%x",ucTmpBuf[1]);
            printf("\n RDID 2:%x",ucTmpBuf[2]);
            if ((ucTmpBuf[0] == 0x9D) && (ucTmpBuf[1] == 0x7F) && (ucTmpBuf[2] == 0x7B))
            {
                printf("\n  PMC-RDID");
                printf("\n   PM25LV512A/PM25LV512");
                g_ucFlashType=Flash_PMC512;
                g_ucBankNumber=1;
            }
            else
            {
                 return FALSE;
            }
            break;
    }
    MDrv_Ursa_6M40_ReadChipIDBuffer(ucTmpBuf);
    printf("\n RDID1 0:%x",ucTmpBuf[0]);
    printf("\n RDID1 1:%x",ucTmpBuf[1]);
    printf("\n RDID1 2:%x",ucTmpBuf[2]);
    return TRUE;
}

MS_U8 SrcReadFlash(MS_U16 pcount , MS_U8 BankNum)
{
    MS_U8 u8Data;
    memcpy(&u8Data,(void *)(g_u32ISPSrcAddr+(MS_U32)pcount + (MS_U32)BankNum*0x10000), 1);
    return u8Data;
}


MS_U8 SFlashRdsr(void)
{
    MS_U8 buffer[2];

    buffer[0]=SPI_WRITE;
    buffer[1]=sFlash.RDSR;
    MDrv_Ursa_6M40_SWI2C_WriteDatas(buffer,2,NULL,0);

    buffer[0]=SPI_READ;
    MDrv_Ursa_6M40_SWI2C_ReadDatas(buffer,1,&buffer[1],1);

    MDrv_Ursa_6M40_SWI2C_WriteStop();

    return buffer[1];
}

MS_BOOL SFlashChecksr(void)
{
    MS_U8 ucdelay = 10;
    MS_U32 count=1000;

    while(count--)
    {
        if((SFlashRdsr()&0x01)==0x00)
            return TRUE;
        while(ucdelay--);
    }
    return FALSE;
}


void SFlashWrsr(MS_U8 tdata)
{
    MS_U8 buffer[3];

    SFlashChecksr();

    // for sst sflash (sst manufacturer id=0xBF )
    if(sFlash.manufacturer_id==0xBF)
    {
        buffer[0]=SPI_WRITE;
        buffer[1]=0x50;
        MDrv_Ursa_6M40_SWI2C_WriteDatas(buffer,2,NULL,0);

        MDrv_Ursa_6M40_SWI2C_WriteStop();
    }

    buffer[0]=SPI_WRITE;
    buffer[1]=sFlash.WRSR;
    buffer[2]=tdata;
    MDrv_Ursa_6M40_SWI2C_WriteDatas(buffer,sizeof(buffer),NULL,0);

    MDrv_Ursa_6M40_SWI2C_WriteStop();
}

void SFlashWren(void)
{
    MS_U8 buffer[2];

    buffer[0]=SPI_WRITE;
    buffer[1]=sFlash.WREN;

    SFlashChecksr();
    MDrv_Ursa_6M40_SWI2C_WriteDatas(buffer,2,NULL,0);

    MDrv_Ursa_6M40_SWI2C_WriteStop();
}
void SFlashWrdi(void)
{
    MS_U8 buffer[2];

    buffer[0]=SPI_WRITE;
    buffer[1]=sFlash.WRDI;

    SFlashChecksr();
    MDrv_Ursa_6M40_SWI2C_WriteDatas(buffer,2,NULL,0);

    buffer[0]=SPI_STOP;
    MDrv_Ursa_6M40_SWI2C_WriteDatas(buffer,1,NULL,0);
}

MS_BOOL VerifyPMC64K(U8 BankNum)
{
    MS_U8 tdata[]={SPI_WRITE,0x03,0x00,0x00,0x00};
    MS_BOOL VerifyOk=TRUE;
    MS_U16 PcCounter=0;
    MS_U8 FlashReadData;

    tdata[1]=sFlash.READS;
    tdata[2]=BankNum;
    tdata[3]=0;
    tdata[4]=0;

    MDrv_Ursa_6M40_SWI2C_WriteDatas(tdata,sizeof(tdata),NULL,0);
    udelay(60*1000);
    {
        MDrv_Ursa_6M40_SWI2C_CommandRead();
           udelay(60*1000);
        MApi_SWI2C_UseBus(URSA_ISP_I2C_BUS_SEL);

     if(MApi_SWI2C_AccessStart(SLAVEADDR, SW_IIC_READ)==FALSE)
    {
         printf("\n6M30->VerifyPMC64K Error");
    }

        for(PcCounter=0;PcCounter<=BANKSIZE-2;PcCounter++)
        {
            FlashReadData=MApi_SWI2C_GetByte(1);
            if(FlashReadData!=SrcReadFlash(PcCounter,BankNum))
            {
                VerifyOk=FALSE;
                printf("\n flash read date error[%x],[%x],[%x]",PcCounter,FlashReadData,SrcReadFlash(PcCounter,BankNum));
                break;
            }
        }

        //last byte
        {
            FlashReadData=MApi_SWI2C_GetByte(0);
            //PcCounter++;

            if(FlashReadData!=SrcReadFlash(PcCounter,BankNum))
                VerifyOk=FALSE;
        }

        // 1 bank program end
        MApi_SWI2C_Stop();
    }

    MDrv_Ursa_6M40_SWI2C_WriteStop();

    return VerifyOk;
}

void ProgSST64K(MS_U8 BankNum)
{
    MS_U8 k;
    MS_U8 tdata[7];
    MS_U16 PcCounter=0;

    SFlashWrsr(0x00);

    SFlashWren();
    SFlashChecksr();

    //AAI send the address
    tdata[0]=SPI_WRITE;
    tdata[1]=sFlash.PG_PROG;
    tdata[2]=BankNum;
    tdata[3]=0;
    tdata[4]=0;
    tdata[5]=SrcReadFlash(PcCounter,BankNum);
    PcCounter++;
    tdata[6]=SrcReadFlash(PcCounter,BankNum);
    PcCounter++;

    MApi_SWI2C_UseBus(URSA_ISP_I2C_BUS_SEL);
    MApi_SWI2C_AccessStart(SLAVEADDR, SW_IIC_WRITE);

    for(k=0;k<sizeof(tdata);k++)
        MApi_SWI2C_SendByte(tdata[k]);
    MDrv_Ursa_6M40_SWI2C_WriteStop();
    SFlashChecksr();

    //AAI send the datas
    tdata[0]=SPI_WRITE;
    tdata[1]=sFlash.PG_PROG;
    for (;PcCounter<0xFFFE;)
    {
        tdata[2]=SrcReadFlash(PcCounter,BankNum);
        PcCounter++;
        tdata[3]=SrcReadFlash(PcCounter,BankNum);
        PcCounter++;

        MApi_SWI2C_UseBus(URSA_ISP_I2C_BUS_SEL);
        MApi_SWI2C_AccessStart(SLAVEADDR, SW_IIC_WRITE);
        for(k=0;k<4;k++)
            MApi_SWI2C_SendByte(tdata[k]);
        MDrv_Ursa_6M40_SWI2C_WriteStop();
        //SFlashChecksr();
    }
    //AAI send the remain 2 bytes
    tdata[2]=SrcReadFlash(PcCounter,BankNum);
    PcCounter++;
    tdata[3]=SrcReadFlash(PcCounter,BankNum);

    MApi_SWI2C_UseBus(URSA_ISP_I2C_BUS_SEL);
    MApi_SWI2C_AccessStart(SLAVEADDR, SW_IIC_WRITE);
    for(k=0;k<4;k++)
        MApi_SWI2C_SendByte(tdata[k]);
    MDrv_Ursa_6M40_SWI2C_WriteStop();
    SFlashChecksr();
    //AAI stop
    SFlashWrdi();
    SFlashChecksr();
}

void ProgPMC64K(MS_U8 BankNum)
{
    MS_U8 k;
    MS_U16 i;
    MS_U8 tdata[5];
    MS_U8 count;
    MS_U16 PcCounter=0;

    SFlashWrsr(0x00);

    for(i=0;i<=BLOCKNUM;i++)
    {
        SFlashWren();
        SFlashChecksr();

        count=BLOCKSIZE-1;

        tdata[0]=SPI_WRITE;
        tdata[1]=sFlash.PG_PROG;
        tdata[2]=BankNum;
        tdata[3]=i;
        tdata[4]=0;

        MApi_SWI2C_UseBus(URSA_ISP_I2C_BUS_SEL);
        MApi_SWI2C_AccessStart(SLAVEADDR, SW_IIC_WRITE);

        for(k=0;k<sizeof(tdata);k++)
            MApi_SWI2C_SendByte(tdata[k]);

        while(count--)
        {
            MApi_SWI2C_SendByte(SrcReadFlash(PcCounter,BankNum));

            PcCounter++;
        }

        // 1 byte more
        MApi_SWI2C_SendByte(SrcReadFlash(PcCounter,BankNum));
        PcCounter++;

        //block program end
        MDrv_Ursa_6M40_SWI2C_WriteStop();
      printf("*");
    }

    MDrv_Ursa_6M40_SWI2C_WriteDatas(tdata,2,NULL,0);
    SFlashWrdi();
    SFlashChecksr();
}

void SFlashChip_Erase(void)
{
    //U8 tdata[5]={SPI_WRITE,0x00,0x00,0x00,0x00};
    MS_U8 addr[2];

    SFlashWrsr(0x00);
    SFlashWren();
    SFlashChecksr();

    addr[0]=SPI_WRITE;
    addr[1]=sFlash.CHIP_ERASE;
    MDrv_Ursa_6M40_SWI2C_WriteDatas(addr,2,NULL,0);

    MDrv_Ursa_6M40_SWI2C_WriteStop();

    SFlashChecksr();//Vick Add
}

void SFlashProgram(void)
{
    MS_U16    num;
    MS_U8    BankTmp;

    BankTmp = g_ucBankNumber;
    for(num=0;num<BankTmp;num++)
    {
        printf("\n Write Bank %x",num);
        if (g_ucFlashType==Flash_SST25VF016B||g_ucFlashType==Flash_SST25VF040B)
            ProgSST64K(num);
        else
            ProgPMC64K(num);
    g_u8CurPercent = 80 - 40*(num+1)/g_ucBankNumber;
    }
}
MS_BOOL SFlashVerify(void)
{
    MS_U8    num;
    MS_U8    BankTmp;

    BankTmp = g_ucBankNumber;
    for(num=0;num<BankTmp;num++)
    {
        printf("\n Verify Bank %x",num);
        if(VerifyPMC64K(num)==FALSE)
            return FALSE;
    g_u8CurPercent = 40 - 40*(num+1)/g_ucBankNumber;

    }
    return TRUE;
}
void  Ursa_ISP_Init(MS_U32 u32Addr, MS_U32 u32Size)
{
    ErrorFlag = FlashProgOK;
    g_eFlashProgramState = FlashProgStateInit;
    g_u32ISPSrcAddr = u32Addr;
    g_u32ISPCodeSize = u32Size;
}


int  Ursa_ISP_Program(void)
{
    MDrv_Ursa_6M40_SWI2C_Init();
        MS_U16 wErrCounter;

        if (ErrorFlag != FlashProgOK)
        {
            return (0xF0+ErrorFlag);
        }

        switch (g_eFlashProgramState)
        {
            case FlashProgStateInit:
                g_u8CurPercent = 100;
                g_eFlashProgramState = FlashProgStateEnterIsp;
                break;

            case FlashProgStateEnterIsp:
                printf("\n1:ISP Enter\n");
                MDrv_Ursa_6M40_EnterIspMode();
                udelay(500*1000);
                MDrv_Ursa_6M40_ExitIspMode();
                udelay(500*1000);

                for(wErrCounter = 0;wErrCounter<ENTER_ISP_ERROR_MAX;)
                {//for arcing
                    MDrv_Ursa_6M40_WP_PullHigh();
                    if (!MDrv_Ursa_6M40_EnterIspMode())
                    {
                        wErrCounter++;
                        udelay(10*1000);
                        MDrv_Ursa_6M40_ExitIspMode();
                        udelay(80*1000);
                    }
                    else
                        break;
                }

                if (wErrCounter>=ENTER_ISP_ERROR_MAX)
                {
                    ErrorFlag=FlashEnterIspModeErr;
                    printf("\nCan not enter ISP\n");
                    goto ProgEnd;
                }
               else
             {
                    printf("\nEnter ISP Successful[%x]\n",wErrCounter);
             }
                udelay(50*1000);//Wait the Protect pin to hight.
                for(wErrCounter=0;wErrCounter<GET_ID_ERROR_MAX;)
                {
                    if (!GetsFlashType())
                    {
                        wErrCounter++;
                        udelay(50*1000);
                    }
                    else
                        break;
                }

                if (wErrCounter>=GET_ID_ERROR_MAX)
                {
                    printf("\n Detect SPI Flash Failed");
                    g_ucFlashType=Flash_A25L40P;
                    g_ucBankNumber=8;
                }
                sFlash=SupportSFlash[g_ucFlashType];

                printf("\n Bank Number=%d",g_ucBankNumber);
                //-------------------------
                g_ucBankNumber = (g_u32ISPCodeSize/0x10000)+1;
                //-------------------------
                printf("\n Program Banks=%d",g_ucBankNumber);

                //------------------------
                //disable write protect and set status 0x00
                SFlashWren();
                SFlashWrsr(0x00);
                g_u8CurPercent = 95;
                g_eFlashProgramState = FlashProgStateErase;
                break;

            case FlashProgStateErase:
                //Step2:Chip Erase
                printf("\n2:Chip Erase");
                SFlashChip_Erase();

                //wait the flash erase finished.
                for (wErrCounter = 0;wErrCounter<sFlash.ChipEraseMaxTime;wErrCounter++)
                {
                    if (SFlashRdsr()&0x01)
                    {
                        if (sFlash.ChipEraseMaxTime <= (MS_U16)40)
                        {// 0.1s
                            udelay(100*1000);
                        }
                        else if (sFlash.ChipEraseMaxTime <= (MS_U16)200)
                        {// 0.2s
                            udelay(100*1000);
                            wErrCounter++;
                            udelay(100*1000);
                        }
                        else if (sFlash.ChipEraseMaxTime <= (MS_U16)600)
                        {// 0.5s
                            udelay(100*1000);
                            wErrCounter++;
                            udelay(100*1000);
                            wErrCounter++;
                            udelay(100*1000);
                            wErrCounter++;
                            udelay(100*1000);
                            wErrCounter++;
                            udelay(100*1000);
                        }
                        else
                        {// 1s
                            udelay(100*1000);
                            wErrCounter++;
                            udelay(100*1000);
                            wErrCounter++;
                            udelay(100*1000);
                            wErrCounter++;
                            udelay(100*1000);
                            wErrCounter++;
                            udelay(100*1000);
                            wErrCounter++;
                            udelay(100*1000);
                            wErrCounter++;
                            udelay(100*1000);
                            wErrCounter++;
                            udelay(100*1000);
                            wErrCounter++;
                            udelay(100*1000);
                            wErrCounter++;
                            udelay(100*1000);
                        }
                    }
                    else
                        break;
                }
                printf("\n Wait Count:%d",wErrCounter);
                g_u8CurPercent = 80;
                g_eFlashProgramState = FlashProgStateBlank;
                break;

            case FlashProgStateBlank:
            #if 0
                    //Step3:Blanking Check
                    printf("\n3:Blanking");
                    if(!SFlashBlanking(0,sFlash.size))
                    {
                        ErrorFlag=FlashBlankingErr;
                        goto ProgEnd;
                    }
            #endif
                g_u8CurPercent = 40;
                g_eFlashProgramState = FlashProgStateProgram;
                break;

            case FlashProgStateProgram:
                //Step4:Prog Flash
                printf("\n4:Prog... ");
                SFlashProgram();
                g_u8CurPercent = 20;
                g_eFlashProgramState = FlashProgStateVerify;
                break;

            case FlashProgStateVerify:
                //Step5:Verify
                printf("\n5:Verify");
                SFlashWren();
                SFlashWrsr(sFlash.LOCK);
                SFlashWrdi();

                if(!SFlashVerify())
                {
                    ErrorFlag=FlashVerifyErr;
                    goto ProgEnd;
                }
                printf("\nVerify->OK!");
                g_u8CurPercent = 10;
                g_eFlashProgramState = FlashProgStateExit;
                break;

            case FlashProgStateExit:
                //Step6:Exit ISP
                printf("\n6:Exit ISP");
                MDrv_Ursa_6M40_ExitIspMode();

                g_u8CurPercent = 0;
                g_eFlashProgramState = FlashProgStateIdle;
                break;

           case FlashProgStateIdle:
            break;
        }

    ProgEnd:
        if (ErrorFlag != FlashProgOK)
        {
            MDrv_Ursa_6M40_ExitIspMode();
    #if (ENABLE_WATCH_DOG == ENABLE)
            MDrv_Sys_EnableWatchDog();
    #endif
            return (0xF0+ErrorFlag);
        }
        else
        {
            return g_u8CurPercent;
        }
    return 0;
}
 int do_ursa7_upgrade(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
 {
     char cmd[CMD_BUF] = "\0";
     char *env =NULL;
     int partition = 0;
     int device = 0;
     int ret = 0;
     MS_U8 u8Percent= 0;
     long unsigned  int u32FileSize = 0;
     if (-1 == appInitUsbDisk())
         {
             UBOOT_ERROR("FAIL : can not init usb!! \n");
             return -1;
         }
      ret = check_file_partition(URSA7_UPGRADE_BIN_PATH,&device,&partition);
      if(ret == 0)
      {
             UBOOT_DEBUG("has Ursa7 upgrade bin\n");


             UBOOT_DEBUG("Geting file size\n");
             snprintf(cmd, CMD_BUF, "fatfilesize usb %d:%d %s", device,partition, URSA7_UPGRADE_BIN_PATH);
             UBOOT_DEBUG("cmd=%s\n",cmd);
             ret = run_command(cmd, 0);
             if(ret!=0)
             {
                 UBOOT_ERROR("get script file's size fail\n");
                 return -1;
             }
             else
             {
                 env=getenv("filesize");
                 if(env==NULL)
                 {
                     UBOOT_ERROR("get env 'filesize' fail\n");
                 }
                 u32FileSize = simple_strtol(env, NULL, 16);
                 printf("Size 0x%lx \n",u32FileSize);

             }

             snprintf(cmd, CMD_BUF, "fatload usb %d:%d  %X %s %ul",device, partition, UPGRADE_BUFFER_ADDR, URSA7_UPGRADE_BIN_PATH,u32FileSize);

             UBOOT_DEBUG("cmd=%s\n",cmd);
             if(-1 == run_command(cmd, 0))
             {
                 UBOOT_ERROR("Load Upgrade File fail!\n");
                 return -1;
             }
             else
             {
                UBOOT_INFO("Load upgrade file OK!~\n");
                UBOOT_INFO("Start Upgrade Ursa!~\n");
                Ursa_ISP_Init(UPGRADE_BUFFER_ADDR,u32FileSize);
                Ursa_ISP_Program();
                do
                {
                    u8Percent =  Ursa_ISP_Program();;
                }while ((u8Percent < 0xF0) && (u8Percent != 0));

                UBOOT_TRACE("OK\n");
                run_command("reset",0);
            }
     }
     else
     {
         UBOOT_DEBUG("no %s in usb disk\n",URSA7_UPGRADE_BIN_PATH);
     }
     return -1;
 }


 int do_ursa7_reset(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
    {
        MS_U16 wErrCounter;
        MDrv_Ursa_6M40_SWI2C_Init();
        for(wErrCounter = 0;wErrCounter<ENTER_ISP_ERROR_MAX;)
        {
            if (!MDrv_Ursa_6M40_EnterIspMode())
            {
                wErrCounter++;
                udelay(10*1000);
                MDrv_Ursa_6M40_ExitIspMode();
                udelay(80*1000);
            }
            else
                break;
        }
    MDrv_Ursa_6M40_ExitIspMode();
    return 0;
    }

#endif

