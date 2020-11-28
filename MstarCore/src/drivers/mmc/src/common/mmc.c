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


static struct list_head mmc_devices;
static int cur_dev_num = -1;
unsigned char mmc_ddr_mode = 0;

extern int board_mmc_init(bd_t *bis);
extern int eMMC_mmc_Init(struct mmc* mmc);

int __board_mmc_getcd(u8 *cd, struct mmc *mmc) {
	return -1;
}

int board_mmc_getcd(u8 *cd, struct mmc *mmc)__attribute__((weak,
	alias("__board_mmc_getcd")));

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

int mmc_switch_part(int dev_num, unsigned int part_num)
{
    struct mmc *mmc = find_mmc_device(dev_num);

    if (!mmc)
        return -1;

    return mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_PART_CONF,
        (mmc->part_config & ~PART_ACCESS_MASK)| (part_num & PART_ACCESS_MASK));
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
	if (size==0 && reliable_write==1 && (mmc->reliable_write==3 || mmc->reliable_write==2))
    {
        printf("Reliable write is default supported!\n");
        return 0;
    }
	
    if (mmc->slc_size || mmc->ext_csd[EXT_CSD_PARTITION_SETTING_COMPLETED])
    {
		printf("eMMC: SLC mode size: %llu, reliable write: %u, has been set\n", 
			mmc->slc_size, mmc->ext_csd[EXT_CSD_WR_REL_SET]&BIT0);
		
        return 0;
    }

    if (!size && (reliable_write == 1))
    {
		unsigned char u8_ECSD167 = mmc->ext_csd[EXT_CSD_WR_REL_SET], 
			          u8_ECSD166 = mmc->ext_csd[EXT_CSD_WR_REL_PARAM];
			
        if( (mmc->ext_csd[EXT_CSD_WR_REL_PARAM] & 0x01) == 0x01 ) // ECSD[166] is rw
        {			
            mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_ERASE_GROUP_DEF, 1);
            mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_WR_REL_SET, 0x1f);
            // complete the partition configuration
            if(0 == mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_PARTITION_SETTING_COMPLETED, 0x01))
            {
				mmc->reliable_write = 2;

                while (1)
                    printf("Please reset the board!!!!!! Reliable write would be active after reset!!!!!!\n");
            }
			else
			{
				if((u8_ECSD167 & BIT0) && 0!=u8_ECSD167)
					printf("The write reliability is default enabled! ECSD[167]=%Xh ECSD[166]=%Xh \n", u8_ECSD167, u8_ECSD166);
					
				else
					while (1)
						printf("eMMC Err: can NOT enable write reliability: ECSD[167]=%Xh ECSD[166]=%Xh \n", u8_ECSD167, u8_ECSD166);

				return 0;
			}

            
        }
        else // ECSD[167] is ro
        {
            if( (mmc->ext_csd[EXT_CSD_WR_REL_SET]&BIT0) && (0!=mmc->ext_csd[EXT_CSD_WR_REL_SET]) )
                printf("The write reliability is default enabled! ECSD[167]=%Xh ECSD[166]=%Xh \n", u8_ECSD167, u8_ECSD166);
            else
                while(1)
					printf("eMMC Err: This eMMC doesn't support write reliability! ECSD[167]=%Xh ECSD[166]=%Xh \n", u8_ECSD167, u8_ECSD166);

			return 0;
        }
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

int mmc_register(struct mmc *mmc)
{
	/* Setup the universal parts of the block interface just once */
	mmc->block_dev.if_type = IF_TYPE_MMC;
	mmc->block_dev.dev = cur_dev_num++;
	mmc->block_dev.removable = 1;

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

	//print_mmc_devices(',');

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

