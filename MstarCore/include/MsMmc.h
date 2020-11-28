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

#ifndef __CMD_MS_MMC__
#define __CMD_MS_MMC__
#include <common.h>

struct emmc_write_options {
	ulong *buffer;		/* memory block containing image to write */
       char *fatfile_name; /* only be used for emmc binary restore, transfer the binary file name */
	u64 length;		/* number of bytes to write */
	u64 offset;		/* start address in EMMC */
	int quiet;		/* don't display progress messages */
	int pad;		/* pad to page size */
};

typedef struct emmc_write_options emmc_write_options_t;

struct emmc_read_options {
    u_char *buffer;     /* memory block in which read image is written*/
    char *fatfile_name; /* only be used for emmc binary making, transfer the binary file name */
    u64 length;       /* number of bytes to read */
    u64 offset;       /* start address in EMMC */
    int quiet;      /* don't display progress messages */
	int bootno;     /* boot partition number, 1 or 2 */
};

struct mmc_bininfo{
	ulong valid_block;
	disk_partition_t dpt; 
};

typedef struct emmc_read_options emmc_read_options_t;

#ifndef CONFIG_GENERIC_MMC
int do_mmc (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
#else
int do_mmcinfo (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_mmcreg (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);

#if defined(CONFIG_USB) && defined(CONFIG_FAT)
int do_emmc_bin_restore(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_emmcboot_mkbin(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_emmc_mkbin(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
#endif

int do_mmc_bininfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_mmcops(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_eMMCops(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
#endif

int get_mmc_partsize (char *puPartName,unsigned int *u32PartSize);

#endif
