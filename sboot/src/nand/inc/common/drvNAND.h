//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all 
// or part of MStar Software is expressly prohibited, unless prior written 
// permission has been granted by MStar. 
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.  
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software. 
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s 
//    confidential information in strictest confidence and not disclose to any
//    third party.  
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.  
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or 
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.  
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
/*===========================================================
 * MStar Semiconductor Inc.
 *
 * Nand Driver for FCIE3 - drvNAND_v3.h
 *
 * History
 *    - initial version, 2009.06.07, Hill.Sung
 *      please modify the drvNAND_platform.h for your platform.
 *
 *
 *===========================================================*/

#ifndef NAND_DRV_V3
#define NAND_DRV_V3

#ifndef U32
#define U32  unsigned long
#endif
#ifndef U16
#define U16  unsigned short
#endif
#ifndef U8
#define U8   unsigned char
#endif
#ifndef S32
#define S32  signed long
#endif
#ifndef S16
#define S16  signed short
#endif
#ifndef S8
#define S8   signed char
#endif

#ifndef SWAP16
#define SWAP16(x) \
    ((U16)( \
    (((U16)(x) & (U16) 0x00ffU) << 8) | \
    (((U16)(x) & (U16) 0xff00U) >> 8) ))
#endif
#ifndef SWAP32
#define SWAP32(x) \
    ((U32)( \
    (((U32)(x) & (U32) 0x000000ffUL) << 24) | \
    (((U32)(x) & (U32) 0x0000ff00UL) <<  8) | \
    (((U32)(x) & (U32) 0x00ff0000UL) >>  8) | \
    (((U32)(x) & (U32) 0xff000000UL) >> 24) ))
#endif
#ifndef SWAP64
#define SWAP64(x) \
    ((U64)( \
    (U64)(((U64)(x) & (U64) 0x00000000000000ffULL) << 56) | \
    (U64)(((U64)(x) & (U64) 0x000000000000ff00ULL) << 40) | \
    (U64)(((U64)(x) & (U64) 0x0000000000ff0000ULL) << 24) | \
    (U64)(((U64)(x) & (U64) 0x00000000ff000000ULL) <<  8) | \
    (U64)(((U64)(x) & (U64) 0x000000ff00000000ULL) >>  8) | \
    (U64)(((U64)(x) & (U64) 0x0000ff0000000000ULL) >> 24) | \
    (U64)(((U64)(x) & (U64) 0x00ff000000000000ULL) >> 40) | \
    (U64)(((U64)(x) & (U64) 0xff00000000000000ULL) >> 56) ))
#endif

#ifdef BIG_ENDIAN // project team defined macro
#define cpu2le64(x) SWAP64((x))
#define le2cpu64(x) SWAP64((x))
#define cpu2le32(x) SWAP32((x))
#define le2cpu32(x) SWAP32((x))
#define cpu2le16(x) SWAP16((x))
#define le2cpu16(x) SWAP16((x))
#define cpu2be64(x) ((UINT64)(x))
#define be2cpu64(x) ((UINT64)(x))
#define cpu2be32(x) ((UINT32)(x))
#define be2cpu32(x) ((UINT32)(x))
#define cpu2be16(x) ((UINT16)(x))
#define be2cpu16(x) ((UINT16)(x))
#else	// Little_Endian
#define cpu2le64(x) ((UINT64)(x))
#define le2cpu64(x) ((UINT64)(x))
#define cpu2le32(x) ((UINT32)(x))
#define le2cpu32(x) ((UINT32)(x))
#define cpu2le16(x) ((UINT16)(x))
#define le2cpu16(x) ((UINT16)(x))
#define cpu2be64(x) SWAP64((x))
#define be2cpu64(x) SWAP64((x))
#define cpu2be32(x) SWAP32((x))
#define be2cpu32(x) SWAP32((x))
#define cpu2be16(x) SWAP16((x))
#define be2cpu16(x) SWAP16((x))
#endif

//=====================================================================================
#include "../config/drvNAND_config.h" // [CAUTION]: edit drvNAND_config.h for your platform
//=====================================================================================
#include "drvNAND_err_codes.h"

#define NAND_MFR_FUJITSU	    0x04
#define NAND_MFR_RENESAS	    0x07
#define NAND_MFR_ST			    0x20
#define NAND_MFR_MICRON		    0x2C
#define NAND_MFR_NATIONAL	    0x8F
#define NAND_MFR_TOSHIBA	    0x98
#define NAND_MFR_HYNIX		    0xAD
#define NAND_MFR_SAMSUNG	    0xEC
#define NAND_MFR_MXIC           0xC2
#define NAND_MFR_UNKNOWN        0xFF

//===========================================================
// debug macro
//===========================================================
#define UNFD_FTL_RD_TEST     0
#define UNFD_FTL_WL_TEST     0

#define UNFD_API_DEBUG       0
#define UNFD_FTL_RW_DEBUG    0
#define UNFD_FTL_BREAK_TEST  0

#define UNFD_PRINT_EC        0

#if UNFD_API_DEBUG
#define unfd_api_debug(x)    x
#else
#define unfd_api_debug(X)
#endif

#if UNFD_FTL_RW_DEBUG
#define ftl_rw_debug(x)      x
#else
#define ftl_rw_debug(X)
#endif

#if UNFD_FTL_BREAK_TEST
#define FTL_BREAK_PT_ID      17 // current max:17
#define ftl_break_pt(ID)     if(FTL_BREAK_PT_ID == ID)  {nand_debug(0,1,"ftl_break_pt(%u)",ID);  nand_stop();}
#else
#define FTL_BREAK_PT_ID      -1
#define ftl_break_pt(ID)
#endif

//------------------------------------
#define UNFD_FTL_PHY_GUARD      0
#define UNFD_FTL_MG_TEST        0
#define UNFD_FTL_SPEED_UP       0
#define UNFD_FTL_CHECK_ERROR    1

#if UNFD_FTL_PHY_GUARD
#define UNFD_FTL_MEM_GUARD      1
#else
#define UNFD_FTL_MEM_GUARD      0
#endif
#if UNFD_FTL_SPEED_UP
#undef  UNFD_FTL_CHECK_ERROR
#define UNFD_FTL_CHECK_ERROR    0
#endif

//------------------------------------

//===========================================================
// Partition Info parameters
//===========================================================
typedef UNFD_PACK0 struct _PARTITION_RECORD {

    U16 u16_StartBlk;     // the start block index, reserved for UNFD internal use.
    U16 u16_BlkCnt;       // project team defined
    U16 u16_PartType;     // project team defined, e.g. UNFD_PART_XXX_0
    U16 u16_BackupBlkCnt; // reserved good blocks count for backup, UNFD internal use.
                          // e.g. u16BackupBlkCnt  = u16BlkCnt * 0.03 + 2
} UNFD_PACK1 PARTITION_RECORD_t, *P_PARTITION_RECORD_t;

typedef UNFD_PACK0 struct _PARTITION_INFO {

	U32	u32_ChkSum;
	U16	u16_SpareByteCnt;
	U16	u16_PageByteCnt;
	U16	u16_BlkPageCnt;
	U16	u16_BlkCnt;
	U16	u16_PartCnt;
	U16	u16_UnitByteCnt;
	PARTITION_RECORD_t records[];

} UNFD_PACK1 PARTITION_INFO_t;

typedef UNFD_PACK0 struct _NAND_FLASH_INFO {

	U8	au8_Tag[16];
	U8	u8_IDByteCnt;
	U8	au8_ID[15];
	U32	u32_ChkSum;
	U16	u16_SpareByteCnt;
	U16	u16_PageByteCnt;
	U16	u16_BlkPageCnt;
	U16	u16_BlkCnt;
	U32	u32_Config;
	U16	u16_ECCType;
	U16	u16_SeqAccessTime;
	U8	padding[12];
	U8	u8_Vendor[16];
	U8	u8_PartNumber[16];
	U8  u8_PairPageMapLoc;
	U8  u8_PairPageMapType;
	U8	u8_DQSMode;
	U8	u8_DDRTiming;
	U8	u8_DelayCell;
	//for TV ROM Code
	U8	u8_BL0PBA;
	U8	u8_BL1PBA;
	U8	u8_UBOOTPBA;
	//U8	u8_UBOOT1PBA;
	U8  u8_reserved[20];
    U8  u8_HashPBA[3][2];

} UNFD_PACK1 NAND_FLASH_INFO_t;


typedef UNFD_PACK0 struct _BlK_INFO {

	U8	u8_BadBlkMark;
	U8	u8_PartType;
	U16	u16_BlkAddr;
	U8	au8_Misc[2];
	U8	au8_ECC[10];

} UNFD_PACK1 BLK_INFO_t;


typedef UNFD_PACK0 struct _INIT_BBT {

	U32	u32_ChkSum;
	U16	u16_Cnt;
	U8	au8_BadBlkTbl[];

} UNFD_PACK1 INIT_BBT_t;


typedef UNFD_PACK0 struct _MIU_RECORD {

	U32 u32_RegAddr;
	U32 u32_RegValue;

} UNFD_PACK1 MIU_RECORD_t;

typedef UNFD_PACK0 struct _MIU_PART {

	U32	u32_ChkSum;
	U32	u32_ByteCnt;

	MIU_RECORD_t records[];

} UNFD_PACK1 MIU_PART_t;

typedef struct _PAIRED_PAGE_MAP {

    U16 u16_LSB;
    U16 u16_MSB;

} PAIRED_PAGE_MAP_t, *P_PAIRED_PAGE_MAP_t;

#define UNFD_LOGI_PART		0x8000 // bit-or if the partition needs Wear-Leveling
#define UNFD_HIDDEN_PART	0x4000 // bit-or if this partition is hidden, normally it is set for the LOGI PARTs.

#define UNFD_PART_HWCONFIG		1
#define UNFD_PART_BOOTLOGO		2
#define UNFD_PART_BL			3
#define UNFD_PART_OS			4
#define UNFD_PART_CUS			5
#define UNFD_PART_UBOOT			6
#define UNFD_PART_SECINFO		7
#define UNFD_PART_OTP			8
#define UNFD_PART_RECOVERY		9
#define UNFD_PART_E2PBAK		10
#define UNFD_PART_NVRAMBAK		11
#define UNFD_PART_APANIC		12

//Following is the Logical partition
#define UNFD_PART_E2P0          (0|UNFD_LOGI_PART|UNFD_HIDDEN_PART)
#define UNFD_PART_E2P1          (1|UNFD_LOGI_PART|UNFD_HIDDEN_PART)
#define UNFD_PART_NVRAM0		(2|UNFD_LOGI_PART|UNFD_HIDDEN_PART)
#define UNFD_PART_NVRAM1		(3|UNFD_LOGI_PART|UNFD_HIDDEN_PART)
#define UNFD_PART_SYSTEM		(4|UNFD_LOGI_PART|UNFD_HIDDEN_PART)
#define UNFD_PART_CACHE			(5|UNFD_LOGI_PART|UNFD_HIDDEN_PART)
#define UNFD_PART_DATA			(6|UNFD_LOGI_PART|UNFD_HIDDEN_PART)
//===========================================================
// Logical Disk Info
//===========================================================
typedef struct _DISK_INFO {

    U32 u32_StartSector;
    U32 u32_SectorCnt;
} DISK_INFO_t, *P_DISK_INFO_t;

#define UNFD_MAX_DISK_NUM    16 // [CAUTION]: max logical partition count

#if defined(__VER_UNFD_FTL__)
#include "drvNAND_ftl.h"
#endif
//===========================================================
// driver parameters
//===========================================================
#define NAND_ID_BYTE_CNT     15

#define R_SEQUENCE_003A      1
#define R_SEQUENCE_004A      2
#define R_SEQUENCE_004A30    3
#define R_SEQUENCE_005A30    4

typedef U32 (*ReadSectorsPtr)(U32 , U8 , U8 *, U8 *, U32 );

typedef struct _NAND_DRIVER
{

	U8  au8_ID[NAND_ID_BYTE_CNT];

	//-----------------------------
	// HAL parameters
	//-----------------------------
#if (defined(NC_SEL_FCIE3) && NC_SEL_FCIE3) || (defined(NC_SEL_FCIE5) && NC_SEL_FCIE5)
	#if (defined(NC_SEL_FCIE3) && NC_SEL_FCIE3)
	volatile U16 u16_Reg1B_SdioCtrl;
	#endif
	volatile U16 u16_Reg40_Signal;
	volatile U16 u16_Reg48_Spare;
	volatile U16 u16_Reg49_SpareSize;
	volatile U16 u16_Reg50_EccCtrl;
	volatile U16 u16_Reg57_RELatch;

	#if (defined(NC_SEL_FCIE3) && NC_SEL_FCIE3)
    	volatile U16 u16_Reg2C_SMStatus;
	#elif (defined(NC_SEL_FCIE5) && NC_SEL_FCIE5)
	#if (defined(ENABLE_8BIT_MACRO) && ENABLE_8BIT_MACRO)
	volatile U16 u16_Emmc_Pll_Reg6C;
	#elif (defined(ENABLE_32BIT_MACRO) && ENABLE_32BIT_MACRO)
	volatile U16 u16_Emmc_Pll_Reg09;
	#endif
	#endif
	volatile U16 u16_Reg58_DDRCtrl;
	volatile U16 u16_Reg59_TrrTcs;
	volatile U16 u16_Reg56_HWCmdDelay;
	volatile U16 u16_Reg5A_tWHR_tCLHZ;
	volatile U16 u16_Reg5D_tCWAW_tADL;
	#elif 0
	#endif

	#if defined(FCIE_LFSR) && FCIE_LFSR
	volatile U16 u16_Reg59_LFSRCtrl;
	#endif

	U32 u32_CISRow;
	U32 u32_Clk;
	//-----------------------------
	// NAND Info (listed by their init_sequence)
	//-----------------------------
	U8  u8_WordMode;
	U8  u8_OpCode_RW_AdrCycle;
	U8  u8_Flag_004A30;
	U16 u16_One_Col_Addr;

	U16 u16_BlkPageCnt;
	U16 u16_PageByteCnt;
    U16 u16_SpareByteCnt;
	U16 u16_ECCType;

	//U16 u16_BlkSectorCnt;
	U16 u16_PageSectorCnt;
	U16 u16_SectorByteCnt;
	U16 u16_SectorSpareByteCnt;
	U16 u16_ECCCodeByteCnt;

    U8  u8_BlkPageCntBits;
    //U8  u8_BlkSectorCntBits;
	U8  u8_PageByteCntBits;
	//U8  u8_SpareByteCntBits;
	U8  u8_PageSectorCntBits;
	U8  u8_SectorByteCntBits;
	//U8  u8_SectorSpareByteCntBits;

	//U16 u16_BlkPageCntMask;
	//U16 u16_BlkSectorCntMask;
	//U16 u16_PageByteCntMask;
    //U16 u16_SpareByteCntMask;
	//U16 u16_PageSectorCntMask;
	//U16 u16_SectorByteCntMask;

	U16 u16_NandMode;

	U8  u8_CellType;
	U8  u8_PairPageMapLoc;
	U8	u8_DQSMode;
	U8	u8_DDRTiming;
	U8	u8_DelayCell;
	U8	u8_BL0PBA;
	U8	u8_BL1PBA;
	U8	u8_UBOOTPBA;
	//U8	u8_UBOOT1PBA;
	U8	u8_AddrCycleIdx;	
	U8  u8_HashPBA[3][2];

	NAND_DRIVER_PLAT_CTX PlatCtx_t;

	U8	u8_BitflipThreshold;
	U8  u8_HashPageIdx[2];
	U8  u8_BootVerion;
	U32 u32_BootSize;
	ReadSectorsPtr pReadSectors;		
	/*** Please append new member here ***/


} NAND_DRIVER, *P_NAND_DRIVER;

typedef enum NandHalConfig_e_
{
	NAND_HAL_RAW = 0,
	NAND_HAL_PATCH = 1
} NandHalConfig_e;

//===========================================================
// exposed APIs
//===========================================================
// pub module header
#include "../api/drv_unfd.h"

extern U32 drvNAND_WriteBuf(U8 * pu8_buf, U16 u16_len);
extern U32 drvNAND_ReadBuf(U8* pu8_buf, U16 u16_Len);
extern U32 drvNAND_ReadCmdOOB(U32 u32_PageAddr, U32 u32_Col);
extern U32 drvNAND_ReadStatus(void);
extern U32 drvNAND_CheckECC(int * s32ECCStatus);
extern void drvNAND_GetMtdParts(char *buf);

extern U32 drvNAND_WritePartition(U16 u16_PartType,
								U8 *pu8_DataBuf,
								U32 u32_StartPhySector,
								U32 u32_SectorCnt,
								U32 u32_LogicIdx);
extern U32 drvNAND_ReadPartition(U16 u16_PartType,
								U8 *pu8_DataBuf,
								U32 u32_StartPhySector,
								U32 u32_SectorCnt,
								U32 u32_LogicIdx);
extern U32 drvNAND_ErasePartition(U16 u16_PartType);
extern U32 drvNAND_EraseAllPartitions(void);
extern U32 drvNAND_EraseAll (void);
extern U32 drvNAND_GetCapacity (U16 u16_PartType, U32 *pu32_Cap);

#if defined(UNFD_FTL_WL) && UNFD_FTL_WL
extern U32 drvNAND_WearLeveling(void);
extern U32 drvNAND_WearLeveling1(void);
extern U32 drvNAND_WL_SaveECnt(U8 u8_ECntZoneIndex);
#endif
//===========================================================
// internal used functions
//===========================================================
//#include "drvNAND_utl.h"
extern void *drvNAND_get_DrvContext_address(void);
extern void *drvNAND_get_DrvContext_PartInfo(void);
extern U32 drvNAND_ChkSum(U8 *pu8_Data, U16 u16_ByteCnt);
extern U32 nand_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt);

//---------------------------------------
// HAL functions
//---------------------------------------
#ifdef TV_ROM
extern U32	NC_Init(U8 u8_ReqDDRDetect);
#else
extern U32  NC_Init(void);
#endif
extern U32  NC_ReInit(void);
extern U32  NC_EnableLFSR(void);
extern U32  NC_DisableLFSR(void);
extern U32  NC_PlatformResetPre(void);
extern U32  NC_PlatformResetPost(void);
extern U32  NC_PlatformInit(void);
extern U32  NC_ConfigContext(void);
extern U32  NC_ResetFCIE(void);
extern U32  NC_ReadPages(U32 u32_PhyRowIdx, U8 *pu8_DataBuf, U8 *pu8_SpareBuf, U32 u32_PageCnt);
extern U32  NC_WritePages(U32 u32_PhyRowIdx, U8 *pu8_DataBuf, U8 *pu8_SpareBuf, U32 u32_PageCnt);
extern U32  NC_PageCopy(U32 u32_SrcPhyRowIdx, U32 u32_DstPhyRowIdx, U8 *pu8_DataBuf, U8 *pu8_SpareBuf, U32 u32_PageCnt);
extern U32  NC_ReadSectors(U32 u32_PhyRowIdx, U8 u8_SectorInPage, U8 *pu8_DataBuf, U8 *pu8_SpareBuf, U32 u32_SectorCnt);
extern U32  NC_ReadSectors_IPVerify(U32 u32_PhyRowIdx, U8 u8_SectorInPage, U8 *pu8_DataBuf, U8 *pu8_SpareBuf, U32 u32_SectorCnt);
extern U32  NC_WriteSectors(U32 u32_PhyRowIdx, U8 u8_SectorInPage, U8 *pu8_DataBuf, U8 *pu8_SpareBuf, U32 u32_SectorCnt);
extern U32  NC_WriteSectors_IPVerify(U32 u32_PhyRowIdx, U8 u8_SectorInPage, U8 *pu8_DataBuf, U8 *pu8_SpareBuf, U32 u32_SectorCnt);
extern U32  NC_ReadID(void);
extern U32  NC_ProbeReadSeq(void);
#if defined(FCIE4_DDR) && FCIE4_DDR
extern U32  NC_SetONFISyncMode(void);
extern U32  NC_ProbeIfONFIDDR(void);
extern U32  NC_ProbeIfToggleDDR(void);
extern U32  NC_DetectDDRTiming(void);
extern U32  NC_FCIE4SetInterface(U8 u8_IfDDR, U8 u8_dqs_mode, U8 u8_dqs_delaycell, U8 u8_rd_ddr_timing);
#endif
extern U32  NC_EraseBlk(U32 u32PhyRowIdx);
extern U32  NC_ResetNandFlash(void);
extern void NC_SendCmdForLADebug(void);
extern U32  NC_Read_RandomIn(U32 u32PhyRow, U32 u32Col, U8 *pu8DataBuf, U32 u32DataByteCnt);
extern U32  NC_Write_RandomOut(U32 u32_PhyRow, U32 u32_Col, U8 *pu8_DataBuf, U32 u32_DataByteCnt);
extern U32  NC_GetECCBits(void);
extern U32  NC_WaitComplete(U32 u32_EventReg, U16 u16_WaitEvent, U32 u32_MicroSec);
extern U32  NC_ReadStatus(void);
extern void NC_CheckECC(int *s32ECCStatus);

extern void NC_Config(void);
extern void NC_SetCIFD(U8 *pu8_Buf, U32 u32_CIFDPos, U32 u32_ByteCnt);
extern void NC_GetCIFD(U8 *pu8_Buf, U32 u32_CIFDPos, U32 u32_ByteCnt);
extern void NC_SetCIFD_Const(U8 u8_Data, U32 u32_CIFDPos, U32 u32_ByteCnt);

extern U32  NC_WritePage_RIUMode(U32 u32_PhyRowIdx, U8 *pu8_DataBuf, U8 *pu8_SpareBuf);
extern U32  NC_ReadSector_RIUMode(U32 u32_PhyRowIdx, U8 u8_SectorInPage, U8 *pu8_DataBuf, U8 *pu8_SpareBuf);

extern void NC_ConfigHal(NandHalConfig_e config);

extern U32 drvNAND_init_sem(void);
extern U32 drvNAND_lock_sem(void);
extern U32 drvNAND_unlock_sem(void);

extern void drvNAND_SetAssertPBA(void);
extern U32 drvNAND_IPVerify_Main(void);

extern void nand_switch_sram(U32 u32_Offset);

#ifdef REMAP_PPM_ADDR
extern void nand_remap_ppm_addr(PAIRED_PAGE_MAP_t **pptPairedPageMapSRAM);
#endif

#endif // NAND_DRV_V3

