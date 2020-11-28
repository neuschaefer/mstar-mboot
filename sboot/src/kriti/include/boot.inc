################################################################################
#
# Copyright (c) 2006-2011 MStar Semiconductor, Inc.
# All rights reserved.
#
# Unless otherwise stipulated in writing, any and all information contained
# herein regardless in any format shall remain the sole proprietary of
# MStar Semiconductor Inc. and be kept in strict confidence
# ("MStar Confidential Information") by the recipient.
# Any unauthorized act including without limitation unauthorized disclosure,
# copying, use, reproduction, sale, distribution, modification, disassembling,
# reverse engineering and compiling of the contents of MStar Confidential
# Information is unlawful and strictly prohibited. MStar hereby reserves the
# rights to any and all damages, losses, costs and expenses resulting therefrom.
#
################################################################################

#include "boot1.inc"

#-------------------------------------------------------------------------------------------------
# Version
#-------------------------------------------------------------------------------------------------
BOOT_VERSION                    = 0x20110304

#-------------------------------------------------------------------------------------------------
# Build Options
#-------------------------------------------------------------------------------------------------

#define BOOT_FREE               1

#ifdef CONFIG_MSTAR_TITANIA_BD_FPGA
#define FPGA_LINUX_KERNEL_FLASH_ADDRESS     0xb4010000
#define FPGA_LINUX_KERNEL_DRAM_ADDRESS      0xa0400000
#define FPGA_LINUX_KERNEL_ENTRY             0x80404150
#define FPGA_LINUX_KERNEL_SIZE              0x00800000

#endif

#ifndef CONFIG_MIU1_DRAM_NONE
ENABLE_MIU1		                = 1
#else
ENABLE_MIU1		                = 0
#endif

#ifdef CONFIG_BIST_0x0401_UNITS
BIST_LEN                    = 0x0401
#endif

#ifdef CONFIG_BIST_0x1001_UNITS
BIST_LEN                    = 0x1001
#endif

#ifdef CONFIG_BIST_0x8001_UNITS
BIST_LEN                    = 0x8001
#endif

MIPS_OCP_CLOCK_RATIO            = 0x20	        # 0x00: 1:1 / 0x20: 2:1 / 0x40: 3:1

BOOT_DEBUG_VERSION              = 1             # Set for debugging boot code

#//BOOT_COPY_VIA_DMA             = 0             # Set for copying zipped binary from Flash to DRAM via DMA; otherwise via CPU
#//BOOT_PARALLEL_FLASH           = 0             # Set for booting from Parallel Flash; otherwise from Serial Flash

SUPPORT_POWER_SAVING            = 0
#//DYNAMIC_POWER_ON_OFF          = 0

SUPPORT_UNZIP                   = 1             # Set for supporting Unzip (also need to change boot.sh)

# Set DRAM type (exclusive selection)
#//DRAM_TYPE_DDR16_ETRON           = 1             # BD_MST041A / BD_MST041B
#//DRAM_TYPE_SDR16_ESMT            = 0             # BD_MST041D / BD_MST041E
#//DRAM_TYPE_SDR16_ETRON           = 0

#-------------------------------------------------------------------------------------------------
# Addressed in ROM / RAM
#-------------------------------------------------------------------------------------------------
# Start address after boot-up
#ADDR_BOOT_ROM_START             = 0xBFC00000    #0x94000000



# Reserve Bytes for boot code (to avoid recursive defines SIZE_BOOT in boot1.inc)
SIZE_BOOT_RESERVED              = 3072
SIZE_BOOTROM_RESERVED           = 8192
SIZE_BOOTRAM_RESERVED           = 1024
SIZE_BOOTNAND_RESERVED          = 53248         # 52 KB

SIZE_CHUNK_HEADER_RESERVED      = 128           # 16 chunks.

#### Copy UBoot binary from SPI Flash to RAM ###
#SIZE_UBOOT in boot1.c
#ADDR_UBOOT_ROM_START           = (ADDR_BOOT_ROM_START + SIZE_BOOT_RESERVED + SIZE_BOOTROM_RESERVED + SIZE_BOOTRAM_RESERVED + SIZE_BOOTNAND_RESERVED + SIZE_CHUNK_HEADER_RESERVED)
#ADDR_UBOOT_ROM_END             = (ADDR_UBOOT_ROM_START + SIZE_UBOOT) #actually end+1
#ADDR_UBOOT_RAM_START           = (UBOOT_ENTRY_ADDR | 0x20000000)
#ADDR_UBOOT_RAM_START_CACHE     = (ADDR_UBOOT_RAM_START & ~0x20000000 )
#ADDR_UBOOT_RAM_END             = (ADDR_UBOOT_RAM_START + SIZE_UBOOT) #actually end+1
#ADDR_UBOOT_RAM_ENTRY_CACHE     = UBOOT_ENTRY_ADDR    #ToDo: copy general exception handler at OS init instead of linking it to code

### Unzip binary ###
#Initialize system stack pointer for c subroutine
ADDR_STACK_POINTER              = 0x82A80000 #0x80A80000    # Initial stack pointer (downwards)

#-------------------------------------------------------------------------------------------------
# Initialize Regs & Initialize Cache
#-------------------------------------------------------------------------------------------------
M_DebugCOUNTDM                  = (0x01 << 25)

M_StatusCU                      = (0x0f << 28)
M_StatusRP                      = (0x01 << 27)
M_StatusRE                      = (0x01 << 25)
M_StatusBEV                     = (0x01 << 22)
M_StatusTS                      = (0x01 << 21)
M_StatusSR                      = (0x01 << 20)
M_StatusNMI                     = (0x01 << 19)
M_StatusIM7                     = (0x01 << 15)
M_StatusIM2                     = (0x01 << 10)
M_StatusIM                      = (0xff << 8)
M_StatusUM                      = (0x01 << 4)
M_StatusERL                     = (0x01 << 2)
M_StatusEXL                     = (0x01 << 1)
M_StatusIE                      = (0x01 << 0)

M_CauseIV                       = (0x01 << 23)
M_CauseWP                       = (0x01 << 22)
M_CauseIP1                      = (0x01 << 9)
M_CauseIP0                      = (0x01 << 8)

M_ConfigK23                     = (0x07 << 28)
M_ConfigKU                      = (0x07 << 25)
M_ConfigMT                      = (0x07 << 7)
M_ConfigK0                      = (0x07 << 0)
K_CacheAttrCN                   = (0x03 << 0) #Cacheable, noncoherent, write-back, write allocate.
S_Config1IS                     = 22
M_Config1IS                     = (0x07 << S_Config1IS)
S_Config1IL                     = 19
M_Config1IL                     = (0x07 << S_Config1IL)
S_Config1IA                     = 16
M_Config1IA                     = (0x07 << S_Config1IA)
S_Config1DS                     = 13
M_Config1DS                     = (0x07 << S_Config1DS)
S_Config1DL                     = 10
M_Config1DL                     = (0x07 << S_Config1DL)
S_Config1DA                     = 7
M_Config1DA                     = (0x07 << S_Config1DA)

INITIAL_STATUS                  = 0x10400000
INITIAL_CONFIG0                 = 0x00000002 #Uncached

Index_Store_Tag_I               = 0x8
Index_Store_Tag_D               = 0x9
Address_Fill_I                  = 0x14
#A_DSPRAM                       = 0x04000000        # 0x84000000
A_KSEG0BASE                     = 0x80000000

# alan.chen adds start

CONFIG0_MIPS32_64_MSK           = 0x8000ffff
STATUS_MIPS32_64_MSK            = 0xfffcffff

S_ConfigMM                      = 18     /* 24K specific, merging enable/disable */
M_ConfigMM                      = (0x1 << S_ConfigMM)

K_CacheAttrCN                   = 3

STATUS_MIPS34K	                = 0

# alan.chen adds end

#-------------------------------------------------------------------------------------------------
# UART Register
#-------------------------------------------------------------------------------------------------
UART_RX                         = (0 * 4)       # In:  Receive buffer (DLAB=0)    (16-byte FIFO)
UART_TX                         = (0 * 4)       # Out: Transmit buffer (DLAB=0)   (16-byte FIFO)
UART_DLL                        = (0 * 4)       # Out: Divisor Latch Low (DLAB=1)
UART_DLM                        = (1 * 4)       # Out: Divisor Latch High (DLAB=1)
UART_IER                        = (1 * 4)       # Out: Interrupt Enable Register
UART_IIR                        = (2 * 4)       # In:  Interrupt ID Register
UART_FCR                        = (2 * 4)       # Out: FIFO Control Register
UART_LCR                        = (3 * 4)       # Out: Line Control Register
UART_MCR                        = (4 * 4)       # Out: Modem Control Register
UART_LSR                        = (5 * 4)       # In:  Line Status Register
UART_MSR                        = (6 * 4)       # In:  Modem Status Register
UART_SCR                        = (7 * 4)       # I/O: Scratch Register
#-------------------------------------------------------------------------------------------------
# FIFO Control Register
#-------------------------------------------------------------------------------------------------
UART_FCR_ENABLE_FIFO            = 0x01          # Enable the FIFO
UART_FCR_CLEAR_RCVR             = 0x02          # Clear the RCVR FIFO
UART_FCR_CLEAR_XMIT             = 0x04          # Clear the XMIT FIFO
UART_FCR_DMA_SELECT             = 0x08          # For DMA applications
UART_FCR_TRIGGER_MASK           = 0xC0          # Mask for the FIFO trigger range
UART_FCR_TRIGGER_1              = 0x00          # Mask for trigger set at 1
UART_FCR_TRIGGER_4              = 0x40          # Mask for trigger set at 4
UART_FCR_TRIGGER_8              = 0x80          # Mask for trigger set at 8
UART_FCR_TRIGGER_14             = 0xC0          # Mask for trigger set at 14

#-------------------------------------------------------------------------------------------------
# Flash registers
#-------------------------------------------------------------------------------------------------
#REG_ISP_CLK_SRC                = (0xBF800000 + 0x1E26*4)
#REG_SFSH_PIU_BASE              = 0xBF207800
#REG_SFSH_DMA_STATE             = (REG_SFSH_PIU_BASE + 0x10*4) #[1]done [2]busy [8:15]state
#REG_SFSH_DMA_SPISTART_L        = (REG_SFSH_PIU_BASE + 0x70*4) #[15:0]
#REG_SFSH_DMA_SPISTART_H        = (REG_SFSH_PIU_BASE + 0x71*4) #[23:16]
#REG_SFSH_DMA_DRAMSTART_L       = (REG_SFSH_PIU_BASE + 0x72*4) #[15:0]  in unit of B; must be 8B aligned
#REG_SFSH_DMA_DRAMSTART_H       = (REG_SFSH_PIU_BASE + 0x73*4) #[23:16]
#REG_SFSH_DMA_SIZE_L            = (REG_SFSH_PIU_BASE + 0x74*4) #[15:0]  in unit of B; must be 8B aligned
#REG_SFSH_DMA_SIZE_H            = (REG_SFSH_PIU_BASE + 0x75*4) #[23:16]
#REG_SFSH_DMA_CMD               = (REG_SFSH_PIU_BASE + 0x76*4)
#SFSH_DMA_ALIGN                 = 8

#-------------------------------------------------------------------------------------------------
# Other registers
#-------------------------------------------------------------------------------------------------
REG_TOP_POWER_STATUS            = 0xbf203cdc

#-------------------------------------------------------------------------------------------------
# MIU registers
#-------------------------------------------------------------------------------------------------
MIU0_BASE                       = 0xBF202400
MIU1_BASE                       = 0xBF200C00

MIU0_ATOP_BASE                  = 0xBF221A00
MIU1_ATOP_BASE                  = 0xBF221B00   # alan : need to update

CLK_GEN0_BASE                   = 0xBF201600
CLK_GEN1_BASE                   = 0xBF206600

ADC_ATOP_BASE                   = 0xBF204A00
ADC_DTOP_BASE                   = 0xBF204C00
DVI_DTOP_BASE                   = 0xBF204424
#DVI_ATOP_BASE                  = 0xBF204A00
DVI_ATOP_BASE                   = 0xBF221200

CHIP_TOP_BASE                   = 0xBF203C00
ANA_MISC_BASE                   = 0xBF221800

USB0_BASE                       = 0xBF200E00
USB1_BASE                       = 0xBF220400

UTMI1_BASE                      = 0xBF205400
UTMI0_BASE                      = 0xBF207500

SC1_BASE                        = 0xBF205E00
SC3_BASE                        = 0xBF206200
SC4_BASE                        = 0xBF206400

AFEC_BASE                       = 0xBF206A00

#-------------------------------------------------------------------------------------------------
# registers
#-------------------------------------------------------------------------------------------------
PM_BASE                         = 0xBF001C00
MAU_BASE                        = 0xBF001D00

#-------------------------------------------------------------------------------------------------
# UART registers
#-------------------------------------------------------------------------------------------------
UART_BASE                       = 0xBF201300
UART_LCR_DLAB                   = 0x80    # Divisor latch access bit
UART_LCR_SBC                    = 0x40    # Set break control
UART_LCR_SPAR                   = 0x20    # Stick parity (?)
UART_LCR_EPAR                   = 0x10    # Even parity select
UART_LCR_PARITY                 = 0x08    # Parity Enable
UART_LCR_STOP1                  = 0x00    # Stop bits: 0=1 stop bit, 1= 2 stop bits
UART_LCR_STOP2                  = 0x04    # Stop bits: 0=1 stop bit, 1= 2 stop bits
UART_LCR_WLEN5                  = 0x00    # Wordlength: 5 bits
UART_LCR_WLEN6                  = 0x01    # Wordlength: 6 bits
UART_LCR_WLEN7                  = 0x02    # Wordlength: 7 bits
UART_LCR_WLEN8                  = 0x03    # Wordlength: 8 bits

#ifdef CONFIG_MSTAR_KRITI_BD_FPGA
UART_BAUD_RATE              = 38400
UART_CLK_FREQ               = 12000000
#else
#Baud rate
UART_BAUD_RATE	                = 115200
#Clock source
UART_CLK_FREQ           = 123000000
#endif

#CPU clock
CPU_CLOCK_FREQ          = (CPU_CLOCK * 1000000)


#Divisor
UART_DIVISOR                    = (UART_CLK_FREQ / (16 * UART_BAUD_RATE))

UART_DIVISOR_H                  = (UART_DIVISOR >> 8)
UART_DIVISOR_L                  = (UART_DIVISOR & 0xff)

#-------------------------------------------------------------------------------------------------
# L2 cache setup
#-------------------------------------------------------------------------------------------------
#if defined(CONFIG_MSTAR_TITANIA_L2_CACHE_LINE_32_BYTES)
L2_CACHE_LINE_SIZE              = 32
#elif defined(CONFIG_MSTAR_TITANIA_L2_CACHE_LINE_64_BYTES)
L2_CACHE_LINE_SIZE              = 64
#else
L2_CACHE_LINE_SIZE              = 64
#endif

#-------------------------------------------------------------------------------------------------
# Init setup
#-------------------------------------------------------------------------------------------------
### UART 0 = 1: enable UART 0  Disable UART 2
### UART 0 = 0: enable UART 2  Disable UART 0
BOOTINFO_UART0_ENABLE           = 1
#if defined(CONFIG_UART1_SEL)
BOOTINFO_UART1_ENABLE           = 1
#else
BOOTINFO_UART1_ENABLE           = 0
#endif
BOOTINFO_UART2_ENABLE           = 0
BOOTINFO_UART3_ENABLE           = 0

#---------------------------------------------------------------------------------------------------------
# Parameters for "sboot to kernel"
#---------------------------------------------------------------------------------------------------------
.if(SBOOT_TO_KERNEL)
ADDR_BIN_ROM_START          = 0xb4010000
ADDR_BIN_RAM_START          = (ADDR_BIN_RAM_START_CACHE | 0xa0000000) //transfer to non-cached address
ADDR_BIN_RAM_END            = (ADDR_BIN_RAM_START + SIZE_KERNEL )
KERNEL_ENTRY                = (KERNEL_ENTRY_CACHE)
.endif

#-------------------------------------------------------------------------------------------------
# Macros
#-------------------------------------------------------------------------------------------------
# --------------------------------------------------------------
# MACRO NAME 	: 	W1B_REG
# PARAMETERS 	:	base, RIU register base address
# PARAMETERS 	:	index, RIU register index
# PARAMETERS 	:	value, value
# INTERNAL REGS	: $8, $9
# RETURN     	:  none
# --------------------------------------------------------------
.macro W1B_REG base, index, value
    # $8 and $9 = BYTE2REAL(B)            (((B)>>1<<2)+((B)&0x01)
    li      $8, \index
    li	    $9, \base
    add 	$8, $8, $9
    move    $9, $8

    # $8 = ((B)>>1<<2)
    srl	    $8, $8, 1
    sll	    $8, $8, 2

    # $9 = (B)&0x01
    andi	$9, $9, 1

    # $8 = BYTE2REAL(B)
    add 	$8, $8, $9

    # set value to RIU
    # $9 is the result of RIU base (0xBF000000) + BYTE2REAL(base+index)
    li	    $9, 0xBF000000
    add	    $9, $9, $8
    # $8 is the value
    li      $8, (\value & 0xFF)
    sb      $8, 0($9)
.endm

# --------------------------------------------------------------
# MACRO NAME 	: 	W1BC_REG
# PARAMETERS 	:	base, RIU register base address
# PARAMETERS 	:	index, RIU register index
# PARAMETERS 	:	bit_inx, clear bits
# INTERNAL REGS	: $8, $9, $10
# RETURN     	:  none
# --------------------------------------------------------------
.macro W1BC_REG base, index, bit_inx
    li      $8, \index
    li	    $9, \base
    add 	$8, $8, $9
    move    $9, $8

    srl	    $8, $8, 1
    sll	    $8, $8, 2

    andi	$9, $9, 1
    add 	$8, $8, $9

    # set value to RIU
    # $9 is the result of RIU base (0xBF000000) + BYTE2REAL(base+index)
    li	    $9, 0xBF000000
    add	    $9, $9, $8

    # $8 is the origial value of RIU register
    lb      $8, 0($9)

    # load bit inx to $10 and not it.
    li      $10, \bit_inx
    not     $10, $10
    and	    $8, $8, $10

    # store to RIU
    sb      $8, 0($9)
.endm

# --------------------------------------------------------------
# MACRO NAME 	: 	W1BS_REG
# PARAMETERS 	:	base, RIU register base address
# PARAMETERS 	:	index, RIU register index
# PARAMETERS 	:	bit_inx, set bits
# INTERNAL REGS	: $8, $9
# RETURN     	:  none
# --------------------------------------------------------------
.macro W1BS_REG base, index, bit_inx
    # this macro use 2 temp registers $8, $9
    # $8 is the result of BYTE2REAL(base+index)
    li      $8, \index
    li	    $9, \base
    add 	$8, $8, $9
    move    $9, $8

    srl	    $8, $8, 1
    sll	    $8, $8, 2

    andi	$9, $9, 1
    add 	$8, $8, $9

    # set value to RIU
    # $9 is the result of RIU base (0xBF000000) + BYTE2REAL(base+index)
    li	    $9, 0xBF000000
    add	    $9, $9, $8

    # $8 is the origial value of RIU register
    lb      $8, 0($9)
    ori     $8, $8, \bit_inx

    # store to RIU
    sb      $8, 0($9)
.endm

#-------------------------------------------------------------------------------------------------
# Macros
#-------------------------------------------------------------------------------------------------
#ifndef _macro_wreg_l_
.macro WREG_L reg, value
    lui     $8, \reg >> 16
    li      $9, (\value & 0xFF)
    sb      $9, (\reg & 0xFFFF)($8)
.endm
#define	_macro_wreg_l_
#endif

#ifndef _macro_wreg_h_
.macro WREG_H reg, value
    lui     $8, \reg >> 16
    li      $9, (\value & 0xFF)
    sb      $9, ((\reg + 2) & 0xFFFF)($8)
.endm
#define	_macro_wreg_h_
#endif

#ifndef _macro_wreg_b_
.macro WREG_B reg, value
    lui     $8, \reg >> 16
    li      $9, \value
    sb      $9, (\reg & 0xFFFF)($8)
.endm
#define	_macro_wreg_b_
#endif

#ifndef _macro_wreg_
.macro WREG reg, value
    lui     $8, \reg >> 16
    li      $9, \value
    sw      $9, (\reg & 0xFFFF)($8)
.endm
#define	_macro_wreg_
#endif

#ifndef	_macro_lwreg_
.macro LWREG reg, value
    li      $9, \value
    sw      $9, (\reg & 0xFFFF)($8)
.endm
#define	_macro_lwreg_
#endif


#ifndef	_macro_wreg_d_
.macro WREG_D reg, value
    lui     $8, \reg >> 16
    li      $9, \value >> 16
    sw      $9, ((\reg & 0xFFFF)+4 )($8)
    li      $9, \value
    sw      $9, (\reg & 0xFFFF)($8)
.endm
#define	_macro_wreg_d_
#endif

#ifndef	_macro_dbgreg_
.macro DBGREG value
    WREG    0xBF206700, \value
.endm
#define	_macro_dbgreg_
#endif

#ifndef _macro_while_
.macro WHILE1
while:
    li      $9, 0x0
    beqz    $9, while
    nop
.endm
#endif

#.macro DELAYUS us
#   li      $10, \us * (CPU_CLOCK_FREQ/2/1000000) #ticks
#   mfc0    $26, $9      #tick1
#1:
#   mfc0    $9, $9      #tick2
#   subu    $11, $9, $26 #tick2-tick1
#   blt     $11, $10, 1b
#   nop
#.endm

#ifndef	_macro_delayus_
.macro DELAYUS us
lui     $8, %hi(0xBF006048)
li      $9, (\us*12) & 0x0000FFFF
sw      $9, %lo(0xBF006048)($8)
lui     $8, %hi(0xBF00604C)
li      $9, (\us*12) >> 16
sw      $9, %lo(0xBF00604C)($8)
lui     $8, %hi(0xBF006040)
lw      $9, %lo(0xBF006040)($8)
ori     $9, $9, 0x00000002
sw      $9, %lo(0xBF006040)($8)
DELAYUS_\@:
lui     $8, %hi(0xBF006044)
lw      $9, %lo(0xBF006044)($8)
andi    $9, 0x00000001
beqz    $9, DELAYUS_\@
    nop
.endm
#define	_macro_delayus_
#endif

#ifndef	_macro_rreg_
.macro RREG reg_d, reg
    lui     $8, \reg >> 16
    lw      \reg_d, (\reg & 0xFFFF)($8)
.endm
#define	_macro_rreg_
#endif

#ifndef	_macro_lrreg_
.macro LRREG reg_d, reg
    lw      \reg_d, (\reg & 0xFFFF)($8)
.endm
#define	_macro_lrreg_
#endif

#ifndef	_macro_sssw_
.macro SSSW reg, value
    lui     $8, \reg >> 16
    sw      \value, (\reg & 0xFFFF)($8)
.endm
#define	_macro_sssw_
#endif

#ifndef	_macro_lsssw_
.macro LSSSW reg, value
    sw      \value, (\reg & 0xFFFF)($8)
.endm
#define	_macro_lsssw_
#endif

#ifndef	_macro_putcw_
.macro PUTCW char
    W1B_REG 0x980, 0x0, \char
PUTC_\@:

    li      $8, 0xBF201328
    lw      $8, 0($8)
    andi    $8, $8, 0x60
    li      $9, 0x60
    bne     $8, $9, PUTC_\@
    nop
.endm
#define	_macro_putcw_
#endif

#ifndef	_macro_putc_
.macro PUTC char
    lui     $27, 0
    ori	    $27, $27, \char
    SSSW    0xBF201300, $27
.endm
#define	_macro_putc_
#endif

#ifndef	_macro_putk_
.macro PUTK char
    lui     $9, 0
    ori	    $9, $9, \char
    SSSW    0xBF201300, $9
.endm
#endif

#ifndef	_macro_reg_c2m_
.macro REG_C2M cpu_reg, mstar_reg
lui     $8, \mstar_reg >> 16
sw      \cpu_reg, (\mstar_reg & 0xFFFF)($8)
.endm
#endif

#-------------------------------------------------
#Macro: TIMER HEAD (for rum time mesurement)
#-------------------------------------------------
.macro TIMER_HEAD
    WREG    0xBF006080, 0x0000
    WREG    0xBF006088, 0xFFFF
    WREG    0xBF00608C, 0xFFFF
    WREG    0xBF006080, 0x0001
.endm

#-------------------------------------------------
#Macro: TIMER_TAIL (for rum time mesurement)
#-------------------------------------------------
.macro TIMER_TAIL
    RREG    $9, 0xBF006090
    REG_C2M $9, 0xBF006088
    RREG    $9, 0xBF006094
    REG_C2M $9, 0xBF00608C
.endm

#define KUSEG_MSK		        0x80000000
#define KSEG_MSK		        0xE0000000
#define KUSEGBASE		        0x00000000
#define KSEG0BASE		        0x80000000
#define KSEG1BASE		        0xA0000000
#define KSSEGBASE		        0xC0000000
#define KSEG3BASE		        0xE0000000


#define KSEG0A(reg) 	        and reg, ~KSEG_MSK; or reg, KSEG0BASE

#define SSNOP                   sll zero, zero, 1
#define EHB                     sll zero, zero, 3
#define NOPS	                SSNOP; SSNOP; SSNOP; EHB


#define MFC0(dst, src)      \
	  	mfc0 dst,src



#define MTC0(src, dst)      \
		nop;	            \
        mtc0 src,dst;       \
		NOPS


#define CFC1(dst, src)      \
		nop;	            \
        cfc1 dst, src;      \
		NOPS

#define CTC1(src, dest)     \
		nop;	            \
        ctc1 src, dest;     \
		NOPS

#define DISP_STR( s )

#define LEAF(name)          \
  		.##text;            \
  		.##globl    name;   \
  		.##ent      name;   \
name:

#define END(name)\
  		.##size name,.-name;\
  		.##end	name

#define MFC0_SEL_OPCODE(dst, src, sel)  \
	  	.##word (0x40000000 | ((dst)<<16) | ((src)<<11) | (sel))

#define MTC0_SEL_OPCODE(src, dst, sel)  \
	  	.##word (0x40800000 | ((src)<<16) | ((dst)<<11) | (sel));   \
		NOPS

#define SET_MIPS3()                             .##set mips3
#define SET_MIPS0()                             .##set mips0
#define SET_PUSH()                              .##set push
#define SET_POP()                               .##set pop

/* cache operations */

#define CACHE_OP( code, type )			        (((code) << 2) | (type))

#define ICACHE_INDEX_INVALIDATE			        CACHE_OP(0x0, 0)
#define ICACHE_INDEX_LOAD_TAG			        CACHE_OP(0x1, 0)
#define ICACHE_INDEX_STORE_TAG			        CACHE_OP(0x2, 0)
#define DCACHE_INDEX_WRITEBACK_INVALIDATE	    CACHE_OP(0x0, 1)
#define DCACHE_INDEX_LOAD_TAG			        CACHE_OP(0x1, 1)
#define DCACHE_INDEX_STORE_TAG			        CACHE_OP(0x2, 1)
#define SCACHE_INDEX_WRITEBACK_INVALIDATE	    CACHE_OP(0x0, 3)
#define SCACHE_INDEX_STORE_TAG			        CACHE_OP(0x2, 3)

#define ICACHE_ADDR_HIT_INVALIDATE		        CACHE_OP(0x4, 0)
#define ICACHE_ADDR_FILL			            CACHE_OP(0x5, 0)
#define ICACHE_ADDR_FETCH_LOCK			        CACHE_OP(0x7, 0)
#define DCACHE_ADDR_HIT_INVALIDATE		        CACHE_OP(0x4, 1)
#define DCACHE_ADDR_HIT_WRITEBACK_INVALIDATE	CACHE_OP(0x5, 1)
#define DCACHE_ADDR_HIT_WRITEBACK		        CACHE_OP(0x6, 1)
#define DCACHE_ADDR_FETCH_LOCK			        CACHE_OP(0x7, 1)

#define SCACHE_ADDR_HIT_WRITEBACK_INVALIDATE	CACHE_OP(0x5, 3)





