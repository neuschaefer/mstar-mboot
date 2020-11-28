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
//  MStar Semiconductor - Unified eMMC Driver
//
//  eMMC_hal.c - Storage Team, 2011/10/03
//
//  Design Notes:
//    2011/10/03 - FCIE3 physical layer functions (hill.sung)
//
//=======================================================================
#include "../../inc/common/eMMC.h"
#if defined(UNIFIED_eMMC_DRIVER) && UNIFIED_eMMC_DRIVER
extern U8 g_eMMCDrv_array[15];

//========================================================
// HAL pre-processors
//========================================================
#if IF_FCIE_SHARE_PINS
	#define eMMC_PAD_SWITCH(enable)    eMMC_pads_switch(enable);
#else
    // NULL to save CPU a JMP/RET time
	#define eMMC_PAD_SWITCH(enable)
#endif

#if IF_FCIE_SHARE_CLK
	#define eMMC_CLK_SETTING(ClkParam) eMMC_clock_setting(ClkParam);
#else
    // NULL to save CPU a JMP/RET time
	#define eMMC_CLK_SETTING(ClkParam)
#endif

#if IF_FCIE_SHARE_IP
    // re-config FCIE3 for NFIE mode
	#define eMMC_RECONFIG()       eMMC_ReConfig();
#else
    // NULL to save CPU a JMP/RET time
    #define eMMC_RECONFIG()
#endif

//#define eMMC_FCIE_CLK_DIS()    REG_FCIE_CLRBIT(FCIE_SD_MODE, BIT_SD_CLK_EN)

#define eMMC_CMD1_RETRY_CNT    0x1000
#define eMMC_CMD3_RETRY_CNT    0x5

//========================================================
// HAL APIs
//========================================================
U32 eMMC_FCIE_WaitEvents(U32 u32_RegAddr, U16 u16_Events, U32 u32_MicroSec)
{
    return eMMC_FCIE_PollingEvents(u32_RegAddr, u16_Events, u32_MicroSec);
}

U32 eMMC_FCIE_PollingEvents(U32 u32_RegAddr, U16 u16_Events, U32 u32_MicroSec)
{
	 U32 u32_i;
	 U16 u16_val;

	for(u32_i=0; u32_i<u32_MicroSec; u32_i++)
	{
		eMMC_hw_timer_delay(HW_TIMER_DELAY_1us);
		REG_FCIE_R(u32_RegAddr, u16_val);
		if(u16_Events == (u16_val & u16_Events))
			break;
	}

	if(u32_i == u32_MicroSec)
	{
		return eMMC_ST_ERR_TIMEOUT_WAIT_REG0;
	}

	return eMMC_ST_SUCCESS;
}


U32 eMMC_FCIE_Reset(void)
{

	#ifdef IP_FCIE_VERSION_5

	REG_FCIE_CLRBIT(FCIE_RST, BIT_FCIE_SOFT_RST_n);
	eMMC_hw_timer_delay(HW_TIMER_DELAY_100us);
	REG_FCIE_SETBIT(FCIE_RST, BIT_FCIE_SOFT_RST_n);

	#else


	// miu request reset - set
	REG_FCIE_SETBIT(FCIE_MMA_PRI_REG, BIT_MIU_REQUEST_RST);

	// FCIE reset - set
	REG_FCIE_CLRBIT(FCIE_TEST_MODE, BIT_FCIE_SOFT_RST_n); /* active low */
	eMMC_hw_timer_delay(HW_TIMER_DELAY_100us);


	// FCIE reset - clear
	REG_FCIE_SETBIT(FCIE_TEST_MODE, BIT_FCIE_SOFT_RST_n);
	// FCIE reset - check
	//eMMC_FCIE_CheckResetDone();
	// miu request reset - clear
	REG_FCIE_CLRBIT(FCIE_MMA_PRI_REG, BIT_MIU_REQUEST_RST);

	#endif

	return eMMC_ST_SUCCESS;
}


U32 eMMC_FCIE_Init(void)
{
	U32 u32_err;

	eMMC_PlatformResetPre();


	// ------------------------------------------
	u32_err = eMMC_FCIE_Reset();
	if(eMMC_ST_SUCCESS != u32_err)
	{
		return u32_err;
	}

	#ifdef IP_FCIE_VERSION_5

	REG_FCIE_W(FCIE_MIE_INT_EN, 0);
	REG_FCIE_W(FCIE_MIE_FUNC_CTL, BIT_EMMC_EN);
	REG_FCIE_W(FCIE_SD_MODE, 0);
	REG_FCIE_W(FCIE_SD_CTRL, 0);
	REG_FCIE_W(FCIE_BLK_SIZE, 512);

	REG_FCIE_W(FCIE_RSP_SHIFT_CNT, 0);
	REG_FCIE_W(FCIE_RX_SHIFT_CNT, 0);

	REG_FCIE_W(FCIE_WR_SBIT_TIMER, 0);
	REG_FCIE_W(FCIE_RD_SBIT_TIMER, 0);

	#else

	REG_FCIE_W(FCIE_MIE_INT_EN, 0);
	REG_FCIE_W(FCIE_MMA_PRI_REG, BIT_MIU_CLK_FREE_RUN);
	REG_FCIE_W(FCIE_PATH_CTRL, BIT_SD_EN);
	// all cmd are 5 bytes (excluding CRC)
	REG_FCIE_W(FCIE_CMD_SIZE, eMMC_CMD_BYTE_CNT);
	REG_FCIE_W(FCIE_SD_CTRL, 0);
	REG_FCIE_W(FCIE_SD_MODE, 0);
	// default sector size: 0x200
	REG_FCIE_W(FCIE_SDIO_CTRL, BIT_SDIO_BLK_MODE | eMMC_SECTOR_512BYTE);

	//REG_FCIE_W(FCIE_BOOT_CONFIG, 0); // set by eMMC_pads_switch
	REG_FCIE_W(FCIE_PWR_SAVE_MODE, 0);

	#endif

	eMMC_FCIE_ClearEvents();
    eMMC_PlatformResetPost();

	return eMMC_ST_SUCCESS;	// ok
}


void eMMC_FCIE_ClearEvents(void)
{
	U16 u16_reg;

	while(1){
		REG_FCIE_W(FCIE_MIE_EVENT, BIT_ALL_CARD_INT_EVENTS);
		REG_FCIE_R(FCIE_MIE_EVENT, u16_reg);
		if(0==(u16_reg&BIT_ALL_CARD_INT_EVENTS))
			break;
	}

	REG_FCIE_SETBIT(FCIE_SD_STATUS, BIT_SD_FCIE_ERR_FLAGS);
}


U32 eMMC_FCIE_WaitD0High(U32 u32_Timeout)
{
	U32 u32_cnt;
	U16 u16_read;

	for(u32_cnt=0; u32_cnt < u32_Timeout; u32_cnt++)
	{
		REG_FCIE_R(FCIE_SD_STATUS, u16_read);

		#ifdef IP_FCIE_VERSION_5
		if(!(u16_read&BIT_SD_CARD_BUSY))
			break;
		#else
		if((u16_read&BIT_SD_CARD_D0_ST))
			break;
		#endif

		eMMC_hw_timer_delay(HW_TIMER_DELAY_1us);
	}

	if(u32_Timeout == u32_cnt)
	{
		return eMMC_ST_ERR_TIMEOUT_WAITD0HIGH;
	}

	return eMMC_ST_SUCCESS;
}


#define WAIT_FIFOCLK_READY_CNT  0x10000

U32 eMMC_FCIE_FifoClkRdy(void)
{
	#ifndef IP_FCIE_VERSION_5
	 U32 u32_i;
	 U16 u16_Reg;

	for(u32_i=0; u32_i<TIME_WAIT_FIFOCLK_RDY; u32_i++)
	{
		REG_FCIE_R(FCIE_MMA_PRI_REG, u16_Reg);
		if(u16_Reg & BIT_FIFO_CLKRDY)
			break;
		eMMC_hw_timer_delay(HW_TIMER_DELAY_1us);
	}

	if(WAIT_FIFOCLK_READY_CNT == u32_i)
	{
	    // add debug register
		return eMMC_ST_ERR_TIMEOUT_FIFOCLKRDY;
	}
	#endif
	return eMMC_ST_SUCCESS;
}


U32 eMMC_FCIE_SendCmd
(
	U16 u16_Mode, U16 u16_Ctrl, U32 u32_Arg, U8 u8_CmdIdx, U8 u8_RspByteCnt
)
{
	U32 u32_err, u32_Timeout = TIME_WAIT_DAT0_HIGH;
	eMMC_DRIVER *g_eMMCDrv = (eMMC_DRIVER *)g_eMMCDrv_array;

#ifdef IP_FCIE_VERSION_5
	REG_FCIE_W(FCIE_CMD_RSP_SIZE, (5<<BIT_CMD_SIZE_SHIFT) | u8_RspByteCnt );
#else
	REG_FCIE_W(FCIE_RSP_SIZE, u8_RspByteCnt & BIT_SD_RSP_SIZE_MASK);
#endif
	REG_FCIE_W(FCIE_SD_MODE, u16_Mode);
	// set cmd
	//   CIFC(0) = 39:32 | 47:40
    //   CIFC(1) = 23:16 | 31:24
    //   CIFC(2) = (CIFC(2) & 0xFF00) | 15:8, ignore (CRC7 | end_bit).

    REG_FCIE_W(FCIE_CIFC_ADDR(0),((u32_Arg>>24)<<8) | (0x40|u8_CmdIdx));
	REG_FCIE_W(FCIE_CIFC_ADDR(1), (u32_Arg&0xFF00) | ((u32_Arg>>16)&0xFF));
	REG_FCIE_W(FCIE_CIFC_ADDR(2),  u32_Arg&0xFF);

	if(12 != u8_CmdIdx)
	{
		u32_err = eMMC_FCIE_WaitD0High(u32_Timeout);
		if(eMMC_ST_SUCCESS != u32_err)
			goto LABEL_SEND_CMD_ERROR;
	}

	REG_FCIE_W(FCIE_SD_CTRL, u16_Ctrl);

	#ifdef IP_FCIE_VERSION_5
	REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_JOB_START);
	#endif

	if(g_eMMCDrv->u32_Flag & FCIE_FLAG_RSP_WAIT_D0H){
		u32_err = eMMC_FCIE_WaitD0High(u32_Timeout);
        if(eMMC_ST_SUCCESS != u32_err)
	        goto LABEL_SEND_CMD_ERROR;
	}

	// wait event
	u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT, BIT_SD_CMD_END, TIME_WAIT_CMDRSP_END);

	LABEL_SEND_CMD_ERROR:
	return u32_err;

}


void eMMC_FCIE_GetCIFC(U16 u16_WordPos, U16 u16_WordCnt, U16 *pu16_Buf)
{
	U16 u16_i;

	for(u16_i=u16_WordPos; u16_i<u16_WordCnt; u16_i++)
		REG_FCIE_R(FCIE_CIFC_ADDR(u16_i), pu16_Buf[u16_i]);
}

#ifdef IP_FCIE_VERSION_5

U32 eMMC_WaitCIFD_Event(U16 u16_WaitEvent, U32  u32_MicroSec)
{
	volatile U32 u32_Count;
	volatile U16 u16_Reg;

	for (u32_Count=0; u32_Count < u32_MicroSec; u32_Count++)
	{
		REG_FCIE_R(NC_CIFD_EVENT, u16_Reg);
		if ((u16_Reg & u16_WaitEvent) == u16_WaitEvent)
			break;

		eMMC_hw_timer_delay(HW_TIMER_DELAY_1us);
	}
	if (u32_Count >= u32_MicroSec)
	{
		REG_FCIE_R(NC_CIFD_EVENT, u16_Reg);
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "CIFD Event Timout %X\n", u16_Reg);
	}
	return u32_Count;
}

U32 eMMC_WaitGetCIFD(U8 * pu8_DataBuf, U32 u32_ByteCnt)
{
	U16 u16_i, *pu16_Data = (U16*)pu8_DataBuf;

	if(u32_ByteCnt > FCIE_CIFD_BYTE_CNT)
	{
		return eMMC_ST_ERR_INVALID_PARAM;
	}
	if (eMMC_WaitCIFD_Event(BIT_WBUF_FULL, HW_TIMER_DELAY_500ms)== (HW_TIMER_DELAY_500ms ))
	{
		return eMMC_ST_ERR_CMD17_CIFD;
	}

	for(u16_i=0; u16_i<(u32_ByteCnt>>1); u16_i++)
		REG_FCIE_R(NC_WBUF_CIFD_ADDR(u16_i), pu16_Data[u16_i]);

	REG_FCIE_W(NC_CIFD_EVENT, BIT_WBUF_FULL); // W1C

	REG_FCIE_W(NC_CIFD_EVENT, BIT_WBUF_EMPTY_TRI);

	return eMMC_ST_SUCCESS;
}

#else

void eMMC_FCIE_GetCIFD(U16 u16_WordPos, U16 u16_WordCnt, U16 *pu16_Buf)
{
	U16 u16_i;

	for(u16_i=u16_WordPos; u16_i<u16_WordCnt; u16_i++)
		REG_FCIE_R(FCIE_CIFD_ADDR(u16_i), pu16_Buf[u16_i]);
}

#endif

//========================================================
// Send CMD HAL APIs
//========================================================
U32 eMMC_Identify(void)
{
	U32 u32_err;
	U16 u16_i;
    eMMC_DRIVER *g_eMMCDrv = (eMMC_DRIVER *)g_eMMCDrv_array;

	// CMD0
	u32_err = eMMC_CMD0(0); // reset to idle state

	if(eMMC_ST_SUCCESS != u32_err)
		return u32_err;

	// CMD1
	for(u16_i=0; u16_i<eMMC_CMD1_RETRY_CNT; u16_i++)
	{
		u32_err = eMMC_CMD1();
		if(eMMC_ST_SUCCESS == u32_err)
			break;
        eMMC_hw_timer_delay(HW_TIMER_DELAY_1ms);

		if(eMMC_ST_ERR_CMD1_DEV_NOT_RDY != u32_err)
            return u32_err;
	}

	// CMD2
    u32_err = eMMC_CMD2();
	if(eMMC_ST_SUCCESS != u32_err)
		return u32_err;

	// CMD3
	u32_err = eMMC_CMD3_CMD7(g_eMMCDrv->u16_RCA, 3);
	if(eMMC_ST_SUCCESS != u32_err)
	{
	    g_eMMCDrv->u16_RCA++;
	    return u32_err;
	}


	return eMMC_ST_SUCCESS;
}


// reest, etc.
U32 eMMC_CMD0(U32 u32_Arg)
{
	U32 u32_err;
	U16 u16_ctrl;
    eMMC_DRIVER *g_eMMCDrv = (eMMC_DRIVER *)g_eMMCDrv_array;

	u16_ctrl = BIT_SD_CMD_EN;

	//LABEL_SEND_CMD:
	eMMC_FCIE_ClearEvents();
	u32_err = eMMC_FCIE_SendCmd(g_eMMCDrv->u16_Reg10_Mode, u16_ctrl, u32_Arg, 0, 0);

	return u32_err;
}


// send OCR
U32 eMMC_CMD1(void)
{
	U32 u32_err, u32_arg;
	U16 u16_ctrl, u16_reg;
    eMMC_DRIVER *g_eMMCDrv = (eMMC_DRIVER *)g_eMMCDrv_array;

	// (sector mode | byte mode) | (3.0|3.1|3.2|3.3|3.4 V)
	u32_arg = BIT30 | (BIT23|BIT22|BIT21|BIT20|BIT19|BIT18|BIT17|BIT16|BIT15);
	u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;


	eMMC_FCIE_ClearEvents();
	u32_err = eMMC_FCIE_SendCmd(
		g_eMMCDrv->u16_Reg10_Mode, u16_ctrl, u32_arg, 1, eMMC_R3_BYTE_CNT);

    if(eMMC_ST_SUCCESS != u32_err)
		return u32_err;

	// check status
	REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
	// R3 has no CRC, so does not check BIT_SD_RSP_CRC_ERR
	if(u16_reg & BIT_SD_RSP_TIMEOUT)
	{
	    u32_err = eMMC_ST_ERR_CMD1;
		return u32_err;
	}
	else
	{	// CMD1 ok, do things here
	    eMMC_FCIE_GetCIFC(0, 3, (U16*)g_eMMCDrv->au8_Rsp);

		if(0 == (g_eMMCDrv->au8_Rsp[1] & 0x80))
			u32_err =  eMMC_ST_ERR_CMD1_DEV_NOT_RDY;
		else
			g_eMMCDrv->u8_IfSectorMode = (g_eMMCDrv->au8_Rsp[1]&BIT6)>>6;
	}

	return u32_err;
}


// send CID
U32 eMMC_CMD2(void)
{
	U32 u32_err, u32_arg;
	U16 u16_ctrl, u16_reg;
	eMMC_DRIVER *g_eMMCDrv = (eMMC_DRIVER *)g_eMMCDrv_array;

	u32_arg = 0;
	u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN | BIT_SD_RSPR2_EN;


	eMMC_FCIE_ClearEvents();
	u32_err = eMMC_FCIE_SendCmd(
		g_eMMCDrv->u16_Reg10_Mode, u16_ctrl, u32_arg, 2, eMMC_R2_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {

    }
	else
	{	// check status
		REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
		if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR))
		{
			u32_err = eMMC_ST_ERR_CMD2;
		}
	}

	return u32_err;
}


// CMD3: assign RCA. CMD7: select device
U32 eMMC_CMD3_CMD7(U16 u16_RCA, U8 u8_CmdIdx)
{
	U32 u32_err, u32_arg;
	U16 u16_ctrl, u16_reg;
    eMMC_DRIVER *g_eMMCDrv = (eMMC_DRIVER *)g_eMMCDrv_array;

	if(7 == u8_CmdIdx)
		g_eMMCDrv->u32_Flag |= FCIE_FLAG_RSP_WAIT_D0H;

	u32_arg = u16_RCA<<16;
	u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;

	eMMC_FCIE_ClearEvents();
	u32_err = eMMC_FCIE_SendCmd(
		g_eMMCDrv->u16_Reg10_Mode, u16_ctrl, u32_arg, u8_CmdIdx, eMMC_R1_BYTE_CNT);

	if(eMMC_ST_SUCCESS == u32_err)
	{
	    // check status
		REG_FCIE_R(FCIE_SD_STATUS, u16_reg);

		// de-select has no rsp
		if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR))
		{
			u32_err = eMMC_ST_ERR_CMD3_CMD7;
		}
		else
		{
			u32_err = eMMC_CheckR1Error();
		}
	}

	g_eMMCDrv->u32_Flag &= ~FCIE_FLAG_RSP_WAIT_D0H;
	return u32_err;
}

#ifdef IP_FCIE_VERSION_5

U32 eMMC_SetBusSpeed(U8 u8_BusSpeed)
{
	U32 u32_err;

	u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 185, u8_BusSpeed);
	if(eMMC_ST_SUCCESS != u32_err)
		return u32_err;

	return u32_err;
}

#endif

U32 eMMC_SetBusWidth(U8 u8_BusWidth)
{
	U8  u8_value;
	U32 u32_err;

    eMMC_DRIVER *g_eMMCDrv = (eMMC_DRIVER *)g_eMMCDrv_array;
	// -------------------------------
	if(u8_BusWidth !=8)
		return eMMC_ST_ERR_PARAMETER;
	else
        u8_value=2;


	// -------------------------------
	u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 183, u8_value);
	if(eMMC_ST_SUCCESS != u32_err)
		return u32_err;

	// -------------------------------
	g_eMMCDrv->u16_Reg10_Mode &= ~BIT_SD_DATA_WIDTH_MASK;

	g_eMMCDrv->u8_BUS_WIDTH = BIT_SD_DATA_WIDTH_8;
	g_eMMCDrv->u16_Reg10_Mode |= BIT_SD_DATA_WIDTH_8;


	return u32_err;
}

U32 eMMC_ModifyExtCSD(U8 u8_AccessMode, U8 u8_ByteIdx, U8 u8_Value)
{
	U32 u32_arg, u32_err;

	u32_arg = ((u8_AccessMode&3)<<24) | (u8_ByteIdx<<16) |
		      (u8_Value<<8);

	u32_err = eMMC_CMD6(u32_arg);


    return u32_err;
}

// SWITCH cmd
U32 eMMC_CMD6(U32 u32_Arg)
{
	U32 u32_err, u32_arg;
	U16 u16_ctrl, u16_reg;
    eMMC_DRIVER *g_eMMCDrv = (eMMC_DRIVER *)g_eMMCDrv_array;

	u32_arg = u32_Arg;
	u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;
	g_eMMCDrv->u32_Flag |= FCIE_FLAG_RSP_WAIT_D0H;


	eMMC_FCIE_ClearEvents();
	u32_err = eMMC_FCIE_SendCmd(
		g_eMMCDrv->u16_Reg10_Mode, u16_ctrl, u32_arg, 6, eMMC_R1b_BYTE_CNT);

	if(eMMC_ST_SUCCESS == u32_err)
	{	// check status
		REG_FCIE_R(FCIE_SD_STATUS, u16_reg);

		if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR))
		{
			u32_err = eMMC_ST_ERR_CMD6;
		}
		else
		{
			u32_err = eMMC_CheckR1Error();
		}
	}

	g_eMMCDrv->u32_Flag &= ~FCIE_FLAG_RSP_WAIT_D0H;
	return u32_err;
}

//------------------------------------------------

U32 eMMC_CMD17_CIFD(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf)
{
	U32 u32_err, u32_arg;
	U16 u16_mode, u16_ctrl, u16_reg;

	#ifdef IP_FCIE_VERSION_5
	U16 u16_i;
	#endif

    eMMC_DRIVER *g_eMMCDrv = (eMMC_DRIVER *)g_eMMCDrv_array;

	#ifndef IP_FCIE_VERSION_5
	REG_FCIE_W(FCIE_CIFD_WORD_CNT, 0);
	#endif

	// -------------------------------
	// send cmd
	u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN | BIT_SD_DAT_EN;

	u32_arg =  u32_eMMCBlkAddr << (g_eMMCDrv->u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);
	u16_mode = BIT_SD_DATA_CIFD | g_eMMCDrv->u16_Reg10_Mode | g_eMMCDrv->u8_BUS_WIDTH;
	eMMC_FCIE_ClearEvents();

	#ifdef IP_FCIE_VERSION_5

	REG_FCIE_W(FCIE_JOB_BL_CNT, 1);

	REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, eMMC_SECTOR_512BYTE & 0xFFFF);
	REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16, eMMC_SECTOR_512BYTE >> 16);

	#endif

	u32_err = eMMC_FCIE_SendCmd(
		u16_mode, u16_ctrl, u32_arg, 17, eMMC_R1_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
		goto LABEL_END;
    }

	// -------------------------------
	// check FCIE

	#ifdef IP_FCIE_VERSION_5

	//read for data
	for (u16_i=0; u16_i< (eMMC_SECTOR_512BYTE >> 6); u16_i++)
	{   // read data
		u32_err = eMMC_WaitGetCIFD((U8*)((U32)pu8_DataBuf + (u16_i << 6)), 0x40);
		if(u32_err != eMMC_ST_SUCCESS)
		{
			goto LABEL_END;
		}
	}

	u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT, BIT_DMA_END, TIME_WAIT_1_BLK_END);

	#else
	u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT, BIT_SD_DATA_END, TIME_WAIT_1_BLK_END);
	#endif

	if(eMMC_ST_SUCCESS != u32_err)
	{
		u32_err = eMMC_ST_ERR_CMD17_CIFD;
		goto LABEL_END;
	}

	REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
	if(u16_reg & BIT_SD_FCIE_ERR_FLAGS)
	{
		u32_err = eMMC_ST_ERR_CMD17_CIFD;
		goto LABEL_END;
	}

	// -------------------------------
	// check device
	u32_err = eMMC_CheckR1Error();
	if(eMMC_ST_SUCCESS != u32_err)
	{
		u32_err = eMMC_ST_ERR_CMD17_CIFD;
		goto LABEL_END;
	}

	#ifndef IP_FCIE_VERSION_5
	// -------------------------------
	// CMD17 ok, do things here
	eMMC_FCIE_GetCIFD(0, eMMC_SECTOR_512BYTE>>1, (U16*)pu8_DataBuf);
	#endif

	LABEL_END:

	return u32_err;
}


U32 eMMC_CMD12(U16 u16_RCA)
{
	U32 u32_err, u32_arg;
	U16 u16_ctrl, u16_reg;
    eMMC_DRIVER *g_eMMCDrv = (eMMC_DRIVER *)g_eMMCDrv_array;

    u32_arg = (u16_RCA<<16);
	u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;
	g_eMMCDrv->u32_Flag |= FCIE_FLAG_RSP_WAIT_D0H;


	eMMC_FCIE_ClearEvents();

	u32_err = eMMC_FCIE_SendCmd(
		g_eMMCDrv->u16_Reg10_Mode, u16_ctrl, u32_arg, 12, eMMC_R1b_BYTE_CNT);

	if(eMMC_ST_SUCCESS == u32_err)
	{	// check status
		REG_FCIE_R(FCIE_SD_STATUS, u16_reg);

		if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR))
		{
			u32_err = eMMC_ST_ERR_CMD12;
		}
		else
		{
			u32_err = eMMC_CheckR1Error();
		}
	}

	g_eMMCDrv->u32_Flag &= ~FCIE_FLAG_RSP_WAIT_D0H;
	return u32_err;
}


U32 eMMC_CMD18_MIU(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf, U16 u16_BlkCnt)
{
	U32 u32_err, u32_err_12, u32_arg;
	U16 u16_mode, u16_ctrl, u16_reg;
	U32 u32_dma_addr;
    eMMC_DRIVER *g_eMMCDrv = (eMMC_DRIVER *)g_eMMCDrv_array;

	// -------------------------------
	// send cmd
	u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN | BIT_SD_DAT_EN;

	u32_arg =  u32_eMMCBlkAddr << (g_eMMCDrv->u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);
	u16_mode = g_eMMCDrv->u16_Reg10_Mode | g_eMMCDrv->u8_BUS_WIDTH;

	eMMC_FCIE_ClearEvents();
	REG_FCIE_W(FCIE_JOB_BL_CNT, u16_BlkCnt);
    u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)pu8_DataBuf, eMMC_SECTOR_512BYTE*u16_BlkCnt);

	#ifdef IP_FCIE_VERSION_5

	REG_FCIE_W(FCIE_MIU_DMA_ADDR_15_0, u32_dma_addr & 0xFFFF);
	REG_FCIE_W(FCIE_MIU_DMA_ADDR_31_16, u32_dma_addr >> 16);

	REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, (eMMC_SECTOR_512BYTE*u16_BlkCnt) & 0xFFFF);
	REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16,( eMMC_SECTOR_512BYTE*u16_BlkCnt) >> 16);

	#else

	REG_FCIE_W(FCIE_SDIO_ADDR0, u32_dma_addr & 0xFFFF);
	REG_FCIE_W(FCIE_SDIO_ADDR1, u32_dma_addr >> 16);

	#endif

	#ifndef IP_FCIE_VERSION_5

	REG_FCIE_CLRBIT(FCIE_MMA_PRI_REG, BIT_DMA_DIR_W);
	u32_err = eMMC_FCIE_FifoClkRdy();
	if(eMMC_ST_SUCCESS != u32_err)
	{
		goto LABEL_END;
	}
	REG_FCIE_SETBIT(FCIE_PATH_CTRL, BIT_MMA_EN);

	#endif

	u32_err = eMMC_FCIE_SendCmd(
		u16_mode, u16_ctrl, u32_arg, 18, eMMC_R1_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
		goto LABEL_END;
    }

	// -------------------------------
	// check FCIE

	#ifdef IP_FCIE_VERSION_5

	u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT, BIT_DMA_END, TIME_WAIT_n_BLK_END*(1+(u16_BlkCnt>>9)));

	#else
	u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT,
	    BIT_MIU_LAST_DONE|BIT_CARD_DMA_END, TIME_WAIT_n_BLK_END*(1+(u16_BlkCnt>>9)));
	#endif
	if(eMMC_ST_SUCCESS != u32_err)
	{
		u32_err = eMMC_ST_ERR_CMD18;
		goto LABEL_END;
	}

	REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
	if(eMMC_ST_SUCCESS != u32_err || (u16_reg & BIT_SD_FCIE_ERR_FLAGS))
	{
		u32_err = eMMC_ST_ERR_CMD18;
		goto LABEL_END;
	}
	// -------------------------------
	// check device
	u32_err = eMMC_CheckR1Error();
	if(eMMC_ST_SUCCESS != u32_err)
	{
		u32_err = eMMC_ST_ERR_CMD18;
		goto LABEL_END;
	}

	LABEL_END:
	u32_err_12 = eMMC_CMD12(g_eMMCDrv->u16_RCA);
	return u32_err ? u32_err : u32_err_12;

}



U32 eMMC_CheckR1Error(void)
{
    eMMC_DRIVER *g_eMMCDrv = (eMMC_DRIVER *)g_eMMCDrv_array;
	eMMC_FCIE_GetCIFC(0, 3, (U16*)g_eMMCDrv->au8_Rsp);
	if(g_eMMCDrv->au8_Rsp[1] & (eMMC_ERR_R1_31_24>>24))
	{
		return eMMC_ST_ERR_R1_31_24;
	}

	if(g_eMMCDrv->au8_Rsp[2] & (eMMC_ERR_R1_23_16>>16))
	{
		return eMMC_ST_ERR_R1_23_16;
	}

	if(g_eMMCDrv->au8_Rsp[3] & (eMMC_ERR_R1_15_8>>8))
	{
		return eMMC_ST_ERR_R1_15_8;
	}

	if(g_eMMCDrv->au8_Rsp[4] & (eMMC_ERR_R1_7_0>>0))
	{
		return eMMC_ST_ERR_R1_7_0;
	}

	return eMMC_ST_SUCCESS;
}



#endif

