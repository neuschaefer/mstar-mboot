@-------------------------------------------------------------------------------------------------
@ UART registers
@-------------------------------------------------------------------------------------------------
UART_BASE                   = (MS_BUS_RIU_ADDR+0x00201300)
UART_LCR_DLAB               =  0x80    @ Divisor latch access bit
UART_LCR_SBC                =  0x40    @ Set break control
UART_LCR_SPAR               =  0x20    @ Stick parity (?)
UART_LCR_EPAR               =  0x10    @ Even parity select
UART_LCR_PARITY             =  0x08    @ Parity Enable
UART_LCR_STOP1              =  0x00    @ Stop bits: 0=1 stop bit, 1= 2 stop bits
UART_LCR_STOP2              =  0x04    @ Stop bits: 0=1 stop bit, 1= 2 stop bits
UART_LCR_WLEN5              =  0x00    @ Wordlength: 5 bits
UART_LCR_WLEN6              =  0x01    @ Wordlength: 6 bits
UART_LCR_WLEN7              =  0x02    @ Wordlength: 7 bits
UART_LCR_WLEN8              =  0x03    @ Wordlength: 8 bits

@Baud rate
UART_BAUD_RATE	        = 115200

@CPU clock
CPU_CLOCK_FREQ          = 900000000

@Clock source
UART_CLK_FREQ           = 123000000

@Divisor
UART_DIVISOR            = (UART_CLK_FREQ/(16 * UART_BAUD_RATE))

UART_DIVISOR_H          = (UART_DIVISOR >> 8)
UART_DIVISOR_L          = (UART_DIVISOR & 0xff)

@-------------------------------------------------------------------------------------------------
@ UART Register
@-------------------------------------------------------------------------------------------------
UART_RX      =    (0 * 4)    @ In:  Receive buffer (DLAB=0)    (16-byte FIFO)
UART_TX      =    (0 * 4)    @ Out: Transmit buffer (DLAB=0)   (16-byte FIFO)
UART_DLL     =    (0 * 4)    @ Out: Divisor Latch Low (DLAB=1)
UART_DLM     =    (1 * 4)    @ Out: Divisor Latch High (DLAB=1)
UART_IER     =    (1 * 4)    @ Out: Interrupt Enable Register
UART_IIR     =    (2 * 4)    @ In:  Interrupt ID Register
UART_FCR     =    (2 * 4)    @ Out: FIFO Control Register
UART_LCR     =    (3 * 4)    @ Out: Line Control Register
UART_MCR     =    (4 * 4)    @ Out: Modem Control Register
UART_LSR     =    (5 * 4)    @ In:  Line Status Register
UART_MSR     =    (6 * 4)    @ In:  Modem Status Register
UART_SCR     =    (7 * 4)    @ I/O: Scratch Register
@-------------------------------------------------------------------------------------------------
@ FIFO Control Register
@-------------------------------------------------------------------------------------------------
UART_FCR_ENABLE_FIFO         =   0x01    @ Enable the FIFO
UART_FCR_CLEAR_RCVR          =   0x02    @ Clear the RCVR FIFO
UART_FCR_CLEAR_XMIT          =   0x04    @ Clear the XMIT FIFO
UART_FCR_DMA_SELECT          =   0x08    @ For DMA applications
UART_FCR_TRIGGER_MASK        =   0xC0    @ Mask for the FIFO trigger range
UART_FCR_TRIGGER_1           =   0x00    @ Mask for trigger set at 1
UART_FCR_TRIGGER_4           =   0x40    @ Mask for trigger set at 4
UART_FCR_TRIGGER_8           =   0x80    @ Mask for trigger set at 8
UART_FCR_TRIGGER_14          =   0xC0    @ Mask for trigger set at 14

@-------------------------------------------------------------------------------------------------
@ Init setup
@-------------------------------------------------------------------------------------------------
@@@ UART 0 = 1: enable UART 0  Disable UART 2
@@@ UART 0 = 0: enable UART 2  Disable UART 0
UART0           = 1

@-------------------------------------------------
@Macro: PUTK
@-------------------------------------------------
.macro PUTK char
    #LDR	    r12, =\char
    #REG_C2M r12, 0x1F201300
    WREG_B 0x1F201300 \char
.endm

@-------------------------------------------------
@Macro: DPUTK
@-------------------------------------------------
.macro DPUTK char
    WREG_B 0x1F201300 \char
DPUTK_\@:
    RREG r12, 0x1F201328
    and r12, r12, #0x0060
    cmp r12, #0x0060
    bne DPUTK_\@
.endm

#[*] BOOT_InitUART
@-------------------------------------------------
@Macro: drv_uart_init_fpga
@-------------------------------------------------
.macro drv_uart_init_fpga

#    WREG 0x1F001c24, 0x0800
    WREG 0x1F201310, 0x0001
    WREG 0x1F201318, 0x0083
    WREG 0x1F201308, 0x0000
    WREG 0x1F201300, 0x0013
    WREG 0x1F201318, 0x0003
    WREG 0x1F203d50, 0x0005
    WREG 0x1F203d4c, 0x2104

.endm

@-------------------------------------------------
@Macro: drv_uart_init
@-------------------------------------------------
.macro drv_uart_init
#if 0
    WREG        (CLK_GEN0_BASE+0x13*4) 0x0C01     @ 123Mhz
#else
    WREG        0x1F20164C  0x0C01
#endif

.if (UART0==1)
    #enable reg_uart_rx_enable
    RREG        r0,     0x1F001c24
    orr         r0,     r0,#0x0800
    REG_C2M     r0,     0x1F001c24

    #Select to PIU_UART0
    RREG        r0,     0x1F203d4c
    orr         r0,     r0,         #0x0004
    REG_C2M     r0,     0x1F203d4c
.endif

.if (UART0==0)
##   Select UART2 source
    WREG        0x1F203d4c  0x0400
    WREG        0x1F203d50  0x0000
    #10: RX2/TX2 uses PAD_DDCR_DA2/PAD_DDCR_CK2
    RREG        r0,         0x1F203c08
    orr         r0,         r0,     #0x0800
    REG_C2M     r0,         0x1F203c08

    RREG        r0,         0x1F203c08
    and         r0,         r0,     #0xFBFF
    REG_C2M     r0,         0x1F203c08
.endif

    RREG        r0,         0x1F201318   @ Divisor Latch Access;
    orr         r0,         r0,     #0x0080       @ 1: The divisor latches can be accessed
    REG_C2M     r0,         0x1F201318

    WREG        0x1F201300  UART_DIVISOR_L
    WREG        0x1F201308  UART_DIVISOR_H

    RREG        r0,         0x1F201318    @ Kernel need
#if 0
    and         r0,         r0,     #0xFF7F
#else
    bic         r0,         r0,     #0x0080
#endif
    REG_C2M     r0,         0x1F201318

    WREG        0x1F201310  0x0000        @ Kernel need
    WREG        0x1F201310  0x0007

    WREG        0x1F201318  0x0000        @ Kernel need
    WREG        0x1F201318  0x0003
    WREG        0x1F201320  0x0000        @ Kernel need
    WREG        0x1F201308  0x0000        @ Kernel need

.endm