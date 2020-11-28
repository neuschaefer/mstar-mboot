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

#include "eMMC.h"

#ifdef IP_FCIE_VERSION_5

#ifdef CONFIG_TSD
///////////////////////////////////////////////////////////////////////////////
// 32 bits field "card status" in R1/R1b(part of R6) response
///////////////////////////////////////////////////////////////////////////////

#define CS_BIT_OUT_OF_RANGE		1<<31
#define CS_BIT_ADDRESS_ERROR		1<<30
#define CS_BIT_BLOCK_LEN_ERROR		1<<29
#define CS_BIT_ERASE_SEQ_ERR		1<<28
#define CS_BIT_ERASE_PARAM		1<<27
#define CS_BIT_WP_VIOLATION		1<<26
#define CS_BIT_CARD_IS_LOCKED		1<<25
#define CS_BIT_LOCK_UNLOCK_FAILED	1<<24

#define CS_BIT_CMD_CRC_ERROR		1<<23
#define CS_BIT_ILLEGAL_COMMAND		1<<22
#define CS_BIT_CARD_ECC_FAILED		1<<21
#define CS_BIT_CARD_CONTROLLER_ERR	1<<20
#define CS_BIT_UNKNOW_ERROR		1<<19
//#define CS_BIT_RESERVED		1<<18
#define CS_BIT_DEFERRED_RSP		1<<17
#define CS_BIT_CSD_OVERWRITE		1<<16

#define CS_BIT_WP_ERASE_SKIP		1<<15
#define CS_BIT_CARD_ECC_DISABLED	1<<14
#define CS_BIT_ERASE_RESET		1<<13
#define CS_BITS_MSK_CURRENT_STATE	0xF<<9 // 12:9
#define CS_BIT_READY_FOR_DATA		1<<8

//#define CS_BIT_RESERVED		1<<7
//#define CS_BIT_RESERVED		1<<6
#define CS_BIT_APP_CMD			1<<5
#define CS_BIT_SDIO_CARD		1<<4
#define CS_BIT_AKE_SEQ_ERROR		1<<3
#define CS_BIT_RESERVED_4_APL_SPECIFIC	1<<2
#define CS_BIT_RESERVED_4_MANUF_TEST1	1<<1
#define CS_BIT_RESERVED_4_MANUF_TEST0	1<<0

///////////////////////////////////////////////////////////////////////////////

#define CMD08_CHECK_PATTERN         0xAA
#define CMD08_VOLTAGE_2P7_TO_3P6V   0x01

///////////////////////////////////////////////////////////////////////////////

U32 tSD_CheckCardStatus(U32 u32CardStatus)
{
	U32 u32CurrentState = (u32CardStatus & CS_BITS_MSK_CURRENT_STATE) >> 9;
	eMMC_debug(0,0,"card state: %d ", u32CurrentState);
	switch(u32CurrentState) {
		case 0:		eMMC_debug(0,0,"(idle)");	break;
		case 1:		eMMC_debug(0,0,"(ready)");	break;
		case 2:		eMMC_debug(0,0,"(ident)");	break;
		case 3:		eMMC_debug(0,0,"(stby)");	break;
		case 4:		eMMC_debug(0,0,"(tran)");	break;
		case 5:		eMMC_debug(0,0,"(data)");	break;
		case 6:		eMMC_debug(0,0,"(rcv)");	break;
		case 7:		eMMC_debug(0,0,"(prg)");	break;
		case 8:		eMMC_debug(0,0,"(dis)");	break;
		default:	eMMC_debug(0,0,"(?)");	break;
	}

	eMMC_debug(0,0,", ERR BITS [ ");
	if(u32CardStatus&CS_BIT_OUT_OF_RANGE)		eMMC_debug(0,0,"OUT_OF_RANGE ");
	if(u32CardStatus&CS_BIT_ADDRESS_ERROR)          eMMC_debug(0,0,"ADDRESS_ERROR ");
	if(u32CardStatus&CS_BIT_BLOCK_LEN_ERROR)        eMMC_debug(0,0,"BLOCK_LEN_ERROR ");
	if(u32CardStatus&CS_BIT_ERASE_SEQ_ERR)          eMMC_debug(0,0,"ERASE_SEQ_ERR ");
	if(u32CardStatus&CS_BIT_ERASE_PARAM)            eMMC_debug(0,0,"ERASE_PARAM ");
	if(u32CardStatus&CS_BIT_WP_VIOLATION)           eMMC_debug(0,0,"WP_VIOLATION ");
	if(u32CardStatus&CS_BIT_CARD_IS_LOCKED)         eMMC_debug(0,0,"CARD_IS_LOCKED ");
	if(u32CardStatus&CS_BIT_LOCK_UNLOCK_FAILED)     eMMC_debug(0,0,"LOCK_UNLOCK_FAILED ");

	if(u32CardStatus&CS_BIT_CMD_CRC_ERROR)          eMMC_debug(0,0,"CMD_CRC_ERROR ");
	if(u32CardStatus&CS_BIT_ILLEGAL_COMMAND)        eMMC_debug(0,0,"ILLEGAL_COMMAND ");
	if(u32CardStatus&CS_BIT_CARD_ECC_FAILED)        eMMC_debug(0,0,"CARD_ECC_FAILED ");
	if(u32CardStatus&CS_BIT_CARD_CONTROLLER_ERR)    eMMC_debug(0,0,"CARD_CONTROLLER_ERR ");
	if(u32CardStatus&CS_BIT_UNKNOW_ERROR)           eMMC_debug(0,0,"UNKNOW_ERROR ");
 	if(u32CardStatus&CS_BIT_CSD_OVERWRITE)          eMMC_debug(0,0,"CSD_OVERWRITE ");

	if(u32CardStatus&CS_BIT_WP_ERASE_SKIP)          eMMC_debug(0,0,"WP_ERASE_SKIP ");
	if(u32CardStatus&CS_BIT_CARD_ECC_DISABLED)      eMMC_debug(0,0,"CARD_ECC_DISABLED ");
	if(u32CardStatus&CS_BIT_ERASE_RESET)            eMMC_debug(0,0,"ERASE_RESET ");
	if(u32CardStatus&CS_BIT_READY_FOR_DATA)         eMMC_debug(0,0,"READY_FOR_DATA ");

	if(u32CardStatus&CS_BIT_APP_CMD)                eMMC_debug(0,0,"APP_CMD ");
	if(u32CardStatus&CS_BIT_AKE_SEQ_ERROR)          eMMC_debug(0,0,"AKE_SEQ_ERROR ");

	eMMC_debug(0,0,"]\n");

	return eMMC_ST_SUCCESS;

}

 U8 eMMC_FCIE_CmdRspBufGet(U8 u8addr)
{
    U32 u32Tmp;

    u32Tmp =REG_FCIE(FCIE_CMDFIFO_ADDR(u8addr>>1));

    if(u8addr&0x1)
    {
        return(u32Tmp>>8);
    }
    else
    {
        return(u32Tmp&0xFF);
    }

}
void eMMC_FCIE_GetCIFC(U16 u16_WordPos, U16 u16_WordCnt, U16 *pu16_Buf)
{
	U16 u16_i;


	for(u16_i=0; u16_i<u16_WordCnt; u16_i++)
		REG_FCIE_R(FCIE_CMDFIFO_ADDR(u16_i), pu16_Buf[u16_i]);

}


// CMD8 bcr R7 send interface condition
U32 tSD_CMD8(void)
{
	U32 u32_err = 0;
	U16 u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN, u16_reg;
	U32 u32_arg = (CMD08_VOLTAGE_2P7_TO_3P6V << 8) | CMD08_CHECK_PATTERN;

	eMMC_FCIE_ClearEvents();

	u32_err = eMMC_FCIE_SendCmd(g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, 8, eMMC_R1_BYTE_CNT);
	if(eMMC_ST_SUCCESS != u32_err) {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: CMD55 send CMD fail: %08Xh\n", u32_err);
		return u32_err;
	}

	REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
	if( u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR) ) {
		u32_err = eMMC_ST_ERR_CMD8_NO_RSP;
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: CMD55 Rsp err, Reg.12: %04Xh \n", u16_reg);
	}

	/*eMMC_debug(0,0,"\tR7(%d): %02X %02X %02X %02X\n",	eMMC_FCIE_CmdRspBufGet(0),
							eMMC_FCIE_CmdRspBufGet(1),
							eMMC_FCIE_CmdRspBufGet(2),
							eMMC_FCIE_CmdRspBufGet(3),
							eMMC_FCIE_CmdRspBufGet(4) );*/

	if( CMD08_CHECK_PATTERN!=eMMC_FCIE_CmdRspBufGet(4) || CMD08_VOLTAGE_2P7_TO_3P6V!=eMMC_FCIE_CmdRspBufGet(3)) {
		u32_err = eMMC_ST_ERR_CMD8_ECHO;
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: CMD8 Rsp err, Reg.12: %04Xh \n", u16_reg);
	}

	return u32_err;

}

// CMD55 ac R1 APP_CMD
U32 tSD_CMD55_AppCmd(U16 u16RelaCardAddr)
{
	U32 u32_err = 0;
	U16 u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN, u16_reg;
	U32 u32_arg = ((U32)u16RelaCardAddr) << 16;

	eMMC_FCIE_ClearEvents();

	u32_err = eMMC_FCIE_SendCmd(g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, 55, eMMC_R1_BYTE_CNT);
	if(eMMC_ST_SUCCESS != u32_err) {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: CMD55 send CMD fail: %08Xh\n", u32_err);
		return u32_err;
	}

	REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
	if( u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR) ) {
		u32_err = eMMC_ST_ERR_CMD55_NO_RSP;
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: CMD55 Rsp err, Reg.12: %04Xh \n", u16_reg);
	}

	/*eMMC_debug(0,0,"\tR1(%d): %02X %02X %02X %02X\n",	eMMC_FCIE_CmdRspBufGet(0),
							eMMC_FCIE_CmdRspBufGet(1),
							eMMC_FCIE_CmdRspBufGet(2),
							eMMC_FCIE_CmdRspBufGet(3),
							eMMC_FCIE_CmdRspBufGet(4) );*/

	if((eMMC_FCIE_CmdRspBufGet(4)&CS_BIT_APP_CMD)==0) { // add checking APP_CMD bit in R1

		u32_err = eMMC_ST_ERR_CMD55_APP_CMD_BIT;
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: CMD55 Rsp err, Reg.12: %04Xh \n", u16_reg);
	}

	return u32_err;
}

// ACMD41 bcr R3 send operation condition
U32 tSD_ACMD41(void)
{
	U32 u32_err, u32_arg;
	U16 u16_ctrl, u16_reg;

	//eMMC_debug(0,0,"[%s] L: %d --> %s()\n", __FILE__, __LINE__, __FUNCTION__);

	// (sector mode | byte mode) | (3.0|3.1|3.2|3.3|3.4 V)
	//u32_arg = BIT30 | (BIT23|BIT22|BIT21|BIT20|BIT19|BIT18|BIT17|BIT16|BIT15);

	//u32_arg = BIT30 | (BIT16|BIT15); // CCS(CardCapacityStatus) + 2.8V
	u32_arg = BIT30 | (BIT21|BIT20); // CCS(CardCapacityStatus) + 3.3V
	u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;


	u32_err = tSD_CMD55_AppCmd(g_eMMCDrv.u16_RCA); // RCA is 0 here
	if(eMMC_ST_SUCCESS != u32_err) {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: CMD1 send CMD fail: %08Xh \n", u32_err);
		return u32_err;
	}

	eMMC_FCIE_ClearEvents();

	u32_err = eMMC_FCIE_SendCmd(g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, 41, eMMC_R3_BYTE_CNT);
	if(eMMC_ST_SUCCESS != u32_err) {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: CMD1 send CMD fail: %08Xh \n", u32_err);
		return u32_err;
	}

	// check status
	REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
	// R3 has no CRC, so does not check BIT_SD_RSP_CRC_ERR
	if(u16_reg & BIT_SD_RSP_TIMEOUT) {
		u32_err = eMMC_ST_ERR_ACMD41_NO_RSP;
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: CMD41 no Rsp, Reg.12: %04Xh \n", u16_reg);
		return u32_err;
	} else {	// CMD1 ok, do things here
		eMMC_FCIE_GetCIFC(0, 3, (U16*)g_eMMCDrv.au8_Rsp);
		//eMMC_dump_mem(g_eMMCDrv.au8_Rsp, eMMC_R3_BYTE_CNT);

		//eMMC_debug(0,0,"ACMD41_R3: %02X %02X %02X %02X %02X\n", g_eMMCDrv.au8_Rsp[0], g_eMMCDrv.au8_Rsp[1], g_eMMCDrv.au8_Rsp[2], g_eMMCDrv.au8_Rsp[3], g_eMMCDrv.au8_Rsp[4]);
		if(0x40 & eMMC_FCIE_CmdRspBufGet(0)) eMMC_debug(0,0,"no response?\n");
		/*eMMC_debug(0,0,"\tR3(%d): %02X %02X %02X %02X\n",	eMMC_FCIE_CmdRspBufGet(0),
								eMMC_FCIE_CmdRspBufGet(1),
								eMMC_FCIE_CmdRspBufGet(2),
								eMMC_FCIE_CmdRspBufGet(3),
								eMMC_FCIE_CmdRspBufGet(4) );*/

		if(0 == (g_eMMCDrv.au8_Rsp[1] & 0x80))
			u32_err =  eMMC_ST_ERR_ACMD41_DEV_BUSY;
		else
		{
			g_eMMCDrv.u8_IfSectorMode = (g_eMMCDrv.au8_Rsp[1]&BIT6)>>6;
			/*if(g_eMMCDrv.u8_IfSectorMode) eMMC_debug(0,0,"SDHC\n");
			else eMMC_debug(0,0,"SDSC\n");*/
		}
	}

	return u32_err;

}

U32 tSD_WaitCardPowerUp(void)
{
	U16 u16_i;
	U32 u32_err;

	for(u16_i=0; u16_i<5000; u16_i++) { // max 10 sec

		//printf("wait ACMD41:%x\n", u16_i);
		
		u32_err = tSD_ACMD41();
		if(eMMC_ST_ERR_ACMD41_DEV_BUSY == u32_err) { // delay and polling again
			eMMC_hw_timer_sleep(2);
		} else {
			break; // fail or power up finish
		}
	}
	return u32_err;
}

#define tSD_R6_ERR_CMD_CRC	BIT23
#define tSD_R6_ERR_ILLEGLE_CMD	BIT22
#define tSD_R6_ERR_GENERAL_ERR	BIT19

// CMD3 bcr R6 send relative addr
U32 tSD_CMD3(void)
{
	U32 u32_err = 0;
	U16 u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN, u16_reg;
	//U32 u32R6 = 0;
	//U8 u8_cs;

	eMMC_FCIE_ClearEvents();

	u32_err = eMMC_FCIE_SendCmd(g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, 0, 3, eMMC_R1_BYTE_CNT); // R6
	if(eMMC_ST_SUCCESS != u32_err) {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: CMD3 send CMD fail: %08Xh\n", u32_err);
		return u32_err;
	}

	REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
	if( u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR) ) {
		u32_err = eMMC_ST_ERR_CMD55_NO_RSP;
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: CMD3 Rsp err, Reg.12: %04Xh \n", u16_reg);
	}

	/*eMMC_debug(0,0,"\tR6(%d): %02X %02X %02X %02X\n",	eMMC_FCIE_CmdRspBufGet(0),
							eMMC_FCIE_CmdRspBufGet(1),
							eMMC_FCIE_CmdRspBufGet(2),
							eMMC_FCIE_CmdRspBufGet(3),
							eMMC_FCIE_CmdRspBufGet(4) );*/

	g_eMMCDrv.u16_RCA = (eMMC_FCIE_CmdRspBufGet(1)<<8) | eMMC_FCIE_CmdRspBufGet(2);

	//eMMC_debug(0,0,"RCA: %04Xh\n", g_eMMCDrv.u16_RCA);

	/*u8_cs = (eMMC_FCIE_CmdRspBufGet(3) & (eMMC_R1_CURRENT_STATE>>8))>>1;
	eMMC_debug(0,0,"card state: %d ", u8_cs);
	switch(u8_cs) {
		case 0:		eMMC_debug(0,0,"(idle)\n");	break;
		case 1:		eMMC_debug(0,0,"(ready)\n");	break;
		case 2:		eMMC_debug(0,0,"(ident)\n");	break;
		case 3:		eMMC_debug(0,0,"(stby)\n");	break;
		case 4:		eMMC_debug(0,0,"(tran)\n");	break;
		case 5:		eMMC_debug(0,0,"(data)\n");	break;
		case 6:		eMMC_debug(0,0,"(rcv)\n");	break;
		case 7:		eMMC_debug(0,0,"(prg)\n");	break;
		case 8:		eMMC_debug(0,0,"(dis)\n");	break;
		default:	eMMC_debug(0,0,"(?)\n");	break;
	}*/

	// check error here...

	return u32_err;
}

typedef union _RSP_R2_CSD
{
    U8 BYTE[17];

    struct
    {
        U8  RESEV_3F;
        U8  CSD_STRUCT;
        U8  TAAC;
        U8  NSAC;
        U8  TRAN_SPEED; // 0x32 or 0x5A
        U8  CCC;
        U8  READ_BL_LEN; // include part of CCC
        U16 C_SIZE;
        U8  C_SIZE2;
        U16 C_SIZE_MULT;
        // . . .
        U8  CRC;
    } __attribute__ ((packed)) V_1P0;

    struct
    {
        U8  RESEV_3F;
        U8  CSD_STRUCT;
        U8  TAAC;
        U8  NSAC;
        U8  TRAN_SPEED; // the same as CSD v1.0
        U16 READ_BL_LEN;
        U32 C_SIZE; // need mask 0x003FFFFF
        // . . .
        U8  CRC;
    } __attribute__ ((packed)) V_2P0;

} RSP_R2_CSD; // CMD09 send CSD

#define U32BEND2LEND(X) ( ((X&0x000000FF)<<24) + ((X&0x0000FF00)<<8) + ((X&0x00FF0000)>>8) + ((X&0xFF000000)>>24) )
#define U16BEND2LEND(X) ( ((X&0x00FF)<<8) + ((X&0xFF00)>>8) )

// use CMD9 to get CSD & parsing for capacity
// CSD of SD has version 1.0 & 2.0
U32 tSD_CSD_Config(void)
{
	U32 u32_Error = 0;
	RSP_R2_CSD  CSD, * pCSD  = &CSD;
	U8 i;

	//eMMC_debug(0,0,"[%s] L: %d --> %s()\n", __FILE__, __LINE__, __FUNCTION__);

	u32_Error = eMMC_CMD9(g_eMMCDrv.u16_RCA);
	if(eMMC_ST_SUCCESS != u32_Error) goto ErrorHandle;

	for(i=0; i<16; i++) {
		pCSD->BYTE[i] = eMMC_FCIE_CmdRspBufGet(i);
	}

	if((pCSD->V_1P0.CSD_STRUCT&0xC0)==0x00)
	{
		pCSD->V_1P0.READ_BL_LEN = pCSD->V_1P0.READ_BL_LEN & 0x0F;
		pCSD->V_1P0.C_SIZE = ((U16BEND2LEND(pCSD->V_1P0.C_SIZE)&0x03FF)<<2) + (((U16)(pCSD->V_1P0.C_SIZE2&0xC0))>>6);
		pCSD->V_1P0.C_SIZE_MULT = (U16BEND2LEND(pCSD->V_1P0.C_SIZE_MULT)&0x0380) >> 7;
		/*DBG_SD_INIT(LOG_SD(L_INFO, "CSD 1.0\r\n"));
		DBG_SD_INIT(LOG_SD(L_INFO, "CSD.V_1P0.CSD_STRUCT    = 0x%02X\r\n", pCSD->V_1P0.CSD_STRUCT));
		DBG_SD_INIT(LOG_SD(L_INFO, "CSD.V_1P0.TAAC          = 0x%02X\r\n", pCSD->V_1P0.TAAC));
		DBG_SD_INIT(LOG_SD(L_INFO, "CSD.V_1P0.NSAC          = 0x%02X\r\n", pCSD->V_1P0.NSAC));
		DBG_SD_INIT(LOG_SD(L_INFO, "CSD.V_1P0.TRAN_SPEED    = 0x%02X\r\n", pCSD->V_1P0.TRAN_SPEED));
		DBG_SD_INIT(LOG_SD(L_INFO, "CSD.V_1P0.CCC           = 0x%02X\r\n", pCSD->V_1P0.CCC));
		DBG_SD_INIT(LOG_SD(L_INFO, "CSD.V_1P0.READ_BL_LEN   = 0x%02X\r\n", pCSD->V_1P0.READ_BL_LEN));*/
		//eMMC_debug(0,0,"CSD.V_1P0.C_SIZE        = 0x%04X\n", pCSD->V_1P0.C_SIZE);
		//eMMC_debug(0,0,"CSD.V_1P0.C_SIZE2       = 0x%02X\n", pCSD->V_1P0.C_SIZE2);
		//eMMC_debug(0,0,"CSD.V_1P0.C_SIZE_MULT   = 0x%04X\n", pCSD->V_1P0.C_SIZE_MULT);
	}
	else if((pCSD->V_1P0.CSD_STRUCT&0xC0)==0x40) // 2 bits
	{
		pCSD->V_2P0.C_SIZE = U32BEND2LEND(pCSD->V_2P0.C_SIZE)&0x003FFFFF; // 22 bits
		/*DBG_SD_INIT(LOG_SD(L_INFO, "CSD 2.0\r\n"));
		DBG_SD_INIT(LOG_SD(L_INFO, "CSD.V_2P0.CSD_STRUCT    = 0x%02X\r\n", pCSD->V_2P0.CSD_STRUCT));
		DBG_SD_INIT(LOG_SD(L_INFO, "CSD.V_2P0.TAAC          = 0x%02X ", pCSD->V_2P0.TAAC));
		if(pCSD->V_2P0.TAAC==0x0E) DBG_SD_INIT(LOG_SD(L_INFO, "R: 100ms, W: 250ms\r\n")); // P.109 / P.54
		else LOG_SD(L_ERROR, "Error!!! wrong info in CSD...\r\n");
		DBG_SD_INIT(LOG_SD(L_INFO, "CSD.V_2P0.NSAC          = 0x%02X\r\n", pCSD->V_2P0.NSAC));
		DBG_SD_INIT(LOG_SD(L_INFO, "CSD.V_2P0.TRAN_SPEED    = 0x%02X\r\n", pCSD->V_2P0.TRAN_SPEED));
		DBG_SD_INIT(LOG_SD(L_INFO, "CSD.V_2P0.READ_BL_LEN   = 0x%04X\r\n", pCSD->V_2P0.READ_BL_LEN));*/
		//eMMC_debug(0,0,"CSD.V_2P0.C_SIZE        = 0x%08X\n", pCSD->V_2P0.C_SIZE);
	}
	else
	{
		eMMC_debug(0,0,"Error!!! Wrong CSD_STRUCT = 0x%02X\r\n", pCSD->V_1P0.CSD_STRUCT&0xC0);
		/*LOG_SD(L_ERROR, "CSD:");
		for(i=0; i<CmdRspInfo.RspSize; i++)
		{
			LOG_SD(L_ERROR, "%02X ", pCSD->BYTE[i]);
		}
		LOG_SD(L_ERROR, "\r\n");
		IoStatus= IO_WRONG_CSD_STRUCT;*/
		u32_Error = eMMC_ST_ERR_CMD9_CSD_FMT;
		goto ErrorHandle;
	}

	if(g_eMMCDrv.u8_IfSectorMode) // SDHC
	{
		g_eMMCDrv.u32_SEC_COUNT = (CSD.V_2P0.C_SIZE+1) << 10; // to have sector number
	}
	else // standard capacity
	{
		g_eMMCDrv.u32_SEC_COUNT = ((U32)CSD.V_1P0.C_SIZE)+1;
		if(CSD.V_1P0.C_SIZE_MULT>7)
		{
			eMMC_debug(0,0,"Wrong CSD.V_1P0.C_SIZE_MULT\n");
			goto ErrorHandle;
		}
		g_eMMCDrv.u32_SEC_COUNT <<= ((U32)CSD.V_1P0.C_SIZE_MULT)+2;
		switch(CSD.V_1P0.READ_BL_LEN)
		{
		case  9: // x  512
			// do nothing
			break;
		case 10: // x 1024
			g_eMMCDrv.u32_SEC_COUNT <<= 1;
			break;
		case 11: // x 2048
			g_eMMCDrv.u32_SEC_COUNT <<= 2;
			break;
		default:
			eMMC_debug(0,0,"Wrong CSD.V_1P0.READ_BL_LEN\n");
			goto ErrorHandle;
			break;
		}
	}

	return u32_Error;

ErrorHandle:
	eMMC_debug(0,0,"[%s] L: %d --> %s() error...\n", __FILE__, __LINE__, __FUNCTION__);
	return u32_Error;
}

// ACMD6 ac R1 set bus width
U32 tSD_ACMD6(U32 u32Arg)
{
	U32 u32_err;
	U16 u16_ctrl, u16_reg;
	//U8 u8_cs;

	//eMMC_debug(0,0,"[%s] L: %d --> %s()\n", __FILE__, __LINE__, __FUNCTION__);

	u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;

	u32_err = tSD_CMD55_AppCmd(g_eMMCDrv.u16_RCA); // RCA is 0 here
	if(eMMC_ST_SUCCESS != u32_err) {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: ACMD6 send CMD55 fail: %08Xh \n", u32_err);
		return u32_err;
	}

	eMMC_FCIE_ClearEvents();

	u32_err = eMMC_FCIE_SendCmd(g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32Arg, 6, eMMC_R1_BYTE_CNT);
	if(eMMC_ST_SUCCESS != u32_err) {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: ACMD6 send fail: %08Xh \n", u32_err);
		return u32_err;
	}

	// check status
	REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
	//printf("acmd6:%x\n",u16_reg);
	// R3 has no CRC, so does not check BIT_SD_RSP_CRC_ERR
	if(u16_reg & BIT_SD_RSP_TIMEOUT) {
		u32_err = eMMC_ST_ERR_ACMD6_NO_RSP;
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: ACMD6 no Rsp, Reg.12: %04Xh \n", u16_reg);
		return u32_err;
	} else {
		eMMC_FCIE_GetCIFC(0, 3, (U16*)g_eMMCDrv.au8_Rsp);
		//eMMC_dump_mem(g_eMMCDrv.au8_Rsp, eMMC_R3_BYTE_CNT);

		//eMMC_debug(0,0,"ACMD41_R3: %02X %02X %02X %02X %02X\n", g_eMMCDrv.au8_Rsp[0], g_eMMCDrv.au8_Rsp[1], g_eMMCDrv.au8_Rsp[2], g_eMMCDrv.au8_Rsp[3], g_eMMCDrv.au8_Rsp[4]);
		if(0x40 & eMMC_FCIE_CmdRspBufGet(0)) eMMC_debug(0,0,"no response?\n");
		/*eMMC_debug(0,0,"\tR1(%d): %02X %02X %02X %02X\n",	eMMC_FCIE_CmdRspBufGet(0),
								eMMC_FCIE_CmdRspBufGet(1),
								eMMC_FCIE_CmdRspBufGet(2),
								eMMC_FCIE_CmdRspBufGet(3),
								eMMC_FCIE_CmdRspBufGet(4) );
		u8_cs = (eMMC_FCIE_CmdRspBufGet(3) & (eMMC_R1_CURRENT_STATE>>8))>>1;
		eMMC_debug(0,0,"card state: %d ", u8_cs);
		switch(u8_cs) {
			case 0:		eMMC_debug(0,0,"(idle)\n");	break;
			case 1:		eMMC_debug(0,0,"(ready)\n");	break;
			case 2:		eMMC_debug(0,0,"(ident)\n");	break;
			case 3:		eMMC_debug(0,0,"(stby)\n");	break;
			case 4:		eMMC_debug(0,0,"(tran)\n");	break;
			case 5:		eMMC_debug(0,0,"(data)\n");	break;
			case 6:		eMMC_debug(0,0,"(rcv)\n");	break;
			case 7:		eMMC_debug(0,0,"(prg)\n");	break;
			case 8:		eMMC_debug(0,0,"(dis)\n");	break;
			default:	eMMC_debug(0,0,"(?)\n");	break;
		}*/
	}

	return u32_err;
}

U32 tSD_SetBusCondition(U8 u8BusWidth)
{
	U32 u32_Error = 0;
	U32 u32Arg = 0;

	if(u8BusWidth==1) {
		u32Arg = 0;
	} else if(u8BusWidth==4) {
		u32Arg = 2;
	} else {
		u32_Error = eMMC_ST_ERR_ACMD6_WRONG_PARA;
		goto ErrorHandle;
	}

	u32_Error = tSD_ACMD6(u32Arg);
	if(eMMC_ST_SUCCESS != u32_Error) goto ErrorHandle;

	if(u8BusWidth==1) {
		g_eMMCDrv.u8_BUS_WIDTH = BIT_SD_DATA_WIDTH_1;
		g_eMMCDrv.u16_Reg10_Mode &= ~BIT_SD_DATA_WIDTH_4;
	} else if(u8BusWidth==4) {
		eMMC_debug(0,0,"set to 4 bits data bus\n");
		g_eMMCDrv.u8_BUS_WIDTH = BIT_SD_DATA_WIDTH_4;
		g_eMMCDrv.u16_Reg10_Mode |= BIT_SD_DATA_WIDTH_4;
	}
	return u32_Error;

ErrorHandle:

	eMMC_debug(0,0,"eMMC err: %s() error %08Xh\n", __FUNCTION__, u32_Error);
	return u32_Error;
}

U8   sd_status[64]	__attribute__((aligned(eMMC_CACHE_LINE)));

// ACMD13 adtc R1, to get sd status
U32 tSD_ACMD13(void)
{
	U32 u32_err;
	U16 u16_ctrl, u16_reg, u16_mode;
	//U8 i;
	U32 u32AU_SIZE = 0;
	U32 u32ERASE_SIZE = 0;
	U32 u32_dma_addr;
	//eMMC_debug(0,0,"[%s] L: %d --> %s()\n", __FILE__, __LINE__, __FUNCTION__);

	//u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN | BIT_SD_DAT_EN;
	u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN | BIT_SD_DTRX_EN;

	u32_err = tSD_CMD55_AppCmd(g_eMMCDrv.u16_RCA); // RCA is 0 here
	if(eMMC_ST_SUCCESS != u32_err) {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: ACM13 send CMD55 fail: %08Xh \n", u32_err);
		goto ErrorHandle;
	}

	eMMC_FCIE_ClearEvents();
	
	REG_FCIE_W(FCIE_JOB_BL_CNT, 1);
	REG_FCIE_W(FCIE_BLK_SIZE, 64); // 64 bytes tuning pattern
	
	u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)sd_status, 64);
	REG_FCIE_W(FCIE_MIU_DMA_ADDR_15_0, u32_dma_addr & 0xFFFF);
	REG_FCIE_W(FCIE_MIU_DMA_ADDR_31_16, u32_dma_addr >> 16);

	REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, 64 & 0xFFFF);
	REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16, 0 );



	u16_mode = g_eMMCDrv.u16_Reg10_Mode | g_eMMCDrv.u8_BUS_WIDTH;


	u32_err = eMMC_FCIE_SendCmd(u16_mode, u16_ctrl, 0, 13, eMMC_R1_BYTE_CNT);
	if(eMMC_ST_SUCCESS != u32_err) {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: ACMD13 send fail: %08Xh \n", u32_err);
		goto ErrorHandle;
	}

	u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT,BIT_DMA_END, TIME_WAIT_R_1_BLK_END);

	if(u32_err) {
		goto ErrorHandle;
	}

	// check status
	REG_FCIE_R(FCIE_SD_STATUS, u16_reg);

	if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR)) {
		u32_err = eMMC_ST_ERR_ACMD13_NO_RSP;
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: ACMD13 no Rsp, Reg.12: %04Xh \n", u16_reg);
		goto ErrorHandle;
	} else if(u16_reg &BIT_SD_R_CRC_ERR) {
		u32_err = eMMC_ST_ERR_ACMD13_DAT_CRC;
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: ACMD13 data CRC err, Reg.12: %04Xh \n", u16_reg);
		goto ErrorHandle;
	} else {
		eMMC_FCIE_GetCIFC(0, 3, (U16*)g_eMMCDrv.au8_Rsp);
		if(0x40 & eMMC_FCIE_CmdRspBufGet(0)) eMMC_debug(0,0,"no response?\n");

		/*eMMC_debug(0,0,"SD status:");
		for(i=0; i<64; i++) {
			if(i%16==0) eMMC_debug(0,0,"\n\t");
			eMMC_debug(0,0,"%02X ", eMMC_FCIE_DataFifoGet(i));
		}
		eMMC_debug(0,0,"\n");*/
		
		if((sd_status[0]&0xC0)==0x80) {
			eMMC_debug(0,0,"4 bits mode\n");
		} else if((sd_status[0]&0xC0)==0x00) {
			eMMC_debug(0,0,"1 bit mode\n");
		} else {
			eMMC_debug(0,0,"Other ? bit(s) mode\n");
		}

		u32AU_SIZE = sd_status[10] >> 4;
		u32ERASE_SIZE = (((U16)sd_status[11]) << 8) | sd_status[12];
		g_eMMCDrv.u8_EraseTimeout = sd_status[13] >> 2;

		/*eMMC_debug(0,0,"u8AU_SIZE = %d, ", u32AU_SIZE);
		eMMC_debug(0,0,"u16ERASE_SIZE = %d, ", u32ERASE_SIZE);
		eMMC_debug(0,0,"u8ERASE_TO = %d\n", g_eMMCDrv.u8_EraseTimeout);*/

		if( (u32AU_SIZE<1) || (u32AU_SIZE>9) ) eMMC_debug(0,0,"AU_SIZE not defined\n");
		else u32AU_SIZE = 0x10<<u32AU_SIZE; // AU_SIZE in sector unit
		if(!u32ERASE_SIZE) eMMC_debug(0,0,"Erase timeout calculation not supported\n");

		g_eMMCDrv.u32_EraseSize = u32AU_SIZE * u32ERASE_SIZE;

		//eMMC_debug(0,0,"Erase Unit Size: %08Xh ( %d KB)\n", g_eMMCDrv.u32_EraseSize, g_eMMCDrv.u32_EraseSize>>1);

	}

ErrorHandle:

	if(u32_err)
		eMMC_debug(0,0,"[%s] L: %d --> %s() error %08Xh\n", __FILE__, __LINE__, __FUNCTION__, u32_err);

	//REG_FCIE_W(FCIE_SDIO_CTRL, BIT_SDIO_BLK_MODE | eMMC_SECTOR_512BYTE); // restore anyway...

	return u32_err;
}
// ACMD51 adtc 8 byte R1, send SCR register
U32 tSD_ACMD51(void)
{
	U32 u32_err = 0;
	U16 u16_ctrl , u16_reg;
	U16 u16_mode;
	//U8 i;
	U32 u32_dma_addr;
	U8   buf[8]	__attribute__((aligned(eMMC_CACHE_LINE)));

	u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN | BIT_SD_DTRX_EN;

	u32_err = tSD_CMD55_AppCmd(g_eMMCDrv.u16_RCA); // RCA is 0 here
	if(eMMC_ST_SUCCESS != u32_err) {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: ACM51 send CMD55 fail: %08Xh \n", u32_err);
		goto ErrorHandle;
	}

	eMMC_FCIE_ClearEvents();

	REG_FCIE_W(FCIE_JOB_BL_CNT, 1);
	REG_FCIE_W(FCIE_BLK_SIZE, 8); // 64 bytes tuning pattern

	u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)buf, 8);
	REG_FCIE_W(FCIE_MIU_DMA_ADDR_15_0, u32_dma_addr & 0xFFFF);
	REG_FCIE_W(FCIE_MIU_DMA_ADDR_31_16, u32_dma_addr >> 16);

	REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, 8 & 0xFFFF);
	REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16, 0 );

	u16_mode =   g_eMMCDrv.u16_Reg10_Mode | g_eMMCDrv.u8_BUS_WIDTH;

	u32_err = eMMC_FCIE_SendCmd(u16_mode, u16_ctrl, 0, 51, eMMC_R1_BYTE_CNT);
	if(eMMC_ST_SUCCESS != u32_err) {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: ACM51 send CMD fail: %08Xh\n", u32_err);
		goto ErrorHandle;
	}

	u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT,BIT_DMA_END, TIME_WAIT_R_1_BLK_END);

	if(u32_err) {
		goto ErrorHandle;
	}

	// check status
	REG_FCIE_R(FCIE_SD_STATUS, u16_reg);

	if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR)) {

		u32_err = eMMC_ST_ERR_CMD6_NO_RSP;
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: ACM51 no Rsp, Reg.12: %04Xh \n", u16_reg);
		goto ErrorHandle;

	} else if(u16_reg &BIT_SD_R_CRC_ERR) {

		u32_err = eMMC_ST_ERR_CMD6_DAT_CRC;
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: ACM51 data CRC err, Reg.12: %04Xh \n", u16_reg);
		goto ErrorHandle;

	} else {

		/*eMMC_debug(0,0,"SCR:");
		for(i=0; i<8; i++) {
			if(i%16==0) eMMC_debug(0,0,"\n\t");
			eMMC_debug(0,0,"%02X ", eMMC_FCIE_DataFifoGet(i));
		}
		eMMC_debug(0,0,"\n");*/

		g_eMMCDrv.u8_ErasedMemContent = buf[1] >> 7;
		//eMMC_debug(0,0,"Data status after erase: %d\n", g_eMMCDrv.u8_ErasedMemContent);
	}

ErrorHandle:

//	REG_FCIE_W(FCIE_SDIO_CTRL, BIT_SDIO_BLK_MODE | eMMC_SECTOR_512BYTE); // restore anyway...

	if(u32_err)
		eMMC_debug(0,0,"[%s] L: %d --> %s() error %08Xh\n", __FILE__, __LINE__, __FUNCTION__, u32_err);

	return u32_err;

}
U8  cmd6buf[64]	__attribute__((aligned(eMMC_CACHE_LINE)));
// CMD6 adtc 64 bytes R1, switch function (high-speed...)
U32 tSD_CMD6(U32 u32Arg)
{
	U32 u32_err = 0;
	U16 u16_ctrl , u16_reg;
	U16 u16_mode;
	//U8 i;
	//U8   buf[8]	__attribute__((aligned(eMMC_CACHE_LINE)));
	U32 u32_dma_addr;
	//U16 u16mA;

//printf("cmd6........\n");
//eMMC_hw_timer_sleep(3000);
	//eMMC_debug(0,0,"%s(%08Xh)\n", __FUNCTION__, u32Arg);
	u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN | BIT_SD_DTRX_EN;

	eMMC_FCIE_ClearEvents();
	
	REG_FCIE_W(FCIE_JOB_BL_CNT, 1);
	REG_FCIE_W(FCIE_BLK_SIZE, 64); // 64 bytes tuning pattern

	u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)cmd6buf, 64);
	REG_FCIE_W(FCIE_MIU_DMA_ADDR_15_0, u32_dma_addr & 0xFFFF);
	REG_FCIE_W(FCIE_MIU_DMA_ADDR_31_16, u32_dma_addr >> 16);

	REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, 64 & 0xFFFF);
	REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16, 0 );

  //    printf("arg:%x\n",u32Arg);

	u16_mode =   g_eMMCDrv.u16_Reg10_Mode | g_eMMCDrv.u8_BUS_WIDTH;

	u32_err = eMMC_FCIE_SendCmd(u16_mode, u16_ctrl, u32Arg, 6, eMMC_R1_BYTE_CNT);
	if(eMMC_ST_SUCCESS != u32_err) {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: CMD55 send CMD fail: %08Xh\n", u32_err);
		goto ErrorHandle;
	}

	u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT,BIT_DMA_END, TIME_WAIT_R_1_BLK_END);
	if(u32_err) {
		goto ErrorHandle;
	}

	// check status
	REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
	if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR)) {

		u32_err = eMMC_ST_ERR_CMD6_NO_RSP;
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: CMD6 no Rsp, Reg.12: %04Xh \n", u16_reg);
		goto ErrorHandle;

	} else if(u16_reg &BIT_SD_R_CRC_ERR) {

		u32_err = eMMC_ST_ERR_CMD6_DAT_CRC;
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: CMD6 data CRC err, Reg.12: %04Xh \n", u16_reg);
		goto ErrorHandle;

	//}
	//else if (u16_reg&BIT_SD_CARD_BUSY)
	//{
		//u32_err=eMMC_ST_ERR_CMD6_SWC_STS_ERR;

	} else {

		/*u16mA = (((U16)eMMC_FCIE_DataFifoGet(0))<<8) + eMMC_FCIE_DataFifoGet(1);
		if(!u16mA)
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: switch status error\n");
		else
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "Max current consumption: %d mA\n", u16mA);
		eMMC_debug(0,0,"switch func status:");
		for(i=0; i<64; i++) {
			if(i%16==0) eMMC_debug(0,0,"\n\t");
			eMMC_debug(0,0,"%02X ", eMMC_FCIE_DataFifoGet(i));
		}
		eMMC_debug(0,0,"\n");*/
	}

ErrorHandle:

	//REG_FCIE_W(FCIE_SDIO_CTRL, BIT_SDIO_BLK_MODE | eMMC_SECTOR_512BYTE); // restore anyway...
	if(u32_err)
		eMMC_debug(0,0,"[%s] L: %d --> %s() error %08Xh\n", __FILE__, __LINE__, __FUNCTION__, u32_err);
	return u32_err;

}
U32 tSD_SetBusSpeed(U8 u8BusSpeed)
{
	U32 u32_Error = 0;
	int timeout;
	U32 *switch_status=0;
	
	if(u8BusSpeed!=eMMC_SPEED_HIGH) return eMMC_ST_ERR_CMD6_WRONG_PARA; // implement switch 2 high speed only

	//tSD_CMD6(0x00000000); // check nothing
	//tSD_CMD6(0x00FFFFFF); // check current selected
	//tSD_CMD6(0x001234E1); // check for fun, not every card feed back correct
//	u32_Error = tSD_CMD6(0x00fffff1); // check high speed access mode
//	if(u32_Error) goto ErrorHandle;
	//	u32_Error = tSD_CMD6(0x80000001); // check high speed access mode
	//	printk("u32_err:%x\n",u32_Error);
#if 1
	timeout = 4;
	while (timeout--) {
	///	err = sd_switch(mmc, SD_SWITCH_CHECK, 0, 1,	(u8 *)&switch_status);
		u32_Error = tSD_CMD6(0x00000001); // check high speed access mode
		printk("u32_err:%x\n",u32_Error);
		if (u32_Error) {
			printf("CMD6 check error\n");
			return u32_Error;
		}
		switch_status=(U32*)cmd6buf;

		/* The high-speed function is busy.  Try again */
		if (!(__be32_to_cpu(switch_status[7]) & SD_HIGHSPEED_BUSY))
			break;
		
	}
	if (__be32_to_cpu(switch_status[3]) & SD_HIGHSPEED_SUPPORTED)
	{
		printf("SDR25");
		u32_Error = tSD_CMD6(0x80000001); // switch

	}
	else
	{
		u32_Error = eMMC_ST_ERR_CMD6_HS_NOT_SRPO;
		printf("HS not support\n");
	
		goto ErrorHandle;

	}
#endif
	
#if 0
	
	u16mA = (((U16)cmd6buf[0])<<8) + cmd6buf[1];
	printf("13:%x\n",cmd6buf[13]);
	if( !(cmd6buf[13]&0x02) ) { // check bit 401
		u32_Error = eMMC_ST_ERR_CMD6_HS_NOT_SRPO;
		goto ErrorHandle;

	} else if(!u16mA) {

		u32_Error = eMMC_ST_ERR_CMD6_SWC_STS_ERR;
		goto ErrorHandle;

	} else if( (cmd6buf[16]&0x0F)!=0x01 ) {

		u32_Error = eMMC_ST_ERR_CMD6_SWC_STS_CODE;
		goto ErrorHandle;

	} else {
		u32_Error = tSD_CMD6(0x80fffff1); // switch
		//tSD_CMD6(0x00FFFFFF); // check again to confirm
	}
#endif
	return u32_Error;

ErrorHandle:

	eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: Not switch 2 high speed %08Xh\n", u32_Error);

	return u32_Error;
}

// CMD32 ac R1, erase block start
static U32 tSD_CMD32(U32 u32DataAddr)
{
	U32 u32_err = 0;
	U16 u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN, u16_reg;
	U32 u32_arg =  u32DataAddr << (g_eMMCDrv.u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);
	U32 u32CardStatus = 0;

	//eMMC_debug(0,0,"\t%s(%08Xh), ", __FUNCTION__, u32_arg);

	eMMC_FCIE_ClearEvents();

	u32_err = eMMC_FCIE_SendCmd(g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, 32, eMMC_R1_BYTE_CNT);
	if(eMMC_ST_SUCCESS != u32_err) {
		goto ErrorHandle;
	}

	REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
	if( u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR) ) {
		u32_err = eMMC_ST_ERR_CMD32_NO_RSP;
		goto ErrorHandle;
	}

	u32CardStatus = (((U32)eMMC_FCIE_CmdRspBufGet(1))<<24) | (((U32)eMMC_FCIE_CmdRspBufGet(2))<<16) |
			(((U32)eMMC_FCIE_CmdRspBufGet(3))<< 8) |  ((U32)eMMC_FCIE_CmdRspBufGet(4));

	//tSD_CheckCardStatus(u32CardStatus);

	if(u32CardStatus&CS_BIT_ERASE_SEQ_ERR) {

		u32_err = eMMC_ST_ERR_CMD32_SEQ_ERR;
		goto ErrorHandle;

	} else if(u32CardStatus&CS_BIT_ERASE_PARAM) {

		u32_err = eMMC_ST_ERR_CMD32_SEQ_ERR;
		goto ErrorHandle;

	} else if(u32CardStatus&CS_BIT_ERASE_RESET) {

		u32_err = eMMC_ST_ERR_CMD32_RESET;
		goto ErrorHandle;
	}

	return u32_err;

ErrorHandle:

	eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: %s() fail %08Xh\n", __FUNCTION__, u32_err);

	return u32_err;

}

// CMD33 ac R1, erase block end
static U32 tSD_CMD33(U32 u32DataAddr)
{
	U32 u32_err = 0;
	U16 u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN, u16_reg;
	U32 u32_arg =  u32DataAddr << (g_eMMCDrv.u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);
	U32 u32CardStatus = 0;

	//eMMC_debug(0,0,"\t%s(%08Xh), ", __FUNCTION__, u32_arg);

	eMMC_FCIE_ClearEvents();

	u32_err = eMMC_FCIE_SendCmd(g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, 33, eMMC_R1_BYTE_CNT);
	if(eMMC_ST_SUCCESS != u32_err) {
		goto ErrorHandle;
	}

	REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
	if( u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR) ) {
		u32_err = eMMC_ST_ERR_CMD33_NO_RSP;
		goto ErrorHandle;
	}

	u32CardStatus = (((U32)eMMC_FCIE_CmdRspBufGet(1))<<24) | (((U32)eMMC_FCIE_CmdRspBufGet(2))<<16) |
			(((U32)eMMC_FCIE_CmdRspBufGet(3))<< 8) |  ((U32)eMMC_FCIE_CmdRspBufGet(4));

	//tSD_CheckCardStatus(u32CardStatus);

	if(u32CardStatus&CS_BIT_ERASE_SEQ_ERR) {

		u32_err = eMMC_ST_ERR_CMD33_SEQ_ERR;
		goto ErrorHandle;

	} else if(u32CardStatus&CS_BIT_ERASE_PARAM) {

		u32_err = eMMC_ST_ERR_CMD33_SEQ_ERR;
		goto ErrorHandle;

	} else if(u32CardStatus&CS_BIT_ERASE_RESET) {

		u32_err = eMMC_ST_ERR_CMD33_RESET;
		goto ErrorHandle;
	}

	return u32_err;

ErrorHandle:

	eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: %s() fail %08Xh\n", __FUNCTION__, u32_err);

	return u32_err;

}

// CMD38 ac R1b, erase
// the erase size should be erase unit (if not, timeout might happen)
static U32 tSD_CMD38(void)
{
	U32 u32_err = 0;
	U16 u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN, u16_reg;
	U32 u32CardStatus = 0;

	//eMMC_debug(0,0,"\t%s(), ", __FUNCTION__);

	eMMC_FCIE_ClearEvents();

	u32_err = eMMC_FCIE_SendCmd(g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, 0, 38, eMMC_R1_BYTE_CNT);
	if(eMMC_ST_SUCCESS != u32_err) {
		goto ErrorHandle;
	}

	REG_FCIE_R(FCIE_SD_STATUS, u16_reg);
	if( u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR) ) {
		u32_err = eMMC_ST_ERR_CMD38_NO_RSP;
		goto ErrorHandle;
	}

	u32CardStatus = (((U32)eMMC_FCIE_CmdRspBufGet(1))<<24) | (((U32)eMMC_FCIE_CmdRspBufGet(2))<<16) |
			(((U32)eMMC_FCIE_CmdRspBufGet(3))<< 8) |  ((U32)eMMC_FCIE_CmdRspBufGet(4));

	//tSD_CheckCardStatus(u32CardStatus);

	if(u32CardStatus&CS_BIT_ERASE_SEQ_ERR) {

		u32_err = eMMC_ST_ERR_CMD38_SEQ_ERR;
		goto ErrorHandle;

	} else if(u32CardStatus&CS_BIT_ERASE_PARAM) {

		u32_err = eMMC_ST_ERR_CMD38_SEQ_ERR;
		goto ErrorHandle;

	} else if(u32CardStatus&CS_BIT_ERASE_RESET) {

		u32_err = eMMC_ST_ERR_CMD38_RESET;
		goto ErrorHandle;
	}

	if(eMMC_FCIE_WaitD0High( (g_eMMCDrv.u8_EraseTimeout)? (g_eMMCDrv.u8_EraseTimeout<<20) : 3000000)) { // use shift to give more tolerence

		u32_err = eMMC_ST_ERR_CMD38_TO;
	}

	return u32_err;

ErrorHandle:

	eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: %s() fail %08Xh\n", __FUNCTION__, u32_err);

	return u32_err;

}

U32 tSD_EraseCMDSeq(U32 u32StartSectorAddr, U32 u32EndSectorAddr)
{
	U32 u32_Error = 0;
	U32 u32_SectrorTotal = u32EndSectorAddr - u32StartSectorAddr + 1;
	U32 u32_Sector2Erase = 0;
	U32 u32_SectorAddr1 = u32StartSectorAddr, u32_SectorAddr2 = 0;

	//eMMC_debug(0,0,"!!!Erase Unit: %Xh\n", g_eMMCDrv.u32_EraseSize);

	eMMC_debug(0,0,"tSD_EraseCMDSeq(%Xh, %Xh)\n", u32StartSectorAddr, u32EndSectorAddr);

	//eMMC_debug(0,0,"1. u32_SectrorTotal = %Xh, Erase Unit: %Xh\n", u32_SectrorTotal, g_eMMCDrv.u32_EraseSize);

	do {
		if( u32_SectrorTotal > g_eMMCDrv.u32_EraseSize) {
			//eMMC_debug(0,0,"over than erase unit\n");
			u32_Sector2Erase = g_eMMCDrv.u32_EraseSize;
			u32_SectorAddr2 = u32_SectorAddr1 + g_eMMCDrv.u32_EraseSize - 1;
		} else {
			//eMMC_debug(0,0,"redudant\n");
			u32_Sector2Erase = u32_SectrorTotal;
			u32_SectorAddr2 = u32EndSectorAddr;
		}

		eMMC_debug(0,0,"\33[1;31m\tErase: ( %Xh ~ %Xh )\33[m\n", u32_SectorAddr1, u32_SectorAddr2);

		u32_Error = tSD_CMD32(u32_SectorAddr1);
		if(u32_Error) {
			goto ErrorHandle;
		}

		u32_Error = tSD_CMD33(u32_SectorAddr2);
		if(u32_Error) {
			goto ErrorHandle;
		}

		u32_Error = tSD_CMD38();
		if(u32_Error) {
			goto ErrorHandle;
		}

		//eMMC_debug(0,0,"2. u32_SectrorTotal = %Xh\n", u32_SectrorTotal);

		u32_SectrorTotal -= u32_Sector2Erase;
		u32_SectorAddr1	+= u32_Sector2Erase;;

		//eMMC_debug(0,0,"3. u32_SectrorTotal = %Xh\n", u32_SectrorTotal);

	} while(u32_SectrorTotal);

	return u32_Error;

ErrorHandle:

	eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: %s() fail %08Xh\n", __FUNCTION__, u32_Error);
	return u32_Error;

}

#endif // CONFIG_TSD

#endif 

