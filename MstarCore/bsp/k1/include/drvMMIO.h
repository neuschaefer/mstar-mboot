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
/// @file   drvMMIO.h
/// @brief  MMIO SYS Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __DRV_MMIO_H__
#define __DRV_MMIO_H__


#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"


//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------
#define MSIF_MMIO_LIB_CODE              {'M','M','I','O'}    //Lib code
#define MSIF_MMIO_LIBVER                {'0','1'}            //LIB version
#define MSIF_MMIO_BUILDNUM              {'0','2'}            //Build Number
#define MSIF_MMIO_CHANGELIST            {'0','0','4','0','9','9','0','8'} //P4 ChangeList Number

#define MMIO_DRV_VERSION                /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_MMIO_LIB_CODE,                  /* IP__                                             */  \
    MSIF_MMIO_LIBVER,                    /* 0.0 ~ Z.Z                                        */  \
    MSIF_MMIO_BUILDNUM,                  /* 00 ~ 99                                          */  \
    MSIF_MMIO_CHANGELIST,                /* CL#                                              */  \
    MSIF_OS

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
// HW register space
#define DRV_MMIO_PM_BANK            0x0001
#define DRV_MMIO_NONPM_BANK         0x0002
#define DRV_MMIO_FLASH_BANK0        0x0003
#if defined(CHIP_A5) || defined(CHIP_A5P) || defined(CHIP_AGATE)
#define DRV_MMIO_FRC_BANK           0x0004
#endif
#define DRV_MMIO_OTP_BANK           0x0010
#define DRV_MMIO_SPRAM_BANK         0x0011

// Specific HW IP base
#define DRV_MMIO_SC_BANK            0x0100
#define DRV_MMIO_TSP_BANK           0x0101
#define DRV_MMIO_NDS_BANK           0x0102
#define DRV_MMIO_NSK_BANK           0x0103
#define DRV_MMIO_CAM_BANK           0x0104
#define DRV_MMIO_NGA_BANK           0x0105


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

MS_BOOL MDrv_MMIO_Init(void);
MS_BOOL MDrv_MMIO_GetBASE(MS_U32 *u32Baseaddr, MS_U32 *u32Basesize, MS_U32 u32Module);
MS_BOOL MDrv_MMIO_Close(void);


#ifdef __cplusplus
}
#endif


#endif // __DRV_MMIO_H__
