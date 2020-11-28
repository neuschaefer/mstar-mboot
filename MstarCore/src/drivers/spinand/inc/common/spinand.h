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

#ifndef _SPINAND_H_
#define _SPINAND_H_

#include "drvSPINAND.h"

#define USFD_LOGI_PART			0x8000

#define USFD_PART_HWCONFIG		1
#define USFD_PART_BOOTLOGO		2
#define USFD_PART_BL			3
#define USFD_PART_OS			4
#define USFD_PART_CUS			5
#define USFD_PART_UBOOT			6
#define USFD_PART_SECINFO		7
#define USFD_PART_OTP			8
#define USFD_PART_RECOVERY		9
#define USFD_PART_E2PBAK		10
#define USFD_PART_NVRAMBAK		11
#define USFD_PART_APANIC		12
#define USFD_PART_ENV			13
#define USFD_PART_MISC			14
#define USFD_PART_TBL			15
#define USFD_PART_CTRL			16
#define USFD_PART_FDD			17
#define USFD_PART_TDD			18
#define USFD_PART_UBIRO			19

typedef struct
{
	U16 u16_StartBlk;		// the start block index
	U16 u16_BlkCnt;			// project team defined
	U16 u16_PartType;		// project team defined
	U16 u16_BackupBlkCnt;	// reserved good blocks count for backup, UNFD internal use.
							// e.g. u16BackupBlkCnt  = u16BlkCnt * 0.03 + 2
} PARTITION_RECORD_t;

typedef struct
{
	U32 u32_ChkSum;
	U16	u16_SpareByteCnt;
	U16	u16_PageByteCnt;
	U16	u16_BlkPageCnt;
	U16	u16_BlkCnt;
	U16 u16_PartCnt;
	U16 u16_UnitByteCnt;
	PARTITION_RECORD_t records[62];

} PARTITION_INFO_t;

typedef struct _SPI_NAND_DRIVER
{
	SPINAND_FLASH_INFO_t tSpinandInfo;

	PARTITION_INFO_t tPartInfo;
	U8 u8_HasPNI;

	U8 *pu8_pagebuf;
	U8 *pu8_sparebuf;
	U32 u32_column;
	U8 u8_status;

} SPI_NAND_DRIVER_t;

typedef struct
{
	U8  au8_Tag[16];
	SPINAND_FLASH_INFO_t tSpiNandInfo;
	U8 au8_Reserved[];

} SPINAND_FLASH_INFO_TAG_t;

#define SPINAND_FLASH_INFO_TAG "MSTARSEMIUSFDCIS"

// this definition is used to measure nand read/write speed
#define NAND_SPEED_TEST                     0

extern void dump_mem(unsigned char *buf, int cnt);
#endif

