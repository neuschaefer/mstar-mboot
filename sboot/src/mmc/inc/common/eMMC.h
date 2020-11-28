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
 * eMMC Driver for FCIE4 - eMMC.h
 *
 * History
 *    - initial version, 2011.09.22, Hill.Sung
 *      please modify the eMMC_platform.h for your platform.
 *
 *
 *===========================================================*/
#ifndef eMMC_DRIVER_H
#define eMMC_DRIVER_H


//===========================================================
// debug macro
//===========================================================


//=====================================================================================
#include "../config/eMMC_config.h" // [CAUTION]: edit eMMC_config.h for your platform
//=====================================================================================
#include "eMMC_err_codes.h"


//===========================================================
// macro for Spec.
//===========================================================
#define ADDRESSING_MODE_BYTE      1 // 1 byte
#define ADDRESSING_MODE_SECTOR    2 // 512 bytes
#define ADDRESSING_MODE_4KB       3 // 4KB bytes

#define eMMC_SPEED_OLD            0
#define eMMC_SPEED_HIGH           1
#define eMMC_SPEED_HS200          2

#define eMMC_FLAG_TRIM            BIT0
#define eMMC_FLAG_HPI_CMD12       BIT1
#define eMMC_FLAG_HPI_CMD13       BIT2

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

//===========================================================
// driver structures
//===========================================================
#define FCIE_FLAG_GET_PART_INFO   BIT1
#define FCIE_FLAG_RSP_WAIT_D0H    BIT2 // currently only R1b
#define FCIE_FLAG_DDR_MODE        BIT3
#define FCIE_FLAG_DDR_TUNING      BIT4
#define FCIE_FLAG_SPEED_MASK      (BIT5|BIT6)
#define FCIE_FLAG_SPEED_HIGH      BIT5
#define FCIE_FLAG_SPEED_HS200     BIT6
#define FCIE_FLAG_TESTING         BIT7
#define FCIE_FLAG_PADTYPE_MASK    (BIT8|BIT9)
#define FCIE_FLAG_PADTYPE_DDR     BIT8
#define FCIE_FLAG_PADTYPE_SDR     BIT9
#define FCIE_FLAG_PADTYPE_BYPASS  (BIT8|BIT9)


typedef struct _eMMC_DRIVER
{
	// ----------------------------------------
    // FCIE
    // ----------------------------------------
	U16 u16_RCA;
	U32 u32_Flag;
	U8  au8_Rsp[eMMC_R1_BYTE_CNT];

	U16 u16_Reg10_Mode;

    // ----------------------------------------
    // eMMC
    // ----------------------------------------
	U8  u8_IfSectorMode;
	// ExtCSD
	U8  u8_BUS_WIDTH;
} eMMC_DRIVER, *P_eMMC_DRIVER;


//extern U8 g_eMMCDrv_array[15];

//===========================================================
// exposed APIs
//===========================================================
#include "../api/drv_eMMC.h"

//===========================================================
// internal used functions
//===========================================================
#include "eMMC_utl.h"
#include "eMMC_hal.h"


#endif // eMMC_DRIVER_H

