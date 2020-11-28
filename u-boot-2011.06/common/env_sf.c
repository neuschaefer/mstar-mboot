/*
 * (C) Copyright 2000-2010
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2001 Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Andreas Heppel <aheppel@sysgo.de>
 *
 * (C) Copyright 2008 Atmel Corporation
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
#include <common.h>
#include <environment.h>
#include <malloc.h>
#include <spi_flash.h>
#include <search.h>
#include <errno.h>
// MSTAR start
#include <drvSERFLASH.h>
#include <flash.h>
// MSTAR end

#ifndef CONFIG_ENV_SPI_BUS
# define CONFIG_ENV_SPI_BUS	0
#endif
#ifndef CONFIG_ENV_SPI_CS
# define CONFIG_ENV_SPI_CS		0
#endif
#ifndef CONFIG_ENV_SPI_MAX_HZ
# define CONFIG_ENV_SPI_MAX_HZ	1000000
#endif
#ifndef CONFIG_ENV_SPI_MODE
# define CONFIG_ENV_SPI_MODE	SPI_MODE_3
#endif

#ifdef CONFIG_ENV_OFFSET_REDUND
static ulong env_offset = CONFIG_ENV_OFFSET;
static ulong env_new_offset = CONFIG_ENV_OFFSET_REDUND;

#define ACTIVE_FLAG   1
#define OBSOLETE_FLAG 0
#endif /* CONFIG_ENV_OFFSET_REDUND */

DECLARE_GLOBAL_DATA_PTR;

/* references to names in env_common.c */
extern uchar default_environment[];
// MSTART start
#if CONFIG_JANUS2
#define SPIFLASH_KSEG0_ADDR 0xb4000000
#else
#if defined(__ARM__)
#define SPIFLASH_KSEG0_ADDR 0x14000000
#else
#define SPIFLASH_KSEG0_ADDR 0x94000000
#endif
#endif
env_t *env_ptr = NULL;
extern int default_environment_size;
extern unsigned int cfg_env_offset;
// MSTART end

char * env_name_spec = "SPI Flash";
#if defined(CONFIG_ENV_IS_IN_SPIFLASH)
static int env_empty = 0;
#endif
// MSTART start
//static struct spi_flash *env_flash;
// MSTART end

uchar env_get_char_spec(int index)
{
    return *((uchar *)(gd->env_addr + index));
}

#if defined(CONFIG_ENV_OFFSET_REDUND)

int saveenv(void)
{
    env_t	env_new;
    ssize_t	len;
    char	*res;
    u32	saved_size, saved_offset;
    char	*saved_buffer = NULL;
    u32	sector = 1;
    int	ret;
    char	flag = OBSOLETE_FLAG;

    if (!env_flash) {
        env_flash = spi_flash_probe(CONFIG_ENV_SPI_BUS,
            CONFIG_ENV_SPI_CS,
            CONFIG_ENV_SPI_MAX_HZ, CONFIG_ENV_SPI_MODE);
        if (!env_flash) {
            set_default_env("!spi_flash_probe() failed");
            return 1;
        }
    }

    res = (char *)&env_new.data;
    len = hexport_r(&env_htab, '\0', &res, ENV_SIZE);
    if (len < 0) {
        error("Cannot export environment: errno = %d\n", errno);
        return 1;
    }
    env_new.crc   = crc32(0, env_new.data, ENV_SIZE);
    env_new.flags = ACTIVE_FLAG;

    if (gd->env_valid == 1) {
        env_new_offset = CONFIG_ENV_OFFSET_REDUND;
        env_offset = CONFIG_ENV_OFFSET;
    } else {
        env_new_offset = CONFIG_ENV_OFFSET;
        env_offset = CONFIG_ENV_OFFSET_REDUND;
    }

    /* Is the sector larger than the env (i.e. embedded) */
    if (CONFIG_ENV_SECT_SIZE > CONFIG_ENV_SIZE) {
        saved_size = CONFIG_ENV_SECT_SIZE - CONFIG_ENV_SIZE;
        saved_offset = env_new_offset + CONFIG_ENV_SIZE;
        saved_buffer = malloc(saved_size);
        if (!saved_buffer) {
            ret = 1;
            goto done;
        }
        ret = spi_flash_read(env_flash, saved_offset,
            saved_size, saved_buffer);
        if (ret)
            goto done;
    }

    if (CONFIG_ENV_SIZE > CONFIG_ENV_SECT_SIZE) {
        sector = CONFIG_ENV_SIZE / CONFIG_ENV_SECT_SIZE;
        if (CONFIG_ENV_SIZE % CONFIG_ENV_SECT_SIZE)
            sector++;
    }

    puts("Erasing SPI flash...");
    ret = spi_flash_erase(env_flash, env_new_offset,
        sector * CONFIG_ENV_SECT_SIZE);
    if (ret)
        goto done;

    puts("Writing to SPI flash...");

    ret = spi_flash_write(env_flash, env_new_offset,
        CONFIG_ENV_SIZE, &env_new);
    if (ret)
        goto done;

    if (CONFIG_ENV_SECT_SIZE > CONFIG_ENV_SIZE) {
        ret = spi_flash_write(env_flash, saved_offset,
            saved_size, saved_buffer);
        if (ret)
        goto done;
    }

    ret = spi_flash_write(env_flash,
        env_offset + offsetof(env_t, flags),
        sizeof(env_new.flags), &flag);
    if (ret)
        goto done;

    puts("done\n");

    gd->env_valid = (gd->env_valid == 2 ? 1 : 2);

    printf("Valid environment: %d\n", (int)gd->env_valid);

 done:
    if (saved_buffer)
        free(saved_buffer);
    return ret;
}

void env_relocate_spec(void)
{
    int ret;
    int crc1_ok = 0, crc2_ok = 0;
    env_t *tmp_env1 = NULL;
    env_t *tmp_env2 = NULL;
    env_t *ep = NULL;

    tmp_env1 = (env_t *)malloc(CONFIG_ENV_SIZE);
    tmp_env2 = (env_t *)malloc(CONFIG_ENV_SIZE);

    if (!tmp_env1 || !tmp_env2) {
        set_default_env("!malloc() failed");
        goto out;
    }

    env_flash = spi_flash_probe(CONFIG_ENV_SPI_BUS, CONFIG_ENV_SPI_CS,
        CONFIG_ENV_SPI_MAX_HZ, CONFIG_ENV_SPI_MODE);
    if (!env_flash) {
        set_default_env("!spi_flash_probe() failed");
        goto out;
    }

    ret = spi_flash_read(env_flash, CONFIG_ENV_OFFSET,
        CONFIG_ENV_SIZE, tmp_env1);
    if (ret) {
        set_default_env("!spi_flash_read() failed");
        goto err_read;
    }

    if (crc32(0, tmp_env1->data, ENV_SIZE) == tmp_env1->crc)
        crc1_ok = 1;

    ret = spi_flash_read(env_flash, CONFIG_ENV_OFFSET_REDUND,
        CONFIG_ENV_SIZE, tmp_env2);
    if (!ret) {
        if (crc32(0, tmp_env2->data, ENV_SIZE) == tmp_env2->crc)
            crc2_ok = 1;
    }

    if (!crc1_ok && !crc2_ok) {
        set_default_env("!bad CRC");
        goto err_read;
    } else if (crc1_ok && !crc2_ok) {
        gd->env_valid = 1;
    } else if (!crc1_ok && crc2_ok) {
        gd->env_valid = 2;
    } else if (tmp_env1->flags == ACTIVE_FLAG &&
        tmp_env2->flags == OBSOLETE_FLAG) {
        gd->env_valid = 1;
    } else if (tmp_env1->flags == OBSOLETE_FLAG &&
        tmp_env2->flags == ACTIVE_FLAG) {
        gd->env_valid = 2;
    } else if (tmp_env1->flags == tmp_env2->flags) {
        gd->env_valid = 2;
    } else if (tmp_env1->flags == 0xFF) {
        gd->env_valid = 2;
    } else {
        /*
        * this differs from code in env_flash.c, but I think a sane
        * default path is desirable.
        */
        gd->env_valid = 2;
    }

    if (gd->env_valid == 1)
        ep = tmp_env1;
    else
        ep = tmp_env2;

    ret = env_import((char *)ep, 0);
    if (!ret) {
        error("Cannot import environment: errno = %d\n", errno);
        set_default_env("env_import failed");
    }

err_read:
    spi_flash_free(env_flash);
    env_flash = NULL;
out:
    free(tmp_env1);
    free(tmp_env2);

    return;
}
#else
//MSTAR start
static int write_flash(MS_U32 u32Addr, const MS_U8* pu8Src, MS_U32 u32Size)
{
//#if (!CONFIG_MSTAR_SILENT)
    printf("Write addr=0x%08x, size=0x%08x\n", (unsigned int)u32Addr, (unsigned int)u32Size);
//#endif

    MDrv_SERFLASH_WriteProtect(FALSE);

    int ret = -1;

    if(u32Size>0x1000) // a sector size is 4KBytes
    {
        printf("block erase\n");
        ret=MDrv_SERFLASH_AddressErase(u32Addr, u32Size, TRUE);
    }
    else
    {
        printf("sector erase\n");
        ret=MDrv_SERFLASH_SectorErase(u32Addr, u32Addr+u32Size-1);
    }
    if (ret!=-1)
    {
        if (MDrv_SERFLASH_Write(u32Addr, u32Size, (MS_U8*)pu8Src))
        {
            ret = 0;
        }
    }

    MDrv_SERFLASH_WriteProtect(TRUE);

    return ret;
}
//MSTAR end

int saveenv(void)
{
#if 1 //MSTAR
    ssize_t	len=0;
    char *res=NULL;

    //MDrv_SERFLASH_Init();
    res = (char *)&(env_ptr->data);
    len = hexport_r(&env_htab, '\0', &res, ENV_SIZE);
    if (len < 0) {
        error("Cannot export environment: errno = %d\n", errno);
        return -1;
    }
    env_ptr->crc   = crc32(0, env_ptr->data, ENV_SIZE);
#ifdef CONFIG_SYS_REDUNDAND_ENVIRONMENT
    env_ptr->flags = ++env_flags; /* increase the serial */
#endif
    int ret = write_flash(CONFIG_ENV_ADDR, (MS_U8*)env_ptr, CONFIG_ENV_SIZE);
    int retBak = write_flash(CONFIG_ENV_ADDR_BAK, (MS_U8*)env_ptr, CONFIG_ENV_SIZE);
    if( (ret == 0) && (retBak == 0) )
        return 0;
    else
        return -1;
#else //MSTAR
	u32 saved_size, saved_offset;
	char *saved_buffer = NULL;
	u32 sector = 1;
	int ret = 1;
	env_t	env_new;
	char	*res;
	ssize_t	len;

	if (!env_flash) {
		env_flash = spi_flash_probe(CONFIG_ENV_SPI_BUS,
			CONFIG_ENV_SPI_CS,
			CONFIG_ENV_SPI_MAX_HZ, CONFIG_ENV_SPI_MODE);
		if (!env_flash) {
			set_default_env("!spi_flash_probe() failed");
			return 1;
		}
	}

	/* Is the sector larger than the env (i.e. embedded) */
	if (CONFIG_ENV_SECT_SIZE > CONFIG_ENV_SIZE) {
		saved_size = CONFIG_ENV_SECT_SIZE - CONFIG_ENV_SIZE;
		saved_offset = CONFIG_ENV_OFFSET + CONFIG_ENV_SIZE;
		saved_buffer = malloc(saved_size);
		if (!saved_buffer) {
			goto done;
		}
		ret = spi_flash_read(env_flash, saved_offset,
			saved_size, saved_buffer);
		if (ret)
			goto done;
	}

	if (CONFIG_ENV_SIZE > CONFIG_ENV_SECT_SIZE) {
		sector = CONFIG_ENV_SIZE / CONFIG_ENV_SECT_SIZE;
		if (CONFIG_ENV_SIZE % CONFIG_ENV_SECT_SIZE)
			sector++;
	}

	res = (char *)&env_new.data;
	len = hexport_r(&env_htab, '\0', &res, ENV_SIZE);
	if (len < 0) {
		error("Cannot export environment: errno = %d\n", errno);
		goto done;
	}
	env_new.crc = crc32(0, env_new.data, ENV_SIZE);

	puts("Erasing SPI flash...");
	ret = spi_flash_erase(env_flash, CONFIG_ENV_OFFSET,
		sector * CONFIG_ENV_SECT_SIZE);
	if (ret)
		goto done;

	puts("Writing to SPI flash...");
	ret = spi_flash_write(env_flash, CONFIG_ENV_OFFSET,
		CONFIG_ENV_SIZE, &env_new);
	if (ret)
		goto done;

	if (CONFIG_ENV_SECT_SIZE > CONFIG_ENV_SIZE) {
		ret = spi_flash_write(env_flash, saved_offset,
			saved_size, saved_buffer);
		if (ret)
			goto done;
	}

	ret = 0;
	puts("done\n");

 done:
	if (saved_buffer)
		free(saved_buffer);
	return ret;
#endif //MSTAR
}

#if 1 //MSTAR
void env_relocate_spec (void)
{
    extern void set_default_env(const char *s);
    int ret=0;
    void* pEnvBuf = malloc(CONFIG_ENV_SIZE);
    if(pEnvBuf==NULL) 
    {
        printf("%s: malloc() failed, at %d\n", __func__, __LINE__);
        return;
    }
    memset(pEnvBuf, 0, CONFIG_ENV_SIZE);
#if 0 // use BDMA instead of memcpy to speed up boot time
    flush_cache((MS_PHYADDR)pEnvBuf,CONFIG_ENV_SIZE);
    MDrv_BDMA_FlashCopy2Dram(  CONFIG_ENV_ADDR , (MS_PHYADDR)pEnvBuf, CONFIG_ENV_SIZE);
#else
    memcpy(pEnvBuf, (void*)(SPIFLASH_KSEG0_ADDR + CONFIG_ENV_ADDR), CONFIG_ENV_SIZE);
#endif

#if defined(CONFIG_ENV_IS_IN_SPIFLASH)
    uchar EnvFlag[4]={0};
    memcpy((uchar*)EnvFlag, (void*)(SPIFLASH_KSEG0_ADDR + CONFIG_ENV_ADDR), sizeof(EnvFlag));
    if((ulong)&EnvFlag[0] == 0xFFFFFFFF)
    {
        env_empty = 1;
    }
    else
    {
        env_empty = 0;
    }
#endif
    void* pEnvBufBak = malloc(CONFIG_ENV_SIZE);
    if(pEnvBufBak==NULL){
        free(pEnvBuf);
        return;
    }
    memset(pEnvBufBak, 0, CONFIG_ENV_SIZE);
#if 0 // use BDMA instead of memcpy to speed up boot time
    flush_cache( (MS_PHYADDR)  pEnvBufBak,CONFIG_ENV_SIZE);
    MDrv_BDMA_FlashCopy2Dram(  CONFIG_ENV_ADDR_BAK , (MS_PHYADDR)pEnvBufBak, CONFIG_ENV_SIZE);
#else
    memcpy(pEnvBufBak, (void*)(SPIFLASH_KSEG0_ADDR + CONFIG_ENV_ADDR_BAK), CONFIG_ENV_SIZE);
#endif

    size_t offsetCrc = offsetof(env_t, crc);
    size_t offsetData = offsetof(env_t, data);

    ulong crc = *(ulong *)(pEnvBuf + offsetCrc);
    ulong crcNew = crc32(0, pEnvBuf + offsetData, ENV_SIZE);
    ulong crcBak = *(ulong *)(pEnvBufBak + offsetCrc);
    ulong crcNewBak = crc32(0, pEnvBufBak + offsetData, ENV_SIZE);

    if ( (crc != crcNew) && (crcBak != crcNewBak) )
    {
        set_default_env("!bad CRC");
        memcpy (env_ptr->data, default_environment, default_environment_size);
        env_ptr->crc = crc32(0, env_ptr->data, ENV_SIZE);
        gd->env_valid = 1;
        goto Exit;
    }

    if (crc != crcNew)
    {
        write_flash(CONFIG_ENV_ADDR, (MS_U8*)pEnvBufBak, CONFIG_ENV_SIZE);
    }
    else if (crcBak != crcNewBak)
    {
        write_flash(CONFIG_ENV_ADDR_BAK, (MS_U8*)pEnvBuf, CONFIG_ENV_SIZE);
    }

    memcpy(env_ptr, (crc != crcNew) ? pEnvBufBak : pEnvBuf, CONFIG_ENV_SIZE);
    ret = env_import((const char *)env_ptr, 1);
    if (ret)
    {
        gd->env_valid = 1;
    }
    else
    {
        printf("%s: env_import() failed, at %d\n", __func__, __LINE__);
    }

Exit:
    free(pEnvBufBak);
    free(pEnvBuf);
}
#else //MSTAR
void env_relocate_spec(void)
{
	char buf[CONFIG_ENV_SIZE];
	int ret;

	env_flash = spi_flash_probe(CONFIG_ENV_SPI_BUS, CONFIG_ENV_SPI_CS,
			CONFIG_ENV_SPI_MAX_HZ, CONFIG_ENV_SPI_MODE);
	if (!env_flash) {
		set_default_env("!spi_flash_probe() failed");
		return;
	}

	ret = spi_flash_read(env_flash,
		CONFIG_ENV_OFFSET, CONFIG_ENV_SIZE, buf);
	if (ret) {
		set_default_env("!spi_flash_read() failed");
		goto out;
	}

	ret = env_import(buf, 1);

	if (ret)
		gd->env_valid = 1;
out:
	spi_flash_free(env_flash);
	env_flash = NULL;
}
#endif //MSTAR
#endif

// MSTAR start
flash_info_t flash_info[CONFIG_SYS_MAX_FLASH_BANKS];	/* info for FLASH chips */

/*-----------------------------------------------------------------------
 * flash_init()
 *
 * sets up flash_info and returns size of FLASH (bytes)
 */
int spi_init (void)
{
#if (ENABLE_MODULE_ENV_IN_SERIAL==1)
    int i, j;
    const SERFLASH_Info *pSPIFlashInfo;

    MDrv_SERFLASH_Init();
    pSPIFlashInfo = MDrv_SERFLASH_GetInfo();
    if(pSPIFlashInfo==NULL) {
        printf("flash_init fail\n");
        return -1;
    }

    // init flash_info
    for (i = 0; i < CONFIG_SYS_MAX_FLASH_BANKS; i++)
    {
        flash_info[i].size = pSPIFlashInfo->u32TotalSize;
        flash_info[i].sector_count = pSPIFlashInfo->u32SecNum;
        for (j = 0; j < pSPIFlashInfo->u32SecNum; j++)
        {
            flash_info[i].start[j] = j * pSPIFlashInfo->u32SecSize;
        }
    }

    // set environment offset on spi flash.
    #if(CONFIG_FORCE_TO_ASSIGN_ENV_OFFSET==1)
    cfg_env_offset = CONFIG_ENV_VAR_OFFSET;
    #else
    cfg_env_offset = pSPIFlashInfo->u32TotalSize - (CONFIG_ENV_SIZE << 1);
    #endif

#endif
    return 0;
}
// MSTAR end

int env_init(void)
{
	/* SPI flash isn't usable before relocation */
	gd->env_addr = (ulong)&default_environment[0];
	gd->env_valid = 1;

	return 0;
}
#if defined(CONFIG_ENV_IS_IN_SPIFLASH)
int env_isempty(void)
{
    return env_empty;
}
#endif
