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

#ifndef _DRV_SPINAND_BOOT_H_
#define _DRV_SPINAND_BOOT_H_

extern U32 drvNAND_LoadBLOffset(U8* pu8DMAAddr, U32 u32_Offset, U32 u32_Size);
extern U32 drvNAND_Load2ndBL(U8* pu8DMAAddr, U32 u32_Size);
extern U32 drvNAND_LoaduBoot(U8* pu8DMAAddr, U32 u32_BLSize);

#endif

