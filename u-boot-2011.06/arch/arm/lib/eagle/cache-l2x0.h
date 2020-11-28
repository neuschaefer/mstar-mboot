/*
 * arch/arm/include/asm/hardware/cache-l2x0.h
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

#include "common.h"

#ifndef __ASM_ARM_HARDWARE_L2X0_H
#define __ASM_ARM_HARDWARE_L2X0_H

#define L2X0_CACHE_ID			0x000
#define   L2X0_CACHE_ID_PART_MASK	(0xf << 6)
#define   L2X0_CACHE_ID_PART_L210	(1 << 6)
#define   L2X0_CACHE_ID_PART_L310	(3 << 6)
#define L2X0_CACHE_TYPE			0x004
#define L2X0_CTRL			0x100
#define L2X0_AUX_CTRL			0x104
#define L2X0_TAG_LATENCY_CTRL		0x108
#define L2X0_DATA_LATENCY_CTRL		0x10C
#define L2X0_EVENT_CNT_CTRL		0x200
#define L2X0_EVENT_CNT1_CFG		0x204
#define L2X0_EVENT_CNT0_CFG		0x208
#define L2X0_EVENT_CNT1_VAL		0x20C
#define L2X0_EVENT_CNT0_VAL		0x210
#define L2X0_INTR_MASK			0x214
#define L2X0_MASKED_INTR_STAT		0x218
#define L2X0_RAW_INTR_STAT		0x21C
#define L2X0_INTR_CLEAR			0x220
#define L2X0_CACHE_SYNC			0x730
#define L2X0_INV_LINE_PA		0x770
#define L2X0_INV_WAY			0x77C
#define L2X0_CLEAN_LINE_PA		0x7B0
#define L2X0_CLEAN_LINE_IDX		0x7B8
#define L2X0_CLEAN_WAY			0x7BC
#define L2X0_CLEAN_INV_LINE_PA		0x7F0
#define L2X0_CLEAN_INV_LINE_IDX		0x7F8
#define L2X0_CLEAN_INV_WAY		0x7FC
#define L2X0_LOCKDOWN_WAY_D		0x900
#define L2X0_LOCKDOWN_WAY_I		0x904
#define L2X0_TEST_OPERATION		0xF00
#define L2X0_LINE_DATA			0xF10
#define L2X0_LINE_TAG			0xF30
#define L2X0_DEBUG_CTRL			0xF40

#define readl_relaxed(addr) *(volatile unsigned long*)(addr)
#define writel_relaxed(value,addr) *(volatile unsigned long*)(addr) = value

/* Constants of L2_CACHE  */
#define L2_CACHE_PHYS         0x15000000
#define L2_CACHE_OFFSET       0x00000000
#define L2_CACHE_SIZE         0x1000
#define L2_CACHE_VIRT         (L2_CACHE_PHYS + L2_CACHE_OFFSET)
#define L2_CACHE_p2v(pa)      ((pa) + L2_CACHE_OFFSET)
#define L2_CACHE_v2p(va)      ((va) - L2_CACHE_OFFSET)
#define L2_CACHE_ADDRESS(x)   L2_CACHE_p2v(x)


/* Constants of AMBER3 L2 Linefill & Prefetch */
#define L2_LINEFILL             1
#define L2_PREFETCH             1
#define PREFETCH_CTL_REG        0xF60

#define DOUBLE_LINEFILL_ENABLE  0x40000000  //[30]
#define I_PREFETCH_ENABLE       0x20000000  //[29]     
#define D_PREFETCH_ENABLE       0x10000000  //[28]
#define LINEFILL_WRAP_DISABLE   0x08000000  //[27]
#define PREFETCH_OFFSET         0x00000000  //[4:0] ,only support 0-7,15,23,31 

#define L2_CACHE_write(v,a)         (*(volatile unsigned int *)L2_CACHE_ADDRESS(a) = (v))
#define L2_CACHE_read(a)            (*(volatile unsigned int *)L2_CACHE_ADDRESS(a))

struct outer_cache_fns {
    void (*inv_range)(unsigned long, unsigned long);
    void (*inv_all)(void);
    void (*clean_range)(unsigned long, unsigned long);
    void (*clean_all)(void);
    void (*flush_range)(unsigned long, unsigned long);
    void (*flush_all)(void);
    int (*is_enable)(void); 
    void (*sync)(void);
};

void l2x0_init(void  *base, unsigned long aux_val, unsigned long aux_mask);
void l2_cache_init(void);

#endif
