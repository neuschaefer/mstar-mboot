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
#ifndef __RISC32_UTIL_H__
#define __RISC32_UTIL_H__

#include "datatype.h"
#include "risc32_spr.h"

#if defined (__mips__)

extern U32 hal_lsbit_index(U32 mask);
extern U32 hal_msbit_index(U32 mask);

#define __mhal_lsbit_index(_value_) hal_lsbit_index(_value_)
#define __mhal_msbit_index(_value_) hal_msbit_index(_value_)

extern U32 hal_disable_interrupts(void);
#define __mhal_interrupt_disable(_old_) { (_old_) = hal_disable_interrupts(); }

extern void hal_enable_interrupts(void);
#define __mhal_interrupt_enable() hal_enable_interrupts()

extern void hal_restore_interrupts( U32 old );
#define __mhal_interrupt_restore(_old_) hal_restore_interrupts( _old_ )

#define ASM_CLEAR_EHB   "nop;nop;nop;\n"

#define __mhal_interrupt_mask( _vector_ )       \
MST_MACRO_START                                 \
    asm volatile (                              \
        "mfc0   $3,$12\n"                       \
        "la     $2,0x00000400\n"                \
        "sllv   $2,$2,%0\n"                     \
        "nor    $2,$2,$0\n"                     \
        "and    $3,$3,$2\n"                     \
        "mtc0   $3,$12\n"                       \
        ASM_CLEAR_EHB                           \
        :                                       \
        : "r"(_vector_)                         \
        : "$2", "$3"                            \
        );                                      \
MST_MACRO_END

#define __mhal_interrupt_unmask( _vector_ )     \
MST_MACRO_START                                 \
    asm volatile (                              \
        "mfc0   $3,$12\n"                       \
        "la     $2,0x00000400\n"                \
        "sllv   $2,$2,%0\n"                     \
        "or     $3,$3,$2\n"                     \
        "mtc0   $3,$12\n"                       \
        ASM_CLEAR_EHB                           \
        :                                       \
        : "r"(_vector_)                         \
        : "$2", "$3"                            \
        );                                      \
MST_MACRO_END


#else


#define __mhal_lsbit_index(_value_)                                         \
    ({                                                                      \
    unsigned long _index_;                                                  \
    __asm__ __volatile__ ("l.ff1\t\t%0,%1" : "=r" (_index_) : "r" (_value_));\
    _index_;                                                                \
    })

#define __mhal_msbit_index(_value_)                                         \
    ({                                                                      \
    unsigned long _index_;                                                  \
    __asm__ __volatile__ ("l.fl1\t\t%0,%1" : "=r" (_index_) : "r" (_value_));\
    _index_;                                                                \
    })

#define __mhal_interrupt_disable(_old_)                                     \
    MST_MACRO_START                                                         \
    _old_ = mfspr(SPR_SR);                                                  \
    mtspr(SPR_SR, (_old_) & ~(SPR_SR_IEE | SPR_SR_TEE));                    \
    MST_MACRO_END

#define __mhal_interrupt_enable()                                           \
    mtspr(SPR_SR, (SPR_SR_IEE|SPR_SR_TEE) | mfspr(SPR_SR))

#define __mhal_interrupt_restore(_old_)                                     \
    mtspr(SPR_SR, (~(SPR_SR_IEE|SPR_SR_TEE) & mfspr(SPR_SR) ) |             \
                  ( (SPR_SR_IEE|SPR_SR_TEE) & (_old_) ))

#define __mhal_interrupt_mask(_intr_)                                       \
    MST_MACRO_START                                                         \
    if (_intr_ != MHAL_INTERRUPT_TICK_TIMER)                                \
    {                                                                       \
        mtspr(SPR_PICMR, mfspr(SPR_PICMR) & ~(1 << (_intr_ - 1)));          \
    }                                                                       \
    MST_MACRO_END

#define __mhal_interrupt_unmask(_intr_)                                     \
    MST_MACRO_START                                                         \
    if (_intr_ != MHAL_INTERRUPT_TICK_TIMER)                                \
    {                                                                       \
        mtspr(SPR_PICMR, mfspr(SPR_PICMR) | (1 << (_intr_ - 1)));           \
    }                                                                       \
    MST_MACRO_END

#define __mhal_mmu_disable(_old_)                                     \
        MST_MACRO_START                                                         \
        _old_ = mfspr(SPR_SR);                                      \
        mtspr(SPR_SR, (_old_) & ~(SPR_SR_IME | SPR_SR_DME));                    \
        MST_MACRO_END

#endif

#endif /* __RISC32_UTIL_H__ */
