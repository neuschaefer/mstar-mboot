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
#include "drvSPICMD.h"
#include "halSPINAND.h"
#endif

//==========================================================================
// Define
//==========================================================================


//==========================================================================
// Global Variable
//==========================================================================

U32 MDrv_SPINAND_Read(U32 u32_BlkIdx, U32 u32_PageIdx, U8 u8_SectorInPage, U32 u32_SectorCnt, U8 *u8Data, U8 *pu8_SpareBuf)
{
    U32  u32DataSize;
    U32  u32Addr;
    U16  u16NumofSector;
    U8   u8Status;
    SPINAND_FLASH_ERRNO_e eRet = ERR_SPINAND_SUCCESS;
    //calculate page address 
    u32Addr = (u32_BlkIdx * BLOCK_SIZE) + u32_PageIdx;
    //read data to cache first
    HAL_SPINAND_RFC(u32Addr, &u8Status);

    if(u8Status & ECC_STATUS_ERR)
    {
        eRet = ERR_SPINAND_ECC_ERROR;
    }
    
    if(PLANE)
        HAL_SPINAND_PLANE_HANDLER(u32Addr);
    //HAL_SPINAND_SetCKG(CLKCFG);
    // calculate data size
    u32DataSize = u32_SectorCnt * SECTOR_SIZE;
    // calculate read start address
    u32Addr = u8_SectorInPage * SECTOR_SIZE;

    // Read SPINand Data
    HAL_SPINAND_Read (u32Addr, u32DataSize, u8Data);

    // calculate number of sector per page
    u16NumofSector = PAGE_SIZE / SECTOR_SIZE;
    // update start address to spare start address

    u32Addr = PAGE_SIZE + ((SPARE_SIZE / u16NumofSector)*(u8_SectorInPage));

    // update size to SPARE space size
    u32DataSize = ((SPARE_SIZE / u16NumofSector) *u32_SectorCnt);

    // Read SPINand Spare Data
    HAL_SPINAND_Read(u32Addr, u32DataSize, pu8_SpareBuf);
    return eRet;
}

