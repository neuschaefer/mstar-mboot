/*
 *#############################################################################
 *
 * Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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

#ifndef _HAL_SPINAND_BOOT_H_
#define _HAL_SPINAND_BOOT_H_

#include "halSPINAND.h"

#if defined(CONFIG_MCU_ARM)
#define CONFIG_SRAM_SPINAND_OFFSET  0x1FC02800 //512B Reserved for SPINAND Flash Driver
#define CONFIG_SRAM_SPINAND_BUF     (0x1FC02800+0x100)
#define RIU_BASE                    0x1F200000
#elif defined(CONFIG_MCU_MIPS32)
#define CONFIG_SRAM_SPINAND_OFFSET  0xB2003800 //512B Reserved for SPINAND Flash Driver
#define CONFIG_SRAM_SPINAND_BUF     (0xB2003800+0x100)
#define RIU_BASE                    0xBF200000
#else
#error  "Unknown CPU Platform"
#endif

#define REG_OFFSET_SHIFT_BITS       2
#define GET_REG_ADDR(x, y)          ((x)+((y) << REG_OFFSET_SHIFT_BITS))

#define REG_BANK_PORTSTATUS         0x0280U
#define PORTSTATUS_BASE             GET_REG_ADDR(RIU_BASE, REG_BANK_PORTSTATUS)
#define BOOTSTAGE_REG               GET_REG_ADDR(PORTSTATUS_BASE, 0x7)

#define DEBUG_REG                   GET_REG_ADDR(PORTSTATUS_BASE, 0x01)
#define DEBUG_REG_SYS_L1            GET_REG_ADDR(PORTSTATUS_BASE, 0x02)
#define DEBUG_REG_SYS_L2            GET_REG_ADDR(PORTSTATUS_BASE, 0x03)

#define REG_READ_UINT16(reg_addr, val)      val = REG((reg_addr))
#define REG_WRITE_UINT16(reg_addr, val)     REG((reg_addr)) = (val)

#endif

