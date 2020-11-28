/*
 * (C) Copyright 2010
 * Texas Instruments, <www.ti.com>
 *
 * Author :
 *	Aneesh V	<aneesh@ti.com>
 *	Steve Sakoman	<steve@sakoman.com>
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

/*
 *  get_device_type(): tell if GP/HS/EMU/TST
 */
u32 get_device_type(void)
{
	return 0;
}

/*
 * get_board_rev() - get board revision
 */
u32 get_board_rev(void)
{
	return 0x20;
}

/*
 * Print CPU information
 */
int print_cpuinfo(void)
{
#if (ENABLE_AMBER3)
	puts("CPU  : AMBER3\n");
#elif (ENABLE_EAGLE)
	puts("CPU  : Eagle\n");
#elif (ENABLE_AGATE)
	puts("CPU  : Agate\n");
#elif (ENABLE_EINSTEIN)
	puts("CPU  : Einstein\n");
#elif (ENABLE_EINSTEIN3)
	puts("CPU  : Einstein3\n");
#elif (ENABLE_EDISON)
	puts("CPU  : Edison\n");
#elif (ENABLE_EIFFEL)
    puts("CPU  : Eiffel\n");
#elif (ENABLE_NIKE)
    puts("CPU  : Nike\n");
#elif (ENABLE_MADISON)
    puts("CPU  : Madison\n");
#elif (ENABLE_CLIPPERS)
    puts("CPU  : Clippers\n");
#elif (ENABLE_MIAMI)
    puts("CPU  : Miami\n");
#elif (ENABLE_NADAL)
    puts("CPU  : Nadal\n");
#elif (ENABLE_KRONUS)
    puts("CPU  : kronus\n");
#elif (ENABLE_KAISERIN)
    puts("CPU  : kaiserin\n");
#elif (ENABLE_KAISER)
    puts("CPU  : Kaiser\n");
#elif (ENABLE_NAPOLI)
    puts("CPU  : Napoli\n");
#elif (ENABLE_MONACO)
    puts("CPU  : Monaco\n");
#elif (ENABLE_MUJI)
    puts("CPU  : Muji\n");
#elif (ENABLE_CELTICS)
    puts("CPU  : Celtics\n");
#else
	puts("CPU  : Unknown\n");
#endif

	return 0;
}
