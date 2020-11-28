/*
 * (C) Copyright 2008-2011 Freescale Semiconductor, Inc.
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

/* #define DEBUG */

#include <common.h>

#include <command.h>
#include <environment.h>
#include <linux/stddef.h>
#include <malloc.h>
#include <mmc.h>
#include <search.h>
#include <errno.h>
#include <MsSystem.h>

#include "drv_eMMC.h"
#include "../disk/part_emmc.h"

/* references to names in env_common.c */
extern uchar default_environment[];

char *env_name_spec = "MMC";

static write_env_cb fpWriteEnv = NULL;
static read_env_cb fpReadEnv = NULL;

extern ulong emmc_boot_read(struct mmc *mmc, int prtno, int dev_num, ulong start, lbaint_t blkcnt, unsigned long *dst);
extern ulong emmc_boot_write(struct mmc *mmc, int prtno, int dev_num, ulong start, lbaint_t blkcnt, unsigned long *src);

#ifdef ENV_IS_EMBEDDED
extern uchar environment[];
env_t *env_ptr = (env_t *)(&environment[0]);
#else /* ! ENV_IS_EMBEDDED */
env_t *env_ptr = NULL;
#endif /* ENV_IS_EMBEDDED */

/* local functions */
#if !defined(ENV_IS_EMBEDDED)
static void use_default(void);
#endif

DECLARE_GLOBAL_DATA_PTR;

#if !defined(CONFIG_ENV_OFFSET)
#define CONFIG_ENV_OFFSET 0
#endif

static int __mmc_get_env_addr(struct mmc *mmc, u32 *env_addr)
{
    *env_addr = CONFIG_ENV_OFFSET;
    return 0;
}
__attribute__((weak, alias("__mmc_get_env_addr")))
int mmc_get_env_addr(struct mmc *mmc, u32 *env_addr);


uchar env_get_char_spec(int index)
{
    return *((uchar *)(gd->env_addr + index));
}

int env_init(void)
{
    /* use default */
    gd->env_addr = (ulong)&default_environment[0];
    gd->env_valid = 1;

    return 0;
}

int init_mmc_for_env(struct mmc *mmc)
{
    if (!mmc) {
        puts("No MMC card found\n");
        return -1;
    }

    //if (mmc_init(mmc)) {
    if(eMMC_Init()){
        puts("MMC init failed\n");
        return  -1;
    }

    return 0;
}

#ifdef CONFIG_CMD_SAVEENV

void RegisterCBWriteEnv(write_env_cb cb)
{
    fpWriteEnv=cb;
}

int _write_env(struct mmc *mmc, unsigned long size,
			unsigned long offset, const void *buffer)
{
    uint  blk_cnt, n,i;
    int ret;
    emmc_partition_t	*mpart;
    mpart = malloc(sizeof(*mpart));

    //blk_start = ALIGN(offset, 512) / 512;
    blk_cnt   = ALIGN(size, 512) / 512;

    //n = emmc_boot_write(mmc, 2, CONFIG_SYS_MMC_ENV_DEV, blk_start, blk_cnt, (unsigned long *)buffer);
    //n = eMMC_WriteBootPart((U8*)buffer, blk_cnt << 9, blk_start, 2);

    //MsApiChunkHeader_GetValue(CH_UBOOT_ENVIRONMENT_ROM_OFFSET, &blk_start);
    //MsApiChunkHeader_GetValue(CH_UBOOT_ENVIRONMENT_SIZE, &total_size);

    memset(mpart,0,sizeof(*mpart));
	for(i=1;i<= EMMC_RESERVED_FOR_MAP_V2;i++)
	{
		n = (uint)eMMC_ReadData((U8 *)(mpart), 512 , i);
		if(n != 0)
            return n;

		if(strcmp("MPOOL", (const char *)mpart->name)==0)
		{
             break;
		}
	}

   char command[100];
   sprintf(command,"mmc write.p.continue 0x%x MPOOL 0x%x 0x%x",(unsigned int)buffer,(unsigned int)(mpart->block_count - (blk_cnt <<1) + (offset >> 9)),(unsigned int)blk_cnt<<9);
   ret=run_command((const char *)command, 0);
   
   free(mpart);
   
    return (ret != -1) ? 0 : -1;
}

inline int write_env(struct mmc *mmc, unsigned long size,
			unsigned long offset, const void *buffer)
{
    if(fpWriteEnv!=NULL)
    {
        return fpWriteEnv(mmc,size,offset,buffer);
    }
    else
    {
        return _write_env(mmc, size, offset, buffer);
    }

}

int saveenv(void)
{
    env_t *tmp_env1 = NULL;
    ssize_t	len;
    char *res=NULL;
    //struct mmc *mmc = find_mmc_device(CONFIG_SYS_MMC_ENV_DEV);
    u32 offset = 0;//CONFIG_ENV_OFFSET;

    tmp_env1 = (env_t *)malloc(CONFIG_ENV_SIZE);

    if (!tmp_env1) {
        set_default_env("!malloc() failed");
        return 1;
    }
#if 0
    struct mmc *mmc = find_mmc_device(CONFIG_SYS_MMC_ENV_DEV);

    if (init_mmc_for_env(mmc))
    return 1;

    if(mmc_get_env_addr(mmc, &offset))
    return 1;
#endif

    res = (char *)tmp_env1->data;
    len = hexport_r(&env_htab, '\0', &res, ENV_SIZE);
    if (len < 0) {
        error("Cannot export environment: errno = %d\n", errno);
        free(tmp_env1);
        return 1;
    }
    tmp_env1->crc   = crc32(0, tmp_env1->data, ENV_SIZE);
    printf("Writing to MMC(%d)... ", CONFIG_SYS_MMC_ENV_DEV);
    if (write_env(NULL, CONFIG_ENV_SIZE, offset, (u_char *)tmp_env1)) {
        puts("failed to save env\n");
        //return 1;
    }
    if (write_env(NULL, CONFIG_ENV_SIZE, (offset + CONFIG_ENV_SIZE), (u_char *)tmp_env1)) {
        puts("failed to save backup env\n");
        //return 1;
    }

    free(tmp_env1);
    puts("done\n");
    return 0;
}
#endif /* CONFIG_CMD_SAVEENV */
void RegisterCBReadEnv(read_env_cb cb)
{
    fpReadEnv=cb;
}

int _read_env(struct mmc *mmc, unsigned long size,
			unsigned long offset, const void *buffer)
{
    uint  blk_cnt,i,n;
    int ret;
    emmc_partition_t	*mpart;
    mpart = malloc(sizeof(*mpart));

    //blk_start = ALIGN(offset, 512) / 512;
    blk_cnt   = ALIGN(size, 512) / 512;

    //n = emmc_boot_read(mmc, 2, CONFIG_SYS_MMC_ENV_DEV, blk_start, blk_cnt, (unsigned long *)buffer);
    //n = eMMC_ReadBootPart((U8*)buffer, blk_cnt << 9, blk_start, 2);

    //MsApiChunkHeader_GetValue(CH_UBOOT_ENVIRONMENT_ROM_OFFSET, &blk_start);
    //MsApiChunkHeader_GetValue(CH_UBOOT_ENVIRONMENT_SIZE, &total_size);
	memset(mpart,0,sizeof(*mpart));

	for(i=1;i<= EMMC_RESERVED_FOR_MAP_V2;i++)
	{
		n = (uint)eMMC_ReadData((U8*)mpart, 512 , i);
		if(n != 0)
            return n;
		
		if(strcmp("MPOOL", (const char *)mpart->name)==0)
		{
             break;
		}
	}

	char command[100];
	sprintf(command,"mmc read.p.continue 0x%x MPOOL 0x%x 0x%x",(unsigned int)buffer,(unsigned int)(mpart->block_count - (blk_cnt <<1) + (offset >> 9)),(unsigned int)blk_cnt<<9);
	ret=run_command((const char *)command, 0);

    free(mpart);
    return (ret !=-1) ? 0 : -1;
}

inline int read_env(struct mmc *mmc, unsigned long size,
			unsigned long offset, const void *buffer)
{
    if(fpReadEnv!=NULL)
    {
        return fpReadEnv(mmc,size,offset,buffer);
    }
    else
    {
        return _read_env(mmc,size,offset,buffer);
    }
}

void env_relocate_spec(void)
{
#if !defined(ENV_IS_EMBEDDED)
    char *buf=malloc(CONFIG_ENV_SIZE+CONFIG_ENV_SIZE);
    char *bufbak=NULL;
    env_t *ep, *epbak;
    //struct mmc *mmc = find_mmc_device(CONFIG_SYS_MMC_ENV_DEV);
    u32 crc, crcbak, offset = 0;//CONFIG_ENV_OFFSET;
    int ret, retbak;
    if(!buf)
    {
        use_default();
        printf("malloc env buf fail, using default\n");
        return;
    }
    bufbak=buf+CONFIG_ENV_SIZE;
#if 0
    struct mmc *mmc = find_mmc_device(CONFIG_SYS_MMC_ENV_DEV);


    if (init_mmc_for_env(mmc)) {
        use_default();
        return;
    }

    if(mmc_get_env_addr(mmc, &offset)) {
        use_default();
        return ;
    }
#endif

    ret = read_env(NULL, CONFIG_ENV_SIZE, offset, buf);
    retbak = read_env(NULL, CONFIG_ENV_SIZE, (offset + CONFIG_ENV_SIZE), bufbak);
    ep = (env_t *)buf;
    epbak = (env_t *)bufbak;
    crc = crc32(0, ep->data, ENV_SIZE);
    crcbak = crc32(0, epbak->data, ENV_SIZE);

    if (((crc != ep->crc) || (ret == -1))&& ((crcbak != epbak->crc) || (retbak == -1)))
    {
        use_default();
        free(buf);
        return;
    }

    if (crc != ep->crc)
    {
        if (write_env(NULL, CONFIG_ENV_SIZE, offset, bufbak)) {
            puts("failed to resave env\n");
            //return 1;
        }
    }
    else if (crcbak != epbak->crc)
    {
        if (write_env(NULL, CONFIG_ENV_SIZE, offset + CONFIG_ENV_SIZE, buf)) {
            puts("failed to resave backup env\n");
            //return 1;
        }
    }
    env_import((crc != ep->crc) ? bufbak : buf, 1);
    free(buf);
#endif
}

#if !defined(ENV_IS_EMBEDDED)
static void use_default()
{
    set_default_env(NULL);
}
#endif
