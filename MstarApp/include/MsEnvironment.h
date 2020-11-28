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

#ifndef __MS_ENVIRONMENT_H__
#define __MS_ENVIRONMENT_H__

//#include <environment.h>
#include "MsTypes.h"


#if defined(ENABLE_MODULE_ENV_IN_SERIAL)
# if defined(CONFIG_SECURITY_BOOT)
#  ifndef  SEC_INFOR_SIZE
#   define SEC_INFOR_SIZE    0x10000
#  endif
#  ifndef  SEC_INFOR_ADDR
#   define SEC_INFOR_ADDR    (CONFIG_ENV_ADDR - SEC_INFOR_SIZE)
#  endif
#  ifndef  SEC_INFOR_ADDR_BAK
#   define SEC_INFOR_ADDR_BAK    (SEC_INFOR_ADDR - SEC_INFOR_SIZE)
#  endif
#endif


#if  defined(CONFIG_ENV_IS_IN_NAND)
# if  defined(CONFIG_SECURITY_BOOT)
#  ifndef  SEC_INFOR_BLOCK_NUM
#   define SEC_INFOR_BLOCK_NUM    0x3
#  endif
#  ifndef  SEC_INFOR_ADDR
#   define SEC_INFOR_ADDR    (CONFIG_ENV_ADDR - (SEC_INFOR_BLOCK_NUM * nand->erasesize))
#  endif
#  ifndef  SEC_INFOR_ADDR_BAK
#   define SEC_INFOR_ADDR_BAK    (SEC_INFOR_ADDR - (SEC_INFOR_BLOCK_NUM * nand->erasesize))
#  endif
# endif
# endif
#endif


//#if defined(CONFIG_ENV_IS_IN_MMC)
//# if defined(CONFIG_SECURITY_BOOT)
 //
//#  endif
//#endif

#define MAX_MMAP_ID_LEN 32
#define ENV_CFG_PREFIX  "ENV="
#if (ENABLE_MODULE_ENV_IN_NAND==1)
#define ENV_CFG         "ENV=NAND"
#elif (ENABLE_MODULE_ENV_IN_UBI == 1)
#define ENV_CFG         "ENV=UBI"
#elif (ENABLE_MODULE_ENV_IN_SERIAL==1)
#define ENV_CFG         "ENV=SERIAL"
//#elif (CONFIG_COMMANDS & CONFIG_ENV_IN_SERIAL_512K)
//#define ENV_CFG         "ENV=SERIAL_512K"
#elif (ENABLE_MODULE_ENV_IN_MMC == 1)
#define ENV_CFG         "ENV=EMMC"
#else
#error "Wrong ENV_CFG settings!"
#endif

#define SECURITY_ENV_CFG_PREFIX  "SECURITY="
#if defined(CONFIG_SECURITY_BOOT)
#define SECURITY_ENV_CFG         "SECURITY=ON"
#else
#define SECURITY_ENV_CFG         "SECURITY=OFF"
#endif

#define INFO_EXCHANGE_CFG           "info_exchange"
#if (ENABLE_MODULE_INFO_IN_UBI_FILE == 1)
#define INFO_EXCHANGE_STORAGE       "ubifile"
#elif (ENABLE_MODULE_INFO_IN_SERIAL_ENV == 1)
#define INFO_EXCHANGE_STORAGE       "spi"
#elif (ENABLE_MODULE_INFO_IN_MMC_ENV == 1)
#define INFO_EXCHANGE_STORAGE       "emmc"
#else
#define INFO_EXCHANGE_STORAGE       "unknow"
#endif
int do_testmode_set(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_set_bootargs( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_del_boogargs_cfg (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_set_bootargs_cfg (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_sync_mmap_to_env( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_mmap_to_env( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_config2env( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_add_bootcheckpoints (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);

//-------------------------------------------------------------------------------------------------    
/// Delet the member that exist in bootargs
/// For example: del_bootargs_cfg("autotest")
/// @param delCfg                           \b IN: the member that exist in the env 'bootargs'
/// @return  int                              \b OUT: 0, delete sucessfully , -1, delete fail
//-------------------------------------------------------------------------------------------------
int del_bootargs_cfg(char *delCfg);

//-------------------------------------------------------------------------------------------------    
/// Edit a new member to bootargs
/// For example: set_bootargs_cfg("autotest","autotest=ture");
/// @param prefix_cfg                           \b IN: the new member's prefix
/// @param setCfg                               \b IN: the new member's content
/// @return  int                                   \b OUT: 0, edit sucessfully , -1, edit fail
//-------------------------------------------------------------------------------------------------
int set_bootargs_cfg(char * prefix_cfg,char *setCfg,MS_BOOL bDontSaveEnv);


//-------------------------------------------------------------------------------------------------    
/// Restore the envirnoment variable from supernova's mmap
/// @param id_mmap                           \b IN: the id  in mmap
/// @param env_addr                               \b IN: the name of addr in env
/// @param env_len                               \b IN: the name of len in env
/// @return  int                                   \b OUT: 0, edit sucessfully , -1, edit fail
/// example:
/// #define E_MMAP_ID_PM51_USAGE_MEM_AVAILABLE                     0x0000200000
/// id = "E_MMAP_ID_PM51_USAG"
/// env_addr="PM51_ADDR"
/// env_leng="PM51_LEN"
//-------------------------------------------------------------------------------------------------
int setMmapInfo2Env(char *id_mmap, char *env_addr, char *env_len);

//-------------------------------------------------------------------------------------------------    
/// Set the boot time information to envirnoment variable 'bootargs'
/// @param none
/// @return  none
//-------------------------------------------------------------------------------------------------
void _boottime_set_to_env(void);

#if CONFIG_RESCUE_ENV
int    saveenv_rescue     (void);
#endif

#endif
