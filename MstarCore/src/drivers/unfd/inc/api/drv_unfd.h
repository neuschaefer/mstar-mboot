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

#ifndef __DRV_UNFD_H__
#define __DRV_UNFD_H__

/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
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

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef struct _NAND_INFO
{
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
	U16	u16_tRC;
	U8	padding[12];
	U8	u8_Vendor[16];
	U8	u8_PartNumber[16];

	U16 u16_ECCCodeByteCnt;
	U16 u16_PageSectorCnt;
	U8  u8_WordMode;

} NAND_INFO_t;

typedef struct _PAIRED_PAGE_MAP {
    U16 u16_LSB;
    U16 u16_MSB;
} PAIRED_PAGE_MAP_t, *P_PAIRED_PAGE_MAP_t;

extern PAIRED_PAGE_MAP_t ga_tPairedPageMap[];
extern U8 gau8_ReadRetryTable[];
/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
extern U32 drvNAND_Init(void);
extern U32 drvNAND_IPVerify_Main(void);


extern U32 drvNAND_GetNandInfo(NAND_INFO_t *pNandInfo);


extern U32 drvNAND_ChkRdy(U32 u32_PartNo);
extern int drv_unfd_init(void);
extern U32 drvNAND_LoadBootLoader(U8 *pu8_DestAddr, U32 u32_StartSector, U32 u32_SectorCnt, U32 u32_LogicIdx);
extern U32 drvNAND_InitProgrammer(void);
extern U32 drvNAND_GetNandID(U8 *pu8IDByteCnt, U8 *pu8ID);
extern U32 drvNAND_CheckCIS(U8 *pu8_CISData);
extern U32 drvNAND_WriteCIS(U8 *pu8_CISData);
extern U32 drvNAND_ReadCIS(U8 *pu8_CISData);
extern U32 drvNAND_WriteMiuParam(U32 u32_SrcPhyAddr, U32 u32_StartSector, U32 u32_SectorCnt);
extern U32 drvNAND_LoadMiuParam(U32 u32_SrcPhyAddr, U32 u32_StartSector, U32 u32_SectorCnt);
extern U32 drvNAND_EraseMiuParam(void);
extern U32 drvNAND_GetMiuParamCapacity(void);
extern U32 drvNAND_WriteBootLoader(U32 u32_SrcPhyAddr, U32 u32_StartSector, U32 u32_SectorCnt);
extern U32 drvNAND_EraseBootLoader(void);
extern U32 drvNAND_GetBootLoaderCapacity(U32 u32_LogicIdx);
extern U32 drvNAND_WriteOS(U32 u32_SrcPhyAddr, U32 u32_StartSector, U32 u32_SectorCnt);
extern U32 drvNAND_LoadOS(U32 u32_SrcPhyAddr, U32 u32_StartSector, U32 u32_SectorCnt, void (*pfCB)(U32 XferSize));
extern U32 drvNAND_EraseOS(void);
extern U32 drvNAND_GetOSCapacity(void);
extern U32 drvNAND_WriteCUS(U32 u32_SrcPhyAddr, U32 u32_StartSector, U32 u32_SectorCnt);
extern U32 drvNAND_LoadCUS(U32 u32_SrcPhyAddr, U32 u32_StartSector, U32 u32_SectorCnt);
extern U32 drvNAND_EraseCUS(void);
extern U32 drvNAND_GetCUSCapacity(void);
extern U32 drvNAND_EraseAllPartitions(void);
extern U32 drvNAND_WriteNRAI(U32 u32_SrcPhyAddr, U32 u32_StartSector, U32 u32_SectorCnt);
extern U32 drvNAND_ReadNRAI(U32 u32_SrcPhyAddr, U32 u32_StartSector, U32 u32_SectorCnt);
extern U32 drvNAND_GetNRAICapacity(void);
extern U32 drvNAND_WriteE2P0(U32 u32_SrcPhyAddr, U32 u32_StartSector, U32 u32_SectorCnt);
extern U32 drvNAND_ReadE2P0(U32 u32_SrcPhyAddr, U32 u32_StartSector, U32 u32_SectorCnt);
extern U32 drvNAND_GetE2P0Capacity(void);
extern U32 drvNAND_WriteE2P1(U32 u32_SrcPhyAddr, U32 u32_StartSector, U32 u32_SectorCnt);
extern U32 drvNAND_ReadE2P1(U32 u32_SrcPhyAddr, U32 u32_StartSector, U32 u32_SectorCnt);
extern U32 drvNAND_GetE2P1Capacity(void);
extern U32 drvNAND_WriteBacktrace(U32 u32_SrcPhyAddr, U32 u32_StartSector, U32 u32_SectorCnt);
extern U32 drvNAND_ReadBacktrace(U32 u32_SrcPhyAddr, U32 u32_StartSector, U32 u32_SectorCnt);
extern U32 drvNAND_GetBacktraceCapacity(void);
extern U32 drvNAND_WriteFAT(U32 u32_SrcPhyAddr, U32 u32_StartSector, U32 u32_SectorCnt);
extern U32 drvNAND_ReadFAT(U32 u32_SrcPhyAddr, U32 u32_StartSector, U32 u32_SectorCnt);
extern U32 drvNAND_GetFATCapacity(void);
extern U32 drvNAND_WriteNVRAM0(U32 u32_SrcPhyAddr, U32 u32_StartSector, U32 u32_SectorCnt);
extern U32 drvNAND_ReadNVRAM0(U32 u32_SrcPhyAddr, U32 u32_StartSector, U32 u32_SectorCnt);
extern U32 drvNAND_GetNVRAM0Capacity(void);
extern U32 drvNAND_WriteNVRAM1(U32 u32_SrcPhyAddr, U32 u32_StartSector, U32 u32_SectorCnt);
extern U32 drvNAND_ReadNVRAM1(U32 u32_SrcPhyAddr, U32 u32_StartSector, U32 u32_SectorCnt);
extern U32 drvNAND_GetNVRAM1Capacity(void);
extern U32 drvNAND_FormatFTL(void);
extern U32 drvNAND_GetPhyCapacity(void);

extern U32 drvNAND_EraseAllPhyBlk(void);
extern U32 drvNAND_EraseAllGoodPhyBlk(U16 *pu16_GoodBlkCnt, U16 *pu16_BadBlkIdxList, U16 *pu16_BadBlkCnt);
extern U32 drvNAND_ErasePhysicalBlk(U16 u16_BlkIdx);
extern U32 drvNAND_ReadPhysicalPage(U32 u32_PageIdx, U8 *pu8_Data, U8 *pu8_Spare);
extern U32 drvNAND_WritePhysicalPage(U32 u32_PageIdx, U8 *pu8_Data, U8 *pu8_Spare);
extern U32 drvNAND_CheckGoodBlk(U16 u16_BlkIdx);
extern U32 drvNAND_ResetNandFlash(void);
extern U32 drvNAND_FlushCache(void);

#endif //__DRV_UNFD_H__

