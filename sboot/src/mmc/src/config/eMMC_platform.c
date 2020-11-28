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
//  eMMC_platform.c - Storage Team, 2011/02/25
//
//  Design Notes: defines common platform-dependent functions.
//
//    1. 2012/05/02 - support A3 uboot platform
//
//=======================================================================
#include "../../inc/common/eMMC.h"
#if defined(UNIFIED_eMMC_DRIVER) && UNIFIED_eMMC_DRIVER
extern U8 g_eMMCDrv_array[15];

//=============================================================
U32 eMMC_hw_timer_delay(U32 u32us)
{
	#if 0
    int i = 0;

	for (i = 0; i < (u32us<<2); i++)
	{
		#if 1
		 int j = 0, tmp;
		for (j = 0; j < 0x2; j++)
		{
			tmp = j;
		}
		#endif
	}
	#else
    //udelay((u32us>>1)+(u32us>>4)+1);
    //udelay(u32us * 24);
    U32 u32HWTimer = 0;
	volatile U16 u16TimerLow = 0;
	volatile U16 u16TimerHigh = 0;

	// reset HW timer
	REG_FCIE_W(TIMER0_MAX_LOW, 0xFFFF);
	REG_FCIE_W(TIMER0_MAX_HIGH, 0xFFFF);
	REG_FCIE_W(TIMER0_ENABLE, 0);

	// start HW timer
	REG_FCIE_SETBIT(TIMER0_ENABLE, 0x0001);

	while( u32HWTimer < 12*u32us ) // wait for u32usTick micro seconds
	{
		REG_FCIE_R(TIMER0_CAP_LOW, u16TimerLow);
		REG_FCIE_R(TIMER0_CAP_HIGH, u16TimerHigh);

		u32HWTimer = (u16TimerHigh<<16) | u16TimerLow;
	}

	REG_FCIE_W(TIMER0_ENABLE, 0);
	#endif
	return u32us;
}


// use to performance test
U32 eMMC_hw_timer_start(void)
{
	return 0;
}

U32 eMMC_hw_timer_tick(void)
{
	// TIMER_FREERUN_32K  32 KHz
	// TIMER_FREERUN_XTAL 38.4 MHz,
	// counting down
	return 0;//HalTimerRead(TIMER_FREERUN_32K);
}

#if (defined(eMMC_DRV_EAGLE_BOOTRAM)&&eMMC_DRV_EAGLE_BOOTRAM)
void eMMC_DumpPadClk(void)
{
	//----------------------------------------------
	eMMC_debug(0, 1, "\n[clk setting]: %uKHz \n", g_eMMCDrv.u32_ClkKHz);
	eMMC_debug(0, 1, "FCIE 1X (0x%X):0x%X\n", reg_ckg_fcie_1X, REG_FCIE_U16(reg_ckg_fcie_1X));
	eMMC_debug(0, 1, "FCIE 4X (0x%X):0x%X\n", reg_ckg_fcie_4X, REG_FCIE_U16(reg_ckg_fcie_4X));
	eMMC_debug(0, 1, "CMU (0x%X):0x%X\n", reg_ckg_CMU, REG_FCIE_U16(reg_ckg_CMU));

	//----------------------------------------------
	eMMC_debug(0, 1, "\n[pad setting]: ");
	switch(g_eMMCDrv.u32_Flag & FCIE_FLAG_PADTYPE_MASK)
	{
	case FCIE_FLAG_PADTYPE_DDR:
		eMMC_debug(0,0,"DDR\n");  break;
	case FCIE_FLAG_PADTYPE_SDR:
		eMMC_debug(0,0,"SDR\n");  break;
	case FCIE_FLAG_PADTYPE_BYPASS:
		eMMC_debug(0,0,"BYPASS\n");  break;
	default:
		eMMC_debug(0,0,"eMMC Err: Pad unknown\n");  eMMC_die("\n");
	}
	eMMC_debug(0, 1, "chiptop_0x5A (0x%X):0x%X\n", reg_chiptop_0x5A, REG_FCIE_U16(reg_chiptop_0x5A));
	eMMC_debug(0, 1, "chiptop_0x1F (0x%X):0x%X\n", reg_chiptop_0x1F, REG_FCIE_U16(reg_chiptop_0x1F));
	eMMC_debug(0, 1, "chiptop_0x70 (0x%X):0x%X\n", reg_chiptop_0x70, REG_FCIE_U16(reg_chiptop_0x70));
	eMMC_debug(0, 1, "chiptop_0x64 (0x%X):0x%X\n", reg_chiptop_0x64, REG_FCIE_U16(reg_chiptop_0x64));
	eMMC_debug(0, 1, "chiptop_0x4F (0x%X):0x%X\n", reg_chiptop_0x4F, REG_FCIE_U16(reg_chiptop_0x4F));
	eMMC_debug(0, 1, "chiptop_0x03 (0x%X):0x%X\n", reg_chiptop_0x03, REG_FCIE_U16(reg_chiptop_0x03));
	eMMC_debug(0, 1, "chiptop_0x51 (0x%X):0x%X\n", reg_chiptop_0x51, REG_FCIE_U16(reg_chiptop_0x51));
	eMMC_debug(0, 1, "chiptop_0x6F (0x%X):0x%X\n\n", reg_chiptop_0x6F, REG_FCIE_U16(reg_chiptop_0x6F));

	eMMC_debug(0, 1, "chiptop_0x43 (0x%X):0x%X\n", reg_chiptop_0x43, REG_FCIE_U16(reg_chiptop_0x43));
	eMMC_debug(0, 1, "chiptop_0x50 (0x%X):0x%X\n", reg_chiptop_0x50, REG_FCIE_U16(reg_chiptop_0x50));
	eMMC_debug(0, 1, "chiptop_0x0B (0x%X):0x%X\n", reg_chiptop_0x0B, REG_FCIE_U16(reg_chiptop_0x0B));
	eMMC_debug(0, 1, "chiptop_0x5D (0x%X):0x%X\n", reg_chiptop_0x5D, REG_FCIE_U16(reg_chiptop_0x5D));

	eMMC_debug(0, 1, "\n");
}

U32 eMMC_pads_switch(U32 u32_FCIE_IF_Type)
{
	g_eMMCDrv.u32_Flag &= ~FCIE_FLAG_PADTYPE_MASK;

	REG_FCIE_SETBIT(FCIE_BOOT_CONFIG, BIT1);

	REG_FCIE_CLRBIT(FCIE_BOOT_CONFIG,
			    BIT_MACRO_EN|BIT_SD_DDR_EN|BIT_SD_BYPASS_MODE_EN|BIT_SD_SDR_IN_BYPASS|BIT_SD_FROM_TMUX);

	switch(u32_FCIE_IF_Type){
		case FCIE_eMMC_DDR:
			eMMC_debug(eMMC_DEBUG_LEVEL_HIGH,1,"eMMC pads: DDR\n");

			REG_FCIE_SETBIT(reg_chiptop_0x43,
				BIT_PAD_EMMC_CLK_SRC|BIT_eMMC_RSTPIN_VAL);
			REG_FCIE_CLRBIT(reg_chiptop_0x43,
				BIT_EMPTY|BIT_eMMC_RSTPIN_EN|BIT_PAD_BYPASS_MACRO);

			// set DDR mode
			REG_FCIE_SETBIT(FCIE_BOOT_CONFIG, BIT_MACRO_EN|BIT_SD_DDR_EN);
			// set chiptop
			g_eMMCDrv.u32_Flag |= FCIE_FLAG_PADTYPE_DDR;
			break;

		case FCIE_eMMC_SDR:
            eMMC_debug(eMMC_DEBUG_LEVEL_HIGH,1,"eMMC pads: SDR\n");

			REG_FCIE_SETBIT(reg_chiptop_0x43,
				BIT_PAD_EMMC_CLK_SRC|BIT_eMMC_RSTPIN_VAL);
			REG_FCIE_CLRBIT(reg_chiptop_0x43,
				BIT_EMPTY|BIT_eMMC_RSTPIN_EN|BIT_PAD_BYPASS_MACRO);

			// set SDR mode
			REG_FCIE_SETBIT(FCIE_BOOT_CONFIG, BIT_MACRO_EN);
			g_eMMCDrv.u32_Flag |= FCIE_FLAG_PADTYPE_SDR;
			break;

		case FCIE_eMMC_BYPASS:
			eMMC_debug(eMMC_DEBUG_LEVEL_HIGH,1,"eMMC pads: BYPASS\n");

			REG_FCIE_SETBIT(reg_chiptop_0x43,
				BIT_PAD_EMMC_CLK_SRC|BIT_eMMC_RSTPIN_VAL|BIT_PAD_BYPASS_MACRO);
			REG_FCIE_CLRBIT(reg_chiptop_0x43,
				BIT_EMPTY|BIT_eMMC_RSTPIN_EN);

			// set bypadd mode
			REG_FCIE_SETBIT(FCIE_BOOT_CONFIG,
			    BIT_MACRO_EN|BIT_SD_BYPASS_MODE_EN|BIT_SD_SDR_IN_BYPASS);
			g_eMMCDrv.u32_Flag |= FCIE_FLAG_PADTYPE_BYPASS;
			break;

		default:
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: unknown interface: %X\n",u32_FCIE_IF_Type);
			return eMMC_ST_ERR_INVALID_PARAM;
	}

	// set chiptop
	REG_FCIE_CLRBIT(reg_chiptop_0x5A, BIT0|BIT1|BIT2);
	REG_FCIE_CLRBIT(reg_chiptop_0x1F, BIT0|BIT1);
	REG_FCIE_CLRBIT(reg_chiptop_0x70, BIT2);
	REG_FCIE_CLRBIT(reg_chiptop_0x64, BIT0);
	REG_FCIE_CLRBIT(reg_chiptop_0x4F, BIT13|BIT14);
	REG_FCIE_CLRBIT(reg_chiptop_0x03, BIT6|BIT7);
	REG_FCIE_CLRBIT(reg_chiptop_0x51, BIT10|BIT11);
	REG_FCIE_CLRBIT(reg_chiptop_0x6F, BIT14|BIT15);

	REG_FCIE_CLRBIT(reg_chiptop_0x50, BIT_NAND_CS1_EN|BIT_ALL_PAD_IN);
	REG_FCIE_CLRBIT(reg_chiptop_0x0B, BIT_NAND_CS2_EN|BIT_NAND_CS3_EN|
		BIT_SD0_CFG|BIT_SD0_CFG2|BIT_SD1_CFG|BIT_SD1_CFG2|BIT_NAND_CFG);


	#if (MS_BOARD_TYPE_SEL == BD_MST142A_D01A_S_EAGLE) || \
        (MS_BOARD_TYPE_SEL == BD_MST028B_10AFX_EAGLE)
	    //defined(CONFIG_MSTAR_BD_MST028B_10AFX_EAGLE)
    // eMMC Mode1: 142A, 028B
    REG_FCIE_CLRBIT(reg_chiptop_0x5D, BIT_eMMC_CFG_MASK);
    REG_FCIE_SETBIT(reg_chiptop_0x5D, BIT_eMMC_CFG_MODE1);
	#else
    // eMMC Mode2: 152A ,147A, 038B
	REG_FCIE_SETBIT(reg_chiptop_0x5D, BIT_eMMC_CFG_MODE2);
    #endif

	REG_FCIE_SETBIT(FCIE_REG_2Dh, BIT_NEW_DESIGN_ENn);

	return eMMC_ST_SUCCESS;
}


U32 eMMC_clock_setting(U32 u32ClkParam)
{
	eMMC_PlatformResetPre();

	switch(u32ClkParam)	{
	case BIT_FCIE_CLK_300K:  g_eMMCDrv.u32_ClkKHz = 300;    break;
	case BIT_FCIE_CLK_20M:   g_eMMCDrv.u32_ClkKHz = 20000;  break;
    case BIT_FCIE_CLK_27M: g_eMMCDrv.u32_ClkKHz = 27000;  break;
	case BIT_FCIE_CLK_32M:   g_eMMCDrv.u32_ClkKHz = 32000; break;
    case BIT_FCIE_CLK_36M: g_eMMCDrv.u32_ClkKHz = 36000;  break;
	case BIT_FCIE_CLK_40M:   g_eMMCDrv.u32_ClkKHz = 40000; break;
    case BIT_FCIE_CLK_43_2M: g_eMMCDrv.u32_ClkKHz = 43200; break;
    case BIT_FCIE_CLK_48M:   g_eMMCDrv.u32_ClkKHz = 48000; break;
	default:
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh\n", eMMC_ST_ERR_INVALID_PARAM);
		return eMMC_ST_ERR_INVALID_PARAM;
	}

	REG_FCIE_CLRBIT(reg_ckg_fcie_1X, BIT_FCIE_CLK_Gate|BIT_FCIE_CLK_MASK);
	REG_FCIE_SETBIT(reg_ckg_fcie_1X, BIT_FCIE_CLK_SEL|(u32ClkParam<<BIT_FCIE_CLK_SHIFT));

	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 1, "clk:%uKHz, Param:%Xh, fcie_1X(%Xh):%Xh, fcie_4X(%Xh):%Xh\n",
		g_eMMCDrv.u32_ClkKHz, u32ClkParam,
		reg_ckg_fcie_1X, REG_FCIE_U16(reg_ckg_fcie_1X),
		reg_ckg_fcie_4X, REG_FCIE_U16(reg_ckg_fcie_4X));

    eMMC_PlatformResetPost();
	return eMMC_ST_SUCCESS;
}

#if 0

U32 eMMC_clock_gating(void)
{
	eMMC_PlatformResetPre();
	g_eMMCDrv.u32_ClkKHz = 0;
	REG_FCIE_W(reg_ckg_fcie_1X, BIT_FCIE_CLK_Gate);
	REG_FCIE_W(reg_ckg_fcie_4X, BIT_FCIE_CLK4X_Gate);
	REG_FCIE_CLRBIT(FCIE_SD_MODE, BIT_SD_CLK_EN);
	eMMC_PlatformResetPost();
	return eMMC_ST_SUCCESS;
}

#endif

U8 gau8_FCIEClkSel[eMMC_FCIE_VALID_CLK_CNT]={
	BIT_FCIE_CLK4X_48M,
	BIT_FCIE_CLK4X_40M,
	BIT_FCIE_CLK4X_36M,
	BIT_FCIE_CLK4X_27M,
	BIT_FCIE_CLK4X_20M,
};

#if defined(IF_DETECT_eMMC_DDR_TIMING) && IF_DETECT_eMMC_DDR_TIMING
static char *sgachar_string[]={"  2T","1.5T","2.5T","  0T"};

static U32 eMMC_FCIE_DetectDDRTiming_Ex(U8 u8_DQS, U8 u8_DelaySel)
{
	U32 u32_SectorAddr;
	eMMC_PNI_t *pPartInfo = (eMMC_PNI_t*)gau8_eMMC_PartInfoBuf;

	if(g_eMMCDrv.u32_Flag & FCIE_FLAG_GET_PART_INFO)
	    u32_SectorAddr = pPartInfo->u16_BlkPageCnt *
		             pPartInfo->u16_PageByteCnt *
		             eMMC_PBA2_DETECT_DDRT;
	else
		u32_SectorAddr = eMMC_DEFAULT_BLK_DETECT_DDRT;

	//eMMC_debug(0,1,"SectorAddr: %Xh\n", u32_SectorAddr);

	eMMC_debug(eMMC_DEBUG_LEVEL_HIGH,0,"\ndqs:%s[%Xh]  cell:%02Xh \n",
		sgachar_string[u8_DQS], u8_DQS, u8_DelaySel);

	eMMC_FCIE_SetDDRTimingReg(u8_DQS, u8_DelaySel);
    return eMMCTest_BlkWRC_ProbeDDR(u32_SectorAddr);
}

#define FCIE_DELAY_CELL_ts         700 // 0.7ns
static eMMC_FCIE_DDRT_WINDOW_t sg_DDRTWindow[2];

U32 eMMC_FCIE_DetectDDRTiming(void)
{
	U8  u8_dqs, u8_delay_sel, u8_i;
	U8  u8_dqs_prev=0xFF, u8_delay_sel_prev;
	U8  au8_DQSRegVal[4]={3,1,0,2}; // 0T, 1.5T, 2T, 2.5T
	U8  au8_DQS_10T[4]={0,15,20,25}; // 0T, 1.5T, 2T, 2.5T
	U8  u8_delay_Sel_max;
	U32 u32_ts;
	U32 u32_err;
	eMMC_FCIE_DDRT_WINDOW_t *pWindow = &sg_DDRTWindow[0];

	if(0 == (g_eMMCDrv.u32_Flag&FCIE_FLAG_DDR_MODE)){
		//eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC WARN: SDR mode can't detect DDR timing\n");
		u32_err = eMMC_FCIE_EnableDDRMode();
		if(eMMC_ST_SUCCESS != u32_err)
		{
		    printf("eMMC Error: set DDR IF fail: %X\n", u32_err);
		    return u32_err;
		}
	}
	g_eMMCDrv.u32_Flag |= FCIE_FLAG_DDR_TUNING; // just to turn off some log

	//--------------------------------------------------
	sg_DDRTWindow[0].u8_Cnt = 0;
	sg_DDRTWindow[0].aParam[0].u8_DQS = 0;
	sg_DDRTWindow[0].aParam[1].u8_DQS = 0;
    sg_DDRTWindow[1].u8_Cnt = 0;
	sg_DDRTWindow[1].aParam[0].u8_DQS = 0;
	sg_DDRTWindow[1].aParam[1].u8_DQS = 0;
	for(u8_i=1; u8_i <= BIT_DQS_MODE_MASK>>BIT_DQS_MDOE_SHIFT; u8_i++)
	{
		sg_DDRTWindow[0].au8_DQSValidCellCnt[u8_i]=0;
		sg_DDRTWindow[1].au8_DQSValidCellCnt[u8_i]=0;
	}

	//--------------------------------------------------
	// calculate delay_Sel_max
	u32_ts = 1000*1000*1000 / g_eMMCDrv.u32_ClkKHz;
	u32_ts >>= 2; // for 4X's 1T

    //--------------------------------------------------
    // no need to try DQS of no delay
	//for(u8_dqs=0; u8_dqs<=(BIT_DQS_MODE_MASK>>BIT_DQS_MDOE_SHIFT); u8_dqs++)
	for(u8_dqs=1; u8_dqs<=(BIT_DQS_MODE_MASK>>BIT_DQS_MDOE_SHIFT); u8_dqs++)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_HIGH,0,"\n---------------------------\n");

		if(u8_dqs < (BIT_DQS_MODE_MASK>>BIT_DQS_MDOE_SHIFT))
		    u8_delay_Sel_max =
		        (au8_DQS_10T[u8_dqs+1]-au8_DQS_10T[u8_dqs])
		        *u32_ts/(FCIE_DELAY_CELL_ts*10);
		else
			u8_delay_Sel_max = (BIT_DQS_DELAY_CELL_MASK>>BIT_DQS_DELAY_CELL_SHIFT);

		if(u8_delay_Sel_max > (BIT_DQS_DELAY_CELL_MASK>>BIT_DQS_DELAY_CELL_SHIFT))
		{
			eMMC_debug(eMMC_DEBUG_LEVEL_HIGH,0,"max delay cell: %u\n", u8_delay_Sel_max);
			eMMC_debug(eMMC_DEBUG_LEVEL_HIGH,0,"invalid, not try\n\n");
			continue;
		}
		else
			eMMC_debug(eMMC_DEBUG_LEVEL_HIGH,0,"max delay cell: %u\n\n", u8_delay_Sel_max);

		sg_DDRTWindow[0].au8_DQSTryCellCnt[u8_dqs] = u8_delay_Sel_max;
		sg_DDRTWindow[1].au8_DQSTryCellCnt[u8_dqs] = u8_delay_Sel_max;

		//for(u8_delay_sel=0; u8_delay_sel<=(BIT_DQS_DELAY_CELL_MASK>>BIT_DQS_DELAY_CELL_SHIFT); u8_delay_sel++)
		for(u8_delay_sel=0; u8_delay_sel<=u8_delay_Sel_max; u8_delay_sel++)
		{
			u32_err = eMMC_FCIE_DetectDDRTiming_Ex(au8_DQSRegVal[u8_dqs], u8_delay_sel);
			if(eMMC_ST_SUCCESS == u32_err)
			{
				eMMC_debug(eMMC_DEBUG_LEVEL_HIGH,0,"  PASS\n\n");
				pWindow->u8_Cnt++;
				if(0 == pWindow->aParam[0].u8_DQS) // save the window head
				{
					pWindow->aParam[0].u8_DQS = u8_dqs; // dqs uses index
					pWindow->aParam[0].u8_Cell = u8_delay_sel;
				}
				pWindow->au8_DQSValidCellCnt[u8_dqs]++;

				u8_dqs_prev = u8_dqs;
				u8_delay_sel_prev = u8_delay_sel;
			}
			else
			{   // save the window tail
				if(0xFF != u8_dqs_prev)
				{
					pWindow->aParam[1].u8_DQS = u8_dqs_prev; // dqs uses index
					pWindow->aParam[1].u8_Cell = u8_delay_sel_prev;
				}
				u8_dqs_prev = 0xFF;

				// discard & re-use the window having less PASS cnt
				pWindow =
				    (sg_DDRTWindow[0].u8_Cnt < sg_DDRTWindow[1].u8_Cnt) ?
				    &sg_DDRTWindow[0] : &sg_DDRTWindow[1];
				pWindow->u8_Cnt = 0;
				pWindow->aParam[0].u8_DQS = 0;
				for(u8_i=1; u8_i <= BIT_DQS_MODE_MASK>>BIT_DQS_MDOE_SHIFT; u8_i++)
					pWindow->au8_DQSValidCellCnt[u8_i]=0;
			}
		}
	}

	// for the case of last try is ok
	if(0xFF != u8_dqs_prev)
	{
		pWindow->aParam[1].u8_DQS = u8_dqs_prev; // dqs uses index
		pWindow->aParam[1].u8_Cell = u8_delay_sel_prev;
	}

	g_eMMCDrv.u32_Flag &= ~FCIE_FLAG_DDR_TUNING;

	eMMC_debug(eMMC_DEBUG_LEVEL_HIGH,0,"\n W0, Cnt:%Xh, [%Xh %Xh], [%Xh %Xh]\n",
		sg_DDRTWindow[0].u8_Cnt,
		sg_DDRTWindow[0].aParam[0].u8_DQS, sg_DDRTWindow[0].aParam[0].u8_Cell,
		sg_DDRTWindow[0].aParam[1].u8_DQS, sg_DDRTWindow[0].aParam[1].u8_Cell);
	for(u8_i=1; u8_i <= BIT_DQS_MODE_MASK>>BIT_DQS_MDOE_SHIFT; u8_i++)
		eMMC_debug(eMMC_DEBUG_LEVEL_HIGH,0,"DQSValidCellCnt[%u]:%u \n",
			u8_i, sg_DDRTWindow[0].au8_DQSValidCellCnt[u8_i]);

	eMMC_debug(eMMC_DEBUG_LEVEL_HIGH,0,"\n W1, Cnt:%Xh, [%Xh %Xh], [%Xh %Xh]\n",
		sg_DDRTWindow[1].u8_Cnt,
		sg_DDRTWindow[1].aParam[0].u8_DQS, sg_DDRTWindow[1].aParam[0].u8_Cell,
		sg_DDRTWindow[1].aParam[1].u8_DQS, sg_DDRTWindow[1].aParam[1].u8_Cell);
	for(u8_i=1; u8_i <= BIT_DQS_MODE_MASK>>BIT_DQS_MDOE_SHIFT; u8_i++)
		eMMC_debug(eMMC_DEBUG_LEVEL_HIGH,0,"DQSValidCellCnt[%u]:%u \n",
			u8_i, sg_DDRTWindow[1].au8_DQSValidCellCnt[u8_i]);

	if(sg_DDRTWindow[0].u8_Cnt || sg_DDRTWindow[1].u8_Cnt)
		return eMMC_ST_SUCCESS;
	else
		return eMMC_ST_ERR_NO_OK_DDR_PARAM;

}


U32 eMMC_FCIE_BuildDDRTimingTable(void)
{
	U8 au8_DQSRegVal[4]={3,1,0,2}; // 0T, 1.5T, 2T, 2.5T
	U8  u8_i, u8_ClkIdx, u8_SetIdx, u8_tmp, u8_DqsIdx, u8_CellBase;
	U32 u32_err, u32_ret=eMMC_ST_ERR_NO_OK_DDR_PARAM;
	eMMC_FCIE_DDRT_WINDOW_t *pWindow;

	memset((void*)&g_eMMCDrv.DDRTable, '\0', sizeof(g_eMMCDrv.DDRTable));
	u8_SetIdx = 0;

	for(u8_ClkIdx=0; u8_ClkIdx<eMMC_FCIE_VALID_CLK_CNT; u8_ClkIdx++)
	{

		eMMC_debug(eMMC_DEBUG_LEVEL,0,"=================================\n");
		eMMC_clock_setting(gau8_FCIEClkSel[u8_ClkIdx]);
		eMMC_debug(eMMC_DEBUG_LEVEL,0,"=================================\n");

		// ---------------------------
		// search and set the Windows
		u32_err = eMMC_FCIE_DetectDDRTiming();

		// ---------------------------
		// set the Table
		if(eMMC_ST_SUCCESS == u32_err)
		{
			#if 0
			// before 12MHz, should at least 2 clk is ok for DDR
			if(eMMC_FCIE_DDRT_SET_CNT-1 == u8_SetIdx &&
				BIT_FCIE_CLK_12M == gau8_FCIEClkSel[u8_ClkIdx])
				u32_ret = eMMC_ST_SUCCESS;
			#endif

			g_eMMCDrv.DDRTable.Set[u8_SetIdx].u8_Clk = gau8_FCIEClkSel[u8_ClkIdx];

			// ---------------------------
		 	// select Window
			pWindow = NULL;

			// pick up the Window of Cell=0 case
			if(sg_DDRTWindow[0].aParam[0].u8_DQS != sg_DDRTWindow[0].aParam[1].u8_DQS &&
			   sg_DDRTWindow[1].aParam[0].u8_DQS == sg_DDRTWindow[1].aParam[1].u8_DQS)
			   pWindow = &sg_DDRTWindow[0];
			else if(sg_DDRTWindow[0].aParam[0].u8_DQS == sg_DDRTWindow[0].aParam[1].u8_DQS &&
			   sg_DDRTWindow[1].aParam[0].u8_DQS != sg_DDRTWindow[1].aParam[1].u8_DQS)
			   pWindow = &sg_DDRTWindow[1];
			else if(sg_DDRTWindow[0].aParam[0].u8_DQS != sg_DDRTWindow[0].aParam[1].u8_DQS &&
			   sg_DDRTWindow[1].aParam[0].u8_DQS != sg_DDRTWindow[1].aParam[1].u8_DQS)
			   pWindow =
				    (sg_DDRTWindow[0].u8_Cnt > sg_DDRTWindow[1].u8_Cnt) ?
				    &sg_DDRTWindow[0] : &sg_DDRTWindow[1];

			// ---------------------------
			if(NULL != pWindow)
			{

				// pick up the DQS having max valid cell
				u8_tmp = 0;
				for(u8_i=1; u8_i <= BIT_DQS_MODE_MASK>>BIT_DQS_MDOE_SHIFT; u8_i++)
				{
					if(u8_tmp <= pWindow->au8_DQSValidCellCnt[u8_i]){
						u8_tmp = pWindow->au8_DQSValidCellCnt[u8_i];
						u8_DqsIdx = u8_i;
					}
				}
				if(0 != u8_DqsIdx) // do not use 0T, this should be always TRUE
				{
					if(pWindow->au8_DQSValidCellCnt[u8_DqsIdx-1] >= 3 &&
						pWindow->au8_DQSValidCellCnt[u8_DqsIdx] >= 3)
					{
						g_eMMCDrv.DDRTable.Set[u8_SetIdx].Param.u8_DQS = au8_DQSRegVal[u8_DqsIdx];
						g_eMMCDrv.DDRTable.Set[u8_SetIdx].Param.u8_Cell = 0; // nice
					}
					else
					{
						u8_tmp = (pWindow->au8_DQSValidCellCnt[u8_DqsIdx] +
							pWindow->au8_DQSValidCellCnt[u8_DqsIdx-1]) / 2;


						if(u8_tmp < pWindow->au8_DQSValidCellCnt[u8_DqsIdx-1])
						{
							g_eMMCDrv.DDRTable.Set[u8_SetIdx].Param.u8_DQS =
								au8_DQSRegVal[u8_DqsIdx-1];

							u8_CellBase = pWindow->au8_DQSTryCellCnt[u8_DqsIdx-1] - pWindow->au8_DQSValidCellCnt[u8_DqsIdx-1];
							g_eMMCDrv.DDRTable.Set[u8_SetIdx].Param.u8_Cell =
								u8_CellBase + pWindow->au8_DQSValidCellCnt[u8_DqsIdx-1] +
								pWindow->au8_DQSValidCellCnt[u8_DqsIdx] - u8_tmp;
						}
						else
						{   g_eMMCDrv.DDRTable.Set[u8_SetIdx].Param.u8_DQS =
								au8_DQSRegVal[u8_DqsIdx];
						    g_eMMCDrv.DDRTable.Set[u8_SetIdx].Param.u8_Cell =
								(pWindow->au8_DQSValidCellCnt[u8_DqsIdx-1] +
								pWindow->au8_DQSValidCellCnt[u8_DqsIdx]) / 2;
						}
					}
				}
			}

			// ---------------------------
            // or, pick up the Window of large PASS Cnt
			else //if(NULL == pWindow)
			{
			    pWindow =
				    (sg_DDRTWindow[0].u8_Cnt > sg_DDRTWindow[1].u8_Cnt) ?
				    &sg_DDRTWindow[0] : &sg_DDRTWindow[1];

				g_eMMCDrv.DDRTable.Set[u8_SetIdx].Param.u8_DQS = au8_DQSRegVal[pWindow->aParam[0].u8_DQS];
				g_eMMCDrv.DDRTable.Set[u8_SetIdx].Param.u8_Cell =
					(pWindow->aParam[0].u8_Cell + pWindow->aParam[1].u8_Cell)/2;
			}

			#if 0
			// ---------------------------
			// use 12M for Set.Min
			if(eMMC_FCIE_DDRT_SET_CNT-2 == u8_SetIdx)
				u8_ClkIdx = eMMC_FCIE_VALID_CLK_CNT-2;
			#else
			if(FCIE_SLOW_CLK == g_eMMCDrv.DDRTable.Set[u8_SetIdx].u8_Clk)
				g_eMMCDrv.DDRTable.u8_SetCnt = u8_SetIdx + 1;
			#endif

			u8_SetIdx++;
		}
	}

	// dump DDRT Set
	u8_tmp = eMMC_FCIE_VALID_CLK_CNT > eMMC_FCIE_DDRT_SET_CNT ?
	    eMMC_FCIE_DDRT_SET_CNT : eMMC_FCIE_VALID_CLK_CNT;
	u8_tmp = u8_tmp > g_eMMCDrv.DDRTable.u8_SetCnt ?
		g_eMMCDrv.DDRTable.u8_SetCnt : u8_tmp;

	eMMC_DumpDDRTTable();

	// ======================================================
	// CAUTION: expect 48MHz can have valid DDRT parameter
	if(g_eMMCDrv.DDRTable.Set[eMMC_DDRT_SET_MAX].u8_Clk == gau8_FCIEClkSel[0]
		&& 0 != g_eMMCDrv.DDRTable.u8_SetCnt)
		u32_ret = eMMC_ST_SUCCESS;
	// ======================================================

	// ---------------------------
	// save DDRT Table
	if(eMMC_ST_SUCCESS == u32_ret)
	{

		g_eMMCDrv.DDRTable.u32_ChkSum =
		    eMMC_ChkSum((U8*)&g_eMMCDrv.DDRTable, sizeof(g_eMMCDrv.DDRTable)-4);
		memcpy(gau8_eMMC_SectorBuf, (U8*)&g_eMMCDrv.DDRTable, sizeof(g_eMMCDrv.DDRTable));

		eMMC_FCIE_ApplyDDRTSet(eMMC_DDRT_SET_MAX);

		u32_err = eMMC_CMD24(eMMC_DDRTABLE_BLK_0, gau8_eMMC_SectorBuf);
	    u32_ret = eMMC_CMD24(eMMC_DDRTABLE_BLK_1, gau8_eMMC_SectorBuf);
	    if(eMMC_ST_SUCCESS!=u32_err && eMMC_ST_SUCCESS!=u32_ret)
	    {
		    eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC ERROR: %Xh %Xh\n",
			    u32_err, u32_ret);
		    return eMMC_ST_ERR_SAVE_DDRT_FAIL;
	    }
	}
	else
	{
		*(U32*)&gau8_eMMC_SectorBuf[0] = ~
		    eMMC_ChkSum((U8*)&g_eMMCDrv.DDRTable, sizeof(g_eMMCDrv.DDRTable));

		eMMC_FCIE_EnableSDRMode();
	}

	return u32_ret;
}

#endif // IF_DETECT_eMMC_DDR_TIMING


void eMMC_set_WatchDog(U8 u8_IfEnable)
{
	u8_IfEnable = u8_IfEnable;
	// do nothing
}

void eMMC_reset_WatchDog(void)
{
	// do nothing
}

#define MSTAR_MIU0_BUS_BASE                      0x40000000
#define MSTAR_MIU1_BUS_BASE                      0xA0000000
U32 eMMC_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt)
{
	u32_ByteCnt = u32_ByteCnt;
	#if 0
	flush_cache(u32_DMAAddr, u32_ByteCnt);
	#endif
	if(u32_DMAAddr < MSTAR_MIU1_BUS_BASE) // MIU0
	{
		REG_FCIE_CLRBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
	}
	else
	{	REG_FCIE_SETBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
		u32_DMAAddr -= MSTAR_MIU1_BUS_BASE;
	}
	return u32_DMAAddr;
}

void eMMC_Invalidate_data_cache_buffer(U32 u32_addr, S32 s32_size)
{
	u32_addr = u32_addr;
	s32_size = s32_size;
//	flush_cache(u32_addr, s32_size);
}

void eMMC_flush_miu_pipe(void)
{

}

void *eMMC_memset (void *str, int c, unsigned int len)
{
  register char *st = str;

  while (len-- > 0)
    *st++ = c;
  return str;
}

void *eMMC_memcpy (void *destaddr, void const *srcaddr, unsigned int len)
{
  char *dest = destaddr;
  char const *src = srcaddr;

  while (len-- > 0)
    *dest++ = *src++;
  return destaddr;
}

U32 eMMC_PlatformResetPre(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformResetPost(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformInit(void)
{
	eMMC_pads_switch(FCIE_eMMC_SDR);
	eMMC_clock_setting(FCIE_SLOWEST_CLK);

	return eMMC_ST_SUCCESS;
}

static U32 sgu32_MemGuard0 = 0xA55A;
eMMC_ALIGN0 eMMC_DRIVER g_eMMCDrv eMMC_ALIGN1;
static U32 sgu32_MemGuard1 = 0x1289;

eMMC_ALIGN0 U8 gau8_eMMC_SectorBuf[eMMC_SECTOR_BUF_16KB] eMMC_ALIGN1; // 512 bytes
eMMC_ALIGN0 U8 gau8_eMMC_PartInfoBuf[eMMC_SECTOR_512BYTE] eMMC_ALIGN1; // 512 bytes

U32 eMMC_CheckIfMemCorrupt(void)
{
	if(0xA55A != sgu32_MemGuard0 || 0x1289 != sgu32_MemGuard1)
		return eMMC_ST_ERR_MEM_CORRUPT;

	return eMMC_ST_SUCCESS;
}
#elif (defined(eMMC_DRV_EDISON_BOOTRAM)&&eMMC_DRV_EDISON_BOOTRAM)


U16 u16_reg_chiptop_0x10_val =0,u16_reg_chiptop_0x6E_val=0;

void eMMC_DumpPadClk(void)
{

}


U32 eMMC_clock_setting(U32 u32ClkParam)
{
	eMMC_PlatformResetPre();


	REG_FCIE_CLRBIT(reg_ckg_fcie_1X, BIT_FCIE_CLK_Gate|BIT_FCIE_CLK_MASK);
	REG_FCIE_SETBIT(reg_ckg_fcie_1X, BIT_FCIE_CLK_SEL|(u32ClkParam<<BIT_FCIE_CLK_SHIFT));

    eMMC_PlatformResetPost();
	return eMMC_ST_SUCCESS;

}


void eMMC_set_WatchDog(U8 u8_IfEnable)
{
	u8_IfEnable = u8_IfEnable;
	// do nothing
}

void eMMC_reset_WatchDog(void)
{
	// do nothing
}


U32 eMMC_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt)
{
	u32_ByteCnt = u32_ByteCnt;
	#if 0
	flush_cache(u32_DMAAddr, u32_ByteCnt);
	#endif
	if(u32_DMAAddr < CONFIG_MIU1_BUSADDR) // MIU0
	{
		REG_FCIE_CLRBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU0_BUSADDR);
	}
	else
	{	REG_FCIE_SETBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU1_BUSADDR);
	}

	return u32_DMAAddr;
}

void eMMC_Invalidate_data_cache_buffer(U32 u32_addr, S32 s32_size)
{
	u32_addr = u32_addr;
	s32_size = s32_size;
//	flush_cache(u32_addr, s32_size);
}

void eMMC_flush_miu_pipe(void)
{

}

void *eMMC_memset (void *str, int c, unsigned int len)
{
  register char *st = str;

  while (len-- > 0)
    *st++ = c;
  return str;
}

void *eMMC_memcpy (void *destaddr, void const *srcaddr, unsigned int len)
{
  char *dest = destaddr;
  char const *src = srcaddr;

  while (len-- > 0)
    *dest++ = *src++;
  return destaddr;
}

U32 eMMC_PlatformResetPre(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformResetPost(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformInit(void)
{
	eMMC_clock_setting(FCIE_SLOWEST_CLK);

	return eMMC_ST_SUCCESS;
}


//eMMC_ALIGN0 eMMC_DRIVER g_eMMCDrv eMMC_ALIGN1;



#elif (defined(eMMC_DRV_EIFFEL_BOOTRAM) && eMMC_DRV_EIFFEL_BOOTRAM)
void eMMC_DumpPadClk(void)
{

}

U32 eMMC_clock_setting(U32 u32ClkParam)
{
	eMMC_PlatformResetPre();

	REG_FCIE_CLRBIT(reg_ckg_fcie_1X, BIT_FCIE_CLK_Gate|BIT_FCIE_CLK_MASK);
	REG_FCIE_SETBIT(reg_ckg_fcie_1X, BIT_FCIE_CLK_SEL|(u32ClkParam<<BIT_FCIE_CLK_SHIFT));

    eMMC_PlatformResetPost();
	return eMMC_ST_SUCCESS;

}

void eMMC_set_WatchDog(U8 u8_IfEnable)
{
	u8_IfEnable = u8_IfEnable;
	// do nothing
}

void eMMC_reset_WatchDog(void)
{
	// do nothing
}


U32 eMMC_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt)
{
	u32_ByteCnt = u32_ByteCnt;

	#if 0
	flush_cache(u32_DMAAddr, u32_ByteCnt);
	#endif

	if(u32_DMAAddr < CONFIG_MIU1_BUSADDR) // MIU0
	{
		REG_FCIE_CLRBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU0_BUSADDR);
	}
	else
	{	REG_FCIE_SETBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU1_BUSADDR);
	}

    return u32_DMAAddr;
}

void eMMC_Invalidate_data_cache_buffer(U32 u32_addr, S32 s32_size)
{
	u32_addr = u32_addr;
	s32_size = s32_size;
//	flush_cache(u32_addr, s32_size);
}

void eMMC_flush_miu_pipe(void)
{

}

void *eMMC_memset (void *str, int c, unsigned int len)
{
  register char *st = str;

  while (len-- > 0)
    *st++ = c;
  return str;
}

void *eMMC_memcpy (void *destaddr, void const *srcaddr, unsigned int len)
{
  char *dest = destaddr;
  char const *src = srcaddr;

  while (len-- > 0)
    *dest++ = *src++;
  return destaddr;
}

U32 eMMC_PlatformResetPre(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformResetPost(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformInit(void)
{
	eMMC_clock_setting(FCIE_SLOWEST_CLK);

	return eMMC_ST_SUCCESS;
}


//eMMC_ALIGN0 eMMC_DRIVER g_eMMCDrv eMMC_ALIGN1;
//eMMC_ALIGN0 U8 gau8_eMMC_SectorBuf[eMMC_SECTOR_BUF_BYTECNT] eMMC_ALIGN1; // 512 bytes
//eMMC_ALIGN0 U8 gau8_eMMC_PartInfoBuf[eMMC_SECTOR_512BYTE] eMMC_ALIGN1; // 512 bytes




#elif (defined(eMMC_DRV_NIKE_BOOTRAM)&&eMMC_DRV_NIKE_BOOTRAM)
void eMMC_DumpPadClk(void)
{

}


U32 eMMC_clock_setting(U32 u32ClkParam)
{
	eMMC_PlatformResetPre();

	REG_FCIE_CLRBIT(reg_ckg_fcie, BIT_FCIE_CLK_Gate|BIT_FCIE_CLK_MASK);
	REG_FCIE_SETBIT(reg_ckg_fcie, u32ClkParam<<BIT_FCIE_CLK_SHIFT);
    REG_FCIE_SETBIT(reg_ckg_nfie_div4_en, BIT_FCIE_CLK_DIV4_EN);

    eMMC_PlatformResetPost();
	return eMMC_ST_SUCCESS;
}

void eMMC_set_WatchDog(U8 u8_IfEnable)
{
	u8_IfEnable = u8_IfEnable;
	// do nothing
}

void eMMC_reset_WatchDog(void)
{
	// do nothing
}

U32 eMMC_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt)
{
	u32_ByteCnt = u32_ByteCnt;
	#if 0
	flush_cache(u32_DMAAddr, u32_ByteCnt);
	#endif

	if(u32_DMAAddr < CONFIG_MIU1_BUSADDR) // MIU0
	{
		REG_FCIE_CLRBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU0_BUSADDR);
	}
	else
	{	REG_FCIE_SETBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU1_BUSADDR);
	}

	return u32_DMAAddr;
}

void eMMC_Invalidate_data_cache_buffer(U32 u32_addr, S32 s32_size)
{
	u32_addr = u32_addr;
	s32_size = s32_size;
//	flush_cache(u32_addr, s32_size);
}

void eMMC_flush_miu_pipe(void)
{

}

void *eMMC_memset (void *str, int c, unsigned int len)
{
  register char *st = str;

  while (len-- > 0)
    *st++ = c;
  return str;
}

void *eMMC_memcpy (void *destaddr, void const *srcaddr, unsigned int len)
{
  char *dest = destaddr;
  char const *src = srcaddr;

  while (len-- > 0)
    *dest++ = *src++;
  return destaddr;
}

U32 eMMC_PlatformResetPre(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformResetPost(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformInit(void)
{
	eMMC_clock_setting(FCIE_SLOWEST_CLK);

	return eMMC_ST_SUCCESS;
}

//eMMC_ALIGN0 eMMC_DRIVER g_eMMCDrv eMMC_ALIGN1;
//eMMC_ALIGN0 U8 gau8_eMMC_SectorBuf[eMMC_SECTOR_BUF_16KB] eMMC_ALIGN1; // 512 bytes
//eMMC_ALIGN0 U8 gau8_eMMC_PartInfoBuf[eMMC_SECTOR_512BYTE] eMMC_ALIGN1; // 512 bytes

#elif (defined(eMMC_DRV_MADISON_BOOTRAM)&&eMMC_DRV_MADISON_BOOTRAM)
void eMMC_DumpPadClk(void)
{

}


U32 eMMC_clock_setting(U32 u32ClkParam)
{
	eMMC_PlatformResetPre();
	REG_FCIE_CLRBIT(reg_ckg_nfie, BIT_XTAL_CLK_SEL);
	REG_FCIE_CLRBIT(reg_ckg_fcie, BIT_FCIE_CLK_Gate|BIT_FCIE_CLK_MASK);
	REG_FCIE_SETBIT(reg_ckg_fcie, u32ClkParam<<BIT_FCIE_CLK_SHIFT);
    REG_FCIE_SETBIT(reg_ckg_nfie_div4_en, BIT_FCIE_CLK_DIV4_EN);
	REG_FCIE_SETBIT(reg_ckg_nfie, BIT_XTAL_CLK_SEL);
    eMMC_PlatformResetPost();
	return eMMC_ST_SUCCESS;
}

void eMMC_set_WatchDog(U8 u8_IfEnable)
{
	u8_IfEnable = u8_IfEnable;
	// do nothing
}

void eMMC_reset_WatchDog(void)
{
	// do nothing
}

U32 eMMC_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt)
{
	u32_ByteCnt = u32_ByteCnt;
	#if 0
	flush_cache(u32_DMAAddr, u32_ByteCnt);
	#endif

	if(u32_DMAAddr < CONFIG_MIU1_BUSADDR) // MIU0
	{
		REG_FCIE_CLRBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU0_BUSADDR);
	}
	else
	{	REG_FCIE_SETBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU1_BUSADDR);
	}

	return u32_DMAAddr;
}

void eMMC_Invalidate_data_cache_buffer(U32 u32_addr, S32 s32_size)
{
	u32_addr = u32_addr;
	s32_size = s32_size;
//	flush_cache(u32_addr, s32_size);
}

void eMMC_flush_miu_pipe(void)
{

}

void *eMMC_memset (void *str, int c, unsigned int len)
{
  register char *st = str;

  while (len-- > 0)
    *st++ = c;
  return str;
}

void *eMMC_memcpy (void *destaddr, void const *srcaddr, unsigned int len)
{
  char *dest = destaddr;
  char const *src = srcaddr;

  while (len-- > 0)
    *dest++ = *src++;
  return destaddr;
}

U32 eMMC_PlatformResetPre(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformResetPost(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformInit(void)
{
	eMMC_clock_setting(FCIE_SLOWEST_CLK);

	return eMMC_ST_SUCCESS;
}

U32 eMMC_ROM_LoadImages_Addr(void)
{
	U32 u32_func_addr;
	u32_func_addr =(REG_FCIE(DEBUG_REG_SYS_L1)<<16) + REG_FCIE(DEBUG_REG_SYS_L2);

    return u32_func_addr;
}

//eMMC_ALIGN0 eMMC_DRIVER g_eMMCDrv eMMC_ALIGN1;
//eMMC_ALIGN0 U8 gau8_eMMC_SectorBuf[eMMC_SECTOR_BUF_16KB] eMMC_ALIGN1; // 512 bytes
//eMMC_ALIGN0 U8 gau8_eMMC_PartInfoBuf[eMMC_SECTOR_512BYTE] eMMC_ALIGN1; // 512 bytes

#elif (defined(eMMC_DRV_CLIPPERS_BOOTRAM)&&eMMC_DRV_CLIPPERS_BOOTRAM)
void eMMC_DumpPadClk(void)
{

}


U32 eMMC_clock_setting(U32 u32ClkParam)
{
	eMMC_PlatformResetPre();
	
	REG_FCIE_CLRBIT(reg_ckg_fcie, BIT_FCIE_CLK_Gate|BIT_FCIE_CLK_MASK);
	REG_FCIE_SETBIT(reg_ckg_fcie, u32ClkParam<<BIT_FCIE_CLK_SHIFT | BIT_FCIE_CLK_SRC_SEL);

    eMMC_PlatformResetPost();
	return eMMC_ST_SUCCESS;
}

void eMMC_set_WatchDog(U8 u8_IfEnable)
{
	u8_IfEnable = u8_IfEnable;
	// do nothing
}

void eMMC_reset_WatchDog(void)
{
	// do nothing
}

U32 eMMC_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt)
{
	u32_ByteCnt = u32_ByteCnt;
	#if 0
	flush_cache(u32_DMAAddr, u32_ByteCnt);
	#endif
	REG_FCIE_CLRBIT(FCIE_MMA_PRI_REG, BIT_MIU_SELECT_MASK);

	if(u32_DMAAddr < CONFIG_MIU1_BUSADDR) // MIU0
	{
		return (u32_DMAAddr - CONFIG_MIU0_BUSADDR);
	}
	else  // MIU1
	{
		REG_FCIE_SETBIT(FCIE_MMA_PRI_REG, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU1_BUSADDR);
	}

	return u32_DMAAddr;
}

void eMMC_Invalidate_data_cache_buffer(U32 u32_addr, S32 s32_size)
{
	u32_addr = u32_addr;
	s32_size = s32_size;
//	flush_cache(u32_addr, s32_size);
}

void eMMC_flush_miu_pipe(void)
{

}

void *eMMC_memset (void *str, int c, unsigned int len)
{
  register char *st = str;

  while (len-- > 0)
    *st++ = c;
  return str;
}

void *eMMC_memcpy (void *destaddr, void const *srcaddr, unsigned int len)
{
  char *dest = destaddr;
  char const *src = srcaddr;

  while (len-- > 0)
    *dest++ = *src++;
  return destaddr;
}

U32 eMMC_PlatformResetPre(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformResetPost(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformInit(void)
{
	eMMC_clock_setting(FCIE_SLOWEST_CLK);

	return eMMC_ST_SUCCESS;
}


//eMMC_ALIGN0 eMMC_DRIVER g_eMMCDrv eMMC_ALIGN1;
//eMMC_ALIGN0 U8 gau8_eMMC_SectorBuf[eMMC_SECTOR_BUF_16KB] eMMC_ALIGN1; // 512 bytes
//eMMC_ALIGN0 U8 gau8_eMMC_PartInfoBuf[eMMC_SECTOR_512BYTE] eMMC_ALIGN1; // 512 bytes
#elif (defined(eMMC_DRV_MIAMI_BOOTRAM)&&eMMC_DRV_MIAMI_BOOTRAM)
void eMMC_DumpPadClk(void)
{

}


U32 eMMC_clock_setting(U32 u32ClkParam)
{
	eMMC_PlatformResetPre();

	REG_FCIE_CLRBIT(reg_ckg_fcie, BIT_FCIE_CLK_Gate|BIT_FCIE_CLK_MASK|BIT_FCIE_CLK_SRC_SEL);

	if(u32ClkParam==BIT_FCIE_CLK_300K)
	{
		REG_FCIE_SETBIT(reg_ckg_fcie, u32ClkParam<<BIT_FCIE_CLK_SHIFT | BIT_FCIE_CLK_SRC_SEL);
	}
	else
	{
		REG_FCIE_SETBIT(reg_ckg_fcie, u32ClkParam<<BIT_FCIE_CLK_SHIFT);
	}

    eMMC_PlatformResetPost();
	return eMMC_ST_SUCCESS;
}

void eMMC_set_WatchDog(U8 u8_IfEnable)
{
	u8_IfEnable = u8_IfEnable;
	// do nothing
}

void eMMC_reset_WatchDog(void)
{
	// do nothing
}

U32 eMMC_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt)
{
	u32_ByteCnt = u32_ByteCnt;
	#if 0
	flush_cache(u32_DMAAddr, u32_ByteCnt);
	#endif

	// Need to set bank 0x1006 16 bits addr 0x7A bit9 on to make below code work,
	// otherwise, always DMA to MIU0

	REG_FCIE_CLRBIT(FCIE_MMA_PRI_REG, BIT_MIU_SELECT_MASK);

	if(u32_DMAAddr < CONFIG_MIU1_BUSADDR) // MIU0
	{
		return (u32_DMAAddr - CONFIG_MIU0_BUSADDR);
	}
	else // MIU1
	{
		REG_FCIE_SETBIT(FCIE_MMA_PRI_REG, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU1_BUSADDR);
	}
#if 0
	else if(u32_DMAAddr < CONFIG_MIU2_BUSADDR) // MIU1
	{
		REG_FCIE_SETBIT(FCIE_MMA_PRI_REG, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU1_BUSADDR);
	}
	else // MIU2
	{
		REG_FCIE_SETBIT(FCIE_MMA_PRI_REG, BIT_MIU2_SELECT);
		return (u32_DMAAddr - CONFIG_MIU2_BUSADDR);
	}
#endif

	return u32_DMAAddr;
}

void eMMC_Invalidate_data_cache_buffer(U32 u32_addr, S32 s32_size)
{
	u32_addr = u32_addr;
	s32_size = s32_size;
//	flush_cache(u32_addr, s32_size);
}

void eMMC_flush_miu_pipe(void)
{

}

void *eMMC_memset (void *str, int c, unsigned int len)
{
	register char *st = str;

	while (len-- > 0)
		*st++ = c;
	return str;
}

void *eMMC_memcpy (void *destaddr, void const *srcaddr, unsigned int len)
{
	char *dest = destaddr;
	char const *src = srcaddr;

	while (len-- > 0)
		*dest++ = *src++;
	return destaddr;
}

U32 eMMC_PlatformResetPre(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformResetPost(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformInit(void)
{
	eMMC_clock_setting(FCIE_SLOWEST_CLK);

	return eMMC_ST_SUCCESS;
}

//eMMC_ALIGN0 eMMC_DRIVER g_eMMCDrv eMMC_ALIGN1;
//eMMC_ALIGN0 U8 gau8_eMMC_SectorBuf[eMMC_SECTOR_BUF_16KB] eMMC_ALIGN1; // 512 bytes
//eMMC_ALIGN0 U8 gau8_eMMC_PartInfoBuf[eMMC_SECTOR_512BYTE] eMMC_ALIGN1; // 512 bytes


#elif (defined(eMMC_DRV_MONACO_BOOTRAM)&&eMMC_DRV_MONACO_BOOTRAM)
void eMMC_DumpPadClk(void)
{

}


U32 eMMC_clock_setting(U32 u32ClkParam)
{
	eMMC_PlatformResetPre();

	REG_FCIE_CLRBIT(reg_ckg_fcie, BIT_FCIE_CLK_Gate|BIT_FCIE_CLK_MASK|BIT_FCIE_CLK_SRC_SEL);

	if(u32ClkParam==BIT_FCIE_CLK_300K)
	{
		REG_FCIE_SETBIT(reg_ckg_fcie, u32ClkParam<<BIT_FCIE_CLK_SHIFT | BIT_FCIE_CLK_SRC_SEL);
	}
	else
	{
		REG_FCIE_SETBIT(reg_ckg_fcie, u32ClkParam<<BIT_FCIE_CLK_SHIFT);
	}

    eMMC_PlatformResetPost();
	return eMMC_ST_SUCCESS;
}

void eMMC_set_WatchDog(U8 u8_IfEnable)
{
	u8_IfEnable = u8_IfEnable;
	// do nothing
}

void eMMC_reset_WatchDog(void)
{
	// do nothing
}

U32 eMMC_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt)
{
	u32_ByteCnt = u32_ByteCnt;
	#if 0
	flush_cache(u32_DMAAddr, u32_ByteCnt);
	#endif

	// Need to set bank 0x1006 16 bits addr 0x7A bit9 on to make below code work,
	// otherwise, always DMA to MIU0

	REG_FCIE_CLRBIT(FCIE_MMA_PRI_REG, BIT_MIU_SELECT_MASK);

	if(u32_DMAAddr < CONFIG_MIU1_BUSADDR) // MIU0
	{
		return (u32_DMAAddr - CONFIG_MIU0_BUSADDR);
	}
	else if(u32_DMAAddr < CONFIG_MIU2_BUSADDR) // MIU1
	{
		REG_FCIE_SETBIT(FCIE_MMA_PRI_REG, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU1_BUSADDR);
	}
	else // MIU2
	{
		REG_FCIE_SETBIT(FCIE_MMA_PRI_REG, BIT_MIU2_SELECT);
		return (u32_DMAAddr - CONFIG_MIU2_BUSADDR);
	}

	return u32_DMAAddr;
}

void eMMC_Invalidate_data_cache_buffer(U32 u32_addr, S32 s32_size)
{
	u32_addr = u32_addr;
	s32_size = s32_size;
//	flush_cache(u32_addr, s32_size);
}

void eMMC_flush_miu_pipe(void)
{

}

void *eMMC_memset (void *str, int c, unsigned int len)
{
	register char *st = str;

	while (len-- > 0)
		*st++ = c;
	return str;
}

void *eMMC_memcpy (void *destaddr, void const *srcaddr, unsigned int len)
{
	char *dest = destaddr;
	char const *src = srcaddr;

	while (len-- > 0)
		*dest++ = *src++;
	return destaddr;
}

U32 eMMC_PlatformResetPre(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformResetPost(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformInit(void)
{
	eMMC_clock_setting(FCIE_SLOWEST_CLK);

	return eMMC_ST_SUCCESS;
}

//eMMC_ALIGN0 eMMC_DRIVER g_eMMCDrv eMMC_ALIGN1;
//eMMC_ALIGN0 U8 gau8_eMMC_SectorBuf[eMMC_SECTOR_BUF_16KB] eMMC_ALIGN1; // 512 bytes
//eMMC_ALIGN0 U8 gau8_eMMC_PartInfoBuf[eMMC_SECTOR_512BYTE] eMMC_ALIGN1; // 512 bytes

#elif (defined(eMMC_DRV_MUJI_BOOTRAM)&&eMMC_DRV_MUJI_BOOTRAM)
void eMMC_DumpPadClk(void)
{

}


U32 eMMC_clock_setting(U32 u32ClkParam)
{
	eMMC_PlatformResetPre();

	REG_FCIE_CLRBIT(reg_ckg_fcie, BIT_FCIE_CLK_Gate|BIT_FCIE_CLK_MASK|BIT_FCIE_CLK_SRC_SEL);

	if(u32ClkParam==BIT_FCIE_CLK_300K)
	{
		REG_FCIE_SETBIT(reg_ckg_fcie, u32ClkParam<<BIT_FCIE_CLK_SHIFT | BIT_FCIE_CLK_SRC_SEL);
	}
	else
	{
		REG_FCIE_SETBIT(reg_ckg_fcie, u32ClkParam<<BIT_FCIE_CLK_SHIFT);
	}

    eMMC_PlatformResetPost();
	return eMMC_ST_SUCCESS;
}

void eMMC_set_WatchDog(U8 u8_IfEnable)
{
	u8_IfEnable = u8_IfEnable;
	// do nothing
}

void eMMC_reset_WatchDog(void)
{
	// do nothing
}

U32 eMMC_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt)
{
	u32_ByteCnt = u32_ByteCnt;
	#if 0
	flush_cache(u32_DMAAddr, u32_ByteCnt);
	#endif

	// Need to set bank 0x1006 16 bits addr 0x7A bit9 on to make below code work,
	// otherwise, always DMA to MIU0

	REG_FCIE_CLRBIT(FCIE_MMA_PRI_REG, BIT_MIU_SELECT_MASK);

	if(u32_DMAAddr < CONFIG_MIU1_BUSADDR) // MIU0
	{
		return (u32_DMAAddr - CONFIG_MIU0_BUSADDR);
	}
	else if(u32_DMAAddr < CONFIG_MIU2_BUSADDR) // MIU1
	{
		REG_FCIE_SETBIT(FCIE_MMA_PRI_REG, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU1_BUSADDR);
	}
	else // MIU2
	{
		REG_FCIE_SETBIT(FCIE_MMA_PRI_REG, BIT_MIU2_SELECT);
		return (u32_DMAAddr - CONFIG_MIU2_BUSADDR);
	}

	return u32_DMAAddr;
}

void eMMC_Invalidate_data_cache_buffer(U32 u32_addr, S32 s32_size)
{
	u32_addr = u32_addr;
	s32_size = s32_size;
//	flush_cache(u32_addr, s32_size);
}

void eMMC_flush_miu_pipe(void)
{

}

void *eMMC_memset (void *str, int c, unsigned int len)
{
	register char *st = str;

	while (len-- > 0)
		*st++ = c;
	return str;
}

void *eMMC_memcpy (void *destaddr, void const *srcaddr, unsigned int len)
{
	char *dest = destaddr;
	char const *src = srcaddr;

	while (len-- > 0)
		*dest++ = *src++;
	return destaddr;
}

U32 eMMC_PlatformResetPre(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformResetPost(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformInit(void)
{
	eMMC_clock_setting(FCIE_SLOWEST_CLK);

	return eMMC_ST_SUCCESS;
}

//eMMC_ALIGN0 eMMC_DRIVER g_eMMCDrv eMMC_ALIGN1;
//eMMC_ALIGN0 U8 gau8_eMMC_SectorBuf[eMMC_SECTOR_BUF_16KB] eMMC_ALIGN1; // 512 bytes
//eMMC_ALIGN0 U8 gau8_eMMC_PartInfoBuf[eMMC_SECTOR_512BYTE] eMMC_ALIGN1; // 512 bytes
#elif (defined(eMMC_DRV_CELTICS_BOOTRAM)&&eMMC_DRV_CELTICS_BOOTRAM)
void eMMC_DumpPadClk(void)
{

}


U32 eMMC_clock_setting(U32 u32ClkParam)
{
	eMMC_PlatformResetPre();

	REG_FCIE_CLRBIT(reg_ckg_fcie, BIT_FCIE_CLK_Gate|BIT_FCIE_CLK_MASK|BIT_FCIE_CLK_SRC_SEL);

	if(u32ClkParam==BIT_FCIE_CLK_300K)
	{
		REG_FCIE_SETBIT(reg_ckg_fcie, u32ClkParam<<BIT_FCIE_CLK_SHIFT | BIT_FCIE_CLK_SRC_SEL);
	}
	else
	{
		REG_FCIE_SETBIT(reg_ckg_fcie, u32ClkParam<<BIT_FCIE_CLK_SHIFT);
	}

    eMMC_PlatformResetPost();
	return eMMC_ST_SUCCESS;
}

void eMMC_set_WatchDog(U8 u8_IfEnable)
{
	u8_IfEnable = u8_IfEnable;
	// do nothing
}

void eMMC_reset_WatchDog(void)
{
	// do nothing
}

U32 eMMC_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt)
{
	u32_ByteCnt = u32_ByteCnt;
	#if 0
	flush_cache(u32_DMAAddr, u32_ByteCnt);
	#endif

	// Need to set bank 0x1006 16 bits addr 0x7A bit9 on to make below code work,
	// otherwise, always DMA to MIU0

	REG_FCIE_CLRBIT(FCIE_MMA_PRI_REG, BIT_MIU_SELECT_MASK);

	if(u32_DMAAddr < CONFIG_MIU1_BUSADDR) // MIU0
	{
		return (u32_DMAAddr - CONFIG_MIU0_BUSADDR);
	}
	else if(u32_DMAAddr < CONFIG_MIU2_BUSADDR) // MIU1
	{
		REG_FCIE_SETBIT(FCIE_MMA_PRI_REG, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU1_BUSADDR);
	}
	else // MIU2
	{
		REG_FCIE_SETBIT(FCIE_MMA_PRI_REG, BIT_MIU2_SELECT);
		return (u32_DMAAddr - CONFIG_MIU2_BUSADDR);
	}

	return u32_DMAAddr;
}

void eMMC_Invalidate_data_cache_buffer(U32 u32_addr, S32 s32_size)
{
	u32_addr = u32_addr;
	s32_size = s32_size;
//	flush_cache(u32_addr, s32_size);
}

void eMMC_flush_miu_pipe(void)
{

}

void *eMMC_memset (void *str, int c, unsigned int len)
{
	register char *st = str;

	while (len-- > 0)
		*st++ = c;
	return str;
}

void *eMMC_memcpy (void *destaddr, void const *srcaddr, unsigned int len)
{
	char *dest = destaddr;
	char const *src = srcaddr;

	while (len-- > 0)
		*dest++ = *src++;
	return destaddr;
}

U32 eMMC_PlatformResetPre(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformResetPost(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformInit(void)
{
	eMMC_clock_setting(FCIE_SLOWEST_CLK);

	return eMMC_ST_SUCCESS;
}

//eMMC_ALIGN0 eMMC_DRIVER g_eMMCDrv eMMC_ALIGN1;
//eMMC_ALIGN0 U8 gau8_eMMC_SectorBuf[eMMC_SECTOR_BUF_16KB] eMMC_ALIGN1; // 512 bytes
//eMMC_ALIGN0 U8 gau8_eMMC_PartInfoBuf[eMMC_SECTOR_512BYTE] eMMC_ALIGN1; // 512 bytes
#elif (defined(eMMC_DRV_NADAL_BOOTRAM)&&eMMC_DRV_NADAL_BOOTRAM)
void eMMC_DumpPadClk(void)
{

}


U32 eMMC_clock_setting(U32 u32ClkParam)
{
	eMMC_PlatformResetPre();

	REG_FCIE_CLRBIT(reg_ckg_fcie, BIT_FCIE_CLK_Gate|BIT_FCIE_CLK_MASK);
	REG_FCIE_SETBIT(reg_ckg_fcie, u32ClkParam<<BIT_FCIE_CLK_SHIFT);
    REG_FCIE_SETBIT(reg_ckg_nfie_div4_en, BIT_FCIE_CLK_DIV4_EN);

    eMMC_PlatformResetPost();
	return eMMC_ST_SUCCESS;
}

void eMMC_set_WatchDog(U8 u8_IfEnable)
{
	u8_IfEnable = u8_IfEnable;
	// do nothing
}

void eMMC_reset_WatchDog(void)
{
	// do nothing
}

U32 eMMC_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt)
{
	u32_ByteCnt = u32_ByteCnt;
	#if 0
	flush_cache(u32_DMAAddr, u32_ByteCnt);
	#endif

	if(u32_DMAAddr < CONFIG_MIU1_BUSADDR) // MIU0
	{
		REG_FCIE_CLRBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU0_BUSADDR);
	}
	else
	{	REG_FCIE_SETBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU1_BUSADDR);
	}

	return u32_DMAAddr;
}

void eMMC_Invalidate_data_cache_buffer(U32 u32_addr, S32 s32_size)
{
	u32_addr = u32_addr;
	s32_size = s32_size;
//	flush_cache(u32_addr, s32_size);
}

void eMMC_flush_miu_pipe(void)
{

}

void *eMMC_memset (void *str, int c, unsigned int len)
{
  register char *st = str;

  while (len-- > 0)
    *st++ = c;
  return str;
}

void *eMMC_memcpy (void *destaddr, void const *srcaddr, unsigned int len)
{
  char *dest = destaddr;
  char const *src = srcaddr;

  while (len-- > 0)
    *dest++ = *src++;
  return destaddr;
}

U32 eMMC_PlatformResetPre(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformResetPost(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformInit(void)
{
	eMMC_clock_setting(FCIE_SLOWEST_CLK);

	return eMMC_ST_SUCCESS;
}

//eMMC_ALIGN0 eMMC_DRIVER g_eMMCDrv eMMC_ALIGN1;
//eMMC_ALIGN0 U8 gau8_eMMC_SectorBuf[eMMC_SECTOR_BUF_16KB] eMMC_ALIGN1; // 512 bytes
//eMMC_ALIGN0 U8 gau8_eMMC_PartInfoBuf[eMMC_SECTOR_512BYTE] eMMC_ALIGN1; // 512 bytes

#elif (defined(eMMC_DRV_EINSTEIN_BOOTRAM)&&eMMC_DRV_EINSTEIN_BOOTRAM)
void eMMC_DumpPadClk(void)
{

}


U32 eMMC_clock_setting(U32 u32ClkParam)
{
	eMMC_PlatformResetPre();

	REG_FCIE_CLRBIT(reg_ckg_fcie, BIT_FCIE_CLK_Gate|BIT_FCIE_CLK_MASK);
	REG_FCIE_SETBIT(reg_ckg_fcie, u32ClkParam<<BIT_FCIE_CLK_SHIFT);


    eMMC_PlatformResetPost();
	return eMMC_ST_SUCCESS;
}

void eMMC_set_WatchDog(U8 u8_IfEnable)
{
	u8_IfEnable = u8_IfEnable;
	// do nothing
}

void eMMC_reset_WatchDog(void)
{
	// do nothing
}

U32 eMMC_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt)
{
	u32_ByteCnt = u32_ByteCnt;
	#if 0
	flush_cache(u32_DMAAddr, u32_ByteCnt);
	#endif

	if(u32_DMAAddr < CONFIG_MIU1_BUSADDR) // MIU0
	{
		REG_FCIE_CLRBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU0_BUSADDR);
	}
	else
	{	REG_FCIE_SETBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU1_BUSADDR);
	}

	return u32_DMAAddr;
}

void eMMC_Invalidate_data_cache_buffer(U32 u32_addr, S32 s32_size)
{
	u32_addr = u32_addr;
	s32_size = s32_size;
//	flush_cache(u32_addr, s32_size);
}

void eMMC_flush_miu_pipe(void)
{

}

void *eMMC_memset (void *str, int c, unsigned int len)
{
  register char *st = str;

  while (len-- > 0)
    *st++ = c;
  return str;
}

void *eMMC_memcpy (void *destaddr, void const *srcaddr, unsigned int len)
{
  char *dest = destaddr;
  char const *src = srcaddr;

  while (len-- > 0)
    *dest++ = *src++;
  return destaddr;
}

U32 eMMC_PlatformResetPre(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformResetPost(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformInit(void)
{
	eMMC_clock_setting(FCIE_SLOWEST_CLK);

	return eMMC_ST_SUCCESS;
}

//eMMC_ALIGN0 eMMC_DRIVER g_eMMCDrv eMMC_ALIGN1;
//eMMC_ALIGN0 U8 gau8_eMMC_SectorBuf[eMMC_SECTOR_BUF_16KB] eMMC_ALIGN1; // 512 bytes
//eMMC_ALIGN0 U8 gau8_eMMC_PartInfoBuf[eMMC_SECTOR_512BYTE] eMMC_ALIGN1; // 512 bytes

#elif (defined(eMMC_DRV_NAPOLI_BOOTRAM)&&eMMC_DRV_NAPOLI_BOOTRAM)
void eMMC_DumpPadClk(void)
{

}


U32 eMMC_clock_setting(U32 u32ClkParam)
{
	eMMC_PlatformResetPre();

	REG_FCIE_CLRBIT(reg_ckg_fcie, BIT_FCIE_CLK_Gate|BIT_FCIE_CLK_MASK);
	REG_FCIE_SETBIT(reg_ckg_fcie, BIT_FCIE_CLK_SRC_SEL|u32ClkParam<<BIT_FCIE_CLK_SHIFT);

    eMMC_PlatformResetPost();
	return eMMC_ST_SUCCESS;
}

void eMMC_set_WatchDog(U8 u8_IfEnable)
{
	u8_IfEnable = u8_IfEnable;
	// do nothing
}

void eMMC_reset_WatchDog(void)
{
	// do nothing
}

U32 eMMC_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt)
{
	u32_ByteCnt = u32_ByteCnt;
	#if 0
	flush_cache(u32_DMAAddr, u32_ByteCnt);
	#endif

	if(u32_DMAAddr < CONFIG_MIU1_BUSADDR) // MIU0
	{
		REG_FCIE_CLRBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU0_BUSADDR);
	}
	else
	{	REG_FCIE_SETBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU1_BUSADDR);
	}

	return u32_DMAAddr;
}

void eMMC_Invalidate_data_cache_buffer(U32 u32_addr, S32 s32_size)
{
	u32_addr = u32_addr;
	s32_size = s32_size;
//	flush_cache(u32_addr, s32_size);
}

void eMMC_flush_miu_pipe(void)
{

}

void *eMMC_memset (void *str, int c, unsigned int len)
{
  register char *st = str;

  while (len-- > 0)
    *st++ = c;
  return str;
}

void *eMMC_memcpy (void *destaddr, void const *srcaddr, unsigned int len)
{
  char *dest = destaddr;
  char const *src = srcaddr;

  while (len-- > 0)
    *dest++ = *src++;
  return destaddr;
}

U32 eMMC_PlatformResetPre(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformResetPost(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformInit(void)
{
	eMMC_clock_setting(FCIE_SLOWEST_CLK);

	return eMMC_ST_SUCCESS;
}

//eMMC_ALIGN0 eMMC_DRIVER g_eMMCDrv eMMC_ALIGN1;
//eMMC_ALIGN0 U8 gau8_eMMC_SectorBuf[eMMC_SECTOR_BUF_16KB] eMMC_ALIGN1; // 512 bytes
//eMMC_ALIGN0 U8 gau8_eMMC_PartInfoBuf[eMMC_SECTOR_512BYTE] eMMC_ALIGN1; // 512 bytes

#elif (defined(eMMC_DRV_EINSTEIN3_BOOTRAM)&&eMMC_DRV_EINSTEIN3_BOOTRAM)
void eMMC_DumpPadClk(void)
{

}


U32 eMMC_clock_setting(U32 u32ClkParam)
{
	eMMC_PlatformResetPre();

	REG_FCIE_CLRBIT(reg_ckg_fcie, BIT_FCIE_CLK_Gate|BIT_FCIE_CLK_MASK);
	REG_FCIE_SETBIT(reg_ckg_fcie, u32ClkParam<<BIT_FCIE_CLK_SHIFT);


    eMMC_PlatformResetPost();
	return eMMC_ST_SUCCESS;
}

void eMMC_set_WatchDog(U8 u8_IfEnable)
{
	u8_IfEnable = u8_IfEnable;
	// do nothing
}

void eMMC_reset_WatchDog(void)
{
	// do nothing
}

U32 eMMC_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt)
{
	u32_ByteCnt = u32_ByteCnt;
	#if 0
	flush_cache(u32_DMAAddr, u32_ByteCnt);
	#endif

	if(u32_DMAAddr < CONFIG_MIU1_BUSADDR) // MIU0
	{
		REG_FCIE_CLRBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU0_BUSADDR);
	}
	else
	{	REG_FCIE_SETBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
		return (u32_DMAAddr - CONFIG_MIU1_BUSADDR);
	}

	return u32_DMAAddr;
}

void eMMC_Invalidate_data_cache_buffer(U32 u32_addr, S32 s32_size)
{
	u32_addr = u32_addr;
	s32_size = s32_size;
//	flush_cache(u32_addr, s32_size);
}

void eMMC_flush_miu_pipe(void)
{

}

void *eMMC_memset (void *str, int c, unsigned int len)
{
  register char *st = str;

  while (len-- > 0)
    *st++ = c;
  return str;
}

void *eMMC_memcpy (void *destaddr, void const *srcaddr, unsigned int len)
{
  char *dest = destaddr;
  char const *src = srcaddr;

  while (len-- > 0)
    *dest++ = *src++;
  return destaddr;
}

U32 eMMC_PlatformResetPre(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformResetPost(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_PlatformInit(void)
{
	eMMC_clock_setting(FCIE_SLOWEST_CLK);

	return eMMC_ST_SUCCESS;
}

//eMMC_ALIGN0 eMMC_DRIVER g_eMMCDrv eMMC_ALIGN1;
//eMMC_ALIGN0 U8 gau8_eMMC_SectorBuf[eMMC_SECTOR_BUF_16KB] eMMC_ALIGN1; // 512 bytes
//eMMC_ALIGN0 U8 gau8_eMMC_PartInfoBuf[eMMC_SECTOR_512BYTE] eMMC_ALIGN1; // 512 bytes



#else
  #error "Error! no platform functions."
#endif
#endif
