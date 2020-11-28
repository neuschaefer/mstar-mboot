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
#include <common.h>
#include <command.h>
#include <mmc.h>
#include <part.h>
#include <malloc.h>
#include <asm/errno.h>
#include <asm/io.h>
#include "drvFCIE_config.h"

#ifdef SD_USE_FCIE5
#include  "drvFCIE5.h"
#else
#include "drvFCIE.h"
#endif
#define DRIVER_NAME "mstar-emmc"

extern U8 halFCIE_Platform_SetFcieClock(U32 u32Clock);

#define DBGMMC(X)   //X

struct fcie_regs {
	u32 mie_event;
	u32 mie_int_en;
	u32 mma_pri_reg;
	u32 miu_dma_addr_h;
	u32 miu_dma_addr_l;
	u32 card_event;
    u32 card_int_en;
    u32 card_det;
    u32 card_pwr;
    u32 force_int;
    u32 mie_path_ctl;
    u32 job_bl_cnt;
    u32 tr_bk_cnt;
    u32 rsp_size;
    u32 cmd_size;
    u32 card_wd_cnt;
    u32 sd_mode;
    u32 sd_ctl;
    u32 sd_sts;
    u32 ms_mode;
    u32 ms_ctl;
    u32 ms_sts;
    u32 cf_inf_ctl1;
    u32 cf_inf_ctl2;
    u32 cf_bus;
    u32 cf_stb_set;
    u32 cf_ctl;
    u32 sdio_ctl;
    u32 sdio_addrl;
    u32 sdio_addrh;
    u32 sdio_sts;
};

struct fcie_host {
	struct mmc          *mmc;
	struct fcie_regs    *base;
	int                 irq;
	int                 detect_irq;
	int                 dma;
	int                 do_dma;
	unsigned int        power_mode;

	struct mmc_cmd      *cmd;
	struct mmc_data     *data;

	unsigned int        dma_nents;
	unsigned int        datasize;
	unsigned int        dma_dir;

	u16                 rev_no;
	unsigned char       buswidth;

	int                 clock;
};

static struct fcie_host fcie_host;
static struct fcie_host *host = &fcie_host;
static int fcie_mmc_init(void);

extern unsigned char mmc_ddr_mode;

extern void halFCIE_Reset_Toggle_Count(void);
extern void halFCIE_Disable_Stop_Clock(void);

int board_mmc_init(bd_t *bis)
{
	fcie_mmc_init();
	return 0;
}
//extern U32 SD_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt);
U32 SD_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt)
{
	flush_cache(u32_DMAAddr, u32_ByteCnt);
	#ifdef CONFIG_MCU_ARM

	//printf("MIU0[%Xh], MIU1[%Xh]\n", CONFIG_MIU0_BUSADDR, CONFIG_MIU1_BUSADDR);
	if(u32_DMAAddr < CONFIG_MIU1_BUSADDR) // MIU0
	{
		//REG_FCIE_CLRBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
		return  (u32_DMAAddr - CONFIG_MIU0_BUSADDR);
	}
	else
	{
		// REG_FCIE_SETBIT(FCIE_MIU_DMA_26_16, BIT_MIU1_SELECT);
		printf("MIU1\n");
		return  (u32_DMAAddr - CONFIG_MIU1_BUSADDR);
	}
	#endif
}

#ifdef SD_USE_FCIE5

static __inline void fcie_dump_mem_line(unsigned char *buf, U32 cnt)
{
	U32 i;

	printf("  0x%08X: ", (U32)buf);
	for (i= 0; i < cnt; i++)
		printf("%02Xh ", buf[i]);

	printf(" | ");

	for (i = 0; i < cnt; i++)
		printf("%c", (buf[i] >= 32 && buf[i] < 128) ? buf[i] : '.');

	printf("\n");
}

void fcie_dump_mem(unsigned char *buf, U32 cnt)
{
	U32 i;

	for (i= 0; i < cnt; i+= 16)
		fcie_dump_mem_line(buf + i, 16);
}

//static U8 temp_buffer[0x2000];

/*static void fcie_setup_data(struct fcie_host *host, struct mmc_data *data)
{
	unsigned int nob = data->blocks;
	unsigned int blksz = data->blocksize;
	unsigned int datasize = nob * blksz;
    //unsigned int bufaddr;
	unsigned int u32BusAddr;
	unsigned int u32DeviceAddr;

	//printf("fcie setup data: data->blocks = %d, data->blocksize = %d\n", data->blocks, data->blocksize);
	//printf(" ... adtc %d ... ", data->blocks*data->blocksize);

	// unsigned int job_bl_cnt_reg = (unsigned int)(&host->base->job_bl_cnt);
	// unsigned int sdio_ctl_reg = (unsigned int)(&host->base->sdio_ctl);
	// unsigned int sdio_addrl_reg = (unsigned int)(&host->base->sdio_addrl);
	// unsigned int sdio_addrh_reg = (unsigned int)(&host->base->sdio_addrh);

	REG_FCIE_W(FCIE_BLK_SIZE, data->blocksize);

	host->data = data;
    DBGMMC(printf("fcie_setup_data(%d,%d)\n", nob,blksz));

    if (nob > 4095)
        DBGMMC(printf("fcie:error job cnt > 4095!\n"));

	//if (data->dma==ADMA_MODE)
	  // REG(FCIE_JOB_BL_CNT)=1;
	//else
	REG(FCIE_JOB_BL_CNT)=nob;
	REG(FCIE_BLK_SIZE)=blksz;
	//writew(nob, job_bl_cnt_reg);
	//writew(blksz+0x8000, sdio_ctl_reg);  // Use the byte mode
	host->datasize = datasize;

	if (host->data->flags & MMC_DATA_READ)
	{
		//printf("sd read addr handle\n");

		u32BusAddr = (unsigned int)data->dest;
		//u32BusAddr = temp_buffer;
		//u32BusAddr = 0x20400000;

		flush_cache(u32BusAddr, 0x200);
		Chip_Flush_Memory();

		//invalidate_dcache_range((ulong)u32BusAddr, datasize);
	}
	else
	{
		u32BusAddr = (unsigned int)data->src;
		flush_cache(u32BusAddr, datasize);
	}

	// printf("bufaddr:0x%X, size:%d\n", bufaddr, datasize);
	// halFCIE_Flush_Cache(bufaddr, datasize);
	// bufaddr = halFCIE_PHY2MIUAddr(bufaddr);


	u32DeviceAddr = SD_translate_DMA_address_Ex(u32BusAddr, nob*blksz);

	//printf("%08Xh --> %08Xh\n", u32BusAddr, u32DeviceAddr);

    REG(FCIE_MIU_DMA_ADDR_15_0) = u32DeviceAddr & 0xFFFF;
    REG(FCIE_MIU_DMA_ADDR_31_16) = u32DeviceAddr>>16;

	//printf("MIU addr = %04X%04Xh\n", REG(FCIE_MIU_DMA_ADDR_31_16), REG(FCIE_MIU_DMA_ADDR_15_0));

	//fcie_dump_mem(u32BusAddr, (nob*blksz>0x200)?0x200:nob*blksz);

#if 0
	if (data->dma==ADMA_MODE)
	{
		REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0, 0x10 & 0xFFFF);
		REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16,0x10 >> 16);
	}
	else
#endif
	{
		REG(FCIE_MIU_DMA_LEN_15_0)=datasize & 0xffff;
		REG(FCIE_MIU_DMA_LEN_31_16)=(datasize >> 16);
	}

    //writew(bufaddr, sdio_addrl_reg);
    //writew((bufaddr>>16), sdio_addrh_reg);

}*/

#else
static void fcie_setup_data(struct fcie_host *host, struct mmc_data *data)
{
	unsigned int nob = data->blocks;
	unsigned int blksz = data->blocksize;
	unsigned int datasize = nob * blksz;
    unsigned int bufaddr;

    unsigned int job_bl_cnt_reg = (unsigned int)(&host->base->job_bl_cnt);
    unsigned int sdio_ctl_reg = (unsigned int)(&host->base->sdio_ctl);
    unsigned int sdio_addrl_reg = (unsigned int)(&host->base->sdio_addrl);
    unsigned int sdio_addrh_reg = (unsigned int)(&host->base->sdio_addrh);

	host->data = data;
    DBGMMC(printf("fcie_setup_data(%d,%d)\n", nob,blksz));

    if (nob > 4095)
        DBGMMC(printf("fcie:error job cnt > 4095!\n"));

	writew(nob, job_bl_cnt_reg);
	writew(blksz+0x8000, sdio_ctl_reg);  // Use the byte mode
	host->datasize = datasize;
        if (host->data->flags & MMC_DATA_READ) {
                 bufaddr = (unsigned int)data->dest;
                 flush_cache(bufaddr, datasize);
                 invalidate_dcache_range((ulong)bufaddr, datasize);
                }
		else
                {
                  bufaddr = (unsigned int)data->src;
                  flush_cache(bufaddr, datasize);

                }


	DBGMMC(printf("bufaddr:0x%X, size:%d\n", bufaddr, datasize));
   // halFCIE_Flush_Cache(bufaddr, datasize);
   // bufaddr = halFCIE_PHY2MIUAddr(bufaddr);


   bufaddr = SD_translate_DMA_address_Ex(bufaddr,nob*blksz);

    writew(bufaddr, sdio_addrl_reg);
    writew((bufaddr>>16), sdio_addrh_reg);

}
#endif

#if 0

static int fcie_start_cmd(struct fcie_host *host, struct mmc_cmd *cmd)
{
    CMD_RSP_INFO CmdRspInfo={0};

    if (host->cmd != NULL)
		printf("fcie_mmc : error!\n");
	host->cmd = cmd;

   // printf("[CMD %d][Arq 0x%x]\n", cmd->cmdidx, cmd->cmdarg);

	switch (cmd->resp_type) {
	case MMC_RSP_R1: /* short CRC, OPCODE */
	case MMC_RSP_R1b:/* short CRC, OPCODE, BUSY */
        CmdRspInfo.RspType = RSP_TYPE_R1;
        CmdRspInfo.RspSize = 0x06;
		break;
	case MMC_RSP_R2: /* long 136 bit + CRC */
        CmdRspInfo.RspType = RSP_TYPE_R2;
        CmdRspInfo.RspSize = 17;
		break;
	case MMC_RSP_R3: /* short */
        CmdRspInfo.RspType = RSP_TYPE_R3;
        CmdRspInfo.RspSize = 0x06;
		break;
	case MMC_RSP_NONE:
        CmdRspInfo.RspType = RSP_TYPE_NO;
        CmdRspInfo.RspSize = 0;
		break;
	default:
		printf("mxcmci: unhandled response type 0x%x\n",
				cmd->resp_type);
		return -EINVAL;
	}

    CmdRspInfo.CardClock = host->clock;
    CmdRspInfo.CmdSize = 5;
    CmdRspInfo.CmdRsp.Command[0] = 0x40+cmd->cmdidx;
    cmd->cmdarg=swab32(host->cmd->cmdarg);

    //memcpy((u8*)&(CmdRspInfo.CmdRsp.Command[1]), (u8 *)&cmd->cmdarg, 4);
    CmdRspInfo.CmdRsp.Command[1] = cmd->cmdarg & 0xFF;
    CmdRspInfo.CmdRsp.Command[2] = (cmd->cmdarg >> 8) & 0xFF;
	CmdRspInfo.CmdRsp.Command[3] = (cmd->cmdarg >> 16) & 0xFF;
	CmdRspInfo.CmdRsp.Command[4] = cmd->cmdarg >> 24;

    if (host->data)
    {
        CmdRspInfo.CmdType = CMD_TYPE_ADTC;
        if (host->data->flags & MMC_DATA_WRITE)
            CmdRspInfo.Dir = DAT_WRITE;
        else
            CmdRspInfo.Dir = DAT_READ;
    }

    if( mmc_ddr_mode )
    {
        if( (host->cmd->cmdidx == 17) || (host->cmd->cmdidx == 18) )
        {
            halFCIE_Set_Read_Toggle_Count();
            halFCIE_Reset_Toggle_Count();
        }
        else if( (host->cmd->cmdidx == 24) || (host->cmd->cmdidx == 25) )
        {
            halFCIE_Set_Write_Toggle_Count();
            halFCIE_Reset_Toggle_Count();
            halFCIE_Disable_Stop_Clock();
        }
        else //if( host->cmd->cmdidx == 12 )
        {
            halFCIE_Disable_Stop_Clock();
        }
    }

    return (halFCIE_SendCmdEx(&CmdRspInfo, (u8 *)&(cmd->response[0])));

}
#endif

static void fcie_finish_request(struct fcie_host *host,
		struct mmc_cmd *cmd, struct mmc_data *data)
{
	host->cmd = NULL;
	host->data = NULL;
}
#ifdef SD_USE_FCIE5
static int fcie_read_response(struct fcie_host *host)
{
	struct mmc_cmd *cmd = host->cmd;
   // unsigned int sd_sts_reg = (unsigned int)(&host->base->sd_sts);
    u16 stat;

	if (!cmd)
		return 0;

    stat=REG(FCIE_SD_STATUS);
    FCIE_RIU_W16(FCIE_SD_STATUS, stat);

	if (cmd->resp_type == MMC_RSP_R3) {
		stat &= ~BIT_CMD_RSP_CERR;
    }

	if (stat & BIT_CMD_NO_RSP) {

        //if ((cmd->cmdidx!=8)&&(cmd->cmdidx!=55))
        printf("cmd[%d] timeout, stat: %04Xh\n", cmd->cmdidx,stat);
		printf("command no response\n");
		return TIMEOUT;

	} else if (stat & (BIT_CMD_RSP_CERR+ \
	                   BIT_DAT_WR_TOUT+  \
	                   BIT_DAT_WR_CERR+  \
	                   BIT_DAT_RD_CERR)    \
	           && cmd->resp_type & MMC_RSP_CRC) {
		printf("cmd crc error\n");
        printf("CMD%d stat=%04X\n", cmd->cmdidx, stat);
		return -EILSEQ;
	}

    if (cmd->resp_type & MMC_RSP_PRESENT) {
       // cmd->response[0]=swab32(cmd->response[0]);
       // cmd->response[1]=swab32(cmd->response[1]);
       // cmd->response[2]=swab32(cmd->response[2]);
        //cmd->response[3]=swab32(cmd->response[3]);
 //       printf("\r\ncmd->response[0]:%lX\n", cmd->response[0]);
  //      printf("cmd->response[1]:%lX\n", cmd->response[1]);
    //    printf("cmd->response[2]:%lX\n", cmd->response[2]);
    //    printf("cmd->response[3]:%lX\n", cmd->response[3]);
    }

	return 0;
}

#else
static int fcie_read_response(struct fcie_host *host)
{
	struct mmc_cmd *cmd = host->cmd;
    unsigned int sd_sts_reg = (unsigned int)(&host->base->sd_sts);
    u16 stat;

	if (!cmd)
		return 0;


    stat=readw(sd_sts_reg);
    writew(stat, sd_sts_reg);


	if (cmd->resp_type == MMC_RSP_R3) {
		stat &= ~R_SD_CMDRSP_CERR;
    }

	if (stat & R_SD_CMD_NORSP) {
        //if ((cmd->cmdidx!=8)&&(cmd->cmdidx!=55))
		     printf("cmd[%d] timeout , stat:%x\n", cmd->cmdidx,stat);
		return TIMEOUT;
	} else if (stat & (R_SD_CMDRSP_CERR+ \
	                   R_SD_DAT_STSNEG+  \
	                   R_SD_DAT_STSERR+  \
	                   R_SD_DAT_CERR)    \
	           && cmd->resp_type & MMC_RSP_CRC) {
		printf("cmd crc error\n");
        printf("CMD%d stat=%04X\n", cmd->cmdidx, stat);
		return -EILSEQ;
	}

    if (cmd->resp_type & MMC_RSP_PRESENT) {
        cmd->response[0]=swab32(cmd->response[0]);
        cmd->response[1]=swab32(cmd->response[1]);
        cmd->response[2]=swab32(cmd->response[2]);
        cmd->response[3]=swab32(cmd->response[3]);
        //printf("\r\ncmd->response[0]:%lX\n", cmd->response[0]);
        //printf("cmd->response[1]:%lX\n", cmd->response[1]);
        //printf("cmd->response[2]:%lX\n", cmd->response[2]);
        //printf("cmd->response[3]:%lX\n", cmd->response[3]);
    }

	return 0;
}
#endif

#if 0
static int fcie_transfer_data(struct fcie_host *host)
{
	struct mmc_data *data = host->data;
	u8 stat;
	unsigned long length;

	length = data->blocks * data->blocksize;
	host->datasize = 0;

	if (data->flags & MMC_DATA_READ) {
		stat = halFCIE_TransferData(DAT_READ);
		if (stat)
			return stat;
		host->datasize += length;
		//halFCIE_Flush_Cache((ulong)data->dest, length); //Fix cache problem
	} else {
		stat = halFCIE_TransferData(DAT_WRITE);
		if (stat)
			return stat;
		host->datasize += length;
	}

	return 0;
}
#endif

static int fcie_finish_data(struct fcie_host *host, unsigned char stat)
{
	int data_error = 0;

	if (stat) {
		printf("fcie_mmc : request failed. status: 0x%08x\n",
				stat);
		if (stat == IO_ERROR) {
			data_error = -EILSEQ;
		} else if (stat == IO_TIME_OUT) {
			data_error = TIMEOUT;
		} else {
			data_error = -EIO;
		}
	}

	host->data = NULL;

	return data_error;
}

static int fcie_cmd_done(struct fcie_host *host)
{
	u8 datastat = 0;
	int ret;

	ret = fcie_read_response(host);

	if (ret) {
		fcie_finish_request(host, host->cmd, host->data);
		return ret;
	}

	if (!host->data) {
		fcie_finish_request(host, host->cmd, host->data);
		return 0;
	}

	//datastat = fcie_transfer_data(host);


	ret = fcie_finish_data(host, datastat);
	fcie_finish_request(host, host->cmd, host->data);

	return ret;
}

static U32 mstar_mci_setup_dma_info(struct mmc_data * pdata, CMD_RSP_INFO * pCmdRspInfo)
{
	U32 u32BusAddr, u32DeviceAddr, u32DmaLength = 0;
	//struct scatterlist  *pScatterList = 0;

	u32DmaLength = pdata->blocks * pdata->blocksize;
	//printf(" blocks = %d, block size = %d = ... adtc %ld ... ", pdata->blocks, pdata->blocksize, u32DmaLength);

	//BUG_ON(pData->sg_len!=1);

	//pScatterList = &(pData->sg[0]);
	//u32BusAddr = sg_dma_address(pScatterList);
	//u32DmaLeng = sg_dma_len(pScatterList);

	//BUG_ON((u32DmaLeng>>9)&0xFFFFF000);

	if (pdata->flags & MMC_DATA_READ)
	{
		u32BusAddr = (unsigned int)pdata->dest;
		//u32BusAddr = temp_buffer;
		//u32BusAddr = 0x20400000;
		flush_cache(u32BusAddr, u32DmaLength);
		Chip_Flush_Memory();
	}
	else
	{
		u32BusAddr = (unsigned int)pdata->src;
		flush_cache(u32BusAddr, u32DmaLength);
	}

	u32DeviceAddr = SD_translate_DMA_address_Ex(u32BusAddr, pdata->blocks * pdata->blocksize);

	pCmdRspInfo->DataPath = PATH_DMA;
	pCmdRspInfo->MiuAddr = u32DeviceAddr;
	pCmdRspInfo->pBufferAddr = NULL; // DMA don't need this field
	pCmdRspInfo->BlockSize = pdata->blocksize;
	pCmdRspInfo->BlockCount = pdata->blocks;

	return u32DmaLength;
}

#define U32BEND2LEND(X) ( ((X&0x000000FF)<<24) + ((X&0x0000FF00)<<8) + ((X&0x00FF0000)>>8) + ((X&0xFF000000)>>24) )
#define U16BEND2LEND(X) ( ((X&0x00FF)<<8) + ((X&0xFF00)>>8) )

static int fcie_request(struct mmc *mmc, struct mmc_cmd *cmd, struct mmc_data *data)
{
	struct fcie_host *host = mmc->priv;

#if 1

	U32 u32_err;
    CMD_RSP_INFO CmdRspInfo= {0};
	U8 * pTemp;
	U8 u8RspByteNum;
	U8 u8_i;

	CmdRspInfo.Command.Cmd.Index = cmd->cmdidx | 0x40;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(cmd->cmdarg);

	//printf("cmd->cmdarg = %08lX\n", cmd->cmdarg);
	//printf("CmdRspInfo.Command.Cmd.Arg = %08lX\n", CmdRspInfo.Command.Cmd.Arg);

	if(!data)
	{
		CmdRspInfo.CmdType = CMD_TYPE_NDTC; // simple command
	}
	else
	{
		CmdRspInfo.CmdType = CMD_TYPE_ADTC; // data transder command
	}

	switch (cmd->resp_type) {

		case MMC_RSP_R1:
		//case MMC_RSP_R5:
		//case MMC_RSP_R6:
		//case MMC_RSP_R7:
			CmdRspInfo.RspType = RSP_TYPE_R1;
			break;
		case MMC_RSP_NONE:
			CmdRspInfo.RspType = RSP_TYPE_NO;
			break;

		case MMC_RSP_R1b:
			CmdRspInfo.RspType = RSP_TYPE_R1b;
			break;
		case MMC_RSP_R2:
			CmdRspInfo.RspType = RSP_TYPE_R2;
			break;
		case MMC_RSP_R3:
		//case MMC_RSP_R4:
			CmdRspInfo.RspType = RSP_TYPE_R3;
			break;
		default:
			printf("SDIO Err: not support response type");
			break;
	}

	if(data) // command with data transfer
	{
		switch(data->flags) {
			case MMC_DATA_WRITE:
				//printf("MMC_DATA_WRITE, ");
				CmdRspInfo.ReadWriteDir = DIR_W;
				break;
			case MMC_DATA_READ:
				//printf("MMC_DATA_READ, ");
				CmdRspInfo.ReadWriteDir = DIR_R;
				break;
			default:
				printf("SD Err: data->flags = %08Xh, ", data->flags);
				break;
		}

		switch(host->buswidth)
		{
			case BUS_1_BIT:
				CmdRspInfo.BusWidth = BUS_1_BIT;
				//printf("1 bits\n");
				break;
			case BUS_4_BITS:
				CmdRspInfo.BusWidth = BUS_4_BITS;
				//printf("4 bits\n");
				break;
			case BUS_8_BITS:
				CmdRspInfo.BusWidth = BUS_8_BITS;
				//printf("8 bits\n");
				break;
		}

		#if 0 // defined(ENABLE_eMMC_ADMA_MODE) && ENABLE_eMMC_ADMA_MODE

			/*data->bytes_xfered = */mstar_mci_prepare_descriptors(data);
			mstar_mci_setup_descriptor_addr(&CmdRspInfo);

		#else

			/*data->bytes_xfered = */mstar_mci_setup_dma_info(data, &CmdRspInfo);

		#endif

	}


	u32_err = HalFcie_SendCommand(&CmdRspInfo);


	if(u32_err)
	{
		//cmd->error = -EIO;
		//printf("request happen error\n");

		return 1;
		if(data) // command with data transfer
		{
			// dump out what we read
			//cmd->data->bytes_xfered = 0;
		}
		//printf("send command fail\n");;
	}
	else
	{
		//cmd->error = 0;

		pTemp = (U8*)&(cmd->response[0]);
		u8RspByteNum = (cmd->resp_type&MMC_RSP_136)?16:4;

		//printf("u8RspByteNum = %d\n", u8RspByteNum);

		for(u8_i=0; u8_i<u8RspByteNum; u8_i++) {
			pTemp[ (3-(u8_i%4)) + ((u8_i/4)<<2) ] = HalFcie_CmdFifoGet((U8)(u8_i+1));
		}
	}


	#if 0
	if (data) {
		fcie_dump_mem((unsigned char*)data->dest, data->blocksize);
		//fcie_dump_mem(0x20400000, data->blocksize);
	}
	#endif

#else

	if (data) {
		fcie_setup_data(host, data);
	}

    fcie_start_cmd(host, cmd);

	#if 0
	if (data) {
		fcie_dump_mem((unsigned char*)data->dest, data->blocksize);
		//fcie_dump_mem(0x20400000, data->blocksize);
	}
	#endif

#endif

	return fcie_cmd_done(host);
}


static void fcie_set_ios(struct mmc *mmc)
{
	struct fcie_host *host = mmc->priv;

    //printf("fcie_set_ios: [%d KHz], [%d bits]\n", mmc->clock/1000, mmc->bus_width);

    if (mmc->bus_width == 8)
        halFCIE_SetBusWidth(&host->buswidth, BUS_8_BITS);
	else if (mmc->bus_width == 4)
		halFCIE_SetBusWidth(&host->buswidth, BUS_4_BITS);
	else
		halFCIE_SetBusWidth(&host->buswidth, BUS_1_BIT);

    host->clock = mmc->clock/1000;

	if(host->clock)
	{
		halFCIE_Platform_SetFcieClock(host->clock);
        halFCIE_OpenClock(1);
	}
	else
	{
		halFCIE_OpenClock(0);
	}

}


static int fcie_init(struct mmc *mmc)
{
	halFCIE_Init();
	return 0;
}

static int fcie_initialize(void)
{
	struct mmc *mmc = NULL;

	mmc = malloc(sizeof(struct mmc));

	if (!mmc)
		return -ENOMEM;
	memset(mmc, 0, sizeof(struct mmc));

	sprintf(mmc->name, DRIVER_NAME);
	mmc->send_cmd = fcie_request;
	mmc->set_ios = fcie_set_ios;
	mmc->init = fcie_init;

    mmc->host_caps =  MMC_MODE_4BIT;
	mmc->host_caps |= MMC_MODE_HS;

	host->base = (struct fcie_regs *)RIU_BASE_FCIE;
	mmc->priv = host;
	host->mmc = mmc;

	mmc->voltages = MMC_VDD_27_28 | MMC_VDD_28_29 | MMC_VDD_29_30 | MMC_VDD_30_31 | MMC_VDD_31_32 |
					MMC_VDD_32_33 | MMC_VDD_33_34 | MMC_VDD_34_35 | MMC_VDD_35_36;

	mmc->f_min =   300000; // 300KHz
	mmc->f_max = 30000000; //  50MHz

	mmc_register(mmc);

	return 0;
}

int fcie_mmc_init(void)
{
	return fcie_initialize();
}


