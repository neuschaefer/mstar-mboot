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
    MS_BOOL                         Init;
} COPRO_DrvInfo;


typedef struct _COPRO_DrvStatus
{
    MS_BOOL                         HwBusy;
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
    void MDrv_COPRO_SetDbgLevel(MS_U8 level);
    MS_U32 MDrv_COPRO_GetBase(void);
    MS_U32 MDrv_CPU_QueryClock(void);

#ifdef __cplusplus
}
#endif

#endif // _DRV_CPU_H_

