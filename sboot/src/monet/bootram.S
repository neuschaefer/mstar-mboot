/*
 *#############################################################################
 *
 * Copyright (c) 2006-2015 MStar Semiconductor, Inc.
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

/*
 * PSR bits
 */
#define PSR_MODE_EL0t	0x00000000
#define PSR_MODE_EL1t	0x00000004
#define PSR_MODE_EL1h	0x00000005
#define PSR_MODE_EL2t	0x00000008
#define PSR_MODE_EL2h	0x00000009
#define PSR_MODE_EL3t	0x0000000c
#define PSR_MODE_EL3h	0x0000000d
#define PSR_MODE_MASK	0x0000000f

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
#define LINUX_KERNEL_SIZE           0x00800000
#endif

//-------------------------------------------------------------------------------------------------
// BOOTRAM_Entry:
// @param  None
// @return None
// @note   Entry point of Boot code
//-------------------------------------------------------------------------------------------------
    .globl      BOOTRAM_Entry

BOOTRAM_Entry:

    DPUTK       '_'

// Add Version Information for Load Board
//  WREG        (MS_BUS_RIU_ADDR + (0x103382 << 1)), 0x0001
//  WREG        (MS_BUS_RIU_ADDR + (0x103384 << 1)), 0x2014
//  WREG        (MS_BUS_RIU_ADDR + (0x103386 << 1)), 0x1013

    //Configure PAD top for MUX and GPIO (e.g. DDR power)
    ldr         x0, =padInitTbl
    add         x0, x0, #10
//  bl          MDrv_WriteRegMaskTbl

//================================================================================================
#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) || \
    defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)

    ldr         w0, =Bootram_SecondaryCore
    ldr         w1, =0xFFFF
    mov         w2, w0, lsr #16
    and         w2, w2, w1
    REG_C2M     w2, BOOT_INFO_REGISTER_CORE1_START_ADDR_HIGH

    and         w2, w0, w1
    REG_C2M     w2, BOOT_INFO_REGISTER_CORE1_START_ADDR_LOW

#endif

//================================================================================================
    //Initial Global Interrupt Interface
//  WREG        (REG_GIC_DIST_BASE_ADDRESS + 0x0000), 0x00000001
    WREG        (REG_GIC_CPU_BASE_ADDRESS + 0x0004), 0x000000f0
    WREG        (REG_GIC_DIST_BASE_ADDRESS + 0x0180), 0xffff0000
    WREG        (REG_GIC_DIST_BASE_ADDRESS + 0x0100), 0x0000ffff

    //Poke Core1/2/3 using software interrupt
    WREG        (REG_GIC_DIST_BASE_ADDRESS + 0x0F00), 0x000e0001
   
    //enable GIC dis/cpu interface  
    WREG        (REG_GIC_DIST_BASE_ADDRESS + 0x0000), 0x00000001
    WREG        (REG_GIC_CPU_BASE_ADDRESS + 0x0000), 0x00000001

    //Switch FIQ/IRQ merge bit
    WREG        (0x1f000000 + (0x123964 << 1)), 0x00001051

#if defined(CONFIG_MSTAR_TITANIA_BD_FPGA) && defined(CONFIG_64BIT_TO_32BIT_MODE)
    DPUTK       'a'
    DPUTK       'a'
    DPUTK       'r'
    DPUTK       'c'
    DPUTK       'h'
    DPUTK       '3'
    DPUTK       '2'
    DPUTK       '.'
    DPUTK       '.'
    DPUTK       '.'
   
    bl          aarch32_setup

    .word 0xe320f000  //nop
    .word 0xe320f000  //nop
    .word 0xeafffffe  //b .
 
#else 
    /* enter el1 bypassing el2 */
    bl         el3_setup

    DPUTK       'a'
    DPUTK       'a'
    DPUTK       'r'
    DPUTK       'c'
    DPUTK       'h'
    DPUTK       '6'
    DPUTK       '4'
    DPUTK       '.'
    DPUTK       '.'
    DPUTK       '.'
#endif

BootRam_Loop:
    b BootRam_Loop

//================================================================================================
// Clear data in BSS section

    ldr         x0, =_ld_bootbss_start
    ldr         x1, =_ld_bootbss_end

    cmp         x0, x1
    b.eq        _ClearBssExit

_ClearBssLoop:
    str         wzr, [x0], #0x04
    cmp         x0, x1
    b.ne        _ClearBssLoop

_ClearBssExit:

//================================================================================================
// Initialize system stack pointer for unzip subroutine

    ldr         x0, =ADDR_STACK_POINTER
    mov         sp, x0

#if defined(CONFIG_MSTAR_TITANIA_BD_FPGA) || defined(CONFIG_SBOOT_TO_KERNEL)
//================================================================================================
//Copy Image to DRAM

    ldr         x0, =LINUX_KERNEL_FLASH_ADDRESS     //Starting Address of Linux Kernel in SPI Flash
    ldr         x1, =LINUX_KERNEL_DRAM_ADDRESS      //Dest Address of Linux Kernel in DRAM
    ldr         x2, =LINUX_KERNEL_SIZE              //Image Size of Linux Kernel

#if 0
_CopyImageLoop:
    LDMIA       x0!, {x3 - x10}
    STMIA       x1!, {x3 - x10}
    SUBS        x2, x2, #32
    bge         _CopyImageLoop

#else
_CopyImageLoop:

    ldr         x3, [x0], #0x04
    str         x3, [x1], #0x04

    subs        x2, x2, #0x04

    ldr         x3, =0x0007FFFF
    and         x4, x2, x3
    cmp         x4, #0
    b.gt        _CopyImageLoop

    PUTK        '#'

    cmp         x2, #0
    b.gt        _CopyImageLoop
#endif

//================================================================================================
//Jump to Kernel Entry of Linux

    PUTK        '\n'
    PUTK        '\r'

    mrs         x0, SCTLR_EL3   
    bic         x0, x0, #(0x01 << 12) | (0x01 << 11) @//Disable L1 I-Cache and Branch Prediction
    bic         x0, x0, #(0x01 << 2)                 @//Disable L1 D-Cache and MMU
    msr         SCTLR_EL3, x0

    ldr         x30, =LINUX_KERNEL_ENTRY
    ret

#endif

//================================================================================================
#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)
    //LOAD CHUNK HEADER
    ldr         x0, =CONFIG_UBOOT_LOADADDR
    ldr         x1, =0x400
    bl          drvNAND_LoaduBoot

    // LOAD UBOOT
    ldr         x0, =CONFIG_UBOOT_LOADADDR
    ldr         w3, [x0, #0]    // UBOOT_ROM_START in MBOOT PARTITION
    ldr         w1, [x0, #4]    // UBOOT_RAM_START
    ldr         w2, [x0, #8]    // UBOOT_RAM_END
    sub         w1, w2, w1      // UBOOT_SIZE = UBOOT_RAM_END - UBOOT_RAM_START
    add         w1, w1, w3      // LOAD SIZE
    sub         w0, w0, w3
    bl          drvNAND_LoaduBoot

#elif defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    //LOAD CHUNK HEADER
    ldr         x0, =CONFIG_UBOOT_LOADADDR
    ldr         x1, =0x400
    ldr         x2, =0x1000
    bl          eMMC_ReadData_MIU

    // LOAD UBOOT
    ldr         x0, =CONFIG_UBOOT_LOADADDR
    ldr         x1, =0x180000
    ldr         x2, =0x1002
    bl          eMMC_ReadData_MIU
#else

    bl          DoMSDecompression

#endif

//================================================================================================
BOOT_POINT:

    DPUTK       'U'

    WREG        0x1f006040, 0x0000          //Disable Hardware Timer 1

#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) || \
    defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    ldr         x30, =CONFIG_UBOOT_LOADADDR
    ret
#else

#ifndef CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51
#ifdef CONFIG_MSTAR_PM_SWIR
    ldr         x0, =0x14030000
#else
    ldr         x0, =0x14020000
#endif
#else
    ldr         x0, =0x14030000
#endif

    ldr         x30, [x0, #16]
    ret
#endif

//================================================================================================
    .globl      Bootram_SecondaryCore
Bootram_SecondaryCore:

    wfe
    
    RREG        w1, BOOT_INFO_REGISTER_MAGIC
    ldr         w2, =0xbabe               //check magic number
    cmp         w1, w2
    b.ne         Bootram_SecondaryCore

Bootram_MpCoreLoop:
    /*enter el1 bypassing el2 */
    bl          el3_setup
   
    RREG        w7, BOOT_INFO_REGISTER_CORE1_START_ADDR_LOW
    and         w7, w7, #0x03
    cmp         w7, #0
    b.ne        Bootram_MpCoreLoop        //Check the starting address of secondary processor is legal

    RREG        w7, BOOT_INFO_REGISTER_CORE1_START_ADDR_HIGH
    RREG        w8, BOOT_INFO_REGISTER_CORE1_START_ADDR_LOW

    add         w9, w8, w7, lsl #16
    br          x9

Bootram_SecondaryCoreExit:
    b           Bootram_SecondaryCoreExit

/*************************************************************************
 * If we're fortunate enough to boot at EL3, ensure that the world is
 * sane before dropping to EL2.
 *************************************************************************/
el3_setup:
    mrs	        x0, CurrentEL
    cmp	        x0, #PSR_MODE_EL3t
    ccmp	x0, #PSR_MODE_EL3h, #0x4, ne
    b.eq	1f
    ret

1:  msr         ELR_EL3, x30
    msr         SCTLR_EL2, XZR
    mov         x0, #0x3c9
    msr         SPSR_EL3, x0
    mov         x0, #0x401
    msr         SCR_EL3, x0
    eret

#if defined(CONFIG_64BIT_TO_32BIT_MODE)
aarch32_setup:
    msr      vbar_el3, xzr
    msr      vbar_el2, xzr

   /*Put system registers to known values*/
    MSR      SCTLR_EL2, xzr
    msr      SCTLR_EL1, xzr
    msr      CPTR_EL3, xzr
    msr      CPTR_EL2, xzr
    msr      CPACR_EL1, xzr
    /*msr      FPEXC32_EL2, xzr*/
    msr      HACR_EL2, xzr
    msr      HSTR_EL2, xzr
    msr      CNTVOFF_EL2, xzr

    /*Set ID register view for NS.EL1*/
    mrs      x0, MPIDR_EL1
    msr      VMPIDR_EL2, x0
    mrs      x0, MIDR_EL1
    msr      VPIDR_EL2, x0

    /*CORTEX-A53 SPECIFIC CORE*/
    mrs      x1, ACTLR_EL3
    orr      x1, x1, #1
    orr      x1, x1, #(1 << 1)
    orr      x1, x1, #(1 << 4)
    orr      x1, x1, #(1 << 5)
    orr      x1, x1, #(1 << 6)
    msr      ACTLR_EL3, x1

    msr      HCR_EL2, xzr
    msr      ELR_EL3, x30
    msr      SCTLR_EL2, XZR
    mov      x0, #0x3c9
    msr      SPSR_EL3, x0
    mov      x0, #0x401
    msr      SCR_EL3, x0
    msr      ELR_EL3, x30

    mrs      x1,spsr_el3
    mov      x2, 0xfffffffffffffde0
    and      x1, x1, x2 
    orr      x1, x1,#0x3       //SVC mode
    orr      x1, x1,#(1 << 4)  //AARCH32
    and      x1, x1,~(1 << 9)  //Litle endian
    msr      spsr_el3, x1

    eret

#endif


//-------------------------------------------------------------------------------------------------
// BOOTRAM_Pad
// param  None
// return None
// note   Pad with zeros (Reserve SIZE_BOOTRAM_RESERVED Bytes for bootram)
//-------------------------------------------------------------------------------------------------

    .org        (SIZE_BOOTRAM_RESERVED - 4)
    .word       0
