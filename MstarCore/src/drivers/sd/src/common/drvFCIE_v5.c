////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
#include <config.h>
#include "drvFCIE_config.h"

#ifdef SD_USE_FCIE5

#include "common.h"
#include "mmc.h"
#include "drvFCIE5.h"
//#include "eMMC_err_codes.h"

struct scatterlist {

	U32	u32_dma_addr;
	U32	u32_length;
};

struct kernel_like_mmc_data {

	unsigned int		sg_len;		/* size of scatter list */
	struct scatterlist	*sg;		/* I/O scatter list */
};

///////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct _ADMA_DESCRIPTOR
{
	U32 adma_end_flag   :1;
	U32 adma_miu_sel    :2;
	U32                 :13;    // reserve
	U32 adma_job_cnt    :16;
	U32 adma_miu_addr;
	U32 adma_length;
	U32 reserved;

} ADMA_DESCRIPTOR ;

#define SG_SEG_NUM 512

typedef struct _ADMA_INFO
{
    ADMA_DESCRIPTOR Descriptor[SG_SEG_NUM];
    //U32 const DescriptorAddr;
    U32 DescriptorAddr;

} ADMA_INFO ;

///////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_SCATTERLIST_COUNT 0x10

ADMA_INFO g_ADMAInfo __attribute__((aligned(0x80)));

U8 gu8SilenceTuning;
U32 gu32BestSkew4;

///////////////////////////////////////////////////////////////////////////////////////////////////


extern E_IO_STS HalFcie_WaitMieEvent(U16 u16ReqVal, U32 u32WaitMs);
extern void halFCIE_Platform_InitChiptop(void);
extern U32 SD_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt);
static U32 mstar_mci_prepare_descriptors(struct kernel_like_mmc_data * pData);
static void	mstar_mci_setup_descriptor_addr(CMD_RSP_INFO * pCmdRspInfo);
void HalFcie_SetIOVoltage(U8 u8Volt);



/**************************************
* Macro define
**************************************/
#define TIMEOUT_NORMAL 1000  // 1000ms
#define _halFCIE_ClearErrSts() do { \
    REG(FCIE_SD_STATUS) = (0x1f); \
} while(0)

//volatile U32 *_pu32CMD_RSP_BUF = (volatile U32 *)(CIF_C_ADDR);

#define DBGMMC(X)    //X



/**************************************
* Local Function
**************************************/
/*********************************************************************
*
*   PROCEDURE NAME:
*       _halFCIE_GetCIFC
*
*   DESCRIPTION:
*       Get CIFIFO byte value
*   NOTE:
*
*********************************************************************/
static void _halFCIE_SetupMiuBurstCtrl(void)
{
    #if 0
    #if (MIU_BURST_LEN == BYTES_8)
    // burst length = 8
    FCIE_RIU_W16(MMA_PRIORITY , R_MIU_BUS_CTRL_EN); // enable burst length control
    FCIE_RIU_16_OF(MMA_PRIORITY , WBIT09+WBIT08); // burst length = 8
    #elif (MIU_BURST_LEN == BYTES_16)
    // burst length = 16
    FCIE_RIU_W16(MMA_PRIORITY , R_MIU_BUS_CTRL_EN); // enable burst length control
    FCIE_RIU_16_ON(MMA_PRIORITY , WBIT08); // burst length = 16
    #elif (MIU_BURST_LEN == BYTES_32)
    // burst length = 32
    FCIE_RIU_W16(MMA_PRIORITY , R_MIU_BUS_CTRL_EN); // enable burst length control
    FCIE_RIU_16_ON(MMA_PRIORITY , WBIT09); // burst length = 32
    #endif
    #endif
}


/**************************************
* Global Function
**************************************/

/*********************************************************************
*
*   PROCEDURE NAME:
*       halFCIE_Init
*
*   DESCRIPTION:
*       Initial FCIE engine
*
*   NOTE:
*
*********************************************************************/
void halFCIE_Init(void)
{
	//printf("halfcie init\n");



	halFCIE_Platform_InitChiptop();

	// FCIE_RIU_W16(MIE_PATH_CTL, 0x0000);
	// FCIE_RIU_W16(MIE_EVENT   , 0xFFFF);
	FCIE_RIU_16_OF(REG_CLK_SDIO, BIT00);		//enable SD clk
	halFCIE_Platform_Reset_Fcie();

	// Set FCIE to bypass mode
	FCIE_RIU_16_OF(FCIE_MIE_FUNC_CTL, 3);		//clear SD_EN, EMMC_EN
	FCIE_RIU_16_ON(FCIE_MIE_FUNC_CTL, BIT_SDIO_MOD);
	FCIE_RIU_16_OF(FCIE_DDR_MODE, BIT07|WBIT08|WBIT12|WBIT13|WBIT14);

#ifdef _8BIT_MARCO
	FCIE_RIU_16_ON(FCIE_DDR_MODE,BIT07);
#endif

#ifdef SDR_MODE
	printf("sdr mode\n");
	FCIE_RIU_16_ON(FCIE_DDR_MODE, WBIT13|WBIT14);
#endif

	FCIE_RIU_16_OF(R_SDIO_PLL_0x68, BIT00|BIT01);

#ifdef _8BIT_MARCO
	FCIE_RIU_16_ON(R_SDIO_PLL_0x68, BIT00);			//enable EMMC func
	FCIE_RIU_16_OF(R_SDIO_PLL_0x6A, BIT00|BIT01);
	FCIE_RIU_16_ON(R_SDIO_PLL_0x6A, BIT00);				//IO BUS width=1
	FCIE_RIU_W16(R_SDIO_PLL_0x6B, 0x413);				//Page byte count
#endif

	FCIE_RIU_16_OF(reg_sdiopll_0x6d, BIT00);
	FCIE_RIU_16_ON(reg_sdiopll_0x6f, BIT00|BIT01);
	FCIE_RIU_16_OF(reg_sdiopll_0x70, WBIT08);
	FCIE_RIU_16_ON(reg_sdiopll_0x71, 0xffff);
	FCIE_RIU_16_ON(reg_sdiopll_0x73, 0xffff);
	FCIE_RIU_16_ON(reg_sdiopll_0x74, WBIT15);


    _halFCIE_SetupMiuBurstCtrl();

}

static U32 gu32Fcie5DebugBus[4];
static char *gStrDebugMode[] = {"CMD state",
								"FIFO status",
								"ADMA Address",
								"ADMA blk cnt"};

//1: CMDstate
//2: {FIFOsts, WRstate, RDstate}l
//3: ADMA Address
//4: ADMA block cnt

void HalFcie_DumpDebugBus(void)
{
	U32 u32_reg;
	U16 u16_i;

	printf("\n\n");
	printf("\n");

	REG_FCIE_CLRBIT(FCIE_EMMC_DEBUG_BUS1, BIT_DEBUG_MODE_MSK);
	REG_FCIE_SETBIT(FCIE_EMMC_DEBUG_BUS1, BIT_DEBUG_MODE_SET);

	for(u16_i=0; u16_i<4; u16_i++)
	{
		REG_FCIE_CLRBIT(FCIE_TEST_MODE, BIT_DEBUG_MODE_MASK);
		REG_FCIE_SETBIT(FCIE_TEST_MODE, (u16_i+1)<<BIT_DEBUG_MODE_SHIFT);

		printf("0x15 = %Xh, ", REG_FCIE(FCIE_TEST_MODE));
		REG_FCIE_R(FCIE_EMMC_DEBUG_BUS0, u32_reg);
		printf("0x38 = %Xh, ", u32_reg);
		gu32Fcie5DebugBus[u16_i] = u32_reg;

		REG_FCIE_R(FCIE_EMMC_DEBUG_BUS1, u32_reg);
		printf("0x39 = %Xh\n", u32_reg);
		gu32Fcie5DebugBus[u16_i] |= (u32_reg&0x00FF)<<16;
	}

	for(u16_i=0; u16_i<4; u16_i++)
	{
		printf("%s:\t %06Xh\n", gStrDebugMode[u16_i], gu32Fcie5DebugBus[u16_i]);
	}

	printf("\n");

}

void HalFcie_DumpRegisterBank(U32 u32Bank, U16 u16WordCount)
{
	U16 u16_i;
	volatile U16 u16_reg;

	for(u16_i=0 ; u16_i<u16WordCount; u16_i++)
	{
		if(0 == u16_i%8)
			printf("\n%02Xh:| ", u16_i);

		REG_FCIE_R(GET_REG_ADDR(u32Bank, u16_i), u16_reg);
		printf("%04Xh ", u16_reg);
	}
    printf("\n");
}

void HalFcie_DumpRegister(void)
{
	//U16 u16_i;

	printf("\n\nfcie reg:");
	HalFcie_DumpRegisterBank(FCIE_REG_BASE_ADDR, 0x40);

#if 0
	printk("FCIE JobCnt: \n");
	printk("JobCnt: %Xh \n", REG_FCIE(FCIE_JOB_BL_CNT));

	printk("\nFCIE CMDFIFO:");
	//eMMC_FCIE_GetCMDFIFO(0, 0x09, (U16*)sgau16_eMMCDebugReg);
	for(u16_i=0 ; u16_i<0x20; u16_i++)
	{
		if(0 == u16_i%8)
			printk("\n%02Xh:| ", u16_i);

		printk("%04Xh ", sgau16_eMMCDebugReg[u16_i]);
	}
#endif

    printf("\n\nchiptop reg:");
	HalFcie_DumpRegisterBank(PAD_CHIPTOP_BASE, 0x80);

    printf("\n\nsdio_pll reg:");
	HalFcie_DumpRegisterBank(SDIO_PLL_BASE, 0x80);

    printf("\n\nclockgen reg:");
	HalFcie_DumpRegisterBank(CLKGEN0_BASE, 0x80);


}


void halFCIE_OpenClock(U8 On_off)
{
    if (On_off)
        FCIE_RIU_16_ON(FCIE_SD_MODE, BIT_CLK_EN);
	else
		FCIE_RIU_16_OF(FCIE_SD_MODE, BIT_CLK_EN);
}

// total 17 bytes 0~16
U8 HalFcie_CmdFifoGet(U8 u8addr)
{
    U16 u16Tmp;

	if(u8addr>16) printf("SD Err: Cmd FIFO addr overflow in get %d\n", u8addr);

	//REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_CHK_CMD);

	u16Tmp = REG_FCIE(FCIE_CMDFIFO_ADDR(u8addr>>1));

	//REG_FCIE_CLRBIT(FCIE_SD_CTRL, BIT_CHK_CMD);

    if(u8addr&0x1)
    {
        return (U8)(u16Tmp>>8);
    }
    else
    {
        return (U8)(u16Tmp&0xFF);
    }
}


// total 17 bytes 0~16
void HalFcie_CmdFifoSet(U8 u8addr, U8 u8value)
{
    U16 u16Tmp;

	if(u8addr>16) printf("SD Err: Cmd FIFO addr overflow to set %d\n", u8addr);

	REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_CHK_CMD);

	u16Tmp = REG_FCIE(FCIE_CMDFIFO_ADDR(u8addr>>1));

    if(u8addr & 1)
    {
        u16Tmp = (u8value<<8) + (u16Tmp&0xFF);
    }
    else
    {
        u16Tmp = (u16Tmp&0xFF00)+u8value;
    }

	REG_FCIE_W(FCIE_CMDFIFO_ADDR(u8addr>>1), u16Tmp);

	REG_FCIE_CLRBIT(FCIE_SD_CTRL, BIT_CHK_CMD);

}

/*********************************************************************
*
*   PROCEDURE NAME:
*       halFCIE_EnableCardInf
*
*   DESCRIPTION:
*       Enable FCIE card interface
*   NOTE:
*
*********************************************************************/
void DrvFCIE_GetCMDFIFO( U16 u16_WordCnt, U16 *pu16_Buf)
{
	U16 u16_i;

	for(u16_i=0; u16_i<u16_WordCnt; u16_i++)
		REG_FCIE_R(FCIE_CMDFIFO_ADDR(u16_i), pu16_Buf[u16_i]);
}

/*static U8 _halFCIE_GetCIFC(U8 u8addr)
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
}*/

void HalFcie_ClearEvents(void)
{
	volatile U16 u16_reg;
	while(1){
		REG_FCIE_W(FCIE_MIE_EVENT, BIT_ALL_CARD_INT_EVENTS);
		REG_FCIE_R(FCIE_MIE_EVENT, u16_reg);
		if(0==(u16_reg&BIT_ALL_CARD_INT_EVENTS))
			break;
		REG_FCIE_W(FCIE_MIE_EVENT, 0);
		REG_FCIE_W(FCIE_MIE_EVENT, 0);
	}
	REG_FCIE_W1C(FCIE_SD_STATUS, BIT_SD_FCIE_ERR_FLAGS); // W1C
}


/*********************************************************************
*
*   PROCEDURE NAME:
*       halFCIE_SendCmdEx
*
*   DESCRIPTION:
*       Send command to card (for linux/uboot use)
*   NOTE:
*
*********************************************************************/

#if 0

int itune=0;

E_IO_STS halFCIE_SendCmdEx(CMD_RSP_INFO * pCmdRspInfo, U8 *rsp)
{
	E_IO_STS IoSts=IO_SUCCESS;
	U16 au16_tmp[3];
	U32 timeout = TIMEOUT_NORMAL;
	//U16 u16_WordCnt;//, u16tmp;
	//U32 u32_Arg;
	int i;
	U8   command;

	//    if((pCmdRspInfo->CmdRsp.Command[0]- 0x40) == MMC_CMD_ERASE) {
	//  timeout = *((U32 *)rsp);
	// }
	//_halFCIE_ClearErrSts();

	//halFCIE_EnableCardInf(R_SD_EN);

	//halFCIE_Platform_SetFcieClock(pCmdRspInfo->CardClock);

	//FCIE_RIU_16_ON(SD_MODE, R_SD_CLK_EN+R_SD_CS_EN+R_SD_DATSYNC);
	//  FCIE_RIU_16_ON(SD_MODE, R_SD_CLK_EN+R_SD_CS_EN);
	REG_FCIE_SETBIT(FCIE_SD_MODE, BIT_CLK_EN);

	//FCIE_RIU_16_OF(SDIO_CTL, R_SDIO_BLK_MOD); // Some cmd use byte mode

	//REG(CMD_SIZE) = pCmdRspInfo->CmdSize; // hardware generate the last CRC byte automatically

	// if( pCmdRspInfo->RspSize )
	//   REG(RSP_SIZE) = pCmdRspInfo->RspSize-1; // hardware check the last CRC byte automatically
	//  else
	//  REG(RSP_SIZE) = pCmdRspInfo->RspSize;
	REG_FCIE_CLRBIT(FCIE_CMD_RSP_SIZE, BIT_CMD_SIZE_MASK);
	REG_FCIE_SETBIT(FCIE_CMD_RSP_SIZE, ( pCmdRspInfo->CmdSize)<< BIT_CMD_SIZE_SHIFT);

	REG_FCIE_CLRBIT(FCIE_CMD_RSP_SIZE, BIT_RSP_SIZE_MASK);
	if( pCmdRspInfo->RspSize )
		REG_FCIE_SETBIT(FCIE_CMD_RSP_SIZE, (pCmdRspInfo->RspSize-1) & BIT_RSP_SIZE_MASK);
	else
		REG_FCIE_SETBIT(FCIE_CMD_RSP_SIZE, (pCmdRspInfo->RspSize) & BIT_RSP_SIZE_MASK);

	command = pCmdRspInfo->CmdRsp.Command[0];

	//printf("cmd :%x\n",command);
	//printf("cmd type :%x\n",pCmdRspInfo->CmdType);
	// fcie5
	//u32_Arg=pCmdRspInfo->Cmdarg;

	REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_CHK_CMD);

	REG_FCIE_W(FCIE_CMDFIFO_ADDR(0),((U16)(pCmdRspInfo->CmdRsp.Command[1])<<8) | (pCmdRspInfo->CmdRsp.Command[0]));
	REG_FCIE_W(FCIE_CMDFIFO_ADDR(1), ((U16)(pCmdRspInfo->CmdRsp.Command[3])<<8) | (pCmdRspInfo->CmdRsp.Command[2]));
	REG_FCIE_W(FCIE_CMDFIFO_ADDR(2),  ((U16)(pCmdRspInfo->CmdRsp.Command[5])<<8) | (pCmdRspInfo->CmdRsp.Command[4]));

	REG_FCIE_R(FCIE_CMDFIFO_ADDR(0),au16_tmp[0]);
	REG_FCIE_R(FCIE_CMDFIFO_ADDR(1),au16_tmp[1]);
	REG_FCIE_R(FCIE_CMDFIFO_ADDR(2),au16_tmp[2]);
	#if 0
	printf("CMDFIFO 0:%04X, ",au16_tmp[0]);
	printf("CMDFIFO 1:%04X, ",au16_tmp[1]);
	printf("CMDFIFO 2:%04X\n",au16_tmp[2]);
	#endif
	//	if(au16_tmp[0] == (((u32_Arg>>24)<<8) | (pCmdRspInfo->Command))&&
	//	au16_tmp[1] == ((u32_Arg&0xFF00) | ((u32_Arg>>16)&0xFF))&&
	//au16_tmp[2] == (u32_Arg&0xFF))
	//break;

	//FCIE_RIU_16_OF(FCIE_SD_CTRL, BIT_CHK_CMD); // clear command check for reading response value

	REG_FCIE_W(FCIE_SD_CTRL, 0); // clear first

	#if TEST_CMDNORESPONSE
		FCIE_RIU_16_ON(FCIE_SD_CTRL, BIT_ERR_DET_ON);
	#endif

    if(halFCIE_SDWaitD0High(timeout))
    {
        goto ErrorHandleEx;
    }

	REG_FCIE_CLRBIT(FCIE_SD_MODE, BIT_SD_DATA_CIFD);

	//REG_FCIE_W(FCIE_SD_CTRL, BIT_SD_CMD_EN | BIT_SD_RSP_EN |BIT_JOB_START);
    if(pCmdRspInfo->RspSize)
    {
		printf("send cmd with rsp\n");
        if(pCmdRspInfo->CmdType==CMD_TYPE_ADTC)
		{
			//REG_FCIE_W(FCIE_CMD_RSP_SIZE, 0x200);

			if(pCmdRspInfo->Dir == DAT_READ)
			{
				//  FCIE_RIU_16_OF(MMA_PRIORITY, R_JOB_RW_DIR); // set read direction
				//    REG(MIE_PATH_CTL) = R_SD_EN+R_MMA_ENABLE; // MIU start transfer when write.
				//REG(SD_CTL) = (R_SD_CMD_EN+R_SD_RSP_EN+R_SD_DTRX_EN);
				#if TEST_READCRCERR
					REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, (0x200+1) & 0xFFFF);
					REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16, 0);
					REG_FCIE_W(FCIE_BLK_SIZE, 0x200+1);
				#endif

				#if TEST_READSTOPCLOCK
					if (pCmdRspInfo->Command==0x51)
					{
						REG_FCIE_SETBIT(FCIE_RX_SHIFT_CNT, BIT_RSTOP_SHIFT_SEL);
						REG_FCIE_CLRBIT(FCIE_RX_SHIFT_CNT,0x0f);
						u16tmp=REG_FCIE(FCIE_RX_SHIFT_CNT);

						REG_FCIE_W(FCIE_RX_SHIFT_CNT,u16tmp|itune);
						printf("itune:%x  %x\n",itune,REG_FCIE(FCIE_RX_SHIFT_CNT));
						itune++;
						if (itune >=16) itune=0;
					}
				#endif

				#if TEST_RESPONSESHIFT
					if (pCmdRspInfo->Command==0x51)
					{
						REG_FCIE_SETBIT(FCIE_RSP_SHIFT_CNT, BIT_RSP_SHIFT_SEL);
						REG_FCIE_CLRBIT(FCIE_RSP_SHIFT_CNT,0x0f);
						u16tmp=REG_FCIE(FCIE_RSP_SHIFT_CNT);

						REG_FCIE_W(FCIE_RSP_SHIFT_CNT,u16tmp|itune);
						printf("response tune:%x  %x\n",itune,REG_FCIE(FCIE_RSP_SHIFT_CNT));
						itune++;
						if (itune >=16) itune=0;
					}

				#endif

				/* if (data->dma==R2N_MODE)
				{
				REG_FCIE_SETBIT(FCIE_SD_MODE, BIT_SD_DATA_CIFD);
				REG_FCIE_W(FCIE_SD_CTRL,  BIT_SD_DTRX_EN|BIT_SD_CMD_EN | BIT_SD_RSP_EN  |BIT_JOB_START);	//send command
				//send command

				}
				else if (data->dma==ADMA_MODE)
				REG_FCIE_W(FCIE_SD_CTRL, BIT_ADMA_EN|BIT_SD_CMD_EN | BIT_SD_RSP_EN |BIT_SD_DTRX_EN |BIT_JOB_START);
				else*/
				FCIE_RIU_16_ON(FCIE_SD_CTRL, BIT_SD_CMD_EN|BIT_SD_RSP_EN|BIT_SD_DTRX_EN|BIT_JOB_START);

			}
			else // write
			{
				//if (data->dma==R2N_MODE)
				//REG_FCIE_SETBIT(FCIE_SD_MODE, BIT_SD_DATA_CIFD);

				#if TEST_WRITECRCERR
					REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, (0x200-1) & 0xFFFF);
					REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16,0);
					REG_FCIE_W(FCIE_BLK_SIZE, 0x200-1);
				#endif

				//FCIE_RIU_16_ON(MMA_PRIORITY, R_JOB_RW_DIR); // set write direction
				//REG(MIE_PATH_CTL) = R_SD_EN+R_MMA_ENABLE; // MIU start transfer when write.
				//REG(SD_CTL) = (R_SD_CMD_EN+R_SD_RSP_EN);
				FCIE_RIU_16_ON(FCIE_SD_CTRL, BIT_SD_CMD_EN|BIT_SD_RSP_EN|BIT_JOB_START);
			}
        } // adtc
        else if(pCmdRspInfo->RspType==RSP_TYPE_R2)
        {
			// REG(SD_CTL) = (R_SD_CMD_EN+R_SD_RSP_EN+R_SD_RSPR2_EN);
			FCIE_RIU_16_ON(FCIE_SD_CTRL, BIT_SD_CMD_EN|BIT_SD_RSP_EN|BIT_SD_RSPR2_EN|BIT_JOB_START);
        }
        else
        {
			if(pCmdRspInfo->RspType==RSP_TYPE_R3)
			{
				FCIE_RIU_16_OF(FCIE_SD_CTRL, BIT_ERR_DET_ON); // R3 has no CRC, IP detect wrong error
			}
			#if TEST_RESPONSECRCERR
				REG_FCIE_SETBIT(FCIE_CMD_RSP_SIZE, (pCmdRspInfo->RspSize) & BIT_RSP_SIZE_MASK);
				FCIE_RIU_16_ON(FCIE_SD_CTRL, BIT_SD_CMD_EN|BIT_SD_RSP_EN|BIT_JOB_START);
			#else
				FCIE_RIU_16_ON(FCIE_SD_CTRL, BIT_SD_CMD_EN|BIT_SD_RSP_EN|BIT_JOB_START);
			#endif
			//REG(SD_CTL) = (R_SD_CMD_EN+R_SD_RSP_EN);
        }
    }
    else // no response need
    {
		printf("send cmd without rsp\n");
		FCIE_RIU_16_ON(FCIE_SD_CTRL, BIT_SD_CMD_EN|BIT_JOB_START);
    }

	//printf("sd ctl:%x\n",REG_FCIE(FCIE_SD_CTRL));
    IoSts = halFCIE_Platform_WaitMieEvent(BIT_SD_CMD_END, SD_TIMEOUT_VALUE);
    if(IoSts)
    {
        goto ErrorHandleEx;
    }

	if(pCmdRspInfo->CmdType!=CMD_TYPE_ADTC)
	    if(halFCIE_SDWaitD0High(timeout))
		{
			goto ErrorHandleEx;
		}
#if 0
    if(pCmdRspInfo->RspSize)
    {
        DBGMMC(printf("(RSP):%02X ", _halFCIE_GetCIFC(0)));
        for(i=1; i<pCmdRspInfo->RspSize-1; i++) // last CRC didn't copy to CIFC
        {
            rsp[i-1] = _halFCIE_GetCIFC(i);
            DBGMMC(printf("%02X ", rsp[i-1]));
        }
		DBGMMC(printf("\r\n"));
    }
#endif
    if(pCmdRspInfo->RspSize)
    {
        printf(", RSP(%d): ", pCmdRspInfo->RspSize);
		for(i=0; i<pCmdRspInfo->RspSize-1; i++) // last CRC didn't copy to CIFC
		{
			rsp[ (3-(i%4)) + ((i/4)<<2) ] = _halFCIE_GetCIFC((U8)(i+1));
			printf("%02X ", _halFCIE_GetCIFC(i));
		}
		printf("\r\n");
		/*
		u16_WordCnt=pCmdRspInfo->RspSize /4  + 1 ;
		for(i=0; i<u16_WordCnt; i+=4)
		{
			rsp[i+3]=_halFCIE_GetCIFC(1+i);
			rsp[i+2]=_halFCIE_GetCIFC(2+i);
			rsp[i+1]=_halFCIE_GetCIFC(3+i);
			rsp[i]=_halFCIE_GetCIFC(4+i);
			//REG_FCIE_R(FCIE_CMDFIFO_ADDR(u16_i), *(ppp+u16_i+1));
			//REG_FCIE_R(FCIE_CMDFIFO_ADDR(u16_i+1),*(ppp+u16_i));
		}
		*/
    }
	else
	{
		printf("\r\n");
	}

    return IoSts;

ErrorHandleEx:

    printf("send cmd fial 0x%02X!\r\n", IoSts);

    return IO_TIME_OUT;
}

#else

//#define PRINT_CMD_RSP

E_IO_STS HalFcie_SendCommand(CMD_RSP_INFO * pCmdRspInfo)
{
    E_IO_STS IoSts = IO_SUCCESS;
    U8 i;
	U16 u16_reg;
	U16 u16Index = 0;
	//U32 u32_err = eMMC_ST_SUCCESS;
	const U8 u8CmdSize = 5; // command always 6 bytes, exclude CRC is fix to 5
	U8 u8RspSize = 0;

#ifdef PRINT_CMD_RSP
	//printf("\r\n");
	//printf("\33[1;31mCMD%d_", 0xBF&pCmdRspInfo->Command.Cmd.Index);
	printf("CMD%d_", 0xBF&pCmdRspInfo->Command.Cmd.Index);
	printf("[%d] ", u8CmdSize);
    for(i=0; i<u8CmdSize; i++)
    {
        printf("%02X ", pCmdRspInfo->Command.Array[i]);
    }
#endif

	// setup response size from response type
	switch(pCmdRspInfo->RspType) {

		case RSP_TYPE_NO:
			//printf("no rsp\n");
			u8RspSize = 0;
			break;
		case RSP_TYPE_R2:
			//printf("rsp 16 bytes\n");
			u8RspSize = 16; // not include CRC byte
			break;
		default:
			//printf("rsp 5 bytes\n");
			u8RspSize = 5; // not include CRC byte
			break;
	}

	HalFcie_ClearEvents();

	//printf(("FCIE_MIE_EVENT = %04X\r\n", REG_FCIE(FCIE_MIE_EVENT));
    //HalFcie_EnableCardInf(R_SD_EN);
    //HalFcie_SetClock(pCmdRspInfo->CardClock);

    REG_FCIE_SETBIT(FCIE_SD_MODE, BIT_CLK_EN);
    REG_FCIE_CLRBIT(FCIE_SD_MODE, BIT_DATA_SYNC);

	// setup command & response size
	// hardware generate the last CRC byte automatically
	// hardware check the last CRC byte automatically
	REG_FCIE_W(FCIE_CMD_RSP_SIZE, (u8CmdSize<<BIT_CMD_SIZE_SHIFT) + u8RspSize );

	// prepare command FIFO
    for(i=0; i<u8CmdSize; i++)
    {
        HalFcie_CmdFifoSet(i, pCmdRspInfo->Command.Array[i]);
    }

	REG_FCIE_W(FCIE_SD_CTRL, 0); // clear first

	#if TEST_CMDNORESPONSE
		FCIE_RIU_16_ON(FCIE_SD_CTRL, BIT_ERR_DET_ON);
	#endif

	if(pCmdRspInfo->CmdType!=CMD_TYPE_ADTC) // simple command
	{
		switch(pCmdRspInfo->RspType) {
			case RSP_TYPE_NO:
				//printf("command only");
		        REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_SD_CMD_EN);
				break;
			case RSP_TYPE_R2:
				//printf("cmd + r2\r\n");
    	        REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_SD_CMD_EN + BIT_SD_RSP_EN + BIT_SD_RSPR2_EN);
				break;
			case RSP_TYPE_R3:
				FCIE_RIU_16_OF(FCIE_SD_CTRL, BIT_ERR_DET_ON); // R3 has no CRC, IP detect wrong error
			case RSP_TYPE_R1:
			case RSP_TYPE_R1b:
			//case RSP_TYPE_R4:
			//case RSP_TYPE_R5:
			default:
				//printf("cmd + rsp\r\n");
    	        REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_SD_CMD_EN + BIT_SD_RSP_EN);
				break;
		}

		#if defined(ENABLE_eMMC_INTERRUPT_MODE)&&ENABLE_eMMC_INTERRUPT_MODE
			REG_FCIE_SETBIT(FCIE_MIE_INT_EN, BIT_CMD_END);
		#endif

	}
	else // data transfer command
	{
		// we can enable cmd + data at the same time in read
		if(pCmdRspInfo->ReadWriteDir==DIR_R)
		{
           	REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_SD_CMD_EN+BIT_SD_RSP_EN+BIT_SD_DTRX_EN);

			if(pCmdRspInfo->DataPath==PATH_ADMA) {

				REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_ADMA_EN); // ADMA read
			}
			#if defined(ENABLE_eMMC_INTERRUPT_MODE)&&ENABLE_eMMC_INTERRUPT_MODE
				REG_FCIE_SETBIT(FCIE_MIE_INT_EN, BIT_DMA_END);
			#endif
		}
		else // write can not send data with cmd at the same time
		{
           	REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_SD_CMD_EN+BIT_SD_RSP_EN); // command first
			#if defined(ENABLE_eMMC_INTERRUPT_MODE)&&ENABLE_eMMC_INTERRUPT_MODE
				REG_FCIE_SETBIT(FCIE_MIE_INT_EN, BIT_CMD_END);
			#endif
		}

		switch(pCmdRspInfo->DataPath)
		{
			case PATH_DMA:
			case PATH_ADMA:
				REG_FCIE_CLRBIT(FCIE_SD_MODE, BIT_DATA_DEST);
				break;
			case PATH_R2N:
				REG_FCIE_SETBIT(FCIE_SD_MODE, BIT_DATA_DEST);
				break;
			default:
				printf("SD Err: wrong data destination\r\n");
				break;
		}

		//printf("FCIE_SD_MODE = %04X\r\n", REG_FCIE(FCIE_SD_MODE));

		// data bus width setup
		REG_FCIE_CLRBIT(FCIE_SD_MODE, BIT_SD_DATA_WIDTH_MASK);
		if(pCmdRspInfo->BusWidth==BUS_4_BITS) {
			//printf("4 bits\n");
			REG_FCIE_SETBIT(FCIE_SD_MODE, BIT_SD_DATA_WIDTH_4);
		}
		else if(pCmdRspInfo->BusWidth==BUS_8_BITS) {
			//printf("8 bits\n");
			REG_FCIE_SETBIT(FCIE_SD_MODE, BIT_SD_DATA_WIDTH_8);
		}
		else {
			//printf("1 bit\n");
		}

		REG_FCIE_W(FCIE_BLK_SIZE, pCmdRspInfo->BlockSize);

		REG_FCIE_W(FCIE_MIU_DMA_ADDR_15_0,  pCmdRspInfo->MiuAddr & 0xFFFF);
		REG_FCIE_W(FCIE_MIU_DMA_ADDR_31_16, pCmdRspInfo->MiuAddr >> 16);

		if(pCmdRspInfo->DataPath!=PATH_ADMA) // normal DMA or R2N
		{
			REG_FCIE_W(FCIE_JOB_BL_CNT, pCmdRspInfo->BlockCount);
			#if 1
			REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0,  (pCmdRspInfo->BlockCount*pCmdRspInfo->BlockSize) & 0xFFFF);
			REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16, (pCmdRspInfo->BlockCount*pCmdRspInfo->BlockSize) >> 16);
			#else // debug test use only
			REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0,  0x0200);
			REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16, 0x0000);
			#endif
		}
		else // ADMA
		{
			REG_FCIE_W(FCIE_JOB_BL_CNT, 1);
			REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0,  0x0010);
			REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16, 0x0000);
		}
	}


	#if 0 // debug use only ------------------------------------------------------------------------
	if((0xBF&pCmdRspInfo->CmdRsp.Command[0])==1)
	{
		printf("while(1) on purpose\n"); while(1);
	}
	#endif // debug use only -----------------------------------------------------------------------


	REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_JOB_START); // start action


	if(pCmdRspInfo->CmdType!=CMD_TYPE_ADTC) // simple command
	{
		IoSts = HalFcie_WaitMieEvent(BIT_SD_CMD_END, SD_TIMEOUT_VALUE);
		if(IoSts==IO_ERROR_DETECT)
		{
			printf("SD Err: fcie detect error while wait simple cmd end, FCIE_SD_STATUS = %04X\n", REG_FCIE(FCIE_SD_STATUS));
			goto ErrorHandle;
		}
		else if(IoSts==IO_TIME_OUT)
		{
			printf("SD Err: wait simple cmd end timeout\r\n");
			goto ErrorHandle;
		}
    }
    else // data transfer command
    {
		if(pCmdRspInfo->ReadWriteDir==DIR_R) // read adtc
		{
			// R2N need wait for more events
			if(pCmdRspInfo->DataPath==PATH_R2N)
			{
				// read out 64 bytes per time, read 8 times in 512 bytes case
				for(u16Index=0; u16Index<8; u16Index++)
				{
					IoSts = HalFcie_WaitGetCIFD( pCmdRspInfo->pBufferAddr + (u16Index<<4), 64);
					if(IoSts)
					{
						printf("SD Err: wait get CIFD fail\r\n");
						while(1);
						goto ErrorHandle;
					}
				}
			}

	        IoSts = HalFcie_WaitMieEvent(BIT_DMA_END, SD_DMA_TIMEOUT_VALUE);
			if(IoSts==IO_ERROR_DETECT)
			{
				printf("SD Err: fcie detect error while wait read end, FCIE_SD_STATUS = %04X\n", REG_FCIE(FCIE_SD_STATUS));
				goto ErrorHandle;
			}
			else if(IoSts==IO_TIME_OUT)
			{
				printf("SD Err: wait read end timeout\r\n");
				goto ErrorHandle;
			}
		}
		else // write adtc
		{
			// need to wait cmd finish then start the data transfer in write
			IoSts = HalFcie_WaitMieEvent(BIT_SD_CMD_END, SD_TIMEOUT_VALUE);
			if(IoSts==IO_ERROR_DETECT)
			{
				printf("SD Err: fcie detect error while wait write cmd end, FCIE_SD_STATUS = %04X\n", REG_FCIE(FCIE_SD_STATUS));
				goto ErrorHandle;
			}
			else if(IoSts==IO_TIME_OUT)
			{
				printf("SD Err: wait write cmd end timeout\r\n");
				goto ErrorHandle;
			}
			#if 0
			else // debug use only, write command OK, check response here
			{
				printf("RSP: ");
				for(i=0; i<u8RspSize; i++) // last CRC didn't copy to CIFC
				{
					printf("%02X ", HalFcie_CmdFifoGet(i));
				}
				printf("\n");
			}
			#endif

			//REG_FCIE_CLRBIT(FCIE_SD_CTRL, BIT_SD_RSPR2_EN+BIT_SD_RSP_EN+BIT_SD_CMD_EN+BIT_SD_DTRX_EN+BIT_SD_DAT_DIR_W);
			REG_FCIE_W(FCIE_SD_CTRL, BIT_SD_DTRX_EN+BIT_SD_DAT_DIR_W); // data transfer second

			if(pCmdRspInfo->DataPath==PATH_ADMA) {

				REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_ADMA_EN); // ADMA write
			}

			#if defined(ENABLE_eMMC_INTERRUPT_MODE)&&ENABLE_eMMC_INTERRUPT_MODE
				REG_FCIE_SETBIT(FCIE_MIE_INT_EN, BIT_DMA_END);
			#endif


			REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_JOB_START); // start action


			// R2N
			if(pCmdRspInfo->DataPath==PATH_R2N)
			{
				// write in 64 bytes per time, read 8 times in 512 bytes case
				for(u16Index=0; u16Index<8; u16Index++)
				{
					IoSts = HalFcie_WaitSetCIFD( pCmdRspInfo->pBufferAddr + (u16Index<<4), 64);
					if(IoSts)
					{
						printf("SD Err: wait set CIFD fail\r\n");
						while(1);
						goto ErrorHandle;
					}
				}
			}

	        IoSts = HalFcie_WaitMieEvent(BIT_DMA_END, SD_DMA_TIMEOUT_VALUE);
			if(IoSts==IO_ERROR_DETECT)
			{
				printf("SD Err: fcie detect error while wait dma end, FCIE_SD_STATUS = %04X\n", REG_FCIE(FCIE_SD_STATUS));
				goto ErrorHandle;
			}
			else if(IoSts==IO_TIME_OUT)
			{
				printf("SD Err: wait dma end timeout\r\n");
				goto ErrorHandle;
			}
		}

    }

	u16_reg = REG_FCIE(FCIE_SD_STATUS);

	//printf("FCIE_SD_STATUS = %04X", u16_reg);

	if( ((pCmdRspInfo->RspType==RSP_TYPE_R2)||(pCmdRspInfo->RspType==RSP_TYPE_R3)) && ((u16_reg&BITS_ERROR)==BIT_CMD_RSP_CERR) ) {
		// patch hardware false alarm of R2 response CRC error
		//printf("patch hardware false alarm of R2 response CRC error\r\n");
	    REG_FCIE_W(FCIE_SD_STATUS, BIT_CMD_RSP_CERR);
	}
	else if(u16_reg&BITS_ERROR) {
		if(!gu8SilenceTuning)
		{
			printf("SD Err: FCIE_SD_STATUS = %04X\n", REG_FCIE(FCIE_SD_STATUS));
			if(u16_reg&BIT_SD_R_CRC_ERR)	printf("SD Err: read CRC error\n");
			if(u16_reg&BIT_DAT_WR_CERR)		printf("SD Err: write CRC status error\n");
			if(u16_reg&BIT_DAT_WR_TOUT)		printf("SD Err: transmitted data phase to error\n");
			if(u16_reg&BIT_CMD_NO_RSP)		printf("SD Err: command no response\n");
			if(u16_reg&BIT_CMD_RSP_CERR)	printf("SD Err: response CRC error\n");
			if(u16_reg&BIT_DAT_RD_TOUT)		printf("SD Err: received data phase to error\n");
		}
		//HalFcie_ClearErrSts();
		IoSts = IO_ERROR;
		goto ErrorHandle;
	}

	// After CMD18, data might be possible all low in D0 to cause timeout here.
    //if(pCmdRspInfo->SkipWaitData0==0)
    if(pCmdRspInfo->RspType==RSP_TYPE_R1b)
    {
		IoSts = halFCIE_SDWaitD0High(TIMEOUT_NORMAL);
        if(IoSts)
        {
			printf("SD Err: wait D0 high timeout in sned cmd\n");
			while(1);
            goto ErrorHandle;
        }
    }

    if(u8RspSize)
    {
		#ifdef PRINT_CMD_RSP
		printf(", RSP(%d): ", u8RspSize);
		#endif
        for(i=0; i<u8RspSize; i++) // last CRC didn't copy to CIFC
        {
            pCmdRspInfo->Response.Array[i] = HalFcie_CmdFifoGet(i);
			#ifdef PRINT_CMD_RSP
			printf("%02X ", pCmdRspInfo->Response.Array[i]);
			#endif
        }
		#ifdef PRINT_CMD_RSP
        printf("\n");
		#endif
        /*if(HalFcie_CheckResponse())
        {
            LOG_FCIE(L_FCIE_ERROR, "Error!!! Response Error!\r\n");
            goto ErrorHandle;
        }*/
    }
    else
    {
		#ifdef PRINT_CMD_RSP
        printf("\n");
		#endif
    }

    REG_FCIE_CLRBIT(FCIE_SD_MODE, BIT_CLK_EN); // turn off clock after command finish

    return IO_SUCCESS;

ErrorHandle:

	if(!gu8SilenceTuning)
	{
    	printf("SD Err: send CMD%d", 0xBF&pCmdRspInfo->Command.Cmd.Index);
		printf("[%d] ", u8CmdSize);
    	for(i=0; i<u8CmdSize; i++)
    	{
        	printf("%02X ", pCmdRspInfo->Command.Array[i]);
    	}
		printf(" fail 0x%02X!\r\n", IoSts);
	}

    REG_FCIE_CLRBIT(FCIE_SD_MODE, BIT_CLK_EN); // turn off clock after command finish even fail

    return IoSts;
}

#define U32BEND2LEND(X) ( ((X&0x000000FF)<<24) + ((X&0x0000FF00)<<8) + ((X&0x00FF0000)>>8) + ((X&0xFF000000)>>24) )

U32 DrvSd_CMD17(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf)
{
	U32 u32_err = 0;
	U32 u32_arg;
	//U8  u8_retry = 0;
	//U32 u32PhyAddr = 0;
    CMD_RSP_INFO CmdRspInfo = {0};
	U32 u32_dma_addr;

	u32_arg =  u32_eMMCBlkAddr;

	u32_dma_addr = SD_translate_DMA_address_Ex((U32)pu8_DataBuf, 0x200);

	CmdRspInfo.Command.Cmd.Index = 17|0x40;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(u32_arg);
    CmdRspInfo.CmdType = CMD_TYPE_ADTC;
    CmdRspInfo.RspType = RSP_TYPE_R1;
	CmdRspInfo.ReadWriteDir = DIR_R;
	CmdRspInfo.DataPath = PATH_DMA;
	CmdRspInfo.BusWidth = BUS_4_BITS;
	CmdRspInfo.MiuAddr = u32_dma_addr;
	CmdRspInfo.pBufferAddr = NULL; // DMA don't need this field
	CmdRspInfo.BlockSize = 512;
	CmdRspInfo.BlockCount = 1;

    u32_err = HalFcie_SendCommand(&CmdRspInfo);

	if(u32_err)
	{
		goto ErrorHandle;
	}

	return 0;

ErrorHandle:

	return u32_err;
}

U32 DrvSd_CMD24(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf)
{
	U32 u32_err = 0;
	U32 u32_arg;
	//U8  u8_retry = 0;
	//U32 u32PhyAddr = 0;
    CMD_RSP_INFO CmdRspInfo = {0};
	U32 u32_dma_addr;

	u32_arg =  u32_eMMCBlkAddr;

	u32_dma_addr = SD_translate_DMA_address_Ex((U32)pu8_DataBuf, 0x200);

	CmdRspInfo.Command.Cmd.Index = 24|0x40;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(u32_arg);
    CmdRspInfo.CmdType = CMD_TYPE_ADTC;
    CmdRspInfo.RspType = RSP_TYPE_R1;
	CmdRspInfo.ReadWriteDir = DIR_W;
	CmdRspInfo.DataPath = PATH_DMA;
	CmdRspInfo.BusWidth = BUS_4_BITS;
	CmdRspInfo.MiuAddr = u32_dma_addr;
	CmdRspInfo.pBufferAddr = NULL; // DMA don't need this field
	CmdRspInfo.BlockSize = 512;
	CmdRspInfo.BlockCount = 1;

    u32_err = HalFcie_SendCommand(&CmdRspInfo);

	if(u32_err)
	{
		goto ErrorHandle;
	}

	return 0;

ErrorHandle:

	return u32_err;
}

#define STUFF_BITS			0x00000000

U32 DrvSd_CMD12(void)
{
	U32 u32_err = 0;
    CMD_RSP_INFO CmdRspInfo = {0};

	CmdRspInfo.Command.Cmd.Index = 12|0x40;
	CmdRspInfo.Command.Cmd.Arg = STUFF_BITS;
    CmdRspInfo.CmdType = CMD_TYPE_AC;
    CmdRspInfo.RspType = RSP_TYPE_R1b;

    u32_err = HalFcie_SendCommand(&CmdRspInfo);

	if(u32_err)
	{
		goto ErrorHandle;
	}

	return 0;

ErrorHandle:

	return u32_err;
}


U32 DrvSd_CMD18_ADMA(U32 u32_eMMCBlkAddr, struct kernel_like_mmc_data * pData)
{
	U32 u32_err = 0;
    CMD_RSP_INFO CmdRspInfo = {0};
	//U32 u32_dma_addr;

	CmdRspInfo.Command.Cmd.Index = 18|0x40;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(u32_eMMCBlkAddr);
    CmdRspInfo.CmdType = CMD_TYPE_ADTC;
    CmdRspInfo.RspType = RSP_TYPE_R1;
	CmdRspInfo.ReadWriteDir = DIR_R;
	CmdRspInfo.BusWidth = BUS_4_BITS;

	// setup below in mstar_mci_setup_descriptor_addr()
	#if 0
	CmdRspInfo.DataPath = PATH_ADMA;
	CmdRspInfo.MiuAddr = u32_dma_addr;
	CmdRspInfo.pBufferAddr = NULL; // DMA don't need this field
	CmdRspInfo.BlockSize = 512;
	CmdRspInfo.BlockCount = 1;
	#endif

	mstar_mci_prepare_descriptors(pData);
	mstar_mci_setup_descriptor_addr(&CmdRspInfo);

    u32_err = HalFcie_SendCommand(&CmdRspInfo);
	if(u32_err)
	{
		goto ErrorHandle;
	}

	DrvSd_CMD12();

	return 0;

ErrorHandle:

	return u32_err;
}

U32 DrvSd_CMD25_ADMA(U32 u32_eMMCBlkAddr, struct kernel_like_mmc_data * pData)
{
	U32 u32_err = 0;
    CMD_RSP_INFO CmdRspInfo = {0};
	//U32 u32_dma_addr;

	CmdRspInfo.Command.Cmd.Index = 25|0x40;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(u32_eMMCBlkAddr);
    CmdRspInfo.CmdType = CMD_TYPE_ADTC;
    CmdRspInfo.RspType = RSP_TYPE_R1;
	CmdRspInfo.ReadWriteDir = DIR_W;
	CmdRspInfo.BusWidth = BUS_4_BITS;

	// setup below in mstar_mci_setup_descriptor_addr()
	#if 0
	CmdRspInfo.DataPath = PATH_ADMA;
	CmdRspInfo.MiuAddr = u32_dma_addr;
	CmdRspInfo.pBufferAddr = NULL; // DMA don't need this field
	CmdRspInfo.BlockSize = 512;
	CmdRspInfo.BlockCount = 1;
	#endif

	mstar_mci_prepare_descriptors(pData);

	//fcie_dump_mem(g_ADMAInfo.DescriptorAddr, 0x200);

	mstar_mci_setup_descriptor_addr(&CmdRspInfo);

    u32_err = HalFcie_SendCommand(&CmdRspInfo);
	if(u32_err)
	{
		goto ErrorHandle;
	}

	DrvSd_CMD12();

	return 0;

ErrorHandle:

	return u32_err;
}


#endif

E_IO_STS HalFcie_WaitGetCIFD(U32 * pu32_DataBuf, U32 u32_ByteCnt)
{
	U16 u16_i, *pu16_Data = (U16*)pu32_DataBuf;

	if(u32_ByteCnt > FCIE_CIFD_BYTE_CNT)
	{
		return IO_ERROR;
	}
	if (eMMC_WaitCIFD_Event(BIT_WBUF_FULL, HW_TIMER_DELAY_500ms)== (HW_TIMER_DELAY_500ms ))
	{
		printf( "Error: CIFD timeout 0, ErrCode\r\n" );
		return IO_ERROR; // timeout
	}

	for(u16_i=0; u16_i<(u32_ByteCnt>>1); u16_i++)
		REG_FCIE_R(NC_WBUF_CIFD_ADDR(u16_i), pu16_Data[u16_i]);

	REG_FCIE_W(NC_CIFD_EVENT,BIT_WBUF_FULL);

	REG_FCIE_W(NC_CIFD_EVENT, BIT_WBUF_EMPTY_TRI);

	return IO_SUCCESS;
}

U16 SD_ReadCRCFifo(U32 i)
{
	return REG_FCIE(NC_CRCBUF_CIFD_ADDR(i));
}
U32 eMMC_WaitCIFD_Event(U16 u16_WaitEvent, U32  u32_MicroSec)
{
	volatile U32 u32_Count;
	volatile U16 u16_Reg;

	for (u32_Count=0; u32_Count < u32_MicroSec; u32_Count++)
	{
		REG_FCIE_R(NC_CIFD_EVENT, u16_Reg);
		if ((u16_Reg & u16_WaitEvent) == u16_WaitEvent)
			break;

		udelay(HW_TIMER_DELAY_1us);
	}
	if (u32_Count >= u32_MicroSec)
	{
		REG_FCIE_R(NC_CIFD_EVENT, u16_Reg);
		printf( "CIFD Event Timout \n");
	}
	return u32_Count;
}

E_IO_STS HalFcie_WaitSetCIFD(U32 * pu32_DataBuf, U32 u32_ByteCnt)
{
	U16 u16_i, *pu16_Data = (U16*)pu32_DataBuf;

	if(u32_ByteCnt > FCIE_CIFD_BYTE_CNT)
	{
		return IO_ERROR;
	}

	for(u16_i=0; u16_i<(u32_ByteCnt>>1); u16_i++)
		REG_FCIE_W(NC_RBUF_CIFD_ADDR(u16_i), pu16_Data[u16_i]);

	REG_FCIE_SETBIT(NC_CIFD_EVENT, BIT_RBUF_FULL_TRI);

	if (eMMC_WaitCIFD_Event(BIT_RBUF_EMPTY, HW_TIMER_DELAY_500ms)== (HW_TIMER_DELAY_500ms ))
	{
		printf("Error: CIFD timeout \r\n");
		return IO_TIME_OUT;
	}

	REG_FCIE_SETBIT(NC_CIFD_EVENT, BIT_RBUF_EMPTY);

	return IO_SUCCESS;
}

// 0~11 pattern select
// 0: 0x00000000
// 1: 0xFFFFFFFF
// 2: 0xFF00FF00
// 3: 0x00FF00FF
// 4: 0x55555555
// 5: 0xAAAAAAAA
// 6: 0xAA55AA55
// 7: 0x55AA55AA
// 8: 0xA55AA55A
// 9: 0x5AA55AA5
//10: incresing
//11: decreasing

U32 HalFcie_BistTest(U8 u8_PatSel)
{
    U32 u32_err = 0;

    printf("BIST pattern index: %d\n", u8_PatSel);

    // Select pattern
    REG_FCIE_CLRBIT(FCIE_BIST, 0xF<<12);
    REG_FCIE_SETBIT(FCIE_BIST, (u8_PatSel & 0xF)<<12);

    // Set BIST Mode
    REG_FCIE_SETBIT(FCIE_TEST_MODE, BIT_BIST_MODE);

	DrvSd_CMD24(10000, (U8*)0x20400000);

	DrvSd_CMD17(10000, (U8*)0x20400000);

    // Wait BIST Error Flag
    if( REG_FCIE(FCIE_BIST) & BIT0 )
    {
        printf("\033[7;31m%s: BIST pattern type %d fail!!\033[m\n", __FUNCTION__, u8_PatSel);
        while(1);
    }

    printf("%s: BIST pattern type %d ok!!\n", __FUNCTION__, u8_PatSel);

    REG_FCIE_CLRBIT(FCIE_TEST_MODE, BIT_BIST_MODE);

    return u32_err;
}

U32 HalFcie_PowerSaveMode(void)
{
    //U32 u32_err = 0;
	U32 u32_i = 0;
	U16 u16_Reg = 0;

    // Enable power save test by RIU mode
    //REG_FCIE_W(FCIE_PWR_SAVE_CTL, 0x000D);

    /* (1) Clear HW Enable */
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x00), 0x0000);
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x01),
               PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x07);

	/* (2) Clear All Interrupt */
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x02), 0xffff);
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x03),
               PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x00);

	/* (3) Clear SD MODE Enable */
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x04), 0x0000);
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x05),
               PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x0B);

	/* (4) Clear SD CTL Enable */
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x06), 0x0000);
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x07),
               PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x0C);

	/* (5) Reset Start */
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x08), 0x0000);
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x09),
               PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x3F);

	/* (6) Reset End */
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x0A), 0x0001);
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x0B),
               PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x3F);

	/* (7) Set "SD_MOD" */
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x0C), 0x0021);
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x0D),
               PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x0B);

	/* (8) Enable "reg_sdio_en" */
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x0E), 0x0004);
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x0F),
               PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x07);

	/* (9) Command Content, IDLE */
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x10), 0x0040);
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x11),
               PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x20);

	/* (10) Command Content, STOP */
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x12), 0x0000);
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x13),
               PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x21);

	/* (11) Command Content, STOP */
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x14), 0x0000);
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x15),
               PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x22);

	/* (12) Command & Response Size */
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x16), 0x0500);
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x17),
               PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x0A);

	/* (13) Enable Interrupt, SD_CMD_END */
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x18), 0x0002);
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x19),
               PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x01);

	/* (14) Command Enable + job Start */
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x1A), 0x0044);
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x1B),
               PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x0C);

	/* (15) Wait Interrupt */
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x1C), 0x0000);
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x1D),
               PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WINT);

	/* (16) Clear Interrupt */
	//REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x1E), 0x0002);
	//REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x1F),
    //           PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x00);

    /* (17) Clear HW Enable */
	//REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x20), 0x0000);
	//REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x21),
    //           PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_WREG | PWR_CMD_BK0 | 0x07);

	/* (18) STOP */
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x1E), 0x0000);
	REG_FCIE_W(GET_REG_ADDR(FCIE_POWEER_SAVE_MODE_BASE, 0x1F),
               PWR_BAT_CLASS | PWR_RST_CLASS | PWR_CMD_STOP);

    printf("1s\n");	udelay(1000000);
    printf("1s\n");	udelay(1000000);
    printf("1s\n");	udelay(1000000);
    printf("1s\n");	udelay(1000000);
    printf("1s\n");	udelay(1000000);
    printf("1s\n");	udelay(1000000);
    printf("1s\n");	udelay(1000000);
    printf("1s\n");	udelay(1000000);
    printf("1s\n");	udelay(1000000);
    printf("1s\n");	udelay(1000000);

    //while(1);

    // Trigger power save mode
    REG_FCIE_W(FCIE_PWR_SAVE_CTL, 0x000F);

	while(1){

		u16_Reg = REG_FCIE(FCIE_PWR_SAVE_CTL);
		printf("FCIE_PWR_SAVE_CTL = %04Xh\n", u16_Reg);

    	if( u16_Reg & (BIT_POWER_SAVE_MODE_INT|BIT_RIU_SAVE_EVENT) )
    	{
		    printf("Power saving mode ok\n");
			break;
		}
		udelay(1000);
		u32_i++;
		if(u32_i==1000) {
    	    printf("Power saving mode fail\n");
			while(1);
			break;
		}
	}

    return 0;
}

void HalFcie_TestDataOneIntr(void)
{
	U16 u16_Reg = 0;
	U32 u32_i = 0;

	REG_FCIE_CLRBIT(FCIE_SDIO_MOD, BIT_REG_SDIO_MOD_MASK);

	// 0b00: Continuous interrupt detect

	// 0b01: CMD12 ot IO abort command interrupt detect
	//REG_FCIE_SETBIT(FCIE_SDIO_MOD, BIT0);

	// 0b10: Single block read/write interrupt detect
	//REG_FCIE_SETBIT(FCIE_SDIO_MOD, BIT1);

	// 0b11: multi-block read/write interrupt detect
	//REG_FCIE_SETBIT(FCIE_SDIO_MOD, BIT1|BIT0);

	REG_FCIE_SETBIT(FCIE_SDIO_MOD, BIT_SDIO_DET_ON); // enable SDIO interrupt

	REG_FCIE_CLRBIT(FCIE_SDIO_MOD, BIT_SDIO_DET_INT_SRC);

	while(1) {

		u16_Reg = REG_FCIE(FCIE_MIE_EVENT);

    	if( u16_Reg & BIT_SDIO_INT )
    	{
		    printf("SDIO interrupt detected\n");
			break;
		}

		udelay(1000); // 1 ms
		u32_i++;

		if(u32_i%1000==999) {
			printf("%d s\n", (u32_i/1000)+1);
		}

		if(u32_i==10000) {
    	    printf("test data 1 interrupt 10 sec timeout\n");
			break;
		}

	}

}


#define TEST_BUFFER_SIZE    0x100000 // 1MB
static U8 W_BUFFER[TEST_BUFFER_SIZE] __attribute__((aligned(0x80)));
static U8 R_BUFFER[TEST_BUFFER_SIZE] __attribute__((aligned(0x80)));

// W_BUFFER is 1MB
// R_BUFFER is 1MB
// each 1MB read write buffer divide to 256KB x 4
// 256KB = 512 sectors
// setup different descriptor to test ADMA
//

#define AMDA_256KB 256*1024
#define BLOCK_ADDR_4_TEST 0000

U8 HalFcie_TestAdvanceDMA(U8 u8Pattern)
{
	struct kernel_like_mmc_data mmc_data_w, mmc_data_r;
	struct scatterlist sg_w[4], sg_r[4];
	U8 u8_i;

	printf("HalFcie_TestAdvanceDMA(%02Xh)\n", u8Pattern);

	g_ADMAInfo.DescriptorAddr = (U32)g_ADMAInfo.Descriptor; // init

	memset(W_BUFFER, 0x00, 0x100000);
	memset(R_BUFFER, 0x00, 0x100000);

	memset(W_BUFFER,				u8Pattern, 0x200 * 10);
	memset(W_BUFFER+AMDA_256KB,		u8Pattern, 0x200 *  5);
	memset(W_BUFFER+AMDA_256KB*2,	u8Pattern, 0x200 *  3);
	memset(W_BUFFER+AMDA_256KB*3,	u8Pattern, 0x200 *  1);

	//fcie_dump_mem(g_ADMAInfo.DescriptorAddr, 0x200);

	///////////////////////////////////////////////////////////////////////////////////////////
	// write SG setup
	mmc_data_w.sg_len = 4;
	mmc_data_w.sg = sg_w;
	// 1st SG
	sg_w[0].u32_dma_addr = ((U32)W_BUFFER);
	sg_w[0].u32_length = 0x200 * 10; // 10 sectors
	// 2nd SG
	sg_w[1].u32_dma_addr = ((U32)W_BUFFER)+AMDA_256KB;
	sg_w[1].u32_length = 0x200 * 5; // 5 sectors
	// 3rd SG
	sg_w[2].u32_dma_addr = ((U32)W_BUFFER)+AMDA_256KB*2;
	sg_w[2].u32_length = 0x200 * 3; // 3 sectors
	// 4th SG
	sg_w[3].u32_dma_addr = ((U32)W_BUFFER)+AMDA_256KB*3;
	sg_w[3].u32_length = 0x200 * 1; // 1 sector

	for(u8_i=0; u8_i<4; u8_i++){
		printf("W SG[%d]: 0x%08X\n", u8_i, sg_w[u8_i].u32_dma_addr);
	}

	DrvSd_CMD25_ADMA(BLOCK_ADDR_4_TEST, &mmc_data_w);

	///////////////////////////////////////////////////////////////////////////////////////////
	// read SG setup
	mmc_data_r.sg_len = 4;
	mmc_data_r.sg = sg_r;
	// 1st SG
	sg_r[0].u32_dma_addr = ((U32)R_BUFFER);
	sg_r[0].u32_length = 0x200 * 10; // 10 sectors
	// 2nd SG
	sg_r[1].u32_dma_addr = ((U32)R_BUFFER)+AMDA_256KB;
	sg_r[1].u32_length = 0x200 * 5; // 5 sectors
	// 3rd SG
	sg_r[2].u32_dma_addr = ((U32)R_BUFFER)+AMDA_256KB*2;
	sg_r[2].u32_length = 0x200 * 3; // 3 sectors
	// 4th SG
	sg_r[3].u32_dma_addr = ((U32)R_BUFFER)+AMDA_256KB*3;
	sg_r[3].u32_length = 0x200 * 1; // 1 sector

	for(u8_i=0; u8_i<4; u8_i++){
		printf("R SG[%d]: 0x%08X\n", u8_i, sg_r[u8_i].u32_dma_addr);
	}

	DrvSd_CMD18_ADMA(BLOCK_ADDR_4_TEST, &mmc_data_r);



	if(memcmp(W_BUFFER, R_BUFFER, 0x100000))
	{
		printf("ADMA test fail\n");
		return 1;
	}
	else
	{
		printf("ADMA test OK\n");
		return 0;
	}

}

#define DEBUG_SG_ELEMENT 0

static U32 mstar_mci_prepare_descriptors(struct kernel_like_mmc_data * pData)
{
	U32 i, /*u32DescptAddr,*/ u32BusAddr, u32DeviceAddr, u32DmaLeng, u32TotalLength = 0;
	struct scatterlist * pScatterList = NULL;

	//printk("descriptor addr %08Xh", g_ADMAInfo.DescriptorAddr);
	//u32DescptAddr = virt_to_phys((void *)g_ADMAInfo.DescriptorAddr); // virtual to bus address
	//printk(" -- virt_to_phys --> %08Xh\n", u32DescptAddr);

	// setup descriptor
	memset(&g_ADMAInfo, 0, sizeof(ADMA_INFO)-4); // clear

	#if defined(DEBUG_SG_ELEMENT) && DEBUG_SG_ELEMENT
	printk("SG[%d] = ", pData->sg_len);
	#endif

	for(i=0; i<pData->sg_len; i++) {

		pScatterList = &(pData->sg[i]);
		//u32BusAddr = sg_dma_address(pScatterList);
		//u32DmaLeng = sg_dma_len(pScatterList);

		u32BusAddr = pScatterList->u32_dma_addr;
		u32DmaLeng = pScatterList->u32_length;

		flush_cache(u32BusAddr, u32DmaLeng);

		//BUG_ON((u32DmaLeng>>9)&0xFFFFF000);
		u32TotalLength += u32DmaLeng;
		#if defined(DEBUG_SG_ELEMENT) && DEBUG_SG_ELEMENT
		printk("%d + ", u32DmaLeng>>9);
		#endif
		printf("SG[%d] %2d sector, BA = %08Xh", i, u32DmaLeng>>9, u32BusAddr);
		if( u32BusAddr >= CONFIG_MIU1_BUSADDR) {
			u32DeviceAddr = u32BusAddr - CONFIG_MIU1_BUSADDR;
			g_ADMAInfo.Descriptor[i].adma_miu_sel = 1;
			printf(" - %08Xh(MIU1) = %08Xh\n", CONFIG_MIU1_BUSADDR , u32DeviceAddr);
		} else {
			u32DeviceAddr = u32BusAddr - CONFIG_MIU0_BUSADDR;
			printf(" - %08Xh(MIU0) = %08Xh\n", CONFIG_MIU0_BUSADDR , u32DeviceAddr);
		}

		g_ADMAInfo.Descriptor[i].adma_miu_addr = u32DeviceAddr;
		g_ADMAInfo.Descriptor[i].adma_job_cnt = u32DmaLeng>>9;
		g_ADMAInfo.Descriptor[i].adma_length = u32DmaLeng;

	}

	g_ADMAInfo.Descriptor[pData->sg_len-1].adma_end_flag = 1; // must give a end mark

	#if defined(DEBUG_SG_ELEMENT) && DEBUG_SG_ELEMENT
	printk("= %d\n", u32TotalLength>>9);
	#endif

	//MsOS_Dcache_Flush(g_ADMAInfo.Descriptor, sizeof(ADMA_INFO));

	//Chip_Clean_Cache_Range_VA_PA(g_ADMAInfo.DescriptorAddr, u32DescptAddr, sizeof(ADMA_INFO));

	//eMMC_dump_mem((U8 *)&g_ADMAInfo, 32); // debug use

	return u32TotalLength;
}


// if there is only 1 descriptor, only need to setup once
// need to think about share IP case, setup each time for safe if share IP

static void	mstar_mci_setup_descriptor_addr(CMD_RSP_INFO * pCmdRspInfo)
{
	U32	u32DescptAddr;

	// give descriptor array addr to FCIE
	//u32DescptMiuAddr = eMMC_translate_DMA_address_Ex(g_ADMAInfo.DescriptorAddr, sizeof(ADMA_INFO));
	//printk("mstar_mci_setup_descriptor_addr1 --> %08X\n", g_ADMAInfo.DescriptorAddr);
	// kernel
	//u32DescptAddr = virt_to_phys((void *)g_ADMAInfo.DescriptorAddr); // virtual to bus address
	// bus addr = virtual addr in mboot

	u32DescptAddr = g_ADMAInfo.DescriptorAddr;

	flush_cache(u32DescptAddr, sizeof(g_ADMAInfo));

	//printf("mstar_mci_setup_descriptor_addr2 --> %08X\n", u32DescptAddr);
	//printf("Descpt Addr: %08Xh --> %08Xh", g_ADMAInfo.DescriptorAddr, u32DescptMiuAddr);
	// bus address to device address
	if( u32DescptAddr >= CONFIG_MIU1_BUSADDR) {
		u32DescptAddr -= CONFIG_MIU1_BUSADDR;
		//REG_FCIE_SETBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
		//printk(" - %08Xh(MIU1) = %08Xh\n", MSTAR_MIU1_BUS_BASE , u32DescptMiuAddr);
	} else {
		u32DescptAddr -= CONFIG_MIU0_BUSADDR;
		//REG_FCIE_CLRBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
		//printk(" - %08Xh(MIU0) = %08Xh\n", MSTAR_MIU0_BUS_BASE , u32DescptMiuAddr);
	}
	//printf("mstar_mci_setup_descriptor_addr3 --> %08X\n", u32DescptAddr);

	pCmdRspInfo->DataPath = PATH_ADMA;
	pCmdRspInfo->MiuAddr = u32DescptAddr;
	pCmdRspInfo->pBufferAddr = NULL; // DMA don't need this field
	pCmdRspInfo->BlockSize = 512;
	pCmdRspInfo->BlockCount = 1;

}


///////////////////////////////////////////////////////////////////////////////////////////////////


//int tune=0;
/*********************************************************************
*
*   PROCEDURE NAME:
*       halFCIE_TransferData
*
*   DESCRIPTION:
*       Transfer data to card (for linux/uboot use)
*   NOTE:
*
*********************************************************************/
#if 0
E_IO_STS halFCIE_TransferData(E_DAT_DIR eDir)
{
    E_IO_STS u8Err=IO_SUCCESS;
    //unsigned char* bufaddr;
    //int   u16_i,u32_err;

#if 0
    if (data->dma==R2N_MODE)
    {
         if (eDir==DAT_WRITE)		//write
         {
                 bufaddr =data->dest;

		REG_FCIE_SETBIT(FCIE_SD_MODE, BIT_SD_DATA_CIFD);


         	REG_FCIE_W(FCIE_SD_CTRL, BIT_SD_DTRX_EN|BIT_SD_DAT_DIR_W|BIT_JOB_START);
		printf("R2N write data\n");
		for (u16_i=0; u16_i< (0x200 >> 6); u16_i++)
		{
		u32_err = eMMC_WaitSetCIFD(  bufaddr + (u16_i << 6), 0x40);
		if(u32_err != eMMC_ST_SUCCESS)
		{
			printf("R2N write data fail\n");
		       return;
		}
		}

          }
	   else		//read R2N
	   {
	   		printf("R2N read data\n");
                 bufaddr =data->dest;

	   	for (u16_i=0; u16_i< (0x200 >> 6); u16_i++)
		{   // read data
			u32_err = eMMC_WaitGetCIFD(bufaddr + (u16_i << 6), 0x40);
			if(u32_err != eMMC_ST_SUCCESS)
			{
				printf("R2N reae data fail\n");
				return;
			}
		}

	   }
	   u32_err = halFCIE_Platform_WaitMieEvent(BIT_DMA_END, 3000);
 	   if( REG(FCIE_SD_STATUS) & (BIT_DAT_RD_CERR+BIT_DAT_WR_CERR+BIT_DAT_WR_TOUT) )
    		{
     	   	printf("Transfer data have IO_ERROR, SD_STS = 0x%04X\r\n", FCIE_RIU_R16(FCIE_SD_STATUS));
     	   	_halFCIE_ClearErrSts();
    	    	halFCIE_Platform_Reset_Fcie();
   	     	u8Err = IO_ERROR;
 	   	}
	   return;

    }
#endif
    // DMA or ADMA mode

    if(eDir==1)
    {
        if (halFCIE_SDWaitD0High(TIMEOUT_NORMAL))    //For compatibility of slower MMC cards
        {
            printf("Error!!! wait D0 high fail 3!\r\n");
            u8Err = IO_TIME_OUT;
            goto TransDatErr;
        }

#if  TEST_WRITECRC
	      REG_FCIE_SETBIT(FCIE_RX_SHIFT_CNT, BIT_WRSTS_SHIFT_SEL);
	      REG_FCIE_CLRBIT(FCIE_RX_SHIFT_CNT,0x0f00);
		u16_i=REG_FCIE(FCIE_RX_SHIFT_CNT);

	     REG_FCIE_W(FCIE_RX_SHIFT_CNT,u16_i|(tune<<8));
	     printf("tune:%x\n",tune);
	     tune++;
	     if (tune >=16) tune=0;
#endif

	/*
	if (data->dma==ADMA_MODE)
	{

		printf("write adma:%x\n", BIT_ADMA_EN| BIT_JOB_START|BIT_SD_DAT_DIR_W|BIT_SD_DTRX_EN);
		REG(FCIE_SD_CTRL) =BIT_ADMA_EN| BIT_JOB_START|BIT_SD_DAT_DIR_W|BIT_SD_DTRX_EN ;// start write DMA
	}
	else
	*/
		FCIE_RIU_16_ON(FCIE_SD_CTRL, BIT_JOB_START|BIT_SD_DAT_DIR_W|BIT_SD_DTRX_EN) ;// start write DMA
    }

    u8Err = halFCIE_Platform_WaitMieEvent(BIT_DMA_END, SD_DMA_TIMEOUT_VALUE);
	//u8Err = halFCIE_Platform_WaitMieEvent(R_CARD_DMA_END+R_MMA_LAST_DONE_Z, SD_DMA_TIMEOUT_VALUE * 120 );

    halFCIE_Platform_ClearEvent(BIT_DMA_END);

    if( REG(FCIE_SD_STATUS) & (BIT_DAT_RD_CERR+BIT_DAT_WR_CERR+BIT_DAT_WR_TOUT) )
    {
        printf("Transfer data have IO_ERROR, SD_STS = 0x%04X\r\n", FCIE_RIU_R16(FCIE_SD_STATUS));
        _halFCIE_ClearErrSts();
        halFCIE_Platform_Reset_Fcie();
        u8Err = IO_ERROR;
    }
TransDatErr:

    return (u8Err);

}

#endif

#if 0
U32 sd_hw_timer_delay(U32 u32us)
{
	#if 1
    U32 u32HWTimer = 0;
    volatile U16 u16TimerLow = 0;
    volatile U16 u16TimerHigh = 0;

    // reset HW timer
    REG_FCIE_W(TIMER1_MAX_LOW, 0xFFFF);
    REG_FCIE_W(TIMER1_MAX_HIGH, 0xFFFF);
    REG_FCIE_W(TIMER1_ENABLE, 0);

    // start HW timer
    REG_FCIE_SETBIT(TIMER1_ENABLE, 0x0001);

    while( u32HWTimer < 12*u32us ) // wait for u32usTick micro seconds
    {
        REG_FCIE_R(TIMER1_CAP_LOW, u16TimerLow);
        REG_FCIE_R(TIMER1_CAP_HIGH, u16TimerHigh);

        u32HWTimer = (u16TimerHigh<<16) | u16TimerLow;
    }

    REG_FCIE_W(TIMER1_ENABLE, 0);
	#else
	volatile U32 u32_i=u32us;
    //udelay((u32us>>1)+(u32us>>4)+1);
    while(u32_i>1000)
    {
		udelay(1000);
		u32_i-=1000;
    }
	udelay(u32_i);
	#endif
	return u32us;
}
U32 eMMC_hw_timer_sleep(U32 u32ms)
{
	U32 u32_us = u32ms*1000;

	while(u32_us > 1000)
	{
		sd_hw_timer_delay(1000); // uboot has no context switch
		u32_us -= 1000;
	}

	sd_hw_timer_delay(u32_us);
	return u32ms;
}
#endif
/*********************************************************************
*
*   PROCEDURE NAME:
*       halFCIE_SDWaitD0High
*
*   DESCRIPTION:
*       Check SD data 0 is high or low.
*   NOTE:
*
*********************************************************************/
E_IO_STS halFCIE_SDWaitD0High(U32 timeout)
{
	volatile U32 u32_cnt;

	REG_FCIE_SETBIT(FCIE_SD_MODE, BIT_CLK_EN);

	for(u32_cnt=0; u32_cnt < timeout; u32_cnt++)
	{
		if( !(FCIE_RIU_R16(FCIE_SD_STATUS) & BIT_SD_CARD_BUSY) ) return IO_SUCCESS;
		udelay(1000);
	}

	printf("SDIO Err: wait D0 H timeout: %04Xh\n", REG(FCIE_SD_STATUS));
	return IO_TIME_OUT;

}

/*********************************************************************
*
*   PROCEDURE NAME:
*       halFCIE_SetBusWidth
*
*   DESCRIPTION:
*       Set FCIE data bus width.
*   NOTE:
*
*********************************************************************/
E_IO_STS halFCIE_SetBusWidth(U8 * pu8BusWidth, E_DATA_BUS DataBus)
{
    FCIE_RIU_16_OF(FCIE_SD_MODE, BIT_SD_DATA_WIDTH_4+BIT_SD_DATA_WIDTH_8);

    switch(DataBus)
    {
        case BUS_1_BIT:
            *pu8BusWidth = BUS_1_BIT;
            break;

        case BUS_4_BITS:
			//FCIE_RIU_16_ON(SD_MODE, R_SD_4BITS);
            //printf("set 4 bits width\n");
			REG_FCIE_SETBIT(FCIE_SD_MODE, BIT_SD_DATA_WIDTH_4);
            *pu8BusWidth = BUS_4_BITS;
            break;

        case BUS_8_BITS:
			// FCIE_RIU_16_ON(SD_MODE, R_SD_8BITS);
			REG_FCIE_SETBIT(FCIE_SD_MODE, BIT_SD_DATA_WIDTH_8);
            *pu8BusWidth = BUS_8_BITS;
            break;

        default:
            printf("wrong para in halFCIE_SetBusWidth()\r\n");
            return IO_ERROR;
    }
    return IO_SUCCESS;
}

void HalFcie_SetShiftTune(U8 u8Select, U8 u8Type, U8 u8Count)
{
	if(u8Count>=16) {
		printf("SDIO Err: wrong shift counter\n");
		return;
	}

	if(u8Type==1) // response
	{
		if(u8Select)
		{
			REG_FCIE_CLRBIT(FCIE_RSP_SHIFT_CNT, BIT_RSP_SHIFT_TUNE_MASK);
			REG_FCIE_SETBIT(FCIE_RSP_SHIFT_CNT, u8Count|BIT_RSP_SHIFT_SEL);
		}
		else
		{
			REG_FCIE_CLRBIT(FCIE_RSP_SHIFT_CNT, BIT_RSP_SHIFT_TUNE_MASK|BIT_RSP_SHIFT_SEL);
		}
	}
	else if(u8Type==2) // read clock stop
	{
		if(u8Select)
		{
			REG_FCIE_CLRBIT(FCIE_RX_SHIFT_CNT, BIT_RSTOP_SHIFT_TUNE_MASK);
			REG_FCIE_SETBIT(FCIE_RX_SHIFT_CNT, u8Count|BIT_RSTOP_SHIFT_SEL);
		}
		else
		{
			REG_FCIE_CLRBIT(FCIE_RX_SHIFT_CNT, BIT_RSTOP_SHIFT_TUNE_MASK|BIT_RSTOP_SHIFT_SEL);
		}
	}
	else if(u8Type==3) // write crc status
	{
		if(u8Select)
		{
			REG_FCIE_CLRBIT(FCIE_RX_SHIFT_CNT, BIT_WRSTS_SHIFT_TUNE_MASK);
			REG_FCIE_SETBIT(FCIE_RX_SHIFT_CNT, (u8Count<<8)|BIT_WRSTS_SHIFT_SEL);
		}
		else
		{
			REG_FCIE_CLRBIT(FCIE_RX_SHIFT_CNT, BIT_WRSTS_SHIFT_TUNE_MASK|BIT_WRSTS_SHIFT_SEL);
		}

	}
	else
	{
		printf("SDIO Err: wrong shft type\n");
	}

	printf("RSP_SHIFT_CNT = %04Xh, RX_SHIFT_CNT = %04Xh\n", REG_FCIE(FCIE_RSP_SHIFT_CNT), REG_FCIE(FCIE_RX_SHIFT_CNT));
}

void HalFcie_SetVDD(U8 u8OnOff)
{
	REG_FCIE_CLRBIT(CHIPGPIO_01, BIT3); // oen = 0, output

	if(u8OnOff)
	{
		REG_FCIE_CLRBIT(CHIPGPIO_00, BIT3); // set GPIO low to get 3.3V VDD
	}
	else
	{
		REG_FCIE_SETBIT(CHIPGPIO_00, BIT3); // set GPIO high to get 3.3V VDD
	}
}

#define VOLT_00V 0
#define VOLT_33V 1
#define VOLT_18V 2

// must set 3.3V fisrt, then switch to 1.8V

void HalFcie_SetIOVoltage(U8 u8Volt)
{
	U32 u32_i = 0;
	static U8 only_need_run_once = 0;
	static U8 ldo_on_off_status = 0;

	if(!only_need_run_once)
	{
		// 1. disable OSP (short protection curcuit related)
		REG_FCIE_SETBIT(SDIOPLL_1D, BIT15);

		// 2. OSP count = 0x30
		REG_FCIE_CLRBIT(SDIOPLL_36, 0xFF00);
		REG_FCIE_SETBIT(SDIOPLL_36, 0x3000);

		only_need_run_once = 1;
	}

	if(u8Volt==VOLT_00V)
	{
		ldo_on_off_status = 0;
		REG_FCIE_SETBIT(SDIOPLL_36, BIT05);		// Turning off LDO
	}
	else
	{
		if(!ldo_on_off_status) // LDO is off
		{
			// 3. tunning on LDO
			REG_FCIE_SETBIT(SDIOPLL_36, BIT05);		// Turning off LDO
			udelay(10000);							// delay 10ms
			REG_FCIE_CLRBIT(SDIOPLL_36, BIT05);		// Turning on LDO
			ldo_on_off_status = 1;
		}

		// 4. check if 3.3V ready
		if(u8Volt==VOLT_33V)
		{
			REG_FCIE_CLRBIT(SDIOPLL_36, BIT02|BIT04);		// set to 3.3V

			//printf("wait 3.3V ready\n");

			while(1)
			{
				if (FCIE_RIU_R16(SDIOPLL_10) & BIT12) break;
				//printf(".");

				udelay(1000); // delay 1ms
				if(u32_i++>1000)
				{
					printf("timeout to set 3.3V\n");
					while(1);
				}
			}
		}
		// 5. check if 1.8V ready
		else if(u8Volt==VOLT_18V)
		{
			REG_FCIE_SETBIT(SDIOPLL_36, BIT02|BIT04);		// set to 1.8V

			//printf("wait 1.8V ready");

			while(1)
			{
				if (FCIE_RIU_R16(SDIOPLL_10) & BIT13) break;
				//printf(".");

				udelay(1000); // delay 1ms
				if(u32_i++>1000)
				{
					printf("timeout to set 1.8V\n");
					while(1);
				}
			}

			//printf("1.8V is ready\n");
		}
	}


}

U8 HalFcie_SendClocknWaitD0High(void)
{
    E_IO_STS IoSts = IO_SUCCESS;

    REG_FCIE_SETBIT(FCIE_SD_MODE, BIT_CLK_EN);

	IoSts = halFCIE_SDWaitD0High(TIMEOUT_NORMAL);
    if(IoSts)
    {
		printf("SD Err: wait D0 high timeout in HalFcie_SendClocknWaitD0High()\n");
        goto ErrorHandle;
    }

    REG_FCIE_CLRBIT(FCIE_SD_MODE, BIT_CLK_EN);

	return 0;

ErrorHandle:

	return 1;

}

//
// skew1: 0~17 (18 steps)
// skew2: 0~8  ( 9 steps)
// skew3: 0~8  ( 9 steps)
// skew4: 0~17 (18 steps)

void HalSdio_SetSkew(U8 u8SkewIdx, U32 u32SkewValue)
{
	//printf("\nHalSdio_SetSkew4(%d) . . . ", u32Skew4);

	switch(u8SkewIdx)
	{
		case 1:
			if(u32SkewValue>17) goto ErrorHandle;

			REG_FCIE_CLRBIT(reg_sdiopll_0x03, BIT_SKEW1_MASK);
			if(u32SkewValue<9)
			{
				REG_FCIE_CLRBIT(reg_sdiopll_0x69, BIT3);
				REG_FCIE_SETBIT(reg_sdiopll_0x03, u32SkewValue);
			}
			else
			{
				REG_FCIE_SETBIT(reg_sdiopll_0x69, BIT3);
				REG_FCIE_SETBIT(reg_sdiopll_0x03, u32SkewValue-9);
			}
			break;

		case 2:
			if(u32SkewValue>8) goto ErrorHandle;

			REG_FCIE_CLRBIT(reg_sdiopll_0x03, BIT_SKEW2_MASK);
			REG_FCIE_SETBIT(reg_sdiopll_0x03, u32SkewValue<<4);
			break;

		case 3:
			if(u32SkewValue>8) goto ErrorHandle;

			REG_FCIE_CLRBIT(reg_sdiopll_0x03, BIT_SKEW3_MASK);
			REG_FCIE_SETBIT(reg_sdiopll_0x03, u32SkewValue<<8);
			break;

		case 4:
			if(u32SkewValue>17) goto ErrorHandle;

			REG_FCIE_CLRBIT(reg_sdiopll_0x03, BIT_SKEW4_MASK);
			if(u32SkewValue<9)
			{
				REG_FCIE_CLRBIT(reg_sdiopll_0x6c, BIT7);
				REG_FCIE_SETBIT(reg_sdiopll_0x03, u32SkewValue<<12);
			}
			else
			{
				REG_FCIE_SETBIT(reg_sdiopll_0x6c, BIT7);
				REG_FCIE_SETBIT(reg_sdiopll_0x03, (u32SkewValue-9)<<12);
			}
			break;

		default:
			goto ErrorHandle;
			break;
	}

	return;

ErrorHandle:

	printf("SDErr: wrong skew index (%d) or wrong skew value (%d)\n", u8SkewIdx, u32SkewValue);

}

void HalSdio_SetTriggerLevel(U8 u8STrigLevel)
{
	REG_FCIE_CLRBIT(reg_sdiopll_0x20, BIT_TRIG_LEVEL_MASK);
	switch(u8STrigLevel)
	{
		case 0:
			break;
		case 1:
			REG_FCIE_SETBIT(reg_sdiopll_0x20, BIT_TRIG_LEVEL_1);
			break;
		case 2:
			REG_FCIE_SETBIT(reg_sdiopll_0x20, BIT_TRIG_LEVEL_2);
			break;
		case 3:
			REG_FCIE_SETBIT(reg_sdiopll_0x20, BIT_TRIG_LEVEL_3);
			break;
		case 4:
			REG_FCIE_SETBIT(reg_sdiopll_0x20, BIT_TRIG_LEVEL_4);
			break;
		case 5:
			REG_FCIE_SETBIT(reg_sdiopll_0x20, BIT_TRIG_LEVEL_5);
			break;
		case 6:
			REG_FCIE_SETBIT(reg_sdiopll_0x20, BIT_TRIG_LEVEL_6);
			break;
		case 7:
			REG_FCIE_SETBIT(reg_sdiopll_0x20, BIT_TRIG_LEVEL_7);
			break;
		default:
			printf("SdErr: wrong parameter for set trigger level\n");
			break;
	}
}

#endif


