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

#include "boot1.inc"

#ifndef _MSTAR_ADDR_INC_
#include "mstar_addr.inc"
#endif

#ifndef _DRV_UART_INC_
#include "drv_uart.inc"
#endif

#ifndef _MACRO_INC_
#include "macro.inc"
#endif

#ifndef _BOARD_H_
#include "Board.h"
#endif

#ifndef _BOOT_INC_
#define _BOOT_INC_

//-------------------------------------------------------------------------------------------------
// Version
//-------------------------------------------------------------------------------------------------
BOOT_VERSION                            = 0x20141009

//-------------------------------------------------------------------------------------------------
// Build Options
//-------------------------------------------------------------------------------------------------

#if defined(CONFIG_BIST_0x0401_UNITS)
BIST_LEN                                = 0x0401
#elif defined(CONFIG_BIST_0x1001_UNITS)
BIST_LEN                                = 0x1001
#elif defined(CONFIG_BIST_0x8001_UNITS)
BIST_LEN                                = 0x8001
#else
BIST_LEN                                = 0x1001
#endif

BOOT_DEBUG_VERSION                      = 1         //Set for debugging boot code
SUPPORT_POWER_SAVING                    = 1
//DYNAMIC_POWER_ON_OFF                  = 0

SUPPORT_UNZIP                           = 1         //Set for supporting Unzip (also need to change boot.sh)
//---------------------------------------------------------------------------------------------------------
// SUPPORT_UNZIP
//---------------------------------------------------------------------------------------------------------
SBOOT_TO_KERNEL_ZIP                     = 0
ADDR_UNZIP_STACK_POINTER                = (MS_BUS_MIU0_0000M + 0x00380000)
ADDR_ZIPBIN_ROM_START                   = (MS_BUS_XIU_SPI_ADDR + 0x00030000)
ADDR_ZIPBIN_RAM_START                   = (MS_BUS_MIU0_0000M + 0x01000000)
ADDR_ZIPBIN_RAM_END                     = (MS_BUS_MIU0_0000M + 0x01400000)
ADDR_ZIPBIN_RAM_START_CACHE             = (ADDR_ZIPBIN_RAM_START)
ADDR_SYSTEM_RAM_START                   = (MS_BUS_MIU0_0000M + 0x00400000)
ADDR_UNZIP_BUFFER                       = (MS_BUS_MIU0_0000M + 0x00300000)
ADDR_UNZIP_ROM_START                    = (MS_BUS_XIU_SPI_ADDR + 0x00020000)
ADDR_UNZIP_RAM_START                    = (MS_BUS_MIU0_0000M + 0x00100000)
ADDR_UNZIP_RAM_END                      = (MS_BUS_MIU0_0000M + 0x00110000)
ADDR_UNZIP_RAM_START_CACHE              = (ADDR_UNZIP_RAM_START)

//-------------------------------------------------------------------------------------------------
// Addressed in ROM / RAM
//-------------------------------------------------------------------------------------------------
// Start address after boot-up
ADDR_BOOT_ROM_START                     = MS_BUS_BOOT_ADDR

//Reserve Bytes for boot code (to avoid recursive defines SIZE_BOOT in boot1.inc)
SIZE_BOOT_RESERVED                      = 3072
SIZE_BOOTROM_RESERVED                   = 8192
SIZE_BOOTRAM_RESERVED                   = 2048
SIZE_BOOTNAND_RESERVED                  = 53248     //52 KB

SIZE_CHUNK_HEADER_RESERVED              = 128       //16 chunks.

// Copy UBoot binary from SPI Flash to RAM @@@
//SIZE_UBOOT                           in boot1.c
//ADDR_UBOOT_ROM_START                 = (ADDR_BOOT_ROM_START + SIZE_BOOT_RESERVED + SIZE_BOOTROM_RESERVED + SIZE_BOOTRAM_RESERVED + SIZE_BOOTNAND_RESERVED + SIZE_CHUNK_HEADER_RESERVED)
//ADDR_UBOOT_ROM_END                   = (ADDR_UBOOT_ROM_START + SIZE_UBOOT) #actually end+1
//ADDR_UBOOT_RAM_START                 = (UBOOT_ENTRY_ADDR | 0x20000000)
//ADDR_UBOOT_RAM_START_CACHE           = (ADDR_UBOOT_RAM_START & ~0x20000000 )
//ADDR_UBOOT_RAM_END                   = (ADDR_UBOOT_RAM_START + SIZE_UBOOT) #actually end+1
//ADDR_UBOOT_RAM_ENTRY_CACHE           = UBOOT_ENTRY_ADDR    @ToDo: copy general exception handler at OS init instead of linking it to code

// Unzip binary @@@
//Initialize system stack pointer for c subroutine
ADDR_STACK_POINTER                      = MS_BUS_MIU0_0000M + (CONFIG_DRAM_SIZE_MB_RELOCATE - 1) * 0x100000    //Initial stack pointer (downwards)

CONFIG_CPU_CLOCK                        = ((3623878 / CPU_CLOCK) * 1000)

#ifdef CONFIG_MSTAR_DVFS_ENABLE
CONFIG_DVFS_CPU_CLOCK_MAX               = CONFIG_CPU_CLOCK
CONFIG_DVFS_CPU_CLOCK_MIN               = ((3623878 / CONFIG_MSTAR_DVFS_CPU_CLOCK_LOWER_BOUND) * 1000)
CONFIG_DVFS_CPU_CLOCK_INIT              = ((3623878 / CONFIG_MSTAR_DVFS_INIT_CPU_CLOCK) * 1000)
#endif

#if defined(CONFIG_MSTAR_GPU_MANUAL) 
CONFIG_GPU_CLOCK                        = (GPU_CLOCK / 6)
#endif 

#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH) || \
    defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
BOOT_INFO_REGISTER_CORE1_START_ADDR_HIGH = (MS_BUS_RIU_ADDR + (0x100510 << 1))
BOOT_INFO_REGISTER_CORE1_START_ADDR_LOW = (MS_BUS_RIU_ADDR + (0x100512 << 1))
#endif

#if defined(CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
CONFIG_EMMC_HASH0_SIZE                  = (14 * 1024)
CONFIG_EMMC_HASH1_SIZE                  = (14 * 1024)
CONFIG_EMMC_HASH1_MIU_SIZE              = (7 * 1024)
#if defined(CONFIG_MSTAR_STR_ENABLE)
CONFIG_EMMC_HASH1_STR_SIZE              = (7 * 1024)
#endif
CONFIG_EMMC_BOOTRAM_ADDRESS             = (32 * 1024) + CONFIG_EMMC_HASH0_SIZE
#endif

//-------------------------------------------------------------------------------------------------
// GIC registers
//-------------------------------------------------------------------------------------------------
REG_GIC_BASE_ADDRESS                    = 0x16000000
REG_GIC_CPU_BASE_ADDRESS                = (REG_GIC_BASE_ADDRESS + 0x2000)
REG_GIC_DIST_BASE_ADDRESS               = (REG_GIC_BASE_ADDRESS + 0x1000)

//-------------------------------------------------------------------------------------------------
// FCIE registers
//-------------------------------------------------------------------------------------------------
FCIE0_BASE                              = 0x1F222600
REG_MMA_PRI                             = (FCIE0_BASE + 0x02 << 2)
REG_MIU_ADDR_H                          = (FCIE0_BASE + 0x03 << 2)
REG_MIU_ADDR_L                          = (FCIE0_BASE + 0x04 << 2)
REG_MMA_PATH_CTL                        = (FCIE0_BASE + 0x0A << 2)
REG_JOB_BL_CNT                          = (FCIE0_BASE + 0x0B << 2)
REG_SD_MODE                             = (FCIE0_BASE + 0x10 << 2)
REG_SD_CTRL                             = (FCIE0_BASE + 0x11 << 2)
REG_BOOT_CONFIG                         = (FCIE0_BASE + 0x2F << 2)

//-------------------------------------------------------------------------------------------------
// Voltage Identification Registers
//-------------------------------------------------------------------------------------------------
REG_EFUSE_BANK1_HIGH                    = (MS_BUS_RIU_ADDR + (0x00200E << 1))
REG_EFUSE_BANK1_LOW                     = (MS_BUS_RIU_ADDR + (0x00200C << 1))

//-------------------------------------------------------------------------------------------------
// Other registers
//-------------------------------------------------------------------------------------------------
REG_TOP_POWER_STATUS                    = (MS_BUS_RIU_ADDR + 0x00203cdc)

//-------------------------------------------------------------------------------------------------
// registers
//-------------------------------------------------------------------------------------------------
PM_BASE                                 = (MS_BUS_RIU_ADDR + 0x00001C00)
MAU_BASE                                = (MS_BUS_RIU_ADDR + 0x00001D00)

//-------------------------------------------------------------------------------------------------
// secondary core entry
//-------------------------------------------------------------------------------------------------
BOOT_INFO_REGISTER_CORE1_START_ADDR_LOW  = (MS_BUS_RIU_ADDR + (0x100510 << 1))
BOOT_INFO_REGISTER_CORE1_START_ADDR_HIGH = (MS_BUS_RIU_ADDR + (0x100512 << 1))
BOOT_INFO_REGISTER_MAGIC                 = (MS_BUS_RIU_ADDR + (0x100514 << 1))
#endif
