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
/// @file   drvSYS.h
/// @brief  System Control Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_SYS_DMD_VD_MBX_H_
#define _DRV_SYS_DMD_VD_MBX_H_

#ifdef __cplusplus
extern "C"
{
#endif
//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef enum
{
    E_DMD_VD_MBX_TYPE_ATV,
    E_DMD_VD_MBX_TYPE_DVBT,
    E_DMD_VD_MBX_TYPE_DVBC,
    E_DMD_VD_MBX_TYPE_ATSC,
    E_DMD_VD_MBX_TYPE_MAX
}DMD_VD_MBX_Type;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_SYS_DMD_VD_MBX_Init(void);
void MDrv_SYS_DMD_VD_MBX_SetType(DMD_VD_MBX_Type eType);
MS_BOOL MDrv_SYS_DMD_VD_MBX_ReadReg(MS_U32 u32Reg, MS_U8 *u8Value);
MS_BOOL MDrv_SYS_DMD_VD_MBX_ReadDSPReg(MS_U32 u32Reg, MS_U8 *u8Value);
MS_BOOL MDrv_SYS_DMD_VD_MBX_DBG_ReadReg(MS_U32 u32Reg, MS_U8 *u8Value);
MS_BOOL MDrv_SYS_DMD_VD_MBX_WriteReg(MS_U32 u32Reg, MS_U8 u8Value);
MS_BOOL MDrv_SYS_DMD_VD_MBX_WriteDSPReg(MS_U32 u32Reg, MS_U8 u8Value);
MS_BOOL MDrv_SYS_DMD_VD_MBX_DBG_WriteReg(MS_U32 u32Reg, MS_U8 u8Value);
#ifdef __cplusplus
}
#endif
#endif // _DRV_SYS_DMD_VD_MBX_H_

