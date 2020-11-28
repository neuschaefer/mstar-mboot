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
#include <MsTypes.h>

#include <common.h>
#include <command.h>
#include <malloc.h>
#include <MsUtility.h>
#include <MsDebug.h>
#include <MsSystem.h>
#include <MsRawIO.h>
#include <drvSERFLASH.h>

#include <MsMBootConfig.h>

st_mboot_config mboot_config;

int do_get_mboot_config(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int ret = -1;
    U32 u32ConfigOffset = 0;
    UBOOT_TRACE("IN\n");

    ret = mboot_raw_io_Config();
    if(0 != ret)
    {
        UBOOT_ERROR("raw_io_config setting fail!\n");
        return -1;
    }

    ret=MsApiChunkHeader_GetValue(CH_MBOOT_CONFIG_BINARY_OFFSET, &u32ConfigOffset);
    if(ret != 0)
    {
        UBOOT_ERROR("get mboot config binary offset fail!\n");
        return -1;
    }

    memset(&mboot_config, 0, sizeof(mboot_config));
    if (-1 == raw_read((U32)&mboot_config, u32ConfigOffset, sizeof(mboot_config)))
    {
        UBOOT_ERROR("ERROR: read mboot config failed...>>>\n");
        return -1;
    }
    else if(mboot_config.magic_number != MBOOT_CONFIG_MAGIC_NUMBER)
    {
		UBOOT_ERROR("the magic of mboot_config.bin is wrong...>>>\n");
		UBOOT_ERROR("read mboot config failed!...>>>\n");
    }
	else
	{
		UBOOT_DEBUG("read mboot config successfully...>>>\n");
        UBOOT_DEBUG("mboot config >>> \n");
        display_mboot_config(mboot_config);
    }

    UBOOT_TRACE("OUT\n");
    return 0;
}

void display_mboot_config(st_mboot_config mboot_config)
{
	UBOOT_DEBUG("\n[Version]\n");
	UBOOT_DEBUG("Version = %d\n", mboot_config.version);
    /* pm_boot_config #0 */
    UBOOT_DEBUG("\n[BootToPM]\n");
    UBOOT_DEBUG("PmWakeEnableIR     = %d\n", (mboot_config.pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-1)) ? 1 : 0));
    UBOOT_DEBUG("PmWakeEnableSAR    = %d\n", (mboot_config.pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-2)) ? 1 : 0));
    UBOOT_DEBUG("PmWakeEnableGPIO0  = %d\n", (mboot_config.pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-3)) ? 1 : 0));
    UBOOT_DEBUG("PmWakeEnableGPIO1  = %d\n", (mboot_config.pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-4)) ? 1 : 0));
    UBOOT_DEBUG("PmWakeEnableUART1  = %d\n", (mboot_config.pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-5)) ? 1 : 0));
    UBOOT_DEBUG("PmWakeEnableSYNC   = %d\n", (mboot_config.pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-6)) ? 1 : 0));
    UBOOT_DEBUG("PmWakeEnableESYNC  = %d\n", (mboot_config.pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-7)) ? 1 : 0));
    UBOOT_DEBUG("PmWakeEnableRTC0   = %d\n", (mboot_config.pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-8)) ? 1 : 0));
    UBOOT_DEBUG("PmWakeEnableRTC1   = %d\n", (mboot_config.pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-9)) ? 1 : 0));
    UBOOT_DEBUG("PmWakeEnableDVI0   = %d\n", (mboot_config.pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-10)) ? 1 : 0));
    UBOOT_DEBUG("PmWakeEnableDVI2   = %d\n", (mboot_config.pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-11)) ? 1 : 0));
    UBOOT_DEBUG("PmWakeEnableCEC    = %d\n", (mboot_config.pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-12)) ? 1 : 0));
    UBOOT_DEBUG("PmWakeEnableAVLINK = %d\n", (mboot_config.pm_wakeup_source & (1<<(NUMBER_OF_PM_WAKEUP_SOURCE-13)) ? 1 : 0));
    UBOOT_DEBUG("PmWakeIRKeyCode1   = 0x%X\n", mboot_config.pm_wakeup_keycode1);
    UBOOT_DEBUG("PmWakeIRKeyCode2   = 0x%X\n", mboot_config.pm_wakeup_keycode2);
    UBOOT_DEBUG("PmWakeIRKeyCode0   = 0x%X\n", mboot_config.pm_ir_headcode0);
    UBOOT_DEBUG("PmWakeIRKeyCode1   = 0x%X\n", mboot_config.pm_ir_headcode1);

    /* flash_wp_config #1 */
    UBOOT_DEBUG("\n[FlashWP]\n");
    UBOOT_DEBUG("PIN_FLASH_WP0      = %d\n", mboot_config.pin_flash_wp0);
    UBOOT_DEBUG("PIN_FLASH_WP1      = %d\n", mboot_config.pin_flash_wp1);

    /* db_table_config #2 */
    UBOOT_DEBUG("\n[DBTable]\n");
    UBOOT_DEBUG("UBIPART            = %s\n", mboot_config.ubipart);
    UBOOT_DEBUG("Config_Partition   = %s\n", mboot_config.config_partition);
    UBOOT_DEBUG("Customer_Partition = %s\n", mboot_config.customer_partition);
    UBOOT_DEBUG("Config_Path        = %s\n", mboot_config.config_path);
    UBOOT_DEBUG("Customer_path      = %s\n", mboot_config.customer_path);

    /* keypad_config #3 */
    UBOOT_DEBUG("\n[KeypadConfig]\n");
    UBOOT_DEBUG("ADC_KEY_LEVEL      = %d\n", mboot_config.adc_key_level_num);
    {
        int i_level;
        for(i_level = 0; i_level < NUMBER_OF_KEYPAD_ADC_LEVEL; i_level++)
        {
            UBOOT_DEBUG("ADC_KEY_L%d         = 0x%X\n", i_level, mboot_config.adc_key_level[i_level]);
        }
    }

    /* boot_check_config #4 */
    UBOOT_DEBUG("\n[BootCheck]\n");
    UBOOT_DEBUG("IR_RECOVERY_KEY          = 0x%X\n", mboot_config.ir_recovery_key);
    UBOOT_DEBUG("IR_FORCEUGRADE_KEY       = 0x%X\n", mboot_config.ir_force_upgrade_key);
    UBOOT_DEBUG("IR_UPGRADEBOOTLOADER_KEY = 0x%X\n", mboot_config.ir_upgradebootloader_key);
    //UBOOT_DEBUG("IR_UART_ONOFF_KEY        = 0x%X\n", mboot_config.ir_uart_onoff_key);
    UBOOT_DEBUG("KEYPAD_RECOVERY_KEY      = 0x%X\n", mboot_config.keypad_recovery_key);
    UBOOT_DEBUG("KEYPAD_FORCEUGRADE_KEY   = 0x%X\n", mboot_config.keypad_force_upgrade_key);
    UBOOT_DEBUG("KEYPAD_UPGRADEBOOTLOADER_KEY = 0x%X\n", mboot_config.keypad_upgradebootloader_key);
    //UBOOT_DEBUG("KEYPAD_UART_ONOFF_KEY    = 0x%X\n", mboot_config.keypad_uart_onoff_key);

    /* boot_logo_config #5 */
    UBOOT_DEBUG("\n[BootLogo]\n");
    UBOOT_DEBUG("Logo_Partition           = %s\n", mboot_config.boot_logo_partition);
    UBOOT_DEBUG("Logo_Path                = %s\n", mboot_config.boot_logo_path);
    UBOOT_DEBUG("Logo_File                = %s\n", mboot_config.boot_logo_file);

    /* boot_music_config #6 */
    UBOOT_DEBUG("\n[BootMusic]\n");
    UBOOT_DEBUG("Music_Partition           = %s\n", mboot_config.boot_music_partition);
    UBOOT_DEBUG("Music_Path                = %s\n", mboot_config.boot_music_path);
    UBOOT_DEBUG("Music_File                = %s\n", mboot_config.boot_music_file);

    /* osd_config #7 */
    UBOOT_DEBUG("\n[OSD]\n");
    UBOOT_DEBUG("OSD_Layer_Width           = %d\n", mboot_config.default_osd_layer_width);
    UBOOT_DEBUG("OSD_Layer_Height          = %d\n", mboot_config.default_osd_layer_height);
    UBOOT_DEBUG("OSD_String_X              = %d\n", mboot_config.default_osd_string_x);
    UBOOT_DEBUG("OSD_String_Y              = %d\n", mboot_config.default_osd_string_y);
    UBOOT_DEBUG("OSD_ATTRIB                = %d\n", mboot_config.default_osd_attrib);
    UBOOT_DEBUG("OSD_COLOR                 = %d\n", mboot_config.default_osd_color);
    UBOOT_DEBUG("OSD_String_Tips           = %s\n", mboot_config.default_osd_string_tips);
    UBOOT_DEBUG("OSD_Backgroud_Path        = %s\n", mboot_config.default_osd_background_path);

    /* usb_upgrade_config #8 */
    UBOOT_DEBUG("\n[USBUpgrade]\n");
    UBOOT_DEBUG("OAD_BIN_PATH              = %s\n", mboot_config.default_oad_bin_path);
    UBOOT_DEBUG("NET_BIN_PATH              = %s\n", mboot_config.default_net_bin_path);
    UBOOT_DEBUG("AP_BIN_PATH               = %s\n", mboot_config.default_ap_bin_path);
    UBOOT_DEBUG("MBOOT_BIN_PATH            = %s\n", mboot_config.default_mboot_bin_path);
    UBOOT_DEBUG("SBOOT_BIN_PATH            = %s\n", mboot_config.defalut_sboot_bin_path);
    UBOOT_DEBUG("URSA_BIN_PATH             = %s\n", mboot_config.default_ursa_bin_path);
	UBOOT_DEBUG("OTA_ZIP_PATH              = %s\n", mboot_config.default_ota_zip_path);

    /* mmap_config #9 */
    UBOOT_DEBUG("\n[MMAP]\n");
    UBOOT_DEBUG("VE_BUFFER_ADDR            = 0x%X\n", mboot_config.ve_buffer_address);

    /* mmap_config #10 */
    UBOOT_DEBUG("\n[URSA]\n");
    UBOOT_DEBUG("URSA_Type                 = %d\n", mboot_config.ursa_type);

    /* mmap_config #11 */
    UBOOT_DEBUG("\n[EthCheck]\n");
    UBOOT_DEBUG("Store_Position            = %d\n", mboot_config.ethaddr_stored_position);
    UBOOT_DEBUG("I2C_Slave_Address         = %d\n", mboot_config.ethaddr_i2c_slave_address);
    UBOOT_DEBUG("Bank_Address              = 0x%X\n", mboot_config.ethaddr_in_bank_address);
}
