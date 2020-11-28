/*
 * (C) Copyright 2010
 * Texas Instruments Incorporated, <www.ti.com>
 * Steve Sakoman  <steve@sakoman.com>
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
#include <asm/arch/sys_proto.h>
#include <asm/arch/mmc_host_def.h>

#include "panda.h"

DECLARE_GLOBAL_DATA_PTR;

const struct omap_sysinfo sysinfo = {
    "Board:"
};

/**
 * @brief board_init
 *
 * @return 0
 */
int board_init(void)
{
    gd->bd->bi_arch_number = MACH_TYPE_OMAP4_PANDA;
    gd->bd->bi_boot_params = (0x20400000 + 0x100); /* boot param addr */

    return 0;
}

int board_eth_init(bd_t *bis)
{
    return 0;
}

/**
 * @brief misc_init_r - Configure Panda board specific configurations
 * such as power configurations, ethernet initialization as phase2 of
 * boot sequence
 *
 * @return 0
 */
int misc_init_r(void)
{
    return 0;
}

void do_set_mux(u32 base, struct pad_conf_entry const *array, int size)
{
    int i;
    struct pad_conf_entry *pad = (struct pad_conf_entry *) array;

    for (i = 0; i < size; i++, pad++)
        writew(pad->val, base + pad->offset);
}

/**
 * @brief set_muxconf_regs Setting up the configuration Mux registers
 * specific to the board.
 */
void set_muxconf_regs(void)
{
}
