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
/// @file   drvIRQ.h
/// @brief  IRQ Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_IRQ_H_
#define _DRV_IRQ_H_

#include"MsIRQ.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"

//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------
#define MSIF_DRVIRQ_LIB_CODE              {'I','R','Q',' '}    //Lib code
#define MSIF_DRVIRQ_LIBVER                {'0','1'}            //LIB version
#define MSIF_DRVIRQ_BUILDNUM              {'0','3'}            //Build Number
#define MSIF_DRVIRQ_CHANGELIST            {'0','0','5','5','5','6','7','9'} //P4 ChangeList Number

#define DRVIRQ_DRV_VERSION                /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_DRVIRQ_LIB_CODE,                  /* IP__                                             */  \
    MSIF_DRVIRQ_LIBVER,                    /* 0.0 ~ Z.Z                                        */  \
    MSIF_DRVIRQ_BUILDNUM,                  /* 00 ~ 99                                          */  \
    MSIF_DRVIRQ_CHANGELIST,                /* CL#                                              */  \
    MSIF_OS

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
// TICK_TIMER
#define MDRV_RISC32_TIMER   0x80
// PIC
#define MDRV_RISC32_UART    0x81

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
///Define CPU to CPU interrupt type
typedef enum
{
    E_IRQ_CPU0_2_CPU1,      ///< 8051 to AEON
    E_IRQ_CPU0_2_CPU2,      ///< 8051 to BEON
    E_IRQ_CPU1_2_CPU0,      ///< AEON to 8051
    E_IRQ_CPU1_2_CPU2,      ///< AEON to BEON
    E_IRQ_CPU2_2_CPU0,      ///< BEON to 8051
    E_IRQ_CPU2_2_CPU1,      ///< BEON to AEON
}IRQ_CPU_TYPE;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
void MDrv_IRQ_Detech(MS_U32 u32Vector);
void MDrv_IRQ_Attach(MS_U32 u32Vector, void *pIntCb);
void MDrv_IRQ_Restore(void);
void MDrv_IRQ_MaskAll(void);
void MDrv_IRQ_UnMaskAll(void);
void MDrv_IRQ_Mask(MS_U32 u32Vector);
void MDrv_IRQ_UnMask(MS_U32 u32Vector);
void MDrv_IRQ_NotifyCpu(IRQ_CPU_TYPE eType);
MS_BOOL MDrv_IRQ_Init(void);
MS_BOOL MDrv_IRQ_InISR(void);

#ifdef __cplusplus
}
#endif

#endif // _DRV_IRQ_H_

