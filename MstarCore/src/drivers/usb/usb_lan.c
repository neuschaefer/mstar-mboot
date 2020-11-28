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

extern int rtl8150_init(struct eth_device *nic);
extern int pegasus_init(struct eth_device *nic);
extern int ax88772a_init(struct eth_device *nic);

struct eth_device *gnic=NULL;
typedef int  (*__entry) (struct eth_device*);

struct init_info {
	unsigned short idVendor;
	unsigned short idProduct;
    __entry init;
};

struct init_info ctrlTbl[] =
{
	{VENDOR_ID_REALTEK, PRODUCT_ID_RTL8150, rtl8150_init}
	,{VENDOR_ID_ADMTEK, PRODUCT_ID_ADM8515, pegasus_init}
	,{VENDOR_ID_ASIX, PRODUCT_ID_AX88772A, ax88772a_init}
};

#define USBLAN_MAX_INFOTBL  (sizeof(ctrlTbl)/sizeof(struct init_info))

static int lookup_ctrlTbl(u16 idVendor, u16 idProduct)
{
    u8 idx = 0;

    for(; idx < USBLAN_MAX_INFOTBL; idx++)
    {
        if (idVendor == ctrlTbl[idx].idVendor
            && idProduct == ctrlTbl[idx].idProduct)
            break;
    }
    return idx;
}

void usb_lan_release(void)
{
    if (gnic)
        free(gnic);
}

void dump_pkt(u8 *pkt, u32 len)
{
    u32 i = 0;

    DEBUGFUNC();

    for (; i< len; i++)
    {
        if (i%0x10 == 0)
            printf("\n%x: ", (u32)pkt);

        if (*pkt < 0x10)
            printf("0%x ", *pkt);
        else
            printf("%x ", *pkt);
        pkt++;
    }

    printf("\n");
}

/**************************************************************************
PROBE - Look for an adapter, this routine's visible to the outside
You should omit the last argument struct pci_device * for a non-PCI NIC
***************************************************************************/
int
usb_lan_initialize(struct usb_device *udev)
{
	struct usb_lan_hw *hw = NULL;
	struct eth_device *nic = NULL;
	u8 ret = 1;

    DEBUGFUNC();

	nic = (struct eth_device *) malloc(sizeof (struct eth_device));
	if (!nic) {
	    return -ENOMEM;
	}
    hw = (struct usb_lan_hw *) malloc(sizeof (struct usb_lan_hw));
	if (!hw) {
        free(nic);
	    return -ENOMEM;
	}

    gnic=nic;
    nic->udev = udev;
	nic->priv = hw;

    USB_LAN_ERR("vendor:%x product:%x\n",nic->udev->descriptor.idVendor, nic->udev->descriptor.idProduct);
    hw->tblIdx = lookup_ctrlTbl(nic->udev->descriptor.idVendor, nic->udev->descriptor.idProduct);
    if (USBLAN_MAX_INFOTBL == hw->tblIdx)
    {
        USB_LAN_ERR("Can't find usb lan dev!!\n");
        free(nic);
        free(hw);
         return -ENXIO;
    }

    USB_LAN_DBG("Go to fxp:%x\n", ctrlTbl[hw->tblIdx].init);
    //printf cause fxp crash
#if 0
    ret = ctrlTbl[hw->tblIdx].init(nic);
#else
    if (hw->tblIdx==0)
        ret = rtl8150_init(nic);
    else if (hw->tblIdx==1)
        ret = pegasus_init(nic);
    else
        ret = ax88772a_init(nic);

#endif

    if (!ret)
    {
        USB_LAN_ERR("init failed device:%u\n", hw->tblIdx);
        free(nic);
        free(hw);        
        return 0;
    }
	eth_register(nic);

	uEMAC_start = 0;
	uUSB_LAN_start = 1;
    free(nic);
    free(hw);    
	return 1;
}

