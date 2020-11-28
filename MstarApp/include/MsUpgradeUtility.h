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

#ifndef _Ms_UPGRADEUTILITY_H_
#define _Ms_UPGRADEUTILITY_H_
#include <MsTypes.h>
#include <ShareType.h>
#include <common.h>
#include <command.h>
#include <exports.h>

#define ENV_FORCEUPGRADE "force_upgrade"
#define ENV_UPGRADE_NAME        "UpgradeImage"
#define USB_DEVICE           "usb_device"
#define USB_PARTITION        "usb_partition"

typedef enum
{
    EN_UPDATE_MODE_NONE,
    EN_UPDATE_MODE_TFTP,
    EN_UPDATE_MODE_USB,
    EN_UPDATE_MODE_OAD,
    EN_UPDATE_MODE_NET,
    EN_UPDATE_MODE_USB_WITH_SEG_DECRYPTED,
    EN_UPDATE_MODE_NET_WITH_SEG_DECRYPTED,
}EN_UPDATE_MODE;

int check_script_encrypt(char *script_buf);    
int check_file_partition(char *upgradeFile,int *device, int *partition);

void set_dont_overwrite_byname(char *upgradeFile);

int do_file_part_load (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_check_file_partition(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);

void setUpgradeFsMountName(char* pFsMount);
char* getUpgradeFsMountName(void);

//---------------------------------------------------------------- ---------------------------------    
/// Check if this cmd should be executed or not.
/// @param next_line  \b IN: cmd that will be executed later.
/// @return BOOLEAN   \b OUT: TRUE: This cmd should be skipped. FALSE:This cmd should be executed.
//-------------------------------------------------------------------------------------------------
BOOLEAN check_skip_cmd(char *next_line);

//---------------------------------------------------------------- ---------------------------------    
/// This serial apis are for protecting the specific partitions are overwrited. ex: customer
/// This cmd is used to init this function
//-------------------------------------------------------------------------------------------------
int do_dont_overwrite_init(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);

//---------------------------------------------------------------- ---------------------------------    
/// This serial apis are for protecting the specific partitions are overwrited. ex: customer
/// This cmd is used to register which partition should not be overwrite
//-------------------------------------------------------------------------------------------------
int do_dont_overwrite(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);

//---------------------------------------------------------------- ---------------------------------    
/// This serial apis are for protecting the specific partitions are overwrited. ex: customer
/// This cmd is used to free all registered partitions.
//-------------------------------------------------------------------------------------------------
int do_dont_overwrite_free(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);

//---------------------------------------------------------------- ---------------------------------    
/// This serial apis are for protecting the specific partitions are overwrited. ex: customer
/// This api is used to enable this function
//-------------------------------------------------------------------------------------------------
void dont_overwrite_enable(void);

//---------------------------------------------------------------- ---------------------------------    
/// This serial apis are for protecting the specific partitions are overwrited. ex: customer
/// This api is used to disable this function
//-------------------------------------------------------------------------------------------------
void dont_overwrite_disable(void);


//---------------------------------------------------------------- ---------------------------------    
/// These serial apis are for forcing to upgrade the specific partitions, even these partitions should not be overwrite. ex:customer
/// The priority of these serial apis are higher than do_dont_overwrite_xxxx
/// This api is used to init this function.
/// @return int                                 \b OUT: 0:success, -1: fail
//-------------------------------------------------------------------------------------------------
int do_force_overwirte_init(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);

//---------------------------------------------------------------- ---------------------------------    
/// These serial apis are for forcing to upgrade the specific partitions, even these partitions should not be overwrite. ex:customer
/// The priority of these serial apis are higher than do_dont_overwrite_xxxx
/// This api is used to register which partition must overwrite
/// @param partitionName.                 \b IN: partition name
/// @return int                                 \b OUT: 0:success, -1: fail
//-------------------------------------------------------------------------------------------------
int do_force_overwrite(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);

//---------------------------------------------------------------- ---------------------------------    
/// These serial apis are for forcing to upgrade the specific partitions, even these partitions should not be overwrite. ex:customer
/// The priority of these serial apis are higher than do_dont_overwrite_xxxx
/// This api is used to free all registered partitions.
/// @return int                                 \b OUT: 0:success, -1: fail
//-------------------------------------------------------------------------------------------------
int do_force_overwrite_free(void);

//---------------------------------------------------------------- ---------------------------------    
/// These serial apis are for forcing to upgrade the specific partitions, even these partitions should not be overwrite. ex:customer
/// The priority of these serial apis are higher than do_dont_overwrite_xxxx
/// This api is used to disable this function
//-------------------------------------------------------------------------------------------------
void do_force_overwrite_disable(void);

//---------------------------------------------------------------- ---------------------------------    
/// These serial apis are for forcing to upgrade the specific partitions, even these partitions should not be overwrite. ex:customer
/// The priority of these serial apis are higher than do_dont_overwrite_xxxx
/// This api is used to enable this function
//-------------------------------------------------------------------------------------------------
void do_force_overwrite_enable(void);

//-------------------------------------------------------------------------------------------------    
/// Check if the script file is right or not. This script file is in frot of the upgrade image.
/// @param  upgradeFile                 \b IN: The file name of upgrade image   
/// @param  scriptBuf                     \b IN: The dram address of scriptBuf   
/// @return  int                             \b OUT: 0: script file is right. -1: script file is wrong
//-------------------------------------------------------------------------------------------------
int check_script_crc(char * upgradeFile, char *scriptBuf);

//-------------------------------------------------------------------------------------------------    
/// Set the file name of upgrade image to uboot's environment variable
/// @param  str                             \b IN: The file name of upgrade image   
/// @return  int                             \b OUT: 0: set file name successfully. -1: set file name fail
//-------------------------------------------------------------------------------------------------
int setUpgradeFileName(char *str);

//-------------------------------------------------------------------------------------------------    
/// delete an environment variable, and this environmet recall the file name of upgrade image
/// @return  int                             \b OUT: 0: delete file name successfully. -1: delete file name fail
//-------------------------------------------------------------------------------------------------
int deleteUpgradeFileName(void);

//-------------------------------------------------------------------------------------------------    
/// setup the script file's size, and this script file is stored in front of the upgrade image.
/// The default size is 0x4000
/// @param  size                            \b IN: The file size of upgrade script file
/// @return  int                             \b OUT: 0: setup size successfully. -1: setup size fail
//-------------------------------------------------------------------------------------------------
int setScritSizeOfUpgradeImage(unsigned int size);

//-------------------------------------------------------------------------------------------------    
/// clear the script file's size to zero, and this script file is stored in front of the upgrade image.
/// @return  int                             \b OUT: 0: clear size successfully. -1: clear size fail
//-------------------------------------------------------------------------------------------------
int clearScritSizeOfUpgradeImage(void);

//-------------------------------------------------------------------------------------------------    
/// get the script file's size, and this script file is stored in front of the upgrade image.
/// If no setting, this function will return the default value. Default value is 0x4000 now.
/// @return  unsigned int                             \b OUT: 
//-------------------------------------------------------------------------------------------------
unsigned int getScritSizeOfUpgradeImage(void);

//-------------------------------------------------------------------------------------------------    
/// setup current upgrade mode
/// @return  unsigned int                             \b OUT: 0: setup successfully, -1: setup fail
//-------------------------------------------------------------------------------------------------
int setUpgradeMode(EN_UPDATE_MODE enMode);

//-------------------------------------------------------------------------------------------------    
/// get current upgrade mode
/// @return  EN_UPDATE_MODE                      \b OUT:
//-------------------------------------------------------------------------------------------------
EN_UPDATE_MODE getUpgradeMode(void);

//-------------------------------------------------------------------------------------------------    
/// calculate the total amount of commands in the script file
/// PS: This function will destory the datas that are stored in the buffer.
/// @param  script_buf                                  \b IN: the buffer for the script file
/// @return  unsigned int                               \b OUT: the total amount of commands
//-------------------------------------------------------------------------------------------------
unsigned int check_script_cmd_count(char *script_buf);

#if defined (CONFIG_R2_BRINGUP)

//-------------------------------------------------------------------------------------------------    
/// This api are for upgrading nuttx 
//-------------------------------------------------------------------------------------------------
int do_update_nuttx(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
#endif
#endif
