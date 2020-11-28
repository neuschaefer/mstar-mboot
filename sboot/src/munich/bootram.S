/*
 *#############################################################################
 *
 * Copyright (c) 2006-2013 MStar Semiconductor, Inc.
 * All rights reserved.
 *
 * Unless otherwise stipulated in writing, any and all information contained
 * herein regardless in any format shall remain the sole proprietary of
 * MStar Semiconductor Inc. and be kept in strict confidence
 * (¡§MStar Confidential Information¡¨) by the recipient.
 * Any unauthorized act including without limitation unauthorized disclosure,
 * copying, use, reproduction, sale, distribution, modification, disassembling,
 * reverse engineering and compiling of the contents of MStar Confidential
 * Information is unlawful and strictly prohibited. MStar hereby reserves the
 * rights to any and all damages, losses, costs and expenses resulting therefrom.
 *
 *#############################################################################
 */

#ifndef _BOOT_INC_
#include "boot.inc"
#endif

#if defined(CONFIG_SBOOT_TO_KERNEL) && defined(CONFIG_MSTAR_TITANIA_BD_FPGA)
#define LINUX_KERNEL_FLASH_ADDRESS  0x14010000
#define LINUX_KERNEL_DRAM_ADDRESS   0x20208000
#define LINUX_KERNEL_ENTRY          0x20208000
#define LINUX_KERNEL_SIZE           0x00800000
#elif defined(CONFIG_MSTAR_TITANIA_BD_FPGA)
#define LINUX_KERNEL_FLASH_ADDRESS  0x14020000
#define LINUX_KERNEL_DRAM_ADDRESS   0x20400000
#define LINUX_KERNEL_ENTRY          0x20408000
#define LINUX_KERNEL_SIZE           0x00200000
#elif defined(CONFIG_SBOOT_TO_KERNEL)
#define LINUX_KERNEL_FLASH_ADDRESS  0x14010000
#define LINUX_KERNEL_DRAM_ADDRESS   0x20208000
#define LINUX_KERNEL_ENTRY          0x20208000
#define LINUX_KERNEL_SIZE           0x003a0000
#endif

@//-------------------------------------------------------------------------------------------------
@// BOOTRAM_Entry:
@// @param  None
@// @return None
@// @note   Entry point of Boot code
@//-------------------------------------------------------------------------------------------------
    .globl      BOOTRAM_Entry

BOOTRAM_Entry:

    DPUTK       '_'

    @//Configure PAD top for MUX and GPIO (e.g. DDR power)
    ldr         r0, =padInitTbl
    add         r0, r0, #10
    bl          MDrv_WriteRegMaskTbl

    @//Initial EMAC Trimming Control Setting
    bl          BootRom_InitEmacTrimmingControl
#ifdef CONFIG_MSTAR_EDINBURGH
    bl          BootRom_InitExtDemod
#endif

#ifdef CONFIG_MSTAR_CASHMERE
    bl          BootRom_InitExtDemod_Cashmere
#endif
@//================================================================================================
#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) || \
    defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)

    ldr         r0, =Bootram_SecondaryCore
    ldr         r1, =0xFFFF
    mov         r2, r0, lsr #16
    and         r2, r2, r1
    REG_C2M     r2, BOOT_INFO_REGISTER_CORE1_START_ADDR_HIGH

    and         r2, r0, r1
    REG_C2M     r2, BOOT_INFO_REGISTER_CORE1_START_ADDR_LOW

#endif

@//================================================================================================
    @//Initial Global Interrupt Interface
    WREG        (REG_GIC_CPU_BASE_ADDRESS + 0x0004), 0x000000f0
    WREG        (REG_GIC_DIST_BASE_ADDRESS + 0x0180), 0xffff0000
    WREG        (REG_GIC_DIST_BASE_ADDRESS + 0x0100), 0x0000ffff
    WREG        (REG_GIC_CPU_BASE_ADDRESS + 0x0000), 0x00000001

    @//Initial Internal Interrupt Controller
    WREG        (REG_GIC_DIST_BASE_ADDRESS + 0x0F00), 0x000e0001
    WREG        (REG_GIC_DIST_BASE_ADDRESS + 0x0000), 0x00000001

@//================================================================================================
@// Clear data in BSS section
    ldr         r0, =_ld_bootbss_start
    ldr         r1, =_ld_bootbss_end
    mov         r2, #0

    cmp         r0, r1
    beq         _ClearBssExit

_ClearBssLoop:
    cmp         r0, r1
    str         r2, [r0], #0x04
    bne         _ClearBssLoop

_ClearBssExit:

@//================================================================================================
@// Initialize system stack pointer for unzip subroutine

#ifdef CONFIG_DYNAMIC_RELOCATE 
#    WREG        (MS_BUS_RIU_ADDR + (0x1012c0 << 1)), 0x100  @//Add MIU protect to set read only region from 0x200000 to 0x6000000
#    WREG        (MS_BUS_RIU_ADDR + (0x1012c2 << 1)), 0x7000
#    WREG        (MS_BUS_RIU_ADDR + (0x1012d2 << 1)), 0x0001
    
    RREG    r0, (MS_BUS_RIU_ADDR + (0x0E70 << 1))           @//Select power on mode between Dc_On and Ac_On
    bic     r0, r0, #0x00FF
    ldr     r1, =0xFF00
    cmp     r0, r1
    bne     BootRam_Dc_On
    nop
BootRam_Ac_On:
    ldr     r0, =(CONFIG_RELOCATION_INFO_ADDRESS)           @//Set the dram size from config
    ldr     r1, =(CONFIG_DRAM_SIZE_MB_RELOCATE)
    str     r1, [r0]
BootRam_Dc_On:
    ldr     r0, =(CONFIG_RELOCATION_INFO_ADDRESS)           @//Get the dram size from CONFIG_RELOCATION_INFO_ADDRESS
    ldr     r1, [r0]
    sub	    r1, r1, #1
    mov     r1, r1, lsl #20
    add     r1, r1, #MS_BUS_MIU0_0000M
    mov	    sp, r1
#else
    ldr         r13, =ADDR_STACK_POINTER
#endif
#ifdef CONFIG_MSTAR_STR_MINISIZE
    ldr         r13, =CONFIG_KERNEL_START_ADDRESS
#endif

#if defined(CONFIG_MSTAR_TITANIA_BD_FPGA) || defined(CONFIG_SBOOT_TO_KERNEL)
@//================================================================================================
@//Copy Image to DRAM

    ldr         r0, =LINUX_KERNEL_FLASH_ADDRESS     @//Starting Address of Linux Kernel in SPI Flash
    ldr         r1, =LINUX_KERNEL_DRAM_ADDRESS      @//Dest Address of Linux Kernel in DRAM
    ldr         r2, =LINUX_KERNEL_SIZE              @//Image Size of Linux Kernel

#if defined(CONFIG_SBOOT_TO_KERNEL)
_CopyImageLoop:

    LDMIA       r0!, {r3 - r10}
    STMIA       r1!, {r3 - r10}
    SUBS        r2, r2, #32
    bge         _CopyImageLoop

#else
_CopyImageLoop:

    ldr         r3, [r0], #0x04
    str         r3, [r1], #0x04

    subs        r2, r2, #0x04

    ldr         r3, =0x0007FFFF
    and         r4, r2, r3
    cmp         r4, #0
    bgt         _CopyImageLoop

    PUTK        '#'

    cmp         r2, #0
    bgt         _CopyImageLoop
#endif

@//================================================================================================
@//Jump to Kernel Entry of Linux

    PUTK        '\n'
    PUTK        '\r'

    ldr         pc, =LINUX_KERNEL_ENTRY

#endif

@//================================================================================================
#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)
    @//LOAD CHUNK HEADER
    ldr         r0, =CONFIG_UBOOT_LOADADDR
    ldr         r1, =0x400
    bl          drvNAND_LoaduBoot

#if defined(CONFIG_MSTAR_AUTHEN_ENABLE) && defined(CONFIG_SECURITY_BOOT)
	RREG        r0, (MS_BUS_RIU_ADDR + (0x0038E0 << 1)) @//check ROM authentication
	ldr         r1, =0x0001
    and         r0, r0, r1
    cmp         r0, r1
    bne         BootRam_AuthChunkHeader_Exit

	@//Authenticate CHUNK HEADER
	ldr         r0, =CONFIG_UBOOT_LOADADDR
	ldr         r1, =0x2F0
	ldr         r2, =CONFIG_UBOOT_LOADADDR + 0x300
	ldr         r3, =0x0
	bl          MDrv_AESDMA_SecureMain

	@//If authentication fail, jump to reset whole system
    cmp         r0, #1
    bne         BootRam_AuthenticationFail

BootRam_AuthChunkHeader_Exit:
#endif

    @// LOAD UBOOT
    ldr         r0, =CONFIG_UBOOT_LOADADDR
    ldr         r3, [r0, #0]    @// UBOOT_ROM_START in MBOOT PARTITION
    ldr         r1, [r0, #4]    @// UBOOT_RAM_START
    ldr         r2, [r0, #8]    @// UBOOT_RAM_END
    ldr         r5, [r0, #4]    @// UBOOT_RAM_START
    ldr         r6, [r0, #8]    @// UBOOT_RAM_END
    sub         r1, r2, r1      @// UBOOT_SIZE = UBOOT_RAM_END - UBOOT_RAM_START
    add         r1, r1, r3      @// LOAD SIZE
    sub         r0, r0, r3
    bl          drvNAND_LoaduBoot

#if defined(CONFIG_MSTAR_AUTHEN_ENABLE) && defined(CONFIG_SECURITY_BOOT)
	RREG        r0, (MS_BUS_RIU_ADDR + (0x0038E0 << 1)) @//check ROM authentication
	ldr         r1, =0x0001
    and         r0, r0, r1
    cmp         r0, r1
    bne         BootRam_AuthUBoot_Exit

    @//Authenticate U-BOOT
	ldr         r0, =CONFIG_UBOOT_LOADADDR
	sub         r1, r6, r5
	ldr         r2, =CONFIG_UBOOT_LOADADDR + 0x10
	add         r2, r2, r1
	ldr         r3, =0x0
	bl          MDrv_AESDMA_SecureMain

	@//If authentication fail, jump to reset whole system
    cmp         r0, #1
    bne         BootRam_AuthenticationFail

BootRam_AuthUBoot_Exit:
#endif

#elif defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    @//LOAD CHUNK HEADER
    ldr         r0, =CONFIG_UBOOT_LOADADDR
    ldr         r1, =0x400
    ldr         r2, =0x1000
    bl          eMMC_ReadData_MIU

#if defined(CONFIG_MSTAR_AUTHEN_ENABLE) && defined(CONFIG_SECURITY_BOOT)
	RREG        r0, (MS_BUS_RIU_ADDR + (0x0038E0 << 1)) @//check ROM authentication
	ldr         r1, =0x0001
    and         r0, r0, r1
    cmp         r0, r1
    bne         BootRam_AuthChunkHeader_Exit

	@//Authenticate CHUNK HEADER
	ldr         r0, =CONFIG_UBOOT_LOADADDR
	ldr         r1, =0x2F0
	ldr         r2, =CONFIG_UBOOT_LOADADDR + 0x300
	ldr         r3, =0x0
	bl          MDrv_AESDMA_SecureMain

	@//If authentication fail, jump to reset whole system
    cmp         r0, #1
    bne         BootRam_AuthenticationFail

BootRam_AuthChunkHeader_Exit:
#endif
    @// LOAD UBOOT
    ldr         r0, =CONFIG_UBOOT_LOADADDR
    ldr         r5, [r0, #4]    @// UBOOT_RAM_START
    ldr         r6, [r0, #8]    @// UBOOT_RAM_END
    sub         r1, r6 , r5
    add         r1, r1 , #0x110  @// SECURITY INFO Size 0x110
    ldr         r2, =0x1002
    bl          eMMC_ReadData_MIU

#if defined(CONFIG_MSTAR_AUTHEN_ENABLE) && defined(CONFIG_SECURITY_BOOT)
	RREG        r0, (MS_BUS_RIU_ADDR + (0x0038E0 << 1)) @//check ROM authentication
	ldr         r1, =0x0001
    and         r0, r0, r1
    cmp         r0, r1
    bne         BootRam_AuthUBoot_Exit

    @//Authenticate U-BOOT
	ldr         r0, =CONFIG_UBOOT_LOADADDR
	sub         r1, r6, r5
	ldr         r2, =CONFIG_UBOOT_LOADADDR + 0x10
	add         r2, r2, r1
	ldr         r3, =0x0
	bl          MDrv_AESDMA_SecureMain

	@//If authentication fail, jump to reset whole system
    cmp         r0, #1
    bne         BootRam_AuthenticationFail

BootRam_AuthUBoot_Exit:
#endif
#else
   
    bl          DoMSDecompression

#endif

@//================================================================================================
BOOT_POINT:

    DPUTK       'U'

    WREG        0x1f006040, 0x0000          @//Disable Hardware Timer 1

#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) || \
    defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH) || \
    defined(CONFIG_BOOTING_FROM_EXT_EMMC_WITH_CPU)
    ldr         pc, =CONFIG_UBOOT_LOADADDR
#else

#ifndef CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51
#ifdef CONFIG_MSTAR_RT_PM_IN_SPI
    ldr         r0, =0x14030000
#else
    ldr         r0, =0x14020000
#endif
#else
    ldr         r0, =0x14030000
#endif

    ldr         pc, [r0, #16]
#endif

#if defined(CONFIG_TRUSTZONE_ENABLE)
@//================================================================================================
    .globl      Bootram_Secure_Core
Bootram_Secure_Core:
    ldr     r1, =0x73fff
    mrc     p15, 0, r0, c1, c1, 2
    orr     r0,  r0, r1
    mcr     p15, 0, r0, c1, c1, 2
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

    ldr r0,=(CONFIG_KERNEL_START_ADDRESS+0x8000)
    ldr r1,=0xbbbb
    str r1, [r0]

boot_nuttx:
    ldr r0,=(CONFIG_KERNEL_START_ADDRESS+0x8000)
    ldr r1,[r0]
    ldr r2,=0xaaaa             @check magic number
    cmp r1,r2
    bne boot_nuttx

    bl BootRom_InvalidateCache
    ldr pc, =0x38008000
#endif

@//================================================================================================
    .globl      Bootram_SecondaryCore
Bootram_SecondaryCore:

    WREG        (MS_BUS_RIU_ADDR + (0x1033A2 << 1)), 0xff
    WREG        (CONFIG_KERNEL_START_ADDRESS + 0x8000), 0

Bootram_MpCoreLoop:

    wfi

    @ fetch magic number from riu register
    RREG        r1, 0x1F000000 + (0x101D00 << 1) + (0x6D << 2)
    ldr         r2, =0xbabe
    cmp         r1, r2
    bne         Bootram_MpCoreLoop

    mov         ip, lr
    bl          BootRom_InvalidateCache     @//Invalidate Cache
    mov         lr, ip

#if defined(CONFIG_TRUSTZONE_ENABLE)
    ldr     r1, =0x73fff
    mrc     p15, 0, r0, c1, c1, 2
    orr     r0,  r0, r1
    mcr     p15, 0, r0, c1, c1, 2
    ldr    r0, =0xA000ffff
    mov    r1, #0x16000000
    add    r1, r1, #0x1080
    str    r0, [r1]
    add    r1, r1, #0x4
    str    r0, [r1]
    ldr    r0, =0xfff
    mov    r1, #0x16000000
    add    r1, r1, #0x54
    str    r0, [r1]
    ldr    r0, =0xf0
    mov    r1, #0x16000000
    add    r1, r1, #0x104
    str    r0, [r1]
    mrc     15, 0, r0, cr1, cr0, 1
    orr     r0, r0, #1
    mcr     15, 0, r0, cr1, cr0, 1

    mrc p15, 0, r0, c1, c1, 2
    orr r0, r0, #3<<10
    bic r0, r0, #3<<14
    mcr p15, 0, r0, c1, c1, 2
    ldr r0, =(0xF << 20)
    mcr p15, 0, r0, c1, c0, 2

    dmb
    dsb

    mrc  p15, 0, r0, c1, c1, 0
    orr  r0, #0x1
    mcr  p15, 0, r0, c1, c1, 0
    mcr p15, 0, r0, c1, c0, 2
    bic r0, #0x40000000
    mrc p15, 0, r0, c1, c0, 2
#endif

	@ fetch branch address from riu register
    RREG        r1, 0x1F000000 + (0x101D00 << 1) + (0x7B << 2)
    RREG        r2, 0x1F000000 + (0x101D00 << 1) + (0x7C << 2)
    add         r1, r1, r2, lsl #16
    mov         pc, r1

Bootram_SecondaryCoreExit:
    b           Bootram_SecondaryCoreExit

@//-------------------------------------------------------------------------------------------------
@// Invalidate Caches
@// @param  None
@// @return None
@// @note   __invalidate_v7_cache
@//-------------------------------------------------------------------------------------------------
BootRom_InvalidateCache:

    mov         r0, #0
    mcr         p15, 0, r0, c8, c7, 0       @//Invalidate Inst TLB and Data TLB
    mcr         p15, 0, r0, c7, c5, 0       @//Invalidate I-Cache

    @//Must iterate over the caches in order to synthesise a complete clean
    @//of data / unified cache

    mrc         p15, 1, r0, c0, c0, 1       @//read Cache Level ID register (clidr)
    ands        r3, r0, #0x7000000          @//extract level of coherency from clidr
    mov         r3, r3, lsr #23             @//left align level of coherency bit field
    beq         _InvalidateCache_Finished   @//if loc is 0, then no need to clean

    mov         r10, #0                     @//start clean at cache level 0 (in r10)

_InvalidateCache_Loop1:
    add         r2, r10, r10, lsr #1        @//work out 3x current cache level
    mov         r1, r0, lsr r2              @//extract cache type bits from clidr
    and         r1, r1, #7                  @//mask of the bits for current cache only
    cmp         r1, #2                      @//see what cache we have at this level
    blt         _InvalidateCache_Skip       @//skip if no cache, or just i-cache

    mcr         p15, 2, r10, c0, c0, 0      @//select current cache level in cssr
    mov         r1, #0
    mcr         p15, 0, r1, c7, c5, 4       @//prefetchflush to synch the new cssr&csidr
    mrc         p15, 1, r1, c0, c0, 0       @//read the new csidr
    and         r2, r1, #7                  @//extract the length of the cache lines
    add         r2, r2, #4                  @//add 4 (line length offset)
    ldr         r6, =0x03ff
    ands        r6, r6, r1, lsr #3          @//find maximum number on the way size

    .word       0xe16f5f16                  @//DCI   0xE16F5F16 @CLZ r5, r6 @ find bit position of way size increment
    ldr         r7, =0x7fff
    ands        r7, r7, r1, lsr #13         @//extract max number of the index size

_InvalidateCache_Loop2:
    mov         r8, r6                      @//create working copy of max way size

_InvalidateCache_Loop3:
    orr         r11, r10, r8, lsl r5        @//factor way and cache number into r11
    orr         r11, r11, r7, lsl r2        @//factor index number into r11
    mcr         p15, 0, r11, c7, c6, 2      @//invalidate by set/way
    subs        r8, r8, #1                  @//decrement the way
    bge         _InvalidateCache_Loop3

    subs        r7, r7, #1                  @//decrement the index
    bge         _InvalidateCache_Loop2

_InvalidateCache_Skip:
    add         r10, r10, #2                @//increment cache number
    cmp         r3, r10
    bgt         _InvalidateCache_Loop1

_InvalidateCache_Finished:
    bx          lr

#if defined(CONFIG_MSTAR_AUTHEN_ENABLE) && defined(CONFIG_SECURITY_BOOT)
BootRam_AuthenticationFail:
	b           BootRam_AuthenticationFail
#endif

#ifdef CONFIG_MSTAR_EDINBURGH
@//-------------------------------------------------------------------------------------------------
@// BootRom_InitExtDemod
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
@//    .global     BootRom_InitExtDemod
BootRom_InitExtDemod:

    WREG_B      (MS_BUS_RIU_ADDR + (0x000e60 << 1) + 1), 0x00

    RREG        r0, (MS_BUS_RIU_ADDR + (0x101eae << 1))
    bic         r0, r0, #(0x01 << 2)
    REG_C2M     r0, (MS_BUS_RIU_ADDR + (0x101eae << 1))

    WREG_B      (MS_BUS_RIU_ADDR + (0x112002 << 1) + 1), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x11280e << 1)), 0x10
    WREG_B      (MS_BUS_RIU_ADDR + (0x11286a << 1) + 1), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x11287a << 1)), 0x01
    WREG_B      (MS_BUS_RIU_ADDR + (0x112878 << 1) + 1), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x112802 << 1)), 0x0C
    WREG_B      (MS_BUS_RIU_ADDR + (0x112802 << 1) + 1), 0x00

    bx          lr

#endif

#ifdef CONFIG_MSTAR_CASHMERE
@//-------------------------------------------------------------------------------------------------
@// BootRom_InitExtDemod_Cashmere
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
@//    .global     BootRom_InitExtDemod_Cashmere
BootRom_InitExtDemod_Cashmere:
    WREG_B      (MS_BUS_RIU_ADDR + (0x112002 << 1) + 1), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x112840 << 1)), 0x00
    WREG_B      (MS_BUS_RIU_ADDR + (0x11287a << 1)), 0x01
#endif
@//-------------------------------------------------------------------------------------------------
@// BootRom_InitEmacTrimmingControl
@// @param
@// @return None
@// @note
@//-------------------------------------------------------------------------------------------------
@//    .global     BootRom_InitEmacTrimmingControl
BootRom_InitEmacTrimmingControl:

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x2000 << 1))
    ldr         r11, =0x0025
    str         r11, [r12, #(0x4e << 1)]                    @//Set bank to read efuse

    ldr         r11, =0x0001
    str         r11, [r12, #(0x4c << 1)]                    @//Launch efuse read

BootRom_InitEmacTrimmingControlLoop:
    ldr         r11, [r12, #(0x4c << 1)]                    @//Polling efuse read down
    cmp         r11, #0
    bne         BootRom_InitEmacTrimmingControlLoop

    ldr         r11, [r12, #(0x84 << 1)]                    @//Get eFuse at Bank 0x4D[13:0]

    ldr         r1, =0x3FFF
    and         r0, r11, r1

    mov         r1, r11, lsr #14
    and         r1, r1, #0x03

    ldr         r11, [r12, #(0x86 << 1)]                    @//Get eFuse at Bank 0x4D[17:14]

    and         r11, r11, #0x03
    mov         r11, r11, lsl #2
    orr         r1, r1, r11
    mov         r1, r1, lsl #8

    ldr         r12, =(MS_BUS_RIU_ADDR + (0x3400 << 1))
    ldr         r11, [r12, #(0x60 << 1)]
    and         r11, r11, #~(0x0f << 8)
    orr         r11, r11, r1
    orr         r11, r11, #(0x01 << 2)
    str         r11, [r12, #(0x60 << 1)]                    @//0x0034_60[11:8] + 0x0034_60[2] = 1

    ldr         r11, [r12, #(0x68 << 1)]
    and         r11, r11, #0xC000
    orr         r11, r11, r0
    orr         r11, r11, #(0x01 << 15)
    str         r11, [r12, #(0x68 << 1)]                    @//0x0034_68[13:0] + 0x0034_68[15] = 1

BootRom_InitEmacTrimmingControlExit:

    bx          lr
@//-------------------------------------------------------------------------------------------------
@// BOOTRAM_Pad
@// @param  None
@// @return None
@// @note   Pad with zeros (Reserve SIZE_BOOTRAM_RESERVED Bytes for bootram)
@//-------------------------------------------------------------------------------------------------
    .org        (SIZE_BOOTRAM_RESERVED - 4)
    .word       0
