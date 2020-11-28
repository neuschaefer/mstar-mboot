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
#include <linux/string.h>
#include "../../inc/common/drvNAND.h"
#include "../../inc/common/drvNAND_utl.h"
//#include <linux/string.h>

#define NANDINFO_ADDR				 0x82000000
#define PARTINFO_ADDR				 0x82100000
#define READBACKCHECK				 0

static unsigned char nand_buffer[16384] __attribute((aligned(64)));
static U16 u16_CISBlkIdx[2];

U32 drvNAND_EraseAllGoodPhyBlk(U16 *pu16_GoodBlkCnt, U16 *pu16_BadBlkIdxList, U16 *pu16_BadBlkCnt)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();

	U32 u32_Err;
	U16 u16_BlkIdx;

	//drvNAND_lock_sem();
	for (u16_BlkIdx = 0; u16_BlkIdx < pNandDrv->u16_BlkCnt; u16_BlkIdx++ )
	{
		if( drvNAND_IsGoodBlk(u16_BlkIdx) )
		{
			u32_Err = drvNAND_ErasePhyBlk(u16_BlkIdx);
			if (u32_Err != UNFD_ST_SUCCESS) {
                nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "Erase Blk 0x%04x failed with EC: 0x%08x\n",
                    (unsigned int)u16_BlkIdx, (unsigned int)u32_Err);

				drvNAND_MarkBadBlk(u16_BlkIdx);
			}
		}
	}
	//drvNAND_unlock_sem();

	return UNFD_ST_SUCCESS;
}

//------------------------------------------------------------------------
// 1. when this function ok, the drvNAND_SearchCIS called at the end,
//    would setup NANDINFO & PARTINFO in NAND_DRIVER.
// 2. memory for pPartInfo (512B), setup by drvNAND_get_DrvContext_PartInfo.
//------------------------------------------------------------------------
U32 drvNAND_Init(void)
{
	U32 u32_Err = UNFD_ST_SUCCESS;
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
#if NAND_BUF_USE_STACK
	U8 au8_SectorBuf[1024];
	U8 au8_SpareBuf[64];
#else
	U8 *au8_SectorBuf;
	U8 *au8_SpareBuf;
#endif

	nand_debug(UNFD_DEBUG_LEVEL_HIGH, 1, "\n");

	//drvNAND_CheckAlignPack(UNFD_CACHE_LINE);

	memset(pNandDrv, '\0', sizeof(NAND_DRIVER));

	NC_PlatformInit();
	// setup memory for pPartInfo (512B)
	pNandDrv->pPartInfo = drvNAND_get_DrvContext_PartInfo();
	memset(pNandDrv->pPartInfo, '\0', NAND_PARTITAION_BYTE_CNT);

	nand_pads_switch(1);
	//nand_clock_setting(pNandDrv->u32_Clk);
	
	
	u32_Err = drvNAND_ProbeReadSeq();
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		u32_Err = UNFD_ST_ERR_UNKNOWN_RSEQ;
		goto INIT_END;
	}
    //Ensure bus detection correct
    NC_EraseBlk(0);

	u32_Err = NC_ReadID();
	if (u32_Err != UNFD_ST_SUCCESS) {
        nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "Failed to read ID with EC: 0x%08x\n", (unsigned int)u32_Err);
		u32_Err = UNFD_ST_ERR_UNKNOWN_ID;
		goto INIT_END;
	}
    pNandDrv->u16_PageByteCnt = 0x800;
    pNandDrv->u16_SpareByteCnt = 0x80;
    pNandDrv->u16_ECCType = ECC_TYPE_32BIT1KB;
    NC_ConfigNandFlashContext();
    NC_Init();
    pNandDrv->u16_Reg48_Spare |= (1 << 12);
    NC_Config();
	// Try to read sector according to u8_WordMode assigned by strapping
	au8_SectorBuf = (U8*)pNandDrv->PlatCtx_t.pu8_PageDataBuf;
	au8_SpareBuf = (U8*)pNandDrv->PlatCtx_t.pu8_PageSpareBuf;
	u32_Err = NC_ReadSectors(0, 0, au8_SectorBuf, au8_SpareBuf, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		// If read sector fail, change u8_WordMode and try again
		if (pNandDrv->u8_WordMode == 0)
		{
			pNandDrv->u8_WordMode = 1;
			pNandDrv->u16_Reg50_EccCtrl |= BIT_NC_WORD_MODE;
		}
		else
		{
			pNandDrv->u8_WordMode = 0;
			pNandDrv->u16_Reg50_EccCtrl &= (~BIT_NC_WORD_MODE);
		}

		nand_debug(UNFD_DEBUG_LEVEL, 1, "retry auto-checking 8/16 bits:0x%X\n", pNandDrv->u8_WordMode);

		u32_Err = NC_ReadSectors(0, 0, au8_SectorBuf, au8_SpareBuf, 1);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(UNFD_DEBUG_LEVEL, 1, "fails to auto-checking 8/16 bits\n");
			goto INIT_END;
		}
	}
	nand_debug(UNFD_DEBUG_LEVEL, 1, "Complete auto-checking 8/16 bits:0x%X\n", pNandDrv->u8_WordMode);

	u32_Err = drvNAND_SearchCIS();

    #if defined(ENABLE_CUS_READ_ENHANCEMENT) && ENABLE_CUS_READ_ENHANCEMENT
	if(u32_Err == UNFD_ST_SUCCESS)
		CUS_BBT_Init();
    #endif

    #if defined(BLD_LD_OS_RD) && BLD_LD_OS_RD
    if(UNFD_ST_SUCCESS != drvNAND_BldRD_Init())
    {
		nand_debug(UNFD_DEBUG_LEVEL_ERROR,1,"Warning: no free blk for RD !!\n");
		nand_die();
    }
    #endif

INIT_END:

	return u32_Err;
}


U32 drvNAND_CheckCIS(U8 *pu8_CISData)
{
	NAND_INFO_t *pNandInfo = (NAND_INFO_t*)pu8_CISData;
	PARTITION_INFO_t *pPartInfo = (PARTITION_INFO_t*)(pu8_CISData + 0x200);
	U32 u32_ChkSum;

	nand_debug(UNFD_DEBUG_LEVEL_HIGH, 1, "\n");

	if (drvNAND_CompareCISTag(pNandInfo->au8_Tag)) {
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "Tag mismatch\n");
		return UNFD_ST_ERR_CIS_NAND_ERR;
	}

	u32_ChkSum = drvNAND_CheckSum(pu8_CISData + 0x24, 0x32 - 0x24);
	if (u32_ChkSum != pNandInfo->u32_ChkSum) {

        nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "NAND Info chksum mismatch: 0x%08x, 0x%08x\n",
            (unsigned int)u32_ChkSum, (unsigned int)pNandInfo->u32_ChkSum);

		dump_mem(pu8_CISData, 0x200);
		return UNFD_ST_ERR_CIS_NAND_ERR;
	}

	u32_ChkSum = drvNAND_CheckSum(pu8_CISData + 0x200 + 0x04, 0x200 - 0x04);
	if (u32_ChkSum != pPartInfo->u32_ChkSum) {

        nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "Part Info chksum mismatch: 0x%08x, 0x%08x\n",
            (unsigned int)u32_ChkSum, (unsigned int)pPartInfo->u32_ChkSum);

		dump_mem(pu8_CISData + 0x200, 0x200);
		return UNFD_ST_ERR_CIS_PART_ERR;
	}

	//dump_nand_info(pNandInfo);
	dump_part_info(pPartInfo);

	return UNFD_ST_SUCCESS;
}


U32 drvNAND_WriteCIS(U8 *pu8_CISData)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
#if NAND_BUF_USE_STACK
	U8 au8_PageBuf[4096];
	U8 au8_SpareBuf[128];
#else
	U8 *au8_PageBuf = (U8*)pNandDrv->PlatCtx_t.pu8_PageDataBuf;
	U8 *au8_SpareBuf = (U8*)pNandDrv->PlatCtx_t.pu8_PageSpareBuf;
#endif
	NAND_INFO_t *pNandInfo = (NAND_INFO_t*)pu8_CISData;
	PARTITION_INFO_t *pPartInfo = (PARTITION_INFO_t*)(pu8_CISData + 0x200);
	BLK_INFO_t *pBlkInfo = (BLK_INFO_t*)au8_SpareBuf;
	U32 u32_Err = UNFD_ST_SUCCESS;
	U16 u16_BlkIdx;
	U16 u32_PageIdx;
	U32 u32_ByteCnt;
	U8 u8_CISIdx;
	U8 au8_BBT[512];
	INIT_BBT_t *pInitBBT = (INIT_BBT_t *)au8_BBT;

	nand_debug(UNFD_DEBUG_LEVEL_HIGH, 1, "\n");


    memset(au8_BBT, '\0', 512);

	memset(pNandDrv->au8_ID, '\0', NAND_ID_BYTE_CNT);
	memcpy(pNandDrv->au8_ID, pNandInfo->au8_ID, pNandInfo->u8_IDByteCnt);
	pNandDrv->u8_IDByteCnt     = pNandInfo->u8_IDByteCnt;
	pNandDrv->u16_SpareByteCnt = pNandInfo->u16_SpareByteCnt;
	pNandDrv->u16_PageByteCnt  = pNandInfo->u16_PageByteCnt;
	pNandDrv->u16_BlkPageCnt   = pNandInfo->u16_BlkPageCnt;
	pNandDrv->u16_BlkCnt       = pNandInfo->u16_BlkCnt;
	pNandDrv->u16_ECCType      = pNandInfo->u16_ECCType;
	pNandDrv->u32_Config       = pNandInfo->u32_Config;
	//dump_nand_info(pNandInfo);

	u32_ByteCnt = pPartInfo->u16_PartCnt * pPartInfo->u16_UnitByteCnt;
	memcpy(pNandDrv->pPartInfo, pPartInfo, sizeof(*pPartInfo) + u32_ByteCnt);
	dump_part_info(pPartInfo);

	NC_ConfigNandFlashContext();
	NC_Init();

	if(pNandDrv->u8_CISBlk == 0xFF) // No CIS found, initialize BBT now
	{
		nand_debug(UNFD_DEBUG_LEVEL_HIGH, 1, "No CIS found, initialize BBT now\n");
		drvNAND_InitBBT(pInitBBT);
	}
	else
	{
		nand_debug(UNFD_DEBUG_LEVEL_HIGH, 1, "get original BBT from %Xh blk\n", pNandDrv->u8_CISBlk);
		u32_Err = NC_ReadSectors((pNandDrv->u8_CISBlk<<pNandDrv->u8_BlkPageCntBits)+2, 0, au8_PageBuf, au8_SpareBuf, 1);
		if(u32_Err == UNFD_ST_SUCCESS)
		{
			memcpy(au8_BBT, au8_PageBuf, 512);
		}
		else
		{
			nand_debug(UNFD_DEBUG_LEVEL_HIGH, 1, "Read BBT fail, initialize BBT again\n");
			drvNAND_InitBBT(pInitBBT);
		}
	}
	nand_debug(UNFD_DEBUG_LEVEL_HIGH, 1, "Initial BBT-->\n");
	dump_mem((unsigned char *) au8_BBT, 512);

	u8_CISIdx = 0;

	/* Search for two good blocks within the first 10 physical blocks */
	for (u16_BlkIdx = 0; u16_BlkIdx < 10; u16_BlkIdx++) {
        pNandDrv->u16_ECCType = ECC_TYPE_32BIT1KB;
        pNandDrv->u16_PageByteCnt  = 0x800;
        pNandDrv->u16_SpareByteCnt = 0x80;
        NC_ConfigNandFlashContext();
		NC_Init();
		pNandDrv->u16_Reg48_Spare |= (1 << 12);
		NC_Config();

		/* Check first page of block */
		u32_PageIdx = u16_BlkIdx << pNandDrv->u8_BlkPageCntBits;
		u32_Err = NC_ReadSectors(u32_PageIdx, 0, au8_PageBuf, au8_SpareBuf, 1);
		if (u32_Err != UNFD_ST_SUCCESS)
            nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "NC_ReadSectors(0x%X)=0x%X\n", (unsigned int)u32_PageIdx, (unsigned int)u32_Err);
		if (au8_SpareBuf[0] != 0xFF) {
			nand_debug(UNFD_DEBUG_LEVEL_WARNING, 1, "Skip bad blk 0x%04x\n", u16_BlkIdx);
			continue;
		}

		/* Reeset NAND driver and FCIE to the original settings */
		pNandDrv->u16_ECCType = pNandInfo->u16_ECCType;
        pNandDrv->u16_PageByteCnt  = pNandInfo->u16_PageByteCnt;
        pNandDrv->u16_SpareByteCnt = pNandInfo->u16_SpareByteCnt;
		NC_ConfigNandFlashContext();
		NC_Init();
		pNandDrv->u16_Reg48_Spare &= ~(1 << 12);
		NC_Config();

		u32_Err = drvNAND_ErasePhyBlk(u16_BlkIdx);
		if (u32_Err != UNFD_ST_SUCCESS) {
            nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "Erase blk 0x%04x failed with EC: 0x%08x\n",
                (unsigned int)u16_BlkIdx, (unsigned int)u32_Err);

			drvNAND_MarkBadBlk(u16_BlkIdx);
			continue;
		}

		memset(au8_PageBuf, '\0', pNandDrv->u16_PageByteCnt);
		//memcpy(au8_PageBuf, pNandInfo, sizeof(*pNandInfo));
		memcpy(au8_PageBuf, pNandInfo, 512);
		memset(au8_SpareBuf, '\0', pNandDrv->u16_SpareByteCnt);

		pBlkInfo->u8_BadBlkMark = 0xFF;
		pBlkInfo->u8_PartType = 0;
		pBlkInfo->u16_BlkAddr = u8_CISIdx;
		*(U16*)pBlkInfo->au8_Misc = 0;

		/*
		 * Configure NAND driver and FCIE to
		 *   512-byte Page Size
		 *   512-byte Sector Size
		 *   512-byte / 4bits ECC Type
		 */

        pNandDrv->u16_ECCType = ECC_TYPE_32BIT1KB;
        pNandDrv->u16_PageByteCnt  = 0x800;
        pNandDrv->u16_SpareByteCnt = 0x80;
		NC_ConfigNandFlashContext();
		NC_Init();
		pNandDrv->u16_Reg48_Spare |= (1 << 12);
		NC_Config();

        //u32_Err = drvNAND_WritePhyPage(u32_PageIdx, au8_PageBuf, au8_SpareBuf);
        u32_Err = NC_WriteSectors(u32_PageIdx, 0, au8_PageBuf, au8_SpareBuf, 1);	
		/* Reeset NAND driver and FCIE to the original settings */
		pNandDrv->u16_ECCType = pNandInfo->u16_ECCType;
        pNandDrv->u16_PageByteCnt  = pNandInfo->u16_PageByteCnt;
        pNandDrv->u16_SpareByteCnt = pNandInfo->u16_SpareByteCnt;
		NC_ConfigNandFlashContext();
		NC_Init();
		pNandDrv->u16_Reg48_Spare &= ~(1 << 12);
		NC_Config();

		if (u32_Err != UNFD_ST_SUCCESS) {
            nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "Write Nand Info failed with EC: 0x%08x\n", (unsigned int)u32_Err);
			drvNAND_MarkBadBlk(u16_BlkIdx);
			continue;
		}

		/*
		 *  Write Partition Info to the 2nd page
		 */
		memset(au8_PageBuf, '\0', pNandDrv->u16_PageByteCnt);

		//u32_ByteCnt = pPartInfo->u16_UnitByteCnt * pPartInfo->u16_PartCnt;
		//memcpy(au8_PageBuf, pPartInfo, sizeof(*pPartInfo) + u32_ByteCnt);
		memcpy(au8_PageBuf, pPartInfo, 512);
		*(U16*)pBlkInfo->au8_Misc = 1;

        //u32_Err = drvNAND_WritePhyPage(++u32_PageIdx, au8_PageBuf, au8_SpareBuf);
        u32_Err = NC_WriteSectors(++u32_PageIdx, 0, au8_PageBuf, au8_SpareBuf, 1);	
		if (u32_Err != UNFD_ST_SUCCESS) {
            nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "Write Part Info failed with EC: 0x%08x\n", (unsigned int)u32_Err);
			drvNAND_MarkBadBlk(u16_BlkIdx);
			continue;
		}

		/*
		 *  Write Initial BBT to the 3rd page
		 */
		memset(au8_PageBuf, '\0', pNandDrv->u16_PageByteCnt);
		memcpy(au8_PageBuf, au8_BBT, 512);
		*(U16*)pBlkInfo->au8_Misc = 2;

        //u32_Err = drvNAND_WritePhyPage(++u32_PageIdx, au8_PageBuf, au8_SpareBuf);
        u32_Err = NC_WriteSectors(++u32_PageIdx, 0, au8_PageBuf, au8_SpareBuf, 1);	
		if (u32_Err != UNFD_ST_SUCCESS) {
            nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "Write Initial BBT failed with EC: 0x%08x\n", (unsigned int)u32_Err);
			drvNAND_MarkBadBlk(u16_BlkIdx);
			continue;
		}

		nand_debug(UNFD_DEBUG_LEVEL_HIGH, 1, "CIS%d is written to blk 0x%04x\n",
				   u8_CISIdx, u16_BlkIdx);

		u16_CISBlkIdx[u8_CISIdx] = u16_BlkIdx;
		
		if (++u8_CISIdx == 2)
			break;
	}

	/* Reeset NAND driver and FCIE to the original settings */
	pNandDrv->u16_ECCType = pNandInfo->u16_ECCType;
    pNandDrv->u16_PageByteCnt  = pNandInfo->u16_PageByteCnt;
    pNandDrv->u16_SpareByteCnt = pNandInfo->u16_SpareByteCnt;
	NC_ConfigNandFlashContext();
	NC_Init();
	pNandDrv->u16_Reg48_Spare &= ~(1 << 12);
	NC_Config();

	switch (u8_CISIdx) {
	case 0:
		u32_Err = UNFD_ST_ERR_NO_BLK_FOR_CIS0;
		break;
	case 1:
		u32_Err = UNFD_ST_ERR_NO_BLK_FOR_CIS1;
		break;
	case 2:
		u32_Err = UNFD_ST_SUCCESS;
		break;
	}



	return u32_Err;
}


U32 drvNAND_WriteCIS_from_DRAM(U32 nandInfoAddr, U32 partInfoAddr)
{
	U32 u32_i, u32_j, u32_Err;
	//U16 u16_GoodBlkCnt,u16_BadBlkIdxList, u16_BadBlkCnt;
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	NAND_INFO_t *pNandInfo;
    //PARTITION_INFO_t *pPartInfo = (PARTITION_INFO_t*)PARTINFO_ADDR;
	//U8 *pu8_Buf = (U8*) NANDINFO_ADDR;
    PARTITION_INFO_t *pPartInfo = (PARTITION_INFO_t*)partInfoAddr;
	U8 *pu8_Buf = (U8*) nandInfoAddr;
    //printf("nandInfoAddr=0X%x\n",nandInfoAddr);
    //printf("partInfoAddr=0X%x\n",partInfoAddr); 
	u32_Err = UNFD_ST_SUCCESS;

	pNandDrv->u8_CISBlk=0xFF;

	drvNAND_Init();
    


	
	for(u32_i=0; u32_i<(16384); u32_i+=0x200)
	{
		pNandInfo = (NAND_INFO_t*)(pu8_Buf + u32_i);
		
		// compare ID
		for(u32_j=0; u32_j<pNandInfo->u8_IDByteCnt; u32_j++)
		{
			if(pNandInfo->au8_ID[u32_j] != pNandDrv->au8_ID[u32_j])
				break;
		}
		if(u32_j == pNandDrv->u8_IDByteCnt)
			break;
	}
	if(u32_i == (16384))
	{
		nand_debug(0,1,"Err. no NANDInfo in NNI !!!\n");
		return 1; // error
	}
	nand_debug(0,1,"found NANDInfo in NNI\n");

	
	// config NAND driver
	pNandDrv->u8_IDByteCnt     = pNandInfo->u8_IDByteCnt;
	pNandDrv->u16_SpareByteCnt = pNandInfo->u16_SpareByteCnt;
	pNandDrv->u16_PageByteCnt  = pNandInfo->u16_PageByteCnt;
	pNandDrv->u16_BlkPageCnt   = pNandInfo->u16_BlkPageCnt;
	pNandDrv->u16_BlkCnt       = pNandInfo->u16_BlkCnt;
	pNandDrv->u16_PageSectorCnt= pNandInfo->u16_PageByteCnt>>9;
	pNandDrv->u16_ECCType      = pNandInfo->u16_ECCType;
	pNandDrv->u32_Config       = pNandInfo->u32_Config;

	
	
	memcpy(nand_buffer,pNandInfo,512);
	memcpy(nand_buffer+0x200,pPartInfo,512);

	u32_Err = drvNAND_CheckCIS(nand_buffer);

	if(u32_Err != UNFD_ST_SUCCESS)
	{
        printf("Check CIS fail, ErrCode: %x\r\n", (unsigned int)u32_Err);
		return u32_Err;
	}
	
	NC_ConfigNandFlashContext();
	NC_Init();

	//drvNAND_EraseAllGoodPhyBlk(&u16_GoodBlkCnt, &u16_BadBlkIdxList, &u16_BadBlkCnt);
	//pNandDrv->u8_CISBlk=0xFF;

	u32_Err = drvNAND_WriteCIS(nand_buffer);

	if(u32_Err != UNFD_ST_SUCCESS)
	{
        printf("Write CIS fail, ErrCode: %x\r\n",(unsigned int)u32_Err);
		return u32_Err;
	}

	printf("Write CIS is done\r\n");
	return u32_Err;
	//udelay(30000000);

	//memcpy(nand_buffer_read,cis_info,0x400);

	//drvNAND_WriteMIU(nand_buffer_read);
	//drvNAND_LoadMIUParam(nand_buffer_write);

	//drvNAND_Init_n();
	//drvNAND_WriteUBOOT(nand_buffer_read);
	//drvNAND_Init_ROM();
	//drvNAND_LoadML(nand_buffer_read);

	//drvNAND_LoadML_Comp(nand_buffer_write);

	//Set_hw_config(nand_buffer_write, 0x11, 1);
	
}
U32 drvNAND_Write_DDRT_ML(
	U32 u32_DDRT_NAND_Off, U8* pu8DDR_Buf, U32 u32_DDRTByteCount, 
	U32 u32_ML_NAND_Off, U8* pu8ML_Buf, U32 u32_MLByteCount
)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	
    U32 u32_Err = UNFD_ST_SUCCESS/*, u32_idx*/;
    U16 u16_DDRTPageCount, u16_MLPageCount, u16_DDRTOffPage,u16_MLOffPage/*,u16_page_idx*/;
	U8 u8_idx;
    //U8 *au8_PageBuf = (U8*)pNandDrv->PlatCtx_t.pu8_PageDataBuf;
    U8 *au8_SpareBuf = (U8*)pNandDrv->PlatCtx_t.pu8_PageSpareBuf;
	
	//Translate to page count
	u16_DDRTPageCount = u32_DDRTByteCount >> (U32)pNandDrv->u8_PageByteCntBits;
	if(u32_DDRTByteCount % ((U32) pNandDrv->u16_PageByteCnt))
		u16_DDRTPageCount++;	
	
	u16_MLPageCount = u32_MLByteCount >> (U32)pNandDrv->u8_PageByteCntBits;
	if(u32_MLByteCount % ((U32) pNandDrv->u16_PageByteCnt))
		u16_MLPageCount++;	

	memset(au8_SpareBuf,0xFF, pNandDrv->u16_SpareByteCnt);

	if(!u32_DDRT_NAND_Off || !u32_ML_NAND_Off)
		return UNFD_ST_ERR_INVALID_ADDR;
	
	u16_DDRTOffPage =  u32_DDRT_NAND_Off >> (U32)pNandDrv->u8_PageByteCntBits;
	u16_MLOffPage =  u32_ML_NAND_Off >> (U32)pNandDrv->u8_PageByteCntBits;	

	for(u8_idx = 0; u8_idx < 2; u8_idx++)
	{
		u32_Err = NC_WritePages( (u16_CISBlkIdx[u8_idx] << pNandDrv->u8_BlkPageCntBits) + u16_DDRTOffPage, 
			pu8DDR_Buf, NULL, (U32)u16_DDRTPageCount);
		
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			printf("Fail to write DDR Table %d\n", u8_idx);
			return u32_Err;
		}
		
#if READBACKCHECK
		for (u16_page_idx = 0; u16_page_idx < u16_DDRTPageCount; u16_page_idx++)
		{
			u32_Err = NC_ReadPages ( (u16_CISBlkIdx[u8_idx] << pNandDrv->u8_BlkPageCntBits) + u16_DDRTOffPage + u16_page_idx, 
				au8_PageBuf, au8_SpareBuf, 1);

			for(u32_idx = 0; u32_idx < pNandDrv->u16_PageByteCnt; u32_idx++)
				if(au8_PageBuf[u32_idx] != pu8DDR_Buf[u32_idx])
				{
					printf("DDR Table R/W mismatch page: %X idx: %X  W: %X ;R: %X\n",
						u16_page_idx,u32_idx, pu8DDR_Buf[u32_idx], au8_PageBuf[u32_idx]);
					
				}
		}
#endif
		
		u32_Err = NC_WritePages( (u16_CISBlkIdx[u8_idx] << pNandDrv->u8_BlkPageCntBits) + u16_MLOffPage , 
			pu8ML_Buf, NULL, (U32)u16_MLPageCount);
		
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			printf("Fail to write MasterLoader %d\n", u8_idx);
			return u32_Err;
		}
		
#if READBACKCHECK
		for (u16_page_idx = 0; u16_page_idx < u16_MLPageCount; u16_page_idx++)
		{
			u32_Err = NC_ReadPages ( (u16_CISBlkIdx[u8_idx] << pNandDrv->u8_BlkPageCntBits) + u16_MLOffPage + u16_page_idx, 
				au8_PageBuf, au8_SpareBuf, 1);

			for(u32_idx = 0; u32_idx < pNandDrv->u16_PageByteCnt; u32_idx++)
				if(au8_PageBuf[u32_idx] != pu8ML_Buf[u32_idx])
				{
					printf("MasterLoader R/W mismatch page: %X idx: %X  W: %X ;R: %X\n",
						u16_page_idx,u32_idx, pu8ML_Buf[u32_idx], au8_PageBuf[u32_idx]);
					
				}
		}
#endif
		
	}
	return u32_Err;

	
}
