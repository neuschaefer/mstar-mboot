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
// (MStar Confidential Information) by the recipient.
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
#include "hwreg_KAISER.h"
#include "chip/bond.h"

#define GPIO_NONE               0       // Not GPIO pin (default)
#define GPIO_IN                 1       // GPI
#define GPIO_OUT_LOW            2       // GPO output low
#define GPIO_OUT_HIGH           3       // GPO output high

#define _MEMMAP_nonPM_  _RVM1(0x0000, 0x10, 0xFF)
#define _MEMMAP_PM_     _RVM1(0x0000, 0x00, 0xFF)

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

#if(PAD_I2S_OUT_WS_IS_GPIO != GPIO_NONE)
 #define PAD_I2S_OUT_WS_OEN (PAD_I2S_OUT_WS_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_I2S_OUT_WS_OUT (PAD_I2S_OUT_WS_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x262e, PAD_I2S_OUT_WS_OUT, BIT5),
     _RVM1(0x262e, PAD_I2S_OUT_WS_OEN, BIT5),
 #endif

 #if(PAD_I2S_OUT_MCK_IS_GPIO != GPIO_NONE)
 #define PAD_I2S_OUT_MCK_OEN (PAD_I2S_OUT_MCK_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_I2S_OUT_MCK_OUT (PAD_I2S_OUT_MCK_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2630, PAD_I2S_OUT_MCK_OUT, BIT5),
     _RVM1(0x2630, PAD_I2S_OUT_MCK_OEN, BIT5),
 #endif

 #if(PAD_I2S_OUT_BCK_IS_GPIO != GPIO_NONE)
 #define PAD_I2S_OUT_BCK_OEN (PAD_I2S_OUT_BCK_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_I2S_OUT_BCK_OUT (PAD_I2S_OUT_BCK_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2632, PAD_I2S_OUT_BCK_OUT, BIT5),
     _RVM1(0x2632, PAD_I2S_OUT_BCK_OEN, BIT5),
 #endif

 #if(PAD_I2S_OUT_SD0_IS_GPIO != GPIO_NONE)
 #define PAD_I2S_OUT_SD0_OEN (PAD_I2S_OUT_SD0_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_I2S_OUT_SD0_OUT (PAD_I2S_OUT_SD0_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2634, PAD_I2S_OUT_SD0_OUT, BIT5),
     _RVM1(0x2634, PAD_I2S_OUT_SD0_OEN, BIT5),
 #endif

 #if(PAD_I2S_OUT_SD1_IS_GPIO != GPIO_NONE)
 #define PAD_I2S_OUT_SD1_OEN (PAD_I2S_OUT_SD1_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_I2S_OUT_SD1_OUT (PAD_I2S_OUT_SD1_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2636, PAD_I2S_OUT_SD1_OUT, BIT5),
     _RVM1(0x2636, PAD_I2S_OUT_SD1_OEN, BIT5),
 #endif

 #if(PAD_I2S_OUT_SD2_IS_GPIO != GPIO_NONE)
 #define PAD_I2S_OUT_SD2_OEN (PAD_I2S_OUT_SD2_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_I2S_OUT_SD2_OUT (PAD_I2S_OUT_SD2_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2638, PAD_I2S_OUT_SD2_OUT, BIT5),
     _RVM1(0x2638, PAD_I2S_OUT_SD2_OEN, BIT5),
 #endif

 #if(PAD_I2S_OUT_SD3_IS_GPIO != GPIO_NONE)
 #define PAD_I2S_OUT_SD3_OEN (PAD_I2S_OUT_SD3_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_I2S_OUT_SD3_OUT (PAD_I2S_OUT_SD3_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x263a, PAD_I2S_OUT_SD3_OUT, BIT5),
     _RVM1(0x263a, PAD_I2S_OUT_SD3_OEN, BIT5),
 #endif

 #if(PAD_SDIO_CLK_IS_GPIO != GPIO_NONE)
 #define PAD_SDIO_CLK_OEN (PAD_SDIO_CLK_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_SDIO_CLK_OUT (PAD_SDIO_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2676, PAD_SDIO_CLK_OUT, BIT5),
     _RVM1(0x2676, PAD_SDIO_CLK_OEN, BIT5),
 #endif

 #if(PAD_SDIO_CMD_IS_GPIO != GPIO_NONE)
 #define PAD_SDIO_CMD_OEN (PAD_SDIO_CMD_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_SDIO_CMD_OUT (PAD_SDIO_CMD_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2678, PAD_SDIO_CMD_OUT, BIT5),
     _RVM1(0x2678, PAD_SDIO_CMD_OEN, BIT5),
 #endif

 #if(PAD_SDIO_D0_IS_GPIO != GPIO_NONE)
 #define PAD_SDIO_D0_OEN (PAD_SDIO_D0_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_SDIO_D0_OUT (PAD_SDIO_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x267a, PAD_SDIO_D0_OUT, BIT5),
     _RVM1(0x267a, PAD_SDIO_D0_OEN, BIT5),
 #endif

 #if(PAD_SDIO_D1_IS_GPIO != GPIO_NONE)
 #define PAD_SDIO_D1_OEN (PAD_SDIO_D1_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_SDIO_D1_OUT (PAD_SDIO_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x267c, PAD_SDIO_D1_OUT, BIT5),
     _RVM1(0x267c, PAD_SDIO_D1_OEN, BIT5),
 #endif

 #if(PAD_SDIO_D2_IS_GPIO != GPIO_NONE)
 #define PAD_SDIO_D2_OEN (PAD_SDIO_D2_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_SDIO_D2_OUT (PAD_SDIO_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x267e, PAD_SDIO_D2_OUT, BIT5),
     _RVM1(0x267e, PAD_SDIO_D2_OEN, BIT5),
 #endif

 #if(PAD_SDIO_D3_IS_GPIO != GPIO_NONE)
 #define PAD_SDIO_D3_OEN (PAD_SDIO_D3_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_SDIO_D3_OUT (PAD_SDIO_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2680, PAD_SDIO_D3_OUT, BIT5),
     _RVM1(0x2680, PAD_SDIO_D3_OEN, BIT5),
 #endif

 #if(PAD_SM0_CD_IS_GPIO != GPIO_NONE)
 #define PAD_SM0_CD_OEN (PAD_SM0_CD_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_SM0_CD_OUT (PAD_SM0_CD_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2500, PAD_SM0_CD_OUT, BIT5),
     _RVM1(0x2500, PAD_SM0_CD_OEN, BIT5),
 #endif

 #if(PAD_SM0_RST_IS_GPIO != GPIO_NONE)
 #define PAD_SM0_RST_OEN (PAD_SM0_RST_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_SM0_RST_OUT (PAD_SM0_RST_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2502, PAD_SM0_RST_OUT, BIT5),
     _RVM1(0x2502, PAD_SM0_RST_OEN, BIT5),
 #endif

 #if(PAD_SM0_VCC_IS_GPIO != GPIO_NONE)
 #define PAD_SM0_VCC_OEN (PAD_SM0_VCC_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_SM0_VCC_OUT (PAD_SM0_VCC_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2504, PAD_SM0_VCC_OUT, BIT5),
     _RVM1(0x2504, PAD_SM0_VCC_OEN, BIT5),
 #endif

 #if(PAD_SM0_IO_IS_GPIO != GPIO_NONE)
 #define PAD_SM0_IO_OEN (PAD_SM0_IO_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_SM0_IO_OUT (PAD_SM0_IO_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2506, PAD_SM0_IO_OUT, BIT5),
     _RVM1(0x2506, PAD_SM0_IO_OEN, BIT5),
 #endif

 #if(PAD_SM0_CLK_IS_GPIO != GPIO_NONE)
 #define PAD_SM0_CLK_OEN (PAD_SM0_CLK_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_SM0_CLK_OUT (PAD_SM0_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2508, PAD_SM0_CLK_OUT, BIT5),
     _RVM1(0x2508, PAD_SM0_CLK_OEN, BIT5),
 #endif

 #if(PAD_SM0_GPIO0_IS_GPIO != GPIO_NONE)
 #define PAD_SM0_GPIO0_OEN (PAD_SM0_GPIO0_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_SM0_GPIO0_OUT (PAD_SM0_GPIO0_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x250a, PAD_SM0_GPIO0_OUT, BIT5),
     _RVM1(0x250a, PAD_SM0_GPIO0_OEN, BIT5),
 #endif

 #if(PAD_SM0_GPIO1_IS_GPIO != GPIO_NONE)
 #define PAD_SM0_GPIO1_OEN (PAD_SM0_GPIO1_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_SM0_GPIO1_OUT (PAD_SM0_GPIO1_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x250c, PAD_SM0_GPIO1_OUT, BIT5),
     _RVM1(0x250c, PAD_SM0_GPIO1_OEN, BIT5),
 #endif

 #if(PAD_SM1_CD_IS_GPIO != GPIO_NONE)
 #define PAD_SM1_CD_OEN (PAD_SM1_CD_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_SM1_CD_OUT (PAD_SM1_CD_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x250e, PAD_SM1_CD_OUT, BIT5),
     _RVM1(0x250e, PAD_SM1_CD_OEN, BIT5),
 #endif

 #if(PAD_SM1_RST_IS_GPIO != GPIO_NONE)
 #define PAD_SM1_RST_OEN (PAD_SM1_RST_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_SM1_RST_OUT (PAD_SM1_RST_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2510, PAD_SM1_RST_OUT, BIT5),
     _RVM1(0x2510, PAD_SM1_RST_OEN, BIT5),
 #endif

 #if(PAD_SM1_VCC_IS_GPIO != GPIO_NONE)
 #define PAD_SM1_VCC_OEN (PAD_SM1_VCC_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_SM1_VCC_OUT (PAD_SM1_VCC_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2512, PAD_SM1_VCC_OUT, BIT5),
     _RVM1(0x2512, PAD_SM1_VCC_OEN, BIT5),
 #endif

 #if(PAD_SM1_IO_IS_GPIO != GPIO_NONE)
 #define PAD_SM1_IO_OEN (PAD_SM1_IO_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_SM1_IO_OUT (PAD_SM1_IO_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2514, PAD_SM1_IO_OUT, BIT5),
     _RVM1(0x2514, PAD_SM1_IO_OEN, BIT5),
 #endif

 #if(PAD_SM1_CLK_IS_GPIO != GPIO_NONE)
 #define PAD_SM1_CLK_OEN (PAD_SM1_CLK_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_SM1_CLK_OUT (PAD_SM1_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2516, PAD_SM1_CLK_OUT, BIT5),
     _RVM1(0x2516, PAD_SM1_CLK_OEN, BIT5),
 #endif

 #if(PAD_SM1_GPIO0_IS_GPIO != GPIO_NONE)
 #define PAD_SM1_GPIO0_OEN (PAD_SM1_GPIO0_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_SM1_GPIO0_OUT (PAD_SM1_GPIO0_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2518, PAD_SM1_GPIO0_OUT, BIT5),
     _RVM1(0x2518, PAD_SM1_GPIO0_OEN, BIT5),
 #endif

 #if(PAD_SM1_GPIO1_IS_GPIO != GPIO_NONE)
 #define PAD_SM1_GPIO1_OEN (PAD_SM1_GPIO1_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_SM1_GPIO1_OUT (PAD_SM1_GPIO1_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x251a, PAD_SM1_GPIO1_OUT, BIT5),
     _RVM1(0x251a, PAD_SM1_GPIO1_OEN, BIT5),
 #endif

 #if(PAD_EJ_DINT_IS_GPIO != GPIO_NONE)
 #define PAD_EJ_DINT_OEN (PAD_EJ_DINT_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_EJ_DINT_OUT (PAD_EJ_DINT_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x268e, PAD_EJ_DINT_OUT, BIT5),
     _RVM1(0x268e, PAD_EJ_DINT_OEN, BIT5),
 #endif

 #if(PAD_EJ_RSTZ_IS_GPIO != GPIO_NONE)
 #define PAD_EJ_RSTZ_OEN (PAD_EJ_RSTZ_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_EJ_RSTZ_OUT (PAD_EJ_RSTZ_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2690, PAD_EJ_RSTZ_OUT, BIT5),
     _RVM1(0x2690, PAD_EJ_RSTZ_OEN, BIT5),
 #endif

 #if(PAD_CI_A0_IS_GPIO != GPIO_NONE)
 #define PAD_CI_A0_OEN (PAD_CI_A0_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_A0_OUT (PAD_CI_A0_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x255a, PAD_CI_A0_OUT, BIT5),
     _RVM1(0x255a, PAD_CI_A0_OEN, BIT5),
 #endif

 #if(PAD_CI_A1_IS_GPIO != GPIO_NONE)
 #define PAD_CI_A1_OEN (PAD_CI_A1_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_A1_OUT (PAD_CI_A1_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x255c, PAD_CI_A1_OUT, BIT5),
     _RVM1(0x255c, PAD_CI_A1_OEN, BIT5),
 #endif

 #if(PAD_CI_A2_IS_GPIO != GPIO_NONE)
 #define PAD_CI_A2_OEN (PAD_CI_A2_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_A2_OUT (PAD_CI_A2_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x255e, PAD_CI_A2_OUT, BIT5),
     _RVM1(0x255e, PAD_CI_A2_OEN, BIT5),
 #endif

 #if(PAD_CI_A3_IS_GPIO != GPIO_NONE)
 #define PAD_CI_A3_OEN (PAD_CI_A3_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_A3_OUT (PAD_CI_A3_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2560, PAD_CI_A3_OUT, BIT5),
     _RVM1(0x2560, PAD_CI_A3_OEN, BIT5),
 #endif

 #if(PAD_CI_A4_IS_GPIO != GPIO_NONE)
 #define PAD_CI_A4_OEN (PAD_CI_A4_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_A4_OUT (PAD_CI_A4_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2562, PAD_CI_A4_OUT, BIT5),
     _RVM1(0x2562, PAD_CI_A4_OEN, BIT5),
 #endif

 #if(PAD_CI_A5_IS_GPIO != GPIO_NONE)
 #define PAD_CI_A5_OEN (PAD_CI_A5_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_A5_OUT (PAD_CI_A5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2564, PAD_CI_A5_OUT, BIT5),
     _RVM1(0x2564, PAD_CI_A5_OEN, BIT5),
 #endif

 #if(PAD_CI_A6_IS_GPIO != GPIO_NONE)
 #define PAD_CI_A6_OEN (PAD_CI_A6_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_A6_OUT (PAD_CI_A6_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2566, PAD_CI_A6_OUT, BIT5),
     _RVM1(0x2566, PAD_CI_A6_OEN, BIT5),
 #endif

 #if(PAD_CI_A7_IS_GPIO != GPIO_NONE)
 #define PAD_CI_A7_OEN (PAD_CI_A7_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_A7_OUT (PAD_CI_A7_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2568, PAD_CI_A7_OUT, BIT5),
     _RVM1(0x2568, PAD_CI_A7_OEN, BIT5),
 #endif

 #if(PAD_CI_A8_IS_GPIO != GPIO_NONE)
 #define PAD_CI_A8_OEN (PAD_CI_A8_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_A8_OUT (PAD_CI_A8_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x256a, PAD_CI_A8_OUT, BIT5),
     _RVM1(0x256a, PAD_CI_A8_OEN, BIT5),
 #endif

 #if(PAD_CI_A9_IS_GPIO != GPIO_NONE)
 #define PAD_CI_A9_OEN (PAD_CI_A9_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_A9_OUT (PAD_CI_A9_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x256c, PAD_CI_A9_OUT, BIT5),
     _RVM1(0x256c, PAD_CI_A9_OEN, BIT5),
 #endif

 #if(PAD_CI_A10_IS_GPIO != GPIO_NONE)
 #define PAD_CI_A10_OEN (PAD_CI_A10_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_A10_OUT (PAD_CI_A10_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x256e, PAD_CI_A10_OUT, BIT5),
     _RVM1(0x256e, PAD_CI_A10_OEN, BIT5),
 #endif

 #if(PAD_CI_A11_IS_GPIO != GPIO_NONE)
 #define PAD_CI_A11_OEN (PAD_CI_A11_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_A11_OUT (PAD_CI_A11_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2570, PAD_CI_A11_OUT, BIT5),
     _RVM1(0x2570, PAD_CI_A11_OEN, BIT5),
 #endif

 #if(PAD_CI_A12_IS_GPIO != GPIO_NONE)
 #define PAD_CI_A12_OEN (PAD_CI_A12_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_A12_OUT (PAD_CI_A12_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2572, PAD_CI_A12_OUT, BIT5),
     _RVM1(0x2572, PAD_CI_A12_OEN, BIT5),
 #endif

 #if(PAD_CI_A13_IS_GPIO != GPIO_NONE)
 #define PAD_CI_A13_OEN (PAD_CI_A13_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_A13_OUT (PAD_CI_A13_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2574, PAD_CI_A13_OUT, BIT5),
     _RVM1(0x2574, PAD_CI_A13_OEN, BIT5),
 #endif

 #if(PAD_CI_A14_IS_GPIO != GPIO_NONE)
 #define PAD_CI_A14_OEN (PAD_CI_A14_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_A14_OUT (PAD_CI_A14_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2576, PAD_CI_A14_OUT, BIT5),
     _RVM1(0x2576, PAD_CI_A14_OEN, BIT5),
 #endif

 #if(PAD_CI_D0_IS_GPIO != GPIO_NONE)
 #define PAD_CI_D0_OEN (PAD_CI_D0_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_D0_OUT (PAD_CI_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2578, PAD_CI_D0_OUT, BIT5),
     _RVM1(0x2578, PAD_CI_D0_OEN, BIT5),
 #endif

 #if(PAD_CI_D1_IS_GPIO != GPIO_NONE)
 #define PAD_CI_D1_OEN (PAD_CI_D1_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_D1_OUT (PAD_CI_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x257a, PAD_CI_D1_OUT, BIT5),
     _RVM1(0x257a, PAD_CI_D1_OEN, BIT5),
 #endif

 #if(PAD_CI_D2_IS_GPIO != GPIO_NONE)
 #define PAD_CI_D2_OEN (PAD_CI_D2_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_D2_OUT (PAD_CI_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x257c, PAD_CI_D2_OUT, BIT5),
     _RVM1(0x257c, PAD_CI_D2_OEN, BIT5),
 #endif

 #if(PAD_CI_D3_IS_GPIO != GPIO_NONE)
 #define PAD_CI_D3_OEN (PAD_CI_D3_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_D3_OUT (PAD_CI_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x257e, PAD_CI_D3_OUT, BIT5),
     _RVM1(0x257e, PAD_CI_D3_OEN, BIT5),
 #endif

 #if(PAD_CI_D4_IS_GPIO != GPIO_NONE)
 #define PAD_CI_D4_OEN (PAD_CI_D4_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_D4_OUT (PAD_CI_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2580, PAD_CI_D4_OUT, BIT5),
     _RVM1(0x2580, PAD_CI_D4_OEN, BIT5),
 #endif

 #if(PAD_CI_D5_IS_GPIO != GPIO_NONE)
 #define PAD_CI_D5_OEN (PAD_CI_D5_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_D5_OUT (PAD_CI_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2582, PAD_CI_D5_OUT, BIT5),
     _RVM1(0x2582, PAD_CI_D5_OEN, BIT5),
 #endif

 #if(PAD_CI_D6_IS_GPIO != GPIO_NONE)
 #define PAD_CI_D6_OEN (PAD_CI_D6_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_D6_OUT (PAD_CI_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2584, PAD_CI_D6_OUT, BIT5),
     _RVM1(0x2584, PAD_CI_D6_OEN, BIT5),
 #endif

 #if(PAD_CI_D7_IS_GPIO != GPIO_NONE)
 #define PAD_CI_D7_OEN (PAD_CI_D7_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_D7_OUT (PAD_CI_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2586, PAD_CI_D7_OUT, BIT5),
     _RVM1(0x2586, PAD_CI_D7_OEN, BIT5),
 #endif

 #if(PAD_CI_IRQAZ_IS_GPIO != GPIO_NONE)
 #define PAD_CI_IRQAZ_OEN (PAD_CI_IRQAZ_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_IRQAZ_OUT (PAD_CI_IRQAZ_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2588, PAD_CI_IRQAZ_OUT, BIT5),
     _RVM1(0x2588, PAD_CI_IRQAZ_OEN, BIT5),
 #endif

 #if(PAD_CI_RST_IS_GPIO != GPIO_NONE)
 #define PAD_CI_RST_OEN (PAD_CI_RST_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_RST_OUT (PAD_CI_RST_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x258a, PAD_CI_RST_OUT, BIT5),
     _RVM1(0x258a, PAD_CI_RST_OEN, BIT5),
 #endif

 #if(PAD_CI_IORDZ_IS_GPIO != GPIO_NONE)
 #define PAD_CI_IORDZ_OEN (PAD_CI_IORDZ_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_IORDZ_OUT (PAD_CI_IORDZ_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x258c, PAD_CI_IORDZ_OUT, BIT5),
     _RVM1(0x258c, PAD_CI_IORDZ_OEN, BIT5),
 #endif

 #if(PAD_CI_IOWRZ_IS_GPIO != GPIO_NONE)
 #define PAD_CI_IOWRZ_OEN (PAD_CI_IOWRZ_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_IOWRZ_OUT (PAD_CI_IOWRZ_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x258e, PAD_CI_IOWRZ_OUT, BIT5),
     _RVM1(0x258e, PAD_CI_IOWRZ_OEN, BIT5),
 #endif

 #if(PAD_CI_OEZ_IS_GPIO != GPIO_NONE)
 #define PAD_CI_OEZ_OEN (PAD_CI_OEZ_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_OEZ_OUT (PAD_CI_OEZ_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2590, PAD_CI_OEZ_OUT, BIT5),
     _RVM1(0x2590, PAD_CI_OEZ_OEN, BIT5),
 #endif

 #if(PAD_CI_WEZ_IS_GPIO != GPIO_NONE)
 #define PAD_CI_WEZ_OEN (PAD_CI_WEZ_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_WEZ_OUT (PAD_CI_WEZ_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2592, PAD_CI_WEZ_OUT, BIT5),
     _RVM1(0x2592, PAD_CI_WEZ_OEN, BIT5),
 #endif

 #if(PAD_CI_REGZ_IS_GPIO != GPIO_NONE)
 #define PAD_CI_REGZ_OEN (PAD_CI_REGZ_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_REGZ_OUT (PAD_CI_REGZ_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2594, PAD_CI_REGZ_OUT, BIT5),
     _RVM1(0x2594, PAD_CI_REGZ_OEN, BIT5),
 #endif

 #if(PAD_CI_CEZ_IS_GPIO != GPIO_NONE)
 #define PAD_CI_CEZ_OEN (PAD_CI_CEZ_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_CEZ_OUT (PAD_CI_CEZ_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2596, PAD_CI_CEZ_OUT, BIT5),
     _RVM1(0x2596, PAD_CI_CEZ_OEN, BIT5),
 #endif

 #if(PAD_CI_WAITZ_IS_GPIO != GPIO_NONE)
 #define PAD_CI_WAITZ_OEN (PAD_CI_WAITZ_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_WAITZ_OUT (PAD_CI_WAITZ_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2598, PAD_CI_WAITZ_OUT, BIT5),
     _RVM1(0x2598, PAD_CI_WAITZ_OEN, BIT5),
 #endif

 #if(PAD_CI_CDZ_IS_GPIO != GPIO_NONE)
 #define PAD_CI_CDZ_OEN (PAD_CI_CDZ_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_CI_CDZ_OUT (PAD_CI_CDZ_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x259a, PAD_CI_CDZ_OUT, BIT5),
     _RVM1(0x259a, PAD_CI_CDZ_OEN, BIT5),
 #endif

 #if(PAD_I2CM1_SDA_IS_GPIO != GPIO_NONE)
 #define PAD_I2CM1_SDA_OEN (PAD_I2CM1_SDA_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_I2CM1_SDA_OUT (PAD_I2CM1_SDA_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2520, PAD_I2CM1_SDA_OUT, BIT5),
     _RVM1(0x2520, PAD_I2CM1_SDA_OEN, BIT5),
 #endif

 #if(PAD_I2CM1_SCL_IS_GPIO != GPIO_NONE)
 #define PAD_I2CM1_SCL_OEN (PAD_I2CM1_SCL_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_I2CM1_SCL_OUT (PAD_I2CM1_SCL_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2522, PAD_I2CM1_SCL_OUT, BIT5),
     _RVM1(0x2522, PAD_I2CM1_SCL_OEN, BIT5),
 #endif

 #if(PAD_TS3_CLK_IS_GPIO != GPIO_NONE)
 #define PAD_TS3_CLK_OEN (PAD_TS3_CLK_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS3_CLK_OUT (PAD_TS3_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2592, PAD_TS3_CLK_OUT, BIT5),
     _RVM1(0x2592, PAD_TS3_CLK_OEN, BIT5),
 #endif

 #if(PAD_TS3_SYNC_IS_GPIO != GPIO_NONE)
 #define PAD_TS3_SYNC_OEN (PAD_TS3_SYNC_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS3_SYNC_OUT (PAD_TS3_SYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2594, PAD_TS3_SYNC_OUT, BIT5),
     _RVM1(0x2594, PAD_TS3_SYNC_OEN, BIT5),
 #endif

 #if(PAD_TS3_VLD_IS_GPIO != GPIO_NONE)
 #define PAD_TS3_VLD_OEN (PAD_TS3_VLD_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS3_VLD_OUT (PAD_TS3_VLD_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2596, PAD_TS3_VLD_OUT, BIT5),
     _RVM1(0x2596, PAD_TS3_VLD_OEN, BIT5),
 #endif

 #if(PAD_TS3_D0_IS_GPIO != GPIO_NONE)
 #define PAD_TS3_D0_OEN (PAD_TS3_D0_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS3_D0_OUT (PAD_TS3_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2598, PAD_TS3_D0_OUT, BIT5),
     _RVM1(0x2598, PAD_TS3_D0_OEN, BIT5),
 #endif

 #if(PAD_TS3_D1_IS_GPIO != GPIO_NONE)
 #define PAD_TS3_D1_OEN (PAD_TS3_D1_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS3_D1_OUT (PAD_TS3_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x259a, PAD_TS3_D1_OUT, BIT5),
     _RVM1(0x259a, PAD_TS3_D1_OEN, BIT5),
 #endif

 #if(PAD_TS3_D2_IS_GPIO != GPIO_NONE)
 #define PAD_TS3_D2_OEN (PAD_TS3_D2_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS3_D2_OUT (PAD_TS3_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x259c, PAD_TS3_D2_OUT, BIT5),
     _RVM1(0x259c, PAD_TS3_D2_OEN, BIT5),
 #endif

 #if(PAD_TS3_D3_IS_GPIO != GPIO_NONE)
 #define PAD_TS3_D3_OEN (PAD_TS3_D3_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS3_D3_OUT (PAD_TS3_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x259e, PAD_TS3_D3_OUT, BIT5),
     _RVM1(0x259e, PAD_TS3_D3_OEN, BIT5),
 #endif

 #if(PAD_TS3_D4_IS_GPIO != GPIO_NONE)
 #define PAD_TS3_D4_OEN (PAD_TS3_D4_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS3_D4_OUT (PAD_TS3_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x25a0, PAD_TS3_D4_OUT, BIT5),
     _RVM1(0x25a0, PAD_TS3_D4_OEN, BIT5),
 #endif

 #if(PAD_TS3_D5_IS_GPIO != GPIO_NONE)
 #define PAD_TS3_D5_OEN (PAD_TS3_D5_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS3_D5_OUT (PAD_TS3_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x25a2, PAD_TS3_D5_OUT, BIT5),
     _RVM1(0x25a2, PAD_TS3_D5_OEN, BIT5),
 #endif

 #if(PAD_TS3_D6_IS_GPIO != GPIO_NONE)
 #define PAD_TS3_D6_OEN (PAD_TS3_D6_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS3_D6_OUT (PAD_TS3_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x25a4, PAD_TS3_D6_OUT, BIT5),
     _RVM1(0x25a4, PAD_TS3_D6_OEN, BIT5),
 #endif

 #if(PAD_TS3_D7_IS_GPIO != GPIO_NONE)
 #define PAD_TS3_D7_OEN (PAD_TS3_D7_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS3_D7_OUT (PAD_TS3_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x25a6, PAD_TS3_D7_OUT, BIT5),
     _RVM1(0x25a6, PAD_TS3_D7_OEN, BIT5),
 #endif

 #if(PAD_I2CM0_SDA_IS_GPIO != GPIO_NONE)
 #define PAD_I2CM0_SDA_OEN (PAD_I2CM0_SDA_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_I2CM0_SDA_OUT (PAD_I2CM0_SDA_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x251c, PAD_I2CM0_SDA_OUT, BIT5),
     _RVM1(0x251c, PAD_I2CM0_SDA_OEN, BIT5),
 #endif

 #if(PAD_I2CM0_SCL_IS_GPIO != GPIO_NONE)
 #define PAD_I2CM0_SCL_OEN (PAD_I2CM0_SCL_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_I2CM0_SCL_OUT (PAD_I2CM0_SCL_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x251e, PAD_I2CM0_SCL_OUT, BIT5),
     _RVM1(0x251e, PAD_I2CM0_SCL_OEN, BIT5),
 #endif

 #if(PAD_SPDIF_OUT_IS_GPIO != GPIO_NONE)
 #define PAD_SPDIF_OUT_OEN (PAD_SPDIF_OUT_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_SPDIF_OUT_OUT (PAD_SPDIF_OUT_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x262c, PAD_SPDIF_OUT_OUT, BIT5),
     _RVM1(0x262c, PAD_SPDIF_OUT_OEN, BIT5),
 #endif

 #if(PAD_EJ_TDO_IS_GPIO != GPIO_NONE)
 #define PAD_EJ_TDO_OEN (PAD_EJ_TDO_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_EJ_TDO_OUT (PAD_EJ_TDO_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2684, PAD_EJ_TDO_OUT, BIT5),
     _RVM1(0x2684, PAD_EJ_TDO_OEN, BIT5),
 #endif

 #if(PAD_EJ_TDI_IS_GPIO != GPIO_NONE)
 #define PAD_EJ_TDI_OEN (PAD_EJ_TDI_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_EJ_TDI_OUT (PAD_EJ_TDI_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2686, PAD_EJ_TDI_OUT, BIT5),
     _RVM1(0x2686, PAD_EJ_TDI_OEN, BIT5),
 #endif

 #if(PAD_EJ_TMS_IS_GPIO != GPIO_NONE)
 #define PAD_EJ_TMS_OEN (PAD_EJ_TMS_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_EJ_TMS_OUT (PAD_EJ_TMS_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2688, PAD_EJ_TMS_OUT, BIT5),
     _RVM1(0x2688, PAD_EJ_TMS_OEN, BIT5),
 #endif

 #if(PAD_EJ_TCK_IS_GPIO != GPIO_NONE)
 #define PAD_EJ_TCK_OEN (PAD_EJ_TCK_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_EJ_TCK_OUT (PAD_EJ_TCK_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x268a, PAD_EJ_TCK_OUT, BIT5),
     _RVM1(0x268a, PAD_EJ_TCK_OEN, BIT5),
 #endif

 #if(PAD_EJ_TRST_N_IS_GPIO != GPIO_NONE)
 #define PAD_EJ_TRST_N_OEN (PAD_EJ_TRST_N_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_EJ_TRST_N_OUT (PAD_EJ_TRST_N_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x268c, PAD_EJ_TRST_N_OUT, BIT5),
     _RVM1(0x268c, PAD_EJ_TRST_N_OEN, BIT5),
 #endif

 #if(PAD_TS2_CLK_IS_GPIO != GPIO_NONE)
 #define PAD_TS2_CLK_OEN (PAD_TS2_CLK_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS2_CLK_OUT (PAD_TS2_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2550, PAD_TS2_CLK_OUT, BIT5),
     _RVM1(0x2550, PAD_TS2_CLK_OEN, BIT5),
 #endif

 #if(PAD_TS2_SYNC_IS_GPIO != GPIO_NONE)
 #define PAD_TS2_SYNC_OEN (PAD_TS2_SYNC_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS2_SYNC_OUT (PAD_TS2_SYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2552, PAD_TS2_SYNC_OUT, BIT5),
     _RVM1(0x2552, PAD_TS2_SYNC_OEN, BIT5),
 #endif

 #if(PAD_TS2_VLD_IS_GPIO != GPIO_NONE)
 #define PAD_TS2_VLD_OEN (PAD_TS2_VLD_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS2_VLD_OUT (PAD_TS2_VLD_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2554, PAD_TS2_VLD_OUT, BIT5),
     _RVM1(0x2554, PAD_TS2_VLD_OEN, BIT5),
 #endif

 #if(PAD_TS2_D0_IS_GPIO != GPIO_NONE)
 #define PAD_TS2_D0_OEN (PAD_TS2_D0_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS2_D0_OUT (PAD_TS2_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2556, PAD_TS2_D0_OUT, BIT5),
     _RVM1(0x2556, PAD_TS2_D0_OEN, BIT5),
 #endif

 #if(PAD_TS2_D1_IS_GPIO != GPIO_NONE)
 #define PAD_TS2_D1_OEN (PAD_TS2_D1_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS2_D1_OUT (PAD_TS2_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2558, PAD_TS2_D1_OUT, BIT5),
     _RVM1(0x2558, PAD_TS2_D1_OEN, BIT5),
 #endif

 #if(PAD_TS2_D2_IS_GPIO != GPIO_NONE)
 #define PAD_TS2_D2_OEN (PAD_TS2_D2_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS2_D2_OUT (PAD_TS2_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x255a, PAD_TS2_D2_OUT, BIT5),
     _RVM1(0x255a, PAD_TS2_D2_OEN, BIT5),
 #endif

 #if(PAD_TS2_D3_IS_GPIO != GPIO_NONE)
 #define PAD_TS2_D3_OEN (PAD_TS2_D3_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS2_D3_OUT (PAD_TS2_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x255c, PAD_TS2_D3_OUT, BIT5),
     _RVM1(0x255c, PAD_TS2_D3_OEN, BIT5),
 #endif

 #if(PAD_TS2_D4_IS_GPIO != GPIO_NONE)
 #define PAD_TS2_D4_OEN (PAD_TS2_D4_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS2_D4_OUT (PAD_TS2_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x255e, PAD_TS2_D4_OUT, BIT5),
     _RVM1(0x255e, PAD_TS2_D4_OEN, BIT5),
 #endif

 #if(PAD_TS2_D5_IS_GPIO != GPIO_NONE)
 #define PAD_TS2_D5_OEN (PAD_TS2_D5_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS2_D5_OUT (PAD_TS2_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2560, PAD_TS2_D5_OUT, BIT5),
     _RVM1(0x2560, PAD_TS2_D5_OEN, BIT5),
 #endif

 #if(PAD_TS2_D6_IS_GPIO != GPIO_NONE)
 #define PAD_TS2_D6_OEN (PAD_TS2_D6_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS2_D6_OUT (PAD_TS2_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2562, PAD_TS2_D6_OUT, BIT5),
     _RVM1(0x2562, PAD_TS2_D6_OEN, BIT5),
 #endif

 #if(PAD_TS2_D7_IS_GPIO != GPIO_NONE)
 #define PAD_TS2_D7_OEN (PAD_TS2_D7_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS2_D7_OUT (PAD_TS2_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2564, PAD_TS2_D7_OUT, BIT5),
     _RVM1(0x2564, PAD_TS2_D7_OEN, BIT5),
 #endif

 #if(PAD_TS1_CLK_IS_GPIO != GPIO_NONE)
 #define PAD_TS1_CLK_OEN (PAD_TS1_CLK_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS1_CLK_OUT (PAD_TS1_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x253a, PAD_TS1_CLK_OUT, BIT5),
     _RVM1(0x253a, PAD_TS1_CLK_OEN, BIT5),
 #endif

 #if(PAD_TS1_SYNC_IS_GPIO != GPIO_NONE)
 #define PAD_TS1_SYNC_OEN (PAD_TS1_SYNC_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS1_SYNC_OUT (PAD_TS1_SYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x253c, PAD_TS1_SYNC_OUT, BIT5),
     _RVM1(0x253c, PAD_TS1_SYNC_OEN, BIT5),
 #endif

 #if(PAD_TS1_VLD_IS_GPIO != GPIO_NONE)
 #define PAD_TS1_VLD_OEN (PAD_TS1_VLD_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS1_VLD_OUT (PAD_TS1_VLD_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x253e, PAD_TS1_VLD_OUT, BIT5),
     _RVM1(0x253e, PAD_TS1_VLD_OEN, BIT5),
 #endif

 #if(PAD_TS1_D0_IS_GPIO != GPIO_NONE)
 #define PAD_TS1_D0_OEN (PAD_TS1_D0_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS1_D0_OUT (PAD_TS1_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x254e, PAD_TS1_D0_OUT, BIT5),
     _RVM1(0x254e, PAD_TS1_D0_OEN, BIT5),
 #endif

 #if(PAD_TS1_D1_IS_GPIO != GPIO_NONE)
 #define PAD_TS1_D1_OEN (PAD_TS1_D1_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS1_D1_OUT (PAD_TS1_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x254c, PAD_TS1_D1_OUT, BIT5),
     _RVM1(0x254c, PAD_TS1_D1_OEN, BIT5),
 #endif

 #if(PAD_TS1_D2_IS_GPIO != GPIO_NONE)
 #define PAD_TS1_D2_OEN (PAD_TS1_D2_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS1_D2_OUT (PAD_TS1_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x254a, PAD_TS1_D2_OUT, BIT5),
     _RVM1(0x254a, PAD_TS1_D2_OEN, BIT5),
 #endif

 #if(PAD_TS1_D3_IS_GPIO != GPIO_NONE)
 #define PAD_TS1_D3_OEN (PAD_TS1_D3_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS1_D3_OUT (PAD_TS1_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2548, PAD_TS1_D3_OUT, BIT5),
     _RVM1(0x2548, PAD_TS1_D3_OEN, BIT5),
 #endif

 #if(PAD_TS1_D4_IS_GPIO != GPIO_NONE)
 #define PAD_TS1_D4_OEN (PAD_TS1_D4_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS1_D4_OUT (PAD_TS1_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2546, PAD_TS1_D4_OUT, BIT5),
     _RVM1(0x2546, PAD_TS1_D4_OEN, BIT5),
 #endif

 #if(PAD_TS1_D5_IS_GPIO != GPIO_NONE)
 #define PAD_TS1_D5_OEN (PAD_TS1_D5_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS1_D5_OUT (PAD_TS1_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2544, PAD_TS1_D5_OUT, BIT5),
     _RVM1(0x2544, PAD_TS1_D5_OEN, BIT5),
 #endif

 #if(PAD_TS1_D6_IS_GPIO != GPIO_NONE)
 #define PAD_TS1_D6_OEN (PAD_TS1_D6_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS1_D6_OUT (PAD_TS1_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2542, PAD_TS1_D6_OUT, BIT5),
     _RVM1(0x2542, PAD_TS1_D6_OEN, BIT5),
 #endif

 #if(PAD_TS1_D7_IS_GPIO != GPIO_NONE)
 #define PAD_TS1_D7_OEN (PAD_TS1_D7_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS1_D7_OUT (PAD_TS1_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2540, PAD_TS1_D7_OUT, BIT5),
     _RVM1(0x2540, PAD_TS1_D7_OEN, BIT5),
 #endif

 #if(PAD_TS0_CLK_IS_GPIO != GPIO_NONE)
 #define PAD_TS0_CLK_OEN (PAD_TS0_CLK_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS0_CLK_OUT (PAD_TS0_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2524, PAD_TS0_CLK_OUT, BIT5),
     _RVM1(0x2524, PAD_TS0_CLK_OEN, BIT5),
 #endif

 #if(PAD_TS0_SYNC_IS_GPIO != GPIO_NONE)
 #define PAD_TS0_SYNC_OEN (PAD_TS0_SYNC_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS0_SYNC_OUT (PAD_TS0_SYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2528, PAD_TS0_SYNC_OUT, BIT5),
     _RVM1(0x2528, PAD_TS0_SYNC_OEN, BIT5),
 #endif

 #if(PAD_TS0_VLD_IS_GPIO != GPIO_NONE)
 #define PAD_TS0_VLD_OEN (PAD_TS0_VLD_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS0_VLD_OUT (PAD_TS0_VLD_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2526, PAD_TS0_VLD_OUT, BIT5),
     _RVM1(0x2526, PAD_TS0_VLD_OEN, BIT5),
 #endif

 #if(PAD_TS0_D0_IS_GPIO != GPIO_NONE)
 #define PAD_TS0_D0_OEN (PAD_TS0_D0_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS0_D0_OUT (PAD_TS0_D0_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2538, PAD_TS0_D0_OUT, BIT5),
     _RVM1(0x2538, PAD_TS0_D0_OEN, BIT5),
 #endif

 #if(PAD_TS0_D1_IS_GPIO != GPIO_NONE)
 #define PAD_TS0_D1_OEN (PAD_TS0_D1_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS0_D1_OUT (PAD_TS0_D1_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2536, PAD_TS0_D1_OUT, BIT5),
     _RVM1(0x2536, PAD_TS0_D1_OEN, BIT5),
 #endif

 #if(PAD_TS0_D2_IS_GPIO != GPIO_NONE)
 #define PAD_TS0_D2_OEN (PAD_TS0_D2_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS0_D2_OUT (PAD_TS0_D2_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2534, PAD_TS0_D2_OUT, BIT5),
     _RVM1(0x2534, PAD_TS0_D2_OEN, BIT5),
 #endif

 #if(PAD_TS0_D3_IS_GPIO != GPIO_NONE)
 #define PAD_TS0_D3_OEN (PAD_TS0_D3_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS0_D3_OUT (PAD_TS0_D3_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2532, PAD_TS0_D3_OUT, BIT5),
     _RVM1(0x2532, PAD_TS0_D3_OEN, BIT5),
 #endif

 #if(PAD_TS0_D4_IS_GPIO != GPIO_NONE)
 #define PAD_TS0_D4_OEN (PAD_TS0_D4_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS0_D4_OUT (PAD_TS0_D4_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2530, PAD_TS0_D4_OUT, BIT5),
     _RVM1(0x2530, PAD_TS0_D4_OEN, BIT5),
 #endif

 #if(PAD_TS0_D5_IS_GPIO != GPIO_NONE)
 #define PAD_TS0_D5_OEN (PAD_TS0_D5_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS0_D5_OUT (PAD_TS0_D5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x252e, PAD_TS0_D5_OUT, BIT5),
     _RVM1(0x252e, PAD_TS0_D5_OEN, BIT5),
 #endif

 #if(PAD_TS0_D6_IS_GPIO != GPIO_NONE)
 #define PAD_TS0_D6_OEN (PAD_TS0_D6_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS0_D6_OUT (PAD_TS0_D6_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x252c, PAD_TS0_D6_OUT, BIT5),
     _RVM1(0x252c, PAD_TS0_D6_OEN, BIT5),
 #endif

 #if(PAD_TS0_D7_IS_GPIO != GPIO_NONE)
 #define PAD_TS0_D7_OEN (PAD_TS0_D7_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_TS0_D7_OUT (PAD_TS0_D7_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x252a, PAD_TS0_D7_OUT, BIT5),
     _RVM1(0x252a, PAD_TS0_D7_OEN, BIT5),
 #endif

 #if(PAD_NF_WEZ_IS_GPIO != GPIO_NONE)
 #define PAD_NF_WEZ_OEN (PAD_NF_WEZ_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_NF_WEZ_OUT (PAD_NF_WEZ_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x264e, PAD_NF_WEZ_OUT, BIT5),
     _RVM1(0x264e, PAD_NF_WEZ_OEN, BIT5),
 #endif

 #if(PAD_NF_WPZ_IS_GPIO != GPIO_NONE)
 #define PAD_NF_WPZ_OEN (PAD_NF_WPZ_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_NF_WPZ_OUT (PAD_NF_WPZ_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2650, PAD_NF_WPZ_OUT, BIT5),
     _RVM1(0x2650, PAD_NF_WPZ_OEN, BIT5),
 #endif

 #if(PAD_NF_RBZ_IS_GPIO != GPIO_NONE)
 #define PAD_NF_RBZ_OEN (PAD_NF_RBZ_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_NF_RBZ_OUT (PAD_NF_RBZ_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2646, PAD_NF_RBZ_OUT, BIT5),
     _RVM1(0x2646, PAD_NF_RBZ_OEN, BIT5),
 #endif

 #if(PAD_NF_REZ_IS_GPIO != GPIO_NONE)
 #define PAD_NF_REZ_OEN (PAD_NF_REZ_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_NF_REZ_OUT (PAD_NF_REZ_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2648, PAD_NF_REZ_OUT, BIT5),
     _RVM1(0x2648, PAD_NF_REZ_OEN, BIT5),
 #endif

 #if(PAD_NF_CEZ_BGA_IS_GPIO != GPIO_NONE)
 #define PAD_NF_CEZ_BGA_OEN (PAD_NF_CEZ_BGA_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_NF_CEZ_BGA_OUT (PAD_NF_CEZ_BGA_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2644, PAD_NF_CEZ_BGA_OUT, BIT5),
     _RVM1(0x2644, PAD_NF_CEZ_BGA_OEN, BIT5),
 #endif

 #if(PAD_NF_CE1Z_BGA_IS_GPIO != GPIO_NONE)
 #define PAD_NF_CE1Z_BGA_OEN (PAD_NF_CE1Z_BGA_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_NF_CE1Z_BGA_OUT (PAD_NF_CE1Z_BGA_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2662, PAD_NF_CE1Z_BGA_OUT, BIT5),
     _RVM1(0x2662, PAD_NF_CE1Z_BGA_OEN, BIT5),
 #endif

 #if(PAD_DM_GPIO1_IS_GPIO != GPIO_NONE)
 #define PAD_DM_GPIO1_OEN (PAD_DM_GPIO1_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_DM_GPIO1_OUT (PAD_DM_GPIO1_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2642, PAD_DM_GPIO1_OUT, BIT5),
     _RVM1(0x2642, PAD_DM_GPIO1_OEN, BIT5),
 #endif

 #if(PAD_DM_GPIO0_IS_GPIO != GPIO_NONE)
 #define PAD_DM_GPIO0_OEN (PAD_DM_GPIO0_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_DM_GPIO0_OUT (PAD_DM_GPIO0_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x2640, PAD_DM_GPIO0_OUT, BIT5),
     _RVM1(0x2640, PAD_DM_GPIO0_OEN, BIT5),
 #endif

 #if(PAD_S_GPIO0_IS_GPIO != GPIO_NONE)
 #define PAD_S_GPIO0_OEN (PAD_S_GPIO0_IS_GPIO == GPIO_IN ? BIT0: 0)
 #define PAD_S_GPIO0_OUT (PAD_S_GPIO0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
     _RVM1(0x1e41, PAD_S_GPIO0_OUT, BIT0),
     _RVM1(0x1e41, PAD_S_GPIO0_OEN, BIT0),
 #endif

 #if(PAD_S_GPIO1_IS_GPIO != GPIO_NONE)
 #define PAD_S_GPIO1_OEN (PAD_S_GPIO1_IS_GPIO == GPIO_IN ? BIT1: 0)
 #define PAD_S_GPIO1_OUT (PAD_S_GPIO1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
     _RVM1(0x1e41, PAD_S_GPIO1_OUT, BIT1),
     _RVM1(0x1e41, PAD_S_GPIO1_OEN, BIT1),
 #endif

 #if(PAD_S_GPIO2_IS_GPIO != GPIO_NONE)
 #define PAD_S_GPIO2_OEN (PAD_S_GPIO2_IS_GPIO == GPIO_IN ? BIT2: 0)
 #define PAD_S_GPIO2_OUT (PAD_S_GPIO2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
     _RVM1(0x1e41, PAD_S_GPIO2_OUT, BIT2),
     _RVM1(0x1e41, PAD_S_GPIO2_OEN, BIT2),
 #endif

 #if(PAD_VSYNC_OUT_IS_GPIO != GPIO_NONE)
 #define PAD_VSYNC_OUT_OEN (PAD_VSYNC_OUT_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_VSYNC_OUT_OUT (PAD_VSYNC_OUT_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x263e, PAD_VSYNC_OUT_OUT, BIT5),
     _RVM1(0x263e, PAD_VSYNC_OUT_OEN, BIT5),
 #endif

 #if(PAD_HSYNC_OUT_IS_GPIO != GPIO_NONE)
 #define PAD_HSYNC_OUT_OEN (PAD_HSYNC_OUT_IS_GPIO == GPIO_IN ? BIT5: 0)
 #define PAD_HSYNC_OUT_OUT (PAD_HSYNC_OUT_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
     _RVM1(0x263c, PAD_HSYNC_OUT_OUT, BIT5),
     _RVM1(0x263c, PAD_HSYNC_OUT_OEN, BIT5),
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
 #endif

 #if(PAD_GPIO_PM7_IS_GPIO != GPIO_NONE)
 #define PAD_GPIO_PM7_OEN (PAD_GPIO_PM7_IS_GPIO == GPIO_IN ? BIT7: 0)
 #define PAD_GPIO_PM7_OUT (PAD_GPIO_PM7_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
     _RVM1(0x0e20, PAD_GPIO_PM7_OUT, BIT7),
     _RVM1(0x0e1e, PAD_GPIO_PM7_OEN, BIT7),
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
 #endif

 #if(PAD_GPIO_PM11_IS_GPIO != GPIO_NONE)
 #define PAD_GPIO_PM11_OEN (PAD_GPIO_PM11_IS_GPIO == GPIO_IN ? BIT3: 0)
 #define PAD_GPIO_PM11_OUT (PAD_GPIO_PM11_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
     _RVM1(0x0e21, PAD_GPIO_PM11_OUT, BIT3),
     _RVM1(0x0e1f, PAD_GPIO_PM11_OEN, BIT3),
 #endif

 #if(PAD_GPIO_PM12_IS_GPIO != GPIO_NONE)
 #define PAD_GPIO_PM12_OEN (PAD_GPIO_PM12_IS_GPIO == GPIO_IN ? BIT4: 0)
 #define PAD_GPIO_PM12_OUT (PAD_GPIO_PM12_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
     _RVM1(0x0e21, PAD_GPIO_PM12_OUT, BIT4),
     _RVM1(0x0e1f, PAD_GPIO_PM12_OEN, BIT4),
 #endif


//---------------------------------------------------------------------
// Pad Configuartion
//---------------------------------------------------------------------
    _MEMMAP_PM_,

    #define IRIN_USE_PM5 ((PADS_PM5_IS_IRIN==1)? BIT0 : 0) //QFP156 MODE
    _RVM1(0x0E50, IRIN_USE_PM5, BIT0),

    _MEMMAP_nonPM_,

    #define SM0_OPEN ((PADS_SM0_OPEN == PAD_SM0_CLK) ? (BIT0) : \
                      (PADS_SM0_OPEN == PAD_SM0_RST ) ? (BIT0) : \
                      (PADS_SM0_OPEN == PAD_SM1_CLK ) ? (BIT1) : \
                      (PADS_SM0_OPEN == PAD_SM1_RST ) ? (BIT1) : \
                      (PADS_SM0_OPEN == PAD_CI_A10 ) ? (BIT1|BIT0) : \
                      (PADS_SM0_OPEN == PAD_CI_A13 ) ? (BIT1|BIT0) : 0)

    _RVM1(0x1E18, SM0_OPEN, BITMASK(2:0)),

    #define SM0_C48 ((PADS_SM0_C48 == PAD_SM0_GPIO0) ? (BIT4) : \
                     (PADS_SM0_C48 == PAD_SM0_GPIO1) ? (BIT4) : \
                     (PADS_SM0_C48 == PAD_SM1_GPIO0) ? (BIT5) : \
                     (PADS_SM0_C48 == PAD_SM1_GPIO1) ? (BIT5) : 0)

    _RVM1(0x1E18, SM0_C48, BITMASK(5:4)),

    #define SM0_EN  ((PADS_SM0_EN == PAD_SM0_IO) ? (BIT0) : \
                     (PADS_SM0_EN == PAD_SM0_CLK) ? (BIT0) : \
                     (PADS_SM0_EN == PAD_SM0_RST) ? (BIT0) : \
                     (PADS_SM0_EN == PAD_SM0_CD) ? (BIT0) : \
                     (PADS_SM0_EN == PAD_SM0_VCC) ? (BIT0) : \
                     (PADS_SM0_EN == PAD_SM1_IO) ? (BIT1) : \
                     (PADS_SM0_EN == PAD_SM1_CLK) ? (BIT1) : \
                     (PADS_SM0_EN == PAD_SM1_RST) ? (BIT1) : \
                     (PADS_SM0_EN == PAD_SM1_CD) ? (BIT1) : \
                     (PADS_SM0_EN == PAD_SM1_VCC) ? (BIT1) : \
                     (PADS_SM0_EN == PAD_CI_A14) ? (BIT1|BIT0) : \
                     (PADS_SM0_EN == PAD_CI_A13) ? (BIT1|BIT0) : \
                     (PADS_SM0_EN == PAD_CI_A12) ? (BIT1|BIT0) : \
                     (PADS_SM0_EN == PAD_CI_A11) ? (BIT1|BIT0) : \
                     (PADS_SM0_EN == PAD_CI_A10) ? (BIT1|BIT0) : 0)


    _RVM1(0x1E19, SM0_EN, BITMASK(2:0)),

    #define SM1_OPEN ((PADS_SM1_OPEN == PAD_SM1_RST ) ? (BIT0) : \
                      (PADS_SM1_OPEN == PAD_SM1_CLK) ? (BIT0) : \
                      (PADS_SM1_OPEN == PAD_CI_A13) ? (BIT1) : \
                      (PADS_SM1_OPEN == PAD_CI_A10) ? (BIT1) : \
                      (PADS_SM1_OPEN == PAD_SM0_RST) ? (BIT1|BIT0) : \
                      (PADS_SM1_OPEN == PAD_SM0_CLK) ? (BIT1|BIT0) : 0)

    _RVM1(0x1E1A, SM1_OPEN, BITMASK(1:0)),

    #define SM1_C48 ((PADS_SM1_C48 == PAD_SM1_GPIO0 ) ? (BIT4) : \
                      (PADS_SM1_C48 == PAD_SM1_GPIO1) ? (BIT4) : \
                      (PADS_SM1_C48 == PAD_SM0_GPIO0) ? (BIT5|BIT4) : \
                      (PADS_SM1_C48 == PAD_SM0_GPIO1) ? (BIT5|BIT4) : 0)

    _RVM1(0x1E1A, SM1_C48, BITMASK(5:4)),

    #define SM1_EN  ((PADS_SM1_EN == PAD_SM1_RST  ) ? (BIT0) : \
                     (PADS_SM1_EN == PAD_SM1_CD) ? (BIT0) : \
                     (PADS_SM1_EN == PAD_SM1_VCC) ? (BIT0) : \
                     (PADS_SM1_EN == PAD_SM1_IO) ? (BIT0) : \
                     (PADS_SM1_EN == PAD_SM1_CLK) ? (BIT0) : \
                     (PADS_SM1_EN == PAD_CI_A14) ? (BIT1) : \
                     (PADS_SM1_EN == PAD_CI_A13) ? (BIT1) : \
                     (PADS_SM1_EN == PAD_CI_A12) ? (BIT1) : \
                     (PADS_SM1_EN == PAD_CI_A11) ? (BIT1) : \
                     (PADS_SM1_EN == PAD_CI_A10) ? (BIT1) : \
                     (PADS_SM1_EN == PAD_SM0_RST) ? (BIT1|BIT0) : \
                     (PADS_SM1_EN == PAD_SM0_CD) ? (BIT1|BIT0) : \
                     (PADS_SM1_EN == PAD_SM0_VCC) ? (BIT1|BIT0) : \
                     (PADS_SM1_EN == PAD_SM0_IO) ? (BIT1|BIT0) : \
                     (PADS_SM1_EN == PAD_SM0_CLK) ? (BIT1|BIT0) : 0)

    _RVM1(0x1E1B, SM1_EN, BITMASK(2:0)),

    #define I2CM0_MODE ((PADS_I2CM0_MODE == PAD_I2CM0_SDA  ) ? (BIT0) : \
                        (PADS_I2CM0_MODE == PAD_I2CM0_SCL) ? (BIT0) : \
                        (PADS_I2CM0_MODE == PAD_SM0_IO) ? (BIT1) : \
                        (PADS_I2CM0_MODE == PAD_SM0_CLK) ? (BIT1) : \
                        (PADS_I2CM0_MODE == PAD_CI_CEZ) ? (BIT1|BIT0) : \
                        (PADS_I2CM0_MODE == PAD_CI_IRQAZ) ? (BIT1|BIT0) : 0)

    _RVM1(0x1E12, I2CM0_MODE, BIT1|BIT0),

    #define I2CM1_MODE ((PADS_I2CM1_MODE == PAD_I2CM1_SCL) ? (BIT4) : \
                        (PADS_I2CM1_MODE == PAD_I2CM1_SDA) ? (BIT4) : \
                        (PADS_I2CM1_MODE == PAD_TS0_D5) ? (BIT5|BIT4) : \
                        (PADS_I2CM1_MODE == PAD_TS0_D4) ? (BIT5|BIT4) : \
                        (PADS_I2CM1_MODE == PAD_CI_A10) ? (BIT6) : \
                        (PADS_I2CM1_MODE == PAD_CI_A9) ? (BIT6) : \
                        (PADS_I2CM1_MODE == PAD_TS1_D7) ? (BIT6|BIT4) : \
                        (PADS_I2CM1_MODE == PAD_TS1_D6) ? (BIT6|BIT4) : 0)

    _RVM1(0x1E12, I2CM1_MODE, BITMASK(6:4)),

    // according to the problem of naming, we decide to change to the actually mode number
    #define TS0_MODE ((PADS_TS0_MODE == 1) ? (BIT0) : \
                      (PADS_TS0_MODE == 2) ? (BIT1) : \
                      (PADS_TS0_MODE == 3) ? (BIT1|BIT0) : 0)

    _RVM1(0x1E04, TS0_MODE, BITMASK(1:0)),

    // according to the problem of naming, we decide to change to the actually mode number
    #define TS1_MODE ((PADS_TS1_MODE == 1) ? (BIT4) : \
                      (PADS_TS1_MODE == 2) ? (BIT5) : \
                      (PADS_TS1_MODE == 3) ? (BIT5|BIT4) : 0)

    _RVM1(0x1E04, TS1_MODE, BITMASK(5:4)),

    // use the TS2_CLK as the main different pin comparison
    #define TS2_MODE ((PADS_TS2_MODE == PAD_TS2_CLK) ? (BIT0) : \
                      (PADS_TS2_MODE == PAD_SPDIF_OUT) ? (BIT1) : 0)

    _RVM1(0x1E05, TS2_MODE, BITMASK(1:0)),

    // use the TS2_CLK as the main different pin comparison
    #define TS3_MODE ((PADS_TS3_MODE == 1) ? (BIT4) : \
                      (PADS_TS3_MODE == 2) ? (BIT5) : \
                      (PADS_TS3_MODE == 3) ? (BIT5|BIT4) : 0)

    _RVM1(0x1E05, TS3_MODE, BITMASK(5:4)),

    // use the NF_REZ as the main different pin comparison
    #define NAND_MODE ((PADS_NAND_MODE == PAD_SM0_CD) ? (BIT0) : \
                       (PADS_NAND_MODE == PAD_CI_A8) ? (BIT1) : \
                       (PADS_NAND_MODE == PAD_NF_REZ) ? (BIT1|BIT0) : 0)

    _RVM1(0x1E0C, NAND_MODE, BITMASK(3:0)),

    // use the PCM_RST as the main different pin comparison
    #define CI_MODE ((PADS_CI_MODE == PAD_CI_OEZ) ? (BIT0) : \
                     (PADS_CI_MODE == PAD_CI_RST) ? (BIT1) : \
                     (PADS_CI_MODE == PAD_TS0_D5) ? (BIT1|BIT0) : 0)

    _RVM1(0x1E0E, CI_MODE, BITMASK(1:0)),

    // use CCIR_OUT_CLK define
    #define CCIR_OUT_MODE ((PADS_CCIR_OUT_MODE == PAD_TS1_CLK) ? (BIT4) : 0)

    _RVM1(0x1E10, CCIR_OUT_MODE, BIT4),

    // use CCIR_IN_CLK define
    #define CCIR_IN_MODE ((PADS_CCIR_IN_MODE == PAD_TS1_CLK) ? (BIT0) : 0)

    _RVM1(0x1E10, CCIR_IN_MODE, BIT0),

    // use PANEL_CTL[0] define
    #define PANEL_IF_MODE ((PADS_PANEL_IF_MODE == PAD_CI_OEZ) ? (BIT0) : 0)

    _RVM1(0x1E11, PANEL_IF_MODE, BIT0),

    // use SPDIF_OUT as the main different pin comparison
    #define SPDIF_OUT_MODE ((PADS_SPDIF_OUT_MODE == PAD_CI_A12) ? (BIT4) : \
                            (PADS_SPDIF_OUT_MODE == PAD_TS0_CLK) ? (BIT5) : \
                            (PADS_SPDIF_OUT_MODE == PAD_SPDIF_OUT) ? (BIT5|BIT4) : \
                            (PADS_SPDIF_OUT_MODE == PAD_TS1_D6) ? (BIT6) : \
                            (PADS_SPDIF_OUT_MODE == PAD_SM0_CD) ? (BIT6|BIT4) : 0)

    _RVM1(0x1E0A, SPDIF_OUT_MODE, BITMASK(6:4)),

    // use SPDIF_IN as the main different pin comparison
    #define SPDIF_IN_MODE ((PADS_SPDIF_IN_MODE == PAD_CI_A12) ? (BIT0) : \
                            (PADS_SPDIF_IN_MODE == PAD_TS0_CLK) ? (BIT1) : \
                            (PADS_SPDIF_IN_MODE == PAD_SPDIF_OUT) ? (BIT1|BIT0) : \
                            (PADS_SPDIF_IN_MODE == PAD_TS1_CLK) ? (BIT2) : \
                            (PADS_SPDIF_IN_MODE == PAD_SM0_CD) ? (BIT2|BIT0) : 0)

    _RVM1(0x1E0A, SPDIF_IN_MODE, BITMASK(2:0)),

    // use I2S_IN_BCK as the main different pin comparison
    #define I2S_IN_MODE ((PADS_I2S_IN_MODE == PAD_CI_D2 ) ? (BIT0) : \
                         (PADS_I2S_IN_MODE == PAD_I2S_OUT_BCK) ? (BIT1) : \
                         (PADS_I2S_IN_MODE == PAD_TS1_D5) ? (BIT1|BIT0) : 0)

    _RVM1(0x1E0B, I2S_IN_MODE, BITMASK(1:0)),

    // use I2S_OUT_BCK as the main different pin comparison
    #define I2S_OUT_MODE ((PADS_I2S_OUT_MODE == PAD_CI_D2  ) ? (BIT4) : \
                          (PADS_I2S_OUT_MODE == PAD_I2S_OUT_BCK) ? (BIT5) : \
                          (PADS_I2S_OUT_MODE == PAD_TS1_D5) ? (BIT5|BIT4) : 0)

    _RVM1(0x1E0B, I2S_OUT_MODE, BITMASK(5:4)),

    // use MPIF_CSN as the main different pin comparison
    #define MPIF_MODE ((PADS_MPIF_MODE == PAD_TS1_CLK) ? (BIT4) : \
                       (PADS_MPIF_MODE == PAD_CI_D1) ? 0 : \
                       (PADS_MPIF_MODE == PAD_CI_D3) ? (BIT5|BIT4) : 0)

    _RVM1(0x1E0E, MPIF_MODE, BITMASK(6:4)),

    // use SDIO_CDZ as the main different pin comparison
    #define SDIO_MODE ((PADS_SDIO_MODE == PAD_TS1_CLK) ? (BIT4) : \
                       (PADS_SDIO_MODE == PAD_CI_D1) ? (BIT5|BIT4) : 0)

    _RVM1(0x1E0C, SDIO_MODE, BITMASK(6:4)),

    // use SD_CDZ as the main different pin comparison
    #define SDIO2_MODE ((PADS_SDIO_MODE == PAD_TS1_SYNC) ? (BIT4) : \
                       (PADS_SDIO_MODE == PAD_CI_D3) ? (BIT5|BIT4) : 0)

    _RVM1(0x1E0D, SDIO_MODE, BITMASK(6:4)),

/*

    #define ET_MODE ((PADS_ET_MODE == PAD_ET_CRS) ? (BIT0) : \
                       (PADS_ET_MODE == PAD_ET_TXD1) ? (BIT1) : \
                       (PADS_ET_MODE == PAD_PF_A14) ? (BIT1|BIT0) : \
                       (PADS_ET_MODE == PAD_PF_A3) ? (BIT2) : 0)

    _RVM1(0x1E0F, ET_MODE, BITMASK(2:0)),
*/

/*
    #define RF_AGC_EN ((PADS_RF_AGC_EN == PAD_RF_AGC) ? (BIT1) : 0)

    _RVM1(0x1E3A, RF_AGC_EN, BIT1),
*/

/*
    #define IF_AGC_EN ((PADS_IF_AGC_EN == PAD_IF_AGC) ? (BIT0) : 0)

    _RVM1(0x1E3A, IF_AGC_EN, BIT0),
*/

    // use CTS as the main different pin comparison
    #define MODEM_MODE ((PADS_MODEM_MODE == PAD_TS0_D3) ? (BIT4) : \
                        (PADS_MODEM_MODE == PAD_TS1_CLK) ? (BIT5) : \
                        (PADS_MODEM_MODE == PAD_CI_A14) ? (BIT5|BIT4) : 0)

    _RVM1(0x1E0F, MODEM_MODE, BITMASK(5:4)),

    #define PWM_MODE ((PADS_PWM_MODE == PAD_HSYNC_OUT) ? (BIT0) : \
                        (PADS_PWM_MODE == PAD_VSYNC_OUT) ? (BIT0) : 0)

    _RVM1(0x1E13, PWM_MODE, BIT0),

/*
    #define PF_CS1_EN ((PADS_PF_CS1_EN == PAD_PF_A25) ? (BIT0) : 0)

    _RVM1(0x1E1E, PF_CS1_EN, BIT0),
*/

    #define HSYNC_EN ((PADS_HSYNC_EN == PAD_HSYNC_OUT) ? (BIT0) : 0)

    _RVM1(0x1E16, HSYNC_EN, BIT0),

    #define VSYNC_EN ((PADS_VSYNC_EN == PAD_VSYNC_OUT) ? (BIT4) : 0)

    _RVM1(0x1E16, VSYNC_EN, BIT4),

    // UART MUX
    #define SECOND_UART_MODE ((PADS_SECOND_UART_MODE == PAD_HSYNC_OUT) ? (BIT0) : \
                        (PADS_SECOND_UART_MODE == PAD_VSYNC_OUT) ? (BIT0) : \
                        (PADS_SECOND_UART_MODE == PAD_I2CM0_SDA) ? (BIT1) : \
                        (PADS_SECOND_UART_MODE == PAD_I2CM0_SCL) ? (BIT1) : \
                        (PADS_SECOND_UART_MODE == PAD_I2CM1_SCL) ? (BIT1|BIT0) : \
                        (PADS_SECOND_UART_MODE == PAD_I2CM1_SDA) ? (BIT1|BIT0) : \
                        (PADS_SECOND_UART_MODE == PAD_TS1_VLD) ? (BIT2) : \
                        (PADS_SECOND_UART_MODE == PAD_TS1_SYNC) ? (BIT2) : 0)

    _RVM1(0x1E06, SECOND_UART_MODE, BITMASK(2:0)),

    #define THIRD_UART_MODE ((PADS_THIRD_UART_MODE == PAD_TS1_D7) ? (BIT4) : \
                           (PADS_THIRD_UART_MODE == PAD_TS1_D6) ? (BIT4) : \
                           (PADS_THIRD_UART_MODE == PAD_I2S_OUT_SD2) ? (BIT5|BIT4) : \
                           (PADS_THIRD_UART_MODE == PAD_I2S_OUT_SD3) ? (BIT5|BIT4) : 0)

    _RVM1(0x1E06, THIRD_UART_MODE, BITMASK(5:4)),

    #define FOURTH_UART_MODE ((PADS_FOURTH_UART_MODE == PAD_TS0_D1) ? (BIT1) : \
                           (PADS_FOURTH_UART_MODE == PAD_TS0_D0) ? (BIT1) : \
                           (PADS_FOURTH_UART_MODE == PAD_HSYNC_OUT) ? (BIT1|BIT0) : \
                           (PADS_FOURTH_UART_MODE == PAD_VSYNC_OUT) ? (BIT1|BIT0) : 0)

    _RVM1(0x1E07, FOURTH_UART_MODE, BITMASK(1:0)),

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

    _MEMMAP_PM_,

    _RVM1(0x0E13, BIT3, BIT3),   // RX0_ENABLE
    _RVM1(0x0E13, 0 , BIT4),   // UART0 -> reg_uart_sel0
#if 0
    #define SEL_CZ_ON   ((PIN_SPI_CZ1 ? BIT5 : 0) | \
                         (PIN_SPI_CZ2 ? BIT6 : 0) | \
                         (PIN_SPI_CZ3 ? BIT7 : 0))

    _RVM1(0x3C1D, ~(SEL_CZ_ON), BITMASK(7:5)),
#endif
    _MEMMAP_nonPM_,

#if 0 //K2 setting
#if (MS_BOARD_TYPE_SEL == BD_MST170A_D01A_S) || (MS_BOARD_TYPE_SEL == BD_MST170A_D01A)
    // swap port 2, for K2 BGA package, port2 should always swapped
    _RVM1(0x2A0B, BIT5, BIT5),
#endif
#endif

    // Clear all pad in
    _RVM1(0x1EA1, 0, BIT7),
    _END_OF_TBL_,

//---------------------------------------------------------------------
// ISP_TOOL Write Protect (Need to check ????)
//---------------------------------------------------------------------
    //external flash #1
    _MEMMAP_PM_,
    _RVM1(0x0E6A, 0x00, BIT0), //reg_spi_gpio set to 0 (swtch to spi_do, spi_di, spi_ck)
    _RVM1(0x0E6A, 0x00, BIT1), //reg_spicsz0_gpio set to 0 (enable spi_cz0)
    _RVM1(0x08F4, 0x00, 0xFF), //reg_chip_select set to 0 (select embedded SPI Flash)
    #if (PIN_FLASH_WP0)
    _RVM1(0x0E21, BIT0, BIT0),
    _RVM1(0x0E1F,    0, BIT0),
    #endif
    _END_OF_TBL_,

    //external flash #2
    _MEMMAP_PM_,
    _RVM1(0x0E6A, 0x00, BIT0), //reg_spi_gpio set to 0 (swtch to spi_do, spi_di, spi_ck)
    #if (PIN_SPI_CZ1)
    _RVM1(0x0E6A, 0x00, BIT2), //reg_spicsz1_gpio set to 0 (enable spi_cz1)
    _RVM1(0x08F4, 0x01, 0xFF), //reg_chip_select set to 1 (select external flash #1)
    #if (PIN_FLASH_WP1)
    _RVM1(0x0E21, BIT0, BIT0),
    _RVM1(0x0E1F,    0, BIT0),
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
    #error "UART src selection conflict"
#endif


