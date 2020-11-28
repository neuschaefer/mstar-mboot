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
#include "hwreg_clippers.h"
#include "chip/bond.h"

#define GPIO_NONE                   0       // Not GPIO pin (default)
#define GPIO_IN                     1       // GPI
#define GPIO_OUT_LOW                2       // GPO output low
#define GPIO_OUT_HIGH               3       // GPO output high

#if defined(ARM_CHAKRA) || defined(MIPS_CHAKRA) || defined(MSOS_TYPE_LINUX)
#define _MapBase_nonPM_CLIPPERS      (RIU_MAP + 0x200000)
#define _MapBase_PM_CLIPPERS         RIU_MAP
#else
#define _MapBase_nonPM_CLIPPERS      0xA0200000
#define _MapBase_PM_CLIPPERS         0xA0000000
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

    #if(PAD_GPIO_PM0_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM0_OEN (PAD_GPIO_PM0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO_PM0_OUT (PAD_GPIO_PM0_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f00, PAD_GPIO_PM0_OUT, BIT1),
    _RVM1(0x0f00, PAD_GPIO_PM0_OEN, BIT0),
    //default is GPIO
    #endif

    #if(PAD_GPIO_PM1_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM1_OEN (PAD_GPIO_PM1_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO_PM1_OUT (PAD_GPIO_PM1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f02, PAD_GPIO_PM1_OUT, BIT1),
    _RVM1(0x0f02, PAD_GPIO_PM1_OEN, BIT0),
    //default is GPIO
    #endif

    #if(PAD_GPIO_PM2_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM2_OEN (PAD_GPIO_PM2_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO_PM2_OUT (PAD_GPIO_PM2_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f04, PAD_GPIO_PM2_OUT, BIT1),
    _RVM1(0x0f04, PAD_GPIO_PM2_OEN, BIT0),
    _RVM1(0x0e39, 0, BIT5 | BIT4 ),   //reg[0e39]#5 ~ #4 = 00b
    #endif

    #if(PAD_GPIO_PM3_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM3_OEN (PAD_GPIO_PM3_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO_PM3_OUT (PAD_GPIO_PM3_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f06, PAD_GPIO_PM3_OUT, BIT1),
    _RVM1(0x0f06, PAD_GPIO_PM3_OEN, BIT0),
    _RVM1(0x0e39, 0, BIT5 | BIT4 ),   //reg[0e39]#5 ~ #4 = 00b
    #endif

    #if(PAD_GPIO_PM4_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM4_OEN (PAD_GPIO_PM4_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO_PM4_OUT (PAD_GPIO_PM4_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f08, PAD_GPIO_PM4_OUT, BIT1),
    _RVM1(0x0f08, PAD_GPIO_PM4_OEN, BIT0),
    //default is GPIO
    #endif

    #if(PAD_GPIO_PM5_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM5_OEN (PAD_GPIO_PM5_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO_PM5_OUT (PAD_GPIO_PM5_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f0a, PAD_GPIO_PM5_OUT, BIT1),
    _RVM1(0x0f0a, PAD_GPIO_PM5_OEN, BIT0),
    _RVM1(0x0e39, BIT3 , BIT3 ),   //reg[0e39]#3 = 1
    #endif

    #if(PAD_GPIO_PM6_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM6_OEN (PAD_GPIO_PM6_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO_PM6_OUT (PAD_GPIO_PM6_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f0c, PAD_GPIO_PM6_OUT, BIT1),
    _RVM1(0x0f0c, PAD_GPIO_PM6_OEN, BIT0),
    _RVM1(0x0e6a, BIT2 , BIT2 ),   //reg[0e6a]#2 = 1
    #endif

    #if(PAD_GPIO_PM7_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM7_OEN (PAD_GPIO_PM7_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO_PM7_OUT (PAD_GPIO_PM7_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f0e, PAD_GPIO_PM7_OUT, BIT1),
    _RVM1(0x0f0e, PAD_GPIO_PM7_OEN, BIT0),
    _RVM1(0x0e6a, BIT3 , BIT3 ),   //reg[0e6a]#3 = 1
    #endif

    #if(PAD_GPIO_PM8_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM8_OEN (PAD_GPIO_PM8_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO_PM8_OUT (PAD_GPIO_PM8_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f10, PAD_GPIO_PM8_OUT, BIT1),
    _RVM1(0x0f10, PAD_GPIO_PM8_OEN, BIT0),
    //default is GPIO
    #endif

    #if(PAD_GPIO_PM9_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM9_OEN (PAD_GPIO_PM9_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO_PM9_OUT (PAD_GPIO_PM9_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f12, PAD_GPIO_PM9_OUT, BIT1),
    _RVM1(0x0f12, PAD_GPIO_PM9_OEN, BIT0),
    _RVM1(0x0ee4, 0, BIT1 ),   //reg[0ee4]#1 = 0
    #endif

    #if(PAD_PM_SPI_CK_IS_GPIO != GPIO_NONE)
    #define PAD_PM_SPI_CK_OEN (PAD_PM_SPI_CK_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_PM_SPI_CK_OUT (PAD_PM_SPI_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f30, PAD_PM_SPI_CK_OUT, BIT1),
    _RVM1(0x0f30, PAD_PM_SPI_CK_OEN, BIT0),
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

    #if(PAD_PM_SPI_CZ_IS_GPIO != GPIO_NONE)
    #define PAD_PM_SPI_CZ_OEN (PAD_PM_SPI_CZ_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_PM_SPI_CZ_OUT (PAD_PM_SPI_CZ_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f2e, PAD_PM_SPI_CZ_OUT, BIT1),
    _RVM1(0x0f2e, PAD_PM_SPI_CZ_OEN, BIT0),
    //reg_spicsz0_gpio
    _RVM1(0x0e6a, BIT1 , BIT1 ),   //reg[0e6a]#1 = 1
    #endif

    #if(PAD_PM_SPI_DI_IS_GPIO != GPIO_NONE)
    #define PAD_PM_SPI_DI_OEN (PAD_PM_SPI_DI_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_PM_SPI_DI_OUT (PAD_PM_SPI_DI_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f32, PAD_PM_SPI_DI_OUT, BIT1),
    _RVM1(0x0f32, PAD_PM_SPI_DI_OEN, BIT0),
    //reg_spi_gpio
    _RVM1(0x0e6a, BIT0 , BIT0 ),   //reg[0e6a]#0 = 1
    #endif

    #if(PAD_VID1_IS_GPIO != GPIO_NONE)
    #define PAD_VID1_OEN (PAD_VID1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_VID1_OUT (PAD_VID1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2e85, PAD_VID1_OUT, BIT0),
    _RVM1(0x2e85, PAD_VID1_OEN, BIT1),
    //reg_vid_is_gpio
    _RVM1(0x0e39, BIT2 , BIT2 ),   //reg[0e39]#2 = 1
    //reg_miic_mode[1:0]
    _RVM1(0x0e39, 0, BIT5 | BIT4 ),   //reg[0e39]#5 ~ #4 = 00b
    #endif

    #if(PAD_VID0_IS_GPIO != GPIO_NONE)
    #define PAD_VID0_OEN (PAD_VID0_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_VID0_OUT (PAD_VID0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2e84, PAD_VID0_OUT, BIT0),
    _RVM1(0x2e84, PAD_VID0_OEN, BIT1),
    //reg_vid_is_gpio
    _RVM1(0x0e39, BIT2 , BIT2 ),   //reg[0e39]#2 = 1
    //reg_miic_mode[1:0]
    _RVM1(0x0e39, 0, BIT5 | BIT4 ),   //reg[0e39]#5 ~ #4 = 00b
    #endif

    _MEMMAP_nonPM_,

    #if(PAD_GPIO0_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO0_OEN (PAD_GPIO0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO0_OUT (PAD_GPIO0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b00, PAD_GPIO0_OUT, BIT0),
    _RVM1(0x2b02, PAD_GPIO0_OEN, BIT0),
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0 ),   //reg[101edf]#0 = 0
    //reg_seconduartmode
    _RVM1(0x1e05, 0, BIT1 | BIT0 ),   //reg[101e05]#1 ~ #0 = 00b
    //reg_fourthuartmode
    _RVM1(0x1e04, 0, BIT7 | BIT6 ),   //reg[101e04]#7 ~ #6 = 00b
    //reg_od2nduart
    _RVM1(0x1ea9, 0, BIT1 | BIT0 ),   //reg[101ea9]#1 ~ #0 = 00b
    //reg_od4thuart
    _RVM1(0x1ea9, 0, BIT5 | BIT4 ),   //reg[101ea9]#5 ~ #4 = 00b
    //reg_miic_mode4
    _RVM1(0x1ede, 0, BIT0 ),   //reg[101ede]#0 = 0b
    //reg_extint0
    _RVM1(0x1ea5, 0, BIT0 ),   //reg[101ea5]#0 = 0b
    //reg_p1_enable_b0
    _RVM1(0x1ea4, 0, BIT0 ),   //reg[101ea4]#0 = 0b
    #endif

    #if(PAD_GPIO1_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO1_OEN (PAD_GPIO1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_GPIO1_OUT (PAD_GPIO1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x2b00, PAD_GPIO1_OUT, BIT1),
    _RVM1(0x2b02, PAD_GPIO1_OEN, BIT1),
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0 ),   //reg[101edf]#0 = 0
    //reg_seconduartmode
    _RVM1(0x1e05, 0, BIT1 | BIT0 ),   //reg[101e05]#1 ~ #0 = 00b
    //reg_fourthuartmode
    _RVM1(0x1e04, 0, BIT7 | BIT6 ),   //reg[101e04]#7 ~ #6 = 00b
    //reg_od2nduart
    _RVM1(0x1ea9, 0, BIT1 | BIT0 ),   //reg[101ea9]#1 ~ #0 = 00b
    //reg_od4thuart
    _RVM1(0x1ea9, 0, BIT5 | BIT4 ),   //reg[101ea9]#5 ~ #4 = 00b
    //reg_miic_mode4
    _RVM1(0x1ede, 0, BIT0 ),   //reg[101ede]#0 = 0b
    //reg_extint1
    _RVM1(0x1ea5, 0, BIT1 ),   //reg[101ea5]#1 = 0b
    //reg_p1_enable_b1
    _RVM1(0x1ea4, 0, BIT1 ),   //reg[101ea4]#1 = 0b
    #endif

    #if(PAD_GPIO2_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO2_OEN (PAD_GPIO2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_GPIO2_OUT (PAD_GPIO2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x2b00, PAD_GPIO2_OUT, BIT2),
    _RVM1(0x2b02, PAD_GPIO2_OEN, BIT2),
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0 ),   //reg[101edf]#0 = 0
    //reg_fifthuartmode
    _RVM1(0x1e04, 0, BIT3 | BIT2 ),   //reg[101e04]#3 ~ #2 = 00b
    //reg_od5thuart
    _RVM1(0x1eaa, 0, BIT5 | BIT4 ),   //reg[101eaa]#5 ~ #4 = 00b
    //reg_miic_mode1
    _RVM1(0x1edc, 0, BIT1 ),   //reg[101edc]#1 = 0b
    //reg_extint2
    _RVM1(0x1ea5, 0, BIT2 ),   //reg[101ea5]#2 = 0b
    //reg_p1_enable_b2
    _RVM1(0x1ea4, 0, BIT2 ),   //reg[101ea4]#2 = 0b
    #endif

    #if(PAD_GPIO3_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO3_OEN (PAD_GPIO3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_GPIO3_OUT (PAD_GPIO3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x2b00, PAD_GPIO3_OUT, BIT3),
    _RVM1(0x2b02, PAD_GPIO3_OEN, BIT3),
    //reg_test_in_mode
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0 ),   //reg[101edf]#0 = 0
    //reg_fifthuartmode
    _RVM1(0x1e04, 0, BIT3 | BIT2 ),   //reg[101e04]#3 ~ #2 = 00b
    //reg_od5thuart
    _RVM1(0x1eaa, 0, BIT5 | BIT4 ),   //reg[101eaa]#5 ~ #4 = 00b
    //reg_miic_mode1
    _RVM1(0x1edc, 0, BIT1 ),   //reg[101edc]#1 = 0b
    //reg_extint3
    _RVM1(0x1ea5, 0, BIT3 ),   //reg[101ea5]#3 = 0b
    //reg_p1_enable_b3
    _RVM1(0x1ea4, 0, BIT3 ),   //reg[101ea4]#3 = 0b
    #endif

    #if(PAD_GPIO4_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO4_OEN (PAD_GPIO4_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_GPIO4_OUT (PAD_GPIO4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2b00, PAD_GPIO4_OUT, BIT4),
    _RVM1(0x2b02, PAD_GPIO4_OEN, BIT4),
    //reg_test_in_mode
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0 ),   //reg[101edf]#0 = 0
    //reg_fifthuartmode
    _RVM1(0x1e04, 0, BIT3 | BIT2 ),   //reg[101e04]#3 ~ #2 = 00b
    //reg_od5thuart
    _RVM1(0x1eaa, 0, BIT5 | BIT4 ),   //reg[101eaa]#5 ~ #4 = 00b
    //reg_miic_mode5
    _RVM1(0x1ede, 0, BIT1 ),   //reg[101ede]#1 = 0b
    //reg_extint4
    _RVM1(0x1ea5, 0, BIT4 ),   //reg[101ea5]#4 = 0b
    //reg_p1_enable_b4
    _RVM1(0x1ea4, 0, BIT4 ),   //reg[101ea4]#4 = 0b
    #endif

    #if(PAD_GPIO5_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO5_OEN (PAD_GPIO5_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_GPIO5_OUT (PAD_GPIO5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x2b00, PAD_GPIO5_OUT, BIT5),
    _RVM1(0x2b02, PAD_GPIO5_OEN, BIT5),
    //reg_test_in_mode
    _RVM1(0x1e24, 0, BIT2|BIT1|BIT0 ),   //reg[101e24]#2 ~ #0 = 000b
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0 ),   //reg[101edf]#0 = 0
    //reg_test_out_mode
    _RVM1(0x101e24, 0, BIT6 | BIT5 | BIT4 ),   //reg[0x101e24]#6 ~ #4 = 000b
    //reg_fifthuartmode
    _RVM1(0x1e04, 0, BIT3 | BIT2 ),   //reg[101e04]#3 ~ #2 = 00b
    //reg_od5thuart
    _RVM1(0x1eaa, 0, BIT5 | BIT4 ),   //reg[101eaa]#5 ~ #4 = 00b
    //reg_miic_mode5
    _RVM1(0x1ede, 0, BIT1 ),   //reg[101ede]#1 = 0b
    //reg_extint5
    _RVM1(0x1ea5, 0, BIT5 ),   //reg[101ea5]#5 = 0b
    //reg_p1_enable_b5
    _RVM1(0x1ea4, 0, BIT5 ),   //reg[101ea4]#5 = 0b
    #endif

    #if(PAD_GPIO6_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO6_OEN (PAD_GPIO6_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_GPIO6_OUT (PAD_GPIO6_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x2b00, PAD_GPIO6_OUT, BIT6),
    _RVM1(0x2b02, PAD_GPIO6_OEN, BIT6),
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0 ),   //reg[101edf]#0 = 0
    //reg_sixthuartmode
    _RVM1(0x1e08, 0, BIT7 | BIT6 ),   //reg[101e08]#7 ~ #6 = 00b
    //reg_od6thuart
    _RVM1(0x1eaa, 0, BIT7 | BIT6 ),   //reg[101eaa]#7 ~ #6 = 00b
    //reg_extint6
    _RVM1(0x1ea5, 0, BIT6 ),   //reg[101ea5]#6 = 0b
    //reg_p1_enable_b6
    _RVM1(0x1ea4, 0, BIT6 ),   //reg[101ea4]#6 = 0b
    #endif

    #if(PAD_GPIO7_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO7_OEN (PAD_GPIO7_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_GPIO7_OUT (PAD_GPIO7_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x2b00, PAD_GPIO7_OUT, BIT7),
    _RVM1(0x2b02, PAD_GPIO7_OEN, BIT7),
    //reg_sixthuartmode
    _RVM1(0x1e08, 0, BIT7 | BIT6 ),   //reg[101e08]#7 ~ #6 = 00b
    //reg_od6thuart
    _RVM1(0x1eaa, 0, BIT7 | BIT6 ),   //reg[101eaa]#7 ~ #6 = 00b
    //reg_extint7
    _RVM1(0x1ea5, 0, BIT7 ),   //reg[101ea5]#7 = 0b
    //reg_p1_enable_b7
    _RVM1(0x1ea4, 0, BIT7 ),   //reg[101ea4]#7 = 0b
    #endif

    #if(PAD_SPI2_CK_IS_GPIO != GPIO_NONE)
    #define PAD_SPI2_CK_OEN (PAD_SPI2_CK_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_SPI2_CK_OUT (PAD_SPI2_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x2b18, PAD_SPI2_CK_OUT, BIT3),
    _RVM1(0x2b1a, PAD_SPI2_CK_OEN, BIT3),
    //reg_ld_spi2_config
    _RVM1(0x1eb4, 0, BIT1 ),   //reg[101eb4]#1 = 0b
    //reg_ld_spi3_config
    _RVM1(0x1eb4, 0, BIT2 ),   //reg[101eb4#2 = 0b
    #endif

    #if(PAD_SPI2_DI_IS_GPIO != GPIO_NONE)
    #define PAD_SPI2_DI_OEN (PAD_SPI2_DI_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_SPI2_DI_OUT (PAD_SPI2_DI_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x2b18, PAD_SPI2_DI_OUT, BIT2),
    _RVM1(0x2b1a, PAD_SPI2_DI_OEN, BIT2),
    //reg_ld_spi2_config
    _RVM1(0x1eb4, 0, BIT1 ),   //reg[101eb4]#1 = 0b
    //reg_ld_spi3_config
    _RVM1(0x1eb4, 0, BIT2 ),   //reg[101eb4#2 = 0b
    #endif

    #if(PAD_SPI1_CK_IS_GPIO != GPIO_NONE)
    #define PAD_SPI1_CK_OEN (PAD_SPI1_CK_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_SPI1_CK_OUT (PAD_SPI1_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x2b18, PAD_SPI1_CK_OUT, BIT1),
    _RVM1(0x2b1a, PAD_SPI1_CK_OEN, BIT1),
    //reg_ld_spi1_config
    _RVM1(0x1eb4, 0, BIT0 ),   //reg[101eb4]#0 = 0b
    //reg_ld_spi3_config
    _RVM1(0x1eb4, 0, BIT2 ),   //reg[101eb4#2 = 0b
    #endif

    #if(PAD_SPI1_DI_IS_GPIO != GPIO_NONE)
    #define PAD_SPI1_DI_OEN (PAD_SPI1_DI_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_SPI1_DI_OUT (PAD_SPI1_DI_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b18, PAD_SPI1_DI_OUT, BIT0),
    _RVM1(0x2b1a, PAD_SPI1_DI_OEN, BIT0),
    //reg_ld_spi1_config
    _RVM1(0x1eb4, 0, BIT0 ),   //reg[101eb4]#0 = 0b
    //reg_ld_spi3_config
    _RVM1(0x1eb4, 0, BIT2 ),   //reg[101eb4#2 = 0b
    #endif

    #if(PAD_I2CM_CK_IS_GPIO != GPIO_NONE)
    #define PAD_I2CM_CK_OEN (PAD_I2CM_CK_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_I2CM_CK_OUT (PAD_I2CM_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b20, PAD_I2CM_CK_OUT, BIT0),
    _RVM1(0x2b22, PAD_I2CM_CK_OEN, BIT0),
    //reg_fastuartmode
    _RVM1(0x1e04, 0, BIT5 | BIT4 ),   //reg[101e04]#5 ~ #4 = 00b
    //reg_odfastuart
    _RVM1(0x1ea9, 0, BIT7 | BIT6 ),   //reg[101ea9]#7 ~ #6 = 00b
    //reg_miic_mode0
    _RVM1(0x1edc, 0, BIT0 ),   //reg[101edc]#0 = 0b
    #endif

    #if(PAD_I2CM_DA_IS_GPIO != GPIO_NONE)
    #define PAD_I2CM_DA_OEN (PAD_I2CM_DA_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_I2CM_DA_OUT (PAD_I2CM_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x2b20, PAD_I2CM_DA_OUT, BIT1),
    _RVM1(0x2b22, PAD_I2CM_DA_OEN, BIT1),
    //reg_fastuartmode
    _RVM1(0x1e04, 0, BIT5 | BIT4 ),   //reg[101e04]#5 ~ #4 = 00b
    //reg_odfastuart
    _RVM1(0x1ea9, 0, BIT7 | BIT6 ),   //reg[101ea9]#7 ~ #6 = 00b
    //reg_miic_mode0
    _RVM1(0x1edc, 0, BIT0 ),   //reg[101edc]#0 = 0b
    #endif

    #if(PAD_SM_VCC_IS_GPIO != GPIO_NONE)
    #define PAD_SM_VCC_OEN (PAD_SM_VCC_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_SM_VCC_OUT (PAD_SM_VCC_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x2b38, PAD_SM_VCC_OUT, BIT5),
    _RVM1(0x2b3a, PAD_SM_VCC_OEN, BIT5),
    //reg_sm_config
    _RVM1(0x1edc, 0, BIT5 | BIT4 ),   //reg[101edc]#5 ~ #4 = 00b
    #endif

    #if(PAD_SM_CD_IS_GPIO != GPIO_NONE)
    #define PAD_SM_CD_OEN (PAD_SM_CD_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_SM_CD_OUT (PAD_SM_CD_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2b38, PAD_SM_CD_OUT, BIT4),
    _RVM1(0x2b3a, PAD_SM_CD_OEN, BIT4),
    //reg_sm_config
    _RVM1(0x1edc, 0, BIT5 | BIT4 ),   //reg[101edc]#5 ~ #4 = 00b
    #endif

    #if(PAD_SM_VSEL_IS_GPIO != GPIO_NONE)
    #define PAD_SM_VSEL_OEN (PAD_SM_VSEL_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_SM_VSEL_OUT (PAD_SM_VSEL_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x2b38, PAD_SM_VSEL_OUT, BIT3),
    _RVM1(0x2b3a, PAD_SM_VSEL_OEN, BIT3),
    //reg_sm_config
    _RVM1(0x1edc, 0, BIT5 | BIT4 ),   //reg[101edc]#5 ~ #4 = 00b
    #endif

    #if(PAD_SM_IO_IS_GPIO != GPIO_NONE)
    #define PAD_SM_IO_OEN (PAD_SM_IO_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_SM_IO_OUT (PAD_SM_IO_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x2b38, PAD_SM_IO_OUT, BIT2),
    _RVM1(0x2b3a, PAD_SM_IO_OEN, BIT2),
    //reg_sm_config
    _RVM1(0x1edc, 0, BIT5 | BIT4 ),   //reg[101edc]#5 ~ #4 = 00b
    #endif

    #if(PAD_SM_RST_IS_GPIO != GPIO_NONE)
    #define PAD_SM_RST_OEN (PAD_SM_RST_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_SM_RST_OUT (PAD_SM_RST_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x2b38, PAD_SM_RST_OUT, BIT1),
    _RVM1(0x2b3a, PAD_SM_RST_OEN, BIT1),
    //reg_thirduartmode
    _RVM1(0x1e05, 0, BIT3 | BIT2 ),   //reg[101e05]#3 ~ #2 = 00b
    //reg_od3rduart
    _RVM1(0x1ea9, 0, BIT3 | BIT2 ),   //reg[101ea9]#3 ~ #2 = 00b
    //reg_sm_config
    _RVM1(0x1edc, 0, BIT5 | BIT4 ),   //reg[101edc]#5 ~ #4 = 00b
    #endif

    #if(PAD_SM_CLK_IS_GPIO != GPIO_NONE)
    #define PAD_SM_CLK_OEN (PAD_SM_CLK_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_SM_CLK_OUT (PAD_SM_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b38, PAD_SM_CLK_OUT, BIT0),
    _RVM1(0x2b3a, PAD_SM_CLK_OEN, BIT0),
    //reg_thirduartmode
    _RVM1(0x1e05, 0, BIT3 | BIT2 ),   //reg[101e05]#3 ~ #2 = 00b
    //reg_od3rduart
    _RVM1(0x1ea9, 0, BIT3 | BIT2 ),   //reg[101ea9]#3 ~ #2 = 00b
    //reg_sm_config
    _RVM1(0x1edc, 0, BIT5 | BIT4 ),   //reg[101edc]#5 ~ #4 = 00b
    #endif

    #if(PAD_TS_D7_IS_GPIO != GPIO_NONE)
    #define PAD_TS_D7_OEN (PAD_TS_D7_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_TS_D7_OUT (PAD_TS_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x2b07, PAD_TS_D7_OUT, BIT2),
    _RVM1(0x2b09, PAD_TS_D7_OEN, BIT2),
    //reg_ts0config
    _RVM1(0x1eaf, 0, BIT2|BIT1|BIT0 ),   //reg[101eaf]#2 ~ #0 = 000b
    #endif

    #if(PAD_TS_D6_IS_GPIO != GPIO_NONE)
    #define PAD_TS_D6_OEN (PAD_TS_D6_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_TS_D6_OUT (PAD_TS_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x2b07, PAD_TS_D6_OUT, BIT1),
    _RVM1(0x2b09, PAD_TS_D6_OEN, BIT1),
    //reg_ts0config
    _RVM1(0x1eaf, 0, BIT2|BIT1|BIT0 ),   //reg[101eaf]#2 ~ #0 = 000b
    //reg_fastuartmode
    _RVM1(0x1e04, 0, BIT5 | BIT4 ),   //reg[101e04]#5 ~ #4 = 00b
    //reg_odfastuart
    _RVM1(0x1ea9, 0, BIT7 | BIT6 ),   //reg[101ea9]#7 ~ #6 = 00b
    #endif

    #if(PAD_TS_D5_IS_GPIO != GPIO_NONE)
    #define PAD_TS_D5_OEN (PAD_TS_D5_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_TS_D5_OUT (PAD_TS_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b07, PAD_TS_D5_OUT, BIT0),
    _RVM1(0x2b09, PAD_TS_D5_OEN, BIT0),
    //reg_ts0config
    _RVM1(0x1eaf, 0, BIT2|BIT1|BIT0 ),   //reg[101eaf]#2 ~ #0 = 000b
    //reg_fastuartmode
    _RVM1(0x1e04, 0, BIT5 | BIT4 ),   //reg[101e04]#5 ~ #4 = 00b
    //reg_odfastuart
    _RVM1(0x1ea9, 0, BIT7 | BIT6 ),   //reg[101ea9]#7 ~ #6 = 00b
    #endif

    #if(PAD_TS_D4_IS_GPIO != GPIO_NONE)
    #define PAD_TS_D4_OEN (PAD_TS_D4_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_TS_D4_OUT (PAD_TS_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x2b06, PAD_TS_D4_OUT, BIT7),
    _RVM1(0x2b08, PAD_TS_D4_OEN, BIT7),
    //reg_ts0config
    _RVM1(0x1eaf, 0, BIT2|BIT1|BIT0 ),   //reg[101eaf]#2 ~ #0 = 000b
    //reg_fourthuartmode
    _RVM1(0x1e04, 0, BIT7 | BIT6 ),   //reg[101e04]#7 ~ #6 = 00b
    //reg_od4thuart
    _RVM1(0x1ea9, 0, BIT5 | BIT4 ),   //reg[101ea9]#5 ~ #4 = 00b
    #endif

    #if(PAD_TS_D3_IS_GPIO != GPIO_NONE)
    #define PAD_TS_D3_OEN (PAD_TS_D3_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_TS_D3_OUT (PAD_TS_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x2b06, PAD_TS_D3_OUT, BIT6),
    _RVM1(0x2b08, PAD_TS_D3_OEN, BIT6),
    //reg_ts0config
    _RVM1(0x1eaf, 0, BIT2|BIT1|BIT0 ),   //reg[101eaf]#2 ~ #0 = 000b
    //reg_fourthuartmode
    _RVM1(0x1e04, 0, BIT7 | BIT6 ),   //reg[101e04]#7 ~ #6 = 00b
    //reg_od4thuart
    _RVM1(0x1ea9, 0, BIT5 | BIT4 ),   //reg[101ea9]#5 ~ #4 = 00b
    #endif

    #if(PAD_TS_D2_IS_GPIO != GPIO_NONE)
    #define PAD_TS_D2_OEN (PAD_TS_D2_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS_D2_OUT (PAD_TS_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x2b06, PAD_TS_D2_OUT, BIT5),
    _RVM1(0x2b08, PAD_TS_D2_OEN, BIT5),
    //reg_ts0config
    _RVM1(0x1eaf, 0, BIT2|BIT1|BIT0 ),   //reg[101eaf]#2 ~ #0 = 000b
    #endif

    #if(PAD_TS_D1_IS_GPIO != GPIO_NONE)
    #define PAD_TS_D1_OEN (PAD_TS_D1_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_TS_D1_OUT (PAD_TS_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2b06, PAD_TS_D1_OUT, BIT4),
    _RVM1(0x2b08, PAD_TS_D1_OEN, BIT4),
    //reg_ts0config
    _RVM1(0x1eaf, 0, BIT2|BIT1|BIT0 ),   //reg[101eaf]#2 ~ #0 = 000b
    #endif

    #if(PAD_TS_D0_IS_GPIO != GPIO_NONE)
    #define PAD_TS_D0_OEN (PAD_TS_D0_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_TS_D0_OUT (PAD_TS_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x2b06, PAD_TS_D0_OUT, BIT3),
    _RVM1(0x2b08, PAD_TS_D0_OEN, BIT3),
    //reg_ts0config
    _RVM1(0x1eaf, 0, BIT2|BIT1|BIT0 ),   //reg[101eaf]#2 ~ #0 = 000b
    //reg_spi_ts_config
    _RVM1(0x1eb4, 0, BIT3 ),   //reg[101eb4]#3 = 0b
    //reg_mcu_jtag_mode
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 00b
    //reg_dspejtagmode
    _RVM1(0x1e07, 0, BIT2|BIT1|BIT0 ),   //reg[101e07]#2 ~ #0 = 000b
    #endif

    #if(PAD_TS_SYNC_IS_GPIO != GPIO_NONE)
    #define PAD_TS_SYNC_OEN (PAD_TS_SYNC_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_TS_SYNC_OUT (PAD_TS_SYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x2b06, PAD_TS_SYNC_OUT, BIT1),
    _RVM1(0x2b08, PAD_TS_SYNC_OEN, BIT1),
    //reg_ts0config
    _RVM1(0x1eaf, 0, BIT2|BIT1|BIT0 ),   //reg[101eaf]#2 ~ #0 = 000b
    //reg_spi_ts_config
    _RVM1(0x1eb4, 0, BIT3 ),   //reg[101eb4]#3 = 0b
    //reg_mcu_jtag_mode
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 00b
    //reg_dspejtagmode
    _RVM1(0x1e07, 0, BIT2|BIT1|BIT0 ),   //reg[101e07]#2 ~ #0 = 000b
    #endif

    #if(PAD_TS_VLD_IS_GPIO != GPIO_NONE)
    #define PAD_TS_VLD_OEN (PAD_TS_VLD_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_TS_VLD_OUT (PAD_TS_VLD_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b06, PAD_TS_VLD_OUT, BIT0),
    _RVM1(0x2b08, PAD_TS_VLD_OEN, BIT0),
    //reg_ts0config
    _RVM1(0x1eaf, 0, BIT2|BIT1|BIT0 ),   //reg[101eaf]#2 ~ #0 = 000b
    //reg_spi_ts_config
    _RVM1(0x1eb4, 0, BIT3 ),   //reg[101eb4]#3 = 0b
    //reg_mcu_jtag_mode
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 00b
    //reg_dspejtagmode
    _RVM1(0x1e07, 0, BIT2|BIT1|BIT0 ),   //reg[101e07]#2 ~ #0 = 000b
    #endif

    #if(PAD_TS_CLK_IS_GPIO != GPIO_NONE)
    #define PAD_TS_CLK_OEN (PAD_TS_CLK_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_TS_CLK_OUT (PAD_TS_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x2b06, PAD_TS_CLK_OUT, BIT2),
    _RVM1(0x2b08, PAD_TS_CLK_OEN, BIT2),
    //reg_ts0config
    _RVM1(0x1eaf, 0, BIT2|BIT1|BIT0 ),   //reg[101eaf]#2 ~ #0 = 000b
    //reg_spi_ts_config
    _RVM1(0x1eb4, 0, BIT3 ),   //reg[101eb4]#3 = 0b
    //reg_mcu_jtag_mode
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 00b
    //reg_dspejtagmode
    _RVM1(0x1e07, 0, BIT2|BIT1|BIT0 ),   //reg[101e07]#2 ~ #0 = 000b
    #endif

    #if(PAD_EJ_TRST_N_IS_GPIO != GPIO_NONE)
    #define PAD_EJ_TRST_N_OEN (PAD_EJ_TRST_N_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_EJ_TRST_N_OUT (PAD_EJ_TRST_N_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b32, PAD_EJ_TRST_N_OUT, BIT0),
    _RVM1(0x2b34, PAD_EJ_TRST_N_OEN, BIT0),
    //reg_ej_config_o[1:0]
    _RVM1(0x1e05, 0, BIT5 | BIT4 ),   //reg[101e05]#5 ~ #4 = 00b
    //reg_ej_config_x[1:0]
    _RVM1(0x1e27, 0, BIT1 | BIT0 ),   //reg[101e27]#1 ~ #0 = 00b
    #endif

    #if(PAD_EJ_TDO_IS_GPIO != GPIO_NONE)
    #define PAD_EJ_TDO_OEN (PAD_EJ_TDO_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_EJ_TDO_OUT (PAD_EJ_TDO_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x2b32, PAD_EJ_TDO_OUT, BIT1),
    _RVM1(0x2b34, PAD_EJ_TDO_OEN, BIT1),
    //reg_ej_config_o[1:0]
    _RVM1(0x1e05, 0, BIT5 | BIT4 ),   //reg[101e05]#5 ~ #4 = 00b
    //reg_ej_config_x[1:0]
    _RVM1(0x1e27, 0, BIT1 | BIT0 ),   //reg[101e27]#1 ~ #0 = 00b
    //reg_mcu_jtag_mode
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 00b
    //reg_dspejtagmode
    _RVM1(0x1e07, 0, BIT2|BIT1|BIT0 ),   //reg[101e07]#2 ~ #0 = 000b
    //reg_thirduartmode
    _RVM1(0x1e05, 0, BIT3 | BIT2 ),   //reg[101e05]#3 ~ #2 = 00b
    //reg_od3rduart
    _RVM1(0x1ea9, 0, BIT3 | BIT2 ),   //reg[101ea9]#3 ~ #2 = 00b
    #endif

    #if(PAD_EJ_TCK_IS_GPIO != GPIO_NONE)
    #define PAD_EJ_TCK_OEN (PAD_EJ_TCK_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_EJ_TCK_OUT (PAD_EJ_TCK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x2b32, PAD_EJ_TCK_OUT, BIT2),
    _RVM1(0x2b34, PAD_EJ_TCK_OEN, BIT2),
    //reg_ej_config_o[1:0]
    _RVM1(0x1e05, 0, BIT5 | BIT4 ),   //reg[101e05]#5 ~ #4 = 00b
    //reg_ej_config_x[1:0]
    _RVM1(0x1e27, 0, BIT1 | BIT0 ),   //reg[101e27]#1 ~ #0 = 00b
    //reg_mcu_jtag_mode
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 00b
    //reg_dspejtagmode
    _RVM1(0x1e07, 0, BIT2|BIT1|BIT0 ),   //reg[101e07]#2 ~ #0 = 000b
    #endif

    #if(PAD_EJ_TDI_IS_GPIO != GPIO_NONE)
    #define PAD_EJ_TDI_OEN (PAD_EJ_TDI_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_EJ_TDI_OUT (PAD_EJ_TDI_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x2b32, PAD_EJ_TDI_OUT, BIT3),
    _RVM1(0x2b34, PAD_EJ_TDI_OEN, BIT3),
    //reg_ej_config_o[1:0]
    _RVM1(0x1e05, 0, BIT5 | BIT4 ),   //reg[101e05]#5 ~ #4 = 00b
    //reg_ej_config_x[1:0]
    _RVM1(0x1e27, 0, BIT1 | BIT0 ),   //reg[101e27]#1 ~ #0 = 00b
    //reg_mcu_jtag_mode
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 00b
    //reg_dspejtagmode
    _RVM1(0x1e07, 0, BIT2|BIT1|BIT0 ),   //reg[101e07]#2 ~ #0 = 000b
    //reg_thirduartmode
    _RVM1(0x1e05, 0, BIT3 | BIT2 ),   //reg[101e05]#3 ~ #2 = 00b
    //reg_od3rduart
    _RVM1(0x1ea9, 0, BIT3 | BIT2 ),   //reg[101ea9]#3 ~ #2 = 00b
    #endif

    #if(PAD_EJ_DINT_IS_GPIO != GPIO_NONE)
    #define PAD_EJ_DINT_OEN (PAD_EJ_DINT_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_EJ_DINT_OUT (PAD_EJ_DINT_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2b32, PAD_EJ_DINT_OUT, BIT4),
    _RVM1(0x2b34, PAD_EJ_DINT_OEN, BIT4),
    //reg_ej_config_o[1:0]
    _RVM1(0x1e05, 0, BIT5 | BIT4 ),   //reg[101e05]#5 ~ #4 = 00b
    //reg_ej_config_x[1:0]
    _RVM1(0x1e27, 0, BIT1 | BIT0 ),   //reg[101e27]#1 ~ #0 = 00b
    #endif

    #if(PAD_EJ_RSTZ_IS_GPIO != GPIO_NONE)
    #define PAD_EJ_RSTZ_OEN (PAD_EJ_RSTZ_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_EJ_RSTZ_OUT (PAD_EJ_RSTZ_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x2b32, PAD_EJ_RSTZ_OUT, BIT5),
    _RVM1(0x2b34, PAD_EJ_RSTZ_OEN, BIT5),
    //reg_ej_config_o[1:0]
    _RVM1(0x1e05, 0, BIT5 | BIT4 ),   //reg[101e05]#5 ~ #4 = 00b
    //reg_ej_config_x[1:0]
    _RVM1(0x1e27, 0, BIT1 | BIT0 ),   //reg[101e27]#1 ~ #0 = 00b
    #endif

    #if(PAD_EJ_TMS_IS_GPIO != GPIO_NONE)
    #define PAD_EJ_TMS_OEN (PAD_EJ_TMS_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_EJ_TMS_OUT (PAD_EJ_TMS_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x2b32, PAD_EJ_TMS_OUT, BIT6),
    _RVM1(0x2b34, PAD_EJ_TMS_OEN, BIT6),
    //reg_ej_config_o[1:0]
    _RVM1(0x1e05, 0, BIT5 | BIT4 ),   //reg[101e05]#5 ~ #4 = 00b
    //reg_ej_config_x[1:0]
    _RVM1(0x1e27, 0, BIT1 | BIT0 ),   //reg[101e27]#1 ~ #0 = 00b
    //reg_mcu_jtag_mode
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 00b
    //reg_dspejtagmode
    _RVM1(0x1e07, 0, BIT2|BIT1|BIT0 ),   //reg[101e07]#2 ~ #0 = 000b
    #endif

    #if(PAD_I2S_IN_WS_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_IN_WS_OEN (PAD_I2S_IN_WS_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_I2S_IN_WS_OUT (PAD_I2S_IN_WS_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b0d, PAD_I2S_IN_WS_OUT, BIT0),
    _RVM1(0x2b0f, PAD_I2S_IN_WS_OEN, BIT0),
    //reg_i2sinconfig
    _RVM1(0x1eae, 0, BIT2 ),   //reg[101eae]#2 = 0b
    //reg_fastuartmode
    _RVM1(0x1e04, 0, BIT5 | BIT4 ),   //reg[101e04]#5 ~ #4 = 00b
    //reg_odfastuart
    _RVM1(0x1ea9, 0, BIT7 | BIT6 ),   //reg[101ea9]#7 ~ #6 = 00b
    #endif

    #if(PAD_I2S_IN_SD_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_IN_SD_OEN (PAD_I2S_IN_SD_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_I2S_IN_SD_OUT (PAD_I2S_IN_SD_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x2b0d, PAD_I2S_IN_SD_OUT, BIT2),
    _RVM1(0x2b0f, PAD_I2S_IN_SD_OEN, BIT2),
    //reg_i2sinconfig
    _RVM1(0x1eae, 0, BIT2 ),   //reg[101eae]#2 = 0b
    #endif

    #if(PAD_I2S_IN_BCK_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_IN_BCK_OEN (PAD_I2S_IN_BCK_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_I2S_IN_BCK_OUT (PAD_I2S_IN_BCK_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x2b0d, PAD_I2S_IN_BCK_OUT, BIT1),
    _RVM1(0x2b0f, PAD_I2S_IN_BCK_OEN, BIT1),
    //reg_i2sinconfig
    _RVM1(0x1eae, 0, BIT2 ),   //reg[101eae]#2 = 0b
    //reg_i2soutconfig0
    _RVM1(0x1eae, 0, BIT4 ),   //reg[101eae]#4 = 0b
    //reg_fastuartmode
    _RVM1(0x1e04, 0, BIT5 | BIT4 ),   //reg[101e04]#5 ~ #4 = 00b
    //reg_odfastuart
    _RVM1(0x1ea9, 0, BIT7 | BIT6 ),   //reg[101ea9]#7 ~ #6 = 00b
    #endif

    #if(PAD_I2S_OUT_MCK_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_MCK_OEN (PAD_I2S_OUT_MCK_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_I2S_OUT_MCK_OUT (PAD_I2S_OUT_MCK_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x2b0c, PAD_I2S_OUT_MCK_OUT, BIT1),
    _RVM1(0x2b0e, PAD_I2S_OUT_MCK_OEN, BIT1),
    //reg_i2soutconfig0
    _RVM1(0x1eae, 0, BIT4 ),   //reg[101eae]#4 = 0b
    #endif

    #if(PAD_I2S_OUT_WS_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_WS_OEN (PAD_I2S_OUT_WS_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_I2S_OUT_WS_OUT (PAD_I2S_OUT_WS_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x2b0c, PAD_I2S_OUT_WS_OUT, BIT2),
    _RVM1(0x2b0e, PAD_I2S_OUT_WS_OEN, BIT2),
    //reg_i2soutconfig0
    _RVM1(0x1eae, 0, BIT4 ),   //reg[101eae]#4 = 0b
    #endif

    #if(PAD_I2S_OUT_MUTE_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_MUTE_OEN (PAD_I2S_OUT_MUTE_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_I2S_OUT_MUTE_OUT (PAD_I2S_OUT_MUTE_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x2b0c, PAD_I2S_OUT_MUTE_OUT, BIT7),
    _RVM1(0x2b0e, PAD_I2S_OUT_MUTE_OEN, BIT7),
    //reg_i2smutemode
    _RVM1(0x1e05, 0, BIT7 | BIT6 ),   //reg[101e05]#7 ~ #6 = 00b
    //reg_mcu_jtag_mode
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 00b
    //reg_dspejtagmode
    _RVM1(0x1e07, 0, BIT2|BIT1|BIT0 ),   //reg[101e07]#2 ~ #0 = 000b
    //reg_thirduartmode
    _RVM1(0x1e05, 0, BIT3 | BIT2 ),   //reg[101e05]#3 ~ #2 = 00b
    //reg_od3rduart
    _RVM1(0x1ea9, 0, BIT3 | BIT2 ),   //reg[101ea9]#3 ~ #2 = 00b
    #endif

    #if(PAD_I2S_OUT_SD_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_SD_OEN (PAD_I2S_OUT_SD_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_I2S_OUT_SD_OUT (PAD_I2S_OUT_SD_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x2b0c, PAD_I2S_OUT_SD_OUT, BIT3),
    _RVM1(0x2b0e, PAD_I2S_OUT_SD_OEN, BIT3),
    //reg_i2soutconfig1
    _RVM1(0x1eae, 0, BIT5 ),   //reg[101eae]#5 = 0b
    #endif

    #if(PAD_I2S_OUT_SD1_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_SD1_OEN (PAD_I2S_OUT_SD1_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_I2S_OUT_SD1_OUT (PAD_I2S_OUT_SD1_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2b0c, PAD_I2S_OUT_SD1_OUT, BIT4),
    _RVM1(0x2b0e, PAD_I2S_OUT_SD1_OEN, BIT4),
    //reg_i2soutconfig2
    _RVM1(0x1eb3, 0, BIT3 ),   //reg[101eb3]#3 = 0b
    //reg_mcu_jtag_mode
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 00b
    //reg_dspejtagmode
    _RVM1(0x1e07, 0, BIT2|BIT1|BIT0 ),   //reg[101e07]#2 ~ #0 = 000b
    //reg_seconduartmode
    _RVM1(0x1e05, 0, BIT1 | BIT0 ),   //reg[101e05]#1 ~ #0 = 00b
    //reg_od2nduart
    _RVM1(0x1ea9, 0, BIT1 | BIT0 ),   //reg[101ea9]#1 ~ #0 = 00b
    //reg_miic_mode3
    _RVM1(0x1edc, 0, BIT3 ),   //reg[101edc]#3 = 0b
    #endif

    #if(PAD_I2S_OUT_SD2_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_SD2_OEN (PAD_I2S_OUT_SD2_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_I2S_OUT_SD2_OUT (PAD_I2S_OUT_SD2_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x2b0c, PAD_I2S_OUT_SD2_OUT, BIT5),
    _RVM1(0x2b0e, PAD_I2S_OUT_SD2_OEN, BIT5),
    //reg_i2soutconfig3
    _RVM1(0x1eb3, 0, BIT4 ),   //reg[101eb3]#4 = 0b
    //reg_mcu_jtag_mode
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 00b
    //reg_dspejtagmode
    _RVM1(0x1e07, 0, BIT2|BIT1|BIT0 ),   //reg[101e07]#2 ~ #0 = 000b
    //reg_seconduartmode
    _RVM1(0x1e05, 0, BIT1 | BIT0 ),   //reg[101e05]#1 ~ #0 = 00b
    //reg_od2nduart
    _RVM1(0x1ea9, 0, BIT1 | BIT0 ),   //reg[101ea9]#1 ~ #0 = 00b
    //reg_miic_mode3
    _RVM1(0x1edc, 0, BIT3 ),   //reg[101edc]#3 = 0b
    #endif

    #if(PAD_I2S_OUT_SD3_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_SD3_OEN (PAD_I2S_OUT_SD3_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_I2S_OUT_SD3_OUT (PAD_I2S_OUT_SD3_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x2b0c, PAD_I2S_OUT_SD3_OUT, BIT6),
    _RVM1(0x2b0e, PAD_I2S_OUT_SD3_OEN, BIT6),
    //reg_i2soutconfig4
    _RVM1(0x1eb3, 0, BIT5 ),   //reg[101eb3]#5 = 0b
    //reg_mcu_jtag_mode
    _RVM1(0x1ede, 0, BIT3 | BIT2 ),   //reg[101ede]#3 ~ #2 = 00b
    //reg_dspejtagmode
    _RVM1(0x1e07, 0, BIT2|BIT1|BIT0 ),   //reg[101e07]#2 ~ #0 = 000b
    //reg_thirduartmode
    _RVM1(0x1e05, 0, BIT3 | BIT2 ),   //reg[101e05]#3 ~ #2 = 00b
    //reg_od3rduart
    _RVM1(0x1ea9, 0, BIT3 | BIT2 ),   //reg[101ea9]#3 ~ #2 = 00b
    #endif

    #if(PAD_I2S_OUT_BCK_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_BCK_OEN (PAD_I2S_OUT_BCK_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_I2S_OUT_BCK_OUT (PAD_I2S_OUT_BCK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b0c, PAD_I2S_OUT_BCK_OUT, BIT0),
    _RVM1(0x2b0e, PAD_I2S_OUT_BCK_OEN, BIT0),
    #endif

    #if(PAD_SPDIF_OUT_IS_GPIO != GPIO_NONE)
    #define PAD_SPDIF_OUT_OEN (PAD_SPDIF_OUT_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_SPDIF_OUT_OUT (PAD_SPDIF_OUT_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b2c, PAD_SPDIF_OUT_OUT, BIT0),
    _RVM1(0x2b2e, PAD_SPDIF_OUT_OEN, BIT0),
    //reg_spdifoutconfig
    _RVM1(0x1eae, 0, BIT7 ),   //reg[101eae]#7 = 0
    //reg_seconduartmode
    _RVM1(0x1e05, 0, BIT1 | BIT0 ),   //reg[101e05]#1 ~ #0 = 00b
    //reg_od2nduart
    _RVM1(0x1ea9, 0, BIT1 | BIT0 ),   //reg[101ea9]#1 ~ #0 = 00b
    //reg_miic_mode2
    _RVM1(0x1edc, 0, BIT2 ),   //reg[101edc]#2 = 0b
    #endif

    #if(PAD_SPDIF_IN_IS_GPIO != GPIO_NONE)
    #define PAD_SPDIF_IN_OEN (PAD_SPDIF_IN_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_SPDIF_IN_OUT (PAD_SPDIF_IN_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x2b2c, PAD_SPDIF_IN_OUT, BIT1),
    _RVM1(0x2b2e, PAD_SPDIF_IN_OEN, BIT1),
    //reg_spdifinconfig
    _RVM1(0x1eae, 0, BIT6 ),   //reg[101eae]#6 = 0
    //reg_seconduartmode
    _RVM1(0x1e05, 0, BIT1 | BIT0 ),   //reg[101e05]#1 ~ #0 = 00b
    //reg_od2nduart
    _RVM1(0x1ea9, 0, BIT1 | BIT0 ),   //reg[101ea9]#1 ~ #0 = 00b
    //reg_miic_mode2
    _RVM1(0x1edc, 0, BIT2 ),   //reg[101edc]#2 = 0b
    #endif

    #if(PAD_LED0_IS_GPIO != GPIO_NONE)
    #define PAD_LED0_OEN (PAD_LED0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_LED0_OUT (PAD_LED0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b26, PAD_LED0_OUT, BIT0),
    _RVM1(0x2b28, PAD_LED0_OEN, BIT0),
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0 ),   //reg[101edf]#0 = 0
    //reg_led_mode
    _RVM1(0x1eb4, 0, BIT4 ),   //reg[101eb4]#4 = 0b
    #endif

    #if(PAD_LED1_IS_GPIO != GPIO_NONE)
    #define PAD_LED1_OEN (PAD_LED1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_LED1_OUT (PAD_LED1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x2b26, PAD_LED1_OUT, BIT1),
    _RVM1(0x2b28, PAD_LED1_OEN, BIT1),
    //reg_et_mode
    _RVM1(0x1edf, 0, BIT0 ),   //reg[101edf]#0 = 0
    //reg_led_mode
    _RVM1(0x1eb4, 0, BIT4 ),   //reg[101eb4]#4 = 0b
    #endif

    #if(PAD_DDC_CK_IS_GPIO != GPIO_NONE)
    #define PAD_DDC_CK_OEN (PAD_DDC_CK_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_DDC_CK_OUT (PAD_DDC_CK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b20, PAD_DDC_CK_OUT, BIT0),
    _RVM1(0x2b22, PAD_DDC_CK_OEN, BIT0),
    //reg_ddc_hdmi_en
    _RVM1(0x1eae, 0, BIT0 ),   //reg[101eae]#0 = 0b
    //reg_ddc_miic_en
    _RVM1(0x1eae, 0, BIT1 ),   //reg[101eae]#1 = 0b
    #endif

    #if(PAD_DDC_DA_IS_GPIO != GPIO_NONE)
    #define PAD_DDC_DA_OEN (PAD_DDC_DA_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_DDC_DA_OUT (PAD_DDC_DA_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x2b20, PAD_DDC_DA_OUT, BIT1),
    _RVM1(0x2b22, PAD_DDC_DA_OEN, BIT1),
    //reg_ddc_hdmi_en
    _RVM1(0x1eae, 0, BIT0 ),   //reg[101eae]#0 = 0b
    //reg_ddc_miic_en
    _RVM1(0x1eae, 0, BIT1 ),   //reg[101eae]#1 = 0b
    #endif

    #if(PAD_SD_D3_IS_GPIO != GPIO_NONE)
    #define PAD_SD_D3_OEN (PAD_SD_D3_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_SD_D3_OUT (PAD_SD_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2b12, PAD_SD_D3_OUT, BIT0),
    _RVM1(0x2b14, PAD_SD_D3_OEN, BIT0),
    //reg_sd_config
    _RVM1(0x1eb5, 0, BIT1 | BIT0 ),   //reg[101eb5]#1 ~ #0 = 00b
    #endif

    #if(PAD_SD_D2_IS_GPIO != GPIO_NONE)
    #define PAD_SD_D2_OEN (PAD_SD_D2_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_SD_D2_OUT (PAD_SD_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x2b12, PAD_SD_D2_OUT, BIT1),
    _RVM1(0x2b14, PAD_SD_D2_OEN, BIT1),
    //reg_sd_config
    _RVM1(0x1eb5, 0, BIT1 | BIT0 ),   //reg[101eb5]#1 ~ #0 = 00b
    #endif

    #if(PAD_SD_D1_IS_GPIO != GPIO_NONE)
    #define PAD_SD_D1_OEN (PAD_SD_D1_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_SD_D1_OUT (PAD_SD_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x2b12, PAD_SD_D1_OUT, BIT2),
    _RVM1(0x2b14, PAD_SD_D1_OEN, BIT2),
    //reg_sd_config
    _RVM1(0x1eb5, 0, BIT1 | BIT0 ),   //reg[101eb5]#1 ~ #0 = 00b
    #endif

    #if(PAD_SD_D0_IS_GPIO != GPIO_NONE)
    #define PAD_SD_D0_OEN (PAD_SD_D0_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_SD_D0_OUT (PAD_SD_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x2b12, PAD_SD_D0_OUT, BIT3),
    _RVM1(0x2b14, PAD_SD_D0_OEN, BIT3),
    //reg_sd_config
    _RVM1(0x1eb5, 0, BIT1 | BIT0 ),   //reg[101eb5]#1 ~ #0 = 00b
    #endif

    #if(PAD_SD_CMD_IS_GPIO != GPIO_NONE)
    #define PAD_SD_CMD_OEN (PAD_SD_CMD_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_SD_CMD_OUT (PAD_SD_CMD_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2b12, PAD_SD_CMD_OUT, BIT4),
    _RVM1(0x2b14, PAD_SD_CMD_OEN, BIT4),
    //reg_sd_config
    _RVM1(0x1eb5, 0, BIT1 | BIT0 ),   //reg[101eb5]#1 ~ #0 = 00b
    #endif

    #if(PAD_SD_CLK_IS_GPIO != GPIO_NONE)
    #define PAD_SD_CLK_OEN (PAD_SD_CLK_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_SD_CLK_OUT (PAD_SD_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x2b12, PAD_SD_CLK_OUT, BIT5),
    _RVM1(0x2b14, PAD_SD_CLK_OEN, BIT5),
    //reg_sd_config
    _RVM1(0x1eb5, 0, BIT1 | BIT0 ),   //reg[101eb5]#1 ~ #0 = 00b
    #endif

    _MEMMAP_PM_,

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
//---------------------------------------------------------------------
// Pad Configuartion
//---------------------------------------------------------------------
#ifdef PADS_TS0_CONFIG
    #if (PADS_TS0_CONFIG != UNKNOWN_PAD_MUX)
    #define _CONFIG_TS0_CONFIG  ((PADS_TS0_CONFIG == PARALLEL_IN) ? BIT0: \
                                 (PADS_TS0_CONFIG == SERIAL_IN) ? BIT1 : 0)
        _RVM1(0x1eaf, _CONFIG_TS0_CONFIG, BITMASK(1:0)),
    #endif
#endif

#ifdef PADS_NAND_MODE
    #if (PADS_NAND_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_NAND_MODE   ((PADS_NAND_MODE == PAD_NAND_AD) ? BIT6 : 0)
        _RVM1(0x1ede, _CONFIG_NAND_MODE, (BIT7 | BIT6)),

	//pe for pad_nand_ad
   	#if (PADS_NAND_MODE == PAD_NAND_AD)
        _RVM1(0x1e1a, BITMASK(7:0), BITMASK(7:0)),
	#endif

    #else
        _RVM1(0x1ede, 0, (BIT7 | BIT6)),
    #endif
#endif

#ifdef PADS_NAND_CS1_EN
    #if (PADS_NAND_CS1_EN != UNKNOWN_PAD_MUX)
    #define _CONFIG_NAND_CS1_EN ((PADS_NAND_CS1_EN == ENABLE) ? BIT5 : 0)
        _RVM1(0x1ede, _CONFIG_NAND_CS1_EN, BIT5),
    #endif
#endif

#ifdef PADS_SPDIF_OUT
    #if (PADS_SPDIF_OUT != UNKNOWN_PAD_MUX)
    #define _CONFIG_SPDIF_OUT   ((PADS_SPDIF_OUT == ENABLE) ? BIT7 : 0)
        _RVM1(0x1eae, _CONFIG_SPDIF_OUT, BIT7),
    #endif
#endif

#ifdef PADS_SPDIF_IN
    #if (PADS_SPDIF_IN != UNKNOWN_PAD_MUX)
    #define _CONFIG_SPDIF_IN    ((PADS_SPDIF_IN == ENABLE) ? BIT6 : 0)
        _RVM1(0x1eae, _CONFIG_SPDIF_IN, BIT6),
    #endif
#endif

#ifdef PADS_I2S_IN
    #if (PADS_I2S_IN != UNKNOWN_PAD_MUX)
    #define _CONFIG_I2S_IN  ((PADS_I2S_IN == ENABLE) ? BIT2 : 0)
        _RVM1(0x1eae, _CONFIG_I2S_IN, BIT2),
    #endif
#endif

#ifdef PADS_I2S_MUTE
    #if (PADS_I2S_MUTE != UNKNOWN_PAD_MUX)
    #define _CONFIG_I2S_MUTE    ((PADS_I2S_MUTE == PAD_GPIO15) ? BIT6: \
                                 (PADS_I2S_MUTE == PAD_PWM4) ? BIT7 : 0)
        _RVM1(0x1e05, _CONFIG_I2S_MUTE, (BIT7 | BIT6)),
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
    #define _CONFIG_I2S_OUT_SD ((PADS_I2S_OUT_SD == ENABLE) ? BIT5 : 0)
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

#ifdef PADS_ET_MODE
    #if (PADS_ET_MODE != UNKNOWN_PAD_MUX)           //for External Ethernet PHY
    #define _CONFIG_ET_MODE     ((PADS_ET_MODE == ENABLE) ? BIT0 : 0)
        _RVM1(0x1edf, _CONFIG_ET_MODE, BIT0),
    #endif
#endif

#ifdef PADS_LED_MODE
    #if (PADS_LED_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_LED_MODE    ((PADS_LED_MODE == ENABLE) ? BIT4 : 0)
        _RVM1(0x1eb4, _CONFIG_LED_MODE, BIT4),
    #endif
#endif

#ifdef PADS_MSPI_MODE
    #if (PADS_MSPI_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_MSPI_MODE   ((PADS_MSPI_MODE == PAD_SPI1) ? BIT0 : \
                                 (PADS_MSPI_MODE == PAD_SPI2) ? BIT1 : \
                                 (PADS_MSPI_MODE == PAD_SPI3) ? BIT2 : \
                                 (PADS_MSPI_MODE == PAD_SPI4) ? BIT3 : 0)
        _RVM1(0x1eb4, _CONFIG_MSPI_MODE, (BIT3 | BIT2 | BIT1 | BIT0)),
    #endif
#endif

#ifdef PADS_UART2_MODE
    #if (PADS_UART2_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_UART2_MODE  ((PADS_UART2_MODE == PAD_SPDIF_OUT) ? BIT0 : \
                                 (PADS_UART2_MODE == PAD_SPDIF_IN) ? BIT0 : \
                                 (PADS_UART2_MODE == PAD_I2S_OUT_SD1) ? BIT1 : \
                                 (PADS_UART2_MODE == PAD_I2S_OUT_SD2) ? BIT1 : \
                                 (PADS_UART2_MODE == PAD_GPIO0) ? (BIT1 | BIT0) : \
                                 (PADS_UART2_MODE == PAD_GPIO1) ? (BIT1 | BIT0) : 0 )
       _RVM1(0x1e05, _CONFIG_UART2_MODE, (BIT1 | BIT0)),
    #endif
#endif

#ifdef PADS_UART3_MODE
    #if (PADS_UART3_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_UART3_MODE  ((PADS_UART3_MODE == PAD_I2S_OUT_SD3) ? BIT2 : \
                                 (PADS_UART3_MODE == PAD_I2S_OUT_MUTE) ? BIT2 : \
                                 (PADS_UART3_MODE == PAD_SM_CLK) ? BIT3 : \
                                 (PADS_UART3_MODE == PAD_SM_RST) ? BIT3 : \
                                 (PADS_UART3_MODE == PAD_EJ_TDO) ? (BIT3 | BIT2) : \
                                 (PADS_UART3_MODE == PAD_EJ_TDI) ? (BIT3 | BIT2) : 0 )
        _RVM1(0x1e05, _CONFIG_UART3_MODE, (BIT3 | BIT2)),
    #endif
#endif

#ifdef PADS_UART4_MODE
    #if (PADS_UART4_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_UART4_MODE  ((PADS_UART4_MODE == PAD_TS_D3) ? BIT6 : \
                                 (PADS_UART4_MODE == PAD_TS_D4) ? BIT6 : \
                                 (PADS_UART4_MODE == PAD_GPIO0) ? BIT7 : \
                                 (PADS_UART4_MODE == PAD_GPIO1) ? BIT7 : 0 )
        _RVM1(0x1e04, _CONFIG_UART4_MODE, (BIT7 | BIT6)),
    #endif
#endif

#ifdef PADS_UART5_MODE
    #if (PADS_UART5_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_UART5_MODE  ((PADS_UART5_MODE == PAD_GPIO2) ? BIT2: \
                                 (PADS_UART5_MODE == PAD_GPIO3) ? BIT2: \
                                 (PADS_UART5_MODE == PAD_GPIO4) ? BIT3: \
                                 (PADS_UART5_MODE == PAD_GPIO5) ? BIT3: 0 )
        _RVM1(0x1e08, _CONFIG_UART5_MODE, (BIT3 | BIT2)),
    #endif
#endif

#ifdef PADS_UART6_MODE
    #if (PADS_UART6_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_UART6_MODE  ((PADS_UART6_MODE == PAD_GPIO6) ? BIT6: \
                                 (PADS_UART6_MODE == PAD_GPIO7) ? BIT7: 0 )
        _RVM1(0x1e08, _CONFIG_UART6_MODE, (BIT7 | BIT6)),
    #endif
#endif

#ifdef PADS_FAST_UART_MODE
    #if (PADS_FAST_UART_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_FAST_UART_MODE  ((PADS_FAST_UART_MODE == PAD_I2S_IN_WS) ? BIT4 : \
                                     (PADS_FAST_UART_MODE == PAD_I2S_IN_BCK) ? BIT4 : \
                                     (PADS_FAST_UART_MODE == PAD_TS_D5) ? BIT5 : \
                                     (PADS_FAST_UART_MODE == PAD_TS_D6) ? BIT5 : \
                                     (PADS_FAST_UART_MODE == PAD_I2CM_CK) ? (BIT5 | BIT4) : \
                                     (PADS_FAST_UART_MODE == PAD_I2CM_DA) ? (BIT5 | BIT4) : 0 )
        _RVM1(0x1e04, _CONFIG_FAST_UART_MODE, (BIT5 | BIT4)),
    #endif
#endif

#ifdef PADS_OD_UART2_MODE
    #if (PADS_OD_UART2_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_OD_UART2_MODE   ((PADS_OD_UART2_MODE == PAD_SPDIF_OUT) ? BIT0 : \
                                     (PADS_OD_UART2_MODE == PAD_SPDIF_IN) ? BIT0 : \
                                     (PADS_OD_UART2_MODE == PAD_I2S_OUT_SD1) ? BIT1 : \
                                     (PADS_OD_UART2_MODE == PAD_I2S_OUT_SD2) ? BIT1 : \
                                     (PADS_OD_UART2_MODE == PAD_GPIO0) ? (BIT1 | BIT0) : \
                                     (PADS_OD_UART2_MODE == PAD_GPIO1) ? (BIT1 | BIT0) : 0 )
        _RVM1(0x1ea9, _CONFIG_OD_UART2_MODE, (BIT1 | BIT0)),
    #endif
#endif

#ifdef PADS_OD_UART3_MODE
    #if (PADS_OD_UART3_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_OD_UART3_MODE   ((PADS_OD_UART3_MODE == PAD_I2S_OUT_SD3) ? BIT2 : \
                                     (PADS_OD_UART3_MODE == PAD_I2S_OUT_MUTE) ? BIT2 : \
                                     (PADS_OD_UART3_MODE == PAD_SM_CLK) ? BIT3 : \
                                     (PADS_OD_UART3_MODE == PAD_SM_RST) ? BIT3 : \
                                     (PADS_OD_UART3_MODE == PAD_EJ_TDO) ? (BIT3 | BIT2) : \
                                     (PADS_OD_UART3_MODE == PAD_EJ_TDI) ? (BIT3 | BIT2) : 0 )
        _RVM1(0x1ea9, _CONFIG_OD_UART3_MODE, (BIT3 | BIT2)),
    #endif
#endif

#ifdef PADS_OD_UART4_MODE
    #if (PADS_OD_UART4_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_OD_UART4_MODE   ((PADS_OD_UART4_MODE == PAD_TS_D3) ? BIT4 : \
                                     (PADS_OD_UART4_MODE == PAD_TS_D4) ? BIT4 : \
                                     (PADS_OD_UART4_MODE == PAD_GPIO0) ? BIT5 : \
                                     (PADS_OD_UART4_MODE == PAD_GPIO1) ? BIT5 : 0 )
        _RVM1(0x1ea9, _CONFIG_OD_UART4_MODE, (BIT5 | BIT4)),
    #endif
#endif

#ifdef PADS_OD_UART5_MODE
    #if (PADS_OD_UART5_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_OD_UART5_MODE  ((PADS_OD_UART5_MODE == PAD_GPIO2) ? BIT4: \
                                    (PADS_OD_UART5_MODE == PAD_GPIO3) ? BIT4: \
                                    (PADS_OD_UART5_MODE == PAD_GPIO4) ? BIT5: \
                                    (PADS_OD_UART5_MODE == PAD_GPIO5) ? BIT5: 0 )
        _RVM1(0x1eaa, _CONFIG_OD_UART5_MODE, (BIT5 | BIT4)),
    #endif
#endif

#ifdef PADS_OD_UART6_MODE
    #if (PADS_OD_UART6_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_OD_UART6_MODE  ((PADS_OD_UART6_MODE == PAD_GPIO6) ? BIT6: \
                                 (PADS_OD_UART6_MODE == PAD_GPIO7) ? BIT7: 0 )
        _RVM1(0x1eaa, _CONFIG_OD_UART6_MODE, (BIT7 | BIT6)),
    #endif
#endif

#ifdef PADS_OD_FAST_UART_MODE
    #if (PADS_OD_FAST_UART_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_OD_FAST_UART_MODE   ((PADS_OD_FAST_UART_MODE == PAD_I2S_IN_WS) ? BIT6 : \
                                         (PADS_OD_FAST_UART_MODE == PAD_I2S_IN_BCK) ? BIT6 : \
                                         (PADS_OD_FAST_UART_MODE == PAD_TS_D5) ? BIT7 : \
                                         (PADS_OD_FAST_UART_MODE == PAD_TS_D6) ? BIT7 : \
                                         (PADS_OD_FAST_UART_MODE == PAD_I2CM_CK) ? (BIT7 | BIT6) : \
                                         (PADS_OD_FAST_UART_MODE == PAD_I2CM_DA) ? (BIT7 | BIT6) : 0 )
        _RVM1(0x1ea9, _CONFIG_OD_FAST_UART_MODE, (BIT7 | BIT6)),
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
    //_RVM1(0x1ea8, ((UART5_SRC_SEL << 4) | UART4_SRC_SEL), BITMASK(7:0)),

#if ((UART0_SRC_SEL == UART1_SRC_SEL) || \
     (UART0_SRC_SEL == UART2_SRC_SEL) || \
     (UART0_SRC_SEL == UART3_SRC_SEL) || \
     (UART0_SRC_SEL == UART4_SRC_SEL) || \
     (UART0_SRC_SEL == UART5_SRC_SEL) || \
     (UART1_SRC_SEL == UART0_SRC_SEL) || \
     (UART1_SRC_SEL == UART2_SRC_SEL) || \
     (UART1_SRC_SEL == UART3_SRC_SEL) || \
     (UART1_SRC_SEL == UART4_SRC_SEL) || \
     (UART1_SRC_SEL == UART5_SRC_SEL) || \
     (UART2_SRC_SEL == UART0_SRC_SEL) || \
     (UART2_SRC_SEL == UART1_SRC_SEL) || \
     (UART2_SRC_SEL == UART3_SRC_SEL) || \
     (UART2_SRC_SEL == UART4_SRC_SEL) || \
     (UART2_SRC_SEL == UART5_SRC_SEL) || \
     (UART3_SRC_SEL == UART0_SRC_SEL) || \
     (UART3_SRC_SEL == UART1_SRC_SEL) || \
     (UART3_SRC_SEL == UART2_SRC_SEL) || \
     (UART3_SRC_SEL == UART4_SRC_SEL) || \
     (UART3_SRC_SEL == UART5_SRC_SEL) || \
     (UART4_SRC_SEL == UART0_SRC_SEL) || \
     (UART4_SRC_SEL == UART1_SRC_SEL) || \
     (UART4_SRC_SEL == UART2_SRC_SEL) || \
     (UART4_SRC_SEL == UART3_SRC_SEL) || \
     (UART4_SRC_SEL == UART5_SRC_SEL) || \
     (UART5_SRC_SEL == UART0_SRC_SEL) || \
     (UART5_SRC_SEL == UART1_SRC_SEL) || \
     (UART5_SRC_SEL == UART2_SRC_SEL) || \
     (UART5_SRC_SEL == UART3_SRC_SEL) || \
     (UART5_SRC_SEL == UART4_SRC_SEL))
    #error "[ERROR] UART Source Selection Conflict"
#endif

    _MEMMAP_PM_,
    _RVM1(0x0e13, 0, BIT4),         //Select UART Source to reg_uart_sel0
    _RVM1(0x0e13, BIT3, BIT3),      //Enable UART Rx
    _MEMMAP_nonPM_,

#ifdef PADS_MIIC_MODE0
    #if (PADS_MIIC_MODE0 != UNKNOWN_PAD_MUX)
    #define _CONFIG_MIIC_MODE0  ((PADS_MIIC_MODE0 == PAD_GPIO28) ? BIT0 : \
                                 (PADS_MIIC_MODE0 == PAD_GPIO29) ? BIT0 : 0)
        _RVM1(0x1edc, _CONFIG_MIIC_MODE0, BIT0),
    #endif
#endif

#ifdef PADS_MIIC_MODE1
    #if (PADS_MIIC_MODE1 != UNKNOWN_PAD_MUX)
    #define _CONFIG_MIIC_MODE1  ((PADS_MIIC_MODE1 == PAD_TGPIO2) ? BIT1 : \
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

#ifdef PADS_MIIC_MODE3
    #if (PADS_MIIC_MODE3 != UNKNOWN_PAD_MUX)
    #define _CONFIG_MIIC_MODE3  ((PADS_MIIC_MODE3 == PAD_GPIO36) ? BIT3 : \
                                 (PADS_MIIC_MODE3 == PAD_GPIO37) ? BIT3 : 0)
        _RVM1(0x1edc, _CONFIG_MIIC_MODE3, BIT3),
    #endif
#endif

#ifdef PADS_MIIC_MODE4
    #if (PADS_MIIC_MODE4 != UNKNOWN_PAD_MUX)
    #define _CONFIG_MIIC_MODE4  ((PADS_MIIC_MODE4 == PAD_GPIO30) ? BIT0 : \
                                 (PADS_MIIC_MODE4 == PAD_GPIO31) ? BIT0 : 0)
        _RVM1(0x1ede, _CONFIG_MIIC_MODE4, BIT0),
    #endif
#endif

#ifdef PADS_MIIC_MODE5
    #if (PADS_MIIC_MODE5 != UNKNOWN_PAD_MUX)
    #define _CONFIG_MIIC_MODE5  ((PADS_MIIC_MODE5 == PAD_GPIO32) ? BIT1 : \
                                 (PADS_MIIC_MODE5 == PAD_GPIO33) ? BIT1 : 0)
        _RVM1(0x1ede, _CONFIG_MIIC_MODE2, BIT1),
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

#ifdef PADS_EXT_GPIO_INT0
    #if (PADS_EXT_GPIO_INT0 != UNKNOWN_PAD_MUX)
    #define _PADS_EXT_GPIO_INT0   ((PADS_EXT_GPIO_INT0 == ENABLE) ? BIT0 : 0 )
        _RVM1(0x1ea5, _PADS_EXT_GPIO_INT0, BIT0),
    #endif
#endif

#ifdef PADS_EXT_GPIO_INT1
    #if (PADS_EXT_GPIO_INT1 != UNKNOWN_PAD_MUX)
    #define _PADS_EXT_GPIO_INT1   ((PADS_EXT_GPIO_INT1 == ENABLE) ? BIT1 : 0 )
        _RVM1(0x1ea5, _PADS_EXT_GPIO_INT1, BIT1),
    #endif
#endif

#ifdef PADS_EXT_GPIO_INT2
    #if (PADS_EXT_GPIO_INT2 != UNKNOWN_PAD_MUX)
    #define _PADS_EXT_GPIO_INT2   ((PADS_EXT_GPIO_INT2 == ENABLE) ? BIT2 : 0 )
        _RVM1(0x1ea5, _PADS_EXT_GPIO_INT2, BIT2),
    #endif
#endif

#ifdef PADS_EXT_GPIO_INT3
    #if (PADS_EXT_GPIO_INT3 != UNKNOWN_PAD_MUX)
    #define _PADS_EXT_GPIO_INT3   ((PADS_EXT_GPIO_INT3 == ENABLE) ? BIT3 : 0 )
        _RVM1(0x1ea5, _PADS_EXT_GPIO_INT3, BIT3),
    #endif
#endif

#ifdef PADS_EXT_GPIO_INT4
    #if (PADS_EXT_GPIO_INT4 != UNKNOWN_PAD_MUX)
    #define _PADS_EXT_GPIO_INT4   ((PADS_EXT_GPIO_INT4 == ENABLE) ? BIT4 : 0 )
        _RVM1(0x1ea5, _PADS_EXT_GPIO_INT4, BIT4),
    #endif
#endif

#ifdef PADS_EXT_GPIO_INT5
    #if (PADS_EXT_GPIO_INT5 != UNKNOWN_PAD_MUX)
    #define _PADS_EXT_GPIO_INT5   ((PADS_EXT_GPIO_INT5 == ENABLE) ? BIT5 : 0 )
        _RVM1(0x1ea5, _PADS_EXT_GPIO_INT5, BIT5),
    #endif
#endif

#ifdef PADS_EXT_GPIO_INT6
    #if (PADS_EXT_GPIO_INT6 != UNKNOWN_PAD_MUX)
    #define _PADS_EXT_GPIO_INT6   ((PADS_EXT_GPIO_INT6 == ENABLE) ? BIT6 : 0 )
        _RVM1(0x1ea5, _PADS_EXT_GPIO_INT6, BIT6),
    #endif
#endif

#ifdef PADS_EXT_GPIO_INT7
    #if (PADS_EXT_GPIO_INT7 != UNKNOWN_PAD_MUX)
    #define _PADS_EXT_GPIO_INT7   ((PADS_EXT_GPIO_INT7 == ENABLE) ? BIT7 : 0 )
        _RVM1(0x1ea5, _PADS_EXT_GPIO_INT7, BIT7),
    #endif
#endif

#ifdef PADS_PM51_PORT1_GPIO0
    #if (PADS_PM51_PORT1_GPIO0!= UNKNOWN_PAD_MUX)
    #define _CONFIG_PM51_PORT1_GPIO0    ((PADS_PM51_PORT1_GPIO0 == ENABLE) ? BIT0 : 0)
        _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO0, BIT0),
    #endif
#endif

#ifdef PADS_PM51_PORT1_GPIO1
    #if (PADS_PM51_PORT1_GPIO1!= UNKNOWN_PAD_MUX)
    #define _CONFIG_PM51_PORT1_GPIO1    ((PADS_PM51_PORT1_GPIO1 == ENABLE) ? BIT1 : 0)
        _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO1, BIT1),
    #endif
#endif

#ifdef PADS_PM51_PORT1_GPIO2
    #if (PADS_PM51_PORT1_GPIO2!= UNKNOWN_PAD_MUX)
    #define _CONFIG_PM51_PORT1_GPIO2    ((PADS_PM51_PORT1_GPIO2 == ENABLE) ? BIT2 : 0)
        _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO2, BIT2),
    #endif
#endif

#ifdef PADS_PM51_PORT1_GPIO3
    #if (PADS_PM51_PORT1_GPIO3!= UNKNOWN_PAD_MUX)
    #define _CONFIG_PM51_PORT1_GPIO3    ((PADS_PM51_PORT1_GPIO3 == ENABLE) ? BIT3 : 0)
        _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO3, BIT3),
    #endif
#endif

#ifdef PADS_PM51_PORT1_GPIO4
    #if (PADS_PM51_PORT1_GPIO4!= UNKNOWN_PAD_MUX)
    #define _CONFIG_PM51_PORT1_GPIO4    ((PADS_PM51_PORT1_GPIO4 == ENABLE) ? BIT4 : 0)
        _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO4, BIT4),
    #endif
#endif

#ifdef PADS_PM51_PORT1_GPIO5
    #if (PADS_PM51_PORT1_GPIO5!= UNKNOWN_PAD_MUX)
    #define _CONFIG_PM51_PORT1_GPIO5    ((PADS_PM51_PORT1_GPIO5 == ENABLE) ? BIT5 : 0)
        _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO5, BIT5),
    #endif
#endif

#ifdef PADS_PM51_PORT1_GPIO6
    #if (PADS_PM51_PORT1_GPIO6!= UNKNOWN_PAD_MUX)
    #define _CONFIG_PM51_PORT1_GPIO6    ((PADS_PM51_PORT1_GPIO6 == ENABLE) ? BIT6 : 0)
        _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO6, BIT6),
    #endif
#endif

#ifdef PADS_PM51_PORT1_GPIO7
    #if (PADS_PM51_PORT1_GPIO7!= UNKNOWN_PAD_MUX)
    #define _CONFIG_PM51_PORT1_GPIO7    ((PADS_PM51_PORT1_GPIO7 == ENABLE) ? BIT7 : 0)
        _RVM1(0x1ea4, _CONFIG_PM51_PORT1_GPIO7, BIT7),
    #endif
#endif

#ifdef PADS_SM_MODE
    #if (PADS_SM_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_SM_MODE     ((PADS_SM_MODE == CONFIG_SMART_CARD_PCM) ? BIT4 : \
                                 (PADS_SM_MODE == CONFIG_SMART_CARD_TS1) ? BIT5 : 0)
        _RVM1(0x1edc, _CONFIG_SM_MODE, (BIT5 | BIT4)),
    #endif
#endif

#ifdef PADS_SD_MODE
    #if (PADS_SD_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_SD_MODE     ((PADS_SD_MODE == CONFIG_SD_MODE0) ? BIT0: \
                                 (PADS_SD_MODE == CONFIG_SD_MODE1) ? BIT1: 0)
        _RVM1(0x1eb5, _CONFIG_SD_MODE, (BIT1 | BIT0)),
    #endif
#endif

#ifdef PADS_SDIO_MODE
    #if (PADS_SDIO_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_SDIO_MODE   ((PADS_SDIO_MODE == CONFIG_SDIO_MODE0) ? BIT4: \
                                 (PADS_SDIO_MODE == CONFIG_SDIO_MODE1) ? BIT5: \
                                 (PADS_SDIO_MODE == CONFIG_SDIO_MODE2) ? (BIT5 | BIT4) : 0)
        _RVM1(0x1ef6, _CONFIG_SDIO_MODE, (BIT5 | BIT4)),
    #endif
#endif

#ifdef PADS_EMMC_MODE
    #if (PADS_EMMC_MODE != UNKNOWN_PAD_MUX)
    #define _CONFIG_EMMC_MODE   ((PADS_EMMC_MODE == PAD_EMMC) ? BIT6 : 0)
        _RVM1(0x1edc, _CONFIG_EMMC_MODE, (BIT7 | BIT6)),
    #else
        _RVM1(0x1edc, 0, (BIT7 | BIT6)),
    #endif
#endif

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
#if ((MS_BOARD_TYPE_SEL == BD_MST207A_D01A_S_CLIPPERS))
    _RVM1(0x0e04, BIT2, BIT2),          //Output Value of PM2
    _RVM1(0x0e04, 0, BIT2),               //Output Enable of PM2
    _RVM1(0x0e39, 0, BIT5 | BIT4 ),   //reg[0e39]#5 ~ #4 = 00b
#elif ((MS_BOARD_TYPE_SEL == BD_MST207B_D01A_S_CLIPPERS))
    _RVM1(0x0e04, BIT2, BIT2),          //Output Value of PM2
    _RVM1(0x0e04, 0, BIT2),               //Output Enable of PM2
    _RVM1(0x0e39, 0, BIT5 | BIT4 ),   //reg[0e39]#5 ~ #4 = 00b
#else
    #error [ERROR] Invalid WP0 Settings in Unknown Board
#endif
#endif
    _END_OF_TBL_,
};

