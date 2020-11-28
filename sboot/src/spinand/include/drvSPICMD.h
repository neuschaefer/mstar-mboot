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
#include "drvSPINAND.h"

// SPI NAND COMMAND
#define SPI_NAND_CMD_PGRD                0x13
#define SPI_NAND_CMD_RDID                0x9F
#define SPI_NAND_CMD_WREN                0x06
#define SPI_NAND_CMD_WRDIS               0x04
#define SPI_NAND_CMD_RFC                 0x03
#define SPI_NAND_CMD_PP                  0x02
#define SPI_NAND_CMD_RPL                 0x84
#define SPI_NAND_CMD_PE                  0x10
#define SPI_NAND_CMD_GF                  0x0F
#define SPI_NAND_CMD_RESET               0xFF
        #define SPI_NAND_REG_PROT                0xA0
        #define SPI_NAND_REG_FEAT                0xB0
        #define SPI_NAND_REG_STAT                0xC0
                #define SPI_NAND_STAT_OIP              1
                #define ECC_STATUS_PASS                (0x00 << 4)
                #define ECC_STATUS_ERR                 (0x02 << 4)
        #define SPI_NAND_REG_FUT                 0xD0
#define SPI_NAND_CMD_SF                  0x1F
#define SPI_NAND_CMD_BE                  0xD8
#define SPI_NAND_CMD_CE                  0xC7
#define SPI_NAND_ADDR_LEN                   3
#define SPI_NAND_PAGE_ADDR_LEN              2
#define SPI_NAND_PLANE_OFFSET               6
#define SPI_RESET_DELAY                  2000

