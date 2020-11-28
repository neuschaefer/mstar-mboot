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

#ifndef _DRV_DTMB_H_
#define _DRV_DTMB_H_

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
#define MSIF_DMD_DTMB_INTERN_LIB_CODE           {'D','M','D','_','A','T', 'S','C','_','I','N','T','E','R','N','_'} //Lib code
#define MSIF_DMD_DTMB_INTERN_LIBVER             {'0','0'}      //LIB version
#define MSIF_DMD_DTMB_INTERN_BUILDNUM           {'0','0' }    //Build Number
#define MSIF_DMD_DTMB_INTERN_CHANGELIST         {'0','0','0','0','0','0','0','0'} //P4 ChangeList Number

typedef enum _e_DTMB_HAL_COMMAND
{
    CMD_DTMB_Exit = 0,
    CMD_DTMB_InitClk,
    CMD_DTMB_Download,
    CMD_DTMB_SoftReset,
    CMD_DTMB_SetModeClean,
    CMD_DTMB_Active,
    CMD_DTMB_Dtmb_FEC_Lock,
    CMD_DTMB_PNM_Lock,
    CMD_DTMB_Dtmb_PreLock,
    CMD_DTMB_Vsb_QAM_AGCLock,
    CMD_DTMB_Vsb_CE_Lock,
    CMD_DTMB_ReadPKTERR,
    CMD_DTMB_FWVERSION,
    CMD_DTMB_CheckSignalCondition,
    CMD_DTMB_QAM_Main_Lock,
    CMD_DTMB_QAM_PreLock,
    CMD_DTMB_ReadFrequencyOffset,
    CMD_DTMB_ReadIFAGC,
    CMD_DTMB_ReadSNRPercentage,
    CMD_DTMB_Set256QamMode,
    CMD_DTMB_SetDvbcMode,
    CMD_DTMB_Check8VSB64_256QAM,
    CMD_DTMB_SetDtmbMode,
    //CMD_DTMB_GPIO_SET_LEVEL,
    //CMD_DTMB_GPIO_OUT_ENABLE,
    //CMD_DTMB_GetPostViterbiBer,
    //CMD_DTMB_GetPreViterbiBer,
    //CMD_DTMB_GetFreqOffset,
    //CMD_DTMB_GetSNR,
    CMD_DTMB_IIC_Bypass_Mode,
    CMD_DTMB_RepeaterDisable,
    CMD_DTMB_RepeaterEnable,
    CMD_DTMB_TS_INTERFACE_CONFIG,
    CMD_DTMB_GetPostViterbiBer,
    CMD_DTMB_SELDMD,
    CMD_DTMB_GETDMD_NUM,
    CMD_DTMB_TOPControl,
    CMD_DTMB_ADCOut_CTL,
    CMD_DTMB_CHECK_CURRENT_LOADING,
    CMD_DTMB_TURN_ON_DOWNLOAD_FW_FLOW,
    CMD_DTMB_CHECK_FW_STATUS,
    CMD_DTMB_SW_SSPI_GPIO,
    CMD_DTMB_GPIO_GET_LEVEL,
    CMD_DTMB_GPIO_SET_LEVEL,
    CMD_DTMB_GPIO_OUT_ENABLE,
    CMD_DTMB_GET_PRELDPCBER,
    CMD_DTMB_GetIFAGC_HighByte    
}e_DTMB_HAL_COMMAND;

#define DMD_DTMB_INTERN_VER                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_DMD_DTMB_INTERN_LIB_CODE,      /* IP__                                             */  \
    MSIF_DMD_DTMB_INTERN_LIBVER,        /* 0.0 ~ Z.Z                                        */  \
    MSIF_DMD_DTMB_INTERN_BUILDNUM,      /* 00 ~ 99                                          */  \
    MSIF_DMD_DTMB_INTERN_CHANGELIST,    /* CL#                                              */  \
    MSIF_OS

#define IS_BITS_SET(val, bits)                  (((val)&(bits)) == (bits))


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef enum
{
    DMD_DTMB_DBGLV_NONE,    // disable all the debug message
    DMD_DTMB_DBGLV_INFO,    // information
    DMD_DTMB_DBGLV_NOTICE,  // normal but significant condition
    DMD_DTMB_DBGLV_WARNING, // warning conditions
    DMD_DTMB_DBGLV_ERR,     // error conditions
    DMD_DTMB_DBGLV_CRIT,    // critical conditions
    DMD_DTMB_DBGLV_ALERT,   // action must be taken immediately
    DMD_DTMB_DBGLV_EMERG,   // system is unusable
    DMD_DTMB_DBGLV_DEBUG,   // debug-level messages
} DMD_DTMB_DbgLv;

typedef enum
{
    DMD_DTMB_DEMOD_DTMB,
    DMD_DTMB_DEMOD_DVBC,
    DMD_DTMB_DEMOD_MAX,
    DMD_DTMB_DEMOD_NULL = DMD_DTMB_DEMOD_MAX,
} DMD_DTMB_DEMOD_TYPE;

typedef enum
{
    DMD_DTMB_SIGNAL_NO                   = 0,    /* little or no input power detected    */
    DMD_DTMB_SIGNAL_WEAK                 = 1,    /* some power detected.                 */
    DMD_DTMB_SIGNAL_MODERATE             = 2,
    DMD_DTMB_SIGNAL_STRONG               = 4,
    DMD_DTMB_SIGNAL_VERY_STRONG          = 8
} DMD_DTMB_SIGNAL_CONDITION;

typedef enum
{
    DMD_DTMB_GETLOCK,
    DMD_DTMB_GETLOCK_VSB_AGCLOCK,
    DMD_DTMB_GETLOCK_VSB_PRELOCK, // pilot lock
    DMD_DTMB_GETLOCK_VSB_FSYNCLOCK,
    DMD_DTMB_GETLOCK_VSB_CELOCK,
    DMD_DTMB_GETLOCK_VSB_FECLOCK,
    DMD_DTMB_GETLOCK_QAM_AGCLOCK,
    DMD_DTMB_GETLOCK_QAM_PRELOCK, // TR lock
    DMD_DTMB_GETLOCK_QAM_MAINLOCK,
} DMD_DTMB_GETLOCK_TYPE;

typedef enum
{
    DMD_DTMB_LOCK,
    DMD_DTMB_CHECKING,
    DMD_DTMB_CHECKEND,
    DMD_DTMB_UNLOCK,
    DMD_DTMB_NULL,
} DMD_DTMB_LOCK_STATUS;

/// For demod init
typedef struct
{
    // init
    MS_U16 u16VSBAGCLockCheckTime;//50
    MS_U16 u16DTMBPreLockCheckTime;//300
    MS_U16 u16DTMBPNMLockCheckTime;//1200
    MS_U16 u16DTMBFECLockCheckTime;//5000

    MS_U16 u16QAMAGCLockCheckTime;//50
    MS_U16 u16QAMPreLockCheckTime;//1000
    MS_U16 u16QAMMainLockCheckTime;//3000

    // register init
    MS_U8 *u8DMD_DTMB_DSPRegInitExt; // TODO use system variable type
    MS_U8 u8DMD_DTMB_DSPRegInitSize;
    MS_U8 *u8DMD_DTMB_InitExt; // TODO use system variable type

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
    MS_U32  u32TdiStartAddr;    
    
    MS_BOOL bIsUseSspiLoadCode;
    
} DMD_DTMB_InitData;

typedef enum
{
    E_DMD_DTMB_FAIL=0,
    E_DMD_DTMB_OK=1
} DMD_DTMB_Result;

typedef struct
{
    MS_U8 u8Version;
    MS_U32 u32DTMBScanTimeStart;
    MS_U32 u32DTMBFECLockTime;
    DMD_DTMB_LOCK_STATUS eStatus;
    MS_U32 u32DTMBLockStatus;
} DMD_DTMB_Info;

typedef struct _s_DTMB_GPIO_INTERFACE
{
    MS_U8   u8Pin;
    MS_BOOL bLevel;
} s_DTMB_GPIO_INTERFACE;

#define DMD_DTMB_LOCK_DTMB_PRE_LOCK BIT_(0)
#define DMD_DTMB_LOCK_DTMB_PNM_LOCK BIT_(1)
#define DMD_DTMB_LOCK_VSB_CE_LOCK BIT_(2)
#define DMD_DTMB_LOCK_DTMB_FEC_LOCK BIT_(3)

#define DMD_DTMB_LOCK_QAM_AGC_LOCK BIT_(8)
#define DMD_DTMB_LOCK_QAM_PRE_LOCK BIT_(9)
#define DMD_DTMB_LOCK_QAM_MAIN_LOCK BIT_(10)

//typedef void(*P_DMD_ISR_Proc)(MS_U8 u8DMDID);


typedef struct _s_DTMB_HAL_FUNCTION_TABLE
{
    MS_BOOL (*HAL_DMD_DTMB_IOCTL_CMD)(e_DTMB_HAL_COMMAND eCmd, void *pHandle);
}s_DTMB_HAL_FUNCTION_TABLE;
//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_Init
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DTMB_Init(DMD_DTMB_InitData *pDMD_DVBT_InitData, MS_U32 u32InitDataLen);
////////////////////////////////////////////////////////////////////////////////
/// Should be called when exit VD input source
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DTMB_Exit(void);

extern MS_BOOL MDrv_DMD_DTMB_IIC_BYPASS_MODE(MS_BOOL bEnable);
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
extern MS_BOOL MDrv_DMD_DTMB_SetDbgLevel(DMD_DTMB_DbgLv u8DbgLevel);
//-------------------------------------------------------------------------------------------------
/// Get the information of DVBT driver\n
/// @return the pointer to the driver information
//-------------------------------------------------------------------------------------------------
extern DMD_DTMB_Info* MDrv_DMD_DTMB_GetInfo(void);
//-------------------------------------------------------------------------------------------------
/// Get DVBT driver version
/// when get ok, return the pointer to the driver version
//-------------------------------------------------------------------------------------------------
extern MS_BOOL MDrv_DMD_DTMB_GetLibVer(const MSIF_Version **ppVersion);
////////////////////////////////////////////////////////////////////////////////
/// To get DVBT's register  value, only for special purpose.\n
/// u16Addr       : the address of DVBT's register\n
/// return the value of AFEC's register\n
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DTMB_GetReg(MS_U16 u16Addr, MS_U8 *pu8Data);
////////////////////////////////////////////////////////////////////////////////
/// To set DVBT's register value, only for special purpose.\n
/// u16Addr       : the address of DVBT's register\n
/// u8Value        : the value to be set\n
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DTMB_SetReg(MS_U16 u16Addr, MS_U8 u8Data);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_SetSerialControl
////////////////////////////////////////////////////////////////////////////////
///extern MS_BOOL MDrv_DMD_DTMB_SetSerialControl(MS_BOOL bEnable);
extern MS_BOOL MDrv_DMD_DTMB_SetSerialControl(MS_U8 u8TsConfigData);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DTMB_SetReset
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DTMB_SetReset(void);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_SetConfig
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DTMB_SetConfig(DMD_DTMB_DEMOD_TYPE eType, MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_SetActive
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DTMB_SetActive(MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_Get_Lock
////////////////////////////////////////////////////////////////////////////////
extern DMD_DTMB_LOCK_STATUS MDrv_DMD_DTMB_GetLock(DMD_DTMB_GETLOCK_TYPE eType);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DTMB_GetModulationMode
////////////////////////////////////////////////////////////////////////////////
extern DMD_DTMB_DEMOD_TYPE MDrv_DMD_DTMB_GetModulationMode(void);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetSignalStrength
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DTMB_GetSignalStrength(MS_U16 *u16Strength);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetSignalQuality
////////////////////////////////////////////////////////////////////////////////
extern MS_U8 MDrv_DMD_DTMB_GetSignalQuality(void);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DTMB_GetIfAgcValue
extern MS_S8 MDrv_DMD_DTMB_GetIfAgcValue(void);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetCellID
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DTMB_GetCellID(MS_U16 *u16CellID);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DTMB_Read_PKT_ERR
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DTMB_Read_uCPKT_ERR(MS_U16 *u16PacketErr);
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DTMB_GetPreViterbiBer(float *ber);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DTMB_GetPostViterbiBer
extern MS_BOOL MDrv_DMD_DTMB_GetPostViterbiBer(float *ber);
extern MS_BOOL MDrv_DMD_DTMB_Initial_Hal_Interface(void);    //this function will be implemented in DTMB Hal layer

extern MS_BOOL MDrv_INTERNAL_DMD_DTMB_Link_Func(void);    //this function will be implemented in ISDBT Hal layer
extern MS_BOOL MDrv_EXTERNAL_DMD_DTMB_Link_Func(void);    //this function will be implemented in ISDBT Hal layer


//extern MS_U8 MDrv_DMD_DTMB_GetSNRPercentage(void);

extern MS_BOOL MDrv_DMD_DTMB_SetDtmbMode(void);

extern MS_BOOL MDrv_DMD_DTMB_Set256QamMode(void);

extern MS_BOOL MDrv_DMD_DTMB_SetDvbcMode(void);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DTMB_SEL_DMD
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DTMB_SEL_DMD(MS_U8 eDMD_NUM);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DTMB_GET_DMD_NUM
////////////////////////////////////////////////////////////////////////////////
extern MS_U8 MDrv_DMD_DTMB_GET_DMD_NUM(void);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DTMB_LoadFW
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DTMB_LoadFW(MS_U8 DMD_NUM);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DTMB_ADCOut_CTL
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DTMB_ADCOut_CTL(MS_U8 DMD_NUM);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DTMB_GetSNRPercentage
////////////////////////////////////////////////////////////////////////////////
extern MS_U8 MDrv_DMD_DTMB_GetSNRPercentage(void);

extern MS_U32 MDrv_DMD_DTMB_SetPowerState(EN_POWER_MODE u16PowerState);


////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DTMB_SWITCH_SSPI_GPIO
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DTMB_SWITCH_SSPI_GPIO(MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DTMB_GPIO_GET_LEVEL
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DTMB_GPIO_GET_LEVEL(MS_U8 u8Pin, MS_BOOL *bLevel);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DTMB_GPIO_SET_LEVEL
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DTMB_GPIO_SET_LEVEL(MS_U8 u8Pin, MS_BOOL bLevel);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DTMB_GPIO_OUT_ENABLE
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DTMB_GPIO_OUT_ENABLE(MS_U8 u8Pin, MS_BOOL bEnableOut);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DTMB_GetPreLdpcBer
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DTMB_GetPreLdpcBer(float *pber);



#ifdef __cplusplus
}
#endif


#endif // _DRV_DVBT_H_

