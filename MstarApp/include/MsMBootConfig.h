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

#ifndef _Mstar_MBoot_Config_Header_
#define _Mstar_MBoot_Config_Header_

#include <command.h>
#include <ShareType.h>

// general arguments
#define NUMBER_OF_PM_WAKEUP_SOURCE                       13
#define NUMBER_OF_KEYPAD_ADC_LEVEL                       8
#define MAX_NUMBER_OF_KEYPAD_ADC_LEVEL                   16
#define MAX_STRING_LENGTH                                32
#define MBOOT_CONFIG_MAGIC_NUMBER		0xAABBCCDD

#pragma pack (1)					// force to be aligned by one byte
typedef struct
{
	/* magic number */
	U32 magic_number;
	
	/* version control*/
	U32 version;					// it records mboot_config.ini's version
	
	/* pm_boot_config (6 bytes) */
	U16 pm_wakeup_source;			// every bit represents one source, 1:enable, 0:disable
	U8 pm_wakeup_keycode1;
	U8 pm_wakeup_keycode2;
	U8 pm_ir_headcode0;
	U8 pm_ir_headcode1;

	/* flash_wp_config (2 bytes) */
	U8 pin_flash_wp0;
	U8 pin_flash_wp1;

	/* db_table_config (32*5=160 bytes) */
	U8 ubipart[MAX_STRING_LENGTH];
	U8 config_partition[MAX_STRING_LENGTH];
	U8 customer_partition[MAX_STRING_LENGTH];
	U8 config_path[MAX_STRING_LENGTH];
	U8 customer_path[MAX_STRING_LENGTH];

	/* keypad_config (17 bytes)*/
	U8 adc_key_level_num;
	U8 adc_key_level[MAX_NUMBER_OF_KEYPAD_ADC_LEVEL];

	/* boot_check_config (6 bytes)*/
	U8 ir_recovery_key;
	U8 ir_force_upgrade_key;
	//U8 ir_uart_onoff_key;
	U8 ir_upgradebootloader_key;
	U8 keypad_recovery_key;
	U8 keypad_force_upgrade_key;
	//U8 keypad_uart_onoff_key;
	U8 keypad_upgradebootloader_key;

	/* boot_logo_config (32*3=96 bytes)*/
	U8 boot_logo_partition[MAX_STRING_LENGTH];
	U8 boot_logo_path[MAX_STRING_LENGTH];
	U8 boot_logo_file[MAX_STRING_LENGTH];

	/* boot_music_config (32*3=96 bytes)*/
	U8 boot_music_partition[MAX_STRING_LENGTH];
	U8 boot_music_path[MAX_STRING_LENGTH];
	U8 boot_music_file[MAX_STRING_LENGTH];

	/* osd_config (4*2+3+32*2=75 bytes)*/
	U32 default_osd_layer_width;
	U32 default_osd_layer_height;
	U16 default_osd_attrib;
	U8  default_osd_color;
	U8  default_osd_string_x;
	U8  default_osd_string_y;
	U8 default_osd_string_tips[MAX_STRING_LENGTH];
	U8 default_osd_background_path[MAX_STRING_LENGTH];

	/* usb_upgrade_config (32*7=224 bytes)*/
	U8 default_oad_bin_path[MAX_STRING_LENGTH];
	U8 default_net_bin_path[MAX_STRING_LENGTH];
	U8 default_ap_bin_path[MAX_STRING_LENGTH];
	U8 default_mboot_bin_path[MAX_STRING_LENGTH];
	U8 defalut_sboot_bin_path[MAX_STRING_LENGTH];
	U8 default_ursa_bin_path[MAX_STRING_LENGTH];
	U8 default_ota_zip_path[MAX_STRING_LENGTH];	
	
	/* mmap_config 4 bytes */
	U32 ve_buffer_address;

	/* ursa_config 1 byte*/
	U8 ursa_type;

	/* eth_check_config 6 bytes*/
	U8 ethaddr_stored_position;
	U8 ethaddr_i2c_slave_address;
	U32 ethaddr_in_bank_address;
} st_mboot_config;

extern st_mboot_config mboot_config;
int do_get_mboot_config(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
void display_mboot_config(st_mboot_config mboot_config);

#endif //_Mstar_MBoot_Config_Header_