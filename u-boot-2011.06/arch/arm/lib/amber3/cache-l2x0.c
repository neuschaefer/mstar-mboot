/*
 * arch/arm/mm/cache-l2x0.c - L210/L220 cache controller support
 *
 * Copyright (C) 2007 ARM Limited
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
#include <stdlib.h>
#include <stdio.h>

#include "common.h"
#include "cache-l2x0.h"

#define CACHE_LINE_SIZE		32

static void  *l2x0_base;
static unsigned long l2x0_way_mask;	/* Bitmask of active ways */
extern struct outer_cache_fns outer_cache;

static inline void cache_wait_way(void *reg, unsigned long mask)
{
	/* wait for cache operation by line or way to complete */
	while (readl_relaxed(reg) & mask)
		;
}

static inline void cache_wait(void *reg, unsigned long mask)
{
	/* cache operations by line are atomic on PL310 */
}

static inline void cache_sync(void)
{
	void *base = l2x0_base;
	writel_relaxed(0, (unsigned long)base + L2X0_CACHE_SYNC);
	cache_wait((void *)((unsigned long)base + L2X0_CACHE_SYNC), 1);
}

static inline void l2x0_clean_line(unsigned long addr)
{
	void  *base = l2x0_base;
	cache_wait((void *)((unsigned long)base + L2X0_CLEAN_LINE_PA), 1);
	writel_relaxed(addr, (unsigned long)base + L2X0_CLEAN_LINE_PA);
}

static inline void l2x0_inv_line(unsigned long addr)
{
	void *base = l2x0_base;
	cache_wait((void *)((unsigned long)base + L2X0_INV_LINE_PA), 1);
	writel_relaxed(addr, (unsigned long)base + L2X0_INV_LINE_PA);
}


/* Optimised out for non-errata case */
static inline void debug_writel(unsigned long val)
{
}

static inline void l2x0_flush_line(unsigned long addr)
{
	void  *base = l2x0_base;
	cache_wait((void *)((unsigned long)base + L2X0_CLEAN_INV_LINE_PA), 1);
	writel_relaxed(addr, (unsigned long)base + L2X0_CLEAN_INV_LINE_PA);
}

static void l2x0_cache_sync(void)
{
	cache_sync();
}

static inline void l2x0_inv_all(void)
{
	/* invalidate all ways */
	writel_relaxed(l2x0_way_mask, (unsigned long)l2x0_base + L2X0_INV_WAY);
	cache_wait_way((void *)((unsigned long)l2x0_base + L2X0_INV_WAY), l2x0_way_mask);
	cache_sync();
}

static void l2x0_inv_range(unsigned long start, unsigned long end)
{
	void  *base = l2x0_base;
	
	if (start & (CACHE_LINE_SIZE - 1)) {
		start &= ~(CACHE_LINE_SIZE - 1);
		debug_writel(0x03);
		l2x0_flush_line(start);
		debug_writel(0x00);
		start += CACHE_LINE_SIZE;
	}

	if (end & (CACHE_LINE_SIZE - 1)) {
		end &= ~(CACHE_LINE_SIZE - 1);
		debug_writel(0x03);
		l2x0_flush_line(end);
		debug_writel(0x00);
	}

	while (start < end) {
		unsigned long blk_end = start + min(end - start, 4096UL);

		while (start < blk_end) {
			l2x0_inv_line(start);
			start += CACHE_LINE_SIZE;
		}

		if (blk_end < end) {
		}
	}
	cache_wait((void*)((unsigned long)base + L2X0_INV_LINE_PA), 1);
	cache_sync();
}

static inline void l2x0_clean_all(void)
{
	/* invalidate all ways */
	writel_relaxed(l2x0_way_mask, (unsigned long)l2x0_base + L2X0_CLEAN_WAY);
	cache_wait_way((void*)((unsigned long)l2x0_base + L2X0_CLEAN_WAY) , l2x0_way_mask);
	cache_sync();
}

static void l2x0_clean_range(unsigned long start, unsigned long end)
{
	void *base = l2x0_base;

	start &= ~(CACHE_LINE_SIZE - 1);
	while (start < end) {
		unsigned long blk_end = start + min(end - start, 4096UL);

		while (start < blk_end) {
			l2x0_clean_line(start);
			start += CACHE_LINE_SIZE;
		}

		if (blk_end < end) {
		}
	}
	cache_wait((void*)((unsigned long)base + L2X0_CLEAN_LINE_PA), 1);
	cache_sync(); 

}

void l2x0_flush_all(void)
{
	/* invalidate all ways */
	writel_relaxed(l2x0_way_mask, (unsigned long)l2x0_base + L2X0_CLEAN_INV_WAY);
	cache_wait_way((void*)((unsigned long)l2x0_base + L2X0_CLEAN_INV_WAY), l2x0_way_mask);
	cache_sync();
}

static void l2x0_flush_range(unsigned long start, unsigned long end)
{
	void  *base = l2x0_base;

	start &= ~(CACHE_LINE_SIZE - 1);
	while (start < end) {
		unsigned long blk_end = start + min(end - start, 4096UL);
		debug_writel(0x03);
		while (start < blk_end) {
			l2x0_flush_line(start);
			start += CACHE_LINE_SIZE;
		}
		debug_writel(0x00);

		if (blk_end < end) {
		}
	}
	cache_wait((void*)((unsigned long)base + L2X0_CLEAN_INV_LINE_PA), 1);
	cache_sync();
}

static inline int l2x0_is_enable(void)
{
              
    return (readl_relaxed((unsigned long)l2x0_base + L2X0_CTRL) & 1);
}

void l2x0_init(void  *base, unsigned long aux_val, unsigned long aux_mask)
{
	unsigned long aux;
    unsigned long cache_id;
	int ways;
	const char *type;

	l2x0_base = base;

	printf("base = %lx, aux_val = %lx, aux_mask = %lx\n", (long unsigned)base, (unsigned long)aux_val, (unsigned long)aux_mask);
	
	cache_id = readl_relaxed((unsigned long)l2x0_base + L2X0_CACHE_ID);
	aux = readl_relaxed((unsigned long)l2x0_base + L2X0_AUX_CTRL);

	aux &= aux_mask;
	aux |= aux_val;

	/* Determine the number of ways */
	switch (cache_id & L2X0_CACHE_ID_PART_MASK) {
	case L2X0_CACHE_ID_PART_L310:
		if (aux & (1 << 16))
			ways = 16;
		else
			ways = 8;
		type = "L310";
		break;
	case L2X0_CACHE_ID_PART_L210:
		ways = (aux >> 13) & 0xf;
		type = "L210";
		break;
	default:
		/* Assume unknown chips have 8 ways */
		ways = 8;
		type = "L2x0 series";
		break;
	}

	l2x0_way_mask = (1 << ways) - 1;

	/*
	 * Check if l2x0 controller is already enabled.
	 * If you are booting from non-secure mode
	 * accessing the below registers will fault.
	 */
	if (!(readl_relaxed((unsigned long)l2x0_base + L2X0_CTRL) & 1)) {

		/* l2x0 controller is disabled */
		writel_relaxed(aux, (unsigned long)l2x0_base + L2X0_AUX_CTRL);

		l2x0_inv_all();

		/* enable L2X0 */
		writel_relaxed(1, (unsigned long)l2x0_base + L2X0_CTRL);
	}

	outer_cache.is_enable = l2x0_is_enable;
	outer_cache.inv_range = l2x0_inv_range;
	outer_cache.inv_all= l2x0_inv_all;
	outer_cache.clean_range = l2x0_clean_range;
	outer_cache.clean_all= l2x0_clean_all;
	outer_cache.flush_range = l2x0_flush_range;
	outer_cache.flush_all= l2x0_flush_all;
	outer_cache.sync = l2x0_cache_sync;

	printf("%s cache controller enabled\n", type);
	printf("l2x0: %d ways, CACHE_ID 0x%08lx, AUX_CTRL 0x%08lx\n",
			 ways, (unsigned long)cache_id, (unsigned long)aux);
}

void l2_cache_init(void)
{
    unsigned int val = 0;
    void * l2x0_base = (void *)(L2_CACHE_ADDRESS(L2_CACHE_PHYS));

    /*L2_LINEFILL*/
    val = L2_CACHE_read( L2_CACHE_PHYS + PREFETCH_CTL_REG );
     
    L2_CACHE_write(( val | DOUBLE_LINEFILL_ENABLE | LINEFILL_WRAP_DISABLE ), L2_CACHE_PHYS + PREFETCH_CTL_REG);
     
    /*L2_PREFETCH*/
    val = L2_CACHE_read( L2_CACHE_PHYS + PREFETCH_CTL_REG );
    L2_CACHE_write(( val | I_PREFETCH_ENABLE | D_PREFETCH_ENABLE | PREFETCH_OFFSET ), L2_CACHE_PHYS + PREFETCH_CTL_REG );
     
    /* set RAM latencies to 2 cycle for this core tile. */
    writel_relaxed(0x111, (unsigned long)l2x0_base + L2X0_TAG_LATENCY_CTRL);
    writel_relaxed(0x111, (unsigned long)l2x0_base + L2X0_DATA_LATENCY_CTRL);

   	l2x0_init(l2x0_base, 0x00400000, 0xfe0fffff);
}

void l2_cache_disable(void)
{
    /* disable L2X0 */
    writel_relaxed(0, (unsigned long)l2x0_base + L2X0_CTRL);
}
