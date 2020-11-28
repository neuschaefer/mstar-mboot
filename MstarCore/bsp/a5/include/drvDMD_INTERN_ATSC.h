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
/// @file   drvDMD_DVBT_INTERN.h
/// @brief  DVBT Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_ATSC_H_
#define _DRV_ATSC_H_

#include "MsCommon.h"

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
#define MSIF_DMD_ATSC_INTERN_LIB_CODE           {'D','M','D','_','A','T', 'S','C','_','I','N','T','E','R','N','_'} //Lib code
#define MSIF_DMD_ATSC_INTERN_LIBVER             {'0','0'}      //LIB version
#define MSIF_DMD_ATSC_INTERN_BUILDNUM           {'0','0' }    //Build Number
#define MSIF_DMD_ATSC_INTERN_CHANGELIST         {'0','0','0','0','0','0','0','0'} //P4 ChangeList Number

#define DMD_ATSC_INTERN_VER                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_DMD_ATSC_INTERN_LIB_CODE,      /* IP__                                             */  \
    MSIF_DMD_ATSC_INTERN_LIBVER,        /* 0.0 ~ Z.Z                                        */  \
    MSIF_DMD_ATSC_INTERN_BUILDNUM,      /* 00 ~ 99                                          */  \
    MSIF_DMD_ATSC_INTERN_CHANGELIST,    /* CL#                                              */  \
    MSIF_OS

#define IS_BITS_SET(val, bits)                  (((val)&(bits)) == (bits))

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef enum
{
    DMD_ATSC_DBGLV_NONE,    // disable all the debug message
    DMD_ATSC_DBGLV_INFO,    // information
    DMD_ATSC_DBGLV_NOTICE,  // normal but significant condition
    DMD_ATSC_DBGLV_WARNING, // warning conditions
    DMD_ATSC_DBGLV_ERR,     // error conditions
    DMD_ATSC_DBGLV_CRIT,    // critical conditions
    DMD_ATSC_DBGLV_ALERT,   // action must be taken immediately
    DMD_ATSC_DBGLV_EMERG,   // system is unusable
    DMD_ATSC_DBGLV_DEBUG,   // debug-level messages
} DMD_ATSC_DbgLv;

typedef enum
{
    DMD_ATSC_DEMOD_ATSC_VSB,
    DMD_ATSC_DEMOD_ATSC_64QAM,
    DMD_ATSC_DEMOD_ATSC_256QAM,
    DMD_ATSC_DEMOD_MAX,
    DMD_ATSC_DEMOD_NULL = DMD_ATSC_DEMOD_MAX,
} DMD_ATSC_DEMOD_TYPE;

typedef enum
{
    DMD_ATSC_SIGNAL_NO                   = 0,    /* little or no input power detected    */
    DMD_ATSC_SIGNAL_WEAK                 = 1,    /* some power detected.                 */
    DMD_ATSC_SIGNAL_MODERATE             = 2,
    DMD_ATSC_SIGNAL_STRONG               = 4,
    DMD_ATSC_SIGNAL_VERY_STRONG          = 8
} DMD_ATSC_SIGNAL_CONDITION;

typedef enum
{
    DMD_ATSC_GETLOCK,
    DMD_ATSC_GETLOCK_VSB_AGCLOCK,
    DMD_ATSC_GETLOCK_VSB_PRELOCK, // pilot lock
    DMD_ATSC_GETLOCK_VSB_FSYNCLOCK,
    DMD_ATSC_GETLOCK_VSB_CELOCK,
    DMD_ATSC_GETLOCK_VSB_FECLOCK,
    DMD_ATSC_GETLOCK_QAM_AGCLOCK,
    DMD_ATSC_GETLOCK_QAM_PRELOCK, // TR lock
    DMD_ATSC_GETLOCK_QAM_MAINLOCK,
} DMD_ATSC_GETLOCK_TYPE;

typedef enum
{
    DMD_ATSC_LOCK,
    DMD_ATSC_CHECKING,
    DMD_ATSC_CHECKEND,
    DMD_ATSC_UNLOCK,
    DMD_ATSC_NULL,
} DMD_ATSC_LOCK_STATUS;

/// For demod init
typedef struct
{
    // init
    MS_U16 u16VSBAGCLockCheckTime;
    MS_U16 u16VSBPreLockCheckTime;
    MS_U16 u16VSBFSyncLockCheckTime;
    MS_U16 u16VSBFECLockCheckTime;

    MS_U16 u16QAMAGCLockCheckTime;
    MS_U16 u16QAMPreLockCheckTime;
    MS_U16 u16QAMMainLockCheckTime;
    
    // register init
    MS_U8 *u8DMD_ATSC_DSPRegInitExt; // TODO use system variable type
    MS_U8 u8DMD_ATSC_DSPRegInitSize;
    MS_U8 *u8DMD_ATSC_InitExt; // TODO use system variable type
    
    MS_U16  u16IF_KHZ;
    MS_BOOL bIQSwap; 
} DMD_ATSC_InitData;

typedef enum
{
    E_DMD_ATSC_FAIL=0,
    E_DMD_ATSC_OK=1
} DMD_ATSC_Result;

typedef struct
{
    MS_U8 u8Version;
    MS_U32 u32ATSCScanTimeStart;
    MS_U32 u32ATSCFECLockTime;
    DMD_ATSC_LOCK_STATUS eStatus;
    MS_U32 u32ATSCLockStatus;
} DMD_ATSC_Info;

#define DMD_ATSC_LOCK_VSB_PRE_LOCK BIT_(0)
#define DMD_ATSC_LOCK_VSB_FSYNC_LOCK BIT_(1)
#define DMD_ATSC_LOCK_VSB_CE_LOCK BIT_(2)
#define DMD_ATSC_LOCK_VSB_FEC_LOCK BIT_(3)

#define DMD_ATSC_LOCK_QAM_AGC_LOCK BIT_(8)
#define DMD_ATSC_LOCK_QAM_PRE_LOCK BIT_(9)
#define DMD_ATSC_LOCK_QAM_MAIN_LOCK BIT_(10)

//typedef void(*P_DMD_ISR_Proc)(MS_U8 u8DMDID);


//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_Init
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_ATSC_Init(DMD_ATSC_InitData *pDMD_DVBT_InitData, MS_U32 u32InitDataLen);
////////////////////////////////////////////////////////////////////////////////
/// Should be called when exit VD input source
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_ATSC_Exit(void);
//------------------------------------------------------------------------------
/// Set detailed level of DVBT driver debug message
/// u8DbgLevel : debug level for Parallel Flash driver\n
/// AVD_DBGLV_NONE,    ///< disable all the debug message\n
/// AVD_DBGLV_INFO,    ///< information\n
/// AVD_DBGLV_NOTICE,  ///< normal but significant condition\n
/// AVD_DBGLV_WARNING, ///< warning conditions\n
/// AVD_DBGLV_ERR,     ///< error conditions\n
/// AVD_DBGLV_CRIT,    ///< critical conditions\n
/// AVD_DBGLV_ALERT,   ///< action must be taken immediately\n
/// AVD_DBGLV_EMERG,   ///< system is unusable\n
/// AVD_DBGLV_DEBUG,   ///< debug-level messages\n
/// @return TRUE : succeed
/// @return FALSE : failed to set the debug level
//------------------------------------------------------------------------------
extern MS_BOOL MDrv_DMD_ATSC_SetDbgLevel(DMD_ATSC_DbgLv u8DbgLevel);
//-------------------------------------------------------------------------------------------------
/// Get the information of DVBT driver\n
/// @return the pointer to the driver information
//-------------------------------------------------------------------------------------------------
extern DMD_ATSC_Info* MDrv_DMD_ATSC_GetInfo(void);
//-------------------------------------------------------------------------------------------------
/// Get DVBT driver version
/// when get ok, return the pointer to the driver version
//-------------------------------------------------------------------------------------------------
extern MS_BOOL MDrv_DMD_ATSC_GetLibVer(const MSIF_Version **ppVersion);
////////////////////////////////////////////////////////////////////////////////
/// To get DVBT's register  value, only for special purpose.\n
/// u16Addr       : the address of DVBT's register\n
/// return the value of AFEC's register\n
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_ATSC_GetReg(MS_U16 u16Addr, MS_U8 *pu8Data);
////////////////////////////////////////////////////////////////////////////////
/// To set DVBT's register value, only for special purpose.\n
/// u16Addr       : the address of DVBT's register\n
/// u8Value        : the value to be set\n
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_ATSC_SetReg(MS_U16 u16Addr, MS_U8 u8Data);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_SetSerialControl
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_ATSC_SetSerialControl(MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_ATSC_SetReset
////////////////////////////////////////////////////////////////////////////////
extern void MDrv_DMD_ATSC_SetReset(void);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_SetConfig
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_ATSC_SetConfig(DMD_ATSC_DEMOD_TYPE eType, MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_SetActive
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_ATSC_SetActive(MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_Get_Lock
////////////////////////////////////////////////////////////////////////////////
extern DMD_ATSC_LOCK_STATUS MDrv_DMD_ATSC_GetLock(DMD_ATSC_GETLOCK_TYPE eType);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_ATSC_GetModulationMode
////////////////////////////////////////////////////////////////////////////////
extern DMD_ATSC_DEMOD_TYPE MDrv_DMD_ATSC_GetModulationMode(void);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetSignalStrength
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_ATSC_GetSignalStrength(MS_U16 *u16Strength);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetSignalQuality
////////////////////////////////////////////////////////////////////////////////
extern DMD_ATSC_SIGNAL_CONDITION MDrv_DMD_ATSC_GetSignalQuality(void);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetCellID
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_ATSC_GetCellID(MS_U16 *u16CellID);
#ifdef __cplusplus
}
#endif


#endif // _DRV_DVBT_H_

