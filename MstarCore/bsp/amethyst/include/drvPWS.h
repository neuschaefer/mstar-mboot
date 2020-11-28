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
////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVPWS_H_
#define _DRVPWS_H_

////////////////////////////////////////////////////////////////////////////////
/// @file drvPWS.h
/// @author MStar Semiconductor Inc.
/// @brief power saving driver
////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// Header Files
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C"
{
#endif

#include "MsCommon.h"

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define MSIF_PWS_LIB_CODE                     {'P','W','S','_'}        //Lib code
#define MSIF_PWS_LIBVER                       {'0','2'}            //LIB version
#define MSIF_PWS_BUILDNUM                     {'0','9'}            //Build Number
#define MSIF_PWS_CHANGELIST                   {'0','0','4','4','8','1','7','6'} //P4 ChangeList Number

#define PWS_API_VERSION                /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_PWS_LIB_CODE,                        /* IP__                                             */  \
    MSIF_PWS_LIBVER,                          /* 0.0 ~ Z.Z                                        */  \
    MSIF_PWS_BUILDNUM,                        /* 00 ~ 99                                          */  \
    MSIF_PWS_CHANGELIST,                      /* CL#                                              */  \
    MSIF_OS

#define SIOCDEVON       0x89F1
#define SIOCDEVOFF      0x89F2

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

typedef enum
{
    PWS_FAIL    = 0,
    PWS_SUCCESS = 1
} E_PWS_Result;

#if defined (MSOS_TYPE_LINUX)
typedef enum
{
    PHY_OFF    = 0,
    PHY_ON   = 1
} E_PWS_PHY;
#endif

typedef enum
{
    PWS_ADD_SOURCE  = 0,
    PWS_DEL_SOURCE  = 1,
    PWS_INVAILD_OP  = 2
} E_PWS_Operation;

typedef enum
{
    PWS_FULL    = 0,
    PWS_OFF_LINE_DETECT = 1
} E_PWS_Sync;

typedef enum
{
    _NO_SOURCE_   = 0,
    _USB_         = BIT_(0),
    _SV_          = BIT_(1),
    _HDMI4_       = BIT_(2),
    _HDMI3_       = BIT_(3),
    _HDMI2_       = BIT_(4),
    _HDMI1_       = BIT_(5),
    _YPbPr_       = BIT_(6),
    _SCART_       = BIT_(7),
    _RGB_         = BIT_(8),
    _CVBS_        = BIT_(9),
    _ATV_SSIF_    = BIT_(10),
    _ATV_VIF_     = BIT_(11),
    _DTV_ATSC_    = BIT_(12),
    _DTV_DVB_     = BIT_(13),
    _CVBSOe_      = BIT_(14),
    _CVBSOi_      = BIT_(15),
    _UNKNOWN_     = BIT_(16)
} E_PWS_SouceInfo;

typedef enum
{
    E_PWS_DBGLV_NONE,          //no debug message
    E_PWS_DBGLV_ERR_ONLY,      //show error only
    E_PWS_DBGLV_REG_DUMP,      //show error & reg dump
    E_PWS_DBGLV_INFO,          //show error & informaiton
    E_PWS_DBGLV_ALL            //show error, information & funciton name
} E_PWS_DBG_LEVEL;

typedef struct
{
    E_PWS_DBG_LEVEL u8DbgLevel;
    MS_BOOL bInit;
} PWS_Status;

typedef struct
{
    E_PWS_SouceInfo SourceList;
    MS_U32 u32IOMap;
} PWS_Info;

typedef enum
{
    E_PWS_API_UNUSED = 0,
    E_PWS_USE_HANDLE_SOURCE = 1,
    E_PWS_USE_HANDLE_IP = 2
} E_PWS_Use;

typedef enum
{
    E_PWS_IP_ON  = 0,
    E_PWS_IP_OFF = 1
} E_PWS_IpPowerCtrl;

typedef enum
{
    E_PWS_IP_CALLBACK_BEFORE_ON  = 0,
    E_PWS_IP_CALLBACK_BEFORE_OFF = 1,
    E_PWS_IP_CALLBACK_AFTER_ON   = 2,
    E_PWS_IP_CALLBACK_AFTER_OFF  = 3,
    E_PWS_IP_CALLBACK_UNKNOWN = 4
} E_PWS_CallbackCtrl;

#define STR_LEN     32
typedef void (*P_PWS_Callback)(void);
typedef struct
{
    E_PWS_CallbackCtrl ctrl;
    unsigned char regName[STR_LEN];
    P_PWS_Callback _PWSCallback;
} PWS_RegisterCallback;

typedef enum
{
    E_PWS_VIF_NO_SAW     = 0,
    E_PWS_VIF_SINGLE_SAW = 1,
    E_PWS_VIF_DUAL_SAW   = 2,
    E_PWS_VIF_SINGLE_SAW_DIF = 3,
    E_PWS_VIF_UNKNOWN    = 3
} E_PWS_VIF_type;

#define PWS_Register_CB_size    2
//------------------------------------------------------------------------------
// Extern Function
//------------------------------------------------------------------------------
E_PWS_Result MDrv_PWS_GetLibVer(const MSIF_Version **ppVersion);
E_PWS_Result MDrv_PWS_SetDbgLevel(E_PWS_DBG_LEVEL eLEVEL);
void         MDrv_PWS_GetInfo(PWS_Info *pInfo);
void         MDrv_PWS_GetStatus(PWS_Status *pStatus);
E_PWS_SouceInfo MDrv_PWS_GetSourceInfo(void);
MS_U16       MDrv_PWS_Read2Byte(MS_U32 u32RegAddr );

E_PWS_Result MDrv_PWS_Init(E_PWS_VIF_type eVifType);
E_PWS_Result MDrv_PWS_HandleSource(E_PWS_Operation operation,E_PWS_SouceInfo source,E_PWS_Sync sync_type);
E_PWS_Result MDrv_PWS_HandleIP(E_PWS_IpPowerCtrl IpPowerCtrl,const unsigned char *RegName);
E_PWS_Result MDrv_PWS_RegisterCallback(MS_U8 index,E_PWS_CallbackCtrl cb_ctrl,unsigned char *RegName,P_PWS_Callback pfCallback);
E_PWS_Result MDrv_PWS_CancelCallback(MS_U8 index);
#if defined (MSOS_TYPE_LINUX)
E_PWS_Result MDrv_PWS_PHYPower(E_PWS_PHY bSetFlag);
#endif

#ifdef __cplusplus
}
#endif

#endif
