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
#ifndef SD_USE_FCIE5

#include <common.h>
#include <mmc.h>
#include "drvFCIE.h"

/**************************************
* Macro define
**************************************/
#define TIMEOUT_NORMAL 1000  // 1000ms
#define _halFCIE_ClearErrSts() do { \
    REG(SD_STS) = (R_SD_CMDRSP_CERR+R_SD_CMD_NORSP+R_SD_DAT_STSNEG+R_SD_DAT_STSERR+R_SD_DAT_CERR); \
} while(0)

volatile U32 *_pu32CMD_RSP_BUF = (volatile U32 *)(CIF_C_ADDR);

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
// must enable R_SD_EN in MIE_PATH_CTL first
static U8 _halFCIE_GetCIFC(U8 u8addr)
{
    U32 u32Tmp;

    u32Tmp = _pu32CMD_RSP_BUF[u8addr>>1];

    if(u8addr&0x1)
    {
        return(u32Tmp>>8);
    }
    else
    {
        return(u32Tmp&0xFF);
    }

}

/*********************************************************************
*
*   PROCEDURE NAME:
*       _halFCIE_SetCIFC
*
*   DESCRIPTION:
*       Set CIFIFO byte value
*   NOTE:
*
*********************************************************************/
// must enable R_SD_EN in MIE_PATH_CTL first
static void _halFCIE_SetCIFC(U8 u8addr, U8 u8value)
{

    U16 u16Tmp;

    u16Tmp = _pu32CMD_RSP_BUF[u8addr>>1]; // read modify write

    if(u8addr & 1)
    {
        u16Tmp = (u8value<<8) + (u16Tmp&0xFF);
    }
    else
    {
        u16Tmp = (u16Tmp&0xFF00)+u8value;
    }

    _pu32CMD_RSP_BUF[u8addr>>1] = u16Tmp;

}

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
    halFCIE_Platform_InitChiptop();

    FCIE_RIU_W16(MIE_PATH_CTL, 0x0000);
    FCIE_RIU_W16(MIE_EVENT   , 0xFFFF);

    halFCIE_Platform_Reset_Fcie();

    // Set FCIE to bypass mode
#if ENABLE_AMBER3
    FCIE_RIU_W16(EMMC_BOOT_CONFIG, 0x0400);
#elif ENABLE_AGATE
    FCIE_RIU_W16(EMMC_BOOT_CONFIG, 0x0D00);
#elif ENABLE_EINSTEIN || ENABLE_NAPOLI || ENABLE_MONACO || ENABLE_MUJI || ENABLE_CELTICS
    FCIE_RIU_16_OF(EMMC_BOOT_CONFIG, 0x1f00);	
    FCIE_RIU_16_ON(EMMC_BOOT_CONFIG, WBIT10);	

#elif ENABLE_NIKE || ENABLE_MADISON || ENABLE_MIAMI || ENABLE_NADAL || ENABLE_CLIPPERS
    FCIE_RIU_16_OF(EMMC_BOOT_CONFIG, 0x1f00);	
	
#endif
  #ifdef USE_SD_MODE
      FCIE_RIU_16_OF(SD_MODE,WBIT09);	//SDIO mode
  #else
    FCIE_RIU_16_ON(SD_MODE,WBIT09);	//SDIO mode
    #endif
 #ifdef SDR_MODE
    FCIE_RIU_16_ON(NC_REORDER,WBIT15);
 #else
     FCIE_RIU_16_ON(EMMC_BOOT_CONFIG, WBIT10);	//BYPASS mode
 #endif


    _halFCIE_SetupMiuBurstCtrl();
}

void halFCIE_DumpRegister(void)
{
    U16 i;

    printf("\nCHIPTOP:\n");
	printf("allpadin: %04X\n", FCIE_RIU_R16(ALL_PAD_IN));
	printf("SD pad: %04X\n", FCIE_RIU_R16(SD_TOP_CFG));
	printf("PCM pad: %04X\n", FCIE_RIU_R16(PCMCIA_TOP_CFG));
	printf("eMMC pad: %04X\n", FCIE_RIU_R16(EMMC_TOP_CFG));
	printf("nand pad: %04X\n", FCIE_RIU_R16(NAND_TOP_CFG));
    printf("eMMC force boot: %04X\n", FCIE_RIU_R16(EMMC_BOOT_CFG));

    printf("\nCLKGEN0:\n");
	printf("fcie clk: %04X\n", FCIE_RIU_R16(REG_CLK_NFIE));

    printf("\nFCIE3:\r\n");

    for(i=0; i<0x80; i++)
    {
        if(i%8==0) printf("%02X: ", (i/8)*8);
        printf("0x%04X ", FCIE_RIU_R16(MIE_EVENT+(i<<FCIE_OffShift)) );
        if(i%8==7) printf(":%02X\r\n", ((i/8)*8)+7);
    }

    printf("\nFCIE3 debug ports:\n");
	for(i=0; i<=7; i++)
	{
		// Enable debug ports
		FCIE_RIU_16_OF(TEST_MODE, (WBIT10|WBIT09|WBIT08));
		FCIE_RIU_16_ON(TEST_MODE, i<<8);

		// Dump debug ports
		printf("\nDebug Mode \033[31m%d:\033[m\n", i);
		printf("DBus[15:0]=\033[34m%04X\033[m\n", FCIE_RIU_R16(DEBUG_BUS0));
		printf("DBus[23:16]=\033[34m%04X\033[m\n", FCIE_RIU_R16(DEBUG_BUS1));
	}
}

void halFCIE_OpenClock(U8 On_off)
{
    if (On_off)
        FCIE_RIU_16_ON(SD_MODE, R_SD_CLK_EN);
	else
		FCIE_RIU_16_OF(SD_MODE, R_SD_CLK_EN);
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
void halFCIE_EnableCardInf(U8 u8MIE_PATH)
{
    U8 u8Tmp;

    u8Tmp = FCIE_RIU_R16(MIE_PATH_CTL);
    if(u8Tmp == u8MIE_PATH)
        return;

    FCIE_RIU_R16(SD_CTL)  &= ~(R_SD_DTRX_EN+R_SD_CMD_EN+R_SD_RSP_EN+R_SD_RSPR2_EN+R_SD_DTRX_DIR);
    FCIE_RIU_R16(SD_MODE) &= ~(R_SD_DEST+R_MMC_BUS_TEST);

    FCIE_RIU_W16(MIE_PATH_CTL, 0x00);
    //halFCIE_Platform_Reset_Fcie();
    FCIE_RIU_W16(MIE_PATH_CTL, u8MIE_PATH);
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
E_IO_STS halFCIE_SendCmdEx(CMD_RSP_INFO * pCmdRspInfo, U8 *rsp)
{
    E_IO_STS IoSts=IO_SUCCESS;
    U32 u32TimeMs;
    U8 i, au8_temp[6];
    U32 timeout = TIMEOUT_NORMAL;   

//    if((pCmdRspInfo->CmdRsp.Command[0]- 0x40) == MMC_CMD_ERASE) {
     //  timeout = *((U32 *)rsp);       
   // }

    _halFCIE_ClearErrSts();

    halFCIE_EnableCardInf(R_SD_EN);

    halFCIE_Platform_SetFcieClock(pCmdRspInfo->CardClock);

    //FCIE_RIU_16_ON(SD_MODE, R_SD_CLK_EN+R_SD_CS_EN+R_SD_DATSYNC);
    FCIE_RIU_16_ON(SD_MODE, R_SD_CLK_EN+R_SD_CS_EN);

    //FCIE_RIU_16_OF(SDIO_CTL, R_SDIO_BLK_MOD); // Some cmd use byte mode

    REG(CMD_SIZE) = pCmdRspInfo->CmdSize; // hardware generate the last CRC byte automatically

    if( pCmdRspInfo->RspSize )
    REG(RSP_SIZE) = pCmdRspInfo->RspSize-1; // hardware check the last CRC byte automatically
    else
        REG(RSP_SIZE) = pCmdRspInfo->RspSize;

    LABEL_CIFC_SET:
    for(i=0; i<pCmdRspInfo->CmdSize; i++)
    {
        _halFCIE_SetCIFC(i, pCmdRspInfo->CmdRsp.Command[i]);

		au8_temp[i] = _halFCIE_GetCIFC(i);
		if(au8_temp[i] != pCmdRspInfo->CmdRsp.Command[i])
			goto LABEL_CIFC_SET;
    }

    if(pCmdRspInfo->CmdType==CMD_TYPE_ADTC)
    {
        // FCIE patch, need when MIU clock slow or CPU fast
        u32TimeMs = 0;
        while(1)
        {
            if(FCIE_RIU_R16(MMA_PRIORITY)&R_FIFO_CLK_RDY)
            {
                break;
            }

            if(++u32TimeMs==0x3FFFF)
            {
                printf("Error!!! time out in wait FIFO clock ready!\r\n");
                printf("MMA_PRIORITY = 0x%04X\r\n", FCIE_RIU_R16(MMA_PRIORITY));
                printf("MIE_PATH   = 0x%04X\r\n",   FCIE_RIU_R16(MIE_PATH_CTL)  );
                goto ErrorHandleEx;
            }
        }
    }
    
    if(halFCIE_SDWaitD0High(timeout))
    {
        goto ErrorHandleEx;
    }

    if(pCmdRspInfo->RspSize)
    {
        if(pCmdRspInfo->CmdType==CMD_TYPE_ADTC)
        {
            if(pCmdRspInfo->Dir == DAT_READ)
            {
               FCIE_RIU_16_OF(MMA_PRIORITY, R_JOB_RW_DIR); // set read direction
               REG(MIE_PATH_CTL) = R_SD_EN+R_MMA_ENABLE; // MIU start transfer when write.
               REG(SD_CTL) = (R_SD_CMD_EN+R_SD_RSP_EN+R_SD_DTRX_EN);
            }
            else
            {
               FCIE_RIU_16_ON(MMA_PRIORITY, R_JOB_RW_DIR); // set write direction
               REG(MIE_PATH_CTL) = R_SD_EN+R_MMA_ENABLE; // MIU start transfer when write.
               REG(SD_CTL) = (R_SD_CMD_EN+R_SD_RSP_EN);
            }
        }
        else if(pCmdRspInfo->RspType==RSP_TYPE_R2)
        {
            REG(SD_CTL) = (R_SD_CMD_EN+R_SD_RSP_EN+R_SD_RSPR2_EN);
        }
        else
        {
            REG(SD_CTL) = (R_SD_CMD_EN+R_SD_RSP_EN);
        }
    }
    else // no response need
    {
        REG(SD_CTL) = (R_SD_CMD_EN);
    }

    IoSts = halFCIE_Platform_WaitMieEvent(R_SD_CMD_END, SD_TIMEOUT_VALUE);
    if(IoSts)
    {
        goto ErrorHandleEx;
    }

    if(halFCIE_SDWaitD0High(timeout))
    {
        goto ErrorHandleEx;
    }

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

    return IoSts;

ErrorHandleEx:

    printf("send cmd fial 0x%02X!\r\n", IoSts);

    return IO_TIME_OUT;
}

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
E_IO_STS halFCIE_TransferData(E_DAT_DIR eDir)
{
    E_IO_STS u8Err=IO_SUCCESS;


    if(eDir==1)
    {   
        if (halFCIE_SDWaitD0High(TIMEOUT_NORMAL))    //For compatibility of slower MMC cards
        {
            printf("Error!!! wait D0 high fail 3!\r\n");
            u8Err = IO_TIME_OUT;
            goto TransDatErr;
        }
        REG(SD_CTL) = R_SD_DTRX_DIR+R_SD_DTRX_EN; // start write DMA
    }
    u8Err = halFCIE_Platform_WaitMieEvent(R_CARD_DMA_END+R_MMA_LAST_DONE_Z, SD_DMA_TIMEOUT_VALUE);
	//u8Err = halFCIE_Platform_WaitMieEvent(R_CARD_DMA_END+R_MMA_LAST_DONE_Z, SD_DMA_TIMEOUT_VALUE * 120 );
	
    halFCIE_Platform_ClearEvent(R_CARD_DMA_END+R_MMA_LAST_DONE_Z+R_SD_DATA_END+R_MMA_DATA_END);

    if( REG(SD_STS) & (R_SD_DAT_CERR+R_SD_DAT_STSERR+R_SD_DAT_STSNEG) )
    {
        printf("Transfer data have IO_ERROR, SD_STS = 0x%04X\r\n", FCIE_RIU_R16(SD_STS));
        _halFCIE_ClearErrSts();
        halFCIE_Platform_Reset_Fcie();
        u8Err = IO_ERROR;
    }
TransDatErr:

    return (u8Err);

}

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
    U16 u16RegData;
    U32 Count = 0;

    while(1)
    {
        //printf("SD_STS = 0x%04X\r\n", FCIE_RIU_R16(SD_STS));

        u16RegData = FCIE_RIU_R16(SD_STS);
        if(u16RegData&R_SD_DAT0)
        {
            return (IO_SUCCESS);
        }

        FCIE_DELAY_MS(1);
        if(++Count==timeout) //erase time out (1000 always timeout)
        {
            printf("_DrvSDMMC_wDat0Hi Time Out\n");
            return (IO_TIME_OUT);
        }
    }
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
    FCIE_RIU_16_OF(SD_MODE, R_SD_4BITS+R_SD_8BITS);

    switch(DataBus)
    {
        case BUS_1_BIT:
            *pu8BusWidth = BUS_1_BIT;
            break;
        case BUS_4_BITS:
            FCIE_RIU_16_ON(SD_MODE, R_SD_4BITS);
            *pu8BusWidth = BUS_4_BITS;
            break;
        case BUS_8_BITS:
            FCIE_RIU_16_ON(SD_MODE, R_SD_8BITS);
            *pu8BusWidth = BUS_8_BITS;
            break;
        default:
            printf("wrong para in halFCIE_SetBusWidth()\r\n");
            return IO_ERROR;
    }
    return IO_SUCCESS;
}
#endif
