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
/// @file   drvDMD_ISDBT.h
/// @brief  ISDBT Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_ISDBT_H_
#define _DRV_ISDBT_H_

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
#define MSIF_DMD_ISDBT_INTERN_LIB_CODE           {'D','M','D','_','I','S', 'D','B','T','_','E','X','T','E','R','N','_'} //Lib code
#define MSIF_DMD_ISDBT_INTERN_LIBVER             {'0','0'}      //LIB version
#define MSIF_DMD_ISDBT_INTERN_BUILDNUM           {'0','0' }    //Build Number
#define MSIF_DMD_ISDBT_INTERN_CHANGELIST         {'0','0','0','0','0','0','0','0'} //P4 ChangeList Number

// ISDBT
typedef enum
{
      E_ISDBT_Layer_A = 0x00,
      E_ISDBT_Layer_B = 0x01,
      E_ISDBT_Layer_C = 0x02,
      E_ISDBT_Layer_INVALID,
}EN_ISDBT_Layer;

 /// ISDBT FFT enum
typedef enum
{      
      E_ISDBT_FFT_2K = 0x00,  /// 2K     
      E_ISDBT_FFT_4K = 0x01,  /// 4k      
      E_ISDBT_FFT_8K = 0x02,  /// 8k     
     E_ISDBT_FFT_INVALID,  /// invalid indicator
} EN_ISDBT_FFT_VAL;

/// ISDBT modulation mode
typedef enum
{
     E_ISDBT_DQPSK   = 0,  /// DQPSK  
     E_ISDBT_QPSK    = 1,   /// QPSK
     E_ISDBT_16QAM   = 2,    /// 16QAM
     E_ISDBT_64QAM   = 3,   /// 64QAM
     E_ISDBT_QAM_INVALID,    /// invalid indicator
} EN_ISDBT_CONSTEL_TYPE;

 /// ISDBT code rate
typedef enum
{
     E_ISDBT_CODERATE_1_2 = 0,  /// 1/2
     E_ISDBT_CODERATE_2_3 = 1,   /// 2/3
     E_ISDBT_CODERATE_3_4 = 2,   /// 3/4
     E_ISDBT_CODERATE_5_6 = 3,   /// 5/6
     E_ISDBT_CODERATE_7_8 = 4,   /// 7/8
     E_ISDBT_CODERATE_INVALID,  /// invalid indicator
} EN_ISDBT_CODE_RATE;

 /// ISDBT guard interval enum
typedef enum
{
     E_ISDBT_GUARD_INTERVAL_1_4  = 0,   /// 1/4
     E_ISDBT_GUARD_INTERVAL_1_8  = 1,  /// 1/8
     E_ISDBT_GUARD_INTERVAL_1_16 = 2,     /// 1/16
     E_ISDBT_GUARD_INTERVAL_1_32 = 3,  /// 1/32
     E_ISDBT_GUARD_INTERVAL_INVALID,    /// invalid indicator
} EN_ISDBT_GUARD_INTERVAL;

/// ISDBT Time Interleaving enum
typedef enum
{ 
     // 2K mode
     E_ISDBT_2K_TDI_0 = 0,   /// Tdi = 0
     E_ISDBT_2K_TDI_4 = 1,   /// Tdi = 4
     E_ISDBT_2K_TDI_8 = 2,    /// Tdi = 8
     E_ISDBT_2K_TDI_16 = 3,  /// Tdi = 16
     // 4K mode
     E_ISDBT_4K_TDI_0 = 4,  /// Tdi = 0
     E_ISDBT_4K_TDI_2 = 5,  /// Tdi = 2
     E_ISDBT_4K_TDI_4 = 6,  /// Tdi = 4
     E_ISDBT_4K_TDI_8 = 7,   /// Tdi = 8
     // 8K mode   
     E_ISDBT_8K_TDI_0 = 8,  /// Tdi = 0
     E_ISDBT_8K_TDI_1 = 9,  /// Tdi = 1
     E_ISDBT_8K_TDI_2 = 10, /// Tdi = 2
     E_ISDBT_8K_TDI_4 = 11,    /// Tdi = 4
     E_ISDBT_TDI_INVALID,    /// invalid indicator
} EN_ISDBT_TIME_INTERLEAVING;

typedef enum _e_ISDBT_HAL_COMMAND
{
    CMD_ISDBT_Exit = 0,
    CMD_ISDBT_InitClk,
    CMD_ISDBT_Download,
    CMD_ISDBT_SoftReset,
    CMD_ISDBT_SetModeClean,
    CMD_ISDBT_Active,
    CMD_ISDBT_Check_FEC_Lock,
    CMD_ISDBT_Check_FSA_TRACK_Lock,
    CMD_ISDBT_Check_PSYNC_Lock,
    CMD_ISDBT_Check_ICFO_CH_EXIST_Lock,
    CMD_ISDBT_Read_PKT_ERR,
    CMD_ISDBT_FWVERSION,
    CMD_ISDBT_GetSignalCodeRate,
    CMD_ISDBT_GetSignalGuardInterval,
    CMD_ISDBT_GetSignalTimeInterleaving,
    CMD_ISDBT_GetSignalFFTValue,
    CMD_ISDBT_GetSignalModulation,
    CMD_ISDBT_GetSignalStrength,
    CMD_ISDBT_GetSignalQuality,
    CMD_ISDBT_IIC_Bypass_Mode,
    CMD_ISDBT_SWITCH_SSPI_GPIO,
    CMD_ISDBT_GPIO_GET_LEVEL,
    CMD_ISDBT_GPIO_SET_LEVEL,
    CMD_ISDBT_GPIO_OUT_ENABLE,
    CMD_ISDBT_GetPostViterbiBer,
    CMD_ISDBT_GetPreViterbiBer,
    CMD_ISDBT_GetFreqOffset,
    CMD_ISDBT_GetSNR,
    CMD_ISDBT_TS_INTERFACE_CONFIG,
    CMD_ISDBT_GetSignalQualityOfLayerA,
    CMD_ISDBT_GetSignalQualityOfLayerB,
    CMD_ISDBT_GetSignalQualityOfLayerC,
    CMD_ISDBT_GetSignalQualityCombine
}e_ISDBT_HAL_COMMAND;

#define DMD_ISDBT_INTERN_VER                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_DMD_ISDBT_INTERN_LIB_CODE,      /* IP__                                             */  \
    MSIF_DMD_ISDBT_INTERN_LIBVER,        /* 0.0 ~ Z.Z                                        */  \
    MSIF_DMD_ISDBT_INTERN_BUILDNUM,      /* 00 ~ 99                                          */  \
    MSIF_DMD_ISDBT_INTERN_CHANGELIST,    /* CL#                                              */  \
    MSIF_OS

#define IS_BITS_SET(val, bits)                  (((val)&(bits)) == (bits))

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef enum
{
    DMD_ISDBT_DBGLV_NONE,    // disable all the debug message
    DMD_ISDBT_DBGLV_INFO,    // information
    DMD_ISDBT_DBGLV_NOTICE,  // normal but significant condition
    DMD_ISDBT_DBGLV_WARNING, // warning conditions
    DMD_ISDBT_DBGLV_ERR,     // error conditions
    DMD_ISDBT_DBGLV_CRIT,    // critical conditions
    DMD_ISDBT_DBGLV_ALERT,   // action must be taken immediately
    DMD_ISDBT_DBGLV_EMERG,   // system is unusable
    DMD_ISDBT_DBGLV_DEBUG,   // debug-level messages
} DMD_ISDBT_DbgLv;

typedef struct _ISDBT_MODULATION_MODE
{
    EN_ISDBT_CODE_RATE  eIsdbtCodeRate;
    EN_ISDBT_GUARD_INTERVAL eIsdbtGI;
    EN_ISDBT_TIME_INTERLEAVING eIsdbtTDI;
    EN_ISDBT_FFT_VAL eIsdbtFFT;
    EN_ISDBT_CONSTEL_TYPE eIsdbtConstellation;
} sISDBT_MODULATION_MODE;


typedef enum
{
    DMD_ISDBT_GETLOCK,
    DMD_ISDBT_GETLOCK_FSA_TRACK_LOCK,
    DMD_ISDBT_GETLOCK_PSYNC_LOCK,
    DMD_ISDBT_GETLOCK_ICFO_CH_EXIST_LOCK,
    DMD_ISDBT_GETLOCK_FEC_LOCK
} DMD_ISDBT_GETLOCK_TYPE;

typedef enum
{
    DMD_ISDBT_LOCK,
    DMD_ISDBT_CHECKING,
    DMD_ISDBT_CHECKEND,
    DMD_ISDBT_UNLOCK,
    DMD_ISDBT_NULL,
} DMD_ISDBT_LOCK_STATUS;

/// For demod init
typedef struct
{
    // init
    MS_U16 u16ISDBTIcfoChExistCheckTime;
    MS_U16 u16ISDBTFECLockCheckTime;
    
    // register init
    MS_U8 *u8DMD_ISDBT_DSPRegInitExt; // TODO use system variable type
    MS_U8 u8DMD_ISDBT_DSPRegInitSize;
    MS_U8 *u8DMD_ISDBT_InitExt; // TODO use system variable type
    
    MS_U16  u16IF_KHZ;
    MS_BOOL bIQSwap; 
    
    MS_U8   u1TsConfigByte_SerialMode : 1;
    MS_U8   u1TsConfigByte_DataSwap   : 1;
    MS_U8   u1TsConfigByte_ClockInv   : 1;
    MS_U8   u5TsConfigByte_DivNum     : 5;

    MS_U8 u8I2CSlaveAddr;
    MS_U8 u8I2CSlaveBus;
    MS_BOOL bIsExtDemod;

    MS_BOOL (*I2C_WriteBytes)(MS_U16 u16BusNumSlaveID, MS_U8 u8addrcount, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data);
    MS_BOOL (*I2C_ReadBytes)(MS_U16 u16BusNumSlaveID, MS_U8 u8AddrNum, MS_U8* paddr, MS_U16 u16size, MS_U8* pu8data);

    MS_U16  u16AgcReferenceValue;
    MS_U32  u32TdiStartAddr;
} DMD_ISDBT_InitData;

typedef enum
{
    E_DMD_ISDBT_FAIL=0,
    E_DMD_ISDBT_OK=1
} DMD_ISDBT_Result;

typedef struct
{
    MS_U8 u8Version;
    MS_U32 u32ISDBTScanTimeStart;
    MS_U32 u32ISDBTFECLockTime;
    DMD_ISDBT_LOCK_STATUS eStatus;
    MS_U32 u32ISDBTLockStatus;
} DMD_ISDBT_Info;

#define DMD_ISDBT_LOCK_FSA_TRACK_LOCK BIT_(0)
#define DMD_ISDBT_LOCK_PSYNC_LOCK BIT_(1)
#define DMD_ISDBT_LOCK_ICFO_CH_EXIST_LOCK BIT_(2)
#define DMD_ISDBT_LOCK_FEC_LOCK BIT_(3)


//typedef void(*P_DMD_ISR_Proc)(MS_U8 u8DMDID);
typedef struct _s_ISDBT_GET_PKT_ERR
{
    EN_ISDBT_Layer     eIsdbtLayer;
    MS_U16                  u16PacketErr;
}s_ISDBT_GET_PKT_ERR;


typedef struct _s_ISDBT_GET_MODULATION
{
    EN_ISDBT_Layer     eIsdbtLayer;
    EN_ISDBT_CONSTEL_TYPE                  eConstellation;
}s_ISDBT_GET_MODULATION;

typedef struct _s_ISDBT_GET_SIGNAL_STRENGTH
{
    EN_ISDBT_Layer     eIsdbtLayer;
    EN_ISDBT_CONSTEL_TYPE                  eConstellation;
}s_ISDBT_GET_SIGNAL_STRENGTH;

typedef struct _s_ISDBT_GPIO_INTERFACE
{
    MS_U8     u8Pin;
    MS_BOOL bLevel;
}s_ISDBT_GPIO_INTERFACE;

typedef struct _s_ISDBT_GET_BER_VALUE
{
    EN_ISDBT_Layer     eIsdbtLayer;
    float                       fBerValue;
}s_ISDBT_GET_BER_VALUE;

typedef struct _s_ISDBT_GET_CodeRate
{
    EN_ISDBT_Layer                            eIsdbtLayer;
    EN_ISDBT_CODE_RATE                  eCodeRate;
}s_ISDBT_GET_CodeRate;

typedef struct _s_ISDBT_GET_TimeInterleaving
{
    EN_ISDBT_Layer                            eIsdbtLayer;
    EN_ISDBT_TIME_INTERLEAVING      eTimeInterleaving;
}s_ISDBT_GET_TimeInterleaving;


typedef struct _s_ISDBT_HAL_FUNCTION_TABLE
{
    MS_BOOL (*HAL_DMD_ISDBT_IOCTL_CMD)(e_ISDBT_HAL_COMMAND eCmd, void *pHandle);
}s_ISDBT_HAL_FUNCTION_TABLE;

//s_ISDBT_HAL_FUNCTION_TABLE    sISDBT_HAL_FUNCTION_TABLE = {0};

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_Init
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_ISDBT_Init(DMD_ISDBT_InitData *pDMD_DVBT_InitData, MS_U32 u32InitDataLen);
////////////////////////////////////////////////////////////////////////////////
/// Should be called when exit VD input source
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_ISDBT_Exit(void);
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
extern MS_BOOL MDrv_DMD_ISDBT_SetDbgLevel(DMD_ISDBT_DbgLv u8DbgLevel);
//-------------------------------------------------------------------------------------------------
/// Get the information of DVBT driver\n
/// @return the pointer to the driver information
//-------------------------------------------------------------------------------------------------
extern DMD_ISDBT_Info* MDrv_DMD_ISDBT_GetInfo(void);
//-------------------------------------------------------------------------------------------------
/// Get DVBT driver version
/// when get ok, return the pointer to the driver version
//-------------------------------------------------------------------------------------------------
extern MS_BOOL MDrv_DMD_ISDBT_GetLibVer(const MSIF_Version **ppVersion);
////////////////////////////////////////////////////////////////////////////////
/// To get DVBT's register  value, only for special purpose.\n
/// u16Addr       : the address of DVBT's register\n
/// return the value of AFEC's register\n
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_ISDBT_GetReg(MS_U16 u16Addr, MS_U8 *pu8Data);
////////////////////////////////////////////////////////////////////////////////
/// To set DVBT's register value, only for special purpose.\n
/// u16Addr       : the address of DVBT's register\n
/// u8Value        : the value to be set\n
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_ISDBT_SetReg(MS_U16 u16Addr, MS_U8 u8Data);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_SetSerialControl
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_ISDBT_SetSerialControl(MS_U8 u8TsConfigData);

////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_ISDBT_SetReset
////////////////////////////////////////////////////////////////////////////////
extern void MDrv_DMD_ISDBT_SetReset(void);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_SetConfig
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_ISDBT_SetConfig(MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_SetActive
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_ISDBT_SetActive(MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_Get_Lock
////////////////////////////////////////////////////////////////////////////////
extern DMD_ISDBT_LOCK_STATUS MDrv_DMD_ISDBT_GetLock(DMD_ISDBT_GETLOCK_TYPE eType);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_ISDBT_GetModulationMode
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_ISDBT_GetModulationMode(EN_ISDBT_Layer LayerIndex, sISDBT_MODULATION_MODE *sIsdbtModulationMode);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetSignalStrength
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_ISDBT_GetSignalStrength(MS_U16 *u16Strength);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetSignalQuality
////////////////////////////////////////////////////////////////////////////////
extern MS_U16 MDrv_DMD_ISDBT_GetSignalQuality(void);
extern MS_U16 MDrv_DMD_ISDBT_GetSignalQualityOfLayerA(void);
extern MS_U16 MDrv_DMD_ISDBT_GetSignalQualityOfLayerB(void);
extern MS_U16 MDrv_DMD_ISDBT_GetSignalQualityOfLayerC(void);
extern MS_U16 MDrv_DMD_ISDBT_GetSignalQualityCombine(void);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetCellID
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_ISDBT_GetCellID(MS_U16 *u16CellID);

extern MS_BOOL MDrv_DMD_ISDBT_IIC_BYPASS_MODE(MS_BOOL    bEnable);

extern MS_BOOL MDrv_DMD_ISDBT_Read_PKT_ERR(EN_ISDBT_Layer LayerIndex, MS_U16 *u16PacketErr);


extern MS_BOOL MDrv_DMD_ISDBT_SWITCH_SSPI_GPIO(MS_BOOL   bEnable);

extern MS_BOOL MDrv_DMD_ISDBT_GPIO_GET_LEVEL(MS_U8 u8Pin, MS_BOOL *bLevel);

extern MS_BOOL MDrv_DMD_ISDBT_GPIO_SET_LEVEL(MS_U8 u8Pin, MS_BOOL bLevel);

extern MS_BOOL MDrv_DMD_ISDBT_GPIO_OUT_ENABLE(MS_U8 u8Pin, MS_BOOL bEnableOut);

extern MS_BOOL MDrv_DMD_ISDBT_GetPostViterbiBer(EN_ISDBT_Layer LayerIndex, float *ber);

extern MS_BOOL MDrv_DMD_ISDBT_GetPreViterbiBer(EN_ISDBT_Layer LayerIndex, float *ber);

extern MS_BOOL MDrv_DMD_ISDBT_GetFreqOffset(float *pFreqOff);
extern MS_BOOL MDrv_DMD_ISDBT_GetSNR(float *pf_snr);

extern MS_BOOL MDrv_DMD_ISDBT_GetFwVer(MS_U16 *pu16FwVer);
extern MS_BOOL MDrv_DMD_ISDBT_Initial_Hal_Interface(void);    //this function will be implemented in ISDBT Hal layer

extern MS_BOOL MDrv_INTERNAL_DMD_ISDBT_Link_Func(void);    //this function will be implemented in ISDBT Hal layer
extern MS_BOOL MDrv_EXTERNAL_DMD_ISDBT_Link_Func(void);    //this function will be implemented in ISDBT Hal layer

#ifdef __cplusplus
}
#endif


#endif // _DRV_DVBT_H_

