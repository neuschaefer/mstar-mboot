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
#include <common.h>
#include <MsTest.h>
#include <MsEnvironment.h>
#include <MsApiPM.h>

#if CONFIG_MINIUBOOT
#else

#if defined (CONFIG_POINTS_HANDLER_ENABLE)
U_BOOT_CMD(
    add_bootcp, CONFIG_SYS_MAXARGS, 1,    do_add_bootcheckpoints,
    "add_bootcp   - Perform to enable the booting check-points(reboot 15 times, then auto disable)\n",
    NULL
);
#endif

U_BOOT_CMD(
    testmode , CONFIG_SYS_MAXARGS, 1,    do_testmode_set ,
    "set testmode into bootargs.",
    "testmode <mode>\n"
    "mode:autotest,moduletest,hsl,mdebugtest"
);

#endif

U_BOOT_CMD(
    bootargs_set,    CONFIG_SYS_MAXARGS,    1,     do_set_bootargs,
    "Set info exchange and set to boot args. ",
    "    -  \n"
);

#if CONFIG_MINIUBOOT
#else
U_BOOT_CMD(
    config2env,    CONFIG_SYS_MAXARGS,    1,     do_config2env,
    "Set config to environment.",
    "    -  \n"
);
#endif

#if (CONFIG_ENABLE_RTPM)
#ifdef CONFIG_MSTAR_STR_MINISIZE
U_BOOT_CMD_STR(
#else
U_BOOT_CMD(
#endif
    runtime_pm, CONFIG_SYS_MAXARGS, 1,    do_run_time_pm,
    "if boot to PM\n",
    NULL
);
#endif

#if CONFIG_MINIUBOOT
#else
U_BOOT_CMD(
    dc, 2, 1, do_del_boogargs_cfg,
    "delete the specific cofig that is in the bootargs\n",
    "[config]\n"
    "For example: dl autotest\n"    
);

U_BOOT_CMD(
    ac, 3, 1, do_set_bootargs_cfg,
    "set a new config to the bootargs\n",
    "[config][content]\n"
    "For example: add autotest true\n"    
);

U_BOOT_CMD(
    sync_mmap, 1, 1, do_sync_mmap_to_env,
    "Sync the some id's address and len to env and bootargs from supernova's mmap\n",
    "\n"
);

U_BOOT_CMD(
    m2e, 4, 1, do_mmap_to_env,
    "Restore the address and len to env from supernova's mmap\n",
    "[ID] [n1] [n2]"
    "For example:"
    "ID:E_MMAP_ID_PM51_USAG"
    "n1: This is an name of env, this env store the addr for ID"
    "n2: This is an name of env, this env store the len for ID"
    "\n"
);
#endif

