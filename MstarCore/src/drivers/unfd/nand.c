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
#include <common.h>


#include <linux/mtd/compat.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>

#include "inc/common/drvNAND.h"

#define DMA_MODE					1

U32 u32CurRow = 0;
U32 u32CurCol = 0;
U32 u32CIFDIdx = 0;
U16 u16ByteIdxofPage = 0;
U32 u32WriteLen = 0;
S32 s32_ECCStatus = 0;

int sectoridx=0;

U8 u8MainBuf[8192*4] UNFD_ALIGN1;
U8 u8SpareBuf[640*4] UNFD_ALIGN1;

#define CONFIG_NANDDRV_DEBUG 1

#if (CONFIG_NANDDRV_DEBUG)
#define NAND_DEBUG(fmt, args...) nand_debug(UNFD_DEBUG_LEVEL_LOW, 1, fmt, ##args)
#else
#define NAND_DEBUG(fmt, args...)
#endif


/* These really don't belong here, as they are specific to the NAND Model */
static uint8_t scan_ff_pattern[] = {0xff};

/* struct nand_bbt_descr - bad block table descriptor */
static struct nand_bbt_descr _titania_nand_bbt_descr = {
	.options = NAND_BBT_2BIT | NAND_BBT_LASTBLOCK | NAND_BBT_VERSION | NAND_BBT_CREATE | NAND_BBT_WRITE,
	.offs = 5,
	.len = 1,
	.pattern = scan_ff_pattern
};

static struct nand_ecclayout unfd_nand_oob_custom;

static uint8_t bbt_pattern[] = {'B', 'b', 't', '0' };
static uint8_t mirror_pattern[] = {'1', 't', 'b', 'B' };

static struct nand_bbt_descr _titania_bbt_main_descr = {
	.options		= NAND_BBT_LASTBLOCK | NAND_BBT_CREATE | NAND_BBT_WRITE |
					  NAND_BBT_2BIT | NAND_BBT_VERSION | NAND_BBT_PERCHIP,
	.offs			= 1,
	.len			= 3,
	.veroffs		= 4,
	.maxblocks		= NAND_BBT_BLOCK_NUM,
	.pattern		= bbt_pattern
};

static struct nand_bbt_descr _titania_bbt_mirror_descr = {
	.options		= NAND_BBT_LASTBLOCK | NAND_BBT_CREATE | NAND_BBT_WRITE |
					  NAND_BBT_2BIT | NAND_BBT_VERSION | NAND_BBT_PERCHIP,
	.offs			= 1,
	.len			= 3,
	.veroffs		= 4,
	.maxblocks		= NAND_BBT_BLOCK_NUM,
	.pattern		= mirror_pattern
};

static void _titania_nand_hwcontrol(struct mtd_info *mtdinfo, int cmd, unsigned int ctrl)
{
	NAND_DEBUG("NANDDrv_HWCONTROL()\n");

	switch(cmd)
	{
		case NAND_CTL_SETNCE:
			NAND_DEBUG("NAND_CTL_SETNCE\n");
			// Let FCIE3 control the CE
			break;
		case NAND_CTL_CLRNCE:
			NAND_DEBUG("NAND_CTL_CLRNCE\n");
			// Let FCIE3 control the CE

			break;
		case NAND_CTL_SETCLE:
			NAND_DEBUG("NAND_CTL_SETCLE\n");
			// We have no way to control CLE in NFIE/FCIE2/FCIE3
			break;
		case NAND_CTL_CLRCLE:
			NAND_DEBUG("NAND_CTL_CLRCLE\n");
			// We have no way to control CLE in NFIE/FCIE2/FCIE3
			break;

		case NAND_CTL_SETALE:
			NAND_DEBUG("NAND_CTL_SETALE\n");
			// We have no way to control CLE in NFIE/FCIE2/FCIE3
			break;
		case NAND_CTL_CLRALE:
			NAND_DEBUG("NAND_CTL_CLRALE\n");
			// We have no way to control CLE in NFIE/FCIE2/FCIE3
			break;

		default:
			NAND_DEBUG("UNKNOWN CMD\n");
			break;
  }

  return;
}


static int _titania_nand_device_ready(struct mtd_info *mtdinfo)
{
	NAND_DEBUG("NANDDrv_DEVICE_READY()\n");

	#if 0 // We have wait ready in each HAL functions
	drvNAND_WaitReady(1000);
	#endif

	return 1;
}

static void _titania_nand_write_buf(struct mtd_info *mtd, const u_char *buf, int len)
{

	NAND_DEBUG("NANDDrv_WRITE_BUF() 0x%X\r\n",len);

	NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();
	U8 *pu8MainBuf;
	U8 *pu8SpareBuf;

	if( len >= pNandDrv->u16_PageByteCnt * pNandDrv->u8_PlaneCnt ) // whole page or Main area only
	{
		if( len > pNandDrv->u16_PageByteCnt * pNandDrv->u8_PlaneCnt ) // whole page
		{
			#if !defined(CONFIG_ARM)
			if( ((U32)buf) >= 0xC0000000 ) // For MIU1 (MIPS)
			{
				memcpy(u8MainBuf, buf, pNandDrv->u16_PageByteCnt * pNandDrv->u8_PlaneCnt);
				memcpy(u8SpareBuf, buf + (pNandDrv->u16_PageByteCnt * pNandDrv->u8_PlaneCnt), pNandDrv->u16_SpareByteCnt * pNandDrv->u8_PlaneCnt);
				pu8MainBuf = u8MainBuf;
				pu8SpareBuf = u8SpareBuf;
			}
			else
			#endif
			{
				pu8MainBuf = (U8*)buf;
				pu8SpareBuf = (U8*)buf + (pNandDrv->u16_PageByteCnt * pNandDrv->u8_PlaneCnt);
			}

			#if defined(FCIE_LFSR) && FCIE_LFSR
			if(pNandDrv->u8_RequireRandomizer == 1)
				NC_EnableLFSR();
			#endif

			#if DMA_MODE
			if(pNandDrv->u8_PlaneCnt > 1)
				NC_WritePages2P(u32CurRow, pu8MainBuf, pu8SpareBuf, 1);
			else
				NC_WritePages(u32CurRow, pu8MainBuf, pu8SpareBuf, 1);
			#else
			NC_WritePage_RIUMode(u32CurRow, pu8MainBuf, pu8SpareBuf);
			#endif
		}
		else // main area only
		{
			memcpy(u8MainBuf, buf, len);
			u32WriteLen += len;
			u16ByteIdxofPage += len;
		}
	}
	else
	{
		if((u32WriteLen==0) && (u16ByteIdxofPage>=pNandDrv->u16_PageByteCnt * pNandDrv->u8_PlaneCnt)) // mtd skip prepare main area, default all oxff
		{
			memset(u8MainBuf, 0xFF, pNandDrv->u16_PageByteCnt * pNandDrv->u8_PlaneCnt);
			memset(u8SpareBuf, 0xFF, pNandDrv->u16_SpareByteCnt * pNandDrv->u8_PlaneCnt);
		}

		memcpy(u8SpareBuf, buf, len);
		u32WriteLen += len;
		u16ByteIdxofPage += len;

		if( (u32WriteLen == (pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt) * pNandDrv->u8_PlaneCnt) ||
		(u32WriteLen ==  pNandDrv->u16_SpareByteCnt * pNandDrv->u8_PlaneCnt))
		{

			#if defined(FCIE_LFSR) && FCIE_LFSR
			if(pNandDrv->u8_RequireRandomizer == 1)
				NC_EnableLFSR();
			#endif

			#if DMA_MODE
			if(pNandDrv->u8_PlaneCnt > 1)
				NC_WritePages2P(u32CurRow, u8MainBuf, u8SpareBuf, 1);
			else
				NC_WritePages(u32CurRow, u8MainBuf, u8SpareBuf, 1);
			#else
			NC_WritePage_RIUMode(u32CurRow, u8MainBuf, u8SpareBuf);
			#endif
		}
	}

  return;
}

static void _titania_nand_read_buf(struct mtd_info *mtd, u_char* const buf, int len)
{
//	printf("_titania_nand_read_buf(): %08X, %d\n",buf, len );

	NAND_DEBUG("NANDDrv_READ_BUF()0x%X\n",len);

	NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();
	U8 *pu8MainBuf;
	U8 *pu8SpareBuf;
	U32 u32_Err = 0;

	u16ByteIdxofPage = len;

	if( len >= pNandDrv->u16_PageByteCnt * pNandDrv->u8_PlaneCnt)
	{
		if( len > pNandDrv->u16_PageByteCnt * pNandDrv->u8_PlaneCnt)
		{
			#if !defined(CONFIG_ARM)
			if( ((U32)buf) >= 0xC0000000 ) // For MIU1 (MIPS)
			{
				pu8MainBuf = u8MainBuf;
				pu8SpareBuf = u8SpareBuf;
			}
			else
			#endif
			{
				pu8MainBuf = buf;
				pu8SpareBuf = (U8*)buf + (pNandDrv->u16_PageByteCnt * pNandDrv->u8_PlaneCnt);
			}

			#if DMA_MODE

			#if defined(FCIE_LFSR) && FCIE_LFSR
			if(pNandDrv->u8_RequireRandomizer == 1)
				NC_EnableLFSR();
			#endif
			memset(pu8SpareBuf, 0xFF, pNandDrv->u16_SpareByteCnt * pNandDrv->u8_PlaneCnt);
			if(pNandDrv->u8_PlaneCnt > 1)
			{
				u32_Err = NC_ReadPages(u32CurRow, pu8MainBuf, pu8SpareBuf, 1);
				if(u32_Err == 0)
					u32_Err = NC_ReadPages(u32CurRow + pNandDrv->u16_BlkPageCnt,
								pu8MainBuf + pNandDrv->u16_PageByteCnt, pu8SpareBuf + pNandDrv->u16_SpareByteCnt, 1);
			}
			else
				u32_Err = NC_ReadPages(u32CurRow, pu8MainBuf, pu8SpareBuf, 1);
			#else
			for(sectoridx = 0; sectoridx < pNandDrv->u16_PageSectorCnt; sectoridx ++)
				u32_Err = NC_ReadSector_RIUMode(u32CurRow, sectoridx, pu8MainBuf + sectoridx*pNandDrv->u16_SectorByteCnt,
					pu8SpareBuf+ sectoridx*pNandDrv->u16_SectorSpareByteCnt);
			#endif
			NC_CheckECC((int*)(&s32_ECCStatus));
			if(u32_Err != UNFD_ST_SUCCESS)
				s32_ECCStatus = -1;

			if( buf != pu8MainBuf ) // If MIU1, copy data from temp buffer
			{
				memcpy(buf, u8MainBuf, pNandDrv->u16_PageByteCnt * pNandDrv->u8_PlaneCnt);
				memcpy((U8*)buf + (pNandDrv->u16_PageByteCnt * pNandDrv->u8_PlaneCnt), u8SpareBuf, pNandDrv->u16_SpareByteCnt * pNandDrv->u8_PlaneCnt);
			}
		}
		else
		{
			#if !defined(CONFIG_ARM)
			if( ((U32)buf) >= 0xC0000000 ) // For MIU1 (MIPS)
			{
				pu8MainBuf = u8MainBuf;
			}
			else
			#endif
			{
				pu8MainBuf = buf;
			}
			pu8SpareBuf = u8SpareBuf; // Preserve spare data in temp buffer for next read_buf()

			#if DMA_MODE

			#if defined(FCIE_LFSR) && FCIE_LFSR
			if(pNandDrv->u8_RequireRandomizer == 1)
				NC_EnableLFSR();
			#endif

			memset(pu8SpareBuf, 0xFF, pNandDrv->u16_SpareByteCnt * pNandDrv->u8_PlaneCnt);
			if(pNandDrv->u8_PlaneCnt > 1)
			{
				u32_Err = NC_ReadPages(u32CurRow, pu8MainBuf, pu8SpareBuf, 1);
				if(u32_Err == 0)
					u32_Err = NC_ReadPages(u32CurRow + pNandDrv->u16_BlkPageCnt,
								pu8MainBuf + pNandDrv->u16_PageByteCnt, pu8SpareBuf + pNandDrv->u16_SpareByteCnt, 1);
			}
			else
			u32_Err = NC_ReadPages(u32CurRow, pu8MainBuf, pu8SpareBuf, 1);
			#else
			for(sectoridx = 0; sectoridx < pNandDrv->u16_PageSectorCnt; sectoridx ++)
				u32_Err = NC_ReadSector_RIUMode(u32CurRow, sectoridx, pu8MainBuf + sectoridx*pNandDrv->u16_SectorByteCnt,
					pu8SpareBuf+ sectoridx*pNandDrv->u16_SectorSpareByteCnt );
			#endif
			NC_CheckECC((int *)(&s32_ECCStatus));
			if(u32_Err != UNFD_ST_SUCCESS)
				s32_ECCStatus = -1;

			if( buf != pu8MainBuf ) // If MIU1, copy data from temp buffer
				 memcpy(buf, u8MainBuf, pNandDrv->u16_PageByteCnt);
		}
	}
	else
	{
		memcpy(buf, u8SpareBuf, len);
	}

	return;
}

static u16 _titania_nand_read_word(struct mtd_info *mtd)
{
	NAND_DEBUG("NANDDrv_READ_WORD()\n");
	return 0;
}

static u_char _titania_nand_read_byte(struct mtd_info *mtd)
{
	U8 u8Ret = 0;
	#if defined(NC_SEL_FCIE3) && NC_SEL_FCIE3
	
	#if defined(FCIE_LFSR) && FCIE_LFSR
	NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();
	if(pNandDrv->u8_RequireRandomizer)
	{
		if(pNandDrv->u16_Reg48_Spare & BIT_NC_SPARE_DEST_MIU)
			u8Ret = u8SpareBuf[u32CIFDIdx];
		else
			NC_GetCIFD(&u8Ret, u32CIFDIdx, 1);

		u32CIFDIdx ++;
	}
	else
	{
	#endif
		NC_GetCIFD(&u8Ret, u32CIFDIdx, 1);
		u32CIFDIdx ++;
	#if defined(FCIE_LFSR) && FCIE_LFSR
	}
	#endif

	#elif defined(NC_SEL_FCIE5) && NC_SEL_FCIE5	//only spare dma
	u8Ret = u8SpareBuf[u32CIFDIdx];	
	u32CIFDIdx ++;
	#endif
	NAND_DEBUG("NANDDrv_READ_BYTE()=0x%X\n",u8Ret);

	return (u8Ret);
}

/**
 * nand_wait - [DEFAULT]  wait until the command is done
 * @mtd:  MTD device structure
 * @this: NAND chip structure
 * @state:  state to select the max. timeout value
 *
 * Wait for command done. This applies to erase and program only
 * Erase can take up to 400ms and program up to 20ms according to
 * general NAND and SmartMedia specs
 *
 */
static int _titania_nand_wait(struct mtd_info *mtd, struct nand_chip *this)
{
	NAND_DEBUG("NANDDrv_WAIT()\n");

	return REG(NC_ST_READ);
}

static void _titania_nand_cmdfunc(struct mtd_info *mtd, unsigned command, int column, int page_addr)
{
	NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();
	struct nand_chip *chip =(struct nand_chip*)(mtd->priv);
	int LBA, LPA;

	if(pNandDrv->u8_PlaneCnt > 1)
	{
		LBA = page_addr >> (chip->phys_erase_shift - chip->page_shift);
		LPA = page_addr & ((1<<(chip->phys_erase_shift - chip->page_shift))-1);
		page_addr = ((LBA<<1)<<pNandDrv->u8_BlkPageCntBits)+LPA;
	}


	switch (command) {
		case NAND_CMD_READ0:
			NAND_DEBUG("_titania_nand_cmdfunc: NAND_CMD_READ0, page_addr: 0x%x, column: 0x%x.\n", page_addr, (column>>1));
			u32CurRow = page_addr;
			u32CurCol = column;
			break;

		case NAND_CMD_READ1:
			NAND_DEBUG("_titania_nand_cmdfunc: NAND_CMD_READ1.\n");

			NAND_DEBUG("\033[31mUNFD not support READ1(CMD 0x01) now!!!\033[m\n");
			break;

		case NAND_CMD_READOOB:
			NAND_DEBUG("_titania_nand_cmdfunc: NAND_CMD_READOOB.\n");

			NAND_DEBUG("\033[34mReadOOB (CMD 0x50)\033[m\n");
			u32CIFDIdx = 0;
			#if defined(FCIE_LFSR) && FCIE_LFSR
			if(pNandDrv->u8_RequireRandomizer)
			{
				NC_EnableLFSR();
				NC_ReadPages(page_addr, u8MainBuf, u8SpareBuf, 1);
			}
			else
			#endif
			{
				u16ByteIdxofPage = 0;
				NC_Read_RandomIn(page_addr, column + pNandDrv->u16_PageByteCnt, u8SpareBuf,
					(pNandDrv->u16_SpareByteCnt >= 512)? 510 : pNandDrv->u16_SpareByteCnt);
				if(pNandDrv->u8_PlaneCnt > 1)
				{
					NC_Read_RandomIn(page_addr + pNandDrv->u16_BlkPageCnt, column + pNandDrv->u16_PageByteCnt, u8SpareBuf + pNandDrv->u16_SpareByteCnt,
						(pNandDrv->u16_SpareByteCnt >= 512)? 510 : pNandDrv->u16_SpareByteCnt);
					if(u8SpareBuf[0] != 0xFF || u8SpareBuf[pNandDrv->u16_SpareByteCnt] != 0xFF)
						u8SpareBuf[0] = u8SpareBuf[pNandDrv->u16_SpareByteCnt] = 0;
				}
			}
		break;

		case NAND_CMD_READID:
			NAND_DEBUG("_titania_nand_cmdfunc: NAND_CMD_READID.\n");

			u32CIFDIdx = 0;
			NC_ReadID();
			memcpy(u8SpareBuf, pNandDrv->au8_ID, NAND_ID_BYTE_CNT);
			break;

		case NAND_CMD_PAGEPROG:
			/* sent as a multicommand in NAND_CMD_SEQIN */
			NAND_DEBUG("_titania_nand_cmdfunc: NAND_CMD_PAGEPROG.\n");

			// We have done page program in write_buf()
			break;

		case NAND_CMD_ERASE1:
			NAND_DEBUG("_titania_nand_cmdfunc: NAND_CMD_ERASE1,  page_addr: 0x%x, column: 0x%x.\n", page_addr, column);
			if(pNandDrv->u8_PlaneCnt > 1)
				NC_EraseBlk2P(page_addr);
			else
				NC_EraseBlk(page_addr);

			break;

		case NAND_CMD_ERASE2:
			NAND_DEBUG("_titania_nand_cmdfunc: NAND_CMD_ERASE2.\n");
			// We do all erase function in Erase1 command.

			break;

		case NAND_CMD_SEQIN:
			/* send PAGE_PROG command(0x1080) */
			NAND_DEBUG("_titania_nand_cmdfunc: NAND_CMD_SEQIN/PAGE_PROG,  page_addr: 0x%x, column: 0x%x.\n", page_addr, column);

			u32CurRow = page_addr;
			u32CurCol = column;
			u16ByteIdxofPage = column;
			u32WriteLen = 0;
			break;

		case NAND_CMD_STATUS:
			NAND_DEBUG("_titania_nand_cmdfunc: NAND_CMD_STATUS.\n");

			u32CIFDIdx = 0;
			NC_ReadStatus();

			break;

		case NAND_CMD_RESET:
			NAND_DEBUG("_titania_nand_cmdfunc: NAND_CMD_RESET.\n");

			NC_ResetNandFlash();

			break;

		case NAND_CMD_STATUS_MULTI:
			NAND_DEBUG("_titania_nand_cmdfunc: NAND_CMD_STATUS_MULTI.\n");

			u32CIFDIdx = 0;
			NC_ReadStatus();
			break;

		case NAND_CMD_READSTART:
			NAND_DEBUG("_titania_nand_cmdfunc: NAND_CMD_READSTART.\n");

			// We have done this command in NC_ReadPages()
			break;

		case NAND_CMD_CACHEDPROG:
			NAND_DEBUG("_titania_nand_cmdfunc: NAND_CMD_CACHEDPROG.\n");

			NAND_DEBUG("\033[31mUNFD not support CACHEPROG (CMD 0x15) now!!!\033[m\n");
			break;

		default:
			NAND_DEBUG("_titania_nand_cmdfunc: error, unsupported command.\n");
			break;
	}

	return;
}

static void _titania_nand_enable_hwecc(struct mtd_info *mtd, int mode)
{
	NAND_DEBUG("enable_hwecc\r\n");
	// default enable
}

static int _titania_nand_calculate_ecc(struct mtd_info *mtd, const u_char *dat, u_char *ecc_code)
{
	NAND_DEBUG("calculate_ecc\r\n");

	// NFIE/FCIE2/FCIE3 will calculate it.

	return 0;
}

static int _titania_nand_correct_data(struct mtd_info *mtd, u_char *dat, u_char *read_ecc, u_char *calc_ecc)
{
	int s32ECCStatus = 0;
	//NC_CheckECC(&s32ECCStatus);
	s32ECCStatus = s32_ECCStatus;
	return s32ECCStatus;
}
U32 drvNAND_Init(void)
{
	U32 u32_Err = 0;
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();

	memset(pNandDrv, 0, sizeof(NAND_DRIVER));

	NC_PlatformInit();

	pNandDrv->pPartInfo = drvNAND_get_DrvContext_PartInfo();
	memset(pNandDrv->pPartInfo, 0, NAND_PARTITAION_BYTE_CNT);

	u32_Err = drvNAND_ProbeReadSeq();
	if(u32_Err != UNFD_ST_SUCCESS)
	{
		return u32_Err;
	}
	u32_Err = drvNAND_SearchCIS();

	#if defined(ENABLE_READ_DISTURBANCE_SUPPORT) && ENABLE_READ_DISTURBANCE_SUPPORT
	if(u32_Err == UNFD_ST_SUCCESS)
	{
		nand_ReadDisturbance();
	}
	#endif

	return u32_Err;
}


int nand_unfd_init(void)
{
	NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();
	U32 u32_Err;
	u32_Err = drvNAND_Init();

	if(UNFD_ST_ERR_NO_CIS == u32_Err)
	{
		printf("NAND: No CIS\n");

		#if defined(FCIE4_DDR) && FCIE4_DDR || defined(DDR_NAND_SUPPORT) && DDR_NAND_SUPPORT
		if(pNandDrv->u16_Reg58_DDRCtrl & BIT_DDR_MASM)
		{
			printf("NAND Error: Detect DDR NAND but have no CIS in NAND\n");
			printf("Please use command, \"ncisbl\", to write cis\n");
			return -1;
		}
		#endif
		{
			NC_PlatformInit();
			NC_ReConfig();
			
			#if defined(ENABLE_NAND_INTERRUPT_MODE) && ENABLE_NAND_INTERRUPT_MODE
			nand_enable_intr_mode();
            #endif

			NC_ResetNandFlash(); // Reset NAND flash
			nand_debug(UNFD_DEBUG_LEVEL_HIGH,1, "NC_ResetNandFlash done\n");

			NC_ReadID();
			nand_debug(UNFD_DEBUG_LEVEL_HIGH,1, "NC_ReadID done\n");

			if( drvNAND_CHECK_FLASH_TYPE() != 0)
			{
				printf("[%s]\tUnsupported NAND Type, Need to update CIS or modify code\n",__func__);
				return -1;
			}

			nand_debug(UNFD_DEBUG_LEVEL_HIGH,1,"drvNAND_CHECK_FLASH_TYPE done\n");

			NC_ConfigNandFlashContext();
			NC_Init();
		}
	}
	else if(UNFD_ST_SUCCESS != u32_Err)
	{
		printf("[%s]\tdrvNAND_Init Error : %lX", __func__, u32_Err);
		return -1;
	}
	
	/*Config clock timing either for DDR NAND or SDR NAND */
	nand_config_clock(pNandDrv->u16_tRC);

	if(u32_Err == UNFD_ST_SUCCESS)
	{
		if(nand_ReadDisturbance_BigImgRestore(NULL) != UNFD_ST_SUCCESS)
		{
			printf("[%s] NAND fatal Error, restore data fail\n", __func__);
		}
	}
	return 0;
}

/*
 * Board-specific NAND initialization.
 * - hwcontrol: hardwarespecific function for accesing control-lines
 * - dev_ready: hardwarespecific function for  accesing device ready/busy line
 * - eccmode: mode of ecc, see defines
 */

int board_nand_init(struct nand_chip *nand)
{
	U16 u16_tmp, u16_oob_poi, u16_i, u16_SectorSpareByteCnt;
	NAND_DEBUG("NANDDrv_BOARD_NAND_INIT().\n");

    #if DMA_MODE
	//printf("DMA MODE\n");
    #else
	printf("RIU MODE !!!!!!\n");
    #endif

	NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();


	if( nand_unfd_init() != 0 ) return -1;

	#if defined(NC_SEL_FCIE3) && NC_SEL_FCIE3
	// Set flag to inform the kernel that only NAND driver is enabled
	REG_CLR_BITS_UINT16(NC_REG_16h, BIT_KERN_CHK_NAND_EMMC_MSK);
	REG_SET_BITS_UINT16(NC_REG_16h, BIT_KERN_NAND);
	#elif defined(NC_SEL_FCIE5) && NC_SEL_FCIE5
	//Set flag to inform the kernel that only NAND driver is enabled ????? how
	#endif

	/* please refer to include/linux/nand.h for more info. */
	nand->dev_ready = _titania_nand_device_ready;
	nand->cmd_ctrl = _titania_nand_hwcontrol;
	nand->ecc.mode  = NAND_ECC_HW;

	nand->ecc.size                      = pNandDrv->u16_PageByteCnt * pNandDrv->u8_PlaneCnt;
	nand->ecc.bytes                     = pNandDrv->u16_ECCCodeByteCnt * pNandDrv->u16_PageSectorCnt * pNandDrv->u8_PlaneCnt;
	nand->require_randomizer            = pNandDrv->u8_RequireRandomizer;
	nand->ecc_corretable_bit			= pNandDrv->u16_ECCCorretableBit;
	nand->ecc_bitflip_threshold			= pNandDrv->u16_BitflipThreshold;

	u16_SectorSpareByteCnt = (pNandDrv->u16_SpareByteCnt/pNandDrv->u16_PageSectorCnt);
	nand->ecc.sectors = pNandDrv->u16_PageSectorCnt * pNandDrv->u8_PlaneCnt;

	unfd_nand_oob_custom.eccbytes = pNandDrv->u8_PlaneCnt*(pNandDrv->u16_ECCCodeByteCnt * pNandDrv->u16_PageSectorCnt);
	for(u16_tmp=0 ; u16_tmp<pNandDrv->u8_PlaneCnt*pNandDrv->u16_PageSectorCnt ; u16_tmp++)
	{
		u16_oob_poi = ((u16_tmp+1)*u16_SectorSpareByteCnt)-pNandDrv->u16_ECCCodeByteCnt;
		for(u16_i=0 ; u16_i<pNandDrv->u16_ECCCodeByteCnt ; u16_i++)
		{
			unfd_nand_oob_custom.eccpos[(u16_tmp*pNandDrv->u16_ECCCodeByteCnt)+u16_i] = u16_oob_poi++;
		}

		if( u16_tmp == 0 || u16_tmp == pNandDrv->u16_PageSectorCnt)
		{
			unfd_nand_oob_custom.oobfree[u16_tmp].offset = u16_tmp*u16_SectorSpareByteCnt + 2;
			unfd_nand_oob_custom.oobfree[u16_tmp].length= u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt - 2;
		}
		else
		{
			unfd_nand_oob_custom.oobfree[u16_tmp].offset = u16_tmp*u16_SectorSpareByteCnt;
			unfd_nand_oob_custom.oobfree[u16_tmp].length= u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt;
		}
	}
	//dump_mem((unsigned char *) &unfd_nand_oob_custom, sizeof(unfd_nand_oob_custom));
	unfd_nand_oob_custom.oobavail = 0;
	for (u16_i = 0; u16_i < ARRAY_SIZE(unfd_nand_oob_custom.oobfree); u16_i++)
	{
		if(unfd_nand_oob_custom.oobfree[u16_i].length)
			unfd_nand_oob_custom.oobavail += unfd_nand_oob_custom.oobfree[u16_i].length;
	}


	nand->ecc.layout =  &unfd_nand_oob_custom;
	_titania_nand_bbt_descr.offs    = pNandDrv->u8_BadBlkMarker;

	nand->ecc.hwctl = _titania_nand_enable_hwecc;
	nand->ecc.correct = _titania_nand_correct_data;
	nand->ecc.calculate = _titania_nand_calculate_ecc;

	if( pNandDrv->u16_PageByteCnt > 512 )
		nand->options = NAND_USE_FLASH_BBT | NAND_NO_AUTOINCR;
	else
		nand->options = NAND_USE_FLASH_BBT;

	nand->options = NAND_USE_FLASH_BBT;
	nand->waitfunc = _titania_nand_wait;
	nand->read_byte = _titania_nand_read_byte;
	nand->read_word = _titania_nand_read_word;
	nand->read_buf = _titania_nand_read_buf;
	nand->write_buf = _titania_nand_write_buf;
	nand->chip_delay = 20; //@FIXME: unite: us, please refer to nand_base.c 20us is default.
	nand->cmdfunc = _titania_nand_cmdfunc;
	nand->badblock_pattern = &_titania_nand_bbt_descr; //using default badblock pattern.
	nand->bbt_td = &_titania_bbt_main_descr;
	nand->bbt_md = &_titania_bbt_mirror_descr;

	if(unfd_nand_oob_custom.oobfree[0].length < (nand->bbt_td->len +1))
	{
		nand->bbt_td->offs = 0;
		nand->bbt_td->veroffs = 3;
		nand->bbt_md->offs = 0;
		nand->bbt_md->veroffs = 3;
	}

	if(pNandDrv->u16_BBtPageCheckCount != 0 && pNandDrv->u16_BBtPageCheckCount <= NAND_BBT_PAGE_COUNT)	//using specific bbt checking
	{
		_titania_nand_bbt_descr.BBtMarkerPageCount = pNandDrv->u16_BBtPageCheckCount;
		_titania_nand_bbt_descr.options |= NAND_BBT_SCANASSIGNEDPAGES;
		for(u16_i = 0; u16_i < pNandDrv->u16_BBtPageCheckCount; u16_i ++)
		{
			_titania_nand_bbt_descr.BBtMarkerPage[u16_i] = pNandDrv->u16_BBtPageIdx[u16_i];
			_titania_nand_bbt_descr.BBtMarkerOffs[u16_i] = pNandDrv->u16_BBtMarker[u16_i];
		}
	}
	return 0;

}

U32 drvNAND_WriteCIS_for_ROM(NAND_FLASH_INFO_t * pNandInfo)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	PARTITION_INFO_t *pPartInfo = drvNAND_get_DrvContext_PartInfo();
	U8 *au8_PageBuf = (U8*)pNandDrv->PlatCtx_t.pu8_PageDataBuf;
	U8 *au8_SpareBuf = (U8*)pNandDrv->PlatCtx_t.pu8_PageSpareBuf;
	BLK_INFO_t *pBlkInfo = (BLK_INFO_t*)au8_SpareBuf;
	U32 u32_Err = UNFD_ST_SUCCESS;
	U16 u16_PBA;
	U32 u32_PageIdx;
	U8 u8_CISIdx;

	NC_ConfigNandFlashContext();
	NC_RegInit();
	NC_Config();
	nand_config_clock(pNandInfo->u16_tRC);

	#if defined(FCIE4_DDR) && FCIE4_DDR || defined(DDR_NAND_SUPPORT) && DDR_NAND_SUPPORT
	memcpy((void *) &pNandInfo->tDefaultDDR, (const void *) &pNandDrv->tDefaultDDR, sizeof(DDR_TIMING_GROUP_t));
	memcpy((void *) &pNandInfo->tMaxDDR, (const void *) &pNandDrv->tMaxDDR, sizeof(DDR_TIMING_GROUP_t));
	memcpy((void *) &pNandInfo->tMinDDR, (const void *) &pNandDrv->tMinDDR, sizeof(DDR_TIMING_GROUP_t));
	#endif

	u8_CISIdx = 0;
	REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) ) = 0x0000;

    /* Search for two good blocks within the first 10 physical blocks */
	for (u16_PBA = 0; u16_PBA < 10; u16_PBA++) {

		/* Reeset NAND driver and FCIE to the original settings */
		pNandDrv->u16_SpareByteCnt = pNandInfo->u16_SpareByteCnt;
		pNandDrv->u16_PageByteCnt  = pNandInfo->u16_PageByteCnt;
		pNandDrv->u16_ECCType      = pNandInfo->u16_ECCType;
		NC_ConfigNandFlashContext();
		NC_RegInit();
		pNandDrv->u16_Reg48_Spare &= ~BIT_NC_HW_AUTO_RANDOM_CMD_DISABLE;
		//Disable Randomizer for nni Read/Write
		#if defined(FCIE_LFSR) && FCIE_LFSR
		if(pNandDrv->u8_RequireRandomizer)
			NC_DisableLFSR();
		#endif
		NC_Config();

		u32_PageIdx = u16_PBA << pNandDrv->u8_BlkPageCntBits;

        /* Check block is good block */
		if(!drvNAND_IsGoodBlk(u16_PBA))
			continue;

		u32_Err = NC_EraseBlk(u16_PBA << pNandDrv->u8_BlkPageCntBits);
		if (u32_Err != UNFD_ST_SUCCESS) {
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "Erase blk 0x%04x failed: 0x%08lx\n",
				u16_PBA, u32_Err);

			drvNAND_MarkBadBlk(u16_PBA);
			continue;
		}

		pNandDrv->u16_PageByteCnt = 2048;
		pNandDrv->u16_SpareByteCnt = 256;
		pNandDrv->u16_ECCType = NANDINFO_ECC_TYPE;

		NC_ConfigNandFlashContext();
		NC_RegInit();
		pNandDrv->u16_Reg48_Spare |= BIT_NC_HW_AUTO_RANDOM_CMD_DISABLE;
		NC_Config();

		memset(au8_PageBuf, '\0', pNandDrv->u16_PageByteCnt);
		memcpy(au8_PageBuf, pNandInfo, 512);
		memset(au8_SpareBuf, 0xFF, pNandDrv->u16_SpareByteCnt);

		pBlkInfo->u8_BadBlkMark = 0xFF;
		pBlkInfo->u8_PartType = 0;

		u32_Err = NC_WriteSectors(u32_PageIdx, 0, au8_PageBuf, au8_SpareBuf, 1);

		if (u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "write nni failed: 0x%08lx\n", u32_Err);
			drvNAND_MarkBadBlk(u16_PBA);
			continue;
		}

		/* Reset NAND driver and FCIE to the original settings */
		pNandDrv->u16_SpareByteCnt = pNandInfo->u16_SpareByteCnt;
		pNandDrv->u16_PageByteCnt  = pNandInfo->u16_PageByteCnt;
		pNandDrv->u16_ECCType      = pNandInfo->u16_ECCType;
		NC_ConfigNandFlashContext();
		NC_RegInit();

		pNandDrv->u16_Reg48_Spare &= ~BIT_NC_HW_AUTO_RANDOM_CMD_DISABLE;
		NC_Config();

		/*
		**	Write Partition Info the 2nd page
		**/
		if(pNandDrv->u8_HasPNI == 1)
		{
			memset(au8_PageBuf, '\0', pNandDrv->u16_PageByteCnt);
			memcpy(au8_PageBuf, pPartInfo, 512);

			u32_Err = NC_WriteSectors(u32_PageIdx+ga_tPairedPageMap[1].u16_LSB, 0, au8_PageBuf, au8_SpareBuf, 1);
			if (u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "Write Part Info failed with EC: 0x%08lx\n", u32_Err);
				drvNAND_MarkBadBlk(u16_PBA);
				continue;
			}
		}

		/*
		**  Write Paired Page Map to the 4th page
		**/
		if(pNandDrv->u8_CellType == 1)  // MLC
		{
			memset(au8_PageBuf, '\0', pNandDrv->u16_PageByteCnt);
			memcpy(au8_PageBuf, &ga_tPairedPageMap, 2048);
			u32_Err = NC_WritePages(u32_PageIdx+pNandInfo->u8_PairPageMapLoc, au8_PageBuf, au8_SpareBuf, 1);
			if (u32_Err != UNFD_ST_SUCCESS) {
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "Write Paired-Page Map failed with EC: 0x%08lx\n", u32_Err);
				drvNAND_MarkBadBlk(u16_PBA);
				continue;
			}
		}

		/*
		if(pNandDrv->u8_RequireReadRetry && pNandDrv->u8_ReadRetryLoc != 0)  // MLC
		{
			memset(au8_PageBuf, '\0', pNandDrv->u16_PageByteCnt);
			memcpy(au8_PageBuf, &gau8_ReadRetryTable, 512);
			u32_Err = NC_WritePages(u32_PageIdx+pNandInfo->u8_ReadRetryLoc, au8_PageBuf, au8_SpareBuf, 1);
			if (u32_Err != UNFD_ST_SUCCESS) {
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "Write Customize Read-Retry Table failed with EC: 0x%08lx\n", u32_Err);
				drvNAND_MarkBadBlk(u16_PBA);
				continue;
			}
		}
		*/

		printf("CIS%d is written to blk 0x%04x\n", u8_CISIdx, u16_PBA);

		pNandDrv->u16_CISPBA[u8_CISIdx] = u16_PBA;

		if ((++u8_CISIdx) == 2)
			break;
	}

	/* Reset NAND driver and FCIE to the original settings */
	pNandDrv->u16_SpareByteCnt = pNandInfo->u16_SpareByteCnt;
	pNandDrv->u16_PageByteCnt  = pNandInfo->u16_PageByteCnt;
	pNandDrv->u16_ECCType      = pNandInfo->u16_ECCType;
	NC_ConfigNandFlashContext();
	NC_RegInit();
	pNandDrv->u16_Reg48_Spare &= ~(1 << 12);
	NC_Config();

	switch (u8_CISIdx) {
		case 0:
			REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) )  = 0x0002;
			u32_Err = UNFD_ST_ERR_NO_BLK_FOR_CIS0;
			break;
		case 1:
			REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) )  = 0x0003;
			u32_Err = UNFD_ST_ERR_NO_BLK_FOR_CIS1;
			break;
		case 2:
			u32_Err = UNFD_ST_SUCCESS;
			break;
	}

    return u32_Err;
}


int search_cis_in_DRAM(U8* pu8_CISAddr, U8* pu8_PPMAddr, U8* pu8_PNIAddr, NAND_FLASH_INFO_t *pNandInfoOut)
{
	NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();
	NAND_FLASH_INFO_t * pNandInfo;
	PARTITION_INFO_t * pPartInfo;
	U32 u32_i, u32_j, u32_Err, u32_ChkSum;
	U8 u8_IsEnd = 0;

	REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) )  = 0x0000;

	NC_PlatformInit();

	u32_Err = NC_ResetNandFlash();
	if(u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1,"NAND Reset Fail\n");
		REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) )  = 0x0002;
		return -1;
	}

	u32_Err = NC_ReadID();
	if(u32_Err!= UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "Read ID Fail\n");
		REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) )  = 0x0003;
		return -1;
	}
	printf("Begin Search CIS in DRAM\n");

	//Search 20 pieces of possiable cis memory
	//for(u32_i = 0; u32_i < 0x200 * 20; u32_i += 0x200)
	u32_i = 0;
	while(1)
	{
		pNandInfo = (NAND_FLASH_INFO_t*)(pu8_CISAddr + u32_i);

		for(u32_j=0; u32_j<pNandInfo->u8_IDByteCnt; u32_j++)
		{
			if(pNandInfo->au8_ID[u32_j] != pNandDrv->au8_ID[u32_j])
				break;
		}
		if(u32_j == pNandInfo->u8_IDByteCnt)
			break;

		// used to check the end of nni in DRAM
		u32_ChkSum = drvNAND_CheckSum(((void*)pNandInfo) + 0x24, 0x32 - 0x24);
		if (drvNAND_CompareCISTag(pNandInfo->au8_Tag) ||(u32_ChkSum != pNandInfo->u32_ChkSum))
		{
			u8_IsEnd = 1;
			break;
		}
		u32_i += 0x200;
	}
	if(u8_IsEnd)
	{
		printf("No available CIS match with current nand flash\n");
		REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) )  = 0x0004;
		return -1;
	}
	
	printf("NAND ID:");
	for(u32_j=0; u32_j<pNandInfo->u8_IDByteCnt; u32_j++)
	{
		printf("0x%X ", pNandDrv->au8_ID[u32_j]);
	}
	printf("\nFound CIS in given memory\n");
	drvNAND_ParseNandInfo(pNandInfo);
	//dump_nand_info(pNandInfo);

	NC_ConfigNandFlashContext();
	/*Re-Search DDR timing again*/
	u32_Err = NC_Init();
	if(u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1,"NC_Init Fail ErrCode: %lX\n", u32_Err);
		REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) )  = 0x0005;
		return -1;
	}
	NC_Config();

	nand_config_clock(pNandInfo->u16_tRC);

	//search pni
	pNandDrv->u8_HasPNI = 0;
	if(pu8_PNIAddr != NULL)
	{
		for(u32_i = 0; u32_i < NAND_PARTITAION_BYTE_CNT * 20 ; u32_i += NAND_PARTITAION_BYTE_CNT)
		{
			pPartInfo = (PARTITION_INFO_t*) (pu8_PNIAddr + u32_i);

			if(pPartInfo->u16_SpareByteCnt == pNandDrv->u16_SpareByteCnt &&
				pPartInfo->u16_PageByteCnt == pNandDrv->u16_PageByteCnt &&
				pPartInfo->u16_BlkPageCnt == pNandDrv->u16_BlkPageCnt &&
				pPartInfo->u16_BlkCnt == pNandDrv->u16_BlkCnt) // Match Partition layout
			{
				memcpy(pNandDrv->pPartInfo, pPartInfo, NAND_PARTITAION_BYTE_CNT);
				dump_part_info(pNandDrv->pPartInfo);
				pNandDrv->u8_HasPNI = 1;
				break;
			}
		}
	}
	
	//memcpy pair page map
	printf("Cell Type %d, Randomizer %d\n", pNandDrv->u8_CellType, pNandDrv->u8_RequireRandomizer);
	if(pNandDrv->u8_CellType)
		memcpy(&ga_tPairedPageMap, pu8_PPMAddr + (pNandInfo->u8_PairPageMapType * 0x800), 0x800);
	else
	{
		for(u32_i = 0; u32_i < 0x200; u32_i++)
		{
			ga_tPairedPageMap[u32_i].u16_LSB = u32_i;
			ga_tPairedPageMap[u32_i].u16_MSB = u32_i;
		}
	}
	printf("Require Read Retry %d\n", pNandDrv->u8_RequireReadRetry);

	memcpy(pNandInfoOut, pNandInfo, 0x200);

	return 0;
}

int nand_write_block_slcmode(U32 u32_BlkRow, U8* p_buffer, U32 u32_PageCnt, U32 (*nand_markbad)(U32))
{
	NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();

	int i, j, BlkPageCnt;
	U32 u32_TmpRow, u32_Err;
	U8 *pu8_buffer = p_buffer;
	U8 *pu8_PageDataBuf = pNandDrv->PlatCtx_t.pu8_PageDataBuf;
	BlkPageCnt = pNandDrv->u16_BlkPageCnt >> 1;

	memset(pu8_PageDataBuf, 0x5a5a, pNandDrv->u16_PageByteCnt);

	for(i = 0; i < u32_PageCnt; i ++)
	{
		u32_TmpRow = u32_BlkRow + ga_tPairedPageMap[i].u16_LSB;
		u32_Err = drvNAND_LFSRWritePhyPage(u32_TmpRow, pu8_buffer, NULL);
		if(u32_Err)
		{
			printf ("NAND write to offset %lx failed %ld\n",
				u32_TmpRow, u32_Err);
			printf("Mark current block as bad block\n");
			//mark bad
			if(nand_markbad == NULL)
				drvNAND_MarkBadBlk(u32_BlkRow >> pNandDrv->u8_BlkPageCntBits);
			else
				nand_markbad(u32_BlkRow >> pNandDrv->u8_BlkPageCntBits);

			pu8_buffer -= pNandDrv->u16_PageByteCnt * i;
			u32_BlkRow += pNandDrv->u16_BlkPageCnt;

			return -1;
		}
		pu8_buffer += pNandDrv->u16_PageByteCnt;

		//Write Dummy data to MSB Page of MLC NAND
		if(i != BlkPageCnt - 1)
		{
			if(ga_tPairedPageMap[i].u16_LSB != (ga_tPairedPageMap[i + 1].u16_LSB - 1))
			{
				for(j = ga_tPairedPageMap[i].u16_LSB + 1; j < ga_tPairedPageMap[i + 1].u16_LSB; j ++)
				{
					u32_Err = drvNAND_LFSRWritePhyPage(u32_BlkRow + j, pu8_PageDataBuf, NULL);
					if(u32_Err)
					{
						printf ("NAND write to offset %lx failed %ld\n",
							u32_BlkRow + j, u32_Err);
						printf("Mark current block as bad block\n");
						//mark bad
						if(nand_markbad == NULL)
							drvNAND_MarkBadBlk(u32_BlkRow >> pNandDrv->u8_BlkPageCntBits);
						else
							nand_markbad(u32_BlkRow >> pNandDrv->u8_BlkPageCntBits);

						pu8_buffer -= pNandDrv->u16_PageByteCnt * i;
						u32_BlkRow += pNandDrv->u16_BlkPageCnt;

						return -1;
					}
				}
			}
		}
		else{
			for(j = ga_tPairedPageMap[i].u16_LSB + 1; j < pNandDrv->u16_BlkPageCnt; j ++)
			{
				u32_Err = drvNAND_LFSRWritePhyPage(u32_BlkRow + j, pu8_PageDataBuf, NULL);
				if(u32_Err)
				{
					printf ("NAND write to offset %lx failed %ld\n",
						u32_BlkRow + j, u32_Err);
					printf("Mark current block as bad block\n");
					//mark bad
					if(nand_markbad == NULL)
						drvNAND_MarkBadBlk(u32_BlkRow >> pNandDrv->u8_BlkPageCntBits);
					else
						nand_markbad(u32_BlkRow >> pNandDrv->u8_BlkPageCntBits);

					pu8_buffer -= pNandDrv->u16_PageByteCnt * i;
					u32_BlkRow += pNandDrv->u16_BlkPageCnt;

					return -1;
				}
			}
		}
	}
	return 0;
}

int nand_write_bootloader(U32 u32_Row,U8 * pu8_addr, U32 u32_size, U8 u8_BootStageId)
{
	NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();

	U8 * pu8_DataBuf = pu8_addr;
	U16 u16_BlkPageCnt;
	U32 u32_pagecnt, u32_Err, u32_size_tmp = u32_size, u32_Row_Read = u32_Row;
	U8 u8_IdWritten = 0;
	u16_BlkPageCnt = (pNandDrv->u8_CellType) ? pNandDrv->u16_BlkPageCnt/2: pNandDrv->u16_BlkPageCnt;

	memset(u8SpareBuf, 0xFF, pNandDrv->u16_SpareByteCnt);

	u32_pagecnt = u32_size >> pNandDrv->u8_PageByteCntBits;
	//add register status for polling by TV Tool
	REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) )  = 0x0000;

	#if defined(FCIE_LFSR) && FCIE_LFSR
	if(pNandDrv->u8_RequireRandomizer)
		NC_DisableLFSR();
	#endif
	while(u32_pagecnt >= u16_BlkPageCnt)
	{
		while (drvNAND_IsGoodBlk(u32_Row >> pNandDrv->u8_BlkPageCntBits) == 0)
		{
			u32_Row += pNandDrv->u16_BlkPageCnt;
			//bad block jump to next block
			if(u32_Row == (pNandDrv->u16_BlkCnt << pNandDrv->u8_BlkPageCntBits))
			{
				printf("Error : There is no available GOOD block in current nand device\n");
				REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) )  = 0x0004;
				return -1;
			}
		}
		u32_Err = NC_EraseBlk(u32_Row);
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			drvNAND_MarkBadBlk(u32_Row >> pNandDrv->u8_BlkPageCntBits);
			//jump to next block
			u32_Row += pNandDrv->u16_BlkPageCnt;
			continue;
		}

		if(u8_IdWritten == 0)
			u8SpareBuf[1] = u8_BootStageId;
		else
			u8SpareBuf[1] = 0xFF;

		if(pNandDrv->u8_CellType)
		{
			U16 u16_i, u16_flag = 0;
			U32 u32_TmpRow;
			for(u16_i =0; u16_i < u16_BlkPageCnt; u16_i ++)
			{
				u32_TmpRow = u32_Row + ga_tPairedPageMap[u16_i].u16_LSB;
				u32_Err = NC_WritePages(u32_TmpRow, pu8_DataBuf, u8SpareBuf, 1);
				if(u32_Err != UNFD_ST_SUCCESS)
				{
					drvNAND_MarkBadBlk(u32_Row >> pNandDrv->u8_BlkPageCntBits);
					//jump to next block
					u32_Row += pNandDrv->u16_BlkPageCnt;
					u16_flag = 1;
					break;
				}
				pu8_DataBuf += pNandDrv->u16_PageByteCnt;
			}
			if(u16_flag == 1)
			{
				pu8_DataBuf -= pNandDrv->u16_PageByteCnt * u16_i;
				continue;
			}
		}
		else
		{
			u32_Err = NC_WritePages(u32_Row, pu8_DataBuf, u8SpareBuf, pNandDrv->u16_BlkPageCnt);
			if(u32_Err != UNFD_ST_SUCCESS)
			{
				drvNAND_MarkBadBlk(u32_Row >> pNandDrv->u8_BlkPageCntBits);
				//jump to next block
				u32_Row += pNandDrv->u16_BlkPageCnt;
				continue;
			}
			pu8_DataBuf += (u16_BlkPageCnt << pNandDrv->u8_PageByteCntBits);
		}
		u8_IdWritten = 1;

		u32_pagecnt -= u16_BlkPageCnt;
		u32_size -= (u16_BlkPageCnt << pNandDrv->u8_PageByteCntBits);
		u32_Row += pNandDrv->u16_BlkPageCnt;
	}

	while(u32_size)
	{
		while (drvNAND_IsGoodBlk(u32_Row >> pNandDrv->u8_BlkPageCntBits) == 0)
		{
			u32_Row += pNandDrv->u16_BlkPageCnt;
			//bad block jump to next block
			if(u32_Row == (pNandDrv->u16_BlkCnt << pNandDrv->u8_BlkPageCntBits))
			{
				printf("Error : There is no available GOOD block in current nand device\n");
				REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) )  = 0x0004;
				return -1;
			}
		}

		u32_Err = NC_EraseBlk(u32_Row);
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			drvNAND_MarkBadBlk(u32_Row >> pNandDrv->u8_BlkPageCntBits);
			//jump to next block
			u32_Row += pNandDrv->u16_BlkPageCnt;
			continue;
		}

		if(u8_IdWritten == 0)
			u8SpareBuf[1] = u8_BootStageId;
		else
			u8SpareBuf[1] = 0xFF;

		u32_pagecnt = u32_size >> pNandDrv->u8_PageByteCntBits;
		if((u32_size & (pNandDrv->u16_PageByteCnt -1)))
			 u32_pagecnt += 1;

		if(pNandDrv->u8_CellType)
		{
			U16 u16_i, u16_flag = 0;
			U32 u32_TmpRow;
			for(u16_i =0; u16_i < u32_pagecnt; u16_i ++)
			{
				u32_TmpRow = u32_Row + ga_tPairedPageMap[u16_i].u16_LSB;
				u32_Err = NC_WritePages(u32_TmpRow, pu8_DataBuf, u8SpareBuf, 1);
				if(u32_Err != UNFD_ST_SUCCESS)
				{
					drvNAND_MarkBadBlk(u32_Row >> pNandDrv->u8_BlkPageCntBits);
					//jump to next block
					u32_Row += pNandDrv->u16_BlkPageCnt;
					u16_flag = 1;
					break;
				}
				pu8_DataBuf += pNandDrv->u16_PageByteCnt;
			}
			if(u16_flag == 1)
			{
				pu8_DataBuf -= pNandDrv->u16_PageByteCnt * u16_i;
				continue;
			}
		}
		else
		{
		    u32_Err = NC_WritePages(u32_Row, pu8_DataBuf, u8SpareBuf, u32_pagecnt);
		    if(u32_Err != UNFD_ST_SUCCESS)
		    {
			    drvNAND_MarkBadBlk(u32_Row >> pNandDrv->u8_BlkPageCntBits);
			    //jump to next block
			    u32_Row += pNandDrv->u16_BlkPageCnt;
			    continue;
		    }
		}
		u8_IdWritten = 1;

		u32_size-= u32_size;
	}
	//finish programming
	//Add register checking
	//read back check
	u32_size = u32_size_tmp;
	u32_pagecnt = u32_size >> pNandDrv->u8_PageByteCntBits;
	pu8_DataBuf = pu8_addr;
	u32_Row = u32_Row_Read;

	while(u32_pagecnt >= u16_BlkPageCnt)
	{
		while (drvNAND_IsGoodBlk(u32_Row >> pNandDrv->u8_BlkPageCntBits) == 0)
		{
			u32_Row += pNandDrv->u16_BlkPageCnt;
			//bad block jump to next block
			if(u32_Row == (pNandDrv->u16_BlkCnt << pNandDrv->u8_BlkPageCntBits))
			{
				printf("Error : There is no available GOOD block in current nand device\n");
				REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) )  = 0x0004;
				return -1;
			}
		}

		{
			U16 u16_i;
			U32 u32_TmpRow;
			for(u16_i =0; u16_i < u16_BlkPageCnt; u16_i ++)
			{
				u32_TmpRow = u32_Row + ga_tPairedPageMap[u16_i].u16_LSB;
				u32_Err = NC_ReadPages(u32_TmpRow, u8MainBuf, u8SpareBuf, 1);
				if(u32_Err != UNFD_ST_SUCCESS)
				{
					printf("Error: ECC fail when read back checking\n");
					REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) )  = 0x0002;
					return -1;
				}
				if(memcmp(u8MainBuf, pu8_DataBuf, pNandDrv->u16_PageByteCnt))
				{
					printf("Error: compare fail when read back checking\n");
					printf("RAM--->\n");
					dump_mem((unsigned char *) pu8_DataBuf, pNandDrv->u16_PageByteCnt);
					printf("NAND--->\n");
					dump_mem((unsigned char *) u8MainBuf, pNandDrv->u16_PageByteCnt);
					REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) )  = 0x0003;
					return -1;
				}
				pu8_DataBuf += pNandDrv->u16_PageByteCnt;
			}
		}

		u32_pagecnt -= u16_BlkPageCnt;
		u32_size -= (u16_BlkPageCnt << pNandDrv->u8_PageByteCntBits);
		u32_Row += pNandDrv->u16_BlkPageCnt;
	}

	while(u32_size)
	{
		while (drvNAND_IsGoodBlk(u32_Row >> pNandDrv->u8_BlkPageCntBits) == 0)
		{
			u32_Row += pNandDrv->u16_BlkPageCnt;
			//bad block jump to next block
			if(u32_Row == (pNandDrv->u16_BlkCnt << pNandDrv->u8_BlkPageCntBits))
			{
				printf("Error : There is no available GOOD block in current nand device\n");
				REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) )  = 0x0004;
				return -1;
			}
		}

		u32_pagecnt = u32_size >> pNandDrv->u8_PageByteCntBits;
		if((u32_size & (pNandDrv->u16_PageByteCnt -1)))
			 u32_pagecnt += 1;

		{
			U16 u16_i;
			U32 u32_TmpRow;
			for(u16_i =0; u16_i < u32_pagecnt; u16_i ++)
			{
				u32_TmpRow = u32_Row + ga_tPairedPageMap[u16_i].u16_LSB;
				u32_Err = NC_ReadPages(u32_TmpRow, u8MainBuf, u8SpareBuf, 1);
				if(u32_Err != UNFD_ST_SUCCESS)
				{
					printf("Error: ECC fail when read back checking\n");
					REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) )  = 0x0002;
					return -1;
				}
				if(memcmp(u8MainBuf, pu8_DataBuf, pNandDrv->u16_PageByteCnt))
				{
					printf("Error: compare fail when read back checking\n");
					printf("RAM--->\n");
					dump_mem((unsigned char *) pu8_DataBuf, pNandDrv->u16_PageByteCnt);
					printf("NAND--->\n");
					dump_mem((unsigned char *) u8MainBuf, pNandDrv->u16_PageByteCnt);
					REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) )  = 0x0003;
					return -1;
				}

				pu8_DataBuf += pNandDrv->u16_PageByteCnt;
			}
		}

		u32_size-= u32_size;
	}
	//Register status Ok
	REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) )  = 0x0001;
	return 0;
}

/*
 *For SLC, full block program is not necessary
 *Turn on this switch on MLC
 */
#if 0
#ifdef FULL_BLOCK_PROGRAM_SCRUB
static u32 empty_check(const void *buf, u32 len)
{
	int i;
	NAND_DRIVER * pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();

	//if ((!len) || (len & (meminfo->oobblock + meminfo->oobsize - 1)))
		//return -1;

	for (i = (len >> 2) - 1; i >= 0; i--)
		if (((const uint32_t *)buf)[i] != 0xFFFFFFFF)
			break;

	/* The resulting length must be aligned to the minimum flash I/O size */
	len = ALIGN((i + 1) << 2, pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt);
	return len;
}
#endif
#endif

int drvNAND_ReadCISBlk(U32 u32_off, U8* pu8_DataBuf)
{
	NAND_DRIVER * pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();
	U32 u32_Ret, i, pglen;
	U32 u32_Row = u32_off >> pNandDrv->u8_PageByteCntBits;
	U16 u16_BlkCntTmp, u16_BlkPageCntTmp, u16_PageByteCntTmp, u16_SpareByteCntTmp, u16_ECCTypeTmp;
	U32 page_off = pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt;

	//set 0xff for nni page
	memset((void*)pu8_DataBuf, 0xff, pNandDrv->u16_PageByteCnt);
	u16_BlkCntTmp = pNandDrv->u16_BlkCnt;
	u16_BlkPageCntTmp = pNandDrv->u16_BlkPageCnt;
	u16_PageByteCntTmp = pNandDrv->u16_PageByteCnt;
	u16_SpareByteCntTmp = pNandDrv->u16_SpareByteCnt;
	u16_ECCTypeTmp = pNandDrv->u16_ECCType;
	//reconfig nni read setting

	pNandDrv->u16_BlkCnt = 0x400;
	pNandDrv->u16_BlkPageCnt = 0x20;
	pNandDrv->u16_PageByteCnt = 0x800;
	pNandDrv->u16_SpareByteCnt = 0x100;
	pNandDrv->u16_ECCType = NANDINFO_ECC_TYPE;

	#if defined(FCIE_LFSR) && FCIE_LFSR
	if(pNandDrv->u8_RequireRandomizer)
		NC_DisableLFSR();
	#endif

	NC_ConfigNandFlashContext();
	NC_RegInit();
	pNandDrv->u16_Reg48_Spare |= (1 << 12);
	NC_Config();

	u32_Ret = NC_ReadSectors(u32_Row, 0, pu8_DataBuf, (U8*)((U32)pu8_DataBuf + pNandDrv->u16_SectorByteCnt), 1);
	if(u32_Ret != 0)
		return u32_Ret;

	//restore original setting
	pNandDrv->u16_BlkCnt = u16_BlkCntTmp;
	pNandDrv->u16_BlkPageCnt = u16_BlkPageCntTmp;
	pNandDrv->u16_PageByteCnt = u16_PageByteCntTmp;
	pNandDrv->u16_SpareByteCnt = u16_SpareByteCntTmp;
	pNandDrv->u16_ECCType = u16_ECCTypeTmp;
	pglen = pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt;

	NC_ConfigNandFlashContext();
	NC_RegInit();
	pNandDrv->u16_Reg48_Spare &= ~(1 << 12);
	NC_Config();

	for(i = 1 ; i < pNandDrv->u16_BlkPageCnt; i ++)
	{
		u32_Ret = NC_ReadPages(u32_Row + i, (U8*) ((U32)pu8_DataBuf + page_off * i),
							(U8*) ((U32)pu8_DataBuf + (page_off * i) + pNandDrv->u16_PageByteCnt), 1);
		if(u32_Ret)
			return u32_Ret;
			
		/*
		 *For SLC, full block program is not necessary
		 *Turn on this switch on MLC
		 */
		#if 0
		#ifdef FULL_BLOCK_PROGRAM_SCRUB
		{
			U32 chk_len;
			chk_len = empty_check((pu8_DataBuf + page_off * i), pglen);
			if (!chk_len)
			{
				(pu8_DataBuf + page_off * i)[0] = 0xfe; // indicate empty page
			}
		}
		#endif
		#endif
	}

	return UNFD_ST_SUCCESS;
}

void drvNAND_GetMtdParts(char *buf)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	PARTITION_INFO_t *pPartInfo = pNandDrv->pPartInfo;
	U8 u8_i,u8_PartNo, u8_Unknown = 0;
	int len, Maxlen = 512;
	u32 PartSize = 0, PartSize1 = 0, PartSize2 = 0;
	U32 u32_Err;
	u32 virtual_boot;
	U32 u32_BlkIdx;
	U8	u8_MbootCnt= 0;
	U32 u32_MbootBlkIdx[2];
	char *mtd_buf=buf, tmp[128], PartName[16];
	U16 u16_LastPartType;

	if(pNandDrv->u8_HasPNI == 0)
		goto cleanup;

	sprintf(mtd_buf, "mtdparts=edb64M-nand:");
	//printf("%s\r\n",buf);
	mtd_buf += 21;
	if (Maxlen < 21)
		goto cleanup;
	Maxlen -= 21;

	u16_LastPartType = 0;
	for(u8_i = 0; u8_i < pPartInfo->u16_PartCnt; u8_i ++)
	{
		if( (pPartInfo->records[u8_i].u16_PartType & UNFD_LOGI_PART) == UNFD_LOGI_PART)
			break;

		PartSize = 0;
		if( u8_i )
		{
			memcpy(mtd_buf, ",", 1);
			mtd_buf ++;
			Maxlen --;
		}

		PartSize = pNandDrv->u16_BlkPageCnt * pNandDrv->u16_PageByteCnt *
			(pPartInfo->records[u8_i].u16_BackupBlkCnt + pPartInfo->records[u8_i].u16_BlkCnt);

		u8_PartNo = u16_LastPartType != pPartInfo->records[u8_i].u16_PartType ? 0:1;

		u16_LastPartType = pPartInfo->records[u8_i].u16_PartType;

		switch(pPartInfo->records[u8_i].u16_PartType)
		{
			case UNFD_PART_BOOTLOGO:
				sprintf(PartName,"UBILD" );
				break;
			case UNFD_PART_UBOOT:
				sprintf(PartName,"MBOOT" );
				break;
			case UNFD_PART_OS:
				sprintf(PartName,"KL" );
				break;
			case UNFD_PART_SECINFO:
				sprintf(PartName,"KL_BP" );
				break;
			case UNFD_PART_OTP:
				sprintf(PartName,"NTP" );
				break;
			case UNFD_PART_RECOVERY:
				sprintf(PartName,"RECOVERY" );
				break;
			case UNFD_PART_MISC:
				sprintf(PartName,"MISC" );
				break;
			case UNFD_PART_TBL:
				sprintf(PartName,"TBL" );
				break;
			case UNFD_PART_CTRL:
				sprintf(PartName,"CTRL" );
				break;
			case UNFD_PART_UBIRO:
				sprintf(PartName,"UBIRO" );
				break;
			default:
				sprintf(PartName,"UNKNOWN%d", u8_Unknown++);
				break;
		}
		if (u8_i)
			sprintf(tmp, "%dk(%s)", PartSize/1024, PartName); //,pPartInfo->records[u8_i].u16_PartType);
		else
		{
			u8_MbootCnt = 0;
			if(pNandDrv->u8_BL1PBA != 0)
			{
				//search vid chunk header for mboot partition beginning
				u32_BlkIdx = 1;
				while(1)
				{
					u32_Err = NC_ReadPages((pNandDrv->u8_BL1PBA + u32_BlkIdx) << pNandDrv->u8_BlkPageCntBits, u8MainBuf, u8SpareBuf, 1);
					//binary ID for chunk header
					if( ((U32 *)u8MainBuf)[0x7] == 0x0000B007 && u32_Err == UNFD_ST_SUCCESS)
					{
						u32_MbootBlkIdx[u8_MbootCnt] = (pNandDrv->u8_BL1PBA + u32_BlkIdx);
						u8_MbootCnt ++;
					}
					if(u8_MbootCnt == 2)
						break;

					if((pNandDrv->u8_BL1PBA + u32_BlkIdx) == 0xFF)
						break;

					u32_BlkIdx ++;
				}
				if((pNandDrv->u8_BL1PBA + u32_BlkIdx) == 0xFF)
				{
					//only one mboot or upgrade power cut
					//goto cleanup;
					if(u8_MbootCnt == 1)		//one mboot ->powercut during upgrade->layout ubild
					{
						virtual_boot = u32_MbootBlkIdx[0] * (pNandDrv->u16_BlkPageCnt * pNandDrv->u16_PageByteCnt) / 1024;
						PartSize = PartSize - (u32_MbootBlkIdx[0] - 10) * (pNandDrv->u16_BlkPageCnt * pNandDrv->u16_PageByteCnt) ;
						sprintf(tmp, "%dk@%dk(%s)", PartSize/1024, virtual_boot, PartName);
						printf("Warning: Only One Mboot found, Please re-upgrade your mboot, in case of read ecc fail\n");
					}
					else	//no mboot  using default for ubild partition, impossible in normal case or tool programming case
						goto cleanup;
				}
				else
				{
					 if(u8_MbootCnt == 1)
					{
						virtual_boot = u32_MbootBlkIdx[0] * (pNandDrv->u16_BlkPageCnt * pNandDrv->u16_PageByteCnt) / 1024;
						PartSize = PartSize - (u32_MbootBlkIdx[0] - 10) * (pNandDrv->u16_BlkPageCnt * pNandDrv->u16_PageByteCnt) ;
						sprintf(tmp, "%dk@%dk(%s)", PartSize/1024, virtual_boot, PartName);
					}
					else if(u8_MbootCnt == 2)
					{
						virtual_boot = u32_MbootBlkIdx[0] * (pNandDrv->u16_BlkPageCnt * pNandDrv->u16_PageByteCnt) / 1024;
						PartSize1 = (u32_MbootBlkIdx[1] - u32_MbootBlkIdx[0]) * (pNandDrv->u16_BlkPageCnt * pNandDrv->u16_PageByteCnt) ;
						PartSize2 = PartSize - (u32_MbootBlkIdx[1] - 10) * (pNandDrv->u16_BlkPageCnt * pNandDrv->u16_PageByteCnt) ;
						sprintf(tmp, "%dk@%dk(%s),%dk(%sBAK)", PartSize1/1024, virtual_boot, PartName,PartSize2/1024, PartName);
					}
					else
						goto cleanup;

					//virtual_boot = (pNandDrv->u8_BL1PBA + u32_BlkIdx) * (pNandDrv->u16_BlkPageCnt * pNandDrv->u16_PageByteCnt) / 1024;
					//PartSize = PartSize - ((pNandDrv->u8_BL1PBA + u32_BlkIdx - 10) * (pNandDrv->u16_BlkPageCnt * pNandDrv->u16_PageByteCnt));
				}
			}
			else if(pNandDrv->u8_HashPBA[1][1] != 0)
			{
				u32_BlkIdx = 1;
				while(1)
				{
					u32_Err = NC_ReadPages((pNandDrv->u8_HashPBA[1][1] + u32_BlkIdx) << pNandDrv->u8_BlkPageCntBits, u8MainBuf, u8SpareBuf, 1);
					//binary ID for chunk header
					if( ((U32 *)u8MainBuf)[0x7] == 0x0000B007 && u32_Err == UNFD_ST_SUCCESS)
					{
						u32_MbootBlkIdx[u8_MbootCnt] = (pNandDrv->u8_HashPBA[1][1] + u32_BlkIdx);
						u8_MbootCnt ++;
					}
					if(u8_MbootCnt == 2)
						break;
					if((pNandDrv->u8_HashPBA[1][1] + u32_BlkIdx) == 0xFF)
						break;

					u32_BlkIdx ++;
				}
				if((pNandDrv->u8_HashPBA[1][1] + u32_BlkIdx) == 0xFF)
				{
					//only one mboot or upgrade power cut
					//goto cleanup;
					if(u8_MbootCnt == 1)		//one mboot ->powercut during upgrade->layout ubild
					{
						virtual_boot = u32_MbootBlkIdx[0] * (pNandDrv->u16_BlkPageCnt * pNandDrv->u16_PageByteCnt) / 1024;
						PartSize = PartSize - (u32_MbootBlkIdx[0] - 10) * (pNandDrv->u16_BlkPageCnt * pNandDrv->u16_PageByteCnt) ;
						sprintf(tmp, "%dk@%dk(%s)", PartSize/1024, virtual_boot, PartName);
						printf("Warning: Only One Mboot found, Please re-upgrade your mboot, in case of read ecc fail.\n");
					}
					else	//no mboot  using default for ubild partition impossible in normal case or tool programming case
						goto cleanup;
				}
				else
				{
					 if(u8_MbootCnt == 1)
					{
						virtual_boot = u32_MbootBlkIdx[0] * (pNandDrv->u16_BlkPageCnt * pNandDrv->u16_PageByteCnt) / 1024;
						PartSize = PartSize - (u32_MbootBlkIdx[0] - 10) * (pNandDrv->u16_BlkPageCnt * pNandDrv->u16_PageByteCnt) ;
						sprintf(tmp, "%dk@%dk(%s)", PartSize/1024, virtual_boot, PartName);
					}
					else if(u8_MbootCnt == 2)
					{
						virtual_boot = u32_MbootBlkIdx[0] * (pNandDrv->u16_BlkPageCnt * pNandDrv->u16_PageByteCnt) / 1024;
						//PartSize = PartSize - (u32_MbootBlkIdx[0] - 10) * (pNandDrv->u16_BlkPageCnt * pNandDrv->u16_PageByteCnt) ;
						PartSize1 = (u32_MbootBlkIdx[1] - u32_MbootBlkIdx[0]) * (pNandDrv->u16_BlkPageCnt * pNandDrv->u16_PageByteCnt) ;
						PartSize2 = PartSize - (u32_MbootBlkIdx[1] - 10) * (pNandDrv->u16_BlkPageCnt * pNandDrv->u16_PageByteCnt) ;
						sprintf(tmp, "%dk@%dk(%s),%dk(%sBAK)", PartSize1/1024, virtual_boot, PartName,PartSize2/1024, PartName);
					}
					else
						goto cleanup;
					//virtual_boot = (pNandDrv->u8_HashPBA[1][1] + u32_BlkIdx) * (pNandDrv->u16_BlkPageCnt * pNandDrv->u16_PageByteCnt) / 1024;
					//PartSize = PartSize - (pNandDrv->u8_HashPBA[1][1] + u32_BlkIdx - 10) * (pNandDrv->u16_BlkPageCnt * pNandDrv->u16_PageByteCnt) ;
				}
			}
			else
				goto cleanup;

		}
		len = strlen(tmp);
		memcpy(mtd_buf, tmp, len);
		mtd_buf += len;
		if (Maxlen < len)
			goto cleanup;
		Maxlen -= len;

	}
	if( (pPartInfo->records[u8_i].u16_PartType & UNFD_LOGI_PART) == UNFD_LOGI_PART)
	{
		sprintf(tmp,",-(UBI)");
		len= strlen(tmp);
		memcpy(mtd_buf, tmp, len);
		mtd_buf += len;
		if (Maxlen < len)
			goto cleanup;
		Maxlen -= len;
	}
	*mtd_buf = '\0';
	return ;
	cleanup:
	buf[0] = '\0';
	return ;
}

void nand_SyncMtdPartFor1stBoot(void)
{
	const char *parts;
	char mtd_buf[512];
	char buffer[1024];
	char *pch;

	parts = getenv("mtdparts");
	if(parts == NULL)
		return;

	pch = strstr(parts, "(UBILD)");

	if(pch != NULL)
	{
		pch +=7;		//len of "(UBILD)"

		if(strlen(pch) != 0)
		{
			pch += 1;		//skip ","
			sprintf(mtd_buf, "edb64M-nand:%s", pch);		
			sprintf(buffer,"dynpart %s", mtd_buf);
			run_command(buffer,0);
		}
	}
}


U32 drvNAND_RefreshCIS(void)
{
	NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();
	NAND_FLASH_INFO_t * pNandInfo = (NAND_FLASH_INFO_t* )malloc(512);
	PARTITION_INFO_t *pPartInfo = pNandDrv->pPartInfo;
	U32 u32_BlkIdx, u32_MBootBegin = 0, u32_MBootEnd = 0;
	U32 u32_Err;
	U8 	u8_i;
	int bl_count = 0;

	if(!pNandInfo)
	{
		printf("Memory Allocate fail for pNandInfo\n");
		return -1;
	}


	//setup pNandInfo for CIS
	memset(pNandInfo, 0, 512);
	memcpy(pNandInfo->au8_Tag, "MSTARSEMIUNFDCIS", 16);
	pNandInfo->u8_IDByteCnt = pNandDrv->u8_IDByteCnt;
	memset(pNandInfo->au8_ID, 0, NAND_ID_BYTE_CNT);
	memcpy(pNandInfo->au8_ID, pNandDrv->au8_ID, pNandDrv->u8_IDByteCnt);
	pNandInfo->u16_SpareByteCnt = pNandDrv->u16_SpareByteCnt;
	pNandInfo->u16_PageByteCnt = pNandDrv->u16_PageByteCnt;
	pNandInfo->u16_BlkPageCnt = pNandDrv->u16_BlkPageCnt;
	pNandInfo->u16_BlkCnt = pNandDrv->u16_BlkCnt;
	pNandInfo->u32_Config = pNandDrv->u32_Config;

	pNandInfo->u16_ECCType = pNandDrv->u16_ECCType;
	pNandInfo->u16_tRC          = pNandDrv->u16_tRC;
	pNandInfo->u8_tRP           = pNandDrv->u8_tRP;
	pNandInfo->u8_tREH          = pNandDrv->u8_tREH;
	pNandInfo->u8_tREA          = pNandDrv->u8_tREA;
	pNandInfo->u8_tRR           = pNandDrv->u8_tRR;
	pNandInfo->u16_tADL         = pNandDrv->u16_tADL;
	pNandInfo->u16_tRHW         = pNandDrv->u16_tRHW;
	pNandInfo->u16_tWHR         = pNandDrv->u16_tWHR;
	pNandInfo->u16_tCCS         = pNandDrv->u16_tCCS;
	pNandInfo->u8_tCS           = pNandDrv->u8_tCS;
	pNandInfo->u16_tWC          = pNandDrv->u16_tWC;
	pNandInfo->u8_tWP           = pNandDrv->u8_tWP;
	pNandInfo->u8_tWH           = pNandDrv->u8_tWH;
	pNandInfo->u16_tCWAW        = pNandDrv->u16_tCWAW;
	pNandInfo->u8_tCLHZ			= pNandDrv->u8_tCLHZ;
	pNandInfo->u8_AddrCycleIdx 	= pNandDrv->u8_AddrCycleIdx;
	pNandInfo->u16_tWW			= pNandDrv->u16_tWW;

	pNandInfo->u8_PairPageMapLoc = pNandDrv->u8_PairPageMapLoc;
	pNandInfo->u8_ReadRetryType =	pNandDrv->u8_ReadRetryType;
	pNandInfo->u8_BitflipThreshold = pNandDrv->u16_BitflipThreshold;

	pNandInfo->u32_ChkSum 		= drvNAND_CheckSum((U8*) (pNandInfo) + 0x24, 0x32 - 0x24);

	memcpy(pNandInfo->u8_Vendor, pNandDrv->u8_Vendor, 16);
	memcpy(pNandInfo->u8_PartNumber, pNandDrv->u8_PartNumber, 16);

	pNandInfo->u8_Hash0PageIdx = pNandDrv->u8_Hash0PageIdx;
	pNandInfo->u8_Hash1PageIdx = pNandDrv->u8_Hash1PageIdx;
	pNandInfo->u32_BootSize = pNandDrv->u32_BootSize;

	pNandInfo->u16_BBtPageCheckCount = pNandDrv->u16_BBtPageCheckCount;
	memcpy(pNandInfo->u16_BBtPageIdx, pNandDrv->u16_BBtPageIdx, NAND_BBT_PAGE_COUNT*sizeof(U16));
	memcpy(pNandInfo->u16_BBtMarker, pNandDrv->u16_BBtMarker, NAND_BBT_PAGE_COUNT*sizeof(U16));


	//search MBOOT partition in partinfo

	if(pNandDrv->u8_HasPNI == 1)
	{
		for(u8_i = 0; u8_i < pPartInfo->u16_PartCnt; u8_i ++)
		{
			if(pPartInfo->records[u8_i].u16_PartType == UNFD_PART_UBOOT)
			{
				u32_MBootBegin = pPartInfo->records[u8_i].u16_StartBlk;
				u32_MBootEnd = pPartInfo->records[u8_i].u16_StartBlk + pPartInfo->records[u8_i].u16_BlkCnt + pPartInfo->records[u8_i].u16_BackupBlkCnt;
				break;
			}
		}
		if(u8_i == pPartInfo->u16_PartCnt)
		{
			printf("ERROR: Partition info does not contain MBOOT partition\n");
			return -1;
		}

		//search sboot uboot/ HashX location for update nni infomation

		if(pNandDrv->u8_BL0PBA != 0)	//for bl uboot
		{
			bl_count = 0;
			//search bl location in MBOOT PARTITION
			for(u32_BlkIdx = u32_MBootBegin; u32_BlkIdx < u32_MBootEnd; u32_BlkIdx ++)
			{
				u32_Err = NC_ReadPages(u32_BlkIdx << pNandDrv->u8_BlkPageCntBits, u8MainBuf, u8SpareBuf, 1);
				if(u32_Err != UNFD_ST_SUCCESS)
					continue;
				if(!pNandDrv->u16_BBtPageCheckCount || pNandDrv->u16_BBtPageCheckCount > NAND_BBT_PAGE_COUNT){
					if(u8SpareBuf[0] != 0xFF)
						continue;
				}else{
					if(!drvNAND_CheckSpareSpacePattern(u8SpareBuf, u32_BlkIdx << pNandDrv->u8_BlkPageCntBits))
						continue;
				}
				if(!drvNAND_CheckAll0xFF(u8MainBuf, pNandDrv->u16_PageByteCnt))
				{
					if(bl_count == 0)
						pNandInfo->u8_BL0PBA = pNandDrv->u8_BL0PBA = (U8)u32_BlkIdx;
					else if(bl_count == 1)
					{
						pNandInfo->u8_BL1PBA = pNandDrv->u8_BL1PBA = (U8)u32_BlkIdx;
						bl_count ++;
						break;
					}
					bl_count ++;
				}
			}

			printf("BL0_PBA %X, BL1_PBA %X\n", pNandDrv->u8_BL0PBA, pNandDrv->u8_BL1PBA);
			if(bl_count != 2)
			{
				printf("WARNING: there is no two sboots in NAND Flash, Please Reupgrade Sboot\n");
				return -1;
			}

			if(pNandDrv->u8_UBOOTPBA != 0)
			{
				bl_count = 0;
				for(u32_BlkIdx = u32_MBootBegin; u32_BlkIdx < u32_MBootEnd; u32_BlkIdx ++)
				{
					u32_Err = NC_ReadPages(u32_BlkIdx << pNandDrv->u8_BlkPageCntBits, u8MainBuf, u8SpareBuf, 1);
					if(u32_Err != UNFD_ST_SUCCESS)
						continue;
					if(!pNandDrv->u16_BBtPageCheckCount || pNandDrv->u16_BBtPageCheckCount > NAND_BBT_PAGE_COUNT){
						if(u8SpareBuf[0] != 0xFF)
							continue;
					}else{
						if(!drvNAND_CheckSpareSpacePattern(u8SpareBuf, u32_BlkIdx << pNandDrv->u8_BlkPageCntBits))
							continue;
					}
					if(((U32 *)u8MainBuf)[0x7] == 0x0000B007)
					{
						if(bl_count == 1)
						{
							pNandInfo->u8_UBOOTPBA = pNandDrv->u8_UBOOTPBA = (U8)u32_BlkIdx;
							bl_count ++;
							break;
						}
						bl_count ++;
					}
				}
				if(bl_count != 2)
				{
					printf("WARNING: there is no two Mboots in NAND Flash, Please Reupgrade Mboot\n");
					return -1;
				}

				printf("UBOOTPBA %X\n", pNandDrv->u8_UBOOTPBA);
			}
		}
		else if(pNandDrv->u8_HashPBA[0][0] != 0)	//for hash
		{
			bl_count = 0;
			//search bl location in MBOOT PARTITION
			for(u32_BlkIdx = u32_MBootBegin; u32_BlkIdx < u32_MBootEnd; u32_BlkIdx ++)
			{
				u32_Err = NC_ReadPages(u32_BlkIdx << pNandDrv->u8_BlkPageCntBits, u8MainBuf, u8SpareBuf, 1);
				if(u32_Err != UNFD_ST_SUCCESS)
					continue;
				if(!pNandDrv->u16_BBtPageCheckCount || pNandDrv->u16_BBtPageCheckCount > NAND_BBT_PAGE_COUNT){
					if(u8SpareBuf[0] != 0xFF)
						continue;
				}else{
					if(!drvNAND_CheckSpareSpacePattern(u8SpareBuf, u32_BlkIdx << pNandDrv->u8_BlkPageCntBits))
						continue;
				}

				if(!drvNAND_CheckAll0xFF(u8MainBuf, pNandDrv->u16_PageByteCnt))
				{
					pNandInfo->u8_HashPBA[bl_count>>1][bl_count&1] = pNandDrv->u8_HashPBA[bl_count>>1][bl_count&1] = (U8)u32_BlkIdx;
					if(++bl_count == 4)
						break;
				}
			}

			printf("HASH00_PBA %X, HASH01_PBA %X\n", pNandInfo->u8_HashPBA[0][0], pNandInfo->u8_HashPBA[0][1]);
			printf("HASH10_PBA %X, HASH11_PBA %X\n", pNandInfo->u8_HashPBA[1][0], pNandInfo->u8_HashPBA[1][1]);
			//printf("HASH00_PBA %X, HASH01_PBA %X\n", pNandInfo->u8_HashPBA[0][0], pNandInfo->u8_HashPBA[0][1]);
			if(bl_count != 4)
			{
				printf("WARNING: there is no two sboots in NAND Flash, Please Reupgrade Sboot\n");
				return -1;
			}

			bl_count = 0;
			for(u32_BlkIdx = pNandDrv->u8_HashPBA[1][1]+1; u32_BlkIdx < u32_MBootEnd; u32_BlkIdx ++)
			{
				u32_Err = NC_ReadPages(u32_BlkIdx << pNandDrv->u8_BlkPageCntBits, u8MainBuf, u8SpareBuf, 1);
				if(u32_Err != UNFD_ST_SUCCESS)
					continue;
				if(!pNandDrv->u16_BBtPageCheckCount || pNandDrv->u16_BBtPageCheckCount > NAND_BBT_PAGE_COUNT){
					if(u8SpareBuf[0] != 0xFF)
						continue;
				}else{
					if(!drvNAND_CheckSpareSpacePattern(u8SpareBuf, u32_BlkIdx << pNandDrv->u8_BlkPageCntBits))
						continue;
				}
				if(((U32 *)u8MainBuf)[0x7] == 0x0000B007)
				{
					pNandInfo->u8_HashPBA[2][bl_count] = pNandDrv->u8_HashPBA[2][bl_count] = (U8)u32_BlkIdx;
					if(++bl_count == 2)
						break;
				}
			}
			if(bl_count != 2)
			{
				printf("WARNING: there is no two Mboots in NAND Flash, Please Reupgrade Mboot\n");
				return -1;
			}

			printf("HASH20_PBA %X, HASH21_PBA %X\n", pNandInfo->u8_HashPBA[2][0], pNandInfo->u8_HashPBA[2][1]);
		}
	}

	NC_PlatformInit();

	u32_Err = NC_ResetNandFlash();
	if(u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1,"NAND Reset Fail\n");
		return -1;
	}
	#if defined(FCIE4_DDR) && FCIE4_DDR
	memset((void *) &pNandDrv->tDefaultDDR, 0, sizeof(DDR_TIMING_GROUP_t));
	memset((void *) &pNandDrv->tMaxDDR, 0, sizeof(DDR_TIMING_GROUP_t));
	memset((void *) &pNandDrv->tMinDDR, 0, sizeof(DDR_TIMING_GROUP_t));
	#endif
	NC_ConfigNandFlashContext();
	/*Re-Search DDR timing again*/
	u32_Err = NC_Init();
	if(u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1,"NC_Init Fail ErrCode: %lX\n", u32_Err);
		return -1;
	}
	NC_Config();

	nand_config_clock(pNandInfo->u16_tRC);

	u32_Err = drvNAND_WriteCIS_for_ROM(pNandInfo);

	nand_SyncMtdPartFor1stBoot();
	
	return u32_Err;
}

#if ENABLE_MODULE_BFN_WRITE_NAND
#define CHIPCFG_CMD_BASE       0xFE00
#define CHIPCFG_CMD_END        0xFFF0
#define CHIPCFG_CMD_WAIT       0xFF00
#define CHIPCFG_CMD_DBG        0xFFE0

unsigned char *nand_buffer;
static unsigned char nand_buffer2[16384] __attribute((aligned(64)));
static unsigned char nand_buffer_spare[16384] __attribute((aligned(64)));

#define MIUIDTAG    (0x4D495530)      // 'MIU0'
#define LDRIDTAG    (0x4C445230)      // 'LDR0'
#define BINIDTAG    (0x42494E30)      // 'BIN0'

static U32 BFN_WritePage_MIU(U32 u32Row, U8 *u8Buf, U8 *u8Spare, U16 u16Repeat, U16 autodis)
{
    NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();
    U32 u32_Err = UNFD_ST_SUCCESS;


    if(autodis)
    {
        pNandDrv->u16_Reg48_Spare |= BIT_NC_HW_AUTO_RANDOM_CMD_DISABLE;
        NC_Config();
    }

    u32_Err = NC_WritePages( u32Row, u8Buf, u8Spare, u16Repeat);
    if( u32_Err != UNFD_ST_SUCCESS)
	{
        printf("NC_WritePages error\n");
    }

    if(autodis)
    {
        pNandDrv->u16_Reg48_Spare &= ~BIT_NC_HW_AUTO_RANDOM_CMD_DISABLE;
        NC_Config();
    }

    return u32_Err;
}

static U32 BFN_ReadPage_MIU(U32 u32Row, U8 *u8Buf, U8 *u8Spare, U16 u16Repeat, U16 autodis)
{
    NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();
    U32 u32_Err = UNFD_ST_SUCCESS;

    if(autodis)
    {
        pNandDrv->u16_Reg48_Spare |= BIT_NC_HW_AUTO_RANDOM_CMD_DISABLE;
        NC_Config();
    }

    u32_Err = NC_ReadPages( u32Row, u8Buf, u8Spare, u16Repeat);
    if( u32_Err != UNFD_ST_SUCCESS)
	{
        printf("NC_ReadPages error\n");
    }

    if(autodis)
    {
        pNandDrv->u16_Reg48_Spare &= ~BIT_NC_HW_AUTO_RANDOM_CMD_DISABLE;
        NC_Config();
    }

    return u32_Err;
}

static U32 BFN_WriteSector(U32 u32PageIndex, U8 *u8Buf, U8 *u8Spare, U16 autodis)
{
    NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();
    U32 u32_Err = UNFD_ST_SUCCESS;


    if(autodis)
    {
        pNandDrv->u16_Reg48_Spare |= BIT_NC_HW_AUTO_RANDOM_CMD_DISABLE;
        NC_Config();
    }

    u32_Err = NC_WriteSectors( u32PageIndex, 0, u8Buf, u8Spare, 1);
    if( u32_Err != UNFD_ST_SUCCESS)
	{
        printf("NC_WriteSectors error\n");
    }

    NC_Write_RandomOut(u32PageIndex,0,u8Buf,16);

    if(autodis)
    {
        pNandDrv->u16_Reg48_Spare &= ~BIT_NC_HW_AUTO_RANDOM_CMD_DISABLE;
        NC_Config();
    }

    return u32_Err;
}

static U32 BFN_ReadSector_RIU(U32 u32Row, U32 u32Col, U8 *u8Buf, U8 *u8SprBuf ,U16 autodis)
{
    NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();
    U32 u32_Err = UNFD_ST_SUCCESS;

    if(autodis)
    {
        pNandDrv->u16_Reg48_Spare |= BIT_NC_HW_AUTO_RANDOM_CMD_DISABLE;
        NC_Config();
    }

    u32_Err = NC_ReadSector_RIUMode(u32Row, u32Col, u8Buf, u8SprBuf);

    if(autodis)
    {
        pNandDrv->u16_Reg48_Spare &= ~BIT_NC_HW_AUTO_RANDOM_CMD_DISABLE;
        NC_Config();
    }

    return u32_Err;
}

int drvNAND_ReadMIUParam(U32 u32MIUPos)
{
	/*
    int              retlen=0;
    while (1)
    {
        U16 reg = *(U16*)u32MIUPos;

        retlen += 4;

        if (reg == CHIPCFG_CMD_END)
            return retlen;

        u32MIUPos += 4;
    }
    return 0;
	*/
	 return 0x2000;
}


U32 drvNAND_WriteMIUParam(int MIUBLOCK, U32 MIUPOS)
{
    NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();

    int ParamMIUSize;
    int ProgramPage=0;
    U32 u32_Err = UNFD_ST_SUCCESS;

    u32_Err = NC_EraseBlk( MIUBLOCK * pNandDrv->u16_BlkPageCnt );//use first block as test item
    if (u32_Err != UNFD_ST_SUCCESS)
    {
        printf("MIU write blk error!!\n");
        drvNAND_MarkBadBlk(MIUBLOCK);
        return 0;
    }

    //==============write MIU position==============
    // read MIU parameter

    ParamMIUSize = drvNAND_ReadMIUParam(MIUPOS);

    *((U32*)(nand_buffer2+0x00)) = MIUIDTAG;//0x4D495530
    *((U32*)(nand_buffer2+0x04)) = pNandDrv->u16_PageByteCnt;
    *((U32*)(nand_buffer2+0x10)) = ParamMIUSize>>9; // number of MIU page (in 512 bytes size)
    *((U32*)(nand_buffer2+0x14)) = pNandDrv->u16_BlkPageCnt;

    memset(nand_buffer_spare, -1, sizeof(nand_buffer_spare));

    printf("MIU parameter size %d\n",ParamMIUSize);
    BFN_WritePage_MIU(MIUBLOCK * pNandDrv->u16_BlkPageCnt + ProgramPage, (U8*)nand_buffer2,(U8*)nand_buffer_spare,1,1);
    ProgramPage++;
    printf("Write First Page, ParamMIUSize left %d program page number %d\n",ParamMIUSize,ProgramPage);

    while(ParamMIUSize > 0)
    {
        BFN_WritePage_MIU(MIUBLOCK * pNandDrv->u16_BlkPageCnt+ProgramPage,(U8*)nand_buffer+((ProgramPage-1)*(512)), (U8*)nand_buffer_spare,1,1);
        ParamMIUSize -= 512;
        ProgramPage ++;
        printf("Write next Page, ParamMIUSize left %d program page number %d\n",ParamMIUSize,ProgramPage);
    }

    return 1;
}

U32 drvNAND_WriteCISMIUParam(int MIUBLOCK, U32 MIUPOS, NAND_FLASH_INFO_t * pNandInfo)
{
    NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();
    PARTITION_INFO_t *pPartInfo = drvNAND_get_DrvContext_PartInfo();
    BLK_INFO_t *pBlkInfo = (BLK_INFO_t*)nand_buffer_spare;

    int ParamMIUSize;
    int ProgramPage=0;
    U32 u32_Err = UNFD_ST_SUCCESS;
    U32 u32_PageIdx;
    U16 u16_CISIdx;

    /* Check first page of block */
    u32_PageIdx = MIUBLOCK << pNandDrv->u8_BlkPageCntBits;
    u32_Err = BFN_ReadPage_MIU(u32_PageIdx,nand_buffer2,nand_buffer_spare,1,1);
    if (u32_Err != UNFD_ST_SUCCESS)
    {
        printf("MIU write blk error!!%s %x\n",__FUNCTION__,__LINE__);
    }
    if (nand_buffer_spare[0] != 0xFF)
    {
        printf("MIU write blk error!!%s %x\n",__FUNCTION__,__LINE__);
        return 0;
    }

    u32_Err = NC_EraseBlk( MIUBLOCK * pNandDrv->u16_BlkPageCnt );//use first block as test item
    if (u32_Err != UNFD_ST_SUCCESS)
    {
        printf("MIU write blk error!!%s %x\n",__FUNCTION__,__LINE__);
        drvNAND_MarkBadBlk(MIUBLOCK);
        return 0;
    }

    //==============write MIU position==============
    // read MIU parameter

    ParamMIUSize = drvNAND_ReadMIUParam(MIUPOS);

    /* original drvNAND_WriteCIS_for_ROM*/
    NC_ConfigNandFlashContext();
    NC_RegInit();
    NC_Config();

    nand_config_clock(pNandInfo->u16_tRC);

	#if defined(FCIE4_DDR) && FCIE4_DDR
	memcpy((void *) &pNandInfo->tDefaultDDR, (const void *) &pNandDrv->tDefaultDDR, sizeof(DDR_TIMING_GROUP_t));
	memcpy((void *) &pNandInfo->tMaxDDR, (const void *) &pNandDrv->tMaxDDR, sizeof(DDR_TIMING_GROUP_t));
	memcpy((void *) &pNandInfo->tMinDDR, (const void *) &pNandDrv->tMinDDR, sizeof(DDR_TIMING_GROUP_t));
	#endif

    u16_CISIdx = REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) );
    switch (u16_CISIdx) {
		case 2:
            printf("for first cis index\n");
			u16_CISIdx = 0;
			break;
		case 3:
            printf("for second cis index");
            u16_CISIdx = 1;
			break;
		default:
            printf("for first cis index");
            REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) ) = 0;
			u16_CISIdx = 0;
			break;
	}

    /* Reeset NAND driver and FCIE to the original settings */
    pNandDrv->u16_SpareByteCnt = pNandInfo->u16_SpareByteCnt;
    pNandDrv->u16_PageByteCnt  = pNandInfo->u16_PageByteCnt;
    pNandDrv->u16_ECCType      = pNandInfo->u16_ECCType;
    NC_ConfigNandFlashContext();
    NC_RegInit();
    pNandDrv->u16_Reg48_Spare &= ~(1 << 12);
    #if defined(FCIE_LFSR) && FCIE_LFSR
    if(pNandDrv->u8_RequireRandomizer)
        NC_DisableLFSR();
    #endif
    NC_Config();

    pNandDrv->u16_PageByteCnt = 2048;
    pNandDrv->u16_SpareByteCnt = 256;
    pNandDrv->u16_ECCType = NANDINFO_ECC_TYPE;

    NC_ConfigNandFlashContext();
    NC_RegInit();

    // copy CIS to the buffer offset 0x20
    memset(nand_buffer2, '\0', 512);
    memcpy(nand_buffer2,pNandInfo,512);
    memset(nand_buffer_spare, -1, sizeof(nand_buffer_spare));

    pBlkInfo->u8_BadBlkMark = 0xFF;
    pBlkInfo->u8_PartType = 0;

    u32_Err = BFN_WriteSector(MIUBLOCK * pNandDrv->u16_BlkPageCnt + ProgramPage, (U8*)nand_buffer2,(U8*)nand_buffer_spare,1);

    if (u32_Err != UNFD_ST_SUCCESS)
    {
        printf("MIU write blk error!!%s %x\n",__FUNCTION__,__LINE__);
        drvNAND_MarkBadBlk(MIUBLOCK);
        return 0;
    }

    /*
        **  Write Partition Info the 2nd page
        **/
	if(pNandDrv->u8_HasPNI == 1)
	{
		memset(nand_buffer2, '\0', pNandDrv->u16_PageByteCnt);
		memcpy(nand_buffer2, pPartInfo, 512);

        u32_Err = BFN_WriteSector(MIUBLOCK * pNandDrv->u16_BlkPageCnt + ga_tPairedPageMap[1].u16_LSB, (U8*)nand_buffer2,(U8*)nand_buffer_spare,1);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			printf("MIU write blk error!!%s %x\n",__FUNCTION__,__LINE__);
			drvNAND_MarkBadBlk(MIUBLOCK);
			return 0;
		}
	}

    /*
    **  Write Paired Page Map to the 4th page
    **/
    if(pNandDrv->u8_CellType == 1)  // MLC
    {
        memset(nand_buffer2, '\0', pNandDrv->u16_PageByteCnt);
        memcpy(nand_buffer2, &ga_tPairedPageMap, 2048);

        u32_Err = BFN_WriteSector(MIUBLOCK * pNandDrv->u16_BlkPageCnt + pNandInfo->u8_PairPageMapLoc, (U8*)nand_buffer2,(U8*)nand_buffer_spare,1);
		if (u32_Err != UNFD_ST_SUCCESS) {
            printf("MIU write blk error!!%s %x\n",__FUNCTION__,__LINE__);
            drvNAND_MarkBadBlk(MIUBLOCK);
            return 0;
        }
    }
    u16_CISIdx++;

    printf("CIS is written to blk 0x%04x\n", MIUBLOCK);

    // chk cis index
	switch (u16_CISIdx) {
		case 0:
			REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) )  = 0x0002;
			u32_Err = UNFD_ST_ERR_NO_BLK_FOR_CIS0;
			break;
		case 1:
			REG(RIU_BASE + (0x1980 << 2) + (0x41 << 2) )  = 0x0003;
			u32_Err = UNFD_ST_ERR_NO_BLK_FOR_CIS1;
			break;
		case 2:
			u32_Err = UNFD_ST_SUCCESS;
			break;
	}

    printf("MIU parameter size %d, sector byte count %d\n",ParamMIUSize, pNandDrv->u16_SectorByteCnt);

    ProgramPage = 10;


    while(ParamMIUSize > 0)
    {
        printf("Write Page, ParamMIUSize left %d program page number %d\n",ParamMIUSize,ProgramPage);
        u32_Err = BFN_WriteSector(MIUBLOCK * pNandDrv->u16_BlkPageCnt+ProgramPage,(U8*)nand_buffer+((ProgramPage-10)*(pNandDrv->u16_SectorByteCnt)), (U8*)nand_buffer_spare,1);
        if (u32_Err != UNFD_ST_SUCCESS)
        {
            printf("MIU write blk error!!%s %x\n",__FUNCTION__,__LINE__);
        }

        ParamMIUSize -= pNandDrv->u16_SectorByteCnt;
        ProgramPage ++;
    }
    printf("totally write %x\n",ProgramPage-10);

    /* Reset NAND driver and FCIE to the original settings */
    pNandDrv->u16_SpareByteCnt = pNandInfo->u16_SpareByteCnt;
    pNandDrv->u16_PageByteCnt  = pNandInfo->u16_PageByteCnt;
    pNandDrv->u16_ECCType      = pNandInfo->u16_ECCType;
    NC_ConfigNandFlashContext();
    NC_RegInit();
    pNandDrv->u16_Reg48_Spare &= ~(1 << 12);
	NC_Config();

    return 1;
}

U32 drvNAND_RefreshCISMIUParam(int MIUBLOCK, U32 MIUPOS)
{
	NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();
	NAND_FLASH_INFO_t * pNandInfo = (NAND_FLASH_INFO_t* )malloc(512);
	PARTITION_INFO_t *pPartInfo = pNandDrv->pPartInfo;
	U32 u32_BlkIdx, u32_MBootBegin = 0, u32_MBootEnd = 0;
	U32 u32_Err;
	U8 	u8_i;
	int bl_count = 0;

	if(!pNandInfo)
	{
		printf("Memory Allocate fail for pNandInfo\n");
		return -1;
	}

	//setup pNandInfo for CIS
	memset(pNandInfo, 0, 512);
	memcpy(pNandInfo->au8_Tag, "MSTARSEMIUNFDCIS", 16);
	pNandInfo->u8_IDByteCnt = pNandDrv->u8_IDByteCnt;
	memset(pNandInfo->au8_ID, 0, NAND_ID_BYTE_CNT);
	memcpy(pNandInfo->au8_ID, pNandDrv->au8_ID, pNandDrv->u8_IDByteCnt);
	pNandInfo->u16_SpareByteCnt = pNandDrv->u16_SpareByteCnt;
	pNandInfo->u16_PageByteCnt = pNandDrv->u16_PageByteCnt;
	pNandInfo->u16_BlkPageCnt = pNandDrv->u16_BlkPageCnt;
	pNandInfo->u16_BlkCnt = pNandDrv->u16_BlkCnt;
	pNandInfo->u32_Config = pNandDrv->u32_Config;

	pNandInfo->u16_ECCType = pNandDrv->u16_ECCType;
	pNandInfo->u16_tRC          = pNandDrv->u16_tRC;
	pNandInfo->u8_tRP           = pNandDrv->u8_tRP;
	pNandInfo->u8_tREH          = pNandDrv->u8_tREH;
	pNandInfo->u8_tREA          = pNandDrv->u8_tREA;
	pNandInfo->u8_tRR           = pNandDrv->u8_tRR;
	pNandInfo->u16_tADL         = pNandDrv->u16_tADL;
	pNandInfo->u16_tRHW         = pNandDrv->u16_tRHW;
	pNandInfo->u16_tWHR         = pNandDrv->u16_tWHR;
	pNandInfo->u16_tCCS         = pNandDrv->u16_tCCS;
	pNandInfo->u8_tCS           = pNandDrv->u8_tCS;
	pNandInfo->u16_tWC          = pNandDrv->u16_tWC;
	pNandInfo->u8_tWP           = pNandDrv->u8_tWP;
	pNandInfo->u8_tWH           = pNandDrv->u8_tWH;
	pNandInfo->u16_tCWAW        = pNandDrv->u16_tCWAW;
	pNandInfo->u8_tCLHZ			= pNandDrv->u8_tCLHZ;
	pNandInfo->u8_AddrCycleIdx 	= pNandDrv->u8_AddrCycleIdx;
	pNandInfo->u16_tWW			= pNandDrv->u16_tWW;

	pNandInfo->u8_PairPageMapLoc = pNandDrv->u8_PairPageMapLoc;
	pNandInfo->u8_ReadRetryType =	pNandDrv->u8_ReadRetryType;
	pNandInfo->u8_BitflipThreshold = pNandDrv->u16_BitflipThreshold;

	pNandInfo->u32_ChkSum 		= drvNAND_CheckSum((U8*) (pNandInfo) + 0x24, 0x32 - 0x24);

	memcpy(pNandInfo->u8_Vendor, pNandDrv->u8_Vendor, 16);
	memcpy(pNandInfo->u8_PartNumber, pNandDrv->u8_PartNumber, 16);

	pNandInfo->u8_Hash0PageIdx = pNandDrv->u8_Hash0PageIdx;
	pNandInfo->u8_Hash1PageIdx = pNandDrv->u8_Hash1PageIdx;
	pNandInfo->u32_BootSize = pNandDrv->u32_BootSize;

	//search MBOOT partition in partinfo

	if(pNandDrv->u8_HasPNI == 1)
	{
		for(u8_i = 0; u8_i < pPartInfo->u16_PartCnt; u8_i ++)
		{
			if(pPartInfo->records[u8_i].u16_PartType == UNFD_PART_UBOOT)
			{
				u32_MBootBegin = pPartInfo->records[u8_i].u16_StartBlk;
				u32_MBootEnd = pPartInfo->records[u8_i].u16_StartBlk + pPartInfo->records[u8_i].u16_BlkCnt + pPartInfo->records[u8_i].u16_BackupBlkCnt;
				break;
			}
		}
		if(u8_i == pPartInfo->u16_PartCnt)
		{
			printf("ERROR: Partition info does not contain MBOOT partition\n");
			return -1;
		}

		//search sboot uboot/ HashX location for update nni infomation

		if(pNandDrv->u8_BL0PBA != 0)	//for bl uboot
		{
			bl_count = 0;
			//search bl location in MBOOT PARTITION
			for(u32_BlkIdx = u32_MBootBegin; u32_BlkIdx < u32_MBootEnd; u32_BlkIdx ++)
			{
				u32_Err = NC_ReadPages(u32_BlkIdx << pNandDrv->u8_BlkPageCntBits, u8MainBuf, u8SpareBuf, 1);
				if(u32_Err != UNFD_ST_SUCCESS || u8SpareBuf[0] !=0xFF)
					continue;
				if(!drvNAND_CheckAll0xFF(u8MainBuf, pNandDrv->u16_PageByteCnt))
				{
					if(bl_count == 0)
						pNandInfo->u8_BL0PBA = pNandDrv->u8_BL0PBA = (U8)u32_BlkIdx;
					else if(bl_count == 1)
					{
						pNandInfo->u8_BL1PBA = pNandDrv->u8_BL1PBA = (U8)u32_BlkIdx;
						bl_count ++;
						break;
					}
					bl_count ++;
				}
			}

			printf("BL0_PBA %X, BL1_PBA %X\n", pNandDrv->u8_BL0PBA, pNandDrv->u8_BL1PBA);
			if(bl_count != 2)
			{
				printf("WARNING: there is no two sboots in NAND Flash, Please Reupgrade Sboot\n");
				return -1;
			}

			if(pNandDrv->u8_UBOOTPBA != 0)
			{
				bl_count = 0;
				for(u32_BlkIdx = u32_MBootBegin; u32_BlkIdx < u32_MBootEnd; u32_BlkIdx ++)
				{
					u32_Err = NC_ReadPages(u32_BlkIdx << pNandDrv->u8_BlkPageCntBits, u8MainBuf, u8SpareBuf, 1);
					if(u32_Err != UNFD_ST_SUCCESS || u8SpareBuf[0] !=0xFF)
						continue;
					if(((U32 *)u8MainBuf)[0x7] == 0x0000B007)
					{
						if(bl_count == 1)
						{
							pNandInfo->u8_UBOOTPBA = pNandDrv->u8_UBOOTPBA = (U8)u32_BlkIdx;
							bl_count ++;
							break;
						}
						bl_count ++;
					}
				}
				if(bl_count != 2)
				{
					printf("WARNING: there is no two Mboots in NAND Flash, Please Reupgrade Mboot\n");
					return -1;
				}

				printf("UBOOTPBA %X\n", pNandDrv->u8_UBOOTPBA);
			}
		}
		else if(pNandDrv->u8_HashPBA[0][0] != 0)	//for hash
		{
			bl_count = 0;
			//search bl location in MBOOT PARTITION
			for(u32_BlkIdx = u32_MBootBegin; u32_BlkIdx < u32_MBootEnd; u32_BlkIdx ++)
			{
				u32_Err = NC_ReadPages(u32_BlkIdx << pNandDrv->u8_BlkPageCntBits, u8MainBuf, u8SpareBuf, 1);
				if(u32_Err != UNFD_ST_SUCCESS || u8SpareBuf[0] !=0xFF)
					continue;
				if(!drvNAND_CheckAll0xFF(u8MainBuf, pNandDrv->u16_PageByteCnt))
				{
					pNandInfo->u8_HashPBA[bl_count>>1][bl_count&1] = pNandDrv->u8_HashPBA[bl_count>>1][bl_count&1] = (U8)u32_BlkIdx;
					if(++bl_count == 4)
						break;
				}
			}

			printf("HASH00_PBA %X, HASH01_PBA %X\n", pNandInfo->u8_HashPBA[0][0], pNandInfo->u8_HashPBA[0][1]);
			printf("HASH10_PBA %X, HASH11_PBA %X\n", pNandInfo->u8_HashPBA[1][0], pNandInfo->u8_HashPBA[1][1]);
			//printf("HASH00_PBA %X, HASH01_PBA %X\n", pNandInfo->u8_HashPBA[0][0], pNandInfo->u8_HashPBA[0][1]);
			if(bl_count != 4)
			{
				printf("WARNING: there is no two sboots in NAND Flash, Please Reupgrade Sboot\n");
				return -1;
			}

			bl_count = 0;
			for(u32_BlkIdx = pNandDrv->u8_HashPBA[1][1]+1; u32_BlkIdx < u32_MBootEnd; u32_BlkIdx ++)
			{
				u32_Err = NC_ReadPages(u32_BlkIdx << pNandDrv->u8_BlkPageCntBits, u8MainBuf, u8SpareBuf, 1);
				if(u32_Err != UNFD_ST_SUCCESS || u8SpareBuf[0] !=0xFF)
					continue;
				if(((U32 *)u8MainBuf)[0x7] == 0x0000B007)
				{
					pNandInfo->u8_HashPBA[2][bl_count] = pNandDrv->u8_HashPBA[2][bl_count] = (U8)u32_BlkIdx;
					if(++bl_count == 2)
						break;
				}
			}
			if(bl_count != 2)
			{
				printf("WARNING: there is no two Mboots in NAND Flash, Please Reupgrade Mboot\n");
				return -1;
			}

			printf("HASH20_PBA %X, HASH21_PBA %X\n", pNandInfo->u8_HashPBA[2][0], pNandInfo->u8_HashPBA[2][1]);
		}
        else
        {
            printf("loop\n");
        }
	}

    dump_nand_info(pNandInfo);

	NC_PlatformInit();

	u32_Err = NC_ResetNandFlash();
	if(u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1,"NAND Reset Fail\n");
		return -1;
	}
#if defined(FCIE4_DDR) && FCIE4_DDR
	memset((void *) &pNandDrv->tDefaultDDR, 0, sizeof(DDR_TIMING_GROUP_t));
	memset((void *) &pNandDrv->tMaxDDR, 0, sizeof(DDR_TIMING_GROUP_t));
	memset((void *) &pNandDrv->tMinDDR, 0, sizeof(DDR_TIMING_GROUP_t));
#endif
	NC_ConfigNandFlashContext();
	/*Re-Search DDR timing again*/
	u32_Err = NC_Init();
	if(u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1,"NC_Init Fail ErrCode: %lX\n", u32_Err);
		return -1;
	}
	NC_Config();

	nand_config_clock(pNandInfo->u16_tRC);


    drvNAND_WriteCISMIUParam(MIUBLOCK,MIUPOS,pNandInfo);

    printf("sizeof CIS is %x\n",sizeof(NAND_FLASH_INFO_t));
    return 0;
}

U32 drvNAND_SearchCISMIUParam(void)
{
    U32 u32_Err;

    u32_Err = drvNAND_SearchCIS();
#if defined(ENABLE_READ_DISTURBANCE_SUPPORT) && ENABLE_READ_DISTURBANCE_SUPPORT
	if(u32_Err == UNFD_ST_SUCCESS)
	{
		nand_ReadDisturbance();
	}
#endif



    return 0;
}

U32 drvNAND_WriteLoader(int LOADERBLOCK, U8* u8LDRPos)
{
    U32             Ldr2MIUPos = 0;
    U32             LdrSize = 0;
    U32             LdrEntryOffset = 0; // means the actually position offset from u8BINPos for bin file to store
    U32             LdrStackPoint = 0;
    int i=0,j=LOADERBLOCK;

    NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();

    memset(nand_buffer2, 0, 0x100);

    Ldr2MIUPos = *((U32*)(u8LDRPos));
    LdrSize = *((U32*)(u8LDRPos+12));
    LdrEntryOffset = *((U32*)(u8LDRPos+4));
    LdrStackPoint = *((U32*)(u8LDRPos+8));
    Ldr2MIUPos += LdrEntryOffset;
    u8LDRPos += LdrEntryOffset;
    LdrSize -= LdrEntryOffset;

    *((U32*)(nand_buffer2+0x00)) = LDRIDTAG;
    *((U32*)(nand_buffer2+0x04)) = Ldr2MIUPos;// the position we are going to put to MIU and jump
    *((U32*)(nand_buffer2+0x10)) = LDRIDTAG;
    *((U32*)(nand_buffer2+0x14)) = LdrSize;
    *((U32*)(nand_buffer2+0x20)) = LDRIDTAG;
    *((U32*)(nand_buffer2+0x24)) = LdrStackPoint;
    //*((U32*)(nand_buffer_spare+16)) = APPEntryOffset;//start point of AP

    printf("[%lx]MIU pos %lx\r\nLoader file size %lx\r\nLoader Entry offset %lx\r\n",(U32)u8LDRPos,Ldr2MIUPos,LdrSize,LdrEntryOffset);
    printf("Loader stack point: %lx\n",LdrStackPoint);
 
    memset(nand_buffer_spare, -1, sizeof(nand_buffer_spare));
    while(LdrSize)
    {
        if (i==0)
        {
            printf("<flow control>issue erase [block:%x] operation!\n",j);
            NC_EraseBlk(j * pNandDrv->u16_BlkPageCnt);
            BFN_WritePage_MIU((j * pNandDrv->u16_BlkPageCnt)+i,(U8*)nand_buffer2,(U8*)nand_buffer_spare,1,0);
            i++;
            continue;
        }

        BFN_WritePage_MIU((j * pNandDrv->u16_BlkPageCnt)+i,(U8*)u8LDRPos,(U8*)nand_buffer_spare,1,0);

        u8LDRPos += ((LdrSize < pNandDrv->u16_PageByteCnt ) ? LdrSize : pNandDrv->u16_PageByteCnt);
        LdrSize -= ((LdrSize < pNandDrv->u16_PageByteCnt ) ? LdrSize : pNandDrv->u16_PageByteCnt);
        i++;

        if (i== pNandDrv->u16_BlkPageCnt)
        {
            j++;
            i=0;
            printf("<flow control>reset i back to 0 and check block to next [block:%x]\n",j);
        }
    }

    return 1;
}


static U16 HEADER_OFFSET = 0x100;

U32 drvNAND_WriteBINParam(int BINBLOCK,U8* u8BINPos)
{
    U32             Bin2MIUPos = 0;
    U32             BinSize = 0;
    U32             APPEntryOffset = 0; // means the actually position offset from u8BINPos for bin file to store

    int i=0,j=BINBLOCK;

    NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();

    memset(nand_buffer2, 0, 0x100);
    
    Bin2MIUPos = *((U32*)(u8BINPos));
    BinSize = *((U32*)(u8BINPos+8));
    APPEntryOffset = *((U32*)(u8BINPos+4));
    Bin2MIUPos += HEADER_OFFSET; //APPEntryOffset;
    u8BINPos += HEADER_OFFSET;//APPEntryOffset;
    BinSize -= HEADER_OFFSET;//APPEntryOffset;
    APPEntryOffset -= HEADER_OFFSET;
    *((U32*)(nand_buffer2+0x00)) = BINIDTAG;
    *((U32*)(nand_buffer2+0x04)) = Bin2MIUPos;
    *((U32*)(nand_buffer2+0x10)) = BINIDTAG; // the position we are going to put to MIU and jump
    *((U32*)(nand_buffer2+0x14)) = BinSize;
    *((U32*)(nand_buffer2+0x20)) = BINIDTAG; // the position we are going to put to MIU and jump
    *((U32*)(nand_buffer2+0x24)) = APPEntryOffset;
    //*((U32*)(nand_buffer_spare+16)) = APPEntryOffset;//start point of AP

    printf("[%lx]MIU pos %lx\r\nBin file size %lx\r\nApp Entry offset %lx\r\n",(U32)u8BINPos,Bin2MIUPos,BinSize,APPEntryOffset);

    memset(nand_buffer_spare, -1, sizeof(nand_buffer_spare));

    while(BinSize)
    {
        if (i==0)
        {
            printf("<flow control>issue erase [block:%x] operation!\n",j);
            NC_EraseBlk(j * pNandDrv->u16_BlkPageCnt);
            BFN_WritePage_MIU((j * pNandDrv->u16_BlkPageCnt)+i,(U8*)nand_buffer2,(U8*)nand_buffer_spare,1,0);
            i++;
            continue;
        }

        BFN_WritePage_MIU((j * pNandDrv->u16_BlkPageCnt)+i,(U8*)u8BINPos,(U8*)nand_buffer_spare,1,0);

        u8BINPos += ((BinSize < pNandDrv->u16_PageByteCnt ) ? BinSize : pNandDrv->u16_PageByteCnt);
        BinSize -= ((BinSize < pNandDrv->u16_PageByteCnt ) ? BinSize : pNandDrv->u16_PageByteCnt);
        i++;

        if (i== pNandDrv->u16_BlkPageCnt)
        {
            j++;
            i=0;
            printf("<flow control>reset i back to 0 and check block to next [block:%x]\n",j);
        }
    }

    return 1;
}


U32 drvNAND_ReadNANDMIUParam(void)
{
    U32 row_pos = 0;
    NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();

    while(1) {
        printf("next row position %lx\n",row_pos);
        BFN_ReadSector_RIU(row_pos, 0,nand_buffer,nand_buffer_spare,1);

        printf("%x\n",*((U32*)(nand_buffer)));
        if (*((U32*)(nand_buffer)) == MIUIDTAG)
        {
            printf("tag correct\n");
            printf("read next block\n");

            break;
        }

        row_pos += pNandDrv->u16_BlkPageCnt;
        if (row_pos > (0x10*pNandDrv->u16_BlkPageCnt ))
            return 1;

    }
U32 BINSize=0;
    while (1)
    {
        printf("2next row position %lx\n",row_pos);
        BFN_ReadPage_MIU(row_pos, nand_buffer,nand_buffer_spare,1,0);
        //_PUTDW(*((MS_U32*)(MIUPos)));
        printf("%lx\n",*((U32*)(nand_buffer)));
        if (*((U32*)(nand_buffer)) == LDRIDTAG)
        {
            printf("tag correct\n");
            printf("size %lx miu pos %lx\n",*((U32*)(nand_buffer+20)),*((U32*)(nand_buffer+4)));
            BINSize=*((U32*)(nand_buffer+20));
            break;
        }
        row_pos += pNandDrv->u16_BlkPageCnt;
    }

    U32 i=0;

    while(BINSize)
    {
        //_PUTDW(row_pos);
        printf("3next row position %lx %lx\n",row_pos,i);
        BFN_ReadPage_MIU(row_pos, nand_buffer,nand_buffer_spare,1,0);
        if (i==0)
        {
            if (*((U32*)(nand_buffer)) != LDRIDTAG)
            {
                row_pos += pNandDrv->u16_BlkPageCnt;
            }
            else
            {
                i++;
            }
            continue;
        }

        //_PUTC('E');
        i++;
        nand_buffer += pNandDrv->u16_PageByteCnt;
        BINSize -= ((BINSize < pNandDrv->u16_PageByteCnt)?BINSize:pNandDrv->u16_PageByteCnt);
        if (i==pNandDrv->u16_BlkPageCnt)
        {
            row_pos += pNandDrv->u16_BlkPageCnt;
            i=0;
        }
        //_PUTDW(BINSize);
    }
    return 0;
}




U32 drvNAND_BFN_FLASH_INFO(U32 bfn_type,U32 bfn_blk,U32 bfn_addr)
{
    NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();

    printf("byte per page %d page per block %d total block %d\n", pNandDrv->u16_PageByteCnt, pNandDrv->u16_BlkPageCnt, pNandDrv->u16_BlkCnt);

    nand_buffer = (unsigned char *)bfn_addr;

    switch (bfn_type)
    {
    case 1://miu
        // if Partial Mode (if not 512B/page, set Partial Mode)
        drvNAND_WriteMIUParam(bfn_blk,bfn_addr);
        //drvNAND_ReadNANDMIUParam(); /* for Test */
        break;
    case 2://ldr
        drvNAND_WriteLoader(bfn_blk,(U8*)bfn_addr);
        break;
    case 3://app
        printf("bfn block %lx bfn address %lx\n",bfn_blk,bfn_addr);
        drvNAND_WriteBINParam(bfn_blk,(U8*)bfn_addr);
        break;
    case 4://chk
        printf("gogogogog\n");
        drvNAND_ReadNANDMIUParam();
        break;
    case 5://cis for box
        printf("refreshCIS for box use\n");
        drvNAND_RefreshCISMIUParam(bfn_blk,bfn_addr);
        break;
    case 6:
        printf("check for CIS correctness\n");
        drvNAND_SearchCISMIUParam();
    default:
        return 0;
    }

    return 1;
}
//=====================
#endif
