################################################################################
#
# Copyright (c) 2006-2007 MStar Semiconductor, Inc.
# All rights reserved.
#
# Unless otherwise stipulated in writing, any and all information contained
# herein regardless in any format shall remain the sole proprietary of
# MStar Semiconductor Inc. and be kept in strict confidence
# (¡§MStar Confidential Information¡¨) by the recipient.
# Any unauthorized act including without limitation unauthorized disclosure,
# copying, use, reproduction, sale, distribution, modification, disassembling,
# reverse engineering and compiling of the contents of MStar Confidential
# Information is unlawful and strictly prohibited. MStar hereby reserves the
# rights to any and all damages, losses, costs and expenses resulting therefrom.
#
################################################################################



#include "boot.inc"
#include "macro.inc"
#include "drv_uart.inc"
#include "drv_cache.inc"
#include "drv_pl310.inc"
#include "drv_arm.inc"
#include "Board.h"

#[*] Copy AP from ROM to DRAM
@-------------------------------------------------
@Macro: BOOTRAM_LoadAPRAM
@-------------------------------------------------
.macro BOOTRAM_LoadAPRAM
    LDR     r10, =0x14020000
    LDR     r11, =0x40100000
    LDR     r12, =0x40200000
    LDR     r9,  =0x40100000
    SUB     r12, r12, r9
    MEMCPY32
.endm


.if (SBOOT_TO_KERNEL)
@-------------------------------------------------------------------------------------------------
@ KERNEL_CopyBinary
@ @param  None
@ @return None
@ @note   Copy Kernel binary from ROM to RAM
@-------------------------------------------------------------------------------------------------
.global KERNEL_CopyBinary
KERNEL_CopyBinary:

@src(r10), dst(r11), len(r12) should be 32bit align
@ Load ROM_START, RAM_START, RAM_END
    LDR     r10, =0x14010000
    LDR     r11, =0x43008000
    LDR     r12, =0x00700000
    MEMCPY32
    mov PC,lr
.endif

#-------------------------------------------------------------------------------------------------
# BOOTRAM_Entry:
# @param  None
# @return None
# @note   Entry point of Boot code
#-------------------------------------------------------------------------------------------------
    .globl  BOOTRAM_Entry
BOOTRAM_Entry:
    PUTK '_'

    #if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) || \
    	defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    PUTK    'A'
    PUTK    'U'
    PUTK    'T'
    PUTK    'H'
    PUTK    'E'
    PUTK    'N'
    PUTK    '_'
    PUTK    'O'
    PUTK    'K'
    PUTK   '\n'
    PUTK   '\r'

	.if(ENABLE_MSTAR_BD_MST159A_D01A_S == 1)
    WREG    (MS_BUS_RIU_ADDR + (0x1225FC << 1)), 0x000F   @addr
    RREG    r0, (MS_BUS_RIU_ADDR + (0x1225FE <<1 ))
    bic     r0, r0, #0x1F00
    bic     r0, r0, #0x00FF
    add     r0, r0, #0x0100		@ bit count
    add     r0, r0, #0x001A		@ offset addr
    ldr     r1, =(MS_BUS_RIU_ADDR + (0x1225FE <<1 ))
    str     r0, [r1]
	.endif
	.if(ENABLE_MSTAR_BD_MST036B_EDISON == 1 || ENABLE_MSTAR_BD_MST036B_EDISON_CUS18_ATSC == 1 || ENABLE_MSTAR_BD_MST036B_EDISON_CUS19 == 1)
    WREG    (MS_BUS_RIU_ADDR + (0x1225FC << 1)), 0x102B   @offset addr
    RREG    r0, (MS_BUS_RIU_ADDR + (0x1225FE <<1 ))
    bic     r0, r0, #0x1F00
    bic     r0, r0, #0x00FF
    add     r0, r0, #0x0066		@ offset addr
    @add     r0, r0, #0x0000		@ bit count
    ldr     r1, =(MS_BUS_RIU_ADDR + (0x1225FE <<1 ))
    str     r0, [r1]
	.endif

    drv_arm_fpu_init
    drv_arm_exldr_exstr_enable
    drv_arm_gic_init
    drv_arm_Set_Intr_Core0_1

    @//bl  BootRam_InitMiu1
    #endif

  .if(EMMC_BOOT == 0)
    @clear bss
    ldr     r10, =_ld_bootbss_start
    ldr     r11, =_ld_bootbss_end
    mov     r12, #0
    MEMSET32
  .endif

    # Initialize system stack pointer for unzip subroutine
#ifdef CONFIG_DYNAMIC_RELOCATE 
#    WREG    (MS_BUS_RIU_ADDR + (0x1012d2 << 1)), 0x100  @//Add MIU protect to set read only region from 0x200000 to 0x6000000
#    WREG    (MS_BUS_RIU_ADDR + (0x1012d4 << 1)), 0x3000
#    WREG    (MS_BUS_RIU_ADDR + (0x1012c0 << 1)), 0x0001
    
    RREG    r0, (MS_BUS_RIU_ADDR + (0x0E70 << 1))       @//Select power on mode between Dc_On and Ac_On
    bic     r0, r0, #0x00FF
    ldr     r1, =0xFF00
    cmp     r0, r1
    bne     BootRam_Dc_On
    nop
BootRam_Ac_On:
    ldr     r0, =(CONFIG_RELOCATION_INFO_ADDRESS)       @//Set the dram size from config
    ldr     r1, =(CONFIG_DRAM_SIZE_MB_RELOCATE)
    str     r1, [r0]
BootRam_Dc_On:
    ldr     r0, =(CONFIG_RELOCATION_INFO_ADDRESS)       @//Get the dram size from CONFIG_RELOCATION_INFO_ADDRESS
    ldr     r1, [r0]
    sub	    r1, r1, #1
    mov     r1, r1, lsl #20
    add     r1, r1, #MS_BUS_MIU0_0000M
    mov	    sp, r1
#else
    ldr         r13, =ADDR_STACK_POINTER
#endif

    .if(IS_FPGA == 1)
    PUTK    'F'
    PUTK    'P'
    PUTK    'G'
    PUTK    'A'

    .endif

    .if (SBOOT_TO_KERNEL)
    bl  KERNEL_CopyBinary
    PUTK    '_'
    PUTK    'K'
    PUTK    'E'
    @ab:
    @ldr pc,=ab
    LDR PC,=0x43008000
    .endif


  .if(EMMC_BOOT == 0)
    bl      DoMSDecompression
    PUTK    '_'
  .endif
    @RREG  r0,0x1f006050  @read timer0 to r0
    @RREG  r1,0x1f006054  @read timer0 to r1
    WREG  0x1f006040, 0x0000 @disable timer
BOOT_POINT:
    PUTK 'D'
    # UBoot binary entry
    .if (BOOTING_FROM_EXT_SPI_WITH_PM51 != 1)
        .if (CONFIG_MSTAR_RT_PM_IN_SPI == 1)
            ldr         r0, =0x14030000
        .else
            ldr         r0, =0x14020000
        .endif
    .else
        ldr     r0, =0x14030000
    .endif

    #if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) || \
    	defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    ldr         pc, =CONFIG_UBOOT_LOADADDR
	#else
    ldr         pc, [r0, #16]
	#endif

    PUTK 'b'

    .globl  core1_loop
core1_loop:
    ldr r0,=(CONFIG_KERNEL_START_ADDRESS+0x8000)
    mov r1,#0
    str r1,[r0]
    @WREG 0x1f2067bc, 0x1122  @debug

#if defined(CONFIG_TRUSTZONE_ENABLE)
    ldr     r1, =0x73fff
    mrc     p15, 0, r0, c1, c1, 2
    orr     r0,  r0, r1
    mcr     p15, 0, r0, c1, c1, 2

    /*Set IRQ and local tiemr as Group1 for non secure world usage */
    ldr    r0, =0xA000ffff
    mov    r1, #0x16000000
    add    r1, r1, #0x1080
    str    r0, [r1]

    ldr    r0, =0xf0
    mov    r1, #0x16000000
    add    r1, r1, #0x104
    str    r0, [r1]

    mrc     15, 0, r0, cr1, cr0, 1
    orr     r0, r0, #1
    mcr     15, 0, r0, cr1, cr0, 1


    #mrc  p15, 0, r0, c1, c1, 0
    #orr  r0, #0x1
    #mcr  p15, 0, r0, c1, c1, 0

   #Boot Nuttx


    ldr r0,=(CONFIG_KERNEL_START_ADDRESS+0x8000)
    ldr r1,=0xbbbb
    str r1, [r0]


boot_nuttx:
    ldr r0,=(CONFIG_KERNEL_START_ADDRESS+0x8000)
    ldr r1,[r0]
    ldr r2,=0xaaaa             @check magic number
    cmp r1,r2
 
   bne boot_nuttx

   putk 'x'

   ARM_INIT

   #ldr r0, =Jump_back
   ldr pc, =0x58008000

@Nuttx will never jump back here

#endif

wfi_loop:
    WFI
    @WREG 0x1f2067bc, 0x5EE5  @debug
    ldr r0,=(CONFIG_KERNEL_START_ADDRESS+0x8000)
    ldr r1,[r0]
    ldr r2,=0xbabe             @check magic number
    cmp r1,r2
    @WREG 0x1f2024E8, 0x5567  @debug
    bne wfi_loop
    ldr pc,[r0,#4]

    @RREG r0, 0x1f206744
    @and  r0, #0x3
    @cmp  r0, #0
    @WREG 0x1f2024E8, 0x5567  @debug
    @bne core1_loop   @make sure start address of secondary is legal
    @WREG 0x1f2024E8, 0x3344  @debug
    @RREG r0, 0x1f206740
    @RREG r1, 0x1f206744
    @add r2, r1,r0,lsl #16
    @mov pc, r2

    #ldr   pc,=__secondary_a_core
    @ core1 will not run here
    loop:
    ldr pc, =loop

#-------------------------------------------------------------------------------------------------
# BOOTRAM_Pad
# @param  None
# @return None
# @note   Pad with zeros (Reserve SIZE_BOOTRAM_RESERVED Bytes for bootram)
#-------------------------------------------------------------------------------------------------
    @.org    (SIZE_BOOTRAM_RESERVED-4)
    @.word   0

#if 0
BootRam_InitMiu1:

	mov         r13, lr

    @ MIU1 Software reset
    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )) , 0x0000   @hold miu_0
    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )) , 0x0c01   @
    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )) , 0x0c00   @
    WREG    (MS_BUS_RIU_ADDR + (0x100602 <<1 )) , 0x0000   @

    @ MIU1 Request mask
    WREG    (MS_BUS_RIU_ADDR + (0x100646 <<1 )) , 0x7FFE   @ mask group0
    WREG    (MS_BUS_RIU_ADDR + (0x100666 <<1 )) , 0xFFFF   @ mask group1
    WREG    (MS_BUS_RIU_ADDR + (0x100686 <<1 )) , 0xFFFF   @ mask group2
    WREG    (MS_BUS_RIU_ADDR + (0x1006A6 <<1 )) , 0xFFFF   @ mask group3

    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
    WREG    (MS_BUS_RIU_ADDR + (0x110db6 <<1 )) , 0x4001   @ reg_DDRPLL_LOOP_DIV_FIRST    : [15:14]   divide by 4
    #endif
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
    WREG    (MS_BUS_RIU_ADDR + (0x110db6 <<1 )) , 0x4000   @ reg_DDRPLL_LOOP_DIV_FIRST    : [15:14]   divide by 4
    #endif

    WREG    (MS_BUS_RIU_ADDR + (0x110db4 <<1 )) , 0x0300   @ reg_DDRPLL_LOOP_DIV_SECOND   : [15:14]   divide by 3
    WREG    (MS_BUS_RIU_ADDR + (0x110db0 <<1 )) , 0xeb85   @ set pll to 780 MHz
    WREG    (MS_BUS_RIU_ADDR + (0x110db2 <<1 )) , 0x0019

    @ Avoid DDRPLL unknown(MCLK05X & MCLK025X) by resset ddrat[28]
    WREG    (MS_BUS_RIU_ADDR + (0x110da4 <<1 )) , 0x1000

	DELAYUS 5000    @ delay 5ms

    WREG    (MS_BUS_RIU_ADDR + (0x110da4 <<1 )) , 0x0000

    ldr r0, =HASH2_MIU1_DDR_Init
    bl BootRam_WriteRegTbl32

    DELAYUS 1000    @ delay 1ms

    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )) , 0x0c01   @miu_sw_rst

    DELAYUS 1      @ delay 1us

    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )) , 0x0c08

    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
    WREG    (MS_BUS_RIU_ADDR + (0x110d80 <<1 )) , 0x1e01   @reg_pkg_sel      1   : [0]
    #endif
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
    WREG    (MS_BUS_RIU_ADDR + (0x110d80 <<1 )) , 0x1e02   @reg_pkg_sel      1   : [0]
    #endif

    WREG    (MS_BUS_RIU_ADDR + (0x110d82 <<1 )) , 0xaaaa   @reg_cko_state        cc  : [7:0]
    WREG    (MS_BUS_RIU_ADDR + (0x110d98 <<1 )) , 0x0000
    WREG    (MS_BUS_RIU_ADDR + (0x100602 <<1 )) , 0x03a3
    WREG    (MS_BUS_RIU_ADDR + (0x110dd4 <<1 )) , 0x0000

	DELAYUS  100  @ delay 100us

    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_8BIT_FLYBY)
    WREG    (MS_BUS_RIU_ADDR + (0x110d88 <<1 )) , 0x703f   @reg_rx_en
    #endif
    #if(MIU_CONFIG == DDR3_MIU0_32_MIU1_16_16BIT_TMODE)
    WREG    (MS_BUS_RIU_ADDR + (0x110d88 <<1 )) , 0x003f   @reg_rx_en
    #endif

    @ MIU1 INIT Cycle
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x0000 @ hold miu_0
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x0008 @ DRAM reset
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x000c @ DRAM reset+CS
    DELAYUS 300                                         @ delay 300us
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x000e @ DRAM reset+CS+CKE
    DELAYUS 500                                         @ delay 500us
    WREG    (MS_BUS_RIU_ADDR + (0x100600 <<1 )), 0x001f @ DRAM reset+CS+CKE+auto cycle+ODE
CheckMiu1Init:
    RREG    r0,(MS_BUS_RIU_ADDR + (0x100600 <<1 ))
    lsr     r0, r0, #15
    cmp     r0, #1
    bne     CheckMiu1Init

	DELAYUS 200   @ delay 200us

    @ U04 last down Z switch
    RREG    r0, (MS_BUS_RIU_ADDR + (0x001e02 <<1 ))
    bic     r0, r0, #0x00FF
    lsr     r0, r0, #8
    cmp     r0, #3
    blt     U03_chip_bypass
    nop
    RREG    r0, (MS_BUS_RIU_ADDR + (0x10065E <<1 ))
    orr     r0, r0, #0x0100
    ldr     r1, =(MS_BUS_RIU_ADDR + (0x10065E <<1 ))
    str     r0, [r1]

	WREG    (MS_BUS_RIU_ADDR + (0x100692 <<1 )) , 0xFFFF

    b       Next_Step
    nop

U03_chip_bypass:
    WREG    (MS_BUS_RIU_ADDR + (0x100692 <<1 )) , 0xFFFE   @GE MIU0 and MIU1 last done Z select to 128 arbit

Next_Step:
    @ last_done_z select to last stage
    WREG    (MS_BUS_RIU_ADDR + (0x100652 <<1 )) , 0xFFFF
    WREG    (MS_BUS_RIU_ADDR + (0x100672 <<1 )) , 0xFFFF
    WREG    (MS_BUS_RIU_ADDR + (0x1006B2 <<1 )) , 0xFFFF

	@disable auto DQS for chip bring up
#if !defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH) && \
    !defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)
    WREG    (MS_BUS_RIU_ADDR + (0x100646 <<1 )) , 0x7FFE   @Mask MIU0_group_0
    drv_miu1_autophase
    nop
#endif

	WREG    (MS_BUS_RIU_ADDR + (0x10122A <<1 )) , 0x0000   @Switch MIU0 client 0x0F from SC to BIST
    WREG    (MS_BUS_RIU_ADDR + (0x10062A <<1 )) , 0x0000   @Switch MIU1 client 0x0F from SC to BIST

	@ BIST test
    WREG    (MS_BUS_RIU_ADDR + (0x100646 <<1 )) , 0x7FFE   @Mask MIU0_group_0
    bl          Miu1_BistTest

	WREG    (MS_BUS_RIU_ADDR + (0x1012e0 <<1 )) , 0x0000   @ stop bist test

    @ open all MIU1 request mask (All IP can access MIU resource)
    WREG    (MS_BUS_RIU_ADDR + (0x100646 <<1 )) , 0x0000   @Mask MIU0_group_0
    WREG    (MS_BUS_RIU_ADDR + (0x100666 <<1 )) , 0x0000   @Mask MIU0_group_1
    WREG    (MS_BUS_RIU_ADDR + (0x100686 <<1 )) , 0x0000   @Mask MIU0_group_2
    WREG    (MS_BUS_RIU_ADDR + (0x1006a6 <<1 )) , 0x0000   @Mask MIU0_group_3

    @ all MIU1 IP select MIU0 in bringup
    WREG    (MS_BUS_RIU_ADDR + (0x1006f0 <<1 )), 0x0000
    WREG    (MS_BUS_RIU_ADDR + (0x1006f2 <<1 )), 0x0000
    WREG    (MS_BUS_RIU_ADDR + (0x1006f4 <<1 )), 0x0000
    WREG    (MS_BUS_RIU_ADDR + (0x1006f6 <<1 )), 0x0000

    WREG    (MS_BUS_RIU_ADDR + (0x10061e <<1 )), 0x1808   @ SW initial done and turn on arbitor
    WREG    (MS_BUS_RIU_ADDR + (0x1006fc <<1 )), 0x8400

    RREG     r0, 0x1F202454    @Switch MIU0 client 0x0F from BIST to SC
    orr      r0, r0, #0x4000
    REG_C2M  r0, 0x1F202454

    RREG     r0, 0x1F200C54    @Switch MIU1 client 0x0F from BIST to SC
    orr      r0, r0, #0x4000
    REG_C2M  r0, 0x1F200C54

#if defined(CONFIG_MSTAR_TITANIA_MMAP_32MB_32MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x5000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_64MB_32MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x5000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_64MB_64MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x6000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_128MB_64MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x6000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_128MB_128MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x7000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_128MB_128MB_DEFAULT)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x7000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_256MB_256MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x8000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_512MB_512MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x9000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_512MB_256MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x8000
#elif defined(CONFIG_MSTAR_TITANIA_MMAP_1024MB_512MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x9000
#elif defined(CONFIG_MSTAR_EDISON_MMAP_512MB_256MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x8000
#elif defined(CONFIG_MSTAR_EDISON_MMAP_512MB_512MB)
    WREG    (MS_BUS_RIU_ADDR + (0x1006C0 <<1 )), 0x9000
#else
    #error "Incorrect MMAP setting!!"
#endif

    mov         lr, r13
    bx          lr

@//-------------------------------------------------------------------------------------------------
@// MiuBistTest
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
Miu1_BistTest:
    @//Setup for MIU1 BIST
    PUTK        'B'
    PUTK        'I'
    PUTK        'S'
    PUTK        'T'
    PUTK        '1'
    PUTK        '-'

    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0000   @//1012e0 //reset bist test
    WREG        (MS_BUS_RIU_ADDR + (0x1012f0 << 1)), 0x8000   @//1012f0 bit_15=1 choice to MIU_1
    WREG        (MS_BUS_RIU_ADDR + (0x1012e2 << 1)), 0x0000   @//1012e2 //start address base unit:4 k bytes
    WREG        (MS_BUS_RIU_ADDR + (0x1012e4 << 1)), 0x1001   @//BIST_LEN
    WREG        (MS_BUS_RIU_ADDR + (0x1012e8 << 1)), 0x5aa5   @//1012e8 //bist test pattern

BistTest:
    WREG        (MS_BUS_RIU_ADDR + (0x1012e0 << 1)), 0x0003   @//bist test mode:3

ChkBistMiu0:
    RREG        r1, (MS_BUS_RIU_ADDR + (0x1012e0 << 1))
    and         r0, r1, #0x8000
    cmp         r0, #0
    beq         ChkBistMiu0

    and         r0, r1, #0x6000
    cmp         r0, #0
    beq         BistMiu0_OK

BistMiu0_FAIL:
    PUTK        'F'
    PUTK        'A'
    PUTK        'I'
    PUTK        'L'
    b           BistRet

BistMiu0_OK:
    PUTK        'O'
    PUTK        'K'

BistRet:
    PUTK        '\n'
    PUTK        '\r'

    bx          lr

#endif
