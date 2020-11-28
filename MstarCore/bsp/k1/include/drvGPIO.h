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
///////////////////////////////////////////////////////////////////////////////

#ifndef __DRVGPIO_H__
#define __DRVGPIO_H__


#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"

#define MSIF_GPIO_LIB_CODE                     {'G','P','I','O'}    //Lib code
#define MSIF_GPIO_LIBVER                       {'0','3'}            //LIB version
#define MSIF_GPIO_BUILDNUM                     {'0','6'}            //Build Number
#define MSIF_GPIO_CHANGELIST                   {'0','0','5','5','7','0','9','3'} //P4 ChangeList Number

#define GPIO_DRV_VERSION                /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_GPIO_LIB_CODE,                        /* IP__                                             */  \
    MSIF_GPIO_LIBVER,                          /* 0.0 ~ Z.Z                                        */  \
    MSIF_GPIO_BUILDNUM,                        /* 00 ~ 99                                          */  \
    MSIF_GPIO_CHANGELIST,                      /* CL#                                              */  \
    MSIF_OS

typedef enum _GPIO_DbgLv
{
    E_GPIO_DBGLV_NONE,          //no debug message
    E_GPIO_DBGLV_ERR_ONLY,      //show error only
    E_GPIO_DBGLV_REG_DUMP,      //show error & reg dump
    E_GPIO_DBGLV_INFO,          //show error & informaiton
    E_GPIO_DBGLV_ALL            //show error, information & funciton name
}GPIO_DbgLv;

typedef enum _GPIO_Result
{
    E_GPIO_NOT_SUPPORT = -1,
    E_GPIO_FAIL = 0,
    E_GPIO_OK = 1
}GPIO_Result;

typedef struct _GPIO_Info
{
    MS_U32      u32GPIONum;
    MS_U32      u32IOMap;
    MS_U32      u32IOMap_PM;
}GPIO_Info;

typedef struct _GPIO_Status
{
    MS_U8   u8DbgLevel;
    MS_BOOL bInit;
}GPIO_Status;

typedef int MS_GPIO_NUM;        ///< GPIO handle, for default operations,


MS_BOOL MDrv_GPIO_SetIOMapBase(void);

GPIO_Result MDrv_GPIO_GetLibVer(const MSIF_Version **ppVersion);
GPIO_Result MDrv_GPIO_SetDbgLevel(GPIO_DbgLv eLevel);
const GPIO_Info* MDrv_GPIO_GetInfo(void);
void MDrv_GPIO_GetStatus(GPIO_Status *pStatus);

void mdrv_gpio_init(void);
void mdrv_gpio_set_high(MS_GPIO_NUM gpio);
void mdrv_gpio_set_low(MS_GPIO_NUM gpio);
void mdrv_gpio_set_input(MS_GPIO_NUM gpio);
//void mdrv_gpio_set_output(MS_GPIO_NUM gpio);
int mdrv_gpio_get_inout(MS_GPIO_NUM gpio);
int mdrv_gpio_get_level(MS_GPIO_NUM gpio);

typedef enum _GPIO_Edge
{
    E_GPIO_RISING_EDGE,
    E_GPIO_FALLING_EDGE
} GPIO_Edge;

/// Callback function which is called in GPIO ISR.
typedef void ( *GPIO_Callback ) (void);

GPIO_Result mdrv_gpio_attach_interrupt(MS_GPIO_NUM gpio_num,GPIO_Edge gpio_edge_type,GPIO_Callback pCallback);
GPIO_Result mdrv_gpio_detach_interrupt(MS_GPIO_NUM gpio_num);
void mdrv_gpio_interrupt_action(void);
void mdrv_gpio_enable_interrupt_all(void);
void mdrv_gpio_disable_interrupt_all(void);
GPIO_Result mdrv_gpio_enable_interrupt(MS_GPIO_NUM gpio);
GPIO_Result mdrv_gpio_disable_interrupt(MS_GPIO_NUM gpio);


#ifdef __cplusplus
}
#endif

#endif /* __DRVGPIO_H__ */

