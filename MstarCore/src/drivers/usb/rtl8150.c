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

//-------------------------------------------------------------------------------------------------
//  Include files
//-------------------------------------------------------------------------------------------------
#include <common.h>

#include <net.h>
#include "usb.h"
#include "usb_lan.h"


#define	IDR					0x0120
#define	MAR					0x0126
#define	CR					0x012e
#define	TCR					0x012f
#define	RCR					0x0130
#define	TSR					0x0132
#define	RSR					0x0133
#define	CON0				0x0135
#define	CON1				0x0136
#define	MSR					0x0137
#define	PHYADD				0x0138
#define	PHYDAT				0x0139
#define	PHYCNT				0x013b
#define	GPPC				0x013d
#define	BMCR				0x0140
#define	BMSR				0x0142
#define	ANAR				0x0144
#define	ANLP				0x0146
#define	AER					0x0148
#define CSCR				0x014C  /* This one has the link status */
#define CSCR_LINK_STATUS	(1 << 3)

#define	USB_LAN_REQT_READ	    0xc0
#define	USB_LAN_REQT_WRITE	    0x40
#define	USB_LAN_REQ_GET_REGS	0x05
#define	USB_LAN_REQ_SET_REGS	0x05

/* Receive status register errors */
#define RSR_ROK             (1)
#define RSR_CRC				(1<<2)
#define RSR_FAE				(1<<1)
#define RSR_ERRORS			(RSR_CRC | RSR_FAE)

#define	RTL8150_MTU			1700

unsigned char netbuf[RTL8150_MTU+92]  __attribute__ ((aligned (128)));

/* NIC specific static variables go here */
static char packet[2096];

extern void __inline__ wait_ms(unsigned long ms);
extern int usb_bulk_transfer_in(struct usb_device *dev,
			void *data, int len,int *transdata);
extern int usb_bulk_transfer_out(struct usb_device *dev,
			void *data, int len);

/**************************************************************************
RTL 8150 Operations
***************************************************************************/
static int get_registers(const struct eth_device *nic, u16 indx, u16 size, void *data)
{
    return usb_control_msg(nic->udev, usb_rcvctrlpipe(nic->udev, 0),
        USB_LAN_REQ_GET_REGS, USB_LAN_REQT_READ,
        indx, 0, data, size, 500);
}

static int set_registers(const struct eth_device *nic, u16 indx, u16 size, void *data)
{
    return usb_control_msg(nic->udev, usb_sndctrlpipe(nic->udev, 0),
        USB_LAN_REQ_SET_REGS, USB_LAN_REQT_WRITE,
        indx, 0, data, size, 500);
}

static void disable_net_traffic(const struct eth_device *nic)
{
    u8 cr=0; //Coverity CID:105707
    get_registers(nic, CR, 1, &cr);
    cr &= 0xf3;
    set_registers(nic, CR, 1, &cr);
}

static void rtl8150_disable(struct eth_device *nic)
{
    netif_stop_queue(nic);
    disable_net_traffic(nic);
}

static int rtl8150_reset(const struct eth_device *nic)
{
    u8 data = 0x11;
    unsigned long i = HZ;
    set_registers(nic, CR, 1, &data);
    do {
        get_registers(nic, CR, 1, &data);
    } while ((data & 0x11) && --i);
    //  wait_ms(3000);
    //printf("data:%x\n",data);
    return (i > 0) ? 1 : 0;
}

static int enable_net_traffic(const struct eth_device *nic)
{
    u8 cr, tcr, rcr, msr;

    DEBUGFUNC();

    /* RCR bit7=1 attach Rx info at the end;  =0 HW CRC (which is broken) */
    rcr = 0x9e;
    tcr = 0xd8;         //windows RTL driver set to 0x18
    cr = 0x0c;
    //	if (!(rcr & 0x80))
    //		set_bit(USB_LAN_HW_CRC, &nic->flags);

    set_registers(nic, RCR, 1, &rcr);
    set_registers(nic, TCR, 1, &tcr);
    set_registers(nic, CR, 1, &cr);
    get_registers(nic, MSR, 1, &msr);

	return 0;
}

static void set_ethernet_addr(struct eth_device *nic)
{
    u8 node_id[6]={0};

    get_registers(nic, IDR, sizeof(node_id), node_id);
    memcpy(nic->enetaddr, node_id, sizeof(node_id));
}

/**************************************************************************
POLL - Wait for a frame
***************************************************************************/
static int
rtl8150_rx(struct eth_device *nic)
{
    void *usb_buffer;
    int datalen;

    usb_buffer=(void*)&netbuf[0];
    usb_bulk_transfer_in((nic->udev),usb_buffer, RTL8150_MTU,&datalen);

    memcpy((uchar *)packet,(usb_buffer),datalen);
#ifdef USB_LAN_DEBUG
    dump_pkt((uchar *)packet, datalen);
#endif
    NetReceive((uchar *)packet, datalen);
    return 1;
}

/**************************************************************************
TRANSMIT - Transmit a frame
***************************************************************************/
static int
rtl8150_tx(struct eth_device *nic, volatile void *packet, int length)
{
    void *usb_buffer;

    usb_buffer=(void*)&netbuf[0];
    memcpy(usb_buffer,(void *)packet,length);

    while (length < 60)         //padding to 60 bytes
    {
        *((u8*)packet+length)=0;
        length++;
    }

#ifdef USB_LAN_DEBUG
    dump_pkt(usb_buffer, length);
#endif
    usb_bulk_transfer_out( nic->udev,usb_buffer, length);
    return 1;
}

static int
rtl8150_open(struct eth_device *nic, bd_t * bis)
{
    DEBUGFUNC();

    rtl8150_reset(nic);
    enable_net_traffic(nic);
    return 1;
}

/**************************************************************************
INIT - set up ethernet interface(s)
***************************************************************************/
int rtl8150_init(struct eth_device *nic)
{
    DEBUGFUNC();

    nic->init = rtl8150_open;
    nic->recv = rtl8150_rx;
    nic->send = rtl8150_tx;
    nic->halt = rtl8150_disable;

    if (!rtl8150_reset(nic)) {
        printf("rtl8150 - device reset failed \n");
    }
    set_ethernet_addr(nic);
    return 1;
}

