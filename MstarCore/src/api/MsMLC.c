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

#include <config.h>
#include <common.h>
#include <command.h>
#include <malloc.h>
#include <watchdog.h>
#include <fat.h>
#include <drvWDT.h>
#include <MsMath.h>
#include <u-boot/crc.h>

#include <MsMLC.h>

#ifdef CONFIG_LZO
#include <linux/lzo.h>
#endif
#include "../disk/part_emmc.h"


// =======================================================================
// MLC test cmd
// =======================================================================
int do_MsMLC(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	if (argc < 2)
		return cmd_usage(cmdtp);
	
	//============================
	if (strcmp(argv[1], "info") == 0)
	{

		return 0;
	}
	else if (strcmp(argv[1], "init") == 0)
	{
		
		return 0;
	}

	//============================
    #if defined(IF_IP_VERIFY) && IF_IP_VERIFY
	else if (strcmp(argv[1], "test") == 0)
	{
		u32 u32_LoopCnt, u32_i;

		u32_LoopCnt = simple_strtoul(argv[2], NULL, 16);
		
		for(u32_i=0; u32_i<u32_LoopCnt; u32_i++)
		{
			printf("Test: %u \n", u32_i);
			//if(MLC_ST_SUCCESS != u32_err)
		//		break;
		}

		return 0;
	}		
    #endif
	
	//============================
	

	return cmd_usage(cmdtp);
}


