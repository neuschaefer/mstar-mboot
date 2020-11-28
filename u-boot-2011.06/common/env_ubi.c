/*
 * (C) Copyright 2000-2010
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2008
 * Stuart Wood, Lab X Technologies <stuart.wood@labxtechnologies.com>
 *
 * (C) Copyright 2004
 * Jian Zhang, Texas Instruments, jzhang@ti.com.
 *
 * (C) Copyright 2001 Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Andreas Heppel <aheppel@sysgo.de>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#define DEBUG

#include <common.h>
#include <command.h>
#include <environment.h>
#include <linux/stddef.h>
#include <malloc.h>
#include <nand.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#include <jffs2/load_kernel.h>
#include <ubi_uboot.h>
#include <search.h>
#include <CusRawIO.h>

//#include <errno.h>

//MSTAR start
#include <MsSystem.h>
extern unsigned int cfg_env_offset;
//MSTAR end

#if defined(CONFIG_CMD_SAVEENV) && defined(CONFIG_CMD_NAND)
#define CMD_SAVEENV
#elif defined(CONFIG_ENV_OFFSET_REDUND)
#error Cannot use CONFIG_ENV_OFFSET_REDUND without CONFIG_CMD_SAVEENV & CONFIG_CMD_NAND
#endif

#if defined(CONFIG_ENV_SIZE_REDUND) && (CONFIG_ENV_SIZE_REDUND != CONFIG_ENV_SIZE)
#error CONFIG_ENV_SIZE_REDUND should be the same as CONFIG_ENV_SIZE
#endif

#ifndef CONFIG_ENV_RANGE
#define CONFIG_ENV_RANGE	CONFIG_ENV_SIZE
#endif

/* references to names in env_common.c */
extern uchar default_environment[];
#if ( CONFIG_VESTEL_MB97 == 1 )
extern MS_BOOL gb_EnvUpdate;
#endif
char *env_name_spec = "UBI";
char *env_partition = NAND_DEFAULT_PARTITION;
int ubi_leb_sz = 0;
int	env_vol_sz = 0;
#define ENV_VOL_NAME	NAND_DEFAULT_VOLUME

char mtdstr[128];
char gbuf[CONFIG_ENV_SIZE];
env_t env_new;
#if defined(ENV_IS_EMBEDDED)
extern uchar environment[];
env_t *env_ptr = (env_t *)(&environment[0]);
#elif defined(CONFIG_NAND_ENV_DST)
env_t *env_ptr = (env_t *)CONFIG_NAND_ENV_DST;
#else /* ! ENV_IS_EMBEDDED */
env_t *env_ptr = 0;
#endif /* ENV_IS_EMBEDDED */

DECLARE_GLOBAL_DATA_PTR;

extern struct ubi_volume *ubi_find_volume(char *volume);
extern int ubi_create_vol(char *volume, size_t size, int dynamic);
extern int ubi_volume_write_offset(char *volume, void *buf, size_t size, off_t offset);
extern int find_dev_and_part(const char *id, struct mtd_device **dev, u8 *part_num, struct part_info **part);
extern int ubi_volume_partial_read(char *volume, char *buf, size_t size, size_t partition_offset);
extern int ubi_get_leb_size(void);
extern int ubi_get_avai_peb(void);
extern int ubi_get_volume_size(char *volume, size_t *size);
extern void ubi_get_part_name(char *name);
extern void ubifs_get_sb_name(char *name);
#if (ENABLE_MODULE_NAND_FLASH == 1)
extern void drvNAND_GetMtdParts(char *buf);
#endif
#if (ENABLE_MODULE_SPI_NAND_FLASH == 1)
extern void MDrv_SPINAND_GetMtdParts(char *buf);
#endif

char IdsStr[] = "nand0=edb64M-nand";

uchar env_get_char_spec (int index)
{
	return ( *((uchar *)(gd->env_addr + index)) );
}

uint32_t crc32_env_ubi (uint32_t crc, const unsigned char *p, unsigned int len)
{
     return crc32_no_comp(crc ^ 0xffffffffL, p, len) ^ 0xffffffffL;
}
/*
 * This is called before nand_init() so we can't read NAND to
 * validate env data.
 *
 * Mark it OK for now. env_relocate() in env_common.c will call our
 * relocate function which does the real validation.
 *
 * When using a NAND boot image (like sequoia_nand), the environment
 * can be embedded or attached to the U-Boot image in NAND flash.
 * This way the SPL loads not only the U-Boot image from NAND but
 * also the environment.
 */
int env_init(void)
{
#if defined(ENV_IS_EMBEDDED) || defined(CONFIG_NAND_ENV_DST)
	int crc1_ok = 0, crc2_ok = 0;
	env_t *tmp_env1;

#ifdef CONFIG_ENV_OFFSET_REDUND
	env_t *tmp_env2;

	tmp_env2 = (env_t *)((ulong)env_ptr + CONFIG_ENV_SIZE);
	crc2_ok = (crc32(0, tmp_env2->data, ENV_SIZE) == tmp_env2->crc);
#endif

	tmp_env1 = env_ptr;

	crc1_ok = (crc32_env_ubi(0, tmp_env1->data, ENV_SIZE) == tmp_env1->crc);

	if (!crc1_ok && !crc2_ok) {
		gd->env_addr  = 0;
		gd->env_valid = 0;

		return 0;
	} else if (crc1_ok && !crc2_ok) {
		gd->env_valid = 1;
	}
#ifdef CONFIG_ENV_OFFSET_REDUND
	else if (!crc1_ok && crc2_ok) {
		gd->env_valid = 2;
	} else {
		/* both ok - check serial */
		if(tmp_env1->flags == 255 && tmp_env2->flags == 0)
			gd->env_valid = 2;
		else if(tmp_env2->flags == 255 && tmp_env1->flags == 0)
			gd->env_valid = 1;
		else if(tmp_env1->flags > tmp_env2->flags)
			gd->env_valid = 1;
		else if(tmp_env2->flags > tmp_env1->flags)
			gd->env_valid = 2;
		else /* flags are equal - almost impossible */
			gd->env_valid = 1;
	}

	if (gd->env_valid == 2)
		env_ptr = tmp_env2;
	else
#endif
	if (gd->env_valid == 1)
		env_ptr = tmp_env1;

	gd->env_addr = (ulong)env_ptr->data;

#else /* ENV_IS_EMBEDDED || CONFIG_NAND_ENV_DST */
	gd->env_addr  = (ulong)&default_environment[0];
	gd->env_valid = 1;
#endif /* ENV_IS_EMBEDDED || CONFIG_NAND_ENV_DST */

	return (0);
}

#ifdef CMD_SAVEENV
/*
 * The legacy NAND code saved the environment in the first NAND device i.e.,
 * nand_dev_desc + 0. This is also the behaviour using the new NAND code.
 */
int writeenv(size_t offset, u_char *buf)
{
	//dump_mem_env(buf, 0x800);
#if defined(CONFIG_CMD_UBI)
	return ubi_volume_write_offset(ENV_VOL_NAME, buf, CONFIG_ENV_SIZE, (off_t)offset);
#else
	return 0;
#endif
}
#if ( CONFIG_VESTEL_MB97 == 1 )
int saveenv_final(void)
{
    printf("\n\nSAVEENV FINALLY\n\n");

#if defined(CONFIG_CMD_UBI)
	int ret;
	char cmd_buf[30];
	ssize_t len;
	size_t size;
	char *res;
	struct mtd_device *dev;
	struct part_info *part;
	char last_ubi_partname[32];
	char last_sb_name[32];
	u8 pnum;

	memset(last_ubi_partname, 0, 32);
	memset(last_sb_name, 0, 32);
	ubi_get_part_name(last_ubi_partname);
	ubifs_get_sb_name(last_sb_name);

	if(find_dev_and_part(env_partition, &dev, &pnum, &part))
	{
		printf("Partition %s not found!\n", env_partition);
		printf("save env fail\n");
		return 1;
	}

	if(!ubi_find_volume(ENV_VOL_NAME))
	{
		sprintf(cmd_buf, "ubi part %s", env_partition);
		if(run_command(cmd_buf, 0) == -1)
			return 1;
	}
	if(!ubi_leb_sz)
		ubi_leb_sz = ubi_get_leb_size();

	res = (char *)&env_new.data;
	len = hexport_r(&env_htab, '\0', &res, ENV_SIZE);
	if (len < 0) {
		printf("Cannot export environment\n");
		return 1;
	}
	env_new.crc = crc32_env_ubi(0, env_new.data, ENV_SIZE);
	//printf("saveenv crc = %X\n", env_new.crc);

	if(ubi_find_volume(ENV_VOL_NAME))
	{
		printf("Write Env to %X...\n", CONFIG_ENV_OFFSET);
		ret = writeenv(CONFIG_ENV_OFFSET, (u_char *)&env_new);
		if (ret) {
			puts("Failed\n");
			return ret;
		}
		printf("Write Backup Env to %X...\n", CONFIG_ENV_OFFSET + ubi_leb_sz);
		ret = writeenv(CONFIG_ENV_OFFSET + ubi_leb_sz, (u_char *) &env_new);
		if (ret)
		{
			puts("Backup Failed\n");
			return ret;
		}
	}
	else
	{
		printf("Found no %s Volume\n Create %s volume\n", ENV_VOL_NAME, ENV_VOL_NAME);
		ret = ubi_create_vol(ENV_VOL_NAME, env_vol_sz, 1);
		if(ret)
		{
			printf("create %s volume in %s partition fail with size = %0xX\n", ENV_VOL_NAME, env_partition, env_vol_sz);
			return ret;
		}
		ubi_leb_sz = ubi_get_leb_size();

	    MsApiChunkHeader_GetValue(CH_UBOOT_ENVIRONMENT_ROM_OFFSET,&cfg_env_offset);
		ubi_get_volume_size(ENV_VOL_NAME, &size);
		cfg_env_offset = size - (cfg_env_offset*ubi_leb_sz);

		ret = writeenv(CONFIG_ENV_OFFSET, (u_char *)&env_new);
        if (ret) {
			puts("Failed\n");
            return ret;
        }
		ret = writeenv(CONFIG_ENV_OFFSET + ubi_leb_sz, (u_char *) &env_new);
		if (ret)
		{
			puts("Backup Failed\n");
			return ret;
		}
	}
	if(last_ubi_partname[0]){
		sprintf(cmd_buf, "ubi part %s", last_ubi_partname);
		if(run_command(cmd_buf, 0) == -1){
			printf("restore ubi part %s failed\n", last_ubi_partname);
			return -1;
		}
	}
	if(last_sb_name[0]){
		sprintf(cmd_buf, "ubifsmount %s", last_sb_name);
		if(run_command(cmd_buf, 0) == -1){
			printf("remount volume %s failed\n", last_sb_name);
			return -1;
		}
	}
	puts("done\n");
	return ret;
#else
	return 0;
#endif
}
#endif

int saveenv(void)
{
#if ( CONFIG_VESTEL_MB97 == 1 )
    printf("\n\nSAVEENV\n\n");
    gb_EnvUpdate = TRUE;
    return 0;
#endif

#if defined(CONFIG_CMD_UBI)
	int ret;
	char cmd_buf[30];
	ssize_t len;
	size_t size;
	char *res;
	struct mtd_device *dev;
	struct part_info *part;
	char last_ubi_partname[32];
	char last_sb_name[32];
	u8 pnum;

	memset(last_ubi_partname, 0, 32);
	memset(last_sb_name, 0, 32);
	ubi_get_part_name(last_ubi_partname);
	ubifs_get_sb_name(last_sb_name);

	if(find_dev_and_part(env_partition, &dev, &pnum, &part))
	{
		printf("Partition %s not found!\n", env_partition);
		printf("save env fail\n");
		return 1;
	}

	if(!ubi_find_volume(ENV_VOL_NAME))
	{
		sprintf(cmd_buf, "ubi part %s", env_partition);
		if(run_command(cmd_buf, 0) == -1)
			return 1;
	}
	if(!ubi_leb_sz)
		ubi_leb_sz = ubi_get_leb_size();

	res = (char *)&env_new.data;
	len = hexport_r(&env_htab, '\0', &res, ENV_SIZE);
	if (len < 0) {
		printf("Cannot export environment\n");
		return 1;
	}
	env_new.crc = crc32_env_ubi(0, env_new.data, ENV_SIZE);
	//printf("saveenv crc = %X\n", env_new.crc);

	if(ubi_find_volume(ENV_VOL_NAME))
	{
		printf("Write Env to %X...\n", CONFIG_ENV_OFFSET);
		ret = writeenv(CONFIG_ENV_OFFSET, (u_char *)&env_new);
		if (ret) {
			puts("Failed\n");
			return ret;
		}
		printf("Write Backup Env to %X...\n", CONFIG_ENV_OFFSET + ubi_leb_sz);
		ret = writeenv(CONFIG_ENV_OFFSET + ubi_leb_sz, (u_char *) &env_new);
		if (ret)
		{
			puts("Backup Failed\n");
			return ret;
		}
	}
	else
	{
		printf("Found no %s Volume\n Create %s volume\n", ENV_VOL_NAME, ENV_VOL_NAME);
		ret = ubi_create_vol(ENV_VOL_NAME, env_vol_sz, 1);
		if(ret)
		{
			printf("create %s volume in %s partition fail with size = %0xX\n", ENV_VOL_NAME, env_partition, env_vol_sz);
			return ret;
		}
		ubi_leb_sz = ubi_get_leb_size();

	    MsApiChunkHeader_GetValue(CH_UBOOT_ENVIRONMENT_ROM_OFFSET,&cfg_env_offset);
		ubi_get_volume_size(ENV_VOL_NAME, &size);
		cfg_env_offset = size - (cfg_env_offset*ubi_leb_sz);

		ret = writeenv(CONFIG_ENV_OFFSET, (u_char *)&env_new);
        if (ret) {
			puts("Failed\n");
            return ret;
        }
		ret = writeenv(CONFIG_ENV_OFFSET + ubi_leb_sz, (u_char *) &env_new);
		if (ret)
		{
			puts("Backup Failed\n");
			return ret;
		}
	}
	if(last_ubi_partname[0]){
		sprintf(cmd_buf, "ubi part %s", last_ubi_partname);
		if(run_command(cmd_buf, 0) == -1){
			printf("restore ubi part %s failed\n", last_ubi_partname);
			return -1;
		}
	}
	if(last_sb_name[0]){
		sprintf(cmd_buf, "ubifsmount %s", last_sb_name);
		if(run_command(cmd_buf, 0) == -1){
			printf("remount volume %s failed\n", last_sb_name);
			return -1;
		}
	}
	puts("done\n");
	return ret;
#else
	return 0;
#endif
}
#endif /* CMD_SAVEENV */

int readenv(size_t offset, u_char * buf)
{
#if defined(CONFIG_CMD_UBI)
	return ubi_volume_partial_read(ENV_VOL_NAME, (char *)buf, CONFIG_ENV_SIZE, offset);
#else
	return 0;
#endif
}

/*
 * The legacy NAND code saved the environment in the first NAND
 * device i.e., nand_dev_desc + 0. This is also the behaviour using
 * the new NAND code.
 */

void env_relocate_spec (void)
{
#if defined(CONFIG_CMD_UBI)

#if !defined(ENV_IS_EMBEDDED)
	int ret, i, readfrombackup;
	char cmd_buf[30];
	struct mtd_device *dev;
	struct part_info *part;
	uint32_t crc;
	size_t size;
	env_t *ep;
	u8 pnum;

#if defined(CONFIG_ENV_OFFSET_OOB)
	ret = get_nand_env_oob(&nand_info[0], &nand_env_oob_offset);
	/*
	 * If unable to read environment offset from NAND OOB then fall through
	 * to the normal environment reading code below
	 */
	if (!ret) {
		printf("Found Environment offset in OOB..\n");
	} else {
		set_default_env("!no env offset in OOB");
		return;
	}
#endif

	//get mtdpart string from pni
	set_default_env("!set default for mtdparts");

	#if (ENABLE_MODULE_NAND_FLASH == 1)
	drvNAND_GetMtdParts(mtdstr);
	#endif
	#if (ENABLE_MODULE_SPI_NAND_FLASH == 1)
	MDrv_SPINAND_GetMtdParts(mtdstr);
	#endif

	setenv("mtdparts", mtdstr);
	setenv("mtdids", IdsStr);

	mtdparts_init();
	if(find_dev_and_part(env_partition, &dev, &pnum, &part))
	{
		printf("Partition %s not found!\n", env_partition);
		printf("read env fail\n");
		return;
	}

	if(!ubi_find_volume(ENV_VOL_NAME))
	{
		sprintf(cmd_buf, "ubi part %s", env_partition);
		if(run_command(cmd_buf, 0) == -1)
			return;
	}
	if(!ubi_leb_sz)
		ubi_leb_sz = ubi_get_leb_size();

	if(!env_vol_sz)
		env_vol_sz = (ubi_get_avai_peb() - 1) * ubi_leb_sz;

	if(cfg_env_offset == 0)
	{
	    MsApiChunkHeader_GetValue(CH_UBOOT_ENVIRONMENT_ROM_OFFSET,&cfg_env_offset);
		ubi_get_volume_size(ENV_VOL_NAME, &size);
		cfg_env_offset = size - (cfg_env_offset*ubi_leb_sz);
	}
	//find ENV volume

	readfrombackup = 0;
	if(ubi_find_volume(ENV_VOL_NAME))
	{
		for(i = 0 ;i < CONFIG_ENV_BLOCK_NUM; i ++)
		{
			ret = readenv(CONFIG_ENV_OFFSET + i * ubi_leb_sz, (u_char *)gbuf);
			if (ret) {
				if(i < (CONFIG_ENV_BLOCK_NUM - 1))
				{
					printf("Read ENV fail, Read Backup ENV\n");
					readfrombackup = 1;
					continue;
				}
				else
				{
					printf("Read Backup ENV Failed\n");
					return;
				}
			}
			ep = (env_t*) gbuf;
			memcpy(&crc, &ep->crc, sizeof(crc));
//			printf("Calc crc %X, Read crc %X\n", crc32(0, ep->data, ENV_SIZE), crc);
			if(crc32_env_ubi(0,  ep->data, ENV_SIZE) == crc)
			{
				env_import(gbuf, 0);
				break;
			}
			else
			{
				if(i < (CONFIG_ENV_BLOCK_NUM - 1))
				{
					printf("Read ENV crc error, Read Backup ENV\n");
					readfrombackup = 1;
				}
				else
				{
					printf("Read Backup ENV crc error\n");
					return;
				}
			}
		}
	}
	else
	{
		printf("Found no %s Volume\n Create %s volume\n", ENV_VOL_NAME, ENV_VOL_NAME);
		ret = ubi_create_vol(ENV_VOL_NAME, env_vol_sz, 1);
		if(ret)
			printf("create %s volume in %s partition fail with size = 0x%X\n",  ENV_VOL_NAME, env_partition, env_vol_sz);

		ubi_leb_sz = ubi_get_leb_size();

		ubi_get_volume_size(ENV_VOL_NAME, &size);

		MsApiChunkHeader_GetValue(CH_UBOOT_ENVIRONMENT_ROM_OFFSET,&cfg_env_offset);
		cfg_env_offset = size - (cfg_env_offset*ubi_leb_sz);
	}

	//restore data from backup
	if(readfrombackup == 1)
	{
		ret = saveenv();
		if(ret)
			printf("restore data fail\n");
	}
#endif /* ! ENV_IS_EMBEDDED */

#else
	set_default_env("!set default for NAND program");

#endif /* ! CONFIG_CMD_UBI*/
}
