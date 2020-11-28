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
#include "../../inc/common/drvNAND_device.h"
//#include "drvWDT.h"

#if (defined(FCIE_ZDEC_TEST) && FCIE_ZDEC_TEST)
#include "../drivers/zdec/mstar_zdec.h"
#include "../drivers/zdec/96_zlib_prop_1.h"
#include "../drivers/zdec/96_zlib_prop_2.h"
#include "../drivers/zdec/35827_zlib_prop_1.h"
#include "../drivers/zdec/35827_zlib_prop_2.h"
#include "../drivers/zdec/72094_zlib_prop_1.h"
#include "../drivers/zdec/72094_zlib_prop_2.h"
#include "../drivers/zdec/107474_zlib_prop_1.h"
#include "../drivers/zdec/107474_zlib_prop_2.h"
#include "../drivers/zdec/121250_zlib_prop_1.h"
#include "../drivers/zdec/121250_zlib_prop_2.h"
#include "../drivers/zdec/squashfs_test_1_96_35731_131072.h"
#include "../drivers/zdec/squashfs_test_2_35827_19864_70326.h"
#include "../drivers/zdec/squashfs_test_3_72094_29571_110762.h"
#include "../drivers/zdec/squashfs_test_4_107474_13776_72656.h"
#include "../drivers/zdec/squashfs_test_5_121250_28458_106205.h"
#endif

#if IF_IP_VERIFY
//========================================================
// exposed function
//========================================================
U32  drvNAND_IPVerify_Main(void);
U32  NCTEST_WriteImagesForROM(void);
U32  NCTEST_TestReadWriteSpeed(void);

U32  NCTEST_HWRepeatModeTest(void);
U32  NCTEST_HWECCCheckNotAllFF(U32 u32_TestRow);
U32  NCTEST_HWECCSpare640B(U32 u32_TestRow);
void NCTEST_EarseAllBlk(void);
void NCTEST_EWRCAllBlk(void);
U32  NCTEST_EraseAllGoodBlks(void);
void nand_dump_FMap(void);
void nand_LUT_Test(void);
U32  NCTEST_DataCompare(U8 *pu8_buf0, U8 *pu8_buf1, U32 u32_byteCnt);
void NCTEST_LogiWR_TestWBQ(void);
void NCTEST_LogiWR_TestFBQ(void);
void NCTEST_LogiWR_Stress(U32 u32_TotalSectorCnt);
void NCTEST_LogiWR_Once(U32 u32_StartSectorIdx, U32 u32_SectorCnt);
U32  NCTEST_DumpECCRegisters(void);
#if defined(FCIE_LFSR) && FCIE_LFSR
#if defined(FCIE_LFSR) && FCIE_LFSR
static U32 NCTEST_LFSRTest(U32 u32_PBA);
int  LFSR1_NLines_NIOs_SectorUnit(U16 au16_DatIn[], U16 au16_BufOut[], U32 u32_ByteCnt, U16 u16_Page, U8 u8_lines, U8 u8_IOs);
#endif
#endif
#if 1
#define LOGI_STRESS_TEST_SECTOR_CNT  0x136 // 8MB
#define LOGI_STRESS_TEST_SECTOR_ADR  0x4500 // 32MB
#else
#define LOGI_STRESS_TEST_SECTOR_CNT  0x101 // 8MB
#define LOGI_STRESS_TEST_SECTOR_ADR  0x10000 // 32MB
#endif
volatile U8 au8_TestBuf[LOGI_STRESS_TEST_SECTOR_CNT<<9]; // [CAUTION]

static const U8 sgau8_ID_HardCode[] = NAND_DEVICE_ID;
//static U8* const pu8_string = "abcde";

#define ECC_TEST_PATTERN             0xFF

// FIXME:
#define RTC_REG_BASE_ADDR 0

#define RTC_CTRL        GET_REG_ADDR(RTC_REG_BASE_ADDR, 0x40)
#define BIT_EN          BIT1
#define BIT_TRIGGER     BIT4
#define RTC_SECOND      GET_REG_ADDR(RTC_REG_BASE_ADDR, 0x48)

//test pattern
#define NAND_PATTERN_0000    0x0000 // smooth
#define NAND_PATTERN_FFFF    0xFFFF // smooth
#define NAND_PATTERN_00FF    0x00FF // board
#define NAND_PATTERN_FFFF    0xFFFF // board
#define NAND_PATTERN_00FF    0x00FF // board
#define NAND_PATTERN_AA55    0xAA55 // board

extern 	U8	au8_nand_clk_max;

static U32 NCTEST_RW_CIFD(void)
{
	U32 u32_Idx;
	volatile U16 u16_Reg;

	for (u32_Idx = 0; u32_Idx < NC_CIFD_BYTE_CNT >> 1; u32_Idx++)
		REG_WRITE_UINT16(NC_CIFD_ADDR(u32_Idx), (U16)(u32_Idx + (u32_Idx << 8)));

	for (u32_Idx = 0; u32_Idx < NC_CIFD_BYTE_CNT >> 1; u32_Idx++)
	{
		REG_READ_UINT16(NC_CIFD_ADDR(u32_Idx), u16_Reg);
		if (u16_Reg != (U16)(u32_Idx + (u32_Idx << 8)))
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "CIFD W/R Err: Idx: %lu, W: 0x%04x, R: 0x%04x\n",
					u32_Idx, (U16)(u32_Idx + (u32_Idx << 8)), u16_Reg);
			return UNFD_ST_ERR_NO_NFIE;
		}
	}

	return UNFD_ST_SUCCESS;
}

static U32 NCTEST_AccessCIFD(void)
{
	U16 u16_i, u16_j, u16_Tmp;
	U8 au8_W[NC_CIFD_BYTE_CNT], au8_R[NC_CIFD_BYTE_CNT];

	if (NCTEST_RW_CIFD() != UNFD_ST_SUCCESS)
		return UNFD_ST_ERR_NO_NFIE;

	for (u16_i = 0; u16_i < NC_CIFD_BYTE_CNT; u16_i++)
	{
		for (u16_j = u16_i; u16_j < NC_CIFD_BYTE_CNT; u16_j++)
		{
			au8_W[u16_j] = u16_j + 1;
			au8_R[u16_j] = ~au8_W[u16_j];
		}

		NC_SetCIFD(&au8_W[u16_i], u16_i, NC_CIFD_BYTE_CNT - u16_i);
		NC_GetCIFD(&au8_R[u16_i], u16_i, NC_CIFD_BYTE_CNT - u16_i);

		for (u16_j = u16_i; u16_j < NC_CIFD_BYTE_CNT; u16_j++)
		{
			if (au8_W[u16_j] != au8_R[u16_j])
			{
				REG_READ_UINT16(NC_CIFD_ADDR(u16_j >> 1), u16_Tmp);
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR 1: Idx_i: 0x%x  Idx_j: 0x%x  Val: 0x%x  W: 0x%x  R: 0x%x\n",
						u16_i, u16_j, u16_Tmp, au8_W[u16_j], au8_R[u16_j]);

				return UNFD_ST_ERR_NO_NFIE;
			}
		}
	}

	return UNFD_ST_SUCCESS;
}

U32 NCTEST_ReadID(void)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;
	U8 u8_Idx;

	u32_Err = NC_ReadID();
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NC_ReadID fail, ErrCode: 0x%08lx\n", u32_Err);
		return UNFD_ST_ERR_UNKNOWN_ID;
	}

	if (pNandDrv->u8_IDByteCnt != NAND_DEVICE_ID_LEN)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR! ID Byte Cnt incorrect\n");
		return UNFD_ST_ERR_UNKNOWN_ID;
	}

	nand_debug(UNFD_DEBUG_LEVEL_HIGH, 1, "ID Byte Cnt: %d\n", pNandDrv->u8_IDByteCnt);

	for (u8_Idx = 0; u8_Idx < NAND_DEVICE_ID_LEN; u8_Idx++)
	{
		if ( pNandDrv->au8_ID[u8_Idx] != sgau8_ID_HardCode[u8_Idx])
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ID[%u]: R: 0x%02x != 0x%02x\n", u8_Idx,
					pNandDrv->au8_ID[u8_Idx], sgau8_ID_HardCode[u8_Idx]);
			return UNFD_ST_ERR_UNKNOWN_ID;
		}
	}

	nand_debug(UNFD_DEBUG_LEVEL_HIGH, 1, "ReadID ok\n");

	return UNFD_ST_SUCCESS;
}

#define NCTEST_RANDOM_BYTE_CNT  0x40

static U32 NCTEST_RandomRW(void)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;
	U32 u32_PageIdx, u32_ByteIdx;
	U8  au8_W[NCTEST_RANDOM_BYTE_CNT], au8_R[NCTEST_RANDOM_BYTE_CNT];

	u32_PageIdx = pNandDrv->u16_BlkPageCnt*2;

	/* erase the first blk */
	u32_Err = NC_EraseBlk(u32_PageIdx);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RandomRW 0, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	for (u32_ByteIdx = 0; u32_ByteIdx < NCTEST_RANDOM_BYTE_CNT; u32_ByteIdx++)
	{
		au8_W[u32_ByteIdx] = 0xFF-(u32_ByteIdx + 1);
		au8_R[u32_ByteIdx] = ~au8_W[u32_ByteIdx];
	}

	u32_Err = NC_Write_RandomOut(u32_PageIdx, 2, au8_W, NCTEST_RANDOM_BYTE_CNT);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RandomRW 1, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	u32_Err = NC_Read_RandomIn(u32_PageIdx, 2, au8_R, NCTEST_RANDOM_BYTE_CNT);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RandomRW 2, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	if(NCTEST_DataCompare(au8_W, au8_R, NCTEST_RANDOM_BYTE_CNT))
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RandomRW 3 \n");
		return UNFD_ST_ERR_DATA_CMP_FAIL;
	}

	return UNFD_ST_SUCCESS;
}

static U32 NCTEST_RandomRW_MIU(void)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;
	U32 u32_PageIdx, u32_ByteIdx;
	U8  au8_W[NCTEST_RANDOM_BYTE_CNT], au8_R[NCTEST_RANDOM_BYTE_CNT];

	u32_PageIdx = pNandDrv->u16_BlkPageCnt*2;

	/* erase the first blk */
	u32_Err = NC_EraseBlk(u32_PageIdx);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RandomRW_MIU 0, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	for (u32_ByteIdx = 0; u32_ByteIdx < NCTEST_RANDOM_BYTE_CNT; u32_ByteIdx++)
	{
		au8_W[u32_ByteIdx] = 0xFF-(u32_ByteIdx + 1);
		au8_R[u32_ByteIdx] = ~au8_W[u32_ByteIdx];
	}

	u32_Err = NC_Write_RandomOut_MIU(u32_PageIdx, 2, au8_W, NCTEST_RANDOM_BYTE_CNT);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RandomRW_MIU 1, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	u32_Err = NC_Read_RandomIn_MIU(u32_PageIdx, 2, au8_R, NCTEST_RANDOM_BYTE_CNT);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RandomRW_MIU 2, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	if(NCTEST_DataCompare(au8_W, au8_R, NCTEST_RANDOM_BYTE_CNT))
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RandomRW_MIU 3 \n");
		return UNFD_ST_ERR_DATA_CMP_FAIL;
	}

	return UNFD_ST_SUCCESS;
}

U32 NCTEST_VerifyDMAAddress(void)
{
	volatile U8 *au8_W, *au8_R;
	U16 u16_i;

	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;

	for(u16_i=0; u16_i<0x100; u16_i++)
	{
		au8_W[u16_i]=u16_i;
		au8_R[u16_i]=~au8_W[u16_i];
	}
	for(u16_i=0; u16_i<0x100; u16_i++)
	{
		if(au8_W[u16_i] != u16_i || au8_R[u16_i] != (U8)~au8_W[u16_i])
			break;
	}

	if(u16_i != 0x100)
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "test DMA Addr fail: %Xh %Xh %Xh \n", 
		    u16_i, au8_W[u16_i], au8_R[u16_i]);
	
	return UNFD_ST_SUCCESS;
}

static U32 NCTEST_RWSinglePages_RM(U32 u32_StartRowIdx, U32 u32_PageCnt)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;
	U32 u32_PageIdx, u32_SectorIdx, u32_ByteIdx, u16_SpareByteCnt;
	U8  *au8_W, *au8_R;
	U8  *au8_WSpare, *au8_RSpare;

	/* erase the first blk */
    u32_Err = NC_EraseBlk(u32_StartRowIdx &~ pNandDrv->u16_BlkPageCntMask);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_RM 0, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	/* setup buffers */
	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	/* W/R/C each page */
	for (u32_PageIdx = 0; u32_PageIdx < u32_PageCnt; u32_PageIdx++)
	{
		/* erase */
		if (u32_PageIdx && !((u32_StartRowIdx + u32_PageIdx) & pNandDrv->u16_BlkPageCntMask))
		{
			u32_Err = NC_EraseBlk(u32_StartRowIdx + u32_PageIdx);
			if (u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_RM 1, ErrCode: 0x%08lx\n", u32_Err);
				return u32_Err;
			}
		}

		/* init test pattern */
		for (u32_ByteIdx = 0; u32_ByteIdx < pNandDrv->u16_PageByteCnt; u32_ByteIdx++)
		{
			if (pNandDrv->u8_IfECCTesting)
				au8_W[u32_ByteIdx] = ECC_TEST_PATTERN;
			else
				au8_W[u32_ByteIdx] = u32_ByteIdx + 1;

			au8_R[u32_ByteIdx] = ~au8_W[u32_ByteIdx];
		}

		for (u32_ByteIdx = 0; u32_ByteIdx < pNandDrv->u16_SpareByteCnt; u32_ByteIdx++)
		{
			if (pNandDrv->u8_IfECCTesting)
				au8_WSpare[u32_ByteIdx] = ECC_TEST_PATTERN;
			else
				au8_WSpare[u32_ByteIdx] = u32_ByteIdx + 1 ;

			au8_RSpare[u32_ByteIdx] = ~au8_WSpare[u32_ByteIdx];
		}

		u32_Err = NC_WritePage_RIUMode(u32_StartRowIdx + u32_PageIdx, au8_W, au8_WSpare);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_RM 2, ErrCode: 0x%08lx\n", u32_Err);
			return u32_Err;
		}

		/* read test pattern */
		for (u32_SectorIdx = 0; u32_SectorIdx < pNandDrv->u16_PageSectorCnt; u32_SectorIdx++)
		{
			u32_Err = NC_ReadSector_RIUMode(u32_StartRowIdx + u32_PageIdx, u32_SectorIdx,
					au8_R + (u32_SectorIdx << pNandDrv->u8_SectorByteCntBits),
					//au8_RSpare + (u32_SectorIdx << pNandDrv->u8_SectorSpareByteCntBits));
					au8_RSpare + (u32_SectorIdx * pNandDrv->u16_SectorSpareByteCnt));
			if (u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_RM 3, ErrCode: 0x%08lx\n", u32_Err);
				return u32_Err;
			}
		}

		/* compare test pattern */
		if(NCTEST_DataCompare(au8_W, au8_R, pNandDrv->u16_PageByteCnt))
	    {
		    nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_RM 4 \n");
		    return UNFD_ST_ERR_DATA_CMP_FAIL;
	    }

		u16_SpareByteCnt = pNandDrv->u16_SpareByteCnt;
		#if SPARE640B_CIFD512B_PATCH
		if(u16_SpareByteCnt > 0x200)
			u16_SpareByteCnt = (0x200/pNandDrv->u16_SectorSpareByteCnt)*pNandDrv->u16_SectorSpareByteCnt;
		#endif
		for (u32_ByteIdx = 0; u32_ByteIdx < u16_SpareByteCnt; u32_ByteIdx++)
		{

			if (u32_ByteIdx == pNandDrv->u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt +
					pNandDrv->u16_SectorSpareByteCnt * (u32_ByteIdx / pNandDrv->u16_SectorSpareByteCnt))
			{
				u32_ByteIdx += pNandDrv->u16_ECCCodeByteCnt - 1;
				continue;
			}

			if (au8_WSpare[u32_ByteIdx] != au8_RSpare[u32_ByteIdx])
			{
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_RM 5, Row: 0x%08lx, Col: 0x%04lx, W: 0x%02x, R: 0x%02x\n",
						u32_StartRowIdx + u32_PageIdx, u32_ByteIdx, au8_WSpare[u32_ByteIdx], au8_RSpare[u32_ByteIdx]);
				return UNFD_ST_ERR_DATA_CMP_FAIL;
			}
		}
	}

	return UNFD_ST_SUCCESS;
}


#if defined(__VER_UNFD_FTL__) && __VER_UNFD_FTL__
static void NCTEST_DumpMG(void)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err, u32_i;
	U16 u16_PBA, u16_page;

	U8  *au8_W, *au8_R;
	U8  *au8_WSpare, *au8_RSpare;

	/* setup buffers */
	au8_R = (U8*)DMA_R_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	for(u16_PBA=3; u16_PBA<8; u16_PBA++)
	{
		u16_page = 0;

		do
		{
			u32_Err = NC_ReadSectors((u16_PBA<<pNandDrv->u8_BlkPageCntBits)+u16_page,
				                   0, au8_R, au8_RSpare, 1);
		    if (u32_Err != UNFD_ST_SUCCESS)
		        nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR.1: ErrCode: 0x%08x\n", u32_Err);

            if(0xFF==au8_RSpare[0] && UNFD_FTL_BLK_ID_MG==au8_RSpare[1] &&
			  u16_page<pNandDrv->u16_BlkPageCnt)
		    {
			    nand_debug(0,0,"PBA:%X  Page:%X\n", u16_PBA, u16_page);
			    dump_mem(au8_R, pNandDrv->u16_SectorByteCnt);
			    nand_debug(0,0,"\n");
			    dump_mem(au8_RSpare, pNandDrv->u16_SectorSpareByteCnt);
            }

			u16_page++;

		}while(0xFF==au8_RSpare[0] && UNFD_FTL_BLK_ID_MG==au8_RSpare[1] &&
			  u16_page<pNandDrv->u16_BlkPageCnt);

	}

}
#endif

static U32 NCTEST_RWSinglePages(U32 u32_StartRowIdx, U32 u32_PageCnt)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;
	U32 u32_PageIdx, u32_ByteIdx;
	U16 u16_SpareByteCnt;

	U8  *au8_W, *au8_R;
	U8  *au8_WSpare, *au8_RSpare;

	/* erase the first blk */

	u32_Err = NC_EraseBlk(u32_StartRowIdx &~ pNandDrv->u16_BlkPageCntMask);

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RWSinglePages 0, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	/* setup buffers */
	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	/* W/R/C each page */
	for (u32_PageIdx = 0; u32_PageIdx < u32_PageCnt; u32_PageIdx++)
	{
		/* erase */
		if (u32_PageIdx && !((u32_StartRowIdx + u32_PageIdx) & pNandDrv->u16_BlkPageCntMask))
		{
			u32_Err = NC_EraseBlk(u32_StartRowIdx + u32_PageIdx);
			if (u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RWSinglePages 1, ErrCode: 0x%08lx\n", u32_Err);
				return u32_Err;
			}
		}

		/* init test pattern */
		for (u32_ByteIdx = 0; u32_ByteIdx < pNandDrv->u16_PageByteCnt; u32_ByteIdx++)
		{
			if (pNandDrv->u8_IfECCTesting)
				au8_W[u32_ByteIdx] = ECC_TEST_PATTERN;
			else
				au8_W[u32_ByteIdx] = u32_ByteIdx + 1;

			au8_R[u32_ByteIdx] = ~au8_W[u32_ByteIdx];
            #if 0
			if(u32_ByteIdx<0x20)
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "set: [%2u]: adr:%X val:%02X  adr:%X val:%02X\n",
				    u32_ByteIdx, &au8_W[u32_ByteIdx], au8_W[u32_ByteIdx],
				    &au8_R[u32_ByteIdx], au8_R[u32_ByteIdx]);
			#endif
		}

		for (u32_ByteIdx = 0; u32_ByteIdx < pNandDrv->u16_SpareByteCnt; u32_ByteIdx++)
		{
			if (pNandDrv->u8_IfECCTesting)
				au8_WSpare[u32_ByteIdx] = ECC_TEST_PATTERN;
			else
				au8_WSpare[u32_ByteIdx] = u32_ByteIdx + 1 ;

			au8_RSpare[u32_ByteIdx] = ~au8_WSpare[u32_ByteIdx];
		}

		u32_Err = NC_WritePages(u32_StartRowIdx + u32_PageIdx, au8_W, au8_WSpare, 1);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RWSinglePages 2, ErrCode: 0x%08lx\n", u32_Err);
			return u32_Err;
		}

		/* read test pattern */
		u32_Err = NC_ReadPages(u32_StartRowIdx + u32_PageIdx, au8_R, au8_RSpare, 1);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RWSinglePages 3, ErrCode: 0x%08lx\n", u32_Err);
			return u32_Err;
		}
		// [CAUTION]: if the above 2 of nand_translate_DMA_address_Ex, data area must be handled later.
		//nand_translate_DMA_address_Ex((U32)sgau8_RBuf, pNandDrv->u16_PageByteCnt);
		//nand_translate_DMA_address_Ex((U32)sgau8_RSpareBuf, pNandDrv->u16_PageByteCnt);

		/* compare test pattern */
		if(NCTEST_DataCompare(au8_W, au8_R, pNandDrv->u16_PageByteCnt))
	    {
		    nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RWSinglePages 4 \n");
		    return UNFD_ST_ERR_DATA_CMP_FAIL;
	    }

		u16_SpareByteCnt = pNandDrv->u16_SpareByteCnt;
		#if SPARE640B_CIFD512B_PATCH
		if(u16_SpareByteCnt > 0x200)
			u16_SpareByteCnt = (0x200/pNandDrv->u16_SectorSpareByteCnt)*pNandDrv->u16_SectorSpareByteCnt;
		#endif
		for (u32_ByteIdx = 0; u32_ByteIdx < u16_SpareByteCnt; u32_ByteIdx++)
		{
			if (u32_ByteIdx == pNandDrv->u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt +
					pNandDrv->u16_SectorSpareByteCnt * (u32_ByteIdx / pNandDrv->u16_SectorSpareByteCnt))
			{
				u32_ByteIdx += pNandDrv->u16_ECCCodeByteCnt - 1;
				continue;
			}

			if (au8_WSpare[u32_ByteIdx] != au8_RSpare[u32_ByteIdx])
			{
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RWSinglePages, spare, Row: 0x%08lx, Col: 0x%04lx, W: 0x%02x, R: 0x%02x\n",
						u32_StartRowIdx + u32_PageIdx, u32_ByteIdx, au8_WSpare[u32_ByteIdx], au8_RSpare[u32_ByteIdx]);
				return UNFD_ST_ERR_DATA_CMP_FAIL;
			}
		}
	}

	return UNFD_ST_SUCCESS;
}

// test Repeat Cnt
// (test within one blk)
U32 NCTEST_RWMultiplePages_OneTime(U32 u32_StartRowIdx, U32 u32_PageCnt)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;
	U32 u32_ByteIdx, u32_DataByteCnt, u32_SpareByteCnt;

	U32 *au32_W, *au32_R;
	U8  *au8_WSpare, *au8_RSpare;

	/* check parameters */
	#if 0
	if (((u32_StartRowIdx + u32_PageCnt) &~ pNandDrv->u16_BlkPageCntMask) !=
			(u32_StartRowIdx &~ pNandDrv->u16_BlkPageCntMask))
	#else
    if(u32_StartRowIdx + u32_PageCnt > pNandDrv->u16_BlkPageCnt +
	    ((u32_StartRowIdx>>pNandDrv->u8_BlkPageCntBits)<<pNandDrv->u8_BlkPageCntBits))
	#endif
	{
		nand_debug(0,1,"%lX %lX\n", u32_StartRowIdx, u32_PageCnt);
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 0, ErrCode: 0x%08x\n",
				UNFD_ST_ERR_INVALID_PARAM);
		return UNFD_ST_ERR_INVALID_PARAM;
	}

	/* setup buffers */
	au32_W = (U32*)DMA_W_ADDR;
	au32_R = (U32*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	u32_DataByteCnt = u32_PageCnt << pNandDrv->u8_PageByteCntBits;

	/* NOTE: when use RepeatCnt, for the Spare area is still using the first Spare size byte cnt. */
	u32_SpareByteCnt = pNandDrv->u16_SpareByteCnt;

	/* erase first blk */
	u32_Err = NC_EraseBlk(u32_StartRowIdx &~ pNandDrv->u16_BlkPageCntMask);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 0, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	/* init test pattern */
	for (u32_ByteIdx = 0; u32_ByteIdx < u32_DataByteCnt >> 2; u32_ByteIdx++)
	{
		au32_W[u32_ByteIdx] = u32_ByteIdx + 1;//0xFF ^ ((u32_ByteIdx&1)?0xFF:0x00); //u32_ByteIdx + 1;
		au32_R[u32_ByteIdx] = ~au32_W[u32_ByteIdx];
	}

	au8_WSpare[0] = 0xFF;  au8_RSpare[0] = 0;
	for (u32_ByteIdx = 1; u32_ByteIdx < u32_SpareByteCnt; u32_ByteIdx++)
	{
		au8_WSpare[u32_ByteIdx] = u32_ByteIdx + 1;//0xFF ^ ((u32_ByteIdx&1)?0xFF:0x00); //
		au8_RSpare[u32_ByteIdx] = ~au8_WSpare[u32_ByteIdx];
	}

	/* write test pattern */
	//pNandDrv->u16_Reg48_Spare &= ~BIT_NC_SPARE_DEST_MIU;
	//NC_Config();
	u32_Err = NC_WritePages(u32_StartRowIdx, (U8*)au32_W, (U8*)au8_WSpare, u32_PageCnt);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 2, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	/* read test pattern */
	//pNandDrv->u16_Reg48_Spare |= BIT_NC_SPARE_DEST_MIU;
	//NC_Config();
	u32_Err = NC_ReadPages(u32_StartRowIdx, (U8*)au32_R, (U8*)au8_RSpare, u32_PageCnt);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 3, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}
	// [CAUTION]: if the above 2 of nand_translate_DMA_address_Ex, data area must be handled later.
	//nand_translate_DMA_address_Ex((U32)sgau32_RBuf, pNandDrv->u16_PageByteCnt);
	//nand_translate_DMA_address_Ex((U32)sgau8_RSpareBuf, pNandDrv->u16_PageByteCnt);

	/* compare test pattern */
	if(NCTEST_DataCompare((U8*)au32_W, (U8*)au32_R, u32_DataByteCnt))
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 4 \n");
	    return UNFD_ST_ERR_DATA_CMP_FAIL;
	}

	#if SPARE640B_CIFD512B_PATCH
	if(u32_SpareByteCnt > 0x200)
		u32_SpareByteCnt = (0x200/pNandDrv->u16_SectorSpareByteCnt)*pNandDrv->u16_SectorSpareByteCnt;
	#endif
	for(u32_ByteIdx = 0; u32_ByteIdx < u32_SpareByteCnt; u32_ByteIdx++)
	{
		if (u32_ByteIdx == pNandDrv->u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt +
				pNandDrv->u16_SectorSpareByteCnt * (u32_ByteIdx / pNandDrv->u16_SectorSpareByteCnt))
		{
			u32_ByteIdx += pNandDrv->u16_ECCCodeByteCnt - 1;
			continue;
		}

		//if(au8_WSpare[u32_ByteIdx&pNandDrv->u16_SpareByteCntMask] != au8_RSpare[u32_ByteIdx])
		if(au8_WSpare[u32_ByteIdx] != au8_RSpare[u32_ByteIdx])
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 5\n");//, Row: 0x%08x, Col: 0x%04x, W: 0x%02x, R: 0x%02x\n",
					//u32_ByteIdx >> pNandDrv->u8_SpareByteCntBits, u32_ByteIdx & pNandDrv->u16_SpareByteCntMask,
					//au8_WSpare[u32_ByteIdx], au8_RSpare[u32_ByteIdx]);
			return UNFD_ST_ERR_DATA_CMP_FAIL;
		}
	}

	return UNFD_ST_SUCCESS;
}



static U16 sgu16_LowPage[]={0,1,2,3,6,7,10,11,14,15,18,19,22,23,26,27,30,31};
static U32 NCTEST_RWSinglePages_Partial_SWRepeat1(U32 u32_StartRowIdx)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;
	U32 u32_Row;
    //U32 u32_PageIdx;
    //U32 u32_SectorIdx;
    U32 u32_ByteIdx;
	//U16 u16_PageByteCnt, u16_SpareByteCnt, u16_PageSectorCnt;
    U16 u16_i, u16_j;

	U8  *au8_W, *au8_R;
	U8  *au8_WSpare, *au8_RSpare;
	U32 *pu32_R, *pu32_W;

	/* setup buffers */
	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;


	/* init test pattern */
	pu32_R = (U32*)au8_R;
	pu32_W = (U32*)au8_W;
	for (u32_ByteIdx = 0; u32_ByteIdx < pNandDrv->u16_PageByteCnt; u32_ByteIdx++)
	{
		pu32_W[u32_ByteIdx] = u32_ByteIdx + 1;
		pu32_R[u32_ByteIdx] = ~pu32_W[u32_ByteIdx];
	}

	pu32_R = (U32*)au8_RSpare;
	pu32_W = (U32*)au8_WSpare;
	for (u32_ByteIdx = 0; u32_ByteIdx < pNandDrv->u16_SpareByteCnt; u32_ByteIdx++)
	{
		pu32_W[u32_ByteIdx] = u32_ByteIdx + 1 ;
		pu32_R[u32_ByteIdx] = ~pu32_W[u32_ByteIdx];
	}

	u32_Row = u32_StartRowIdx & ~pNandDrv->u16_BlkPageCntMask;

	u32_Err = NC_EraseBlk(u32_Row);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat1 1, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	//NC_EnableLFSR();

    // ----------------------------------------------------
	// w,w,w,w ...  r,r,r,r ...  c,c,c,c ... loops
	for(u16_i=0; u16_i<pNandDrv->u16_PageSectorCnt; u16_i++)
	//for(u16_i=0; u16_i<6; u16_i++)
	{
		#if 1
		// write sectors
	    u32_Err = NC_WriteSectors(
		    u32_Row + sgu16_LowPage[u16_i], // change to another page
		    u16_i,
		    au8_W + (u16_i << pNandDrv->u8_SectorByteCntBits),
		    au8_WSpare + (u16_i * pNandDrv->u16_SectorSpareByteCnt),
		    1);
		#else
		u32_Err = NC_WritePages(
			u32_Row + u16_i, // change to another page
			au8_W,
			au8_WSpare,
			1);
		#endif
	    if(u32_Err != UNFD_ST_SUCCESS)
	    {
		    nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat1 2,"
				" ErrCode: 0x%08lx, index:%X \n", u32_Err, u16_i);
		    return u32_Err;
	    }
	}

	for(u16_i=0; u16_i<pNandDrv->u16_PageSectorCnt; u16_i++)
	//for(u16_i=0; u16_i<6; u16_i++)
	{
		u32_Err = NC_ReadSectors(
		    u32_Row + sgu16_LowPage[u16_i], // change to another page
		    u16_i,
		    au8_R + (u16_i << pNandDrv->u8_SectorByteCntBits),
		    au8_RSpare + (u16_i * pNandDrv->u16_SectorSpareByteCnt),
		    1);
	    if(u32_Err != UNFD_ST_SUCCESS)
	    {
		    nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat1 3,"
				" ErrCode: 0x%08lx, index:%X \n", u32_Err, u16_i);
		    return u32_Err;
	    }
	}

	for(u16_i=0; u16_i<pNandDrv->u16_PageSectorCnt; u16_i++)
	//for(u16_i=0; u16_i<6; u16_i++)
	{
		u32_Err = NCTEST_DataCompare(
			au8_W + (u16_i << pNandDrv->u8_SectorByteCntBits),
			au8_R + (u16_i << pNandDrv->u8_SectorByteCntBits),
			pNandDrv->u16_SectorByteCnt);
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat1 4,"
				" data mismatch, index:%X \n", u16_i);
		    return u32_Err;
		}
	}
	for(u16_i=0; u16_i<pNandDrv->u16_PageSectorCnt; u16_i++)
	{
		#if SPARE640B_CIFD512B_PATCH
		if((u16_i+1) * pNandDrv->u16_SectorSpareByteCnt > 0x200)
			break;
		#endif
		u32_Err = NCTEST_DataCompare(
			au8_WSpare + (u16_i * pNandDrv->u16_SectorSpareByteCnt),
			au8_RSpare + (u16_i * pNandDrv->u16_SectorSpareByteCnt),
			pNandDrv->u16_SectorSpareByteCnt-pNandDrv->u16_ECCCodeByteCnt);
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat1 5,"
				" spare mismatch, index:%X \n", u16_i);
		    return u32_Err;
		}
	}

    // ----------------------------------------------------
	// w, r, c ... loops
	for(u16_j=0; u16_j<pNandDrv->u16_PageSectorCnt; u16_j++)
	{
		// write sectors
	    u32_Err = NC_WriteSectors(
		    u32_Row + sgu16_LowPage[u16_j+u16_i], // change to another page
		    u16_j,
		    au8_W + (u16_j << pNandDrv->u8_SectorByteCntBits),
		    au8_WSpare + (u16_j * pNandDrv->u16_SectorSpareByteCnt),
		    1);
	    if(u32_Err != UNFD_ST_SUCCESS)
	    {
		    nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat1 6,"
				" ErrCode: 0x%08lx, index:%X \n", u32_Err, u16_j);
		    return u32_Err;
	    }

		// read sectors
	    u32_Err = NC_ReadSectors(
		    u32_Row + sgu16_LowPage[u16_j+u16_i], // change to another page
		    u16_j,
		    au8_R + (u16_j << pNandDrv->u8_SectorByteCntBits),
		    au8_RSpare + (u16_j * pNandDrv->u16_SectorSpareByteCnt),
		    1);
	    if(u32_Err != UNFD_ST_SUCCESS)
	    {
		    nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat1 7,"
				" ErrCode: 0x%08lx, index:%X \n", u32_Err, u16_j);
		    return u32_Err;
	    }

		u32_Err = NCTEST_DataCompare(
			au8_W + (u16_j << pNandDrv->u8_SectorByteCntBits),
			au8_R + (u16_j << pNandDrv->u8_SectorByteCntBits),
			pNandDrv->u16_SectorByteCnt);
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat1 8,"
				" data mismatch, index:%X \n", u16_j);
		    return u32_Err;
		}

		if(u16_j * pNandDrv->u16_SectorSpareByteCnt < 0x200)
		{
		u32_Err = NCTEST_DataCompare(
			au8_WSpare + (u16_j * pNandDrv->u16_SectorSpareByteCnt),
			au8_RSpare + (u16_j * pNandDrv->u16_SectorSpareByteCnt),
			pNandDrv->u16_SectorSpareByteCnt-pNandDrv->u16_ECCCodeByteCnt);
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat1 9,"
				" spare mismatch, index:%X \n", u16_j);
		    return u32_Err;
		}}
	}

	return UNFD_ST_SUCCESS;
}


static U32 NCTEST_RWSinglePages_Partial_SWRepeat2(U32 u32_StartRowIdx, U32 u32_PageCnt)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;
	U32 u32_PageIdx, u32_SectorIdx,	u32_ByteIdx;
	U16 u16_PageByteCnt, u16_SpareByteCnt, u16_PageSectorCnt;

	U8  *au8_W, *au8_R;
	U8  *au8_WSpare, *au8_RSpare;
	U32 *pu32_R, *pu32_W;

	/* erase the first blk */
	u32_Err = NC_EraseBlk(u32_StartRowIdx &~ pNandDrv->u16_BlkPageCntMask);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat2 0, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	/* setup buffers */
	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	u16_PageByteCnt = pNandDrv->u16_PageByteCnt;
	u16_SpareByteCnt = pNandDrv->u16_SpareByteCnt;
	u16_PageSectorCnt = pNandDrv->u16_PageSectorCnt;

	/* W/R/C each page */
	for (u32_PageIdx = 0; u32_PageIdx < u32_PageCnt; u32_PageIdx++)
	{
		/* erase */
		if (u32_PageIdx && !((u32_StartRowIdx + u32_PageIdx) & pNandDrv->u16_BlkPageCntMask))
		{
			u32_Err = NC_EraseBlk(u32_StartRowIdx + u32_PageIdx);
			if (u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat2 1, ErrCode: 0x%08lx\n", u32_Err);
				return u32_Err;
			}
		}

		/* init test pattern */
		pu32_R = (U32*)au8_R;
		pu32_W = (U32*)au8_W;
		for (u32_ByteIdx = 0; u32_ByteIdx < u16_PageByteCnt; u32_ByteIdx++)
		{
			pu32_W[u32_ByteIdx] = u32_ByteIdx + 1;
			pu32_R[u32_ByteIdx] = ~pu32_W[u32_ByteIdx];
		}

		pu32_R = (U32*)au8_RSpare;
		pu32_W = (U32*)au8_WSpare;
		for (u32_ByteIdx = 0; u32_ByteIdx < u16_SpareByteCnt; u32_ByteIdx++)
		{
			pu32_W[u32_ByteIdx] = u32_ByteIdx + 1 ;
			pu32_R[u32_ByteIdx] = ~pu32_W[u32_ByteIdx];
		}

		/* write test pattern */
		#if 1// defined(FCIE4_DDR) && FCIE4_DDR
        	u32_Err = NC_WritePages(u32_StartRowIdx + u32_PageIdx, au8_W, au8_WSpare, 1);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat2 2, ErrCode: 0x%08lx\n", u32_Err);
			return u32_Err;
		}
		#else
		for (u32_SectorIdx = 0; u32_SectorIdx < u16_PageSectorCnt; u32_SectorIdx++)
		{
			u32_Err = NC_WriteSectors(u32_StartRowIdx + u32_PageIdx, u32_SectorIdx,
					au8_W + (u32_SectorIdx << pNandDrv->u8_SectorByteCntBits),
					au8_WSpare + (u32_SectorIdx * pNandDrv->u16_SectorSpareByteCnt), 1);
			if (u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat2 2, ErrCode: 0x%08lx\n", u32_Err);
				return u32_Err;
			}
		}
		#endif

		/* read test pattern */
		if (u32_PageIdx == 1)
		{
			for (u32_SectorIdx = 0; u32_SectorIdx < u16_PageSectorCnt; u32_SectorIdx++)
			{
				u32_Err = NC_ReadSectors(u32_StartRowIdx + u32_PageIdx, u32_SectorIdx,
						au8_R + (u32_SectorIdx << pNandDrv->u8_SectorByteCntBits),
						au8_RSpare + (u32_SectorIdx * pNandDrv->u16_SectorSpareByteCnt), 1);
				if (u32_Err != UNFD_ST_SUCCESS)
				{
					nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat2 3.0, ErrCode: 0x%08lx\n", u32_Err);
					return u32_Err;
				}
			}
		}
		else if (u32_PageIdx == 0)
		{
			u32_SectorIdx = 0;
			u32_Err = NC_ReadSectors(u32_StartRowIdx + u32_PageIdx, u32_SectorIdx,
					au8_R + (u32_SectorIdx << pNandDrv->u8_SectorByteCntBits),
					au8_RSpare + (u32_SectorIdx * pNandDrv->u16_SectorSpareByteCnt), 1);
			if (u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat2 3.1, ErrCode: 0x%08lx\n", u32_Err);
				return u32_Err;
			}

			u32_SectorIdx += 1;
			if (u32_SectorIdx < u16_PageSectorCnt)
			{
				u32_Err = NC_ReadSectors(u32_StartRowIdx + u32_PageIdx, u32_SectorIdx,
						au8_R + (u32_SectorIdx << pNandDrv->u8_SectorByteCntBits),
						//au8_RSpare + (u32_SectorIdx << pNandDrv->u8_SectorSpareByteCntBits), 2);
						au8_RSpare + (u32_SectorIdx * pNandDrv->u16_SectorSpareByteCnt), 2);
				if (u32_Err != UNFD_ST_SUCCESS)
				{
					nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat2 3.2, ErrCode: 0x%08lx\n", u32_Err);
					return u32_Err;
				}
			}

			u32_SectorIdx += 2;
			if (u32_SectorIdx < u16_PageSectorCnt)
			{
				u32_Err = NC_ReadSectors(u32_StartRowIdx + u32_PageIdx, u32_SectorIdx,
						au8_R + (u32_SectorIdx << pNandDrv->u8_SectorByteCntBits),
						//au8_RSpare + (u32_SectorIdx << pNandDrv->u8_SectorSpareByteCntBits),
						au8_RSpare + (u32_SectorIdx * pNandDrv->u16_SectorSpareByteCnt),
						u16_PageSectorCnt - u32_SectorIdx);
				if (u32_Err != UNFD_ST_SUCCESS)
				{
					nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat2 3.3, ErrCode: 0x%08lx\n", u32_Err);
					return u32_Err;
				}
			}

			//NC_WritePages(u32_StartRowIdx + u32_PageIdx, au8_R, au8_RSpare, 1);
		}
		else
		{
			u32_SectorIdx = 0;
			u32_Err = NC_ReadSectors(u32_StartRowIdx + u32_PageIdx, u32_SectorIdx,
					au8_R + (u32_SectorIdx << pNandDrv->u8_SectorByteCntBits),
					au8_RSpare + (u32_SectorIdx * pNandDrv->u16_SectorSpareByteCnt),
					u16_PageSectorCnt);
			if (u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat2 3.4, ErrCode: 0x%08lx\n", u32_Err);
				return u32_Err;
			}
		}

		u32_Err = NCTEST_DataCompare(au8_W, au8_R, u16_PageByteCnt);
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat2 4\n");
		    return u32_Err;
		}

		#if SPARE640B_CIFD512B_PATCH
		if(u16_SpareByteCnt > 0x200)
			u16_SpareByteCnt = (0x200/pNandDrv->u16_SectorSpareByteCnt)*pNandDrv->u16_SectorSpareByteCnt;
		#endif
		for(u32_ByteIdx = 0; u32_ByteIdx < u16_SpareByteCnt; u32_ByteIdx++)
		{
			if (u32_ByteIdx == pNandDrv->u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt +
					pNandDrv->u16_SectorSpareByteCnt * (u32_ByteIdx / pNandDrv->u16_SectorSpareByteCnt))
			{
				u32_ByteIdx += pNandDrv->u16_ECCCodeByteCnt - 1;
				continue;
			}

			if (au8_WSpare[u32_ByteIdx] != au8_RSpare[u32_ByteIdx])
			{
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat2 5, Row:%08lX, Col:%04lX, W: %02X, R: %02X \n",
						u32_StartRowIdx + u32_PageIdx, u32_ByteIdx, au8_WSpare[u32_ByteIdx], au8_RSpare[u32_ByteIdx]);
				return UNFD_ST_ERR_DATA_CMP_FAIL;
			}
		}
	}

	return UNFD_ST_SUCCESS;
}

#if 1
static U32 NCTEST_DumpBadBlk(U8 *pu8_BadBlkBitmap)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_BlkIdx = 0;

	nand_debug(UNFD_DEBUG_LEVEL_HIGH, 1, "Dump BadBlk Bitmap\n");
	nand_debug(UNFD_DEBUG_LEVEL_HIGH, 1, "===================================\n");
	for (u32_BlkIdx = 0; u32_BlkIdx < pNandDrv->u16_BlkCnt >> 3; u32_BlkIdx++)
	{
		if (!(u32_BlkIdx & 0xF))
			nand_debug(UNFD_DEBUG_LEVEL_HIGH, 0, "\n");

		nand_debug(UNFD_DEBUG_LEVEL_HIGH, 0, "%02x ", pu8_BadBlkBitmap[u32_BlkIdx]);
	}

	nand_debug(UNFD_DEBUG_LEVEL_HIGH, 0, "\n");
	nand_debug(UNFD_DEBUG_LEVEL_HIGH, 1, "===================================\n");
	return UNFD_ST_SUCCESS;
}
#endif

#if 1
static int NCTEST_Zerobits_In_Byte(U8 u8_Byte)
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
#endif

#if 1
static U32 NCTEST_MLCScanBadBlk(U8 *pu8_BadBlkBitmap)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;
	U8  *au8_R, *au8_RSpare,au8_retry;
	U32 u32_PageIdx, u32_BlkIdx;
	U16 u16_BadBlkCnt = 0, u16_i, u16_j, u16_RegVal;
    int ECCErrBitCnt ,false_alarm;

	memset(pu8_BadBlkBitmap, 0xFF, pNandDrv->u16_BlkCnt >> 3);

	au8_R = (U8*)DMA_R_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	for (u32_BlkIdx = 10; u32_BlkIdx < pNandDrv->u16_BlkCnt; u32_BlkIdx++)
	{
	    au8_retry=0;
		u32_PageIdx = u32_BlkIdx << pNandDrv->u8_BlkPageCntBits;
        nand_redo_read_first:
		u32_Err = NC_ReadPages(u32_PageIdx, au8_R, au8_RSpare, 1);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
    		if (u32_Err == UNFD_ST_ERR_ECC_FAIL)
    		{
                false_alarm = 1;
                for(u16_i=0;u16_i< pNandDrv->u16_PageSectorCnt;u16_i++)
                {
                    ECCErrBitCnt =0;
                    for(u16_j=0;u16_j< pNandDrv->u16_SectorByteCnt;u16_j++)
                    {
    					ECCErrBitCnt += NCTEST_Zerobits_In_Byte(au8_R[u16_i*pNandDrv->u16_SectorByteCnt+u16_j]);
                    }

    				if(ECCErrBitCnt > pNandDrv->u16_ECCCorretableBit)
    				{
    					false_alarm  = 0;
    					break;
                	}

                    for(u16_j=0;u16_j< pNandDrv->u16_SectorSpareByteCnt;u16_j++)
                    {
    					ECCErrBitCnt += NCTEST_Zerobits_In_Byte(au8_RSpare[u16_i*pNandDrv->u16_SectorSpareByteCnt+u16_j]);
                    }

    				if(ECCErrBitCnt > pNandDrv->u16_ECCCorretableBit)
    				{
    					false_alarm  = 0;
    					break;
                	}
                }
    			if (false_alarm ==0)
    			{
    			    if(au8_retry ==0)
    			    {
                        au8_retry++;
						REG_READ_UINT16(NC_LFSR_CTRL, u16_RegVal);

	                    if(0 == (u16_RegVal & BIT_LFSR_ENABLE))
	                    {
							NC_EnableLFSR();
	                    }
						else
						{
							NC_DisableLFSR();
						}
						goto nand_redo_read_first;
    			    }
					else
					{
        				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR:NCTEST_ScanBadBlk 1, ErrCode: 0x%08lx\n", u32_Err);
        				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "bad blk : 0x%04lx\n", u32_BlkIdx);
                        u16_BadBlkCnt++;
        				pu8_BadBlkBitmap[u32_BlkIdx >> 3] &= ~(1 << (u32_BlkIdx & 0x7));
        			    continue;
					}
    			}
    		}
    		else
    		{
    			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR:NCTEST_ScanBadBlk 1, ErrCode: 0x%08lx\n", u32_Err);
    			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "bad blk : 0x%04lx\n", u32_BlkIdx);
    			u16_BadBlkCnt++;
    			pu8_BadBlkBitmap[u32_BlkIdx >> 3] &= ~(1 << (u32_BlkIdx & 0x7));
    			continue;
    		}
		}

		if (au8_RSpare[0] != 0xFF)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "bad blk +: 0x%04lx\n", u32_BlkIdx);
			u16_BadBlkCnt++;
			pu8_BadBlkBitmap[u32_BlkIdx >> 3] &= ~(1 << (u32_BlkIdx & 0x7));
			continue;
		}

		au8_retry=0;
		u32_PageIdx += pNandDrv->u16_BlkPageCnt - 1;

		u32_Err = NC_ReadPages(u32_PageIdx,	au8_R, au8_RSpare, 1);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
    		if (u32_Err == UNFD_ST_ERR_ECC_FAIL)
    		{
                false_alarm = 1;
                for(u16_i=0;u16_i< pNandDrv->u16_PageSectorCnt;u16_i++)
                {
                    ECCErrBitCnt =0;
                    for(u16_j=0;u16_j< pNandDrv->u16_SectorByteCnt;u16_j++)
                    {
    					ECCErrBitCnt += NCTEST_Zerobits_In_Byte(au8_R[u16_i*pNandDrv->u16_SectorByteCnt+u16_j]);
                    }

    				if(ECCErrBitCnt > pNandDrv->u16_ECCCorretableBit)
    				{
    					false_alarm  = 0;
    					break;
                	}

                    for(u16_j=0;u16_j< pNandDrv->u16_SectorSpareByteCnt;u16_j++)
                    {
    					ECCErrBitCnt += NCTEST_Zerobits_In_Byte(au8_RSpare[u16_i*pNandDrv->u16_SectorSpareByteCnt+u16_j]);
                    }

    				if(ECCErrBitCnt > pNandDrv->u16_ECCCorretableBit)
    				{
    					false_alarm  = 0;
    					break;
                	}
                }
    			if (false_alarm ==0)
    			{
     			    if(au8_retry ==0)
    			    {
                        au8_retry++;
						REG_READ_UINT16(NC_LFSR_CTRL, u16_RegVal);

	                    if(0 == (u16_RegVal & BIT_LFSR_ENABLE))
	                    {
							NC_EnableLFSR();
	                    }
						else
						{
							NC_DisableLFSR();
						}
						goto nand_redo_read_first;
    			    }
					else
					{
        				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR:NCTEST_ScanBadBlk 1, ErrCode: 0x%08lx\n", u32_Err);
        				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "bad blk : 0x%04lx\n", u32_BlkIdx);
                        u16_BadBlkCnt++;
        				pu8_BadBlkBitmap[u32_BlkIdx >> 3] &= ~(1 << (u32_BlkIdx & 0x7));
        			    continue;
					}
    			}

    		}
    		else
    		{
    			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR:NCTEST_ScanBadBlk 1, ErrCode: 0x%08lx\n", u32_Err);
    			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "bad blk : 0x%04lx\n", u32_BlkIdx);
    			u16_BadBlkCnt++;
    			pu8_BadBlkBitmap[u32_BlkIdx >> 3] &= ~(1 << (u32_BlkIdx & 0x7));
    			continue;
    		}
		}
		if (au8_RSpare[0] != 0xFF)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "bad blk -: 0x%04lx\n", u32_BlkIdx);
			u16_BadBlkCnt++;
			pu8_BadBlkBitmap[u32_BlkIdx >> 3] &= ~(1 << u32_BlkIdx & 0x7);
			continue;
		}
	}

	nand_debug(UNFD_DEBUG_LEVEL_HIGH, 1, "\n Total Bad Blk Cnt: 0x%04x\n", u16_BadBlkCnt);

	NCTEST_DumpBadBlk(pu8_BadBlkBitmap);

	return UNFD_ST_SUCCESS;
}
#endif

static U32 NCTEST_RWMultiplePages_Partial_HWRepeat(U32 u32_StartRowIdx, U32 u32_PageCnt)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;
	U32 u32_ByteIdx;
	U32 *au32_W, *au32_R;
	U8  *au8_WSpare, *au8_RSpare;
	U32 u32_DataByteCnt, u32_SpareByteCnt;

	/* check parameters */ // can not excess more than one blk
	if(u32_StartRowIdx + u32_PageCnt > pNandDrv->u16_BlkPageCnt +
	    ((u32_StartRowIdx>>pNandDrv->u8_BlkPageCntBits)<<pNandDrv->u8_BlkPageCntBits))
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime_Partial 0, ErrCode: 0x%08x\n",
				UNFD_ST_ERR_INVALID_PARAM);
		return UNFD_ST_ERR_INVALID_PARAM;
	}

	/* setup buffers */
	au32_W = (U32*)DMA_W_ADDR;
	au32_R = (U32*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	u32_DataByteCnt = u32_PageCnt << pNandDrv->u8_PageByteCntBits;

	/* NOTE: when use RepeatCnt, for the Spare area is still using the first Spare size byte cnt. */
	u32_SpareByteCnt = pNandDrv->u16_SpareByteCnt;

	/* erase the first blk */
	u32_Err = NC_EraseBlk(u32_StartRowIdx &~ pNandDrv->u16_BlkPageCntMask);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime_Partial 1, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	/* init test pattern */
	for (u32_ByteIdx = 0; u32_ByteIdx < u32_DataByteCnt >> 2; u32_ByteIdx++)
	{
		au32_W[u32_ByteIdx] = u32_ByteIdx + 1;
		au32_R[u32_ByteIdx] = ~au32_W[u32_ByteIdx];
	}

	for (u32_ByteIdx = 0; u32_ByteIdx < u32_SpareByteCnt; u32_ByteIdx++)
	{
		au8_WSpare[u32_ByteIdx] = u32_ByteIdx + 1 ;
		au8_RSpare[u32_ByteIdx] = ~au8_WSpare[u32_ByteIdx];
	}

	/* write test pattern */
	u32_Err = NC_WritePages(u32_StartRowIdx, (U8*)au32_W, au8_WSpare, u32_PageCnt);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime_Partial 2, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	/* read test pattern */
	u32_Err = NC_ReadSectors(u32_StartRowIdx, 0, (U8*)au32_R, au8_RSpare,
			(u32_PageCnt << pNandDrv->u8_PageSectorCntBits) - 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime_Partial 3.0, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	u32_Err = NC_ReadSectors(
        u32_StartRowIdx + u32_PageCnt - 1,
        pNandDrv->u16_PageSectorCnt - 1,
		(U8*)au32_R + (((u32_PageCnt << pNandDrv->u8_PageSectorCntBits) - 1) << pNandDrv->u8_SectorByteCntBits),
		au8_RSpare + pNandDrv->u16_SectorSpareByteCnt * (pNandDrv->u16_PageSectorCnt - 1),
		1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime_Partial 3.1, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	// compare
	u32_Err = NCTEST_DataCompare((U8*)au32_W, (U8*)au32_R, u32_DataByteCnt);
	if(u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime_Partial 4\n");
	    return u32_Err;
	}
    #if SPARE640B_CIFD512B_PATCH
	if(u32_SpareByteCnt > 0x200)
		u32_SpareByteCnt = (0x200/pNandDrv->u16_SectorSpareByteCnt)*pNandDrv->u16_SectorSpareByteCnt;
	#endif
	for (u32_ByteIdx = 0; u32_ByteIdx < u32_SpareByteCnt; u32_ByteIdx++)
	{
		if (u32_ByteIdx == pNandDrv->u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt +
				pNandDrv->u16_SectorSpareByteCnt * (u32_ByteIdx / pNandDrv->u16_SectorSpareByteCnt))
		{
			u32_ByteIdx += pNandDrv->u16_ECCCodeByteCnt - 1;
			continue;
		}

		if(au8_WSpare[u32_ByteIdx] != au8_RSpare[u32_ByteIdx])
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime_Partial 5, W: %02X, R: %02X \n",
				au8_WSpare[u32_ByteIdx],
				au8_RSpare[u32_ByteIdx]);
			return UNFD_ST_ERR_DATA_CMP_FAIL;
		}
	}

	return UNFD_ST_SUCCESS;
}

static U32 NCTEST_PageCopy(void)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;

	U32 u32_SrcTestRow, u32_DstTestRow;
	U16 u16_SpareByteCnt;
	U32 u32_ByteIdx;
	U8 *au8_W, *au8_R;
	U8  *au8_WSpare, *au8_RSpare;

	/* setup buffers */
	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	/* Copy 5th block 3rd page to 1st block 2nd page */
	u32_SrcTestRow = 3 + (5 << pNandDrv->u8_BlkPageCntBits);
	u32_DstTestRow = 2 + (1 << pNandDrv->u8_BlkPageCntBits);

	/* init test pattern */
	for (u32_ByteIdx = 0; u32_ByteIdx < pNandDrv->u16_PageByteCnt; u32_ByteIdx++) {
		au8_W[u32_ByteIdx] = u32_ByteIdx + 1;
		au8_R[u32_ByteIdx] = ~au8_W[u32_ByteIdx];
	}

	for (u32_ByteIdx = 0; u32_ByteIdx < pNandDrv->u16_SpareByteCnt; u32_ByteIdx++) {
		au8_WSpare[u32_ByteIdx] = u32_ByteIdx + 1 ;
		au8_RSpare[u32_ByteIdx] = ~au8_WSpare[u32_ByteIdx];
	}

	u32_Err = NC_EraseBlk(5 << pNandDrv->u8_BlkPageCntBits);

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_PageCopy 0, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	u32_Err = NC_EraseBlk(1 << pNandDrv->u8_BlkPageCntBits);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_PageCopy 1, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	u32_Err = NC_WritePages(u32_SrcTestRow, au8_W, au8_WSpare, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_PageCopy 2, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	u32_Err = NC_PageCopy(u32_SrcTestRow, u32_DstTestRow, (U8*)au8_W, au8_WSpare, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_PageCopy 2, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	u32_Err = NC_ReadPages(u32_DstTestRow, au8_R, au8_RSpare, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_PageCopy 3, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	if(NCTEST_DataCompare(au8_W, au8_R, pNandDrv->u16_PageByteCnt))
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR, NCTEST_PageCopy 4 \n");
		return UNFD_ST_ERR_DATA_CMP_FAIL;
	}

	u16_SpareByteCnt = pNandDrv->u16_SpareByteCnt;
	#if SPARE640B_CIFD512B_PATCH
	if(u16_SpareByteCnt > 0x200)
		u16_SpareByteCnt = (0x200/pNandDrv->u16_SectorSpareByteCnt)*pNandDrv->u16_SectorSpareByteCnt;
	#endif
	for (u32_ByteIdx = 0; u32_ByteIdx < u16_SpareByteCnt; u32_ByteIdx++)
	{
		//if(au8_WSpare[u32_ByteIdx&pNandDrv->u16_SpareByteCntMask] != au8_RSpare[u32_ByteIdx])
		if(au8_WSpare[u32_ByteIdx] != au8_RSpare[u32_ByteIdx])
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_PageCopy 5, ByteIdx: 0x%08lx, W: 0x%02x, R: 0x%02x\n",
					u32_ByteIdx, au8_WSpare[u32_ByteIdx], au8_RSpare[u32_ByteIdx]);
			return UNFD_ST_ERR_DATA_CMP_FAIL;
		}
	}
	return UNFD_ST_SUCCESS;
}

static U32 NCTEST_ECC_For_All_0xFF_Pages(U32 u32_TestRow)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;

	U8 *au8_R;
	U8 *au8_RSpare;

	/* setup buffers */
	au8_R = (U8*)DMA_R_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	u32_Err = NC_EraseBlk(u32_TestRow);

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_ECC_For_All_0xFF_Pages 0, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	u32_Err = NC_ReadPages(u32_TestRow, au8_R, au8_RSpare, 1);

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_ECC_For_All_0xFF_Pages 1, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	u32_Err = NC_WritePages(u32_TestRow, au8_R, au8_RSpare, 1);

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_ECC_For_All_0xFF_Pages 2, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	pNandDrv->u16_Reg50_EccCtrl |= BIT_NC_ALL0xFF_ECC_CHECK;
	NC_Config();

	u32_Err = NC_ReadPages(u32_TestRow, au8_R, au8_RSpare, 1);

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_ECC_For_All_0xFF_Pages 3, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	/* Expected UNFD_ST_ERR_ECC_FAIL, not UNFD_ST_SUCCESS */
	nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "expect to get ECC error\n");
	u32_Err = NC_ReadPages(u32_TestRow+1, au8_R, au8_RSpare, 1);

	if (u32_Err != UNFD_ST_ERR_ECC_FAIL)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_ECC_For_All_0xFF_Pages 4, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	pNandDrv->u16_Reg50_EccCtrl &= ~BIT_NC_ALL0xFF_ECC_CHECK;
	NC_Config();

	u32_Err = NC_ReadPages(u32_TestRow+1, au8_R, au8_RSpare, 1);

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_ECC_For_All_0xFF_Pages 5, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	return UNFD_ST_SUCCESS;
}

static U32 NCTEST_ECC_Generation_Bypass(U32 u32_TestRow)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;

	U32 u32_ByteIdx;
	U8 *au8_R;
	U8 *au8_RSpare;

	/* setup buffers */
	au8_R = (U8*)DMA_R_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	for (u32_ByteIdx = 0; u32_ByteIdx < pNandDrv->u16_PageByteCnt; u32_ByteIdx++)
		au8_R[u32_ByteIdx] = u32_ByteIdx + 1;

	for (u32_ByteIdx = 0; u32_ByteIdx < pNandDrv->u16_SpareByteCnt; u32_ByteIdx++)
		au8_RSpare[u32_ByteIdx] = u32_ByteIdx + 1;

	u32_Err = NC_EraseBlk(u32_TestRow);

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_ECC_Generation_Bypass 0, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	u32_Err = NC_WritePages(u32_TestRow, au8_R, au8_RSpare, 1);

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_ECC_Generation_Bypass 1, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	pNandDrv->u16_Reg50_EccCtrl |= BIT_NC_BYPASS_ECC;
	NC_Config();

	u32_Err = NC_WritePages(u32_TestRow+1, au8_R, au8_RSpare, 1);

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_ECC_Generation_Bypass 2, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	pNandDrv->u16_Reg50_EccCtrl &= ~BIT_NC_BYPASS_ECC;
	NC_Config();

    u32_Err = NC_ReadPages(u32_TestRow, au8_R, au8_RSpare, 1);

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_ECC_Generation_Bypass 3, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	/* Expected UNFD_ST_ERR_ECC_FAIL, not UNFD_ST_SUCCESS */
	nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "expect to get ECC error\n");

	u32_Err = NC_ReadPages(u32_TestRow+1, au8_R, au8_RSpare, 1);

	if (u32_Err != UNFD_ST_ERR_ECC_FAIL)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_ECC_Generation_Bypass 4, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	pNandDrv->u16_Reg50_EccCtrl |= BIT_NC_BYPASS_ECC;
	NC_Config();

	u32_Err = NC_ReadPages(u32_TestRow+1, au8_R, au8_RSpare, 1);

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_ECC_Generation_Bypass 5, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	pNandDrv->u16_Reg50_EccCtrl &= ~BIT_NC_BYPASS_ECC;
	NC_Config();

	return UNFD_ST_SUCCESS;
}


//volatile struct fcie_ctrl_struct *fcie = (struct fcie_ctrl_struct*)FCIE_REG_BASE_ADDR;
#if defined(NC_SEL_FCIE3) && NC_SEL_FCIE3
static U32 NCTEST_PowerSave(void)
{
  #if defined(FCIE_POWER_SAVE_MODE) && FCIE_POWER_SAVE_MODE
	U16 u16_Reg;
	/*
	 * Enable Power Save HW and use RIU interface to test power save function
	 */
    #if 0
    // [CAUTION]: have to reset at first.
    //REG_CLR_BITS_UINT16(NC_PWRSAVE_CTL, BIT_SD_POWER_SAVE_RST);

	REG_WRITE_UINT16(NC_PWRSAVE_CTL,
	    BIT_POWER_SAVE_MOUE | BIT_POWER_SAVE_MODE_INT_EN | BIT_SD_POWER_SAVE_RST);
    #endif
	/*
	 * Write script file to Power_Save_FIFO
	 */

	/* (1) Clear HW Enable */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x40), 0x0000);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x41),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x0A);

	/* (2) Clear All Interrupt */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x42), 0xffff);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x43),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x00);

	/* (3) Clear SDE MODE Enable */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x44), 0x0000);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x45),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x10);

	/* (4) Clear SDE CTL Enable */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x46), 0x0000);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x47),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x11);

	/* (5) Reset Start */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x48), 0x4800);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x49),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x30);

	/* (6) Reset End */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x4A), 0x5800);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x4B),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x30);

	/* (7) Set "SD_MOD" */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x4C), 0x0053);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x4D),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x10);

	/* (8) Enable "csreg_sd_en" */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x4E), 0x0002);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x4F),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x0A);

	/* (9) Command Content, STOP */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x50), 0x004C);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x51),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK1 | 0x00);

	/* (10) Command Content, STOP */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x52), 0x0000);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x53),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK1 | 0x01);

	/* (11) Command Content, STOP */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x54), 0x0000);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x55),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK1 | 0x02);

	/* (12) Command Size */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x56), 0x0005);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x57),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x0E);

	/* (13) Response Size */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x58), 0x0005);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x59),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x0D);

	/* (14) Enable Interrupt, SD_CMD_END, NC_JOB_END */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x5A), 0x0202);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x5B),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x01);

	/* (15) Command Enable */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x5C), 0x0006);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x5D),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x11);

	/* (16) Wait Interrupt */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x5E), 0x0000);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x5F),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WINT);

	/* (17) Clear Interrupt */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x60), 0x0002);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x61),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x00);

	/* (18) Command Content, IDLE */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x62), 0x0040);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x63),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK1 | 0x00);

	/* (19) Command Enable */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x64), 0x0004);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x65),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x11);

	/* (20) Wait Interrupt */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x66), 0x0000);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x67),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WINT);

	/* (21) Clear Interrupt */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x68), 0x0002);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x69),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x00);

	/* (22) Enable "csreg_nc_en */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x6A), 0x0020);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x6B),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x0A);

	/* (23) Enable "ce_en, ce_auto, wp_en, wp_auto" */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x6C), 0x003C);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x6D),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x40);

	/* (24) RESET Command queue */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x6E), 0x0020);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x6F),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x43);

	/* (25) RESET Command queue	*/
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x70), 0x8804);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x71),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x44);

	/* (26) RESET Command queue	*/
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x72), 0x8888);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x73),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x44);

	/* (27) JOB_START */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x74), 0x0001);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x75),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x45);

	/* (28) Wait Interrupt */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x76), 0x0000);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x77),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WINT);

	/* (29) Clear JOB_END Interrupt */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x78), 0x0200);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x79),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x00);

	/* (30) Clear HW Enable */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x7A), 0x0000);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x7B),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x0A);

	/* (31) STOP */
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x7C), 0x0000);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_BASE1_ADDR, 0x7D),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_STOP);

	/* Start "Nand/Card IP" to read/write data from/to "Nand Flash/Card" */
	{
		NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();

		U16 u16_Tmp;
		U32 u32_PageCnt = 0x40;
		U32 u32_PhyRowIdx = 0;
		U32 u32_DataDMAAddr;
		U8* pu8_DataBuf = (U8*)DMA_W_ADDR;

		nand_pads_switch(1);
		REG_WRITE_UINT16(NC_MIE_EVENT, BIT_NC_JOB_END|BIT_MMA_DATA_END);

		u32_DataDMAAddr = nand_translate_DMA_address_Ex((U32)pu8_DataBuf, pNandDrv->u16_PageByteCnt * u32_PageCnt);

		REG_WRITE_UINT16(NC_JOB_BL_CNT, u32_PageCnt << pNandDrv->u8_PageSectorCntBits);
		REG_WRITE_UINT16(NC_SDIO_ADDR0, u32_DataDMAAddr & 0xFFFF);
		REG_WRITE_UINT16(NC_SDIO_ADDR1, u32_DataDMAAddr >> 16);
		REG_SET_BITS_UINT16(NC_MMA_PRI_REG, BIT_NC_DMA_DIR_W);
		REG_SET_BITS_UINT16(NC_PATH_CTL, BIT_MMA_EN);

		REG_WRITE_UINT16(NC_AUXREG_ADR, AUXADR_ADRSET);
		REG_WRITE_UINT16(NC_AUXREG_DAT, 0);
		REG_WRITE_UINT16(NC_AUXREG_DAT, u32_PhyRowIdx & 0xFFFF);
		REG_WRITE_UINT16(NC_AUXREG_DAT, u32_PhyRowIdx >> 16);

		REG_WRITE_UINT16(NC_AUXREG_ADR, AUXADR_INSTQUE);
		REG_WRITE_UINT16(NC_AUXREG_DAT, (pNandDrv->u8_OpCode_RW_AdrCycle<< 8) | (CMD_0x80));
		REG_WRITE_UINT16(NC_AUXREG_DAT, (CMD_0x10 << 8) | ACT_SER_DOUT);
		REG_WRITE_UINT16(NC_AUXREG_DAT, (CMD_0x70 << 8) | ACT_WAITRB);
		REG_WRITE_UINT16(NC_AUXREG_DAT, (ACT_REPEAT << 8) | ACT_CHKSTATUS);
		REG_WRITE_UINT16(NC_AUXREG_DAT, ACT_BREAK);
		REG_WRITE_UINT16(NC_AUXREG_ADR, AUXADR_RPTCNT);
		REG_WRITE_UINT16(NC_AUXREG_DAT, u32_PageCnt - 1);

		for (u16_Tmp=0; u16_Tmp < pNandDrv->u16_PageSectorCnt; u16_Tmp++)
			NC_SetCIFD_Const(0xFF, pNandDrv->u16_SectorSpareByteCnt * u16_Tmp,
							 pNandDrv->u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt);

		REG_WRITE_UINT16(NC_CTRL,
						 (BIT_NC_CIFD_ACCESS|BIT_NC_JOB_START|BIT_NC_IF_DIR_W));
		//while(1);
	}

	nand_hw_timer_delay(HW_TIMER_DELAY_1ms);
	/* Step 4: Before Nand IP DMA end, use RIU interface to test power save function */
	REG_WRITE_UINT16(NC_PWRSAVE_CTL, BIT_POWER_SAVE_MODE
					 | BIT_SD_POWER_SAVE_RIU
					 | BIT_POWER_SAVE_MODE_INT_EN
					 | BIT_SD_POWER_SAVE_RST);

	/* Step 5: Check Interrupt and interrupt type. */

	if (NC_WaitComplete(BIT_NC_POWER_SAVE, WAIT_RESET_TIME) == WAIT_RESET_TIME)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: timeout on waiting Reg00[BIT_NC_POWER_SAVE]\n");
		return UNFD_ST_ERR_RST_TIMEOUT;
	}

	REG_READ_UINT16(NC_PWRSAVE_CTL, u16_Reg);
	nand_debug(UNFD_DEBUG_LEVEL_HIGH, 1, "NC_PWRSAVE_CTL: 0x%04x\n", u16_Reg);

	REG_WRITE_UINT16(NC_PWRSAVE_CTL, 0);
//	nand_die();
	//NC_Init();
#endif
	return UNFD_ST_SUCCESS;
}
#elif defined(NC_SEL_FCIE5) && NC_SEL_FCIE5
static U32 NCTEST_PowerSave(void)
{
#if defined(FCIE_POWER_SAVE_MODE) && FCIE_POWER_SAVE_MODE
	U16 u16_Reg;
	U32 u32_Count;
	int i;

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x00), 0x0000);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x01),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x63);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x02), 0xffff);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x03),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x60);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x04), 0x0000);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x05),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x3F);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x06), 0x0001);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x07),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x3F);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x08), 0x0001);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x09),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x61);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x0A), 0x0001);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x0B),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x63);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x0C), 0x003C);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x0D),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x40);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x0E), 0x0020);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x0F),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x43);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x10), 0x8804);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x11),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x44);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x12), 0x8888);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x13),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x44);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x14), 0x0001);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x15),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x45);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x16), 0x0000);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x17),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WINT);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x18), 0x0001);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x19),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x60);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x1A), 0x0000);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x1B),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x63);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x1C), 0x0000);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x1D),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_STOP);

	{
		NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();

		U16 u16_Tmp;
		U32 u32_PageCnt = 0x40;
		U32 u32_PhyRowIdx = 0;
		U32 u32_DataDMAAddr, u32_SpareDMAAddr;
		U8* pu8_DataBuf = (U8*)DMA_W_ADDR;
		U8* pu8_SpareBuf = (U8*)DMA_W_SPARE_ADDR;

		for(u16_Tmp=0 ; u16_Tmp<128 ; u16_Tmp++)
			pu8_SpareBuf[u16_Tmp] = 0xFF;
			
		REG_WRITE_UINT16(NC_MIE_EVENT, BIT_NC_JOB_END);
		REG_CLR_BITS_UINT16(NC_FUN_CTL, BIT_R2N_MODE_EN);
		
		u32_DataDMAAddr = nand_translate_DMA_address_Ex((U32)pu8_DataBuf, pNandDrv->u16_PageByteCnt * u32_PageCnt, WRITE_TO_NAND);
		u32_SpareDMAAddr = nand_translate_DMA_address_Ex((U32)pu8_SpareBuf, pNandDrv->u16_SpareByteCnt, WRITE_TO_NAND);

		REG_WRITE_UINT16(NC_WSPARE_DMA_ADR0, u32_SpareDMAAddr & 0xFFFF);
		REG_WRITE_UINT16(NC_WSPARE_DMA_ADR1, u32_SpareDMAAddr >>16);
		
		REG_WRITE_UINT16(NC_WDATA_DMA_ADR0, u32_DataDMAAddr & 0xFFFF);//>>MIU_BUS_WIDTH_BITS));
		REG_WRITE_UINT16(NC_WDATA_DMA_ADR1, u32_DataDMAAddr >> 16);//(MIU_BUS_WIDTH_BITS+16)));

		REG_WRITE_UINT16(NC_AUXREG_ADR, AUXADR_ADRSET);
		REG_WRITE_UINT16(NC_AUXREG_DAT, 0);
		REG_WRITE_UINT16(NC_AUXREG_DAT, u32_PhyRowIdx & 0xFFFF);
		REG_WRITE_UINT16(NC_AUXREG_DAT, u32_PhyRowIdx >> 16);

		REG_WRITE_UINT16(NC_AUXREG_ADR, AUXADR_INSTQUE);
		REG_WRITE_UINT16(NC_AUXREG_DAT, (pNandDrv->u8_OpCode_RW_AdrCycle<< 8) | (CMD_0x80));
		REG_WRITE_UINT16(NC_AUXREG_DAT, (CMD_0x10 << 8) | ACT_SER_DOUT);
		REG_WRITE_UINT16(NC_AUXREG_DAT, (CMD_0x70 << 8) | ACT_WAITRB);
		REG_WRITE_UINT16(NC_AUXREG_DAT, (ACT_REPEAT << 8) | ACT_CHKSTATUS);
		REG_WRITE_UINT16(NC_AUXREG_DAT, ACT_BREAK);
		REG_WRITE_UINT16(NC_AUXREG_ADR, AUXADR_RPTCNT);
		REG_WRITE_UINT16(NC_AUXREG_DAT, u32_PageCnt - 1);

		REG_WRITE_UINT16(NC_CTRL, BIT_NC_JOB_START);
			//while(1);
	}

	nand_hw_timer_delay(HW_TIMER_DELAY_1ms);

	/* Step 4: Before Nand IP DMA end, use RIU interface to test power save function */
	REG_WRITE_UINT16(NC_PWR_SAVE_CTL, BIT_PWR_SAVE_MODE
					 | BIT_SD_PWR_SAVE_RIU
					 | BIT_PWR_SAVE_INT_EN
					 | BIT_SD_PWR_SAVE_RST);

	/* Step 5: Check Interrupt and interrupt type. */

	for (u32_Count=0; u32_Count < WAIT_RESET_TIME; u32_Count++)
	{
		REG_READ_UINT16(NC_PWR_SAVE_CTL, u16_Reg);
		if ((u16_Reg & BIT_PWR_SAVE_MODE_INT) == BIT_PWR_SAVE_MODE_INT)
			break;

		nand_hw_timer_delay(HW_TIMER_DELAY_1us);
	}

	if(u32_Count == WAIT_RESET_TIME)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: timeout on waiting Reg[BIT_NC_POWER_SAVE]\n");
		return UNFD_ST_ERR_RST_TIMEOUT;
	}

	REG_READ_UINT16(NC_PWR_SAVE_CTL, u16_Reg);
	nand_debug(UNFD_DEBUG_LEVEL_HIGH, 1, "NC_PWRSAVE_CTL: 0x%04x\n", u16_Reg);

	REG_WRITE_UINT16(NC_PWR_SAVE_CTL, BIT_PWR_SAVE_MODE_INT);
	REG_WRITE_UINT16(NC_PWR_SAVE_CTL, 0);

#endif
	return UNFD_ST_SUCCESS;

}

#endif

static U32 NCTEST_ECC_BCH(U8 u8_BCHBitCnt, U32 u32_TestRow, U8 u8_IsMLC) // ok for BCH 4/8
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err, u32_i, u32_j, u32_k;
	volatile U8  u8_Data, u8_Flag;
	volatile U16 u16_Reg51, u16_Reg52, u16_Reg53,u16_Reg54;

	U8  *au8_W, *au8_R;
	U8  *au8_WSpare, *au8_RSpare;

	if(u8_IsMLC)
		u8_BCHBitCnt /= 2;

	nand_debug(0, 1, "BCH Correctable Bit : 0x%X\n", u8_BCHBitCnt);
	// ----------------------------
    // setup data
    // ----------------------------
	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	for (u32_i = 0; u32_i < pNandDrv->u16_PageByteCnt; u32_i++)
	{
		//au8_W[u32_i] = (u32_i & 0xFF);
		au8_W[u32_i] = ECC_TEST_PATTERN;
		au8_R[u32_i] = ~au8_W[u32_i];
	}
	au8_WSpare[0] = 0xFF;
	for (u32_i = 1; u32_i < pNandDrv->u16_SpareByteCnt; u32_i++)
	{
		//au8_WSpare[u32_i] = (u32_i & 0xFF);
		au8_WSpare[u32_i] = ECC_TEST_PATTERN;
		au8_RSpare[u32_i] = ~au8_WSpare[u32_i];
	}

	u32_Err = NC_EraseBlk(u32_TestRow);

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "ERROR: %s 1, ErrCode: 0x%08lX\n", __func__,u32_Err);
		return u32_Err;
	}
	pNandDrv->u16_Reg48_Spare |= BIT_NC_HW_AUTO_RANDOM_CMD_DISABLE;
	NC_Config();

	dump_mem(au8_WSpare, pNandDrv->u16_SpareByteCnt);
	#if 0
	nand_debug(0,1,"Write 1 3s\n");
	nand_hw_timer_delay(DELAY_1s_in_us);
	nand_debug(0,1,"Delay 1s\n");
	nand_hw_timer_delay(DELAY_1s_in_us);
	nand_debug(0,1,"Delay 1s\n");
	nand_hw_timer_delay(DELAY_1s_in_us);
	nand_debug(0,1,"Delay 1s\n");
	#endif
	u32_Err = NC_WriteSectors(u32_TestRow, 0, au8_W, au8_WSpare, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "ERROR: %s 2, ErrCode: 0x%08lX\n", __func__,u32_Err);
		return u32_Err;
	}
	#if 0
	nand_debug(0,1,"Read 1  3s\n");
	nand_hw_timer_delay(DELAY_1s_in_us);
	nand_debug(0,1,"Delay 1s\n");
	nand_hw_timer_delay(DELAY_1s_in_us);
	nand_debug(0,1,"Delay 1s\n");
	nand_hw_timer_delay(DELAY_1s_in_us);
	nand_debug(0,1,"Delay 1s\n");
	#endif
	u32_Err = NC_ReadSectors(u32_TestRow, 0, au8_R, au8_RSpare, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "ERROR: %s 3, ErrCode: 0x%08lX\n", __func__,u32_Err);
		return u32_Err;
	}
	nand_debug(0, 1, "dump: \n");
	dump_mem(au8_RSpare, pNandDrv->u16_SpareByteCnt);

	for(u32_i=0; u32_i<pNandDrv->u16_SectorByteCnt; u32_i++)
		if(au8_W[u32_i] != au8_R[u32_i])
		{
			nand_debug(0, 0, "ERROR: %s 4, I:%lX W:%X R:%X\n",__func__,
				u32_i, au8_W[u32_i], au8_R[u32_i]);
			return UNFD_ST_ERR_DATA_CMP_FAIL;
		}
	if((pNandDrv->u16_Reg48_Spare & BIT_NC_SPARE_ECC_BYPASS) == 0)
	{
		for(u32_i=0; u32_i<pNandDrv->u16_SectorSpareByteCnt-pNandDrv->u16_ECCCodeByteCnt; u32_i++)
			if(au8_WSpare[u32_i] != au8_RSpare[u32_i])
			{
				nand_debug(0, 0, "ERROR: %s 5, I:%lX W:%X R:%X\n",__func__,
					u32_i, au8_WSpare[u32_i], au8_RSpare[u32_i]);
				return UNFD_ST_ERR_DATA_CMP_FAIL;
			}
	}

	// ----------------------------
    // corrupt data bits
    // ----------------------------
	u8_Flag = 0;
	memcpy(au8_WSpare, au8_RSpare, pNandDrv->u16_SpareByteCnt);
	if(pNandDrv->u16_Reg48_Spare & BIT_NC_SPARE_ECC_BYPASS)
	{
		au8_WSpare[0] = 0xFF;
		for(u32_i=1; u32_i<pNandDrv->u16_SectorSpareByteCnt-pNandDrv->u16_ECCCodeByteCnt; u32_i++)
			au8_WSpare[u32_i] = u32_i;
	}
	for(u32_j=0; u32_j<u8_BCHBitCnt + 1; u32_j++)
	{
		nand_debug(0, 1, "corrupt %lXh bits\n", u32_j+1);

		#if 0xFF == ECC_TEST_PATTERN
		u8_Data = 0xFE;
		#elif 0 == ECC_TEST_PATTERN
		u8_Data = 0x01;
		#endif

		if(pNandDrv->u16_Reg48_Spare & BIT_NC_SPARE_ECC_BYPASS)
		{
			au8_W[u32_j] = u8_Data;
			nand_debug(0,1,"Data: %X\n", au8_W[u32_j]);
		}
		else
		{
			if(u32_j < u8_BCHBitCnt / 2 && (u32_j ) < pNandDrv->u16_SectorSpareByteCnt-pNandDrv->u16_ECCCodeByteCnt)
			{
				au8_WSpare[u32_j ] = u8_Data;
				nand_debug(0,1,"Spare Data: %X\n", au8_WSpare[u32_j]);
			}
			else
			{
				au8_W[u32_j] = u8_Data;
				nand_debug(0,1,"Data: %X\n", au8_W[u32_j]);
			}
		}

		pNandDrv->u16_Reg50_EccCtrl |= BIT_NC_BYPASS_ECC;
		pNandDrv->u16_Reg48_Spare	|= BIT_NC_HW_AUTO_RANDOM_CMD_DISABLE;
	    	NC_Config();
#if 0
		nand_debug(0,1,"Write 2 3s\n");
		nand_hw_timer_delay(DELAY_1s_in_us);
		nand_debug(0,1,"Delay 1s\n");
		nand_hw_timer_delay(DELAY_1s_in_us);
		nand_debug(0,1,"Delay 1s\n");
		nand_hw_timer_delay(DELAY_1s_in_us);
		nand_debug(0,1,"Delay 1s\n");
#endif
		u32_Err = NC_WriteSectors(u32_TestRow + u32_j+1, 0, au8_W, au8_WSpare, 1);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(0, 1, "ERROR: %s 6, ErrCode: 0x%08lX\n", __func__,u32_Err);
			return u32_Err;
		}
		pNandDrv->u16_Reg50_EccCtrl &= ~BIT_NC_BYPASS_ECC;
		pNandDrv->u16_Reg48_Spare	|= BIT_NC_HW_AUTO_RANDOM_CMD_DISABLE;

		NC_Config();
#if 0
		nand_debug(0,1,"Read 2 3s\n");
		nand_hw_timer_delay(DELAY_1s_in_us);
		nand_debug(0,1,"Delay 1s\n");
		nand_hw_timer_delay(DELAY_1s_in_us);
		nand_debug(0,1,"Delay 1s\n");
		nand_hw_timer_delay(DELAY_1s_in_us);
		nand_debug(0,1,"Delay 1s\n");
#endif

		u32_Err = NC_ReadSectors(u32_TestRow + u32_j+1, 0, au8_R, au8_RSpare, 1);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(0, 1, "ERROR: %s 7, ErrCode: 0x%08lX\n", __func__, u32_Err);
			return u32_Err;
		}

		//dump_mem(au8_W, 8);
		//dump_mem(au8_R, 8);

		// check data
		if(u32_j<u8_BCHBitCnt)
		{
			for(u32_i=0; u32_i<pNandDrv->u16_SectorByteCnt; u32_i++)
			{
				if(ECC_TEST_PATTERN != au8_R[u32_i])
				{
					nand_debug(0, 1, "%s 8, I:%lX R:%X != %X\n",__func__,
						u32_i,  au8_R[u32_i], ECC_TEST_PATTERN);
					return UNFD_ST_ERR_DATA_CMP_FAIL;
				}
			}
			for(u32_i=0; u32_i<pNandDrv->u16_SectorSpareByteCnt-pNandDrv->u16_ECCCodeByteCnt; u32_i++)
			{
				if(pNandDrv->u16_Reg48_Spare & BIT_NC_SPARE_ECC_BYPASS)
				{
					if(au8_WSpare[u32_i] != au8_RSpare[u32_i] && u8_IsMLC == 0)
					{
						nand_debug(0, 1, "Warning :  au8_RSpare[0x%04lx]: 0x%02x != 0x%x\n", u32_i, au8_RSpare[u32_i], au8_WSpare[u32_i]);
					}
				}
				 else if(au8_RSpare[u32_i] != ECC_TEST_PATTERN)
				 {
					nand_debug(0, 1, "%s 9, I:%lX R:%X != %X\n",__func__,
						u32_i,  au8_RSpare[u32_i], ECC_TEST_PATTERN);
					return UNFD_ST_ERR_DATA_CMP_FAIL;
				 }
			}
		}

		// check registers
		REG_READ_UINT16(NC_ECC_STAT0, u16_Reg51);
		REG_READ_UINT16(NC_ECC_STAT1, u16_Reg52);
		REG_READ_UINT16(NC_ECC_STAT2, u16_Reg53);
		nand_debug(0, 1, "Reg51: 0x%04x  Reg52: 0x%04x  Reg53: 0x%04x\n",
			u16_Reg51, u16_Reg52, u16_Reg53);

		if(1!=(u16_Reg53 & BIT_NC_ECC_FLGA_MASK) && u32_j<u8_BCHBitCnt)
		{
			nand_debug(0, 1, "Reg53 incorrect 0: %X \n", u16_Reg53);
			return UNFD_ST_ERR_ECC_FAIL;
		}
		if(2!=(u16_Reg53 & BIT_NC_ECC_FLGA_MASK) && u32_j==(u8_BCHBitCnt) && u8_IsMLC == 0)
		{
			nand_debug(0, 1, "Reg53 incorrect 1: %X \n", u16_Reg53);
			return UNFD_ST_ERR_ECC_FAIL;
		}

		if(1!=u16_Reg52 && u32_j<(u8_BCHBitCnt))
		{
			nand_debug(0, 1, "Reg52 incorrect 0: %X \n", u16_Reg52);
			return UNFD_ST_ERR_ECC_FAIL;
		}
		if(1==u16_Reg52 && u32_j==(u8_BCHBitCnt) && u8_IsMLC == 0)
		{
			nand_debug(0, 1, "Reg52 incorrect 1: %X \n", u16_Reg52);
			return UNFD_ST_ERR_ECC_FAIL;
		}

		if((u16_Reg51&BIT_NC_ECC_FAIL) && u32_j<(u8_BCHBitCnt))
		{
			nand_debug(0, 1, "Reg51 incorrect 0: %X \n", u16_Reg51);
			return UNFD_ST_ERR_ECC_FAIL;
		}
		if(0==(u16_Reg51&BIT_NC_ECC_FAIL) && u32_j==(u8_BCHBitCnt) && u8_IsMLC == 0)
		{
			nand_debug(0, 1, "Reg51 incorrect 1: %X \n", u16_Reg51);
			return UNFD_ST_ERR_ECC_FAIL;
		}
		if(((u16_Reg51&BIT_NC_ECC_MAX_BITS_MASK)>>1)!=(u32_j+1) && u32_j<(u8_BCHBitCnt))
		{
			if(u8_IsMLC == 0)
			{
				nand_debug(0, 1, "Reg51 incorrect 2: %X \n", u16_Reg51);
				return UNFD_ST_ERR_ECC_FAIL;
			}
			else
			{
				nand_debug(0, 1, "Warning MLC Reg51 incorrect 2: %X \n", u16_Reg51);
			}
		}

		//using R2N Mode

		// read back
		u32_Err = NC_ReadSector_RIUMode(u32_TestRow + u32_j+1, 0, (U8*)au8_R, (U8*)au8_RSpare);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			if(UNFD_ST_ERR_ECC_FAIL_RM == u32_Err && u32_j==(u8_BCHBitCnt))
			{
				continue;
			}
			nand_debug(0, 1, "ERROR: %s 2, ErrCode: 0x%08lx\n",__func__, u32_Err);
			return u32_Err;
		}
		// check data
		for (u32_i = 0; u32_i < pNandDrv->u16_SectorByteCnt; u32_i++)
		{
			if (ECC_TEST_PATTERN != au8_R[u32_i])
			{
				nand_debug(0, 1, "Err: au8_R[0x%04lx]: 0x%02x != 0x%x\n", u32_i, au8_R[u32_i], ECC_TEST_PATTERN);
				return UNFD_ST_ERR_DATA_CMP_FAIL;
			}
		}
		for (u32_i = 0; u32_i < pNandDrv->u16_SectorSpareByteCnt; u32_i++)
		{
			if (u32_i == pNandDrv->u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt +
					pNandDrv->u16_SectorSpareByteCnt * (u32_i / pNandDrv->u16_SectorSpareByteCnt))
			{
				u32_i += pNandDrv->u16_ECCCodeByteCnt;
				u32_i -= 1;  continue;
			}


			if(!(pNandDrv->u16_Reg48_Spare & BIT_NC_SPARE_ECC_BYPASS))
			{
				if (ECC_TEST_PATTERN != au8_RSpare[u32_i] && u8_IsMLC == 0)
				{
					nand_debug(0, 1, "Err: au8_RSpare[0x%04lx]: 0x%02x != 0x%x\n", u32_i, au8_RSpare[u32_i], ECC_TEST_PATTERN);
					return UNFD_ST_ERR_DATA_CMP_FAIL;
				}
			}
			else
			{
				if(au8_WSpare[u32_i] != au8_RSpare[u32_i])
				{
					nand_debug(0, 1, "Warning :  au8_RSpare[0x%04lx]: 0x%02x != 0x%x\n", u32_i, au8_RSpare[u32_i], au8_WSpare[u32_i]);
				}
			}
		}

		//check RIU Mode ECC registers
		REG_READ_UINT16(NC_ECC_STAT0, u16_Reg51);
		REG_READ_UINT16(NC_ECC_STAT1, u16_Reg52);
		REG_READ_UINT16(NC_ECC_STAT2, u16_Reg53);
		nand_debug(2, 1, "Reg51: 0x%04x  Reg52: 0x%04x	Reg53: 0x%04x\n", u16_Reg51, u16_Reg52, u16_Reg53);
		if (u16_Reg51 & BIT_NC_ECC_FAIL)
		{
			nand_debug(0, 1, "ERROR: ECC_BCH_RIU 3, ErrCode: 0x%08x\n", UNFD_ST_ERR_INVALID_ECC_REG51);
			return UNFD_ST_ERR_INVALID_ECC_REG51;
		}
		/*if (1 != u16_Reg52)
		  {
		  nand_debug(0, 1, "ERROR: ECC_BCH24b_1KB_RIU 4, ErrCode: 0x%08x\n", UNFD_ST_ERR_INVALID_ECC_REG52);
		  return UNFD_ST_ERR_INVALID_ECC_REG52;
		  }*/
		if ((u16_Reg53 & BIT_NC_ECC_FLGA_MASK) != BIT_NC_ECC_FLGA_CORRECT)
		{
			nand_debug(0, 1, "ERROR: ECC_BCH_RIU 5, ErrCode: 0x%08x\n", UNFD_ST_ERR_INVALID_ECC_REG53);
			return UNFD_ST_ERR_INVALID_ECC_REG53;
		}
		u32_i = (u16_Reg51 & BIT_NC_ECC_MAX_BITS_MASK)>>1;
		nand_debug(0, 1, "0x%lx bits to be corrected\n", u32_i);
		for (u32_k = 0; u32_k < u32_i; u32_k++)
		{
			REG_CLR_BITS_UINT16(NC_ECC_STAT2, BIT_NC_ECC_SEL_LOC_MASK);
			REG_SET_BITS_UINT16(NC_ECC_STAT2, u32_k<<BIT_NC_ECC_SEL_LOC_SHIFT);
			REG_READ_UINT16(NC_ECC_LOC, u16_Reg54);
			nand_debug(0, 1, " err:bit-0x%02lx, loc: 0x%04x-th bit\n", u32_k, u16_Reg54);
		}
		//u8_Flag = 0;
	}

	return UNFD_ST_SUCCESS;
}

//testing ecc corruption and repeat count

U32 NCTEST_ECC_BCH_PageMode(U32 u32_TestRow)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_i, u32_j, u32_k, u32_Err;
	U8  *au8_W, *au8_R;
	U8  *au8_WSpare, *au8_RSpare;
	U8 u8_Data;
	volatile U16 u16_Reg51, u16_Reg52, u16_Reg53;

	au8_W = (U8*)(DMA_W_ADDR);
	au8_R = (U8*)(DMA_R_ADDR);
	au8_WSpare = (U8*)(DMA_W_SPARE_ADDR);
	au8_RSpare = (U8*)(DMA_R_SPARE_ADDR);

	//init data
	for(u32_i = 0; u32_i < pNandDrv->u16_PageByteCnt; u32_i ++)
	{
		au8_W[u32_i] = ECC_TEST_PATTERN;
		au8_R [u32_i] = ~(au8_W[u32_i] );
	}
	for(u32_i = 0; u32_i < pNandDrv->u16_PageSectorCnt; u32_i ++)
	{
		au8_WSpare[u32_i * pNandDrv->u16_SectorSpareByteCnt + 0] = 0xFF;
		au8_WSpare[u32_i * pNandDrv->u16_SectorSpareByteCnt + 1] = u32_i;
		for(u32_j = 2;u32_j < pNandDrv->u16_SectorSpareByteCnt; u32_j ++)
		{
			au8_WSpare[u32_i * pNandDrv->u16_SectorSpareByteCnt + u32_j] =ECC_TEST_PATTERN;

			au8_RSpare [u32_i * pNandDrv->u16_SectorSpareByteCnt + u32_j] = ~(au8_WSpare[u32_j] );
		}
	}
	//erase block

	u32_Err = NC_EraseBlk(u32_TestRow);
	if(u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "ERROR: %s Erase 1\n", __func__);
		return u32_Err;
	}

	u32_Err = NC_WritePages(u32_TestRow + 0, au8_W, au8_WSpare, 1);
	if(u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "ERROR: %s Write Page 1\n", __func__);
		return u32_Err;
	}

	u32_Err = NC_ReadPages(u32_TestRow + 0, au8_R, au8_RSpare, 1);
	if(u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "ERROR: %s Read Page 1\n", __func__);
		return u32_Err;
	}

	for(u32_i=0; u32_i<pNandDrv->u16_PageByteCnt; u32_i++)
		if(au8_W[u32_i] != au8_R[u32_i])
		{
			nand_debug(0, 0, "ERROR: %s 4, I:%lX W:%X R:%X\n",__func__,
				u32_i, au8_W[u32_i], au8_R[u32_i]);
			return UNFD_ST_ERR_DATA_CMP_FAIL;
		}
	for(u32_j = 0; u32_j < pNandDrv->u16_PageSectorCnt; u32_j ++)
	{
		for(u32_i=0; u32_i<pNandDrv->u16_SectorSpareByteCnt-pNandDrv->u16_ECCCodeByteCnt; u32_i++)
		{
			if(au8_WSpare[u32_j * pNandDrv->u16_SectorSpareByteCnt + u32_i] != au8_RSpare[u32_j * pNandDrv->u16_SectorSpareByteCnt + u32_i])
			{
				nand_debug(0, 0, "ERROR: %s 5, I:%lX W:%X R:%X\n",__func__,
					u32_i, au8_WSpare[u32_j * pNandDrv->u16_SectorSpareByteCnt + u32_i], au8_RSpare[ u32_j * pNandDrv->u16_SectorSpareByteCnt +u32_i]);
				return UNFD_ST_ERR_DATA_CMP_FAIL;
			}
		}
	}

	//copy ecc code from RSpare buffer to WSpare buffer
	memcpy(au8_WSpare, au8_RSpare, pNandDrv->u16_SpareByteCnt);

	//begin corruption data, max number of bits for corruption is half of that able to correct
	for(u32_j = 0; u32_j < pNandDrv->u16_ECCCorretableBit >> 1 ; u32_j ++)
	{
		nand_debug(0, 1, "corrupt %lXh bits\n", u32_j+1);

		#if 0xFF == ECC_TEST_PATTERN
		u8_Data = 0xFE;
		#elif 0 == ECC_TEST_PATTERN
		u8_Data = 0x01;
		#endif

		//then same index of each sector
		for(u32_i = 0; u32_i < pNandDrv->u16_PageSectorCnt; u32_i ++)
		{
			au8_W[u32_i * pNandDrv->u16_SectorByteCnt + u32_j] = u8_Data;
			nand_debug(0,1,"Corrupt Idx %lX, Data: %X\n", u32_i * pNandDrv->u16_SectorByteCnt + u32_j, au8_W[u32_i * pNandDrv->u16_SectorByteCnt + u32_j]);
		}


		pNandDrv->u16_Reg50_EccCtrl |= BIT_NC_BYPASS_ECC;
	    	NC_Config();

		u32_Err = NC_WritePages(u32_TestRow + u32_j+1, au8_W, au8_WSpare, 1);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(0, 1, "ERROR: %s 6, ErrCode: 0x%08lX\n", __func__,u32_Err);
			return u32_Err;
		}

		pNandDrv->u16_Reg50_EccCtrl &= ~BIT_NC_BYPASS_ECC;
		NC_Config();

		u32_Err = NC_ReadPages(u32_TestRow + u32_j+1, au8_R, au8_RSpare, 1);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			dump_mem(au8_R, pNandDrv->u16_PageByteCnt);
			dump_mem(au8_RSpare, pNandDrv->u16_SpareByteCnt);
			nand_debug(0, 1, "ERROR: %s 7, ErrCode: 0x%08lX\n", __func__, u32_Err);
			return u32_Err;
		}

		for(u32_i=0; u32_i<pNandDrv->u16_PageByteCnt; u32_i++)
			if(ECC_TEST_PATTERN!= au8_R[u32_i])
			{
				nand_debug(0, 0, "ERROR: %s 8, I:%lX R:%X != %X\n",__func__,
					u32_i, au8_R[u32_i], ECC_TEST_PATTERN);
				return UNFD_ST_ERR_DATA_CMP_FAIL;
			}
		for(u32_k = 0; u32_k < pNandDrv->u16_PageSectorCnt; u32_k ++)
		{
			for(u32_i=0; u32_i<pNandDrv->u16_SectorSpareByteCnt-pNandDrv->u16_ECCCodeByteCnt; u32_i++)
			{
				if(au8_WSpare[u32_k * pNandDrv->u16_SectorSpareByteCnt + u32_i] != au8_RSpare[u32_k * pNandDrv->u16_SectorSpareByteCnt + u32_i])
				{
					nand_debug(0, 0, "ERROR: %s 9, I:%lX W:%X R:%X\n",__func__,
						u32_i, au8_WSpare[u32_k * pNandDrv->u16_SectorSpareByteCnt + u32_i], au8_RSpare[ u32_k * pNandDrv->u16_SectorSpareByteCnt +u32_i]);
					return UNFD_ST_ERR_DATA_CMP_FAIL;
				}
			}
		}

		REG_READ_UINT16(NC_ECC_STAT0, u16_Reg51);
		REG_READ_UINT16(NC_ECC_STAT1, u16_Reg52);
		REG_READ_UINT16(NC_ECC_STAT2, u16_Reg53);
		nand_debug(0, 1, "Reg51: 0x%04x  Reg52: 0x%04x  Reg53: 0x%04x\n",
			u16_Reg51, u16_Reg52, u16_Reg53);

		if(1!=(u16_Reg53 & BIT_NC_ECC_FLGA_MASK))
		{
			nand_debug(0, 1, "Reg53 incorrect 0: %X \n", u16_Reg53);
			return UNFD_ST_ERR_ECC_FAIL;
		}

		if(pNandDrv->u16_PageSectorCnt!=u16_Reg52)
		{
			nand_debug(0, 1, "Warning could be MLC Reg52 incorrect 2: %X \n", u16_Reg52);
			nand_debug(0, 1, "Reg52 incorrect 0: %X, expected %X \n", u16_Reg52, pNandDrv->u16_PageSectorCnt);
		}

		if((u16_Reg51&BIT_NC_ECC_FAIL))
		{
			nand_debug(0, 1, "Reg51 incorrect 0: %X \n", u16_Reg51);
			return UNFD_ST_ERR_ECC_FAIL;
		}
		if(((u16_Reg51&BIT_NC_ECC_MAX_BITS_MASK)>>1)!=(u32_j+1) )
		{
			nand_debug(0, 1, "Warning could be MLC Reg51 incorrect 2: %X \n", u16_Reg51);
		}
	}

	return UNFD_ST_SUCCESS;
}


#if defined(NC_SEL_FCIE3) && NC_SEL_FCIE3
#define ECC512BCount  6
#define ECC1KBCount	3
U8 au8_ECCType512B[] = {
	ECC_TYPE_4BIT, ECC_TYPE_8BIT, ECC_TYPE_12BIT,ECC_TYPE_16BIT, ECC_TYPE_20BIT, ECC_TYPE_24BIT
};
U8 au8_ECCType1KB[] = {
	ECC_TYPE_24BIT1KB,	ECC_TYPE_32BIT1KB,  ECC_TYPE_40BIT1KB
};
U16 au16_512BECCByteCnt[] =
{
	ECC_CODE_BYTECNT_4BIT, ECC_CODE_BYTECNT_8BIT, ECC_CODE_BYTECNT_12BIT, ECC_CODE_BYTECNT_16BIT, ECC_CODE_BYTECNT_20BIT,
	ECC_CODE_BYTECNT_24BIT
};

U16 au16_1KBECCByteCnt[] =
{
	ECC_CODE_BYTECNT_24BIT1KB, ECC_CODE_BYTECNT_32BIT1KB, ECC_CODE_BYTECNT_40BIT1KB
};


static U32 NCTEST_ALL_ECC_BCH(U32 u32_TestRow)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	//config all type of ecc
	U8 u8_ECCIdx, u8_SpareCntIdx;
	U32 u32_Err;

	//init PageSectorCnt for 512B ECC
	pNandDrv->u16_PageByteCnt = 0x800;
	pNandDrv->u16_SpareByteCnt = 0x100;
	pNandDrv->u16_ECCType = au8_ECCType512B[0];
	NC_ConfigNandFlashContext();
	NC_RegInit();
	#if 1
	for(u8_ECCIdx = 0; u8_ECCIdx < ECC512BCount; u8_ECCIdx++)
	{
		for(u8_SpareCntIdx = 0; u8_SpareCntIdx < 11; u8_SpareCntIdx++)
		{
			#if defined(ENABLE_32BIT_MACRO) && ENABLE_32BIT_MACRO		//HW limitation 4x mode SectorSpareByteCnt should be multiple of 4
			if(au16_512BECCByteCnt[u8_ECCIdx] % 4)
				pNandDrv->u16_SpareByteCnt = ((au16_512BECCByteCnt[u8_ECCIdx] / 4 + 1)  * 4 + (u8_SpareCntIdx + 1) * 4) * pNandDrv->u16_PageSectorCnt;
			else
				pNandDrv->u16_SpareByteCnt = (au16_512BECCByteCnt[u8_ECCIdx] + (u8_SpareCntIdx + 1) * 4) * pNandDrv->u16_PageSectorCnt;
			#else
			pNandDrv->u16_SpareByteCnt = (au16_512BECCByteCnt[u8_ECCIdx] + (u8_SpareCntIdx + 1) * 2) * pNandDrv->u16_PageSectorCnt;
			#endif
			nand_debug(0, 1, "Testing ECC Type 0x%X, Spare Size %d\n", au8_ECCType512B[u8_ECCIdx], pNandDrv->u16_SpareByteCnt);
			pNandDrv->u16_ECCType = au8_ECCType512B[u8_ECCIdx];
			NC_ConfigNandFlashContext();
			NC_RegInit();
			NC_Config();
			#if 0
			pNandDrv->u16_Reg48_Spare |= BIT_NC_SPARE_ECC_BYPASS;
			NC_Config();
			nand_debug(0,1, "Spare ECC Bypass\n");
			u32_Err = NCTEST_ECC_BCH(pNandDrv->u16_ECCCorretableBit, u32_TestRow, 0);
			if(u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(0,  1, "%s fail with ECC Type %X\n", __func__,au8_ECCType512B[u8_ECCIdx]);
				return UNFD_ST_ERR_ECC_FAIL;
			}
			#endif

			pNandDrv->u16_Reg48_Spare &= ~BIT_NC_SPARE_ECC_BYPASS;
			NC_Config();
			nand_debug(0,1, "No Spare ECC Bypass\n");
			u32_Err = NCTEST_ECC_BCH(pNandDrv->u16_ECCCorretableBit, u32_TestRow, 0);
			if(u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(0,  1, "%s fail with ECC Type %X\n", __func__,au8_ECCType512B[u8_ECCIdx]);
				return UNFD_ST_ERR_ECC_FAIL;
			}

			nand_debug(0,1, "OK\n\n");
		}
	}
	#endif

	//init PageSectorCnt for 1KB ECC
	pNandDrv->u16_SpareByteCnt = 0x100;
	pNandDrv->u16_ECCType = au8_ECCType1KB[0];
	NC_ConfigNandFlashContext();
	NC_RegInit();

	for(u8_ECCIdx = 0; u8_ECCIdx < ECC1KBCount; u8_ECCIdx++)
	{
		for(u8_SpareCntIdx = 0; u8_SpareCntIdx < 11; u8_SpareCntIdx++)
		{
			#if defined(ENABLE_32BIT_MACRO) && ENABLE_32BIT_MACRO		//HW limitation 4x mode SectorSpareByteCnt should be multiple of 4
			if(au16_1KBECCByteCnt[u8_ECCIdx] % 4)
				pNandDrv->u16_SpareByteCnt = ((au16_1KBECCByteCnt[u8_ECCIdx] / 4 + 1)  * 4 + (u8_SpareCntIdx + 1) * 4) * pNandDrv->u16_PageSectorCnt;
			else
				pNandDrv->u16_SpareByteCnt = (au16_1KBECCByteCnt[u8_ECCIdx] + (u8_SpareCntIdx + 1) * 4) * pNandDrv->u16_PageSectorCnt;
			#else
			pNandDrv->u16_SpareByteCnt = (au16_1KBECCByteCnt[u8_ECCIdx] + (u8_SpareCntIdx + 1) * 2) * pNandDrv->u16_PageSectorCnt;
			#endif

			nand_debug(0, 1, "Testing ECC Type 0x%X, Spare Size %d\n", au8_ECCType1KB[u8_ECCIdx], pNandDrv->u16_SpareByteCnt);
			pNandDrv->u16_ECCType = au8_ECCType1KB[u8_ECCIdx];
			NC_ConfigNandFlashContext();
			NC_RegInit();
			#if 0
			pNandDrv->u16_Reg48_Spare |= BIT_NC_SPARE_ECC_BYPASS;
			NC_Config();
			nand_debug(0,1, "Spare ECC Bypass\n");
			u32_Err = NCTEST_ECC_BCH(pNandDrv->u16_ECCCorretableBit, u32_TestRow, 0);
			if(u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(0,  1, "%s fail with ECC Type %X\n", __func__,au8_ECCType1KB[u8_ECCIdx]);
				return UNFD_ST_ERR_ECC_FAIL;
			}
			#endif

			pNandDrv->u16_Reg48_Spare &= ~BIT_NC_SPARE_ECC_BYPASS;
			NC_Config();

			nand_debug(0,1, "No Spare ECC Bypass\n");
			u32_Err = NCTEST_ECC_BCH(pNandDrv->u16_ECCCorretableBit, u32_TestRow, 0);
			if(u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(0,  1, "%s fail with ECC Type %X\n", __func__,au8_ECCType1KB[u8_ECCIdx]);
				return UNFD_ST_ERR_ECC_FAIL;
			}

			nand_debug(0,1, "OK\n\n");
		}
	}

	pNandDrv->u16_PageByteCnt = NAND_PAGE_BYTE_CNT;
	pNandDrv->u16_SpareByteCnt = NAND_SPARE_BYTE_CNT;
	pNandDrv->u16_ECCType = NAND_ECC_TYPE;
	NC_ConfigNandFlashContext();
	NC_RegInit();

	return UNFD_ST_SUCCESS;
}

#define PAGE_MODE_COUNT	5

U16 au16_PageByteCnt[]=
{
	512, 2048, 4096, 8192, 16384,
};

static U32 NCTEST_All_Page_Mode(void)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err, u32_i, u32_j, u32_k, u32_Row = 10 * pNandDrv->u16_BlkPageCnt;
	U8 u8_1KECC;

	for(u32_i =0; u32_i < PAGE_MODE_COUNT; u32_i ++)
	{
		pNandDrv->u16_PageByteCnt = au16_PageByteCnt[u32_i];

		if(au16_PageByteCnt[u32_i] < 1024)
			u8_1KECC =0;
		else
			u8_1KECC = 1;
		for(u32_j = 0; u32_j < ECC512BCount; u32_j ++)
		{
			for(u32_k = 1; u32_k < 11; u32_k ++)
			{
				//check if good block
				pNandDrv->u16_PageByteCnt = NAND_PAGE_BYTE_CNT;
				pNandDrv->u16_SpareByteCnt = NAND_SPARE_BYTE_CNT;
				pNandDrv->u16_ECCType = NAND_ECC_TYPE;
				NC_ConfigNandFlashContext();
				u32_Err = NC_RegInit();
				NC_Config();
				if(u32_Err	!= UNFD_ST_SUCCESS)
				{
					nand_debug(0, 1, "Init fail\n");
					goto Error;
				}


				while(drvNAND_IsGoodBlk(u32_Row >> pNandDrv->u8_BlkPageCntBits) == 0)
				{
					nand_debug(0,1, "Skip Bad PBA 0x%lX\n", u32_Row >> pNandDrv->u8_BlkPageCntBits);
					u32_Row += pNandDrv->u16_BlkPageCnt;
					if(u32_Row >= (pNandDrv->u16_BlkCnt << pNandDrv->u8_BlkPageCntBits))
						u32_Row = 10 * pNandDrv->u16_BlkPageCnt;
				}
				nand_debug(0,1, "Testing Row 0x%lX\n", u32_Row);
				pNandDrv->u16_PageByteCnt = au16_PageByteCnt[u32_i] ;
				pNandDrv->u16_ECCType  = au8_ECCType512B[u32_j];


				if(au16_512BECCByteCnt[u32_j] % 4)
					pNandDrv->u16_SpareByteCnt = ((au16_512BECCByteCnt[u32_j] / 4 + 1)	* 4 + (u32_k) * 4) * (pNandDrv->u16_PageByteCnt / 512);
				else
					pNandDrv->u16_SpareByteCnt = (au16_512BECCByteCnt[u32_j] + (u32_k) * 4) * (pNandDrv->u16_PageByteCnt / 512);

				pNandDrv->u16_SpareByteCnt = ((pNandDrv->u16_SpareByteCnt  / (pNandDrv->u16_PageByteCnt / 512)) + ( 16 - (pNandDrv->u16_SpareByteCnt  / (pNandDrv->u16_PageByteCnt / 512)) % 16)) * (pNandDrv->u16_PageByteCnt / 512);

				if(pNandDrv->u16_PageByteCnt > NAND_PAGE_BYTE_CNT || pNandDrv->u16_SpareByteCnt > NAND_SPARE_BYTE_CNT)
				{
					if(u8_1KECC == 1)
						goto TRY_1KB;
					else
						continue;
				}

				nand_debug(0,1 , "Tesing Page Byte %d\n", pNandDrv->u16_PageByteCnt);
				nand_debug(0,1 , "Tesing Spare Byte %d\n", pNandDrv->u16_SpareByteCnt);
				nand_debug(0,1 , "Tesing  ECC Mode %d\n", pNandDrv->u16_ECCType);
				NC_ConfigNandFlashContext();
				u32_Err = NC_RegInit();
				NC_Config();
				if(u32_Err	!= UNFD_ST_SUCCESS)
				{
					nand_debug(0, 1, "Init fail\n");
					goto Error;
				}
				if(NAND_PAGE_BYTE_CNT > 0x200)
				{
					pNandDrv->u16_Reg48_Spare&= ~BIT_NC_ONE_COL_ADDR;
					NC_Config();
				}
				nand_debug(0, 1, "Testing for DMA\n");
				u32_Err = NCTEST_RWSinglePages(u32_Row,3);
				if(u32_Err	!=	UNFD_ST_SUCCESS)
				{
					goto Error;
				}
				nand_debug(0, 1, "Testing for RIU\n");

				u32_Err = NCTEST_RWSinglePages_RM(u32_Row,3);
				if(u32_Err	!= UNFD_ST_SUCCESS)
				{
					goto Error;
				}

				nand_debug(0, 1, "Testing for Partial Mode\n");
				u32_Err = NCTEST_RWSinglePages_Partial_SWRepeat2(u32_Row, 3);
				if(u32_Err	!= UNFD_ST_SUCCESS)
				{
					goto Error;
				}

				nand_debug(0, 1, "Testing for LFSRTest\n");
				u32_Err = NCTEST_LFSRTest(u32_Row >> pNandDrv->u8_BlkPageCntBits);
				if(u32_Err != UNFD_ST_SUCCESS)
				{
					goto Error;
				}
				if(pNandDrv->u16_ECCType != ECC_TYPE_4BIT)
				{
					nand_debug(0, 1, "Testing for ECC_BCH_PageMode\n");
					u32_Err = NCTEST_ECC_BCH_PageMode(u32_Row);
					if(u32_Err != UNFD_ST_SUCCESS)
					{
						goto Error;
					}
				}


				u32_Err = NC_EraseBlk(u32_Row);
				if(u32_Err != UNFD_ST_SUCCESS)
				{
					nand_debug(0, 1, "Erase Fail\n");
					goto Error;
				}

				if(u8_1KECC == 0)
				{
					u32_Row += pNandDrv->u16_BlkPageCnt;
					continue;
				}

				TRY_1KB:
				if(u32_j >=ECC1KBCount)
				{
					u32_Row += pNandDrv->u16_BlkPageCnt;
					continue;
				}

				pNandDrv->u16_ECCType  = au8_ECCType1KB[u32_j];

				if(au16_1KBECCByteCnt[u32_j] % 4)
					pNandDrv->u16_SpareByteCnt = ((au16_1KBECCByteCnt[u32_j] / 4 + 1)	* 4 + (u32_k) * 4) * (pNandDrv->u16_PageByteCnt / 1024);
				else
					pNandDrv->u16_SpareByteCnt = (au16_1KBECCByteCnt[u32_j] + (u32_k) * 4) * (pNandDrv->u16_PageByteCnt / 1024);

				//pNandDrv->u16_SpareByteCnt = ((pNandDrv->u16_SpareByteCnt  / (pNandDrv->u16_PageByteCnt / 1024)) + ( 16 - (pNandDrv->u16_SpareByteCnt  / (pNandDrv->u16_PageByteCnt / 1024)) % 16)) * (pNandDrv->u16_PageByteCnt / 1024);

				if(pNandDrv->u16_PageByteCnt > NAND_PAGE_BYTE_CNT || pNandDrv->u16_SpareByteCnt > NAND_SPARE_BYTE_CNT)
					continue;

				nand_debug(0,1 , "Tesing Page Byte %d\n", pNandDrv->u16_PageByteCnt);
				nand_debug(0,1 , "Tesing Spare Byte %d\n", pNandDrv->u16_SpareByteCnt);
				nand_debug(0,1 , "Tesing  ECC Mode %d\n", pNandDrv->u16_ECCType);
				NC_ConfigNandFlashContext();
				u32_Err = NC_RegInit();
				if(u32_Err	!= UNFD_ST_SUCCESS)
				{
					nand_debug(0, 1, "Init fail\n");
					goto Error;
				}
				NC_Config();
				if(NAND_PAGE_BYTE_CNT > 0x200)
				{
					pNandDrv->u16_Reg48_Spare&= ~BIT_NC_ONE_COL_ADDR;
					NC_Config();
				}
				nand_debug(0, 1, "Testing for DMA\n");
				u32_Err = NCTEST_RWSinglePages(u32_Row,3);
				if(u32_Err	!=	UNFD_ST_SUCCESS)
				{
					goto Error;
				}
				nand_debug(0, 1, "Testing for RIU\n");

				u32_Err = NCTEST_RWSinglePages_RM(u32_Row,3);
				if(u32_Err	!= UNFD_ST_SUCCESS)
				{
					goto Error;
				}

				nand_debug(0, 1, "Testing for Partial Mode\n");
				u32_Err = NCTEST_RWSinglePages_Partial_SWRepeat2(u32_Row, 3);
				if(u32_Err	!= UNFD_ST_SUCCESS)
				{
					goto Error;
				}

				nand_debug(0, 1, "Testing for LFSRTest\n");
				u32_Err = NCTEST_LFSRTest(u32_Row >> pNandDrv->u8_BlkPageCntBits);
				if(u32_Err != UNFD_ST_SUCCESS)
				{
					goto Error;
				}

				nand_debug(0, 1, "Testing for ECC_BCH_PageMode\n");
				u32_Err = NCTEST_ECC_BCH_PageMode(u32_Row);
				if(u32_Err != UNFD_ST_SUCCESS)
				{
					goto Error;
				}

				u32_Err = NC_EraseBlk(u32_Row);
				if(u32_Err != UNFD_ST_SUCCESS)
				{
					nand_debug(0, 1, "Erase Fail\n");
					goto Error;
				}

				u32_Row += pNandDrv->u16_BlkPageCnt;
			}
		}
	}
	pNandDrv->u16_PageByteCnt = NAND_PAGE_BYTE_CNT;
	pNandDrv->u16_SpareByteCnt = NAND_SPARE_BYTE_CNT;
	pNandDrv->u16_ECCType = NAND_ECC_TYPE;
	NC_ConfigNandFlashContext();
	u32_Err = NC_RegInit();
	NC_Config();
	if(u32_Err  != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "Init fail\n");
		goto Error;
	}
	return UNFD_ST_SUCCESS;
Error:
	#if 0
	pNandDrv->u16_PageByteCnt = NAND_PAGE_BYTE_CNT;
	pNandDrv->u16_SpareByteCnt = NAND_SPARE_BYTE_CNT;
	pNandDrv->u16_ECCType = NAND_ECC_TYPE;
	NC_ConfigNandFlashContext();
	u32_Err = NC_Init();
	if(u32_Err  != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "Init fail\n");
	}
	#endif
	if(NC_EraseBlk(u32_Row) != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "Erase Fail\n");
	}
	return u32_Err;
}



#elif defined(NC_SEL_FCIE5) && NC_SEL_FCIE5

#define ECCCount  6
U8 au8_ECCType512B[] = {
	ECC_TYPE_8BIT, ECC_TYPE_16BIT, ECC_TYPE_24BIT, ECC_TYPE_32BIT, ECC_TYPE_40BIT, ECC_TYPE_60BIT
};
U8 au8_ECCType1KB[] = {
	ECC_TYPE_8BIT1KB,	ECC_TYPE_16BIT1KB,	ECC_TYPE_24BIT1KB,	ECC_TYPE_32BIT1KB,	ECC_TYPE_40BIT1KB, ECC_TYPE_60BIT1KB
};
U16 au16_ECCByteCnt[] = 
{
	14, 28, 42, 56, 70, 106
};

static U32 NCTEST_ECC_BCH_SCAN_ALL(U8 u8_BCHBitCnt, U32 u32_TestRow, U8 u8_IsMLC) // ok for BCH 4/8
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err, u32_i, u32_j;
	volatile U8  u8_Flag;

	U8  *au8_W, *au8_R, *au8_W_Corrupt;
	U8  *au8_WSpare, *au8_RSpare, *au8_WSpare_Corrupt;

	if(u8_IsMLC)
		u8_BCHBitCnt /= 2;

	nand_debug(0, 1, "BCH Correctable Bit : 0x%X\n", u8_BCHBitCnt);
	// ----------------------------
    // setup data
    // ----------------------------
	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;
	au8_W_Corrupt = (U8*)(DMA_W_ADDR + pNandDrv->u16_PageByteCnt);	
	au8_WSpare_Corrupt = (U8*)(DMA_W_SPARE_ADDR + pNandDrv->u16_SpareByteCnt);

	for (u32_i = 0; u32_i < pNandDrv->u16_PageByteCnt; u32_i++)
	{
		au8_W[u32_i] = (u32_i & 0xFF);
		//au8_W[u32_i] = ECC_TEST_PATTERN;
		au8_R[u32_i] = ~au8_W[u32_i];
	}
	au8_WSpare[0] = 0xFF;
	for (u32_i = 1; u32_i < pNandDrv->u16_SpareByteCnt; u32_i++)
	{
		//au8_WSpare[u32_i] = (u32_i & 0xFF);
		au8_WSpare[u32_i] = ECC_TEST_PATTERN;
		au8_RSpare[u32_i] = ~au8_WSpare[u32_i];
	}

	u32_Err = NC_EraseBlk(u32_TestRow);

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "ERROR: %s 1, ErrCode: 0x%08lX\n", __func__,u32_Err);
		return u32_Err;
	}
	pNandDrv->u16_Reg48_Spare |= BIT_NC_HW_AUTO_RANDOM_CMD_DISABLE;
	NC_Config();

	dump_mem(au8_WSpare, pNandDrv->u16_SpareByteCnt);
	#if 0
	nand_debug(0,1,"Write 1 3s\n");
	nand_hw_timer_delay(DELAY_1s_in_us);
	nand_debug(0,1,"Delay 1s\n");
	nand_hw_timer_delay(DELAY_1s_in_us);
	nand_debug(0,1,"Delay 1s\n");
	nand_hw_timer_delay(DELAY_1s_in_us);
	nand_debug(0,1,"Delay 1s\n");
	#endif	
	u32_Err = NC_WriteSectors(u32_TestRow, 0, au8_W, au8_WSpare, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "ERROR: %s 2, ErrCode: 0x%08lX\n", __func__,u32_Err);
		return u32_Err;
	}
	#if 0
	nand_debug(0,1,"Read 1  3s\n");
	nand_hw_timer_delay(DELAY_1s_in_us);
	nand_debug(0,1,"Delay 1s\n");
	nand_hw_timer_delay(DELAY_1s_in_us);
	nand_debug(0,1,"Delay 1s\n");
	nand_hw_timer_delay(DELAY_1s_in_us);
	nand_debug(0,1,"Delay 1s\n");
	#endif
	u32_Err = NC_ReadSectors(u32_TestRow, 0, au8_R, au8_RSpare, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "ERROR: %s 3, ErrCode: 0x%08lX\n", __func__,u32_Err);
		return u32_Err;
	}
	nand_debug(0, 1, "dump: \n");
	dump_mem(au8_RSpare, pNandDrv->u16_SpareByteCnt);

	for(u32_i=0; u32_i<pNandDrv->u16_SectorByteCnt; u32_i++)
		if(au8_W[u32_i] != au8_R[u32_i])
		{
			nand_debug(0, 0, "ERROR: %s 4, I:%lX W:%X R:%X\n",__func__,
				u32_i, au8_W[u32_i], au8_R[u32_i]);
			return UNFD_ST_ERR_DATA_CMP_FAIL;
		}
	if((pNandDrv->u16_Reg48_Spare & BIT_NC_SPARE_ECC_BYPASS) == 0)
	{
		for(u32_i=0; u32_i<pNandDrv->u16_SectorSpareByteCnt-pNandDrv->u16_ECCCodeByteCnt; u32_i++)
			if(au8_WSpare[u32_i] != au8_RSpare[u32_i])
			{
				nand_debug(0, 0, "ERROR: %s 5, I:%lX W:%X R:%X\n",__func__,
					u32_i, au8_WSpare[u32_i], au8_RSpare[u32_i]);
				return UNFD_ST_ERR_DATA_CMP_FAIL;
			}
	}

	// ----------------------------
    // corrupt data bits
    // ----------------------------
	u8_Flag = 0;
	memcpy(au8_WSpare, au8_RSpare, pNandDrv->u16_SpareByteCnt);
	if(pNandDrv->u16_Reg48_Spare & BIT_NC_SPARE_ECC_BYPASS)
	{
		au8_WSpare[0] = 0xFF;
		for(u32_i=1; u32_i<pNandDrv->u16_SectorSpareByteCnt-pNandDrv->u16_ECCCodeByteCnt; u32_i++)
			au8_WSpare[u32_i] = u32_i;
	}

	for(u32_j = 0; u32_j < (pNandDrv->u16_SectorByteCnt + pNandDrv->u16_SectorSpareByteCnt)* 8; u32_j +=u8_BCHBitCnt)
	{
		memcpy(au8_W_Corrupt, au8_W, pNandDrv->u16_SectorByteCnt);
		memcpy(au8_WSpare_Corrupt, au8_WSpare, pNandDrv->u16_SectorSpareByteCnt);
		for(u32_i = 0; u32_i < u8_BCHBitCnt; u32_i ++)
		{
			if((u32_j + u32_i) < pNandDrv->u16_SectorByteCnt * 8)
			{
				au8_W_Corrupt[(u32_j + u32_i)/8] = au8_W_Corrupt[(u32_j + u32_i)/8] ^ (1 << ((u32_j + u32_i) & 7) );
				//nand_debug(0, 1, "Corrupt Main Data I: 0x%X, Corrupt: 0x%X, Orig: 0x%X\n", (u32_j + u32_i)/8, au8_W_Corrupt[(u32_j + u32_i)/8], au8_W[(u32_j + u32_i)/8]);
			}
			else if(((u32_j + u32_i) >= pNandDrv->u16_SectorByteCnt * 8) && ((u32_j + u32_i) < (pNandDrv->u16_SectorByteCnt + pNandDrv->u16_SectorSpareByteCnt) * 8))
			{
				au8_WSpare_Corrupt[(u32_j + u32_i) / 8 - pNandDrv->u16_SectorByteCnt] = au8_WSpare_Corrupt[(u32_j + u32_i) / 8 - pNandDrv->u16_SectorByteCnt] ^ (1 << ((u32_j + u32_i) & 7) );
				//nand_debug(0, 1, "Corrupt Spare Data I: 0x%X, Corrupt: 0x%X, Orig: 0x%X\n", (u32_j + u32_i) / 8 - pNandDrv->u16_SectorByteCnt, au8_WSpare_Corrupt[(u32_j + u32_i) / 8 - pNandDrv->u16_SectorByteCnt], au8_WSpare[(u32_j + u32_i) / 8 - pNandDrv->u16_SectorByteCnt]);
			}
		}

		if(((u32_TestRow + u32_j/u8_BCHBitCnt +1) & pNandDrv->u16_BlkPageCntMask) == 0)
		{
			if(drvNAND_IsGoodBlk((u32_TestRow + u32_j/u8_BCHBitCnt +1) >> pNandDrv->u8_BlkPageCntBits) ==0)
				u32_TestRow += pNandDrv->u16_BlkPageCnt;
		
			u32_Err = NC_EraseBlk(u32_TestRow + u32_j/u8_BCHBitCnt +1);
			if (u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(0, 1, "ERROR: %s 5.9, ErrCode: 0x%08lX\n", __func__,u32_Err);
				return u32_Err;
			}
		}
		
		pNandDrv->u16_Reg50_EccCtrl |= BIT_NC_BYPASS_ECC;
		pNandDrv->u16_Reg48_Spare	|= BIT_NC_HW_AUTO_RANDOM_CMD_DISABLE;
	    	NC_Config();

		u32_Err = NC_WriteSectors(u32_TestRow + u32_j/u8_BCHBitCnt +1, 0, au8_W_Corrupt, au8_WSpare_Corrupt, 1);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(0, 1, "ERROR: %s 6, ErrCode: 0x%08lX\n", __func__,u32_Err);
			return u32_Err;
		}
		pNandDrv->u16_Reg50_EccCtrl &= ~BIT_NC_BYPASS_ECC;
		pNandDrv->u16_Reg48_Spare	|= BIT_NC_HW_AUTO_RANDOM_CMD_DISABLE;
		
		NC_Config();

		memset(au8_R, 0, pNandDrv->u16_SectorByteCnt);
		memset(au8_RSpare, 0, pNandDrv->u16_SectorSpareByteCnt);

		u32_Err = NC_ReadSectors(u32_TestRow + u32_j/u8_BCHBitCnt +1, 0, au8_R, au8_RSpare, 1);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			dump_mem(au8_R, pNandDrv->u16_SectorByteCnt);
			dump_mem(au8_RSpare, pNandDrv->u16_SectorSpareByteCnt);
			nand_debug(0, 1, "ERROR: %s 7, ErrCode: 0x%08lX\n", __func__, u32_Err);
			return u32_Err;
		}

		for(u32_i=0; u32_i<pNandDrv->u16_SectorByteCnt; u32_i++)
		{
			if(au8_W[u32_i] != au8_R[u32_i])
			{
				nand_debug(0, 1, "%s 8, I:%lX R:%X != %X\n",__func__,
					u32_i,  au8_R[u32_i],  au8_W[u32_i]);
				return UNFD_ST_ERR_DATA_CMP_FAIL;
			}
		}
		for(u32_i=0; u32_i<pNandDrv->u16_SectorSpareByteCnt; u32_i++)
		{
			if(pNandDrv->u16_Reg48_Spare & BIT_NC_SPARE_ECC_BYPASS)
			{
				if(au8_WSpare[u32_i] != au8_RSpare[u32_i] && u8_IsMLC == 0)
				{
					nand_debug(0, 1, "Warning :  au8_RSpare[0x%04lx]: 0x%02x != 0x%x\n", u32_i, au8_RSpare[u32_i], au8_WSpare[u32_i]);
				}
			}
			 else if(au8_RSpare[u32_i] != au8_WSpare[u32_i])
			 {
				nand_debug(0, 1, "%s 9, I:%lX R:%X != %X\n",__func__,
					u32_i,  au8_RSpare[u32_i], au8_WSpare[u32_i]);
				return UNFD_ST_ERR_DATA_CMP_FAIL;	 
			 }
		}		
	}
	
	return UNFD_ST_SUCCESS;
}


static U32 NCTEST_ALL_ECC_BCH(U32 u32_TestRow)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	//config all type of ecc
	U8 u8_ECCIdx, u8_SpareCntIdx;
	U32 u32_Err;

	//init PageSectorCnt for 512B ECC
	pNandDrv->u16_PageByteCnt = 0x800;
	pNandDrv->u16_SpareByteCnt = 0x100;			
	pNandDrv->u16_ECCType = au8_ECCType512B[0];
	NC_ConfigNandFlashContext();
	NC_RegInit();
	#if 1
	for(u8_ECCIdx = 0; u8_ECCIdx < ECCCount; u8_ECCIdx++)
	{	
		for(u8_SpareCntIdx = 0; u8_SpareCntIdx < 11; u8_SpareCntIdx++)
		{
			#if defined(ENABLE_32BIT_MACRO) && ENABLE_32BIT_MACRO		//HW limitation 4x mode SectorSpareByteCnt should be multiple of 4
			if(au16_ECCByteCnt[u8_ECCIdx] % 4)
				pNandDrv->u16_SpareByteCnt = ((au16_ECCByteCnt[u8_ECCIdx] / 4 + 1)  * 4 + (u8_SpareCntIdx + 1) * 4) * pNandDrv->u16_PageSectorCnt;
			else
				pNandDrv->u16_SpareByteCnt = (au16_ECCByteCnt[u8_ECCIdx] + (u8_SpareCntIdx + 1) * 4) * pNandDrv->u16_PageSectorCnt;
			#else
			pNandDrv->u16_SpareByteCnt = (au16_ECCByteCnt[u8_ECCIdx] + (u8_SpareCntIdx + 1) * 2) * pNandDrv->u16_PageSectorCnt;
			#endif
			nand_debug(0, 1, "Testing ECC Type 0x%X, Spare Size %d\n", au8_ECCType512B[u8_ECCIdx], pNandDrv->u16_SpareByteCnt);
			pNandDrv->u16_ECCType = au8_ECCType512B[u8_ECCIdx];
			NC_ConfigNandFlashContext();
			NC_RegInit();			

			pNandDrv->u16_Reg48_Spare |= BIT_NC_SPARE_ECC_BYPASS;
			NC_Config();
			nand_debug(0,1, "Spare ECC Bypass\n");
			u32_Err = NCTEST_ECC_BCH(pNandDrv->u16_ECCCorretableBit, u32_TestRow, 0);
			if(u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(0,  1, "%s fail with ECC Type %X\n", __func__,au8_ECCType512B[u8_ECCIdx]);
				return UNFD_ST_ERR_ECC_FAIL;
			}

			pNandDrv->u16_Reg48_Spare &= ~BIT_NC_SPARE_ECC_BYPASS;
			NC_Config();
			nand_debug(0,1, "No Spare ECC Bypass\n");
			u32_Err = NCTEST_ECC_BCH(pNandDrv->u16_ECCCorretableBit, u32_TestRow, 0);
			if(u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(0,  1, "%s fail with ECC Type %X\n", __func__,au8_ECCType512B[u8_ECCIdx]);
				return UNFD_ST_ERR_ECC_FAIL;
			}

			nand_debug(0, 1, "NCTEST_ECC_BCH_SCAN_ALL Test...\n");
			u32_Err = NCTEST_ECC_BCH_SCAN_ALL(pNandDrv->u16_ECCCorretableBit, u32_TestRow, 0);
			if (u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_ECC_BCH_SCAN_ALL fail, ErrCode: 0x%08lx\n", u32_Err);
				return UNFD_ST_ERR_ECC_FAIL;
			}

			nand_debug(0,1, "OK\n\n");
		}
	}
	#endif
	
	//init PageSectorCnt for 1KB ECC
	pNandDrv->u16_SpareByteCnt = 0x100;			
	pNandDrv->u16_ECCType = au8_ECCType1KB[0];
	NC_ConfigNandFlashContext();
	NC_RegInit();

	for(u8_ECCIdx = 0; u8_ECCIdx < ECCCount; u8_ECCIdx++)
	{	
		for(u8_SpareCntIdx = 0; u8_SpareCntIdx < 11; u8_SpareCntIdx++)
		{
			#if defined(ENABLE_32BIT_MACRO) && ENABLE_32BIT_MACRO		//HW limitation 4x mode SectorSpareByteCnt should be multiple of 4
			if(au16_ECCByteCnt[u8_ECCIdx] % 4)
				pNandDrv->u16_SpareByteCnt = ((au16_ECCByteCnt[u8_ECCIdx] / 4 + 1)  * 4 + (u8_SpareCntIdx + 1) * 4) * pNandDrv->u16_PageSectorCnt;
			else
				pNandDrv->u16_SpareByteCnt = (au16_ECCByteCnt[u8_ECCIdx] + (u8_SpareCntIdx + 1) * 4) * pNandDrv->u16_PageSectorCnt;
			#else
			pNandDrv->u16_SpareByteCnt = (au16_ECCByteCnt[u8_ECCIdx] + (u8_SpareCntIdx + 1) * 2) * pNandDrv->u16_PageSectorCnt;
			#endif

			nand_debug(0, 1, "Testing ECC Type 0x%X, Spare Size %d\n", au8_ECCType1KB[u8_ECCIdx], pNandDrv->u16_SpareByteCnt);
			pNandDrv->u16_ECCType = au8_ECCType1KB[u8_ECCIdx];
			NC_ConfigNandFlashContext();
			NC_RegInit();			

			pNandDrv->u16_Reg48_Spare |= BIT_NC_SPARE_ECC_BYPASS;
			NC_Config();
			nand_debug(0,1, "Spare ECC Bypass\n");
			u32_Err = NCTEST_ECC_BCH(pNandDrv->u16_ECCCorretableBit, u32_TestRow, 0);
			if(u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(0,  1, "%s fail with ECC Type %X\n", __func__,au8_ECCType1KB[u8_ECCIdx]);
				return UNFD_ST_ERR_ECC_FAIL;
			}

			pNandDrv->u16_Reg48_Spare &= ~BIT_NC_SPARE_ECC_BYPASS;
			NC_Config();

			nand_debug(0,1, "No Spare ECC Bypass\n");
			u32_Err = NCTEST_ECC_BCH(pNandDrv->u16_ECCCorretableBit, u32_TestRow, 0);
			if(u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(0,  1, "%s fail with ECC Type %X\n", __func__,au8_ECCType1KB[u8_ECCIdx]);
				return UNFD_ST_ERR_ECC_FAIL;
			}

			nand_debug(0, 1, "NCTEST_ECC_BCH_SCAN_ALL Test...\n");
			u32_Err = NCTEST_ECC_BCH_SCAN_ALL(pNandDrv->u16_ECCCorretableBit, u32_TestRow, 0);
			if (u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_ECC_BCH_SCAN_ALL fail, ErrCode: 0x%08lx\n", u32_Err);
				return UNFD_ST_ERR_ECC_FAIL;
			}

			nand_debug(0,1, "OK\n\n");
		}
	}

	pNandDrv->u16_PageByteCnt = NAND_PAGE_BYTE_CNT;
	pNandDrv->u16_SpareByteCnt = NAND_SPARE_BYTE_CNT;			
	pNandDrv->u16_ECCType = NAND_ECC_TYPE;
	NC_ConfigNandFlashContext();
	NC_RegInit();

	return UNFD_ST_SUCCESS;
}

static U32 NCTEST_ALL_ECC_BCH_MLC(U32 u32_TestRow)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	//config all type of ecc
	U8 u8_ECCIdx, u8_SpareCntIdx;
	U32 u32_Err;

	//init PageSectorCnt for 512B ECC
	pNandDrv->u16_PageByteCnt = 0x800;
	pNandDrv->u16_SpareByteCnt = 0x100;			
	pNandDrv->u16_ECCType = au8_ECCType512B[0];
	NC_ConfigNandFlashContext();
	NC_RegInit();
	#if 1
	for(u8_ECCIdx = 0; u8_ECCIdx < ECCCount; u8_ECCIdx++)
	{	
		for(u8_SpareCntIdx = 0; u8_SpareCntIdx < 5; u8_SpareCntIdx++)
		{
			#if defined(ENABLE_32BIT_MACRO) && ENABLE_32BIT_MACRO		//HW limitation 4x mode SectorSpareByteCnt should be multiple of 4
			if(au16_ECCByteCnt[u8_ECCIdx] % 4)
				pNandDrv->u16_SpareByteCnt = ((au16_ECCByteCnt[u8_ECCIdx] / 4 + 1)  * 4 + (u8_SpareCntIdx + 1) * 4) * pNandDrv->u16_PageSectorCnt;
			else
				pNandDrv->u16_SpareByteCnt = (au16_ECCByteCnt[u8_ECCIdx] + (u8_SpareCntIdx + 1) * 4) * pNandDrv->u16_PageSectorCnt;
			#else
			pNandDrv->u16_SpareByteCnt = (au16_ECCByteCnt[u8_ECCIdx] + (u8_SpareCntIdx + 1) * 2) * pNandDrv->u16_PageSectorCnt;
			#endif
			nand_debug(0, 1, "Testing ECC Type 0x%X, Spare Size %d\n", au8_ECCType512B[u8_ECCIdx], pNandDrv->u16_SpareByteCnt);
			pNandDrv->u16_ECCType = au8_ECCType512B[u8_ECCIdx];
			NC_ConfigNandFlashContext();
			NC_RegInit();			

			pNandDrv->u16_Reg48_Spare |= BIT_NC_SPARE_ECC_BYPASS;
			NC_Config();
			nand_debug(0,1, "Spare ECC Bypass\n");
			u32_Err = NCTEST_ECC_BCH(pNandDrv->u16_ECCCorretableBit, u32_TestRow, 1);
			if(u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(0,  1, "%s fail with ECC Type %X\n", __func__,au8_ECCType512B[u8_ECCIdx]);
				return UNFD_ST_ERR_ECC_FAIL;
			}

			pNandDrv->u16_Reg48_Spare &= ~BIT_NC_SPARE_ECC_BYPASS;
			NC_Config();
			nand_debug(0,1, "No Spare ECC Bypass\n");
			u32_Err = NCTEST_ECC_BCH(pNandDrv->u16_ECCCorretableBit, u32_TestRow, 1);
			if(u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(0,  1, "%s fail with ECC Type %X\n", __func__,au8_ECCType512B[u8_ECCIdx]);
				return UNFD_ST_ERR_ECC_FAIL;
			}

			nand_debug(0,1, "OK\n\n");
		}
	}
	#endif
	
	//init PageSectorCnt for 1KB ECC
	pNandDrv->u16_SpareByteCnt = 0x100;			
	pNandDrv->u16_ECCType = au8_ECCType1KB[0];
	NC_ConfigNandFlashContext();
	NC_RegInit();

	for(u8_ECCIdx = 0; u8_ECCIdx < ECCCount; u8_ECCIdx++)
	{	
		for(u8_SpareCntIdx = 0; u8_SpareCntIdx < 5; u8_SpareCntIdx++)
		{
			#if defined(ENABLE_32BIT_MACRO) && ENABLE_32BIT_MACRO		//HW limitation 4x mode SectorSpareByteCnt should be multiple of 4
			if(au16_ECCByteCnt[u8_ECCIdx] % 4)
				pNandDrv->u16_SpareByteCnt = ((au16_ECCByteCnt[u8_ECCIdx] / 4 + 1)  * 4 + (u8_SpareCntIdx + 1) * 4) * pNandDrv->u16_PageSectorCnt;
			else
				pNandDrv->u16_SpareByteCnt = (au16_ECCByteCnt[u8_ECCIdx] + (u8_SpareCntIdx + 1) * 4) * pNandDrv->u16_PageSectorCnt;
			#else
			pNandDrv->u16_SpareByteCnt = (au16_ECCByteCnt[u8_ECCIdx] + (u8_SpareCntIdx + 1) * 2) * pNandDrv->u16_PageSectorCnt;
			#endif

			nand_debug(0, 1, "Testing ECC Type 0x%X, Spare Size %d\n", au8_ECCType1KB[u8_ECCIdx], pNandDrv->u16_SpareByteCnt);
			pNandDrv->u16_ECCType = au8_ECCType1KB[u8_ECCIdx];
			NC_ConfigNandFlashContext();
			NC_RegInit();			

			pNandDrv->u16_Reg48_Spare |= BIT_NC_SPARE_ECC_BYPASS;
			NC_Config();
			nand_debug(0,1, "Spare ECC Bypass\n");
			u32_Err = NCTEST_ECC_BCH(pNandDrv->u16_ECCCorretableBit, u32_TestRow, 1);
			if(u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(0,  1, "%s fail with ECC Type %X\n", __func__,au8_ECCType1KB[u8_ECCIdx]);
				return UNFD_ST_ERR_ECC_FAIL;
			}

			pNandDrv->u16_Reg48_Spare &= ~BIT_NC_SPARE_ECC_BYPASS;
			NC_Config();

			nand_debug(0,1, "No Spare ECC Bypass\n");
			u32_Err = NCTEST_ECC_BCH(pNandDrv->u16_ECCCorretableBit, u32_TestRow, 1);
			if(u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(0,  1, "%s fail with ECC Type %X\n", __func__,au8_ECCType1KB[u8_ECCIdx]);
				return UNFD_ST_ERR_ECC_FAIL;
			}

			nand_debug(0,1, "OK\n\n");			
		}
	}

	pNandDrv->u16_PageByteCnt = NAND_PAGE_BYTE_CNT;
	pNandDrv->u16_SpareByteCnt = NAND_SPARE_BYTE_CNT;			
	pNandDrv->u16_ECCType = NAND_ECC_TYPE;
	NC_ConfigNandFlashContext();
	NC_RegInit();

	return UNFD_ST_SUCCESS;
}

#define PAGE_MODE_COUNT	5

U16 au16_PageByteCnt[]=
{
	512, 2048, 4096, 8192, 16384,
};

static U32 NCTEST_All_Page_Mode(void)
{	
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err, u32_i, u32_j, u32_k, u32_Row = 0;
	U8 u8_1KECC;
//	u32_Row =  pNandDrv->u16_BlkPageCnt;

	for(u32_i =0; u32_i < PAGE_MODE_COUNT; u32_i ++)
	{
		pNandDrv->u16_PageByteCnt = au16_PageByteCnt[u32_i];
		
		if(au16_PageByteCnt[u32_i] < 1024)
			u8_1KECC =0;
		else 
			u8_1KECC = 1;
		for(u32_j = 0; u32_j < ECCCount; u32_j ++)
		{
			for(u32_k = 1; u32_k < 11; u32_k ++)
			{
				//check if good block
				pNandDrv->u16_PageByteCnt = NAND_PAGE_BYTE_CNT;
				pNandDrv->u16_SpareByteCnt = NAND_SPARE_BYTE_CNT;
				pNandDrv->u16_ECCType = NAND_ECC_TYPE;
				NC_ResetFCIE();
				NC_ConfigNandFlashContext();
				u32_Err = NC_RegInit();
				if(u32_Err	!= UNFD_ST_SUCCESS)
				{
					nand_debug(0, 1, "Init fail\n");
					goto Error;
				}
				
				
#if 0
				nand_debug(0,1,"Delay 1s\n");
				nand_hw_timer_delay(DELAY_1s_in_us);
				nand_debug(0,1,"Delay 1s\n");
				nand_hw_timer_delay(DELAY_1s_in_us);
				nand_debug(0,1,"Delay 1s\n");
				nand_hw_timer_delay(DELAY_1s_in_us);
				nand_debug(0,1,"Delay 1s\n");
#endif
				while(drvNAND_IsGoodBlk(u32_Row >> pNandDrv->u8_BlkPageCntBits) == 0)
				{
					nand_debug(0,1, "Skip Bad PBA 0x%lX\n", u32_Row >> pNandDrv->u8_BlkPageCntBits);
					u32_Row += pNandDrv->u16_BlkPageCnt;
					if(u32_Row >= (pNandDrv->u16_BlkCnt << pNandDrv->u8_BlkPageCntBits))
						u32_Row = 0;
				}
				nand_debug(0,1, "Testing Row 0x%lX\n", u32_Row);
				pNandDrv->u16_PageByteCnt = au16_PageByteCnt[u32_i] ;
				pNandDrv->u16_ECCType  = au8_ECCType512B[u32_j];

				if(pNandDrv->u16_Reg58_DDRCtrl & BIT_NC_32B_MODE)
				{
					if(au16_ECCByteCnt[u32_j] % 4)
						pNandDrv->u16_SpareByteCnt = ((au16_ECCByteCnt[u32_j] / 4 + 1)	* 4 + (u32_k) * 4) * (pNandDrv->u16_PageByteCnt / 512);
					else
						pNandDrv->u16_SpareByteCnt = (au16_ECCByteCnt[u32_j] + (u32_k) * 4) * (pNandDrv->u16_PageByteCnt / 512);
				}
				else
				{
					pNandDrv->u16_SpareByteCnt = (au16_ECCByteCnt[u32_j] + (u32_k) * 2) * (pNandDrv->u16_PageByteCnt / 512);
				}

				if(pNandDrv->u16_PageByteCnt > NAND_PAGE_BYTE_CNT || pNandDrv->u16_SpareByteCnt > NAND_SPARE_BYTE_CNT)
				{
					if(u8_1KECC == 1)
						goto TRY_1KB;
					else
						continue;
				}

				nand_debug(0,1 , "Tesing Page Byte %d\n", pNandDrv->u16_PageByteCnt);
				nand_debug(0,1 , "Tesing Spare Byte %d\n", pNandDrv->u16_SpareByteCnt);
				nand_debug(0,1 , "Tesing  ECC Mode %d\n", pNandDrv->u16_ECCType);
				NC_ConfigNandFlashContext();
				u32_Err = NC_RegInit();
				if(u32_Err	!= UNFD_ST_SUCCESS)
				{
					nand_debug(0, 1, "Init fail\n");
					goto Error;
				}
				if(NAND_PAGE_BYTE_CNT > 0x200)
				{
					pNandDrv->u16_Reg48_Spare&= ~BIT_NC_ONE_COL_ADDR;
					NC_Config();
				}
				nand_debug(0, 1, "Testing for DMA\n");
				u32_Err = NCTEST_RWSinglePages(u32_Row,3);
				if(u32_Err	!=	UNFD_ST_SUCCESS)
				{
					goto Error;
				}
				nand_debug(0, 1, "Testing for RIU\n");
				
				u32_Err = NCTEST_RWSinglePages_RM(u32_Row,3);
				if(u32_Err	!= UNFD_ST_SUCCESS)
				{
					goto Error;
				}
				
				nand_debug(0, 1, "Testing for Partial Mode\n");
				u32_Err = NCTEST_RWSinglePages_Partial_SWRepeat2(u32_Row, 3);
				if(u32_Err	!= UNFD_ST_SUCCESS)
				{
					goto Error;
				}

				nand_debug(0, 1, "Testing for LFSRTest\n");
				u32_Err = NCTEST_LFSRTest(u32_Row >> pNandDrv->u8_BlkPageCntBits);
				if(u32_Err != UNFD_ST_SUCCESS)
				{
					goto Error;
				}
				
				nand_debug(0, 1, "Testing for ECC_BCH_PageMode\n");
				u32_Err = NCTEST_ECC_BCH_PageMode(u32_Row);
				if(u32_Err != UNFD_ST_SUCCESS)
				{
					goto Error;
				}
				
				u32_Err = NC_EraseBlk(u32_Row);
				if(u32_Err != UNFD_ST_SUCCESS)
				{
					nand_debug(0, 1, "Erase Fail\n");
					goto Error;
				}
				
				if(u8_1KECC == 0)
				{
					u32_Row += pNandDrv->u16_BlkPageCnt;				
					continue;
				}

				TRY_1KB:
				pNandDrv->u16_ECCType  = au8_ECCType1KB[u32_j];

				if(pNandDrv->u16_Reg58_DDRCtrl & BIT_NC_32B_MODE)
				{
					if(au16_ECCByteCnt[u32_j] % 4)
						pNandDrv->u16_SpareByteCnt = ((au16_ECCByteCnt[u32_j] / 4 + 1)	* 4 + (u32_k) * 4) * (pNandDrv->u16_PageByteCnt / 1024);
					else
						pNandDrv->u16_SpareByteCnt = (au16_ECCByteCnt[u32_j] + (u32_k) * 4) * (pNandDrv->u16_PageByteCnt / 1024);
				}
				else
				{
					pNandDrv->u16_SpareByteCnt = (au16_ECCByteCnt[u32_j] + (u32_k) * 2) * (pNandDrv->u16_PageByteCnt / 1024);
				}

				if(pNandDrv->u16_PageByteCnt > NAND_PAGE_BYTE_CNT || pNandDrv->u16_SpareByteCnt > NAND_SPARE_BYTE_CNT)
					continue;

				nand_debug(0,1 , "Tesing Page Byte %d\n", pNandDrv->u16_PageByteCnt);
				nand_debug(0,1 , "Tesing Spare Byte %d\n", pNandDrv->u16_SpareByteCnt);
				nand_debug(0,1 , "Tesing  ECC Mode %d\n", pNandDrv->u16_ECCType);
				NC_ConfigNandFlashContext();
				u32_Err = NC_RegInit();
				if(u32_Err	!= UNFD_ST_SUCCESS)
				{
					nand_debug(0, 1, "Init fail\n");
					goto Error;
				}
				if(NAND_PAGE_BYTE_CNT > 0x200)
				{
					pNandDrv->u16_Reg48_Spare&= ~BIT_NC_ONE_COL_ADDR;
					NC_Config();
				}
				nand_debug(0, 1, "Testing for DMA\n");
				u32_Err = NCTEST_RWSinglePages(u32_Row,3);
				if(u32_Err	!=	UNFD_ST_SUCCESS)
				{
					goto Error;
				}
				nand_debug(0, 1, "Testing for RIU\n");
				
				u32_Err = NCTEST_RWSinglePages_RM(u32_Row,3);
				if(u32_Err	!= UNFD_ST_SUCCESS)
				{
					goto Error;
				}
				
				nand_debug(0, 1, "Testing for Partial Mode\n");
				u32_Err = NCTEST_RWSinglePages_Partial_SWRepeat2(u32_Row, 3);
				if(u32_Err	!= UNFD_ST_SUCCESS)
				{
					goto Error;
				}

				nand_debug(0, 1, "Testing for LFSRTest\n");
				u32_Err = NCTEST_LFSRTest(u32_Row >> pNandDrv->u8_BlkPageCntBits);
				if(u32_Err != UNFD_ST_SUCCESS)
				{
					goto Error;
				}
				
				nand_debug(0, 1, "Testing for ECC_BCH_PageMode\n");
				u32_Err = NCTEST_ECC_BCH_PageMode(u32_Row);
				if(u32_Err != UNFD_ST_SUCCESS)
				{
					goto Error;
				}
				
				u32_Err = NC_EraseBlk(u32_Row);
				if(u32_Err != UNFD_ST_SUCCESS)
				{
					nand_debug(0, 1, "Erase Fail\n");
					goto Error;
				}
				
				u32_Row += pNandDrv->u16_BlkPageCnt;
			}
		}
	}
	pNandDrv->u16_PageByteCnt = NAND_PAGE_BYTE_CNT;
	pNandDrv->u16_SpareByteCnt = NAND_SPARE_BYTE_CNT;
	pNandDrv->u16_ECCType = NAND_ECC_TYPE;
	NC_ConfigNandFlashContext();
	u32_Err = NC_RegInit();
	if(u32_Err  != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "Init fail\n");
		goto Error;
	}
	return UNFD_ST_SUCCESS;
Error:
	#if 0
	pNandDrv->u16_PageByteCnt = NAND_PAGE_BYTE_CNT;
	pNandDrv->u16_SpareByteCnt = NAND_SPARE_BYTE_CNT;
	pNandDrv->u16_ECCType = NAND_ECC_TYPE;
	NC_ConfigNandFlashContext();
	u32_Err = NC_Init();
	if(u32_Err  != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "Init fail\n");
	}
	#endif
	NC_ResetFCIE();
	NC_Config();
	if(NC_EraseBlk(u32_Row) != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "Erase Fail\n");
	}		
	return u32_Err;
}


static U32 NCTEST_ZERO_ONE_CASE(void)
{	
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err, u32_i, u32_j, u32_TestRow = 0;
	volatile U16 u16_Reg42, u16_Reg4B, u16_Reg4C;
	U8  *au8_W, *au8_R;
	U8  *au8_WSpare, *au8_RSpare;
	// ----------------------------
	// setup data
	// ----------------------------
	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	for(u32_i = 0 ;u32_i < pNandDrv->u16_PageByteCnt; u32_i ++)
		au8_W[u32_i ] = 0;
	for(u32_i = 0 ;u32_i < pNandDrv->u16_SpareByteCnt; u32_i ++)
		au8_WSpare[u32_i ] = 0;

	u32_Err = NC_EraseBlk(u32_TestRow);
	if(u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1," Erase Error\n");
		return u32_Err;
	}

	nand_debug(0, 1, "Testing for all 0xff\n");

	u32_Err = NC_ReadPages(u32_TestRow, au8_R, au8_RSpare, 1);
	if(u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "Read Error 1\n");
		return u32_Err;
	}

	REG_READ_UINT16(NC_STAT_CHK,u16_Reg42);
	nand_debug(0,1, "REG 42 =  0x%X\n", u16_Reg42);
	if((u16_Reg42 & BIT_NC_ALLONE_FLAG) ==0)
	{
		nand_debug(0, 1, "Error All one Flag 1\n");
		return UNFD_ST_ERR_ECC_FAIL;
	}

	pNandDrv->u16_Reg50_EccCtrl |= BIT_NC_BYPASS_ECC;
	NC_Config();
	u32_Err = NC_WritePages(u32_TestRow, au8_W, au8_WSpare, 1);
	if(u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "Write Error 1\n");
		return u32_Err;		
	}

	nand_debug(0, 1, "Testing for all 0\n");	
	u32_Err = NC_ReadPages(u32_TestRow, au8_R, au8_RSpare, 1);
	if(u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "Read Error 1\n");
		return u32_Err; 	
	}
	pNandDrv->u16_Reg50_EccCtrl &=~ BIT_NC_BYPASS_ECC;
	NC_Config();
	REG_READ_UINT16(NC_STAT_CHK,u16_Reg42);
	nand_debug(0,1, "REG 42 =  0x%X\n", u16_Reg42);
	if((u16_Reg42 & BIT_NC_ALLZERO_FLAG) ==0)
	{
		nand_debug(0, 1, "Error All zero Flag 1\n");
		return UNFD_ST_ERR_ECC_FAIL;
	}

	//Enable Randomizer
	#if defined(FCIE_LFSR) && FCIE_LFSR
	NC_EnableLFSR();
	//read original 0xff 
	pNandDrv->u16_Reg50_EccCtrl |= BIT_NC_BYPASS_ECC;
	NC_Config();

	nand_debug(0, 1, "Testing for all 0xff before scramble\n");
	u32_Err = NC_ReadPages(u32_TestRow + 1, au8_R, au8_RSpare, 1);
	if(u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "Read Error 2\n");
		return u32_Err;
	}
	REG_READ_UINT16(NC_STAT_CHK,u16_Reg42);
	nand_debug(0,1, "REG 42 =  0x%X\n", u16_Reg42);
	if((u16_Reg42 & BIT_NC_SCRAM_ALLONE_FLAG) ==0)
	{
		nand_debug(0, 1, "Error Scramble All zero Flag 1\n");
		return UNFD_ST_ERR_ECC_FAIL;
	}
	//read original all 0
	nand_debug(0, 1, "Testing for all 0 before scramble\n");	
	u32_Err = NC_ReadPages(u32_TestRow, au8_R, au8_RSpare, 1);
	if(u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "Read Error 3\n");
		return u32_Err;
	}
	
	REG_READ_UINT16(NC_STAT_CHK,u16_Reg42);
	nand_debug(0,1, "REG 42 =  0x%X\n", u16_Reg42);
	if((u16_Reg42 & BIT_NC_SCRAM_ALLZERO_FLAG) ==0)
	{
		nand_debug(0, 1, "Error Scramble All zero Flag 1\n");
		return UNFD_ST_ERR_ECC_FAIL;
	}

	//randomizer all 0 

	u32_Err = NC_WritePages(u32_TestRow + 2, au8_W, au8_WSpare, 1);
	if(u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "Write Error 2\n");
		return u32_Err;
	}
	nand_debug(0, 1, "Testing for all 0 after scramble\n");

	u32_Err = NC_ReadPages(u32_TestRow + 2, au8_R, au8_RSpare, 1);
	if(u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "Read Error 4\n");
		return u32_Err;
	}
	
	REG_READ_UINT16(NC_STAT_CHK,u16_Reg42);
	nand_debug(0,1, "REG 42 =  0x%X\n", u16_Reg42);
	if((u16_Reg42 & BIT_NC_ALLZERO_FLAG) ==0)
	{
		nand_debug(0, 1, "Error  All zero Flag 2\n");
		return UNFD_ST_ERR_ECC_FAIL;
	}

	//randomizer all 0xff
	for(u32_i = 0 ;u32_i < pNandDrv->u16_PageByteCnt; u32_i ++)
		au8_W[u32_i ] = 0xFF;
	for(u32_i = 0 ;u32_i < pNandDrv->u16_SpareByteCnt; u32_i ++)
		au8_WSpare[u32_i ] = 0xFF;

	u32_Err = NC_WritePages(u32_TestRow + 3, au8_W, au8_WSpare, 1);
	if(u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "Write Error 3\n");
		return u32_Err;
	}
	nand_debug(0, 1, "Testing for all 0xff after scramble\n");

	u32_Err = NC_ReadPages(u32_TestRow + 3, au8_R, au8_RSpare, 1);
	if(u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "Read Error 5\n");
		return u32_Err;
	}
	
	REG_READ_UINT16(NC_STAT_CHK,u16_Reg42);
	nand_debug(0,1, "REG 42 =  0x%X\n", u16_Reg42);
	if((u16_Reg42 & BIT_NC_ALLONE_FLAG) ==0)
	{
		nand_debug(0, 1, "Error  All zero Flag 3\n");
		return UNFD_ST_ERR_ECC_FAIL;
	}
	pNandDrv->u16_Reg50_EccCtrl &= ~BIT_NC_BYPASS_ECC;
	NC_Config();	
	NC_DisableLFSR();
	#endif


	u32_TestRow = 4;

	for(u32_j = 1; u32_j <= 40; u32_j ++)
	{
		if((u32_TestRow & pNandDrv->u16_BlkPageCntMask) == 0)
		{
			u32_Err = NC_EraseBlk(u32_TestRow);
			if(u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(0, 1, "Erase Fail 2\n");
				return u32_Err;
			}
		}
		//randomizer all 0xff
		for(u32_i = 0 ;u32_i < pNandDrv->u16_PageByteCnt; u32_i ++)
			au8_W[u32_i ] = 0xFF;
		for(u32_i = 0 ;u32_i < pNandDrv->u16_SpareByteCnt; u32_i ++)
			au8_WSpare[u32_i ] = 0xFF;
	
		for(u32_i = 0 ;u32_i < u32_j; u32_i ++)
			au8_W[u32_i ] = 0xFE;

		for(u32_i = 0 ;u32_i < u32_j / 3; u32_i ++)
			au8_W[u32_i + pNandDrv->u16_SectorByteCnt * 2] = 0xFE;

		for(u32_i = 0 ;u32_i < u32_j / 2; u32_i ++)
			au8_W[u32_i  + pNandDrv->u16_SectorByteCnt] = 0xFE;
		
		pNandDrv->u16_Reg50_EccCtrl |= BIT_NC_BYPASS_ECC;
		NC_Config();

		u32_Err = NC_WritePages(u32_TestRow, au8_W, au8_WSpare, 1);
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(0, 1, "Write Fail 4\n");
			return u32_Err;
		}
		
		u32_Err = NC_ReadPages(u32_TestRow, au8_R, au8_RSpare, 1);
		
			if(u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(0, 1, "Read Error 6\n");
				return u32_Err;
		}

		REG_READ_UINT16(NC_ZERO_CNT,u16_Reg4B);
		nand_debug(0, 1,"Reg 4B =  0x%X\n", u16_Reg4B);
		if(u16_Reg4B !=  u32_j)
		{
			nand_debug(0,1, "1 read %d but expected %ld\n", u16_Reg4B, u32_j);
			return UNFD_ST_ERR_ECC_FAIL;
		}

		#if defined(FCIE_LFSR) && FCIE_LFSR
		NC_EnableLFSR();


	#if 0
	nand_debug(0,1,"Delay 1s\n");
	nand_hw_timer_delay(DELAY_1s_in_us);
	nand_debug(0,1,"Delay 1s\n");
	nand_hw_timer_delay(DELAY_1s_in_us);
	nand_debug(0,1,"Delay 1s\n");
	nand_hw_timer_delay(DELAY_1s_in_us);
	nand_debug(0,1,"Delay 1s\n");
	#endif	
	
		u32_Err = NC_ReadPages(u32_TestRow, au8_R, au8_RSpare, 1);
		
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(0, 1, "Read Error 7\n");
			return u32_Err;
		}

		REG_READ_UINT16(NC_ZERO_CNT_SCRAMBLE,u16_Reg4C);
		nand_debug(0,1,"Reg 4C =  0x%X\n", u16_Reg4C);
		if(u16_Reg4C !=  u32_j)
		{
			nand_debug(0,1, "2 read %d but expected %ld\n", u16_Reg4C, u32_j);
			return UNFD_ST_ERR_ECC_FAIL;
		}

		//write scrambled data
		u32_TestRow ++;
		u32_Err = NC_WritePages(u32_TestRow, au8_W, au8_WSpare, 1);
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(0, 1, "Write Fail 5\n");
			return u32_Err;
		}

		u32_Err = NC_ReadPages(u32_TestRow, au8_R, au8_RSpare, 1);
		
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(0, 1, "Read Error 8\n");
			return u32_Err;
		}

		REG_READ_UINT16(NC_ZERO_CNT,u16_Reg4B);
		nand_debug(0,1,"Reg 4B =  0x%X\n", u16_Reg4B);
		if(u16_Reg4B !=  u32_j)
		{
			nand_debug(0,1, "3 read %d but expected %ld\n", u16_Reg4B, u32_j);
			return UNFD_ST_ERR_ECC_FAIL;
		}
		
		NC_DisableLFSR();
		#endif 
		pNandDrv->u16_Reg50_EccCtrl &= ~BIT_NC_BYPASS_ECC;
		NC_Config();
		u32_TestRow ++;
	}
	return UNFD_ST_SUCCESS;
}

static U32 NCTEST_Zero_Bit_Count(void)
{	
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err, u32_i, u32_j, u32_k, u32_TestRow = 0, u32_0Cnt, u32_Max0Cnt;
	volatile U16  u16_Reg4B, u16_Reg4C;
	U8  *au8_W, *au8_R, *au8_RTmp, *au8_RTmp2;
	U8  *au8_WSpare, *au8_RSpare;
	// ----------------------------
	// setup data
	// ----------------------------
	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_RTmp = (U8*)(DMA_R_ADDR + pNandDrv->u16_PageByteCnt);
	au8_RTmp2 = (U8*)(DMA_R_ADDR + pNandDrv->u16_PageByteCnt * 3);	
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	u32_TestRow = 0;

	for(u32_j = 1; u32_j <= 40; u32_j ++)
	{
		if((u32_TestRow & pNandDrv->u16_BlkPageCntMask) == 0)
		{
			u32_Err = NC_EraseBlk(u32_TestRow);
			if(u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(0, 1, "Erase Fail 2\n");
				return u32_Err;
			}
		}
		//randomizer all 0xff
		for(u32_i = 0 ;u32_i < pNandDrv->u16_PageByteCnt; u32_i ++)
			au8_W[u32_i ] = 0xFF;
		for(u32_i = 0 ;u32_i < pNandDrv->u16_SpareByteCnt; u32_i ++)
			au8_WSpare[u32_i ] = 0xFF;
	
		for(u32_i = 0 ;u32_i < u32_j; u32_i ++)
			au8_W[u32_i ] = 0xFE;

		for(u32_i = 0 ;u32_i < u32_j / 3; u32_i ++)
			au8_W[u32_i + pNandDrv->u16_SectorByteCnt * 2] = 0xFE;

		for(u32_i = 0 ;u32_i < u32_j / 2; u32_i ++)
			au8_W[u32_i  + pNandDrv->u16_SectorByteCnt] = 0xFE;
		
		pNandDrv->u16_Reg50_EccCtrl |= BIT_NC_BYPASS_ECC;
		NC_Config();

		//nand_debug(0, 1, "u32_j %d No LFSR Write Page Row %X\n", u32_j,u32_TestRow);
		u32_Err = NC_WritePages(u32_TestRow, au8_W, au8_WSpare, 1);
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(0, 1, "Write Fail 4\n");
			return u32_Err;
		}
		//nand_debug(0, 1, "u32_j %d No LFSR Read Page Row %X\n", u32_j,u32_TestRow);
		u32_Err = NC_ReadPages(u32_TestRow, au8_R, au8_RSpare, 1);
		if(u32_Err != UNFD_ST_SUCCESS)
		{
				nand_debug(0, 1, "Read Error 6\n");
				return u32_Err;
		}

		REG_READ_UINT16(NC_ZERO_CNT,u16_Reg4B);
		//for each sector count max zero bit
		
		nand_debug(0,1,"Reg 4B =  0x%X\n", u16_Reg4B);
		u32_Max0Cnt = 0;
		for(u32_i = 0; u32_i < pNandDrv->u16_PageSectorCnt; u32_i ++)
		{
			u32_0Cnt = 0;
			for(u32_k = 0; u32_k < pNandDrv->u16_SectorByteCnt; u32_k ++)
			{
				u32_0Cnt +=NCTEST_Zerobits_In_Byte(au8_R[u32_i * pNandDrv->u16_SectorByteCnt + u32_k]);
			}
			for(u32_k = 0; u32_k < pNandDrv->u16_SectorSpareByteCnt; u32_k ++)
			{
				u32_0Cnt +=NCTEST_Zerobits_In_Byte(au8_RSpare[u32_i * pNandDrv->u16_SectorSpareByteCnt + u32_k]);
			}
			if(u32_0Cnt >= u32_Max0Cnt)
				u32_Max0Cnt = u32_0Cnt;
		}

		if(u16_Reg4B != u32_Max0Cnt)
		{
			nand_debug(0,1, "2 read %d but expected %ld\n", u16_Reg4B, u32_Max0Cnt);
			return UNFD_ST_ERR_ECC_FAIL;
		}
		#if defined(FCIE_LFSR) && FCIE_LFSR
		NC_EnableLFSR();
		#if 1
		//nand_debug(0, 1, "u32_j %d LFSR Read Page Row %X\n", u32_j,u32_TestRow);		
		u32_Err = NC_ReadPages(u32_TestRow, au8_R, au8_RSpare, 1);
		
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(0, 1, "Read Error 7\n");
			return u32_Err;
		}

		for(u32_i = 0;  u32_i < pNandDrv->u16_PageSectorCnt; u32_i ++)
		{
			for(u32_k = 0; u32_k < pNandDrv->u16_SectorByteCnt + pNandDrv->u16_SectorSpareByteCnt; u32_k ++)
			{
				if(u32_k < pNandDrv->u16_SectorByteCnt)
					au8_RTmp[u32_i  * (pNandDrv->u16_SectorByteCnt + pNandDrv->u16_SectorSpareByteCnt) + u32_k] = au8_R[u32_i * pNandDrv->u16_SectorByteCnt + u32_k];
				else
					au8_RTmp[u32_i  * (pNandDrv->u16_SectorByteCnt + pNandDrv->u16_SectorSpareByteCnt) + u32_k] = au8_RSpare[(u32_i * pNandDrv->u16_SectorSpareByteCnt) + u32_k - pNandDrv->u16_SectorByteCnt];
			}
		}

		#if defined(ENABLE_8BIT_MACRO) && ENABLE_8BIT_MACRO
		if(pNandDrv->u16_Reg58_DDRCtrl & BIT_DDR_MASM)
			LFSR1_NLines_NIOs_SectorUnit((U16*)au8_RTmp,(U16*)au8_RTmp2, pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt,(u32_TestRow & pNandDrv->u16_BlkPageCntMask), 16, 16);
		else
			LFSR1_NLines_NIOs_SectorUnit((U16*)au8_RTmp,(U16*)au8_RTmp2, pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt,(u32_TestRow & pNandDrv->u16_BlkPageCntMask), 16, 8);
		#elif defined(ENABLE_32BIT_MACRO) && ENABLE_32BIT_MACRO
		if(pNandDrv->u16_Reg58_DDRCtrl & BIT_NC_32B_MODE)
			LFSR1_NLines_NIOs_SectorUnit((U16*)au8_RTmp,(U16*)au8_RTmp2, pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt,(u32_TestRow & pNandDrv->u16_BlkPageCntMask), 32, 32);
		else
			LFSR1_NLines_NIOs_SectorUnit((U16*)au8_RTmp,(U16*)au8_RTmp2, pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt,(u32_TestRow & pNandDrv->u16_BlkPageCntMask), 16, 8);
		#endif

		REG_READ_UINT16(NC_ZERO_CNT_SCRAMBLE,u16_Reg4C);
		u32_Max0Cnt = 0;
		for(u32_i = 0; u32_i < pNandDrv->u16_PageSectorCnt; u32_i ++)
		{
			u32_0Cnt = 0;
			for(u32_k = 0; u32_k < (pNandDrv->u16_SectorByteCnt +  pNandDrv->u16_SectorSpareByteCnt); u32_k ++)
			{
				u32_0Cnt +=NCTEST_Zerobits_In_Byte(au8_RTmp2[u32_i * (pNandDrv->u16_SectorByteCnt +  pNandDrv->u16_SectorSpareByteCnt) + u32_k]);
			}
			if(u32_0Cnt >= u32_Max0Cnt)
				u32_Max0Cnt = u32_0Cnt;
		}		
		nand_debug(0,1,"Reg 4C =  0x%X\n", u16_Reg4C);
		if(u16_Reg4C !=  u32_Max0Cnt)
		{
			nand_debug(0,1, "2 read %d but expected %ld\n", u16_Reg4C, u32_Max0Cnt);
			dump_mem(au8_RTmp2, pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt);
			return UNFD_ST_ERR_ECC_FAIL;
		}
		#endif
		//write scrambled data
		u32_TestRow ++;
		//nand_debug(0, 1, "u32_j %d LFSR Write Page Row %X\n", u32_j,u32_TestRow);		
		
		u32_Err = NC_WritePages(u32_TestRow, au8_W, au8_WSpare, 1);
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(0, 1, "Write Fail 5\n");
			return u32_Err;
		}
		
		//nand_debug(0, 1, "u32_j %d LFSR Read Page Row %X\n", u32_j,u32_TestRow);		

		u32_Err = NC_ReadPages(u32_TestRow, au8_R, au8_RSpare, 1);
		
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(0, 1, "Read Error 8\n");
			return u32_Err;
		}

		REG_READ_UINT16(NC_ZERO_CNT,u16_Reg4B);
		
		nand_debug(0,1,"Reg 4B =  0x%X\n", u16_Reg4B);
		u32_Max0Cnt = 0;
		for(u32_i = 0; u32_i < pNandDrv->u16_PageSectorCnt; u32_i ++)
		{
			u32_0Cnt = 0;
			for(u32_k = 0; u32_k < pNandDrv->u16_SectorByteCnt; u32_k ++)
			{
				u32_0Cnt +=NCTEST_Zerobits_In_Byte(au8_R[u32_i * pNandDrv->u16_SectorByteCnt + u32_k]);
			}
			for(u32_k = 0; u32_k < pNandDrv->u16_SectorSpareByteCnt; u32_k ++)
			{
				u32_0Cnt +=NCTEST_Zerobits_In_Byte(au8_RSpare[u32_i * pNandDrv->u16_SectorSpareByteCnt + u32_k]);
			}
			if(u32_0Cnt >= u32_Max0Cnt)
				u32_Max0Cnt = u32_0Cnt;
		}

		if(u16_Reg4B != u32_Max0Cnt)
		{
			nand_debug(0,1, "2 read %d but expected %ld\n", u16_Reg4B, u32_Max0Cnt);
			return UNFD_ST_ERR_ECC_FAIL;
		}

		NC_DisableLFSR();
		#endif 
		pNandDrv->u16_Reg50_EccCtrl &= ~BIT_NC_BYPASS_ECC;
		NC_Config();
		u32_TestRow ++;
	}
	return UNFD_ST_SUCCESS;
}


static U32 NCTEST_MIU_BURST(void)
{
	U32 u32_Err;
	U16 u16_i;

	for (u16_i = 0; u16_i < 3; u16_i ++)
	{
		//set burst length
		nand_debug(0, 1, "Testing Burst Setting %X\n", u16_i);
		REG_SET_BITS_UINT16(NC_MIU_CTRL,( u16_i & 3));
		u32_Err = NCTEST_RWSinglePages(0, 5);
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			return u32_Err;
		}
	}
	REG_CLR_BITS_UINT16(NC_MIU_CTRL, BIT_MIU_BURST_EN_MASK);
	return UNFD_ST_SUCCESS;
}

static U32 NCTEST_Bist(U32 u32_StartRowIdx, U8 u8_BistPat)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;

	U8  *au8_W, *au8_R;
	U8  *au8_WSpare, *au8_RSpare;
	U32 u32_i;
	U32  *au32_W, *au32_R;
	U16 u16_Reg;

	/* setup buffers */
	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	au32_W = (U32*)au8_W;
	au32_R = (U32*)au8_R;

	REG_CLR_BITS_UINT16(NC_BIST_MODE, BIT_SEL_BIST_PAT_MASK);
	REG_SET_BITS_UINT16(NC_BIST_MODE, (u8_BistPat<<BIT_SEL_BIST_PAT_SHIFT));

	for(u32_i=0 ; u32_i<pNandDrv->u16_SpareByteCnt ; u32_i++)
	{
		au8_WSpare[u32_i] = 0xFF;
	}

	switch(u8_BistPat)
	{
		case 0:
			for(u32_i=0 ; u32_i<pNandDrv->u16_PageByteCnt*pNandDrv->u16_BlkPageCnt/4 ; u32_i++)
			{
				au32_W[u32_i] = 0x00000000;
			}
			break;
		case 1:
			for(u32_i=0 ; u32_i<pNandDrv->u16_PageByteCnt*pNandDrv->u16_BlkPageCnt/4 ; u32_i++)
			{
				au32_W[u32_i] = 0xFFFFFFFF;
			}
			break;
		case 2:
			for(u32_i=0 ; u32_i<pNandDrv->u16_PageByteCnt*pNandDrv->u16_BlkPageCnt/4 ; u32_i++)
			{
				au32_W[u32_i] = 0xFF00FF00;
			}
			break;			
		case 3:
			for(u32_i=0 ; u32_i<pNandDrv->u16_PageByteCnt*pNandDrv->u16_BlkPageCnt/4 ; u32_i++)
			{
				au32_W[u32_i] = 0x00FF00FF;
			}
			break;	
		case 4:
			for(u32_i=0 ; u32_i<pNandDrv->u16_PageByteCnt*pNandDrv->u16_BlkPageCnt/4 ; u32_i++)
			{
				au32_W[u32_i] = 0x55555555;
			}
			break;	
		case 5:
			for(u32_i=0 ; u32_i<pNandDrv->u16_PageByteCnt*pNandDrv->u16_BlkPageCnt/4 ; u32_i++)
			{
				au32_W[u32_i] = 0xAAAAAAAA;
			}
			break;	
		case 6:
			for(u32_i=0 ; u32_i<pNandDrv->u16_PageByteCnt*pNandDrv->u16_BlkPageCnt/4 ; u32_i++)
			{
				au32_W[u32_i] = 0xAA55AA55;
			}
			break;	
		case 7:
			for(u32_i=0 ; u32_i<pNandDrv->u16_PageByteCnt*pNandDrv->u16_BlkPageCnt/4 ; u32_i++)
			{
				au32_W[u32_i] = 0x55AA55AA;
			}
			break;	
		case 8:
			for(u32_i=0 ; u32_i<pNandDrv->u16_PageByteCnt*pNandDrv->u16_BlkPageCnt/4 ; u32_i++)
			{
				au32_W[u32_i] = 0xA55AA55A;
			}
			break;	
		case 9:
			for(u32_i=0 ; u32_i<pNandDrv->u16_PageByteCnt*pNandDrv->u16_BlkPageCnt/4 ; u32_i++)
			{
				au32_W[u32_i] = 0x5AA55AA5;
			}
			break;	
		case 10:
			for(u32_i=0 ; u32_i<pNandDrv->u16_PageByteCnt*pNandDrv->u16_BlkPageCnt ; u32_i++)
			{
				au8_W[u32_i] = (U8)u32_i;
			}
			break;	
		case 11:
			for(u32_i=0 ; u32_i<pNandDrv->u16_PageByteCnt*pNandDrv->u16_BlkPageCnt ; u32_i++)
			{
				au8_W[u32_i] = 0xFF-(U8)u32_i;
			}
			break;	
		default:
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: Bist pattern out of range\n");
			return UNFD_ST_ERR_INVALID_PARAM;
			break;
	}

	/* erase the first blk */

	u32_Err = NC_EraseBlk(u32_StartRowIdx &~ pNandDrv->u16_BlkPageCntMask);

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_Bist 0, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	REG_SET_BITS_UINT16(NC_FUN_CTL, BIT_BIST_MODE);
	u32_Err = NC_WritePages(u32_StartRowIdx, 0, 0, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_Bist 1, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}
	
	REG_CLR_BITS_UINT16(NC_FUN_CTL, BIT_BIST_MODE);
	u32_Err = NC_ReadPages(u32_StartRowIdx, au8_R, au8_RSpare, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_Bist 2, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	/* compare test pattern */
	if(NCTEST_DataCompare(au8_W, au8_R, pNandDrv->u16_PageByteCnt))
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_Bist 3 \n");
		return UNFD_ST_ERR_DATA_CMP_FAIL;
	}

	REG_SET_BITS_UINT16(NC_FUN_CTL, BIT_BIST_MODE);
	u32_Err = NC_ReadPages(u32_StartRowIdx, 0, 0, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_Bist 4, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}
	u16_Reg = REG(NC_BIST_MODE);
	REG_CLR_BITS_UINT16(NC_FUN_CTL, BIT_BIST_MODE);
	if((u16_Reg & BIT_BIST_ERR_FLAG) == BIT_BIST_ERR_FLAG)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_Bist 5 \n");
		return UNFD_ST_ERR_DATA_CMP_FAIL;
	}

	/* erase the first blk */

	u32_Err = NC_EraseBlk(u32_StartRowIdx &~ pNandDrv->u16_BlkPageCntMask);

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_Bist 6, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	REG_SET_BITS_UINT16(NC_FUN_CTL, BIT_BIST_MODE);
	u32_Err = NC_WritePages(u32_StartRowIdx, 0, 0, pNandDrv->u16_BlkPageCnt);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_Bist 7, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}
	
	REG_CLR_BITS_UINT16(NC_FUN_CTL, BIT_BIST_MODE);
	u32_Err = NC_ReadPages(u32_StartRowIdx, au8_R, au8_RSpare, pNandDrv->u16_BlkPageCnt);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_Bist 8, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	/* compare test pattern */
	if(NCTEST_DataCompare(au8_W, au8_R, pNandDrv->u16_PageByteCnt*pNandDrv->u16_BlkPageCnt))
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_Bist 9 \n");
		return UNFD_ST_ERR_DATA_CMP_FAIL;
	}

	REG_SET_BITS_UINT16(NC_FUN_CTL, BIT_BIST_MODE);
	u32_Err = NC_ReadPages(u32_StartRowIdx, 0, 0, pNandDrv->u16_BlkPageCnt);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_Bist 10, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}
	u16_Reg = REG(NC_BIST_MODE);
	REG_CLR_BITS_UINT16(NC_FUN_CTL, BIT_BIST_MODE);
	if((u16_Reg & BIT_BIST_ERR_FLAG) == BIT_BIST_ERR_FLAG)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_Bist 11 \n");
		return UNFD_ST_ERR_DATA_CMP_FAIL;
	}
	return UNFD_ST_SUCCESS;
}

static U32 NCTEST_BistCmdQue(U32 u32_StartRowIdx, U8 u8_BistPat)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();  
	U16 u16_Reg;
	U32 u32_Count;
	U32 u32_Err;

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x00), 0x0000);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x01),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x63);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x02), 0xffff);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x03),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x60);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x04), 0x0000);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x05),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x3F);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x06), 0x0001);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x07),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x3F);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x08), 0x0001);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x09),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x61);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x0A), 0x0009);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x0B),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x63);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x0C), u8_BistPat<<12);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x0D),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x36);
	
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x0E), 0x000B);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x0F),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x43);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x10), 0x0000);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x11),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x44);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x12), u32_StartRowIdx & 0xFFFF);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x13),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x44);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x14), u32_StartRowIdx >> 16);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x15),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x44);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x16), 0x0020);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x17),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x43);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x18), (NAND_RW_ADR_CYCLE_CNT<< 8) | (CMD_0x80));
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x19),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x44);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x1A), (CMD_0x10 << 8) | ACT_SER_DOUT);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x1B),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x44);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x1C), (CMD_0x70 << 8) | ACT_WAITRB);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x1D),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x44);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x1E), (ACT_REPEAT << 8) | ACT_CHKSTATUS);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x1F),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x44);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x20), ACT_BREAK);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x21),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x44);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x22), 0x0018);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x23),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x43);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x24), 0x40-1);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x25),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x44);
	
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x26), 0x0001);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x27),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x45);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x28), 0x0000);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x29),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WINT);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x2A), 0x0001);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x2B),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x60);
//---------------------------------------------------------------------------------------
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x2C), 0x0020);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x2D),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x43);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x2E), (NAND_RW_ADR_CYCLE_CNT<< 8) | (CMD_0x00));
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x2F),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x44);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x30), (ACT_WAITRB << 8) | CMD_0x30);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x31),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x44);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x32), (ACT_REPEAT << 8) | ACT_SER_DIN);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x33),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x44);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x34), ACT_BREAK);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x35),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x44);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x36), 0x0018);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x37),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x43);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x38), 0x40-1);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x39),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x44);


	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x3A), 0x0001);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x3B),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x45);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x3C), 0x0000);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x3D),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WINT);

	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x3E), 0x0000);
	REG_WRITE_UINT16(GET_REG_ADDR(FCIE_REG_PWS_BASE_ADDR, 0x3F),
					 PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_STOP);

	nand_hw_timer_delay(HW_TIMER_DELAY_1ms);

	u32_Err = NC_EraseBlk(u32_StartRowIdx &~ pNandDrv->u16_BlkPageCntMask);

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_BistCmdQue, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	REG_WRITE_UINT16(NC_PWR_SAVE_CTL, BIT_PWR_SAVE_MODE
					 | BIT_SD_PWR_SAVE_RIU
					 | BIT_PWR_SAVE_INT_EN
					 | BIT_SD_PWR_SAVE_RST);

	for (u32_Count=0; u32_Count < (DELAY_1s_in_us*20); u32_Count++)
	{
		REG_READ_UINT16(NC_PWR_SAVE_CTL, u16_Reg);
		if ((u16_Reg & 
			(BIT_PWR_SAVE_MODE_INT|BIT_RIU_SAVE_EVENT|BIT_SD_PWR_SAVE_RST|BIT_PWR_SAVE_INT_EN|BIT_SD_PWR_SAVE_RIU|BIT_PWR_SAVE_MODE))
			== (BIT_PWR_SAVE_MODE_INT|BIT_RIU_SAVE_EVENT|BIT_SD_PWR_SAVE_RST|BIT_PWR_SAVE_INT_EN|BIT_SD_PWR_SAVE_RIU|BIT_PWR_SAVE_MODE))
		{
			REG_READ_UINT16(NC_MIE_EVENT, u16_Reg);
			if((u16_Reg & BIT_NC_JOB_END) == BIT_NC_JOB_END)
			{
				REG_SET_BITS_UINT16(NC_MIE_EVENT, BIT_NC_JOB_END);
				break;
			}
		}
		nand_hw_timer_delay(HW_TIMER_DELAY_1us);
	}

	if(u32_Count == (DELAY_1s_in_us*20))
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: timeout on waiting Reg[BIT_NC_POWER_SAVE]\n");
		return UNFD_ST_ERR_RST_TIMEOUT;
	}

	REG_READ_UINT16(NC_PWR_SAVE_CTL, u16_Reg);
	nand_debug(UNFD_DEBUG_LEVEL_HIGH, 0, "NC_PWRSAVE_CTL: 0x%04x\n", u16_Reg);

	REG_READ_UINT16(NC_BIST_MODE, u16_Reg);
	nand_debug(UNFD_DEBUG_LEVEL_HIGH, 0, "NC_BIST_MODE: 0x%04x\n", u16_Reg);

	REG_WRITE_UINT16(NC_PWR_SAVE_CTL, BIT_PWR_SAVE_MODE_INT);	
	REG_WRITE_UINT16(NC_PWR_SAVE_CTL, 0);
	
	REG_CLR_BITS_UINT16(NC_FUN_CTL, BIT_BIST_MODE);
	u16_Reg = REG(NC_BIST_MODE);
	if((u16_Reg & BIT_BIST_ERR_FLAG) == BIT_BIST_ERR_FLAG)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_BistCmdQue bist fail\n");
		return UNFD_ST_ERR_DATA_CMP_FAIL;
	}	

	return UNFD_ST_SUCCESS;
}

static U32 NCTEST_NandBoot(U32 u32_StartRowIdx)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;
	U32 u32_ByteIdx;
	U16 u16_SpareByteCnt;

	U8  *au8_W, *au8_R;
	U8  *au8_WSpare, *au8_RSpare;



	/* setup buffers */
	au8_W = (U8*)DMA_W_SRAM_ADDR;
	au8_R = (U8*)DMA_R_SRAM_ADDR;
	au8_WSpare = (U8*)DMA_W_SRAM_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SRAM_SPARE_ADDR;

	/* W/R/C each page */
	/* erase the first blk */

	u32_Err = NC_EraseBlk(u32_StartRowIdx &~ pNandDrv->u16_BlkPageCntMask);

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_NandBoot 0, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	/* init test pattern */
	for (u32_ByteIdx = 0; u32_ByteIdx < pNandDrv->u16_PageByteCnt; u32_ByteIdx++)
	{
		if (pNandDrv->u8_IfECCTesting)
			au8_W[u32_ByteIdx] = ECC_TEST_PATTERN;
		else
			au8_W[u32_ByteIdx] = u32_ByteIdx + 1;

		au8_R[u32_ByteIdx] = ~au8_W[u32_ByteIdx];
		#if 0
		if(u32_ByteIdx<0x20)
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "set: [%2u]: adr:%X val:%02X  adr:%X val:%02X\n",
			    u32_ByteIdx, &au8_W[u32_ByteIdx], au8_W[u32_ByteIdx],
			    &au8_R[u32_ByteIdx], au8_R[u32_ByteIdx]);
		#endif
	}

	for (u32_ByteIdx = 0; u32_ByteIdx < pNandDrv->u16_SpareByteCnt; u32_ByteIdx++)
	{
		if (pNandDrv->u8_IfECCTesting)
			au8_WSpare[u32_ByteIdx] = ECC_TEST_PATTERN;
		else
			au8_WSpare[u32_ByteIdx] = u32_ByteIdx + 1 ;

		au8_RSpare[u32_ByteIdx] = ~au8_WSpare[u32_ByteIdx];
	}
	#if 0
	pNandDrv->u16_Reg50_EccCtrl &=~ BIT_NC_BYPASS_ECC;
	NC_Config();
	#endif

	REG_SET_BITS_UINT16(NC_FUN_CTL, BIT_BOOT_MODE);
	REG_SET_BITS_UINT16(NC_BOOT_MODE, BIT_NAND_BOOT_EN|BIT_BOOT_SRAM_SEL);

	u32_Err = NC_WritePages(u32_StartRowIdx, au8_W, au8_WSpare, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_NandBoot 1, ErrCode: 0x%08lx\n", u32_Err);
		REG_CLR_BITS_UINT16(NC_FUN_CTL, BIT_BOOT_MODE);
		REG_CLR_BITS_UINT16(NC_BOOT_MODE, BIT_NAND_BOOT_EN|BIT_BOOT_SRAM_SEL);
		return u32_Err;
	}
	#if 0
	pNandDrv->u16_Reg50_EccCtrl |= BIT_NC_BYPASS_ECC;
	NC_Config();
	#endif
	
	/* read test pattern */
	u32_Err = NC_ReadPages(u32_StartRowIdx, au8_R, au8_RSpare, 1);
	REG_CLR_BITS_UINT16(NC_FUN_CTL, BIT_BOOT_MODE);
	REG_CLR_BITS_UINT16(NC_BOOT_MODE, BIT_NAND_BOOT_EN|BIT_BOOT_SRAM_SEL);	
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		dump_mem(au8_R, pNandDrv->u16_PageByteCnt);
		
		dump_mem(au8_RSpare, pNandDrv->u16_SpareByteCnt);
		if(NCTEST_DataCompare(au8_W, au8_R, pNandDrv->u16_PageByteCnt))
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_NandBoot 2 \n");
			return UNFD_ST_ERR_DATA_CMP_FAIL;
		}
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_NandBoot 3, ErrCode: 0x%08lx\n", u32_Err);

		return u32_Err;
	}
	// [CAUTION]: if the above 2 of nand_translate_DMA_address_Ex, data area must be handled later.
	//nand_translate_DMA_address_Ex((U32)sgau8_RBuf, pNandDrv->u16_PageByteCnt);
	//nand_translate_DMA_address_Ex((U32)sgau8_RSpareBuf, pNandDrv->u16_PageByteCnt);

	/* compare test pattern */
	if(NCTEST_DataCompare(au8_W, au8_R, pNandDrv->u16_PageByteCnt))
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_NandBoot 4 \n");
		REG_CLR_BITS_UINT16(NC_FUN_CTL, BIT_BOOT_MODE);
		REG_CLR_BITS_UINT16(NC_BOOT_MODE, BIT_NAND_BOOT_EN|BIT_BOOT_SRAM_SEL);
		return UNFD_ST_ERR_DATA_CMP_FAIL;
	}

	u16_SpareByteCnt = pNandDrv->u16_SpareByteCnt;
	#if SPARE640B_CIFD512B_PATCH
	if(u16_SpareByteCnt > 0x200)
		u16_SpareByteCnt = (0x200/pNandDrv->u16_SectorSpareByteCnt)*pNandDrv->u16_SectorSpareByteCnt;
	#endif
	for (u32_ByteIdx = 0; u32_ByteIdx < u16_SpareByteCnt; u32_ByteIdx++)
	{
		if (u32_ByteIdx == pNandDrv->u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt +
				pNandDrv->u16_SectorSpareByteCnt * (u32_ByteIdx / pNandDrv->u16_SectorSpareByteCnt))
		{
			u32_ByteIdx += pNandDrv->u16_ECCCodeByteCnt - 1;
			continue;
		}

		if (au8_WSpare[u32_ByteIdx] != au8_RSpare[u32_ByteIdx])
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_NandBoot, spare, Row: 0x%08lx, Col: 0x%04lx, W: 0x%02x, R: 0x%02x\n",
					u32_StartRowIdx, u32_ByteIdx, au8_WSpare[u32_ByteIdx], au8_RSpare[u32_ByteIdx]);
			REG_CLR_BITS_UINT16(NC_FUN_CTL, BIT_BOOT_MODE);
			REG_CLR_BITS_UINT16(NC_BOOT_MODE, BIT_NAND_BOOT_EN|BIT_BOOT_SRAM_SEL);	
			return UNFD_ST_ERR_DATA_CMP_FAIL;
		}
	}

	nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "au8_W->\n");
	dump_mem(au8_W, 16);
	nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "au8_WSpare->\n");	
	dump_mem(au8_WSpare, 16);
	nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "au8_R->\n");	
	dump_mem(au8_R, 16);
	nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "au8_RSpare->\n");	
	dump_mem(au8_RSpare, 16);
		
	return UNFD_ST_SUCCESS;
}


U32 NCTEST_ReadLatchTiming(void)
{
	NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();
	U16 u16_i, u16_j, u16_Reg57_RELatch;
	U32 u32_Err;
	U8 au8_ID[NAND_ID_BYTE_CNT];

	memcpy(au8_ID, pNandDrv->au8_ID, NAND_ID_BYTE_CNT);
	u16_Reg57_RELatch = pNandDrv->u16_Reg57_RELatch;
	for(u16_i = 0 ; u16_i < 8 ; u16_i ++)
	{
		pNandDrv->u16_Reg57_RELatch &= ~(BIT_NC_LATCH_DATA_MASK);
		pNandDrv->u16_Reg57_RELatch |= (u16_i << 1) &BIT_NC_LATCH_DATA_MASK;
		pNandDrv->u16_Reg57_RELatch &= ~(BIT_NC_LATCH_STS_MASK);
		pNandDrv->u16_Reg57_RELatch |= (u16_i << 5) & BIT_NC_LATCH_STS_MASK;
		NC_Config();		
		u32_Err = NC_ReadID();
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(0, 1, "ReadID Error with ErrCode 0x%lX\n", u32_Err);
			return u32_Err;
		}
		for(u16_j = 0; u16_j < NAND_ID_BYTE_CNT; u16_j++)
		{
			if(pNandDrv->au8_ID[u16_j] != au8_ID[u16_j])
			{
				nand_debug(0, 1, "Compare ID failure @ idx 0x%X; found 0x%X, but expected 0x%X\n", u16_j, pNandDrv->au8_ID[u16_j], au8_ID[u16_j]);
				break;
			}
		}
	}
	memcpy(pNandDrv->au8_ID, au8_ID, NAND_ID_BYTE_CNT);	
	pNandDrv->u16_Reg57_RELatch = u16_Reg57_RELatch;
	NC_Config();
	return UNFD_ST_SUCCESS;
}

static U32 NCTEST_CheckFirstEccErrorPage(U16 u16_PBA)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;
	U32 u32_ByteIdx, u32_DataByteCnt, u32_SpareByteCnt;
	U32 u32_PageCnt, u32_StartRowIdx, u32_PageIdx;
	U32 *au32_W, *au32_R;
	U8  *au8_WSpare, *au8_RSpare;
	U16 u16_1stErrPage;

	u32_StartRowIdx = u16_PBA << pNandDrv->u8_BlkPageCntBits;
	u32_PageCnt = pNandDrv->u16_BlkPageCnt;
	/* check parameters */
	#if 0
	if (((u32_StartRowIdx + u32_PageCnt) &~ pNandDrv->u16_BlkPageCntMask) !=
			(u32_StartRowIdx &~ pNandDrv->u16_BlkPageCntMask))
	#else
    if(u32_StartRowIdx + u32_PageCnt > pNandDrv->u16_BlkPageCnt +
	    ((u32_StartRowIdx>>pNandDrv->u8_BlkPageCntBits)<<pNandDrv->u8_BlkPageCntBits))
	#endif
	{
		nand_debug(0,1,"%lX %lX\n", u32_StartRowIdx, u32_PageCnt);
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 0, ErrCode: 0x%08x\n",
				UNFD_ST_ERR_INVALID_PARAM);
		return UNFD_ST_ERR_INVALID_PARAM;
	}

	/* setup buffers */
	au32_W = (U32*)DMA_W_ADDR;
	au32_R = (U32*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	u32_DataByteCnt = u32_PageCnt << pNandDrv->u8_PageByteCntBits;

	/* NOTE: when use RepeatCnt, for the Spare area is still using the first Spare size byte cnt. */
	u32_SpareByteCnt = pNandDrv->u16_SpareByteCnt;

	nand_debug(0,1, "EraseBlk\n");
	/* erase first blk */
	u32_Err = NC_EraseBlk(u32_StartRowIdx &~ pNandDrv->u16_BlkPageCntMask);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 0, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}
	nand_debug(0,1, "Init Pattern\n");

	/* init test pattern */
	for (u32_ByteIdx = 0; u32_ByteIdx < u32_DataByteCnt >> 2; u32_ByteIdx++)
	{
		au32_W[u32_ByteIdx] = 0xFF ^ ((u32_ByteIdx&1)?0xFF:0x00); //u32_ByteIdx + 1;
		au32_R[u32_ByteIdx] = ~au32_W[u32_ByteIdx];
	}

	for (u32_ByteIdx = 0; u32_ByteIdx < u32_SpareByteCnt; u32_ByteIdx++)
	{
		au8_WSpare[u32_ByteIdx] = 0xFF ^ ((u32_ByteIdx&1)?0xFF:0x00); //u32_ByteIdx + 1;
		au8_RSpare[u32_ByteIdx] = ~au8_WSpare[u32_ByteIdx];
	}
	au8_WSpare[0] = 0xFF;

	nand_debug(0,1, "Write pattern\n");

	/* write test pattern */
	//pNandDrv->u16_Reg48_Spare &= ~BIT_NC_SPARE_DEST_MIU;
	//NC_Config();
	u32_Err = NC_WritePages(u32_StartRowIdx, (U8*)au32_W, (U8*)au8_WSpare, u32_PageCnt);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 2, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	nand_debug(0,1, "Read pattern\n");

	/* read test pattern */
	//pNandDrv->u16_Reg48_Spare |= BIT_NC_SPARE_DEST_MIU;
	//NC_Config();
	u32_Err = NC_ReadPages(u32_StartRowIdx, (U8*)au32_R, (U8*)au8_RSpare, u32_PageCnt);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		dump_mem((U8*)au32_R, pNandDrv->u16_PageByteCnt);
		dump_mem((U8*)au8_RSpare, pNandDrv->u16_SpareByteCnt);
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 3, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}
	// [CAUTION]: if the above 2 of nand_translate_DMA_address_Ex, data area must be handled later.
	//nand_translate_DMA_address_Ex((U32)sgau32_RBuf, pNandDrv->u16_PageByteCnt);
	//nand_translate_DMA_address_Ex((U32)sgau8_RSpareBuf, pNandDrv->u16_PageByteCnt);
	nand_debug(0,1, "Compare pattern\n");

	/* compare test pattern */
	if(NCTEST_DataCompare((U8*)au32_W, (U8*)au32_R, u32_DataByteCnt))
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 4 \n");
	    return UNFD_ST_ERR_DATA_CMP_FAIL;
	}
	nand_debug(0,1, "Compare pattern 2\n");

	#if SPARE640B_CIFD512B_PATCH
	if(u32_SpareByteCnt > 0x200)
		u32_SpareByteCnt = (0x200/pNandDrv->u16_SectorSpareByteCnt)*pNandDrv->u16_SectorSpareByteCnt;
	#endif
	for(u32_ByteIdx = 0; u32_ByteIdx < u32_SpareByteCnt; u32_ByteIdx++)
	{
		if (u32_ByteIdx == pNandDrv->u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt +
				pNandDrv->u16_SectorSpareByteCnt * (u32_ByteIdx / pNandDrv->u16_SectorSpareByteCnt))
		{
			u32_ByteIdx += pNandDrv->u16_ECCCodeByteCnt - 1;
			continue;
		}

		//if(au8_WSpare[u32_ByteIdx&pNandDrv->u16_SpareByteCntMask] != au8_RSpare[u32_ByteIdx])
		if(au8_WSpare[u32_ByteIdx] != au8_RSpare[u32_ByteIdx])
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 5, Col: 0x%04lx, W: 0x%02x, R: 0x%02x\n",
					 u32_ByteIdx,
					au8_WSpare[u32_ByteIdx], au8_RSpare[u32_ByteIdx]);
			return UNFD_ST_ERR_DATA_CMP_FAIL;
		}
	}

	//Begin corrupt each page from last page

	memset(au32_W, 0x0, pNandDrv->u16_PageByteCnt);
	memset(au8_WSpare, 0xFF, pNandDrv->u16_SpareByteCnt);
	for(u32_PageIdx = 0; u32_PageIdx < pNandDrv->u16_BlkPageCnt; u32_PageIdx ++)
	{
		u32_Err = NC_WritePages(u32_StartRowIdx + pNandDrv->u16_BlkPageCnt - 1 - u32_PageIdx, (U8*)au32_W, au8_WSpare, 1);
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 6, ErrCode: 0x%08lx\n", u32_Err);
			return u32_Err;		
		}

		u32_Err = NC_ReadPages(u32_StartRowIdx, (U8*)au32_R, au8_WSpare, u32_PageCnt);
		if(u32_Err != UNFD_ST_ERR_ECC_FAIL)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 7, ErrCode: 0x%08lx\n", u32_Err);
			return UNFD_ST_ERR_DATA_CMP_FAIL;					
		}
		REG_READ_UINT16(NC_1ST_ECC_ERR_PAGE, u16_1stErrPage);
		if(u16_1stErrPage != pNandDrv->u16_BlkPageCnt - 1 - u32_PageIdx)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 8, 1st Ecc Err should be 0x%lX, but 0x%X read\n", pNandDrv->u16_BlkPageCnt - 1 - u32_PageIdx, u16_1stErrPage);
			return UNFD_ST_ERR_DATA_CMP_FAIL;			
		}
	}

	u32_Err = NC_EraseBlk(u32_StartRowIdx &~ pNandDrv->u16_BlkPageCntMask);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 9, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	return UNFD_ST_SUCCESS;
}

#define DMA_PAGE_LEN1 	3
#define DMA_PAGE_LEN2 	6
#define DMA_PAGE_LEN3		9
static ADMA_DESC_t ADMADesc[128];


static U8	au8_MainDesTable[8*128];

static U32 NCTEST_RWMultiplePages_OneTimeADMA(U32 u32_StartRowIdx)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;
	U32 u32_ByteIdx, u32_DataByteCnt, u32_SpareByteCnt;
	U32 u32_PageCnt = DMA_PAGE_LEN1 + DMA_PAGE_LEN2 + DMA_PAGE_LEN3;

	U32 *au32_W, *au32_R;
	U32 *au32_W1, *au32_R1;
	U32 *au32_W2, *au32_R2;	
	U8  *au8_WSpare, *au8_RSpare;
	U8  *au8_WSpare1, *au8_RSpare1;
	U8  *au8_WSpare2, *au8_RSpare2;
	U8	*pu8_DesTable = au8_MainDesTable;	

	/* check parameters */
	#if 0
	if (((u32_StartRowIdx + u32_PageCnt) &~ pNandDrv->u16_BlkPageCntMask) !=
			(u32_StartRowIdx &~ pNandDrv->u16_BlkPageCntMask))
	#else
    if(u32_StartRowIdx + u32_PageCnt > pNandDrv->u16_BlkPageCnt +
	    ((u32_StartRowIdx>>pNandDrv->u8_BlkPageCntBits)<<pNandDrv->u8_BlkPageCntBits))
	#endif
	{
		nand_debug(0,1,"%lX %lX\n", u32_StartRowIdx, u32_PageCnt);
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 0, ErrCode: 0x%08x\n",
				UNFD_ST_ERR_INVALID_PARAM);
		return UNFD_ST_ERR_INVALID_PARAM;
	}

	// setup 3 different dram buffers for ADMA
	
	/* setup buffers */
	au32_W = (U32*)DMA_W_ADDR;
	au32_R = (U32*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;
	/* setup buffers */
	au32_W1 = (U32*)(DMA_W_ADDR  + 2 *  pNandDrv->u16_PageByteCnt * DMA_PAGE_LEN1);
	au32_R1 = (U32*)(DMA_R_ADDR + 2 * pNandDrv->u16_PageByteCnt * DMA_PAGE_LEN1);
	au8_WSpare1 = (U8*)(DMA_W_SPARE_ADDR + 2 *  pNandDrv->u16_SpareByteCnt * DMA_PAGE_LEN1);
	au8_RSpare1 = (U8*)(DMA_R_SPARE_ADDR + 2 * pNandDrv->u16_SpareByteCnt * DMA_PAGE_LEN1 );
	/* setup buffers */
	au32_W2 = (U32*)((U32)au32_W1 + (pNandDrv->u16_PageByteCnt * DMA_PAGE_LEN2) + 2 *  pNandDrv->u16_PageByteCnt * DMA_PAGE_LEN2 );
	au32_R2 = (U32*)((U32)au32_R1 + (pNandDrv->u16_PageByteCnt * DMA_PAGE_LEN2) + 2 *  pNandDrv->u16_PageByteCnt * DMA_PAGE_LEN2 );
	au8_WSpare2 = (U8*)((U32)au8_WSpare1 + (pNandDrv->u16_SpareByteCnt * DMA_PAGE_LEN2) + 2 *  pNandDrv->u16_SpareByteCnt * DMA_PAGE_LEN2 );
	au8_RSpare2 = (U8*)((U32)au8_RSpare1 + (pNandDrv->u16_SpareByteCnt * DMA_PAGE_LEN2) + 2 *  pNandDrv->u16_SpareByteCnt * DMA_PAGE_LEN2 );

	/* erase first blk */
	#if 1
	u32_Err = NC_EraseBlk(u32_StartRowIdx &~ pNandDrv->u16_BlkPageCntMask);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 0, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}
	#endif

	u32_DataByteCnt = DMA_PAGE_LEN1 << pNandDrv->u8_PageByteCntBits;

	/* NOTE: when use RepeatCnt, for the Spare area is still using the first Spare size byte cnt. */
	u32_SpareByteCnt = pNandDrv->u16_SpareByteCnt;

	/* init test pattern */
	for (u32_ByteIdx = 0; u32_ByteIdx < u32_DataByteCnt >> 2; u32_ByteIdx++)
	{
		au32_W[u32_ByteIdx] = 0xFF ^ ((u32_ByteIdx&1)?0xFF:0x00); //u32_ByteIdx + 1;
		au32_R[u32_ByteIdx] = ~au32_W[u32_ByteIdx];
	}

	for (u32_ByteIdx = 0; u32_ByteIdx < u32_SpareByteCnt; u32_ByteIdx++)
	{
		au8_WSpare[u32_ByteIdx] = 0xFF ^ ((u32_ByteIdx&1)?0xFF:0x00); //u32_ByteIdx + 1;
		au8_RSpare[u32_ByteIdx] = ~au8_WSpare[u32_ByteIdx];
	}
	//parse address and length to adma table, one adma record is 64 bit(8 byte)
	
	u32_DataByteCnt = DMA_PAGE_LEN2 << pNandDrv->u8_PageByteCntBits;

	/* init test pattern */
	for (u32_ByteIdx = 0; u32_ByteIdx < u32_DataByteCnt >> 2; u32_ByteIdx++)
	{
		au32_W1[u32_ByteIdx] =( 0xFF ^ ((u32_ByteIdx&1)?0xFF:0x00)) + 1; //u32_ByteIdx + 1;
		au32_R1[u32_ByteIdx] = ~au32_W[u32_ByteIdx];
	}

	for (u32_ByteIdx = 0; u32_ByteIdx < u32_SpareByteCnt; u32_ByteIdx++)
	{
		au8_WSpare1[u32_ByteIdx] = (0xFF ^ ((u32_ByteIdx&1)?0xFF:0x00)) + 1; //u32_ByteIdx + 1;
		au8_RSpare1[u32_ByteIdx] = ~au8_WSpare[u32_ByteIdx];
	}


	u32_DataByteCnt = DMA_PAGE_LEN3 << pNandDrv->u8_PageByteCntBits;

	/* init test pattern */
	for (u32_ByteIdx = 0; u32_ByteIdx < u32_DataByteCnt >> 2; u32_ByteIdx++)
	{
		au32_W2[u32_ByteIdx] = (0xFF ^ ((u32_ByteIdx&1)?0xFF:0x00)) + 3; //u32_ByteIdx + 1;
		au32_R2[u32_ByteIdx] = ~au32_W[u32_ByteIdx];
	}

	for (u32_ByteIdx = 0; u32_ByteIdx < u32_SpareByteCnt; u32_ByteIdx++)
	{
		au8_WSpare2[u32_ByteIdx] = (0xFF ^ ((u32_ByteIdx&1)?0xFF:0x00)) + 3; //u32_ByteIdx + 1;
		au8_RSpare2[u32_ByteIdx] = ~au8_WSpare[u32_ByteIdx];
	}

	drvNAND_ParseAddrToADMA((U8*)au32_W,DMA_PAGE_LEN1<< pNandDrv->u8_PageByteCntBits, 
		WRITE_TO_NAND, &ADMADesc[0],0);

	drvNAND_ParseAddrToADMA((U8*)au32_W1,DMA_PAGE_LEN2 << pNandDrv->u8_PageByteCntBits, 
		WRITE_TO_NAND, &ADMADesc[1],0);

	drvNAND_ParseAddrToADMA((U8*)au32_W2,DMA_PAGE_LEN3 << pNandDrv->u8_PageByteCntBits, 
		WRITE_TO_NAND, &ADMADesc[2],1);

	pu8_DesTable = (U8*)ADMADesc;

	nand_debug(0,1, "Write pattern\n");

	/* write test pattern */
	//pNandDrv->u16_Reg48_Spare &= ~BIT_NC_SPARE_DEST_MIU;
	//NC_Config();
	#if 1
	u32_Err = NC_ADMAWritePages(u32_StartRowIdx, (U8*)pu8_DesTable, (U8*)au8_WSpare, u32_PageCnt);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 2, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}
	#endif
	#if 0
	u32_Err = NC_WritePages(u32_StartRowIdx, (U8*)pu8_DesTable, (U8*)au8_WSpare, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 2, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}
	#endif
	#if 0
	u32_Err = NC_WritePages(u32_StartRowIdx, (U8*)au32_W, (U8*)au8_WSpare, DMA_PAGE_LEN1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 2, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}
	#endif

	nand_debug(0,1, "Read pattern\n");
	

	drvNAND_ParseAddrToADMA((U8*)au32_R,DMA_PAGE_LEN1<< pNandDrv->u8_PageByteCntBits, 
		READ_FROM_NAND, &ADMADesc[0],0);

	drvNAND_ParseAddrToADMA((U8*)au32_R1,DMA_PAGE_LEN2<< pNandDrv->u8_PageByteCntBits, 
		READ_FROM_NAND, &ADMADesc[1],0);

	drvNAND_ParseAddrToADMA((U8*)au32_R2,DMA_PAGE_LEN3<< pNandDrv->u8_PageByteCntBits, 
		READ_FROM_NAND, &ADMADesc[2],1);

	pu8_DesTable = (U8*)ADMADesc;

	//NC_ResetFCIE();
	/* read test pattern */
	//pNandDrv->u16_Reg48_Spare |= BIT_NC_SPARE_DEST_MIU;
	//NC_Config();
	#if 1
	u32_Err = NC_ADMAReadPages(u32_StartRowIdx, (U8*)pu8_DesTable, (U8*)au8_RSpare, u32_PageCnt, 0);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 3, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}
	#else
	u32_Err = NC_ReadPages(u32_StartRowIdx, (U8*)au32_R, (U8*)au8_RSpare, DMA_PAGE_LEN1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 3.1, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}	
	u32_Err = NC_ReadPages(u32_StartRowIdx +DMA_PAGE_LEN1 , (U8*)au32_R1, (U8*)au8_RSpare1, DMA_PAGE_LEN2);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 3.2, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}	
	u32_Err = NC_ReadPages(u32_StartRowIdx + DMA_PAGE_LEN1 + DMA_PAGE_LEN2, (U8*)au32_R2, (U8*)au8_RSpare2, DMA_PAGE_LEN3);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 3.3, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	#endif
	// [CAUTION]: if the above 2 of nand_translate_DMA_address_Ex, data area must be handled later.
	//nand_translate_DMA_address_Ex((U32)sgau32_RBuf, pNandDrv->u16_PageByteCnt);
	//nand_translate_DMA_address_Ex((U32)sgau8_RSpareBuf, pNandDrv->u16_PageByteCnt);
	nand_debug(0,1, "Compare pattern\n");

	/* compare test pattern */
	if(NCTEST_DataCompare((U8*)au32_W, (U8*)au32_R, DMA_PAGE_LEN1 << pNandDrv->u8_PageByteCntBits))
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 4.1 \n");
		return UNFD_ST_ERR_DATA_CMP_FAIL;
	}
	/* compare test pattern */
	if(NCTEST_DataCompare((U8*)au32_W1, (U8*)au32_R1, DMA_PAGE_LEN2 << pNandDrv->u8_PageByteCntBits))
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 4.2 \n");
		return UNFD_ST_ERR_DATA_CMP_FAIL;
	}
	/* compare test pattern */
	if(NCTEST_DataCompare((U8*)au32_W2, (U8*)au32_R2, DMA_PAGE_LEN3 << pNandDrv->u8_PageByteCntBits))
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 4.3 \n");
		return UNFD_ST_ERR_DATA_CMP_FAIL;
	}

	#if 0
	#if SPARE640B_CIFD512B_PATCH
	if(u32_SpareByteCnt > 0x200)
		u32_SpareByteCnt = (0x200/pNandDrv->u16_SectorSpareByteCnt)*pNandDrv->u16_SectorSpareByteCnt;
	#endif
	for(u32_ByteIdx = 0; u32_ByteIdx < u32_SpareByteCnt; u32_ByteIdx++)
	{
		if (u32_ByteIdx == pNandDrv->u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt +
				pNandDrv->u16_SectorSpareByteCnt * (u32_ByteIdx / pNandDrv->u16_SectorSpareByteCnt))
		{
			u32_ByteIdx += pNandDrv->u16_ECCCodeByteCnt - 1;
			continue;
		}

		//if(au8_WSpare[u32_ByteIdx&pNandDrv->u16_SpareByteCntMask] != au8_RSpare[u32_ByteIdx])
		if(au8_WSpare[u32_ByteIdx] != au8_RSpare[u32_ByteIdx])
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_OneTime 5, Col: 0x%04x, W: 0x%02x, R: 0x%02x\n",
					 u32_ByteIdx,
					au8_WSpare[u32_ByteIdx], au8_RSpare[u32_ByteIdx]);
			return UNFD_ST_ERR_DATA_CMP_FAIL;
		}
	}
	#endif

	return UNFD_ST_SUCCESS;
}


#if defined(FCIE_ZDEC_TEST) && FCIE_ZDEC_TEST
U8  u8_decompress[128*1024];
ZDecDescriptor_t p_ZDecOutput_st[128] UNFD_ALIGN1;
ZDecDescriptor_t p_ZDecDesc_st[128] UNFD_ALIGN1;

static U32 NCTEST_ZDEC(U32 u32_StartRowIdx, U8 * squashfs_test_img, U32 squashfs_test_img_len, U8* decompression_image, U32 decompressed_size)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U8  *au8_W, *au8_R;
	U8  *au8_W1, *au8_R1;
	U8  *au8_W2, *au8_R2;	
	U8  *au8_WSpare, *au8_RSpare;
	U8  *au8_WSpare1, *au8_RSpare1;
	U8  *au8_WSpare2, *au8_RSpare2;	
	U32 u32_err;
	U32 u32_i;
	U32 u32_blk_addr;
	U32 u32_index;
	U32 u32_totalTime, u32_nandtotalTime;
	U32 u32_compressed_size;
	U32 u32_uncompressed_size;
	U32 u32_blk_count;
	U32 u32_tmp_blk_count;
	int s32_decode_size;
	U32 u32_count = 0;
	U32 u32_time_count = 0;
	U32 u32_ZDecOutputAddr;
	U32 u32_ZDecDescAddr;
	U32 u32_DecompressAddr;
	float speed = 0, tmp;
	U32 a,b;

	/* setup buffers */
	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;	
	/* setup buffers */
	au8_R1 = (U8*)(DMA_R_ADDR + pNandDrv->u16_PageByteCnt * DMA_PAGE_LEN1);
	au8_RSpare1 = (U8*)(DMA_R_SPARE_ADDR + pNandDrv->u16_SpareByteCnt * DMA_PAGE_LEN1 );
	/* setup buffers */
	au8_R2 = (U8*)((U32)au8_R1 + (pNandDrv->u16_PageByteCnt * DMA_PAGE_LEN2));
	au8_RSpare2 = (U8*)((U32)au8_RSpare1 + (pNandDrv->u16_SpareByteCnt * DMA_PAGE_LEN2));
	memset(au8_R, 0, pNandDrv->u16_PageByteCnt * (DMA_PAGE_LEN1+DMA_PAGE_LEN2+DMA_PAGE_LEN3));
	dump_mem(au8_R, 16);

	
    #if defined(WRITE_TEST_SQUASHFS_IMAGE) && WRITE_TEST_SQUASHFS_IMAGE
	
//    nand_debug(0, 0, "Write test SQUASHFS image\n");

	u32_err = NC_EraseBlk(u32_StartRowIdx);
    if(UNFD_ST_SUCCESS != u32_err)
	{
		nand_debug(0, 0, "Err, erase block(row %Xh) fail: %Xh \n", u32_StartRowIdx, u32_err);
		return u32_err;
	}
	
	for(u32_i = 0 ; u32_i < pNandDrv->u16_SpareByteCnt ; u32_i++)
		au8_WSpare[u32_i] = 0xFF;

	u32_compressed_size = (squashfs_test_img_len>(pNandDrv->u16_PageByteCnt*pNandDrv->u16_BlkPageCnt))
						? (pNandDrv->u16_PageByteCnt*pNandDrv->u16_BlkPageCnt) : squashfs_test_img_len;

	//nand_debug(0, 1, "Compressed size 0x%X\n", u32_compressed_size);
	
	u32_count = (u32_compressed_size+pNandDrv->u16_PageByteCnt-1)/pNandDrv->u16_PageByteCnt;
	
	u32_err = NC_WritePages(u32_StartRowIdx, (U8 *) squashfs_test_img, au8_WSpare, u32_count);
    if(UNFD_ST_SUCCESS != u32_err)
	{
		nand_debug(0, 0, "Err, write page(row %Xh) fail: %Xh \n", u32_StartRowIdx, u32_err);
		return u32_err;
	}

	u32_err = NC_ReadPages(u32_StartRowIdx, (U8 *) au8_R, au8_RSpare, u32_count);
    if(UNFD_ST_SUCCESS != u32_err)
	{
		nand_debug(0, 0, "Err, read page(row %Xh) fail: %Xh \n", u32_StartRowIdx, u32_err);
		return u32_err;
	}

	if(NCTEST_DataCompare(squashfs_test_img, au8_R, u32_count*pNandDrv->u16_PageByteCnt))
	{
		nand_debug(0, 0, "Err, compare fail 1\n");
		return UNFD_ST_ERR_DATA_CMP_FAIL;
	}

	u32_compressed_size = squashfs_test_img_len - u32_count*pNandDrv->u16_PageByteCnt;
	u32_count = (u32_compressed_size+pNandDrv->u16_PageByteCnt-1)/pNandDrv->u16_PageByteCnt;
	if(u32_count)
	{
		u32_err = NC_EraseBlk(u32_StartRowIdx+pNandDrv->u16_BlkPageCnt);
	    if(UNFD_ST_SUCCESS != u32_err)
		{
			nand_debug(0, 0, "Err, erase block(row %Xh) fail: %Xh \n", u32_StartRowIdx+pNandDrv->u16_BlkPageCnt, u32_err);
			return u32_err;
		}	

		u32_err = NC_WritePages(u32_StartRowIdx+pNandDrv->u16_BlkPageCnt,
			(U8 *) squashfs_test_img+pNandDrv->u16_PageByteCnt*pNandDrv->u16_BlkPageCnt, au8_WSpare, u32_count);
	    if(UNFD_ST_SUCCESS != u32_err)
		{
			nand_debug(0, 0, "Err, write page(row %Xh) fail: %Xh \n", u32_StartRowIdx+pNandDrv->u16_BlkPageCnt, u32_err);
			return u32_err;
		}

		u32_err = NC_ReadPages(u32_StartRowIdx +pNandDrv->u16_BlkPageCnt, (U8 *) au8_R, au8_RSpare, u32_count);
	    if(UNFD_ST_SUCCESS != u32_err)
		{
			nand_debug(0, 0, "Err, read page(row %Xh) fail: %Xh \n", u32_StartRowIdx, u32_err);
			return u32_err;
		}

		if(NCTEST_DataCompare(squashfs_test_img+pNandDrv->u16_PageByteCnt*pNandDrv->u16_BlkPageCnt, au8_R, u32_count*pNandDrv->u16_PageByteCnt))
		{
			nand_debug(0, 0, "Err, compare fail 2\n");
			return UNFD_ST_ERR_DATA_CMP_FAIL;
		}	

		
	}
//	nand_debug(0, 0, "[Write test SQUASHFS image ok] \n");
    #endif

	u32_index = 0;
	u32_compressed_size = squashfs_test_img_len;
	u32_uncompressed_size = decompressed_size;
	
	u32_count = (u32_index + u32_compressed_size+pNandDrv->u16_PageByteCnt-1)/pNandDrv->u16_PageByteCnt;
	
	memset(au8_R, 0, u32_count*pNandDrv->u16_PageByteCnt);
	memset(u8_decompress, 0, 128*1024);
	dump_mem(u8_decompress, 16);
	
	u32_DecompressAddr = nand_translate_DMA_address_Ex((U32)u8_decompress, sizeof(u8_decompress), WRITE_TO_NAND);
	
	memset(p_ZDecOutput_st, 0, sizeof(ZDecDescriptor_t)*128);
	p_ZDecOutput_st[0].u32_Address = cpu2le32(u32_DecompressAddr);
	p_ZDecOutput_st[0].u32_PageCnt = cpu2le32((u32_uncompressed_size+pNandDrv->u16_PageByteCnt-1)/pNandDrv->u16_PageByteCnt);
	p_ZDecOutput_st[0].u32_MIUSel = cpu2le32(0);
	p_ZDecOutput_st[0].u32_EndFlag = cpu2le32(1);
	//nand_debug(0, 0, "p_ZDecOutput_st[0].u32_Address : %Xh \n", p_ZDecOutput_st[0].u32_Address);
	//nand_debug(0, 0, "p_ZDecOutput_st[0].u32_PageCnt : %Xh \n", p_ZDecOutput_st[0].u32_PageCnt);
	//nand_debug(0, 0, "p_ZDecOutput_st[0].u32_MIUSel : %Xh \n", p_ZDecOutput_st[0].u32_MIUSel);
	//nand_debug(0, 0, "p_ZDecOutput_st[0].u32_EndFlag : %Xh \n", p_ZDecOutput_st[0].u32_EndFlag);
	
	u32_ZDecOutputAddr =nand_translate_DMA_address_Ex((U32)p_ZDecOutput_st, sizeof(ZDecDescriptor_t)*1, WRITE_TO_NAND);

	dump_mem(p_ZDecOutput_st, sizeof(ZDecDescriptor_t));


	// Setup ZDEC
	mstar_zdec_init(ZMODE_DEC_SCATTER_NAND,
			0,
			1,
			u32_index,	//+2,         // ZLIB offset = 2 bytes
			0,                   // no bit offset
			0,			//descriptor miu
			u32_ZDecOutputAddr,//p_ZDecOutput_st,
			sizeof(ZDecDescriptor_t)*1,
			pNandDrv->u16_PageByteCnt,
			pNandDrv->u16_PageByteCnt);

	memset(ADMADesc, 0, sizeof(ADMA_DESC_t)*16);

	for(u32_i = 0; u32_i < u32_count; u32_i ++)
	{
		drvNAND_ParseAddrToADMA(au8_R + (u32_i << pNandDrv->u8_PageByteCntBits), (1) << pNandDrv->u8_PageByteCntBits, 
			READ_FROM_NAND, &ADMADesc[u32_i], (u32_i == (u32_count - 1)) ? 1 : 0);
		p_ZDecDesc_st[u32_i].u32_Address = ADMADesc[u32_i].u32_Address;
		p_ZDecDesc_st[u32_i].u32_PageCnt = ADMADesc[u32_i].u32_PageCnt;
		p_ZDecDesc_st[u32_i].u32_MIUSel = ADMADesc[u32_i].u32_MIUSel;
		p_ZDecDesc_st[u32_i].u32_EndFlag = ADMADesc[u32_i].u32_EndFlag;		
	}
	
	//nand_debug(0, 0,"p_ZDecDesc_st 0x%X\n", (U32)p_ZDecDesc_st);	
	//nand_debug(0, 0, "p_ZDecDesc_st[0].u32_Address : %Xh \n", p_ZDecDesc_st[0].u32_Address);
	//nand_debug(0, 0, "p_ZDecDesc_st[0].u32_PageCnt : %Xh \n", p_ZDecDesc_st[0].u32_PageCnt);
	//nand_debug(0, 0, "p_ZDecDesc_st[0].u32_MIUSel : %Xh \n", p_ZDecDesc_st[0].u32_MIUSel);
	//nand_debug(0, 0, "p_ZDecDesc_st[0].u32_EndFlag : %Xh \n", p_ZDecDesc_st[0].u32_EndFlag);
	
	dump_mem(p_ZDecDesc_st, sizeof(ADMA_DESC_t));

	u32_ZDecDescAddr =nand_translate_DMA_address_Ex((U32)p_ZDecDesc_st, sizeof(ZDecDescriptor_t)*u32_count, WRITE_TO_NAND);

	mstar_zdec_feed(1, // last
				0,
				u32_ZDecDescAddr, //p_ZDecDesc_st,
				sizeof(ZDecDescriptor_t) * u32_count);
			   //sizeof(ZDecDescriptor_t) * 3);

	//measure time start
	HWTimer_Start();

	u32_err = NC_ADMAReadPages(u32_StartRowIdx, (U8*)ADMADesc, (U8*)au8_RSpare, u32_count, 1);
	if (u32_err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 0, "Err, read page(row %Xh) fail: %Xh \n", u32_StartRowIdx, u32_err);
		return u32_err;
	}
	
	u32_nandtotalTime = HWTimer_End();

	//nand_debug(0, 0, "Wait decoding\n");
	// wait for decode done
	while (-1 == (s32_decode_size = mstar_zdec_check_decode_done()))
	{
		nand_hw_timer_delay(HW_TIMER_DELAY_1us);
		if( ++u32_time_count > 10000 )
		{
			nand_debug(0, 1, "Decode timeout!\n");
			while(1);
		}
	}
	
	///*
	u32_totalTime = HWTimer_End();

	speed = (((float)(u32_count * pNandDrv->u16_PageByteCnt))/(((float)u32_nandtotalTime)/((float)12000000)))/((float)(1024*1024));
	a = (int)speed;
	
	tmp = (speed - ((float)a))*1000;
	b = (int)tmp;
	
	nand_debug(0,1,"fcie total time = %d.%03ds(%d)\n", u32_nandtotalTime/12000000, u32_nandtotalTime/12000, u32_nandtotalTime);
	nand_debug(0,1,"fcie total size = %lX\n", (u32_count * pNandDrv->u16_PageByteCnt));
	nand_debug(0,1,"fcie speed = %d.%03d MB/s\n", a, b);
	
	speed = (((float)s32_decode_size)/(((float)u32_totalTime)/((float)12000000)))/((float)(1024*1024));
	a = (int)speed;
	
	tmp = (speed - ((float)a))*1000;
	b = (int)tmp;
	
	nand_debug(0,1,"fcie + zdec total time = %d.%03ds(%d)\n", u32_totalTime/12000000, u32_totalTime/12000, u32_totalTime);
	nand_debug(0,1,"fcie + zdectotal size = %lX\n", s32_decode_size);
	nand_debug(0,1,"fcie + zdec speed = %d.%03d MB/s\n", a, b);

	nand_debug(0,1,"return decoded size 0x%X\n", s32_decode_size);
	//*/
	/*
	for(u32_i = 0; u32_i < 0x1000; u32_i++)
	{
		if(zdec_fcie_ticker[u32_i] != 0)
			printf("fcie ptr 0x%X, dec cnt 0x%X, timer ticker 0x%X\n", zdec_fcie1[u32_i], zdec_fcie2[u32_i], zdec_fcie_ticker[u32_i] );
	}

	for(u32_i = 0; u32_i < 0x1000; u32_i++)
	{
		if(zdec_fcie_ticker2[u32_i] != 0)
			printf("fcie ptr 0x%X, dec cnt 0x%X, timer ticker 0x%X\n", zdec_fcie3[u32_i], zdec_fcie4[u32_i], zdec_fcie_ticker2[u32_i] );
	}
	//*/

	//measure end
	
	mstar_zdec_release();

	//REG_FCIE_SETBIT(FCIE_ZDEC_CTL0, BIT_SD2ZDEC_PTR_CLR);
	//nand_hw_timer_delay(HW_TIMER_DELAY_1ms);
	//REG_FCIE_CLRBIT(FCIE_ZDEC_CTL0, BIT_SD2ZDEC_PTR_CLR|BIT_ZDEC_EN);

	//nand_debug(0, 1, "Decode finished\n");
	
	if(NCTEST_DataCompare(squashfs_test_img, au8_R, u32_count*pNandDrv->u16_PageByteCnt))
	{
		nand_debug(0, 0, "Err, comare fail 2\n");
		return UNFD_ST_ERR_DATA_CMP_FAIL;
	}
	dump_mem(au8_R, 16);

	if(NCTEST_DataCompare(decompression_image, u8_decompress, u32_uncompressed_size))
	{
		nand_debug(0, 0, "Err, comare fail 3\n");
		dump_mem(u8_decompress, u32_uncompressed_size);
		return UNFD_ST_ERR_DATA_CMP_FAIL;
	}	

	dump_mem(u8_decompress, 16);
	REG_SET_BITS_UINT16(NC_CTRL,  BIT_NC_NF2ZDEC_PTR_CLR);
	nand_hw_timer_delay(HW_TIMER_DELAY_1ms);
	REG_CLR_BITS_UINT16(NC_CTRL,  BIT_NC_NF2ZDEC_PTR_CLR);
	
	return UNFD_ST_SUCCESS;
}

static U32 NCTEST_ZDEC2(U32 u32_StartRowIdx, U8 * squashfs_test_img, U32 squashfs_test_img_len, U8* decompression_image, U32 decompressed_size)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U8	*au8_W, *au8_R;
	U8	*au8_W1, *au8_R1;
	U8	*au8_W2, *au8_R2;	
	U8	*au8_WSpare, *au8_RSpare;
	U8	*au8_WSpare1, *au8_RSpare1;
	U8	*au8_WSpare2, *au8_RSpare2; 
	U32 u32_err;
	U32 u32_i;
	U32 u32_blk_addr;
	U32 u32_index;
	U32 u32_totalTime, u32_nandtotalTime;
	U32 u32_compressed_size;
	U32 u32_uncompressed_size;
	U32 u32_blk_count;
	U32 u32_tmp_blk_count;
	int s32_decode_size;
	U32 u32_count = 0;
	U32 u32_time_count = 0;
	U32 u32_ZDecOutputAddr;
	U32 u32_ZDecDescAddr;
	U32 u32_DecompressAddr;
	float speed = 0, tmp;
	U32 a,b;

	/* setup buffers */
	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR; 
	/* setup buffers */
	au8_R1 = (U8*)(DMA_R_ADDR + pNandDrv->u16_PageByteCnt * DMA_PAGE_LEN1);
	au8_RSpare1 = (U8*)(DMA_R_SPARE_ADDR + pNandDrv->u16_SpareByteCnt * DMA_PAGE_LEN1 );
	/* setup buffers */
	au8_R2 = (U8*)((U32)au8_R1 + (pNandDrv->u16_PageByteCnt * DMA_PAGE_LEN2));
	au8_RSpare2 = (U8*)((U32)au8_RSpare1 + (pNandDrv->u16_SpareByteCnt * DMA_PAGE_LEN2));
	memset(au8_R, 0, pNandDrv->u16_PageByteCnt * (DMA_PAGE_LEN1+DMA_PAGE_LEN2+DMA_PAGE_LEN3));
	dump_mem(au8_R, 16);

	
#if defined(WRITE_TEST_SQUASHFS_IMAGE) && WRITE_TEST_SQUASHFS_IMAGE
	
//	nand_debug(0, 0, "Write test SQUASHFS image\n");

	u32_err = NC_EraseBlk(u32_StartRowIdx);
	if(UNFD_ST_SUCCESS != u32_err)
	{
		nand_debug(0, 0, "Err, erase block(row %Xh) fail: %Xh \n", u32_StartRowIdx, u32_err);
		return u32_err;
	}
	
	for(u32_i = 0 ; u32_i < pNandDrv->u16_SpareByteCnt ; u32_i++)
		au8_WSpare[u32_i] = 0xFF;

	u32_compressed_size = (squashfs_test_img_len>(pNandDrv->u16_PageByteCnt*pNandDrv->u16_BlkPageCnt))
						? (pNandDrv->u16_PageByteCnt*pNandDrv->u16_BlkPageCnt) : squashfs_test_img_len;
	
	u32_count = (u32_compressed_size+pNandDrv->u16_PageByteCnt-1)/pNandDrv->u16_PageByteCnt;
	
	u32_err = NC_WritePages(u32_StartRowIdx, (U8 *) squashfs_test_img, au8_WSpare, u32_count);
	if(UNFD_ST_SUCCESS != u32_err)
	{
		nand_debug(0, 0, "Err, write page(row %Xh) fail: %Xh \n", u32_StartRowIdx, u32_err);
		return u32_err;
	}

	u32_err = NC_ReadPages(u32_StartRowIdx, (U8 *) au8_R, au8_RSpare, u32_count);
	if(UNFD_ST_SUCCESS != u32_err)
	{
		nand_debug(0, 0, "Err, read page(row %Xh) fail: %Xh \n", u32_StartRowIdx, u32_err);
		return u32_err;
	}

	if(NCTEST_DataCompare(squashfs_test_img, au8_R, u32_count*pNandDrv->u16_PageByteCnt))
	{
		nand_debug(0, 0, "Err, compare fail 1\n");
		return UNFD_ST_ERR_DATA_CMP_FAIL;
	}

	u32_compressed_size = squashfs_test_img_len - u32_count*pNandDrv->u16_PageByteCnt;
	u32_count = (u32_compressed_size+pNandDrv->u16_PageByteCnt-1)/pNandDrv->u16_PageByteCnt;
	if(u32_count)
	{
		u32_err = NC_EraseBlk(u32_StartRowIdx+pNandDrv->u16_BlkPageCnt);
		if(UNFD_ST_SUCCESS != u32_err)
		{
			nand_debug(0, 0, "Err, erase block(row %Xh) fail: %Xh \n", u32_StartRowIdx+pNandDrv->u16_BlkPageCnt, u32_err);
			return u32_err;
		}	

		u32_err = NC_WritePages(u32_StartRowIdx+pNandDrv->u16_BlkPageCnt,
			(U8 *) squashfs_test_img+pNandDrv->u16_PageByteCnt*pNandDrv->u16_BlkPageCnt, au8_WSpare, u32_count);
		if(UNFD_ST_SUCCESS != u32_err)
		{
			nand_debug(0, 0, "Err, write page(row %Xh) fail: %Xh \n", u32_StartRowIdx+pNandDrv->u16_BlkPageCnt, u32_err);
			return u32_err;
		}

		u32_err = NC_ReadPages(u32_StartRowIdx +pNandDrv->u16_BlkPageCnt, (U8 *) au8_R, au8_RSpare, u32_count);
		if(UNFD_ST_SUCCESS != u32_err)
		{
			nand_debug(0, 0, "Err, read page(row %Xh) fail: %Xh \n", u32_StartRowIdx, u32_err);
			return u32_err;
		}

		if(NCTEST_DataCompare(squashfs_test_img+pNandDrv->u16_PageByteCnt*pNandDrv->u16_BlkPageCnt, au8_R, u32_count*pNandDrv->u16_PageByteCnt))
		{
			nand_debug(0, 0, "Err, compare fail 2\n");
			return UNFD_ST_ERR_DATA_CMP_FAIL;
		}	

		
	}
//	nand_debug(0, 0, "[Write test SQUASHFS image ok] \n");
#endif

	u32_index = 0;
	u32_compressed_size = squashfs_test_img_len;
	u32_uncompressed_size = decompressed_size;

	u32_count = (u32_index + u32_compressed_size+pNandDrv->u16_PageByteCnt-1)/pNandDrv->u16_PageByteCnt;
	
	memset(au8_R, 0, u32_count*pNandDrv->u16_PageByteCnt);
	memset(u8_decompress, 0, 128*1024);
	dump_mem(u8_decompress, 16);
	
	u32_DecompressAddr = nand_translate_DMA_address_Ex((U32)u8_decompress, sizeof(u8_decompress), WRITE_TO_NAND);
	
	memset(p_ZDecOutput_st, 0, sizeof(ZDecDescriptor_t)*128);
	p_ZDecOutput_st[0].u32_Address = cpu2le32(u32_DecompressAddr);
	p_ZDecOutput_st[0].u32_PageCnt = cpu2le32((u32_uncompressed_size+pNandDrv->u16_PageByteCnt-1)/pNandDrv->u16_PageByteCnt);
	p_ZDecOutput_st[0].u32_MIUSel = cpu2le32(0);
	p_ZDecOutput_st[0].u32_EndFlag = cpu2le32(1);
	
	u32_ZDecOutputAddr =nand_translate_DMA_address_Ex((U32)p_ZDecOutput_st, sizeof(ZDecDescriptor_t)*1, WRITE_TO_NAND);


	// Setup ZDEC
	mstar_zdec_init(ZMODE_DEC_SCATTER_NAND,
					   0,
					   1,
					   u32_index,	//+2,		  // ZLIB offset = 2 bytes
					   0,					// no bit offset
					   0,			//descriptor miu
					   u32_ZDecOutputAddr,//p_ZDecOutput_st,
					   sizeof(ZDecDescriptor_t)*1,
					   pNandDrv->u16_PageByteCnt,
					   pNandDrv->u16_PageByteCnt);

	memset(ADMADesc, 0, sizeof(ADMA_DESC_t)*128);


	for(u32_i = 0; u32_i < u32_count; u32_i ++)
	{
		drvNAND_ParseAddrToADMA(au8_R + ((u32_i) << pNandDrv->u8_PageByteCntBits), (1) << pNandDrv->u8_PageByteCntBits, 
			READ_FROM_NAND, &ADMADesc[u32_i],  1);
		
		p_ZDecDesc_st[u32_i * 2].u32_Address = ADMADesc[u32_i].u32_Address;
		p_ZDecDesc_st[u32_i * 2].u32_PageCnt = ADMADesc[u32_i].u32_PageCnt;
		p_ZDecDesc_st[u32_i * 2].u32_MIUSel = ADMADesc[u32_i].u32_MIUSel;
		p_ZDecDesc_st[u32_i * 2].u32_EndFlag = ADMADesc[u32_i].u32_EndFlag;

	}
	
	HWTimer_Start();
	u32_nandtotalTime = 0;
	
	for(u32_i = 0; u32_i < u32_count; u32_i ++)
	{
		U32 u32_tmp;
		U8 u8_last = 0;
		
		u32_ZDecDescAddr =nand_translate_DMA_address_Ex((U32) &p_ZDecDesc_st[u32_i * 2], sizeof(ZDecDescriptor_t), WRITE_TO_NAND);

		//printf("mstar feed zdec  0x%X address 0x%X\n", u32_i, u32_ZDecDescAddr);
		if(u32_i == (u32_count - 1))
		{
			u8_last = 1;
		}
		mstar_zdec_feed( u8_last,  // last
				0,
				u32_ZDecDescAddr, //p_ZDecDesc_st,
				sizeof(ZDecDescriptor_t));

		u32_tmp = HWTimer_End();
		
		u32_err = NC_ADMAReadPages(u32_StartRowIdx + u32_i, (U8*)&ADMADesc[u32_i ], (U8*)au8_RSpare, 1, 1);
		if (u32_err != UNFD_ST_SUCCESS)
		{
			nand_debug(0, 0, "Err, read page(row %Xh) fail: %Xh \n", u32_StartRowIdx + u32_i, u32_err);
			return u32_err;
		}
		u32_nandtotalTime += HWTimer_End() - u32_tmp;

		REG_SET_BITS_UINT16(NC_CTRL,  BIT_NC_NF2ZDEC_PTR_CLR);
		
		REG_CLR_BITS_UINT16(NC_CTRL,  BIT_NC_NF2ZDEC_PTR_CLR);
		
		if(u32_i != (u32_count -1)) 
			while (0 != mstar_zdec_check_adma_table_done());
		else
			break;
			
	}

	while (-1 == (s32_decode_size = mstar_zdec_check_decode_done()))
	{
		nand_hw_timer_delay(HW_TIMER_DELAY_1us);
		
		if( ++u32_time_count > 10000 )
		{
			nand_debug(0, 1, "Decode timeout!\n");
			while(1);
		}
	}
	
	///*
	u32_totalTime = HWTimer_End();

	speed = (((float)(u32_count * pNandDrv->u16_PageByteCnt))/(((float)u32_nandtotalTime)/((float)12000000)))/((float)(1024*1024));
	a = (int)speed;
	
	tmp = (speed - ((float)a))*1000;
	b = (int)tmp;
	
	nand_debug(0,1,"fcie total time = %d.%03ds(%d)\n", u32_nandtotalTime/12000000, u32_nandtotalTime/12000, u32_nandtotalTime);
	nand_debug(0,1,"fcie total size = %lX\n", (u32_count * pNandDrv->u16_PageByteCnt));
	nand_debug(0,1,"fcie speed = %d.%03d MB/s\n", a, b);
	
	speed = (((float)s32_decode_size)/(((float)u32_totalTime)/((float)12000000)))/((float)(1024*1024));
	a = (int)speed;
	
	tmp = (speed - ((float)a))*1000;
	b = (int)tmp;
	
	nand_debug(0,1,"fcie + zdec total time = %d.%03ds(%d)\n", u32_totalTime/12000000, u32_totalTime/12000, u32_totalTime);
	nand_debug(0,1,"fcie + zdectotal size = %lX\n", s32_decode_size);
	nand_debug(0,1,"fcie + zdec speed = %d.%03d MB/s\n", a, b);

	nand_debug(0,1,"return decoded size 0x%X\n", s32_decode_size);

	//measure end
	
	mstar_zdec_release();

	nand_debug(0, 1, "Decode finished\n");
	
	if(NCTEST_DataCompare(squashfs_test_img, au8_R, u32_count*pNandDrv->u16_PageByteCnt))
	{
		nand_debug(0, 0, "Err, comare fail 2\n");
		return UNFD_ST_ERR_DATA_CMP_FAIL;
	}
	dump_mem(au8_R, 16);

	if(NCTEST_DataCompare(decompression_image, u8_decompress, u32_uncompressed_size))
	{
		nand_debug(0, 0, "Err, comare fail 3\n");
		dump_mem(u8_decompress, u32_uncompressed_size);
		return UNFD_ST_ERR_DATA_CMP_FAIL;
	}	

	dump_mem(u8_decompress, 16);
	REG_SET_BITS_UINT16(NC_CTRL,  BIT_NC_NF2ZDEC_PTR_CLR);
	nand_hw_timer_delay(HW_TIMER_DELAY_1ms);
	REG_CLR_BITS_UINT16(NC_CTRL,  BIT_NC_NF2ZDEC_PTR_CLR);
	
	return UNFD_ST_SUCCESS;
}

#endif


#endif




//volatile struct fcie_ctrl_struct *fcie = (struct fcie_ctrl_struct*)FCIE_REG_BASE_ADDR;

static U32 NCTEST_BYTE_OFFSET_DMA(U32 u32_StartRowIdx)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;
	U32 u32_PageIdx, u32_ByteIdx;
	U16 u16_SpareByteCnt;

	U8  *au8_W, *au8_R;
	U8  *au8_WSpare, *au8_RSpare;

	/* erase the first blk */

	u32_Err = NC_EraseBlk(u32_StartRowIdx &~ pNandDrv->u16_BlkPageCntMask);

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RWSinglePages 0, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	/* setup buffers */


	/* W/R/C each page */
	for (u32_PageIdx = 0; u32_PageIdx < 16; u32_PageIdx++)
	{
		au8_W = (U8*)(DMA_W_ADDR + u32_PageIdx);
		au8_R = (U8*)(DMA_R_ADDR + u32_PageIdx);
		au8_WSpare = (U8*)(DMA_W_SPARE_ADDR + u32_PageIdx);
		au8_RSpare = (U8*)(DMA_R_SPARE_ADDR + u32_PageIdx);

		/* erase */
		if (u32_PageIdx && !((u32_StartRowIdx + u32_PageIdx) & pNandDrv->u16_BlkPageCntMask))
		{
			u32_Err = NC_EraseBlk(u32_StartRowIdx + u32_PageIdx);
			if (u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RWSinglePages 1, ErrCode: 0x%08lx\n", u32_Err);
				return u32_Err;
			}
		}

		/* init test pattern */
		for (u32_ByteIdx = 0; u32_ByteIdx < pNandDrv->u16_PageByteCnt; u32_ByteIdx++)
		{
			if (pNandDrv->u8_IfECCTesting)
				au8_W[u32_ByteIdx] = ECC_TEST_PATTERN;
			else
				au8_W[u32_ByteIdx] = u32_ByteIdx + 1;

			au8_R[u32_ByteIdx] = ~au8_W[u32_ByteIdx];
            #if 0
			if(u32_ByteIdx<0x20)
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "set: [%2u]: adr:%X val:%02X  adr:%X val:%02X\n",
				    u32_ByteIdx, &au8_W[u32_ByteIdx], au8_W[u32_ByteIdx],
				    &au8_R[u32_ByteIdx], au8_R[u32_ByteIdx]);
			#endif
		}

		for (u32_ByteIdx = 0; u32_ByteIdx < pNandDrv->u16_SpareByteCnt; u32_ByteIdx++)
		{
			if (pNandDrv->u8_IfECCTesting)
				au8_WSpare[u32_ByteIdx] = ECC_TEST_PATTERN;
			else
				au8_WSpare[u32_ByteIdx] = u32_ByteIdx + 1 ;

			au8_RSpare[u32_ByteIdx] = ~au8_WSpare[u32_ByteIdx];
		}

		u32_Err = NC_WritePages(u32_StartRowIdx + u32_PageIdx, au8_W, au8_WSpare, 1);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RWSinglePages 2, ErrCode: 0x%08lx\n", u32_Err);
			return u32_Err;
		}

		/* read test pattern */
		u32_Err = NC_ReadPages(u32_StartRowIdx + u32_PageIdx, au8_R, au8_RSpare, 1);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RWSinglePages 3, ErrCode: 0x%08lx\n", u32_Err);
			return u32_Err;
		}
		// [CAUTION]: if the above 2 of nand_translate_DMA_address_Ex, data area must be handled later.
		//nand_translate_DMA_address_Ex((U32)sgau8_RBuf, pNandDrv->u16_PageByteCnt);
		//nand_translate_DMA_address_Ex((U32)sgau8_RSpareBuf, pNandDrv->u16_PageByteCnt);

		/* compare test pattern */
		if(NCTEST_DataCompare(au8_W, au8_R, pNandDrv->u16_PageByteCnt))
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RWSinglePages 4 \n");
			return UNFD_ST_ERR_DATA_CMP_FAIL;
		}

		u16_SpareByteCnt = pNandDrv->u16_SpareByteCnt;
		#if SPARE640B_CIFD512B_PATCH
		if(u16_SpareByteCnt > 0x200)
			u16_SpareByteCnt = (0x200/pNandDrv->u16_SectorSpareByteCnt)*pNandDrv->u16_SectorSpareByteCnt;
		#endif
		for (u32_ByteIdx = 0; u32_ByteIdx < u16_SpareByteCnt; u32_ByteIdx++)
		{
			if (u32_ByteIdx == pNandDrv->u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt +
					pNandDrv->u16_SectorSpareByteCnt * (u32_ByteIdx / pNandDrv->u16_SectorSpareByteCnt))
			{
				u32_ByteIdx += pNandDrv->u16_ECCCodeByteCnt - 1;
				continue;
			}

			if (au8_WSpare[u32_ByteIdx] != au8_RSpare[u32_ByteIdx])
			{
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RWSinglePages, spare, Row: 0x%08lx, Col: 0x%04lx, W: 0x%02x, R: 0x%02x\n",
						u32_StartRowIdx + u32_PageIdx, u32_ByteIdx, au8_WSpare[u32_ByteIdx], au8_RSpare[u32_ByteIdx]);
				return UNFD_ST_ERR_DATA_CMP_FAIL;
			}
		}
	}

	return UNFD_ST_SUCCESS;
}

U32 NCTEST_ResetTorture(void)
{
	nand_debug(UNFD_DEBUG_LEVEL_HIGH, 1, "Rest torture\n");

	while(1)
	{
        #if 0
		REG_CLR_BITS_UINT16(NC_TEST_MODE, BIT_FCIE_SOFT_RST); /* active low */
		nand_hw_timer_delay(HW_TIMER_DELAY_1ms);
		REG_SET_BITS_UINT16(NC_TEST_MODE, BIT_FCIE_SOFT_RST);
		nand_hw_timer_delay(HW_TIMER_DELAY_1ms);
        #else
		U32 u32_Err = NC_ResetNandFlash();
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RestTorture failed with ErrCode: 0x%08lx\n", u32_Err);
			return u32_Err;
		}
        #endif
	}
	return UNFD_ST_SUCCESS;
}


U32 NCTEST_DataCompare(U8 *pu8_buf0, U8 *pu8_buf1, U32 u32_byteCnt)
{
	U32 u32_i;
	U8  u8_ErrFlag=0;

	for (u32_i=0; u32_i < u32_byteCnt; u32_i++)
	{
		if (pu8_buf0[u32_i] != pu8_buf1[u32_i])
		{
			nand_debug(0, 1, "error: i:%08lX  buf0:%02X  buf1:%02X \n",
				u32_i, pu8_buf0[u32_i], pu8_buf1[u32_i]);
			
			u8_ErrFlag = 1;
			//break;
		}
	}

	//if(u32_i != u32_byteCnt)
	if(u8_ErrFlag)
		return UNFD_ST_ERR_DATA_CMP_FAIL; // fail
	else
		return UNFD_ST_SUCCESS; // ok
}


U32 NCTEST_DumpECCRegisters(void)
{
	U16 u16_Reg51, u16_Reg52, u16_Reg53;

	REG_READ_UINT16(NC_ECC_STAT0, u16_Reg51);
	REG_READ_UINT16(NC_ECC_STAT1, u16_Reg52);
	REG_READ_UINT16(NC_ECC_STAT2, u16_Reg53);
	if((u16_Reg51&BIT_NC_ECC_FAIL) || (u16_Reg53&BIT_NC_ECC_FLGA_FAIL))
	{
		nand_debug(0,1,"ERROR. NAND, ECC fail: Reg.51:%04X, Reg.52:%04X, Reg.53:%04X\n",
			u16_Reg51, u16_Reg52, u16_Reg53);
		return UNFD_ST_ERR_ECC_FAIL;
	}
	else
		nand_debug(0,1,"ECC ok, reg51h: %04X, reg52h: %04X, reg53h: %04X \n",
		    u16_Reg51, u16_Reg52, u16_Reg53);

	return UNFD_ST_SUCCESS;
}

// =====================================================
#if defined(FCIE_LFSR) && FCIE_LFSR


static U16 gau16_seeds[]={
#include "seeds_SEC.txt"
};

#define NAND_PAGE_SEEDCNT    0x80

#define SEC_LFSR_SHIFT1(u16_new, u16_old) \
    u16_new = ((u16_old&BIT14)>>14 ^ (u16_old&BIT13)>>13) |\
              (u16_old&BIT13)<<1 | (u16_old&BIT12)<<1 |\
              (u16_old&BIT11)<<1 | (u16_old&BIT10)<<1 |\
              (u16_old&BIT9)<<1  | (u16_old&BIT8)<<1  |\
              (u16_old&BIT7)<<1  | (u16_old&BIT6)<<1  |\
              (u16_old&BIT5)<<1  | (u16_old&BIT4)<<1  |\
              (u16_old&BIT3)<<1  | (u16_old&BIT2)<<1  |\
              (u16_old&BIT1)<<1  | (u16_old&BIT0)<<1;

#define LFSR_TYPE1    SEC_LFSR_SHIFT1 // A Sir chooses this one

//===========================================================
int  LFSR1_NLines_NIOs_SectorUnit(U16 au16_DatIn[], U16 au16_BufOut[], U32 u32_ByteCnt, U16 u16_Page, U8 u8_lines, U8 u8_IOs)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();

	U16 au16_LFSR_Value[32];
	U8  u8_data_src[4];
	U16 u16_bit, u16_byte, u16_i, u16_LFSR_i, u16_j;
	U8  *pu8_data_src[4], *pu8_data_dest[4];

	if(u8_lines > 32 || u8_IOs > 32)
	{
		nand_debug(0, 1,"Max line or IO count is 32 but param. is lines: %d, IOs %d \n ", u8_lines, u8_IOs);
		return -1;
	}

	for(u16_byte=0; u16_byte<u32_ByteCnt; u16_byte+=u8_IOs/8)
	{
		// pre-select 16 seeds for each sector, sector is main + spare
		if(0 == u16_byte%(pNandDrv->u16_SectorByteCnt + pNandDrv->u16_SectorSpareByteCnt))
		{
			for(u16_LFSR_i=0; u16_LFSR_i< u8_lines; u16_LFSR_i++)
			{
				u16_i = u16_LFSR_i + u16_Page;

				while(u16_i >= NAND_PAGE_SEEDCNT)
					u16_i -= NAND_PAGE_SEEDCNT;

				au16_LFSR_Value[u16_LFSR_i] = gau16_seeds[u16_i];
			}
		}

		//handle how many "8 io" a time, byte as unit
		for(u16_i = 0; u16_i < u8_IOs/8; u16_i ++)
		{
			u16_j = u16_byte + u16_i;
			pu8_data_src[u16_i] = (U8*)(((U8*)&au16_DatIn[u16_j/2])+(u16_j&1));
			pu8_data_dest[u16_i]= (U8*)(((U8*)&au16_BufOut[u16_j/2])+(u16_j&1));
			u8_data_src[u16_i] = *pu8_data_src[u16_i];
			*pu8_data_dest[u16_i] = 0;
			for(u16_bit=0; u16_bit<8; u16_bit++)
			{
				*pu8_data_dest[u16_i] |= ((u8_data_src[u16_i]&BIT0) ^
					((au16_LFSR_Value[u16_i * 8 + u16_bit]&BIT14)>>14 ^ (au16_LFSR_Value[u16_i * 8 + u16_bit]&BIT13)>>13))<<u16_bit;
				u8_data_src[u16_i] >>= 1;
			}
		}

		for(u16_i=0; u16_i< u8_lines; u16_i++)
			LFSR_TYPE1(au16_LFSR_Value[u16_i], au16_LFSR_Value[u16_i]);

	}
	return 0;
}


static U16 sgau16_ScrambledP00[(NAND_PAGE_BYTE_CNT+NAND_SPARE_BYTE_CNT)/2] ;
static U16 sgau16_ScrambledP01[(NAND_PAGE_BYTE_CNT+NAND_SPARE_BYTE_CNT)/2] ;
static U16 sgau16_ScrambledP02[(NAND_PAGE_BYTE_CNT+NAND_SPARE_BYTE_CNT)/2] ;
static U16 sgau16_ScrambledP7F[(NAND_PAGE_BYTE_CNT+NAND_SPARE_BYTE_CNT)/2] ;
static U16 sgau16_ScrambledP80[(NAND_PAGE_BYTE_CNT+NAND_SPARE_BYTE_CNT)/2] ;
static U16 sgau16_ScrambledP81[(NAND_PAGE_BYTE_CNT+NAND_SPARE_BYTE_CNT)/2] ;

#define LFSR_TEST_PAGE_CNT   3
#define LFSR_DATA_PATTERN    0x5A5A

static U32 NCTEST_LFSRTest(U32 u32_PBA)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_row, u32_Err;
	U8  *au8_W, *au8_R, *au8_WTmp;
	U8  *au8_WSpare, *au8_RSpare;
	U8  *apu8_scrambled[LFSR_TEST_PAGE_CNT];
	U16 u16_i, u16_j, u16_loop, u16_TestBlk=u32_PBA;

	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	au8_WTmp = (U8 *)(DMA_W_ADDR + pNandDrv->u16_PageByteCnt * 5);

	// check Wrod Mode
	if(pNandDrv->u16_Reg50_EccCtrl & BIT_NC_WORD_MODE)
	{
		nand_debug(0,1,"Error: current only test for x8 IOs \n");
		nand_debug(0,1,"need implement for x16 IOs \n");
		return UNFD_ST_ERR_HAL_W_INVALID_PARAM;
	}
	
	if(pNandDrv->u16_BlkPageCnt != 0x40 && pNandDrv->u16_BlkPageCnt != 0x100)
	{
		nand_debug(0, 1, "LFSR test does not support blkpagecnt 0x%X\n", pNandDrv->u16_BlkPageCnt);
		return UNFD_ST_SUCCESS;
	}

	u32_row = pNandDrv->u16_BlkPageCnt*u16_TestBlk;
	u32_Err = NC_EraseBlk(u32_row);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR.1, erase fail: 0x%08lX\n", u32_Err);
		goto LABEL_LFSR_TEST_END;
	}


	u16_loop = 0;
    // ----------------------------------------------------------
    LABEL_WR_LFSR_TEST:
    switch(u16_loop)
    {
		case 0: // w,r with LFSR, page:0~2
			nand_debug(0,1,"enable LFSR, test blk:%lX, page:%03lX~ %03lX \n",
		        u32_row >> pNandDrv->u8_BlkPageCntBits,
		        u32_row & pNandDrv->u16_BlkPageCntMask,
		        (u32_row+LFSR_TEST_PAGE_CNT-1) & pNandDrv->u16_BlkPageCntMask);
			// enable LFSR
			NC_EnableLFSR();
			NC_Config();
			// setup data pattern
			for(u16_j=0; u16_j<LFSR_TEST_PAGE_CNT; u16_j++)
			{
	            for(u16_i=0; u16_i<pNandDrv->u16_PageByteCnt; u16_i++)
	            {
		            au8_W[(u16_j<<pNandDrv->u8_PageByteCntBits) + u16_i] = (U8)LFSR_DATA_PATTERN;
				    //au8_R[u16_i] = ~au8_W[u16_i];
			    }
	            for(u16_i=0; u16_i<pNandDrv->u16_SpareByteCnt; u16_i++)
	            {
		            //au8_WSpare[u16_i] = LFSR_DATA_PATTERN;
		            au8_WSpare[u16_j*pNandDrv->u16_SpareByteCnt + u16_i] = (U8)LFSR_DATA_PATTERN;
		            //au8_RSpare[u16_i] = ~au8_WSpare[u16_i];
	            }
			}
			break;

		case 1: // w,r with LFSR, page: 0x7F, 0, 1
		    if(0x40 == pNandDrv->u16_BlkPageCnt)
				u32_row = pNandDrv->u16_BlkPageCnt*u16_TestBlk + 0x3D;
			else if(0x100 == pNandDrv->u16_BlkPageCnt)
				u32_row = pNandDrv->u16_BlkPageCnt*u16_TestBlk + 0x7F; // the last seed
			else
			{u16_loop++;  goto LABEL_WR_LFSR_TEST;}

			nand_debug(0,1,"enable LFSR, test blk:%lX, page:%03lX~ %03lX \n",
		        u32_row >> pNandDrv->u8_BlkPageCntBits,
		        u32_row & pNandDrv->u16_BlkPageCntMask,
		        (u32_row+LFSR_TEST_PAGE_CNT-1) & pNandDrv->u16_BlkPageCntMask);
			// setup data pattern
			for(u16_j=0; u16_j<LFSR_TEST_PAGE_CNT; u16_j++)
			{
	            for(u16_i=0; u16_i<pNandDrv->u16_PageByteCnt; u16_i++)
	            {
		            au8_W[(u16_j<<pNandDrv->u8_PageByteCntBits) + u16_i] = (U8)LFSR_DATA_PATTERN;
				    //au8_R[u16_i] = ~au8_W[u16_i];
			    }
	            for(u16_i=0; u16_i<pNandDrv->u16_SpareByteCnt; u16_i++)
	            {
		            //au8_WSpare[u16_i] = LFSR_DATA_PATTERN;
		            au8_WSpare[u16_j*pNandDrv->u16_SpareByteCnt + u16_i] = (U8)LFSR_DATA_PATTERN;
		            //au8_RSpare[u16_i] = ~au8_WSpare[u16_i];
	            }
			}
			break;

		default:
			u32_Err = UNFD_ST_SUCCESS;
			goto LABEL_LFSR_TEST_END;
    }

	u32_Err = NC_WritePages(u32_row, au8_W, au8_WSpare, LFSR_TEST_PAGE_CNT);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR.2, write fail: 0x%08lX\n", u32_Err);
		goto LABEL_LFSR_TEST_END;
	}

	u32_Err = NC_ReadPages(u32_row, au8_R, au8_RSpare, LFSR_TEST_PAGE_CNT);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR.3, read fail: 0x%08lX\n", u32_Err);
		goto LABEL_LFSR_TEST_END;
	}

	u32_Err = NCTEST_DumpECCRegisters();
	if(UNFD_ST_SUCCESS != u32_Err)
		goto LABEL_LFSR_TEST_END;

	if(NCTEST_DataCompare(au8_W, au8_R, pNandDrv->u16_PageByteCnt*LFSR_TEST_PAGE_CNT))
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR.5, data mismatch \n");
		//return UNFD_ST_ERR_DATA_CMP_FAIL;
	}
	else
		nand_debug(0,1,"page data compare ok\n");

	for(u16_i=0; u16_i<pNandDrv->u16_PageSectorCnt; u16_i++)
	{
		#if SPARE640B_CIFD512B_PATCH
		if((u16_i+1) * pNandDrv->u16_SectorSpareByteCnt > 0x200)
			break;
		#endif
	    if(NCTEST_DataCompare(
		    au8_WSpare + u16_i*pNandDrv->u16_SectorSpareByteCnt,
		    au8_RSpare + u16_i*pNandDrv->u16_SectorSpareByteCnt,
		    pNandDrv->u16_SectorSpareByteCnt-pNandDrv->u16_ECCCodeByteCnt))
	    {
		    nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR.6, spare mismatch, Sector:%X \n", u16_i);
		    //return UNFD_ST_ERR_DATA_CMP_FAIL;
	    }
	}
	nand_debug(0,1,"spare data compare ok\n");

	u16_loop++;
	if(u16_loop < 2)
		goto LABEL_WR_LFSR_TEST;

	// ----------------------------------------------------------
	nand_debug(0,1,"----------------------------\n");
    LABEL_R_LFSR_TEST:
    switch(u16_loop)
    {
		case 2: // r without LFSR, page:0~2
		    u32_row = pNandDrv->u16_BlkPageCnt*u16_TestBlk;
			nand_debug(0,1,"R, disable LFSR, test blk:%lX, page:%03lX~ %03lX \n",
		        u32_row >> pNandDrv->u8_BlkPageCntBits,
		        u32_row & pNandDrv->u16_BlkPageCntMask,
		        (u32_row+LFSR_TEST_PAGE_CNT-1) & pNandDrv->u16_BlkPageCntMask);
			pNandDrv->u16_Reg50_EccCtrl |= BIT_NC_BYPASS_ECC;
			// disable LFSR
			NC_DisableLFSR();
			NC_Config();
			memset(au8_WTmp, 0x5a, pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt);

			if(pNandDrv->u16_Reg58_DDRCtrl & BIT_DDR_MASM)
			{
				LFSR1_NLines_NIOs_SectorUnit((U16*)au8_WTmp,sgau16_ScrambledP00, pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt,(u32_row + 0)  & pNandDrv->u16_BlkPageCntMask, 16, 16);
				LFSR1_NLines_NIOs_SectorUnit((U16*)au8_WTmp,sgau16_ScrambledP01, pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt,(u32_row + 1) & pNandDrv->u16_BlkPageCntMask, 16, 16);
				LFSR1_NLines_NIOs_SectorUnit((U16*)au8_WTmp,sgau16_ScrambledP02, pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt,(u32_row + 2) & pNandDrv->u16_BlkPageCntMask, 16, 16);
			}
			else
			{
				LFSR1_NLines_NIOs_SectorUnit((U16*)au8_WTmp,sgau16_ScrambledP00, pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt,(u32_row + 0) & pNandDrv->u16_BlkPageCntMask, 16, 8);
				LFSR1_NLines_NIOs_SectorUnit((U16*)au8_WTmp,sgau16_ScrambledP01, pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt,(u32_row + 1) & pNandDrv->u16_BlkPageCntMask, 16, 8);
				LFSR1_NLines_NIOs_SectorUnit((U16*)au8_WTmp,sgau16_ScrambledP02, pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt,(u32_row + 2) & pNandDrv->u16_BlkPageCntMask, 16, 8);
			}

			apu8_scrambled[0] = (U8*)sgau16_ScrambledP00;
			apu8_scrambled[1] = (U8*)sgau16_ScrambledP01;
			apu8_scrambled[2] = (U8*)sgau16_ScrambledP02;
			break;

		case 3:
		    if(0x40 == pNandDrv->u16_BlkPageCnt)
				u32_row = pNandDrv->u16_BlkPageCnt*u16_TestBlk + 0x3D;
			else if(0x100 == pNandDrv->u16_BlkPageCnt)
				u32_row = pNandDrv->u16_BlkPageCnt*u16_TestBlk + 0x7F; // the last seed
			else
			{u16_loop++;  goto LABEL_WR_LFSR_TEST;}

			nand_debug(0,1,"R, disable LFSR, test blk:%lX, page:%03lX~ %03lX \n",
		        u32_row >> pNandDrv->u8_BlkPageCntBits,
		        u32_row & pNandDrv->u16_BlkPageCntMask,
		        (u32_row+LFSR_TEST_PAGE_CNT-1) & pNandDrv->u16_BlkPageCntMask);
			memset(au8_WTmp, 0x5a, pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt);

			if(pNandDrv->u16_Reg58_DDRCtrl & BIT_DDR_MASM)
			{
				LFSR1_NLines_NIOs_SectorUnit((U16*)au8_WTmp,sgau16_ScrambledP7F, pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt,u32_row & pNandDrv->u16_BlkPageCntMask, 16, 16);
				LFSR1_NLines_NIOs_SectorUnit((U16*)au8_WTmp,sgau16_ScrambledP80, pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt,(u32_row + 1) & pNandDrv->u16_BlkPageCntMask, 16, 16);
				LFSR1_NLines_NIOs_SectorUnit((U16*)au8_WTmp,sgau16_ScrambledP81, pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt,(u32_row + 2) & pNandDrv->u16_BlkPageCntMask, 16, 16);
			}
			else
			{
				LFSR1_NLines_NIOs_SectorUnit((U16*)au8_WTmp,sgau16_ScrambledP7F, pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt,u32_row & pNandDrv->u16_BlkPageCntMask, 16, 8);
				LFSR1_NLines_NIOs_SectorUnit((U16*)au8_WTmp,sgau16_ScrambledP80, pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt,(u32_row + 1) & pNandDrv->u16_BlkPageCntMask, 16, 8);
				LFSR1_NLines_NIOs_SectorUnit((U16*)au8_WTmp,sgau16_ScrambledP81, pNandDrv->u16_PageByteCnt + pNandDrv->u16_SpareByteCnt,(u32_row + 2) & pNandDrv->u16_BlkPageCntMask, 16, 8);
			}

			apu8_scrambled[0] = (U8*)sgau16_ScrambledP7F;
			apu8_scrambled[1] = (U8*)sgau16_ScrambledP80;
			apu8_scrambled[2] = (U8*)sgau16_ScrambledP81;
			break;

		default:
			u32_Err = UNFD_ST_SUCCESS;
			goto LABEL_LFSR_TEST_END;
    }

	for(u16_i=0; u16_i<LFSR_TEST_PAGE_CNT; u16_i++)
	{
	    u32_Err = NC_ReadPages(u32_row+u16_i, au8_R, au8_RSpare, 1);
    	if (u32_Err != UNFD_ST_SUCCESS)
	    {
		    nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR.7, read fail: 0x%08lX\n", u32_Err);
		    goto LABEL_LFSR_TEST_END;
	    }
		for(u16_j = 0; u16_j < pNandDrv->u16_PageSectorCnt; u16_j ++)
		{
			u32_Err = NC_ReadSectors(u32_row + u16_i ,u16_j,  au8_R + (u16_j << pNandDrv->u8_SectorByteCntBits),
				au8_RSpare + u16_j * pNandDrv->u16_SectorSpareByteCnt, 1);
			if (u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR.7.1, read fail: 0x%08lX\n", u32_Err);
				goto LABEL_LFSR_TEST_END;
			}
		}

		#if 0
	    u32_Err = NCTEST_DumpECCRegisters();
	    if(UNFD_ST_SUCCESS != u32_Err)
		    goto LABEL_LFSR_TEST_END;
		#endif

		for(u16_j=0; u16_j<pNandDrv->u16_PageSectorCnt; u16_j++)
	    {
			// compare data area
		    if(NCTEST_DataCompare(
			    apu8_scrambled[u16_i] + u16_j*(pNandDrv->u16_SectorByteCnt+pNandDrv->u16_SectorSpareByteCnt),
			    au8_R + (u16_j<<pNandDrv->u8_SectorByteCntBits),
			    pNandDrv->u16_SectorByteCnt))
	        {
		        nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR.8, data mismatch, page:%lX, sector:%X \n",
				    (u32_row+u16_i) & pNandDrv->u16_BlkPageCntMask, u16_j);
		        //return UNFD_ST_ERR_DATA_CMP_FAIL;
	        }
	    }
	    nand_debug(0,1,"data compare ok: page.%lX\n", (u32_row+u16_i) & pNandDrv->u16_BlkPageCntMask);

		for(u16_j=0; u16_j<pNandDrv->u16_PageSectorCnt; u16_j++)
		{
			#if SPARE640B_CIFD512B_PATCH
			if((u16_j+1) * pNandDrv->u16_SectorSpareByteCnt > 0x200)
			    break;
			#endif
	        if(NCTEST_DataCompare(
		        apu8_scrambled[u16_i] + (u16_j+1)*pNandDrv->u16_SectorByteCnt + u16_j*pNandDrv->u16_SectorSpareByteCnt,
		        au8_RSpare + u16_j*pNandDrv->u16_SectorSpareByteCnt,
		        pNandDrv->u16_SectorSpareByteCnt-pNandDrv->u16_ECCCodeByteCnt))
	        {
		        nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR.9, spare mismatch, Sector:%X \n", u16_i);
		        //return UNFD_ST_ERR_DATA_CMP_FAIL;
	        }
		}
	nand_debug(0,1,"spare compare ok: page.%lX\n", (u32_row+u16_i) & pNandDrv->u16_BlkPageCntMask);
	}

	u16_loop++;
	if(u16_loop < 4)
		goto LABEL_R_LFSR_TEST;

	LABEL_LFSR_TEST_END:
	pNandDrv->u16_Reg50_EccCtrl &= ~BIT_NC_BYPASS_ECC;
	NC_Config();

	return u32_Err;
}

#endif
// =====================================================
#define READ_COUNT_SHOW_LOG  10000
static U32 u32_counter=0;
static U8 u8_log_flag=0;

U32 NCTEST_WBlkLSBPages(U32 u32_PBA, U32 u32_PageCnt)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;
	U32 u32_ByteIdx, u32_TestRow;
	U16 u16_PageIdx;
	U16 *au16_WritePageBuf;
	U8  *au8_WSpare;
    U16 i,j,u16_pattern_size;

	au16_WritePageBuf = (U16*)DMA_W_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;

	// prepare test pattern
	u16_pattern_size = pNandDrv->u16_PageByteCnt/8/2;
	for(i=0 ; i<8 ; i++)
	{
		switch(i)
		{
			case 0:
				for(j=0 ; j<u16_pattern_size ; j++)
					au16_WritePageBuf[i*u16_pattern_size + j] = 0x0000;
				break;
			case 1:
				for(j=0 ; j<u16_pattern_size ; j++)
					au16_WritePageBuf[i*u16_pattern_size + j] = 0xFFFF;
				break;
			case 2:
				for(j=0 ; j<u16_pattern_size ; j++)
					au16_WritePageBuf[i*u16_pattern_size + j] = 0x0FF0;
				break;
			case 3:
				for(j=0 ; j<u16_pattern_size ; j++)
					au16_WritePageBuf[i*u16_pattern_size + j] = 0xFF00;
				break;
			case 4:
				for(j=0 ; j<u16_pattern_size ; j++)
					au16_WritePageBuf[i*u16_pattern_size + j] = 0x55AA;
				break;
			case 5:
				for(j=0 ; j<u16_pattern_size ; j++)
					au16_WritePageBuf[i*u16_pattern_size + j] = 0x5A5A;
				break;
			case 6:
				for(j=0 ; j<u16_pattern_size*2 ; j++)
					((U8 *)au16_WritePageBuf)[i*u16_pattern_size*2 + j] = j;
				break;
			case 7:
				for(j=0 ; j<u16_pattern_size*2 ; j++)
					((U8 *)au16_WritePageBuf)[i*u16_pattern_size*2 + j] = 0xFF-j;
				break;
			default:
				break;
		}
	}

	for (u32_ByteIdx = 0; u32_ByteIdx < pNandDrv->u16_SpareByteCnt; u32_ByteIdx++)
	{
		au8_WSpare[u32_ByteIdx] = 0xFF;
	}

    u32_TestRow = u32_PBA * pNandDrv->u16_BlkPageCnt;
	/* erase the first blk */
	u32_Err = NC_EraseBlk(u32_TestRow &~ pNandDrv->u16_BlkPageCntMask);

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: Erase Fail, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	/* W each page */
	for (u16_PageIdx = 0; u16_PageIdx < (u32_PageCnt>>1); u16_PageIdx++)
	{
		u32_Err = NC_WritePages(u32_TestRow + ga_tPairedPageMap[u16_PageIdx].u16_LSB, (U8 *)au16_WritePageBuf, au8_WSpare, 1);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_WritePages Fail, ErrCode: 0x%08lx\n", u32_Err);
			return u32_Err;
		}
	}

	return UNFD_ST_SUCCESS;
}

// =====================================================

static U32 NCTEST_WBlkPages(U32 u32_PBA, U16 u16_PageCnt)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;
	U32 u32_ByteIdx,u32_TestRow;
	U16 u16_PageIdx;

	U16 *au16_WritePageBuf;
	U8  *au8_WSpare;
    U16 i,j,u16_pattern_size;


	au16_WritePageBuf = (U16*)DMA_W_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;

	// prepare test pattern
	u16_pattern_size = pNandDrv->u16_PageByteCnt/8/2;
	for(i=0 ; i<8 ; i++)
	{
		switch(i)
		{
			case 0:
				for(j=0 ; j<u16_pattern_size ; j++)
					au16_WritePageBuf[i*u16_pattern_size + j] = 0x0000;
				break;
			case 1:
				for(j=0 ; j<u16_pattern_size ; j++)
					au16_WritePageBuf[i*u16_pattern_size + j] = 0xFFFF;
				break;
			case 2:
				for(j=0 ; j<u16_pattern_size ; j++)
					au16_WritePageBuf[i*u16_pattern_size + j] = 0x0FF0;
				break;
			case 3:
				for(j=0 ; j<u16_pattern_size ; j++)
					au16_WritePageBuf[i*u16_pattern_size + j] = 0xFF00;
				break;
			case 4:
				for(j=0 ; j<u16_pattern_size ; j++)
					au16_WritePageBuf[i*u16_pattern_size + j] = 0x55AA;
				break;
			case 5:
				for(j=0 ; j<u16_pattern_size ; j++)
					au16_WritePageBuf[i*u16_pattern_size + j] = 0x5A5A;
				break;
			case 6:
				for(j=0 ; j<u16_pattern_size*2 ; j++)
					((U8 *)au16_WritePageBuf)[i*u16_pattern_size*2 + j] = j;
				break;
			case 7:
				for(j=0 ; j<u16_pattern_size*2 ; j++)
					((U8 *)au16_WritePageBuf)[i*u16_pattern_size*2 + j] = 0xFF-j;
				break;
			default:
				break;
		}
	}


	for (u32_ByteIdx = 0; u32_ByteIdx < pNandDrv->u16_SpareByteCnt; u32_ByteIdx++)
	{
		au8_WSpare[u32_ByteIdx] = 0xFF;
	}

	u32_TestRow = u32_PBA * pNandDrv->u16_BlkPageCnt;
	/* erase the first blk */
	u32_Err = NC_EraseBlk(u32_TestRow &~ pNandDrv->u16_BlkPageCntMask);

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: Erase Fail, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	/* W each page */
	for (u16_PageIdx = 0; u16_PageIdx < u16_PageCnt; u16_PageIdx++)
	{
		u32_Err = NC_WritePages(u32_TestRow+u16_PageIdx , (U8 *)au16_WritePageBuf, au8_WSpare, 1);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: WritePages Fail, ErrCode: 0x%08lx\n", u32_Err);
			return u32_Err;
		}
	}

	return UNFD_ST_SUCCESS;
}
// =====================================================

U32 NCTEST_RBlkLSBPages(U32 u32_PBA, U16 u16_PageCnt)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err,u32_TestRow;
	U16 u16_PageIdx;
	U8 *au8_R;
	U8 *au8_RSpare;
    U32 u32_Corretable_ECC;
	U32 u32_Max_Corretable_ECC;
	U16 u16_Max_Corretable_ECC_PageIdx;

	/* setup buffers */
	au8_R = (U8*)DMA_R_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	u32_Max_Corretable_ECC = 0;
	u16_Max_Corretable_ECC_PageIdx = ga_tPairedPageMap[0].u16_LSB;

    u32_TestRow = u32_PBA * pNandDrv->u16_BlkPageCnt;
    /* R each page */
    for (u16_PageIdx = 0; u16_PageIdx < (u16_PageCnt>>1); u16_PageIdx++)
    {
    	u32_Err = NC_ReadPages(u32_TestRow + ga_tPairedPageMap[u16_PageIdx].u16_LSB, au8_R, au8_RSpare, 1);
    	if (u32_Err != UNFD_ST_SUCCESS)
    	{
    		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ReadPage Fail, ErrCode: 0x%08lx\n", u32_Err);
    		return u32_Err;
    	}

		u32_Corretable_ECC = NC_GetECCBits();
        if(u8_log_flag ==1)
       	{
			if(u32_Corretable_ECC > u32_Max_Corretable_ECC)
			{
			    u16_Max_Corretable_ECC_PageIdx = ga_tPairedPageMap[u16_PageIdx].u16_LSB;
				u32_Max_Corretable_ECC = u32_Corretable_ECC;
        	}
		}
    }

	if(u8_log_flag == 1)
	{
		nand_debug(UNFD_DEBUG_LEVEL, 0, "Blk: 0x%lX  Page: 0x%X Max Corretable_ECC: 0x%lX\r\n",
        u32_PBA, u16_Max_Corretable_ECC_PageIdx, u32_Max_Corretable_ECC);
	}
	return UNFD_ST_SUCCESS;
}

// =====================================================
U32 NCTEST_ReadLoopInitData(U32 u32_PBA)
{
	U32 u32_Err = UNFD_ST_SUCCESS;
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
    U32 u32_BlkIdx;
	U32 u32_BlkCnt;
	U8 *au8_R;
	U8 *au8_RSpare;
	U8 *pu8_BadBlk;
	/* setup buffers */
	au8_R = (U8*)DMA_R_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;
	nand_clock_setting(FCIE3_SW_DEFAULT_CLK);

	nand_debug(0, 1, "===================================\n");
	nand_debug(0, 1, "NAND ReadLoopInitData              \n");
	nand_debug(0, 1, "===================================\n");
	pu8_BadBlk = (U8*)DMA_BAD_BLK_BUF;
	memset(pu8_BadBlk, 0xFF, pNandDrv->u16_BlkCnt >> 3);
	NC_DisableLFSR();
    NCTEST_MLCScanBadBlk(pu8_BadBlk);

	u32_BlkCnt = 0;
	u32_BlkIdx = u32_PBA;
	//NC_DisableLFSR();
	while(u32_BlkCnt <2)
	{
	    #if 1
		if (!(pu8_BadBlk[u32_BlkIdx >> 3] & (1 << (u32_BlkIdx & 0x7))))
		{
			nand_debug(UNFD_DEBUG_LEVEL, 1, "Skip bad blk: 0x%08lx\n", u32_BlkIdx);
			u32_BlkIdx++;
			continue;
		}
	    #endif
		u32_Err = NCTEST_WBlkLSBPages(u32_BlkIdx, pNandDrv->u16_BlkPageCnt);
    	if (u32_Err != UNFD_ST_SUCCESS)
    	{
    		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_WSinglePages Fail~\n");
    		return u32_Err;
    	}
		u32_BlkIdx++;
		u32_BlkCnt++;
	}

	nand_debug(UNFD_DEBUG_LEVEL, 1, "Write LSB Page with no Randomizer Success\n");
	#if 1
	NC_EnableLFSR();
	u32_BlkCnt = 0;

	while(u32_BlkCnt <2)
	{
	    #if 1
		if (!(pu8_BadBlk[u32_BlkIdx >> 3] & (1 << (u32_BlkIdx & 0x7))))
		{
			nand_debug(UNFD_DEBUG_LEVEL, 1, "Skip bad blk: 0x%08lx\n", u32_BlkIdx);
			u32_BlkIdx++;
			continue;
		}
	    #endif
		u32_Err = NCTEST_WBlkLSBPages(u32_BlkIdx, pNandDrv->u16_BlkPageCnt);
    	if (u32_Err != UNFD_ST_SUCCESS)
    	{
    		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_WSinglePages Fail~\n");
    		return u32_Err;
    	}
		u32_BlkIdx++;
		u32_BlkCnt++;
	}

    nand_debug(UNFD_DEBUG_LEVEL, 1, "Write LSB Page with Randomizer Success\n");
    #endif
	#if 1
	u32_BlkCnt = 0;

	while(u32_BlkCnt <2)
	{
	    #if 1
		if (!(pu8_BadBlk[u32_BlkIdx >> 3] & (1 << (u32_BlkIdx & 0x7))))
		{
			nand_debug(UNFD_DEBUG_LEVEL, 1, "Skip bad blk: 0x%08lx\n", u32_BlkIdx);
			u32_BlkIdx++;
			continue;
		}
	    #endif
		u32_Err = NCTEST_WBlkPages(u32_BlkIdx, pNandDrv->u16_BlkPageCnt);
    	if (u32_Err != UNFD_ST_SUCCESS)
    	{
    		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_WSinglePages Fail~\n");
    		return u32_Err;
    	}
		u32_BlkIdx++;
		u32_BlkCnt++;
	}
	nand_debug(UNFD_DEBUG_LEVEL, 1, "Write LSB/MSB Page with Randomizer Success\n");
	#endif
	return u32_Err;
}
// =====================================================
U32 NCTEST_ReadLoop(U32 u32_PBA)
{
	U32 u32_Err = UNFD_ST_SUCCESS;
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
    U32 u32_BlkIdx;
	U32 u32_BlkCnt;

	U8 *au8_R;
	U8 *au8_RSpare;
	U8 *pu8_BadBlk;
	/* setup buffers */
	au8_R = (U8*)DMA_R_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;
	nand_clock_setting(FCIE3_SW_DEFAULT_CLK);

	nand_debug(0, 1, "===================================\n");
	nand_debug(0, 1, "NAND ReadLoop                      \n");
	nand_debug(0, 1, "===================================\n");

	pu8_BadBlk = (U8*)DMA_BAD_BLK_BUF;
	memset(pu8_BadBlk, 0xFF, pNandDrv->u16_BlkCnt >> 3);
	NC_DisableLFSR();
    NCTEST_MLCScanBadBlk(pu8_BadBlk);

    while(1)
    {
		if(((u32_counter % READ_COUNT_SHOW_LOG) ==0) && (u32_counter >0))
		{
		    nand_debug(UNFD_DEBUG_LEVEL, 0, "==================================================\n");
			nand_debug(UNFD_DEBUG_LEVEL, 1, "Read Page Loop:%lX\n",u32_counter);
			u8_log_flag =1;
		}

		NC_DisableLFSR();
		u32_BlkCnt =0;
		u32_BlkIdx = u32_PBA;
		if(u8_log_flag ==1)
		{
		    nand_debug(UNFD_DEBUG_LEVEL, 1, "Reaad LSB Page with  MSB Empity and Has No Randomizer\n");
		}
    	while(u32_BlkCnt <2)
    	{
    		#if 1
			if (!(pu8_BadBlk[u32_BlkIdx >> 3] & (1 << (u32_BlkIdx & 0x7))))
			{
				nand_debug(UNFD_DEBUG_LEVEL, 1, "Skip bad blk: 0x%08lx\n", u32_BlkIdx);
				u32_BlkIdx++;
				continue;
			}
 			#endif

    		u32_Err = NCTEST_RBlkLSBPages(u32_BlkIdx, pNandDrv->u16_BlkPageCnt);
    		if (u32_Err != UNFD_ST_SUCCESS)
    		{
    			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RSingleLSBPages Fail~\n");
    			return u32_Err;
    		}
			u32_BlkCnt++;
			u32_BlkIdx++;
    	}
		u32_BlkCnt =0;
        #if 1
		NC_EnableLFSR();
		if(u8_log_flag ==1)
		{
		    nand_debug(UNFD_DEBUG_LEVEL, 0, "-------------------------------------\n");
		    nand_debug(UNFD_DEBUG_LEVEL, 1, "Reaad LSB Page with MSB Empity and Has Randomizer\n");
		}
		while(u32_BlkCnt <2)
		{
            #if 1
			if (!(pu8_BadBlk[u32_BlkIdx >> 3] & (1 << (u32_BlkIdx & 0x7))))
			{
				nand_debug(UNFD_DEBUG_LEVEL, 1, "Skip bad blk: 0x%08lx\n", u32_BlkIdx);
				u32_BlkIdx++;
				continue;
			}
            #endif

    		u32_Err = NCTEST_RBlkLSBPages(u32_BlkIdx, pNandDrv->u16_BlkPageCnt);
    		if (u32_Err != UNFD_ST_SUCCESS)
    		{
    			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RSingleLSBPages Fail~\n");
    			return u32_Err;
    		}
			u32_BlkCnt++;
			u32_BlkIdx++;
		}
        #endif
        #if 1
		u32_BlkCnt =0;
		if(u8_log_flag ==1)
		{
		    nand_debug(UNFD_DEBUG_LEVEL, 0, "-------------------------------------\n");
		    nand_debug(UNFD_DEBUG_LEVEL, 1, "Reaad LSB Page with MSB/LSB FUll and Has Randomizer\n");
		}
		while(u32_BlkCnt <2)
		{
            #if 1
			if (!(pu8_BadBlk[u32_BlkIdx >> 3] & (1 << (u32_BlkIdx & 0x7))))
			{
				nand_debug(UNFD_DEBUG_LEVEL, 1, "Skip bad blk: 0x%08lx\n", u32_BlkIdx);
				u32_BlkIdx++;
				continue;
			}
            #endif

    		u32_Err = NCTEST_RBlkLSBPages(u32_BlkIdx, pNandDrv->u16_BlkPageCnt);
    		if (u32_Err != UNFD_ST_SUCCESS)
    		{
    			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_RSingleLSBPages Fail~\n");
    			return u32_Err;
    		}
			u32_BlkCnt++;
			u32_BlkIdx++;
		}
		#endif

    	u32_counter++;

        if(u8_log_flag ==1)
		   u8_log_flag =0;
    }

    return u32_Err;

}
// =====================================================
#if defined(EMMC_PLL_1XCLK_TABLE_CNT)
DDR_TIMING_GROUP_t all_clock_timing[EMMC_PLL_1XCLK_TABLE_CNT];

#define FCIE_IP_TEST_SUITE_ENABLE  1
#define FCIE_IP_TEST_SUITE_BURNIN  0
#else
#define FCIE_IP_TEST_SUITE_ENABLE  0
#define FCIE_IP_TEST_SUITE_BURNIN  0
#endif
U32 drvNAND_IPVerify_Main(void)
{
	volatile U32 u32_Err, u32_TestRow;
	#if FCIE_IP_TEST_SUITE_BURNIN
	U32 u32_i, u32_TestLoop=0;
	#endif
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();

	nand_debug(0, 1, "===================================\n");
	nand_debug(0, 1, "Unified NFIE Verification Program  \n");
	nand_debug(0, 1, "===================================\n");

	/* pad switch */
	nand_pads_switch(1);

	/* set clock */
	nand_clock_setting(FCIE3_SW_DEFAULT_CLK);

	nand_debug(0, 1, "RIU_BASE: 0x%08x\n", RIU_BASE);
	nand_debug(0, 1, "FCIE_REG_BASE_ADDR: 0x%08x\n", FCIE_REG_BASE_ADDR);
	nand_debug(0, 1, "FCIE_NC_CIFD_BASE: 0x%08x\n", FCIE_NC_CIFD_BASE);
	/* clean NandDrv */
	memset(pNandDrv, '\0', sizeof(*pNandDrv));

	/* config NandDrv */
	pNandDrv->u8_OpCode_RW_AdrCycle = NAND_RW_ADR_CYCLE_CNT;
	pNandDrv->u8_OpCode_Erase_AdrCycle = NAND_E_ADR_CYCLE_CNT;
	pNandDrv->u16_ECCType = NAND_ECC_TYPE;

	pNandDrv->u16_BlkCnt = NAND_BLK_CNT;
	pNandDrv->u16_BlkPageCnt = NAND_BLK_PAGE_CNT;
	pNandDrv->u16_PageByteCnt = NAND_PAGE_BYTE_CNT;
	pNandDrv->u16_SpareByteCnt = NAND_SPARE_BYTE_CNT;
	pNandDrv->u8_IDByteCnt = NAND_DEVICE_ID_LEN;

	#if defined(MT29F64G08CBAAB) &&MT29F64G08CBAAB
	pNandDrv->u16_tRC = 20;
	pNandDrv->u8_tRP = 10;
	pNandDrv->u8_tREH = 7;
	pNandDrv->u8_tREA = 16;
	pNandDrv->u8_tRR = 20;
	pNandDrv->u16_tADL = 70;
	pNandDrv->u16_tRHW = 100;
	pNandDrv->u16_tWHR = 60;
	pNandDrv->u16_tCCS = 200;
	pNandDrv->u8_tCS = 15;
	pNandDrv->u16_tWC = 20;
	pNandDrv->u8_tWP = 10;
	pNandDrv->u8_tWH = 7;
	pNandDrv->u16_tCWAW = 0;
	pNandDrv->u8_tCLHZ = 0;
	pNandDrv->u16_tWW = 100;
	#endif

	NC_PlatformInit();

	NC_ConfigNandFlashContext();

	/* init & config NC */
	u32_Err = NC_Init();

	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: init FCIE fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}

	//NC_Config();
	nand_debug(0, 1, "NFIE RIU access ok!\n\n");
	#if defined(MT29F64G08CBAAB) &&MT29F64G08CBAAB
	au8_nand_clk_max = NFIE_4CLK_TABLE_CNT - 1;

	nand_config_clock(pNandDrv->u8_tREA);
	#endif

	dump_nand_driver(pNandDrv);

	u32_TestRow = pNandDrv->u16_BlkPageCnt*40; // select which block to test, avoid to use block.0 always.

    #if 0
	//for(u32_Err=0; u32_Err<10; u32_Err++)
	//	NCTEST_DumpPages(pNandDrv->u16_BlkPageCnt * u32_Err, 1);
	NCTEST_DumpMG();
    while(1);
    #endif

    #if 0
	//NCTEST_EarseAllBlk();
	//NCTEST_EraseAllGoodBlks();
	//NCTEST_WriteImagesForROM();
	//NCTEST_ECC_RS_BurnIn();
	//while(1);
    #endif

	//pNandDrv->u16_Reg50_EccCtrl |= BIT_NC_DYNAMIC_OFFCLK; // for test
	//pNandDrv->u16_Reg50_EccCtrl |= BIT_NC_ALL0xFF_ECC_CHECK; // for test
	//pNandDrv->u16_Reg50_EccCtrl |= BIT_NC_BYPASS_ECC; // for test
	//REG_WRITE_UINT16(NC_RAND_R_CMD, 0x2233);
	//REG_WRITE_UINT16(NC_RAND_W_CMD, 0x0066);
	//pNandDrv->u16_Reg48_Spare |= BIT_NC_HW_AUTO_RANDOM_CMD_DISABLE;
	// FIXME
	// nand_platform_init();

    #if 0
	/* check the data bus */
	//count_down(5);
	//NCTEST_Check_DBus();  //goto LABEL_END_OF_TESTS;

	NCTEST_HWECCCheckNotAllFF(u32_TestRow);
    NCTEST_LFSRTest();
	//NCTEST_HWECCSpare640B(u32_TestRow);

	//NCTEST_HWRepeatModeTest();

	//NC_ReadPages(0X1C7F, (U8*)DMA_R_ADDR, (U8*)DMA_W_SPARE_ADDR, 1);
	//NCTEST_DumpECCRegisters();
	while(1);
	nand_die();
    #endif

    #if 0
	    nand_debug(2, 1, "RW Verify 16bits waveform...\n");
	    u32_Err = NCTEST_Verify_16bits(3, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "ERROR: RW Verify 16bits waveform fail, ErrCode: 0x%08x\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(2, 1, "RW Verify 16bits waveform end\n\n");
	while(1);
    #endif

    //--------------------------------------
    #if 0 || FCIE_IP_TEST_SUITE_ENABLE
	u32_Err = NCTEST_AccessCIFD();
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: Access CIFD fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(UNFD_DEBUG_LEVEL_HIGH, 1, "CIFD scan ok!\n\n");
	#else
	u32_Err = (U32)NCTEST_AccessCIFD; // to avoid compiler warning
    #endif

    //--------------------------------------
    #if 0 || FCIE_IP_TEST_SUITE_ENABLE
    NCTEST_VerifyDMAAddress();
	#else
	u32_Err = (U32)NCTEST_VerifyDMAAddress; // to avoid compiler warning
    #endif

    //--------------------------------------
    #if (0 || FCIE_IP_TEST_SUITE_ENABLE) && !(defined(FCIE4_DDR) && FCIE4_DDR)
    NC_ResetNandFlash();
	u32_Err = NCTEST_ReadID();
	//while(1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ReadID fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(0, 1, "Read ID ok! -> issue CMD/ADR/DAT ok\n\n");

    #if 0
	NCTEST_InitDisp();
	nand_debug(0,1,"repeat reading id...\n");
	while(1)
	    if(UNFD_ST_SUCCESS != NCTEST_ReadID())
			break;

	*(volatile U16*)0x2A00724C |= (U16)BIT13; // not gate Disp clk]
	while(1);
	#endif
	#else
	u32_Err = (U32)NCTEST_ReadID; // to avoid compiler warning
    #endif

    //--------------------------------------
	// NCTEST_ResetTorture();
    #if 0 || FCIE_IP_TEST_SUITE_ENABLE
	u32_Err = NC_EraseBlk(u32_TestRow);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
	    nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NC_EraseBlk fail, ErrCode: 0x%08lx\n", u32_Err);
	    goto LABEL_END_OF_TESTS;
	}
	nand_debug(0, 1, "Erase Blk ok!\n\n");
    #endif


    #if FCIE_IP_TEST_SUITE_BURNIN
	for(u32_TestLoop = 0; u32_TestLoop < NFIE_4CLK_TABLE_CNT - 1; u32_TestLoop ++)
	{
		pNandDrv->tDefaultDDR.u8_DdrTiming = 0;
		au8_nand_clk_max = u32_TestLoop;
		nand_config_clock(pNandDrv->u8_tREA);
		memcpy(&all_clock_timing[u32_TestLoop], &pNandDrv->tDefaultDDR, sizeof(DDR_TIMING_GROUP_t));
	}
	u32_TestLoop = 0;
	u32_TestRow = pNandDrv->u16_BlkPageCnt * 9;
    LABEL_IP_TEST_SUITE_BURNIN:
	#if defined(MT29F64G08CBAAB) &&MT29F64G08CBAAB
//	au8_nand_clk_max = EMMC_PLL_1XCLK_100M_IDX;

	memcpy( &pNandDrv->tDefaultDDR, &all_clock_timing[u32_TestLoop % NFIE_4CLK_TABLE_CNT], sizeof(DDR_TIMING_GROUP_t));
	nand_config_clock(pNandDrv->u8_tREA);
	#endif
	u32_TestRow += pNandDrv->u16_BlkPageCnt;
	if(u32_TestRow >= ((pNandDrv->u16_BlkCnt -0x20) << pNandDrv->u8_BlkPageCntBits))
		u32_TestRow = pNandDrv->u16_BlkPageCnt * 10; // start from blk.10

	while(drvNAND_IsGoodBlk(u32_TestRow >> pNandDrv->u8_BlkPageCntBits) == 0)
	{
		nand_debug(0,1, "Skip Bad PBA 0x%X\n", u32_TestRow >> pNandDrv->u8_BlkPageCntBits);
		u32_TestRow += pNandDrv->u16_BlkPageCnt;
		if(u32_TestRow >= ((pNandDrv->u16_BlkCnt -0x20) << pNandDrv->u8_BlkPageCntBits))
			u32_TestRow = 10 * pNandDrv->u16_BlkPageCnt;
	}

	nand_debug(UNFD_DEBUG_LEVEL, 1, "\n\n");
	nand_debug(UNFD_DEBUG_LEVEL, 1, "=======================\n");
	nand_debug(UNFD_DEBUG_LEVEL, 1, "Burn-in Loop: %lX,  Blk: %lX\n", u32_TestLoop, u32_TestRow>>pNandDrv->u8_BlkPageCntBits);
	nand_debug(UNFD_DEBUG_LEVEL, 1, "=======================\n");

	u32_TestLoop++;
	#endif
    //--------------------------------------
    #if 0 || FCIE_IP_TEST_SUITE_ENABLE
	nand_debug(0, 1, "RandomRW Test...\n");

	u32_Err = NCTEST_RandomRW();

	if (u32_Err != UNFD_ST_SUCCESS)
	{
	    nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RandomRW fail, ErrCode: 0x%08lx\n", u32_Err);
		#if FCIE_IP_TEST_SUITE_BURNIN
		goto LABEL_IP_TEST_SUITE_BURNIN;
		#else
	    goto LABEL_END_OF_TESTS;
		#endif
	}
    nand_debug(0, 1, "RandomRW ok!\n\n");
	#else
	u32_Err = (U32)NCTEST_RandomRW; // to avoid compiler warning
    #endif

    #if (0 || FCIE_IP_TEST_SUITE_ENABLE)
	nand_debug(0, 1, "RandomRW_MIU Test...\n");

	u32_Err = NCTEST_RandomRW_MIU();

	if (u32_Err != UNFD_ST_SUCCESS)
	{
	    nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RandomRW_MIU fail, ErrCode: 0x%08lx\n", u32_Err);
		#if FCIE_IP_TEST_SUITE_BURNIN
		goto LABEL_IP_TEST_SUITE_BURNIN;
		#else
	    goto LABEL_END_OF_TESTS;
		#endif
	}
    nand_debug(0, 1, "RandomRW_MIU ok!\n\n");
    #else
	u32_Err = (U32)NCTEST_RandomRW_MIU; // to avoid compiler warning
    #endif

    //--------------------------------------
    #if 0 || FCIE_IP_TEST_SUITE_ENABLE
	if(pNandDrv->u16_SpareByteCnt <= 512){ // spare area <= CIFD size
	nand_debug(0, 1, "RW Single Pages RIU Mode Test...\n");

	u32_Err = NCTEST_RWSinglePages_RM(u32_TestRow+0, 3);

	if(u32_Err != UNFD_ST_SUCCESS)
	{
	    nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RW Single Pages RM fail, ErrCode: 0x%08lx\n", u32_Err);
	    goto LABEL_END_OF_TESTS;
	}
	nand_debug(0, 1, "RW Single Pages RM ok!\n");}
    #endif

    //--------------------------------------
    #if 0 || FCIE_IP_TEST_SUITE_ENABLE
	nand_debug(0, 1, "RW Single Pages Test...\n");
	u32_Err = NCTEST_RWSinglePages(u32_TestRow+4, 3);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RW Single Pages fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(0, 1, "RW Single Pages ok!\n\n");
    #endif

    //--------------------------------------
	#if 0 || FCIE_IP_TEST_SUITE_ENABLE
	nand_debug(0, 1, "RW MultiplePages_OneTime Test...\n");
	//NC_FCIE4SetInterface(0,0,0,0);
	u32_Err = NCTEST_RWMultiplePages_OneTime(u32_TestRow, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RW MultiplePages_OneTime fail 0, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(0, 1, "RW MultiplePages_OneTime Test 0 ok!...\n");

	u32_Err = NCTEST_RWMultiplePages_OneTime(u32_TestRow, pNandDrv->u16_BlkPageCnt-1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RW MultiplePages_OneTime fail 1, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(0, 1, "RW MultiplePages_OneTime Test 1 ok!...\n");

	u32_Err = NCTEST_RWMultiplePages_OneTime(u32_TestRow, pNandDrv->u16_BlkPageCnt);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RW MultiplePages_OneTime fail 2, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(0, 1, "RW MultiplePages_OneTime Test 2 ok! -> Repeat Cnt ok.\n\n");
    #endif

    //--------------------------------------
    #if 0 || FCIE_IP_TEST_SUITE_ENABLE
	nand_debug(0, 1, "RWSinglePages_Partial_SWRepeat Test...\n");
	u32_Err = NCTEST_RWSinglePages_Partial_SWRepeat1(u32_TestRow);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}

	u32_Err = NCTEST_RWSinglePages_Partial_SWRepeat2(u32_TestRow, 3);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWSinglePages_Partial_SWRepeat fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(0, 1, "RWSinglePages_Partial_SWRepeat ok!\n\n");

	nand_debug(0, 1, "RWSinglePages_Partial_HWRepeat Test...\n");
	u32_Err = NCTEST_RWMultiplePages_Partial_HWRepeat(u32_TestRow, pNandDrv->u16_BlkPageCnt - 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_Partial_HWRepeat fail 1, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	u32_Err = NCTEST_RWMultiplePages_Partial_HWRepeat(u32_TestRow, pNandDrv->u16_BlkPageCnt);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RWMultiplePages_Partial_HWRepeat fail 2, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}

	nand_debug(0, 1, "RWMultiplePages_Partial_HWRepeat ok! -> Parital Mode + Repeat Cnt ok.\n\n");
    #else
	u32_Err = (U32)NCTEST_RWSinglePages_Partial_SWRepeat1; // to avoid compiler warning
	u32_Err = (U32)NCTEST_RWMultiplePages_Partial_HWRepeat; // to avoid compiler warning
    #endif

	//--------------------------------------
    #if (0 || FCIE_IP_TEST_SUITE_ENABLE) && (defined(FCIE_LFSR) && FCIE_LFSR)
	nand_debug(0, 1, "LFSRTest Test...\n");
	//NC_FCIE4SetInterface(0,0,0,0);
	u32_Err = NCTEST_LFSRTest(u32_TestRow>>pNandDrv->u8_BlkPageCntBits);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		 nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: LFSRTest fail, ErrCode: 0x%08lx\n", u32_Err);
		 goto LABEL_END_OF_TESTS;
	}
	nand_debug(0, 1, "LFSRTest ok!\n\n");
	#endif


    //--------------------------------------
    #if 0 || FCIE_IP_TEST_SUITE_ENABLE
    nand_debug(0, 1, "PageCopy Test...\n");

    u32_Err = NCTEST_PageCopy();

    if (u32_Err != UNFD_ST_SUCCESS)
    {
        nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: PageCopy fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(0, 1, "PageCopy ok!\n\n");
    #else
	u32_Err = (U32)NCTEST_PageCopy; // to avoid compiler warning
	#endif

	//--------------------------------------
    #if 0 || FCIE_IP_TEST_SUITE_ENABLE
	nand_debug(0, 1, "ECC_For_All_0xff_Pages Test...\n");
	u32_Err = NCTEST_ECC_For_All_0xFF_Pages(u32_TestRow);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
	    nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ECC_For_All_0xff_Pages fail, ErrCode: 0x%08lx\n", u32_Err);
	    goto LABEL_END_OF_TESTS;
	}
	nand_debug(0, 1, "ECC_For_All_0xff_Pages ok!\n\n");
    #else
	u32_Err = (U32)NCTEST_ECC_For_All_0xFF_Pages; // to avoid compiler warning
	#endif

	//--------------------------------------
    #if 0 || FCIE_IP_TEST_SUITE_ENABLE//finish
	nand_debug(0, 1, "ECC_Generation_Bypass Test...\n");

	u32_Err = NCTEST_ECC_Generation_Bypass(u32_TestRow);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ECC_Generation_Bypass fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(0, 1, "ECC_Generation_Bypass ok!\n\n");
    #else
	u32_Err = (U32)NCTEST_ECC_Generation_Bypass; // to avoid compiler warning
	#endif

	//--------------------------------------
    #if 0 || FCIE_IP_TEST_SUITE_ENABLE//finish
	nand_debug(0, 1, "NCTEST_HWECCCheckNotAllFF Test...\n");

	u32_Err = NCTEST_HWECCCheckNotAllFF(u32_TestRow);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_HWECCCheckNotAllFF fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(0, 1, "NCTEST_HWECCCheckNotAllFF ok!\n\n");
    #endif

	#if (0|| FCIE_IP_TEST_SUITE_ENABLE) // Only SLC NAND
	nand_debug(2, 1, "ECC_ALL_BCH Test...\n");
	pNandDrv->u8_IfECCTesting = 1;
	u32_Err = NCTEST_ALL_ECC_BCH(u32_TestRow);
	pNandDrv->u8_IfECCTesting = 0;
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "ERROR: ECC_ALL_BCH fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(2, 1, "ECC_ALL_BCH ok!\n");
	#else
	u32_Err = (U32)NCTEST_ALL_ECC_BCH; // to avoid compiler warning
	#endif

	#if (0 || FCIE_IP_TEST_SUITE_ENABLE)    // Only SDR mode
	nand_debug(2, 1, "All_Page_Mode Test...\n");
	u32_Err = NCTEST_All_Page_Mode();
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "ERROR: All_Page_Mode fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(2, 1, "All_Page_Mode  ok!\n");
	#else
	u32_Err = (U32)NCTEST_All_Page_Mode; // to avoid compiler warning
	#endif

	#if (0 || FCIE_IP_TEST_SUITE_ENABLE)
	nand_debug(2, 1, "ECC_BCH_PageMode  Test...\n");
	pNandDrv->u8_IfECCTesting = 1;
	u32_Err = NCTEST_ECC_BCH_PageMode(u32_TestRow);
	pNandDrv->u8_IfECCTesting = 0;
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "ERROR: ECC_BCH_PageMode  fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(2, 1, "ECC_BCH_PageMode  ok!\n");
	#endif

	//--------------------------------------
	#if 0  || FCIE_IP_TEST_SUITE_ENABLE
	nand_debug(0, 1, "byte offset dma Test...\n");
	u32_Err = NCTEST_BYTE_OFFSET_DMA(u32_TestRow);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: byte offset dma fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(0, 1, "byte offset dma ok!\n\n");
	#else
	u32_Err = (U32)NCTEST_BYTE_OFFSET_DMA; // to avoid compiler warning
	#endif

	#if defined(NC_SEL_FCIE5) && NC_SEL_FCIE5
	
	#if (0 || FCIE_IP_TEST_SUITE_ENABLE)
	nand_debug(0, 1, "RW MultiplePages_OneTime ADMA Test...\n");
	//NC_FCIE4SetInterface(0,0,0,0);
	u32_Err = NCTEST_RWMultiplePages_OneTimeADMA(u32_TestRow);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: RW MultiplePages_OneTime ADMA fail 0, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(0, 1, "RW MultiplePages_OneTime ADMA Test 0 ok!...\n");
	#endif
	
	#if (1 || FCIE_IP_TEST_SUITE_ENABLE) && (defined(FCIE_ZDEC_TEST) && FCIE_ZDEC_TEST)
	nand_debug(0, 1, "ZDEC Test...\n");
	
	nand_debug(0, 1, "96.bin case1\n");
	u32_Err = NCTEST_ZDEC(u32_TestRow, __96_zlib_prop_1_bin, __96_zlib_prop_1_bin_len, squashfs_test_1_96_35731_131072_bin, 131072);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ZDEC Test fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	u32_Err = NCTEST_ZDEC2(u32_TestRow, __96_zlib_prop_1_bin, __96_zlib_prop_1_bin_len, squashfs_test_1_96_35731_131072_bin, 131072);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ZDEC Test fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}

	nand_debug(0, 1, "96.bin case2\n");
	u32_Err = NCTEST_ZDEC(u32_TestRow, __96_zlib_prop_2_bin, __96_zlib_prop_2_bin_len, squashfs_test_1_96_35731_131072_bin, 131072);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ZDEC Test fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	u32_Err = NCTEST_ZDEC2(u32_TestRow, __96_zlib_prop_2_bin, __96_zlib_prop_2_bin_len, squashfs_test_1_96_35731_131072_bin, 131072);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ZDEC Test fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}


	nand_debug(0, 1, "35827.bin case1\n");
	u32_Err = NCTEST_ZDEC(u32_TestRow, __35827_zlib_prop_1_bin, __35827_zlib_prop_1_bin_len, squashfs_test_2_35827_19864_70326_bin, 70326);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ZDEC Test fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	u32_Err = NCTEST_ZDEC2(u32_TestRow, __35827_zlib_prop_1_bin, __35827_zlib_prop_1_bin_len, squashfs_test_2_35827_19864_70326_bin, 70326);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ZDEC Test fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}

	nand_debug(0, 1, "35827.bin case2\n");
	u32_Err = NCTEST_ZDEC(u32_TestRow, __35827_zlib_prop_2_bin, __35827_zlib_prop_2_bin_len, squashfs_test_2_35827_19864_70326_bin, 70326);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ZDEC Test fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	u32_Err = NCTEST_ZDEC2(u32_TestRow, __35827_zlib_prop_2_bin, __35827_zlib_prop_2_bin_len, squashfs_test_2_35827_19864_70326_bin, 70326);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ZDEC Test fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}


	nand_debug(0, 1, "72094.bin case1\n");
	u32_Err = NCTEST_ZDEC(u32_TestRow, __72094_zlib_prop_1_bin, __72094_zlib_prop_1_bin_len, squashfs_test_3_72094_29571_110762_bin, 110762);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ZDEC Test fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	u32_Err = NCTEST_ZDEC2(u32_TestRow, __72094_zlib_prop_1_bin, __72094_zlib_prop_1_bin_len, squashfs_test_3_72094_29571_110762_bin, 110762);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ZDEC Test fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}

	nand_debug(0, 1, "72094.bin case2\n");
	u32_Err = NCTEST_ZDEC(u32_TestRow, __72094_zlib_prop_2_bin, __72094_zlib_prop_2_bin_len, squashfs_test_3_72094_29571_110762_bin, 110762);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ZDEC Test fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	u32_Err = NCTEST_ZDEC2(u32_TestRow, __72094_zlib_prop_2_bin, __72094_zlib_prop_2_bin_len, squashfs_test_3_72094_29571_110762_bin, 110762);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ZDEC Test fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}


	nand_debug(0, 1, "107474.bin case1\n");
	u32_Err = NCTEST_ZDEC(u32_TestRow, __107474_zlib_prop_1_bin, __107474_zlib_prop_1_bin_len, squashfs_test_4_107474_13776_72656_bin, 72656);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ZDEC Test fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	u32_Err = NCTEST_ZDEC2(u32_TestRow, __107474_zlib_prop_1_bin, __107474_zlib_prop_1_bin_len, squashfs_test_4_107474_13776_72656_bin, 72656);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ZDEC Test fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	
	nand_debug(0, 1, "107474.bin case2\n");
	u32_Err = NCTEST_ZDEC(u32_TestRow, __107474_zlib_prop_2_bin, __107474_zlib_prop_2_bin_len, squashfs_test_4_107474_13776_72656_bin, 72656);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ZDEC Test fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	u32_Err = NCTEST_ZDEC2(u32_TestRow, __107474_zlib_prop_2_bin, __107474_zlib_prop_2_bin_len, squashfs_test_4_107474_13776_72656_bin, 72656);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ZDEC Test fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	
	nand_debug(0, 1, "121250.bin case1\n");
	u32_Err = NCTEST_ZDEC(u32_TestRow, __121250_zlib_prop_1_bin, __121250_zlib_prop_1_bin_len, squashfs_test_5_121250_28458_106205_bin, 106205);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ZDEC Test fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	u32_Err = NCTEST_ZDEC2(u32_TestRow, __121250_zlib_prop_1_bin, __121250_zlib_prop_1_bin_len, squashfs_test_5_121250_28458_106205_bin, 106205);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ZDEC Test fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}

	nand_debug(0, 1, "121250.bin case2\n");
	u32_Err = NCTEST_ZDEC(u32_TestRow, __121250_zlib_prop_2_bin, __121250_zlib_prop_2_bin_len, squashfs_test_5_121250_28458_106205_bin, 106205);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ZDEC Test fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	u32_Err = NCTEST_ZDEC2(u32_TestRow, __121250_zlib_prop_2_bin, __121250_zlib_prop_2_bin_len, squashfs_test_5_121250_28458_106205_bin, 106205);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: ZDEC Test fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	
	
	#endif

	#if (0 || FCIE_IP_TEST_SUITE_ENABLE) //SLC NAND only
	nand_debug(0, 1, "CheckFirstEccErrorPage Test...\n");
	//NC_FCIE4SetInterface(0,0,0,0);
	u32_Err = NCTEST_CheckFirstEccErrorPage(u32_TestRow >> pNandDrv->u8_BlkPageCntBits);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: CheckFirstEccErrorPage fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(0, 1, "CheckFirstEccErrorPage Test ok!...\n");
	#endif

	#if (0 || FCIE_IP_TEST_SUITE_ENABLE)
	{
		U32 u32_j;
		nand_debug(UNFD_DEBUG_LEVEL, 1, "BIST Test...\n");
		for(u32_j=0 ; u32_j<12 ; u32_j++)
		{
			#if 0 // turn on to final count down
			int i;
			nand_debug(UNFD_DEBUG_LEVEL, 0, "Final count down to measure waveform : ");
			for(i=3;i>0;i--)
			{
				nand_debug(UNFD_DEBUG_LEVEL, 0, "%d  ", i);

				nand_hw_timer_delay(HW_TIMER_DELAY_1s);
			}
			nand_debug(UNFD_DEBUG_LEVEL, 0, "\n");
			#endif
			
			u32_Err = NCTEST_Bist(u32_TestRow, u32_j);
			if (u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_Bist %ld fail, ErrCode: 0x%08lx\n", u32_j, u32_Err);
				goto LABEL_END_OF_TESTS;
			}

			u32_Err = NCTEST_BistCmdQue(u32_TestRow, u32_j);
			if (u32_Err != UNFD_ST_SUCCESS)
			{
				nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_BistCmdQue %ld fail, ErrCode: 0x%08lx\n", u32_j, u32_Err);
				goto LABEL_END_OF_TESTS;
			}
		
			nand_debug(UNFD_DEBUG_LEVEL_HIGH, 1, "NCTEST_Bist Pattern %ld ok!\n", u32_j);
		}
		nand_debug(UNFD_DEBUG_LEVEL_HIGH, 1, "NCTEST_Bist ok!\n\n");
	}
	#endif
	
	#if (0 || FCIE_IP_TEST_SUITE_ENABLE)	
	nand_debug(0, 1, "NAND Boot Test...\n");
	u32_Err = NCTEST_NandBoot(u32_TestRow);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NAND Boot, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(0, 1, "NAND Boot ok!\n\n");
	#endif

	#if (0 || FCIE_IP_TEST_SUITE_ENABLE)
	nand_debug(2, 1, "Read_Latch_Timing  Test...\n");
	u32_Err = NCTEST_ReadLatchTiming();
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "ERROR: Read_Latch_Timing  fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(2, 1, "Read_Latch_Timing  ok!\n");
	#endif	

	#if (0 || FCIE_IP_TEST_SUITE_ENABLE)
	nand_debug(2, 1, "ECC_BCH_PageMode  Test...\n");
	pNandDrv->u8_IfECCTesting = 1;
	u32_Err = NCTEST_ECC_BCH_PageMode(u32_TestRow);
	pNandDrv->u8_IfECCTesting = 0;
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "ERROR: ECC_BCH_PageMode  fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(2, 1, "ECC_BCH_PageMode  ok!\n");
	#endif

	#if (0 || FCIE_IP_TEST_SUITE_ENABLE)
	nand_debug(2, 1, "ALL_ECC_BCH  MLC Test...\n");
	pNandDrv->u8_IfECCTesting = 1;
	u32_Err = NCTEST_ALL_ECC_BCH_MLC(u32_TestRow);
	pNandDrv->u8_IfECCTesting = 0;
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "ERROR: ALL_ECC_BCH MLC fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(2, 1, "ALL_ECC_BCH MLC ok!\n");
	#endif		

	#if (0 || FCIE_IP_TEST_SUITE_ENABLE)		//SLC NAND Only
	nand_debug(2, 1, "ZERO_ONE_CASE Test...\n");
	u32_Err = NCTEST_ZERO_ONE_CASE();
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "ERROR: ZERO_ONE_CASE fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(2, 1, "ZERO_ONE_CASE  ok!\n");
	#endif	

	#if (0 || FCIE_IP_TEST_SUITE_ENABLE)
	nand_debug(2, 1, "Zero_Bit_Count Test...\n");
	u32_Err = NCTEST_Zero_Bit_Count();
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "ERROR: Zero_Bit_Count fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(2, 1, "Zero_Bit_Count  ok!\n");
	#endif	

	#if (0 || FCIE_IP_TEST_SUITE_ENABLE)
	nand_debug(2, 1, "MIU Burst Test...\n");
	u32_Err = NCTEST_MIU_BURST();
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(0, 1, "ERROR: MIU Burst fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(2, 1, "MIU Burst  ok!\n");
	#endif	


	#endif


#if 0 || FCIE_IP_TEST_SUITE_ENABLE
	u32_Err = NC_EraseBlk(u32_TestRow);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
	    nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NC_EraseBlk fail, ErrCode: 0x%08lx\n", u32_Err);
	    goto LABEL_END_OF_TESTS;
	}
	nand_debug(0, 1, "Erase Blk ok!\n\n");
#endif

	//--------------------------------------
	#if FCIE_IP_TEST_SUITE_BURNIN
    goto LABEL_IP_TEST_SUITE_BURNIN;
    #endif
	//--------------------------------------
	
    #if (0 || FCIE_IP_TEST_SUITE_ENABLE) && (defined(FCIE_POWER_SAVE_MODE) && FCIE_POWER_SAVE_MODE)
	u32_Err = NCTEST_PowerSave();
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_PowerSave fail, ErrCode: 0x%08lx\n", u32_Err);
		goto LABEL_END_OF_TESTS;
	}
	nand_debug(UNFD_DEBUG_LEVEL_HIGH, 1, "PowerSave Mode ok!\n\n");
	#else
	u32_Err = (U32)NCTEST_PowerSave; // to avoid compiler warning	
    #endif


    #if 0
    //NCTEST_InitDisp(); // [CAUTION]: Disp can not pattern generate, need Bradd or Jeff.Tsai help

    //NCTEST_TestReadWriteSpeed();
    //NCTEST_EraseAllGoodBlks();
    /*while(1)
    {
		u32_Err++;
		nand_clock_setting((u32_Err & 7) ? (u32_Err & 7):1);

		if(UNFD_ST_SUCCESS != NC_Write_RandomOut(pNandDrv->u16_BlkPageCnt<<1, 0, &u32_Err, 1))
		{
			nand_debug(0,1,"clk: %X\n", u32_Err & 7);
			while(1);
		}
    }*/
	NCTEST_ECC_RS_BurnIn();
	//NCTEST_RW_BurnIn();
    #endif

	//--------------------------------------
    #if 0// defined(__VER_UNFD_FTL__) && __VER_UNFD_FTL__ // for FTL verification
    {
		int int_Ret;
		int_Ret = drv_unfd_init();
		nand_debug(0,1,"drv_unfd_init: %X\n", int_Ret);
		if(0==int_Ret)
			while(1);

	     //nand_LUT_Test();

		//NCTEST_LogiWR_Once(0, 1);
		//NCTEST_LogiWR_Once(0x4500-3, 5);
		//NCTEST_LogiWR_Once(0x4503, 5);
		//nand_dump_FMap();

		//NCTEST_LogiWR_Stress(LOGI_STRESS_TEST_SECTOR_CNT);

		//NCTEST_LogiWR_TestWBQ();

    }
    #endif
    nand_debug(0, 1, "FCIE IP Verified OK!\n");
    while(1);

LABEL_END_OF_TESTS:
	nand_debug(UNFD_DEBUG_LEVEL, 1, "end of fail \n\n");
	nand_die();

	return UNFD_ST_SUCCESS;
}


#if defined(__VER_UNFD_FTL__) && __VER_UNFD_FTL__
void NCTEST_LogiWR_Stress(U32 u32_TotalSectorCnt)
{
	U32 u32_SecPos, u32_SecCnt, u32_i;
	volatile U8  *au8_W, *au8_R;
	volatile U8  *au8_WSpare, *au8_RSpare;

	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	if(u32_TotalSectorCnt > LOGI_STRESS_TEST_SECTOR_CNT)
	{
		nand_debug(0,1,"error invalid total sector cnt: %lX \n", u32_TotalSectorCnt);
		return;
	}
	if(u32_TotalSectorCnt > LOGI_STRESS_TEST_SECTOR_ADR)
	{
		nand_debug(0,1,"error invalid total sector cnt: %lX \n", u32_TotalSectorCnt);
		return;
	}

	// start test
	for (u32_SecPos=0; u32_SecPos<LOGI_STRESS_TEST_SECTOR_ADR; u32_SecPos++)
	{
		//nand_LUT_Test();
		nand_debug(0, 1, "\n StartSec: %08lX \n", u32_SecPos);

		for (u32_SecCnt=0; u32_SecCnt<=u32_TotalSectorCnt; u32_SecCnt++)
		{
			for (u32_i=0; u32_i < u32_SecCnt<<9; u32_i++)
			{
				au8_TestBuf[u32_i] = (U8)(u32_i + u32_SecCnt);
			}
			nand_WriteFlow(u32_SecPos, u32_SecCnt, (U32)au8_TestBuf);

			for (u32_i=0; u32_i<(u32_SecCnt<<9); u32_i++)
			{
				au8_TestBuf[u32_i] = ~au8_TestBuf[u32_i];
			}
			//nand_debug(0,0,"\n");
			nand_ReadFlow(u32_SecPos, u32_SecCnt, (U32)au8_TestBuf);
			for (u32_i=0; u32_i<(u32_SecCnt<<9); u32_i++)
			{
				if (au8_TestBuf[u32_i] != (U8)(u32_i + u32_SecCnt))
				{
					nand_debug(0, 1, "error.1.: u32_SecPos:%lX  u32_SecCnt:%lX  u32_i:%lX  W:%X  R:%X\n",
						u32_SecPos, u32_SecCnt, u32_i, (U8)(u32_i + u32_SecCnt), au8_TestBuf[u32_i]);
					while(1);
				}
			}

			//nand_debug(0,0,"\n\n");

			for (u32_i=0; u32_i < u32_SecCnt<<9; u32_i++)
			{
				au8_TestBuf[u32_i] = (U8)(u32_i + u32_SecCnt + 1);
			}
			nand_WriteFlow(LOGI_STRESS_TEST_SECTOR_ADR-u32_SecPos-1, u32_SecCnt, (U32)au8_TestBuf);

			for (u32_i=0; u32_i < u32_SecCnt<<9; u32_i++)
			{
				au8_TestBuf[u32_i] = ~au8_TestBuf[u32_i];
			}
			//nand_debug(0,0,"\n");
			nand_ReadFlow(LOGI_STRESS_TEST_SECTOR_ADR-u32_SecPos-1, u32_SecCnt, (U32)au8_TestBuf);
			for (u32_i=0; u32_i < u32_SecCnt<<9; u32_i++)
			{
				if (au8_TestBuf[u32_i] != (U8)(u32_i + u32_SecCnt + 1))
				{
					nand_debug(0, 1, "error.1.: u32_SecPos:%lX  u32_SecCnt:%lX  u32_i:%lX  W:%X  R:%X\n",
						u32_SecPos, u32_SecCnt, u32_i, (U8)(u32_i + u32_SecCnt + 1), au8_TestBuf[u32_i]);
					while(1);
				}
			}
		}
	}

}

void NCTEST_LogiWR_TestFBQ(void)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_i, u32_Ret;
	U8  *au8_W, *au8_R;
	U8  *au8_WSpare, *au8_RSpare;

	/* setup buffers */
	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	for(u32_i=0; u32_i<(512*0x200); u32_i++) // use 512 sectors
	{
		au8_W[u32_i] = u32_i;
		au8_R[u32_i] = ~au8_W[u32_i];
	}

	//------------------------------------------
	// test case.0
	u32_Ret = nand_WriteFlow(pNandDrv->u16_BlkSectorCnt*0, pNandDrv->u16_PageSectorCnt, (U32)au8_W + (0<<9));
	if(UNFD_ST_SUCCESS != u32_Ret)
		nand_debug(0,1,"Err.0.0: %X \n", u32_Ret);

	u32_Ret = nand_WriteFlow(pNandDrv->u16_BlkSectorCnt*1, pNandDrv->u16_PageSectorCnt, (U32)au8_W + (1<<9));
	if(UNFD_ST_SUCCESS != u32_Ret)
		nand_debug(0,1,"Err.0.1: %X \n", u32_Ret);

	u32_Ret = nand_WriteFlow(pNandDrv->u16_BlkSectorCnt*2, pNandDrv->u16_PageSectorCnt, (U32)au8_W + (2<<9));
	if(UNFD_ST_SUCCESS != u32_Ret)
		nand_debug(0,1,"Err.0.2: %X \n", u32_Ret);

	u32_Ret = nand_WriteFlow(pNandDrv->u16_BlkSectorCnt*3, pNandDrv->u16_PageSectorCnt, (U32)au8_W + (3<<9));
	if(UNFD_ST_SUCCESS != u32_Ret)
		nand_debug(0,1,"Err.0.3: %X \n", u32_Ret);

}

void NCTEST_LogiWR_TestWBQ(void)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_i, u32_Ret;
	U8  *au8_W, *au8_R;
	U8  *au8_WSpare, *au8_RSpare;

	/* setup buffers */
	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	for(u32_i=0; u32_i<(512*0x200); u32_i++) // use 512 sectors
	{
		au8_W[u32_i] = u32_i;
		au8_R[u32_i] = ~au8_W[u32_i];
	}

	//------------------------------------------
	// test case.0
	for(u32_i=0; u32_i<10; u32_i++)
	{
		u32_Ret = nand_WriteFlow(u32_i, 1, (U32)au8_W + (u32_i<<9));
		if(UNFD_ST_SUCCESS != u32_Ret)
			nand_debug(0,1,"Err.0.0: %X \n", u32_Ret);
	}
	for(u32_i=0; u32_i<10; u32_i++)
	{
		u32_Ret = nand_ReadFlow(u32_i, 1, (U32)au8_R + (u32_i<<9));
		if(UNFD_ST_SUCCESS != u32_Ret)
			nand_debug(0,1,"Err.0.1: %X \n", u32_Ret);
	}
	NCTEST_DataCompare(au8_W, au8_R, 512*10);
	nand_debug(0,1," case.0 ok\n");

	//------------------------------------------
	// test case.1
	u32_Ret = nand_WriteFlow(3, 5, (U32)au8_W + (3<<9));
	if(UNFD_ST_SUCCESS != u32_Ret)
		nand_debug(0,1,"Err.1.0: %X \n", u32_Ret);

	u32_Ret = nand_ReadFlow(0, 10, (U32)au8_R);
	if(UNFD_ST_SUCCESS != u32_Ret)
		nand_debug(0,1,"Err.1.1: %X \n", u32_Ret);

	NCTEST_DataCompare(au8_W, au8_R, 512*10);
	nand_debug(0,1," case.1 ok\n");

	//------------------------------------------
	// test case.2
	u32_Ret = nand_WriteFlow(pNandDrv->u16_BlkSectorCnt+1, 3, (U32)au8_W+((pNandDrv->u16_BlkSectorCnt+1)<<9));
	if(UNFD_ST_SUCCESS != u32_Ret)
		nand_debug(0,1,"Err.2.0: %X \n", u32_Ret);
	u32_Ret = nand_WriteFlow(pNandDrv->u16_BlkSectorCnt*2+1, 3, (U32)au8_W+((pNandDrv->u16_BlkSectorCnt*2+1)<<9));
	if(UNFD_ST_SUCCESS != u32_Ret)
		nand_debug(0,1,"Err.2.1: %X \n", u32_Ret);
    u32_Ret = nand_WriteFlow(pNandDrv->u16_BlkSectorCnt*3+1, 3, (U32)au8_W+((pNandDrv->u16_BlkSectorCnt*3+1)<<9));
	if(UNFD_ST_SUCCESS != u32_Ret)
		nand_debug(0,1,"Err.2.2: %X \n", u32_Ret);

	u32_Ret = nand_ReadFlow(pNandDrv->u16_BlkSectorCnt+1, 3, (U32)au8_R+((pNandDrv->u16_BlkSectorCnt+1)<<9));
	if(UNFD_ST_SUCCESS != u32_Ret)
		nand_debug(0,1,"Err.2.3: %X \n", u32_Ret);
	u32_Ret = nand_ReadFlow(pNandDrv->u16_BlkSectorCnt*2+1, 3, (U32)au8_R+((pNandDrv->u16_BlkSectorCnt*2+1)<<9));
	if(UNFD_ST_SUCCESS != u32_Ret)
		nand_debug(0,1,"Err.2.4: %X \n", u32_Ret);
	u32_Ret = nand_ReadFlow(pNandDrv->u16_BlkSectorCnt*3+1, 3, (U32)au8_R+((pNandDrv->u16_BlkSectorCnt*3+1)<<9));
	if(UNFD_ST_SUCCESS != u32_Ret)
		nand_debug(0,1,"Err.2.5: %X \n", u32_Ret);

	NCTEST_DataCompare((U8*)((U32)au8_W+((pNandDrv->u16_BlkSectorCnt+1)<<9)), (U8*)((U32)au8_R+((pNandDrv->u16_BlkSectorCnt+1)<<9)), 512*3);
	NCTEST_DataCompare((U8*)((U32)au8_W+((pNandDrv->u16_BlkSectorCnt*2+1)<<9)), (U8*)((U32)au8_R+((pNandDrv->u16_BlkSectorCnt*2+1)<<9)), 512*3);
	NCTEST_DataCompare((U8*)((U32)au8_W+((pNandDrv->u16_BlkSectorCnt*3+1)<<9)), (U8*)((U32)au8_R+((pNandDrv->u16_BlkSectorCnt*3+1)<<9)), 512*3);
	nand_debug(0,1," case.2 ok\n");



}


void NCTEST_LogiWR_Once(U32 u32_StartSectorIdx, U32 u32_SectorCnt)
{
	U32 u32_i, u32_Ret;
	U8  *au8_W, *au8_R;
	U8  *au8_WSpare, *au8_RSpare;

	/* setup buffers */
	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	for(u32_i=0; u32_i<0x200; u32_i++)
	{
		au8_W[u32_i] = u32_i;
		au8_R[u32_i] = ~au8_W[u32_i];
	}

	u32_Ret = nand_WriteFlow(u32_StartSectorIdx, u32_SectorCnt, (U32)au8_W);
	if(UNFD_ST_SUCCESS != u32_Ret)
		nand_debug(0,1,"WriteFlow: %X \n", u32_Ret);

	u32_Ret = nand_ReadFlow(u32_StartSectorIdx, u32_SectorCnt, (U32)au8_R);
	if(UNFD_ST_SUCCESS != u32_Ret)
		nand_debug(0,1,"ReadFlow: %X \n", u32_Ret);

	for(u32_i=0; u32_i<0x200; u32_i++)
	{
		if(au8_W[u32_i] != au8_R[u32_i])
			nand_debug(0,1,"Pos:%X  W:%X  R:%X\n", u32_i, au8_W[u32_i], au8_R[u32_i]);
	}

}
#endif


U32 NCTEST_TestReadWriteSpeed(void)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_i, u32_Err;

	U8  *au8_W, *au8_R;
	U8  *au8_WSpare, *au8_RSpare;

	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	nand_debug(0, 1, "w start\n");

	for(u32_i=0; u32_i<(pNandDrv->u16_BlkCnt<<pNandDrv->u8_BlkPageCntBits); u32_i++)
	{
		#if 1
		u32_Err = NC_WritePages(u32_i, au8_W, au8_WSpare, 1);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NC_Test, ErrCode: 0x%08lx\n", u32_Err);
			return u32_Err;
		}
		#else
		u32_Err = NC_ReadPages(u32_i, au8_R, au8_RSpare, 1);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NC_Test, ErrCode: 0x%08x\n", u32_Err);
			return u32_Err;
		}
		#endif
	}

	nand_debug(0, 1, "end\n");

    return 0;
}



//==============================================
// for special WinTarget
//==============================================
void NCTEST_EarseAllBlk(void)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	//U32 u32_Ret;
	U16 u16_i, u16_Cnt;
    #if 0
	u32_Ret = drvNAND_Init();
	if(UNFD_ST_SUCCESS != u32_Ret)
	{
		nand_debug(0,1,"ERROR, NAND, no CIS\n");
		while(1);
	}
	#endif

	u16_Cnt=0;
	for(u16_i=10; u16_i<pNandDrv->u16_BlkCnt; u16_i++)
	{
		if(UNFD_ST_SUCCESS != NC_EraseBlk(u16_i << pNandDrv->u8_BlkPageCntBits))
		{
			nand_debug(0,1,"bad blk: %X \n", u16_i);
			u16_Cnt++;
		}
	}
	nand_debug(0,1,"total bad blk: %X \n", u16_Cnt);
}


void NCTEST_EWRCAllBlk(void)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Err;
	U16 u16_i, u16_j, u16_k, u16_Loop;
	U8	*au8_W, *au8_R;
	U8	*au8_WSpare, *au8_RSpare;

	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;


	for(u16_i = 0; u16_i < pNandDrv->u16_PageByteCnt; u16_i++)
	{
		au8_W[u16_i] = u16_i + 1;
		au8_R[u16_i] = ~au8_W[u16_i];
    }
	for(u16_i = 0; u16_i < pNandDrv->u16_SpareByteCnt; u16_i++)
	{
		au8_WSpare[u16_i] = u16_i + 1 ;
		au8_RSpare[u16_i] = ~au8_WSpare[u16_i];
	}

	nand_config_clock(50); // tR 30 ns

	u16_Loop=0;
	while(u16_Loop < 1)
	{
		u16_Loop++;

	    for(u16_i=0; u16_i<pNandDrv->u16_BlkCnt; u16_i++)
	    {
			nand_debug(0,0,"blk: %04X", u16_i);

			au8_RSpare[0]=0xFF;
			u32_Err = NC_ReadPages(u16_i << pNandDrv->u8_BlkPageCntBits, au8_R, au8_RSpare, 1);
			if(UNFD_ST_SUCCESS!=u32_Err || 0!=au8_RSpare[0])
			{
				if(UNFD_ST_SUCCESS != NC_EraseBlk(u16_i << pNandDrv->u8_BlkPageCntBits))
		        {
			        nand_debug(0,1,"+ bad blk: %04X \n", u16_i);
					drvNAND_MarkBadBlk(u16_i);
				    continue;
		        }
			}
			else
			{   nand_debug(0,0,"          init bad blk \n");
				continue;
			}

			for(u16_j=0; u16_j<pNandDrv->u16_BlkPageCnt; u16_j++)
			{
				u32_Err = NC_WritePages((u16_i<<pNandDrv->u8_BlkPageCntBits)+u16_j,
					au8_W, au8_WSpare, 1);
		        if(u32_Err != UNFD_ST_SUCCESS)
		        {
			        nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: w fail, ErrCode: 0x%08lx\n", u32_Err);
					drvNAND_MarkBadBlk(u16_i);
			        goto LABEL_END_OF_A_BLK;
		        }

		        u32_Err = NC_ReadPages((u16_i<<pNandDrv->u8_BlkPageCntBits)+u16_j,
					au8_R, au8_RSpare, 1);
		        if (u32_Err != UNFD_ST_SUCCESS)
		        {
			        nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: r fail, ErrCode: 0x%08lx\n", u32_Err);
					drvNAND_MarkBadBlk(u16_i);
			        goto LABEL_END_OF_A_BLK;
		        }

				for (u16_k = 0; u16_k < pNandDrv->u16_PageByteCnt; u16_k++)
		        {
			        if(au8_W[u16_k] != au8_R[u16_k])
			        {
				        nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: c fail, data, Row: 0x%08X, Col: 0x%04X, W: 0x%02X, R: 0x%02X\n",
						    (u16_i<<pNandDrv->u8_BlkPageCntBits)+u16_j, u16_k, au8_W[u16_k], au8_R[u16_k]);
						drvNAND_MarkBadBlk(u16_i);
				        goto LABEL_END_OF_A_BLK;
			        }
		        }
		        for(u16_k = 0; u16_k < pNandDrv->u16_SpareByteCnt; u16_k++)
		        {
			        if(u16_k == pNandDrv->u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt +
					    pNandDrv->u16_SectorSpareByteCnt * (u16_k / pNandDrv->u16_SectorSpareByteCnt))
			        {
				        u16_k += pNandDrv->u16_ECCCodeByteCnt - 1;
				        break;
			        }

			        if (au8_WSpare[u16_k] != au8_RSpare[u16_k])
			        {
				        nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: c fail,, spare, Row: 0x%08x, Col: 0x%04x, W: 0x%02x, R: 0x%02x\n",
						    (u16_i<<pNandDrv->u8_BlkPageCntBits)+u16_j, u16_k, au8_WSpare[u16_k], au8_RSpare[u16_k]);
						drvNAND_MarkBadBlk(u16_i);
				        goto LABEL_END_OF_A_BLK;
			        }
		        }
			}

			if(UNFD_ST_SUCCESS != NC_EraseBlk(u16_i << pNandDrv->u8_BlkPageCntBits))
		    {
				drvNAND_MarkBadBlk(u16_i);
			    nand_debug(0,1,"- bad blk: %04X \n", u16_i);
				continue;
		    }
			nand_debug(0,0,"          ok\n");

			LABEL_END_OF_A_BLK:;
	    }

	}

}


U32 NCTEST_EraseAllGoodBlks(void)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Blk, u32_Row, u32_Err, u32_BadBlkCnt;

	U8  *au8_W, *au8_R;
	U8  *au8_WSpare, *au8_RSpare;

	#if 0
	//u32_Err = drvNAND_SearchCIS();
	u32_Err = drvNAND_Init();
	if(UNFD_ST_SUCCESS != u32_Err)
	{
		nand_debug(0,1,"ERROR, NAND, no CIS\n");
		while(1);
	}
	#endif
	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	u32_BadBlkCnt = 0;

	nand_debug(0, 1, "EraseAllGoodBlks start\n");

	for(u32_Blk=0; u32_Blk<pNandDrv->u16_BlkCnt; u32_Blk++)
	{
		u32_Row = u32_Blk << pNandDrv->u8_BlkPageCntBits;

		u32_Err = NC_ReadPages(u32_Row, au8_R, au8_RSpare, 1);
		#if 0
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(0, 1, "err.0: read fail: code:%X, blk:%X\n", u32_Err, u32_Blk);
            goto LABEL_ERR_HANDLE;
		}
		#endif

		//if(0xFF != au8_RSpare[0])
		if(0 == au8_RSpare[0])
		{
			nand_debug(0, 1, "err.1: bad blk: %lX\n", u32_Blk);
			goto LABEL_ERR_HANDLE;
		}

		u32_Err = NC_EraseBlk(u32_Row);
		if (u32_Err != UNFD_ST_SUCCESS)
		{
			nand_debug(0, 1, "err.2: erase fail: code:%lX, blk:%lX\n", u32_Err, u32_Blk);
			goto LABEL_ERR_HANDLE;
		}

		continue;

		LABEL_ERR_HANDLE:
		//drvNAND_MarkBadBlk(u32_Blk); // <- erase inside, not good for bad blk
		u32_BadBlkCnt++;
	}

	nand_debug(0,1,"total bad blk: %lX \n", u32_BadBlkCnt);

    return 0;
}


U32 NCTEST_HWRepeatModeTest(void)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	U32 u32_Blk, u32_Row, u32_Err, /*u32_ByteIdx,*/ u32_i;

	U8  *au8_W, *au8_R;
	U8  *au8_WSpare, *au8_RSpare;

	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	nand_debug(0, 1, "HWRepeatModeTest\n");
	NC_SendCmdForLADebug();

	u32_Blk=1;
	u32_Row = pNandDrv->u16_BlkPageCnt;
	while(1)
	{
		u32_Blk++;
		if(u32_Blk == pNandDrv->u16_BlkCnt)
			u32_Blk = 1;

		if(u32_Row == pNandDrv->u16_BlkPageCnt)
			u32_Row = 1;
		else
			u32_Row = pNandDrv->u16_BlkPageCnt;

		if(0 == drvNAND_IsGoodBlk(u32_Blk)) // skip bad blk
		{
			nand_debug(0,1,"skip bad blk: %04lX\n", u32_Blk);
			continue;
		}

		nand_debug(0, 1, "testing blk: %04lX, PageCnt: %02lX\n", u32_Blk, u32_Row);

		u32_Err = NCTEST_RWMultiplePages_OneTime(
			u32_Blk << pNandDrv->u8_BlkPageCntBits,
			u32_Row);
	    if(u32_Err != UNFD_ST_SUCCESS)
	    {
			nand_debug(0,1,"\n\n");
			nand_debug(0,1,"dump w data:\n");
			for(u32_i=0; u32_i<u32_Row; u32_i++)
			{
				nand_debug(0,1,"page: %02lX\n", u32_i);
				dump_mem(
					au8_W + (u32_i<<pNandDrv->u8_PageByteCntBits),
					pNandDrv->u16_PageByteCnt);
				nand_debug(0,1,"\n");
			}

			nand_debug(0,1,"\n\n");
			nand_debug(0,1,"dump r data:\n");
			for(u32_i=0; u32_i<u32_Row; u32_i++)
			{
				nand_debug(0,1,"page: %02lX\n", u32_i);
				dump_mem(
					au8_R + (u32_i<<pNandDrv->u8_PageByteCntBits),
					pNandDrv->u16_PageByteCnt);
				nand_debug(0,1,"\n");
			}

	        return u32_Err;
	    }

		u32_Err = NC_EraseBlk(u32_Blk);
		if(UNFD_ST_SUCCESS != u32_Err)
			drvNAND_MarkBadBlk(u32_Blk);
	}

	return UNFD_ST_SUCCESS;
}



U32 NCTEST_HWECCCheckNotAllFF(U32 u32_TestRow)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	//U32 u32_Blk, u32_Row;
    U32 u32_Err, u32_ByteIdx;
    //U32 u32_i;

	U8  *au8_W, *au8_R;
	U8  *au8_WSpare, *au8_RSpare;

	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	nand_debug(0, 1, "NCTEST_HWECCTest\n");

	u32_Err = NC_EraseBlk(u32_TestRow);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_HWECCTest 1, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	/* init test pattern */
	for(u32_ByteIdx = 0; u32_ByteIdx < pNandDrv->u16_PageByteCnt; u32_ByteIdx++)
	{
		au8_W[u32_ByteIdx] = ECC_TEST_PATTERN;
		au8_R[u32_ByteIdx] = ~au8_W[u32_ByteIdx];
    }

	for(u32_ByteIdx = 0; u32_ByteIdx < pNandDrv->u16_SpareByteCnt; u32_ByteIdx++)
	{
		au8_WSpare[u32_ByteIdx] = ECC_TEST_PATTERN;
		au8_RSpare[u32_ByteIdx] = ~au8_WSpare[u32_ByteIdx];
	}

    // =================================================
	pNandDrv->u16_Reg50_EccCtrl |= BIT_NC_BYPASS_ECC;
	NC_Config();

	au8_W[1] = 0x7F;
	u32_Err = NC_WritePages(u32_TestRow, au8_W, au8_WSpare, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_HWECCTest 2, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	nand_debug(0,1,"expect to get ECC fail \n");
	pNandDrv->u16_Reg50_EccCtrl &= ~BIT_NC_BYPASS_ECC;
	NC_Config();
	u32_Err = NC_ReadPages(u32_TestRow, au8_R, au8_RSpare, 1);
	if (u32_Err != UNFD_ST_ERR_ECC_FAIL)
	{
		NCTEST_DumpECCRegisters();
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_HWECCTest 3, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	au8_W[1] = 0xFF;

	// =================================================
	pNandDrv->u16_Reg50_EccCtrl |= BIT_NC_BYPASS_ECC;
	NC_Config();

	//au8_W[0x2] = 0x7F;
	au8_W[0x11] = 0x7F;
	u32_Err = NC_WritePages(u32_TestRow+1, au8_W, au8_WSpare, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_HWECCTest 4, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	nand_debug(0,1,"expect to get ECC fail \n");
	pNandDrv->u16_Reg50_EccCtrl &= ~BIT_NC_BYPASS_ECC;
	NC_Config();
	u32_Err = NC_ReadPages(u32_TestRow+1, au8_R, au8_RSpare, 1);
	if (u32_Err != UNFD_ST_ERR_ECC_FAIL)
	{
		NCTEST_DumpECCRegisters();
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_HWECCTest 5, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	au8_W[0x11] = 0xFF;

	// =================================================
	pNandDrv->u16_Reg50_EccCtrl |= BIT_NC_BYPASS_ECC;
	NC_Config();

	au8_W[0x23] = 0x7F;
	u32_Err = NC_WritePages(u32_TestRow+2, au8_W, au8_WSpare, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_HWECCTest 6, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	nand_debug(0,1,"expect to get ECC fail \n");
	pNandDrv->u16_Reg50_EccCtrl &= ~BIT_NC_BYPASS_ECC;
	NC_Config();
	u32_Err = NC_ReadPages(u32_TestRow+2, au8_R, au8_RSpare, 1);
	if (u32_Err != UNFD_ST_ERR_ECC_FAIL)
	{
		NCTEST_DumpECCRegisters();
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_HWECCTest 7, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}
	au8_W[0x23] = 0xFF;

	u32_Err = NC_EraseBlk(u32_TestRow);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_HWECCTest 8, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	return UNFD_ST_SUCCESS;
}


U32 NCTEST_HWECCSpare640B(U32 u32_TestRow)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	//U32 u32_Blk, u32_Row;
    U32 u32_Err, u32_ByteIdx, u32_i;

	U8  *au8_W, *au8_R;
	U8  *au8_WSpare, *au8_RSpare;

	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;

	nand_debug(0, 1, "NCTEST_HWECCTest\n");

	u32_Err = NC_EraseBlk(u32_TestRow);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_HWECCTest 1, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	/* init test pattern */
	for(u32_ByteIdx = 0; u32_ByteIdx < pNandDrv->u16_PageByteCnt; u32_ByteIdx++)
	{
		au8_W[u32_ByteIdx] = ECC_TEST_PATTERN;
		au8_R[u32_ByteIdx] = ~au8_W[u32_ByteIdx];
    }

	for(u32_ByteIdx = 0; u32_ByteIdx < pNandDrv->u16_SpareByteCnt; u32_ByteIdx++)
	{
		au8_WSpare[u32_ByteIdx] = ECC_TEST_PATTERN;
		au8_RSpare[u32_ByteIdx] = ~au8_WSpare[u32_ByteIdx];
	}

	u32_Err = NC_WritePages(u32_TestRow, au8_W, au8_WSpare, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_HWECCTest 2, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	// get ECC code in au8_RSpare
	u32_Err = NC_ReadPages(u32_TestRow, au8_R, au8_RSpare, 1); // get ECC code in au8_RSpare
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_HWECCTest 3, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}
	NCTEST_DumpECCRegisters();

	u32_Err=NCTEST_DataCompare(au8_W, au8_R, pNandDrv->u16_PageByteCnt);
	if(UNFD_ST_SUCCESS != u32_Err)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "page data fail\n");
		return u32_Err;
	}
	for(u32_i=0; u32_i<pNandDrv->u16_PageSectorCnt; u32_i++)
	{
		u32_Err=NCTEST_DataCompare(
			au8_WSpare + u32_i*pNandDrv->u16_SectorSpareByteCnt,
			au8_RSpare  + u32_i*pNandDrv->u16_SectorSpareByteCnt,
			pNandDrv->u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt);
		if(UNFD_ST_SUCCESS != u32_Err)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "sector:%lX sapre fail\n", u32_i);
			return u32_Err;
		}
	}

	// correct bits in data & spare, before last 2 sector
	for(u32_i=0; u32_i<pNandDrv->u16_PageSectorCnt-2; u32_i++)
		au8_R[1 + (u32_i<<pNandDrv->u8_SectorByteCntBits)] ^= 0x80;
	for(u32_i=0; u32_i<pNandDrv->u16_PageSectorCnt-2; u32_i++)
		au8_RSpare[1 + u32_i*pNandDrv->u16_SectorSpareByteCnt] ^= 0x80;

	pNandDrv->u16_Reg50_EccCtrl |= BIT_NC_BYPASS_ECC;
	NC_Config();
	u32_Err = NC_WritePages(u32_TestRow+1, au8_R, au8_RSpare, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_HWECCTest 2, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	pNandDrv->u16_Reg50_EccCtrl &= ~BIT_NC_BYPASS_ECC;
	NC_Config();
	u32_Err = NC_ReadPages(u32_TestRow+1, au8_W, au8_WSpare, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_HWECCTest 2, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}
	NCTEST_DumpECCRegisters();

	u32_Err=NCTEST_DataCompare(au8_R, au8_W, pNandDrv->u16_PageByteCnt);
	if(UNFD_ST_SUCCESS != u32_Err)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "page data fail\n");
		//return u32_Err;
	}
	for(u32_i=0; u32_i<pNandDrv->u16_PageSectorCnt; u32_i++)
	{
		u32_Err=NCTEST_DataCompare(
			au8_RSpare + u32_i*pNandDrv->u16_SectorSpareByteCnt,
			au8_WSpare  + u32_i*pNandDrv->u16_SectorSpareByteCnt,
			pNandDrv->u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt);
		if(UNFD_ST_SUCCESS != u32_Err)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "sector:%lX sapre fail\n", u32_i);
			//return u32_Err;
		}
	}

	// correct bits in data & spare, at last sector
	au8_W[1 + ((pNandDrv->u16_PageSectorCnt-1)<<pNandDrv->u8_SectorByteCntBits)] ^= 0x80;
	au8_WSpare[512+82] = 0x11;
	#if 0
	au8_WSpare[0 + (pNandDrv->u16_PageSectorCnt-1)*pNandDrv->u16_SectorSpareByteCnt] = 0x00;
	au8_WSpare[1 + (pNandDrv->u16_PageSectorCnt-1)*pNandDrv->u16_SectorSpareByteCnt] = 0x00;
	au8_WSpare[2 + (pNandDrv->u16_PageSectorCnt-1)*pNandDrv->u16_SectorSpareByteCnt] = 0x00;
	au8_WSpare[3 + (pNandDrv->u16_PageSectorCnt-1)*pNandDrv->u16_SectorSpareByteCnt] = 0x0;
	au8_WSpare[4 + (pNandDrv->u16_PageSectorCnt-1)*pNandDrv->u16_SectorSpareByteCnt] = 0x00;
	#endif

	pNandDrv->u16_Reg50_EccCtrl |= BIT_NC_BYPASS_ECC;
	NC_Config();
	u32_Err = NC_WritePages(u32_TestRow+2, au8_W, au8_WSpare, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_HWECCTest 2, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}

	pNandDrv->u16_Reg50_EccCtrl &= ~BIT_NC_BYPASS_ECC;
	NC_Config();
	u32_Err = NC_ReadPages(u32_TestRow+2, au8_R, au8_RSpare, 1);
	if (u32_Err != UNFD_ST_SUCCESS)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "ERROR: NCTEST_HWECCTest 2, ErrCode: 0x%08lx\n", u32_Err);
		return u32_Err;
	}
	NCTEST_DumpECCRegisters();

	u32_Err=NCTEST_DataCompare(au8_W, au8_R, pNandDrv->u16_PageByteCnt);
	if(UNFD_ST_SUCCESS != u32_Err)
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "page data fail\n");
		//return u32_Err;
	}
	for(u32_i=0; u32_i<pNandDrv->u16_PageSectorCnt; u32_i++)
	{
		u32_Err=NCTEST_DataCompare(
			au8_WSpare + u32_i*pNandDrv->u16_SectorSpareByteCnt,
			au8_RSpare  + u32_i*pNandDrv->u16_SectorSpareByteCnt,
			pNandDrv->u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt);
		if(UNFD_ST_SUCCESS != u32_Err)
		{
			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "sector:%lX sapre fail\n", u32_i);
			//return u32_Err;
		}
	}

	return UNFD_ST_SUCCESS;

}


// ===========================================
#define ROM_IMAGE_COUNT    4
static U8 sgau8_Img0[]={
    //#include "NANDINFO.txt"
};
static U8 sgau8_Img1[]={
    //#include "PARTITION.txt"
};
static U8 sgau8_Img2[]={
    //#include "PAIRPAGEMAP.txt"
};
static U8 sgau8_Img3[]={
    //#include "bootloader_MSW8873x.txt"
};
static U8 *sgpau8_ImgPtr[ROM_IMAGE_COUNT]={
	sgau8_Img0, sgau8_Img1, sgau8_Img2, sgau8_Img3
};
static U8 sgau8_ImgStartNANDAddr[ROM_IMAGE_COUNT][2]={
	{0,0},{0,1},{0,3},{0xA,0} //{PBA, Row}
};

U32 NCTEST_WriteImagesForROM(void)
{
	NAND_DRIVER *pNandDrv = drvNAND_get_DrvContext_address();
	volatile U32 u32_err, u32_row, u32_i;
	U8  *au8_W, *au8_R;
	U8  *au8_WSpare, *au8_RSpare;
	BLK_INFO_t *pBlkInfo;
	U8 u8_ImgIdx;

	/* setup buffers */
	au8_W = (U8*)DMA_W_ADDR;
	au8_R = (U8*)DMA_R_ADDR;
	au8_WSpare = (U8*)DMA_W_SPARE_ADDR;
	au8_RSpare = (U8*)DMA_R_SPARE_ADDR;
	pBlkInfo = (BLK_INFO_t*)au8_WSpare;

	for(u32_i=0; u32_i<0x200; u32_i++)
		au8_WSpare[u32_i]=0;

	// ==========================================
	// write nni
	u8_ImgIdx = 0;
	pNandDrv->u16_PageByteCnt = 0x800;
	pNandDrv->u16_SpareByteCnt = 0x100;
	NC_ConfigNandFlashContext();
	NC_Init();
	pNandDrv->u16_Reg48_Spare |= BIT_NC_HW_AUTO_RANDOM_CMD_DISABLE;
	NC_Config();
	//dump_nand_driver(pNandDrv);

	u32_row =  sgau8_ImgStartNANDAddr[u8_ImgIdx][0] << pNandDrv->u8_BlkPageCntBits;
	u32_row += sgau8_ImgStartNANDAddr[u8_ImgIdx][1];
	u32_err = NC_EraseBlk(u32_row);
	if(UNFD_ST_SUCCESS != u32_err)
	{
		nand_debug(0,1,"error, e nni fail: %lX\n", u32_err);
		while(1);
	}
	pBlkInfo->u8_BadBlkMark = 0xFF;
	pBlkInfo->u8_PartType = 0; // CIS block
	u32_err = NC_WriteSectors(u32_row, 0, sgpau8_ImgPtr[u8_ImgIdx], (U8*)pBlkInfo, 1);
	if(UNFD_ST_SUCCESS != u32_err)
	{
		nand_debug(0,1,"error, w nni fail: %lX\n", u32_err);
		while(1);
	}
	u32_err = NC_ReadSectors(u32_row, 0, au8_R, (U8*)au8_RSpare, 1);
	if(UNFD_ST_SUCCESS != u32_err)
	{
		nand_debug(0,1,"error, r nni fail: %lX\n", u32_err);
		while(1);
	}
	u32_err = NCTEST_DataCompare((U8*)sgpau8_ImgPtr[u8_ImgIdx], (U8*)au8_R, pNandDrv->u16_SectorByteCnt);
	if(UNFD_ST_SUCCESS != u32_err)
	{
		nand_debug(0,1,"error, c nni data fail: %lX\n", u32_err);
		while(1);
	}
	//nand_debug(0,1,"\n\n");
	//dump_mem(au8_R, pNandDrv->u16_SectorByteCnt);
	//nand_debug(0,1,"\n\n");

	u32_err = NCTEST_DataCompare(au8_WSpare, au8_RSpare,
		pNandDrv->u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt);
	if(UNFD_ST_SUCCESS != u32_err)
	{
		nand_debug(0,1,"error, c nni spare fail: %lX\n", u32_err);
		while(1);
	}
	//dump_mem(au8_RSpare, pNandDrv->u16_SectorSpareByteCnt);
	nand_debug(0,1,"\n nni ok \n");

	// ==========================================
	// write pni
	u8_ImgIdx = 1;
	pNandDrv->u16_PageByteCnt = NAND_PAGE_BYTE_CNT;
	pNandDrv->u16_SpareByteCnt = NAND_SPARE_BYTE_CNT;
	NC_ConfigNandFlashContext();
	NC_Init();
	pNandDrv->u16_Reg48_Spare &= ~BIT_NC_HW_AUTO_RANDOM_CMD_DISABLE;
	NC_Config();

	u32_row =  sgau8_ImgStartNANDAddr[u8_ImgIdx][0] << pNandDrv->u8_BlkPageCntBits;
	u32_row += sgau8_ImgStartNANDAddr[u8_ImgIdx][1];

	u32_err = NC_WriteSectors(u32_row, 0, sgpau8_ImgPtr[u8_ImgIdx], (U8*)pBlkInfo, 1);
	if(UNFD_ST_SUCCESS != u32_err)
	{
		nand_debug(0,1,"error, w pni fail: %lX\n", u32_err);
		while(1);
	}
	u32_err = NC_ReadSectors(u32_row, 0, au8_R, (U8*)au8_RSpare, 1);
	if(UNFD_ST_SUCCESS != u32_err)
	{
		nand_debug(0,1,"error, r pni fail: %lX\n", u32_err);
		while(1);
	}
	u32_err = NCTEST_DataCompare((U8*)sgpau8_ImgPtr[u8_ImgIdx], (U8*)au8_R, pNandDrv->u16_SectorByteCnt);
	if(UNFD_ST_SUCCESS != u32_err)
	{
		nand_debug(0,1,"error, c pni data fail: %lX\n", u32_err);
		while(1);
	}
	//nand_debug(0,1,"\n\n");
	//dump_mem(au8_R, pNandDrv->u16_SectorByteCnt);
	//nand_debug(0,1,"\n\n");

	u32_err = NCTEST_DataCompare(au8_WSpare, au8_RSpare,
		pNandDrv->u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt);
	if(UNFD_ST_SUCCESS != u32_err)
	{
		nand_debug(0,1,"error, c pni spare fail: %lX\n", u32_err);
		while(1);
	}
	//dump_mem(au8_RSpare, pNandDrv->u16_SectorSpareByteCnt);
	nand_debug(0,1,"\n pni ok \n");

	// ==========================================
	// write ppm
	#if defined(NC_SEL_FCIE3) && NC_SEL_FCIE3
	if(pNandDrv->u16_SectorByteCnt > 0x200 &&
		0==(pNandDrv->u16_Reg48_Spare&BIT_NC_SPARE_DEST_MIU))
	{
		nand_debug(0,1,"CAUTION: NAND spare:%u, need spare DMA to get whole spare\n", pNandDrv->u16_Reg48_Spare);
		while(1);
	}
	#endif
	u8_ImgIdx = 2;
	u32_row =  sgau8_ImgStartNANDAddr[u8_ImgIdx][0] << pNandDrv->u8_BlkPageCntBits;
	u32_row += sgau8_ImgStartNANDAddr[u8_ImgIdx][1];
	u32_err = NC_WritePages(u32_row, sgpau8_ImgPtr[u8_ImgIdx], (U8*)pBlkInfo, 1);
	if(UNFD_ST_SUCCESS != u32_err)
	{
		nand_debug(0,1,"error, w ppm fail: %lX\n", u32_err);
		while(1);
	}
	u32_err = NC_ReadPages(u32_row, au8_R, (U8*)au8_RSpare, 1);
	if(UNFD_ST_SUCCESS != u32_err)
	{
		nand_debug(0,1,"error, r ppm fail: %lX\n", u32_err);
		while(1);
	}
	u32_err = NCTEST_DataCompare((U8*)sgpau8_ImgPtr[u8_ImgIdx], (U8*)au8_R, pNandDrv->u16_PageByteCnt);
	if(UNFD_ST_SUCCESS != u32_err)
	{
		nand_debug(0,1,"error, c ppm data fail: %lX\n", u32_err);
		while(1);
	}
	//nand_debug(0,1,"\n\n");
	//dump_mem(au8_R, pNandDrv->u16_PageByteCnt);
	//nand_debug(0,1,"\n\n");

	u32_err = NCTEST_DataCompare(au8_WSpare, au8_RSpare,
		pNandDrv->u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt);
	if(UNFD_ST_SUCCESS != u32_err)
	{
		nand_debug(0,1,"error, c ppm spare fail: %lX\n", u32_err);
		while(1);
	}
	//dump_mem(au8_RSpare, pNandDrv->u16_SpareByteCnt);
	nand_debug(0,1,"\n ppm ok \n");

	// ==========================================
	// write bdr
	#if defined(NC_SEL_FCIE3) && NC_SEL_FCIE3
	if(pNandDrv->u16_SectorByteCnt > 0x200 &&
		0==(pNandDrv->u16_Reg48_Spare&BIT_NC_SPARE_DEST_MIU))
	{
		nand_debug(0,1,"CAUTION: NAND spare:%u, need spare DMA to get whole spare\n", pNandDrv->u16_Reg48_Spare);
		while(1);
	}
	#endif
	u8_ImgIdx = 3;
	u32_row =  sgau8_ImgStartNANDAddr[u8_ImgIdx][0] << pNandDrv->u8_BlkPageCntBits;
	u32_row += sgau8_ImgStartNANDAddr[u8_ImgIdx][1];

	u32_err = NC_EraseBlk(u32_row);
	if(UNFD_ST_SUCCESS != u32_err)
	{
		nand_debug(0,1,"error, e bdr fail: %lX\n", u32_err);
		while(1);
	}

	for(u32_i=0; u32_i<4; u32_i++)
	{
		nand_debug(0,1,"w bdr @ row: %lXh \n", u32_row+u32_i);

	    u32_err = NC_WritePages(u32_row+u32_i,
		    sgpau8_ImgPtr[u8_ImgIdx]+(u32_i<<pNandDrv->u8_PageByteCntBits),
		    (U8*)pBlkInfo, 1);
    	if(UNFD_ST_SUCCESS != u32_err)
	    {
		    nand_debug(0,1,"error: %lXh, w bdr fail: %lX\n", u32_i, u32_err);
    		while(1);
	    }
    	u32_err = NC_ReadPages(u32_row+u32_i,
			au8_R+(u32_i<<pNandDrv->u8_PageByteCntBits), (U8*)au8_RSpare, 1);
	    if(UNFD_ST_SUCCESS != u32_err)
    	{
	    	nand_debug(0,1,"error, r bdr fail: %lX\n", u32_err);
		    while(1);
    	}
	    u32_err = NCTEST_DataCompare(
			(U8*)sgpau8_ImgPtr[u8_ImgIdx]+(u32_i<<pNandDrv->u8_PageByteCntBits),
			(U8*)au8_R+(u32_i<<pNandDrv->u8_PageByteCntBits),
			pNandDrv->u16_PageByteCnt);
    	if(UNFD_ST_SUCCESS != u32_err)
	    {
		    nand_debug(0,1,"error, c bdr data fail: %lX\n", u32_err);
    		while(1);
	    }
    	nand_debug(0,1,"\n\n");
	    dump_mem(au8_R+(u32_i<<pNandDrv->u8_PageByteCntBits), pNandDrv->u16_PageByteCnt);
    	nand_debug(0,1,"\n\n");

	    u32_err = NCTEST_DataCompare(au8_WSpare, au8_RSpare,
		    pNandDrv->u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt);
    	if(UNFD_ST_SUCCESS != u32_err)
	    {
		    nand_debug(0,1,"error, c bdr spare fail: %lX\n", u32_err);
    		while(1);
	    }
	    dump_mem(au8_RSpare, pNandDrv->u16_SpareByteCnt);
		nand_debug(0,1,"\n\n");

		if(sizeof(sgau8_Img3) <= ((u32_i+1)<<pNandDrv->u8_PageByteCntBits))
			break;
	}

	nand_debug(0,1,"\n bdr ok, %Xh %Xh, %lXh %lXh\n",
		sizeof(sgau8_Img3), sizeof(sgpau8_ImgPtr[u8_ImgIdx]),
		drvNAND_CheckSum(sgpau8_ImgPtr[u8_ImgIdx], sizeof(sgau8_Img3)),
		drvNAND_CheckSum(au8_R, sizeof(sgau8_Img3)));

	return UNFD_ST_SUCCESS;
}
#endif
