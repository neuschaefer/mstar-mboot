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


#include <common.h>
#ifdef  CONFIG_USB_EHCI
#include <usb.h>
#if defined(CONFIG_JANUS) || defined(CONFIG_MARIA10)
#include <asm-aeon/io.h>
#else
#if defined(__ARM__)
#include <asm/io.h>
#else
#include <asm/io.h>
#endif
#endif
#include "ehci_usb.h"

#if defined(CONFIG_JANUS) || defined(CONFIG_MARIA10)
    #define HW_BASE         0xa0200000
#elif defined(__ARM__)
    #define HW_BASE          0x1f200000
#else
    #define HW_BASE         0xbf200000
#endif

//static int root_hub_devnum = 0;
static struct usb_port_status rh_status = { 0 };/* root hub port status */

#ifdef SL811_DEBUG
    #define PDEBUG(level, fmt, args...) \
        if (debug >= (level)) printf("[%s:%d] " fmt, \
        __PRETTY_FUNCTION__, __LINE__ , ## args)
#else
    #define PDEBUG(level, fmt, args...) do {} while(0)
#endif

#if 0
static int titania_rh_submit_urb(struct usb_device *usb_dev, unsigned long pipe,
                   void *data, int buf_len, struct devrequest *cmd);
#endif
extern int UsbPortSelect;

void usb_bc_enable(u32 utmi_base, u32 bc_base, u8 enable)
{
	if (enable) {
		//printf("BC enable \n");
		writeb(readb((void *)(utmi_base+(0x1*2-1))) | 0x40, (void *)(utmi_base+(0x1*2-1)));  //IREF_PDN=1��b1. (utmi+0x01[6] )
		writeb(readb((void *)(bc_base+(0x3*2-1))) | 0x40, (void *)(bc_base+(0x3*2-1)));  // [6]= reg_host_bc_en
		writeb(readb((void *)(bc_base+(0xc*2))) | 0x40, (void *)(bc_base+(0xc*2)));  // [6]= reg_into_host_bc_sw_tri
		writew(0x0000, (void *)(bc_base));  // [15:0] = bc_ctl_ov_en
		writeb(readb((void *)(bc_base+(0xa*2))) | 0x80, (void *)(bc_base+(0xa*2)));  // [7]=reg_bc_switch_en
	}
	else {
		// disable BC
		//printf("BC disable \n");
		writeb(readb((void *)(bc_base+(0xc*2))) & (~0x40), (void *)(bc_base+(0xc*2)));  // [6]= reg_into_host_bc_sw_tri
		writeb(readb((void *)(bc_base+(0x3*2-1))) & (~0x40), (void *)(bc_base+(0x3*2-1)));  // [6]= reg_host_bc_en
		writeb(readb((void *)(utmi_base+(0x1*2-1))) & (~0x40), (void *)(utmi_base+(0x1*2-1)));  //IREF_PDN=1��b1. (utmi+0x01[6] )
	}
}

#if defined(__ARM__)
static U32 miu0_bus_base_addr;
static U32 miu1_bus_base_addr;
#if defined(MIU2_BUS_BASE_ADDR)
static U32 miu2_bus_base_addr;
#endif

U32 VA2PA(U32 u32_DMAAddr)
{
    //printf("VA:0x%x ->", u32_DMAAddr);
    #if 1
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
    #else
    if((u32_DMAAddr>=MIU0_BUS_BASE_ADDR)&&(u32_DMAAddr<(MIU0_BUS_BASE_ADDR+MIU0_SIZE)))
    {
        u32_DMAAddr -= MIU0_BUS_BASE_ADDR;
        u32_DMAAddr += MIU0_PHY_BASE_ADDR;
    }
    else if((u32_DMAAddr>= MIU1_BUS_BASE_ADDR)&&(u32_DMAAddr<(MIU1_BUS_BASE_ADDR+MIU1_SIZE)))
    {
        u32_DMAAddr -= MIU1_BUS_BASE_ADDR;
        u32_DMAAddr |= MIU1_PHY_BASE_ADDR;
    }
    else
        u32_DMAAddr = 0xFFFFFFFF;
    #endif
    //printf("PA:0x%x\n", u32_DMAAddr);
    return  u32_DMAAddr;
}

U32 PA2VA(U32 u32_DMAAddr)
{
    //printf("PA:0x%x ->", u32_DMAAddr);
    #if 1
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
    u32_DMAAddr=MsOS_PA2KSEG1(u32_DMAAddr);

    #else
    if((u32_DMAAddr>=MIU0_PHY_BASE_ADDR)&&(u32_DMAAddr<(MIU0_PHY_BASE_ADDR+MIU0_SIZE)))
    {
        u32_DMAAddr -= MIU0_PHY_BASE_ADDR;
        u32_DMAAddr += MIU0_BUS_BASE_ADDR;
    }
    else if((u32_DMAAddr>= MIU1_PHY_BASE_ADDR)&&(u32_DMAAddr<(MIU1_PHY_BASE_ADDR+MIU1_SIZE)))
    {
        u32_DMAAddr -= MIU1_PHY_BASE_ADDR;
        u32_DMAAddr |= MIU1_BUS_BASE_ADDR;
    }
    else
        u32_DMAAddr = 0xFFFFFFFF;
    #endif
    //printf("VA:0x%x\n", u32_DMAAddr);
    return  u32_DMAAddr;
}
#endif

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

static void TV_usb_init(void)
{
#if defined(ENABLE_USB_NEW_MIU_SEL)
    MIU_select_setting_ehc(HW_BASE+0x700*2);
#endif

//===========================================================================
    writeb(0x0A, (void*) (HW_BASE+0x700*2)); // Disable MAC initial suspend, Reset UHC
    writeb(0x28, (void*) (HW_BASE+0x700*2)); // Release UHC reset, enable UHC XIU function

    writeb(readb((void*)HW_BASE+(0x3A80+0x3C)*2) | 0x01, (void*) (HW_BASE+(0x3A80+0x3C)*2)); // set CA_START as 1
    mdelay(10);

    writeb(readb((void*)HW_BASE+(0x3A80+0x3C)*2) & ~0x01, (void*) (HW_BASE+(0x3A80+0x3C)*2)); // release CA_START
#if (ENABLE_KAISER)
    writeb(readb((void*)HW_BASE+(0x3a80+0x10)*2) | 0x40, (void*) (HW_BASE+(0x3a80+0x10)*2)); // bit<6> for monkey test and HS current
#endif
    while ((readb((void*)HW_BASE+(0x3A80+0x3C)*2) & 0x02) == 0);    // polling bit <1> (CA_END)

#if defined(CONFIG_KRONUS) || (ENABLE_KAISER)
    writeb(readb((void*)(HW_BASE+(0x3A80+0x0b)*2-1) ) |0x20, (void*) (HW_BASE+(0x3A80+0x0b)*2-1)); // dp dm swap
#endif

    writeb(readb((void*)HW_BASE+(0x700+0x02)*2) & ~0x03, (void*) (HW_BASE+(0x700+0x02)*2)); //UHC select enable
    writeb(readb((void*)HW_BASE+(0x700+0x02)*2) | 0x01, (void*) (HW_BASE+(0x700+0x02)*2)); //UHC select enable

    writeb(readb((void*)HW_BASE+(0x2400+0x40)*2) & ~0x10, (void*) (HW_BASE+(0x2400+0x40)*2)); //0: VBUS On.
    mdelay(1);    // delay 1ms
    writeb(readb((void*)HW_BASE+(0x2400+0x40)*2) | 0x08, (void*) (HW_BASE+(0x2400+0x40)*2)); // Active HIGH
    mdelay(1);    // delay 1ms

    writeb((readb((void*)HW_BASE+(0x3a80+0x06)*2) & 0x9F) | 0x40, (void*) (HW_BASE+(0x3a80+0x06)*2)); //reg_tx_force_hs_current_enable

    writeb(readb((void*)HW_BASE+(0x3a80+0x03)*2-1) | 0x28, (void*) (HW_BASE+(0x3a80+0x03)*2-1)); //Disconnect window select
    writeb(readb((void*)HW_BASE+(0x3a80+0x03)*2-1) & 0xef, (void*) (HW_BASE+(0x3a80+0x03)*2-1)); //Disconnect window select
    writeb(readb((void*)HW_BASE+(0x3a80+0x07)*2-1) & 0xfd, (void*) (HW_BASE+(0x3a80+0x07)*2-1)); //Disable improved CDR
#if (ENABLE_EDISON) || (ENABLE_KAISER) || (ENABLE_EINSTEIN) || \
	(ENABLE_NAPOLI) || (ENABLE_KENYA) || (ENABLE_CLIPPERS) || \
	(ENABLE_KERES) || (ENABLE_MONACO) ||  (ENABLE_MUJI) || \
	(ENABLE_CELTICS)
    writeb(readb((void*)HW_BASE+(0x3a80+0x08)*2) | 0x08, (void*) (HW_BASE+(0x3a80+0x08)*2)); // bit<3> for 240's phase as 120's clock set 1, bit<4> for 240Mhz in mac 0 for faraday 1 for etron
#elif (ENABLE_EIFFEL) || (ENABLE_KERES)
    writeb(readb((void*)HW_BASE+(0x3a80+0x08)*2) & ~0x08, (void*) (HW_BASE+(0x3a80+0x08)*2)); // bit<3> special for Eiffel analog LIB issue
#endif
    writeb(readb((void*)HW_BASE+(0x3a80+0x09)*2-1) |0x81, (void*) (HW_BASE+(0x3a80+0x09)*2-1)); // UTMI RX anti-dead-loc, ISI effect improvement
#if (ENABLE_KERES)
    writeb(readb((void*)HW_BASE+(0x3a80+0x0b)*2-1) & ~0x80, (void*) (HW_BASE+(0x3a80+0x0b)*2-1)); // TX timing select latch path
#else
    writeb(readb((void*)HW_BASE+(0x3a80+0x0b)*2-1) |0x80, (void*) (HW_BASE+(0x3a80+0x0b)*2-1)); // TX timing select latch path
#endif
    writeb(readb((void*)HW_BASE+(0x3a80+0x15)*2-1) |0x20, (void*) (HW_BASE+(0x3a80+0x15)*2-1)); // Chirp signal source select
#if (ENABLE_AGATE) || (ENABLE_EAGLE) || (ENABLE_EDISON) || \
	(ENABLE_EIFFEL) || (ENABLE_NIKE) || (ENABLE_NADAL) || \
	(ENABLE_KAISER) || (ENABLE_NUGGET) || (ENABLE_EINSTEIN) || \
	(ENABLE_NIKON) || (ENABLE_NAPOLI) || (ENABLE_KENYA) || \
	(ENABLE_MADISON) || (ENABLE_MIAMI) || (ENABLE_CLIPPERS) || \
	(ENABLE_KERES) || (ENABLE_MONACO) ||  (ENABLE_MUJI) || \
	(ENABLE_CELTICS)
    writeb(readb((void*)HW_BASE+(0x3a80+0x15)*2-1) |0x40, (void*) (HW_BASE+(0x3a80+0x15)*2-1)); // change to 55 interface
#endif

#if (ENABLE_AMBER3) || (ENABLE_EAGLE)
    /* for early 40nm setting */
    writeb(readb((void*)HW_BASE+(0x3a80+0x2c)*2) |0x98, (void*) (HW_BASE+(0x3a80+0x2c)*2));
    writeb(readb((void*)HW_BASE+(0x3a80+0x2d)*2-1) |0x02, (void*) (HW_BASE+(0x3a80+0x2d)*2-1));
    writeb(readb((void*)HW_BASE+(0x3a80+0x2e)*2) |0x10, (void*) (HW_BASE+(0x3a80+0x2e)*2));
    writeb(readb((void*)HW_BASE+(0x3a80+0x2f)*2-1) |0x01, (void*) (HW_BASE+(0x3a80+0x2f)*2-1));
#elif (ENABLE_KENYA)
    writeb(readb((void*)HW_BASE+(0x3a80+0x2c)*2) |0x90, (void*) (HW_BASE+(0x3a80+0x2c)*2));
    writeb(readb((void*)HW_BASE+(0x3a80+0x2d)*2-1) |0x02, (void*) (HW_BASE+(0x3a80+0x2d)*2-1));
    writeb(readb((void*)HW_BASE+(0x3a80+0x2f)*2-1) |0x81, (void*) (HW_BASE+(0x3a80+0x2f)*2-1));
#else    /* for 55nm and later 40nm with 55nm setting */
    writeb(readb((void*)HW_BASE+(0x3a80+0x2c)*2) |0x10, (void*) (HW_BASE+(0x3a80+0x2c)*2));
    writeb(readb((void*)HW_BASE+(0x3a80+0x2d)*2-1) |0x02, (void*) (HW_BASE+(0x3a80+0x2d)*2-1));
    writeb(readb((void*)HW_BASE+(0x3a80+0x2f)*2-1) |0x81, (void*) (HW_BASE+(0x3a80+0x2f)*2-1));
#endif

#if (ENABLE_KENYA)
    writeb(readb((void*)HW_BASE+(0x700+0x0a)*2) | 0x40, (void*) (HW_BASE+(0x700+0x0a)*2)); //enable PV2MI bridge ECO
#endif

#if (ENABLE_EIFFEL) || (ENABLE_NIKE) || (ENABLE_NADAL) || \
	(ENABLE_NUGGET) || (ENABLE_EINSTEIN) || (ENABLE_NIKON) || \
	(ENABLE_NAPOLI) || (ENABLE_MADISON) || (ENABLE_MIAMI) || \
	(ENABLE_CLIPPERS) || (ENABLE_MONACO) ||  (ENABLE_MUJI) || \
	(ENABLE_CELTICS)
    usb_bc_enable(HW_BASE+0x3a80*2, HW_BASE+0x23600*2, FALSE);
#elif (ENABLE_KAISER)
    usb_bc_enable(HW_BASE+0x3a80*2, HW_BASE+0x22f00*2, FALSE);
#elif (ENABLE_KENYA)
    usb_bc_enable(HW_BASE+0x3a80*2, HW_BASE+0x205e0*2, FALSE);
#elif (ENABLE_KERES)
    usb_bc_enable(HW_BASE+0x3a80*2, HW_BASE+0x13700*2, FALSE);
#endif
//===========================================================================
}
#if defined(ENABLE_SECOND_EHC)
void TV_usb_init_port1(void)
{
#if defined(CONFIG_KRONUS)
    #define UTMI1_BASE  0x2A00
    #define UHC1_BASE   0x10300
    #define USBC1_BASE  0x10200
#else
    #define UTMI1_BASE  0x3A00
    #define UHC1_BASE   0xD00
    #define USBC1_BASE  0x780
#endif

#if defined(ENABLE_USB_NEW_MIU_SEL)
    MIU_select_setting_ehc(HW_BASE+USBC1_BASE*2);
#endif

    writeb(0x0A, (void*) (HW_BASE+USBC1_BASE*2)); // Disable MAC initial suspend, Reset UHC
    writeb(0x28, (void*) (HW_BASE+USBC1_BASE*2)); // Release UHC reset, enable UHC XIU function

    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x3C)*2) | 0x01, (void*) (HW_BASE+(UTMI1_BASE+0x3C)*2)); // set CA_START as 1
    mdelay(10);

    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x3C)*2) & ~0x01, (void*) (HW_BASE+(UTMI1_BASE+0x3C)*2)); // release CA_START
#if (ENABLE_KAISER)
    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x10)*2) | 0x40, (void*) (HW_BASE+(UTMI1_BASE+0x10)*2)); // bit<6> for monkey test and HS current
#endif

    while ((readb((void*)HW_BASE+(UTMI1_BASE+0x3C)*2) & 0x02) == 0)    // polling bit <1> (CA_END)
    ;

    //#if defined(CONFIG_URANUS4)
    //    //for Shire MCP only
    //    writeb(readb((void*)(HW_BASE+(0x3a00+0x0b)*2-1) ) |0x20, (void*) (HW_BASE+(0x3a00+0x0b)*2-1)); // dp dm swap
    //#endif
#if defined(CONFIG_KRONUS) || (ENABLE_KAISER)
    writeb(readb((void*)(HW_BASE+(UTMI1_BASE+0x0b)*2-1) ) |0x20, (void*) (HW_BASE+(UTMI1_BASE+0x0b)*2-1)); // dp dm swap
#endif

    writeb(readb((void*)HW_BASE+(USBC1_BASE+0x02)*2) & ~0x03, (void*) (HW_BASE+(USBC1_BASE+0x02)*2)); //UHC select enable
    writeb(readb((void*)HW_BASE+(USBC1_BASE+0x02)*2) | 0x01, (void*) (HW_BASE+(USBC1_BASE+0x02)*2)); //UHC select enable

    writeb(readb((void*)HW_BASE+(UHC1_BASE+0x40)*2) & ~0x10, (void*) (HW_BASE+(UHC1_BASE+0x40)*2)); //0: VBUS On.
    mdelay(1);    // delay 1ms

    writeb(readb((void*)HW_BASE+(UHC1_BASE+0x40)*2) | 0x08, (void*) (HW_BASE+(UHC1_BASE+0x40)*2)); // Active HIGH
    mdelay(1);    // delay 1ms
    writeb((readb((void*)HW_BASE+(UTMI1_BASE+0x06)*2) & 0x9F) | 0x40, (void*) (HW_BASE+(UTMI1_BASE+0x06)*2)); //reg_tx_force_hs_current_enable

    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x03)*2-1) | 0x28, (void*) (HW_BASE+(UTMI1_BASE+0x03)*2-1)); //Disconnect window select
    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x03)*2-1) & 0xef, (void*) (HW_BASE+(UTMI1_BASE+0x03)*2-1)); //Disconnect window select
    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x07)*2-1) & 0xfd, (void*) (HW_BASE+(UTMI1_BASE+0x07)*2-1)); //Disable improved CDR
#if (ENABLE_EDISON) || (ENABLE_KAISER) || (ENABLE_EINSTEIN) || \
	(ENABLE_NAPOLI) || (ENABLE_KENYA) || (ENABLE_CLIPPERS) || \
	(ENABLE_MONACO) ||  (ENABLE_MUJI) || (ENABLE_CELTICS)
    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x08)*2) | 0x08, (void*) (HW_BASE+(UTMI1_BASE+0x08)*2)); // bit<3> for 240's phase as 120's clock set 1, bit<4> for 240Mhz in mac 0 for faraday 1 for etron
#elif (ENABLE_EIFFEL) || (ENABLE_KERES)
    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x08)*2) & ~0x08, (void*) (HW_BASE+(UTMI1_BASE+0x08)*2)); // bit<3> special for Eiffel analog LIB issue
#endif
    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x09)*2-1) |0x81, (void*) (HW_BASE+(UTMI1_BASE+0x09)*2-1)); // UTMI RX anti-dead-loc, ISI effect improvement
#if (ENABLE_KERES)
    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x0b)*2-1) & ~0x80, (void*) (HW_BASE+(UTMI1_BASE+0x0b)*2-1)); // TX timing select latch path
#else
    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x0b)*2-1) |0x80, (void*) (HW_BASE+(UTMI1_BASE+0x0b)*2-1)); // TX timing select latch path
#endif
    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x15)*2-1) |0x20, (void*) (HW_BASE+(UTMI1_BASE+0x15)*2-1)); // Chirp signal source select
#if (ENABLE_AGATE) || (ENABLE_EAGLE) || (ENABLE_EDISON) || \
	(ENABLE_EIFFEL) || (ENABLE_NIKE) || (ENABLE_NADAL) || \
	(ENABLE_KAISER) || (ENABLE_NUGGET) || (ENABLE_EINSTEIN) || \
	(ENABLE_NIKON) || (ENABLE_NAPOLI) || (ENABLE_KENYA) || \
	(ENABLE_MADISON) || (ENABLE_MIAMI) || (ENABLE_CLIPPERS) || \
	(ENABLE_KERES) || (ENABLE_MONACO) ||  (ENABLE_MUJI) || \
	(ENABLE_CELTICS)
    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x15)*2-1) |0x40, (void*) (HW_BASE+(UTMI1_BASE+0x15)*2-1)); // change to 55 interface
#endif

#if (ENABLE_AMBER3) || (ENABLE_EAGLE)
    /* for early 40nm setting */
    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x2c)*2) |0x98, (void*) (HW_BASE+(UTMI1_BASE+0x2c)*2));
    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x2d)*2-1) |0x02, (void*) (HW_BASE+(UTMI1_BASE+0x2d)*2-1));
    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x2e)*2) |0x10, (void*) (HW_BASE+(UTMI1_BASE+0x2e)*2));
    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x2f)*2-1) |0x01, (void*) (HW_BASE+(UTMI1_BASE+0x2f)*2-1));
#else    /* for 55nm and later 40nm with 55nm setting */
    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x2c)*2) |0x10, (void*) (HW_BASE+(UTMI1_BASE+0x2c)*2));
    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x2d)*2-1) |0x02, (void*) (HW_BASE+(UTMI1_BASE+0x2d)*2-1));
    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x2f)*2-1) |0x81, (void*) (HW_BASE+(UTMI1_BASE+0x2f)*2-1));
#endif

#if (ENABLE_EIFFEL) || (ENABLE_NIKE) || (ENABLE_NADAL) || \
	(ENABLE_NUGGET) || (ENABLE_EINSTEIN) || (ENABLE_NIKON) || \
	(ENABLE_NAPOLI) || (ENABLE_MADISON) || (ENABLE_MIAMI) || \
	(ENABLE_CLIPPERS) || (ENABLE_MONACO) ||  (ENABLE_MUJI) || \
	(ENABLE_CELTICS)
    usb_bc_enable(HW_BASE+UTMI1_BASE*2, HW_BASE+0x23620*2, FALSE);
#elif (ENABLE_KAISER)
    usb_bc_enable(HW_BASE+UTMI1_BASE*2, HW_BASE+0x22f40*2, FALSE);
#elif (ENABLE_KENYA)
    usb_bc_enable(HW_BASE+UTMI1_BASE*2, HW_BASE+0x205c0*2, FALSE);
#elif (ENABLE_KERES)
    usb_bc_enable(HW_BASE+UTMI1_BASE*2, HW_BASE+0x13740*2, FALSE);
#endif
//===========================================================================
}
#endif
#if defined(ENABLE_THIRD_EHC)
void TV_usb_init_port2(void)
{
#if defined(CONFIG_URANUS4) || defined(CONFIG_KAISERIN) || (ENABLE_KAISER)
    #define UTMI2_BASE  0x2A00
    #define UHC2_BASE   0x10300
    #define USBC2_BASE  0x10200
#else
    #define UTMI2_BASE  0x3900
    #define UHC2_BASE   0x13900
    #define USBC2_BASE  0x13800
#endif

#if defined(ENABLE_USB_NEW_MIU_SEL)
    MIU_select_setting_ehc(HW_BASE+USBC2_BASE*2);
#endif

    writeb(0x0A, (void*)(HW_BASE+USBC2_BASE*2)); // Disable MAC initial suspend, Reset UHC
    writeb(0x28, (void*)(HW_BASE+USBC2_BASE*2)); // Release UHC reset, enable UHC XIU function

    writeb(readb((void*)(HW_BASE+(UTMI2_BASE+0x3C)*2) ) | 0x01, (void*) (HW_BASE+(UTMI2_BASE+0x3C)*2)); // set CA_START as 1
    mdelay(10);

    writeb(readb((void*)(HW_BASE+(UTMI2_BASE+0x3C)*2) ) & ~0x01, (void*) (HW_BASE+(UTMI2_BASE+0x3C)*2)); // release CA_START

#if (ENABLE_KAISER)
    printf("p2 Mbs\n");
    writeb(readb((void*)HW_BASE+(UTMI2_BASE+0x10)*2) | 0x40, (void*) (HW_BASE+(UTMI2_BASE+0x10)*2)); // bit<6> for monkey test and HS current
#endif

    while ((readb((void*)(HW_BASE+(UTMI2_BASE+0x3C)*2) ) & 0x02) == 0);    // polling bit <1> (CA_END)

#if defined(CONFIG_URANUS4)
    writeb(readb((void*)(HW_BASE+(UTMI2_BASE+0x0b)*2-1) ) |0x20, (void*) (HW_BASE+(UTMI2_BASE+0x0b)*2-1)); // dp dm swap
#endif

    writeb(readb((void*)(HW_BASE+(USBC2_BASE+0x02)*2) ) & ~0x03, (void*) (HW_BASE+(USBC2_BASE+0x02)*2)); //UHC select enable
    writeb(readb((void*)(HW_BASE+(USBC2_BASE+0x02)*2) ) | 0x01, (void*) (HW_BASE+(USBC2_BASE+0x02)*2)); //UHC select enable

    writeb(readb((void*)(HW_BASE+(UHC2_BASE+0x40)*2) ) & ~0x10, (void*) (HW_BASE+(UHC2_BASE+0x40)*2)); //0: VBUS On.
    mdelay(1);    // delay 1ms

    writeb(readb((void*)(HW_BASE+(UHC2_BASE+0x40)*2) ) | 0x08, (void*) (HW_BASE+(UHC2_BASE+0x40)*2)); // Active HIGH
    mdelay(1);    // delay 1ms
    writeb((readb((void*)(HW_BASE+(UTMI2_BASE+0x06)*2) ) & 0x9F) | 0x40, (void*) (HW_BASE+(UTMI2_BASE+0x06)*2)); //reg_tx_force_hs_current_enable

    writeb(readb((void*)(HW_BASE+(UTMI2_BASE+0x03)*2-1) ) | 0x28, (void*) (HW_BASE+(UTMI2_BASE+0x03)*2-1)); //Disconnect window select
    writeb(readb((void*)(HW_BASE+(UTMI2_BASE+0x03)*2-1) ) & 0xef, (void*) (HW_BASE+(UTMI2_BASE+0x03)*2-1)); //Disconnect window select
    writeb(readb((void*)(HW_BASE+(UTMI2_BASE+0x07)*2-1) ) & 0xfd, (void*) (HW_BASE+(UTMI2_BASE+0x07)*2-1)); //Disable improved CDR
#if (ENABLE_EDISON) || (ENABLE_KAISER) || (ENABLE_EINSTEIN) || \
	(ENABLE_NAPOLI) || (ENABLE_CLIPPERS) || (ENABLE_MONACO) || \
	(ENABLE_MUJI) || (ENABLE_CELTICS)
    writeb(readb((void*)(HW_BASE+(UTMI2_BASE+0x08)*2) ) | 0x08, (void*) (HW_BASE+(UTMI2_BASE+0x08)*2)); // bit<3> for 240's phase as 120's clock set 1, bit<4> for 240Mhz in mac 0 for faraday 1 for etron
#elif (ENABLE_EIFFEL)
    writeb(readb((void*)HW_BASE+(UTMI2_BASE+0x08)*2) & ~0x08, (void*) (HW_BASE+(UTMI2_BASE+0x08)*2)); // bit<3> special for Eiffel analog LIB issue
#endif
    writeb(readb((void*)(HW_BASE+(UTMI2_BASE+0x09)*2-1) ) |0x81, (void*) (HW_BASE+(UTMI2_BASE+0x09)*2-1)); // UTMI RX anti-dead-loc, ISI effect improvement
    writeb(readb((void*)(HW_BASE+(UTMI2_BASE+0x0b)*2-1) ) |0x80, (void*) (HW_BASE+(UTMI2_BASE+0x0b)*2-1)); // TX timing select latch path
    writeb(readb((void*)(HW_BASE+(UTMI2_BASE+0x15)*2-1) ) |0x20, (void*) (HW_BASE+(UTMI2_BASE+0x15)*2-1)); // Chirp signal source select
#if (ENABLE_AGATE) || (ENABLE_EAGLE) || (ENABLE_EDISON) || \
	(ENABLE_EIFFEL) || (ENABLE_NIKE) || (ENABLE_NADAL) || \
	(ENABLE_KAISER) || (ENABLE_EINSTEIN) || (ENABLE_NIKON) || \
	(ENABLE_NAPOLI) || (ENABLE_MADISON) || (ENABLE_MIAMI) || \
	(ENABLE_CLIPPERS) || (ENABLE_MONACO) ||  (ENABLE_MUJI) || \
	(ENABLE_CELTICS)
    writeb(readb((void*)(HW_BASE+(UTMI2_BASE+0x15)*2-1) ) |0x40, (void*) (HW_BASE+(UTMI2_BASE+0x15)*2-1)); // change to 55 interface
#endif

#if (ENABLE_AMBER3) || (ENABLE_EAGLE)
    /* for early 40nm setting */
    writeb(readb((void*)(HW_BASE+(UTMI2_BASE+0x2c)*2) ) |0x98, (void*) (HW_BASE+(UTMI2_BASE+0x2c)*2));
    writeb(readb((void*)(HW_BASE+(UTMI2_BASE+0x2d)*2-1) ) |0x02, (void*) (HW_BASE+(UTMI2_BASE+0x2d)*2-1));
    writeb(readb((void*)(HW_BASE+(UTMI2_BASE+0x2e)*2) ) |0x10, (void*) (HW_BASE+(UTMI2_BASE+0x2e)*2));
    writeb(readb((void*)(HW_BASE+(UTMI2_BASE+0x2f)*2-1) ) |0x01, (void*) (HW_BASE+(UTMI2_BASE+0x2f)*2-1));
#elif (ENABLE_KENYA)
    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x2c)*2) |0x90, (void*) (HW_BASE+(UTMI1_BASE+0x2c)*2));
    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x2d)*2-1) |0x02, (void*) (HW_BASE+(UTMI1_BASE+0x2d)*2-1));
    writeb(readb((void*)HW_BASE+(UTMI1_BASE+0x2f)*2-1) |0x81, (void*) (HW_BASE+(UTMI1_BASE+0x2f)*2-1));
#else    /* for 55nm and later 40nm with 55nm setting */
    writeb(readb((void*)(HW_BASE+(UTMI2_BASE+0x2c)*2) ) |0x10, (void*) (HW_BASE+(UTMI2_BASE+0x2c)*2));
    writeb(readb((void*)(HW_BASE+(UTMI2_BASE+0x2d)*2-1) ) |0x02, (void*) (HW_BASE+(UTMI2_BASE+0x2d)*2-1));
    writeb(readb((void*)(HW_BASE+(UTMI2_BASE+0x2f)*2-1) ) |0x81, (void*) (HW_BASE+(UTMI2_BASE+0x2f)*2-1));
#endif

#if (ENABLE_KENYA)
    writeb(readb((void*)HW_BASE+(USBC1_BASE+0x0a)*2) | 0x40, (void*) (HW_BASE+(USBC1_BASE+0x0a)*2)); //enable PV2MI bridge ECO
#endif

#if (ENABLE_EIFFEL) || (ENABLE_NIKE) || (ENABLE_NADAL) || \
	(ENABLE_EINSTEIN) || (ENABLE_NIKON) || (ENABLE_NAPOLI) || \
	(ENABLE_MADISON) || (ENABLE_MIAMI) || (ENABLE_CLIPPERS) || \
	(ENABLE_MONACO) || (ENABLE_MUJI) || (ENABLE_CELTICS)
    usb_bc_enable(HW_BASE+UTMI2_BASE*2, HW_BASE+0x23640*2, FALSE);
#elif (ENABLE_KAISER)
    usb_bc_enable(HW_BASE+UTMI2_BASE*2, HW_BASE+0x22f80*2, FALSE);
#endif
}
#endif

#if defined(ENABLE_FOURTH_EHC)
void TV_usb_init_port3(void)
{
#if defined(CONFIG_KAISERIN)
    #define UTMI3_BASE  0x20A00
    #define UHC3_BASE   0x20900
    #define USBC3_BASE  0x20800
#elif (ENABLE_MONACO)
    #define UTMI3_BASE  0x22300
    #define UHC3_BASE   0x53000
    #define USBC3_BASE  0x53200
#elif (ENABLE_MUJI)
    #define UTMI3_BASE  0x22300
    #define UHC3_BASE   0x53000
    #define USBC3_BASE  0x53200
#elif (ENABLE_CELTICS)
    #define UTMI3_BASE  0x22300
    #define UHC3_BASE   0x53000
    #define USBC3_BASE  0x53200
#else
    #define UTMI3_BASE  0x22080
    #define UHC3_BASE   0x22600
    #define USBC3_BASE  0x13880
#endif

#if defined(ENABLE_USB_NEW_MIU_SEL)
    MIU_select_setting_ehc(HW_BASE+USBC3_BASE*2);
#endif

    //printf("TV_usb_init_port3, (U,C,H)=(%x,%x,%x) \n", UTMI3_BASE, USBC3_BASE, UHC3_BASE);
    writeb(0x0A, (void*)(HW_BASE+USBC3_BASE*2)); // Disable MAC initial suspend, Reset UHC
    writeb(0x28, (void*)(HW_BASE+USBC3_BASE*2)); // Release UHC reset, enable UHC XIU function

    writeb(readb((void*)(HW_BASE+(UTMI3_BASE+0x3C)*2) ) | 0x01, (void*) (HW_BASE+(UTMI3_BASE+0x3C)*2)); // set CA_START as 1
    mdelay(10);

    writeb(readb((void*)(HW_BASE+(UTMI3_BASE+0x3C)*2) ) & ~0x01, (void*) (HW_BASE+(UTMI3_BASE+0x3C)*2)); // release CA_START

    while ((readb((void*)(HW_BASE+(UTMI3_BASE+0x3C)*2) ) & 0x02) == 0);    // polling bit <1> (CA_END)

    writeb(readb((void*)(HW_BASE+(USBC3_BASE+0x02)*2) ) & ~0x03, (void*) (HW_BASE+(USBC3_BASE+0x02)*2)); //UHC select enable
    writeb(readb((void*)(HW_BASE+(USBC3_BASE+0x02)*2) ) | 0x01, (void*) (HW_BASE+(USBC3_BASE+0x02)*2)); //UHC select enable

    writeb(readb((void*)(HW_BASE+(UHC3_BASE+0x40)*2) ) & ~0x10, (void*) (HW_BASE+(UHC3_BASE+0x40)*2)); //0: VBUS On.
    mdelay(1);    // delay 1ms

    writeb(readb((void*)(HW_BASE+(UHC3_BASE+0x40)*2) ) | 0x08, (void*) (HW_BASE+(UHC3_BASE+0x40)*2)); // Active HIGH
    mdelay(1);    // delay 1ms
    writeb((readb((void*)(HW_BASE+(UTMI3_BASE+0x06)*2) ) & 0x9F) | 0x40, (void*) (HW_BASE+(UTMI3_BASE+0x06)*2)); //reg_tx_force_hs_current_enable

    writeb(readb((void*)(HW_BASE+(UTMI3_BASE+0x03)*2-1) ) | 0x28, (void*) (HW_BASE+(UTMI3_BASE+0x03)*2-1)); //Disconnect window select
    writeb(readb((void*)(HW_BASE+(UTMI3_BASE+0x03)*2-1) ) & 0xef, (void*) (HW_BASE+(UTMI3_BASE+0x03)*2-1)); //Disconnect window select
    writeb(readb((void*)(HW_BASE+(UTMI3_BASE+0x07)*2-1) ) & 0xfd, (void*) (HW_BASE+(UTMI3_BASE+0x07)*2-1)); //Disable improved CDR

    writeb(readb((void*)(HW_BASE+(UTMI3_BASE+0x08)*2) ) | 0x08, (void*) (HW_BASE+(UTMI3_BASE+0x08)*2)); // bit<3> for 240's phase as 120's clock set 1, bit<4> for 240Mhz in mac 0 for faraday 1 for etron

    writeb(readb((void*)(HW_BASE+(UTMI3_BASE+0x09)*2-1) ) |0x81, (void*) (HW_BASE+(UTMI3_BASE+0x09)*2-1)); // UTMI RX anti-dead-loc, ISI effect improvement
    writeb(readb((void*)(HW_BASE+(UTMI3_BASE+0x0b)*2-1) ) |0x80, (void*) (HW_BASE+(UTMI3_BASE+0x0b)*2-1)); // TX timing select latch path
    writeb(readb((void*)(HW_BASE+(UTMI3_BASE+0x15)*2-1) ) |0x20, (void*) (HW_BASE+(UTMI3_BASE+0x15)*2-1)); // Chirp signal source select

    writeb(readb((void*)(HW_BASE+(UTMI3_BASE+0x15)*2-1) ) |0x40, (void*) (HW_BASE+(UTMI3_BASE+0x15)*2-1)); // change to 55 interface


    /* for 55nm and later 40nm with 55nm setting */
    writeb(readb((void*)(HW_BASE+(UTMI3_BASE+0x2c)*2) ) |0x10, (void*) (HW_BASE+(UTMI3_BASE+0x2c)*2));
    writeb(readb((void*)(HW_BASE+(UTMI3_BASE+0x2d)*2-1) ) |0x02, (void*) (HW_BASE+(UTMI3_BASE+0x2d)*2-1));
    writeb(readb((void*)(HW_BASE+(UTMI3_BASE+0x2f)*2-1) ) |0x81, (void*) (HW_BASE+(UTMI3_BASE+0x2f)*2-1));

#if defined(CONFIG_KAISERIN)
    /* List no battery charger ICs */
#elif (ENABLE_MONACO)
    usb_bc_enable(HW_BASE+UTMI3_BASE*2, HW_BASE+0x23680*2, FALSE);
#elif (ENABLE_MUJI)
    usb_bc_enable(HW_BASE+UTMI3_BASE*2, HW_BASE+0x23680*2, FALSE);
#elif (ENABLE_CELTICS)
    usb_bc_enable(HW_BASE+UTMI3_BASE*2, HW_BASE+0x23680*2, FALSE);
#else
    usb_bc_enable(HW_BASE+UTMI3_BASE*2, HW_BASE+0x23660*2, FALSE);
#endif
}
#endif

extern int Usb_host_Init(void);
extern int Usb_host_PreInit(void);
extern int Usb_host_PostInit(void);
#if defined(ENABLE_SECOND_EHC)
extern int Usb_host_Init2(void);
extern int Usb_host_PreInit2(void);
extern int Usb_host_PostInit2(void);
#endif
#if defined(ENABLE_THIRD_EHC)
extern int Usb_host_Init3(void);
extern int Usb_host_PreInit3(void);
extern int Usb_host_PostInit3(void);
#endif
#if defined(ENABLE_FOURTH_EHC)
extern int Usb_host_Init4(void);
extern int Usb_host_PreInit4(void);
extern int Usb_host_PostInit4(void);
#endif
int usb_lowlevel_init(void)
{
    int speed=-1;
    int ret = 0;
    //root_hub_devnum = 0;

    #if defined(__ARM__)
    miu0_bus_base_addr = MsOS_VA2PA(MIU0_BUS_BASE_ADDR);
    miu1_bus_base_addr = MsOS_VA2PA(MIU1_BUS_BASE_ADDR);
    #if defined(MIU2_BUS_BASE_ADDR)
    miu2_bus_base_addr = MsOS_VA2PA(MIU2_BUS_BASE_ADDR);
    #endif
    #endif

    if (UsbPortSelect==0)
    {
        TV_usb_init();
        speed=Usb_host_Init();
    }
#if defined(ENABLE_SECOND_EHC)
    else if (UsbPortSelect==1)
    {
        TV_usb_init_port1();
        speed=Usb_host_Init2();
    }
#endif
#if defined(ENABLE_THIRD_EHC)
    else if (UsbPortSelect==2)
    {
        TV_usb_init_port2();
        speed=Usb_host_Init3();
    }
#endif
#if defined(ENABLE_FOURTH_EHC)
    else if (UsbPortSelect==3)
    {
        TV_usb_init_port3();
        speed=Usb_host_Init4();
    }
#endif
#if 1
    if (speed==1)
    {
        rh_status.wPortStatus |= USB_PORT_STAT_CONNECTION | USB_PORT_STAT_LOW_SPEED;
    }
    else
    {
        rh_status.wPortStatus |= USB_PORT_STAT_CONNECTION;
        rh_status.wPortStatus &= ~USB_PORT_STAT_LOW_SPEED;
        if(speed==-1)
            ret =-1;
    }
    rh_status.wPortChange |= USB_PORT_STAT_C_CONNECTION;
#endif
    return ret;
}

int usb_lowlevel_preinit(void)
{
    int speed=-1;
    int ret = 0;
    //root_hub_devnum = 0;
    if (UsbPortSelect==0)
    {
        TV_usb_init();
        speed=Usb_host_PreInit();
    }
#if defined(ENABLE_SECOND_EHC)
    else if (UsbPortSelect==1)
    {
        TV_usb_init_port1();
        speed=Usb_host_PreInit2();
    }
#endif
#if defined(ENABLE_THIRD_EHC)
    else if (UsbPortSelect==2)
    {
        TV_usb_init_port2();
        speed=Usb_host_PreInit3();
    }
#endif
#if defined(ENABLE_FOURTH_EHC)
    else if (UsbPortSelect==3)
    {
        TV_usb_init_port3();
        speed=Usb_host_PreInit4();
    }
#endif
#if 1
    if (speed==1)
    {
        rh_status.wPortStatus |= USB_PORT_STAT_CONNECTION | USB_PORT_STAT_LOW_SPEED;
    }
    else
    {
        rh_status.wPortStatus |= USB_PORT_STAT_CONNECTION;
        rh_status.wPortStatus &= ~USB_PORT_STAT_LOW_SPEED;
        if(speed==-1)
            ret =-1;
    }
    rh_status.wPortChange |= USB_PORT_STAT_C_CONNECTION;
#endif
    return ret;
}

int usb_lowlevel_postinit(void)
{
    int speed=-1;
    int ret = 0;

    #if defined(__ARM__)
    miu0_bus_base_addr = MsOS_VA2PA(MIU0_BUS_BASE_ADDR);
    miu1_bus_base_addr = MsOS_VA2PA(MIU1_BUS_BASE_ADDR);
    #if defined(MIU2_BUS_BASE_ADDR)
    miu2_bus_base_addr = MsOS_VA2PA(MIU2_BUS_BASE_ADDR);
    #endif
    #endif

    //root_hub_devnum = 0;
    if (UsbPortSelect==0)
    {
        //TV_usb_init();
        speed=Usb_host_PostInit();
    }
#if defined(ENABLE_SECOND_EHC)
    else if (UsbPortSelect==1)
    {
        //TV_usb_init_port1();
        speed=Usb_host_PostInit2();
    }
#endif
#if defined(ENABLE_THIRD_EHC)
    else if (UsbPortSelect==2)
    {
        //TV_usb_init_port2();
        speed=Usb_host_PostInit3();
    }
#endif
#if defined(ENABLE_FOURTH_EHC)
    else if (UsbPortSelect==3)
    {
        //TV_usb_init_port3();
        speed=Usb_host_PostInit4();
    }
#endif
#if 1
    if (speed==1)
    {
        rh_status.wPortStatus |= USB_PORT_STAT_CONNECTION | USB_PORT_STAT_LOW_SPEED;
    }
    else
    {
        rh_status.wPortStatus |= USB_PORT_STAT_CONNECTION;
        rh_status.wPortStatus &= ~USB_PORT_STAT_LOW_SPEED;
        if(speed==-1)
            ret =-1;
    }
    rh_status.wPortChange |= USB_PORT_STAT_C_CONNECTION;
#endif
    return ret;
}

extern void MDrv_UsbClose(void);
#if defined(ENABLE_SECOND_EHC)
extern void MDrv_UsbClose2(void);
#endif
#if defined(ENABLE_THIRD_EHC)
extern void MDrv_UsbClose3(void);
#endif
#if defined(ENABLE_FOURTH_EHC)
extern void MDrv_UsbClose4(void);
#endif
#ifdef ENABLE_USB_LAN_MODULE
extern void usb_lan_release(void);
#endif
int usb_lowlevel_stop(int p)
{
    if (p==0xff)                 //use UsbPortSelect
    {
        p=UsbPortSelect;
    }

#ifdef ENABLE_USB_LAN_MODULE
    usb_lan_release();
#endif

    if (p==0)
    {
        MDrv_UsbClose();
    }
#if defined(ENABLE_SECOND_EHC)
    else if (p==1)
    {
        MDrv_UsbClose2();
    }
#endif
#if defined(ENABLE_THIRD_EHC)
    else if (p==2)
    {
        MDrv_UsbClose3();
    }
#endif
#if defined(ENABLE_FOURTH_EHC)
    else if (p==3)
    {
        MDrv_UsbClose4();
    }
#endif
   return 0;
}

extern unsigned char Send_Receive_Bulk_Data(void *buffer,int len,int dir_out);
extern unsigned char Send_Receive_Bulk_Data2(void *buffer,int len,int dir_out);
extern unsigned char Send_Receive_Bulk_Data3(void *buffer,int len,int dir_out);
#if defined(ENABLE_FOURTH_EHC)
extern unsigned char Send_Receive_Bulk_Data4(void *buffer,int len,int dir_out);
extern unsigned long gUsbStatusP3;
extern int gTotalBytesP3;
#endif

extern unsigned long  gUsbStatus,gUsbStatusP1,gUsbStatusP2;
extern int gTotalBytes,gTotalBytesP1,gTotalBytesP2;
int usb_bulk_transfer_in(struct usb_device *dev, void *data, int len,int *transdata)
{
    *transdata=0;
    if (UsbPortSelect==0)
    {
        if (Send_Receive_Bulk_Data(data,len,0)>0)
        {
            dev->status=gUsbStatus;
            return -1;
         }
        *transdata=len-gTotalBytes;
    }
#if defined(ENABLE_SECOND_EHC)
    else if (UsbPortSelect==1)
    {
        if (Send_Receive_Bulk_Data2(data,len,0)>0)
        {
            dev->status=gUsbStatusP1;
            return -1;
        }
        *transdata=len-gTotalBytesP1;
    }
#endif
#if defined(ENABLE_THIRD_EHC)
    else if (UsbPortSelect==2)
    {
        if (Send_Receive_Bulk_Data3(data,len,0)>0)
        {
            dev->status=gUsbStatusP2;
            return -1;
        }
        *transdata=len-gTotalBytesP2;
    }
#endif
#if defined(ENABLE_FOURTH_EHC)
    else if (UsbPortSelect==3)
    {
        if (Send_Receive_Bulk_Data4(data,len,0)>0)
        {
            dev->status=gUsbStatusP3;
            return -1;
        }
        *transdata=len-gTotalBytesP3;
    }
#endif

    if(dev->status==0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int usb_bulk_transfer_out(struct usb_device *dev, void *data, int len)
{
    if (UsbPortSelect==0)
    {
        if (Send_Receive_Bulk_Data(data,len,1)>0)
        {
            dev->status=gUsbStatus;
            return -1;
        }
    }
#if defined(ENABLE_SECOND_EHC)
    else if (UsbPortSelect==1)
    {
         if (Send_Receive_Bulk_Data2(data,len,1)>0)
        {
            dev->status=gUsbStatusP1;
            return -1;
        }
    }
#endif
#if defined(ENABLE_THIRD_EHC)
    else if (UsbPortSelect==2)
    {
         if (Send_Receive_Bulk_Data3(data,len,1)>0)
        {
            dev->status=gUsbStatusP2;
            return -1;
        }
    }
#endif
#if defined(ENABLE_FOURTH_EHC)
    else if (UsbPortSelect==3)
    {
         if (Send_Receive_Bulk_Data4(data,len,1)>0)
        {
            dev->status=gUsbStatusP3;
            return -1;
        }
    }
#endif

    if(dev->status==0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int submit_bulk_msg(struct usb_device *dev, unsigned long pipe, void *buffer, int len)
{
    int dir_out = usb_pipeout(pipe);
    int done = 0;

    dev->status = 0;

    if (UsbPortSelect==0)
    {
        if (Send_Receive_Bulk_Data(buffer,len,dir_out)>0)
        {
            dev->status=gUsbStatus;
            return -1;
        }
    }
#if defined(ENABLE_SECOND_EHC)
    else if (UsbPortSelect==1)
    {
         if (Send_Receive_Bulk_Data2(buffer,len,dir_out)>0)
        {
            dev->status=gUsbStatusP1;
            return -1;
        }
    }
#endif
#if defined(ENABLE_THIRD_EHC)
    else if (UsbPortSelect==2)
    {
         if (Send_Receive_Bulk_Data3(buffer,len,dir_out)>0)
        {
            dev->status=gUsbStatusP2;
            return -1;
        }
    }
#endif
#if defined(ENABLE_FOURTH_EHC)
    else if (UsbPortSelect==3)
    {
         if (Send_Receive_Bulk_Data4(buffer,len,dir_out)>0)
        {
            dev->status=gUsbStatusP3;
            return -1;
        }
    }
#endif
    dev->act_len = done;

    return 0;
}

extern unsigned char flib_Host20_Issue_Control (unsigned char bEdNum, unsigned char* pbCmd, unsigned short hwDataSize, unsigned char* pbData);
#if defined(ENABLE_SECOND_EHC)
extern unsigned char flib_Host20_Issue_Control2 (unsigned char bEdNum, unsigned char* pbCmd, unsigned short hwDataSize, unsigned char* pbData);
#endif
#if defined(ENABLE_THIRD_EHC)
extern unsigned char flib_Host20_Issue_Control3 (unsigned char bEdNum, unsigned char* pbCmd, unsigned short hwDataSize, unsigned char* pbData);
#endif
#if defined(ENABLE_FOURTH_EHC)
extern unsigned char flib_Host20_Issue_Control4 (unsigned char bEdNum, unsigned char* pbCmd, unsigned short hwDataSize, unsigned char* pbData);
#endif
int submit_control_msg(struct usb_device *dev, unsigned long pipe, void *buffer,
               int len,struct devrequest *setup)
{
    int done = 0;
    dev->status = 0;

    if (UsbPortSelect==0)
    {

        if ( flib_Host20_Issue_Control (dev->devnum,(unsigned char*) setup,len,(unsigned char*) buffer) > 0)
        {
            dev->status=gUsbStatus;
            done=-1;
        }
    }
#if defined(ENABLE_SECOND_EHC)
    else if (UsbPortSelect==1)
    {
        if ( flib_Host20_Issue_Control2(dev->devnum,(unsigned char*) setup,len,(unsigned char*) buffer) > 0)
        {
            dev->status=gUsbStatusP1;
            done=-1;
        }
    }
#endif
#if defined(ENABLE_THIRD_EHC)
    else if (UsbPortSelect==2)
    {
        if ( flib_Host20_Issue_Control3(dev->devnum,(unsigned char*) setup,len,(unsigned char*) buffer) > 0)
        {
            dev->status=gUsbStatusP2;
            done=-1;
        }
    }
#endif
#if defined(ENABLE_FOURTH_EHC)
    else if (UsbPortSelect==3)
    {
        if ( flib_Host20_Issue_Control4(dev->devnum,(unsigned char*) setup,len,(unsigned char*) buffer) > 0)
        {
            dev->status=gUsbStatusP3;
            done=-1;
        }
    }
#endif
    /* status phase */

    dev->act_len = len;

    return done;
}

extern void SetControl1MaxPacket(unsigned char max);
extern void USB_Bulk_Init(struct usb_device *dev);
extern int ever_inited;

#if defined(ENABLE_SECOND_EHC)
extern void SetControl1MaxPacket2(unsigned char max);
extern void USB_Bulk_Init2(struct usb_device *dev);
extern int ever_inited2;
#endif

#if defined(ENABLE_THIRD_EHC)
extern void SetControl1MaxPacket3(unsigned char max);
extern void USB_Bulk_Init3(struct usb_device *dev);
extern int ever_inited3;
#endif

#if defined(ENABLE_FOURTH_EHC)
extern void SetControl1MaxPacket4(unsigned char max);
extern void USB_Bulk_Init4(struct usb_device *dev);
extern int ever_inited4;
#endif

void SetControl1MaxPacketEx(unsigned char max, int port)
{
    if (UsbPortSelect==0)
        SetControl1MaxPacket(max);
#if defined(ENABLE_SECOND_EHC)
    else if (UsbPortSelect==1)
        SetControl1MaxPacket2(max);
#endif
#if defined(ENABLE_THIRD_EHC)
    else if (UsbPortSelect==2)
        SetControl1MaxPacket3(max);
#endif
#if defined(ENABLE_FOURTH_EHC)
    else if (UsbPortSelect==3)
        SetControl1MaxPacket4(max);
#endif
    else
        printf("[USB] SetControl1MaxPacketEx: exceed max port (%d)\n", UsbPortSelect);
}

void USB_Bulk_InitEx(struct usb_device *dev, int port)
{
    if (UsbPortSelect==0)
        USB_Bulk_Init(dev);              //init bulk structure,yuwen
#if defined(ENABLE_SECOND_EHC)
    else if (UsbPortSelect==1)
        USB_Bulk_Init2(dev);
#endif
#if defined(ENABLE_THIRD_EHC)
    else if (UsbPortSelect==2)
        USB_Bulk_Init3(dev);
#endif
#if defined(ENABLE_FOURTH_EHC)
    else if (UsbPortSelect==3)
        USB_Bulk_Init4(dev);
#endif
    else
        printf("[USB] USB_Bulk_InitEx: exceed max port (%d)\n", UsbPortSelect);
}

void Usb_host_SetEverInited(int val)
{
    if (UsbPortSelect==0)
        ever_inited = val;
#if defined(ENABLE_SECOND_EHC)
    else if (UsbPortSelect==1)
        ever_inited2 = val;
#endif
#if defined(ENABLE_THIRD_EHC)
    else if (UsbPortSelect==2)
        ever_inited3 = val;
#endif
#if defined(ENABLE_FOURTH_EHC)
    else if (UsbPortSelect==3)
        ever_inited4 = val;
#endif
    else
        printf("[USB] Usb_host_SetEverInited: exceed max port (%d)\n", UsbPortSelect);
}

int submit_int_msg(struct usb_device *dev, unsigned long pipe, void *buffer, int len, int interval)
{
    return -1;
}

/*
 * SL811 Virtual Root Hub
 */

/* Device descriptor */
#if 0
static __u8 sl811_rh_dev_des[] =
{
    0x12,        /*    __u8  bLength; */
    0x01,        /*    __u8  bDescriptorType; Device */
    0x10,        /*    __u16 bcdUSB; v1.1 */
    0x01,
    0x09,        /*    __u8  bDeviceClass; HUB_CLASSCODE */
    0x00,        /*    __u8  bDeviceSubClass; */
    0x00,        /*    __u8  bDeviceProtocol; */
    0x08,        /*    __u8  bMaxPacketSize0; 8 Bytes */
    0x00,        /*    __u16 idVendor; */
    0x00,
    0x00,        /*    __u16 idProduct; */
    0x00,
    0x00,        /*    __u16 bcdDevice; */
    0x00,
    0x00,        /*    __u8  iManufacturer; */
    0x02,        /*    __u8  iProduct; */
    0x01,        /*    __u8  iSerialNumber; */
    0x01        /*    __u8  bNumConfigurations; */
};

/* Configuration descriptor */
static __u8 sl811_rh_config_des[] =
{
    0x09,        /*    __u8  bLength; */
    0x02,        /*    __u8  bDescriptorType; Configuration */
    0x19,        /*    __u16 wTotalLength; */
    0x00,
    0x01,        /*    __u8  bNumInterfaces; */
    0x01,        /*    __u8  bConfigurationValue; */
    0x00,        /*    __u8  iConfiguration; */
    0x40,        /*    __u8  bmAttributes;
            Bit 7: Bus-powered, 6: Self-powered, 5 Remote-wakwup,
            4..0: resvd */
    0x00,        /*    __u8  MaxPower; */

    /* interface */
    0x09,        /*    __u8  if_bLength; */
    0x04,        /*    __u8  if_bDescriptorType; Interface */
    0x00,        /*    __u8  if_bInterfaceNumber; */
    0x00,        /*    __u8  if_bAlternateSetting; */
    0x01,        /*    __u8  if_bNumEndpoints; */
    0x09,        /*    __u8  if_bInterfaceClass; HUB_CLASSCODE */
    0x00,        /*    __u8  if_bInterfaceSubClass; */
    0x00,        /*    __u8  if_bInterfaceProtocol; */
    0x00,        /*    __u8  if_iInterface; */

    /* endpoint */
    0x07,        /*    __u8  ep_bLength; */
    0x05,        /*    __u8  ep_bDescriptorType; Endpoint */
    0x81,        /*    __u8  ep_bEndpointAddress; IN Endpoint 1 */
    0x03,        /*    __u8  ep_bmAttributes; Interrupt */
    0x08,        /*    __u16 ep_wMaxPacketSize; */
    0x00,
    0xff        /*    __u8  ep_bInterval; 255 ms */
};

/* root hub class descriptor*/
static __u8 sl811_rh_hub_des[] =
{
    0x09,            /*  __u8  bLength; */
    0x29,            /*  __u8  bDescriptorType; Hub-descriptor */
    0x01,            /*  __u8  bNbrPorts; */
    0x00,            /* __u16  wHubCharacteristics; */
    0x00,
    0x50,            /*  __u8  bPwrOn2pwrGood; 2ms */
    0x00,            /*  __u8  bHubContrCurrent; 0 mA */
    0xfc,            /*  __u8  DeviceRemovable; *** 7 Ports max *** */
    0xff            /*  __u8  PortPwrCtrlMask; *** 7 ports max *** */
};

/*
 * helper routine for returning string descriptors in UTF-16LE
 * input can actually be ISO-8859-1; ASCII is its 7-bit subset
 */
static int ascii2utf (char *s, u8 *utf, int utfmax)
{
    int retval;

    for (retval = 0; *s && utfmax > 1; utfmax -= 2, retval += 2) {
        *utf++ = *s++;
        *utf++ = 0;
    }
    return retval;
}
#endif
/*
 * root_hub_string is used by each host controller's root hub code,
 * so that they're identified consistently throughout the system.
 */
#if 0
static int usb_root_hub_string (int id, int serial, char *type, __u8 *data, int len)
{
    char buf [30];

    /* assert (len > (2 * (sizeof (buf) + 1)));
       assert (strlen (type) <= 8);*/

    /* language ids */
    if (id == 0) {
        *data++ = 4; *data++ = 3;    /* 4 bytes data */
        *data++ = 0; *data++ = 0;    /* some language id */
        return 4;

    /* serial number */
    } else if (id == 1) {
        sprintf (buf, "%#x", serial);

    /* product description */
    } else if (id == 2) {
        sprintf (buf, "USB %s Root Hub", type);

    /* id 3 == vendor description */

    /* unsupported IDs --> "stall" */
    } else
        return 0;

    ascii2utf (buf, data + 2, len - 2);
    data [0] = 2 + strlen(buf) * 2;
    data [1] = 3;
    return data [0];
}
#endif
/* helper macro */
#define OK(x)    len = (x); break

/*
 * This function handles all USB request to the the virtual root hub
 */
#if 0
static int titania_rh_submit_urb(struct usb_device *usb_dev, unsigned long pipe,
                   void *data, int buf_len, struct devrequest *cmd)
{
    __u8 data_buf[16];
    __u8 *bufp = data_buf;
    int len = 0;
    int status = 0;

    __u16 bmRType_bReq;
    __u16 wValue;
    __u16 wIndex;
    __u16 wLength;

    if (usb_pipeint(pipe)) {
        PDEBUG(0, "interrupt transfer unimplemented!\n");
        return 0;
    }

    bmRType_bReq  = cmd->requesttype | (cmd->request << 8);
    wValue          = le16_to_cpu (cmd->value);
    wIndex          = le16_to_cpu (cmd->index);
    wLength          = le16_to_cpu (cmd->length);

    PDEBUG(5, "submit rh urb, req = %d(%x) val = %#x index = %#x len=%d\n",
           bmRType_bReq, bmRType_bReq, wValue, wIndex, wLength);

    /* Request Destination:
           without flags: Device,
           USB_RECIP_INTERFACE: interface,
           USB_RECIP_ENDPOINT: endpoint,
           USB_TYPE_CLASS means HUB here,
           USB_RECIP_OTHER | USB_TYPE_CLASS  almost ever means HUB_PORT here
    */
    switch (bmRType_bReq) {
    case RH_GET_STATUS:
        *(__u16 *)bufp = cpu_to_le16(1);
        OK(2);

    case RH_GET_STATUS | USB_RECIP_INTERFACE:
        *(__u16 *)bufp = cpu_to_le16(0);
        OK(2);

    case RH_GET_STATUS | USB_RECIP_ENDPOINT:
        *(__u16 *)bufp = cpu_to_le16(0);
        OK(2);

    case RH_GET_STATUS | USB_TYPE_CLASS:
        *(__u32 *)bufp = cpu_to_le32(0);
        OK(4);

    case RH_GET_STATUS | USB_RECIP_OTHER | USB_TYPE_CLASS:
        *(__u32 *)bufp = cpu_to_le32(rh_status.wPortChange<<16 | rh_status.wPortStatus);
        OK(4);

    case RH_CLEAR_FEATURE | USB_RECIP_ENDPOINT:
        switch (wValue) {
        case 1:
            OK(0);
        }
        break;

    case RH_CLEAR_FEATURE | USB_TYPE_CLASS:
        switch (wValue) {
        case C_HUB_LOCAL_POWER:
            OK(0);

        case C_HUB_OVER_CURRENT:
            OK(0);
        }
        break;

    case RH_CLEAR_FEATURE | USB_RECIP_OTHER | USB_TYPE_CLASS:
        switch (wValue) {
        case USB_PORT_FEAT_ENABLE:
            rh_status.wPortStatus &= ~USB_PORT_STAT_ENABLE;
            OK(0);

        case USB_PORT_FEAT_SUSPEND:
            rh_status.wPortStatus &= ~USB_PORT_STAT_SUSPEND;
            OK(0);

        case USB_PORT_FEAT_POWER:
            rh_status.wPortStatus &= ~USB_PORT_STAT_POWER;
            OK(0);

        case USB_PORT_FEAT_C_CONNECTION:
            rh_status.wPortChange &= ~USB_PORT_STAT_C_CONNECTION;
            OK(0);

        case USB_PORT_FEAT_C_ENABLE:
            rh_status.wPortChange &= ~USB_PORT_STAT_C_ENABLE;
            OK(0);

        case USB_PORT_FEAT_C_SUSPEND:
            rh_status.wPortChange &= ~USB_PORT_STAT_C_SUSPEND;
            OK(0);

        case USB_PORT_FEAT_C_OVER_CURRENT:
            rh_status.wPortChange &= ~USB_PORT_STAT_C_OVERCURRENT;
            OK(0);

        case USB_PORT_FEAT_C_RESET:
            rh_status.wPortChange &= ~USB_PORT_STAT_C_RESET;
            OK(0);
        }
        break;

    case RH_SET_FEATURE | USB_RECIP_OTHER | USB_TYPE_CLASS:
        switch (wValue) {
        case USB_PORT_FEAT_SUSPEND:
            rh_status.wPortStatus |= USB_PORT_STAT_SUSPEND;
            OK(0);

        case USB_PORT_FEAT_RESET:
            rh_status.wPortStatus |= USB_PORT_STAT_RESET;
            rh_status.wPortChange = 0;
            rh_status.wPortChange |= USB_PORT_STAT_C_RESET;
            rh_status.wPortStatus &= ~USB_PORT_STAT_RESET;
            rh_status.wPortStatus |= USB_PORT_STAT_ENABLE;
            OK(0);

        case USB_PORT_FEAT_POWER:
            rh_status.wPortStatus |= USB_PORT_STAT_POWER;
            OK(0);

        case USB_PORT_FEAT_ENABLE:
            rh_status.wPortStatus |= USB_PORT_STAT_ENABLE;
            OK(0);
        }
        break;

    case RH_SET_ADDRESS:
        root_hub_devnum = wValue;
        OK(0);

    case RH_GET_DESCRIPTOR:
        switch ((wValue & 0xff00) >> 8) {
        case USB_DT_DEVICE:
            len = sizeof(sl811_rh_dev_des);
            bufp = sl811_rh_dev_des;
            OK(len);

        case USB_DT_CONFIG:
            len = sizeof(sl811_rh_config_des);
            bufp = sl811_rh_config_des;
            OK(len);

        case USB_DT_STRING:
            len = usb_root_hub_string(wValue & 0xff, (int)(long)0,    "SL811HS", data, wLength);
            if (len > 0) {
                bufp = data;
                OK(len);
            }

        default:
            status = -32;
        }
        break;

    case RH_GET_DESCRIPTOR | USB_TYPE_CLASS:
        len = sizeof(sl811_rh_hub_des);
        bufp = sl811_rh_hub_des;
        OK(len);

    case RH_GET_CONFIGURATION:
        bufp[0] = 0x01;
        OK(1);

    case RH_SET_CONFIGURATION:
        OK(0);

    default:
        PDEBUG(1, "unsupported root hub command\n");
        status = -32;
    }

    len = min(len, buf_len);
    if (data != bufp)
        memcpy(data, bufp, len);

    PDEBUG(5, "len = %d, status = %d\n", len, status);

    usb_dev->status = status;
    usb_dev->act_len = len;

    return status == 0 ? len : status;
}
#endif
#endif    /* CONFIG_USB_SL811HS */
