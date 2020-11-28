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

#define _UART_C_

////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "datatype.h"
#include "drvGlobal.h"
#include "hwreg.h"
#include "MsCommon.h"
#include "MApp_Wakeup.h"
#include "drvUART.h"
#include "uartdebug.h"
#include "msIR.h"
#include "MApp_Key.h"
#include "xcSys.h"

////////////////////////////////////////////////////////////////////////////////

#define ENABLE_CUS_UART_TEST_COMMAND    1
#define ENABLE_CUS_UART_CMD_RW_BANK_N   1
#define ENABLE_DEBUG_RW_MEMORY          1

#define XC_RIU_BASE                     0x102F00

////////////////////////////////////////////////////////////////////////////////

static MS_U32 uart_debug;
#if ENABLE_UART2
static MS_U32 uart2_debug;
U8 g_Uart2_ack = 0;
#endif

////////////////////////////////////////////////////////////////////////////////

void putcharb(MS_U8 byte)
{
    if (uart_debug)
    {
        mdrv_uart_write(uart_debug, (MS_U8 *)&byte, 1);
    }
}


#if( ENABLE_DEBUG_RW_MEMORY )

static U32 g_u32DebugRWMemBaseAddress = 0;

static U8 DrvMemReadByte(U32 u32MemAddr )
{
    U8 *pu8;
    pu8 = (U8*)_PA2VA(u32MemAddr);
    return *pu8;
}

static void DrvMemWriteByte(U32 u32MemAddr, U8 u8Data )
{
    U8 *pu8;
    pu8 = (U8*)_PA2VA(u32MemAddr);
    *pu8 = u8Data;
}

static U8 NormalCmd_ReadXData1001xx(U8 u8Offset)
{
    U8 uc;

    switch(u8Offset)
    {
        case 0xF0:
            uc = g_u32DebugRWMemBaseAddress;
            break;
        case 0xF1:
            uc = g_u32DebugRWMemBaseAddress>>8;
            break;
        case 0xF2:
            uc = g_u32DebugRWMemBaseAddress>>16;
            break;
        case 0xF3:
            uc = g_u32DebugRWMemBaseAddress>>24;
            break;
        default:
            uc = DrvMemReadByte(g_u32DebugRWMemBaseAddress+u8Offset);
            break;
    }
    return uc;
}

static void NormalCmd_WriteXData1001xx(U8 u8Offset, BYTE u8Data)
{
    switch(u8Offset)
    {
        case 0xF0:
            g_u32DebugRWMemBaseAddress = (DWORD)u8Data|(g_u32DebugRWMemBaseAddress&0xFFFFFF00);
            printf("memAddr=%lX\n", g_u32DebugRWMemBaseAddress);
            break;
        case 0xF1:
            g_u32DebugRWMemBaseAddress = (DWORD)u8Data<<8|(g_u32DebugRWMemBaseAddress&0xFFFF00FF);
            printf("memAddr=%lX\n", g_u32DebugRWMemBaseAddress);
            break;
        case 0xF2:
            g_u32DebugRWMemBaseAddress = (DWORD)u8Data<<16|(g_u32DebugRWMemBaseAddress&0xFF00FFFF);
            printf("memAddr=%lX\n", g_u32DebugRWMemBaseAddress);
            break;
        case 0xF3:
            g_u32DebugRWMemBaseAddress = (DWORD)u8Data<<24|(g_u32DebugRWMemBaseAddress&0x00FFFFFF);
            printf("memAddr=%lX\n", g_u32DebugRWMemBaseAddress);
            break;
        default:
            DrvMemWriteByte( g_u32DebugRWMemBaseAddress+u8Offset, u8Data );
            printf("mem[%lX]=%X\n", g_u32DebugRWMemBaseAddress+u8Offset, u8Data);
            break;
    }
}
#endif // #if( ENABLE_DEBUG_RW_MEMORY )

#define ENABLE_UART_CHECKSUM 1
// Check uart protocal
#if ( ENABLE_UART_CHECKSUM )
BOOL IsUartCmdValid(void);
BOOL IsUartCmdValid(void)
{
    MS_U8 i, ucLen;
    MS_U8 ucCS = 0;

    if( UART_EXT )
    {
        ucLen = UART_CMD_EXT_LENGTH;
    }
    else
    {
        ucLen = UART_CMD_LENGTH;
    }

    ucCS = 0;

    for( i = 0; i < ucLen; ++ i )
    {
        ucCS += g_UartCommand.Buffer[i];
    }

    if( ucCS == 0xFF )
        return 1;
    else
        return 0;
}

#endif

void MDrv_UART_RecvHandler(int c)
{
    MDrv_UART_ChckWakeupEvent(c);

    g_Uart0CheckTick = 50;// time-out control ms

    if (g_UartCommand.Index >= _UART_CMD_LENGTH_)
    {
        g_UartCommand.Index = 0;
    }

    g_UartCommand.Buffer[g_UartCommand.Index] = c;

    if( g_bDebugProgStopFlag )
        printf("[%d] = %x \r\n", g_UartCommand.Index, c);

    // check command buffer index
    if (UART_EXT)
    {
        if (g_UartCommand.Index == 0) // check 1st data
        {
            g_UartCommand.Index++; // for get UART_CMD_EXT_LENGTH
        }
        else
        {
            if (g_UartCommand.Index < UART_CMD_EXT_LENGTH) // still read command
            {
                g_UartCommand.Index++; // next index of command buffer
            }
            if (g_UartCommand.Index >= UART_CMD_EXT_LENGTH) // read command ok
            {
            #if ( ENABLE_UART_CHECKSUM )
                if( IsUartCmdValid() )
            #endif
                g_bUart0Detected = TRUE; // command  buffer recieve ok
                g_UartCommand.Index = 0; // reset index of command buffer
                g_Uart0CheckTick = 0;
            }
        }
    }
    else
    {
        if (g_UartCommand.Index < UART_CMD_LENGTH) // still read command
        {
            g_UartCommand.Index++; // next index of command buffer
        }
        if (g_UartCommand.Index >= UART_CMD_LENGTH) // read command ok
        {
            #if ( ENABLE_UART_CHECKSUM )
             if( IsUartCmdValid() )
            #endif
            g_bUart0Detected = TRUE; // command  buffer recieve ok
            g_UartCommand.Index = 0; // reset index of command buffer
            g_Uart0CheckTick = 0;
        }
    }

    MsOS_EnableInterrupt(E_INT_IRQ_UART0);

}

#if ENABLE_UART2
void MDrv_UART2_RecvHandler(int c)
{
	MDrv_UART_ChckWakeupEvent(c);
    g_Uart2CheckTick = 50;

    if (g_Uart2Command.Index >= _UART_CMD_LENGTH_)
    {
        g_Uart2Command.Index = 0;
    }
    g_Uart2Command.Buffer[g_Uart2Command.Index] = c; // recieve byte
    g_Uart2_ack = 0xE5;

    g_Uart2Command.Index ++;
    if (g_Uart2Command.Index == 9)
    {
        g_bUart2Detected     = TRUE; // command  buffer recieve ok
        g_Uart2Command.Index = 0;    // reset index of command buffer
        g_Uart2CheckTick     = 0;
    }
    else if(g_Uart2Command.Buffer[0] == 0x69 && g_Uart2Command.Index == 3)
    {
        g_bUart2Detected     = TRUE; // command  buffer recieve ok
        g_Uart2Command.Index = 0;    // reset index of command buffer
        g_Uart2CheckTick     = 0;
    }

    MsOS_EnableInterrupt(E_INT_IRQ_UART1);
}
#endif // #if ENABLE_UART2


void MDrv_UART_ConfigWakeup(void)
{
    MDrv_UART_Init(E_UART_AEON,38400);

    g_UartCommand.Index = 0;

    g_bDebugProgStopFlag = FALSE;

    g_Uart0CheckTick = 0;

    uart_debug = mdrv_uart_open(E_UART_AEON_R2);

    if (uart_debug)
    {
        mdrv_uart_set_rx_callback(uart_debug, MDrv_UART_RecvHandler);
    }

  #if ENABLE_UART2
    g_Uart2Command.Index = 0;

    g_Uart2CheckTick = 0;

    uart2_debug = mdrv_uart_open(E_UART_PIU_UART1);

    mdrv_uart_connect(E_UART_PORT2, E_UART_PIU_UART1);

    if (uart2_debug)
    {
        mdrv_uart_set_rx_callback(uart2_debug, MDrv_UART2_RecvHandler);

    }
  #endif

}


BOOL Cus_UART_ExecTestCommand(void)
{
    BOOL bRtn = TRUE;
    U8 u8XCBank;
    U8 ucPara1;
    U8 ucPara2;
    U8 ucPara3;

    ucPara1 = g_UartCommand.Buffer[_UART_CMD_INDEX2_];
    ucPara2 = g_UartCommand.Buffer[_UART_CMD_INDEX3_];
    ucPara3 = g_UartCommand.Buffer[_UART_CMD_INDEX4_];

    u8XCBank = MDrv_ReadByte(XC_RIU_BASE);

#if 0
    if( g_bDebugProgStopFlag )
        printf(">> Cus_UART_ExecTestCommand(%x) \r\n", g_UartCommand.Buffer[_UART_CMD_INDEX1_]);
#endif

    switch ( g_UartCommand.Buffer[_UART_CMD_INDEX1_] )
    {

        default:
//            printf("No case for Cus_UART_ExecTestCommand \r\n");
            bRtn = FALSE; // Use system default test command
            break;
    }

    MDrv_WriteByte(XC_RIU_BASE, u8XCBank);
    return bRtn;
}


BOOL Cus_UART_DecodeCommand(void)
{
    BOOL bRtn = TRUE;
  #if( ENABLE_CUS_UART_CMD_RW_BANK_N )
    static U8 u8XCBank = 0;
  #endif
    U32 u32Tmp;

#if 0
    if( g_bDebugProgStopFlag )
        printf(">> Cus_UART_DecodeCommand(%x) \r\n", UART_CMD);
#endif

    switch (UART_CMD)
    {
    #if( ENABLE_CUS_UART_CMD_RW_BANK_N )
        case uartWrite_MST_Bank_n:
            u32Tmp = ((U8)UART_CMD_MS_BANK_H << 16) |
                           ((U8)UART_CMD_MS_BANK_L << 8)  |
                            (U8)UART_CMD_MS_REGINDEX;

            if( u32Tmp == 0x102F00 ) // Scaler bank sel
                u8XCBank = UART_CMD_MS_REGDATA;
            else if( (u32Tmp&0xFFFF00) == 0x102F00 ) // Scaler bank
            {
                MDrv_WriteByte( 0x102F00, u8XCBank ); // Sel bank
            }

            MDrv_WriteByte( u32Tmp, UART_CMD_MS_REGDATA );

            putcharb( 0xF1 );
            break;

        case uartRead_MST_Bank_n:
            u32Tmp = ((U8)UART_CMD_MS_BANK_H << 16) |
                           ((U8)UART_CMD_MS_BANK_L << 8)  |
                            (U8)UART_CMD_MS_REGINDEX;

            /*if( u32Tmp == 0x102F00 ) // Scaler bank sel
                {}
            else*/ if( (u32Tmp&0xFFFF00) == 0x102F00 ) // Scaler bank
            {
                MDrv_WriteByte( 0x102F00, u8XCBank ); // Sel bank
            }

            putcharb( 0xF2 );
            putcharb( MDrv_ReadByte(u32Tmp) );

            //printf("\nRn[%X],", u32Tmp );
            break;
    #endif // #if( ENABLE_CUS_UART_CMD_RW_BANK_N )


    #if( ENABLE_DEBUG_RW_MEMORY )
        case uartWrite_MCU_XDATA:
            u32Tmp = ((U8)UART_CMD_MS_BANK_H << 16) |
               ((U8)UART_CMD_MS_BANK_L << 8)  |
                (U8)UART_CMD_MS_REGINDEX;

            if( (u32Tmp&0xFFFF00) == 0x100100 ) // R/W memory port
            {
                putcharb( 0xF1 );
                NormalCmd_WriteXData1001xx(u32Tmp&0xFF, UART_CMD_MCU_DATA);
            }
            else
            {
                bRtn = FALSE;
            }

            break;
        case uartRead_MCU_XDATA:
            u32Tmp = ((U8)UART_CMD_MS_BANK_H << 16) |
               ((U8)UART_CMD_MS_BANK_L << 8)  |
                (U8)UART_CMD_MS_REGINDEX;

            if( (u32Tmp&0xFFFF00) == 0x100100 ) // R/W memory port
            {
                putcharb( 0xF2 );
                putcharb( NormalCmd_ReadXData1001xx(u32Tmp&0xFF) );
            }
            else
            {
                bRtn = FALSE;
            }
            break;
    #endif


    #if( ENABLE_CUS_UART_TEST_COMMAND )
        case uartTest_Command:
            bRtn = Cus_UART_ExecTestCommand();
            break;
    #endif


        default:
            u32Tmp = 0; // For warning
            bRtn = FALSE;
//            printf("No case for Cus_UART_DecodeCommand \r\n");
            break;
    }

    return bRtn;
}

void Cus_UART_DecodeExtCommand(void)
{
#if 0
    if( g_bDebugProgStopFlag )
        printf(">> Cus_UART_DecodeExtCommand(%x) \r\n", UART_EXT_DEV);
#endif

    switch( UART_EXT_DEV )
    {

        default:
//            printf("No case for Cus_UART_DecodeExtCommand \r\n");
            break;
    }
}

void MDrv_UART_DecodeExtCommand(void)
{
//    MS_U8 u8addressCount, u8dataCount;
//    MS_U8 u8Result, i;

#if 0
    if( g_bDebugProgStopFlag )
        printf(">> MDrv_UART_DecodeExtCommand(%x) \r\n", UART_EXT_DEV);
#endif

    switch( UART_EXT_DEV )
    {
       case uartExtDev_XC_rw:

         if (UART_EXT_CMD == 0x02)
         {
            MDrv_WriteByte(0x102F00, UART_EXT_CMD_MS_DAT1 );

            MDrv_WriteByte(((U8)UART_EXT_CMD_MS_DAT2 << 16) |
                            ((U8)UART_EXT_CMD_MS_DAT3 << 8)  |
                            (U8)UART_EXT_CMD_MS_DAT4,
                           (U8)UART_EXT_CMD_MS_DAT5
                           );
            putcharb(0xF1);
         }
         else if (UART_EXT_CMD == 0x01)
         {
            putcharb(0xF2);

            MDrv_WriteByte(0x102F00, UART_EXT_CMD_MS_DAT1 );
            putcharb(MDrv_ReadByte(((U8)UART_EXT_CMD_MS_DAT2 << 16) |
                                     ((U8)UART_EXT_CMD_MS_DAT3 << 8)  |
                                     (U8)UART_EXT_CMD_MS_DAT4
                                   )
                     );
        }
        break;


         default:
            printf("No case for MDrv_UART_DecodeExtCommand \r\n");
            break;
    }
}

void MDrv_UART_ExecTestCommand(void)
{
    U8 ucPara1;
    U8 ucPara2;
    U8 ucPara3;

    ucPara1 = g_UartCommand.Buffer[_UART_CMD_INDEX2_];
    ucPara2 = g_UartCommand.Buffer[_UART_CMD_INDEX3_];
    ucPara3 = g_UartCommand.Buffer[_UART_CMD_INDEX4_];

//    printf(">> MDrv_UART_DecodeExtCommand(%x) \r\n", g_UartCommand.Buffer[_UART_CMD_INDEX1_]);

    switch ( g_UartCommand.Buffer[_UART_CMD_INDEX1_] )
    {
        case 0x50:
            g_bDebugProgStopFlag = !g_bDebugProgStopFlag;
            if( g_bDebugProgStopFlag )
            {
                printf("<Debug>\r\n");
            }
            else
            {
                printf("<Free>\r\n");
            }
            break;

        case 0x63:  // Keypad Up
            u8KeyCode = KEY_UP;
            break;
        case 0x72:  // Keypad Left
            u8KeyCode = KEY_LEFT;
            break;
        case 0x73:  // Keypad Menu
            u8KeyCode = KEY_MENU;
            break;
        case 0x74:  // Keypad Right
            u8KeyCode = KEY_RIGHT;
            break;
        case 0x75:  // Keypad Source
            u8KeyCode = KEY_INPUT_SOURCE;
            break;
        case 0x76:  // Keypad Power
            u8KeyCode = KEY_POWER;
            break;
        case 0x83:  // Keypad Down
            u8KeyCode = KEY_DOWN;
            break;

        case 0x84:  // IRKEY_EXIT
            u8KeyCode = KEY_EXIT;
            break;

        case 0x90:  // Irkey Input
            u8KeyCode = KEY_INPUT_SOURCE;
            break;
        case 0x91:  // Irkey Sleep
            u8KeyCode = KEY_SLEEP;
            break;
        case 0x92:  // Irkey 1
            u8KeyCode = KEY_1;
            break;
        case 0x93:  // Irkey 4
            u8KeyCode = KEY_4;
            break;
        case 0x94:  // Irkey 7
            u8KeyCode = KEY_7;
            break;
        case 0x95:  // Irkey 0
            u8KeyCode = KEY_0;
            break;
        case 0x96:  // Irkey Select
            u8KeyCode = KEY_SELECT;
            break;
        case 0x97:  // Irkey Menu
            u8KeyCode = KEY_MENU;
            break;
        case 0xA1:  // Irkey Display
            u8KeyCode = KEY_INFO;
            break;
        case 0xA2:  // Irkey 2
            u8KeyCode = KEY_2;
            break;
        case 0xA3:  // Irkey 5
            u8KeyCode = KEY_5;
            break;
        case 0xA4:  // Irkey 8
            u8KeyCode = KEY_8;
            break;
        case 0xA5:  // Irkey -
            u8KeyCode = KEY_DASH;
            break;
        case 0xA6:  // Irkey Up
            u8KeyCode = KEY_INPUT_SOURCE;
            break;
        case 0xA7:  // Irkey Left
            u8KeyCode = KEY_LEFT;
            break;
        case 0xB1:  // Irkey MTS
            u8KeyCode = KEY_MTS;
            break;
        case 0xB2:  // Irkey 3
            u8KeyCode = KEY_3;
            break;
        case 0xB3:  // Irkey 6
            u8KeyCode = KEY_6;
            break;
        case 0xB4:  // Irkey 9
            u8KeyCode = KEY_9;
            break;
        case 0xB5:  // Irkey Freeze
            u8KeyCode = KEY_FREEZE;
            break;
        case 0xB6:  // Irkey Zoom
            u8KeyCode = KEY_ZOOM;
            break;
        case 0xB7:  // Irkey Right
            u8KeyCode = KEY_RIGHT;
            break;
        case 0xB8:  // Irkey Exit
            u8KeyCode = KEY_EXIT;
            break;
        case 0xC1:  // Irkey Mute
            u8KeyCode = KEY_MUTE;
            break;
        case 0xC2:  // Irkey Vol+
            u8KeyCode = KEY_VOLUME_PLUS;
            break;
        case 0xC3:  // Irkey Vol-
            u8KeyCode = KEY_VOLUME_MINUS;
            break;
        case 0xC4:  // Irkey Ch+
            u8KeyCode = KEY_CHANNEL_PLUS;
            break;
        case 0xC5:  // Irkey Ch-
            u8KeyCode = KEY_CHANNEL_MINUS;
            break;
        case 0xC7:  // Irkey Down
            u8KeyCode = KEY_DOWN;
            break;
        case 0xD0:  // Irkey Power
            u8KeyCode = KEY_POWER;
            break;

        default:
            printf("No case for MDrv_UART_ExecTestCommand \r\n");
            break;
    }
}

void MDrv_UART_DecodeNormalCommand(void)
{
//    U8 u8Value;
//    U16 u16EEADDR;

#if 0
    if( g_bDebugProgStopFlag )
        printf(">> MDrv_UART_DecodeNormalCommand(%x) \r\n", UART_CMD);
#endif

    switch ( UART_CMD )
    {
        case uartWrite_MST_Bank_n:
            MDrv_WriteByte(((U8)UART_CMD_MS_BANK_H << 16) |
                           ((U8)UART_CMD_MS_BANK_L << 8)  |
                            (U8)UART_CMD_MS_REGINDEX,
                           UART_CMD_MS_REGDATA
                          );
            putcharb( 0xF1 );
            break;

        case uartRead_MST_Bank_n:
            putcharb( 0xF2 );
            putcharb(MDrv_ReadByte(((U8)UART_CMD_MS_BANK_H << 16) |
                                   ((U8)UART_CMD_MS_BANK_L << 8)  |
                                   (U8)UART_CMD_MS_REGINDEX
                                  )
                    );
            break;


        case uartWrite_MCU_XDATA:
             MDrv_WriteByte(((U8)UART_CMD_MCU_IDX_H1 << 16) |
                             ((U8)UART_CMD_MCU_IDX_H2 << 8)  |
                             (U8)UART_CMD_MCU_IDX_L,
                            UART_CMD_MCU_DATA
                          );
            putcharb( 0xF1 );
            break;

        case uartRead_MCU_XDATA:
            putcharb( 0xF2 );
            putcharb(MDrv_ReadByte(((U8)UART_CMD_MCU_IDX_H1 << 16) |
                                   ((U8)UART_CMD_MCU_IDX_H2 << 8)  |
                                   (U8)UART_CMD_MCU_IDX_L
                                  )
                    );
            break;

/*
        case uartI2C_Device_Write:
            if ( FALSE == MDrv_IIC_WriteByte( UART_CMD_MCU_IDX_H, UART_CMD_MCU_IDX_L, UART_CMD_MCU_DATA ) )
            {
                printf( "I2C Error!!! uartI2C_Device_Write\n" );
            }

            putcharb( 0xF1 );
            break;

        case uartI2C_Device_Read:
            putcharb( 0xF2 );
            if ( MDrv_IIC_ReadByte( UART_CMD_MCU_IDX_H, UART_CMD_MCU_IDX_L, &u8Value ) )
                putcharb( u8Value );
            else
                putcharb( 0xFF );
            break;
*/

        case uartTest_Command:
            MDrv_UART_ExecTestCommand();
            break;

        default:
//            printf("No case for MDrv_UART_DecodeNormalCommand \r\n");
            break;
    }
}

void UART_DecodeCommand(void)
{
    if (!g_bDisableUartDebug && g_bUart0Detected) // check command flag
    {
        g_bUart0Detected = FALSE;

        { //command normal mode
            if (UART_EXT)
            {
                Cus_UART_DecodeExtCommand();
                MDrv_UART_DecodeExtCommand();
            }
            else
            {
                if( Cus_UART_DecodeCommand() == FALSE )
                    MDrv_UART_DecodeNormalCommand();
            }
        }
    }
}


U8 msAPI_UART_DecodeCommand(void)
{
    UART_DecodeCommand();

    // stop main loop for debug
    /*if( g_bDebugProgStopFlag )
        return 1;
    else*/
        return 0;
}



////////////////////////////////////////////////////////////////////////////////
#undef _UART_C_

