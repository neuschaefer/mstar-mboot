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

#include <command.h>
#include <config.h>
#include <CusSystem.h>

#if CONFIG_MSTAR_STR_ENABLE
#ifdef CONFIG_MSTAR_STR_MINISIZE
U_BOOT_CMD_STR(
#else
U_BOOT_CMD(
#endif
	checkstr,1,        1,	do_check_str_resume,
	"check_str_resume\n",
	"command: checkstr\n"
);
#endif

#if (ENABLE_MODULE_ANDROID_BOOT == 1 )
U_BOOT_CMD(
    envload, CONFIG_SYS_MAXARGS, 1,    do_envload,
    "envload   - reload the nand environment.\n",
    NULL
);
#endif

#if defined (CONFIG_MBOOT_VERSION)
U_BOOT_CMD(
    mbootver_set, CONFIG_SYS_MAXARGS, 1,    do_setmbootver,
    "setmbootver   -  for customer show in factory menu.\n",
    NULL
);
#endif

//#if defined(CONFIG_LOAD_ENV_FROM_SN)
U_BOOT_CMD(
    loadenv ,    CONFIG_SYS_MAXARGS,    1,     do_loadenv,
    "loadenv   - load env for nand \n",
    "    -  \n"
);
//#endif

#if defined (CONFIG_SET_4K2K_MODE)
U_BOOT_CMD(
    set_FRC ,    CONFIG_SYS_MAXARGS,    1,     do_setFRC,
    "set_FRC   - set FRC \n",
    "    -  \n"
);
#endif

#if defined (CONFIG_URSA_6M40)
#ifdef CONFIG_MSTAR_STR_MINISIZE
U_BOOT_CMD_STR(
#else
U_BOOT_CMD(
#endif
    ursa_lvds_on,   CONFIG_SYS_MAXARGS, 1,    do_ursa_lvds_on,
    "ursa_lvds_on   - set ursa lvds on\n",
    NULL
);
U_BOOT_CMD(
    ursa_lvds_off,   CONFIG_SYS_MAXARGS, 1,    do_ursa_lvds_off,
    "ursa_lvds_off   - set ursa lvds off\n",
    NULL
);


#ifdef CONFIG_MSTAR_STR_MINISIZE
U_BOOT_CMD_STR(
#else
U_BOOT_CMD(
#endif
		ursa_osd_unmute,	CONFIG_SYS_MAXARGS, 1,	  do_ursa_osd_unmute,
		"ursa_osd_unmute	- ursa_osd_unmute\n",
		NULL
	);
U_BOOT_CMD(
		ursa_2k_mode,	CONFIG_SYS_MAXARGS, 1,	  do_ursa_2k_mode_on,
		"ursa_2k_mode	- ursa_2k_mode_on\n",
		NULL
	);

U_BOOT_CMD(
        ursa_set_osd_mode,   CONFIG_SYS_MAXARGS, 1,    do_ursa_set_osd_mode,
        "ursa_set_osd_mode   - do_ursa_set_osd_mode\n",
        NULL
    );
#endif

#if defined (CONFIG_ENABLE_4K2K_PANEL)
#if defined (CONFIG_INX_VB1) || defined (CONFIG_INX_NOVA_VB1)
U_BOOT_CMD(
    inx_panel_set_init,   CONFIG_SYS_MAXARGS, 1,    do_inx_panel_set_init,
    "inx_panel_sete_init   - init inx panel\n",
    NULL
);

U_BOOT_CMD(
    inx_panel_set_fhd,   CONFIG_SYS_MAXARGS, 1,    do_inx_panel_set_fhd,
    "panel_set_fhd   - set panel as fhd mode\n",
    NULL
);

U_BOOT_CMD(
    inx_panel_set_4k2k,   CONFIG_SYS_MAXARGS, 1,    do_inx_panel_set_4k2k,
    "panel_set_4k2k   - set panel as 4k2k mode\n",
    NULL
);
#endif

#if defined (CONFIG_INX_VB1)
U_BOOT_CMD(
    panel_inx_vb1_init,    CONFIG_SYS_MAXARGS, 1,    do_panel_inx_vb1_init,
    "panel_inx_vb1_init   - panel_inx_vb1_init\n",
    NULL
);
#endif

#if defined (CONFIG_INX_NOVA_VB1)
U_BOOT_CMD(
    inx_nova_set_4k2k_2division,   CONFIG_SYS_MAXARGS, 1,    do_inx_nova_set_4k2k_2division,
    "inx_nova_set_4k2k_2division   - set 4k2k in 2 division\n",
    NULL
);
#endif
#endif
#if defined (CONFIG_URSA_8)
#ifdef CONFIG_MSTAR_STR_MINISIZE
U_BOOT_CMD_STR(
#else
U_BOOT_CMD(
#endif
    ursa8_lvds_on,   CONFIG_SYS_MAXARGS, 1,    do_ursa8_lvds_on,
    "ursa8_lvds_on   - set ursa8 lvds on\n",
    NULL
);

U_BOOT_CMD(
    ursa8_set_osd_mode,   CONFIG_SYS_MAXARGS, 1,    do_ursa8_set_osd_mode,
    "ursa8_set_osd_mode   - do_ursa8_set_osd_mode\n",
    NULL
);

#endif

#if (ENABLE_MODULE_BOOT_IR == 1)
U_BOOT_CMD(
    ir_delay, CONFIG_SYS_MAXARGS, 1,    do_ir_delay,
    "ir_delay   -  delay 300ms for IR detect.\n",
    NULL
);
#endif

#if defined (CONFIG_URSA6_VB1)
#ifdef CONFIG_MSTAR_STR_MINISIZE
U_BOOT_CMD_STR(
#else
U_BOOT_CMD(
#endif
    send_I2C_cmd_to_ursa6, CONFIG_SYS_MAXARGS, 1,    do_send_I2C_cmd_to_ursa6,
    "send_I2C_cmd_to_ursa6   -  send I2C command to URSA6\n",
    NULL
);
#endif

U_BOOT_CMD(
    load_environment_first_time,   CONFIG_SYS_MAXARGS, 1,    do_load_environment_first_time,
    "load_environment_first_time   - load mboot environment settings by reading environment.txt from file system\n",
    NULL
);