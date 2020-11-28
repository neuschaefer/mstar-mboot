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

#ifndef _DRV_SPINAND_H_
#define _DRV_SPINAND_H_
#include "halSPINAND.h"


#define MID_GD          0xC8
#define MID_MICRON      0x2C

typedef enum _SPINAND_ERROR_NUM
{
    ERR_SPINAND_SUCCESS,
    ERR_SPINAND_UNKNOWN_ID,
    ERR_SPINAND_TIMEOUT,
    ERR_SPINAND_ECC_ERROR,
    ERR_SPINAND_BAD_BLK,
    ERR_SPINAND_E_FAIL,
    ERR_SPINAND_W_FAIL,
    ERR_SPINAND_INVALID
} SPINAND_FLASH_ERRNO_e;

typedef struct
{
    U8   u8_IDByteCnt; 
    U8   au8_ID[15];
    U16  u16_SpareByteCnt;
    U16  u16_PageByteCnt;
    U16  u16_BlkPageCnt;
    U16  u16_BlkCnt;
    U16  u16_SectorByteCnt;
    U8   u8PlaneCnt;
    U8   u8WrapConfig;
    BOOL bRIURead;
    U8   u8_MaxClk;
    U8   u8_UBOOTPBA;
    U8   u8_BL0PBA;
    U8   u8_BL1PBA;
    U8   u8_HashPBA[3][2];
//    U8   u8ReadMode;
//    U8   u8WriteMode;
} SPINAND_FLASH_INFO_t;

#define _gtSpinandInfo    ((SPINAND_FLASH_INFO_t *)CONFIG_SRAM_SPINAND_OFFSET)

#define SPARE_SIZE  _gtSpinandInfo->u16_SpareByteCnt
#define BLOCK_SIZE  _gtSpinandInfo->u16_BlkPageCnt
#define SECTOR_SIZE _gtSpinandInfo->u16_SectorByteCnt
#define PAGE_SIZE   _gtSpinandInfo->u16_PageByteCnt
#define PLANE       _gtSpinandInfo->u8PlaneCnt
#define RIU_FLAG    _gtSpinandInfo->bRIURead
#define CLKCFG      _gtSpinandInfo->u8_MaxClk
//#define READ_MODE   _gtSpinandInfo->u8ReadMode
//#define WRITE_MODE  _gtSpinandInfo->u8WriteMode

U32 MDrv_SPINAND_Read(U32 u32_BlkIdx, U32 u32_PageIdx, U8 u8_SectorInPage, U32 u32_SectorCnt, U8 *u8Data, U8 *pu8_SpareBuf);

#endif

