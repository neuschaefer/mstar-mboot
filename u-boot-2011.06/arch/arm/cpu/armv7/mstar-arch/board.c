/*
 *
 * Common functions for OMAP4 based boards
 *
 * (C) Copyright 2010
 * Texas Instruments, <www.ti.com>
 *
 * Author :
 *	Aneesh V	<aneesh@ti.com>
 *	Steve Sakoman	<steve@sakoman.com>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
#include <common.h>
#include <asm/arch/cpu.h>
#include <asm/arch/sys_proto.h>
#include <asm/sizes.h>
// MSTAR start
#include <configs/uboot_board_config.h>
// MSTAR end

DECLARE_GLOBAL_DATA_PTR;

/*
 * Routine: s_init
 * Description: Does early system init of muxing and clocks.
 *              - Called path is with SRAM stack.
 */
void s_init(void)
{
	watchdog_init();
}

/*
 * Routine: wait_for_command_complete
 * Description: Wait for posting to finish on watchdog
 */
void wait_for_command_complete(struct watchdog *wd_base)
{
	int pending = 1;
	do {
		pending = readl(&wd_base->wwps);
	} while (pending);
}

/*
 * Routine: watchdog_init
 * Description: Shut down watch dogs
 */
void watchdog_init(void)
{
#if 0
	struct watchdog *wd2_base = (struct watchdog *)WDT2_BASE;

	writel(WD_UNLOCK1, &wd2_base->wspr);
	//TODO: fix it. temporary off. wait_for_command_complete(wd2_base);
	writel(WD_UNLOCK2, &wd2_base->wspr);
#endif
}


/*
 * This function finds the SDRAM size available in the system
 * based on DMM section configurations
 * This is needed because the size of memory installed may be
 * different on different versions of the board
 */
u32 sdram_size(void)
{
#ifdef CONFIG_DYNAMIC_RELOCATE
    u32 *dram_size = (u32 *)RELOCATION_INFO_ADDRESS;

    *dram_size = *dram_size * 0x100000;
    return *dram_size;
#else
    return CONFIG_DRAM_SIZE_MB_RELOCATE * 0x100000;
#endif
}


/*
 * Routine: dram_init
 * Description: sets uboots idea of sdram size
 */
int dram_init(void)
{

	gd->ram_size = sdram_size();

	return 0;
}

/*
 * Print board information
 */
int checkboard(void)
{
	printf("%s %s\n", sysinfo.board_string, BOARD_NAME);
	return 0;
}

/*
* This function is called by start_armboot. You can reliably use static
* data. Any boot-time function that require static data should be
* called from here
*/
int arch_cpu_init(void)
{
//  set_muxconf_regs();
	return 0;
}
