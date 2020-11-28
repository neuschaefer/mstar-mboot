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

#include "../../inc/common/eMMC.h"
#if defined(UNIFIED_eMMC_DRIVER) && UNIFIED_eMMC_DRIVER
#if 0
//--------------------------------------------------------------------------
static eMMC_ALIGN0 eMMC_TEST_ALIGN_PACK_t g_eMMCTestAlignPack_t eMMC_ALIGN1;
U32 eMMC_CheckAlignPack(U8 u8_AlignByteCnt)
{
	// check alignment
	if((U32)&(g_eMMCTestAlignPack_t.u8_0) & (u8_AlignByteCnt-1))
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: not aliged. expect %Xh but %Xh \n",
			u8_AlignByteCnt, (U32)&(g_eMMCTestAlignPack_t.u8_0));
		eMMC_die();
		return eMMC_ST_ERR_NOT_ALIGN;
	}
	// check packed - 0
	if((U32)&(g_eMMCTestAlignPack_t.u16_0)-(U32)&(g_eMMCTestAlignPack_t.u8_0) != 1 ||
	   (U32)&(g_eMMCTestAlignPack_t.u32_0)-(U32)&(g_eMMCTestAlignPack_t.u8_0) != 3 ||
	   (U32)&(g_eMMCTestAlignPack_t.u32_1)-(U32)&(g_eMMCTestAlignPack_t.u8_0) != 7)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: not packed. check err.0 \n");
		eMMC_die();
		return eMMC_ST_ERR_NOT_PACKED;
	}
	// check packed - 1
	if((U32)&(g_eMMCTestAlignPack_t.u16_0)-(U32)&(g_eMMCTestAlignPack_t.u8_0) != 1 ||
	   (U32)&(g_eMMCTestAlignPack_t.u32_0)-(U32)&(g_eMMCTestAlignPack_t.u16_0)!= 2 ||
	   (U32)&(g_eMMCTestAlignPack_t.u32_1)-(U32)&(g_eMMCTestAlignPack_t.u32_0)!= 4)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: not packed. check err.1 \n");
		eMMC_die();
		return eMMC_ST_ERR_NOT_PACKED;
	}

	//eMMC_debug(eMMC_DEBUG_LEVEL_HIGH, 1, "ok\n");
	return eMMC_ST_SUCCESS;
}


static __inline void dump_mem_line(unsigned char *buf, int cnt)
{
	int i;
	buf = buf;
	eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 0, " 0x%08X: ", (U32)buf);
	for (i= 0; i < cnt; i++)
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 0, "%02Xh ", buf[i]);

	eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 0, " | ");

	for (i = 0; i < cnt; i++)
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 0, "%c", (buf[i] >= 32 && buf[i] < 128) ? buf[i] : '.');

	eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 0, "\n");
}

void eMMC_dump_mem(unsigned char *buf, int cnt)
{
	int i;

	for (i= 0; i < cnt; i+= 16)
		dump_mem_line(buf + i, 16);
}


U32 eMMC_ComapreData(U8 *pu8_Buf0, U8 *pu8_Buf1, U32 u32_ByteCnt)
{
	U32 u32_i, u32_offset;

	for(u32_i=0; u32_i<u32_ByteCnt; u32_i++)
	{
		if(pu8_Buf0[u32_i] != pu8_Buf1[u32_i])
		{
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: data mismatch: i:[%Xh], Buf0: %02Xh, Buf1: %02Xh\n",
				u32_i, pu8_Buf0[u32_i], pu8_Buf1[u32_i]);
			break;
		}
	}

	if(u32_i != u32_ByteCnt && 0==(g_eMMCDrv.u32_Flag&FCIE_FLAG_DDR_TUNING))
	{
		u32_offset = (u32_i>>eMMC_SECTOR_512BYTE_BITS)<<eMMC_SECTOR_512BYTE_BITS;
		
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,0,"\ndump Buf0, from %Xh-th bytes\n", u32_offset);
        eMMC_dump_mem(pu8_Buf0+u32_offset, eMMC_SECTOR_512BYTE);
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,0,"dump Buf1, from %Xh-th bytes\n", u32_offset);
        eMMC_dump_mem(pu8_Buf1+u32_offset, eMMC_SECTOR_512BYTE);
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,0,"\n");
		return eMMC_ST_ERR_DATA_MISMATCH;
	}

	return eMMC_ST_SUCCESS;
}

U32 eMMC_ChkSum(U8 *pu8_Data, U32 u32_ByteCnt)
{
    volatile U16 u16_Tmp;
    volatile U32 u32_Sum=0;	
    for (u16_Tmp=0; u16_Tmp < u32_ByteCnt; u16_Tmp++) 
       u32_Sum += pu8_Data[u16_Tmp];	
    return (u32_Sum);
}


/* return 0: same, 1: different */
U32 eMMC_CompareCISTag(U8 *tag)
{
	const char *str = "MSTARSEMIUNFDCIS";
	int i = 0;

	for (i = 0; i < 16; i++) {
		if (tag[i] != str[i])
			return 1;
	}

	return 0;
}


U32 eMMC_PrintDeviceInfo(void)
{
	U32 u32_err;
	U8 au8_buf[eMMC_SECTOR_512BYTE];

	u32_err = eMMC_CheckIfReady();
	if(eMMC_ST_SUCCESS != u32_err)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: eMMC_Init_Ex fail: %Xh", u32_err);
		return u32_err;
	}

	// ------------------------------
	u32_err = eMMC_CMD8(au8_buf);
	if(eMMC_ST_SUCCESS != u32_err)
		return u32_err;
	eMMC_debug(eMMC_DEBUG_LEVEL, 0, "ExtCSD:\n");
    eMMC_debug(eMMC_DEBUG_LEVEL, 0, "-------------------------------\n");
    //eMMC_dump_mem(au8_buf, eMMC_SECTOR_512BYTE);
	eMMC_debug(eMMC_DEBUG_LEVEL, 0, "\n");	
	eMMC_debug(eMMC_DEBUG_LEVEL, 0, "SEC_COUNT: %Xh\n", g_eMMCDrv.u32_SEC_COUNT);
	eMMC_debug(eMMC_DEBUG_LEVEL, 0, "Capacity: %u MB\n", g_eMMCDrv.u32_SEC_COUNT>>11);
	eMMC_debug(eMMC_DEBUG_LEVEL, 0, "eMMC BUS_WIDTH: %Xh\n", g_eMMCDrv.u8_BUS_WIDTH);

	eMMC_debug(eMMC_DEBUG_LEVEL, 0, "TRIM: %Xh\n", 
		(g_eMMCDrv.u32_eMMCFlag&eMMC_FLAG_TRIM)?1:0);

	if(g_eMMCDrv.u32_eMMCFlag & (eMMC_FLAG_HPI_CMD12|eMMC_FLAG_HPI_CMD13))
		eMMC_debug(eMMC_DEBUG_LEVEL, 0, "HPI: CMD%u \n", 
		    (g_eMMCDrv.u32_eMMCFlag&eMMC_FLAG_HPI_CMD12)?12:13);
	else
		eMMC_debug(eMMC_DEBUG_LEVEL, 0, "HPI: 0 \n");

	eMMC_debug(eMMC_DEBUG_LEVEL,0,"Reliable Write BlkCnt: %Xh\n", g_eMMCDrv.u16_ReliableWBlkCnt);
	eMMC_debug(eMMC_DEBUG_LEVEL, 0, "-------------------------------\n\n");

	// ------------------------------
	#if 0
	u32_err = eMMC_CMD3_CMD7(0, 7);
		if(eMMC_ST_SUCCESS != u32_err)
			return u32_err;

	u32_err = eMMC_CMD9(g_eMMCDrv.u16_RCA);
	if(eMMC_ST_SUCCESS != u32_err)
		return u32_err;
	#endif

	eMMC_debug(eMMC_DEBUG_LEVEL, 0, "CSD:\n");
    eMMC_debug(eMMC_DEBUG_LEVEL, 0, "-------------------------------\n");
    eMMC_dump_mem(&g_eMMCDrv.au8_CSD[0], eMMC_MAX_RSP_BYTE_CNT);
	eMMC_debug(eMMC_DEBUG_LEVEL, 0, "\n");
	eMMC_debug(eMMC_DEBUG_LEVEL, 0, "SPEC_VERS: %Xh, R_BL_LEN: %Xh, W_BL_LEN: %Xh \n", 
		g_eMMCDrv.u8_SPEC_VERS, g_eMMCDrv.u8_R_BL_LEN, g_eMMCDrv.u8_W_BL_LEN);
	eMMC_debug(eMMC_DEBUG_LEVEL, 0, "Access Mode: %s\n", g_eMMCDrv.u8_IfSectorMode?"Sector":"Byte");	
	eMMC_debug(eMMC_DEBUG_LEVEL, 0, "C_SIZE: %Xh\n", g_eMMCDrv.u16_C_SIZE);	
	eMMC_debug(eMMC_DEBUG_LEVEL, 0, "ERASE_GRP_SIZE: %Xh, ERASE_GRP_MULT: %Xh\n", 
		g_eMMCDrv.u8_ERASE_GRP_SIZE, g_eMMCDrv.u8_ERASE_GRP_MULT);	
	eMMC_debug(eMMC_DEBUG_LEVEL, 0, "EraseUnitSize: %u\n", g_eMMCDrv.u32_EraseUnitSize);
	switch(g_eMMCDrv.u8_Tran_Speed)
	{
		case 0x2A:
			eMMC_debug(eMMC_DEBUG_LEVEL, 0, "default speed 20MHz\n"); break;
		case 0x32:
			eMMC_debug(eMMC_DEBUG_LEVEL, 0, "default speed 26MHz\n"); break;
		default:
			eMMC_debug(eMMC_DEBUG_LEVEL, 0, "normal TRAN_SPEED: %Xh\n", g_eMMCDrv.u8_Tran_Speed);
	}
	eMMC_debug(eMMC_DEBUG_LEVEL, 0, "TAAC: %Xh, NSAC: %Xh, R2W_FACTOR: %Xh\n", 
		g_eMMCDrv.u8_TAAC, g_eMMCDrv.u8_NSAC, g_eMMCDrv.u8_R2W_FACTOR);
    eMMC_debug(eMMC_DEBUG_LEVEL, 0, "-------------------------------\n\n");

	eMMC_debug(eMMC_DEBUG_LEVEL, 0, "CID:\n");
    eMMC_debug(eMMC_DEBUG_LEVEL, 0, "-------------------------------\n");
    eMMC_dump_mem(&g_eMMCDrv.au8_CID[0], eMMC_MAX_RSP_BYTE_CNT);
	eMMC_debug(eMMC_DEBUG_LEVEL, 0, "-------------------------------\n\n");

	#if 0
	u32_err = eMMC_CMD3_CMD7(g_eMMCDrv.u16_RCA, 7);
		if(eMMC_ST_SUCCESS != u32_err)
			return u32_err;
	#endif
	return u32_err;
}


void eMMC_dump_nni(eMMC_NNI_t *peMMCInfo)
{
#if eMMC_DEBUG_LEVEL <= eMMC_DEBUG_LEVEL_LOW
	int i;
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "###############################################\n");
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "#        eMMC NNI                             #\n");
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "###############################################\n");

	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "peMMCInfo: 0x%08X\n", (U32)peMMCInfo);
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "au8_Tag          : [");
	for (i = 0; i < 16; i++)
		eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 0, "%c", peMMCInfo->au8_Tag[i]);
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 0, "]\n");

	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "u8_IDByteCnt     : 0x%04x\n", peMMCInfo->u8_IDByteCnt);

	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "au8_ID           : 0x[ ");
	for (i = 0; i < peMMCInfo->u8_IDByteCnt; i++)
		eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 0, "%02X ", peMMCInfo->au8_ID[i]);
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 0, "]\n");

	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "u32_ChkSum       : 0x%04X\n", peMMCInfo->u32_ChkSum);
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "u16_SpareByteCnt : 0x%04x\n", peMMCInfo->u16_SpareByteCnt);
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "u16_PageByteCnt  : 0x%04x\n", peMMCInfo->u16_PageByteCnt);
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "u16_BlkPageCnt   : 0x%04x\n", peMMCInfo->u16_BlkPageCnt);
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "u16_BlkCnt       : 0x%04x\n", peMMCInfo->u16_BlkCnt);
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "u32_Config       : 0x%08X\n", peMMCInfo->u32_Config);
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "u16_ECCType      : 0x%04x\n", peMMCInfo->u16_ECCType);
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "u16_SeqAccessTime: 0x%04x\n", peMMCInfo->u16_SeqAccessTime);
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "u8_Vendor: %s\n", peMMCInfo->au8_Vendor);
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "u8_PartNumber: %s\n", peMMCInfo->au8_PartNumber);	
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "u8_PairPageMapLoc: 0x%04x\n", peMMCInfo->u8_PairPageMapLoc);
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "u8_PairPageMapType: 0x%04x\n", peMMCInfo->u8_PairPageMapType);
#endif
}

void eMMC_dump_pni(eMMC_PNI_t *pPartInfo)
{
	pPartInfo = pPartInfo;
#if eMMC_DEBUG_LEVEL <= eMMC_DEBUG_LEVEL_LOW
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "###############################################\n");
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "#        eMMC PNI                             #\n");
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "###############################################\n");

	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "pPartInfo: 0x%08X\n", (U32)pPartInfo);
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "u32_ChkSum      : 0x%04X\n", pPartInfo->u32_ChkSum);
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "u16_SpareByteCnt : 0x%04x\n", pPartInfo->u16_SpareByteCnt);
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "u16_PageByteCnt : 0x%04x\n", pPartInfo->u16_PageByteCnt);
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "u16_BlkPageCnt : 0x%04x\n", pPartInfo->u16_BlkPageCnt);
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "u16_BlkCnt : 0x%04x\n", pPartInfo->u16_BlkCnt);
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "u16_PartCnt     : 0x%04x\n", pPartInfo->u16_PartCnt);
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "u16_UnitByteCnt : 0x%04x\n", pPartInfo->u16_UnitByteCnt);

	//dump_part_records(pPartInfo->records, pPartInfo->u16_PartCnt);
#endif	
}
#endif
#endif
