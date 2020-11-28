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
/// @file   drvWDT.h
/// @brief  Piu Watch Dog Timer Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_RTC_H_
#define _DRV_RTC_H_



#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"

////////////////////////////////////////////////////////////////////////////////
//  Type and Structure
////////////////////////////////////////////////////////////////////////////////
#define RTC_DRV_VERSION                 /* Character String for DRV/API version  */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                              */  \
    MSIF_CUS,                           /* 0x0000                                         */  \
    MSIF_MOD,                           /* 0x0000                                         */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    {'R','T','C',},                     /* IP__                                             */  \
    {'0','0'},                          /* 0.0 ~ Z.Z                                      */  \
    {'0','0'},                          /* 00 ~ 99                                         */  \
    {'0','0','0','0','0','0','0','0'},  /* CL#                                              */  \
    MSIF_OS


typedef enum _RTC_DbgLv
{
    E_RTC_DBGLV_NONE,          /* no debug message */
    E_RTC_DBGLV_ERR_ONLY,      /* show error only */
    E_RTC_DBGLV_INFO,          /* show error & informaiton */
    E_RTC_DBGLV_ALL            /* show error, information & funciton name */
}RTC_DbgLv;


typedef enum
{
    E_MS_DRV_RTC_0,
    E_MS_DRV_RTC_2,
}E_MS_DRV_RTC;

MS_BOOL MDrv_RTC_Init(E_MS_DRV_RTC eRtc, MS_U32 u32Freq, MS_U32 u32Xtal, MS_U32 u32Sec,InterruptCb pIntCb);
MS_U32 MDrv_RTC_GetCount(E_MS_DRV_RTC eRtc);
void MDrv_RTC_DeInit(E_MS_DRV_RTC eRtc);

#ifdef __cplusplus
}
#endif

#endif // _DRV_WDT_H_

