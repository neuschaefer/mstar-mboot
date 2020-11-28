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
#include "stdio.h"
#include "datatype.h"
#include "risc32.h"
//#include "mhal_arch.h"

static struct
{
    mhal_isr_t  isr;
    U32         data;
} expt_table[MHAL_EXCEPTION_MAX + 1];


void mhal_exception_attach(MHAL_EXCEPTION_TYPE expt_num, mhal_isr_t isr, U32 data)
{
    int old;
    if ((U32)expt_num <= MHAL_EXCEPTION_MAX)
    {
        __mhal_interrupt_disable(old);
        expt_table[expt_num].isr = isr;
        expt_table[expt_num].data = data;
        __mhal_interrupt_restore(old);
    }
}

void mhal_exception_detach(MHAL_EXCEPTION_TYPE expt_num)
{
    if ((U32)expt_num <= MHAL_EXCEPTION_MAX)
    {
        expt_table[expt_num].isr = 0;
    }
}

void mhal_exception_handler(MHAL_SavedRegisters *regs, int vector)
{
    mhal_isr_t isr = 0;

    if ((U32)vector <= MHAL_EXCEPTION_MAX)
    {
        isr = expt_table[vector].isr;
        if (isr)
        {
            isr(regs, expt_table[vector].data);
        }
    }

    if (!isr)
    {
        printf("Exception: %d\n", vector);

        printf("r0 : %08lX  r1 : %08lX  r2 : %08lX  r3 : %08lX\n", regs->r[0],  regs->r[1],  regs->r[2],  regs->r[3]);
        printf("r4 : %08lX  r5 : %08lX  r6 : %08lX  r7 : %08lX\n", regs->r[4],  regs->r[5],  regs->r[6],  regs->r[7]);
        printf("r8 : %08lX  r9 : %08lX  r10: %08lX  r11: %08lX\n", regs->r[8],  regs->r[9],  regs->r[10], regs->r[11]);
        printf("r12: %08lX  r13: %08lX  r14: %08lX  r15: %08lX\n", regs->r[12], regs->r[13], regs->r[14], regs->r[15]);
        printf("r16: %08lX  r17: %08lX  r18: %08lX  r19: %08lX\n", regs->r[16], regs->r[17], regs->r[18], regs->r[19]);
        printf("r20: %08lX  r21: %08lX  r22: %08lX  r23: %08lX\n", regs->r[20], regs->r[21], regs->r[22], regs->r[23]);
        printf("r24: %08lX  r25: %08lX  r26: %08lX  r27: %08lX\n", regs->r[24], regs->r[25], regs->r[26], regs->r[27]);
        printf("r28: %08lX  r29: %08lX  r30: %08lX  r31: %08lX\n", regs->r[28], regs->r[29], regs->r[30], regs->r[31]);

        printf("sr : %08X  pc : %08lX  eear: %08lX\n", regs->sr, regs->pc, regs->eear);

        dump_backtrace();
        while (1);
    }
}
