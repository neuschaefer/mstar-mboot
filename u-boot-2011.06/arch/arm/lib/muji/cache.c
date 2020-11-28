/*
 * (C) Copyright 2002
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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

/* for now: just dummy functions to satisfy the linker */

#include <common.h>
#include "cache-l2x0.h"

#define BIT0        0x0001
#define BIT1        0x0002
#define BIT2        0x0004
#define BIT3        0x0008
#define BIT4        0x0010
#define BIT5        0x0020
#define BIT6        0x0040
#define BIT7        0x0080
#define BIT8        0x0100
#define BIT9        0x0200
#define BIT10       0x0400
#define BIT11       0x0800
#define BIT12       0x1000
#define BIT13       0x2000
#define BIT14       0x4000
#define BIT15       0x8000

struct outer_cache_fns outer_cache;

void _chip_flush_miu_pipe(void)
{
    unsigned short  dwReadData = 0;

    //toggle the flush miu pipe fire bit 
    *(volatile unsigned short *)(0x1f203114) &= ~(0x0001);
    *(volatile unsigned short *)(0x1f203114) |= 0x0001;

    do
    {
        dwReadData = *(volatile unsigned short *)(0x1f203140);
        dwReadData &= BIT12;  //Check Status of Flush Pipe Finish

    } while(dwReadData != BIT12  );
    
    //reset fire operation
    *(volatile unsigned short *)(0x1f203114) &= ~(0x0001);
}

void  flush_cache (unsigned long addr, unsigned long len)
{
    // NOTE: use flush range instead of flush all (From Namo's comment)
    extern void v7_dma_flush_range(const void *, const void *);
    v7_dma_flush_range((const void *)addr, (const void *)(addr + len));

#ifndef CONFIG_L2_OFF
    if (outer_cache.is_enable()) //check if L2 is enabled
    {
        //Clean&Inv L2 by range 
        outer_cache.flush_range(addr,addr + len);
    }
#endif
   
    _chip_flush_miu_pipe();

	return;
}

void flush_cache_all(void)
{
    extern void v7_flush_cache_all(void);
	
    v7_flush_cache_all();
	
#ifndef CONFIG_L2_OFF
	if (outer_cache.is_enable()) //check if L2 is enabled
    {
         //Clean&Inv L2 by Way
         outer_cache.flush_all();
    }
#endif

    _chip_flush_miu_pipe();
}

void  invalidate_dcache_range (unsigned long addr, unsigned long len)
{
    extern void v7_dma_inv_range(const void *, const void *);
	
#ifndef CONFIG_L2_OFF	
    if (outer_cache.is_enable()) //check if L2 is enabled
    {
           //Inv L2 by range 
           outer_cache.inv_range(addr ,addr + len);
    }
#endif

#ifdef CONFIG_SYS_DCACHE
    v7_dma_inv_range((const void *)addr, (const void *)(addr + len));
#endif
	
	return;
}

void Chip_Flush_Memory(void)
{
    _chip_flush_miu_pipe();
}

void Chip_Read_Memory(void)
{
    _chip_flush_miu_pipe();
}

