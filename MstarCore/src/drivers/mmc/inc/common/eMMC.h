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

#ifndef eMMC_DRIVER_H
#define eMMC_DRIVER_H

//=====================================================================================
#include "eMMC_config.h" // [CAUTION]: edit eMMC_config.h for your platform
//=====================================================================================
#include "eMMC_err_codes.h"

#define eMMC_DRIVER_VERSION   3 // used to sync with other SW stages (e.g. linux kernel)

//===========================================================
// debug macro
//===========================================================
extern U32 gu32_eMMCDrvExtFlag;

#define eMMCDRV_EXTFLAG_DISABLE_LOG   BIT0
#define eMMC_DISABLE_LOG(yes)    \
	do{ \
		if(yes)  gu32_eMMCDrvExtFlag |= eMMCDRV_EXTFLAG_DISABLE_LOG; \
	    else     gu32_eMMCDrvExtFlag &= ~eMMCDRV_EXTFLAG_DISABLE_LOG;\
	}while(0);
#define eMMC_IF_DISABLE_LOG()    \
	(gu32_eMMCDrvExtFlag & eMMCDRV_EXTFLAG_DISABLE_LOG)

#define eMMCDRV_EXTFLAG_BKG_SCAN      BIT1 // for Irwin
#define eMMC_SET_BKG_SCAN_HS200()  gu32_eMMCDrvExtFlag |= eMMCDRV_EXTFLAG_BKG_SCAN;
#define eMMC_CLR_BKG_SCAN_HS200()  gu32_eMMCDrvExtFlag &= ~eMMCDRV_EXTFLAG_BKG_SCAN;
#define eMMC_CHK_BKG_SCAN_HS200()  (gu32_eMMCDrvExtFlag & eMMCDRV_EXTFLAG_BKG_SCAN)

#define eMMCDRV_EXTFLAG_DISABLE_RETRY   BIT2
#define eMMC_DISABLE_RETRY(yes)    \
	do{ \
		if(yes)  gu32_eMMCDrvExtFlag |= eMMCDRV_EXTFLAG_DISABLE_RETRY; \
	    else     gu32_eMMCDrvExtFlag &= ~eMMCDRV_EXTFLAG_DISABLE_RETRY;\
	}while(0);
#define eMMC_IF_DISABLE_RETRY()    \
	((gu32_eMMCDrvExtFlag & eMMCDRV_EXTFLAG_DISABLE_RETRY) || eMMC_IF_TUNING_TTABLE())

//===========================================================
// macro for Spec.
//===========================================================
#define ADDRESSING_MODE_BYTE      1 // 1 byte
#define ADDRESSING_MODE_SECTOR    2 // 512 bytes
#define ADDRESSING_MODE_4KB       3 // 4KB bytes

#define eMMC_DEVTYPE_HS400_1_8V   BIT6 // ECSD[196]
#define eMMC_DEVTYPE_HS200_1_8V   BIT4
#define eMMC_DEVTYPE_DDR          BIT2
#define eMMC_DEVTYPE_ALL          (eMMC_DEVTYPE_HS400_1_8V|eMMC_DEVTYPE_HS200_1_8V|eMMC_DEVTYPE_DDR)

#define eMMC_SPEED_OLD            0 // ECSD[185]
#define eMMC_SPEED_HIGH           1
#define eMMC_SPEED_HS200          2
#define eMMC_SPEED_HS400          3

#define eMMC_DRIVING_TYPE0	      0 // x1
#define eMMC_DRIVING_TYPE1	      1 // x1.5
#define eMMC_DRIVING_TYPE2	      2 // x0.75
#define eMMC_DRIVING_TYPE3	      3 // x0.5
#define eMMC_DRIVING_TYPE4	      4 // x1.2

#define eMMC_FLAG_TRIM            BIT0
#define eMMC_FLAG_HPI_CMD12       BIT1
#define eMMC_FLAG_HPI_CMD13       BIT2

#define eMMC_PwrOffNotif_OFF      0
#define eMMC_PwrOffNotif_ON       1
#define eMMC_PwrOffNotif_SHORT    2
#define eMMC_PwrOffNotif_LONG     3

//-------------------------------------------------------
// Devices has to be in 512B block length mode by default
// after power-on, or software reset.
//-------------------------------------------------------
#define eMMC_SECTOR_512BYTE       0x200
#define eMMC_SECTOR_512BYTE_BITS  9
#define eMMC_SECTOR_512BYTE_MASK  (eMMC_SECTOR_512BYTE-1)

#define eMMC_SECTOR_BUF_16KB      (eMMC_SECTOR_512BYTE * 0x20)

#define eMMC_SECTOR_BYTECNT       eMMC_SECTOR_512BYTE
#define eMMC_SECTOR_BYTECNT_BITS  eMMC_SECTOR_512BYTE_BITS
//-------------------------------------------------------

#define eMMC_ExtCSD_SetBit        1
#define eMMC_ExtCSD_ClrBit        2
#define eMMC_ExtCSD_WByte         3

#define eMMC_CMD_BYTE_CNT         5
#define eMMC_R1_BYTE_CNT          5
#define eMMC_R1b_BYTE_CNT         5
#define eMMC_R2_BYTE_CNT          16
#define eMMC_R3_BYTE_CNT          5
#define eMMC_R4_BYTE_CNT          5
#define eMMC_R5_BYTE_CNT          5
#define eMMC_MAX_RSP_BYTE_CNT     eMMC_R2_BYTE_CNT

// ExtCSD[171]
#define PERM_WP_EN    BIT2
#define PWR_WP_EN     BIT0

// ExtCSD[173]
#define SEC_WP_SEL   BIT7
#define PWR_WP_DIS   BIT6
#define PERM_WP_DIS  BIT4
#define PERM_WP_SEL  BIT3
#define PERM_WP_EN   BIT2
#define PWR_WP_SEL   BIT1
#define PWR_WP_EN    BIT0

//===========================================================
// Partition Info parameters
//===========================================================

// internal data Sector Address
#define eMMC_ID_BYTE_CNT           15
#define eMMC_ID_FROM_CID_BYTE_CNT  10
#define eMMC_ID_DEFAULT_BYTE_CNT   11 // last byte means n GB


//===========================================================
// DDR Timing Table
//===========================================================
typedef eMMC_PACK0 struct _eMMC_FCIE_DDRT_PARAM {

    U8 u8_DQS, u8_Cell;

} eMMC_PACK1 eMMC_FCIE_DDRT_PARAM_t;


typedef eMMC_PACK0 struct _eMMC_FCIE_DDRT_WINDOW {

    U8 u8_Cnt;
	// DQS uses index, not reg value (see code)
	eMMC_FCIE_DDRT_PARAM_t aParam[2];
	U8 au8_DQSTryCellCnt[(BIT_DQS_MODE_MASK>>BIT_DQS_MDOE_SHIFT)+1];
	U8 au8_DQSValidCellCnt[(BIT_DQS_MODE_MASK>>BIT_DQS_MDOE_SHIFT)+1];

} eMMC_PACK1 eMMC_FCIE_DDRT_WINDOW_t;


typedef eMMC_PACK0 struct _eMMC_FCIE_DDRT_SET {

    U8 u8_Clk;
	eMMC_FCIE_DDRT_PARAM_t Param; // register values

} eMMC_PACK1 eMMC_FCIE_DDRT_SET_t;


#define eMMC_FCIE_DDRT_SET_CNT  12
#define eMMC_TIMING_SET_MAX      0
#define eMMC_TIMING_SET_MIN      1

// ----------------------------------------------
typedef eMMC_PACK0 struct _eMMC_FCIE_DDRT_TABLE {

	U8 u8_SetCnt, u8_CurSetIdx;

	#if !(defined(ENABLE_eMMC_ATOP) && ENABLE_eMMC_ATOP)
	// DDR48 (digital macro)
	eMMC_FCIE_DDRT_SET_t Set[eMMC_FCIE_DDRT_SET_CNT];
	#else
	// ATOP (for  DDR52, HS200, HS400)
	eMMC_FCIE_ATOP_SET_t Set[1];//eMMC_FCIE_VALID_CLK_CNT];
	#endif

	U32 u32_ChkSum; // put in the last
	U32 u32_VerNo; // for auto update

} eMMC_PACK1 eMMC_FCIE_TIMING_TABLE_t;

#define REG_OP_W    1
#define REG_OP_CLRBIT  2    
#define REG_OP_SETBIT  3

typedef eMMC_PACK0 struct _eMMC_FCIE_REG_SET {      //total 10 bytes
    U32 u32_RegAddress;             //(BANK_ADDRESS + REGISTER OFFSET ) << 2
    U16 u16_RegValue;
    U16 u16_RegMask;
    U16 u16_OpCode;
} eMMC_PACK1 eMMC_FCIE_REG_SET_t;

typedef eMMC_PACK0 struct _eMMC_FCIE_GEN_TIMING_TABLE {
    U32 u32_ChkSum;
	U32 u32_VerNo; // for auto update
    U32 u32_Clk;    
    U8 u8_SpeedMode;
    U8 u8_CurSetIdx;
    U8 u8_RegisterCnt;
    U8 u8_SetCnt;
    U8 au8_CID[eMMC_MAX_RSP_BYTE_CNT];
    U32 u32_Dummy[6];      //for extension
    eMMC_FCIE_REG_SET_t RegSet[45]; //at most 45 register set
} eMMC_PACK1 eMMC_FCIE_GEN_TIMING_TABLE_t;


#if defined(CONFIG_EMMC_FORCE_DDR52)
#define eMMC_TIMING_TABLE_VERSION        2
#else
#define eMMC_TIMING_TABLE_VERSION        6 // for CL > 1047810
#endif
#define eMMC_TIMING_TABLE_CHKSUM_OFFSET  8

//===========================================================
// life test
//===========================================================
typedef eMMC_PACK0 struct _eMMC_FCIE_LIFE_TEST_BYTES_CNT {
	U32 u32_LIFETIME_TEST_FIXED_GBytes;
    U32 u32_LIFETIME_TEST_FILLED_GBytes;
    U32 u32_LIFETIME_TEST_RANDOM_GBytes;
	U32 u32_ChkSum; // put in the last
} eMMC_PACK1 eMMC_FCIE_LIFE_TEST_BYTES_CNT_t;

//===========================================================
// burst length for write speed
//===========================================================
typedef eMMC_PACK0 struct _eMMC_FCIE_WLen_TABLE {

	U16 u16_BestBrustLen, u16_WorstBrustLen;

	U16 u16_BestMBPerSec, u16_BestMBPerSecPoint;
	U16 u16_WorstMBPerSec, u16_WorstMBPerSecPoint;

	U32 u32_ChkSum; // put in the last

} eMMC_PACK1 eMMC_FCIE_WLen_TABLE_t;

//===========================================================
// Gernel Purpose Partition
//===========================================================
typedef eMMC_PACK0 struct _eMMC_GP_Part{
	U32 u32_PartSize;
	U8 u8_EnAttr;
	U8 u8_ExtAttr;
	U8 u8_RelW;
} eMMC_PACK1 eMMC_GP_Part_t;

//===========================================================
// driver flag (u32_DrvFlag)
//===========================================================
#define DRV_FLAG_INIT_DONE       BIT0 // include eMMC identify done

#define DRV_FLAG_GET_PART_INFO   BIT1
#define DRV_FLAG_RSP_WAIT_D0H    BIT2 // currently only R1b

#define DRV_FLAG_DDR_MODE        BIT3
#define DRV_FLAG_TUNING_TTABLE   BIT4 // to avoid retry & heavy log
#define DRV_FLAG_SPEED_MASK      (BIT7|BIT6|BIT5)
#define DRV_FLAG_SPEED_HIGH      BIT5
#define DRV_FLAG_SPEED_HS200     BIT6
#define DRV_FLAG_SPEED_HS400     BIT7

#define eMMC_IF_NORMAL_SDR()   (0==(g_eMMCDrv.u32_DrvFlag&DRV_FLAG_DDR_MODE)&&\
	        DRV_FLAG_SPEED_HIGH==(g_eMMCDrv.u32_DrvFlag&DRV_FLAG_SPEED_MASK))
#define eMMC_SPEED_MODE()      (g_eMMCDrv.u32_DrvFlag&DRV_FLAG_SPEED_MASK)

#define DRV_FLAG_PwrOffNotif_MASK   (BIT8|BIT9)
#define DRV_FLAG_PwrOffNotif_OFF    0
#define DRV_FLAG_PwrOffNotif_ON     BIT8
#define DRV_FLAG_PwrOffNotif_SHORT  BIT9
#define DRV_FLAG_PwrOffNotif_LONG   (BIT8|BIT9)

#define DRV_FLAG_RSPFROMRAM_SAVE    BIT10
#define DRV_FLAG_ERROR_RETRY        BIT11
#define DRV_FLAG_GEN_TTABLE         BIT12

#define DRV_FLAG_SPEED_HS400_DETECT BIT13

typedef struct _eMMC_DRIVER
{
	U32 u32_ChkSum; // [8th ~ last-512] bytes
	U8 au8_Sig[4];  // 'e','M','M','C'

	// ----------------------------------------
    // FCIE
    // ----------------------------------------
	U16 u16_RCA;
	U32 u32_DrvFlag, u32_LastErrCode;
	U8  au8_Rsp[eMMC_MAX_RSP_BYTE_CNT];
	U8  au8_CSD[eMMC_MAX_RSP_BYTE_CNT];
	U8  au8_CID[eMMC_MAX_RSP_BYTE_CNT];
	U16 u16_Reg10_Mode;
	U32 u32_ClkKHz;
	U16 u16_ClkRegVal, u8_PadType;
	eMMC_FCIE_TIMING_TABLE_t TimingTable_t;
    eMMC_FCIE_GEN_TIMING_TABLE_t TimingTable_G_t;    
	eMMC_FCIE_LIFE_TEST_BYTES_CNT_t Life_Bytes_Cnt_t;
    // ----------------------------------------
    // eMMC
    // ----------------------------------------
	// CSD
	U8  u8_SPEC_VERS;
	U8  u8_R_BL_LEN, u8_W_BL_LEN; // supported max blk len
	U16 u16_C_SIZE;
	U8  u8_TAAC, u8_NSAC, u8_Tran_Speed;
	U8  u8_C_SIZE_MULT;
	U8  u8_ERASE_GRP_SIZE, u8_ERASE_GRP_MULT;
	U8  u8_R2W_FACTOR;

	U8  u8_IfSectorMode;
	U32 u32_eMMCFlag;
	U32 u32_EraseUnitSize;

	// ExtCSD
	U32 u32_SEC_COUNT;
	U32 u32_BOOT_SEC_COUNT;

	U8  u8_BUS_WIDTH, u8_ErasedMemContent;
	U16 u16_ReliableWBlkCnt;
	U8  u8_ECSD185_HsTiming, u8_ECSD192_Ver, u8_ECSD196_DevType, u8_ECSD197_DriverStrength;
	U8  u8_ECSD248_CMD6TO, u8_ECSD247_PwrOffLongTO, u8_ECSD34_PwrOffCtrl;
	U8	u8_ECSD160_PartSupField, u8_ECSD224_HCEraseGRPSize, u8_ECSD221_HCWpGRPSize;
	U8	u8_ECSD159_MaxEnhSize_2, u8_ECSD158_MaxEnhSize_1, u8_ECSD157_MaxEnhSize_0;
	U8	u8_u8_ECSD155_PartSetComplete, u8_ECSD166_WrRelParam;
    U8  u8_BOOT_SIZE_MULT;

    #ifdef CONFIG_TSD
	// ----------------------------------------
	// tSD
	// ----------------------------------------
	U8 u8_EraseTimeout; // unit: second
	U32 u32_EraseSize; // unit: sector(512B)
    #endif

    // ----------------------------------------
    // CIS
    // ----------------------------------------
	// nni
	U8 u8_IDByteCnt, au8_ID[eMMC_ID_BYTE_CNT];
	U8 au8_Vendor[16], au8_PartNumber[16];

	// pni
    U32 au32_Pad[2]; // don't move

	U32 u32_PartDevNodeStartSector;
	U16 u16_PartDevNodeSectorCnt;
	U32 u32_FATSectorCnt;

    // ----------------------
	#if defined(eMMC_RSP_FROM_RAM) && eMMC_RSP_FROM_RAM
	// rsp from ram
	U8 au8_AllRsp[eMMC_SECTOR_512BYTE]; // last 4 bytes are CRC
	#endif

	// ----------------------
	#if defined(eMMC_BURST_LEN_AUTOCFG) && eMMC_BURST_LEN_AUTOCFG
	eMMC_FCIE_WLen_TABLE_t  BurstWriteLen_t;
	#endif

	// ----------------------
	#if defined(eMMC_PROFILE_WR) && eMMC_PROFILE_WR
	U32 u32_CNT_CMD17, u32_CNT_CMD24, u32_CNT_CMD18, u32_CNT_CMD25;
	U64 u64_CNT_TotalRBlk, u64_CNT_TotalWBlk;

	U32 u32_CNT_MinRBlk, u32_CNT_MinWBlk, u32_CNT_MaxRBlk, u32_CNT_MaxWBlk;
	U32 u32_RBlk_tmp, u32_WBlk_tmp;
	U32 au32_CNT_MinRBlk[0x200], au32_CNT_MinWBlk[0x200]; // for blk count < 0x200, how many times

	U32 u32_Addr_RLast, u32_Addr_WLast;
	U32 u32_Addr_RHitCnt, u32_Addr_WHitCnt;

	U32 u32_temp_count;
	#endif

	eMMC_GP_Part_t	GP_Part[4];

	U32 u32_EnUserStartAddr;
	U32 u32_EnUserSize;
	U8	u8_EnUserEnAttr;
	U8	u8_EnUserRelW;

} eMMC_DRIVER, *P_eMMC_DRIVER;


extern eMMC_DRIVER g_eMMCDrv;

// ADMA Descriptor
struct  _AdmaDescriptor{
	U32	u32_End     : 1;
	U32	u32_MiuSel  : 2;
	U32             : 13;
	U32 u32_JobCnt  : 16;
	U32 u32_Address;
	U32 u32_DmaLen;
	U32 u32_Dummy;
};

//===========================================================
// exposed APIs
//===========================================================
#include "drv_eMMC.h"

//===========================================================
// internal used functions
//===========================================================
#include "eMMC_utl.h"
#include "eMMC_hal.h"
#include "eMMC_wp.h"

extern U8 gau8_WBuf[], gau8_RBuf[];

extern U32  eMMC_IPVerify_Main(void);
extern U32  eMMC_IPVerify_Main_Big(void);
extern U32  eMMC_IPVerify_Main_Ex(U32 u32_DataPattern);
#define eMMC_TEST_READONLY   1
#define eMMC_TEST_WRITEONLY  2
extern U32  eMMC_IPVerify_WriteOnly(U16 u16_TestPattern);
extern U32  eMMC_IPVerify_ReadOnly(void);
extern U32  eMMC_IPVerify_SDRDDR_AllClkTemp(void);
extern void eMMCTest_DownCount(U32 u32_Sec);
extern U32  eMMC_IPVerify_Performance(void);
extern U32  eMMCTest_BlkWRC_ProbeTiming(U32 u32_eMMC_Addr);
extern U32  eMMCTest_KeepR_TestDDR(U32 u32_LoopCnt);
extern U32  eMMCTest_Lifetime(U8 u8_TestMode);
extern U32  eMMCTest_PwrCut_InitData(U8* u8_DataBuf, U32 u32_BlkStartAddr);
extern U32  eMMCTest_PwrCut_Test(U8* u8_DataBuf, U32 u32_BlkStartAddr);
extern U32  eMMC_WaitCompleteIntr(U32 u32_RegAddr, U16 u16_WaitEvent, U32 u32_MicroSec);
extern void eMMC_enable_intr_mode(void);
//power cut
extern void eMMC_CheckPowerCut(void);
extern void eMMC_LockFCIE(U8 *pu8_str);
extern void eMMC_UnlockFCIE(U8 *pu8_str);

#define eMMC_LIFETIME_TEST_FIXED    1
#define eMMC_LIFETIME_TEST_FILLED   2
#define eMMC_LIFETIME_TEST_RANDOM   3

#define EMMC_RESERVED_BLK_FOR_MAP 4096//0~2Mbytes
#define EMMC_UBOOT_SIZE       6144//2~5Mbytes
#define EMMC_MPOOL_SIZE       4096//5~7Mbytes

extern U32 eMMC_BootMode(U32 *pu32_Addr, U32 u32_ByteCnt);
extern U8	HalFcie_CmdFifoGet(U8 u8addr);
extern void	HalFcie_CmdFifoSet(U8 u8addr, U8 u8value);

extern void	HalFcie_SetFlag4Kernel2RuneMMC(void);
extern U8	HalFcie_CheckIfeMMCRun4Kernel(void);
extern void eMMC_FCIE_GetCMDFIFO(U16 u16_WordPos, U16 u16_WordCnt, U16 *pu16_Buf);
extern U32 	eMMC_WaitCIFD_Event(U16 u16_WaitEvent, U32  u32_MicroSec);
extern U32 	eMMC_WaitSetCIFD(U8 * pu8_DataBuf, U32 u32_ByteCnt);
extern U32 	eMMC_WaitGetCIFD(U8 * pu8_DataBuf, U32 u32_ByteCnt);

#endif // eMMC_DRIVER_H

