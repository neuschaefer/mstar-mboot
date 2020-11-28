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
#include <MsUpgrade.h>
#include <MsUpgradeUtility.h>
#include <config.h>
#include <command.h>

#if (ENABLE_MODULE_NET==1)
U_BOOT_CMD(
    mstar ,    CONFIG_SYS_MAXARGS,    1,     do_mstar,
    "update kernal & root file system automatically by script file",
    "mstar [script_file_name]\n"
    "set CmdAbort = 0 in env to ignore the abort when cmd error\n"
);
#endif

#if (ENABLE_MODULE_USB == 1)

U_BOOT_CMD(
    ustar ,    CONFIG_SYS_MAXARGS,    1,     do_ustar,
    "ustar   - update kernal & root file system automatically by script file\n",
    "[script_file_name] \n"
    "    - when use this command \n"
    "    - at first use usb start \n"
    "    - then use ustar \n"
    "    -  \n"
);

#if CONFIG_MINIUBOOT
#else
U_BOOT_CMD(
    udstar ,    CONFIG_SYS_MAXARGS,    1,     do_udstar,
    "Execute the script file that is stored in usb disk\n",
    "[script_file_name] \n"
    "If you don't input a file name, udstar will use the defatult file name \n"    
);
#endif

#endif

#if (ENABLE_MODULE_NETUPDATE == 1)
U_BOOT_CMD(
    nstar ,    CONFIG_SYS_MAXARGS,    1,     do_nstar,
    "nstar   - update softwave system automatically via net\n",
   NULL
);
#endif

#if CONFIG_RESCUE_ENV
U_BOOT_CMD(
    bstar ,    CONFIG_SYS_MAXARGS,    1,     do_bstar,
    "bstar   - update softwave system automatically via backup\n",
    NULL
);
#endif

#if (ENABLE_MODULE_OAD == 1)
U_BOOT_CMD(
    ostar ,    CONFIG_SYS_MAXARGS,    1,     do_ostar,
    "ostar   - update softwave system automatically via oad\n",
    NULL
);
#endif

#if (ENABLE_MODULE_ENV_UPGRADE_FROM_BANK == 1)
U_BOOT_CMD(
    rstar ,    CONFIG_SYS_MAXARGS,    1,     do_rstar,
    "do env update from the lastest spi bank.\n",
    "    -  \n"
);
#endif

#if CONFIG_MINIUBOOT
#else
#if ( (ENABLE_MODULE_OAD == 1) || (ENABLE_MODULE_NETUPDATE == 1) || (ENABLE_MODULE_USB == 1))
U_BOOT_CMD(
    mbup ,    CONFIG_SYS_MAXARGS,    1,     do_mboot_upgrade,
    "mboot upgrade\n",
    "[mboot dram buffer addr] [mboot size] \n"
);
#endif
#endif

int do_aes_decrypt(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]); //MB100_BRINGUP


U_BOOT_CMD(aesdec, 5, 0, do_aes_decrypt,
            "decrypt aes file\n",
            "aesdec interface(hex) device(hex) filename(hex) addr(hex)\n"
        );

