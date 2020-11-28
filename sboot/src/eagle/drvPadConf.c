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
// Copyright (c) 2006-2012 MStar Semiconductor, Inc.
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
#include "hwreg_EAGLE.h"
#include "chip/bond.h"

#define GPIO_NONE                   0       // Not GPIO pin (default)
#define GPIO_IN                     1       // GPI
#define GPIO_OUT_LOW                2       // GPO output low
#define GPIO_OUT_HIGH               3       // GPO output high

#if defined (MIPS_CHAKRA) || defined(MSOS_TYPE_LINUX)
#define _MapBase_nonPM_EAGLE        (RIU_MAP + 0x200000)
#define _MapBase_PM_EAGLE           RIU_MAP
#else
#define _MapBase_nonPM_EAGLE        0xA0200000
#define _MapBase_PM_EAGLE           0xA0000000
#endif

#define _MEMMAP_nonPM_              _RVM1(0x0000, 0x10, 0xFF)
#define _MEMMAP_PM_                 _RVM1(0x0000, 0x00, 0xFF)

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
    _RVM1(0x0e6a, BIT1, BIT1),   //reg[0e6a]#1 = 1
    //default is GPIO
    #endif

    #if(PAD_PM_SPI_CK_IS_GPIO != GPIO_NONE)
    #define PAD_PM_SPI_CK_OEN (PAD_PM_SPI_CK_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_PM_SPI_CK_OUT (PAD_PM_SPI_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x0e3a, PAD_PM_SPI_CK_OUT, BIT5),
    _RVM1(0x0e3c, PAD_PM_SPI_CK_OEN, BIT5),
    //reg_spi_gpio
    _RVM1(0x0e6a, BIT0, BIT0),   //reg[0e6a]#0 = 1
    //default is GPIO
    #endif

    #if(PAD_PM_SPI_DI_IS_GPIO != GPIO_NONE)
    #define PAD_PM_SPI_DI_OEN (PAD_PM_SPI_DI_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_PM_SPI_DI_OUT (PAD_PM_SPI_DI_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x0e3a, PAD_PM_SPI_DI_OUT, BIT6),
    _RVM1(0x0e3c, PAD_PM_SPI_DI_OEN, BIT6),
    //reg_spi_gpio
    _RVM1(0x0e6a, BIT0, BIT0),   //reg[0e6a]#0 = 1
    //default is GPIO
    #endif

    #if(PAD_PM_SPI_DO_IS_GPIO != GPIO_NONE)
    #define PAD_PM_SPI_DO_OEN (PAD_PM_SPI_DO_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_PM_SPI_DO_OUT (PAD_PM_SPI_DO_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x0e3a, PAD_PM_SPI_DO_OUT, BIT7),
    _RVM1(0x0e3c, PAD_PM_SPI_DO_OEN, BIT7),
    //reg_spi_gpio
    _RVM1(0x0e6a, BIT0, BIT0),   //reg[0e6a]#0 = 1
    //default is GPIO
    #endif

    #if(PAD_IRIN_IS_GPIO != GPIO_NONE)
    #define PAD_IRIN_OEN (PAD_IRIN_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_IRIN_OUT (PAD_IRIN_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x0e3a, PAD_IRIN_OUT, BIT0),
    _RVM1(0x0e3c, PAD_IRIN_OEN, BIT0),
    //reg_ir_is_gpio
    _RVM1(0x0e38, BIT4, BIT4),   //reg[0e38]#4 = 1
    //default is GPIO
    #endif

    #if(PAD_CEC_IS_GPIO != GPIO_NONE)
    #define PAD_CEC_OEN (PAD_CEC_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_CEC_OUT (PAD_CEC_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x0e3a, PAD_CEC_OUT, BIT2),
    _RVM1(0x0e3c, PAD_CEC_OEN, BIT2),
    //reg_cec_is_gpio
    _RVM1(0x0e38, BIT6, BIT6),   //reg[0e38]#6 = 1
    //default is GPIO
    #endif

    #if(PAD_AV_LNK_IS_GPIO != GPIO_NONE)
    #define PAD_AV_LNK_OEN (PAD_AV_LNK_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_AV_LNK_OUT (PAD_AV_LNK_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x0e3a, PAD_AV_LNK_OUT, BIT3),
    _RVM1(0x0e3c, PAD_AV_LNK_OEN, BIT3),
    //reg_av_lnk_is_gpio
    _RVM1(0x0e38, BIT7, BIT7 ),   //reg[0e38]#7 = 1
    #endif

    #if(PAD_PWM_PM_IS_GPIO != GPIO_NONE)
    #define PAD_PWM_PM_OEN (PAD_PWM_PM_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_PWM_PM_OUT (PAD_PWM_PM_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0e3a, PAD_PWM_PM_OUT, BIT1),
    _RVM1(0x0e3c, PAD_PWM_PM_OEN, BIT1),
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT4 ),   //reg[101e24]#4 = 0b
    //reg_pwm_pm_is_gpio
    _RVM1(0x0e38, BIT5, BIT5 ),   //reg[0e38]#5 = 1
    #endif

    #if(PAD_DDCA_CK_IS_GPIO != GPIO_NONE)
    #define PAD_DDCA_CK_OEN (PAD_DDCA_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_DDCA_CK_OUT (PAD_DDCA_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x0494, PAD_DDCA_CK_OUT, BIT2),
    _RVM1(0x0494, PAD_DDCA_CK_OEN, BIT1),
    //reg_gpio2a0_en
    _RVM1(0x0494, BIT7, BIT7 ),   //reg[0494]#7 = 1
    #endif

    #if(PAD_DDCA_DA_IS_GPIO != GPIO_NONE)
    #define PAD_DDCA_DA_OEN (PAD_DDCA_DA_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_DDCA_DA_OUT (PAD_DDCA_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x0494, PAD_DDCA_DA_OUT, BIT6),
    _RVM1(0x0494, PAD_DDCA_DA_OEN, BIT5),
    //reg_gpio2a0_en
    _RVM1(0x0494, BIT7, BIT7 ),   //reg[0494]#7 = 1
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
    //reg_uart_is_gpio[1]
    _RVM1(0x0e6b, 0, BIT1),   //reg[0e6b]#1 = 0
    //default is GPIO
    #endif

    #if(PAD_GPIO_PM2_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM2_OEN (PAD_GPIO_PM2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_GPIO_PM2_OUT (PAD_GPIO_PM2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x0e20, PAD_GPIO_PM2_OUT, BIT2),
    _RVM1(0x0e1e, PAD_GPIO_PM2_OEN, BIT2),
    //default is GPIO
    #endif

    #if(PAD_GPIO_PM3_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM3_OEN (PAD_GPIO_PM3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_GPIO_PM3_OUT (PAD_GPIO_PM3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x0e20, PAD_GPIO_PM3_OUT, BIT3),
    _RVM1(0x0e1e, PAD_GPIO_PM3_OEN, BIT3),
    //default is GPIO
    #endif

    #if(PAD_GPIO_PM4_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM4_OEN (PAD_GPIO_PM4_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_GPIO_PM4_OUT (PAD_GPIO_PM4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x0e20, PAD_GPIO_PM4_OUT, BIT4),
    _RVM1(0x0e1e, PAD_GPIO_PM4_OEN, BIT4),
    //reg_gpio_pm_lock
    _RVM1(0x0e24, 0xbe, 0xFFFF),   //reg[0e24] = 'hbe
    _RVM1(0x0e25, 0xba, 0xFFFF),   //reg[0e25] = 'hba
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
    _RVM1(0x0e6a, BIT2, BIT2),   //reg[0e6a]#2 = 1
    //default is GPIO
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
    //reg_uart_is_gpio[1]
    _RVM1(0x0e6b, 0, BIT0),   //reg[0e6b]#0 = 0
    //default is GPIO
    #endif

    #if(PAD_GPIO_PM9_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM9_OEN (PAD_GPIO_PM9_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_GPIO_PM9_OUT (PAD_GPIO_PM9_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0e21, PAD_GPIO_PM9_OUT, BIT1),
    _RVM1(0x0e1f, PAD_GPIO_PM9_OEN, BIT1),
    //default is GPIO
    #endif

    #if(PAD_GPIO_PM10_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM10_OEN (PAD_GPIO_PM10_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_GPIO_PM10_OUT (PAD_GPIO_PM10_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x0e21, PAD_GPIO_PM10_OUT, BIT2),
    _RVM1(0x0e1f, PAD_GPIO_PM10_OEN, BIT2),
    //reg_spicsz2_gpio
    _RVM1(0x0e6a, 0, BIT3),   //reg[0e6a]#3=0
    //default is GPIO
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
    //default is GPIO
    #endif

    #if(PAD_HOTPLUGD_IS_GPIO != GPIO_NONE)
    #define PAD_HOTPLUGD_OEN (PAD_HOTPLUGD_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_HOTPLUGD_OUT (PAD_HOTPLUGD_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x0e4e, PAD_HOTPLUGD_OUT, BIT7),
    _RVM1(0x0e4e, PAD_HOTPLUGD_OEN, BIT3),
    //default is GPIO
    #endif

    #if(PAD_DDCDA_CK_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDA_CK_OEN (PAD_DDCDA_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_DDCDA_CK_OUT (PAD_DDCDA_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x0496, PAD_DDCDA_CK_OUT, BIT2),
    _RVM1(0x0496, PAD_DDCDA_CK_OEN, BIT1),
    //reg_gpio2do_en
    _RVM1(0x0496, BIT7, BIT7),   //reg[0496]#7 = 1
    //default is GPIO
    #endif

    #if(PAD_DDCDA_DA_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDA_DA_OEN (PAD_DDCDA_DA_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_DDCDA_DA_OUT (PAD_DDCDA_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x0496, PAD_DDCDA_DA_OUT, BIT6),
    _RVM1(0x0496, PAD_DDCDA_DA_OEN, BIT5),
    //reg_gpio2do_en
    _RVM1(0x0496, BIT7, BIT7),   //reg[0496]#7 = 1
    //default is GPIO
    #endif

    #if(PAD_DDCDB_CK_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDB_CK_OEN (PAD_DDCDB_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_DDCDB_CK_OUT (PAD_DDCDB_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x0497, PAD_DDCDB_CK_OUT, BIT2),
    _RVM1(0x0497, PAD_DDCDB_CK_OEN, BIT1),
    //reg_gpio2d1_en
    _RVM1(0x0497, BIT7, BIT7),   //reg[0497]#7 = 1
    //default is GPIO
    #endif

    #if(PAD_DDCDB_DA_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDB_DA_OEN (PAD_DDCDB_DA_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_DDCDB_DA_OUT (PAD_DDCDB_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x0497, PAD_DDCDB_DA_OUT, BIT6),
    _RVM1(0x0497, PAD_DDCDB_DA_OEN, BIT5),
    //reg_gpio2d1_en
    _RVM1(0x0497, BIT7, BIT7),   //reg[0497]#7 = 1
    //default is GPIO
    #endif

    #if(PAD_DDCDC_CK_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDC_CK_OEN (PAD_DDCDC_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_DDCDC_CK_OUT (PAD_DDCDC_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x0498, PAD_DDCDC_CK_OUT, BIT2),
    _RVM1(0x0498, PAD_DDCDC_CK_OEN, BIT1),
    //reg_gpio2d2_en
    _RVM1(0x0498, BIT7, BIT7),   //reg[0498]#7 = 1
    //default is GPIO
    #endif

    #if(PAD_DDCDC_DA_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDC_DA_OEN (PAD_DDCDC_DA_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_DDCDC_DA_OUT (PAD_DDCDC_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x0498, PAD_DDCDC_DA_OUT, BIT6),
    _RVM1(0x0498, PAD_DDCDC_DA_OEN, BIT5),
    //reg_gpio2d2_en
    _RVM1(0x0498, BIT7, BIT7),   //reg[0498]#7 = 1
    //default is GPIO
    #endif

    #if(PAD_DDCDD_CK_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDD_CK_OEN (PAD_DDCDD_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_DDCDD_CK_OUT (PAD_DDCDD_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x0499, PAD_DDCDD_CK_OUT, BIT2),
    _RVM1(0x0499, PAD_DDCDD_CK_OEN, BIT1),
    //reg_gpio2d3_en
    _RVM1(0x0499, BIT7, BIT7),   //reg[0499]#7 = 1
    //default is GPIO
    #endif

    #if(PAD_DDCDD_DA_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDD_DA_OEN (PAD_DDCDD_DA_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_DDCDD_DA_OUT (PAD_DDCDD_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x0499, PAD_DDCDD_DA_OUT, BIT6),
    _RVM1(0x0499, PAD_DDCDD_DA_OEN, BIT5),
    //reg_gpio2d3_en
    _RVM1(0x0499, BIT7, BIT7),   //reg[0499]#7 = 1
    //default is GPIO
    #endif

    #if(PAD_SAR0_IS_GPIO != GPIO_NONE)
    #define PAD_SAR0_OEN (PAD_SAR0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_SAR0_OUT (PAD_SAR0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1424, PAD_SAR0_OUT, BIT0),
    _RVM1(0x1423, PAD_SAR0_OEN, BIT0),
    //reg_sar_aisel[0]
    _RVM1(0x1422, 0, BIT0),   //reg[1422]#0=0
    #endif

    #if(PAD_SAR1_IS_GPIO != GPIO_NONE)
    #define PAD_SAR1_OEN (PAD_SAR1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_SAR1_OUT (PAD_SAR1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1424, PAD_SAR1_OUT, BIT1),
    _RVM1(0x1423, PAD_SAR1_OEN, BIT1),
    //reg_sar_aisel[1]
    _RVM1(0x1422, 0, BIT1),   //reg[1422]#1=0
    #endif

    #if(PAD_SAR2_IS_GPIO != GPIO_NONE)
    #define PAD_SAR2_OEN (PAD_SAR2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_SAR2_OUT (PAD_SAR2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1424, PAD_SAR2_OUT, BIT2),
    _RVM1(0x1423, PAD_SAR2_OEN, BIT2),
    //reg_sar_aisel[2]
    _RVM1(0x1422, 0, BIT2),   //reg[1422]#2=0
    #endif

    #if(PAD_SAR3_IS_GPIO != GPIO_NONE)
    #define PAD_SAR3_OEN (PAD_SAR3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_SAR3_OUT (PAD_SAR3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1424, PAD_SAR3_OUT, BIT3),
    _RVM1(0x1423, PAD_SAR3_OEN, BIT3),
    //reg_sar_aisel[3]
    _RVM1(0x1422, 0, BIT3),   //reg[1422]#3=0
    #endif

    #if(PAD_SAR4_IS_GPIO != GPIO_NONE)
    #define PAD_SAR4_OEN (PAD_SAR4_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_SAR4_OUT (PAD_SAR4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1424, PAD_SAR4_OUT, BIT4),
    _RVM1(0x1423, PAD_SAR4_OEN, BIT4),
    //reg_sar_aisel[4]
    _RVM1(0x1422, 0, BIT4),   //reg[1422]#4=0
    #endif

    _MEMMAP_nonPM_,

    #if(PAD_DDCR_DA_IS_GPIO != GPIO_NONE)
    #define PAD_DDCR_DA_OEN (PAD_DDCR_DA_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_DDCR_DA_OUT (PAD_DDCR_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e9a, PAD_DDCR_DA_OUT, BIT2),
    _RVM1(0x1e9a, PAD_DDCR_DA_OEN, BIT0),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_ddcrmode
    _RVM1(0x1eae, 0, BIT1 | BIT0),   //reg[101eae]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_DDCR_CK_IS_GPIO != GPIO_NONE)
    #define PAD_DDCR_CK_OEN (PAD_DDCR_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_DDCR_CK_OUT (PAD_DDCR_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e9a, PAD_DDCR_CK_OUT, BIT3),
    _RVM1(0x1e9a, PAD_DDCR_CK_OEN, BIT1),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_ddcrmode
    _RVM1(0x1eae, 0, BIT1 | BIT0),   //reg[101eae]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO0_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO0_OEN (PAD_GPIO0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO0_OUT (PAD_GPIO0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e56, PAD_GPIO0_OUT, BIT0),
    _RVM1(0x1e5c, PAD_GPIO0_OEN, BIT0),
    //reg_ej_config
    //_RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4=0
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_usbdrvvbusconfig
    _RVM1(0x1e04, 0, BIT1 | BIT0),   //reg[101e04]#1 ~ #0=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_p1_enable_b0
    _RVM1(0x1eb8, 0, BIT0),   //reg[101eb8]#0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO1_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO1_OEN (PAD_GPIO1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_GPIO1_OUT (PAD_GPIO1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e56, PAD_GPIO1_OUT, BIT1),
    _RVM1(0x1e5c, PAD_GPIO1_OEN, BIT1),
    //reg_ej_config
    //_RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4=0
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_usbdrvvbusconfig
    _RVM1(0x1e04, 0, BIT1 | BIT0),   //reg[101e04]#1 ~ #0=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_p1_enable_b1
    _RVM1(0x1eb8, 0, BIT1),   //reg[101eb8]#1=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO2_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO2_OEN (PAD_GPIO2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_GPIO2_OUT (PAD_GPIO2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e56, PAD_GPIO2_OUT, BIT2),
    _RVM1(0x1e5c, PAD_GPIO2_OEN, BIT2),
    //reg_ej_config
    //_RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4=0
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_p1_enable_b2
    _RVM1(0x1eb8, 0, BIT2),   //reg[101eb8]#2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO3_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO3_OEN (PAD_GPIO3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_GPIO3_OUT (PAD_GPIO3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e56, PAD_GPIO3_OUT, BIT3),
    _RVM1(0x1e5c, PAD_GPIO3_OEN, BIT3),
    //reg_ej_config
    //_RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4=0
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_seconduartmode
    _RVM1(0x1e05, 0, BIT1 | BIT0),   //reg[101e05]#1 ~ #0=0
    //reg_od2nduart
    _RVM1(0x1eb6, 0, BIT1 | BIT0),   //reg[101eb6]#1 ~ #0=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_p1_enable_b3
    _RVM1(0x1eb8, 0, BIT3),   //reg[101eb8]#3=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO4_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO4_OEN (PAD_GPIO4_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_GPIO4_OUT (PAD_GPIO4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e56, PAD_GPIO4_OUT, BIT4),
    _RVM1(0x1e5c, PAD_GPIO4_OEN, BIT4),
    //reg_ej_config
    //_RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4=0
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_seconduartmode
    _RVM1(0x1e05, 0, BIT1 | BIT0),   //reg[101e05]#1 ~ #0=0
    //reg_od2nduart
    _RVM1(0x1eb6, 0, BIT1 | BIT0),   //reg[101eb6]#1 ~ #0=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_p1_enable_b4
    _RVM1(0x1eb8, 0, BIT4),   //reg[101eb8]#4=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO5_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO5_OEN (PAD_GPIO5_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_GPIO5_OUT (PAD_GPIO5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e56, PAD_GPIO5_OUT, BIT5),
    _RVM1(0x1e5c, PAD_GPIO5_OEN, BIT5),
    //reg_ej_config
    //_RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4=0
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_fastuartmode
    _RVM1(0x1e04, 0, BIT5 | BIT4),   //reg[101e04]#5 ~ #4=0
    //reg_odfastuart
    _RVM1(0x1eb6, 0, BIT7 | BIT6),   //reg[101eb6]#7 ~ #6=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_p1_enable_b5
    _RVM1(0x1eb8, 0, BIT5),   //reg[101eb8]#5=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO6_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO6_OEN (PAD_GPIO6_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_GPIO6_OUT (PAD_GPIO6_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e56, PAD_GPIO6_OUT, BIT6),
    _RVM1(0x1e5c, PAD_GPIO6_OEN, BIT6),
    //reg_ej_config
    //_RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4=0
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_fastuartmode
    _RVM1(0x1e04, 0, BIT5 | BIT4),   //reg[101e04]#5 ~ #4=0
    //reg_odfastuart
    _RVM1(0x1eb6, 0, BIT7 | BIT6),   //reg[101eb6]#7 ~ #6=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_p1_enable_b6
    _RVM1(0x1eb8, 0, BIT6),   //reg[101eb8]#6=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO7_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO7_OEN (PAD_GPIO7_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_GPIO7_OUT (PAD_GPIO7_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e56, PAD_GPIO7_OUT, BIT7),
    _RVM1(0x1e5c, PAD_GPIO7_OEN, BIT7),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_seconduartmode
    _RVM1(0x1e05, 0, BIT1 | BIT0),   //reg[101e05]#1 ~ #0=0
    //reg_od2nduart
    _RVM1(0x1eb6, 0, BIT1 | BIT0),   //reg[101eb6]#1 ~ #0=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_p1_enable_b7
    _RVM1(0x1eb8, 0, BIT7),   //reg[101eb8]#7=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO8_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO8_OEN (PAD_GPIO8_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO8_OUT (PAD_GPIO8_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e57, PAD_GPIO8_OUT, BIT0),
    _RVM1(0x1e5d, PAD_GPIO8_OEN, BIT0),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_seconduartmode
    _RVM1(0x1e05, 0, BIT1 | BIT0),   //reg[101e05]#1 ~ #0=0
    //reg_od2nduart
    _RVM1(0x1eb6, 0, BIT1 | BIT0),   //reg[101eb6]#1 ~ #0=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_pdtracectrl
    _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO9_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO9_OEN (PAD_GPIO9_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_GPIO9_OUT (PAD_GPIO9_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e57, PAD_GPIO9_OUT, BIT1),
    _RVM1(0x1e5d, PAD_GPIO9_OEN, BIT1),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_thirduartmode
    _RVM1(0x1e05, 0, BIT3 | BIT2),   //reg[101e05]#3 ~ #2=0
    //reg_od3rduart
    _RVM1(0x1eb6, 0, BIT3 | BIT2),   //reg[101eb6]#3 ~ #2=0
    //reg_pdtracectrl
    _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO10_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO10_OEN (PAD_GPIO10_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_GPIO10_OUT (PAD_GPIO10_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e57, PAD_GPIO10_OUT, BIT2),
    _RVM1(0x1e5d, PAD_GPIO10_OEN, BIT2),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_thirduartmode
    _RVM1(0x1e05, 0, BIT3 | BIT2),   //reg[101e05]#3 ~ #2=0
    //reg_od3rduart
    _RVM1(0x1eb6, 0, BIT3 | BIT2),   //reg[101eb6]#3 ~ #2=0
    //reg_pdtracectrl
    _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO11_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO11_OEN (PAD_GPIO11_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_GPIO11_OUT (PAD_GPIO11_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e57, PAD_GPIO11_OUT, BIT3),
    _RVM1(0x1e5d, PAD_GPIO11_OEN, BIT3),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_fourthuartmode
    _RVM1(0x1e04, 0, BIT7 | BIT6),   //reg[101e04]#7 ~ #6=0
    //reg_od4thuart
    _RVM1(0x1eb6, 0, BIT5 | BIT4),   //reg[101eb6]#5 ~ #4=0
    //reg_pdtracectrl
    _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO12_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO12_OEN (PAD_GPIO12_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_GPIO12_OUT (PAD_GPIO12_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e57, PAD_GPIO12_OUT, BIT4),
    _RVM1(0x1e5d, PAD_GPIO12_OEN, BIT4),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_mpif_mode
    _RVM1(0x1eb5, 0, BIT7 | BIT6),   //reg[101eb5]#7 ~ #6=0
    //reg_fourthuartmode
    _RVM1(0x1e04, 0, BIT7 | BIT6),   //reg[101e04]#7 ~ #6=0
    //reg_od4thuart
    _RVM1(0x1eb6, 0, BIT5 | BIT4),   //reg[101eb6]#5 ~ #4=0
    //reg_pdtracectrl
    _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO13_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO13_OEN (PAD_GPIO13_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_GPIO13_OUT (PAD_GPIO13_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e57, PAD_GPIO13_OUT, BIT5),
    _RVM1(0x1e5d, PAD_GPIO13_OEN, BIT5),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_mpif_mode
    _RVM1(0x1eb5, 0, BIT7 | BIT6),   //reg[101eb5]#7 ~ #6=0
    //reg_fastuartmode
    _RVM1(0x1e04, 0, BIT5 | BIT4),   //reg[101e04]#5 ~ #4=0
    //reg_odfastuart
    _RVM1(0x1eb6, 0, BIT7 | BIT6),   //reg[101eb6]#7 ~ #6=0
    //reg_pdtracectrl
    _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO14_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO14_OEN (PAD_GPIO14_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_GPIO14_OUT (PAD_GPIO14_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e57, PAD_GPIO14_OUT, BIT6),
    _RVM1(0x1e5d, PAD_GPIO14_OEN, BIT6),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_mpif_mode
    _RVM1(0x1eb5, 0, BIT7 | BIT6),   //reg[101eb5]#7 ~ #6=0
    //reg_fastuartmode
    _RVM1(0x1e04, 0, BIT5 | BIT4),   //reg[101e04]#5 ~ #4=0
    //reg_odfastuart
    _RVM1(0x1eb6, 0, BIT7 | BIT6),   //reg[101eb6]#7 ~ #6=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO15_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO15_OEN (PAD_GPIO15_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_GPIO15_OUT (PAD_GPIO15_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e57, PAD_GPIO15_OUT, BIT7),
    _RVM1(0x1e5d, PAD_GPIO15_OEN, BIT7),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_i2smutemode
    _RVM1(0x1e05, 0, BIT7 | BIT6),   //reg[101e05]#7 ~ #6=0
    //reg_mpif_mode
    _RVM1(0x1eb5, 0, BIT7 | BIT6),   //reg[101eb5]#7 ~ #6=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO16_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO16_OEN (PAD_GPIO16_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO16_OUT (PAD_GPIO16_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e58, PAD_GPIO16_OUT, BIT0),
    _RVM1(0x1e5e, PAD_GPIO16_OEN, BIT0),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_mpif_mode
    _RVM1(0x1eb5, 0, BIT7 | BIT6),   //reg[101eb5]#7 ~ #6=0
    //reg_3dflagconfig
    _RVM1(0x1eb1, 0, BIT7 | BIT6),   //reg[101eb1]#7 ~ #6=0
    //reg_tserrout
    _RVM1(0x1ea3, 0, BIT0),   //reg[101ea3]#0=0
    _RVM1(0x1ea2, 0, BIT7),   //reg[101ea2]#7=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO17_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO17_OEN (PAD_GPIO17_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_GPIO17_OUT (PAD_GPIO17_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e58, PAD_GPIO17_OUT, BIT1),
    _RVM1(0x1e5e, PAD_GPIO17_OEN, BIT1),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_mpif_mode
    _RVM1(0x1eb5, 0, BIT7 | BIT6),   //reg[101eb5]#7 ~ #6=0
    //reg_miic_mode0
    _RVM1(0x1eb5, 0, BIT1 | BIT0),   //reg[101eb5]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO18_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO18_OEN (PAD_GPIO18_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_GPIO18_OUT (PAD_GPIO18_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e58, PAD_GPIO18_OUT, BIT2),
    _RVM1(0x1e5e, PAD_GPIO18_OEN, BIT2),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_mpif_mode
    _RVM1(0x1eb5, 0, BIT7 | BIT6),   //reg[101eb5]#7 ~ #6=0
    //reg_miic_mode0
    _RVM1(0x1eb5, 0, BIT1 | BIT0),   //reg[101eb5]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO19_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO19_OEN (PAD_GPIO19_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_GPIO19_OUT (PAD_GPIO19_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e58, PAD_GPIO19_OUT, BIT3),
    _RVM1(0x1e5e, PAD_GPIO19_OEN, BIT3),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_et_mode
    //_RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0=0
    //reg_led_mode
    //_RVM1(0x1eb4, 0, BIT5 | BIT4),   //reg[101eb4]#5 ~ #4=0
    //reg_et_test_mode
    //_RVM1(0x1edf, 0, BIT3 | BIT2),   //reg[101edf]#3 ~ #2=0
    //reg_seconduartmode
    _RVM1(0x1e05, 0, BIT1 | BIT0),   //reg[101e05]#1 ~ #0=0
    //reg_od2nduart
    _RVM1(0x1eb6, 0, BIT1 | BIT0),   //reg[101eb6]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO20_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO20_OEN (PAD_GPIO20_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_GPIO20_OUT (PAD_GPIO20_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e58, PAD_GPIO20_OUT, BIT4),
    _RVM1(0x1e5e, PAD_GPIO20_OEN, BIT4),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_et_mode
    //_RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0=0
    //reg_led_mode
    //_RVM1(0x1eb4, 0, BIT5 | BIT4),   //reg[101eb4]#5 ~ #4=0
    //reg_et_test_mode
    //_RVM1(0x1edf, 0, BIT3 | BIT2),   //reg[101edf]#3 ~ #2=0
    //reg_seconduartmode
    _RVM1(0x1e05, 0, BIT1 | BIT0),   //reg[101e05]#1 ~ #0=0
    //reg_od2nduart
    _RVM1(0x1eb6, 0, BIT1 | BIT0),   //reg[101eb6]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO21_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO21_OEN (PAD_GPIO21_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_GPIO21_OUT (PAD_GPIO21_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e58, PAD_GPIO21_OUT, BIT5),
    _RVM1(0x1e5e, PAD_GPIO21_OEN, BIT5),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_et_mode
    //_RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0=0
    //reg_et_test_mode
    //_RVM1(0x1edf, 0, BIT3 | BIT2),   //reg[101edf]#3 ~ #2=0
    //reg_od3rduart
    _RVM1(0x1eb6, 0, BIT3 | BIT2),   //reg[101eb6]#3 ~ #2=0
    //reg_extint5
    _RVM1(0x1ee0, 0, BIT5),   //reg[101ee0]#5=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO22_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO22_OEN (PAD_GPIO22_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_GPIO22_OUT (PAD_GPIO22_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e58, PAD_GPIO22_OUT, BIT6),
    _RVM1(0x1e5e, PAD_GPIO22_OEN, BIT6),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_et_mode
    //_RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0=0
    //reg_et_test_mode
    //_RVM1(0x1edf, 0, BIT3 | BIT2),   //reg[101edf]#3 ~ #2=0
    //reg_od3rduart
    _RVM1(0x1eb6, 0, BIT3 | BIT2),   //reg[101eb6]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO23_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO23_OEN (PAD_GPIO23_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_GPIO23_OUT (PAD_GPIO23_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e58, PAD_GPIO23_OUT, BIT7),
    _RVM1(0x1e5e, PAD_GPIO23_OEN, BIT7),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_et_mode
    //_RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0=0
    //reg_et_test_mode
    //_RVM1(0x1edf, 0, BIT3 | BIT2),   //reg[101edf]#3 ~ #2=0
    //reg_fourthuartmode
    _RVM1(0x1e04, 0, BIT7 | BIT6),   //reg[101e04]#7 ~ #6=0
    //reg_od4thuart
    _RVM1(0x1eb6, 0, BIT5 | BIT4),   //reg[101eb6]#5 ~ #4=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO24_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO24_OEN (PAD_GPIO24_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO24_OUT (PAD_GPIO24_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e59, PAD_GPIO24_OUT, BIT0),
    _RVM1(0x1e5f, PAD_GPIO24_OEN, BIT0),
    //reg_et_mode
    //_RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0=0
    //reg_et_test_mode
    //_RVM1(0x1edf, 0, BIT3 | BIT2),   //reg[101edf]#3 ~ #2=0
    //reg_fourthuartmode
    _RVM1(0x1e04, 0, BIT7 | BIT6),   //reg[101e04]#7 ~ #6=0
    //reg_od4thuart
    _RVM1(0x1eb6, 0, BIT5 | BIT4),   //reg[101eb6]#5 ~ #4=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO25_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO25_OEN (PAD_GPIO25_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_GPIO25_OUT (PAD_GPIO25_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e59, PAD_GPIO25_OUT, BIT1),
    _RVM1(0x1e5f, PAD_GPIO25_OEN, BIT1),
    //reg_et_mode
    //_RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0=0
    //reg_et_test_mode
    //_RVM1(0x1edf, 0, BIT3 | BIT2),   //reg[101edf]#3 ~ #2=0
    //reg_fastuartmode
    _RVM1(0x1e04, 0, BIT5 | BIT4),   //reg[101e04]#5 ~ #4=0
    //reg_odfastuart
    _RVM1(0x1eb6, 0, BIT7 | BIT6),   //reg[101eb6]#7 ~ #6=0
    //reg_extint1
    _RVM1(0x1ee0, 0, BIT1),   //reg[101ee0]#1=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO26_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO26_OEN (PAD_GPIO26_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_GPIO26_OUT (PAD_GPIO26_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e59, PAD_GPIO26_OUT, BIT2),
    _RVM1(0x1e5f, PAD_GPIO26_OEN, BIT2),
    //reg_et_mode
    //_RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0=0
    //reg_led_mode
    //_RVM1(0x1eb4, 0, BIT5 | BIT4),   //reg[101eb4]#5 ~ #4=0
    //reg_et_test_mode
    //_RVM1(0x1edf, 0, BIT3 | BIT2),   //reg[101edf]#3 ~ #2=0
    //reg_usbdrvvbusconfig
    _RVM1(0x1e04, 0, BIT1 | BIT0),   //reg[101e04]#1 ~ #0=0
    //reg_fastuartmode
    _RVM1(0x1e04, 0, BIT5 | BIT4),   //reg[101e04]#5 ~ #4=0
    //reg_odfastuart
    _RVM1(0x1eb6, 0, BIT7 | BIT6),   //reg[101eb6]#7 ~ #6=0
    //reg_extint7
    _RVM1(0x1ee0, 0, BIT7),   //reg[101ee0]#7=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_GPIO27_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO27_OEN (PAD_GPIO27_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_GPIO27_OUT (PAD_GPIO27_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e59, PAD_GPIO27_OUT, BIT3),
    _RVM1(0x1e5f, PAD_GPIO27_OEN, BIT3),
    //reg_et_mode
    //_RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0=0
    //reg_led_mode
    //_RVM1(0x1eb4, 0, BIT5 | BIT4),   //reg[101eb4]#5 ~ #4=0
    //reg_et_test_mode
    //_RVM1(0x1edf, 0, BIT3 | BIT2),   //reg[101edf]#3 ~ #2=0
    //reg_usbdrvvbusconfig
    _RVM1(0x1e04, 0, BIT1 | BIT0),   //reg[101e04]#1 ~ #0=0
    //reg_extint4
    _RVM1(0x1ee0, 0, BIT4),   //reg[101ee0]#4=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_I2S_IN_WS_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_IN_WS_OEN (PAD_I2S_IN_WS_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_I2S_IN_WS_OUT (PAD_I2S_IN_WS_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e6c, PAD_I2S_IN_WS_OUT, BIT0),
    _RVM1(0x1e6e, PAD_I2S_IN_WS_OEN, BIT0),
    //CHIP_CONFIG = NoEJ
    //reg_ej_config
    //_RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_i2sinconfig
    _RVM1(0x1eae, 0, BIT2),   //reg[101eae]#2=0
    //reg_mcu_jtag_mode
    //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6=0
    //reg_dspejtagmode
    //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0=0
    //reg_thirduartmode
    _RVM1(0x1e05, 0, BIT3 | BIT2),   //reg[101e05]#3 ~ #2=0
    //reg_od3rduart
    _RVM1(0x1eb6, 0, BIT3 | BIT2),   //reg[101eb6]#3 ~ #2=0
    //reg_extint6
    _RVM1(0x1ee0, 0, BIT6),   //reg[101ee0]#6=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_I2S_IN_BCK_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_IN_BCK_OEN (PAD_I2S_IN_BCK_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_I2S_IN_BCK_OUT (PAD_I2S_IN_BCK_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e6c, PAD_I2S_IN_BCK_OUT, BIT1),
    _RVM1(0x1e6e, PAD_I2S_IN_BCK_OEN, BIT1),
    //CHIP_CONFIG = NoEJ
    //reg_ej_config
    //_RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_i2sinconfig
    _RVM1(0x1eae, 0, BIT2),   //reg[101eae]#2=0
    //reg_dspejtagmode
    //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0=0
    //reg_thirduartmode
    _RVM1(0x1e05, 0, BIT3 | BIT2),   //reg[101e05]#3 ~ #2=0
    //reg_od3rduart
    _RVM1(0x1eb6, 0, BIT3 | BIT2),   //reg[101eb6]#3 ~ #2=0
    //reg_miic_mode2
    _RVM1(0x1eb5, 0, BIT5 | BIT4),   //reg[101eb5]#5 ~ #4=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_I2S_IN_SD_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_IN_SD_OEN (PAD_I2S_IN_SD_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_I2S_IN_SD_OUT (PAD_I2S_IN_SD_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e6c, PAD_I2S_IN_SD_OUT, BIT2),
    _RVM1(0x1e6e, PAD_I2S_IN_SD_OEN, BIT2),
    //CHIP_CONFIG = NoEJ
    //reg_ej_config
    //_RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_i2sinconfig
    _RVM1(0x1eae, 0, BIT2),   //reg[101eae]#2=0
    //reg_3dflagconfig
    _RVM1(0x1eb1, 0, BIT7 | BIT6),   //reg[101eb1]#7 ~ #6=0
    //reg_dspejtagmode
    //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0=0
    //reg_tserrout
    _RVM1(0x1ea3, 0, BIT0),   //reg[101ea3]#0=0
    //_RVM1(0x1ea2, 0, BIT7),   //reg[101ea2]#7=0
    //reg_miic_mode2
    _RVM1(0x1eb5, 0, BIT5 | BIT4),   //reg[101eb5]#5 ~ #4=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_SPDIF_IN_IS_GPIO != GPIO_NONE)
    #define PAD_SPDIF_IN_OEN (PAD_SPDIF_IN_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_SPDIF_IN_OUT (PAD_SPDIF_IN_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e6c, PAD_SPDIF_IN_OUT, BIT3),
    _RVM1(0x1e6e, PAD_SPDIF_IN_OEN, BIT3),
    //CHIP_CONFIG = NoEJ
    //reg_ej_config
    //_RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4=0
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_spdifinconfig
    _RVM1(0x1eae, 0, BIT6),   //reg[101eae]#6=0
    //reg_3dflagconfig
    _RVM1(0x1eb1, 0, BIT7 | BIT6),   //reg[101eb1]#7 ~ #6=0
    //reg_dspejtagmode
    //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_SPDIF_OUT_IS_GPIO != GPIO_NONE)
    #define PAD_SPDIF_OUT_OEN (PAD_SPDIF_OUT_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_SPDIF_OUT_OUT (PAD_SPDIF_OUT_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e6c, PAD_SPDIF_OUT_OUT, BIT4),
    _RVM1(0x1e6e, PAD_SPDIF_OUT_OEN, BIT4),
    //CHIP_CONFIG = NoEJ
    //reg_ej_config
    //_RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4=0
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_spdifoutconfig
    _RVM1(0x1eae, 0, BIT7),   //reg[101eae]#7=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_I2S_OUT_WS_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_WS_OEN (PAD_I2S_OUT_WS_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_I2S_OUT_WS_OUT (PAD_I2S_OUT_WS_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e6c, PAD_I2S_OUT_WS_OUT, BIT5),
    _RVM1(0x1e6e, PAD_I2S_OUT_WS_OEN, BIT5),
    //CHIP_CONFIG = NoEJ
    //reg_ej_config
    //_RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4=0
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_i2soutconfig
    _RVM1(0x1eae, 0, BIT5 | BIT4),   //reg[101eae]#5 ~ #4=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_I2S_OUT_MCK_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_MCK_OEN (PAD_I2S_OUT_MCK_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_I2S_OUT_MCK_OUT (PAD_I2S_OUT_MCK_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e6c, PAD_I2S_OUT_MCK_OUT, BIT6),
    _RVM1(0x1e6e, PAD_I2S_OUT_MCK_OEN, BIT6),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_i2soutconfig
    _RVM1(0x1eae, 0, BIT5 | BIT4),   //reg[101eae]#5 ~ #4=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_I2S_OUT_BCK_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_BCK_OEN (PAD_I2S_OUT_BCK_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_I2S_OUT_BCK_OUT (PAD_I2S_OUT_BCK_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e6c, PAD_I2S_OUT_BCK_OUT, BIT7),
    _RVM1(0x1e6e, PAD_I2S_OUT_BCK_OEN, BIT7),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_i2soutconfig
    _RVM1(0x1eae, 0, BIT5 | BIT4),   //reg[101eae]#5 ~ #4=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_I2S_OUT_SD_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_SD_OEN (PAD_I2S_OUT_SD_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_I2S_OUT_SD_OUT (PAD_I2S_OUT_SD_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e6d, PAD_I2S_OUT_SD_OUT, BIT0),
    _RVM1(0x1e6f, PAD_I2S_OUT_SD_OEN, BIT0),
    //CHIP_CONFIG = NoEJ
    //reg_ej_config
    //_RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4=0
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_i2soutconfig
    _RVM1(0x1eae, 0, BIT5 | BIT4),   //reg[101eae]#5 ~ #4=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_I2S_OUT_SD1_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_SD1_OEN (PAD_I2S_OUT_SD1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_I2S_OUT_SD1_OUT (PAD_I2S_OUT_SD1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e6d, PAD_I2S_OUT_SD1_OUT, BIT1),
    _RVM1(0x1e6f, PAD_I2S_OUT_SD1_OEN, BIT1),
    //reg_i2soutconfig
    _RVM1(0x1eae, 0, BIT5 | BIT4),   //reg[101eae]#5 ~ #4=0
    //reg_mcu_jtag_mode
    //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6=0
    //reg_usbdrvvbusconfig
    _RVM1(0x1e04, 0, BIT1 | BIT0),   //reg[101e04]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_I2S_OUT_SD2_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_SD2_OEN (PAD_I2S_OUT_SD2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_I2S_OUT_SD2_OUT (PAD_I2S_OUT_SD2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e6d, PAD_I2S_OUT_SD2_OUT, BIT2),
    _RVM1(0x1e6f, PAD_I2S_OUT_SD2_OEN, BIT2),
    //reg_i2soutconfig
    _RVM1(0x1eae, 0, BIT5 | BIT4),   //reg[101eae]#5 ~ #4=0
    //reg_mcu_jtag_mode
    //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6=0
    //reg_usbdrvvbusconfig
    _RVM1(0x1e04, 0, BIT1 | BIT0),   //reg[101e04]#1 ~ #0=0
    //reg_fourthuartmode
    _RVM1(0x1e04, 0, BIT7 | BIT6),   //reg[101e04]#7 ~ #6=0
    //reg_od4thuart
    _RVM1(0x1eb6, 0, BIT5 | BIT4),   //reg[101eb6]#5 ~ #4=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_I2S_OUT_SD3_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_SD3_OEN (PAD_I2S_OUT_SD3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_I2S_OUT_SD3_OUT (PAD_I2S_OUT_SD3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e6d, PAD_I2S_OUT_SD3_OUT, BIT3),
    _RVM1(0x1e6f, PAD_I2S_OUT_SD3_OEN, BIT3),
    //reg_i2soutconfig
    _RVM1(0x1eae, 0, BIT5 | BIT4),   //reg[101eae]#5 ~ #4=0
    //reg_mcu_jtag_mode
    //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6=0
    //reg_fourthuartmode
    _RVM1(0x1e04, 0, BIT7 | BIT6),   //reg[101e04]#7 ~ #6=0
    //reg_od4thuart
    _RVM1(0x1eb6, 0, BIT5 | BIT4),   //reg[101eb6]#5 ~ #4=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_SPI1_CK_IS_GPIO != GPIO_NONE)
    #define PAD_SPI1_CK_OEN (PAD_SPI1_CK_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_SPI1_CK_OUT (PAD_SPI1_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e90, PAD_SPI1_CK_OUT, BIT4),
    _RVM1(0x1e90, PAD_SPI1_CK_OEN, BIT0),
    //reg_ld_spi1_config
    _RVM1(0x1eb4, 0, BIT0),   //reg[101eb4]#0=0
    //reg_ld_spi3_config
    _RVM1(0x1eb4, 0, BIT2),   //reg[101eb4]#2=0
    //reg_sd0_config2
    _RVM1(0x1e16, 0, BIT5 | BIT4),   //reg[101e16]#5 ~ #4=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_SPI1_DI_IS_GPIO != GPIO_NONE)
    #define PAD_SPI1_DI_OEN (PAD_SPI1_DI_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_SPI1_DI_OUT (PAD_SPI1_DI_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e90, PAD_SPI1_DI_OUT, BIT5),
    _RVM1(0x1e90, PAD_SPI1_DI_OEN, BIT1),
    //reg_ld_spi1_config
    _RVM1(0x1eb4, 0, BIT0),   //reg[101eb4]#0=0
    //reg_ld_spi3_config
    _RVM1(0x1eb4, 0, BIT2),   //reg[101eb4]#2=0
    //reg_sd0_config2
    _RVM1(0x1e16, 0, BIT5 | BIT4),   //reg[101e16]#5 ~ #4=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_SPI2_CK_IS_GPIO != GPIO_NONE)
    #define PAD_SPI2_CK_OEN (PAD_SPI2_CK_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_SPI2_CK_OUT (PAD_SPI2_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e90, PAD_SPI2_CK_OUT, BIT6),
    _RVM1(0x1e90, PAD_SPI2_CK_OEN, BIT2),
    //reg_ld_spi2_config
    _RVM1(0x1eb4, 0, BIT1),   //reg[101eb4]#1=0
    //reg_ld_spi3_config
    _RVM1(0x1eb4, 0, BIT2),   //reg[101eb4]#2=0
    //reg_sd1_config2
    _RVM1(0x1e17, 0, BIT1 | BIT0),   //reg[101e17]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_SPI2_DI_IS_GPIO != GPIO_NONE)
    #define PAD_SPI2_DI_OEN (PAD_SPI2_DI_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_SPI2_DI_OUT (PAD_SPI2_DI_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e90, PAD_SPI2_DI_OUT, BIT7),
    _RVM1(0x1e90, PAD_SPI2_DI_OEN, BIT3),
    //reg_chiptop_dummy_3[0]
    //_RVM1(0x1e3e, 0, BIT0),   //reg[101e3e]#0=0
    //reg_ld_spi2_config
    _RVM1(0x1eb4, 0, BIT1),   //reg[101eb4]#1=0
    //reg_ld_spi3_config
    _RVM1(0x1eb4, 0, BIT2),   //reg[101eb4]#2=0
    //reg_sd1_config2
    _RVM1(0x1e17, 0, BIT1 | BIT0),   //reg[101e17]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_VSYNC_LIKE_IS_GPIO != GPIO_NONE)
    #define PAD_VSYNC_LIKE_OEN (PAD_VSYNC_LIKE_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_VSYNC_LIKE_OUT (PAD_VSYNC_LIKE_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e91, PAD_VSYNC_LIKE_OUT, BIT5),
    _RVM1(0x1e91, PAD_VSYNC_LIKE_OEN, BIT4),
    //reg_ld_spi1cz_config
    _RVM1(0x1eb2, 0, BIT4 | BIT3),   //reg[101eb2]#4 ~ #3=0
    //reg_pwm5_mode
    _RVM1(0x1eb2, 0, BIT1 | BIT0),   //reg[101eb2]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_NAND_CEZ_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_CEZ_OEN (PAD_NAND_CEZ_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_NAND_CEZ_OUT (PAD_NAND_CEZ_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e8c, PAD_NAND_CEZ_OUT, BIT0),
    _RVM1(0x1e8e, PAD_NAND_CEZ_OEN, BIT0),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e86, BIT1, BIT1 ),   //reg[101e86] #1 = 1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_emmc_config
    _RVM1(0x1ebb, 0, BIT7 | BIT6),   //reg[101ebb]#7 ~ #6=0
    //CHIP_CONFIG is not equal to "BOOT_FROM_EMMC_M2"
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_NAND_CEZ1_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_CEZ1_OEN (PAD_NAND_CEZ1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_NAND_CEZ1_OUT (PAD_NAND_CEZ1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e8c, PAD_NAND_CEZ1_OUT, BIT1),
    _RVM1(0x1e8e, PAD_NAND_CEZ1_OEN, BIT1),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e86, BIT1, BIT1 ),   //reg[101e86] #1 = 1b
    //reg_nand_cs1_en
    _RVM1(0x1ea1, 0, BIT2),   //reg[101ea1]#2=0
    //reg_emmc_config
    _RVM1(0x1ebb, 0, BIT7 | BIT6),   //reg[101ebb]#7 ~ #6=0
    //CHIP_CONFIG is not equal to "BOOT_FROM_EMMC_M2"
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_NAND_CLE_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_CLE_OEN (PAD_NAND_CLE_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_NAND_CLE_OUT (PAD_NAND_CLE_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e8c, PAD_NAND_CLE_OUT, BIT2),
    _RVM1(0x1e8e, PAD_NAND_CLE_OEN, BIT2),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e86, BIT1, BIT1 ),   //reg[101e86] #1 = 1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_emmc_config
    _RVM1(0x1ebb, 0, BIT7 | BIT6),   //reg[101ebb]#7 ~ #6=0
    //CHIP_CONFIG is not equal to "BOOT_FROM_EMMC_M2"
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_NAND_REZ_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_REZ_OEN (PAD_NAND_REZ_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_NAND_REZ_OUT (PAD_NAND_REZ_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e8c, PAD_NAND_REZ_OUT, BIT3),
    _RVM1(0x1e8e, PAD_NAND_REZ_OEN, BIT3),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e86, BIT1, BIT1 ),   //reg[101e86] #1 = 1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_emmc_config
    _RVM1(0x1ebb, 0, BIT7 | BIT6),   //reg[101ebb]#7 ~ #6=0
    //CHIP_CONFIG is not equal to "BOOT_FROM_EMMC_M2"
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_NAND_WEZ_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_WEZ_OEN (PAD_NAND_WEZ_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_NAND_WEZ_OUT (PAD_NAND_WEZ_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e8c, PAD_NAND_WEZ_OUT, BIT4),
    _RVM1(0x1e8e, PAD_NAND_WEZ_OEN, BIT4),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e86, BIT1 , BIT1 ),   //reg[101e86] #1 = 1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_emmc_config
    _RVM1(0x1ebb, 0, BIT7 | BIT6),   //reg[101ebb]#7 ~ #6=0
    //CHIP_CONFIG is not equal to "BOOT_FROM_EMMC_M2"
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_NAND_WPZ_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_WPZ_OEN (PAD_NAND_WPZ_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_NAND_WPZ_OUT (PAD_NAND_WPZ_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e8c, PAD_NAND_WPZ_OUT, BIT5),
    _RVM1(0x1e8e, PAD_NAND_WPZ_OEN, BIT5),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_emmc_config
    _RVM1(0x1ebb, 0, BIT7 | BIT6),   //reg[101ebb]#7 ~ #6=0
    //CHIP_CONFIG is not equal to "BOOT_FROM_EMMC_M2"
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_NAND_ALE_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_ALE_OEN (PAD_NAND_ALE_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_NAND_ALE_OUT (PAD_NAND_ALE_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e8c, PAD_NAND_ALE_OUT, BIT6),
    _RVM1(0x1e8e, PAD_NAND_ALE_OEN, BIT6),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e86, BIT1, BIT1 ),   //reg[101e86] #1 = 1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_emmc_config
    _RVM1(0x1ebb, 0, BIT7 | BIT6),   //reg[101ebb]#7 ~ #6=0
    //CHIP_CONFIG is not equal to "BOOT_FROM_EMMC_M2"
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_NAND_RBZ_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_RBZ_OEN (PAD_NAND_RBZ_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_NAND_RBZ_OUT (PAD_NAND_RBZ_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e8c, PAD_NAND_RBZ_OUT, BIT7),
    _RVM1(0x1e8e, PAD_NAND_RBZ_OEN, BIT7),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_emmc_config
    _RVM1(0x1ebb, 0, BIT7 | BIT6),   //reg[101ebb]#7 ~ #6=0
    //CHIP_CONFIG is not equal to "BOOT_FROM_EMMC_M2"
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_NAND_DQS_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_DQS_OEN (PAD_NAND_DQS_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_NAND_DQS_OUT (PAD_NAND_DQS_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e8d, PAD_NAND_DQS_OUT, BIT0),
    _RVM1(0x1e8f, PAD_NAND_DQS_OEN, BIT0),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e86, BIT1, BIT1 ),   //reg[101e86] #1 = 1b
    //reg_ds_testen
    //_RVM1(0x1359, 0, BIT6 ),   //reg[111359] #6 = 0b
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_D3_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_D3_OEN (PAD_PCM_D3_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_PCM_D3_OUT (PAD_PCM_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e76, PAD_PCM_D3_OUT, BIT0),
    _RVM1(0x1e7c, PAD_PCM_D3_OEN, BIT0),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e86, BIT1, BIT1 ),   //reg[101e86] #1 = 1b
    //reg_pcm_d_pe[3]
    _RVM1(0x1e18, BIT3, BIT3),   //reg[101e18]#3=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_mcu_jtag_mode
    //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_emmc_config
    _RVM1(0x1ebb, 0, BIT7 | BIT6),   //reg[101ebb]#7 ~ #6=0
    //CHIP_CONFIG = BOOT_FROM_EMMC_M1
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_D4_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_D4_OEN (PAD_PCM_D4_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_PCM_D4_OUT (PAD_PCM_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e76, PAD_PCM_D4_OUT, BIT1),
    _RVM1(0x1e7c, PAD_PCM_D4_OEN, BIT1),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e86, BIT1, BIT1 ),   //reg[101e86] #1 = 1b
    //reg_pcm_d_pe[4]
    _RVM1(0x1e18, BIT4, BIT4),   //reg[101e18]#4=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_mcu_jtag_mode
    //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_sd0_config
    _RVM1(0x1e16, 0, BIT3 | BIT2),   //reg[101e16]#3 ~ #2=0
    //reg_sd1_config
    _RVM1(0x1e16, 0, BIT7 | BIT6),   //reg[101e16]#7 ~ #6=0
    //reg_sd0_config2
    _RVM1(0x1e16, 0, BIT5 | BIT4),   //reg[101e16]#5 ~ #4=0
    //reg_sd1_config2
    _RVM1(0x1e17, 0, BIT1 | BIT0),   //reg[101e17]#1 ~ #0=0
    //reg_emmc_config
    _RVM1(0x1ebb, 0, BIT7 | BIT6),   //reg[101ebb]#7 ~ #6=0
    //CHIP_CONFIG = BOOT_FROM_EMMC_M1
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_D5_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_D5_OEN (PAD_PCM_D5_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_PCM_D5_OUT (PAD_PCM_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e76, PAD_PCM_D5_OUT, BIT2),
    _RVM1(0x1e7c, PAD_PCM_D5_OEN, BIT2),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e86, BIT1 , BIT1 ),   //reg[101e86] #1 = 1b
    //reg_pcm_d_pe[5]
    _RVM1(0x1e18, BIT5, BIT5),   //reg[101e18]#5=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_mcu_jtag_mode
    _RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_sd0_config
    _RVM1(0x1e16, 0, BIT3 | BIT2),   //reg[101e16]#3 ~ #2=0
    //reg_sd1_config
    _RVM1(0x1e16, 0, BIT7 | BIT6),   //reg[101e16]#7 ~ #6=0
    //reg_sd0_config2
    _RVM1(0x1e16, 0, BIT5 | BIT4),   //reg[101e16]#5 ~ #4=0
    //reg_sd1_config2
    _RVM1(0x1e17, 0, BIT1 | BIT0),   //reg[101e17]#1 ~ #0=0
    //reg_emmc_config
    _RVM1(0x1ebb, 0, BIT7 | BIT6),   //reg[101ebb]#7 ~ #6=0
    //CHIP_CONFIG = BOOT_FROM_EMMC_M1
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_D6_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_D6_OEN (PAD_PCM_D6_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_PCM_D6_OUT (PAD_PCM_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e76, PAD_PCM_D6_OUT, BIT3),
    _RVM1(0x1e7c, PAD_PCM_D6_OEN, BIT3),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e86, BIT1, BIT1 ),   //reg[101e86] #1 = 1b
    //reg_pcm_d_pe[6]
    _RVM1(0x1e18, BIT6, BIT6),   //reg[101e18]#6=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_mcu_jtag_mode
    //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_sd0_config
    _RVM1(0x1e16, 0, BIT3 | BIT2),   //reg[101e16]#3 ~ #2=0
    //reg_sd1_config
    _RVM1(0x1e16, 0, BIT7 | BIT6),   //reg[101e16]#7 ~ #6=0
    //reg_sd0_config2
    _RVM1(0x1e16, 0, BIT5 | BIT4),   //reg[101e16]#5 ~ #4=0
    //reg_sd1_config2
    _RVM1(0x1e17, 0, BIT1 | BIT0),   //reg[101e17]#1 ~ #0=0
    //reg_emmc_config
    _RVM1(0x1ebb, 0, BIT7 | BIT6),   //reg[101ebb]#7 ~ #6=0
    //CHIP_CONFIG = BOOT_FROM_EMMC_M1
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_D7_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_D7_OEN (PAD_PCM_D7_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_PCM_D7_OUT (PAD_PCM_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e76, PAD_PCM_D7_OUT, BIT4),
    _RVM1(0x1e7c, PAD_PCM_D7_OEN, BIT4),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e86, BIT1, BIT1 ),   //reg[101e86] #1 = 1b
    //reg_pcm_d_pe[7]
    _RVM1(0x1e18, BIT7, BIT7),   //reg[101e18]#7=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_sd0_config
    _RVM1(0x1e16, 0, BIT3 | BIT2),   //reg[101e16]#3 ~ #2=0
    //reg_sd1_config
    _RVM1(0x1e16, 0, BIT7 | BIT6),   //reg[101e16]#7 ~ #6=0
    //reg_sd0_config2
    _RVM1(0x1e16, 0, BIT5 | BIT4),   //reg[101e16]#5 ~ #4=0
    //reg_sd1_config2
    _RVM1(0x1e17, 0, BIT1 | BIT0),   //reg[101e17]#1 ~ #0=0
    //reg_emmc_config
    _RVM1(0x1ebb, 0, BIT7 | BIT6),   //reg[101ebb]#7 ~ #6=0
    //CHIP_CONFIG = BOOT_FROM_EMMC_M1
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_CE_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_CE_N_OEN (PAD_PCM_CE_N_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_PCM_CE_N_OUT (PAD_PCM_CE_N_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e76, PAD_PCM_CE_N_OUT, BIT5),
    _RVM1(0x1e7c, PAD_PCM_CE_N_OEN, BIT5),
    //reg_pcm_pe[0]
    _RVM1(0x1e82, BIT0, BIT0),   //reg[101e82]#0=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_pcmctrlconfig
    _RVM1(0x1e9f, 0, BIT7),   //reg[101e9f]#7=0
    //reg_cictrlconfig
    _RVM1(0x1ec8, 0, BIT1),   //reg[101ec8]#1=0
    //reg_sm_config
    _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_A10_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A10_OEN (PAD_PCM_A10_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_PCM_A10_OUT (PAD_PCM_A10_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e76, PAD_PCM_A10_OUT, BIT6),
    _RVM1(0x1e7c, PAD_PCM_A10_OEN, BIT6),
    //reg_pcm_pe[18]
    _RVM1(0x1e84, BIT2, BIT2),   //reg[101e84]#2=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_OE_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_OE_N_OEN (PAD_PCM_OE_N_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_PCM_OE_N_OUT (PAD_PCM_OE_N_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e76, PAD_PCM_OE_N_OUT, BIT7),
    _RVM1(0x1e7c, PAD_PCM_OE_N_OEN, BIT7),
    //reg_pcm_pe[1]
    _RVM1(0x1e82, BIT1, BIT1),   //reg[101e82]#1=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_pcmctrlconfig
    _RVM1(0x1e9f, 0, BIT7),   //reg[101e9f]#7=0
    //reg_sm_config
    _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_A11_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A11_OEN (PAD_PCM_A11_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_PCM_A11_OUT (PAD_PCM_A11_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e77, PAD_PCM_A11_OUT, BIT0),
    _RVM1(0x1e7d, PAD_PCM_A11_OEN, BIT0),
    //reg_pcm_pe[19]
    _RVM1(0x1e84, BIT3, BIT3),   //reg[101e84]#3=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_IORD_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_IORD_N_OEN (PAD_PCM_IORD_N_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_PCM_IORD_N_OUT (PAD_PCM_IORD_N_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e77, PAD_PCM_IORD_N_OUT, BIT1),
    _RVM1(0x1e7d, PAD_PCM_IORD_N_OEN, BIT1),
    //reg_pcm_pe[2]
    _RVM1(0x1e82, BIT2, BIT2),   //reg[101e82]#2=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_pcmctrlconfig
    _RVM1(0x1e9f, 0, BIT7),   //reg[101e9f]#7=0
    //reg_cictrlconfig
    _RVM1(0x1ec8, 0, BIT1),   //reg[101ec8]#1=0
    //reg_sm_config
    _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_A9_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A9_OEN (PAD_PCM_A9_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_PCM_A9_OUT (PAD_PCM_A9_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e77, PAD_PCM_A9_OUT, BIT2),
    _RVM1(0x1e7d, PAD_PCM_A9_OEN, BIT2),
    //reg_pcm_pe[17]
    _RVM1(0x1e84, BIT1, BIT1),   //reg[101e84]#1=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_IOWR_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_IOWR_N_OEN (PAD_PCM_IOWR_N_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_PCM_IOWR_N_OUT (PAD_PCM_IOWR_N_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e77, PAD_PCM_IOWR_N_OUT, BIT3),
    _RVM1(0x1e7d, PAD_PCM_IOWR_N_OEN, BIT3),
    //reg_pcm_pe[3]
    _RVM1(0x1e82, BIT3, BIT3),   //reg[101e82]#3=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_pcmctrlconfig
    _RVM1(0x1e9f, 0, BIT7),   //reg[101e9f]#7=0
    //reg_cictrlconfig
    _RVM1(0x1ec8, 0, BIT1),   //reg[101ec8]#1=0
    //reg_sm_config
    _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_A8_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A8_OEN (PAD_PCM_A8_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_PCM_A8_OUT (PAD_PCM_A8_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e77, PAD_PCM_A8_OUT, BIT4),
    _RVM1(0x1e7d, PAD_PCM_A8_OEN, BIT4),
    //reg_pcm_pe[16]
    _RVM1(0x1e84, BIT0, BIT0),   //reg[101e84]#0=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_A13_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A13_OEN (PAD_PCM_A13_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_PCM_A13_OUT (PAD_PCM_A13_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e77, PAD_PCM_A13_OUT, BIT5),
    _RVM1(0x1e7d, PAD_PCM_A13_OEN, BIT5),
    //reg_pcm_pe[21]
    _RVM1(0x1e84, BIT5, BIT5),   //reg[101e84]#5=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_A14_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A14_OEN (PAD_PCM_A14_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_PCM_A14_OUT (PAD_PCM_A14_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e77, PAD_PCM_A14_OUT, BIT6),
    _RVM1(0x1e7d, PAD_PCM_A14_OEN, BIT6),
    //reg_pcm_pe[22]
    _RVM1(0x1e84, BIT6, BIT6),   //reg[101e84]#6=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_WE_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_WE_N_OEN (PAD_PCM_WE_N_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_PCM_WE_N_OUT (PAD_PCM_WE_N_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e77, PAD_PCM_WE_N_OUT, BIT7),
    _RVM1(0x1e7d, PAD_PCM_WE_N_OEN, BIT7),
    //reg_pcm_pe[4]
    _RVM1(0x1e82, BIT4, BIT4),   //reg[101e82]#4=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_pcmctrlconfig
    _RVM1(0x1e9f, 0, BIT7),   //reg[101e9f]#7=0
    //reg_sm_config
    _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_IRQA_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_IRQA_N_OEN (PAD_PCM_IRQA_N_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_PCM_IRQA_N_OUT (PAD_PCM_IRQA_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e78, PAD_PCM_IRQA_N_OUT, BIT0),
    _RVM1(0x1e7e, PAD_PCM_IRQA_N_OEN, BIT0),
    //reg_pcm_pe[5]
    _RVM1(0x1e82, BIT5, BIT5),   //reg[101e82]#5=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_pcmctrlconfig
    _RVM1(0x1e9f, 0, BIT7),   //reg[101e9f]#7=0
    //reg_cictrlconfig
    _RVM1(0x1ec8, 0, BIT1),   //reg[101ec8]#1=0
    //reg_sm_config
    _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_A12_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A12_OEN (PAD_PCM_A12_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_PCM_A12_OUT (PAD_PCM_A12_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e78, PAD_PCM_A12_OUT, BIT1),
    _RVM1(0x1e7e, PAD_PCM_A12_OEN, BIT1),
    //reg_pcm_pe[20]
    _RVM1(0x1e84, BIT4, BIT4),   //reg[101e84]#4=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_A7_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A7_OEN (PAD_PCM_A7_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_PCM_A7_OUT (PAD_PCM_A7_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e78, PAD_PCM_A7_OUT, BIT2),
    _RVM1(0x1e7e, PAD_PCM_A7_OEN, BIT2),
    //reg_pcm_pe[15]
    _RVM1(0x1e83, BIT7, BIT7),   //reg[101e83]#7=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_A6_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A6_OEN (PAD_PCM_A6_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_PCM_A6_OUT (PAD_PCM_A6_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e78, PAD_PCM_A6_OUT, BIT3),
    _RVM1(0x1e7e, PAD_PCM_A6_OEN, BIT3),
    //reg_pcm_pe[14]
    _RVM1(0x1e83, BIT6, BIT6),   //reg[101e83]#6=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_A5_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A5_OEN (PAD_PCM_A5_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_PCM_A5_OUT (PAD_PCM_A5_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e78, PAD_PCM_A5_OUT, BIT4),
    _RVM1(0x1e7e, PAD_PCM_A5_OEN, BIT4),
    //reg_pcm_pe[13]
    _RVM1(0x1e83, BIT5, BIT5),   //reg[101e83]#5=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_WAIT_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_WAIT_N_OEN (PAD_PCM_WAIT_N_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_PCM_WAIT_N_OUT (PAD_PCM_WAIT_N_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e78, PAD_PCM_WAIT_N_OUT, BIT5),
    _RVM1(0x1e7e, PAD_PCM_WAIT_N_OEN, BIT5),
    //reg_pcm_pe[6]
    _RVM1(0x1e82, BIT6, BIT6),   //reg[101e82]#6=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_pcmctrlconfig
    _RVM1(0x1e9f, 0, BIT7),   //reg[101e9f]#7=0
    //reg_cictrlconfig
    _RVM1(0x1ec8, 0, BIT1),   //reg[101ec8]#1=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_A4_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A4_OEN (PAD_PCM_A4_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_PCM_A4_OUT (PAD_PCM_A4_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e78, PAD_PCM_A4_OUT, BIT6),
    _RVM1(0x1e7e, PAD_PCM_A4_OEN, BIT6),
    //reg_pcm_pe[12]
    _RVM1(0x1e83, BIT4, BIT4),   //reg[101e83]#4=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_A3_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A3_OEN (PAD_PCM_A3_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_PCM_A3_OUT (PAD_PCM_A3_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e78, PAD_PCM_A3_OUT, BIT7),
    _RVM1(0x1e7e, PAD_PCM_A3_OEN, BIT7),
    //reg_pcm_pe[11]
    _RVM1(0x1e83, BIT3, BIT3),   //reg[101e83]#3=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_sd0_config
    _RVM1(0x1e16, 0, BIT3 | BIT2),   //reg[101e16]#3 ~ #2=0
    //reg_sd1_config
    _RVM1(0x1e16, 0, BIT7 | BIT6),   //reg[101e16]#7 ~ #6=0
    //reg_sd0_config2
    _RVM1(0x1e16, 0, BIT5 | BIT4),   //reg[101e16]#5 ~ #4=0
    //reg_sd1_config2
    _RVM1(0x1e17, 0, BIT1 | BIT0),   //reg[101e17]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_A2_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A2_OEN (PAD_PCM_A2_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_PCM_A2_OUT (PAD_PCM_A2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e79, PAD_PCM_A2_OUT, BIT0),
    _RVM1(0x1e7f, PAD_PCM_A2_OEN, BIT0),
    //reg_pcm_pe[10]
    _RVM1(0x1e83, BIT2, BIT2),   //reg[101e83]#2=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_nand_mode
    //_RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_sd0_config
    _RVM1(0x1e16, 0, BIT3 | BIT2),   //reg[101e16]#3 ~ #2=0
    //reg_sd1_config
    _RVM1(0x1e16, 0, BIT7 | BIT6),   //reg[101e16]#7 ~ #6=0
    //reg_sd0_config2
    _RVM1(0x1e16, 0, BIT5 | BIT4),   //reg[101e16]#5 ~ #4=0
    //reg_sd1_config2
    _RVM1(0x1e17, 0, BIT1 | BIT0),   //reg[101e17]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_REG_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_REG_N_OEN (PAD_PCM_REG_N_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_PCM_REG_N_OUT (PAD_PCM_REG_N_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e79, PAD_PCM_REG_N_OUT, BIT1),
    _RVM1(0x1e7f, PAD_PCM_REG_N_OEN, BIT1),
    //reg_pcm_pe[7]
    _RVM1(0x1e82, BIT7, BIT7),   //reg[101e82]#7=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_pcmctrlconfig
    _RVM1(0x1e9f, 0, BIT7),   //reg[101e9f]#7=0
    //reg_cictrlconfig
    _RVM1(0x1ec8, 0, BIT1),   //reg[101ec8]#1=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_A1_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A1_OEN (PAD_PCM_A1_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_PCM_A1_OUT (PAD_PCM_A1_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e79, PAD_PCM_A1_OUT, BIT2),
    _RVM1(0x1e7f, PAD_PCM_A1_OEN, BIT2),
    //reg_pcm_pe[9]
    _RVM1(0x1e83, BIT1, BIT1),   //reg[101e83]#1=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_sd0_config
    _RVM1(0x1e16, 0, BIT3 | BIT2),   //reg[101e16]#3 ~ #2=0
    //reg_sd1_config
    _RVM1(0x1e16, 0, BIT7 | BIT6),   //reg[101e16]#7 ~ #6=0
    //reg_sd0_config2
    _RVM1(0x1e16, 0, BIT5 | BIT4),   //reg[101e16]#5 ~ #4=0
    //reg_sd1_config2
    _RVM1(0x1e17, 0, BIT1 | BIT0),   //reg[101e17]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_A0_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_A0_OEN (PAD_PCM_A0_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_PCM_A0_OUT (PAD_PCM_A0_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e79, PAD_PCM_A0_OUT, BIT3),
    _RVM1(0x1e7f, PAD_PCM_A0_OEN, BIT3),
    //reg_pcm_pe[8]
    _RVM1(0x1e83, BIT0, BIT0),   //reg[101e83]#0=1b
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_sd0_config
    _RVM1(0x1e16, 0, BIT3 | BIT2),   //reg[101e16]#3 ~ #2=0
    //reg_sd1_config
    _RVM1(0x1e16, 0, BIT7 | BIT6),   //reg[101e16]#7 ~ #6=0
    //reg_sd0_config2
    _RVM1(0x1e16, 0, BIT5 | BIT4),   //reg[101e16]#5 ~ #4=0
    //reg_sd1_config2
    _RVM1(0x1e17, 0, BIT1 | BIT0),   //reg[101e17]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_D0_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_D0_OEN (PAD_PCM_D0_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_PCM_D0_OUT (PAD_PCM_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e79, PAD_PCM_D0_OUT, BIT4),
    _RVM1(0x1e7f, PAD_PCM_D0_OEN, BIT4),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e86, BIT1 , BIT1 ),   //reg[101e86] #1 = 1b
    //reg_pcm_d_pe[0]
    _RVM1(0x1e18, BIT0, BIT0),   //reg[101e18]#0=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_emmc_config
    _RVM1(0x1ebb, 0, BIT7 | BIT6),   //reg[101ebb]#7 ~ #6=0
    //CHIP_CONFIG = BOOT_FROM_EMMC_M1
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_D1_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_D1_OEN (PAD_PCM_D1_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_PCM_D1_OUT (PAD_PCM_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e79, PAD_PCM_D1_OUT, BIT5),
    _RVM1(0x1e7f, PAD_PCM_D1_OEN, BIT5),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e86, BIT1 , BIT1 ),   //reg[101e86] #1 = 1b
    //reg_pcm_d_pe[1]
    _RVM1(0x1e18, BIT1, BIT1),   //reg[101e18]#1=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_emmc_config
    _RVM1(0x1ebb, 0, BIT7 | BIT6),   //reg[101ebb]#7 ~ #6=0
    //CHIP_CONFIG = BOOT_FROM_EMMC_M1
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_D2_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_D2_OEN (PAD_PCM_D2_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_PCM_D2_OUT (PAD_PCM_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e79, PAD_PCM_D2_OUT, BIT6),
    _RVM1(0x1e7f, PAD_PCM_D2_OEN, BIT6),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e86, BIT1 , BIT1 ),   //reg[101e86] #1 = 1b
    //reg_pcm_d_pe[2]
    _RVM1(0x1e18, BIT2, BIT2),   //reg[101e18]#2=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_pcmadconfig
    _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6=0
    //reg_ciadconfig
    _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0=0
    //reg_emmc_config
    _RVM1(0x1ebb, 0, BIT7 | BIT6),   //reg[101ebb]#7 ~ #6=0
    //CHIP_CONFIG = BOOT_FROM_EMMC_M1
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_RESET_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_RESET_OEN (PAD_PCM_RESET_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_PCM_RESET_OUT (PAD_PCM_RESET_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e79, PAD_PCM_RESET_OUT, BIT7),
    _RVM1(0x1e7f, PAD_PCM_RESET_OEN, BIT7),
    //reg_pcm_pe[23]
    _RVM1(0x1e84, BIT7, BIT7),   //reg[101e84]#7=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_pcmctrlconfig
    _RVM1(0x1e9f, 0, BIT7),   //reg[101e9f]#7=0
    //reg_cictrlconfig
    _RVM1(0x1ec8, 0, BIT1),   //reg[101ec8]#1=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM_CD_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_CD_N_OEN (PAD_PCM_CD_N_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_PCM_CD_N_OUT (PAD_PCM_CD_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e7a, PAD_PCM_CD_N_OUT, BIT0),
    _RVM1(0x1e80, PAD_PCM_CD_N_OEN, BIT0),
    //reg_pcm_pe[24]
    _RVM1(0x1e85, BIT0, BIT0),   //reg[101e85]#0=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_pcmctrlconfig
    _RVM1(0x1e9f, 0, BIT7),   //reg[101e9f]#7=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM2_CE_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM2_CE_N_OEN (PAD_PCM2_CE_N_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_PCM2_CE_N_OUT (PAD_PCM2_CE_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e7b, PAD_PCM2_CE_N_OUT, BIT0),
    _RVM1(0x1e81, PAD_PCM2_CE_N_OEN, BIT0),
    //reg_pcm2ctrlconfig
    _RVM1(0x1e9f, 0, BIT5),   //reg[101e9f]#5=0
    //reg_sd0_config
    _RVM1(0x1e16, 0, BIT3 | BIT2),   //reg[101e16]#3 ~ #2=0
    //reg_extint0
    _RVM1(0x1ee0, 0, BIT0),   //reg[101ee0]#0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM2_IRQA_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM2_IRQA_N_OEN (PAD_PCM2_IRQA_N_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_PCM2_IRQA_N_OUT (PAD_PCM2_IRQA_N_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e7b, PAD_PCM2_IRQA_N_OUT, BIT1),
    _RVM1(0x1e81, PAD_PCM2_IRQA_N_OEN, BIT1),
    //reg_pcm2ctrlconfig
    _RVM1(0x1e9f, 0, BIT5),   //reg[101e9f]#5=0
    //reg_sd0_config
    _RVM1(0x1e16, 0, BIT3 | BIT2),   //reg[101e16]#3 ~ #2=0
    //reg_extint2
    _RVM1(0x1ee0, 0, BIT2),   //reg[101ee0]#2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM2_WAIT_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM2_WAIT_N_OEN (PAD_PCM2_WAIT_N_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_PCM2_WAIT_N_OUT (PAD_PCM2_WAIT_N_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e7b, PAD_PCM2_WAIT_N_OUT, BIT2),
    _RVM1(0x1e81, PAD_PCM2_WAIT_N_OEN, BIT2),
    //reg_chiptop_dummy_3[1]
    //_RVM1(0x1e3e, 0, BIT1),   //reg[101e3e]#1=0
    //reg_pcm2ctrlconfig
    _RVM1(0x1e9f, 0, BIT5),   //reg[101e9f]#5=0
    //reg_sd1_config
    _RVM1(0x1e16, 0, BIT7 | BIT6),   //reg[101e16]#7 ~ #6=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM2_RESET_IS_GPIO != GPIO_NONE)
    #define PAD_PCM2_RESET_OEN (PAD_PCM2_RESET_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_PCM2_RESET_OUT (PAD_PCM2_RESET_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e7b, PAD_PCM2_RESET_OUT, BIT3),
    _RVM1(0x1e81, PAD_PCM2_RESET_OEN, BIT3),
    //reg_pcm2ctrlconfig
    _RVM1(0x1e9f, 0, BIT5),   //reg[101e9f]#5=0
    //reg_sd1_config
    _RVM1(0x1e16, 0, BIT7 | BIT6),   //reg[101e16]#7 ~ #6=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PCM2_CD_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM2_CD_N_OEN (PAD_PCM2_CD_N_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_PCM2_CD_N_OUT (PAD_PCM2_CD_N_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e7b, PAD_PCM2_CD_N_OUT, BIT4),
    _RVM1(0x1e81, PAD_PCM2_CD_N_OEN, BIT4),
    //reg_pcm_pe[25]
    _RVM1(0x1e85, BIT1, BIT1),   //reg[101e85]#1=1b
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_pcm2ctrlconfig
    _RVM1(0x1e9f, 0, BIT5),   //reg[101e9f]#5=0
    //reg_pcm2_cdn_config
    _RVM1(0x1eb3, 0, BIT2),   //reg[101eb3]#2=0
    //reg_extint3
    _RVM1(0x1ee0, 0, BIT3),   //reg[101ee0]#3=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PWM0_IS_GPIO != GPIO_NONE)
    #define PAD_PWM0_OEN (PAD_PWM0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_PWM0_OUT (PAD_PWM0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e98, PAD_PWM0_OUT, BIT0),
    _RVM1(0x1e96, PAD_PWM0_OEN, BIT0),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_pwm0_mode
    _RVM1(0x1ea2, 0, BIT0),   //reg[101ea2]#0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PWM1_IS_GPIO != GPIO_NONE)
    #define PAD_PWM1_OEN (PAD_PWM1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_PWM1_OUT (PAD_PWM1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e98, PAD_PWM1_OUT, BIT1),
    _RVM1(0x1e96, PAD_PWM1_OEN, BIT1),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_pwm1_mode
    _RVM1(0x1ea2, 0, BIT1),   //reg[101ea2]#1=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PWM2_IS_GPIO != GPIO_NONE)
    #define PAD_PWM2_OEN (PAD_PWM2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_PWM2_OUT (PAD_PWM2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e98, PAD_PWM2_OUT, BIT2),
    _RVM1(0x1e96, PAD_PWM2_OEN, BIT2),
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_pwm2_mode
    _RVM1(0x1ea2, 0, BIT2),   //reg[101ea2]#2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PWM3_IS_GPIO != GPIO_NONE)
    #define PAD_PWM3_OEN (PAD_PWM3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_PWM3_OUT (PAD_PWM3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e98, PAD_PWM3_OUT, BIT3),
    _RVM1(0x1e96, PAD_PWM3_OEN, BIT3),
    //reg_pwm3_mode
    _RVM1(0x1ea2, 0, BIT3),   //reg[101ea2]#3=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PWM4_IS_GPIO != GPIO_NONE)
    #define PAD_PWM4_OEN (PAD_PWM4_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_PWM4_OUT (PAD_PWM4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e98, PAD_PWM4_OUT, BIT4),
    _RVM1(0x1e96, PAD_PWM4_OEN, BIT4),
    //reg_i2smutemode
    _RVM1(0x1e05, 0, BIT7 | BIT6),   //reg[101e05]#7 ~ #6=0
    //reg_pwm4_mode
    _RVM1(0x1ea2, 0, BIT5 | BIT4),   //reg[101ea2]#5 ~ #4=0
    //reg_tserrout
    _RVM1(0x1ea3, 0, BIT0),   //reg[101ea3]#0=0
    _RVM1(0x1ea2, 0, BIT7),   //reg[101ea2]#7=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PWM5_IS_GPIO != GPIO_NONE)
    #define PAD_PWM5_OEN (PAD_PWM5_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_PWM5_OUT (PAD_PWM5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e98, PAD_PWM5_OUT, BIT5),
    _RVM1(0x1e96, PAD_PWM5_OEN, BIT5),
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_pwm0_dim_mode
    _RVM1(0x1eef, 0, BIT0),   //reg[101eef]#0=0
    //reg_sm_config
    _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PWM6_IS_GPIO != GPIO_NONE)
    #define PAD_PWM6_OEN (PAD_PWM6_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_PWM6_OUT (PAD_PWM6_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e98, PAD_PWM6_OUT, BIT6),
    _RVM1(0x1e96, PAD_PWM6_OEN, BIT6),
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_pwm1_dim_mode
    _RVM1(0x1eef, 0, BIT1),   //reg[101eef]#1=0
    //reg_sm_config
    _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PWM7_IS_GPIO != GPIO_NONE)
    #define PAD_PWM7_OEN (PAD_PWM7_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_PWM7_OUT (PAD_PWM7_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e98, PAD_PWM7_OUT, BIT7),
    _RVM1(0x1e96, PAD_PWM7_OEN, BIT7),
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_pwm2_dim_mode
    _RVM1(0x1eef, 0, BIT2),   //reg[101eef]#2=0
    //reg_sm_config
    _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PWM8_IS_GPIO != GPIO_NONE)
    #define PAD_PWM8_OEN (PAD_PWM8_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_PWM8_OUT (PAD_PWM8_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e99, PAD_PWM8_OUT, BIT0),
    _RVM1(0x1e97, PAD_PWM8_OEN, BIT0),
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_pwm3_dim_mode
    _RVM1(0x1eef, 0, BIT3),   //reg[101eef]#3=0
    //reg_sm_config
    _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PWM9_IS_GPIO != GPIO_NONE)
    #define PAD_PWM9_OEN (PAD_PWM9_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_PWM9_OUT (PAD_PWM9_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e99, PAD_PWM9_OUT, BIT1),
    _RVM1(0x1e97, PAD_PWM9_OEN, BIT1),
    //reg_pwm4_dim_mode
    _RVM1(0x1eef, 0, BIT4),   //reg[101eef]#4=0
    //reg_sm_config
    _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_PWM10_IS_GPIO != GPIO_NONE)
    #define PAD_PWM10_OEN (PAD_PWM10_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_PWM10_OUT (PAD_PWM10_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e99, PAD_PWM10_OUT, BIT2),
    _RVM1(0x1e97, PAD_PWM10_OEN, BIT2),
    //reg_pwm5_dim_mode
    _RVM1(0x1eef, 0, BIT5),   //reg[101eef]#5=0
    //reg_sm_config
    _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_EMMC_RSTN_IS_GPIO != GPIO_NONE)
    #define PAD_EMMC_RSTN_OEN (PAD_EMMC_RSTN_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_EMMC_RSTN_OUT (PAD_EMMC_RSTN_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x0a40, PAD_EMMC_RSTN_OUT, BIT0),
    _RVM1(0x0a40, PAD_EMMC_RSTN_OEN, BIT1),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e86, BIT1 , BIT1 ),   //reg[101e86] #1 = 1b
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_nand_cs3_en
    _RVM1(0x1e16, 0, BIT1),   //reg[101e16]#1=0
    //reg_emmc_rstn_en
    _RVM1(0x1e86, 0, BIT3),   //reg[101e86]#3=0
    //reg_emmc_config
    _RVM1(0x1ebb, 0, BIT7 | BIT6),   //reg[101ebb]#7 ~ #6=0
    //CHIP_CONFIG is not equal to "BOOT_FROM_EMMC_M1"
    //CHIP_CONFIG is not equal to "BOOT_FROM_EMMC_M2"
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_EMMC_CLK_IS_GPIO != GPIO_NONE)
    #define PAD_EMMC_CLK_OEN (PAD_EMMC_CLK_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_EMMC_CLK_OUT (PAD_EMMC_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x0a41, PAD_EMMC_CLK_OUT, BIT0),
    _RVM1(0x0a41, PAD_EMMC_CLK_OEN, BIT1),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e86, BIT1 , BIT1 ),   //reg[101e86] #1 = 1b
    //reg_sd_use_bypass
    _RVM1(0x1e86, 0, BIT0 ),   //reg[101e86] #0 = 0b
    //reg_ds_testen
    //_RVM1(0x1359, 0, BIT6 ),   //reg[111359] #6 = 0b
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_emmc_config
    _RVM1(0x1ebb, 0, BIT7 | BIT6),   //reg[101ebb]#7 ~ #6=0
    //CHIP_CONFIG is not equal to "BOOT_FROM_EMMC_M1"
    //CHIP_CONFIG is not equal to "BOOT_FROM_EMMC_M2"
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_EMMC_CMD_IS_GPIO != GPIO_NONE)
    #define PAD_EMMC_CMD_OEN (PAD_EMMC_CMD_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_EMMC_CMD_OUT (PAD_EMMC_CMD_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x0a42, PAD_EMMC_CMD_OUT, BIT0),
    _RVM1(0x0a42, PAD_EMMC_CMD_OEN, BIT1),
    //reg_fcie2macro_sd_bypass
    _RVM1(0x1e86, BIT1 , BIT1 ),   //reg[101e86] #1 = 1b
    //reg_nand_mode
    _RVM1(0x1e17, 0, BIT6 | BIT5 | BIT4),   //reg[101e17]#6 ~ #4=0
    //reg_nand_cs2_en
    _RVM1(0x1e16, 0, BIT0),   //reg[101e16]#0=0
    //reg_emmc_config
    _RVM1(0x1ebb, 0, BIT7 | BIT6),   //reg[101ebb]#7 ~ #6=0
    //CHIP_CONFIG is not equal to "BOOT_FROM_EMMC_M1"
    //CHIP_CONFIG is not equal to "BOOT_FROM_EMMC_M2"
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TGPIO0_IS_GPIO != GPIO_NONE)
    #define PAD_TGPIO0_OEN (PAD_TGPIO0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_TGPIO0_OUT (PAD_TGPIO0_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e9c, PAD_TGPIO0_OUT, BIT4),
    _RVM1(0x1e9c, PAD_TGPIO0_OEN, BIT0),
    //reg_vsync_vif_out_en
    _RVM1(0x1ea3, 0, BIT6),   //reg[101ea3]#6=0
    //reg_mcu_jtag_mode
    //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6=0
    //reg_dspejtagmode
    //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TGPIO1_IS_GPIO != GPIO_NONE)
    #define PAD_TGPIO1_OEN (PAD_TGPIO1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_TGPIO1_OUT (PAD_TGPIO1_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e9c, PAD_TGPIO1_OUT, BIT5),
    _RVM1(0x1e9c, PAD_TGPIO1_OEN, BIT1),
    //reg_mcu_jtag_mode
    //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6=0
    //reg_dspejtagmode
    //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TGPIO2_IS_GPIO != GPIO_NONE)
    #define PAD_TGPIO2_OEN (PAD_TGPIO2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_TGPIO2_OUT (PAD_TGPIO2_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e9c, PAD_TGPIO2_OUT, BIT6),
    _RVM1(0x1e9c, PAD_TGPIO2_OEN, BIT2),
    //reg_mcu_jtag_mode
    //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6=0
    //reg_dspejtagmode
    //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0=0
    //reg_miic_mode1
    _RVM1(0x1eb5, 0, BIT3 | BIT2),   //reg[101eb5]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TGPIO3_IS_GPIO != GPIO_NONE)
    #define PAD_TGPIO3_OEN (PAD_TGPIO3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_TGPIO3_OUT (PAD_TGPIO3_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e9c, PAD_TGPIO3_OUT, BIT7),
    _RVM1(0x1e9c, PAD_TGPIO3_OEN, BIT3),
    //reg_mcu_jtag_mode
    //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6=0
    //reg_dspejtagmode
    //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0=0
    //reg_miic_mode1
    _RVM1(0x1eb5, 0, BIT3 | BIT2),   //reg[101eb5]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS0_D0_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D0_OEN (PAD_TS0_D0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_TS0_D0_OUT (PAD_TS0_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e64, PAD_TS0_D0_OUT, BIT0),
    _RVM1(0x1e68, PAD_TS0_D0_OEN, BIT0),
    //reg_ts0_pe[0]
    _RVM1(0x1e1c, BIT0, BIT0),   //reg[101e1c]#0=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_ts0_config
    _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS0_D1_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D1_OEN (PAD_TS0_D1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_TS0_D1_OUT (PAD_TS0_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e64, PAD_TS0_D1_OUT, BIT1),
    _RVM1(0x1e68, PAD_TS0_D1_OEN, BIT1),
    //reg_ts0_pe[1]
    _RVM1(0x1e1c, BIT1, BIT1),   //reg[101e1c]#1=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_ts0_config
    _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS0_D2_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D2_OEN (PAD_TS0_D2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_TS0_D2_OUT (PAD_TS0_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e64, PAD_TS0_D2_OUT, BIT2),
    _RVM1(0x1e68, PAD_TS0_D2_OEN, BIT2),
    //reg_ts0_pe[2]
    _RVM1(0x1e1c, BIT2, BIT2),   //reg[101e1c]#2=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_ts0_config
    _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS0_D3_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D3_OEN (PAD_TS0_D3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_TS0_D3_OUT (PAD_TS0_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e64, PAD_TS0_D3_OUT, BIT3),
    _RVM1(0x1e68, PAD_TS0_D3_OEN, BIT3),
    //reg_ts0_pe[3]
    _RVM1(0x1e1c, BIT3, BIT3),   //reg[101e1c]#3=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_test_out_mode
    //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4=0
    //reg_ts0_config
    _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS0_D4_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D4_OEN (PAD_TS0_D4_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_TS0_D4_OUT (PAD_TS0_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e64, PAD_TS0_D4_OUT, BIT4),
    _RVM1(0x1e68, PAD_TS0_D4_OEN, BIT4),
    //reg_ts0_pe[4]
    _RVM1(0x1e1c, BIT4, BIT4),   //reg[101e1c]#4=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_ts0_config
    _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS0_D5_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D5_OEN (PAD_TS0_D5_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_D5_OUT (PAD_TS0_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e64, PAD_TS0_D5_OUT, BIT5),
    _RVM1(0x1e68, PAD_TS0_D5_OEN, BIT5),
    //reg_ts0_pe[5]
    _RVM1(0x1e1c, BIT5, BIT5),   //reg[101e1c]#5=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_ts0_config
    _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS0_D6_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D6_OEN (PAD_TS0_D6_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_TS0_D6_OUT (PAD_TS0_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e64, PAD_TS0_D6_OUT, BIT6),
    _RVM1(0x1e68, PAD_TS0_D6_OEN, BIT6),
    //reg_ts0_pe[6]
    _RVM1(0x1e1c, BIT6, BIT6),   //reg[101e1c]#6=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_ts0_config
    _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS0_D7_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D7_OEN (PAD_TS0_D7_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_TS0_D7_OUT (PAD_TS0_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e64, PAD_TS0_D7_OUT, BIT7),
    _RVM1(0x1e68, PAD_TS0_D7_OEN, BIT7),
    //reg_ts0_pe[7]
    _RVM1(0x1e1c, BIT7, BIT7),   //reg[101e1c]#7=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_ts0_config
    _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS0_VLD_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_VLD_OEN (PAD_TS0_VLD_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_TS0_VLD_OUT (PAD_TS0_VLD_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e65, PAD_TS0_VLD_OUT, BIT0),
    _RVM1(0x1e69, PAD_TS0_VLD_OEN, BIT0),
    //reg_ts0_pe[8]
    _RVM1(0x1e1d, BIT0, BIT0),   //reg[101e1d]#0=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_ts0_config
    _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS0_SYNC_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_SYNC_OEN (PAD_TS0_SYNC_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_TS0_SYNC_OUT (PAD_TS0_SYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e65, PAD_TS0_SYNC_OUT, BIT1),
    _RVM1(0x1e69, PAD_TS0_SYNC_OEN, BIT1),
    //reg_ts0_pe[9]
    _RVM1(0x1e1d, BIT1, BIT1),   //reg[101e1d]#1=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_ts0_config
    _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS0_CLK_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_CLK_OEN (PAD_TS0_CLK_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_TS0_CLK_OUT (PAD_TS0_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e65, PAD_TS0_CLK_OUT, BIT2),
    _RVM1(0x1e69, PAD_TS0_CLK_OEN, BIT2),
    //reg_ts0_pe[10]
    _RVM1(0x1e1d, BIT2, BIT2),   //reg[101e1d]#2=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_ts0_config
    _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS1_CLK_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_CLK_OEN (PAD_TS1_CLK_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_TS1_CLK_OUT (PAD_TS1_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e4c, PAD_TS1_CLK_OUT, BIT0),
    _RVM1(0x1e4e, PAD_TS1_CLK_OEN, BIT0),
    //reg_ts1_pe[10]
    _RVM1(0x1e1f, BIT2, BIT2),   //reg[101e1f]#2=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_ts1_config
    _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4=0
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1),   //reg[101ea3]#1=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_miic_mode0
    _RVM1(0x1eb5, 0, BIT1 | BIT0),   //reg[101eb5]#1 ~ #0=0
    //reg_pdtracectrl
    _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS1_SYNC_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_SYNC_OEN (PAD_TS1_SYNC_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_TS1_SYNC_OUT (PAD_TS1_SYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e4c, PAD_TS1_SYNC_OUT, BIT1),
    _RVM1(0x1e4e, PAD_TS1_SYNC_OEN, BIT1),
    //reg_ts1_pe[9]
    _RVM1(0x1e1f, BIT1, BIT1),   //reg[101e1f]#1=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_ts1_config
    _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4=0
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1),   //reg[101ea3]#1=0
    //reg_miic_mode0
    _RVM1(0x1eb5, 0, BIT1 | BIT0),   //reg[101eb5]#1 ~ #0=0
    //reg_pdtracectrl
    _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0=0
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS1_VLD_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_VLD_OEN (PAD_TS1_VLD_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_TS1_VLD_OUT (PAD_TS1_VLD_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e4c, PAD_TS1_VLD_OUT, BIT2),
    _RVM1(0x1e4e, PAD_TS1_VLD_OEN, BIT2),
    //reg_ts1_pe[8]
    _RVM1(0x1e1f, BIT0, BIT0),   //reg[101e1f]#0=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_ts1_config
    _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4=0
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1),   //reg[101ea3]#1=0
    //reg_miic_mode1
    _RVM1(0x1eb5, 0, BIT3 | BIT2),   //reg[101eb5]#3 ~ #2=0
    //reg_miic_mode2
    _RVM1(0x1eb5, 0, BIT5 | BIT4),   //reg[101eb5]#5 ~ #4=0
    //reg_pdtracectrl
    _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS1_D7_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D7_OEN (PAD_TS1_D7_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_TS1_D7_OUT (PAD_TS1_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e4c, PAD_TS1_D7_OUT, BIT3),
    _RVM1(0x1e4e, PAD_TS1_D7_OEN, BIT3),
    //reg_ts1_pe[7]
    _RVM1(0x1e1e, BIT7, BIT7),   //reg[101e1e]#7=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_ts1_config
    _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4=0
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1),   //reg[101ea3]#1=0
    //reg_dspejtagmode
    //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_pdtracectrl
    _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS1_D6_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D6_OEN (PAD_TS1_D6_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_TS1_D6_OUT (PAD_TS1_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e4c, PAD_TS1_D6_OUT, BIT4),
    _RVM1(0x1e4e, PAD_TS1_D6_OEN, BIT4),
    //reg_ts1_pe[6]
    _RVM1(0x1e1e, BIT6, BIT6),   //reg[101e1e]#6=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_ts1_config
    _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4=0
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1),   //reg[101ea3]#1=0
    //reg_dspejtagmode
    //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_sm_config
    _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2=0
    //reg_pdtracectrl
    _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS1_D5_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D5_OEN (PAD_TS1_D5_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS1_D5_OUT (PAD_TS1_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e4c, PAD_TS1_D5_OUT, BIT5),
    _RVM1(0x1e4e, PAD_TS1_D5_OEN, BIT5),
    //reg_ts1_pe[5]
    _RVM1(0x1e1e, BIT5, BIT5),   //reg[101e1e]#5=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_ts1_config
    _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4=0
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1),   //reg[101ea3]#1=0
    //reg_dspejtagmode
    //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_sm_config
    _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2=0
    //reg_pdtracectrl
    _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS1_D4_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D4_OEN (PAD_TS1_D4_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_TS1_D4_OUT (PAD_TS1_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e4c, PAD_TS1_D4_OUT, BIT6),
    _RVM1(0x1e4e, PAD_TS1_D4_OEN, BIT6),
    //reg_ts1_pe[4]
    _RVM1(0x1e1e, BIT4, BIT4),   //reg[101e1e]#4=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_ts1_config
    _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4=0
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1),   //reg[101ea3]#1=0
    //reg_dspejtagmode
    //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_sm_config
    _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS1_D3_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D3_OEN (PAD_TS1_D3_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_TS1_D3_OUT (PAD_TS1_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e4c, PAD_TS1_D3_OUT, BIT7),
    _RVM1(0x1e4e, PAD_TS1_D3_OEN, BIT7),
    //reg_ts1_pe[3]
    _RVM1(0x1e1e, BIT3, BIT3),   //reg[101e1e]#3=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_ts1_config
    _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4=0
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1),   //reg[101ea3]#1=0
    //reg_bt656_ctrl
    //_RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_sm_config
    _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS1_D2_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D2_OEN (PAD_TS1_D2_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_TS1_D2_OUT (PAD_TS1_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e4d, PAD_TS1_D2_OUT, BIT0),
    _RVM1(0x1e4f, PAD_TS1_D2_OEN, BIT0),
    //reg_ts1_pe[2]
    _RVM1(0x1e1e, BIT2, BIT2),   //reg[101e1e]#2=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_ts1_config
    _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4=0
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1),   //reg[101ea3]#1=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_sm_config
    _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS1_D1_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D1_OEN (PAD_TS1_D1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_TS1_D1_OUT (PAD_TS1_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e4d, PAD_TS1_D1_OUT, BIT1),
    _RVM1(0x1e4f, PAD_TS1_D1_OEN, BIT1),
    //reg_ts1_pe[1]
    _RVM1(0x1e1e, BIT1, BIT1),   //reg[101e1e]#1=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_ts1_config
    _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4=0
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1),   //reg[101ea3]#1=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_sm_config
    _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_TS1_D0_IS_GPIO != GPIO_NONE)
    #define PAD_TS1_D0_OEN (PAD_TS1_D0_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_TS1_D0_OUT (PAD_TS1_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e4d, PAD_TS1_D0_OUT, BIT2),
    _RVM1(0x1e4f, PAD_TS1_D0_OEN, BIT2),
    //reg_ts1_pe[0]
    _RVM1(0x1e1e, BIT0, BIT0),   //reg[101e1e]#0=1b
    //reg_test_in_mode
    //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0=0
    //reg_ts1_config
    _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4=0
    //reg_ts_out_mode
    _RVM1(0x1ea3, 0, BIT1),   //reg[101ea3]#1=0
    //reg_bt656_ctrl
    _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6=0
    //reg_miic_mode1
    _RVM1(0x1eb5, 0, BIT3 | BIT2),   //reg[101eb5]#3 ~ #2=0
    //reg_miic_mode2
    _RVM1(0x1eb5, 0, BIT5 | BIT4),   //reg[101eb5]#5 ~ #4=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_UART_TX2_IS_GPIO != GPIO_NONE)
    #define PAD_UART_TX2_OEN (PAD_UART_TX2_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_UART_TX2_OUT (PAD_UART_TX2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x0a00, PAD_UART_TX2_OUT, BIT0),
    _RVM1(0x0a02, PAD_UART_TX2_OEN, BIT0),
    //reg_thirduartmode
    _RVM1(0x1e05, 0, BIT3 | BIT2),   //reg[101e05]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

    #if(PAD_UART_RX2_IS_GPIO != GPIO_NONE)
    #define PAD_UART_RX2_OEN (PAD_UART_RX2_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_UART_RX2_OUT (PAD_UART_RX2_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0a00, PAD_UART_RX2_OUT, BIT1),
    _RVM1(0x0a02, PAD_UART_RX2_OEN, BIT1),
    //reg_thirduartmode
    _RVM1(0x1e05, 0, BIT3 | BIT2),   //reg[101e05]#3 ~ #2=0
    //reg_allpad_in
    //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0
    //default is GPIO
    #endif

//---------------------------------------------------------------------
// Pad Configuartion
//---------------------------------------------------------------------
#ifdef PADS_VSYNC_VIF_OUT_EN
#if (PADS_VSYNC_VIF_OUT_EN != Unknown_pad_mux)
#define VSYNC_VIF_OUT_EN   ((PADS_VSYNC_VIF_OUT_EN == ENABLE) ? BIT6 : 0)
    _RVM1(0x1EA3, VSYNC_VIF_OUT_EN, BIT6),
#endif
#endif

#ifdef PADS_TS0_CONFIG
#if (PADS_TS0_CONFIG != Unknown_pad_mux)
#define TS0_CONFIG   ((PADS_TS0_CONFIG == PARALLEL_IN) ? BIT2 : \
                      (PADS_TS0_CONFIG == SERIAL_IN) ? BIT3 : \
                      (PADS_TS0_CONFIG == PARALLEL_2nd_PORT) ? (BIT3 | BIT2) : 0)
    _RVM1(0x1EA3, TS0_CONFIG, (BIT3 | BIT2)),
#endif
#endif

#ifdef PADS_TS1_CONFIG
#if (PADS_TS1_CONFIG != Unknown_pad_mux)
#define TS1_CONFIG   ((PADS_TS1_CONFIG == PARALLEL_IN) ? BIT4 : \
                      (PADS_TS1_CONFIG == PARALLEL_OUT) ? BIT5 : \
                      (PADS_TS1_CONFIG == SERIAL_IN) ? (BIT5 | BIT4) : 0)
    _RVM1(0x1EA3, TS1_CONFIG, (BIT5 | BIT4)),
#endif
#endif

#ifdef PADS_TS_OUT
#if (PADS_TS_OUT != Unknown_pad_mux)
#define TS_OUT_MODE   ((PADS_TS_OUT == ENABLE) ? BIT1 : 0)
    _RVM1(0x1EA3, TS_OUT_MODE, BIT1),
#endif
#endif

#ifdef PADS_TS0_PE
#if (PADS_TS0_PE == ENABLE)
    _RVM1(0x1E1C, BITMASK(7:0), BITMASK(7:0)),
    _RVM1(0x1E1D, BITMASK(2:0), BITMASK(2:0)),
#else
    _RVM1(0x1E1C, 0, BITMASK(7:0)),
    _RVM1(0x1E1D, 0, BITMASK(2:0)),
#endif
#endif

#ifdef PADS_TS1_PE
#if (PADS_TS1_PE == ENABLE)
    _RVM1(0x1E1E, BITMASK(7:0), BITMASK(7:0)),
    _RVM1(0x1E1F, BITMASK(2:0), BITMASK(2:0)),
#else
    _RVM1(0x1E1E, 0, BITMASK(7:0)),
    _RVM1(0x1E1F, 0, BITMASK(2:0)),
#endif
#endif

#ifdef PADS_NAND_MODE
#if (PADS_NAND_MODE != Unknown_pad_mux)
#define NAND_MODE   ((PADS_NAND_MODE == PCM_D) ? BIT4 : \
                     (PADS_NAND_MODE == PCM_A) ? BIT5 : 0)
    _RVM1(0x1E17, NAND_MODE, (BIT6 | BIT5 | BIT4)),
#if(PADS_NAND_MODE == PCM_D)
    _RVM2(0x1e18, BITMASK(7:0), BITMASK(7:0)),
#else
    _RVM2(0x1e83, BITMASK(7:0), BITMASK(7:0)),
#endif
#else
    _RVM1(0x1E17, 0, (BIT6 | BIT5 | BIT4)),
    _RVM1(0x1E86, BIT1, BIT1),
#endif
#endif

#ifdef PADS_PCM1_CTRL
#if (PADS_PCM1_CTRL != Unknown_pad_mux)
#define PCM1_CTRL   ((PADS_PCM1_CTRL == PAD_PCM_CE_N) ? BIT7 : 0)
    _RVM1(0x1E9F, PCM1_CTRL, BIT7),
#endif
#endif

#ifdef PADS_PCM1_AD
#if (PADS_PCM1_AD != Unknown_pad_mux)
#define PCM1_AD   ((PADS_PCM1_AD == PAD_PCM_D7) ? BIT6 : 0)
    _RVM1(0x1E9F, PCM1_AD, BIT6),
#endif
#endif

#ifdef PADS_PCM1_PE
#if (PADS_PCM1_PE != Unknown_pad_mux)
#if (PADS_PCM1_PE == PCM_PE_ON)
        _RVM1(0x1E82, 0xFF, 0xFF),
        _RVM1(0x1E83, 0xFF, 0xFF),
        _RVM1(0x1E84, 0xFF, 0xFF),
        _RVM1(0x1E85, 0xFF, 0x03),
#else
        _RVM1(0x1E82, 0x00, 0xFF),
        _RVM1(0x1E83, 0x00, 0xFF),
        _RVM1(0x1E84, 0x00, 0xFF),
        _RVM1(0x1E85, 0x00, 0x3F),
#endif
#endif
#endif

#ifdef PADS_PCM1_D_PE
#if (PADS_PCM1_D_PE != Unknown_pad_mux)
#define PCM1_D_PE   ((PADS_PCM1_D_PE == PCM_D_PE_ON) ? 0xFF : 0)
        _RVM1(0x1E18, PCM1_D_PE, 0xFF),
#endif
#endif

#ifdef PADS_CI_CTRL
#if (PADS_CI_CTRL != Unknown_pad_mux)
#define CI_CTRL   ((PADS_CI_CTRL == ENABLE) ? BIT1 : 0)
    _RVM1(0x1EC8, CI_CTRL, BIT1),
#endif
#endif

#ifdef PADS_CI_AD
#if (PADS_CI_AD != Unknown_pad_mux)
#define CI_AD   ((PADS_CI_AD == ENABLE) ? BIT0 : 0)
    _RVM1(0x1EC8, CI_AD, BIT0),
#endif
#endif

#ifdef PADS_PCM2_CTRL
#if (PADS_PCM2_CTRL != Unknown_pad_mux)
#define PCM2_CTRL   ((PADS_PCM2_CTRL == ENABLE) ? BIT5 : 0)
    _RVM1(0x1E9F, PCM2_CTRL, BIT5),
#endif
#endif

#ifdef PADS_SPDIF_OUT
#if (PADS_SPDIF_OUT != Unknown_pad_mux)
#define SPDIF_OUT   ((PADS_SPDIF_OUT == PAD_SPDIF_OUT) ? BIT7 : 0)
    _RVM1(0x1EAE, SPDIF_OUT, BIT7),
#endif
#endif

#ifdef PADS_SPDIF_IN
#if (PADS_SPDIF_IN != Unknown_pad_mux)
#define SPDIF_IN   ((PADS_SPDIF_IN == PAD_SPDIF_IN) ? BIT6 : 0)
    _RVM1(0x1EAE, SPDIF_IN, BIT6),
#endif
#endif

#ifdef PADS_I2S_IN
#if (PADS_I2S_IN != Unknown_pad_mux)
#define I2S_IN    ((PADS_I2S_IN == ENABLE) ? BIT2 : 0)
    _RVM1(0x1EAE, I2S_IN, BIT2),
#endif
#endif

#ifdef PADS_I2S_MUTE
#if (PADS_I2S_MUTE != Unknown_pad_mux)
#define I2S_MUTE   ((PADS_I2S_MUTE == PAD_GPIO15) ? BIT6 : \
                    (PADS_I2S_MUTE == PAD_PWM4) ? BIT7 : 0)
    _RVM1(0x1E05, I2S_MUTE, (BIT7 | BIT6)),
#endif
#endif

#ifdef PADS_I2S_OUT
#if (PADS_I2S_OUT != Unknown_pad_mux)
#define I2S_OUT   ((PADS_I2S_OUT == SINGLE_CH_I2S_OUT) ? BIT4 : \
                   (PADS_I2S_OUT == MULTI_CH_I2S_OUT) ? BIT5 : 0)
    _RVM1(0x1EAE, I2S_OUT, (BIT5 | BIT4)),
#endif
#endif

// LED
     _RVM1(0x1EB4, BIT4, BIT4),

#ifdef PADS_MPIF_MODE
#if (PADS_MPIF_MODE != Unknown_pad_mux)
#define MPIF_MODE   ((PADS_MPIF_MODE == ONE_BIT_MODE) ? BIT6 : \
                     (PADS_MPIF_MODE == TWO_BIT_MODE) ? BIT7 : \
                     (PADS_MPIF_MODE == FOUR_BIT_MODE) ? (BIT7 | BIT6) : 0)
    _RVM1(0x1EB5, MPIF_MODE, (BIT7 | BIT6)),
#endif
#endif

#ifdef PADS_ET_MODE
#if (PADS_ET_MODE != Unknown_pad_mux)           //for External Ethernet PHY
#define ET_MODE   ((PADS_ET_MODE == ENABLE) ? BIT0 : 0)
    _RVM1(0x1EDF, ET_MODE, BIT0),
#endif
#endif

#ifdef PADS_3D_FLAG_CONFIG
#if (PADS_3D_FLAG_CONFIG != Unknown_pad_mux)
#define _3D_FLAG_CONFIG   ((PADS_3D_FLAG_CONFIG == PAD_SPDIF_IN) ? BIT6 : \
                           (PADS_3D_FLAG_CONFIG == PAD_GPIO16) ? BIT7 : \
                           (PADS_3D_FLAG_CONFIG == PAD_I2S_IN_SD) ? (BIT7 | BIT6) : 0)
    _RVM1(0x1EB1, _3D_FLAG_CONFIG, (BIT7 | BIT6)),
#endif
#endif

//==========
// UART Modes
//==========
#ifdef PADS_UART2_MODE
#if (PADS_UART2_MODE != Unknown_pad_mux)
#define UART2_MODE   ((PADS_UART2_MODE == PAD_GPIO7) ? BIT0 : \
                      (PADS_UART2_MODE == PAD_GPIO8) ? BIT0 : \
                      (PADS_UART2_MODE == PAD_GPIO19) ? BIT1 : \
                      (PADS_UART2_MODE == PAD_GPIO20) ? BIT1 : \
                      (PADS_UART2_MODE == PAD_GPIO3) ? (BIT1 | BIT0) : \
                      (PADS_UART2_MODE == PAD_GPIO4) ? (BIT1 | BIT0) : 0 )
    _RVM1(0x1E05, UART2_MODE, (BIT1 | BIT0)),
#endif
#endif

#ifdef PADS_UART3_MODE
#if (PADS_UART3_MODE != Unknown_pad_mux)
#define UART3_MODE   ((PADS_UART3_MODE == PAD_GPIO9) ? BIT2: \
                      (PADS_UART3_MODE == PAD_GPIO10) ? BIT2: \
                      (PADS_UART3_MODE == PAD_I2S_IN_WS) ? BIT3: \
                      (PADS_UART3_MODE == PAD_I2S_IN_BCK) ? BIT3: \
                      (PADS_UART3_MODE == PAD_UART_TX2) ? (BIT3 | BIT2) : \
                      (PADS_UART3_MODE == PAD_UART_RX2) ? (BIT3 | BIT2) : 0 )
    _RVM1(0x1E05, UART3_MODE, (BIT3 | BIT2)),
#endif
#endif

#ifdef PADS_UART4_MODE
#if (PADS_UART4_MODE != Unknown_pad_mux)
#define UART4_MODE   ((PADS_UART4_MODE == PAD_GPIO11) ? BIT6: \
                      (PADS_UART4_MODE == PAD_GPIO12) ? BIT6: \
                      (PADS_UART4_MODE == PAD_GPIO23) ? BIT7: \
                      (PADS_UART4_MODE == PAD_GPIO24) ? BIT7: \
                      (PADS_UART4_MODE == PAD_I2S_OUT_SD2) ? (BIT7 | BIT6) : \
                      (PADS_UART4_MODE == PAD_I2S_OUT_SD3) ? (BIT7 | BIT6) : 0 )
    _RVM1(0x1E04, UART4_MODE, (BIT7 | BIT6)),
#endif
#endif

#ifdef PADS_FAST_UART_MODE
#if (PADS_FAST_UART_MODE != Unknown_pad_mux)
#define FAST_UART_MODE   ((PADS_FAST_UART_MODE == PAD_GPIO5) ? BIT4 : \
                          (PADS_FAST_UART_MODE == PAD_GPIO6) ? BIT4 : \
                          (PADS_FAST_UART_MODE == PAD_GPIO25) ? BIT5 : \
                          (PADS_FAST_UART_MODE == PAD_GPIO26) ? BIT5 : \
                          (PADS_FAST_UART_MODE == PAD_GPIO13) ? (BIT5 | BIT4) : \
                          (PADS_FAST_UART_MODE == PAD_GPIO14) ? (BIT5 | BIT4) : 0 )
    _RVM1(0x1E04, FAST_UART_MODE, (BIT5 | BIT4)),
#endif
#endif

//==========
// UART Select
//==========
#define UART_INV    ((UART0_INV ? BIT0 : 0) | \
                     (UART1_INV ? BIT1 : 0) | \
                     (UART2_INV ? BIT2 : 0) | \
                     (UART3_INV ? BIT3 : 0) | \
                     (UART4_INV ? BIT4 : 0))

    _RVM1(0x1EAB, UART_INV, BITMASK(7:0)),
    _RVM1(0x1EA6, (UART1_SRC_SEL << 4) | (UART0_SRC_SEL << 0), BITMASK(7:0)),
    _RVM1(0x1EA7, (UART3_SRC_SEL << 4) | (UART2_SRC_SEL << 0), BITMASK(7:0)),
    _RVM1(0x1EA8, (UART4_SRC_SEL << 0), BITMASK(3:0)),

#ifdef PADS_PWM0_MODE
#if (PADS_PWM0_MODE != Unknown_pad_mux)
#define PWM0_MODE   ((PADS_PWM0_MODE == PAD_PWM0) ? BIT0:  0)
    _RVM1(0x1EA2, PWM0_MODE, BIT0),
#endif
#endif

#ifdef PADS_PWM1_MODE
#if (PADS_PWM1_MODE != Unknown_pad_mux)
#define PWM1_MODE   ((PADS_PWM1_MODE == PAD_PWM1) ? BIT1:  0)
    _RVM1(0x1EA2, PWM1_MODE, BIT1),
#endif
#endif

#ifdef PADS_PWM2_MODE
#if (PADS_PWM2_MODE != Unknown_pad_mux)
#define PWM2_MODE   ((PADS_PWM2_MODE == PAD_PWM2) ? BIT2:  0)
    _RVM1(0x1EA2, PWM2_MODE, BIT2),
#endif
#endif

#ifdef PADS_PWM3_MODE
#if (PADS_PWM3_MODE != Unknown_pad_mux)
#define PWM3_MODE   ((PADS_PWM3_MODE == PAD_PWM3) ? BIT3:  0)
    _RVM1(0x1EA2, PWM3_MODE, BIT3),
#endif
#endif

#ifdef PADS_PWM4_MODE
#if (PADS_PWM4_MODE != Unknown_pad_mux)
#define PWM4_MODE   ((PADS_PWM4_MODE == PAD_PWM4) ? BIT4 : 0)
    _RVM1(0x1EA2, PWM4_MODE, (BIT5 | BIT4)),
#endif
#endif

#ifdef PADS_PWM5_MODE
#if (PADS_PWM5_MODE != Unknown_pad_mux)
#define PWM5_MODE   ((PADS_PWM5_MODE == PAD_D3P) ? BIT0 : \
                     (PADS_PWM5_MODE == PAD_VSYNC_LIKE) ? BIT1 : \
                     (PADS_PWM5_MODE == PAD_ACKP) ? (BIT1 | BIT0) : 0)
    _RVM1(0x1EB2, PWM5_MODE, (BIT1 | BIT0)),
#endif
#endif

#ifdef PADS_NAND_CS1_EN
#if (PADS_NAND_CS1_EN != Unknown_pad_mux)
#define NAND_CS1_EN   ((PADS_NAND_CS1_EN == PAD_NAND_CEZ1) ? BIT2 : 0)
    _RVM1(0x1EA1, NAND_CS1_EN, BIT2),
#endif
#endif

#ifdef PADS_NAND_CS2_EN
#if (PADS_NAND_CS2_EN != Unknown_pad_mux)
#define NAND_CS2_EN   ((PADS_NAND_CS2_EN == PAD_EMMC_CMD) ? BIT0 : 0)
    _RVM1(0x1E16, NAND_CS1_EN, BIT0),
#endif
#endif

#ifdef PADS_NAND_CS3_EN
#if (PADS_NAND_CS3_EN != Unknown_pad_mux)
#define NAND_CS3_EN   ((PADS_NAND_CS3_EN == PAD_EMMC_RSTN) ? BIT1 : 0)
    _RVM1(0x1E16, NAND_CS3_EN, BIT1),
#endif
#endif

#ifdef PADS_TSERR_OUT
#if (PADS_TSERR_OUT != Unknown_pad_mux)
#define TSERR_OUT   ((PADS_TSERR_OUT == PAD_I2S_IN_SD) ? BIT7 :  \
                     (PADS_TSERR_OUT == PAD_GPIO16) ? BIT8 :  \
                     (PADS_TSERR_OUT == PAD_PWM4) ? (BIT8 | BIT7) : 0)
    _RVM2(0x1EA2, TSERR_OUT, (BIT8 | BIT7)),
#endif
#endif

#ifdef PADS_BT656_CTRL
#if (PADS_BT656_CTRL != Unknown_pad_mux)
#define BT656_CTR   ((PADS_BT656_CTRL == TS1_PADs) ? BIT6:  \
                     (PADS_BT656_CTRL == PCM_PADs) ? BIT7:  \
                     (PADS_BT656_CTRL == GPIO_PADs) ? (BIT7 | BIT6) : 0)
    _RVM1(0x1EDF, BT656_CTR, (BIT7 | BIT6)),
#endif
#endif

#ifdef PADS_DDCR_MODE
#if (PADS_DDCR_MODE != Unknown_pad_mux)
#define DDCR_MODE   ((PADS_DDCR_MODE == DDCR_PADs) ? BIT0 : \
                     (PADS_DDCR_MODE == IIC_PADs) ? BIT1 : 0)
        _RVM1(0x1EAE, DDCR_MODE, (BIT1 | BIT0)),
#endif
#endif

#ifdef PADS_MIIC_MODE0
#if (PADS_MIIC_MODE0 != Unknown_pad_mux)
#define MIIC_MODE0  ((PADS_MIIC_MODE0 == PAD_GPIO17) ? BIT0 :  \
                     (PADS_MIIC_MODE0 == PAD_GPIO18) ? BIT0 :  \
                     (PADS_MIIC_MODE0 == PAD_TS1_CLK) ? BIT1 :  \
                     (PADS_MIIC_MODE0 == PAD_TS1_SYNC) ? BIT1 : 0)
    _RVM1(0x1EB5, MIIC_MODE0, (BIT1 | BIT0)),
#endif
#endif

//PAD_TS1_VLD & PAD_TS1_D0: priority => miic_mode1 higher than miic_mode2
#ifdef PADS_MIIC_MODE1
#if (PADS_MIIC_MODE1 != Unknown_pad_mux)
#define MIIC_MODE1  ((PADS_MIIC_MODE1 == PAD_TGPIO2) ? BIT2 :  \
                     (PADS_MIIC_MODE1 == PAD_TGPIO3) ? BIT2 :  \
                     (PADS_MIIC_MODE1 == PAD_TS1_VLD) ? BIT3 :  \
                     (PADS_MIIC_MODE1 == PAD_TS1_D0) ? BIT3 : 0)
    _RVM1(0x1EB5, MIIC_MODE1, (BIT3 | BIT2)),
#endif
#endif

#ifdef PADS_MIIC_MODE2
#if (PADS_MIIC_MODE2 != Unknown_pad_mux)
#define MIIC_MODE2  ((PADS_MIIC_MODE2 == PAD_I2S_IN_BCK) ? BIT4 :  \
                     (PADS_MIIC_MODE2 == PAD_I2S_IN_SD) ? BIT4 :  \
                     (PADS_MIIC_MODE2 == PAD_TS1_VLD) ? BIT5 :  \
                     (PADS_MIIC_MODE2 == PAD_TS1_D0) ? BIT5 : 0)
    _RVM1(0x1EB5, MIIC_MODE2, (BIT5 | BIT4)),
#endif
#endif

#ifdef PADS_SM_MODE
#if (PADS_SM_MODE != Unknown_pad_mux)
#define SM_MODE     ((PADS_SM_MODE == SMART_CARD_PWM) ? BIT2:  \
                     (PADS_SM_MODE == SMART_CARD_TS1) ? BIT3: \
                     (PADS_SM_MODE == SMART_CARD_PCM) ? (BIT3 | BIT2) : 0)
    _RVM1(0x1E17, SM_MODE, (BIT3 | BIT2)),

#if (PADS_SM_MODE == SMART_CARD_PCM)
    _RVM1(0x1EC8, 0, BIT1),
    _RVM1(0x1E9F, 0, BIT7),
#endif
#endif

//#if (SMART_SOURCE == SMART_CARD_VCC_3P3V)
//     _RVM1(0x1E24, 0, BIT2|BIT1|BIT0),
//     _RVM1(0x1EAF, 0, BIT5|BIT4|BIT3),
//     _RVM1(0x2BB6, 0,BIT0),
//#endif
//
//#if (SMART_SOURCE == SMART_CARD_VCC_5V)
//#if (PADS_SM_MODE == SMART_CARD_PCM)
//     _RVM1(0x2BB6, 1, BIT0),
//#endif
//#if (PADS_SM_MODE == SMART_CARD_TS1)
//     _RVM1(0x1E24, 0, BIT2|BIT1|BIT0),
//     _RVM1(0x1EAF, 0, BIT5|BIT4|BIT3),
//     _RVM1(0x2BB6, 1, BIT0),
//#endif
//#endif
#endif

#ifdef PADS_SD0_MODE
#if (PADS_SD0_MODE != Unknown_pad_mux)
#define SD_MODE   ((PADS_SD_MODE == PCM_A) ? BIT3 : \
                   (PADS_SD_MODE == PCM_D) ? BIT2 : 0)
    _RVM1(0x1E16, SD_MODE, (BIT3 | BIT2)),
#endif
#endif

#ifdef PADS_SD1_MODE
#if (PADS_SD1_MODE != Unknown_pad_mux)
#define SD_MODE   ((PADS_SD_MODE == PCM_A) ? BIT7 : \
                   (PADS_SD_MODE == PCM_D) ? BIT6 : 0)
    _RVM1(0x1E16, SD_MODE, (BIT7 | BIT6)),
#endif
#endif

#ifdef PADS_EMMC_MODE
#if (PADS_EMMC_MODE != Unknown_pad_mux)
#define EMMC_MODE   ((PADS_EMMC_MODE == NAND_DATA) ? BIT6 : \
                     (PADS_EMMC_MODE == NAND_CTRL) ? (BIT7 | BIT6) : 0)
    _RVM1(0x1EBB, EMMC_MODE, (BIT7 | BIT6)),
#endif
#endif

#ifdef PADS_PDTRACE_MODE
#if (PADS_PDTRACE_MODE != Unknown_pad_mux)
#define _CONFIG_PDTRACE_MODE   ((PADS_PDTRACE_MODE == PADS_TS1) ? BIT0 : \
                                (PADS_PDTRACE_MODE == PADS_GPIO) ? BIT1 : 0)
    _RVM1(0x1E9F _CONFIG_PDTRACE_MODE, (BIT1 | BIT0)),
#endif
#endif

#ifdef ENABLE_EXT_GPIO_INT0
#define _CONFIG_EXT_GPIO_INT0   ((ENABLE_EXT_GPIO_INT0 == ENABLE) ? BIT0 : 0)
    _RVM1(0x1EE0, _CONFIG_EXT_GPIO_INT0, BIT0),
#endif

#ifdef ENABLE_EXT_GPIO_INT1
#define _CONFIG_EXT_GPIO_INT1   ((ENABLE_EXT_GPIO_INT1 == ENABLE) ? BIT1 : 0)
    _RVM1(0x1EE0, _CONFIG_EXT_GPIO_INT1, BIT1),
#endif

#ifdef ENABLE_EXT_GPIO_INT2
#define _CONFIG_EXT_GPIO_INT2   ((ENABLE_EXT_GPIO_INT2 == ENABLE) ? BIT2 : 0)
    _RVM1(0x1EE0, _CONFIG_EXT_GPIO_INT0, BIT2),
#endif

#ifdef ENABLE_EXT_GPIO_INT3
#define _CONFIG_EXT_GPIO_INT3   ((ENABLE_EXT_GPIO_INT3 == ENABLE) ? BIT3 : 0)
    _RVM1(0x1EE0, _CONFIG_EXT_GPIO_INT0, BIT3),
#endif

#ifdef ENABLE_EXT_GPIO_INT4
#define _CONFIG_EXT_GPIO_INT4   ((ENABLE_EXT_GPIO_INT4 == ENABLE) ? BIT4 : 0)
    _RVM1(0x1EE0, _CONFIG_EXT_GPIO_INT4, BIT4),
#endif

#ifdef ENABLE_EXT_GPIO_INT5
#define _CONFIG_EXT_GPIO_INT5   ((ENABLE_EXT_GPIO_INT0 == ENABLE) ? BIT5 : 0)
    _RVM1(0x1EE0, _CONFIG_EXT_GPIO_INT5, BIT5),
#endif

#ifdef ENABLE_EXT_GPIO_INT6
#define _CONFIG_EXT_GPIO_INT6   ((ENABLE_EXT_GPIO_INT6 == ENABLE) ? BIT6 : 0)
    _RVM1(0x1EE0, _CONFIG_EXT_GPIO_INT6, BIT6),
#endif

#ifdef ENABLE_EXT_GPIO_INT7
#define _CONFIG_EXT_GPIO_INT7   ((ENABLE_EXT_GPIO_INT7 == ENABLE) ? BIT7 : 0)
    _RVM1(0x1EE0, _CONFIG_EXT_GPIO_INT7, BIT7),
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

#define SET_P1 P1_B0 | P1_B1 | P1_B2 | P1_B3 | P1_B4 | P1_B5 | P1_B6 | P1_B7
    _RVM3(0x1EB8, SET_P1, 0xFF),
#endif

    _MEMMAP_PM_,

    _RVM1(0x0E13, BIT3, BIT3),      // RX0_ENABLE
    _RVM1(0x0E13, 0,    BIT4),      // UART0 -> reg_uart_sel0

    _MEMMAP_nonPM_,

    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7=0

    _END_OF_TBL_,

//=================================================================================================
    //external flash #1
    _MEMMAP_PM_,
    _RVM1(0x0E6A, 0x00, BIT0), //reg_spi_gpio set to 0 (swtch to spi_do, spi_di, spi_ck)
    _RVM1(0x0E6A, 0x00, BIT1), //reg_spicsz0_gpio set to 0 (enable spi_cz0)
    _RVM1(0x08F4, 0x00, 0xFF), //reg_chip_select set to 0 (select embedded SPI Flash)
#if (PIN_FLASH_WP0)
    _RVM1(0x0e20, BIT0, BIT0), //PM0
    _RVM1(0x0E1E,    0, BIT0),
#endif
    _END_OF_TBL_,

    //external flash #2
    _MEMMAP_PM_,
    _RVM1(0x0E6A, 0x00, BIT0), //reg_spi_gpio set to 0 (swtch to spi_do, spi_di, spi_ck)
#if (PIN_SPI_CZ1)
    _RVM1(0x0E6A, 0x00, BIT2), //reg_spicsz1_gpio set to 0 (enable spi_cz1)
    _RVM1(0x08F4, 0x01, 0xFF), //reg_chip_select set to 1 (select external flash #1)
#if (PIN_FLASH_WP1)
    _RVM1(0x0E21, BIT0, BIT0), //PM8
    _RVM1(0x0E1F,    0, BIT0),
#endif
    _END_OF_TBL_,
#endif

//=================================================================================================

};

//-----------------------------------------------------------------
// Sanity check for PAD_TOP setting (TODO)
//-----------------------------------------------------------------

#if (UART0_SRC_SEL == UART1_SRC_SEL) || \
    (UART0_SRC_SEL == UART2_SRC_SEL) || \
    (UART1_SRC_SEL == UART2_SRC_SEL)
    #error "UART src selection conflict"
#endif

#if 0//alex_tung###
#if 0
    // ET
    #define ET_IS_GPIO      ((PAD_ET_COL_IS_GPIO | \
                              PAD_ET_TXD1_IS_GPIO | \
                              PAD_ET_TXD0_IS_GPIO | \
                              PAD_ET_TX_EN_IS_GPIO | \
                              PAD_ET_TX_CLK_IS_GPIO | \
                              PAD_ET_RXD0_IS_GPIO | \
                              PAD_ET_RXD1_IS_GPIO | \
                              PAD_ET_MDC_IS_GPIO | \
                              PAD_ET_MDIO_IS_GPIO) ? BIT2 : 0)

    #define ET_OEN          ((PAD_ET_COL_IS_GPIO == GPIO_IN ? (1UL << 0) : 0) | \
                             (PAD_ET_TXD1_IS_GPIO == GPIO_IN ? (1UL << 1) : 0) | \
                             (PAD_ET_TXD0_IS_GPIO == GPIO_IN ? (1UL << 2) : 0) | \
                             (PAD_ET_TX_EN_IS_GPIO  == GPIO_IN ? (1UL << 3) : 0) | \
                             (PAD_ET_TX_CLK_IS_GPIO  == GPIO_IN ? (1UL << 4) : 0) | \
                             (PAD_ET_RXD0_IS_GPIO  == GPIO_IN ? (1UL << 5) : 0) | \
                             (PAD_ET_RXD1_IS_GPIO  == GPIO_IN ? (1UL << 6) : 0) | \
                             (PAD_ET_MDC_IS_GPIO  == GPIO_IN ? (1UL << 7) : 0) | \
                             (PAD_ET_MDIO_IS_GPIO  == GPIO_IN ? (1UL << 8) : 0))

    #define ET_OUT          ((PAD_ET_COL_IS_GPIO == GPIO_OUT_HIGH ? (1UL << 0) : 0) | \
                             (PAD_ET_TXD1_IS_GPIO == GPIO_OUT_HIGH ? (1UL << 1) : 0) | \
                             (PAD_ET_TXD0_IS_GPIO == GPIO_OUT_HIGH ? (1UL << 2) : 0) | \
                             (PAD_ET_TX_EN_IS_GPIO  == GPIO_OUT_HIGH ? (1UL << 3) : 0) | \
                             (PAD_ET_TX_CLK_IS_GPIO  == GPIO_OUT_HIGH ? (1UL << 4) : 0) | \
                             (PAD_ET_RXD0_IS_GPIO  == GPIO_OUT_HIGH ? (1UL << 5) : 0) | \
                             (PAD_ET_RXD1_IS_GPIO  == GPIO_OUT_HIGH ? (1UL << 6) : 0) | \
                             (PAD_ET_MDC_IS_GPIO  == GPIO_OUT_HIGH ? (1UL << 7) : 0) | \
                             (PAD_ET_MDIO_IS_GPIO  == GPIO_OUT_HIGH ? (1UL << 8) : 0))

    _RVM2(0x1E84, ET_OUT, 0x01FF),
    _RVM2(0x1E86, ET_OEN, 0x01FF),
    _RVM1(0x1EDF, ET_IS_GPIO, BIT2),
#endif

    // I2S,SPDIF,
    #define I2S_IS_GPIO     ((PAD_I2S_IN_WS_IS_GPIO ? (1UL << 5) : 0) | \
                             (PAD_I2S_IN_BCK_IS_GPIO ? (1UL << 5) : 0) | \
                             (PAD_I2S_IN_SD_IS_GPIO ? (1UL << 5) : 0) | \
                             (PAD_I2S_OUT_MCK_IS_GPIO ? (1UL << 6) : 0) | \
                             (PAD_I2S_OUT_WS_IS_GPIO ? (1UL << 6) : 0) | \
                             (PAD_I2S_OUT_BCK_IS_GPIO ? (1UL << 6) : 0) | \
                             (PAD_I2S_OUT_SD_IS_GPIO ? (1UL << 6) : 0))

    #define I2S_OUT_IS_GPIO_NONE  ((PAD_I2S_OUT_MCK_IS_GPIO | \
                                    PAD_I2S_OUT_WS_IS_GPIO  | \
                                    PAD_I2S_OUT_BCK_IS_GPIO | \
                                    PAD_I2S_OUT_SD_IS_GPIO) ? 0 : 3)

    #define I2S_SD_IS_GPIO  (((PAD_I2S_OUT_SD1_IS_GPIO & I2S_OUT_IS_GPIO_NONE) ? (1UL << 2) : 0) | \
                             ((PAD_I2S_OUT_SD2_IS_GPIO & I2S_OUT_IS_GPIO_NONE) ? (1UL << 2) : 0) | \
                             ((PAD_I2S_OUT_SD3_IS_GPIO & I2S_OUT_IS_GPIO_NONE) ? (1UL << 2) : 0))

    #define SPDIF_IS_GPIO   ((PAD_SPDIF_IN_IS_GPIO ? (1UL << 6) : 0) | \
                             (PAD_SPDIF_OUT_IS_GPIO ? (1UL << 7) : 0))

    #define I2S_SPDIF_OEN   ((PAD_I2S_IN_WS_IS_GPIO     == GPIO_IN ? (1UL << 0) : 0) | \
                             (PAD_I2S_IN_BCK_IS_GPIO    == GPIO_IN ? (1UL << 1) : 0) | \
                             (PAD_I2S_IN_SD_IS_GPIO     == GPIO_IN ? (1UL << 2) : 0) | \
                             (PAD_SPDIF_IN_IS_GPIO      == GPIO_IN ? (1UL << 3) : 0) | \
                             (PAD_SPDIF_OUT_IS_GPIO     == GPIO_IN ? (1UL << 4) : 0) | \
                             (PAD_I2S_OUT_MCK_IS_GPIO   == GPIO_IN ? (1UL << 5) : 0) | \
                             (PAD_I2S_OUT_WS_IS_GPIO    == GPIO_IN ? (1UL << 6) : 0) | \
                             (PAD_I2S_OUT_BCK_IS_GPIO   == GPIO_IN ? (1UL << 7) : 0) | \
                             (PAD_I2S_OUT_SD_IS_GPIO    == GPIO_IN ? (1UL << 8) : 0) | \
                             (PAD_I2S_OUT_SD1_IS_GPIO   == GPIO_IN ? (1UL << 9) : 0) | \
                             (PAD_I2S_OUT_SD2_IS_GPIO   == GPIO_IN ? (1UL << 10) : 0) | \
                             (PAD_I2S_OUT_SD3_IS_GPIO   == GPIO_IN ? (1UL << 11) : 0))

    #define I2S_SPDIF_OUT   ((PAD_I2S_IN_WS_IS_GPIO     == GPIO_OUT_HIGH ? (1UL << 0) : 0) | \
                             (PAD_I2S_IN_BCK_IS_GPIO    == GPIO_OUT_HIGH ? (1UL << 1) : 0) | \
                             (PAD_I2S_IN_SD_IS_GPIO     == GPIO_OUT_HIGH ? (1UL << 2) : 0) | \
                             (PAD_SPDIF_IN_IS_GPIO      == GPIO_OUT_HIGH ? (1UL << 3) : 0) | \
                             (PAD_SPDIF_OUT_IS_GPIO     == GPIO_OUT_HIGH ? (1UL << 4) : 0) | \
                             (PAD_I2S_OUT_MCK_IS_GPIO   == GPIO_OUT_HIGH ? (1UL << 5) : 0) | \
                             (PAD_I2S_OUT_WS_IS_GPIO    == GPIO_OUT_HIGH ? (1UL << 6) : 0) | \
                             (PAD_I2S_OUT_BCK_IS_GPIO   == GPIO_OUT_HIGH ? (1UL << 7) : 0) | \
                             (PAD_I2S_OUT_SD_IS_GPIO    == GPIO_OUT_HIGH ? (1UL << 8) : 0) | \
                             (PAD_I2S_OUT_SD1_IS_GPIO   == GPIO_OUT_HIGH ? (1UL << 9) : 0) | \
                             (PAD_I2S_OUT_SD2_IS_GPIO   == GPIO_OUT_HIGH ? (1UL << 10) : 0) | \
                             (PAD_I2S_OUT_SD3_IS_GPIO   == GPIO_OUT_HIGH ? (1UL << 11) : 0))

    _RVM2(0x1E6C, I2S_SPDIF_OUT, 0x0FFF),
    _RVM2(0x1E6E, I2S_SPDIF_OEN, 0x0FFF),
    _RVM1(0x1EE1, SPDIF_IS_GPIO, BIT7|BIT6),
    _RVM1(0x1EA2, I2S_IS_GPIO, BIT6|BIT5),
    _RVM1(0x1EA1, I2S_SD_IS_GPIO, BIT2),

    #if(PAD_PCM_WE_N_IS_GPIO != GPIO_NONE)
    #define PAD_PCM_WE_N_OEN (PAD_PCM_WE_N_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_PCM_WE_N_OUT (PAD_PCM_WE_N_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e78, PAD_PCM_WE_N_OUT, BIT2),
    _RVM1(0x1e7E, PAD_PCM_WE_N_OEN, BIT2),
    _RVM1(0x1ee0, BIT5, BIT5),
    #endif

#endif
