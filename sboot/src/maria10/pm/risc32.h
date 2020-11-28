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
#ifndef __RISC32_H__
#define __RISC32_H__

//#ifdef LIBPRANA
#include "risc32_util.h"
//#endif

#include "datatype.h"

typedef enum {
    MHAL_EXCEPTION_BUS_ERROR = 2,
    MHAL_EXCEPTION_DATA_PAGE_FAULT,
    MHAL_EXCEPTION_INSTRUCTION_PAGE_FAULT,
    MHAL_EXCEPTION_TICK_TIMER,
    MHAL_EXCEPTION_UNALIGNED_ACCESS,
    MHAL_EXCEPTION_ILLEGAL_INSTRUCTION,
    MHAL_EXCEPTION_EXTERNAL_INTERRUPT,
    MHAL_EXCEPTION_DTLB_MISS,
    MHAL_EXCEPTION_ITLB_MISS,
    MHAL_EXCEPTION_RANGE,
    MHAL_EXCEPTION_SYSCALL,
    MHAL_EXCEPTION_RESERVED,
    MHAL_EXCEPTION_TRAP,
    MHAL_EXCEPTION_MAX = MHAL_EXCEPTION_TRAP,
} MHAL_EXCEPTION_TYPE;

typedef enum {
    MHAL_INTERRUPT_TICK_TIMER,
    MHAL_INTERRUPT_00 = 1,  // NOTE, PIC interrupt from 1 for handler performance
    MHAL_INTERRUPT_01,
    MHAL_INTERRUPT_02,
    MHAL_INTERRUPT_03,
    MHAL_INTERRUPT_04,
    MHAL_INTERRUPT_05,
    MHAL_INTERRUPT_06,
    MHAL_INTERRUPT_07,
    MHAL_INTERRUPT_08,
    MHAL_INTERRUPT_09,
    MHAL_INTERRUPT_10,
    MHAL_INTERRUPT_11,
    MHAL_INTERRUPT_12,
    MHAL_INTERRUPT_13,
    MHAL_INTERRUPT_14,
    MHAL_INTERRUPT_15,
    MHAL_INTERRUPT_16,
    MHAL_INTERRUPT_17,
    MHAL_INTERRUPT_18,
    MHAL_INTERRUPT_19,
    MHAL_INTERRUPT_20,
    MHAL_INTERRUPT_21,
    MHAL_INTERRUPT_22,
    MHAL_INTERRUPT_23,
    MHAL_INTERRUPT_24,
    MHAL_INTERRUPT_25,
    MHAL_INTERRUPT_26,
    MHAL_INTERRUPT_27,
    MHAL_INTERRUPT_28,
    MHAL_INTERRUPT_29,
    MHAL_INTERRUPT_30,
    MHAL_INTERRUPT_31,
} MHAL_INTERRUPT_TYPE;

// Aliases for interrupt number
#define MHAL_INTERRUPT_FIQ          MHAL_INTERRUPT_02
#define MHAL_INTERRUPT_IRQ          MHAL_INTERRUPT_03
#define MHAL_INTERRUPT_UART         MHAL_INTERRUPT_19
#define MHAL_INTERRUPT_MAX          MHAL_INTERRUPT_31

typedef struct
{
    unsigned long   r1;
    unsigned long   r2;
    unsigned long   r9;
    unsigned long   r10;
    unsigned long   r12;
    unsigned long   r14;
    unsigned long   r16;
    unsigned long   r18;
    unsigned long   r20;
    unsigned long   r22;
    unsigned long   r24;
    unsigned long   r26;
    unsigned long   r28;
    unsigned long   r30;
    unsigned long   sr;
} MHAL_Context;

typedef struct
{
    unsigned long   r[32];          // GPR regs
    unsigned long   machi2;         // AMAC extension
    unsigned long   machi;          // High and low words of
    unsigned long   maclo;          //   multiply/accumulate reg

    // These are only saved for exceptions and interrupts
    int             vector;         // Vector number
    int             sr;             // Status Reg
    unsigned long   pc;             // Program Counter

    // Saved only for exceptions, and not restored when continued:
    // Effective address of instruction/data access that caused exception
    unsigned long   eear;           // Exception effective address reg
} MHAL_SavedRegisters;

typedef void (*mhal_isr_t)(MHAL_SavedRegisters *regs, U32 vector);

MST_BEGIN_DECL

void mhal_exception_attach(MHAL_EXCEPTION_TYPE expt_num, mhal_isr_t isr, U32 dat);
void mhal_exception_detach(MHAL_EXCEPTION_TYPE expt_num);
void mhal_exception_handler(MHAL_SavedRegisters *regs, int vector);

int  mhal_interrupt_disable(void);
void mhal_interrupt_enable(void);
void mhal_interrupt_resotre(int old);

void mhal_interrupt_mask(MHAL_INTERRUPT_TYPE intr_num);
void mhal_interrupt_unmask(MHAL_INTERRUPT_TYPE intr_num);
void mhal_interrupt_mask_all(void);

void mhal_interrupt_lock(void);
void mhal_interrupt_unlock(void);

void mhal_interrupt_attach(MHAL_INTERRUPT_TYPE intr_num, mhal_isr_t isr, U32 dat);
void mhal_interrupt_detach(MHAL_INTERRUPT_TYPE intr_num);

void mhal_stack_init(void *stack);

void mhal_dcache_flush(U32 u32Base, U32 u32Size);

void mhal_switch_context(MHAL_Context *pNextCtx, MHAL_Context **pSaveCtxPtr);
void mhal_load_context(MHAL_Context *pNextCtx);

MST_END_DECL

#endif /* __RISC32_H__ */
