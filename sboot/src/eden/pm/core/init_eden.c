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
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2008 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ( ß¡±MStar Confidential Information ßÆØ) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "datatype.h"
#include "drvGlobal.h"
#include "hwreg.h"
#include "MApp_Wakeup.h"
#include "MsTypes.h"
#include "uartdebug.h"

//***********************************************************
//              Macro Definitions
//***********************************************************
#define PMSLEEP_REG_BASE                        (0x0700*2)
#define REG_PM_WK_IRQ_POL                       ((0x00*0x10000) + (PMSLEEP_REG_BASE + 0x09*2))
#define REG_PM_UART_RX_ENABLE                   ((0x00*0x10000) + (PMSLEEP_REG_BASE + 0x09*2))
#define REG_PM_HK51_UART0_EN                    ((0x00*0x10000) + (PMSLEEP_REG_BASE + 0x09*2))
#define REG_PM_WAKEUP_RST_CHIP_TOP_EN           ((0x00*0x10000) + (PMSLEEP_REG_BASE + 0x09*2))
#define REG_PM_WAKEUP_RST_51_EN                 ((0x00*0x10000) + (PMSLEEP_REG_BASE + 0x09*2))
#define REG_PM_DEEP_SLEEP                       ((0x00*0x10000) + (PMSLEEP_REG_BASE + 0x09*2))

#define REG_PM_IRQ_SYNC                       BIT3
#define REG_PM_IRQ_RTC0                       BIT4
#define REG_PM_IRQ_DDC                        BIT5
#define REG_PM_IRQ_AVLINK                     BIT6
#define REG_PM_IRQ_RTC1                       BIT7


//***********************************************************
//              Global Functions Declaration
//***********************************************************
void InitialSystemPowerDown(void);
#if BLOCK_POWER_FUNC
void MDrv_Block_PowerUp(void);
#endif

//***********************************************************
//              Local Functions Definition
//***********************************************************
static void MDrv_Digital_PowerDown(void)
{
    // Please follow IP clock gating flow
    // 1. IP SW reset
    // 2. MIU client ID mask
    // 3. IP clock gate
    {
        // tsp and stc0
        MDrv_Write2Byte(0x101588, MDrv_Read2Byte(0x101588) & ~(BIT2|BIT1|BIT0));  // IP reset
        MDrv_Write2Byte(0x101246, MDrv_Read2Byte(0x101588) | (BIT14|BIT10|BIT9));  // g0
        MDrv_WriteRegBit(0x100b54, 1, BIT0);    // tsp clock gating
        MDrv_WriteRegBit(0x100b55, 1, BIT0);    // stc0 clock gating
    }

    {
        // mvd
        MDrv_Write2Byte(0x101100, MDrv_Read2Byte(0x101100) | BIT0); // IP reset
        MDrv_Write2Byte(0x101246, MDrv_Read2Byte(0x101588) | BIT11);  // g0
        MDrv_Write2Byte(0x101286, MDrv_Read2Byte(0x101286) | BIT4);  // g2
        MDrv_WriteRegBit(0x100b72, 1, BIT0);    // IP clock gating
        MDrv_WriteRegBit(0x100b73, 1, BIT0);
        MDrv_WriteRegBit(0x100b74, 1, BIT0);
        MDrv_WriteRegBit(0x100b75, 1, BIT0);
        MDrv_WriteRegBit(0x100b76, 1, BIT0);
        MDrv_WriteRegBit(0x100b77, 1, BIT0);
        MDrv_WriteRegBit(0x100b78, 1, BIT0);
        MDrv_WriteRegBit(0x100b79, 1, BIT0);
    }

    {
        // mvop
        MDrv_Write2Byte(0x101422, MDrv_Read2Byte(0x101422) & ~(BIT0));
        MDrv_Write2Byte(0x101266, MDrv_Read2Byte(0x101266) | BIT3);   //g1
        MDrv_WriteRegBit(0x100b4c, 1, BIT0);
        MDrv_WriteRegBit(0x100b4d, 1, BIT0);
    }

    {
        // gop
        MDrv_Write2Byte(0x101ffe, MDrv_Read2Byte(0x101ffe) & ~(BIT3|BIT2|BIT1|BIT0)); // set gop bank
        MDrv_Write2Byte(0x101f00, MDrv_Read2Byte(0x101f00) | BIT0);
        MDrv_Write2Byte(0x101266, MDrv_Read2Byte(0x101266) | (BIT6|BIT5|BIT4));   //g1
        MDrv_WriteRegBit(0x100b80, 1, BIT0);
        MDrv_WriteRegBit(0x100b81, 1, BIT0);
        MDrv_WriteRegBit(0x100b83, 1, BIT0);
    }

    {
        // ge
        MDrv_Write2Byte(0x102800, MDrv_Read2Byte(0x102800) & ~(BIT0));
        MDrv_Write2Byte(0x101286, MDrv_Read2Byte(0x101286) | BIT1); //g2
        MDrv_WriteRegBit(0x100b90, 1, BIT0);
    }

    {
        // hvd
        MDrv_Write2Byte(0x101b02, MDrv_Read2Byte(0x101b02) | BIT0);
        MDrv_Write2Byte(0x101286, MDrv_Read2Byte(0x101286) | (BIT3|BIT5)); //g2
        MDrv_WriteRegBit(0x100b62, 1, BIT0);
    }

    {
        // usb
        MDrv_WriteRegBit(0x103a88, 1, BIT7);
        MDrv_WriteByte(0x103a82, 0x80);
        MDrv_WriteByte(0x103a83, 0x90);
        MDrv_WriteByte(0x103a80, 0xc7);
        MDrv_WriteByte(0x103a81, 0xef);
        MDrv_WriteByte(0x100700, 0x00);
        MDrv_WriteByte(0x100702, 0x00);

        MDrv_Write2Byte(0x102408, MDrv_Read2Byte(0x102408) | BIT1);
        MDrv_Write2Byte(0x101286, MDrv_Read2Byte(0x101286) | BIT6); //g2
    }

    {
        // jpd
        MDrv_Write2Byte(0x101700, MDrv_Read2Byte(0x101700) & ~(BIT13));
        MDrv_Write2Byte(0x101286, MDrv_Read2Byte(0x101286) | BIT8); //g2
        MDrv_WriteRegBit(0x100b6a, 1, BIT0);
    }

    {
        // dscrmb
        MDrv_Write2Byte(0x100c00, MDrv_Read2Byte(0x100c00) | BIT7);
        MDrv_Write2Byte(0x101286, MDrv_Read2Byte(0x101286) | BIT9); //g2
        // clk gateing ??
    }

    {
        // vd(comb)
        MDrv_WriteRegBit(0x103613, 1, BIT6);  // comb SW reset
        MDrv_WriteRegBit(0x103770, 1, BIT3);  // VBI SW reset
        MDrv_WriteRegBit(0x103801, 1, BIT7);  // SCM SW reset
        MDrv_Write2Byte(0x101266, MDrv_Read2Byte(0x101266) | (BIT13|BIT12));   //g1
        MDrv_Write2Byte(0x101246, MDrv_Read2Byte(0x101588) | BIT12);  // g0
        MDrv_Write2Byte(0x101286, MDrv_Read2Byte(0x101286) | BIT2);  // g2
        MDrv_WriteRegBit(0x100b41, 1, BIT0);
        MDrv_WriteRegBit(0x100b46, 1, BIT0);
        MDrv_WriteRegBit(0x100b43, 1, BIT0);
        MDrv_WriteRegBit(0x100b47, 1, BIT0);
    }

    {
        // mau0 & mau1
        // g0,ID=5 mau0(hk_aeon) riu=0x100f
        // g0,ID=6 mau1(codec_aeon) riu=0x1003
        // g0,ID=8 unused
        MDrv_WriteRegBit(0x100ff0, 0, BIT1);
        MDrv_WriteRegBit(0x1003f0, 0, BIT1);
        MDrv_Write2Byte(0x101246, MDrv_Read2Byte(0x101588) | (BIT6|BIT5));  // g0
        MDrv_WriteRegBit(0x100b24, 1, BIT0);
        MDrv_WriteRegBit(0x100b60, 1, BIT0);
    }

    {
        // sc
        MDrv_WriteByte(0x102f00, 0x00); // bank0
        MDrv_WriteByte(0x103f04, 0x01); // SC SW reset
        MDrv_Write2Byte(0x101266, MDrv_Read2Byte(0x101266) | (BIT10|BIT9|BIT8|BIT7));   //g1
        MDrv_WriteRegBit(0x100ba8, 1, BIT0); // sc clock gate
        MDrv_WriteRegBit(0x100baa, 1, BIT0);
        MDrv_WriteRegBit(0x100bac, 1, BIT0);
        MDrv_WriteRegBit(0x100bae, 1, BIT0);
        MDrv_WriteRegBit(0x100ba5, 1, BIT0);
        MDrv_WriteRegBit(0x100ba3, 1, BIT0);
    }

    {
        // vivaldi9
        MDrv_WriteByte(0x112c00, 0x03); // vivaldi reset
        MDrv_Write2Byte(0x101246, MDrv_Read2Byte(0x101588) | (BIT5|BIT6));  // g0
        MDrv_Write2Byte(0x101266, MDrv_Read2Byte(0x101266) | (BIT0|BIT1|BIT2));   //g1
        MDrv_Write2Byte(0x101286, MDrv_Read2Byte(0x101286) | BIT0);  // g2
        MDrv_WriteByte(0x112caa, 0x00);
        MDrv_WriteByte(0x112cab, 0x00);
    }

    MDrv_WriteRegBit(0x100b34, 1, BIT0);
    MDrv_WriteRegBit(0x100b49, 1, BIT0);
    MDrv_WriteRegBit(0x100b4c, 1, BIT0);
    MDrv_WriteRegBit(0x100b4d, 1, BIT0);
    MDrv_WriteRegBit(0x100b6a, 1, BIT0);

    MDrv_WriteRegBit(0x103308, 1, BIT0);
    MDrv_WriteRegBit(0x103309, 1, BIT0);
    MDrv_WriteRegBit(0x103314, 1, BIT0);
    MDrv_WriteRegBit(0x10331a, 1, BIT0);
    MDrv_WriteRegBit(0x10331b, 1, BIT0);

    MDrv_WriteRegBit(0x100b3e, 1, BIT0);
    MDrv_WriteRegBit(0x100b27, 1, BIT0);
	
#if ENABLE_UART2
    MDrv_WriteRegBit(0x100b28, 0, BIT0);
#else
	MDrv_WriteRegBit(0x100b28, 1, BIT0);
#endif

    MDrv_WriteRegBit(0x100b29, 1, BIT0);
    MDrv_WriteRegBit(0x100b3f, 1, BIT0);

    MDrv_WriteRegBit(0x100b86, 1, BIT0);
    MDrv_WriteRegBit(0x100b87, 1, BIT0);

    MDrv_WriteRegBit(0x100ba6, 1, BIT0);
    MDrv_WriteRegBit(0x100bae, 1, BIT0);
    MDrv_WriteRegBit(0x100baf, 1, BIT0);
    MDrv_WriteRegBit(0x100ba6, 1, BIT0);
    MDrv_WriteRegBit(0x100b42, 1, BIT0);
    MDrv_WriteRegBit(0x10331e, 1, BIT0);
    MDrv_WriteRegBit(0x100b44, 1, BIT0);
    MDrv_WriteRegBit(0x100b45, 1, BIT0);

    MDrv_WriteRegBit(0x100b34, 1, BIT0);
    MDrv_WriteRegBit(0x100b34, 1, BIT0);
    MDrv_WriteRegBit(0x100b24, 1, BIT0);

    MDrv_WriteRegBit(0x100ba7, 1, BIT0);
    MDrv_WriteRegBit(0x100b60, 1, BIT0);
    MDrv_WriteRegBit(0x103362, 1, BIT0);
}

static void MDrv_DVITOP_PowerDown(void) //OK
{
    MDrv_WriteRegBit( 0x000e98, 0, 0x01);
    MDrv_WriteRegBit( 0x1109c0, 1, 0x20);
    MDrv_WriteRegBit( 0x1109c0, 1, 0x80);
    MDrv_WriteRegBit( 0x000e97, 1, 0x01);
    MDrv_WriteRegBit( 0x000e97, 0, 0x02);
    MDrv_WriteRegBit( 0x000e94, 0, 0x40);
    MDrv_WriteRegBit( 0x1109BE, 1, 0x01);
    MDrv_WriteRegBit( 0x1109C0, 1, 0x07);

    MDrv_WriteRegBit( 0x1109C1, 1, 0x07);
    MDrv_WriteRegBit( 0x1109C1, 1, 0x38);

    MDrv_WriteRegBit( 0x1109D3, 1, 0x07);
    MDrv_WriteRegBit( 0x1109D3, 1, 0x38);

    MDrv_WriteRegBit( 0x1109F8, 1, 0x07);
    MDrv_WriteRegBit( 0x1109F8, 1, 0x70);

    MDrv_WriteRegBit( 0x000e97, 0, 0x38);
    MDrv_WriteRegBit( 0x102711, 0, 0x02);

}

static void MDrv_Demod_PowerDown(void) //OK
{
    //switch 0x112800 bank access right to HK mcu
    MDrv_WriteRegBit(0x101e39, 0, 0x03);
    //configure settings
    MDrv_WriteRegBit(0x112840, 1, 0x10);
    MDrv_WriteRegBit(0x112818, 1, 0x04);
    MDrv_WriteRegBit(0x11281E, 1, 0x80);
    MDrv_WriteRegBit(0x112818, 1, 0x01);
    MDrv_WriteRegBit(0x112879, 1, 0x10);
    //switch 0x112800 bank access right to dmd mcu
    MDrv_WriteRegBit(0x101e39, 1, 0x03);
}

static void MDrv_VideoAtop_PowerDown(void) //OK
{
    MDrv_WriteRegBit(0x10250B, 1, 0x08);
    MDrv_WriteRegBit(0x102503, 0, 0x40);
    MDrv_WriteRegBit(0x102509, 1, 0x04);
    MDrv_WriteRegBit(0x102509, 1, 0x08);
    MDrv_WriteRegBit(0x102509, 1, 0x10);
    MDrv_WriteRegBit(0x10250A, 1, 0x04);
    MDrv_WriteRegBit(0x10250A, 1, 0x08);
    MDrv_WriteRegBit(0x10257E, 1, 0x01);
    MDrv_WriteRegBit(0x10250A, 1, 0x10);
    MDrv_WriteRegBit(0x10250A, 1, 0x20);
    MDrv_WriteRegBit(0x10257E, 1, 0x02);
    MDrv_WriteRegBit(0x102508, 1, 0x04);
    MDrv_WriteRegBit(0x102508, 1, 0x08);
    MDrv_WriteRegBit(0x102508, 1, 0x01);
    MDrv_WriteRegBit(0x102508, 1, 0x02);
    MDrv_WriteRegBit(0x102508, 1, 0x10);
    MDrv_WriteRegBit(0x102505, 0, 0x01);
    MDrv_WriteRegBit(0x102505, 0, 0x02);
    MDrv_WriteRegBit(0x102570, 0, 0x02);
    MDrv_WriteRegBit(0x102570, 0, 0x01);
    MDrv_WriteRegBit(0x102590, 0, 0x08);
    MDrv_WriteRegBit(0x102592, 0, 0x08);
    MDrv_WriteRegBit(0x10250B, 1, 0x01);
    MDrv_WriteRegBit(0x10250B, 1, 0x02);
    MDrv_WriteRegBit(0x10250B, 1, 0x04);
    MDrv_WriteRegBit(0x102509, 1, 0x02);
    MDrv_WriteRegBit(0x10250A, 1, 0x02);
    MDrv_WriteRegBit(0x102509, 1, 0x01);
    MDrv_WriteRegBit(0x102508, 1, 0x20);
    MDrv_WriteRegBit(0x102508, 1, 0x40);
    MDrv_WriteRegBit(0x102508, 1, 0x80);
    MDrv_WriteRegBit(0x102509, 1, 0x40);
    MDrv_WriteRegBit(0x102580, 1, 0x40);
    MDrv_WriteRegBit(0x1025A0, 1, 0x01);
    MDrv_WriteRegBit(0x1025A4, 1, 0x01);
    MDrv_WriteRegBit(0x1025BC, 1, 0x40);
    MDrv_WriteRegBit(0x1025BC, 1, 0x80);
    MDrv_WriteRegBit(0x1025BD, 1, 0x01);
    MDrv_WriteRegBit(0x1025BD, 1, 0x02);
    MDrv_WriteRegBit(0x1025BD, 1, 0x04);
    MDrv_WriteRegBit(0x1025BD, 1, 0x08);
    MDrv_WriteRegBit(0x1025BD, 1, 0x10);
    MDrv_WriteRegBit(0x1025BD, 1, 0x20);
}

static void MDrv_LPLL_PowerDown(void) //OK
{
    MDrv_WriteRegBit(0x1031d8, 1, 0x08);
    MDrv_WriteRegBit(0x1031d8, 1, 0x10);
    MDrv_WriteRegBit(0x103106, 1, 0x20);
    MDrv_WriteRegBit(0x103166, 1, 0x20);
}

static void MDrv_MOD_PowerDown(void) //OK
{
    MDrv_WriteRegBit(0x1032F0, 1, 0x01);
    MDrv_WriteRegBit(0x1032F1, 1, 0x01);
    MDrv_WriteRegBit(0x1032EE, 1, 0x01);
    MDrv_WriteRegBit(0x1032EE, 1, 0x02);
    MDrv_WriteRegBit(0x1032EE, 1, 0x04);
}

static void MDrv_AUSDM_PowerDown(void) //OK
{
    MDrv_WriteRegBit(0x112C20, 1, 0x08);
    MDrv_WriteRegBit(0x112CDA, 1, 0x01);
    MDrv_WriteRegBit(0x112CDA, 1, 0x02);
    MDrv_WriteRegBit(0x112CDD, 1, 0x20);
    MDrv_WriteRegBit(0x112CDD, 1, 0x10);
    MDrv_WriteRegBit(0x112CDD, 1, 0x08);
    MDrv_WriteRegBit(0x112CDD, 1, 0x04);
    MDrv_WriteRegBit(0x112CDD, 1, 0x02);
    MDrv_WriteRegBit(0x112CDD, 1, 0x01);
    MDrv_WriteRegBit(0x112CDC, 1, 0x80);
    MDrv_WriteRegBit(0x112CDC, 1, 0x40);
    MDrv_WriteRegBit(0x112CDC, 1, 0x20);
    MDrv_WriteRegBit(0x112CDC, 1, 0x10);
    MDrv_WriteRegBit(0x112CDE, 1, 0x80);
    MDrv_WriteRegBit(0x112CDE, 1, 0x40);
    MDrv_WriteRegBit(0x112CE1, 1, 0x10);
    MDrv_WriteRegBit(0x112CE0, 1, 0x20);
    MDrv_WriteRegBit(0x112CE0, 1, 0x10);
    MDrv_WriteRegBit(0x112CE3, 1, 0x03);
    MDrv_WriteRegBit(0x112CE6, 1, 0x02);
    MDrv_WriteRegBit(0x112CE6, 1, 0x01);
    MDrv_WriteRegBit(0x112CE9, 1, 0x80);
    MDrv_WriteRegBit(0x112CEA, 1, 0x08);
    MDrv_WriteRegBit(0x112CED, 1, 0x80);
    MDrv_WriteRegBit(0x112CED, 1, 0x08);
}

static void MDrv_AUPLL_PowerDown(void) //OK
{
    MDrv_WriteRegBit(0x112C26, 1, 0x80);
    MDrv_WriteRegBit(0x112C26, 1, 0x08);
    MDrv_WriteRegBit(0x112C26, 1, 0x04);
    MDrv_WriteRegBit(0x112C26, 1, 0x02);
    MDrv_WriteRegBit(0x112C26, 1, 0x01);
}

static void MDrv_USBPLL_PowerDown(void) //OK
{
    MDrv_WriteRegBit(0x103A88, 1, 0x80);
    MDrv_WriteRegBit(0x103A81, 1, 0x80);
    MDrv_WriteRegBit(0x103A81, 1, 0x40);
    MDrv_WriteRegBit(0x103A81, 1, 0x20);
    MDrv_WriteRegBit(0x103A81, 1, 0x10);
    MDrv_WriteRegBit(0x103A81, 1, 0x08);
    MDrv_WriteRegBit(0x103A81, 1, 0x04);
    MDrv_WriteRegBit(0x103A81, 1, 0x02);
    MDrv_WriteRegBit(0x103A81, 1, 0x01);
    MDrv_WriteRegBit(0x103A80, 1, 0x80);
    MDrv_WriteRegBit(0x103A80, 1, 0x40);
    MDrv_WriteRegBit(0x103A80, 1, 0x04);
    MDrv_WriteRegBit(0x103A80, 1, 0x01);
    MDrv_WriteByte(0x103A82, 0x80);
    MDrv_WriteByte(0x103A83, 0x90);
    MDrv_WriteByte(0x103A80, 0xC7);
    MDrv_WriteByte(0x103A81, 0xEF);
}

static void MDrv_DSPPLL_PowerDown(void)
{
    MDrv_WriteRegBit(0x110C43, 1, BIT0);
    MDrv_WriteRegBit(0x110C43, 1, BIT1);
    MDrv_WriteRegBit(0x110C43, 1, BIT2);
}

static void MDrv_DDRPLL_PowerDown(void) //OK
{
    MDrv_WriteRegBit(0x110d00, 1, 0x08);
    MDrv_WriteRegBit(0x110d00, 1, 0x10);
    MDrv_WriteRegBit(0x110d01, 0, 0x04);
    MDrv_WriteRegBit(0x110d01, 0, 0x08);
    MDrv_WriteRegBit(0x110d01, 1, 0x80);
    MDrv_WriteRegBit(0x110d08, 0, 0x00);
    MDrv_WriteRegBit(0x110d60, 1, 0x02);
    MDrv_WriteRegBit(0x110d33, 1, 0x80);
}

static void MDrv_MPLL_PowerDown(void)
{
    //switch 0x112800 bank access right to HK mcu
    MDrv_WriteRegBit(0x101e39, 0, 0x03);
    //MPLL power down
    MDrv_WriteRegBit(0x11286A, 1, 0x08);
    MDrv_WriteRegBit(0x11286B, 1, 0x10);
    MDrv_WriteRegBit(0x11286A, 1, 0x80);
    MDrv_WriteRegBit(0x11286B, 1, 0x20);
    MDrv_WriteRegBit(0x112860, 1, 0x02);
    MDrv_WriteRegBit(0x112860, 1, 0x04);
    MDrv_WriteRegBit(0x112860, 1, 0x08);
    MDrv_WriteRegBit(0x112860, 1, 0x10);
    MDrv_WriteRegBit(0x112860, 1, 0x20);
    MDrv_WriteRegBit(0x112860, 1, 0x40);
    MDrv_WriteRegBit(0x11286C, 0, 0x10);
    MDrv_WriteRegBit(0x11286C, 0, 0x01);
    MDrv_WriteRegBit(0x11286B, 0, 0x40);
    MDrv_WriteRegBit(0x11286B, 0, 0x80);
    MDrv_WriteRegBit(0x11286D, 0, 0x02);
    //switch 0x112800 bank access right to dmd mcu
    MDrv_WriteRegBit(0x101e39, 1, 0x03);

    MDrv_WriteByte(0x100b2c, 0x00); // patch for power saving (MPLL disable issue)
    MDrv_WriteRegBit(0x100b20, 0, 0x01); // patch for power saving (MPLL disable issue)
    MDrv_WriteRegBit(0x000f40, 0, 0x80); // patch for power saving (MPLL disable issue)
    
#if ENABLE_UART2
    MDrv_WriteRegBit(0x110c03, 0, 0x01);
#else
	MDrv_WriteRegBit(0x110c03, 1, 0x01);
#endif

	MDrv_WriteRegBit(0x110c43, 1, 0x01);
}

#if BLOCK_POWER_FUNC
static void MDrv_Block_PowerDown(void)
{
    //(1) Block Codec
    MDrv_WriteRegBit(0x101e3a, 1, BIT0);
    MDrv_WriteRegBit(0x101e1e, 0, BIT1);
    MDrv_WriteRegBit(0x101e1e, 0, BIT5);
    //(2) Block Demod
    MDrv_WriteRegBit(0x101e3a, 1, BIT1);
    MDrv_WriteRegBit(0x101e1e, 0, BIT2);
    MDrv_WriteRegBit(0x101e1e, 0, BIT6);
    //(3) Block SC
    #if ENABLE_SC_BLOCK_SYNC_WAKEUP
    MDrv_WriteRegBit(0x101e3a, 1, BIT2);
    MDrv_WriteRegBit(0x101e1e, 0, BIT0);
    MDrv_WriteRegBit(0x101e1e, 0, BIT4);
    #endif
    //(4) Block Vivaldi
    MDrv_WriteRegBit(0x101e3a, 1, BIT3);
    MDrv_WriteRegBit(0x101e1e, 0, BIT3);
    MDrv_WriteRegBit(0x101e1e, 0, BIT7);

}

void MDrv_Block_PowerUp(void)
{
    //(1) Block Codec
    MDrv_WriteRegBit(0x101e1e, 1, BIT5);
    MDrv_WriteRegBit(0x101e1e, 1, BIT1);
    MDrv_WriteRegBit(0x101e3a, 0, BIT0);
    //(2) Block Demod
    MDrv_WriteRegBit(0x101e1e, 1, BIT6);
    MDrv_WriteRegBit(0x101e1e, 1, BIT2);
    MDrv_WriteRegBit(0x101e3a, 0, BIT1);
    //(3) Block SC
    MDrv_WriteRegBit(0x101e1e, 1, BIT4);
    MDrv_WriteRegBit(0x101e1e, 1, BIT0);
    MDrv_WriteRegBit(0x101e3a, 0, BIT2);
    //(4) Block Vivaldi
    MDrv_WriteRegBit(0x101e1e, 1, BIT7);
    MDrv_WriteRegBit(0x101e1e, 1, BIT3);
    MDrv_WriteRegBit(0x101e3a, 0, BIT3);

}

#endif

//***********************************************************
//              Global Functions Definition
//***********************************************************
void InitialSystemPowerDown(void)
{
    MDrv_Digital_PowerDown();
    MDrv_DVITOP_PowerDown();
    MDrv_Demod_PowerDown();
    MDrv_VideoAtop_PowerDown();
    MDrv_LPLL_PowerDown();
    MDrv_MOD_PowerDown();
    MDrv_AUSDM_PowerDown();
    MDrv_AUPLL_PowerDown();
    MDrv_USBPLL_PowerDown();
    MDrv_DSPPLL_PowerDown();
    MDrv_DDRPLL_PowerDown();
    MDrv_MPLL_PowerDown();
    #if BLOCK_POWER_FUNC
    MDrv_Block_PowerDown();
    #endif
}


