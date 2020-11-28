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

/*
 * eHCI host controller driver
 *
 * Copyright (C) 2014 MStar Inc.
 *
 *            Warning
 * This file is only for Mstar
 * core chips later than Monaco.
 * ex.
 *     Monaco 2014/06/09
 */

#ifndef __PLATFORM_H__
#define __PLATFORM_H__
#define USBHOST_LIB_VER	"2014.06.09"

#include <configs/uboot_board_config.h> // system board definition
#include "MsTypes.h"

/* Select a OS Platform */
//#define SERET_ENV
#define MSTAR_UBOOT_ENV

/* General Setting for Mstar Platform USB Portting */
//#ifdef SERET_ENV
//#define CONFIG_USB_STORAGE 1
//#define USB_BAD_DEVICE_RETRY_PATCH 1
/* normal 1 + additional N */
//#define USB_BAD_DEV_MAX_RETRY 2
//#endif
#define USB_WAIT_LOOP_COUNT 0 // for super speed device

/* USB Test Mode */
// #define USB_TEST
#define USB_LEGEND_DATA_TOGGLE_METHOD

/****** Chip variable setting ******/
#if 1	/* Every Mstar chip should appley it */
	#define _USB_FLUSH_BUFFER	1
#else
	#define _USB_FLUSH_BUFFER	0
#endif

//---- 1. change override to hs_txser_en condition (DM always keep high issue)
//	#define ENABLE_HS_DM_KEEP_HIGH_ECO

//---- 2. fix pv2mi bridge mis-behavior
#if 1	/* Every Mstar chip should appley it */
	#define ENABLE_PV2MI_BRIDGE_ECO
#endif

//---- 3. 240's phase as 120's clock
#if 1	/* Every Mstar chip should appley it */
	/* bit<3> for 240's phase as 120's clock set 1, bit<4> for 240Mhz in mac 0 for faraday 1 for etron */
	#define ENABLE_UTMI_240_AS_120_PHASE_ECO
	//#define UTMI_240_AS_120_PHASE_ECO_INV
#endif

//---- 4. change to 55 interface
#if 1	/* Every Mstar chip should appley it */
	#define ENABLE_UTMI_55_INTERFACE
#endif

//---- 5. enabe PVCI i_miwcplt wait for mi2uh_last_done_z
#if 1	/* Every Mstar New chip should appley it */
#define _USB_MIU_WRITE_WAIT_LAST_DONE_Z_PATCH 1
#endif

//------ UTMI disconnect level parameters ---------------------------------
// 0x00: 550mv, 0x20: 575, 0x40: 600, 0x60: 625
#if 0
	// for 28 nm
	#define UTMI_DISCON_LEVEL_2A	(0x60)
#else
	#define UTMI_DISCON_LEVEL_2A	(0x0)
#endif

//------ UTMI eye diagram parameters ---------------------------------
#if 0
	// for 40nm
	#define UTMI_EYE_SETTING_2C	(0x98)
	#define UTMI_EYE_SETTING_2D	(0x02)
	#define UTMI_EYE_SETTING_2E	(0x10)
	#define UTMI_EYE_SETTING_2F	(0x01)
	#define UTMI_ALL_EYE_SETTING	(0x01100298)
#elif 0
	// for 40nm after Agate, use 55nm setting7
	#define UTMI_EYE_SETTING_2C	(0x90)
	#define UTMI_EYE_SETTING_2D	(0x03)
	#define UTMI_EYE_SETTING_2E	(0x30)
	#define UTMI_EYE_SETTING_2F	(0x81)
	#define UTMI_ALL_EYE_SETTING	(0x81300390)
#elif 0
	// for 40nm after Agate, use 55nm setting6
	#define UTMI_EYE_SETTING_2C	(0x10)
	#define UTMI_EYE_SETTING_2D	(0x03)
	#define UTMI_EYE_SETTING_2E	(0x30)
	#define UTMI_EYE_SETTING_2F	(0x81)
	#define UTMI_ALL_EYE_SETTING	(0x81300310)
#elif 0
	// for 40nm after Agate, use 55nm setting5
	#define UTMI_EYE_SETTING_2C	(0x90)
	#define UTMI_EYE_SETTING_2D	(0x02)
	#define UTMI_EYE_SETTING_2E	(0x30)
	#define UTMI_EYE_SETTING_2F	(0x81)
	#define UTMI_ALL_EYE_SETTING	(0x81300290)
#elif 0
	// for 40nm after Agate, use 55nm setting4
	#define UTMI_EYE_SETTING_2C	(0x90)
	#define UTMI_EYE_SETTING_2D	(0x03)
	#define UTMI_EYE_SETTING_2E	(0x00)
	#define UTMI_EYE_SETTING_2F	(0x81)
	#define UTMI_ALL_EYE_SETTING	(0x81000390)
#elif 0
	// for 40nm after Agate, use 55nm setting3
	#define UTMI_EYE_SETTING_2C	(0x10)
	#define UTMI_EYE_SETTING_2D	(0x03)
	#define UTMI_EYE_SETTING_2E	(0x00)
	#define UTMI_EYE_SETTING_2F	(0x81)
	#define UTMI_ALL_EYE_SETTING	(0x81000310)
#elif 0
	// for 40nm after Agate, use 55nm setting2
	#define UTMI_EYE_SETTING_2C	(0x90)
	#define UTMI_EYE_SETTING_2D	(0x02)
	#define UTMI_EYE_SETTING_2E	(0x00)
	#define UTMI_EYE_SETTING_2F	(0x81)
	#define UTMI_ALL_EYE_SETTING	(0x81000290)
#else
	// for 40nm after Agate, use 55nm setting1, the default
	#define UTMI_EYE_SETTING_2C	(0x10)
	#define UTMI_EYE_SETTING_2D	(0x02)
	#define UTMI_EYE_SETTING_2E	(0x00)
	#define UTMI_EYE_SETTING_2F	(0x81)
	#define UTMI_ALL_EYE_SETTING	(0x81000210)
#endif

/****** Porting environment setting ******/
#if defined(SERET_ENV)
	/* Delay Function */
	#include <timer.h>
	#define udelay(us)		udelay(us)

	/* buncing buffer enable for non cache flush API in cache enable system */
	// #define USB_BOUNCING_BUF	1
	#define readb(addr)		*((unsigned char volatile *)(addr))
	#define writeb(val, addr)	(*((unsigned char volatile *)(addr)) = (unsigned char)val)
	
	#define mdelay(ms)		{	MS_U32 i;		\
						for(i=0;i<ms;i++)	\
						udelay(1000);		\
					}

	#define USB_DELAY(ms)		mdelay(ms)
	#define wait_ms(ms)		mdelay(ms)
#endif

#if defined(MSTAR_UBOOT_ENV)
	extern MS_U32 MsOS_VA2PA(MS_U32 addr);
	extern MS_U32 MsOS_PA2KSEG0(MS_U32 addr);
	extern MS_U32 MsOS_PA2KSEG1(MS_U32 addr);
	extern void Chip_Read_Memory(void);
	extern void Chip_Flush_Memory(void);
	extern void   flush_cache   (unsigned long, unsigned long);

	/* Delay Function */
	void udelay (unsigned long);

	#define readb(addr)			*((unsigned char volatile *)(addr))
	#define writeb(val, addr)	(*((unsigned char volatile *)(addr)) = (unsigned char)val)
	#define readw(addr) 		*((volatile MS_UINT16 *)(addr))
	#define writew(val, addr)	(*((volatile MS_UINT16 *)(addr)) = (MS_UINT16)val)
	#define readl(addr) 		*((volatile MS_UINT32 *)(addr))
	#define writel(val, addr)	(*((volatile MS_UINT32 *)(addr)) = (MS_UINT32)val)

	#define mdelay(ms)		{	MS_U32 i;		\
						for(i=0;i<ms;i++)	\
						udelay(1000);		\
					}

	#define USB_DELAY(ms)		mdelay(ms)

	#if defined(__ARM__)
		#define KSEG02KSEG1(addr)	MsOS_PA2KSEG1(MsOS_VA2PA((MS_U32)addr))
		#define KSEG12KSEG0(addr)	MsOS_PA2KSEG0(MsOS_VA2PA((MS_U32)addr))
	#else
		#define KSEG02KSEG1(addr)	((void *)((MS_U32)(addr)|0x20000000))  //cached -> unchched
		#define KSEG12KSEG0(addr)	((void *)((MS_U32)(addr)&~0x20000000)) //unchched -> cached
	#endif

	/* virtual address to physical address translation */
	#if defined(__ARM__)
		#if (ENABLE_MONACO) 
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
		#elif (ENABLE_MIAMI)  //Only MIU0/MIU1
		        #define ENABLE_USB_NEW_MIU_SEL	1
			#define USB_MIU_SEL0	0x70
			#define USB_MIU_SEL1	0xB8
			#define USB_MIU_SEL2	0xFF
			#define USB_MIU_SEL3	0xFF
			#define MIU0_BUS_BASE_ADDR	CONFIG_MIU0_BUSADDR
			#define MIU0_PHY_BASE_ADDR	0x00000000UL
			#define MIU1_BUS_BASE_ADDR	CONFIG_MIU1_BUSADDR
			#define MIU1_PHY_BASE_ADDR	0x80000000UL			
		#elif (ENABLE_MUJI)  //Only MIU0/MIU1
		        #define ENABLE_USB_NEW_MIU_SEL	1
			#define USB_MIU_SEL0	0x70
			#define USB_MIU_SEL1	0xB8
			#define USB_MIU_SEL2	0xFF
			#define USB_MIU_SEL3	0xFF
			#define MIU0_BUS_BASE_ADDR	CONFIG_MIU0_BUSADDR
			#define MIU0_PHY_BASE_ADDR	0x00000000UL
			#define MIU1_BUS_BASE_ADDR	CONFIG_MIU1_BUSADDR
			#define MIU1_PHY_BASE_ADDR	0x80000000UL			
		#elif (ENABLE_CELTICS)  //Only MIU0/MIU1
		    #define ENABLE_USB_NEW_MIU_SEL	1
			#define USB_MIU_SEL0	0x70
			#define USB_MIU_SEL1	0xB8
			#define USB_MIU_SEL2	0xFF
			#define USB_MIU_SEL3	0xFF
			#define MIU0_BUS_BASE_ADDR	CONFIG_MIU0_BUSADDR
			#define MIU0_PHY_BASE_ADDR	0x00000000UL
			#define MIU1_BUS_BASE_ADDR	CONFIG_MIU1_BUSADDR
			#define MIU1_PHY_BASE_ADDR	0x80000000UL			
		#else
			#define MIU0_BUS_BASE_ADDR	CONFIG_MIU0_BUSADDR
			#define MIU0_PHY_BASE_ADDR	0x00000000UL
			#define MIU1_BUS_BASE_ADDR	CONFIG_MIU1_BUSADDR
			#define MIU1_PHY_BASE_ADDR	0x80000000UL
		#endif

		/* transmit between BUS and USB PHY Addr */
		extern unsigned int VA2PA(unsigned int u32_DMAAddr);
		extern unsigned int PA2VA(unsigned int u32_DMAAddr);
	#elif defined(__MIPS__)
		#define VA2PA(a)  (a)
		#define PA2VA(a)  (a)
	#else // ??? which CPU
		#define VA2PA(a)  ((a) & 0x1FFFFFFF)
		#define PA2VA(a)  ((a) | 0xA0000000) //// mapping to uncache address
	#endif
#endif

/* RIU Base */
#if defined(__ARM__)
	#define HW_BASE		0x1f200000
#elif defined(__MIPS__)
	#define HW_BASE		0xbf200000
#else
	#error Unknow CPU core type
#endif

#if defined(CONFIG_ARM)
#define _MSTAR_PM_BASE         0x1F000000
#else
#define _MSTAR_PM_BASE         0xBF000000
#endif

#define EHCFLAG_NONE		0x0
#define EHCFLAG_DPDM_SWAP	0x1
#define EHCFLAF_XHC_COMP	0x2

/* xhc definition */
#if (ENABLE_MONACO) || (ENABLE_MIAMI) || (ENABLE_MUJI) || (ENABLE_CELTICS)
#define XHCI_2PORTS
#endif

#if (ENABLE_MONACO) || (ENABLE_MIAMI) || (ENABLE_MUJI) || (ENABLE_CELTICS)
#define XHCI_PORT0_ADDR		(HW_BASE+0x90440)
#define XHCI_PORT1_ADDR		(HW_BASE+0x90450)
#define MSTAR_U3TOP_BASE	(HW_BASE+(0x22500 << 1))
#endif

/* struct xhc_comp */
#define XHC_COMP_NONE		{0}
#define XHC_COMP_PORT0		{0, XHCI_PORT0_ADDR, MSTAR_U3TOP_BASE}
#define XHC_COMP_PORT1		{1, XHCI_PORT1_ADDR, MSTAR_U3TOP_BASE}


/* Register base mapping */
/* Port0 */
#define MSTAR_UTMI_BASE  (HW_BASE+(0x3A80 << 1))
#define MSTAR_USBC_BASE  (HW_BASE+(0x0700 << 1))
#define MSTAR_UHC_BASE   (HW_BASE+(0x2400 << 1))

#if (ENABLE_MONACO) || (ENABLE_MIAMI) || (ENABLE_MUJI) || (ENABLE_CELTICS)
	#define MSTAR_BC_BASE	(HW_BASE+(0x23600 << 1))
#else
	#define MSTAR_BC_BASE    0
#endif

#if 0
	#define MSTAR_INIT_FLAG     EHCFLAG_DPDM_SWAP
#else
	#define MSTAR_INIT_FLAG     EHCFLAG_NONE
#endif

#define MSTAR_COMP0			XHC_COMP_NONE

/* Port1 */
#define MSTAR_UTMI1_BASE  (HW_BASE+(0x3A00 << 1))
#define MSTAR_USBC1_BASE  (HW_BASE+(0x0780 << 1))
#define MSTAR_UHC1_BASE   (HW_BASE+(0x0D00 << 1))

#if (ENABLE_MONACO) || (ENABLE_MIAMI) || (ENABLE_MUJI) || (ENABLE_CELTICS)
	#define MSTAR_BC1_BASE	(HW_BASE+(0x23620 << 1))
#else
	#define MSTAR_BC1_BASE	0
#endif

#if 0
	#define MSTAR_INIT1_FLAG	EHCFLAG_DPDM_SWAP
#else
	#define MSTAR_INIT1_FLAG	EHCFLAG_NONE
#endif

#define MSTAR_COMP1			XHC_COMP_NONE

/* Port2 */
#define MSTAR_UTMI2_BASE  (HW_BASE+(0x3900 << 1))
#define MSTAR_USBC2_BASE  (HW_BASE+(0x13800 << 1))
#define MSTAR_UHC2_BASE   (HW_BASE+(0x13900 << 1))

#if (ENABLE_MONACO) || (ENABLE_MIAMI) || (ENABLE_MUJI) || (ENABLE_CELTICS)
	#define MSTAR_BC2_BASE	(HW_BASE+(0x23640 << 1))
#else
	#define MSTAR_BC2_BASE	0
#endif

#if 0
	#define MSTAR_INIT2_FLAG     EHCFLAG_DPDM_SWAP
#else
	#define MSTAR_INIT2_FLAG     EHCFLAG_NONE
#endif

#define MSTAR_COMP2			XHC_COMP_NONE

/* Port3 */
#if (ENABLE_MONACO) || (ENABLE_MIAMI) || (ENABLE_MUJI) || (ENABLE_CELTICS)
	#define MSTAR_UTMI3_BASE	(HW_BASE+(0x22300 << 1))
	#define MSTAR_USBC3_BASE	(HW_BASE+(0x53200 << 1))
	#define MSTAR_UHC3_BASE		(HW_BASE+(0x53000 << 1))
	#define MSTAR_BC3_BASE		(HW_BASE+(0x23680 << 1))
#else
	/* deault: null Port3 base */
	#define MSTAR_UTMI3_BASE	(0x00000000)
	#define MSTAR_USBC3_BASE	(0x00000000)
	#define MSTAR_UHC3_BASE		(0x00000000)
	#define MSTAR_BC3_BASE		(0x00000000)
#endif

#if 0
	#define MSTAR_INIT3_FLAG     EHCFLAG_DPDM_SWAP
#elif (ENABLE_MONACO) || (ENABLE_MIAMI) || (ENABLE_MUJI) || (ENABLE_CELTICS)
	#define MSTAR_INIT3_FLAG     EHCFLAF_XHC_COMP
#else
	#define MSTAR_INIT3_FLAG     EHCFLAG_NONE
#endif

#if (ENABLE_MONACO) || (ENABLE_MIAMI) || (ENABLE_MUJI) || (ENABLE_CELTICS)
	#define MSTAR_COMP3     	XHC_COMP_PORT0
#else
	#define MSTAR_COMP3     	XHC_COMP_NONE
#endif


/* Port4 */
#if (ENABLE_MONACO) || (ENABLE_MIAMI) || (ENABLE_MUJI) || (ENABLE_CELTICS)
	#define MSTAR_UTMI4_BASE	(HW_BASE+(0x22380 << 1))
	#define MSTAR_USBC4_BASE	(HW_BASE+(0x53280 << 1))
	#define MSTAR_UHC4_BASE		(HW_BASE+(0x53100 << 1))
	#define MSTAR_BC4_BASE		(HW_BASE+(0x236A0 << 1))
#else
	/* deault: null Port3 base */
	#define MSTAR_UTMI4_BASE	(0x00000000)
	#define MSTAR_USBC4_BASE	(0x00000000)
	#define MSTAR_UHC4_BASE		(0x00000000)
	#define MSTAR_BC4_BASE		(0x00000000)
#endif

#if 0
	#define MSTAR_INIT4_FLAG     EHCFLAG_DPDM_SWAP
#elif (ENABLE_MONACO) || (ENABLE_MIAMI) || (ENABLE_MUJI) || (ENABLE_CELTICS)
	#define MSTAR_INIT4_FLAG     EHCFLAF_XHC_COMP
#else
	#define MSTAR_INIT4_FLAG     EHCFLAG_NONE
#endif

#if (ENABLE_MONACO) || (ENABLE_MIAMI) || (ENABLE_MUJI) || (ENABLE_CELTICS)
	#define MSTAR_COMP4     	XHC_COMP_PORT1
#else
	#define MSTAR_COMP4     	XHC_COMP_NONE
#endif


/* Port5 */
#if 0
	#define MSTAR_UTMI5_BASE	(HW_BASE+(0x << 1))
	#define MSTAR_USBC5_BASE	(HW_BASE+(0x << 1))
	#define MSTAR_UHC5_BASE		(HW_BASE+(0x << 1))
	#define MSTAR_BC5_BASE		(HW_BASE+(0x << 1))
#else
	/* deault: null Port5 base */
	#define MSTAR_UTMI5_BASE	(0x00000000)
	#define MSTAR_USBC5_BASE	(0x00000000)
	#define MSTAR_UHC5_BASE		(0x00000000)
	#define MSTAR_BC5_BASE		(0x00000000)
#endif

#if 0
	#define MSTAR_INIT5_FLAG     EHCFLAG_DPDM_SWAP
#else
	#define MSTAR_INIT5_FLAG     EHCFLAG_NONE
#endif

#define MSTAR_COMP5 		XHC_COMP_NONE


#endif /* __PLATFORM_H__*/
