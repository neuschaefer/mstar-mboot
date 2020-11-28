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

#ifndef NAND_DRV_FTL
#define NAND_DRV_FTL

//===================================================
// feature list
#define UNFD_FTL_WBQ                0 // ver.03
#define UNFD_FTL_FMAP               0 // ver.04
#define UNFD_FTL_WL                 0 // ver.06
#define UNFD_FTL_RD                 0 // ver.05
#define UNFD_FTL_TRACK_LOG          0

//===================================================
// [CAUTION]: if mismatch the value in RootBlk,
//            do the Low Level Format to clear logical area
#define UNFD_ROOT_BLK_CNT           1
#define UNFD_FTL_VERSION            0x07

#define MAX_LUT_CNT                 5
#define LUT_PBA_CNT                 0x400
#define UNFD_FREE_BLK_CNT_PER_1K    16 // [CAUTION]: logical area at least need to reserved 16 blocks
                                       // FreeBlk Cnt includes (also used to cover) bad blks
#define LUT_LBA_CNT                 (LUT_PBA_CNT-UNFD_FREE_BLK_CNT_PER_1K)


//===================================================
// Blk IDs
#define UNFD_FTL_BLK_ID_ROOT    (0 + UNFD_PART_PHY_POS)
#define UNFD_FTL_BLK_ID_CTRL    (1 + UNFD_PART_PHY_POS)
#define UNFD_FTL_BLK_ID_LUT     (2 + UNFD_PART_PHY_POS)
#define UNFD_FTL_BLK_ID_PPB     (4 + UNFD_PART_PHY_POS) // partial page blk
#define UNFD_FTL_BLK_ID_DATA    (5 + UNFD_PART_PHY_POS)
#define UNFD_FTL_BLK_ID_WLECNT  (6 + UNFD_PART_PHY_POS)
#define UNFD_FTL_BLK_ID_FMAP    (7 + UNFD_PART_PHY_POS)
#define UNFD_FTL_BLK_ID_RD      (8 + UNFD_PART_PHY_POS)
#define UNFD_FTL_BLK_ID_MG      (9 + UNFD_PART_PHY_POS)
#define UNFD_FTL_BLK_ID_END     UNFD_FTL_BLK_ID_MG

//----------------------------
// RootBlk
typedef UNFD_PACK0 struct _ROOT_BLK_DATA{
    U32 u32_Tmp;

} UNFD_PACK1 ROOT_BLK_DATA_t, *P_ROOT_BLK_DATA_t;


typedef UNFD_PACK0 struct _ROOT_BLK_SPARE{
    U8 u8_BadBlkMark;
	U8 u8_BlkID;
	U8 u8_FTLVerNum;
	U8 u8_RDD3;
	U8 u8_RDD4;
	U8 u8_RDD5;

} UNFD_PACK1 ROOT_BLK_SPARE_t, *P_ROOT_BLK_SPARE_t;


//----------------------------
// PartialPageBlk
#if UNFD_FTL_WBQ
typedef UNFD_PACK0 struct _PPB_BLK_SPARE{
    U8  u8_BadBlkMark;
	U8  u8_BlkID;
	U8  u8_WBQIdx;
	U8  u8_RDD3;
	U8  u8_RDD4;
	U8  u8_RDD5;

} UNFD_PACK1 PPB_BLK_SPARE_t, *P_PPB_BLK_SPARE_t;
#endif

//----------------------------
// DataBlk
typedef UNFD_PACK0 struct _DATA_BLK_SPARE{
    U8  u8_BadBlkMark;
	U8  u8_BlkID;
	U16 u16_LBA;
	U8  u8_RDD4;
	U8  u8_RDD5;

} UNFD_PACK1 DATA_BLK_SPARE_t, *P_DATA_BLK_SPARE_t;

//----------------------------
// WLECntBlk
#if UNFD_FTL_WL
typedef UNFD_PACK0 struct _WLECNT_BLK_SPARE{
    U8  u8_BadBlkMark;
	U8  u8_BlkID;
	U8  u8_ECntIdx;
	U8  u8_ECntSubIdx;
	U8  u8_RDD4;
	U8  u8_RDD5;

} UNFD_PACK1 WLECNT_BLK_SPARE_t, *P_WLECNT_BLK_SPARE_t;
#endif

//----------------------------
// FMapBlk
#if UNFD_FTL_FMAP
typedef UNFD_PACK0 struct _FMAP_BLK_SPARE{
    U8  u8_BadBlkMark;
	U8  u8_BlkID;
	U16 u16_LBA;
	U8  u8_PageIdx;
	U8  u8_RDD5;

} UNFD_PACK1 FMAP_BLK_SPARE_t, *P_FMAP_BLK_SPARE_t;
#endif

//----------------------------
// RDBlk
#if UNFD_FTL_RD
typedef UNFD_PACK0 struct _RD_BLK_DATA{
    U16 u16_SrcPBA;
	U16 u16_DestPBA;
	U32 u32_Checksum;

} UNFD_PACK1 RD_BLK_DATA_t, *P_RD_BLK_DATA_t;

typedef UNFD_PACK0 struct _RD_BLK_SPARE{
    U8  u8_BadBlkMark;
	U8  u8_BlkID;
	U8  u8_St;
	U8  u8_RDD3;
	U8  u8_RDD4;
	U8  u8_RDD5;

} UNFD_PACK1 RD_BLK_SPARE_t, *P_RD_BLK_SPARE_t;

#define UNFD_FTL_RD_ST_IDLE    0
#define UNFD_FTL_RD_ST_START   1
#endif


//===================================================
// Memory Guarf
#if UNFD_FTL_MEM_GUARD
typedef UNFD_PACK0 struct _MG_X_REC{

	U16 u16_mem_gw0;
	U16 u16_mem_gw1;
	U16 u16_mem_gw2;
	U16 u16_mem_gw3;
	U16 u16_mem_gw4;
	U16 u16_mem_lock0;
	U16 u16_mem_lock1;

    U16 u16_mem_w0;
	U16 u16_mem_w1;
	U16 u16_mem_w2;
	U16 u16_mem_w3;
	U16 u16_mem_w4;
	U16 u16_mem_w5;
	U16 u16_mem_w6;
	U16 u16_mem_w7;
	U16 u16_mem_w8;

	U32 u32_mem_stack_adr, u32_mem_stack_dat;
	U32 u32_mem_stack_dat_cur;

	U32 u32_mem_stack1_adr, u32_mem_stack1_dat;
	U32 u32_mem_stack1_dat_cur;

} UNFD_PACK1 MG_X_REC_t, *P_MG_X_REC_t;


typedef UNFD_PACK0 struct _MG_BLK_SPARE{
    U8  u8_BadBlkMark;
	U8  u8_BlkID;
	U8  u8_RDD2;
	U8  u8_RDD3;
	U8  u8_RDD4;
	U8  u8_RDD5;

} UNFD_PACK1 MG_X_REC_SPARE_t, *P_MG_X_REC_SPARE_t;
#endif

//===================================================
#if UNFD_FTL_WBQ
#define MAX_WBQ_CNT  4

typedef struct _WBQ {

    volatile U16 u16_LBA;
    volatile U16 u16_OldPBA;
    volatile U16 u16_NewPBA;    // pick up from FreeBlk

    volatile U16 u16_PagePos;   // points to the "next & free" page, in the u16_NewPBA.
    volatile U16 u16_SectorPos; // if have partial page data (page not fulfilled)
	                            // co-work with pNandDrv->u16_PPB & u16_PPBPageIdx
    volatile U16 u16_PPBPageIdx;// if SectorPos is 0, then don't care PPBPageIdx

} WBQ_t, *P_WBQ_t;
#endif


//===================================================
#if UNFD_FTL_FMAP
//----------------------------------------
// [CAUTION]: any change for this feature,
//            we have to change UNFD_FTL_VERSION to do Low Level Format.
//----------------------------------------
#define FMAP_MAX_SECTOR_CNT     0x280 //0x500
#define FMAP_SPACE_FACTOR       4 // one blk in FMAP holds the 1/FMAP_SPACE_FACTOR sectors of original blk

#define FMAP_MAX_LBA_CNT        40
#define FMAP_MAX_BLKPAGE_CNT    0x80 // [CAUTION]
#endif

//===================================================
#if UNFD_FTL_WL
#define WL_EC_THRESHOLD		0x20//0x80
#define WL_SAVE_EC_TIMES	0x40//0x100
#define WL_CHECK_EC_MASK	0x1F//(0x20-1)
#endif

//===================================================
// exposed functions
extern U32 nand_Init_FTL(void);
extern U32 nand_Low_Level_Format(void);
extern U32 nand_get_partition_sector_cnt(U32 u32_PartNo);

extern U32 nand_WriteFlow(U32 u32_StartSectorIdx, U32 u32_SectorCnt, U32 u32_RWBufferAddress);
extern U32 nand_ReadFlow(U32 u32_StartSectorIdx, U32 u32_SectorCnt, U32 u32_RWBufferAddress);
#if UNFD_FTL_WBQ
extern U32 nand_FlushWBQ(U8 u8_WBQIdx);
#endif
#if UNFD_FTL_RD
extern void nand_ReadDisturbance(void);
#endif
#if UNFD_FTL_WL
extern void nand_Wear_Leveling(void);
extern void nand_Wear_Leveling1(void);
extern void nand_SaveEraseCounter(U8 u8_EraseCounterZoneIndex);
#endif
#endif // NAND_DRV_FTL

