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
#include "drvSPINAND_common.h"
#include "../config/drvSPINAND_config.h"
#ifdef __cplusplus
extern "C"
{
#endif

#define MID_GD          0xC8
#define MID_MICRON      0x2C

#define SPINAND_READ_SUBPAGE 1

typedef enum _SPINAND_ERROR_NUM
{
    ERR_SPINAND_SUCCESS,
    ERR_SPINAND_UNKNOWN_ID,
    ERR_SPINAND_TIMEOUT,
    ERR_SPINAND_ECC_ERROR,
    ERR_SPINAND_ECC_BITFLIP,
    ERR_SPINAND_BAD_BLK,
    ERR_SPINAND_E_FAIL,
    ERR_SPINAND_W_FAIL,
    ERR_SPINAND_INVALID
} SPINAND_FLASH_ERRNO_e;

typedef enum
{
    E_SPINAND_SINGLE_MODE,
    E_SPINAND_FAST_MODE,
    E_SPINAND_DUAL_MODE,
    E_SPINAND_DUAL_MODE_IO,
    E_SPINAND_QUAD_MODE,
    E_SPINAND_QUAD_MODE_IO,
}SPINAND_MODE;

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
    U8   u8CLKConfig;
    U8   u8_UBOOTPBA;
    U8   u8_BL0PBA;
    U8   u8_BL1PBA;
    U8   u8_HashPBA[3][2];
    U8   u8ReadMode;
    U8   u8WriteMode;
} SPINAND_FLASH_INFO_t;

#define DEBUG_SPINAND(debug_level, x)     do { if (_u8SPINANDDbgLevel >= (debug_level)) (x); } while(0)

extern BOOL MDrv_SPINAND_Init(SPINAND_FLASH_INFO_t *tSpinandInfo);
extern U32 MDrv_SPINAND_Read(U32 u32_PageIdx, U8 *u8Data, U8 *pu8_SpareBuf);
extern U32 MDrv_SPINAND_Write(U32 u32_PageIdx, U8 *u8Data, U8 *pu8_SpareBuf);
extern U32 MDrv_SPINAND_BLOCK_ERASE(U32 u32_BlkIdx);
extern U8 MDrv_SPINAND_ReadID(U16 u16Size, U8 *u8Data);
extern void SpiNandMain(unsigned int dwSramAddress, unsigned int dwSramSize);
extern U32 MDrv_SPINAND_SetMode(SPINAND_MODE eMode);
extern BOOL MDrv_SPINAND_ForceInit(SPINAND_FLASH_INFO_t *tSpinandInfo);
extern U32 MDrv_SPINAND_Read_RandomIn(U32 u32_PageIdx, U32 u32_Column, U32 u32_Byte, U8 *u8Data);

extern U32 HAL_SPINAND_Read (U32 u32Addr, U32 u32DataSize, U8 *pu8Data);
extern U32 HAL_SPINAND_Write( U32 u32_PageIdx, U8 *u8Data, U8 *pu8_SpareBuf);
extern U32  HAL_SPINAND_ReadID(U32 u32DataSize, U8 *pu8Data);
extern U32 HAL_SPINAND_RFC(U32 u32Addr, U8 *pu8Data);
extern void HAL_SPINAND_Config(U32 u32PMRegBaseAddr, U32 u32NonPMRegBaseAddr);
extern U32 HAL_SPINAND_BLOCKERASE(U32 u32_PageIdx);
extern U32 HAL_SPINAND_Init(void);
extern U32 HAL_SPINAND_WriteProtect(BOOL bEnable);
extern BOOL HAL_SPINAND_PLANE_HANDLER(U32 u32Addr);
extern U32 HAL_SPINAND_SetMode(SPINAND_MODE eMode);
extern void HAL_SPINAND_CSCONFIG(void);
////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: HAL_SPINAND_SetCKG()
/// @brief \b Function \b Description: This function is used to set ckg_spi dynamically
/// @param <IN>        \b eCkgSpi    : enumerate the ckg_spi
/// @param <OUT>       \b NONE    :
/// @param <RET>       \b TRUE: Success FALSE: Fail
/// @param <GLOBAL>    \b NONE    :
/// @param <NOTE>    \b : Please use this function carefully , and is restricted to Flash ability
////////////////////////////////////////////////////////////////////////////////
extern BOOL HAL_SPINAND_SetCKG(U8 u8CkgSpi);
extern U8 HAL_SPINAND_ReadStatusRegister(U8 *u8Status, U8 u8Addr);
extern U8 HAL_SPINAND_WriteStatusRegister(U8 *u8Status, U8 u8Addr);
extern U32 HAL_SPINAND_READ_STATUS(U8 *pu8Status, U8 u8Addr);
extern U8 _u8SPINANDDbgLevel;

#ifdef __cplusplus
}
#endif

#endif

