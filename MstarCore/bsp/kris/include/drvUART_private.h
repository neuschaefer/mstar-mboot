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
////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVUART_PRIV_H_
#define _DRVUART_PRIV_H_

////////////////////////////////////////////////////////////////////////////////
/// @file drvUART_private.h
/// @author MStar Semiconductor Inc.
/// @brief UART control driver
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////
#include "MsCommon.h"

#ifdef __cplusplus
extern "C"
{
#endif
#include "MsTypes.h"

enum {
    MDrv_CMD_UART_Open,
    MDrv_CMD_UART_Close,
    MDrv_CMD_UART_Connect,
    MDrv_CMD_UART_SetBaudRate,
} eMbxIoctlOpt;

void UARTRegisterToUtopia(FUtopiaOpen ModuleType);
MS_U32 UARTOpen(void** pInstance, MS_U32 u32ModuleVersion, void* pAttribute);
MS_U32 UARTClose(void* pInstance);
MS_U32 UARTIoctl(void* pInstance, MS_U32 u32Cmd, void *pArgs);

typedef MS_U32 (*IOCTL_UART_OPEN)(UART_DEVICE_TYPE);
typedef MS_U16 (*IOCTL_UART_CLOSE)(MS_U32);
typedef MS_U16 (*IOCTL_UART_CONNECT)(UART_PORT_TYPE, UART_DEVICE_TYPE);
typedef MS_U16 (*IOCTL_UART_SET_BAUDRATE)(MS_U32, MS_U32);

typedef struct _UART_OPEN
{
    UART_DEVICE_TYPE eUartType;
}UART_OPEN, *PUART_OPEN;

typedef struct _UART_CLOSE
{
    MS_U32 u32Fd;
}UART_CLOSE, *PUART_CLOSE;

typedef struct _UART_CONNECT
{
    UART_PORT_TYPE ePortType;
    UART_DEVICE_TYPE eDeviceType;
}UART_CONNECT, *PUART_CONNECT;

typedef struct _UART_SET_BAUDRATE
{
    MS_U32 u32Uart;
    MS_U32 u32BaudRate;
}UART_SET_BUADRATE, *PUART_SET_BUAD_RATE;

typedef struct _UART_INSTANT_PRIVATE
{
    IOCTL_UART_OPEN                       fpUARTOpen;
    IOCTL_UART_CLOSE                      fpUARTClose;
    IOCTL_UART_CONNECT                    fpUARTConnect;
    IOCTL_UART_SET_BAUDRATE               fpUARTSetBaudRate;
}UART_INSTANT_PRIVATE;

typedef struct _UART_RESOURCE_PRIVATE
{
    MS_U32 Dummy;
}UART_RESOURCE_PRIVATE;

//instant
typedef struct _UART_INSTANT_ATTRIBUTE
{
    UART_DEVICE_TYPE  eUartType;
    MS_U32 u32BaudRate;
}UART_INSTANT_ATTRIBUTE;

#ifdef __cplusplus
}
#endif
#endif //_DRVUART_PRIV_H_

