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
/// @file   drvDMD_EXTERN_MSB124x.h
/// @brief  MSB124x Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_DVBT_H_
#define _DRV_DVBT_H_

#include "MsCommon.h"
//#include "drvDMD_common.h"
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
#define MSIF_DMD_MSB124X_INTERN_LIB_CODE           {'1','2', '4','x'} //Lib code
#define MSIF_DMD_MSB124X_INTERN_LIBVER             {'0','1'}      //LIB version
#define MSIF_DMD_MSB124X_INTERN_BUILDNUM           {'0','0' }    //Build Number
#define MSIF_DMD_MSB124X_INTERN_CHANGELIST         {'0','0','0','0','0','0','0','0'} //P4 ChangeList Number

#define DMD_MSB124X_EXTERN_VER                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_DMD_MSB124X_INTERN_LIB_CODE,      /* IP__                                             */  \
    MSIF_DMD_MSB124X_INTERN_LIBVER,        /* 0.0 ~ Z.Z                                        */  \
    MSIF_DMD_MSB124X_INTERN_BUILDNUM,      /* 00 ~ 99                                          */  \
    MSIF_DMD_MSB124X_INTERN_CHANGELIST,    /* CL#                                              */  \
    MSIF_OS

#define IS_BITS_SET(val, bits)                  (((val)&(bits)) == (bits))

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef enum
{
    E_DMD_MSB124X_DBGLV_NONE,    // disable all the debug message
    E_DMD_MSB124X_DBGLV_INFO,    // information
    E_DMD_MSB124X_DBGLV_NOTICE,  // normal but significant condition
    E_DMD_MSB124X_DBGLV_WARNING, // warning conditions
    E_DMD_MSB124X_DBGLV_ERR,     // error conditions
    E_DMD_MSB124X_DBGLV_CRIT,    // critical conditions
    E_DMD_MSB124X_DBGLV_ALERT,   // action must be taken immediately
    E_DMD_MSB124X_DBGLV_EMERG,   // system is unusable
    E_DMD_MSB124X_DBGLV_DEBUG,   // debug-level messages
} eDMD_MSB124X_DbgLv;

typedef enum
{
    // fw version, check sum,Address Start at 0x00
    C_CHECK_SUM_L = 0x00,
    C_CHECK_SUM_H,
    C_FW_VER_0,
    C_FW_VER_1,
    C_FW_VER_2,
	
    // Operation Mode Settings,Address Start at 0x20
    C_opmode_auto_scan_sym_rate= 0x20,
    C_opmode_auto_scan_qam,
    C_if_inv_pwm_out_en,

    // Config Params
    C_config_zif= 0x23,
    C_config_fc_l,
    C_config_fc_h,
    C_config_fs_l,
    C_config_fs_h,
    C_config_bw_l,    // 0x28
    C_config_bw_h,
    C_config_bw1_l,
    C_config_bw1_h,
    C_config_bw2_l,
    C_config_bw2_h,
    C_config_bw3_l,
    C_config_bw3_h,
    C_config_qam,     // 0x30
    C_config_cci,
    C_config_ts_serial,
    C_config_ts_clk_rate,
    C_config_ts_out_inv,
    C_config_ts_data_swap,
    C_config_iq_swap,   

     //not always changed
     C_opmode_rfagc_en,					
     C_opmode_humdet_en,   // 0x38					 
     C_opmode_dcr_en,					   
     C_opmode_iqb_en,					   
     C_opmode_auto_iq,					   
     C_opmode_auto_rfmax,

     C_opmode_atv_detector_en,		 

     C_config_rssi,			 		     
     C_config_rfmax,		

    DVBC_PARAM_LEN,
} DVBC_Param;

typedef enum
{
#if 1
    // operation mode settings
    T_OPMODE_RFAGC_EN  = 0x20,   // 0x20
    T_OPMODE_HUMDET_EN,
    T_OPMODE_DCR_EN,
    T_OPMODE_IIS_EN,
    T_OPMODE_CCI_EN,
    T_OPMODE_ACI_EN,
    T_OPMODE_IQB_EN,
    T_OPMODE_AUTO_IQ,
    T_OPMODE_AUTO_RFMAX,    // 0x28
    T_OPMODE_AUTO_ACI,
    T_OPMODE_FIX_MODE_CP,
    T_OPMODE_FIX_TPS,
    T_OPMODE_AUTO_SCAN,
    T_OPMODE_RSV_0X2D,
    T_OPMODE_RSV_0X2E,
    T_OPMODE_RSV_0X2F,

    // channel config param
    T_CONFIG_RSSI,    // 0x30
    T_CONFIG_ZIF,
    T_CONFIG_FREQ,
    T_CONFIG_FC_L,
    T_CONFIG_FC_H,
    T_CONFIG_FS_L,
    T_CONFIG_FS_H,
    T_CONFIG_BW,
    T_CONFIG_MODE,    // 0x38
    T_CONFIG_CP,
    T_CONFIG_LP_SEL,
    T_CONFIG_CSTL,
    T_CONFIG_HIER,
    T_CONFIG_HPCR,
    T_CONFIG_LPCR,
    T_CONFIG_IQ_SWAP,
    T_CONFIG_RFMAX,    // 0x40
    T_CONFIG_CCI,
    T_CONFIG_ICFO_RANGE,
    T_CONFIG_RFAGC_REF,
    T_CONFIG_IFAGC_REF_2K,
    T_CONFIG_IFAGC_REF_8K,
    T_CONFIG_IFAGC_REF_ACI,
    T_CONFIG_IFAGC_REF_IIS_2K,
    T_CONFIG_IFAGC_REF_IIS_8K,    // 0x48
    T_CONFIG_ACI_DET_TH_L,
    T_CONFIG_ACI_DET_TH_H,
    T_CONFIG_TS_SERIAL,
    T_CONFIG_TS_CLK_RATE,
    T_CONFIG_TS_OUT_INV,
    T_CONFIG_TS_DATA_SWAP,
    T_CONFIG_2K_SFO_H,
    T_CONFIG_2K_SFO_L,    // 0x50
    T_CONFIG_8K_SFO_H,
    T_CONFIG_8K_SFO_L,
    T_CONFIG_CHECK_CHANNEL,
    T_CONFIG_SLICER_SNR_POS,
    T_CONFIG_TDP_CCI_KP,
    T_CONFIG_CCI_FSWEEP,
    T_CONFIG_TS_CLK_RATE_AUTO,
    T_CONFIG_IF_INV_PWM_OUT_EN,

    /**********************
     * crc =
     *    ~(T_OPMODE_RFAGC_EN^T_OPMODE_HUMDET_EN^....^T_CONFIG_TS_CLK_RATE_AUTO)
     ************************/
    T_PARAM_CHECK_SUM,

    T_DVBT_LOCK_HIS   = 0xF0,
    T_DVBT2_NOCHAN_Flag = 0xF1,
    T_DVBT_NOCHAN_Flag = 0xF2,
	
    DVBT_PARAM_LEN,
#else
T_OPMODE_RFAGC_EN  = 0x20,
T_OPMODE_AUTO_IQ,
T_CONFIG_ZIF,
T_CONFIG_FC_L,
T_CONFIG_FC_H,
T_CONFIG_FS_L,
T_CONFIG_FS_H,
T_CONFIG_BW,
T_CONFIG_IQ_SWAP,
T_CONFIG_TS_SERIAL,
T_CONFIG_TS_CLK_RATE,
T_CONFIG_TS_OUT_INV,
T_CONFIG_TS_DATA_SWAP,
T_CONFIG_TS_CLK_RATE_AUTO,
T_PARAM_CHECK_SUM,
 DVBT_PARAM_LEN,

#endif
} DVBT_Param;

typedef enum
{
    // fw version, check sum
    E_T2_CHECK_SUM_L      = 0x00,
    E_T2_CHECK_SUM_H,
    E_T2_FW_VER_0,
    E_T2_FW_VER_1,
    E_T2_FW_VER_2,

    // operation mode
    E_T2_ZIF_EN           = 0x20,
    E_T2_RF_AGC_EN,
    E_T2_HUM_DET_EN,
    E_T2_DCR_EN,
    E_T2_IQB_EN,
    E_T2_IIS_EN,
    E_T2_CCI_EN,
    E_T2_LOW_PWR_DET_EN,
    E_T2_ACI_DET_EN,
    E_T2_TD_MOTION_EN,
    E_T2_FD_MOTION_EN,

    // channel tuning param
    E_T2_BW               = 0x40,
    E_T2_FC_L             = 0x41,
    E_T2_FC_H             = 0x42,
    E_T2_FS_L,
    E_T2_FS_H,
    E_T2_ZIF,
    E_T2_GI,
    E_T2_ACI_DET_TYPE,
    E_T2_AGC_REF,         //0x48
    E_T2_RSSI_REF,
    E_T2_SNR_TIME_L,
    E_T2_SNR_TIME_H,
    E_T2_BER_CMP_TIME_L,
    E_T2_BER_CMP_TIME_H,
    E_T2_SFO_CFO_NUM,
    E_T2_CCI,
    E_T2_ACI_DET_TH_L,    //0x50
    E_T2_ACI_DET_TH_H,
    E_T2_TS_SERIAL     = 0x52,
    E_T2_TS_CLK_RATE   = 0x53,
    E_T2_TS_OUT_INV    = 0x54,
    E_T2_TS_DATA_SWAP  = 0x55,
    E_T2_TDP_CCI_KP,
    E_T2_CCI_FSWEEP,      //0x57
    E_T2_TS_ERR_POL,      //0x58
    E_T2_IF_AGC_INV_PWM_EN,  //0x59
    E_T2_CCI_TYPE,	     //0x5A
    E_T2_LITE,                 //0x5B

    // dvbt2 lock history
    E_T2_DVBT2_LOCK_HIS   = 0xF0,
    E_T2_FEF_DET_IND,
    E_T2_MPLP_NO_COMMON_IND,

    // splp, mplp releted
    E_T2_PLP_ID_ARR       = 0x100,
    E_T2_L1_FLAG          = 0x120,
    E_T2_PLP_ID,
    E_T2_GROUP_ID,
    E_T2_PARAM_NUM,
} E_DVBT2_PARAM;

typedef enum
{
    E_DMD_MSB124X_DEMOD_I2C_DYNAMIC_SLAVE_ID_1,
    E_DMD_MSB124X_DEMOD_I2C_DYNAMIC_SLAVE_ID_2,
    E_DMD_MSB124X_DEMOD_I2C_DYNAMIC_SLAVE_ID_3,
    E_DMD_MSB124X_DEMOD_I2C_DYNAMIC_SLAVE_ID_4    
} eDMD_MSB124X_DemodI2CSlaveID;

typedef enum
{
    E_DMD_MSB124X_DEMOD_I2C_READ_BYTES,
    E_DMD_MSB124X_DEMOD_I2C_WRITE_BYTES       
} eDMD_MSB124X_DemodI2CMethod;

/// For demod init
typedef struct
{
    MS_U8 u8WO_SPI_Flash;
    MS_BOOL bPreloadDSPCodeFromMainCHIPI2C;
    MS_BOOL bFlashWPEnable;
    void (*fpGPIOReset)(MS_BOOL bOnOff);
    MS_BOOL (*fpMSB124X_I2C_Access)(eDMD_MSB124X_DemodI2CSlaveID eSlaveID, eDMD_MSB124X_DemodI2CMethod eMethod, MS_U8 u8AddrSize, MS_U8 *pu8Addr, MS_U16 u16Size, MS_U8 *pu8Data);
    MS_U8* pDVBC_DSP_REG;
    MS_U8* pDVBT_DSP_REG;
    MS_U8* pDVBT2_DSP_REG;
    MS_BOOL bEnableSPILoadCode;
    void (*fpMSB124x_SPIPAD_En)(MS_BOOL bOnOff);
    MS_U8 u8WO_Sdram;// 1 means no sdram on board
} sDMD_MSB124X_InitData;

typedef enum
{
    E_DMD_MSB124X_DEMOD_NONE,
    E_DMD_MSB124X_DEMOD_DVBT2,
    E_DMD_MSB124X_DEMOD_DVBT,
    E_DMD_MSB124X_DEMOD_DVBC,
    E_DMD_MSB124X_DEMOD_DVBS2,
} eDMD_MSB124X_DemodulatorType;

typedef enum
{
    E_DMD_MSB124X_FAIL=0,
    E_DMD_MSB124X_OK=1
} DMD_MSB124X_Result;


typedef struct
{
    MS_U16 u16Version;
} DMD_MSB124X_Info;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_Init
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_MSB124X_Init(sDMD_MSB124X_InitData *pDMD_MSB124X_InitData, MS_U32 u32InitDataLen);
////////////////////////////////////////////////////////////////////////////////
/// Should be called when exit VD input source
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_MSB124X_Exit(void);
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
extern MS_BOOL MDrv_DMD_MSB124X_SetDbgLevel(eDMD_MSB124X_DbgLv u8DbgLevel);
//-------------------------------------------------------------------------------------------------
/// Get the information of DVBT driver\n
/// @return the pointer to the driver information
//-------------------------------------------------------------------------------------------------
//extern DMD_DVBT_Info* MDrv_DMD_DVBT_GetInfo(DMD_DVBT_INFO_TYPE eInfoType);
//-------------------------------------------------------------------------------------------------
/// Get DVBT driver version
/// when get ok, return the pointer to the driver version
//-------------------------------------------------------------------------------------------------
extern MS_BOOL MDrv_DMD_MSB124X_GetLibVer(const MSIF_Version **ppVersion);
////////////////////////////////////////////////////////////////////////////////
/// Get DVBT FW version
/// u16Addr       : the address of DVBT's register\n
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_MSB124X_GetFWVer(MS_U16 *ver);
////////////////////////////////////////////////////////////////////////////////
/// To get DVBT's register  value, only for special purpose.\n
/// u16Addr       : the address of DVBT's register\n
/// return the value of AFEC's register\n
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_MSB124X_GetReg(MS_U16 u16Addr, MS_U8 *pu8Data);
////////////////////////////////////////////////////////////////////////////////
/// To set DVBT's register value, only for special purpose.\n
/// u16Addr       : the address of DVBT's register\n
/// u8Value        : the value to be set\n
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_MSB124X_SetReg(MS_U16 u16Addr, MS_U8 u8Data);
////////////////////////////////////////////////////////////////////////////////
/// To set DVBT's register value, only for special purpose.\n
/// u16Addr       : the address of DVBT's register\n
/// u8Value        : the value to be set\n
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_MSB124X_SetRegs(MS_U16 u16Addr, MS_U8* u8pData, MS_U16 data_size);
////////////////////////////////////////////////////////////////////////////////
/// To set DVBT's register value, only for special purpose.\n
/// u16Addr       : the address of DVBT's register\n
/// u8Value        : the value to be set\n
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_MSB124X_SetReg2Bytes(MS_U16 u16Addr, MS_U16 u16Data);
////////////////////////////////////////////////////////////////////////////////
/// To get DVBT's register  value, only for special purpose.\n
/// u16Addr       : the address of DVBT's register\n
/// return the value of AFEC's register\n
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_MSB124X_GetDSPReg(MS_U16 u16Addr, MS_U8 *pu8Data);
////////////////////////////////////////////////////////////////////////////////
/// To set DVBT's register value, only for special purpose.\n
/// u16Addr       : the address of DVBT's register\n
/// u8Value        : the value to be set\n
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_MSB124X_SetDSPReg(MS_U16 u16Addr, MS_U8 u8Data);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_MSB124X_SetCurrentDemodulatorType
////////////////////////////////////////////////////////////////////////////////
extern void MDrv_DMD_MSB124X_SetCurrentDemodulatorType(eDMD_MSB124X_DemodulatorType eCurrentDemodulatorType);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_MSB124X_LoadDSPCode
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_MSB124X_LoadDSPCode(void);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_MSB124X__DTV_DVBT_DSPReg_CRC
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_MSB124X_DTV_DVBT_DSPReg_CRC(void);
////////////////////////////////////////////////////////////////////////////////
/// power on init
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_MSB124X_Power_On_Initialization(void);
#ifdef __cplusplus
}
#endif


#endif // _DRV_DVBT_H_

