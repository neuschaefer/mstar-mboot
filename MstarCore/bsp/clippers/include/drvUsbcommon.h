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
#ifndef __USBCOMMON_H
#define __USBCOMMON_H

#include "asmCPU.h" // ASSERT debug

typedef void* (*mem_Alloc)(int size);
typedef void (*mem_Free)(void* pBuf);
typedef MS_U32 (*mem_VA2PA)(MS_U32 addr);
typedef MS_U32 (*mem_PA2VA)(MS_U32 addr, int bCached);
typedef void* (*mem_Cached2Noncached)(MS_U32 addr);
typedef void* (*mem_NonCached2Cached)(MS_U32 addr);


extern mem_Alloc    pfnAllocCachedMem, pfnAllocNoncachedMem;
extern mem_Free     pfnFreeCachedMem, pfnFreeNoncachedMem;
extern mem_VA2PA    pfnVA2PA;
extern mem_PA2VA    pfnPA2VA;
extern mem_Cached2Noncached     pfnCached2Noncached;
extern mem_NonCached2Cached     pfnNoncached2Cached;

#if 1 // eCos lib
#define Usb_AllocateNonCachedMemory(x)  pfnAllocNoncachedMem(x)
#define Usb_FreeNonCachedMemory(x)      pfnFreeNoncachedMem(x)
#define Usb_AllocateCachedMemory(x)     pfnAllocCachedMem(x)
#define Usb_FreeCachedMemory(x)         pfnFreeCachedMem(x)


//extern void* (*kmalloc)(int size, int flag); 
//extern void  (*kfree)(void* pBuf); 
#define kmalloc(size, flag)             pfnAllocCachedMem(size)
#define kfree(pBuf)                     pfnFreeCachedMem(pBuf)

#define USB_VA2PA(addr)                 pfnVA2PA(addr)
#else
#define Usb_AllocateNonCachedMemory(x)  kmalloc(x, 0)
#define Usb_FreeNonCachedMemory(x)      kfree(x)
#define Usb_AllocateCachedMemory(x)     kmalloc(x, 0)
#define Usb_FreeCachedMemory(x)         kfree(x)
#endif

#if 1 // eCos lib
#define KSEG02KSEG1(addr)       pfnCached2Noncached((MS_U32)addr)  //cached -> unchched, 20111017 for K2
#define KSEG12KSEG0(addr)       pfnNoncached2Cached((MS_U32)addr) //unchched -> cached
#else
#define KSEG02KSEG1(addr)       ((void *)((MS_U32)(addr)|0x20000000))  //cached -> unchched
#define KSEG12KSEG0(addr)       ((void *)((MS_U32)(addr)&~0x20000000)) //unchched -> cached
#endif

#ifndef U32
#define U32 MS_U32
#endif

#ifndef U16
#define U16 MS_U16
#endif

#ifndef U8
#define U8 MS_U8
#endif

#ifndef S32
#define S32 MS_S32
#endif

#ifndef S16
#define S16 MS_S16
#endif

#ifndef S8
#define S8 MS_S8
#endif

#ifndef __u32
#define __u32 MS_U32
#endif

#ifndef __u16
#define __u16 MS_U16
#endif

#ifndef __u8
#define __u8 MS_U8
#endif

#ifndef __s32
#define __s32 MS_S32
#endif

#ifndef __s16
#define __s16 MS_S16
#endif

#ifndef __s8
#define __s8 MS_S8
#endif

#ifndef BOOL
#define BOOL MS_BOOL
#endif

#ifndef BOOLEAN
#define BOOLEAN MS_BOOL
#endif


#ifdef MS_DEBUG
#define ASSERT(_bool_)                                                                                      \
        {                                                                                                   \
            if ( ! ( _bool_ ) )                                                                             \
            {                                                                                               \
                diag_printf("ASSERT FAIL: %s, %s %s %d\n", #_bool_, __FILE__, __PRETTY_FUNCTION__, __LINE__);\
                MAsm_CPU_SwDbgBp();                                                                       \
            }                                                                                               \
        }
#else
#define ASSERT(_bool_) MS_ASSERT(_bool_)
#endif



//#define MsOS_DiableAllInterrupts() MsOS_DisableAllInterrupts()

//externC int  diag_printf( const char *fmt, ... );

#ifndef MSTAR_USB_DEBUG
#define MSTAR_USB_DEBUG                  0
#endif

/* Define trace levels. */
#define USB_DEBUG_LEVEL_ERROR          (1)    /* Error condition debug messages. */
#define USB_DEBUG_LEVEL_WARNING        (2)    /* Warning condition debug messages. */
#define USB_DEBUG_LEVEL_DEBUG          (3)    /* Debug messages (high debugging). */
#define USB_DEBUG_LEVEL_INFO           (4)    /* Infomation messages. */

#define USB_DEBUG_LEVEL                USB_DEBUG_LEVEL_WARNING


#if     (MSTAR_USB_DEBUG)
#define ehci_printf(fmt, arg...)       diag_printf(fmt, ##arg)
#define ehci_debug(dbg_lv, str, ...)                \
    do {                                            \
        if (dbg_lv > USB_DEBUG_LEVEL)               \
            break;                                  \
        else {                                      \
            ehci_printf(str, ##__VA_ARGS__);        \
        }                                           \
    } while(0)
#else  /* MSTAR_USB_DEBUG */
#define ehci_printf(...)
#define ehci_debug(enable, tag, str, ...) do{} while(0)
#endif /* MSTAR_USB_DEBUG */

//#define MSTAR_USB_DEBUG_MSG
#ifdef MSTAR_USB_DEBUG_MSG
#define ms_usbhost_msg(fmt, arg...)    \
        do {diag_printf(fmt, ##arg);} while(0)
#else
#define ms_usbhost_msg(...)
#endif

//#define MSTAR_USB_DEBUG_WARN
#ifdef MSTAR_USB_DEBUG_WARN
#define ms_usbhost_warn(fmt, arg...)    \
        do {diag_printf(fmt, ##arg);} while(0)
#else
#define ms_usbhost_warn(...)
#endif

//#define MSTAR_USB_DEBUG_DEBUG
#ifdef MSTAR_USB_DEBUG_DEBUG
#define ms_usbhost_debug(fmt, arg...)    \
        do {diag_printf(fmt, ##arg);} while(0)
#else
#define ms_usbhost_debug(...)
#endif

//Chip ID deifinition
#define CHIPID_NEPTUNE     0x2
#define CHIPID_ERIS        0x3
#define CHIPID_TITANIA     0x4
#define CHIPID_PLUTO       0x5
#define CHIPID_TRITON      0x6
#define CHIPID_TITANIA2    0xB
#define CHIPID_TITANIA3    0xF
#define CHIPID_EUCLID      0x15
#define CHIPID_TITANIA4    0x18
#define CHIPID_URANUS4     0x1B
#define CHIPID_TITANIA7    0x1C
#define CHIPID_JANUS       0x1D
#define CHIPID_TITANIA8    0x1F
#define CHIPID_TITANIA9    0x23
#define CHIPID_KRONUS      0x2F
#define CHIPID_KAISERIN      0x41
#define CHIPID_KAPPA       0x75
#define CHIPID_KELTIC      0x72
#define CHIPID_KENYA       0x7C
#define CHIPID_KRITI       0x87
#define CHIPID_KAISER      0x56
#define CHIPID_KERES       0x7E


#if defined(CHIP_U4)
    #define USB_LIB_CHIPID        CHIPID_URANUS4
#elif defined(CHIP_K1)
    #define USB_LIB_CHIPID        CHIPID_KRONUS
#elif defined(CHIP_K2)
    #define USB_LIB_CHIPID        CHIPID_KAISERIN
#elif defined(CHIP_KAPPA)
    #define USB_LIB_CHIPID        CHIPID_KAPPA
#elif defined(CHIP_KELTIC)
    #define USB_LIB_CHIPID        CHIPID_KELTIC
#elif defined(CHIP_KENYA)
    #define USB_LIB_CHIPID        CHIPID_KENYA
#elif defined(CHIP_KRITI)
    #define USB_LIB_CHIPID        CHIPID_KRITI
#elif defined(CHIP_KAISER)
    #define USB_LIB_CHIPID        CHIPID_KAISER
#elif defined(CHIP_KERES)
    #define USB_LIB_CHIPID        CHIPID_KERES
#else
    #error No USB Driver Supported
#endif

#endif

