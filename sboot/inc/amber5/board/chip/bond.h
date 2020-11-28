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
////////////////////////////////////////////////////////////////////////////////

#ifndef _CHIP_BOND_H_
#define _CHIP_BOND_H_

#include "Board.h"

//----------------------------------------------------------------------------
// I2S / SPDIF (TODO: automatically defined to 0 if some pins are used for GPIO)
//----------------------------------------------------------------------------

#ifndef PIN_I2S_IN
    #if (!CHIP_HAS_I2S_IN)
        #define PIN_I2S_IN      0
    #else
        #error "PIN_I2S_IN not defined"
    #endif
#endif

#ifndef PIN_I2S_OUT
    #if (!CHIP_HAS_I2S_OUT)
        #define PIN_I2S_OUT     0
    #else
        #error "PIN_I2S_OUT not defined"
    #endif
#endif

#ifndef PIN_SPDIF_IN
    #if (!CHIP_HAS_SPDIF_IN)
        #define PIN_SPDIF_IN    0
    #else
        #error "PIN_I2S_OUT not defined"
    #endif
#endif

#ifndef PIN_SPDIF_OUT
    #if (!CHIP_HAS_SPDIF_OUT)
        #define PIN_SPDIF_OUT   0
    #else
        #error "PIN_SPDIF_OUT not defined"
    #endif
#endif

#ifndef PIN_I2S_OUT_MUTE
    #define PIN_I2S_OUT_MUTE    0
#endif

//----------------------------------------------------------------------------
// UART_SRC_SEL
//----------------------------------------------------------------------------
//#define T3_For_UART2_Debug

#ifdef T3_For_UART2_Debug
    #ifndef UART0_SRC_SEL
        //#define UART0_SRC_SEL   (UART_SEL_MHEG5)
    #define UART0_SRC_SEL   (0)
    #endif

    #ifndef UART1_SRC_SEL
        #define UART1_SRC_SEL   (UART_SEL_VD_MHEG5)
    #endif

    #ifndef UART2_SRC_SEL
        //#define UART2_SRC_SEL   (UART_SEL_TSP)
        #define UART2_SRC_SEL   (UART_SEL_MHEG5)
    #endif

    #ifndef UART3_SRC_SEL
        #define UART3_SRC_SEL   (UART_SEL_PIU_UART0)
    #endif

    #ifndef UART4_SRC_SEL
        #define UART4_SRC_SEL   (UART_SEL_PIU_UART1)
    #endif

#else

    #ifndef UART0_SRC_SEL
        #define UART0_SRC_SEL   (UART_SEL_PIU_UART0)
    #endif

    #ifndef UART1_SRC_SEL
        #define UART1_SRC_SEL   (UART_SEL_VD_MHEG5)
    #endif

    #ifndef UART2_SRC_SEL
        #define UART2_SRC_SEL   (UART_SEL_TSP)
    #endif

    #ifndef UART3_SRC_SEL
        #define UART3_SRC_SEL   (UART_SEL_PIU_FAST_UART)
    #endif

    #ifndef UART4_SRC_SEL
        #define UART4_SRC_SEL   (UART_SEL_PIU_UART1)
    #endif

#endif



//----------------------------------------------------------------------------
// UART_INV
//----------------------------------------------------------------------------

#ifndef UART0_INV
    #define UART0_INV   0
#endif

#ifndef UART1_INV
    #define UART1_INV   0
#endif

#ifndef UART2_INV
    #define UART2_INV   0
#endif

#ifndef UART3_INV
    #define UART3_INV   0
#endif

#ifndef UART4_INV
    #define UART4_INV   0
#endif

//----------------------------------------------------------------------------
// PIN_TS1
//----------------------------------------------------------------------------

#ifndef PIN_TS1
    #if (!CHIP_HAS_TS1)
        #define PIN_TS1 0
    #else
        #error "PIN_TS1 not defined"
    #endif
#endif

//----------------------------------------------------------------------------
// PIN_UART1
//----------------------------------------------------------------------------

#ifndef PIN_UART1
    #define PIN_UART1   0
#elif (PIN_UART1 != 0 && \
       ((PIN_UART1 == PADS_UART1_MODE1 && !CHIP_HAS_UART1_MODE1) || \
        (PIN_UART1 == PADS_UART1_MODE2 && !CHIP_HAS_UART1_MODE2) || \
        (PIN_UART1 == PADS_UART1_MODE3 && !CHIP_HAS_UART1_MODE3)))
    #error "PIN_UART1 error"
#endif

//----------------------------------------------------------------------------
// PIN_UART2
//----------------------------------------------------------------------------

#ifndef PIN_UART2
    #define PIN_UART2   0
#elif (PIN_UART2 != 0 && \
       ((PIN_UART2 == PADS_UART2_MODE1 && !CHIP_HAS_UART2_MODE1) || \
        (PIN_UART2 == PADS_UART2_MODE2 && !CHIP_HAS_UART2_MODE2) || \
        (PIN_UART2 == PADS_UART2_MODE3 && !CHIP_HAS_UART2_MODE3)))
    #error "PIN_UART1 error"
#endif

//----------------------------------------------------------------------------
// PIN_CIMAX
//----------------------------------------------------------------------------

#ifndef PIN_CIMAX
    #if (!CHIP_HAS_CIMAX)
        #define PIN_CIMAX   0
    #else
        #error "PIN_CIMAX not defined"
    #endif
#elif (PIN_CIMAX != 0 && !CHIP_HAS_CIMAX)
    #error "PIN_CIMAX error"
#endif

//----------------------------------------------------------------------------
// PIN_PCMCIA
//----------------------------------------------------------------------------

#ifndef PIN_PCMCIA
    #if (!CHIP_HAS_PCMCIA)
        #define PIN_PCMCIA   0
    #else
        #error "PIN_PCMCIA not defined"
    #endif
#elif (PIN_PCMCIA != 0 && !CHIP_HAS_PCMCIA)
    #error "PIN_PCMCIA error"
#endif

//----------------------------------------------------------------------------
// PIN_MIIC
//----------------------------------------------------------------------------

#ifndef PIN_MIIC
    #if (CHIP_USE_IIC_IN_DDCR2)
        #define PIN_MIIC    PADS_DDCR2
    #else
        #define PIN_MIIC    PADS_DDCR
    #endif
#endif

#if ((PIN_MIIC == PADS_DDCR2 && !CHIP_HAS_DDCR2) || \
     (PIN_MIIC == PADS_DDCR  && !CHIP_HAS_DDCR))
    #error "PIN_MIIC error"
#endif

//----------------------------------------------------------------------------
// PIN_PF (TODO: update bonding script to check pinout)
//----------------------------------------------------------------------------

#ifndef PIN_PF
    #define PIN_PF      0
#endif

//----------------------------------------------------------------------------
// PIN_ET
//----------------------------------------------------------------------------

#ifndef PIN_ET
    #define PIN_ET      0
#endif

//----------------------------------------------------------------------------
// PIN_USBDRVBUS
//----------------------------------------------------------------------------

#ifndef PIN_USBDRVBUS
    #define PIN_USBDRVBUS   0
#endif

//----------------------------------------------------------------------------
// PIN_PWM2 / PIN_PWM3
//----------------------------------------------------------------------------

#ifndef PIN_PWM2
    #if (CHIP_USE_PWM2_IN_GPIO14 && !PAD_GPIO14_IS_GPIO)
        #define PIN_PWM2    PAD_GPIO14
    #else
        #define PIN_PWM2    PAD_PWM2
    #endif
#endif

#ifndef PIN_PWM3
    #if (CHIP_USE_PWM3_IN_GPIO15 && !PAD_GPIO15_IS_GPIO)
        #define PIN_PWM3    PAD_GPIO15
    #else
        #define PIN_PWM3    PAD_PWM3
    #endif
#endif

//----------------------------------------------------------------------------
// PIN_MCUJTAG
//----------------------------------------------------------------------------

#ifndef PIN_MCUJTAG
    #define PIN_MCUJTAG 0
#endif

//----------------------------------------------------------------------------
// PIN_DSPJTAG
//----------------------------------------------------------------------------

#ifndef PIN_DSPJTAG
    #define PIN_DSPJTAG 0
#endif

//----------------------------------------------------------------------------
// PIN_SPI_CZ[3:1]
//----------------------------------------------------------------------------

#ifndef PIN_SPI_CZ1
    #define PIN_SPI_CZ1 0
#endif

#ifndef PIN_SPI_CZ2
    #define PIN_SPI_CZ2 0
#endif

#ifndef PIN_SPI_CZ3
    #define PIN_SPI_CZ3 0
#endif

//----------------------------------------------------------------------------
// PIN_FLASH_WP
//----------------------------------------------------------------------------

#ifndef PIN_FLASH_WP0
    #define PIN_FLASH_WP0   0
#endif

#ifndef PIN_FLASH_WP1
    #define PIN_FLASH_WP1   0
#endif

#ifndef PIN_FLASH_WP2
    #define PIN_FLASH_WP2   0
#endif

#ifndef PIN_FLASH_WP3
    #define PIN_FLASH_WP3   0
#endif

//----------------------------------------------------------------------------
// PIN_SCART_ID
//----------------------------------------------------------------------------

#ifndef PIN_SCART_ID0
    #define PIN_SCART_ID0  0
#endif

#ifndef PIN_SCART_ID1
    #define PIN_SCART_ID1  0
#endif

#endif /* _CHIP_BOND_H_ */
