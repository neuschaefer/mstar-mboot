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
//=======================================================================
//  MStar Semiconductor - Unified Nand Flash Driver
//
//  drvNAND_hal.c - Storage Team, 2009/08/20
//
//  Design Notes:
//    2009/08/21 - FCIE3 physical layer functions
//
//=======================================================================

#include "../../inc/common/drvNAND.h"


//========================================================
// HAL pre-processors
//========================================================
#if IF_FCIE_SHARE_PINS
    #define NC_PAD_SWITCH(enable)
#else
    #define NC_PAD_SWITCH(enable)
#endif

#if IF_FCIE_SHARE_CLK
    #define NC_CLK_SETTING(ClkParam)
#else
    #define NC_CLK_SETTING(ClkParam)
#endif

#if IF_FCIE_SHARE_IP
    #define NC_LOCK_FCIE()
    #define NC_UNLOCK_FCIE()
    #define NC_RECONFIG()
#else
    #define NC_LOCK_FCIE()
    #define NC_UNLOCK_FCIE()
    #define NC_RECONFIG()
#endif

#if defined(NEED_FLUSH_MIU_PIPE) && NEED_FLUSH_MIU_PIPE
    #define FLUSH_MIU_PIPE()
#else
    #define FLUSH_MIU_PIPE()
#endif


//========================================================
// HAL misc. function definitions
//========================================================
#if defined(NC_SEL_FCIE5) && NC_SEL_FCIE5
U32  NC_WaitComplete(U32 u32_EventReg, U16 u16_WaitEvent, U32 u32_MicroSec);
U32 NC_WaitGetCIFD(U8 * pu8_DataBuf, U32 u32_ByteCnt);

void NC_GetCIFD(U8 *pu8_Buf, U32 u32_CIFDPos, U32 u32_ByteCnt)
{
	U32 u32_i, u32_BufPos;
	U16 u16_Tmp;

	if (u32_CIFDPos & 1) {
		REG_READ_UINT16(NC_WBUF_CIFD_ADDR(u32_CIFDPos>>1), u16_Tmp);
		pu8_Buf[0] = (U8)(u16_Tmp >> 8);
		u32_CIFDPos += 1;
		u32_ByteCnt -= 1;
		u32_BufPos = 1;
	} else
		u32_BufPos = 0;

	for (u32_i=0; u32_i<u32_ByteCnt>>1; u32_i++) {
		REG_READ_UINT16(NC_WBUF_CIFD_ADDR(u32_i+(u32_CIFDPos>>1)), u16_Tmp);
		pu8_Buf[(u32_i<<1)+u32_BufPos] = (U8)u16_Tmp;
		pu8_Buf[(u32_i<<1)+u32_BufPos+1] = (U8)(u16_Tmp>>8);
	}

	if (u32_ByteCnt - (u32_i<<1)) {
		REG_READ_UINT16(NC_WBUF_CIFD_ADDR(u32_i+(u32_CIFDPos>>1)), u16_Tmp);
		pu8_Buf[(u32_i<<1)+u32_BufPos] = (U8)u16_Tmp;
	}

}

U32 NC_WaitGetCIFD(U8 * pu8_DataBuf, U32 u32_ByteCnt)
{
	if(u32_ByteCnt > NC_CIFD_WBUF_BYTE_CNT)
	{
		return UNFD_ST_ERR_INVAL_CIFD_CNT;
	}
	if (NC_WaitComplete(NC_CIFD_EVENT, BIT_WBUF_FULL, WAIT_READ_TIME)== (WAIT_READ_TIME ))
	{
		REG_WRITE_UINT16(NC_PART_MODE, 0);
		REG_CLR_BITS_UINT16(NC_FUN_CTL, BIT_R2N_MODE_EN);
		NC_CLR_DDR_MODE();
		return UNFD_ST_ERR_R_TIMEOUT_RM; // timeout
	}
	NC_GetCIFD(pu8_DataBuf , 0, u32_ByteCnt);

	REG_WRITE_UINT16(NC_CIFD_EVENT,BIT_WBUF_FULL);
	
	REG_WRITE_UINT16(NC_CIFD_EVENT, BIT_WBUF_EMPTY_TRI);

	return UNFD_ST_SUCCESS;
}


U32  NC_ReadSectors(U32 u32_PhyRowIdx, U8 u8_SectorInPage, U8 *pu8_DataBuf, U8 *pu8_SpareBuf, U32 u32_SectorCnt)
{
	U16 u16_Tmp;
	NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();
	U32	u32_DataDMAAddr, U32_SpareDMAAddr;

	// HW setting
	NC_PAD_SWITCH(pNandDrv->u8_PadMode);
	NC_CLK_SETTING(pNandDrv->u32_Clk);
	NC_RECONFIG();
	NC_SET_DDR_MODE(); // to turn on ONFI clk
	REG_WRITE_UINT16(NC_MIE_EVENT, BIT_NC_JOB_END);
	REG_CLR_BITS_UINT16(NC_FUN_CTL, BIT_R2N_MODE_EN);

	u32_DataDMAAddr = ((U32)pu8_DataBuf)&0x1FFFFFFF;
	U32_SpareDMAAddr = ((U32)pu8_SpareBuf)&0x1FFFFFFF;
	
	REG_WRITE_UINT16(NC_RSPARE_DMA_ADR0, (U32)U32_SpareDMAAddr & 0xFFFF);
	REG_WRITE_UINT16(NC_RSPARE_DMA_ADR1, (U32)U32_SpareDMAAddr >>16);

	REG_WRITE_UINT16(NC_PART_MODE, (BIT_PARTIAL_MODE_EN)|((u32_SectorCnt - 1) << BIT_START_SECTOR_CNT_SHIFT)|(u8_SectorInPage << BIT_START_SECTOR_IDX_SHIFT));
	
	REG_WRITE_UINT16(NC_RDATA_DMA_ADR0, (U32)u32_DataDMAAddr & 0xFFFF);
	REG_WRITE_UINT16(NC_RDATA_DMA_ADR1, (U32)u32_DataDMAAddr >> 16);

	REG_WRITE_UINT16(NC_AUXREG_ADR, AUXADR_ADRSET);

	REG_WRITE_UINT16(NC_AUXREG_DAT, u8_SectorInPage << pNandDrv->u8_SectorByteCntBits);
	REG_WRITE_UINT16(NC_AUXREG_DAT, u32_PhyRowIdx & 0xFFFF);
	REG_WRITE_UINT16(NC_AUXREG_DAT, u32_PhyRowIdx >> 16);

	REG_WRITE_UINT16(NC_AUXREG_ADR, AUXADR_INSTQUE);
	REG_WRITE_UINT16(NC_AUXREG_DAT, (pNandDrv->u8_OpCode_RW_AdrCycle<< 8) | (CMD_0x00));

	REG_WRITE_UINT16(NC_AUXREG_DAT, (ACT_WAITRB << 8) | CMD_0x30);
	REG_WRITE_UINT16(NC_AUXREG_DAT, (ACT_BREAK << 8) | ACT_SER_DIN);

	REG_WRITE_UINT16(NC_CTRL, BIT_NC_JOB_START);
	if (NC_WaitComplete(NC_MIE_EVENT, BIT_NC_JOB_END, WAIT_READ_TIME) == (WAIT_READ_TIME))
	{
		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "Error: NC_ReadSectors Timeout, ErrCode:%Xh \r\n", UNFD_ST_ERR_R_TIMEOUT);
		REG_WRITE_UINT16(NC_PART_MODE, 0);
		return UNFD_ST_ERR_R_TIMEOUT;
	}

	// Check ECC
	REG_READ_UINT16(NC_ECC_STAT0, u16_Tmp);
	if (u16_Tmp & BIT_NC_ECC_FAIL)
	{
		NC_CLR_DDR_MODE();
		REG_WRITE_UINT16(NC_PART_MODE, 0);
		return UNFD_ST_ERR_ECC_FAIL;
	}

	REG_WRITE_UINT16(NC_PART_MODE, 0);

	NC_CLR_DDR_MODE();
	return UNFD_ST_SUCCESS;
}


U32  NC_ReadSector_RIUMode(U32 u32_PhyRowIdx, U8 u8_SectorInPage, U8 *pu8_DataBuf, U8 *pu8_SpareBuf )
{
	volatile U16 u16_Tmp, u16_i, u16_j, u16_k, u16_Cnt, u16_ByteLoc;
	U16 u16_Col;
	NAND_DRIVER *pNandDrv = (NAND_DRIVER*)drvNAND_get_DrvContext_address();
	U32 u32_Tmp, u32_Err;

	NC_PAD_SWITCH(pNandDrv->u8_PadMode);
	NC_CLK_SETTING(pNandDrv->u32_Clk);
	NC_RECONFIG();
	NC_SET_DDR_MODE();

	REG_SET_BITS_UINT16(NC_FUN_CTL, BIT_R2N_MODE_EN); // enable RIU Mode
	REG_WRITE_UINT16(NC_MIE_EVENT, BIT_NC_JOB_END);

	
	// if Partial Mode (if not 512B/page, set Partial Mode)	
	REG_WRITE_UINT16(NC_PART_MODE, BIT_PARTIAL_MODE_EN|(u8_SectorInPage<<BIT_START_SECTOR_IDX_SHIFT));
	
	REG_WRITE_UINT16(NC_AUXREG_ADR, AUXADR_ADRSET);
	u16_Col = u8_SectorInPage << pNandDrv->u8_SectorByteCntBits;
	REG_WRITE_UINT16(NC_AUXREG_DAT, u16_Col);
	REG_WRITE_UINT16(NC_AUXREG_DAT, u32_PhyRowIdx & 0xFFFF);
	REG_WRITE_UINT16(NC_AUXREG_DAT, u32_PhyRowIdx >> 16);

	REG_WRITE_UINT16(NC_AUXREG_ADR, AUXADR_INSTQUE);
	REG_WRITE_UINT16(NC_AUXREG_DAT, (pNandDrv->u8_OpCode_RW_AdrCycle<< 8) | (CMD_0x00));

	REG_WRITE_UINT16(NC_AUXREG_DAT, (ACT_WAITRB << 8) | CMD_0x30);
	REG_WRITE_UINT16(NC_AUXREG_DAT, (ACT_BREAK << 8) | ACT_SER_DIN);

	REG_WRITE_UINT16(NC_CTRL, BIT_NC_JOB_START);

	//read for data
	u16_Cnt = pNandDrv->u16_SectorByteCnt >> 6; // how many 64B per sector
	u16_Cnt = (pNandDrv->u16_SectorByteCnt & (0x40 -1)) ? u16_Cnt + 1 : u16_Cnt;
	for (u16_j=0; u16_j<u16_Cnt; u16_j++)
	{   // read data
		u16_Tmp =( (pNandDrv->u16_SectorByteCnt - (u16_j << 6)) >= 0x40) ? 
			0x40 : (pNandDrv->u16_SectorByteCnt - (u16_j << 6) );
		u32_Err = NC_WaitGetCIFD((U8*)((U32)pu8_DataBuf + (u16_j << 6)), u16_Tmp);
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			REG_CLR_BITS_UINT16(NC_FUN_CTL, BIT_R2N_MODE_EN);
			NC_CLR_DDR_MODE();
			return u32_Err;
		}		
	}
	
	//read for spare
	u16_Cnt = pNandDrv->u16_SectorSpareByteCnt >> 6; // how many 64B per sector
	u16_Cnt = (pNandDrv->u16_SectorSpareByteCnt & (0x40 -1)) ? u16_Cnt + 1 : u16_Cnt;
	for (u16_j=0; u16_j<u16_Cnt; u16_j++)
	{   // read data
		u16_Tmp =( (pNandDrv->u16_SectorSpareByteCnt - (u16_j << 6)) >= 0x40) ? 
			0x40: (pNandDrv->u16_SectorSpareByteCnt - (u16_j << 6));
		u32_Err = NC_WaitGetCIFD( (U8*)((U32)pu8_SpareBuf + (u16_j << 6)), u16_Tmp);
		if(u32_Err != UNFD_ST_SUCCESS)
		{
			REG_CLR_BITS_UINT16(NC_FUN_CTL, BIT_R2N_MODE_EN);
			NC_CLR_DDR_MODE();
			return u32_Err;
		}		
	}

	// wait for events
	u32_Tmp = 0;
	do{
		u16_Tmp = 0; // do not remove this line
		REG_READ_UINT16(NC_MIE_EVENT, u16_Tmp);
		nand_hw_timer_delay(HW_TIMER_DELAY_1us);
		u32_Tmp++;
		if(u32_Tmp > WAIT_READ_TIME)
  		{
			REG_WRITE_UINT16(NC_PART_MODE, 0);						
			REG_CLR_BITS_UINT16(NC_FUN_CTL, BIT_R2N_MODE_EN);
			NC_CLR_DDR_MODE();
			return UNFD_ST_ERR_R_TIMEOUT_RM;
		}
	}while(((u16_Tmp & BIT_NC_R2N_ECCCOR)==0) && ((u16_Tmp & (BIT_NC_JOB_END )) != (BIT_NC_JOB_END )));

    // if ECC Fail
	REG_READ_UINT16(NC_ECC_STAT2, u16_Tmp);
	if ((u16_Tmp & BIT_NC_ECC_FLGA_MASK) == BIT_NC_ECC_FLGA_FAIL)
	{
		REG_WRITE_UINT16(NC_PART_MODE, 0);				
		REG_CLR_BITS_UINT16(NC_FUN_CTL, BIT_R2N_MODE_EN);	
		return UNFD_ST_ERR_ECC_FAIL_RM;
	}

	REG_READ_UINT16(NC_MIE_EVENT, u16_Tmp);
	if (u16_Tmp & BIT_NC_R2N_ECCCOR)
	{
//		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "RIU Mode, ECC happens: ");
		// make CIFD available for SW
		// [CAUTION]: before clear BIT_NC_R2N_ECC, JOB_END would not set.
		REG_W1C_BITS_UINT16(NC_MIE_EVENT, BIT_NC_R2N_ECCCOR);
		if(NC_WaitComplete(NC_MIE_EVENT, BIT_NC_JOB_END, WAIT_READ_TIME) == WAIT_READ_TIME)
		{
			REG_WRITE_UINT16(NC_PART_MODE, 0);			
			REG_CLR_BITS_UINT16(NC_FUN_CTL, BIT_R2N_MODE_EN);			
			NC_CLR_DDR_MODE();
		}

		REG_READ_UINT16(NC_ECC_STAT2, u16_Tmp);
		u16_Cnt = (u16_Tmp & BIT_NC_ECC_CNT_MASK) >> BIT_NC_ECC_CNT_SHIFT;
//		nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "%u bits\r\n", u16_Cnt);
		for (u16_i=0; u16_i<u16_Cnt; u16_i++)
		{
			REG_CLR_BITS_UINT16(NC_ECC_STAT2, BIT_NC_ECC_SEL_LOC_MASK);
			REG_SET_BITS_UINT16(NC_ECC_STAT2, u16_i<<BIT_NC_ECC_SEL_LOC_SHIFT);
			LABEL_ECC_LOC_READ:
			//REG_READ_UINT16(NC_ECC_LOC, u16_Tmp);
			REG_READ_UINT16(NC_ECC_LOC, u16_j);
			REG_READ_UINT16(NC_ECC_LOC, u16_k);
			if(u16_j != u16_k)
				goto LABEL_ECC_LOC_READ;
//			nand_debug(UNFD_DEBUG_LEVEL_ERROR, 1, "bit loc: %02Xh \r\n", u16_j);
			u16_ByteLoc = u16_j >> 3;
			if (u16_ByteLoc < pNandDrv->u16_SectorByteCnt)
			{
				pu8_DataBuf[u16_ByteLoc] ^= 1<<(u16_j%8);
			}
			else if (u16_ByteLoc < pNandDrv->u16_SectorByteCnt +
			       pNandDrv->u16_SectorSpareByteCnt - pNandDrv->u16_ECCCodeByteCnt)
			{
				pu8_SpareBuf[u16_ByteLoc-pNandDrv->u16_SectorByteCnt] ^= 1<<(u16_j%8);
			}
		}

    	u16_Tmp = BIT_NC_R2N_ECCCOR;
  	}

	else if(0 == (u16_Tmp & BIT_NC_R2N_ECCCOR)){
		if (NC_WaitComplete(NC_MIE_EVENT, BIT_NC_JOB_END, WAIT_READ_TIME) == WAIT_READ_TIME)
		{
			U16 u16_Reg;
			REG_READ_UINT16(NC_MIE_EVENT, u16_Reg);
			REG_WRITE_UINT16(NC_PART_MODE, 0);
			REG_CLR_BITS_UINT16(NC_FUN_CTL, BIT_R2N_MODE_EN);
			return UNFD_ST_ERR_R_TIMEOUT_RM; // timeout
		}
	}

	NC_CLR_DDR_MODE();
  	REG_WRITE_UINT16(NC_PART_MODE, 0);
	REG_CLR_BITS_UINT16(NC_FUN_CTL, BIT_R2N_MODE_EN);
	return UNFD_ST_SUCCESS;
}

U32 NC_WaitComplete(U32 u32_EventReg, U16 u16_WaitEvent, U32 u32_MicroSec)
{
	volatile U32 u32_Count;
	volatile U16 u16_Reg;

	for (u32_Count=0; u32_Count < u32_MicroSec; u32_Count++)
	{
		REG_READ_UINT16(u32_EventReg, u16_Reg);
		if ((u16_Reg & u16_WaitEvent) == u16_WaitEvent)
			break;

		nand_hw_timer_delay(HW_TIMER_DELAY_1us);
	}

	if (u32_Count < u32_MicroSec)
		REG_W1C_BITS_UINT16(u32_EventReg, u16_WaitEvent); /*clear events*/

	return u32_Count;

}

#endif // NC_SEL_FCIE3
