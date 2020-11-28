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
#include <search.h>
#include <errno.h>

//MSTAR start
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

char *env_name_spec = "NAND";


#if defined(ENV_IS_EMBEDDED)
extern uchar environment[];
env_t *env_ptr = (env_t *)(&environment[0]);
#elif defined(CONFIG_NAND_ENV_DST)
env_t *env_ptr = (env_t *)CONFIG_NAND_ENV_DST;
#else /* ! ENV_IS_EMBEDDED */
env_t *env_ptr = 0;
#endif /* ENV_IS_EMBEDDED */

DECLARE_GLOBAL_DATA_PTR;

uchar env_get_char_spec (int index)
{
	return ( *((uchar *)(gd->env_addr + index)) );
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

	crc1_ok = (crc32(0, tmp_env1->data, ENV_SIZE) == tmp_env1->crc);

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
#ifdef CONFIG_ENV_OFFSET_REDUND
int writeenv(size_t offset, u_char *buf)
{
	size_t end = offset + CONFIG_ENV_RANGE;
	size_t amount_saved = 0;
	size_t blocksize, len;
	u_char *char_ptr;

	blocksize = nand_info[0].erasesize;
	len = min(blocksize, CONFIG_ENV_SIZE);

	while (amount_saved < CONFIG_ENV_SIZE && offset < end) {
		if (nand_block_isbad(&nand_info[0], offset)) {
			offset += blocksize;
		} else {
			char_ptr = &buf[amount_saved];
			if (nand_write(&nand_info[0], offset, &len,
					char_ptr))
				return 1;
			offset += blocksize;
			amount_saved += len;
		}
	}
	if (amount_saved != CONFIG_ENV_SIZE)
		return 1;

	return 0;
}
#else
extern unsigned int need_blk;
int writeenv(size_t offset, u_char *buf)
{
	size_t amount_saved = 0;
	size_t blocksize;
	unsigned char *rbuf;
    unsigned char *wbuf;
	struct nand_chip *chip = nand_info[0].priv;
	blocksize = nand_info[0].erasesize;
    int i;
	unsigned int write_length;
    unsigned int adr_offset=0;

    wbuf = malloc(nand_info[0].writesize+nand_info[0].oobsize);
    if(wbuf ==NULL)
	    return 1;

	rbuf = malloc(nand_info[0].writesize+nand_info[0].oobsize);
    if(rbuf ==NULL)
	    return 1;

	if (!blocksize)
		return 1;

    write_length = need_blk*2+2;

    for(i=0;i< write_length;i++)
    {
		chip->ops.ooblen = nand_info[0].oobsize;
		chip->ops.len    = nand_info[0].writesize;
		chip->ops.datbuf = rbuf;
		chip->ops.oobbuf = &rbuf[nand_info[0].writesize];
		chip->ops.ooboffs = 0;
		chip->ops.mode = MTD_OOB_RAW;

        nand_info[0].read_oob(&nand_info[0],offset, &chip->ops);

 		if (chip->ops.oobbuf[chip->badblockpos] != 0xff)
		{
			offset += blocksize;
			continue;
		}
		else
		{
            if(amount_saved >= (need_blk<<1))
            {
                break;
            }
			else
			{
                if (nand_write(&nand_info[0], offset, &blocksize, buf+adr_offset))
                {
                    memset(wbuf, '\0' , nand_info[0].writesize+nand_info[0].oobsize);
					chip->ops.ooblen = nand_info[0].oobsize;
					chip->ops.len    = nand_info[0].writesize;
					chip->ops.datbuf = wbuf;
					chip->ops.oobbuf = &wbuf[nand_info[0].writesize];
					chip->ops.ooboffs = 0;
					chip->ops.mode = MTD_OOB_RAW;

					nand_info[0].write_oob(&nand_info[0],offset,&chip->ops);
					offset += blocksize;
                }
			    else
			    {
			        offset += blocksize;
				    amount_saved++;
					if(need_blk >1)//block size smaller than CONFIG_ENV_SIZE
					{
					    if(amount_saved == need_blk)
						    adr_offset = 0;
						else
                            adr_offset += blocksize;
					}
			    }
			}
		}
    }
    free(wbuf);
	free(rbuf);
	if (amount_saved != (need_blk<<1))
		return 1;

	return 0;
}
#endif

#ifdef CONFIG_ENV_OFFSET_REDUND
static unsigned char env_flags;

int saveenv(void)
{
	env_t	env_new;
	ssize_t	len;
	char	*res;
	int	ret = 0;
	nand_erase_options_t nand_erase_options;

	memset(&nand_erase_options, 0, sizeof(nand_erase_options));
	nand_erase_options.length = CONFIG_ENV_RANGE;

	if (CONFIG_ENV_RANGE < CONFIG_ENV_SIZE)
		return 1;

	res = (char *)&env_new.data;
	len = hexport_r(&env_htab, '\0', &res, ENV_SIZE);
	if (len < 0) {
		error("Cannot export environment: errno = %d\n", errno);
		return 1;
	}
	env_new.crc   = crc32(0, env_new.data, ENV_SIZE);
	env_new.flags = ++env_flags; /* increase the serial */

	if(gd->env_valid == 1) {
		puts("Erasing redundant NAND...\n");
		nand_erase_options.offset = CONFIG_ENV_OFFSET_REDUND;
		if (nand_erase_opts(&nand_info[0], &nand_erase_options))
			return 1;

		puts("Writing to redundant NAND... ");
		ret = writeenv(CONFIG_ENV_OFFSET_REDUND,
			(u_char *)&env_new);
	} else {
		puts("Erasing NAND...\n");
		nand_erase_options.offset = CONFIG_ENV_OFFSET;
		if (nand_erase_opts(&nand_info[0], &nand_erase_options))
			return 1;

		puts("Writing to NAND... ");
		ret = writeenv(CONFIG_ENV_OFFSET,
			(u_char *)&env_new);
	}
	if (ret) {
		puts("FAILED!\n");
		return 1;
	}

	puts("done\n");

	gd->env_valid = (gd->env_valid == 2 ? 1 : 2);

	return ret;
}
#else /* ! CONFIG_ENV_OFFSET_REDUND */
int saveenv(void)
{
	int ret = 0;
	env_t	env_new;
	ssize_t	len;
	char	*res;
	nand_erase_options_t nand_erase_options;

	memset(&nand_erase_options, 0, sizeof(nand_erase_options));

	nand_erase_options.length = (need_blk*2+2)*nand_info[0].erasesize;
	nand_erase_options.offset = cfg_env_offset;

	res = (char *)&env_new.data;
	len = hexport_r(&env_htab, '\0', &res, ENV_SIZE);
	if (len < 0) {
		error("Cannot export environment: errno = %d\n", errno);
		return 1;
	}
	env_new.crc   = crc32(0, env_new.data, ENV_SIZE);

	puts("Erasing Nand...\n");
	if (nand_erase_env(&nand_info[0], &nand_erase_options))
		return 1;

	puts("Writing to Nand... \n");
	if (writeenv(cfg_env_offset, (u_char *)&env_new)) {
		puts("FAILED!\n");
		return 1;
	}
	puts("done\n");
	return ret;
}
#endif /* CONFIG_ENV_OFFSET_REDUND */
#endif /* CMD_SAVEENV */

#ifdef CONFIG_ENV_OFFSET_REDUND
int readenv(size_t offset, u_char * buf)
{
	size_t end = offset + CONFIG_ENV_RANGE;
	size_t amount_loaded = 0;
	size_t blocksize, len;

	u_char *char_ptr;

	blocksize = nand_info[0].erasesize;
	if (!blocksize)
		return 1;
	len = min(blocksize, CONFIG_ENV_SIZE);

	while (amount_loaded < CONFIG_ENV_SIZE && offset < end) {
		if (nand_block_isbad(&nand_info[0], offset)) {
			offset += blocksize;
		} else {
			char_ptr = &buf[amount_loaded];
			if (nand_read_skip_bad(&nand_info[0], offset, &len, char_ptr))
				return 1;
			offset += blocksize;
			amount_loaded += len;
		}
	}
	if (amount_loaded != CONFIG_ENV_SIZE)
		return 1;

	return 0;
}
#else

unsigned char env_need_refresh = 0;

int readenv(size_t offset, u_char * buf)
{
	size_t amount_loaded = 0;
	size_t blocksize;
	size_t offset_scan = offset;
	struct nand_chip *chip = nand_info[0].priv;
	int i, j;
	unsigned int read_length;
	unsigned int env_bbt = 0;
	unsigned int env_bbt_mask;
	unsigned int adr_offset = 0;
	int bakup_start =0;//bakup env data region start block
    unsigned char *cptr = NULL;
    unsigned char *cptr2 = NULL;
	unsigned char *rbuf = NULL;

    env_t *ep = 0;
    uint32_t crc;

	rbuf = malloc(nand_info[0].writesize+nand_info[0].oobsize);
    if(rbuf ==NULL)
	    return 1;

    blocksize = nand_info[0].erasesize;
	if (!blocksize)
		return 1;

    read_length = need_blk*2+2;
    env_bbt_mask = (1<<read_length)-1;
    cptr = malloc(need_blk * blocksize);
    if(cptr == NULL)
	    return 1;

    cptr2 = malloc(need_blk * blocksize);
    if(cptr2 == NULL)
	    return 1;

    for(i=0;i< read_length;i++)
    {
		chip->ops.ooblen = nand_info[0].oobsize;
		chip->ops.len    = nand_info[0].writesize;
		chip->ops.datbuf = rbuf;
		chip->ops.oobbuf = &rbuf[nand_info[0].writesize];
		chip->ops.ooboffs = 0;
		chip->ops.mode = MTD_OOB_RAW;

        nand_info[0].read_oob(&nand_info[0],offset_scan, &chip->ops);
 		if (chip->ops.oobbuf[chip->badblockpos] != 0xff)
		{
		    env_bbt |= 1<< i;
		}
		offset_scan += blocksize;
    }
    env_bbt = env_bbt_mask - env_bbt;
    //find bakup env data region start block
    for(i=0;i< read_length;i++)
    {
       bakup_start++;
       if(env_bbt & (1<< i))
       {
	       amount_loaded++;
		   if(amount_loaded == need_blk)
		       break;
       }
    }
	amount_loaded = 0;

    // 1st Env block
    for(i=0; i<read_length; i++)
    {
        chip->ops.ooblen = nand_info[0].oobsize;
		chip->ops.len    = nand_info[0].writesize;
		chip->ops.datbuf = rbuf;
		chip->ops.oobbuf = &rbuf[nand_info[0].writesize];
		chip->ops.ooboffs = 0;
		chip->ops.mode = MTD_OOB_RAW;

        // Find good block with Env
        nand_info[0].read_oob(&nand_info[0],offset, &chip->ops);
        if (chip->ops.oobbuf[chip->badblockpos] != 0xff)
		{
			offset += blocksize;
			continue;
		}
		else
        {
            if (nand_read(&nand_info[0], offset, &blocksize, cptr+adr_offset))
            {
                if(i < bakup_start)
                {
                    offset += ((bakup_start-i)*blocksize);//goto bakup region
					adr_offset = 0;
					amount_loaded = 0;
				}
				else
                {
                    printf("\033[31m 1st Env block has read error. Need to refresh!\033[m\n");
                    env_need_refresh = 1;
                    offset += blocksize;
                    break;
                }
            }
            else
            {
			    offset += blocksize;
			    amount_loaded++;
				adr_offset += blocksize;

				if(amount_loaded >= need_blk)
				    break;
			}
        }
    }

    // Check 1st Env CRC
    ep = (env_t *)cptr;

    memcpy(&crc, &ep->crc, sizeof(crc));

    if (crc32(0, ep->data, ENV_SIZE) != crc)
    {
        printf("\033[31m 1st Env block has CRC error. Need to refresh!\033[m\n");
        free(cptr);
        cptr = NULL;
        env_need_refresh = 1;
    }

    // Check 2nd Env block
    adr_offset = 0;

    for(j=0; j<(read_length-i); j++)
    {
        chip->ops.ooblen = nand_info[0].oobsize;
        chip->ops.len    = nand_info[0].writesize;
        chip->ops.datbuf = rbuf;
        chip->ops.oobbuf = &rbuf[nand_info[0].writesize];
        chip->ops.ooboffs = 0;
        chip->ops.mode = MTD_OOB_RAW;

        nand_info[0].read_oob(&nand_info[0],offset, &chip->ops);
        if (chip->ops.oobbuf[chip->badblockpos] != 0xff)
        {
            offset += blocksize;
            continue;
        }
        else
        {
            if (nand_read(&nand_info[0], offset, &blocksize, cptr2+adr_offset))
            {
                printf("\033[31m 2nd Env block has read error. Need to refresh!\033[m\n");
                env_need_refresh = 1;
                break;
            }
            else
            {
                break;
            }
        }
    }

    // Check 2nd Env CRC
    ep = (env_t *)cptr2;

    memcpy(&crc, &ep->crc, sizeof(crc));

    if (crc32(0, ep->data, ENV_SIZE) != crc)
    {
        printf("\033[31m 2nd Env block has CRC error. Need to refresh!\033[m\n");
        free(cptr2);
        cptr2 = NULL;
        env_need_refresh = 1;
    }

    if( cptr )
    {
        memcpy(buf,cptr,CONFIG_ENV_SIZE);
	    free(cptr);
    }

    if( cptr2 )
    {
        if( !cptr )
            memcpy(buf,cptr2,CONFIG_ENV_SIZE);
        free(cptr2);
    }

	free(rbuf);
	if (amount_loaded != need_blk)
		return 1;

	return 0;
}
#endif

#ifdef CONFIG_ENV_OFFSET_OOB
int get_nand_env_oob(nand_info_t *nand, unsigned long *result)
{
	struct mtd_oob_ops ops;
	uint32_t oob_buf[ENV_OFFSET_SIZE/sizeof(uint32_t)];
	int ret;

	ops.datbuf = NULL;
	ops.mode = MTD_OOB_AUTO;
	ops.ooboffs = 0;
	ops.ooblen = ENV_OFFSET_SIZE;
	ops.oobbuf = (void *) oob_buf;

	ret = nand->read_oob(nand, ENV_OFFSET_SIZE, &ops);
	if (ret) {
		printf("error reading OOB block 0\n");
		return ret;
	}

	if (oob_buf[0] == ENV_OOB_MARKER) {
		*result = oob_buf[1] * nand->erasesize;
	} else if (oob_buf[0] == ENV_OOB_MARKER_OLD) {
		*result = oob_buf[1];
	} else {
		printf("No dynamic environment marker in OOB block 0\n");
		return -ENOENT;
	}

	return 0;
}
#endif

#ifdef CONFIG_ENV_OFFSET_REDUND
void env_relocate_spec(void)
{
#if !defined(ENV_IS_EMBEDDED)
	int crc1_ok = 0, crc2_ok = 0;
	env_t *ep, *tmp_env1, *tmp_env2;

	tmp_env1 = (env_t *)malloc(CONFIG_ENV_SIZE);
	tmp_env2 = (env_t *)malloc(CONFIG_ENV_SIZE);

	if ((tmp_env1 == NULL) || (tmp_env2 == NULL)) {
		puts("Can't allocate buffers for environment\n");
		free(tmp_env1);
		free(tmp_env2);
		set_default_env("!malloc() failed");
		return;
	}

	if (readenv(CONFIG_ENV_OFFSET, (u_char *) tmp_env1))
		puts("No Valid Environment Area found\n");

	if (readenv(CONFIG_ENV_OFFSET_REDUND, (u_char *) tmp_env2))
		puts("No Valid Redundant Environment Area found\n");

	crc1_ok = (crc32(0, tmp_env1->data, ENV_SIZE) == tmp_env1->crc);
	crc2_ok = (crc32(0, tmp_env2->data, ENV_SIZE) == tmp_env2->crc);

	if (!crc1_ok && !crc2_ok) {
		free(tmp_env1);
		free(tmp_env2);
		set_default_env("!bad CRC");
		return;
	} else if (crc1_ok && !crc2_ok) {
		gd->env_valid = 1;
	} else if (!crc1_ok && crc2_ok) {
		gd->env_valid = 2;
	} else {
		/* both ok - check serial */
		if (tmp_env1->flags == 255 && tmp_env2->flags == 0)
			gd->env_valid = 2;
		else if (tmp_env2->flags == 255 && tmp_env1->flags == 0)
			gd->env_valid = 1;
		else if (tmp_env1->flags > tmp_env2->flags)
			gd->env_valid = 1;
		else if (tmp_env2->flags > tmp_env1->flags)
			gd->env_valid = 2;
		else /* flags are equal - almost impossible */
			gd->env_valid = 1;

	}

	free(env_ptr);

	if (gd->env_valid == 1)
		ep = tmp_env1;
	else
		ep = tmp_env2;

	env_flags = ep->flags;
	env_import((char *)ep, 0);

	free(tmp_env1);
	free(tmp_env2);

#endif /* ! ENV_IS_EMBEDDED */
}
#else /* ! CONFIG_ENV_OFFSET_REDUND */
/*
 * The legacy NAND code saved the environment in the first NAND
 * device i.e., nand_dev_desc + 0. This is also the behaviour using
 * the new NAND code.
 */
void env_relocate_spec (void)
{
#if !defined(ENV_IS_EMBEDDED)
	int ret;
	char buf[CONFIG_ENV_SIZE];

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

	ret = readenv(cfg_env_offset, (u_char *)buf);
	if (ret) {
		set_default_env("!readenv() failed");
		return;
	}

	env_import(buf, 1);

    if( env_need_refresh )
    {
        saveenv();
        env_need_refresh = 0;
    }

#endif /* ! ENV_IS_EMBEDDED */
}
#endif /* CONFIG_ENV_OFFSET_REDUND */
