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
/// file    asmCPU.h
/// @author MStar Semiconductor Inc.
/// @brief  Inline Assembly wrapper
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef _ASM_CPU_H_
#define _ASM_CPU_H_



#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Extern Functions
//-------------------------------------------------------------------------------------------------
void    MAsm_CPU_Sync(void);
void    MAsm_CPU_Nop(void);
void    MAsm_CPU_SwDbgBp(void);
void    MAsm_CPU_SwDbgBp(void);
void    MAsm_CPU_PowerDown(void);
void    MAsm_CPU_StatusBEV(MS_BOOL bBEV);
void    MAsm_CPU_Jump(MS_U32 u32PC);
MS_U8   MAsm_CPU_GetTrailOne(MS_U32 u32Flags);
void    MAsm_CPU_EnableTimerInterrupt(MS_BOOL bEnable);
void    MAsm_CPU_DelayMs(MS_U32 msec);
void    MAsm_CPU_DelayUs(MS_U32 usec);
void    MAsm_CPU_SetEBASE(MS_U32 u32addr);
MS_U32 MAsm_GetSystemTime (void);
void MAsm_CPU_TimerInit(void);


#ifdef __cplusplus
}
#endif

#endif // _ASM_CPU_H_

