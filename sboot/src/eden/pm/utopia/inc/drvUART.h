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
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvUART.h
/// @brief  UART Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __MDRV_UART_H__
#define __MDRV_UART_H__

///
/// @file drvUART.h
/// @brief MStar driver for UART devices
///
/// @par Example: connect AEON uart to UART port0, output message
/// @code
/// ms_uart_dev_t uart;
///
/// mdrv_uart_connect(E_UART_PORT0, E_UART_AEON);
/// uart = mdrv_uart_open(E_UART_AEON);
/// if (uart != UART_DEV_NULL)
/// {
///     mdrv_uart_set_baudrate(uart, 38400);    // must do this after base clock changed
///     setconsole(uart);                       // set this uart device as console
/// }
/// printf("uart test");
/// mdrv_uart_close(uart);
/// @endcode
///
///
/// @par Example: use buffered output
/// @code
/// ms_uart_dev_t uart;
/// char tx_buffer[1024];
///
/// uart = mdrv_uart_open(E_UART_PIU_UART0);
/// if (uart != UART_DEV_NULL)
/// {
///     mdrv_uart_set_tx_buffer(uart, tx_buffer, sizeof(tx_buffer));
/// }
/// @endcode



#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"

//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------
#define UART_CAPS_AEON                  0x00000001
#define UART_CAPS_PIU                   0x00000002


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

// #define UART_TYPE_DEF
/// Version string.
#define UART_DRV_VERSION                /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    {'U','A','R','T'},                  /* IP__                                             */  \
    {'0','1'},                          /* 0.0 ~ Z.Z                                        */  \
    {'0','6'},                          /* 00 ~ 99                                          */  \
    {'0','0','3','1','0','0','5','0'},  /* CL#                                              */  \
    MSIF_OS

#define UART_TYPE_AEON      0x10
#define UART_TYPE_PIU       0x20
#define UART_TYPE_EYWA		0


// Baud rate
//#define UART_BAUD_RATE                38400 //9600 //19200 //38400 //57600 //115200 =>too frequent Rx INT
#define UART_BAUD_RATE              115200

#define UART_DEV_NULL   ((ms_uart_dev_t)0)


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

typedef enum
{
    E_UART_OK,
    E_UART_FAIL,
} UART_Result;

typedef struct _UART_DrvInfo
{
    MS_BOOL                         Init;
    MS_U32                          Caps;
} UART_DrvInfo;

typedef struct _UART_DrvStatus
{
    MS_BOOL                         HwBusy;
} UART_DrvStatus;

/// UART devices, not all of them can be access directly
typedef enum
{
    E_UART_INVALID = -1,    ///< INVALID
    E_UART_AEON,            ///< AEON
    E_UART_VDEC,            ///< VD_MHEG5 (only used in mdrv_uart_connect())
    E_UART_TSP,             ///< TSP (only used in mdrv_uart_connect())
    E_UART_PIU_UART0,       ///< PIU0
    E_UART_PIU_UART1,       ///< PIU1 (only available for some chips)
    E_UART_PIU_UART2,       ///< PIU2 (only available for some chips)
    E_UART_PIU_FUART0,      ///< PIU Fast UART (only available for some chips)
    E_UART_HK51_UART0,      ///< HK51 UART0 (only used in mdrv_uart_connect())
    E_UART_HK51_UART1,      ///< HK51 UART1 (only used in mdrv_uart_connect())
    E_UART_VD51_UART0,      ///< VD51 UART0 (only used in mdrv_uart_connect())
    E_UART_VD51_UART1,      ///< VD51 UART1 (only used in mdrv_uart_connect())
                            ///<            (only available for some chips)
    E_UART_AEON_R2,         ///< AEON_R2 for HK
    E_UART_AEON_AUDIO_R2,   ///< AEON_R2 for Audio
    E_UART_DMD51_UART0,     ///< DMD51 UART0 (only used in mdrv_uart_connect())
    E_UART_DMD51_UART1,     ///< DMD51 UART1 (only used in mdrv_uart_connect())
    E_UART_SECURE_R2,       ///< SECURE_R2 (only available for some chips)
    E_UART_OFF,             ///< UART Disable
} UART_DEVICE_TYPE;

/// UART port
/// different port have different pad mux, please check package spec.
/// sometimes the net name will mislead the real port number
typedef enum
{
    E_UART_PORT_INVALID = -1,///< invalid uart port
    E_UART_PORT0,           ///< usually muxed with DDCA
    E_UART_PORT1,           ///< port 1
    E_UART_PORT2,           ///< port 2
    E_UART_PORT3,           ///< port 3
    E_UART_PORT4,           ///< port 4
} UART_PORT_TYPE;

typedef enum _UART_DbgLv
{
    E_UART_DBGLV_NONE           //no debug message
    ,E_UART_DBGLV_ERR_ONLY      //show error only
    ,E_UART_DBGLV_INFO          //show error & informaiton
    ,E_UART_DBGLV_ALL           //show error, information & funciton name
}UART_DbgLv;


/// prototypr of UART rx callback
typedef void (*ms_uart_rx_callback)(int c);     // TODO: add user data?

/// prototypr of UART rx callback
typedef void (*ms_uart_rx_callback_halreg)(int c, MS_U32 pHalReg);

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
/// @brief open UART device, both rx/tx is enabled after this
/// @param uart_dev:    uart device instance to open (AEON / PIU_UARTx)
/// @return uart handle. when failed, it returns UART_DEV_NULL
///////////////////////////////////////////////////////////////////////////////
MS_U32 mdrv_uart_open(UART_DEVICE_TYPE uart_dev);

///////////////////////////////////////////////////////////////////////////////
/// @brief close a UART device handle
/// @param uart \b    uart handle to close
/// @return 0 if sucess, -1 if failed
///////////////////////////////////////////////////////////////////////////////
MS_U16 mdrv_uart_close(MS_U32 uart);

///////////////////////////////////////////////////////////////////////////////
/// Please note the connectivity should be a one-to-one mapping
/// @brief connect a UART device to a UART port
/// @param uart_port:   uart port
/// @param uart_dev:    uart device
/// @return 0: sucess, -1: failed
///////////////////////////////////////////////////////////////////////////////
MS_U16 mdrv_uart_connect(UART_PORT_TYPE uart_port, UART_DEVICE_TYPE uart_dev);

///////////////////////////////////////////////////////////////////////////////
/// @brief get the connection of UART port to UART device, (get device by port)
/// @param uart_port:   uart port
/// @return enum UART_DEVICE_TYPE, E_UART_INVALID if error occurs
///////////////////////////////////////////////////////////////////////////////
UART_DEVICE_TYPE mdrv_uart_get_connection(UART_PORT_TYPE uart_port);

///////////////////////////////////////////////////////////////////////////////
/// @brief Invert the signal polarity of UART
/// @param uart_port:   uart device
/// @param bInv:        0: not invert, 1 invert
/// @return 0: sucess -1: failed (uart_port out of range)
///////////////////////////////////////////////////////////////////////////////
MS_U16 mdrv_uart_invert(UART_PORT_TYPE uart_port, MS_BOOL bInv);

///////////////////////////////////////////////////////////////////////////////
/// Set the baudrate of the UART device, the base clock must be set before set
/// baudrate. If the clock is changed (like CKG_MCU change for E_UART_AEON),
/// this function must be called again for
/// @brief Set the baudrate of the UART device
/// @param uart:   uart device handle
/// @param baudrate: baudrate
/// @return 0: success, -1: failed
///////////////////////////////////////////////////////////////////////////////
MS_U16 mdrv_uart_set_baudrate(MS_U32 uart, MS_U32 baudrate);

///////////////////////////////////////////////////////////////////////////////
/// The rx_cb will be called every incoming byte is received
/// @brief Set RX callback by interrupt serive routine
/// @param uart:    uart device handle
/// @param rx_cb:   rx callback, 0 to disable the rx callback
/// @return 0: success, -1: failed
///////////////////////////////////////////////////////////////////////////////
MS_U16 mdrv_uart_set_rx_callback(MS_U32 uart, ms_uart_rx_callback rx_cb);

///////////////////////////////////////////////////////////////////////////////
/// If tx_buffer is not NULL, uart tx will use buffered mode, otherwise use polling mode
/// For Fast UART DMA mode, the buffer and len must aligned to MIU unit size
/// @brief set tx buffer for buffered mode
/// @param uart:        uart device handle
/// @param tx_buffer:   pointer to tx buffer
/// @param len:         tx buffer size
/// @return 0: success, -1: failed
///////////////////////////////////////////////////////////////////////////////
MS_U16 mdrv_uart_set_tx_buffer(MS_U32 uart, void *tx_buffer, MS_U16 len);

///////////////////////////////////////////////////////////////////////////////
/// If tx_buffer is not NULL, uart tx will use buffered mode, otherwise use polling mode
/// For Fast UART DMA mode, the buffer and len must aligned to MIU unit size
/// @brief set tx buffer for buffered mode
/// @param uart:        uart device handle
/// @param rx_buffer:   pointer to tx buffer
/// @param len:         tx buffer size
/// @return 0: success, -1: failed
///////////////////////////////////////////////////////////////////////////////
MS_U16 mdrv_uart_set_rx_buffer(MS_U32 uart, void *rx_buffer, MS_U16 len);

///////////////////////////////////////////////////////////////////////////////
/// @brief enable uart rx
/// @param uart:        uart device handle
/// @return 0: success, -1: failed
///////////////////////////////////////////////////////////////////////////////
MS_U16 mdrv_uart_rx_enable(MS_U32 uart);

///////////////////////////////////////////////////////////////////////////////
/// @brief enable uart tx
/// @param uart:        uart device handle
/// @return 0: success, -1: failed
///////////////////////////////////////////////////////////////////////////////
MS_U16 mdrv_uart_tx_enable(MS_U32 uart);

///////////////////////////////////////////////////////////////////////////////
/// @brief disable uart rx
/// @param uart:        uart device handle
/// @return 0: success, -1: failed
///////////////////////////////////////////////////////////////////////////////
MS_U16 mdrv_uart_rx_disable(MS_U32 uart);

///////////////////////////////////////////////////////////////////////////////
/// @brief disable uart tx
/// @param uart:        uart device handle
/// @return 0: success, -1: failed
///////////////////////////////////////////////////////////////////////////////
MS_U16 mdrv_uart_tx_disable(MS_U32 uart);

///////////////////////////////////////////////////////////////////////////////
/// @brief read data from uart
/// @param uart:        uart device handle
/// @param buf:         buffer to store read data
/// @param len:         buffer length
/// @return -1: failed, others: bytes read
///////////////////////////////////////////////////////////////////////////////
MS_U16 mdrv_uart_read(MS_U32 uart, MS_U8 *buf, MS_U32 len);

///////////////////////////////////////////////////////////////////////////////
/// @brief write data to uart
/// @param uart:        uart device handle
/// @param buf:         buffer for write data
/// @param len:         data length
/// @return -1: failed, others: bytes written
///////////////////////////////////////////////////////////////////////////////
MS_U16 mdrv_uart_write(MS_U32 uart, const MS_U8 *buf, MS_U16 len);

MS_U16 mdrv_uart_poll(MS_U32 hUart, int types);
MS_U16 mdrv_uart_set_rx_callback_halreg(MS_U32 uart, ms_uart_rx_callback_halreg rx_cb);

/// UART callback function used in interrupt context
typedef void(*P_UART_ISR_Proc)(MS_U8 u8UARTID);

UART_Result MDrv_UART_SetIOMapBase(void);
void MDrv_UART_Init(UART_DEVICE_TYPE uart_dev, MS_U32 baudrate);
void MDrv_UART_Standby_Init (void);
void MDrv_UART_PutChar(MS_U8 u8Ch);
void MDrv_UART_PutString(char *u8str);
MS_U8 MDrv_UART_GetChar(void);
void MDrv_UART_GetFile(MS_U8 *pu8Buf, MS_U32 u32Len);
const UART_DrvInfo* MDrv_UART_GetInfo(void);
UART_Result MDrv_UART_GetLibVer(const MSIF_Version **ppVersion);
UART_Result MDrv_UART_GetStatus(UART_DrvStatus *pStatus);
void MDrv_UART_SetDbgLevel(MS_U8 level);

#if UART_TYPE_EYWA
#define EYWA_PAYLOAD_LEN 8
#define EYWA_DEFAULT_PARITY 0

typedef struct _Eywa_FastUart_struct
{
	MS_U8 data_type;
	MS_U8 data_type_inv;
	MS_U16 len;
	MS_U8 payload[EYWA_PAYLOAD_LEN];
	MS_U8 parity;
} Eywa_FastUart_struct;

typedef enum
{
	E_EYWA_INVALID = 0,
	E_EYWA_KEYPAD,
	E_EYWA_VOICE,
	E_EYWA_GYROSCOPE,
	E_EYWA_GSENSOR,
	E_EYWA_TOUCHPAD
} EYWA_DATATYPE;

typedef enum
{
	E_EYWA_INV_INVALID = 0xFF,
	E_EYWA_INV_KEYPAD = 0xFE,
	E_EYWA_INV_VOICE = 0xFD,
	E_EYWA_INV_GYROSCOPE = 0xFC,
	E_EYWA_INV_GSENSOR = 0xFB,
	E_EYWA_INV_TOUCHPAD = 0xFA
} EYWA_DATATYPE_INV;

void Eywa_UART_RecvHandler(MS_U8);
MS_U8 Eywa_Cal8BitsChecksum(MS_U8 *, MS_U32);
void Eywa_UART_Init(void);

#endif


#ifdef __cplusplus
}
#endif

#endif /* __MDRV_UART_H__ */
