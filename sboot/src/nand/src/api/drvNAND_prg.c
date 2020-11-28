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
#include "../../inc/common/drvNAND.h"
//#include "drvNAND_utl.h"
#define BL2_OFFSET	32*1024
#define CHUNK_HEADER_BINARYID 0x0000B007
#define CHUNK_HEADER_BINARYID_POS	0x7

#define NAND_HASH_END_BLK                   255

static PAIRED_PAGE_MAP_t *ga_tPairedPageMap = (PAIRED_PAGE_MAP_t *)(CONFIG_BOOTRAM_LOADADDR - 0x4000);
#if defined(NC_SEL_FCIE5) && NC_SEL_FCIE5
static U8* gpu8_SpareBuf = (U8*)(CONFIG_BOOTRAM_LOADADDR - 0x5000);
#endif

U32 drvNAND_LoadBLOffset(U8* pu8DMAAddr, U32 u32_Offset, U32 u32_Size);
U32 drvNAND_Load2ndBL(U8* pu8DMAAddr, U32 u32_Size);
U32 drvNAND_LoaduBoot(U8* pu8DMAAddr, U32 u32_BLSize);

static U32 drvNAND_LoadBL(U8* pu8DMAAddr, U32 u32_Offset, U32 u32_Size, U8 u8_IsDMA)
{
	#if (defined(ENABLE_NAND_RIU_MODE) && ENABLE_NAND_RIU_MODE)  || defined(ENABLE_ROM_DMA_FUNCTION) && ENABLE_ROM_DMA_FUNCTION
	PAIRED_PAGE_MAP_t *ga_tPairedPageMapSRAM = (PAIRED_PAGE_MAP_t *) (ROM_PPM_ADDR);		//rom code 's pair-page map
	#endif
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32	u32_Err = UNFD_ST_SUCCESS;
	U32	u32_SectorCnt;
	U32	u32_i;
	U32	u32_j;
	U32	u32_TmpSectorCnt = 0;
	U32	u32_Row;
	U32	u32_SectorIdx;
	U8	*pu8_PBA;
	U8	au8_SpareData[2];
	U8	*pu8_SpareData = au8_SpareData;
	U8	u8_BootStageId;

	//REG_WRITE_UINT16(DEBUG_REG_SYS_L1, 0xD100);

	#ifdef REMAP_PPM_ADDR
	if(u8_IsDMA == 0)
		nand_remap_ppm_addr(&ga_tPairedPageMapSRAM);
	#endif

	u32_SectorCnt = (u32_Size) >> pNandDrv->u8_SectorByteCntBits;
	if(u32_Size & (pNandDrv->u16_SectorByteCnt - 1))
		u32_SectorCnt += 1;

	if(pNandDrv->u8_BL0PBA)
	{
		pu8_PBA = &pNandDrv->u8_BL0PBA;
		u8_BootStageId = BOOT_NONSECURE;
	}
	else
	{
		pu8_PBA = &pNandDrv->u8_HashPBA[1][0];
		u8_BootStageId = BOOT_HASH1;
	}

	while(1)
	{
		if(u8_IsDMA)
		{	
			//prepare dram dma address for spare of FCIE5
			#if defined(NC_SEL_FCIE5) && NC_SEL_FCIE5
			pu8_SpareData = gpu8_SpareBuf;
			#endif
			u32_Err = NC_ReadSectors((*pu8_PBA) << pNandDrv->u8_BlkPageCntBits, 
									0, 
									pu8DMAAddr,
									pu8_SpareData, 
									1);
		}
		#if defined(ENABLE_NAND_RIU_MODE) && ENABLE_NAND_RIU_MODE
		else
		{
			#if defined(SPARE_BUFFER_ADDR) 	//for fcie5 only
			pu8_SpareData = (U8 *)SPARE_BUFFER_ADDR;
			#endif		
			u32_Err = NC_ReadSector_RIUMode((*pu8_PBA) << pNandDrv->u8_BlkPageCntBits, 
											0, 
											pu8DMAAddr,
											pu8_SpareData);			
		}
		#elif defined(ENABLE_ROM_DMA_FUNCTION) && ENABLE_ROM_DMA_FUNCTION
		else
		{
			//prepare sram dma address for spare of FCIE5
			#if defined(SPARE_BUFFER_ADDR) //for fcie5 only
			pu8_SpareData = (U8 *)SPARE_BUFFER_ADDR;
			#endif
			nand_switch_sram((U32)pu8DMAAddr - CONFIG_SRAM_BASE_ADDRESS);
			u32_Err = pNandDrv->pReadSectors((*pu8_PBA) << pNandDrv->u8_BlkPageCntBits, 
											0, 
											pu8DMAAddr,
											pu8_SpareData, 1);			
		}
		#endif
		if(u32_Err==UNFD_ST_SUCCESS && pu8_SpareData[0]==0xFF && pu8_SpareData[1]==u8_BootStageId)
		{
			for(u32_i = 0; u32_i < u32_SectorCnt; )
			{
				u32_SectorIdx = (((u32_Offset >> pNandDrv->u8_SectorByteCntBits) + u32_i) & (pNandDrv->u16_PageSectorCnt - 1));
					
				//calculate page index in a block for pair page map
				u32_j = (u32_i + (u32_Offset >> pNandDrv->u8_SectorByteCntBits)) >> pNandDrv->u8_PageSectorCntBits;

				u32_Row = (*pu8_PBA) << pNandDrv->u8_BlkPageCntBits;
				if(u8_IsDMA)
				{
					u32_TmpSectorCnt = ((u32_i + pNandDrv->u16_PageSectorCnt) < u32_SectorCnt)
				                   				? (pNandDrv->u16_PageSectorCnt-u32_SectorIdx) : (u32_SectorCnt - u32_i);		
					u32_Row += ga_tPairedPageMap[u32_j].u16_LSB;
					//prepare dram dma address for spare of FCIE5
					#if defined(NC_SEL_FCIE5) && NC_SEL_FCIE5
					pu8_SpareData = gpu8_SpareBuf;
					u32_Err = NC_ReadSectors(u32_Row, 
											u32_SectorIdx, 
											pu8DMAAddr + (u32_i << pNandDrv->u8_SectorByteCntBits),
											pu8_SpareData,
											u32_TmpSectorCnt);
					
					#else
					u32_Err = NC_ReadSectors(u32_Row, 
											u32_SectorIdx, 
											pu8DMAAddr + (u32_i << pNandDrv->u8_SectorByteCntBits),
											NULL,
											u32_TmpSectorCnt);
					#endif
					u32_i += u32_TmpSectorCnt;
				}
				#if defined(ENABLE_NAND_RIU_MODE) && ENABLE_NAND_RIU_MODE
				else
				{
					u32_Row += ga_tPairedPageMapSRAM[u32_j].u16_LSB;
					#if defined(SPARE_BUFFER_ADDR)  //for fcie5 only
					pu8_SpareData = (U8 *)SPARE_BUFFER_ADDR;
					u32_Err = NC_ReadSector_RIUMode(u32_Row, 
													u32_SectorIdx, 
													pu8DMAAddr + (u32_i << pNandDrv->u8_SectorByteCntBits),
													pu8_SpareData);
					
					#else	//for fcie3
					u32_Err = NC_ReadSector_RIUMode(u32_Row, 
													u32_SectorIdx, 
													pu8DMAAddr + (u32_i << pNandDrv->u8_SectorByteCntBits),
													NULL);
					#endif
					u32_i++;
				}
				#elif defined(ENABLE_ROM_DMA_FUNCTION) && ENABLE_ROM_DMA_FUNCTION
				else
				{
					u32_Row += ga_tPairedPageMapSRAM[u32_j].u16_LSB;
					
					nand_switch_sram((U32)pu8DMAAddr + (u32_i << pNandDrv->u8_SectorByteCntBits)  - CONFIG_SRAM_BASE_ADDRESS);	
					
					u32_TmpSectorCnt = ((u32_i + pNandDrv->u16_PageSectorCnt) < u32_SectorCnt)
				                   				? (pNandDrv->u16_PageSectorCnt-u32_SectorIdx) : (u32_SectorCnt - u32_i);
					
					#if defined(SPARE_BUFFER_ADDR)  //for fcie5 only
					pu8_SpareData = (U8 *)SPARE_BUFFER_ADDR;
					#endif
					
					u32_Err = pNandDrv->pReadSectors(u32_Row, 
													u32_SectorIdx, 
													pu8DMAAddr + (u32_i << pNandDrv->u8_SectorByteCntBits),
													pu8_SpareData, u32_TmpSectorCnt);
					u32_i += u32_TmpSectorCnt;
				}
				#endif
				#if defined(NC_SEL_FCIE3) && NC_SEL_FCIE3
				if( (u32_Err != UNFD_ST_SUCCESS) || (REG(NC_CTRL)&BIT_NC_ALLONE_FLAG))
				#elif defined(NC_SEL_FCIE5) && NC_SEL_FCIE5
				if( (u32_Err != UNFD_ST_SUCCESS) || (REG(NC_STAT_CHK)&BIT_NC_ALLONE_FLAG))
				#endif
					goto RETRY_READ_BL;
			}

			goto EXIT_BL;
		}

RETRY_READ_BL:
		if((*pu8_PBA)==NAND_HASH_END_BLK)
		{
			//REG_WRITE_UINT16(DEBUG_REG_SYS_L1, 0xD110);
			return UNFD_ST_ERR_NO_BL;
		}

		(*pu8_PBA)++;
	}

EXIT_BL:
	//REG_WRITE_UINT16(DEBUG_REG_SYS_L1, 0xD200);
	return u32_Err;
}

/*
 * This api loads the 2nd BL in the same block of the BL0_PBA or BL1_PBA from offset 32KB
 * 
 */

#if (defined(ENABLE_NAND_RIU_MODE) && ENABLE_NAND_RIU_MODE) || defined(ENABLE_ROM_DMA_FUNCTION) && ENABLE_ROM_DMA_FUNCTION
U32 drvNAND_LoadBLOffset(U8* pu8DMAAddr, U32 u32_Offset, U32 u32_Size)
{
	#if (defined(ENABLE_NAND_RIU_MODE) && ENABLE_NAND_RIU_MODE)	
	
	#if defined(NC_SEL_FCIE3) && NC_SEL_FCIE3
	REG_CLR_BITS_UINT16(NC_REG_PAD_SWITCH, BIT3);
	#elif defined(NC_SEL_FCIE5) && NC_SEL_FCIE5
	REG_WRITE_UINT16(NC_BOOT_MODE, 0);
	REG_CLR_BITS_UINT16(NC_FUN_CTL, BIT_BOOT_MODE);
	#endif

	#elif defined(ENABLE_ROM_DMA_FUNCTION) && ENABLE_ROM_DMA_FUNCTION
	
	#if defined(NC_SEL_FCIE3) && NC_SEL_FCIE3
	REG_SET_BITS_UINT16(NC_REG_PAD_SWITCH, BIT3);
	#elif defined(NC_SEL_FCIE5) && NC_SEL_FCIE5
	REG_WRITE_UINT16(NC_BOOT_MODE, BIT_NAND_BOOT_EN);
	REG_SET_BITS_UINT16(NC_FUN_CTL, BIT_BOOT_MODE);
	#endif
	
	#endif
	
	return(drvNAND_LoadBL(pu8DMAAddr, u32_Offset, u32_Size, 0));
}
#endif

/*
 * This api loads the 2nd BL in the same block of the BL0_PBA or BL1_PBA from offset 32KB
 * 
 */

U32 drvNAND_Load2ndBL(U8* pu8DMAAddr, U32 u32_Size)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;
	U32 u32_i;

	#if defined(NC_SEL_FCIE3) && NC_SEL_FCIE3
	REG_CLR_BITS_UINT16(NC_REG_PAD_SWITCH, BIT3);
	#elif defined(NC_SEL_FCIE5) && NC_SEL_FCIE5
	REG_WRITE_UINT16(NC_BOOT_MODE, 0);
	REG_CLR_BITS_UINT16(NC_FUN_CTL, BIT_BOOT_MODE);
	#endif

	// Load paired page table first
	if(pNandDrv->u8_CellType)
	{
		#if defined(NC_SEL_FCIE3) && NC_SEL_FCIE3
		u32_Err = NC_ReadSectors(pNandDrv->u32_CISRow + pNandDrv->u8_PairPageMapLoc, 0, (U8*)ga_tPairedPageMap, NULL, 2);
		#elif defined(NC_SEL_FCIE5) && NC_SEL_FCIE5
		u32_Err = NC_ReadSectors(pNandDrv->u32_CISRow + pNandDrv->u8_PairPageMapLoc, 0, (U8*)ga_tPairedPageMap, gpu8_SpareBuf, 2);
		#endif
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			//REG_WRITE_UINT16(DEBUG_REG_SYS_L1, 0xD010);
			return UNFD_ST_ERR_NO_BL;
		}
	}
	else
	{
		for(u32_i = 0; u32_i < 512; u32_i ++)
		{
			ga_tPairedPageMap[u32_i].u16_LSB = u32_i;
		}
	}

	return(drvNAND_LoadBL(pu8DMAAddr, BL2_OFFSET, u32_Size, 1));
}

// in order to reduce nand code size in sram, we define a section in dram
// __ATTR_DRAM_CODE__ is defined in drvNAND_xxx_sboot.h
// section is added in sboot.lds.S
#ifndef __ATTR_DRAM_CODE__
	#define __ATTR_DRAM_CODE__ 
#endif
U32 __ATTR_DRAM_CODE__  drvNAND_LoaduBoot(U8* pu8DMAAddr, U32 u32_BLSize)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32         u32_Err = UNFD_ST_SUCCESS;
	U32         u32_SectorCnt;
	U32         u32_i;
	U32         u32_j;
	U32         u32_TmpSectorCnt;
	U32         u32_Row;
	U8	        u8_PBA;
	U16         u16_BlkPageCnt;
	U8	        au8_SpareData[2];
	U8	*pu8_SpareData = au8_SpareData;
	
	#if defined(NC_SEL_FCIE5) && NC_SEL_FCIE5
	pu8_SpareData = (U8 *)gpu8_SpareBuf;
	#endif

	//REG_WRITE_UINT16(DEBUG_REG_SYS_L1, 0xD000);
	u16_BlkPageCnt = pNandDrv->u16_BlkPageCnt >> pNandDrv->u8_CellType;	
	u32_SectorCnt = (u32_BLSize) >> pNandDrv->u8_SectorByteCntBits;
	if(u32_BLSize & (pNandDrv->u16_SectorByteCnt - 1))
		u32_SectorCnt += 1;
	
	//REG_WRITE_UINT16(DEBUG_REG_SYS_L1, 0xD100);
	
	//1st uboot locate at the next good block of BL1PBA
	
	u8_PBA = pNandDrv->u8_BL0PBA != 0 ? pNandDrv->u8_BL0PBA : pNandDrv->u8_HashPBA[2][0]-1;

	RETRY_READ_UBOOT2:
	
	for(u32_i = 0; u32_i < u32_SectorCnt; u32_i += pNandDrv->u16_PageSectorCnt)
	{
		u32_TmpSectorCnt = ((u32_i + pNandDrv->u16_PageSectorCnt) < u32_SectorCnt) ?
							pNandDrv->u16_PageSectorCnt : (u32_SectorCnt - u32_i);
		
		u32_j = (u32_i & (pNandDrv->u16_PageSectorCnt * u16_BlkPageCnt - 1)) >> pNandDrv->u8_PageSectorCntBits;
		
		if(u32_j == 0 )
		{	
			search_next_block:
			u8_PBA ++;
			// Read 1st sector for checking good block
			u32_Row = u8_PBA << pNandDrv->u8_BlkPageCntBits;

			#if defined(ENABLE_CACHE) && ENABLE_CACHE
			//only invalidate first page of Mboot for checking header.
			if(u32_i == 0)
			{
				nand_translate_DMA_address_Ex(
					(U32)pu8DMAAddr, pNandDrv->u16_SectorByteCnt*u32_TmpSectorCnt);
				
				#if defined(NC_SEL_FCIE5) && NC_SEL_FCIE5
				nand_translate_DMA_address_Ex( (U32)gpu8_SpareBuf, pNandDrv->u16_SpareByteCnt);
				#endif
				
			}
			#endif

			u32_Err = NC_ReadSectors(u32_Row, 0, pu8DMAAddr + (u32_i << pNandDrv->u8_SectorByteCntBits),
			                         pu8_SpareData, u32_TmpSectorCnt);

			// Check the bad block infomation
			if( pu8_SpareData[0] != 0xFF  || u32_Err != UNFD_ST_SUCCESS)
			{
				goto search_next_block;
			}
			else
			{
				// Check chunk header binary ID 0x0000B007
				if(u32_i == 0)
				{
					if( ((U32*)(pu8DMAAddr))[CHUNK_HEADER_BINARYID_POS] != CHUNK_HEADER_BINARYID)
					{
						goto search_next_block;
					}
				}
			}
		}
		else
		{
			u32_Row = u8_PBA << pNandDrv->u8_BlkPageCntBits;
			u32_Row += ga_tPairedPageMap[u32_j].u16_LSB;

			//always need spare address for dma in FCIE5
			#if defined(NC_SEL_FCIE5) && NC_SEL_FCIE5
			u32_Err = NC_ReadSectors(u32_Row, 0, pu8DMAAddr + (u32_i << pNandDrv->u8_SectorByteCntBits),
										pu8_SpareData, u32_TmpSectorCnt);
			#else
			u32_Err = NC_ReadSectors(u32_Row, 0, pu8DMAAddr + (u32_i << pNandDrv->u8_SectorByteCntBits),
										NULL, u32_TmpSectorCnt);
			#endif
		}

		#if defined(NC_SEL_FCIE3) && NC_SEL_FCIE3
		if((u32_Err != UNFD_ST_SUCCESS) || (REG(NC_CTRL)&BIT_NC_ALLONE_FLAG))
		#elif defined(NC_SEL_FCIE5) && NC_SEL_FCIE5
		if( (u32_Err != UNFD_ST_SUCCESS) || (REG(NC_STAT_CHK)&BIT_NC_ALLONE_FLAG))
		#endif
		{
			if(u8_PBA==NAND_HASH_END_BLK)
				return UNFD_ST_ERR_NO_BL;
			
			goto RETRY_READ_UBOOT2;
		}

	}
	
	//REG_WRITE_UINT16(DEBUG_REG_SYS_L1, 0xD200);
	
	return u32_Err;
}
