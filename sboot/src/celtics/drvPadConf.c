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

#include <stdio.h>

#include "datatype.h"
#include "drvRIU.h"
#include "Board.h"
#include "c_riubase.h"
#include "hwreg_celtics.h"
#include "chip/bond.h"

#define GPIO_NONE               0       // Not GPIO pin (default)
#define GPIO_IN                 1       // GPI
#define GPIO_OUT_LOW            2       // GPO output low
#define GPIO_OUT_HIGH           3       // GPO output high

#if defined(ARM_CHAKRA) || defined (MIPS_CHAKRA) || defined(MSOS_TYPE_LINUX)
#define _MapBase_nonPM_CELTICS      (RIU_MAP + 0x200000)
#define _MapBase_PM_CELTICS         RIU_MAP
#else
#define _MapBase_nonPM_CELTICS      0xA0200000
#define _MapBase_PM_CELTICS         0xA0000000
#endif

#define _MEMMAP_nonPM_          _RVM1(0x0000, 0x10, 0xFF)
#define _MEMMAP_PM_             _RVM1(0x0000, 0x00, 0xFF)
#define _MEMMAP_nonPM_SPARE0_   _RVM1(0x0000, 0x12, 0xFF)

const U8 padInitTbl[] =
{
    0x39, 0xB6, 0x5B, 0x53,     // magic code for ISP_Tool

    // programable device number
    // spi flash count
#if 0
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
#define PAD_PM_SPI_CZ_OEN (PAD_PM_SPI_CZ_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_PM_SPI_CZ_OUT (PAD_PM_SPI_CZ_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f2e, PAD_PM_SPI_CZ_OUT, BIT1),
    _RVM1(0x0f2e, PAD_PM_SPI_CZ_OEN, BIT0),
    //reg_spicsz0_gpio
    _RVM1(0x0e6a, BIT1 , BIT1 ),   //reg[0e6a]#1 = 1
#endif

#if(PAD_PM_SPI_CK_IS_GPIO != GPIO_NONE)
#define PAD_PM_SPI_CK_OEN (PAD_PM_SPI_CK_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_PM_SPI_CK_OUT (PAD_PM_SPI_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f30, PAD_PM_SPI_CK_OUT, BIT1),
    _RVM1(0x0f30, PAD_PM_SPI_CK_OEN, BIT0),
    //reg_spi_gpio
    _RVM1(0x0e6a, BIT0 , BIT0 ),   //reg[0e6a]#0 = 1
#endif

#if(PAD_PM_SPI_DI_IS_GPIO != GPIO_NONE)
#define PAD_PM_SPI_DI_OEN (PAD_PM_SPI_DI_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_PM_SPI_DI_OUT (PAD_PM_SPI_DI_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f32, PAD_PM_SPI_DI_OUT, BIT1),
    _RVM1(0x0f32, PAD_PM_SPI_DI_OEN, BIT0),
    //reg_spi_gpio
    _RVM1(0x0e6a, BIT0 , BIT0 ),   //reg[0e6a]#0 = 1
#endif

#if(PAD_PM_SPI_DO_IS_GPIO != GPIO_NONE)
#define PAD_PM_SPI_DO_OEN (PAD_PM_SPI_DO_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_PM_SPI_DO_OUT (PAD_PM_SPI_DO_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f34, PAD_PM_SPI_DO_OUT, BIT1),
    _RVM1(0x0f34, PAD_PM_SPI_DO_OEN, BIT0),
    //reg_spi_gpio
    _RVM1(0x0e6a, BIT0 , BIT0 ),   //reg[0e6a]#0 = 1
#endif

#if(PAD_IRIN_IS_GPIO != GPIO_NONE)
#define PAD_IRIN_OEN (PAD_IRIN_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_IRIN_OUT (PAD_IRIN_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f26, PAD_IRIN_OUT, BIT1),
    _RVM1(0x0f26, PAD_IRIN_OEN, BIT0),
    //reg_ir_is_gpio
    _RVM1(0x0e38, BIT4 , BIT4 ),   //reg[0e38]#4 = 1
#endif

#if(PAD_CEC_IS_GPIO != GPIO_NONE)
#define PAD_CEC_OEN (PAD_CEC_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_CEC_OUT (PAD_CEC_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f2a, PAD_CEC_OUT, BIT1),
    _RVM1(0x0f2a, PAD_CEC_OEN, BIT0),
    //reg_cec_is_gpio
    _RVM1(0x0e38, BIT6 , BIT6 ),   //reg[0e38]#6 = 1
#endif

#if(PAD_AV_LNK_IS_GPIO != GPIO_NONE)
#define PAD_AV_LNK_OEN (PAD_AV_LNK_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_AV_LNK_OUT (PAD_AV_LNK_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f2c, PAD_AV_LNK_OUT, BIT1),
    _RVM1(0x0f2c, PAD_AV_LNK_OEN, BIT0),
    //reg_av_lnk_is_gpio
    _RVM1(0x0e38, BIT7 , BIT7 ),   //reg[0e38]#7 = 1
#endif

#if(PAD_PWM_PM_IS_GPIO != GPIO_NONE)
#define PAD_PWM_PM_OEN (PAD_PWM_PM_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_PWM_PM_OUT (PAD_PWM_PM_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f28, PAD_PWM_PM_OUT, BIT1),
    _RVM1(0x0f28, PAD_PWM_PM_OEN, BIT0),
    //reg_pwm_pm_is_gpio
    _RVM1(0x0e38, BIT5 , BIT5 ),   //reg[0e38]#5 = 1
#endif

#if(PAD_DDCA_CK_IS_GPIO != GPIO_NONE)
#define PAD_DDCA_CK_OEN (PAD_DDCA_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_DDCA_CK_OUT (PAD_DDCA_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x0494, PAD_DDCA_CK_OUT, BIT2),
    _RVM1(0x0494, PAD_DDCA_CK_OEN, BIT1),
    //reg_gpio2a0_en
    _RVM1(0x0494, BIT7 , BIT7 ),   //reg[0494]#7 = 1
#endif

#if(PAD_DDCA_DA_IS_GPIO != GPIO_NONE)
#define PAD_DDCA_DA_OEN (PAD_DDCA_DA_IS_GPIO == GPIO_IN ? BIT5: 0)
#define PAD_DDCA_DA_OUT (PAD_DDCA_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x0494, PAD_DDCA_DA_OUT, BIT6),
    _RVM1(0x0494, PAD_DDCA_DA_OEN, BIT5),
    //reg_gpio2a0_en
    _RVM1(0x0494, BIT7 , BIT7 ),   //reg[0494]#7 = 1
#endif

#if(PAD_GPIO_PM0_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM0_OEN (PAD_GPIO_PM0_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_GPIO_PM0_OUT (PAD_GPIO_PM0_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f00, PAD_GPIO_PM0_OUT, BIT1),
    _RVM1(0x0f00, PAD_GPIO_PM0_OEN, BIT0),
#endif

#if(PAD_GPIO_PM1_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM1_OEN (PAD_GPIO_PM1_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_GPIO_PM1_OUT (PAD_GPIO_PM1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f02, PAD_GPIO_PM1_OUT, BIT1),
    _RVM1(0x0f02, PAD_GPIO_PM1_OEN, BIT0),
    //reg_uart_is_gpio[1]
    _RVM1(0x0e6b, 0, BIT1 ),   //reg[0e6b]#1 = 0
    //reg_uart_is_gpio[3]
    _RVM1(0x0e6b, 0, BIT3 ),   //reg[0e6b]#3 = 0
#endif

#if(PAD_GPIO_PM2_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM2_OEN (PAD_GPIO_PM2_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_GPIO_PM2_OUT (PAD_GPIO_PM2_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f04, PAD_GPIO_PM2_OUT, BIT1),
    _RVM1(0x0f04, PAD_GPIO_PM2_OEN, BIT0),
#endif

#if(PAD_GPIO_PM3_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM3_OEN (PAD_GPIO_PM3_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_GPIO_PM3_OUT (PAD_GPIO_PM3_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f06, PAD_GPIO_PM3_OUT, BIT1),
    _RVM1(0x0f06, PAD_GPIO_PM3_OEN, BIT0),
#endif

#if(PAD_GPIO_PM4_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM4_OEN (PAD_GPIO_PM4_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_GPIO_PM4_OUT (PAD_GPIO_PM4_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f08, PAD_GPIO_PM4_OUT, BIT1),
    _RVM1(0x0f08, PAD_GPIO_PM4_OEN, BIT0),
    //reg_gpio_pm_lock
    _RVM1(0x0e24, 0xbe, 0xFFFF),   //reg[0e24]#7 ~ #0 = 10111110b
    _RVM1(0x0e25, 0xba, 0xFFFF),   //reg[0e25]#7 ~ #0 = 10111010b
#endif

#if(PAD_GPIO_PM5_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM5_OEN (PAD_GPIO_PM5_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_GPIO_PM5_OUT (PAD_GPIO_PM5_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f0a, PAD_GPIO_PM5_OUT, BIT1),
    _RVM1(0x0f0a, PAD_GPIO_PM5_OEN, BIT0),
#endif

#if(PAD_GPIO_PM6_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM6_OEN (PAD_GPIO_PM6_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_GPIO_PM6_OUT (PAD_GPIO_PM6_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f0c, PAD_GPIO_PM6_OUT, BIT1),
    _RVM1(0x0f0c, PAD_GPIO_PM6_OEN, BIT0),
    //reg_spicsz1_gpio
    _RVM1(0x0e6a, BIT2 , BIT2 ),   //reg[0e6a]#2 = 1
#endif

#if(PAD_GPIO_PM7_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM7_OEN (PAD_GPIO_PM7_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_GPIO_PM7_OUT (PAD_GPIO_PM7_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f0e, PAD_GPIO_PM7_OUT, BIT1),
    _RVM1(0x0f0e, PAD_GPIO_PM7_OEN, BIT0),
#endif

#if(PAD_GPIO_PM8_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM8_OEN (PAD_GPIO_PM8_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_GPIO_PM8_OUT (PAD_GPIO_PM8_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f10, PAD_GPIO_PM8_OUT, BIT1),
    _RVM1(0x0f10, PAD_GPIO_PM8_OEN, BIT0),
    //reg_uart_is_gpio[0]
    _RVM1(0x0e6b, 0, BIT0 ),   //reg[0e6b]#0 = 0
#endif

#if(PAD_GPIO_PM9_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM9_OEN (PAD_GPIO_PM9_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_GPIO_PM9_OUT (PAD_GPIO_PM9_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f12, PAD_GPIO_PM9_OUT, BIT1),
    _RVM1(0x0f12, PAD_GPIO_PM9_OEN, BIT0),
#endif

#if(PAD_GPIO_PM10_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM10_OEN (PAD_GPIO_PM10_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_GPIO_PM10_OUT (PAD_GPIO_PM10_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f14, PAD_GPIO_PM10_OUT, BIT1),
    _RVM1(0x0f14, PAD_GPIO_PM10_OEN, BIT0),
    //reg_spicsz2_gpio
    _RVM1(0x0e6a, 0, BIT3 ),   //reg[0e6a]#3 = 0
#endif

#if(PAD_GPIO_PM11_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM11_OEN (PAD_GPIO_PM11_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_GPIO_PM11_OUT (PAD_GPIO_PM11_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f16, PAD_GPIO_PM11_OUT, BIT1),
    _RVM1(0x0f16, PAD_GPIO_PM11_OEN, BIT0),
#endif

#if(PAD_GPIO_PM12_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM12_OEN (PAD_GPIO_PM12_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_GPIO_PM12_OUT (PAD_GPIO_PM12_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f18, PAD_GPIO_PM12_OUT, BIT1),
    _RVM1(0x0f18, PAD_GPIO_PM12_OEN, BIT0),
    //reg_uart_is_gpio_1[0]
    _RVM1(0x0e6b, 0, BIT6 ),   //reg[0e6b]#6 = 0
    //reg_uart_is_gpio_1[1]
    _RVM1(0x0e6b, 0, BIT7 ),   //reg[0e6b]#7 = 0
#endif

#if(PAD_GPIO_PM13_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM13_OEN (PAD_GPIO_PM13_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_GPIO_PM13_OUT (PAD_GPIO_PM13_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f1a, PAD_GPIO_PM13_OUT, BIT1),
    _RVM1(0x0f1a, PAD_GPIO_PM13_OEN, BIT0),
#endif

#if(PAD_GPIO_PM14_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM14_OEN (PAD_GPIO_PM14_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_GPIO_PM14_OUT (PAD_GPIO_PM14_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f1c, PAD_GPIO_PM14_OUT, BIT1),
    _RVM1(0x0f1c, PAD_GPIO_PM14_OEN, BIT0),
    //reg_mhl_cable_detect_sel
    _RVM1(0x0ee4, 0, BIT6 ),   //reg[0ee4]#6 = 0
#endif

#if(PAD_GPIO_PM15_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM15_OEN (PAD_GPIO_PM15_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_GPIO_PM15_OUT (PAD_GPIO_PM15_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f1e, PAD_GPIO_PM15_OUT, BIT1),
    _RVM1(0x0f1e, PAD_GPIO_PM15_OEN, BIT0),
    //reg_vbus_en_sel
    _RVM1(0x0ee4, 0, BIT7 ),   //reg[0ee4]#7 = 0
#endif

#if(PAD_GPIO_PM16_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM16_OEN (PAD_GPIO_PM16_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_GPIO_PM16_OUT (PAD_GPIO_PM16_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f20, PAD_GPIO_PM16_OUT, BIT1),
    _RVM1(0x0f20, PAD_GPIO_PM16_OEN, BIT0),
    //reg_cbus_debug_sel
    _RVM1(0x0ee5, 0, BIT0 ),   //reg[0ee5]#0 = 0
#endif

#if(PAD_GPIO_PM17_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM17_OEN (PAD_GPIO_PM17_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_GPIO_PM17_OUT (PAD_GPIO_PM17_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f22, PAD_GPIO_PM17_OUT, BIT1),
    _RVM1(0x0f22, PAD_GPIO_PM17_OEN, BIT0),
    //reg_hdmitx_cec_en
    _RVM1(0x0ee4, 0, BIT0 ),   //reg[0ee4]#0 = 0
#endif

#if(PAD_GPIO_PM18_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM18_OEN (PAD_GPIO_PM18_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_GPIO_PM18_OUT (PAD_GPIO_PM18_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f24, PAD_GPIO_PM18_OUT, BIT1),
    _RVM1(0x0f24, PAD_GPIO_PM18_OEN, BIT0),
    //reg_hdmitx_hotplug_en
    _RVM1(0x0ee4, 0, BIT1 ),   //reg[0ee4]#1 = 0
#endif

#if(PAD_LED0_IS_GPIO != GPIO_NONE)
#define PAD_LED0_OEN (PAD_LED0_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_LED0_OUT (PAD_LED0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2e80, PAD_LED0_OUT, BIT0),
    _RVM1(0x2e80, PAD_LED0_OEN, BIT1),
    //reg_wol_is_gpio
    _RVM1(0x0e39, 0, BIT1 ),   //reg[0e39]#1 = 0
#endif

#if(PAD_LED1_IS_GPIO != GPIO_NONE)
#define PAD_LED1_OEN (PAD_LED1_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_LED1_OUT (PAD_LED1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2e81, PAD_LED1_OUT, BIT0),
    _RVM1(0x2e81, PAD_LED1_OEN, BIT1),
    //reg_wol_is_gpio
    _RVM1(0x0e39, 0, BIT1 ),   //reg[0e39]#1 = 0
#endif

#if(PAD_HOTPLUGA_IS_GPIO != GPIO_NONE)
#define PAD_HOTPLUGA_OEN (PAD_HOTPLUGA_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_HOTPLUGA_OUT (PAD_HOTPLUGA_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x0e4e, PAD_HOTPLUGA_OUT, BIT4),
    _RVM1(0x0e4e, PAD_HOTPLUGA_OEN, BIT0),
    //reg_hpluga_mhl_en
    _RVM1(0x0ee7, 0, BIT0 ),   //reg[0ee7]#0 = 0
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
    _RVM1(0x0ee6, 0, BIT0 ),   //reg[0ee6]#0 = 0
#endif

#if(PAD_HOTPLUGD_IS_GPIO != GPIO_NONE)
#define PAD_HOTPLUGD_OEN (PAD_HOTPLUGD_IS_GPIO == GPIO_IN ? BIT3: 0)
#define PAD_HOTPLUGD_OUT (PAD_HOTPLUGD_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x0e4e, PAD_HOTPLUGD_OUT, BIT7),
    _RVM1(0x0e4e, PAD_HOTPLUGD_OEN, BIT3),
    //reg_wol_is_gpio
    _RVM1(0x0e39, 0, BIT1 ),   //reg[0e39]#1 = 0
    //reg_vid_is_gpio
    _RVM1(0x0e39, 0, BIT2 ),   //reg[0e39]#2 = 0
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

#if(PAD_VID0_IS_GPIO != GPIO_NONE)
#define PAD_VID0_OEN (PAD_VID0_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_VID0_OUT (PAD_VID0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2e84, PAD_VID0_OUT, BIT0),
    _RVM1(0x2e84, PAD_VID0_OEN, BIT1),
    //reg_vid_is_gpio
    _RVM1(0x0e39, BIT2 , BIT2 ),   //reg[0e39]#2 = 1
#endif

#if(PAD_VID1_IS_GPIO != GPIO_NONE)
#define PAD_VID1_OEN (PAD_VID1_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_VID1_OUT (PAD_VID1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2e85, PAD_VID1_OUT, BIT0),
    _RVM1(0x2e85, PAD_VID1_OEN, BIT1),
    //reg_vid_is_gpio
    _RVM1(0x0e39, BIT2 , BIT2 ),   //reg[0e39]#2 = 1
#endif

#if(PAD_WOL_INT_IS_GPIO != GPIO_NONE)
#define PAD_WOL_INT_OEN (PAD_WOL_INT_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_WOL_INT_OUT (PAD_WOL_INT_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2e82, PAD_WOL_INT_OUT, BIT0),
    _RVM1(0x2e82, PAD_WOL_INT_OEN, BIT1),
    //reg_wol_is_gpio
    _RVM1(0x0e39, 0, BIT1 ),   //reg[0e39]#1 = 0
#endif

_MEMMAP_nonPM_,

#if(PAD_DDCR_DA_IS_GPIO != GPIO_NONE)
#define PAD_DDCR_DA_OEN (PAD_DDCR_DA_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_DDCR_DA_OUT (PAD_DDCR_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b86, PAD_DDCR_DA_OUT, BIT0),
    _RVM1(0x2b86, PAD_DDCR_DA_OEN, BIT1),
    //reg_test_out_mode[2:0]
    // _RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_ddcrmode[1:0]
    _RVM1(0x1eae, 0, BIT1 | BIT0 ),   //reg[101eae]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_DDCR_CK_IS_GPIO != GPIO_NONE)
#define PAD_DDCR_CK_OEN (PAD_DDCR_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_DDCR_CK_OUT (PAD_DDCR_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b87, PAD_DDCR_CK_OUT, BIT0),
    _RVM1(0x2b87, PAD_DDCR_CK_OEN, BIT1),
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_ddcrmode[1:0]
    _RVM1(0x1eae, 0, BIT1 | BIT0 ),   //reg[101eae]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO0_IS_GPIO != GPIO_NONE)
#define PAD_GPIO0_OEN (PAD_GPIO0_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO0_OUT (PAD_GPIO0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b00, PAD_GPIO0_OUT, BIT0),
    _RVM1(0x2b00, PAD_GPIO0_OEN, BIT1),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5 | BIT4 ),   //reg[101e05]#5 ~ #4 = 0b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcm_config
    _RVM1(0x1ef6, 0, BIT1 ),   //reg[101ef6]#1 = 0b
    //reg_p1_enable_b0
    _RVM1(0x1ea4, 0, BIT0 ),   //reg[101ea4]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO1_IS_GPIO != GPIO_NONE)
#define PAD_GPIO1_OEN (PAD_GPIO1_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO1_OUT (PAD_GPIO1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b01, PAD_GPIO1_OUT, BIT0),
    _RVM1(0x2b01, PAD_GPIO1_OEN, BIT1),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5 | BIT4 ),   //reg[101e05]#5 ~ #4 = 0b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcm_config
    _RVM1(0x1ef6, 0, BIT1 ),   //reg[101ef6]#1 = 0b
    //reg_p1_enable_b1
    _RVM1(0x1ea4, 0, BIT1 ),   //reg[101ea4]#1 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO2_IS_GPIO != GPIO_NONE)
#define PAD_GPIO2_OEN (PAD_GPIO2_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO2_OUT (PAD_GPIO2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b02, PAD_GPIO2_OUT, BIT0),
    _RVM1(0x2b02, PAD_GPIO2_OEN, BIT1),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5 | BIT4 ),   //reg[101e05]#5 ~ #4 = 0b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcm_config
    _RVM1(0x1ef6, 0, BIT1 ),   //reg[101ef6]#1 = 0b
    //reg_p1_enable_b2
    _RVM1(0x1ea4, 0, BIT2 ),   //reg[101ea4]#2 = 0b
    //reg_usb30vctl_config[1:0]
    _RVM1(0x1e08, 0, BIT5 | BIT4 ),   //reg[101e08]#5 ~ #4 = 0b
    //reg_osd3dflag_config[1:0]
    _RVM1(0x1ef6, 0, BIT7 | BIT6 ),   //reg[101ef6]#7 ~ #6 = 0b
    //reg_3dflagconfig[1:0]
    _RVM1(0x1eb3, 0, BIT7 | BIT6 ),   //reg[101eb3]#7 ~ #6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO3_IS_GPIO != GPIO_NONE)
#define PAD_GPIO3_OEN (PAD_GPIO3_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO3_OUT (PAD_GPIO3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b03, PAD_GPIO3_OUT, BIT0),
    _RVM1(0x2b03, PAD_GPIO3_OEN, BIT1),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5 | BIT4 ),   //reg[101e05]#5 ~ #4 = 0b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_seconduartmode[1:0]
    _RVM1(0x1e05, 0, BIT1 | BIT0 ),   //reg[101e05]#1 ~ #0 = 0b
    //reg_od2nduart[1:0]
    _RVM1(0x1ea9, 0, BIT1 | BIT0 ),   //reg[101ea9]#1 ~ #0 = 0b
    //reg_p1_enable_b3
    _RVM1(0x1ea4, 0, BIT3 ),   //reg[101ea4]#3 = 0b
    //reg_usb30vctl_config[1:0]
    _RVM1(0x1e08, 0, BIT5 | BIT4 ),   //reg[101e08]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO4_IS_GPIO != GPIO_NONE)
#define PAD_GPIO4_OEN (PAD_GPIO4_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO4_OUT (PAD_GPIO4_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b04, PAD_GPIO4_OUT, BIT0),
    _RVM1(0x2b04, PAD_GPIO4_OEN, BIT1),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5 | BIT4 ),   //reg[101e05]#5 ~ #4 = 0b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_seconduartmode[1:0]
    _RVM1(0x1e05, 0, BIT1 | BIT0 ),   //reg[101e05]#1 ~ #0 = 0b
    //reg_od2nduart[1:0]
    _RVM1(0x1ea9, 0, BIT1 | BIT0 ),   //reg[101ea9]#1 ~ #0 = 0b
    //reg_p1_enable[4]
    _RVM1(0x1ea4, 0, BIT4 ),   //reg[101ea4]#4 = 0b
    //reg_usb30vctl_config[1:0]
    _RVM1(0x1e08, 0, BIT5 | BIT4 ),   //reg[101e08]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO5_IS_GPIO != GPIO_NONE)
#define PAD_GPIO5_OEN (PAD_GPIO5_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO5_OUT (PAD_GPIO5_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b05, PAD_GPIO5_OUT, BIT0),
    _RVM1(0x2b05, PAD_GPIO5_OEN, BIT1),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5 | BIT4 ),   //reg[101e05]#5 ~ #4 = 0b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_fastuartmode[1:0]
    _RVM1(0x1e04, 0, BIT5 | BIT4 ),   //reg[101e04]#5 ~ #4 = 0b
    //reg_odfuart[1:0]
    _RVM1(0x1ea9, 0, BIT7 | BIT6 ),   //reg[101ea9]#7 ~ #6 = 0b
    //reg_p1_enable[5]
    _RVM1(0x1ea4, 0, BIT5 ),   //reg[101ea4]#5 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO6_IS_GPIO != GPIO_NONE)
#define PAD_GPIO6_OEN (PAD_GPIO6_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO6_OUT (PAD_GPIO6_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b06, PAD_GPIO6_OUT, BIT0),
    _RVM1(0x2b06, PAD_GPIO6_OEN, BIT1),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5 | BIT4 ),   //reg[101e05]#5 ~ #4 = 0b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_fastuartmode[1:0]
    _RVM1(0x1e04, 0, BIT5 | BIT4 ),   //reg[101e04]#5 ~ #4 = 0b
    //reg_odfuart[1:0]
    _RVM1(0x1ea9, 0, BIT7 | BIT6 ),   //reg[101ea9]#7 ~ #6 = 0b
    //reg_p1_enable[6]
    _RVM1(0x1ea4, 0, BIT6 ),   //reg[101ea4]#6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO7_IS_GPIO != GPIO_NONE)
#define PAD_GPIO7_OEN (PAD_GPIO7_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO7_OUT (PAD_GPIO7_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b07, PAD_GPIO7_OUT, BIT0),
    _RVM1(0x2b07, PAD_GPIO7_OEN, BIT1),
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_seconduartmode[1:0]
    _RVM1(0x1e05, 0, BIT1 | BIT0 ),   //reg[101e05]#1 ~ #0 = 0b
    //reg_od2nduart[1:0]
    _RVM1(0x1ea9, 0, BIT1 | BIT0 ),   //reg[101ea9]#1 ~ #0 = 0b
    //reg_p1_enable[7]
    _RVM1(0x1ea4, 0, BIT7 ),   //reg[101ea4]#7 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO8_IS_GPIO != GPIO_NONE)
#define PAD_GPIO8_OEN (PAD_GPIO8_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO8_OUT (PAD_GPIO8_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b08, PAD_GPIO8_OUT, BIT0),
    _RVM1(0x2b08, PAD_GPIO8_OEN, BIT1),
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_seconduartmode[1:0]
    _RVM1(0x1e05, 0, BIT1 | BIT0 ),   //reg[101e05]#1 ~ #0 = 0b
    //reg_fifthuartmode[1:0]
    _RVM1(0x1e08, 0, BIT3 | BIT2 ),   //reg[101e08]#3 ~ #2 = 0b
    //reg_od2nduart[1:0]
    _RVM1(0x1ea9, 0, BIT1 | BIT0 ),   //reg[101ea9]#1 ~ #0 = 0b
    //reg_od5thuart[1:0]
    _RVM1(0x1eaa, 0, BIT5 | BIT4 ),   //reg[101eaa]#5 ~ #4 = 0b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1 | BIT0 ),   //reg[101e9f]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO9_IS_GPIO != GPIO_NONE)
#define PAD_GPIO9_OEN (PAD_GPIO9_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO9_OUT (PAD_GPIO9_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b09, PAD_GPIO9_OUT, BIT0),
    _RVM1(0x2b09, PAD_GPIO9_OEN, BIT1),
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_thirduartmode[1:0]
    _RVM1(0x1e05, 0, BIT3 | BIT2 ),   //reg[101e05]#3 ~ #2 = 0b
    //reg_fifthuartmode[1:0]
    _RVM1(0x1e08, 0, BIT3 | BIT2 ),   //reg[101e08]#3 ~ #2 = 0b
    //reg_od3rduart[1:0]
    _RVM1(0x1ea9, 0, BIT3 | BIT2 ),   //reg[101ea9]#3 ~ #2 = 0b
    //reg_od5thuart[1:0]
    _RVM1(0x1eaa, 0, BIT5 | BIT4 ),   //reg[101eaa]#5 ~ #4 = 0b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1 | BIT0 ),   //reg[101e9f]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO10_IS_GPIO != GPIO_NONE)
#define PAD_GPIO10_OEN (PAD_GPIO10_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO10_OUT (PAD_GPIO10_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b0a, PAD_GPIO10_OUT, BIT0),
    _RVM1(0x2b0a, PAD_GPIO10_OEN, BIT1),
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_thirduartmode[1:0]
    _RVM1(0x1e05, 0, BIT3 | BIT2 ),   //reg[101e05]#3 ~ #2 = 0b
    //reg_od3rduart[1:0]
    _RVM1(0x1ea9, 0, BIT3 | BIT2 ),   //reg[101ea9]#3 ~ #2 = 0b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1 | BIT0 ),   //reg[101e9f]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO11_IS_GPIO != GPIO_NONE)
#define PAD_GPIO11_OEN (PAD_GPIO11_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO11_OUT (PAD_GPIO11_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b0b, PAD_GPIO11_OUT, BIT0),
    _RVM1(0x2b0b, PAD_GPIO11_OEN, BIT1),
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_fourthuartmode[1:0]
    _RVM1(0x1e04, 0, BIT7 | BIT6 ),   //reg[101e04]#7 ~ #6 = 0b
    //reg_od4thuart[1:0]
    _RVM1(0x1ea9, 0, BIT5 | BIT4 ),   //reg[101ea9]#5 ~ #4 = 0b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1 | BIT0 ),   //reg[101e9f]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO12_IS_GPIO != GPIO_NONE)
#define PAD_GPIO12_OEN (PAD_GPIO12_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO12_OUT (PAD_GPIO12_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b0c, PAD_GPIO12_OUT, BIT0),
    _RVM1(0x2b0c, PAD_GPIO12_OEN, BIT1),
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_fourthuartmode[1:0]
    _RVM1(0x1e04, 0, BIT7 | BIT6 ),   //reg[101e04]#7 ~ #6 = 0b
    //reg_od4thuart[1:0]
    _RVM1(0x1ea9, 0, BIT5 | BIT4 ),   //reg[101ea9]#5 ~ #4 = 0b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1 | BIT0 ),   //reg[101e9f]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO13_IS_GPIO != GPIO_NONE)
#define PAD_GPIO13_OEN (PAD_GPIO13_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO13_OUT (PAD_GPIO13_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b0d, PAD_GPIO13_OUT, BIT0),
    _RVM1(0x2b0d, PAD_GPIO13_OEN, BIT1),
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_fastuartmode[1:0]
    _RVM1(0x1e04, 0, BIT5 | BIT4 ),   //reg[101e04]#5 ~ #4 = 0b
    //reg_odfuart[1:0]
    _RVM1(0x1ea9, 0, BIT7 | BIT6 ),   //reg[101ea9]#7 ~ #6 = 0b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1 | BIT0 ),   //reg[101e9f]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO14_IS_GPIO != GPIO_NONE)
#define PAD_GPIO14_OEN (PAD_GPIO14_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO14_OUT (PAD_GPIO14_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b0e, PAD_GPIO14_OUT, BIT0),
    _RVM1(0x2b0e, PAD_GPIO14_OEN, BIT1),
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_fastuartmode[1:0]
    _RVM1(0x1e04, 0, BIT5 | BIT4 ),   //reg[101e04]#5 ~ #4 = 0b
    //reg_odfuart[1:0]
    _RVM1(0x1ea9, 0, BIT7 | BIT6 ),   //reg[101ea9]#7 ~ #6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO15_IS_GPIO != GPIO_NONE)
#define PAD_GPIO15_OEN (PAD_GPIO15_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO15_OUT (PAD_GPIO15_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b0f, PAD_GPIO15_OUT, BIT0),
    _RVM1(0x2b0f, PAD_GPIO15_OEN, BIT1),
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_i2smutemode[1:0]
    _RVM1(0x1e05, 0, BIT7 | BIT6 ),   //reg[101e05]#7 ~ #6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO16_IS_GPIO != GPIO_NONE)
#define PAD_GPIO16_OEN (PAD_GPIO16_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO16_OUT (PAD_GPIO16_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b10, PAD_GPIO16_OUT, BIT0),
    _RVM1(0x2b10, PAD_GPIO16_OEN, BIT1),
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_fifthuartmode[1:0]
    _RVM1(0x1e08, 0, BIT3 | BIT2 ),   //reg[101e08]#3 ~ #2 = 0b
    //reg_od5thuart[1:0]
    _RVM1(0x1eaa, 0, BIT5 | BIT4 ),   //reg[101eaa]#5 ~ #4 = 0b
    //reg_tserrout[1:0]
    _RVM1(0x1ec9, 0, BIT1 | BIT0 ),   //reg[101ec9]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO17_IS_GPIO != GPIO_NONE)
#define PAD_GPIO17_OEN (PAD_GPIO17_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO17_OUT (PAD_GPIO17_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b11, PAD_GPIO17_OUT, BIT0),
    _RVM1(0x2b11, PAD_GPIO17_OEN, BIT1),
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_tso_evd_mode
    _RVM1(0x1e21, 0, BIT1 ),   //reg[101e21]#1 = 0b
    //reg_fifthuartmode[1:0]
    _RVM1(0x1e08, 0, BIT3 | BIT2 ),   //reg[101e08]#3 ~ #2 = 0b
    //reg_od5thuart[1:0]
    _RVM1(0x1eaa, 0, BIT5 | BIT4 ),   //reg[101eaa]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO18_IS_GPIO != GPIO_NONE)
#define PAD_GPIO18_OEN (PAD_GPIO18_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO18_OUT (PAD_GPIO18_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b12, PAD_GPIO18_OUT, BIT0),
    _RVM1(0x2b12, PAD_GPIO18_OEN, BIT1),
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_tso_evd_mode
    _RVM1(0x1e21, 0, BIT1 ),   //reg[101e21]#1 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO19_IS_GPIO != GPIO_NONE)
#define PAD_GPIO19_OEN (PAD_GPIO19_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO19_OUT (PAD_GPIO19_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b13, PAD_GPIO19_OUT, BIT0),
    _RVM1(0x2b13, PAD_GPIO19_OEN, BIT1),
    //reg_agc_dbg
    _RVM1(0x1e9e, 0, BIT7 ),   //reg[101e9e]#7 = 0b
    //reg_tso_evd_mode
    _RVM1(0x1e21, 0, BIT1 ),   //reg[101e21]#1 = 0b
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0 ),   //reg[101edf]#0 = 0b
    //reg_led_mode
    _RVM1(0x1eb4, 0, BIT4 ),   //reg[101eb4]#4 = 0b
    //reg_seconduartmode[1:0]
    _RVM1(0x1e05, 0, BIT1 | BIT0 ),   //reg[101e05]#1 ~ #0 = 0b
    //reg_od2nduart[1:0]
    _RVM1(0x1ea9, 0, BIT1 | BIT0 ),   //reg[101ea9]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO20_IS_GPIO != GPIO_NONE)
#define PAD_GPIO20_OEN (PAD_GPIO20_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO20_OUT (PAD_GPIO20_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b14, PAD_GPIO20_OUT, BIT0),
    _RVM1(0x2b14, PAD_GPIO20_OEN, BIT1),
    //reg_agc_dbg
    _RVM1(0x1e9e, 0, BIT7 ),   //reg[101e9e]#7 = 0b
    //reg_tso_evd_mode
    _RVM1(0x1e21, 0, BIT1 ),   //reg[101e21]#1 = 0b
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0 ),   //reg[101edf]#0 = 0b
    //reg_led_mode
    _RVM1(0x1eb4, 0, BIT4 ),   //reg[101eb4]#4 = 0b
    //reg_seconduartmode[1:0]
    _RVM1(0x1e05, 0, BIT1 | BIT0 ),   //reg[101e05]#1 ~ #0 = 0b
    //reg_od2nduart[1:0]
    _RVM1(0x1ea9, 0, BIT1 | BIT0 ),   //reg[101ea9]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO21_IS_GPIO != GPIO_NONE)
#define PAD_GPIO21_OEN (PAD_GPIO21_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO21_OUT (PAD_GPIO21_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b15, PAD_GPIO21_OUT, BIT0),
    _RVM1(0x2b15, PAD_GPIO21_OEN, BIT1),
    //reg_tso_evd_mode
    _RVM1(0x1e21, 0, BIT1 ),   //reg[101e21]#1 = 0b
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0 ),   //reg[101edf]#0 = 0b
    //reg_thirduartmode[1:0]
    _RVM1(0x1e05, 0, BIT3 | BIT2 ),   //reg[101e05]#3 ~ #2 = 0b
    //reg_od3rduart[1:0]
    _RVM1(0x1ea9, 0, BIT3 | BIT2 ),   //reg[101ea9]#3 ~ #2 = 0b
    //reg_ext_int[5]
    _RVM1(0x1ea5, 0, BIT5 ),   //reg[101ea5]#5 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO22_IS_GPIO != GPIO_NONE)
#define PAD_GPIO22_OEN (PAD_GPIO22_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO22_OUT (PAD_GPIO22_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b16, PAD_GPIO22_OUT, BIT0),
    _RVM1(0x2b16, PAD_GPIO22_OEN, BIT1),
    //reg_tso_evd_mode
    _RVM1(0x1e21, 0, BIT1 ),   //reg[101e21]#1 = 0b
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0 ),   //reg[101edf]#0 = 0b
    //reg_thirduartmode[1:0]
    _RVM1(0x1e05, 0, BIT3 | BIT2 ),   //reg[101e05]#3 ~ #2 = 0b
    //reg_od3rduart[1:0]
    _RVM1(0x1ea9, 0, BIT3 | BIT2 ),   //reg[101ea9]#3 ~ #2 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO23_IS_GPIO != GPIO_NONE)
#define PAD_GPIO23_OEN (PAD_GPIO23_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO23_OUT (PAD_GPIO23_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b17, PAD_GPIO23_OUT, BIT0),
    _RVM1(0x2b17, PAD_GPIO23_OEN, BIT1),
    //reg_tso_evd_mode
    _RVM1(0x1e21, 0, BIT1 ),   //reg[101e21]#1 = 0b
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0 ),   //reg[101edf]#0 = 0b
    //reg_fourthuartmode[1:0]
    _RVM1(0x1e04, 0, BIT7 | BIT6 ),   //reg[101e04]#7 ~ #6 = 0b
    //reg_od4thuart[1:0]
    _RVM1(0x1ea9, 0, BIT5 | BIT4 ),   //reg[101ea9]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO24_IS_GPIO != GPIO_NONE)
#define PAD_GPIO24_OEN (PAD_GPIO24_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO24_OUT (PAD_GPIO24_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b18, PAD_GPIO24_OUT, BIT0),
    _RVM1(0x2b18, PAD_GPIO24_OEN, BIT1),
    //reg_tso_evd_mode
    _RVM1(0x1e21, 0, BIT1 ),   //reg[101e21]#1 = 0b
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0 ),   //reg[101edf]#0 = 0b
    //reg_fourthuartmode[1:0]
    _RVM1(0x1e04, 0, BIT7 | BIT6 ),   //reg[101e04]#7 ~ #6 = 0b
    //reg_od4thuart[1:0]
    _RVM1(0x1ea9, 0, BIT5 | BIT4 ),   //reg[101ea9]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO25_IS_GPIO != GPIO_NONE)
#define PAD_GPIO25_OEN (PAD_GPIO25_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO25_OUT (PAD_GPIO25_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b19, PAD_GPIO25_OUT, BIT0),
    _RVM1(0x2b19, PAD_GPIO25_OEN, BIT1),
    //reg_tso_evd_mode
    _RVM1(0x1e21, 0, BIT1 ),   //reg[101e21]#1 = 0b
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0 ),   //reg[101edf]#0 = 0b
    //reg_fastuartmode[1:0]
    _RVM1(0x1e04, 0, BIT5 | BIT4 ),   //reg[101e04]#5 ~ #4 = 0b
    //reg_odfuart[1:0]
    _RVM1(0x1ea9, 0, BIT7 | BIT6 ),   //reg[101ea9]#7 ~ #6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO26_IS_GPIO != GPIO_NONE)
#define PAD_GPIO26_OEN (PAD_GPIO26_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO26_OUT (PAD_GPIO26_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b1a, PAD_GPIO26_OUT, BIT0),
    _RVM1(0x2b1a, PAD_GPIO26_OEN, BIT1),
    //reg_tso_evd_mode
    _RVM1(0x1e21, 0, BIT1 ),   //reg[101e21]#1 = 0b
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0 ),   //reg[101edf]#0 = 0b
    //reg_fastuartmode[1:0]
    _RVM1(0x1e04, 0, BIT5 | BIT4 ),   //reg[101e04]#5 ~ #4 = 0b
    //reg_odfuart[1:0]
    _RVM1(0x1ea9, 0, BIT7 | BIT6 ),   //reg[101ea9]#7 ~ #6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO27_IS_GPIO != GPIO_NONE)
#define PAD_GPIO27_OEN (PAD_GPIO27_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO27_OUT (PAD_GPIO27_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b1b, PAD_GPIO27_OUT, BIT0),
    _RVM1(0x2b1b, PAD_GPIO27_OEN, BIT1),
    //reg_tso_evd_mode
    _RVM1(0x1e21, 0, BIT1 ),   //reg[101e21]#1 = 0b
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0 ),   //reg[101edf]#0 = 0b
    //reg_ext_int[4]
    _RVM1(0x1ea5, 0, BIT4 ),   //reg[101ea5]#4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO28_IS_GPIO != GPIO_NONE)
#define PAD_GPIO28_OEN (PAD_GPIO28_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO28_OUT (PAD_GPIO28_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2ba0, PAD_GPIO28_OUT, BIT0),
    _RVM1(0x2ba0, PAD_GPIO28_OEN, BIT1),
    //reg_miic_mode0
    _RVM1(0x1edc, 0, BIT0 ),   //reg[101edc]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO29_IS_GPIO != GPIO_NONE)
#define PAD_GPIO29_OEN (PAD_GPIO29_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO29_OUT (PAD_GPIO29_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2ba1, PAD_GPIO29_OUT, BIT0),
    _RVM1(0x2ba1, PAD_GPIO29_OEN, BIT1),
    //reg_miic_mode0
    _RVM1(0x1edc, 0, BIT0 ),   //reg[101edc]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO30_IS_GPIO != GPIO_NONE)
#define PAD_GPIO30_OEN (PAD_GPIO30_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO30_OUT (PAD_GPIO30_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2ba2, PAD_GPIO30_OUT, BIT0),
    _RVM1(0x2ba2, PAD_GPIO30_OEN, BIT1),
    //reg_miic_mode4
    _RVM1(0x1ede, 0, BIT0 ),   //reg[101ede]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO31_IS_GPIO != GPIO_NONE)
#define PAD_GPIO31_OEN (PAD_GPIO31_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO31_OUT (PAD_GPIO31_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2ba3, PAD_GPIO31_OUT, BIT0),
    _RVM1(0x2ba3, PAD_GPIO31_OEN, BIT1),
    //reg_miic_mode4
    _RVM1(0x1ede, 0, BIT0 ),   //reg[101ede]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO32_IS_GPIO != GPIO_NONE)
#define PAD_GPIO32_OEN (PAD_GPIO32_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO32_OUT (PAD_GPIO32_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2ba4, PAD_GPIO32_OUT, BIT0),
    _RVM1(0x2ba4, PAD_GPIO32_OEN, BIT1),
    //reg_miic_mode5
    _RVM1(0x1ede, 0, BIT1 ),   //reg[101ede]#1 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO33_IS_GPIO != GPIO_NONE)
#define PAD_GPIO33_OEN (PAD_GPIO33_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO33_OUT (PAD_GPIO33_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2ba5, PAD_GPIO33_OUT, BIT0),
    _RVM1(0x2ba5, PAD_GPIO33_OEN, BIT1),
    //reg_miic_mode5
    _RVM1(0x1ede, 0, BIT1 ),   //reg[101ede]#1 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO34_IS_GPIO != GPIO_NONE)
#define PAD_GPIO34_OEN (PAD_GPIO34_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO34_OUT (PAD_GPIO34_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2ba6, PAD_GPIO34_OUT, BIT0),
    _RVM1(0x2ba6, PAD_GPIO34_OEN, BIT1),
    //reg_sixthuartmode
    _RVM1(0x1e08, 0, BIT7 | BIT6 ),   //reg[101e08]#7 ~ #6 = 00b
    //reg_od6thuart[1:0]
    _RVM1(0x1eaa, 0, BIT7 | BIT6 ),   //reg[101eaa]#7 ~ #6 = 00b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO35_IS_GPIO != GPIO_NONE)
#define PAD_GPIO35_OEN (PAD_GPIO35_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO35_OUT (PAD_GPIO35_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2ba7, PAD_GPIO35_OUT, BIT0),
    _RVM1(0x2ba7, PAD_GPIO35_OEN, BIT1),
    //reg_sixthuartmode
    _RVM1(0x1e08, 0, BIT7 | BIT6 ),   //reg[101e08]#7 ~ #6 = 00b
    //reg_od6thuart[1:0]
    _RVM1(0x1eaa, 0, BIT7 | BIT6 ),   //reg[101eaa]#7 ~ #6 = 00b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO36_IS_GPIO != GPIO_NONE)
#define PAD_GPIO36_OEN (PAD_GPIO36_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO36_OUT (PAD_GPIO36_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2ba8, PAD_GPIO36_OUT, BIT0),
    _RVM1(0x2ba8, PAD_GPIO36_OEN, BIT1),
    //reg_miic_mode3
    _RVM1(0x1edc, 0, BIT3 ),   //reg[101edc]#3 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GPIO37_IS_GPIO != GPIO_NONE)
#define PAD_GPIO37_OEN (PAD_GPIO37_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO37_OUT (PAD_GPIO37_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2ba9, PAD_GPIO37_OUT, BIT0),
    _RVM1(0x2ba9, PAD_GPIO37_OEN, BIT1),
    //reg_miic_mode3
    _RVM1(0x1edc, 0, BIT3 ),   //reg[101edc]#3 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_I2S_IN_WS_IS_GPIO != GPIO_NONE)
#define PAD_I2S_IN_WS_OEN (PAD_I2S_IN_WS_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_I2S_IN_WS_OUT (PAD_I2S_IN_WS_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b36, PAD_I2S_IN_WS_OUT, BIT0),
    _RVM1(0x2b36, PAD_I2S_IN_WS_OEN, BIT1),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5 | BIT4 ),   //reg[101e05]#5 ~ #4 = 0b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_i2sinconfig
    _RVM1(0x1eae, 0, BIT2 ),   //reg[101eae]#2 = 0b
    //reg_mcujtagmode[1:0]
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 0b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1 | BIT0 ),   //reg[101e07]#1 ~ #0 = 0b
    //reg_thirduartmode[1:0]
    _RVM1(0x1e05, 0, BIT3 | BIT2 ),   //reg[101e05]#3 ~ #2 = 0b
    //reg_od3rduart[1:0]
    _RVM1(0x1ea9, 0, BIT3 | BIT2 ),   //reg[101ea9]#3 ~ #2 = 0b
    //reg_ext_int[6]
    _RVM1(0x1ea5, 0, BIT6 ),   //reg[101ea5]#6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_I2S_IN_BCK_IS_GPIO != GPIO_NONE)
#define PAD_I2S_IN_BCK_OEN (PAD_I2S_IN_BCK_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_I2S_IN_BCK_OUT (PAD_I2S_IN_BCK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b37, PAD_I2S_IN_BCK_OUT, BIT0),
    _RVM1(0x2b37, PAD_I2S_IN_BCK_OEN, BIT1),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5 | BIT4 ),   //reg[101e05]#5 ~ #4 = 0b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_i2sinconfig
    _RVM1(0x1eae, 0, BIT2 ),   //reg[101eae]#2 = 0b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1 | BIT0 ),   //reg[101e07]#1 ~ #0 = 0b
    //reg_thirduartmode[1:0]
    _RVM1(0x1e05, 0, BIT3 | BIT2 ),   //reg[101e05]#3 ~ #2 = 0b
    //reg_od3rduart[1:0]
    _RVM1(0x1ea9, 0, BIT3 | BIT2 ),   //reg[101ea9]#3 ~ #2 = 0b
    //reg_miic_mode2
    _RVM1(0x1edc, 0, BIT2 ),   //reg[101edc]#2 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_I2S_IN_SD_IS_GPIO != GPIO_NONE)
#define PAD_I2S_IN_SD_OEN (PAD_I2S_IN_SD_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_I2S_IN_SD_OUT (PAD_I2S_IN_SD_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b38, PAD_I2S_IN_SD_OUT, BIT0),
    _RVM1(0x2b38, PAD_I2S_IN_SD_OEN, BIT1),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5 | BIT4 ),   //reg[101e05]#5 ~ #4 = 0b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_i2sinconfig
    _RVM1(0x1eae, 0, BIT2 ),   //reg[101eae]#2 = 0b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1 | BIT0 ),   //reg[101e07]#1 ~ #0 = 0b
    //reg_tserrout[1:0]
    _RVM1(0x1ec9, 0, BIT1 | BIT0 ),   //reg[101ec9]#1 ~ #0 = 0b
    //reg_miic_mode2
    _RVM1(0x1edc, 0, BIT2 ),   //reg[101edc]#2 = 0b
    //reg_3dflagconfig[1:0]
    _RVM1(0x1eb3, 0, BIT7 | BIT6 ),   //reg[101eb3]#7 ~ #6 = 0b
    //reg_osd3dflag_config
    _RVM1(0x1ef6, 0, BIT7 | BIT6 ),   //reg[101ef6]#7 ~ #6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_SPDIF_IN_IS_GPIO != GPIO_NONE)
#define PAD_SPDIF_IN_OEN (PAD_SPDIF_IN_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_SPDIF_IN_OUT (PAD_SPDIF_IN_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b39, PAD_SPDIF_IN_OUT, BIT0),
    _RVM1(0x2b39, PAD_SPDIF_IN_OEN, BIT1),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5 | BIT4 ),   //reg[101e05]#5 ~ #4 = 0b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_spdifinconfig
    _RVM1(0x1eae, 0, BIT6 ),   //reg[101eae]#6 = 0b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1 | BIT0 ),   //reg[101e07]#1 ~ #0 = 0b
    //reg_3dflagconfig[1:0]
    _RVM1(0x1eb3, 0, BIT7 | BIT6 ),   //reg[101eb3]#7 ~ #6 = 0b
    //reg_osd3dflag_config
    _RVM1(0x1ef6, 0, BIT7 | BIT6 ),   //reg[101ef6]#7 ~ #6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_SPDIF_OUT_IS_GPIO != GPIO_NONE)
#define PAD_SPDIF_OUT_OEN (PAD_SPDIF_OUT_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_SPDIF_OUT_OUT (PAD_SPDIF_OUT_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b3a, PAD_SPDIF_OUT_OUT, BIT0),
    _RVM1(0x2b3a, PAD_SPDIF_OUT_OEN, BIT1),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5 | BIT4 ),   //reg[101e05]#5 ~ #4 = 0b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_spdifoutconfig
    _RVM1(0x1eae, 0, BIT7 ),   //reg[101eae]#7 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_I2S_OUT_WS_IS_GPIO != GPIO_NONE)
#define PAD_I2S_OUT_WS_OEN (PAD_I2S_OUT_WS_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_I2S_OUT_WS_OUT (PAD_I2S_OUT_WS_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b3b, PAD_I2S_OUT_WS_OUT, BIT0),
    _RVM1(0x2b3b, PAD_I2S_OUT_WS_OEN, BIT1),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5 | BIT4 ),   //reg[101e05]#5 ~ #4 = 0b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_i2soutconfig0
    _RVM1(0x1eae, 0, BIT4 ),   //reg[101eae]#4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_I2S_OUT_MCK_IS_GPIO != GPIO_NONE)
#define PAD_I2S_OUT_MCK_OEN (PAD_I2S_OUT_MCK_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_I2S_OUT_MCK_OUT (PAD_I2S_OUT_MCK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b3c, PAD_I2S_OUT_MCK_OUT, BIT0),
    _RVM1(0x2b3c, PAD_I2S_OUT_MCK_OEN, BIT1),
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_i2soutconfig0
    _RVM1(0x1eae, 0, BIT4 ),   //reg[101eae]#4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_I2S_OUT_BCK_IS_GPIO != GPIO_NONE)
#define PAD_I2S_OUT_BCK_OEN (PAD_I2S_OUT_BCK_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_I2S_OUT_BCK_OUT (PAD_I2S_OUT_BCK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b3d, PAD_I2S_OUT_BCK_OUT, BIT0),
    _RVM1(0x2b3d, PAD_I2S_OUT_BCK_OEN, BIT1),
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_i2soutconfig0
    _RVM1(0x1eae, 0, BIT4 ),   //reg[101eae]#4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_I2S_OUT_SD_IS_GPIO != GPIO_NONE)
#define PAD_I2S_OUT_SD_OEN (PAD_I2S_OUT_SD_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_I2S_OUT_SD_OUT (PAD_I2S_OUT_SD_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b3e, PAD_I2S_OUT_SD_OUT, BIT0),
    _RVM1(0x2b3e, PAD_I2S_OUT_SD_OEN, BIT1),
    //reg_ej_config[1:0]
    _RVM1(0x1e05, 0, BIT5 | BIT4 ),   //reg[101e05]#5 ~ #4 = 0b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_i2soutconfig1
    _RVM1(0x1eae, 0, BIT5 ),   //reg[101eae]#5 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_I2S_OUT_SD1_IS_GPIO != GPIO_NONE)
#define PAD_I2S_OUT_SD1_OEN (PAD_I2S_OUT_SD1_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_I2S_OUT_SD1_OUT (PAD_I2S_OUT_SD1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b3f, PAD_I2S_OUT_SD1_OUT, BIT0),
    _RVM1(0x2b3f, PAD_I2S_OUT_SD1_OEN, BIT1),
    //reg_i2soutconfig2
    _RVM1(0x1eb3, 0, BIT0 ),   //reg[101eb3]#0 = 0b
    //reg_mcujtagmode[1:0]
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 0b
    //reg_spdifoutconfig2
    _RVM1(0x1e04, 0, BIT1 | BIT0 ),   //reg[101e04]#1 ~ #0 = 0b
    //reg_ext_int[7]
    _RVM1(0x1ea5, 0, BIT7 ),   //reg[101ea5]#7 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_I2S_OUT_SD2_IS_GPIO != GPIO_NONE)
#define PAD_I2S_OUT_SD2_OEN (PAD_I2S_OUT_SD2_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_I2S_OUT_SD2_OUT (PAD_I2S_OUT_SD2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b40, PAD_I2S_OUT_SD2_OUT, BIT0),
    _RVM1(0x2b40, PAD_I2S_OUT_SD2_OEN, BIT1),
    //reg_i2soutconfig3
    _RVM1(0x1eb3, 0, BIT4 ),   //reg[101eb3]#4 = 0b
    //reg_mcujtagmode[1:0]
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 0b
    //reg_fourthuartmode[1:0]
    _RVM1(0x1e04, 0, BIT7 | BIT6 ),   //reg[101e04]#7 ~ #6 = 0b
    //reg_od4thuart[1:0]
    _RVM1(0x1ea9, 0, BIT5 | BIT4 ),   //reg[101ea9]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_I2S_OUT_SD3_IS_GPIO != GPIO_NONE)
#define PAD_I2S_OUT_SD3_OEN (PAD_I2S_OUT_SD3_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_I2S_OUT_SD3_OUT (PAD_I2S_OUT_SD3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b41, PAD_I2S_OUT_SD3_OUT, BIT0),
    _RVM1(0x2b41, PAD_I2S_OUT_SD3_OEN, BIT1),
    //reg_i2soutconfig4
    _RVM1(0x1eb3, 0, BIT5 ),   //reg[101eb3]#5 = 0b
    //reg_mcujtagmode[1:0]
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 0b
    //reg_fourthuartmode[1:0]
    _RVM1(0x1e04, 0, BIT7 | BIT6 ),   //reg[101e04]#7 ~ #6 = 0b
    //reg_od4thuart[1:0]
    _RVM1(0x1ea9, 0, BIT5 | BIT4 ),   //reg[101ea9]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_VSYNC_LIKE_IS_GPIO != GPIO_NONE)
#define PAD_VSYNC_LIKE_OEN (PAD_VSYNC_LIKE_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_VSYNC_LIKE_OUT (PAD_VSYNC_LIKE_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bb0, PAD_VSYNC_LIKE_OUT, BIT0),
    _RVM1(0x2bb0, PAD_VSYNC_LIKE_OEN, BIT1),
    //reg_vsync_like_config[1:0]
    _RVM1(0x1eb4, 0, BIT7 | BIT6 ),   //reg[101eb4]#7 ~ #6 = 0b
    //reg_ext_int[1]
    _RVM1(0x1ea5, 0, BIT1 ),   //reg[101ea5]#1 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_SPI1_CK_IS_GPIO != GPIO_NONE)
#define PAD_SPI1_CK_OEN (PAD_SPI1_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_SPI1_CK_OUT (PAD_SPI1_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bb1, PAD_SPI1_CK_OUT, BIT0),
    _RVM1(0x2bb1, PAD_SPI1_CK_OEN, BIT1),
    //reg_ld_spi1_config
    _RVM1(0x1eb4, 0, BIT0 ),   //reg[101eb4]#0 = 0b
    //reg_ld_spi3_config
    _RVM1(0x1eb4, 0, BIT2 ),   //reg[101eb4]#2 = 0b
    //reg_dim_config
    _RVM1(0x1ef6, 0, BIT0 ),   //reg[101ef6]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_SPI1_DI_IS_GPIO != GPIO_NONE)
#define PAD_SPI1_DI_OEN (PAD_SPI1_DI_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_SPI1_DI_OUT (PAD_SPI1_DI_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bb2, PAD_SPI1_DI_OUT, BIT0),
    _RVM1(0x2bb2, PAD_SPI1_DI_OEN, BIT1),
    //reg_ld_spi1_config
    _RVM1(0x1eb4, 0, BIT0 ),   //reg[101eb4]#0 = 0b
    //reg_ld_spi3_config
    _RVM1(0x1eb4, 0, BIT2 ),   //reg[101eb4]#2 = 0b
    //reg_dim_config
    _RVM1(0x1ef6, 0, BIT0 ),   //reg[101ef6]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_SPI2_CK_IS_GPIO != GPIO_NONE)
#define PAD_SPI2_CK_OEN (PAD_SPI2_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_SPI2_CK_OUT (PAD_SPI2_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bb3, PAD_SPI2_CK_OUT, BIT0),
    _RVM1(0x2bb3, PAD_SPI2_CK_OEN, BIT1),
    //reg_ld_spi2_config
    _RVM1(0x1eb4, 0, BIT1 ),   //reg[101eb4]#1 = 0b
    //reg_ld_spi3_config
    _RVM1(0x1eb4, 0, BIT2 ),   //reg[101eb4]#2 = 0b
    //reg_dim_config
    _RVM1(0x1ef6, 0, BIT0 ),   //reg[101ef6]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_SPI2_DI_IS_GPIO != GPIO_NONE)
#define PAD_SPI2_DI_OEN (PAD_SPI2_DI_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_SPI2_DI_OUT (PAD_SPI2_DI_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bb4, PAD_SPI2_DI_OUT, BIT0),
    _RVM1(0x2bb4, PAD_SPI2_DI_OEN, BIT1),
    //reg_ld_spi2_config
    _RVM1(0x1eb4, 0, BIT1 ),   //reg[101eb4]#1 = 0b
    //reg_ld_spi3_config
    _RVM1(0x1eb4, 0, BIT2 ),   //reg[101eb4]#2 = 0b
    //reg_dim_config
    _RVM1(0x1ef6, 0, BIT0 ),   //reg[101ef6]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_DIM0_IS_GPIO != GPIO_NONE)
#define PAD_DIM0_OEN (PAD_DIM0_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_DIM0_OUT (PAD_DIM0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bee, PAD_DIM0_OUT, BIT0),
    _RVM1(0x2bee, PAD_DIM0_OEN, BIT1),
    //reg_dim_config
    _RVM1(0x1ef6, 0, BIT0 ),   //reg[101ef6]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_DIM1_IS_GPIO != GPIO_NONE)
#define PAD_DIM1_OEN (PAD_DIM1_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_DIM1_OUT (PAD_DIM1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bef, PAD_DIM1_OUT, BIT0),
    _RVM1(0x2bef, PAD_DIM1_OEN, BIT1),
    //reg_dim_config
    _RVM1(0x1ef6, 0, BIT0 ),   //reg[101ef6]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_DIM2_IS_GPIO != GPIO_NONE)
#define PAD_DIM2_OEN (PAD_DIM2_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_DIM2_OUT (PAD_DIM2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bf0, PAD_DIM2_OUT, BIT0),
    _RVM1(0x2bf0, PAD_DIM2_OEN, BIT1),
    //reg_dim_config
    _RVM1(0x1ef6, 0, BIT0 ),   //reg[101ef6]#0 = 0b
    //reg_fifthuartmode[1:0]
    _RVM1(0x1e08, 0, BIT3 | BIT2 ),   //reg[101e08]#3 ~ #2 = 0b
    //reg_od5thuart[1:0]
    _RVM1(0x1eaa, 0, BIT5 | BIT4 ),   //reg[101eaa]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_DIM3_IS_GPIO != GPIO_NONE)
#define PAD_DIM3_OEN (PAD_DIM3_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_DIM3_OUT (PAD_DIM3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bf1, PAD_DIM3_OUT, BIT0),
    _RVM1(0x2bf1, PAD_DIM3_OEN, BIT1),
    //reg_dim_config
    _RVM1(0x1ef6, 0, BIT0 ),   //reg[101ef6]#0 = 0b
    //reg_fifthuartmode[1:0]
    _RVM1(0x1e08, 0, BIT3 | BIT2 ),   //reg[101e08]#3 ~ #2 = 0b
    //reg_od5thuart[1:0]
    _RVM1(0x1eaa, 0, BIT5 | BIT4 ),   //reg[101eaa]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM2_CE_N_IS_GPIO != GPIO_NONE)
#define PAD_PCM2_CE_N_OEN (PAD_PCM2_CE_N_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM2_CE_N_OUT (PAD_PCM2_CE_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b63, PAD_PCM2_CE_N_OUT, BIT0),
    _RVM1(0x2b63, PAD_PCM2_CE_N_OEN, BIT1),
    //reg_pcm2ctrlconfig
    _RVM1(0x1ec8, 0, BIT3 ),   //reg[101ec8]#3 = 0b
    //reg_ext_int[0]
    _RVM1(0x1ea5, 0, BIT0 ),   //reg[101ea5]#0 = 0b
    //reg_sdio_config[1:0]
    _RVM1(0x1ef6, 0, BIT5 | BIT4 ),   //reg[101ef6]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM2_IRQA_N_IS_GPIO != GPIO_NONE)
#define PAD_PCM2_IRQA_N_OEN (PAD_PCM2_IRQA_N_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM2_IRQA_N_OUT (PAD_PCM2_IRQA_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b64, PAD_PCM2_IRQA_N_OUT, BIT0),
    _RVM1(0x2b64, PAD_PCM2_IRQA_N_OEN, BIT1),
    //reg_pcm2ctrlconfig
    _RVM1(0x1ec8, 0, BIT3 ),   //reg[101ec8]#3 = 0b
    //reg_ext_int[2]
    _RVM1(0x1ea5, 0, BIT2 ),   //reg[101ea5]#2 = 0b
    //reg_sdio_config[1:0]
    _RVM1(0x1ef6, 0, BIT5 | BIT4 ),   //reg[101ef6]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM2_WAIT_N_IS_GPIO != GPIO_NONE)
#define PAD_PCM2_WAIT_N_OEN (PAD_PCM2_WAIT_N_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM2_WAIT_N_OUT (PAD_PCM2_WAIT_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b65, PAD_PCM2_WAIT_N_OUT, BIT0),
    _RVM1(0x2b65, PAD_PCM2_WAIT_N_OEN, BIT1),
    //reg_pcm2ctrlconfig
    _RVM1(0x1ec8, 0, BIT3 ),   //reg[101ec8]#3 = 0b
    //reg_sd_config[1:0]
    _RVM1(0x1eb5, 0, BIT1 | BIT0 ),   //reg[101eb5]#1 ~ #0 = 0b
    //reg_sdio_config[1:0]
    _RVM1(0x1ef6, 0, BIT5 | BIT4 ),   //reg[101ef6]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM2_RESET_IS_GPIO != GPIO_NONE)
#define PAD_PCM2_RESET_OEN (PAD_PCM2_RESET_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM2_RESET_OUT (PAD_PCM2_RESET_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b66, PAD_PCM2_RESET_OUT, BIT0),
    _RVM1(0x2b66, PAD_PCM2_RESET_OEN, BIT1),
    //reg_pcm2ctrlconfig
    _RVM1(0x1ec8, 0, BIT3 ),   //reg[101ec8]#3 = 0b
    //reg_sd_config[1:0]
    _RVM1(0x1eb5, 0, BIT1 | BIT0 ),   //reg[101eb5]#1 ~ #0 = 0b
    //reg_sdio_config[1:0]
    _RVM1(0x1ef6, 0, BIT5 | BIT4 ),   //reg[101ef6]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM2_CD_N_IS_GPIO != GPIO_NONE)
#define PAD_PCM2_CD_N_OEN (PAD_PCM2_CD_N_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM2_CD_N_OUT (PAD_PCM2_CD_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b67, PAD_PCM2_CD_N_OUT, BIT0),
    _RVM1(0x2b67, PAD_PCM2_CD_N_OEN, BIT1),
    //reg_lb_en
    _RVM1(0x3f80, 0, BIT0 ),   //reg[123f80]#0 = 0b
    //reg_lb_bypass_mode
    _RVM1(0x3f80, 0, BIT2 ),   //reg[123f80]#2 = 0b
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0 , BIT0 ),   //reg[101e21]#0 = 1b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_pcm2ctrlconfig
    _RVM1(0x1ec8, 0, BIT3 ),   //reg[101ec8]#3 = 0b
    //reg_pcm2ctrlconfig_cd_n
    _RVM1(0x1e9e, 0, BIT0 ),   //reg[101e9e]#0 = 0b
    //reg_ext_int[3]
    _RVM1(0x1ea5, 0, BIT3 ),   //reg[101ea5]#3 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_D3_IS_GPIO != GPIO_NONE)
#define PAD_PCM_D3_OEN (PAD_PCM_D3_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_D3_OUT (PAD_PCM_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b42, PAD_PCM_D3_OUT, BIT0),
    _RVM1(0x2b42, PAD_PCM_D3_OEN, BIT1),
    //reg_pcm_pe[3]
    _RVM1(0x1e12, BIT3 , BIT3 ),   //reg[101e12]#3 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_mcujtagmode[1:0]
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_D4_IS_GPIO != GPIO_NONE)
#define PAD_PCM_D4_OEN (PAD_PCM_D4_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_D4_OUT (PAD_PCM_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b43, PAD_PCM_D4_OUT, BIT0),
    _RVM1(0x2b43, PAD_PCM_D4_OEN, BIT1),
    //reg_pcm_pe[4]
    _RVM1(0x1e12, BIT4 , BIT4 ),   //reg[101e12]#4 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_mcujtagmode[1:0]
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_D5_IS_GPIO != GPIO_NONE)
#define PAD_PCM_D5_OEN (PAD_PCM_D5_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_D5_OUT (PAD_PCM_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b44, PAD_PCM_D5_OUT, BIT0),
    _RVM1(0x2b44, PAD_PCM_D5_OEN, BIT1),
    //reg_pcm_pe[5]
    _RVM1(0x1e12, BIT5 , BIT5 ),   //reg[101e12]#5 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_mcujtagmode[1:0]
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_D6_IS_GPIO != GPIO_NONE)
#define PAD_PCM_D6_OEN (PAD_PCM_D6_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_D6_OUT (PAD_PCM_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b45, PAD_PCM_D6_OUT, BIT0),
    _RVM1(0x2b45, PAD_PCM_D6_OEN, BIT1),
    //reg_pcm_pe[6]
    _RVM1(0x1e12, BIT6 , BIT6 ),   //reg[101e12]#6 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_mcujtagmode[1:0]
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_D7_IS_GPIO != GPIO_NONE)
#define PAD_PCM_D7_OEN (PAD_PCM_D7_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_D7_OUT (PAD_PCM_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b46, PAD_PCM_D7_OUT, BIT0),
    _RVM1(0x2b46, PAD_PCM_D7_OEN, BIT1),
    //reg_pcm_pe[7]
    _RVM1(0x1e12, BIT7 , BIT7 ),   //reg[101e12]#7 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_CE_N_IS_GPIO != GPIO_NONE)
#define PAD_PCM_CE_N_OEN (PAD_PCM_CE_N_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_CE_N_OUT (PAD_PCM_CE_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b47, PAD_PCM_CE_N_OUT, BIT0),
    _RVM1(0x2b47, PAD_PCM_CE_N_OEN, BIT1),
    //reg_pcm_pe[8]
    _RVM1(0x1e13, BIT0 , BIT0 ),   //reg[101e13]#0 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmctrlconfig
    _RVM1(0x1ec8, 0, BIT5 ),   //reg[101ec8]#5 = 0b
    //reg_cictrlconfig
    _RVM1(0x1ec8, 0, BIT1 ),   //reg[101ec8]#1 = 0b
    //reg_sm_config[1:0]
    _RVM1(0x1edc, 0, BIT5 | BIT4 ),   //reg[101edc]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_A10_IS_GPIO != GPIO_NONE)
#define PAD_PCM_A10_OEN (PAD_PCM_A10_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_A10_OUT (PAD_PCM_A10_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b48, PAD_PCM_A10_OUT, BIT0),
    _RVM1(0x2b48, PAD_PCM_A10_OEN, BIT1),
    //reg_pcm_pe[26]
    _RVM1(0x1e15, BIT2 , BIT2 ),   //reg[101e15]#2 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_sdio_config[1:0]
    _RVM1(0x1ef6, 0, BIT5 | BIT4 ),   //reg[101ef6]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_OE_N_IS_GPIO != GPIO_NONE)
#define PAD_PCM_OE_N_OEN (PAD_PCM_OE_N_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_OE_N_OUT (PAD_PCM_OE_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b49, PAD_PCM_OE_N_OUT, BIT0),
    _RVM1(0x2b49, PAD_PCM_OE_N_OEN, BIT1),
    //reg_pcm_pe[9]
    _RVM1(0x1e13, BIT1 , BIT1 ),   //reg[101e13]#1 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmctrlconfig
    _RVM1(0x1ec8, 0, BIT5 ),   //reg[101ec8]#5 = 0b
    //reg_sm_config[1:0]
    _RVM1(0x1edc, 0, BIT5 | BIT4 ),   //reg[101edc]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_A11_IS_GPIO != GPIO_NONE)
#define PAD_PCM_A11_OEN (PAD_PCM_A11_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_A11_OUT (PAD_PCM_A11_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b4a, PAD_PCM_A11_OUT, BIT0),
    _RVM1(0x2b4a, PAD_PCM_A11_OEN, BIT1),
    //reg_pcm_pe[27]
    _RVM1(0x1e15, BIT3 , BIT3 ),   //reg[101e15]#3 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_sdio_config[1:0]
    _RVM1(0x1ef6, 0, BIT5 | BIT4 ),   //reg[101ef6]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_IORD_N_IS_GPIO != GPIO_NONE)
#define PAD_PCM_IORD_N_OEN (PAD_PCM_IORD_N_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_IORD_N_OUT (PAD_PCM_IORD_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b4b, PAD_PCM_IORD_N_OUT, BIT0),
    _RVM1(0x2b4b, PAD_PCM_IORD_N_OEN, BIT1),
    //reg_pcm_pe[10]
    _RVM1(0x1e13, BIT2 , BIT2 ),   //reg[101e13]#2 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmctrlconfig
    _RVM1(0x1ec8, 0, BIT5 ),   //reg[101ec8]#5 = 0b
    //reg_cictrlconfig
    _RVM1(0x1ec8, 0, BIT1 ),   //reg[101ec8]#1 = 0b
    //reg_sm_config[1:0]
    _RVM1(0x1edc, 0, BIT5 | BIT4 ),   //reg[101edc]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_A9_IS_GPIO != GPIO_NONE)
#define PAD_PCM_A9_OEN (PAD_PCM_A9_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_A9_OUT (PAD_PCM_A9_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b4c, PAD_PCM_A9_OUT, BIT0),
    _RVM1(0x2b4c, PAD_PCM_A9_OEN, BIT1),
    //reg_pcm_pe[25]
    _RVM1(0x1e15, BIT1 , BIT1 ),   //reg[101e15]#1 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_sdio_config[1:0]
    _RVM1(0x1ef6, 0, BIT5 | BIT4 ),   //reg[101ef6]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_IOWR_N_IS_GPIO != GPIO_NONE)
#define PAD_PCM_IOWR_N_OEN (PAD_PCM_IOWR_N_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_IOWR_N_OUT (PAD_PCM_IOWR_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b4d, PAD_PCM_IOWR_N_OUT, BIT0),
    _RVM1(0x2b4d, PAD_PCM_IOWR_N_OEN, BIT1),
    //reg_pcm_pe[11]
    _RVM1(0x1e13, BIT3 , BIT3 ),   //reg[101e13]#3 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmctrlconfig
    _RVM1(0x1ec8, 0, BIT5 ),   //reg[101ec8]#5 = 0b
    //reg_cictrlconfig
    _RVM1(0x1ec8, 0, BIT1 ),   //reg[101ec8]#1 = 0b
    //reg_sm_config[1:0]
    _RVM1(0x1edc, 0, BIT5 | BIT4 ),   //reg[101edc]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_A8_IS_GPIO != GPIO_NONE)
#define PAD_PCM_A8_OEN (PAD_PCM_A8_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_A8_OUT (PAD_PCM_A8_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b4e, PAD_PCM_A8_OUT, BIT0),
    _RVM1(0x2b4e, PAD_PCM_A8_OEN, BIT1),
    //reg_pcm_pe[24]
    _RVM1(0x1e15, BIT0 , BIT0 ),   //reg[101e15]#0 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_sdio_config[1:0]
    _RVM1(0x1ef6, 0, BIT5 | BIT4 ),   //reg[101ef6]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_A13_IS_GPIO != GPIO_NONE)
#define PAD_PCM_A13_OEN (PAD_PCM_A13_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_A13_OUT (PAD_PCM_A13_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b4f, PAD_PCM_A13_OUT, BIT0),
    _RVM1(0x2b4f, PAD_PCM_A13_OEN, BIT1),
    //reg_pcm_pe[29]
    _RVM1(0x1e15, BIT5 , BIT5 ),   //reg[101e15]#5 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_A14_IS_GPIO != GPIO_NONE)
#define PAD_PCM_A14_OEN (PAD_PCM_A14_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_A14_OUT (PAD_PCM_A14_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b50, PAD_PCM_A14_OUT, BIT0),
    _RVM1(0x2b50, PAD_PCM_A14_OEN, BIT1),
    //reg_pcm_pe[30]
    _RVM1(0x1e15, BIT6 , BIT6 ),   //reg[101e15]#6 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_WE_N_IS_GPIO != GPIO_NONE)
#define PAD_PCM_WE_N_OEN (PAD_PCM_WE_N_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_WE_N_OUT (PAD_PCM_WE_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b51, PAD_PCM_WE_N_OUT, BIT0),
    _RVM1(0x2b51, PAD_PCM_WE_N_OEN, BIT1),
    //reg_pcm_pe[12]
    _RVM1(0x1e13, BIT4 , BIT4 ),   //reg[101e13]#4 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmctrlconfig
    _RVM1(0x1ec8, 0, BIT5 ),   //reg[101ec8]#5 = 0b
    //reg_sm_config[1:0]
    _RVM1(0x1edc, 0, BIT5 | BIT4 ),   //reg[101edc]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_IRQA_N_IS_GPIO != GPIO_NONE)
#define PAD_PCM_IRQA_N_OEN (PAD_PCM_IRQA_N_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_IRQA_N_OUT (PAD_PCM_IRQA_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b52, PAD_PCM_IRQA_N_OUT, BIT0),
    _RVM1(0x2b52, PAD_PCM_IRQA_N_OEN, BIT1),
    //reg_pcm_pe[13]
    _RVM1(0x1e13, BIT5 , BIT5 ),   //reg[101e13]#5 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmctrlconfig
    _RVM1(0x1ec8, 0, BIT5 ),   //reg[101ec8]#5 = 0b
    //reg_cictrlconfig
    _RVM1(0x1ec8, 0, BIT1 ),   //reg[101ec8]#1 = 0b
    //reg_sm_config[1:0]
    _RVM1(0x1edc, 0, BIT5 | BIT4 ),   //reg[101edc]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_A12_IS_GPIO != GPIO_NONE)
#define PAD_PCM_A12_OEN (PAD_PCM_A12_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_A12_OUT (PAD_PCM_A12_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b53, PAD_PCM_A12_OUT, BIT0),
    _RVM1(0x2b53, PAD_PCM_A12_OEN, BIT1),
    //reg_pcm_pe[28]
    _RVM1(0x1e15, BIT4 , BIT4 ),   //reg[101e15]#4 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_A7_IS_GPIO != GPIO_NONE)
#define PAD_PCM_A7_OEN (PAD_PCM_A7_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_A7_OUT (PAD_PCM_A7_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b54, PAD_PCM_A7_OUT, BIT0),
    _RVM1(0x2b54, PAD_PCM_A7_OEN, BIT1),
    //reg_pcm_pe[23]
    _RVM1(0x1e14, BIT7 , BIT7 ),   //reg[101e14]#7 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_sd_config[1:0]
    _RVM1(0x1eb5, 0, BIT1 | BIT0 ),   //reg[101eb5]#1 ~ #0 = 0b
    //reg_sdio_config[1:0]
    _RVM1(0x1ef6, 0, BIT5 | BIT4 ),   //reg[101ef6]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_A6_IS_GPIO != GPIO_NONE)
#define PAD_PCM_A6_OEN (PAD_PCM_A6_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_A6_OUT (PAD_PCM_A6_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b55, PAD_PCM_A6_OUT, BIT0),
    _RVM1(0x2b55, PAD_PCM_A6_OEN, BIT1),
    //reg_pcm_pe[22]
    _RVM1(0x1e14, BIT6 , BIT6 ),   //reg[101e14]#6 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_sd_config[1:0]
    _RVM1(0x1eb5, 0, BIT1 | BIT0 ),   //reg[101eb5]#1 ~ #0 = 0b
    //reg_sdio_config[1:0]
    _RVM1(0x1ef6, 0, BIT5 | BIT4 ),   //reg[101ef6]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_A5_IS_GPIO != GPIO_NONE)
#define PAD_PCM_A5_OEN (PAD_PCM_A5_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_A5_OUT (PAD_PCM_A5_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b56, PAD_PCM_A5_OUT, BIT0),
    _RVM1(0x2b56, PAD_PCM_A5_OEN, BIT1),
    //reg_pcm_pe[21]
    _RVM1(0x1e14, BIT5 , BIT5 ),   //reg[101e14]#5 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_sd_config[1:0]
    _RVM1(0x1eb5, 0, BIT1 | BIT0 ),   //reg[101eb5]#1 ~ #0 = 0b
    //reg_sdio_config[1:0]
    _RVM1(0x1ef6, 0, BIT5 | BIT4 ),   //reg[101ef6]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_WAIT_N_IS_GPIO != GPIO_NONE)
#define PAD_PCM_WAIT_N_OEN (PAD_PCM_WAIT_N_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_WAIT_N_OUT (PAD_PCM_WAIT_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b57, PAD_PCM_WAIT_N_OUT, BIT0),
    _RVM1(0x2b57, PAD_PCM_WAIT_N_OEN, BIT1),
    //reg_pcm_pe[14]
    _RVM1(0x1e13, BIT6 , BIT6 ),   //reg[101e13]#6 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmctrlconfig
    _RVM1(0x1ec8, 0, BIT5 ),   //reg[101ec8]#5 = 0b
    //reg_cictrlconfig
    _RVM1(0x1ec8, 0, BIT1 ),   //reg[101ec8]#1 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_A4_IS_GPIO != GPIO_NONE)
#define PAD_PCM_A4_OEN (PAD_PCM_A4_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_A4_OUT (PAD_PCM_A4_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b58, PAD_PCM_A4_OUT, BIT0),
    _RVM1(0x2b58, PAD_PCM_A4_OEN, BIT1),
    //reg_pcm_pe[20]
    _RVM1(0x1e14, BIT4 , BIT4 ),   //reg[101e14]#4 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_sd_config[1:0]
    _RVM1(0x1eb5, 0, BIT1 | BIT0 ),   //reg[101eb5]#1 ~ #0 = 0b
    //reg_sdio_config[1:0]
    _RVM1(0x1ef6, 0, BIT5 | BIT4 ),   //reg[101ef6]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_A3_IS_GPIO != GPIO_NONE)
#define PAD_PCM_A3_OEN (PAD_PCM_A3_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_A3_OUT (PAD_PCM_A3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b59, PAD_PCM_A3_OUT, BIT0),
    _RVM1(0x2b59, PAD_PCM_A3_OEN, BIT1),
    //reg_pcm_pe[19]
    _RVM1(0x1e14, BIT3 , BIT3 ),   //reg[101e14]#3 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_A2_IS_GPIO != GPIO_NONE)
#define PAD_PCM_A2_OEN (PAD_PCM_A2_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_A2_OUT (PAD_PCM_A2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b5a, PAD_PCM_A2_OUT, BIT0),
    _RVM1(0x2b5a, PAD_PCM_A2_OEN, BIT1),
    //reg_pcm_pe[18]
    _RVM1(0x1e14, BIT2 , BIT2 ),   //reg[101e14]#2 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_REG_N_IS_GPIO != GPIO_NONE)
#define PAD_PCM_REG_N_OEN (PAD_PCM_REG_N_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_REG_N_OUT (PAD_PCM_REG_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b5b, PAD_PCM_REG_N_OUT, BIT0),
    _RVM1(0x2b5b, PAD_PCM_REG_N_OEN, BIT1),
    //reg_pcm_pe[15]
    _RVM1(0x1e13, BIT7 , BIT7 ),   //reg[101e13]#7 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_pcmctrlconfig
    _RVM1(0x1ec8, 0, BIT5 ),   //reg[101ec8]#5 = 0b
    //reg_cictrlconfig
    _RVM1(0x1ec8, 0, BIT1 ),   //reg[101ec8]#1 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_A1_IS_GPIO != GPIO_NONE)
#define PAD_PCM_A1_OEN (PAD_PCM_A1_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_A1_OUT (PAD_PCM_A1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b5c, PAD_PCM_A1_OUT, BIT0),
    _RVM1(0x2b5c, PAD_PCM_A1_OEN, BIT1),
    //reg_pcm_pe[17]
    _RVM1(0x1e14, BIT1 , BIT1 ),   //reg[101e14]#1 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_A0_IS_GPIO != GPIO_NONE)
#define PAD_PCM_A0_OEN (PAD_PCM_A0_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_A0_OUT (PAD_PCM_A0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b5d, PAD_PCM_A0_OUT, BIT0),
    _RVM1(0x2b5d, PAD_PCM_A0_OEN, BIT1),
    //reg_pcm_pe[16]
    _RVM1(0x1e14, BIT0 , BIT0 ),   //reg[101e14]#0 = 1b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_D0_IS_GPIO != GPIO_NONE)
#define PAD_PCM_D0_OEN (PAD_PCM_D0_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_D0_OUT (PAD_PCM_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b5e, PAD_PCM_D0_OUT, BIT0),
    _RVM1(0x2b5e, PAD_PCM_D0_OEN, BIT1),
    //reg_pcm_pe[0]
    _RVM1(0x1e12, BIT0 , BIT0 ),   //reg[101e12]#0 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_D1_IS_GPIO != GPIO_NONE)
#define PAD_PCM_D1_OEN (PAD_PCM_D1_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_D1_OUT (PAD_PCM_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b5f, PAD_PCM_D1_OUT, BIT0),
    _RVM1(0x2b5f, PAD_PCM_D1_OEN, BIT1),
    //reg_pcm_pe[1]
    _RVM1(0x1e12, BIT1 , BIT1 ),   //reg[101e12]#1 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_D2_IS_GPIO != GPIO_NONE)
#define PAD_PCM_D2_OEN (PAD_PCM_D2_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_D2_OUT (PAD_PCM_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b60, PAD_PCM_D2_OUT, BIT0),
    _RVM1(0x2b60, PAD_PCM_D2_OEN, BIT1),
    //reg_pcm_pe[2]
    _RVM1(0x1e12, BIT2 , BIT2 ),   //reg[101e12]#2 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pcmadconfig
    _RVM1(0x1ec8, 0, BIT4 ),   //reg[101ec8]#4 = 0b
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0 ),   //reg[101ec8]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_RESET_IS_GPIO != GPIO_NONE)
#define PAD_PCM_RESET_OEN (PAD_PCM_RESET_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_RESET_OUT (PAD_PCM_RESET_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b61, PAD_PCM_RESET_OUT, BIT0),
    _RVM1(0x2b61, PAD_PCM_RESET_OEN, BIT1),
    //reg_pcm_pe[31]
    _RVM1(0x1e15, BIT7 , BIT7 ),   //reg[101e15]#7 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_pcmctrlconfig
    _RVM1(0x1ec8, 0, BIT5 ),   //reg[101ec8]#5 = 0b
    //reg_cictrlconfig
    _RVM1(0x1ec8, 0, BIT1 ),   //reg[101ec8]#1 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PCM_CD_N_IS_GPIO != GPIO_NONE)
#define PAD_PCM_CD_N_OEN (PAD_PCM_CD_N_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PCM_CD_N_OUT (PAD_PCM_CD_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b62, PAD_PCM_CD_N_OUT, BIT0),
    _RVM1(0x2b62, PAD_PCM_CD_N_OEN, BIT1),
    //reg_pcm_pe[32]
    _RVM1(0x1e16, BIT0 , BIT0 ),   //reg[101e16]#0 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_pcmctrlconfig
    _RVM1(0x1ec8, 0, BIT5 ),   //reg[101ec8]#5 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PWM0_IS_GPIO != GPIO_NONE)
#define PAD_PWM0_OEN (PAD_PWM0_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PWM0_OUT (PAD_PWM0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b88, PAD_PWM0_OUT, BIT0),
    _RVM1(0x2b88, PAD_PWM0_OEN, BIT1),
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pwm0_mode
    _RVM1(0x1ec8, 0, BIT2 ),   //reg[101ec8]#2 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PWM1_IS_GPIO != GPIO_NONE)
#define PAD_PWM1_OEN (PAD_PWM1_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PWM1_OUT (PAD_PWM1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b89, PAD_PWM1_OUT, BIT0),
    _RVM1(0x2b89, PAD_PWM1_OEN, BIT1),
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pwm1_mode
    _RVM1(0x1ec8, 0, BIT6 ),   //reg[101ec8]#6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PWM2_IS_GPIO != GPIO_NONE)
#define PAD_PWM2_OEN (PAD_PWM2_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PWM2_OUT (PAD_PWM2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b8a, PAD_PWM2_OUT, BIT0),
    _RVM1(0x2b8a, PAD_PWM2_OEN, BIT1),
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pwm2_mode
    _RVM1(0x1ec8, 0, BIT7 ),   //reg[101ec8]#7 = 0b
    //reg_ire_mode[1:0]
    _RVM1(0x1ede, 0, BIT5 | BIT4 ),   //reg[101ede]#5 ~ #4 = 00b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PWM3_IS_GPIO != GPIO_NONE)
#define PAD_PWM3_OEN (PAD_PWM3_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PWM3_OUT (PAD_PWM3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b8b, PAD_PWM3_OUT, BIT0),
    _RVM1(0x2b8b, PAD_PWM3_OEN, BIT1),
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_pwm3_mode
    _RVM1(0x1ec9, 0, BIT4 ),   //reg[101ec9]#4 = 0b
    //reg_ire_mode[1:0]
    _RVM1(0x1ede, 0, BIT5 | BIT4 ),   //reg[101ede]#5 ~ #4 = 00b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_PWM4_IS_GPIO != GPIO_NONE)
#define PAD_PWM4_OEN (PAD_PWM4_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PWM4_OUT (PAD_PWM4_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b8c, PAD_PWM4_OUT, BIT0),
    _RVM1(0x2b8c, PAD_PWM4_OEN, BIT1),
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_i2smutemode[1:0]
    _RVM1(0x1e05, 0, BIT7 | BIT6 ),   //reg[101e05]#7 ~ #6 = 0b
    //reg_pwm4_mode
    _RVM1(0x1ec9, 0, BIT5 ),   //reg[101ec9]#5 = 0b
    //reg_tserrout[1:0]
    _RVM1(0x1ec9, 0, BIT1 | BIT0 ),   //reg[101ec9]#1 ~ #0 = 0b
    //reg_ire_mode[1:0]
    _RVM1(0x1ede, 0, BIT5 | BIT4 ),   //reg[101ede]#5 ~ #4 = 00b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TCON0_IS_GPIO != GPIO_NONE)
#define PAD_TCON0_OEN (PAD_TCON0_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TCON0_OUT (PAD_TCON0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b93, PAD_TCON0_OUT, BIT0),
    _RVM1(0x2b93, PAD_TCON0_OEN, BIT1),
    //reg_tconconfig[0]
    _RVM1(0x1ea0, 0, BIT0 ),   //reg[101ea0]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TCON1_IS_GPIO != GPIO_NONE)
#define PAD_TCON1_OEN (PAD_TCON1_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TCON1_OUT (PAD_TCON1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b92, PAD_TCON1_OUT, BIT0),
    _RVM1(0x2b92, PAD_TCON1_OEN, BIT1),
    //reg_tconconfig[1]
    _RVM1(0x1ea0, 0, BIT1 ),   //reg[101ea0]#1 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TCON2_IS_GPIO != GPIO_NONE)
#define PAD_TCON2_OEN (PAD_TCON2_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TCON2_OUT (PAD_TCON2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b95, PAD_TCON2_OUT, BIT0),
    _RVM1(0x2b95, PAD_TCON2_OEN, BIT1),
    //reg_tconconfig[2]
    _RVM1(0x1ea0, 0, BIT2 ),   //reg[101ea0]#2 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TCON3_IS_GPIO != GPIO_NONE)
#define PAD_TCON3_OEN (PAD_TCON3_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TCON3_OUT (PAD_TCON3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b94, PAD_TCON3_OUT, BIT0),
    _RVM1(0x2b94, PAD_TCON3_OEN, BIT1),
    //reg_tconconfig[3]
    _RVM1(0x1ea0, 0, BIT3 ),   //reg[101ea0]#3 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TCON4_IS_GPIO != GPIO_NONE)
#define PAD_TCON4_OEN (PAD_TCON4_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TCON4_OUT (PAD_TCON4_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b97, PAD_TCON4_OUT, BIT0),
    _RVM1(0x2b97, PAD_TCON4_OEN, BIT1),
    //reg_tconconfig[4]
    _RVM1(0x1ea0, 0, BIT4 ),   //reg[101ea0]#4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TCON5_IS_GPIO != GPIO_NONE)
#define PAD_TCON5_OEN (PAD_TCON5_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TCON5_OUT (PAD_TCON5_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b96, PAD_TCON5_OUT, BIT0),
    _RVM1(0x2b96, PAD_TCON5_OEN, BIT1),
    //reg_tconconfig[5]
    _RVM1(0x1ea0, 0, BIT5 ),   //reg[101ea0]#5 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TCON6_IS_GPIO != GPIO_NONE)
#define PAD_TCON6_OEN (PAD_TCON6_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TCON6_OUT (PAD_TCON6_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b99, PAD_TCON6_OUT, BIT0),
    _RVM1(0x2b99, PAD_TCON6_OEN, BIT1),
    //reg_tconconfig[6]
    _RVM1(0x1ea0, 0, BIT6 ),   //reg[101ea0]#6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TCON7_IS_GPIO != GPIO_NONE)
#define PAD_TCON7_OEN (PAD_TCON7_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TCON7_OUT (PAD_TCON7_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b98, PAD_TCON7_OUT, BIT0),
    _RVM1(0x2b98, PAD_TCON7_OEN, BIT1),
    //reg_tconconfig[7]
    _RVM1(0x1ea0, 0, BIT7 ),   //reg[101ea0]#7 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TCON8_IS_GPIO != GPIO_NONE)
#define PAD_TCON8_OEN (PAD_TCON8_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TCON8_OUT (PAD_TCON8_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b9b, PAD_TCON8_OUT, BIT0),
    _RVM1(0x2b9b, PAD_TCON8_OEN, BIT1),
    //reg_tconconfig[8]
    _RVM1(0x1ea1, 0, BIT0 ),   //reg[101ea1]#0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TCON9_IS_GPIO != GPIO_NONE)
#define PAD_TCON9_OEN (PAD_TCON9_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TCON9_OUT (PAD_TCON9_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b9a, PAD_TCON9_OUT, BIT0),
    _RVM1(0x2b9a, PAD_TCON9_OEN, BIT1),
    //reg_tconconfig[9]
    _RVM1(0x1ea1, 0, BIT1 ),   //reg[101ea1]#1 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TCON10_IS_GPIO != GPIO_NONE)
#define PAD_TCON10_OEN (PAD_TCON10_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TCON10_OUT (PAD_TCON10_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b9d, PAD_TCON10_OUT, BIT0),
    _RVM1(0x2b9d, PAD_TCON10_OEN, BIT1),
    //reg_tconconfig[10]
    _RVM1(0x1ea1, 0, BIT2 ),   //reg[101ea1]#2 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TCON11_IS_GPIO != GPIO_NONE)
#define PAD_TCON11_OEN (PAD_TCON11_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TCON11_OUT (PAD_TCON11_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b9c, PAD_TCON11_OUT, BIT0),
    _RVM1(0x2b9c, PAD_TCON11_OEN, BIT1),
    //reg_tconconfig[11]
    _RVM1(0x1ea1, 0, BIT3 ),   //reg[101ea1]#3 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TCON12_IS_GPIO != GPIO_NONE)
#define PAD_TCON12_OEN (PAD_TCON12_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TCON12_OUT (PAD_TCON12_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b9f, PAD_TCON12_OUT, BIT0),
    _RVM1(0x2b9f, PAD_TCON12_OEN, BIT1),
    //reg_tconconfig[12]
    _RVM1(0x1ea1, 0, BIT4 ),   //reg[101ea1]#4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TCON13_IS_GPIO != GPIO_NONE)
#define PAD_TCON13_OEN (PAD_TCON13_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TCON13_OUT (PAD_TCON13_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b9e, PAD_TCON13_OUT, BIT0),
    _RVM1(0x2b9e, PAD_TCON13_OEN, BIT1),
    //reg_tconconfig[13]
    _RVM1(0x1ea1, 0, BIT5 ),   //reg[101ea1]#5 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TGPIO0_IS_GPIO != GPIO_NONE)
#define PAD_TGPIO0_OEN (PAD_TGPIO0_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TGPIO0_OUT (PAD_TGPIO0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b8d, PAD_TGPIO0_OUT, BIT0),
    _RVM1(0x2b8d, PAD_TGPIO0_OEN, BIT1),
    //reg_vsync_vif_out_en
    _RVM1(0x1ea3, 0, BIT6 ),   //reg[101ea3]#6 = 0b
    //reg_mcujtagmode[1:0]
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 0b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1 | BIT0 ),   //reg[101e07]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TGPIO1_IS_GPIO != GPIO_NONE)
#define PAD_TGPIO1_OEN (PAD_TGPIO1_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TGPIO1_OUT (PAD_TGPIO1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b8e, PAD_TGPIO1_OUT, BIT0),
    _RVM1(0x2b8e, PAD_TGPIO1_OEN, BIT1),
    //reg_mcujtagmode[1:0]
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 0b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1 | BIT0 ),   //reg[101e07]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TGPIO2_IS_GPIO != GPIO_NONE)
#define PAD_TGPIO2_OEN (PAD_TGPIO2_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TGPIO2_OUT (PAD_TGPIO2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b8f, PAD_TGPIO2_OUT, BIT0),
    _RVM1(0x2b8f, PAD_TGPIO2_OEN, BIT1),
    //reg_mcujtagmode[1:0]
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 0b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1 | BIT0 ),   //reg[101e07]#1 ~ #0 = 0b
    //reg_miic_mode1
    _RVM1(0x1edc, 0, BIT1 ),   //reg[101edc]#1 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TGPIO3_IS_GPIO != GPIO_NONE)
#define PAD_TGPIO3_OEN (PAD_TGPIO3_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TGPIO3_OUT (PAD_TGPIO3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b90, PAD_TGPIO3_OUT, BIT0),
    _RVM1(0x2b90, PAD_TGPIO3_OEN, BIT1),
    //reg_mcujtagmode[1:0]
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 0b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1 | BIT0 ),   //reg[101e07]#1 ~ #0 = 0b
    //reg_miic_mode1
    _RVM1(0x1edc, 0, BIT1 ),   //reg[101edc]#1 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS0_D0_IS_GPIO != GPIO_NONE)
#define PAD_TS0_D0_OEN (PAD_TS0_D0_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS0_D0_OUT (PAD_TS0_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b1c, PAD_TS0_D0_OUT, BIT0),
    _RVM1(0x2b1c, PAD_TS0_D0_OEN, BIT1),
    //reg_ts0_pe[0]
    _RVM1(0x1e1c, BIT0 , BIT0 ),   //reg[101e1c]#0 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_ts0config[1:0]
    _RVM1(0x1eaf, 0, BIT1 | BIT0 ),   //reg[101eaf]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS0_D1_IS_GPIO != GPIO_NONE)
#define PAD_TS0_D1_OEN (PAD_TS0_D1_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS0_D1_OUT (PAD_TS0_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b1d, PAD_TS0_D1_OUT, BIT0),
    _RVM1(0x2b1d, PAD_TS0_D1_OEN, BIT1),
    //reg_ts0_pe[1]
    _RVM1(0x1e1c, BIT1 , BIT1 ),   //reg[101e1c]#1 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_ts0config[1:0]
    _RVM1(0x1eaf, 0, BIT1 | BIT0 ),   //reg[101eaf]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS0_D2_IS_GPIO != GPIO_NONE)
#define PAD_TS0_D2_OEN (PAD_TS0_D2_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS0_D2_OUT (PAD_TS0_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b1e, PAD_TS0_D2_OUT, BIT0),
    _RVM1(0x2b1e, PAD_TS0_D2_OEN, BIT1),
    //reg_ts0_pe[2]
    _RVM1(0x1e1c, BIT2 , BIT2 ),   //reg[101e1c]#2 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_ts0config[1:0]
    _RVM1(0x1eaf, 0, BIT1 | BIT0 ),   //reg[101eaf]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS0_D3_IS_GPIO != GPIO_NONE)
#define PAD_TS0_D3_OEN (PAD_TS0_D3_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS0_D3_OUT (PAD_TS0_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b1f, PAD_TS0_D3_OUT, BIT0),
    _RVM1(0x2b1f, PAD_TS0_D3_OEN, BIT1),
    //reg_ts0_pe[3]
    _RVM1(0x1e1c, BIT3 , BIT3 ),   //reg[101e1c]#3 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_ts0config[1:0]
    _RVM1(0x1eaf, 0, BIT1 | BIT0 ),   //reg[101eaf]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS0_D4_IS_GPIO != GPIO_NONE)
#define PAD_TS0_D4_OEN (PAD_TS0_D4_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS0_D4_OUT (PAD_TS0_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b20, PAD_TS0_D4_OUT, BIT0),
    _RVM1(0x2b20, PAD_TS0_D4_OEN, BIT1),
    //reg_ts0_pe[4]
    _RVM1(0x1e1c, BIT4 , BIT4 ),   //reg[101e1c]#4 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_ts0config[1:0]
    _RVM1(0x1eaf, 0, BIT1 | BIT0 ),   //reg[101eaf]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS0_D5_IS_GPIO != GPIO_NONE)
#define PAD_TS0_D5_OEN (PAD_TS0_D5_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS0_D5_OUT (PAD_TS0_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b21, PAD_TS0_D5_OUT, BIT0),
    _RVM1(0x2b21, PAD_TS0_D5_OEN, BIT1),
    //reg_ts0_pe[5]
    _RVM1(0x1e1c, BIT5 , BIT5 ),   //reg[101e1c]#5 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_ts0config[1:0]
    _RVM1(0x1eaf, 0, BIT1 | BIT0 ),   //reg[101eaf]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS0_D6_IS_GPIO != GPIO_NONE)
#define PAD_TS0_D6_OEN (PAD_TS0_D6_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS0_D6_OUT (PAD_TS0_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b22, PAD_TS0_D6_OUT, BIT0),
    _RVM1(0x2b22, PAD_TS0_D6_OEN, BIT1),
    //reg_ts0_pe[6]
    _RVM1(0x1e1c, BIT6 , BIT6 ),   //reg[101e1c]#6 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_ts0config[1:0]
    _RVM1(0x1eaf, 0, BIT1 | BIT0 ),   //reg[101eaf]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS0_D7_IS_GPIO != GPIO_NONE)
#define PAD_TS0_D7_OEN (PAD_TS0_D7_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS0_D7_OUT (PAD_TS0_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b23, PAD_TS0_D7_OUT, BIT0),
    _RVM1(0x2b23, PAD_TS0_D7_OEN, BIT1),
    //reg_ts0_pe[7]
    _RVM1(0x1e1c, BIT7 , BIT7 ),   //reg[101e1c]#7 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_ts0config[1:0]
    _RVM1(0x1eaf, 0, BIT1 | BIT0 ),   //reg[101eaf]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS0_VLD_IS_GPIO != GPIO_NONE)
#define PAD_TS0_VLD_OEN (PAD_TS0_VLD_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS0_VLD_OUT (PAD_TS0_VLD_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b24, PAD_TS0_VLD_OUT, BIT0),
    _RVM1(0x2b24, PAD_TS0_VLD_OEN, BIT1),
    //reg_ts0_pe[8]
    _RVM1(0x1e1d, BIT0 , BIT0 ),   //reg[101e1d]#0 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_ts0config[1:0]
    _RVM1(0x1eaf, 0, BIT1 | BIT0 ),   //reg[101eaf]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS0_SYNC_IS_GPIO != GPIO_NONE)
#define PAD_TS0_SYNC_OEN (PAD_TS0_SYNC_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS0_SYNC_OUT (PAD_TS0_SYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b25, PAD_TS0_SYNC_OUT, BIT0),
    _RVM1(0x2b25, PAD_TS0_SYNC_OEN, BIT1),
    //reg_ts0_pe[9]
    _RVM1(0x1e1d, BIT1 , BIT1 ),   //reg[101e1d]#1 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_ts0config[1:0]
    _RVM1(0x1eaf, 0, BIT1 | BIT0 ),   //reg[101eaf]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS0_CLK_IS_GPIO != GPIO_NONE)
#define PAD_TS0_CLK_OEN (PAD_TS0_CLK_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS0_CLK_OUT (PAD_TS0_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b26, PAD_TS0_CLK_OUT, BIT0),
    _RVM1(0x2b26, PAD_TS0_CLK_OEN, BIT1),
    //reg_ts0_pe[10]
    _RVM1(0x1e1d, BIT2 , BIT2 ),   //reg[101e1d]#2 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_ts0config[1:0]
    _RVM1(0x1eaf, 0, BIT1 | BIT0 ),   //reg[101eaf]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS1_CLK_IS_GPIO != GPIO_NONE)
#define PAD_TS1_CLK_OEN (PAD_TS1_CLK_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS1_CLK_OUT (PAD_TS1_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b27, PAD_TS1_CLK_OUT, BIT0),
    _RVM1(0x2b27, PAD_TS1_CLK_OEN, BIT1),
    //reg_ts1_pe[10]
    _RVM1(0x1e0d, BIT2 , BIT2 ),   //reg[101e0d]#2 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_ts1config[1:0]
    _RVM1(0x1eaf, 0, BIT4 | BIT3 ),   //reg[101eaf]#4 ~ #3 = 0b
    //reg_ts_out_mode
    _RVM1(0x1edc, 0, BIT3 ),   //reg[101edc]#3 = 0b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1 | BIT0 ),   //reg[101e9f]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS1_SYNC_IS_GPIO != GPIO_NONE)
#define PAD_TS1_SYNC_OEN (PAD_TS1_SYNC_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS1_SYNC_OUT (PAD_TS1_SYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b28, PAD_TS1_SYNC_OUT, BIT0),
    _RVM1(0x2b28, PAD_TS1_SYNC_OEN, BIT1),
    //reg_ts1_pe[9]
    _RVM1(0x1e0d, BIT1 , BIT1 ),   //reg[101e0d]#1 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_ts1config[1:0]
    _RVM1(0x1eaf, 0, BIT4 | BIT3 ),   //reg[101eaf]#4 ~ #3 = 0b
    //reg_ts_out_mode
    _RVM1(0x1edc, 0, BIT3 ),   //reg[101edc]#3 = 0b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1 | BIT0 ),   //reg[101e9f]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS1_VLD_IS_GPIO != GPIO_NONE)
#define PAD_TS1_VLD_OEN (PAD_TS1_VLD_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS1_VLD_OUT (PAD_TS1_VLD_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b29, PAD_TS1_VLD_OUT, BIT0),
    _RVM1(0x2b29, PAD_TS1_VLD_OEN, BIT1),
    //reg_ts1_pe[8]
    _RVM1(0x1e0d, BIT0 , BIT0 ),   //reg[101e0d]#0 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_ts1config[1:0]
    _RVM1(0x1eaf, 0, BIT4 | BIT3 ),   //reg[101eaf]#4 ~ #3 = 0b
    //reg_ts_out_mode
    _RVM1(0x1edc, 0, BIT3 ),   //reg[101edc]#3 = 0b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1 | BIT0 ),   //reg[101e9f]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS1_D7_IS_GPIO != GPIO_NONE)
#define PAD_TS1_D7_OEN (PAD_TS1_D7_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS1_D7_OUT (PAD_TS1_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b2a, PAD_TS1_D7_OUT, BIT0),
    _RVM1(0x2b2a, PAD_TS1_D7_OEN, BIT1),
    //reg_ts1_pe[7]
    _RVM1(0x1e0c, BIT7 , BIT7 ),   //reg[101e0c]#7 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_ts1config[1:0]
    _RVM1(0x1eaf, 0, BIT4 | BIT3 ),   //reg[101eaf]#4 ~ #3 = 0b
    //reg_ts_out_mode
    _RVM1(0x1edc, 0, BIT3 ),   //reg[101edc]#3 = 0b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1 | BIT0 ),   //reg[101e07]#1 ~ #0 = 0b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1 | BIT0 ),   //reg[101e9f]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS1_D6_IS_GPIO != GPIO_NONE)
#define PAD_TS1_D6_OEN (PAD_TS1_D6_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS1_D6_OUT (PAD_TS1_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b2b, PAD_TS1_D6_OUT, BIT0),
    _RVM1(0x2b2b, PAD_TS1_D6_OEN, BIT1),
    //reg_ts1_pe[6]
    _RVM1(0x1e0c, BIT6 , BIT6 ),   //reg[101e0c]#6 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_ts1config[1:0]
    _RVM1(0x1eaf, 0, BIT4 | BIT3 ),   //reg[101eaf]#4 ~ #3 = 0b
    //reg_ts_out_mode
    _RVM1(0x1edc, 0, BIT3 ),   //reg[101edc]#3 = 0b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1 | BIT0 ),   //reg[101e07]#1 ~ #0 = 0b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1 | BIT0 ),   //reg[101e9f]#1 ~ #0 = 0b
    //reg_sm_config[1:0]
    _RVM1(0x1edc, 0, BIT5 | BIT4 ),   //reg[101edc]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS1_D5_IS_GPIO != GPIO_NONE)
#define PAD_TS1_D5_OEN (PAD_TS1_D5_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS1_D5_OUT (PAD_TS1_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b2c, PAD_TS1_D5_OUT, BIT0),
    _RVM1(0x2b2c, PAD_TS1_D5_OEN, BIT1),
    //reg_ts1_pe[5]
    _RVM1(0x1e0c, BIT5 , BIT5 ),   //reg[101e0c]#5 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_ts1config[1:0]
    _RVM1(0x1eaf, 0, BIT4 | BIT3 ),   //reg[101eaf]#4 ~ #3 = 0b
    //reg_ts_out_mode
    _RVM1(0x1edc, 0, BIT3 ),   //reg[101edc]#3 = 0b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1 | BIT0 ),   //reg[101e07]#1 ~ #0 = 0b
    //reg_pdtracectrl[1:0]
    _RVM1(0x1e9f, 0, BIT1 | BIT0 ),   //reg[101e9f]#1 ~ #0 = 0b
    //reg_sm_config[1:0]
    _RVM1(0x1edc, 0, BIT5 | BIT4 ),   //reg[101edc]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS1_D4_IS_GPIO != GPIO_NONE)
#define PAD_TS1_D4_OEN (PAD_TS1_D4_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS1_D4_OUT (PAD_TS1_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b2d, PAD_TS1_D4_OUT, BIT0),
    _RVM1(0x2b2d, PAD_TS1_D4_OEN, BIT1),
    //reg_ts1_pe[4]
    _RVM1(0x1e0c, BIT4 , BIT4 ),   //reg[101e0c]#4 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_ts1config[1:0]
    _RVM1(0x1eaf, 0, BIT4 | BIT3 ),   //reg[101eaf]#4 ~ #3 = 0b
    //reg_ts_out_mode
    _RVM1(0x1edc, 0, BIT3 ),   //reg[101edc]#3 = 0b
    //reg_dspejtagmode[1:0]
    _RVM1(0x1e07, 0, BIT1 | BIT0 ),   //reg[101e07]#1 ~ #0 = 0b
    //reg_sm_config[1:0]
    _RVM1(0x1edc, 0, BIT5 | BIT4 ),   //reg[101edc]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS1_D3_IS_GPIO != GPIO_NONE)
#define PAD_TS1_D3_OEN (PAD_TS1_D3_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS1_D3_OUT (PAD_TS1_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b2e, PAD_TS1_D3_OUT, BIT0),
    _RVM1(0x2b2e, PAD_TS1_D3_OEN, BIT1),
    //reg_ts1_pe[3]
    _RVM1(0x1e0c, BIT3 , BIT3 ),   //reg[101e0c]#3 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_ts1config[1:0]
    _RVM1(0x1eaf, 0, BIT4 | BIT3 ),   //reg[101eaf]#4 ~ #3 = 0b
    //reg_ts_out_mode
    _RVM1(0x1edc, 0, BIT3 ),   //reg[101edc]#3 = 0b
    //reg_sm_config[1:0]
    _RVM1(0x1edc, 0, BIT5 | BIT4 ),   //reg[101edc]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS1_D2_IS_GPIO != GPIO_NONE)
#define PAD_TS1_D2_OEN (PAD_TS1_D2_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS1_D2_OUT (PAD_TS1_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b2f, PAD_TS1_D2_OUT, BIT0),
    _RVM1(0x2b2f, PAD_TS1_D2_OEN, BIT1),
    //reg_ts1_pe[2]
    _RVM1(0x1e0c, BIT2 , BIT2 ),   //reg[101e0c]#2 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_ts1config[1:0]
    _RVM1(0x1eaf, 0, BIT4 | BIT3 ),   //reg[101eaf]#4 ~ #3 = 0b
    //reg_ts_out_mode
    _RVM1(0x1edc, 0, BIT3 ),   //reg[101edc]#3 = 0b
    //reg_sm_config[1:0]
    _RVM1(0x1edc, 0, BIT5 | BIT4 ),   //reg[101edc]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS1_D1_IS_GPIO != GPIO_NONE)
#define PAD_TS1_D1_OEN (PAD_TS1_D1_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS1_D1_OUT (PAD_TS1_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b30, PAD_TS1_D1_OUT, BIT0),
    _RVM1(0x2b30, PAD_TS1_D1_OEN, BIT1),
    //reg_ts1_pe[1]
    _RVM1(0x1e0c, BIT1 , BIT1 ),   //reg[101e0c]#1 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_ts1config[1:0]
    _RVM1(0x1eaf, 0, BIT4 | BIT3 ),   //reg[101eaf]#4 ~ #3 = 0b
    //reg_ts_out_mode
    _RVM1(0x1edc, 0, BIT3 ),   //reg[101edc]#3 = 0b
    //reg_sm_config[1:0]
    _RVM1(0x1edc, 0, BIT5 | BIT4 ),   //reg[101edc]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS1_D0_IS_GPIO != GPIO_NONE)
#define PAD_TS1_D0_OEN (PAD_TS1_D0_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS1_D0_OUT (PAD_TS1_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b31, PAD_TS1_D0_OUT, BIT0),
    _RVM1(0x2b31, PAD_TS1_D0_OEN, BIT1),
    //reg_ts1_pe[0]
    _RVM1(0x1e0c, BIT0 , BIT0 ),   //reg[101e0c]#0 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_ts1config[1:0]
    _RVM1(0x1eaf, 0, BIT4 | BIT3 ),   //reg[101eaf]#4 ~ #3 = 0b
    //reg_ts1config[1:0]
    _RVM1(0x1eaf, 0, BIT4 | BIT3 ),   //reg[101eaf]#4 ~ #3 = 0b
    //reg_ts_out_mode
    _RVM1(0x1edc, 0, BIT3 ),   //reg[101edc]#3 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_NAND_CEZ_IS_GPIO != GPIO_NONE)
#define PAD_NAND_CEZ_OEN (PAD_NAND_CEZ_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_NAND_CEZ_OUT (PAD_NAND_CEZ_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b78, PAD_NAND_CEZ_OUT, BIT0),
    _RVM1(0x2b78, PAD_NAND_CEZ_OEN, BIT1),
    //reg_lb_en
    _RVM1(0x3f80, 0, BIT0 ),   //reg[123f80]#0 = 0b
    //reg_lb_bypass_mode
    _RVM1(0x3f80, 0, BIT2 ),   //reg[123f80]#2 = 0b
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0 , BIT0 ),   //reg[101e21] #0 = 1b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_emmc_config[1:0]
    _RVM1(0x1edc, 0, BIT7 | BIT6 ),   //reg[101edc]#7 ~ #6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_NAND_CEZ1_IS_GPIO != GPIO_NONE)
#define PAD_NAND_CEZ1_OEN (PAD_NAND_CEZ1_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_NAND_CEZ1_OUT (PAD_NAND_CEZ1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b79, PAD_NAND_CEZ1_OUT, BIT0),
    _RVM1(0x2b79, PAD_NAND_CEZ1_OEN, BIT1),
    //reg_lb_en
    _RVM1(0x3f80, 0, BIT0 ),   //reg[123f80]#0 = 0b
    //reg_lb_bypass_mode
    _RVM1(0x3f80, 0, BIT2 ),   //reg[123f80]#2 = 0b
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0 , BIT0 ),   //reg[101e21] #0 = 1b
    //reg_nand_cs1_en
    _RVM1(0x1ede, 0, BIT5 ),   //reg[101ede]#5 = 0b
    //reg_emmc_config[1:0]
    _RVM1(0x1edc, 0, BIT7 | BIT6 ),   //reg[101edc]#7 ~ #6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_NAND_CLE_IS_GPIO != GPIO_NONE)
#define PAD_NAND_CLE_OEN (PAD_NAND_CLE_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_NAND_CLE_OUT (PAD_NAND_CLE_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b7a, PAD_NAND_CLE_OUT, BIT0),
    _RVM1(0x2b7a, PAD_NAND_CLE_OEN, BIT1),
    //reg_lb_en
    _RVM1(0x3f80, 0, BIT0 ),   //reg[123f80]#0 = 0b
    //reg_lb_bypass_mode
    _RVM1(0x3f80, 0, BIT2 ),   //reg[123f80]#2 = 0b
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0 , BIT0 ),   //reg[101e21] #0 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_emmc_config[1:0]
    _RVM1(0x1edc, 0, BIT7 | BIT6 ),   //reg[101edc]#7 ~ #6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_NAND_REZ_IS_GPIO != GPIO_NONE)
#define PAD_NAND_REZ_OEN (PAD_NAND_REZ_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_NAND_REZ_OUT (PAD_NAND_REZ_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b7b, PAD_NAND_REZ_OUT, BIT0),
    _RVM1(0x2b7b, PAD_NAND_REZ_OEN, BIT1),
    //reg_lb_en
    _RVM1(0x3f80, 0, BIT0 ),   //reg[123f80]#0 = 0b
    //reg_lb_bypass_mode
    _RVM1(0x3f80, 0, BIT2 ),   //reg[123f80]#2 = 0b
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0 , BIT0 ),   //reg[101e21] #0 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_emmc_config[1:0]
    _RVM1(0x1edc, 0, BIT7 | BIT6 ),   //reg[101edc]#7 ~ #6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_NAND_WEZ_IS_GPIO != GPIO_NONE)
#define PAD_NAND_WEZ_OEN (PAD_NAND_WEZ_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_NAND_WEZ_OUT (PAD_NAND_WEZ_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b7c, PAD_NAND_WEZ_OUT, BIT0),
    _RVM1(0x2b7c, PAD_NAND_WEZ_OEN, BIT1),
    //reg_lb_en
    _RVM1(0x3f80, 0, BIT0 ),   //reg[123f80]#0 = 0b
    //reg_lb_bypass_mode
    _RVM1(0x3f80, 0, BIT2 ),   //reg[123f80]#2 = 0b
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0 , BIT0 ),   //reg[101e21] #0 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_emmc_config[1:0]
    _RVM1(0x1edc, 0, BIT7 | BIT6 ),   //reg[101edc]#7 ~ #6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_NAND_WPZ_IS_GPIO != GPIO_NONE)
#define PAD_NAND_WPZ_OEN (PAD_NAND_WPZ_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_NAND_WPZ_OUT (PAD_NAND_WPZ_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b7d, PAD_NAND_WPZ_OUT, BIT0),
    _RVM1(0x2b7d, PAD_NAND_WPZ_OEN, BIT1),
    //reg_lb_en
    _RVM1(0x3f80, 0, BIT0 ),   //reg[123f80]#0 = 0b
    //reg_lb_bypass_mode
    _RVM1(0x3f80, 0, BIT2 ),   //reg[123f80]#2 = 0b
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0 , BIT0 ),   //reg[101e21] #0 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_emmc_config[1:0]
    _RVM1(0x1edc, 0, BIT7 | BIT6 ),   //reg[101edc]#7 ~ #6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_NAND_ALE_IS_GPIO != GPIO_NONE)
#define PAD_NAND_ALE_OEN (PAD_NAND_ALE_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_NAND_ALE_OUT (PAD_NAND_ALE_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b7e, PAD_NAND_ALE_OUT, BIT0),
    _RVM1(0x2b7e, PAD_NAND_ALE_OEN, BIT1),
    //reg_lb_en
    _RVM1(0x3f80, 0, BIT0 ),   //reg[123f80]#0 = 0b
    //reg_lb_bypass_mode
    _RVM1(0x3f80, 0, BIT2 ),   //reg[123f80]#2 = 0b
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0 , BIT0 ),   //reg[101e21] #0 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_emmc_config[1:0]
    _RVM1(0x1edc, 0, BIT7 | BIT6 ),   //reg[101edc]#7 ~ #6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_NAND_RBZ_IS_GPIO != GPIO_NONE)
#define PAD_NAND_RBZ_OEN (PAD_NAND_RBZ_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_NAND_RBZ_OUT (PAD_NAND_RBZ_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b7f, PAD_NAND_RBZ_OUT, BIT0),
    _RVM1(0x2b7f, PAD_NAND_RBZ_OEN, BIT1),
    //reg_lb_en
    _RVM1(0x3f80, 0, BIT0 ),   //reg[123f80]#0 = 0b
    //reg_lb_bypass_mode
    _RVM1(0x3f80, 0, BIT2 ),   //reg[123f80]#2 = 0b
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0 , BIT0 ),   //reg[101e21] #0 = 1b
    //reg_test_in_mode[2:0]
    //_RVM1(0x1e24, 0, BIT2 ~ BIT0 ),   //reg[101e24]#2 ~ #0 = 00b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_emmc_config[1:0]
    _RVM1(0x1edc, 0, BIT7 | BIT6 ),   //reg[101edc]#7 ~ #6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_NAND_DQS_IS_GPIO != GPIO_NONE)
#define PAD_NAND_DQS_OEN (PAD_NAND_DQS_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_NAND_DQS_OUT (PAD_NAND_DQS_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b80, PAD_NAND_DQS_OUT, BIT0),
    _RVM1(0x2b80, PAD_NAND_DQS_OEN, BIT1),
    //reg_lb_en
    _RVM1(0x3f80, 0, BIT0 ),   //reg[123f80]#0 = 0b
    //reg_lb_bypass_mode
    _RVM1(0x3f80, 0, BIT2 ),   //reg[123f80]#2 = 0b
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0 , BIT0 ),   //reg[101e21] #0 = 1b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_EMMC_RSTN_IS_GPIO != GPIO_NONE)
#define PAD_EMMC_RSTN_OEN (PAD_EMMC_RSTN_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_EMMC_RSTN_OUT (PAD_EMMC_RSTN_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bac, PAD_EMMC_RSTN_OUT, BIT0),
    _RVM1(0x2bac, PAD_EMMC_RSTN_OEN, BIT1),
    //reg_lb_en
    _RVM1(0x3f80, 0, BIT0 ),   //reg[123f80]#0 = 0b
    //reg_lb_bypass_mode
    _RVM1(0x3f80, 0, BIT2 ),   //reg[123f80]#2 = 0b
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0 , BIT0 ),   //reg[101e21] #0 = 1b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_emmc_rstn_en
    _RVM1(0x1e9e, 0, BIT2 ),   //reg[101e9e]#2 = 0b
    //reg_emmc_config[1:0]
    _RVM1(0x1edc, 0, BIT7 | BIT6 ),   //reg[101edc]#7 ~ #6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_EMMC_CLK_IS_GPIO != GPIO_NONE)
#define PAD_EMMC_CLK_OEN (PAD_EMMC_CLK_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_EMMC_CLK_OUT (PAD_EMMC_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bad, PAD_EMMC_CLK_OUT, BIT0),
    _RVM1(0x2bad, PAD_EMMC_CLK_OEN, BIT1),
    //reg_lb_en
    _RVM1(0x3f80, 0, BIT0 ),   //reg[123f80]#0 = 0b
    //reg_lb_bypass_mode
    _RVM1(0x3f80, 0, BIT2 ),   //reg[123f80]#2 = 0b
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0 , BIT0 ),   //reg[101e21] #0 = 1b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_emmc_config[1:0]
    _RVM1(0x1edc, 0, BIT7 | BIT6 ),   //reg[101edc]#7 ~ #6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_EMMC_CMD_IS_GPIO != GPIO_NONE)
#define PAD_EMMC_CMD_OEN (PAD_EMMC_CMD_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_EMMC_CMD_OUT (PAD_EMMC_CMD_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bae, PAD_EMMC_CMD_OUT, BIT0),
    _RVM1(0x2bae, PAD_EMMC_CMD_OEN, BIT1),
    //reg_lb_en
    _RVM1(0x3f80, 0, BIT0 ),   //reg[123f80]#0 = 0b
    //reg_lb_bypass_mode
    _RVM1(0x3f80, 0, BIT2 ),   //reg[123f80]#2 = 0b
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e21, BIT0 , BIT0 ),   //reg[101e21] #0 = 1b
    //reg_test_out_mode[2:0]
    //_RVM1(0x1e24, 0, BIT6 ~ BIT4 ),   //reg[101e24]#6 ~ #4 = 00b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_emmc_config[1:0]
    _RVM1(0x1edc, 0, BIT7 | BIT6 ),   //reg[101edc]#7 ~ #6 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS2_D0_IS_GPIO != GPIO_NONE)
#define PAD_TS2_D0_OEN (PAD_TS2_D0_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS2_D0_OUT (PAD_TS2_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b32, PAD_TS2_D0_OUT, BIT0),
    _RVM1(0x2b32, PAD_TS2_D0_OEN, BIT1),
    //reg_ts2config
    _RVM1(0x1eaf, 0, BIT6 ),   //reg[101eaf]#6 = 0b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_sd_config[1:0]
    _RVM1(0x1eb5, 0, BIT1 | BIT0 ),   //reg[101eb5]#1 ~ #0 = 0b
    //reg_sdio_config[1:0]
    _RVM1(0x1ef6, 0, BIT5 | BIT4 ),   //reg[101ef6]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS2_VLD_IS_GPIO != GPIO_NONE)
#define PAD_TS2_VLD_OEN (PAD_TS2_VLD_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS2_VLD_OUT (PAD_TS2_VLD_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b33, PAD_TS2_VLD_OUT, BIT0),
    _RVM1(0x2b33, PAD_TS2_VLD_OEN, BIT1),
    //reg_ts2config
    _RVM1(0x1eaf, 0, BIT6 ),   //reg[101eaf]#6 = 0b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_sd_config[1:0]
    _RVM1(0x1eb5, 0, BIT1 | BIT0 ),   //reg[101eb5]#1 ~ #0 = 0b
    //reg_sdio_config[1:0]
    _RVM1(0x1ef6, 0, BIT5 | BIT4 ),   //reg[101ef6]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS2_SYNC_IS_GPIO != GPIO_NONE)
#define PAD_TS2_SYNC_OEN (PAD_TS2_SYNC_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS2_SYNC_OUT (PAD_TS2_SYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b34, PAD_TS2_SYNC_OUT, BIT0),
    _RVM1(0x2b34, PAD_TS2_SYNC_OEN, BIT1),
    //reg_ts2config
    _RVM1(0x1eaf, 0, BIT6 ),   //reg[101eaf]#6 = 0b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_sd_config[1:0]
    _RVM1(0x1eb5, 0, BIT1 | BIT0 ),   //reg[101eb5]#1 ~ #0 = 0b
    //reg_sdio_config[1:0]
    _RVM1(0x1ef6, 0, BIT5 | BIT4 ),   //reg[101ef6]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_TS2_CLK_IS_GPIO != GPIO_NONE)
#define PAD_TS2_CLK_OEN (PAD_TS2_CLK_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TS2_CLK_OUT (PAD_TS2_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b35, PAD_TS2_CLK_OUT, BIT0),
    _RVM1(0x2b35, PAD_TS2_CLK_OEN, BIT1),
    //reg_ts2config
    _RVM1(0x1eaf, 0, BIT6 ),   //reg[101eaf]#6 = 0b
    //reg_nand_mode[1:0]
    _RVM1(0x1ede, 0, BIT7 | BIT6 ),   //reg[101ede]#7 ~ #6 = 0b
    //reg_sd_config[1:0]
    _RVM1(0x1eb5, 0, BIT1 | BIT0 ),   //reg[101eb5]#1 ~ #0 = 0b
    //reg_sdio_config[1:0]
    _RVM1(0x1ef6, 0, BIT5 | BIT4 ),   //reg[101ef6]#5 ~ #4 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GT_RX_CTL_IS_GPIO != GPIO_NONE)
#define PAD_GT_RX_CTL_OEN (PAD_GT_RX_CTL_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GT_RX_CTL_OUT (PAD_GT_RX_CTL_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bd0, PAD_GT_RX_CTL_OUT, BIT0),
    _RVM1(0x2bd0, PAD_GT_RX_CTL_OEN, BIT1),
    //reg_gt_config
    _RVM1(0x1ef8, 0, BIT1 | BIT0 ),   //reg[101ef8]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GT_RX_D0_IS_GPIO != GPIO_NONE)
#define PAD_GT_RX_D0_OEN (PAD_GT_RX_D0_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GT_RX_D0_OUT (PAD_GT_RX_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bd1, PAD_GT_RX_D0_OUT, BIT0),
    _RVM1(0x2bd1, PAD_GT_RX_D0_OEN, BIT1),
    //reg_gt_config
    _RVM1(0x1ef8, 0, BIT1 | BIT0 ),   //reg[101ef8]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GT_RX_D1_IS_GPIO != GPIO_NONE)
#define PAD_GT_RX_D1_OEN (PAD_GT_RX_D1_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GT_RX_D1_OUT (PAD_GT_RX_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bd2, PAD_GT_RX_D1_OUT, BIT0),
    _RVM1(0x2bd2, PAD_GT_RX_D1_OEN, BIT1),
    //reg_gt_config
    _RVM1(0x1ef8, 0, BIT1 | BIT0 ),   //reg[101ef8]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GT_RX_D2_IS_GPIO != GPIO_NONE)
#define PAD_GT_RX_D2_OEN (PAD_GT_RX_D2_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GT_RX_D2_OUT (PAD_GT_RX_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bd3, PAD_GT_RX_D2_OUT, BIT0),
    _RVM1(0x2bd3, PAD_GT_RX_D2_OEN, BIT1),
    //reg_gt_config
    _RVM1(0x1ef8, 0, BIT1 | BIT0 ),   //reg[101ef8]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GT_RX_D3_IS_GPIO != GPIO_NONE)
#define PAD_GT_RX_D3_OEN (PAD_GT_RX_D3_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GT_RX_D3_OUT (PAD_GT_RX_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bd4, PAD_GT_RX_D3_OUT, BIT0),
    _RVM1(0x2bd4, PAD_GT_RX_D3_OEN, BIT1),
    //reg_gt_config
    _RVM1(0x1ef8, 0, BIT1 | BIT0 ),   //reg[101ef8]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GT_RX_CLK_IS_GPIO != GPIO_NONE)
#define PAD_GT_RX_CLK_OEN (PAD_GT_RX_CLK_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GT_RX_CLK_OUT (PAD_GT_RX_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bd5, PAD_GT_RX_CLK_OUT, BIT0),
    _RVM1(0x2bd5, PAD_GT_RX_CLK_OEN, BIT1),
    //reg_gt_config
    _RVM1(0x1ef8, 0, BIT1 | BIT0 ),   //reg[101ef8]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GT_TX_CLK_IS_GPIO != GPIO_NONE)
#define PAD_GT_TX_CLK_OEN (PAD_GT_TX_CLK_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GT_TX_CLK_OUT (PAD_GT_TX_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bd6, PAD_GT_TX_CLK_OUT, BIT0),
    _RVM1(0x2bd6, PAD_GT_TX_CLK_OEN, BIT1),
    //reg_gt_config
    _RVM1(0x1ef8, 0, BIT1 | BIT0 ),   //reg[101ef8]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GT_TX_D0_IS_GPIO != GPIO_NONE)
#define PAD_GT_TX_D0_OEN (PAD_GT_TX_D0_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GT_TX_D0_OUT (PAD_GT_TX_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bd7, PAD_GT_TX_D0_OUT, BIT0),
    _RVM1(0x2bd7, PAD_GT_TX_D0_OEN, BIT1),
    //reg_gt_config
    _RVM1(0x1ef8, 0, BIT1 | BIT0 ),   //reg[101ef8]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GT_TX_D1_IS_GPIO != GPIO_NONE)
#define PAD_GT_TX_D1_OEN (PAD_GT_TX_D1_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GT_TX_D1_OUT (PAD_GT_TX_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bd8, PAD_GT_TX_D1_OUT, BIT0),
    _RVM1(0x2bd8, PAD_GT_TX_D1_OEN, BIT1),
    //reg_gt_config
    _RVM1(0x1ef8, 0, BIT1 | BIT0 ),   //reg[101ef8]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GT_TX_D2_IS_GPIO != GPIO_NONE)
#define PAD_GT_TX_D2_OEN (PAD_GT_TX_D2_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GT_TX_D2_OUT (PAD_GT_TX_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bd9, PAD_GT_TX_D2_OUT, BIT0),
    _RVM1(0x2bd9, PAD_GT_TX_D2_OEN, BIT1),
    //reg_gt_config
    _RVM1(0x1ef8, 0, BIT1 | BIT0 ),   //reg[101ef8]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GT_TX_D3_IS_GPIO != GPIO_NONE)
#define PAD_GT_TX_D3_OEN (PAD_GT_TX_D3_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GT_TX_D3_OUT (PAD_GT_TX_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bda, PAD_GT_TX_D3_OUT, BIT0),
    _RVM1(0x2bda, PAD_GT_TX_D3_OEN, BIT1),
    //reg_gt_config
    _RVM1(0x1ef8, 0, BIT1 | BIT0 ),   //reg[101ef8]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GT_TX_CTL_IS_GPIO != GPIO_NONE)
#define PAD_GT_TX_CTL_OEN (PAD_GT_TX_CTL_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GT_TX_CTL_OUT (PAD_GT_TX_CTL_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bdb, PAD_GT_TX_CTL_OUT, BIT0),
    _RVM1(0x2bdb, PAD_GT_TX_CTL_OEN, BIT1),
    //reg_gt_config
    _RVM1(0x1ef8, 0, BIT1 | BIT0 ),   //reg[101ef8]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GT_MDC_IS_GPIO != GPIO_NONE)
#define PAD_GT_MDC_OEN (PAD_GT_MDC_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GT_MDC_OUT (PAD_GT_MDC_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bdc, PAD_GT_MDC_OUT, BIT0),
    _RVM1(0x2bdc, PAD_GT_MDC_OEN, BIT1),
    //reg_gt_config
    _RVM1(0x1ef8, 0, BIT1 | BIT0 ),   //reg[101ef8]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GT_MDIO_IS_GPIO != GPIO_NONE)
#define PAD_GT_MDIO_OEN (PAD_GT_MDIO_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GT_MDIO_OUT (PAD_GT_MDIO_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bdd, PAD_GT_MDIO_OUT, BIT0),
    _RVM1(0x2bdd, PAD_GT_MDIO_OEN, BIT1),
    //reg_gt_config
    _RVM1(0x1ef8, 0, BIT1 | BIT0 ),   //reg[101ef8]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif

#if(PAD_GT_FR_CLK_IS_GPIO != GPIO_NONE)
#define PAD_GT_FR_CLK_OEN (PAD_GT_FR_CLK_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GT_FR_CLK_OUT (PAD_GT_FR_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bde, PAD_GT_FR_CLK_OUT, BIT0),
    _RVM1(0x2bde, PAD_GT_FR_CLK_OEN, BIT1),
    //reg_gt_config
    _RVM1(0x1ef8, 0, BIT1 | BIT0 ),   //reg[101ef8]#1 ~ #0 = 0b
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7 ),   //reg[101ea1]#7 = 0b
#endif


//---------------------------------------------------------------------
// Pad Configuartion
//---------------------------------------------------------------------
#if (PADS_VSYNC_VIF_OUT_EN != Unknown_pad_mux)
#define VSYNC_VIF_OUT_EN   ((PADS_VSYNC_VIF_OUT_EN == ENABLE) ? BIT6 : 0)
            _RVM1(0x1EA3, VSYNC_VIF_OUT_EN, BIT6),
#endif

#if (PADS_TS0_CONFIG != Unknown_pad_mux)
#define TS0_CONFIG   ((PADS_TS0_CONFIG == PARALLEL_IN) ? BIT0 : \
                      (PADS_TS0_CONFIG == SERIAL_IN) ? BIT1 : 0)
        _RVM1(0x1EAF, TS0_CONFIG, BITMASK(1:0)),
#endif

#if (PADS_TS1_CONFIG != Unknown_pad_mux)
#define TS1_CONFIG   ((PADS_TS1_CONFIG == PARALLEL_IN) ? BIT3 : \
                      (PADS_TS1_CONFIG == PARALLEL_OUT) ? BIT4 : \
                      (PADS_TS1_CONFIG == SERIAL_IN) ? (BIT4|BIT3) : 0)
        _RVM1(0x1EAF, TS1_CONFIG, BITMASK(5:3)),
#endif

#if (PADS_TS2_CONFIG != Unknown_pad_mux)
#define TS2_CONFIG   ((PADS_TS2_CONFIG == PAD_TS2_D0) ? BIT6 : \
                      (PADS_TS2_CONFIG == PAD_TS2_VLD) ? BIT6 : \
                      (PADS_TS2_CONFIG == PAD_TS2_CLK) ? BIT6 : \
                      (PADS_TS2_CONFIG == PAD_TS2_SYNC) ? BIT6 : 0)
        _RVM1(0x1EAF, TS2_CONFIG, BIT6),
#endif

#if (PADS_TS_OUT != Unknown_pad_mux)
#define TS_OUT_MODE   ((PADS_TS_OUT == ENABLE) ? BIT3: 0)
    _RVM1(0x1EDC, TS_OUT_MODE, BIT3),
#endif


#if (PADS_NAND_MODE != Unknown_pad_mux)
#define NAND_MODE   ((PADS_NAND_MODE == PCM_A) ? BIT6: \
                     (PADS_NAND_MODE == TS2_PADs) ? BIT7 : 0)
        _RVM1(0x1EDE, NAND_MODE, BITMASK(7:6)),
#else
        _RVM1(0x1EDE, 0, BITMASK(7:6)),
#endif

#if (PADS_PCM1_PE != Unknown_pad_mux)
#if (PADS_PCM1_PE == PCM_PE_ON)
        _RVM1(0x1E12, 0xFF, 0xFF),
        _RVM1(0x1E13, 0xFF, 0xFF),
        _RVM1(0x1E14, 0xFF, 0xFF),
        _RVM1(0x1E15, 0xFF, 0xFF),
        _RVM1(0x1E16, 0x03, 0x03),
#else
        _RVM1(0x1E12, 0x00, 0xFF),
        _RVM1(0x1E13, 0x00, 0xFF),
        _RVM1(0x1E14, 0x00, 0xFF),
        _RVM1(0x1E15, 0x00, 0xFF),
        _RVM1(0x1E16, 0x00, 0x03),
#endif
#endif

#if (PADS_PCM1_CTRL != Unknown_pad_mux)
#define PCM1_CTRL   ((PADS_PCM1_CTRL == PAD_PCM_CE_N) ? BIT5 : 0)
        _RVM1(0x1EC8, PCM1_CTRL, BIT5),
#endif

#if (PADS_PCM1_AD != Unknown_pad_mux)
#define PCM1_AD   ((PADS_PCM1_AD == PAD_PCM_D7) ? BIT4 : 0)
        _RVM1(0x1EC8, PCM1_AD, BIT4),
#endif

#if (PADS_CI_CTRL != Unknown_pad_mux)
#define CI_CTRL   ((PADS_CI_CTRL == PAD_PCM_IORD_N) ? BIT1 : 0)
        _RVM1(0x1EC8, CI_CTRL, BIT1),
#endif

#if (PADS_CI_AD != Unknown_pad_mux)
#define CI_AD   ((PADS_CI_AD == PAD_PCM_D4) ? BIT0 : 0)
        _RVM1(0x1EC8, CI_AD, BIT0),
#endif

#if (PADS_PCM2_CTRL != Unknown_pad_mux)
#define PCM2_CTRL   ((PADS_PCM2_CTRL == PAD_PCM2_CD_N) ? BIT3 : 0)
        _RVM1(0x1EC8, PCM2_CTRL, BIT3),
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
#define I2S_IN    ((PADS_I2S_IN == PAD_I2S_IN_WS) ? BIT2 : 0)
        _RVM1(0x1EAE, I2S_IN, BIT2),
#endif

#if (PADS_I2S_MUTE != Unknown_pad_mux)
#define I2S_MUTE   ((PADS_I2S_MUTE == PAD_GPIO15) ? BIT6 : \
                    (PADS_I2S_MUTE == PAD_PWM4) ? BIT7 : 0)
        _RVM1(0x1E05, I2S_MUTE, BIT7|BIT6),
#endif

#if (PADS_I2S_OUT != Unknown_pad_mux)
#define I2S_OUT   ((PADS_I2S_OUT == ENABLE) ? BIT4 : 0)
        _RVM1(0x1EAE, I2S_OUT, BIT4),
#endif

#if (PADS_I2S_OUT_SD != Unknown_pad_mux)
#define I2S_OUT_SD   ((PADS_I2S_OUT_SD == ENABLE) ? BIT5 : 0)
        _RVM1(0x1EAE, I2S_OUT_SD, BIT5),
#endif

#if (PADS_I2S_OUT_SD1 != Unknown_pad_mux)
#define I2S_OUT_SD1   ((PADS_I2S_OUT_SD1 == ENABLE) ? BIT3 : 0)
        _RVM1(0x1EB3, I2S_OUT_SD1, BIT3),
#endif

#if (PADS_I2S_OUT_SD2 != Unknown_pad_mux)
#define I2S_OUT_SD2   ((PADS_I2S_OUT_SD2 == ENABLE) ? BIT4 : 0)
        _RVM1(0x1EB3, I2S_OUT_SD2, BIT4),
#endif

#if (PADS_I2S_OUT_SD3 != Unknown_pad_mux)
#define I2S_OUT_SD3   ((PADS_I2S_OUT_SD3 == ENABLE) ? BIT5 : 0)
        _RVM1(0x1EB3, I2S_OUT_SD3, BIT5),
#endif

// LED
     _RVM1(0x1EB4, BIT4, BIT4),

#if (PADS_ET_MODE != Unknown_pad_mux)
#define ET_MODE   ((PADS_ET_MODE == PAD_GPIO24) ? BIT0 : 0)
        _RVM1(0x1EDF, ET_MODE, BIT0),
#endif

    // UART
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
                      (PADS_UART3_MODE == PAD_GPIO21) ? BIT3|BIT2: \
                      (PADS_UART3_MODE == PAD_GPIO22) ? BIT3|BIT2: 0 )
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

    // UART_SEL
    #define UART_INV    ((UART0_INV ? BIT0 : 0) | \
                         (UART1_INV ? BIT1 : 0) | \
                         (UART2_INV ? BIT2 : 0) | \
                         (UART3_INV ? BIT3 : 0) | \
                         (UART4_INV ? BIT4 : 0))

        _RVM1(0x1EAB, UART_INV, BITMASK(4:0)),
        _RVM1(0x1EA6, (UART1_SRC_SEL << 4) | (UART0_SRC_SEL << 0), BITMASK(7:0)),
        _RVM1(0x1EA7, (UART3_SRC_SEL << 4) | (UART2_SRC_SEL << 0), BITMASK(7:0)),
        _RVM1(0x1EA8, (UART4_SRC_SEL << 0), BITMASK(3:0)),

        _MEMMAP_PM_,

        _RVM1(0x0E13, BIT3, BIT3),   // RX0_ENABLE
        _RVM1(0x0E13, 0 , BIT4),   // UART0 -> reg_uart_sel0

        _MEMMAP_nonPM_,

#if (PADS_PWM0_MODE != Unknown_pad_mux)
#define PWM0_MODE   ((PADS_PWM0_MODE == PAD_PWM0) ? BIT2:  0)
            _RVM1(0x1EC8, PWM0_MODE, BIT2),
#endif

#if (PADS_PWM1_MODE != Unknown_pad_mux)
#define PWM1_MODE   ((PADS_PWM1_MODE == PAD_PWM1) ? BIT6:  0)
            _RVM1(0x1EC8, PWM1_MODE, BIT6),
#endif

#if (PADS_PWM2_MODE != Unknown_pad_mux)
#define PWM2_MODE   ((PADS_PWM2_MODE == PAD_PWM2) ? BIT7:  0)
            _RVM1(0x1EC8, PWM2_MODE, BIT7),

#endif

#if (PADS_PWM3_MODE != Unknown_pad_mux)
#define PWM3_MODE   ((PADS_PWM3_MODE == PAD_PWM3) ? BIT4:  0)
            _RVM1(0x1EC9, PWM3_MODE, BIT4),
#endif

#if (PADS_PWM4_MODE != Unknown_pad_mux)
#define PWM4_MODE   ((PADS_PWM4_MODE == PAD_PWM4) ? BIT5:  0)
            _RVM1(0x1EC9, PWM4_MODE, BIT5),
#endif

#if (PADS_NAND_CS1_EN != Unknown_pad_mux)
#define NAND_CS1_EN   ((PADS_NAND_CS1_EN == PAD_NAND_CEZ1) ? BIT5:  0)
        _RVM1(0x1EDE, NAND_CS1_EN, BIT5),
#endif

#if (PADS_DDCR_MODE != Unknown_pad_mux)
#define DDCR_MODE   ((PADS_DDCR_MODE == DDCR_PADs) ? BIT0:  \
                     (PADS_DDCR_MODE == IIC_PADs) ? BIT1:  0)
        _RVM1(0x1EAE, DDCR_MODE, BIT1|BIT0),
#endif

#if (PADS_MIIC_MODE != Unknown_pad_mux)
#define MIIC_MODE   ((PADS_MIIC_MODE == PAD_GPIO18) ? BIT0:  \
                     (PADS_MIIC_MODE == PAD_GPIO17) ? BIT0:  \
                     (PADS_MIIC_MODE == PAD_TGPIO2) ? BIT1:  \
                     (PADS_MIIC_MODE == PAD_TGPIO3) ? BIT1:  \
                     (PADS_MIIC_MODE == PAD_I2S_IN_BCK) ? BIT2:  \
                     (PADS_MIIC_MODE == PAD_I2S_IN_SD) ? BIT2: 0)
        _RVM1(0x1EDC, MIIC_MODE, BIT2|BIT1|BIT0),
#endif

#if (PADS_SM_MODE != Unknown_pad_mux)
#define SM_MODE   ((PADS_SM_MODE == SMART_CARD_PCM) ? BIT4:  \
                   (PADS_SM_MODE == SMART_CARD_TS1) ? BIT5: 0)
        _RVM1(0x1EDC, SM_MODE, BIT5|BIT4),
#if (PADS_SM_MODE == SMART_CARD_PCM)
		_RVM1(0x1EC8, 0, BIT5|BIT1),
		_RVM1(0x1E13, BIT3, BIT3),
#endif
#endif
/*
#if (SMART_SOURCE == SMART_CARD_VCC_3P3V)
     _RVM1(0x1E24, 0, BIT2|BIT1|BIT0),
     _RVM1(0x1EAF, 0, BIT5|BIT4|BIT3),
     _RVM1(0x2BB6, 0,BIT0),
#endif

#if (SMART_SOURCE == SMART_CARD_VCC_5V)
#if (PADS_SM_MODE == SMART_CARD_PCM)
     _RVM1(0x2BB6, 1, BIT0),
#endif
#if (PADS_SM_MODE == SMART_CARD_TS1)
     _RVM1(0x1E24, 0, BIT2|BIT1|BIT0),
     _RVM1(0x1EAF, 0, BIT5|BIT4|BIT3),
     _RVM1(0x2BB6, 1, BIT0),
#endif
#endif
*/
#if (PADS_SD_MODE != Unknown_pad_mux)
#define SD_MODE   ((PADS_SD_MODE == PAD_PCM_D4) ? BIT0:  \
				   (PADS_SD_MODE == PAD_TS2_D0) ? BIT1:  \
				   (PADS_SD_MODE == PAD_SPI1_DI) ? BIT1|BIT0: 0)
        _RVM1(0x1EB4, SD_MODE, BIT1|BIT0),
#endif

#if (PADS_EMMC_MODE != Unknown_pad_mux)
#define EMMC_MODE   ((PADS_EMMC_MODE == PAD_PCM_D0) ? BIT6:  \
					 (PADS_EMMC_MODE == PAD_NAND_RBZ) ? (BIT6|BIT7):  0)
        _RVM1(0x1EDC, EMMC_MODE, BIT6|BIT7),
#endif

    _MEMMAP_nonPM_,

    // Clear all pad in
    _RVM1(0x1EA1, 0, BIT7),
    _END_OF_TBL_,

//---------------------------------------------------------------------
// ISP_TOOL Write Protect
//---------------------------------------------------------------------

    //external flash #1 //Alex tung
    _MEMMAP_PM_,
    _RVM1(0x0E6A, 0x00, BIT0), //reg_spi_gpio set to 0 (swtch to spi_do, spi_di, spi_ck)
    _RVM1(0x0E6A, 0x00, BIT1), //reg_spicsz0_gpio set to 0 (enable spi_cz0)
    _RVM1(0x08F4, 0x00, 0xFF), //reg_chip_select set to 0 (select externel SPI Flash #1)
    #if (PIN_FLASH_WP0)
      #if (MS_BOARD_TYPE_SEL == BD_MST181A_D01A_S)
      // PM13
      _RVM1(0x0F1A, BIT1, BIT1),//output high
      _RVM1(0x0F1A,    0, BIT0),//output enable
      #elif (MS_BOARD_TYPE_SEL == BD_MST181B_D01A_S)
      // PM0
      _RVM1(0x0F00, BIT1, BIT1),//output high
      _RVM1(0x0F00,    0, BIT0),//output enable
      #elif (MS_BOARD_TYPE_SEL == BD_MST181C_D01A_S)
      //PM3
      _RVM1(0x0F06, BIT1, BIT1),//output high
      _RVM1(0x0F06,    0, BIT0),//output enable
      #elif (MS_BOARD_TYPE_SEL == BD_MST181D_D01A_S)
      // PM0
      _RVM1(0x0F00, BIT1, BIT1),//output high
      _RVM1(0x0F00,    0, BIT0),//output enable
      #elif (MS_BOARD_TYPE_SEL == BD_MST051B_10ANV)
      // PM0
      _RVM1(0x0F00, BIT1, BIT1),//output high
      _RVM1(0x0F00,    0, BIT0),//output enable
      #elif (MS_BOARD_TYPE_SEL == BD_MST181B_D01A_S_CASHMERE)
      // PM0
      _RVM1(0x0F00, BIT1, BIT1),//output high
      _RVM1(0x0F00,    0, BIT0),//output enable
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
      #if (MS_BOARD_TYPE_SEL == BD_MST181A_D01A_S)
      //PM3
      _RVM1(0x0F06, BIT1, BIT1),//output high
      _RVM1(0x0F06,    0, BIT0),//output enable
      #elif (MS_BOARD_TYPE_SEL == BD_MST181C_D01A_S)
      // PM13
      _RVM1(0x0F1A, BIT1, BIT1),//output high
      _RVM1(0x0F1A,    0, BIT0),//output enable
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


