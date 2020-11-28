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
#ifndef _Mstar_Boot_Header_
#define _Mstar_Boot_Header_
#include <CusBoot.h>


#if (ENABLE_MODULE_MMC == 1)
#define BOOT_COMMAND "mmc read.p 0x45000000 recovery 0x00800000; bootm 0x45000000"
#else
#define BOOT_COMMAND "nand read.e 0x45000000 recovery 0x00800000; bootm 0x45000000"
#endif

#if defined (CONFIG_R2_BRINGUP)
#define HEADER_SIZE 128
#define MAGIC_ID_LEN 16
#define BOOT_CONFIG_FLAG_SIZE 1
#define ONE_G_MIU_INTERVAL_FLAG_SIZE 1

#define DEBUG_INFO_SIZE 0x200

extern char TeeMagicID[MAGIC_ID_LEN];

typedef struct
{
    unsigned int uitee_header_len;
    unsigned int uitee_start_paddr;    
    unsigned int uitee_start_vaddr;
    unsigned int uitee_image_size;
    unsigned long long ulltime;
    unsigned long long ullTeeBinVersion;
    unsigned int uitee_mem_len;
    unsigned int uihw_aes_paddr;    
    unsigned int uihw_aes_buffer_len;    
    unsigned int uiHeaderVersion;
    unsigned int uicrc_value;
}_ST_TEE_HEADER;


typedef struct
{
    _ST_TEE_HEADER _sthd;
    unsigned char reserved[HEADER_SIZE-sizeof(_ST_TEE_HEADER)-ONE_G_MIU_INTERVAL_FLAG_SIZE-BOOT_CONFIG_FLAG_SIZE-MAGIC_ID_LEN];    
    unsigned char one_g_miu_interval[ONE_G_MIU_INTERVAL_FLAG_SIZE];
    unsigned char bootConfigFlag[BOOT_CONFIG_FLAG_SIZE];
    unsigned char ucMagicID[MAGIC_ID_LEN];
}ST_TEE_HEADER;
#endif


typedef enum
{
    EN_BOOT_MODE_UNKNOWN,
    EN_BOOT_MODE_NORMAL,
    EN_BOOT_MODE_RECOVERY,
    EN_BOOT_MODE_FORCEUGRADE,
    EN_BOOT_MODE_USB_UPGRADE,
    EN_BOOT_MODE_NET_UPGRADE,
    EN_BOOT_MODE_OAD_UPGRADE,
#if (ENABLE_MODULE_ENV_UPGRADE_FROM_BANK == 1)
    EN_BOOT_MODE_ENV_UPGRADE,
#endif
    EN_BOOT_MODE_USB_RECOVRY_UPGRADE,
    EN_BOOT_MODE_OTA_UPGRADE,
    EN_BOOT_MODE_RECOVRY_WIPE_DATA,
    EN_BOOT_MODE_RECOVRY_WIPE_CACHE,
    EN_BOOT_MODE_UART_DEBUG,
#if CONFIG_RESCUE_ENV
    EN_BOOT_MODE_BRICK_TERMINATOR,
#endif
#if (ENABLE_MODULE_SYSTEM_RESTORE == 1)
    EN_BOOT_MODE_SYSTEM_RESTORE,
#endif

}EN_BOOT_MODE;

int do_bootcheck (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int isBootToRecovery(void);

#if ENABLE_BOOT_SPI_ECOS
int do_read_boot_info (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
#endif

#if (CONFIG_R2_BRINGUP)
int do_readNuttx (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_bootNuttx(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_save_nconfig(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_load_nconfig(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_set_tee_debug_level (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
#endif

#if defined(CONFIG_TRUSTZONE_ENABLE)
void do_bootNuttx(void);
#endif

#endif
