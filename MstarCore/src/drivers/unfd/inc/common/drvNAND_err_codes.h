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
#ifndef __UNFD_ERR_CODES_H__
#define __UNFD_ERR_CODES_H__

#define  UNFD_ST_SUCCESS                   0

#define  UNFD_ST_ERR_2L_MAP2_1P           (0x0000 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_BL0_ECCERR           (0x0001 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_BL1_ECCERR           (0x0002 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_CIS0_ECCERR          (0x0003 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_CIS1_ECCERR          (0x0004 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_CIS_NAND_ERR         (0x0005 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_CIS_PART_ERR         (0x0006 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_DATA_CMP_FAIL        (0x0007 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_DISKCONN_FAIL        (0x0008 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_DISK_CONN_FAIL       (0x0009 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_DISKINIT_FAIL        (0x000A | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_E_BUSY               (0x000B | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_ECC_FAIL             (0x000C | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_ECC_FAIL_RM          (0x000D | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_E_FAIL               (0x000E | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_E_PROTECTED          (0x000F | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_E_TIMEOUT            (0x0010 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_EXCEED_CAPACITY      (0x0011 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_HAL_R_INVALID_PARAM  (0x0012 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_HAL_W_INVALID_PARAM  (0x0013 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_INVALID_ADDR         (0x0014 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_INVALID_ECC_REG51    (0x0015 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_INVALID_ECC_REG52    (0x0016 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_INVALID_ECC_REG53    (0x0017 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_INVALID_PARAM        (0x0018 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_INVALID_PART         (0x0019 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_IOLUP_FAIL           (0x001A | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_LACK_BLK             (0x001B | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_LOGI_PART            (0x001C | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_MIU_PARAM0_ECCERR    (0x001D | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_MIU_PARAM1_ECCERR    (0x001E | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_MIU_RPATCH_TIMEOUT   (0x001F | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NO_BL                (0x0020 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NO_BLK_FOR_BL0       (0x0021 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NO_BLK_FOR_BL1       (0x0022 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NO_BLK_FOR_CIS0      (0x0023 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NO_BLK_FOR_CIS1      (0x0024 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NO_BLK_FOR_MIU0      (0x0025 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NO_BLK_FOR_MIU1      (0x0026 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NO_BLK_FOR_OS0       (0x0027 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NO_BLK_FOR_OS1       (0x0028 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NO_CIS               (0x0029 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NO_GOOD_BLK          (0x002A | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NO_MIU_PARAM         (0x002B | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NO_NFIE              (0x002C | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NO_OS                (0x002D | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NOT_READY            (0x002E | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NULL_PTR             (0x002F | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_OS0_ECCERR           (0x0030 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_OS1_ECCERR           (0x0031 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_PHY_PART             (0x0032 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_PLAT_INIT_0          (0x0033 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_RST_TIMEOUT          (0x0034 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_R_TIMEOUT            (0x0035 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_R_TIMEOUT_RM         (0x0036 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_SIGNATURE_FAIL       (0x0037 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_UNKNOWN_ECC_TYPE     (0x0038 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_UNKNOWN_ID           (0x0039 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_UNKNOWN_RSEQ         (0x003A | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_W_BUSY               (0x003B | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_W_FAIL               (0x003C | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_W_PROTECT            (0x003D | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_W_PROTECTED          (0x003E | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_W_TIMEOUT            (0x003F | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_W_TIMEOUT_RM         (0x0040 | UNFD_ST_PLAT)
#define  UNFD_ST_NO_NANDINFO              (0x0041 | UNFD_ST_PLAT)
#define  UNFD_ST_NO_PARTINFO              (0x0042 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_BAD_BLK              (0x0043 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_SEMAPHORE            (0x0044 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_FTL_NOT_FORMAT       (0x0045 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_FTL_NO_ROOT_BLK      (0x0046 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_FTL_VERSION_MISS     (0x0047 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NOT_ALIGN            (0x0048 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NOT_PACKED           (0x0049 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_FAT_SHIFT            (0x004A | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NO_FREE_BLK_FOR_RD   (0x004B | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_EC_SHIFT             (0x004C | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NOT_TOGGLE_DDR       (0x004D | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NO_TOGGLE_DDR_TIMING (0x004E | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_NOT_ONFI_DDR         (0x004F | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_SET_FEATURE_TIMEOUT  (0x0050 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_TOGGLE_SET_SYNC_MODE (0x0051 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_LFSR_RD_LATCH        (0x0052 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_LFSR_DDRTIMING       (0x0053 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_PROBABLE_TOGGLE_DDR       (0x0054 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_PAD_UNSUPPORT_DDR_NAND    (0x0055 | UNFD_ST_PLAT)
#define  UNFD_ST_ERR_SETUP_READ_RETRY_FAIL     (0x0056 | UNFD_ST_PLAT)
#define	 UNFD_ST_ERR_INVAL_CIFD_CNT            (0x0057 | UNFD_ST_PLAT)
#define	 UNFD_ST_ERR_NAND_BUSY                 (0x0058 | UNFD_ST_PLAT)

#endif /* __UNFD_ERR_CODES_H__ */
