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
/*
 * Copyright 2008, Freescale Semiconductor, Inc
 * Andy Fleming
 *
 * Based vaguely on the Linux code
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <config.h>
#include <common.h>
#include <command.h>
#include <mmc.h>
#include <part.h>
#include <malloc.h>
#include <linux/list.h>
#include <div64.h>
#include "../../inc/api/drv_eMMC.h"
//#include <MsUboot.h>

static struct list_head mmc_devices;
static int cur_dev_num = -1;

unsigned char mmc_ddr_mode = 0;

extern void udelay (unsigned long usec);
extern void * memcpy(void * dest,const void *src,size_t count);
extern int board_mmc_init(bd_t *bis);
extern int eMMC_mmc_Init(struct mmc* mmc);

int __board_mmc_getcd(u8 *cd, struct mmc *mmc) {
	return -1;
}

int board_mmc_getcd(u8 *cd, struct mmc *mmc)__attribute__((weak,
	alias("__board_mmc_getcd")));

int mmc_trace = 0;

int mmc_send_cmd(struct mmc *mmc, struct mmc_cmd *cmd, struct mmc_data *data)
{
	if (mmc_trace == 1)
	{
		int ret;
		int i;
		u8 *ptr;

		printf("CMD_SEND:%d\n", cmd->cmdidx);
		printf("\t\tARG\t\t\t 0x%08X\n", cmd->cmdarg);
		printf("\t\tFLAG\t\t\t %d\n", cmd->flags);
		ret = mmc->send_cmd(mmc, cmd, data);
		switch (cmd->resp_type) {
			case MMC_RSP_NONE:
				printf("\t\tMMC_RSP_NONE\n");
				break;
			case MMC_RSP_R1:
				printf("\t\tMMC_RSP_R1,5,6,7 \t 0x%08X \n",
						cmd->response[0]);
				break;
			case MMC_RSP_R1b:
				printf("\t\tMMC_RSP_R1b\t\t 0x%08X \n",
						cmd->response[0]);
				break;
			case MMC_RSP_R2:
				printf("\t\tMMC_RSP_R2\t\t 0x%08X \n",
						cmd->response[0]);
				printf("\t\t          \t\t 0x%08X \n",
						cmd->response[1]);
				printf("\t\t          \t\t 0x%08X \n",
						cmd->response[2]);
				printf("\t\t          \t\t 0x%08X \n",
						cmd->response[3]);
				printf("\n");
				printf("\t\t\t\t\tDUMPING DATA\n");
				for (i = 0; i < 4; i++) {
					int j;
					printf("\t\t\t\t\t%03d - ", i*4);
					ptr = (u8*)(&cmd->response[i]);
					ptr += 3;
					for (j = 0; j < 4; j++)
						printf("%02X ", *ptr--);
					printf("\n");
				}
				break;
			case MMC_RSP_R3:
				printf("\t\tMMC_RSP_R3,4\t\t 0x%08X \n",
						cmd->response[0]);
				break;
			default:
				printf("\t\tERROR MMC rsp not supported\n");
				break;
		}
		return ret;
	}
	else
	{
		return mmc->send_cmd(mmc, cmd, data);
	}

}

int mmc_switch(struct mmc *mmc, u8 set, u8 index, u8 value)
{
	struct mmc_cmd cmd;

	cmd.cmdidx = MMC_CMD_SWITCH;
	cmd.resp_type = MMC_RSP_R1b;
	cmd.cmdarg = (MMC_SWITCH_MODE_WRITE_BYTE << 24) |
		(index << 16) |
		(value << 8);
	cmd.flags = 0;

//	return mmc_send_cmd(mmc, &cmd, NULL);
	return eMMC_SetExtCSD(MMC_SWITCH_MODE_WRITE_BYTE, index, value); 
}

int mmc_set_blocklen(struct mmc *mmc, int len)
{
	struct mmc_cmd cmd;

	cmd.cmdidx = MMC_CMD_SET_BLOCKLEN;
	cmd.resp_type = MMC_RSP_R1;
	cmd.cmdarg = len;
	cmd.flags = 0;

	return mmc_send_cmd(mmc, &cmd, NULL);
}

struct mmc *find_mmc_device(int dev_num)
{
	struct mmc *m;
	struct list_head *entry;

	list_for_each(entry, &mmc_devices) {
		m = list_entry(entry, struct mmc, link);

		if (m->block_dev.dev == dev_num)
			return m;
	}

	printf("MMC Device %d not found\n", dev_num);

	return NULL;
}

static ulong
mmc_write_blocks(struct mmc *mmc, ulong start, lbaint_t blkcnt, const void*src)
{
	struct mmc_cmd cmd;
	struct mmc_data data;

	if ((start + blkcnt) > mmc->block_dev.lba) {
		printf("MMC: block number 0x%lx exceeds max(0x%lx)\n",
			start + blkcnt, mmc->block_dev.lba);
		return 0;
	}

	if (blkcnt > 1)
		cmd.cmdidx = MMC_CMD_WRITE_MULTIPLE_BLOCK;
	else
		cmd.cmdidx = MMC_CMD_WRITE_SINGLE_BLOCK;

	if (mmc->high_capacity)
		cmd.cmdarg = start;
	else
		cmd.cmdarg = start * mmc->write_bl_len;

	cmd.resp_type = MMC_RSP_R1;
	cmd.flags = 0;

	data.src = src;
	data.blocks = blkcnt;
	data.blocksize = mmc->write_bl_len;
	data.flags = MMC_DATA_WRITE;

	if (mmc_send_cmd(mmc, &cmd, &data)) {
		printf("mmc write failed\n");
		return 0;
	}

	if (blkcnt > 1) {
		cmd.cmdidx = MMC_CMD_STOP_TRANSMISSION;
		cmd.cmdarg = 0;
		cmd.resp_type = MMC_RSP_R1b;
		cmd.flags = 0;
		if (mmc_send_cmd(mmc, &cmd, NULL)) {
			printf("mmc fail to send stop cmd\n");
			return 0;
		}
	}

	return blkcnt;
}

static ulong
_mmc_bwrite(int dev_num, ulong start, lbaint_t blkcnt, unsigned long *src)
{
	lbaint_t cur, blocks_todo = blkcnt;

	struct mmc *mmc = find_mmc_device(dev_num);
	if (!mmc)
		return 0;

    if( !mmc_ddr_mode )
    {
	    if (mmc_set_blocklen(mmc, mmc->write_bl_len))
		    return 0;
    }

	do {
		/*
		 * The 4095 constraint comes from mstar hardware has
		 * only 12 bit width block number counter
		 */
     
#ifdef LED_FLICK_WHEN_SW_UPDATE
        {
            extern void do_Led_Flicker_Control(void);
            do_Led_Flicker_Control();
        }
#endif
		cur = (blocks_todo > 4095) ? 4095 : blocks_todo;
		if(mmc_write_blocks(mmc, start, cur, src) != cur)
			return 0;
		blocks_todo -= cur;
		start += cur;
		src += cur * mmc->write_bl_len;
	} while (blocks_todo > 0);

	return blkcnt;
}

static ulong
mmc_bwrite(int dev_num, ulong start, lbaint_t blkcnt, const void *src)
{
    int n;

	if( blkcnt > 0x800 )
	{
	    int nn = 0;
	    u32 cur_cnt = blkcnt;
	    int boffset = start;
	    int doffset = (int)src;

	    n = 0;

	    while( cur_cnt > 0 )
	    {
		    if( cur_cnt >= 0x800 )
		    {
		        nn = _mmc_bwrite(0, boffset, 0x800, (unsigned long *)(doffset));
		        boffset += 0x800;
		        doffset += 0x100000;
		        cur_cnt -= 0x800;
		    }
		    else
		    {
		        nn = _mmc_bwrite(0, boffset, cur_cnt, (unsigned long *)(doffset));
		        cur_cnt -= cur_cnt;
		    }

		    n += nn;
	    }
	}
	else
    {
        n = _mmc_bwrite(0, start, blkcnt, (unsigned long *)src);
    }

	return n;
}

int mmc_read_blocks(struct mmc *mmc, void *dst, ulong start, lbaint_t blkcnt)
{
	struct mmc_cmd cmd;
	struct mmc_data data;

	if ((start + blkcnt) > mmc->block_dev.lba) {
		printf("MMC: block number 0x%lx exceeds max(0x%lx)\n",
			start + blkcnt, mmc->block_dev.lba);
		return 0;
	}

	if (blkcnt > 1)
		cmd.cmdidx = MMC_CMD_READ_MULTIPLE_BLOCK;
	else
		cmd.cmdidx = MMC_CMD_READ_SINGLE_BLOCK;

	if (mmc->high_capacity)
		cmd.cmdarg = start;
	else
		cmd.cmdarg = start * mmc->read_bl_len;

	cmd.resp_type = MMC_RSP_R1;
	cmd.flags = 0;

	data.dest = dst;
	data.blocks = blkcnt;
	data.blocksize = mmc->read_bl_len;
	data.flags = MMC_DATA_READ;

	if (mmc_send_cmd(mmc, &cmd, &data))
		return 0;

	if (blkcnt > 1) {
		cmd.cmdidx = MMC_CMD_STOP_TRANSMISSION;
		cmd.cmdarg = 0;
		cmd.resp_type = MMC_RSP_R1b;
		cmd.flags = 0;
		if (mmc_send_cmd(mmc, &cmd, NULL)) {
			printf("mmc fail to send stop cmd\n");
			return 0;
		}
	}

	return blkcnt;
}

static ulong mmc_bread(int dev_num, ulong start, lbaint_t blkcnt, void *dst)
{
	lbaint_t cur, blocks_todo = blkcnt;

	if (blkcnt == 0)
		return 0;

	struct mmc *mmc = find_mmc_device(dev_num);
	if (!mmc)
		return 0;

	if ((start + blkcnt) > mmc->block_dev.lba) {
		printf("MMC: block number 0x%lx exceeds max(0x%lx)\n",
			start + blkcnt, mmc->block_dev.lba);
		return 0;
	}

    if( !mmc_ddr_mode )
    {
	    if (mmc_set_blocklen(mmc, mmc->read_bl_len))
		    return 0;
    }

	do {
		/*
		 * The 4095 constraint comes from mstar hardware has
		 * only 12 bit width block number counter
		 */
		cur = (blocks_todo > 4095) ? 4095 : blocks_todo;
		if(mmc_read_blocks(mmc, dst, start, cur) != cur)
			return 0;
		blocks_todo -= cur;
		start += cur;
		dst += cur * mmc->read_bl_len;
	} while (blocks_todo > 0);

	return blkcnt;
}

static ulong
mmc_erase_blocks(struct mmc *mmc, ulong start, lbaint_t blkcnt)
{
	struct mmc_cmd cmd;
    unsigned int ea_grp_size = 0, ea_timeout = 0;

	if ((start + blkcnt) > mmc->block_dev.lba) {
		printf("MMC: block number 0x%lx exceeds max(0x%lx)\n",
			start + blkcnt, mmc->block_dev.lba);
		return 0;
	}
    
    if((mmc->ext_csd[192] >= 5) && (mmc->ext_csd[EXT_CSD_HC_ERASE_GRP_SIZE]!=0))
    {
        if(mmc->ext_csd[EXT_CSD_ERASE_GROUP_DEF] != 0x1)
            mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_ERASE_GROUP_DEF, 1);
        ea_grp_size = mmc->ext_csd[EXT_CSD_HC_ERASE_GRP_SIZE]<<10; // unit 512B
    }else {    //not HC emmc, <=2G           
        ea_grp_size = (((mmc->csd[2]>>5)&0x1f)+1)*(((mmc->csd[2]>>10)&0x1f)+1); //unit 512B
    }

    ea_timeout = mmc->ext_csd[EXT_CSD_ERASE_TIMEOUT_MULT] * 300; //time out for one erase group size
    if(!ea_timeout)
        ea_timeout = 300;  //patch for kinston, >2G emmc

    if(!ea_grp_size)       
        ea_timeout = 60*1000;  
    else if(blkcnt >= ea_grp_size)
        ea_timeout *= (blkcnt/ea_grp_size);
        
    //step 1 erase group start address 
    cmd.cmdidx = MMC_CMD_ERASE_GROUP_START;
	if (mmc->high_capacity)
		cmd.cmdarg = start;
	else
		cmd.cmdarg = start * mmc->write_bl_len;
    //printf("step 1 erase group start 0x%08X\n", cmd.cmdarg);

	cmd.resp_type = MMC_RSP_R1;
	cmd.flags = 0;
	if (mmc_send_cmd(mmc, &cmd, NULL)) {
		printf("mmc erase failed\n");
		return 0;
	}
	
    //step 2 erase group end address  
    cmd.cmdidx = MMC_CMD_ERASE_GROUP_END;
	if (mmc->high_capacity)
		cmd.cmdarg = start + blkcnt - 1;
	else
		cmd.cmdarg = (start + blkcnt - 1) * mmc->write_bl_len;
    //printf("step 2 erase group end 0x%08X\n", cmd.cmdarg);

	cmd.resp_type = MMC_RSP_R1;
	cmd.flags = 0;
	if (mmc_send_cmd(mmc, &cmd, NULL)) {
		printf("mmc erase failed\n");
		return 0;
	}

    //step 3 erase operation start
    cmd.cmdidx = MMC_CMD_ERASE;
	cmd.cmdarg = 0;    //0x01 trim 

	cmd.resp_type = MMC_RSP_R1b;
	cmd.flags = 0;

    //set timeout value
    cmd.response[0] = ea_timeout;    //ms
    
	if (mmc_send_cmd(mmc, &cmd, NULL)) {
		printf("mmc erase failed\n");
		return 0;
	}
	
	return blkcnt;
}


static ulong
_mmc_berase(int dev_num, ulong start, lbaint_t blkcnt)
{
	struct mmc *mmc = find_mmc_device(dev_num);
	if (!mmc)
		return 0;
     
#ifdef LED_FLICK_WHEN_SW_UPDATE
        {
            extern void do_Led_Flicker_Control(void);
            do_Led_Flicker_Control();
        }
#endif		
	if(mmc_erase_blocks(mmc, start, blkcnt) != blkcnt)
	    return 0;

	return blkcnt;
}


static ulong
mmc_berase(int dev_num, ulong start, lbaint_t blkcnt)
{ 
    int nn = 0;

    if( blkcnt > 0 )
    {
        nn = _mmc_berase(0, start, blkcnt);
    }	

	return nn;
}

int mmc_go_idle(struct mmc* mmc)
{
	struct mmc_cmd cmd;
	int err;

	udelay(1000);

	cmd.cmdidx = MMC_CMD_GO_IDLE_STATE;
	cmd.cmdarg = 0;
	cmd.resp_type = MMC_RSP_NONE;
	cmd.flags = 0;

	err = mmc_send_cmd(mmc, &cmd, NULL);

	if (err)
		return err;

	udelay(2000);

	return 0;
}

int
sd_send_op_cond(struct mmc *mmc)
{
	int timeout = 1000;
	int err;
	struct mmc_cmd cmd;

	do {
		cmd.cmdidx = MMC_CMD_APP_CMD;
		cmd.resp_type = MMC_RSP_R1;
		cmd.cmdarg = 0;
		cmd.flags = 0;

		err = mmc_send_cmd(mmc, &cmd, NULL);

		if (err)
			return err;

		cmd.cmdidx = SD_CMD_APP_SEND_OP_COND;
		cmd.resp_type = MMC_RSP_R3;

		/*
		 * Most cards do not answer if some reserved bits
		 * in the ocr are set. However, Some controller
		 * can set bit 7 (reserved for low voltages), but
		 * how to manage low voltages SD card is not yet
		 * specified.
		 */
		cmd.cmdarg = mmc->voltages & 0xff8000;

		if (mmc->version == SD_VERSION_2)
			cmd.cmdarg |= OCR_HCS;

		err = mmc_send_cmd(mmc, &cmd, NULL);

		if (err)
			return err;

		udelay(1000);
	} while ((!(cmd.response[0] & OCR_BUSY)) && timeout--);

	if (timeout <= 0)
		return UNUSABLE_ERR;

	if (mmc->version != SD_VERSION_2)
		mmc->version = SD_VERSION_1_0;

	mmc->ocr = cmd.response[0];

	mmc->high_capacity = ((mmc->ocr & OCR_HCS) == OCR_HCS);
	mmc->rca = 0;

	return 0;
}

int mmc_send_op_cond(struct mmc *mmc)
{
    int timeout = 1000;
    struct mmc_cmd cmd;
    int err;

    /* Some cards seem to need this */
    mmc_go_idle(mmc);

    do {
        cmd.cmdidx = MMC_CMD_SEND_OP_COND;
        cmd.resp_type = MMC_RSP_R3;
        cmd.cmdarg = OCR_HCS | mmc->voltages;
        cmd.flags = 0;

        err = mmc_send_cmd(mmc, &cmd, NULL);

        if (err)
            return err;

        udelay(1000);
    } while (!(cmd.response[0] & OCR_BUSY) && timeout--);

    if (timeout <= 0)
        return UNUSABLE_ERR;

    mmc->version = MMC_VERSION_UNKNOWN;
    mmc->ocr = cmd.response[0];

    mmc->high_capacity = ((mmc->ocr & OCR_HCS) == OCR_HCS);
    mmc->rca = 0;

    return 0;
}


int mmc_send_ext_csd(struct mmc *mmc, char *ext_csd)
{
	struct mmc_cmd cmd;
	struct mmc_data data;
	int err;

	/* Get the Card Status Register */
	cmd.cmdidx = MMC_CMD_SEND_EXT_CSD;
	cmd.resp_type = MMC_RSP_R1;
	cmd.cmdarg = 0;
	cmd.flags = 0;

	data.dest = ext_csd;
	data.blocks = 1;
	data.blocksize = 512;
	data.flags = MMC_DATA_READ;

	//err = mmc_send_cmd(mmc, &cmd, &data);
	err = eMMC_GetExtCSD((U8*) ext_csd);

	return err;
}

int ext_csd_sectors;
int mmc_change_freq(struct mmc *mmc)
{
	char ext_csd[512];
	char cardtype;
	int err;

	mmc->card_caps = 0;

	/* Only version 4 supports high-speed */
	if (mmc->version < MMC_VERSION_4)
		return 0;

	//mmc->card_caps |= MMC_MODE_4BIT|MMC_MODE_8BIT;
	mmc->card_caps |= MMC_MODE_8BIT; //MMC_MODE_4BIT;

	err = mmc_send_ext_csd(mmc, ext_csd);

	if (err)
		return err;

    #if 0
	if(mmc->cid[0] == MOVINAND_ID) {
		printf("found MOVINAND_ID = %X\n", MOVINAND_ID);
	    if (ext_csd[212] || ext_csd[213] || ext_csd[214] || ext_csd[215])
		    mmc->high_capacity = 1;
	}
    #endif

	cardtype = ext_csd[196] & 0xf;

	err = mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_HS_TIMING, 1);

	if (err)
		return err;

	/* Now check to see that it worked */
	err = mmc_send_ext_csd(mmc, ext_csd);

	if (err)
		return err;

	/* No high-speed support */
	if (!ext_csd[185])
		return 0;

	/* High Speed is set, there are two types: 52MHz and 26MHz */
	if( cardtype & MMC_DDR_52MHZ_18_3V )    /* MMC supports 52MHz DDR 1.8/3V */
    {
        mmc_ddr_mode = 0;
        mmc->card_caps |= MMC_MODE_HS_52MHz | MMC_MODE_HS;
    }
    else if (cardtype & MMC_HS_52MHZ)
		mmc->card_caps |= MMC_MODE_HS_52MHz | MMC_MODE_HS;
	else
		mmc->card_caps |= MMC_MODE_HS;

	return 0;
}

int mmc_switch_part(int dev_num, unsigned int part_num)
{
    struct mmc *mmc = find_mmc_device(dev_num);

    if (!mmc)
        return -1;

    return mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_PART_CONF,
        (mmc->part_config & ~PART_ACCESS_MASK)| (part_num & PART_ACCESS_MASK));
}

int sd_switch(struct mmc *mmc, int mode, int group, u8 value, u8 *resp)
{
	struct mmc_cmd cmd;
	struct mmc_data data;

	/* Switch the frequency */
	cmd.cmdidx = SD_CMD_SWITCH_FUNC;
	cmd.resp_type = MMC_RSP_R1;
	cmd.cmdarg = (mode << 31) | 0xffffff;
	cmd.cmdarg &= ~(0xf << (group * 4));
	cmd.cmdarg |= value << (group * 4);
	cmd.flags = 0;

	data.dest = (char *)resp;
	data.blocksize = 64;
	data.blocks = 1;
	data.flags = MMC_DATA_READ;

	return mmc_send_cmd(mmc, &cmd, &data);
}

/* frequency bases */
/* divided by 10 to be nice to platforms without floating point */
int fbase[] = {
	10000,
	100000,
	1000000,
	10000000,
};

/* Multiplier values for TRAN_SPEED.  Multiplied by 10 to be nice
 * to platforms without floating point.
 */
int multipliers[] = {
	0,	/* reserved */
	10,
	12,
	13,
	15,
	20,
	25,
	30,
	35,
	40,
	45,
	50,
	55,
	60,
	70,
	80,
};

void mmc_set_ios(struct mmc *mmc)
{
	mmc->set_ios(mmc);
}

void mmc_set_clock(struct mmc *mmc, uint clock)
{
	if (clock > mmc->f_max)
		clock = mmc->f_max;

	if (clock < mmc->f_min)
		clock = mmc->f_min;

	mmc->clock = clock;

	mmc_set_ios(mmc);
}

void mmc_set_bus_width(struct mmc *mmc, uint width)
{
	mmc->bus_width = width;

	mmc_set_ios(mmc);
}

int mmc_slc_mode(struct mmc *mmc, u64 size, int reliable_write)
{
    int err;
    u64 ea_size, max_ea_size;

    if (!mmc->has_init)
    {
        err = mmc_send_ext_csd(mmc, mmc->ext_csd);
        if (err)
        {
            printf("read ecsd fail while set slc mode, err %d\n", err);
            return err;
        }
    }

    if (((mmc->ext_csd[192] < 5) || ((mmc->ext_csd[160] & 0x3) != 3)) && (size != 0))
    {
        printf("Enhanced attribute of partition is not supported, slc size should be 0!\r\n");
        return 0;
    }
    if ((reliable_write == 1) && (mmc->reliable_write == 0))
    {
        printf("Reliable write is not supported, should be 0!\n");
        return 0;
    }

    if (mmc->slc_size || (mmc->reliable_write == 2) || mmc->ext_csd[EXT_CSD_PARTITION_SETTING_COMPLETED])
    {
        printf("SLC mode or reliable write has been set, slc size is %lld bytes\n", mmc->slc_size);
        return 0;
    }

    if (!size && (reliable_write == 1))
    {
        mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_ERASE_GROUP_DEF, 1);
        mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_WR_REL_SET, 0x1f);
        // complete the partition configuration
        mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_PARTITION_SETTING_COMPLETED, 0x01);

        mmc->reliable_write = 2;

        while (1)
            printf("Please reset the board!!!!!! Reliable write would be active after reset!!!!!!\n");
    }

    if(size <= 0)
    {
        printf("Invalid slc size %llu bytes\n", size);
        return 1;        
    }

    ea_size = size / (mmc->ext_csd[221] * mmc->ext_csd[224]);
    ea_size >>= 19;
    max_ea_size = mmc->ext_csd[157] | ((u32)(mmc->ext_csd[158]) << 8)
    	             | ((u32)(mmc->ext_csd[159]) << 16);

    // 0xffffffff indicates max slc size
    if (size == 0xffffffff)
    {
        ea_size = max_ea_size;
        size = (max_ea_size << 19) * (mmc->ext_csd[221] * mmc->ext_csd[224]);
    }
    else if (ea_size > max_ea_size)
    {
        printf("Size exceeds max enhanced area, max size is: %lldMB\r\n",
            (max_ea_size * mmc->ext_csd[221] * mmc->ext_csd[224]) >> 1);
        return -1;
    }

    mmc->slc_size = (ea_size << 19) * (mmc->ext_csd[221] * mmc->ext_csd[224]);
    // slc size of input is not aligned
    if ((size != 0xffffffff) && (size != mmc->slc_size) && (ea_size < max_ea_size))
    {
        ea_size++;
        mmc->slc_size = (ea_size << 19) * (mmc->ext_csd[221] * mmc->ext_csd[224]);
    }

    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_ERASE_GROUP_DEF, 1);

    if ((reliable_write == 1) ||
        (((mmc->slc_size << 1) < mmc->capacity) && (mmc->reliable_write != 0)))
    {
        // set reliable write
        mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_WR_REL_SET, 0x1f);
        if (!reliable_write)
        {
            printf("Reliable write will be set to protect the whole emmc space!");
        }
    }
    
    #if 0
    // configure the general purpose area
    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_GP_SIZE_MULT_1_0, mmc->ext_csd[157]);
    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_GP_SIZE_MULT_1_1, mmc->ext_csd[158]);
    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_GP_SIZE_MULT_1_2, mmc->ext_csd[159]);

    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_GP_SIZE_MULT_2_0, 0);
    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_GP_SIZE_MULT_2_1, 0);
    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_GP_SIZE_MULT_2_2, 0);

    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_GP_SIZE_MULT_3_0, 0);
    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_GP_SIZE_MULT_3_1, 0);
    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_GP_SIZE_MULT_3_2, 0);

    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_GP_SIZE_MULT_4_0, 0);
    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_GP_SIZE_MULT_4_1, 0);
    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_GP_SIZE_MULT_4_2, 0);

    // configure the enhanced area, leave it as mlc

    // configure the attribute of these areas
    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_PARTITIONS_ATTRIBUTE, 2);
    #endif
    // configure the enhanced area
    // start address = 0
    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_ENH_START_ADDR_0, 0);
    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_ENH_START_ADDR_1, 0);
    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_ENH_START_ADDR_2, 0);
    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_ENH_START_ADDR_3, 0);
    // set size of enhanced area
    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_ENH_SIZE_MULT_0, (u8)(ea_size & 0xff));
    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_ENH_SIZE_MULT_1, (u8)((ea_size & 0xff00) >> 8));
    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_ENH_SIZE_MULT_2, (u8)((ea_size & 0xff0000) >> 16));

    // configure the attribute of these areas
    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_PARTITIONS_ATTRIBUTE, 1);

    // complete the partition configuration
    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_PARTITION_SETTING_COMPLETED, 1);

    printf("SLC partition size is %lld\n", mmc->slc_size);
    while (1)
        printf("Please reset the board!!!!!! SLC mode or reliable write will be active after reset!!!!!!\n");
	
    return 0;
}

int mmc_ecsd_read(struct mmc *mmc)
{
    int i, err;

    err = mmc_send_ext_csd(mmc, mmc->ext_csd);
    if (err)
    {
        printf("read ecsd register fail, err %d\n", err);
        return err;
    }

    for (i = 0; i < 512; i++)
        printf("ecsd[%d]:0x%x\r\n", i, mmc->ext_csd[i]);

    return 0;
}

int mmc_ecsd_write(struct mmc *mmc, u8 num, u8 mask, u8 value)
{
    int err;
    u8 tmp;

    err = mmc_send_ext_csd(mmc, mmc->ext_csd);
    if (err)
    {
        printf("read ecsd register fail, err %d\n", err);
        return err;
    }

    tmp = mmc->ext_csd[num];
    
    tmp &= ~mask;
    value &= mask;
    tmp |= value;
	
    mmc->ext_csd[num] = tmp;
    mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, num, tmp);
    
    return 0;
}

int mmc_startup(struct mmc *mmc)
{
    int err;
	uint mult, freq;
	u64 cmult, csize;
	struct mmc_cmd cmd;

	/* Put the Card in Identify Mode */
	cmd.cmdidx = MMC_CMD_ALL_SEND_CID;
	cmd.resp_type = MMC_RSP_R2;
	cmd.cmdarg = 0;
	cmd.flags = 0;

	err = mmc_send_cmd(mmc, &cmd, NULL);

	if (err)
		return err;

	memcpy(mmc->cid, cmd.response, 16);

	/*
	 * For MMC cards, set the Relative Address.
	 * For SD cards, get the Relatvie Address.
	 * This also puts the cards into Standby State
	 */
	cmd.cmdidx = SD_CMD_SEND_RELATIVE_ADDR;
	cmd.cmdarg = mmc->rca << 16;
	cmd.resp_type = MMC_RSP_R6;
	cmd.flags = 0;

	err = mmc_send_cmd(mmc, &cmd, NULL);

	if (err)
		return err;

	if (IS_SD(mmc))
		mmc->rca = (cmd.response[0] >> 16) & 0xffff;

	/* Get the Card-Specific Data */
	cmd.cmdidx = MMC_CMD_SEND_CSD;
	cmd.resp_type = MMC_RSP_R2;
	cmd.cmdarg = mmc->rca << 16;
	cmd.flags = 0;

	err = mmc_send_cmd(mmc, &cmd, NULL);

	if (err)
		return err;

	mmc->csd[0] = cmd.response[0];
	mmc->csd[1] = cmd.response[1];
	mmc->csd[2] = cmd.response[2];
	mmc->csd[3] = cmd.response[3];

	if (mmc->version == MMC_VERSION_UNKNOWN) {
		int version = (cmd.response[0] >> 26) & 0xf;

		switch (version) {
			case 0:
				mmc->version = MMC_VERSION_1_2;
				break;
			case 1:
				mmc->version = MMC_VERSION_1_4;
				break;
			case 2:
				mmc->version = MMC_VERSION_2_2;
				break;
			case 3:
				mmc->version = MMC_VERSION_3;
				break;
			case 4:
				mmc->version = MMC_VERSION_4;
				break;
			default:
				mmc->version = MMC_VERSION_1_2;
				break;
		}
	}

	/* divide frequency by 10, since the mults are 10x bigger */
	freq = fbase[(cmd.response[0] & 0x7)];
	mult = multipliers[((cmd.response[0] >> 3) & 0xf)];

	mmc->tran_speed = freq * mult;

	mmc->read_bl_len = 1 << ((cmd.response[1] >> 16) & 0xf);

	if (IS_SD(mmc))
		mmc->write_bl_len = mmc->read_bl_len;
	else
		mmc->write_bl_len = 1 << ((cmd.response[3] >> 22) & 0xf);

	#if 0
	if (mmc->high_capacity) {
		csize = (mmc->csd[1] & 0x3f) << 16
			| (mmc->csd[2] & 0xffff0000) >> 16;
		cmult = 8;
	} else {
		csize = (mmc->csd[1] & 0x3ff) << 2
			| (mmc->csd[2] & 0xc0000000) >> 30;
		cmult = (mmc->csd[2] & 0x00038000) >> 15;
	}
	#else
    csize = (mmc->csd[1] & 0x3ff) << 2
			| (mmc->csd[2] & 0xc0000000) >> 30;
	cmult = (mmc->csd[2] & 0x00038000) >> 15;
	#endif

	mmc->capacity = (csize + 1) << (cmult + 2);
	mmc->capacity *= mmc->read_bl_len;

	if (mmc->read_bl_len > 512)
		mmc->read_bl_len = 512;

	if (mmc->write_bl_len > 512)
		mmc->write_bl_len = 512;

	/* Select the card, and put it into Transfer Mode */
	cmd.cmdidx = MMC_CMD_SELECT_CARD;
	cmd.resp_type = MMC_RSP_R1b;
	cmd.cmdarg = mmc->rca << 16;
	cmd.flags = 0;
	err = mmc_send_cmd(mmc, &cmd, NULL);

	if (err)
		return err;

    #if 1
	if (!IS_SD(mmc) && (mmc->version >= MMC_VERSION_4) && 0xFFF==csize) {
		/* check  ext_csd version and capacity */
		err = mmc_send_ext_csd(mmc, mmc->ext_csd);
		if (!err & (mmc->ext_csd[192] >= 2)) {
			mmc->capacity = mmc->ext_csd[212] << 0  | mmc->ext_csd[213] << 8 |
					        mmc->ext_csd[214] << 16 | mmc->ext_csd[215] << 24;
			mmc->capacity *= 512;
		}
	}
    else
    {
        err = mmc_send_ext_csd(mmc, mmc->ext_csd);
        if (err)
		      return err;
    }
    #endif

    // reliable write is supported
    if ((mmc->ext_csd[EXT_CSD_WR_REL_SET] & 0x01) == 1) // reliable write is configured
        mmc->reliable_write = 2;
    else if((mmc->ext_csd[192] >= 5) && ((mmc->ext_csd[EXT_CSD_WR_REL_PARAM] & 0x1) == 0x1))
        mmc->reliable_write = 1;  // reliable write is supported but not configured
    else
        mmc->reliable_write = 0;  // reliable write is unsupported 


    if ((mmc->ext_csd[192] >= 5) && ((mmc->ext_csd[160] & 0x3) == 3))
    {
        mmc->slc_size = ((mmc->ext_csd[EXT_CSD_ENH_SIZE_MULT_0]
               | ((u32)(mmc->ext_csd[EXT_CSD_ENH_SIZE_MULT_1]) << 8)
    	       | ((u32)(mmc->ext_csd[EXT_CSD_ENH_SIZE_MULT_2]) << 16)) << 19)
    	       * mmc->ext_csd[221] * mmc->ext_csd[224];
        mmc->max_slc_size = ((mmc->ext_csd[157]
               | ((u32)(mmc->ext_csd[158]) << 8)
    	       | ((u32)(mmc->ext_csd[159]) << 16)) << 19)
    	       * mmc->ext_csd[221] * mmc->ext_csd[224];
    }
    else // slc mode is unsupported
    {
        mmc->slc_size = mmc->max_slc_size = 0;
    }

	err = mmc_change_freq(mmc);

	if (err)
		return err;

	/* Restrict card's capabilities by what the host can do */
	mmc->card_caps &= mmc->host_caps;

	/* Set the card to use 8 bit*/
    if( mmc_ddr_mode )
        err = mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_BUS_WIDTH, EXT_CSD_BUS_WIDTH_DDR_8);  /* DDR 8 bit */
    else
        err = mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_BUS_WIDTH, EXT_CSD_BUS_WIDTH_8);  /* Normal 8 bit */

	if (err)
		return err;

	mmc_set_bus_width(mmc, 8);
	mmc_set_clock(mmc, 50000000);

    //if( mmc_ddr_mode )
        //halFCIE_Config_DDR_Mode();


	/* fill in device description */
	mmc->block_dev.lun = 0;
	mmc->block_dev.type = 0;
	mmc->block_dev.blksz = mmc->read_bl_len;
	mmc->block_dev.lba = lldiv(mmc->capacity, mmc->read_bl_len);
        mmc->block_dev.part_type = PART_TYPE_EMMC;
	sprintf((char *)mmc->block_dev.vendor, "Man %06x Snr %08x", mmc->cid[0] >> 8,
			(mmc->cid[2] << 8) | (mmc->cid[3] >> 24));
	sprintf((char *)mmc->block_dev.product, "%c%c%c%c%c", mmc->cid[0] & 0xff,
			(mmc->cid[1] >> 24), (mmc->cid[1] >> 16) & 0xff,
			(mmc->cid[1] >> 8) & 0xff, mmc->cid[1] & 0xff);
	sprintf((char *)mmc->block_dev.revision, "%d.%d", mmc->cid[2] >> 28,
			(mmc->cid[2] >> 24) & 0xf);
	//init_part(&mmc->block_dev);

	return 0;
}

int mmc_send_if_cond(struct mmc *mmc)
{
	struct mmc_cmd cmd;
	int err;

	cmd.cmdidx = SD_CMD_SEND_IF_COND;
	/* We set the bit if the host supports voltages between 2.7 and 3.6 V */
	cmd.cmdarg = ((mmc->voltages & 0xff8000) != 0) << 8 | 0xaa;
	cmd.resp_type = MMC_RSP_R7;
	cmd.flags = 0;

	err = mmc_send_cmd(mmc, &cmd, NULL);

	if (err)
		return err;

	if ((cmd.response[0] & 0xff) != 0xaa)
		return UNUSABLE_ERR;
	else
		mmc->version = SD_VERSION_2;

	return 0;
}

int mmc_register(struct mmc *mmc)
{
	/* Setup the universal parts of the block interface just once */
	mmc->block_dev.if_type = IF_TYPE_MMC;
	mmc->block_dev.dev = cur_dev_num++;
	mmc->block_dev.removable = 1;
	mmc->block_dev.block_read = mmc_bread;
	mmc->block_dev.block_write = mmc_bwrite;
	mmc->block_dev.block_erase = mmc_berase;
	//mmc->block_dev.boot_part_write = mmc_boot_part_write;

	INIT_LIST_HEAD (&mmc->link);

	list_add_tail (&mmc->link, &mmc_devices);

	return 0;
}

block_dev_desc_t *mmc_get_dev(int dev)
{
	struct mmc *mmc = find_mmc_device(dev);

	return mmc ? &mmc->block_dev : NULL;
}

int mmc_init(struct mmc *mmc)
{
	return eMMC_mmc_Init(mmc);

#if 0
	int err;

	err = mmc->init(mmc);

	if (err)
		return err;

    mmc_set_clock(mmc, 1);
	mmc_set_bus_width(mmc, 1);

    /* Reset the Card */
    err = mmc_go_idle(mmc);

    if (err)
		return err;

	err = mmc_send_op_cond(mmc);

	if (err) {
		printf("Card did not respond to voltage select!\n");
		return UNUSABLE_ERR;
	}

	return mmc_startup(mmc);
#endif
}

void print_mmc_devices(char separator)
{
	struct mmc *m;
	struct list_head *entry;

	list_for_each(entry, &mmc_devices) {
		m = list_entry(entry, struct mmc, link);

		printf("%s: %d, %lu blocks", m->name, m->block_dev.dev, m->block_dev.lba);

		if (entry->next != &mmc_devices)
			printf("%c ", separator);
	}

	printf("\n");
}

int get_mmc_num(void)
{
    return cur_dev_num;
}

int mmc_initialize(bd_t *bis)
{
	INIT_LIST_HEAD (&mmc_devices);

	cur_dev_num = 0;

    board_mmc_init(bis);

	print_mmc_devices(',');

	return 0;
}

int mmc_slc_check(struct mmc *mmc)
{
    int slc_mode, slc_mode_env, flag = 0, err;
    char *emmc_slc_mode = NULL;
    char buf[4];

    if (!mmc->has_init)
    {
        err = mmc_send_ext_csd(mmc, mmc->ext_csd);
        if (err)
        {
            printf("read ecsd fail while check slc mode, err %d\n", err);
            return err;
        }
    }

    slc_mode = (mmc->slc_size == 0) ? 0:1;
    //if ((mmc->ext_csd[192] < 5) || ((mmc->ext_csd[160] & 0x3) != 3))
    //{
        //printf("Enhanced attribute of partition is not supported!\r\n");
        //slc_mode = 0;
    //}
    emmc_slc_mode = getenv("mmcslcmode");

    if (emmc_slc_mode)
    {
        slc_mode_env = (int)simple_strtol(emmc_slc_mode, NULL, 10);
        if (slc_mode != slc_mode_env)
        {
            slc_mode_env = slc_mode;
            flag = 1;
        }
    }
    else
    {
        slc_mode_env = slc_mode;
        flag = 1;
    }

    if (flag == 1)
    {
        sprintf(buf, "%X", slc_mode_env);
        setenv("mmcslcmode", buf);
        saveenv();
    }

    return 0;
}

/* EMMC reliable write check */
int mmc_relwr_check(struct mmc *mmc)
{
    int reliable_write, relwr_env, flag = 0, err;
    char *relwr_mode = NULL;
    char buf[4];

    if (!mmc->has_init)
    {
        err = mmc_send_ext_csd(mmc, mmc->ext_csd);
        if (err)
        {
            printf("read ecsd fail while check slc mode, err %d\n", err);
            return err;
        }
    }

    reliable_write = mmc->reliable_write;
    relwr_mode = getenv("mmcrelwr");

    if (relwr_mode)
    {
        relwr_env = (int)simple_strtol(relwr_mode, NULL, 10);
        if (reliable_write != relwr_env)
        {
            relwr_env = reliable_write;
            flag = 1;
        }
    }
    else
    {
        relwr_env = reliable_write;
        flag = 1;
    }

    if (flag == 1)
    {
        sprintf(buf, "%X", relwr_env);
        setenv("mmcrelwr", buf);
        saveenv();
    }

    return 0;
}

int mmc_slc_relwr_check(struct mmc *mmc)
{
    int err;
    
    err = mmc_slc_check(mmc);
    if (err)
    {
        printf("eMMC slc mode check fail!!!\n");
        return err;
    }
        
    err = mmc_relwr_check(mmc);
    if (err)
    {
        printf("eMMC reliable write configuration check fail!!!\n");
        return err;
    }
        
    if ((mmc->slc_size == 0) && (mmc->reliable_write != 2))
    {
        printf("Both of slc mode and reliable write are unconfigured!!!!!!\n");
		return 1;
    }
    if ((mmc->slc_size < mmc->capacity) && (mmc->slc_size > 0) && (mmc->reliable_write != 2))
    {
        printf("Reliable write should be configured!!!!!!\n");
		return 1;
    }

	return 0;
}

int mmc_get_alignsize(struct mmc *mmc)
{
    int alignsize, err;

    err = mmc_send_ext_csd(mmc, mmc->ext_csd);
    if (err)
    {
        printf("read ecsd fail, err %d\n", err);
        return err;
    }

    alignsize = mmc->ext_csd[221] * mmc->ext_csd[224] * 512;
    printf("SLC partition size should be aligned with %dKB\n", alignsize);

    return 0;
}

