/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Alex Zuepke <azu@sysgo.de>
 *
 * (C) Copyright 2002
 * Gary Jennejohn, DENX Software Engineering, <garyj@denx.de>
 *
 * (C) Copyright 2004
 * DAVE Srl
 * http://www.dave-tech.it
 * http://www.wawnet.biz
 * mailto:info@wawnet.biz
 *
 * (C) Copyright 2004 Texas Insturments
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
// MSTAR start
#include <MsTypes.h>
#include <MsUboot.h>
#include <drvMMIO.h>
#include <MsDevice.h>
// MSTAR end

int do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	printf("\n[AT][MB][start do_reset] \n");
#if 1 // MSTAR
    {
        MS_U32 u32Tmp=0;
        MDrv_MMIO_GetBASE((MS_U32 *) &RIU_MAP, &u32Tmp, MS_MODULE_PM);
        printf("%s: Using RIU_MAP: 0x%lx, at %d\n", __func__, RIU_MAP, __LINE__);
        RIU_MAP = 0x1F000000; //TODO: fix it, when mmu is ready
    }
#endif

	udelay (50000);				/* wait 50 ms */


	disable_interrupts();
#if 1 // MSTAR
        MDrv_Sys_WholeChipReset();
#else
	reset_cpu(0);
#endif

	/*NOTREACHED*/
	return 0;
}
