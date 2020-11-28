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

#include "inc/asm/platform.h"
#include "inc/common.h"
#include "inc/drvhostlib.h"
#include "inc/ubootglue.h"

#ifdef USB_GLUE_DEBUG
#define USB_GLUE_PRINTF MS_MSG
#else
#define USB_GLUE_PRINTF(fmt, ...)
#endif

/* root hub port status */
static struct usb_port_status rh_status = { 0 };
extern int UsbPortSelect;

#define MAX_ROOT_PORTS 8 // depends on chip
struct usb_hcd array_usb_root_port[MAX_ROOT_PORTS] =
{
	{0, MSTAR_UTMI_BASE,MSTAR_UHC_BASE, MSTAR_USBC_BASE, MSTAR_BC_BASE, MSTAR_INIT_FLAG, 0, MSTAR_COMP0},
	{1, MSTAR_UTMI1_BASE,MSTAR_UHC1_BASE, MSTAR_USBC1_BASE, MSTAR_BC1_BASE, MSTAR_INIT1_FLAG, 0, MSTAR_COMP1},
	{2, MSTAR_UTMI2_BASE,MSTAR_UHC2_BASE, MSTAR_USBC2_BASE, MSTAR_BC2_BASE, MSTAR_INIT2_FLAG, 0, MSTAR_COMP2},
	{3, MSTAR_UTMI3_BASE,MSTAR_UHC3_BASE, MSTAR_USBC3_BASE, MSTAR_BC3_BASE, MSTAR_INIT3_FLAG, 0, MSTAR_COMP3},
	{4, MSTAR_UTMI4_BASE,MSTAR_UHC4_BASE, MSTAR_USBC4_BASE, MSTAR_BC4_BASE, MSTAR_INIT4_FLAG, 0, MSTAR_COMP4},
	{5, MSTAR_UTMI5_BASE,MSTAR_UHC5_BASE, MSTAR_USBC5_BASE, MSTAR_BC5_BASE, MSTAR_INIT5_FLAG, 0, MSTAR_COMP5},
};

int FirstBulkIn,FirstBulkOut; // for compile 

#if defined(__ARM__)
static u32 miu0_bus_base_addr;
static u32 miu1_bus_base_addr;
#if defined(MIU2_BUS_BASE_ADDR)
static U32 miu2_bus_base_addr;
#endif

unsigned int VA2PA(unsigned int u32_DMAAddr)
{
	u32_DMAAddr = MsOS_VA2PA(u32_DMAAddr);

	if(u32_DMAAddr < miu1_bus_base_addr)
	{
		u32_DMAAddr -= miu0_bus_base_addr;
		u32_DMAAddr += MIU0_PHY_BASE_ADDR;
	}
#if defined(MIU2_BUS_BASE_ADDR)
	else if(u32_DMAAddr < miu2_bus_base_addr)
	{
		u32_DMAAddr -= miu1_bus_base_addr;
		u32_DMAAddr |= MIU1_PHY_BASE_ADDR;
	}
	else
	{
		u32_DMAAddr -= miu2_bus_base_addr;
		u32_DMAAddr |= MIU2_PHY_BASE_ADDR;
	}
#else
	else
	{
		u32_DMAAddr -= miu1_bus_base_addr;
		u32_DMAAddr |= MIU1_PHY_BASE_ADDR;
	}
#endif
	return u32_DMAAddr;
}

unsigned int PA2VA(unsigned int u32_DMAAddr)
{
	if(u32_DMAAddr < MIU1_PHY_BASE_ADDR)
	{
		u32_DMAAddr -= MIU0_PHY_BASE_ADDR;
		u32_DMAAddr += miu0_bus_base_addr;
	}
#if defined(MIU2_BUS_BASE_ADDR)
	else if(u32_DMAAddr < MIU2_PHY_BASE_ADDR)
	{
		u32_DMAAddr -= MIU1_PHY_BASE_ADDR;
		u32_DMAAddr |= miu1_bus_base_addr;
	}
	else 
	{
		u32_DMAAddr -= MIU2_PHY_BASE_ADDR;
		u32_DMAAddr |= miu2_bus_base_addr;
	}
#else
	else 
	{
		u32_DMAAddr -= MIU1_PHY_BASE_ADDR;
		u32_DMAAddr |= miu1_bus_base_addr;
	}    
#endif
	u32_DMAAddr=MsOS_PA2KSEG1(u32_DMAAddr); // mapping to uncache address

	return  u32_DMAAddr;
}
#endif

static void usb_bc_enable(u32 utmi_base, u32 bc_base, u8 enable)
{
	if (!bc_base)
		return;
    
	if (enable)
	{
		//printf("BC enable \n");
		writeb(readb((void *)(utmi_base+(0x1*2-1))) | 0x40, (void *)(utmi_base+(0x1*2-1)));  //IREF_PDN=1¡¦b1. (utmi+0x01[6] )
		writeb(readb((void *)(bc_base+(0x3*2-1))) | 0x40, (void *)(bc_base+(0x3*2-1)));  // [6]= reg_host_bc_en
		writeb(readb((void *)(bc_base+(0xc*2))) | 0x40, (void *)(bc_base+(0xc*2)));  // [6]= reg_into_host_bc_sw_tri
		writeb(0x00, (void *)(bc_base));  // [15:0] = bc_ctl_ov_en
		writeb(0x00, (void *)(bc_base+(0x1*2-1)));  // [15:0] = bc_ctl_ov_en
		writeb(readb((void *)(bc_base+(0xa*2))) | 0x80, (void *)(bc_base+(0xa*2)));  // [7]=reg_bc_switch_en
	}
	else
	{
		// disable BC
		//printf("BC disable \n");
		writeb(readb((void *)(bc_base+(0xc*2))) & (~0x40), (void *)(bc_base+(0xc*2)));  // [6]= reg_into_host_bc_sw_tri
		writeb(readb((void *)(bc_base+(0x3*2-1))) & (~0x40), (void *)(bc_base+(0x3*2-1)));  // [6]= reg_host_bc_en
		writeb(readb((void *)(utmi_base+(0x1*2-1))) & (~0x40), (void *)(utmi_base+(0x1*2-1)));  //IREF_PDN=1¡¦b1. (utmi+0x01[6] )
	}
}

void xhci_ppc(struct xhc_comp *xhci, int	bOn)
{
	u16 addr_w, bit_num;
	u32 addr, gpio_addr;
	u8  value, low_active;

	switch (xhci->port_index) {
	case 0:
		addr_w = readw((void*)(xhci->u3top_base+0xFC*2));
		addr = (u32)addr_w << 8;
		addr_w = readw((void*)(xhci->u3top_base+0xFE*2));
		addr |= addr_w & 0xFF;
		bit_num = (addr_w >> 8) & 0x7;
		low_active = (u8)((addr_w >> 11) & 0x1);
		break;
	case 1:
		addr_w = readw((void*)(xhci->u3top_base+0xE6*2));
		addr = (u32)addr_w << 8;
		addr_w = readw((void*)(xhci->u3top_base+0xE8*2));
		addr |= addr_w & 0xFF;
		bit_num = (addr_w >> 8) & 0x7;
		low_active = (u8)((addr_w >> 11) & 0x1);
		break;
	default:	/* "can't happen" */
		return;
	}
	
	if (addr)
	{
		printf("xhci_ppc: turn %s USB3.0 port %d power \n", (bOn) ? "on" : "off", xhci->port_index);
		printf("Addr: 0x%x bit_num: %d low_active:%d\n", addr, bit_num, low_active);

		value = (u8)(1 << bit_num);
		if (addr & 0x1)
			gpio_addr = _MSTAR_PM_BASE+addr*2-1;
		else
			gpio_addr = _MSTAR_PM_BASE+addr*2;

		if (low_active^bOn)
		{
			writeb(readb((void*)gpio_addr) | value, (void*)gpio_addr); 
		}
		else
		{
			writeb(readb((void*)gpio_addr) & (u8)(~value), (void*)gpio_addr); 
		}
	}
	else {
		printf("\n\n!!!! ERROR : xhci: no GPIO information for vbus port power control  !!!! \n\n");
		return;
	}	


}


#if defined(ENABLE_USB_NEW_MIU_SEL)
void MIU_select_setting_ehc(unsigned int USBC_base)
{
	printf("[USB] config miu select [%x] [%x] [%x] ][%x]\n", USB_MIU_SEL0, USB_MIU_SEL1, USB_MIU_SEL2, USB_MIU_SEL3);
	writeb(USB_MIU_SEL0, (void*)(USBC_base+0x14*2));        //Setting MIU0 segment
	writeb(USB_MIU_SEL1, (void*)(USBC_base+0x16*2));        //Setting MIU1 segment
	writeb(USB_MIU_SEL2, (void*)(USBC_base+0x17*2-1));      //Setting MIU2 segment
	writeb(USB_MIU_SEL3, (void*)(USBC_base+0x18*2));        //Setting MIU3 segment
	writeb(readb((void*)(USBC_base+0x19*2-1)) | 0x01, (void*)(USBC_base+0x19*2-1)); //Enable miu partition mechanism
}
#endif

void TV_usb_init(struct usb_hcd *hcd)
{
	USB_GLUE_PRINTF("[USB] TV_usb_init (UTMI Init) ++\n");
	USB_GLUE_PRINTF("[USB] UTMI Base %8x\n", hcd->utmi_base);
	USB_GLUE_PRINTF("[USB] UHC Base %8x\n", hcd->ehc_base);
	USB_GLUE_PRINTF("[USB] USBC Base %8x\n", hcd->usbc_base);
	USB_GLUE_PRINTF("[USB] BC Base %8x\n", hcd->bc_base);

#if defined(ENABLE_USB_NEW_MIU_SEL)
	MIU_select_setting_ehc(hcd->usbc_base);
#endif
	writeb(0x0A, hcd->usbc_base);	/* Disable MAC initial suspend, Reset UHC */
	writeb(0x28, hcd->usbc_base);	/* Release UHC reset, enable UHC XIU function */

	writeb(readb(hcd->utmi_base+0x3C*2) | 0x01, hcd->utmi_base+0x3C*2);	/* set CA_START as 1 */

	mdelay(1); // 10->1

	writeb(readb(hcd->utmi_base+0x3C*2) & ~0x01, hcd->utmi_base+0x3C*2);	/* release CA_START */
#if defined(ENABLE_HS_DM_KEEP_HIGH_ECO)
	writeb(readb((void*)hcd->utmi_base+0x10*2) | 0x40, (void*) (hcd->utmi_base+0x10*2)); // bit<6> for monkey test and HS current
#endif
	while (((unsigned int)(readb(hcd->utmi_base+0x3C*2)) & 0x02) == 0);	/* polling bit <1> (CA_END) */

	if (hcd->init_flag & EHCFLAG_DPDM_SWAP)
		writeb(readb(hcd->utmi_base+0x0b*2-1) |0x20, hcd->utmi_base+0x0b*2-1);	/* dp dm swap */
	writeb(readb(hcd->usbc_base+0x02*2) & ~0x03, hcd->usbc_base+0x02*2);	/* UHC select enable */
	writeb(readb(hcd->usbc_base+0x02*2) | 0x01, hcd->usbc_base+0x02*2);	/* UHC select enable */

	writeb(readb(hcd->ehc_base+0x40*2) & ~0x10, hcd->ehc_base+0x40*2);	/* 0: VBUS On. */
	udelay(1);	/* delay 1us */
	writeb(readb(hcd->ehc_base+0x40*2) | 0x08, hcd->ehc_base+0x40*2);	/* Active HIGH */

	writeb((readb(hcd->utmi_base+0x06*2) & 0x9F) | 0x40, hcd->utmi_base+0x06*2);	/* reg_tx_force_hs_current_enable */

	writeb(readb(hcd->utmi_base+0x03*2-1) | 0x28, hcd->utmi_base+0x03*2-1);	/* Disconnect window select */
	writeb(readb(hcd->utmi_base+0x03*2-1) & 0xef, hcd->utmi_base+0x03*2-1);	/* Disconnect window select */
	writeb(readb(hcd->utmi_base+0x07*2-1) & 0xfd, hcd->utmi_base+0x07*2-1);	/* Disable improved CDR */

#if defined(ENABLE_UTMI_240_AS_120_PHASE_ECO)
	#if defined(UTMI_240_AS_120_PHASE_ECO_INV)
	writeb(readb((void*)hcd->utmi_base+0x08*2) & ~0x08, (void*) (hcd->utmi_base+0x08*2)); // bit<3> special for Eiffel analog LIB issue
	#else
	writeb(readb(hcd->utmi_base+0x08*2) | 0x08, hcd->utmi_base+0x08*2);	/* bit<3> for 240's phase as 120's clock set 1, bit<4> for 240Mhz in mac 0 for faraday 1 for etron */
	#endif
#endif

	writeb(readb(hcd->utmi_base+0x09*2-1) | 0x81, hcd->utmi_base+0x09*2-1);	/* UTMI RX anti-dead-loc, ISI effect improvement */
	writeb(readb(hcd->utmi_base+0x0b*2-1) | 0x80, hcd->utmi_base+0x0b*2-1);	/* TX timing select latch path */
	writeb(readb(hcd->utmi_base+0x15*2-1) | 0x20, hcd->utmi_base+0x15*2-1);	/* Chirp signal source select */
#if defined(ENABLE_UTMI_55_INTERFACE)
	writeb(readb(hcd->utmi_base+0x15*2-1) | 0x40, hcd->utmi_base+0x15*2-1);	/* change to 55 interface */
#endif

#if defined(ENABLE_PV2MI_BRIDGE_ECO)
	writeb(readb((hcd->usbc_base+0x0a*2)) | 0x40, hcd->usbc_base+0x0a*2);
#endif
	/* Init UTMI eye diagram parameter setting */
	writeb(readb(hcd->utmi_base+0x2c*2) | UTMI_EYE_SETTING_2C, hcd->utmi_base+0x2c*2);
	writeb(readb(hcd->utmi_base+0x2d*2-1) | UTMI_EYE_SETTING_2D, hcd->utmi_base+0x2d*2-1);
	writeb(readb(hcd->utmi_base+0x2e*2) | UTMI_EYE_SETTING_2E, hcd->utmi_base+0x2e*2);
	writeb(readb(hcd->utmi_base+0x2f*2-1) | UTMI_EYE_SETTING_2F, hcd->utmi_base+0x2f*2-1);

#if _USB_MIU_WRITE_WAIT_LAST_DONE_Z_PATCH
	/* Enabe PVCI i_miwcplt wait for mi2uh_last_done_z */
	writeb(readb(hcd->ehc_base+0x83*2-1) | MS_BIT4, hcd->ehc_base+0x83*2-1);
#endif

	usb_bc_enable(hcd->utmi_base, hcd->bc_base, FALSE);

	USB_GLUE_PRINTF ("[USB] TV_usb_init--\n");
}

int Usb_host_Init(struct usb_hcd *hcd, unsigned int delay)
{
	unsigned int usb_retry_cnt = USB_WAIT_LOOP_COUNT;

	USB_GLUE_PRINTF ("[USB] Usb_host_Init++\n");

	hcd->ever_inited = 1;

	/* Data length byte alignment issue */
	flib_Host20_Fix_DataLength_ByteAlign(hcd);

usb_device_detect_retry:
	if (flib_Host20_Init(hcd, 0, delay)==0)
	{
		if (usb_retry_cnt--)
		{
			MS_MSG("[USB] waiting for connecting...%d\n", usb_retry_cnt+1);
			goto usb_device_detect_retry;
		}
		MS_MSG("[USB] USB init failed\n");
		return -1;
	}

	USB_GLUE_PRINTF ("[USB] Usb_host_Init--\n");
	return hcd->bSpeed;
}

int _usb_lowlevel_init(int entry)
{
	int speed = -1;
	int ret = 0;
	struct usb_hcd *hcd = &array_usb_root_port[UsbPortSelect];

#if defined(__ARM__)
	miu0_bus_base_addr = MsOS_VA2PA(MIU0_BUS_BASE_ADDR);
	miu1_bus_base_addr = MsOS_VA2PA(MIU1_BUS_BASE_ADDR); 
	#if defined(MIU2_BUS_BASE_ADDR)
	miu2_bus_base_addr = MsOS_VA2PA(MIU2_BUS_BASE_ADDR); 
	#endif
#endif

	USB_GLUE_PRINTF ("[USB] usb_lowlevel_init++\n");

	MS_MSG ("[USB] USB EHCI LIB VER: %s\n", USBHOST_LIB_VER);
	MS_MSG ("[USB] Port %d is Enabled\n", UsbPortSelect);

	if (hcd->init_flag & EHCFLAF_XHC_COMP)
	{
		//disable port
		xhci_ssport_set_state(&hcd->xhci, false);
		//turn on power
		xhci_ppc(&hcd->xhci, true);
	}

	TV_usb_init(hcd);
	if (entry == 1)
		goto port_status;

	speed = (entry == 2) ? Usb_host_Init(hcd, 0) :
		Usb_host_Init(hcd, USB_WAIT_TIME) ;
port_status:
	if (speed == 1)
	{
		rh_status.wPortStatus |= USB_PORT_STAT_CONNECTION | USB_PORT_STAT_LOW_SPEED;
	}
	else
	{
		rh_status.wPortStatus |= USB_PORT_STAT_CONNECTION;
		rh_status.wPortStatus &= ~USB_PORT_STAT_LOW_SPEED;

		if(speed == -1)
			ret = -1;
	}

	rh_status.wPortChange |= USB_PORT_STAT_C_CONNECTION;
	USB_GLUE_PRINTF ("[USB] usb_lowlevel_init--\n");    
	return ret;
}

inline int usb_lowlevel_init(void)
{
	return _usb_lowlevel_init(0);
}

inline int usb_lowlevel_preinit(void)
{
	return _usb_lowlevel_init(1);
}

inline int usb_lowlevel_postinit(void)
{
	return _usb_lowlevel_init(2);
}

int usb_lowlevel_stop(int p)
{
	struct usb_hcd *hcd = &array_usb_root_port[p];

	if(hcd->ever_inited == 0)
		return 0;

	flib_Host20_StopRun_Setting(hcd, HOST20_Disable);

	if (hcd->init_flag & EHCFLAF_XHC_COMP)
	{
		//turn off power
		xhci_ppc(&hcd->xhci, false);
		//enable port
		xhci_ssport_set_state(&hcd->xhci, true);
		mdelay(1000);
	}

	if (hcd->ever_inited == 2)
	{
		MS_MSG("[USB] Long time stable device. Waiting .5 second...\n");
		mdelay(500);
	}
	
	return 0;
}

inline void Usb_host_SetEverInited(int val)
{
	struct usb_hcd *hcd = &array_usb_root_port[UsbPortSelect];

	hcd->ever_inited = val;
}

inline void SetControl1MaxPacketEx(MS_UINT8 max, int port)
{
	struct usb_hcd *hcd = &array_usb_root_port[UsbPortSelect];

	flib_Host20_SetControl1MaxPacket(hcd, max);
}

inline void USB_Bulk_InitEx(struct usb_device *dev, int port)
{
	struct usb_hcd *hcd = &array_usb_root_port[UsbPortSelect];

	hcd->FirstBulkIn = 1;
	hcd->FirstBulkOut = 1;
#ifdef USB_LEGEND_DATA_TOGGLE_METHOD
	FirstBulkIn = 1;
	FirstBulkOut = 1;
#endif    
	/* report device speed */
	dev->speed = hcd->bSpeed;
	flib_Host20_Bulk_Init(dev, hcd);
}

int submit_bulk_msg(struct usb_device *dev, unsigned long pipe, void *buffer, int len)
{
	int dir_out = usb_pipeout(pipe);
	int done = 0;    
	struct usb_hcd *hcd = &array_usb_root_port[UsbPortSelect];

	/* deal with bulk endpoint data toggle */
#ifdef USB_LEGEND_DATA_TOGGLE_METHOD
	hcd->FirstBulkIn = (FirstBulkIn != hcd->FirstBulkIn) ? FirstBulkIn : hcd->FirstBulkIn;
	hcd->FirstBulkOut = (FirstBulkOut != hcd->FirstBulkOut) ? FirstBulkOut : hcd->FirstBulkOut;
#endif
	dev->status = 0;

	if (flib_Host20_Send_Receive_Bulk_Data(hcd, buffer,len,dir_out)>0)
	{
		dev->status = hcd->urb_status;
		return -1;
	}

	dev->act_len = done;
	/* deal with bulk endpoint data toggle */
#ifdef USB_LEGEND_DATA_TOGGLE_METHOD
	FirstBulkIn = (FirstBulkIn == hcd->FirstBulkIn) ? FirstBulkIn : hcd->FirstBulkIn;
	FirstBulkOut = (FirstBulkOut == hcd->FirstBulkOut) ? FirstBulkOut : hcd->FirstBulkOut;
#endif
	return 0;
}

int submit_control_msg(struct usb_device *dev, unsigned long pipe, void *buffer,
		int len,struct devrequest *setup)
{
	int done = 0;
	struct usb_hcd *hcd = &array_usb_root_port[UsbPortSelect];

	dev->status = 0;

	if ( flib_Host20_Issue_Control (hcd, dev->devnum,(unsigned char*) setup,len,(unsigned char*) buffer) > 0)
	{
		dev->status = hcd->urb_status;
		done=-1;
	}

	/* status phase */
	dev->act_len = len;

	/* deal with bulk endpoint data toggle */
#ifndef USB_LEGEND_DATA_TOGGLE_METHOD
	/* clear feature: endpoint stall */
	if ((setup->request == USB_REQ_CLEAR_FEATURE) && (setup->requesttype == USB_RECIP_ENDPOINT))
	{
		if (pipe & USB_DIR_IN)
			hcd->FirstBulkIn = 1;
		else
			hcd->FirstBulkOut = 1;
	}
#endif
	return done;
}

int submit_int_msg(struct usb_device *dev, unsigned long pipe, void *buffer, int len, int interval)
{
	return -1;
}
