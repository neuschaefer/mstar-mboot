////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStaR Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MSAPI_TUNER_H
#define MSAPI_TUNER_H

//#include "debug.h"
//#include <drvVIF.h>
#include <tuner/Tuner.h>
#include <ShareType.h>
#include <apiDMX.h>
#if 1//((CONFIG_COMMANDS&(CFG_CMD_TUNER | CFG_CMD_DEMOD)) == (CFG_CMD_TUNER | CFG_CMD_DEMOD))

/******************************************************************************/
/*                 Macro                                                      */
/******************************************************************************/
#define FE_NOT_LOCK     0
#define FE_LOCK         1
#define FE_AGC_NOT_LOCK 2

//typedef U8 BOOLEAN;

typedef enum
{
    E_RESULT_SUCCESS = 0,                 ///< Result Success
    E_RESULT_FAILURE,                     ///< Result Failure
    E_RESULT_INVALID_PARAMETER,         ///< Result Invalid Parameter
    E_RESULT_OUTOF_MEMORY,               ///< Result Out of memory
    E_RESULT_OUTOF_EEPROM,               ///< Result Out of EEPROM
    E_RESULT_COMMUNICATION_ERROR,       ///< Result Communication Error
    E_RESULT_SAVE_TO_EEPROM_FAIL,       ///< Result Save to EEPROM fail
    E_RESULT_NOTHING,                    ///< Result Nothing
    E_RESULT_ILLEGAL_ACCESS,            ///< Result Illegal access
    E_RESULT_UNSUPPORTED                ///< Result unsupported
} FUNCTION_RESULT;


typedef enum
{
    DEMOD_MODE_PAL,
    DEMOD_MODE_DVB,
    DEMOD_MODE_NUM
} EN_DEMOD_MODE;


typedef enum
{
    PAL_SCAN,
    DVB_SCAN,
} EN_SCAN_MODE;

typedef enum
{
    DEMOD_SPECTRUM_NORMAL,
    DEMOD_SPECTRUM_INVERTER,
    DEMOD_SPECTRUM_AUTO
} EN_DEMOD_SPECTRUM_MODE;

typedef enum
{
    SIGNAL_NO = 0,          // little or no input power detected
    SIGNAL_WEAK,            // some power detected.
    SIGNAL_MODERATE,        // lock achieved, SNR < 15 dB (approx)
    SIGNAL_STRONG,          // lock achieved, SNR < 24 dB (approx)
    SIGNAL_VERY_STRONG,     // lock achieved, SNR > 24 dB (approx)
} EN_SIGNAL_CONDITION;

typedef enum
{
    STATE_VSB_CHECK_INIT,
    STATE_VSB_CHECK_CR_LOCK,
    STATE_VSB_CHECK_WAIT_INIT,
    STATE_VSB_CHECK_SYNC_LOCK,
    STATE_VSB_CHECK_SNR,
} EN_VSB_CHECK_LOCK_STATE;

typedef enum
{
    STATE_QAM_CHECK_INIT,
    STATE_QAM_CHECK_WAIT_INIT,
    STATE_QAM_CHANGE_MODE,
    STATE_QAM_CHECK_FEC_LOCK,
    STATE_QAM_CHECK_MPEG_LOCK,
} EN_QAM_CHECK_LOCK_STATE;

typedef enum
{
    STATE_VSB_STABLE_INIT,
    STATE_VSB_STABLE_WAIT_INIT,
    STATE_VSB_STABLE_SYNC_LOCK,
} EN_VSB_CHECK_STABLE_STATE;
typedef enum
{
    EN_DVB_T_TYPE=0,
    EN_DVB_C_TYPE
} EN_DVB_TYPE;
/// TP Setting
typedef struct
{
    U32 u32Frequency; ///< Frequency, 50,000 ~ 860,000 Khz
    RF_CHANNEL_BANDWIDTH enBandWidth;   ///< Bandwidth
    U8 u8PLPID;
    U8 u8HpLp;
#if DVB_C_ENABLE
    U8 u8Modulation;
    U32 u32Symbol_rate;
    BOOLEAN bAutoSRFlag;
    BOOLEAN bAutoQamFlag;
#endif
} MS_TP_SETTING;

#if ((FRONTEND_DEMOD_TYPE == MSTAR_MSB123x_DEMOD) || (FRONTEND_DEMOD_TYPE == MSTAR_MSB1233c_DEMOD) || (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD)||(FRONTEND_DEMOD_TYPE == MSTAR_MSB1238_DEMOD)||(FRONTEND_DEMOD_TYPE == MSTAR_MSB1240_DEMOD))
typedef enum
{
    E_DEVICE_DEMOD_NULL,
    E_DEVICE_DEMOD_DVB_T,
    E_DEVICE_DEMOD_DVB_T2,
    E_DEVICE_DEMOD_DVB_C
}EN_DEVICE_DEMOD_TYPE;
#endif
#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB123x_DEMOD)
typedef enum
{
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

    /**********************
     * crc =
     *    ~(T_OPMODE_RFAGC_EN^T_OPMODE_HUMDET_EN^....^T_CONFIG_TS_CLK_RATE_AUTO)
     ************************/
    T_PARAM_CHECK_SUM,

    DVBT_PARAM_LEN,
} DVBT_Param;

typedef enum							// BW: 0->1.7M, 1->5M, 2->6M, 3->7M, 4->8M, 5->10M
{
    E_DEMOD_BW_17M    = 0x0,
    E_DEMOD_BW_5M      = 0x1,
    E_DEMOD_BW_6M      = 0x2,
    E_DEMOD_BW_7M      = 0x3,
    E_DEMOD_BW_8M      = 0x4,
    E_DEMOD_BW_10M    = 0x5,
}E_DEMOD_CHANNEL_BANDWIDTH;

typedef enum
{
    E_DEMOD_LOCK,
    E_DEMOD_CHECKING,
    E_DEMOD_CHECKEND,
    E_DEMOD_UNLOCK,
    E_DEMOD_NULL,
} EN_LOCK_STATUS;

typedef enum
{
    E_FE_SIGNAL_NO = 0,
    E_FE_SIGNAL_WEAK,
    E_FE_SIGNAL_MODERATE,
    E_FE_SIGNAL_STRONG,
    E_FE_SIGNAL_VERY_STRONG,
} EN_FRONTEND_SIGNAL_CONDITION;
#endif

#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB122x_DEMOD)
typedef enum
{
    E_DEMOD_LOCK,
    E_DEMOD_CHECKING,
    E_DEMOD_CHECKEND,
    E_DEMOD_UNLOCK,
    E_DEMOD_NULL,
} EN_LOCK_STATUS;
#endif

#ifdef MSAPI_TUNER_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

INTERFACE void msAPI_Tuner_InintCurrentTPSetting(void);
INTERFACE void msAPI_Tuner_Initialization(BOOLEAN bSrcChg);
INTERFACE void msAPI_Tuner_InitExternDemod(void);
INTERFACE void msAPI_Tuner_ZigZagScan(void);
INTERFACE void msAPI_Tuner_Tune2RfCh(MS_TP_SETTING *pstTPSetting);
INTERFACE BOOLEAN msAPI_Tuner_IsSameRfChannel(MS_TP_SETTING *pstTPSetting);
INTERFACE void msAPI_Tuner_PowerOnOff(BOOLEAN bPower);
INTERFACE U8 msAPI_Tuner_GetSingalSNRPercentage(void);
INTERFACE MS_U16 msAPI_Tuner_GetSignalQualityPercentage(void);
INTERFACE BOOLEAN msAPI_Tuner_GetBER(float *ber);
INTERFACE BOOLEAN msAPI_Tuner_GetSignalModulMode(MS_U16 *wModul_Mode);
INTERFACE void msAPI_Check_Lock_State_Init(void);
INTERFACE BOOLEAN msAPI_Tuner_CheckLock(BOOLEAN *CheckLockResult,BOOLEAN fScan);
INTERFACE void msAPI_Demodulator_Exit(void);
INTERFACE BOOLEAN msAPI_Demodulator_Reset(void);
INTERFACE void msAPI_Tuner_Serial_Control(BOOLEAN bParallelMode);
INTERFACE FUNCTION_RESULT msAPI_Tuner_CheckSignalStrength(MS_U16 *wStrength);
INTERFACE BOOLEAN msAPI_Tuner_Get_CELL_ID( MS_U16 * cell_id);
INTERFACE BOOLEAN msAPI_Tuner_Get_PLP_ID( U8 * pu8plp_id);
INTERFACE U8 msAPI_Tuner_Get_HpLp( void);
INTERFACE BOOLEAN msAPI_Tuner_Is_HierarchyOn(void);
INTERFACE FUNCTION_RESULT msAPI_Tuner_GetCurTPSetting(MS_TP_SETTING *pstCurTPSetting);



INTERFACE void msAPI_Tuner_SwitchSource(EN_DVB_TYPE etype, BOOLEAN bInit);
INTERFACE EN_DVB_TYPE msAPI_Tuner_GetSourceType(void);
INTERFACE void msAPI_Tuner_SetAntenna(BOOLEAN bIsCATV);
INTERFACE DMX_FILTER_STATUS msAPI_Tuner_SetByPassMode(BOOLEAN bByPass, BOOLEAN bPVRMode);
INTERFACE BOOLEAN msAPI_Tuner_IsParallelMode(void);
INTERFACE BOOLEAN msAPI_Tuner_IsByPassMode(void);
INTERFACE U8 msAPI_Tuner_GetDspStatus(void);
#if (DVB_C_ENABLE)
INTERFACE void msAPI_Tuner_UpdateTPSetting(void);
#endif
#if ((FRONTEND_DEMOD_TYPE == MSTAR_MSB123x_DEMOD) || (FRONTEND_DEMOD_TYPE == MSTAR_MSB1233c_DEMOD) \
    ||(FRONTEND_DEMOD_TYPE == MSTAR_MSB1233c_DEMOD))
INTERFACE void msAPI_GetPlpBitMap(U8* u8PlpBitMap);
INTERFACE BOOLEAN msAPI_GetPlpGroupID(U8 u8PlpID, U8* u8GroupID);
INTERFACE BOOLEAN msAPI_SetPlpGroupID(U32 u32PlpID, U32 u32GroupID);
INTERFACE BOOLEAN msAPI_SetDemodType(EN_DEVICE_DEMOD_TYPE enDemodType);
INTERFACE EN_DEVICE_DEMOD_TYPE msAPI_GetDemodType(void);
#endif
#undef INTERFACE

#define ENABLE_SCAN_ONELINE_MSG 0
#endif
#endif // MSAPI_TUNER_H

