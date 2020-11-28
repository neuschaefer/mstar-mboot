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

enum pegasus_registers {
	EthCtrl0 = 0,
	EthCtrl1 = 1,
	EthCtrl2 = 2,
	EthID = 0x10,
	Reg1d = 0x1d,
	EpromOffset = 0x20,
	EpromData = 0x21,	/* 0x21 low, 0x22 high byte */
	EpromCtrl = 0x23,
	PhyAddr = 0x25,
	PhyData = 0x26, 	/* 0x26 low, 0x27 high byte */
	PhyCtrl = 0x28,
	UsbStst = 0x2a,
	EthTxStat0 = 0x2b,
	EthTxStat1 = 0x2c,
	EthRxStat = 0x2d,
	WakeupControl = 0x78,
	Reg7b = 0x7b,
	Gpio0 = 0x7e,
	Gpio1 = 0x7f,
	Reg81 = 0x81,
};

#define	PEGASUS_REQT_READ	    (0xc0)
#define	PEGASUS_REQT_WRITE	    (0x40)
#define	PEGASUS_REQ_GET_REGS	(0xf0)
#define	PEGASUS_REQ_SET_REGS	(0xf1)

#define	DEFAULT_GPIO_RESET	    (0x24)
#define	DEFAULT_GPIO_SET	    (0x26)

#define	PEGASUS_MTU             (1536)
#define	REG_TIMEOUT		        (100)

unsigned char netbuf[PEGASUS_MTU]  __attribute__ ((aligned (128)));

/* NIC specific static variables go here */
static char packet[2096];

extern void __inline__ wait_ms(unsigned long ms);
extern int usb_bulk_transfer_in(struct usb_device *dev,
			void *data, int len,int *transdata);
extern int usb_bulk_transfer_out(struct usb_device *dev,
			void *data, int len);

/**************************************************************************
Pegasus Operations
***************************************************************************/
static int get_registers(struct eth_device *nic, u16 reg, u16 size, void *data)
{
	return usb_control_msg(nic->udev, usb_rcvctrlpipe(nic->udev, 0),
                               PEGASUS_REQ_GET_REGS, PEGASUS_REQT_READ,
                               0, reg, data, size, 500);
}

static int set_registers(const struct eth_device *nic, u16 reg, u16 size, void *data)
{
	return usb_control_msg(nic->udev, usb_sndctrlpipe(nic->udev, 0),
                               PEGASUS_REQ_SET_REGS, PEGASUS_REQT_WRITE,
                               0, reg, (void *)data, size, 500);
}

static int set_register(const struct eth_device *nic, u16 reg, u8 data)
{
	return usb_control_msg(nic->udev, usb_sndctrlpipe(nic->udev, 0),
                               PEGASUS_REQ_SET_REGS, PEGASUS_REQT_WRITE,
                               data, reg, &data, 1, 500);
}

static void disable_net_traffic(const struct eth_device *nic)
{
    u8 tmp = 0;

    DEBUGFUNC();
    set_registers(nic, EthCtrl0, 2, &tmp);
}

static void pegasus_disable(struct eth_device *nic)
{
    DEBUGFUNC();

    netif_stop_queue(nic);
    disable_net_traffic(nic);
}

static inline int
reset_mac(struct eth_device *nic)
{
	u8 data = 0x8;
	int i;

    DEBUGFUNC();
	set_register(nic, EthCtrl1, 0x08);
	for (i = 0; i < REG_TIMEOUT; i++)
	{
		get_registers(nic, EthCtrl1, 1, &data);
		if (~data & 0x08)
		{
			set_register(nic, Gpio1, 0x26);
			set_register(nic, Gpio0, 0x24);
			set_register(nic, Gpio0, DEFAULT_GPIO_SET);
			break;
		}
	}
	if (i == REG_TIMEOUT)
		return 0;

	return 1;
}

static int pegasus_reset(struct eth_device *nic)
{
    DEBUGFUNC();

    if (!reset_mac(nic))
    {
        USB_LAN_ERR("Reset mac error\n");
        return 0;
    }
    set_register(nic, Reg1d, 0);
    //reset phy
    set_register(nic, Reg7b, 1);
    wait_ms(100);
    //stop reset phy
    set_register(nic, Reg7b, 2);
    return 1;
}

static int enable_net_traffic(const struct eth_device *nic)
{
    u8 data[4] = {0xC9, 0 | 0x20 /* set full duplex */ | 0x10 /* set 100 Mbps */, 0x01 /* loopback = 0x09, otherwise = 0x01 */};

    DEBUGFUNC();

    return set_registers(nic, EthCtrl0, 3, data);
}

static void set_ethernet_addr(struct eth_device *nic)
{
    u8 node_id[6]={0};

    DEBUGFUNC();
    memset(node_id, 0, sizeof(node_id));
    get_registers(nic, EthID, sizeof(node_id), node_id);
    memcpy(nic->enetaddr, node_id, sizeof(node_id));

    USB_LAN_ERR("net addr:%x-%x-%x-%x-%x-%x\n",nic->enetaddr[0],nic->enetaddr[1],nic->enetaddr[2],nic->enetaddr[3],nic->enetaddr[4],nic->enetaddr[5]);
}

/**************************************************************************
POLL - Wait for a frame
***************************************************************************/
static int
pegasus_rx(struct eth_device *nic)
{
    void *usb_buffer;
    int datalen;

    DEBUGFUNC();

    usb_buffer=(void*)&netbuf[0];
    usb_bulk_transfer_in((nic->udev),usb_buffer, PEGASUS_MTU,&datalen);

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
pegasus_tx(struct eth_device *nic, volatile void *packet, int length)
{
    void *usb_buffer;

    usb_buffer=(void*)&netbuf[0];
	memcpy(usb_buffer+2,(void *)packet,length);
	//@FIXME:add 2 dummy bytes to avoid USB LAN ignore it
    length +=2;
    while (length < 60)         //padding to 60 bytes
    {
        *((u8*)usb_buffer+length)=0;
		length++;
	}

#ifdef USB_LAN_DEBUG
    dump_pkt(usb_buffer, length);
#endif
    usb_bulk_transfer_out( nic->udev,usb_buffer, length);
	return 1;
}

static int
pegasus_open(struct eth_device *nic, bd_t * bis)
{
    u8 enet_addr[6];
    DEBUGFUNC();

    memcpy(enet_addr, nic->enetaddr, 6);
    set_registers(nic, EthID, 6, enet_addr);
	enable_net_traffic(nic);
	return 1;
}

/**************************************************************************
INIT - set up ethernet interface(s)
***************************************************************************/
int pegasus_init(struct eth_device *nic)
{
    DEBUGFUNC();

    nic->init = pegasus_open;
    nic->recv = pegasus_rx;
    nic->send = pegasus_tx;
    nic->halt = pegasus_disable;

    set_register(nic, EpromCtrl, 0);
    set_register(nic, EpromOffset, 0x04);
    set_register(nic, EpromCtrl, 2);
    set_register(nic, EpromCtrl, 0);
    set_register(nic, EpromData, 0);

    if (!pegasus_reset(nic))
    {
		USB_LAN_ERR("pegasus - device reset failed \n");
		return 0;
	}

    set_register(nic, 0x80, 0xc0);
    set_register(nic, 0x83, 0xff);
    set_register(nic, 0x84, 0x01);
    set_register(nic, Reg81, 0x02);

 	set_ethernet_addr(nic);
 	return 1;
}

