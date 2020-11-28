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
#ifndef DRV_WBLE_H
#define DRV_WBLE_H

#ifdef __cplusplus
extern "C"
{
#endif


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
//  library information
#define MSIF_WBLE_LIB_CODE               {'W','B','L','E'}
#define MSIF_WBLE_LIBVER                 {'0','0'}
#define MSIF_WBLE_BUILDNUM               {'0','2'}
#define MSIF_WBLE_CHANGELIST             {'0','0','2','7','5','5','7','8'}
#define WBLE_API_VERSION                  /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_WBLE_LIB_CODE  ,                 /* IP__                                             */  \
    MSIF_WBLE_LIBVER    ,                 /* 0.0 ~ Z.Z                                        */  \
    MSIF_WBLE_BUILDNUM  ,                 /* 00 ~ 99                                          */  \
    MSIF_WBLE_CHANGELIST,                 /* CL#                                              */  \
    MSIF_OS

#define WBLE_INITDATA_VERSION                1


/// XC Return Value
typedef enum
{
    E_DRVWBLE_RET_FAIL = 0,   ///<Fail
    E_DRVWBLE_RET_OK,         ///<OK
} E_DRVWBLE_ReturnValue;



void MDrv_WBLE_Init(void);
void MDrv_WBLE_EnableBLE(MS_BOOL bEnable);
void MDrv_WBLE_EnableWLE(MS_BOOL bEnable);
void MDrv_WBLE_SetBLE(MS_U8 u8Start, MS_U8 u8Slop);
void MDrv_WBLE_SetWLE(MS_U8 u8Start, MS_U8 u8Slop);
void MDrv_WBLE_Handler_BLEAvgLuma(MS_U8 u8AvgY, MS_U16 u16YTotalSum);
void MDrv_WBLE_Set_SlopeValue(MS_U8 u8Slope);

#ifdef __cplusplus
}
#endif



#endif
