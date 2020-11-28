/*
 * (C) Copyright 2003
 * Kyle Harris, kharris@nexus-tech.net
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

#include <common.h>
#include <command.h>
#include <mmc.h>

static int curr_device = -1;
extern unsigned int gu32BestSkew4;
extern unsigned char gu8SilenceTuning;

//extern void HalFcie_SetShiftTune(U8 u8Select, U8 u8Type, U8 u8Count);
//extern U32 HalFcie_BistTest(U8 u8_PatSel);
//extern U32 HalFcie_PowerSaveMode(void);
//extern void HalFcie_TestDataOneIntr(void);

#define NONE			"\033[m"
#define RED				"\033[0;32;31m"
#define LIGHT_RED		"\033[1;31m"
#define GREEN			"\033[0;32;32m"
#define LIGHT_GREEN		"\033[1;32m"
#define BLUE			"\033[0;32;34m"
#define LIGHT_BLUE		"\033[1;34m"
#define DARY_GRAY		"\033[1;30m"
#define CYAN			"\033[0;36m"
#define LIGHT_CYAN		"\033[1;36m"
#define PURPLE			"\033[0;35m"
#define LIGHT_PURPLE	"\033[1;35m"
#define BROWN			"\033[0;33m"
#define YELLOW			"\033[1;33m"
#define LIGHT_GRAY		"\033[0;37m"
#define WHITE			"\033[1;37m"

#ifndef CONFIG_GENERIC_MMC

int do_mmc (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int dev;

	if (argc < 2)
		return cmd_usage(cmdtp);

	if (strcmp(argv[1], "init") == 0) {
		if (argc == 2) {
			if (curr_device < 0)
				dev = 1;
			else
				dev = curr_device;
		} else if (argc == 3) {
			dev = (int)simple_strtoul(argv[2], NULL, 10);
		} else {
			return cmd_usage(cmdtp);
		}

		if (mmc_legacy_init(dev) != 0) {
			puts("No MMC card found\n");
			return 1;
		}

		curr_device = dev;
		printf("mmc%d is available\n", curr_device);
	} else if (strcmp(argv[1], "device") == 0) {
		if (argc == 2) {
			if (curr_device < 0) {
				puts("No MMC device available\n");
				return 1;
			}
		} else if (argc == 3) {
			dev = (int)simple_strtoul(argv[2], NULL, 10);

#ifdef CONFIG_SYS_MMC_SET_DEV
			if (mmc_set_dev(dev) != 0)
				return 1;
#endif
			curr_device = dev;
		} else {
			return cmd_usage(cmdtp);
		}

		printf("mmc%d is current device\n", curr_device);
	} else {
		return cmd_usage(cmdtp);
	}

	return 0;
}

U_BOOT_CMD(
	mmc, 3, 1, do_mmc,
	"MMC sub-system",
	"init [dev] - init MMC sub system\n"
	"mmc device [dev] - show or set current device"
);

#else /* !CONFIG_GENERIC_MMC */

static void print_mmcinfo(struct mmc *mmc)
{
	printf("Device: %s\n", mmc->name);
	printf("Manufacturer ID: %x\n", mmc->cid[0] >> 24);
	printf("OEM: %x\n", (mmc->cid[0] >> 8) & 0xffff);
	printf("Name: %c%c%c%c%c \n", mmc->cid[0] & 0xff,
			(mmc->cid[1] >> 24), (mmc->cid[1] >> 16) & 0xff,
			(mmc->cid[1] >> 8) & 0xff, mmc->cid[1] & 0xff);

	printf("Tran Speed: %d\n", mmc->tran_speed);
	printf("Rd Block Len: %d\n", mmc->read_bl_len);

	printf("%s version %d.%d\n", IS_SD(mmc) ? "SD" : "MMC",
			(mmc->version >> 4) & 0xf, mmc->version & 0xf);

	printf("High Capacity: %s\n", mmc->high_capacity ? "Yes" : "No");
	puts("Capacity: ");
	print_size(mmc->capacity, "\n");

	printf("Bus Width: %d-bit\n", mmc->bus_width);
}

int do_mmcinfo (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	struct mmc *mmc;

	if (curr_device < 0) {
		if (get_mmc_num() > 0)
			curr_device = 0;
		else {
			puts("No MMC device available\n");
			return 1;
		}
	}

	mmc = find_mmc_device(curr_device);

	if (mmc) {
		mmc_init(mmc);

		print_mmcinfo(mmc);
		return 0;
	} else {
		printf("no mmc device at slot %x\n", curr_device);
		return 1;
	}
}

U_BOOT_CMD(
	sdinfo, 1, 0, do_mmcinfo,
	"display SD info",
	"    - device number of the device to dislay info of\n"
	""
);

int do_mmcops(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	if (argc < 2)
		return cmd_usage(cmdtp);

	if (curr_device < 0) {
		if (get_mmc_num() > 0)
			curr_device = 0;
		else {
			puts("No MMC device available\n");
			return 1;
		}
	}

	if (strcmp(argv[1], "rescan") == 0)
	{
		struct mmc *mmc = find_mmc_device(curr_device);

		if (!mmc) {
			printf("no mmc device at slot %x\n", curr_device);
			return 1;
		}

		mmc->has_init = 0;
		mmc_init(mmc);

		return 0;
	}
	else if (strcmp(argv[1], "burning") == 0)
	{
		struct mmc *mmc = find_mmc_device(curr_device);
        u32 n, i, j;
		u32 blknr = 100;
		static u8 test_pattern[512];
		static u8 read_pattern[512];
		if (!mmc) {
			printf("no mmc device at slot %x\n", curr_device);
			return 1;
		}

		mmc->has_init = 0;
		mmc_init(mmc);

        for(i=0;i<100;i++)
        {
           printf("loop :%d\n",i);
           for(j=0;j<512;j++)
		       test_pattern[j]=j+i;
		   n = mmc->block_dev.block_write(curr_device, blknr, 1, test_pattern);
		   n = mmc->block_dev.block_read(curr_device, blknr, 1, read_pattern);
		   for(j=0;j<512;j++)
		   {
		       if (read_pattern[j] != test_pattern[j])
			   {
			       printf("[%d]r:[0x%x]!=w:[0x%x]\n", j,read_pattern[j],test_pattern[j]);
				   while(1);
		       }
		   }
        }
				   printf("burning OK\n");

		return 0;
	}
	else if (strncmp(argv[1], "part", 4) == 0)
	{
		block_dev_desc_t *mmc_dev;
		struct mmc *mmc = find_mmc_device(curr_device);

		if (!mmc) {
			printf("no mmc device at slot %x\n", curr_device);
			return 1;
		}
		mmc_init(mmc);
		mmc_dev = mmc_get_dev(curr_device);
		if (mmc_dev != NULL &&
				mmc_dev->type != DEV_TYPE_UNKNOWN) {
			print_part(mmc_dev);
			return 0;
		}

		puts("get mmc type error!\n");
		return 1;
	}
	else if (strcmp(argv[1], "list") == 0)
	{
		print_mmc_devices('\n');
		return 0;
	}
	else if (strcmp(argv[1], "dev") == 0)
	{
		int dev, part = -1;
		struct mmc *mmc;

		if (argc == 2)
			dev = curr_device;
		else if (argc == 3)
			dev = simple_strtoul(argv[2], NULL, 10);
		else if (argc == 4) {
			dev = (int)simple_strtoul(argv[2], NULL, 10);
			part = (int)simple_strtoul(argv[3], NULL, 10);
			if (part > PART_ACCESS_MASK) {
				printf("#part_num shouldn't be larger"
					" than %d\n", PART_ACCESS_MASK);
				return 1;
			}
		} else
			return cmd_usage(cmdtp);

		mmc = find_mmc_device(dev);
		if (!mmc) {
			printf("no mmc device at slot %x\n", dev);
			return 1;
		}

		mmc_init(mmc);
		if (part != -1) {
			int ret;
			if (mmc->part_config == MMCPART_NOAVAILABLE) {
				printf("Card doesn't support part_switch\n");
				return 1;
			}

			if (part != mmc->part_num) {
				ret = mmc_switch_part(dev, part);
				if (!ret)
					mmc->part_num = part;

				printf("switch to partions #%d, %s\n",
						part, (!ret) ? "OK" : "ERROR");
			}
		}
		curr_device = dev;
		if (mmc->part_config == MMCPART_NOAVAILABLE)
			printf("mmc%d is current device\n", curr_device);
		else
			printf("mmc%d(part %d) is current device\n",
				curr_device, mmc->part_num);

		return 0;
	}
	else if (strcmp(argv[1], "read") == 0)
	{
		void *addr = (void *)simple_strtoul(argv[2], NULL, 16);
		u32 cnt = simple_strtoul(argv[4], NULL, 16);
		u32 n;
		u32 blk = simple_strtoul(argv[3], NULL, 16);
		struct mmc *mmc = find_mmc_device(curr_device);

		if (!mmc) {
			printf("no mmc device at slot %x\n", curr_device);
			return 1;
		}

		printf("\nMMC read: dev # %d, block # %d, count %d ... ",
				curr_device, blk, cnt);

		mmc_init(mmc);

				n = mmc->block_dev.block_read(curr_device, blk, cnt, addr);

		/* flush cache after read */
		flush_cache((ulong)addr, cnt * 512); /* FIXME */

		printf("%d blocks read: %s\n", n, (n==cnt) ? "OK" : "ERROR");
		return (n == cnt) ? 0 : 1;
	}
	else if (strcmp(argv[1], "write") == 0)
	{
		void *addr = (void *)simple_strtoul(argv[2], NULL, 16);
		u32 cnt = simple_strtoul(argv[4], NULL, 16);
		u32 n;
		struct mmc *mmc = find_mmc_device(curr_device);

		int blk = simple_strtoul(argv[3], NULL, 16);

		if (!mmc) {
			printf("no mmc device at slot %x\n", curr_device);
			return 1;
		}

		printf("\nMMC write: dev # %d, block # %d, count %d ... ", curr_device, blk, cnt);

		mmc_init(mmc);

		n = mmc->block_dev.block_write(curr_device, blk, cnt, addr);

		printf("%d blocks written: %s\n", n, (n == cnt) ? "OK" : "ERROR");

		return (n == cnt) ? 0 : 1;
	}
	else if (strcmp(argv[1], "tune") == 0)
	{
		const u32 blk = 10000; // notice! hardcode block address here . . .
		const u32 cnt = 2;
		void * addr = (void *)0x20400000;
		u32 n = 0;
		struct mmc *mmc = find_mmc_device(curr_device);
		u8 u8_i = 0;
		u8 Ret[16] = {0};
		u8 u8Type = 0;

		if (!mmc) {
			printf("no mmc device at slot %x\n", curr_device);
			return 1;
		}

		mmc_init(mmc);

		if (strncmp(argv[2], "rsp", 3) == 0)
		{
			u8Type = 1;
		}
		else if (strncmp(argv[2], "rstop", 5) == 0)
		{
			u8Type = 2;
		}
		else if (strncmp(argv[2], "wrsts", 5) == 0)
		{
			u8Type = 3;
		}
		else
		{
			printf("wrong parameter\n");
			return 1;
		}

		for(u8_i=0; u8_i<16; u8_i++)
		{
			mmc->has_init = 0; mmc_init(mmc); // init again for clean enviroment

			printf("\n");
			HalFcie_SetShiftTune(1, u8Type, u8_i);
			if(u8Type!=3)
			{
				n = mmc->block_dev.block_read(curr_device, blk, cnt, addr);
			}
			else
			{
				n = mmc->block_dev.block_write(curr_device, blk, cnt, addr);
			}
			if(n==cnt) Ret[u8_i] = 1;
			HalFcie_SetShiftTune(0, u8Type, 0); // restore back for init again
		}

		for(u8_i=0; u8_i<16; u8_i++)
		{
			printf("  %2d", u8_i);
		}
		printf("\n");
		for(u8_i=0; u8_i<16; u8_i++)
		{
			printf("  %s", Ret[u8_i] ? "OK" : "NG");
		}
		printf("\n");

		return (n == cnt) ? 0 : 1;

	}
	else if (strcmp(argv[1], "bist") == 0)
	{
		u8 u8_i = 0;

 		for(u8_i=0; u8_i<12; u8_i++)
		{
			HalFcie_BistTest(u8_i);
		}
	}
	else if (strcmp(argv[1], "pwrsave") == 0)
	{
		return HalFcie_PowerSaveMode();
	}
	else if (strcmp(argv[1], "d1intr") == 0)
	{
		return HalFcie_TestDataOneIntr();
	}
	else if (strcmp(argv[1], "adma") == 0)
	{
		u8 u8_Pattern = 0;

 		for(u8_Pattern=0; u8_Pattern<=0xFE; u8_Pattern++)
		{
			if( HalFcie_TestAdvanceDMA(u8_Pattern))
			{
				break;
			}
		}
		if(u8_Pattern==0xFF)
		{
			printf("OK\n");
			return 0;
		}
	}
	else if (strcmp(argv[1], "test") == 0)
	{
		unsigned int n = 0;
		struct mmc *mmc = find_mmc_device(curr_device);
		unsigned short u16_pattern;

		if (!mmc) {
			printf("no mmc device at slot %x\n", curr_device);
			return 1;
		}

		if(strcmp(argv[2], "wo") == 0)
		{
			u16_pattern = simple_strtoul(argv[3], NULL, 16);
			memset((void*)0x20400000, u16_pattern, 128<<9);
		}

		while(1)
		{
			if(strcmp(argv[2], "ro") == 0)
			{
				n = mmc->block_dev.block_read(curr_device, 100000, 128, (void*)0x20400000);
				printf("%d blocks read: %s\n", n, (n == 128) ? "OK" : "ERROR");
			}
			else if(strcmp(argv[2], "wo") == 0)
			{
				n = mmc->block_dev.block_write(curr_device, 100000, 128, (void*)0x20400000);
				printf("%d blocks written: %s\n", n, (n == 128) ? "OK" : "ERROR");
			}
			if(n!=128) break;
  		}
	}
	else if (strcmp(argv[1], "scanphase") == 0)
	{
		unsigned int n;
		struct mmc *mmc = find_mmc_device(curr_device);
		unsigned short u16_pattern;
		unsigned char result[18][18];// = {0};
		unsigned char skew1 = 0, skew4 = 0, trig_level = 0;
		unsigned char u8RescanAfterFail = 0;

		if (!mmc) {
			printf("no mmc device at slot %x\n", curr_device);
			return 1;
		}

		if(strcmp(argv[2], "read") == 0)
		{
			if(strcmp(argv[3], "rescan") == 0)
			{
				u8RescanAfterFail = 1;
			}

			gu8SilenceTuning = 1;

			for(trig_level=0; trig_level<8; trig_level++)
			{
				for(skew4=0; skew4<18; skew4++)
				{
					HalSdio_SetTriggerLevel(trig_level);
					HalSdio_SetSkew(4, skew4);
					n = mmc->block_dev.block_read(curr_device, 100000, 128, (void*)0x20400000);
					if(n == 128)
					{
						result[trig_level][skew4] = 0; // OK
					}
					else
					{
						result[trig_level][skew4] = 1; // NG
						if(u8RescanAfterFail)
						{
							mmc->has_init = 0; mmc_init(mmc); // init again for clean enviroment
							gu8SilenceTuning = 1;
						}
					}
				}
			}

			gu8SilenceTuning = 0;

			printf("TL\\S4: ");
			for(skew4=0; skew4<18; skew4++)
			{
				printf("[%2d] ", skew4);
			}
			printf("\n");

			for(trig_level=0; trig_level<8; trig_level++)
			{
				printf("  [%2d] ", trig_level);
				for(skew4=0; skew4<18; skew4++)
				{
					//printf("[%2d] ", skew4);
					printf(" %s  ", (result[trig_level][skew4]==0) ? "OK" : LIGHT_RED"NG"NONE);
				}
				printf("\n");
			}

			// restore back
			HalSdio_SetTriggerLevel(0);
			HalSdio_SetSkew(1, 0);
			HalSdio_SetSkew(4, gu32BestSkew4);

			return 0;
		}
		else if(strcmp(argv[2], "write") == 0)
		{
			// prepare buffer
			u16_pattern = simple_strtoul(argv[3], NULL, 16);
			memset((void*)0x20400000, u16_pattern, 128<<9);

			if(strcmp(argv[3], "rescan") == 0)
			{
				u8RescanAfterFail = 1;
			}

			gu8SilenceTuning = 1;

			for(skew1=0; skew1<18; skew1++)
			{
				for(skew4=0; skew4<18; skew4++)
				{
					//printf("\nS1[%d]S4[%d]\n", skew1, skew4);
					HalSdio_SetSkew(1, skew1);
					HalSdio_SetSkew(4, skew4);

					n = mmc->block_dev.block_write(curr_device, 100000, 128, (void*)0x20400000);
					if(n == 128)
					{
						result[skew1][skew4] = 0; // OK
					}
					else
					{
						result[skew1][skew4] = 1; // NG
						if(u8RescanAfterFail)
						{
							mmc->has_init = 0; mmc_init(mmc); // init again for clean enviroment
							gu8SilenceTuning = 1;
						}
					}
				}
			}

			gu8SilenceTuning = 0;

			printf("S1\\S4: ");
			for(skew4=0; skew4<18; skew4++)
			{
				printf("[%2d] ", skew4);
			}
			printf("\n");

			for(skew1=0; skew1<18; skew1++)
			{
				printf("  [%2d] ", skew1);
				for(skew4=0; skew4<18; skew4++)
				{
					//printf("[%2d] ", skew4);
					printf(" %s  ", (result[skew1][skew4]==0) ? "OK" : LIGHT_RED"NG"NONE);
				}
				printf("\n");
			}

			// restore back
			HalSdio_SetSkew(1, 0);
			HalSdio_SetSkew(4, gu32BestSkew4);

			return 0;
		}

	}
	else if (strcmp(argv[1], "reg") == 0)
	{
		HalFcie_DumpRegister();
		return 0;
	}

	return cmd_usage(cmdtp);
}

U_BOOT_CMD(
	sd, 6, 1, do_mmcops,
	"SD Card sub system",
	"read addr blk# cnt\n"
	"sd write addr blk# cnt\n"
	"sd tune [rsp/rstop/wrsts]\n"
	"sd bist - test BIST function\n"
	"sd pwrsave - test power save mode\n"
	"sd adma - test ADMA write read compare\n"
	"sd test [wo/ro] [data pattern] - write only or read only test\n"
	"sd scanphase [read/write] - scan skew value to show eye wide\n"
	"sd d1intr\n"
	"sd rescan\n"
	"sd burning\n"
	"sd part - lists available partition on current mmc device\n"
	"sd dev [dev] [part] - show or set current mmc device [partition]\n"
	"sd list - lists available devices\n");

#endif

