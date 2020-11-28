#include <common.h>

#include "serial_titania.h"
#if !defined(CONFIG_JANUS) && !defined(CONFIG_MARIA10)
//#include <regCHIP.h>
#endif

#define IO_WRITE(addr, val) (*(volatile unsigned int *)(addr) = (val))
#define IO_READ(addr) (*(volatile unsigned int *)(addr))
#define CONSOLE_PORT CONFIG_CONS_INDEX

/*
 * IntegratorCP has two UARTs, use the first one, at 38400-8-N-1
 * Versatile PB has four UARTs.
 */

#define CONSOLE_PORT    CONFIG_CONS_INDEX
#define baudRate        CONFIG_BAUDRATE

#if !defined(CONFIG_JANUS) && !defined(CONFIG_MARIA10)
    #define NUM_PORTS (sizeof(port)/sizeof(port[0]))
#endif

static void titania_putc (int portnum, char c);
static int titania_tstc (int portnum);
#if !defined(CONFIG_JANUS) && !defined(CONFIG_MARIA10)
    #define CPU_CLOCK_FREQ 12000000
#else
    #define CPU_CLOCK_FREQ 14400000
#endif

#define BOTH_EMPTY                  (UART_LSR_TEMT | UART_LSR_THRE)

#define UART_REG8(addr)             UART1_REG8(addr)
#define UART_MSEC_LOOP              ( CPU_CLOCK_FREQ/1000/4 )
#define UART_DELAY(_loop)           { volatile int i; for (i=0; i<(_loop)*UART_MSEC_LOOP; i++); }
#define UART_TIME(_stamp, _loop)    { _stamp = (_loop); }
#define UART_EXPIRE(_stamp)         ( !(--_stamp) )
#define UART_INIT()                 { }
#define UART_ENTRY()                { }
#define UART_RETURN()               { }

int serial_init (void)
{
	return 0;
}

void serial_putc (const char c)
{
    if(c == '\n')
    {
        titania_putc(CONSOLE_PORT, '\r'); //CR
        titania_putc(CONSOLE_PORT, '\n'); //LF
    }
    else
    {
        titania_putc(CONSOLE_PORT, c);
    }
}

void serial_puts (const char *s)
{
	while (*s)
    {
		serial_putc (*s++);
	}
}

static int titania_tstc (int portnum)
{
	return ((UART_REG8(UART_LSR)&UART_LSR_DR) == UART_LSR_DR); //TRUE if data in Rx FIFO
	//return 0;
}

#if defined(CONFIG_JANUS) || defined(CONFIG_MARIA10)
int serial_getc (void)
{
    MS_U8 lsr, ier;
    MS_U8 c;

    ier = UART_REG8(UART_IER);
    UART_REG8(UART_IER) = 0;

    do
    {
        lsr = UART_REG8(UART_LSR);
    } while ((lsr & UART_LSR_DR) != UART_LSR_DR);

    c = UART_REG8(UART_RX);

    UART_REG8(UART_IER) = ier;

    return c;

}
#else
int serial_getc (void)
{
    MS_U8 u8Ch, u8Reg;
    do {
        u8Reg = UART_REG8(UART_LSR);
        if ( (u8Reg & UART_LSR_DR) == UART_LSR_DR )
        {
            break;
        }
    } while (1);

    u8Ch = UART_REG8(UART_RX);	//get char
    return u8Ch;

}
#endif

static void titania_putc (int portnum, char c)
{
    MS_U8 u8Reg;

    do {
        u8Reg = UART_REG8(UART_LSR);
        if ((u8Reg & BOTH_EMPTY) == BOTH_EMPTY)
    	{
            break;
        }
    }while(1);

    UART_REG8(UART_TX) = c;	//put char
}

int serial_tstc (void)
{
	return titania_tstc (CONSOLE_PORT);
}

void serial_setbrg (void)
{
}



//#endif //ifdef CONFIG_URANUS
