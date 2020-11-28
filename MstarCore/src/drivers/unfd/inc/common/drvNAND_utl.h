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
#ifndef __DRVNAND_UTL_H__
#define __DRVNAND_UTL_H__

#include "drvNAND.h"

extern U32 drvNAND_ProbeReadSeq(void);
extern U32 drvNAND_CheckPartInfo(U32 u32_PageIdx);
extern U32 drvNAND_SearchCIS(void);
extern U32 drvNAND_SearchCIS1(U8 *u8_CIS1Blk);
extern U32 drvNAND_InitBBT(INIT_BBT_t *pInitBBT);
extern void drvNAND_ParseNandInfo(NAND_FLASH_INFO_t *pNandInfo);


typedef UNFD_PACK0 struct _TEST_ALIGN_PACK {

	U8	u8_0;
	U16	u16_0;
	U32	u32_0, u32_1;

} UNFD_PACK1 TEST_ALIGN_PACK_t;
extern U32 drvNAND_CheckAlignPack(U8 u8_AlignByteCnt);

extern void dump_mem(unsigned char *buf, int cnt);
extern void dump_nand_info(NAND_FLASH_INFO_t *pNandInfo);
extern void dump_part_records(PARTITION_RECORD_t *pRecord, int cnt);
extern void dump_part_info(PARTITION_INFO_t *pPartInfo);
extern void dump_miu_records(MIU_RECORD_t *records, int cnt);
extern void dump_miu_part(MIU_PART_t *pMiuPart);
extern void dump_general_blk_info(BLK_INFO_t *pBlkInfo);
extern void dump_nand_driver(NAND_DRIVER *pNandDrv);

extern U32 drvNAND_CompareCISTag(U8 *tag);
extern U8  drvNAND_CountBits(U32 u32_x);
extern U32 drvNAND_CheckSum(U8 *pu8_Data, U16 u16_ByteCnt);

extern PARTITION_RECORD_t *drvNAND_SearchPartition(PARTITION_RECORD_t *pRecord,
												   U16 u16_PartType);

extern U32 drvNAND_ReadBlk(U8 *pu8_DestAddr, U8 u8_PartType, U16 u16_PBA,
							U16 u16_LBA, U32 u32_StartSector, 
							U32 u32_SectorCnt);
extern U32 drvNAND_WriteBlk(U8 *pu8_DestAddr, U8 u8_PartType, U16 u16_PBA,
							U16 u16_LBA, U32 u32_StartSector,
							U32 u32_SectorCnt);

extern U32 drvNAND_WriteBlkNonBackup(U8 *pu8_DestAddr, U8 u8_PartType, U16 u16_PBA,
					 U16 u16_LBA,	U32 u32_StartSector,
					 U32 u32_SectorCnt);

extern U32 drvNAND_CheckSpareSpacePattern(U8 *au8_SpareBuf, U32 u32_PageIdx);
extern U32 drvNAND_IsGoodBlk(U16 u16_BlkIdx);
extern U32 drvNAND_IsFreeBlk(U16 u16_BlkIdx);
extern U8  drvNAND_CheckAll0xFF(U8* pu8_Buf, U32 u32_ByteCnt);
extern U16 drvNAND_FindFreePage(U16 u16_BlkIdx);
extern U16 drvNAND_FindFreeLSBPage(U16 u16_BlkIdx);
extern U32 drvNAND_MoveBlkData(U16 u16_DestBlk, U16 u16_SrcBlk, U16 u16_PageCnt);

extern U32 drvNAND_MarkBadBlk(U16 u16_BlkIdx);
extern U32 drvNAND_ErasePhyBlk(U16 u16_BlkIdx);
extern U32 drvNAND_ReadPhyPage(U32 u32_PageIdx, U8 *pu8_Data, U8 *pu8_Spare);
extern U32 drvNAND_WritePhyPage(U32 u32_PageIdx, U8 *pu8_Data, U8 *pu8_Spare);
extern U32 drvNAND_LFSRReadPhyPage(U32 u32_PageIdx, U8 *pu8_Data, U8 *pu8_Spare);
extern U32 drvNAND_LFSRWritePhyPage(U32 u32_PageIdx, U8 *pu8_Data, U8 *pu8_Spare);

extern int nand_CheckEmptyPageFalseAlarm(U8 *main, U8 *spare);
extern int nand_ReadDisturbance_BigImg(U32  u32_BlkRow, U8 u8_torture, U32 (*nand_markbad)(U32));
extern U32 nand_ReadDisturbance_BigImgRestore(U32 (*nand_markbad)(U32));

extern U32 drvNAND_WriteBlkByteOffset(U8 *pu8_DestAddr, U8 u8_PartType, U16 u16_PBA, U16 u16_LBA, U32 u32_StartByte, U32 u32_ByteCnt);
extern U32 drvNAND_ReadBlkByteOffset(U8 *pu8_DestAddr, U8 u8_PartType, U16 u16_PBA, U16 u16_LBA, U32 u32_StartByte, U32 u32_ByteCnt);

extern U32 drvNAND_ParseAddrToADMA(U8 * pu8_DMADataBuf,  U32 u32_ByteCnt, U8 u8_Direction, ADMA_DESC_t* ADMADesc, U8 u8_IsEnd);

/*
 * Return Zero Bit Count of input byte against 0xFF
 */
static inline int ZeroBitCountfor0xFFByte(U8 u8_Byte)
{
	int i;
	int sum = 0;
	if(u8_Byte ^ 0xFF)
	{
		for(i = 0; i < 8; i ++)
			sum += ((u8_Byte >> i)  & 0x1) ^ 1;
	}
	return sum;
}

#endif /* __DRVNAND_UTL_H__ */
