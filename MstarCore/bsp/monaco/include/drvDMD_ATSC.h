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
/// @file   drvDMD_ATSC.h
/// @brief  ATSC Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_ATSC_H_
#define _DRV_ATSC_H_

//-------------------------------------------------------------------------------------------------
//  Driver Compiler Options
//-------------------------------------------------------------------------------------------------

#define DMD_ATSC_UTOPIA_EN                  1
#define DMD_ATSC_UTOPIA2_EN                 0

#define DMD_ATSC_STR_EN                     0
#define DMD_ATSC_MULTI_THREAD_SAFE          0
#define DMD_ATSC_MULTI_DMD_EN               1

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------

#include "MsTypes.h"
#if DMD_ATSC_UTOPIA_EN || DMD_ATSC_UTOPIA2_EN
#include "MsVersion.h"
#include "MsCommon.h"
#endif
#if DMD_ATSC_UTOPIA2_EN || DMD_ATSC_STR_EN
#include "utopia.h"
#endif

//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

#ifndef DLL_PUBLIC 
#define DLL_PUBLIC 
#endif

#if DMD_ATSC_MULTI_DMD_EN
#define DMD_ATSC_MAX_DEMOD_NUM          2
#else
#define DMD_ATSC_MAX_DEMOD_NUM          1
#endif

#if DMD_ATSC_UTOPIA_EN || DMD_ATSC_UTOPIA2_EN
#define MSIF_DMD_ATSC_LIB_CODE          {'D','M','D','_','A','T', 'S','C','_'} //Lib code
#define MSIF_DMD_ATSC_LIBVER            {'0','0'}                              //LIB version
#define MSIF_DMD_ATSC_BUILDNUM          {'0','0' }                             //Build Number
#define MSIF_DMD_ATSC_CHANGELIST        {'0','0','0','0','0','0','0','0'}      //P4 ChangeList Number

#define DMD_ATSC_VER                    /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_DMD_ATSC_LIB_CODE,             /* IP__                                             */  \
    MSIF_DMD_ATSC_LIBVER,               /* 0.0 ~ Z.Z                                        */  \
    MSIF_DMD_ATSC_BUILDNUM,             /* 00 ~ 99                                          */  \
    MSIF_DMD_ATSC_CHANGELIST,           /* CL#                                              */  \
    MSIF_OS
#endif // #if DMD_ATSC_UTOPIA_EN || DMD_ATSC_UTOPIA2_EN

#ifndef BIT_
#define BIT_(n)                                 (1 << (n))
#endif

#define DMD_ATSC_LOCK_VSB_PRE_LOCK              BIT_(0)
#define DMD_ATSC_LOCK_VSB_FSYNC_LOCK            BIT_(1)
#define DMD_ATSC_LOCK_VSB_CE_LOCK               BIT_(2)
#define DMD_ATSC_LOCK_VSB_FEC_LOCK              BIT_(3)

#define DMD_ATSC_LOCK_QAM_AGC_LOCK              BIT_(8)
#define DMD_ATSC_LOCK_QAM_PRE_LOCK              BIT_(9)
#define DMD_ATSC_LOCK_QAM_MAIN_LOCK             BIT_(10)

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

typedef enum
{
    DMD_ATSC_HAL_CMD_Exit = 0,
    DMD_ATSC_HAL_CMD_InitClk,
    DMD_ATSC_HAL_CMD_Download,
    DMD_ATSC_HAL_CMD_FWVERSION,
    DMD_ATSC_HAL_CMD_SoftReset,
    DMD_ATSC_HAL_CMD_SetVsbMode,
    DMD_ATSC_HAL_CMD_Set64QamMode,
    DMD_ATSC_HAL_CMD_Set256QamMode,
    DMD_ATSC_HAL_CMD_SetModeClean,
    DMD_ATSC_HAL_CMD_Set_QAM_SR,
    DMD_ATSC_HAL_CMD_Active,
    DMD_ATSC_HAL_CMD_Check8VSB64_256QAM,
    DMD_ATSC_HAL_CMD_AGCLock,
    DMD_ATSC_HAL_CMD_Vsb_PreLock,
    DMD_ATSC_HAL_CMD_Vsb_FSync_Lock,
    DMD_ATSC_HAL_CMD_Vsb_CE_Lock,
    DMD_ATSC_HAL_CMD_Vsb_FEC_Lock,
    DMD_ATSC_HAL_CMD_QAM_PreLock,
    DMD_ATSC_HAL_CMD_QAM_Main_Lock,
    DMD_ATSC_HAL_CMD_ReadIFAGC,
    DMD_ATSC_HAL_CMD_CheckSignalCondition,
    DMD_ATSC_HAL_CMD_ReadSNRPercentage,
    DMD_ATSC_HAL_CMD_ReadPKTERR,
    DMD_ATSC_HAL_CMD_GetPreViterbiBer,
    DMD_ATSC_HAL_CMD_GetPostViterbiBer,
    DMD_ATSC_HAL_CMD_ReadFrequencyOffset,
    DMD_ATSC_HAL_CMD_TS_INTERFACE_CONFIG,
    DMD_ATSC_HAL_CMD_IIC_Bypass_Mode,
    DMD_ATSC_HAL_CMD_SSPI_TO_GPIO,
    DMD_ATSC_HAL_CMD_GPIO_GET_LEVEL,
    DMD_ATSC_HAL_CMD_GPIO_SET_LEVEL,
    DMD_ATSC_HAL_CMD_GPIO_OUT_ENABLE,
    DMD_ATSC_HAL_CMD_GET_REG,
    DMD_ATSC_HAL_CMD_SET_REG,
    CMD_ATSC_HAL_CMD_GET_QAM_SNR
} DMD_ATSC_HAL_COMMAND;

typedef struct
{
    MS_U8 u8Pin;
    union
    {
        MS_BOOL bLevel;
        MS_BOOL bIsOut;
    };
} DMD_ATSC_GPIO_PIN_DATA;

typedef struct
{
    MS_U16 u16Addr;
    MS_U8  u8Data;
} DMD_ATSC_REG_DATA;

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
    DMD_ATSC_DBGLV_DEBUG    // debug-level messages
} DMD_ATSC_DbgLv;

typedef enum
{
    DMD_ATSC_DEMOD_ATSC_VSB,
    DMD_ATSC_DEMOD_ATSC_64QAM,
    DMD_ATSC_DEMOD_ATSC_256QAM,
    DMD_ATSC_DEMOD_ATSC_16QAM,
    DMD_ATSC_DEMOD_ATSC_32QAM,
    DMD_ATSC_DEMOD_ATSC_128QAM,
    DMD_ATSC_DEMOD_MAX,
    DMD_ATSC_DEMOD_NULL = DMD_ATSC_DEMOD_MAX
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
    DMD_ATSC_GETLOCK_QAM_MAINLOCK
} DMD_ATSC_GETLOCK_TYPE;

typedef enum
{
    DMD_ATSC_LOCK,
    DMD_ATSC_CHECKING,
    DMD_ATSC_CHECKEND,
    DMD_ATSC_UNLOCK,
    DMD_ATSC_NULL
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

typedef enum _eDMD_SEL
{
    DMD0 = 0,
    DMD1,
    HK,
}eDMD_SEL;

/// For demod init
typedef struct
{
    // Timeout time
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
    MS_BOOL bIsQPad;//0
   
    //By IC:
    MS_U8   u8IS_DUAL;//0
    MS_BOOL bIsExtDemod;//0
    
    //By TS (Only for MCP or ext demod):
    MS_U8 u1TsConfigByte_SerialMode : 1;
    MS_U8 u1TsConfigByte_DataSwap   : 1;
    MS_U8 u1TsConfigByte_ClockInv   : 1;
    MS_U8 u5TsConfigByte_DivNum     : 5;

    //By SYS I2C (Only for MCP or ext demod):
    MS_U8 u8I2CSlaveAddr;
    MS_U8 u8I2CSlaveBus;
    MS_BOOL (*I2C_WriteBytes)(MS_U16 u16BusNumSlaveID, MS_U8 u8addrcount, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data);
    MS_BOOL (*I2C_ReadBytes)(MS_U16 u16BusNumSlaveID, MS_U8 u8AddrNum, MS_U8* paddr, MS_U16 u16size, MS_U8* pu8data);
    
    //By SYS MSPI (Only for MCP or ext demod):
    MS_BOOL bIsUseSspiLoadCode;
    MS_BOOL bIsSspiUseTsPin;
    
    #if !DMD_ATSC_UTOPIA_EN && !DMD_ATSC_UTOPIA2_EN
    MS_U32  (*GetSystemTimeMS)(void);      // Get sys time (unit: ms)
    void    (*DelayMS)(MS_U32 ms);         // Delay time (unit: ms)
    MS_BOOL (*CreateMutex)(MS_BOOL enable); // Create&Delete mutex
    void    (*LockDMD)(MS_BOOL enable);    // Enter&Leave mutex
    #endif
} DMD_ATSC_InitData;

typedef struct
{
    MS_BOOL bInit;
    MS_BOOL bDownloaded;
    
    #if DMD_ATSC_STR_EN
    MS_BOOL             bIsDTV;
    EN_POWER_MODE       eLastState;
    #endif
    DMD_ATSC_DEMOD_TYPE eLastType;
    MS_U16              u16SymRate;
    
    MS_BOOL (*HAL_DMD_ATSC_IOCTL_CMD)(DMD_ATSC_HAL_COMMAND eCmd, void *pPara);
} DMD_ATSC_PriData;

typedef struct
{
    MS_U8  u8Version;
    MS_U32 u32ATSCScanTimeStart;
    MS_U32 u32ATSCFECLockTime;
    MS_U32 u32ATSCLockStatus; 
} DMD_ATSC_Info;

typedef struct
{
    DMD_ATSC_InitData  sDMD_ATSC_InitData;
    DMD_ATSC_PriData   sDMD_ATSC_PriData;
    DMD_ATSC_Info      sDMD_ATSC_Info;
} DMD_ATSC_ResData;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
/// Set detailed level of ATSC driver debug message
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
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_SetDbgLevel(DMD_ATSC_DbgLv u8DbgLevel);
//-------------------------------------------------------------------------------------------------
/// Get the information of ATSC driver\n
/// @return the pointer to the driver information
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC extern DMD_ATSC_Info* MDrv_DMD_ATSC_GetInfo(void);
//-------------------------------------------------------------------------------------------------
/// Get ATSC driver version
/// when get ok, return the pointer to the driver version
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_GetLibVer(const MSIF_Version **ppVersion);

////////////////////////////////////////////////////////////////////////////////
/// Should be called once when power on init
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_Initial_Hal_Interface(void);

////////////////////////////////////////////////////////////////////////////////
///                            SINGLE DEMOD API                              ///
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// Should be called every time when enter DTV input source
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_Init(DMD_ATSC_InitData *pDMD_ATSC_InitData, MS_U32 u32InitDataLen);
////////////////////////////////////////////////////////////////////////////////
/// Should be called every time when exit DTV input source
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_Exit(void);
////////////////////////////////////////////////////////////////////////////////
/// Set demod mode and enable demod
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_SetConfig(DMD_ATSC_DEMOD_TYPE eType, MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// Reset FW state machine (no use)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_SetReset(void);
////////////////////////////////////////////////////////////////////////////////
/// SEL DEMOD (no use)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_SEL_DMD(eDMD_SEL eDMD_NUM);
////////////////////////////////////////////////////////////////////////////////
/// Load FW (no use)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_LoadFW(eDMD_SEL DMD_NUM);
////////////////////////////////////////////////////////////////////////////////
/// Set VSB mode
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_SetVsbMode(void);
////////////////////////////////////////////////////////////////////////////////
/// Set 256QAM mode
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_Set256QamMode(void);
////////////////////////////////////////////////////////////////////////////////
/// Set 64QAM mode
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_Set64QamMode(void);
////////////////////////////////////////////////////////////////////////////////
/// Set demod mode and enable demod (only for J83B)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_Set_QAM_SR(DMD_ATSC_DEMOD_TYPE eType, MS_U16 symbol_rate);
////////////////////////////////////////////////////////////////////////////////
/// Active demod (not use)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_SetActive(MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// Set demod power state for STR
////////////////////////////////////////////////////////////////////////////////
#if DMD_ATSC_STR_EN
DLL_PUBLIC extern MS_U32 MDrv_DMD_ATSC_SetPowerState(EN_POWER_MODE u16PowerState);
#endif
////////////////////////////////////////////////////////////////////////////////
/// Get demod lock status
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern DMD_ATSC_LOCK_STATUS MDrv_DMD_ATSC_GetLock(DMD_ATSC_GETLOCK_TYPE eType);
////////////////////////////////////////////////////////////////////////////////
/// Get demod modulation mode
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern DMD_ATSC_DEMOD_TYPE MDrv_DMD_ATSC_GetModulationMode(void);
////////////////////////////////////////////////////////////////////////////////
/// Get demod signal strength (IF AGC gain)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_GetSignalStrength(MS_U16 *u16Strength);
////////////////////////////////////////////////////////////////////////////////
/// Get demod signal quality (NO SIGNAL, WEAK, MODERATE, STRONG and VERY_STRONG)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern DMD_ATSC_SIGNAL_CONDITION MDrv_DMD_ATSC_GetSignalQuality(void);
////////////////////////////////////////////////////////////////////////////////
/// Get demod SNR percentage (MAX SNR 40dB)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_U8 MDrv_DMD_ATSC_GetSNRPercentage(void);
////////////////////////////////////////////////////////////////////////////////
/// Get demod SNR (only for J.83ABC)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_GET_QAM_SNR(float *f_snr);
////////////////////////////////////////////////////////////////////////////////
/// Get demod packet error number
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_Read_uCPKT_ERR(MS_U16 *u16PacketErr);
////////////////////////////////////////////////////////////////////////////////
/// Get demod pre Viterbi BER
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_GetPreViterbiBer(float *ber);
////////////////////////////////////////////////////////////////////////////////
/// Get demod post Viterbi BER
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_GetPostViterbiBer(float *ber);
////////////////////////////////////////////////////////////////////////////////
/// Get demod frequency offset
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_ReadFrequencyOffset(MS_S16 *cfo);
////////////////////////////////////////////////////////////////////////////////
/// Set TS output mode (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_SetSerialControl(MS_U8 u8TsConfigData);
////////////////////////////////////////////////////////////////////////////////
/// Enable I2C bypass mode (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_IIC_BYPASS_MODE(MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// Switch pin to SSPI or GPIO (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_SWITCH_SSPI_GPIO(MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// Get GPIO pin high or low (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_GPIO_GET_LEVEL(MS_U8 u8Pin, MS_BOOL *bLevel);
////////////////////////////////////////////////////////////////////////////////
/// Set GPIO pin high or low (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_GPIO_SET_LEVEL(MS_U8 u8Pin, MS_BOOL bLevel);
////////////////////////////////////////////////////////////////////////////////
/// Set GPIO pin output or input (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_GPIO_OUT_ENABLE(MS_U8 u8Pin, MS_BOOL bEnableOut);

////////////////////////////////////////////////////////////////////////////////
/// To get ATSC's register  value, only for special purpose.\n
/// u16Addr       : the address of ATSC's register\n
/// pu8Data       : the value to be gotten\n
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_GetReg(MS_U16 u16Addr, MS_U8 *pu8Data);
////////////////////////////////////////////////////////////////////////////////
/// To set ATSC's register value, only for special purpose.\n
/// u16Addr       : the address of ATSC's register\n
/// u8Value       : the value to be set\n
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_SetReg(MS_U16 u16Addr, MS_U8 u8Data);

////////////////////////////////////////////////////////////////////////////////
///                            MULTI DEMOD API                               ///
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// Should be called every time when enter DTV input source
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_MD_Init(MS_U8 id, DMD_ATSC_InitData *pDMD_ATSC_InitData, MS_U32 u32InitDataLen);
////////////////////////////////////////////////////////////////////////////////
/// Should be called every time when exit DTV input source
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_MD_Exit(MS_U8 id);
////////////////////////////////////////////////////////////////////////////////
/// Set demod mode and enable demod
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_MD_SetConfig(MS_U8 id, DMD_ATSC_DEMOD_TYPE eType, MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// Reset FW state machine (no use)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_MD_SetReset(void);
////////////////////////////////////////////////////////////////////////////////
/// Set demod mode and enable demod (only for J83B)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_MD_Set_QAM_SR(MS_U8 id, DMD_ATSC_DEMOD_TYPE eType, MS_U16 symbol_rate);
////////////////////////////////////////////////////////////////////////////////
/// Active demod (not use)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_MD_SetActive(MS_U8 id, MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// Set demod power state for STR
////////////////////////////////////////////////////////////////////////////////
#if DMD_ATSC_STR_EN
DLL_PUBLIC extern MS_U32 MDrv_DMD_ATSC_MD_SetPowerState(MS_U8 id, EN_POWER_MODE u16PowerState);
#endif
////////////////////////////////////////////////////////////////////////////////
/// Get demod lock status
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern DMD_ATSC_LOCK_STATUS MDrv_DMD_ATSC_MD_GetLock(MS_U8 id, DMD_ATSC_GETLOCK_TYPE eType);
////////////////////////////////////////////////////////////////////////////////
/// Get demod modulation mode
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern DMD_ATSC_DEMOD_TYPE MDrv_DMD_ATSC_MD_GetModulationMode(MS_U8 id);
////////////////////////////////////////////////////////////////////////////////
/// Get demod signal strength (IF AGC gain)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_MD_GetSignalStrength(MS_U8 id, MS_U16 *u16Strength);
////////////////////////////////////////////////////////////////////////////////
/// Get demod signal quality (NO SIGNAL, WEAK, MODERATE, STRONG and VERY_STRONG)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern DMD_ATSC_SIGNAL_CONDITION MDrv_DMD_ATSC_MD_GetSignalQuality(MS_U8 id);
////////////////////////////////////////////////////////////////////////////////
/// Get demod SNR percentage (MAX SNR 40dB)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_U8 MDrv_DMD_ATSC_MD_GetSNRPercentage(MS_U8 id);
////////////////////////////////////////////////////////////////////////////////
/// Get demod SNR (only for J.83ABC)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_MD_GET_QAM_SNR(MS_U8 id, float *f_snr);
////////////////////////////////////////////////////////////////////////////////
/// Get demod packet error number
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_MD_Read_uCPKT_ERR(MS_U8 id, MS_U16 *u16PacketErr);
////////////////////////////////////////////////////////////////////////////////
/// Get demod pre Viterbi BER
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_MD_GetPreViterbiBer(MS_U8 id, float *ber);
////////////////////////////////////////////////////////////////////////////////
/// Get demod post Viterbi BER
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_MD_GetPostViterbiBer(MS_U8 id, float *ber);
////////////////////////////////////////////////////////////////////////////////
/// Get demod frequency offset
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_MD_ReadFrequencyOffset(MS_U8 id, MS_S16 *cfo);
////////////////////////////////////////////////////////////////////////////////
/// Set TS output mode (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_MD_SetSerialControl(MS_U8 id, MS_U8 u8TsConfigData);
////////////////////////////////////////////////////////////////////////////////
/// Enable I2C bypass mode (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_MD_IIC_BYPASS_MODE(MS_U8 id, MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// Switch pin to SSPI or GPIO (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_MD_SWITCH_SSPI_GPIO(MS_U8 id, MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// Get GPIO pin high or low (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_MD_GPIO_GET_LEVEL(MS_U8 id, MS_U8 u8Pin, MS_BOOL *bLevel);
////////////////////////////////////////////////////////////////////////////////
/// Set GPIO pin high or low (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_MD_GPIO_SET_LEVEL(MS_U8 id, MS_U8 u8Pin, MS_BOOL bLevel);
////////////////////////////////////////////////////////////////////////////////
/// Set GPIO pin output or input (only for external demod)
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_MD_GPIO_OUT_ENABLE(MS_U8 id, MS_U8 u8Pin, MS_BOOL bEnableOut);

////////////////////////////////////////////////////////////////////////////////
/// To get ATSC's register  value, only for special purpose.\n
/// u16Addr       : the address of ATSC's register\n
/// pu8Data       : the value to be gotten\n
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_MD_GetReg(MS_U8 id, MS_U16 u16Addr, MS_U8 *pu8Data);
////////////////////////////////////////////////////////////////////////////////
/// To set ATSC's register value, only for special purpose.\n
/// u16Addr       : the address of ATSC's register\n
/// u8Value       : the value to be set\n
////////////////////////////////////////////////////////////////////////////////
DLL_PUBLIC extern MS_BOOL MDrv_DMD_ATSC_MD_SetReg(MS_U8 id, MS_U16 u16Addr, MS_U8 u8Data);

#ifdef __cplusplus
}
#endif

#endif // _DRV_ATSC_H_

