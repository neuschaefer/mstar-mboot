//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all 
// or part of MStar Software is expressly prohibited, unless prior written 
// permission has been granted by MStar. 
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.  
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software. 
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s 
//    confidential information in strictest confidence and not disclose to any
//    third party.  
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.  
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or 
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.  
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
#include <stdio.h>
#include <assert.h>
#include "datatype.h"
#include "risc32.h"
//#include "mhal_arch.h"
#include "risc32_spr.h"
#include "risc32_util.h"

#ifndef ASSERT
#define ASSERT(expr)    ((expr) ? (void)0 : __assert(__FILE__, __LINE__, ""))
#endif

#ifdef __AEONR2__
#define AEON_CLOCK_FREQ 12000000
#else
#define AEON_CLOCK_FREQ 12000000
#endif

#if 1   // To fix compile warning and need to check after, 2009/11/23
int mhal_mmu_disable(void);
void mhal_interrupt_restore(int old);
void mhal_interrupt_handler(MHAL_SavedRegisters *regs, int vector);
void mhal_interrupt_dumpvector(void);
extern void dump_backtrace(void);
#endif

struct interrupt
{
    mhal_isr_t  isr;
    U32         data;
};

static void __mhal_default_isr(MHAL_SavedRegisters *regs, U32 vector)
{
    printf("\nmhal_default_isr vector: %ld regs: %p\n", vector, regs);
    dump_backtrace();
    while(1);
}

void mhal_default_isr(MHAL_SavedRegisters *regs, U32 vector) __attribute__ ((weak, alias("__mhal_default_isr")));

static struct interrupt intr_table[MHAL_INTERRUPT_MAX + 1];

static volatile int nr_intr_locks;
static volatile int saved_intr_state;

int  mhal_interrupt_disable(void)
{
    int spr_sr;
    __mhal_interrupt_disable(spr_sr);
    return spr_sr;
}

void mhal_interrupt_enable(void)
{
    __mhal_interrupt_enable();
}

void mhal_interrupt_restore(int old)
{
    __mhal_interrupt_restore(old);
}

void mhal_interrupt_mask_all(void)
{
    mtspr(SPR_PICMR, 0x00000000);
}

void mhal_interrupt_mask(MHAL_INTERRUPT_TYPE intr_num)
{
    __mhal_interrupt_mask(intr_num);
}

void mhal_interrupt_unmask(MHAL_INTERRUPT_TYPE intr_num)
{
    __mhal_interrupt_unmask(intr_num);
}

void mhal_interrupt_lock(void)
{
    int spr_sr;

    __mhal_interrupt_disable(spr_sr);
    if (++nr_intr_locks == 1)
    {
        saved_intr_state = spr_sr;
    }

    ASSERT(nr_intr_locks > 0);
}

void mhal_interrupt_unlock(void)
{
    ASSERT(nr_intr_locks > 0);

    if (--nr_intr_locks == 0)
    {
        __mhal_interrupt_restore(saved_intr_state);
    }
}

void mhal_interrupt_attach(MHAL_INTERRUPT_TYPE intr_num, mhal_isr_t isr, U32 dat)
{
    if (intr_num <= MHAL_INTERRUPT_MAX)
    {
        intr_table[intr_num].isr = isr;
        intr_table[intr_num].data = dat;
    }
}

void mhal_interrupt_detach(MHAL_INTERRUPT_TYPE intr_num)
{
    if (intr_num <= MHAL_INTERRUPT_MAX)
    {
        intr_table[intr_num].isr = 0;
    }
}

#define ISR_TIMER0_PERIOD_US        1000UL  // : 1000us, unit:us, Timer 0 Interrupt period

void mhal_interrupt_handler(MHAL_SavedRegisters *regs, int vector)
{
    unsigned long spr;
    unsigned long picvec;
    mhal_isr_t    isr;

    UNUSED(vector);

    spr = mfspr(SPR_PICSR);
    picvec = __mhal_lsbit_index(spr);
    isr = intr_table[picvec].isr;
    if (isr)
    {
       isr(regs, intr_table[picvec].data);   //call isr here
    }
    else
    {
       mhal_default_isr(regs, picvec);
    }
    if (picvec)
    {
        picvec--;
        spr = mfspr(SPR_PICMR);
        mtspr(SPR_PICMR, spr & ~(1 << picvec));
        mtspr(SPR_PICSR, mfspr(SPR_PICSR) & ~(1 << picvec));
        mtspr(SPR_PICMR, spr);
    }

    if(picvec==0)
    {
        mtspr(SPR_TTMR, 0x60000000 | (AEON_CLOCK_FREQ / ISR_TIMER0_PERIOD_US));
    }
}

void mhal_interrupt_dumpvector(void)
{
    unsigned int i;
    for(i=0;i< MHAL_INTERRUPT_MAX;i++)
    {
        printf("vector %d addr:%lX data:%lX\n",i,(U32)intr_table[i].isr,(U32)intr_table[i].data);
    }
}

