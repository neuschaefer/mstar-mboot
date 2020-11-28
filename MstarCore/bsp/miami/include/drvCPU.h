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
/// @file   drvCPU.h
/// @brief  System Control Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_CPU_H_
#define _DRV_CPU_H_

#include "MsTypes.h"
#include "MsDevice.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define CPU_UTOPIA20       (1)

//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
// #define COPRO_TYPE_DEF
/// Version string.

#define MSIF_COPRO_LIB_CODE                     {'C','O','P','R'}    //Lib code
#define MSIF_COPRO_LIBVER                       {'0','2'}            //LIB version
#define MSIF_COPRO_BUILDNUM                     {'1','0'}            //Build Number
#define MSIF_COPRO_CHANGELIST                   {'0','0','5','5','7','0','9','3'} //P4 ChangeList Number

#define COPRO_DRV_VERSION                       /* Character String for DRV/API version             */  \
    MSIF_TAG,                             /* 'MSIF'                                           */  \
    MSIF_CLASS,                           /* '00'                                             */  \
    MSIF_CUS,                             /* 0x0000                                           */  \
    MSIF_MOD,                             /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_COPRO_LIB_CODE,                        /* IP__                                             */  \
    MSIF_COPRO_LIBVER,                          /* 0.0 ~ Z.Z                                        */  \
    MSIF_COPRO_BUILDNUM,                        /* 00 ~ 99                                          */  \
    MSIF_COPRO_CHANGELIST,                      /* CL#                                              */  \
    MSIF_OS


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef enum
{
    E_COPRO_OK,
    E_COPRO_FAIL,
} COPRO_Result;

typedef struct _COPRO_DrvInfo
{
    MS_BOOL     Init;
    MS_U32      u32Addr;
} COPRO_DrvInfo;


typedef struct _COPRO_DrvStatus
{
    MS_BOOL     HwBusy;
} COPRO_DrvStatus;

typedef enum _COPRO_DbgLv
{
    E_COPRO_DBGLV_NONE,           //no debug message
    E_COPRO_DBGLV_ERR_ONLY,      //show error only
    E_COPRO_DBGLV_INFO,          //show error & informaiton
    E_COPRO_DBGLV_ALL           //show error, information & funciton name
}COPRO_DbgLv;

typedef enum
{
    Q_PARALLEL,
    Q_STATE,
    Q_MPEG2_FS,
    Q_MPEG2,
    Q_TSPLAYER_FS,
    Q_TSPLAYER,
    Q_VDPLAYER_FS,
    Q_VDPLAYER,
    Q_MBFS,
    Q_IR,
    Q_OBAMA,
    Q_PRINT_MESSAGE,
    Q_CIPLUS,
    Q_DLNA,
    Q_BTPD,
    Q_KTV,
    Q_SHWFS,
    Q_APENGINE,
    Q_MM,
    Q_MHEG5,
    Q_NWDEBUG, //add by Ian
    Q_NUM,
} Q_TYPE;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
#if (CPU_UTOPIA20)
#include "drvCPU_v2.h"
#endif

    void MDrv_COPRO_Disable(void);
    void MDrv_COPRO_Enable(MS_U32 u32_ADR);
    //void MDrv_BEON_Init(MS_U16 u16BeonBinID, MS_U32 u32BEON_ADR, MS_U32 u32BEON_LEN);
    //void MDrv_BEON_Init_ByAddr(MS_U32 u32BEON_ADR, MS_U32 u32BEON_LEN);
    void  MDrv_SetBEON_Host(MS_BOOL bHost);
    void   MDrv_COPRO_Init_Front(void);
    void   MDrv_COPRO_Init_End(MS_U32 u32_ADR);

    const COPRO_DrvInfo* MDrv_COPRO_GetInfo(void);
    COPRO_Result MDrv_COPRO_GetLibVer(const MSIF_Version **ppVersion);
    COPRO_Result MDrv_COPRO_GetStatus(COPRO_DrvStatus *pStatus);
    void MDrv_COPRO_SetDbgLevel(MS_U8 u8Level);
    MS_U32 MDrv_COPRO_GetBase(void);
    MS_U32 MDrv_CPU_QueryClock(void);
    MS_U32 MDrv_CPU_SetPowerState(EN_POWER_MODE u16PowerState);
	MS_U32 MDrv_CPU_GetDqmemInfo(MS_U32 *pu32_DqmemAddr, MS_U32 *pu32_DqmemSize);

#ifdef __cplusplus
}
#endif

#endif // _DRV_CPU_H_

