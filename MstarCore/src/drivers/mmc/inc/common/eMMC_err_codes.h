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
#ifndef __eMMC_ERR_CODES_H__
#define __eMMC_ERR_CODES_H__
//===========================================================
// device status (R1, R1b)
//===========================================================
#define eMMC_R1_ADDRESS_OUT_OF_RANGE     BIT31
#define eMMC_R1_ADDRESS_MISALIGN         BIT30
#define eMMC_R1_BLOCK_LEN_ERROR          BIT29
#define eMMC_R1_ERASE_SEQ_ERROR          BIT28
#define eMMC_R1_ERASE_PARAM              BIT27
#define eMMC_R1_WP_VIOLATION             BIT26
#define eMMC_R1_DEVICE_IS_LOCKED         BIT25
#define eMMC_R1_LOCK_UNLOCK_FAILED       BIT24
#define eMMC_R1_COM_CRC_ERROR            BIT23
#define eMMC_R1_ILLEGAL_COMMAND          BIT22
#define eMMC_R1_DEVICE_ECC_FAILED        BIT21
#define eMMC_R1_CC_ERROR                 BIT20
#define eMMC_R1_ERROR                    BIT19
#define eMMC_R1_CID_CSD_OVERWRITE        BIT16
#define eMMC_R1_WP_ERASE_SKIP            BIT15
#define eMMC_R1_ERASE_RESET              BIT13
#define eMMC_R1_CURRENT_STATE            (BIT12|BIT11|BIT10|BIT9)
#define eMMC_R1_READY_FOR_DATA           BIT8
#define eMMC_R1_SWITCH_ERROR             BIT7
#define eMMC_R1_EXCEPTION_EVENT          BIT6
#define eMMC_R1_APP_CMD                  BIT5

#define eMMC_ERR_R1_31_24       (eMMC_R1_ADDRESS_OUT_OF_RANGE| \
	                             eMMC_R1_ADDRESS_MISALIGN| \
	                             eMMC_R1_BLOCK_LEN_ERROR| \
	                             eMMC_R1_ERASE_SEQ_ERROR| \
	                             eMMC_R1_ERASE_PARAM| \
	                             eMMC_R1_WP_VIOLATION| \
	                             eMMC_R1_LOCK_UNLOCK_FAILED)
#define eMMC_ERR_R1_23_16       (eMMC_R1_COM_CRC_ERROR| \
								 eMMC_R1_ILLEGAL_COMMAND| \
								 eMMC_R1_DEVICE_ECC_FAILED| \
								 eMMC_R1_CC_ERROR| \
								 eMMC_R1_ERROR| \
								 eMMC_R1_CID_CSD_OVERWRITE)
#define eMMC_ERR_R1_15_8        (eMMC_R1_WP_ERASE_SKIP| \
								 eMMC_R1_ERASE_RESET)
#define eMMC_ERR_R1_7_0         (eMMC_R1_SWITCH_ERROR)

#define eMMC_ERR_R1_31_0        (eMMC_ERR_R1_31_24|eMMC_ERR_R1_23_16|eMMC_ERR_R1_15_8|eMMC_ERR_R1_7_0)
#define eMMC_ERR_R1_NEED_RETRY  (eMMC_R1_COM_CRC_ERROR|eMMC_R1_DEVICE_ECC_FAILED|eMMC_R1_CC_ERROR|eMMC_R1_ERROR|eMMC_R1_SWITCH_ERROR)
//===========================================================
// driver error codes
//===========================================================
#define eMMC_ST_SUCCESS                  0

#define eMMC_ST_ERR_MEM_CORRUPT          (0x0001 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_NOT_ALIGN            (0x0002 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_NOT_PACKED           (0x0003 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_DATA_MISMATCH        (0x0004 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_TIMEOUT_WAIT_REG0    (0x0005 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_TIMEOUT_FIFOCLKRDY   (0x0006 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_TIMEOUT_MIULASTDONE  (0x0007 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_TIMEOUT_WAITD0HIGH   (0x0008 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_TIMEOUT_CARDDMAEND   (0x0009 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_TIMEOUT_WAITCIFDEVENT   (0x000A | eMMC_ST_PLAT)
#define eMMC_ST_ERR_FCIE_STS_ERR			(0x000B | eMMC_ST_PLAT)

#define eMMC_ST_ERR_BIST_FAIL            (0x0010 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_DEBUG_MODE           (0x0011 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_FCIE_NO_CLK          (0x0012 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_PARAMETER            (0x0013 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_NOT_INIT             (0x0014 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_INVALID_PARAM        (0x0015 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_PARTITION_CHKSUM     (0x0016 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_NO_PART_INFO         (0x0017 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_NO_PARTITION         (0x0018 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_NO_OK_DDR_PARAM      (0x0019 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_SAVE_DDRT_FAIL       (0x001A | eMMC_ST_PLAT)
#define eMMC_ST_ERR_DDRT_CHKSUM          (0x001B | eMMC_ST_PLAT)
#define eMMC_ST_ERR_DDRT_NONA            (0x001C | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CIS_NNI              (0x001D | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CIS_PNI              (0x001E | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CIS_NNI_NONA         (0x001F | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CIS_PNI_NONA         (0x0020 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_SDR_DETECT_DDR       (0x0021 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_NO_CIS               (0x0022 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_NOT_eMMC_PLATFROM    (0x0023 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_FCIE_NO_RIU          (0x0024 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_INT_TO               (0x0025 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_UNKNOWN_CLK          (0x0026 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_BUILD_DDRT           (0x0027 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_NO_RSP_IN_RAM        (0x0028 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_NO_SLOWER_CLK        (0x0029 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_PAD_ABNORMAL_OFF     (0x0030 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_SAVE_BLEN_FAIL       (0x0031 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_BLEN_CHKSUM          (0x0032 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CHKSUM               (0x0033 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_ERR_DET				 (0x0034 | eMMC_ST_PLAT)

#define eMMC_ST_ERR_CMD1                 (0x0A00 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD1_DEV_NOT_RDY     (0x0A01 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD2                 (0x0A02 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD3_CMD7            (0x0A03 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_R1_31_24             (0x0A04 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_R1_23_16             (0x0A05 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_R1_15_8              (0x0A06 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_R1_7_0               (0x0A07 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD8_CIFD            (0x0A08 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD8_MIU             (0x0A09 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD17_CIFD           (0x0A0A | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD17_MIU            (0x0A0B | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD18                (0x0A0C | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD6                 (0x0A0D | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD13                (0x0A0E | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD12                (0x0A0F | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD24_CIFD           (0x0A10 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD24_CIFD_WAIT_D0H  (0x0A11 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD24_CIFD_CHK_R1    (0x0A12 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD24_MIU            (0x0A13 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD24_MIU_WAIT_D0H   (0x0A14 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD24_MIU_CHK_R1     (0x0A15 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD25                (0x0A16 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD25_WAIT_D0H       (0x0A17 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD25_CHK_R1         (0x0A18 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD9                 (0x0A19 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_SEC_UPFW_TO          (0x0A20 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD16                (0x0A21 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_NO_HS200_1_8V	     (0x0A22 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD21_ONE_BIT	     (0x0A23 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD21_RSP            (0x0A24 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD21_DATA_CRC	     (0x0A25 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD21_NO_DRVING	     (0x0A26 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD21_HS200_FAIL	 (0x0A27 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD21_DATA_CMP	     (0x0A28 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD21_NO_HS200_1_8V  (0x0A29 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_SET_DRV_STRENGTH	 (0x0A2A | eMMC_ST_PLAT)
#define eMMC_ST_ERR_SKEW4           	 (0x0A2B | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD31_MIU            (0x0A2C | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD28                (0x0A2D | eMMC_ST_PLAT)
#define eMMC_ST_ERR_WP_BOOT_PWR_CFG      (0x0A2E | eMMC_ST_PLAT)
#define eMMC_ST_ERR_WP_BOOT_PWR_FAIL     (0x0A2F | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD23                (0x0A30 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD17_RSP                (0x0A31 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD18_RSP                (0x0A32 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD24_RSP                (0x0A33 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD25_RSP                (0x0A34 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD12_RSP                (0x0A35 | eMMC_ST_PLAT)


#define eMMC_ST_ERR_CMD8_ECHO		     (0x0B00 | eMMC_ST_PLAT)
#define	eMMC_ST_ERR_CMD8_NO_RSP		     (0x0B01 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD55_NO_RSP	     (0x0B02 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD55_RSP_CRC	     (0x0B03 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD55_APP_CMD_BIT 	 (0x0B04 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_ACMD41_DEV_BUSY      (0x0B05 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_ACMD41_NO_RSP	     (0x0B06 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD9_CSD_FMT	     (0x0B07 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_ACMD6_NO_RSP	     (0x0B08 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_ACMD6_WRONG_PARA	 (0x0B09 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_ACMD13_NO_RSP	     (0x0B0A | eMMC_ST_PLAT)
#define eMMC_ST_ERR_ACMD13_DAT_CRC	     (0x0B0B | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD6_NO_RSP		     (0x0B0C | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD6_DAT_CRC	     (0x0B0D | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD6_WRONG_PARA	     (0x0B0E | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD6_HS_NOT_SRPO	 (0x0B0F | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD6_SWC_STS_ERR	 (0x0B10 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD6_SWC_STS_CODE	 (0x0B11 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD32_NO_RSP	     (0x0B12 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD32_SEQ_ERR	     (0x0B13 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD32_PARAM_ERR	     (0x0B14 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD32_RESET		     (0x0B15 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD33_NO_RSP	     (0x0B16 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD33_SEQ_ERR	     (0x0B17 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD33_PARAM_ERR	     (0x0B18 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD33_RESET		     (0x0B19 | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD38_NO_RSP	     (0x0B1A | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD38_SEQ_ERR	     (0x0B1B | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD38_PARAM_ERR	     (0x0B1C | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD38_RESET		     (0x0B1D | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD38_TO		     (0x0B1E | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD3536_ERR		     (0x0B1F | eMMC_ST_PLAT)
#define eMMC_ST_ERR_CMD38_ERR		     (0x0B20 | eMMC_ST_PLAT)


#endif /* __eMMC_ERR_CODES_H__ */
