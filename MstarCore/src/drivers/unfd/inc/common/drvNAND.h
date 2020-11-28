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

#ifndef NAND_DRV_V3
#define NAND_DRV_V3

#ifndef U64
#define U64  unsigned long long
#endif
#ifndef U32
#define U32  unsigned long
#endif
#ifndef U16
#define U16  unsigned short
#endif
#ifndef U8
#define U8   unsigned char
#endif
#ifndef S64
#define S64  signed long long
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
#ifndef NULL
#define NULL (void*)0
#endif

#ifndef UINT16
#define UINT16 U16
#endif
#ifndef UINT32
#define UINT32 U32
#endif
#ifndef UINT64
#define UINT64 U64
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
#else // Little_Endian
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

#define INTER_CMD		0
#define ACT_CMD			1
#define ADDR_CYCLE_CMD	2
#define ACT_DMA_CMD		3			//ACT_SER_DOUT, ACT_SER_DIN,
#define ACT_RAN_CMD		4			//ACT_RAN_DIN, ACT_RAN_DOUT
#define CUST_CMD		5
#define RAN_BYTE_CMD	6

#define NAND_BBT_PAGE_COUNT 8


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

	U32 u32_ChkSum;
	U16	u16_SpareByteCnt;
	U16	u16_PageByteCnt;
	U16	u16_BlkPageCnt;
	U16	u16_BlkCnt;
	U16 u16_PartCnt;
	U16 u16_UnitByteCnt;
	PARTITION_RECORD_t records[];

} UNFD_PACK1 PARTITION_INFO_t;

typedef UNFD_PACK0 struct _DDR_TIMING_GROUP {

	U8	u8_ClkIdx;
	U8	u8_DqsMode;
	U8	u8_DelayCell;
	U8	u8_DdrTiming;

} UNFD_PACK1 DDR_TIMING_GROUP_t;

typedef UNFD_PACK0 struct _NAND_FLASH_INFO {

	U8  au8_Tag[16];
	U8  u8_IDByteCnt;
	U8  au8_ID[15];
	U32 u32_ChkSum;
	U16 u16_SpareByteCnt;
	U16 u16_PageByteCnt;
	U16 u16_BlkPageCnt;
	U16 u16_BlkCnt;
	U32 u32_Config;
	U16 u16_ECCType;
	U16	u16_tRC;
	U8  u8_tRP;
	U8  u8_tREH;
	U8  u8_tREA;
	U8  u8_tRR;
	U16 u16_tADL;
	U16 u16_tRHW;
	U16 u16_tWHR;
	U16 u16_InitBadBlkCnt;
	U8  u8_Vendor[16];
	U8  u8_PartNumber[16];
	U8  u8_PairPageMapLoc;
	U8  u8_PairPageMapType;
	U16 u16_tCCS;
	U8  u8_tCS;
	//for TV ROM Code
	U8  u8_BL0PBA;
	U8  u8_BL1PBA;
	U8  u8_UBOOTPBA;
	U16	u16_tWC;
	U8  u8_tWP;
	U8  u8_tWH;
	U16 u16_tCWAW;
	U8 u8_tCLHZ;
	U8 u8_AddrCycleIdx;
	DDR_TIMING_GROUP_t tDefaultDDR;
	DDR_TIMING_GROUP_t tMaxDDR;
	DDR_TIMING_GROUP_t tMinDDR;
	U8  u8_HashPBA[3][2];
	U16  u16_tWW;
	U8	u8_ReadRetryType;
	U8  u8_BitflipThreshold;
	U8	u8_Hash0PageIdx;
	U8	u8_Hash1PageIdx;
	U32	 u32_BootSize;	
	U16	u16_BBtPageCheckCount;
	U16	u16_BBtPageIdx[NAND_BBT_PAGE_COUNT];
	U16	u16_BBtMarker[NAND_BBT_PAGE_COUNT];
} UNFD_PACK1 NAND_FLASH_INFO_t;


typedef UNFD_PACK0 struct _MLC_BACKUP_BLK_SPARE_INFO
{
	U8 u8_BadBlkMarker;
	U16 u16_BackupPBA;
} UNFD_PACK1 MBBS_INFO_t;


typedef UNFD_PACK0 struct _BlK_INFO {

	U8  u8_BadBlkMark;
	U8  u8_PartType;
	U16 u16_BlkAddr;
	U8  au8_Misc[2];
	U8  au8_ECC[10];

} UNFD_PACK1 BLK_INFO_t;


typedef UNFD_PACK0 struct _INIT_BBT {

	U32 u32_ChkSum;
	U16 u16_Cnt;
	U8  au8_BadBlkTbl[];

} UNFD_PACK1 INIT_BBT_t;


typedef UNFD_PACK0 struct _MIU_RECORD {

	U32 u32_RegAddr;
	U32 u32_RegValue;

} UNFD_PACK1 MIU_RECORD_t;

typedef UNFD_PACK0 struct _MIU_PART {

	U32 u32_ChkSum;
	U32 u32_ByteCnt;

	MIU_RECORD_t records[];

} UNFD_PACK1 MIU_PART_t;


/*
BIT :	[63:32]	|	[31: 13]	|	[12: 3]	|	[2:1]		|	[0]
	MIU_		Reserved		Page_		MIU_		End_
	Address					Count		SEL			Flag
*/
typedef  struct  _ADMA_DESC{
	U32 u32_EndFlag : 1;
	U32 u32_MIUSel : 2;
	U32 u32_PageCnt : 10;
	U32 			: 19;
	U32 u32_Address;
} ADMA_DESC_t;


typedef  struct  _ZDEC_DESC_{
	U32 u32_EndFlag : 1;
	U32 u32_MIUSel : 2;
	U32 u32_PageCnt : 10;
	U32 			: 19;
	U32 u32_Address;
} ZDecDescriptor_t;


#define TSB_REGISTER_NUMBER		4
#define TSB_READRETRY_TIME		6
#define 	SAMSUNG_REGISTER_NUMBER 	4
#define SAMSUNG_READRETRY_TIME		15
#define MICRON_REIGSTER_NUMBER	4
#define MCIRON_READRETRY_TIME	4

#define HYNIX20nm32GBMLC_REGISTER_NUMBER		8
#define HYNIX20nm32GBMLC_READRETRY_TIME		8


typedef UNFD_PACK0 struct _READ_RETRY {
	U8  u8_CustRegNo;
	U8* pu8_CustRegTable;
	U8  u8_DefaultValueOffset;
	U8  u8_MaxRetryTime;
	U8  u8_ByteLenPerCmd;
	U8  ***pppu8_RetryRegValue;
	U8  u8_DefaultValueRestore;
	U8  u8_SetCmdLen;
	U8* pu8_SetCmdTypeSeq;
	U8* pu8_SetCmdValueSeq;
	U8  u8_GetCmdLen;
	U8* pu8_GetCmdTypeSeq;
	U8* pu8_GetCmdValueSeq;
} UNFD_PACK1 READ_RETRY_t;

#define UNFD_LOGI_PART    0x8000 // bit-or if the partition needs Wear-Leveling
#define UNFD_HIDDEN_PART  0x4000 // bit-or if this partition is hidden, normally it is set for the LOGI PARTs.

#define UNFD_PART_HWCONFIG		1
#define UNFD_PART_BOOTLOGO      2
#define UNFD_PART_BL      3
#define UNFD_PART_OS      4
#define UNFD_PART_CUS     5
#define UNFD_PART_UBOOT     6
#define UNFD_PART_SECINFO		7
#define UNFD_PART_OTP			8
#define UNFD_PART_RECOVERY		9
#define UNFD_PART_E2PBAK		10
#define UNFD_PART_NVRAMBAK		11
#define UNFD_PART_APANIC		12
#define UNFD_PART_ENV			13
#define UNFD_PART_MISC			14
#define UNFD_PART_TBL			15
#define UNFD_PART_CTRL			16
#define UNFD_PART_FDD			17
#define UNFD_PART_TDD			18
#define UNFD_PART_UBIRO			19

//Following is the Logical partition
#define UNFD_PART_E2P0          (0|UNFD_LOGI_PART|UNFD_HIDDEN_PART)
#define UNFD_PART_E2P1          (1|UNFD_LOGI_PART|UNFD_HIDDEN_PART)
#define UNFD_PART_NVRAM0		(2|UNFD_LOGI_PART|UNFD_HIDDEN_PART)
#define UNFD_PART_NVRAM1		(3|UNFD_LOGI_PART|UNFD_HIDDEN_PART)
#define UNFD_PART_SYSTEM		(4|UNFD_LOGI_PART|UNFD_HIDDEN_PART)
#define UNFD_PART_CACHE			(5|UNFD_LOGI_PART|UNFD_HIDDEN_PART)
#define UNFD_PART_DATA			(6|UNFD_LOGI_PART|UNFD_HIDDEN_PART)

#define UNFD_LOGI_PART_START	UNFD_PART_E2P0
#define UNFD_LOGI_PART_END		UNFD_PART_DATA

//===========================================================
// Logical Disk Info
//===========================================================
typedef struct _DISK_INFO {

	U32 u32_StartSector;
	U32 u32_SectorCnt;
} DISK_INFO_t, *P_DISK_INFO_t;

#define UNFD_MAX_DISK_NUM    16 // [CAUTION]: max logical partition count

#include "drvNAND_ftl.h"

//===========================================================
// driver parameters
//===========================================================
#define NAND_ID_BYTE_CNT     15

#define R_SEQUENCE_003A      1
#define R_SEQUENCE_004A      2
#define R_SEQUENCE_004A30    3
#define R_SEQUENCE_005A30    4

//bit14:13 of u32_Config, 00:Normal, 01:Cache, 10:MultiP, 11:MultiP cache
#define UNFD_RW_NORMAL				0
#define UNFD_RW_CACHE				1
#define UNFD_RW_MULTIPLANE			2
#define UNFD_RW_MULTIPLANE_CACHE	3

typedef struct _NAND_DRIVER
{
	//-------------
	U16 u16_mem_w0; // MEM_GUARD_W0
	//-------------

	U8  au8_ID[NAND_ID_BYTE_CNT];
	U8  u8_IDByteCnt;

	U8  u8_CISBlk;
	U8  u8_CIS0_EccStatus;

	//-----------------------------
	// HAL parameters
	//-----------------------------
    #if (defined(NC_SEL_FCIE3) && NC_SEL_FCIE3) || (defined(NC_SEL_FCIE5) && NC_SEL_FCIE5)
	volatile U16 u16_Reg1B_SdioCtrl;
	volatile U16 u16_Reg40_Signal;
	volatile U16 u16_Reg48_Spare;
	volatile U16 u16_Reg49_SpareSize;
	volatile U16 u16_Reg50_EccCtrl;
	volatile U16 u16_Reg57_RELatch;

	volatile U16 u16_Reg2C_SMStatus;
	volatile U16 u16_Reg58_DDRCtrl;
	volatile U16 u16_Reg5A_tWHR_tCLHZ;
	volatile U16 u16_Reg5D_tCWAW_tADL;
	#endif
	
	#if defined(NC_SEL_FCIE5) && NC_SEL_FCIE5
	volatile U16 u16_EmmcPllReg62_LatWin;
	volatile U16 u16_EmmcPllReg6c_DqsSel;
	volatile U16 u16_EmmcPllReg6D_DdrSdrCtrl;
	volatile U16 u16_EmmcPllReg09_PhaseSel;
	#endif

	#if defined(NC_HWCMD_DELAY) && NC_HWCMD_DELAY
	volatile U16 u16_Reg56_Rand_W_Cmd;
	#endif

	#if defined(FCIE_LFSR) && FCIE_LFSR|| (defined(NC_TRR_TCS) && NC_TRR_TCS)
	volatile U16 u16_Reg59_LFSRCtrl;
	#endif

	#if defined(FCIE4_DDR) && FCIE4_DDR || defined(DDR_NAND_SUPPORT) && DDR_NAND_SUPPORT
	DDR_TIMING_GROUP_t tDefaultDDR;
	DDR_TIMING_GROUP_t tMaxDDR;
	DDR_TIMING_GROUP_t tMinDDR;
	#endif

	#if defined(REG_ANALOG_DELAY_CELL)
	volatile U16 u16_Analog_dqs_delaycell;
	#endif

    #if defined(FCIE4_DDR_EMMC_PLL) && FCIE4_DDR_EMMC_PLL
    U16 u16_Emmc_Pll_Reg09;
    #endif

	U8	u8_PadMode;
	U8	u8_HasPNI;
	#if defined(NC_SEL_FCIE5) && NC_SEL_FCIE5
	U8	u8_MacroType;
	#endif
	U32 u32_Clk;
	U32 u32_minClk;
	//-----------------------------
	// NAND Info (listed by their init_sequence)
	//-----------------------------
	U8  u8_WordMode;
	U8  u8_OpCode_RW_AdrCycle;
	U8  u8_OpCode_Erase_AdrCycle;
	U8  u8_Flag_004A30;
	U16 u16_One_Col_Addr;

	U16 u16_BlkCnt;
	U16 u16_BlkPageCnt;
	U16 u16_PageByteCnt;
	U16 u16_SpareByteCnt;
	U16 u16_BitflipThreshold;
	U16 u16_ECCCorretableBit;
	U16 u16_ECCType;
	U32 u32_Config;
	U16	u16_tRC;
	U8  u8_tRP;
	U8  u8_tREH;
	U8  u8_tREA;
	U8  u8_tRR;
	U16 u16_tADL;
	U16 u16_tRHW;
	U16 u16_tWHR;
	U16 u16_tCCS;
	U8  u8_tCS;
	U16	u16_tWC;
	U8  u8_tWP;
	U8  u8_tWH;
	U16 u16_tCWAW;
	U8	u8_tCLHZ;
	U8 	u8_AddrCycleIdx;
	U16  u16_tWW;
	U8  u8_Vendor[16];
	U8  u8_PartNumber[16];

	U8  u8_CellType;	// bit0 of u32_Config, 0:SLC, 1:MLC
	U8  u8_BadBlkMarker;// bit3:1 of u32_Config, 0:Column0, ...
	U8  u8_PlaneCnt;	// bit6:4 of u32_Config, 0:P1, 1:P2, ...
	U8	u8_RequireRandomizer;	// bit8		of u32_Config, 0: disable, 1: enable
	U8	u8_NANDInterface;//bit10:9 of u32_Config, 0:SDR 1:Toggle 2: ONFI
	U8  u8_CacheProgram;    // bit12:11 of u32_Config, 0 normal, 1 cache, 2 multi-plane, 3 multi-plane cache
	U8  u8_CacheRead;       // bit14:13 of u32_Config, 0 normal, 1 cache, 2 multi-plane, 3 multi-plane cache
	U8  u8_RequireReadRetry;	// bit15	of u32_Config, 0: no retry 1: read retry
	U8  u8_PairPageMapLoc;
	U16 u16_BlkSectorCnt;
	U16 u16_PageSectorCnt;
	U16 u16_SectorByteCnt;
	U16 u16_SectorSpareByteCnt;
	U16 u16_ECCCodeByteCnt;

	U8  u8_BlkPageCntBits;
	U8  u8_BlkSectorCntBits;
	U8  u8_PageByteCntBits;
	//U8  u8_SpareByteCntBits;
	U8  u8_PageSectorCntBits;
	U8  u8_SectorByteCntBits;
	//U8  u8_SectorSpareByteCntBits;

	U16 u16_BlkPageCntMask;
	U16 u16_BlkSectorCntMask;
	U16 u16_PageByteCntMask;
	  //U16 u16_SpareByteCntMask;
	U16 u16_PageSectorCntMask;
	U16 u16_SectorByteCntMask;

	U16 u16_CISPBA[2];
	U8  u8_BL0PBA;
	U8  u8_BL1PBA;
	U8  u8_UBOOTPBA;
	U8  u8_HashPBA[3][2];
	U8	u8_Hash0PageIdx;
	U8	u8_Hash1PageIdx;
	U32	u32_BootSize;
	U16	u16_BBtPageCheckCount;
	U16	u16_BBtPageIdx[NAND_BBT_PAGE_COUNT];
	U16	u16_BBtMarker[NAND_BBT_PAGE_COUNT];

	//-------------
	U16 u16_mem_w1; // MEM_GUARD_W1
	//-------------

	NAND_DRIVER_PLAT_CTX PlatCtx_t;
	//-----------------------------
	// Partition Info
	//-----------------------------
	PARTITION_INFO_t *pPartInfo;

	//-----------------------------
	// Read Retry Info
	//-----------------------------
	U8  u8_ReadRetryType;
	READ_RETRY_t ReadRetry_t;
	U8 **ppu8_ReadRetryDefault;

	#if defined(__VER_UNFD_FTL__) && __VER_UNFD_FTL__
	  //-----------------------------
	// UNFD parameters
	//-----------------------------
	DISK_INFO_t DiskInfo_t[UNFD_MAX_DISK_NUM];
	U16 u16_FirstPBA_AssertDebug;
	U16 u16_FirstPBA_LogiArea;
	U16 u16_RootBlkPhyIdx;
	U16 u16_LogiDataBlkCnt, u16_LogiFreeBlkCnt, u16_BadBlkCnt;

	//-------------
	U16 u16_mem_w2; // MEM_GUARD_W2
	//-------------

	  // for first zone (the first 1000 logi blocks)
	U16 u16_FirstPBA_Zone0; // = u16_FirstPBA_LogiArea + UNFD_ROOT_BLK_CNT
	U16 au16_L2P_0[1024];
	#if UNFD_FTL_FMAP
	U16 au16_FBIdx_0[UNFD_FREE_BLK_CNT_PER_1K+FMAP_MAX_LBA_CNT*FMAP_SPACE_FACTOR];
	#else
	U16 au16_FBIdx_0[UNFD_FREE_BLK_CNT_PER_1K]; // free blk must be physical index
	#endif
	U8  u8_FBHead_0, u8_FBTail_0, u8_FBCnt_0, u8_FBMaxCnt_0;
	U16 u16_Zone0LBACnt;

	//-------------
	U16 u16_mem_w3; // MEM_GUARD_W3
	//-------------

	// for the folowing zones
	U16 u16_FirstPBA_Zone1;
	U16 au16_ActiveZoneIdx[MAX_LUT_CNT-1];
	U16 au16_L2P_1[(MAX_LUT_CNT-1)*1024];
	U16 au16_FBIdx_1[(MAX_LUT_CNT-1)*UNFD_FREE_BLK_CNT_PER_1K]; // free blk must be physical index
	U8  u8_FBHead_1, u8_FBTail_1, u8_FBCnt_1;
	U8  u8_Zone1SubZoneCnt, u8_Zone1LUTFlag;

	//-------------
	U16 u16_mem_w4; // MEM_GUARD_W4
	//-------------

	#if UNFD_FTL_WBQ
	WBQ_t aWBQ_t[MAX_WBQ_CNT];
	U16   u16_PPB, u16_PPB_Page;
	#endif

	//-------------
	U16 u16_mem_w5; // MEM_GUARD_W5
	//-------------

	#if UNFD_FTL_FMAP
	  U16 u16_FM_FirstLBA, u16_FM_LBACnt, u16_FM_PBACnt;
	U8  u8_FM_PBAPageCnt;
	// R: use au16_FM_BL2P + au8_FM_PL2P
	// W: use au16_FM_BL2P + au8_FM_FreePagePos,
	//    update au16_FM_BL2P, au8_FM_PL2P, au8_FM_FreePagePos
	U16 au16_FM_BL2P[FMAP_MAX_LBA_CNT][FMAP_SPACE_FACTOR]; // value: PBA
	U8  au8_FM_FreePagePos[FMAP_MAX_LBA_CNT][FMAP_SPACE_FACTOR]; // value: 0 ~ BlkPageCnt
	U8  au8_FM_PL2P[FMAP_MAX_LBA_CNT][FMAP_MAX_BLKPAGE_CNT]; // value: 0 ~ BlkPageCnt
	U8  u8_FM_init;
	#endif

	//-------------
	U16 u16_mem_w6; // MEM_GUARD_W6
	//-------------

	#if UNFD_FTL_RD || NAND_BLD_LD_OS
	  volatile U16 u16_RD_SrcPBA; // source blk
	  volatile U8  u8_RD_ECCBitsCnt, u8_RD_ActiveFlag;
	U16 u16_RDB, u16_RDB_Page; // store RD info for physical area

	#if (defined(BLD_LD_OS_RD)&&BLD_LD_OS_RD)
	  U16 u16_RD_FreeBlk;
	#endif

	#if UNFD_FTL_RD_TEST
	U16 u16_RD_TestCnt;
	#endif
	#endif

	//-------------
	U16 u16_mem_w7; // MEM_GUARD_W7
	//-------------

	#if UNFD_FTL_WL
	U16 au16_WL_ECntPBA[MAX_LUT_CNT];
	U16 au16_WL_ECntPBA_Page[MAX_LUT_CNT];
	U32 au32_ZoneTotalECnt[MAX_LUT_CNT];

	#if UNFD_FTL_WL_TEST
	U16 u16_WL_TestCnt;
	#endif
	#endif
	#endif
	//-----------------------------
	#if IF_IP_VERIFY
	U8 u8_IfECCTesting;
	#endif

	volatile U16 u16_Test0, u16_Test1;

	  //-------------
	volatile U32 u32_mem_stack_adr,  u32_mem_stack_dat;
	volatile U32 u32_mem_stack1_adr, u32_mem_stack1_dat;

	U16 u16_mem_w8; // MEM_GUARD_W8
	//-------------
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


extern U32 drvNAND_WritePartition(U32 u32_PartNo, U32 u32_StartPhySector,
                  U8 *pu8_DataBuf, U32 u32_SectorCnt);
extern U32 drvNAND_ReadPartition(U32 u32_PartNo, U32 u32_StartPhySector,
                  U8 *pu8_DataBuf, U32 u32_SectorCnt);

#if UNFD_FTL_WL
extern U32 drvNAND_WearLeveling(void);
extern U32 drvNAND_WearLeveling1(void);
extern U32 drvNAND_WL_SaveECnt(U8 u8_ECntZoneIndex);
#endif
//===========================================================
// internal used functions
//===========================================================
#include "drvNAND_utl.h"
extern void *drvNAND_get_DrvContext_address(void);
extern void *drvNAND_get_DrvContext_PartInfo(void);
extern U32 drvNAND_ChkSum(U8 *pu8_Data, U16 u16_ByteCnt);

//---------------------------------------
// HAL functions
//---------------------------------------
extern U32  NC_Init(void);
extern U32  NC_RegInit(void);
extern void NC_ReConfig(void);
extern U32  NC_EnableLFSR(void);
extern U32  NC_DisableLFSR(void);
extern U32  NC_PlatformResetPre(void);
extern U32  NC_PlatformResetPost(void);
extern U32  NC_PlatformInit(void);
extern U32  NC_ConfigNandFlashContext(void);
extern U32  NC_ResetFCIE(void);
extern U32  NC_ReadPages(U32 u32_PhyRowIdx, U8 *pu8_DataBuf, U8 *pu8_SpareBuf, U32 u32_PageCnt);
extern U32  NC_WritePages(U32 u32_PhyRowIdx, U8 *pu8_DataBuf, U8 *pu8_SpareBuf, U32 u32_PageCnt);
extern U32  NC_PageCopy(U32 u32_SrcPhyRowIdx, U32 u32_DstPhyRowIdx, U8 *pu8_DataBuf, U8 *pu8_SpareBuf, U32 u32_PageCnt);
extern U32  NC_ReadSectors(U32 u32_PhyRowIdx, U8 u8_SectorInPage, U8 *pu8_DataBuf, U8 *pu8_SpareBuf, U32 u32_SectorCnt);
extern U32  NC_WriteSectors(U32 u32_PhyRowIdx, U8 u8_SectorInPage, U8 *pu8_DataBuf, U8 *pu8_SpareBuf, U32 u32_SectorCnt);
extern U32  NC_ReadID(void);
extern U32  NC_ProbeReadSeq(void);
#if defined(FCIE4_DDR) && FCIE4_DDR
extern U32  NC_ReadToggleParamPage(void);
extern U32  NC_ReadONFIParamPage(void);
extern U32  NC_SetONFISyncMode(void);
extern U32  NC_ProbeDDRNAND(void);
extern U32  NC_ProbeIfONFIDDR(void);
extern U32  NC_ProbeIfToggleDDR(void);
extern U32  NC_DetectDDRTiming(void);
extern U32  NC_FCIE4SetInterface(U8 u8_IfDDR, U8 u8_dqs_mode, U8 u8_dqs_delaycell, U8 u8_rd_ddr_timing);
extern U32  NC_FCIE4SetInterface_EMMC_PLL(U8 u8_IfDDR, U8 u8_dll_phase_sel, U8 u8_rd_ddr_timing);
#endif

#if (defined(NC_SEL_FCIE5) && NC_SEL_FCIE5) && (defined(DDR_NAND_SUPPORT) && DDR_NAND_SUPPORT)
extern U32  NC_ReadToggleParamPage(void);
extern U32  NC_ReadONFIParamPage(void);
extern U32  NC_SetONFISyncMode(void);
extern U32  NC_ProbeIfONFIDDR(void);
extern U32  NC_ProbeIfToggleDDR(void);
extern U32  NC_DetectDDRTiming(void);
extern U32  NC_FCIE5SetInterface(U8 u8_IfDDR, U8 u8_dqs_mode, U8 u8_dqs_delaycell, U8 u8_rd_ddr_timing);

#endif

extern U32  NC_EraseBlk(U32 u32PhyRowIdx);
extern U32  NC_ResetNandFlash(void);
extern void NC_SendCmdForLADebug(void);
extern U32  NC_Read_RandomIn(U32 u32PhyRow, U32 u32Col, U8 *pu8DataBuf, U32 u32DataByteCnt);
extern U32  NC_Write_RandomOut(U32 u32_PhyRow, U32 u32_Col, U8 *pu8_DataBuf, U32 u32_DataByteCnt);
extern U32  NC_Read_RandomIn_MIU(U32 u32PhyRow, U32 u32Col, U8 *pu8DataBuf, U32 u32DataByteCnt);
extern U32  NC_Write_RandomOut_MIU(U32 u32_PhyRow, U32 u32_Col, U8 *pu8_DataBuf, U32 u32_DataByteCnt);
extern U32  NC_GetECCBits(void);
extern U32  NC_WaitComplete(U16 u16_WaitEvent, U32 u32_MicroSec);
extern U32  NC_ReadStatus(void);
extern void NC_CheckECC(int *s32ECCStatus);

extern void NC_Config(void);
extern void NC_SetCIFD(U8 *pu8_Buf, U32 u32_CIFDPos, U32 u32_ByteCnt);
extern void NC_GetCIFD(U8 *pu8_Buf, U32 u32_CIFDPos, U32 u32_ByteCnt);
extern void NC_SetCIFD_Const(U8 u8_Data, U32 u32_CIFDPos, U32 u32_ByteCnt);
extern void NC_GetRBufCIFD(U8 *pu8_Buf, U32 u32_CIFDPos, U32 u32_ByteCnt);


extern U32  NC_WritePage_RIUMode(U32 u32_PhyRowIdx, U8 *pu8_DataBuf, U8 *pu8_SpareBuf);
extern U32  NC_ReadSector_RIUMode(U32 u32_PhyRowIdx, U8 u8_SectorInPage, U8 *pu8_DataBuf, U8 *pu8_SpareBuf);

extern void NC_ConfigHal(NandHalConfig_e config);
extern U32 NC_WritePages2P(U32 u32_PlaneRowIdx, U8 *pu8_DataBuf, U8 *pu8_SpareBuf, U32 u32_PageCnt);
extern U32 NC_EraseBlk2P(U32 u32_PlaneRowIdx);

extern U32 drvNAND_init_sem(void);
extern U32 drvNAND_lock_sem(void);
extern U32 drvNAND_unlock_sem(void);

extern void drvNAND_SetAssertPBA(void);
extern U32 drvNAND_IPVerify_Main(void);
extern U32 NCTEST_ReadLoopInitData(U32 u32_StartRowIdx);
extern U32 NCTEST_ReadLoop(U32 u32_StartRowIdx);


//Read Retry

extern void NC_SetupReadRetryCmd(void);
extern U32 NC_GetRegDefaultValue(void);

extern U32 NC_GetReadRetryRegValue(U8** ppu8_RegisterValue);


extern U32  NC_ADMAReadPages(U32 u32_PhyRowIdx, U8 *pu8_DataBuf, U8 *pu8_SpareBuf, U32 u32_PageCnt, U8 u8_Zdec);
extern U32  NC_ADMAWritePages(U32 u32_PhyRowIdx, U8 *pu8_DataBuf, U8 *pu8_SpareBuf, U32 u32_PageCnt);

#endif // NAND_DRV_V3

