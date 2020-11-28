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
#include "hwreg_monet.h"
#include "chip/bond.h"

#define GPIO_NONE                   0       // Not GPIO pin (default)
#define GPIO_IN                     1       // GPI
#define GPIO_OUT_LOW                2       // GPO output low
#define GPIO_OUT_HIGH               3       // GPO output high

#if defined(ARM_CHAKRA) || defined(MIPS_CHAKRA) || defined(MSOS_TYPE_LINUX)
#define _MapBase_nonPM_MONET        (RIU_MAP + 0x00200000)
#define _MapBase_PM_MONET           RIU_MAP
#else
#define _MapBase_nonPM_MONET        0xa0200000
#define _MapBase_PM_MONET           0xa0000000
#endif

#define _MEMMAP_nonPM_              _RVM1(0x0000, 0x10, 0xFF)
#define _MEMMAP_PM_                 _RVM1(0x0000, 0x00, 0xFF)

const U8 padInitTbl_PreInit[] =
{
    0xFF, 0xFF, 0xFF, 0xFF,     // magic code for ISP_Tool

    // programable device number
    // spi flash count
    0,
    0x00,                       // nor
    0x00,                       // nand
    0x00,                       // reserved
    0x00,                       // reserved
    0x00,                       // reserved

//---------------------------------------------------------------------
// GPIO Configuartion
//---------------------------------------------------------------------
    _MEMMAP_PM_,

    #if(PAD_VID0_IS_GPIO != GPIO_NONE)
        #define PAD_VID0_OEN (PAD_VID0_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_VID0_OUT (PAD_VID0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2e84, PAD_VID0_OUT, BIT0),
        _RVM1(0x2e84, PAD_VID0_OEN, BIT1),
        //reg_vid_is_gpio
        _RVM1(0x0efb, BIT0, BIT0),   //reg[0efb]#0 = 1
        #undef PAD_VID0_IS_GPIO
        #define PAD_VID0_IS_GPIO    GPIO_NONE
    #endif

    #if(PAD_VID1_IS_GPIO != GPIO_NONE)
        #define PAD_VID1_OEN (PAD_VID1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_VID1_OUT (PAD_VID1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2e85, PAD_VID1_OUT, BIT0),
        _RVM1(0x2e85, PAD_VID1_OEN, BIT1),
        //reg_sar_aisel[4]
        _RVM1(0x1422, 0, BIT4),   //reg[1422]#4 = 0
        #undef PAD_VID1_IS_GPIO
        #define PAD_VID1_IS_GPIO    GPIO_NONE
    #endif

    _MEMMAP_nonPM_,

//---------------------------------------------------------------------
// Pad Configuartion
//---------------------------------------------------------------------

//=============================================================================
#ifdef PADS_NAND_MODE
    #if (PADS_NAND_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_NAND_MODE   ((PADS_NAND_MODE == PAD_PCM_A) ? BIT4 : 0)
        _RVM1(0x1e17, _CONFIG_NAND_MODE, (BIT6 | BIT5 | BIT4)),

    #if (PADS_NAND_MODE == PAD_PCM_A)
        _RVM2(0x1e18, BITMASK(7:0), BITMASK(7:0)),
    #endif

    #else
        _RVM1(0x1e17, 0, (BIT6 | BIT5 | BIT4)),
    #endif
#endif

#ifdef PADS_NAND_CS1_EN
    #if (PADS_NAND_CS1_EN != UNKNOWN_PAD_MUX)
    #define _CONFIG_NAND_CS1_EN ((PADS_NAND_CS1_EN == ENABLE) ? BIT2 : 0)
        _RVM1(0x1ea1, _CONFIG_NAND_CS1_EN, BIT2),
    #endif
#endif

#ifdef PADS_NAND_CS2_EN
    #if (PADS_NAND_CS2_EN != UNKNOWN_PAD_MUX)
    #define _CONFIG_NAND_CS2_EN ((PADS_NAND_CS2_EN == ENABLE) ? BIT0 : 0)
        _RVM1(0x1e16, _CONFIG_NAND_CS2_EN, BIT0),
    #endif
#endif

#ifdef PADS_NAND_CS3_EN
    #if (PADS_NAND_CS3_EN != UNKNOWN_PAD_MUX)
    #define _CONFIG_NAND_CS3_EN ((PADS_NAND_CS3_EN == ENABLE) ? BIT1 : 0)
        _RVM1(0x1e16, _CONFIG_NAND_CS3_EN, BIT1),
    #endif
#endif

#ifdef PADS_NAND_PE
    #if (PADS_NAND_PE == ENABLE)
        _RVM1(0x1ed6, BITMASK(7:0), BITMASK(7:0)),
        _RVM1(0x1ed7, BIT0, BIT0),
    #else
        _RVM1(0x1ed6, 0, BITMASK(7:0)),
        _RVM1(0x1ed7, 0, BIT0),
    #endif
#endif

//=============================================================================
#ifdef PADS_EMMC_MODE
    #if (PADS_EMMC_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_EMMC_MODE   ((PADS_EMMC_MODE == PAD_NAND_CTRL) ? BIT6 : 0)
        _RVM1(0x1ebb, _CONFIG_EMMC_MODE, (BIT7 | BIT6)),
    #else
        _RVM1(0x1ebb, 0, (BIT7 | BIT6)),
    #endif
#endif

//=============================================================================
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7),     //reg[101ea1]#7 = 0b
    _END_OF_TBL_,
};

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
    #endif

    #if(PAD_PM_SPI_CK_IS_GPIO != GPIO_NONE)
        #define PAD_PM_SPI_CK_OEN (PAD_PM_SPI_CK_IS_GPIO == GPIO_IN ? BIT5: 0)
        #define PAD_PM_SPI_CK_OUT (PAD_PM_SPI_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
        _RVM1(0x0e3a, PAD_PM_SPI_CK_OUT, BIT5),
        _RVM1(0x0e3c, PAD_PM_SPI_CK_OEN, BIT5),
        //reg_spi_gpio
        _RVM1(0x0e6a, BIT0, BIT0),   //reg[0e6a]#0 = 1
    #endif

    #if(PAD_PM_SPI_DI_IS_GPIO != GPIO_NONE)
        #define PAD_PM_SPI_DI_OEN (PAD_PM_SPI_DI_IS_GPIO == GPIO_IN ? BIT6: 0)
        #define PAD_PM_SPI_DI_OUT (PAD_PM_SPI_DI_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x0e3a, PAD_PM_SPI_DI_OUT, BIT6),
        _RVM1(0x0e3c, PAD_PM_SPI_DI_OEN, BIT6),
        //reg_spi_gpio
        _RVM1(0x0e6a, BIT0, BIT0),   //reg[0e6a]#0 = 1
    #endif

    #if(PAD_PM_SPI_DO_IS_GPIO != GPIO_NONE)
        #define PAD_PM_SPI_DO_OEN (PAD_PM_SPI_DO_IS_GPIO == GPIO_IN ? BIT7: 0)
        #define PAD_PM_SPI_DO_OUT (PAD_PM_SPI_DO_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
        _RVM1(0x0e3a, PAD_PM_SPI_DO_OUT, BIT7),
        _RVM1(0x0e3c, PAD_PM_SPI_DO_OEN, BIT7),
        //reg_spi_gpio
        _RVM1(0x0e6a, BIT0, BIT0),   //reg[0e6a]#0 = 1
    #endif

    #if(PAD_IRIN_IS_GPIO != GPIO_NONE)
        #define PAD_IRIN_OEN (PAD_IRIN_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_IRIN_OUT (PAD_IRIN_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x0e3a, PAD_IRIN_OUT, BIT0),
        _RVM1(0x0e3c, PAD_IRIN_OEN, BIT0),
        //reg_ir_is_gpio
        _RVM1(0x0e38, BIT4, BIT4),   //reg[0e38]#4 = 1
    #endif

    #if(PAD_CEC_IS_GPIO != GPIO_NONE)
        #define PAD_CEC_OEN (PAD_CEC_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_CEC_OUT (PAD_CEC_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x0e3a, PAD_CEC_OUT, BIT2),
        _RVM1(0x0e3c, PAD_CEC_OEN, BIT2),
        //reg_cec_is_gpio
        _RVM1(0x0e38, BIT6, BIT6),   //reg[0e38]#6 = 1
    #endif

    #if(PAD_AV_LNK_IS_GPIO != GPIO_NONE)
        #define PAD_AV_LNK_OEN (PAD_AV_LNK_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_AV_LNK_OUT (PAD_AV_LNK_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
        _RVM1(0x0e3a, PAD_AV_LNK_OUT, BIT3),
        _RVM1(0x0e3c, PAD_AV_LNK_OEN, BIT3),
        //reg_av_lnk_is_gpio
        _RVM1(0x0e38, BIT7, BIT7),   //reg[0e38]#7 = 1
    #endif

    #if(PAD_PWM_PM_IS_GPIO != GPIO_NONE)
        #define PAD_PWM_PM_OEN (PAD_PWM_PM_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PWM_PM_OUT (PAD_PWM_PM_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x0e3a, PAD_PWM_PM_OUT, BIT1),
        _RVM1(0x0e3c, PAD_PWM_PM_OEN, BIT1),
        //reg_test_out_mode[0]
        //_RVM1(0x1e24, 0, BIT4),   //reg[101e24]#4 = 0
        //reg_pwm_pm_is_gpio
        _RVM1(0x0e38, BIT5, BIT5),   //reg[0e38]#5 = 1
    #endif

    #if(PAD_DDCA_CK_IS_GPIO != GPIO_NONE)
        #define PAD_DDCA_CK_OEN (PAD_DDCA_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_DDCA_CK_OUT (PAD_DDCA_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x0494, PAD_DDCA_CK_OUT, BIT2),
        _RVM1(0x0494, PAD_DDCA_CK_OEN, BIT1),
        //reg_gpio2a0_en
        _RVM1(0x0494, BIT7, BIT7),   //reg[0494]#7 = 1
    #endif

    #if(PAD_DDCA_DA_IS_GPIO != GPIO_NONE)
        #define PAD_DDCA_DA_OEN (PAD_DDCA_DA_IS_GPIO == GPIO_IN ? BIT5: 0)
        #define PAD_DDCA_DA_OUT (PAD_DDCA_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x0494, PAD_DDCA_DA_OUT, BIT6),
        _RVM1(0x0494, PAD_DDCA_DA_OEN, BIT5),
        //reg_gpio2a0_en
        _RVM1(0x0494, BIT7, BIT7),   //reg[0494]#7 = 1
    #endif

    #if(PAD_GPIO_PM0_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO_PM0_OEN (PAD_GPIO_PM0_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_GPIO_PM0_OUT (PAD_GPIO_PM0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x0e20, PAD_GPIO_PM0_OUT, BIT0),
        _RVM1(0x0e1e, PAD_GPIO_PM0_OEN, BIT0),
    #endif

    #if(PAD_GPIO_PM1_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO_PM1_OEN (PAD_GPIO_PM1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO_PM1_OUT (PAD_GPIO_PM1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x0e20, PAD_GPIO_PM1_OUT, BIT1),
        _RVM1(0x0e1e, PAD_GPIO_PM1_OEN, BIT1),
        //reg_uart_is_gpio[1]
        _RVM1(0x0e6b, 0, BIT1),   //reg[0e6b]#1 = 0
        //reg_uart_is_gpio[3]
        _RVM1(0x0e6b, 0, BIT3),   //reg[0e6b]#3 = 0
    #endif

    #if(PAD_GPIO_PM2_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO_PM2_OEN (PAD_GPIO_PM2_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_GPIO_PM2_OUT (PAD_GPIO_PM2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x0e20, PAD_GPIO_PM2_OUT, BIT2),
        _RVM1(0x0e1e, PAD_GPIO_PM2_OEN, BIT2),
        //reg_mhl_cable_detect_sel
        _RVM1(0x0ee4, 0, BIT6),   //reg[0ee4]#6 = 0
    #endif

    #if(PAD_GPIO_PM3_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO_PM3_OEN (PAD_GPIO_PM3_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_GPIO_PM3_OUT (PAD_GPIO_PM3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
        _RVM1(0x0e20, PAD_GPIO_PM3_OUT, BIT3),
        _RVM1(0x0e1e, PAD_GPIO_PM3_OEN, BIT3),
        //reg_vbus_en_sel
        _RVM1(0x0ee4, 0, BIT7),   //reg[0ee4]#7 = 0
    #endif

    #if(PAD_GPIO_PM4_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO_PM4_OEN (PAD_GPIO_PM4_IS_GPIO == GPIO_IN ? BIT4: 0)
        #define PAD_GPIO_PM4_OUT (PAD_GPIO_PM4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
        _RVM1(0x0e20, PAD_GPIO_PM4_OUT, BIT4),
        _RVM1(0x0e1e, PAD_GPIO_PM4_OEN, BIT4),
        //reg_gpio_pm_lock
        _RVM1(0x0e24, 0xBE, 0xFF),  //reg[0e24]#7 ~ #0 = 10111110b
        _RVM1(0x0e25, 0xBA, 0xFF),  //reg[0e25]#7 ~ #0 = 10111010b
    #endif

    #if(PAD_GPIO_PM5_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO_PM5_OEN (PAD_GPIO_PM5_IS_GPIO == GPIO_IN ? BIT5: 0)
        #define PAD_GPIO_PM5_OUT (PAD_GPIO_PM5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
        _RVM1(0x0e20, PAD_GPIO_PM5_OUT, BIT5),
        _RVM1(0x0e1e, PAD_GPIO_PM5_OEN, BIT5),
    #endif

    #if(PAD_GPIO_PM6_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO_PM6_OEN (PAD_GPIO_PM6_IS_GPIO == GPIO_IN ? BIT6: 0)
        #define PAD_GPIO_PM6_OUT (PAD_GPIO_PM6_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x0e20, PAD_GPIO_PM6_OUT, BIT6),
        _RVM1(0x0e1e, PAD_GPIO_PM6_OEN, BIT6),
        //reg_spicsz1_gpio
        _RVM1(0x0e6a, BIT2, BIT2),   //reg[0e6a]#2 = 1
    #endif

    #if(PAD_GPIO_PM7_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO_PM7_OEN (PAD_GPIO_PM7_IS_GPIO == GPIO_IN ? BIT7: 0)
        #define PAD_GPIO_PM7_OUT (PAD_GPIO_PM7_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
        _RVM1(0x0e20, PAD_GPIO_PM7_OUT, BIT7),
        _RVM1(0x0e1e, PAD_GPIO_PM7_OEN, BIT7),
        //reg_uart_is_gpio[2]
        _RVM1(0x0e6b, 0, BIT2),   //reg[0e6b]#2 = 0
    #endif

    #if(PAD_GPIO_PM8_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO_PM8_OEN (PAD_GPIO_PM8_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_GPIO_PM8_OUT (PAD_GPIO_PM8_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x0e21, PAD_GPIO_PM8_OUT, BIT0),
        _RVM1(0x0e1f, PAD_GPIO_PM8_OEN, BIT0),
        //reg_uart_is_gpio[1]
        _RVM1(0x0e6b, 0, BIT0),   //reg[0e6b]#0 = 0
        //reg_wol_int2pad[0]
        _RVM1(0x0efa, 0, BIT0),   //reg[0efa]#0 = 0
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
        _RVM1(0x0e6a, 0, BIT3),   //reg[0e6a]#3 = 0
    #endif

    #if(PAD_GPIO_PM11_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO_PM11_OEN (PAD_GPIO_PM11_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_GPIO_PM11_OUT (PAD_GPIO_PM11_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
        _RVM1(0x0e21, PAD_GPIO_PM11_OUT, BIT3),
        _RVM1(0x0e1f, PAD_GPIO_PM11_OEN, BIT3),
    #endif

    #if(PAD_PM_LED_IS_GPIO != GPIO_NONE)
        #define PAD_PM_LED_OEN (PAD_PM_LED_IS_GPIO == GPIO_IN ? BIT4: 0)
        #define PAD_PM_LED_OUT (PAD_PM_LED_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
        _RVM1(0x0e21, PAD_PM_LED_OUT, BIT4),
        _RVM1(0x0e1f, PAD_PM_LED_OEN, BIT4),
        //reg_cbus_debug_sel
        _RVM1(0x0ee5, 0, BIT0),   //reg[0ee5]#0 = 0
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
        _RVM1(0x0ee6, 0, BIT0),   //reg[0ee6]#0 = 0
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
    #endif

    #if(PAD_DDCDA_DA_IS_GPIO != GPIO_NONE)
        #define PAD_DDCDA_DA_OEN (PAD_DDCDA_DA_IS_GPIO == GPIO_IN ? BIT5: 0)
        #define PAD_DDCDA_DA_OUT (PAD_DDCDA_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x0496, PAD_DDCDA_DA_OUT, BIT6),
        _RVM1(0x0496, PAD_DDCDA_DA_OEN, BIT5),
        //reg_gpio2do_en
        _RVM1(0x0496, BIT7, BIT7),   //reg[0496]#7 = 1
    #endif

    #if(PAD_DDCDB_CK_IS_GPIO != GPIO_NONE)
        #define PAD_DDCDB_CK_OEN (PAD_DDCDB_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_DDCDB_CK_OUT (PAD_DDCDB_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x0497, PAD_DDCDB_CK_OUT, BIT2),
        _RVM1(0x0497, PAD_DDCDB_CK_OEN, BIT1),
        //reg_gpio2d1_en
        _RVM1(0x0497, BIT7, BIT7),   //reg[0497]#7 = 1
    #endif

    #if(PAD_DDCDB_DA_IS_GPIO != GPIO_NONE)
        #define PAD_DDCDB_DA_OEN (PAD_DDCDB_DA_IS_GPIO == GPIO_IN ? BIT5: 0)
        #define PAD_DDCDB_DA_OUT (PAD_DDCDB_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x0497, PAD_DDCDB_DA_OUT, BIT6),
        _RVM1(0x0497, PAD_DDCDB_DA_OEN, BIT5),
        //reg_gpio2d1_en
        _RVM1(0x0497, BIT7, BIT7),   //reg[0497]#7 = 1
    #endif

    #if(PAD_DDCDC_CK_IS_GPIO != GPIO_NONE)
        #define PAD_DDCDC_CK_OEN (PAD_DDCDC_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_DDCDC_CK_OUT (PAD_DDCDC_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x0498, PAD_DDCDC_CK_OUT, BIT2),
        _RVM1(0x0498, PAD_DDCDC_CK_OEN, BIT1),
        //reg_gpio2d2_en
        _RVM1(0x0498, BIT7, BIT7),   //reg[0498]#7 = 1
    #endif

    #if(PAD_DDCDC_DA_IS_GPIO != GPIO_NONE)
        #define PAD_DDCDC_DA_OEN (PAD_DDCDC_DA_IS_GPIO == GPIO_IN ? BIT5: 0)
        #define PAD_DDCDC_DA_OUT (PAD_DDCDC_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x0498, PAD_DDCDC_DA_OUT, BIT6),
        _RVM1(0x0498, PAD_DDCDC_DA_OEN, BIT5),
        //reg_gpio2d2_en
        _RVM1(0x0498, BIT7, BIT7),   //reg[0498]#7 = 1
    #endif

    #if(PAD_DDCDD_CK_IS_GPIO != GPIO_NONE)
        #define PAD_DDCDD_CK_OEN (PAD_DDCDD_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_DDCDD_CK_OUT (PAD_DDCDD_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x0499, PAD_DDCDD_CK_OUT, BIT2),
        _RVM1(0x0499, PAD_DDCDD_CK_OEN, BIT1),
        //reg_gpio2d3_en
        _RVM1(0x0499, BIT7, BIT7),   //reg[0499]#7 = 1
    #endif

    #if(PAD_DDCDD_DA_IS_GPIO != GPIO_NONE)
        #define PAD_DDCDD_DA_OEN (PAD_DDCDD_DA_IS_GPIO == GPIO_IN ? BIT5: 0)
        #define PAD_DDCDD_DA_OUT (PAD_DDCDD_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x0499, PAD_DDCDD_DA_OUT, BIT6),
        _RVM1(0x0499, PAD_DDCDD_DA_OEN, BIT5),
        //reg_gpio2d3_en
        _RVM1(0x0499, BIT7, BIT7),   //reg[0499]#7 = 1
    #endif

    #if(PAD_SAR0_IS_GPIO != GPIO_NONE)
        #define PAD_SAR0_OEN (PAD_SAR0_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_SAR0_OUT (PAD_SAR0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x1424, PAD_SAR0_OUT, BIT0),
        _RVM1(0x1423, PAD_SAR0_OEN, BIT0),
        //reg_sar_aisel[0]
        _RVM1(0x1422, 0, BIT0),   //reg[1422]#0 = 0
    #endif

    #if(PAD_SAR1_IS_GPIO != GPIO_NONE)
        #define PAD_SAR1_OEN (PAD_SAR1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_SAR1_OUT (PAD_SAR1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x1424, PAD_SAR1_OUT, BIT1),
        _RVM1(0x1423, PAD_SAR1_OEN, BIT1),
        //reg_sar_aisel[1]
        _RVM1(0x1422, 0, BIT1),   //reg[1422]#1 = 0
    #endif

    #if(PAD_SAR2_IS_GPIO != GPIO_NONE)
        #define PAD_SAR2_OEN (PAD_SAR2_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_SAR2_OUT (PAD_SAR2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x1424, PAD_SAR2_OUT, BIT2),
        _RVM1(0x1423, PAD_SAR2_OEN, BIT2),
        //reg_sar_aisel[2]
        _RVM1(0x1422, 0, BIT2),   //reg[1422]#2 = 0
    #endif

    #if(PAD_SAR3_IS_GPIO != GPIO_NONE)
        #define PAD_SAR3_OEN (PAD_SAR3_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_SAR3_OUT (PAD_SAR3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
        _RVM1(0x1424, PAD_SAR3_OUT, BIT3),
        _RVM1(0x1423, PAD_SAR3_OEN, BIT3),
        //reg_sar_aisel[3]
        _RVM1(0x1422, 0, BIT3),   //reg[1422]#3 = 0
    #endif

    #if(PAD_SAR4_IS_GPIO != GPIO_NONE)
        #define PAD_SAR4_OEN (PAD_SAR4_IS_GPIO == GPIO_IN ? BIT4: 0)
        #define PAD_SAR4_OUT (PAD_SAR4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
        _RVM1(0x1424, PAD_SAR4_OUT, BIT4),
        _RVM1(0x1423, PAD_SAR4_OEN, BIT4),
        //reg_sar_aisel[4]
        _RVM1(0x1422, 0, BIT4),   //reg[1422]#4 = 0
    #endif

    #if(PAD_VID0_IS_GPIO != GPIO_NONE)
        #define PAD_VID0_OEN (PAD_VID0_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_VID0_OUT (PAD_VID0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2e84, PAD_VID0_OUT, BIT0),
        _RVM1(0x2e84, PAD_VID0_OEN, BIT1),
        //reg_vid_is_gpio
        _RVM1(0x0efb, BIT0, BIT0),   //reg[0efb]#0 = 1
    #endif

    #if(PAD_VID1_IS_GPIO != GPIO_NONE)
        #define PAD_VID1_OEN (PAD_VID1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_VID1_OUT (PAD_VID1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2e85, PAD_VID1_OUT, BIT0),
        _RVM1(0x2e85, PAD_VID1_OEN, BIT1),
        //reg_sar_aisel[4]
        _RVM1(0x1422, 0, BIT4),   //reg[1422]#4 = 0
    #endif

    _MEMMAP_nonPM_,

    #if(PAD_ARC0_IS_GPIO != GPIO_NONE)
        #define PAD_ARC0_OEN (PAD_ARC0_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_ARC0_OUT (PAD_ARC0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x1ee8, PAD_ARC0_OUT, BIT0),
        _RVM1(0x1ee8, PAD_ARC0_OEN, BIT1),
        //reg_arc_gpio_en
        _RVM1(0x1ee8, BIT3, BIT3),   //reg[101ee8] #3 = 1b
        //reg_arc_mode
        _RVM1(0x1ee7, 0, BIT7),   //reg[101ee7]#7 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_DDCR_DA_IS_GPIO != GPIO_NONE)
        #define PAD_DDCR_DA_OEN (PAD_DDCR_DA_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_DDCR_DA_OUT (PAD_DDCR_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x1e9a, PAD_DDCR_DA_OUT, BIT2),
        _RVM1(0x1e9a, PAD_DDCR_DA_OEN, BIT0),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_ddcrmode[1:0]
        _RVM1(0x1eae, 0, BIT1 | BIT0),   //reg[101eae]#1 ~ #0 = 00b
        //reg_ddcrmode[1:0]
        _RVM1(0x1eae, 0, BIT1 | BIT0),   //reg[101eae]#1 ~ #0 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_DDCR_CK_IS_GPIO != GPIO_NONE)
        #define PAD_DDCR_CK_OEN (PAD_DDCR_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_DDCR_CK_OUT (PAD_DDCR_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
        _RVM1(0x1e9a, PAD_DDCR_CK_OUT, BIT3),
        _RVM1(0x1e9a, PAD_DDCR_CK_OEN, BIT1),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_ddcrmode[1:0]
        _RVM1(0x1eae, 0, BIT1 | BIT0),   //reg[101eae]#1 ~ #0 = 00b
        //reg_ddcrmode[1:0]
        _RVM1(0x1eae, 0, BIT1 | BIT0),   //reg[101eae]#1 ~ #0 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO0_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO0_OEN (PAD_GPIO0_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_GPIO0_OUT (PAD_GPIO0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x1e56, PAD_GPIO0_OUT, BIT0),
        _RVM1(0x1e5c, PAD_GPIO0_OEN, BIT0),
        //reg_chiptop_dummy_2[15]
        _RVM1(0x1e3d, 0, BIT7),   //reg[101e3d]#7 = 0b
        //reg_ej_config_o[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 00b
        //reg_ej_config_x[1:0]
        _RVM1(0x1e27, 0, BIT1 | BIT0),   //reg[101e27]#1 ~ #0 = 00b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_usbdrvvbusconfig[1:0]
        _RVM1(0x1e04, 0, BIT1 | BIT0),   //reg[101e04]#1 ~ #0 = 00b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_p1_enable_b0
        _RVM1(0x1eb8, 0, BIT0),   //reg[101eb8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO1_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO1_OEN (PAD_GPIO1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO1_OUT (PAD_GPIO1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x1e56, PAD_GPIO1_OUT, BIT1),
        _RVM1(0x1e5c, PAD_GPIO1_OEN, BIT1),
        //reg_chiptop_dummy_2[15]
        _RVM1(0x1e3d, 0, BIT7),   //reg[101e3d]#7 = 0b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_usbdrvvbusconfig[1:0]
        _RVM1(0x1e04, 0, BIT1 | BIT0),   //reg[101e04]#1 ~ #0 = 00b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_p1_enable_b1
        _RVM1(0x1eb8, 0, BIT1),   //reg[101eb8]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO2_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO2_OEN (PAD_GPIO2_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_GPIO2_OUT (PAD_GPIO2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x1e56, PAD_GPIO2_OUT, BIT2),
        _RVM1(0x1e5c, PAD_GPIO2_OEN, BIT2),
        //reg_chiptop_dummy_2[15]
        _RVM1(0x1e3d, 0, BIT7),   //reg[101e3d]#7 = 0b
        //reg_ej_config_o[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 00b
        //reg_ej_config_x[1:0]
        _RVM1(0x1e27, 0, BIT1 | BIT0),   //reg[101e27]#1 ~ #0 = 00b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_p1_enable_b2
        _RVM1(0x1eb8, 0, BIT2),   //reg[101eb8]#2 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO3_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO3_OEN (PAD_GPIO3_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_GPIO3_OUT (PAD_GPIO3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
        _RVM1(0x1e56, PAD_GPIO3_OUT, BIT3),
        _RVM1(0x1e5c, PAD_GPIO3_OEN, BIT3),
        //reg_ej_config_o[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 00b
        //reg_ej_config_x[1:0]
        _RVM1(0x1e27, 0, BIT1 | BIT0),   //reg[101e27]#1 ~ #0 = 00b
        //reg_ej_config_o[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 00b
        //reg_ej_config_x[1:0]
        _RVM1(0x1e27, 0, BIT1 | BIT0),   //reg[101e27]#1 ~ #0 = 00b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_seconduartmode[1:0]
        _RVM1(0x1e05, 0, BIT1 | BIT0),   //reg[101e05]#1 ~ #0 = 00b
        //reg_fastuartmode[1:0]
        _RVM1(0x1e04, 0, BIT5 | BIT4),   //reg[101e04]#5 ~ #4 = 00b
        //reg_od2nduart[1:0]
        _RVM1(0x1eb6, 0, BIT1 | BIT0),   //reg[101eb6]#1 ~ #0 = 00b
        //reg_odfastuart[1:0]
        _RVM1(0x1eb6, 0, BIT7 | BIT6),   //reg[101eb6]#7 ~ #6 = 00b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_p1_enable_b3
        _RVM1(0x1eb8, 0, BIT3),   //reg[101eb8]#3 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO4_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO4_OEN (PAD_GPIO4_IS_GPIO == GPIO_IN ? BIT4: 0)
        #define PAD_GPIO4_OUT (PAD_GPIO4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
        _RVM1(0x1e56, PAD_GPIO4_OUT, BIT4),
        _RVM1(0x1e5c, PAD_GPIO4_OEN, BIT4),
        //reg_ej_config_o[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 00b
        //reg_ej_config_x[1:0]
        _RVM1(0x1e27, 0, BIT1 | BIT0),   //reg[101e27]#1 ~ #0 = 00b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_seconduartmode[1:0]
        _RVM1(0x1e05, 0, BIT1 | BIT0),   //reg[101e05]#1 ~ #0 = 00b
        //reg_fastuartmode[1:0]
        _RVM1(0x1e04, 0, BIT5 | BIT4),   //reg[101e04]#5 ~ #4 = 00b
        //reg_od2nduart[1:0]
        _RVM1(0x1eb6, 0, BIT1 | BIT0),   //reg[101eb6]#1 ~ #0 = 00b
        //reg_odfastuart[1:0]
        _RVM1(0x1eb6, 0, BIT7 | BIT6),   //reg[101eb6]#7 ~ #6 = 00b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_p1_enable_b4
        _RVM1(0x1eb8, 0, BIT4),   //reg[101eb8]#4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO5_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO5_OEN (PAD_GPIO5_IS_GPIO == GPIO_IN ? BIT5: 0)
        #define PAD_GPIO5_OUT (PAD_GPIO5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
        _RVM1(0x1e56, PAD_GPIO5_OUT, BIT5),
        _RVM1(0x1e5c, PAD_GPIO5_OEN, BIT5),
        //reg_chiptop_dummy_2[15]
        _RVM1(0x1e3d, 0, BIT7),   //reg[101e3d]#7 = 0b
        //reg_ej_config_o[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 00b
        //reg_ej_config_x[1:0]
        _RVM1(0x1e27, 0, BIT1 | BIT0),   //reg[101e27]#1 ~ #0 = 00b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_p1_enable_b5
        _RVM1(0x1eb8, 0, BIT5),   //reg[101eb8]#5 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO6_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO6_OEN (PAD_GPIO6_IS_GPIO == GPIO_IN ? BIT6: 0)
        #define PAD_GPIO6_OUT (PAD_GPIO6_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x1e56, PAD_GPIO6_OUT, BIT6),
        _RVM1(0x1e5c, PAD_GPIO6_OEN, BIT6),
        //reg_chiptop_dummy_2[15]
        _RVM1(0x1e3d, 0, BIT7),   //reg[101e3d]#7 = 0b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_p1_enable_b6
        _RVM1(0x1eb8, 0, BIT6),   //reg[101eb8]#6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO7_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO7_OEN (PAD_GPIO7_IS_GPIO == GPIO_IN ? BIT7: 0)
        #define PAD_GPIO7_OUT (PAD_GPIO7_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
        _RVM1(0x1e56, PAD_GPIO7_OUT, BIT7),
        _RVM1(0x1e5c, PAD_GPIO7_OEN, BIT7),
        //reg_chiptop_dummy_2[15]
        _RVM1(0x1e3d, 0, BIT7),   //reg[101e3d]#7 = 0b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_seconduartmode[1:0]
        _RVM1(0x1e05, 0, BIT1 | BIT0),   //reg[101e05]#1 ~ #0 = 00b
        //reg_od2nduart[1:0]
        _RVM1(0x1eb6, 0, BIT1 | BIT0),   //reg[101eb6]#1 ~ #0 = 00b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_p1_enable_b7
        _RVM1(0x1eb8, 0, BIT7),   //reg[101eb8]#7 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO8_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO8_OEN (PAD_GPIO8_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_GPIO8_OUT (PAD_GPIO8_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x1e57, PAD_GPIO8_OUT, BIT0),
        _RVM1(0x1e5d, PAD_GPIO8_OEN, BIT0),
        //reg_chiptop_dummy_2[15]
        _RVM1(0x1e3d, 0, BIT7),   //reg[101e3d]#7 = 0b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_seconduartmode[1:0]
        _RVM1(0x1e05, 0, BIT1 | BIT0),   //reg[101e05]#1 ~ #0 = 00b
        //reg_od2nduart[1:0]
        _RVM1(0x1eb6, 0, BIT1 | BIT0),   //reg[101eb6]#1 ~ #0 = 00b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO9_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO9_OEN (PAD_GPIO9_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO9_OUT (PAD_GPIO9_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x1e57, PAD_GPIO9_OUT, BIT1),
        _RVM1(0x1e5d, PAD_GPIO9_OEN, BIT1),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_thirduartmode[1:0]
        _RVM1(0x1e05, 0, BIT3 | BIT2),   //reg[101e05]#3 ~ #2 = 00b
        //reg_od3rduart[1:0]
        _RVM1(0x1eb6, 0, BIT3 | BIT2),   //reg[101eb6]#3 ~ #2 = 00b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO10_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO10_OEN (PAD_GPIO10_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_GPIO10_OUT (PAD_GPIO10_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x1e57, PAD_GPIO10_OUT, BIT2),
        _RVM1(0x1e5d, PAD_GPIO10_OEN, BIT2),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_thirduartmode[1:0]
        _RVM1(0x1e05, 0, BIT3 | BIT2),   //reg[101e05]#3 ~ #2 = 00b
        //reg_od3rduart[1:0]
        _RVM1(0x1eb6, 0, BIT3 | BIT2),   //reg[101eb6]#3 ~ #2 = 00b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO11_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO11_OEN (PAD_GPIO11_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_GPIO11_OUT (PAD_GPIO11_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
        _RVM1(0x1e57, PAD_GPIO11_OUT, BIT3),
        _RVM1(0x1e5d, PAD_GPIO11_OEN, BIT3),
        //reg_chiptop_dummy_2[15]
        _RVM1(0x1e3d, 0, BIT7),   //reg[101e3d]#7 = 0b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_fourthuartmode[1:0]
        _RVM1(0x1e04, 0, BIT7 | BIT6),   //reg[101e04]#7 ~ #6 = 00b
        //reg_od4thuart[1:0]
        _RVM1(0x1eb6, 0, BIT5 | BIT4),   //reg[101eb6]#5 ~ #4 = 00b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO12_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO12_OEN (PAD_GPIO12_IS_GPIO == GPIO_IN ? BIT4: 0)
        #define PAD_GPIO12_OUT (PAD_GPIO12_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
        _RVM1(0x1e57, PAD_GPIO12_OUT, BIT4),
        _RVM1(0x1e5d, PAD_GPIO12_OEN, BIT4),
        //reg_chiptop_dummy_2[15]
        _RVM1(0x1e3d, 0, BIT7),   //reg[101e3d]#7 = 0b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_fourthuartmode[1:0]
        _RVM1(0x1e04, 0, BIT7 | BIT6),   //reg[101e04]#7 ~ #6 = 00b
        //reg_od4thuart[1:0]
        _RVM1(0x1eb6, 0, BIT5 | BIT4),   //reg[101eb6]#5 ~ #4 = 00b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO13_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO13_OEN (PAD_GPIO13_IS_GPIO == GPIO_IN ? BIT5: 0)
        #define PAD_GPIO13_OUT (PAD_GPIO13_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
        _RVM1(0x1e57, PAD_GPIO13_OUT, BIT5),
        _RVM1(0x1e5d, PAD_GPIO13_OEN, BIT5),
        //reg_chiptop_dummy_2[15]
        _RVM1(0x1e3d, 0, BIT7),   //reg[101e3d]#7 = 0b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_fastuartmode[1:0]
        _RVM1(0x1e04, 0, BIT5 | BIT4),   //reg[101e04]#5 ~ #4 = 00b
        //reg_odfastuart[1:0]
        _RVM1(0x1eb6, 0, BIT7 | BIT6),   //reg[101eb6]#7 ~ #6 = 00b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO14_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO14_OEN (PAD_GPIO14_IS_GPIO == GPIO_IN ? BIT6: 0)
        #define PAD_GPIO14_OUT (PAD_GPIO14_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x1e57, PAD_GPIO14_OUT, BIT6),
        _RVM1(0x1e5d, PAD_GPIO14_OEN, BIT6),
        //reg_chiptop_dummy_2[15]
        _RVM1(0x1e3d, 0, BIT7),   //reg[101e3d]#7 = 0b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_fastuartmode[1:0]
        _RVM1(0x1e04, 0, BIT5 | BIT4),   //reg[101e04]#5 ~ #4 = 00b
        //reg_odfastuart[1:0]
        _RVM1(0x1eb6, 0, BIT7 | BIT6),   //reg[101eb6]#7 ~ #6 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO15_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO15_OEN (PAD_GPIO15_IS_GPIO == GPIO_IN ? BIT7: 0)
        #define PAD_GPIO15_OUT (PAD_GPIO15_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
        _RVM1(0x1e57, PAD_GPIO15_OUT, BIT7),
        _RVM1(0x1e5d, PAD_GPIO15_OEN, BIT7),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_i2smutemode[1:0]
        _RVM1(0x1e05, 0, BIT7 | BIT6),   //reg[101e05]#7 ~ #6 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO16_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO16_OEN (PAD_GPIO16_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_GPIO16_OUT (PAD_GPIO16_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x1e58, PAD_GPIO16_OUT, BIT0),
        _RVM1(0x1e5e, PAD_GPIO16_OEN, BIT0),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_3dflagconfig[1:0]
        _RVM1(0x1eb1, 0, BIT7 | BIT6),   //reg[101eb1]#7 ~ #6 = 00b
        //reg_tserrout[1:0]
        _RVM1(0x1ea2, 0, BIT7 | BIT6),   //reg[101ea2]#7 ~ #6 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO17_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO17_OEN (PAD_GPIO17_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO17_OUT (PAD_GPIO17_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x1e58, PAD_GPIO17_OUT, BIT1),
        _RVM1(0x1e5e, PAD_GPIO17_OEN, BIT1),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_miic_mode0[1:0]
        _RVM1(0x1eb5, 0, BIT1 | BIT0),   //reg[101eb5]#1 ~ #0 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO18_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO18_OEN (PAD_GPIO18_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_GPIO18_OUT (PAD_GPIO18_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x1e58, PAD_GPIO18_OUT, BIT2),
        _RVM1(0x1e5e, PAD_GPIO18_OEN, BIT2),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_miic_mode0[1:0]
        _RVM1(0x1eb5, 0, BIT1 | BIT0),   //reg[101eb5]#1 ~ #0 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO19_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO19_OEN (PAD_GPIO19_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_GPIO19_OUT (PAD_GPIO19_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
        _RVM1(0x1e58, PAD_GPIO19_OUT, BIT3),
        _RVM1(0x1e5e, PAD_GPIO19_OEN, BIT3),
        //reg_agc_dbg
        _RVM1(0x1e06, 0, BIT5),   //reg[101e06]#5 = 0b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_et_mode
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        //reg_led_mode[1:0]
        _RVM1(0x1eb4, 0, BIT5 | BIT4),   //reg[101eb4]#5 ~ #4 = 00b
        //reg_et_test_mode[1:0]
        //_RVM1(0x1edf, 0, BIT3 | BIT2),   //reg[101edf]#3 ~ #2 = 00b
        //reg_et_test_mode[1:0]
        //_RVM1(0x1edf, 0, BIT3 | BIT2),   //reg[101edf]#3 ~ #2 = 00b
        //reg_seconduartmode[1:0]
        _RVM1(0x1e05, 0, BIT1 | BIT0),   //reg[101e05]#1 ~ #0 = 00b
        //reg_fastuartmode[1:0]
        _RVM1(0x1e04, 0, BIT5 | BIT4),   //reg[101e04]#5 ~ #4 = 00b
        //reg_od2nduart[1:0]
        _RVM1(0x1eb6, 0, BIT1 | BIT0),   //reg[101eb6]#1 ~ #0 = 00b
        //reg_odfastuart[1:0]
        _RVM1(0x1eb6, 0, BIT7 | BIT6),   //reg[101eb6]#7 ~ #6 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO20_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO20_OEN (PAD_GPIO20_IS_GPIO == GPIO_IN ? BIT4: 0)
        #define PAD_GPIO20_OUT (PAD_GPIO20_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
        _RVM1(0x1e58, PAD_GPIO20_OUT, BIT4),
        _RVM1(0x1e5e, PAD_GPIO20_OEN, BIT4),
        //reg_agc_dbg
        _RVM1(0x1e06, 0, BIT5),   //reg[101e06]#5 = 0b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_et_mode
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        //reg_led_mode[1:0]
        _RVM1(0x1eb4, 0, BIT5 | BIT4),   //reg[101eb4]#5 ~ #4 = 00b
        //reg_et_test_mode[1:0]
        //_RVM1(0x1edf, 0, BIT3 | BIT2),   //reg[101edf]#3 ~ #2 = 00b
        //reg_seconduartmode[1:0]
        _RVM1(0x1e05, 0, BIT1 | BIT0),   //reg[101e05]#1 ~ #0 = 00b
        //reg_fastuartmode[1:0]
        _RVM1(0x1e04, 0, BIT5 | BIT4),   //reg[101e04]#5 ~ #4 = 00b
        //reg_od2nduart[1:0]
        _RVM1(0x1eb6, 0, BIT1 | BIT0),   //reg[101eb6]#1 ~ #0 = 00b
        //reg_odfastuart[1:0]
        _RVM1(0x1eb6, 0, BIT7 | BIT6),   //reg[101eb6]#7 ~ #6 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO21_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO21_OEN (PAD_GPIO21_IS_GPIO == GPIO_IN ? BIT5: 0)
        #define PAD_GPIO21_OUT (PAD_GPIO21_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
        _RVM1(0x1e58, PAD_GPIO21_OUT, BIT5),
        _RVM1(0x1e5e, PAD_GPIO21_OEN, BIT5),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_et_mode
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        //reg_et_test_mode[1:0]
        //_RVM1(0x1edf, 0, BIT3 | BIT2),   //reg[101edf]#3 ~ #2 = 00b
        //reg_od3rduart[1:0]
        _RVM1(0x1eb6, 0, BIT3 | BIT2),   //reg[101eb6]#3 ~ #2 = 00b
        //reg_extint5
        _RVM1(0x1ee0, 0, BIT5),   //reg[101ee0]#5 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO22_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO22_OEN (PAD_GPIO22_IS_GPIO == GPIO_IN ? BIT6: 0)
        #define PAD_GPIO22_OUT (PAD_GPIO22_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x1e58, PAD_GPIO22_OUT, BIT6),
        _RVM1(0x1e5e, PAD_GPIO22_OEN, BIT6),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_et_mode
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        //reg_et_test_mode[1:0]
        //_RVM1(0x1edf, 0, BIT3 | BIT2),   //reg[101edf]#3 ~ #2 = 00b
        //reg_od3rduart[1:0]
        _RVM1(0x1eb6, 0, BIT3 | BIT2),   //reg[101eb6]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO23_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO23_OEN (PAD_GPIO23_IS_GPIO == GPIO_IN ? BIT7: 0)
        #define PAD_GPIO23_OUT (PAD_GPIO23_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
        _RVM1(0x1e58, PAD_GPIO23_OUT, BIT7),
        _RVM1(0x1e5e, PAD_GPIO23_OEN, BIT7),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_et_mode
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        //reg_et_test_mode[1:0]
        //_RVM1(0x1edf, 0, BIT3 | BIT2),   //reg[101edf]#3 ~ #2 = 00b
        //reg_fourthuartmode[1:0]
        _RVM1(0x1e04, 0, BIT7 | BIT6),   //reg[101e04]#7 ~ #6 = 00b
        //reg_od4thuart[1:0]
        _RVM1(0x1eb6, 0, BIT5 | BIT4),   //reg[101eb6]#5 ~ #4 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO24_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO24_OEN (PAD_GPIO24_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_GPIO24_OUT (PAD_GPIO24_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x1e59, PAD_GPIO24_OUT, BIT0),
        _RVM1(0x1e5f, PAD_GPIO24_OEN, BIT0),
        //reg_et_mode
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        //reg_et_test_mode[1:0]
        //_RVM1(0x1edf, 0, BIT3 | BIT2),   //reg[101edf]#3 ~ #2 = 00b
        //reg_fourthuartmode[1:0]
        _RVM1(0x1e04, 0, BIT7 | BIT6),   //reg[101e04]#7 ~ #6 = 00b
        //reg_od4thuart[1:0]
        _RVM1(0x1eb6, 0, BIT5 | BIT4),   //reg[101eb6]#5 ~ #4 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO25_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO25_OEN (PAD_GPIO25_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO25_OUT (PAD_GPIO25_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x1e59, PAD_GPIO25_OUT, BIT1),
        _RVM1(0x1e5f, PAD_GPIO25_OEN, BIT1),
        //reg_et_mode
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        //reg_et_test_mode[1:0]
        //_RVM1(0x1edf, 0, BIT3 | BIT2),   //reg[101edf]#3 ~ #2 = 00b
        //reg_extint1
        _RVM1(0x1ee0, 0, BIT1),   //reg[101ee0]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO26_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO26_OEN (PAD_GPIO26_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_GPIO26_OUT (PAD_GPIO26_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x1e59, PAD_GPIO26_OUT, BIT2),
        _RVM1(0x1e5f, PAD_GPIO26_OEN, BIT2),
        //reg_et_mode
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        //reg_led_mode[1:0]
        _RVM1(0x1eb4, 0, BIT5 | BIT4),   //reg[101eb4]#5 ~ #4 = 00b
        //reg_et_test_mode[1:0]
        //_RVM1(0x1edf, 0, BIT3 | BIT2),   //reg[101edf]#3 ~ #2 = 00b
        //reg_usbdrvvbusconfig[1:0]
        _RVM1(0x1e04, 0, BIT1 | BIT0),   //reg[101e04]#1 ~ #0 = 00b
        //reg_extint7
        _RVM1(0x1ee0, 0, BIT7),   //reg[101ee0]#7 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO27_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO27_OEN (PAD_GPIO27_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_GPIO27_OUT (PAD_GPIO27_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
        _RVM1(0x1e59, PAD_GPIO27_OUT, BIT3),
        _RVM1(0x1e5f, PAD_GPIO27_OEN, BIT3),
        //reg_et_mode
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        //reg_led_mode[1:0]
        _RVM1(0x1eb4, 0, BIT5 | BIT4),   //reg[101eb4]#5 ~ #4 = 00b
        //reg_et_test_mode[1:0]
        //_RVM1(0x1edf, 0, BIT3 | BIT2),   //reg[101edf]#3 ~ #2 = 00b
        //reg_usbdrvvbusconfig[1:0]
        _RVM1(0x1e04, 0, BIT1 | BIT0),   //reg[101e04]#1 ~ #0 = 00b
        //reg_extint4
        _RVM1(0x1ee0, 0, BIT4),   //reg[101ee0]#4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_I2S_IN_WS_IS_GPIO != GPIO_NONE)
        #define PAD_I2S_IN_WS_OEN (PAD_I2S_IN_WS_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_I2S_IN_WS_OUT (PAD_I2S_IN_WS_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x1e6c, PAD_I2S_IN_WS_OUT, BIT0),
        _RVM1(0x1e6e, PAD_I2S_IN_WS_OEN, BIT0),
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_i2sinconfig
        _RVM1(0x1eae, 0, BIT2),   //reg[101eae]#2 = 0b
        //reg_mcu_jtag_mode[1:0]
        //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6 = 00b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 00b
        //reg_thirduartmode[1:0]
        _RVM1(0x1e05, 0, BIT3 | BIT2),   //reg[101e05]#3 ~ #2 = 00b
        //reg_od3rduart[1:0]
        _RVM1(0x1eb6, 0, BIT3 | BIT2),   //reg[101eb6]#3 ~ #2 = 00b
        //reg_extint6
        _RVM1(0x1ee0, 0, BIT6),   //reg[101ee0]#6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_I2S_IN_BCK_IS_GPIO != GPIO_NONE)
        #define PAD_I2S_IN_BCK_OEN (PAD_I2S_IN_BCK_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_I2S_IN_BCK_OUT (PAD_I2S_IN_BCK_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x1e6c, PAD_I2S_IN_BCK_OUT, BIT1),
        _RVM1(0x1e6e, PAD_I2S_IN_BCK_OEN, BIT1),
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_i2sinconfig
        _RVM1(0x1eae, 0, BIT2),   //reg[101eae]#2 = 0b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 00b
        //reg_thirduartmode[1:0]
        _RVM1(0x1e05, 0, BIT3 | BIT2),   //reg[101e05]#3 ~ #2 = 00b
        //reg_od3rduart[1:0]
        _RVM1(0x1eb6, 0, BIT3 | BIT2),   //reg[101eb6]#3 ~ #2 = 00b
        //reg_miic_mode2[1:0]
        _RVM1(0x1eb5, 0, BIT5 | BIT4),   //reg[101eb5]#5 ~ #4 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_I2S_IN_SD_IS_GPIO != GPIO_NONE)
        #define PAD_I2S_IN_SD_OEN (PAD_I2S_IN_SD_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_I2S_IN_SD_OUT (PAD_I2S_IN_SD_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x1e6c, PAD_I2S_IN_SD_OUT, BIT2),
        _RVM1(0x1e6e, PAD_I2S_IN_SD_OEN, BIT2),
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_i2sinconfig
        _RVM1(0x1eae, 0, BIT2),   //reg[101eae]#2 = 0b
        //reg_3dflagconfig[1:0]
        _RVM1(0x1eb1, 0, BIT7 | BIT6),   //reg[101eb1]#7 ~ #6 = 00b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 00b
        //reg_tserrout[1:0]
        _RVM1(0x1ea2, 0, BIT7 | BIT6),   //reg[101ea2]#7 ~ #6 = 00b
        //reg_miic_mode2[1:0]
        _RVM1(0x1eb5, 0, BIT5 | BIT4),   //reg[101eb5]#5 ~ #4 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_SPDIF_IN_IS_GPIO != GPIO_NONE)
        #define PAD_SPDIF_IN_OEN (PAD_SPDIF_IN_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_SPDIF_IN_OUT (PAD_SPDIF_IN_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
        _RVM1(0x1e6c, PAD_SPDIF_IN_OUT, BIT3),
        _RVM1(0x1e6e, PAD_SPDIF_IN_OEN, BIT3),
        //reg_ej_config_o[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 00b
        //reg_ej_config_x[1:0]
        _RVM1(0x1e27, 0, BIT1 | BIT0),   //reg[101e27]#1 ~ #0 = 00b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_spdifinconfig
        _RVM1(0x1eae, 0, BIT6),   //reg[101eae]#6 = 0b
        //reg_3dflagconfig[1:0]
        _RVM1(0x1eb1, 0, BIT7 | BIT6),   //reg[101eb1]#7 ~ #6 = 00b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_SPDIF_OUT_IS_GPIO != GPIO_NONE)
        #define PAD_SPDIF_OUT_OEN (PAD_SPDIF_OUT_IS_GPIO == GPIO_IN ? BIT4: 0)
        #define PAD_SPDIF_OUT_OUT (PAD_SPDIF_OUT_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
        _RVM1(0x1e6c, PAD_SPDIF_OUT_OUT, BIT4),
        _RVM1(0x1e6e, PAD_SPDIF_OUT_OEN, BIT4),
        //reg_ej_config_o[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 00b
        //reg_ej_config_x[1:0]
        _RVM1(0x1e27, 0, BIT1 | BIT0),   //reg[101e27]#1 ~ #0 = 00b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_spdifoutconfig
        _RVM1(0x1eae, 0, BIT7),   //reg[101eae]#7 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_I2S_OUT_WS_IS_GPIO != GPIO_NONE)
        #define PAD_I2S_OUT_WS_OEN (PAD_I2S_OUT_WS_IS_GPIO == GPIO_IN ? BIT5: 0)
        #define PAD_I2S_OUT_WS_OUT (PAD_I2S_OUT_WS_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
        _RVM1(0x1e6c, PAD_I2S_OUT_WS_OUT, BIT5),
        _RVM1(0x1e6e, PAD_I2S_OUT_WS_OEN, BIT5),
        //reg_ej_config_o[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 00b
        //reg_ej_config_x[1:0]
        _RVM1(0x1e27, 0, BIT1 | BIT0),   //reg[101e27]#1 ~ #0 = 00b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_i2soutconfig1
        _RVM1(0x1edb, 0, BIT1),   //reg[101edb]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_I2S_OUT_MCK_IS_GPIO != GPIO_NONE)
        #define PAD_I2S_OUT_MCK_OEN (PAD_I2S_OUT_MCK_IS_GPIO == GPIO_IN ? BIT6: 0)
        #define PAD_I2S_OUT_MCK_OUT (PAD_I2S_OUT_MCK_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x1e6c, PAD_I2S_OUT_MCK_OUT, BIT6),
        _RVM1(0x1e6e, PAD_I2S_OUT_MCK_OEN, BIT6),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_i2soutconfig0
        _RVM1(0x1edb, 0, BIT0),   //reg[101edb]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_I2S_OUT_BCK_IS_GPIO != GPIO_NONE)
        #define PAD_I2S_OUT_BCK_OEN (PAD_I2S_OUT_BCK_IS_GPIO == GPIO_IN ? BIT7: 0)
        #define PAD_I2S_OUT_BCK_OUT (PAD_I2S_OUT_BCK_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
        _RVM1(0x1e6c, PAD_I2S_OUT_BCK_OUT, BIT7),
        _RVM1(0x1e6e, PAD_I2S_OUT_BCK_OEN, BIT7),
        //reg_ej_config_o[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 00b
        //reg_ej_config_x[1:0]
        _RVM1(0x1e27, 0, BIT1 | BIT0),   //reg[101e27]#1 ~ #0 = 00b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_i2soutconfig2
        _RVM1(0x1edb, 0, BIT2),   //reg[101edb]#2 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_I2S_OUT_SD_IS_GPIO != GPIO_NONE)
        #define PAD_I2S_OUT_SD_OEN (PAD_I2S_OUT_SD_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_I2S_OUT_SD_OUT (PAD_I2S_OUT_SD_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x1e6d, PAD_I2S_OUT_SD_OUT, BIT0),
        _RVM1(0x1e6f, PAD_I2S_OUT_SD_OEN, BIT0),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_i2soutconfig3
        _RVM1(0x1edb, 0, BIT3),   //reg[101edb]#3 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_I2S_OUT_SD1_IS_GPIO != GPIO_NONE)
        #define PAD_I2S_OUT_SD1_OEN (PAD_I2S_OUT_SD1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_I2S_OUT_SD1_OUT (PAD_I2S_OUT_SD1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x1e6d, PAD_I2S_OUT_SD1_OUT, BIT1),
        _RVM1(0x1e6f, PAD_I2S_OUT_SD1_OEN, BIT1),
        //reg_i2soutconfig4
        _RVM1(0x1edb, 0, BIT4),   //reg[101edb]#4 = 0b
        //reg_mcu_jtag_mode[1:0]
        //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6 = 00b
        //reg_usbdrvvbusconfig[1:0]
        _RVM1(0x1e04, 0, BIT1 | BIT0),   //reg[101e04]#1 ~ #0 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_I2S_OUT_SD2_IS_GPIO != GPIO_NONE)
        #define PAD_I2S_OUT_SD2_OEN (PAD_I2S_OUT_SD2_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_I2S_OUT_SD2_OUT (PAD_I2S_OUT_SD2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x1e6d, PAD_I2S_OUT_SD2_OUT, BIT2),
        _RVM1(0x1e6f, PAD_I2S_OUT_SD2_OEN, BIT2),
        //reg_i2soutconfig5
        _RVM1(0x1edb, 0, BIT5),   //reg[101edb]#5 = 0b
        //reg_mcu_jtag_mode[1:0]
        //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6 = 00b
        //reg_usbdrvvbusconfig[1:0]
        _RVM1(0x1e04, 0, BIT1 | BIT0),   //reg[101e04]#1 ~ #0 = 00b
        //reg_fourthuartmode[1:0]
        _RVM1(0x1e04, 0, BIT7 | BIT6),   //reg[101e04]#7 ~ #6 = 00b
        //reg_od4thuart[1:0]
        _RVM1(0x1eb6, 0, BIT5 | BIT4),   //reg[101eb6]#5 ~ #4 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_I2S_OUT_SD3_IS_GPIO != GPIO_NONE)
        #define PAD_I2S_OUT_SD3_OEN (PAD_I2S_OUT_SD3_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_I2S_OUT_SD3_OUT (PAD_I2S_OUT_SD3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
        _RVM1(0x1e6d, PAD_I2S_OUT_SD3_OUT, BIT3),
        _RVM1(0x1e6f, PAD_I2S_OUT_SD3_OEN, BIT3),
        //reg_i2soutconfig6
        _RVM1(0x1edb, 0, BIT6),   //reg[101edb]#6 = 0b
        //reg_mcu_jtag_mode[1:0]
        //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6 = 00b
        //reg_fourthuartmode[1:0]
        _RVM1(0x1e04, 0, BIT7 | BIT6),   //reg[101e04]#7 ~ #6 = 00b
        //reg_od4thuart[1:0]
        _RVM1(0x1eb6, 0, BIT5 | BIT4),   //reg[101eb6]#5 ~ #4 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_SPI1_CK_IS_GPIO != GPIO_NONE)
        #define PAD_SPI1_CK_OEN (PAD_SPI1_CK_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_SPI1_CK_OUT (PAD_SPI1_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
        _RVM1(0x1e90, PAD_SPI1_CK_OUT, BIT4),
        _RVM1(0x1e90, PAD_SPI1_CK_OEN, BIT0),
        //reg_ld_spi1_config
        _RVM1(0x1eb4, 0, BIT0),   //reg[101eb4]#0 = 0b
        //reg_ld_spi3_config
        _RVM1(0x1eb4, 0, BIT2),   //reg[101eb4]#2 = 0b
        //reg_pwm5_mode[1:0]
        _RVM1(0x1eb2, 0, BIT1 | BIT0),   //reg[101eb2]#1 ~ #0 = 00b
        //reg_pwm7_dim_mode
        _RVM1(0x1eef, 0, BIT7),   //reg[101eef]#7 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_SPI1_DI_IS_GPIO != GPIO_NONE)
        #define PAD_SPI1_DI_OEN (PAD_SPI1_DI_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_SPI1_DI_OUT (PAD_SPI1_DI_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
        _RVM1(0x1e90, PAD_SPI1_DI_OUT, BIT5),
        _RVM1(0x1e90, PAD_SPI1_DI_OEN, BIT1),
        //reg_ld_spi1_config
        _RVM1(0x1eb4, 0, BIT0),   //reg[101eb4]#0 = 0b
        //reg_ld_spi3_config
        _RVM1(0x1eb4, 0, BIT2),   //reg[101eb4]#2 = 0b
        //reg_pwm4_mode[1:0]
        _RVM1(0x1ea2, 0, BIT5 | BIT4),   //reg[101ea2]#5 ~ #4 = 00b
        //reg_pwm6_dim_mode
        _RVM1(0x1eef, 0, BIT6),   //reg[101eef]#6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_SPI2_CK_IS_GPIO != GPIO_NONE)
        #define PAD_SPI2_CK_OEN (PAD_SPI2_CK_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_SPI2_CK_OUT (PAD_SPI2_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x1e90, PAD_SPI2_CK_OUT, BIT6),
        _RVM1(0x1e90, PAD_SPI2_CK_OEN, BIT2),
        //reg_ld_spi2_config
        _RVM1(0x1eb4, 0, BIT1),   //reg[101eb4]#1 = 0b
        //reg_ld_spi3_config
        _RVM1(0x1eb4, 0, BIT2),   //reg[101eb4]#2 = 0b
        //reg_pwm5_mode[1:0]
        _RVM1(0x1eb2, 0, BIT1 | BIT0),   //reg[101eb2]#1 ~ #0 = 00b
        //reg_pwm5_dim_mode
        _RVM1(0x1eef, 0, BIT5),   //reg[101eef]#5 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_SPI2_DI_IS_GPIO != GPIO_NONE)
        #define PAD_SPI2_DI_OEN (PAD_SPI2_DI_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_SPI2_DI_OUT (PAD_SPI2_DI_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
        _RVM1(0x1e90, PAD_SPI2_DI_OUT, BIT7),
        _RVM1(0x1e90, PAD_SPI2_DI_OEN, BIT3),
        //reg_agc_dbg
        _RVM1(0x1e06, 0, BIT5),   //reg[101e06]#5 = 0b
        //reg_ld_spi2_config
        _RVM1(0x1eb4, 0, BIT1),   //reg[101eb4]#1 = 0b
        //reg_ld_spi3_config
        _RVM1(0x1eb4, 0, BIT2),   //reg[101eb4]#2 = 0b
        //reg_pwm4_mode[1:0]
        _RVM1(0x1ea2, 0, BIT5 | BIT4),   //reg[101ea2]#5 ~ #4 = 00b
        //reg_pwm4_dim_mode
        _RVM1(0x1eef, 0, BIT4),   //reg[101eef]#4 = 0b
        //reg_chiptop_dummy_3[0]
        _RVM1(0x1e3e, 0, BIT0),   //reg[101e3e]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_VSYNC_LIKE_IS_GPIO != GPIO_NONE)
        #define PAD_VSYNC_LIKE_OEN (PAD_VSYNC_LIKE_IS_GPIO == GPIO_IN ? BIT4: 0)
        #define PAD_VSYNC_LIKE_OUT (PAD_VSYNC_LIKE_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
        _RVM1(0x1e91, PAD_VSYNC_LIKE_OUT, BIT5),
        _RVM1(0x1e91, PAD_VSYNC_LIKE_OEN, BIT4),
        //reg_ld_spi1cz_config[1:0]
        _RVM1(0x1eb2, 0, BIT4 | BIT3),   //reg[101eb2]#4 ~ #3 = 00b
        //reg_ld_spi1cz_config[1:0]
        _RVM1(0x1eb2, 0, BIT4 | BIT3),   //reg[101eb2]#4 ~ #3 = 00b
        //reg_ld_spi1cz_config[1:0]
        _RVM1(0x1eb2, 0, BIT4 | BIT3),   //reg[101eb2]#4 ~ #3 = 00b
        //reg_pwm5_mode[1:0]
        _RVM1(0x1eb2, 0, BIT1 | BIT0),   //reg[101eb2]#1 ~ #0 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_CEZ_IS_GPIO != GPIO_NONE)
        #define PAD_NAND_CEZ_OEN (PAD_NAND_CEZ_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_NAND_CEZ_OUT (PAD_NAND_CEZ_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x1e8c, PAD_NAND_CEZ_OUT, BIT0),
        _RVM1(0x1e8e, PAD_NAND_CEZ_OEN, BIT0),
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e86, BIT1, BIT1),   //reg[101e86] #1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_nand_mode[0]
        _RVM1(0x1e17, 0, BIT4),   //reg[101e17]#4 = 0b
        //reg_emmc_config[0]
        _RVM1(0x1ebb, 0, BIT6),   //reg[101ebb]#6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_CEZ1_IS_GPIO != GPIO_NONE)
        #define PAD_NAND_CEZ1_OEN (PAD_NAND_CEZ1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_NAND_CEZ1_OUT (PAD_NAND_CEZ1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x1e8c, PAD_NAND_CEZ1_OUT, BIT1),
        _RVM1(0x1e8e, PAD_NAND_CEZ1_OEN, BIT1),
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e86, BIT1, BIT1),   //reg[101e86] #1 = 1b
        //reg_nand_cs1_en
        _RVM1(0x1ea1, 0, BIT2),   //reg[101ea1]#2 = 0b
        //reg_emmc_config[0]
        _RVM1(0x1ebb, 0, BIT6),   //reg[101ebb]#6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_CLE_IS_GPIO != GPIO_NONE)
        #define PAD_NAND_CLE_OEN (PAD_NAND_CLE_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_NAND_CLE_OUT (PAD_NAND_CLE_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x1e8c, PAD_NAND_CLE_OUT, BIT2),
        _RVM1(0x1e8e, PAD_NAND_CLE_OEN, BIT2),
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e86, BIT1, BIT1),   //reg[101e86] #1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_nand_mode[0]
        _RVM1(0x1e17, 0, BIT4),   //reg[101e17]#4 = 0b
        //reg_emmc_config[0]
        _RVM1(0x1ebb, 0, BIT6),   //reg[101ebb]#6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_REZ_IS_GPIO != GPIO_NONE)
        #define PAD_NAND_REZ_OEN (PAD_NAND_REZ_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_NAND_REZ_OUT (PAD_NAND_REZ_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
        _RVM1(0x1e8c, PAD_NAND_REZ_OUT, BIT3),
        _RVM1(0x1e8e, PAD_NAND_REZ_OEN, BIT3),
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e86, BIT1, BIT1),   //reg[101e86] #1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_nand_mode[0]
        _RVM1(0x1e17, 0, BIT4),   //reg[101e17]#4 = 0b
        //reg_emmc_config[0]
        _RVM1(0x1ebb, 0, BIT6),   //reg[101ebb]#6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_WEZ_IS_GPIO != GPIO_NONE)
        #define PAD_NAND_WEZ_OEN (PAD_NAND_WEZ_IS_GPIO == GPIO_IN ? BIT4: 0)
        #define PAD_NAND_WEZ_OUT (PAD_NAND_WEZ_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
        _RVM1(0x1e8c, PAD_NAND_WEZ_OUT, BIT4),
        _RVM1(0x1e8e, PAD_NAND_WEZ_OEN, BIT4),
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e86, BIT1, BIT1),   //reg[101e86] #1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_nand_mode[0]
        _RVM1(0x1e17, 0, BIT4),   //reg[101e17]#4 = 0b
        //reg_emmc_config[0]
        _RVM1(0x1ebb, 0, BIT6),   //reg[101ebb]#6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_WPZ_IS_GPIO != GPIO_NONE)
        #define PAD_NAND_WPZ_OEN (PAD_NAND_WPZ_IS_GPIO == GPIO_IN ? BIT5: 0)
        #define PAD_NAND_WPZ_OUT (PAD_NAND_WPZ_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
        _RVM1(0x1e8c, PAD_NAND_WPZ_OUT, BIT5),
        _RVM1(0x1e8e, PAD_NAND_WPZ_OEN, BIT5),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_nand_mode[0]
        _RVM1(0x1e17, 0, BIT4),   //reg[101e17]#4 = 0b
        //reg_emmc_config[0]
        _RVM1(0x1ebb, 0, BIT6),   //reg[101ebb]#6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_ALE_IS_GPIO != GPIO_NONE)
        #define PAD_NAND_ALE_OEN (PAD_NAND_ALE_IS_GPIO == GPIO_IN ? BIT6: 0)
        #define PAD_NAND_ALE_OUT (PAD_NAND_ALE_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x1e8c, PAD_NAND_ALE_OUT, BIT6),
        _RVM1(0x1e8e, PAD_NAND_ALE_OEN, BIT6),
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e86, BIT1, BIT1),   //reg[101e86] #1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_nand_mode[0]
        _RVM1(0x1e17, 0, BIT4),   //reg[101e17]#4 = 0b
        //reg_emmc_config[0]
        _RVM1(0x1ebb, 0, BIT6),   //reg[101ebb]#6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_RBZ_IS_GPIO != GPIO_NONE)
        #define PAD_NAND_RBZ_OEN (PAD_NAND_RBZ_IS_GPIO == GPIO_IN ? BIT7: 0)
        #define PAD_NAND_RBZ_OUT (PAD_NAND_RBZ_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
        _RVM1(0x1e8c, PAD_NAND_RBZ_OUT, BIT7),
        _RVM1(0x1e8e, PAD_NAND_RBZ_OEN, BIT7),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_nand_mode[0]
        _RVM1(0x1e17, 0, BIT4),   //reg[101e17]#4 = 0b
        //reg_emmc_config[0]
        _RVM1(0x1ebb, 0, BIT6),   //reg[101ebb]#6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM2_CE_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM2_CE_N_OEN (PAD_PCM2_CE_N_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_PCM2_CE_N_OUT (PAD_PCM2_CE_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x1e7b, PAD_PCM2_CE_N_OUT, BIT0),
        _RVM1(0x1e81, PAD_PCM2_CE_N_OEN, BIT0),
        //reg_pcm2ctrlconfig
        _RVM1(0x1e9f, 0, BIT5),   //reg[101e9f]#5 = 0b
        //reg_sdio_config[1:0]
        _RVM1(0x1eb7, 0, BIT3 | BIT2),   //reg[101eb7]#3 ~ #2 = 00b
        //reg_extint0
        _RVM1(0x1ee0, 0, BIT0),   //reg[101ee0]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM2_IRQA_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM2_IRQA_N_OEN (PAD_PCM2_IRQA_N_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM2_IRQA_N_OUT (PAD_PCM2_IRQA_N_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x1e7b, PAD_PCM2_IRQA_N_OUT, BIT1),
        _RVM1(0x1e81, PAD_PCM2_IRQA_N_OEN, BIT1),
        //reg_pcm2ctrlconfig
        _RVM1(0x1e9f, 0, BIT5),   //reg[101e9f]#5 = 0b
        //reg_sdio_config[1:0]
        _RVM1(0x1eb7, 0, BIT3 | BIT2),   //reg[101eb7]#3 ~ #2 = 00b
        //reg_extint2
        _RVM1(0x1ee0, 0, BIT2),   //reg[101ee0]#2 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM2_WAIT_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM2_WAIT_N_OEN (PAD_PCM2_WAIT_N_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_PCM2_WAIT_N_OUT (PAD_PCM2_WAIT_N_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x1e7b, PAD_PCM2_WAIT_N_OUT, BIT2),
        _RVM1(0x1e81, PAD_PCM2_WAIT_N_OEN, BIT2),
        //reg_pcm2ctrlconfig
        _RVM1(0x1e9f, 0, BIT5),   //reg[101e9f]#5 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb7, 0, BIT1 | BIT0),   //reg[101eb7]#1 ~ #0 = 00b
        //reg_sd_config[1:0]
        _RVM1(0x1eb7, 0, BIT1 | BIT0),   //reg[101eb7]#1 ~ #0 = 00b
        //reg_sdio_config[1:0]
        _RVM1(0x1eb7, 0, BIT3 | BIT2),   //reg[101eb7]#3 ~ #2 = 00b
        //reg_sdio_config[1:0]
        _RVM1(0x1eb7, 0, BIT3 | BIT2),   //reg[101eb7]#3 ~ #2 = 00b
        //reg_chiptop_dummy_3[1]
        _RVM1(0x1e3e, 0, BIT1),   //reg[101e3e]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM2_RESET_IS_GPIO != GPIO_NONE)
        #define PAD_PCM2_RESET_OEN (PAD_PCM2_RESET_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_PCM2_RESET_OUT (PAD_PCM2_RESET_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
        _RVM1(0x1e7b, PAD_PCM2_RESET_OUT, BIT3),
        _RVM1(0x1e81, PAD_PCM2_RESET_OEN, BIT3),
        //reg_pcm2ctrlconfig
        _RVM1(0x1e9f, 0, BIT5),   //reg[101e9f]#5 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb7, 0, BIT1 | BIT0),   //reg[101eb7]#1 ~ #0 = 00b
        //reg_sd_config[1:0]
        _RVM1(0x1eb7, 0, BIT1 | BIT0),   //reg[101eb7]#1 ~ #0 = 00b
        //reg_sdio_config[1:0]
        _RVM1(0x1eb7, 0, BIT3 | BIT2),   //reg[101eb7]#3 ~ #2 = 00b
        //reg_sdio_config[1:0]
        _RVM1(0x1eb7, 0, BIT3 | BIT2),   //reg[101eb7]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM2_CD_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM2_CD_N_OEN (PAD_PCM2_CD_N_IS_GPIO == GPIO_IN ? BIT4: 0)
        #define PAD_PCM2_CD_N_OUT (PAD_PCM2_CD_N_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
        _RVM1(0x1e7b, PAD_PCM2_CD_N_OUT, BIT4),
        _RVM1(0x1e81, PAD_PCM2_CD_N_OEN, BIT4),
        //reg_pcm_pe[25]
        _RVM1(0x1e85, BIT1, BIT1),   //reg[101e85]#1 = 1b
        //reg_pcm2ctrlconfig
        _RVM1(0x1e9f, 0, BIT5),   //reg[101e9f]#5 = 0b
        //reg_pcm2_cdn_config
        _RVM1(0x1eb3, 0, BIT2),   //reg[101eb3]#2 = 0b
        //reg_extint3
        _RVM1(0x1ee0, 0, BIT3),   //reg[101ee0]#3 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_D3_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_D3_OEN (PAD_PCM_D3_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_PCM_D3_OUT (PAD_PCM_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x1e76, PAD_PCM_D3_OUT, BIT0),
        _RVM1(0x1e7c, PAD_PCM_D3_OEN, BIT0),
        //reg_pcm_pe[11]
        _RVM1(0x1e83, BIT3, BIT3),   //reg[101e83]#3 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_mcu_jtag_mode[1:0]
        //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6 = 00b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_D4_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_D4_OEN (PAD_PCM_D4_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_D4_OUT (PAD_PCM_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x1e76, PAD_PCM_D4_OUT, BIT1),
        _RVM1(0x1e7c, PAD_PCM_D4_OEN, BIT1),
        //reg_pcm_pe[12]
        _RVM1(0x1e83, BIT4, BIT4),   //reg[101e83]#4 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_mcu_jtag_mode[1:0]
        //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6 = 00b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_D5_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_D5_OEN (PAD_PCM_D5_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_PCM_D5_OUT (PAD_PCM_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x1e76, PAD_PCM_D5_OUT, BIT2),
        _RVM1(0x1e7c, PAD_PCM_D5_OEN, BIT2),
        //reg_pcm_pe[13]
        _RVM1(0x1e83, BIT5, BIT5),   //reg[101e83]#5 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_mcu_jtag_mode[1:0]
        //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6 = 00b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_D6_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_D6_OEN (PAD_PCM_D6_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_PCM_D6_OUT (PAD_PCM_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
        _RVM1(0x1e76, PAD_PCM_D6_OUT, BIT3),
        _RVM1(0x1e7c, PAD_PCM_D6_OEN, BIT3),
        //reg_pcm_pe[14]
        _RVM1(0x1e83, BIT6, BIT6),   //reg[101e83]#6 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_mcu_jtag_mode[1:0]
        //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6 = 00b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_D7_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_D7_OEN (PAD_PCM_D7_IS_GPIO == GPIO_IN ? BIT4: 0)
        #define PAD_PCM_D7_OUT (PAD_PCM_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
        _RVM1(0x1e76, PAD_PCM_D7_OUT, BIT4),
        _RVM1(0x1e7c, PAD_PCM_D7_OEN, BIT4),
        //reg_pcm_pe[15]
        _RVM1(0x1e83, BIT7, BIT7),   //reg[101e83]#7 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_CE_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_CE_N_OEN (PAD_PCM_CE_N_IS_GPIO == GPIO_IN ? BIT5: 0)
        #define PAD_PCM_CE_N_OUT (PAD_PCM_CE_N_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
        _RVM1(0x1e76, PAD_PCM_CE_N_OUT, BIT5),
        _RVM1(0x1e7c, PAD_PCM_CE_N_OEN, BIT5),
        //reg_pcm_pe[0]
        _RVM1(0x1e82, BIT0, BIT0),   //reg[101e82]#0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmctrlconfig
        _RVM1(0x1e9f, 0, BIT7),   //reg[101e9f]#7 = 0b
        //reg_cictrlconfig
        _RVM1(0x1ec8, 0, BIT1),   //reg[101ec8]#1 = 0b
        //reg_sm_config[1:0]
        _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A10_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A10_OEN (PAD_PCM_A10_IS_GPIO == GPIO_IN ? BIT6: 0)
        #define PAD_PCM_A10_OUT (PAD_PCM_A10_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x1e76, PAD_PCM_A10_OUT, BIT6),
        _RVM1(0x1e7c, PAD_PCM_A10_OEN, BIT6),
        //reg_pcm_pe[18]
        _RVM1(0x1e84, BIT2, BIT2),   //reg[101e84]#2 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_sdio_config[1:0]
        _RVM1(0x1eb7, 0, BIT3 | BIT2),   //reg[101eb7]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_OE_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_OE_N_OEN (PAD_PCM_OE_N_IS_GPIO == GPIO_IN ? BIT7: 0)
        #define PAD_PCM_OE_N_OUT (PAD_PCM_OE_N_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
        _RVM1(0x1e76, PAD_PCM_OE_N_OUT, BIT7),
        _RVM1(0x1e7c, PAD_PCM_OE_N_OEN, BIT7),
        //reg_pcm_pe[1]
        _RVM1(0x1e82, BIT1, BIT1),   //reg[101e82]#1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmctrlconfig
        _RVM1(0x1e9f, 0, BIT7),   //reg[101e9f]#7 = 0b
        //reg_sm_config[1:0]
        _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A11_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A11_OEN (PAD_PCM_A11_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_PCM_A11_OUT (PAD_PCM_A11_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x1e77, PAD_PCM_A11_OUT, BIT0),
        _RVM1(0x1e7d, PAD_PCM_A11_OEN, BIT0),
        //reg_pcm_pe[19]
        _RVM1(0x1e84, BIT3, BIT3),   //reg[101e84]#3 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_sdio_config[1:0]
        _RVM1(0x1eb7, 0, BIT3 | BIT2),   //reg[101eb7]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_IORD_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_IORD_N_OEN (PAD_PCM_IORD_N_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_IORD_N_OUT (PAD_PCM_IORD_N_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x1e77, PAD_PCM_IORD_N_OUT, BIT1),
        _RVM1(0x1e7d, PAD_PCM_IORD_N_OEN, BIT1),
        //reg_pcm_pe[2]
        _RVM1(0x1e82, BIT2, BIT2),   //reg[101e82]#2 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmctrlconfig
        _RVM1(0x1e9f, 0, BIT7),   //reg[101e9f]#7 = 0b
        //reg_cictrlconfig
        _RVM1(0x1ec8, 0, BIT1),   //reg[101ec8]#1 = 0b
        //reg_sm_config[1:0]
        _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A9_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A9_OEN (PAD_PCM_A9_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_PCM_A9_OUT (PAD_PCM_A9_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x1e77, PAD_PCM_A9_OUT, BIT2),
        _RVM1(0x1e7d, PAD_PCM_A9_OEN, BIT2),
        //reg_pcm_pe[17]
        _RVM1(0x1e84, BIT1, BIT1),   //reg[101e84]#1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_sdio_config[1:0]
        _RVM1(0x1eb7, 0, BIT3 | BIT2),   //reg[101eb7]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_IOWR_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_IOWR_N_OEN (PAD_PCM_IOWR_N_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_PCM_IOWR_N_OUT (PAD_PCM_IOWR_N_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
        _RVM1(0x1e77, PAD_PCM_IOWR_N_OUT, BIT3),
        _RVM1(0x1e7d, PAD_PCM_IOWR_N_OEN, BIT3),
        //reg_pcm_pe[3]
        _RVM1(0x1e82, BIT3, BIT3),   //reg[101e82]#3 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmctrlconfig
        _RVM1(0x1e9f, 0, BIT7),   //reg[101e9f]#7 = 0b
        //reg_cictrlconfig
        _RVM1(0x1ec8, 0, BIT1),   //reg[101ec8]#1 = 0b
        //reg_sm_config[1:0]
        _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A8_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A8_OEN (PAD_PCM_A8_IS_GPIO == GPIO_IN ? BIT4: 0)
        #define PAD_PCM_A8_OUT (PAD_PCM_A8_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
        _RVM1(0x1e77, PAD_PCM_A8_OUT, BIT4),
        _RVM1(0x1e7d, PAD_PCM_A8_OEN, BIT4),
        //reg_pcm_pe[16]
        _RVM1(0x1e84, BIT0, BIT0),   //reg[101e84]#0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_sdio_config[1:0]
        _RVM1(0x1eb7, 0, BIT3 | BIT2),   //reg[101eb7]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A13_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A13_OEN (PAD_PCM_A13_IS_GPIO == GPIO_IN ? BIT5: 0)
        #define PAD_PCM_A13_OUT (PAD_PCM_A13_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
        _RVM1(0x1e77, PAD_PCM_A13_OUT, BIT5),
        _RVM1(0x1e7d, PAD_PCM_A13_OEN, BIT5),
        //reg_pcm_pe[21]
        _RVM1(0x1e84, BIT5, BIT5),   //reg[101e84]#5 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb7, 0, BIT1 | BIT0),   //reg[101eb7]#1 ~ #0 = 00b
        //reg_sdio_config[1:0]
        _RVM1(0x1eb7, 0, BIT3 | BIT2),   //reg[101eb7]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A14_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A14_OEN (PAD_PCM_A14_IS_GPIO == GPIO_IN ? BIT6: 0)
        #define PAD_PCM_A14_OUT (PAD_PCM_A14_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x1e77, PAD_PCM_A14_OUT, BIT6),
        _RVM1(0x1e7d, PAD_PCM_A14_OEN, BIT6),
        //reg_pcm_pe[22]
        _RVM1(0x1e84, BIT6, BIT6),   //reg[101e84]#6 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb7, 0, BIT1 | BIT0),   //reg[101eb7]#1 ~ #0 = 00b
        //reg_sdio_config[1:0]
        _RVM1(0x1eb7, 0, BIT3 | BIT2),   //reg[101eb7]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_WE_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_WE_N_OEN (PAD_PCM_WE_N_IS_GPIO == GPIO_IN ? BIT7: 0)
        #define PAD_PCM_WE_N_OUT (PAD_PCM_WE_N_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
        _RVM1(0x1e77, PAD_PCM_WE_N_OUT, BIT7),
        _RVM1(0x1e7d, PAD_PCM_WE_N_OEN, BIT7),
        //reg_pcm_pe[4]
        _RVM1(0x1e82, BIT4, BIT4),   //reg[101e82]#4 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmctrlconfig
        _RVM1(0x1e9f, 0, BIT7),   //reg[101e9f]#7 = 0b
        //reg_sm_config[1:0]
        _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_IRQA_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_IRQA_N_OEN (PAD_PCM_IRQA_N_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_PCM_IRQA_N_OUT (PAD_PCM_IRQA_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x1e78, PAD_PCM_IRQA_N_OUT, BIT0),
        _RVM1(0x1e7e, PAD_PCM_IRQA_N_OEN, BIT0),
        //reg_pcm_pe[5]
        _RVM1(0x1e82, BIT5, BIT5),   //reg[101e82]#5 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmctrlconfig
        _RVM1(0x1e9f, 0, BIT7),   //reg[101e9f]#7 = 0b
        //reg_cictrlconfig
        _RVM1(0x1ec8, 0, BIT1),   //reg[101ec8]#1 = 0b
        //reg_sm_config[1:0]
        _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A12_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A12_OEN (PAD_PCM_A12_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_A12_OUT (PAD_PCM_A12_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x1e78, PAD_PCM_A12_OUT, BIT1),
        _RVM1(0x1e7e, PAD_PCM_A12_OEN, BIT1),
        //reg_pcm_pe[20]
        _RVM1(0x1e84, BIT4, BIT4),   //reg[101e84]#4 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb7, 0, BIT1 | BIT0),   //reg[101eb7]#1 ~ #0 = 00b
        //reg_sdio_config[1:0]
        _RVM1(0x1eb7, 0, BIT3 | BIT2),   //reg[101eb7]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A7_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A7_OEN (PAD_PCM_A7_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_PCM_A7_OUT (PAD_PCM_A7_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x1e78, PAD_PCM_A7_OUT, BIT2),
        _RVM1(0x1e7e, PAD_PCM_A7_OEN, BIT2),
        //reg_pcm_a_pe[7]
        _RVM1(0x1e18, BIT7, BIT7),   //reg[101e18]#7 = 1b
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e86, BIT1, BIT1),   //reg[101e86] #1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_nand_mode[0]
        _RVM1(0x1e17, 0, BIT4),   //reg[101e17]#4 = 0b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb7, 0, BIT1 | BIT0),   //reg[101eb7]#1 ~ #0 = 00b
        //reg_sdio_config[1:0]
        _RVM1(0x1eb7, 0, BIT3 | BIT2),   //reg[101eb7]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A6_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A6_OEN (PAD_PCM_A6_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_PCM_A6_OUT (PAD_PCM_A6_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
        _RVM1(0x1e78, PAD_PCM_A6_OUT, BIT3),
        _RVM1(0x1e7e, PAD_PCM_A6_OEN, BIT3),
        //reg_pcm_a_pe[6]
        _RVM1(0x1e18, BIT6, BIT6),   //reg[101e18]#6 = 1b
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e86, BIT1, BIT1),   //reg[101e86] #1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_nand_mode[0]
        _RVM1(0x1e17, 0, BIT4),   //reg[101e17]#4 = 0b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb7, 0, BIT1 | BIT0),   //reg[101eb7]#1 ~ #0 = 00b
        //reg_sdio_config[1:0]
        _RVM1(0x1eb7, 0, BIT3 | BIT2),   //reg[101eb7]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A5_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A5_OEN (PAD_PCM_A5_IS_GPIO == GPIO_IN ? BIT4: 0)
        #define PAD_PCM_A5_OUT (PAD_PCM_A5_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
        _RVM1(0x1e78, PAD_PCM_A5_OUT, BIT4),
        _RVM1(0x1e7e, PAD_PCM_A5_OEN, BIT4),
        //reg_pcm_a_pe[5]
        _RVM1(0x1e18, BIT5, BIT5),   //reg[101e18]#5 = 1b
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e86, BIT1, BIT1),   //reg[101e86] #1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_nand_mode[0]
        _RVM1(0x1e17, 0, BIT4),   //reg[101e17]#4 = 0b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb7, 0, BIT1 | BIT0),   //reg[101eb7]#1 ~ #0 = 00b
        //reg_sdio_config[1:0]
        _RVM1(0x1eb7, 0, BIT3 | BIT2),   //reg[101eb7]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_WAIT_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_WAIT_N_OEN (PAD_PCM_WAIT_N_IS_GPIO == GPIO_IN ? BIT5: 0)
        #define PAD_PCM_WAIT_N_OUT (PAD_PCM_WAIT_N_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
        _RVM1(0x1e78, PAD_PCM_WAIT_N_OUT, BIT5),
        _RVM1(0x1e7e, PAD_PCM_WAIT_N_OEN, BIT5),
        //reg_pcm_pe[6]
        _RVM1(0x1e82, BIT6, BIT6),   //reg[101e82]#6 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmctrlconfig
        _RVM1(0x1e9f, 0, BIT7),   //reg[101e9f]#7 = 0b
        //reg_cictrlconfig
        _RVM1(0x1ec8, 0, BIT1),   //reg[101ec8]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A4_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A4_OEN (PAD_PCM_A4_IS_GPIO == GPIO_IN ? BIT6: 0)
        #define PAD_PCM_A4_OUT (PAD_PCM_A4_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x1e78, PAD_PCM_A4_OUT, BIT6),
        _RVM1(0x1e7e, PAD_PCM_A4_OEN, BIT6),
        //reg_pcm_a_pe[4]
        _RVM1(0x1e18, BIT4, BIT4),   //reg[101e18]#4 = 1b
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e86, BIT1, BIT1),   //reg[101e86] #1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_nand_mode[0]
        _RVM1(0x1e17, 0, BIT4),   //reg[101e17]#4 = 0b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb7, 0, BIT1 | BIT0),   //reg[101eb7]#1 ~ #0 = 00b
        //reg_sdio_config[1:0]
        _RVM1(0x1eb7, 0, BIT3 | BIT2),   //reg[101eb7]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A3_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A3_OEN (PAD_PCM_A3_IS_GPIO == GPIO_IN ? BIT7: 0)
        #define PAD_PCM_A3_OUT (PAD_PCM_A3_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
        _RVM1(0x1e78, PAD_PCM_A3_OUT, BIT7),
        _RVM1(0x1e7e, PAD_PCM_A3_OEN, BIT7),
        //reg_pcm_a_pe[3]
        _RVM1(0x1e18, BIT3, BIT3),   //reg[101e18]#3 = 1b
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e86, BIT1, BIT1),   //reg[101e86] #1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_nand_mode[0]
        _RVM1(0x1e17, 0, BIT4),   //reg[101e17]#4 = 0b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A2_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A2_OEN (PAD_PCM_A2_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_PCM_A2_OUT (PAD_PCM_A2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x1e79, PAD_PCM_A2_OUT, BIT0),
        _RVM1(0x1e7f, PAD_PCM_A2_OEN, BIT0),
        //reg_pcm_a_pe[2]
        _RVM1(0x1e18, BIT2, BIT2),   //reg[101e18]#2 = 1b
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e86, BIT1, BIT1),   //reg[101e86] #1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_nand_mode[0]
        _RVM1(0x1e17, 0, BIT4),   //reg[101e17]#4 = 0b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_REG_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_REG_N_OEN (PAD_PCM_REG_N_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_REG_N_OUT (PAD_PCM_REG_N_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x1e79, PAD_PCM_REG_N_OUT, BIT1),
        _RVM1(0x1e7f, PAD_PCM_REG_N_OEN, BIT1),
        //reg_pcm_pe[7]
        _RVM1(0x1e82, BIT7, BIT7),   //reg[101e82]#7 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_pcmctrlconfig
        _RVM1(0x1e9f, 0, BIT7),   //reg[101e9f]#7 = 0b
        //reg_cictrlconfig
        _RVM1(0x1ec8, 0, BIT1),   //reg[101ec8]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A1_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A1_OEN (PAD_PCM_A1_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_PCM_A1_OUT (PAD_PCM_A1_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x1e79, PAD_PCM_A1_OUT, BIT2),
        _RVM1(0x1e7f, PAD_PCM_A1_OEN, BIT2),
        //reg_pcm_a_pe[1]
        _RVM1(0x1e18, BIT1, BIT1),   //reg[101e18]#1 = 1b
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e86, BIT1, BIT1),   //reg[101e86] #1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_nand_mode[0]
        _RVM1(0x1e17, 0, BIT4),   //reg[101e17]#4 = 0b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A0_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A0_OEN (PAD_PCM_A0_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_PCM_A0_OUT (PAD_PCM_A0_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
        _RVM1(0x1e79, PAD_PCM_A0_OUT, BIT3),
        _RVM1(0x1e7f, PAD_PCM_A0_OEN, BIT3),
        //reg_pcm_a_pe[0]
        _RVM1(0x1e18, BIT0, BIT0),   //reg[101e18]#0 = 1b
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e86, BIT1, BIT1),   //reg[101e86] #1 = 1b
        //reg_nand_mode[0]
        _RVM1(0x1e17, 0, BIT4),   //reg[101e17]#4 = 0b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_D0_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_D0_OEN (PAD_PCM_D0_IS_GPIO == GPIO_IN ? BIT4: 0)
        #define PAD_PCM_D0_OUT (PAD_PCM_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
        _RVM1(0x1e79, PAD_PCM_D0_OUT, BIT4),
        _RVM1(0x1e7f, PAD_PCM_D0_OEN, BIT4),
        //reg_pcm_pe[8]
        _RVM1(0x1e83, BIT0, BIT0),   //reg[101e83]#0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_D1_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_D1_OEN (PAD_PCM_D1_IS_GPIO == GPIO_IN ? BIT5: 0)
        #define PAD_PCM_D1_OUT (PAD_PCM_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
        _RVM1(0x1e79, PAD_PCM_D1_OUT, BIT5),
        _RVM1(0x1e7f, PAD_PCM_D1_OEN, BIT5),
        //reg_pcm_pe[9]
        _RVM1(0x1e83, BIT1, BIT1),   //reg[101e83]#1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_D2_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_D2_OEN (PAD_PCM_D2_IS_GPIO == GPIO_IN ? BIT6: 0)
        #define PAD_PCM_D2_OUT (PAD_PCM_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x1e79, PAD_PCM_D2_OUT, BIT6),
        _RVM1(0x1e7f, PAD_PCM_D2_OEN, BIT6),
        //reg_pcm_pe[10]
        _RVM1(0x1e83, BIT2, BIT2),   //reg[101e83]#2 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pcmadconfig
        _RVM1(0x1e9f, 0, BIT6),   //reg[101e9f]#6 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_RESET_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_RESET_OEN (PAD_PCM_RESET_IS_GPIO == GPIO_IN ? BIT7: 0)
        #define PAD_PCM_RESET_OUT (PAD_PCM_RESET_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
        _RVM1(0x1e79, PAD_PCM_RESET_OUT, BIT7),
        _RVM1(0x1e7f, PAD_PCM_RESET_OEN, BIT7),
        //reg_pcm_pe[23]
        _RVM1(0x1e84, BIT7, BIT7),   //reg[101e84]#7 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_pcmctrlconfig
        _RVM1(0x1e9f, 0, BIT7),   //reg[101e9f]#7 = 0b
        //reg_cictrlconfig
        _RVM1(0x1ec8, 0, BIT1),   //reg[101ec8]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_CD_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_CD_N_OEN (PAD_PCM_CD_N_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_PCM_CD_N_OUT (PAD_PCM_CD_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x1e7a, PAD_PCM_CD_N_OUT, BIT0),
        _RVM1(0x1e80, PAD_PCM_CD_N_OEN, BIT0),
        //reg_pcm_pe[24]
        _RVM1(0x1e85, BIT0, BIT0),   //reg[101e85]#0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_pcmctrlconfig
        _RVM1(0x1e9f, 0, BIT7),   //reg[101e9f]#7 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PWM0_IS_GPIO != GPIO_NONE)
        #define PAD_PWM0_OEN (PAD_PWM0_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_PWM0_OUT (PAD_PWM0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x1e98, PAD_PWM0_OUT, BIT0),
        _RVM1(0x1e96, PAD_PWM0_OEN, BIT0),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pwm0_mode
        _RVM1(0x1ea2, 0, BIT0),   //reg[101ea2]#0 = 0b
        //reg_pwm0_dim_mode
        _RVM1(0x1eef, 0, BIT0),   //reg[101eef]#0 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb7, 0, BIT1 | BIT0),   //reg[101eb7]#1 ~ #0 = 00b
        //reg_sdio_config[1:0]
        _RVM1(0x1eb7, 0, BIT3 | BIT2),   //reg[101eb7]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PWM1_IS_GPIO != GPIO_NONE)
        #define PAD_PWM1_OEN (PAD_PWM1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PWM1_OUT (PAD_PWM1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x1e98, PAD_PWM1_OUT, BIT1),
        _RVM1(0x1e96, PAD_PWM1_OEN, BIT1),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pwm1_mode
        _RVM1(0x1ea2, 0, BIT1),   //reg[101ea2]#1 = 0b
        //reg_pwm1_dim_mode
        _RVM1(0x1eef, 0, BIT1),   //reg[101eef]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PWM2_IS_GPIO != GPIO_NONE)
        #define PAD_PWM2_OEN (PAD_PWM2_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_PWM2_OUT (PAD_PWM2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x1e98, PAD_PWM2_OUT, BIT2),
        _RVM1(0x1e96, PAD_PWM2_OEN, BIT2),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_pwm2_mode
        _RVM1(0x1ea2, 0, BIT2),   //reg[101ea2]#2 = 0b
        //reg_pwm2_dim_mode
        _RVM1(0x1eef, 0, BIT2),   //reg[101eef]#2 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PWM3_IS_GPIO != GPIO_NONE)
        #define PAD_PWM3_OEN (PAD_PWM3_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_PWM3_OUT (PAD_PWM3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
        _RVM1(0x1e98, PAD_PWM3_OUT, BIT3),
        _RVM1(0x1e96, PAD_PWM3_OEN, BIT3),
        //reg_pwm3_mode
        _RVM1(0x1ea2, 0, BIT3),   //reg[101ea2]#3 = 0b
        //reg_pwm3_dim_mode
        _RVM1(0x1eef, 0, BIT3),   //reg[101eef]#3 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PWM4_IS_GPIO != GPIO_NONE)
        #define PAD_PWM4_OEN (PAD_PWM4_IS_GPIO == GPIO_IN ? BIT4: 0)
        #define PAD_PWM4_OUT (PAD_PWM4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
        _RVM1(0x1e98, PAD_PWM4_OUT, BIT4),
        _RVM1(0x1e96, PAD_PWM4_OEN, BIT4),
        //reg_i2smutemode[1:0]
        _RVM1(0x1e05, 0, BIT7 | BIT6),   //reg[101e05]#7 ~ #6 = 00b
        //reg_pwm4_mode[1:0]
        _RVM1(0x1ea2, 0, BIT5 | BIT4),   //reg[101ea2]#5 ~ #4 = 00b
        //reg_tserrout[1:0]
        _RVM1(0x1ea2, 0, BIT7 | BIT6),   //reg[101ea2]#7 ~ #6 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PWM5_IS_GPIO != GPIO_NONE)
        #define PAD_PWM5_OEN (PAD_PWM5_IS_GPIO == GPIO_IN ? BIT5: 0)
        #define PAD_PWM5_OUT (PAD_PWM5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
        _RVM1(0x1e98, PAD_PWM5_OUT, BIT5),
        _RVM1(0x1e96, PAD_PWM5_OEN, BIT5),
        //reg_sm_config[1:0]
        _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_EMMC_RSTN_IS_GPIO != GPIO_NONE)
        #define PAD_EMMC_RSTN_OEN (PAD_EMMC_RSTN_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_EMMC_RSTN_OUT (PAD_EMMC_RSTN_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x0a40, PAD_EMMC_RSTN_OUT, BIT0),
        _RVM1(0x0a40, PAD_EMMC_RSTN_OEN, BIT1),
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e86, BIT1, BIT1),   //reg[101e86] #1 = 1b
        //reg_nand_cs3_en
        _RVM1(0x1e16, 0, BIT1),   //reg[101e16]#1 = 0b
        //reg_emmc_rstn_en
        _RVM1(0x1e86, 0, BIT3),   //reg[101e86]#3 = 0b
        //reg_emmc_config[0]
        _RVM1(0x1ebb, 0, BIT6),   //reg[101ebb]#6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_EMMC_CLK_IS_GPIO != GPIO_NONE)
        #define PAD_EMMC_CLK_OEN (PAD_EMMC_CLK_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_EMMC_CLK_OUT (PAD_EMMC_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x0a41, PAD_EMMC_CLK_OUT, BIT0),
        _RVM1(0x0a41, PAD_EMMC_CLK_OEN, BIT1),
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e86, BIT1, BIT1),   //reg[101e86] #1 = 1b
        //reg_emmc_config[0]
        _RVM1(0x1ebb, 0, BIT6),   //reg[101ebb]#6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_EMMC_CMD_IS_GPIO != GPIO_NONE)
        #define PAD_EMMC_CMD_OEN (PAD_EMMC_CMD_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_EMMC_CMD_OUT (PAD_EMMC_CMD_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x0a42, PAD_EMMC_CMD_OUT, BIT0),
        _RVM1(0x0a42, PAD_EMMC_CMD_OEN, BIT1),
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e86, BIT1, BIT1),   //reg[101e86] #1 = 1b
        //reg_nand_cs2_en
        _RVM1(0x1e16, 0, BIT0),   //reg[101e16]#0 = 0b
        //reg_emmc_config[0]
        _RVM1(0x1ebb, 0, BIT6),   //reg[101ebb]#6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON0_IS_GPIO != GPIO_NONE)
        #define PAD_TCON0_OEN (PAD_TCON0_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON0_OUT (PAD_TCON0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x0a33, PAD_TCON0_OUT, BIT0),
        _RVM1(0x0a33, PAD_TCON0_OEN, BIT1),
        //reg_tconconfig0
        _RVM1(0x1eb9, 0, BIT0),   //reg[101eb9]#0 = 0b
        //reg_ld_spi1cz_tconfig[1:0]
        _RVM1(0x1eb2, 0, BIT7 | BIT6),   //reg[101eb2]#7 ~ #6 = 00b
        //reg_ld_spi1cz_tconfig[1:0]
        _RVM1(0x1eb2, 0, BIT7 | BIT6),   //reg[101eb2]#7 ~ #6 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON1_IS_GPIO != GPIO_NONE)
        #define PAD_TCON1_OEN (PAD_TCON1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON1_OUT (PAD_TCON1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x0a32, PAD_TCON1_OUT, BIT0),
        _RVM1(0x0a32, PAD_TCON1_OEN, BIT1),
        //reg_tconconfig1
        _RVM1(0x1eb9, 0, BIT1),   //reg[101eb9]#1 = 0b
        //reg_ld_spi2_tconfig
        _RVM1(0x1eb3, 0, BIT0),   //reg[101eb3]#0 = 0b
        //reg_ld_spi3_tconfig
        _RVM1(0x1eb3, 0, BIT1),   //reg[101eb3]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON2_IS_GPIO != GPIO_NONE)
        #define PAD_TCON2_OEN (PAD_TCON2_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON2_OUT (PAD_TCON2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x0a35, PAD_TCON2_OUT, BIT0),
        _RVM1(0x0a35, PAD_TCON2_OEN, BIT1),
        //reg_chiptop_dummy_3[2]
        _RVM1(0x1e3e, 0, BIT2),   //reg[101e3e]#2 = 0b
        //reg_tconconfig2
        _RVM1(0x1eb9, 0, BIT2),   //reg[101eb9]#2 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON3_IS_GPIO != GPIO_NONE)
        #define PAD_TCON3_OEN (PAD_TCON3_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON3_OUT (PAD_TCON3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x0a34, PAD_TCON3_OUT, BIT0),
        _RVM1(0x0a34, PAD_TCON3_OEN, BIT1),
        //reg_chiptop_dummy_3[3]
        _RVM1(0x1e3e, 0, BIT3),   //reg[101e3e]#3 = 0b
        //reg_tconconfig3
        _RVM1(0x1eb9, 0, BIT3),   //reg[101eb9]#3 = 0b
        //reg_ld_spi1_tconfig
        _RVM1(0x1eb2, 0, BIT5),   //reg[101eb2]#5 = 0b
        //reg_ld_spi3_tconfig
        _RVM1(0x1eb3, 0, BIT1),   //reg[101eb3]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON4_IS_GPIO != GPIO_NONE)
        #define PAD_TCON4_OEN (PAD_TCON4_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON4_OUT (PAD_TCON4_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x0a37, PAD_TCON4_OUT, BIT0),
        _RVM1(0x0a37, PAD_TCON4_OEN, BIT1),
        //reg_tconconfig4
        _RVM1(0x1eb9, 0, BIT4),   //reg[101eb9]#4 = 0b
        //reg_ld_spi2_tconfig
        _RVM1(0x1eb3, 0, BIT0),   //reg[101eb3]#0 = 0b
        //reg_ld_spi3_tconfig
        _RVM1(0x1eb3, 0, BIT1),   //reg[101eb3]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON5_IS_GPIO != GPIO_NONE)
        #define PAD_TCON5_OEN (PAD_TCON5_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON5_OUT (PAD_TCON5_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x0a36, PAD_TCON5_OUT, BIT0),
        _RVM1(0x0a36, PAD_TCON5_OEN, BIT1),
        //reg_tconconfig5
        _RVM1(0x1eb9, 0, BIT5),   //reg[101eb9]#5 = 0b
        //reg_ld_spi1_tconfig
        _RVM1(0x1eb2, 0, BIT5),   //reg[101eb2]#5 = 0b
        //reg_ld_spi3_tconfig
        _RVM1(0x1eb3, 0, BIT1),   //reg[101eb3]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON6_IS_GPIO != GPIO_NONE)
        #define PAD_TCON6_OEN (PAD_TCON6_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON6_OUT (PAD_TCON6_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x0a39, PAD_TCON6_OUT, BIT0),
        _RVM1(0x0a39, PAD_TCON6_OEN, BIT1),
        //reg_tconconfig6
        _RVM1(0x1eb9, 0, BIT6),   //reg[101eb9]#6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON7_IS_GPIO != GPIO_NONE)
        #define PAD_TCON7_OEN (PAD_TCON7_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON7_OUT (PAD_TCON7_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x0a38, PAD_TCON7_OUT, BIT0),
        _RVM1(0x0a38, PAD_TCON7_OEN, BIT1),
        //reg_tconconfig7
        _RVM1(0x1eb9, 0, BIT7),   //reg[101eb9]#7 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TGPIO0_IS_GPIO != GPIO_NONE)
        #define PAD_TGPIO0_OEN (PAD_TGPIO0_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_TGPIO0_OUT (PAD_TGPIO0_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
        _RVM1(0x1e9c, PAD_TGPIO0_OUT, BIT4),
        _RVM1(0x1e9c, PAD_TGPIO0_OEN, BIT0),
        //reg_vsync_vif_out_en
        _RVM1(0x1ea3, 0, BIT6),   //reg[101ea3]#6 = 0b
        //reg_mcu_jtag_mode[1:0]
        //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6 = 00b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TGPIO1_IS_GPIO != GPIO_NONE)
        #define PAD_TGPIO1_OEN (PAD_TGPIO1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TGPIO1_OUT (PAD_TGPIO1_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
        _RVM1(0x1e9c, PAD_TGPIO1_OUT, BIT5),
        _RVM1(0x1e9c, PAD_TGPIO1_OEN, BIT1),
        //reg_mcu_jtag_mode[1:0]
        //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6 = 00b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TGPIO2_IS_GPIO != GPIO_NONE)
        #define PAD_TGPIO2_OEN (PAD_TGPIO2_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_TGPIO2_OUT (PAD_TGPIO2_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x1e9c, PAD_TGPIO2_OUT, BIT6),
        _RVM1(0x1e9c, PAD_TGPIO2_OEN, BIT2),
        //reg_mcu_jtag_mode[1:0]
        //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6 = 00b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 00b
        //reg_miic_mode1[1:0]
        _RVM1(0x1eb5, 0, BIT3 | BIT2),   //reg[101eb5]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TGPIO3_IS_GPIO != GPIO_NONE)
        #define PAD_TGPIO3_OEN (PAD_TGPIO3_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_TGPIO3_OUT (PAD_TGPIO3_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
        _RVM1(0x1e9c, PAD_TGPIO3_OUT, BIT7),
        _RVM1(0x1e9c, PAD_TGPIO3_OEN, BIT3),
        //reg_mcu_jtag_mode[1:0]
        //_RVM1(0x1e06, 0, BIT7 | BIT6),   //reg[101e06]#7 ~ #6 = 00b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 00b
        //reg_miic_mode1[1:0]
        _RVM1(0x1eb5, 0, BIT3 | BIT2),   //reg[101eb5]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_D0_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_D0_OEN (PAD_TS0_D0_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_TS0_D0_OUT (PAD_TS0_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x1e64, PAD_TS0_D0_OUT, BIT0),
        _RVM1(0x1e68, PAD_TS0_D0_OEN, BIT0),
        //reg_ts0_pe[0]
        _RVM1(0x1e1c, BIT0, BIT0),   //reg[101e1c]#0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_ts0_config[1:0]
        _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2 = 00b
        //reg_ts0_config[1:0]
        _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_D1_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_D1_OEN (PAD_TS0_D1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS0_D1_OUT (PAD_TS0_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x1e64, PAD_TS0_D1_OUT, BIT1),
        _RVM1(0x1e68, PAD_TS0_D1_OEN, BIT1),
        //reg_ts0_pe[1]
        _RVM1(0x1e1c, BIT1, BIT1),   //reg[101e1c]#1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_ts0_config[1:0]
        _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_D2_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_D2_OEN (PAD_TS0_D2_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_TS0_D2_OUT (PAD_TS0_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x1e64, PAD_TS0_D2_OUT, BIT2),
        _RVM1(0x1e68, PAD_TS0_D2_OEN, BIT2),
        //reg_ts0_pe[2]
        _RVM1(0x1e1c, BIT2, BIT2),   //reg[101e1c]#2 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_ts0_config[1:0]
        _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_D3_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_D3_OEN (PAD_TS0_D3_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_TS0_D3_OUT (PAD_TS0_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
        _RVM1(0x1e64, PAD_TS0_D3_OUT, BIT3),
        _RVM1(0x1e68, PAD_TS0_D3_OEN, BIT3),
        //reg_ts0_pe[3]
        _RVM1(0x1e1c, BIT3, BIT3),   //reg[101e1c]#3 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 000b
        //reg_ts0_config[1:0]
        _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_D4_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_D4_OEN (PAD_TS0_D4_IS_GPIO == GPIO_IN ? BIT4: 0)
        #define PAD_TS0_D4_OUT (PAD_TS0_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
        _RVM1(0x1e64, PAD_TS0_D4_OUT, BIT4),
        _RVM1(0x1e68, PAD_TS0_D4_OEN, BIT4),
        //reg_ts0_pe[4]
        _RVM1(0x1e1c, BIT4, BIT4),   //reg[101e1c]#4 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_ts0_config[1:0]
        _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_D5_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_D5_OEN (PAD_TS0_D5_IS_GPIO == GPIO_IN ? BIT5: 0)
        #define PAD_TS0_D5_OUT (PAD_TS0_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
        _RVM1(0x1e64, PAD_TS0_D5_OUT, BIT5),
        _RVM1(0x1e68, PAD_TS0_D5_OEN, BIT5),
        //reg_ts0_pe[5]
        _RVM1(0x1e1c, BIT5, BIT5),   //reg[101e1c]#5 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_ts0_config[1:0]
        _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_D6_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_D6_OEN (PAD_TS0_D6_IS_GPIO == GPIO_IN ? BIT6: 0)
        #define PAD_TS0_D6_OUT (PAD_TS0_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x1e64, PAD_TS0_D6_OUT, BIT6),
        _RVM1(0x1e68, PAD_TS0_D6_OEN, BIT6),
        //reg_ts0_pe[6]
        _RVM1(0x1e1c, BIT6, BIT6),   //reg[101e1c]#6 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_ts0_config[1:0]
        _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_D7_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_D7_OEN (PAD_TS0_D7_IS_GPIO == GPIO_IN ? BIT7: 0)
        #define PAD_TS0_D7_OUT (PAD_TS0_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
        _RVM1(0x1e64, PAD_TS0_D7_OUT, BIT7),
        _RVM1(0x1e68, PAD_TS0_D7_OEN, BIT7),
        //reg_ts0_pe[7]
        _RVM1(0x1e1c, BIT7, BIT7),   //reg[101e1c]#7 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_ts0_config[1:0]
        _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_VLD_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_VLD_OEN (PAD_TS0_VLD_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_TS0_VLD_OUT (PAD_TS0_VLD_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x1e65, PAD_TS0_VLD_OUT, BIT0),
        _RVM1(0x1e69, PAD_TS0_VLD_OEN, BIT0),
        //reg_ts0_pe[8]
        _RVM1(0x1e1d, BIT0, BIT0),   //reg[101e1d]#0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_ts0_config[1:0]
        _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2 = 00b
        //reg_ts0_config[1:0]
        _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_SYNC_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_SYNC_OEN (PAD_TS0_SYNC_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS0_SYNC_OUT (PAD_TS0_SYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x1e65, PAD_TS0_SYNC_OUT, BIT1),
        _RVM1(0x1e69, PAD_TS0_SYNC_OEN, BIT1),
        //reg_ts0_pe[9]
        _RVM1(0x1e1d, BIT1, BIT1),   //reg[101e1d]#1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_ts0_config[1:0]
        _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2 = 00b
        //reg_ts0_config[1:0]
        _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_CLK_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_CLK_OEN (PAD_TS0_CLK_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_TS0_CLK_OUT (PAD_TS0_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x1e65, PAD_TS0_CLK_OUT, BIT2),
        _RVM1(0x1e69, PAD_TS0_CLK_OEN, BIT2),
        //reg_ts0_pe[10]
        _RVM1(0x1e1d, BIT2, BIT2),   //reg[101e1d]#2 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_ts0_config[1:0]
        _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2 = 00b
        //reg_ts0_config[1:0]
        _RVM1(0x1ea3, 0, BIT3 | BIT2),   //reg[101ea3]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_CLK_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_CLK_OEN (PAD_TS1_CLK_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_TS1_CLK_OUT (PAD_TS1_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x1e4c, PAD_TS1_CLK_OUT, BIT0),
        _RVM1(0x1e4e, PAD_TS1_CLK_OEN, BIT0),
        //reg_ts1_pe[10]
        _RVM1(0x1e1f, BIT2, BIT2),   //reg[101e1f]#2 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_miic_mode0[1:0]
        _RVM1(0x1eb5, 0, BIT1 | BIT0),   //reg[101eb5]#1 ~ #0 = 00b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_SYNC_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_SYNC_OEN (PAD_TS1_SYNC_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS1_SYNC_OUT (PAD_TS1_SYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x1e4c, PAD_TS1_SYNC_OUT, BIT1),
        _RVM1(0x1e4e, PAD_TS1_SYNC_OEN, BIT1),
        //reg_ts1_pe[9]
        _RVM1(0x1e1f, BIT1, BIT1),   //reg[101e1f]#1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_miic_mode0[1:0]
        _RVM1(0x1eb5, 0, BIT1 | BIT0),   //reg[101eb5]#1 ~ #0 = 00b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_VLD_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_VLD_OEN (PAD_TS1_VLD_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_TS1_VLD_OUT (PAD_TS1_VLD_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x1e4c, PAD_TS1_VLD_OUT, BIT2),
        _RVM1(0x1e4e, PAD_TS1_VLD_OEN, BIT2),
        //reg_ts1_pe[8]
        _RVM1(0x1e1f, BIT0, BIT0),   //reg[101e1f]#0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_miic_mode1[1:0]
        _RVM1(0x1eb5, 0, BIT3 | BIT2),   //reg[101eb5]#3 ~ #2 = 00b
        //reg_miic_mode2[1:0]
        _RVM1(0x1eb5, 0, BIT5 | BIT4),   //reg[101eb5]#5 ~ #4 = 00b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_D7_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_D7_OEN (PAD_TS1_D7_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_TS1_D7_OUT (PAD_TS1_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
        _RVM1(0x1e4c, PAD_TS1_D7_OUT, BIT3),
        _RVM1(0x1e4e, PAD_TS1_D7_OEN, BIT3),
        //reg_ts1_pe[7]
        _RVM1(0x1e1e, BIT7, BIT7),   //reg[101e1e]#7 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 00b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_D6_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_D6_OEN (PAD_TS1_D6_IS_GPIO == GPIO_IN ? BIT4: 0)
        #define PAD_TS1_D6_OUT (PAD_TS1_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
        _RVM1(0x1e4c, PAD_TS1_D6_OUT, BIT4),
        _RVM1(0x1e4e, PAD_TS1_D6_OEN, BIT4),
        //reg_ts1_pe[6]
        _RVM1(0x1e1e, BIT6, BIT6),   //reg[101e1e]#6 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 00b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_sm_config[1:0]
        _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2 = 00b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_D5_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_D5_OEN (PAD_TS1_D5_IS_GPIO == GPIO_IN ? BIT5: 0)
        #define PAD_TS1_D5_OUT (PAD_TS1_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
        _RVM1(0x1e4c, PAD_TS1_D5_OUT, BIT5),
        _RVM1(0x1e4e, PAD_TS1_D5_OEN, BIT5),
        //reg_ts1_pe[5]
        _RVM1(0x1e1e, BIT5, BIT5),   //reg[101e1e]#5 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 00b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_sm_config[1:0]
        _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2 = 00b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_D4_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_D4_OEN (PAD_TS1_D4_IS_GPIO == GPIO_IN ? BIT6: 0)
        #define PAD_TS1_D4_OUT (PAD_TS1_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x1e4c, PAD_TS1_D4_OUT, BIT6),
        _RVM1(0x1e4e, PAD_TS1_D4_OEN, BIT6),
        //reg_ts1_pe[4]
        _RVM1(0x1e1e, BIT4, BIT4),   //reg[101e1e]#4 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 00b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_sm_config[1:0]
        _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_D3_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_D3_OEN (PAD_TS1_D3_IS_GPIO == GPIO_IN ? BIT7: 0)
        #define PAD_TS1_D3_OUT (PAD_TS1_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
        _RVM1(0x1e4c, PAD_TS1_D3_OUT, BIT7),
        _RVM1(0x1e4e, PAD_TS1_D3_OEN, BIT7),
        //reg_ts1_pe[3]
        _RVM1(0x1e1e, BIT3, BIT3),   //reg[101e1e]#3 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_sm_config[1:0]
        _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_D2_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_D2_OEN (PAD_TS1_D2_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_TS1_D2_OUT (PAD_TS1_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x1e4d, PAD_TS1_D2_OUT, BIT0),
        _RVM1(0x1e4f, PAD_TS1_D2_OEN, BIT0),
        //reg_ts1_pe[2]
        _RVM1(0x1e1e, BIT2, BIT2),   //reg[101e1e]#2 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_sm_config[1:0]
        _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_D1_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_D1_OEN (PAD_TS1_D1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS1_D1_OUT (PAD_TS1_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x1e4d, PAD_TS1_D1_OUT, BIT1),
        _RVM1(0x1e4f, PAD_TS1_D1_OEN, BIT1),
        //reg_ts1_pe[1]
        _RVM1(0x1e1e, BIT1, BIT1),   //reg[101e1e]#1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_sm_config[1:0]
        _RVM1(0x1e17, 0, BIT3 | BIT2),   //reg[101e17]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_D0_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_D0_OEN (PAD_TS1_D0_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_TS1_D0_OUT (PAD_TS1_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x1e4d, PAD_TS1_D0_OUT, BIT2),
        _RVM1(0x1e4f, PAD_TS1_D0_OEN, BIT2),
        //reg_ts1_pe[0]
        _RVM1(0x1e1e, BIT0, BIT0),   //reg[101e1e]#0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 000b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts1_config[1:0]
        _RVM1(0x1ea3, 0, BIT5 | BIT4),   //reg[101ea3]#5 ~ #4 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_ts_out_mode[1:0]
        _RVM1(0x1ea3, 0, BIT1 | BIT0),   //reg[101ea3]#1 ~ #0 = 00b
        //reg_bt656_ctrl[1:0]
        _RVM1(0x1edf, 0, BIT7 | BIT6),   //reg[101edf]#7 ~ #6 = 00b
        //reg_miic_mode1[1:0]
        _RVM1(0x1eb5, 0, BIT3 | BIT2),   //reg[101eb5]#3 ~ #2 = 00b
        //reg_miic_mode2[1:0]
        _RVM1(0x1eb5, 0, BIT5 | BIT4),   //reg[101eb5]#5 ~ #4 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_UART_TX2_IS_GPIO != GPIO_NONE)
        #define PAD_UART_TX2_OEN (PAD_UART_TX2_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_UART_TX2_OUT (PAD_UART_TX2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x0a00, PAD_UART_TX2_OUT, BIT0),
        _RVM1(0x0a02, PAD_UART_TX2_OEN, BIT0),
        //reg_thirduartmode[1:0]
        _RVM1(0x1e05, 0, BIT3 | BIT2),   //reg[101e05]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_UART_RX2_IS_GPIO != GPIO_NONE)
        #define PAD_UART_RX2_OEN (PAD_UART_RX2_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_UART_RX2_OUT (PAD_UART_RX2_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x0a00, PAD_UART_RX2_OUT, BIT1),
        _RVM1(0x0a02, PAD_UART_RX2_OEN, BIT1),
        //reg_thirduartmode[1:0]
        _RVM1(0x1e05, 0, BIT3 | BIT2),   //reg[101e05]#3 ~ #2 = 00b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

//---------------------------------------------------------------------
// Pad Configuartion
//---------------------------------------------------------------------

//=============================================================================
#ifdef PADS_VSYNC_VIF_OUT_EN
    #if (PADS_VSYNC_VIF_OUT_EN != UNKNOWN_PAD_MUX)
    #define _CONFIG_VSYNC_VIF_OUT_EN    ((PADS_VSYNC_VIF_OUT_EN == ENABLE) ? BIT6 : 0)
        _RVM1(0x1ea3, _CONFIG_VSYNC_VIF_OUT_EN, BIT6),
    #endif
#endif

//=============================================================================
#ifdef PADS_TS0_CONFIG
    #if (PADS_TS0_CONFIG != UNKNOWN_PAD_MUX)
    #define _CONFIG_TS0_CONFIG  ((PADS_TS0_CONFIG == PARALLEL_IN) ? BIT2 : \
                                 (PADS_TS0_CONFIG == SERIAL_IN) ? BIT3 : 0)
        _RVM1(0x1ea3, _CONFIG_TS0_CONFIG, (BIT3 | BIT2)),
    #endif
#endif

#ifdef PADS_TS1_CONFIG
    #if (PADS_TS1_CONFIG != UNKNOWN_PAD_MUX)
    #define _CONFIG_TS1_CONFIG  ((PADS_TS1_CONFIG == PARALLEL_IN) ? BIT4 : \
                                 (PADS_TS1_CONFIG == PARALLEL_OUT) ? BIT5 : \
                                 (PADS_TS1_CONFIG == SERIAL_IN) ? (BIT5 | BIT4) : 0)
        _RVM1(0x1ea3, _CONFIG_TS1_CONFIG, (BIT5 | BIT4)),
    #endif
#endif

#ifdef PADS_TS_OUT
    #if (PADS_TS_OUT != UNKNOWN_PAD_MUX)
    #define _CONFIG_TS_OUT_MODE ((PADS_TS_OUT == ENABLE) ? BIT0 : 0)
        _RVM1(0x1ea3, _CONFIG_TS_OUT_MODE, (BIT1 | BIT0)),
    #endif
#endif

#ifdef PADS_TSERR_OUT
    #if (PADS_TSERR_OUT != UNKNOWN_PAD_MUX)
    #define _CONFIG_TSERR_OUT   ((PADS_TSERR_OUT == PAD_I2S_IN_SD) ? BIT6 :  \
                                 (PADS_TSERR_OUT == PAD_GPIO16) ? BIT7 :  \
                                 (PADS_TSERR_OUT == PAD_PWM4) ? (BIT7 | BIT6) : 0)
        _RVM2(0x1ea2, _CONFIG_TSERR_OUT, (BIT7 | BIT6)),
    #endif
#endif

#ifdef PADS_TS0_PE
    #if (PADS_TS0_PE == ENABLE)
        _RVM1(0x1e1c, BITMASK(7:0), BITMASK(7:0)),
        _RVM1(0x1e1d, BITMASK(2:0), BITMASK(2:0)),
    #else
        _RVM1(0x1e1c, 0, BITMASK(7:0)),
        _RVM1(0x1e1d, 0, BITMASK(2:0)),
    #endif
#endif

#ifdef PADS_TS1_PE
    #if (PADS_TS1_PE == ENABLE)
        _RVM1(0x1e1e, BITMASK(7:0), BITMASK(7:0)),
        _RVM1(0x1e1f, BITMASK(2:0), BITMASK(2:0)),
    #else
        _RVM1(0x1e1e, 0, BITMASK(7:0)),
        _RVM1(0x1e1f, 0, BITMASK(2:0)),
    #endif
#endif

//=============================================================================
#ifdef PADS_NAND_MODE
    #if (PADS_NAND_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_NAND_MODE   ((PADS_NAND_MODE == PAD_PCM_A) ? BIT4 : 0)
        _RVM1(0x1e17, _CONFIG_NAND_MODE, (BIT6 | BIT5 | BIT4)),

    #if (PADS_NAND_MODE == PAD_PCM_A)
        _RVM2(0x1e18, BITMASK(7:0), BITMASK(7:0)),
    #endif

    #else
        _RVM1(0x1e17, 0, (BIT6 | BIT5 | BIT4)),
    #endif
#endif

#ifdef PADS_NAND_CS1_EN
    #if (PADS_NAND_CS1_EN != UNKNOWN_PAD_MUX)
    #define _CONFIG_NAND_CS1_EN ((PADS_NAND_CS1_EN == ENABLE) ? BIT2 : 0)
        _RVM1(0x1ea1, _CONFIG_NAND_CS1_EN, BIT2),
    #endif
#endif

#ifdef PADS_NAND_CS2_EN
    #if (PADS_NAND_CS2_EN != UNKNOWN_PAD_MUX)
    #define _CONFIG_NAND_CS2_EN ((PADS_NAND_CS2_EN == ENABLE) ? BIT0 : 0)
        _RVM1(0x1e16, _CONFIG_NAND_CS2_EN, BIT0),
    #endif
#endif

#ifdef PADS_NAND_CS3_EN
    #if (PADS_NAND_CS3_EN != UNKNOWN_PAD_MUX)
    #define _CONFIG_NAND_CS3_EN ((PADS_NAND_CS3_EN == ENABLE) ? BIT1 : 0)
        _RVM1(0x1e16, _CONFIG_NAND_CS3_EN, BIT1),
    #endif
#endif

#ifdef PADS_NAND_PE
    #if (PADS_NAND_PE == ENABLE)
        _RVM1(0x1ed6, BITMASK(7:0), BITMASK(7:0)),
        _RVM1(0x1ed7, BIT0, BIT0),
    #else
        _RVM1(0x1ed6, 0, BITMASK(7:0)),
        _RVM1(0x1ed7, 0, BIT0),
    #endif
#endif

//=============================================================================
#ifdef PADS_EMMC_MODE
    #if (PADS_EMMC_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_EMMC_MODE   ((PADS_EMMC_MODE == PAD_NAND_CTRL) ? BIT6 : 0)
        _RVM1(0x1ebb, _CONFIG_EMMC_MODE, (BIT7 | BIT6)),
    #else
        _RVM1(0x1ebb, 0, (BIT7 | BIT6)),
    #endif
#endif

#ifdef PADS_SD_MODE
    #if (PADS_SD_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_SD_MODE     ((PADS_SD_MODE == CONFIG_SD_MODE0) ? BIT0: \
                                 (PADS_SD_MODE == CONFIG_SD_MODE1) ? BIT1: 0)
        _RVM1(0x1eb7, _CONFIG_SD_MODE, (BIT1 | BIT0)),
    #endif
#endif

#ifdef PADS_SDIO_MODE
    #if (PADS_SDIO_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_SDIO_MODE   ((PADS_SDIO_MODE == CONFIG_SDIO_MODE0) ? BIT2: \
                                 (PADS_SDIO_MODE == CONFIG_SDIO_MODE1) ? BIT3: \
                                 (PADS_SDIO_MODE == CONFIG_SDIO_MODE2) ? (BIT3 | BIT2) : 0)
        _RVM1(0x1eb7, _CONFIG_SDIO_MODE, (BIT3 | BIT2)),
    #endif
#endif

//=============================================================================
#ifdef PADS_PCM1_CTRL
    #if (PADS_PCM1_CTRL != UNKNOWN_PAD_MUX)
    #define _CONFIG_PCM1_CTRL   ((PADS_PCM1_CTRL == PAD_PCM_CE_N) ? BIT7 : 0)
        _RVM1(0x1e9f, _CONFIG_PCM1_CTRL, BIT7),
    #endif
#endif

#ifdef PADS_PCM1_AD
    #if (PADS_PCM1_AD != UNKNOWN_PAD_MUX)
    #define _CONFIG_PCM1_AD     ((PADS_PCM1_AD == PAD_PCM_D7) ? BIT6 : 0)
        _RVM1(0x1e9f, _CONFIG_PCM1_AD, BIT6),
    #endif
#endif

#ifdef PADS_PCM1_PE
    #if (PADS_PCM1_PE != UNKNOWN_PAD_MUX)
    #if (PADS_PCM1_PE == ENABLE)
        _RVM1(0x1e82, BITMASK(7:0), BITMASK(7:0)),
        _RVM1(0x1e83, BITMASK(7:0), BITMASK(7:0)),
        _RVM1(0x1e84, BITMASK(7:0), BITMASK(7:0)),
        _RVM1(0x1e85, BITMASK(1:0), BITMASK(1:0)),
    #else
        _RVM1(0x1e82, 0, BITMASK(7:0)),
        _RVM1(0x1e83, 0, BITMASK(7:0)),
        _RVM1(0x1e84, 0, BITMASK(7:0)),
        _RVM1(0x1e85, 0, BITMASK(1:0)),
    #endif
    #endif
#endif

#ifdef PADS_PCM2_CTRL
    #if (PADS_PCM2_CTRL != UNKNOWN_PAD_MUX)
    #define _CONFIG_PCM2_CTRL   ((PADS_PCM2_CTRL == PAD_PCM2_CD_N) ? BIT5 : 0)
        _RVM1(0x1e9f, _CONFIG_PCM2_CTRL, BIT5),
    #endif
#endif

#ifdef PADS_CI_CTRL
    #if (PADS_CI_CTRL != UNKNOWN_PAD_MUX)
    #define _CONFIG_CI_CTRL     ((PADS_CI_CTRL == ENABLE) ? BIT1 : 0)
        _RVM1(0x1ec8, _CONFIG_CI_CTRL, BIT1),
    #endif
#endif

#ifdef PADS_CI_AD
    #if (PADS_CI_AD != UNKNOWN_PAD_MUX)
    #define _CONFIG_CI_AD   ((PADS_CI_AD == ENABLE) ? BIT0 : 0)
        _RVM1(0x1ec8, _CONFIG_CI_AD, BIT0),
    #endif
#endif

//=============================================================================
#ifdef PADS_I2S_IN
    #if (PADS_I2S_IN != UNKNOWN_PAD_MUX)
    #define _CONFIG_I2S_IN  ((PADS_I2S_IN == ENABLE) ? BIT2 : 0)
        _RVM1(0x1eae, _CONFIG_I2S_IN, BIT2),
    #endif
#endif

#ifdef PADS_I2S_OUT
    #if (PADS_I2S_OUT != UNKNOWN_PAD_MUX)
    #define _CONFIG_I2S_OUT ((PADS_I2S_OUT == PAD_I2S_OUT_SD) ? BIT3: \
                             (PADS_I2S_OUT == PAD_I2S_OUT_SD1) ? BIT4: \
                             (PADS_I2S_OUT == PAD_I2S_OUT_SD2) ? BIT5: \
                             (PADS_I2S_OUT == PAD_I2S_OUT_SD3) ? BIT6: 0)
        _RVM1(0x1e05, 0, (BIT5 | BIT4)), //Disable JTAG pad configuration
        _RVM1(0x1edb, (BIT2 | BIT1 | BIT0), (BIT2 | BIT1 | BIT0)),
        _RVM1(0x1edb, _CONFIG_I2S_OUT, BITMASK(6:3)),
    #endif
#endif

#ifdef PADS_I2S_MUTE
    #if (PADS_I2S_MUTE != UNKNOWN_PAD_MUX)
    #define _CONFIG_I2S_MUTE    ((PADS_I2S_MUTE == PAD_GPIO15) ? BIT6: \
                                 (PADS_I2S_MUTE == PAD_PWM4) ? BIT7 : 0)
        _RVM1(0x1e05, _CONFIG_I2S_MUTE, (BIT7 | BIT6)),
    #endif
#endif

#ifdef PADS_SPDIF_IN
    #if (PADS_SPDIF_IN != UNKNOWN_PAD_MUX)
    #define _CONFIG_SPDIF_IN    ((PADS_SPDIF_IN == ENABLE) ? BIT6 : 0)
        _RVM1(0x1eae, _CONFIG_SPDIF_IN, BIT6),
    #endif
#endif

#ifdef PADS_SPDIF_OUT
    #if (PADS_SPDIF_OUT != UNKNOWN_PAD_MUX)
    #define _CONFIG_SPDIF_OUT   ((PADS_SPDIF_OUT == ENABLE) ? BIT7 : 0)
        _RVM1(0x1eae, _CONFIG_SPDIF_OUT, BIT7),
    #endif
#endif

//=============================================================================
#ifdef PADS_ET_MODE
    #if (PADS_ET_MODE != UNKNOWN_PAD_MUX)           //for External Ethernet PHY
    #define _CONFIG_ET_MODE     ((PADS_ET_MODE == ENABLE) ? BIT0 : 0)
        _RVM1(0x1edf, _CONFIG_ET_MODE, BIT0),
    #endif
#endif

//=============================================================================
#ifdef PADS_3D_FLAG_CONFIG
    #if (PADS_3D_FLAG_CONFIG != UNKNOWN_PAD_MUX)
    #define _CONFIG_3D_FLAG_CONFIG  ((PADS_3D_FLAG_CONFIG == PAD_SPDIF_IN) ? BIT6 : \
                                     (PADS_3D_FLAG_CONFIG == PAD_GPIO16) ? BIT7 : \
                                     (PADS_3D_FLAG_CONFIG == PAD_I2S_IN_SD) ? (BIT7 | BIT6) : 0)
        _RVM1(0x1eb1, _CONFIG_3D_FLAG_CONFIG, (BIT7 | BIT6)),
    #endif
#endif

//=============================================================================
#ifdef PADS_LED_MODE
    #if (PADS_LED_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_LED_MODE    ((PADS_LED_MODE == PAD_GPIO19) ? BIT4 : \
                                 (PADS_LED_MODE == PAD_GPIO20) ? BIT4 : \
                                 (PADS_LED_MODE == PAD_GPIO26) ? BIT5 : \
                                 (PADS_LED_MODE == PAD_GPIO27) ? BIT5 : 0)
        _RVM1(0x1eb4, _CONFIG_LED_MODE, (BIT5 | BIT4)),
    #endif
#endif

//=============================================================================
#ifdef PADS_UART2_MODE
    #if (PADS_UART2_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_UART2_MODE  ((PADS_UART2_MODE == PAD_GPIO7) ? BIT0 : \
                                 (PADS_UART2_MODE == PAD_GPIO8) ? BIT0 : \
                                 (PADS_UART2_MODE == PAD_GPIO19) ? BIT1 : \
                                 (PADS_UART2_MODE == PAD_GPIO20) ? BIT1 : \
                                 (PADS_UART2_MODE == PAD_GPIO3) ? (BIT1 | BIT0) : \
                                 (PADS_UART2_MODE == PAD_GPIO4) ? (BIT1 | BIT0) : 0 )
        _RVM1(0x1e05, _CONFIG_UART2_MODE, (BIT1 | BIT0)),
    #endif
#endif

#ifdef PADS_UART3_MODE
    #if (PADS_UART3_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_UART3_MODE  ((PADS_UART3_MODE == PAD_GPIO9) ? BIT2 : \
                                 (PADS_UART3_MODE == PAD_GPIO10) ? BIT2 : \
                                 (PADS_UART3_MODE == PAD_I2S_IN_WS) ? BIT3 : \
                                 (PADS_UART3_MODE == PAD_I2S_IN_BCK) ? BIT3 : \
                                 (PADS_UART3_MODE == PAD_UART_TX2) ? (BIT3 | BIT2) : \
                                 (PADS_UART3_MODE == PAD_UART_RX2) ? (BIT3 | BIT2) : 0 )
        _RVM1(0x1e05, _CONFIG_UART3_MODE, (BIT3 | BIT2)),
    #endif
#endif

#ifdef PADS_UART4_MODE
    #if (PADS_UART4_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_UART4_MODE  ((PADS_UART4_MODE == PAD_GPIO11) ? BIT6 : \
                                 (PADS_UART4_MODE == PAD_GPIO12) ? BIT6 : \
                                 (PADS_UART4_MODE == PAD_GPIO23) ? BIT7 : \
                                 (PADS_UART4_MODE == PAD_GPIO24) ? BIT7 : \
                                 (PADS_UART4_MODE == PAD_I2S_OUT_SD2) ? (BIT7 | BIT6) : \
                                 (PADS_UART4_MODE == PAD_I2S_OUT_SD3) ? (BIT7 | BIT6) : 0 )
        _RVM1(0x1e04, _CONFIG_UART4_MODE, (BIT7 | BIT6)),
    #endif
#endif

#ifdef PADS_FAST_UART_MODE
    #if (PADS_FAST_UART_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_FAST_UART_MODE  ((PADS_FAST_UART_MODE == PAD_GPIO19) ? BIT4 : \
                                     (PADS_FAST_UART_MODE == PAD_GPIO20) ? BIT4 : \
                                     (PADS_FAST_UART_MODE == PAD_GPIO3) ? BIT5 : \
                                     (PADS_FAST_UART_MODE == PAD_GPIO4) ? BIT5 : \
                                     (PADS_FAST_UART_MODE == PAD_GPIO13) ? (BIT5 | BIT4) : \
                                     (PADS_FAST_UART_MODE == PAD_GPIO14) ? (BIT5 | BIT4) : 0 )
        _RVM1(0x1e04, _CONFIG_FAST_UART_MODE, (BIT5 | BIT4)),
    #endif
#endif

#ifdef PADS_OD_UART2_MODE
    #if (PADS_OD_UART2_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_OD_UART2_MODE   ((PADS_OD_UART2_MODE == PAD_GPIO7) ? BIT0 : \
                                     (PADS_OD_UART2_MODE == PAD_GPIO8) ? BIT0 : \
                                     (PADS_OD_UART2_MODE == PAD_GPIO19) ? BIT1 : \
                                     (PADS_OD_UART2_MODE == PAD_GPIO20) ? BIT1 : \
                                     (PADS_OD_UART2_MODE == PAD_GPIO3) ? (BIT1 | BIT0) : \
                                     (PADS_OD_UART2_MODE == PAD_GPIO4) ? (BIT1 | BIT0) : 0 )
        _RVM1(0x1eb6, _CONFIG_OD_UART2_MODE, (BIT1 | BIT0)),
    #endif
#endif

#ifdef PADS_OD_UART3_MODE
    #if (PADS_OD_UART3_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_OD_UART3_MODE   ((PADS_OD_UART3_MODE == PAD_GPIO9) ? BIT2 : \
                                     (PADS_OD_UART3_MODE == PAD_GPIO10) ? BIT2 : \
                                     (PADS_OD_UART3_MODE == PAD_I2S_IN_WS) ? BIT3 : \
                                     (PADS_OD_UART3_MODE == PAD_I2S_IN_BCK) ? BIT3 : \
                                     (PADS_OD_UART3_MODE == PAD_GPIO21) ? (BIT3 | BIT2) : \
                                     (PADS_OD_UART3_MODE == PAD_GPIO22) ? (BIT3 | BIT2) : 0 )
        _RVM1(0x1eb6, _CONFIG_OD_UART3_MODE, (BIT3 | BIT2)),
    #endif
#endif

#ifdef PADS_OD_UART4_MODE
    #if (PADS_OD_UART4_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_OD_UART4_MODE   ((PADS_OD_UART4_MODE == PAD_GPIO11) ? BIT4 : \
                                     (PADS_OD_UART4_MODE == PAD_GPIO12) ? BIT4 : \
                                     (PADS_OD_UART4_MODE == PAD_GPIO23) ? BIT5 : \
                                     (PADS_OD_UART4_MODE == PAD_GPIO24) ? BIT5 : \
                                     (PADS_OD_UART4_MODE == PAD_I2S_OUT_SD2) ? (BIT5 | BIT4) : \
                                     (PADS_OD_UART4_MODE == PAD_I2S_OUT_SD3) ? (BIT5 | BIT4) : 0 )
        _RVM1(0x1eb6, _CONFIG_OD_UART4_MODE, (BIT5 | BIT4)),
    #endif
#endif

#ifdef PADS_OD_FAST_UART_MODE
    #if (PADS_OD_FAST_UART_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_OD_FAST_UART_MODE   ((PADS_OD_FAST_UART_MODE == PAD_GPIO19) ? BIT6 : \
                                         (PADS_OD_FAST_UART_MODE == PAD_GPIO20) ? BIT6 : \
                                         (PADS_OD_FAST_UART_MODE == PAD_GPIO3) ? BIT7 : \
                                         (PADS_OD_FAST_UART_MODE == PAD_GPIO4) ? BIT7 : \
                                         (PADS_OD_FAST_UART_MODE == PAD_GPIO13) ? (BIT7 | BIT6) : \
                                         (PADS_OD_FAST_UART_MODE == PAD_GPIO14) ? (BIT7 | BIT6) : 0 )
        _RVM1(0x1eb6, _CONFIG_OD_FAST_UART_MODE, (BIT7 | BIT6)),
    #endif
#endif

#ifdef PADS_UART0_INV_MODE
#define _CONFIG_ENABLE_UART0_INV_MODE   ((PADS_UART0_INV_MODE == ENABLE) ? BIT0 : 0)
    _RVM1(0x1eab, _CONFIG_ENABLE_UART0_INV_MODE, BIT0),
#endif

#ifdef PADS_UART1_INV_MODE
#define _CONFIG_ENABLE_UART1_INV_MODE   ((PADS_UART1_INV_MODE == ENABLE) ? BIT1 : 0)
    _RVM1(0x1eab, _CONFIG_ENABLE_UART1_INV_MODE, BIT1),
#endif

#ifdef PADS_UART2_INV_MODE
#define _CONFIG_ENABLE_UART2_INV_MODE   ((PADS_UART2_INV_MODE == ENABLE) ? BIT2 : 0)
    _RVM1(0x1eab, _CONFIG_ENABLE_UART2_INV_MODE, BIT2),
#endif

#ifdef PADS_UART3_INV_MODE
#define _CONFIG_ENABLE_UART3_INV_MODE   ((PADS_UART3_INV_MODE == ENABLE) ? BIT3 : 0)
    _RVM1(0x1eab, _CONFIG_ENABLE_UART3_INV_MODE, BIT3),
#endif

#ifdef PADS_FAST_UART_INV_MODE
#define _CONFIG_ENABLE_FAST_UART_INV_MODE   ((PADS_FAST_UART_INV_MODE == ENABLE) ? BIT3 : 0)
    _RVM1(0x1eab, _CONFIG_ENABLE_FAST_UART_INV_MODE, BIT3),
#endif

    _RVM1(0x1ea6, ((UART1_SRC_SEL << 4) | UART0_SRC_SEL), BITMASK(7:0)),
    _RVM1(0x1ea7, ((UART3_SRC_SEL << 4) | UART2_SRC_SEL), BITMASK(7:0)),
    _RVM1(0x1ea8, UART4_SRC_SEL, BITMASK(3:0)),

#if ((UART0_SRC_SEL == UART1_SRC_SEL) || \
     (UART0_SRC_SEL == UART2_SRC_SEL) || \
     (UART0_SRC_SEL == UART3_SRC_SEL) || \
     (UART0_SRC_SEL == UART4_SRC_SEL) || \
     (UART1_SRC_SEL == UART0_SRC_SEL) || \
     (UART1_SRC_SEL == UART2_SRC_SEL) || \
     (UART1_SRC_SEL == UART3_SRC_SEL) || \
     (UART1_SRC_SEL == UART4_SRC_SEL) || \
     (UART2_SRC_SEL == UART0_SRC_SEL) || \
     (UART2_SRC_SEL == UART1_SRC_SEL) || \
     (UART2_SRC_SEL == UART3_SRC_SEL) || \
     (UART2_SRC_SEL == UART4_SRC_SEL) || \
     (UART3_SRC_SEL == UART0_SRC_SEL) || \
     (UART3_SRC_SEL == UART1_SRC_SEL) || \
     (UART3_SRC_SEL == UART2_SRC_SEL) || \
     (UART3_SRC_SEL == UART4_SRC_SEL) || \
     (UART4_SRC_SEL == UART0_SRC_SEL) || \
     (UART4_SRC_SEL == UART1_SRC_SEL) || \
     (UART4_SRC_SEL == UART2_SRC_SEL) || \
     (UART4_SRC_SEL == UART3_SRC_SEL))
    #error "[ERROR] UART Source Selection Conflict"
#endif

    _MEMMAP_PM_,
    _RVM1(0x0e13, 0, BIT4),         //Select UART Source to reg_uart_sel0
    _RVM1(0x0e13, BIT3, BIT3),      //Enable UART Rx
    _MEMMAP_nonPM_,

//=============================================================================
#ifdef PADS_PWM0_MODE
    #if (PADS_PWM0_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_PWM0_MODE   ((PADS_PWM0_MODE == ENABLE) ? BIT0:  0)
        _RVM1(0x1ea2, _CONFIG_PWM0_MODE, BIT0),
    #endif
#endif

#ifdef PADS_PWM1_MODE
    #if (PADS_PWM1_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_PWM1_MODE   ((PADS_PWM1_MODE == ENABLE) ? BIT1:  0)
        _RVM1(0x1ea2, _CONFIG_PWM1_MODE, BIT1),
    #endif
#endif

#ifdef PADS_PWM2_MODE
    #if (PADS_PWM2_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_PWM2_MODE   ((PADS_PWM2_MODE == ENABLE) ? BIT2:  0)
        _RVM1(0x1ea2, _CONFIG_PWM2_MODE, BIT2),
    #endif
#endif

#ifdef PADS_PWM3_MODE
    #if (PADS_PWM3_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_PWM3_MODE   ((PADS_PWM3_MODE == ENABLE) ? BIT3:  0)
        _RVM1(0x1ea2, _CONFIG_PWM3_MODE, BIT3),
    #endif
#endif

#ifdef PADS_PWM4_MODE
    #if (PADS_PWM4_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_PWM4_MODE   ((PADS_PWM4_MODE == PAD_SPI1_DI) ? BIT4 : \
                                 (PADS_PWM4_MODE == PAD_SPI2_DI) ? BIT5 : \
                                 (PADS_PWM4_MODE == PAD_PWM4) ? (BIT5 | BIT4) : 0 )
        _RVM1(0x1ea2, _CONFIG_PWM4_MODE, (BIT5 | BIT4)),
    #endif
#endif

#ifdef PADS_PWM5_MODE
    #if (PADS_PWM5_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_PWM5_MODE   ((PADS_PWM5_MODE == PAD_SPI2_CK) ? BIT0 : \
                                 (PADS_PWM5_MODE == PAD_SPI1_CK) ? BIT1 : \
                                 (PADS_PWM5_MODE == PAD_VSYNC_LIKE) ? (BIT1 | BIT0) : 0 )
        _RVM1(0x1eb2, _CONFIG_PWM5_MODE, (BIT1 | BIT0)),
    #endif
#endif

#ifdef PADS_PWM0_DIM_MODE
    #if (PADS_PWM0_DIM_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_PWM0_DIM_MODE   ((PADS_PWM0_DIM_MODE == ENABLE) ? BIT0:  0)
        _RVM1(0x1eef, _CONFIG_PWM0_DIM_MODE, BIT0),
    #endif
#endif

#ifdef PADS_PWM1_DIM_MODE
    #if (PADS_PWM1_DIM_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_PWM1_DIM_MODE   ((PADS_PWM1_DIM_MODE == ENABLE) ? BIT1:  0)
        _RVM1(0x1eef, _CONFIG_PWM1_DIM_MODE, BIT1),
    #endif
#endif

#ifdef PADS_PWM2_DIM_MODE
    #if (PADS_PWM2_DIM_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_PWM2_DIM_MODE   ((PADS_PWM2_DIM_MODE == ENABLE) ? BIT2:  0)
        _RVM1(0x1eef, _CONFIG_PWM2_DIM_MODE, BIT2),
    #endif
#endif

#ifdef PADS_PWM3_DIM_MODE
    #if (PADS_PWM3_DIM_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_PWM3_DIM_MODE   ((PADS_PWM3_DIM_MODE == ENABLE) ? BIT3:  0)
        _RVM1(0x1eef, _CONFIG_PWM3_DIM_MODE, BIT3),
    #endif
#endif

#ifdef PADS_PWM4_DIM_MODE
    #if (PADS_PWM4_DIM_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_PWM4_DIM_MODE   ((PADS_PWM4_DIM_MODE == ENABLE) ? BIT4:  0)
        _RVM1(0x1eef, _CONFIG_PWM4_DIM_MODE, BIT4),
    #endif
#endif

#ifdef PADS_PWM5_DIM_MODE
    #if (PADS_PWM5_DIM_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_PWM5_DIM_MODE   ((PADS_PWM5_DIM_MODE == ENABLE) ? BIT5:  0)
        _RVM1(0x1eef, _CONFIG_PWM5_DIM_MODE, BIT5),
    #endif
#endif

//=============================================================================
#ifdef PADS_MSPI_MODE
    #if (PADS_MSPI_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_MSPI_MODE   ((PADS_MSPI_MODE == PAD_SPI1) ? BIT0 : \
                                 (PADS_MSPI_MODE == PAD_SPI2) ? BIT1 : \
                                 (PADS_MSPI_MODE == PAD_SPI3) ? BIT2 : \
                                 (PADS_MSPI_MODE == PAD_SPI4) ? BIT3 : 0)
        _RVM1(0x1eb4, _CONFIG_MSPI_MODE, (BIT3 | BIT2 | BIT1 | BIT0)),
    #endif
#endif

//=============================================================================
#ifdef PADS_BT656_CTRL_MODE
    #if (PADS_BT656_CTRL_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_BT656_CTRL_MODE ((PADS_BT656_CTRL_MODE == PAD_TS1) ? BIT6:  \
                                     (PADS_BT656_CTRL_MODE == PAD_PCM) ? BIT7:  \
                                     (PADS_BT656_CTRL_MODE == PADS_GPIO) ? (BIT7 | BIT6) : 0)
        _RVM1(0x1edf, _CONFIG_BT656_CTRL_MODE, (BIT7 | BIT6)),
    #endif
#endif

//=============================================================================
#ifdef PADS_DDCR_MODE
    #if (PADS_DDCR_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_DDCR_MODE   ((PADS_DDCR_MODE == PAD_DDCR) ? BIT0 : \
                                 (PADS_DDCR_MODE == PAD_IIC) ? BIT1 : 0)
        _RVM1(0x1eae, _CONFIG_DDCR_MODE, (BIT1 | BIT0)),
    #endif
#endif

//=============================================================================
#ifdef PADS_MIIC_MODE0
    #if (PADS_MIIC_MODE0 != UNKNOWN_PAD_MUX)
    #define _CONFIG_MIIC_MODE0  ((PADS_MIIC_MODE0 == PAD_GPIO17) ? BIT0 : \
                                 (PADS_MIIC_MODE0 == PAD_GPIO18) ? BIT0 : \
                                 (PADS_MIIC_MODE0 == PAD_TS1_CLK) ? BIT1 : \
                                 (PADS_MIIC_MODE0 == PAD_TS1_SYNC) ? BIT1 : 0)
        _RVM1(0x1eb5, _CONFIG_MIIC_MODE0, (BIT1 | BIT0)),
    #endif
#endif

#ifdef PADS_MIIC_MODE1
    #if (PADS_MIIC_MODE1 != UNKNOWN_PAD_MUX)
    #define _CONFIG_MIIC_MODE1  ((PADS_MIIC_MODE1 == PAD_TGPIO2) ? BIT2 : \
                                 (PADS_MIIC_MODE1 == PAD_TGPIO3) ? BIT2 : \
                                 (PADS_MIIC_MODE1 == PAD_TS1_VLD) ? BIT3 : \
                                 (PADS_MIIC_MODE1 == PAD_TS1_D0) ? BIT3 : 0)
        _RVM1(0x1eb5, _CONFIG_MIIC_MODE1, (BIT3 | BIT2)),
    #endif
#endif

#ifdef PADS_MIIC_MODE2
    #if (PADS_MIIC_MODE2 != UNKNOWN_PAD_MUX)
    #define _CONFIG_MIIC_MODE2  ((PADS_MIIC_MODE2 == PAD_I2S_IN_BCK) ? BIT4 : \
                                 (PADS_MIIC_MODE2 == PAD_I2S_IN_SD) ? BIT4 : \
                                 (PADS_MIIC_MODE2 == PAD_TS1_VLD) ? BIT5 : \
                                 (PADS_MIIC_MODE2 == PAD_TS1_D0) ? BIT5 : 0)
        _RVM1(0x1eb5, _CONFIG_MIIC_MODE2, (BIT5 | BIT4)),
    #endif
#endif

//=============================================================================
#ifdef PADS_SM_MODE
    #if (PADS_SM_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_SM_MODE     ((PADS_SM_MODE == CONFIG_SMART_CARD_PWM) ? BIT2 : \
                                 (PADS_SM_MODE == CONFIG_SMART_CARD_TS1) ? BIT3 : \
                                 (PADS_SM_MODE == CONFIG_SMART_CARD_PCM) ? (BIT3 | BIT2) : 0)
        _RVM1(0x1e17, _CONFIG_SM_MODE, (BIT3 | BIT2)),

    #if (PADS_SM_MODE == SMART_CARD_PCM)
        _RVM1(0x1ec8, 0, (BIT1 | BIT0)),          //Disable Ctrl/Address/Data Pads of PCM/CI
        _RVM1(0x1e9f, 0, (BIT7 | BIT6)),
    #endif
/*
    #if (PADS_SM_MODE == SMART_CARD_TS1)
        _RVM1(0x1e24, 0, (BIT2 | BIT1 | BIT0)),
        _RVM1(0x1eaf, 0, (BIT5 | BIT4 | BIT3)),
    #endif
*/
    #endif
#endif

#ifdef PADS_SMART_CARD_VCC
    #if (PADS_SMART_CARD_VCC != UNKNOWN_PAD_MUX)
    #define _CONFIG_SMART_CARD_VCC_MODE ((PADS_SMART_CARD_VCC == CONFIG_SMART_CARD_VCC_3P3V) ? 0 : \
                                         (PADS_SMART_CARD_VCC == CONFIG_SMART_CARD_VCC_5V) ? BIT3 : 0)
        _RVM1(0x0a42, _CONFIG_SMART_CARD_VCC_MODE, BIT3),
    #endif
#endif

//=============================================================================
#ifdef PADS_PDTRACE_MODE
    #if (PADS_PDTRACE_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_PDTRACE_MODE    ((PADS_PDTRACE_MODE == PAD_TS1) ? BIT0 : \
                                     (PADS_PDTRACE_MODE == PADS_GPIO) ? BIT1 : 0)
        _RVM1(0x1e9f, _CONFIG_PDTRACE_MODE, (BIT1 | BIT0)),
    #endif
#endif

//=============================================================================
#ifdef PADS_TCON0_MODE
    #if (PADS_TCON0_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_TCON0_MODE      ((PADS_TCON0_MODE == ENABLE) ? BIT0 : 0)
        _RVM1(0x1eb9, _CONFIG_TCON0_MODE, BIT0),
    #endif
#endif

#ifdef PADS_TCON1_MODE
    #if (PADS_TCON1_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_TCON1_MODE      ((PADS_TCON1_MODE == ENABLE) ? BIT1 : 0)
        _RVM1(0x1eb9, _CONFIG_TCON1_MODE, BIT1),
    #endif
#endif

#ifdef PADS_TCON2_MODE
    #if (PADS_TCON2_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_TCON2_MODE      ((PADS_TCON2_MODE == ENABLE) ? BIT2 : 0)
        _RVM1(0x1eb9, _CONFIG_TCON2_MODE, BIT2),
    #endif
#endif

#ifdef PADS_TCON3_MODE
    #if (PADS_TCON3_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_TCON3_MODE      ((PADS_TCON3_MODE == ENABLE) ? BIT3 : 0)
        _RVM1(0x1eb9, _CONFIG_TCON3_MODE, BIT3),
    #endif
#endif

#ifdef PADS_TCON4_MODE
    #if (PADS_TCON4_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_TCON4_MODE      ((PADS_TCON4_MODE == ENABLE) ? BIT4 : 0)
        _RVM1(0x1eb9, _CONFIG_TCON4_MODE, BIT4),
    #endif
#endif

#ifdef PADS_TCON5_MODE
    #if (PADS_TCON5_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_TCON5_MODE      ((PADS_TCON5_MODE == ENABLE) ? BIT5 : 0)
        _RVM1(0x1eb9, _CONFIG_TCON5_MODE, BIT5),
    #endif
#endif

#ifdef PADS_TCON6_MODE
    #if (PADS_TCON6_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_TCON6_MODE      ((PADS_TCON6_MODE == ENABLE) ? BIT6 : 0)
        _RVM1(0x1eb9, _CONFIG_TCON6_MODE, BIT6),
    #endif
#endif

#ifdef PADS_TCON7_MODE
    #if (PADS_TCON7_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_TCON7_MODE      ((PADS_TCON7_MODE == ENABLE) ? BIT7 : 0)
        _RVM1(0x1eb9, _CONFIG_TCON7_MODE, BIT7),
    #endif
#endif

//=============================================================================
#ifdef ENABLE_EXT_GPIO_INT0
    #if (ENABLE_EXT_GPIO_INT0 != UNKNOWN_PAD_MUX)
    #define _CONFIG_EXT_GPIO_INT0   ((ENABLE_EXT_GPIO_INT0 == ENABLE) ? BIT0 : 0)
        _RVM1(0x1ee0, _CONFIG_EXT_GPIO_INT0, BIT0),
    #endif
#endif

#ifdef ENABLE_EXT_GPIO_INT1
    #if (ENABLE_EXT_GPIO_INT1 != UNKNOWN_PAD_MUX)
    #define _CONFIG_EXT_GPIO_INT1   ((ENABLE_EXT_GPIO_INT1 == ENABLE) ? BIT1 : 0)
        _RVM1(0x1ee0, _CONFIG_EXT_GPIO_INT1, BIT1),
    #endif
#endif

#ifdef ENABLE_EXT_GPIO_INT2
    #if (ENABLE_EXT_GPIO_INT2 != UNKNOWN_PAD_MUX)
    #define _CONFIG_EXT_GPIO_INT2   ((ENABLE_EXT_GPIO_INT2 == ENABLE) ? BIT2 : 0)
        _RVM1(0x1ee0, _CONFIG_EXT_GPIO_INT0, BIT2),
    #endif
#endif

#ifdef ENABLE_EXT_GPIO_INT3
    #if (ENABLE_EXT_GPIO_INT3 != UNKNOWN_PAD_MUX)
    #define _CONFIG_EXT_GPIO_INT3   ((ENABLE_EXT_GPIO_INT3 == ENABLE) ? BIT3 : 0)
        _RVM1(0x1ee0, _CONFIG_EXT_GPIO_INT0, BIT3),
    #endif
#endif

#ifdef ENABLE_EXT_GPIO_INT4
    #if (ENABLE_EXT_GPIO_INT4 != UNKNOWN_PAD_MUX)
    #define _CONFIG_EXT_GPIO_INT4   ((ENABLE_EXT_GPIO_INT4 == ENABLE) ? BIT4 : 0)
        _RVM1(0x1ee0, _CONFIG_EXT_GPIO_INT4, BIT4),
    #endif
#endif

#ifdef ENABLE_EXT_GPIO_INT5
    #if (ENABLE_EXT_GPIO_INT5 != UNKNOWN_PAD_MUX)
    #define _CONFIG_EXT_GPIO_INT5   ((ENABLE_EXT_GPIO_INT0 == ENABLE) ? BIT5 : 0)
        _RVM1(0x1ee0, _CONFIG_EXT_GPIO_INT5, BIT5),
    #endif
#endif

#ifdef ENABLE_EXT_GPIO_INT6
    #if (ENABLE_EXT_GPIO_INT6 != UNKNOWN_PAD_MUX)
    #define _CONFIG_EXT_GPIO_INT6   ((ENABLE_EXT_GPIO_INT6 == ENABLE) ? BIT6 : 0)
        _RVM1(0x1ee0, _CONFIG_EXT_GPIO_INT6, BIT6),
    #endif
#endif

#ifdef ENABLE_EXT_GPIO_INT7
    #if (ENABLE_EXT_GPIO_INT7 != UNKNOWN_PAD_MUX)
    #define _CONFIG_EXT_GPIO_INT7   ((ENABLE_EXT_GPIO_INT7 == ENABLE) ? BIT7 : 0)
        _RVM1(0x1ee0, _CONFIG_EXT_GPIO_INT7, BIT7),
    #endif
#endif

#ifdef ENABLE_EXT_GPIO_INT8
    #if (ENABLE_EXT_GPIO_INT8 != UNKNOWN_PAD_MUX)
    #define _CONFIG_EXT_GPIO_INT8   ((ENABLE_EXT_GPIO_INT8 == ENABLE) ? BIT0 : 0)
        _RVM1(0x1e3e, _CONFIG_EXT_GPIO_INT8, BIT0),
    #endif
#endif

#ifdef ENABLE_EXT_GPIO_INT9
    #if (ENABLE_EXT_GPIO_INT9 != UNKNOWN_PAD_MUX)
    #define _CONFIG_EXT_GPIO_INT9   ((ENABLE_EXT_GPIO_INT9 == ENABLE) ? BIT1 : 0)
        _RVM1(0x1e3e, _CONFIG_EXT_GPIO_INT9, BIT1),
    #endif
#endif
//=============================================================================
#ifdef ENABLE_PM51_PORT1_GPIO0
    #if (ENABLE_PM51_PORT1_GPIO0 != UNKNOWN_PAD_MUX)
    #define _CONFIG_PM51_PORT1_GPIO0    ((ENABLE_PM51_PORT1_GPIO0 == ENABLE) ? BIT0 : 0)
        _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO0, BIT0),
    #endif
#endif

#ifdef ENABLE_PM51_PORT1_GPIO1
    #if (ENABLE_PM51_PORT1_GPIO1 != UNKNOWN_PAD_MUX)
    #define _CONFIG_PM51_PORT1_GPIO1    ((ENABLE_PM51_PORT1_GPIO1 == ENABLE) ? BIT1 : 0)
        _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO1, BIT1),
    #endif
#endif

#ifdef ENABLE_PM51_PORT1_GPIO2
    #if (ENABLE_PM51_PORT1_GPIO2 != UNKNOWN_PAD_MUX)
    #define _CONFIG_PM51_PORT1_GPIO2    ((ENABLE_PM51_PORT1_GPIO2 == ENABLE) ? BIT2 : 0)
        _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO2, BIT2),
    #endif
#endif

#ifdef ENABLE_PM51_PORT1_GPIO3
    #if (ENABLE_PM51_PORT1_GPIO3 != UNKNOWN_PAD_MUX)
    #define _CONFIG_PM51_PORT1_GPIO3    ((ENABLE_PM51_PORT1_GPIO3 == ENABLE) ? BIT3 : 0)
        _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO3, BIT3),
    #endif
#endif

#ifdef ENABLE_PM51_PORT1_GPIO4
    #if (ENABLE_PM51_PORT1_GPIO4 != UNKNOWN_PAD_MUX)
    #define _CONFIG_PM51_PORT1_GPIO4    ((ENABLE_PM51_PORT1_GPIO4 == ENABLE) ? BIT4 : 0)
        _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO4, BIT4),
    #endif
#endif

#ifdef ENABLE_PM51_PORT1_GPIO5
    #if (ENABLE_PM51_PORT1_GPIO5 != UNKNOWN_PAD_MUX)
    #define _CONFIG_PM51_PORT1_GPIO5    ((ENABLE_PM51_PORT1_GPIO5 == ENABLE) ? BIT5 : 0)
        _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO5, BIT5),
    #endif
#endif

#ifdef ENABLE_PM51_PORT1_GPIO6
    #if (ENABLE_PM51_PORT1_GPIO6 != UNKNOWN_PAD_MUX)
    #define _CONFIG_PM51_PORT1_GPIO6    ((ENABLE_PM51_PORT1_GPIO6 == ENABLE) ? BIT6 : 0)
        _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO6, BIT6),
    #endif
#endif

#ifdef ENABLE_PM51_PORT1_GPIO7
    #if (ENABLE_PM51_PORT1_GPIO7 != UNKNOWN_PAD_MUX)
    #define _CONFIG_PM51_PORT1_GPIO7    ((ENABLE_PM51_PORT1_GPIO7 == ENABLE) ? BIT7 : 0)
        _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO7, BIT7),
    #endif
#endif

//=============================================================================
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7),     //reg[101ea1]#7 = 0b
    _END_OF_TBL_,

//=================================================================================================
    //External Flash #1
    _MEMMAP_PM_,
    _RVM1(0x0e6a, 0, BIT0),             //Select to spi_do, spi_di and spi_ck
    _RVM1(0x0e6a, 0, BIT1),             //Select to spi_cz0
    _RVM1(0x08f4, 0, (BIT1 | BIT0)),    //Select to External #1 SPI Flash

#if (PIN_FLASH_WP0)
#if ((MS_BOARD_TYPE_SEL == BD_MST176A_D01A_S_MONET))
    _RVM1(0x0e21, BIT2, BIT2),          //Output Value of PM10
    _RVM1(0x0e1f, 0, BIT2),             //Output Enable of PM10
#elif (MS_BOARD_TYPE_SEL == BD_FPGA_MONET)
#else
    #error [ERROR] Invalid WP0 Settings in Unknown Board
#endif
#endif
    _END_OF_TBL_,

//=================================================================================================
    //External Flash #2
    _MEMMAP_PM_,
    _RVM1(0x0e6a, 0, BIT0),             //Select to spi_do, spi_di and spi_ck
#if (PIN_SPI_CZ1)
    _RVM1(0x0e6a, 0, BIT2),             //Select to spi_cz1
    _RVM1(0x08f4, 1, (BIT1 | BIT0)),    //Select to External #2 SPI Flash
#if (PIN_FLASH_WP1)
#if ((MS_BOARD_TYPE_SEL == BD_MST176A_D01A_S_MONET))
    _RVM1(0x0e21, BIT2, BIT2),          //Output Value of PM10
    _RVM1(0x0e1f, 0, BIT2),             //Output Enable of PM10
#elif (MS_BOARD_TYPE_SEL == BD_FPGA_MONET)
#else
    #error [ERROR] Invalid WP1 Settings in Unknown Board
#endif
#endif
    _END_OF_TBL_,
#endif

};
