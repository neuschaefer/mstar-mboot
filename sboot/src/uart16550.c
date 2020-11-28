/////////////////////////////////////////////////////////////////////////////
// * Copyright (C) 2001 MontaVista Software Inc.
// * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net
// *
// * This program is free software; you can redistribute  it and/or modify it
// * under  the terms of  the GNU General  Public License as published by the
// * Free Software Foundation;  either version 2 of the  License, or (at your
// * option) any later version.
// *
/////////////////////////////////////////////////////////////////////////////


#include "uart16550.h"


//dhjung LGE
uint32 Uart16550TestC(void)
{
    return ((UART_REG8(UART_LSR)&UART_LSR_DR) == UART_LSR_DR); //TRUE if data in Rx FIFO
}

uint8 Uart16550GetPoll(void)
{
//dhjung LGE
#if 1
    u8 u8Ch, u8Reg;
    do {
        u8Reg = UART_REG8(UART_LSR);
        if ( (u8Reg & UART_LSR_DR) == UART_LSR_DR )
        {
            break;
        }
    } while (1);

    u8Ch = UART_REG8(UART_RX);  //get char
    return u8Ch;

#else

    u8 u8Ch;

    while ( (UART_REG8(UART_LSR)&UART_LSR_DR) != UART_LSR_DR);  //data ready in rx FIFO???

    u8Ch = (u8)(UART_REG8(UART_FIFO));

    UART_REG8(UART_RB)|=0x8000;

    return u8Ch;
#endif
}

void Uart16550Put(uint8 byte)
{
//dhjung LGE
#if 1
    u8  u8Reg;
    //u32 u32Timer;

    //Wait for Transmit-hold-register empty
    //UART_TIME(u32Timer,10)  //10ms for OS version
    do {
        u8Reg = UART_REG8(UART_LSR);
        if ((u8Reg & UART_LSR_THRE) == UART_LSR_THRE)
        {
            break;
        }
    }while(1);

    UART_REG8(UART_TX) = byte;  //put char

    //Wait for both Transmitter empty & Transmit-hold-register empty
    //UART_TIME(u32Timer,10)  //10ms for OS version
    do {
        u8Reg = UART_REG8(UART_LSR);
        if ((u8Reg & BOTH_EMPTY) == BOTH_EMPTY)
        {
            break;
        }
    }while(1);

#else

    while( ( UART_REG8(UART_LSR)&UART_LSR_TXFIFO_FULL) == UART_LSR_TXFIFO_FULL);  //data full in tx FIFO???

    //CAUTION : Need to sync the Rx and Tx INT config in the MDrv_UART_Init()
    UART_REG8(UART_FIFO) = UART_IER_RDA | byte;	//put char
#endif
}

