/*
 * (C) Copyright 2008
 * Texas Instruments
 *
 * Richard Woodruff <r-woodruff2@ti.com>
 * Syed Moahmmed Khasim <khasim@ti.com>
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 * Alex Zuepke <azu@sysgo.de>
 *
 * (C) Copyright 2002
 * Gary Jennejohn, DENX Software Engineering, <garyj@denx.de>
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
#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;

/**************************
*    Mstar board timer patch
**************************/
#define MSTAR_TIMER 	1
#define M_TIMER_CLOCK 	12000000   //12Mhz
#define TIMER0_BASE 	0xBF006040
#define TIMER0_MAX_L 	0xBF006048
#define TIMER0_MAX_H 	0xBF00604C
#define ADR_CNT_LO  		(0x4<<2)
#define ADR_CNT_HI  		(0x5<<2)
#define GET_CNT			(readw(TIMER0_BASE+ADR_CNT_LO)+(readw(TIMER0_BASE+ADR_CNT_HI)<<16))
static ulong cnt=0;

#if (MSTAR_TIMER!=1)
static struct gptimer *timer_base = (struct gptimer *)CONFIG_SYS_TIMERBASE;
#endif

/*
 * Nothing really to do with interrupts, just starts up a counter.
 */

#define TIMER_CLOCK	(V_SCLK / (2 << CONFIG_SYS_PTV))
#define TIMER_LOAD_VAL	0xffffffff
#define TIMER_LOAD_MAX	0xffff
#if 1
int timer_init(void)
{
#if MSTAR_TIMER
	//enable timer0
	writew(0x1,TIMER0_BASE);
    writel(TIMER_LOAD_MAX, TIMER0_MAX_L);
    writel(TIMER_LOAD_MAX, TIMER0_MAX_H);
#else
	/* start the counter ticking up, reload value on overflow */
	writel(TIMER_LOAD_VAL, &timer_base->tldr);
	/* enable timer */
	writel((CONFIG_SYS_PTV << 2) | TCLR_PRE | TCLR_AR | TCLR_ST,
		&timer_base->tclr);
	reset_timer_masked();	/* init the timestamp and lastinc value */

#endif
	return 0;
}
#else
static inline void mips_compare_set(u32 v)
{
	asm volatile ("mtc0 %0, $11" : : "r" (v));
}

static inline void mips_count_set(u32 v)
{
	asm volatile ("mtc0 %0, $9" : : "r" (v));
}


static inline u32 mips_count_get(void)
{
	u32 count;

	asm volatile ("mfc0 %0, $9" : "=r" (count) :);
	return count;
}

/*
 * timer without interrupts
 */

int timer_init(void)
{
	mips_compare_set(0);
	mips_count_set(0);

	return 0;
}
#endif

/*
 * timer without interrupts
 */
void reset_timer(void)
{
#if MSTAR_TIMER

#else
	reset_timer_masked();
#endif
}

ulong get_timer(ulong base)
{
#if MSTAR_TIMER
	cnt=GET_CNT;
	return cnt;
#else
	return get_timer_masked() - base;
#endif
}

void set_timer(ulong t)
{
#if MSTAR_TIMER

#else
	gd->tbl = t;
#endif
}

/* delay x useconds */
void __udelay(unsigned long usec)
{
#if MSTAR_TIMER
	long tmo = usec * (M_TIMER_CLOCK / 1000) / 1000;
	unsigned long now, last = GET_CNT;

	while (tmo > 0) {
		now = GET_CNT;
		if (last > now) /* count up timer overflow */
			tmo -= TIMER_LOAD_VAL - last + now;
		else
			tmo -= now - last;
		last = now;
	}
#else
	long tmo = usec * (TIMER_CLOCK / 1000) / 1000;
	unsigned long now, last = readl(&timer_base->tcrr);

	while (tmo > 0) {
		now = readl(&timer_base->tcrr);
		if (last > now) /* count up timer overflow */
			tmo -= TIMER_LOAD_VAL - last + now;
		else
			tmo -= now - last;
		last = now;
	}
#endif
}

void reset_timer_masked(void)
{
#if MSTAR_TIMER

#else
	/* reset time, capture current incrementer value time */
	gd->lastinc = readl(&timer_base->tcrr) / (TIMER_CLOCK / CONFIG_SYS_HZ);
	gd->tbl = 0;		/* start "advancing" time stamp from 0 */
#endif
}

ulong get_timer_masked(void)
{
#if MSTAR_TIMER
    return 0;
#else
	/* current tick value */
	ulong now = readl(&timer_base->tcrr) / (TIMER_CLOCK / CONFIG_SYS_HZ);

	if (now >= gd->lastinc)	/* normal mode (non roll) */
		/* move stamp fordward with absoulte diff ticks */
		gd->tbl += (now - gd->lastinc);
	else	/* we have rollover of incrementer */
		gd->tbl += ((TIMER_LOAD_VAL / (TIMER_CLOCK / CONFIG_SYS_HZ))
			     - gd->lastinc) + now;
	gd->lastinc = now;
	return gd->tbl;
#endif
}

/*
 * This function is derived from PowerPC code (read timebase as long long).
 * On ARM it just returns the timer value.
 */
unsigned long long get_ticks(void)
{
#if MSTAR_TIMER
    return 0;
#else
	return get_timer(0);
#endif
}

/*
 * This function is derived from PowerPC code (timebase clock frequency).
 * On ARM it returns the number of timer ticks per second.
 */
ulong get_tbclk(void)
{
#if MSTAR_TIMER
    return 0;
#else
	return CONFIG_SYS_HZ;
#endif
}
