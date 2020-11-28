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

//#include <stdio.h>

#include "datatype.h"
#include "drvRIU.h"
#include "Board.h"
//#include "c_riubase.h"
#include "hwreg_KENYA.h"
#include "chip/bond.h"

#define GPIO_NONE               0       // Not GPIO pin (default)
#define GPIO_IN                 1       // GPI
#define GPIO_OUT_LOW            2       // GPO output low
#define GPIO_OUT_HIGH           3       // GPO output high

#if defined (MIPS_CHAKRA) || defined(MSOS_TYPE_LINUX)
#define _MapBase_nonPM_KENYA (RIU_MAP + 0x200000)
#define _MapBase_PM_KENYA    RIU_MAP
#else
#define _MapBase_nonPM_KENYA 0xA0200000
#define _MapBase_PM_KAPPA   0xA0000000
#endif

#define _MEMMAP_nonPM_  _RVM1(0x0000, 0x10, 0xFF)
#define _MEMMAP_PM_     _RVM1(0x0000, 0x00, 0xFF)

#define _END_OF_TBL2_       0xFF, 0xFF

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
    // PM domain
    _MEMMAP_PM_,

    // SPI BUS
    /*
    #define SPI_CZ_IS_GPIO  (PAD_PM_SPI_CZ_IS_GPIO ? BIT1:0)

    #define SPI_BUS_IS_GPIO ((PAD_PM_SPI_CK_IS_GPIO | \
                              PAD_PM_SPI_DI_IS_GPIO | \
                              PAD_PM_SPI_DO_IS_GPIO) ? BIT0 :0)

    #define SPI_BUS_OEN     ((PAD_PM_SPI_CZ_IS_GPIO == GPIO_IN ? (1UL << 4) : 0) | \
                             (PAD_PM_SPI_CK_IS_GPIO == GPIO_IN ? (1UL << 5) : 0) | \
                             (PAD_PM_SPI_DI_IS_GPIO == GPIO_IN ? (1UL << 6) : 0) | \
                             (PAD_PM_SPI_DO_IS_GPIO == GPIO_IN ? (1UL << 7) : 0))



    #define SPI_BUS_OUT     ((PAD_PM_SPI_CZ_IS_GPIO == GPIO_OUT_HIGH ? (1UL << 4) : 0) | \
                             (PAD_PM_SPI_CK_IS_GPIO == GPIO_OUT_HIGH ? (1UL << 5) : 0) | \
                             (PAD_PM_SPI_DI_IS_GPIO == GPIO_OUT_HIGH ? (1UL << 6) : 0) | \
                             (PAD_PM_SPI_DO_IS_GPIO == GPIO_OUT_HIGH ? (1UL << 7) : 0))

    #if((PAD_PM_SPI_CZ_IS_GPIO != GPIO_NONE) && \
        (PAD_PM_SPI_CK_IS_GPIO != GPIO_NONE) && \
        (PAD_PM_SPI_DI_IS_GPIO != GPIO_NONE) && \
        (PAD_PM_SPI_DO_IS_GPIO != GPIO_NONE))


        _RVM1(0x0E3A, SPI_BUS_OUT, BITMASK(7:4)),
        _RVM1(0x0E3C, SPI_BUS_OEN, BITMASK(7:4)),

        _RVM1(0x0E6A, SPI_CZ_IS_GPIO, BIT1),
        _RVM1(0x0E6A, SPI_BUS_IS_GPIO, BIT0),
    #endif
    */
    // IRIN
    // In Kenya, IRIN is input only
    //#define IRIN_IS_GPIO    (PAD_IRIN_IS_GPIO ? BIT4: 0)
    //#define IRIN_OEN        (PAD_IRIN_IS_GPIO == GPIO_IN ? (1UL << 0) : 0)
    //#define IRIN_OUT        (PAD_IRIN_IS_GPIO == GPIO_OUT_HIGH ? (1UL << 0) : 0)

    //_RVM1(0x0E3A, IRIN_OUT, BIT0),
    //_RVM1(0x0E3C, IRIN_OEN, BIT0),
    //_RVM1(0x0E38, IRIN_IS_GPIO, BIT4),

    // CEC
    #define CEC_IS_GPIO     (PAD_HDMI_CEC_IS_GPIO ? BIT6: 0)
    #define CEC_OEN         (PAD_HDMI_CEC_IS_GPIO == GPIO_IN ? BIT0 : 0)
    #define CEC_OUT         (PAD_HDMI_CEC_IS_GPIO == GPIO_OUT_HIGH ? BIT1 : 0)

    _RVM1(0x0F24, CEC_OUT, BIT1),
    _RVM1(0x0F24, CEC_OEN, BIT0),
    _RVM1(0x0E38, CEC_IS_GPIO, BIT6),

    // PM GPIOs are not in the same register anymore, so set initial value individually as follows
    /*

    // GPIO_PM0~GPIO_PM12
    #if(PAD_GPIO_PM4_IS_GPIO != GPIO_NONE)
    _RVM2(0x0e24, 0xBABE, 0xFFFF),
    #endif

    #define GPIO_PM6_IS_GPIO    (PAD_GPIO_PM6_IS_GPIO ? BIT2: 0)

    #if(PAD_GPIO_PM6_IS_GPIO != GPIO_NONE)
    _RVM1(0x0E6A, GPIO_PM6_IS_GPIO, BIT2),
    #endif


    #define GPIO_PM_OEN     ((PAD_GPIO_PM0_IS_GPIO == GPIO_IN ? (1UL <<  0) : 0) | \
                             (PAD_GPIO_PM1_IS_GPIO == GPIO_IN ? (1UL <<  1) : 0) | \
                             (PAD_GPIO_PM2_IS_GPIO == GPIO_IN ? (1UL <<  2) : 0) | \
                             (PAD_GPIO_PM3_IS_GPIO == GPIO_IN ? (1UL <<  3) : 0) | \
                             (PAD_GPIO_PM4_IS_GPIO == GPIO_IN ? (1UL <<  4) : 0) | \
                             (PAD_GPIO_PM5_IS_GPIO == GPIO_IN ? (1UL <<  5) : 0) | \
                             (PAD_GPIO_PM6_IS_GPIO == GPIO_IN ? (1UL <<  6) : 0) | \
                             (PAD_GPIO_PM7_IS_GPIO == GPIO_IN ? (1UL <<  7) : 0) | \
                             (PAD_GPIO_PM8_IS_GPIO == GPIO_IN ? (1UL <<  8) : 0) | \
                             (PAD_GPIO_PM9_IS_GPIO == GPIO_IN ? (1UL <<  9) : 0))

    #define GPIO_PM_OUT     ((PAD_GPIO_PM0_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  0) : 0) | \
                             (PAD_GPIO_PM1_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  1) : 0) | \
                             (PAD_GPIO_PM2_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  2) : 0) | \
                             (PAD_GPIO_PM3_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  3) : 0) | \
                             (PAD_GPIO_PM4_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  4) : 0) | \
                             (PAD_GPIO_PM5_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  5) : 0) | \
                             (PAD_GPIO_PM6_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  6) : 0) | \
                             (PAD_GPIO_PM7_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  7) : 0) | \
                             (PAD_GPIO_PM8_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  8) : 0) | \
                             (PAD_GPIO_PM9_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  9) : 0))

    _RVM2(0x0E20, GPIO_PM_OUT, 0x03FF),
    _RVM2(0x0E1E, GPIO_PM_OEN, 0x03FF),

    */
    /*
        // SAR
        // SAR
        #if(PAD_SAR0_IS_GPIO != GPIO_NONE)
        _RVM1(0x1422, 0, BIT0),
        #endif
        #if(PAD_SAR1_IS_GPIO != GPIO_NONE)
        _RVM1(0x1422, 0, BIT1),
        #endif
        #if(PAD_SAR2_IS_GPIO != GPIO_NONE)
        _RVM1(0x1422, 0, BIT2),
        #endif
        #if(PAD_SAR3_IS_GPIO != GPIO_NONE)
        _RVM1(0x1422, 0, BIT3),
        #endif

        #define SAR_OEN         ((PAD_SAR0_IS_GPIO == GPIO_IN ? (1UL <<  0) : 0) | \
                                 (PAD_SAR1_IS_GPIO == GPIO_IN ? (1UL <<  1) : 0) | \
                                 (PAD_SAR2_IS_GPIO == GPIO_IN ? (1UL <<  2) : 0) | \
                                 (PAD_SAR3_IS_GPIO == GPIO_IN ? (1UL <<  3) : 0))

        #define SAR_OUT         ((PAD_SAR0_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  0) : 0) | \
                                 (PAD_SAR1_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  1) : 0) | \
                                 (PAD_SAR2_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  2) : 0) | \
                                 (PAD_SAR3_IS_GPIO == GPIO_OUT_HIGH ? (1UL <<  3) : 0))

        _RVM1(0x1424, SAR_OUT, BITMASK(3:0)),
        _RVM1(0x1423, SAR_OEN, BITMASK(3:0)),
    */

    // Script Generated GPIO

    #if(PAD_GPIO_PM1_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_PM1_OEN (PAD_GPIO_PM1_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO_PM1_OUT (PAD_GPIO_PM1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f02, PAD_GPIO_PM1_OUT, BIT1),
    _RVM1(0x0f02, PAD_GPIO_PM1_OEN, BIT0),
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
    // set password for control GPIO_PM4
    _RVM1(0x0e24, 0xbe, BITMASK(7:0)),
    _RVM1(0x0e25, 0xba, BITMASK(7:0)),

    _RVM1(0x0f08, PAD_GPIO_PM4_OUT, BIT1),
    _RVM1(0x0f08, PAD_GPIO_PM4_OEN, BIT0),
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
    #endif

    #if(PAD_PWM0_IS_GPIO != GPIO_NONE)
    #define PAD_PWM0_OEN (PAD_PWM0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_PWM0_OUT (PAD_PWM0_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f2c, PAD_PWM0_OUT, BIT1),
    _RVM1(0x0f2c, PAD_PWM0_OEN, BIT0),
    #endif

    #if(PAD_PWM1_IS_GPIO != GPIO_NONE)
    #define PAD_PWM1_OEN (PAD_PWM1_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_PWM1_OUT (PAD_PWM1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f2e, PAD_PWM1_OUT, BIT1),
    _RVM1(0x0f2e, PAD_PWM1_OEN, BIT0),
    #endif

    #if(PAD_PWM2_IS_GPIO != GPIO_NONE)
    #define PAD_PWM2_OEN (PAD_PWM2_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_PWM2_OUT (PAD_PWM2_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0f26, PAD_PWM2_OUT, BIT1),
    _RVM1(0x0f26, PAD_PWM2_OEN, BIT0),
    #endif

    #if(PAD_SAR0_IS_GPIO != GPIO_NONE)
    #define PAD_SAR0_OEN (PAD_SAR0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_SAR0_OUT (PAD_SAR0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)

    //reg_sar_aisel[0]
    //reg[1422]#0 = 0
    _RVM1(0x1422, 0, BIT0),
    _RVM1(0x1424, PAD_SAR0_OUT, BIT0),
    _RVM1(0x1423, PAD_SAR0_OEN, BIT0),
    #endif

    #if(PAD_SAR1_IS_GPIO != GPIO_NONE)
    #define PAD_SAR1_OEN (PAD_SAR1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_SAR1_OUT (PAD_SAR1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)

    //reg_sar_aisel[1]
    //reg[1422]#1 = 0
    _RVM1(0x1422, 0, BIT1),
    _RVM1(0x1424, PAD_SAR1_OUT, BIT1),
    _RVM1(0x1423, PAD_SAR1_OEN, BIT1),
    #endif

    #if(PAD_SAR2_IS_GPIO != GPIO_NONE)
    #define PAD_SAR2_OEN (PAD_SAR2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_SAR2_OUT (PAD_SAR2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)

    //reg_sar_aisel[2]
    //reg[1422]#2 = 0
    _RVM1(0x1422, 0, BIT2),
    _RVM1(0x1424, PAD_SAR2_OUT, BIT2),
    _RVM1(0x1423, PAD_SAR2_OEN, BIT2),
    #endif

    #if(PAD_SAR3_IS_GPIO != GPIO_NONE)
    #define PAD_SAR3_OEN (PAD_SAR3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_SAR3_OUT (PAD_SAR3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)

    //reg_sar_aisel[3]
    //reg[1422]#3 = 0
    _RVM1(0x1422, 0, BIT3),
    _RVM1(0x1424, PAD_SAR3_OUT, BIT3),
    _RVM1(0x1423, PAD_SAR3_OEN, BIT3),
    #endif


    // non-PM domain
    _MEMMAP_nonPM_,

    #if(PAD_ET_MDIO_IS_GPIO != GPIO_NONE)
    #define PAD_ET_MDIO_OEN (PAD_ET_MDIO_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_MDIO_OUT (PAD_ET_MDIO_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2604, PAD_ET_MDIO_OUT, BIT4),
    _RVM1(0x2604, PAD_ET_MDIO_OEN, BIT5),
    #endif

    #if(PAD_ET_MDC_IS_GPIO != GPIO_NONE)
    #define PAD_ET_MDC_OEN (PAD_ET_MDC_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_MDC_OUT (PAD_ET_MDC_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2606, PAD_ET_MDC_OUT, BIT4),
    _RVM1(0x2606, PAD_ET_MDC_OEN, BIT5),
    #endif

    #if(PAD_ET_COL_IS_GPIO != GPIO_NONE)
    #define PAD_ET_COL_OEN (PAD_ET_COL_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_COL_OUT (PAD_ET_COL_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2608, PAD_ET_COL_OUT, BIT4),
    _RVM1(0x2608, PAD_ET_COL_OEN, BIT5),
    #endif

    #if(PAD_ET_RXD0_IS_GPIO != GPIO_NONE)
    #define PAD_ET_RXD0_OEN (PAD_ET_RXD0_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_RXD0_OUT (PAD_ET_RXD0_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x260a, PAD_ET_RXD0_OUT, BIT4),
    _RVM1(0x260a, PAD_ET_RXD0_OEN, BIT5),
    #endif

    #if(PAD_ET_RXD1_IS_GPIO != GPIO_NONE)
    #define PAD_ET_RXD1_OEN (PAD_ET_RXD1_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_RXD1_OUT (PAD_ET_RXD1_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x260c, PAD_ET_RXD1_OUT, BIT4),
    _RVM1(0x260c, PAD_ET_RXD1_OEN, BIT5),
    #endif

    #if(PAD_ET_TX_CLK_IS_GPIO != GPIO_NONE)
    #define PAD_ET_TX_CLK_OEN (PAD_ET_TX_CLK_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_TX_CLK_OUT (PAD_ET_TX_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x260e, PAD_ET_TX_CLK_OUT, BIT4),
    _RVM1(0x260e, PAD_ET_TX_CLK_OEN, BIT5),
    #endif

    #if(PAD_ET_TXD0_IS_GPIO != GPIO_NONE)
    #define PAD_ET_TXD0_OEN (PAD_ET_TXD0_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_TXD0_OUT (PAD_ET_TXD0_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2610, PAD_ET_TXD0_OUT, BIT4),
    _RVM1(0x2610, PAD_ET_TXD0_OEN, BIT5),
    #endif

    #if(PAD_ET_TXD1_IS_GPIO != GPIO_NONE)
    #define PAD_ET_TXD1_OEN (PAD_ET_TXD1_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_TXD1_OUT (PAD_ET_TXD1_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2612, PAD_ET_TXD1_OUT, BIT4),
    _RVM1(0x2612, PAD_ET_TXD1_OEN, BIT5),
    #endif

    #if(PAD_ET_TX_EN_IS_GPIO != GPIO_NONE)
    #define PAD_ET_TX_EN_OEN (PAD_ET_TX_EN_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_ET_TX_EN_OUT (PAD_ET_TX_EN_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2614, PAD_ET_TX_EN_OUT, BIT4),
    _RVM1(0x2614, PAD_ET_TX_EN_OEN, BIT5),
    #endif

    #if(PAD_GPIO_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO_OEN (PAD_GPIO_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_GPIO_OUT (PAD_GPIO_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2650, PAD_GPIO_OUT, BIT4),
    _RVM1(0x2650, PAD_GPIO_OEN, BIT5),
    #endif

    #if(PAD_HDMI_HPD_IS_GPIO != GPIO_NONE)
    #define PAD_HDMI_HPD_OEN (PAD_HDMI_HPD_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_HDMI_HPD_OUT (PAD_HDMI_HPD_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x264e, PAD_HDMI_HPD_OUT, BIT4),
    _RVM1(0x264e, PAD_HDMI_HPD_OEN, BIT5),
    #endif

    #if(PAD_I2CM0_SCL_IS_GPIO != GPIO_NONE)
    #define PAD_I2CM0_SCL_OEN (PAD_I2CM0_SCL_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_I2CM0_SCL_OUT (PAD_I2CM0_SCL_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x251c, PAD_I2CM0_SCL_OUT, BIT4),
    _RVM1(0x251c, PAD_I2CM0_SCL_OEN, BIT5),
    #endif

    #if(PAD_I2CM0_SDA_IS_GPIO != GPIO_NONE)
    #define PAD_I2CM0_SDA_OEN (PAD_I2CM0_SDA_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_I2CM0_SDA_OUT (PAD_I2CM0_SDA_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x251e, PAD_I2CM0_SDA_OUT, BIT4),
    _RVM1(0x251e, PAD_I2CM0_SDA_OEN, BIT5),
    #endif

    #if(PAD_I2S_OUT_MUTE_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_MUTE_OEN (PAD_I2S_OUT_MUTE_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_I2S_OUT_MUTE_OUT (PAD_I2S_OUT_MUTE_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x262e, PAD_I2S_OUT_MUTE_OUT, BIT4),
    _RVM1(0x262e, PAD_I2S_OUT_MUTE_OEN, BIT5),
    #endif

    #if(PAD_I2S_OUT_BCK_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_BCK_OEN (PAD_I2S_OUT_BCK_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_I2S_OUT_BCK_OUT (PAD_I2S_OUT_BCK_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2630, PAD_I2S_OUT_BCK_OUT, BIT4),
    _RVM1(0x2630, PAD_I2S_OUT_BCK_OEN, BIT5),
    #endif

    #if(PAD_I2S_OUT_WS_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_WS_OEN (PAD_I2S_OUT_WS_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_I2S_OUT_WS_OUT (PAD_I2S_OUT_WS_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2632, PAD_I2S_OUT_WS_OUT, BIT4),
    _RVM1(0x2632, PAD_I2S_OUT_WS_OEN, BIT5),
    #endif

    #if(PAD_I2S_OUT_MCK_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_MCK_OEN (PAD_I2S_OUT_MCK_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_I2S_OUT_MCK_OUT (PAD_I2S_OUT_MCK_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2634, PAD_I2S_OUT_MCK_OUT, BIT4),
    _RVM1(0x2634, PAD_I2S_OUT_MCK_OEN, BIT5),
    #endif

    #if(PAD_I2S_OUT_SD0_IS_GPIO != GPIO_NONE)
    #define PAD_I2S_OUT_SD0_OEN (PAD_I2S_OUT_SD0_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_I2S_OUT_SD0_OUT (PAD_I2S_OUT_SD0_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2636, PAD_I2S_OUT_SD0_OUT, BIT4),
    _RVM1(0x2636, PAD_I2S_OUT_SD0_OEN, BIT5),
    #endif

    #if(PAD_LED0_IS_GPIO != GPIO_NONE)
    #define PAD_LED0_OEN (PAD_LED0_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_LED0_OUT (PAD_LED0_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2644, PAD_LED0_OUT, BIT4),
    _RVM1(0x2644, PAD_LED0_OEN, BIT5),
    #endif

    #if(PAD_LED1_IS_GPIO != GPIO_NONE)
    #define PAD_LED1_OEN (PAD_LED1_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_LED1_OUT (PAD_LED1_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2646, PAD_LED1_OUT, BIT4),
    _RVM1(0x2646, PAD_LED1_OEN, BIT5),
    #endif

    #if(PAD_NAND_WPZ_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_WPZ_OEN (PAD_NAND_WPZ_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_NAND_WPZ_OUT (PAD_NAND_WPZ_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x264a, PAD_NAND_WPZ_OUT, BIT0),
    _RVM1(0x264c, PAD_NAND_WPZ_OEN, BIT0),
    #endif

    #if(PAD_NAND_WEZ_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_WEZ_OEN (PAD_NAND_WEZ_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_NAND_WEZ_OUT (PAD_NAND_WEZ_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x264a, PAD_NAND_WEZ_OUT, BIT1),
    _RVM1(0x264c, PAD_NAND_WEZ_OEN, BIT1),
    #endif

    #if(PAD_NAND_ALE_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_ALE_OEN (PAD_NAND_ALE_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_NAND_ALE_OUT (PAD_NAND_ALE_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x264a, PAD_NAND_ALE_OUT, BIT2),
    _RVM1(0x264c, PAD_NAND_ALE_OEN, BIT2),
    #endif

    #if(PAD_NAND_CLE_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_CLE_OEN (PAD_NAND_CLE_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_NAND_CLE_OUT (PAD_NAND_CLE_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x264a, PAD_NAND_CLE_OUT, BIT3),
    _RVM1(0x264c, PAD_NAND_CLE_OEN, BIT3),
    #endif

    #if(PAD_NAND_CEZ1_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_CEZ1_OEN (PAD_NAND_CEZ1_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_NAND_CEZ1_OUT (PAD_NAND_CEZ1_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x264a, PAD_NAND_CEZ1_OUT, BIT4),
    _RVM1(0x264c, PAD_NAND_CEZ1_OEN, BIT4),
    #endif

    #if(PAD_NAND_CEZ_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_CEZ_OEN (PAD_NAND_CEZ_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_NAND_CEZ_OUT (PAD_NAND_CEZ_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x264a, PAD_NAND_CEZ_OUT, BIT5),
    _RVM1(0x264c, PAD_NAND_CEZ_OEN, BIT5),
    #endif

    #if(PAD_NAND_REZ_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_REZ_OEN (PAD_NAND_REZ_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_NAND_REZ_OUT (PAD_NAND_REZ_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x264a, PAD_NAND_REZ_OUT, BIT6),
    _RVM1(0x264c, PAD_NAND_REZ_OEN, BIT6),
    #endif

    #if(PAD_NAND_RBZ_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_RBZ_OEN (PAD_NAND_RBZ_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_NAND_RBZ_OUT (PAD_NAND_RBZ_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x264a, PAD_NAND_RBZ_OUT, BIT7),
    _RVM1(0x264c, PAD_NAND_RBZ_OEN, BIT7),
    #endif

    #if(PAD_NAND_AD0_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_AD0_OEN (PAD_NAND_AD0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_NAND_AD0_OUT (PAD_NAND_AD0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x264b, PAD_NAND_AD0_OUT, BIT0),
    _RVM1(0x264d, PAD_NAND_AD0_OEN, BIT0),
    #endif

    #if(PAD_NAND_AD1_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_AD1_OEN (PAD_NAND_AD1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_NAND_AD1_OUT (PAD_NAND_AD1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x264b, PAD_NAND_AD1_OUT, BIT1),
    _RVM1(0x264d, PAD_NAND_AD1_OEN, BIT1),
    #endif

    #if(PAD_NAND_AD2_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_AD2_OEN (PAD_NAND_AD2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_NAND_AD2_OUT (PAD_NAND_AD2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x264b, PAD_NAND_AD2_OUT, BIT2),
    _RVM1(0x264d, PAD_NAND_AD2_OEN, BIT2),
    #endif

    #if(PAD_NAND_AD3_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_AD3_OEN (PAD_NAND_AD3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_NAND_AD3_OUT (PAD_NAND_AD3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x264b, PAD_NAND_AD3_OUT, BIT3),
    _RVM1(0x264d, PAD_NAND_AD3_OEN, BIT3),
    #endif

    #if(PAD_NAND_AD4_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_AD4_OEN (PAD_NAND_AD4_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_NAND_AD4_OUT (PAD_NAND_AD4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x264b, PAD_NAND_AD4_OUT, BIT4),
    _RVM1(0x264d, PAD_NAND_AD4_OEN, BIT4),
    #endif

    #if(PAD_NAND_AD5_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_AD5_OEN (PAD_NAND_AD5_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_NAND_AD5_OUT (PAD_NAND_AD5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x264b, PAD_NAND_AD5_OUT, BIT5),
    _RVM1(0x264d, PAD_NAND_AD5_OEN, BIT5),
    #endif

    #if(PAD_NAND_AD6_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_AD6_OEN (PAD_NAND_AD6_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_NAND_AD6_OUT (PAD_NAND_AD6_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x264b, PAD_NAND_AD6_OUT, BIT6),
    _RVM1(0x264d, PAD_NAND_AD6_OEN, BIT6),
    #endif

    #if(PAD_NAND_AD7_IS_GPIO != GPIO_NONE)
    #define PAD_NAND_AD7_OEN (PAD_NAND_AD7_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_NAND_AD7_OUT (PAD_NAND_AD7_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x264b, PAD_NAND_AD7_OUT, BIT7),
    _RVM1(0x264d, PAD_NAND_AD7_OEN, BIT7),
    #endif

    #if(PAD_SM0_CD_IS_GPIO != GPIO_NONE)
    #define PAD_SM0_CD_OEN (PAD_SM0_CD_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_SM0_CD_OUT (PAD_SM0_CD_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2500, PAD_SM0_CD_OUT, BIT4),
    _RVM1(0x2500, PAD_SM0_CD_OEN, BIT5),
    #endif

    #if(PAD_SM0_RST_IS_GPIO != GPIO_NONE)
    #define PAD_SM0_RST_OEN (PAD_SM0_RST_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_SM0_RST_OUT (PAD_SM0_RST_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2502, PAD_SM0_RST_OUT, BIT4),
    _RVM1(0x2502, PAD_SM0_RST_OEN, BIT5),
    #endif

    #if(PAD_SM0_VCC_IS_GPIO != GPIO_NONE)
    #define PAD_SM0_VCC_OEN (PAD_SM0_VCC_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_SM0_VCC_OUT (PAD_SM0_VCC_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2504, PAD_SM0_VCC_OUT, BIT4),
    _RVM1(0x2504, PAD_SM0_VCC_OEN, BIT5),
    #endif

    #if(PAD_SM0_IO_IS_GPIO != GPIO_NONE)
    #define PAD_SM0_IO_OEN (PAD_SM0_IO_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_SM0_IO_OUT (PAD_SM0_IO_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2506, PAD_SM0_IO_OUT, BIT4),
    _RVM1(0x2506, PAD_SM0_IO_OEN, BIT5),
    #endif

    #if(PAD_SM0_CLK_IS_GPIO != GPIO_NONE)
    #define PAD_SM0_CLK_OEN (PAD_SM0_CLK_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_SM0_CLK_OUT (PAD_SM0_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2508, PAD_SM0_CLK_OUT, BIT4),
    _RVM1(0x2508, PAD_SM0_CLK_OEN, BIT5),
    #endif

    #if(PAD_SM0_SWITCH_IS_GPIO != GPIO_NONE)
    #define PAD_SM0_SWITCH_OEN (PAD_SM0_SWITCH_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_SM0_SWITCH_OUT (PAD_SM0_SWITCH_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x250a, PAD_SM0_SWITCH_OUT, BIT4),
    _RVM1(0x250a, PAD_SM0_SWITCH_OEN, BIT5),
    #endif

    #if(PAD_SM0_C4_IS_GPIO != GPIO_NONE)
    #define PAD_SM0_C4_OEN (PAD_SM0_C4_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_SM0_C4_OUT (PAD_SM0_C4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x250c, PAD_SM0_C4_OUT, BIT4),
    _RVM1(0x250c, PAD_SM0_C4_OEN, BIT5),
    #endif

    #if(PAD_SM0_C8_IS_GPIO != GPIO_NONE)
    #define PAD_SM0_C8_OEN (PAD_SM0_C8_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_SM0_C8_OUT (PAD_SM0_C8_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x250e, PAD_SM0_C8_OUT, BIT4),
    _RVM1(0x250e, PAD_SM0_C8_OEN, BIT5),
    #endif

    #if(PAD_SPDIF_OUT_IS_GPIO != GPIO_NONE)
    #define PAD_SPDIF_OUT_OEN (PAD_SPDIF_OUT_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_SPDIF_OUT_OUT (PAD_SPDIF_OUT_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x262c, PAD_SPDIF_OUT_OUT, BIT4),
    _RVM1(0x262d, PAD_SPDIF_OUT_OEN, BIT0),
    #endif

    #if(PAD_SPDIF_IN_IS_GPIO != GPIO_NONE)
    #define PAD_SPDIF_IN_OEN (PAD_SPDIF_IN_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_SPDIF_IN_OUT (PAD_SPDIF_IN_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x262c, PAD_SPDIF_IN_OUT, BIT5),
    _RVM1(0x262d, PAD_SPDIF_IN_OEN, BIT1),
    #endif

    #if(PAD_TS0_CLK_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_CLK_OEN (PAD_TS0_CLK_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_CLK_OUT (PAD_TS0_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2524, PAD_TS0_CLK_OUT, BIT4),
    _RVM1(0x2524, PAD_TS0_CLK_OEN, BIT5),
    #endif

    #if(PAD_TS0_VLD_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_VLD_OEN (PAD_TS0_VLD_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_VLD_OUT (PAD_TS0_VLD_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2526, PAD_TS0_VLD_OUT, BIT4),
    _RVM1(0x2526, PAD_TS0_VLD_OEN, BIT5),
    #endif

    #if(PAD_TS0_SYNC_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_SYNC_OEN (PAD_TS0_SYNC_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_SYNC_OUT (PAD_TS0_SYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2528, PAD_TS0_SYNC_OUT, BIT4),
    _RVM1(0x2528, PAD_TS0_SYNC_OEN, BIT5),
    #endif

    #if(PAD_TS0_D7_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D7_OEN (PAD_TS0_D7_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_D7_OUT (PAD_TS0_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x252a, PAD_TS0_D7_OUT, BIT4),
    _RVM1(0x252a, PAD_TS0_D7_OEN, BIT5),
    #endif

    #if(PAD_TS0_D6_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D6_OEN (PAD_TS0_D6_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_D6_OUT (PAD_TS0_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x252c, PAD_TS0_D6_OUT, BIT4),
    _RVM1(0x252c, PAD_TS0_D6_OEN, BIT5),
    #endif

    #if(PAD_TS0_D5_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D5_OEN (PAD_TS0_D5_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_D5_OUT (PAD_TS0_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x252e, PAD_TS0_D5_OUT, BIT4),
    _RVM1(0x252e, PAD_TS0_D5_OEN, BIT5),
    #endif

    #if(PAD_TS0_D4_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D4_OEN (PAD_TS0_D4_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_D4_OUT (PAD_TS0_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2530, PAD_TS0_D4_OUT, BIT4),
    _RVM1(0x2530, PAD_TS0_D4_OEN, BIT5),
    #endif

    #if(PAD_TS0_D3_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D3_OEN (PAD_TS0_D3_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_D3_OUT (PAD_TS0_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2532, PAD_TS0_D3_OUT, BIT4),
    _RVM1(0x2532, PAD_TS0_D3_OEN, BIT5),
    #endif

    #if(PAD_TS0_D2_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D2_OEN (PAD_TS0_D2_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_D2_OUT (PAD_TS0_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2534, PAD_TS0_D2_OUT, BIT4),
    _RVM1(0x2534, PAD_TS0_D2_OEN, BIT5),
    #endif

    #if(PAD_TS0_D1_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D1_OEN (PAD_TS0_D1_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_D1_OUT (PAD_TS0_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2536, PAD_TS0_D1_OUT, BIT4),
    _RVM1(0x2536, PAD_TS0_D1_OEN, BIT5),
    #endif

    #if(PAD_TS0_D0_IS_GPIO != GPIO_NONE)
    #define PAD_TS0_D0_OEN (PAD_TS0_D0_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TS0_D0_OUT (PAD_TS0_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2538, PAD_TS0_D0_OUT, BIT4),
    _RVM1(0x2538, PAD_TS0_D0_OEN, BIT5),
    #endif


//---------------------------------------------------------------------
// Pad Configuartion
//---------------------------------------------------------------------
    _MEMMAP_PM_,

    #define IRIN_USE_PM5 ((PADS_PM5_IS_IRIN==1)? BIT0 : 0) //reg_qfp156_mode

    _RVM1(0x0E50, IRIN_USE_PM5, BIT0),

    _MEMMAP_nonPM_,

    #define SM0_OPEN ((PADS_SM0_OPEN == PAD_SM0_CLK) ? (BIT0) : \
                      (PADS_SM0_OPEN == PAD_SM0_RST ) ? (BIT0) : 0)

    _RVM1(0x1E18, SM0_OPEN, BIT0),
    _RVM1(0x1E31, BIT4, BIT4),
/*
    #define SM0_C48 ((PADS_SM0_C48 == PAD_SM0_GPIO0) ? (BIT4) : \
                     (PADS_SM0_C48 == PAD_SM0_GPIO1) ? (BIT4) : 0)

    _RVM1(0x1E18, SM0_C48, BIT4),
*/
    #define SM0_EN  ((PADS_SM0_EN == PAD_SM0_IO) ? (BIT0) : \
                     (PADS_SM0_EN == PAD_SM0_CLK) ? (BIT0) : \
                     (PADS_SM0_EN == PAD_SM0_RST) ? (BIT0) : \
                     (PADS_SM0_EN == PAD_SM0_CD) ? (BIT0) : \
                     (PADS_SM0_EN == PAD_SM0_VCC) ? (BIT0) : 0)

    _RVM1(0x1E19, SM0_EN, BIT0),

/*
    #define SM1_OPEN ((PADS_SM1_OPEN == PAD_SM1_RST ) ? (BIT0) : \
                      (PADS_SM1_OPEN == PAD_SM1_CLK) ? (BIT0) : \
                      (PADS_SM1_OPEN == PAD_TS1_CLK) ? (BIT1) : \
                      (PADS_SM1_OPEN == PAD_TS1_D6) ? (BIT1) : 0)

    _RVM1(0x1E1A, SM1_OPEN, BIT1|BIT0),

     #define SM1_C48 ((PADS_SM1_C48 == PAD_SM1_GPIO0 ) ? (BIT4) : \
                      (PADS_SM1_C48 == PAD_SM1_GPIO1) ? (BIT4) : \
                      (PADS_SM1_C48 == PAD_TS1_D7) ? (BIT5) : \
                      (PADS_SM1_C48 == PAD_TS1_D6) ? (BIT5) : 0)

    _RVM1(0x1E1A, SM1_C48, BIT5|BIT4),

    #define SM1_EN  ((PADS_SM1_EN == PAD_SM1_RST  ) ? (BIT0) : \
                      (PADS_SM1_EN == PAD_SM1_CD) ? (BIT0) : \
                      (PADS_SM1_EN == PAD_SM1_VCC) ? (BIT0) : \
                      (PADS_SM1_EN == PAD_SM1_GPIO0) ? (BIT1) : \
                      (PADS_SM1_EN == PAD_SM1_GPIO1) ? (BIT1) : \
                      (PADS_SM1_EN == PAD_TS1_CLK) ? (BIT1|BIT0) : \
                      (PADS_SM1_EN == PAD_TS1_SYNC) ? (BIT1|BIT0) : \
                      (PADS_SM1_EN == PAD_TS1_VLD) ? (BIT1|BIT0) : \
                      (PADS_SM1_EN == PAD_TS1_D7) ? (BIT1|BIT0) : \
                      (PADS_SM1_EN == PAD_TS1_D6) ? (BIT1|BIT0) : 0)

    _RVM1(0x1E1B, SM1_EN, BIT1|BIT0),
*/

    #define I2CM0_MODE ((PADS_I2CM0_MODE == PAD_I2CM0_SDA  ) ? (BIT0) : \
                      (PADS_I2CM0_MODE == PAD_I2CM0_SCL) ? (BIT0) : \
                      (PADS_I2CM0_MODE == PAD_SM0_IO) ? (BIT1) : \
                      (PADS_I2CM0_MODE == PAD_SM0_CLK) ? (BIT1) : 0)

    _RVM1(0x1E12, I2CM0_MODE, BIT1|BIT0),
/*
    #define I2CM1_MODE ((PADS_I2CM0_MODE == PAD_I2CM1_SCL) ? (BIT4) : \
                        (PADS_I2CM0_MODE == PAD_I2CM1_SDA) ? (BIT4) : \
                        (PADS_I2CM0_MODE == PAD_ET_TXD1) ? (BIT5) : \
                        (PADS_I2CM0_MODE == PAD_ET_TXD0) ? (BIT5) : \
                        (PADS_I2CM0_MODE == PAD_TS0_D5) ? (BIT5|BIT4) : \
                        (PADS_I2CM0_MODE == PAD_TS0_D4) ? (BIT5|BIT4) : \
                        (PADS_I2CM0_MODE == PAD_TS1_D5) ? (BIT6) : \
                        (PADS_I2CM0_MODE == PAD_TS1_D4) ? (BIT6) : 0)

    _RVM1(0x1E12, I2CM1_MODE, BITMASK(6:4)),
*/
    #define TS0_MODE ((PADS_TS0_MODE == PAD_TS0_CLK) ? (BIT0) : \
                      (PADS_TS0_MODE == PAD_TS0_D7) ? (BIT1) : \
                      (PADS_TS0_MODE == PAD_TS0_D0) ? (BIT1|BIT0) : 0)
//                      (PADS_TS0_MODE == PAD_CI_D3) ? (BIT2) :
//                      (PADS_TS0_MODE == PAD_CI_D2) ? (BIT2|BIT0) :
//                      (PADS_TS0_MODE == PAD_CI_A14) ? (BIT2|BIT1) : 0)

    _RVM1(0x1E04, TS0_MODE, BITMASK(2:0)),
/*
    #define TS1_MODE ((PADS_TS1_MODE == PAD_TS1_CLK) ? (BIT4) : \
                      (PADS_TS1_MODE == PAD_TS1_D7) ? (BIT5) : \
                      (PADS_TS1_MODE == PAD_TS1_D0) ? (BIT5|BIT4) : \
                      (PADS_TS1_MODE == PAD_CI_A6) ? (BIT6) : \
                      (PADS_TS1_MODE == PAD_CI_A7) ? (BIT6|BIT4) : \
                      (PADS_TS1_MODE == PAD_CI_A12) ? (BIT6|BIT5) : \
                      (PADS_TS1_MODE == PAD_CI_A4) ? (BIT6|BIT5|BIT4) : 0)

    _RVM1(0x1E04, TS1_MODE, BITMASK(6:4)),
    */
/*
    #define TS2_MODE ((PADS_TS2_MODE == PAD_TS2_CLK) ? (BIT0) : \
                      (PADS_TS2_MODE == PAD_I2S_OUT_SD0) ? (BIT1) : 0)

    _RVM1(0x1E05, TS2_MODE, BITMASK(1:0)),
*/
/*
    #define NAND_MODE ((PADS_NAND_MODE == PAD_TS1_VLD) ? (BIT0) : \
                       (PADS_NAND_MODE == PAD_TS0_D7) ? (BIT1) : 0)
                       (PADS_NAND_MODE == PAD_S_GPIO4) ? (BIT1|BIT0) : \
                       (PADS_NAND_MODE == PAD_CI_A5) ? (BIT2|BIT0) : 0)
                       (PADS_NAND_MODE == PAD_PF_A21) ? (BIT2) :

    _RVM1(0x1E0C, NAND_MODE, BITMASK(3:0)),
*/
/*
    #define CI_MODE ((PADS_CI_MODE == PAD_CI_A14) ? (BIT0) : 0)

    _RVM1(0x1E0E, CI_MODE, BIT0),
*/
    #define CCIR_OUT_MODE ((PADS_CCIR_OUT_MODE == PAD_TS0_CLK) ? (BIT4) : 0)

    _RVM1(0x1E10, CCIR_OUT_MODE, BITMASK(5:4)),

    #define CCIR_IN_MODE ((PADS_CCIR_IN_MODE == PAD_TS0_CLK) ? (BIT0) : 0)

    _RVM1(0x1E10, CCIR_OUT_MODE, BITMASK(1:0)),
/*
    #define PANEL_IF_MODE ((PADS_PANEL_IF_MODE == PAD_CI_A12) ? (BIT0) : 0)

    _RVM1(0x1E11, PANEL_IF_MODE, BIT0),
*/

    //#define SPDIF_OUT_MODE ((PADS_SPDIF_OUT_MODE == PAD_SPDIF_OUT) ? (BIT5|BIT4) : 0)
    #define SPDIF_OUT_MODE ((PADS_SPDIF_OUT_MODE == PAD_SPDIF_OUT) ? (BIT4) : 0)
/*                            (PADS_SPDIF_OUT_MODE == PAD_TS1_D6) ? (BIT6) :   */
/*                            (PADS_SPDIF_OUT_MODE == PAD_SM0_CD) ? (BIT6|BIT4) : 0)   */

    _RVM1(0x1E0A, SPDIF_OUT_MODE, BITMASK(6:4)),

/*
    #define SPDIF_IN_MODE ((PADS_SPDIF_IN_MODE == PAD_CI_A12) ? (BIT0) : \
                            (PADS_SPDIF_IN_MODE == PAD_CI_A12) ? (BIT1) : \
                            (PADS_SPDIF_IN_MODE == PAD_SPDIF_OUT) ? (BIT1|BIT0) : \
                            (PADS_SPDIF_IN_MODE == PAD_TS1_D6) ? (BIT2) : \
                            (PADS_SPDIF_IN_MODE == PAD_SM0_CD) ? (BIT2|BIT0) : 0)

    _RVM1(0x1E0A, SPDIF_IN_MODE, BITMASK(2:0)),
*/

    #define I2S_IN_MODE 0

    _RVM1(0x1E0B, I2S_IN_MODE, BITMASK(1:0)),
//    #define I2S_OUT_MUTE_MODE ((PADS_I2S_OUT_MUTE_MODE == PAD_I2S_OUT_SD3 ) ? (BIT5) : 0)

//    _RVM1(0x1E11, I2S_OUT_MUTE_MODE, BIT4),

//    #define I2S_OUT_MODE ((PADS_I2S_OUT_MODE == PAD_TS1_CLK) ? (BIT6|BIT5) : 0)

//    _RVM1(0x1E0B, I2S_OUT_MODE, BITMASK(5:4)),

/*
    #define MPIF_MODE ((PADS_MPIF_MODE == PAD_TS1_CLK) ? (BIT4) : \
                       (PADS_MPIF_MODE == PAD_ET_TXD1) ? (BIT5) : 0)
                       (PADS_MPIF_MODE == PAD_PF_A5) ? (BIT6) :
                       (PADS_MPIF_MODE == PAD_PF_A14) ? (BIT6|BIT4) : 0)

    _RVM1(0x1E0E, MPIF_MODE, BITMASK(6:4)),
*/
    #define SDIO_MODE ((PADS_SDIO_MODE == PAD_ET_TXD1) ? (BIT5) : 0)

    _RVM1(0x1E0C, SDIO_MODE, BITMASK(6:4)),

    #define ET_MODE ((PADS_ET_MODE == PAD_ET_TXD1) ? (BIT1) : 0)

    _RVM1(0x1E0F, ET_MODE, BITMASK(2:0)),

//    #define RF_AGC_EN ((PADS_RF_AGC_EN == PAD_RF_AGC) ? (BIT1) : 0)

//    _RVM1(0x1E3A, RF_AGC_EN, BIT1),

//    #define IF_AGC_EN ((PADS_IF_AGC_EN == PAD_IF_AGC) ? (BIT0) : 0)

//    _RVM1(0x1E3A, IF_AGC_EN, BIT0),

    #define MODEM_MODE ((PADS_MODEM_MODE == PAD_TS0_D3) ? (BIT4) : 0)
    _RVM1(0x1E0F, MODEM_MODE, BITMASK(5:4)),
/*
    #define PWM_MODE ((PADS_PWM_MODE == PAD_HSYNC_OUT) ? (BIT0) :
                        (PADS_PWM_MODE == PAD_VSYNC_OUT) ? (BIT0) : 0)

    _RVM1(0x1E13, PWM_MODE, BITMASK(2:0)),
*/
//    #define PF_CS1_EN ((PADS_PF_CS1_EN == PAD_PF_A25) ? (BIT0) : 0)

//    _RVM1(0x1E1E, PF_CS1_EN, BIT0),

//    #define HSYNC_EN ((PADS_HSYNC_EN == PAD_HSYNC_OUT) ? (BIT0) : 0)

//    _RVM1(0x1E16, HSYNC_EN, BIT0),

//    #define VSYNC_EN ((PADS_VSYNC_EN == PAD_VSYNC_OUT) ? (BIT4) : 0)

//    _RVM1(0x1E16, VSYNC_EN, BIT4),

    // UART MUX
/*
    #define SECOND_UART_MODE ((PADS_SECOND_UART_MODE == PAD_HSYNC_OUT) ? (BIT0) :
                        (PADS_SECOND_UART_MODE == PAD_VSYNC_OUT) ? (BIT0) : \
                         (PADS_SECOND_UART_MODE == PAD_I2CM0_SDA) ? (BIT1) : \
                        (PADS_SECOND_UART_MODE == PAD_I2CM0_SCL) ? (BIT1) :
                        (PADS_SECOND_UART_MODE == PAD_TS1_CLK) ? (BIT2) :
                        (PADS_SECOND_UART_MODE == PAD_TS1_SYNC) ? (BIT2) : 0)

    _RVM1(0x1E06, SECOND_UART_MODE, BITMASK(2:0)),
*/
/*
    #define THIRD_UART_MODE ((PADS_THIRD_UART_MODE == PAD_TS1_D7) ? (BIT4) : \
                           (PADS_THIRD_UART_MODE == PAD_TS1_D6) ? (BIT4) : 0)
                           (PADS_THIRD_UART_MODE == PAD_PF_A4) ? (BIT5) :
                           (PADS_THIRD_UART_MODE == PAD_PF_A3) ? (BIT5) : 0)
                           (PADS_THIRD_UART_MODE == PAD_I2S_OUT_SD2) ? (BIT5|BIT4) :
                           (PADS_THIRD_UART_MODE == PAD_I2S_OUT_SD3) ? (BIT5|BIT4) : 0)

    _RVM1(0x1E06, THIRD_UART_MODE, BITMASK(5:4)),
*/
/*
    #define FOURTH_UART_MODE ((PADS_FOURTH_UART_MODE == PAD_ET_RXD2) ? (BIT0) : \
                           (PADS_FOURTH_UART_MODE == PAD_ET_RXD3) ? (BIT0) : \
                          (PADS_FOURTH_UART_MODE == PAD_TS0_D1) ? (BIT1) : \
                           (PADS_FOURTH_UART_MODE == PAD_TS0_D0) ? (BIT1) : 0)
                           (PADS_FOURTH_UART_MODE == PAD_HSYNC_OUT) ? (BIT1|BIT0) : \
                           (PADS_FOURTH_UART_MODE == PAD_VSYNC_OUT) ? (BIT1|BIT0) : 0)

    _RVM1(0x1E07, FOURTH_UART_MODE, BITMASK(1:0)),
*/

    #if(PIN_199_IS_GPIO == GPIO_OUT_LOW)
    //#define EXTERNAL_EMAC_OEN (PIN_199_IS_GPIO == GPIO_OUT_HIGH ? 1: 0)
    _RVM1(0x2650, 0, BIT5),
    _RVM1(0x2650, 0, BIT4),
    #elif (PIN_199_IS_GPIO == GPIO_OUT_HIGH)
    _RVM1(0x2650, (1<<4), BITMASK(BIT5:BIT4)),
    #endif

//---------------------------------------------------------------------
// Kronus U02 to fix smart card problem in 216 pin package
//---------------------------------------------------------------------
//#if (MS_BOARD_TYPE_SEL != BD_MST124E_D01A_S && MS_BOARD_TYPE_SEL != BD_MST124E_D01A_SZ)
//    _RVM1(0x1E45, 0, BIT2), // reg_156_mode set to 0 if the package is not 156 pin for SMC
//#endif
//---------------------------------------------------------------------
    // UART_SRC_SEL

    #define UART_INV    ((UART0_INV ? BIT0 : 0) | \
                         (UART1_INV ? BIT1 : 0) | \
                         (UART2_INV ? BIT2 : 0) | \
                         (UART3_INV ? BIT3 : 0) | \
                         (UART4_INV ? BIT4 : 0))

    _RVM1(0x1EAB, UART_INV, BITMASK(7:0)),

    _RVM1(0x1EA6, (UART1_SRC_SEL << 4) | (UART0_SRC_SEL << 0), BITMASK(7:0)),
    _RVM1(0x1EA7, (UART3_SRC_SEL << 4) | (UART2_SRC_SEL << 0), BITMASK(7:0)),
    _RVM1(0x1EA8, (UART4_SRC_SEL << 0), BITMASK(3:0)),


    // swtich to EJTAG3
    //_RVM1(0x1E2E, BIT1|BIT2, BITMASK(2:1)),

    _MEMMAP_PM_,

    _RVM1(0x0E13, BIT3, BIT3),   // RX0_ENABLE
    _RVM1(0x0E13, 0 , BIT4),   // UART0 -> reg_uart_sel0
#if 0
    #define SEL_CZ_ON   ((PIN_SPI_CZ1 ? BIT5 : 0) | \
                         (PIN_SPI_CZ2 ? BIT6 : 0) | \
                         (PIN_SPI_CZ3 ? BIT7 : 0))

    _RVM1(0x3C1D, ~(SEL_CZ_ON), BITMASK(7:5)),
#endif

    // VPLUG_IN_PWRGD mode setting in PAD_SAR3
    // 1. 0x1411[3:0] reg_sar_aisel:
    //      Pad GPIO/Ain switch: 1: analog input, 0: GPIO
    // 2. 0x1411[11:8] reg_oen_sar_gpio:
    //      Output enable for GPIO pad: 0: enable, 1: disable
    // 3. 0x1413[10] reg_sel_hvdetect:
    //      1'b0: VPLUG_IN_PWRGD = 1, 1'b1: VPLUG_IN_PWRGD = the power status of PAD_SAR3
    _RVM1(0x1422, BIT3, BIT3),
    _RVM1(0x1423, BIT3, BIT3),
    _RVM1(0x1427, BIT2, BIT2),

    _MEMMAP_nonPM_,

    // Clear all pad in
    _RVM1(0x1EA1, 0, BIT7),
    _END_OF_TBL2_,

//---------------------------------------------------------------------
// ISP_TOOL Write Protect (Need to check ????)
//---------------------------------------------------------------------
#if 0
#else
    //external flash #1
    _MEMMAP_PM_,
    _RVM1(0x0E6A, 0x00, BIT0), //reg_spi_gpio set to 0 (swtch to spi_do, spi_di, spi_ck)
    _RVM1(0x0E6A, 0x00, BIT1), //reg_spicsz0_gpio set to 0 (enable spi_cz0)
    // David 20130817, the address change?
    //_RVM1(0x08F4, 0x00, 0xFF), //reg_chip_select set to 0 (select embedded SPI Flash)
    //#if (PIN_FLASH_WP0)
    //_RVM1(0x0E21, BIT0, BIT0),
    //_RVM1(0x0E1F,    0, BIT0),
    //#endif
    _END_OF_TBL2_,

    //external flash #2
    _MEMMAP_PM_,
    _RVM1(0x0E6A, 0x00, BIT0), //reg_spi_gpio set to 0 (swtch to spi_do, spi_di, spi_ck)
    #if (PIN_SPI_CZ1)
    _RVM1(0x0E6A, 0x00, BIT2), //reg_spicsz1_gpio set to 0 (enable spi_cz1)
    // David 20130817, the address change?
    //_RVM1(0x08F4, 0x01, 0xFF), //reg_chip_select set to 1 (select external flash #1)
    //#if (PIN_FLASH_WP1)
    //_RVM1(0x0E21, BIT0, BIT0),
    //_RVM1(0x0E1F,    0, BIT0),
    //#endif
    _END_OF_TBL2_,
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



