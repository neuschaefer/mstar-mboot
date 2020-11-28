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

#ifndef _DRVUART_H
#define _DRVUART_H

#include "datatype.h"

#define __USE__AEON_UART__

#ifdef __USE__AEON_UART__
#define UART_RX     0    // In:  Receive buffer (DLAB=0)    (16-byte FIFO)
#define UART_TX     0    // Out: Transmit buffer (DLAB=0)   (16-byte FIFO)
#define UART_DLL    0    // Out: Divisor Latch Low (DLAB=1)
#define UART_DLM    1    // Out: Divisor Latch High (DLAB=1)
#define UART_IER    1    // Out: Interrupt Enable Register
#define UART_IIR    2    // In:  Interrupt ID Register
#define UART_FCR    2    // Out: FIFO Control Register
#define UART_LCR    3    // Out: Line Control Register
#define UART_MCR    4    // Out: Modem Control Register
#define UART_LSR    5    // In:  Line Status Register
#define UART_MSR    6    // In:  Modem Status Register
#define UART_SCR    7    // I/O: Scratch Register
#else
#define UART_RX        (0 * 2)  // In:  Receive buffer (DLAB=0)
#define UART_TX        (0 * 2)  // Out: Transmit buffer (DLAB=0)
#define UART_DLL       (0 * 2)  // Out: Divisor Latch Low (DLAB=1)
#define UART_DLM       (1 * 2)  // Out: Divisor Latch High (DLAB=1)
#define UART_IER       (1 * 2)  // Out: Interrupt Enable Register
#define UART_IIR       (2 * 2)  // In:  Interrupt ID Register
#define UART_FCR       (2 * 2)  // Out: FIFO Control Register
#define UART_LCR       (3 * 2)  // Out: Line Control Register
#define UART_LSR       (5 * 2)  // In:  Line Status Register
#define UART_MSR       (6 * 2)  // In:  Modem Status Register
#endif

//
// FIFO Control Register
//
#define UART_FCR_ENABLE_FIFO        0x01    // Enable the FIFO
#define UART_FCR_CLEAR_RCVR         0x02    // Clear the RCVR FIFO
#define UART_FCR_CLEAR_XMIT         0x04    // Clear the XMIT FIFO
#define UART_FCR_DMA_SELECT         0x08    // For DMA applications
#define UART_FCR_TRIGGER_MASK       0xC0    // Mask for the FIFO trigger range
#define UART_FCR_TRIGGER_1          0x00    // Mask for trigger set at 1
#define UART_FCR_TRIGGER_4          0x40    // Mask for trigger set at 4
#define UART_FCR_TRIGGER_8          0x80    // Mask for trigger set at 8
#define UART_FCR_TRIGGER_14         0xC0    // Mask for trigger set at 14

//
// Line Control Register
// Note: if the word length is 5 bits (UART_LCR_WLEN5), then setting
// UART_LCR_STOP will select 1.5 stop bits, not 2 stop bits.
//
#define UART_LCR_DLAB               0x80    // Divisor latch access bit
#define UART_LCR_SBC                0x40    // Set break control
#define UART_LCR_SPAR               0x20    // Stick parity (?)
#define UART_LCR_EPAR               0x10    // Even parity select
#define UART_LCR_PARITY             0x08    // Parity Enable
#define UART_LCR_STOP1              0x00    // Stop bits: 0=1 stop bit, 1= 2 stop bits
#define UART_LCR_STOP2              0x04    // Stop bits: 0=1 stop bit, 1= 2 stop bits
#define UART_LCR_WLEN5              0x00    // Wordlength: 5 bits
#define UART_LCR_WLEN6              0x01    // Wordlength: 6 bits
#define UART_LCR_WLEN7              0x02    // Wordlength: 7 bits
#define UART_LCR_WLEN8              0x03    // Wordlength: 8 bits

//
// Line Status Register
//
#define UART_LSR_TEMT               0x40    // Transmitter empty
#define UART_LSR_THRE               0x20    // Transmit-hold-register empty
#define UART_LSR_BI                 0x10    // Break interrupt indicator
#define UART_LSR_FE                 0x08    // Frame error indicator
#define UART_LSR_PE                 0x04    // Parity error indicator
#define UART_LSR_OE                 0x02    // Overrun error indicator
#define UART_LSR_DR                 0x01    // Receiver data ready

//
// Interrupt Identification Register
//
#define UART_IIR_NO_INT             0x01    // No interrupts pending
#define UART_IIR_ID                 0x06    // Mask for the interrupt ID

#define UART_IIR_MSI                0x00    // Modem status interrupt
#define UART_IIR_THRI               0x02    // Transmitter holding register empty
#define UART_IIR_TOI                0x0c    // Receive time out interrupt
#define UART_IIR_RDI                0x04    // Receiver data interrupt
#define UART_IIR_RLSI               0x06    // Receiver line status interrupt

//
// Interrupt Enable Register
//
#define UART_IER_MSI                0x08    // Enable Modem status interrupt
#define UART_IER_RLSI               0x04    // Enable receiver line status interrupt
#define UART_IER_THRI               0x02    // Enable Transmitter holding reg empty int
#define UART_IER_RDI                0x01    // Enable receiver data available interrupt

//
// Modem Control Register
//
#define UART_MCR_LOOP               0x10    // Enable loopback test mode
#define UART_MCR_OUT2               0x08    // Out2 complement
#define UART_MCR_OUT1               0x04    // Out1 complement
#define UART_MCR_RTS                0x02    // RTS complement
#define UART_MCR_DTR                0x01    // DTR complement

//
// Modem Status Register
//
#define UART_MSR_DCD                0x80    // Data Carrier Detect
#define UART_MSR_RI                 0x40    // Ring Indicator
#define UART_MSR_DSR                0x20    // Data Set Ready
#define UART_MSR_CTS                0x10    // Clear to Send
#define UART_MSR_DDCD               0x08    // Delta DCD
#define UART_MSR_TERI               0x04    // Trailing edge ring indicator
#define UART_MSR_DDSR               0x02    // Delta DSR
#define UART_MSR_DCTS               0x01    // Delta CTS
#define UART_MSR_ANY_DELTA          0x0F    // Any of the delta bits!

// both Transmitter empty / Transmit-hold-register empty
#define BOTH_EMPTY (UART_LSR_TEMT | UART_LSR_THRE)

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
// Clock source
#define UART_CLK_FREQ   (XTAL_CLOCK_FREQ)
// Divisor
#define UART_DIVISOR    (UART_CLK_FREQ/(16 * UART_BAUD_RATE))

#ifdef __USE__AEON_UART__
#define UART_BASE       0x90000000
#define UART_REG8(_x_)   ((volatile unsigned char *)UART_BASE)[_x_]
#else
#define UART_BASE       (0xA0200000+0x1300)
#define UART_REG8(_x_)  ((volatile unsigned char *)(UART_BASE))[((_x_) * 4) - ((_x_) & 1)]
#endif


//-------------------------------------------------------------------------------------------------
// Extern Functions
//-------------------------------------------------------------------------------------------------
/// UART callback function used in interrupt context

void uart_init(U32 aeon_clock, U32 uart_clock);
void uart_putc(char c);
char uart_getc(void);
char uart_kbhit(void);
void uart_interrupt_enable(BOOLEAN bEnable);

#endif //#ifndef _DRVUART_H

