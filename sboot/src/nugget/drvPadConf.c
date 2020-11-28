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
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#include "datatype.h"
#include "drvRIU.h"
#include "Board.h"
#include "c_riubase.h"
#include "hwreg_NUGGET.h"
#include "chip/bond.h"

#define GPIO_NONE               0       // Not GPIO pin (default)
#define GPIO_IN                 1       // GPI
#define GPIO_OUT_LOW            2       // GPO output low
#define GPIO_OUT_HIGH           3       // GPO output high

#define _NUGGET_ENBEDED_FLASH_      0       // 1: with enbeded flash, 0: without enbeded flash

#if defined (MIPS_CHAKRA) || defined(MSOS_TYPE_LINUX)
#define _MapBase_nonPM_NUGGET      (RIU_MAP + 0x200000)
#define _MapBase_PM_NUGGET         RIU_MAP
#else
#define _MapBase_nonPM_NUGGET      0xA0200000
#define _MapBase_PM_NUGGET         0xA0000000
#endif

#define _MEMMAP_nonPM_          _RVM1(0x0000, 0x10, 0xFF)
#define _MEMMAP_PM_             _RVM1(0x0000, 0x00, 0xFF)
#define _MEMMAP_nonPM_SPARE0_   _RVM1(0x0000, 0x12, 0xFF)

const U8 padInitTbl[] =
{
    0x39, 0xB6, 0x5B, 0x53,     // magic code for ISP_Tool

    // programable device number
    // spi flash count
    1 + (PIN_SPI_CZ1 != 0) + (PIN_SPI_CZ2 != 0) + (PIN_SPI_CZ3 != 0),
    0x00,                       // nor
    0x00,                       // nand
    0x00,                       // reserved
    0x00,                       // reserved
    0x00,                       // reserved

//---------------------------------------------------------------------
// GPIO Configuartion
//---------------------------------------------------------------------
    _MEMMAP_PM_,

    #if(PAD_PM_SPI_CZ_IS_GPIO != GPIO_NONE)
    #define PAD_PM_SPI_CZ_OEN (PAD_PM_SPI_CZ_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_PM_SPI_CZ_OUT (PAD_PM_SPI_CZ_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x0e3a, PAD_PM_SPI_CZ_OUT, BIT4),
    _RVM1(0x0e3c, PAD_PM_SPI_CZ_OEN, BIT4),
    //reg_spicsz0_gpio
    _RVM1(0x0e6a, BIT1 , BIT1 ),   //reg[0e6a]#1 = 1
    #endif

    #if(PAD_PM_SPI_CK_IS_GPIO != GPIO_NONE)
    #define PAD_PM_SPI_CK_OEN (PAD_PM_SPI_CK_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_PM_SPI_CK_OUT (PAD_PM_SPI_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x0e3a, PAD_PM_SPI_CK_OUT, BIT5),
    _RVM1(0x0e3c, PAD_PM_SPI_CK_OEN, BIT5),
    //reg_spi_gpio
    _RVM1(0x0e6a, BIT0 , BIT0 ),   //reg[0e6a]#0 = 1
    #endif

    #if(PAD_PM_SPI_DI_IS_GPIO != GPIO_NONE)
    #define PAD_PM_SPI_DI_OEN (PAD_PM_SPI_DI_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_PM_SPI_DI_OUT (PAD_PM_SPI_DI_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x0e3a, PAD_PM_SPI_DI_OUT, BIT6),
    _RVM1(0x0e3c, PAD_PM_SPI_DI_OEN, BIT6),
    //reg_spi_gpio
    _RVM1(0x0e6a, BIT0 , BIT0 ),   //reg[0e6a]#0 = 1
    #endif

    #if(PAD_PM_SPI_DO_IS_GPIO != GPIO_NONE)
    #define PAD_PM_SPI_DO_OEN (PAD_PM_SPI_DO_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_PM_SPI_DO_OUT (PAD_PM_SPI_DO_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x0e3a, PAD_PM_SPI_DO_OUT, BIT7),
    _RVM1(0x0e3c, PAD_PM_SPI_DO_OEN, BIT7),
    //reg_spi_gpio
    _RVM1(0x0e6a, BIT0 , BIT0 ),   //reg[0e6a]#0 = 1
    #endif

    #if(PAD_PM_LED_IS_GPIO != GPIO_NONE)
    #define PAD_PM_LED_OEN (PAD_PM_LED_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_PM_LED_OUT (PAD_PM_LED_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x0e0b, PAD_PM_LED_OUT, BIT6),
    _RVM1(0x0e0b, PAD_PM_LED_OEN, BIT5),
    #endif

    #if(PAD_IRIN_IS_GPIO != GPIO_NONE)
    #define PAD_IRIN_OEN (PAD_IRIN_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_IRIN_OUT (PAD_IRIN_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x0e3a, PAD_IRIN_OUT, BIT0),
    _RVM1(0x0e3c, PAD_IRIN_OEN, BIT0),
    //reg_ir_is_gpio
    _RVM1(0x0e38, BIT4 , BIT4 ),   //reg[0e38]#4 = 1
    #endif

    #if(PAD_CEC_IS_GPIO != GPIO_NONE)
    #define PAD_CEC_OEN (PAD_CEC_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_CEC_OUT (PAD_CEC_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x0e3a, PAD_CEC_OUT, BIT2),
    _RVM1(0x0e3c, PAD_CEC_OEN, BIT2),
    //reg_cec_is_gpio
    _RVM1(0x0e38, BIT6 , BIT6 ),   //reg[0e38]#6 = 1
    #endif

    #if(PAD_GPIO_PM0_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM0_OEN (PAD_GPIO_PM0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO_PM0_OUT (PAD_GPIO_PM0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x0e20, PAD_GPIO_PM0_OUT, BIT0),
    _RVM1(0x0e1e, PAD_GPIO_PM0_OEN, BIT0),
    //default is GPIO
    #endif

    #if(PAD_GPIO_PM1_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM1_OEN (PAD_GPIO_PM1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_GPIO_PM1_OUT (PAD_GPIO_PM1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0e20, PAD_GPIO_PM1_OUT, BIT1),
    _RVM1(0x0e1e, PAD_GPIO_PM1_OEN, BIT1),
    #endif

    #if(PAD_GPIO_PM2_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM2_OEN (PAD_GPIO_PM2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_GPIO_PM2_OUT (PAD_GPIO_PM2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x0e20, PAD_GPIO_PM2_OUT, BIT2),
    _RVM1(0x0e1e, PAD_GPIO_PM2_OEN, BIT2),
    #endif

    #if(PAD_GPIO_PM3_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM3_OEN (PAD_GPIO_PM3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_GPIO_PM3_OUT (PAD_GPIO_PM3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x0e20, PAD_GPIO_PM3_OUT, BIT3),
    _RVM1(0x0e1e, PAD_GPIO_PM3_OEN, BIT3),
    #endif

    #if(PAD_GPIO_PM4_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM4_OEN (PAD_GPIO_PM4_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_GPIO_PM4_OUT (PAD_GPIO_PM4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x0e20, PAD_GPIO_PM4_OUT, BIT4),
    _RVM1(0x0e1e, PAD_GPIO_PM4_OEN, BIT4),
    //reg_gpio_pm_lock
    _RVM1(0x0e24,  0xbe, 0xFFFF),   //reg[0e24] = 'hbe
    _RVM1(0xoe25,  0xba, 0xFFFF),   //reg[oe25] = 'hba
    #endif

    #if(PAD_GPIO_PM5_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM5_OEN (PAD_GPIO_PM5_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_GPIO_PM5_OUT (PAD_GPIO_PM5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x0e20, PAD_GPIO_PM5_OUT, BIT5),
    _RVM1(0x0e1e, PAD_GPIO_PM5_OEN, BIT5),
    //default is GPIO
    #endif

    #if(PAD_GPIO_PM6_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM6_OEN (PAD_GPIO_PM6_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_GPIO_PM6_OUT (PAD_GPIO_PM6_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x0e20, PAD_GPIO_PM6_OUT, BIT6),
    _RVM1(0x0e1e, PAD_GPIO_PM6_OEN, BIT6),
    //reg_spicsz1_gpio
    _RVM1(0x0e6a, BIT2 , BIT2 ),   //reg[0e6a]#2 = 1
    #endif

    #if(PAD_GPIO_PM7_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM7_OEN (PAD_GPIO_PM7_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_GPIO_PM7_OUT (PAD_GPIO_PM7_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x0e20, PAD_GPIO_PM7_OUT, BIT7),
    _RVM1(0x0e1e, PAD_GPIO_PM7_OEN, BIT7),
    //default is GPIO
    #endif

    #if(PAD_GPIO_PM8_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM8_OEN (PAD_GPIO_PM8_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO_PM8_OUT (PAD_GPIO_PM8_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x0e21, PAD_GPIO_PM8_OUT, BIT0),
    _RVM1(0x0e1f, PAD_GPIO_PM8_OEN, BIT0),
    #endif

    #if(PAD_GPIO_PM9_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM9_OEN (PAD_GPIO_PM9_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_GPIO_PM9_OUT (PAD_GPIO_PM9_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0e21, PAD_GPIO_PM9_OUT, BIT1),
    _RVM1(0x0e1f, PAD_GPIO_PM9_OEN, BIT1),
    #endif

    #if(PAD_GPIO_PM10_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM10_OEN (PAD_GPIO_PM10_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_GPIO_PM10_OUT (PAD_GPIO_PM10_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x0e21, PAD_GPIO_PM10_OUT, BIT2),
    _RVM1(0x0e1f, PAD_GPIO_PM10_OEN, BIT2),
    //reg_spicsz2_gpio
    _RVM1(0x0e6a, 0, BIT3 ),   //reg[0e6a]#3 = 0
    #endif

    #if(PAD_GPIO_PM11_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM11_OEN (PAD_GPIO_PM11_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_GPIO_PM11_OUT (PAD_GPIO_PM11_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x0e21, PAD_GPIO_PM11_OUT, BIT3),
    _RVM1(0x0e1f, PAD_GPIO_PM11_OEN, BIT3),
    //default is GPIO
    #endif

    #if(PAD_GPIO_PM12_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM12_OEN (PAD_GPIO_PM12_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_GPIO_PM12_OUT (PAD_GPIO_PM12_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x0e21, PAD_GPIO_PM12_OUT, BIT4),
    _RVM1(0x0e1f, PAD_GPIO_PM12_OEN, BIT4),
    //default is GPIO
    #endif

    #if(PAD_GPIO_PM13_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM13_OEN (PAD_GPIO_PM13_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_GPIO_PM13_OUT (PAD_GPIO_PM13_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x0e21, PAD_GPIO_PM13_OUT, BIT5),
    _RVM1(0x0e1f, PAD_GPIO_PM13_OEN, BIT5),
    //reg_mhl_cable_detect_sel
    _RVM1(0x0ee4, 0, BIT6 ),   //reg[0ee4] #6 = 0b
    #endif

    #if(PAD_GPIO_PM14_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM14_OEN (PAD_GPIO_PM14_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_GPIO_PM14_OUT (PAD_GPIO_PM14_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x0e21, PAD_GPIO_PM14_OUT, BIT6),
    _RVM1(0x0e1f, PAD_GPIO_PM14_OEN, BIT6),
    //reg_vbus_en_sel
    _RVM1(0x0ee4, 0, BIT7 ),   //reg[0ee4] #7 = 0b
    #endif

    #if(PAD_GPIO_PM15_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM15_OEN (PAD_GPIO_PM15_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_GPIO_PM15_OUT (PAD_GPIO_PM15_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x0e21, PAD_GPIO_PM15_OUT, BIT7),
    _RVM1(0x0e1f, PAD_GPIO_PM15_OEN, BIT7),
    //reg_cbus_debug_sel
    _RVM1(0x0ee5, 0, BIT0 ),   //reg[0ee5] #0 = 0b
    #endif

    #if(PAD_HOTPLUGA_IS_GPIO != GPIO_NONE)
    #define PAD_HOTPLUGA_OEN (PAD_HOTPLUGA_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_HOTPLUGA_OUT (PAD_HOTPLUGA_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x0e4e, PAD_HOTPLUGA_OUT, BIT4),
    _RVM1(0x0e4e, PAD_HOTPLUGA_OEN, BIT0),
    //default is GPIO
    #endif

    #if(PAD_HOTPLUGB_IS_GPIO != GPIO_NONE)
    #define PAD_HOTPLUGB_OEN (PAD_HOTPLUGB_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_HOTPLUGB_OUT (PAD_HOTPLUGB_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x0e4e, PAD_HOTPLUGB_OUT, BIT5),
    _RVM1(0x0e4e, PAD_HOTPLUGB_OEN, BIT1),
    //default is GPIO
    #endif

    #if(PAD_HOTPLUGC_IS_GPIO != GPIO_NONE)
    #define PAD_HOTPLUGC_OEN (PAD_HOTPLUGC_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_HOTPLUGC_OUT (PAD_HOTPLUGC_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x0e4e, PAD_HOTPLUGC_OUT, BIT6),
    _RVM1(0x0e4e, PAD_HOTPLUGC_OEN, BIT2),
    //reg_hplugc_mhl_en
    _RVM1(0x0ee6, 0, BIT0 ),   //reg[0ee6] #0 = 0b
    //only 1.8V for output High
    #endif

    #if(PAD_HOTPLUGD_IS_GPIO != GPIO_NONE)
    #define PAD_HOTPLUGD_OEN (PAD_HOTPLUGD_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_HOTPLUGD_OUT (PAD_HOTPLUGD_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x0e4e, PAD_HOTPLUGD_OUT, BIT7),
    _RVM1(0x0e4e, PAD_HOTPLUGD_OEN, BIT3),
    //reg_hplugc_mhl_en
    _RVM1(0x0ee6, 0, BIT0 ),   //reg[0ee6] #0 = 0b
    //reg_mhl_plugc_en
    _RVM1(0x2f62, 0, BIT 1 ),   //reg[2f62] # 1 = 0b
    //only 1.8V for output High
    #endif

    #if(PAD_DDCDA_CK_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDA_CK_OEN (PAD_DDCDA_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_DDCDA_CK_OUT (PAD_DDCDA_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x0496, PAD_DDCDA_CK_OUT, BIT2),
    _RVM1(0x0496, PAD_DDCDA_CK_OEN, BIT1),
    //reg_gpio2do_en
    _RVM1(0x0496, BIT7 , BIT7 ),   //reg[0496]#7 = 1
    #endif

    #if(PAD_DDCDA_DA_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDA_DA_OEN (PAD_DDCDA_DA_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_DDCDA_DA_OUT (PAD_DDCDA_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x0496, PAD_DDCDA_DA_OUT, BIT6),
    _RVM1(0x0496, PAD_DDCDA_DA_OEN, BIT5),
    //reg_gpio2do_en
    _RVM1(0x0496, BIT7 , BIT7 ),   //reg[0496]#7 = 1
    #endif

    #if(PAD_DDCDB_CK_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDB_CK_OEN (PAD_DDCDB_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_DDCDB_CK_OUT (PAD_DDCDB_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x0497, PAD_DDCDB_CK_OUT, BIT2),
    _RVM1(0x0497, PAD_DDCDB_CK_OEN, BIT1),
    //reg_gpio2d1_en
    _RVM1(0x0497, BIT7 , BIT7 ),   //reg[0497]#7 = 1
    #endif

    #if(PAD_DDCDB_DA_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDB_DA_OEN (PAD_DDCDB_DA_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_DDCDB_DA_OUT (PAD_DDCDB_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x0497, PAD_DDCDB_DA_OUT, BIT6),
    _RVM1(0x0497, PAD_DDCDB_DA_OEN, BIT5),
    //reg_gpio2d1_en
    _RVM1(0x0497, BIT7 , BIT7 ),   //reg[0497]#7 = 1
    #endif

    #if(PAD_DDCDC_CK_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDC_CK_OEN (PAD_DDCDC_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_DDCDC_CK_OUT (PAD_DDCDC_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x0498, PAD_DDCDC_CK_OUT, BIT2),
    _RVM1(0x0498, PAD_DDCDC_CK_OEN, BIT1),
    //reg_gpio2d2_en
    _RVM1(0x0498, BIT7 , BIT7 ),   //reg[0498]#7 = 1
    #endif

    #if(PAD_DDCDC_DA_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDC_DA_OEN (PAD_DDCDC_DA_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_DDCDC_DA_OUT (PAD_DDCDC_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x0498, PAD_DDCDC_DA_OUT, BIT6),
    _RVM1(0x0498, PAD_DDCDC_DA_OEN, BIT5),
    //reg_gpio2d2_en
    _RVM1(0x0498, BIT7 , BIT7 ),   //reg[0498]#7 = 1
    #endif

    #if(PAD_DDCDD_CK_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDD_CK_OEN (PAD_DDCDD_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_DDCDD_CK_OUT (PAD_DDCDD_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x0499, PAD_DDCDD_CK_OUT, BIT2),
    _RVM1(0x0499, PAD_DDCDD_CK_OEN, BIT1),
    //reg_gpio2d3_en
    _RVM1(0x0499, BIT7 , BIT7 ),   //reg[0499]#7 = 1
    #endif

    #if(PAD_DDCDD_DA_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDD_DA_OEN (PAD_DDCDD_DA_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_DDCDD_DA_OUT (PAD_DDCDD_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x0499, PAD_DDCDD_DA_OUT, BIT6),
    _RVM1(0x0499, PAD_DDCDD_DA_OEN, BIT5),
    //reg_gpio2d3_en
    _RVM1(0x0499, BIT7 , BIT7 ),   //reg[0499]#7 = 1
    #endif

    #if(PAD_SAR0_IS_GPIO != GPIO_NONE)
    #define PAD_SAR0_OEN (PAD_SAR0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_SAR0_OUT (PAD_SAR0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1424, PAD_SAR0_OUT, BIT0),
    _RVM1(0x1423, PAD_SAR0_OEN, BIT0),
    //reg_sar_aisel[0]
    _RVM1(0x1422, 0, BIT0 ),   //reg[1422]#0 = 0
    #endif

    #if(PAD_SAR1_IS_GPIO != GPIO_NONE)
    #define PAD_SAR1_OEN (PAD_SAR1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_SAR1_OUT (PAD_SAR1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1424, PAD_SAR1_OUT, BIT1),
    _RVM1(0x1423, PAD_SAR1_OEN, BIT1),
    //reg_sar_aisel[1]
    _RVM1(0x1422, 0, BIT1 ),   //reg[1422]#1 = 0
    #endif

    #if(PAD_SAR2_IS_GPIO != GPIO_NONE)
    #define PAD_SAR2_OEN (PAD_SAR2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_SAR2_OUT (PAD_SAR2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1424, PAD_SAR2_OUT, BIT2),
    _RVM1(0x1423, PAD_SAR2_OEN, BIT2),
    //reg_sar_aisel[2]
    _RVM1(0x1422, 0, BIT2 ),   //reg[1422]#2 = 0
    #endif

    #if(PAD_SAR3_IS_GPIO != GPIO_NONE)
    #define PAD_SAR3_OEN (PAD_SAR3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_SAR3_OUT (PAD_SAR3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1424, PAD_SAR3_OUT, BIT3),
    _RVM1(0x1423, PAD_SAR3_OEN, BIT3),
    //reg_sar_aisel[3]
    _RVM1(0x1422, 0, BIT3 ),   //reg[1422]#3 = 0
    #endif

    #if(PAD_SAR4_IS_GPIO != GPIO_NONE)
    #define PAD_SAR4_OEN (PAD_SAR4_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_SAR4_OUT (PAD_SAR4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1424, PAD_SAR4_OUT, BIT4),
    _RVM1(0x1423, PAD_SAR4_OEN, BIT4),
    //reg_sar_aisel[4]
    _RVM1(0x1422, 0, BIT4 ),   //reg[1422]#4 = 0
    #endif


    _MEMMAP_nonPM_,
	
    #if(PAD_GPIO0_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO0_OEN (PAD_GPIO0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO0_OUT (PAD_GPIO0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e56, PAD_GPIO0_OUT, BIT0),
    _RVM1(0x1e5C, PAD_GPIO0_OEN, BIT0),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5| BIT4 ),   //reg[101e05]#5 ~ #4 = 00b
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_usbdrvvbusconfig[1:0]
    _RVM1(0x1e04, 0, BIT1|BIT0 ),   //reg[101e04]#1 ~ #0 = 00b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    //reg_p1_enable_b0
    _RVM1(0x1eb8, 0, BIT0 ),   //reg[101eb8]#0 = 0b
    #endif

    #if(PAD_GPIO1_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO1_OEN (PAD_GPIO1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_GPIO1_OUT (PAD_GPIO1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e56, PAD_GPIO1_OUT, BIT1),
    _RVM1(0x1e5C, PAD_GPIO1_OEN, BIT1),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5|BIT4 ),   //reg[101e05]#5 ~ #4 = 00b
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    //reg_p1_enable_b2
    _RVM1(0x1eb8, 0, BIT2 ),   //reg[101eb8]#2 = 0b
    #endif

    #if(PAD_GPIO2_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO2_OEN (PAD_GPIO2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_GPIO2_OUT (PAD_GPIO2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e56, PAD_GPIO2_OUT, BIT2),
    _RVM1(0x1e5C, PAD_GPIO2_OEN, BIT2),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5|BIT4 ),   //reg[101e05]#5 ~ #4 = 00b
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_seconduartmode[1:0]
    _RVM1(0x1e05, 0, BIT1|BIT0 ),   //reg[101e05]#1 ~ #0 = 00b
    //reg_od2nduart[1:0]
    _RVM1(0x1eb6, 0, BIT1|BIT0 ),   //reg[101eb6]#1 ~ #0 = 00b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    //reg_p1_enable_b3
    _RVM1(0x1eb8, 0, BIT3 ),   //reg[101eb8]#3 = 0b
    #endif

    #if(PAD_GPIO3_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO3_OEN (PAD_GPIO3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_GPIO3_OUT (PAD_GPIO3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e56, PAD_GPIO3_OUT, BIT3),
    _RVM1(0x1e5C, PAD_GPIO3_OEN, BIT3),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5|BIT4 ),   //reg[101e05]#5 ~ #4 = 00b
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_seconduartmode[1:0]
    _RVM1(0x1e05, 0, BIT1|BIT0 ),   //reg[101e05]#1 ~ #0 = 00b
    //reg_od2nduart[1:0]
    _RVM1(0x1eb6, 0, BIT1|BIT0 ),   //reg[101eb6]#1 ~ #0 = 00b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    //reg_p1_enable_b4
    _RVM1(0x1eb8, 0, BIT4 ),   //reg[101eb8]#4 = 0b
    #endif

    #if(PAD_GPIO4_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO4_OEN (PAD_GPIO4_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_GPIO4_OUT (PAD_GPIO4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e56, PAD_GPIO4_OUT, BIT4),
    _RVM1(0x1e5C, PAD_GPIO4_OEN, BIT4),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5|BIT4 ),   //reg[101e05]#5 ~ #4 = 00b
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_fastuartmode[1:0]
    _RVM1(0x1e04, 0, BIT5|BIT4 ),   //reg[101e04]#5 ~ #4 = 00b
    //reg_odfastuart[1:0]
    _RVM1(0x1eb6, 0, BIT7|BIT6 ),   //reg[101eb6]#7 ~ #6 = 00b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    //reg_p1_enable_b5
    _RVM1(0x1eb8, 0, BIT5 ),   //reg[101eb8]#5 = 0b
    #endif

    #if(PAD_GPIO5_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO5_OEN (PAD_GPIO5_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_GPIO5_OUT (PAD_GPIO5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e56, PAD_GPIO5_OUT, BIT5),
    _RVM1(0x1e5C, PAD_GPIO5_OEN, BIT5),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5|BIT4 ),   //reg[101e05]#5 ~ #4 = 00b
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_fastuartmode[1:0]
    _RVM1(0x1e04, 0, BIT5|BIT4 ),   //reg[101e04]#5 ~ #4 = 00b
    //reg_odfastuart[1:0]
    _RVM1(0x1eb6, 0, BIT7|BIT6 ),   //reg[101eb6]#7 ~ #6 = 00b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    //reg_p1_enable_b6
    _RVM1(0x1eb8, 0, BIT6 ),   //reg[101eb8]#6 = 0b
    #endif

    #if(PAD_GPIO6_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO6_OEN (PAD_GPIO6_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_GPIO6_OUT (PAD_GPIO6_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e56, PAD_GPIO6_OUT, BIT6),
    _RVM1(0x1e5C, PAD_GPIO6_OEN, BIT6),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_seconduartmode[1:0]
    _RVM1(0x1e05, 0, BIT1|BIT0 ),   //reg[101e05]#1 ~ #0 = 00b
    //reg_od2nduart[1:0]
    _RVM1(0x1eb6, 0, BIT1|BIT0 ),   //reg[101eb6]#1 ~ #0 = 00b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    //reg_p1_enable_b7
    _RVM1(0x1eb8, 0, BIT7 ),   //reg[101eb8]#7 = 0b
    #endif

    #if(PAD_GPIO7_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO7_OEN (PAD_GPIO7_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_GPIO7_OUT (PAD_GPIO7_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e56, PAD_GPIO7_OUT, BIT7),
    _RVM1(0x1e5C, PAD_GPIO7_OEN, BIT7),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_seconduartmode[1:0]
    _RVM1(0x1e05, 0, BIT1|BIT0 ),   //reg[101e05]#1 ~ #0 = 00b
    //reg_od2nduart[1:0]
    _RVM1(0x1eb6, 0, BIT1|BIT0 ),   //reg[101eb6]#1 ~ #0 = 00b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1|BIT0 ),   //reg[101e9f]#1 ~ #0 = 00b
    #endif

    #if(PAD_GPIO8_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO8_OEN (PAD_GPIO8_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO8_OUT (PAD_GPIO8_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e57, PAD_GPIO8_OUT, BIT0),
    _RVM1(0x1e5D, PAD_GPIO8_OEN, BIT0),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_thirduartmode[1:0]
    _RVM1(0x1e05, 0, BIT3|BIT2 ),   //reg[101e05]#3 ~ #2 = 00b
    //reg_od3rduart[1:0]
    _RVM1(0x1eb6, 0, BIT3|BIT2 ),   //reg[101eb6]#3 ~ #2 = 00b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1|BIT0 ),   //reg[101e9f]#1 ~ #0 = 00b
    #endif

    #if(PAD_GPIO9_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO9_OEN (PAD_GPIO9_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_GPIO9_OUT (PAD_GPIO9_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e57, PAD_GPIO9_OUT, BIT1),
    _RVM1(0x1e5D, PAD_GPIO9_OEN, BIT1),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_thirduartmode[1:0]
    _RVM1(0x1e05, 0, BIT3|BIT2 ),   //reg[101e05]#3 ~ #2 = 00b
    //reg_od3rduart[1:0]
    _RVM1(0x1eb6, 0, BIT3|BIT2 ),   //reg[101eb6]#3 ~ #2 = 00b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1|BIT0 ),   //reg[101e9f]#1 ~ #0 = 00b
    #endif

    #if(PAD_GPIO10_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO10_OEN (PAD_GPIO10_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_GPIO10_OUT (PAD_GPIO10_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e57, PAD_GPIO10_OUT, BIT2),
    _RVM1(0x1e5D, PAD_GPIO10_OEN, BIT2),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_fourthuartmode[1:0]
    _RVM1(0x1e04, 0, BIT7|BIT6 ),   //reg[101e04]#7 ~ #6 = 00b
    //reg_od4rduart[1:0]
    _RVM1(0x1eb6, 0, BIT5|BIT4 ),   //reg[101eb6]#5 ~ #4 = 00b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1|BIT0 ),   //reg[101e9f]#1 ~ #0 = 00b
    #endif

    #if(PAD_GPIO11_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO11_OEN (PAD_GPIO11_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_GPIO11_OUT (PAD_GPIO11_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e57, PAD_GPIO11_OUT, BIT3),
    _RVM1(0x1e5D, PAD_GPIO11_OEN, BIT3),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_mpif_mode[1:0]
    _RVM1(0x1eb5, 0, BIT7|BIT6 ),   //reg[101eb5]#7 ~ #6 = 00b
    //reg_fourthuartmode[1:0]
    _RVM1(0x1e04, 0, BIT7|BIT6 ),   //reg[101e04]#7 ~ #6 = 00b
    //reg_od4rduart[1:0]
    _RVM1(0x1eb6, 0, BIT5|BIT4 ),   //reg[101eb6]#5 ~ #4 = 00b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1|BIT0 ),   //reg[101e9f]#1 ~ #0 = 00b
    #endif

    #if(PAD_GPIO12_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO12_OEN (PAD_GPIO12_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_GPIO12_OUT (PAD_GPIO12_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e57, PAD_GPIO12_OUT, BIT4),
    _RVM1(0x1e5D, PAD_GPIO12_OEN, BIT4),
    #endif

    #if(PAD_GPIO13_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO13_OEN (PAD_GPIO13_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_GPIO13_OUT (PAD_GPIO13_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e57, PAD_GPIO13_OUT, BIT5),
    _RVM1(0x1e5D, PAD_GPIO13_OEN, BIT5),
    #endif

    #if(PAD_GPIO14_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO14_OEN (PAD_GPIO14_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_GPIO14_OUT (PAD_GPIO14_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e57, PAD_GPIO14_OUT, BIT6),
    _RVM1(0x1e5D, PAD_GPIO14_OEN, BIT6),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_i2smutemode[1:0]
    _RVM1(0x1e05, 0, BIT7|BIT6 ),   //reg[101e05]#7 ~ #6 = 00b
    //reg_mpif_mode[1:0]
    _RVM1(0x1eb5, 0, BIT7|BIT6 ),   //reg[101eb5]#7 ~ #6 = 00b
    #endif

    #if(PAD_GPIO15_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO15_OEN (PAD_GPIO15_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_GPIO15_OUT (PAD_GPIO15_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e57, PAD_GPIO15_OUT, BIT7),
    _RVM1(0x1e5D, PAD_GPIO15_OEN, BIT7),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_mpif_mode[1:0]
    _RVM1(0x1eb5, 0, BIT7|BIT6 ),   //reg[101eb5]#7 ~ #6 = 00b
    //reg_3dflagconfig[1:0]
    _RVM1(0x1eb3, 0, BIT7|BIT6 ),   //reg[101eb3]#7 ~ #6 = 00b
    //reg_tserrout[1:0]
    _RVM1(0x1ea2, 0, BIT7 ),   //reg[101ea2]#7 = 0b
    #endif

    #if(PAD_GPIO16_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO16_OEN (PAD_GPIO16_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO16_OUT (PAD_GPIO16_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e58, PAD_GPIO16_OUT, BIT0),
    _RVM1(0x1e5E, PAD_GPIO16_OEN, BIT0),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_mpif_mode[1:0]
    _RVM1(0x1eb5, 0, BIT7|BIT6 ),   //reg[101eb5]#7 ~ #6 = 00b
    //reg_miic_mode0[1:0]
    _RVM1(0x1eb5, 0, BIT1|BIT0 ),   //reg[101eb5]#1 ~ #0 = 00b
    #endif

    #if(PAD_GPIO17_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO17_OEN (PAD_GPIO17_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_GPIO17_OUT (PAD_GPIO17_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e58, PAD_GPIO17_OUT, BIT1),
    _RVM1(0x1e5E, PAD_GPIO17_OEN, BIT1),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_mpif_mode[1:0]
    _RVM1(0x1eb5, 0, BIT7|BIT6 ),   //reg[101eb5]#7 ~ #6 = 00b
    //reg_miic_mode0[1:0]
    _RVM1(0x1eb5, 0, BIT1|BIT0 ),   //reg[101eb5]#1 ~ #0 = 00b
    #endif

    #if(PAD_GPIO18_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO18_OEN (PAD_GPIO18_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_GPIO18_OUT (PAD_GPIO18_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e58, PAD_GPIO18_OUT, BIT2),
    _RVM1(0x1e5E, PAD_GPIO18_OEN, BIT2),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0  ),   //reg[101edf]#0  = 0b
    //reg_led_mode[1:0]
    _RVM1(0x1eb4, 0, BIT5|BIT4 ),   //reg[101eb4]#5 ~ #4 = 00b
    //reg_et_test_mode[1:0]
    _RVM1(0x1edf, 0, BIT3|BIT2 ),   //reg[101edf]#3 ~ #2 = 00b
    //reg_seconduartmode[1:0]
    _RVM1(0x1e05, 0, BIT1|BIT0 ),   //reg[101e05]#1 ~ #0 = 00b
    //reg_od2nduart[1:0]
    _RVM1(0x1eb6, 0, BIT1|BIT0 ),   //reg[101eb6]#1 ~ #0 = 00b
    #endif

    #if(PAD_GPIO19_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO19_OEN (PAD_GPIO19_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_GPIO19_OUT (PAD_GPIO19_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e58, PAD_GPIO19_OUT, BIT3),
    _RVM1(0x1e5E, PAD_GPIO19_OEN, BIT3),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0  ),   //reg[101edf]#0  = 0b
    //reg_led_mode[1:0]
    _RVM1(0x1eb4, 0, BIT5|BIT4 ),   //reg[101eb4]#5 ~ #4 = 00b
    //reg_et_test_mode[1:0]
    _RVM1(0x1edf, 0, BIT3|BIT2 ),   //reg[101edf]#3 ~ #2 = 00b
    //reg_seconduartmode[1:0]
    _RVM1(0x1e05, 0, BIT1|BIT0 ),   //reg[101e05]#1 ~ #0 = 00b
    //reg_od2nduart[1:0]
    _RVM1(0x1eb6, 0, BIT1|BIT0 ),   //reg[101eb6]#1 ~ #0 = 00b
    #endif

    #if(PAD_GPIO20_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO20_OEN (PAD_GPIO20_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_GPIO20_OUT (PAD_GPIO20_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e58, PAD_GPIO20_OUT, BIT4),
    _RVM1(0x1e5E, PAD_GPIO20_OEN, BIT4),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0  ),   //reg[101edf]#0  = 0b
    //reg_et_test_mode[1:0]
    _RVM1(0x1edf, 0, BIT3|BIT2 ),   //reg[101edf]#3 ~ #2 = 00b
    //reg_od3rduart[1:0]
    _RVM1(0x1eb6, 0, BIT3|BIT2 ),   //reg[101eb6]#3 ~ #2 = 00b
    //reg_extint5
    _RVM1(0x1ee0, 0, BIT5 ),   //reg[101ee0]#5 = 0b
    #endif

    #if(PAD_GPIO21_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO21_OEN (PAD_GPIO21_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_GPIO21_OUT (PAD_GPIO21_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e58, PAD_GPIO21_OUT, BIT5),
    _RVM1(0x1e5E, PAD_GPIO21_OEN, BIT5),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0  ),   //reg[101edf]#0  = 0b
    //reg_et_test_mode[1:0]
    _RVM1(0x1edf, 0, BIT3|BIT2 ),   //reg[101edf]#3 ~ #2 = 00b
    //reg_od3rduart[1:0]
    _RVM1(0x1eb6, 0, BIT3|BIT2 ),   //reg[101eb6]#3 ~ #2 = 00b
    #endif

    #if(PAD_GPIO22_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO22_OEN (PAD_GPIO22_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_GPIO22_OUT (PAD_GPIO22_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e58, PAD_GPIO22_OUT, BIT6),
    _RVM1(0x1e5E, PAD_GPIO22_OEN, BIT6),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0  ),   //reg[101edf]#0  = 0b
    //reg_et_test_mode[1:0]
    _RVM1(0x1edf, 0, BIT3|BIT2 ),   //reg[101edf]#3 ~ #2 = 00b
    //reg_fourthuartmode[1:0]
    _RVM1(0x1e04, 0, BIT7|BIT6 ),   //reg[101e04]#7 ~ #6 = 00b
    //reg_od4thuart[1:0]
    _RVM1(0x1eb6, 0, BIT5|BIT4 ),   //reg[101eb6]#5 ~ #4 = 00b
    #endif

    #if(PAD_GPIO23_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO23_OEN (PAD_GPIO23_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_GPIO23_OUT (PAD_GPIO23_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e58, PAD_GPIO23_OUT, BIT7),
    _RVM1(0x1e5E, PAD_GPIO23_OEN, BIT7),
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0  ),   //reg[101edf]#0  = 0b
    //reg_et_test_mode[1:0]
    _RVM1(0x1edf, 0, BIT3|BIT2 ),   //reg[101edf]#3 ~ #2 = 00b
    //reg_fourthuartmode[1:0]
    _RVM1(0x1e04, 0, BIT7|BIT6 ),   //reg[101e04]#7 ~ #6 = 00b
    //reg_od4thuart[1:0]
    _RVM1(0x1eb6, 0, BIT5|BIT4 ),   //reg[101eb6]#5 ~ #4 = 00b
    #endif

    #if(PAD_GPIO24_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO24_OEN (PAD_GPIO24_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO24_OUT (PAD_GPIO24_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e59, PAD_GPIO24_OUT, BIT0),
    _RVM1(0x1e5F, PAD_GPIO24_OEN, BIT0),
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0  ),   //reg[101edf]#0  = 0b
    //reg_et_test_mode[1:0]
    _RVM1(0x1edf, 0, BIT3|BIT2 ),   //reg[101edf]#3 ~ #2 = 00b
    //reg_fastuartmode[1:0]
    _RVM1(0x1e04, 0, BIT5|BIT4 ),   //reg[101e04]#5 ~ #4 = 00b
    //reg_odfastuart[1:0]
    _RVM1(0x1eb6, 0, BIT7|BIT6 ),   //reg[101eb6]#7 ~ #6 = 00b
    //reg_extint1
    _RVM1(0x1ee0, 0, BIT1 ),   //reg[101ee0]#1 = 0b
    #endif

    #if(PAD_GPIO25_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO25_OEN (PAD_GPIO25_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_GPIO25_OUT (PAD_GPIO25_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e59, PAD_GPIO25_OUT, BIT1),
    _RVM1(0x1e5F, PAD_GPIO25_OEN, BIT1),
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0  ),   //reg[101edf]#0  = 0b
    //reg_led_mode
    _RVM1(0x1eb4, 0, BIT5|BIT4 ),   //reg[101eb4]#5 ~ #4 = 00b
    //reg_et_test_mode[1:0]
    _RVM1(0x1edf, 0, BIT3|BIT2 ),   //reg[101edf]#3 ~ #2 = 00b
    //reg_usbdrvvbusconfig[1:0]
    _RVM1(0x1e04, 0, BIT1|BIT0 ),   //reg[101e04]#1 ~ #0 = 00b
    //reg_fastuartmode[1:0]
    _RVM1(0x1e04, 0, BIT5|BIT4 ),   //reg[101e04]#5 ~ #4 = 00b
    //reg_odfastuart[1:0]
    _RVM1(0x1eb6, 0, BIT7|BIT6 ),   //reg[101eb6]#7 ~ #6 = 00b
    //reg_extint7
    _RVM1(0x1ee0, 0, BIT7 ),   //reg[101ee0]#7 = 0b
    #endif

    #if(PAD_GPIO26_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO26_OEN (PAD_GPIO26_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_GPIO26_OUT (PAD_GPIO26_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e59, PAD_GPIO26_OUT, BIT2),
    _RVM1(0x1e5F, PAD_GPIO26_OEN, BIT2),
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0  ),   //reg[101edf]#0  = 0b
    //reg_led_mode
    _RVM1(0x1eb4, 0, BIT5|BIT4 ),   //reg[101eb4]#5 ~ #4 = 00b
    //reg_et_test_mode[1:0]
    _RVM1(0x1edf, 0, BIT3|BIT2 ),   //reg[101edf]#3 ~ #2 = 00b
    //reg_usbdrvvbusconfig[1:0]
    _RVM1(0x1e04, 0, BIT1|BIT0 ),   //reg[101e04]#1 ~ #0 = 00b
    //reg_extint4
    _RVM1(0x1ee0, 0, BIT4 ),   //reg[101ee0]#4 = 0b
    #endif

    #if(PAD_GPIO27_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO27_OEN (PAD_GPIO27_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_GPIO27_OUT (PAD_GPIO27_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e59, PAD_GPIO27_OUT, BIT3),
    _RVM1(0x1e5F, PAD_GPIO27_OEN, BIT3),
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0  ),   //reg[101edf]#0  = 0b
    //reg_led_mode
    _RVM1(0x1eb4, 0, BIT5|BIT4 ),   //reg[101eb4]#5 ~ #4 = 00b
    //reg_et_test_mode[1:0]
    _RVM1(0x1edf, 0, BIT3|BIT2 ),   //reg[101edf]#3 ~ #2 = 00b
    //reg_usbdrvvbusconfig[1:0]
    _RVM1(0x1e04, 0, BIT1|BIT0 ),   //reg[101e04]#1 ~ #0 = 00b
    //reg_extint4
    _RVM1(0x1ee0, 0, BIT4 ),   //reg[101ee0]#4 = 0b
    #endif

    #if(PAD_UART_RX2_IS_GPIO != GPIO_NONE)
    #define PAD_UART_RX2_OEN (PAD_UART_RX2_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_UART_RX2_OUT (PAD_UART_RX2_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1000, PAD_UART_RX2_OUT, BIT1),
    _RVM1(0x1002, PAD_UART_RX2_OEN, BIT1),
    //reg_thirduartmode[1:0]
    _RVM1(0x1e05, 0, BIT3|BIT2 ),   //reg[101e05]#3 ~ #2 = 00b
    #endif

    #if(PAD_UART_TX2_IS_GPIO != GPIO_NONE)
    #define PAD_UART_TX2_OEN (PAD_UART_TX2_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_UART_TX2_OUT (PAD_UART_TX2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1000, PAD_UART_TX2_OUT, BIT0),
    _RVM1(0x1002, PAD_UART_TX2_OEN, BIT0),
    //reg_thirduartmode[1:0]
    _RVM1(0x1e05, 0, BIT3|BIT2 ),   //reg[101e05]#3 ~ #2 = 00b
    #endif

    #if(PAD_PWM0_IS_GPIO != GPIO_NONE)
    #define PAD_PWM0_OEN (PAD_PWM0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_PWM0_OUT (PAD_PWM0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e98, PAD_PWM0_OUT, BIT0),
    _RVM1(0x1e96, PAD_PWM0_OEN, BIT0),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6~#2 = 000b
    //reg_pwm0_mode
    _RVM1(0x1ea2, 0, BIT0 ),   //reg[101ea2]#0 = 0b
    #endif

    #if(PAD_PWM1_IS_GPIO != GPIO_NONE)
    #define PAD_PWM1_OEN (PAD_PWM1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_PWM1_OUT (PAD_PWM1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e98, PAD_PWM1_OUT, BIT1),
    _RVM1(0x1e96, PAD_PWM1_OEN, BIT1),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6~#2 = 000b
    //reg_pwm1_mode
    _RVM1(0x1ea2, 0, BIT1 ),   //reg[101ea2]#1 = 0b
    #endif

    #if(PAD_PWM2_IS_GPIO != GPIO_NONE)
    #define PAD_PWM2_OEN (PAD_PWM2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_PWM2_OUT (PAD_PWM2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e98, PAD_PWM2_OUT, BIT2),
    _RVM1(0x1e96, PAD_PWM2_OEN, BIT2),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6~#2 = 000b
    //reg_pwm2_mode
    _RVM1(0x1ea2, 0, BIT2 ),   //reg[101ea2]#2 = 0b
    #endif

    #if(PAD_PWM3_IS_GPIO != GPIO_NONE)
    #define PAD_PWM3_OEN (PAD_PWM3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_PWM3_OUT (PAD_PWM3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e98, PAD_PWM3_OUT, BIT3),
    _RVM1(0x1e96, PAD_PWM3_OEN, BIT3),
    //reg_pwm3_mode
    _RVM1(0x1ea2, 0, BIT3 ),   //reg[101ea2]#3 = 0b
    #endif

    #if(PAD_PWM4_IS_GPIO != GPIO_NONE)
    #define PAD_PWM4_OEN (PAD_PWM4_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_PWM4_OUT (PAD_PWM4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e98, PAD_PWM4_OUT, BIT4),
    _RVM1(0x1e96, PAD_PWM4_OEN, BIT4),
    //reg_i2smutemode[1:0]
    _RVM1(0x1e05, 0, BIT7|BIT6 ),   //reg[101e05]#7 ~ #6 = 00b
    //reg_pwm4_mode
    _RVM1(0x1ea2, 0, BIT4 ),   //reg[101ea2]#4 = 0b
    //reg_tserrout[1:0]
    _RVM1(0x1ea2, 0, BIT7 ),   //reg[101ea2]#7 = 0b
    #endif

    #if(PAD_DDCR_DA_IS_GPIO != GPIO_NONE)
    #define PAD_DDCR_DA_OEN (PAD_DDCR_DA_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_DDCR_DA_OUT (PAD_DDCR_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e9a, PAD_DDCR_DA_OUT, BIT2),
    _RVM1(0x1e9a, PAD_DDCR_DA_OEN, BIT0),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_ddcrmode[1:0]
    _RVM1(0x1eae, 0, BIT1|BIT0 ),   //reg[101eae]#1 ~ #0 = 000b
    #endif

    #if(PAD_DDCR_CK_IS_GPIO != GPIO_NONE)
    #define PAD_DDCR_CK_OEN (PAD_DDCR_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_DDCR_CK_OUT (PAD_DDCR_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e9a, PAD_DDCR_CK_OUT, BIT3),
    _RVM1(0x1e9a, PAD_DDCR_CK_OEN, BIT1),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_ddcrmode[1:0]
    _RVM1(0x1eae, 0, BIT1|BIT0 ),   //reg[101eae]#1 ~ #0 = 000b
    #endif

    #if(PAD_TGPIO0_IS_GPIO != GPIO_NONE)
    #define PAD_TGPIO0_OEN (PAD_TGPIO0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_TGPIO0_OUT (PAD_TGPIO0_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e9c, PAD_TGPIO0_OUT, BIT4),
    _RVM1(0x1e9c, PAD_TGPIO0_OEN, BIT0),
    //reg_vsync_vif_out_en
    _RVM1(0x1ea3, 0, BIT6 ),   //reg[101ea3]#6 = 0b
    //reg_mcu_jtag_mode[1:0]
    _RVM1(0x1e06, 0, BIT7|BIT6 ),   //reg[101e06]#7 ~ #6 = 00b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1|BIT0 ),   //reg[101e07]#1 ~ #0 = 00b
    #endif

    #if(PAD_TGPIO1_IS_GPIO != GPIO_NONE)
    #define PAD_TGPIO1_OEN (PAD_TGPIO1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_TGPIO1_OUT (PAD_TGPIO1_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e9c, PAD_TGPIO1_OUT, BIT5),
    _RVM1(0x1e9c, PAD_TGPIO1_OEN, BIT1),
    //reg_mcu_jtag_mode[1:0]
    _RVM1(0x1e06, 0, BIT7|BIT6 ),   //reg[101e06]#7 ~ #6 = 00b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1|BIT0 ),   //reg[101e07]#1 ~ #0 = 00b
    #endif

    #if(PAD_TGPIO2_IS_GPIO != GPIO_NONE)
    #define PAD_TGPIO2_OEN (PAD_TGPIO2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_TGPIO2_OUT (PAD_TGPIO2_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e9c, PAD_TGPIO2_OUT, BIT6),
    _RVM1(0x1e9c, PAD_TGPIO2_OEN, BIT2),
    //reg_mcu_jtag_mode[1:0]
    _RVM1(0x1e06, 0, BIT7|BIT6 ),   //reg[101e06]#7 ~ #6 = 00b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1|BIT0 ),   //reg[101e07]#1 ~ #0 = 00b
    //reg_miic_mode1[1:0]
    _RVM1(0x1eb5, 0, BIT3|BIT2 ),   //reg[101eb5]#3 ~ #2 = 00b
    #endif

    #if(PAD_TGPIO3_IS_GPIO != GPIO_NONE)
    #define PAD_TGPIO3_OEN (PAD_TGPIO3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_TGPIO3_OUT (PAD_TGPIO3_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e9c, PAD_TGPIO3_OUT, BIT7),
    _RVM1(0x1e9c, PAD_TGPIO3_OEN, BIT3),
    //reg_mcu_jtag_mode[1:0]
    _RVM1(0x1e06, 0, BIT7|BIT6 ),   //reg[101e06]#7 ~ #6 = 00b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1|BIT0 ),   //reg[101e07]#1 ~ #0 = 00b
    //reg_miic_mode1[1:0]
    _RVM1(0x1eb5, 0, BIT3|BIT2 ),   //reg[101eb5]#3 ~ #2 = 00b
    #endif

    #if(PAD_TS0_D0_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D0_OEN (PAD_TS0_D0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_TS0_D0_OUT (PAD_TS0_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e64, PAD_TS0_D0_OUT, BIT0),
    _RVM1(0x1e68, PAD_TS0_D0_OEN, BIT0),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2~#0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_ts0config[1:0]
    _RVM1(0x1ea3, 0, BIT3|BIT2 ),   //reg[101ea3]#3 ~ #2 = 00b
    #endif

    #if(PAD_TS0_D1_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D1_OEN (PAD_TS0_D1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_TS0_D1_OUT (PAD_TS0_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e64, PAD_TS0_D1_OUT, BIT1),
    _RVM1(0x1e68, PAD_TS0_D1_OEN, BIT1),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2~#0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_ts0config[1:0]
    _RVM1(0x1ea3, 0, BIT3|BIT2 ),   //reg[101ea3]#3 ~ #2 = 00b
    #endif

    #if(PAD_TS0_D2_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D2_OEN (PAD_TS0_D2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_TS0_D2_OUT (PAD_TS0_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e64, PAD_TS0_D2_OUT, BIT2),
    _RVM1(0x1e68, PAD_TS0_D2_OEN, BIT2),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2~#0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_ts0config[1:0]
    _RVM1(0x1ea3, 0, BIT3|BIT2 ),   //reg[101ea3]#3 ~ #2 = 00b
    #endif

    #if(PAD_TS0_D3_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D3_OEN (PAD_TS0_D3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_TS0_D3_OUT (PAD_TS0_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e64, PAD_TS0_D3_OUT, BIT3),
    _RVM1(0x1e68, PAD_TS0_D3_OEN, BIT3),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2~#0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_ts0config[1:0]
    _RVM1(0x1ea3, 0, BIT3|BIT2 ),   //reg[101ea3]#3 ~ #2 = 00b
    #endif

    #if(PAD_TS0_D4_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D4_OEN (PAD_TS0_D4_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_TS0_D4_OUT (PAD_TS0_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e64, PAD_TS0_D4_OUT, BIT4),
    _RVM1(0x1e68, PAD_TS0_D4_OEN, BIT4),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2~#0 = 000b
    //reg_ts0config[1:0]
    _RVM1(0x1ea3, 0, BIT3|BIT2 ),   //reg[101ea3]#3 ~ #2 = 00b
    #endif

    #if(PAD_TS0_D5_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D5_OEN (PAD_TS0_D5_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_D5_OUT (PAD_TS0_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e64, PAD_TS0_D5_OUT, BIT5),
    _RVM1(0x1e68, PAD_TS0_D5_OEN, BIT5),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2~#0 = 000b
    //reg_ts0config[1:0]
    _RVM1(0x1ea3, 0, BIT3|BIT2 ),   //reg[101ea3]#3 ~ #2 = 00b
    #endif

    #if(PAD_TS0_D6_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D6_OEN (PAD_TS0_D6_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_TS0_D6_OUT (PAD_TS0_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e64, PAD_TS0_D6_OUT, BIT6),
    _RVM1(0x1e68, PAD_TS0_D6_OEN, BIT6),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2~#0 = 000b
    //reg_ts0config[1:0]
    _RVM1(0x1ea3, 0, BIT3|BIT2 ),   //reg[101ea3]#3 ~ #2 = 00b
    #endif

    #if(PAD_TS0_D7_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D7_OEN (PAD_TS0_D7_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_TS0_D7_OUT (PAD_TS0_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e64, PAD_TS0_D7_OUT, BIT7),
    _RVM1(0x1e68, PAD_TS0_D7_OEN, BIT7),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2~#0 = 000b
    //reg_ts0config[1:0]
    _RVM1(0x1ea3, 0, BIT3|BIT2 ),   //reg[101ea3]#3 ~ #2 = 00b
    #endif

    #if(PAD_TS0_VLD_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_VLD_OEN (PAD_TS0_VLD_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_TS0_VLD_OUT (PAD_TS0_VLD_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e65, PAD_TS0_VLD_OUT, BIT0),
    _RVM1(0x1e69, PAD_TS0_VLD_OEN, BIT0),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2~#0 = 000b
    //reg_ts0config[1:0]
    _RVM1(0x1ea3, 0, BIT3|BIT2 ),   //reg[101ea3]#3 ~ #2 = 00b
    #endif

    #if(PAD_TS0_SYNC_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_SYNC_OEN (PAD_TS0_SYNC_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_TS0_SYNC_OUT (PAD_TS0_SYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e65, PAD_TS0_SYNC_OUT, BIT1),
    _RVM1(0x1e69, PAD_TS0_SYNC_OEN, BIT1),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2~#0 = 000b
    //reg_ts0config[1:0]
    _RVM1(0x1ea3, 0, BIT3|BIT2 ),   //reg[101ea3]#3 ~ #2 = 00b
    #endif

    #if(PAD_TS0_CLK_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_CLK_OEN (PAD_TS0_CLK_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_TS0_CLK_OUT (PAD_TS0_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e65, PAD_TS0_CLK_OUT, BIT2),
    _RVM1(0x1e69, PAD_TS0_CLK_OEN, BIT2),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2~#0 = 000b
    //reg_ts0config[1:0]
    _RVM1(0x1ea3, 0, BIT3|BIT2 ),   //reg[101ea3]#3 ~ #2 = 00b
    #endif

    #if(PAD_TS1_D0_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D0_OEN (PAD_TS1_D0_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_TS1_D0_OUT (PAD_TS1_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e4D, PAD_TS1_D0_OUT, BIT2),
    _RVM1(0x1e4F, PAD_TS1_D0_OEN, BIT2),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_ts1config[1:0]
    _RVM1(0x1ea3, 0, BIT5|BIT4 ),   //reg[101ea3]#5 ~ #4 = 00b
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1 ),   //reg[101ea3]#1 = 0b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    //reg_miic_mode1[1:0]
    _RVM1(0x1eb5, 0, BIT3|BIT2 ),   //reg[101eb5]#3 ~ #2 = 00b
    //reg_miic_mode2[1:0]
    _RVM1(0x1eb5, 0, BIT5|BIT4 ),   //reg[101eb5]#5 ~ #4 = 00b
    #endif

    #if(PAD_TS1_D1_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D1_OEN (PAD_TS1_D1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_TS1_D1_OUT (PAD_TS1_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e4D, PAD_TS1_D1_OUT, BIT1),
    _RVM1(0x1e4F, PAD_TS1_D1_OEN, BIT1),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_ts1config[1:0]
    _RVM1(0x1ea3, 0, BIT5|BIT4 ),   //reg[101ea3]#5 ~ #4 = 00b
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1 ),   //reg[101ea3]#1 = 0b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    #endif

    #if(PAD_TS1_D2_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D2_OEN (PAD_TS1_D2_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_TS1_D2_OUT (PAD_TS1_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e4D, PAD_TS1_D2_OUT, BIT0),
    _RVM1(0x1e4F, PAD_TS1_D2_OEN, BIT0),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_ts1config[1:0]
    _RVM1(0x1ea3, 0, BIT5|BIT4 ),   //reg[101ea3]#5 ~ #4 = 00b
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1 ),   //reg[101ea3]#1 = 0b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    #endif

    #if(PAD_TS1_D3_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D3_OEN (PAD_TS1_D3_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_TS1_D3_OUT (PAD_TS1_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e4C, PAD_TS1_D3_OUT, BIT7),
    _RVM1(0x1e4E, PAD_TS1_D3_OEN, BIT7),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_ts1config[1:0]
    _RVM1(0x1ea3, 0, BIT5|BIT4 ),   //reg[101ea3]#5 ~ #4 = 00b
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1 ),   //reg[101ea3]#1 = 0b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    #endif

    #if(PAD_TS1_D4_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D4_OEN (PAD_TS1_D4_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_TS1_D4_OUT (PAD_TS1_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e4C, PAD_TS1_D4_OUT, BIT6),
    _RVM1(0x1e4E, PAD_TS1_D4_OEN, BIT6),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_ts1config[1:0]
    _RVM1(0x1ea3, 0, BIT5|BIT4 ),   //reg[101ea3]#5 ~ #4 = 00b
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1 ),   //reg[101ea3]#1 = 0b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1|BIT0 ),   //reg[101e07]#1 ~ #0 = 00b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    #endif

    #if(PAD_TS1_D5_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D5_OEN (PAD_TS1_D5_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS1_D5_OUT (PAD_TS1_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e4C, PAD_TS1_D5_OUT, BIT5),
    _RVM1(0x1e4E, PAD_TS1_D5_OEN, BIT5),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_ts1config[1:0]
    _RVM1(0x1ea3, 0, BIT5|BIT4 ),   //reg[101ea3]#5 ~ #4 = 00b
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1 ),   //reg[101ea3]#1 = 0b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1|BIT0 ),   //reg[101e07]#1 ~ #0 = 00b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1|BIT0 ),   //reg[101e9f]#1 ~ #0 = 00b
    #endif

    #if(PAD_TS1_D6_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D6_OEN (PAD_TS1_D6_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_TS1_D6_OUT (PAD_TS1_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e4C, PAD_TS1_D6_OUT, BIT4),
    _RVM1(0x1e4E, PAD_TS1_D6_OEN, BIT4),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_ts1config[1:0]
    _RVM1(0x1ea3, 0, BIT5|BIT4 ),   //reg[101ea3]#5 ~ #4 = 00b
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1 ),   //reg[101ea3]#1 = 0b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1|BIT0 ),   //reg[101e07]#1 ~ #0 = 00b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1|BIT0 ),   //reg[101e9f]#1 ~ #0 = 00b
    #endif

    #if(PAD_TS1_D7_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D7_OEN (PAD_TS1_D7_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_TS1_D7_OUT (PAD_TS1_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e4C, PAD_TS1_D7_OUT, BIT3),
    _RVM1(0x1e4E, PAD_TS1_D7_OEN, BIT3),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_ts1config[1:0]
    _RVM1(0x1ea3, 0, BIT5|BIT4 ),   //reg[101ea3]#5 ~ #4 = 00b
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1 ),   //reg[101ea3]#1 = 0b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1|BIT0 ),   //reg[101e07]#1 ~ #0 = 00b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1|BIT0 ),   //reg[101e9f]#1 ~ #0 = 00b
    #endif

    #if(PAD_TS1_VLD_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_VLD_OEN (PAD_TS1_VLD_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_TS1_VLD_OUT (PAD_TS1_VLD_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e4C, PAD_TS1_VLD_OUT, BIT2),
    _RVM1(0x1e4E, PAD_TS1_VLD_OEN, BIT2),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_ts1config[1:0]
    _RVM1(0x1ea3, 0, BIT5|BIT4 ),   //reg[101ea3]#5 ~ #4 = 00b
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1 ),   //reg[101ea3]#1 = 0b
    //reg_miic_mode1[1:0]
    _RVM1(0x1eb5, 0, BIT3|BIT2 ),   //reg[101eb5]#3 ~ #2 = 00b
    //reg_miic_mode2[1:0]
    _RVM1(0x1eb5, 0, BIT5|BIT4 ),   //reg[101eb5]#5 ~ #4 = 00b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1|BIT0 ),   //reg[101e9f]#1 ~ #0 = 00b
    #endif

    #if(PAD_TS1_SYNC_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_SYNC_OEN (PAD_TS1_SYNC_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_TS1_SYNC_OUT (PAD_TS1_SYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e4C, PAD_TS1_SYNC_OUT, BIT1),
    _RVM1(0x1e4E, PAD_TS1_SYNC_OEN, BIT1),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_ts1config[1:0]
    _RVM1(0x1ea3, 0, BIT5|BIT4 ),   //reg[101ea3]#5 ~ #4 = 00b
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1 ),   //reg[101ea3]#1 = 0b
    //reg_miic_mode0[1:0]
    _RVM1(0x1eb5, 0, BIT1|BIT0 ),   //reg[101eb5]#1 ~ #0 = 00b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1|BIT0 ),   //reg[101e9f]#1 ~ #0 = 00b
    #endif

    #if(PAD_TS1_CLK_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_CLK_OEN (PAD_TS1_CLK_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_TS1_CLK_OUT (PAD_TS1_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e4C, PAD_TS1_CLK_OUT, BIT0),
    _RVM1(0x1e4E, PAD_TS1_CLK_OEN, BIT0),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_ts1config[1:0]
    _RVM1(0x1ea3, 0, BIT5|BIT4 ),   //reg[101ea3]#5 ~ #4 = 00b
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1 ),   //reg[101ea3]#1 = 0b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    //reg_miic_mode0[1:0]
    _RVM1(0x1eb5, 0, BIT1|BIT0 ),   //reg[101eb5]#1 ~ #0 = 00b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1|BIT0 ),   //reg[101e9f]#1 ~ #0 = 00b
    #endif

    #if(PAD_PCM_A4_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A4_OEN (PAD_PCM_A4_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_PCM_A4_OUT (PAD_PCM_A4_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e78, PAD_PCM_A4_OUT, BIT6),
    _RVM1(0x1e7e, PAD_PCM_A4_OEN, BIT6),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    #endif

    #if(PAD_PCM_WAIT_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_WAIT_N_OEN (PAD_PCM_WAIT_N_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_PCM_WAIT_N_OUT (PAD_PCM_WAIT_N_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e78, PAD_PCM_WAIT_N_OUT, BIT5),
    _RVM1(0x1e7e, PAD_PCM_WAIT_N_OEN, BIT5),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_pcmctrlconfig
    _RVM1(0x1e9f, 0, BIT7 ),   //reg[101e9f]#7 = 0b
    //reg_cictrlconfig
    _RVM1(0x1ec8, 0, BIT1 ),   //reg[101ec8]#1 = 0b
    #endif

    #if(PAD_PCM_A5_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A5_OEN (PAD_PCM_A5_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_PCM_A5_OUT (PAD_PCM_A5_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e78, PAD_PCM_A5_OUT, BIT4),
    _RVM1(0x1e7e, PAD_PCM_A5_OEN, BIT4),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    #endif

    #if(PAD_PCM_A6_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A6_OEN (PAD_PCM_A6_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_PCM_A6_OUT (PAD_PCM_A6_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e78, PAD_PCM_A6_OUT, BIT3),
    _RVM1(0x1e7e, PAD_PCM_A6_OEN, BIT3),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    #endif

    #if(PAD_PCM_A7_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A7_OEN (PAD_PCM_A7_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_PCM_A7_OUT (PAD_PCM_A7_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e78, PAD_PCM_A7_OUT, BIT2),
    _RVM1(0x1e7e, PAD_PCM_A7_OEN, BIT2),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    #endif

    #if(PAD_PCM_A12_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A12_OEN (PAD_PCM_A12_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_PCM_A12_OUT (PAD_PCM_A12_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e78, PAD_PCM_A12_OUT, BIT1),
    _RVM1(0x1e7e, PAD_PCM_A12_OEN, BIT1),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    #endif

    #if(PAD_PCM_IRQA_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_IRQA_N_OEN (PAD_PCM_IRQA_N_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_PCM_IRQA_N_OUT (PAD_PCM_IRQA_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e78, PAD_PCM_IRQA_N_OUT, BIT0),
    _RVM1(0x1e7e, PAD_PCM_IRQA_N_OEN, BIT0),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_pcmctrlconfig
    _RVM1(0x1e9f, 0, BIT7 ),   //reg[101e9f]#7 = 0b
    //reg_cictrlconfig
    _RVM1(0x1ec8, 0, BIT1 ),   //reg[101ec8]#1 = 0b
    #endif

    #if(PAD_PCM_A14_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A14_OEN (PAD_PCM_A14_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_PCM_A14_OUT (PAD_PCM_A14_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e77, PAD_PCM_A14_OUT, BIT6),
    _RVM1(0x1e7d, PAD_PCM_A14_OEN, BIT6),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    #endif

    #if(PAD_PCM_A13_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A13_OEN (PAD_PCM_A13_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_PCM_A13_OUT (PAD_PCM_A13_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e77, PAD_PCM_A13_OUT, BIT5),
    _RVM1(0x1e7d, PAD_PCM_A13_OEN, BIT5),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    #endif

    #if(PAD_PCM_A8_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A8_OEN (PAD_PCM_A8_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_PCM_A8_OUT (PAD_PCM_A8_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e77, PAD_PCM_A8_OUT, BIT4),
    _RVM1(0x1e7d, PAD_PCM_A8_OEN, BIT4),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    #endif

    #if(PAD_PCM_IOWR_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_IOWR_N_OEN (PAD_PCM_IOWR_N_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_PCM_IOWR_N_OUT (PAD_PCM_IOWR_N_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e77, PAD_PCM_IOWR_N_OUT, BIT3),
    _RVM1(0x1e7d, PAD_PCM_IOWR_N_OEN, BIT3),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b

    //reg_pcmctrlconfig
    _RVM1(0x1e9f, 0, BIT7 ),   //reg[101e9f]#7 = 0b
    //reg_cictrlconfig
    _RVM1(0x1ec8, 0, BIT1 ),   //reg[101ec8]#1 = 0b
    #endif

    #if(PAD_PCM_A9_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A9_OEN (PAD_PCM_A9_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_PCM_A9_OUT (PAD_PCM_A9_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e77, PAD_PCM_A9_OUT, BIT2),
    _RVM1(0x1e7d, PAD_PCM_A9_OEN, BIT2),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    #endif

    #if(PAD_PCM_IORD_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_IORD_N_OEN (PAD_PCM_IORD_N_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_PCM_IORD_N_OUT (PAD_PCM_IORD_N_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e77, PAD_PCM_IORD_N_OUT, BIT1),
    _RVM1(0x1e7d, PAD_PCM_IORD_N_OEN, BIT1),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_pcmctrlconfig
    _RVM1(0x1e9f, 0, BIT7 ),   //reg[101e9f]#7 = 0b
    //reg_cictrlconfig
    _RVM1(0x1ec8, 0, BIT1 ),   //reg[101ec8]#1 = 0b
    #endif

    #if(PAD_PCM_A11_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A11_OEN (PAD_PCM_A11_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_PCM_A11_OUT (PAD_PCM_A11_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e77, PAD_PCM_A11_OUT, BIT0),
    _RVM1(0x1e7d, PAD_PCM_A11_OEN, BIT0),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    #endif

    #if(PAD_PCM_OE_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_OE_N_OEN (PAD_PCM_OE_N_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_PCM_OE_N_OUT (PAD_PCM_OE_N_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e76, PAD_PCM_OE_N_OUT, BIT7),
    _RVM1(0x1e7c, PAD_PCM_OE_N_OEN, BIT7),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_pcmctrlconfig
    _RVM1(0x1e9f, 0, BIT7 ),   //reg[101e9f]#7 = 0b
    #endif

    #if(PAD_PCM_A10_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A10_OEN (PAD_PCM_A10_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_PCM_A10_OUT (PAD_PCM_A10_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e76, PAD_PCM_A10_OUT, BIT6),
    _RVM1(0x1e7c, PAD_PCM_A10_OEN, BIT6),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    #endif

    #if(PAD_PCM_CE_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_CE_N_OEN (PAD_PCM_CE_N_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_PCM_CE_N_OUT (PAD_PCM_CE_N_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e76, PAD_PCM_CE_N_OUT, BIT5),
    _RVM1(0x1e7c, PAD_PCM_CE_N_OEN, BIT5),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_pcmctrlconfig
    _RVM1(0x1e9f, 0, BIT7 ),   //reg[101e9f]#7 = 0b
    //reg_cictrlconfig
    _RVM1(0x1ec8, 0, BIT1 ),   //reg[101ec8]#1 = 0b
    #endif

    #if(PAD_PCM_D7_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_D7_OEN (PAD_PCM_D7_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_PCM_D7_OUT (PAD_PCM_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e76, PAD_PCM_D7_OUT, BIT4),
    _RVM1(0x1e7c, PAD_PCM_D7_OEN, BIT4),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7|BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    //reg_sd_config
    //reg_sd_config2
    #endif

    #if(PAD_PCM_D6_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_D6_OEN (PAD_PCM_D6_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_PCM_D6_OUT (PAD_PCM_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e76, PAD_PCM_D6_OUT, BIT3),
    _RVM1(0x1e7c, PAD_PCM_D6_OEN, BIT3),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_nand_mode[1:0]
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_mcu_jtag_mode[1:0]
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7| BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    //reg_sd_config
    _RVM1(0x1eaf, 0, BIT1|BIT0 ),   //reg[101eaf]#1~#0 = 00b
    //reg_sd_config2
    _RVM1(0x1eaf, 0, BIT3|BIT2 ),   //reg[101eaf]#3~#2 = 00b
    #endif

    #if(PAD_PCM_D5_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_D5_OEN (PAD_PCM_D5_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_PCM_D5_OUT (PAD_PCM_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e76, PAD_PCM_D5_OUT, BIT2),
    _RVM1(0x1e7c, PAD_PCM_D5_OEN, BIT2),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_nand_mode[1:0]
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_mcu_jtag_mode[1:0]
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7| BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    //reg_sd_config
    _RVM1(0x1eaf, 0, BIT1|BIT0 ),   //reg[101eaf]#1~#0 = 00b
    //reg_sd_config2
    _RVM1(0x1eaf, 0, BIT3|BIT2 ),   //reg[101eaf]#3~#2 = 00b
    #endif

    #if(PAD_PCM_D4_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_D4_OEN (PAD_PCM_D4_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_PCM_D4_OUT (PAD_PCM_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e76, PAD_PCM_D4_OUT, BIT1),
    _RVM1(0x1e7c, PAD_PCM_D4_OEN, BIT1),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_nand_mode[1:0]
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_mcu_jtag_mode[1:0]
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7| BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    //reg_sd_config
    _RVM1(0x1eaf, 0, BIT1|BIT0 ),   //reg[101eaf]#1~#0 = 00b
    //reg_sd_config2
    _RVM1(0x1eaf, 0, BIT3|BIT2 ),   //reg[101eaf]#3~#2 = 00b
    #endif

    #if(PAD_PCM_D3_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_D3_OEN (PAD_PCM_D3_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_PCM_D3_OUT (PAD_PCM_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e76, PAD_PCM_D3_OUT, BIT0),
    _RVM1(0x1e7c, PAD_PCM_D3_OEN, BIT0),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_nand_mode[1:0]
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_mcu_jtag_mode[1:0]
    //reg_bt656_ctrl[1:0]
    _RVM1(0x1edf, 0, BIT7| BIT6 ),   //reg[101edf]#7 ~ #6 = 00b
    //reg_sd_config
    _RVM1(0x1eaf, 0, BIT1|BIT0 ),   //reg[101eaf]#1~#0 = 00b
    //reg_sd_config2
    _RVM1(0x1eaf, 0, BIT3|BIT2 ),   //reg[101eaf]#3~#2 = 00b
    #endif

    #if(PAD_PCM_A3_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A3_OEN (PAD_PCM_A3_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_PCM_A3_OUT (PAD_PCM_A3_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e78, PAD_PCM_A3_OUT, BIT7),
    _RVM1(0x1e7e, PAD_PCM_A3_OEN, BIT7),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_sd_config
    _RVM1(0x1eaf, 0, BIT1|BIT0 ),   //reg[101eaf]#1~#0 = 00b
    //reg_sd_config2
    _RVM1(0x1eaf, 0, BIT3|BIT2 ),   //reg[101eaf]#3~#2 = 00b
    #endif

    #if(PAD_PCM_A2_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A2_OEN (PAD_PCM_A2_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_PCM_A2_OUT (PAD_PCM_A2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e79, PAD_PCM_A2_OUT, BIT0),
    _RVM1(0x1e7f, PAD_PCM_A2_OEN, BIT0),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_sd_config
    _RVM1(0x1eaf, 0, BIT1|BIT0 ),   //reg[101eaf]#1~#0 = 00b
    //reg_sd_config2
    _RVM1(0x1eaf, 0, BIT3|BIT2 ),   //reg[101eaf]#3~#2 = 00b
    #endif

    #if(PAD_PCM_REG_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_REG_N_OEN (PAD_PCM_REG_N_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_PCM_REG_N_OUT (PAD_PCM_REG_N_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e79, PAD_PCM_REG_N_OUT, BIT1),
    _RVM1(0x1e7f, PAD_PCM_REG_N_OEN, BIT1),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_pcmctrlconfig
    _RVM1(0x1e9f, 0, BIT7 ),   //reg[101e9f]#7 = 0b
    //reg_cictrlconfig
    _RVM1(0x1ec8, 0, BIT1 ),   //reg[101ec8]#1 = 0b
    #endif

    #if(PAD_PCM_A1_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A1_OEN (PAD_PCM_A1_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_PCM_A1_OUT (PAD_PCM_A1_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e79, PAD_PCM_A1_OUT, BIT2),
    _RVM1(0x1e7f, PAD_PCM_A1_OEN, BIT2),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_sd_config
    _RVM1(0x1eaf, 0, BIT1|BIT0 ),   //reg[101eaf]#1~#0 = 00b
    //reg_sd_config2
    _RVM1(0x1eaf, 0, BIT3|BIT2 ),   //reg[101eaf]#3~#2 = 00b
    #endif

    #if(PAD_PCM_A0_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A0_OEN (PAD_PCM_A0_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_PCM_A0_OUT (PAD_PCM_A0_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e79, PAD_PCM_A0_OUT, BIT3),
    _RVM1(0x1e7f, PAD_PCM_A0_OEN, BIT3),
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_sd_config
    _RVM1(0x1eaf, 0, BIT1|BIT0 ),   //reg[101eaf]#1~#0 = 00b
    //reg_sd_config2
    _RVM1(0x1eaf, 0, BIT3|BIT2 ),   //reg[101eaf]#3~#2 = 00b
    #endif

    #if(PAD_PCM_D0_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_D0_OEN (PAD_PCM_D0_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_PCM_D0_OUT (PAD_PCM_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e79, PAD_PCM_D0_OUT, BIT4),
    _RVM1(0x1e7f, PAD_PCM_D0_OEN, BIT4),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    #endif

    #if(PAD_PCM_D1_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_D1_OEN (PAD_PCM_D1_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_PCM_D1_OUT (PAD_PCM_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e79, PAD_PCM_D1_OUT, BIT5),
    _RVM1(0x1e7f, PAD_PCM_D1_OEN, BIT5),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    #endif

    #if(PAD_PCM_D2_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_D2_OEN (PAD_PCM_D2_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_PCM_D2_OUT (PAD_PCM_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e79, PAD_PCM_D2_OUT, BIT6),
    _RVM1(0x1e7f, PAD_PCM_D2_OEN, BIT6),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6 ),   //reg[101e9f]#6 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    #endif

    #if(PAD_PCM_RESET_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_RESET_OEN (PAD_PCM_RESET_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_PCM_RESET_OUT (PAD_PCM_RESET_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e79, PAD_PCM_RESET_OUT, BIT7),
    _RVM1(0x1e7f, PAD_PCM_RESET_OEN, BIT7),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_pcmctrlconfig
    _RVM1(0x1e9f, 0, BIT7 ),   //reg[101e9f]#7 = 0b
    //reg_cictrlconfig
    _RVM1(0x1ec8, 0, BIT1 ),   //reg[101ec8]#1 = 0b
    #endif

    #if(PAD_PCM_CD_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_CD_N_OEN (PAD_PCM_CD_N_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_PCM_CD_N_OUT (PAD_PCM_CD_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e7a, PAD_PCM_CD_N_OUT, BIT0),
    _RVM1(0x1e80, PAD_PCM_CD_N_OEN, BIT0),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_pcmctrlconfig
    _RVM1(0x1e9f, 0, BIT7 ),   //reg[101e9f]#7 = 0b
    #endif

    #if(PAD_PCM2_CE_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM2_CE_N_OEN (PAD_PCM2_CE_N_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_PCM2_CE_N_OUT (PAD_PCM2_CE_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e7B, PAD_PCM2_CE_N_OUT, BIT0),
    _RVM1(0x1e81, PAD_PCM2_CE_N_OEN, BIT0),
    //reg_pcm2ctrlconfig
    _RVM1(0x1e9f, 0, BIT5 ),   //reg[101e9f]#5 = 0b
    //reg_extint0
    _RVM1(0x1ee0, 0, BIT0 ),   //reg[101ee0]#0 = 0breg_sd_config
    _RVM1(0x1eaf, 0, BIT1|BIT0 ),   //reg[101eaf]#1~#0 = 00b
    //reg_sd_config2
    _RVM1(0x1eaf, 0, BIT3|BIT2 ),   //reg[101eaf]#3~#2 = 00b
    //reg_sd_config
    _RVM1(0x1eaf, 0, BIT1|BIT0 ),   //reg[101eaf]#1~#0 = 00b
    //reg_sd_config2
    _RVM1(0x1eaf, 0, BIT3|BIT2 ),   //reg[101eaf]#3~#2 = 00b
    #endif

    #if(PAD_PCM2_IRQA_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM2_IRQA_N_OEN (PAD_PCM2_IRQA_N_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_PCM2_IRQA_N_OUT (PAD_PCM2_IRQA_N_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e7B, PAD_PCM2_IRQA_N_OUT, BIT1),
    _RVM1(0x1e81, PAD_PCM2_IRQA_N_OEN, BIT1),
    //reg_pcm2ctrlconfig
    _RVM1(0x1e9f, 0, BIT5 ),   //reg[101e9f]#5 = 0b
    //reg_extint2
    _RVM1(0x1ee0, 0, BIT2 ),   //reg[101ee0]#2 = 0b
    //reg_sd_config
    _RVM1(0x1eaf, 0, BIT1|BIT0 ),   //reg[101eaf]#1~#0 = 00b
    //reg_sd_config2
    _RVM1(0x1eaf, 0, BIT3|BIT2 ),   //reg[101eaf]#3~#2 = 00b
    #endif

    #if(PAD_PCM2_WAIT_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM2_WAIT_N_OEN (PAD_PCM2_WAIT_N_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_PCM2_WAIT_N_OUT (PAD_PCM2_WAIT_N_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e7B, PAD_PCM2_WAIT_N_OUT, BIT2),
    _RVM1(0x1e81, PAD_PCM2_WAIT_N_OEN, BIT2),
    //reg_pcm2ctrlconfig
    _RVM1(0x1e9f, 0, BIT5 ),   //reg[101e9f]#5 = 0b
    //reg_sd_config
    //reg_sd_config2
    #endif

    #if(PAD_PCM2_RESET_IS_GPIO != GPIO_NONE)
    #define PAD_PCM2_RESET_OEN (PAD_PCM2_RESET_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_PCM2_RESET_OUT (PAD_PCM2_RESET_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e7B, PAD_PCM2_RESET_OUT, BIT3),
    _RVM1(0x1e81, PAD_PCM2_RESET_OEN, BIT3),
    //reg_pcm2ctrlconfig
    _RVM1(0x1e9f, 0, BIT5 ),   //reg[101e9f]#5 = 0b
    //reg_sd_config
    //reg_sd_config2
    #endif

    #if(PAD_PCM2_CD_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM2_CD_N_OEN (PAD_PCM2_CD_N_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_PCM2_CD_N_OUT (PAD_PCM2_CD_N_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e7B, PAD_PCM2_CD_N_OUT, BIT4),
    _RVM1(0x1e81, PAD_PCM2_CD_N_OEN, BIT4),
    //reg_pcm2ctrlconfig
    _RVM1(0x1e9f, 0, BIT5 ),   //reg[101e9f]#5 = 0b
    //reg_extint3
    _RVM1(0x1ee0, 0, BIT3 ),   //reg[101ee0]#3 = 0b
    #endif

    #if(PAD_NAND_CLE_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_CLE_OEN (PAD_NAND_CLE_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_NAND_CLE_OUT (PAD_NAND_CLE_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e89, PAD_NAND_CLE_OUT, BIT2),
    _RVM1(0x1e88, PAD_NAND_CLE_OEN, BIT2),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    #endif

    #if(PAD_NAND_CEZ_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_CEZ_OEN (PAD_NAND_CEZ_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_NAND_CEZ_OUT (PAD_NAND_CEZ_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e89, PAD_NAND_CEZ_OUT, BIT0),
    _RVM1(0x1e88, PAD_NAND_CEZ_OEN, BIT0),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    #endif

    #if(PAD_NAND_CEZ1_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_CEZ1_OEN (PAD_NAND_CEZ1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_NAND_CEZ1_OUT (PAD_NAND_CEZ1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e89, PAD_NAND_CEZ1_OUT, BIT1),
    _RVM1(0x1e88, PAD_NAND_CEZ1_OEN, BIT1),
    //reg_nand_cs1_en
    _RVM1(0x1ea1, 0, BIT3 ),   //reg[101ea1]#3 = 0b
    #endif

    #if(PAD_NAND_REZ_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_REZ_OEN (PAD_NAND_REZ_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_NAND_REZ_OUT (PAD_NAND_REZ_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e89, PAD_NAND_REZ_OUT, BIT3),
    _RVM1(0x1e88, PAD_NAND_REZ_OEN, BIT3),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    #endif

    #if(PAD_NAND_WEZ_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_WEZ_OEN (PAD_NAND_WEZ_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_NAND_WEZ_OUT (PAD_NAND_WEZ_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e89, PAD_NAND_WEZ_OUT, BIT4),
    _RVM1(0x1e88, PAD_NAND_WEZ_OEN, BIT4),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    #endif

    #if(PAD_NAND_ALE_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_ALE_OEN (PAD_NAND_ALE_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_NAND_ALE_OUT (PAD_NAND_ALE_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e89, PAD_NAND_ALE_OUT, BIT6),
    _RVM1(0x1e88, PAD_NAND_ALE_OEN, BIT6),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    #endif

    #if(PAD_NAND_RBZ_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_RBZ_OEN (PAD_NAND_RBZ_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_NAND_RBZ_OUT (PAD_NAND_RBZ_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e89, PAD_NAND_RBZ_OUT, BIT7),
    _RVM1(0x1e88, PAD_NAND_RBZ_OEN, BIT7),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    #endif

    #if(PAD_NAND_AD0_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_AD0_OEN (PAD_NAND_AD0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_NAND_AD0_OUT (PAD_NAND_AD0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x100E, PAD_NAND_AD0_OUT, BIT0),
    _RVM1(0x1010, PAD_NAND_AD0_OEN, BIT0),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0 , BIT0 ),   //reg[101e21]#0 = 1b
    #endif

    #if(PAD_NAND_AD1_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_AD1_OEN (PAD_NAND_AD1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_NAND_AD1_OUT (PAD_NAND_AD1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x100E, PAD_NAND_AD1_OUT, BIT1),
    _RVM1(0x1010, PAD_NAND_AD1_OEN, BIT1),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0, BIT0 ),   //reg[101e21]#0 = 1b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_AD2_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_AD2_OEN (PAD_NAND_AD2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_NAND_AD2_OUT (PAD_NAND_AD2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x100E, PAD_NAND_AD2_OUT, BIT2),
    _RVM1(0x1010, PAD_NAND_AD2_OEN, BIT2),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0, BIT0 ),   //reg[101e21]#0 = 1b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_allpad_in
    _RVM1(0x1ea1, BIT7 , BIT7 ),   //reg[101ea1]#7 = 1b
    #endif

    #if(PAD_NAND_AD3_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_AD3_OEN (PAD_NAND_AD3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_NAND_AD3_OUT (PAD_NAND_AD3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x100E, PAD_NAND_AD3_OUT, BIT3),
    _RVM1(0x1010, PAD_NAND_AD3_OEN, BIT3),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0, BIT0 ),   //reg[101e21]#0 = 1b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_AD4_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_AD4_OEN (PAD_NAND_AD4_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_NAND_AD4_OUT (PAD_NAND_AD4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x100E, PAD_NAND_AD4_OUT, BIT4),
    _RVM1(0x1010, PAD_NAND_AD4_OEN, BIT4),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0, BIT0 ),   //reg[101e21]#0 = 1b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_AD5_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_AD5_OEN (PAD_NAND_AD5_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_NAND_AD5_OUT (PAD_NAND_AD5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x100E, PAD_NAND_AD5_OUT, BIT5),
    _RVM1(0x1010, PAD_NAND_AD5_OEN, BIT5),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0, BIT0 ),   //reg[101e21]#0 = 1b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_AD6_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_AD6_OEN (PAD_NAND_AD6_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_NAND_AD6_OUT (PAD_NAND_AD6_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x100E, PAD_NAND_AD6_OUT, BIT6),
    _RVM1(0x1010, PAD_NAND_AD6_OEN, BIT6),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0, BIT0 ),   //reg[101e21]#0 = 1b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_AD7_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_AD7_OEN (PAD_NAND_AD7_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_NAND_AD7_OUT (PAD_NAND_AD7_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x100E, PAD_NAND_AD7_OUT, BIT7),
    _RVM1(0x1010, PAD_NAND_AD7_OEN, BIT7),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0, BIT0 ),   //reg[101e21]#0 = 1b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_DQS_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_DQS_OEN (PAD_NAND_DQS_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_NAND_DQS_OUT (PAD_NAND_DQS_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x100F, PAD_NAND_DQS_OUT, BIT0),
    _RVM1(0x1011, PAD_NAND_DQS_OEN, BIT0),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0, BIT0 ),   //reg[101e21]#0 = 1b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_VSYNC_LIKE_IS_GPIO != GPIO_NONE)
    #define PAD_VSYNC_LIKE_OEN (PAD_VSYNC_LIKE_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_VSYNC_LIKE_OUT (PAD_VSYNC_LIKE_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e91, PAD_VSYNC_LIKE_OUT, BIT5),
    _RVM1(0x1e91, PAD_VSYNC_LIKE_OEN, BIT4),
    //reg_ld_spi4_config
    _RVM1(0x1eb4, 0, BIT3 ),   //reg[101eb4]#3 = 0b
    //reg_ld_spi1cz_config[1:0]
    _RVM1(0x1e3a, 0, BIT5|BIT4 ),   //reg[101e3a]#5 ~ #4 = 00b
    //reg_pwm5_mode
    _RVM1(0x1e3a, 0, BIT1|BIT0 ),   //reg[101e3a]#1 ~ #0 = 00b
    #endif

    #if(PAD_I2S_IN_WS_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_IN_WS_OEN (PAD_I2S_IN_WS_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_I2S_IN_WS_OUT (PAD_I2S_IN_WS_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e6C, PAD_I2S_IN_WS_OUT, BIT0),
    _RVM1(0x1e6E, PAD_I2S_IN_WS_OEN, BIT0),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5|BIT4 ),   //reg[101e05]#5 ~ #4 = 00b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6~#4 = 000b
    //reg_i2sinconfig
    _RVM1(0x1eae, 0, BIT2 ),   //reg[101eae]#2 = 0b
    //reg_mcu_jtag_mode[1:0]
    _RVM1(0x1e06, 0, BIT7|BIT6 ),   //reg[101e06]#7 ~ #6 = 00b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1|BIT0 ),   //reg[101e07]#1 ~ #0 = 00b
    //reg_thirduartmode[1:0]
    _RVM1(0x1e05, 0, BIT3|BIT2 ),   //reg[101e05]#3 ~ #2 = 00b
    //reg_od3rduart[1:0]
    _RVM1(0x1eb6, 0, BIT3|BIT2 ),   //reg[101eb6]#3 ~ #2 = 00b
    //reg_extint6
    _RVM1(0x1ee0, 0, BIT6 ),   //reg[101ee0]#6 = 0b
    #endif

    #if(PAD_I2S_IN_BCK_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_IN_BCK_OEN (PAD_I2S_IN_BCK_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_I2S_IN_BCK_OUT (PAD_I2S_IN_BCK_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e6C, PAD_I2S_IN_BCK_OUT, BIT1),
    _RVM1(0x1e6E, PAD_I2S_IN_BCK_OEN, BIT1),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5|BIT4 ),   //reg[101e05]#5 ~ #4 = 00b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6~#4 = 000b
    //reg_i2sinconfig
    _RVM1(0x1eae, 0, BIT2 ),   //reg[101eae]#2 = 0b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1|BIT0 ),   //reg[101e07]#1 ~ #0 = 00b
    //reg_thirduartmode[1:0]
    _RVM1(0x1e05, 0, BIT3|BIT2 ),   //reg[101e05]#3 ~ #2 = 00b
    //reg_od3rduart[1:0]
    _RVM1(0x1eb6, 0, BIT3|BIT2 ),   //reg[101eb6]#3 ~ #2 = 00b
    //reg_miic_mode2[1:0]
    _RVM1(0x1eb5, 0, BIT5|BIT4 ),   //reg[101eb5]#5 ~ #4 = 00b
    #endif

    #if(PAD_I2S_IN_SD_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_IN_SD_OEN (PAD_I2S_IN_SD_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_I2S_IN_SD_OUT (PAD_I2S_IN_SD_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e6C, PAD_I2S_IN_SD_OUT, BIT2),
    _RVM1(0x1e6E, PAD_I2S_IN_SD_OEN, BIT2),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5|BIT4 ),   //reg[101e05]#5 ~ #4 = 00b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6~#4 = 000b
    //reg_i2sinconfig
    _RVM1(0x1eae, 0, BIT2 ),   //reg[101eae]#2 = 0b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1|BIT0 ),   //reg[101e07]#1 ~ #0 = 00b
    //reg_tserrout[1:0]
    _RVM1(0x1ea2, 0, BIT7 ),   //reg[101ea2]#7 = 0b
    //reg_miic_mode2[1:0]
    _RVM1(0x1eb5, 0, BIT5|BIT4 ),   //reg[101eb5]#5 ~ #4 = 00b
    //reg_3dflagconfig[1:0]
    _RVM1(0x1eb3, 0, BIT7|BIT6 ),   //reg[101eb3]#7 ~ #6 = 00b
    #endif

    #if(PAD_SPDIF_IN_IS_GPIO != GPIO_NONE)
    #define PAD_SPDIF_IN_OEN (PAD_SPDIF_IN_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_SPDIF_IN_OUT (PAD_SPDIF_IN_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e6C, PAD_SPDIF_IN_OUT, BIT3),
    _RVM1(0x1e6E, PAD_SPDIF_IN_OEN, BIT3),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5|BIT4 ),   //reg[101e05]#5 ~ #4 = 00b
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2~#0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6~#4 = 000b
    //reg_spdifinconfig
    _RVM1(0x1eae, 0, BIT6 ),   //reg[101eae]#6 = 0b
    //reg_spdifoutconfig
    _RVM1(0x1eae, 0, BIT7 ),   //reg[101eae]#7 = 0b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1|BIT0 ),   //reg[101e07]#1 ~ #0 = 00b
    //reg_3dflagconfig[1:0]
    _RVM1(0x1eb3, 0, BIT7|BIT6 ),   //reg[101eb3]#7 ~ #6 = 00b
    #endif

    #if(PAD_SPDIF_OUT_IS_GPIO != GPIO_NONE)
    #define PAD_SPDIF_OUT_OEN (PAD_SPDIF_OUT_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_SPDIF_OUT_OUT (PAD_SPDIF_OUT_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e6C, PAD_SPDIF_OUT_OUT, BIT4),
    _RVM1(0x1e6E, PAD_SPDIF_OUT_OEN, BIT4),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT0 ),   //reg[101e24]#2~#0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6~#4 = 000b
    //reg_spdifoutconfig
    _RVM1(0x1eae, 0, BIT7 ),   //reg[101eae]#7 = 0b
    #endif

    #if(PAD_I2S_OUT_MCK_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_MCK_OEN (PAD_I2S_OUT_MCK_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_I2S_OUT_MCK_OUT (PAD_I2S_OUT_MCK_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e6C, PAD_I2S_OUT_MCK_OUT, BIT6),
    _RVM1(0x1e6E, PAD_I2S_OUT_MCK_OEN, BIT6),
    //reg_test_in_mode [2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6~#4 = 000b
    //reg_i2soutconfig[1:0]
    _RVM1(0x1eae, 0, BIT5|BIT4 ),   //reg[101eae]#5 ~ #4 = 00b
    #endif

    #if(PAD_I2S_OUT_WS_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_WS_OEN (PAD_I2S_OUT_WS_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_I2S_OUT_WS_OUT (PAD_I2S_OUT_WS_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e6C, PAD_I2S_OUT_WS_OUT, BIT5),
    _RVM1(0x1e6E, PAD_I2S_OUT_WS_OEN, BIT5),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5|BIT4 ),   //reg[101e05]#5 ~ #4 = 00b
    //reg_test_in_mode [2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6~#4 = 000b
    //reg_i2soutconfig[1:0]
    _RVM1(0x1eae, 0, BIT5|BIT4 ),   //reg[101eae]#5 ~ #4 = 00b
    #endif

    #if(PAD_I2S_OUT_BCK_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_BCK_OEN (PAD_I2S_OUT_BCK_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_I2S_OUT_BCK_OUT (PAD_I2S_OUT_BCK_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e6C, PAD_I2S_OUT_BCK_OUT, BIT7),
    _RVM1(0x1e6E, PAD_I2S_OUT_BCK_OEN, BIT7),
    //reg_test_in_mode [2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6~#4 = 000b
    //reg_i2soutconfig[1:0]
    _RVM1(0x1eae, 0, BIT5|BIT4 ),   //reg[101eae]#5 ~ #4 = 00b
    #endif

    #if(PAD_I2S_OUT_SD_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_SD_OEN (PAD_I2S_OUT_SD_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_I2S_OUT_SD_OUT (PAD_I2S_OUT_SD_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e6D, PAD_I2S_OUT_SD_OUT, BIT0),
    _RVM1(0x1e6F, PAD_I2S_OUT_SD_OEN, BIT0),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5|BIT4 ),   //reg[101e05]#5 ~ #4 = 00b
    //reg_test_in_mode [2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6~#4 = 000b
    //reg_i2soutconfig[1:0]
    _RVM1(0x1eae, 0, BIT5|BIT4 ),   //reg[101eae]#5 ~ #4 = 00b
    #endif

    #if(PAD_I2S_OUT_SD1_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_SD1_OEN (PAD_I2S_OUT_SD1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_I2S_OUT_SD1_OUT (PAD_I2S_OUT_SD1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e6D, PAD_I2S_OUT_SD1_OUT, BIT1),
    _RVM1(0x1e6F, PAD_I2S_OUT_SD1_OEN, BIT1),
    //reg_i2soutconfig[1:0]
    _RVM1(0x1eae, 0, BIT5|BIT4 ),   //reg[101eae]#5 ~ #4 = 00b
    //reg_mcu_jtag_mode[1:0]
    _RVM1(0x1e06, 0, BIT7|BIT6 ),   //reg[101e06]#7 ~ #6 = 00b
    //reg_usbdrvvbusconfig[1:0]
    _RVM1(0x1e04, 0, BIT1|BIT0 ),   //reg[101e04]#1 ~ #0 = 00b
    #endif

    #if(PAD_I2S_OUT_SD2_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_SD2_OEN (PAD_I2S_OUT_SD2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_I2S_OUT_SD2_OUT (PAD_I2S_OUT_SD2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e6D, PAD_I2S_OUT_SD2_OUT, BIT2),
    _RVM1(0x1e6F, PAD_I2S_OUT_SD2_OEN, BIT2),
    //reg_i2soutconfig[1:0]
    _RVM1(0x1eae, 0, BIT5|BIT4 ),   //reg[101eae]#5 ~ #4 = 00b
    //reg_mcu_jtag_mode[1:0]
    _RVM1(0x1e06, 0, BIT7|BIT6 ),   //reg[101e06]#7 ~ #6 = 00b
    //reg_usbdrvvbusconfig[1:0]
    _RVM1(0x1e04, 0, BIT1|BIT0 ),   //reg[101e04]#1 ~ #0 = 00b
    //reg_fourthuartmode[1:0]
    _RVM1(0x1e04, 0, BIT7|BIT6 ),   //reg[101e04]#7 ~ #6 = 00b
    //reg_od4thuart[1:0]
    _RVM1(0x1eb6, 0, BIT5|BIT4 ),   //reg[101eb6]#5 ~ #4 = 00b
    #endif

    #if(PAD_I2S_OUT_SD3_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_SD3_OEN (PAD_I2S_OUT_SD3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_I2S_OUT_SD3_OUT (PAD_I2S_OUT_SD3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e6D, PAD_I2S_OUT_SD3_OUT, BIT3),
    _RVM1(0x1e6F, PAD_I2S_OUT_SD3_OEN, BIT3),
    //reg_i2soutconfig[1:0]
    _RVM1(0x1eae, 0, BIT5|BIT4 ),   //reg[101eae]#5 ~ #4 = 00b
    //reg_mcu_jtag_mode[1:0]
    _RVM1(0x1e06, 0, BIT7|BIT6 ),   //reg[101e06]#7 ~ #6 = 00b
    //reg_fourthuartmode[1:0]
    _RVM1(0x1e04, 0, BIT7|BIT6 ),   //reg[101e04]#7 ~ #6 = 00b
    //reg_od4thuart[1:0]
    _RVM1(0x1eb6, 0, BIT5|BIT4 ),   //reg[101eb6]#5 ~ #4 = 00b
    #endif

    #if(PAD_B_ODD0_IS_GPIO != GPIO_NONE)
    #define PAD_B_ODD0_OEN (PAD_B_ODD0_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_B_ODD0_OUT (PAD_B_ODD0_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x32fc, PAD_B_ODD0_OUT, BIT7),
    _RVM1(0x32fc, PAD_B_ODD0_OEN, BIT3),
    //reg_output_conf[35:34]
    _RVM1(0x32de, 0, BIT3|BIT2 ),   //reg[1032de]#3~#2 = 00b
    //reg_ext_data_en_35_32[3]
    _RVM1(0x32fd, BIT7 , BIT7 ),   //reg[1032fd]#7 = 1b
    //reg_gpo_sel_35_32[3]
    _RVM1(0x32fd, BIT3 , BIT3 ),   //reg[1032fd]#3 = 1b
    #endif

    #if(PAD_B_ODD1_IS_GPIO != GPIO_NONE)
    #define PAD_B_ODD1_OEN (PAD_B_ODD1_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_B_ODD1_OUT (PAD_B_ODD1_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x32fc, PAD_B_ODD1_OUT, BIT6),
    _RVM1(0x32fc, PAD_B_ODD1_OEN, BIT2),
    //reg_output_conf[35:34]
    _RVM1(0x32de, 0, BIT3|BIT2 ),   //reg[1032de]#3~#2 = 00b
    //reg_ext_data_en_35_32[2]
    _RVM1(0x32fd, BIT6 , BIT6 ),   //reg[1032fd]#6 = 1b
    //reg_gpo_sel_35_32[2]
    _RVM1(0x32fd, BIT2 , BIT2 ),   //reg[1032fd]#2 = 1b
    #endif

    #if(PAD_B_ODD2_IS_GPIO != GPIO_NONE)
    #define PAD_B_ODD2_OEN (PAD_B_ODD2_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_B_ODD2_OUT (PAD_B_ODD2_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x32fc, PAD_B_ODD2_OUT, BIT5),
    _RVM1(0x32fc, PAD_B_ODD2_OEN, BIT1),
    //reg_output_conf[33:32]
    _RVM1(0x32de, 0, BIT1|BIT0 ),   //reg[1032de]#1~#0 = 00b
    //reg_ext_data_en_35_32[1]
    _RVM1(0x32fd, BIT5 , BIT5 ),   //reg[1032fd]#5 = 1b
    //reg_gpo_sel_35_32[1]
    _RVM1(0x32fd, BIT1 , BIT1 ),   //reg[1032fd]#1 = 1b
    #endif

    #if(PAD_B_ODD3_IS_GPIO != GPIO_NONE)
    #define PAD_B_ODD3_OEN (PAD_B_ODD3_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_B_ODD3_OUT (PAD_B_ODD3_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x32fc, PAD_B_ODD3_OUT, BIT4),
    _RVM1(0x32fc, PAD_B_ODD3_OEN, BIT0),
    //reg_output_conf[33:32]
    _RVM1(0x32de, 0, BIT1|BIT0 ),   //reg[1032de]#1~#0 = 00b
    //reg_ext_data_en_35_32[0]
    _RVM1(0x32fd, BIT4 , BIT4 ),   //reg[1032fd]#4 = 1b
    //reg_gpo_sel_35_32[0]
    _RVM1(0x32fd, BIT0 , BIT0 ),   //reg[1032fd]#0 = 1b
    #endif

    #if(PAD_B_ODD4_IS_GPIO != GPIO_NONE)
    #define PAD_B_ODD4_OEN (PAD_B_ODD4_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_B_ODD4_OUT (PAD_B_ODD4_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x32a1, PAD_B_ODD4_OUT, BIT7),
    _RVM1(0x32a5, PAD_B_ODD4_OEN, BIT7),
    //reg_output_conf[31:30]
    _RVM1(0x32dd, 0, BIT7|BIT6 ),   //reg[1032dd]#7~#6 = 00b
    //reg_ext_data_en[31]
    _RVM1(0x328f, BIT7 , BIT7 ),   //reg[10328f]#7 = 1b
    //reg_gpo_sel[31]
    _RVM1(0x329d, BIT7 , BIT7 ),   //reg[10329d]#7 = 1b
    #endif

    #if(PAD_B_ODD5_IS_GPIO != GPIO_NONE)
    #define PAD_B_ODD5_OEN (PAD_B_ODD5_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_B_ODD5_OUT (PAD_B_ODD5_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x32a1, PAD_B_ODD5_OUT, BIT6),
    _RVM1(0x32a5, PAD_B_ODD5_OEN, BIT6),
    //reg_output_conf[31:30]
    _RVM1(0x32dd, 0, BIT7|BIT6 ),   //reg[1032dd]#7~#6 = 00b
    //reg_ext_data_en[30]
    _RVM1(0x328f, BIT6 , BIT6 ),   //reg[10328f]#6 = 1b
    //reg_gpo_sel[30]
    _RVM1(0x329d, BIT6 , BIT6 ),   //reg[10329d]#6 = 1b
    #endif

    #if(PAD_B_ODD6_IS_GPIO != GPIO_NONE)
    #define PAD_B_ODD6_OEN (PAD_B_ODD6_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_B_ODD6_OUT (PAD_B_ODD6_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x32a1, PAD_B_ODD6_OUT, BIT5),
    _RVM1(0x32a5, PAD_B_ODD6_OEN, BIT5),
    //reg_output_conf[29:28]
    _RVM1(0x32dd, 0, BIT5|BIT4 ),   //reg[1032dd]#5~#4 = 00b
    //reg_ext_data_en[29]
    _RVM1(0x328f, BIT5 , BIT5 ),   //reg[10328f]#5 = 1b
    //reg_gpo_sel[29]
    _RVM1(0x329d, BIT5 , BIT5 ),   //reg[10329d]#5 = 1b
    #endif

    #if(PAD_B_ODD7_IS_GPIO != GPIO_NONE)
    #define PAD_B_ODD7_OEN (PAD_B_ODD7_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_B_ODD7_OUT (PAD_B_ODD7_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x32a1, PAD_B_ODD7_OUT, BIT4),
    _RVM1(0x32a5, PAD_B_ODD7_OEN, BIT4),
    //reg_output_conf[29:28]
    _RVM1(0x32dd, 0, BIT5|BIT4 ),   //reg[1032dd]#5~#4 = 00b
    //reg_ext_data_en[28]
    _RVM1(0x328f, BIT4 , BIT4 ),   //reg[10328f]#4 = 1b
    //reg_gpo_sel[28]
    _RVM1(0x329d, BIT4 , BIT4 ),   //reg[10329d]#4 = 1b
    #endif

    #if(PAD_G_ODD0_IS_GPIO != GPIO_NONE)
    #define PAD_G_ODD0_OEN (PAD_G_ODD0_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_G_ODD0_OUT (PAD_G_ODD0_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x32a1, PAD_G_ODD0_OUT, BIT3),
    _RVM1(0x32a5, PAD_G_ODD0_OEN, BIT3),
    //reg_output_conf[27:26]
    _RVM1(0x32dd, 0, BIT3|BIT2 ),   //reg[1032dd]#3~#2 = 00b
    //reg_ext_data_en[27]
    _RVM1(0x328f, BIT3 , BIT3 ),   //reg[10328f]#3 = 1b
    //reg_gpo_sel[27]
    _RVM1(0x329d, BIT3 , BIT3 ),   //reg[10329d]#3 = 1b
    #endif

    #if(PAD_G_ODD1_IS_GPIO != GPIO_NONE)
    #define PAD_G_ODD1_OEN (PAD_G_ODD1_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_G_ODD1_OUT (PAD_G_ODD1_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x32a1, PAD_G_ODD1_OUT, BIT2),
    _RVM1(0x32a5, PAD_G_ODD1_OEN, BIT2),
    //reg_output_conf[27:26]
    _RVM1(0x32dd, 0, BIT3|BIT2 ),   //reg[1032dd]#3~#2 = 00b
    //reg_ext_data_en[26]
    _RVM1(0x328f, BIT2 , BIT2 ),   //reg[10328f]#2 = 1b
    //reg_gpo_sel[26]
    _RVM1(0x329d, BIT2 , BIT2 ),   //reg[10329d]#2 = 1b
    #endif

    #if(PAD_G_ODD2_IS_GPIO != GPIO_NONE)
    #define PAD_G_ODD2_OEN (PAD_G_ODD2_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_G_ODD2_OUT (PAD_G_ODD2_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x32a1, PAD_G_ODD2_OUT, BIT1),
    _RVM1(0x32a5, PAD_G_ODD2_OEN, BIT1),
    //reg_output_conf[25:24]
    _RVM1(0x32dd, 0, BIT1|BIT0 ),   //reg[1032dd]#1~#0 = 00b
    //reg_ext_data_en[25]
    _RVM1(0x328f, BIT1 , BIT1 ),   //reg[10328f]#1 = 1b
    //reg_gpo_sel[25]
    _RVM1(0x329d, BIT1 , BIT1 ),   //reg[10329d]#1 = 1b
    #endif

    #if(PAD_G_ODD3_IS_GPIO != GPIO_NONE)
    #define PAD_G_ODD3_OEN (PAD_G_ODD3_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_G_ODD3_OUT (PAD_G_ODD3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x32a1, PAD_G_ODD3_OUT, BIT0),
    _RVM1(0x32a5, PAD_G_ODD3_OEN, BIT0),
    //reg_output_conf[25:24]
    _RVM1(0x32dd, 0, BIT1|BIT0 ),   //reg[1032dd]#1~#0 = 00b
    //reg_ext_data_en[24]
    _RVM1(0x328f, BIT0 , BIT0 ),   //reg[10328f]#0 = 1b
    //reg_gpo_sel[24]
    _RVM1(0x329d, BIT0 , BIT0 ),   //reg[10329d]#0 = 1b
    #endif

    #if(PAD_G_ODD4_IS_GPIO != GPIO_NONE)
    #define PAD_G_ODD4_OEN (PAD_G_ODD4_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_G_ODD4_OUT (PAD_G_ODD4_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x32a0, PAD_G_ODD4_OUT, BIT7),
    _RVM1(0x32a4, PAD_G_ODD4_OEN, BIT7),
    //reg_output_conf[23:22]
    _RVM1(0x32dc, 0, BIT7|BIT6 ),   //reg[1032dc]#7~#6 = 00b
    //reg_ext_data_en[23]
    _RVM1(0x328e, BIT7 , BIT7 ),   //reg[10328e]#7 = 1b
    //reg_gpo_sel[23]
    _RVM1(0x329c, BIT7 , BIT7 ),   //reg[10329c]#7 = 1b
    #endif

    #if(PAD_G_ODD5_IS_GPIO != GPIO_NONE)
    #define PAD_G_ODD5_OEN (PAD_G_ODD5_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_G_ODD5_OUT (PAD_G_ODD5_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x32a0, PAD_G_ODD5_OUT, BIT6),
    _RVM1(0x32a4, PAD_G_ODD5_OEN, BIT6),
    //reg_output_conf[23:22]
    _RVM1(0x32dc, 0, BIT7|BIT6 ),   //reg[1032dc]#7~#6 = 00b
    //reg_ext_data_en[22]
    _RVM1(0x328e, BIT6 , BIT6 ),   //reg[10328e]#6 = 1b
    //reg_gpo_sel[22]
    _RVM1(0x329c, BIT6 , BIT6 ),   //reg[10329c]#6 = 1b
    #endif

    #if(PAD_G_ODD6_IS_GPIO != GPIO_NONE)
    #define PAD_G_ODD6_OEN (PAD_G_ODD6_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_G_ODD6_OUT (PAD_G_ODD6_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x32a0, PAD_G_ODD6_OUT, BIT5),
    _RVM1(0x32a4, PAD_G_ODD6_OEN, BIT5),
    //reg_output_conf[21:20]
    _RVM1(0x32dc, 0, BIT5|BIT4 ),   //reg[1032dc]#5~#4 = 00b
    //reg_ext_data_en[21]
    _RVM1(0x328e, BIT5 , BIT5 ),   //reg[10328e]#5 = 1b
    //reg_gpo_sel[21]
    _RVM1(0x329c, BIT5 , BIT5 ),   //reg[10329c]#5 = 1b
    #endif

    #if(PAD_G_ODD7_IS_GPIO != GPIO_NONE)
    #define PAD_G_ODD7_OEN (PAD_G_ODD7_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_G_ODD7_OUT (PAD_G_ODD7_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x32a0, PAD_G_ODD7_OUT, BIT4),
    _RVM1(0x32a4, PAD_G_ODD7_OEN, BIT4),
    //reg_output_conf[21:20]
    _RVM1(0x32dc, 0, BIT5|BIT4 ),   //reg[1032dc]#5~#4 = 00b
    //reg_ext_data_en[20]
    _RVM1(0x328e, BIT4 , BIT4 ),   //reg[10328e]#4 = 1b
    //reg_gpo_sel[20]
    _RVM1(0x329c, BIT4 , BIT4 ),   //reg[10329c]#4 = 1b
    #endif

    #if(PAD_R_ODD0_IS_GPIO != GPIO_NONE)
    #define PAD_R_ODD0_OEN (PAD_R_ODD0_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_R_ODD0_OUT (PAD_R_ODD0_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x32a0, PAD_R_ODD0_OUT, BIT3),
    _RVM1(0x32a4, PAD_R_ODD0_OEN, BIT3),
    //reg_output_conf[19:18]
    _RVM1(0x32dc, 0, BIT3|BIT2 ),   //reg[1032dc]#3~#2 = 00b
    //reg_ext_data_en[19]
    _RVM1(0x328e, BIT3 , BIT3 ),   //reg[10328e]#3 = 1b
    //reg_gpo_sel[19]
    _RVM1(0x329c, BIT3 , BIT3 ),   //reg[10329c]#3 = 1b
    #endif

    #if(PAD_R_ODD1_IS_GPIO != GPIO_NONE)
    #define PAD_R_ODD1_OEN (PAD_R_ODD1_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_R_ODD1_OUT (PAD_R_ODD1_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x32a0, PAD_R_ODD1_OUT, BIT2),
    _RVM1(0x32a4, PAD_R_ODD1_OEN, BIT2),
    //reg_output_conf[19:18]
    _RVM1(0x32dc, 0, BIT3|BIT2 ),   //reg[1032dc]#3~#2 = 00b
    //reg_ext_data_en[18]
    _RVM1(0x328e, BIT2 , BIT2 ),   //reg[10328e]#2 = 1b
    //reg_gpo_sel[18]
    _RVM1(0x329c, BIT2 , BIT2 ),   //reg[10329c]#2 = 1b
    #endif

    #if(PAD_R_ODD2_IS_GPIO != GPIO_NONE)
    #define PAD_R_ODD2_OEN (PAD_R_ODD2_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_R_ODD2_OUT (PAD_R_ODD2_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x32a0, PAD_R_ODD2_OUT, BIT1),
    _RVM1(0x32a4, PAD_R_ODD2_OEN, BIT1),
    //reg_output_conf[17:16]
    _RVM1(0x32dc, 0, BIT1|BIT0 ),   //reg[1032dc]#1~#0 = 00b
    //reg_ext_data_en[17]
    _RVM1(0x328e, BIT1 , BIT1 ),   //reg[10328e]#1 = 1b
    //reg_gpo_sel[17]
    _RVM1(0x329c, BIT1 , BIT1 ),   //reg[10329c]#1 = 1b
    #endif

    #if(PAD_R_ODD3_IS_GPIO != GPIO_NONE)
    #define PAD_R_ODD3_OEN (PAD_R_ODD3_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_R_ODD3_OUT (PAD_R_ODD3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x32a0, PAD_R_ODD3_OUT, BIT0),
    _RVM1(0x32a4, PAD_R_ODD3_OEN, BIT0),
    //reg_output_conf[17:16]
    _RVM1(0x32dc, 0, BIT1|BIT0 ),   //reg[1032dc]#1~#0 = 00b
    //reg_ext_data_en[16]
    _RVM1(0x328e, BIT0 , BIT0 ),   //reg[10328e]#0 = 1b
    //reg_gpo_sel[16]
    _RVM1(0x329c, BIT0 , BIT0 ),   //reg[10329c]#0 = 1b
    #endif

    #if(PAD_R_ODD4_IS_GPIO != GPIO_NONE)
    #define PAD_R_ODD4_OEN (PAD_R_ODD4_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_R_ODD4_OUT (PAD_R_ODD4_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x329f, PAD_R_ODD4_OUT, BIT7),
    _RVM1(0x32a3, PAD_R_ODD4_OEN, BIT7),
    //reg_output_conf[15:14]
    _RVM1(0x32db, 0, BIT7|BIT6 ),   //reg[1032db]#7~#6 = 00b
    //reg_ext_data_en[15]
    _RVM1(0x328d, BIT7 , BIT7 ),   //reg[10328d]#7 = 1b
    //reg_gpo_sel[15]
    _RVM1(0x329b, BIT7 , BIT7 ),   //reg[10329b]#7 = 1b
    #endif

    #if(PAD_R_ODD5_IS_GPIO != GPIO_NONE)
    #define PAD_R_ODD5_OEN (PAD_R_ODD5_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_R_ODD5_OUT (PAD_R_ODD5_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x329f, PAD_R_ODD5_OUT, BIT6),
    _RVM1(0x32a3, PAD_R_ODD5_OEN, BIT6),
    //reg_output_conf[15:14]
    _RVM1(0x32db, 0, BIT7|BIT6 ),   //reg[1032db]#7~#6 = 00b
    //reg_ext_data_en[14]
    _RVM1(0x328d, BIT6 , BIT6 ),   //reg[10328d]#6 = 1b
    //reg_gpo_sel[14]
    _RVM1(0x329b, BIT6 , BIT6 ),   //reg[10329b]#6 = 1b
    #endif

    #if(PAD_R_ODD6_IS_GPIO != GPIO_NONE)
    #define PAD_R_ODD6_OEN (PAD_R_ODD6_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_R_ODD6_OUT (PAD_R_ODD6_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x329f, PAD_R_ODD6_OUT, BIT5),
    _RVM1(0x32a3, PAD_R_ODD6_OEN, BIT5),
    //reg_output_conf[13:12]
    _RVM1(0x32db, 0, BIT5|BIT4 ),   //reg[1032db]#5~#4 = 00b
    //reg_ext_data_en[13]
    _RVM1(0x328d, BIT5 , BIT5 ),   //reg[10328d]#5 = 1b
    //reg_gpo_sel[13]
    _RVM1(0x329b, BIT5 , BIT5 ),   //reg[10329b]#5 = 1b
    #endif

    #if(PAD_R_ODD7_IS_GPIO != GPIO_NONE)
    #define PAD_R_ODD7_OEN (PAD_R_ODD7_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_R_ODD7_OUT (PAD_R_ODD7_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x329f, PAD_R_ODD7_OUT, BIT4),
    _RVM1(0x32a3, PAD_R_ODD7_OEN, BIT4),
    //reg_output_conf[13:12]
    _RVM1(0x32db, 0, BIT5|BIT4 ),   //reg[1032db]#5~#4 = 00b
    //reg_ext_data_en[12]
    _RVM1(0x328d, BIT4 , BIT4 ),   //reg[10328d]#4 = 1b
    //reg_gpo_sel[12]
    _RVM1(0x329b, BIT4 , BIT4 ),   //reg[10329b]#4 = 1b
    #endif

    #if(PAD_LCK_IS_GPIO != GPIO_NONE)
    #define PAD_LCK_OEN (PAD_LCK_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_LCK_OUT (PAD_LCK_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x329e, PAD_LCK_OUT, BIT3),
    _RVM1(0x32a2, PAD_LCK_OEN, BIT3),
    //reg_output_conf[3:2]
    _RVM1(0x32da, 0, BIT3|BIT2 ),   //reg[1032da]#3~#2 = 00b
    //reg_ext_data_en[3]
    _RVM1(0x328c, BIT3 , BIT3 ),   //reg[10328c]#3 = 1b
    //reg_gpo_sel[3]
    _RVM1(0x329a, BIT3 , BIT3 ),   //reg[10329a]#3 = 1b
    #endif

    #if(PAD_LDE_IS_GPIO != GPIO_NONE)
    #define PAD_LDE_OEN (PAD_LDE_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_LDE_OUT (PAD_LDE_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x329e, PAD_LDE_OUT, BIT2),
    _RVM1(0x32a2, PAD_LDE_OEN, BIT2),
    //reg_output_conf[3:2]
    _RVM1(0x32da, 0, BIT3|BIT2 ),   //reg[1032da]#3~#2 = 00b
    //reg_ext_data_en[2]
    _RVM1(0x328c, BIT2 , BIT2 ),   //reg[10328c]#2 = 1b
    //reg_gpo_sel[2]
    _RVM1(0x329a, BIT2 , BIT2 ),   //reg[10329a]#2 = 1b
    #endif

    #if(PAD_LHSYNC_IS_GPIO != GPIO_NONE)
    #define PAD_LHSYNC_OEN (PAD_LHSYNC_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_LHSYNC_OUT (PAD_LHSYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x329e, PAD_LHSYNC_OUT, BIT1),
    _RVM1(0x32a2, PAD_LHSYNC_OEN, BIT1),
    //reg_output_conf[1:0]
    _RVM1(0x32da, 0, BIT1|BIT0 ),   //reg[1032da]#1~#0 = 00b
    //reg_ext_data_en[1]
    _RVM1(0x328c, BIT1 , BIT1 ),   //reg[10328c]#1 = 1b
    //reg_gpo_sel[1]
    _RVM1(0x329a, BIT1 , BIT1 ),   //reg[10329a]#1 = 1b
    #endif

    #if(PAD_LVSYNC_IS_GPIO != GPIO_NONE)
    #define PAD_LVSYNC_OEN (PAD_LVSYNC_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_LVSYNC_OUT (PAD_LVSYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x329e, PAD_LVSYNC_OUT, BIT0),
    _RVM1(0x32a2, PAD_LVSYNC_OEN, BIT0),
    //reg_output_conf[1:0]
    _RVM1(0x32da, 0, BIT1|BIT0 ),   //reg[1032da]#1~#0 = 00b
    //reg_ext_data_en[0]
    _RVM1(0x328c, BIT0 , BIT0 ),   //reg[10328c]#0 = 1b
    //reg_gpo_sel[0]
    _RVM1(0x329a, BIT0 , BIT0 ),   //reg[10329a]#0 = 1b
    #endif

    #if(PAD_PCM_WE_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_WE_N_OEN (PAD_PCM_WE_N_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_PCM_WE_N_OUT (PAD_PCM_WE_N_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e77, PAD_PCM_WE_N_OUT, BIT7),
    _RVM1(0x1e7d, PAD_PCM_WE_N_OEN, BIT7),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_pcmctrlconfig
    _RVM1(0x1e9f, 0, BIT7 ),   //reg[101e9f]#7 = 0b
    #endif

    #if(PAD_NAND_WPZ_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_WPZ_OEN (PAD_NAND_WPZ_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_NAND_WPZ_OUT (PAD_NAND_WPZ_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e89, PAD_NAND_WPZ_OUT, BIT5),
    _RVM1(0x1e88, PAD_NAND_WPZ_OEN, BIT5),
    //reg_test_in_mode[2:0]
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0),   //reg[101e24]#2~#0
    //reg_test_out_mode[2:0]
    _RVM1(0x1e24, 0, BIT6|BIT5|BIT4 ),   //reg[101e24]#6 ~ #4 = 000b
    //reg_nand_mode[2:0]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 00b
    _RVM1(0x1ea1, 0, BIT1|BIT0 ),   //reg[101ea1]#1 ~ #0 = 00b
    #endif

    _MEMMAP_PM_,

    #if(PAD_PWM_PM_IS_GPIO != GPIO_NONE)
    #define PAD_PWM_PM_OEN (PAD_PWM_PM_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_PWM_PM_OUT (PAD_PWM_PM_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0e3a, PAD_PWM_PM_OUT, BIT1),
    _RVM1(0x0e3c, PAD_PWM_PM_OEN, BIT1),
    //reg_pwm_pm_is_gpio
    _RVM1(0x0e38, BIT5 , BIT5 ),   //reg[0e38]#5 = 1
    #endif

    #if(PAD_AV_LNK_IS_GPIO != GPIO_NONE)
    #define PAD_AV_LNK_OEN (PAD_AV_LNK_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_AV_LNK_OUT (PAD_AV_LNK_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x0e3a, PAD_AV_LNK_OUT, BIT3),
    _RVM1(0x0e3c, PAD_AV_LNK_OEN, BIT3),
    //reg_av_lnk_is_gpio
    _RVM1(0x0e38, BIT7 , BIT7 ),   //reg[0e38]#7 = 1
    #endif

    _MEMMAP_nonPM_,

    #if(PAD_SPI1_CK_IS_GPIO != GPIO_NONE)
    #define PAD_SPI1_CK_OEN (PAD_SPI1_CK_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_SPI1_CK_OUT (PAD_SPI1_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e90, PAD_SPI1_CK_OUT, BIT4),
    _RVM1(0x1e90, PAD_SPI1_CK_OEN, BIT0),
    //reg_ld_spi1_config
    _RVM1(0x1eb4, 0, BIT0 ),   //reg[101eb4]#0 = 0b
    //reg_ld_spi3_config
    _RVM1(0x1eb4, 0, BIT2 ),   //reg[101eb4]#2 = 0b
    #endif

    #if(PAD_SPI1_DI_IS_GPIO != GPIO_NONE)
    #define PAD_SPI1_DI_OEN (PAD_SPI1_DI_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_SPI1_DI_OUT (PAD_SPI1_DI_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e90, PAD_SPI1_DI_OUT, BIT5),
    _RVM1(0x1e90, PAD_SPI1_DI_OEN, BIT1),
    //reg_ld_spi1_config
    _RVM1(0x1eb4, 0, BIT0 ),   //reg[101eb4]#0 = 0b
    //reg_ld_spi3_config
    _RVM1(0x1eb4, 0, BIT2 ),   //reg[101eb4]#2 = 0b
    #endif

    #if(PAD_SPI2_CK_IS_GPIO != GPIO_NONE)
    #define PAD_SPI2_CK_OEN (PAD_SPI2_CK_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_SPI2_CK_OUT (PAD_SPI2_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e90, PAD_SPI2_CK_OUT, BIT6),
    _RVM1(0x1e90, PAD_SPI2_CK_OEN, BIT2),
    //reg_ld_spi2_config
    _RVM1(0x1eb4, 0, BIT1 ),   //reg[101eb4]#1 = 0b
    //reg_ld_spi3_config
    _RVM1(0x1eb4, 0, BIT2 ),   //reg[101eb4]#2 = 0b
    #endif

    #if(PAD_SPI2_DI_IS_GPIO != GPIO_NONE)
    #define PAD_SPI2_DI_OEN (PAD_SPI2_DI_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_SPI2_DI_OUT (PAD_SPI2_DI_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e90, PAD_SPI2_DI_OUT, BIT7),
    _RVM1(0x1e90, PAD_SPI2_DI_OEN, BIT3),
    //reg_ld_spi2_config
    _RVM1(0x1eb4, 0, BIT1 ),   //reg[101eb4]#1 = 0b
    //reg_ld_spi3_config
    _RVM1(0x1eb4, 0, BIT2 ),   //reg[101eb4]#2 = 0b
    #endif

    _MEMMAP_nonPM_SPARE0_,
    #if(PAD_TCON0_IS_GPIO != GPIO_NONE)
    #define PAD_TCON0_OEN (PAD_TCON0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_TCON0_OUT (PAD_TCON0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1008, PAD_TCON0_OUT, BIT0),
    _RVM1(0x100A, PAD_TCON0_OEN, BIT0),
    _MEMMAP_nonPM_,
    _RVM1(0x1eb9, 0, BIT0 ),   //reg[101eb9]#0 = 0b
    #endif

    _MEMMAP_nonPM_SPARE0_,
    #if(PAD_TCON1_IS_GPIO != GPIO_NONE)
    #define PAD_TCON1_OEN (PAD_TCON1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_TCON1_OUT (PAD_TCON1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1008, PAD_TCON1_OUT, BIT1),
    _RVM1(0x100A, PAD_TCON1_OEN, BIT1),
    _MEMMAP_nonPM_,
    _RVM1(0x1eb9, 0, BIT1 ),   //reg[101eb9]#1 = 0b
    #endif

    _MEMMAP_nonPM_SPARE0_,
    #if(PAD_TCON2_IS_GPIO != GPIO_NONE)
    #define PAD_TCON2_OEN (PAD_TCON2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_TCON2_OUT (PAD_TCON2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1008, PAD_TCON2_OUT, BIT2),
    _RVM1(0x100A, PAD_TCON2_OEN, BIT2),
    _MEMMAP_nonPM_,
    _RVM1(0x1eb9, 0, BIT2 ),   //reg[101eb9]#2 = 0b
    #endif

    _MEMMAP_nonPM_SPARE0_,
    #if(PAD_TCON3_IS_GPIO != GPIO_NONE)
    #define PAD_TCON3_OEN (PAD_TCON3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_TCON3_OUT (PAD_TCON3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1008, PAD_TCON3_OUT, BIT3),
    _RVM1(0x100A, PAD_TCON3_OEN, BIT3),
    _MEMMAP_nonPM_,
    _RVM1(0x1eb9, 0, BIT3 ),   //reg[101eb9]#3 = 0b
    #endif

    _MEMMAP_nonPM_SPARE0_,
    #if(PAD_TCON4_IS_GPIO != GPIO_NONE)
    #define PAD_TCON4_OEN (PAD_TCON4_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_TCON4_OUT (PAD_TCON4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1008, PAD_TCON4_OUT, BIT4),
    _RVM1(0x100A, PAD_TCON4_OEN, BIT4),
    _MEMMAP_nonPM_,
    _RVM1(0x1eb9, 0, BIT4 ),   //reg[101eb9]#4 = 0b
    #endif

    _MEMMAP_nonPM_SPARE0_,
    #if(PAD_TCON5_IS_GPIO != GPIO_NONE)
    #define PAD_TCON5_OEN (PAD_TCON5_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TCON5_OUT (PAD_TCON5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1008, PAD_TCON5_OUT, BIT5),
    _RVM1(0x100A, PAD_TCON5_OEN, BIT5),
    _MEMMAP_nonPM_,
    _RVM1(0x1eb9, 0, BIT5 ),   //reg[101eb9]#5 = 0b
    #endif

    _MEMMAP_nonPM_SPARE0_,
    #if(PAD_TCON6_IS_GPIO != GPIO_NONE)
    #define PAD_TCON6_OEN (PAD_TCON6_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_TCON6_OUT (PAD_TCON6_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1008, PAD_TCON6_OUT, BIT6),
    _RVM1(0x100A, PAD_TCON6_OEN, BIT6),
    _MEMMAP_nonPM_,
    _RVM1(0x1eb9, 0, BIT6 ),   //reg[101eb9]#6 = 0b
    #endif

    _MEMMAP_nonPM_SPARE0_,
    #if(PAD_TCON7_IS_GPIO != GPIO_NONE)
    #define PAD_TCON7_OEN (PAD_TCON7_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_TCON7_OUT (PAD_TCON7_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1008, PAD_TCON7_OUT, BIT7),
    _RVM1(0x100A, PAD_TCON7_OEN, BIT7),
    _MEMMAP_nonPM_,
    _RVM1(0x1eb9, 0, BIT7 ),   //reg[101eb9]#7 = 0b
    #endif

    _MEMMAP_nonPM_,
//---------------------------------------------------------------------
// Pad Configuartion
//---------------------------------------------------------------------
#if (PADS_VSYNC_VIF_OUT_EN != Unknown_pad_mux)
#define VSYNC_VIF_OUT_EN   ((PADS_VSYNC_VIF_OUT_EN == ENABLE) ? BIT6 : 0)
            _RVM1(0x1EA3, VSYNC_VIF_OUT_EN, BIT6),
#endif

#if (PADS_TS0_CONFIG != Unknown_pad_mux)
#define TS0_CONFIG   ((PADS_TS0_CONFIG == PARALLEL_IN) ? BIT2 : \
                      (PADS_TS0_CONFIG == SERIAL_IN) ? BIT3 : 0)
            _RVM1(0x1EA3, TS0_CONFIG, BITMASK(3:2)),
#endif

#if (PADS_TS1_CONFIG != Unknown_pad_mux)
#define TS1_CONFIG   ((PADS_TS1_CONFIG == PARALLEL_IN) ? BIT4 : \
                      (PADS_TS1_CONFIG == PARALLEL_OUT) ? BIT5 : \
                      (PADS_TS1_CONFIG == SERIAL_IN) ? (BIT5|BIT4) : 0)
            _RVM1(0x1EA3, TS1_CONFIG, BITMASK(5:4)),
#endif

#if (PADS_TS1_CLK != Unknown_pad_mux)                             // TS1_CLK driving  :8MA
	_RVM1(0x1e12, 1, BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0 ),   //reg[101e12]#7 ~ #0 = 11111111b
    _RVM1(0x1e13, 1, BIT2|BIT1|BIT0 ),                            //reg[101e13]#2 ~ #0 = 111b
    _RVM1(0x1e13, 0, BIT7|BIT6|BIT5|BIT4|BIT3 ),                  //reg[101e13]#7 ~ #3 = 00000b
#endif

#if (PADS_TS_OUT != Unknown_pad_mux)
#define TS_OUT_MODE   ((PADS_TS_OUT == ENABLE) ? BIT1: 0)
            _RVM1(0x1EA3, TS_OUT_MODE, BIT1),
#endif


#if (PADS_NAND_MODE != Unknown_pad_mux)
#if (PADS_NAND_MODE == PCM_D) || (PADS_NAND_MODE == NAND_AD)
    _RVM1(0x1EA0, BIT7, BIT7),
#else
    _RVM1(0x1EA0, 0, BIT7),
#endif
#define NAND_MODE   ((PADS_NAND_MODE == PCM_A) ? BIT0: \
                     (PADS_NAND_MODE == NAND_AD) ? BIT0: \
                     (PADS_NAND_MODE == NAND_AD_DQS) ? BIT1 : 0)
    _RVM1(0x1EA1, NAND_MODE, BITMASK(1:0)),
#else
    _RVM1(0x1EA0, 0x00, BIT7),
    _RVM1(0x1EA1, 0x00, BITMASK(1:0)),
#endif

#if (PADS_PCM1_CTRL != Unknown_pad_mux)
#define PCM1_CTRL   ((PADS_PCM1_CTRL == ENABLE) ? BIT7 : 0)
        _RVM1(0x1E9F, PCM1_CTRL, BIT7),
#endif

#if (PADS_PCM1_AD != Unknown_pad_mux)
#define PCM1_AD   ((PADS_PCM1_AD == ENABLE) ? BIT6 : 0)
        _RVM1(0x1E9F, PCM1_AD, BIT6),
#endif

#if (PADS_PCM1_PE != Unknown_pad_mux)
#if (PADS_PCM1_PE == PCM_PE_ON)
        _RVM1(0x1E16, 0xFF, 0xFF),
        _RVM1(0x1E17, 0xFF, 0xFF),
        _RVM1(0x1E18, 0xFF, 0xFF),
        _RVM1(0x1E19, 0xFF, 0xFF),
        _RVM1(0x1E1A, 0x03, 0x03),
#else
        _RVM1(0x1E16, 0x00, 0xFF),
        _RVM1(0x1E17, 0x00, 0xFF),
        _RVM1(0x1E18, 0x00, 0xFF),
        _RVM1(0x1E19, 0x00, 0xFF),
        _RVM1(0x1E1A, 0x00, 0x03),
#endif
#endif

#if (PADS_CI_CTRL != Unknown_pad_mux)
#define CI_CTRL   ((PADS_CI_CTRL == ENABLE) ? BIT1 : 0)
        _RVM1(0x1EC8, CI_CTRL, BIT1),
#endif

#if (PADS_CI_AD != Unknown_pad_mux)
#define CI_AD   ((PADS_CI_AD == ENABLE) ? BIT0 : 0)
        _RVM1(0x1EC8, CI_AD, BIT0),
#endif

#if (PADS_PCM2_CTRL != Unknown_pad_mux)
#define PCM2_CTRL   ((PADS_PCM2_CTRL == ENABLE) ? BIT5 : 0)
        _RVM1(0x1E9F, PCM2_CTRL, BIT5),
#endif

#if (PADS_SPDIF_OUT != Unknown_pad_mux)
#define SPDIF_OUT   ((PADS_SPDIF_OUT == PAD_SPDIF_OUT) ? BIT7 : 0)
        _RVM1(0x1EAE, SPDIF_OUT, BIT7),
#endif

#if (PADS_SPDIF_IN != Unknown_pad_mux)
#define SPDIF_IN   ((PADS_SPDIF_IN == PAD_SPDIF_IN) ? BIT6 : 0)
        _RVM1(0x1EAE, SPDIF_IN, BIT6),
#endif

#if (PADS_I2S_IN != Unknown_pad_mux)
#define I2S_IN    ((PADS_I2S_IN == ENABLE) ? BIT2 : 0)
        _RVM1(0x1EAE, I2S_IN, BIT2),
#endif

#if (PADS_I2S_MUTE != Unknown_pad_mux)
#define I2S_MUTE   ((PADS_I2S_MUTE == PAD_GPIO15) ? BIT6 : \
                    (PADS_I2S_MUTE == PAD_PWM4) ? BIT7 : 0)
        _RVM1(0x1E05, I2S_MUTE, BIT7|BIT6),
#endif

#if (PADS_I2S_OUT != Unknown_pad_mux)
#define I2S_OUT   ((PADS_I2S_OUT == SINGLE_CH_I2S_OUT) ? BIT4 : \
                       (PADS_I2S_OUT == MULTI_CH_I2S_OUT) ? BIT5 : 0)
        _RVM1(0x1EAE, I2S_OUT, BIT5|BIT4),
#endif

#if (PADS_MPIF_MODE != Unknown_pad_mux)
#define MPIF_MODE   ((PADS_MPIF_MODE == ONE_BIT_MODE) ? BIT6 : \
                     (PADS_MPIF_MODE == TWO_BIT_MODE) ? BIT7 : \
                     (PADS_MPIF_MODE == FOUR_BIT_MODE) ? BIT7|BIT6 : 0)
        _RVM1(0x1EB5, MPIF_MODE, BIT7|BIT6),
#endif

#if (PADS_ET_MODE != Unknown_pad_mux)
#define ET_MODE   ((PADS_ET_MODE == ENABLE) ? BIT0 : 0)
        _RVM1(0x1EDF, ET_MODE, BIT0),
#endif

#if (PADS_3D_FLAG_CONFIG != Unknown_pad_mux)
#define FLAG_CONFIG   ((PADS_3D_FLAG_CONFIG == PAD_SPDIF_IN) ? BIT6 : \
                       (PADS_3D_FLAG_CONFIG == PAD_GPIO16) ? BIT7 : \
                       (PADS_3D_FLAG_CONFIG == PAD_I2S_IN_SD) ? BIT7|BIT6 : 0)
        _RVM1(0x1EB3, FLAG_CONFIG, BIT7|BIT6),
#endif

//==========
// UART Modes
//==========
#if (PADS_UART2_MODE != Unknown_pad_mux)
#define UART2_MODE   ((PADS_UART2_MODE == PAD_GPIO7) ? BIT0: \
                      (PADS_UART2_MODE == PAD_GPIO8) ? BIT0: \
                      (PADS_UART2_MODE == PAD_GPIO19) ? BIT1: \
                      (PADS_UART2_MODE == PAD_GPIO20) ? BIT1: \
                      (PADS_UART2_MODE == PAD_GPIO3) ? BIT1|BIT0: \
                      (PADS_UART2_MODE == PAD_GPIO4) ? BIT1|BIT0: 0 )
        _RVM1(0x1E05, UART2_MODE, BIT1|BIT0),
#endif

#if (PADS_UART3_MODE != Unknown_pad_mux)
#define UART3_MODE   ((PADS_UART3_MODE == PAD_GPIO9) ? BIT2: \
                      (PADS_UART3_MODE == PAD_GPIO10) ? BIT2: \
                      (PADS_UART3_MODE == PAD_I2S_IN_WS) ? BIT3: \
                      (PADS_UART3_MODE == PAD_I2S_IN_BCK) ? BIT3: \
                      (PADS_UART3_MODE == PAD_UART_TX2) ? BIT3|BIT2: \
                      (PADS_UART3_MODE == PAD_UART_RX2) ? BIT3|BIT2: 0 )
        _RVM1(0x1E05, UART3_MODE, BIT3|BIT2),
#endif

#if (PADS_UART4_MODE != Unknown_pad_mux)
#define UART4_MODE   ((PADS_UART4_MODE == PAD_GPIO11) ? BIT6: \
                      (PADS_UART4_MODE == PAD_GPIO12) ? BIT6: \
                      (PADS_UART4_MODE == PAD_GPIO23) ? BIT7: \
                      (PADS_UART4_MODE == PAD_GPIO24) ? BIT7: \
                      (PADS_UART4_MODE == PAD_I2S_OUT_SD2) ? BIT7|BIT6: \
                      (PADS_UART4_MODE == PAD_I2S_OUT_SD3) ? BIT7|BIT6: 0 )
        _RVM1(0x1E04, UART4_MODE, BIT7|BIT6),
#endif

#if (PADS_FAST_UART_MODE != Unknown_pad_mux)
#define FAST_UART_MODE   ((PADS_FAST_UART_MODE == PAD_GPIO5) ? BIT4: \
                          (PADS_FAST_UART_MODE == PAD_GPIO6) ? BIT4: \
                          (PADS_FAST_UART_MODE == PAD_GPIO25) ? BIT5: \
                          (PADS_FAST_UART_MODE == PAD_GPIO26) ? BIT5: \
                          (PADS_FAST_UART_MODE == PAD_GPIO13) ? BIT5|BIT4: \
                          (PADS_FAST_UART_MODE == PAD_GPIO14) ? BIT5|BIT4: 0 )
        _RVM1(0x1E04, FAST_UART_MODE, BIT5|BIT4),
#endif


#if (PADS_MSPI_MODE != Unknown_pad_mux)
#define MSPI_MODE   ((PADS_MSPI_MODE == SPI_PAD0) ? BIT0:  \
                     (PADS_MSPI_MODE == SPI_PAD1) ? BIT1:  \
                     (PADS_MSPI_MODE == SPI_PAD2) ? BIT2:  \
                     (PADS_MSPI_MODE == SPI_PAD3) ? BIT3: 0)
        _RVM1(0x1EB4, MSPI_MODE, BIT3|BIT2|BIT1|BIT0),
#endif

//==========
// UART Select
//==========
#define UART_INV    ((UART0_INV ? BIT0 : 0) | \
                     (UART1_INV ? BIT1 : 0) | \
                     (UART2_INV ? BIT2 : 0) | \
                     (UART3_INV ? BIT3 : 0) | \
                     (UART4_INV ? BIT4 : 0))

        _RVM1(0x1EAB, UART_INV, BITMASK(4:0)),
        _RVM1(0x1EA6, (UART1_SRC_SEL << 4) | (UART0_SRC_SEL << 0), BITMASK(7:0)),
        _RVM1(0x1EA7, (UART3_SRC_SEL << 4) | (UART2_SRC_SEL << 0), BITMASK(7:0)),
        _RVM1(0x1EA8, (UART4_SRC_SEL << 0), BITMASK(3:0)),

#if (PADS_PWM0_MODE != Unknown_pad_mux)
#define PWM0_MODE   ((PADS_PWM0_MODE == PAD_PWM0) ? BIT0:  0)
        _RVM1(0x1EA2, PWM0_MODE, BIT0),
#endif

#if (PADS_PWM1_MODE != Unknown_pad_mux)
#define PWM1_MODE   ((PADS_PWM1_MODE == PAD_PWM1) ? BIT1:  0)
        _RVM1(0x1EA2, PWM1_MODE, BIT1),
#endif

#if (PADS_PWM2_MODE != Unknown_pad_mux)
#define PWM2_MODE   ((PADS_PWM2_MODE == PAD_PWM2) ? BIT2:  0)
        _RVM1(0x1EA2, PWM2_MODE, BIT2),
        _RVM1(0x1E06, ~(BIT2), BIT2),//pwm2 output enable
#endif

#if (PADS_PWM3_MODE != Unknown_pad_mux)
#define PWM3_MODE   ((PADS_PWM3_MODE == PAD_PWM3) ? BIT3:  0)
        _RVM1(0x1EA2, PWM3_MODE, BIT3),
#endif

#if (PADS_PWM4_MODE != Unknown_pad_mux) //??
#define PWM4_MODE   ((PADS_PWM4_MODE == PAD_PWM4) ? BIT4:  0)
        _RVM1(0x1EA2, PWM4_MODE, BIT4),
#endif

#if (PADS_PWM5_MODE != Unknown_pad_mux)
#define PWM5_MODE   ((PADS_PWM5_MODE == PAD_B_ODD3) ? BIT0:  \
                     (PADS_PWM5_MODE == PAD_VSYNC_LIKE) ? BIT1: 0)
        _RVM1(0x1E3A, PWM5_MODE, BIT1|BIT0),
#endif

#if (PADS_NAND_CS1_EN != Unknown_pad_mux)
#define NAND_CS1_EN   ((PADS_NAND_CS1_EN == PAD_NAND_CEZ1) ? BIT2:  0)
        _RVM1(0x1EA1, NAND_CS1_EN, BIT2),
#endif

#if (PADS_TSERR_OUT != Unknown_pad_mux)
#define TSERR_OUT   ((PADS_TSERR_OUT == PAD_I2S_IN_SD) ? BIT7:  \
                     (PADS_TSERR_OUT == PAD_GPIO16) ? BIT8:  \
                     (PADS_TSERR_OUT == PAD_PWM4) ? BIT8|BIT7:  0)
        _RVM2(0x1EA2, TSERR_OUT, BIT8|BIT7),
#endif

#if (PADS_BT656_CTRL != Unknown_pad_mux)
#define BT656_CTR   ((PADS_BT656_CTRL == TS1_PADs) ? BIT6:  \
                     (PADS_BT656_CTRL == PCM_PADs) ? BIT7:  \
                     (PADS_BT656_CTRL == GPIO_PADs) ? BIT7|BIT6:  0)
        _RVM1(0x1EDF, BT656_CTR, BIT7|BIT6),
#endif


#if (PADS_DDCR_MODE != Unknown_pad_mux)
#define DDCR_MODE   ((PADS_DDCR_MODE == DDCR_PADs) ? BIT0:  \
                     (PADS_DDCR_MODE == SCK_PADs) ? BIT1:  0)
        _RVM1(0x1EAE, DDCR_MODE, BIT1|BIT0),
#endif

#if (PADS_MIIC_MODE0 != Unknown_pad_mux)
#define MIIC_MODE0  ((PADS_MIIC_MODE0 == PAD_GPIO17) ? BIT0:  \
                     (PADS_MIIC_MODE0 == PAD_GPIO18) ? BIT0:  \
                     (PADS_MIIC_MODE0 == PAD_TS1_CLK) ? BIT1:  \
                     (PADS_MIIC_MODE0 == PAD_TS1_SYNC) ? BIT1:  0)
    _RVM1(0x1EB5, MIIC_MODE0, BIT1|BIT0),
#endif

//PAD_TS1_VLD & PAD_TS1_D0: priority => miic_mode1 higher than miic_mode2
#if (PADS_MIIC_MODE1 != Unknown_pad_mux)
#define MIIC_MODE1  ((PADS_MIIC_MODE1 == PAD_TGPIO2) ? BIT2:  \
                     (PADS_MIIC_MODE1 == PAD_TGPIO3) ? BIT2:  \
                     (PADS_MIIC_MODE1 == PAD_TS1_VLD) ? BIT3:  \
                     (PADS_MIIC_MODE1 == PAD_TS1_D0) ? BIT3:  0)
    _RVM1(0x1EB5, MIIC_MODE1, BIT3|BIT2),
#endif

#if (PADS_MIIC_MODE2 != Unknown_pad_mux)
#define MIIC_MODE2  ((PADS_MIIC_MODE2 == PAD_I2S_IN_BCK) ? BIT4:  \
                     (PADS_MIIC_MODE2 == PAD_I2S_IN_SD) ? BIT4:  \
                     (PADS_MIIC_MODE2 == PAD_TS1_VLD) ? BIT5:  \
                     (PADS_MIIC_MODE2 == PAD_TS1_D0) ? BIT5:  0)
    _RVM1(0x1EB5, MIIC_MODE2, BIT5|BIT4),
#endif

#if (PADS_P1_ENABLE != Unknown_pad_mux)
#define P1_B0    ((PADS_P1_ENABLE & BIT0) ? BIT0 : 0)
#define P1_B1    ((PADS_P1_ENABLE & BIT1) ? BIT1 : 0)
#define P1_B2    ((PADS_P1_ENABLE & BIT2) ? BIT2 : 0)
#define P1_B3    ((PADS_P1_ENABLE & BIT3) ? BIT3 : 0)
#define P1_B4    ((PADS_P1_ENABLE & BIT4) ? BIT4 : 0)
#define P1_B5    ((PADS_P1_ENABLE & BIT5) ? BIT5 : 0)
#define P1_B6    ((PADS_P1_ENABLE & BIT6) ? BIT6 : 0)
#define P1_B7    ((PADS_P1_ENABLE & BIT7) ? BIT7 : 0)

#define SET_P1 P1_B0|P1_B1|P1_B2|P1_B3|P1_B4|P1_B5|P1_B6|P1_B7
        _RVM3(0x1EB8, SET_P1, 0xFF),
#endif

    _MEMMAP_PM_,

    _RVM1(0x0E13, BIT3, BIT3),   // RX0_ENABLE
    _RVM1(0x0E13, 0 , BIT4),   // UART0 -> reg_uart_sel0

    _MEMMAP_nonPM_,

    // Clear all pad in
    _RVM1(0x1EA1, 0, BIT7),
    _END_OF_TBL_,

//---------------------------------------------------------------------
// ISP_TOOL Write Protect
//---------------------------------------------------------------------

#if _NUGGET_ENBEDED_FLASH_

    //embeded flash
    _MEMMAP_PM_,
    _RVM1(0x0E6A, 0x00, BIT0), //reg_spi_gpio set to 0 (swtch to spi_do, spi_di, spi_ck)
    _RVM1(0x0E6A, 0x00, BIT1), //reg_spicsz0_gpio set to 0 (enable spi_cz0)
    _RVM1(0x08F4, 0x00, 0xFF), //reg_chip_select set to 0 (select embedded SPI Flash)
    _END_OF_TBL_,

    //external flash #1
    _MEMMAP_PM_,
    _RVM1(0x0E6A, 0x00, BIT0), //reg_spi_gpio set to 0 (swtch to spi_do, spi_di, spi_ck)
    _RVM1(0x0E6A, 0x00, BIT2), //reg_spicsz1_gpio set to 0 (enable spi_cz1)
    _RVM1(0x08F4, 0x01, 0xFF), //reg_chip_select set to 1 (select external flash #1)
    #if (PIN_FLASH_WP0)
      #if ((MS_BOARD_TYPE_SEL == BD_MST180A_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_MST180B_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_MST050B_10ART_13225) || \
           (MS_BOARD_TYPE_SEL == BD_MST180C_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_MST180D_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_MST065B_10ART_13225) || \
           (MS_BOARD_TYPE_SEL == BD_MST180E_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_MST180F_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_NUGGET_LOADBOARD))
      _RVM1(0x0e20, BIT0, BIT0), //PM0
      _RVM1(0x0E1E,    0, BIT0),
      #elif (MS_BOARD_TYPE_SEL == BD_MST180A_D01A_S)
      _RVM1(0x1424, BIT2, BIT2), //SAR2
      _RVM1(0x1423,    0, BIT2),
      _RVM1(0x1422,    0, BIT2),
      #else
      #error Unknow board type
      #endif
    #endif
    _END_OF_TBL_,

    //external flash #2
    _MEMMAP_PM_,
    _RVM1(0x0E6A, 0x00, BIT0), //reg_spi_gpio set to 0 (swtch to spi_do, spi_di, spi_ck)
  #if (PIN_SPI_CZ1)
    _RVM1(0x0E6A, BIT3, BIT3), //reg_spicsz2_gpio set to 1 (disable spi_cz2 as gpio)  ===> ???
    _RVM1(0x08F4, 0x02, 0xFF), //reg_chip_select set to 2 (select external flash #2)
    #if (PIN_FLASH_WP1)
      #if ((MS_BOARD_TYPE_SEL == BD_MST180A_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_MST180B_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_MST050B_10ART_13225) || \
           (MS_BOARD_TYPE_SEL == BD_MST180C_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_MST180D_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_MST065B_10ART_13225) || \
           (MS_BOARD_TYPE_SEL == BD_MST180E_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_MST180F_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_NUGGET_LOADBOARD))
      _RVM1(0x0E21, BIT0, BIT0), //PM8
      _RVM1(0x0E1F,    0, BIT0),
      #elif (MS_BOARD_TYPE_SEL == BD_MST180A_D01A_S)
      _RVM1(0x0E21, BIT0, BIT0), //PM8
      _RVM1(0x0E1F,    0, BIT0),
      #else
      #error Unknow board type
      #endif
    #endif
    _END_OF_TBL_,
  #endif

#else
    //external flash #1
    _MEMMAP_PM_,
    _RVM1(0x0E6A, 0x00, BIT0), //reg_spi_gpio set to 0 (swtch to spi_do, spi_di, spi_ck)
    _RVM1(0x0E6A, 0x00, BIT1), //reg_spicsz0_gpio set to 0 (enable spi_cz0)
    _RVM1(0x08F4, 0x00, 0xFF), //reg_chip_select set to 0 (select externel SPI Flash #1)
    #if (PIN_FLASH_WP0)
      #if ((MS_BOARD_TYPE_SEL == BD_MST180A_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_MST180B_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_MST050B_10ART_13225) || \
           (MS_BOARD_TYPE_SEL == BD_MST180C_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_MST180D_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_MST065B_10ART_13225) || \
           (MS_BOARD_TYPE_SEL == BD_MST180E_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_MST180F_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_NUGGET_LOADBOARD))
      _RVM1(0x0E20, BIT0, BIT0), //PM3
      _RVM1(0x0E1E,    0, BIT0),
      #else
      #error Unknow board type
      #endif
    #endif
    _END_OF_TBL_,

    //external flash #2
    _MEMMAP_PM_,
    _RVM1(0x0E6A, 0x00, BIT0), //reg_spi_gpio set to 0 (swtch to spi_do, spi_di, spi_ck)
  #if (PIN_SPI_CZ1)
    _RVM1(0x0E6A, 0x00, BIT2), //reg_spicsz1_gpio set to 0 (enable spi_cz1)
    _RVM1(0x08F4, 0x01, 0xFF), //reg_chip_select set to 1 (select external flash #2)
    #if (PIN_FLASH_WP1)
      #if ((MS_BOARD_TYPE_SEL == BD_MST180A_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_MST180B_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_MST180D_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_MST180E_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_MST180F_D01A_S) || \
           (MS_BOARD_TYPE_SEL == BD_NUGGET_LOADBOARD))
      _RVM1(0x0E20, BIT7, BIT7), //PM7
      _RVM1(0x0E1E,    0, BIT7),
      #else
      #error Unknow board type
      #endif
    #endif
    _END_OF_TBL_,
  #endif

#endif

};

//-----------------------------------------------------------------
// Sanity check for PAD_TOP setting (TODO)
//-----------------------------------------------------------------

#if (UART0_SRC_SEL == UART1_SRC_SEL) || \
    (UART0_SRC_SEL == UART2_SRC_SEL) || \
    (UART1_SRC_SEL == UART2_SRC_SEL)
    #error "UART src selection conflict"
#endif


