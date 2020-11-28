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
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file    drvDDC2BI.h
/// @brief  DDC2Bi interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVDDC2BI_H_
#define _DRVDDC2BI_H_

#include "MsTypes.h"

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

#define MSIF_DDC_LIB_CODE               {'D','D','C','_'}
#define MSIF_DDC_LIBVER                 {'0','1'}
#define MSIF_DDC_BUILDNUM               {'0','2'}
#define MSIF_DDC_CHANGELIST             {'0','0','3','1','6','8','6','6'}
#define DDC2BI_DRV_VERSION              /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_DDC_LIB_CODE,                  /* IP__                                             */  \
    MSIF_DDC_LIBVER,                    /* 0.0 ~ Z.Z                                        */  \
    MSIF_DDC_BUILDNUM,                  /* 00 ~ 99                                          */  \
    MSIF_DDC_CHANGELIST,                /* CL#                                              */  \
    MSIF_OS

//----------------------------
// Return value
//----------------------------
typedef enum
{
    E_DDC2BI_RET_FAIL = 0,
    E_DDC2BI_RET_OK,
} E_DDC2BI_ReturnValue;


// DDC2Bi receive/transmit status bytes definitions
#define    DDC2B_CLEAR                  0
#define    DDC2B_SRCADDRESS             1
#define    DDC2B_COMMAND                2
#define    DDC2B_RECBODY                3
#define    DDC2B_WAITFORCK              4
#define    DDC2B_COMPLETED              5
#define    DDC2B_MSGON                  6
#define    DDC2B_OVER                   7

// receive/transmit buffer syntax defines
#define LENGTH                          0
#define COMMAND                         1
#define DATA1                           2
#define DATA2                           3
#define CHKSUM                          4

// DDC2Bi standard definitions
#define DDC2B_DEST_ADDRESS              0x6e
#define DDC2B_SRC_ADDRESS               0x51
#define DDC2Bi_CONTROL_STATUS_FLAG      0x80

// checksum start values
#define    INITRxCK                     DDC2B_SRC_ADDRESS ^ DDC2B_DEST_ADDRESS
#define    INITTxCK                     0x50^DDC2B_DEST_ADDRESS
#define    INITNMVTxCK                  0x50^DDC2B_SRC_ADDRESS

//interrupt flag
#define TXBI                            0x10
#define RCBI                            0x08
//#define SlvBMI                        0x20


#define DDC2B_SRC_ADDRESS_CUSTOMER      0x50
#define MAX_TXWAIT_DELAY                100
#define MaxBufLen                       128


// This defination must be fine.

/*
    Please measure the execution time of a loop without any statement for DDC_WAITING_LOOPSCOUNT.
    ex:
        for ( i = 0 ; i < DDC_WAITING_LOOPSCOUNT ; i++) asm("");

    The asm("") is used to prevent compiler doing optimization on that loop.

    The total execution time of loops should be larger than 1/12M (70ns for DDC clk).
    (Move this part into HAL later)
*/
#define DDC_WAITING_LOOPSCOUNT 3   // 46ns/loop in 172Mhz HK.

typedef MS_U8(*CALLBACK_AlignControl)(MS_U8 *pDDCBuffData);


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
/**
*   DDC2BI Info
*/
typedef struct
{
    MS_U8 Reserved;
}MS_DDC2BI_INFO;

/**
*   DDC2BI Status
*/
typedef struct
{
    MS_BOOL bIsInitialized;
    MS_BOOL bIsRunning;
}MS_DDC2BI_Status;

DLL_PUBLIC E_DDC2BI_ReturnValue  MDrv_DDC2BI_GetLibVer(const MSIF_Version **ppVersion);      ///< Get version (without Mutex protect)
DLL_PUBLIC E_DDC2BI_ReturnValue  MDrv_DDC2BI_GetInfo(MS_DDC2BI_INFO *pInfo);
DLL_PUBLIC E_DDC2BI_ReturnValue  MDrv_DDC2BI_GetStatus(MS_DDC2BI_Status *pStatus);
DLL_PUBLIC E_DDC2BI_ReturnValue  MDrv_DDC2BI_SetDbgLevel(MS_U16 u16DbgSwitch);

DLL_PUBLIC void MDrv_DDC2BI_Init(void);
DLL_PUBLIC MS_BOOL MDrv_DDC2BI_Exit(void);
DLL_PUBLIC void MDrv_DDC2BI_Set_StandardCallBack(CALLBACK_AlignControl align_control);      ///< DDC2BI callback function for Standard
DLL_PUBLIC void MDrv_DDC2BI_Set_CustomerCallBack(CALLBACK_AlignControl align_control);      ///< DDC2BI callback function for Customer

#endif  // _DRVDDC2BI_H_
