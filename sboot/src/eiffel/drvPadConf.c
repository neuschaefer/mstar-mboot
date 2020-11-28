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
#include "hwreg_eiffel.h"
#include "chip/bond.h"

#define GPIO_NONE                   0       // Not GPIO pin (default)
#define GPIO_IN                     1       // GPI
#define GPIO_OUT_LOW                2       // GPO output low
#define GPIO_OUT_HIGH               3       // GPO output high

#if defined(ARM_CHAKRA) || defined(MIPS_CHAKRA) || defined(MSOS_TYPE_LINUX)
#define _MapBase_nonPM_EIFFEL       (RIU_MAP + 0x200000)
#define _MapBase_PM_EIFFEL          RIU_MAP
#else
#define _MapBase_nonPM_EIFFEL       0xA0200000
#define _MapBase_PM_EIFFEL          0xA0000000
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
        _RVM1(0x0e39, BIT2, BIT2),   //reg[0e39]#2 = 1
        #undef PAD_VID0_IS_GPIO
        #define PAD_VID0_IS_GPIO    GPIO_NONE
    #endif

    #if(PAD_VID1_IS_GPIO != GPIO_NONE)
        #define PAD_VID1_OEN (PAD_VID1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_VID1_OUT (PAD_VID1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2e85, PAD_VID1_OUT, BIT0),
        _RVM1(0x2e85, PAD_VID1_OEN, BIT1),
        //reg_vid_is_gpio
        _RVM1(0x0e39, BIT2, BIT2),   //reg[0e39]#2 = 1
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
#define _CONFIG_NAND_MODE   ((PADS_NAND_MODE == PAD_PCM_D) ? BIT6 : \
                             (PADS_NAND_MODE == PAD_PCM_A) ? BIT7 : 0)
    _RVM1(0x1ede, _CONFIG_NAND_MODE, (BIT7 | BIT6)),
#define _CONFIG_DQS_MODE   ((PADS_NAND_MODE == PAD_PCM_A_DQS) ? BIT0 : 0)
    _RVM1(0x1edf, _CONFIG_DQS_MODE, BIT0),
#else
    _RVM1(0x1edf, 0, BIT0),
    _RVM1(0x1ede, 0, (BIT7 | BIT6)),
#endif
#endif

#ifdef PADS_NAND_CS1_EN
#if (PADS_NAND_CS1_EN != UNKNOWN_PAD_MUX)
#define _CONFIG_NAND_CS1_EN ((PADS_NAND_CS1_EN == ENABLE) ? BIT5:  0)
    _RVM1(0x1ede, _CONFIG_NAND_CS1_EN, BIT5),
#endif
#endif

#ifdef PADS_NAND_PE
#if (PADS_NAND_PE == ENABLE)
    _RVM1(0x1e1a, BITMASK(7:0), BITMASK(7:0)),
    _RVM1(0x1e1b, BIT0, BIT0),
#else
    _RVM1(0x1e1a, 0, BITMASK(7:0)),
    _RVM1(0x1e1b, 0, BIT0),
#endif
#endif

//=============================================================================
#ifdef PADS_EMMC_MODE
#if (PADS_EMMC_MODE != UNKNOWN_PAD_MUX)
#define _CONFIG_EMMC_MODE   ((PADS_EMMC_MODE == PAD_PCM_D) ? BIT6 : \
                             (PADS_EMMC_MODE == PAD_NAND_CTRL) ? (BIT7 | BIT6) : 0)
    _RVM1(0x1edc, _CONFIG_EMMC_MODE, (BIT7 | BIT6)),
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
        #define PAD_PM_SPI_CZ_OEN (PAD_PM_SPI_CZ_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_PM_SPI_CZ_OUT (PAD_PM_SPI_CZ_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x0f2e, PAD_PM_SPI_CZ_OUT, BIT1),
        _RVM1(0x0f2e, PAD_PM_SPI_CZ_OEN, BIT0),
        //reg_spi_is_gpio[1]
        _RVM1(0x0e6a, BIT1, BIT1),   //reg[0e6a]#1 = 1b
    #endif

    #if(PAD_PM_SPI_CK_IS_GPIO != GPIO_NONE)
        #define PAD_PM_SPI_CK_OEN (PAD_PM_SPI_CK_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_PM_SPI_CK_OUT (PAD_PM_SPI_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x0f30, PAD_PM_SPI_CK_OUT, BIT1),
        _RVM1(0x0f30, PAD_PM_SPI_CK_OEN, BIT0),
        //reg_spi_is_gpio[0]
        _RVM1(0x0e6a, BIT0, BIT0),   //reg[0e6a]#0 = 1b
    #endif

    #if(PAD_PM_SPI_DI_IS_GPIO != GPIO_NONE)
        #define PAD_PM_SPI_DI_OEN (PAD_PM_SPI_DI_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_PM_SPI_DI_OUT (PAD_PM_SPI_DI_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x0f32, PAD_PM_SPI_DI_OUT, BIT1),
        _RVM1(0x0f32, PAD_PM_SPI_DI_OEN, BIT0),
        //reg_spi_is_gpio[0]
        _RVM1(0x0e6a, BIT0, BIT0),   //reg[0e6a]#0 = 1b
    #endif

    #if(PAD_PM_SPI_DO_IS_GPIO != GPIO_NONE)
        #define PAD_PM_SPI_DO_OEN (PAD_PM_SPI_DO_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_PM_SPI_DO_OUT (PAD_PM_SPI_DO_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x0f34, PAD_PM_SPI_DO_OUT, BIT1),
        _RVM1(0x0f34, PAD_PM_SPI_DO_OEN, BIT0),
        //reg_spi_is_gpio[0]
        _RVM1(0x0e6a, BIT0, BIT0),   //reg[0e6a]#0 = 1b
    #endif

    #if(PAD_IRIN_IS_GPIO != GPIO_NONE)
        #define PAD_IRIN_OEN (PAD_IRIN_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_IRIN_OUT (PAD_IRIN_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x0f26, PAD_IRIN_OUT, BIT1),
        _RVM1(0x0f26, PAD_IRIN_OEN, BIT0),
        //reg_ir_is_gpio
        _RVM1(0x0e38, BIT4, BIT4),   //reg[0e38]#4 = 1b
    #endif

    #if(PAD_CEC_IS_GPIO != GPIO_NONE)
        #define PAD_CEC_OEN (PAD_CEC_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_CEC_OUT (PAD_CEC_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x0f2a, PAD_CEC_OUT, BIT1),
        _RVM1(0x0f2a, PAD_CEC_OEN, BIT0),
        //reg_cec_is_gpio
        _RVM1(0x0e38, BIT6, BIT6),   //reg[0e38]#6 = 1b
    #endif

    #if(PAD_AV_LNK_IS_GPIO != GPIO_NONE)
        #define PAD_AV_LNK_OEN (PAD_AV_LNK_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_AV_LNK_OUT (PAD_AV_LNK_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x0f2c, PAD_AV_LNK_OUT, BIT1),
        _RVM1(0x0f2c, PAD_AV_LNK_OEN, BIT0),
        //reg_av_lnk_is_gpio
        _RVM1(0x0e38, BIT7, BIT7),   //reg[0e38]#7 = 1b
    #endif

    #if(PAD_PWM_PM_IS_GPIO != GPIO_NONE)
        #define PAD_PWM_PM_OEN (PAD_PWM_PM_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_PWM_PM_OUT (PAD_PWM_PM_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x0f28, PAD_PWM_PM_OUT, BIT1),
        _RVM1(0x0f28, PAD_PWM_PM_OEN, BIT0),
        //reg_pwm_pm_is_gpio
        _RVM1(0x0e38, BIT5, BIT5),   //reg[0e38]#5 = 1b
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
        _RVM1(0x0e6b, 0, BIT1),   //reg[0e6b]#1 = 0b
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
        //reg_spi_is_gpio[2]
        _RVM1(0x0e6a, BIT2, BIT2),   //reg[0e6a] #2 = 1b
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
        _RVM1(0x0e6b, 0, BIT0),   //reg[0e6b]#0 = 0b
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
        //reg_spi_is_gpio[3]
        _RVM1(0x0e6a, BIT3, BIT3),   //reg[0e6a] #3 = 1b
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
        _RVM1(0x0ee4, 0, BIT6),   //reg[0ee4] #6 = 0b
    #endif

    #if(PAD_GPIO_PM15_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO_PM15_OEN (PAD_GPIO_PM15_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_GPIO_PM15_OUT (PAD_GPIO_PM15_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x0f1e, PAD_GPIO_PM15_OUT, BIT1),
        _RVM1(0x0f1e, PAD_GPIO_PM15_OEN, BIT0),
        //reg_vbus_en_sel
        _RVM1(0x0ee4, 0, BIT7),   //reg[0ee4] #7 = 0b
    #endif

    #if(PAD_GPIO_PM16_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO_PM16_OEN (PAD_GPIO_PM16_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_GPIO_PM16_OUT (PAD_GPIO_PM16_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x0f20, PAD_GPIO_PM16_OUT, BIT1),
        _RVM1(0x0f20, PAD_GPIO_PM16_OEN, BIT0),
        //reg_cbus_debug_sel
        _RVM1(0x0ee5, 0, BIT0),   //reg[0ee5] #0 = 0b
    #endif

    #if(PAD_GPIO_PM17_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO_PM17_OEN (PAD_GPIO_PM17_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_GPIO_PM17_OUT (PAD_GPIO_PM17_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x0f22, PAD_GPIO_PM17_OUT, BIT1),
        _RVM1(0x0f22, PAD_GPIO_PM17_OEN, BIT0),
    #endif

    #if(PAD_GPIO_PM18_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO_PM18_OEN (PAD_GPIO_PM18_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_GPIO_PM18_OUT (PAD_GPIO_PM18_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x0f24, PAD_GPIO_PM18_OUT, BIT1),
        _RVM1(0x0f24, PAD_GPIO_PM18_OEN, BIT0),
    #endif

    #if(PAD_HOTPLUGA_IS_GPIO != GPIO_NONE)
        #define PAD_HOTPLUGA_OEN (PAD_HOTPLUGA_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_HOTPLUGA_OUT (PAD_HOTPLUGA_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
        _RVM1(0x0e4e, PAD_HOTPLUGA_OUT, BIT4),
        _RVM1(0x0e4e, PAD_HOTPLUGA_OEN, BIT0),
    #endif

    #if(PAD_HOTPLUGB_IS_GPIO != GPIO_NONE)
        #define PAD_HOTPLUGB_OEN (PAD_HOTPLUGB_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_HOTPLUGB_OUT (PAD_HOTPLUGB_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
        _RVM1(0x0e4e, PAD_HOTPLUGB_OUT, BIT5),
        _RVM1(0x0e4e, PAD_HOTPLUGB_OEN, BIT1),
    #endif

    #if(PAD_HOTPLUGC_IS_GPIO != GPIO_NONE)
        #define PAD_HOTPLUGC_OEN (PAD_HOTPLUGC_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_HOTPLUGC_OUT (PAD_HOTPLUGC_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x0e4e, PAD_HOTPLUGC_OUT, BIT6),
        _RVM1(0x0e4e, PAD_HOTPLUGC_OEN, BIT2),
        //reg_hplugc_mhl_en
        _RVM1(0x0ee6, 0, BIT0),   //reg[0ee6] #0 = 0b
        //reg_hotplugc_gpio_en
        _RVM1(0x0f36, BIT0, BIT0),   //reg[0f36] #0 = 1b
    #endif

    #if(PAD_HOTPLUGD_IS_GPIO != GPIO_NONE)
        #define PAD_HOTPLUGD_OEN (PAD_HOTPLUGD_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_HOTPLUGD_OUT (PAD_HOTPLUGD_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
        _RVM1(0x0e4e, PAD_HOTPLUGD_OUT, BIT7),
        _RVM1(0x0e4e, PAD_HOTPLUGD_OEN, BIT3),
        //reg_hplugd_mhl_en
        _RVM1(0x0ee7, 0, BIT0),   //reg[0ee7] #0 = 0b
        //reg_hotplugd_gpio_en
        _RVM1(0x0f36, BIT1, BIT1),   //reg[0f36] #1 = 1b
    #endif

    #if(PAD_DDCA_CK_IS_GPIO != GPIO_NONE)
        #define PAD_DDCA_CK_OEN (PAD_DDCA_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_DDCA_CK_OUT (PAD_DDCA_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x0494, PAD_DDCA_CK_OUT, BIT2),
        _RVM1(0x0494, PAD_DDCA_CK_OEN, BIT1),
        //reg_gpio2a0_en
        _RVM1(0x0494, BIT7, BIT7),   //reg[0494]#7 = 1b
    #endif

    #if(PAD_DDCA_DA_IS_GPIO != GPIO_NONE)
        #define PAD_DDCA_DA_OEN (PAD_DDCA_DA_IS_GPIO == GPIO_IN ? BIT5: 0)
        #define PAD_DDCA_DA_OUT (PAD_DDCA_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x0494, PAD_DDCA_DA_OUT, BIT6),
        _RVM1(0x0494, PAD_DDCA_DA_OEN, BIT5),
        //reg_gpio2a0_en
        _RVM1(0x0494, BIT7, BIT7),   //reg[0494]#7 = 1b
    #endif

    #if(PAD_DDCDA_CK_IS_GPIO != GPIO_NONE)
        #define PAD_DDCDA_CK_OEN (PAD_DDCDA_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_DDCDA_CK_OUT (PAD_DDCDA_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x0496, PAD_DDCDA_CK_OUT, BIT2),
        _RVM1(0x0496, PAD_DDCDA_CK_OEN, BIT1),
        //reg_gpio2d0_en
        _RVM1(0x0496, BIT7, BIT7),   //reg[0496]#7 = 1
    #endif

    #if(PAD_DDCDA_DA_IS_GPIO != GPIO_NONE)
        #define PAD_DDCDA_DA_OEN (PAD_DDCDA_DA_IS_GPIO == GPIO_IN ? BIT5: 0)
        #define PAD_DDCDA_DA_OUT (PAD_DDCDA_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
        _RVM1(0x0496, PAD_DDCDA_DA_OUT, BIT6),
        _RVM1(0x0496, PAD_DDCDA_DA_OEN, BIT5),
        //reg_gpio2d0_en
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

    #if(PAD_SAR_GPIO0_IS_GPIO != GPIO_NONE)
        #define PAD_SAR_GPIO0_OEN (PAD_SAR_GPIO0_IS_GPIO == GPIO_IN ? BIT0: 0)
        #define PAD_SAR_GPIO0_OUT (PAD_SAR_GPIO0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x1424, PAD_SAR_GPIO0_OUT, BIT0),
        _RVM1(0x1423, PAD_SAR_GPIO0_OEN, BIT0),
        //reg_sar_aisel[0]
        _RVM1(0x1422, 0, BIT0),   //reg[1422]#0 = 0
    #endif

    #if(PAD_SAR_GPIO1_IS_GPIO != GPIO_NONE)
        #define PAD_SAR_GPIO1_OEN (PAD_SAR_GPIO1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_SAR_GPIO1_OUT (PAD_SAR_GPIO1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
        _RVM1(0x1424, PAD_SAR_GPIO1_OUT, BIT1),
        _RVM1(0x1423, PAD_SAR_GPIO1_OEN, BIT1),
        //reg_sar_aisel[1]
        _RVM1(0x1422, 0, BIT1),   //reg[1422]#1 = 0
    #endif

    #if(PAD_SAR_GPIO2_IS_GPIO != GPIO_NONE)
        #define PAD_SAR_GPIO2_OEN (PAD_SAR_GPIO2_IS_GPIO == GPIO_IN ? BIT2: 0)
        #define PAD_SAR_GPIO2_OUT (PAD_SAR_GPIO2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
        _RVM1(0x1424, PAD_SAR_GPIO2_OUT, BIT2),
        _RVM1(0x1423, PAD_SAR_GPIO2_OEN, BIT2),
        //reg_sar_aisel[2]
        _RVM1(0x1422, 0, BIT2),   //reg[1422]#2 = 0
    #endif

    #if(PAD_SAR_GPIO3_IS_GPIO != GPIO_NONE)
        #define PAD_SAR_GPIO3_OEN (PAD_SAR_GPIO3_IS_GPIO == GPIO_IN ? BIT3: 0)
        #define PAD_SAR_GPIO3_OUT (PAD_SAR_GPIO3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
        _RVM1(0x1424, PAD_SAR_GPIO3_OUT, BIT3),
        _RVM1(0x1423, PAD_SAR_GPIO3_OEN, BIT3),
        //reg_sar_aisel[3]
        _RVM1(0x1422, 0, BIT3),   //reg[1422]#3 = 0
    #endif

    #if(PAD_SAR_GPIO4_IS_GPIO != GPIO_NONE)
        #define PAD_SAR_GPIO4_OEN (PAD_SAR_GPIO4_IS_GPIO == GPIO_IN ? BIT4: 0)
        #define PAD_SAR_GPIO4_OUT (PAD_SAR_GPIO4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
        _RVM1(0x1424, PAD_SAR_GPIO4_OUT, BIT4),
        _RVM1(0x1423, PAD_SAR_GPIO4_OEN, BIT4),
        //reg_sar_aisel[4]
        _RVM1(0x1422, 0, BIT4),   //reg[1422]#4 = 0
    #endif

     _RVM1(0x1426, BIT6, BIT6), // SAR Level default set to 3.0V

    #if(PAD_LED0_IS_GPIO != GPIO_NONE)
        #define PAD_LED0_OEN (PAD_LED0_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_LED0_OUT (PAD_LED0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2e80, PAD_LED0_OUT, BIT0),
        _RVM1(0x2e80, PAD_LED0_OEN, BIT1),
        //reg_wol_is_gpio
        _RVM1(0x0e39, BIT1, BIT1),   //reg[0e39]#1 = 1
    #endif

    #if(PAD_LED1_IS_GPIO != GPIO_NONE)
        #define PAD_LED1_OEN (PAD_LED1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_LED1_OUT (PAD_LED1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2e81, PAD_LED1_OUT, BIT0),
        _RVM1(0x2e81, PAD_LED1_OEN, BIT1),
        //reg_wol_is_gpio
        _RVM1(0x0e39, BIT1, BIT1),   //reg[0e39]#1 = 1
    #endif

    #if(PAD_VID0_IS_GPIO != GPIO_NONE)
        #define PAD_VID0_OEN (PAD_VID0_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_VID0_OUT (PAD_VID0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2e84, PAD_VID0_OUT, BIT0),
        _RVM1(0x2e84, PAD_VID0_OEN, BIT1),
        //reg_vid_is_gpio
        _RVM1(0x0e39, BIT2, BIT2),   //reg[0e39]#2 = 1
    #endif

    #if(PAD_VID1_IS_GPIO != GPIO_NONE)
        #define PAD_VID1_OEN (PAD_VID1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_VID1_OUT (PAD_VID1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2e85, PAD_VID1_OUT, BIT0),
        _RVM1(0x2e85, PAD_VID1_OEN, BIT1),
        //reg_vid_is_gpio
        _RVM1(0x0e39, BIT2, BIT2),   //reg[0e39]#2 = 1
    #endif

    #if(PAD_WOL_INT_IS_GPIO != GPIO_NONE)
        #define PAD_WOL_INT_OEN (PAD_WOL_INT_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_WOL_INT_OUT (PAD_WOL_INT_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2e82, PAD_WOL_INT_OUT, BIT0),
        _RVM1(0x2e82, PAD_WOL_INT_OEN, BIT1),
        //reg_wol_is_gpio
        _RVM1(0x0e39, BIT1, BIT1),   //reg[0e39]#1 = 1
    #endif

    _MEMMAP_nonPM_,

    #if(PAD_DDCR_DA_IS_GPIO != GPIO_NONE)
        #define PAD_DDCR_DA_OEN (PAD_DDCR_DA_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_DDCR_DA_OUT (PAD_DDCR_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b86, PAD_DDCR_DA_OUT, BIT0),
        _RVM1(0x2b86, PAD_DDCR_DA_OEN, BIT1),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_ddcrmode[1:0]
        _RVM1(0x1eae, 0, BIT1 | BIT0),   //reg[101eae]#1 ~ #0 = 0b
        //reg_ddcrmode[1:0]
        _RVM1(0x1eae, 0, BIT1 | BIT0),   //reg[101eae]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_DDCR_CK_IS_GPIO != GPIO_NONE)
        #define PAD_DDCR_CK_OEN (PAD_DDCR_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_DDCR_CK_OUT (PAD_DDCR_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b87, PAD_DDCR_CK_OUT, BIT0),
        _RVM1(0x2b87, PAD_DDCR_CK_OEN, BIT1),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_ddcrmode[1:0]
        _RVM1(0x1eae, 0, BIT1 | BIT0),   //reg[101eae]#1 ~ #0 = 0b
        //reg_ddcrmode[1:0]
        _RVM1(0x1eae, 0, BIT1 | BIT0),   //reg[101eae]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO0_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO0_OEN (PAD_GPIO0_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO0_OUT (PAD_GPIO0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b00, PAD_GPIO0_OUT, BIT0),
        _RVM1(0x2b00, PAD_GPIO0_OEN, BIT1),
        //reg_ej_config[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 0b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_usbdrvvbusconfig[1:0]
        _RVM1(0x1e04, 0, BIT1 | BIT0),   //reg[101e04]#1 ~ #0 = 0b
        //reg_p1_enable[0]
        _RVM1(0x1ea4, 0, BIT0),   //reg[101ea4]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO1_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO1_OEN (PAD_GPIO1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO1_OUT (PAD_GPIO1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b01, PAD_GPIO1_OUT, BIT0),
        _RVM1(0x2b01, PAD_GPIO1_OEN, BIT1),
        //reg_ej_config[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 0b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_usbdrvvbusconfig[1:0]
        _RVM1(0x1e04, 0, BIT1 | BIT0),   //reg[101e04]#1 ~ #0 = 0b
        //reg_p1_enable[1]
        _RVM1(0x1ea4, 0, BIT1),   //reg[101ea4]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO2_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO2_OEN (PAD_GPIO2_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO2_OUT (PAD_GPIO2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b02, PAD_GPIO2_OUT, BIT0),
        _RVM1(0x2b02, PAD_GPIO2_OEN, BIT1),
        //reg_ej_config[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 0b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_usbdrvvbusconfig[1:0]
        _RVM1(0x1e04, 0, BIT1 | BIT0),   //reg[101e04]#1 ~ #0 = 0b
        //reg_p1_enable[2]
        _RVM1(0x1ea4, 0, BIT2),   //reg[101ea4]#2 = 0b
        //reg_3dflagconfig[1:0]
        _RVM1(0x1eb3, 0, BIT7 | BIT6),   //reg[101eb3]#7 ~ #6 = 0b
        //reg_usb30vctl_config[[1:0]
        _RVM1(0x1e08, 0, BIT5 | BIT4),   //reg[101e08]#5 ~ #4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO3_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO3_OEN (PAD_GPIO3_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO3_OUT (PAD_GPIO3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b03, PAD_GPIO3_OUT, BIT0),
        _RVM1(0x2b03, PAD_GPIO3_OEN, BIT1),
        //reg_ej_config[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 0b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_seconduartmode[1:0]
        _RVM1(0x1e05, 0, BIT1 | BIT0),   //reg[101e05]#1 ~ #0 = 0b
        //reg_od2nduart[1:0]
        _RVM1(0x1ea9, 0, BIT1 | BIT0),   //reg[101ea9]#1 ~ #0 = 0b
        //reg_p1_enable[3]
        _RVM1(0x1ea4, 0, BIT3),   //reg[101ea4]#3 = 0b
        //reg_usb30vctl_config[[1:0]
        _RVM1(0x1e08, 0, BIT5 | BIT4),   //reg[101e08]#5 ~ #4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO4_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO4_OEN (PAD_GPIO4_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO4_OUT (PAD_GPIO4_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b04, PAD_GPIO4_OUT, BIT0),
        _RVM1(0x2b04, PAD_GPIO4_OEN, BIT1),
        //reg_ej_config[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 0b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_seconduartmode[1:0]
        _RVM1(0x1e05, 0, BIT1 | BIT0),   //reg[101e05]#1 ~ #0 = 0b
        //reg_od2nduart[1:0]
        _RVM1(0x1ea9, 0, BIT1 | BIT0),   //reg[101ea9]#1 ~ #0 = 0b
        //reg_p1_enable[4]
        _RVM1(0x1ea4, 0, BIT4),   //reg[101ea4]#4 = 0b
        //reg_usb30vctl_config[[1:0]
        _RVM1(0x1e08, 0, BIT5 | BIT4),   //reg[101e08]#5 ~ #4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO5_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO5_OEN (PAD_GPIO5_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO5_OUT (PAD_GPIO5_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b05, PAD_GPIO5_OUT, BIT0),
        _RVM1(0x2b05, PAD_GPIO5_OEN, BIT1),
        //reg_ej_config[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 0b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_fastuartmode[1:0]
        _RVM1(0x1e04, 0, BIT5 | BIT4),   //reg[101e04]#5 ~ #4 = 0b
        //reg_odfuart[1:0]
        _RVM1(0x1ea9, 0, BIT7 | BIT6),   //reg[101ea9]#7 ~ #6 = 0b
        //reg_p1_enable[5]
        _RVM1(0x1ea4, 0, BIT5),   //reg[101ea4]#5 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO6_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO6_OEN (PAD_GPIO6_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO6_OUT (PAD_GPIO6_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b06, PAD_GPIO6_OUT, BIT0),
        _RVM1(0x2b06, PAD_GPIO6_OEN, BIT1),
        //reg_ej_config[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 0b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_fastuartmode[1:0]
        _RVM1(0x1e04, 0, BIT5 | BIT4),   //reg[101e04]#5 ~ #4 = 0b
        //reg_odfuart[1:0]
        _RVM1(0x1ea9, 0, BIT7 | BIT6),   //reg[101ea9]#7 ~ #6 = 0b
        //reg_p1_enable[6]
        _RVM1(0x1ea4, 0, BIT6),   //reg[101ea4]#6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO7_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO7_OEN (PAD_GPIO7_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO7_OUT (PAD_GPIO7_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b07, PAD_GPIO7_OUT, BIT0),
        _RVM1(0x2b07, PAD_GPIO7_OEN, BIT1),
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_seconduartmode[1:0]
        _RVM1(0x1e05, 0, BIT1 | BIT0),   //reg[101e05]#1 ~ #0 = 0b
        //reg_od2nduart[1:0]
        _RVM1(0x1ea9, 0, BIT1 | BIT0),   //reg[101ea9]#1 ~ #0 = 0b
        //reg_p1_enable[7]
        _RVM1(0x1ea4, 0, BIT7),   //reg[101ea4]#7 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO8_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO8_OEN (PAD_GPIO8_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO8_OUT (PAD_GPIO8_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b08, PAD_GPIO8_OUT, BIT0),
        _RVM1(0x2b08, PAD_GPIO8_OEN, BIT1),
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_seconduartmode[1:0]
        _RVM1(0x1e05, 0, BIT1 | BIT0),   //reg[101e05]#1 ~ #0 = 0b
        //reg_od2nduart[1:0]
        _RVM1(0x1ea9, 0, BIT1 | BIT0),   //reg[101ea9]#1 ~ #0 = 0b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO9_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO9_OEN (PAD_GPIO9_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO9_OUT (PAD_GPIO9_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b09, PAD_GPIO9_OUT, BIT0),
        _RVM1(0x2b09, PAD_GPIO9_OEN, BIT1),
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_thirduartmode[1:0]
        _RVM1(0x1e05, 0, BIT3 | BIT2),   //reg[101e05]#3 ~ #2 = 0b
        //reg_od3rduart[1:0]
        _RVM1(0x1ea9, 0, BIT3 | BIT2),   //reg[101ea9]#3 ~ #2 = 0b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO10_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO10_OEN (PAD_GPIO10_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO10_OUT (PAD_GPIO10_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b0a, PAD_GPIO10_OUT, BIT0),
        _RVM1(0x2b0a, PAD_GPIO10_OEN, BIT1),
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_thirduartmode[1:0]
        _RVM1(0x1e05, 0, BIT3 | BIT2),   //reg[101e05]#3 ~ #2 = 0b
        //reg_od3rduart[1:0]
        _RVM1(0x1ea9, 0, BIT3 | BIT2),   //reg[101ea9]#3 ~ #2 = 0b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO11_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO11_OEN (PAD_GPIO11_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO11_OUT (PAD_GPIO11_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b0b, PAD_GPIO11_OUT, BIT0),
        _RVM1(0x2b0b, PAD_GPIO11_OEN, BIT1),
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_fourthuartmode[1:0]
        _RVM1(0x1e04, 0, BIT7 | BIT6),   //reg[101e04]#7 ~ #6 = 0b
        //reg_od4thuart[1:0]
        _RVM1(0x1ea9, 0, BIT5 | BIT4),   //reg[101ea9]#5 ~ #4 = 0b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO12_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO12_OEN (PAD_GPIO12_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO12_OUT (PAD_GPIO12_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b0c, PAD_GPIO12_OUT, BIT0),
        _RVM1(0x2b0c, PAD_GPIO12_OEN, BIT1),
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_fourthuartmode[1:0]
        _RVM1(0x1e04, 0, BIT7 | BIT6),   //reg[101e04]#7 ~ #6 = 0b
        //reg_od4thuart[1:0]
        _RVM1(0x1ea9, 0, BIT5 | BIT4),   //reg[101ea9]#5 ~ #4 = 0b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO13_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO13_OEN (PAD_GPIO13_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO13_OUT (PAD_GPIO13_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b0d, PAD_GPIO13_OUT, BIT0),
        _RVM1(0x2b0d, PAD_GPIO13_OEN, BIT1),
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_fastuartmode[1:0]
        _RVM1(0x1e04, 0, BIT5 | BIT4),   //reg[101e04]#5 ~ #4 = 0b
        //reg_odfuart[1:0]
        _RVM1(0x1ea9, 0, BIT7 | BIT6),   //reg[101ea9]#7 ~ #6 = 0b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO14_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO14_OEN (PAD_GPIO14_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO14_OUT (PAD_GPIO14_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b0e, PAD_GPIO14_OUT, BIT0),
        _RVM1(0x2b0e, PAD_GPIO14_OEN, BIT1),
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_fastuartmode[1:0]
        _RVM1(0x1e04, 0, BIT5 | BIT4),   //reg[101e04]#5 ~ #4 = 0b
        //reg_odfuart[1:0]
        _RVM1(0x1ea9, 0, BIT7 | BIT6),   //reg[101ea9]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO15_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO15_OEN (PAD_GPIO15_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO15_OUT (PAD_GPIO15_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b0f, PAD_GPIO15_OUT, BIT0),
        _RVM1(0x2b0f, PAD_GPIO15_OEN, BIT1),
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_i2smutemode[1:0]
        _RVM1(0x1e05, 0, BIT7 | BIT6),   //reg[101e05]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO16_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO16_OEN (PAD_GPIO16_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO16_OUT (PAD_GPIO16_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b10, PAD_GPIO16_OUT, BIT0),
        _RVM1(0x2b10, PAD_GPIO16_OEN, BIT1),
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_tserrout[1:0]
        _RVM1(0x1ec9, 0, BIT1 | BIT0),   //reg[101ec9]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO17_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO17_OEN (PAD_GPIO17_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO17_OUT (PAD_GPIO17_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b11, PAD_GPIO17_OUT, BIT0),
        _RVM1(0x2b11, PAD_GPIO17_OEN, BIT1),
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_miic_mode0
        _RVM1(0x1edc, 0, BIT0),   //reg[101edc]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO18_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO18_OEN (PAD_GPIO18_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO18_OUT (PAD_GPIO18_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b12, PAD_GPIO18_OUT, BIT0),
        _RVM1(0x2b12, PAD_GPIO18_OEN, BIT1),
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_miic_mode0
        _RVM1(0x1edc, 0, BIT0),   //reg[101edc]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO19_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO19_OEN (PAD_GPIO19_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO19_OUT (PAD_GPIO19_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b13, PAD_GPIO19_OUT, BIT0),
        _RVM1(0x2b13, PAD_GPIO19_OEN, BIT1),
        //reg_et_mode
        _RVM1(0x1edf, 0, BIT1),   //reg[101edf]#1 = 0b
        //reg_led_mode
        _RVM1(0x1eb4, 0, BIT4),   //reg[101eb4]#4 = 0b
        //reg_seconduartmode[1:0]
        _RVM1(0x1e05, 0, BIT1 | BIT0),   //reg[101e05]#1 ~ #0 = 0b
        //reg_od2nduart[1:0]
        _RVM1(0x1ea9, 0, BIT1 | BIT0),   //reg[101ea9]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO20_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO20_OEN (PAD_GPIO20_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO20_OUT (PAD_GPIO20_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b14, PAD_GPIO20_OUT, BIT0),
        _RVM1(0x2b14, PAD_GPIO20_OEN, BIT1),
        //reg_et_mode
        _RVM1(0x1edf, 0, BIT1),   //reg[101edf]#1 = 0b
        //reg_led_mode
        _RVM1(0x1eb4, 0, BIT4),   //reg[101eb4]#4 = 0b
        //reg_seconduartmode[1:0]
        _RVM1(0x1e05, 0, BIT1 | BIT0),   //reg[101e05]#1 ~ #0 = 0b
        //reg_od2nduart[1:0]
        _RVM1(0x1ea9, 0, BIT1 | BIT0),   //reg[101ea9]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO21_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO21_OEN (PAD_GPIO21_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO21_OUT (PAD_GPIO21_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b15, PAD_GPIO21_OUT, BIT0),
        _RVM1(0x2b15, PAD_GPIO21_OEN, BIT1),
        //reg_et_mode
        _RVM1(0x1edf, 0, BIT1),   //reg[101edf]#1 = 0b
        //reg_thirduartmode[1:0]
        _RVM1(0x1e05, 0, BIT3 | BIT2),   //reg[101e05]#3 ~ #2 = 0b
        //reg_od3rduart[1:0]
        _RVM1(0x1ea9, 0, BIT3 | BIT2),   //reg[101ea9]#3 ~ #2 = 0b
        //reg_ext_int[5]
        _RVM1(0x1ea5, 0, BIT5),   //reg[101ea5]#5 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO22_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO22_OEN (PAD_GPIO22_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO22_OUT (PAD_GPIO22_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b16, PAD_GPIO22_OUT, BIT0),
        _RVM1(0x2b16, PAD_GPIO22_OEN, BIT1),
        //reg_et_mode
        _RVM1(0x1edf, 0, BIT1),   //reg[101edf]#1 = 0b
        //reg_thirduartmode[1:0]
        _RVM1(0x1e05, 0, BIT3 | BIT2),   //reg[101e05]#3 ~ #2 = 0b
        //reg_od3rduart[1:0]
        _RVM1(0x1ea9, 0, BIT3 | BIT2),   //reg[101ea9]#3 ~ #2 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO23_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO23_OEN (PAD_GPIO23_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO23_OUT (PAD_GPIO23_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b17, PAD_GPIO23_OUT, BIT0),
        _RVM1(0x2b17, PAD_GPIO23_OEN, BIT1),
        //reg_et_mode
        _RVM1(0x1edf, 0, BIT1),   //reg[101edf]#1 = 0b
        //reg_fourthuartmode[1:0]
        _RVM1(0x1e04, 0, BIT7 | BIT6),   //reg[101e04]#7 ~ #6 = 0b
        //reg_od4thuart[1:0]
        _RVM1(0x1ea9, 0, BIT5 | BIT4),   //reg[101ea9]#5 ~ #4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO24_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO24_OEN (PAD_GPIO24_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO24_OUT (PAD_GPIO24_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b18, PAD_GPIO24_OUT, BIT0),
        _RVM1(0x2b18, PAD_GPIO24_OEN, BIT1),
        //reg_et_mode
        _RVM1(0x1edf, 0, BIT1),   //reg[101edf]#1 = 0b
        //reg_fourthuartmode[1:0]
        _RVM1(0x1e04, 0, BIT7 | BIT6),   //reg[101e04]#7 ~ #6 = 0b
        //reg_od4thuart[1:0]
        _RVM1(0x1ea9, 0, BIT5 | BIT4),   //reg[101ea9]#5 ~ #4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO25_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO25_OEN (PAD_GPIO25_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO25_OUT (PAD_GPIO25_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b19, PAD_GPIO25_OUT, BIT0),
        _RVM1(0x2b19, PAD_GPIO25_OEN, BIT1),
        //reg_et_mode
        _RVM1(0x1edf, 0, BIT1),   //reg[101edf]#1 = 0b
        //reg_fastuartmode[1:0]
        _RVM1(0x1e04, 0, BIT5 | BIT4),   //reg[101e04]#5 ~ #4 = 0b
        //reg_odfuart[1:0]
        _RVM1(0x1ea9, 0, BIT7 | BIT6),   //reg[101ea9]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO26_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO26_OEN (PAD_GPIO26_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO26_OUT (PAD_GPIO26_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b1a, PAD_GPIO26_OUT, BIT0),
        _RVM1(0x2b1a, PAD_GPIO26_OEN, BIT1),
        //reg_et_mode
        _RVM1(0x1edf, 0, BIT1),   //reg[101edf]#1 = 0b
        //reg_fastuartmode[1:0]
        _RVM1(0x1e04, 0, BIT5 | BIT4),   //reg[101e04]#5 ~ #4 = 0b
        //reg_odfuart[1:0]
        _RVM1(0x1ea9, 0, BIT7 | BIT6),   //reg[101ea9]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_GPIO27_IS_GPIO != GPIO_NONE)
        #define PAD_GPIO27_OEN (PAD_GPIO27_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_GPIO27_OUT (PAD_GPIO27_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b1b, PAD_GPIO27_OUT, BIT0),
        _RVM1(0x2b1b, PAD_GPIO27_OEN, BIT1),
        //reg_et_mode
        _RVM1(0x1edf, 0, BIT1),   //reg[101edf]#1 = 0b
        //reg_ext_int[4]
        _RVM1(0x1ea5, 0, BIT4),   //reg[101ea5]#4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_I2S_IN_WS_IS_GPIO != GPIO_NONE)
        #define PAD_I2S_IN_WS_OEN (PAD_I2S_IN_WS_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_I2S_IN_WS_OUT (PAD_I2S_IN_WS_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b36, PAD_I2S_IN_WS_OUT, BIT0),
        _RVM1(0x2b36, PAD_I2S_IN_WS_OEN, BIT1),
        //reg_ej_config[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 0b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_i2sinconfig
        _RVM1(0x1eae, 0, BIT2),   //reg[101eae]#2 = 0b
        //reg_mcujtagmode[1:0]
        //_RVM1(0x1ede, 0, BIT3 | BIT2),   //reg[101ede]#3 ~ #2 = 0b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 0b
        //reg_thirduartmode[1:0]
        _RVM1(0x1e05, 0, BIT3 | BIT2),   //reg[101e05]#3 ~ #2 = 0b
        //reg_od3rduart[1:0]
        _RVM1(0x1ea9, 0, BIT3 | BIT2),   //reg[101ea9]#3 ~ #2 = 0b
        //reg_ext_int[6]
        _RVM1(0x1ea5, 0, BIT6),   //reg[101ea5]#6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_I2S_IN_BCK_IS_GPIO != GPIO_NONE)
        #define PAD_I2S_IN_BCK_OEN (PAD_I2S_IN_BCK_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_I2S_IN_BCK_OUT (PAD_I2S_IN_BCK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b37, PAD_I2S_IN_BCK_OUT, BIT0),
        _RVM1(0x2b37, PAD_I2S_IN_BCK_OEN, BIT1),
        //reg_ej_config[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 0b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_i2sinconfig
        _RVM1(0x1eae, 0, BIT2),   //reg[101eae]#2 = 0b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 0b
        //reg_thirduartmode[1:0]
        _RVM1(0x1e05, 0, BIT3 | BIT2),   //reg[101e05]#3 ~ #2 = 0b
        //reg_od3rduart[1:0]
        _RVM1(0x1ea9, 0, BIT3 | BIT2),   //reg[101ea9]#3 ~ #2 = 0b
        //reg_miic_mode2
        _RVM1(0x1edc, 0, BIT2),   //reg[101edc]#2 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_I2S_IN_SD_IS_GPIO != GPIO_NONE)
        #define PAD_I2S_IN_SD_OEN (PAD_I2S_IN_SD_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_I2S_IN_SD_OUT (PAD_I2S_IN_SD_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b38, PAD_I2S_IN_SD_OUT, BIT0),
        _RVM1(0x2b38, PAD_I2S_IN_SD_OEN, BIT1),
        //reg_ej_config[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 0b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_i2sinconfig
        _RVM1(0x1eae, 0, BIT2),   //reg[101eae]#2 = 0b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 0b
        //reg_tserrout[1:0]
        _RVM1(0x1ec9, 0, BIT1 | BIT0),   //reg[101ec9]#1 ~ #0 = 0b
        //reg_miic_mode2
        _RVM1(0x1edc, 0, BIT2),   //reg[101edc]#2 = 0b
        //reg_3dflagconfig[1:0]
        _RVM1(0x1eb3, 0, BIT7 | BIT6),   //reg[101eb3]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_SPDIF_IN_IS_GPIO != GPIO_NONE)
        #define PAD_SPDIF_IN_OEN (PAD_SPDIF_IN_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_SPDIF_IN_OUT (PAD_SPDIF_IN_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b39, PAD_SPDIF_IN_OUT, BIT0),
        _RVM1(0x2b39, PAD_SPDIF_IN_OEN, BIT1),
        //reg_ej_config[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 0b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_spdifinconfig
        _RVM1(0x1eae, 0, BIT6),   //reg[101eae]#6 = 0b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 0b
        //reg_3dflagconfig[1:0]
        _RVM1(0x1eb3, 0, BIT7 | BIT6),   //reg[101eb3]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_SPDIF_OUT_IS_GPIO != GPIO_NONE)
        #define PAD_SPDIF_OUT_OEN (PAD_SPDIF_OUT_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_SPDIF_OUT_OUT (PAD_SPDIF_OUT_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b3a, PAD_SPDIF_OUT_OUT, BIT0),
        _RVM1(0x2b3a, PAD_SPDIF_OUT_OEN, BIT1),
        //reg_ej_config[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 0b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_spdifoutconfig
        _RVM1(0x1eae, 0, BIT7),   //reg[101eae]#7 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_I2S_OUT_WS_IS_GPIO != GPIO_NONE)
        #define PAD_I2S_OUT_WS_OEN (PAD_I2S_OUT_WS_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_I2S_OUT_WS_OUT (PAD_I2S_OUT_WS_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b3b, PAD_I2S_OUT_WS_OUT, BIT0),
        _RVM1(0x2b3b, PAD_I2S_OUT_WS_OEN, BIT1),
        //reg_ej_config[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 0b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_i2soutconfig0
        _RVM1(0x1eae, 0, BIT4),   //reg[101eae]#4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_I2S_OUT_MCK_IS_GPIO != GPIO_NONE)
        #define PAD_I2S_OUT_MCK_OEN (PAD_I2S_OUT_MCK_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_I2S_OUT_MCK_OUT (PAD_I2S_OUT_MCK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b3c, PAD_I2S_OUT_MCK_OUT, BIT0),
        _RVM1(0x2b3c, PAD_I2S_OUT_MCK_OEN, BIT1),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_i2soutconfig0
        _RVM1(0x1eae, 0, BIT4),   //reg[101eae]#4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_I2S_OUT_BCK_IS_GPIO != GPIO_NONE)
        #define PAD_I2S_OUT_BCK_OEN (PAD_I2S_OUT_BCK_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_I2S_OUT_BCK_OUT (PAD_I2S_OUT_BCK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b3d, PAD_I2S_OUT_BCK_OUT, BIT0),
        _RVM1(0x2b3d, PAD_I2S_OUT_BCK_OEN, BIT1),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_i2soutconfig0
        _RVM1(0x1eae, 0, BIT4),   //reg[101eae]#4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_I2S_OUT_SD_IS_GPIO != GPIO_NONE)
        #define PAD_I2S_OUT_SD_OEN (PAD_I2S_OUT_SD_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_I2S_OUT_SD_OUT (PAD_I2S_OUT_SD_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b3e, PAD_I2S_OUT_SD_OUT, BIT0),
        _RVM1(0x2b3e, PAD_I2S_OUT_SD_OEN, BIT1),
        //reg_ej_config[1:0]
        _RVM1(0x1e05, 0, BIT5 | BIT4),   //reg[101e05]#5 ~ #4 = 0b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_i2soutconfig1
        _RVM1(0x1eae, 0, BIT5),   //reg[101eae]#5 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_I2S_OUT_SD1_IS_GPIO != GPIO_NONE)
        #define PAD_I2S_OUT_SD1_OEN (PAD_I2S_OUT_SD1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_I2S_OUT_SD1_OUT (PAD_I2S_OUT_SD1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b3f, PAD_I2S_OUT_SD1_OUT, BIT0),
        _RVM1(0x2b3f, PAD_I2S_OUT_SD1_OEN, BIT1),
        //reg_i2soutconfig2
        _RVM1(0x1eb3, 0, BIT3),   //reg[101eb3]#3 = 0b
        //reg_mcujtagmode[1:0]
        //_RVM1(0x1ede, 0, BIT3 | BIT2),   //reg[101ede]#3 ~ #2 = 0b
        //reg_usbdrvvbusconfig[1:0]
        _RVM1(0x1e04, 0, BIT1 | BIT0),   //reg[101e04]#1 ~ #0 = 0b
        //reg_ext_int[7]
        _RVM1(0x1ea5, 0, BIT7),   //reg[101ea5]#7 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_I2S_OUT_SD2_IS_GPIO != GPIO_NONE)
        #define PAD_I2S_OUT_SD2_OEN (PAD_I2S_OUT_SD2_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_I2S_OUT_SD2_OUT (PAD_I2S_OUT_SD2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b40, PAD_I2S_OUT_SD2_OUT, BIT0),
        _RVM1(0x2b40, PAD_I2S_OUT_SD2_OEN, BIT1),
        //reg_i2soutconfig3
        _RVM1(0x1eb3, 0, BIT4),   //reg[101eb3]#4 = 0b
        //reg_mcujtagmode[1:0]
        //_RVM1(0x1ede, 0, BIT3 | BIT2),   //reg[101ede]#3 ~ #2 = 0b
        //reg_usbdrvvbusconfig[1:0]
        _RVM1(0x1e04, 0, BIT1 | BIT0),   //reg[101e04]#1 ~ #0 = 0b
        //reg_fourthuartmode[1:0]
        _RVM1(0x1e04, 0, BIT7 | BIT6),   //reg[101e04]#7 ~ #6 = 0b
        //reg_od4thuart[1:0]
        _RVM1(0x1ea9, 0, BIT5 | BIT4),   //reg[101ea9]#5 ~ #4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_I2S_OUT_SD3_IS_GPIO != GPIO_NONE)
        #define PAD_I2S_OUT_SD3_OEN (PAD_I2S_OUT_SD3_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_I2S_OUT_SD3_OUT (PAD_I2S_OUT_SD3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b41, PAD_I2S_OUT_SD3_OUT, BIT0),
        _RVM1(0x2b41, PAD_I2S_OUT_SD3_OEN, BIT1),
        //reg_i2soutconfig4
        _RVM1(0x1eb3, 0, BIT5),   //reg[101eb3]#5 = 0b
        //reg_mcujtagmode[1:0]
        //_RVM1(0x1ede, 0, BIT3 | BIT2),   //reg[101ede]#3 ~ #2 = 0b
        //reg_usbdrvvbusconfig[1:0]
        _RVM1(0x1e04, 0, BIT1 | BIT0),   //reg[101e04]#1 ~ #0 = 0b
        //reg_fourthuartmode[1:0]
        _RVM1(0x1e04, 0, BIT7 | BIT6),   //reg[101e04]#7 ~ #6 = 0b
        //reg_od4thuart[1:0]
        _RVM1(0x1ea9, 0, BIT5 | BIT4),   //reg[101ea9]#5 ~ #4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_VSYNC_Like_IS_GPIO != GPIO_NONE)
        #define PAD_VSYNC_Like_OEN (PAD_VSYNC_Like_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_VSYNC_Like_OUT (PAD_VSYNC_Like_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2bb0, PAD_VSYNC_Like_OUT, BIT0),
        _RVM1(0x2bb0, PAD_VSYNC_Like_OEN, BIT1),
        //reg_vsync_like_config[1:0]
        _RVM1(0x1eb4, 0, BIT7 | BIT6),   //reg[101eb4]#7 ~ #6 = 0b
        //reg_vsync_like_config[1:0]
        _RVM1(0x1eb4, 0, BIT7 | BIT6),   //reg[101eb4]#7 ~ #6 = 0b
        //reg_vsync_like_config[1:0]
        _RVM1(0x1eb4, 0, BIT7 | BIT6),   //reg[101eb4]#7 ~ #6 = 0b
        //reg_ext_int[1]
        _RVM1(0x1ea5, 0, BIT1),   //reg[101ea5]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_SPI1_CK_IS_GPIO != GPIO_NONE)
        #define PAD_SPI1_CK_OEN (PAD_SPI1_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_SPI1_CK_OUT (PAD_SPI1_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2bb1, PAD_SPI1_CK_OUT, BIT0),
        _RVM1(0x2bb1, PAD_SPI1_CK_OEN, BIT1),
        //reg_ld_spi1_config
        _RVM1(0x1eb4, 0, BIT0),   //reg[101eb4]#0 = 0b
        //reg_ld_spi3_config
        _RVM1(0x1eb4, 0, BIT2),   //reg[101eb4]#2 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb5, 0, BIT1 | BIT0),   //reg[101eb5]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_SPI1_DI_IS_GPIO != GPIO_NONE)
        #define PAD_SPI1_DI_OEN (PAD_SPI1_DI_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_SPI1_DI_OUT (PAD_SPI1_DI_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2bb2, PAD_SPI1_DI_OUT, BIT0),
        _RVM1(0x2bb2, PAD_SPI1_DI_OEN, BIT1),
        //reg_ld_spi1_config
        _RVM1(0x1eb4, 0, BIT0),   //reg[101eb4]#0 = 0b
        //reg_ld_spi3_config
        _RVM1(0x1eb4, 0, BIT2),   //reg[101eb4]#2 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb5, 0, BIT1 | BIT0),   //reg[101eb5]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_SPI2_CK_IS_GPIO != GPIO_NONE)
        #define PAD_SPI2_CK_OEN (PAD_SPI2_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_SPI2_CK_OUT (PAD_SPI2_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2bb3, PAD_SPI2_CK_OUT, BIT0),
        _RVM1(0x2bb3, PAD_SPI2_CK_OEN, BIT1),
        //reg_ld_spi2_config
        _RVM1(0x1eb4, 0, BIT1),   //reg[101eb4]#1 = 0b
        //reg_ld_spi3_config
        _RVM1(0x1eb4, 0, BIT2),   //reg[101eb4]#2 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_SPI2_DI_IS_GPIO != GPIO_NONE)
        #define PAD_SPI2_DI_OEN (PAD_SPI2_DI_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_SPI2_DI_OUT (PAD_SPI2_DI_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2bb4, PAD_SPI2_DI_OUT, BIT0),
        _RVM1(0x2bb4, PAD_SPI2_DI_OEN, BIT1),
        //reg_ld_spi2_config
        _RVM1(0x1eb4, 0, BIT1),   //reg[101eb4]#1 = 0b
        //reg_ld_spi3_config
        _RVM1(0x1eb4, 0, BIT2),   //reg[101eb4]#2 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_CEZ_IS_GPIO != GPIO_NONE)
        #define PAD_NAND_CEZ_OEN (PAD_NAND_CEZ_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_NAND_CEZ_OUT (PAD_NAND_CEZ_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b78, PAD_NAND_CEZ_OUT, BIT0),
        _RVM1(0x2b78, PAD_NAND_CEZ_OEN, BIT1),
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e21, BIT0, BIT0),   //reg[101e21] #0 = 1b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_emmc_config[1:0]
        _RVM1(0x1edc, 0, BIT7 | BIT6),   //reg[101edc]#7 ~ #6 = 0b
        //reg_force_hemcu_boot_from_emmc2
        _RVM1(0x1e20, 0, BIT1),   //reg[101e20]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_CEZ1_IS_GPIO != GPIO_NONE)
        #define PAD_NAND_CEZ1_OEN (PAD_NAND_CEZ1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_NAND_CEZ1_OUT (PAD_NAND_CEZ1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b79, PAD_NAND_CEZ1_OUT, BIT0),
        _RVM1(0x2b79, PAD_NAND_CEZ1_OEN, BIT1),
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e21, BIT0, BIT0),   //reg[101e21] #0 = 1b
        //reg_nand_cs1_en
        _RVM1(0x1ede, 0, BIT5),   //reg[101ede]#5 = 0b
        //reg_emmc_config[1:0]
        _RVM1(0x1edc, 0, BIT7 | BIT6),   //reg[101edc]#7 ~ #6 = 0b
        //reg_force_hemcu_boot_from_emmc2
        _RVM1(0x1e20, 0, BIT1),   //reg[101e20]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_CLE_IS_GPIO != GPIO_NONE)
        #define PAD_NAND_CLE_OEN (PAD_NAND_CLE_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_NAND_CLE_OUT (PAD_NAND_CLE_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b7a, PAD_NAND_CLE_OUT, BIT0),
        _RVM1(0x2b7a, PAD_NAND_CLE_OEN, BIT1),
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e21, BIT0, BIT0),   //reg[101e21] #0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_emmc_config[1:0]
        _RVM1(0x1edc, 0, BIT7 | BIT6),   //reg[101edc]#7 ~ #6 = 0b
        //reg_force_hemcu_boot_from_emmc2
        _RVM1(0x1e20, 0, BIT1),   //reg[101e20]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_REZ_IS_GPIO != GPIO_NONE)
        #define PAD_NAND_REZ_OEN (PAD_NAND_REZ_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_NAND_REZ_OUT (PAD_NAND_REZ_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b7b, PAD_NAND_REZ_OUT, BIT0),
        _RVM1(0x2b7b, PAD_NAND_REZ_OEN, BIT1),
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e21, BIT0, BIT0),   //reg[101e21] #0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_emmc_config[1:0]
        _RVM1(0x1edc, 0, BIT7 | BIT6),   //reg[101edc]#7 ~ #6 = 0b
        //reg_force_hemcu_boot_from_emmc2
        _RVM1(0x1e20, 0, BIT1),   //reg[101e20]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_WEZ_IS_GPIO != GPIO_NONE)
        #define PAD_NAND_WEZ_OEN (PAD_NAND_WEZ_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_NAND_WEZ_OUT (PAD_NAND_WEZ_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b7c, PAD_NAND_WEZ_OUT, BIT0),
        _RVM1(0x2b7c, PAD_NAND_WEZ_OEN, BIT1),
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e21, BIT0, BIT0),   //reg[101e21] #0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_emmc_config[1:0]
        _RVM1(0x1edc, 0, BIT7 | BIT6),   //reg[101edc]#7 ~ #6 = 0b
        //reg_force_hemcu_boot_from_emmc2
        _RVM1(0x1e20, 0, BIT1),   //reg[101e20]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_WPZ_IS_GPIO != GPIO_NONE)
        #define PAD_NAND_WPZ_OEN (PAD_NAND_WPZ_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_NAND_WPZ_OUT (PAD_NAND_WPZ_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b7d, PAD_NAND_WPZ_OUT, BIT0),
        _RVM1(0x2b7d, PAD_NAND_WPZ_OEN, BIT1),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_emmc_config[1:0]
        _RVM1(0x1edc, 0, BIT7 | BIT6),   //reg[101edc]#7 ~ #6 = 0b
        //reg_force_hemcu_boot_from_emmc2
        _RVM1(0x1e20, 0, BIT1),   //reg[101e20]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_ALE_IS_GPIO != GPIO_NONE)
        #define PAD_NAND_ALE_OEN (PAD_NAND_ALE_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_NAND_ALE_OUT (PAD_NAND_ALE_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b7e, PAD_NAND_ALE_OUT, BIT0),
        _RVM1(0x2b7e, PAD_NAND_ALE_OEN, BIT1),
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e21, BIT0, BIT0),   //reg[101e21] #0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_emmc_config[1:0]
        _RVM1(0x1edc, 0, BIT7 | BIT6),   //reg[101edc]#7 ~ #6 = 0b
        //reg_force_hemcu_boot_from_emmc2
        _RVM1(0x1e20, 0, BIT1),   //reg[101e20]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_RBZ_IS_GPIO != GPIO_NONE)
        #define PAD_NAND_RBZ_OEN (PAD_NAND_RBZ_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_NAND_RBZ_OUT (PAD_NAND_RBZ_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b7f, PAD_NAND_RBZ_OUT, BIT0),
        _RVM1(0x2b7f, PAD_NAND_RBZ_OEN, BIT1),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_emmc_config[1:0]
        _RVM1(0x1edc, 0, BIT7 | BIT6),   //reg[101edc]#7 ~ #6 = 0b
        //reg_force_hemcu_boot_from_emmc2
        _RVM1(0x1e20, 0, BIT1),   //reg[101e20]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_NAND_DQS_IS_GPIO != GPIO_NONE)
        #define PAD_NAND_DQS_OEN (PAD_NAND_DQS_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_NAND_DQS_OUT (PAD_NAND_DQS_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b80, PAD_NAND_DQS_OUT, BIT0),
        _RVM1(0x2b80, PAD_NAND_DQS_OEN, BIT1),
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM2_CE_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM2_CE_N_OEN (PAD_PCM2_CE_N_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM2_CE_N_OUT (PAD_PCM2_CE_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b63, PAD_PCM2_CE_N_OUT, BIT0),
        _RVM1(0x2b63, PAD_PCM2_CE_N_OEN, BIT1),
        //reg_pcm2ctrlconfig
        _RVM1(0x1ec8, 0, BIT3),   //reg[101ec8]#3 = 0b
        //reg_ext_int[0]
        _RVM1(0x1ea5, 0, BIT0),   //reg[101ea5]#0 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb5, 0, BIT1 | BIT0),   //reg[101eb5]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM2_IRQA_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM2_IRQA_N_OEN (PAD_PCM2_IRQA_N_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM2_IRQA_N_OUT (PAD_PCM2_IRQA_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b64, PAD_PCM2_IRQA_N_OUT, BIT0),
        _RVM1(0x2b64, PAD_PCM2_IRQA_N_OEN, BIT1),
        //reg_pcm2ctrlconfig
        _RVM1(0x1ec8, 0, BIT3),   //reg[101ec8]#3 = 0b
        //reg_usbdrvvbusconfig[1:0]
        _RVM1(0x1e04, 0, BIT1 | BIT0),   //reg[101e04]#1 ~ #0 = 0b
        //reg_ext_int[2]
        _RVM1(0x1ea5, 0, BIT2),   //reg[101ea5]#2 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb5, 0, BIT1 | BIT0),   //reg[101eb5]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM2_WAIT_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM2_WAIT_N_OEN (PAD_PCM2_WAIT_N_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM2_WAIT_N_OUT (PAD_PCM2_WAIT_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b65, PAD_PCM2_WAIT_N_OUT, BIT0),
        _RVM1(0x2b65, PAD_PCM2_WAIT_N_OEN, BIT1),
        //reg_pcm2ctrlconfig
        _RVM1(0x1ec8, 0, BIT3),   //reg[101ec8]#3 = 0b
        //reg_usbdrvvbusconfig[1:0]
        _RVM1(0x1e04, 0, BIT1 | BIT0),   //reg[101e04]#1 ~ #0 = 0b
        //reg_sd_config2[1:0]
        _RVM1(0x1eb5, 0, BIT3 | BIT2),   //reg[101eb5]#3 ~ #2 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM2_RESET_IS_GPIO != GPIO_NONE)
        #define PAD_PCM2_RESET_OEN (PAD_PCM2_RESET_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM2_RESET_OUT (PAD_PCM2_RESET_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b66, PAD_PCM2_RESET_OUT, BIT0),
        _RVM1(0x2b66, PAD_PCM2_RESET_OEN, BIT1),
        //reg_pcm2ctrlconfig
        _RVM1(0x1ec8, 0, BIT3),   //reg[101ec8]#3 = 0b
        //reg_usbdrvvbusconfig[1:0]
        _RVM1(0x1e04, 0, BIT1 | BIT0),   //reg[101e04]#1 ~ #0 = 0b
        //reg_sd_config2[1:0]
        _RVM1(0x1eb5, 0, BIT3 | BIT2),   //reg[101eb5]#3 ~ #2 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM2_CD_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM2_CD_N_OEN (PAD_PCM2_CD_N_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM2_CD_N_OUT (PAD_PCM2_CD_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b67, PAD_PCM2_CD_N_OUT, BIT0),
        _RVM1(0x2b67, PAD_PCM2_CD_N_OEN, BIT1),
        //reg_pcm_pe[33]
        _RVM1(0x1e16, BIT1, BIT1),   //reg[101e16]#1 = 1b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_pcm2ctrlconfig
        _RVM1(0x1ec8, 0, BIT3),   //reg[101ec8]#3 = 0b
        //reg_pcm2ctrlconfig_cd_n
        _RVM1(0x1e9e, 0, BIT0),   //reg[101e9e]#0 = 0b
        //reg_ext_int[3]
        _RVM1(0x1ea5, 0, BIT3),   //reg[101ea5]#3 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_D3_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_D3_OEN (PAD_PCM_D3_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_D3_OUT (PAD_PCM_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b42, PAD_PCM_D3_OUT, BIT0),
        _RVM1(0x2b42, PAD_PCM_D3_OEN, BIT1),
        //reg_pcm_pe[3]
        _RVM1(0x1e12, BIT3, BIT3),   //reg[101e12]#3 = 1b
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e21, BIT0, BIT0),   //reg[101e21] #0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_mcujtagmode[1:0]
        //_RVM1(0x1ede, 0, BIT3 | BIT2),   //reg[101ede]#3 ~ #2 = 0b
        //reg_emmc_config[1:0]
        _RVM1(0x1edc, 0, BIT7 | BIT6),   //reg[101edc]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_D4_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_D4_OEN (PAD_PCM_D4_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_D4_OUT (PAD_PCM_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b43, PAD_PCM_D4_OUT, BIT0),
        _RVM1(0x2b43, PAD_PCM_D4_OEN, BIT1),
        //reg_pcm_pe[4]
        _RVM1(0x1e12, BIT4, BIT4),   //reg[101e12]#4 = 1b
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e21, BIT0, BIT0),   //reg[101e21] #0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_mcujtagmode[1:0]
        //_RVM1(0x1ede, 0, BIT3 | BIT2),   //reg[101ede]#3 ~ #2 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb5, 0, BIT1 | BIT0),   //reg[101eb5]#1 ~ #0 = 0b
        //reg_sd_config2[1:0]
        _RVM1(0x1eb5, 0, BIT3 | BIT2),   //reg[101eb5]#3 ~ #2 = 0b
        //reg_emmc_config[1:0]
        _RVM1(0x1edc, 0, BIT7 | BIT6),   //reg[101edc]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_D5_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_D5_OEN (PAD_PCM_D5_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_D5_OUT (PAD_PCM_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b44, PAD_PCM_D5_OUT, BIT0),
        _RVM1(0x2b44, PAD_PCM_D5_OEN, BIT1),
        //reg_pcm_pe[5]
        _RVM1(0x1e12, BIT5, BIT5),   //reg[101e12]#5 = 1b
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e21, BIT0, BIT0),   //reg[101e21] #0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_mcujtagmode[1:0]
        //_RVM1(0x1ede, 0, BIT3 | BIT2),   //reg[101ede]#3 ~ #2 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb5, 0, BIT1 | BIT0),   //reg[101eb5]#1 ~ #0 = 0b
        //reg_sd_config2[1:0]
        _RVM1(0x1eb5, 0, BIT3 | BIT2),   //reg[101eb5]#3 ~ #2 = 0b
        //reg_emmc_config[1:0]
        _RVM1(0x1edc, 0, BIT7 | BIT6),   //reg[101edc]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_D6_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_D6_OEN (PAD_PCM_D6_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_D6_OUT (PAD_PCM_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b45, PAD_PCM_D6_OUT, BIT0),
        _RVM1(0x2b45, PAD_PCM_D6_OEN, BIT1),
        //reg_pcm_pe[6]
        _RVM1(0x1e12, BIT6, BIT6),   //reg[101e12]#6 = 1b
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e21, BIT0, BIT0),   //reg[101e21] #0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_mcujtagmode[1:0]
        //_RVM1(0x1ede, 0, BIT3 | BIT2),   //reg[101ede]#3 ~ #2 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb5, 0, BIT1 | BIT0),   //reg[101eb5]#1 ~ #0 = 0b
        //reg_sd_config2[1:0]
        _RVM1(0x1eb5, 0, BIT3 | BIT2),   //reg[101eb5]#3 ~ #2 = 0b
        //reg_emmc_config[1:0]
        _RVM1(0x1edc, 0, BIT7 | BIT6),   //reg[101edc]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_D7_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_D7_OEN (PAD_PCM_D7_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_D7_OUT (PAD_PCM_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b46, PAD_PCM_D7_OUT, BIT0),
        _RVM1(0x2b46, PAD_PCM_D7_OEN, BIT1),
        //reg_pcm_pe[7]
        _RVM1(0x1e12, BIT7, BIT7),   //reg[101e12]#7 = 1b
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e21, BIT0, BIT0),   //reg[101e21] #0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb5, 0, BIT1 | BIT0),   //reg[101eb5]#1 ~ #0 = 0b
        //reg_sd_config2[1:0]
        _RVM1(0x1eb5, 0, BIT3 | BIT2),   //reg[101eb5]#3 ~ #2 = 0b
        //reg_emmc_config[1:0]
        _RVM1(0x1edc, 0, BIT7 | BIT6),   //reg[101edc]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_CE_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_CE_N_OEN (PAD_PCM_CE_N_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_CE_N_OUT (PAD_PCM_CE_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b47, PAD_PCM_CE_N_OUT, BIT0),
        _RVM1(0x2b47, PAD_PCM_CE_N_OEN, BIT1),
        //reg_pcm_pe[8]
        _RVM1(0x1e13, BIT0, BIT0),   //reg[101e13]#0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_pcmctrlconfig
        _RVM1(0x1ec8, 0, BIT5),   //reg[101ec8]#5 = 0b
        //reg_cictrlconfig
        _RVM1(0x1ec8, 0, BIT1),   //reg[101ec8]#1 = 0b
        //reg_sm_config[1:0]
        _RVM1(0x1edc, 0, BIT5 | BIT4),   //reg[101edc]#5 ~ #4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A10_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A10_OEN (PAD_PCM_A10_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_A10_OUT (PAD_PCM_A10_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b48, PAD_PCM_A10_OUT, BIT0),
        _RVM1(0x2b48, PAD_PCM_A10_OEN, BIT1),
        //reg_pcm_pe[26]
        _RVM1(0x1e15, BIT2, BIT2),   //reg[101e15]#2 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_OE_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_OE_N_OEN (PAD_PCM_OE_N_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_OE_N_OUT (PAD_PCM_OE_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b49, PAD_PCM_OE_N_OUT, BIT0),
        _RVM1(0x2b49, PAD_PCM_OE_N_OEN, BIT1),
        //reg_pcm_pe[9]
        _RVM1(0x1e13, BIT1, BIT1),   //reg[101e13]#1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_pcmctrlconfig
        _RVM1(0x1ec8, 0, BIT5),   //reg[101ec8]#5 = 0b
        //reg_sm_config[1:0]
        _RVM1(0x1edc, 0, BIT5 | BIT4),   //reg[101edc]#5 ~ #4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A11_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A11_OEN (PAD_PCM_A11_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_A11_OUT (PAD_PCM_A11_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b4a, PAD_PCM_A11_OUT, BIT0),
        _RVM1(0x2b4a, PAD_PCM_A11_OEN, BIT1),
        //reg_pcm_pe[27]
        _RVM1(0x1e15, BIT3, BIT3),   //reg[101e15]#3 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_IORD_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_IORD_N_OEN (PAD_PCM_IORD_N_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_IORD_N_OUT (PAD_PCM_IORD_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b4b, PAD_PCM_IORD_N_OUT, BIT0),
        _RVM1(0x2b4b, PAD_PCM_IORD_N_OEN, BIT1),
        //reg_pcm_pe[10]
        _RVM1(0x1e13, BIT2, BIT2),   //reg[101e13]#2 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_pcmctrlconfig
        _RVM1(0x1ec8, 0, BIT5),   //reg[101ec8]#5 = 0b
        //reg_cictrlconfig
        _RVM1(0x1ec8, 0, BIT1),   //reg[101ec8]#1 = 0b
        //reg_sm_config[1:0]
        _RVM1(0x1edc, 0, BIT5 | BIT4),   //reg[101edc]#5 ~ #4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A9_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A9_OEN (PAD_PCM_A9_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_A9_OUT (PAD_PCM_A9_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b4c, PAD_PCM_A9_OUT, BIT0),
        _RVM1(0x2b4c, PAD_PCM_A9_OEN, BIT1),
        //reg_pcm_pe[25]
        _RVM1(0x1e15, BIT1, BIT1),   //reg[101e15]#1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_IOWR_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_IOWR_N_OEN (PAD_PCM_IOWR_N_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_IOWR_N_OUT (PAD_PCM_IOWR_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b4d, PAD_PCM_IOWR_N_OUT, BIT0),
        _RVM1(0x2b4d, PAD_PCM_IOWR_N_OEN, BIT1),
        //reg_pcm_pe[11]
        _RVM1(0x1e13, BIT3, BIT3),   //reg[101e13]#3 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_pcmctrlconfig
        _RVM1(0x1ec8, 0, BIT5),   //reg[101ec8]#5 = 0b
        //reg_cictrlconfig
        _RVM1(0x1ec8, 0, BIT1),   //reg[101ec8]#1 = 0b
        //reg_sm_config[1:0]
        _RVM1(0x1edc, 0, BIT5 | BIT4),   //reg[101edc]#5 ~ #4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A8_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A8_OEN (PAD_PCM_A8_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_A8_OUT (PAD_PCM_A8_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b4e, PAD_PCM_A8_OUT, BIT0),
        _RVM1(0x2b4e, PAD_PCM_A8_OEN, BIT1),
        //reg_pcm_pe[24]
        _RVM1(0x1e15, BIT0, BIT0),   //reg[101e15]#0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A13_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A13_OEN (PAD_PCM_A13_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_A13_OUT (PAD_PCM_A13_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b4f, PAD_PCM_A13_OUT, BIT0),
        _RVM1(0x2b4f, PAD_PCM_A13_OEN, BIT1),
        //reg_pcm_pe[29]
        _RVM1(0x1e15, BIT5, BIT5),   //reg[101e15]#5 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A14_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A14_OEN (PAD_PCM_A14_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_A14_OUT (PAD_PCM_A14_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b50, PAD_PCM_A14_OUT, BIT0),
        _RVM1(0x2b50, PAD_PCM_A14_OEN, BIT1),
        //reg_pcm_pe[30]
        _RVM1(0x1e15, BIT6, BIT6),   //reg[101e15]#6 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_WE_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_WE_N_OEN (PAD_PCM_WE_N_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_WE_N_OUT (PAD_PCM_WE_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b51, PAD_PCM_WE_N_OUT, BIT0),
        _RVM1(0x2b51, PAD_PCM_WE_N_OEN, BIT1),
        //reg_pcm_pe[12]
        _RVM1(0x1e13, BIT4, BIT4),   //reg[101e13]#4 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_pcmctrlconfig
        _RVM1(0x1ec8, 0, BIT5),   //reg[101ec8]#5 = 0b
        //reg_sm_config[1:0]
        _RVM1(0x1edc, 0, BIT5 | BIT4),   //reg[101edc]#5 ~ #4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_IRQA_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_IRQA_N_OEN (PAD_PCM_IRQA_N_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_IRQA_N_OUT (PAD_PCM_IRQA_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b52, PAD_PCM_IRQA_N_OUT, BIT0),
        _RVM1(0x2b52, PAD_PCM_IRQA_N_OEN, BIT1),
        //reg_pcm_pe[13]
        _RVM1(0x1e13, BIT5, BIT5),   //reg[101e13]#5 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_pcmctrlconfig
        _RVM1(0x1ec8, 0, BIT5),   //reg[101ec8]#5 = 0b
        //reg_cictrlconfig
        _RVM1(0x1ec8, 0, BIT1),   //reg[101ec8]#1 = 0b
        //reg_sm_config[1:0]
        _RVM1(0x1edc, 0, BIT5 | BIT4),   //reg[101edc]#5 ~ #4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A12_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A12_OEN (PAD_PCM_A12_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_A12_OUT (PAD_PCM_A12_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b53, PAD_PCM_A12_OUT, BIT0),
        _RVM1(0x2b53, PAD_PCM_A12_OEN, BIT1),
        //reg_pcm_pe[28]
        _RVM1(0x1e15, BIT4, BIT4),   //reg[101e15]#4 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A7_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A7_OEN (PAD_PCM_A7_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_A7_OUT (PAD_PCM_A7_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b54, PAD_PCM_A7_OUT, BIT0),
        _RVM1(0x2b54, PAD_PCM_A7_OEN, BIT1),
        //reg_pcm_pe[23]
        _RVM1(0x1e14, BIT7, BIT7),   //reg[101e14]#7 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A6_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A6_OEN (PAD_PCM_A6_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_A6_OUT (PAD_PCM_A6_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b55, PAD_PCM_A6_OUT, BIT0),
        _RVM1(0x2b55, PAD_PCM_A6_OEN, BIT1),
        //reg_pcm_pe[22]
        _RVM1(0x1e14, BIT6, BIT6),   //reg[101e14]#6 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A5_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A5_OEN (PAD_PCM_A5_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_A5_OUT (PAD_PCM_A5_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b56, PAD_PCM_A5_OUT, BIT0),
        _RVM1(0x2b56, PAD_PCM_A5_OEN, BIT1),
        //reg_pcm_pe[21]
        _RVM1(0x1e14, BIT5, BIT5),   //reg[101e14]#5 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_WAIT_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_WAIT_N_OEN (PAD_PCM_WAIT_N_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_WAIT_N_OUT (PAD_PCM_WAIT_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b57, PAD_PCM_WAIT_N_OUT, BIT0),
        _RVM1(0x2b57, PAD_PCM_WAIT_N_OEN, BIT1),
        //reg_pcm_pe[14]
        _RVM1(0x1e13, BIT6, BIT6),   //reg[101e13]#6 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_pcmctrlconfig
        _RVM1(0x1ec8, 0, BIT5),   //reg[101ec8]#5 = 0b
        //reg_cictrlconfig
        _RVM1(0x1ec8, 0, BIT1),   //reg[101ec8]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A4_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A4_OEN (PAD_PCM_A4_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_A4_OUT (PAD_PCM_A4_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b58, PAD_PCM_A4_OUT, BIT0),
        _RVM1(0x2b58, PAD_PCM_A4_OEN, BIT1),
        //reg_pcm_pe[20]
        _RVM1(0x1e14, BIT4, BIT4),   //reg[101e14]#4 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A3_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A3_OEN (PAD_PCM_A3_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_A3_OUT (PAD_PCM_A3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b59, PAD_PCM_A3_OUT, BIT0),
        _RVM1(0x2b59, PAD_PCM_A3_OEN, BIT1),
        //reg_pcm_pe[19]
        _RVM1(0x1e14, BIT3, BIT3),   //reg[101e14]#3 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A2_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A2_OEN (PAD_PCM_A2_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_A2_OUT (PAD_PCM_A2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b5a, PAD_PCM_A2_OUT, BIT0),
        _RVM1(0x2b5a, PAD_PCM_A2_OEN, BIT1),
        //reg_pcm_pe[18]
        _RVM1(0x1e14, BIT2, BIT2),   //reg[101e14]#2 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_REG_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_REG_N_OEN (PAD_PCM_REG_N_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_REG_N_OUT (PAD_PCM_REG_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b5b, PAD_PCM_REG_N_OUT, BIT0),
        _RVM1(0x2b5b, PAD_PCM_REG_N_OEN, BIT1),
        //reg_pcm_pe[15]
        _RVM1(0x1e13, BIT7, BIT7),   //reg[101e13]#7 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_pcmctrlconfig
        _RVM1(0x1ec8, 0, BIT5),   //reg[101ec8]#5 = 0b
        //reg_cictrlconfig
        _RVM1(0x1ec8, 0, BIT1),   //reg[101ec8]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A1_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A1_OEN (PAD_PCM_A1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_A1_OUT (PAD_PCM_A1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b5c, PAD_PCM_A1_OUT, BIT0),
        _RVM1(0x2b5c, PAD_PCM_A1_OEN, BIT1),
        //reg_pcm_pe[17]
        _RVM1(0x1e14, BIT1, BIT1),   //reg[101e14]#1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_A0_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_A0_OEN (PAD_PCM_A0_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_A0_OUT (PAD_PCM_A0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b5d, PAD_PCM_A0_OUT, BIT0),
        _RVM1(0x2b5d, PAD_PCM_A0_OEN, BIT1),
        //reg_pcm_pe[16]
        _RVM1(0x1e14, BIT0, BIT0),   //reg[101e14]#0 = 1b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_D0_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_D0_OEN (PAD_PCM_D0_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_D0_OUT (PAD_PCM_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b5e, PAD_PCM_D0_OUT, BIT0),
        _RVM1(0x2b5e, PAD_PCM_D0_OEN, BIT1),
        //reg_pcm_pe[0]
        _RVM1(0x1e12, BIT0, BIT0),   //reg[101e12]#0 = 1b
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e21, BIT0, BIT0),   //reg[101e21] #0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_emmc_config[1:0]
        _RVM1(0x1edc, 0, BIT7 | BIT6),   //reg[101edc]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_D1_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_D1_OEN (PAD_PCM_D1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_D1_OUT (PAD_PCM_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b5f, PAD_PCM_D1_OUT, BIT0),
        _RVM1(0x2b5f, PAD_PCM_D1_OEN, BIT1),
        //reg_pcm_pe[1]
        _RVM1(0x1e12, BIT1, BIT1),   //reg[101e12]#1 = 1b
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e21, BIT0, BIT0),   //reg[101e21] #0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_emmc_config[1:0]
        _RVM1(0x1edc, 0, BIT7 | BIT6),   //reg[101edc]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_D2_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_D2_OEN (PAD_PCM_D2_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_D2_OUT (PAD_PCM_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b60, PAD_PCM_D2_OUT, BIT0),
        _RVM1(0x2b60, PAD_PCM_D2_OEN, BIT1),
        //reg_pcm_pe[2]
        _RVM1(0x1e12, BIT2, BIT2),   //reg[101e12]#2 = 1b
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e21, BIT0, BIT0),   //reg[101e21] #0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_pcmadconfig
        _RVM1(0x1ec8, 0, BIT4),   //reg[101ec8]#4 = 0b
        //reg_ciadconfig
        _RVM1(0x1ec8, 0, BIT0),   //reg[101ec8]#0 = 0b
        //reg_emmc_config[1:0]
        _RVM1(0x1edc, 0, BIT7 | BIT6),   //reg[101edc]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_RESET_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_RESET_OEN (PAD_PCM_RESET_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_RESET_OUT (PAD_PCM_RESET_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b61, PAD_PCM_RESET_OUT, BIT0),
        _RVM1(0x2b61, PAD_PCM_RESET_OEN, BIT1),
        //reg_pcm_pe[31]
        _RVM1(0x1e15, BIT7, BIT7),   //reg[101e15]#7 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_pcmctrlconfig
        _RVM1(0x1ec8, 0, BIT5),   //reg[101ec8]#5 = 0b
        //reg_cictrlconfig
        _RVM1(0x1ec8, 0, BIT1),   //reg[101ec8]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PCM_CD_N_IS_GPIO != GPIO_NONE)
        #define PAD_PCM_CD_N_OEN (PAD_PCM_CD_N_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PCM_CD_N_OUT (PAD_PCM_CD_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b62, PAD_PCM_CD_N_OUT, BIT0),
        _RVM1(0x2b62, PAD_PCM_CD_N_OEN, BIT1),
        //reg_pcm_pe[32]
        _RVM1(0x1e16, BIT0, BIT0),   //reg[101e16]#0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_pcmctrlconfig
        _RVM1(0x1ec8, 0, BIT5),   //reg[101ec8]#5 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PWM0_IS_GPIO != GPIO_NONE)
        #define PAD_PWM0_OEN (PAD_PWM0_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PWM0_OUT (PAD_PWM0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b88, PAD_PWM0_OUT, BIT0),
        _RVM1(0x2b88, PAD_PWM0_OEN, BIT1),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_pwm0_mode
        _RVM1(0x1ec8, 0, BIT2),   //reg[101ec8]#2 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PWM1_IS_GPIO != GPIO_NONE)
        #define PAD_PWM1_OEN (PAD_PWM1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PWM1_OUT (PAD_PWM1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b89, PAD_PWM1_OUT, BIT0),
        _RVM1(0x2b89, PAD_PWM1_OEN, BIT1),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_pwm1_mode
        _RVM1(0x1ec8, 0, BIT6),   //reg[101ec8]#6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PWM2_IS_GPIO != GPIO_NONE)
        #define PAD_PWM2_OEN (PAD_PWM2_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PWM2_OUT (PAD_PWM2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b8a, PAD_PWM2_OUT, BIT0),
        _RVM1(0x2b8a, PAD_PWM2_OEN, BIT1),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_pwm2_mode
        _RVM1(0x1ec8, 0, BIT7),   //reg[101ec8]#7 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PWM3_IS_GPIO != GPIO_NONE)
        #define PAD_PWM3_OEN (PAD_PWM3_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PWM3_OUT (PAD_PWM3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b8b, PAD_PWM3_OUT, BIT0),
        _RVM1(0x2b8b, PAD_PWM3_OEN, BIT1),
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_pwm3_mode
        _RVM1(0x1ec9, 0, BIT4),   //reg[101ec9]#4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PWM4_IS_GPIO != GPIO_NONE)
        #define PAD_PWM4_OEN (PAD_PWM4_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PWM4_OUT (PAD_PWM4_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b8c, PAD_PWM4_OUT, BIT0),
        _RVM1(0x2b8c, PAD_PWM4_OEN, BIT1),
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_i2smutemode[1:0]
        _RVM1(0x1e05, 0, BIT7 | BIT6),   //reg[101e05]#7 ~ #6 = 0b
        //reg_pwm4_mode
        _RVM1(0x1ec9, 0, BIT5),   //reg[101ec9]#5 = 0b
        //reg_tserrout[1:0]
        _RVM1(0x1ec9, 0, BIT1 | BIT0),   //reg[101ec9]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PWM5_IS_GPIO != GPIO_NONE)
        #define PAD_PWM5_OEN (PAD_PWM5_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PWM5_OUT (PAD_PWM5_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2bb7, PAD_PWM5_OUT, BIT0),
        _RVM1(0x2bb7, PAD_PWM5_OEN, BIT1),
        //reg_pwm0_dim_mode
        _RVM1(0x1eef, 0, BIT0),   //reg[101eef]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PWM6_IS_GPIO != GPIO_NONE)
        #define PAD_PWM6_OEN (PAD_PWM6_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PWM6_OUT (PAD_PWM6_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2bb8, PAD_PWM6_OUT, BIT0),
        _RVM1(0x2bb8, PAD_PWM6_OEN, BIT1),
        //reg_pwm1_dim_mode
        _RVM1(0x1eef, 0, BIT1),   //reg[101eef]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PWM7_IS_GPIO != GPIO_NONE)
        #define PAD_PWM7_OEN (PAD_PWM7_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PWM7_OUT (PAD_PWM7_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2bbb, PAD_PWM7_OUT, BIT0),
        _RVM1(0x2bbb, PAD_PWM7_OEN, BIT1),
        //reg_pwm2_dim_mode
        _RVM1(0x1eef, 0, BIT2),   //reg[101eef]#2 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PWM8_IS_GPIO != GPIO_NONE)
        #define PAD_PWM8_OEN (PAD_PWM8_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PWM8_OUT (PAD_PWM8_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2bbc, PAD_PWM8_OUT, BIT0),
        _RVM1(0x2bbc, PAD_PWM8_OEN, BIT1),
        //reg_pwm3_dim_mode
        _RVM1(0x1eef, 0, BIT3),   //reg[101eef]#3 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PWM9_IS_GPIO != GPIO_NONE)
        #define PAD_PWM9_OEN (PAD_PWM9_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PWM9_OUT (PAD_PWM9_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2bbf, PAD_PWM9_OUT, BIT0),
        _RVM1(0x2bbf, PAD_PWM9_OEN, BIT1),
        //reg_pwm4_dim_mode
        _RVM1(0x1eef, 0, BIT4),   //reg[101eef]#4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PWM10_IS_GPIO != GPIO_NONE)
        #define PAD_PWM10_OEN (PAD_PWM10_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PWM10_OUT (PAD_PWM10_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2bc0, PAD_PWM10_OUT, BIT0),
        _RVM1(0x2bc0, PAD_PWM10_OEN, BIT1),
        //reg_pwm5_dim_mode
        _RVM1(0x1eef, 0, BIT5),   //reg[101eef]#5 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PWM11_IS_GPIO != GPIO_NONE)
        #define PAD_PWM11_OEN (PAD_PWM11_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PWM11_OUT (PAD_PWM11_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2bc1, PAD_PWM11_OUT, BIT0),
        _RVM1(0x2bc1, PAD_PWM11_OEN, BIT1),
        //reg_pwm6_dim_mode
        _RVM1(0x1eef, 0, BIT6),   //reg[101eef]#6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_PWM12_IS_GPIO != GPIO_NONE)
        #define PAD_PWM12_OEN (PAD_PWM12_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_PWM12_OUT (PAD_PWM12_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2bc2, PAD_PWM12_OUT, BIT0),
        _RVM1(0x2bc2, PAD_PWM12_OEN, BIT1),
        //reg_pwm7_dim_mode
        _RVM1(0x1eef, 0, BIT7),   //reg[101eef]#7 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_EMMC_RSTN_IS_GPIO != GPIO_NONE)
        #define PAD_EMMC_RSTN_OEN (PAD_EMMC_RSTN_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_EMMC_RSTN_OUT (PAD_EMMC_RSTN_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2bac, PAD_EMMC_RSTN_OUT, BIT0),
        _RVM1(0x2bac, PAD_EMMC_RSTN_OEN, BIT1),
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e21, BIT0, BIT0),   //reg[101e21] #0 = 1b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_emmc_rstn_en
        _RVM1(0x1e86, 0, BIT0),   //reg[101e86] #0 = 0b
        //reg_emmc_config[1:0]
        _RVM1(0x1edc, 0, BIT7 | BIT6),   //reg[101edc]#7 ~ #6 = 0b
        //reg_force_hemcu_boot_from_emmc2
        _RVM1(0x1e20, 0, BIT1),   //reg[101e20]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_EMMC_CLK_IS_GPIO != GPIO_NONE)
        #define PAD_EMMC_CLK_OEN (PAD_EMMC_CLK_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_EMMC_CLK_OUT (PAD_EMMC_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2bad, PAD_EMMC_CLK_OUT, BIT0),
        _RVM1(0x2bad, PAD_EMMC_CLK_OEN, BIT1),
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e21, BIT0, BIT0),   //reg[101e21] #0 = 1b
        //reg_sd_use_bypass
        _RVM1(0x1e80, 0, BIT0),   //reg[101e80] #0 = 0b
        //reg_ds_testen
        //_RVM1(0x1359, 0, BIT6),   //reg[111359] #6 = 0b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_emmc_config[1:0]
        _RVM1(0x1edc, 0, BIT7 | BIT6),   //reg[101edc]#7 ~ #6 = 0b
        //reg_force_hemcu_boot_from_emmc2
        _RVM1(0x1e20, 0, BIT1),   //reg[101e20]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_EMMC_CMD_IS_GPIO != GPIO_NONE)
        #define PAD_EMMC_CMD_OEN (PAD_EMMC_CMD_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_EMMC_CMD_OUT (PAD_EMMC_CMD_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2bae, PAD_EMMC_CMD_OUT, BIT0),
        _RVM1(0x2bae, PAD_EMMC_CMD_OEN, BIT1),
        //reg_fcie2macro_sd_bypass
        _RVM1(0x1e21, BIT0, BIT0),   //reg[101e21] #0 = 1b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_emmc_config[1:0]
        _RVM1(0x1edc, 0, BIT7 | BIT6),   //reg[101edc]#7 ~ #6 = 0b
        //reg_force_hemcu_boot_from_emmc2
        _RVM1(0x1e20, 0, BIT1),   //reg[101e20]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON0_IS_GPIO != GPIO_NONE)
        #define PAD_TCON0_OEN (PAD_TCON0_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON0_OUT (PAD_TCON0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b93, PAD_TCON0_OUT, BIT0),
        _RVM1(0x2b93, PAD_TCON0_OEN, BIT1),
        //reg_tconconfig[0]
        _RVM1(0x1ea0, 0, BIT0),   //reg[101ea0]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON1_IS_GPIO != GPIO_NONE)
        #define PAD_TCON1_OEN (PAD_TCON1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON1_OUT (PAD_TCON1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b92, PAD_TCON1_OUT, BIT0),
        _RVM1(0x2b92, PAD_TCON1_OEN, BIT1),
        //reg_tconconfig[1]
        _RVM1(0x1ea0, 0, BIT1),   //reg[101ea0]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON2_IS_GPIO != GPIO_NONE)
        #define PAD_TCON2_OEN (PAD_TCON2_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON2_OUT (PAD_TCON2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b95, PAD_TCON2_OUT, BIT0),
        _RVM1(0x2b95, PAD_TCON2_OEN, BIT1),
        //reg_tconconfig[2]
        _RVM1(0x1ea0, 0, BIT2),   //reg[101ea0]#2 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON3_IS_GPIO != GPIO_NONE)
        #define PAD_TCON3_OEN (PAD_TCON3_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON3_OUT (PAD_TCON3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b94, PAD_TCON3_OUT, BIT0),
        _RVM1(0x2b94, PAD_TCON3_OEN, BIT1),
        //reg_tconconfig[3]
        _RVM1(0x1ea0, 0, BIT3),   //reg[101ea0]#3 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON4_IS_GPIO != GPIO_NONE)
        #define PAD_TCON4_OEN (PAD_TCON4_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON4_OUT (PAD_TCON4_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b97, PAD_TCON4_OUT, BIT0),
        _RVM1(0x2b97, PAD_TCON4_OEN, BIT1),
        //reg_tconconfig[4]
        _RVM1(0x1ea0, 0, BIT4),   //reg[101ea0]#4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON5_IS_GPIO != GPIO_NONE)
        #define PAD_TCON5_OEN (PAD_TCON5_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON5_OUT (PAD_TCON5_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b96, PAD_TCON5_OUT, BIT0),
        _RVM1(0x2b96, PAD_TCON5_OEN, BIT1),
        //reg_tconconfig[5]
        _RVM1(0x1ea0, 0, BIT5),   //reg[101ea0]#5 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON6_IS_GPIO != GPIO_NONE)
        #define PAD_TCON6_OEN (PAD_TCON6_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON6_OUT (PAD_TCON6_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b99, PAD_TCON6_OUT, BIT0),
        _RVM1(0x2b99, PAD_TCON6_OEN, BIT1),
        //reg_tconconfig[6]
        _RVM1(0x1ea0, 0, BIT6),   //reg[101ea0]#6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON7_IS_GPIO != GPIO_NONE)
        #define PAD_TCON7_OEN (PAD_TCON7_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON7_OUT (PAD_TCON7_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b98, PAD_TCON7_OUT, BIT0),
        _RVM1(0x2b98, PAD_TCON7_OEN, BIT1),
        //reg_tconconfig[7]
        _RVM1(0x1ea0, 0, BIT7),   //reg[101ea0]#7 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON8_IS_GPIO != GPIO_NONE)
        #define PAD_TCON8_OEN (PAD_TCON8_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON8_OUT (PAD_TCON8_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b9b, PAD_TCON8_OUT, BIT0),
        _RVM1(0x2b9b, PAD_TCON8_OEN, BIT1),
        //reg_tconconfig[8]
        _RVM1(0x1ea1, 0, BIT0),   //reg[101ea1]#0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON9_IS_GPIO != GPIO_NONE)
        #define PAD_TCON9_OEN (PAD_TCON9_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON9_OUT (PAD_TCON9_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b9a, PAD_TCON9_OUT, BIT0),
        _RVM1(0x2b9a, PAD_TCON9_OEN, BIT1),
        //reg_tconconfig[9]
        _RVM1(0x1ea1, 0, BIT1),   //reg[101ea1]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON10_IS_GPIO != GPIO_NONE)
        #define PAD_TCON10_OEN (PAD_TCON10_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON10_OUT (PAD_TCON10_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b9d, PAD_TCON10_OUT, BIT0),
        _RVM1(0x2b9d, PAD_TCON10_OEN, BIT1),
        //reg_tconconfig[10]
        _RVM1(0x1ea1, 0, BIT2),   //reg[101ea1]#2 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON11_IS_GPIO != GPIO_NONE)
        #define PAD_TCON11_OEN (PAD_TCON11_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON11_OUT (PAD_TCON11_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b9c, PAD_TCON11_OUT, BIT0),
        _RVM1(0x2b9c, PAD_TCON11_OEN, BIT1),
        //reg_tconconfig[11]
        _RVM1(0x1ea1, 0, BIT3),   //reg[101ea1]#3 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON12_IS_GPIO != GPIO_NONE)
        #define PAD_TCON12_OEN (PAD_TCON12_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON12_OUT (PAD_TCON12_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b9f, PAD_TCON12_OUT, BIT0),
        _RVM1(0x2b9f, PAD_TCON12_OEN, BIT1),
        //reg_tconconfig[12]
        _RVM1(0x1ea1, 0, BIT4),   //reg[101ea1]#4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON13_IS_GPIO != GPIO_NONE)
        #define PAD_TCON13_OEN (PAD_TCON13_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON13_OUT (PAD_TCON13_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b9e, PAD_TCON13_OUT, BIT0),
        _RVM1(0x2b9e, PAD_TCON13_OEN, BIT1),
        //reg_tconconfig[13]
        _RVM1(0x1ea1, 0, BIT5),   //reg[101ea1]#5 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON14_IS_GPIO != GPIO_NONE)
        #define PAD_TCON14_OEN (PAD_TCON14_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON14_OUT (PAD_TCON14_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2bb5, PAD_TCON14_OUT, BIT0),
        _RVM1(0x2bb5, PAD_TCON14_OEN, BIT1),
        //reg_ld_spi4_config
        _RVM1(0x1eb4, 0, BIT3),   //reg[101eb4]#3 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TCON15_IS_GPIO != GPIO_NONE)
        #define PAD_TCON15_OEN (PAD_TCON15_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TCON15_OUT (PAD_TCON15_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2bb6, PAD_TCON15_OUT, BIT0),
        _RVM1(0x2bb6, PAD_TCON15_OEN, BIT1),
        //reg_osdflagconfig[1:0]
        _RVM1(0x1eb5, 0, BIT5 | BIT4),   //reg[101eb5]#5~#4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TGPIO0_IS_GPIO != GPIO_NONE)
        #define PAD_TGPIO0_OEN (PAD_TGPIO0_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TGPIO0_OUT (PAD_TGPIO0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b8d, PAD_TGPIO0_OUT, BIT0),
        _RVM1(0x2b8d, PAD_TGPIO0_OEN, BIT1),
        //reg_vsync_vif_out_en
        _RVM1(0x1ea3, 0, BIT6),   //reg[101ea3]#6 = 0b
        //reg_mcujtagmode[1:0]
        //_RVM1(0x1ede, 0, BIT3 | BIT2),   //reg[101ede]#3 ~ #2 = 0b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TGPIO1_IS_GPIO != GPIO_NONE)
        #define PAD_TGPIO1_OEN (PAD_TGPIO1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TGPIO1_OUT (PAD_TGPIO1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b8e, PAD_TGPIO1_OUT, BIT0),
        _RVM1(0x2b8e, PAD_TGPIO1_OEN, BIT1),
        //reg_mcujtagmode[1:0]
        //_RVM1(0x1ede, 0, BIT3 | BIT2),   //reg[101ede]#3 ~ #2 = 0b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TGPIO2_IS_GPIO != GPIO_NONE)
        #define PAD_TGPIO2_OEN (PAD_TGPIO2_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TGPIO2_OUT (PAD_TGPIO2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b8f, PAD_TGPIO2_OUT, BIT0),
        _RVM1(0x2b8f, PAD_TGPIO2_OEN, BIT1),
        //reg_mcujtagmode[1:0]
        //_RVM1(0x1ede, 0, BIT3 | BIT2),   //reg[101ede]#3 ~ #2 = 0b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 0b
        //reg_miic_mode1
        _RVM1(0x1edc, 0, BIT1),   //reg[101edc]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TGPIO3_IS_GPIO != GPIO_NONE)
        #define PAD_TGPIO3_OEN (PAD_TGPIO3_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TGPIO3_OUT (PAD_TGPIO3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b90, PAD_TGPIO3_OUT, BIT0),
        _RVM1(0x2b90, PAD_TGPIO3_OEN, BIT1),
        //reg_mcujtagmode[1:0]
        //_RVM1(0x1ede, 0, BIT3 | BIT2),   //reg[101ede]#3 ~ #2 = 0b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 0b
        //reg_miic_mode1
        _RVM1(0x1edc, 0, BIT1),   //reg[101edc]#1 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_D0_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_D0_OEN (PAD_TS0_D0_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS0_D0_OUT (PAD_TS0_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b1c, PAD_TS0_D0_OUT, BIT0),
        _RVM1(0x2b1c, PAD_TS0_D0_OEN, BIT1),
        //reg_ts0_pe[0]
        _RVM1(0x1e1e, BIT0, BIT0),   //reg[101e1e]#0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_ts0config[1:0]
        _RVM1(0x1eaf, 0, BIT1 | BIT0),   //reg[101eaf]#1 ~ #0 = 0b
        //reg_ts2config
        _RVM1(0x1eaf, 0, BIT7 | BIT6),   //reg[101eaf]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_D1_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_D1_OEN (PAD_TS0_D1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS0_D1_OUT (PAD_TS0_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b1d, PAD_TS0_D1_OUT, BIT0),
        _RVM1(0x2b1d, PAD_TS0_D1_OEN, BIT1),
        //reg_ts0_pe[1]
        _RVM1(0x1e1e, BIT1, BIT1),   //reg[101e1e]#1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_ts0config[1:0]
        _RVM1(0x1eaf, 0, BIT1 | BIT0),   //reg[101eaf]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_D2_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_D2_OEN (PAD_TS0_D2_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS0_D2_OUT (PAD_TS0_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b1e, PAD_TS0_D2_OUT, BIT0),
        _RVM1(0x2b1e, PAD_TS0_D2_OEN, BIT1),
        //reg_ts0_pe[2]
        _RVM1(0x1e1e, BIT2, BIT2),   //reg[101e1e]#2 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_ts0config[1:0]
        _RVM1(0x1eaf, 0, BIT1 | BIT0),   //reg[101eaf]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_D3_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_D3_OEN (PAD_TS0_D3_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS0_D3_OUT (PAD_TS0_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b1f, PAD_TS0_D3_OUT, BIT0),
        _RVM1(0x2b1f, PAD_TS0_D3_OEN, BIT1),
        //reg_ts0_pe[3]
        _RVM1(0x1e1e, BIT3, BIT3),   //reg[101e1e]#3 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_ts0config[1:0]
        _RVM1(0x1eaf, 0, BIT1 | BIT0),   //reg[101eaf]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_D4_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_D4_OEN (PAD_TS0_D4_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS0_D4_OUT (PAD_TS0_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b20, PAD_TS0_D4_OUT, BIT0),
        _RVM1(0x2b20, PAD_TS0_D4_OEN, BIT1),
        //reg_ts0_pe[4]
        _RVM1(0x1e1e, BIT4, BIT4),   //reg[101e1e]#4 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_ts0config[1:0]
        _RVM1(0x1eaf, 0, BIT1 | BIT0),   //reg[101eaf]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_D5_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_D5_OEN (PAD_TS0_D5_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS0_D5_OUT (PAD_TS0_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b21, PAD_TS0_D5_OUT, BIT0),
        _RVM1(0x2b21, PAD_TS0_D5_OEN, BIT1),
        //reg_ts0_pe[5]
        _RVM1(0x1e1e, BIT5, BIT5),   //reg[101e1e]#5 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_ts0config[1:0]
        _RVM1(0x1eaf, 0, BIT1 | BIT0),   //reg[101eaf]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_D6_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_D6_OEN (PAD_TS0_D6_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS0_D6_OUT (PAD_TS0_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b22, PAD_TS0_D6_OUT, BIT0),
        _RVM1(0x2b22, PAD_TS0_D6_OEN, BIT1),
        //reg_ts0_pe[6]
        _RVM1(0x1e1e, BIT6, BIT6),   //reg[101e1e]#6 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_ts0config[1:0]
        _RVM1(0x1eaf, 0, BIT1 | BIT0),   //reg[101eaf]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_D7_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_D7_OEN (PAD_TS0_D7_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS0_D7_OUT (PAD_TS0_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b23, PAD_TS0_D7_OUT, BIT0),
        _RVM1(0x2b23, PAD_TS0_D7_OEN, BIT1),
        //reg_ts0_pe[7]
        _RVM1(0x1e1e, BIT7, BIT7),   //reg[101e1e]#7 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_ts0config[1:0]
        _RVM1(0x1eaf, 0, BIT1 | BIT0),   //reg[101eaf]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_VLD_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_VLD_OEN (PAD_TS0_VLD_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS0_VLD_OUT (PAD_TS0_VLD_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b24, PAD_TS0_VLD_OUT, BIT0),
        _RVM1(0x2b24, PAD_TS0_VLD_OEN, BIT1),
        //reg_ts0_pe[8]
        _RVM1(0x1e1f, BIT0, BIT0),   //reg[101e1f]#0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_ts0config[1:0]
        _RVM1(0x1eaf, 0, BIT1 | BIT0),   //reg[101eaf]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_SYNC_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_SYNC_OEN (PAD_TS0_SYNC_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS0_SYNC_OUT (PAD_TS0_SYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b25, PAD_TS0_SYNC_OUT, BIT0),
        _RVM1(0x2b25, PAD_TS0_SYNC_OEN, BIT1),
        //reg_ts0_pe[9]
        _RVM1(0x1e1f, BIT1, BIT1),   //reg[101e1f]#1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_ts0config[1:0]
        _RVM1(0x1eaf, 0, BIT1 | BIT0),   //reg[101eaf]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS0_CLK_IS_GPIO != GPIO_NONE)
        #define PAD_TS0_CLK_OEN (PAD_TS0_CLK_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS0_CLK_OUT (PAD_TS0_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b26, PAD_TS0_CLK_OUT, BIT0),
        _RVM1(0x2b26, PAD_TS0_CLK_OEN, BIT1),
        //reg_ts0_pe[10]
        _RVM1(0x1e1f, BIT2, BIT2),   //reg[101e1f]#2 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_test_out_mode[2:0]
        //_RVM1(0x1e24, 0, BIT6 | BIT5 | BIT4),   //reg[101e24]#6 ~ #4 = 00b
        //reg_ts0config[1:0]
        _RVM1(0x1eaf, 0, BIT1 | BIT0),   //reg[101eaf]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_CLK_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_CLK_OEN (PAD_TS1_CLK_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS1_CLK_OUT (PAD_TS1_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b27, PAD_TS1_CLK_OUT, BIT0),
        _RVM1(0x2b27, PAD_TS1_CLK_OEN, BIT1),
        //reg_ts1_pe[10]
        _RVM1(0x1e0d, BIT2, BIT2),   //reg[101e0d]#2 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_ts1config[1:0]
        _RVM1(0x1eaf, 0, BIT4 | BIT3),   //reg[101eaf]#4 ~ #3 = 0b
        //reg_ts_out_mode
        _RVM1(0x1edc, 0, BIT3),   //reg[101edc]#3 = 0b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_SYNC_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_SYNC_OEN (PAD_TS1_SYNC_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS1_SYNC_OUT (PAD_TS1_SYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b28, PAD_TS1_SYNC_OUT, BIT0),
        _RVM1(0x2b28, PAD_TS1_SYNC_OEN, BIT1),
        //reg_ts1_pe[9]
        _RVM1(0x1e0d, BIT1, BIT1),   //reg[101e0d]#1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_ts1config[1:0]
        _RVM1(0x1eaf, 0, BIT4 | BIT3),   //reg[101eaf]#4 ~ #3 = 0b
        //reg_ts_out_mode
        _RVM1(0x1edc, 0, BIT3),   //reg[101edc]#3 = 0b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_VLD_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_VLD_OEN (PAD_TS1_VLD_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS1_VLD_OUT (PAD_TS1_VLD_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b29, PAD_TS1_VLD_OUT, BIT0),
        _RVM1(0x2b29, PAD_TS1_VLD_OEN, BIT1),
        //reg_ts1_pe[8]
        _RVM1(0x1e0d, BIT0, BIT0),   //reg[101e0d]#0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_ts1config[1:0]
        _RVM1(0x1eaf, 0, BIT4 | BIT3),   //reg[101eaf]#4 ~ #3 = 0b
        //reg_ts_out_mode
        _RVM1(0x1edc, 0, BIT3),   //reg[101edc]#3 = 0b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_D7_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_D7_OEN (PAD_TS1_D7_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS1_D7_OUT (PAD_TS1_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b2a, PAD_TS1_D7_OUT, BIT0),
        _RVM1(0x2b2a, PAD_TS1_D7_OEN, BIT1),
        //reg_ts1_pe[7]
        _RVM1(0x1e0c, BIT7, BIT7),   //reg[101e0c]#7 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_ts1config[1:0]
        _RVM1(0x1eaf, 0, BIT4 | BIT3),   //reg[101eaf]#4 ~ #3 = 0b
        //reg_ts_out_mode
        _RVM1(0x1edc, 0, BIT3),   //reg[101edc]#3 = 0b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 0b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_D6_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_D6_OEN (PAD_TS1_D6_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS1_D6_OUT (PAD_TS1_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b2b, PAD_TS1_D6_OUT, BIT0),
        _RVM1(0x2b2b, PAD_TS1_D6_OEN, BIT1),
        //reg_ts1_pe[6]
        _RVM1(0x1e0c, BIT6, BIT6),   //reg[101e0c]#6 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_ts1config[1:0]
        _RVM1(0x1eaf, 0, BIT4 | BIT3),   //reg[101eaf]#4 ~ #3 = 0b
        //reg_ts_out_mode
        _RVM1(0x1edc, 0, BIT3),   //reg[101edc]#3 = 0b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 0b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 0b
        //reg_sm_config[1:0]
        _RVM1(0x1edc, 0, BIT5 | BIT4),   //reg[101edc]#5 ~ #4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_D5_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_D5_OEN (PAD_TS1_D5_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS1_D5_OUT (PAD_TS1_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b2c, PAD_TS1_D5_OUT, BIT0),
        _RVM1(0x2b2c, PAD_TS1_D5_OEN, BIT1),
        //reg_ts1_pe[5]
        _RVM1(0x1e0c, BIT5, BIT5),   //reg[101e0c]#5 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_ts1config[1:0]
        _RVM1(0x1eaf, 0, BIT4 | BIT3),   //reg[101eaf]#4 ~ #3 = 0b
        //reg_ts_out_mode
        _RVM1(0x1edc, 0, BIT3),   //reg[101edc]#3 = 0b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 0b
        //reg_pdtracectrl[1:0]
        _RVM1(0x1e9f, 0, BIT1 | BIT0),   //reg[101e9f]#1 ~ #0 = 0b
        //reg_sm_config[1:0]
        _RVM1(0x1edc, 0, BIT5 | BIT4),   //reg[101edc]#5 ~ #4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_D4_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_D4_OEN (PAD_TS1_D4_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS1_D4_OUT (PAD_TS1_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b2d, PAD_TS1_D4_OUT, BIT0),
        _RVM1(0x2b2d, PAD_TS1_D4_OEN, BIT1),
        //reg_ts1_pe[4]
        _RVM1(0x1e0c, BIT4, BIT4),   //reg[101e0c]#4 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_ts1config[1:0]
        _RVM1(0x1eaf, 0, BIT4 | BIT3),   //reg[101eaf]#4 ~ #3 = 0b
        //reg_ts_out_mode
        _RVM1(0x1edc, 0, BIT3),   //reg[101edc]#3 = 0b
        //reg_dspejtagmode[1:0]
        //_RVM1(0x1e07, 0, BIT1 | BIT0),   //reg[101e07]#1 ~ #0 = 0b
        //reg_sm_config[1:0]
        _RVM1(0x1edc, 0, BIT5 | BIT4),   //reg[101edc]#5 ~ #4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_D3_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_D3_OEN (PAD_TS1_D3_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS1_D3_OUT (PAD_TS1_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b2e, PAD_TS1_D3_OUT, BIT0),
        _RVM1(0x2b2e, PAD_TS1_D3_OEN, BIT1),
        //reg_ts1_pe[3]
        _RVM1(0x1e0c, BIT3, BIT3),   //reg[101e0c]#3 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_ts1config[1:0]
        _RVM1(0x1eaf, 0, BIT4 | BIT3),   //reg[101eaf]#4 ~ #3 = 0b
        //reg_ts_out_mode
        _RVM1(0x1edc, 0, BIT3),   //reg[101edc]#3 = 0b
        //reg_sm_config[1:0]
        _RVM1(0x1edc, 0, BIT5 | BIT4),   //reg[101edc]#5 ~ #4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_D2_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_D2_OEN (PAD_TS1_D2_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS1_D2_OUT (PAD_TS1_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b2f, PAD_TS1_D2_OUT, BIT0),
        _RVM1(0x2b2f, PAD_TS1_D2_OEN, BIT1),
        //reg_ts1_pe[2]
        _RVM1(0x1e0c, BIT2, BIT2),   //reg[101e0c]#2 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_ts1config[1:0]
        _RVM1(0x1eaf, 0, BIT4 | BIT3),   //reg[101eaf]#4 ~ #3 = 0b
        //reg_ts_out_mode
        _RVM1(0x1edc, 0, BIT3),   //reg[101edc]#3 = 0b
        //reg_sm_config[1:0]
        _RVM1(0x1edc, 0, BIT5 | BIT4),   //reg[101edc]#5 ~ #4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_D1_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_D1_OEN (PAD_TS1_D1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS1_D1_OUT (PAD_TS1_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b30, PAD_TS1_D1_OUT, BIT0),
        _RVM1(0x2b30, PAD_TS1_D1_OEN, BIT1),
        //reg_ts1_pe[1]
        _RVM1(0x1e0c, BIT1, BIT1),   //reg[101e0c]#1 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_ts1config[1:0]
        _RVM1(0x1eaf, 0, BIT4 | BIT3),   //reg[101eaf]#4 ~ #3 = 0b
        //reg_ts_out_mode
        _RVM1(0x1edc, 0, BIT3),   //reg[101edc]#3 = 0b
        //reg_sm_config[1:0]
        _RVM1(0x1edc, 0, BIT5 | BIT4),   //reg[101edc]#5 ~ #4 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS1_D0_IS_GPIO != GPIO_NONE)
        #define PAD_TS1_D0_OEN (PAD_TS1_D0_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS1_D0_OUT (PAD_TS1_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2b31, PAD_TS1_D0_OUT, BIT0),
        _RVM1(0x2b31, PAD_TS1_D0_OEN, BIT1),
        //reg_ts1_pe[0]
        _RVM1(0x1e0c, BIT0, BIT0),   //reg[101e0c]#0 = 1b
        //reg_test_in_mode[2:0]
        //_RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),   //reg[101e24]#2 ~ #0 = 00b
        //reg_ts1config[1:0]
        _RVM1(0x1eaf, 0, BIT4 | BIT3),   //reg[101eaf]#4 ~ #3 = 0b
        //reg_ts_out_mode
        _RVM1(0x1edc, 0, BIT3),   //reg[101edc]#3 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS2_D0_IS_GPIO != GPIO_NONE)
        #define PAD_TS2_D0_OEN (PAD_TS2_D0_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS2_D0_OUT (PAD_TS2_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2ba0, PAD_TS2_D0_OUT, BIT0),
        _RVM1(0x2ba0, PAD_TS2_D0_OEN, BIT1),
        //reg_ts2config
        _RVM1(0x1eaf, 0, BIT7 | BIT6),   //reg[101eaf]#7 ~ #6 = 0b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb5, 0, BIT1 | BIT0),   //reg[101eb5]#1 ~ #0 = 0b
        //reg_sd_config2[1:0]
        _RVM1(0x1eb5, 0, BIT3 | BIT2),   //reg[101eb5]#3 ~ #2 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS2_D1_IS_GPIO != GPIO_NONE)
        #define PAD_TS2_D1_OEN (PAD_TS2_D1_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS2_D1_OUT (PAD_TS2_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2ba1, PAD_TS2_D1_OUT, BIT0),
        _RVM1(0x2ba1, PAD_TS2_D1_OEN, BIT1),
        //reg_ts2config
        _RVM1(0x1eaf, 0, BIT7 | BIT6),   //reg[101eaf]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS2_D2_IS_GPIO != GPIO_NONE)
        #define PAD_TS2_D2_OEN (PAD_TS2_D2_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS2_D2_OUT (PAD_TS2_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2ba2, PAD_TS2_D2_OUT, BIT0),
        _RVM1(0x2ba2, PAD_TS2_D2_OEN, BIT1),
        //reg_ts2config
        _RVM1(0x1eaf, 0, BIT7 | BIT6),   //reg[101eaf]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS2_D3_IS_GPIO != GPIO_NONE)
        #define PAD_TS2_D3_OEN (PAD_TS2_D3_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS2_D3_OUT (PAD_TS2_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2ba3, PAD_TS2_D3_OUT, BIT0),
        _RVM1(0x2ba3, PAD_TS2_D3_OEN, BIT1),
        //reg_ts2config
        _RVM1(0x1eaf, 0, BIT7 | BIT6),   //reg[101eaf]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS2_D4_IS_GPIO != GPIO_NONE)
        #define PAD_TS2_D4_OEN (PAD_TS2_D4_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS2_D4_OUT (PAD_TS2_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2ba4, PAD_TS2_D4_OUT, BIT0),
        _RVM1(0x2ba4, PAD_TS2_D4_OEN, BIT1),
        //reg_ts2config
        _RVM1(0x1eaf, 0, BIT7 | BIT6),   //reg[101eaf]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS2_D5_IS_GPIO != GPIO_NONE)
        #define PAD_TS2_D5_OEN (PAD_TS2_D5_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS2_D5_OUT (PAD_TS2_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2ba5, PAD_TS2_D5_OUT, BIT0),
        _RVM1(0x2ba5, PAD_TS2_D5_OEN, BIT1),
        //reg_ts2config
        _RVM1(0x1eaf, 0, BIT7 | BIT6),   //reg[101eaf]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS2_D6_IS_GPIO != GPIO_NONE)
        #define PAD_TS2_D6_OEN (PAD_TS2_D6_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS2_D6_OUT (PAD_TS2_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2ba6, PAD_TS2_D6_OUT, BIT0),
        _RVM1(0x2ba6, PAD_TS2_D6_OEN, BIT1),
        //reg_ts2config
        _RVM1(0x1eaf, 0, BIT7 | BIT6),   //reg[101eaf]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS2_D7_IS_GPIO != GPIO_NONE)
        #define PAD_TS2_D7_OEN (PAD_TS2_D7_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS2_D7_OUT (PAD_TS2_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2ba7, PAD_TS2_D7_OUT, BIT0),
        _RVM1(0x2ba7, PAD_TS2_D7_OEN, BIT1),
        //reg_ts2config
        _RVM1(0x1eaf, 0, BIT7 | BIT6),   //reg[101eaf]#7 ~ #6 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS2_VLD_IS_GPIO != GPIO_NONE)
        #define PAD_TS2_VLD_OEN (PAD_TS2_VLD_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS2_VLD_OUT (PAD_TS2_VLD_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2ba8, PAD_TS2_VLD_OUT, BIT0),
        _RVM1(0x2ba8, PAD_TS2_VLD_OEN, BIT1),
        //reg_ts2config
        _RVM1(0x1eaf, 0, BIT7 | BIT6),   //reg[101eaf]#7 ~ #6 = 0b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb5, 0, BIT1 | BIT0),   //reg[101eb5]#1 ~ #0 = 0b
        //reg_sd_config2[1:0]
        _RVM1(0x1eb5, 0, BIT3 | BIT2),   //reg[101eb5]#3 ~ #2 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS2_SYNC_IS_GPIO != GPIO_NONE)
        #define PAD_TS2_SYNC_OEN (PAD_TS2_SYNC_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS2_SYNC_OUT (PAD_TS2_SYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2ba9, PAD_TS2_SYNC_OUT, BIT0),
        _RVM1(0x2ba9, PAD_TS2_SYNC_OEN, BIT1),
        //reg_ts2config
        _RVM1(0x1eaf, 0, BIT7 | BIT6),   //reg[101eaf]#7 ~ #6 = 0b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb5, 0, BIT1 | BIT0),   //reg[101eb5]#1 ~ #0 = 0b
        //reg_sd_config2[1:0]
        _RVM1(0x1eb5, 0, BIT3 | BIT2),   //reg[101eb5]#3 ~ #2 = 0b
        //reg_allpad_in
        //_RVM1(0x1ea1, 0, BIT7),   //reg[101ea1]#7 = 0b
    #endif

    #if(PAD_TS2_CLK_IS_GPIO != GPIO_NONE)
        #define PAD_TS2_CLK_OEN (PAD_TS2_CLK_IS_GPIO == GPIO_IN ? BIT1: 0)
        #define PAD_TS2_CLK_OUT (PAD_TS2_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
        _RVM1(0x2baa, PAD_TS2_CLK_OUT, BIT0),
        _RVM1(0x2baa, PAD_TS2_CLK_OEN, BIT1),
        //reg_ts2config
        _RVM1(0x1eaf, 0, BIT7 | BIT6),   //reg[101eaf]#7 ~ #6 = 0b
        //reg_nand_mode[2:0]
        _RVM1(0x1edf, 0, BIT0),   //reg[101edf]#0 = 0b
        _RVM1(0x1ede, 0, BIT7 | BIT6),   //reg[101ede]#7 ~ #6 = 0b
        //reg_sd_config[1:0]
        _RVM1(0x1eb5, 0, BIT1 | BIT0),   //reg[101eb5]#1 ~ #0 = 0b
        //reg_sd_config2[1:0]
        _RVM1(0x1eb5, 0, BIT3 | BIT2),   //reg[101eb5]#3 ~ #2 = 0b
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
#define _CONFIG_TS0_CONFIG  ((PADS_TS0_CONFIG == PARALLEL_IN) ? BIT0 : \
                             (PADS_TS0_CONFIG == SERIAL_IN) ? BIT1 : 0)
    _RVM1(0x1eaf, _CONFIG_TS0_CONFIG, (BIT2 | BIT1 | BIT0)),
#endif
#endif

#ifdef PADS_TS1_CONFIG
#if (PADS_TS1_CONFIG != UNKNOWN_PAD_MUX)
#define _CONFIG_TS1_CONFIG  ((PADS_TS1_CONFIG == PARALLEL_IN) ? BIT3 : \
                             (PADS_TS1_CONFIG == PARALLEL_OUT) ? BIT4 : \
                             (PADS_TS1_CONFIG == SERIAL_IN) ? (BIT4 | BIT3) : 0)
    _RVM1(0x1eaf, _CONFIG_TS1_CONFIG, (BIT5 | BIT4 | BIT3)),
#endif
#endif

#if (PADS_TS2_CONFIG != UNKNOWN_PAD_MUX)
#define _CONFIG_TS2_CONFIG  ((PADS_TS2_CONFIG == PARALLEL_IN) ? BIT7 : \
                             (PADS_TS2_CONFIG == SERIAL_IN) ? BIT6 : 0)
    _RVM1(0x1eaf, _CONFIG_TS2_CONFIG, (BIT7 | BIT6)),
#endif

#ifdef PADS_TS_OUT
#if (PADS_TS_OUT != UNKNOWN_PAD_MUX)
#define _CONFIG_TS_OUT_MODE ((PADS_TS_OUT == ENABLE) ? BIT3 : 0)
    _RVM1(0x1edc, _CONFIG_TS_OUT_MODE, BIT3),
#endif
#endif

#ifdef PADS_TS0_PE
#if (PADS_TS0_PE == ENABLE)
    _RVM1(0x1e1e, BITMASK(7:0), BITMASK(7:0)),
    _RVM1(0x1e1f, BITMASK(2:0), BITMASK(2:0)),
#else
    _RVM1(0x1e1e, 0, BITMASK(7:0)),
    _RVM1(0x1e1f, 0, BITMASK(2:0)),
#endif
#endif

#ifdef PADS_TS1_PE
#if (PADS_TS1_PE == ENABLE)
    _RVM1(0x1e0c, BITMASK(7:0), BITMASK(7:0)),
    _RVM1(0x1e0d, BITMASK(2:0), BITMASK(2:0)),
#else
    _RVM1(0x1e0c, 0, BITMASK(7:0)),
    _RVM1(0x1e0d, 0, BITMASK(2:0)),
#endif
#endif

#ifdef PADS_TSERR_OUT
#if (PADS_TSERR_OUT != UNKNOWN_PAD_MUX)
#define _CONFIG_TSERR_OUT   ((PADS_TSERR_OUT == PAD_I2S_IN_SD) ? BIT0 :  \
                             (PADS_TSERR_OUT == PAD_GPIO7) ? BIT1 :  \
                             (PADS_TSERR_OUT == PAD_PWM4) ? (BIT1 | BIT0) : 0)
    _RVM2(0x1ec8, _CONFIG_TSERR_OUT, (BIT1 | BIT0)),
#endif
#endif

//=============================================================================
#ifdef PADS_NAND_MODE
#if (PADS_NAND_MODE != UNKNOWN_PAD_MUX)
#define _CONFIG_NAND_MODE   ((PADS_NAND_MODE == PAD_PCM_D) ? BIT6 : \
                             (PADS_NAND_MODE == PAD_PCM_A) ? BIT7 : 0)
    _RVM1(0x1ede, _CONFIG_NAND_MODE, (BIT7 | BIT6)),
#define _CONFIG_DQS_MODE   ((PADS_NAND_MODE == PAD_PCM_A_DQS) ? BIT0 : 0)
    _RVM1(0x1edf, _CONFIG_DQS_MODE, BIT0),
#else
    _RVM1(0x1edf, 0, BIT0),
    _RVM1(0x1ede, 0, (BIT7 | BIT6)),
#endif
#endif

#ifdef PADS_NAND_CS1_EN
#if (PADS_NAND_CS1_EN != UNKNOWN_PAD_MUX)
#define _CONFIG_NAND_CS1_EN ((PADS_NAND_CS1_EN == ENABLE) ? BIT5:  0)
    _RVM1(0x1ede, _CONFIG_NAND_CS1_EN, BIT5),
#endif
#endif

#ifdef PADS_NAND_PE
#if (PADS_NAND_PE == ENABLE)
    _RVM1(0x1e1a, BITMASK(7:0), BITMASK(7:0)),
    _RVM1(0x1e1b, BIT0, BIT0),
#else
    _RVM1(0x1e1a, 0, BITMASK(7:0)),
    _RVM1(0x1e1b, 0, BIT0),
#endif
#endif

//=============================================================================
#ifdef PADS_EMMC_MODE
#if (PADS_EMMC_MODE != UNKNOWN_PAD_MUX)
#define _CONFIG_EMMC_MODE   ((PADS_EMMC_MODE == PAD_PCM_D) ? BIT6 : \
                             (PADS_EMMC_MODE == PAD_NAND_CTRL) ? (BIT7 | BIT6) : 0)
    _RVM1(0x1edc, _CONFIG_EMMC_MODE, (BIT7 | BIT6)),
#endif
#endif

#ifdef PADS_SD0_MODE
#if (PADS_SD0_MODE != UNKNOWN_PAD_MUX)
#define _CONFIG_SD0_MODE    ((PADS_SD0_MODE == PAD_PCM_D) ? BIT0:  \
                             (PADS_SD0_MODE == PAD_TS2) ? BIT1:  \
                             (PADS_SD0_MODE == PAD_SPI1) ? BIT1|BIT0: 0)
    _RVM1(0x1eb5, _CONFIG_SD0_MODE, (BIT1 | BIT0)),
#endif
#endif

#ifdef PADS_SD1_MODE
#if (PADS_SD1_MODE != UNKNOWN_PAD_MUX)
#define _CONFIG_SD1_MODE    ((PADS_SD1_MODE == PAD_PCM_D) ? BIT2:  \
                             (PADS_SD1_MODE == PAD_TS2) ? BIT3: 0)
    _RVM1(0x1eb5, _CONFIG_SD1_MODE, (BIT3 | BIT2)),
#endif
#endif

//=============================================================================
#ifdef PADS_PCM1_CTRL
#if (PADS_PCM1_CTRL != UNKNOWN_PAD_MUX)
#define _CONFIG_PCM1_CTRL   ((PADS_PCM1_CTRL == PAD_PCM_CE_N) ? BIT5 : 0)
    _RVM1(0x1ec8, _CONFIG_PCM1_CTRL, BIT5),
#endif
#endif

#ifdef PADS_PCM1_AD
#if (PADS_PCM1_AD != UNKNOWN_PAD_MUX)
#define _CONFIG_PCM1_AD     ((PADS_PCM1_AD == PAD_PCM_D7) ? BIT4 : 0)
    _RVM1(0x1ec8, _CONFIG_PCM1_AD, BIT4),
#endif
#endif

#ifdef PADS_PCM1_PE
#if (PADS_PCM1_PE != UNKNOWN_PAD_MUX)
#if (PADS_PCM1_PE == ENABLE)
        _RVM1(0x1E12, BITMASK(7:0), BITMASK(7:0)),
        _RVM1(0x1E13, BITMASK(7:0), BITMASK(7:0)),
        _RVM1(0x1E14, BITMASK(7:0), BITMASK(7:0)),
        _RVM1(0x1E15, BITMASK(7:0), BITMASK(7:0)),
        _RVM1(0x1E16, BITMASK(1:0), BITMASK(1:0)),
#else
        _RVM1(0x1E12, 0, BITMASK(7:0)),
        _RVM1(0x1E13, 0, BITMASK(7:0)),
        _RVM1(0x1E14, 0, BITMASK(7:0)),
        _RVM1(0x1E15, 0, BITMASK(7:0)),
        _RVM1(0x1E16, 0, BITMASK(1:0)),
#endif
#endif
#endif

#ifdef PADS_PCM2_CTRL
#if (PADS_PCM2_CTRL != UNKNOWN_PAD_MUX)
#define _CONFIG_PCM2_CTRL        ((PADS_PCM2_CTRL == PAD_PCM2_CD_N) ? BIT3 : 0)
#define _CONFIG_PCM2_CTRL_CD_N   ((PADS_PCM2_CTRL == PAD_PCM2_CD_N) ? BIT0 : 0)
    _RVM1(0x1ec8, _CONFIG_PCM2_CTRL, BIT3),
    _RVM1(0x1e9e, _CONFIG_PCM2_CTRL_CD_N, BIT0),
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
#define _CONFIG_I2S_OUT ((PADS_I2S_OUT == ENABLE) ? BIT4 : 0)
    _RVM1(0x1eae, _CONFIG_I2S_OUT, BIT4),
#endif
#endif

#ifdef PADS_I2S_OUT_SD
#if (PADS_I2S_OUT_SD != UNKNOWN_PAD_MUX)
#define _CONFIG_I2S_OUT_SD  ((PADS_I2S_OUT_SD == ENABLE) ? BIT5 : 0)
    _RVM1(0x1eae, _CONFIG_I2S_OUT_SD, BIT5),
#endif
#endif

#ifdef PADS_I2S_OUT_SD1
#if (PADS_I2S_OUT_SD1 != UNKNOWN_PAD_MUX)
#define _CONFIG_I2S_OUT_SD1 ((PADS_I2S_OUT_SD1 == ENABLE) ? BIT3 : 0)
    _RVM1(0x1eb3, _CONFIG_I2S_OUT_SD1, BIT3),
#endif
#endif

#ifdef PADS_I2S_OUT_SD2
#if (PADS_I2S_OUT_SD2 != UNKNOWN_PAD_MUX)
#define _CONFIG_I2S_OUT_SD2 ((PADS_I2S_OUT_SD2 == ENABLE) ? BIT4 : 0)
    _RVM1(0x1eb3, _CONFIG_I2S_OUT_SD2, BIT4),
#endif
#endif

#ifdef PADS_I2S_OUT_SD3
#if (PADS_I2S_OUT_SD3 != UNKNOWN_PAD_MUX)
#define _CONFIG_I2S_OUT_SD3 ((PADS_I2S_OUT_SD3 == ENABLE) ? BIT5 : 0)
    _RVM1(0x1eb3, _CONFIG_I2S_OUT_SD3, BIT5),
#endif
#endif

#ifdef PADS_I2S_MUTE
#if (PADS_I2S_MUTE != UNKNOWN_PAD_MUX)
#define _CONFIG_I2S_MUTE    ((PADS_I2S_MUTE == PAD_GPIO9) ? BIT6 : \
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
#define _CONFIG_ET_MODE     ((PADS_ET_MODE == ENABLE) ? BIT1 : 0)
    _RVM1(0x1edf, _CONFIG_ET_MODE, BIT1),
#endif
#endif

//=============================================================================
#ifdef PADS_3D_FLAG_CONFIG
#if (PADS_3D_FLAG_CONFIG != UNKNOWN_PAD_MUX)
#define _CONFIG_3D_FLAG_CONFIG  ((PADS_3D_FLAG_CONFIG == PAD_SPDIF_IN) ? BIT6 : \
                                 (PADS_3D_FLAG_CONFIG == PAD_GPIO2) ? BIT7 : \
                                 (PADS_3D_FLAG_CONFIG == PAD_I2S_IN_SD) ? (BIT7 | BIT6) : 0)
    _RVM1(0x1eb3, _CONFIG_3D_FLAG_CONFIG, (BIT7 | BIT6)),
#endif
#endif

//=============================================================================
#ifdef PADS_LED_MODE
#if (PADS_LED_MODE != UNKNOWN_PAD_MUX)
#define _CONFIG_LED_MODE    ((PADS_LED_MODE == ENABLE) ? BIT4 : 0)
    _RVM1(0x1eb4, _CONFIG_LED_MODE, BIT4),
#endif
#endif

//=============================================================================
#ifdef PADS_UART2_MODE
#if (PADS_UART2_MODE != UNKNOWN_PAD_MUX)
#define _CONFIG_UART2_MODE  ((PADS_UART2_MODE == PAD_TS0) ? BIT0 : \
                             (PADS_UART2_MODE == PAD_PCM2) ? BIT1 : \
                             (PADS_UART2_MODE == PAD_GPIO) ? (BIT1 | BIT0) : 0 )
    _RVM1(0x1e05, _CONFIG_UART2_MODE, (BIT1 | BIT0)),
#endif
#endif

#ifdef PADS_UART3_MODE
#if (PADS_UART3_MODE != UNKNOWN_PAD_MUX)
#define _CONFIG_UART3_MODE  ((PADS_UART3_MODE == PAD_GPIO) ? BIT2: \
                             (PADS_UART3_MODE == PAD_I2S) ? BIT3: \
                             (PADS_UART3_MODE == PAD_PCM2) ? (BIT3 | BIT2) : 0 )
    _RVM1(0x1e05, _CONFIG_UART3_MODE, (BIT3 | BIT2)),
#endif
#endif

#ifdef PADS_UART4_MODE
#if (PADS_UART4_MODE != UNKNOWN_PAD_MUX)
#define _CONFIG_UART4_MODE  ((PADS_UART4_MODE == PAD_TS2) ? BIT6: \
                             (PADS_UART4_MODE == PAD_GPIO) ? BIT7: \
                             (PADS_UART4_MODE == PAD_I2S) ? (BIT7 | BIT6) : 0 )
    _RVM1(0x1e04, _CONFIG_UART4_MODE, (BIT7 | BIT6)),
#endif
#endif

#ifdef PADS_FAST_UART_MODE
#if (PADS_FAST_UART_MODE != UNKNOWN_PAD_MUX)
#define _CONFIG_FAST_UART_MODE  ((PADS_FAST_UART_MODE == PAD_GPIO1) ? BIT4 : \
                                 (PADS_FAST_UART_MODE == PAD_GPIO2) ? BIT4 : \
                                 (PADS_FAST_UART_MODE == PAD_TCON) ? BIT5 : \
                                 (PADS_FAST_UART_MODE == PAD_GPIO13) ? (BIT5 | BIT4) : \
                                 (PADS_FAST_UART_MODE == PAD_GPIO14) ? (BIT5 | BIT4) : 0 )
    _RVM1(0x1e04, _CONFIG_FAST_UART_MODE, (BIT5 | BIT4)),
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

    _MEMMAP_PM_,
    _RVM1(0x0e13, 0, BIT4),         //Select UART Source to reg_uart_sel0
    _RVM1(0x0e13, BIT3, BIT3),      //Enable UART Rx
    _MEMMAP_nonPM_,

//=============================================================================
#ifdef PADS_PWM0_MODE
#if (PADS_PWM0_MODE != UNKNOWN_PAD_MUX)
#define _CONFIG_PWM0_MODE   ((PADS_PWM0_MODE == ENABLE) ? BIT2:  0)
    _RVM1(0x1ec8, _CONFIG_PWM0_MODE, BIT2),
#endif
#endif

#ifdef PADS_PWM1_MODE
#if (PADS_PWM1_MODE != UNKNOWN_PAD_MUX)
#define _CONFIG_PWM1_MODE   ((PADS_PWM1_MODE == ENABLE) ? BIT6:  0)
    _RVM1(0x1ec8, _CONFIG_PWM1_MODE, BIT6),
#endif
#endif

#ifdef PADS_PWM2_MODE
#if (PADS_PWM2_MODE != UNKNOWN_PAD_MUX)
#define _CONFIG_PWM2_MODE   ((PADS_PWM2_MODE == ENABLE) ? BIT7:  0)
    _RVM1(0x1ec8, _CONFIG_PWM2_MODE, BIT7),
#endif
#endif

#ifdef PADS_PWM3_MODE
#if (PADS_PWM3_MODE != UNKNOWN_PAD_MUX)
#define _CONFIG_PWM3_MODE   ((PADS_PWM3_MODE == ENABLE) ? BIT4:  0)
    _RVM1(0x1ec9, _CONFIG_PWM3_MODE, BIT4),
#endif
#endif

#ifdef PADS_PWM4_MODE
#if (PADS_PWM4_MODE != UNKNOWN_PAD_MUX)
#define _CONFIG_PWM4_MODE   ((PADS_PWM4_MODE == ENABLE) ? BIT5 : 0)
    _RVM1(0x1ec9, _CONFIG_PWM4_MODE, BIT5),
#endif
#endif
//=============================================================================
#if (PADS_MSPI_MODE != UNKNOWN_PAD_MUX)
#define MSPI_MODE   ((PADS_MSPI_MODE == SPI_PAD0) ? BIT0:  \
                     (PADS_MSPI_MODE == SPI_PAD1) ? BIT1:  \
                     (PADS_MSPI_MODE == SPI_PAD2) ? BIT2:  \
                     (PADS_MSPI_MODE == SPI_PAD3) ? BIT3: 0)
        _RVM1(0x1eb4, MSPI_MODE, (BIT3 | BIT2 | BIT1 | BIT0)),
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
#define _CONFIG_MIIC_MODE0  ((PADS_MIIC_MODE0 == PAD_GPIO19) ? BIT0 :  \
                             (PADS_MIIC_MODE0 == PAD_GPIO20) ? BIT0 : 0)
    _RVM1(0x1edc, _CONFIG_MIIC_MODE0, BIT0),
#endif
#endif

#ifdef PADS_MIIC_MODE1
#if (PADS_MIIC_MODE1 != UNKNOWN_PAD_MUX)
#define _CONFIG_MIIC_MODE1  ((PADS_MIIC_MODE1 == PAD_TGPIO2) ? BIT1 :  \
                             (PADS_MIIC_MODE1 == PAD_TGPIO3) ? BIT1 : 0)
    _RVM1(0x1edc, _CONFIG_MIIC_MODE1, BIT1),
#endif
#endif

#ifdef PADS_MIIC_MODE2
#if (PADS_MIIC_MODE2 != UNKNOWN_PAD_MUX)
#define _CONFIG_MIIC_MODE2  ((PADS_MIIC_MODE2 == PAD_I2S_IN_BCK) ? BIT2 : \
                             (PADS_MIIC_MODE2 == PAD_I2S_IN_SD) ? BIT2 : 0)
    _RVM1(0x1edc, _CONFIG_MIIC_MODE2, BIT2),
#endif
#endif

//=============================================================================
#ifdef PADS_SM_MODE
#if (PADS_SM_MODE != UNKNOWN_PAD_MUX)
#define _CONFIG_SM_MODE     ((PADS_SM_MODE == SMART_CARD_PCM) ? BIT4 : \
                             (PADS_SM_MODE == SMART_CARD_TS1) ? BIT5 : 0)
    _RVM1(0x1edc, _CONFIG_SM_MODE, (BIT5 | BIT4)),

#if (PADS_SM_MODE == SMART_CARD_PCM)
    _RVM1(0x1ec8, 0, BIT5 | BIT4 | BIT1 | BIT0),    //Disable Ctrl/Address/Data Pads of PCM/CI
#endif
#if (PADS_SM_MODE == SMART_CARD_TS1)
    _RVM1(0x1e24, 0, BIT2 | BIT1 | BIT0),
    _RVM1(0x1eaf, 0, BIT5 | BIT4 | BIT3),   //Disable TS1 Pad
#endif
#endif
#endif

#ifdef PADS_SMART_CARD_VCC
#if (PADS_SMART_CARD_VCC != UNKNOWN_PAD_MUX)
#define _CONFIG_SMART_CARD_VCC_MODE ((PADS_SMART_CARD_VCC == SMART_CARD_VCC_3P3V) ? 0 : \
                                     (PADS_SMART_CARD_VCC == SMART_CARD_VCC_5V) ? BIT2 : 0)
    _RVM1(0x2bc2, _CONFIG_SMART_CARD_VCC_MODE, BIT2),
#endif
#endif

//=============================================================================
#ifdef PADS_PDTRACE_MODE
#if (PADS_PDTRACE_MODE != UNKNOWN_PAD_MUX)
#define _CONFIG_PDTRACE_MODE    ((PADS_PDTRACE_MODE == PADS_TS1) ? BIT0 : \
                                 (PADS_PDTRACE_MODE == PADS_GPIO) ? BIT1 : 0)
    _RVM1(0x1e9f, _CONFIG_PDTRACE_MODE, (BIT1 | BIT0)),
#endif
#endif

//=============================================================================
#ifdef ENABLE_EXT_GPIO_INT0
#define _CONFIG_EXT_GPIO_INT0   ((ENABLE_EXT_GPIO_INT0 == ENABLE) ? BIT0 : 0)
    _RVM1(0x1ea5, _CONFIG_EXT_GPIO_INT0, BIT0),
#endif

#ifdef ENABLE_EXT_GPIO_INT1
#define _CONFIG_EXT_GPIO_INT1   ((ENABLE_EXT_GPIO_INT1 == ENABLE) ? BIT1 : 0)
    _RVM1(0x1ea5, _CONFIG_EXT_GPIO_INT1, BIT1),
#endif

#ifdef ENABLE_EXT_GPIO_INT2
#define _CONFIG_EXT_GPIO_INT2   ((ENABLE_EXT_GPIO_INT2 == ENABLE) ? BIT2 : 0)
    _RVM1(0x1ea5, _CONFIG_EXT_GPIO_INT0, BIT2),
#endif

#ifdef ENABLE_EXT_GPIO_INT3
#define _CONFIG_EXT_GPIO_INT3   ((ENABLE_EXT_GPIO_INT3 == ENABLE) ? BIT3 : 0)
    _RVM1(0x1ea5, _CONFIG_EXT_GPIO_INT0, BIT3),
#endif

#ifdef ENABLE_EXT_GPIO_INT4
#define _CONFIG_EXT_GPIO_INT4   ((ENABLE_EXT_GPIO_INT4 == ENABLE) ? BIT4 : 0)
    _RVM1(0x1ea5, _CONFIG_EXT_GPIO_INT4, BIT4),
#endif

#ifdef ENABLE_EXT_GPIO_INT5
#define _CONFIG_EXT_GPIO_INT5   ((ENABLE_EXT_GPIO_INT0 == ENABLE) ? BIT5 : 0)
    _RVM1(0x1ea5, _CONFIG_EXT_GPIO_INT5, BIT5),
#endif

#ifdef ENABLE_EXT_GPIO_INT6
#define _CONFIG_EXT_GPIO_INT6   ((ENABLE_EXT_GPIO_INT6 == ENABLE) ? BIT6 : 0)
    _RVM1(0x1ea5, _CONFIG_EXT_GPIO_INT6, BIT6),
#endif

#ifdef ENABLE_EXT_GPIO_INT7
#define _CONFIG_EXT_GPIO_INT7   ((ENABLE_EXT_GPIO_INT7 == ENABLE) ? BIT7 : 0)
    _RVM1(0x1ea5, _CONFIG_EXT_GPIO_INT7, BIT7),
#endif

//=============================================================================
#ifdef ENABLE_PM51_PORT1_GPIO0
#define _CONFIG_PM51_PORT1_GPIO0    ((ENABLE_PM51_PORT1_GPIO0 == ENABLE) ? BIT0 : 0)
    _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO0, BIT0),
#endif

#ifdef ENABLE_PM51_PORT1_GPIO1
#define _CONFIG_PM51_PORT1_GPIO1    ((ENABLE_PM51_PORT1_GPIO1 == ENABLE) ? BIT1 : 0)
    _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO1, BIT1),
#endif

#ifdef ENABLE_PM51_PORT1_GPIO2
#define _CONFIG_PM51_PORT1_GPIO2    ((ENABLE_PM51_PORT1_GPIO2 == ENABLE) ? BIT2 : 0)
    _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO2, BIT2),
#endif

#ifdef ENABLE_PM51_PORT1_GPIO3
#define _CONFIG_PM51_PORT1_GPIO3    ((ENABLE_PM51_PORT1_GPIO3 == ENABLE) ? BIT3 : 0)
    _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO3, BIT3),
#endif

#ifdef ENABLE_PM51_PORT1_GPIO4
#define _CONFIG_PM51_PORT1_GPIO4    ((ENABLE_PM51_PORT1_GPIO4 == ENABLE) ? BIT4 : 0)
    _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO4, BIT4),
#endif

#ifdef ENABLE_PM51_PORT1_GPIO5
#define _CONFIG_PM51_PORT1_GPIO5    ((ENABLE_PM51_PORT1_GPIO5 == ENABLE) ? BIT5 : 0)
    _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO5, BIT5),
#endif

#ifdef ENABLE_PM51_PORT1_GPIO6
#define _CONFIG_PM51_PORT1_GPIO6    ((ENABLE_PM51_PORT1_GPIO6 == ENABLE) ? BIT6 : 0)
    _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO6, BIT6),
#endif

#ifdef ENABLE_PM51_PORT1_GPIO7
#define _CONFIG_PM51_PORT1_GPIO7    ((ENABLE_PM51_PORT1_GPIO7 == ENABLE) ? BIT7 : 0)
    _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO7, BIT7),
#endif

//=============================================================================
    //reg_allpad_in
    _RVM1(0x1ea1, 0, BIT7),     //reg[101ea1]#7 = 0b
    _END_OF_TBL_,

//=================================================================================================
    //External Flash #1
    _MEMMAP_PM_,
    _RVM1(0x0e6a, 0, BIT0),     //Select to spi_do, spi_di and spi_ck
    _RVM1(0x0e6a, 0, BIT1),     //Select to spi_cz0
    _RVM1(0x08f4, 0, 0xFF),     //Select to External #1 SPI Flash

#if (PIN_FLASH_WP0)
#if (MS_BOARD_TYPE_SEL == BD_MST169A_D01A_S_EIFFEL)
    _RVM1(0x0f06, BIT1, BIT1),  //Output Value of PM3
    _RVM1(0x0f06, 0, BIT0),     //Output Enable of PM3
#elif (MS_BOARD_TYPE_SEL == BD_MST201B_D01A_S_EIFFEL)
    _RVM1(0x0f06, BIT1, BIT1),  //Output Value of PM3
    _RVM1(0x0f06, 0, BIT0),     //Output Enable of PM3
#elif (MS_BOARD_TYPE_SEL == BD_MST169A_C01A_S_EIFFEL)
    _RVM1(0x0f06, BIT1, BIT1),  //Output Value of PM3
    _RVM1(0x0f06, 0, BIT0),     //Output Enable of PM3
#elif (MS_BOARD_TYPE_SEL == BD_FPGA_EIFFEL)
#else
    #error [ERROR] Invalid WP0 Settings in Unknown Board
#endif
#endif
    _END_OF_TBL_,

//=================================================================================================
    //External Flash #2
    _MEMMAP_PM_,
    _RVM1(0x0e6a, 0, BIT0),     //Select to spi_do, spi_di and spi_ck
#if (PIN_SPI_CZ1)
    _RVM1(0x0e6a, 0, BIT2),     //Select to spi_cz1
    _RVM1(0x08f4, 1, 0xFF),     //Select to External #2 SPI Flash
#if (PIN_FLASH_WP1)
#if (MS_BOARD_TYPE_SEL == BD_MST169A_D01A_S_EIFFEL)
    _RVM1(0x0f0e, BIT1, BIT1),  //Output Value of PM7
    _RVM1(0x0f0e, 0, BIT0),     //Output Enable of PM7
#elif (MS_BOARD_TYPE_SEL == BD_MST201B_D01A_S_EIFFEL)
    _RVM1(0x0f0e, BIT1, BIT1),  //Output Value of PM7
    _RVM1(0x0f0e, 0, BIT0),     //Output Enable of PM7
#elif (MS_BOARD_TYPE_SEL == BD_MST169A_C01A_S_EIFFEL)
    _RVM1(0x0f0e, BIT1, BIT1),  //Output Value of PM7
    _RVM1(0x0f0e, 0, BIT0),     //Output Enable of PM7
#elif (MS_BOARD_TYPE_SEL == BD_FPGA_EIFFEL)
#else
    #error [ERROR] Invalid WP1 Settings in Unknown Board
#endif
#endif
    _END_OF_TBL_,
#endif

};

//-----------------------------------------------------------------
// Sanity check for PAD_TOP setting (TODO)
//-----------------------------------------------------------------
#if (UART0_SRC_SEL == UART1_SRC_SEL) || \
    (UART0_SRC_SEL == UART2_SRC_SEL) || \
    (UART1_SRC_SEL == UART2_SRC_SEL)
    #error "UART Source Selection Conflict"
#endif

