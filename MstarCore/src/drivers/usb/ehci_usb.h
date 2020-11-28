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
#ifndef EHCI_USB_H
#define EHCI_USB_H

#include <MsTypes.h>
#include <ShareType.h>
extern MS_U32 MsOS_VA2PA(MS_U32 addr);
extern MS_U32 MsOS_PA2KSEG0(MS_U32 addr);
extern MS_U32 MsOS_PA2KSEG1(MS_U32 addr);

#define USB_DELAY(_msec)           wait_ms(_msec)
#if defined(CONFIG_JANUS) || defined(CONFIG_MARIA10)
#define KSEG02KSEG1(addr)  ((void *)((U32)(addr)|0x80000000))
#define KSEG12KSEG0(addr)  ((void *)((U32)(addr)&~0x80000000))
#elif defined(__ARM__)
#define KSEG02KSEG1(addr)  MsOS_PA2KSEG1(MsOS_VA2PA((U32)addr))
#define KSEG12KSEG0(addr)  MsOS_PA2KSEG0(MsOS_VA2PA((U32)addr))
#else
#define KSEG02KSEG1(addr)       ((void *)((UINT32)(addr)|0x20000000))  //cached -> unchched
#define KSEG12KSEG0(addr)       ((void *)((UINT32)(addr)&~0x20000000)) //unchched -> cached
#endif

#if (defined (CONFIG_TITANIA4)||defined(CONFIG_URANUS4)||defined(CONFIG_JANUS))||defined(CONFIG_MARIA10)||defined(CONFIG_KRONUS) ||defined(CONFIG_KAISERIN)
#define VA2PA(a)  (a)
#define PA2VA(a)  (a)
#elif defined(__ARM__)
//#define VA2PA(a)  MsOS_VA2PA((U32)a)
//#define PA2VA(a)  MsOS_PA2KSEG1((U32)a) //// mapping to uncache address
#if ENABLE_EAGLE
#define MIU0_BUS_BASE_ADDR	CONFIG_MIU0_BUSADDR
#define MIU0_PHY_BASE_ADDR	0x00000000UL
#define MIU1_BUS_BASE_ADDR	CONFIG_MIU1_BUSADDR
#define MIU1_PHY_BASE_ADDR	0x20000000UL
#elif ENABLE_AMBER3 || \
      ENABLE_AGATE || \
      ENABLE_EDISON || \
      ENABLE_MUJI || \
      ENABLE_CELTICS
#define MIU0_BUS_BASE_ADDR	CONFIG_MIU0_BUSADDR
#define MIU0_PHY_BASE_ADDR	0x00000000UL
#define MIU1_BUS_BASE_ADDR	CONFIG_MIU1_BUSADDR
#define MIU1_PHY_BASE_ADDR	0x80000000UL
#elif (ENABLE_NIKE) || \
      (ENABLE_MADISON) || \
      (ENABLE_MIAMI) || \
      (ENABLE_NADAL) || \
      (ENABLE_CLIPPERS)
#define MIU0_BUS_BASE_ADDR	CONFIG_MIU0_BUSADDR
#define MIU0_PHY_BASE_ADDR	0x00000000UL
#define MIU1_BUS_BASE_ADDR	CONFIG_MIU1_BUSADDR
#define MIU1_PHY_BASE_ADDR	0x40000000UL
#elif (ENABLE_MONACO)
#define ENABLE_USB_NEW_MIU_SEL	1
#define USB_MIU_SEL0	0x70
#define USB_MIU_SEL1	0xB8
#define USB_MIU_SEL2	0xDC
#define USB_MIU_SEL3	0xFF
#define MIU0_BUS_BASE_ADDR	CONFIG_MIU0_BUSADDR
#define MIU0_PHY_BASE_ADDR	0x00000000UL
#define MIU1_BUS_BASE_ADDR	CONFIG_MIU1_BUSADDR
#define MIU1_PHY_BASE_ADDR	0x80000000UL
#if defined(CONFIG_MIU2_BUSADDR)
	#define MIU2_BUS_BASE_ADDR	CONFIG_MIU2_BUSADDR
	#define MIU2_PHY_BASE_ADDR	0xC0000000UL
#endif
#else
#define MIU0_BUS_BASE_ADDR	CONFIG_MIU0_BUSADDR
#define MIU0_PHY_BASE_ADDR	0x00000000UL
#define MIU1_BUS_BASE_ADDR	CONFIG_MIU1_BUSADDR
#define MIU1_PHY_BASE_ADDR	0x80000000UL
#endif
/* transmit between BUS and USB PHY Addr */
extern U32 VA2PA(U32 u32_DMAAddr);
extern U32 PA2VA(U32 u32_DMAAddr);

#else
#define VA2PA(a)  ((a) & 0x1FFFFFFF)
#define PA2VA(a)  ((a) | 0xA0000000) //// mapping to uncache address
#endif

/* Requests: bRequest << 8 | bmRequestType */
#define RH_GET_STATUS           0x0080
#define RH_CLEAR_FEATURE        0x0100
#define RH_SET_FEATURE          0x0300
#define RH_SET_ADDRESS		0x0500
#define RH_GET_DESCRIPTOR	0x0680
#define RH_SET_DESCRIPTOR       0x0700
#define RH_GET_CONFIGURATION	0x0880
#define RH_SET_CONFIGURATION	0x0900
#define RH_GET_STATE            0x0280
#define RH_GET_INTERFACE        0x0A80
#define RH_SET_INTERFACE        0x0B00
#define RH_SYNC_FRAME           0x0C80

#if !defined(CONFIG_JANUS) && !defined(CONFIG_MARIA10)
#define _USB_FLUSH_BUFFER   1
#else
#define _USB_FLUSH_BUFFER   0
#endif

#endif

