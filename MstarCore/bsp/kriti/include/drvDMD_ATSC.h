//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
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

#include "MsDevice.h"
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

typedef enum _e_ATSC_HAL_COMMAND
{
    CMD_ATSC_Exit = 0,
    CMD_ATSC_InitClk,
    CMD_ATSC_Download,
    CMD_ATSC_SoftReset,
    CMD_ATSC_SetModeClean,
    CMD_ATSC_Active,
    CMD_ATSC_Vsb_FEC_Lock,
    CMD_ATSC_FSync_Lock,
    CMD_ATSC_Vsb_PreLock,
    CMD_ATSC_Vsb_QAM_AGCLock,
    CMD_ATSC_Vsb_CE_Lock,
    CMD_ATSC_ReadPKTERR,
    CMD_ATSC_FWVERSION,
    CMD_ATSC_CheckSignalCondition,
    CMD_ATSC_QAM_Main_Lock,
    CMD_ATSC_QAM_PreLock,
    CMD_ATSC_ReadFrequencyOffset,
    CMD_ATSC_ReadIFAGC,
    CMD_ATSC_ReadSNRPercentage,
    CMD_ATSC_Set256QamMode,
    CMD_ATSC_Set64QamMod,
    CMD_ATSC_Check8VSB64_256QAM,
    CMD_ATSC_SetVsbMode,
    //CMD_ATSC_GPIO_SET_LEVEL,
    //CMD_ATSC_GPIO_OUT_ENABLE,
    //CMD_ATSC_GetPostViterbiBer,
    //CMD_ATSC_GetPreViterbiBer,
    //CMD_ATSC_GetFreqOffset,
    //CMD_ATSC_GetSNR,
    CMD_ATSC_IIC_Bypass_Mode,
    CMD_ATSC_RepeaterDisable,
    CMD_ATSC_RepeaterEnable,
    CMD_ATSC_TS_INTERFACE_CONFIG,
    CMD_ATSC_GetPostViterbiBer,
    CMD_ATSC_SELDMD,
    CMD_ATSC_GETDMD_NUM,
    CMD_ATSC_TOPControl,
    CMD_ATSC_ADCOut_CTL,
    CMD_ATSC_CHECK_CURRENT_LOADING,
    CMD_ATSC_TURN_ON_DOWNLOAD_FW_FLOW,
    CMD_ATSC_GetIFAGC_HighByte,
    CMD_ATSC_GetSymbolRate,
    CMD_ATSC_SET_QAM_SR,
}e_ATSC_HAL_COMMAND;

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
typedef enum _eDMD_SEL
{
    DMD0 = 0,
    DMD1,
    HK,
}eDMD_SEL;
#define DUAL_DMD 

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
    DMD_ATSC_DEMOD_ATSC_16QAM,
    DMD_ATSC_DEMOD_ATSC_32QAM,
    DMD_ATSC_DEMOD_ATSC_64QAM,
    DMD_ATSC_DEMOD_ATSC_128QAM,
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

typedef enum
{
    I_PAD,
    Q_PAD,
} DMD_ATSC_SEL_IQPAD;

typedef enum
{
    QAM_64,
    QAM_256,
} DMD_ATSC_QAM_TYPE;

typedef struct
{
    MS_U8   QAM_type;
    MS_U16  symbol_rate;
}DMD_J83B_Info;

/// For demod init
typedef struct
{
    // init
    MS_U16 u16VSBAGCLockCheckTime;//50
    MS_U16 u16VSBPreLockCheckTime;//300
    MS_U16 u16VSBFSyncLockCheckTime;//1200
    MS_U16 u16VSBFECLockCheckTime;//5000

    MS_U16 u16QAMAGCLockCheckTime;//50
    MS_U16 u16QAMPreLockCheckTime;//1000
    MS_U16 u16QAMMainLockCheckTime;//3000

    // register init
    MS_U8 *u8DMD_ATSC_DSPRegInitExt; // TODO use system variable type
    MS_U8 u8DMD_ATSC_DSPRegInitSize;
    MS_U8 *u8DMD_ATSC_InitExt; // TODO use system variable type

    //By Tuners:
    MS_U16  u16IF_KHZ;//By Tuners
    MS_BOOL bIQSwap;//0
    MS_U16  u16AGC_REFERENCE;//0
    MS_BOOL bTunerGainInvert;//0
   
    //By IC:
    MS_U8   u8IS_DUAL;//0
    MS_BOOL bIsExtDemod;//0

    MS_U8   u1TsConfigByte_SerialMode : 1;
    MS_U8   u1TsConfigByte_DataSwap   : 1;
    MS_U8   u1TsConfigByte_ClockInv   : 1;
    MS_U8   u5TsConfigByte_DivNum     : 5;

    MS_U8 u8I2CSlaveAddr;
    MS_U8 u8I2CSlaveBus;
    //MS_BOOL bIsExtDemod;
    MS_BOOL (*I2C_WriteBytes)(MS_U16 u16BusNumSlaveID, MS_U8 u8addrcount, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data);
    MS_BOOL (*I2C_ReadBytes)(MS_U16 u16BusNumSlaveID, MS_U8 u8AddrNum, MS_U8* paddr, MS_U16 u16size, MS_U8* pu8data);
    MS_U16  u16AgcReferenceValue;
    MS_U8   u8DMD_ATSC_Select_IQPad;
    //MS_U16  u16symbol_rate;
    //MS_U8   QAM_Type;
} DMD_ATSC_InitData;

typedef struct
{
    MS_U8 u16IF_KHZ_L;
    MS_U8 u16IF_KHZ_H;
    MS_U8 u8IQSwap; 
    MS_U8 u16AGC_REF_L;
    MS_U8 u16AGC_REF_H;
    MS_U8 u8IS_DUAL;
    MS_U8 u8DMD_ID;
}BACKEND_REG_DATA;

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


typedef struct _s_ATSC_HAL_FUNCTION_TABLE
{
    MS_BOOL (*HAL_DMD_ATSC_IOCTL_CMD)(e_ATSC_HAL_COMMAND eCmd, void *pHandle);
}s_ATSC_HAL_FUNCTION_TABLE;
//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_Init
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_Init(DMD_ATSC_InitData *pDMD_DVBT_InitData, MS_U32 u32InitDataLen);
////////////////////////////////////////////////////////////////////////////////
/// Should be called when exit VD input source
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_Exit(void);

DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_IIC_BYPASS_MODE(MS_BOOL bEnable);
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
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_SetDbgLevel(DMD_ATSC_DbgLv u8DbgLevel);
//-------------------------------------------------------------------------------------------------
/// Get the information of DVBT driver\n
/// @return the pointer to the driver information
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC extern DMD_ATSC_Info* MDrv_DMD_ATSC_GetInfo(void);
//-------------------------------------------------------------------------------------------------
/// Get DVBT driver version
/// when get ok, return the pointer to the driver version
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_GetLibVer(const MSIF_Version **ppVersion);
////////////////////////////////////////////////////////////////////////////////
/// To get DVBT's register  value, only for special purpose.\n
/// u16Addr       : the address of DVBT's register\n
/// return the value of AFEC's register\n
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_GetReg(MS_U16 u16Addr, MS_U8 *pu8Data);
////////////////////////////////////////////////////////////////////////////////
/// To set DVBT's register value, only for special purpose.\n
/// u16Addr       : the address of DVBT's register\n
/// u8Value        : the value to be set\n
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_SetReg(MS_U16 u16Addr, MS_U8 u8Data);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_SetSerialControl
////////////////////////////////////////////////////////////////////////////////
///DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_SetSerialControl(MS_BOOL bEnable);
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_SetSerialControl(MS_U8 u8TsConfigData);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_ATSC_SetReset
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_SetReset(void);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_SetConfig
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_SetConfig(DMD_ATSC_DEMOD_TYPE eType, MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_SetActive
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_SetActive(MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_Get_Lock
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern DMD_ATSC_LOCK_STATUS MDrv_DMD_ATSC_GetLock(DMD_ATSC_GETLOCK_TYPE eType);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_ATSC_GetModulationMode
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern DMD_ATSC_DEMOD_TYPE MDrv_DMD_ATSC_GetModulationMode(void);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetSignalStrength
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_GetSignalStrength(MS_U16 *u16Strength);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_ATSC_GetIfAgcValue
DLL_PUBLIC extern MS_S8 MDrv_DMD_ATSC_GetIfAgcValue(void);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetSignalQuality
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern DMD_ATSC_SIGNAL_CONDITION MDrv_DMD_ATSC_GetSignalQuality(void);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetCellID
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_GetCellID(MS_U16 *u16CellID);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_ATSC_Read_PKT_ERR
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_Read_uCPKT_ERR(MS_U16 *u16PacketErr);
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_GetPreViterbiBer(float *ber);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_ATSC_GetPostViterbiBer
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_GetPostViterbiBer(float *ber);
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_Initial_Hal_Interface(void);    //this function will be implemented in ATSC Hal layer

DLL_PUBLIC extern MS_BOOL MDrv_INTERNAL_DMD_ATSC_Link_Func(void);    //this function will be implemented in ISDBT Hal layer
DLL_PUBLIC extern MS_BOOL MDrv_EXTERNAL_DMD_ATSC_Link_Func(void);    //this function will be implemented in ISDBT Hal layer


//extern MS_U8 MDrv_DMD_ATSC_GetSNRPercentage(void);

DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_SetVsbMode(void);

DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_Set256QamMode(void);

DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_Set64QamMode(void);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_ATSC_SEL_DMD
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_SEL_DMD(eDMD_SEL eDMD_NUM);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_ATSC_GET_DMD_NUM
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern eDMD_SEL MDrv_DMD_ATSC_GET_DMD_NUM(void);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_ATSC_LoadFW
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_LoadFW(eDMD_SEL DMD_NUM);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_ATSC_ADCOut_CTL
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_ADCOut_CTL(eDMD_SEL DMD_NUM);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_ATSC_GetSNRPercentage
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_U8 MDrv_DMD_ATSC_GetSNRPercentage(void);

DLL_PUBLIC extern MS_U32 MDrv_DMD_ATSC_SetPowerState(EN_POWER_MODE u16PowerState);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_ATSC_GetSymbolRate
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_GetSymbolRate(float *SymRate);
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_ATSC_Set_QAM_SR
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_Set_QAM_SR(DMD_ATSC_QAM_TYPE QAM_type, MS_U16 symbol_rate);
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_ATSC_Clear_QAM_SR
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_Clear_QAM_SR(void);
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif


#endif // _DRV_DVBT_H_

